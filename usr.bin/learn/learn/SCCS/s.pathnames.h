h55133
s 00002/00002/00012
d D 8.1 93/06/06 14:56:48 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00012
d D 5.3 91/04/17 18:00:39 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00001/00024
d D 5.2 91/03/01 14:33:08 bostic 2 1
c ANSI
e
s 00025/00000/00000
d D 5.1 89/05/11 14:40:53 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
D 3
/*
E 3
I 3
/*-
E 3
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
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

#include <paths.h>

D 2
#define	_PATH_DEFPATH	"PATH=%s/bin:"
E 2
#define	_PATH_LEARN	"/usr/libdata/learn"
#define	_PATH_RM	"/bin/rm"
#define	_PATH_STTY	"/bin/stty"
E 1
