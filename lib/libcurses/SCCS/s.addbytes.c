h01848
s 00002/00002/00129
d D 8.4 94/05/04 06:24:27 bostic 29 28
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00001/00129
d D 8.3 94/03/19 13:29:40 bostic 28 27
c It seems to me that addbytes() (and thus addch()) should return ERR if
c you try to go past the end of the window and SCROLLOK is not set.  The
c old code also used to do this; the current code does not.
c This breaks at least one program, mille(6).
c From: Charles Hannum <mycroft@sun-lamp.cs.berkeley.edu>
e
s 00000/00001/00130
d D 8.2 94/01/09 14:37:03 bostic 27 26
c addbytes doesn't need termios.h any more.
e
s 00002/00002/00129
d D 8.1 93/06/11 13:37:12 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00130
d D 5.23 93/06/11 13:36:57 bostic 25 23
c Round #4; try to get ONLCR/NONL right once again
e
s 00002/00002/00129
d R 8.1 93/06/04 16:46:53 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00130
d D 5.22 93/06/04 16:11:56 marc 23 22
c changed to remember and restore TSTP handler, and also to resnapshot tty state when restarting from TSTP.  Also, hardwire GT variable since we always turn tab expansion off.  We still aren't sure what pfast is for, but we haven't given up yet.
e
s 00005/00005/00126
d D 5.21 93/05/16 15:54:33 bostic 22 21
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00000/00009/00131
d D 5.20 93/02/13 14:31:53 bostic 21 20
c add the System V C-string oriented functions (from curs_addstr(TI_LIB));
c make waddstr a macro, minor cleanups
e
s 00002/00000/00138
d D 5.19 93/02/12 17:39:45 torek 20 19
c do not put '\n' characters into the screen data structures
e
s 00002/00002/00136
d D 5.18 93/02/12 09:38:08 bostic 19 18
c make addbytes calls declare const char *
e
s 00001/00001/00137
d D 5.17 93/01/24 20:13:47 bostic 18 17
c rename origtermio to be __orig_termios
e
s 00000/00003/00138
d D 5.16 93/01/11 12:14:08 bostic 17 16
c prettiness police
e
s 00003/00003/00138
d D 5.15 93/01/11 11:53:39 bostic 16 15
c CURSES_{OK,ERR} -> OK,ERR
e
s 00003/00003/00138
d D 5.14 92/12/30 14:54:49 elan 15 14
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00010/00010/00131
d D 5.13 92/11/11 17:35:13 elan 14 13
c Added pointers to firstch and lastch for correct operation of 
c subwindows.
e
s 00006/00005/00135
d D 5.12 92/10/26 12:46:34 elan 13 12
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00023/00006/00117
d D 5.11 92/10/20 10:44:29 elan 12 11
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00028/00016/00095
d D 5.10 92/09/21 15:28:37 elan 11 10
c Added __ISPASTEOL which signifies the fact that the cursor is 
c past the end of the line so that scrolling if turned on will not scroll 
c automatically unless another character is requested to be added.
e
s 00026/00022/00085
d D 5.9 92/09/14 11:00:17 elan 10 9
c Converted to new data structures.
e
s 00006/00004/00101
d D 5.8 92/08/28 15:09:48 elan 9 8
c Fixed '>=' error in window addressing to '>' (caused fence post 
c error). 
c Got rid of NONL.
e
s 00001/00000/00104
d D 5.7 92/08/23 14:38:12 bostic 8 7
c lint
e
s 00007/00006/00097
d D 5.6 92/08/23 09:54:03 bostic 7 6
c SYNCH_OUT and SYNCH_IN reversed on tabs, they didn't work right if the
c first characters in the line.
c don't reset the x and y coordinates unless they're great than win->_maxx
c and win->maxy, didn't work right for the last column of the line
e
s 00083/00089/00020
d D 5.5 92/08/23 09:51:34 bostic 6 4
c KNF
e
s 00085/00089/00020
d R 5.5 92/05/15 14:14:24 bostic 5 4
c reformat to KNF, redo tracing interface, new version for vi; two bug fixes
c Don't reset the x and y coordinates unless > win->_maxx, win->_maxy; this
c change allows you to print in the last column of the window.
c Reverse SYNCH_IN and SYNCH_OUT macro calls for tabs; this change makes
c tabs work right if they're the first characters in the line
e
s 00001/00011/00108
d D 5.4 90/06/01 15:37:10 bostic 4 3
c new copyright notice
e
s 00010/00005/00109
d D 5.3 88/06/30 17:21:09 bostic 3 2
c install approved copyright notice
e
s 00009/00003/00105
d D 5.2 88/06/08 13:56:40 bostic 2 1
c written by Ken Arnold; add Berkeley specific header
e
s 00108/00000/00000
d D 5.1 87/06/24 14:16:35 minshall 1 0
c date and time created 87/06/24 14:16:35 by minshall
e
u
U
t
T
I 1
/*
D 26
 * Copyright (c) 1987 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 26
I 26
D 29
 * Copyright (c) 1987, 1993
E 29
I 29
 * Copyright (c) 1987, 1993, 1994
E 29
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
D 6
#endif /* not lint */
E 6
I 6
#endif	/* not lint */
E 6
E 2

