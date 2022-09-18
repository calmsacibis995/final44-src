h23821
s 00002/00002/00047
d D 8.2 94/05/04 06:24:41 bostic 17 16
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00047
d D 8.1 93/06/04 16:48:04 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00047
d D 5.11 93/05/16 15:54:39 bostic 15 14
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00001/00001/00048
d D 5.10 93/01/11 11:53:48 bostic 14 13
c CURSES_{OK,ERR} -> OK,ERR
e
s 00001/00001/00048
d D 5.9 92/12/30 14:54:59 elan 13 12
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00003/00003/00046
d D 5.8 92/09/14 11:00:28 elan 12 11
c Converted to new data structures.
e
s 00026/00023/00023
d D 5.7 92/08/23 10:56:45 bostic 11 9
c KNF
e
s 00020/00018/00028
d R 5.7 92/05/15 15:33:01 bostic 10 9
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00045
d D 5.6 90/06/01 15:38:46 bostic 9 8
c new copyright notice
e
s 00010/00005/00046
d D 5.5 88/06/30 17:21:37 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00041
d D 5.4 88/06/08 13:57:10 bostic 7 6
c written by Ken Arnold; add Berkeley specific header
e
s 00002/00002/00043
d D 5.3 86/04/16 18:20:53 mckusick 6 5
c turn on cbreak, not raw in getch() if none of noecho, raw, or
c cbreak are already set (from sun!gorodish!guy)
e
s 00002/00001/00043
d D 5.2 85/11/04 15:30:21 bloom 5 4
c echo where typed not top of screen
e
s 00010/00001/00034
d D 5.1 85/06/07 11:32:21 dist 4 3
c Add copyright
e
s 00001/00001/00034
d D 1.3 85/05/01 17:11:27 bloom 3 2
c fix sccs id
e
s 00001/00001/00034
d D 1.2 81/05/11 17:34:28 arnold 2 1
c fix an off-by-one error
e
s 00035/00000/00000
d D 1.1 81/01/26 17:02:54 arnold 1 0
c date and time created 81/01/26 17:02:54 by arnold
e
u
U
t
T
I 4
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
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

E 4
I 1
D 11
# include	"curses.ext"
E 11
I 11
D 17
#include <curses.h>
E 17
I 17
#include "curses.h"
E 17
E 11

/*
D 11
 *	This routine reads in a character from the window.
 *
E 11
I 11
 * wgetch --
 *	Read in a character from the window.
E 11
D 3
 * %G% (Berkeley) %W%
E 3
I 3
D 4
 * %W% (Berkeley) %G%
E 4
E 3
 */
I 11
int
E 11
wgetch(win)
D 11
reg WINDOW	*win; {
E 11
I 11
	register WINDOW *win;
{
	register int inp, weset;
E 11

D 11
	reg bool	weset = FALSE;
	reg char	inp;

	if (!win->_scroll && (win->_flags&_FULLWIN)
E 11
I 11
D 12
	if (!win->_scroll && (win->_flags & _FULLWIN)
E 11
D 2
	    && win->_curx == win->_maxx && win->_cury == win->_maxy)
E 2
I 2
	    && win->_curx == win->_maxx - 1 && win->_cury == win->_maxy - 1)
E 12
I 12
	if (!(win->flags & __SCROLLOK) && (win->flags & __FULLWIN)
	    && win->curx == win->maxx - 1 && win->cury == win->maxy - 1)
E 12
E 2
D 11
		return ERR;
# ifdef DEBUG
	fprintf(outf, "WGETCH: _echoit = %c, _rawmode = %c\n", _echoit ? 'T' : 'F', _rawmode ? 'T' : 'F');
# endif
	if (_echoit && !_rawmode) {
E 11
I 11
D 13
		return (ERR);
E 13
I 13
D 14
		return (CURSES_ERR);
E 14
I 14
		return (ERR);
E 14
E 13
#ifdef DEBUG
D 15
	__TRACE("wgetch: __echoit = %d, __rawmode = %d\n",
E 15
I 15
	__CTRACE("wgetch: __echoit = %d, __rawmode = %d\n",
E 15
	    __echoit, __rawmode);
#endif
	if (__echoit && !__rawmode) {
E 11
D 6
		raw();
E 6
I 6
		cbreak();
E 6
D 11
		weset++;
	}
E 11
I 11
		weset = 1;
	} else
		weset = 0;

E 11
	inp = getchar();
D 11
# ifdef DEBUG
	fprintf(outf,"WGETCH got '%s'\n",unctrl(inp));
# endif
	if (_echoit) {
D 5
		mvwaddch(curscr, win->_cury, win->_curx, inp);
E 5
I 5
		mvwaddch(curscr, win->_cury + win->_begy,
			win->_curx + win->_begx, inp);
E 11
I 11
#ifdef DEBUG
D 15
	__TRACE("wgetch got '%s'\n", unctrl(inp));
E 15
I 15
	__CTRACE("wgetch got '%s'\n", unctrl(inp));
E 15
#endif
	if (__echoit) {
		mvwaddch(curscr,
D 12
		    win->_cury + win->_begy, win->_curx + win->_begx, inp);
E 12
I 12
		    win->cury + win->begy, win->curx + win->begx, inp);
E 12
E 11
E 5
		waddch(win, inp);
	}
	if (weset)
D 6
		noraw();
E 6
I 6
		nocbreak();
E 6
D 11
	return inp;
E 11
I 11
	return (inp);
E 11
}
E 1
