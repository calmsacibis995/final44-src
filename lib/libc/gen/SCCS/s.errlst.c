h19877
s 00001/00001/00114
d D 8.2 93/11/16 12:11:10 bostic 21 20
c ETIMEDOUT: Connection timed out -> Operation timed out
e
s 00002/00002/00113
d D 8.1 93/06/04 12:01:30 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00113
d D 5.12 93/05/15 11:39:32 ralph 19 18
c include stdio.h so mismatch of extern definition of sys_errlist
c can be detected and fix def to match stdio.h.
e
s 00004/00002/00111
d D 5.11 92/04/29 08:51:29 bostic 18 17
c don't have to edit the output if gcc is the compiler
e
s 00001/00001/00112
d D 5.10 91/02/19 16:33:18 bostic 17 16
c POSIX requires this to be used in non-numerical situations
e
s 00001/00001/00112
d D 5.9 90/11/28 17:02:08 bostic 16 15
c EBADFORMAT -> EFTYPE
e
s 00001/00000/00112
d D 5.8 90/11/24 16:56:07 bostic 15 14
c add EBADFORMAT
e
s 00001/00001/00111
d D 5.7 90/10/22 13:44:26 mckusick 14 13
c EOPNOTSUPP => "Operation not supported"
e
s 00001/00011/00111
d D 5.6 90/06/01 14:09:58 bostic 13 12
c new copyright notice
e
s 00043/00028/00079
d D 5.5 89/09/08 16:05:53 bostic 12 11
c one more try -- POSIX and old errors at high speed
e
s 00005/00003/00102
d D 5.4 89/04/10 18:14:39 bostic 11 10
c add errno definition here, instead of perror
e
s 00017/00006/00088
d D 5.3 88/08/05 11:12:04 bostic 10 9
c 59 is unused; 61 is ECONNREFUSED not EREFUSED; add Berkeley header
e
s 00002/00002/00092
d D 5.2 86/03/09 19:45:49 donn 9 8
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00084
d D 5.1 85/05/30 10:41:02 dist 8 7
c Add copyright
e
s 00004/00004/00081
d D 4.7 84/12/04 12:20:29 karels 7 6
c update/generalize/fix error messages
e
s 00004/00000/00081
d D 4.6 82/12/19 12:36:21 sam 6 5
c update to reflect errno.h
e
s 00002/00000/00079
d D 4.5 82/05/02 14:43:02 sam 5 4
c make host errors distinct from network
e
s 00002/00000/00077
d D 4.4 82/04/01 10:32:44 root 4 3
c errors for links
e
s 00073/00044/00004
d D 4.3 82/02/11 12:04:59 root 3 2
c get rid of mpx stuff
e
s 00009/00000/00039
d D 4.2 81/09/25 13:01:04 ecc 2 1
c added bbnnet error messages
e
s 00039/00000/00000
d D 4.1 80/12/21 16:39:37 wnj 1 0
c date and time created 80/12/21 16:39:37 by wnj
e
u
U
t
T
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 8
/* %W% (Berkeley) %E% */
E 8
I 8
/*
D 10
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
D 20
 * Copyright (c) 1982, 1985 Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1982, 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 13
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 10
 */

D 9
#ifndef lint
E 9
I 9
#if defined(LIBC_SCCS) && !defined(lint)
E 9
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
D 10
#endif LIBC_SCCS and not lint
E 10
I 10
#endif /* LIBC_SCCS and not lint */
E 10
E 9

E 8
E 3
D 11
char	*sys_errlist[] = {
E 11
I 11
D 18
char *sys_errlist[] = {
E 18
I 18
D 19
#include <sys/cdefs.h>
E 19
I 19
#include <stdio.h>
E 19

D 19
char *const sys_errlist[] = {
E 19
I 19
const char *const sys_errlist[] = {
E 19
E 18
E 11
D 12
	"Error 0",
D 3
	"Not owner",
	"No such file or directory",
	"No such process",
	"Interrupted system call",
	"I/O error",
	"No such device or address",
	"Arg list too long",
	"Exec format error",
	"Bad file number",
	"No children",
	"No more processes",
	"Not enough core",
	"Permission denied",
	"Bad address",
	"Block device required",
	"Mount device busy",
	"File exists",
	"Cross-device link",
	"No such device",
	"Not a directory",
	"Is a directory",
	"Invalid argument",
	"File table overflow",
	"Too many open files",
	"Not a typewriter",
	"Text file busy",
	"File too large",
	"No space left on device",
	"Illegal seek",
	"Read-only file system",
	"Too many links",
	"Broken pipe",
	"Argument too large",
	"Result too large",
I 2
	/* bbnnet errors */
	"User status available (not an error)",
	"Open attempted when net not initialized",
	"Too many net connections",
	"No more net buffer space",
	"Error from network",
	"Error in raw link or protocol range",
	"Unable to open connection",
	"Unable to send on raw connection",
E 3
I 3
	"Not owner",				/* 1 - EPERM */
	"No such file or directory",		/* 2 - ENOENT */
	"No such process",			/* 3 - ESRCH */
	"Interrupted system call",		/* 4 - EINTR */
	"I/O error",				/* 5 - EIO */
	"No such device or address",		/* 6 - ENXIO */
	"Arg list too long",			/* 7 - E2BIG */
	"Exec format error",			/* 8 - ENOEXEC */
	"Bad file number",			/* 9 - EBADF */
	"No children",				/* 10 - ECHILD */
	"No more processes",			/* 11 - EAGAIN */
D 7
	"Not enough core",			/* 12 - ENOMEM */
E 7
I 7
	"Not enough memory",			/* 12 - ENOMEM */
E 12
I 12
	"Undefined error: 0",			/*  0 - ENOERROR */
	"Operation not permitted",		/*  1 - EPERM */
	"No such file or directory",		/*  2 - ENOENT */
	"No such process",			/*  3 - ESRCH */
	"Interrupted system call",		/*  4 - EINTR */
	"Input/output error",			/*  5 - EIO */
	"Device not configured",		/*  6 - ENXIO */
	"Argument list too long",		/*  7 - E2BIG */
	"Exec format error",			/*  8 - ENOEXEC */
	"Bad file descriptor",			/*  9 - EBADF */
	"No child processes",			/* 10 - ECHILD */
	"Resource deadlock avoided",		/* 11 - EDEADLK */
	"Cannot allocate memory",		/* 12 - ENOMEM */
E 12
E 7
	"Permission denied",			/* 13 - EACCES */
	"Bad address",				/* 14 - EFAULT */
	"Block device required",		/* 15 - ENOTBLK */
D 7
	"Mount device busy",			/* 16 - EBUSY */
E 7
I 7
	"Device busy",				/* 16 - EBUSY */
E 7
	"File exists",				/* 17 - EEXIST */
	"Cross-device link",			/* 18 - EXDEV */
D 12
	"No such device",			/* 19 - ENODEV */
E 12
I 12
	"Operation not supported by device",	/* 19 - ENODEV */
E 12
	"Not a directory",			/* 20 - ENOTDIR */
	"Is a directory",			/* 21 - EISDIR */
	"Invalid argument",			/* 22 - EINVAL */
D 12
	"File table overflow",			/* 23 - ENFILE */
E 12
I 12
	"Too many open files in system",	/* 23 - ENFILE */
E 12
	"Too many open files",			/* 24 - EMFILE */
D 7
	"Not a typewriter",			/* 25 - ENOTTY */
E 7
I 7
	"Inappropriate ioctl for device",	/* 25 - ENOTTY */
E 7
	"Text file busy",			/* 26 - ETXTBSY */
	"File too large",			/* 27 - EFBIG */
	"No space left on device",		/* 28 - ENOSPC */
	"Illegal seek",				/* 29 - ESPIPE */
	"Read-only file system",		/* 30 - EROFS */
	"Too many links",			/* 31 - EMLINK */
	"Broken pipe",				/* 32 - EPIPE */

/* math software */
D 12
	"Argument too large",			/* 33 - EDOM */
	"Result too large",			/* 34 - ERANGE */
E 12
I 12
	"Numerical argument out of domain",	/* 33 - EDOM */
D 17
	"Numerical result out of range",	/* 34 - ERANGE */
E 17
I 17
	"Result too large",			/* 34 - ERANGE */
E 17
E 12

/* non-blocking and interrupt i/o */
D 12
	"Operation would block",		/* 35 - EWOULDBLOCK */
E 12
I 12
	"Resource temporarily unavailable",	/* 35 - EAGAIN */
						/* 35 - EWOULDBLOCK */
E 12
	"Operation now in progress",		/* 36 - EINPROGRESS */
	"Operation already in progress",	/* 37 - EALREADY */

D 12
/* ipc/network software */

	/* argument errors */
E 12
I 12
/* ipc/network software -- argument errors */
E 12
	"Socket operation on non-socket",	/* 38 - ENOTSOCK */
	"Destination address required",		/* 39 - EDESTADDRREQ */
	"Message too long",			/* 40 - EMSGSIZE */
	"Protocol wrong type for socket",	/* 41 - EPROTOTYPE */
D 7
	"Protocol not available",		/* 42 - ENOPROTOOPT */
E 7
I 7
D 12
	"Option not supported by protocol",	/* 42 - ENOPROTOOPT */
E 12
I 12
	"Protocol not available",		/* 42 - ENOPROTOOPT */
E 12
E 7
	"Protocol not supported",		/* 43 - EPROTONOSUPPORT */
	"Socket type not supported",		/* 44 - ESOCKTNOSUPPORT */
D 14
	"Operation not supported on socket",	/* 45 - EOPNOTSUPP */
E 14
I 14
	"Operation not supported",		/* 45 - EOPNOTSUPP */
E 14
	"Protocol family not supported",	/* 46 - EPFNOSUPPORT */
D 12
	"Address family not supported by protocol family",
E 12
						/* 47 - EAFNOSUPPORT */
I 12
	"Address family not supported by protocol family",
E 12
	"Address already in use",		/* 48 - EADDRINUSE */
	"Can't assign requested address",	/* 49 - EADDRNOTAVAIL */

D 11
	/* operational errors */
E 11
I 11
D 12
/* operational errors */

E 12
I 12
/* ipc/network software -- operational errors */
E 12
E 11
	"Network is down",			/* 50 - ENETDOWN */
	"Network is unreachable",		/* 51 - ENETUNREACH */
	"Network dropped connection on reset",	/* 52 - ENETRESET */
	"Software caused connection abort",	/* 53 - ECONNABORTED */
	"Connection reset by peer",		/* 54 - ECONNRESET */
	"No buffer space available",		/* 55 - ENOBUFS */
	"Socket is already connected",		/* 56 - EISCONN */
	"Socket is not connected",		/* 57 - ENOTCONN */
	"Can't send after socket shutdown",	/* 58 - ESHUTDOWN */
D 10
	"Too many references: can't splice",	/* 59 - ETOOMANYREFS */
E 10
I 10
D 12
	"Error 59",				/* 59 - unused */
E 12
I 12
	"Too many references: can't splice",	/* 59 - ETOOMANYREFS */
E 12
E 10
D 21
	"Connection timed out",			/* 60 - ETIMEDOUT */
E 21
I 21
	"Operation timed out",			/* 60 - ETIMEDOUT */
E 21
D 10
	"Connection refused",			/* 61 - EREFUSED */
E 10
I 10
	"Connection refused",			/* 61 - ECONNREFUSED */
I 12

E 12
E 10
I 4
	"Too many levels of symbolic links",	/* 62 - ELOOP */
	"File name too long",			/* 63 - ENAMETOOLONG */
I 12

/* should be rearranged */
E 12
I 5
	"Host is down",				/* 64 - EHOSTDOWN */
D 12
	"Host is unreachable",			/* 65 - EHOSTUNREACH */
E 12
I 12
	"No route to host",			/* 65 - EHOSTUNREACH */
E 12
I 6
	"Directory not empty",			/* 66 - ENOTEMPTY */
I 12

/* quotas & mush */
E 12
	"Too many processes",			/* 67 - EPROCLIM */
	"Too many users",			/* 68 - EUSERS */
	"Disc quota exceeded",			/* 69 - EDQUOT */
I 12

/* Network File System */
	"Stale NFS file handle",		/* 70 - ESTALE */
	"Too many levels of remote in path",	/* 71 - EREMOTE */
	"RPC struct is bad",			/* 72 - EBADRPC */
	"RPC version wrong",			/* 73 - ERPCMISMATCH */
	"RPC prog. not avail",			/* 74 - EPROGUNAVAIL */
	"Program version wrong",		/* 75 - EPROGMISMATCH */
	"Bad procedure for program",		/* 76 - EPROCUNAVAIL */

	"No locks available",			/* 77 - ENOLCK */
	"Function not implemented",		/* 78 - ENOSYS */
I 15
D 16
	"Incorrect format",			/* 79 - EBADFORMAT */
E 16
I 16
	"Inappropriate file type or format",	/* 79 - EFTYPE */
E 16
E 15
E 12
E 6
E 5
E 4
E 3
E 2
};
D 11
int	sys_nerr = { sizeof sys_errlist/sizeof sys_errlist[0] };
E 11
I 11
D 12
int sys_nerr = { sizeof sys_errlist/sizeof sys_errlist[0] };
E 12
int errno;
I 12
D 18
int sys_nerr = { sizeof sys_errlist/sizeof sys_errlist[0] };
E 18
I 18
const int sys_nerr = sizeof(sys_errlist) / sizeof(sys_errlist[0]);
E 18
E 12
E 11
E 1
