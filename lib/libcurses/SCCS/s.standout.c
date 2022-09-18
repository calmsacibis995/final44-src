h47976
s 00012/00013/00029
d D 8.3 94/08/10 07:48:37 bostic 12 11
c simplify the code, return an int (that's what System V does)
e
s 00002/00002/00040
d D 8.2 94/05/04 06:24:59 bostic 11 10
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00040
d D 8.1 93/06/04 16:49:16 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00040
d D 5.6 92/09/14 11:00:42 elan 9 8
c Converted to new data structures.
e
s 00009/00012/00033
d D 5.5 92/08/23 12:15:35 bostic 8 6
c KNF
e
s 00009/00012/00033
d R 5.5 92/05/15 15:17:57 bostic 7 6
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00044
d D 5.4 90/06/01 15:40:25 bostic 6 5
c new copyright notice
e
s 00010/00005/00045
d D 5.3 88/06/30 17:22:05 bostic 5 4
c install approved copyright notice
e
s 00010/00004/00040
d D 5.2 88/06/08 13:57:47 bostic 4 3
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00034
d D 5.1 85/06/07 11:42:26 dist 3 2
c Add copyright
e
s 00001/00001/00034
d D 1.2 85/05/01 17:34:43 bloom 2 1
c fix sccs id
e
s 00035/00000/00000
d D 1.1 81/01/26 17:03:14 arnold 1 0
c date and time created 81/01/26 17:03:14 by arnold
e
u
U
t
T
I 1
/*
I 3
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
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
#endif /* not lint */
E 4

D 8
/*
E 3
 * routines dealing with entering and exiting standout mode
 *
D 2
 * %G% (Berkeley) %W%
E 2
I 2
D 3
 * %W% (Berkeley) %G%
E 3
E 2
 */
E 8
I 8
D 11
#include <curses.h>
E 11
I 11
#include "curses.h"
E 11
E 8

D 8
# include	"curses.ext"

E 8
/*
D 8
 * enter standout mode
E 8
I 8
 * wstandout
 *	Enter standout mode.
E 8
 */
D 12
char *
E 12
I 12
int
E 12
wstandout(win)
D 8
reg WINDOW	*win;
E 8
I 8
D 12
	register WINDOW *win;
E 12
I 12
	WINDOW *win;
E 12
E 8
{
D 12
	if (!SO && !UC)
D 8
		return FALSE;
E 8
I 8
		return (0);
E 8

D 9
	win->_flags |= _STANDOUT;
E 9
I 9
	win->flags |= __WSTANDOUT;
E 9
	return (SO ? SO : UC);
E 12
I 12
	/*
	 * If standout/standend strings, or can underline, set the
	 * screen standout bit.
	 */
	if (SO != NULL && SE != NULL || UC != NULL)
		win->flags |= __WSTANDOUT;
	return (1);
E 12
}

/*
D 8
 * exit standout mode
E 8
I 8
 * wstandend --
 *	Exit standout mode.
E 8
 */
D 12
char *
E 12
I 12
int
E 12
wstandend(win)
D 8
reg WINDOW	*win;
E 8
I 8
D 12
	register WINDOW *win;
E 12
I 12
	WINDOW *win;
E 12
E 8
{
D 12
	if (!SO && !UC)
D 8
		return FALSE;
E 8
I 8
		return (0);
E 8

E 12
D 9
	win->_flags &= ~_STANDOUT;
E 9
I 9
	win->flags &= ~__WSTANDOUT;
E 9
D 12
	return (SE ? SE : UC);
E 12
I 12
	return (1);
E 12
}
E 1
