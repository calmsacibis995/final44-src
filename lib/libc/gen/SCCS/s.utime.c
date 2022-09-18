h41742
s 00002/00002/00029
d D 8.1 93/06/04 12:07:14 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00005/00021
d D 5.5 93/03/05 16:47:32 bostic 7 6
c POSIX 1003.1 compliant utime library call
e
s 00003/00002/00023
d D 5.4 91/02/23 19:50:16 donn 6 5
c Add include files to get prototype declarations, and fix bugs found.
e
s 00014/00014/00011
d D 5.3 90/11/28 22:20:00 bostic 5 4
c new version, using POSIX structures and include file
e
s 00002/00002/00023
d D 5.2 86/03/09 19:24:23 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00016
d D 5.1 85/05/30 10:29:39 dist 3 2
c Add copyright
e
s 00001/00000/00016
d D 4.2 83/05/31 00:13:39 sam 2 1
c include forgotten
e
s 00016/00000/00000
d D 4.1 83/05/31 00:11:38 sam 1 0
c date and time created 83/05/31 00:11:38 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
D 5
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
E 5
 */

D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4
E 3

I 2
#include <sys/time.h>
I 7

E 7
E 2
D 5
/*
 * Backwards compatible utime.
 */
E 5
I 5
#include <utime.h>
E 5

I 6
int
E 6
D 5
utime(name, otv)
	char *name;
	int otv[];
E 5
I 5
utime(path, times)
D 6
	char *path;
	struct utimbuf *times;
E 6
I 6
	const char *path;
	const struct utimbuf *times;
E 6
E 5
{
D 7
	struct timeval tv[2];
E 7
I 7
	struct timeval tv[2], *tvp;
E 7

D 5
	tv[0].tv_sec = otv[0]; tv[0].tv_usec = 0;
	tv[1].tv_sec = otv[1]; tv[1].tv_usec = 0;
	return (utimes(name, tv));
E 5
I 5
D 7
	tv[0].tv_sec = times->actime;
	tv[1].tv_sec = times->modtime;
	tv[0].tv_usec = tv[1].tv_usec = 0;
	return(utimes(path, tv));
E 7
I 7
	if (times) {
		tv[0].tv_sec = times->actime;
		tv[1].tv_sec = times->modtime;
		tv[0].tv_usec = tv[1].tv_usec = 0;
		tvp = tv;
	} else
		tvp = NULL;
	return (utimes(path, tvp));
E 7
E 5
}
E 1
