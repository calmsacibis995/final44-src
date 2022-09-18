h28482
s 00003/00002/00045
d D 8.2 94/05/04 06:24:45 bostic 19 18
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00045
d D 8.1 93/06/04 16:48:25 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00046
d D 5.13 93/02/18 16:59:14 elan 17 16
c Need string.h for memcpy.
e
s 00001/00001/00045
d D 5.12 93/02/18 16:18:38 elan 16 15
c bcopy -> memcpy.  Probably more portable.
e
s 00002/00002/00044
d D 5.11 93/01/11 11:53:51 bostic 15 14
c CURSES_{OK,ERR} -> OK,ERR
e
s 00002/00002/00044
d D 5.10 92/12/30 14:54:46 elan 14 13
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00001/00001/00045
d D 5.9 92/10/27 14:37:53 elan 13 12
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00007/00009/00039
d D 5.8 92/10/26 12:46:33 elan 12 11
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00009/00003/00039
d D 5.7 92/10/20 10:44:27 elan 11 10
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00007/00006/00035
d D 5.6 92/09/14 11:00:32 elan 10 9
c Converted to new data structures.
e
s 00015/00016/00026
d D 5.5 92/08/23 11:08:36 bostic 9 7
c KNF
e
s 00012/00013/00029
d R 5.5 92/05/15 15:20:54 bostic 8 7
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00041
d D 5.4 90/06/01 15:39:05 bostic 7 6
c new copyright notice
e
s 00010/00005/00042
d D 5.3 88/06/30 17:21:43 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00037
d D 5.2 88/06/08 13:57:18 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00031
d D 5.1 85/06/07 11:34:43 dist 4 3
c Add copyright
e
s 00001/00004/00031
d D 1.3 85/05/01 17:18:12 bloom 3 2
c new version from arnold
e
s 00001/00003/00034
d D 1.2 81/04/17 00:45:32 arnold 2 1
c don't erase the last character when returning ERR
e
s 00037/00000/00000
d D 1.1 81/04/17 00:26:16 arnold 1 0
c date and time created 81/04/17 00:26:16 by arnold
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
D 19
#include <curses.h>
E 19
I 17
#include <string.h>
I 19

#include "curses.h"
E 19
E 17
E 9

/*
D 9
 *	This routine performs an insert-char on the line, leaving
 * (_cury,_curx) unchanged.
 *
E 9
I 9
 * winsch --
D 12
 *	Do an insert-char on the line, leaving (_cury,_curx) unchanged.
E 12
I 12
 *	Do an insert-char on the line, leaving (cury, curx) unchanged.
E 12
E 9
D 4
 * %W% (Berkeley) %G%
E 4
 */
D 9
winsch(win, c)
reg WINDOW	*win;
char		c; {
E 9
I 9
int
winsch(win, ch)
	register WINDOW *win;
	int ch;
{
E 9

D 9
	reg char	*temp1, *temp2;
	reg char	*end;
E 9
I 9
D 12
	register char *end, *temp1, *temp2;
E 12
I 12
	register __LDATA *end, *temp1, *temp2;
E 12
E 9

D 10
	end = &win->_y[win->_cury][win->_curx];
	temp1 = &win->_y[win->_cury][win->_maxx - 1];
E 10
I 10
	end = &win->lines[win->cury]->line[win->curx];
	temp1 = &win->lines[win->cury]->line[win->maxx - 1];
E 10
	temp2 = temp1 - 1;
D 11
	while (temp1 > end)
		*temp1-- = *temp2--;
E 11
I 11
	while (temp1 > end) {
D 12
		*temp1 = *temp2;
		/* standout array */
		*(temp1 + win->maxx) = *(temp2 + win->maxx);
E 12
I 12
D 16
		bcopy(temp2, temp1, sizeof(__LDATA));
E 16
I 16
		(void)memcpy(temp1, temp2, sizeof(__LDATA));
E 16
E 12
		temp1--, temp2--;
	}
E 11
D 9
	*temp1 = c;
E 9
I 9
D 12
	*temp1 = ch;
I 11
	*(temp1 + win->maxx) &= ~__STANDOUT;
E 12
I 12
	temp1->ch = ch;
	temp1->attr &= ~__STANDOUT;
E 12
E 11
E 9
D 3
	win->_lastch[win->_cury] = win->_maxx - 1;
	if (win->_firstch[win->_cury] == _NOCHANGE ||
	    win->_firstch[win->_cury] > win->_curx)
		win->_firstch[win->_cury] = win->_curx;
E 3
I 3
D 10
	touchline(win, win->_cury, win->_curx, win->_maxx - 1);
E 3
D 9
	if (win->_cury == LINES - 1 && win->_y[LINES-1][COLS-1] != ' ')
E 9
I 9
	if (win->_cury == LINES - 1 && win->_y[LINES - 1][COLS - 1] != ' ')
E 9
		if (win->_scroll) {
E 10
I 10
D 13
	touchline(win, win->cury, win->curx, win->maxx - 1);
E 13
I 13
	__touchline(win, win->cury, win->curx, win->maxx - 1, 0);
E 13
	if (win->cury == LINES - 1 && 
D 11
	    win->lines[LINES - 1]->line[COLS - 1] != ' ')
E 11
I 11
D 12
	    (win->lines[LINES - 1]->line[COLS - 1] != ' ' ||
	    win->lines[LINES -1]->standout[COLS - 1] & __STANDOUT))
E 12
I 12
	    (win->lines[LINES - 1]->line[COLS - 1].ch != ' ' ||
	    win->lines[LINES -1]->line[COLS - 1].attr != 0))
E 12
E 11
		if (win->flags & __SCROLLOK) {
E 10
			wrefresh(win);
			scroll(win);
D 10
			win->_cury--;
E 10
I 10
			win->cury--;
E 10
D 9
		}
D 2
		else {
			win->_y[LINES-1][COLS-1] = ' ';
E 2
I 2
		else
E 2
			return ERR;
D 2
		}
E 2
	return OK;
E 9
I 9
		} else
D 14
			return (ERR);
	return (OK);
E 14
I 14
D 15
			return (CURSES_ERR);
	return (CURSES_OK);
E 15
I 15
			return (ERR);
	return (OK);
E 15
E 14
E 9
}
E 1
