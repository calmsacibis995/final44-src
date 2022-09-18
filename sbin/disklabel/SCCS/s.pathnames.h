h56771
s 00002/00002/00012
d D 8.1 93/06/05 10:50:57 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00013
d D 5.3 90/06/01 16:14:54 bostic 3 2
c new copyright notice
e
s 00004/00001/00020
d D 5.2 89/05/11 13:51:52 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00021/00000/00000
d D 5.1 89/04/02 12:20:09 bostic 1 0
c date and time created 89/04/02 12:20:09 by bostic
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

I 2
#include <paths.h>

E 2
#define	_PATH_BOOTDIR	"/usr/mdec"
D 2
#define	_PATH_EDITOR	"/usr/ucb/vi"
E 2
I 2
#undef _PATH_TMP
#define	_PATH_TMP	"/tmp/EdDk.aXXXXXX"
E 2
E 1
