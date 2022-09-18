h35763
s 00002/00001/00120
d D 7.22 92/05/26 17:04:03 bostic 32 31
c add ALIGNBYTES constantadd ALIGNBYTES constant
e
s 00004/00004/00117
d D 7.21 92/02/19 17:43:49 bostic 31 30
c rip away illusion of portability in ALIGN
e
s 00002/00002/00119
d D 7.20 91/06/08 16:44:08 bostic 30 29
c don't put anything after the #else or #endif's, unless it's a comment
e
s 00005/00004/00116
d D 7.19 91/05/08 14:40:53 bostic 29 28
c new copyright; att/bsd/shared
e
s 00001/00000/00119
d D 7.18 91/04/28 12:00:43 bostic 28 27
c move comment from <sys/param.h>
e
s 00000/00006/00119
d D 7.17 90/12/16 16:51:06 bostic 27 26
c kernel reorg
e
s 00007/00000/00118
d D 7.16 90/05/10 13:46:40 mckusick 26 25
c add default size for kernel malloc arena
e
s 00007/00000/00111
d D 7.15 90/04/03 22:04:20 karels 25 24
c add ALIGN macro to round pointer up to aligned boundary
e
s 00001/00000/00110
d D 7.14 90/02/23 11:04:15 marc 24 23
c add KERNTEXTOFF
e
s 00001/00001/00109
d D 7.13 89/12/30 22:49:14 mckusick 23 22
c need more UPAGES for NFS
e
s 00001/00001/00109
d D 7.12 89/10/19 23:59:10 mckusick 22 21
c up the number of UPAGES from 10 to 12
e
s 00025/00016/00085
d D 7.11 89/09/04 17:18:20 karels 21 19
c I think bostic and sklower did this: move mbuf parameters here,
c move C limits to machlimits.h
e
s 00004/00002/00099
d R 7.11 89/05/02 21:30:41 mckusick 20 19
c merge NFS from Rick Macklem
e
s 00001/00001/00100
d D 7.10 88/01/21 16:34:17 karels 19 18
c remove endian!
e
s 00009/00029/00092
d D 7.9 88/01/07 10:59:15 bostic 18 17
c move ENDIAN stuff to endian.h, minor reformatting
e
s 00018/00002/00103
d D 7.8 87/10/28 16:21:54 bostic 17 16
c add ANSI C 2.9 numerical limitation constants
e
s 00002/00000/00103
d D 7.7 87/05/21 15:18:34 bostic 16 14
c added #define of MACHINE
e
s 00002/00000/00103
d R 7.7 87/05/13 19:38:41 bostic 15 14
c define MACHINE
e
s 00002/00002/00101
d D 7.6 87/05/12 17:13:09 karels 14 13
c don't use u_type's, wait.h includes us and not types.h
e
s 00005/00001/00098
d D 7.5 87/04/02 16:36:29 karels 13 11
c working with pack labels
e
s 00029/00001/00098
d D 7.4.1.1 87/04/02 16:36:01 karels 12 11
c ifdefs for dev_bsize (almost working_
e
s 00024/00006/00075
d D 7.4 87/01/16 17:28:20 karels 11 10
c mv machdep to machparam.h
e
s 00014/00001/00067
d D 7.3 87/01/16 12:58:23 karels 10 9
c share ntoh? definitions
e
s 00013/00001/00055
d D 7.2 86/11/03 12:28:08 karels 9 7
c defines for byteorder
e
s 00002/00000/00056
d R 7.2 86/10/13 23:03:21 karels 8 7
c define for byte order
e
s 00001/00001/00055
d D 7.1 86/06/05 00:45:24 mckusick 7 6
c 4.3BSD release version
e
s 00008/00000/00048
d D 6.4 85/09/17 23:05:21 karels 6 5
c add cpuspeed variable to adjust delay macro
e
s 00007/00001/00041
d D 6.3 85/06/08 13:43:25 mckusick 5 4
c Add copyright
e
s 00001/00001/00041
d D 6.2 84/12/20 15:02:45 karels 4 3
c increase UPAGES
e
s 00000/00000/00042
d D 6.1 83/07/29 07:20:51 sam 3 2
c 4.2 distribution
e
s 00001/00001/00041
d D 4.2 82/12/09 21:48:23 sam 2 1
c BASEPRI backwards
e
s 00042/00000/00000
d D 4.1 82/11/09 11:27:11 sam 1 0
c date and time created 82/11/09 11:27:11 by sam
e
u
U
f b 
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
D 29
/*
D 7
 * Copyright (c) 1982 Regents of the University of California.
E 7
I 7
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 29
I 29
/*-
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 29
 *
 *	%W% (Berkeley) %G%
 */
E 5

I 17
D 18
#ifndef ENDIAN
E 18
E 17
/*
D 18
 * Machine dependent constants for vax.
E 18
I 18
 * Machine dependent constants for VAX.
E 18
 */
I 9
D 17

E 17
I 16
#define	MACHINE	"vax"

I 18
D 19
#ifndef ENDIAN
E 19
I 19
D 27
#ifndef BYTE_ORDER
E 19
#include <machine/endian.h>
#endif

E 18
E 16
D 17
#ifndef ENDIAN
E 17
I 17
D 21
#define	CHAR_BIT	NBBY
#define	CHAR_MAX	0x7f
#define	CHAR_MIN	0x80
D 18
#define	CLK_TCK		UNDEFINED_FOR_NOW
E 18
I 18
#define	CLK_TCK		60			/* for times() */
E 18
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
E 21
I 21
#include <machine/machlimits.h>
E 21

E 27
I 25
/*
D 31
 * Round p (pointer or byte index) up to a correctly-aligned value
 * for all data types (int, long, ...).   The result is u_int and
 * must be cast to any desired pointer type.
E 31
I 31
 * Round p (pointer or byte index) up to a correctly-aligned value for all
 * data types (int, long, ...).   The result is u_int and must be cast to
 * any desired pointer type.
E 31
 */
D 31
#define	ALIGN(p)	(((u_int)(p) + (sizeof(int) - 1)) &~ (sizeof(int) - 1))
E 31
I 31
D 32
#define	ALIGN(p)	(((u_int)(p) + 3) &~ 3)
E 32
I 32
#define	ALIGNBYTES	3
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)
E 32
E 31

