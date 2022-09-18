h53838
s 00003/00002/00053
d D 8.2 94/05/04 06:24:46 bostic 25 24
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00053
d D 8.1 93/06/04 16:48:28 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00054
d D 5.17 93/05/16 15:54:41 bostic 23 22
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00000/00001/00055
d D 5.16 93/02/18 16:39:24 elan 22 21
c Got rid of unsused variable 'end'.
e
s 00003/00002/00053
d D 5.15 93/02/18 16:18:41 elan 21 20
c bcopy -> memcpy.  Probably more portable.
e
s 00001/00001/00054
d D 5.14 93/01/11 11:53:51 bostic 20 19
c CURSES_{OK,ERR} -> OK,ERR
e
s 00001/00001/00054
d D 5.13 92/12/30 14:55:04 elan 19 18
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00002/00002/00053
d D 5.12 92/10/27 14:38:02 elan 18 17
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00006/00005/00049
d D 5.11 92/10/26 12:46:43 elan 17 16
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00003/00001/00051
d D 5.10 92/10/20 10:44:35 elan 16 15
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00001/00000/00051
d D 5.9 92/10/01 15:04:48 elan 15 14
c turn off __ISPASTEOL.
e
s 00001/00000/00050
d D 5.8 92/09/21 15:22:05 elan 14 13
c Added __ISPASTEOL support.
e
s 00017/00016/00033
d D 5.7 92/09/14 11:00:34 elan 13 12
c Converted to new data structures.
e
s 00002/00001/00047
d D 5.6 92/08/23 14:38:47 bostic 12 11
c lint
e
s 00014/00014/00034
d D 5.5 92/08/23 11:10:45 bostic 11 9
c KNF
e
s 00010/00012/00036
d R 5.5 92/05/15 15:25:56 bostic 10 9
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00047
d D 5.4 90/06/01 15:39:09 bostic 9 8
c new copyright notice
e
s 00010/00005/00048
d D 5.3 88/06/30 17:21:44 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00043
d D 5.2 88/06/08 13:57:20 bostic 7 6
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00037
d D 5.1 85/06/07 11:35:08 dist 6 5
c Add copyright
e
s 00019/00017/00019
d D 1.5 85/05/01 17:19:25 bloom 5 4
c newversion form arnold
e
s 00009/00000/00027
d D 1.4 81/04/17 00:44:35 arnold 4 3
c make it return ERR for illegal scroll type things
e
s 00002/00001/00025
d D 1.3 81/04/16 23:28:28 arnold 3 2
c fix stupid bugs so they WORK!
e
s 00000/00001/00026
d D 1.2 81/03/05 19:16:49 arnold 2 1
c eliminate unnecessary return
e
s 00027/00000/00000
d D 1.1 81/01/26 17:02:57 arnold 1 0
c date and time created 81/01/26 17:02:57 by arnold
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
D 24
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 24
I 24
D 25
 * Copyright (c) 1981, 1993
E 25
I 25
 * Copyright (c) 1981, 1993, 1994
E 25
 *	The Regents of the University of California.  All rights reserved.
E 24
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
D 11
# include	"curses.ext"
E 11
I 11
D 25
#include <curses.h>
E 25
I 12
#include <string.h>
I 25

#include "curses.h"
E 25
E 12
E 11

