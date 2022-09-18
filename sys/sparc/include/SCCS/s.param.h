h29161
s 00060/00000/00115
d D 8.3 95/05/14 21:03:25 mckusick 8 7
c add simple locking primitives
e
s 00002/00002/00113
d D 8.2 95/03/29 20:52:42 mckusick 7 6
c btodb and dbtob need to work with 64-bit numbers (from karels)
e
s 00002/00002/00113
d D 8.1 93/06/11 15:12:14 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/00114
d D 7.5 93/05/03 02:46:49 torek 5 4
c revert to RCS 1.13 (rm cpuspeed)
e
s 00004/00003/00112
d D 7.4 93/04/20 18:48:21 torek 4 3
c spelling; increase NKMEMCLUSTERS to 6 MB; add cpuspeed (under protest)
e
s 00001/00001/00114
d D 7.3 92/10/11 12:42:14 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00110
d D 7.2 92/07/21 16:41:32 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00110/00000/00000
d D 7.1 92/07/13 00:43:02 torek 1 0
c date and time created 92/07/13 00:43:02 by torek
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: param.h,v 1.11 92/06/24 08:52:05 torek Exp $ (LBL)
E 4
I 4
D 5
 * from: $Header: param.h,v 1.14 93/04/07 01:34:00 torek Exp $ (LBL)
E 5
I 5
 * from: $Header: param.h,v 1.13 92/11/26 02:04:38 torek Exp $ (LBL)
E 5
E 4
 */

/*
 * Machine dependent constants for Sun-4c (SPARCstation)
 */
#define	MACHINE	"sparc"
I 8
#define NCPUS 1
E 8

#ifdef KERNEL				/* XXX */
D 3
#include "machine/cpu.h"		/* XXX */
E 3
I 3
#include <machine/cpu.h>		/* XXX */
E 3
#endif					/* XXX */

/*
 * Round p (pointer or byte index) up to a correctly-aligned value for
 * the machine's strictest data type.  The result is u_int and must be
 * cast to any desired pointer type.
 */
#define	ALIGNBYTES	7
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) & ~ALIGNBYTES)

#define	NBPG		4096		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		12		/* log2(NBPG) */

#define	KERNBASE	0xf8000000	/* start of kernel virtual space */
#define	KERNTEXTOFF	0xf8004000	/* start of kernel text */
#define	BTOPKERNBASE	((u_long)KERNBASE >> PG_SHIFT)

#define	DEV_BSIZE	512
#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define	BLKDEV_IOSIZE	2048
#define	MAXPHYS		(64 * 1024)

#define	CLSIZE		1
#define	CLSIZELOG2	0

/* NOTE: SSIZE and UPAGES must be multiples of CLSIZE */
#define	SSIZE		1		/* initial stack size/NBPG */
#define	UPAGES		2		/* pages of u-area */

/*
 * Constants related to network buffer management.
 * MCLBYTES must be no larger than CLBYTES (the software page size), and,
 * on machines that exchange pages of input or output buffers with mbuf
 * clusters (MAPPED_MBUFS), MCLBYTES must also be an integral multiple
 * of the hardware page size.
 */
#define	MSIZE		128		/* size of an mbuf */
#define	MCLBYTES	2048		/* enough for whole Ethernet packet */
#define	MCLSHIFT	11		/* log2(MCLBYTES) */
#define	MCLOFSET	(MCLBYTES - 1)

#ifndef NMBCLUSTERS
#ifdef GATEWAY
#define	NMBCLUSTERS	512		/* map size, max cluster allocation */
#else
#define	NMBCLUSTERS	256		/* map size, max cluster allocation */
#endif
#endif

/*
 * Size of kernel malloc arena in CLBYTES-sized logical pages.
 */
#ifndef	NKMEMCLUSTERS
D 4
#define	NKMEMCLUSTERS	(3 * 1024 * 1024 / CLBYTES)
E 4
I 4
#define	NKMEMCLUSTERS	(6 * 1024 * 1024 / CLBYTES)
E 4
#endif

/* pages ("clicks") (4096 bytes) to disk blocks */
#define	ctod(x)	((x) << (PGSHIFT - DEV_BSHIFT))
#define	dtoc(x)	((x) >> (PGSHIFT - DEV_BSHIFT))
#define	dtob(x)	((x) << DEV_BSHIFT)

/* pages to bytes */
#define	ctob(x)	((x) << PGSHIFT)

/* bytes to pages */
#define	btoc(x)	(((unsigned)(x) + PGOFSET) >> PGSHIFT)

#define	btodb(bytes)		/* calculates (bytes / DEV_BSIZE) */ \
D 7
	((unsigned)(bytes) >> DEV_BSHIFT)
E 7
I 7
	((bytes) >> DEV_BSHIFT)
E 7
#define	dbtob(db)		/* calculates (db * DEV_BSIZE) */ \
D 7
	((unsigned)(db) << DEV_BSHIFT)
E 7
I 7
	((db) << DEV_BSHIFT)
E 7

/*
 * Map a ``block device block'' to a file system block.
 * This should be device dependent, and should use the bsize
 * field from the disk label.
 * For now though just use DEV_BSIZE.
 */
#define	bdbtofsb(bn)	((bn) / (BLKDEV_IOSIZE / DEV_BSIZE))

#ifdef KERNEL
#ifndef LOCORE
I 4
D 5
int cpuspeed;		/* XXX for sysctl(hw.cpuspeed) only; should remove */
E 5
E 4
#define	DELAY(n)	delay(n)
#endif
#else
#define	DELAY(n)	{ register volatile int N = (n); while (--N > 0); }
#endif
I 8

#ifndef _SIMPLELOCK_H_
#define _SIMPLELOCK_H_
/*
 * A simple spin lock.
 *
 * This structure only sets one bit of data, but is sized based on the
 * minimum word size that can be operated on by the hardware test-and-set
 * instruction. It is only needed for multiprocessors, as uniprocessors
 * will always run to completion or a sleep. It is an error to hold one
 * of these locks while a process is sleeping.
 */
struct simplelock {
	int	lock_data;
};

#if !defined(DEBUG) && NCPUS > 1
/*
 * The simple-lock routines are the primitives out of which the lock
 * package is built. The machine-dependent code must implement an
 * atomic test_and_set operation that indivisibly sets the simple lock
 * to non-zero and returns its old value. It also assumes that the
 * setting of the lock to zero below is indivisible. Simple locks may
 * only be used for exclusive locks.
 */
static __inline void
simple_lock_init(lkp)
	struct simplelock *lkp;
{

	lkp->lock_data = 0;
}

static __inline void
simple_lock(lkp)
	__volatile struct simplelock *lkp;
{

	while (test_and_set(&lkp->lock_data))
		continue;
}

static __inline int
simple_lock_try(lkp)
	__volatile struct simplelock *lkp;
{

	return (!test_and_set(&lkp->lock_data))
}

static __inline void
simple_unlock(lkp)
	__volatile struct simplelock *lkp;
{

	lkp->lock_data = 0;
}
#endif /* NCPUS > 1 */
#endif /* !_SIMPLELOCK_H_ */
E 8
E 1
