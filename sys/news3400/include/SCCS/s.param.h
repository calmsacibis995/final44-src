h31961
s 00060/00000/00188
d D 8.3 95/05/14 21:02:39 mckusick 9 8
c add simple locking primitives
e
s 00002/00002/00186
d D 8.2 95/03/29 20:52:02 mckusick 8 7
c btodb and dbtob need to work with 64-bit numbers (from karels)
e
s 00002/00002/00186
d D 8.1 93/06/11 14:58:53 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00183
d D 7.6 93/05/13 19:45:01 utashiro 6 5
c change for new pmap interface.
e
s 00004/00013/00180
d D 7.5 93/03/09 23:48:17 utashiro 5 4
c mips stack must be aligned on 8byte boundary
e
s 00002/00001/00191
d D 7.4 92/12/17 03:24:17 utashiro 4 3
c Added ALIGNBYTES macro
e
s 00002/00000/00190
d D 7.3 92/07/28 17:33:17 bostic 3 2
c update from Kazumasa Utashiro
e
s 00000/00002/00190
d D 7.2 92/06/26 18:26:23 utashiro 2 1
c no SYSCALL_BSDOFFSET
e
s 00192/00000/00000
d D 7.1 92/06/04 16:03:07 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
D 5
#define	MACHINE	"news"
E 5
I 5
#define	MACHINE	"news3400"
I 9
#define NCPUS 1
E 9
E 5
#define COFF

/*
 * Round p (pointer or byte index) up to a correctly-aligned value for all
 * data types (int, long, ...).   The result is u_int and must be cast to
 * any desired pointer type.
 */
D 4
#define	ALIGN(p)	(((u_int)(p) + 3) &~ 3)
E 4
I 4
D 5
#define	ALIGNBYTES	3
E 5
I 5
#define	ALIGNBYTES	7
E 5
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)
E 4

#define	NBPG		4096		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		12		/* LOG2(NBPG) */
#define	NPTEPG		(NBPG/4)

I 6
#define NBSEG		0x400000	/* bytes/segment */
#define	SEGOFSET	(NBSEG-1)	/* byte offset into segment */
#define	SEGSHIFT	22		/* LOG2(NBSEG) */

E 6
#define	KERNBASE	0x80000000	/* start of kernel virtual */
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

#define	DEV_BSIZE	512
#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE	2048
D 6
#define	MAXPHYS		(24 * 1024)	/* max raw I/O transfer size */
E 6
I 6
#define	MAXPHYS		(128 * 1024)	/* max raw I/O transfer size */
E 6

#define	CLSIZE		1
#define	CLSIZELOG2	0

/* NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE */
#define	SSIZE		1		/* initial stack size/NBPG */
#define	SINCR		1		/* increment of stack/NBPG */

#define	UPAGES		2		/* pages of u-area */
D 5
#define	KERNELSTACK	0xffffe000	/* virtual address of kernel stack */
#define	UADDR		0xffffc000	/* address of u */
E 5
I 5
#define	UADDR		0xffffd000	/* address of u */
E 5
#define	UVPN		(UADDR>>PGSHIFT)/* virtual page number of u */
I 5
#define	KERNELSTACK	(UADDR+UPAGES*NBPG)	/* top of kernel stack */
E 5

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
D 8
	((unsigned)(bytes) >> DEV_BSHIFT)
E 8
I 8
	((bytes) >> DEV_BSHIFT)
E 8
#define	dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
D 8
	((unsigned)(db) << DEV_BSHIFT)
E 8
I 8
	((db) << DEV_BSHIFT)
E 8

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

#ifdef news3400
D 5
#ifdef PMAXSPL
#define	splnet		Mach_spl0
#define	splbio		Mach_spl0
#define	spltty		Mach_spl1
#define	splimp		Mach_spl1
#define	splclock	Mach_spl2
I 3
#define	splstatclock	Mach_spl2
E 3
#else
E 5
#define	splnet		spl2
#define	splsoftclock	spl2
#define	splbio		spl3
#define	spltty		spl4
#define	splimp		spl4
#define	splclock	spl5
I 3
#define	splstatclock	spl5
E 3
D 5
#endif /* PMAXSPL */
E 5
#endif /* news3400 */

#ifdef KERNEL
#ifndef LOCORE
extern	int cpuspeed;
#define	DELAY(n)	{ register int N = cpuspeed * (n) / 2; while (--N > 0); }
#endif
#else /* !KERNEL */
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif /* !KERNEL */

D 2
#define	SYSCALL_BSDOFFSET	1000

E 2
#ifndef LOCORE
extern int	intrcnt[];
extern char	*intrnames[];
#endif /* !LOCORE */

#define	INTR_CLOCK	0
#define	INTR_SOFTCLK	1
#define	INTR_SOFTINT	2
#define	INTR_AST	3
#define	INTR_SCSI00	4
#define	INTR_SCSI01	5
#define	INTR_SCSI02	6
#define	INTR_SCSI03	7
#define	INTR_SCSI04	8
#define	INTR_SCSI05	9
#define	INTR_SCSI06	10
#define	INTR_SCSI07	11
#define	INTR_SCSI10	12
#define	INTR_SCSI11	13
#define	INTR_SCSI12	14
#define	INTR_SCSI13	15
#define	INTR_SCSI14	16
#define	INTR_SCSI15	17
#define	INTR_SCSI16	18
#define	INTR_SCSI17	19
#define	INTR_ETHER0	20
#define	INTR_ETHER1	21
#define	INTR_ETHER2	22
#define	INTR_VME2	23
#define	INTR_VME4	24
#define	INTR_RS0	25
#define	INTR_RS1	26
#define	INTR_RS2	27
#define	INTR_RS3	28
#define	INTR_RS4	29
#define	INTR_RS5	30
#define	INTR_RS6	31
#define	INTR_RS7	32
#define	INTR_RS8	33
#define	INTR_RS9	34
#define	INTR_RS10	35
#define	INTR_RS11	36
#define	INTR_PRINTER	37
#define	INTR_FD		38
#define	INTR_AUDIO	39
#define	INTR_KEYBOARD	40
#define	INTR_MOUSE	41
#define	INTR_BITMAP	42
#define	INTR_FDDI	43
#define INTR_RENDER	44

#define	NINTRSLOT	45		/* # of intrcnt[] slot */
I 9

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
E 9
E 1
