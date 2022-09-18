h33827
s 00003/00002/00033
d D 8.2 94/05/04 06:24:29 bostic 4 3
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00033
d D 8.1 93/06/04 16:47:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00030
d D 5.2 93/02/14 11:12:44 bostic 2 1
c don't do a strlen() if length is provided
e
s 00034/00000/00000
d D 5.1 93/02/14 11:06:16 bostic 1 0
c date and time created 93/02/14 11:06:16 by bostic
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1993 Regents of the University of California.
 * All rights reserved.
E 3
I 3
D 4
 * Copyright (c) 1993
E 4
I 4
 * Copyright (c) 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif	/* not lint */

D 4
#include <curses.h>
E 4
#include <string.h>
I 4

#include "curses.h"
E 4

/*
 * waddnstr --
 *	Add a string (at most n characters) to the given window
 *	starting at (_cury, _curx).  If n is negative, add the
 *	entire string.
 */
int
waddnstr(win, s, n)
	WINDOW *win;
	const char *s;
	int n;
{
	size_t len;
I 2
	const char *p;
E 2

D 2
	len = strlen(s);

	if (n > 0 && n < len)
		len = n;
E 2
I 2
	if (n > 0)
		for (p = s, len = 0; n-- && *p++; ++len);
	else
		len = strlen(s);
E 2
	return (waddbytes(win, s, len));
}
E 1