D 6
# include	"curses.ext"
E 6
I 6
D 29
#include <curses.h>
E 29
I 29
#include "curses.h"
E 29
I 9
D 27
#include <termios.h>
E 27
E 9
E 6

I 6
D 10
#define	SYNCH_IN	{y = win->_cury; x = win->_curx;}
#define	SYNCH_OUT	{win->_cury = y; win->_curx = x;}
E 10
I 10
#define	SYNCH_IN	{y = win->cury; x = win->curx;}
#define	SYNCH_OUT	{win->cury = y; win->curx = x;}
E 10

I 12
D 21
int
waddbytes(win, bytes, count)
	WINDOW *win;
D 19
	char *bytes;
E 19
I 19
	const char *bytes;
E 19
	int count;
{
	__waddbytes(win, bytes, count, 0);
}

E 21
D 17


E 17
E 12
E 6
/*
D 6
 *	This routine adds the character to the current position
 *
E 6
I 6
 * waddbytes --
 *	Add the character to the current position in the given window.
E 6
 */
I 8
int
E 8
D 12
waddbytes(win, bytes, count)
E 12
I 12
__waddbytes(win, bytes, count, so)
E 12
D 6
reg WINDOW	*win;
reg char	*bytes;
reg int		count;
E 6
I 6
	register WINDOW *win;
D 19
	register char *bytes;
E 19
I 19
	register const char *bytes;
E 19
	register int count;
I 12
	int so;
