h07886
s 00002/00002/00013
d D 8.1 93/06/06 14:22:19 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00014
d D 5.4 91/01/28 18:01:03 bostic 4 3
c delivermail -> mail.local
e
s 00001/00001/00014
d D 5.3 90/06/25 01:03:56 bostic 3 2
c /bin/mail has moved to /usr/libexec/delivermail
e
s 00001/00011/00014
d D 5.2 90/06/01 16:36:14 bostic 2 1
c new copyright notice
e
s 00025/00000/00000
d D 5.1 90/04/19 13:59:05 bostic 1 0
c date and time created 90/04/19 13:59:05 by bostic
e
u
U
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

#define	_PATH_ATDIR	"/var/at"
#define	_PATH_LASTFILE	"/var/at/lasttimedone"
D 3
#define	_PATH_MAIL	"/bin/mail"
E 3
I 3
D 4
#define	_PATH_MAIL	"/usr/libexec/delivermail"
E 4
I 4
#define	_PATH_MAIL	"/usr/libexec/mail.local"
E 4
E 3
#define	_PATH_PAST	"/var/at/past"
E 1
