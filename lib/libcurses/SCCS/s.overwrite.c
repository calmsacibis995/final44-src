h45619
s 00003/00002/00047
d D 8.2 94/05/04 06:24:51 bostic 22 21
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00047
d D 8.1 93/06/04 16:48:51 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00047
d D 5.14 93/05/16 15:54:45 bostic 20 19
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00002/00001/00047
d D 5.13 93/02/18 16:18:40 elan 19 18
c bcopy -> memcpy.  Probably more portable.
e
s 00002/00002/00046
d D 5.12 93/01/11 11:53:55 bostic 18 17
c CURSES_{OK,ERR} -> OK,ERR
e
s 00002/00002/00046
d D 5.11 92/12/30 14:55:02 elan 17 16
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00002/00001/00046
d D 5.10 92/10/27 14:38:00 elan 16 15
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00001/00004/00046
d D 5.9 92/10/26 12:46:42 elan 15 14
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00003/00000/00047
d D 5.8 92/10/20 10:44:34 elan 14 13
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00008/00007/00039
d D 5.7 92/09/14 11:00:39 elan 13 12
c Converted to new data structures.
e
s 00001/00001/00045
d D 5.6 92/08/23 14:38:37 bostic 12 11
c lint
e
s 00020/00020/00026
d D 5.5 92/08/23 11:38:29 bostic 11 9
c KNF
e
s 00017/00017/00029
d R 5.5 92/05/15 15:25:03 bostic 10 9
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00045
d D 5.4 90/06/01 15:39:43 bostic 9 8
c new copyright notice
e
s 00010/00005/00046
d D 5.3 88/06/30 17:21:56 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00041
d D 5.2 88/06/08 13:57:35 bostic 7 6
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00035
d D 5.1 85/06/07 11:39:19 dist 6 5
c Add copyright
e
s 00019/00014/00017
d D 1.4 85/05/01 17:27:20 bloom 5 4
c new version from arnold
e
s 00005/00002/00026
d D 1.3 83/03/27 15:09:48 arnold 4 2
c 
e
s 00002/00002/00026
d R 1.3 82/02/16 17:09:25 arnold 3 2
c check boundary conditions properly
e
s 00001/00001/00027
d D 1.2 82/02/16 17:06:13 arnold 2 1
c include curses.ext, not curses.h
e
s 00028/00000/00000
d D 1.1 81/01/26 17:03:07 arnold 1 0
c date and time created 81/01/26 17:03:07 by arnold
e
u
U
t
T
I 6
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
D 21
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 21
I 21
D 22
 * Copyright (c) 1981, 1993
E 22
I 22
 * Copyright (c) 1981, 1993, 1994
E 22
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
D 11
#endif /* not lint */
E 11
I 11
#endif	/* not lint */
E 11
E 7

E 6
I 1
D 2
# include	"curses.h"
E 2
I 2
D 11
# include	"curses.ext"
I 5
# include	<ctype.h>
E 11
I 11
#include <ctype.h>
D 22
#include <curses.h>
E 22
I 12
#include <string.h>
I 22

#include "curses.h"
E 22
E 12
E 11
E 5
E 2

D 11
# define	min(a,b)	(a < b ? a : b)
I 5
# define	max(a,b)	(a > b ? a : b)
E 5

E 11
/*
D 11
 *	This routine writes win1 on win2 destructively.
 *
E 11
I 11
 * overwrite --
 *	Writes win1 on win2 destructively.
E 11
D 5
 * %G% (Berkeley) %W%
E 5
I 5
D 6
 * %W% (Berkeley) %G%
E 6
E 5
 */
