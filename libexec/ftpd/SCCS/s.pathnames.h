h58471
s 00002/00002/00012
d D 8.1 93/06/04 18:48:42 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00011
d D 5.3 92/06/27 16:52:12 andrew 3 2
c add paths for message files
e
s 00001/00011/00011
d D 5.2 90/06/01 15:52:45 bostic 2 1
c new copyright notice
e
s 00022/00000/00000
d D 5.1 89/05/11 14:40:31 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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

D 3
#define	_PATH_FTPUSERS	"/etc/ftpusers"
E 3
I 3
#define	_PATH_FTPUSERS		"/etc/ftpusers"
#define	_PATH_FTPWELCOME	"/etc/ftpwelcome"
#define	_PATH_FTPLOGINMESG	"/etc/motd"
E 3
E 1
