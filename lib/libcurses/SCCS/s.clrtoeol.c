h35087
s 00002/00002/00055
d D 8.2 94/05/04 06:24:33 bostic 19 18
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00055
d D 8.1 93/06/04 16:47:18 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00056
d D 5.12 93/05/16 15:54:34 bostic 17 16
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00008/00001/00049
d D 5.11 93/05/06 16:00:30 elan 16 15
c Must take into account ISPASTEOL when clearing.
e
s 00002/00002/00048
d D 5.10 92/11/11 17:35:16 elan 15 14
c Added pointers to firstch and lastch for correct operation of 
c subwindows.
e
s 00001/00001/00049
d D 5.9 92/10/27 14:38:04 elan 14 13
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00009/00004/00041
d D 5.8 92/10/26 12:46:47 elan 13 12
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00002/00001/00043
d D 5.7 92/10/20 10:44:38 elan 12 11
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00010/00009/00034
d D 5.6 92/09/14 11:00:21 elan 11 10
c Converted to new data structures.
e
s 00015/00017/00028
d D 5.5 92/08/23 10:11:45 bostic 10 8
c KNF, return a value
e
s 00015/00015/00030
d R 5.5 92/05/15 14:18:06 bostic 9 8
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00044
d D 5.4 90/06/01 15:37:38 bostic 8 7
c new copyright notice
e
s 00010/00005/00045
d D 5.3 88/06/30 17:21:18 bostic 7 6
c install approved copyright notice
e
s 00010/00004/00040
d D 5.2 88/06/08 13:56:48 bostic 6 5
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00034
d D 5.1 85/06/07 11:26:38 dist 5 4
c Add copyright
e
s 00002/00007/00033
d D 1.3 85/05/01 16:43:59 bloom 4 2
c new version from arnold
e
s 00002/00007/00033
d R 1.3 85/05/01 16:42:36 bloom 3 2
c 
e
s 00000/00002/00040
d D 1.2 81/03/05 19:12:42 arnold 2 1
c eliminate unecessary return
e
s 00042/00000/00000
d D 1.1 81/01/26 17:02:40 arnold 1 0
c date and time created 81/01/26 17:02:40 by arnold
e
u
U
t
T
I 5
/*
D 6
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 18
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 18
I 18
D 19
 * Copyright (c) 1981, 1993
E 19
I 19
 * Copyright (c) 1981, 1993, 1994
E 19
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
D 10
#endif /* not lint */
E 10
I 10
#endif	/* not lint */
E 10
E 6

E 5
I 1
D 10
# include	"curses.ext"
E 10
I 10
D 19
#include <curses.h>
E 19
I 19
#include "curses.h"
E 19
E 10

/*
D 10
 *	This routine clears up to the end of line
 *
E 10
I 10
 * wclrtoeol --
 *	Clear up to the end of line.
E 10
D 4
 * %G% (Berkeley) %W%
E 4
I 4
D 5
 * %W% (Berkeley) %G%
E 5
E 4
 */
I 10
int
E 10
wclrtoeol(win)
D 10
reg WINDOW	*win; {
E 10
I 10
	register WINDOW *win;
{
	register int minx, x, y;
D 13
	register char *end, *maxx, *sp;
E 13
I 13
	register __LDATA *end, *maxx, *sp;
E 13
E 10

D 10
	reg char	*sp, *end;
	reg int		y, x;
	reg char	*maxx;
	reg int		minx;

E 10
D 11
	y = win->_cury;
	x = win->_curx;
	end = &win->_y[y][win->_maxx];
	minx = _NOCHANGE;
	maxx = &win->_y[y][x];
E 11
I 11
	y = win->cury;
	x = win->curx;
I 16
	if (win->lines[y]->flags & __ISPASTEOL) {
		if (y < win->maxy - 1) {
			y++;
			x = 0;
		} else
			return (OK);
	}
E 16
	end = &win->lines[y]->line[win->maxx];
	minx = -1;
	maxx = &win->lines[y]->line[x];
E 11
	for (sp = maxx; sp < end; sp++)
D 12
		if (*sp != ' ') {
E 12
I 12
D 13
		if (*sp != ' ' || *(sp + win->maxx) & __STANDOUT) {
E 13
I 13
		if (sp->ch != ' ' || sp->attr != 0) {
E 13
E 12
			maxx = sp;
D 11
			if (minx == _NOCHANGE)
				minx = sp - win->_y[y];
E 11
I 11
			if (minx == -1)
				minx = sp - win->lines[y]->line;
E 11
D 13
			*sp = ' ';
I 12
			*(sp + win->maxx) &= ~__STANDOUT;
E 13
I 13
			sp->ch = ' ';
			sp->attr = 0;
E 13
E 12
		}
D 10
	/*
	 * update firstch and lastch for the line
	 */
I 4
	touchline(win, y, win->_curx, win->_maxx - 1);
E 4
# ifdef DEBUG
	fprintf(outf, "CLRTOEOL: minx = %d, maxx = %d, firstch = %d, lastch = %d\n", minx, maxx - win->_y[y], win->_firstch[y], win->_lastch[y]);
# endif
E 10
I 10
#ifdef DEBUG
D 17
	__TRACE("CLRTOEOL: minx = %d, maxx = %d, firstch = %d, lastch = %d\n",
E 17
I 17
	__CTRACE("CLRTOEOL: minx = %d, maxx = %d, firstch = %d, lastch = %d\n",
E 17
D 11
	    minx, maxx - win->_y[y], win->_firstch[y], win->_lastch[y]);
E 11
I 11
D 15
	    minx, maxx - win->lines[y]->line, win->lines[y]->firstch, 
	    win->lines[y]->lastch);
E 15
I 15
	    minx, maxx - win->lines[y]->line, *win->lines[y]->firstchp, 
	    *win->lines[y]->lastchp);
E 15
E 11
#endif
	/* Update firstch and lastch for the line. */
D 11
	return (touchline(win, y, win->_curx, win->_maxx - 1));
E 11
I 11
D 14
	return (touchline(win, y, win->curx, win->maxx - 1));
E 14
I 14
D 16
	return (__touchline(win, y, win->curx, win->maxx - 1, 0));
E 16
I 16
	return (__touchline(win, y, x, win->maxx - 1, 0));
E 16
E 14
E 11
E 10
D 4
	if (minx != _NOCHANGE) {
		if (win->_firstch[y] > minx || win->_firstch[y] == _NOCHANGE)
			win->_firstch[y] = minx;
		if (win->_lastch[y] < maxx - win->_y[y])
			win->_lastch[y] = maxx - win->_y[y];
	}
E 4
D 2

	return OK;
E 2
}
I 13





E 13
E 1
