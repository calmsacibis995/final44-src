h30874
s 00002/00002/00014
d D 8.1 93/06/05 10:52:53 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00016
d D 5.6 91/02/28 18:49:51 mckusick 6 5
c get rid of default disk to dump
e
s 00001/00011/00016
d D 5.5 90/06/01 16:15:33 bostic 5 4
c new copyright notice
e
s 00001/00001/00026
d D 5.4 90/02/16 10:01:17 karels 4 3
c *don't* attempt to specify what the *remote* pathname of rmt is
e
s 00001/00001/00026
d D 5.3 90/02/15 13:27:02 mckusick 3 2
c define exactly where to look for rmt command
e
s 00007/00001/00020
d D 5.2 89/05/11 13:52:32 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00021/00000/00000
d D 5.1 89/04/02 12:30:21 bostic 1 0
c date and time created 89/04/02 12:30:21 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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

D 2
#define	_PATH_DUMPDATES	"/etc/dumpdates"
E 2
I 2
#include <paths.h>

D 6
#define	_PATH_DEFDISK	"/dev/rrp1g"
E 6
#define	_PATH_DEFTAPE	"/dev/rmt8"
E 2
#define	_PATH_DTMP	"/etc/dtmp"
I 2
#define	_PATH_DUMPDATES	"/etc/dumpdates"
#define	_PATH_LOCK	"/tmp/dumplockXXXXXX"
D 3
#define	_PATH_RMT	"rmt"
E 3
I 3
D 4
#define	_PATH_RMT	"/usr/libexec/rmt"
E 4
I 4
#define	_PATH_RMT	"rmt"
E 4
E 3
E 2
E 1
