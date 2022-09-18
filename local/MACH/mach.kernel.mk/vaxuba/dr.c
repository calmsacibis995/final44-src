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
 * $Log:	dr.c,v $
 * Revision 2.3  89/03/09  22:32:54  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:01:26  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.
 *	[V1(1)]
 *
 * 16-Sep-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed drprobe() to use maintenance mode DMA cycle feature to cause
 *	a DR11-W to interrupt rather than simply enabling interrupts which
 *	doesn't cause an interrupt on the DR11-W (V3.05f). 
 *
 * 23-Apr-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Completely restructured to separate out user device specific
 *	functionality from common DR11-B/W processing (V3.04g).
 *
 * 18-Nov-81  Mike Accetta (mja) at Carnegie-Mellon University
 *	Restructured slightly to bring more in line with other UNIBUS
 *	drivers and to use ubago which provides exclusive UNIBUS access
 *	synchronization;  fixed bug in drreset which failed to allow
 *	for reallocation of UBA resources on restarted I/O (V3.03b).
 *
 * 23-Oct-81  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added UBA reset recovery (V3.02e).
 *
 * 11-Jul-81  Mike Accetta (mja) at Carnegie-Mellon University
 *	Modified to allow sharing between up to 4 different applications
 *	via separate minor devices and a few new synchronization
 *	IOCTL primitives (V2.00q).
 *
 * 01-Nov-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded for Berkeley version 3.34;  extracted NDR11 onto dr.h
 *	(V2.00).
 *
 * 27-Mar-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed bug in dropen() which always caused function bit 2 to be
 *	cleared;  changed to perform I/O in maximum multiples of
 *	40*1024 bytes (V1.06a).
 *
 * 18-Mar-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added DIOCNOWC and DIOCWC ioctl calls to enable/disable dr-11b
 *	function bit 2 which is used for Grinnell byte
 *	packing/unpacking (V1.05e).
 *
 * 11-Mar-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Moved setting of control function bits before setting of
 *	GO bit in csr (to deal with timing problems in the Grinnell
 *	interface);  added test in interrupt routine for spurious
 *	interrupts without READY bit set (V1.05c).
 *
 * 12-Feb-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed bug in drread() and drwrite() routines which used the
 *	same name for a variable and the global parameter table and
 *	which hence passed a random location to physio() as the buffer
 *	header for I/O (V1.03a).
 *
 * 04-Feb-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created (V1.02).
 *
 */
/*
 *  DR11-B/DR11-W driver  
 */

/*	dr.c	CMU	1/28/80	*/

#include <dr.h>

#if	NDR > 0

#define DEBUG	0

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/uio.h>

#include <vax/pte.h>

#include <vaxuba/drreg.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>


extern int drprobe(), drattach(), drgo(), drintr();
struct	uba_ctlr drctlr[NDR];		/* these are faked for ubago */
struct	uba_device *drinfo[NDR];
u_short	drstd[] = { 0172410, 0 };
struct	uba_driver drdriver =
{
    drprobe, 0, drattach, drgo, drstd, "dr", drinfo, "dr"
};



extern nodev(), nulldev();

#define NCMULP	0
#if	NCMULP > 0
extern	cmulpopen(), cmulpclose(), cmulpread(), cmulpwrite();
extern	cmulpioctl(), cmulpintr(), cmulpreset(), cmulptout();
extern	cmulpattach();
#else
#define cmulpopen	nodev
#define cmulpclose	nodev
#define cmulpread	nodev
#define cmulpwrite	nodev
#define cmulpioctl	nodev
#define cmulpintr	nulldev
#define cmulpreset	nulldev
#define cmulptout	nulldev
#define cmulpattach	nulldev
#endif	NCMULP

#include <gmr.h>
#if	NGMR > 0
extern	gmropen(), gmrclose(), gmrread(), gmrwrite();
extern	gmrioctl(), gmrintr(), gmrreset(), gmrtout();
extern	gmrattach();
#else
#define gmropen		nodev
#define gmrclose	nodev
#define gmrread		nodev
#define gmrwrite	nodev
#define gmrioctl	nodev
#define gmrintr		nulldev
#define gmrreset	nulldev
#define gmrtout		nulldev
#define gmrattach	nulldev
#endif	NGMR

