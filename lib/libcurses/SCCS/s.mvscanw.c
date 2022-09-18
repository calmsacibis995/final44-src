h35545
s 00017/00015/00056
d D 5.6 92/08/23 11:22:09 bostic 10 8
c KNF
e
s 00014/00011/00060
d R 5.6 92/05/15 15:19:03 bostic 9 8
c reformat to KNF, redo tracing interface, new version for vi
e
s 00049/00013/00022
d D 5.5 91/04/15 13:03:29 torek 8 7
c use <stdarg.h> or misuse <varargs.h> depending on __STDC__;
e
s 00001/00011/00034
d D 5.4 90/06/01 15:39:23 bostic 7 6
c new copyright notice
e
s 00010/00005/00035
d D 5.3 88/06/30 17:21:50 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00030
d D 5.2 88/06/08 13:57:28 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00024
d D 5.1 85/06/07 11:36:45 dist 4 3
c Add copyright
e
s 00001/00001/00024
d D 1.3 85/05/01 17:24:18 bloom 3 2
c fix sccs id
e
s 00002/00002/00023
d D 1.2 83/05/17 11:27:02 arnold 2 1
c the function name is _sscans(), not _sscanw().
e
s 00025/00000/00000
d D 1.1 81/01/26 17:03:02 arnold 1 0
c date and time created 81/01/26 17:03:02 by arnold
e
u
U
t
T
I 4
/*
D 5
 * Copyright (c) 1980 Regents of the University of California.
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
D 10
#endif /* not lint */
E 10
I 10
#endif	/* not lint */
E 10
E 5

I 10
#include <curses.h>

E 10
E 4
I 1
D 8
# include	"curses.ext"
E 8
I 8
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
D 10
#include "curses.ext"
E 10
E 8

/*
D 10
 * implement the mvscanw commands.  Due to the variable number of
 * arguments, they cannot be macros.  Another sigh....
E 10
I 10
 * mvscanw, mvwscanw -- 
 *	Implement the mvscanw commands.  Due to the variable number of
 *	arguments, they cannot be macros.  Another sigh....
E 10
D 8
 *
E 8
D 3
 * %G% (Berkeley) %W%
E 3
I 3
D 4
 * %W% (Berkeley) %G%
E 4
E 3
 */
D 10

E 10
D 8
mvscanw(y, x, fmt, args)
reg int		y, x;
char		*fmt;
int		args; {
E 8
I 8
#if __STDC__
D 10
mvscanw(reg int y, reg int x, const char *fmt, ...)
E 10
I 10
mvscanw(register int y, register int x, const char *fmt,...)
E 10
#else
mvscanw(y, x, fmt, va_alist)
D 10
	reg int y, x;
E 10
I 10
	register int y, x;
E 10
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;
E 8

D 2
	return move(y, x) == OK ? _sscanw(stdscr, fmt, &args) : ERR;
E 2
I 2
D 8
	return move(y, x) == OK ? _sscans(stdscr, fmt, &args) : ERR;
E 8
I 8
	if (move(y, x) != OK)
D 10
		return ERR;
E 10
I 10
		return (ERR);
E 10
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 10
	ret = _sscans(stdscr, fmt, ap);
E 10
I 10
	ret = __sscans(stdscr, fmt, ap);
E 10
	va_end(ap);
D 10
	return ret;
E 10
I 10
	return (ret);
E 10
E 8
E 2
}

D 8
mvwscanw(win, y, x, fmt, args)
reg WINDOW	*win;
reg int		y, x;
char		*fmt;
int		args; {
E 8
I 8
#if __STDC__
D 10
mvwscanw(reg WINDOW *win, reg int y, reg int x, const char *fmt, ...)
E 10
I 10
mvwscanw(register WINDOW * win, register int y, register int x,
    const char *fmt, ...)
E 10
#else
mvwscanw(win, y, x, fmt, va_alist)
D 10
	reg WINDOW *win;
	reg int y, x;
E 10
I 10
	register WINDOW *win;
	register int y, x;
E 10
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;
E 8

D 2
	return wmove(win, y, x) == OK ? _sscanw(win, fmt, &args) : ERR;
E 2
I 2
D 8
	return wmove(win, y, x) == OK ? _sscans(win, fmt, &args) : ERR;
E 8
I 8
	if (move(y, x) != OK)
D 10
		return ERR;
E 10
I 10
		return (ERR);
E 10
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	ret = _sscans(win, fmt, ap);
	va_end(ap);
D 10
	return ret;
E 10
I 10
	return (ret);
E 10
E 8
E 2
}
E 1
