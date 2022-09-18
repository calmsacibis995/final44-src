h40602
s 00002/00002/00025
d D 8.2 94/05/04 06:24:31 bostic 13 12
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00025
d D 8.1 93/06/04 16:47:10 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00024
d D 5.8 93/01/11 11:53:40 bostic 11 10
c CURSES_{OK,ERR} -> OK,ERR
e
s 00003/00003/00024
d D 5.7 92/12/30 14:54:51 elan 10 9
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00001/00001/00026
d D 5.6 92/09/14 11:00:19 elan 9 8
c Converted to new data structures.
e
s 00012/00009/00015
d D 5.5 92/08/23 10:04:24 bostic 8 6
c KNF, pass back error value if any
e
s 00011/00008/00016
d R 5.5 92/05/15 14:17:40 bostic 7 6
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00023
d D 5.4 90/06/01 15:37:28 bostic 6 5
c new copyright notice
e
s 00010/00005/00024
d D 5.3 88/06/30 17:21:15 bostic 5 4
c install approved copyright notice
e
s 00010/00004/00019
d D 5.2 88/06/08 13:56:46 bostic 4 3
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00013
d D 5.1 85/06/07 11:25:54 dist 3 2
c Add copyright
e
s 00001/00010/00013
d D 1.2 85/05/01 16:39:33 bloom 2 1
c new version from arnold
e
s 00023/00000/00000
d D 1.1 81/01/26 17:02:37 arnold 1 0
c date and time created 81/01/26 17:02:37 by arnold
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 12
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 12
I 12
D 13
 * Copyright (c) 1981, 1993
E 13
I 13
 * Copyright (c) 1981, 1993, 1994
E 13
 *	The Regents of the University of California.  All rights reserved.
E 12
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

E 3
I 1
D 8
# include	"curses.ext"
E 8
I 8
D 13
#include <curses.h>
E 13
I 13
#include "curses.h"
E 13
E 8

/*
D 8
 *	This routine clears the window.
 *
E 8
I 8
 * wclear --
 *	Clear the window.
E 8
D 2
 * %G% (Berkeley) %W%
E 2
I 2
D 3
 * %W% (Berkeley) %G%
E 3
E 2
 */
I 8
int
E 8
wclear(win)
D 8
reg WINDOW	*win; {

D 2
	if (win == curscr) {
# ifdef DEBUG
		fprintf(outf,"WCLEAR: win == curscr\n");
		fprintf(outf,"WCLEAR: curscr = %d\n",curscr);
		fprintf(outf,"WCLEAR: stdscr = %d\n",stdscr);
# endif
		clear();
		return refresh();
	}
E 2
	werase(win);
	win->_clear = TRUE;
	return OK;
E 8
I 8
	register WINDOW *win;
{
D 10
	if (werase(win) == OK) {
E 10
I 10
D 11
	if (werase(win) == CURSES_OK) {
E 11
I 11
	if (werase(win) == OK) {
E 11
E 10
D 9
		win->_clear = 1;
E 9
I 9
		win->flags |= __CLEAROK;
E 9
D 10
		return (OK);
E 10
I 10
D 11
		return (CURSES_OK);
E 11
I 11
		return (OK);
E 11
E 10
	}
D 10
	return (ERR);
E 10
I 10
D 11
	return (CURSES_ERR);
E 11
I 11
	return (ERR);
E 11
E 10
E 8
}
E 1
