h47449
s 00028/00000/00533
d D 8.2 94/04/20 08:11:13 bostic 11 10
c fix more for the tty driver -- the tty compat stuff has problems
c and we don't have time to fix them.
c From: Mark Davies <mark@Comp.VUW.AC.NZ>
e
s 00002/00002/00531
d D 8.1 93/06/06 15:37:32 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00531
d D 5.9 93/02/11 22:02:16 edward 9 8
c for terminals with "db", clear last line before scrolling up
e
s 00003/00001/00528
d D 5.8 92/06/28 15:49:08 bostic 8 7
c Fix word erase on non-termios systems; bug report 4.3BSD-tahoe/usr.bin/47
e
s 00001/00012/00528
d D 5.7 90/06/01 17:05:04 bostic 7 6
c new copyright notice
e
s 00013/00011/00527
d D 5.6 88/12/13 21:58:39 bostic 6 5
c if a short file, don't move to lower-left corner of the screen,
c unless editing or movement attempted, including at exit.  Correct dumb
c mistake in window signal handling.  Add routine to copy portions of the table.
e
s 00001/00016/00537
d D 5.5 88/11/27 17:59:31 bostic 5 4
c delete comments about how dumb terminal is
e
s 00029/00074/00524
d D 5.4 88/11/22 16:51:49 bostic 4 3
c less -> more
e
s 00002/00004/00596
d D 5.3 88/07/25 12:05:21 bostic 3 2
c update copyright notice
e
s 00005/00005/00595
d D 5.2 88/07/22 12:05:55 bostic 2 1
c lint cleanup
e
s 00600/00000/00000
d D 5.1 88/07/21 18:53:24 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 10
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 3
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 3
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 3
 * by the University of California, Berkeley.  The name of the
E 3
I 3
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 3
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
 * Routines which deal with the characteristics of the terminal.
 * Uses termcap to be as terminal-independent as possible.
 *
 * {{ Someday this should be rewritten to use curses. }}
 */

D 4
#include "less.h"
#if XENIX
#include <sys/types.h>
#include <sys/ioctl.h>
#endif
E 4
I 4
#include <stdio.h>
#include <less.h>
E 4

I 11
#define TERMIOS 1

E 11
#if TERMIO
#include <termio.h>
#else
I 11
#if TERMIOS
#include <termios.h>
#define TAB3 0
#include <sys/ioctl.h>
#else
E 11
#include <sgtty.h>
#endif
I 11
#endif
E 11

#ifdef TIOCGWINSZ
#include <sys/ioctl.h>
#else
/*
 * For the Unix PC (ATT 7300 & 3B1):
 * Since WIOCGETD is defined in sys/window.h, we can't use that to decide
 * whether to include sys/window.h.  Use SIGPHONE from sys/signal.h instead.
 */
#include <sys/signal.h>
#ifdef SIGPHONE
#include <sys/window.h>
#endif
#endif

/*
 * Strings passed to tputs() to do various terminal functions.
 */
static char
	*sc_pad,		/* Pad string */
	*sc_home,		/* Cursor home */
	*sc_addline,		/* Add line, scroll down following lines */
	*sc_lower_left,		/* Cursor to last line, first column */
	*sc_move,		/* General cursor positioning */
	*sc_clear,		/* Clear screen */
	*sc_eol_clear,		/* Clear to end of line */
	*sc_s_in,		/* Enter standout (highlighted) mode */
	*sc_s_out,		/* Exit standout mode */
	*sc_u_in,		/* Enter underline mode */
	*sc_u_out,		/* Exit underline mode */
	*sc_b_in,		/* Enter bold mode */
	*sc_b_out,		/* Exit bold mode */
D 4
	*sc_visual_bell,	/* Visual bell (flash screen) sequence */
E 4
	*sc_backspace,		/* Backspace cursor */
	*sc_init,		/* Startup terminal initialization */
	*sc_deinit;		/* Exit terminal de-intialization */

D 4
public int auto_wrap;		/* Terminal does \r\n when write past margin */
public int ignaw;		/* Terminal ignores \n immediately after wrap */
public int erase_char, kill_char; /* The user's erase and line-kill chars */
public int sc_width, sc_height;	/* Height & width of screen */
public int sc_window = -1;	/* window size for forward and backward */
public int bo_width, be_width;	/* Printing width of boldface sequences */
public int ul_width, ue_width;	/* Printing width of underline sequences */
public int so_width, se_width;	/* Printing width of standout sequences */
E 4
I 4
int auto_wrap;			/* Terminal does \r\n when write past margin */
int ignaw;			/* Terminal ignores \n immediately after wrap */
				/* The user's erase and line-kill chars */
I 9
int retain_below;		/* Terminal retains text below the screen */
E 9
int erase_char, kill_char, werase_char;
int sc_width, sc_height = -1;	/* Height & width of screen */
int sc_window = -1;		/* window size for forward and backward */
int bo_width, be_width;		/* Printing width of boldface sequences */
int ul_width, ue_width;		/* Printing width of underline sequences */
int so_width, se_width;		/* Printing width of standout sequences */
E 4

/*
 * These two variables are sometimes defined in,
 * and needed by, the termcap library.
 * It may be necessary on some systems to declare them extern here.
 */
/*extern*/ short ospeed;	/* Terminal output baud rate */
/*extern*/ char PC;		/* Pad character */

D 4
extern int quiet;		/* If VERY_QUIET, use visual bell for bell */
extern int know_dumb;		/* Don't complain about a dumb terminal */
E 4
extern int back_scroll;
char *tgetstr();
char *tgoto();

/*
 * Change terminal to "raw mode", or restore to "normal" mode.
 * "Raw mode" means 
 *	1. An outstanding read will complete on receipt of a single keystroke.
 *	2. Input is not echoed.  
 *	3. On output, \n is mapped to \r\n.
 *	4. \t is NOT expanded into spaces.
 *	5. Signal-causing characters such as ctrl-C (interrupt),
 *	   etc. are NOT disabled.
 * It doesn't matter whether an input \n is mapped to \r, or vice versa.
 */
D 4
	public void
E 4
raw_mode(on)
	int on;
{
I 11
#if TERMIO || TERMIOS

E 11
#if TERMIO
	struct termio s;
	static struct termio save_term;
I 11
#else
	struct termios s;
	static struct termios save_term;
#endif
E 11

	if (on)
	{
		/*
		 * Get terminal modes.
		 */
I 11
#if TERMIO
E 11
D 4
		ioctl(2, TCGETA, &s);
E 4
I 4
		(void)ioctl(2, TCGETA, &s);
I 11
#else
		tcgetattr(2, &s);
#endif
E 11
E 4

		/*
		 * Save modes and set certain variables dependent on modes.
		 */
		save_term = s;
I 11
#if TERMIO
E 11
		ospeed = s.c_cflag & CBAUD;
I 11
#else
		ospeed = cfgetospeed(&s);
#endif
E 11
		erase_char = s.c_cc[VERASE];
		kill_char = s.c_cc[VKILL];
I 4
		werase_char = s.c_cc[VWERASE];
E 4

		/*
		 * Set the modes to the way we want them.
		 */
		s.c_lflag &= ~(ICANON|ECHO|ECHOE|ECHOK|ECHONL);
		s.c_oflag |=  (OPOST|ONLCR|TAB3);
I 11
#if TERMIO
E 11
		s.c_oflag &= ~(OCRNL|ONOCR|ONLRET);
I 11
#endif
E 11
		s.c_cc[VMIN] = 1;
		s.c_cc[VTIME] = 0;
	} else
	{
		/*
		 * Restore saved modes.
		 */
		s = save_term;
	}
I 11
#if TERMIO
E 11
D 4
	ioctl(2, TCSETAW, &s);
E 4
I 4
	(void)ioctl(2, TCSETAW, &s);
I 11
#else
	tcsetattr(2, TCSADRAIN, &s);
#endif
E 11
E 4
#else
	struct sgttyb s;
I 8
	struct ltchars l;
E 8
	static struct sgttyb save_term;

	if (on)
	{
		/*
		 * Get terminal modes.
		 */
D 4
		ioctl(2, TIOCGETP, &s);
E 4
I 4
		(void)ioctl(2, TIOCGETP, &s);
I 8
		(void)ioctl(2, TIOCGLTC, &l);
E 8
E 4

		/*
		 * Save modes and set certain variables dependent on modes.
		 */
		save_term = s;
		ospeed = s.sg_ospeed;
		erase_char = s.sg_erase;
		kill_char = s.sg_kill;
I 4
D 8
		werase_char = -1;
E 8
I 8
		werase_char = l.t_werasc;
E 8
E 4

		/*
		 * Set the modes to the way we want them.
		 */
		s.sg_flags |= CBREAK;
		s.sg_flags &= ~(ECHO|XTABS);
	} else
	{
		/*
		 * Restore saved modes.
		 */
		s = save_term;
	}
D 4
	ioctl(2, TIOCSETN, &s);
E 4
I 4
	(void)ioctl(2, TIOCSETN, &s);
E 4
#endif
}

