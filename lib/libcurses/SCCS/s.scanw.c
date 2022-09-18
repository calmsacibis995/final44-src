h06423
s 00003/00003/00146
d D 8.3 94/05/04 06:24:56 bostic 20 19
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00009/00009/00140
d D 8.2 93/10/05 09:20:36 bostic 19 18
c use #ifdef __STDC__, it's more correct, and, #if doesn't work on Suns
e
s 00002/00002/00147
d D 8.1 93/06/04 16:49:05 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00148
d D 5.14 93/02/02 13:50:07 elan 17 16
c Fixed inconsistency in function declarations (static vs. global).
e
s 00006/00006/00143
d D 5.13 93/01/11 11:53:59 bostic 16 15
c CURSES_{OK,ERR} -> OK,ERR
e
s 00006/00005/00143
d D 5.12 92/12/30 14:55:08 elan 15 14
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00006/00009/00142
d D 5.11 92/12/30 14:10:18 elan 14 13
c Made _sprintw and _sscans global and public. Changed the names to 
c vwprintw and vwscanw respectively.
e
s 00004/00008/00147
d D 5.10 92/08/31 14:26:06 elan 13 12
c Fixed error in vararg use.
e
s 00067/00004/00088
d D 5.9 92/08/23 14:39:08 bostic 12 11
c fold mv routines in; lint
e
s 00016/00013/00076
d D 5.8 92/08/23 12:11:53 bostic 11 9
c KNF
e
s 00011/00011/00078
d R 5.8 92/05/15 15:22:56 bostic 10 9
c reformat to KNF, redo tracing interface, new version for vi
e
s 00054/00056/00035
d D 5.7 91/04/15 13:03:27 torek 9 8
c use <stdarg.h> or misuse <varargs.h> depending on __STDC__;
e
s 00007/00004/00084
d D 5.6 91/03/12 09:29:27 bostic 8 7
c match the function prototype
e
s 00039/00012/00049
d D 5.5 91/01/21 08:16:25 bostic 7 6
c update for new stdio; from Chris Torek
e
s 00001/00011/00060
d D 5.4 90/06/01 15:40:11 bostic 6 5
c new copyright notice
e
s 00010/00005/00061
d D 5.3 88/06/30 17:22:02 bostic 5 4
c install approved copyright notice
e
s 00010/00004/00056
d D 5.2 88/06/08 13:57:43 bostic 4 3
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00050
d D 5.1 85/06/07 11:41:19 dist 3 2
c Add copyright
e
s 00001/00001/00050
d D 1.2 85/05/01 17:32:32 bloom 2 1
c fix sccs id
e
s 00051/00000/00000
d D 1.1 81/01/26 17:03:11 arnold 1 0
c date and time created 81/01/26 17:03:11 by arnold
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
D 18
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 18
I 18
D 20
 * Copyright (c) 1981, 1993
E 20
I 20
 * Copyright (c) 1981, 1993, 1994
E 20
 *	The Regents of the University of California.  All rights reserved.
E 18
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
D 11
#endif /* not lint */
E 11
I 11
#endif	/* not lint */
E 11
E 4

/*
E 3
D 11
 * scanw and friends
 *
E 11
I 11
 * scanw and friends.
E 11
D 2
 * %G% (Berkeley) %W%
E 2
I 2
D 3
 * %W% (Berkeley) %G%
E 3
E 2
 */

I 11
D 20
#include <curses.h>

E 20
E 11
D 9
# include	"curses.ext"
I 8
# include	"stdarg.h"
E 9
I 9
D 19
#if __STDC__
E 19
I 19
#ifdef __STDC__
E 19
#include <stdarg.h>
#else
#include <varargs.h>
#endif
I 20

#include "curses.h"
E 20
D 11
#include "curses.ext"
E 11
E 9
E 8

I 12
D 13
static int __sscans __P((WINDOW *, const char *, ...));
E 13
I 13
D 14
static int __sscans __P((WINDOW *, const char *, va_list));
E 13

