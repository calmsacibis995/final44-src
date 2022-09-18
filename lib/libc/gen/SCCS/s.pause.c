h63720
s 00002/00002/00021
d D 8.1 93/06/04 12:04:15 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/00018
d D 5.7 91/02/23 19:49:56 donn 8 7
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00019
d D 5.6 90/06/01 14:12:49 bostic 7 6
c new copyright notice
e
s 00015/00004/00015
d D 5.5 89/07/18 18:13:31 bostic 6 5
c written by Sam Leffler; Berkeley copyright
e
s 00001/00000/00018
d D 5.4 88/02/27 15:30:45 bostic 5 4
c 2.10BSD long/int fix
e
s 00001/00001/00017
d D 5.3 87/09/30 12:04:41 bostic 4 3
c long/int bug; bug report 4.3BSD/lib/32
e
s 00002/00002/00016
d D 5.2 86/03/09 19:23:30 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00009
d D 5.1 85/05/30 10:28:14 dist 2 1
c Add copyright
e
s 00010/00000/00000
d D 4.1 83/06/09 11:24:35 sam 1 0
c date and time created 83/06/09 11:24:35 by sam
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
D 6
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 9
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
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
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 3
E 2

I 8
#include <signal.h>
#include <unistd.h>

E 8
/*
 * Backwards compatible pause.
 */
I 8
int
E 8
pause()
{
I 5
D 8
	long sigblock();
E 8
E 5

D 4
	sigpause(sigblock(0));
E 4
I 4
D 8
	sigpause(sigblock(0L));
E 8
I 8
	return sigpause(sigblock(0L));
E 8
E 4
}
E 1
