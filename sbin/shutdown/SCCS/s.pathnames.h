h17806
s 00002/00002/00013
d D 8.1 93/06/05 11:21:01 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00014
d D 5.5 90/06/01 16:29:42 bostic 5 4
c new copyright notice
e
s 00002/00000/00023
d D 5.4 90/02/20 16:12:44 bostic 4 3
c needs to include paths.h, now for _PATH_NOLOGIN
e
s 00000/00001/00023
d D 5.3 90/02/15 09:20:36 bostic 3 2
c remove nologin, it's paths.h now
e
s 00003/00003/00021
d D 5.2 89/05/11 14:02:01 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00023/00000/00000
d D 5.1 89/04/02 15:10:58 bostic 1 0
c date and time created 89/04/02 15:10:58 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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

I 4
#include <paths.h>

E 4
#define	_PATH_FASTBOOT	"/fastboot"
D 2
#define	_PATH_HALT	"/etc/halt"
E 2
I 2
#define	_PATH_HALT	"/sbin/halt"
E 2
D 3
#define	_PATH_NOLOGIN	"/etc/nologin"
E 3
D 2
#define	_PATH_REBOOT	"/etc/reboot"
#define	_PATH_WALL	"/bin/wall"
E 2
I 2
#define	_PATH_REBOOT	"/sbin/reboot"
#define	_PATH_WALL	"/usr/bin/wall"
E 2
E 1