E 12
E 6
{
D 6
#define	SYNCH_OUT()	{win->_cury = y; win->_curx = x;}
#define	SYNCH_IN()	{y = win->_cury; x = win->_curx;}
	reg int		x, y;
	reg int		newx;
E 6
I 6
	static char blanks[] = "        ";
	register int c, newx, x, y;
I 12
	char stand;
E 12
I 10
D 13
	LINE *lp;
E 13
I 13
	__LINE *lp;
E 13
E 10
E 6

D 6
	SYNCH_IN();
# ifdef FULLDEBUG
	fprintf(outf, "ADDBYTES('%c') at (%d, %d)\n", c, y, x);
# endif
E 6
I 6
	SYNCH_IN;
I 9

E 9
#ifdef DEBUG
D 22
	__TRACE("ADDBYTES('%c') at (%d, %d)\n", c, y, x);
E 22
I 22
	__CTRACE("ADDBYTES('%c') at (%d, %d)\n", c, y, x);
E 22
#endif
E 6
	while (count--) {
D 6
	    register int c;
	    static char blanks[] = "        ";
E 6
I 6
		c = *bytes++;
		switch (c) {
		case '\t':
D 7
			SYNCH_IN;
E 7
I 7
			SYNCH_OUT;
E 7
D 15
			if (waddbytes(win, blanks, 8 - (x % 8)) == ERR)
				return (ERR);
E 15
I 15
D 16
			if (waddbytes(win, blanks, 8 - (x % 8)) == CURSES_ERR)
				return (CURSES_ERR);
E 16
I 16
			if (waddbytes(win, blanks, 8 - (x % 8)) == ERR)
				return (ERR);
E 16
E 15
D 7
			SYNCH_OUT;
E 7
I 7
			SYNCH_IN;
E 7
			break;
E 6

D 6
	    c = *bytes++;
	    switch (c) {
	      case '\t':
		    SYNCH_IN();
		    if (waddbytes(win, blanks, 8-(x%8)) == ERR) {
			return ERR;
		    }
		    SYNCH_OUT();
		    break;

	      default:
# ifdef FULLDEBUG
		    fprintf(outf, "ADDBYTES: 1: y = %d, x = %d, firstch = %d, lastch = %d\n", y, x, win->_firstch[y], win->_lastch[y]);
# endif
		    if (win->_flags & _STANDOUT)
			    c |= _STANDOUT;
		    {
# ifdef	FULLDEBUG
			    fprintf(outf, "ADDBYTES(%0.2o, %d, %d)\n", win, y, x);
# endif
			    if (win->_y[y][x] != c) {
				    newx = x + win->_ch_off;
				    if (win->_firstch[y] == _NOCHANGE) {
					    win->_firstch[y] =
							    win->_lastch[y] = newx;
				    } else if (newx < win->_firstch[y])
					    win->_firstch[y] = newx;
				    else if (newx > win->_lastch[y])
E 6
I 6
		default:
D 11
#ifdef DEBUG
	__TRACE("ADDBYTES: 1: y = %d, x = %d, firstch = %d, lastch = %d\n",
D 10
	    y, x, win->_firstch[y], win->_lastch[y]);
E 10
I 10
	    y, x, win->lines[y]->firstch, win->lines[y]->lastch);
E 10
#endif
E 11
D 10
			if (win->_flags & _STANDOUT)
				c |= _STANDOUT;
E 10
I 10
D 12
			if (win->flags & __WSTANDOUT)
				c |= __STANDOUT;
E 12
E 10
#ifdef DEBUG
D 22
	__TRACE("ADDBYTES(%0.2o, %d, %d)\n", win, y, x);
E 22
I 22
	__CTRACE("ADDBYTES(%0.2o, %d, %d)\n", win, y, x);
E 22
#endif
D 10
			if (win->_y[y][x] != c) {
				newx = x + win->_ch_off;
				if (win->_firstch[y] == _NOCHANGE)
					win->_firstch[y] =
E 6
					    win->_lastch[y] = newx;
D 6
# ifdef FULLDEBUG
				    fprintf(outf, "ADDBYTES: change gives f/l: %d/%d [%d/%d]\n",
					    win->_firstch[y], win->_lastch[y],
					    win->_firstch[y] - win->_ch_off,
					    win->_lastch[y] - win->_ch_off);
# endif
			    }
		    }
		    win->_y[y][x++] = c;
		    if (x >= win->_maxx) {
			    x = 0;
    newline:
			    if (++y >= win->_maxy)
				    if (win->_scroll) {
					    SYNCH_OUT();
					    scroll(win);
					    SYNCH_IN();
					    --y;
				    }
				    else
					    return ERR;
		    }
# ifdef FULLDEBUG
		    fprintf(outf, "ADDBYTES: 2: y = %d, x = %d, firstch = %d, lastch = %d\n", y, x, win->_firstch[y], win->_lastch[y]);
# endif
		    break;
	      case '\n':
		    SYNCH_OUT();
		    wclrtoeol(win);
		    SYNCH_IN();
		    if (!NONL)
			    x = 0;
		    goto newline;
	      case '\r':
		    x = 0;
		    break;
	      case '\b':
		    if (--x < 0)
			    x = 0;
		    break;
	    }
    }
    SYNCH_OUT();
    return OK;
E 6
I 6
				else if (newx < win->_firstch[y])
					win->_firstch[y] = newx;
				else if (newx > win->_lastch[y])
					win->_lastch[y] = newx;
E 10
I 10
D 11
			lp = win->lines[y];
E 11
			
I 11
			lp = win->lines[y];
			if (lp->flags & __ISPASTEOL) {
				lp->flags &= ~__ISPASTEOL;
newline:			if (y == win->maxy - 1) {
					if (win->flags & __SCROLLOK) {
D 12
					        x = 0;
E 12
						SYNCH_OUT;
						scroll(win);
						SYNCH_IN;
						lp = win->lines[y];
I 12
					        x = 0;
E 12
D 28
					} 
E 28
I 28
					} else
						return (ERR);
E 28
				} else {
					y++;
					lp = win->lines[y];
					x = 0;
				}
I 20
				if (c == '\n')
					break;
E 20
			}
				
D 12
							
E 12
I 12
			stand = '\0';
			if (win->flags & __WSTANDOUT || so)
				stand |= __STANDOUT;
E 12
#ifdef DEBUG
D 22
	__TRACE("ADDBYTES: 1: y = %d, x = %d, firstch = %d, lastch = %d\n",
E 22
I 22
	__CTRACE("ADDBYTES: 1: y = %d, x = %d, firstch = %d, lastch = %d\n",
E 22
D 14
	    y, x, win->lines[y]->firstch, win->lines[y]->lastch);
E 14
I 14
	    y, x, *win->lines[y]->firstchp, *win->lines[y]->lastchp);
E 14
#endif
E 11
D 12
			if (lp->line[x] != c) {
E 12
I 12
D 13
			if (lp->line[x] != c || !(lp->standout[x] & stand)) {
E 13
I 13
			if (lp->line[x].ch != c || 
			    !(lp->line[x].attr & stand)) {
E 13
E 12
				newx = x + win->ch_off;
				if (!(lp->flags & __ISDIRTY)) {
					lp->flags |= __ISDIRTY;
D 14
					lp->firstch = lp->lastch = newx;
E 14
I 14
					*lp->firstchp = *lp->lastchp = newx;
E 14
				}
D 14
				else if (newx < lp->firstch)
					lp->firstch = newx;
				else if (newx > lp->lastch)
					lp->lastch = newx;
E 14
I 14
				else if (newx < *lp->firstchp)
					*lp->firstchp = newx;
				else if (newx > *lp->lastchp)
					*lp->lastchp = newx;
E 14
E 10
D 7
#ifdef __TRACE
E 7
I 7
#ifdef DEBUG
E 7
D 22
	__TRACE("ADDBYTES: change gives f/l: %d/%d [%d/%d]\n",
E 22
I 22
	__CTRACE("ADDBYTES: change gives f/l: %d/%d [%d/%d]\n",
E 22
D 7
	    win->_firstch[y], win->_lastch[y], win->_firstch[y] - win->_ch_off,
E 7
I 7
D 10
	    win->_firstch[y], win->_lastch[y],
	    win->_firstch[y] - win->_ch_off,
E 7
	    win->_lastch[y] - win->_ch_off);
E 10
I 10
D 14
	    lp->firstch, lp->lastch,
	    lp->firstch - win->ch_off,
	    lp->lastch - win->ch_off);
E 14
I 14
	    *lp->firstchp, *lp->lastchp,
	    *lp->firstchp - win->ch_off,
	    *lp->lastchp - win->ch_off);
E 14
E 10
#endif
			}
D 9
			win->_y[y][x++] = c;
D 7
			if (x >= win->_maxx) {
E 7
I 7
			if (x > win->_maxx) {
E 9
I 9
D 10
			win->_y[y][x] = c;
			if (++x >= win->_maxx) {
E 10
I 10
D 13
			lp->line[x] = c;
E 13
I 13
			lp->line[x].ch = c;
E 13
I 12
			if (stand)
D 13
				lp->standout[x] |= __STANDOUT;
E 13
I 13
				lp->line[x].attr |= __STANDOUT;
E 13
			else
D 13
				lp->standout[x] &= ~__STANDOUT;
E 13
I 13
				lp->line[x].attr &= ~__STANDOUT;
E 13
E 12
D 11
			if (++x >= win->maxx) {
E 10
E 9
E 7
				x = 0;
D 7
newline:			if (++y >= win->_maxy)
E 7
I 7
D 9
newline:			if (++y > win->_maxy)
E 9
I 9
D 10
newline:			if (++y >= win->_maxy)
E 9
E 7
					if (win->_scroll) {
E 10
I 10
newline:			if (++y >= win->maxy) 
					if (win->flags & __SCROLLOK) {
E 10
						SYNCH_OUT;
						scroll(win);
						SYNCH_IN;
						--y;
					} else
						return (ERR);
			}
E 11
I 11
			if (x == win->maxx - 1)
				lp->flags |= __ISPASTEOL;
			else
				x++;
E 11
#ifdef DEBUG
D 22
	__TRACE("ADDBYTES: 2: y = %d, x = %d, firstch = %d, lastch = %d\n",
E 22
I 22
	__CTRACE("ADDBYTES: 2: y = %d, x = %d, firstch = %d, lastch = %d\n",
E 22
D 10
	    y, x, win->_firstch[y], win->_lastch[y]);
E 10
I 10
D 14
	    y, x, win->lines[y]->firstch, win->lines[y]->lastch);
E 14
I 14
	    y, x, *win->lines[y]->firstchp, *win->lines[y]->lastchp);
E 14
E 10
#endif
			break;
		case '\n':
			SYNCH_OUT;
			wclrtoeol(win);
			SYNCH_IN;
D 9
			if (!NONL)
E 9
I 9
D 18
			if (origtermio.c_oflag & ONLCR)
E 18
I 18
D 23
			if (__orig_termios.c_oflag & ONLCR)
E 23
I 23
D 25
			if (__baset.c_oflag & ONLCR)
E 25
I 25
			if (!NONL)
E 25
E 23
E 18
E 9
				x = 0;
			goto newline;
		case '\r':
			x = 0;
			break;
		case '\b':
			if (--x < 0)
				x = 0;
			break;
		}
	}
	SYNCH_OUT;
D 15
	return (OK);
E 15
I 15
D 16
	return (CURSES_OK);
E 16
I 16
	return (OK);
E 16
E 15
E 6
}
I 11
D 17
 
E 17
E 11
E 1
