h40266
s 00001/00011/00011
d D 5.3 90/06/01 15:53:59 bostic 3 2
c new copyright notice
e
s 00003/00002/00019
d D 5.2 89/05/11 14:33:17 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00021/00000/00000
d D 5.1 89/04/02 14:40:22 bostic 1 0
c date and time created 89/04/02 14:40:22 by bostic
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
#define	_PATH_DEFPATH	"PATH=:/usr/ucb:/bin:/usr/bin"
E 2
I 2
#include <paths.h>

#define	_PATH_DEFPATH	"PATH=:/bin:/usr/bin"
E 2
E 1
