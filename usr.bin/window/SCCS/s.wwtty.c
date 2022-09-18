h42908
s 00002/00002/00152
d D 8.1 93/06/06 22:33:15 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00153
d D 3.18 91/02/02 18:19:39 torek 24 23
c must include <sys/types.h> before <fcntl.h>
e
s 00081/00006/00072
d D 3.17 90/08/12 15:25:59 edward 23 22
c switch to POSIX tty, old code still supported under OLD_TTY
e
s 00003/00000/00075
d D 3.16 90/06/06 21:45:56 bostic 22 21
c fix contrib notice (Edward Wang)
e
s 00001/00011/00074
d D 3.15 90/06/02 15:25:46 bostic 21 20
c new copyright notice
e
s 00015/00001/00070
d D 3.14 90/06/02 15:15:07 edward 20 19
c first try at POSIX tty
e
s 00001/00001/00070
d D 3.13 89/05/11 17:01:55 edward 19 18
c the xx layer added, handle "ic" differently, compression added to zapple
e
s 00010/00005/00061
d D 3.12 88/06/29 21:38:57 bostic 18 17
c install approved copyright notice
e
s 00013/00007/00053
d D 3.11 88/02/21 13:38:59 bostic 17 16
c written by Edward Wang; attach Berkeley specific copyright
e
s 00010/00010/00050
d D 3.10 86/08/05 01:24:38 edward 16 15
c lint
e
s 00006/00000/00054
d D 3.9 85/04/24 16:12:28 edward 15 14
c copyright messages
e
s 00009/00003/00045
d D 3.8 84/11/20 23:39:51 edward 14 13
c we don't flush typeahead any more
e
s 00001/00001/00047
d D 3.7 84/05/23 01:56:46 edward 13 12
c new sccs id
e
s 00005/00000/00043
d D 3.6 84/03/03 22:43:18 edward 12 11
c interrupt driven input
e
s 00000/00004/00043
d D 3.5 83/12/17 12:39:35 edward 11 10
c got rid of pgrp in struct ww_tty
e
s 00018/00012/00029
d D 3.4 83/08/26 16:25:02 edward 10 9
c error reporting
e
s 00001/00001/00040
d D 3.3 83/08/23 20:27:29 edward 9 8
c use TIOCSETN instead SETP
e
s 00012/00012/00029
d D 3.2 83/08/12 11:42:42 edward 8 7
c lint
e
s 00000/00000/00041
d D 3.1 83/08/11 17:21:40 edward 7 5
i 6
c last few day's work
e
s 00012/00012/00029
d D 2.1.1.1 83/08/09 18:34:55 edward 6 5
c mile stone
e
s 00000/00000/00041
d D 2.1 83/07/30 13:27:20 edward 5 4
c prepare for major change
e
s 00000/00000/00041
d D 1.4 83/07/22 17:09:03 edward 4 3
c scrolling.
c uses Wscreensize() to get screen size.
c More intelligent framing.
c etc.
e
s 00000/00000/00041
d D 1.3 83/07/19 20:07:52 edward 3 2
c today's work
e
s 00000/00000/00041
d D 1.2 83/07/18 21:03:36 edward 2 1
c multiple window
e
s 00041/00000/00000
d D 1.1 83/07/17 15:19:04 edward 1 0
c date and time created 83/07/17 15:19:04 by edward
e
u
U
f b 
t
T
I 1
D 17
#ifndef lint
D 13
static	char *sccsid = "%W% %E%";
E 13
I 13
static char sccsid[] = "%W% %G%";
E 13
#endif

E 17
I 15
/*
D 17
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 17
I 17
D 25
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
I 22
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 22
D 21
 * Redistribution and use in source and binary forms are permitted
D 18
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 18
I 18
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
E 21
I 21
 * %sccs.include.redist.c%
E 21
E 18
E 17
 */
I 17

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 17

E 15
#include "ww.h"
I 24
#include <sys/types.h>
E 24
I 12
#include <fcntl.h>
I 23
#if !defined(OLD_TTY) && !defined(TIOCGWINSZ)
#include <sys/ioctl.h>
#endif
E 23
E 12

wwgettty(d, t)
register struct ww_tty *t;
{
I 20
D 23
#ifndef POSIX_TTY
E 23
I 23
#ifdef OLD_TTY
E 23
E 20
D 6
	if (ioctl(d, TIOCGETP, &t->ww_sgttyb) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCGETP, (char *)&t->ww_sgttyb) < 0)
