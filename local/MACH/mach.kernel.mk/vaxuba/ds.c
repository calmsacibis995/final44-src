/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ds.c,v $
 * Revision 2.5  89/03/09  22:33:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  11:02:06  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/08/22  21:34:57  mja
 * 	Make MACH conversion work: distinguish between first call of
 * 	dsinit() (where we are only initializing the device) and
 * 	subsequent calls (where we are cleaning up old state).  The
 * 	state that we clean up is not correctly initialized on the first
 * 	call.
 * 	[88/08/19            dbg]
 * 
 * Revision 2.1.2.1  88/08/15  20:28:13  mja
 * 	Create CS1 branch.
 * 
 * 18-Apr-88  David Golub (dbg) at Carnegie-Mellon University
 *	Convert for MACH.
 *
 * 10-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Modified to compile for 4.3;  fixed dsprobe() to correctly
 *	return UNIBUS window size.
 *	[ V5.1(F1) ]
 *
 * 29-Apr-85  Fil Alleva (faa) at Carnegie-Mellon University
 *	Changed dsinit() and dsioctl() to preserve filter bits in ASCCSR
 *	when it is not neccesary to change them. Changing the filter
 *	bits often causes a pop or click as a result of an over driven
 *	multiplexor.
 *
 *  3-Jan-85  Fil Alleva (faa) at Carnegie-Mellon University
 *	Changed ubareset() in dswatch() to dsreset() to avoid clearing
 *	the tables of other unibus devices. If the unibus is wedged then
 *	it will have to be reset manually.
 *
 * 23-Nov-84  Fil Alleva (faa) at Carnegie-Mellon University.
 *	Brought up for UNIX 4.2BSD. Removed ds_locore checks
 *	since 4.2 handles FUBAR correctly (I think, besides it's
 *	never been a problem at NBS-SSI).
 *
 * 16-Jun-83  Fil Alleva (faa) at Carnegie-Mellon University
 *	Added code in dsinit() and dsstop() to set ds_locore flag.  When
 *	set the locore.s SCBVEC interupts, machine check and write
 *	timeout, are ignored. The ds_locore flag is imported from
 *	locore.s.
 *
 * 18-Feb-83  Fil Alleva (faa) at Carnegie-Mellon University
 *	Created.
 */

#include <ds.h>
#if	NDS > 0

/*-------------------------------------------------------------------*
 * DS - asynchronous driver for the DSC ADA.
 *	Copyright 1984 - Fil Alleva. Pittsburgh PA.
 *-----------------------------------------*
 * DESIGN
 *
 * After the appropriate parameters to the DSC have been set,
 * requests to either read or can be made. These requests are buffered
 * so that the driver can supply the DSC DMA with the next memory
 * address to use in doing the data transfer. The DMA itself has
 * one request buffered so that when it finishes the current request
 * it can immediately start on the next one. Once the DMA starts on
 * the request `it' has buffered the driver supplies it with another.
 * If the driver has no more requests buffered, sampled data transfer is
 * brought to a halt while the DSC is processing the last request. The
 * reason for this is that the DSC does not synchronize the end of
 * sampled data transfer with the end of the last buffer. The DSC is
 * started once two requests have been buffered by the driver (one to
 * process and one to buffer by the DMA).  The user can specify
 * how many requests the driver should buffer before blocking. I.e. if
 * the user specifies that two requests should be buffered then the
 * first request will return immediately, the second will return
 * immediately and also cause the DSC to start, the third request will
 * block until the first request is finished being serviced and so on.
 * Once the DSC driver stops or detects an error all subsequent
 * requests will return immediately with an error code. At this point
 * the DSC must be reset.
 *
 * IMPLEMENTATION
 *
 * User i/o requests are buffered in a circular buffer with three
 * indices indicating the current request being processed, the next
 * to be given to the DMA and the next free slot in the buffer.  There
 * is also a counter indicating the number of requests buffered currently.
 *
 * The user buffers passed through the read or write calls must not
 * share any common clusters of pages. The reason is that there is
 * is only a lock bit for each page and not a lock count so only one
 * request can be made to lock a page.
 *
 * NOTES
 *
 * 800e0900 is the first address of the DSC on the unibus for 'adb'
 * on a 750. On a 780 the first CSR is at 80100900.
 * Sometimes the DMAOFL bit is set and appears to be lying. The solution
 *	is to power off the remote enclosure (about 30secs), disconnect
 *	the xbus cables, power on the enclosure and reconnect the cables.
 * DSC recommends avoiding consecutive bus accesses. I don't always follow
 * this.
 *
 * INSTALLATION NOTES
 *	
 * The routines vrelvm() and expand() in vm_proc.c need to have the following
 * code added so that the user process can't die or change its memory
 * allocation while pages are locked in memory. Ie. SPHYSIO is set.
 *
 *	while (p->p_flag & SPHYSIO)
 *	    sleep ((caddr_t) &lbolt, (PZERO-1));
 *
 * CMU has a routine called untimeout to remove entries from the callout
 * table.  If your site doesn't have this routine that line of code in
 * dsclose() can be removed without consequences.
 *
 * This driver was written for a 750 with 3 BDP's, 2 of which are already
 * committed full time to other devices. If you have enough BDP's feel free
 * to change the calls to ubasetup(). Currently this driver uses 2 (MINREQ)
 * data paths.
 *-------------------------------------------------------------------*
 */


