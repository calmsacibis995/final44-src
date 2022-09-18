h41411
s 00002/00002/00037
d D 8.1 93/06/04 13:04:22 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00038
d D 5.11 91/02/23 22:56:31 donn 12 11
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00001/00011/00037
d D 5.10 90/06/01 14:43:45 bostic 11 10
c new copyright notice
e
s 00001/00000/00047
d D 5.9 90/05/17 15:19:09 bostic 10 9
c declare abort correctly
e
s 00013/00005/00029
d D 5.8 90/05/16 09:43:16 bostic 9 8
c use POSIX signal calls
e
s 00005/00001/00029
d D 5.7 90/05/15 22:29:40 bostic 8 7
c ANSI says that programs can catch the abort signal
e
s 00003/00003/00027
d D 5.6 89/08/26 17:00:56 karels 7 6
c posix signals
e
s 00019/00010/00011
d D 5.5 88/08/02 17:42:28 bostic 6 5
c lint cleanup, add Berkeley specific header
e
s 00001/00001/00020
d D 5.4 87/09/30 12:18:53 bostic 5 4
c long/int bug; bug report 4.3BSD/lib/25
e
s 00002/00002/00019
d D 5.3 86/03/09 19:43:59 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00002/00002/00019
d D 5.2 85/07/26 17:43:57 karels 3 2
c Really, let's not shoot all our friends
e
s 00009/00001/00012
d D 5.1 85/05/30 10:40:16 dist 2 1
c Add copyright
e
s 00013/00000/00000
d D 4.1 85/01/24 14:29:08 ralph 1 0
c date and time created 85/01/24 14:29:08 by ralph
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
D 3
 * Copyright (c) 1980 Regents of the University of California.
E 3
I 3
D 13
 * Copyright (c) 1985 Regents of the University of California.
E 3
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 6
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
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 4
E 2

D 6
/* C library -- abort */
E 6
I 6
D 8
#include <signal.h>
E 8
I 8
#include <sys/signal.h>
I 9
#include <stdlib.h>
#include <stddef.h>
I 12
#include <unistd.h>
E 12
E 9
E 8
E 6

I 10
void
E 10
D 6
#include "signal.h"

E 6
abort()
{
D 5
	sigblock(~0);
E 5
I 5
D 6
	sigblock(~0L);
E 5
	signal(SIGILL, SIG_DFL);
	sigsetmask(~sigmask(SIGILL));
D 3
	kill(0, SIGILL);
E 3
I 3
	kill(getpid(), SIGILL);
E 6
I 6
D 9
	(void)sigblock(~0L);
I 8
	(void)sigsetmask(~sigmask(SIGABRT));
	/* leave catch function active to give program a crack at it */
E 9
I 9
	sigset_t mask;

	sigfillset(&mask);
	/*
	 * don't block SIGABRT to give any handler a chance; we ignore
	 * any errors -- X311J doesn't allow abort to return anyway.
	 */
	sigdelset(&mask, SIGABRT);
	(void)sigprocmask(SIG_SETMASK, &mask, (sigset_t *)NULL);
E 9
	(void)kill(getpid(), SIGABRT);
D 9
	/* if we got here, it was no good; reset to default and stop */
E 9
I 9

	/*
	 * if SIGABRT ignored, or caught and the handler returns, do
	 * it again, only harder.
	 */
E 9
E 8
D 7
	(void)signal(SIGILL, SIG_DFL);
	(void)sigsetmask(~sigmask(SIGILL));
	(void)kill(getpid(), SIGILL);
E 7
I 7
	(void)signal(SIGABRT, SIG_DFL);
D 9
	(void)sigsetmask(~sigmask(SIGABRT));
E 9
I 9
	(void)sigprocmask(SIG_SETMASK, &mask, (sigset_t *)NULL);
E 9
	(void)kill(getpid(), SIGABRT);
I 9
	exit(1);
E 9
E 7
E 6
E 3
}
E 1
