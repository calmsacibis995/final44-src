h63648
s 00001/00004/00009
d D 5.4 91/02/08 10:48:55 bostic 4 3
c psdatabase and vmcore no longer used; add dev.db
e
s 00001/00011/00012
d D 5.3 90/05/31 20:36:00 bostic 3 2
c new copyright notice
e
s 00003/00006/00020
d D 5.2 89/05/10 22:15:04 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00026/00000/00000
d D 5.1 89/03/05 21:45:30 bostic 1 0
c date and time created 89/03/05 21:45:30 by bostic
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
#define	_PATH_DEV		"/dev"
#define	_PATH_DEVDRUM		"/dev/drum"
#define	_PATH_DEVMEM		"/dev/mem"
#define	_PATH_KMEM		"/dev/kmem"
#define	_PATH_PSDATABASE	"/etc/psdatabase"
E 2
I 2
D 4
#include <paths.h>

#define	_PATH_PSDATABASE	"/var/run/psdatabase"
E 2
#define	_PATH_VMCORE		"/vmcore"
E 4
I 4
#define	_PATH_DEVDB	"/var/run/dev.db"
E 4
D 2
#define	_PATH_VMUNIX		"/vmunix"
E 2
E 1
