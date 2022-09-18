/*-
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)param.h	7.22 (Berkeley) 5/26/92
 */

/*
 * Machine dependent constants for VAX.
 */
#define	MACHINE	"vax"

/*
 * Round p (pointer or byte index) up to a correctly-aligned value for all
 * data types (int, long, ...).   The result is u_int and must be cast to
 * any desired pointer type.
 */
#define	ALIGNBYTES	3
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)

#define	NBPG		512		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		9		/* LOG2(NBPG) */
#define	NPTEPG		(NBPG/(sizeof (struct pte)))

#define	KERNBASE	0x80000000	/* start of kernel virtual */
#define	KERNTEXTOFF	KERNBASE	/* start of kernel text */
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

#define	DEV_BSIZE	512
#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE	2048
#define	MAXPHYS		(63 * 1024)	/* max raw I/O transfer size */

#define	CLSIZE		2
#define	CLSIZELOG2	1

/* NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE */
#define	SSIZE		4		/* initial stack size/NBPG */
#define	SINCR		4		/* increment of stack/NBPG */

#define	UPAGES		16		/* pages of u-area */

/*
 * Constants related to network buffer management.
 * MCLBYTES must be no larger than CLBYTES (the software page size), and,
 * on machines that exchange pages of input or output buffers with mbuf
 * clusters (MAPPED_MBUFS), MCLBYTES must also be an integral multiple
 * of the hardware page size.
 */
#define	MSIZE		128		/* size of an mbuf */
#define	MAPPED_MBUFS			/* can do scatter-gather I/O */
#if CLBYTES > 1024
#define	MCLBYTES	1024
#define	MCLSHIFT	10
#define	MCLOFSET	(MCLBYTES - 1)
#else
#define	MCLBYTES	CLBYTES
#define	MCLSHIFT	CLSHIFT
#define	MCLOFSET	CLOFSET
#endif
#ifdef GATEWAY
#define	NMBCLUSTERS	512		/* map size, max cluster allocation */
#else
#define	NMBCLUSTERS	256		/* map size, max cluster allocation */
#endif

/*
 * Size of kernel malloc arena in CLBYTES-sized logical pages
 */ 
#ifndef NKMEMCLUSTERS
#define	NKMEMCLUSTERS	(512*1024/CLBYTES)
#endif

/*
 * Some macros for units conversion
 */
/* Core clicks (512 bytes) to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

/* Core clicks (512 bytes) to disk blocks */
#define	ctod(x)	(x)
#define	dtoc(x)	(x)
#define	dtob(x)	((x)<<PGSHIFT)

/* clicks to bytes */
#define	ctob(x)	((x)<<9)

/* bytes to clicks */
#define	btoc(x)	((((unsigned)(x)+511)>>9))

#define	btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
	((unsigned)(bytes) >> DEV_BSHIFT)
#define	dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
	((unsigned)(db) << DEV_BSHIFT)

/*
 * Map a ``block device block'' to a file system block.
 * This should be device dependent, and will be if we
 * add an entry to cdevsw/bdevsw for that purpose.
 * For now though just use DEV_BSIZE.
 */
#define	bdbtofsb(bn)	((bn) / (BLKDEV_IOSIZE/DEV_BSIZE))

/*
 * Macros to decode processor status word.
 */
#define	USERMODE(ps)	(((ps) & PSL_CURMOD) == PSL_CURMOD)
#define	BASEPRI(ps)	(((ps) & PSL_IPL) == 0)

#ifdef KERNEL
#ifndef LOCORE
int	cpuspeed;
#define	DELAY(n)	{ register int N = cpuspeed * (n); while (--N > 0); }
#endif

#else
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif
