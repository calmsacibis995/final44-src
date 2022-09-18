h21092
s 00003/00002/00066
d D 8.2 94/05/04 06:24:44 bostic 26 25
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00066
d D 8.1 93/06/04 16:48:22 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00067
d D 5.16 93/06/04 16:12:00 marc 24 23
c changed to remember and restore TSTP handler, and also to resnapshot tty state when restarting from TSTP.  Also, hardwire GT variable since we always turn tab expansion off.  We still aren't sure what pfast is for, but we haven't given up yet.
e
s 00002/00002/00066
d D 5.15 93/05/16 15:54:40 bostic 23 22
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00002/00003/00066
d D 5.14 93/05/10 12:14:35 bostic 22 21
c don't call startwin() until the last minute, it outputs characters to
c the screen
e
s 00002/00003/00067
d D 5.13 93/01/24 20:14:30 bostic 21 20
c add __startwin, which reinitializes the terminal using TI, VS
e
s 00004/00004/00066
d D 5.12 93/01/11 11:53:50 bostic 20 19
c CURSES_{OK,ERR} -> OK,ERR
e
s 00004/00004/00066
d D 5.11 92/12/30 14:55:11 elan 19 18
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00031/00029/00039
d D 5.10 92/12/22 15:02:37 bostic 18 17
c rework initscr to always call gettmode(), use My_term a little
c more intelligently (if that's possible); initialize globals in case called
c repeatedly; minor cleanups and error checking
e
s 00003/00000/00065
d D 5.9 92/10/27 17:27:09 elan 17 16
c Added check for no HO or CM since without them we can't refresh.
e
s 00002/00001/00063
d D 5.8 92/09/14 11:00:32 elan 16 15
c Converted to new data structures.
e
s 00036/00039/00028
d D 5.7 92/08/23 11:06:54 bostic 15 13
c KNF and lint
e
s 00028/00033/00034
d R 5.7 92/05/15 15:31:15 bostic 14 13
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00001/00066
d D 5.6 91/03/03 18:36:25 bostic 13 12
c ANSI
e
s 00001/00011/00066
d D 5.5 90/06/01 15:39:02 bostic 12 11
c new copyright notice
e
s 00000/00004/00077
d D 5.4 89/11/22 13:34:30 bostic 11 10
c change default tty_ch to 0; remove for loop which purported to find
c the first "tty" file descriptor.  Effect of old code was to always set tty_ch
c to 0 (assuming that the stack was initialized to 0).
e
s 00010/00005/00071
d D 5.3 88/06/30 17:21:42 bostic 10 9
c install approved copyright notice
e
s 00010/00004/00066
d D 5.2 88/06/08 13:57:17 bostic 9 8
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00060
d D 5.1 85/06/07 11:34:20 dist 8 7
c Add copyright
e
s 00003/00008/00058
d D 1.6 85/05/23 15:42:40 bloom 7 6
c only look at stdin, stdout and stderr
e
s 00003/00002/00063
d D 1.5 85/05/01 18:39:52 bloom 6 5
c use getdtablesize() instead of defined NOFILE
e
s 00003/00002/00062
d D 1.4 85/05/01 17:18:07 bloom 5 3
c new version from arnold
e
s 00003/00002/00062
d R 1.4 85/05/01 17:15:55 bloom 4 3
c fix sccs id
e
s 00011/00004/00053
d D 1.3 83/05/19 12:10:43 arnold 3 2
c check more than one channel for tty
e
s 00006/00001/00051
d D 1.2 81/03/06 00:15:52 arnold 2 1
c add handling of ^Z (tstp) signal
e
s 00052/00000/00000
d D 1.1 81/01/26 17:02:56 arnold 1 0
c date and time created 81/01/26 17:02:56 by arnold
e
u
U
t
T
I 8
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 25
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 25
I 25
D 26
 * Copyright (c) 1981, 1993
E 26
I 26
 * Copyright (c) 1981, 1993, 1994
E 26
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 10
E 9
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
D 15
#endif /* not lint */
E 15
I 15
#endif	/* not lint */
E 15
E 9

E 8
I 1
D 15
# include	"curses.ext"
I 2
# include	<signal.h>
E 15
I 15
D 26
#include <curses.h>
E 26
#include <signal.h>
#include <stdlib.h>
I 26

#include "curses.h"
E 26
E 15
I 3
D 6
# include	<sys/param.h>
E 6
E 3
E 2

D 15
extern char	*getenv();

E 15
/*
D 15
 *	This routine initializes the current and standard screen.
 *
E 15
I 15
 * initscr --
 *	Initialize the current and standard screen.
E 15
D 5
 * %G% (Berkeley) %W%
E 5
I 5
D 8
 * %W% (Berkeley) %G%
E 8
E 5
 */
WINDOW *
D 15
initscr() {
E 15
I 15
initscr()
{
	register char *sp;
E 15

D 15
	reg char	*sp;
I 2
D 13
	int		tstp();
E 13
I 13
	void		tstp();
E 13
I 6
D 11
	int 		nfd;
E 11
E 6
E 2

# ifdef DEBUG
	fprintf(outf, "INITSCR()\n");
# endif
D 3
	if (!My_term && isatty(2)) {
		_tty_ch = 2;
E 3
I 3
	if (My_term)
		setterm(Def_term);
	else {
E 15
I 15
#ifdef DEBUG
D 23
	__TRACE("initscr\n");
E 23
I 23
	__CTRACE("initscr\n");
E 23
#endif
D 18
	if (My_term) {
		if (setterm(Def_term) == ERR)
			return (NULL);
	} else {
E 15
D 7
		if (isatty(2))
			_tty_ch = 2;
		else {
D 6
			for (_tty_ch = 0; _tty_ch < NOFILE; _tty_ch++)
E 6
I 6
			nfd = getdtablesize();
			for (_tty_ch = 0; _tty_ch < nfd; _tty_ch++)
E 6
				if (isatty(_tty_ch))
					break;
		}
E 7
I 7
D 11
		for (_tty_ch = 0; _tty_ch < nfd; _tty_ch++)
			if (isatty(_tty_ch))
				break;
E 11
E 7
E 3
		gettmode();
		if ((sp = getenv("TERM")) == NULL)
			sp = Def_term;
D 15
		setterm(sp);
# ifdef DEBUG
		fprintf(outf, "INITSCR: term = %s\n", sp);
# endif
E 15
I 15
		if (setterm(sp) == ERR)
			return (NULL);
#ifdef DEBUG
		__TRACE("initscr: term = %s\n", sp);
#endif
E 15
	}
E 18
I 18
	__echoit = 1;
        __pfast = __rawmode = __noqch = 0;

D 19
	if (gettmode() == ERR)
E 19
I 19
D 20
	if (gettmode() == CURSES_ERR)
E 20
I 20
	if (gettmode() == ERR)
E 20
E 19
		return (NULL);

	/*
	 * If My_term is set, or can't find a terminal in the environment,
	 * use Def_term.
	 */
	if (My_term || (sp = getenv("TERM")) == NULL)
		sp = Def_term;
D 19
	if (setterm(sp) == ERR)
E 19
I 19
D 20
	if (setterm(sp) == CURSES_ERR)
E 20
I 20
	if (setterm(sp) == ERR)
E 20
E 19
		return (NULL);

E 18
I 17
	/* Need either homing or cursor motion for refreshes */
	if (!HO && !CM) 
D 18
		return(NULL);
E 18
I 18
		return (NULL);

E 18
E 17
D 3
	else
		setterm(Def_term);
E 3
D 15
	_puts(TI);
	_puts(VS);
I 2
# ifdef SIGTSTP
	signal(SIGTSTP, tstp);
# endif
E 15
I 15
D 21
	tputs(TI, 0, __cputchar);
	tputs(VS, 0, __cputchar);
E 21
I 21
D 22
	__startwin();
E 21
D 18
	(void)signal(SIGTSTP, tstp);
E 15
E 2
	if (curscr != NULL) {
D 15
# ifdef DEBUG
		fprintf(outf, "INITSCR: curscr = 0%o\n", curscr);
# endif
E 15
I 15
#ifdef DEBUG
		__TRACE("initscr: curscr = 0%o\n", curscr);
#endif
E 18
I 18

E 22
	if (curscr != NULL)
E 18
E 15
		delwin(curscr);
D 18
	}
D 15
# ifdef DEBUG
	fprintf(outf, "LINES = %d, COLS = %d\n", LINES, COLS);
# endif
E 15
I 15
#ifdef DEBUG
	__TRACE("initscr: LINES = %d, COLS = %d\n", LINES, COLS);
#endif
E 18
E 15
D 2
	if ((curscr=newwin(LINES, COLS, 0, 0)) == ERR)
E 2
I 2
D 19
	if ((curscr = newwin(LINES, COLS, 0, 0)) == ERR)
E 19
I 19
D 20
	if ((curscr = newwin(LINES, COLS, 0, 0)) == CURSES_ERR)
E 20
I 20
	if ((curscr = newwin(LINES, COLS, 0, 0)) == ERR)
E 20
E 19
E 2
D 15
		return ERR;
D 5
	curscr->_clear = TRUE;
E 5
I 5
	clearok(curscr, TRUE);
E 15
I 15
		return (NULL);
	clearok(curscr, 1);
E 15
D 16
	curscr->_flags &= ~_FULLLINE;
E 16
I 16
D 18
	curscr->flags &= ~__FULLLINE;
E 16
E 5
	if (stdscr != NULL) {
D 15
# ifdef DEBUG
		fprintf(outf, "INITSCR: stdscr = 0%o\n", stdscr);
# endif
E 15
I 15
#ifdef DEBUG
		__TRACE("initscr: stdscr = 0%o\n", stdscr);
#endif
E 18
I 18

	if (stdscr != NULL)
E 18
E 15
		delwin(stdscr);
I 18
D 19
	if ((stdscr = newwin(LINES, COLS, 0, 0)) == ERR) {
E 19
I 19
D 20
	if ((stdscr = newwin(LINES, COLS, 0, 0)) == CURSES_ERR) {
E 20
I 20
	if ((stdscr = newwin(LINES, COLS, 0, 0)) == ERR) {
E 20
E 19
		delwin(curscr);
		return (NULL);
E 18
	}
D 15
	stdscr = newwin(LINES, COLS, 0, 0);
	return stdscr;
E 15
I 15
D 18
	return(stdscr = newwin(LINES, COLS, 0, 0));
E 18
I 18

D 21
	(void)signal(SIGTSTP, tstp);
E 21
I 21
D 24
	(void)signal(SIGTSTP, __stop_signal_handler);
E 24
I 24
	__set_stophandler();
E 24
E 21

#ifdef DEBUG
D 23
	__TRACE("initscr: LINES = %d, COLS = %d\n", LINES, COLS);
E 23
I 23
	__CTRACE("initscr: LINES = %d, COLS = %d\n", LINES, COLS);
E 23
#endif
I 22
	__startwin();

E 22
	return (stdscr);
E 18
E 15
}
I 16
D 22

E 22
E 16
E 1
