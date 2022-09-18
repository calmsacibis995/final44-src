h07492
s 00002/00002/00096
d D 8.3 94/05/04 06:25:03 bostic 20 19
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00005/00004/00093
d D 8.2 94/01/02 12:29:10 bostic 19 18
c only block SIGALRM and SIGWINCH, not every signal, otherwise the
c program has no chance to handle things like SIGHUP/SIGTERM without
c repainting, and, with SIGTTOU blocked, the repainting will succeed
c as well
e
s 00002/00002/00095
d D 8.1 93/06/07 12:24:34 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00095
d D 5.10 93/06/07 12:20:26 bostic 17 15
c change so users can set __tcaction if they want to switch behavior
e
s 00002/00002/00094
d R 8.1 93/06/04 16:49:30 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00005/00067
d D 5.9 93/06/04 16:11:59 marc 15 14
c changed to remember and restore TSTP handler, and also to resnapshot tty state when restarting from TSTP.  Also, hardwire GT variable since we always turn tab expansion off.  We still aren't sure what pfast is for, but we haven't given up yet.
e
s 00028/00012/00044
d D 5.8 93/01/24 20:14:13 bostic 14 13
c rewrite tstp as __stop_signal_handler: new implementation
e
s 00035/00026/00021
d D 5.7 92/08/23 14:42:47 bostic 13 11
c rewrite for the new tty driver, 4.4BSD
e
s 00027/00027/00020
d R 5.7 92/05/15 15:35:36 bostic 12 11
c rewrite to POSIX signal and termios interfaces
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00000/00046
d D 5.6 91/03/03 18:36:27 bostic 11 10
c ANSI
e
s 00001/00011/00045
d D 5.5 90/06/01 15:40:46 bostic 10 9
c new copyright notice
e
s 00001/00001/00055
d D 5.4 89/06/29 19:28:34 bostic 9 8
c remove references to [sg]tty
e
s 00010/00005/00046
d D 5.3 88/06/30 17:22:10 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00041
d D 5.2 88/06/08 13:57:52 bostic 7 6
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00000/00035
d D 5.1 85/06/07 08:17:23 dist 6 5
c Add copyright
e
s 00001/00001/00034
d D 1.4 85/05/01 17:37:29 bloom 5 4
c fix sccs id
e
s 00006/00000/00029
d D 1.3 83/06/25 22:34:26 sam 4 2
c fix for new signals
e
s 00006/00000/00029
d R 1.3 83/06/21 23:26:14 sam 3 2
c signal not reset on handler entrance
e
s 00003/00003/00026
d D 1.2 83/05/09 20:31:06 arnold 2 1
c stop complaint about "no symbols" on non-tstp machines
e
s 00029/00000/00000
d D 1.1 81/03/06 00:09:01 arnold 1 0
c date and time created 81/03/06 00:09:01 by arnold
e
u
U
t
T
I 6
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
D 18
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 18
I 18
D 20
 * Copyright (c) 1981, 1993
E 20
I 20
 * Copyright (c) 1981, 1993, 1994
E 20
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

E 6
I 1
D 13
# include	<signal.h>
E 13
I 13
D 20
#include <curses.h>
E 20
#include <errno.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
E 13

I 20
#include "curses.h"
E 20
I 15

E 15
D 2
# ifdef SIGTSTP

E 2
D 13
# include	"curses.ext"

E 13
/*
D 13
 * handle stop and start signals
 *
D 5
 * %G% (Berkeley) %W%
E 5
I 5
 * %W% (Berkeley) %G%
E 13
I 13
D 14
 * tstp --
 *	Handle stop and start signals.
E 14
I 14
 * stop_signal_handler --
 *	Handle stop signals.
E 14
E 13
E 5
 */
