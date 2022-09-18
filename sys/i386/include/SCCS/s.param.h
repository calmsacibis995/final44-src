h50873
s 00060/00000/00124
d D 8.3 95/05/14 21:01:36 mckusick 15 14
c add simple locking primitives
e
s 00002/00002/00122
d D 8.2 95/03/29 20:50:16 mckusick 14 13
c btodb and dbtob need to work with 64-bit numbers (from karels)
e
s 00002/00002/00122
d D 8.1 93/06/11 15:48:06 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00122
d D 5.11 92/05/26 17:05:16 bostic 12 11
c add ALIGNBYTES constant
e
s 00002/00007/00121
d D 5.10 92/05/20 16:50:07 bostic 11 10
c Delete DELAY macro (now DELAY is in locore.s).
c from Pace Willisson (pace@blitz.com)
e
s 00004/00004/00124
d D 5.9 92/02/19 17:45:51 bostic 10 9
c rip away illusion of portability in ALIGN
e
s 00001/00001/00127
d D 5.8 91/06/28 17:03:40 karels 9 8
c more kmem
e
s 00007/00000/00121
d D 5.7 91/06/26 10:52:06 sklower 8 7
c add align macro
e
s 00002/00002/00119
d D 5.6 91/06/08 16:43:47 bostic 7 6
c don't put anything after the #else or #endif's, unless it's a comment
e
s 00001/00000/00120
d D 5.5 91/04/28 12:03:30 bostic 6 5
c move SSIZE comment from <sys/param.h>
e
s 00012/00000/00108
d D 5.4 91/04/15 17:15:49 william 5 4
c added mach macros
e
s 00001/00001/00107
d D 5.3 91/01/18 14:32:26 william 4 3
c fixed just which copyright notice is included.
e
s 00025/00004/00083
d D 5.2 91/01/15 15:21:46 william 3 2
c trivia, reno changes, and kernel reorg
e
s 00013/00001/00074
d D 5.1 90/04/24 18:52:16 william 2 1
c 1st Berkeley Release
e
s 00075/00000/00000
d D 1.1 90/03/12 15:48:07 bill 1 0
c date and time created 90/03/12 15:48:07 by bill
e
u
U
t
T
I 2
/*-
D 13
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 4
 * %sccs.include.noredist.c%
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
 * Machine dependent constants for Intel 386.
 */

#define MACHINE "i386"
I 15
#define NCPUS 1
E 15

I 8
/*
D 10
 * Round p (pointer or byte index) up to a correctly-aligned value
 * for all data types (int, long, ...).   The result is u_int and
 * must be cast to any desired pointer type.
E 10
I 10
 * Round p (pointer or byte index) up to a correctly-aligned value for all
 * data types (int, long, ...).   The result is u_int and must be cast to
 * any desired pointer type.
E 10
 */
D 10
#define	ALIGN(p)	(((u_int)(p) + (sizeof(int) - 1)) &~ (sizeof(int) - 1))
E 10
I 10
D 12
#define	ALIGN(p)	(((u_int)(p) + 3) &~ 3)
E 12
I 12
#define	ALIGNBYTES	3
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)
E 12
E 10

E 8
D 3
#ifndef BYTE_ORDER
#include <machine/endian.h>
#endif

E 3
#define	NBPG		4096		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		12		/* LOG2(NBPG) */
#define	NPTEPG		(NBPG/(sizeof (struct pte)))

#define NBPDR		(1024*NBPG)	/* bytes/page dir */
#define	PDROFSET	(NBPDR-1)	/* byte offset into page dir */
#define	PDRSHIFT	22		/* LOG2(NBPDR) */

#define	KERNBASE	0xFE000000	/* start of kernel virtual */
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

#define	DEV_BSIZE	512
#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE	2048
#define	MAXPHYS		(64 * 1024)	/* max raw I/O transfer size */

#define	CLSIZE		1
#define	CLSIZELOG2	0

