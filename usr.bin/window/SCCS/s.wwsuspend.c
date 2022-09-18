h12056
s 00002/00002/00028
d D 8.1 93/06/06 22:33:09 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00004/00029
d D 3.17 92/11/10 11:49:51 edward 24 23
c checkpointing stuff
e
s 00001/00001/00032
d D 3.16 92/08/16 17:43:36 edward 23 22
c changes from Brian Buhrow, primitive yank and put, Posix MIN and TIME,
c and others
e
s 00001/00000/00032
d D 3.15 90/08/12 15:27:34 edward 22 21
c lint
e
s 00001/00001/00031
d D 3.14 90/08/12 15:25:58 edward 21 20
c switch to POSIX tty, old code still supported under OLD_TTY
e
s 00003/00000/00029
d D 3.13 90/06/06 21:45:54 bostic 20 19
c fix contrib notice (Edward Wang)
e
s 00001/00011/00028
d D 3.12 90/06/02 15:25:41 bostic 19 18
c new copyright notice
e
s 00001/00001/00038
d D 3.11 89/10/03 15:23:39 bostic 18 16
c POSIX signals
e
s 00001/00001/00038
d R 3.11 89/08/23 20:11:28 edward 17 16
c sig_t
e
s 00002/00002/00037
d D 3.10 89/08/02 19:13:00 edward 16 15
c data compression and some other stuff
e
s 00010/00005/00029
d D 3.9 88/06/29 21:38:54 bostic 15 14
c install approved copyright notice
e
s 00013/00007/00021
d D 3.8 88/02/21 13:38:58 bostic 14 13
c written by Edward Wang; attach Berkeley specific copyright
e
s 00006/00000/00022
d D 3.7 85/04/24 16:18:45 edward 13 12
c copyright messages
e
s 00001/00001/00021
d D 3.6 84/11/20 23:40:29 edward 12 11
c we don't flush typeahead any more
e
s 00001/00001/00021
d D 3.5 84/05/23 01:59:40 edward 11 10
c new sccs id
e
s 00001/00001/00021
d D 3.4 84/04/16 20:28:59 edward 10 9
c 4.1a, 4.1c compatibility removed, local.h added
e
s 00005/00007/00017
d D 3.3 83/11/02 11:07:55 edward 9 8
c flags for different machines.
e
s 00002/00001/00022
d D 3.2 83/08/15 18:14:25 edward 8 7
c tt cleanup
e
s 00000/00000/00023
d D 3.1 83/08/11 17:22:00 edward 7 5
i 6
c last few day's work
e
s 00009/00008/00014
d D 2.1.1.1 83/08/09 18:35:16 edward 6 5
c mile stone
e
s 00000/00000/00022
d D 2.1 83/07/30 13:27:17 edward 5 4
c prepare for major change
e
s 00000/00000/00022
d D 1.4 83/07/22 17:09:43 edward 4 3
c scrolling.
c uses Wscreensize() to get screen size.
c More intelligent framing.
c etc.
e
s 00000/00000/00022
d D 1.3 83/07/19 20:07:58 edward 3 2
c today's work
e
s 00000/00000/00022
d D 1.2 83/07/18 21:03:57 edward 2 1
c multiple window
e
s 00022/00000/00000
d D 1.1 83/07/17 15:19:06 edward 1 0
c date and time created 83/07/17 15:19:06 by edward
e
u
U
f b 
t
T
I 1
D 14
#ifndef lint
D 11
static	char *sccsid = "%W% %E%";
E 11
I 11
static char sccsid[] = "%W% %G%";
E 11
#endif

E 14
I 13
/*
D 14
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 14
I 14
D 25
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
I 20
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 20
D 19
 * Redistribution and use in source and binary forms are permitted
D 15
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 15
I 15
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 15
E 14
 */
I 14

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 14

E 13
#include "ww.h"
I 8
#include "tt.h"
E 8
D 10
#include <signal.h>
E 10
I 10
#include <sys/signal.h>
E 10

I 22
D 24
void
E 24
E 22
D 6
#define mask(s)	(1<<(SIG/**/s-1))
E 6
I 6
D 9
#define mask(s)	(1 << (s) - 1)
E 6

E 9
wwsuspend()
{
D 9
	int oldmask;
E 9
I 9
D 18
	int (*oldsig)();
E 18
I 18
	sig_t oldsig;
E 18
E 9

D 6
	oldmask = sigblock(mask(TSTP));
E 6
I 6
D 9
	oldmask = sigblock(mask(SIGTSTP));
E 9
I 9
	oldsig = signal(SIGTSTP, SIG_IGN);
E 9
E 6
D 23
	wwend();
E 23
I 23
	wwend(0);
E 23
D 6
	sigsetmask(sigblock(0) & ~mask(TSTP));
	kill(0, SIGTSTP);
	sigblock(mask(TSTP));
	wwsettty(0, &wwnewtty);
	Winit(2, 1);
	sigsetmask(oldmask);
E 6
I 6
D 9
	(void) sigsetmask(sigblock(0) & ~mask(SIGTSTP));
E 9
I 9
	(void) signal(SIGTSTP, SIG_DFL);
E 9
	(void) kill(0, SIGTSTP);
D 9
	(void) sigblock(mask(SIGTSTP));
E 9
I 9
	(void) signal(SIGTSTP, SIG_IGN);
E 9
D 12
	(void) wwsettty(0, &wwnewtty);
E 12
I 12
D 21
	(void) wwsettty(0, &wwnewtty, &wwoldtty);
E 21
I 21
D 24
	(void) wwsettty(0, &wwnewtty);
E 21
E 12
D 8
	(*tt.tt_reset)();
E 8
I 8
D 16
	(*tt.tt_init)();
E 8
	wwredraw();
E 16
I 16
	xxstart();
	wwredraw();		/* XXX, clears the screen twice */
E 24
I 24
	wwstart();
E 24
E 16
D 9
	(void) sigsetmask(oldmask);
E 9
I 9
	(void) signal(SIGTSTP, oldsig);
E 9
E 6
}
E 1
