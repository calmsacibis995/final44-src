h24453
s 00005/00000/00132
d D 8.5 94/01/21 17:25:07 bostic 26 25
c add USL's copyright notice
e
s 00001/00001/00131
d D 8.4 94/01/06 09:22:19 bostic 25 24
c bring comment up to date with C library change of awhile ago
e
s 00001/00001/00131
d D 8.3 94/01/04 15:00:28 bostic 24 23
c EBUSY is defined by POSIX.1
e
s 00001/00001/00131
d D 8.2 93/11/16 12:10:10 bostic 23 22
c ETIMEDOUT: Connection timed out -> Operation timed out
e
s 00002/00002/00130
d D 8.1 93/06/02 19:53:21 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00127
d D 7.14 92/01/09 21:57:53 mckusick 21 20
c new errors for authentication failures
e
s 00001/00001/00126
d D 7.13 91/02/19 16:32:16 bostic 20 19
c POSIX requires this to be used in non-numerical situations
e
s 00001/00001/00126
d D 7.12 90/11/28 17:01:18 bostic 19 18
c EBADFORMAT -> EFTYPE
e
s 00002/00000/00125
d D 7.11 90/11/24 16:56:26 bostic 18 17
c add EBADFORMAT
e
s 00001/00011/00124
d D 7.10 90/06/28 21:58:43 bostic 17 16
c new copyright notice
e
s 00004/00000/00131
d D 7.9 90/05/15 19:20:04 bostic 16 15
c ANSI C requires errno to be defined here
e
s 00006/00000/00125
d D 7.8 90/04/04 22:18:36 karels 15 14
c add ERESTART, EJUSTRETURN pseudos for modifying return from syscall
e
s 00012/00015/00113
d D 7.7 89/09/08 16:05:47 bostic 14 13
c one more try -- POSIX and old errors at high speed
e
s 00019/00019/00109
d D 7.6 89/09/04 14:16:11 karels 13 12
c fix EDEADLK correctly (must be different than EAGAIN);
c put back most of the old comments
e
s 00003/00005/00125
d D 7.5 89/08/21 12:15:46 bostic 12 11
c wrong order for POSIX_SOURCE; bug report 4.3BSD/sys/238
e
s 00032/00021/00098
d D 7.4 89/05/24 19:43:03 bostic 11 10
c POSIX 1003.1; add ENOLCK, ENOSYS
e
s 00023/00003/00096
d D 7.3 89/05/09 16:16:57 mckusick 10 9
c additions from Rick Macklem for NFS
e
s 00002/00001/00097
d D 7.2 89/05/01 23:20:04 marc 9 8
c change value of EAGAIN to that of EWOULDBLOCK for POSIX. (yuck)
e
s 00001/00001/00097
d D 7.1 86/06/04 23:22:11 mckusick 8 7
c 4.3BSD release version
e
s 00002/00000/00096
d D 6.5 86/02/02 21:32:50 karels 7 6
c compatibility with those other people
e
s 00000/00000/00096
d D 6.4 85/06/19 12:23:58 mckusick 6 5
x 4
c get rid of -r6.2 as it causes problems for libc .s routines
e
s 00007/00001/00099
d D 6.3 85/06/08 14:56:43 mckusick 5 4
c Add copyright
e
s 00010/00000/00090
d D 6.2 85/06/02 18:34:04 bloom 4 2
c add user variables for accessing error codes
e
s 00010/00000/00090
d R 6.2 85/06/02 18:20:07 bloom 3 2
c add the user variables for accessing errors
e
s 00000/00000/00090
d D 6.1 83/07/29 06:12:13 sam 2 1
c 4.2 distribution
e
s 00090/00000/00000
d D 4.1 82/12/28 22:57:13 sam 1 0
c date and time created 82/12/28 22:57:13 by sam
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 8
 * Copyright (c) 1982 Regents of the University of California.
E 8
I 8
D 10
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
D 22
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 26
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 26
E 22
E 10
 *
I 10
D 17
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 17
I 17
 * %sccs.include.redist.c%
E 17
 *
E 10
 *	%W% (Berkeley) %G%
 */
E 5

I 16
#ifndef KERNEL
extern int errno;			/* global error number */
#endif

E 16
D 11
/*
 * Error codes
 */

#define	EPERM		1		/* Not owner */
E 11
I 11
D 13
#define	EPERM		1		/* Operation not permitted */
E 13
I 13
D 14
#define	EPERM		1		/* Not owner */
E 14
I 14
#define	EPERM		1		/* Operation not permitted */
E 14
E 13
E 11
#define	ENOENT		2		/* No such file or directory */
#define	ESRCH		3		/* No such process */
D 11
#define	EINTR		4		/* Interrupted system call */
#define	EIO		5		/* I/O error */
E 11
I 11
D 13
#define	EINTR		4		/* Interrupted function call */
#define	EIO		5		/* Input/output error */
E 13
I 13
#define	EINTR		4		/* Interrupted system call */
D 14
#define	EIO		5		/* I/O error */
E 13
E 11
#define	ENXIO		6		/* No such device or address */
#define	E2BIG		7		/* Arg list too long */
E 14
I 14
#define	EIO		5		/* Input/output error */
#define	ENXIO		6		/* Device not configured */
#define	E2BIG		7		/* Argument list too long */
E 14
#define	ENOEXEC		8		/* Exec format error */
D 11
#define	EBADF		9		/* Bad file number */
#define	ECHILD		10		/* No children */
E 11
I 11
#define	EBADF		9		/* Bad file descriptor */
D 13
#define	ECHILD		10		/* No child processes */
E 11
D 9
#define	EAGAIN		11		/* No more processes */
E 9
I 9
					/* 11 - was EAGAIN */
E 9
D 11
#define	ENOMEM		12		/* Not enough core */
E 11
I 11
#define	ENOMEM		12		/* Not enough space */
E 13
I 13
D 14
#define	ECHILD		10		/* No children */
E 14
I 14
#define	ECHILD		10		/* No child processes */
E 14
#define	EDEADLK		11		/* Resource deadlock avoided */
					/* 11 was EAGAIN */
D 14
#define	ENOMEM		12		/* Not enough memory */
E 14
I 14
#define	ENOMEM		12		/* Cannot allocate memory */
E 14
E 13
E 11
#define	EACCES		13		/* Permission denied */
#define	EFAULT		14		/* Bad address */
I 11
#ifndef _POSIX_SOURCE
E 11
#define	ENOTBLK		15		/* Block device required */
I 13
D 24
#define	EBUSY		16		/* Device busy */
E 24
E 13
D 11
#define	EBUSY		16		/* Mount device busy */
E 11
I 11
#endif
I 24
#define	EBUSY		16		/* Device busy */
E 24
D 13
#define	EBUSY		16		/* Resource busy */
E 13
E 11
#define	EEXIST		17		/* File exists */
D 11
#define	EXDEV		18		/* Cross-device link */
E 11
I 11
D 13
#define	EXDEV		18		/* Improper link */
E 13
I 13
#define	EXDEV		18		/* Cross-device link */
E 13
E 11
D 14
#define	ENODEV		19		/* No such device */
E 14
I 14
#define	ENODEV		19		/* Operation not supported by device */
E 14
D 11
#define	ENOTDIR		20		/* Not a directory*/
E 11
I 11
#define	ENOTDIR		20		/* Not a directory */
E 11
#define	EISDIR		21		/* Is a directory */
#define	EINVAL		22		/* Invalid argument */
D 11
#define	ENFILE		23		/* File table overflow */
E 11
I 11
D 13
#define	ENFILE		23		/* Too many open files in system */
E 13
I 13
D 14
#define	ENFILE		23		/* File table overflow */
E 14
I 14
#define	ENFILE		23		/* Too many open files in system */
E 14
E 13
E 11
#define	EMFILE		24		/* Too many open files */
D 11
#define	ENOTTY		25		/* Not a typewriter */
E 11
I 11
D 13
#define	ENOTTY		25		/* Inappropriate I/O control op. */
E 13
I 13
#define	ENOTTY		25		/* Inappropriate ioctl for device */
E 13
#ifndef _POSIX_SOURCE
E 11
#define	ETXTBSY		26		/* Text file busy */
I 11
#endif
E 11
#define	EFBIG		27		/* File too large */
#define	ENOSPC		28		/* No space left on device */
D 11
#define	ESPIPE		29		/* Illegal seek */
E 11
I 11
D 13
#define	ESPIPE		29		/* Invalid seek */
E 13
I 13
#define	ESPIPE		29		/* Illegal seek */
E 13
E 11
#define	EROFS		30		/* Read-only file system */
#define	EMLINK		31		/* Too many links */
#define	EPIPE		32		/* Broken pipe */