D 4
	static void
E 4
I 4
D 5
static
E 4
cannot(s)
	char *s;
{
	char message[100];

D 4
	if (know_dumb)
		/* 
		 * He knows he has a dumb terminal, so don't tell him. 
		 */
		return;

E 4
D 2
	sprintf(message, "WARNING: terminal cannot \"%s\"", s);
E 2
I 2
	(void)sprintf(message, "WARNING: terminal cannot \"%s\"", s);
E 2
	error(message);
}

E 5
/*
 * Get terminal capabilities via termcap.
 */
D 4
	public void
E 4
get_term()
{
	char termbuf[2048];
	char *sp;
	char *term;
	int hard;
#ifdef TIOCGWINSZ
	struct winsize w;
#else
#ifdef WIOCGETD
	struct uwdata w;
#endif
#endif
	static char sbuf[1024];

D 2
	char *getenv();
E 2
I 2
	char *getenv(), *strcpy();
E 2

	/*
	 * Find out what kind of terminal this is.
	 */
 	if ((term = getenv("TERM")) == NULL)
 		term = "unknown";
 	if (tgetent(termbuf, term) <= 0)
D 2
 		strcpy(termbuf, "dumb:co#80:hc:");
E 2
I 2
 		(void)strcpy(termbuf, "dumb:co#80:hc:");
E 2

	/*
	 * Get size of the screen.
	 */
I 4
D 6
	if (sc_height == -1)
E 6
E 4
#ifdef TIOCGWINSZ
D 4
	if (ioctl(2, TIOCGWINSZ, &w) == 0 && w.ws_row > 0)
		sc_height = w.ws_row;
	else
E 4
I 4
D 6
		if (ioctl(2, TIOCGWINSZ, &w) == 0 && w.ws_row > 0)
			sc_height = w.ws_row;
E 6
I 6
	if (ioctl(2, TIOCGWINSZ, &w) == 0 && w.ws_row > 0)
		sc_height = w.ws_row;
E 6
E 4
#else
#ifdef WIOCGETD
D 4
	if (ioctl(2, WIOCGETD, &w) == 0 && w.uw_height > 0)
		sc_height = w.uw_height/w.uw_vs;
	else
E 4
I 4
D 6
		if (ioctl(2, WIOCGETD, &w) == 0 && w.uw_height > 0)
			sc_height = w.uw_height/w.uw_vs;
E 6
I 6
	if (ioctl(2, WIOCGETD, &w) == 0 && w.uw_height > 0)
		sc_height = w.uw_height/w.uw_vs;
E 6
E 4
#endif
#endif
D 4
 		sc_height = tgetnum("li");
 	hard = (sc_height < 0 || tgetflag("hc"));
	if (hard)
	{
E 4
I 4
D 6
		else
			sc_height = tgetnum("li");
E 6
I 6
	else
		sc_height = tgetnum("li");
E 6
	hard = (sc_height < 0 || tgetflag("hc"));
	if (hard) {
E 4
		/* Oh no, this is a hardcopy terminal. */
		sc_height = 24;
	}

#ifdef TIOCGWINSZ
 	if (ioctl(2, TIOCGWINSZ, &w) == 0 && w.ws_col > 0)
		sc_width = w.ws_col;
	else
#ifdef WIOCGETD
	if (ioctl(2, WIOCGETD, &w) == 0 && w.uw_width > 0)
		sc_width = w.uw_width/w.uw_hs;
	else
#endif
#endif
 		sc_width = tgetnum("co");
 	if (sc_width < 0)
  		sc_width = 80;

	auto_wrap = tgetflag("am");
	ignaw = tgetflag("xn");
I 9
	retain_below = tgetflag("db");
E 9

	/*
	 * Assumes termcap variable "sg" is the printing width of
	 * the standout sequence, the end standout sequence,
	 * the underline sequence, the end underline sequence,
	 * the boldface sequence, and the end boldface sequence.
	 */
	if ((so_width = tgetnum("sg")) < 0)
		so_width = 0;
	be_width = bo_width = ue_width = ul_width = se_width = so_width;

	/*
	 * Get various string-valued capabilities.
	 */
	sp = sbuf;

	sc_pad = tgetstr("pc", &sp);
	if (sc_pad != NULL)
		PC = *sc_pad;

	sc_init = tgetstr("ti", &sp);
	if (sc_init == NULL)
		sc_init = "";

	sc_deinit= tgetstr("te", &sp);
	if (sc_deinit == NULL)
		sc_deinit = "";

	sc_eol_clear = tgetstr("ce", &sp);
	if (hard || sc_eol_clear == NULL || *sc_eol_clear == '\0')
	{
D 5
		cannot("clear to end of line");
E 5
		sc_eol_clear = "";
	}

	sc_clear = tgetstr("cl", &sp);
	if (hard || sc_clear == NULL || *sc_clear == '\0')
	{
D 5
		cannot("clear screen");
E 5
		sc_clear = "\n\n";
	}

	sc_move = tgetstr("cm", &sp);
	if (hard || sc_move == NULL || *sc_move == '\0')
	{
		/*
		 * This is not an error here, because we don't 
		 * always need sc_move.
		 * We need it only if we don't have home or lower-left.
		 */
		sc_move = "";
	}

	sc_s_in = tgetstr("so", &sp);
	if (hard || sc_s_in == NULL)
		sc_s_in = "";

	sc_s_out = tgetstr("se", &sp);
	if (hard || sc_s_out == NULL)
		sc_s_out = "";

	sc_u_in = tgetstr("us", &sp);
	if (hard || sc_u_in == NULL)
		sc_u_in = sc_s_in;

	sc_u_out = tgetstr("ue", &sp);
	if (hard || sc_u_out == NULL)
		sc_u_out = sc_s_out;

	sc_b_in = tgetstr("md", &sp);
	if (hard || sc_b_in == NULL)
	{
		sc_b_in = sc_s_in;
		sc_b_out = sc_s_out;
	} else
	{
		sc_b_out = tgetstr("me", &sp);
		if (hard || sc_b_out == NULL)
			sc_b_out = "";
	}

D 4
	sc_visual_bell = tgetstr("vb", &sp);
	if (hard || sc_visual_bell == NULL)
		sc_visual_bell = "";

E 4
	sc_home = tgetstr("ho", &sp);
	if (hard || sc_home == NULL || *sc_home == '\0')
	{
		if (*sc_move == '\0')
		{
D 5
			cannot("home cursor");
E 5
			/*
			 * This last resort for sc_home is supposed to
			 * be an up-arrow suggesting moving to the 
			 * top of the "virtual screen". (The one in
			 * your imagination as you try to use this on
			 * a hard copy terminal.)
			 */
D 5
			sc_home = "|\b^";		
E 5
I 5
			sc_home = "|\b^";
E 5
		} else
		{
			/* 
			 * No "home" string,
			 * but we can use "move(0,0)".
			 */
D 2
			strcpy(sp, tgoto(sc_move, 0, 0));
E 2
I 2
			(void)strcpy(sp, tgoto(sc_move, 0, 0));
E 2
			sc_home = sp;
			sp += strlen(sp) + 1;
		}
	}

	sc_lower_left = tgetstr("ll", &sp);
	if (hard || sc_lower_left == NULL || *sc_lower_left == '\0')
	{
		if (*sc_move == '\0')
		{
D 5
			cannot("move cursor to lower left of screen");
E 5
			sc_lower_left = "\r";
		} else
		{
			/*
			 * No "lower-left" string, 
			 * but we can use "move(0,last-line)".
			 */
D 2
			strcpy(sp, tgoto(sc_move, 0, sc_height-1));
E 2
I 2
			(void)strcpy(sp, tgoto(sc_move, 0, sc_height-1));
E 2
			sc_lower_left = sp;
			sp += strlen(sp) + 1;
		}
	}

	/*
	 * To add a line at top of screen and scroll the display down,
	 * we use "al" (add line) or "sr" (scroll reverse).
	 */
	if ((sc_addline = tgetstr("al", &sp)) == NULL || 
		 *sc_addline == '\0')
		sc_addline = tgetstr("sr", &sp);

	if (hard || sc_addline == NULL || *sc_addline == '\0')
	{
D 5
		cannot("scroll backwards");
E 5
		sc_addline = "";
		/* Force repaint on any backward movement */
		back_scroll = 0;
	}

	if (tgetflag("bs"))
		sc_backspace = "\b";
	else
	{
		sc_backspace = tgetstr("bc", &sp);
		if (sc_backspace == NULL || *sc_backspace == '\0')
			sc_backspace = "\b";
	}
}


/*
 * Below are the functions which perform all the 
 * terminal-specific screen manipulation.
 */

I 4
int putchr();
E 4

/*
 * Initialize terminal
 */
D 4
	public void
E 4
init()
{
	tputs(sc_init, sc_height, putchr);
}

/*
 * Deinitialize terminal
 */
D 4
	public void
E 4
deinit()
{
	tputs(sc_deinit, sc_height, putchr);
}

/*
 * Home cursor (move to upper left corner of screen).
 */
D 4
	public void
E 4
home()
{
	tputs(sc_home, 1, putchr);
}

/*
 * Add a blank line (called with cursor at home).
 * Should scroll the display down.
 */
D 4
	public void
E 4
add_line()
{
	tputs(sc_addline, sc_height, putchr);
}

D 6
/*
 * Move cursor to lower left corner of screen.
 */
E 6
I 6
int short_file;				/* if file less than a screen */
E 6
D 4
	public void
E 4
lower_left()
{
D 6
	tputs(sc_lower_left, 1, putchr);
E 6
I 6
	if (short_file) {
		putchr('\r');
		flush();
	}
	else
		tputs(sc_lower_left, 1, putchr);
E 6
}

/*
 * Ring the terminal bell.
 */
D 4
	public void
E 4
bell()
{
D 4
	if (quiet == VERY_QUIET)
		vbell();
	else
		putchr('\7');
E 4
I 4
	putchr('\7');
E 4
}

/*
D 4
 * Output the "visual bell", if there is one.
 */
	public void
vbell()
{
	if (*sc_visual_bell == '\0')
		return;
	tputs(sc_visual_bell, sc_height, putchr);
}

/*
E 4
 * Clear the screen.
 */
D 4
	public void
E 4
clear()
{
	tputs(sc_clear, sc_height, putchr);
}

/*
 * Clear from the cursor to the end of the cursor's line.
 * {{ This must not move the cursor. }}
 */
D 4
	public void
E 4
clear_eol()
{
	tputs(sc_eol_clear, 1, putchr);
}

/*
 * Begin "standout" (bold, underline, or whatever).
 */
D 4
	public void
E 4
so_enter()
{
	tputs(sc_s_in, 1, putchr);
}

/*
 * End "standout".
 */
D 4
	public void
E 4
so_exit()
{
	tputs(sc_s_out, 1, putchr);
}

/*
 * Begin "underline" (hopefully real underlining, 
 * otherwise whatever the terminal provides).
 */
D 4
	public void
E 4
ul_enter()
{
	tputs(sc_u_in, 1, putchr);
}

/*
 * End "underline".
 */
D 4
	public void
E 4
ul_exit()
{
	tputs(sc_u_out, 1, putchr);
}

/*
 * Begin "bold"
 */
D 4
	public void
E 4
bo_enter()
{
	tputs(sc_b_in, 1, putchr);
}

/*
 * End "bold".
 */
D 4
	public void
E 4
bo_exit()
{
	tputs(sc_b_out, 1, putchr);
}

/*
 * Erase the character to the left of the cursor 
 * and move the cursor left.
 */
D 4
	public void
E 4
backspace()
{
	/* 
	 * Try to erase the previous character by overstriking with a space.
	 */
	tputs(sc_backspace, 1, putchr);
	putchr(' ');
	tputs(sc_backspace, 1, putchr);
}

/*
 * Output a plain backspace, without erasing the previous char.
 */
D 4
	public void
E 4
putbs()
{
	tputs(sc_backspace, 1, putchr);
}
E 1
