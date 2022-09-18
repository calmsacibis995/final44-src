h46582
s 00002/00002/00008
d D 8.1 93/06/02 20:05:51 bostic 7 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00010
d R 5.6 91/04/03 16:13:41 bostic 6 5
c protect all user-level include files against reinclusion
e
s 00001/00011/00009
d D 5.5 90/06/01 14:01:02 bostic 5 4
c new copyright notice
e
s 00001/00001/00019
d D 5.4 90/05/15 19:43:57 bostic 4 3
c string.h is ANSI C include file
e
s 00001/00005/00019
d D 5.3 90/02/12 12:20:39 bostic 3 2
c might as well only have one copy.
e
s 00020/00013/00004
d D 5.2 88/08/12 14:13:46 bostic 2 1
c correct list from manual page
e
s 00017/00000/00000
d D 5.1 85/08/05 21:21:49 kre 1 0
c date and time created 85/08/05 21:21:49 by kre
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
D 7
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
E 2
 *
D 2
 *	%W% (Berkeley) %E%
E 2
I 2
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
E 2
 */

D 2
/*
 * Definitions of the Sys5 compat memory manipulation routines
 */

extern char *memccpy();
extern char *memchr();
extern int memcmp();
extern char *memcpy();
extern char *memset();
E 2
I 2
D 3
char *memccpy();
char *memchr();
char *memcpy();
char *memset();
int memcmp();
E 3
I 3
D 4
#include <strings.h>
E 4
I 4
#include <string.h>
E 4
E 3
E 2
E 1
