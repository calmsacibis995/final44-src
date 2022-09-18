h19231
s 00002/00003/00092
d D 8.2 94/05/04 06:25:01 bostic 18 17
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00093
d D 8.1 93/06/04 16:49:25 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00090
d D 5.12 93/05/16 15:54:52 bostic 16 15
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00003/00001/00092
d D 5.11 93/02/18 16:48:22 elan 15 14
c touchwin needs to return an int.
e
s 00003/00003/00090
d D 5.10 93/01/11 11:54:03 bostic 14 13
c CURSES_{OK,ERR} -> OK,ERR
e
s 00003/00003/00090
d D 5.9 92/12/30 14:55:03 elan 13 12
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00008/00008/00085
d D 5.8 92/11/11 17:35:14 elan 12 11
c Added pointers to firstch and lastch for correct operation of 
c subwindows.
e
s 00036/00007/00057
d D 5.7 92/10/27 14:38:01 elan 11 10
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00014/00013/00050
d D 5.6 92/09/14 11:00:44 elan 10 9
c Converted to new data structures.
e
s 00026/00020/00037
d D 5.5 92/08/23 12:20:59 bostic 9 7
c KNF
e
s 00025/00017/00040
d R 5.5 92/05/15 15:26:52 bostic 8 7
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00056
d D 5.4 90/06/01 15:40:39 bostic 7 6
c new copyright notice
e
s 00010/00005/00057
d D 5.3 88/06/30 17:22:08 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00052
d D 5.2 88/06/08 13:57:50 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00046
d D 5.1 85/06/07 11:43:19 dist 4 3
c Add copyright
e
s 00032/00019/00015
d D 1.3 85/05/01 17:36:51 bloom 3 2
c new version from arnold
e
s 00015/00000/00019
d D 1.2 83/05/09 20:35:28 arnold 2 1
c integrate subwindows fully into all parts of curses
e
s 00019/00000/00000
d D 1.1 81/01/26 17:03:16 arnold 1 0
c date and time created 81/01/26 17:03:16 by arnold
e
u
U
t
T
I 4
/*
D 5
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 17
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 17
I 17
D 18
 * Copyright (c) 1981, 1993
E 18
I 18
 * Copyright (c) 1981, 1993, 1994
E 18
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

E 4
I 1
D 9
# include	"curses.ext"
E 9
I 9
D 18
#include <curses.h>
E 9

E 18
I 18
#include "curses.h"
E 18
I 11

E 11
/*
I 11
 * touchline --
 *	Touch a given line.
 */
int
touchline(win, y, sx, ex)
	WINDOW *win;
	register int y, sx, ex;
{
D 15
	__touchline(win, y, sx, ex, 1);
E 15
I 15
	return (__touchline(win, y, sx, ex, 1));
E 15
}


/*
E 11
D 9
 * make it look like the whole window has been changed.
 *
E 9
I 9
 * touchwin --
 *	Make it look like the whole window has been changed.
E 9
D 3
 * %G% (Berkeley) %W%
E 3
I 3
D 4
 * %W% (Berkeley) %G%
E 4
E 3
 */
I 9
int
E 9
touchwin(win)
D 3
reg WINDOW	*win;
E 3
I 3
D 9
register WINDOW	*win;
E 9
I 9
	register WINDOW *win;
E 9
E 3
{
I 2
D 3
	reg WINDOW	*wp;
E 3
I 3
D 9
	register int	y, maxy;
E 9
I 9
	register int y, maxy;
E 9
E 3

D 3
	do_touch(win);
	for (wp = win->_nextp; wp != win; wp = wp->_nextp)
		do_touch(wp);
E 3
I 3
D 9
# ifdef	DEBUG
	fprintf(outf, "TOUCHWIN(%0.2o)\n", win);
# endif
E 9
I 9
#ifdef DEBUG
D 16
	__TRACE("touchwin: (%0.2o)\n", win);
E 16
I 16
	__CTRACE("touchwin: (%0.2o)\n", win);
E 16
#endif
E 9
D 10
	maxy = win->_maxy;
E 10
I 10
	maxy = win->maxy;
E 10
	for (y = 0; y < maxy; y++)
D 10
		touchline(win, y, 0, win->_maxx - 1);
E 10
I 10
D 11
		touchline(win, y, 0, win->maxx - 1);
E 11
I 11
		__touchline(win, y, 0, win->maxx - 1, 1);
E 11
E 10
I 9
D 13
	return (OK);
E 13
I 13
D 14
	return (CURSES_OK);
E 14
I 14
	return (OK);
E 14
E 13
E 9
E 3
}

D 11
/*
D 3
 * do_touch:
 *	Touch the window
E 3
I 3
D 9
 * touch a given line
E 9
I 9
 * touchline --
 *	Touch a given line.
E 9
E 3
 */
E 11
I 11

