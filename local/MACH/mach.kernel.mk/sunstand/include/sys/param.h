/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	param.h,v $
 * Revision 2.2  89/07/12  00:13:24  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)param.h 2.25 88/02/08 SMI; from UCB 4.35 83/06/10	*/

#ifndef	_PARAM_
#define	_PARAM_

/*
 * Machine type dependent parameters.
 */
#include <machine/param.h>

#define	NPTEPG		(NBPG/(sizeof (struct pte)))

/*
 * Machine-independent constants
 */
#define	NMOUNT	40		/* est. of # mountable fs for quota calc */
#define	MSWAPX	15		/* pseudo mount table index for swapdev */
#define	MAXUPRC	25		/* max processes per user */
#define	NOFILE	64		/* max open files per process */
#define	MAXPID	30000		/* max process id */
#define	MAXUID	60000		/* max user id */
#define	MAXLINK	32767		/* max links */
#define	CANBSIZ	256		/* max size of typewriter line */
#ifndef KERNEL
#define	HZ	60		/* ticks/second according to syscalls that return values in ticks */
#endif
#define	NCARGS	0x100000	/* (absolute) max # characters in exec arglist */
#define	NGROUPS	16		/* max number groups */

#define	NOGROUP	-1		/* marker for empty group set member */

#ifdef KERNEL
/*
 * Priorities
 */
#define	PMASK	0177
#define	PCATCH	0400		/* return if sleep interrupted, don't longjmp */
#define	PSWP	0
#define	PINOD	10
#define	PRIBIO	20
#define	PRIUBA	24
#define	PZERO	25
#define	PPIPE	26
#define	PVFS	27
#define	PWAIT	30
#define	PLOCK	35
#define	PSLEP	40

#ifdef VPIX
#define PV86	41
#endif

#define	PUSER	50

#define	NZERO	20
#endif /*KERNEL*/

/*
 * Signals
 */
#include <sys/signal.h>

#define	ISSIG(p, flag) \
	((p)->p_sig && ((p)->p_flag&STRC || \
	 ((p)->p_sig &~ ((p)->p_sigignore | (p)->p_sigmask))) && issig(flag))

#define	NBPW	sizeof (int)	/* number of bytes in an integer */

#define	NULL	0
#define	CMASK	0		/* default mask for file creation */
#define	NODEV	(dev_t)(-1)

#ifndef INTRLVE
/* macros replacing interleaving functions */
#define	dkblock(bp)	((bp)->b_blkno)
#define	dkunit(bp)	(minor((bp)->b_dev) >> 3)
#endif

#define	CBSIZE	28		/* number of chars in a clist block */
#define	CROUND	0x1F		/* clist rounding; sizeof (int *) + CBSIZE-1 */

#if !defined(LOCORE) || !defined(KERNEL)
#include <sys/types.h>
#endif

/*
 * File system parameters and macros.
 *
 * The file system is made out of blocks of at most MAXBSIZE units,
 * with smaller units (fragments) only in the last direct block.
 * MAXBSIZE primarily determines the size of buffers in the buffer
 * pool. It may be made larger without any effect on existing
 * file systems; however making it smaller make make some file
 * systems unmountable.
 *
 * Note that the blocked devices are assumed to have DEV_BSIZE
 * "sectors" and that fragments must be some multiple of this size.
 */
#define	MAXBSIZE	8192
#define	DEV_BSIZE	512
#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define	MAXFRAG 	8

#define	btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
	((unsigned)(bytes) >> DEV_BSHIFT)
#define	dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
	((unsigned)(db) << DEV_BSHIFT)

/*
 * Map a ``block device block'' to a file system block.
 * XXX - this is currently only being used for tape drives.
 */
#define	BLKDEV_IOSIZE	2048
#define	bdbtofsb(bn)	((bn) / (BLKDEV_IOSIZE/DEV_BSIZE))

/*
 * MAXPATHLEN defines the longest permissable path length,
 * including the terminating null, after expanding symbolic links.
 * MAXSYMLINKS defines the maximum number of symbolic links
 * that may be expanded in a path name. It should be set high
 * enough to allow all legitimate uses, but halt infinite loops
 * reasonably quickly.
 */
#define	MAXPATHLEN	1024
#define	MAXSYMLINKS	20

/*
 * bit map related macros
 */
#define	setbit(a,i)	((a)[(i)/NBBY] |= 1<<((i)%NBBY))
#define	clrbit(a,i)	((a)[(i)/NBBY] &= ~(1<<((i)%NBBY)))
#define	isset(a,i)	((a)[(i)/NBBY] & (1<<((i)%NBBY)))
#define	isclr(a,i)	(((a)[(i)/NBBY] & (1<<((i)%NBBY))) == 0)

/*
 * Macros for fast min/max.
 */
#ifndef MIN
#define	MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define	MAX(a,b) (((a)>(b))?(a):(b))
#endif

/*
 * Macros for counting and rounding.
 */
#ifdef sun386
#define howmany(x, y)   ((((u_int)(x))+(((u_int)(y))-1))/((u_int)(y)))
#define roundup(x, y)   ((((u_int)(x)+((u_int)(y)-1))/(u_int)(y))*(u_int)(y))
#else
#define	howmany(x, y)	(((x)+((y)-1))/(y))
#define	roundup(x, y)	((((x)+((y)-1))/(y))*(y))
#endif

/*
 * Scale factor for scaled integers used to count
 * %cpu time and load averages.
 */
#define	FSHIFT	8		/* bits to right of fixed binary point */
#define	FSCALE	(1<<FSHIFT)

/*
 * Maximum size of hostname recognized and stored in the kernel.
 */
#define	MAXHOSTNAMELEN  64

#endif	_PARAM_
