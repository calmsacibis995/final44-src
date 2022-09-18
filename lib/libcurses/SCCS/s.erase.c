h36567
s 00002/00002/00044
d D 8.2 94/05/04 06:24:40 bostic 18 17
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00044
d D 8.1 93/06/04 16:47:56 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00045
d D 5.12 93/05/16 15:54:39 bostic 16 15
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00001/00001/00045
d D 5.11 93/01/11 11:53:47 bostic 15 14
c CURSES_{OK,ERR} -> OK,ERR
e
s 00001/00001/00045
d D 5.10 92/12/30 14:54:54 elan 14 13
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00002/00001/00044
d D 5.9 92/10/27 14:37:58 elan 13 12
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00005/00006/00040
d D 5.8 92/10/26 12:46:37 elan 12 11
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00002/00001/00044
d D 5.7 92/10/20 10:44:32 elan 11 10
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00008/00008/00037
d D 5.6 92/09/14 11:00:27 elan 10 9
c Converted to new data structures.
e
s 00013/00011/00032
d D 5.5 92/08/23 10:50:43 bostic 9 7
c KNF
e
s 00011/00011/00032
d R 5.5 92/05/15 15:20:08 bostic 8 7
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00042
d D 5.4 90/06/01 15:38:34 bostic 7 6
c new copyright notice
e
s 00010/00005/00043
d D 5.3 88/06/30 17:21:34 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00038
d D 5.2 88/06/08 13:57:06 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00032
d D 5.1 85/06/07 11:31:17 dist 4 3
c Add copyright
e
s 00003/00008/00030
d D 1.3 85/05/01 17:08:42 bloom 3 2
c new version from arnold
e
s 00003/00000/00035
d D 1.2 81/01/27 12:29:20 arnold 2 1
c add debug messages
e
s 00035/00000/00000
d D 1.1 81/01/26 17:02:53 arnold 1 0
c date and time created 81/01/26 17:02:53 by arnold
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
D 9
#endif /* not lint */
E 9
I 9
#endif	/* not lint */
E 9
E 5

E 4
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
 * werase --
 *	Erases everything on the window.
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
werase(win)
D 9
reg WINDOW	*win; {
E 9
I 9
	register WINDOW *win;
{
E 9

D 9
	reg int		y;
	reg char	*sp, *end, *start, *maxx;
	reg int		minx;
E 9
I 9
	register int minx, y;
D 12
	register char *sp, *end, *start, *maxx;
E 12
I 12
	register __LDATA *sp, *end, *start, *maxx;
E 12
E 9

I 2
D 9
# ifdef DEBUG
	fprintf(outf, "WERASE(%0.2o)\n", win);
# endif
E 9
I 9
#ifdef DEBUG
D 16
	__TRACE("werase: (%0.2o)\n", win);
E 16
I 16
	__CTRACE("werase: (%0.2o)\n", win);
E 16
#endif
E 9
E 2
D 10
	for (y = 0; y < win->_maxy; y++) {
		minx = _NOCHANGE;
		start = win->_y[y];
		end = &start[win->_maxx];
E 10
I 10
	for (y = 0; y < win->maxy; y++) {
		minx = -1;
		start = win->lines[y]->line;
		end = &start[win->maxx];
E 10
		for (sp = start; sp < end; sp++)
D 11
			if (*sp != ' ') {
E 11
I 11
D 12
			if (*sp != ' ' || *(sp + win->maxx) & __STANDOUT) {
E 11
				maxx = sp;
E 12
I 12
			if (sp->ch != ' ' || sp->attr != 0) {
				maxx = sp; 
E 12
D 10
				if (minx == _NOCHANGE)
E 10
I 10
				if (minx == -1)
E 10
					minx = sp - start;
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
D 3
		if (minx != _NOCHANGE) {
			if (win->_firstch[y] > minx
			     || win->_firstch[y] == _NOCHANGE)
				win->_firstch[y] = minx;
			if (win->_lastch[y] < maxx - win->_y[y])
				win->_lastch[y] = maxx - win->_y[y];
		}
E 3
I 3
D 10
		if (minx != _NOCHANGE)
			touchline(win, y, minx, maxx - win->_y[y]);
E 10
I 10
		if (minx != -1)
D 13
			touchline(win, y, minx, maxx - win->lines[y]->line);
E 13
I 13
			__touchline(win, y, minx, maxx - win->lines[y]->line,
			   0);
E 13
E 10
E 3
	}
D 10
	win->_curx = win->_cury = 0;
E 10
I 10
D 12
	win->curx = win->cury = 0;
E 12
E 10
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
