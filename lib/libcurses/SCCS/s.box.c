h16277
s 00002/00002/00050
d D 8.2 94/05/04 06:24:30 bostic 17 16
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00050
d D 8.1 93/06/04 16:47:07 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00051
d D 5.11 93/01/11 11:53:40 bostic 15 14
c CURSES_{OK,ERR} -> OK,ERR
e
s 00001/00001/00051
d D 5.10 92/12/30 14:54:50 elan 14 13
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00001/00001/00051
d D 5.9 92/10/27 14:37:56 elan 13 12
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00013/00014/00039
d D 5.8 92/10/26 12:46:36 elan 12 11
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00018/00005/00035
d D 5.7 92/10/20 10:44:31 elan 11 10
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00006/00006/00034
d D 5.6 92/09/14 11:00:19 elan 10 9
c Converted to new data structures.
e
s 00013/00012/00027
d D 5.5 92/08/23 10:02:13 bostic 9 7
c KNF
e
s 00011/00010/00029
d R 5.5 92/05/15 14:17:12 bostic 8 7
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00038
d D 5.4 90/06/01 15:37:23 bostic 7 6
c new copyright notice
e
s 00010/00005/00039
d D 5.3 88/06/30 17:21:13 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00034
d D 5.2 88/06/08 13:56:45 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00028
d D 5.1 85/06/07 11:25:29 dist 4 3
c Add copyright
e
s 00001/00001/00028
d D 1.3 85/05/01 16:34:42 bloom 3 2
c fix sccs ids
e
s 00001/00001/00028
d D 1.2 82/02/16 16:01:41 arnold 2 1
c should include curses.ext, not curses.h
e
s 00029/00000/00000
d D 1.1 81/01/26 17:02:36 arnold 1 0
c date and time created 81/01/26 17:02:36 by arnold
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
D 16
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 16
I 16
D 17
 * Copyright (c) 1981, 1993
E 17
I 17
 * Copyright (c) 1981, 1993, 1994
E 17
 *	The Regents of the University of California.  All rights reserved.
E 16
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

E 4
I 1
D 2
# include	"curses.h"
E 2
I 2
D 9
# include	"curses.ext"
E 9
I 9
D 17
#include <curses.h>
E 17
I 17
#include "curses.h"
E 17
E 9
E 2

/*
D 9
 *	This routine draws a box around the given window with "vert"
 * as the vertical delimiting char, and "hor", as the horizontal one.
 *
E 9
I 9
 * box --
 *	Draw a box around the given window with "vert" as the vertical
 *	delimiting char, and "hor", as the horizontal one.
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
box(win, vert, hor)
D 9
reg WINDOW	*win;
char		vert, hor; {
E 9
I 9
	register WINDOW *win;
	int vert, hor;
{
	register int endy, endx, i;
D 11
	register char *fp, *lp;
E 11
I 11
D 12
	register char *fp, *lp, *sfp, *slp;
E 12
I 12
	register __LDATA *fp, *lp;
E 12
E 11
E 9

D 9
	reg int		i;
	reg int		endy, endx;
	reg char	*fp, *lp;

E 9
D 10
	endx = win->_maxx;
	endy = win->_maxy - 1;
	fp = win->_y[0];
	lp = win->_y[endy];
E 10
I 10
	endx = win->maxx;
	endy = win->maxy - 1;
D 11
	fp = win->topline->line;
E 11
I 11
	fp = win->lines[0]->line;
E 11
	lp = win->lines[endy]->line;
E 10
D 11
	for (i = 0; i < endx; i++)
E 11
I 11
D 12
	sfp = win->lines[0]->standout;
	slp = win->lines[endy]->standout;
E 12
	for (i = 0; i < endx; i++) {
E 11
D 12
		fp[i] = lp[i] = hor;
I 11
		sfp[i] &= ~__STANDOUT;
		slp[i] &= ~__STANDOUT;
E 12
I 12
		fp[i].ch = lp[i].ch = hor;
		fp[i].attr &= ~__STANDOUT;
		lp[i].attr &= ~__STANDOUT;
E 12
	}
E 11
	endx--;
D 11
	for (i = 0; i <= endy; i++)
E 11
I 11
	for (i = 0; i <= endy; i++) {
E 11
D 10
		win->_y[i][0] = (win->_y[i][endx] = vert);
D 9
	if (!win->_scroll && (win->_flags&_SCROLLWIN))
E 9
I 9
	if (!win->_scroll && (win->_flags & _SCROLLWIN))
E 10
I 10
D 12
		win->lines[i]->line[0] = (win->lines[i]->line[endx] = vert);
D 11
	if (!(win->flags & __SCROLLOK) && (win->flags & __SCROLLWIN))
E 11
I 11
		win->lines[i]->standout[0] &= ~__STANDOUT;
		win->lines[i]->standout[endx] &= ~__STANDOUT;
E 12
I 12
		win->lines[i]->line[0].ch = vert;
	        win->lines[i]->line[endx].ch = vert;
		win->lines[i]->line[0].attr &= ~__STANDOUT;
		win->lines[i]->line[endx].attr &= ~__STANDOUT;
E 12
	}
	if (!(win->flags & __SCROLLOK) && (win->flags & __SCROLLWIN)) {
E 11
E 10
E 9
D 12
		fp[0] = fp[endx] = lp[0] = lp[endx] = ' ';
I 11
		sfp[0] &= ~__STANDOUT;
		sfp[endx] &= ~__STANDOUT;
		slp[0] &= ~__STANDOUT;
		slp[endx] &= ~__STANDOUT;
E 12
I 12
		fp[0].ch = fp[endx].ch = lp[0].ch = lp[endx].ch = ' ';
		fp[0].attr &= ~__STANDOUT;
		fp[endx].attr &= ~__STANDOUT;
		lp[0].attr &= ~__STANDOUT;
		lp[endx].attr &= ~__STANDOUT;
E 12
	}
E 11
D 13
	touchwin(win);
E 13
I 13
	__touchwin(win);
E 13
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
}
E 1