I 11
void
E 11
D 13
tstp() {
E 13
I 13
D 14
tstp(signo)
E 14
I 14
__stop_signal_handler(signo)
E 14
	int signo;
{
	struct termios save;
D 14
	sigset_t set;
E 14
I 14
	sigset_t oset, set;
E 14
E 13

I 2
D 13
# ifdef SIGTSTP
E 13
I 13
D 15
	/* Get the current terminal state. */
E 15
I 15
	/* Get the current terminal state (which the user may have changed). */
E 15
	if (tcgetattr(STDIN_FILENO, &save))
		return;
E 13

E 2
D 13
	SGTTY	tty;
I 4
	int	omask;
E 4
# ifdef DEBUG
	if (outf)
		fflush(outf);
# endif
	tty = _tty;
E 13
I 13
D 14
	/* Move the cursor to the end of the screen. */
E 13
	mvcur(0, COLS - 1, LINES - 1, 0);
I 13

	/* End the window. */
E 14
I 14
	/*
D 19
	 * Block every signal we can get our hands on.  This is because
	 * applications have timers going off that want to repaint the
	 * screen.
E 19
I 19
	 * Block window change and timer signals.  The latter is because
	 * applications use timers to decide when to repaint the screen.
E 19
	 */
D 19
	(void)sigfillset(&set);
E 19
I 19
	(void)sigemptyset(&set);
	(void)sigaddset(&set, SIGALRM);
	(void)sigaddset(&set, SIGWINCH);
E 19
	(void)sigprocmask(SIG_BLOCK, &set, &oset);
	
	/*
	 * End the window, which also resets the terminal state to the
	 * original modes.
	 */
E 14
E 13
	endwin();
D 13
	fflush(stdout);
I 4
	/* reset signal handler so kill below stops us */
	signal(SIGTSTP, SIG_DFL);
#define	mask(s)	(1 << ((s)-1))
	omask = sigsetmask(sigblock(0) &~ mask(SIGTSTP));
E 4
	kill(0, SIGTSTP);
I 4
	sigblock(mask(SIGTSTP));
E 4
	signal(SIGTSTP, tstp);
	_tty = tty;
D 9
	stty(_tty_ch, &_tty);
E 9
I 9
	ioctl(_tty_ch, TIOCSETP, &_tty);
E 13
I 13

D 14
	/* Stop ourselves. */
E 14
I 14
	/* Unblock SIGTSTP. */
E 14
	(void)sigemptyset(&set);
	(void)sigaddset(&set, SIGTSTP);
	(void)sigprocmask(SIG_UNBLOCK, &set, NULL);
I 14

	/* Stop ourselves. */
E 14
D 15
	(void)signal(SIGTSTP, SIG_DFL);
E 15
I 15
	__restore_stophandler();
E 15
	(void)kill(0, SIGTSTP);

	/* Time passes ... */

D 14
	/* Reset the signal handler. */
	(void)signal(SIGTSTP, tstp);
E 14
I 14
	/* Reset the curses SIGTSTP signal handler. */
D 15
	(void)signal(SIGTSTP, __stop_signal_handler);
E 15
I 15
	__set_stophandler();
E 15
E 14

D 14
	/* Reset the terminal state. */
E 14
I 14
D 15
	/* Reset the terminal state its mode when we stopped. */
E 14
	(void)tcsetattr(STDIN_FILENO, TCSADRAIN, &save);
E 15
I 15
	/* save the new "default" terminal state */
	(void)tcgetattr(STDIN_FILENO, &__orig_termios);
E 15

I 15
	/* Reset the terminal state to the mode just before we stopped. */
D 17
	(void)tcsetattr(STDIN_FILENO, __tcaction, &save);
E 17
I 17
	(void)tcsetattr(STDIN_FILENO, __tcaction ?
	    TCSASOFT | TCSADRAIN : TCSADRAIN, &save);
E 17

E 15
	/* Restart the screen. */
I 14
	__startwin();

	/* Repaint the screen. */
E 14
E 13
E 9
	wrefresh(curscr);
I 14

	/* Reset the signals. */
	(void)sigprocmask(SIG_SETMASK, &oset, NULL);
I 15
}

static void (*otstpfn)() = SIG_DFL;

/*
 * Set the TSTP handler.
 */
void
__set_stophandler()
{
	otstpfn = signal(SIGTSTP, __stop_signal_handler);
}

/*
 * Restore the TSTP handler.
 */
void
__restore_stophandler()
{
	(void)signal(SIGTSTP, otstpfn);
E 15
E 14
I 2
D 13
# endif	SIGTSTP
E 13
E 2
}
D 2
# endif
E 2
E 1
