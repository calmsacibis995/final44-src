h55062
s 00002/00002/00037
d D 8.1 93/06/04 12:04:27 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00038
d D 5.7 93/05/16 03:32:02 torek 8 7
c keep those consts happy
e
s 00003/00003/00036
d D 5.6 91/02/23 19:49:58 donn 7 6
c Add include files to get prototype declarations, and fix bugs found.
e
s 00006/00005/00033
d D 5.5 90/11/28 00:13:12 bostic 6 5
c make error messages a little better, use constants in unistd.h
e
s 00001/00011/00037
d D 5.4 90/06/01 14:13:12 bostic 5 4
c new copyright notice
e
s 00023/00011/00025
d D 5.3 88/07/26 13:16:44 bostic 4 3
c add appropriate copyright; written by Sam Leffler
e
s 00002/00002/00034
d D 5.2 86/03/09 19:52:49 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00026
d D 5.1 85/05/30 10:48:04 dist 2 1
c Add copyright
e
s 00027/00000/00000
d D 4.1 83/02/10 22:46:00 sam 1 0
c date and time created 83/02/10 22:46:00 by sam
e
u
U
t
T
I 1
D 2
/*	%W% (Berkeley) %G%	*/
E 2
I 2
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 9
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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
/*
 * Print the name of the signal indicated
 * along with the supplied message.
 */
D 6
#include <signal.h>
E 6
I 6
#include <sys/signal.h>
I 7
#include <string.h>
E 7
#include <unistd.h>
E 6

D 7
extern	char *sys_siglist[];

E 7
I 7
void
E 7
psignal(sig, s)
D 4
	unsigned sig;
E 4
I 4
	unsigned int sig;
E 4
D 7
	char *s;
E 7
I 7
	const char *s;
E 7
{
D 8
	register char *c;
E 8
I 8
	register const char *c;
E 8
D 4
	register n;
E 4
I 4
	register int n;
E 4

D 4
	c = "Unknown signal";
E 4
	if (sig < NSIG)
		c = sys_siglist[sig];
I 4
	else
		c = "Unknown signal";
E 4
	n = strlen(s);
	if (n) {
D 4
		write(2, s, n);
		write(2, ": ", 2);
E 4
I 4
D 6
		(void)write(2, s, n);
		(void)write(2, ": ", 2);
E 6
I 6
		(void)write(STDERR_FILENO, s, n);
		(void)write(STDERR_FILENO, ": ", 2);
E 6
E 4
	}
D 4
	write(2, c, strlen(c));
	write(2, "\n", 1);
E 4
I 4
D 6
	(void)write(2, c, strlen(c));
	(void)write(2, "\n", 1);
E 6
I 6
	(void)write(STDERR_FILENO, c, strlen(c));
	(void)write(STDERR_FILENO, "\n", 1);
E 6
E 4
}
E 1