#include <drv.h>
#if	NDRV > 0
extern	drvopen(), drvclose(), drvread(), drvwrite();
extern	drvioctl(), drvintr(), drvreset(), drvtout();
extern	drvattach();
#else
#define drvopen		nodev
#define drvclose	nodev
#define drvread		nodev
#define drvwrite	nodev
#define drvioctl	nodev
#define drvintr		nulldev
#define drvreset	nulldev
#define drvtout		nulldev
#define drvattach	nulldev
#endif	NDRV

#include <drb.h>
#if	NDRB > 0
extern	drbopen(), drbclose(), drbread(), drbwrite();
extern	drbioctl(), drbintr(), drbreset(), drbtout();
extern  drbattach();
#else
#define drbopen		nodev
#define drbclose	nodev
#define drbread		nodev
#define drbwrite	nodev
#define drbioctl	nodev
#define drbintr		nulldev
#define drbreset	nulldev
#define drbtout		nulldev
#define drbattach	nulldev
#endif	NDRB

/*
 *  User device interface routine switch (index by unit type)
 */
struct drdevsw drdevsw[] =
{
    /*  0 - LP10 interface  */
    cmulpopen,	cmulpclose,	cmulpread,	cmulpwrite,	cmulpioctl,
    cmulpintr,	cmulpreset,	cmulptout,	cmulpattach,

    /*  1 - Grinnell Systems frame buffer  */
    gmropen,	gmrclose,	gmrread,	gmrwrite,	gmrioctl,
    gmrintr,	gmrreset,	gmrtout,	gmrattach,

    /*  2 - DRV11-B interface  */
    drvopen,	drvclose,	drvread,	drvwrite,	drvioctl,
    drvintr,	drvreset,	drvtout,	drvattach,

    /*  3 - generic DR11-B interface  */
    drbopen,	drbclose,	drbread,	drbwrite,	drbioctl,
    drbintr,	drbreset,	drbtout,	drbattach,
};


/*
 *  Device state per unit
 */
struct drstat drstat[NDR] = {0};

/*
 *  UBA information used to map through an invalid address after
 *  device timeouts.
 */
int drnoinfo;

/*
 *  dropen - open DR11 device
 *
 *  Check that unit number is within range, that unit is configured and alive.
 *  Call user device specific open routine based on unit type and increment
 *  the open count for this unit if the open was successful. 
 */

dropen(dev, flag)
{
    register int unit = DRUNIT(dev);
    register struct uba_device *ui;
    register struct drstat *drs;
    int error;

    if (unit >= NDR || (ui=drinfo[unit]) == 0 || ui->ui_alive == 0)
    {
	return(ENXIO);
    }
    error = (*drdevsw[ui->ui_type].drsw_open)(dev, flag);
    if (error)
	return(error);

    drs = &drstat[unit];

    /*
     *  If this is the first open of any DR11, allocate one invalid UNIBUS
     *  map register via the DDP for later use in resetting the unibus
     *  address register after a time out.
     *
     *  As a consistency check against future changes in the UNIBUS
     *  allocation routines, check that we were actually allocated only
     *  1 mapping register via the DDP and no byte offset.
     */
    drs->drs_open++;
    drs->drs_csr = 0;
    drs->drs_state = DRS_IDLE;
    if (drnoinfo == 0)
    {
	drnoinfo = uballoc(ui->ui_mi->um_ubanum, (caddr_t)0, 0, 0);
	if ((drnoinfo&~((0x1ff)<<9)) != (1<<18))
	    panic("drnoinfo");
    }
    return(0);
}



/*
 *  drclose - DR11-B close
 *
 *  Call user device specific close routine based on unit type.
 *  Decrement unit open count and clear all CSR bits when count drops to zero.
 */

