h45288
s 00001/00000/00137
d D 8.6 95/02/19 07:49:02 cgd 56 55
c add key_t, so it can be used in syscall arg descriptions.
e
s 00023/00022/00114
d D 8.5 94/07/10 22:58:03 bostic 55 54
c changes for 64-bit machines
e
s 00005/00000/00131
d D 8.4 94/01/21 17:25:25 bostic 54 53
c add USL's copyright notice
e
s 00001/00000/00130
d D 8.3 94/01/07 16:53:21 bostic 53 52
c the lseek declaration requires <sys/cdefs.h>
e
s 00003/00003/00127
d D 8.2 94/01/04 16:16:55 bostic 52 51
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00128
d D 8.1 93/06/02 19:56:24 bostic 51 50
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00129
d D 7.30 93/05/28 22:44:11 bostic 50 49
c make pid_t signed for safety's sake!
e
s 00001/00001/00129
d D 7.29 93/05/28 01:42:10 mckusick 49 48
c pid_t becomes a u_long
e
s 00000/00001/00130
d D 7.28 93/05/25 15:15:51 mckusick 48 47
c __lseek => lseek
e
s 00012/00000/00119
d D 7.27 93/05/02 11:12:24 mckusick 47 46
c add prototype for lseek to make programs casting second arg to off_t work
e
s 00004/00005/00115
d D 7.26 93/04/30 14:10:14 bostic 46 45
c add uint for S5 compatibility, move ANSI/POSIX tests down into
c machine/include/types.h, some of it should now be visible
e
s 00019/00016/00101
d D 7.25 93/02/10 20:28:14 bostic 45 44
c u_short, u_long aren't POSIX, so may not be typdef'd
e
s 00001/00000/00116
d D 7.24 92/08/03 21:15:30 bostic 44 43
c add FD_COPY
e
s 00012/00012/00104
d D 7.23 92/06/23 00:10:06 bostic 43 42
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00000/00027/00116
d D 7.22 92/06/19 23:10:55 mckusick 42 41
c get rid of the fictionof NOQUAD
e
s 00005/00005/00138
d D 7.21 92/05/13 14:44:26 mckusick 41 40
c 64-bit file sizes, 32-bit uid, gid, and dev's
e
s 00003/00000/00140
d D 7.20 92/01/09 21:58:35 mckusick 40 39
c add ZEROQUAD macro
e
s 00030/00004/00110
d D 7.19 91/12/19 12:44:21 mckusick 39 38
c now includes endian.h; define quad_t based on _NOQUAD support
e
s 00005/00000/00109
d D 7.18 91/12/06 14:08:05 bostic 38 37
c add ssize_t, required by POSIX 1003.1
e
s 00030/00034/00079
d D 7.17 91/05/06 11:08:59 bostic 37 36
c cleanup, mostly cosmetic; new copyright; att/bsd/shared
e
s 00001/00000/00112
d D 7.16 91/05/04 16:00:33 karels 36 35
c add tty forward declaration
e
s 00017/00002/00095
d D 7.15 91/04/20 11:19:54 karels 35 34
c forward declarations of common structs; we use hex, not octal
e
s 00008/00005/00089
d D 7.14 91/03/09 17:55:44 bostic 34 33
c create {hp300,i386,tahoe,vax}/include/ansi.h
e
s 00003/00003/00091
d D 7.13 91/02/05 17:03:29 bostic 33 32
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00005/00093
d D 7.12 90/12/16 16:42:17 bostic 32 30
c kernel reorg
e
s 00004/00000/00098
d R 7.12 90/10/23 23:16:14 mckusick 31 30
c add boolean type and defined values (for new VM)
e
s 00022/00007/00076
d D 7.11 90/06/25 00:51:26 bostic 30 29
c add clock_t, time_t, size_t from machtypes.h; make safe for POSIX
e
s 00020/00022/00065
d D 7.10 90/05/17 09:52:44 bostic 29 28
c move label_t to machine/machtypes
e
s 00001/00001/00086
d D 7.9 90/05/15 22:05:13 bostic 28 27
c rename size_t to segsz_t for ANSI C
e
s 00007/00000/00080
d D 7.8 90/05/10 12:53:05 mckusick 27 26
c add typedef for u_quad; merge in support for hp300 from Utah
e
s 00001/00001/00079
d D 7.7 89/08/26 16:38:52 karels 26 25
c link count is unsigned
e
s 00001/00000/00079
d D 7.6 89/05/29 12:35:18 mckusick 25 24
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00003/00001/00076
d D 7.5 89/05/24 18:15:13 bostic 24 23
c POSIX: add inode link count (nlink_t) mode (mode_t)
e
s 00002/00000/00075
d D 7.4 89/05/01 23:11:48 marc 23 22
c add clock_t and pid_t
e
s 00001/00000/00074
d D 7.3 87/06/20 14:24:16 mckusick 22 21
c add typedef for qaddr_t
e
s 00002/00002/00072
d D 7.2 86/10/13 23:02:05 karels 21 20
c merge in tahoe system
e
s 00001/00001/00073
d D 7.1 86/06/04 23:30:38 mckusick 20 19
c 4.3BSD release version
e
s 00001/00001/00073
d D 6.8 86/03/28 19:34:29 karels 19 18
c now need cast in FD_ZERO...
e
s 00003/00003/00071
d D 6.7 85/10/28 16:41:01 mckusick 18 17
c exterminate the ints
e
s 00007/00009/00067
d D 6.6 85/06/25 13:18:22 karels 17 16
c remove dependency of types.h on param.h; increase CBSIZE
e
s 00028/00001/00048
d D 6.5 85/06/17 21:56:44 karels 16 15
c add macros for select masks; mv param's include of types.h
c after defn. of howmany; allow larger hostnames (domains coming!)
e
s 00007/00001/00042
d D 6.4 85/06/08 15:11:18 mckusick 15 14
c Add copyright
e
s 00002/00000/00041
d D 6.3 85/03/07 19:10:51 karels 14 13
c add uid_t, gid_t
e
s 00003/00000/00038
d D 6.2 84/06/09 13:10:47 sam 13 12
c allow multiple includes
e
s 00000/00000/00038
d D 6.1 83/07/29 06:14:42 sam 12 11
c 4.2 distribution
e
s 00000/00006/00038
d D 4.11 83/07/01 02:25:08 root 11 10
c purge #if sun's
e
s 00001/00000/00043
d D 4.10 83/05/18 02:42:30 sam 10 9
c sun changes
e
s 00001/00001/00042
d D 4.9 82/11/13 23:08:50 sam 9 8
c merge 4.1b and 4.1c
e
s 00012/00005/00031
d D 4.8 82/10/31 16:38:34 root 8 7
c label_t and physadr dependent on vax/sun
e
s 00001/00002/00035
d D 4.7 82/10/20 01:16:33 root 7 6
c lint
e
s 00001/00001/00036
d D 4.6 82/10/17 20:51:38 root 6 5
c daddr_t is a long
e
s 00003/00003/00034
d D 4.5 82/09/08 08:12:01 root 5 4
c label_t now a structure; other misc changes
e
s 00003/00001/00034
d D 4.4 82/04/19 19:27:11 mckusic 4 3
c merge in the new file system
e
s 00002/00000/00033
d D 4.3 81/10/17 16:14:46 wnj 3 2
c cleanup (mpx removal, old tty removal, beginnings of select)
e
s 00001/00000/00032
d D 4.2 81/04/28 03:02:28 root 2 1
c typedef portid_t
e
s 00032/00000/00000
d D 4.1 81/03/21 16:09:48 wnj 1 0
c date and time created 81/03/21 16:09:48 by wnj
e
u
U
t
T
I 4
D 5
/*	types.h	2.1	3/25/82	*/

