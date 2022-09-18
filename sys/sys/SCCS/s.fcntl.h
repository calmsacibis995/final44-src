h57955
s 00005/00000/00159
d D 8.3 94/01/21 17:25:08 bostic 22 21
c add USL's copyright notice
e
s 00003/00003/00156
d D 8.2 94/01/04 16:16:28 bostic 21 20
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00157
d D 8.1 93/06/02 19:53:30 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00157
d D 5.16 93/05/28 01:41:50 mckusick 19 18
c reorganize to better alignment
e
s 00007/00003/00152
d D 5.15 92/06/29 11:05:52 bostic 18 17
c make FREAD/FWRITE available to user programs
e
s 00010/00009/00145
d D 5.14 91/07/01 11:54:04 karels 17 16
c re-add FNDELAY for compatibility; try once more to explain
c the difference between O_* and F*
e
s 00012/00020/00142
d D 5.13 91/05/30 15:30:22 mckusick 16 15
c make file flags more consistent; add support for open with lock
e
s 00003/00000/00159
d D 5.12 91/02/23 11:13:09 donn 15 14
c One more prototype declaration.
e
s 00098/00049/00061
d D 5.11 91/02/22 12:35:21 karels 14 13
c rearrange, put all open() and file f_flags definitions here,
c put fcntl stuff together, move all seek, etc. defs to unistd.h
e
s 00013/00013/00097
d D 5.10 91/02/05 17:04:15 bostic 13 12
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00002/00000/00108
d D 5.9 91/02/03 22:51:52 mckusick 12 11
c add include of types.h
e
s 00016/00001/00092
d D 5.8 91/02/01 16:13:38 mckusick 11 10
c add POSIX-style byte-level record locking
e
s 00002/00004/00091
d D 5.7 90/10/31 11:17:19 bostic 10 9
c don't include function prototypes in the kernel
e
s 00005/00000/00090
d D 5.6 90/10/23 10:30:43 mckusick 9 8
c need to include types.h for function prototypes
e
s 00001/00001/00089
d D 5.5 90/05/29 19:29:49 bostic 8 7
c C++ needs prototypes, too
e
s 00078/00034/00012
d D 5.4 90/05/25 18:04:28 bostic 7 6
c POSIX 1003.1
e
s 00006/00000/00040
d D 5.3 90/03/06 15:36:10 bostic 6 5
c add ANSI C prototypes
e
s 00011/00010/00029
d D 5.2 86/01/08 18:20:43 lepreau 5 4
c make dup defs from file.h be textually the same so cpp doesn't bitch.
c Probably ought to #infdef them but that would mean changing file.h too.
e
s 00007/00001/00032
d D 5.1 85/05/30 09:35:54 dist 4 3
c Add copyright
e
s 00006/00000/00027
d D 4.3 85/05/22 18:18:18 mckusick 3 2
c add missing modes
e
s 00009/00002/00018
d D 4.2 83/09/25 14:21:00 karels 2 1
c flags for F_[SG]ETFL
e
s 00020/00000/00000
d D 4.1 83/07/03 00:36:52 sam 1 0
c date and time created 83/07/03 00:36:52 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
D 7
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 20
 * Copyright (c) 1983, 1990 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1983, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 22
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 22
E 20
E 7
 *
I 7
 * %sccs.include.redist.c%
 *
E 7
 *	%W% (Berkeley) %G%
 */
E 4

I 12
D 13
#include "types.h"
E 13
I 13
D 21
#ifndef _FCNTL_H_
#define	_FCNTL_H_
E 21
I 21
#ifndef _SYS_FCNTL_H_
#define	_SYS_FCNTL_H_
E 21
E 13

I 14
/*
 * This file includes the definitions for open and fcntl
 * described by POSIX for <fcntl.h>; it also includes
 * related kernel definitions.
 */

E 14
E 12
D 7
/*
D 5
 * Flag values accessible to open(2) and fcntl(2)
 *  (The first three can only be set by open)
E 5
I 5
 * Flag values accessible to open(2) and fcntl(2)-- copied from
 * <sys/file.h>.  (The first three can only be set by open.)
E 5
 */
