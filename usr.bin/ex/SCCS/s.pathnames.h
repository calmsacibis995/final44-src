h29567
s 00002/00002/00019
d D 8.1 93/06/09 21:45:54 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00019
d D 5.5 91/04/17 17:38:45 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00030
d D 5.4 91/01/28 17:54:03 bostic 4 3
c delivermail -> mail.local
e
s 00001/00001/00030
d D 5.3 89/09/07 14:08:34 bostic 3 2
c /bin/mail -> /usr/libexec/delivermail
e
s 00000/00001/00031
d D 5.2 89/05/19 18:45:16 bostic 2 1
c /tmp is in paths.h
e
s 00032/00000/00000
d D 5.1 89/05/11 14:40:47 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
D 5
/*
E 5
I 5
/*-
E 5
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

#include <paths.h>

#define	_PATH_MAKEKEY		"/usr/libexec/makekey"
D 3
#define	_PATH_BINMAIL		"/bin/mail"
E 3
I 3
D 4
#define	_PATH_BINMAIL		"/usr/libexec/delivermail"
E 4
I 4
#define	_PATH_BINMAIL		"/usr/libexec/mail.local"
E 4
E 3
#define	_PATH_EXRECOVER		"/usr/libexec/ex3.7recover"
#define	_PATH_EXPRESERVE	"/usr/libexec/ex3.7preserve"
#define	_PATH_PRESERVE		"/var/preserve"
D 2
#define	_PATH_TMP		"tmp"
E 2
#ifndef VMUNIX
#ifndef	vms
#define	EXSTRINGS	"/usr/libexec/ex3.7strings"
#endif
#endif
E 1
