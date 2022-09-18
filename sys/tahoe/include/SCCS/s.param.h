h54068
s 00002/00001/00119
d D 7.11 92/05/26 17:04:31 bostic 27 26
c add ALIGNBYTES constant
e
s 00004/00004/00116
d D 7.10 92/02/19 17:44:38 bostic 26 25
c rip away illusion of portability in ALIGN
e
s 00008/00004/00112
d D 7.9 91/05/08 14:23:28 bostic 25 24
c new copyright; att/bsd/shared
e
s 00001/00000/00115
d D 7.8 91/04/28 12:01:27 bostic 24 23
c move SSIZE comment from <sys/param.h>
e
s 00000/00006/00115
d D 7.7 90/12/16 16:44:02 bostic 23 22
c kernel reorg
e
s 00007/00000/00114
d D 7.6 90/05/10 13:46:56 mckusick 22 21
c add default size for kernel malloc arena
e
s 00007/00000/00107
d D 7.5 90/04/03 22:04:36 karels 21 20
c add ALIGN macro to round pointer up to aligned boundary
e
s 00001/00000/00106
d D 7.4 90/02/23 11:06:06 marc 20 19
c add KERNTEXTOFF
e
s 00001/00001/00105
d D 7.3 89/12/30 22:48:33 mckusick 19 18
c need more UPAGES for NFS
e
s 00025/00016/00081
d D 7.2 89/09/04 17:27:28 karels 18 16
c I think bostic and sklower did this: move mbuf parameters here,
c move C limits to machlimits.h
e
s 00004/00000/00097
d R 7.2 89/05/02 17:54:36 mckusick 17 16
c merge of nfs from Rick Macklem
e
s 00001/00001/00096
d D 7.1 88/05/21 18:35:57 karels 16 15
c bring up to revision 7 for tahoe release
e
s 00001/00001/00096
d D 1.12 88/01/21 16:33:38 karels 15 14
c remove ENDIAN!
e
s 00012/00026/00085
d D 1.11 88/01/07 11:22:35 karels 14 13
c mv endian definitions
e
s 00018/00002/00093
d D 1.10 87/10/28 16:22:36 bostic 13 12
c add ANSI C 2.9 numerical limitation constants
e
s 00002/00000/00093
d D 1.9 87/05/21 15:19:11 bostic 12 10
c added #define of MACHINE
e
s 00002/00000/00093
d R 1.9 87/05/13 19:38:34 bostic 11 10
c define MACHINE
e
s 00002/00002/00091
d D 1.8 87/05/12 17:12:25 karels 10 9
c don't use u_type's, wait.h includes us but not types.h
e
s 00004/00000/00089
d D 1.7 87/04/02 15:57:32 karels 9 7
c working with pack labels
e
s 00028/00000/00089
d D 1.6.1.1 87/04/02 15:57:05 karels 8 7
c ifdef for dev_bsize (almost working)
e
s 00024/00006/00065
d D 1.6 87/01/16 17:28:28 karels 7 6
c mv machdep to machparam.h
e
s 00013/00000/00058
d D 1.5 87/01/16 12:57:58 karels 6 5
c share ntoh? definitions
e
s 00012/00012/00046
d D 1.4 86/11/03 12:05:49 karels 5 3
c move key stats, etc. to cpu.h
e
s 00011/00000/00058
d R 1.4 86/10/13 23:04:12 karels 4 3
c define for byte order; move cache key declarations from kernel.h
e
s 00012/00000/00046
d D 1.3 86/01/24 02:21:30 sam 3 2
c move keystats definition for use by vmstat
e
s 00000/00001/00046
d D 1.2 86/01/20 23:52:36 sam 2 1
c cleanup some more of the autoconfig stuff: eliminate all page 
c maps defined in locore.s in favor of dynamically allocated entries; rename 
c some of the iospace definitions and move them into ../tahoevba/vbaparam.h 
c (will ease vme support sometime?)
e
s 00047/00000/00000
d D 1.1 86/01/05 18:46:21 sam 1 0
c date and time created 86/01/05 18:46:21 by sam
e
u
U
f b 
t
T
I 1
D 14
/*	%M%	%I%	%E%	*/
E 14
I 14
D 25
/*
D 16
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 16
I 16
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 16
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 25
I 25
/*-
 * Copyright (c) 1982, 1986, 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.proprietary.c%
E 25
 *
 *	%W% (Berkeley) %G%
 */
