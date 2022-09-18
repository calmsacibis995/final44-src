h14719
s 00002/00002/00034
d D 8.2 94/05/04 06:24:47 bostic 17 16
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00034
d D 8.1 93/06/04 16:48:34 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00035
d D 5.13 93/05/16 15:54:42 bostic 15 14
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00001/00000/00035
d D 5.12 93/04/13 15:01:44 elan 14 13
c Move from line turns of __ISPASTEOL.
e
s 00003/00003/00032
d D 5.11 93/01/11 11:53:52 bostic 13 12
c CURSES_{OK,ERR} -> OK,ERR
e
s 00003/00003/00032
d D 5.10 92/12/30 14:55:01 elan 12 11
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00000/00000/00035
d D 5.9 92/11/05 17:01:46 elan 11 10
c 
e
s 00001/00000/00034
d D 5.8 92/09/21 15:23:50 elan 10 9
c Added __ISPASTEOL support.
e
s 00003/00003/00031
d D 5.7 92/09/14 11:00:35 elan 9 8
c Converted to new data structures.
e
s 00014/00012/00020
d D 5.6 92/08/23 11:13:37 bostic 8 6
c KNF
e
s 00013/00011/00021
d R 5.6 92/05/15 15:26:13 bostic 7 6
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00031
d D 5.5 90/06/01 15:39:16 bostic 6 5
c new copyright notice
e
s 00010/00005/00032
d D 5.4 88/06/30 17:21:47 bostic 5 4
c install approved copyright notice
e
s 00010/00004/00027
d D 5.3 88/06/08 13:57:24 bostic 4 3
c written by Ken Arnold; add Berkeley specific header
e
s 00002/00000/00029
d D 5.2 85/10/08 18:13:59 bloom 3 2
c check the position for negative values
e
s 00010/00001/00019
d D 5.1 85/06/07 11:35:49 dist 2 1
c Add copyright
e
s 00020/00000/00000
d D 1.1 83/03/27 16:12:36 arnold 1 0
c date and time created 83/03/27 16:12:36 by arnold
e
u
U
t
T
I 2
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
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

E 2
I 1
D 8
# include	"curses.ext"
E 8
I 8
D 17
#include <curses.h>
E 17
I 17
#include "curses.h"
E 17
E 8

/*
D 8
 *	This routine moves the cursor to the given point
 *
E 8
I 8
 * wmove --
 *	Moves the cursor to the given point.
E 8
D 2
 * %W% (Berkeley) %G%
E 2
 */
I 8
int
E 8
wmove(win, y, x)
D 8
reg WINDOW	*win;
reg int		y, x; {
E 8
I 8
	register WINDOW *win;
	register int y, x;
{
E 8

D 8
# ifdef DEBUG
	fprintf(outf, "MOVE to (%d, %d)\n", y, x);
# endif
E 8
I 8
#ifdef DEBUG
D 15
	__TRACE("wmove: (%d, %d)\n", y, x);
E 15
I 15
	__CTRACE("wmove: (%d, %d)\n", y, x);
E 15
#endif
E 8
I 3
	if (x < 0 || y < 0)
D 8
		return ERR;
E 8
I 8
D 12
		return (ERR);
E 12
I 12
D 13
		return (CURSES_ERR);
E 13
I 13
		return (ERR);
E 13
E 12
E 8
E 3
D 9
	if (x >= win->_maxx || y >= win->_maxy)
E 9
I 9
	if (x >= win->maxx || y >= win->maxy)
E 9
D 8
		return ERR;
E 8
I 8
D 12
		return (ERR);
E 12
I 12
D 13
		return (CURSES_ERR);
E 13
I 13
		return (ERR);
E 13
E 12
E 8
D 9
	win->_curx = x;
	win->_cury = y;
E 9
I 9
	win->curx = x;
I 14
	win->lines[win->cury]->flags &= ~__ISPASTEOL;
E 14
	win->cury = y;
I 10
	win->lines[y]->flags &= ~__ISPASTEOL;
E 10
E 9
D 8
	return OK;
E 8
I 8
D 12
	return (OK);
E 12
I 12
D 13
	return (CURSES_OK);
E 13
I 13
	return (OK);
E 13
E 12
E 8
}
E 1
