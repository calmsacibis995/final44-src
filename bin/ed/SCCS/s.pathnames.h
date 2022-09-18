h52060
s 00001/00011/00011
d D 5.4 90/05/31 20:30:41 bostic 4 3
c new copyright notice
e
s 00000/00001/00022
d D 5.3 89/05/08 17:54:36 bostic 3 2
c /tmp moves to /usr/include
e
s 00004/00003/00019
d D 5.2 89/05/08 12:58:50 bostic 2 1
c file system reorg and pathnames.h
e
s 00022/00000/00000
d D 5.1 89/03/05 21:28:28 bostic 1 0
c date and time created 89/03/05 21:28:28 by bostic
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

D 2
#define	_PATH_BSHELL		"/bin/sh"
#define	_PATH_L_MAKEKEY		"/lib/makekey"
#define	_PATH_UL_MAKEKEY	"/usr/lib/makekey"
E 2
I 2
#include <paths.h>

#define	_PATH_MAKEKEY	"/usr/libexec/makekey"
D 3
#define	_PATH_TMP	"/tmp/eXXXXX";
E 3
E 2
E 1
