h57842
s 00002/00002/00016
d D 8.1 93/06/06 16:34:35 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00017
d D 5.2 90/06/01 17:47:29 bostic 2 1
c new copyright notice
e
s 00028/00000/00000
d D 5.1 89/05/11 14:41:07 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

#include <paths.h>

#define	_PATH_ACULOG		"/var/log/aculog"
#define	_PATH_LOCKDIRNAME	"/var/spool/uucp/LCK..%s"
#ifdef notdef
#define	_PATH_LOCKDIRNAME	"/var/spool/uucp/LCK/LCK..%s"
#endif
#define	_PATH_PHONES		"/etc/phones"
#define	_PATH_REMOTE		"/etc/remote"
E 1
