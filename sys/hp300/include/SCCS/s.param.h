h25578
s 00003/00000/00232
d D 8.4 95/05/13 13:54:37 mckusick 18 17
c need to protect simplelock from multiple includes
e
s 00057/00000/00175
d D 8.3 95/05/13 11:26:04 mckusick 17 15
c add simple locking primitives
e
s 00057/00000/00175
d R 8.3 95/05/11 14:46:28 mckusick 16 15
c add simple locking primatives
e
s 00002/00002/00173
d D 8.2 95/03/29 20:49:19 mckusick 15 14
c btodb and dbtob need to work with 64-bit numbers (from karels)
e
s 00002/00002/00173
d D 8.1 93/06/10 21:44:53 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00007/00166
d D 7.13 92/12/27 09:26:27 hibler 13 12
c UPAGES now 2, MCLBYTES now 2048, new consts for disklabels
e
s 00010/00009/00163
d D 7.12 92/07/08 01:02:41 mckusick 12 11
c whitespace hacking; add splstatclock
e
s 00009/00010/00163
d D 7.11 92/06/05 15:29:22 hibler 11 10
c merge latest Utah hp300 code including 68040 support
e
s 00002/00001/00171
d D 7.10 92/05/26 17:04:54 bostic 10 9
c add ALIGNBYTES constant
e
s 00004/00004/00168
d D 7.9 92/02/19 17:45:19 bostic 9 8
c rip away illusion of portability in ALIGN
e
s 00001/00001/00171
d D 7.8 91/06/28 16:57:45 karels 8 7
c more kmem
e
s 00007/00000/00165
d D 7.7 91/06/26 10:51:05 sklower 7 6
c add ALIGN macro
e
s 00002/00002/00163
d D 7.6 91/06/08 16:43:25 bostic 6 5
c don't put anything after the #else or #endif's, unless it's a comment
e
s 00003/00010/00162
d D 7.5 91/05/08 14:19:12 karels 5 4
c rm unused, update
e
s 00037/00006/00135
d D 7.4 91/05/04 19:55:31 karels 4 3
c inline spl's from donn; u. is gone, use p->p_addr
e
s 00000/00006/00141
d D 7.3 90/12/16 16:37:21 bostic 3 2
c kernel reorg
e
s 00012/00000/00135
d D 7.2 90/12/05 19:30:24 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00135/00000/00000
d D 7.1 90/05/08 17:51:18 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 14
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 11
 * from: Utah $Hdr: machparam.h 1.11 89/08/14$
E 11
I 11
D 13
 * from: Utah $Hdr: machparam.h 1.12 91/01/18$
E 13
I 13
 * from: Utah $Hdr: machparam.h 1.16 92/12/20$
E 13
E 11
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Machine dependent constants for HP9000 series 300.
 */
#define	MACHINE "hp300"
I 17
#define NCPUS	1
E 17

I 7
/*
D 9
 * Round p (pointer or byte index) up to a correctly-aligned value
 * for all data types (int, long, ...).   The result is u_int and
 * must be cast to any desired pointer type.
E 9
I 9
 * Round p (pointer or byte index) up to a correctly-aligned value for all
 * data types (int, long, ...).   The result is u_int and must be cast to
 * any desired pointer type.
E 9
 */
D 9
#define	ALIGN(p)	(((u_int)(p) + (sizeof(int) - 1)) &~ (sizeof(int) - 1))
E 9
I 9
D 10
#define	ALIGN(p)	(((u_int)(p) + 3) &~ 3)
E 10
I 10
#define	ALIGNBYTES	3
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)
E 10
E 9

E 7
D 3
#ifndef BYTE_ORDER
#include <machine/endian.h>
#endif

#include <machine/machlimits.h>

E 3
#define	NBPG		4096		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		12		/* LOG2(NBPG) */
#define	NPTEPG		(NBPG/(sizeof (struct pte)))

D 11
#define NBSEG		(1024*NBPG)	/* bytes/segment */
E 11
I 11
#define NBSEG		0x400000	/* bytes/segment */
E 11
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

I 4
/* NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE */
E 4
#define	SSIZE		1		/* initial stack size/NBPG */
#define	SINCR		1		/* increment of stack/NBPG */

D 13
#define	UPAGES		3		/* pages of u-area */
E 13
I 13
#define	UPAGES		2		/* pages of u-area */
E 13

/*
 * Constants related to network buffer management.
 * MCLBYTES must be no larger than CLBYTES (the software page size), and,
 * on machines that exchange pages of input or output buffers with mbuf
 * clusters (MAPPED_MBUFS), MCLBYTES must also be an integral multiple
 * of the hardware page size.
 */
#define	MSIZE		128		/* size of an mbuf */
D 13
#define	MCLBYTES	1024
#define	MCLSHIFT	10
E 13
I 13
#define	MCLBYTES	2048		/* large enough for ether MTU */
#define	MCLSHIFT	11
E 13
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
D 8
#define	NKMEMCLUSTERS	(512*1024/CLBYTES)
E 8
I 8
#define	NKMEMCLUSTERS	(2048*1024/CLBYTES)
E 8
#endif

D 5
/*
 * Some macros for units conversion
 */