/*
D 11
 *	This routine performs an insert-line on the window, leaving
 * (_cury,_curx) unchanged.
 *
E 11
I 11
 * winsertln --
D 13
 *	Do an insert-line on the window, leaving (_cury,_curx) unchanged.
E 13
I 13
 *	Do an insert-line on the window, leaving (cury, curx) unchanged.
E 13
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
winsertln(win)
D 11
reg WINDOW	*win; {
E 11
I 11
	register WINDOW *win;
{
E 11

D 11
	reg char	*temp;
	reg int		y;
	reg char	*end;
I 5
	reg int		x;
E 11
I 11
D 12
	register int x, y;
E 12
I 12
D 16
	register int y;
E 16
I 16
	register int y, i;
E 16
E 12
D 13
	register char *end, *temp;
E 13
I 13
D 22
	register char *end;
E 22
D 17
	register LINE *temp;
E 17
I 17
	register __LINE *temp;
E 17
E 13
E 11
E 5

D 3
	temp = win->_y[win->_cury];
E 3
I 3
D 5
	temp = win->_y[win->_maxy-1];
E 3
	win->_firstch[win->_cury] = 0;
	win->_lastch[win->_cury] = win->_maxx - 1;
E 5
I 5
D 11
#ifdef	DEBUG
	fprintf(outf, "INSERTLN(%0.2o)\n", win);
E 11
I 11
#ifdef DEBUG
D 23
	__TRACE("insertln: (%0.2o)\n", win);
E 23
I 23
	__CTRACE("insertln: (%0.2o)\n", win);
E 23
E 11
#endif
D 13
	if (win->_orig == NULL)
		temp = win->_y[win->_maxy - 1];
E 5
	for (y = win->_maxy - 1; y > win->_cury; --y) {
D 5
		win->_y[y] = win->_y[y-1];
		win->_firstch[y] = 0;
		win->_lastch[y] = win->_maxx - 1;
E 5
I 5
		if (win->_orig == NULL)
			win->_y[y] = win->_y[y - 1];
E 13
I 13
	if (win->orig == NULL)
		temp = win->lines[win->maxy - 1];
	for (y = win->maxy - 1; y > win->cury; --y) {
I 14
		win->lines[y]->flags &= ~__ISPASTEOL;
I 15
		win->lines[y - 1]->flags &= ~__ISPASTEOL;
E 15
E 14
		if (win->orig == NULL)
			win->lines[y] = win->lines[y - 1];
E 13
		else
D 13
			bcopy(win->_y[y - 1], win->_y[y], win->_maxx);
		touchline(win, y, 0, win->_maxx - 1);
E 13
I 13
D 21
			bcopy(win->lines[y - 1]->line, 
D 17
			      win->lines[y]->line, win->maxx);
E 17
I 17
			      win->lines[y]->line, win->maxx * __LDATASIZE);
E 21
I 21
			(void)memcpy(win->lines[y]->line, 
			    win->lines[y - 1]->line, 
			    win->maxx * __LDATASIZE);
E 21
E 17
D 18
		touchline(win, y, 0, win->maxx - 1);
E 18
I 18
		__touchline(win, y, 0, win->maxx - 1, 0);
E 18
E 13
E 5
	}
I 5
D 13
	if (win->_orig == NULL)
		win->_y[y] = temp;
E 13
I 13
	if (win->orig == NULL)
		win->lines[y] = temp;
E 13
	else
D 13
		temp = win->_y[y];
E 5
D 11
	for (end = &temp[win->_maxx]; temp < end; )
E 11
I 11
	for (end = &temp[win->_maxx]; temp < end;)
E 11
		*temp++ = ' ';
I 3
D 5
	win->_y[win->_cury] = temp - win->_maxx;
I 4
	if (win->_cury == LINES - 1 && win->_y[LINES-1][COLS-1] != ' ')
		if (win->_scroll) {
			wrefresh(win);
			scroll(win);
			win->_cury--;
		}
		else
			return ERR;
	return OK;
E 5
I 5
	touchline(win, y, 0, win->_maxx - 1);
	if (win->_orig == NULL)
E 13
I 13
		temp = win->lines[y];
D 17
	(void)memset(temp->line, ' ', &temp->line[win->maxx] - temp->line);
I 16
	for(i = 0; i < win->maxx; i++)
		temp->standout[i] &= ~__STANDOUT;
E 17
I 17
	for(i = 0; i < win->maxx; i++) {
		temp->line[i].ch = ' ';
		temp->line[i].attr = 0;
	}
E 17
E 16
D 18
	touchline(win, y, 0, win->maxx - 1);
E 18
I 18
	__touchline(win, y, 0, win->maxx - 1, 0);
E 18
	if (win->orig == NULL)
E 13
D 11
		_id_subwins(win);
E 11
I 11
		__id_subwins(win);
D 19
	return (OK);
E 19
I 19
D 20
	return (CURSES_OK);
E 20
I 20
	return (OK);
E 20
E 19
E 11
E 5
E 4
E 3
D 2
	return OK;
E 2
}
E 1
