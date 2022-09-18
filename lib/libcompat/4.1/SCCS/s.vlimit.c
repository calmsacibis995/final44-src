h34069
s 00002/00002/00044
d D 8.1 93/06/04 16:22:06 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00045
d D 5.4 92/05/28 15:03:22 mckusick 6 5
c need <systypes.h>
e
s 00006/00005/00039
d D 5.3 91/04/19 19:08:05 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00042
d D 5.2 86/03/09 19:24:33 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00035
d D 5.1 85/05/30 10:30:00 dist 3 2
c Add copyright
e
s 00002/00000/00034
d D 4.2 83/06/20 21:41:42 sam 2 1
c fix includes
e
s 00034/00000/00000
d D 4.1 83/06/20 21:39:48 sam 1 0
c date and time created 83/06/20 21:39:48 by sam
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
D 7
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.proprietary.c%
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

/*
 * (Almost) backwards compatible vlimit.
 */
I 6
#include <sys/types.h>
E 6
I 2
#include <sys/time.h>
E 2
#include <sys/resource.h>
I 2
#include <errno.h>
E 2

/* LIM_NORAISE is not emulated */
#define	LIM_NORAISE	0	/* if <> 0, can't raise limits */
#define	LIM_CPU		1	/* max secs cpu time */
#define	LIM_FSIZE	2	/* max size of file created */
#define	LIM_DATA	3	/* max growth of data space */
#define	LIM_STACK	4	/* max growth of stack */
#define	LIM_CORE	5	/* max size of ``core'' file */
#define	LIM_MAXRSS	6	/* max desired data+stack core usage */

#define	NLIMITS		6

vlimit(limit, value)
	int limit, value;
{
	struct rlimit rlim;

	if (limit <= 0 || limit > NLIMITS)
		return (EINVAL);
	if (value == -1) {
		if (getrlimit(limit - 1, &rlim) < 0)
			return (-1);
		return (rlim.rlim_cur);
	}
	rlim.rlim_cur = value;
	rlim.rlim_max = RLIM_INFINITY;
	return (setrlimit(limit - 1, &rlim));
}
E 1