drclose(dev, flag)
{
    register int unit = DRUNIT(dev);
    register struct uba_device *ui = drinfo[unit];
    register struct drstat *drs = &drstat[unit];

    (*drdevsw[ui->ui_type].drsw_close)(dev, flag);
    if (--(drs->drs_open) == 0)
	DRADDR->drst = 0;
}



/*
 *  drread - initiate read operation on DR11
 */

drread(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    register int unit = DRUNIT(dev);
    register struct uba_device *ui = drinfo[unit];

    if (drstat[unit].drs_state != DRS_ERROR)
	return ((*drdevsw[ui->ui_type].drsw_read)(dev, uio));
    else
	return(EACCES);
}



/*
 *  drwrite - initiate write operation on DR11
 */
drwrite(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    register int unit = DRUNIT(dev);
    register struct uba_device *ui = drinfo[unit];

    if (drstat[unit].drs_state != DRS_ERROR)
	return((*drdevsw[ui->ui_type].drsw_write)(dev, uio));
    else
	return(EACCES);
}



/*
 *  drphys - set buffer header parameters for DR11 DMA
 *
 *  Restrict DMA transfers to maximum of MAXDRDMA bytes per UNIBUS
 *  transfer (split up by physio()).
 *
 *  Called at completion of user device specific DMA pre-processing
 *  routine via physio() after buffer header has been assigned and
 *  prior to passing it to the device strategy routine.
 */

drphys(bp)
register struct buf *bp;
{
    if (bp->b_bcount > MAXDRDMA)
	bp->b_bcount = MAXDRDMA;
}

/*
 *  drioctl - DR11-B ioctl call
 *
 *  Call user device specific ioctl routine based on unit type.
 *  Perform (or complete) the generic DR11 ioctl calls:
 *
 *  DRIOCGETR  - return register values
 *  DRIOCSSTR  - set subset of status register bits
 *  DRIOCSDBR  - set data buffer register
 *  DRIOCENBS  - enable/disable signal on interrupt
 *  DRIOCASYNC - enable/disable asynchronous I/O 
 */

/* ARGSUSED */
drioctl(dev, cmd, addr, flag)
caddr_t addr;
dev_t dev;
{
    register int unit = DRUNIT(dev);
    register struct uba_device *ui = drinfo[unit];
    register struct drstat *drs = &drstat[unit];
    register struct drdevice *draddr = DRADDR;
    int error;

    error = (*drdevsw[ui->ui_type].drsw_ioctl)(dev, cmd, addr, flag);
    if (error >= 0)
	return(error);

    switch (cmd)
    {
	/*
	 *  Return register status
	 */
	case DRIOCGETR:
	{
	    struct drreg *drp = (struct drreg *)addr;
	    int ipl;

	    drwaitbusy(unit, PZERO+1);
	    drp->drr_wc = draddr->drwc;
	    drp->drr_ba = draddr->drba;
	    drp->drr_st = draddr->drst;
	    drp->drr_db = draddr->drdb;
	    if (ui->ui_flags&DR11W)
	    {
		ipl = spl_dr(ui);
		draddr->drst = DRCSR_ERR | drs->drs_csr;
		drp->drr_er = draddr->drer;
		draddr->drst = drs->drs_csr;
		splx(ipl);
	    }
	    else
		drp->drr_er = 0;
	    break;
	}

	/*
	 *  Set status register
  	 */
	case DRIOCSSTR:
	{
	    u_short csr = *((u_short *)addr);

	    drwaitbusy(unit, PZERO+1);
	    drs->drs_csr = (drs->drs_csr&~DRCSR_FUNC) | (csr&DRCSR_FUNC);
	    draddr->drst = drs->drs_csr;
	    break;
	}

	/*
	 *  Set data buffer register
  	 */
	case DRIOCSDBR:
	{
	    u_short dbr = *((u_short *)addr);

	    drwaitbusy(unit, PZERO+1);
	    draddr->drdb = dbr;
	    break;
	}

	/*
	 *  Enable signal N on unsolicited interrupt.
	 *  Disable signal on unsolicited interrupt if N is 0.
	 *  If signal is enabled, set IE bit in CSR so that an
	 *  interrupt may occur.
	 */
	case DRIOCENBS:
	{
	    u_int n = *((u_int *)addr);
	    int ipl;

	    if (n < NSIG)
	    {
		drwaitbusy(unit, PZERO+1);
		drs->drs_sigp = u.u_procp;
		drs->drs_pid  = u.u_procp->p_pid;
		ipl = spl_dr(ui);
		if (drs->drs_sign = n)		/* This must be set last */
		    drs->drs_csr |= DRCSR_IE;	/* enabled */
		else
		    drs->drs_csr &= ~(DRCSR_IE);/* disabled */
		draddr->drst = drs->drs_csr;
		if ((ui->ui_flags&DR11B) &&
		   (draddr->drst&(DRCSR_RDY|DRCSR_IE)) == (DRCSR_RDY|DRCSR_IE))
		    drs->drs_state = DRS_IE;
		splx(ipl);
	    }
	    else
		return(EINVAL);
	    break;
	}

	/*
	 *  Enable/disable asynchronous I/O on device
	 */
	case DRIOCASYNC:
	    break;

	default:
	    return(EINVAL);
    }
    return(0);
}

