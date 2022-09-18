h44658
s 00004/00007/00009
d D 5.3 91/04/19 15:49:01 bostic 3 2
c remove last vestiges of AT&T code; fix for ANSI; Berkeley copyright
e
s 00001/00011/00015
d D 5.2 90/06/01 19:04:47 bostic 2 1
c new copyright notice
e
s 00026/00000/00000
d D 5.1 89/05/11 14:40:32 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
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
char *fillst[] = {
	"/bin",
	"/usr",
	"/usr/bin",
	"/usr/lib",
	NULL,
};
E 3
I 3
#define	_PATH_BIN	"/bin"
#define	_PATH_USR	"/usr"
#define	_PATH_USRBIN	"/usr/bin"
#define	_PATH_USRLIB	"/usr/lib"
E 3
E 1
