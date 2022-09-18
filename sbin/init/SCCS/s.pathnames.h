h42032
s 00002/00002/00014
d D 8.1 93/06/05 11:00:34 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00015
d D 6.2 93/05/26 10:16:29 bostic 6 4
c update Donn's organization for general release
e
s 00001/00000/00016
d R 6.2 92/03/02 15:41:54 bostic 5 4
c don't permit multiple invocations
e
s 00007/00004/00009
d D 6.1 91/07/02 18:21:59 mckusick 4 3
c initial rewritten version from Donn Seeley
e
s 00001/00011/00012
d D 5.3 90/06/01 16:17:42 bostic 3 2
c new copyright notice
e
s 00002/00002/00021
d D 5.2 89/05/11 13:54:00 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00023/00000/00000
d D 5.1 89/04/02 14:17:05 bostic 1 0
c date and time created 89/04/02 14:17:05 by bostic
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 4
I 4
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
E 4
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
I 4
 * This code is derived from software contributed to Berkeley by
D 6
 * Donn Seeley at UUNET Technologies, Inc.
E 6
I 6
 * Donn Seeley at Berkeley Software Design, Inc.
E 6
 *
E 4
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 2
#define	_PATH_BSHELL	"/bin/sh"
#define	_PATH_CONSOLE	"/dev/console"
E 2
I 2
#include <paths.h>

E 2
D 4
#define	_PATH_RC	"/etc/rc"
#define	_PATH_RCDOWN	"/etc/rc.shutdown"
E 4
I 4
#define	_PATH_SLOGGER	"/sbin/session_logger"
#define	_PATH_RUNCOM	"/etc/rc"
E 4
E 1