/*
 *  drstrategy - DR11 I/O strategy routine
 */

drstrategy(bp)
struct buf *bp;
{
    register int unit = DRUNIT(bp->b_dev);
    register struct uba_ctlr *um = &drctlr[unit];
    register struct buf *dp = &(drstat[unit].drs_tab);
    register int ipl;

    /*
     *  Put request at end of queue using the canonical queuing algorithm.
     *  The device queue header, dp, is linked onto the end of the
     *  controller active device queue via the b_actf and b_actl pointers
     *  of the controller queue header and the b_forw pointer in each
     *  device queue header.  The buffer, bp, is linked onto the end of
     *  the device queue via the b_actf and b_actl pointers of the device
     *  queue header and the av_forw pointer in each buffer.
     *
     *  This queue of queues scheme must be employed here because this is
     *  the organization required by ubago() if the I/O must block awaiting
     *  UNIBUS resources.  The controller queue will never have more than 1
     *  device header enqueued since each device is its own controller.  Most
     *  device queues will have no more than 1 buffer header enqueued unless
     *  asynchronous I/O is being used.
     */
    bp->av_forw = NULL;			/* last buffer in device queue */
    ipl = spl_dr(drinfo[unit]);
    if (dp->b_actf == NULL)
    {					/* empty device queue: */
	dp->b_actf = bp;		/* buffer to front of device queue */
	dp->b_forw = NULL;		/* last device in controller queue */
	if (um->um_tab.b_actf == NULL)
	    um->um_tab.b_actf = dp;	/* device to front of controller queue */
	else
	    um->um_tab.b_actl->b_forw = dp; /* device to end of controller q */
	um->um_tab.b_actl = dp;		/* new end of controller queue */
    }
    else				/* non-empty device queue: */ 
	dp->b_actl->av_forw = bp;	/* buffer to end of device queue */
    dp->b_actl = bp;			/* new end of device queue */
    if (um->um_tab.b_active == 0)
	drstart(um);
    splx(ipl);
}

/*
 *  drstart - start I/O operation on DR11
 */

drstart(um)
register struct uba_ctlr *um;
{
    int unit;
    register struct buf *bp, *dp;
    register struct uba_device *ui;

loop:
    /*
     *  Get current device queue header from controller queue.
     *  If the queue is empty, there is nothing to do.
     */
    if ((dp = um->um_tab.b_actf) == NULL)
	return;
    /*
     *  Get next buffer header from this device queue.
     *  If the queue has been exhausted, advance to the next
     *  device queue header in the controller queue and try again
     *  (there actually will never be another device queue header
     *  since there is but one per DR11 device but this is the
     *  canonical algorithm for this queue structure).
     */
    if ((bp = dp->b_actf) == NULL)
    {
	um->um_tab.b_actf = dp->b_forw;
	goto loop;
    }
    um->um_tab.b_active++;
    unit = DRUNIT(bp->b_dev);
    ui = drinfo[unit];
    um->um_cmd = dr_com(bp);
    DRADDR->drwc = -((bp->b_bcount+1)/sizeof (short));
    (void)ubago(ui);
}