#include <machine/pte.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mount.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/uio.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/proc.h>
#ifdef	MACH
#include <mach/vm_param.h>
#include <vm/vm_map.h>
#else	MACH
#include <sys/vmmac.h>
#endif	MACH
#include <sys/cmap.h>
#include <sys/kernel.h>		/* for lbolt */

#include <vax/vmparam.h>

#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

#include <sys/ioctl.h>
#include <vaxuba/dsc.h>
#include <vaxuba/dsreg.h>

/*
 * SITE-SPECIFIC
 *     At CMU we have one DMA at position 0.
 */
#define SEQDMA		0		/* DMA address for ASCSEG reg */
#define SEQLST		0200		/* Last Sequence reg field */

#define dsseq(ui, reg, conv, dir) \
((struct dsdevice *) (ui)->ui_addr)->ascseq[reg] = conv | ((dir & 01) << 6)

/*
 * ds flags
 */
#define DS_CLOSED	00
#define DS_OPEN	01
#define DS_BSY		02
#define DS_DONE	04
#ifdef	MACH
#define DS_INIT	010	/* ds_softc is initialized */
#endif	MACH

/*
 * params to driver
 */
#define A_RATE		01
#define A_REQ		02
#define A_SEQ		04

#define MINARG	 	(A_RATE | A_SEQ | A_REQ)
#define DSPRI		(PZERO-1)

#define MAXREQ		16	/* Maximum # of buffered i/o requests */
#define MINREQ		2	/* Minimum # of buffered i/o requests */

#define NEXTBUF(idx)	(((idx)+1)%MAXREQ)
#define NEXTDP(dp)	(((dp)+1)%NDP)

/*
 * relevant information
 * about the dma and asc
 */
struct ds_softc {
    short   c_dmacsr;		/* copy of dma csr on error */
    short   c_asccsr;		/* copy of asc csr on error */
    int     c_flags;		/* internal flags */
    int     c_errs;		/* errors, returned via ioctl */
    short   c_bufno;		/* current buffer request */
    short   c_bufnxt;		/* next buffered i/o request */
    short   c_buffre;		/* next free buffer request slot */
    short   c_bufreq;		/* number of requests to buffer */
    short   c_noreq;		/* number of requests buffered */
    short   c_datap;		/* current data path */
    int     c_uid;		/* user id */
    struct proc *c_procp;	/* process pointer for dsintr */
    int     c_args;		/* args received from user */
    int     c_wticks;		/* watch dog */
    int     c_ubinfo[NDP];	/* uba info */
    caddr_t c_base[MAXREQ];     /* buffered requests */
    int     c_count[MAXREQ];	/* buffered requests */
    struct buf  c_dsb[MAXREQ];	/* buffer headers */
    int	    c_Oldnice;		/* The old user nice */
}               ds_softc[NDS];

/* Driver information for auto-configuration
 */
int dsprobe(), dsattach(), dsintr();

struct uba_device *dsdinfo[NDS];

u_short dsstd[] = {0164400,0};

struct uba_driver dsdriver = {
	dsprobe, 0, dsattach, 0, dsstd, "ds", dsdinfo
};

int   DSCusecount;	/* Use count */
int   DSColdcerrs;	/* Save old c_errs for debug purposes */
short DSCzero = 0;	/* Use 'DSCzero' instead of 0 to avoid clrw 
			   maybe? implemented as read-modify write */


/*------------------------------------------------------------------*
 * DSOPEN - open the DSC
 *------------------------------------------------------------------*
 * IMPLEMENTATION
 *	Calls dsinit().
 *	Starts dswatch().
 *
 * SIDE EFFECTS
 *	Inits ds_softc[unit].
 *
 * DIAGNOSTICS
 *	Prints message on users terminal when the ASC is offline. 
 */
dsopen(dev, flag)
dev_t dev;
{
    register struct dsdevice   *dsaddr;
    register struct uba_device *ui;
    register struct ds_softc   *sc;
    register int    unit;
    extern int dswatch ();

    DSCusecount++;

    if ((unit = minor (dev)) >= NDS)
	goto bad;

    if ((ui = dsdinfo[unit]) == NULL)
	goto bad;

    if (ui->ui_alive == 0)
	goto bad;

    sc = &ds_softc[ui->ui_unit];

    /* Check if the device is already open
     */
    if (sc->c_flags & DS_OPEN) {
bad:	return(ENXIO);
    }

    /* initialize
     */
    if (dsinit (unit)) {
	uprintf ("DSopen: Remote Enclosure Offline\n");
	return(EIO);
    }

    /* Some sc fields can't be set in ds_init
     */
    sc->c_procp  = u.u_procp;
    sc->c_uid    = u.u_ruid;
    sc->c_flags  = DS_OPEN;

    sc->c_wticks = 0;			/* Clear the watch dog timer */
    dswatch (ui->ui_unit);		/* Start the watch dog */
    return (0);
}


/*------------------------------------------------------------------*
 * DSCLOSE - close the DSC
 *------------------------------------------------------------------*
 * IMPLEMENTATION
 *	Calls dsinit().
 *	Waits for pending buffers to complete.
 *	Cancels pending dswatch() timeouts.
 *
 * SIDE EFFECTS
 *	Reinits ds_softc[unit].
 *
 * DIAGNOSTICS
 *	Errors returned via return ();
 */