D 5
#define	O_RDONLY	0
#define	O_WRONLY	1
#define	O_RDWR		2
D 2
#define	O_NDELAY	04	/* Non-blocking I/O */
#define	O_APPEND	010	/* append (writes guaranteed at the end) */
E 2
I 2
#define	O_NDELAY	FNDELAY	/* Non-blocking I/O */
#define	O_APPEND	FAPPEND	/* append (writes guaranteed at the end) */
I 3
#define	O_CREAT		FCREAT	/* open with file create */
#define	O_TRUNC		FTRUNC	/* open with truncation */
#define	O_EXCL		FEXCL	/* error on create if file exists */
E 5
I 5
#define	O_RDONLY	000		/* open for reading */
#define	O_WRONLY	001		/* open for writing */
#define	O_RDWR		002		/* open for read & write */
#define	O_NDELAY	FNDELAY		/* non-blocking open */
					/* really non-blocking I/O for fcntl */
#define	O_APPEND	FAPPEND		/* append on each write */
#define	O_CREAT		FCREAT		/* open with file create */
#define	O_TRUNC		FTRUNC		/* open with truncation */
#define	O_EXCL		FEXCL		/* error on create if file exists */
E 7
I 7
D 13
#ifndef F_DUPFD
E 13
I 13
#ifndef KERNEL
#include <sys/types.h>
#endif
E 13
E 7
E 5
E 3
E 2

I 2
D 7
#ifndef	F_DUPFD
E 2
/* fcntl(2) requests */
#define	F_DUPFD	0	/* Duplicate fildes */
#define	F_GETFD	1	/* Get fildes flags */
#define	F_SETFD	2	/* Set fildes flags */
#define	F_GETFL	3	/* Get file flags */
#define	F_SETFL	4	/* Set file flags */
#define	F_GETOWN 5	/* Get owner */
#define F_SETOWN 6	/* Set owner */
E 7
I 7
D 14
/* command values for fcntl(2) */
E 14
I 14
/*
 * File status flags: these are used by open(2), fcntl(2).
D 17
 * They are also used in the kernel file structure,
 * which is a superset of the open/fcntl flags.
 * Open/fcntl flags begin with O_; kernel-internal-only
 * flags begin with F.
E 17
I 17
 * They are also used (indirectly) in the kernel file structure f_flags,
 * which is a superset of the open/fcntl flags.  Open flags and f_flags
 * are inter-convertible using OFLAGS(fflags) and FFLAGS(oflags).
 * Open/fcntl flags begin with O_; kernel-internal flags begin with F.
E 17
 */
/* open-only flags */
#define	O_RDONLY	0x0000		/* open for reading only */
#define	O_WRONLY	0x0001		/* open for writing only */
#define	O_RDWR		0x0002		/* open for reading and writing */
#define	O_ACCMODE	0x0003		/* mask for above modes */

D 18
#ifdef KERNEL
E 18
/*
D 18
 * Kernel encoding of open mode; separate read and write bits
 * that are independently testable: 1 greater than the above.
E 18
I 18
 * Kernel encoding of open mode; separate read and write bits that are
 * independently testable: 1 greater than the above.
 *
 * XXX
 * FREAD and FWRITE are excluded from the #ifdef KERNEL so that TIOCFLUSH,
 * which was documented to use FREAD/FWRITE, continues to work.
E 18
 */
I 18
#ifndef _POSIX_SOURCE
E 18
#define	FREAD		0x0001
#define	FWRITE		0x0002
#endif
#define	O_NONBLOCK	0x0004		/* no delay */
#define	O_APPEND	0x0008		/* set append mode */
D 16
#ifdef KERNEL
#define	FMARK		0x0010		/* mark during gc() */
#define	FDEFER		0x0020		/* defer for next gc pass */
#endif
E 16
#ifndef _POSIX_SOURCE
I 16
#define	O_SHLOCK	0x0010		/* open with shared file lock */
#define	O_EXLOCK	0x0020		/* open with exclusive file lock */
E 16
#define	O_ASYNC		0x0040		/* signal pgrp when data ready */
D 16
#define	O_SHLOCK	0x0080		/* shared file lock present */
#define	O_EXLOCK	0x0100		/* exclusive file lock present */
E 16
I 16
#define	O_FSYNC		0x0080		/* synchronous writes */
E 16
#endif
#define	O_CREAT		0x0200		/* create if nonexistant */
#define	O_TRUNC		0x0400		/* truncate to zero length */
#define	O_EXCL		0x0800		/* error if already exists */
D 16
#define	O_FSYNC		0x1000		/* synchronous writes */
E 16
I 16
#ifdef KERNEL
#define	FMARK		0x1000		/* mark during gc() */
#define	FDEFER		0x2000		/* defer for next gc pass */
#define	FHASLOCK	0x4000		/* descriptor holds advisory lock */
#endif
E 16