E 5
E 4
I 1
D 15
/*	%M%	%I%	%E%	*/
E 15
I 15
D 37
/*
D 20
 * Copyright (c) 1982 Regents of the University of California.
E 20
I 20
D 21
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 21
I 21
 * Copyright (c) 1982 Regents of the University of California.
E 21
E 20
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 37
I 37
/*-
D 51
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 51
I 51
D 55
 * Copyright (c) 1982, 1986, 1991, 1993
E 55
I 55
 * Copyright (c) 1982, 1986, 1991, 1993, 1994
E 55
 *	The Regents of the University of California.  All rights reserved.
I 54
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 54
E 51
E 37
 *
I 37
 * %sccs.include.redist.c%
 *
E 37
 *	%W% (Berkeley) %G%
 */
E 15

I 13
D 33
#ifndef _TYPES_
#define	_TYPES_
E 33
I 33
D 52
#ifndef _TYPES_H_
#define	_TYPES_H_
E 52
I 52
#ifndef _SYS_TYPES_H_
#define	_SYS_TYPES_H_
E 52
E 33
E 13
D 29
/*
 * Basic system types and major/minor device constructing/busting macros.
 */
E 29

I 39
/* Machine type dependent parameters. */
D 55
#include <machine/endian.h>
E 55
I 55
#include <machine/ansi.h>
#include <machine/types.h>
E 55

