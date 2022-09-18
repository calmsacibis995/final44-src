h60028
s 00002/00002/00026
d D 8.2 94/05/04 06:24:43 bostic 10 9
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00026
d D 8.1 93/06/04 16:48:19 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00026
d D 5.6 92/09/14 11:00:31 elan 8 7
c Converted to new data structures.
e
s 00008/00008/00020
d D 5.5 92/08/23 11:01:47 bostic 7 5
c KNF
e
s 00005/00004/00024
d R 5.5 92/05/15 15:25:12 bostic 6 5
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00027
d D 5.4 90/06/01 15:38:58 bostic 5 4
c new copyright notice
e
s 00010/00005/00028
d D 5.3 88/06/30 17:21:41 bostic 4 3
c install approved copyright notice
e
s 00010/00004/00023
d D 5.2 88/06/08 13:57:15 bostic 3 2
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00017
d D 5.1 85/06/07 11:33:53 dist 2 1
c Add copyright
e
s 00018/00000/00000
d D 1.1 85/05/01 17:13:53 bloom 1 0
c date and time created 85/05/01 17:13:53 by bloom
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
D 9
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 10
 * Copyright (c) 1981, 1993
E 10
I 10
 * Copyright (c) 1981, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 9
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
D 10
#include <curses.h>
E 10
I 10
#include "curses.h"
E 10
E 7

/*
D 7
 * idlok:
 *	Turn on and off using insert/deleteln sequences for the given
 *	window.
 *
E 7
I 7
 * idlok --
 *	Turn on and off using insert/deleteln sequences for the
 *	given window.
E 7
D 2
 * %W% (Berkeley) %G%
E 2
 */
I 7
void
E 7
idlok(win, bf)
D 7
register WINDOW	*win;
bool		bf;
E 7
I 7
	WINDOW *win;
	int bf;
E 7
{
	if (bf)
D 8
		win->_flags |= _IDLINE;
E 8
I 8
		win->flags |= __IDLINE;
E 8
	else
D 8
		win->_flags &= ~_IDLINE;
E 8
I 8
		win->flags &= ~__IDLINE;
E 8
}
E 1