dsclose (dev, flag) {
    register int    unit;
    register struct uba_device *ui;
    register struct ds_softc   *sc;
    extern int dswatch ();

    if ((unit = minor (dev)) >= NDS)
	goto bad;

    if ((ui = dsdinfo[unit]) == NULL) {
bad:	return(ENXIO);
    }

    /* Wait for pending buffers to complete.
     */
    sc = &ds_softc[unit];
    if (DS_BSY & sc->c_flags)
	while (!(sc->c_flags & DS_DONE))
	    sleep ((caddr_t) &lbolt, DSPRI);

    DSColdcerrs = sc->c_errs; 
    (void) dsinit (unit);

    /* cancel pending timeouts to insure callout table doesn't overflow
     */
    untimeout (dswatch, (caddr_t) ui->ui_unit);
    return (0);
}


/*------------------------------------------------------------------*
 * DSINIT - initialize device
 *------------------------------------------------------------------*
 * IMPLEMENTATION
 *	If DS_BSY is set call dsstop().
 *	Inits DMAREGS.
 *	Inits ASCREGS if the ASC is on line.
 *
 * SIDE EFFECTS
 *	Examine dsstop() for side effects.
 *
 * DIAGNOSTICS
 *	Return 1 on error, 0 otherwise.
 *
 * NOTES
 * 	This routine is no longer called from interrupt level.
 */
dsinit (unit) {
    register struct dsdevice   *dsaddr;
    register struct uba_device *ui;
    register struct ds_softc   *sc;
    register short  dummy;
    register int    offl, i;

    if (unit >= NDS)
	return (1);

    if ((ui = dsdinfo[unit]) == NULL)
	return (1);

    dsaddr = (struct dsdevice  *) ui->ui_addr;
    sc = &ds_softc[ui->ui_unit];

    /* Check if the DSC was running. If it was then we have to
     * release the uba map registers (and BDPs if used) and we
     * have to unlock memory.
     */
    if (sc->c_flags & DS_BSY)
	dsstop (unit);

#ifdef	MACH
    /* Unlock memory here
     */
    if (sc->c_flags & DS_INIT)
        dsc_unwire_all(sc);
#endif	MACH

    /* Put the DMA registers in a quiescent state
     */
    dsaddr->dmaclr = DSCzero;   /* Clear Device */
    dsaddr->dmadr = DSCzero;	/* Clear data register */
    dummy = dsaddr->dmasar;	/* Clears DMASFL flag bit */

    /* reset ds_softc
     */
    sc->c_dmacsr = 0;
    sc->c_asccsr = 0;
    sc->c_wticks = 0;
#ifdef	MACH
    sc->c_flags  = DS_INIT;
#else	MACH
    sc->c_flags  = 0;
#endif	MACH
    sc->c_errs   = 0;
    sc->c_args   = 0;
    sc->c_bufno  = 0;
    sc->c_bufnxt = 0;
    sc->c_buffre = 0;
    sc->c_bufreq = 0;
    sc->c_noreq  = 0;
    sc->c_datap  = 0;
    for (i = 0; i < MAXREQ; i++) {
	sc->c_base[i] = (caddr_t) -1;
	sc->c_count[i] = 0;
    }

    /* Check if the remote enclosure is offline
     */
    if (dsaddr->dmacsr & DMA_OFL)
	offl = 1;
    else {
  	/* Reset remote enclosure
	 */
	dsaddr->ascrst = DSCzero;
	dsaddr->asccsr &= ASC_HZMSK;
	offl = 0;
    }

    return (offl);
}


/*------------------------------------------------------------------*
 * DSSTART - queue reads or writes to the DSC
 *------------------------------------------------------------------*
 * IMPLEMENTATION
 *	Validates arguments. See initial discussion of driver.
 *	Set up buffer header for uba map registers.
 *	Lock pages if DS_BSY.
 *	Otherwise check if we have buffered enque the request
 *	and check if can start.
 *	Block when c_noreq > c_bufreq
 *
 * SIDE EFFECTS
 *	Once the DSC is running, c_noreq is examined every time dsintr()
 *	runs to check when the end condition is met.
 *
 * DIAGNOSTICS
 *	Error returned via return ().
 *	More detail can be found in c_errs.
 *
 * HISTORY
 *	Moved the setting of the ASC_RUN bit to come after the second
 *	ubasetup call to avoid possibly losing BDP's. The problem can
 *	arise if the DSC immediately interupts after setting the RUN bit.
 *	This causes the device and its buffers to be released, unfortunately
 *	we were about to allocate the second data path which subsequently
 *	is never released.
 */
dsstart(unit, rw, iov)
struct iovec *iov;
{
    register struct dsdevice *dsaddr;
    register struct uba_device *ui;
    register struct ds_softc *sc;
    register struct buf *bp;
    int req, dummy;
    int i, opl;

    sc = &ds_softc[unit];

    /* Check for enough info to do our thing
     */
    if ((sc->c_args & MINARG) != MINARG)
	sc->c_errs |= EDS_ARGS;

    /* Check if converting was finished already
     */
    if (sc->c_flags & DS_DONE)
	sc->c_errs |= EDS_DONE;

#ifdef	MACH
    /* we check for valid pages and wire them down in one operation. */
#else	MACH
    /* Check the users access to the pages he wants to use.
     */
    if (useracc(iov->iov_base, iov->iov_len, B_WRITE) == NULL)
	sc->c_errs |= EDS_BUFACC;
#endif	MACH

