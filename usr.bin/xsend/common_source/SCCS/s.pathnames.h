h03967
s 00002/00002/00010
d D 8.1 93/06/06 22:29:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00010
d D 5.4 91/01/29 16:03:13 bostic 4 3
c new copyright notice
e
s 00001/00001/00021
d D 5.3 91/01/29 16:02:41 bostic 3 2
c delivermail -> mail.local
e
s 00001/00001/00021
d D 5.2 90/06/25 01:03:17 bostic 2 1
c binmail has moved to /usr/libexec
e
s 00022/00000/00000
d D 5.1 89/05/11 14:41:12 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
D 4
/*
E 4
I 4
/*-
E 4
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

D 2
#define	_PATH_MAIL		"/bin/mail"
E 2
I 2
D 3
#define	_PATH_MAIL		"/usr/libexec/delivermail"
E 3
I 3
#define	_PATH_MAIL		"/usr/libexec/mail.local"
E 3
E 2
#define	_PATH_MAKEKEY		"/usr/libexec/makekey"
#define	_PATH_SECRETMAIL	"/var/spool/secretmail"
E 1
