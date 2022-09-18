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
 * $Log:	ufs_physio.c,v $
 * Revision 2.9  89/03/09  19:33:27  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/02/26  11:29:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.7  89/02/11  04:16:21  mwyoung
 * Relocated from bsd/vm_swp.c
 * 
 * Revision 2.6  89/02/09  04:36:12  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/23  22:10:15  af
 * 	Corrected include file references.
 * 	[89/01/09            af]
 * 	
 * 	Changes for I386: MAXPHYS for EXL 32 * 4096
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  89/01/18  00:46:09  jsb
 * 	Vnode support.
 * 	[89/01/16  15:21:01  jsb]
 * 
 *
 * 16-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Correct IBM-RT SCSI disk conditionals.
 *	[ V5.1(XF19) ]
 *
 * 24-Aug-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Move vsunlock in physio out from under the splbio().  This can cause
 *	a deadlock if someone else has started to do a unwire, has the
 *	vm_page_queue_lock and is now doing a shoot, while we are at spl
 *	and trying to get the vm_page_queue_lock, are cpus_active and
 *	are not taking interrupts.
 *
 * 30-May-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Installed latest fix from IBM to constrain physical disk I/O
 *	length for SCSI drives (this should really be done in a per-
 *	driver routine).
 *	[ V5.1(XF11) ]
 *
 *  7-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Removed unnecessary include of pte.h
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 18-Dec-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.  Carried over change below:
 *
 * 17-Jul-84  Fil Alleva (faa) at Carnegie-Mellon University
 *	NDS:  Added code in physio() to preserve SPHYSIO bit in
 *	users process flags so that the DSC device will work correctly
 *	with other devices.
 *
 * Major changes from Berkeley:
 *	Mach VM is very different... swapping code has been removed.
 */
 
#ifdef	i386
#include <cputypes.h>
#endif	i386

#ifdef	vax
#include <ds.h>
#else	vax
#define NDS	0
#endif	vax
#ifdef	ibmrt
#include <sc.h>
#else	ibmrt
#define NSCC	0
#endif	ibmrt

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)vm_swp.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include <sys/uio.h>

/*
 * Raw I/O. The arguments are
 *	The strategy routine for the device
 *	A buffer, which will always be a special buffer
 *	  header owned exclusively by the device for this purpose
 *	The device number
 *	Read/write flag
 * Essentially all the work is computing physical addresses and
 * validating them.
 * If the user has the proper access privilidges, the process is
 * marked 'delayed unlock' and the pages involved in the I/O are
 * faulted and locked. After the completion of the I/O, the above pages
 * are unlocked.
 */
physio(strat, bp, dev, rw, mincnt, uio)
	int (*strat)(); 
	register struct buf *bp;
	dev_t dev;
	int rw;
	unsigned (*mincnt)();
	struct uio *uio;
{
	register struct iovec *iov;
	register int c;
	char *a;
	int s, error = 0;

nextiov:
	if (uio->uio_iovcnt == 0)
		return (0);
	iov = uio->uio_iov;
	if (useracc(iov->iov_base,(u_int)iov->iov_len,rw==B_READ?B_WRITE:B_READ) == NULL)
		return (EFAULT);
	s = splbio();
	while (bp->b_flags&B_BUSY) {
		bp->b_flags |= B_WANTED;
		sleep((caddr_t)bp, PRIBIO+1);
	}
	splx(s);
	bp->b_error = 0;
	bp->b_proc = u.u_procp;
	bp->b_un.b_addr = iov->iov_base;
	while (iov->iov_len > 0) {
#if	NDS > 0
		int sphysio = (u.u_procp->p_flag&SPHYSIO);
#endif	NDS > 0
		bp->b_flags = B_BUSY | B_PHYS | rw;
		bp->b_dev = dev;
		bp->b_blkno = btodb(uio->uio_offset);
		bp->b_bcount = iov->iov_len;
		(*mincnt)(bp);
		c = bp->b_bcount;
		u.u_procp->p_flag |= SPHYSIO;
		vslock(a = bp->b_un.b_addr, c);
		physstrat(bp, strat, PRIBIO);
		vsunlock(a, c, rw);
#if	NDS > 0
		u.u_procp->p_flag &= (~SPHYSIO | sphysio);
#else	NDS > 0
		u.u_procp->p_flag &= ~SPHYSIO;
#endif	NDS > 0
		(void) splbio();
		if (bp->b_flags&B_WANTED)
			wakeup((caddr_t)bp);
		splx(s);
		c -= bp->b_resid;
		bp->b_un.b_addr += c;
		iov->iov_len -= c;
		uio->uio_resid -= c;
		uio->uio_offset += c;
		/* temp kludge for tape drives */
		if (bp->b_resid || (bp->b_flags&B_ERROR))
			break;
	}
	bp->b_flags &= ~(B_BUSY|B_WANTED|B_PHYS);
	error = geterror(bp);
	/* temp kludge for tape drives */
	if (bp->b_resid || error)
		return (error);
	uio->uio_iov++;
	uio->uio_iovcnt--;
	goto nextiov;
}

#if	NSCC > 0
#define MAXPHYS	(64 * 512)	/* don't increase beyond NDMAXIO */
#else
#define MAXPHYS	(63 * 1024)
#endif

#if	EXL
#undef  MAXPHYS
#define MAXPHYS (32 * 4096)     /* EXL can take 32 pages for dma */
#endif	EXL

unsigned
minphys(bp)
	struct buf *bp;
{

	if (bp->b_bcount > MAXPHYS)
		bp->b_bcount = MAXPHYS;
}
