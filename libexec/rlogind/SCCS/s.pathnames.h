h55444
s 00002/00002/00010
d D 8.1 93/06/04 18:59:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00011
d D 5.4 90/06/01 15:54:28 bostic 4 3
c new copyright notice
e
s 00002/00000/00020
d D 5.3 90/05/12 15:24:10 bostic 3 2
c needs paths.h
e
s 00001/00001/00019
d D 5.2 89/05/09 13:39:22 bostic 2 1
c mv login
e
s 00020/00000/00000
d D 5.1 89/04/02 14:43:07 bostic 1 0
c date and time created 89/04/02 14:43:07 by bostic
e
u
U
f b 
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

I 3
#include <paths.h>

E 3
D 2
#define	_PATH_LOGIN	"/bin/login"
E 2
I 2
#define	_PATH_LOGIN	"/usr/bin/login"
E 2
E 1
