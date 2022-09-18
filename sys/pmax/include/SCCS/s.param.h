h17188
s 00002/00003/00190
d D 8.5 95/06/02 17:24:23 ralph 15 14
c final changes for pmax 4.4-Lite II release
e
s 00000/00000/00193
d D 8.4 95/06/02 17:20:54 ralph 14 13
c final changes for pmax 4.4-Lite II release
e
s 00060/00000/00133
d D 8.3 95/05/14 21:03:01 mckusick 13 12
c add simple locking primitives
e
s 00002/00002/00131
d D 8.2 95/03/29 20:51:24 mckusick 12 11
c btodb and dbtob need to work with 64-bit numbers (from karels)
e
s 00002/00002/00131
d D 8.1 93/06/10 23:02:23 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00128
d D 7.10 93/05/09 18:02:41 ralph 10 9
c new improved pmap changes
e
s 00000/00001/00129
d D 7.9 93/02/04 19:37:03 ralph 9 8
c removed COFF since a.out is used now
e
s 00008/00018/00122
d D 7.8 92/11/15 16:06:56 ralph 8 7
c updates from Rick Macklem for maxine.
e
s 00001/00001/00139
d D 7.7 92/11/04 08:12:24 bostic 7 6
c GCC (and DEC?) align 64 bit values on an eight byte boundary
e
s 00002/00000/00138
d D 7.6 92/07/27 21:34:13 ralph 6 5
c added splstatclock
e
s 00001/00001/00137
d D 7.5 92/05/28 13:59:00 mckusick 5 4
c improve the hashing (from Macklem)
e
s 00002/00001/00136
d D 7.4 92/05/26 17:05:46 bostic 4 3
c add ALIGNBYTES constant
e
s 00007/00000/00130
d D 7.3 92/03/14 13:55:35 ralph 3 2
c added ALIGN macro
e
s 00016/00000/00114
d D 7.2 92/02/29 15:08:02 ralph 2 1
c added support for DS5000
e
s 00114/00000/00000
d D 7.1 92/01/07 20:35:49 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 11
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: machparam.h 1.11 89/08/14$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Machine dependent constants for DEC Station 3100.
 */
#define	MACHINE	"mips"
I 13
#define NCPUS 1
E 13
D 9
#define COFF
E 9

I 3
/*
 * Round p (pointer or byte index) up to a correctly-aligned value for all
 * data types (int, long, ...).   The result is u_int and must be cast to
 * any desired pointer type.
 */
D 4
#define	ALIGN(p)	(((u_int)(p) + 3) &~ 3)
E 4
I 4
D 7
#define	ALIGNBYTES	3
E 7
I 7
#define	ALIGNBYTES	7
E 7
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)
E 4

E 3
#define	NBPG		4096		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		12		/* LOG2(NBPG) */
#define	NPTEPG		(NBPG/4)

I 10
#define NBSEG		0x400000	/* bytes/segment */
#define	SEGOFSET	(NBSEG-1)	/* byte offset into segment */
#define	SEGSHIFT	22		/* LOG2(NBSEG) */

E 10
#define	KERNBASE	0x80000000	/* start of kernel virtual */
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

#define	DEV_BSIZE	512
#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE	2048
D 10
#define	MAXPHYS		(24 * 1024)	/* max raw I/O transfer size */
E 10
I 10
#define	MAXPHYS		(64 * 1024)	/* max raw I/O transfer size */
E 10

#define	CLSIZE		1
#define	CLSIZELOG2	0

/* NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE */
#define	SSIZE		1		/* initial stack size/NBPG */
#define	SINCR		1		/* increment of stack/NBPG */

#define	UPAGES		2		/* pages of u-area */
D 5
#define	UADDR		0xffffc000	/* address of u */
E 5
I 5
#define	UADDR		0xffffd000	/* address of u */
E 5
#define	UVPN		(UADDR>>PGSHIFT)/* virtual page number of u */
#define	KERNELSTACK	(UADDR+UPAGES*NBPG)	/* top of kernel stack */

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
#define	NKMEMCLUSTERS	(512*1024/CLBYTES)
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
D 12
	((unsigned)(bytes) >> DEV_BSHIFT)
E 12
I 12
	((bytes) >> DEV_BSHIFT)
E 12
#define	dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
D 12
	((unsigned)(db) << DEV_BSHIFT)
E 12
I 12
	((db) << DEV_BSHIFT)
E 12

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
#define pmax_round_page(x)	((((unsigned)(x)) + NBPG - 1) & ~(NBPG-1))
#define pmax_trunc_page(x)	((unsigned)(x) & ~(NBPG-1))
#define pmax_btop(x)		((unsigned)(x) >> PGSHIFT)
#define pmax_ptob(x)		((unsigned)(x) << PGSHIFT)

I 2
D 8
#ifdef DS3100
#define splnet()        Mach_spl1()
#define splbio()        Mach_spl0()
#define splimp()        Mach_spl1()
#define spltty()        Mach_spl2()
#define splclock()      Mach_spl3()
I 6
#define splstatclock()  Mach_spl3()
E 6
#endif /* DS3100 */

#ifdef DS5000
#define splnet()        Mach_spl0()
#define splbio()        Mach_spl0()
#define splimp()        Mach_spl0()
#define spltty()        Mach_spl0()
#define splclock()      Mach_spl1()
I 6
#define splstatclock()  Mach_spl1()
E 6
#endif /* DS5000 */

E 8
E 2
D 15
#ifdef KERNEL
E 15
#ifndef LOCORE
I 15
#ifdef KERNEL
E 15
I 8
extern int (*Mach_splnet)(), (*Mach_splbio)(), (*Mach_splimp)(),
	   (*Mach_spltty)(), (*Mach_splclock)(), (*Mach_splstatclock)();
#define	splnet()	((*Mach_splnet)())
#define	splbio()	((*Mach_splbio)())
#define	splimp()	((*Mach_splimp)())
#define	spltty()	((*Mach_spltty)())
#define	splclock()	((*Mach_splclock)())
#define	splstatclock()	((*Mach_splstatclock)())
E 8
extern	int cpuspeed;
#define	DELAY(n)	{ register int N = cpuspeed * (n); while (--N > 0); }
D 15
#endif

E 15
#else /* !KERNEL */
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif /* !KERNEL */
I 13

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
I 15
#endif /* LOCORE */
E 15
E 13
E 1
