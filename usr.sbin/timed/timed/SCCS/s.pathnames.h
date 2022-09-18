h43602
s 00002/00002/00016
d D 8.1 93/06/06 14:09:46 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00014
d D 5.6 93/05/11 11:52:25 bostic 6 5
c put in sccs keywords line
e
s 00006/00003/00010
d D 5.5 93/05/11 11:51:15 bostic 5 4
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00001/00011/00012
d D 5.4 90/06/01 19:04:02 bostic 4 3
c new copyright notice
e
s 00002/00002/00021
d D 5.3 89/05/19 18:14:50 bostic 3 2
c /usr/adm -> /var/log
e
s 00002/00000/00021
d D 5.2 89/05/11 14:14:00 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00021/00000/00000
d D 5.1 89/04/02 15:43:04 bostic 1 0
c date and time created 89/04/02 15:43:04 by bostic
e
u
U
t
T
I 1
D 6
/*
D 5
 * Copyright (c) 1989 The Regents of the University of California.
E 5
I 5
 * Copyright (c) 1985 Regents of the University of California.
E 6
I 6
/*-
D 7
 * Copyright (c) 1985 The Regents of the University of California.
E 6
E 5
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
I 6
 *
 *	%W% (Berkeley) %G%
E 6
E 4
D 5
 *
 *	%W% (Berkeley) %G%
E 5
 */

I 2
#include <paths.h>

I 5
#ifdef sgi
#define	_PATH_MASTERLOG	"/usr/adm/timed.masterlog"
#define	_PATH_TIMEDLOG	"/usr/adm/timed.log"
#else
E 5
E 2
D 3
#define	_PATH_MASTERLOG	"/usr/adm/timed.masterlog"
#define	_PATH_TIMEDLOG	"/usr/adm/timed.log"
E 3
I 3
#define	_PATH_MASTERLOG	"/var/log/timed.masterlog"
#define	_PATH_TIMEDLOG	"/var/log/timed.log"
I 5
#endif
E 5
E 3
E 1