I 45
#ifndef _POSIX_SOURCE
E 45
E 39
I 29
D 37
typedef	short	dev_t;
E 29
D 30
/* major part of a device */
E 30
I 30
#ifndef _POSIX_SOURCE
					/* major part of a device */
E 30
D 35
#define	major(x)	((int)(((unsigned)(x)>>8)&0377))
E 35
I 35
#define	major(x)	((int)(((unsigned)(x) >> 8)&0xff))
E 35
D 29

E 29
D 30
/* minor part of a device */
E 30
I 30
					/* minor part of a device */
E 30
D 35
#define	minor(x)	((int)((x)&0377))
E 35
I 35
#define	minor(x)	((int)((x)&0xff))
E 35
D 29

E 29
D 30
/* make a device number */
E 30
I 30
					/* make a device number */
E 30
#define	makedev(x,y)	((dev_t)(((x)<<8) | (y)))
I 30
#endif
E 30

E 37
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
I 10
D 29
typedef	unsigned short	ushort;		/* sys III compat */
E 29
I 29
D 30
typedef	unsigned short	ushort;		/* sys V compatibility */
E 30
I 30
typedef	unsigned short	ushort;		/* Sys V compatibility */
I 46
typedef	unsigned int	uint;		/* Sys V compatibility */
E 46
I 45
#endif
E 45
E 30
E 29
E 10

I 39
D 42
#ifdef _NOQUAD
typedef	struct	_uquad	{ u_long val[2]; } u_quad_t;
typedef	struct	_quad	{   long val[2]; } quad_t;
typedef	long *	qaddr_t;
#define	QUADNE(q1, q2) \
	((q1).val[_QUAD_LOWWORD] != (q2).val[_QUAD_LOWWORD] || \
	(q1).val[_QUAD_HIGHWORD] != (q2).val[_QUAD_HIGHWORD])
#define	QUADEQ(q1, q2) \
	((q1).val[_QUAD_LOWWORD] == (q2).val[_QUAD_LOWWORD] && \
	(q1).val[_QUAD_HIGHWORD] == (q2).val[_QUAD_HIGHWORD])
#define	QUADGT(q1, q2) \
	(((q1).val[_QUAD_HIGHWORD] == (q2).val[_QUAD_HIGHWORD]) ? \
	 ((q1).val[_QUAD_LOWWORD] > (q2).val[_QUAD_LOWWORD]) : \
	 ((q1).val[_QUAD_HIGHWORD] > (q2).val[_QUAD_HIGHWORD]))
#define	INCRQUAD(q) \
	((++((q).val[_QUAD_LOWWORD]) == 0) ? ++((q).val[_QUAD_HIGHWORD]) : 0)
I 40
#define	ZEROQUAD(q) \
	(q).val[0] = (q).val[1] = 0
E 40

#else /* QUAD support */
E 42
D 45
typedef	unsigned long long u_quad_t;
typedef	long long quad_t;
typedef	quad_t * qaddr_t;
D 42
#define	QUADNE(q1, q2)	(q1) != (q2)
#define	QUADEQ(q1, q2)	(q1) == (q2)
#define	QUADGT(q1, q2)	(q1) > (q2)
#define	INCRQUAD(q)	(q)++
I 40
#define	ZEROQUAD(q)	(q) = 0
E 40
#endif /* QUAD */

