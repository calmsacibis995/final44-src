h02845
s 00002/00002/00049
d D 8.2 94/05/04 06:24:48 bostic 14 13
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00049
d D 8.1 93/06/04 16:48:38 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00047
d D 5.9 93/01/11 11:53:54 bostic 12 11
c CURSES_{OK,ERR} -> OK,ERR
e
s 00004/00004/00047
d D 5.8 92/12/30 14:54:53 elan 11 10
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00001/00001/00050
d D 5.7 92/10/27 14:37:57 elan 10 9
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00011/00011/00040
d D 5.6 92/09/14 11:00:36 elan 9 8
c Converted to new data structures.
e
s 00018/00019/00033
d D 5.5 92/08/23 11:23:41 bostic 8 6
c KNF
e
s 00016/00015/00037
d R 5.5 92/05/15 15:18:38 bostic 7 6
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00051
d D 5.4 90/06/01 15:39:27 bostic 6 5
c new copyright notice
e
s 00010/00005/00052
d D 5.3 88/06/30 17:21:51 bostic 5 4
c install approved copyright notice
e
s 00010/00004/00047
d D 5.2 88/06/08 13:57:30 bostic 4 3
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00041
d D 5.1 85/06/07 11:37:11 dist 3 2
c Add copyright
e
s 00026/00003/00016
d D 1.2 85/05/01 17:27:04 bloom 2 1
c new version from arnold
e
s 00019/00000/00000
d D 1.1 81/01/26 17:03:03 arnold 1 0
c date and time created 81/01/26 17:03:03 by arnold
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 13
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 13
I 13
D 14
 * Copyright (c) 1981, 1993
E 14
I 14
 * Copyright (c) 1981, 1993, 1994
E 14
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 8
#endif /* not lint */
E 8
I 8
#endif	/* not lint */
E 8
E 4

E 3
I 1
D 8
# include	"curses.ext"
E 8
I 8
D 14
#include <curses.h>
E 14
I 14
#include "curses.h"
E 14
E 8

/*
D 8
 * relocate the starting position of a window
 *
E 8
I 8
 * mvwin --
 *	Relocate the starting position of a window.
E 8
D 2
 * %G% (Berkeley) %W%
E 2
I 2
D 3
 * %W% (Berkeley) %G%
E 3
E 2
 */
D 8

E 8
I 8
int
E 8
mvwin(win, by, bx)
D 8
reg WINDOW	*win;
reg int		by, bx; {
E 8
I 8
	register WINDOW *win;
	register int by, bx;
{
	register WINDOW *orig;
	register int dy, dx;
E 8

I 2
D 8
	register WINDOW	*orig;
	register int	dy, dx;

E 8
E 2
D 9
	if (by + win->_maxy > LINES || bx + win->_maxx > COLS)
E 9
I 9
	if (by + win->maxy > LINES || bx + win->maxx > COLS)
E 9
D 8
		return ERR;
E 8
I 8
D 11
		return (ERR);
E 11
I 11
D 12
		return (CURSES_ERR);
E 12
I 12
		return (ERR);
E 12
E 11
E 8
D 2
	win->_begy = by;
	win->_begx = bx;
E 2
I 2
D 9
	dy = by - win->_begy;
	dx = bx - win->_begx;
	orig = win->_orig;
E 9
I 9
	dy = by - win->begy;
	dx = bx - win->begx;
	orig = win->orig;
E 9
	if (orig == NULL) {
		orig = win;
		do {
D 9
			win->_begy += dy;
			win->_begx += dx;
E 9
I 9
			win->begy += dy;
			win->begx += dx;
E 9
D 8
			_swflags_(win);
E 8
I 8
			__swflags(win);
E 8
D 9
			win = win->_nextp;
E 9
I 9
			win = win->nextp;
E 9
		} while (win != orig);
D 8
	}
	else {
E 8
I 8
	} else {
E 8
D 9
		if (by < orig->_begy || win->_maxy + dy > orig->_maxy)
E 9
I 9
		if (by < orig->begy || win->maxy + dy > orig->maxy)
E 9
D 8
			return ERR;
E 8
I 8
D 11
			return (ERR);
E 11
I 11
D 12
			return (CURSES_ERR);
E 12
I 12
			return (ERR);
E 12
E 11
E 8
D 9
		if (bx < orig->_begx || win->_maxx + dx > orig->_maxx)
E 9
I 9
		if (bx < orig->begx || win->maxx + dx > orig->maxx)
E 9
D 8
			return ERR;
E 8
I 8
D 11
			return (ERR);
E 11
I 11
D 12
			return (CURSES_ERR);
E 12
I 12
			return (ERR);
E 12
E 11
E 8
D 9
		win->_begy = by;
		win->_begx = bx;
E 9
I 9
		win->begy = by;
		win->begx = bx;
E 9
D 8
		_swflags_(win);
		_set_subwin_(orig, win);
E 8
I 8
		__swflags(win);
		__set_subwin(orig, win);
E 8
	}
E 2
D 10
	touchwin(win);
E 10
I 10
	__touchwin(win);
E 10
D 8
	return OK;
E 8
I 8
D 11
	return (OK);
E 11
I 11
D 12
	return (CURSES_OK);
E 12
I 12
	return (OK);
E 12
E 11
E 8
}
E 1