    /* We are going to use the Direct Data Path so our
     * buffer MUST be short word aligned.
     */
     if (((int)iov->iov_base) & 01)
	sc->c_errs |= EDS_BUFALL;

    /* check for odd byte count
     */
    if (iov->iov_len & 01)
	sc->c_errs |= EDS_CNT;

#ifdef	MACH
    /* we check for valid pages and wire them down in one operation. */
#else	MACH
    /* If BSY then check if we can lock these pages if not
     * then stop the DSC and set the EDS_LCK bit.
     */
    if (DS_BSY & sc->c_flags) 
	if (dschklock (iov->iov_base, iov->iov_len)) {
	    dsstop (unit);
	    sc->c_errs |= EDS_LCK;
	}
#endif	MACH

    /* Check if there have been any errors yet if so forget it.
     * The DSC must be reinitialized.
     */
    if (sc->c_errs) {
#ifdef	MACH
	/* unwire memory here */
	dsc_unwire_all(sc);
#endif	MACH
	return(EFAULT);
    }

#ifdef	MACH
    /*
     * Unwire the pages belonging to the next buffer.
     */
    if (sc->c_base[sc->c_buffre] != (caddr_t)-1) {
	dsc_unwire_one(sc);
    }
#endif	MACH

    /* set up the c_dsb[sc->c_buffer] with
     * the user's buffer
     */
    bp = &sc->c_dsb[sc->c_buffre];
    bp->b_un.b_addr = iov->iov_base;
    bp->b_error = 0;
    bp->b_proc = u.u_procp;
    bp->b_flags = B_PHYS | B_BUSY;
    bp->b_bcount = iov->iov_len;

    /* If the DSC is busy it means that we don't need to
     * wait to lock these pages down and better do it now.
     */
    if (sc->c_flags & DS_BSY) {
#ifdef	MACH
	kern_return_t	result;
	result = vm_map_pageable(current_task()->map,
			trunc_page(iov->iov_base),
			round_page(iov->iov_base + iov->iov_len),
			FALSE);
	if (result != KERN_SUCCESS) {
	    return(EFAULT);
	}
#else	MACH
        vslock(iov->iov_base, (int) iov->iov_len);
#endif	MACH

	/* Can't protect vslock from interrupts so we need to check
	 * if the DSC is still busy, if not we need to release this
	 * virtual segment that we just locked. After that we lower
	 * priority and return to the user. This code must be protected.
	 */
	opl = spl6();
	if ((sc->c_flags & DS_BSY) == 0) {
#ifdef	MACH
	    splx(opl);
	    (void) vm_map_pageable(current_task()->map,
			trunc_page(iov->iov_base),
			round_page(iov->iov_base + iov->iov_len),
			TRUE);
#else	MACH
	    vsunlock (iov->iov_base, iov->iov_len, B_WRITE);
	    splx (opl);
#endif	MACH
	    return(EFAULT);
	}
    }

    /* Looks like everything is OK and we can let dsstop or dsintr
     * worry about unlocking these pages when the time comes. Although
     * we do stay at high priority until the bookkeeping is done.
     *
     * Save these so we can unlock the pages when we are done
     * with them.
     */
    sc->c_base[sc->c_buffre] = iov->iov_base;
    sc->c_count[sc->c_buffre] = iov->iov_len;

    /* Set c_buffre to the next free request slot
     * increment the number of pending requests.
     */
    sc->c_buffre = NEXTBUF(sc->c_buffre);
    sc->c_noreq++;

    (void) spl0();