E 25
E 17
D 18
/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define	LITTLE	1234		/* least-significant byte first (vax) */
#define	BIG	4321		/* most-significant byte first */
#define	PDP	3412		/* LSB first in word, MSW first in long (pdp) */
#define	ENDIAN	LITTLE		/* byte order on vax */

I 10
/*
 * Macros for network/external number representation conversion.
 */
#if ENDIAN == BIG && !defined(lint)
#define	ntohl(x)	(x)
#define	ntohs(x)	(x)
#define	htonl(x)	(x)
#define	htons(x)	(x)
#else
D 14
u_short	ntohs(), htons();
u_long	ntohl(), htonl();
E 14
I 14
unsigned short	ntohs(), htons();
unsigned long	ntohl(), htonl();
E 14
#endif

I 13
#define	KERNBASE	0x80000000	/* start of kernel virtual */
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

E 18
E 13
I 12
#define	KERNBASE	0x80000000	/* start of kernel virtual */
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

E 12
E 10
E 9
D 11
#define	NBPG	512		/* bytes/page */
#define	PGOFSET	(NBPG-1)	/* byte offset into page */
#define	PGSHIFT	9		/* LOG2(NBPG) */
E 11
I 11
#define	NBPG		512		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		9		/* LOG2(NBPG) */
#define	NPTEPG		(NBPG/(sizeof (struct pte)))
E 11

