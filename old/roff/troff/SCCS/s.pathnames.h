h37078
s 00001/00001/00009
d D 5.3 91/04/30 14:34:58 bostic 3 2
c move troff_font into /usr/old
e
s 00002/00012/00008
d D 5.2 91/04/18 17:55:04 bostic 2 1
c | sed '/ATT (NEW)/d'
e
s 00020/00000/00000
d D 5.1 89/05/11 14:41:25 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
D 2
/*
E 2
I 2
/*-
E 2
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
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

D 3
#define	_PATH_FONTS	"/usr/libdata/troff_font/ftXX"
E 3
I 3
#define	_PATH_FONTS	"/usr/old/libdata/troff_font/ftXX"
E 3
E 1
