h01971
s 00002/00002/00030
d D 8.1 93/06/04 12:04:01 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00031
d D 5.6 92/05/28 00:11:43 mckusick 7 6
c need to include <sys/types.h>
e
s 00002/00000/00029
d D 5.5 91/02/23 19:49:53 donn 6 5
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00028
d D 5.4 90/06/01 14:12:28 bostic 5 4
c new copyright notice
e
s 00015/00004/00024
d D 5.3 89/07/18 18:11:45 bostic 4 3
c written by Sam Leffler; Berkeley copyright
e
s 00002/00002/00026
d D 5.2 86/03/09 19:23:21 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00019
d D 5.1 85/05/30 10:27:57 dist 2 1
c Add copyright
e
s 00020/00000/00000
d D 4.1 83/05/30 23:56:47 sam 1 0
c date and time created 83/05/30 23:56:47 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 8
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 */

D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3
E 2

I 7
#include <sys/types.h>
E 7
#include <sys/time.h>
#include <sys/resource.h>
I 6
#include <unistd.h>
E 6

/*
 * Backwards compatible nice.
 */
I 6
int
E 6
nice(incr)
	int incr;
{
	int prio;
	extern int errno;

	errno = 0;
	prio = getpriority(PRIO_PROCESS, 0);
	if (prio == -1 && errno)
		return (-1);
	return (setpriority(PRIO_PROCESS, 0, prio + incr));
}
E 1