/* math software */
D 11
#define	EDOM		33		/* Argument too large */
E 11
I 11
D 13
#define	EDOM		33		/* Domain error */
E 13
I 13
D 14
#define	EDOM		33		/* Argument too large */
E 13
E 11
#define	ERANGE		34		/* Result too large */
E 14
I 14
#define	EDOM		33		/* Numerical argument out of domain */
D 20
#define	ERANGE		34		/* Numerical result out of range */
E 20
I 20
#define	ERANGE		34		/* Result too large */
E 20
E 14

/* non-blocking and interrupt i/o */
I 12
D 13
#define	EDEADLK		35		/* Resource deadlock avoided */
#define	EAGAIN		EDEADLK		/* Resource temporarily unavailable */
E 13
I 13
#define	EAGAIN		35		/* Resource temporarily unavailable */
E 13
E 12
I 11
#ifndef _POSIX_SOURCE
E 11
D 12
#define	EWOULDBLOCK	35		/* Operation would block */
I 7
D 11
#define	EDEADLK		EWOULDBLOCK	/* ditto */
I 9
#define EAGAIN		EWOULDBLOCK	/* or No Resources (fork failed) */
E 11
I 11
#endif
#define	EDEADLK		EWOULDBLOCK	/* Resource deadlock avoided */
#define	EAGAIN		EWOULDBLOCK	/* Resource temporarily unavailable */
#ifndef _POSIX_SOURCE
E 12
I 12
D 13
#define	EWOULDBLOCK	EDEADLK		/* Operation would block */
E 13
I 13
#define	EWOULDBLOCK	EAGAIN		/* Operation would block */
E 13
E 12
E 11
E 9
E 7
#define	EINPROGRESS	36		/* Operation now in progress */
#define	EALREADY	37		/* Operation already in progress */
I 7

E 7
D 14
/* ipc/network software */

	/* argument errors */
E 14
I 14
/* ipc/network software -- argument errors */
E 14
#define	ENOTSOCK	38		/* Socket operation on non-socket */
#define	EDESTADDRREQ	39		/* Destination address required */
#define	EMSGSIZE	40		/* Message too long */
#define	EPROTOTYPE	41		/* Protocol wrong type for socket */
#define	ENOPROTOOPT	42		/* Protocol not available */
#define	EPROTONOSUPPORT	43		/* Protocol not supported */
#define	ESOCKTNOSUPPORT	44		/* Socket type not supported */
D 25
#define	EOPNOTSUPP	45		/* Operation not supported on socket */
E 25
I 25
#define	EOPNOTSUPP	45		/* Operation not supported */
E 25
#define	EPFNOSUPPORT	46		/* Protocol family not supported */
#define	EAFNOSUPPORT	47		/* Address family not supported by protocol family */
#define	EADDRINUSE	48		/* Address already in use */
#define	EADDRNOTAVAIL	49		/* Can't assign requested address */

