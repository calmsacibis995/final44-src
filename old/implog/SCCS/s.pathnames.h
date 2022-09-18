h49085
s 00001/00011/00009
d D 5.5 90/06/01 18:41:05 bostic 5 4
c new copyright notice
e
s 00000/00002/00020
d D 5.4 90/04/28 12:54:02 bostic 4 3
c don't need paths.h anymore
e
s 00001/00001/00021
d D 5.3 89/05/19 17:09:49 bostic 3 2
c mv from /usr/adm to /var/log
e
s 00002/00000/00020
d D 5.2 89/05/11 14:07:51 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00020/00000/00000
d D 5.1 89/04/02 13:05:16 bostic 1 0
c date and time created 89/04/02 13:05:16 by bostic
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
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

I 2
D 4
#include <paths.h>

E 4
E 2
D 3
#define	_PATH_IMPLOG	"/usr/adm/implog"
E 3
I 3
#define	_PATH_IMPLOG	"/var/log/implog"
E 3
E 1