E 14
E 12
/*
D 11
 *	This routine implements a scanf on the standard screen.
E 11
I 11
 * scanw --
 *	Implement a scanf on the standard screen.
E 11
 */
I 12
int
E 12
D 9
scanw(fmt, args)
char	*fmt;
int	args; {
E 9
I 9
D 19
#if __STDC__
E 19
I 19
#ifdef __STDC__
E 19
scanw(const char *fmt, ...)
#else
scanw(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;
E 9

D 9
	return _sscans(stdscr, fmt, &args);
E 9
I 9
D 19
#if __STDC__
E 19
I 19
#ifdef __STDC__
E 19
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 11
	ret = _sscans(stdscr, fmt, ap);
E 11
I 11
D 14
	ret = __sscans(stdscr, fmt, ap);
E 14
I 14
	ret = vwscanw(stdscr, fmt, ap);
E 14
E 11
	va_end(ap);
D 11
	return ret;
E 11
I 11
	return (ret);
E 11
E 9
}
I 7

E 7
/*
D 11
 *	This routine implements a scanf on the given window.
E 11
I 11
 * wscanw --
 *	Implements a scanf on the given window.
E 11
 */
I 12
int
E 12
D 9
wscanw(win, fmt, args)
WINDOW	*win;
char	*fmt;
int	args; {
E 9
I 9
D 19
#if __STDC__
E 19
I 19
#ifdef __STDC__
E 19
wscanw(WINDOW *win, const char *fmt, ...)
#else
wscanw(win, fmt, va_alist)
	WINDOW *win;
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;
E 9

D 9
	return _sscans(win, fmt, &args);
E 9
I 9
D 19
#if __STDC__
E 19
I 19
#ifdef __STDC__
E 19
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 11
	ret = _sscans(win, fmt, ap);
E 11
I 11
D 14
	ret = __sscans(win, fmt, ap);
E 14
I 14
	ret = vwscanw(win, fmt, ap);
E 14
E 11
	va_end(ap);
D 11
	return ret;
E 11
I 11
	return (ret);
E 11
E 9
}
I 7

E 7
/*
I 12
 * mvscanw, mvwscanw -- 
 *	Implement the mvscanw commands.  Due to the variable number of
 *	arguments, they cannot be macros.  Another sigh....
 */
int
D 19
#if __STDC__
E 19
I 19
#ifdef __STDC__
E 19
mvscanw(register int y, register int x, const char *fmt,...)
#else
mvscanw(y, x, fmt, va_alist)
	register int y, x;
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;

D 15
	if (move(y, x) != OK)
		return (ERR);
E 15
I 15
D 16
	if (move(y, x) != CURSES_OK)
		return (CURSES_ERR);
E 16
I 16
	if (move(y, x) != OK)
		return (ERR);
E 16
E 15
D 19
#if __STDC__
E 19
I 19
#ifdef __STDC__
E 19
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 14
	ret = __sscans(stdscr, fmt, ap);
E 14
I 14
	ret = vwscanw(stdscr, fmt, ap);
E 14
	va_end(ap);
	return (ret);
}

int
D 19
#if __STDC__
E 19
I 19
#ifdef __STDC__
E 19
mvwscanw(register WINDOW * win, register int y, register int x,
    const char *fmt, ...)
#else
mvwscanw(win, y, x, fmt, va_alist)
	register WINDOW *win;
	register int y, x;
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
	int ret;

D 15
	if (move(y, x) != OK)
		return (ERR);
E 15
I 15
D 16
	if (move(y, x) != CURSES_OK)
		return (CURSES_ERR);
E 16
I 16
	if (move(y, x) != OK)
		return (ERR);
E 16
E 15
D 19
#if __STDC__
E 19
I 19
#ifdef __STDC__
E 19
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 14
	ret = __sscans(win, fmt, ap);
E 14
I 14
	ret = vwscanw(win, fmt, ap);
E 14
	va_end(ap);
	return (ret);
}