E 42
E 39
I 37
typedef	char *	caddr_t;		/* core address */
typedef	long	daddr_t;		/* disk address */
D 41
typedef	short	dev_t;			/* device number */
E 41
I 41
typedef	u_long	dev_t;			/* device number */
E 41
typedef	u_long	ino_t;			/* inode number */
D 41
typedef	long	off_t;			/* file offset (should be a quad) */
E 41
I 41
typedef	quad_t	off_t;			/* file offset */
E 41
typedef	u_short	nlink_t;		/* link count */
typedef	long	swblk_t;		/* swap offset */
typedef	long	segsz_t;		/* segment size */
D 41
typedef	u_short	uid_t;			/* user id */
typedef	u_short	gid_t;			/* group id */
E 41
I 41
typedef	u_long	uid_t;			/* user id */
typedef	u_long	gid_t;			/* group id */
E 41
typedef	short	pid_t;			/* process id */
typedef	u_short	mode_t;			/* permissions */
typedef u_long	fixpt_t;		/* fixed point number */
E 45
I 45
D 55
typedef	unsigned long long u_quad_t;	/* quads */
typedef	long long	quad_t;
E 55
I 55
typedef	u_int64_t	u_quad_t;	/* quads */
typedef	int64_t		quad_t;
E 55
typedef	quad_t *	qaddr_t;

typedef	char *		caddr_t;	/* core address */
D 55
typedef	long		daddr_t;	/* disk address */
typedef	unsigned long	dev_t;		/* device number */
typedef unsigned long	fixpt_t;	/* fixed point number */
typedef	unsigned long	gid_t;		/* group id */
typedef	unsigned long	ino_t;		/* inode number */
typedef	unsigned short	mode_t;		/* permissions */
typedef	unsigned short	nlink_t;	/* link count */
E 55
I 55
typedef	int32_t		daddr_t;	/* disk address */
typedef	u_int32_t	dev_t;		/* device number */
typedef u_int32_t	fixpt_t;	/* fixed point number */
typedef	u_int32_t	gid_t;		/* group id */
typedef	u_int32_t	ino_t;		/* inode number */
I 56
typedef	long		key_t;		/* IPC key (for Sys V IPC) */
E 56
typedef	u_int16_t	mode_t;		/* permissions */
typedef	u_int16_t	nlink_t;	/* link count */
E 55
typedef	quad_t		off_t;		/* file offset */
D 49
typedef	short		pid_t;		/* process id */
E 49
I 49
D 50
typedef	unsigned long	pid_t;		/* process id */
E 50
I 50
D 55
typedef	long		pid_t;		/* process id */
E 50
E 49
typedef	long		segsz_t;	/* segment size */
typedef	long		swblk_t;	/* swap offset */
typedef	unsigned long	uid_t;		/* user id */
E 55
I 55
typedef	int32_t		pid_t;		/* process id */
typedef	int32_t		segsz_t;	/* segment size */
typedef	int32_t		swblk_t;	/* swap offset */
typedef	u_int32_t	uid_t;		/* user id */
E 55
E 45

I 47
/*
 * This belongs in unistd.h, but is placed here to ensure that programs
 * casting the second parameter of lseek to off_t will get the correct
 * version of lseek.
 */
#ifndef KERNEL
I 53
#include <sys/cdefs.h>
E 53
D 48
#define	 lseek __lseek
E 48
__BEGIN_DECLS
off_t	 lseek __P((int, off_t, int));
__END_DECLS
#endif

E 47
#ifndef _POSIX_SOURCE
D 39
typedef	struct	_uquad	{ u_long val[2]; } u_quad;
typedef	struct	_quad	{   long val[2]; } quad;
typedef	long *	qaddr_t;	/* should be typedef quad * qaddr_t; */

E 39
D 55
#define	major(x)	((int)(((u_int)(x) >> 8)&0xff))	/* major number */
#define	minor(x)	((int)((x)&0xff))		/* minor number */
#define	makedev(x,y)	((dev_t)(((x)<<8) | (y)))	/* create dev_t */
E 55
I 55
							/* major number */
#define	major(x)	((int32_t)(((u_int32_t)(x) >> 8) & 0xff))
#define	minor(x)	((int32_t)((x) & 0xff))		/* minor number */
#define	makedev(x,y)	((dev_t)(((x) << 8) | (y)))	/* create dev_t */
E 55
#endif

