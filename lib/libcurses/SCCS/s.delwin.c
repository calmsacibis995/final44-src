h17892
s 00003/00002/00051
d D 8.2 94/05/04 06:24:39 bostic 20 19
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00051
d D 8.1 93/06/04 16:47:51 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00053
d D 5.11 93/02/18 16:38:14 elan 18 17
c Got rid of unused variable i.
e
s 00001/00001/00053
d D 5.10 93/01/11 11:53:46 bostic 17 16
c CURSES_{OK,ERR} -> OK,ERR
e
s 00001/00001/00053
d D 5.9 92/12/30 14:54:55 elan 16 15
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00002/00006/00052
d D 5.8 92/10/26 12:46:38 elan 15 14
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00013/00011/00045
d D 5.7 92/09/14 11:00:26 elan 14 13
c Converted to new data structures.
e
s 00001/00000/00055
d D 5.6 92/08/23 14:38:22 bostic 13 12
c lint
e
s 00017/00015/00038
d D 5.5 92/08/23 10:46:47 bostic 12 10
c KNF
e
s 00013/00010/00043
d R 5.5 92/05/15 15:27:45 bostic 11 10
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00052
d D 5.4 90/06/01 15:38:24 bostic 10 9
c new copyright notice
e
s 00010/00005/00053
d D 5.3 88/06/30 17:21:32 bostic 9 8
c install approved copyright notice
e
s 00010/00004/00048
d D 5.2 88/06/08 13:57:03 bostic 8 7
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00042
d D 5.1 85/06/07 11:30:21 dist 7 6
c Add copyright
e
s 00007/00007/00036
d D 1.6 85/05/01 17:05:13 bloom 6 5
c new version from arnold
e
s 00015/00000/00028
d D 1.5 83/04/06 18:38:47 arnold 5 4
c handle deleting subwindows
e
s 00000/00000/00028
d D 1.4 83/04/06 18:31:12 arnold 4 3
c try to deal with subwindow deletion
e
s 00010/00002/00018
d D 1.3 83/04/06 18:30:42 arnold 3 2
c try to deal with subwindows
e
s 00002/00000/00018
d D 1.2 83/03/27 15:09:50 arnold 2 1
c 
e
s 00018/00000/00000
d D 1.1 81/01/26 17:02:50 arnold 1 0
c date and time created 81/01/26 17:02:50 by arnold
e
u
U
t
T
I 7
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 19
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 19
I 19
D 20
 * Copyright (c) 1981, 1993
E 20
I 20
 * Copyright (c) 1981, 1993, 1994
E 20
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
E 8
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif not lint
E 8
I 8
D 12
#endif /* not lint */
E 12
I 12
#endif	/* not lint */
E 12
E 8

E 7
I 1
D 12
# include	"curses.ext"
E 12
I 12
D 20
#include <curses.h>
E 20
I 13
#include <stdlib.h>
I 20

#include "curses.h"
E 20
E 13
E 12

/*
D 12
 *	This routine deletes a window and releases it back to the system.
 *
E 12
I 12
 * delwin --
 *	Delete a window and release it back to the system.
E 12
D 6
 * %G% (Berkeley) %W%
E 6
I 6
D 7
 * %W% (Berkeley) %G%
E 7
E 6
 */
I 12
int
E 12
delwin(win)
D 12
reg WINDOW	*win; {
E 12
I 12
	register WINDOW *win;
{
E 12

D 3
	reg int	i;
E 3
I 3
D 12
	reg int		i;
	reg WINDOW	*wp, *np;
E 12
I 12
	register WINDOW *wp, *np;
I 14
D 15
	register LINE *lp;
E 15
E 14
D 18
	register int i;
E 18
E 12
E 3

D 3
	if (!(win->_flags & _SUBWIN))
E 3
I 3
D 14
	if (win->_orig == NULL) {
E 14
I 14
	if (win->orig == NULL) {
E 14
I 5
		/*
D 12
		 * If we are the original window, delete the space for
		 * all the subwindows, and the array of space as well.
E 12
I 12
		 * If we are the original window, delete the space for all
D 14
		 * the subwindows, and the array of space as well.
E 14
I 14
D 15
		 * the subwindows, and the array of space as well which is
		 * pointed to by win->topline->line.
E 15
I 15
		 * the subwindows, the line space and the window space.
E 15
E 14
E 12
		 */
E 5
E 3
D 14
		for (i = 0; i < win->_maxy && win->_y[i]; i++)
D 6
			cfree(win->_y[i]);
E 6
I 6
			free(win->_y[i]);
		free(win->_firstch);
		free(win->_lastch);
E 6
I 3
		wp = win->_nextp;
E 14
I 14
D 15

		for (lp = win->topline, i = 0; i < win->maxy; i++) 
			free(lp);
E 15
I 15
		free(win->lspace);
E 15
		free(win->wspace);
		free(win->lines);
		wp = win->nextp;
E 14
		while (wp != win) {
D 14
			np = wp->_nextp;
E 14
I 14
			np = wp->nextp;
E 14
			delwin(wp);
			wp = np;
		}
I 5
D 12
	}
	else {
E 12
I 12
	} else {
E 12
		/*
D 6
		 * If we are a subwindow, take ourself out of the
E 6
I 6
D 12
		 * If we are a subwindow, take ourselves out of the
E 6
		 * list.  NOTE: if we are a subwindow, the minimum list
		 * is orig followed by this subwindow, so there are
		 * always at least two windows in the list.
E 12
I 12
		 * If we are a subwindow, take ourselves out of the list.
		 * NOTE: if we are a subwindow, the minimum list is orig
		 * followed by this subwindow, so there are always at least
		 * two windows in the list.
E 12
		 */
D 14
		for (wp = win->_nextp; wp->_nextp != win; wp = wp->_nextp)
E 14
I 14
		for (wp = win->nextp; wp->nextp != win; wp = wp->nextp)
E 14
			continue;
D 14
		wp->_nextp = win->_nextp;
E 14
I 14
		wp->nextp = win->nextp;
E 14
E 5
	}
E 3
D 6
	cfree(win->_y);
I 2
	cfree(win->_firstch);
	cfree(win->_lastch);
E 2
	cfree(win);
E 6
I 6
D 14
	free(win->_y);
E 14
	free(win);
I 12
D 16
	return (OK);
E 16
I 16
D 17
	return (CURSES_OK);
E 17
I 17
	return (OK);
E 17
E 16
E 12
E 6
}
E 1
