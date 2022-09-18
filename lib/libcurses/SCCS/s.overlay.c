h34123
s 00003/00002/00053
d D 8.2 94/05/04 06:24:50 bostic 22 21
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00053
d D 8.1 93/06/04 16:48:45 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00053
d D 5.13 93/05/16 15:54:44 bostic 20 19
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00002/00002/00053
d D 5.12 93/01/11 11:53:55 bostic 19 18
c CURSES_{OK,ERR} -> OK,ERR
e
s 00002/00002/00053
d D 5.11 92/12/30 14:55:00 elan 18 17
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00003/00004/00052
d D 5.10 92/10/26 12:46:41 elan 17 16
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00005/00002/00051
d D 5.9 92/10/20 10:44:33 elan 16 15
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00010/00009/00043
d D 5.8 92/09/14 11:00:38 elan 15 14
c Converted to new data structures.
e
s 00019/00019/00033
d D 5.7 92/08/23 11:36:29 bostic 14 12
c KNF
e
s 00018/00019/00033
d R 5.7 92/05/15 15:26:24 bostic 13 12
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00051
d D 5.6 90/06/01 15:39:36 bostic 12 11
c new copyright notice
e
s 00010/00005/00052
d D 5.5 88/06/30 17:21:54 bostic 11 10
c install approved copyright notice
e
s 00010/00004/00047
d D 5.4 88/06/08 13:57:33 bostic 10 9
c written by Ken Arnold; add Berkeley specific header
e
s 00000/00006/00051
d D 5.3 87/09/14 15:44:10 bostic 9 8
c overlay, not overwrite; bug report 4.3BSD/usr.lib/51, tahoe/usr.lib/2
e
s 00008/00007/00049
d D 5.2 86/02/12 19:24:25 bloom 8 7
c it was really broken (from muller@nprdc.arpa)
e
s 00010/00001/00046
d D 5.1 85/06/07 11:38:39 dist 7 6
c Add copyright
e
s 00024/00011/00023
d D 1.6 85/05/01 17:27:16 bloom 6 5
c new version from arnold
e
s 00001/00001/00033
d D 1.5 84/07/10 00:07:13 mckusick 5 4
c last line botched (fix from Mike Laman, NCR Torrey Pines)
e
s 00001/00001/00033
d D 1.4 82/11/05 17:12:02 arnold 4 3
c fix bug with max() macro
e
s 00005/00010/00029
d D 1.3 82/02/16 17:09:42 arnold 3 2
c check boundary conditions properly
e
s 00001/00001/00038
d D 1.2 82/02/16 17:06:09 arnold 2 1
c include curses.ext, not curses.h
e
s 00039/00000/00000
d D 1.1 81/01/26 17:03:06 arnold 1 0
c date and time created 81/01/26 17:03:06 by arnold
e
u
U
t
T
I 7
/*
D 10
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
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
D 12
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 11
E 10
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 10
#endif not lint
E 10
I 10
D 14
#endif /* not lint */
E 14
I 14
#endif	/* not lint */
E 14
E 10

E 7
I 1
D 2
# include	"curses.h"
E 2
I 2
D 14
# include	"curses.ext"
E 2
# include	<ctype.h>
E 14
I 14
#include <ctype.h>
D 22
#include <curses.h>
E 22
I 22

#include "curses.h"
E 22
E 14

D 14
# define	min(a,b)	(a < b ? a : b)
D 4
# define	max(a,b)	(a < b ? a : b)
E 4
I 4
# define	max(a,b)	(a > b ? a : b)
E 4

E 14
/*
D 14
 *	This routine writes win1 on win2 non-destructively.
 *
E 14
I 14
 * overlay --
 *	Writes win1 on win2 non-destructively.
E 14
D 6
 * %G% (Berkeley) %W%
E 6
I 6
D 7
 * %W% (Berkeley) %G%
E 7
E 6
 */
