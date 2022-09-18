h23046
s 00002/00002/00018
d D 8.1 93/06/06 14:05:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00017
d D 5.4 92/07/15 13:31:52 bostic 4 3
c put slip down into /etc/sliphome
e
s 00006/00000/00014
d D 5.3 92/07/15 11:40:16 karels 3 2
c check in for Mike K. by TK; guess they're working...
e
s 00002/00000/00012
d D 5.2 91/04/01 08:50:47 bostic 2 1
c needs paths.h
e
s 00012/00000/00000
d D 5.1 90/07/01 14:55:18 bostic 1 0
c date and time created 90/07/01 14:55:18 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 3
#ifndef COMPAT
E 3
I 2
#include <paths.h>
I 3
#else
#define	_PATH_DEVNULL	"/dev/null"
#endif
E 3

E 2
D 4
#define	_PATH_ACCESS	"/etc/slip.hosts"
#define	_PATH_LOGIN	"/etc/slip.login"
#define	_PATH_LOGOUT	"/etc/slip.logout"
E 4
I 4
#define	_PATH_ACCESS	"/etc/sliphome/slip.hosts"
#define	_PATH_LOGIN	"/etc/sliphome/slip.login"
#define	_PATH_LOGOUT	"/etc/sliphome/slip.logout"
E 4
I 3
#define	_PATH_DEBUG	"/tmp/sliplogin.XXXXXX"

E 3
E 1