E 14

I 13
D 14
#ifndef ENDIAN
E 14
E 13
/*
 * Machine dependent constants for TAHOE.
 */
I 5
D 13

E 13
I 12
#define	MACHINE	"tahoe"

I 14
D 15
#ifndef ENDIAN
E 15
I 15
D 23
#ifndef BYTE_ORDER
E 15
#include <machine/endian.h>
#endif

E 14
E 12
D 13
#ifndef ENDIAN
E 13
I 13
D 18
#define	CHAR_BIT	NBBY
#define	CHAR_MAX	0x7f
#define	CHAR_MIN	0x80
D 14
#define	CLK_TCK		UNDEFINED_FOR_NOW
E 14
I 14
#define	CLK_TCK		60			/* for times() */
E 14
#define	INT_MAX		0x7fffffff
#define	INT_MIN		0x80000000
#define	LONG_MAX	0x7fffffff
#define	LONG_MIN	0x80000000
#define	SCHAR_MAX	0x7f
#define	SCHAR_MIN	0x80
#define	SHRT_MAX	0x7fff
#define	SHRT_MIN	0x8000
#define	UCHAR_MAX	0xff
#define	UINT_MAX	0xffffffff
#define	ULONG_MAX	0xffffffff
#define	USHRT_MAX	0xffff
E 18
I 18
#include <machine/machlimits.h>
E 18

E 23
I 21
/*
D 26
 * Round p (pointer or byte index) up to a correctly-aligned value
 * for all data types (int, long, ...).   The result is u_int and
 * must be cast to any desired pointer type.
E 26
I 26
 * Round p (pointer or byte index) up to a correctly-aligned value for all
 * data types (int, long, ...).   The result is u_int and must be cast to
 * any desired pointer type.
E 26
 */
D 26
#define	ALIGN(p)	(((u_int)(p) + (sizeof(int) - 1)) &~ (sizeof(int) - 1))
E 26
I 26
D 27
#define	ALIGN(p)	(((u_int)(p) + 3) &~ 3)
E 27
I 27
#define	ALIGNBYTES	3
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)
E 27
E 26

E 21
E 13
D 14
/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define	LITTLE	1234		/* least-significant byte first (vax) */
#define	BIG	4321		/* most-significant byte first */
#define	PDP	3412		/* LSB first in word, MSW first in long (pdp) */
#define	ENDIAN	BIG		/* byte order on tahoe */

I 6
/*
 * Macros for network/external number representation conversion.
 */
#if ENDIAN == BIG && !defined(lint)
#define	ntohl(x)	(x)
#define	ntohs(x)	(x)
#define	htonl(x)	(x)
#define	htons(x)	(x)
#else
D 10
u_short	ntohs(), htons();
u_long	ntohl(), htonl();
E 10
I 10
unsigned short	ntohs(), htons();
unsigned long	ntohl(), htonl();
E 10
#endif

E 14
E 6
E 5
D 7
#define	NBPG	1024		/* bytes/page */
#define	PGOFSET	(NBPG-1)	/* byte offset into page */
#define	PGSHIFT	10		/* LOG2(NBPG) */
E 7
I 7
#define	NBPG		1024		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		10		/* LOG2(NBPG) */
#define	NPTEPG		(NBPG/(sizeof (struct pte)))
E 7

I 9
#define	KERNBASE	0xc0000000	/* start of kernel virtual */
I 20
#define	KERNTEXTOFF	(KERNBASE + 0x800)	/* start of kernel text */
E 20
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

E 9
I 8
#define	KERNBASE	0xc0000000	/* start of kernel virtual */
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

