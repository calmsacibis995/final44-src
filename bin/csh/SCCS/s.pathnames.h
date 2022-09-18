h54847
s 00002/00002/00013
d D 8.1 93/05/31 16:42:40 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00015
d D 5.8 93/05/22 19:06:45 christos 8 7
c Fixed gcc -Wall warnings
e
s 00000/00000/00015
d D 5.7 91/07/19 17:31:17 christos 7 6
c stdio based version; brace glob fix; builtin prototypes
e
s 00000/00001/00015
d D 5.6 91/06/08 12:20:31 bostic 6 5
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00001/00011/00015
d D 5.5 90/05/31 20:29:00 bostic 5 4
c new copyright notice
e
s 00002/00006/00024
d D 5.4 89/05/09 14:14:38 bostic 4 3
c add paths.h
e
s 00004/00000/00026
d D 5.3 89/04/02 11:57:55 bostic 3 2
c rest of pathnames
e
s 00003/00000/00023
d D 5.2 89/03/05 22:01:17 bostic 2 1
c add search path names
e
s 00023/00000/00000
d D 5.1 89/03/05 21:24:00 bostic 1 0
c date and time created 89/03/05 21:24:00 by bostic
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 5
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */
I 4
D 6
#include <paths.h>
E 6
E 4

I 2
#define	_PATH_BIN		"/bin"
I 3
D 4
#define	_PATH_BSHELL		"/bin/sh"
#define	_PATH_CSHELL		"/bin/csh"
#define	_PATH_DEVNULL		"/dev/null"
E 4
E 3
E 2
#define	_PATH_DOTCSHRC		"/etc/csh.cshrc"
#define	_PATH_DOTLOGIN		"/etc/csh.login"
#define	_PATH_DOTLOGOUT		"/etc/csh.logout"
I 3
D 4
#define	_PATH_LOGIN		"/bin/login"
E 3
#define	_PATH_LOGIN		"/bin/login"
I 2
#define	_PATH_UCB		"/usr/ucb"
E 4
I 4
#define	_PATH_LOGIN		"/usr/bin/login"
E 4
#define	_PATH_USRBIN		"/usr/bin"
E 2
E 1
