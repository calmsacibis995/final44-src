h19596
s 00002/00002/00049
d D 8.2 94/05/04 06:25:00 bostic 15 14
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00049
d D 8.1 93/06/04 16:49:21 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00047
d D 5.11 93/05/16 15:54:51 bostic 13 12
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00002/00002/00049
d D 5.10 93/01/11 11:54:02 bostic 12 11
c CURSES_{OK,ERR} -> OK,ERR
e
s 00002/00002/00049
d D 5.9 92/12/30 14:54:48 elan 11 10
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00002/00001/00049
d D 5.8 92/10/27 14:37:55 elan 10 9
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00012/00012/00038
d D 5.7 92/09/14 11:00:43 elan 9 8
c Converted to new data structures.
e
s 00001/00001/00049
d D 5.6 92/08/23 14:38:07 bostic 8 7
c lint
e
s 00022/00019/00028
d D 5.5 92/08/23 12:18:34 bostic 7 5
c KNF
e
s 00021/00017/00030
d R 5.5 92/05/15 15:18:09 bostic 6 5
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00046
d D 5.4 90/06/01 15:40:33 bostic 5 4
c new copyright notice
e
s 00010/00005/00047
d D 5.3 88/06/30 17:22:07 bostic 4 3
c install approved copyright notice
e
s 00010/00004/00042
d D 5.2 88/06/08 13:57:48 bostic 3 2
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00036
d D 5.1 85/06/07 11:42:57 dist 2 1
c Add copyright
e
s 00037/00000/00000
d D 1.1 85/05/01 17:35:30 bloom 1 0
c date and time created 85/05/01 17:35:30 by bloom
e
u
U
t
T
I 2
/*
D 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 14
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 14
I 14
D 15
 * Copyright (c) 1981, 1993
E 15
I 15
 * Copyright (c) 1981, 1993, 1994
E 15
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

E 2
I 1
D 7
# include	"curses.ext"
E 7
I 7
D 15
#include <curses.h>
E 15
I 15
#include "curses.h"
E 15
E 7

D 7
# define	min(a,b)	(a < b ? a : b)
# define	max(a,b)	(a > b ? a : b)

E 7
/*
I 7
 * touchoverlap --
E 7
 *	Touch, on win2, the part that overlaps with win1.
D 7
 *
E 7
D 2
 * %W% (Berkeley) %G%
E 2
 */
I 7
int
E 7
touchoverlap(win1, win2)
D 7
reg WINDOW	*win1, *win2; {
E 7
I 7
	register WINDOW *win1, *win2;
{
D 8
	register int x, y, endy, endx, starty, startx;
E 8
I 8
	register int y, endy, endx, starty, startx;
E 8
E 7

D 7
	reg int		x, y, endy, endx, starty, startx;

# ifdef DEBUG
	fprintf(outf, "TOUCHOVERLAP(%0.2o, %0.2o);\n", win1, win2);
# endif
E 7
I 7
#ifdef DEBUG
D 13
	__TRACE("touchoverlap: (%0.2o, %0.2o);\n", win1, win2);
E 13
I 13
	__CTRACE("touchoverlap: (%0.2o, %0.2o);\n", win1, win2);
E 13
#endif
E 7
D 9
	starty = max(win1->_begy, win2->_begy);
	startx = max(win1->_begx, win2->_begx);
	endy = min(win1->_maxy + win1->_begy, win2->_maxy + win2->_begx);
	endx = min(win1->_maxx + win1->_begx, win2->_maxx + win2->_begx);
E 9
I 9
	starty = max(win1->begy, win2->begy);
	startx = max(win1->begx, win2->begx);
	endy = min(win1->maxy + win1->begy, win2->maxy + win2->begx);
	endx = min(win1->maxx + win1->begx, win2->maxx + win2->begx);
E 9
D 7
# ifdef DEBUG
	fprintf(outf, "TOUCHOVERLAP:from (%d,%d) to (%d,%d)\n", starty, startx, endy, endx);
	fprintf(outf, "TOUCHOVERLAP:win1 (%d,%d) to (%d,%d)\n", win1->_begy, win1->_begx, win1->_begy + win1->_maxy, win1->_begx + win1->_maxx);
	fprintf(outf, "TOUCHOVERLAP:win2 (%d,%d) to (%d,%d)\n", win2->_begy, win2->_begx, win2->_begy + win2->_maxy, win2->_begx + win2->_maxx);
# endif
E 7
I 7
#ifdef DEBUG
D 13
	__TRACE("touchoverlap: from (%d,%d) to (%d,%d)\n",
E 13
I 13
	__CTRACE("touchoverlap: from (%d,%d) to (%d,%d)\n",
E 13
	    starty, startx, endy, endx);
D 13
	__TRACE("touchoverlap: win1 (%d,%d) to (%d,%d)\n",
E 13
I 13
	__CTRACE("touchoverlap: win1 (%d,%d) to (%d,%d)\n",
E 13
D 9
	    win1->_begy, win1->_begx, win1->_begy + win1->_maxy,
	    win1->_begx + win1->_maxx);
E 9
I 9
	    win1->begy, win1->begx, win1->begy + win1->maxy,
	    win1->begx + win1->maxx);
E 9
D 13
	__TRACE("touchoverlap: win2 (%d,%d) to (%d,%d)\n",
E 13
I 13
	__CTRACE("touchoverlap: win2 (%d,%d) to (%d,%d)\n",
E 13
D 9
	    win2->_begy, win2->_begx, win2->_begy + win2->_maxy,
	    win2->_begx + win2->_maxx);
E 9
I 9
	    win2->begy, win2->begx, win2->begy + win2->maxy,
	    win2->begx + win2->maxx);
E 9
#endif
E 7
	if (starty >= endy || startx >= endx)
D 7
		return;
E 7
I 7
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
E 7
D 9
	starty -= win2->_begy;
	startx -= win2->_begx;
	endy -= win2->_begy;
	endx -= win2->_begx;
E 9
I 9
	starty -= win2->begy;
	startx -= win2->begx;
	endy -= win2->begy;
	endx -= win2->begx;
E 9
D 7
	endx--;
	for (y = starty; y < endy; y++)
E 7
I 7
	for (--endx, y = starty; y < endy; y++)
E 7
D 10
		touchline(win2, y, startx, endx);
E 10
I 10
		__touchline(win2, y, startx, endx, 0);
E 10
I 7
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
E 7
}
I 10

E 10
E 1