E 8
I 8
D 16
	if (ioctl(d, (int)TIOCGETP, (char *)&t->ww_sgttyb) < 0)
E 16
I 16
	if (ioctl(d, TIOCGETP, (char *)&t->ww_sgttyb) < 0)
E 16
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 10
D 6
	if (ioctl(d, TIOCGETC, &t->ww_tchars) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCGETC, (char *)&t->ww_tchars) < 0)
E 8
I 8
D 16
	if (ioctl(d, (int)TIOCGETC, (char *)&t->ww_tchars) < 0)
E 16
I 16
	if (ioctl(d, TIOCGETC, (char *)&t->ww_tchars) < 0)
E 16
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 10
D 6
	if (ioctl(d, TIOCGLTC, &t->ww_ltchars) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCGLTC, (char *)&t->ww_ltchars) < 0)
E 8
I 8
D 16
	if (ioctl(d, (int)TIOCGLTC, (char *)&t->ww_ltchars) < 0)
E 16
I 16
	if (ioctl(d, TIOCGLTC, (char *)&t->ww_ltchars) < 0)
E 16
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 10
D 6
	if (ioctl(d, TIOCLGET, &t->ww_lmode) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCLGET, (char *)&t->ww_lmode) < 0)
E 8
I 8
D 16
	if (ioctl(d, (int)TIOCLGET, (char *)&t->ww_lmode) < 0)
E 16
I 16
	if (ioctl(d, TIOCLGET, (char *)&t->ww_lmode) < 0)
E 16
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 10
D 6
	if (ioctl(d, TIOCGETD, &t->ww_ldisc) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCGETD, (char *)&t->ww_ldisc) < 0)
E 8
I 8
D 16
	if (ioctl(d, (int)TIOCGETD, (char *)&t->ww_ldisc) < 0)
E 16
I 16
	if (ioctl(d, TIOCGETD, (char *)&t->ww_ldisc) < 0)
E 16
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
I 20
#else
	if (tcgetattr(d, &t->ww_termios) < 0)
		goto bad;
#endif
E 20
I 12
	if ((t->ww_fflags = fcntl(d, F_GETFL, 0)) < 0)
		goto bad;
E 12
E 10
D 6
	if (ioctl(d, TIOCGPGRP, &t->ww_pgrp) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCGPGRP, (char *)&t->ww_pgrp) < 0)
E 8
I 8
D 11
	if (ioctl(d, (int)TIOCGPGRP, (char *)&t->ww_pgrp) < 0)
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 11
E 10
	return 0;
I 10
bad:
	wwerrno = WWE_SYS;
	return -1;
E 10
}

D 14
wwsettty(d, t)
register struct ww_tty *t;
E 14
I 14
/*
 * Set the modes of tty 'd' to 't'
 * 'o' is the current modes.  We set the line discipline only if
 * it changes, to avoid unnecessary flushing of typeahead.
 */
D 23
wwsettty(d, t, o)
register struct ww_tty *t, *o;
E 23
I 23
wwsettty(d, t)
register struct ww_tty *t;
E 23
E 14
{
D 6
	if (ioctl(d, TIOCSETP, &t->ww_sgttyb) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCSETP, (char *)&t->ww_sgttyb) < 0)
E 8
I 8
D 9
	if (ioctl(d, (int)TIOCSETP, (char *)&t->ww_sgttyb) < 0)
E 9
I 9
D 16
	if (ioctl(d, (int)TIOCSETN, (char *)&t->ww_sgttyb) < 0)
E 16
I 16
D 19
	if (ioctl(d, TIOCSETN, (char *)&t->ww_sgttyb) < 0)
E 19
I 19
D 20
	if (ioctl(d, TIOCSETP, (char *)&t->ww_sgttyb) < 0)
E 20
I 20
D 23
#ifndef POSIX_TTY
	/* for buggy tty driver that doesn't wait for output to drain */
E 23
I 23
#ifdef OLD_TTY
E 23
	int i;
I 23

	/* XXX, for buggy tty drivers that don't wait for output to drain */
E 23
	while (ioctl(d, TIOCOUTQ, &i) >= 0 && i > 0)
		usleep(100000);
	if (ioctl(d, TIOCSETN, (char *)&t->ww_sgttyb) < 0)
E 20
E 19
E 16
E 9
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 10
D 6
	if (ioctl(d, TIOCSETC, &t->ww_tchars) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCSETC, (char *)&t->ww_tchars) < 0)
E 8
I 8
D 16
	if (ioctl(d, (int)TIOCSETC, (char *)&t->ww_tchars) < 0)