E 11
I 9
int
E 9
D 3
static
do_touch(win)
reg WINDOW	*win; {

E 2
	reg int		y, maxy, maxx;

	maxy = win->_maxy;
	maxx = win->_maxx - 1;
	for (y = 0; y < maxy; y++) {
		win->_firstch[y] = 0;
		win->_lastch[y] = maxx;
E 3
I 3
D 11
touchline(win, y, sx, ex)
E 11
I 11
__touchwin(win)
E 11
D 9
register WINDOW	*win;
register int	y, sx, ex;
E 9
I 9
	register WINDOW *win;
I 11
{
	register int y, maxy;

#ifdef DEBUG
D 16
	__TRACE("touchwin: (%0.2o)\n", win);
E 16
I 16
	__CTRACE("touchwin: (%0.2o)\n", win);
E 16
#endif
	maxy = win->maxy;
	for (y = 0; y < maxy; y++)
		__touchline(win, y, 0, win->maxx - 1, 0);
D 13
	return (OK);
E 13
I 13
D 14
	return (CURSES_OK);
E 14
I 14
	return (OK);
E 14
E 13
}

int
__touchline(win, y, sx, ex, force)
	register WINDOW *win;
E 11
	register int y, sx, ex;
I 11
	int force;
E 11
E 9
{
D 9
# ifdef DEBUG
	fprintf(outf, "TOUCHLINE(%0.2o, %d, %d, %d)\n", win, y, sx, ex);
	fprintf(outf, "TOUCHLINE:first = %d, last = %d\n", win->_firstch[y], win->_lastch[y]);
# endif
E 9
I 9
#ifdef DEBUG
D 11
	__TRACE("touchline: (%0.2o, %d, %d, %d)\n", win, y, sx, ex);
E 11
I 11
D 16
	__TRACE("touchline: (%0.2o, %d, %d, %d, %d)\n", win, y, sx, ex, force);
E 11
	__TRACE("touchline: first = %d, last = %d\n",
E 16
I 16
	__CTRACE("touchline: (%0.2o, %d, %d, %d, %d)\n", win, y, sx, ex, force);
	__CTRACE("touchline: first = %d, last = %d\n",
E 16
D 10
	    win->_firstch[y], win->_lastch[y]);
E 10
I 10
D 12
	    win->lines[y]->firstch, win->lines[y]->lastch);
E 12
I 12
	    *win->lines[y]->firstchp, *win->lines[y]->lastchp);
E 12
E 10
#endif
I 11
	if (force)
		win->lines[y]->flags |= __FORCEPAINT;
E 11
E 9
D 10
	sx += win->_ch_off;
	ex += win->_ch_off;
	if (win->_firstch[y] == _NOCHANGE) {
		win->_firstch[y] = sx;
		win->_lastch[y] = ex;
E 10
I 10
	sx += win->ch_off;
	ex += win->ch_off;
	if (!(win->lines[y]->flags & __ISDIRTY)) {
		win->lines[y]->flags |= __ISDIRTY;
D 12
		win->lines[y]->firstch = sx;
		win->lines[y]->lastch = ex;
E 12
I 12
		*win->lines[y]->firstchp = sx;
		*win->lines[y]->lastchp = ex;
E 12
E 10
E 3
D 9
	}
I 3
	else {
E 9
I 9
	} else {
E 9
D 10
		if (win->_firstch[y] > sx)
			win->_firstch[y] = sx;
		if (win->_lastch[y] < ex)
			win->_lastch[y] = ex;
E 10
I 10
D 12
		if (win->lines[y]->firstch > sx)
			win->lines[y]->firstch = sx;
		if (win->lines[y]->lastch < ex)
			win->lines[y]->lastch = ex;
E 12
I 12
		if (*win->lines[y]->firstchp > sx)
			*win->lines[y]->firstchp = sx;
		if (*win->lines[y]->lastchp < ex)
			*win->lines[y]->lastchp = ex;
E 12
E 10
	}
D 9
# ifdef	DEBUG
	fprintf(outf, "TOUCHLINE:first = %d, last = %d\n", win->_firstch[y], win->_lastch[y]);
# endif
E 9
I 9
#ifdef DEBUG
D 16
	__TRACE("touchline: first = %d, last = %d\n",
E 16
I 16
	__CTRACE("touchline: first = %d, last = %d\n",
E 16
D 10
	    win->_firstch[y], win->_lastch[y]);
E 10
I 10
D 12
	    win->lines[y]->firstch, win->lines[y]->lastch);
E 12
I 12
	    *win->lines[y]->firstchp, *win->lines[y]->lastchp);
E 12
E 10
#endif
D 13
	return (OK);
E 13
I 13
D 14
	return (CURSES_OK);
E 14
I 14
	return (OK);
E 14
E 13
E 9
E 3
}
I 15


E 15
E 1
