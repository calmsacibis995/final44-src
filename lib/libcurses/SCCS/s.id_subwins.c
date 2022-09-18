h63190
s 00002/00002/00037
d D 8.2 94/05/04 06:24:42 bostic 11 10
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00037
d D 8.1 93/06/04 16:48:13 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00007/00031
d D 5.7 92/09/14 11:00:30 elan 9 8
c Converted to new data structures.
e
s 00001/00001/00037
d D 5.6 92/08/23 14:38:42 bostic 8 7
c lint
e
s 00010/00011/00028
d D 5.5 92/08/23 11:00:04 bostic 7 5
c KNF
e
s 00006/00006/00033
d R 5.5 92/05/15 15:20:16 bostic 6 5
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00038
d D 5.4 90/06/01 15:38:54 bostic 5 4
c new copyright notice
e
s 00010/00005/00039
d D 5.3 88/06/30 17:21:39 bostic 4 3
c install approved copyright notice
e
s 00010/00004/00034
d D 5.2 88/06/08 13:57:13 bostic 3 2
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00028
d D 5.1 85/06/07 11:33:23 dist 2 1
c Add copyright
e
s 00029/00000/00000
d D 1.1 85/05/01 17:12:56 bloom 1 0
c date and time created 85/05/01 17:12:56 by bloom
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
D 10
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 10
I 10
D 11
 * Copyright (c) 1981, 1993
E 11
I 11
 * Copyright (c) 1981, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 10
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
D 7
#endif /* not lint */
E 7
I 7
#endif	/* not lint */
E 7
E 3

E 2
I 1
D 7
# include	"curses.ext"
E 7
I 7
D 11
#include <curses.h>
E 11
I 11
#include "curses.h"
E 11
E 7

/*
D 7
 * _id_subwins:
E 7
I 7
 * __id_subwins --
E 7
D 9
 *	Re-sync the pointers to _y for all the subwindows.
E 9
I 9
 *	Re-sync the pointers to lines for all the subwindows.
E 9
D 7
 *
E 7
D 2
 * %W% (Berkeley) %G%
E 2
 */
D 7
_id_subwins(orig)
register WINDOW	*orig;
E 7
I 7
void
__id_subwins(orig)
	register WINDOW *orig;
E 7
{
D 7
	register WINDOW	*win;
	register int	realy;
	register int	y, oy, x;
E 7
I 7
	register WINDOW *win;
D 8
	register int oy, realy, x, y;
E 8
I 8
	register int oy, realy, y;
E 8
E 7

D 9
	realy = orig->_begy + orig->_cury;
	for (win = orig->_nextp; win != orig; win = win->_nextp) {
E 9
I 9
	realy = orig->begy + orig->cury;
	for (win = orig->nextp; win != orig; win = win->nextp) {
E 9
		/*
D 7
		 * If the window ends before our current position,
		 * don't need to do anything.
E 7
I 7
		 * If the window ends before our current position, don't need
		 * to do anything.
E 7
		 */
D 9
		if (win->_begy + win->_maxy <= realy)
E 9
I 9
		if (win->begy + win->maxy <= realy)
E 9
			continue;

D 9
		oy = orig->_cury;
		for (y = realy - win->_begy; y < win->_maxy; y++, oy++)
			win->_y[y] = &orig->_y[oy][win->_ch_off];
E 9
I 9
		oy = orig->cury;
		for (y = realy - win->begy; y < win->maxy; y++, oy++)
			win->lines[y]->line = 
				&orig->lines[oy]->line[win->ch_off];
E 9
	}
}
E 1
