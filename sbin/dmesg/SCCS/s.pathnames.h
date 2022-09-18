h48287
s 00001/00011/00011
d D 5.4 90/06/01 16:15:01 bostic 4 3
c new copyright notice
e
s 00001/00001/00021
d D 5.3 89/07/06 16:32:11 bostic 3 2
c /usr/adm -> /var/log; VMUNIX -> UNIX
e
s 00002/00002/00020
d D 5.2 89/05/11 14:07:24 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00022/00000/00000
d D 5.1 89/04/02 12:22:14 bostic 1 0
c date and time created 89/04/02 12:22:14 by bostic
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

I 2
#include <paths.h>

E 2
D 3
#define	_PATH_MSGBUF	"/usr/adm/msgbuf"
E 3
I 3
#define	_PATH_MSGBUF	"/var/log/msgbuf"
E 3
D 2
#define	_PATH_KMEM	"/dev/kmem"
#define	_PATH_VMUNIX	"/vmunix"
E 2
E 1