D 14
	/* operational errors */
E 14
I 14
/* ipc/network software -- operational errors */
E 14
#define	ENETDOWN	50		/* Network is down */
#define	ENETUNREACH	51		/* Network is unreachable */
#define	ENETRESET	52		/* Network dropped connection on reset */
#define	ECONNABORTED	53		/* Software caused connection abort */
#define	ECONNRESET	54		/* Connection reset by peer */
#define	ENOBUFS		55		/* No buffer space available */
#define	EISCONN		56		/* Socket is already connected */
#define	ENOTCONN	57		/* Socket is not connected */
#define	ESHUTDOWN	58		/* Can't send after socket shutdown */
#define	ETOOMANYREFS	59		/* Too many references: can't splice */
D 23
#define	ETIMEDOUT	60		/* Connection timed out */
E 23
I 23
#define	ETIMEDOUT	60		/* Operation timed out */
E 23
#define	ECONNREFUSED	61		/* Connection refused */

D 14
	/* */
E 14
#define	ELOOP		62		/* Too many levels of symbolic links */
D 11
#define	ENAMETOOLONG	63		/* File name too long */
E 11
I 11
D 13
#endif
#define	ENAMETOOLONG	63		/* Filename too long */
E 13
I 13
#endif /* _POSIX_SOURCE */
#define	ENAMETOOLONG	63		/* File name too long */
E 13
E 11

/* should be rearranged */
I 11
#ifndef _POSIX_SOURCE
E 11
#define	EHOSTDOWN	64		/* Host is down */
#define	EHOSTUNREACH	65		/* No route to host */
I 11
D 13
#endif
E 13
I 13
#endif /* _POSIX_SOURCE */
E 13
E 11
#define	ENOTEMPTY	66		/* Directory not empty */

/* quotas & mush */
I 11
#ifndef _POSIX_SOURCE
E 11
#define	EPROCLIM	67		/* Too many processes */
#define	EUSERS		68		/* Too many users */
#define	EDQUOT		69		/* Disc quota exceeded */
I 10

/* Network File System */
#define	ESTALE		70		/* Stale NFS file handle */
D 11
#define	EREMOTE         71		/* Too many levels of remote in path */
E 11
I 11
#define	EREMOTE		71		/* Too many levels of remote in path */
E 11
#define	EBADRPC		72		/* RPC struct is bad */
#define	ERPCMISMATCH	73		/* RPC version wrong */
#define	EPROGUNAVAIL	74		/* RPC prog. not avail */
#define	EPROGMISMATCH	75		/* Program version wrong */
#define	EPROCUNAVAIL	76		/* Bad procedure for program */
I 11
D 13
#endif
E 13
I 13
#endif /* _POSIX_SOURCE */
E 13

#define	ENOLCK		77		/* No locks available */
#define	ENOSYS		78		/* Function not implemented */
I 15

I 21
#ifndef _POSIX_SOURCE
E 21
I 18
D 19
#define	EBADFORMAT	79		/* Incorrect format */
E 19
I 19
#define	EFTYPE		79		/* Inappropriate file type or format */
I 21
#define	EAUTH		80		/* Authentication error */
#define	ENEEDAUTH	81		/* Need authenticator */
#define	ELAST		81		/* Must be equal largest errno */
#endif /* _POSIX_SOURCE */
E 21
E 19

E 18
#ifdef KERNEL
/* pseudo-errors returned inside kernel to modify return to process */
#define	ERESTART	-1		/* restart syscall */
#define	EJUSTRETURN	-2		/* don't modify regs, just return */
#endif
E 15
E 11
E 10
I 4

/*
 * User variables for accessing the error codes
 */

#ifndef KERNEL
extern int errno;
extern int sys_nerr;
extern char *sys_errlist[];
#endif
E 4
E 1
