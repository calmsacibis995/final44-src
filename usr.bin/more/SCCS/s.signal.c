h28780
s 00002/00002/00192
d D 8.1 93/06/06 15:37:36 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00004/00191
d D 5.8 91/03/01 15:12:08 bostic 8 7
c ANSI
e
s 00001/00012/00194
d D 5.7 90/06/01 17:05:11 bostic 7 6
c new copyright notice
e
s 00009/00001/00197
d D 5.6 88/12/03 16:24:55 sam 6 5
c purge pending output when fielding SIGINT (signal handling still 
c is not right -- need to watch out for partial writes?)
e
s 00022/00024/00176
d D 5.5 88/11/22 16:51:53 bostic 5 4
c less -> more
e
s 00002/00004/00198
d D 5.4 88/07/25 12:05:26 bostic 4 3
c update copyright notice
e
s 00001/00001/00201
d D 5.3 88/07/22 12:05:28 bostic 3 2
c return never used
e
s 00015/00050/00187
d D 5.2 88/07/22 11:25:41 bostic 2 1
c when I tell you to die, you die (don't catch ^C)
e
s 00237/00000/00000
d D 5.1 88/07/21 18:53:26 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 9
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 4
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 4
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 4
 * by the University of California, Berkeley.  The name of the
E 4
I 4
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 4
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Routines dealing with signals.
 *
 * A signal usually merely causes a bit to be set in the "signals" word.
 * At some convenient time, the mainline code checks to see if any
 * signals need processing by calling psignal().
 * If we happen to be reading from a file [in iread()] at the time
 * the signal is received, we call intread to interrupt the iread.
 */

D 5
#include "less.h"
E 5
I 5
#include <less.h>
E 5
#include <signal.h>

/*
 * "sigs" contains bits indicating signals which need to be processed.
 */
D 5
public int sigs;
E 5
I 5
int sigs;
E 5

D 2
#define	S_INTERRUPT	01
E 2
#ifdef SIGTSTP
#define	S_STOP		02
#endif
#if defined(SIGWINCH) || defined(SIGWIND)
#define S_WINCH		04
#endif

extern int sc_width, sc_height;
extern int screen_trashed;
extern int lnloop;
extern int linenums;
extern int scroll;
extern int reading;

D 2
/*
 * Interrupt signal handler.
 */
	static HANDLER
interrupt()
{
	SIGNAL(SIGINT, interrupt);
	sigs |= S_INTERRUPT;
	if (reading)
		intread();
}

E 2
#ifdef SIGTSTP
/*
 * "Stop" (^Z) signal handler.
 */
D 5
	static HANDLER
E 5
I 5
D 8
static
E 8
I 8
static void
E 8
E 5
stop()
{
D 2
	SIGNAL(SIGTSTP, stop);
E 2
I 2
D 5
	(void) signal(SIGTSTP, stop);
E 5
I 5
	(void)signal(SIGTSTP, stop);
E 5
E 2
	sigs |= S_STOP;
	if (reading)
		intread();
}
#endif

#ifdef SIGWINCH
/*
 * "Window" change handler
 */
I 8
void
E 8
D 5
	public HANDLER
E 5
winch()
{
D 2
	SIGNAL(SIGWINCH, winch);
E 2
I 2
D 5
	signal(SIGWINCH, winch);
E 5
I 5
	(void)signal(SIGWINCH, winch);
E 5
E 2
	sigs |= S_WINCH;
	if (reading)
		intread();
}
#else
#ifdef SIGWIND
/*
 * "Window" change handler
 */
D 5
	public HANDLER
E 5
winch()
{
D 2
	SIGNAL(SIGWIND, winch);
E 2
I 2
D 5
	signal(SIGWIND, winch);
E 5
I 5
	(void)signal(SIGWIND, winch);
E 5
E 2
	sigs |= S_WINCH;
	if (reading)
		intread();
}
#endif
#endif

I 6
D 8
static int
E 8
I 8
static void
E 8
purgeandquit()
{

	purge();	/* purge buffered output */
	quit();
}

E 6
/*
 * Set up the signal handlers.
 */
D 5
	public void
E 5
init_signals(on)
	int on;
{
I 5
D 8
	int quit();

E 8
E 5
	if (on)
	{
		/*
		 * Set signal handlers.
		 */
D 2
		(void) SIGNAL(SIGINT, interrupt);
E 2
I 2
D 5
		(void) signal(SIGINT, quit);
E 5
I 5
D 6
		(void)signal(SIGINT, quit);
E 6
I 6
		(void)signal(SIGINT, purgeandquit);
E 6
E 5
E 2
#ifdef SIGTSTP
D 2
		(void) SIGNAL(SIGTSTP, stop);
E 2
I 2
D 5
		(void) signal(SIGTSTP, stop);
E 5
I 5
		(void)signal(SIGTSTP, stop);
E 5
E 2
#endif
#ifdef SIGWINCH
D 2
		(void) SIGNAL(SIGWINCH, winch);
E 2
I 2
D 5
		(void) signal(SIGWINCH, winch);
E 5
I 5
		(void)signal(SIGWINCH, winch);
E 5
E 2
#else
#ifdef SIGWIND
D 2
		(void) SIGNAL(SIGWIND, winch);
E 2
I 2
D 5
		(void) signal(SIGWIND, winch);
E 5
I 5
		(void)signal(SIGWIND, winch);
E 5
E 2
#endif
#endif
	} else
	{
		/*
		 * Restore signals to defaults.
		 */
D 2
		(void) SIGNAL(SIGINT, SIG_DFL);
E 2
I 2
D 5
		(void) signal(SIGINT, SIG_DFL);
E 5
I 5
		(void)signal(SIGINT, SIG_DFL);
E 5
E 2
#ifdef SIGTSTP
D 2
		(void) SIGNAL(SIGTSTP, SIG_DFL);
E 2
I 2
D 5
		(void) signal(SIGTSTP, SIG_DFL);
E 5
I 5
		(void)signal(SIGTSTP, SIG_DFL);
E 5
E 2
#endif
#ifdef SIGWINCH
D 2
		(void) SIGNAL(SIGWINCH, SIG_IGN);
E 2
I 2
D 5
		(void) signal(SIGWINCH, SIG_IGN);
E 5
I 5
		(void)signal(SIGWINCH, SIG_IGN);
E 5
E 2
#endif
#ifdef SIGWIND
D 2
		(void) SIGNAL(SIGWIND, SIG_IGN);
E 2
I 2
D 5
		(void) signal(SIGWIND, SIG_IGN);
E 5
I 5
		(void)signal(SIGWIND, SIG_IGN);
E 5
E 2
#endif
	}
}

/*
 * Process any signals we have received.
 * A received signal cause a bit to be set in "sigs".
 */
D 5
	public int
E 5
psignals()
{
	register int tsignals;

	if ((tsignals = sigs) == 0)
D 3
		return (0);
E 3
I 3
		return;
E 3
	sigs = 0;

#ifdef S_WINCH
	if (tsignals & S_WINCH)
	{
		int old_width, old_height;
		/*
		 * Re-execute get_term() to read the new window size.
		 */
		old_width = sc_width;
		old_height = sc_height;
		get_term();
		if (sc_width != old_width || sc_height != old_height)
		{
			scroll = (sc_height + 1) / 2;
			screen_trashed = 1;
		}
	}
#endif
#ifdef SIGTSTP
	if (tsignals & S_STOP)
	{
		/*
		 * Clean up the terminal.
		 */
#ifdef SIGTTOU
D 2
		SIGNAL(SIGTTOU, SIG_IGN);
E 2
I 2
D 5
		signal(SIGTTOU, SIG_IGN);
E 5
I 5
		(void)signal(SIGTTOU, SIG_IGN);
E 5
E 2
#endif
		lower_left();
		clear_eol();
		deinit();
D 5
		flush();
E 5
I 5
		(void)flush();
E 5
		raw_mode(0);
#ifdef SIGTTOU
D 2
		SIGNAL(SIGTTOU, SIG_DFL);
E 2
I 2
D 5
		signal(SIGTTOU, SIG_DFL);
E 5
I 5
		(void)signal(SIGTTOU, SIG_DFL);
E 5
E 2
#endif
D 2
		SIGNAL(SIGTSTP, SIG_DFL);
E 2
I 2
D 5
		signal(SIGTSTP, SIG_DFL);
E 2
		kill(getpid(), SIGTSTP);
E 5
I 5
		(void)signal(SIGTSTP, SIG_DFL);
		(void)kill(getpid(), SIGTSTP);
E 5
		/*
		 * ... Bye bye. ...
		 * Hopefully we'll be back later and resume here...
		 * Reset the terminal and arrange to repaint the
		 * screen when we get back to the main command loop.
		 */
D 2
		SIGNAL(SIGTSTP, stop);
E 2
I 2
D 5
		signal(SIGTSTP, stop);
E 5
I 5
		(void)signal(SIGTSTP, stop);
E 5
E 2
		raw_mode(1);
		init();
		screen_trashed = 1;
	}
#endif
D 2
	if (tsignals & S_INTERRUPT)
	{
		bell();
		/*
		 * {{ You may wish to replace the bell() with 
		 *    error("Interrupt"); }}
		 */

		/*
		 * If we were interrupted while in the "calculating 
		 * line numbers" loop, turn off line numbers.
		 */
		if (lnloop)
		{
			lnloop = 0;
			linenums = 0;
			error("Line numbers turned off");
		}

	}

	return (1);
E 2
}
E 1
