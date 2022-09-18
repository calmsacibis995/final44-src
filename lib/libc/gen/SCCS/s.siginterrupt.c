h35882
s 00002/00002/00033
d D 8.1 93/06/04 12:05:11 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00034
d D 5.5 90/06/01 14:15:43 bostic 6 5
c new copyright notice
e
s 00012/00008/00033
d D 5.4 89/08/26 17:00:54 karels 5 4
c posix signals
e
s 00017/00006/00024
d D 5.3 88/08/02 17:48:53 bostic 4 3
c lint cleanup, add Berkeley specific header
e
s 00002/00002/00028
d D 5.2 86/03/09 19:56:14 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00021
d D 5.1 85/06/05 12:34:30 mckusick 2 1
c Add copyright
e
s 00022/00000/00000
d D 4.1 85/03/11 22:32:11 mckusick 1 0
c date and time created 85/03/11 22:32:11 by mckusick
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
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 5
 * Copyright (c) 1988 Regents of the University of California.
E 5
I 5
D 7
 * Copyright (c) 1989 Regents of the University of California.
E 5
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
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

#include <signal.h>

/*
 * Set signal state to prevent restart of system calls
 * after an instance of the indicated signal.
 */
siginterrupt(sig, flag)
	int sig, flag;
{
D 5
	struct sigvec sv;
E 5
I 5
	extern sigset_t _sigintr;
	struct sigaction sa;
E 5
	int ret;

D 4
	if ((ret = sigvec(sig, 0, &sv)) < 0)
E 4
I 4
D 5
	if ((ret = sigvec(sig, (struct sigvec *)0, &sv)) < 0)
E 5
I 5
	if ((ret = sigaction(sig, (struct sigaction *)0, &sa)) < 0)
E 5
E 4
		return (ret);
D 5
	if (flag)
		sv.sv_flags |= SV_INTERRUPT;
	else
		sv.sv_flags &= ~SV_INTERRUPT;
D 4
	return (sigvec(sig, &sv, 0));
E 4
I 4
	return (sigvec(sig, &sv, (struct sigvec *)0));
E 5
I 5
	if (flag) {
		sigaddset(&_sigintr, sig);
		sa.sa_flags &= ~SA_RESTART;
	} else {
		sigdelset(&_sigintr, sig);
		sa.sa_flags |= SA_RESTART;
	}
	return (sigaction(sig, &sa, (struct sigaction *)0));
E 5
E 4
}
E 1