I 11
int
E 11
overwrite(win1, win2)
D 11
reg WINDOW	*win1, *win2; {
E 11
I 11
	register WINDOW *win1, *win2;
{
	register int x, y, endy, endx, starty, startx;
D 12
	register char *sp, *end;
E 12
E 11

D 4
	reg int		x, y, minx, miny, starty;
E 4
I 4
D 5
	reg int		x, y, minx, miny, startx, starty;
E 5
I 5
D 11
	reg char	*sp, *end;
	reg int		x, y, endy, endx, starty, startx;
E 5
E 4

# ifdef DEBUG
D 5
	fprintf(outf, "OVERWRITE(0%o, 0%o);\n", win1, win2);
E 5
I 5
	fprintf(outf, "OVERWRITE(%0.2o, %0.2o);\n", win1, win2);
E 5
# endif
E 11
I 11
#ifdef DEBUG
D 20
	__TRACE("overwrite: (%0.2o, %0.2o);\n", win1, win2);
E 20
I 20
	__CTRACE("overwrite: (%0.2o, %0.2o);\n", win1, win2);
E 20
#endif
E 11
D 5
	miny = min(win1->_maxy, win2->_maxy);
	minx = min(win1->_maxx, win2->_maxx);
E 5
I 5
D 13
	starty = max(win1->_begy, win2->_begy);
	startx = max(win1->_begx, win2->_begx);
	endy = min(win1->_maxy + win1->_begy, win2->_maxy + win2->_begx);
	endx = min(win1->_maxx + win1->_begx, win2->_maxx + win2->_begx);
E 13
I 13
	starty = max(win1->begy, win2->begy);
	startx = max(win1->begx, win2->begx);
	endy = min(win1->maxy + win1->begy, win2->maxy + win2->begx);
	endx = min(win1->maxx + win1->begx, win2->maxx + win2->begx);
E 13
	if (starty >= endy || startx >= endx)
D 11
		return;
E 5
# ifdef DEBUG
D 5
	fprintf(outf, "OVERWRITE:\tminx = %d,  miny = %d\n", minx, miny);
E 5
I 5
	fprintf(outf, "OVERWRITE:from (%d,%d) to (%d,%d)\n", starty, startx, endy, endx);
E 5
# endif
E 11
I 11
D 17
		return (OK);
E 17
I 17
D 18
		return (CURSES_OK);
E 18
I 18
		return (OK);
E 18
E 17
#ifdef DEBUG
D 20
	__TRACE("overwrite: from (%d, %d) to (%d, %d)\n",
E 20
I 20
	__CTRACE("overwrite: from (%d, %d) to (%d, %d)\n",
E 20
	    starty, startx, endy, endx);
#endif
E 11
D 5
	starty = win1->_begy - win2->_begy;
I 4
	startx = win1->_begx - win2->_begx;
	if (startx < 0)
		startx = 0;
E 4
	for (y = 0; y < miny; y++)
D 4
		if (wmove(win2, y + starty, 0) != ERR)
E 4
I 4
		if (wmove(win2, y + starty, startx) != ERR)
E 4
			for (x = 0; x < minx; x++)
				waddch(win2, win1->_y[y][x]);
E 5
I 5
	x = endx - startx;
	for (y = starty; y < endy; y++) {
D 13
		bcopy(&win1->_y[y - win1->_begy][startx - win1->_begx],
D 11
		      &win2->_y[y - win2->_begy][startx - win2->_begx], x);
E 11
I 11
		    &win2->_y[y - win2->_begy][startx - win2->_begx], x);
E 11
		touchline(win2, y, startx - win2->_begx, endx - win2->_begx);
E 13
I 13
D 19
		bcopy(&win1->lines[y - win1->begy]->line[startx - win1->begx],
E 19
I 19
		(void)memcpy(
E 19
		    &win2->lines[y - win2->begy]->line[startx - win2->begx], 
I 19
		    &win1->lines[y - win1->begy]->line[startx - win1->begx],
E 19
D 15
		    x);
I 14
		bcopy(&win1->lines[y - win1->begy]->standout[startx - win1->begx],
		    &win2->lines[y - win2->begy]->standout[startx - win2->begx], 
		    x);
E 15
I 15
		    x * __LDATASIZE);
E 15
E 14
D 16
		touchline(win2, y, startx - win2->begx, endx - win2->begx);
E 16
I 16
		__touchline(win2, y, startx - win2->begx, endx - win2->begx,
		    0);
E 16
E 13
	}
I 11
D 17
	return (OK);
E 17
I 17
D 18
	return (CURSES_OK);
E 18
I 18
	return (OK);
E 18
E 17
E 11
E 5
}
E 1
