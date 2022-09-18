h48263
s 00001/00011/00011
d D 5.4 90/06/01 15:54:47 bostic 4 3
c new copyright notice
e
s 00000/00001/00022
d D 5.3 90/02/15 09:20:08 bostic 3 2
c remove nologin, it's paths.h now
e
s 00003/00002/00020
d D 5.2 89/05/09 13:40:58 bostic 2 1
c add paths.h
e
s 00022/00000/00000
d D 5.1 89/04/02 14:48:55 bostic 1 0
c date and time created 89/04/02 14:48:55 by bostic
e
u
U
f b 
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
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

D 2
#define	_PATH_BSHELL	"/bin/sh"
#define	_PATH_DEFPATH	"PATH=/usr/ucb:/bin:/usr/bin:"
E 2
I 2
#include <paths.h>

#define	_PATH_DEFPATH	"PATH=/bin:/usr/bin:"
E 2
D 3
#define	_PATH_NOLOGIN	"/etc/nologin"
E 3
E 1