/* Core clicks (4096 bytes) to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

/* Core clicks (4096 bytes) to disk blocks */
E 5
I 5
/* pages ("clicks") (4096 bytes) to disk blocks */
E 5
#define	ctod(x)	((x)<<(PGSHIFT-DEV_BSHIFT))
#define	dtoc(x)	((x)>>(PGSHIFT-DEV_BSHIFT))
#define	dtob(x)	((x)<<DEV_BSHIFT)

D 5
/* clicks to bytes */
E 5
I 5
/* pages to bytes */
E 5
#define	ctob(x)	((x)<<PGSHIFT)

D 5
/* bytes to clicks */
E 5
I 5
/* bytes to pages */
E 5
#define	btoc(x)	(((unsigned)(x)+(NBPG-1))>>PGSHIFT)

I 13
#define LABELSECTOR	(1024/DEV_BSIZE)
#define LABELOFFSET	0

E 13
#define	btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
D 15
	((unsigned)(bytes) >> DEV_BSHIFT)
E 15
I 15
	((bytes) >> DEV_BSHIFT)
E 15
#define	dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
D 15
	((unsigned)(db) << DEV_BSHIFT)
E 15
I 15
	((db) << DEV_BSHIFT)
E 15

/*
 * Map a ``block device block'' to a file system block.
D 4
 * This should be device dependent, and will be if we
 * add an entry to cdevsw/bdevsw for that purpose.
E 4
I 4
 * This should be device dependent, and should use the bsize
 * field from the disk label.
E 4
 * For now though just use DEV_BSIZE.
 */
#define	bdbtofsb(bn)	((bn) / (BLKDEV_IOSIZE/DEV_BSIZE))

/*
I 2
 * Mach derived conversion macros
 */
D 11
#define hp300_round_seg(x)	((((unsigned)(x)) + NBSEG - 1) & ~(NBSEG-1))
#define hp300_trunc_seg(x)	((unsigned)(x) & ~(NBSEG-1))
E 11
#define hp300_round_page(x)	((((unsigned)(x)) + NBPG - 1) & ~(NBPG-1))
#define hp300_trunc_page(x)	((unsigned)(x) & ~(NBPG-1))
D 11
#define hp300_btos(x)		((unsigned)(x) >> SEGSHIFT)
#define hp300_stob(x)		((unsigned)(x) << SEGSHIFT)
E 11
#define hp300_btop(x)		((unsigned)(x) >> PGSHIFT)
#define hp300_ptob(x)		((unsigned)(x) << PGSHIFT)

/*
E 2
D 4
 * Macros to decode processor status word.
E 4
I 4
 * spl functions; all but spl0 are done in-line
E 4
 */
D 4
#define	USERMODE(ps)	(((ps) & PSL_S) == 0)
#define	BASEPRI(ps)	(((ps) & PSL_IPL7) == 0)
E 4
I 4
#include <machine/psl.h>
E 4

I 4
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

D 12
#define splsoftclock()  spl1()
#define splnet()        spl1()
#define splbio()        spl5()
#define splimp()        spl5()
#define spltty()        spl5()
#define splclock()      spl6()
#define splvm()         spl6()
#define splhigh()       spl7()
#define splsched()      spl7()
E 12
I 12
#define splsoftclock()	spl1()
#define splnet()	spl1()
#define splbio()	spl5()
#define splimp()	spl5()
#define spltty()	spl5()
#define splclock()	spl6()
#define splstatclock()	spl6()
#define splvm()		spl6()
#define splhigh()	spl7()
#define splsched()	spl7()
E 12

/* watch out for side effects */
#define splx(s)         (s & PSL_IPL ? _spl(s) : spl0())

E 4
#ifdef KERNEL
#ifndef LOCORE
int	cpuspeed;
#define	DELAY(n)	{ register int N = cpuspeed * (n); while (--N > 0); }
#endif
D 11

E 11
D 6
#else KERNEL
E 6
I 6
#else
E 6
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
D 6
#endif KERNEL
E 6
I 6
#endif
E 6

#ifdef HPUXCOMPAT
/*
 * Constants/macros for HPUX multiple mapping of user address space.
 * Pages in the first 256Mb are mapped in at every 256Mb segment.
I 11
D 13
 *
 * XXX broken in new VM XXX
E 13
E 11
 */
#define HPMMMASK	0xF0000000
D 11
#define ISHPMMADDR(v)	\
D 4
    ((u.u_pcb.pcb_flags&PCB_HPUXMMAP) && ((unsigned)(v)&HPMMMASK) != HPMMMASK)
E 4
I 4
    ((curproc->p_addr->u_pcb.pcb_flags&PCB_HPUXMMAP) && ((unsigned)(v)&HPMMMASK) != HPMMMASK)
E 4
#define HPMMBASEADDR(v)	((unsigned)(v) & ~HPMMMASK)
E 11
I 11
#define ISHPMMADDR(v) \
D 13
	((curproc->p_addr->u_pcb.pcb_flags & PCB_HPUXMMAP) && \
E 13
I 13
	((curproc->p_md.md_flags & MDP_HPUXMMAP) && \
	 ((unsigned)(v) & HPMMMASK) && \
E 13
	 ((unsigned)(v) & HPMMMASK) != HPMMMASK)
#define HPMMBASEADDR(v) \
	((unsigned)(v) & ~HPMMMASK)
E 11
#endif
I 17

I 18
#ifndef _SIMPLELOCK_H_
#define _SIMPLELOCK_H_
E 18
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
I 18
#endif /* !_SIMPLELOCK_H_ */
E 18
E 17
E 1