/*
 *  drgo - UBA resources allocated - start the DR11
 *
 *  Set the bus address register from the bits 0-15 of the allocated
 *  UNIBUS resources.  Set a timeout based on the length of the
 *  transfer.  Set up the CSR with extended memory address bits taken
 *  from bits 16-17 of the allocated unibus resources, function bits 
 *  as supplied in um_cmd (from drstart()) and interrupt enable.
 *  Finally set GO in a separate step so that function bits will have
 *  had a chance to settle down.
 *
 *  Avoid read/modify/write access to the CSR since this may give
 *  unexpected access to the EIR for a DR11-W.
 */

drgo(um)
register struct uba_ctlr *um;
{
    register struct drdevice *draddr = (struct drdevice *)um->um_addr;
    register struct uba_device *ui = drinfo[um->um_ctlr];
    register struct drstat *drs = &drstat[ui->ui_unit];
    register struct buf *bp = um->um_tab.b_actf->b_actf;
    extern drtimeout();

    draddr->drba = um->um_ubinfo;
    timeout(drtimeout, (caddr_t)um->um_ctlr, (int)dr_tout(bp)*60);
    um->um_cmd = um->um_cmd | ((um->um_ubinfo>>12)&DRCSR_XMEM) | DRCSR_IE;
    drs->drs_csr = um->um_cmd;
    draddr->drst = um->um_cmd;
    draddr->drst = um->um_cmd | DRCSR_GO;
}

/*
 *  drdone - clean up after I/O completion
 *
 *  This sequence is used after an interrupt or timeout to clean
 *  up the current I/O operation and possibly begin the next.
 */

#define drdone(um, dp, bp)						\
{									\
    (um)->um_tab.b_active = 0;						\
    (um)->um_tab.b_actf = (dp)->b_forw;					\
    (dp)->b_active = 0;							\
    (dp)->b_actf = (bp)->av_forw;					\
    iodone(bp);								\
    ubadone(um);							\
    drstart(um);							\
}



/*
 *  drtimeout - time out overdue I/O completion 
 *
 *  Called at clock interrupt time when an I/O operation has failed
 *  to complete after the specified number of clock ticks.
 *
 *  Print timeout error message on console, mark I/O as timed-out
 *  and begin next.
 *
 *  Also set the device registers to as harmless a state as possible in
 *  case the user device tries anything funny after we have decided to time
 *  it out.  This means a word count of only 1, and a UNIBUS address
 *  mapped through an invalid mapping register.  There is a race
 *  condition when setting the extended memory bits and then remaining
 *  bits of the UNIBUS address since they are in separate registers.
 *  This will only matter if the current operation was not in the same
 *  quarter of the UNIBUS address space as the invalid address and the
 *  device tries to start transferring between these two instructions.
 *  I refuse to worry about it.
 */

drtimeout(unit)
{
    register struct uba_ctlr *um = &drctlr[unit];
    register struct uba_device *ui = drinfo[unit];
    register struct drstat *drs = &drstat[unit];
    register struct buf *dp, *bp;
    int ipl;

    ipl = spl_dr(ui);
    if ((dp = um->um_tab.b_actf) == NULL)
    {
	printf("dr%d: spurious tout\n", unit);
	splx(ipl);
	return;
    }
    printf("dr%d: tout csr=%b wc=%o ba=%o\n",
	    unit, DRADDR->drst, DRCSR_BITS,
	    (u_short)DRADDR->drwc, (u_short)DRADDR->drba);
    drs->drs_csr = (um->um_cmd&~DRCSR_XMEM) | ((drnoinfo>>12)&DRCSR_XMEM);
    DRADDR->drwc = -1;
    DRADDR->drst = drs->drs_csr;
    DRADDR->drba = drnoinfo;
    bp = dp->b_actf;
    bp->b_flags |= B_ERROR;
    bp->b_error = ENXIO;
    (*drdevsw[ui->ui_type].drsw_tout)(unit);
    drdone(um, dp, bp);
    splx(ipl);
}