E 16
I 16
	if (ioctl(d, TIOCSETC, (char *)&t->ww_tchars) < 0)
E 16
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 10
D 6
	if (ioctl(d, TIOCSLTC, &t->ww_ltchars) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCSLTC, (char *)&t->ww_ltchars) < 0)
E 8
I 8
D 16
	if (ioctl(d, (int)TIOCSLTC, (char *)&t->ww_ltchars) < 0)
E 16
I 16
	if (ioctl(d, TIOCSLTC, (char *)&t->ww_ltchars) < 0)
E 16
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 10
D 6
	if (ioctl(d, TIOCLSET, &t->ww_lmode) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCLSET, (char *)&t->ww_lmode) < 0)
E 8
I 8
D 16
	if (ioctl(d, (int)TIOCLSET, (char *)&t->ww_lmode) < 0)
E 16
I 16
	if (ioctl(d, TIOCLSET, (char *)&t->ww_lmode) < 0)
E 16
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 10
D 6
	if (ioctl(d, TIOCSETD, &t->ww_ldisc) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCSETD, (char *)&t->ww_ldisc) < 0)
E 8
I 8
D 14
	if (ioctl(d, (int)TIOCSETD, (char *)&t->ww_ldisc) < 0)
E 14
I 14
D 23
	if ((o == 0 || t->ww_ldisc != o->ww_ldisc) &&
E 23
I 23
	if (ioctl(d, TIOCGETD, (char *)&i) < 0)
		goto bad;
	if (t->ww_ldisc != i &&
E 23
D 16
	    ioctl(d, (int)TIOCSETD, (char *)&t->ww_ldisc) < 0)
E 16
I 16
	    ioctl(d, TIOCSETD, (char *)&t->ww_ldisc) < 0)
E 16
E 14
I 12
		goto bad;
I 20
#else
I 23
#ifdef sun
	/* XXX, for buggy tty drivers that don't wait for output to drain */
	(void) tcdrain(d);
#endif
E 23
	if (tcsetattr(d, TCSADRAIN, &t->ww_termios) < 0)
		goto bad;
#endif
E 20
	if (fcntl(d, F_SETFL, t->ww_fflags) < 0)
E 12
E 8
E 6
D 10
		return -1;
E 10
I 10
D 11
		goto bad;
E 10
D 6
	if (ioctl(d, TIOCSPGRP, &t->ww_pgrp) < 0)
E 6
I 6
D 8
	if (ioctl(d, TIOCSPGRP, (char *)&t->ww_pgrp) < 0)
E 8
I 8
	if (ioctl(d, (int)TIOCSPGRP, (char *)&t->ww_pgrp) < 0)
E 11
E 8
E 6
D 10
		return -1;
E 10
I 10
		goto bad;
E 10
	return 0;
I 10
bad:
	wwerrno = WWE_SYS;
	return -1;
I 23
}

/*
 * The ttysize and stop-start routines must also work
 * on the control side of pseudoterminals.
 */

wwgetttysize(d, r, c)
	int *r, *c;
{
	struct winsize winsize;

	if (ioctl(d, TIOCGWINSZ, (char *)&winsize) < 0) {
		wwerrno = WWE_SYS;
		return -1;
	}
	if (winsize.ws_row != 0)
		*r = winsize.ws_row;
	if (winsize.ws_col != 0)
		*c = winsize.ws_col;
	return 0;
}

wwsetttysize(d, r, c)
{
	struct winsize winsize;

	winsize.ws_row = r;
	winsize.ws_col = c;
	winsize.ws_xpixel = winsize.ws_ypixel = 0;
	if (ioctl(d, TIOCSWINSZ, (char *)&winsize) < 0) {
		wwerrno = WWE_SYS;
		return -1;
	}
	return 0;
}

wwstoptty(d)
{
#if !defined(OLD_TTY) && defined(TCOOFF)
	/* not guaranteed to work on the pty side */
	if (tcflow(d, TCOOFF) < 0)
#else
	if (ioctl(d, TIOCSTOP, (char *)0) < 0)
#endif
	{
		wwerrno = WWE_SYS;
		return -1;
	}
	return 0;
}

wwstarttty(d)
{
#if !defined(OLD_TTY) && defined(TCOON)
	/* not guaranteed to work on the pty side */
	if (tcflow(d, TCOON) < 0)
#else
	if (ioctl(d, TIOCSTART, (char *)0) < 0)
#endif
	{
		wwerrno = WWE_SYS;
		return -1;
	}
	return 0;
E 23
E 10
}
E 1
