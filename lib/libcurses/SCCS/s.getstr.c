h05071
s 00002/00002/00029
d D 8.2 94/05/04 06:24:41 bostic 16 15
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00029
d D 8.1 93/06/04 16:48:07 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00027
d D 5.8 93/01/11 11:53:49 bostic 14 13
c CURSES_{OK,ERR} -> OK,ERR
e
s 00004/00004/00027
d D 5.7 92/12/30 14:54:57 elan 13 12
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00001/00001/00030
d D 5.6 92/09/14 11:00:29 elan 12 11
c Converted to new data structures.
e
s 00011/00010/00020
d D 5.5 92/08/23 10:58:01 bostic 11 9
c KNF
e
s 00010/00008/00022
d R 5.5 92/05/15 15:24:13 bostic 10 9
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00029
d D 5.4 90/06/01 15:38:50 bostic 9 8
c new copyright notice
e
s 00010/00005/00030
d D 5.3 88/06/30 17:21:38 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00025
d D 5.2 88/06/08 13:57:11 bostic 7 6
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00019
d D 5.1 85/06/07 11:32:52 dist 6 5
c Add copyright
e
s 00001/00001/00019
d D 1.5 85/05/01 17:11:32 bloom 5 4
c fix sccs id
e
s 00001/00001/00019
d D 1.4 83/06/21 14:29:49 arnold 4 3
c delete a spurious semicolon at the end of a while
e
s 00001/00001/00019
d D 1.3 81/04/29 15:27:28 arnold 3 2
c fix a stupid typo
e
s 00004/00002/00016
d D 1.2 81/04/10 13:02:21 arnold 2 1
c fix bug in EOF check
e
s 00018/00000/00000
d D 1.1 81/01/26 17:02:55 arnold 1 0
c date and time created 81/01/26 17:02:55 by arnold
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
D 15
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 15
I 15
D 16
 * Copyright (c) 1981, 1993
E 16
I 16
 * Copyright (c) 1981, 1993, 1994
E 16
 *	The Regents of the University of California.  All rights reserved.
E 15
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
D 16
#include <curses.h>
E 16
I 16
#include "curses.h"
E 16
E 11

/*
D 11
 *	This routine gets a string starting at (_cury,_curx)
 *
E 11
I 11
 * wgetstr --
D 12
 *	Get a string starting at (_cury,_curx).
E 12
I 12
 *	Get a string starting at (cury, curx).
E 12
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
D 11
wgetstr(win,str)
reg WINDOW	*win; 
reg char	*str; {

E 11
I 11
int
wgetstr(win, str)
	register WINDOW *win;
	register char *str;
{
E 11
D 4
	while ((*str = wgetch(win)) != ERR && *str != '\n');
E 4
I 4
D 13
	while ((*str = wgetch(win)) != ERR && *str != '\n')
E 13
I 13
D 14
	while ((*str = wgetch(win)) != CURSES_ERR && *str != '\n')
E 14
I 14
	while ((*str = wgetch(win)) != ERR && *str != '\n')
E 14
E 13
E 4
		str++;
D 2
	*str = '\0';
	if (*str == ERR)
E 2
I 2
D 13
	if (*str == ERR) {
E 13
I 13
D 14
	if (*str == CURSES_ERR) {
E 14
I 14
	if (*str == ERR) {
E 14
E 13
E 2
D 3
		return ERR;
E 3
I 2
		*str = '\0';
I 3
D 11
		return ERR;
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
E 11
E 3
	}
	*str = '\0';
E 2
D 11
	return OK;
E 11
I 11
D 13
	return (OK);
E 13
I 13
D 14
	return (CURSES_OK);
E 14
I 14
	return (OK);
E 14
E 13
E 11
}
E 1
