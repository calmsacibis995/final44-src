h39255
s 00003/00003/00171
d D 8.3 94/05/04 06:24:52 bostic 21 20
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00008/00008/00166
d D 8.2 93/10/05 09:20:36 bostic 20 19
c use #ifdef __STDC__, it's more correct, and, #if doesn't work on Suns
e
s 00002/00002/00172
d D 8.1 93/06/04 16:48:54 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00173
d D 5.15 93/02/02 13:50:08 elan 18 17
c Fixed inconsistency in function declarations (static vs. global).
e
s 00007/00007/00167
d D 5.14 93/01/11 11:53:56 bostic 17 16
c CURSES_{OK,ERR} -> OK,ERR
e
s 00007/00007/00167
d D 5.13 92/12/30 14:55:06 elan 16 15
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00006/00009/00168
d D 5.12 92/12/30 14:10:15 elan 15 14
c Made _sprintw and _sscans global and public. Changed the names to 
c vwprintw and vwscanw respectively.
e
s 00008/00012/00169
d D 5.11 92/08/31 14:25:40 elan 14 13
c Fixed error in vararg use.
e
s 00068/00006/00113
d D 5.10 92/08/23 14:39:01 bostic 13 12
c fold mv routines in; lint
e
s 00033/00028/00086
d D 5.9 92/08/23 11:45:50 bostic 12 10
c KNF
e
s 00020/00012/00102
d R 5.9 92/05/15 15:20:43 bostic 11 10
c reformat to KNF, redo tracing interface, new version for vi
e
s 00053/00026/00061
d D 5.8 91/04/15 13:03:26 torek 10 9
c use <stdarg.h> or misuse <varargs.h> depending on __STDC__;
e
s 00001/00000/00086
d D 5.7 91/02/09 02:21:07 torek 9 8
c put back missing va_start call
e
s 00054/00012/00032
d D 5.6 91/01/27 11:46:55 torek 8 7
c use new stdio function interface to avoid blowing away the stack
c when asked to print long formats (>= 512 characters)
e
s 00001/00011/00043
d D 5.5 90/06/01 15:39:48 bostic 7 6
c new copyright notice
e
s 00010/00005/00044
d D 5.4 88/06/30 17:21:58 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00039
d D 5.3 88/06/08 13:57:37 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00005/00023/00038
d D 5.2 88/06/08 12:50:18 bostic 4 3
c use vsprintf, instead of rolling our own
e
s 00010/00001/00051
d D 5.1 85/06/07 11:39:50 dist 3 2
c Add copyright
e
s 00001/00001/00051
d D 1.2 85/05/01 17:28:29 bloom 2 1
c fix sccs id
e
s 00052/00000/00000
d D 1.1 81/01/26 17:03:08 arnold 1 0
c date and time created 81/01/26 17:03:08 by arnold
e
u
U
t
T
I 1
/*
I 3
D 5
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 19
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 19
I 19
D 21
 * Copyright (c) 1981, 1993
E 21
I 21
 * Copyright (c) 1981, 1993, 1994
E 21
 *	The Regents of the University of California.  All rights reserved.
E 19
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
D 21
#include <curses.h>

E 21
D 20
#if __STDC__
E 20
I 20
#ifdef __STDC__
E 20
#include <stdarg.h>
#else
#include <varargs.h>
#endif
I 21

#include "curses.h"
E 21

E 12
/*
E 3
D 10
 * printw and friends
E 10
I 10
 * printw and friends.
E 10
 *
I 10
 * These routines make nonportable assumptions about varargs if __STDC__
 * is not in effect.
E 10
D 2
 * %G% (Berkeley) %W%
E 2
I 2
D 3
 * %W% (Berkeley) %G%
E 3
E 2
 */

I 13
D 14
static int __sprintw __P((WINDOW *, const char *, ...));
E 14
I 14
D 15
static int __sprintw __P((WINDOW *, const char *, va_list));
E 15
E 14
E 13
I 8
D 10
# include	<varargs.h>
E 8
# include	"curses.ext"
E 10
I 10
D 12
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "curses.ext"
E 12
I 12
static int __winwrite __P((void *, const char *, int));
E 12
E 10

/*
D 12
 *	This routine implements a printf on the standard screen.
E 12
I 12
 * printw --
 *	Printf on the standard screen.
E 12
 */