I 18
#define	KERNBASE	0x80000000	/* start of kernel virtual */
I 24
#define	KERNTEXTOFF	KERNBASE	/* start of kernel text */
E 24
#define	BTOPKERNBASE	((u_long)KERNBASE >> PGSHIFT)

E 18
I 12
#ifndef SECSIZE
E 12
I 11
#define	DEV_BSIZE	512
#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE	2048
I 13
#define	MAXPHYS		(63 * 1024)	/* max raw I/O transfer size */
E 13
I 12
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
#define	MAXPHYS		(63 * 1024)	/* max raw I/O transfer size */
E 12

E 11
#define	CLSIZE		2
#define	CLSIZELOG2	1

I 28
/* NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE */
E 28
D 11
#define	SSIZE	4		/* initial stack size/NBPG */
#define	SINCR	4		/* increment of stack/NBPG */
E 11
I 11
#define	SSIZE		4		/* initial stack size/NBPG */
#define	SINCR		4		/* increment of stack/NBPG */
E 11

D 4
#define	UPAGES	8		/* pages of u-area */
E 4
I 4
D 11
#define	UPAGES	10		/* pages of u-area */
E 11
I 11
D 22
#define	UPAGES		10		/* pages of u-area */
E 22
I 22
D 23
#define	UPAGES		12		/* pages of u-area */
E 23
I 23
#define	UPAGES		16		/* pages of u-area */
E 23
E 22
I 21

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
E 21
E 11
E 4

/*
I 26
 * Size of kernel malloc arena in CLBYTES-sized logical pages
 */ 
#ifndef NKMEMCLUSTERS
#define	NKMEMCLUSTERS	(512*1024/CLBYTES)
#endif

/*
E 26
 * Some macros for units conversion
 */
/* Core clicks (512 bytes) to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

I 12
#ifndef SECSIZE
E 12
/* Core clicks (512 bytes) to disk blocks */
#define	ctod(x)	(x)
#define	dtoc(x)	(x)
D 12
D 13
#define	dtob(x)	((x)<<9)
E 13
I 13
#define	dtob(x)	((x)<<PGSHIFT)
E 13
E 12
I 12
#define	dtob(x)	((x)<<PGSHIFT)
#else SECSIZE
/* Core clicks (512 bytes) to disk blocks; deprecated */
#define	ctod(x)	(x)				/* XXX */
#define	dtoc(x)	(x)				/* XXX */
#define	dtob(x)	((x)<<PGSHIFT)			/* XXX */
#endif SECSIZE
E 12

/* clicks to bytes */
#define	ctob(x)	((x)<<9)

/* bytes to clicks */
#define	btoc(x)	((((unsigned)(x)+511)>>9))
I 11

I 12
#ifndef SECSIZE
E 12
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
I 12
#else SECSIZE
/* bytes to "disk blocks" and back; deprecated */
#define	btodb(bytes)	((unsigned)(bytes) >> DEV_BSHIFT)	/* XXX */
#define	dbtob(db)	((unsigned)(db) << DEV_BSHIFT)		/* XXX */
#endif SECSIZE
E 12
E 11

/*
 * Macros to decode processor status word.
 */
#define	USERMODE(ps)	(((ps) & PSL_CURMOD) == PSL_CURMOD)
D 2
#define	BASEPRI(ps)	(((ps) & PSL_IPL) != 0)
E 2
I 2
#define	BASEPRI(ps)	(((ps) & PSL_IPL) == 0)
E 2

I 6
#ifdef KERNEL
#ifndef LOCORE
int	cpuspeed;
D 9
#endif
E 9
#define	DELAY(n)	{ register int N = cpuspeed * (n); while (--N > 0); }
I 9
#endif
E 9

D 30
#else KERNEL
E 30
I 30
#else
E 30
E 6
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
I 6
D 30
#endif KERNEL
E 30
I 30
#endif
E 30
I 9
D 10
#endif
E 10
I 10
D 18
#endif ENDIAN
E 18
E 10
E 9
E 6
E 1