    /* Once the number of pending requests is >= MINREQ check to
     * see if we have started I/O yet, if not then
     * lets get the show on the road and
     *		1) Set SPHYSIO
     *		2) Set DS_BSY
     *		3) Lock down those pages
     *		4) Start the DSC
     * Note that a request is not "serviced" until the buffer is
     * finished being converted. Therefore only dsintr() removes
     * requests.
     *
     * Note: In the off chance that this is used on a machine with
     * some BDP's available for other devices it should be possible
     * just to make that change.
     */
    if ((sc->c_noreq >= MINREQ) && !(sc->c_flags & DS_BSY)) {
	u.u_procp->p_flag |= SPHYSIO;

	/* While doing the initial lock down check if segments have
	 * overlapping pages if so release locked pages,
	 * unset SPHYSIO, flag an error and return
	 */
#ifdef	MACH
	for (i = 0; i < sc->c_noreq; i++) {
	    kern_return_t	result;

	    result = vm_map_pageable(current_task()->map,
			trunc_page(sc->c_base[i]),
			round_page(sc->c_base[i] + sc->c_count[i]),
			FALSE);
	    if (result != KERN_SUCCESS) {
		while (--i > 0) {
		    (void) vm_map_pageable(current_task()->map,
			trunc_page(sc->c_base[i]),
			round_page(sc->c_base[i] + sc->c_count[i]),
			TRUE);
		}
		u.u_procp->p_flag &= ~SPHYSIO;
		sc->c_errs |= EDS_LCK;
		return(EFAULT);
	    }
	}
#else	MACH
	for (i = 0; i < sc->c_noreq; i++)
	    if (dschklock (sc->c_base[i], sc->c_count[i])) {
		while ((--i) > 0)
		    vsunlock (sc->c_base[i], sc->c_count[i], B_WRITE);
		u.u_procp->p_flag &= ~SPHYSIO;
		sc->c_errs |= EDS_LCK;
		return(EFAULT);
	    } else
		vslock (sc->c_base[i], sc->c_count[i]);
#endif	MACH

	sc->c_flags |= DS_BSY;

	ui = dsdinfo[unit];
	dsaddr = (struct dsdevice *) ui->ui_addr;

	/* if reading then going to
	 * memory so set W2M
	 */
        if (rw == B_WRITE) {
	    dsaddr->asccsr |= ASC_PLAY;
	    dsaddr->dmacsr = DMA_CHN | DMA_IE;
	}
	else {
	    dsaddr->asccsr |= ASC_RECORD;
	    dsaddr->dmacsr = DMA_W2M | DMA_CHN | DMA_IE;
	}

        dummy = dsaddr->ascrst;		/* Clear ACSCSR status bits */
        dsaddr->asccsr |= ASC_IE;	/* Enable ASC interupts */
        dummy = dsaddr->dmasar;		/* Clear DMASFL bit */
        dsaddr->dmacls = DSCzero;	/* Clear DMACSR status bits */
        dsaddr->dmawc = -1;		/* Prepare for chaining */

	/* Set up first two buffers for conversion.  Rest is handled
	 * by dsintr().
	 */
	req = sc->c_bufnxt;
        sc->c_ubinfo[0] = ubasetup(ui->ui_ubanum, &sc->c_dsb[req],UBA_NEEDBDP);
        dsaddr->dmablr = ~(sc->c_count[req] >> 1);
        dsaddr->dmasax =  (sc->c_ubinfo[0] >> 16) & 03;
        dsaddr->dmasar =   sc->c_ubinfo[0];
	sc->c_bufnxt = NEXTBUF (sc->c_bufnxt);

	req = sc->c_bufnxt;
        sc->c_ubinfo[1] = ubasetup(ui->ui_ubanum, &sc->c_dsb[req],UBA_NEEDBDP);
        dsaddr->dmablr = ~(sc->c_count[req] >> 1);
        dsaddr->dmasax =  (sc->c_ubinfo[1] >> 16) & 03;
        dsaddr->dmasar =   sc->c_ubinfo[1];
	sc->c_bufnxt = NEXTBUF (sc->c_bufnxt);

        /* Start the sample transfer
	 */
        dsaddr->asccsr |= ASC_RUN;

#ifdef	MACH
#else	MACH
	/* Increase user process priority while I/O is in progress
	 */
	sc->c_Oldnice =	u.u_procp->p_nice;
	u.u_procp->p_nice = 0;
	(void) setpri (u.u_procp);
#endif	MACH
    }

    /* Check to see if we've made more than sc->c_bufreq requests, if so
     * go to sleep until dsintr wakes us up.
     */
    if (sc->c_noreq > sc->c_bufreq) {
	sleep ((caddr_t) sc, DSPRI);
	if (sc->c_errs) {
#ifdef	MACH
	    /* unwire memory here */
	    dsc_unwire_all(sc);
#endif	MACH
	    return(EIO);
	}
    }
    return(0);
}

/*------------------------------------------------------------------*
 * DSINTR - process interupts and set up next buffer to convert
 *------------------------------------------------------------------*
 * IMPLEMENTATION
 *	Check for device errors.
 *	Stop when processing last buffer or on error.
 *	Release uba map registers and unlock pages of buffer just done.
 *	Wakes up dsstart() if blocked.
 *	Set up next buffer for conversion.
 *
 * SIDE EFFECTS
 * 	Must clear c_wticks or dswatch() will call dsreset().
 *
 * DIAGNOSTICS
 *	Sets c_errs.
 *	Saves DMACSR and ASCCSR.
 *	Prints contents of DMACSR and ASCCSR (if avail) on console.
 *
 * NOTES
 *	1) Device registers are copied to memory to decrease bus traffic.
 *	2) Consecutive bus accesses are avoided. (DSC's suggestion).
 *	3) Can't do a "read-modify-write" while converters are running
 *	   but you try and find out what instructions are implemented
 *	   that way and you win the prize.
 *	4) Note that you must write something to the dma11 clear status
 *	   register or you'll never get any more interrupts.
 *
 * HISTORY
 *	Changed error check to ignore BSY bit DMACSR
 */
