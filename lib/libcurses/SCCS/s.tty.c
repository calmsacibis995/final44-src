h01540
s 00001/00001/00254
d D 8.6 95/01/10 16:36:12 bostic 25 24
c typo, wrong parameter to __mvcur in endwin()
e
s 00019/00001/00236
d D 8.5 94/08/13 15:43:23 bostic 24 23
c use 8K buffering for stdout -- some C libraries use 1K
e
s 00011/00011/00226
d D 8.4 94/05/18 15:47:30 bostic 23 22
c fix return values for tty function
e
s 00003/00004/00234
d D 8.3 94/05/04 06:25:06 bostic 22 21
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00000/00236
d D 8.2 94/01/02 12:29:49 bostic 21 20
c endwin() needs to restore the stop signal handler
e
s 00002/00002/00234
d D 8.1 93/06/07 12:23:07 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00032/00022/00204
d D 5.18 93/06/07 12:23:00 bostic 19 17
c change so users can set __tcaction if they want to switch behavior
c use `curt' consistently in calls to tcsetattr; if __tcaction not set, set
c the hardware bits in the raw structure 
e
s 00002/00002/00224
d R 8.1 93/06/04 16:49:34 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00031/00029/00195
d D 5.17 93/06/04 16:12:01 marc 17 16
c changed to remember and restore TSTP handler, and also to resnapshot tty state when restarting from TSTP.  Also, hardwire GT variable since we always turn tab expansion off.  We still aren't sure what pfast is for, but we haven't given up yet.
e
s 00066/00049/00158
d D 5.16 93/05/30 18:55:53 bostic 16 15
c Mike Karels of BSDI's changes to make curses leave tty hardware options
c alone
e
s 00010/00000/00197
d D 5.15 93/05/30 14:20:04 bostic 15 14
c System V and SMI systems overload VMIN and VTIME
e
s 00008/00000/00189
d D 5.14 93/05/30 13:14:36 bostic 14 13
c Sun uses XTABS, not OXTABS
e
s 00001/00001/00188
d D 5.13 93/05/16 21:40:45 bostic 13 12
c messed up the translation, though
e
s 00001/00001/00188
d D 5.12 93/05/16 21:37:04 bostic 12 11
c some preprocessors try to redefine the mvcur prototype to be __mvcur
c which fails miserably; don't use mvcur internally, either
e
s 00000/00003/00189
d D 5.11 93/05/12 12:26:50 elan 11 10
c Don't want to reset __echoit, __rawmode, and __pfast in endwin().
e
s 00011/00007/00181
d D 5.10 93/05/10 12:13:53 bostic 10 9
c turn off line buffering in __startwin(), turn it back on in endwin()
e
s 00022/00013/00166
d D 5.9 93/01/24 20:14:48 bostic 9 8
c rename origtermio to be __orig_termios
e
s 00002/00003/00177
d D 5.8 93/01/11 11:54:04 bostic 8 7
c CURSES_{OK,ERR} -> OK,ERR
e
s 00003/00002/00177
d D 5.7 92/12/30 14:55:13 elan 7 6
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00001/00000/00178
d D 5.6 92/12/29 10:50:25 elan 6 5
c endwin() leaves cursor at lower left upon exit.
e
s 00006/00007/00172
d D 5.5 92/12/22 15:03:15 bostic 5 4
c don't need newtermio, initialize useraw in case called twice
c delete __endwin (I don't understand it)
e
s 00001/00001/00178
d D 5.4 92/12/22 13:39:17 bostic 4 3
c err if tcgetattr fails
e
s 00002/00002/00177
d D 5.3 92/09/14 11:00:46 elan 3 2
c Converted to new data structures.
e
s 00005/00001/00174
d D 5.2 92/08/31 14:28:35 elan 2 1
c Fixed reference to NONL.  NONL now refers to *output* newlines 
c rather than both input and output as before.  Also, since new
c termio has 2 different flags for input and output -- they need
c to each be set.  Fixed this as well.
e
s 00175/00000/00000
d D 5.1 92/08/23 14:44:10 bostic 1 0
c date and time created 92/08/23 14:44:10 by bostic
e
u
U
t
T
I 1
/*-
D 20
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
D 22
 * Copyright (c) 1992, 1993
E 22
I 22
 * Copyright (c) 1992, 1993, 1994
E 22
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 24
#include <stdlib.h>
E 24
D 16
/*
 * Terminal initialization routines.
 */
E 16
D 22
#include <sys/ioctl.h>

#include <curses.h>
E 22
#include <termios.h>
#include <unistd.h>
I 22

#include "curses.h"
E 22

I 16
/*
 * In general, curses should leave tty hardware settings alone (speed, parity,
 * word size).  This is most easily done in BSD by using TCSASOFT on all
 * tcsetattr calls.  On other systems, it would be better to get and restore
 * those attributes at each change, or at least when stopped and restarted.
 * See also the comments in getterm().
 */
#ifdef TCSASOFT
D 17
#define	TCACTION (TCSASOFT | TCSADRAIN)		/* ignore hardware settings */
E 17
I 17
D 19
int __tcaction = TCSASOFT | TCSADRAIN;         /* ignore hardware settings */
E 19
I 19
int __tcaction = 1;			/* Ignore hardware settings. */
E 19
E 17
#else
D 17
#define	TCACTION  TCSADRAIN
E 17
I 17
D 19
int __tcaction = TCSADRAIN;
E 19
I 19
int __tcaction = 0;
E 19
E 17
#endif

E 16
D 5
struct termios newtermio, origtermio;
E 5
I 5
D 9
struct termios origtermio;
E 9
I 9
D 17
struct termios __orig_termios;
E 9
E 5
D 16
static struct termios norawt, rawt;
E 16
I 16
static struct termios baset, cbreakt, rawt, *curt;
E 17
I 17
D 19
/* was, pfast = rand() % HARDTABS; */

E 19
struct termios __orig_termios, __baset;
static struct termios cbreakt, rawt, *curt;
E 17
E 16
static int useraw;

I 14
#ifndef	OXTABS
#ifdef	XTABS			/* SMI uses XTABS. */
#define	OXTABS	XTABS
#else
#define	OXTABS	0
#endif
#endif

E 14
/*
 * gettmode --
 *	Do terminal type initialization.
 */
int
gettmode()
{
I 5
	useraw = 0;
	
E 5
D 9
	if (tcgetattr(STDIN_FILENO, &origtermio))
E 9
I 9
	if (tcgetattr(STDIN_FILENO, &__orig_termios))
E 9
D 4
		return (OK);
E 4
I 4
D 7
		return (ERR);
E 7
I 7
D 8
		return (CURSES_ERR);
E 8
I 8
		return (ERR);
E 8
E 7
E 4

D 9
	GT = (origtermio.c_oflag & OXTABS) == 0;
D 2
	NONL = (origtermio.c_iflag & ICRNL) == 0;
E 2
I 2
	NONL = (origtermio.c_oflag & ONLCR) == 0;
E 9
I 9
D 17
	GT = (__orig_termios.c_oflag & OXTABS) == 0;
	NONL = (__orig_termios.c_oflag & ONLCR) == 0;
E 17
I 17
	__baset = __orig_termios;
	__baset.c_oflag &= ~OXTABS;
E 17
E 9
E 2

D 9
	norawt = origtermio;
E 9
I 9
D 16
	norawt = __orig_termios;
E 9
	norawt.c_oflag &= ~OXTABS;
E 16
I 16
D 17
	baset = __orig_termios;
	baset.c_oflag &= ~OXTABS;
E 17
I 17
	GT = 0;		/* historical. was used before we wired OXTABS off */
	NONL = (__baset.c_oflag & ONLCR) == 0;
E 17
E 16
I 15

	/*
	 * XXX
	 * System V and SMI systems overload VMIN and VTIME, such that
	 * VMIN is the same as the VEOF element, and VTIME is the same
	 * as the VEOL element.  This means that, if VEOF was ^D, the
	 * default VMIN is 4.  Majorly stupid.
	 */
E 15
D 16
	rawt = norawt;
	cfmakeraw(&rawt);
I 15
	rawt.c_cc[VMIN] = 1;
	rawt.c_cc[VTIME] = 0;
E 16
I 16
D 17
	cbreakt = baset;
E 17
I 17
	cbreakt = __baset;
E 17
	cbreakt.c_lflag &= ~ICANON;
	cbreakt.c_cc[VMIN] = 1;
	cbreakt.c_cc[VTIME] = 0;
E 16
E 15

D 7
	return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt) ? ERR : OK);
E 7
I 7
D 8
	return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt) ? CURSES_ERR : 
							      CURSES_OK);
E 8
I 8
D 16
	return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt) ? ERR : OK);
E 16
I 16
	rawt = cbreakt;
	rawt.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|INLCR|IGNCR|ICRNL|IXON);
	rawt.c_oflag &= ~OPOST;
	rawt.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
D 19
#if 0
E 19
I 19

E 19
	/*
	 * In general, curses should leave hardware-related settings alone.
	 * This includes parity and word size.  Older versions set the tty
	 * to 8 bits, no parity in raw(), but this is considered to be an
	 * artifact of the old tty interface.  If it's desired to change
D 19
	 * parity and word size, the TCSASOFT bit would have to be removed
	 * from the calls that switch to/from "raw" mode.
E 19
I 19
	 * parity and word size, the TCSASOFT bit has to be removed from the
	 * calls that switch to/from "raw" mode.
E 19
	 */
D 19
	rawt.c_iflag &= ~ISTRIP;
	rawt.c_cflag &= ~(CSIZE|PARENB);
	rawt.c_cflag |= CS8;
#endif
E 19
I 19
	if (!__tcaction) {
		rawt.c_iflag &= ~ISTRIP;
		rawt.c_cflag &= ~(CSIZE|PARENB);
		rawt.c_cflag |= CS8;
	}
E 19

D 17
	curt = &baset;
	return (tcsetattr(STDIN_FILENO, TCACTION, &baset) ? ERR : OK);
E 17
I 17
	curt = &__baset;
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, &__baset) ? ERR : OK);
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt) ? ERR : OK);
E 19
E 17
E 16
E 8
E 7
}

int
raw()
{
	useraw = __pfast = __rawmode = 1;
D 16
	return (tcsetattr(STDIN_FILENO, TCSADRAIN, &rawt));
E 16
I 16
	curt = &rawt;
D 17
	return (tcsetattr(STDIN_FILENO, TCACTION, &rawt));
E 17
I 17
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, &rawt));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt) ? ERR : OK);
E 23
E 19
E 17
E 16
}

int
noraw()
{
	useraw = __pfast = __rawmode = 0;
D 16
	return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt));
E 16
I 16
D 17
	curt = &baset;
	return (tcsetattr(STDIN_FILENO, TCACTION, &baset));
E 17
I 17
	curt = &__baset;
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, &__baset));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt) ? ERR : OK);
E 23
E 19
E 17
E 16
}

int
cbreak()
{
D 16
	rawt.c_lflag &= ~ICANON;
	norawt.c_lflag &= ~ICANON;
E 16

	__rawmode = 1;
D 16
	if (useraw)
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &rawt));
	else
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt));
E 16
I 16
	curt = useraw ? &rawt : &cbreakt;
D 17
	return (tcsetattr(STDIN_FILENO, TCACTION, curt));
E 17
I 17
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, curt));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt) ? ERR : OK);
E 23
E 19
E 17
E 16
}

int
nocbreak()
{
D 16
	rawt.c_lflag |= ICANON;
	norawt.c_lflag |= ICANON;
E 16

	__rawmode = 0;
D 16
	if (useraw) 
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &rawt));
	else
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt));
E 16
I 16
D 17
	curt = useraw ? &rawt : &baset;
	return (tcsetattr(STDIN_FILENO, TCACTION, curt));
E 17
I 17
	curt = useraw ? &rawt : &__baset;
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, curt));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt) ? ERR : OK);
E 23
E 19
E 17
E 16
}
	
int
echo()
{
	rawt.c_lflag |= ECHO;
D 16
	norawt.c_lflag |= ECHO;
E 16
I 16
	cbreakt.c_lflag |= ECHO;
D 17
	baset.c_lflag |= ECHO;
E 17
I 17
	__baset.c_lflag |= ECHO;
E 17
E 16
	
	__echoit = 1;
D 16
	if (useraw) 
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &rawt));
	else
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt));
E 16
I 16
D 17
	return (tcsetattr(STDIN_FILENO, TCACTION, curt));
E 17
I 17
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, curt));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt) ? ERR : OK);
E 23
E 19
E 17
E 16
}

int
noecho()
{
	rawt.c_lflag &= ~ECHO;
D 16
	norawt.c_lflag &= ~ECHO;
E 16
I 16
	cbreakt.c_lflag &= ~ECHO;
D 17
	baset.c_lflag &= ~ECHO;
E 17
I 17
	__baset.c_lflag &= ~ECHO;
E 17
E 16
	
	__echoit = 0;
D 16
	if (useraw) 
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &rawt));
	else
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt));
E 16
I 16
D 17
	return (tcsetattr(STDIN_FILENO, TCACTION, curt));
E 17
I 17
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, curt));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt) ? ERR : OK);
E 23
E 19
E 17
E 16
}

int
nl()
{
	rawt.c_iflag |= ICRNL;
	rawt.c_oflag |= ONLCR;
I 2
D 16
	norawt.c_iflag |= ICRNL;
	norawt.c_oflag |= ONLCR;
E 16
I 16
	cbreakt.c_iflag |= ICRNL;
	cbreakt.c_oflag |= ONLCR;
D 17
	baset.c_iflag |= ICRNL;
	baset.c_oflag |= ONLCR;
E 17
I 17
	__baset.c_iflag |= ICRNL;
	__baset.c_oflag |= ONLCR;
E 17
E 16
E 2

	__pfast = __rawmode;
D 16
	if (useraw) 
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &rawt));
	else
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt));
E 16
I 16
D 17
	return (tcsetattr(STDIN_FILENO, TCACTION, curt));
E 17
I 17
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, curt));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt) ? ERR : OK);
E 23
E 19
E 17
E 16
}

int
nonl()
{
	rawt.c_iflag &= ~ICRNL;
	rawt.c_oflag &= ~ONLCR;
I 2
D 16
	norawt.c_iflag &= ~ICRNL;
	norawt.c_oflag &= ~ONLCR;
E 16
I 16
	cbreakt.c_iflag &= ~ICRNL;
	cbreakt.c_oflag &= ~ONLCR;
D 17
	baset.c_iflag &= ~ICRNL;
	baset.c_oflag &= ~ONLCR;
E 17
I 17
	__baset.c_iflag &= ~ICRNL;
	__baset.c_oflag &= ~ONLCR;
E 17
E 16
E 2

	__pfast = 1;
D 16
	if (useraw) 
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &rawt));
	else
		return (tcsetattr(STDIN_FILENO, TCSADRAIN, &norawt));
E 16
I 16
D 17
	return (tcsetattr(STDIN_FILENO, TCACTION, curt));
E 17
I 17
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, curt));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, curt) ? ERR : OK);
E 23
E 19
E 17
E 16
}

I 10
void
__startwin()
{
I 24
	static char *stdbuf;
	static size_t len;

E 24
	(void)fflush(stdout);
D 24
	(void)setvbuf(stdout, NULL, _IOFBF, 0);
E 24
I 24

	/*
	 * Some C libraries default to a 1K buffer when talking to a tty.
	 * With a larger screen, especially across a network, we'd like
	 * to get it to all flush in a single write.  Make it twice as big
	 * as just the characters (so that we have room for cursor motions
	 * and standout information) but no more than 8K.
	 */
	if (stdbuf == NULL) {
		if ((len = LINES * COLS * 2) > 8192)
			len = 8192;
		if ((stdbuf = malloc(len)) == NULL)
			len = 0;
	}
	(void)setvbuf(stdout, stdbuf, _IOFBF, len);
E 24

	tputs(TI, 0, __cputchar);
	tputs(VS, 0, __cputchar);
}

E 10
int
endwin()
{
I 21
	__restore_stophandler();

E 21
D 5
	if (curscr) {
D 3
		if (curscr->_flags & _STANDOUT) {
E 3
I 3
		if (curscr->flags & __WSTANDOUT) {
E 3
			tputs(SE, 0, __cputchar);
D 3
			curscr->_flags &= ~_STANDOUT;
E 3
I 3
			curscr->flags &= ~__WSTANDOUT;
E 3
		}
		__endwin = 1;
E 5
I 5
D 9
	if (curscr && curscr->flags & __WSTANDOUT) {
		tputs(SE, 0, __cputchar);
		curscr->flags &= ~__WSTANDOUT;
E 9
I 9
	if (curscr != NULL) {
		if (curscr->flags & __WSTANDOUT) {
			tputs(SE, 0, __cputchar);
			curscr->flags &= ~__WSTANDOUT;
		}
D 12
		mvcur(curscr->cury, curscr->cury, curscr->maxy - 1, 0);
E 12
I 12
D 13
		__mvcur(curscr->cury, curscr->cury, curscr->maxy - 1, 0);
E 13
I 13
D 25
		__mvcur(curscr->cury, curscr->cury, curscr->maxy - 1, 0, 0);
E 25
I 25
		__mvcur(curscr->cury, curscr->curx, curscr->maxy - 1, 0, 0);
E 25
E 13
E 12
E 9
E 5
	}

	(void)tputs(VE, 0, __cputchar);
	(void)tputs(TE, 0, __cputchar);
I 6
D 9
	mvcur(curscr->cury, curscr->cury, curscr->maxy - 1, 0);
E 9
E 6
	(void)fflush(stdout);
I 10
	(void)setvbuf(stdout, NULL, _IOLBF, 0);
E 10

D 9
	__echoit = origtermio.c_lflag & ECHO;
	__rawmode = origtermio.c_lflag & ICANON;
	__pfast = origtermio.c_iflag & ICRNL ? __rawmode : 1;
	return (tcsetattr(STDIN_FILENO, TCSADRAIN, &origtermio));
E 9
I 9
D 11
	__echoit = __orig_termios.c_lflag & ECHO;
	__rawmode = __orig_termios.c_lflag & ICANON;
	__pfast = __orig_termios.c_iflag & ICRNL ? __rawmode : 1;
E 11
D 16
	return (tcsetattr(STDIN_FILENO, TCSADRAIN, &__orig_termios));
E 16
I 16
D 17
	return (tcsetattr(STDIN_FILENO, TCACTION, &__orig_termios));
E 17
I 17
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, &__orig_termios));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, &__orig_termios));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, &__orig_termios) ? ERR : OK);
E 23
E 19
E 17
E 16
D 10
}

void
__startwin()
{
	tputs(TI, 0, __cputchar);
	tputs(VS, 0, __cputchar);
E 10
E 9
}

/*
 * The following routines, savetty and resetty are completely useless and
 * are left in only as stubs.  If people actually use them they will almost
 * certainly screw up the state of the world.
 */
static struct termios savedtty;
int
savetty()
{
D 23
	return (tcgetattr(STDIN_FILENO, &savedtty));
E 23
I 23
	return (tcgetattr(STDIN_FILENO, &savedtty) ? ERR : OK);
E 23
}

int
resetty()
{
D 16
	return (tcsetattr(STDIN_FILENO, TCSADRAIN, &savedtty));
E 16
I 16
D 17
	return (tcsetattr(STDIN_FILENO, TCACTION, &savedtty));
E 17
I 17
D 19
	return (tcsetattr(STDIN_FILENO, __tcaction, &savedtty));
E 19
I 19
	return (tcsetattr(STDIN_FILENO, __tcaction ?
D 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, &savedtty));
E 23
I 23
	    TCSASOFT | TCSADRAIN : TCSADRAIN, &savedtty) ? ERR : OK);
E 23
E 19
E 17
E 16
}
E 1