/* defined by POSIX 1003.1; BSD default, so no bit required */
#define	O_NOCTTY	0		/* don't assign controlling terminal */

#ifdef KERNEL
/* convert from open() flags to/from fflags; convert O_RD/WR to FREAD/FWRITE */
#define	FFLAGS(oflags)	((oflags) + 1)
#define	OFLAGS(fflags)	((fflags) - 1)

/* bits to save after open */
D 16
#define	FMASK		(FREAD|FWRITE|FAPPEND|FASYNC|FNONBLOCK)
E 16
I 16
#define	FMASK		(FREAD|FWRITE|FAPPEND|FASYNC|FFSYNC|FNONBLOCK)
E 16
/* bits settable by fcntl(F_SETFL, ...) */
D 16
#define	FCNTLFLAGS	(O_NONBLOCK|O_APPEND|O_ASYNC|O_FSYNC)
E 16
I 16
#define	FCNTLFLAGS	(FAPPEND|FASYNC|FFSYNC|FNONBLOCK)
E 16
#endif

/*
 * The O_* flags used to have only F* names, which were used in the kernel
 * and by fcntl.  We retain the F* names for the kernel f_flags field
 * and for backward compatibility for fcntl.
 */
#ifndef _POSIX_SOURCE
D 17
#define	FAPPEND		O_APPEND
#define	FASYNC		O_ASYNC
D 16
#define	FNDELAY		O_NONBLOCK
E 16
I 16
#define	FFSYNC		O_FSYNC
#define	FNONBLOCK	O_NONBLOCK
E 16
#define	O_NDELAY	O_NONBLOCK
E 17
I 17
#define	FAPPEND		O_APPEND	/* kernel/compat */
#define	FASYNC		O_ASYNC		/* kernel/compat */
#define	FFSYNC		O_FSYNC		/* kernel */
#define	FNONBLOCK	O_NONBLOCK	/* kernel */
#define	FNDELAY		O_NONBLOCK	/* compat */
#define	O_NDELAY	O_NONBLOCK	/* compat */
E 17
#endif
D 16

#ifdef KERNEL
#define	FCREAT		O_CREAT		/* not stored in f_flags */
#define	FEXCL		O_EXCL		/* not stored in f_flags */
#define	FTRUNC		O_TRUNC		/* not stored in f_flags */
#define	FEXLOCK		O_EXLOCK
#define	FSHLOCK		O_SHLOCK
#define	FNONBLOCK	O_NONBLOCK
#endif

E 16

/*
 * Constants used for fcntl(2)
 */

/* command values */
E 14
#define	F_DUPFD		0		/* duplicate file descriptor */
#define	F_GETFD		1		/* get file descriptor flags */
#define	F_SETFD		2		/* set file descriptor flags */
#define	F_GETFL		3		/* get file status flags */
#define	F_SETFL		4		/* set file status flags */
#ifndef _POSIX_SOURCE
#define	F_GETOWN	5		/* get SIGIO/SIGURG proc/pgrp */
#define F_SETOWN	6		/* set SIGIO/SIGURG proc/pgrp */
#endif
#define	F_GETLK		7		/* get record locking information */
#define	F_SETLK		8		/* set record locking information */
#define	F_SETLKW	9		/* F_SETLK; wait if blocked */
E 7
I 2

D 7
/* flags for F_GETFL, F_SETFL-- copied from <sys/file.h> */
#define	FNDELAY		00004		/* non-blocking reads */
#define	FAPPEND		00010		/* append on each write */
#define	FASYNC		00100		/* signal pgrp when data ready */
I 3
#define	FCREAT		01000		/* create if nonexistant */
#define	FTRUNC		02000		/* truncate to zero length */
#define	FEXCL		04000		/* error if already created */
E 7
I 7
/* file descriptor flags (F_GETFD, F_SETFD) */
#define	FD_CLOEXEC	1		/* close-on-exec flag */

/* record locking flags (F_GETLK, F_SETLK, F_SETLKW) */
#define	F_RDLCK		1		/* shared or read lock */
#define	F_UNLCK		2		/* unlock */
#define	F_WRLCK		3		/* exclusive or write lock */
I 11
#ifdef KERNEL
#define	F_WAIT		0x010		/* Wait until lock is granted */
#define	F_FLOCK		0x020	 	/* Use flock(2) semantics for lock */
#define	F_POSIX		0x040	 	/* Use POSIX semantics for lock */
#endif
E 11