dsintr(dev)
dev_t dev;
{
    register struct dsdevice   *dsaddr;
    register struct ds_softc   *sc;
    int     unit;

    unit = minor (dev);
    sc = &ds_softc[unit];

    /* reset c_wticks
     */
    sc->c_wticks = 0;

    dsaddr = (struct dsdevice  *) dsdinfo[unit]->ui_addr;
    sc->c_dmacsr = dsaddr->dmacsr;

    /* check for converter error immediately.
     */
    if (sc->c_dmacsr & DMA_ERR)
	sc->c_errs |= EDS_CERR;

    /* Check for termination, either normal or error.
     * Normal termination comes with only 1 pending request
     * which is used to orderly shut down the DSC.
     *
     * NOTE: To simplify the termination code we don't
     * do the bookkeeping on the request just completed until
     * after we check for termination so the number of pending
     * requests c_noreq is 1 greater (i.e. 2 for termination) than
     * the actual number of pending requests at this point.
     */
    if (sc->c_errs || (sc->c_noreq <= MINREQ)) {
	dsstop (unit);
	if (sc->c_dmacsr & DMA_ERR)
	    printf ("ds%d error: asccsr=%b, dmacsr=%b\n", unit,
		    sc->c_asccsr, ASC_BITS, sc->c_dmacsr, DMA_BITS);
	return;
    }


    /* Clean up the buffer we just finished.
     */
    ubarelse (dsdinfo[unit]->ui_ubanum, &sc->c_ubinfo[sc->c_datap]);
#ifdef	MACH
#else	MACH
    dsvsunlock (sc->c_procp, sc->c_base[sc->c_bufno], sc->c_count[sc->c_bufno],
	        B_READ);
    sc->c_base[sc->c_bufno] = (caddr_t) -1;
    sc->c_bufno = NEXTBUF (sc->c_bufno);
    sc->c_noreq--;
#endif	MACH
    wakeup ((caddr_t) sc);

    /* Map next buffer
     */
    sc->c_ubinfo[sc->c_datap] = ubasetup (dsdinfo[unit]->ui_ubanum,
			&sc->c_dsb[sc->c_bufnxt], UBA_NEEDBDP|UBA_CANTWAIT);

    /* reinitialize dma11
     */
    dsaddr->dmacls = DSCzero;

    /* 
     * load dma11 registers
     */
    dsaddr->dmablr = ~(sc->c_count[sc->c_bufnxt] >> 1);
    dsaddr->dmasax = (sc->c_ubinfo[sc->c_datap] >> 16) & 03;
    dsaddr->dmasar =  sc->c_ubinfo[sc->c_datap];

    /* Advance to next buffer and next data path
     */
    sc->c_bufnxt = NEXTBUF (sc->c_bufnxt);
    sc->c_datap  = NEXTDP (sc->c_datap);
}



/*------------------------------------------------------------------*
 * DSSTOP - stop the DSC and release resourses
 *------------------------------------------------------------------*
 * IMPLEMENTATION
 *	Zero DMACSR.
 *	Attempt to capture ASCCSR.
 *	Release resources.
 *	    If it's a reset don't release uba resources since
 *	    the system does that for us.
 *      Wake up dsstart() if it's sleeping.
 *	Unset SPHYSIO.
 *
 * NOTES
 *	Called from interupt level normally.
 */
dsstop (unit)
{
    register struct dsdevice   *dsaddr;
    register struct ds_softc *sc;
    register int i;

    dsaddr = (struct dsdevice  *) dsdinfo[unit]->ui_addr;
    sc = &ds_softc[unit];

    sc->c_dmacsr = dsaddr->dmacsr;	/* get an upto date copy */
    dsaddr->dmacsr = DSCzero;		/* turn off dma11 */
    sc->c_flags &= ~DS_BSY;		/* turn off busy */
    sc->c_flags |= DS_DONE;		/* We are done */

    /* Check if it is safe to touch the ASC registers before doing so.
     */
    if (!((DMA_OFL | DMA_XBA) & sc->c_dmacsr)) {
        sc->c_asccsr = dsaddr->asccsr;		/* get asc status */
	/* clear run, ie, record and play */
        dsaddr->asccsr = sc->c_asccsr & 
			 ~(ASC_RUN | ASC_IE | ASC_RECORD | ASC_PLAY);	
    }

    /* Release uba data paths
     */
    for (i = 0; i < NDP; i++) {
	if ((sc->c_ubinfo[i]) && (!(sc->c_errs & EDS_RST)))
            ubarelse (dsdinfo[unit]->ui_ubanum, &sc->c_ubinfo[i]);
	sc->c_ubinfo[i] = 0;
    }

#ifdef	MACH
    /*	Cannot unwire memory at interrupt level - routine waiting for
     *  DS_DONE will
     */
#else	MACH
    /* Unlock Memory
     * We should know what's what based on buffer indexes
     * But this is safer.
     */ 
    for (i = 0; i < MAXREQ; i++) {
	if (sc->c_base[i] != (caddr_t) -1)
	    dsvsunlock (sc->c_procp, sc->c_base[i], sc->c_count[i], B_READ);
	sc->c_base[i] = (caddr_t) -1;
    }
#endif	MACH
    sc->c_noreq--;			/* penultimate req. serviced */
    sc->c_noreq--;			/* last req. serviced */
	
    /* Unset SPHYSIO
     */
    sc->c_procp->p_flag &= ~SPHYSIO;

#ifdef	MACH
#else	MACH
    /* Reset user process priority to its old value.
     */
    sc->c_procp->p_nice = sc->c_Oldnice;
    (void) setpri (sc->c_procp);
#endif	MACH
    wakeup ((caddr_t) sc);			/* Wakeup dsstart */
}


/*------------------------------------------------------------------*
 * DSREAD - a/d conversion
 */
dsread(dev,uio)
dev_t dev;
struct uio *uio;
{
    return (dsstart(minor(dev), B_READ, uio->uio_iov));
}

/*------------------------------------------------------------------*
 * DSWRITE - d/a conversion
 */
dswrite(dev,uio)
dev_t dev;
struct uio *uio;
{
    return (dsstart(minor(dev), B_WRITE, uio->uio_iov));
}