/*
E 12
I 11
D 14
 * __sscans --
E 14
I 14
 * vwscanw --
E 14
E 11
I 7
D 9
 *	Internal routine to read from a string, and its data structure.
 */
struct strinfo {
	char	*addr;		/* address */
	int	len;		/* remaining bytes */
};

static int
_winread(cookie, buf, n)
char	*cookie, *buf;
reg int	n; {

	reg struct strinfo *s = (struct strinfo *)cookie;

	if (n > s->len)
		n = s->len;
	bcopy(s->addr, buf, n);
	s->len -= n;
	s->addr += n;
	return n;
}

/*
E 9
E 7
 *	This routine actually executes the scanf from the window.
D 7
 *
 *	This is really a modified version of "sscanf".  As such,
 * it assumes that sscanf interfaces with the other scanf functions
 * in a certain way.  If this is not how your system works, you
 * will have to modify this routine to use the interface that your
 * "sscanf" uses.
E 7
I 7
D 9
 *	SHOULD IMPLEMENT VSSCANF
E 9
I 9
D 14
 *	THIS SHOULD BE RENAMED vwscanw AND EXPORTED
E 14
E 9
E 7
 */
D 8
_sscans(win, fmt, args)
E 8
I 8
D 9
_sscans(win, fmt)
E 8
WINDOW	*win;
D 8
char	*fmt;
int	*args; {
E 8
I 8
char	*fmt; {
E 8

E 9
I 9
D 11
_sscans(win, fmt, ap)
E 11
I 11
D 12
__sscans(win, fmt, ap)
E 11
	WINDOW *win;
E 12
I 12
D 17
static int
E 17
I 17
int
E 17
E 12
D 13
#if __STDC__
D 12
	const char *fmt;
E 12
I 12
__sscans(WINDOW *win, const char *fmt, ...)
E 12
#else
E 13
I 12
D 14
__sscans(win, fmt, ap)
E 14
I 14
vwscanw(win, fmt, ap)
E 14
	WINDOW *win;
E 12
D 13
	char *fmt;
I 12
	va_dcl;
E 12
#endif
E 9
I 8
D 12
	va_list ap;
E 12
E 8
I 7
D 9
	int	ret;
	FILE	*f;
	struct	strinfo s;
E 7
	char	buf[100];
E 9
I 9
{
E 13
I 13
	const char *fmt;
E 13
I 12
	va_list ap;
I 13
{

E 13
E 12
D 11
	char buf[100];
E 11
I 11
	char buf[1024];
E 11
E 9
D 7
	FILE	junk;
E 7

D 7
	junk._flag = _IOREAD|_IOSTRG;
	junk._base = junk._ptr = buf;
	if (wgetstr(win, buf) == ERR)
E 7
I 7
D 9
	if ((f = fropen((char *)&s, _winread)) == NULL)
E 7
		return ERR;
D 7
	junk._cnt = strlen(buf);
	return _doscan(&junk, fmt, args);
E 7
I 7
	if (wgetstr(win, buf) == ERR) {
		(void) fclose(f);
		return ERR;
	}
	s.addr = buf;
	s.len = strlen(buf);
D 8
	ret = __svfscanf(f, fmt, args);
E 8
I 8
	va_start(ap, fmt);
	ret = __svfscanf(f, fmt, ap);
	va_end(ap);
E 8
	(void) fclose(f);
	return ret;
E 9
I 9
D 11
	return wgetstr(win, buf) == OK ? vsscanf(buf, fmt, ap) : ERR;
E 11
I 11
D 15
	return (wgetstr(win, buf) == OK ? vsscanf(buf, fmt, ap) : ERR);
E 15
I 15
D 16
	return (wgetstr(win, buf) == CURSES_OK ? vsscanf(buf, fmt, ap) : 
						 CURSES_ERR);
E 16
I 16
	return (wgetstr(win, buf) == OK ?
	    vsscanf(buf, fmt, ap) : ERR);
E 16
E 15
E 11
E 9
E 7
}
E 1