E 37
I 34
D 55
#include <machine/ansi.h>
D 46
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
E 46
E 34
D 8
/* SHOULD USE long RATHER THAN int HERE BUT IT WOULD GIVE LINT ON THE KERNEL */
/* GASTRIC DISTRESS AND DON'T HAVE TIME TO FIX THAT JUST NOW */
E 8
I 8
D 21
#ifdef vax
E 21
I 21
D 29
#if defined(vax) || defined(tahoe)
E 21
E 8
typedef	struct	_physadr { int r[1]; } *physadr;
I 8
typedef	struct	label_t	{
	int	val[14];
} label_t;
E 29
I 29
D 32
#ifdef KERNEL
#include "machine/machtypes.h"
#else
#include <machine/machtypes.h>
E 29
#endif
E 32
I 32
#include <machine/types.h>
E 55
I 55
#include <machine/endian.h>
E 55
I 34
D 46
#endif
E 46
E 34
E 32
I 30

D 43
#ifdef	_CLOCK_T_
typedef	_CLOCK_T_	clock_t;
#undef	_CLOCK_T_
E 43
I 43
#ifdef	_BSD_CLOCK_T_
typedef	_BSD_CLOCK_T_	clock_t;
#undef	_BSD_CLOCK_T_
E 43
#endif

D 34
#ifdef	_TIME_T_
typedef	_TIME_T_	time_t;
#undef	_TIME_T_
#endif

E 34
E 30
I 27
D 29
#if defined(hp300)
typedef	struct	_physadr { short r[1]; } *physadr;
typedef	struct	label_t	{
	int	val[15];	/* consistent with HP-UX */
} label_t;
E 29
I 29
D 43
#ifdef	_SIZE_T_
typedef	_SIZE_T_	size_t;
#undef	_SIZE_T_
E 43
I 43
#ifdef	_BSD_SIZE_T_
typedef	_BSD_SIZE_T_	size_t;
#undef	_BSD_SIZE_T_
E 43
I 34
#endif

I 38
D 43
#ifdef	_SSIZE_T_
typedef	_SSIZE_T_	ssize_t;
#undef	_SSIZE_T_
E 43
I 43
#ifdef	_BSD_SSIZE_T_
typedef	_BSD_SSIZE_T_	ssize_t;
#undef	_BSD_SSIZE_T_
E 43
#endif

E 38
D 43
#ifdef	_TIME_T_
typedef	_TIME_T_	time_t;
#undef	_TIME_T_
E 43
I 43
#ifdef	_BSD_TIME_T_
typedef	_BSD_TIME_T_	time_t;
#undef	_BSD_TIME_T_
E 43
E 34
E 29
#endif
I 29

I 30
#ifndef _POSIX_SOURCE
E 30
E 29
D 37
typedef	struct	_uquad { unsigned long val[2]; } u_quad;
E 27
D 11
#ifdef sun
typedef	struct	_physadr { short r[1]; } *physadr;
typedef	struct	label_t	{
	int	val[13];
} label_t;
D 9
typedef	struct	quad { long val[2]; } quad;
E 9
#endif
E 11
I 9
typedef	struct	_quad { long val[2]; } quad;
I 30
#endif
E 30
I 29
typedef	long *	qaddr_t;	/* should be typedef quad * qaddr_t; */

E 29
E 9
E 8
D 6
typedef	int	daddr_t;
E 6
I 6
typedef	long	daddr_t;
E 6
typedef	char *	caddr_t;
I 22
D 29
typedef	long *	qaddr_t;	/* should be typedef quad * qaddr_t; */
E 29
E 22
D 4
typedef	u_short ino_t;
E 4
I 4
typedef	u_long	ino_t;
E 4
D 7
typedef	int	swblk_t;
E 7
I 7
typedef	long	swblk_t;
E 7
D 18
typedef	int	size_t;
typedef	int	time_t;
E 18
I 18
D 28
typedef	long	size_t;
E 28
I 28
typedef	long	segsz_t;
E 28
D 30
typedef	long	time_t;
I 23
typedef	u_long	clock_t;
E 30
E 23
E 18
D 5
typedef	int	label_t[14];
E 5
I 5
D 8
typedef	struct	label_t	{
	int	val[14];
} label_t;
E 8
E 5
D 29
typedef	short	dev_t;
E 29
D 18
typedef	int	off_t;
E 18
I 18
typedef	long	off_t;
E 18
I 14
typedef	u_short	uid_t;
typedef	u_short	gid_t;
I 23
typedef	short	pid_t;
I 24
D 26
typedef	short	nlink_t;
E 26
I 26
typedef	u_short	nlink_t;
E 26
typedef	u_short	mode_t;
I 25
typedef u_long	fixpt_t;
E 25
E 24
E 23
E 14
I 2
D 7
typedef	long	portid_t;
E 7
I 3

