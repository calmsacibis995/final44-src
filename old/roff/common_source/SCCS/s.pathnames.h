h09398
s 00001/00001/00012
d D 5.5 91/04/30 14:32:59 bostic 5 4
c move term/tab into /usr/old
e
s 00002/00012/00011
d D 5.4 91/04/18 16:49:22 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00000/00022
d D 5.3 91/03/01 15:38:05 cael 3 2
c /usr/adm/tracct -> _PATH_TRACCT (/var/account/tracct)
e
s 00003/00002/00019
d D 5.2 90/06/02 19:56:26 karels 2 1
c move tmac to /usr/share, move defn of /usr/local/lib/tmac to pathnames.h
e
s 00021/00000/00000
d D 5.1 89/08/05 12:23:33 bostic 1 0
c date and time created 89/08/05 12:23:33 by bostic
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
#define	_PATH_TMAC	"/usr/lib/tmac/tmac.xxxxx"
#define	_PATH_TABLPR	"/usr/lib/term/tablpr"
E 2
I 2
#define	_PATH_TMAC		"/usr/share/tmac/tmac."
#define	_PATH_LOCAL_TMAC	"/usr/local/lib/tmac/tmac."
D 5
#define	_PATH_TERM		"/usr/libdata/term/tab"
E 5
I 5
#define	_PATH_TERM		"/usr/old/libdata/term/tab"
E 5
I 3
#define	_PATH_TRACCT		"/var/account/tracct"
E 3
E 2
E 1
