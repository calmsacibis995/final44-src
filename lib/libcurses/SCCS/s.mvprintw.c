h22768
s 00004/00004/00070
d D 5.12 93/01/11 11:53:53 bostic 15 14
c CURSES_{OK,ERR} -> OK,ERR
e
s 00004/00004/00070
d D 5.11 92/12/30 14:55:07 elan 14 13
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00002/00002/00072
d D 5.10 92/12/30 14:10:16 elan 13 12
c Made _sprintw and _sscans global and public. Changed the names to 
c vwprintw and vwscanw respectively.
e
s 00017/00014/00057
d D 5.9 92/08/23 11:19:14 bostic 12 10
c KNF
e
s 00014/00011/00060
d R 5.9 92/05/15 15:25:21 bostic 11 10
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00001/00070
d D 5.8 91/06/19 10:27:58 marc 10 9
c missing "fmt" in call to _sprintw()
e
s 00043/00029/00028
d D 5.7 91/04/15 13:03:28 torek 9 8
c use <stdarg.h> or misuse <varargs.h> depending on __STDC__;
e
s 00030/00018/00027
d D 5.6 91/01/27 11:46:53 torek 8 7
c use new stdio function interface to avoid blowing away the stack
c when asked to print long formats (>= 512 characters)
e
s 00001/00011/00044
d D 5.5 90/06/01 15:39:20 bostic 7 6
c new copyright notice
e
s 00010/00005/00045
d D 5.4 88/06/30 17:21:49 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00040
d D 5.3 88/06/08 13:57:26 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00012/00002/00032
d D 5.2 88/06/08 12:50:17 bostic 4 3
c use vsprintf, instead of rolling our own
e
s 00010/00001/00024
d D 5.1 85/06/07 11:36:20 dist 3 2
c Add copyright
e
s 00001/00001/00024
d D 1.2 85/05/01 17:24:04 bloom 2 1
c fix sccs id
e
s 00025/00000/00000
d D 1.1 81/01/26 17:03:01 arnold 1 0
c date and time created 81/01/26 17:03:01 by arnold
e
u
U
t
T
I 3
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
D 12
#endif /* not lint */
E 12
I 12
#endif	/* not lint */
E 12
E 5

I 12
#include <curses.h>

E 12
I 8
D 9
# include	<varargs.h>
E 8
E 3
I 1
# include	"curses.ext"
E 9
I 9
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
D 12
#include "curses.ext"
E 12
E 9

/*
D 12
 * implement the mvprintw commands.  Due to the variable number of
 * arguments, they cannot be macros.  Sigh....
E 12
I 12
 * mvprintw, mvwprintw --
 *	Implement the mvprintw commands.  Due to the variable number of
 *	arguments, they cannot be macros.  Sigh....
E 12
D 9
 *
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

D 8
mvprintw(y, x, fmt, args)
reg int		y, x;
char		*fmt;
int		args; {
E 8
I 8
D 9
mvprintw(va_alist)
va_dcl {
E 9
I 9
#if __STDC__
D 12
mvprintw(reg int y, reg int x, const char *fmt, ...)
E 12
I 12
mvprintw(register int y, register int x, const char *fmt, ...)
E 12
#else
mvprintw(y, x, fmt, va_alist)
D 12
	reg int y, x;
E 12
I 12
	register int y, x;
E 12
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;
E 9
E 8

D 4
	return move(y, x) == OK ? _sprintw(stdscr, fmt, &args) : ERR;
E 4
I 4
D 8
	char	buf[512];
E 8
I 8
D 9
	va_list	ap;
	reg int	y, x;
	int	ret;
E 8

I 8
	va_start(ap);
	y = va_arg(ap, int);
	x = va_arg(ap, int);
E 9
E 8
D 14
	if (move(y, x) != OK)
D 8
		return ERR;
	(void) vsprintf(buf, fmt, &args);
	return waddstr(stdscr, buf);
E 8
I 8
D 9
		ret = ERR;
	else
		ret = _sprintw(stdscr, ap);
E 9
I 9
D 12
		return ERR;
E 12
I 12
		return (ERR);
E 14
I 14
D 15
	if (move(y, x) != CURSES_OK)
		return (CURSES_ERR);
E 15
I 15
	if (move(y, x) != OK)
		return (ERR);
E 15
E 14
E 12
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 12
	ret = _sprintw(stdscr, fmt, ap);
E 12
I 12
D 13
	ret = __sprintw(stdscr, fmt, ap);
E 13
I 13
	ret = vwprintw(stdscr, fmt, ap);
E 13
E 12
E 9
	va_end(ap);
D 12
	return ret;
E 12
I 12
	return (ret);
E 12
E 8
E 4
}

D 8
mvwprintw(win, y, x, fmt, args)
reg WINDOW	*win;
reg int		y, x;
char		*fmt;
int		args; {
E 8
I 8
D 9
mvwprintw(va_alist)
va_dcl {
E 9
I 9
#if __STDC__
D 12
mvwprintw(reg WINDOW *win, reg int y, reg int x, const char *fmt, ...)
E 12
I 12
mvwprintw(register WINDOW * win, register int y, register int x,
    const char *fmt, ...)
E 12
#else
mvwprintw(win, y, x, fmt, va_alist)
D 12
	reg WINDOW *win;
	reg int y, x;
E 12
I 12
	register WINDOW *win;
	register int y, x;
E 12
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;
E 9
E 8

D 4
	return wmove(win, y, x) == OK ? _sprintw(win, fmt, &args) : ERR;
E 4
I 4
D 8
	char	buf[512];
E 8
I 8
D 9
	va_list		ap;
	reg WINDOW	*win;
	reg int		y, x;
	int		ret;
E 8

D 8
	if (move(y, x) != OK)
		return ERR;
	(void) vsprintf(buf, fmt, &args);
	return waddstr(win, buf);
E 8
I 8
	va_start(ap);
	win = va_arg(ap, WINDOW *);
	y = va_arg(ap, int);
	x = va_arg(ap, int);
E 9
D 14
	if (wmove(win, y, x) != OK)
D 9
		ret = ERR;
	else
		ret = _sprintw(win, ap);
E 9
I 9
D 12
		return ERR;
E 12
I 12
		return (ERR);
E 14
I 14
D 15
	if (wmove(win, y, x) != CURSES_OK)
		return (CURSES_ERR);
E 15
I 15
	if (wmove(win, y, x) != OK)
		return (ERR);
E 15
E 14
E 12
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 10
	ret = _sprintw(win, ap);
E 10
I 10
D 13
	ret = _sprintw(win, fmt, ap);
E 13
I 13
	ret = vwprintw(win, fmt, ap);
E 13
E 10
E 9
	va_end(ap);
D 12
	return ret;
E 12
I 12
	return (ret);
E 12
E 8
E 4
}
E 1