I 14
/*
 * Advisory file segment locking data type -
 * information passed to system by user
 */
struct flock {
D 19
	short	l_type;		/* lock type: read/write, etc. */
	short	l_whence;	/* type of l_start */
E 19
	off_t	l_start;	/* starting offset */
	off_t	l_len;		/* len = 0 means until end of file */
	pid_t	l_pid;		/* lock owner */
I 19
	short	l_type;		/* lock type: read/write, etc. */
	short	l_whence;	/* type of l_start */
E 19
};


E 14
#ifndef _POSIX_SOURCE
/* lock operations for flock(2) */
#define	LOCK_SH		0x01		/* shared file lock */
#define	LOCK_EX		0x02		/* exclusive file lock */
#define	LOCK_NB		0x04		/* don't block when locking */
#define	LOCK_UN		0x08		/* unlock file */
E 7
E 3
#endif
I 6

D 7
#ifdef __STDC__
E 7
I 7
D 14
/* file status flags */
#define	O_RDONLY	00000		/* open for reading only */
#define	O_WRONLY	00001		/* open for writing only */
#define	O_RDWR		00002		/* open for reading and writing */
#define	O_NONBLOCK	00004		/* no delay */
#ifndef _POSIX_SOURCE
#define	O_NDELAY	O_NONBLOCK
#define	FNDELAY		O_NONBLOCK
#endif
/*			00008		/* unused */
#define	O_APPEND	00010		/* set append mode */
#ifndef _POSIX_SOURCE
#define	FAPPEND		O_APPEND
#endif
					/* kernel placeholders */
#if !defined(_POSIX_SOURCE) && defined(KERNEL)
#define	O_MARK		00020		/* mark during gc() */
#define	O_DEFER		00040		/* defer for next gc pass */
#endif
/*			00080		/* unused */
#ifndef _POSIX_SOURCE
#define	O_ASYNC		00100		/* signal pgrp when data ready */
#define	FASYNC		O_ASYNC
#define	O_SHLOCK	00200		/* shared file lock present */
#define	O_EXLOCK	00400		/* exclusive file lock present */
/*			00800		/* unused */
#endif
#define	O_CREAT		01000		/* create if nonexistant */
#define	O_TRUNC		02000		/* truncate to zero length */
#define	O_EXCL		04000		/* error if already exists */
/*			08000		/* unused */
E 14

D 14
/* defined by POSIX 1003.1; BSD default, so no bit required */
#define	O_NOCTTY	0		/* don't assign controlling terminal */

/* mask for file access modes */
#define	O_ACCMODE	(O_RDONLY|O_WRONLY|O_RDWR)

I 11
/* file segment locking set data type - information passed to system by user */
struct flock {
	short	l_type;
	short	l_whence;
	size_t	l_start;
	size_t	l_len;		/* len = 0 means until end of file */
	short	l_sysid;
	int	l_pid;		/* should be pid_t */
};

E 14
E 11
I 10
#ifndef KERNEL
E 10
D 8
#if defined(__STDC__)
E 8
I 8
D 13
#if __STDC__ || c_plusplus
I 9
D 10
#ifdef KERNEL
#include "types.h"
#else
E 10
#include <sys/types.h>
D 10
#endif
E 10
E 9
E 8
E 7
D 11
extern int fcntl(int, int, int);
E 11
I 11
extern int fcntl(int, int, ...);
E 11
I 7
extern int creat(const char *, mode_t);
extern int open(const char *, int, ...);
E 7
#else
extern int fcntl();
I 7
extern int creat();
extern int open();
E 13
I 13
#include <sys/cdefs.h>

__BEGIN_DECLS
I 14
int	open __P((const char *, int, ...));
E 14
int	creat __P((const char *, mode_t));
int	fcntl __P((int, int, ...));
I 15
#ifndef _POSIX_SOURCE
int	flock __P((int, int));
#endif /* !_POSIX_SOURCE */
E 15
D 14
int	open __P((const char *, int, ...));
E 14
__END_DECLS
E 13
I 10
#endif
E 10
E 7
D 13
#endif
E 13
I 7

D 13
#endif /* !F_DUPFD */
E 13
I 13
D 21
#endif /* !_FCNTL_H_ */
E 21
I 21
#endif /* !_SYS_FCNTL_H_ */
E 21
E 13
E 7
E 6
E 2
E 1
