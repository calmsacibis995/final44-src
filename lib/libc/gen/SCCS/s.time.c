h08862
s 00002/00002/00024
d D 8.1 93/06/04 12:06:25 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00025
d D 5.6 90/06/01 14:16:45 bostic 8 7
c new copyright notice
e
s 00003/00006/00033
d D 5.5 89/05/17 22:33:05 bostic 7 6
c POSIX.1 specified time(2); it's not going away
e
s 00015/00004/00024
d D 5.4 88/07/18 16:48:35 bostic 6 5
c written at Berkeley when gettimeofday added; add Berkeley header
e
s 00002/00002/00026
d D 5.3 86/03/09 20:00:06 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00001/00001/00027
d D 5.2 85/10/30 17:06:25 mckusick 4 3
c time returns a long, not time_t
e
s 00009/00001/00019
d D 5.1 85/05/30 10:52:36 dist 3 2
c Add copyright
e
s 00001/00001/00019
d D 4.2 83/02/27 11:19:37 sam 2 1
c oops
e
s 00020/00000/00000
d D 4.1 83/02/24 10:17:18 sam 1 0
c date and time created 83/02/24 10:17:18 by sam
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
/*
D 6
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 9
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
 */

D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5
E 3

D 7
/*
 * Backwards compatible time call.
 */
E 7
#include <sys/types.h>
#include <sys/time.h>

D 4
time_t
E 4
I 4
D 7
long
E 7
I 7
time_t
E 7
E 4
time(t)
	time_t *t;
{
	struct timeval tt;

D 2
	if (getimeofday(&tt, (struct timezone *)0) < 0)
E 2
I 2
	if (gettimeofday(&tt, (struct timezone *)0) < 0)
E 2
D 7
		return (-1);
E 7
I 7
		return(-1);
E 7
	if (t)
		*t = tt.tv_sec;
D 7
	return (tt.tv_sec);
E 7
I 7
	return(tt.tv_sec);
E 7
}
E 1
