h03803
s 00001/00001/00027
d D 5.8 93/02/12 09:38:34 bostic 11 10
c make addstr call declare const char *
e
s 00002/00000/00026
d D 5.7 92/08/23 14:38:17 bostic 10 9
c lint
e
s 00011/00011/00015
d D 5.6 92/08/23 09:59:52 bostic 9 7
c KNF
e
s 00010/00009/00017
d R 5.6 92/05/15 14:15:52 bostic 8 7
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00025
d D 5.5 90/06/01 15:37:19 bostic 7 6
c new copyright notice
e
s 00010/00005/00026
d D 5.4 88/06/30 17:21:12 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00021
d D 5.3 88/06/08 13:56:43 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00002/00005/00023
d D 5.2 87/06/24 14:17:14 minshall 4 3
c Add 'addbytes.c', plus some cleanup by K. Bostic in Makefile.
e
s 00010/00001/00018
d D 5.1 85/06/07 11:25:00 dist 3 2
c Add copyright
e
s 00001/00001/00018
d D 1.2 85/05/01 16:34:37 bloom 2 1
c fix sccs ids
e
s 00019/00000/00000
d D 1.1 81/01/26 17:02:35 arnold 1 0
c date and time created 81/01/26 17:02:35 by arnold
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
E 4
I 4
D 5
 * Copyright (c) 1980-1987 Regents of the University of California.
E 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
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

E 3
I 1
D 9
# include	"curses.ext"
E 9
I 9
#include <curses.h>
I 10
#include <string.h>
E 10
E 9

/*
D 9
 *	This routine adds a string starting at (_cury,_curx)
 *
E 9
I 9
 * waddstr --
 *	Add a string to the given window starting at (_cury, _curx).
E 9
D 2
 * %G% (Berkeley) %W%
E 2
I 2
D 3
 * %W% (Berkeley) %G%
E 3
E 2
 */
I 10
int
E 10
D 9
waddstr(win,str)
reg WINDOW	*win; 
reg char	*str;
E 9
I 9
waddstr(win, str)
	WINDOW *win;
D 11
	char *str;
E 11
I 11
	const char *str;
E 11
E 9
{
D 9
# ifdef DEBUG
	fprintf(outf, "WADDSTR(\"%s\")\n", str);
# endif
D 4
	while (*str)
		if (waddch(win, *str++) == ERR)
			return ERR;
	return OK;
E 4
I 4
	return waddbytes(win, str, strlen(str));
E 9
I 9
#ifdef DEBUG
	__TRACE("waddstr: (\"%s\")\n", str);
#endif
	return (waddbytes(win, str, strlen(str)));
E 9
E 4
}
E 1