I 13
int
E 13
D 8
printw(fmt, args)
char	*fmt;
int	args; {
E 8
I 8
D 10
printw(va_alist)
va_dcl {
E 8

E 10
I 10
D 20
#if __STDC__
E 20
I 20
#ifdef __STDC__
E 20
printw(const char *fmt, ...)
#else
printw(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
{
E 10
D 4
	return _sprintw(stdscr, fmt, &args);
E 4
I 4
D 8
	char	buf[512];
E 8
I 8
D 12
	va_list	ap;
	int	ret;
E 12
I 12
	va_list ap;
	int ret;
E 12
E 8

I 10
D 20
#if __STDC__
E 20
I 20
#ifdef __STDC__
E 20
	va_start(ap, fmt);
#else
E 10
D 8
	(void) vsprintf(buf, fmt, &args);
	return waddstr(stdscr, buf);
E 8
I 8
	va_start(ap);
D 10
	ret = _sprintw(stdscr, ap);
E 10
I 10
#endif
D 13
	ret = _sprintw(stdscr, fmt, ap);
E 13
I 13
D 15
	ret = __sprintw(stdscr, fmt, ap);
E 15
I 15
	ret = vwprintw(stdscr, fmt, ap);
E 15
E 13
E 10
	va_end(ap);
	return (ret);
E 8
E 4
}

/*
D 12
 *	This routine implements a printf on the given window.
E 12
I 12
 * wprintw --
 *	Printf on the given window.
E 12
 */
I 13
int
E 13
D 8
wprintw(win, fmt, args)
E 8
I 8
D 10
wprintw(va_alist)
va_dcl {

E 10
I 10
D 20
#if __STDC__
E 20
I 20
#ifdef __STDC__
E 20
D 12
wprintw(WINDOW *win, const char *fmt, ...)
E 12
I 12
wprintw(WINDOW * win, const char *fmt, ...)
E 12
#else
wprintw(win, fmt, va_alist)
	WINDOW *win;
	char *fmt;
	va_dcl
#endif
{
E 10
D 12
	va_list	ap;
D 10
	WINDOW	*win;
E 10
	int	ret;
E 12
I 12
	va_list ap;
	int ret;
E 12

I 10
#ifdef __STDC__
	va_start(ap, fmt);
#else
E 10
I 9
	va_start(ap);
E 9
D 10
	win = va_arg(ap, WINDOW *);
	ret = _sprintw(win, ap);
E 10
I 10
#endif
D 13
	ret = _sprintw(win, fmt, ap);
E 13
I 13
D 15
	ret = __sprintw(win, fmt, ap);
E 15
I 15
	ret = vwprintw(win, fmt, ap);
E 15
E 13
E 10
	va_end(ap);
	return (ret);
}

/*
I 13
 * mvprintw, mvwprintw --
 *	Implement the mvprintw commands.  Due to the variable number of
 *	arguments, they cannot be macros.  Sigh....
 */
int
D 20
#if __STDC__
E 20
I 20
#ifdef __STDC__
E 20
mvprintw(register int y, register int x, const char *fmt, ...)
#else
mvprintw(y, x, fmt, va_alist)
	register int y, x;
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;

D 14
	if (move(y, x) != OK)
		return (ERR);
E 14
D 20
#if __STDC__
E 20
I 20
#ifdef __STDC__
E 20
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
I 14
D 16
	if (move(y, x) != OK)
		return (ERR);
E 16
I 16
D 17
	if (move(y, x) != CURSES_OK)
		return (CURSES_ERR);
E 17
I 17
	if (move(y, x) != OK)
		return (ERR);
E 17
E 16
E 14
D 15
	ret = __sprintw(stdscr, fmt, ap);
E 15
I 15
	ret = vwprintw(stdscr, fmt, ap);
E 15
	va_end(ap);
	return (ret);
}

int
D 20
#if __STDC__
E 20
I 20
#ifdef __STDC__
E 20
mvwprintw(register WINDOW * win, register int y, register int x,
    const char *fmt, ...)
#else
mvwprintw(win, y, x, fmt, va_alist)
	register WINDOW *win;
	register int y, x;
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;

D 14
	if (wmove(win, y, x) != OK)
		return (ERR);
E 14
D 20
#if __STDC__
E 20
I 20
#ifdef __STDC__
E 20
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
I 14
D 16
	if (wmove(win, y, x) != OK)
		return (ERR);
E 16
I 16
D 17
	if (wmove(win, y, x) != CURSES_OK)
		return (CURSES_ERR);
E 17
I 17
	if (wmove(win, y, x) != OK)
		return (ERR);
E 17
E 16

E 14
D 15
	ret = __sprintw(win, fmt, ap);
E 15
I 15
	ret = vwprintw(win, fmt, ap);
E 15
	va_end(ap);
	return (ret);
}

/*
E 13
D 12
 *	Internal write-buffer-to-window function.
E 12
I 12
 * Internal write-buffer-to-window function.
E 12
 */
static int
D 12
_winwrite(cookie, buf, n)
E 12
I 12
__winwrite(cookie, buf, n)
E 12
D 10
void	*cookie;
reg char *buf;
int	n; {
E 10
I 10
	void *cookie;
D 12
	register char *buf;
E 12
I 12
	register const char *buf;
E 12
	int n;
{
D 12
	register WINDOW *win = (WINDOW *)cookie;
	register int c = n;
E 12
I 12
	register WINDOW *win;
	register int c;
E 12
E 10

D 10
	reg WINDOW *win = (WINDOW *)cookie;
	reg int c = n;

E 10
D 12
	while (--c >= 0) {
E 12
I 12
	for (c = n, win = cookie; --c >= 0;)
E 12
D 16
		if (waddch(win, *buf++) == ERR)
E 16
I 16
D 17
		if (waddch(win, *buf++) == CURSES_ERR)
E 17
I 17
		if (waddch(win, *buf++) == ERR)
E 17
E 16
			return (-1);
D 12
	}
	return n;
E 12
I 12
	return (n);
E 12
}

/*
I 12
D 15
 * __sprintw --
E 15
I 15
 * vwprintw --
E 15
E 12
 *	This routine actually executes the printf and adds it to the window.
D 15
 *	It must not be declared static as it is used in mvprintw.c.
I 10
 *	THIS SHOULD BE RENAMED vwprintw AND EXPORTED
E 15
E 10
 */
D 10
_sprintw(win, ap)
E 8
WINDOW	*win;
D 8
char	*fmt;
int	args; {
E 8
I 8
va_list	ap; {
E 10
I 10
D 12
_sprintw(win, fmt, ap)
E 12
I 12
D 13
__sprintw(win, fmt, ap)
E 12
	WINDOW *win;
E 13
I 13
D 18
static int
E 18
I 18
int
E 18
E 13
D 14
#if __STDC__
D 13
	const char *fmt;
E 13
I 13
__sprintw(WINDOW *win, const char *fmt, ...)
E 13
#else
E 14
I 13
D 15
__sprintw(win, fmt, ap)
E 15
I 15
vwprintw(win, fmt, ap)
E 15
	WINDOW *win;
E 13
D 14
	char *fmt;
I 13
	va_dcl;
E 13
#endif
D 12
	va_list	ap;
E 12
I 12
D 13
	va_list ap;
E 13
E 12
{
E 14
I 14
	const char *fmt;
E 14
I 13
	va_list ap;
I 14
{
E 14
E 13
	FILE *f;
E 10
E 8

D 4
	return _sprintw(win, fmt, &args);
}
/*
 *	This routine actually executes the printf and adds it to the window
 *
 *	This is really a modified version of "sprintf".  As such,
 * it assumes that sprintf interfaces with the other printf functions
 * in a certain way.  If this is not how your system works, you
 * will have to modify this routine to use the interface that your
 * "sprintf" uses.
 */
_sprintw(win, fmt, args)
WINDOW	*win;
char	*fmt;
int	*args; {

	FILE	junk;
E 4
D 8
	char	buf[512];
E 8
I 8
D 10
	FILE	*f;
	char	*fmt;
E 8

E 10
D 4
	junk._flag = _IOWRT + _IOSTRG;
	junk._ptr = buf;
	junk._cnt = 32767;
	_doprnt(fmt, args, &junk);
	putc('\0', &junk);
E 4
I 4
D 8
	(void) vsprintf(buf, fmt, &args);
E 4
	return waddstr(win, buf);
E 8
I 8
D 12
	if ((f = fwopen((void *)win, _winwrite)) == NULL)
		return ERR;
D 10
	fmt = va_arg(ap, char *);
E 10
	(void) vfprintf(f, fmt, ap);
	return fclose(f) ? ERR : OK;
E 12
I 12
	if ((f = funopen(win, NULL, __winwrite, NULL, NULL)) == NULL)
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
	(void)vfprintf(f, fmt, ap);
D 16
	return (fclose(f) ? ERR : OK);
E 16
I 16
D 17
	return (fclose(f) ? CURSES_ERR : CURSES_OK);
E 17
I 17
	return (fclose(f) ? ERR : OK);
E 17
E 16
E 12
E 8
}
E 1