#ifndef SECSIZE
E 8
I 7
#define	DEV_BSIZE	1024
#define	DEV_BSHIFT	10		/* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE	1024		/* NBPG for physical controllers */
I 9
#define	MAXPHYS		(64 * 1024)	/* max raw I/O transfer size */
E 9
I 8
#else SECSIZE
/*
 * Devices without disk labels and the swap virtual device
 * use "blocks" of exactly pagesize.  Devices with disk labels
 * use device-dependent sector sizes for block and character interfaces.
 */
#define	DEV_BSIZE	NBPG
#define	DEV_BSHIFT	PGSHIFT		/* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE	NBPG		/* NBPG for unlabeled block devices */
#endif SECSIZE
#define	MAXPHYS		(64 * 1024)	/* max raw I/O transfer size */
E 8

E 7
#define	CLSIZE		1
#define	CLSIZELOG2	0

I 24
/* NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE */
E 24
D 7
#define	SSIZE	2			/* initial stack size/NBPG */
#define	SINCR	2			/* increment of stack/NBPG */
#define	UPAGES	6			/* pages of u-area (2 stack pages) */
E 7
I 7
#define	SSIZE		2		/* initial stack size/NBPG */
#define	SINCR		2		/* increment of stack/NBPG */
D 19
#define	UPAGES		6		/* pages of u-area (2 stack pages) */
E 19
I 19
#define	UPAGES		8		/* pages of u-area (2 stack pages) */
E 19
I 18

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
E 18
E 7
D 2
#define IOBASE	((caddr_t)0xfff00000)	/* base of Versabus address space */
E 2

#define	MAXCKEY	255		/* maximal allowed code key */
#define	MAXDKEY	255		/* maximal allowed data key */
#define	NCKEY	(MAXCKEY+1)	/* # code keys, including 0 (reserved) */
#define	NDKEY	(MAXDKEY+1)	/* # data keys, including 0 (reserved) */

/*
I 22
 * Size of kernel malloc arena in CLBYTES-sized logical pages
 */ 
#ifndef NKMEMCLUSTERS
#define	NKMEMCLUSTERS	(512*1024/CLBYTES)
#endif

/*
E 22
I 3
D 5
 * Statistics maintained for code and
 * data cache key allocations algorithms.
 */
struct	keystats {
	long	ks_allocs;	/* number of keys allocated */
	long	ks_free;	/* key allocated from free slot */
	long	ks_norefs;	/* key marked in use, but refcnt 0 */
	long	ks_taken;	/* key taken from single process */
	long	ks_shared;	/* key taken from multiple processes */
};

/*
E 5
E 3
 * Some macros for units conversion
 */
/* Core clicks (1024 bytes) to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

I 8
#ifndef SECSIZE
E 8
/* Core clicks (1024 bytes) to disk blocks */
#define	ctod(x)	(x)
#define	dtoc(x)	(x)
#define	dtob(x)	((x)<<PGSHIFT)
I 8
#else SECSIZE
/* Core clicks (1024 bytes) to disk blocks; deprecated */
#define	ctod(x)	(x)				/* XXX */
#define	dtoc(x)	(x)				/* XXX */
#define	dtob(x)	((x)<<PGSHIFT)			/* XXX */
#endif SECSIZE
E 8

/* clicks to bytes */
#define	ctob(x)	((x)<<PGSHIFT)

/* bytes to clicks */
#define	btoc(x)	((((unsigned)(x)+NBPG-1) >> PGSHIFT))
I 7

I 8
#ifndef SECSIZE
E 8
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
I 8
#else SECSIZE
/* bytes to "disk blocks" and back; deprecated */
#define	btodb(bytes)	((unsigned)(bytes) >> DEV_BSHIFT)	/* XXX */
#define	dbtob(db)	((unsigned)(db) << DEV_BSHIFT)		/* XXX */
#endif SECSIZE
E 8
E 7

/*
 * Macros to decode processor status word.
 */
#define	USERMODE(ps)	(((ps) & PSL_CURMOD) == PSL_CURMOD)
#define	BASEPRI(ps)	(((ps) & PSL_IPL) == 0)

#define	DELAY(n)	{ register int N = 3*(n); while (--N > 0); }
I 5
D 14
#endif
E 14
E 5
E 1
