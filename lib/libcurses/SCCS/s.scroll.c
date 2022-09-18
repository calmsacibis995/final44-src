h43125
s 00002/00002/00043
d D 8.3 94/05/04 06:24:57 bostic 25 24
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00000/00001/00045
d D 8.2 94/01/09 14:40:36 bostic 24 23
c don't need termios.h any longer
e
s 00002/00002/00044
d D 8.1 93/06/11 13:37:24 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00045
d D 5.14 93/06/11 13:37:04 bostic 22 20
c Round #4; try to get ONLCR/NONL right once again
e
s 00002/00002/00044
d R 8.1 93/06/04 16:49:08 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00045
d D 5.13 93/06/04 16:11:58 marc 20 19
c changed to remember and restore TSTP handler, and also to resnapshot tty state when restarting from TSTP.  Also, hardwire GT variable since we always turn tab expansion off.  We still aren't sure what pfast is for, but we haven't given up yet.
e
s 00002/00002/00044
d D 5.12 93/05/16 15:54:49 bostic 19 18
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00001/00001/00045
d D 5.11 93/01/24 20:13:59 bostic 18 17
c rename origtermio to be __orig_termios
e
s 00002/00002/00044
d D 5.10 93/01/11 11:54:00 bostic 17 16
c CURSES_{OK,ERR} -> OK,ERR
e
s 00002/00002/00044
d D 5.9 92/12/30 14:55:04 elan 16 15
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00000/00000/00046
d D 5.8 92/10/26 12:46:45 elan 15 14
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00002/00002/00044
d D 5.7 92/09/14 11:00:41 elan 14 13
c Converted to new data structures.
e
s 00002/00001/00044
d D 5.6 92/08/31 14:23:47 elan 13 12
c deleted references to NONL.
e
s 00015/00013/00030
d D 5.5 92/08/23 12:13:44 bostic 12 10
c KNF
e
s 00013/00011/00032
d R 5.5 92/05/15 15:18:24 bostic 11 10
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00042
d D 5.4 90/06/01 15:40:17 bostic 10 9
c new copyright notice
e
s 00010/00005/00043
d D 5.3 88/06/30 17:22:04 bostic 9 8
c install approved copyright notice
e
s 00010/00004/00038
d D 5.2 88/06/08 13:57:45 bostic 8 7
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00032
d D 5.1 85/06/07 11:41:57 dist 7 6
c Add copyright
e
s 00012/00020/00021
d D 1.6 85/05/23 15:41:56 bloom 6 5
c bug fix from arnold
e
s 00002/00002/00039
d D 1.5 85/05/01 17:34:07 bloom 5 4
c new version from arnold
e
s 00006/00003/00035
d D 1.4 84/07/20 11:48:00 mckusick 4 3
c fix gratuitous extra line of scrolling (from sdcsvax!laman)
e
s 00004/00003/00034
d D 1.3 83/06/01 14:04:42 arnold 3 2
c copy the last line to the next to last, too
e
s 00001/00001/00036
d D 1.2 81/05/11 17:38:10 arnold 2 1
c fix an off-by-one error
e
s 00037/00000/00000
d D 1.1 81/01/26 17:03:13 arnold 1 0
c date and time created 81/01/26 17:03:13 by arnold
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
D 23
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 23
I 23
D 25
 * Copyright (c) 1981, 1993
E 25
I 25
 * Copyright (c) 1981, 1993, 1994
E 25
 *	The Regents of the University of California.  All rights reserved.
E 23
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
#endif /* not lint */
E 8

E 7
I 1
D 12
# include	"curses.ext"
E 12
I 12
D 25
#include <curses.h>
E 25
I 25
#include "curses.h"
E 25
I 13
D 24
#include <termios.h>
E 24
E 13
E 12

/*
D 12
 *	This routine scrolls the window up a line.
 *
E 12
I 12
 * scroll --
 *	Scroll the window up a line.
E 12
D 5
 * %G% (Berkeley) %W%
E 5
I 5
D 7
 * %W% (Berkeley) %G%
E 7
E 5
 */
I 12
int
E 12
scroll(win)
D 6
reg WINDOW	*win; {
E 6
I 6
D 12
register  WINDOW	*win;
E 12
I 12
	register WINDOW *win;
E 12
{
D 12
	register int	oy, ox;
E 12
I 12
	register int oy, ox;
E 12
E 6

D 6
	reg char	*sp;
	reg int		i;
	reg char	*temp;
E 6
I 6
D 12
# ifdef DEBUG
	fprintf(outf, "SCROLL(%0.2o)\n", win);
# endif
E 12
I 12
#ifdef DEBUG
D 19
	__TRACE("scroll: (%0.2o)\n", win);
E 19
I 19
	__CTRACE("scroll: (%0.2o)\n", win);
E 19
#endif
E 12
E 6

D 14
	if (!win->_scroll)
E 14
I 14
	if (!(win->flags & __SCROLLOK))
E 14
D 12
		return ERR;
E 12
I 12
D 16
		return (ERR);
E 16
I 16
D 17
		return (CURSES_ERR);
E 17
I 17
		return (ERR);
E 17
E 16
E 12
D 6
	temp = win->_y[0];
D 2
	for (i = 0; i < win->_maxy - 1; i++)
E 2
I 2
D 3
	for (i = 0; i < win->_maxy - 2; i++)
E 2
		win->_y[i] = win->_y[i+1];
	for (sp = temp; sp - temp < win->_maxx; )
E 3
I 3
	for (i = 1; i < win->_maxy; i++)
		win->_y[i - 1] = win->_y[i];
	for (sp = temp; sp < &temp[win->_maxx]; )
E 3
		*sp++ = ' ';
	win->_y[win->_maxy - 1] = temp;
E 6
I 6

	getyx(win, oy, ox);
	wmove(win, 0, 0);
	wdeleteln(win);
	wmove(win, oy, ox);

E 6
D 4
	win->_cury--;
E 4
	if (win == curscr) {
D 5
		putchar('\n');
E 5
I 5
D 12
		_putchar('\n');
E 12
I 12
		putchar('\n');
E 12
E 5
D 13
		if (!NONL)
E 13
I 13
D 18
		if (origtermio.c_oflag & ONLCR)
E 18
I 18
D 20
		if (__orig_termios.c_oflag & ONLCR)
E 20
I 20
D 22
		if (__baset.c_oflag & ONLCR)
E 22
I 22
		if (!NONL)
E 22
E 20
E 18
E 13
D 14
			win->_curx = 0;
E 14
I 14
			win->curx = 0;
E 14
D 12
# ifdef DEBUG
		fprintf(outf, "SCROLL: win == curscr\n");
I 4
D 6
		fflush(outf);
E 6
E 4
# endif
E 12
I 12
#ifdef DEBUG
D 19
		__TRACE("scroll: win == curscr\n");
E 19
I 19
		__CTRACE("scroll: win == curscr\n");
E 19
#endif
E 12
D 4
	}
E 4
I 4
D 6
	} else {
		if(win->_cury-- <= 0)
			win->_cury = 0;
E 4
# ifdef DEBUG
D 4
	else
E 4
		fprintf(outf, "SCROLL: win [0%o] != curscr [0%o]\n",win,curscr);
I 4
		fflush(outf);
E 4
# endif
E 6
I 4
	}
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
E 4
I 3
D 6
	touchwin(win);
E 3
	return OK;
E 6
}
E 1