/*------------------------------------------------------------------*
 * DSIOCTL - ioctl interface for DSC driver
 */
dsioctl(dev, cmd, data, flag)
dev_t dev;
caddr_t data;
{
    register struct dsdevice *dsaddr;
    register struct ds_softc *sc;
    register struct ds_seq *dq;
    register struct ds_err *de;
    struct uba_device *ui;
    int req;
    
    sc = &ds_softc[minor(dev)];
    ui = dsdinfo[minor(dev)];
    dsaddr = (struct dsdevice *) ui->ui_addr;

    switch (cmd) {
	/* set number of requests to buffer */
	case DSREQ:
	    req = *(int *) data;

	    if ((req > MAXREQ) || (req < MINREQ)) {
		return(EFAULT);
	    }

	    sc->c_args |= A_REQ;
	    sc->c_bufreq = req;
	    break;
	
    	/* set sequence */
	case DSSEQ:
	    dq = (struct ds_seq *) data;

	    if ((dq->reg > 15) || (dq->reg < 0)) {
		return(EINVAL);
	    }

	    dsseq(ui, (int) dq->reg, (int) dq->conv, (int) dq->dirt);
	    break;

	/* mark last sequence register */
	case DSLAST:
	    dq = (struct ds_seq *) data;

	    if ((dq->reg > 15) || (dq->reg < 0)) {
		return(EINVAL);
	    }

	    dsaddr->ascseq[dq->reg] |= bit(7);
	    sc->c_args |= A_SEQ;
	    break;

	/* set sample rate */
	case DSRATE:
	    dq = (struct ds_seq *) data;

	    dsaddr->ascsrt = dq->dirt - 1;   /* SRT is 1 less than actual */
	    sc->c_args |= A_RATE;
	    break;

	case DS20KHZ:
	    dsaddr->asccsr &= (~ ASC_HZMSK | ASC_HZ20);
	    dsaddr->asccsr |= ASC_HZ20;		/* set 20kHz filter */
	    break;

	case DS6KHZ:
	    dsaddr->asccsr &= (~ ASC_HZMSK | ASC_HZ6);
	    dsaddr->asccsr |= ASC_HZ6;		/* set 6.4kHz filter */
	    break;

	case DS3KHZ:
	    dsaddr->asccsr &= (~ ASC_HZMSK | ASC_HZ3);
	    dsaddr->asccsr |= ASC_HZ3;		/* set 3.2kHz filter */
	    break;

	case DSBYPASS:
	    dsaddr->asccsr &= (~ ASC_HZMSK | ASC_BYPASS);
	    dsaddr->asccsr |= ASC_BYPASS;	/* set bypass */
	    break;

	/* fetch errors */
	case DSERRS:
	    /* Wait till we're done */
	    if (DS_BSY & sc->c_flags)
		while (!(sc->c_flags & DS_DONE))
		    sleep ((caddr_t) &lbolt, DSPRI);
#ifdef	MACH
	    /* Unwire memory here */
	    dsc_unwire_all(sc);
#endif	MACH
	    de = (struct ds_err *) data;
	    de->dma_csr = sc->c_dmacsr;
	    de->asc_csr = sc->c_asccsr;
	    de->errors = sc->c_errs;
	    break;

	default:
	    return(ENOTTY);
	    break;
    }
    return (0);
}



/*------------------------------------------------------------------*
 * DSPROBE - Generates an interupt at system start up.
 *------------------------------------------------------------------*
 * IMPLEMENTATION
 *	Init DMACSR.
 *	Turn BSY bit on and off to generate an interrupt.
 *	Init ASCCSR if the ASC is on line.
 *
 * DIAGNOSTICS
 *	Print warning message on console if the ASC is off line.
 */
dsprobe (reg)
caddr_t reg;
{
    register int    br,	        /* value-result */
                    cvec;	/* value-result */
    register struct dsdevice   *dsaddr;
    register int    i;
    int     dummy;

#ifdef	lint	
    br = 0;
    cvec = br;
    br = cvec;
#endif	lint

    dsaddr = (struct dsdevice  *) reg;

    dsaddr->dmacsr = DSCzero;	/* Clear DMACSR command bits */
    dsaddr->dmacls = DSCzero;	/* Clear DMACSR status bits */

    /* Set unibus Interupt Enable and BuSY bits
     * Clearing BSY asserts DMAIIN and causes
     * the DMA to interupt to the on the Unibus
     */
    dsaddr->dmacsr = DMA_BSY | DMA_IE;
    dsaddr->dmacsr = DMA_IE;

    DELAY (20000);

    /* Check if the remote enclosure is off line. If it is on line then
     * initialize ASCCSR and status bits
     */
    if ((dsaddr->dmacsr & DMA_OFL) == 0) {
	dsaddr->asccsr = DSCzero;	/* Clear command bits */
	dsaddr->ascrst = DSCzero;	/* Clear status bits and set SRT=80 */
    }
    else
	printf ("ds: Remote enclosure is offline\n");

    /* Put the DMA registers in a quiescent state
     */
    dsaddr->dmaclr = DSCzero;   /* Clear Device */
    dsaddr->dmadr = DSCzero;	/* Clear data register */
    dummy = dsaddr->dmasar;	/* Clears DMASFL flag bit */
    return(0400);
}

/*------------------------------------------------------------------*
 * DSATTACH - attach driver routine
 */