/*
 *  drintr - interrupt received from DR11
 */

drintr(dr)
{
    register struct uba_ctlr *um = &drctlr[dr];
    register struct uba_device *ui = drinfo[dr];
    register struct drstat *drs = &drstat[dr];
    register struct drdevice *draddr = DRADDR;
    register struct buf *bp;
    register struct buf *dp;
    int unit;
    int com;

    /*
     *  Interrupt with no I/O in progress.
     *
     *  If ATTN without NXM, then the user device is initiating an
     *  interrupt.  Call the user device specific interrupt
     *  routine which will return non-zero if the interrupt has been
     *  handled within that routine.  Otherwise send a signal to the
     *  user process if requested.  Always turn off IE after such
     *  an ATTN interrupt to prevent continuous interrupts.
     *
     *  If ATTN was not asserted, then the interrupt was caused by
     *  either the completion of an I/O operation or an error.  If
     *  there is currently no I/O in progress, then we got a
     *  spurious interrupt of some sort.  The DR11-B apparently
     *  generates an interrupt if IE is set while RDY is asserted,
     *  so ignore the first spurious interrupt after setting IE
     *  simultaneously with RDY.
     */
    if ((dp = um->um_tab.b_actf) == NULL)
    {
	if ((draddr->drst&(DRCSR_ATTN|DRCSR_NXM)) == DRCSR_ATTN) 
	{
	    if ((*drdevsw[ui->ui_type].drsw_intr)(dr) == 0)
		if (drs->drs_sign)
		{
		    if (drs->drs_sigp->p_pid == drs->drs_pid)
			psignal(drs->drs_sigp, (int)drs->drs_sign);
		    drs->drs_sign = 0;
		}
    clear:
	    drs->drs_csr &= ~DRCSR_IE;
	    draddr->drst = drs->drs_csr;
	    return;
	}
	if (drs->drs_state == DRS_IE)
	{
	    printf("dr%d: IE intr\n", dr);
	    drs->drs_state = DRS_IDLE;
	    return;
	}
	else
	{
	    printf("dr%d: spurious intr csr=%b\n", dr,
		   draddr->drst, DRCSR_BITS);
	    goto clear;
	}
    }
    /*
     *  Interrupt with I/O in progress.
     *
     *  Cancel the currently pending timeout (the device interrupted).
     *  If ERROR then something went wrong, print an error message on the
     *  console and complete the I/O, otherwise the operation finished
     *  successfully, just complete it.
     */
    bp = dp->b_actf;
    unit = DRUNIT(bp->b_dev);
    untimeout(drtimeout, (caddr_t)unit);
    if (draddr->drst&DRCSR_ERR)
    {
	/*
	 *  Check for DR11-B attempt to cross 32K word boundary.  Reset the
	 *  error indication by clearing the address register, increment the
	 *  extended memory bits and restart the operation (unless we just
	 *  incremented extended memory beyond the 18-bit address space)
	 */
	if ((ui->ui_flags&DR11B) &&
	    draddr->drba == 0 && (draddr->drst&(DRCSR_NXM|DRCSR_ATTN)) == 0)
	{
	    if (com = ((draddr->drst + 020)&DRCSR_XMEM));
	    {
		draddr->drba = 0;
		um->um_cmd &= ~DRCSR_XMEM;
		um->um_cmd |= com;
		drs->drs_csr = um->um_cmd;
		draddr->drst = um->um_cmd | DRCSR_GO;
		return;
	    }
	}
	printf("dr%d: hard error csr=%b wc=%o ba=%o\n",
		unit, draddr->drst, DRCSR_BITS,
	        (u_short)draddr->drwc, (u_short)draddr->drba);
	bp->b_flags |= B_ERROR;
	bp->b_error = EIO;
    }
    bp->b_resid = (-draddr->drwc)<<1;
    drdone(um, dp, bp);
}


    
/*
 *  drwaitbusy - delay while DR11 DMA is in progress
 *
 *  Set the buffer wanted flag for the buffer header at the tail
 *  of the device queue and block at the indicated priority
 *  until the device is no longer performing DMA.  If no DMA is
 *  currently in progress on the device, just return immediately.
 */

