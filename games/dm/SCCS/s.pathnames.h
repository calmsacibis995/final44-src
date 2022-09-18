h03984
s 00002/00002/00011
d D 8.1 93/05/31 16:52:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00010
d D 5.3 90/06/26 10:33:03 bostic 3 2
c cleanup, make documentation match program, move config files into /etc
e
s 00001/00011/00012
d D 5.2 90/06/01 13:05:39 bostic 2 1
c new copyright notice
e
s 00023/00000/00000
d D 5.1 89/05/11 14:40:29 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

I 3
#define	_PATH_CONFIG	"/etc/dm.conf"
E 3
#define	_PATH_HIDE	"/usr/games/hide/"
D 3
#define	_PATH_CONFIG	"/etc/dm.config"
#define	_PATH_NOGAMES	"/usr/games/nogames"
#define	_PATH_LOG	"/var/log/dm.log"
E 3
I 3
#define	_PATH_LOG	"/var/log/games.log"
#define	_PATH_NOGAMES	"/etc/nogames"
E 3
E 1