I 6
/* NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE */
E 6
#define	SSIZE	1		/* initial stack size/NBPG */
#define	SINCR	1		/* increment of stack/NBPG */

D 2
#define	UPAGES	3		/* pages of u-area */
E 2
I 2
#define	UPAGES	2		/* pages of u-area */
E 2

I 3
/*
 * Constants related to network buffer management.
 * MCLBYTES must be no larger than CLBYTES (the software page size), and,
 * on machines that exchange pages of input or output buffers with mbuf
 * clusters (MAPPED_MBUFS), MCLBYTES must also be an integral multiple
 * of the hardware page size.
 */
#define	MSIZE		128		/* size of an mbuf */
#define	MCLBYTES	1024
#define	MCLSHIFT	10
#define	MCLOFSET	(MCLBYTES - 1)
#ifndef NMBCLUSTERS
#ifdef GATEWAY
#define	NMBCLUSTERS	512		/* map size, max cluster allocation */
#else
#define	NMBCLUSTERS	256		/* map size, max cluster allocation */
#endif
#endif

/*
 * Size of kernel malloc arena in CLBYTES-sized logical pages
 */ 
#ifndef NKMEMCLUSTERS
D 9
#define	NKMEMCLUSTERS	(512*1024/CLBYTES)
E 9
I 9
#define	NKMEMCLUSTERS	(2048*1024/CLBYTES)
E 9
#endif
E 3
/*
 * Some macros for units conversion
 */
/* Core clicks (4096 bytes) to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

/* Core clicks (4096 bytes) to disk blocks */
#define	ctod(x)	((x)<<(PGSHIFT-DEV_BSHIFT))
#define	dtoc(x)	((x)>>(PGSHIFT-DEV_BSHIFT))
#define	dtob(x)	((x)<<DEV_BSHIFT)

/* clicks to bytes */
#define	ctob(x)	((x)<<PGSHIFT)

/* bytes to clicks */
#define	btoc(x)	(((unsigned)(x)+(NBPG-1))>>PGSHIFT)

#define	btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
D 14
	((unsigned)(bytes) >> DEV_BSHIFT)
E 14
I 14
	((bytes) >> DEV_BSHIFT)
E 14
#define	dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
D 14
	((unsigned)(db) << DEV_BSHIFT)
E 14
I 14
	((db) << DEV_BSHIFT)
E 14

/*
 * Map a ``block device block'' to a file system block.
 * This should be device dependent, and will be if we
 * add an entry to cdevsw/bdevsw for that purpose.
 * For now though just use DEV_BSIZE.
 */
#define	bdbtofsb(bn)	((bn) / (BLKDEV_IOSIZE/DEV_BSIZE))

I 5
/*
 * Mach derived conversion macros
 */
#define i386_round_pdr(x)	((((unsigned)(x)) + NBPDR - 1) & ~(NBPDR-1))
#define i386_trunc_pdr(x)	((unsigned)(x) & ~(NBPDR-1))
#define i386_round_page(x)	((((unsigned)(x)) + NBPG - 1) & ~(NBPG-1))
#define i386_trunc_page(x)	((unsigned)(x) & ~(NBPG-1))
#define i386_btod(x)		((unsigned)(x) >> PDRSHIFT)
#define i386_dtob(x)		((unsigned)(x) << PDRSHIFT)
#define i386_btop(x)		((unsigned)(x) >> PGSHIFT)
#define i386_ptob(x)		((unsigned)(x) << PGSHIFT)

E 5
D 11
#ifdef KERNEL
#ifndef LOCORE
int	cpuspeed;
#endif
#define	DELAY(n)	{ register int N = cpuspeed * (n); while (--N > 0); }

D 7
#else KERNEL
E 7
I 7
#else
E 11
I 11
#ifndef KERNEL
/* DELAY is in locore.s for the kernel */
E 11
E 7
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
D 7
#endif KERNEL
E 7
I 7
#endif
I 15

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
E 15
E 7
E 1