drwaitbusy(unit, pri)
{
    register struct drstat *drs = &drstat[unit];
    register struct buf *bp;
    register int ipl;

    ipl = splx((int)drs->drs_ipl);
    while (drs->drs_tab.b_actf != NULL)
    {
	bp = drs->drs_tab.b_actl;
	bp->b_flags |= B_WANTED;
	sleep((caddr_t)bp, pri);
    }
    splx(ipl);
}

/*
 * Reset driver after UBA init.
 */

drreset(uban)
int uban;
{

    register struct uba_device *ui;
    register struct uba_ctlr *um;
    register int unit;

    for (unit=0; unit <NDR; unit++)
    {
	ui = drinfo[unit];
	if (ui == 0 || ui->ui_ubanum != uban || ui->ui_alive == 0)
	    continue;
	printf(" dr%d", unit);
	um = ui->ui_mi;
	untimeout(drtimeout, (caddr_t)unit);
	um->um_tab.b_active = 0;
	if (um->um_ubinfo)
	{
	    printf("<%d>", (um->um_ubinfo>>28)&0xf);
	    um->um_ubinfo = 0;
	}
	(*drdevsw[ui->ui_type].drsw_reset)(ui->ui_unit);
	drstart(um);
    }

}



/*
 *  drprobe() saves the ipl for the currently configuring device here so
 *  that it may be later picked up by drattach() and saved when it has a
 *  handle on the unit structure.
 */

static dripl;



/*
 *  drprobe - determine if device is a DR11
 */

drprobe(reg)
caddr_t	reg;
{
    register int br,cvec;
    
#ifdef	lint
    br=0; cvec=br; br=cvec;
    drintr(0);
#endif

    /*  This works for a DR11-B but fails for DR11-W  */
    ((struct drdevice *)reg)->drst = DRCSR_IE;
    DELAY(50);

    if (cvec == 0x200)
    {
	/*  This seems to be the only way to get a DR11-W to interrupt  */
	/*  (it may work on DR11-B but has never been tested) */
	((struct drdevice *)reg)->drba = 0;
	((struct drdevice *)reg)->drwc = -1;
	((struct drdevice *)reg)->drst = DRCSR_MAINT|DRCSR_CYCLE|DRCSR_IE|DRCSR_GO;
	DELAY(50);
    }
    ((struct drdevice *)reg)->drst = 0;
    dripl = br;
    return(1);
}



/*
 *  drattach - auto-configured device is a DR11
 */

drattach(ui)
register struct uba_device *ui;
{
    register struct uba_ctlr *um = &drctlr[ui->ui_unit];
    register struct drdevice *draddr = DRADDR;

    if (ui->ui_unit >= NDR)
	panic("drattach");

    /*
     *  Initialize artificial controller structure from device
     *  parameters.  The controller structure is needed for
     *  ubago().
     */
    ui->ui_mi = um;
    um->um_driver = ui->ui_driver;
    um->um_alive = 1;
    um->um_ubanum = ui->ui_ubanum;
    um->um_hd = ui->ui_hd;
    um->um_addr = ui->ui_addr;
    um->um_ctlr = ui->ui_unit;

    /* determine DR11-B/DR11-W mode */
    ui->ui_type = ui->ui_flags;
    draddr->drst = DRCSR_ERR;			/* attempt to read EIR */
    if (draddr->drst&DRCSR_GO)			/* got EIR ==> DR11W */
	ui->ui_flags = DR11W;
    else					/* got CSR ==> DR11B */
	ui->ui_flags = DR11B;
    draddr->drst = 0;				/* restore to CSR */

    /*  set interrupt priority saved by drprobe  */
    drstat[ui->ui_unit].drs_ipl = dripl;

    /*  perform any needed user device initialization  */
    (*drdevsw[ui->ui_type].drsw_attach)(ui->ui_unit);
}
#endif
