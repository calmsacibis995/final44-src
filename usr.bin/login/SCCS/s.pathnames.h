h34680
s 00002/00002/00011
d D 8.1 93/06/09 22:44:18 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00011
d D 5.7 91/04/18 15:54:28 bostic 7 6
c new copyright; att/bsd/shared
e
s 00000/00001/00023
d D 5.6 91/03/01 14:56:34 bostic 6 5
c ANSI
e
s 00000/00001/00024
d D 5.5 90/06/24 16:18:49 bostic 5 4
c get MAILDIR from paths.h
e
s 00000/00001/00025
d D 5.4 90/02/15 09:20:51 bostic 4 3
c remove nologin, it's paths.h now
e
s 00004/00005/00022
d D 5.3 89/05/09 13:37:40 bostic 3 2
c add paths.h
e
s 00001/00000/00026
d D 5.2 89/04/02 11:59:40 bostic 2 1
c rest of pathnames
e
s 00025/00000/00000
d D 5.1 89/03/05 21:33:30 bostic 1 0
c date and time created 89/03/05 21:33:30 by bostic
e
u
U
t
T
I 1
D 7
/*
E 7
I 7
/*-
E 7
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */

D 3
#define	_PATH_BSHELL	"/bin/sh"
#define	_PATH_CSHELL	"/bin/csh"
E 3
I 3
#include <paths.h>

D 6
#define	_PATH_DEFPATH	"/bin:/usr/bin:/usr/games:"
E 6
E 3
#define	_PATH_HUSHLOGIN	".hushlogin"
D 3
#define	_PATH_LASTLOG	"/usr/adm/lastlog"
#define	_PATH_MAILDIR	"/usr/spool/mail"
E 3
I 3
D 5
#define	_PATH_MAILDIR	"/var/spool/mail"
E 5
E 3
#define	_PATH_MOTDFILE	"/etc/motd"
D 4
#define	_PATH_NOLOGIN	"/etc/nologin"
E 4
I 2
D 3
#define	_PATH_DEFPATH	"/usr/ucb:/bin:/usr/bin:"
E 3
E 2
E 1
