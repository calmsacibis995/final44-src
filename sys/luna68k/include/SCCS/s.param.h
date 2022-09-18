h51001
s 00060/00000/00162
d D 8.3 95/05/14 21:02:09 mckusick 6 5
c add simple locking primitives
e
s 00002/00002/00160
d D 8.2 95/03/29 20:50:58 mckusick 5 4
c btodb and dbtob need to work with 64-bit numbers (from karels)
e
s 00002/00002/00160
d D 8.1 93/06/10 22:22:20 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00006/00158
d D 7.3 93/01/02 13:38:09 akito 3 2
c sync up to  hp300/include/param.h   7.13
e
s 00011/00010/00153
d D 7.2 92/07/23 16:12:04 fujita 2 1
c update for 4.4BSD-alpha distribution
e
s 00163/00000/00000
d D 7.1 92/06/15 06:28:22 fujita 1 0
c date and time created 92/06/15 06:28:22 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992 OMRON Corporation.
D 4
 * Copyright (c) 1982, 1986, 1990, 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1982, 1986, 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: machparam.h 1.11 89/08/14$
D 3
 * OMRON: $Id: param.h,v 1.3 92/06/14 06:28:28 moti Exp $
E 3
I 3
 * from: hp300/include/param.h	7.13 (Berkeley) 12/27/92
E 3
 *
D 2
 * from: hp300/include/param.h	7.8 (Berkeley) 6/28/91
E 2
I 2
D 3
 * from: hp300/include/param.h	7.12 (Berkeley) 7/8/92
E 2
 *
E 3
 *	%W% (Berkeley) %G%
 */

/*
 * Machine dependent constants for LUNA taken from:
 * Param.h for HP9000 series 300.
 */
#define	MACHINE "luna68k"
I 6
#define NCPUS 1
E 6

/*
 * Round p (pointer or byte index) up to a correctly-aligned value
 * for all data types (int, long, ...).   The result is u_int and
 * must be cast to any desired pointer type.
 */
#define	ALIGNBYTES	3
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)

#define	NBPG		4096		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		12		/* LOG2(NBPG) */
#define	NPTEPG		(NBPG/(sizeof (struct pte)))

#define NBSEG	       	0x400000	/* bytes/segment */
#define	SEGOFSET	(NBSEG-1)	/* byte offset into segment */
#define	SEGSHIFT	22		/* LOG2(NBSEG) */

#define	KERNBASE	0x00000000	/* start of kernel virtual */
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

#define	DEV_BSIZE	512
#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE	2048
#define	MAXPHYS		(64 * 1024)	/* max raw I/O transfer size */

#define	CLSIZE		1
#define	CLSIZELOG2	0

/* NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE */
#define	SSIZE		1		/* initial stack size/NBPG */
#define	SINCR		1		/* increment of stack/NBPG */

D 3
#define	UPAGES		3		/* pages of u-area */
E 3
I 3
#define	UPAGES		2		/* pages of u-area */
E 3

/*
 * Constants related to network buffer management.
 * MCLBYTES must be no larger than CLBYTES (the software page size), and,
 * on machines that exchange pages of input or output buffers with mbuf
 * clusters (MAPPED_MBUFS), MCLBYTES must also be an integral multiple
 * of the hardware page size.
 */
#define	MSIZE		128		/* size of an mbuf */
D 3
#define	MCLBYTES	1024
#define	MCLSHIFT	10
E 3
I 3
#define	MCLBYTES	2048		/* large enough for ether MTU */
#define	MCLSHIFT	11
E 3
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
#define	NKMEMCLUSTERS	(2048*1024/CLBYTES)
#endif

/* pages ("clicks") (4096 bytes) to disk blocks */
#define	ctod(x)	((x)<<(PGSHIFT-DEV_BSHIFT))
#define	dtoc(x)	((x)>>(PGSHIFT-DEV_BSHIFT))
#define	dtob(x)	((x)<<DEV_BSHIFT)

/* pages to bytes */
#define	ctob(x)	((x)<<PGSHIFT)

/* bytes to pages */
#define	btoc(x)	(((unsigned)(x)+(NBPG-1))>>PGSHIFT)

#define	btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
D 5
	((unsigned)(bytes) >> DEV_BSHIFT)
E 5
I 5
	((bytes) >> DEV_BSHIFT)
E 5
#define	dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
D 5
	((unsigned)(db) << DEV_BSHIFT)
E 5
I 5
	((db) << DEV_BSHIFT)
E 5

/*
 * Map a ``block device block'' to a file system block.
 * This should be device dependent, and should use the bsize
 * field from the disk label.
 * For now though just use DEV_BSIZE.
 */
#define	bdbtofsb(bn)	((bn) / (BLKDEV_IOSIZE/DEV_BSIZE))

/*
 * Mach derived conversion macros
 */
#define luna_round_page(x)	((((unsigned)(x)) + NBPG - 1) & ~(NBPG-1))
#define luna_trunc_page(x)	((unsigned)(x) & ~(NBPG-1))
#define luna_btop(x)		((unsigned)(x) >> PGSHIFT)
#define luna_ptob(x)		((unsigned)(x) << PGSHIFT)

/*
 * spl functions; all but spl0 are done in-line
 */
#include <machine/psl.h>

#define _spl(s) \
({ \
        register int _spl_r; \
\
        asm __volatile ("clrl %0; movew sr,%0; movew %1,sr" : \
                "&=d" (_spl_r) : "di" (s)); \
        _spl_r; \
})

/* spl0 requires checking for software interrupts */
#define spl1()  _spl(PSL_S|PSL_IPL1)
#define spl2()  _spl(PSL_S|PSL_IPL2)
#define spl3()  _spl(PSL_S|PSL_IPL3)
#define spl4()  _spl(PSL_S|PSL_IPL4)
#define spl5()  _spl(PSL_S|PSL_IPL5)
#define spl6()  _spl(PSL_S|PSL_IPL6)
#define spl7()  _spl(PSL_S|PSL_IPL7)

D 2
#define splsoftclock()  spl1()
#define splnet()        spl1()
#define splbio()        spl5()
#define splimp()        spl5()
#define spltty()        spl6()
#define splclock()      spl5()
#define splvm()         spl6()
#define splhigh()       spl7()
#define splsched()      spl7()
E 2
I 2
#define splsoftclock()	spl1()
#define splnet()	spl1()
#define splbio()	spl5()
#define splimp()	spl5()
#define spltty()	spl6()
#define splclock()	spl5()
#define splstatclock()	spl5()
#define splvm()		spl6()
#define splhigh()	spl7()
#define splsched()	spl7()
E 2

/* watch out for side effects */
#define splx(s)         (s & PSL_IPL ? _spl(s) : spl0())

#ifdef KERNEL
#ifndef LOCORE
int	cpuspeed;
#define	DELAY(n)	{ register int N = cpuspeed * (n); while (--N > 0); }
#endif

#else
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif
I 6

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
E 6
E 1
