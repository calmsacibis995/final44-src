h37807
s 00001/00001/00020
d D 5.5 92/07/20 21:07:23 bostic 5 4
c update paths, Ind* now installed in /usr/old
e
s 00004/00004/00017
d D 5.4 91/10/26 13:20:38 cael 4 3
c modify exec'd pathnames to reflect move to /usr/old
e
s 00002/00012/00019
d D 5.3 91/04/18 16:44:07 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00002/00029
d D 5.2 90/06/19 17:37:44 bostic 2 1
c change paths on Ind files, eign was in the wrong place
e
s 00031/00000/00000
d D 5.1 89/05/11 14:40:59 bostic 1 0
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
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
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

#define	_PATH_ALL	"/usr/dict/lookall/All"
D 2
#define	_PATH_EIGN	"/usr/lib/eign"
E 2
I 2
D 4
#define	_PATH_EIGN	"/usr/share/dict/eign"
E 2
#define	_PATH_HUNT	"/usr/libexec/hunt"
E 4
I 4
#define	_PATH_EIGN	"/usr/dict/eign"
#define	_PATH_HUNT	"/usr/old/libexec/hunt"
E 4
D 2
#define	_PATH_IND	"/usr/share/dict/papers/Ind"
E 2
I 2
D 5
#define	_PATH_IND	"/var/db/Ind"
E 5
I 5
#define	_PATH_IND	"/usr/old/dict/papers/Ind"
E 5
E 2
D 4
#define	_PATH_LIB	"/usr/libexec"
#define	_PATH_MKEY	"/usr/libexec/mkey"
E 4
I 4
#define	_PATH_LIB	"/usr/old/libexec"
#define	_PATH_MKEY	"/usr/old/libexec/mkey"
E 4
#define	_PATH_PWD	"/bin/pwd"
#define	_PATH_SORT	"/usr/bin/sort"
#define	_PATH_TMPS	"/tmp/SbibXXXXXX"
#define	_PATH_USRTMP	"/usr/tmp"
E 1