I 14
int
E 14
overlay(win1, win2)
D 14
reg WINDOW	*win1, *win2; {
E 14
I 14
	register WINDOW *win1, *win2;
{
E 14

D 14
	reg char	*sp, *end;
D 3
	reg int		x, y, endy, endx, starty, startx, y_top,
			y_bot, x_left, x_right;
E 3
I 3
	reg int		x, y, endy, endx, starty, startx;
I 8
	reg int 	y1,y2;
E 14
I 14
	register int x, y, y1, y2, endy, endx, starty, startx;
D 17
	register char *sp, *end;
E 17
I 17
	register __LDATA *sp, *end;
E 17
E 14
E 8
E 3

D 14
# ifdef DEBUG
	fprintf(outf, "OVERLAY(%0.2o, %0.2o);\n", win1, win2);
# endif
E 14
I 14
#ifdef DEBUG
D 20
	__TRACE("overlay: (%0.2o, %0.2o);\n", win1, win2);
E 20
I 20
	__CTRACE("overlay: (%0.2o, %0.2o);\n", win1, win2);
E 20
#endif
E 14
D 3
	y_top = max(win1->_begy, win2->_begy);
	y_bot = min(win1->_maxy, win2->_maxy);
	x_left = max(win1->_begx, win2->_begx);
	x_right = min(win1->_maxx, win2->_maxx);
	starty = y_top - win1->_begy;
	startx = x_left - win1->_begx;
	endy = y_bot - win1->_begy;
	endx = x_right - win1->_begx;
E 3
I 3
D 6
	starty = max(win1->_begy, win2->_begy) - win1->_begy;
	startx = max(win1->_begx, win2->_begx) - win1->_begx;
	endy = min(win1->_maxy, win2->_maxy) - win1->_begy - 1;
	endx = min(win1->_maxx, win2->_maxx) - win1->_begx - 1;
E 3
D 5
	for (y = starty; y < endy; y++) {
E 5
I 5
	for (y = starty; y <= endy; y++) {
E 5
		end = &win1->_y[y][endx];
		x = startx + win1->_begx;
		for (sp = &win1->_y[y][startx]; sp <= end; sp++) {
			if (!isspace(*sp))
				mvwaddch(win2, y + win1->_begy, x, *sp);
E 6
I 6
D 15
	starty = max(win1->_begy, win2->_begy);
	startx = max(win1->_begx, win2->_begx);
	endy = min(win1->_maxy + win1->_begy, win2->_maxy + win2->_begx);
	endx = min(win1->_maxx + win1->_begx, win2->_maxx + win2->_begx);
E 15
I 15
	starty = max(win1->begy, win2->begy);
	startx = max(win1->begx, win2->begx);
	endy = min(win1->maxy + win1->begy, win2->maxy + win2->begx);
	endx = min(win1->maxx + win1->begx, win2->maxx + win2->begx);
E 15
D 14
# ifdef DEBUG
	fprintf(outf, "OVERLAY:from (%d,%d) to (%d,%d)\n", starty, startx, endy, endx);
# endif
E 14
I 14
#ifdef DEBUG
D 20
	__TRACE("overlay: from (%d,%d) to (%d,%d)\n",
E 20
I 20
	__CTRACE("overlay: from (%d,%d) to (%d,%d)\n",
E 20
	    starty, startx, endy, endx);
#endif
E 14
	if (starty >= endy || startx >= endx)
D 14
		return;
E 14
I 14
D 18
		return (OK);
E 18
I 18
D 19
		return (CURSES_OK);
E 19
I 19
		return (OK);
E 19
E 18
E 14
D 9
	x = endx - startx;
	for (y = starty; y < endy; y++) {
		bcopy(&win1->_y[y - win1->_begy][startx - win1->_begx],
		      &win2->_y[y - win2->_begy][startx - win2->_begx], x);
		touchline(win2, y, startx - win2->_begx, endx - win2->_begx);
	}
E 9
D 8
	for (y = starty; y < endy; y++) {
		end = &win1->_y[y - win1->_begy][endx - win1->_begx];
E 8
I 8
D 15
	y1 = starty - win1->_begy;
	y2 = starty - win2->_begy;
E 15
I 15
	y1 = starty - win1->begy;
	y2 = starty - win2->begy;
E 15
	for (y = starty; y < endy; y++, y1++, y2++) {
D 15
		end = &win1->_y[y1][endx - win1->_begx];
E 8
		x = startx - win2->_begx;
D 8
		for (sp = &win1->_y[y][startx - win1->_begx]; sp < end; sp++) {
			if (!isspace(*sp)) {
				waddch(win2, y - win2->_begy, x);
				waddch(win2, *sp);
			}
E 8
I 8
		for (sp = &win1->_y[y1][startx - win1->_begx]; sp < end; sp++) {
E 15
I 15
		end = &win1->lines[y1]->line[endx - win1->begx];
		x = startx - win2->begx;
		for (sp = &win1->lines[y1]->line[startx - win1->begx]; 
		     sp < end; sp++) {
E 15
D 16
			if (!isspace(*sp))
				mvwaddch(win2, y2, x, *sp);
E 16
I 16
D 17
			if (!isspace(*sp)) {
E 17
I 17
			if (!isspace(sp->ch)) {
E 17
				wmove(win2, y2, x);
D 17
				__waddch(win2, y2, x, *sp, 
					 *(sp + win1->maxx) & __STANDOUT);
E 17
I 17
				__waddch(win2, sp);
E 17
			}
E 16
E 8
E 6
			x++;
		}
	}
I 14
D 18
	return (OK);
E 18
I 18
D 19
	return (CURSES_OK);
E 19
I 19
	return (OK);
E 19
E 18
E 14
}
E 1
