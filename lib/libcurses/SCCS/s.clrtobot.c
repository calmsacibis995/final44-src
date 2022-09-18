h63855
s 00002/00002/00047
d D 8.2 94/05/04 06:24:32 bostic 18 17
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00047
d D 8.1 93/06/04 16:47:13 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00003/00040
d D 5.13 93/05/06 16:00:28 elan 16 15
c Must take into account ISPASTEOL when clearing.
e
s 00001/00001/00042
d D 5.12 93/01/11 11:53:41 bostic 15 14
c CURSES_{OK,ERR} -> OK,ERR
e
s 00001/00001/00042
d D 5.11 92/12/30 14:55:05 elan 14 13
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00002/00001/00041
d D 5.10 92/10/27 14:38:03 elan 13 12
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00005/00006/00037
d D 5.9 92/10/26 12:46:46 elan 12 11
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00002/00001/00041
d D 5.8 92/10/20 10:44:37 elan 11 10
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00010/00009/00032
d D 5.7 92/09/14 11:00:20 elan 10 9
c Converted to new data structures.
e
s 00010/00009/00031
d D 5.6 92/08/23 10:08:45 bostic 9 7
c KNF
e
s 00009/00008/00032
d R 5.6 92/05/15 14:17:52 bostic 8 7
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00039
d D 5.5 90/06/01 15:37:33 bostic 7 6
c new copyright notice
e
s 00010/00005/00040
d D 5.4 88/06/30 17:21:16 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00035
d D 5.3 88/06/08 13:56:47 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00001/00001/00038
d D 5.2 85/10/24 12:22:10 bloom 4 3
c should clear to end of first line
e
s 00010/00001/00029
d D 5.1 85/06/07 11:26:14 dist 3 2
c Add copyright
e
s 00003/00009/00027
d D 1.2 85/05/01 16:44:04 bloom 2 1
c new version from arnold
e
s 00036/00000/00000
d D 1.1 81/01/26 17:02:39 arnold 1 0
c date and time created 81/01/26 17:02:39 by arnold
e
u
U
t
T
I 3
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
D 9
#endif /* not lint */
E 9
I 9
#endif	/* not lint */
E 9
E 5

E 3
I 1
D 9
# include	"curses.ext"
E 9
I 9
D 18
#include <curses.h>
E 18
I 18
#include "curses.h"
E 18
E 9

/*
D 9
 *	This routine erases everything on the window.
 *
E 9
I 9
 * wclrtobot --
 *	Erase everything on the window.
E 9
D 2
 * %G% (Berkeley) %W%
E 2
I 2
D 3
 * %W% (Berkeley) %G%
E 3
E 2
 */
I 9
int
E 9
wclrtobot(win)
D 9
reg WINDOW	*win; {
E 9
I 9
	register WINDOW *win;
{
D 16
	register int minx, startx, y;
E 16
I 16
	register int minx, startx, starty, y;
E 16
D 12
	register char *sp, *end, *maxx;
E 12
I 12
	register __LDATA *sp, *end, *maxx;
E 12
E 9

D 9
	reg int		y;
	reg char	*sp, *end, *maxx;
	reg int		startx, minx;

E 9
D 10
	startx = win->_curx;
	for (y = win->_cury; y < win->_maxy; y++) {
		minx = _NOCHANGE;
		end = &win->_y[y][win->_maxx];
		for (sp = &win->_y[y][startx]; sp < end; sp++)
E 10
I 10
D 16
	startx = win->curx;
	for (y = win->cury; y < win->maxy; y++) {
E 16
I 16
	if (win->lines[win->cury]->flags & __ISPASTEOL) {
		starty = win->cury + 1;
		startx = 0;
	} else {
		starty = win->cury;
		startx = win->curx;
	}
	for (y = starty; y < win->maxy; y++) {
E 16
		minx = -1;
		end = &win->lines[y]->line[win->maxx];
		for (sp = &win->lines[y]->line[startx]; sp < end; sp++)
E 10
D 11
			if (*sp != ' ') {
E 11
I 11
D 12
			if (*sp != ' ' || *(sp + win->maxx) & __STANDOUT) {
E 12
I 12
			if (sp->ch != ' ' || sp->attr != 0) {
E 12
E 11
				maxx = sp;
D 10
				if (minx == _NOCHANGE)
					minx = sp - win->_y[y];
E 10
I 10
				if (minx == -1)
					minx = sp - win->lines[y]->line;
E 10
D 12
				*sp = ' ';
I 11
				*(sp + win->maxx) &= ~__STANDOUT;
E 12
I 12
				sp->ch = ' ';
				sp->attr = 0;
E 12
E 11
			}
D 2
		if (minx != _NOCHANGE) {
			if (win->_firstch[y] > minx
			     || win->_firstch[y] == _NOCHANGE)
				win->_firstch[y] = minx;
			if (win->_lastch[y] < maxx - win->_y[y])
				win->_lastch[y] = maxx - win->_y[y];
		}
E 2
I 2
D 10
		if (minx != _NOCHANGE)
D 4
			touchline(win, y, minx, maxx - &win->_y[y][startx]);
E 4
I 4
			touchline(win, y, minx, maxx - &win->_y[y][0]);
E 10
I 10
		if (minx != -1)
D 12
			touchline(win, y, minx, 
			    maxx - win->lines[y]->line);
E 12
I 12
D 13
			touchline(win, y, minx, maxx - win->lines[y]->line);
E 13
I 13
			__touchline(win, y, minx, maxx - win->lines[y]->line,
		            0);
E 13
E 12
E 10
E 4
E 2
		startx = 0;
	}
I 9
D 14
	return (OK);
E 14
I 14
D 15
	return (CURSES_OK);
E 15
I 15
	return (OK);
E 15
E 14
E 9
D 2
	win->_curx = win->_cury = 0;
E 2
}
E 1
