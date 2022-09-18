h48449
s 00001/00005/00012
d D 8.3 94/01/02 10:41:47 bostic 7 6
c add a way to specify the config file (-C)
e
s 00005/00000/00012
d D 8.2 94/01/02 10:41:26 bostic 6 5
c rewrite man to make the configuration file more flexible
e
s 00002/00002/00010
d D 8.1 93/06/06 15:23:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00011
d D 5.4 90/06/01 16:58:36 bostic 4 3
c new copyright notice
e
s 00000/00000/00022
d D 5.3 90/05/27 15:24:07 bostic 3 2
c new man version, with much more complicated configuration file
e
s 00002/00003/00020
d D 5.2 90/03/11 15:11:13 bostic 2 1
c add -m flag, configurable directory search path (/etc/man.config)
c add man.config man page, redo man(1) man page, now AT&T free.  Change '-'
c option to -c, other minor whacks
e
s 00023/00000/00000
d D 5.1 89/05/11 14:40:55 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

I 6
D 7
#ifdef DEBUG
#define	_PATH_MANCONF	"./man.conf"
#else
E 7
E 6
D 2
#define	_PATH_DEFAULT	"/usr/share/man:/usr/new/man:/usr/local/man"
#define	_PATH_LOCAL	"/usr/local/man"
#define	_PATH_NEW	"/usr/new/man"
E 2
I 2
#define	_PATH_MANCONF	"/etc/man.conf"
I 6
D 7
#endif
E 7
E 6
E 2
#define	_PATH_PAGER	"/usr/bin/more -s"
I 2
D 7
#define	_PATH_WHATIS	"whatis.db"
E 7
I 6
#define	_PATH_TMP	"/tmp/man.XXXXXX"
I 7
#define	_PATH_WHATIS	"whatis.db"
E 7
E 6
E 2
E 1