I 30
#ifndef _POSIX_SOURCE
E 37
E 30
I 17
#define	NBBY	8		/* number of bits in a byte */
I 29

E 29
E 17
D 16
typedef	struct	fd_set { int fds_bits[1]; } fd_set;
E 16
I 16
/*
D 29
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
I 17
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= NOFILE (param.h).
E 29
I 29
 * Select uses bit masks of file descriptors in longs.  These macros
 * manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here should
D 37
 * be >= NOFILE (param.h).
E 37
I 37
 * be enough for most uses.
E 37
E 29
E 17
 */
D 17
#ifndef	NBBY
#ifdef KERNEL
#include "param.h"
#else	KERNEL
#include <sys/param.h>
#endif	KERNEL
#endif	NBBY

E 17
#ifndef	FD_SETSIZE
D 17
#define	FD_SETSIZE	NOFILE
E 17
I 17
#define	FD_SETSIZE	256
E 17
#endif

D 55
typedef long	fd_mask;
E 55
I 55
typedef int32_t	fd_mask;
E 55
#define NFDBITS	(sizeof(fd_mask) * NBBY)	/* bits per mask */
I 29

E 29
I 17
#ifndef howmany
D 55
#define	howmany(x, y)	(((x)+((y)-1))/(y))
E 55
I 55
#define	howmany(x, y)	(((x) + ((y) - 1)) / (y))
E 55
#endif
E 17

typedef	struct fd_set {
	fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;

#define	FD_SET(n, p)	((p)->fds_bits[(n)/NFDBITS] |= (1 << ((n) % NFDBITS)))
#define	FD_CLR(n, p)	((p)->fds_bits[(n)/NFDBITS] &= ~(1 << ((n) % NFDBITS)))
#define	FD_ISSET(n, p)	((p)->fds_bits[(n)/NFDBITS] & (1 << ((n) % NFDBITS)))
I 44
#define	FD_COPY(f, t)	bcopy(f, t, sizeof(*(f)))
E 44
D 19
#define FD_ZERO(p)	bzero(p, sizeof(*(p)))
E 19
I 19
D 30
#define FD_ZERO(p)	bzero((char *)(p), sizeof(*(p)))
E 30
I 30
D 41
#define	FD_ZERO(p)	bzero((char *)(p), sizeof(*(p)))
E 41
I 41
#define	FD_ZERO(p)	bzero(p, sizeof(*(p)))
E 41
I 35

#if defined(__STDC__) && defined(KERNEL)
/*
D 46
 * Forward structure declarations for function prototypes.
 * We include the common structures that cross subsystem boundaries here;
 * others are mostly used in the same place that the structure is defined.
E 46
I 46
 * Forward structure declarations for function prototypes.  We include the
 * common structures that cross subsystem boundaries here; others are mostly
 * used in the same place that the structure is defined.
E 46
 */
struct	proc;
struct	pgrp;
struct	ucred;
struct	rusage;
struct	file;
struct	buf;
I 36
struct	tty;
E 36
struct	uio;
#endif
E 35
E 30
E 19

I 30
#endif /* !_POSIX_SOURCE */
E 30
E 16
I 13
D 24
#endif
E 24
I 24
D 33
#endif /* _TYPES_ */
E 33
I 33
D 52
#endif /* !_TYPES_H_ */
E 52
I 52
#endif /* !_SYS_TYPES_H_ */
E 52
E 33
E 24
E 13
E 3
E 2
E 1