dsattach(ui)
struct uba_device *ui;
{
    (void) dsinit(ui->ui_unit);
}


/*-------------------------------------------------------------------*
 * DSWATCH - watch out to see if the DSC hangs !
 *-------------------------------------------------------------------*
 * IMPLEMENTATION
 *	We only worry about watching the DSC when it is open. No need
 * 	to waste cycles if nobody is using it. Dsopen() starts dswatch().
 *
 * NOTES
 *	C_wticks gets cleared on each interrupt. Dswatch() increments
 *	c_wticks and if c_wticks gets over a threshold then the addacs
 *	are assumed to have hung and we do a dsreset.
 */
dswatch (ds) {
    register struct uba_device *ui;
    register struct ds_softc   *sc;

    sc = &ds_softc[ds];
    /** Requeue us only if the device is open **/
    if (sc->c_flags & DS_OPEN)
	timeout (dswatch, (caddr_t) ds, 60);
    else
	return;

    if ((ui = dsdinfo[ds]) == NULL)
	return;
    if (ui->ui_alive == 0)
	return;

    if ((sc->c_flags & DS_BSY) == 0) {
	sc->c_wticks = 0;
	return;
    }

    sc->c_wticks++;
    if (sc->c_wticks >= 25) {
	sc->c_wticks = 0;
	printf ("ds%d: lost interrupt\n", ds);
	dsreset (ui->ui_ubanum);
    }
}


/*-------------------------------------------------------------------*
 * DSRESET - shut down DSC and release resources and memory
 */
dsreset (uban) {
    register struct uba_device *ui;
    register struct ds_softc   *sc;
    register int    ds;

    for (ds = 0; ds < NDS; ds++) {
	if ((ui = dsdinfo[ds]) == NULL)
	    continue;
	if (ui->ui_alive == 0)
	    continue;
	if (ui->ui_ubanum != uban)
	    continue;

	printf (" ds%d", ds);

	/* Set the error reset bit in c_errs so that we know
	 * what happened.
	 */
	sc = &ds_softc[ds];
	sc->c_errs |= EDS_RST;

	/* dsstop unlocks memory, releases uba resources and
	 * wakes the user proc. 
	 */
	if (sc->c_flags & DS_BSY)
	    dsstop(ds);
    }
}





#ifdef	MACH
/*
 *	Since MACH cannot unwire pages at interrupt level, these routines
 *	must be called from thread context whenever there is a chance
 *	that wired buffers are outstanding.
 */

/*
 *	Unwire buffer at sc->c_bufno if wired
 */
dsc_unwire_one(sc)
    register struct ds_softc	*sc;
{
    if (sc->c_base[sc->c_bufno] != (caddr_t)-1) {
	/*
	 *	Unwire the buffer
	 */
	(void) vm_map_pageable(sc->c_procp->task->map,
			trunc_page(sc->c_base[sc->c_bufno]),
			round_page(sc->c_base[sc->c_bufno] +
				   sc->c_count[sc->c_bufno]),
			TRUE);
	sc->c_base[sc->c_bufno] = (caddr_t) -1;
	sc->c_bufno = NEXTBUF(sc->c_bufno);
	sc->c_noreq--;
    }
}

/*
 *	Unwire all buffers
 */
dsc_unwire_all(sc)
    register struct ds_softc	*sc;
{
    while (sc->c_base[sc->c_bufno] != (caddr_t)-1) {
	/*
	 *	Unwire the buffer
	 */
	(void) vm_map_pageable(sc->c_procp->task->map,
			trunc_page(sc->c_base[sc->c_bufno]),
			round_page(sc->c_base[sc->c_bufno] +
				   sc->c_count[sc->c_bufno]),
			TRUE);
	sc->c_base[sc->c_bufno] = (caddr_t) -1;
	sc->c_bufno = NEXTBUF(sc->c_bufno);
    }
}

#else	MACH
/*-------------------------------------------------------------------*
 * DSVSUNLOCK - unlock a virtual segment from interupt level
 */
dsvsunlock(uprocp, base, count, rw)
struct proc *uprocp;
caddr_t base;
{
    register struct pte *pte;
    register struct cmap *c;
    register int    npf;

    pte = vtopte (uprocp, btop (base));
    npf = btoc (count + ((int) base & CLOFSET));
    while (npf > 0) {
	c = &cmap[pgtocm(pte -> pg_pfnum)];
	MUNLOCK (c);
	if (rw == B_READ)	/* Reading from device writes memory */
	    pte -> pg_m = 1;
	pte += CLSIZE;
	npf -= CLSIZE;
    }
}


/*-------------------------------------------------------------------*
 * DSCHKLOCK - check if any pages in segment are locked down.
 *
 * Returns 1 if pages are locked 0 otherwise.
 */

dschklock (base, count)
caddr_t base;
{
    register unsigned   v;
    register int    npf;
    register struct pte *pte;

    v = btop (base);
    pte = vtopte (u.u_procp, v);
    npf = btoc (count + ((int) base & CLOFSET));
    while (npf > 0) {
	if (pte -> pg_v)
	    if (cmap[pgtocm(pte->pg_pfnum)].c_lock)
		return(1);
	pte += CLSIZE;
	v += CLSIZE;
	npf -= CLSIZE;
    }
    return (0);
}
#endif	MACH

#endif	NDS > 0
