h19285
s 00002/00002/00063
d D 8.1 93/06/06 22:32:57 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00003/00054
d D 3.14 92/11/10 11:49:58 edward 16 15
c checkpointing stuff
e
s 00007/00000/00050
d D 3.13 92/08/16 19:22:51 edward 15 12
c changes from Brian Buhrow, primitive yank and put, Posix MIN and TIME,
c and others
e
s 00007/00000/00050
d R 3.13 92/08/16 19:21:58 edward 14 12
c changes from Brian Buhrow, primitive yank and put, Posix MIN and TIME,
e
s 00007/00000/00050
d R 3.13 92/08/16 17:43:38 edward 13 12
c changes from Brian Buhrow, primitive yank and put, Posix MIN and TIME,
c and others
e
s 00004/00001/00046
d D 3.12 92/06/24 14:58:00 edward 12 11
c input error correction stuff
e
s 00001/00000/00046
d D 3.11 91/03/02 13:40:34 bostic 11 10
c ANSI
e
s 00003/00000/00043
d D 3.10 90/06/06 21:45:48 bostic 10 9
c fix contrib notice (Edward Wang)
e
s 00001/00011/00042
d D 3.9 90/06/02 15:25:21 bostic 9 8
c new copyright notice
e
s 00000/00001/00053
d D 3.8 89/10/13 17:19:55 edward 8 7
c include cleanup
e
s 00010/00005/00044
d D 3.7 88/06/29 21:38:44 bostic 7 6
c install approved copyright notice
e
s 00013/00007/00036
d D 3.6 88/02/21 13:38:51 bostic 6 5
c written by Edward Wang; attach Berkeley specific copyright
e
s 00002/00007/00041
d D 3.5 87/06/08 02:28:11 edward 5 4
c interrupt mechanism reworked, make SIGCHLD interrupt also
e
s 00006/00000/00042
d D 3.4 85/04/24 16:19:05 edward 4 3
c copyright messages
e
s 00001/00001/00041
d D 3.3 84/05/23 01:59:48 edward 3 2
c new sccs id
e
s 00001/00001/00041
d D 3.2 84/04/16 20:29:10 edward 2 1
c 4.1a, 4.1c compatibility removed, local.h added
e
s 00042/00000/00000
d D 3.1 84/03/03 22:50:24 edward 1 0
c date and time created 84/03/03 22:50:24 by edward
e
u
U
t
T
I 1
D 6
#ifndef lint
D 3
static	char *sccsid = "%W% %E%";
E 3
I 3
static char sccsid[] = "%W% %G%";
E 3
#endif

E 6
I 4
/*
D 6
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 6
I 6
D 17
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
I 10
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 10
D 9
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 7
E 6
 */
I 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

E 4
#include "ww.h"
I 12
#include "tt.h"
I 15
#if defined(OLD_TTY) || defined(VMIN_BUG)
E 15
E 12
#include <fcntl.h>
I 15
#endif
E 15
D 8
#include <sys/signal.h>
E 8

/*
 * Tty input interrupt handler.
 * (1) Read input into buffer (wwib*).
D 5
 * (2) If the flag wwsetjmp is true, do longjmp(wwjmpbuf) for asyncronous
 *     actions, and to avoid race conditions, clear wwsetjmp.
E 5
I 5
 * (2) Set the interrupt flag if anything is read.
E 5
 * Currently, the last is used to get out of the blocking
 * select() in wwiomux().
 * To avoid race conditions, we only modify wwibq in here, except
 * when the buffer is empty; and everywhere else, we only change wwibp.
 * It should be completely safe.
 */
I 11
void
E 11
wwrint()
{
	register n;

	if (wwibp == wwibq)
		wwibp = wwibq = wwib;
	wwnread++;
I 15
#if defined(OLD_TTY) || defined(VMIN_BUG)
	/* we have set c_cc[VMIN] to 0 */
E 15
D 12
	(void) fcntl(0, F_SETFL, FNDELAY|wwnewtty.ww_fflags);
E 12
I 12
	(void) fcntl(0, F_SETFL, O_NONBLOCK|wwnewtty.ww_fflags);
I 15
#endif
E 15
E 12
	n = read(0, wwibq, wwibe - wwibq);
I 15
#if defined(OLD_TTY) || defined(VMIN_BUG)
E 15
	(void) fcntl(0, F_SETFL, wwnewtty.ww_fflags);
I 15
#endif
E 15
	if (n > 0) {
I 12
		if (tt.tt_rint)
			n = (*tt.tt_rint)(wwibq, n);
E 12
D 16
		wwibq += n;
		wwnreadc += n;
I 5
		wwsetintr();
E 16
I 16
		if (n > 0) {
			wwibq += n;
			wwnreadc += n;
			/*
			 * Hasten or delay the next checkpoint,
			 * as the case may be.
			 */
			if (tt.tt_checkpoint && !wwdocheckpoint)
				(void) alarm(1);
			wwsetintr();
		}
E 16
E 5
	} else if (n == 0)
		wwnreadz++;
	else
		wwnreade++;
D 5
	if (wwinterrupt() && wwsetjmp) {
		wwsetjmp = 0;
D 2
		(void) sigrelse(SIGIO);
E 2
I 2
		(void) sigsetmask(sigblock(0) & ~sigmask(SIGIO));
E 2
		longjmp(wwjmpbuf, 1);
	}
E 5
}
E 1
