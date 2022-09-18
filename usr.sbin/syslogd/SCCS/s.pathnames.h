h11015
s 00002/00002/00012
d D 8.1 93/06/06 14:08:22 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00014
d D 5.4 90/09/29 10:35:19 bostic 4 3
c _PATH_LOG moved to <sys/syslog.h>, used by syslog(3)
e
s 00001/00011/00014
d D 5.3 90/06/01 19:01:07 bostic 3 2
c new copyright notice
e
s 00004/00003/00021
d D 5.2 89/05/11 14:13:36 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00024/00000/00000
d D 5.1 89/04/02 15:33:37 bostic 1 0
c date and time created 89/04/02 15:33:37 by bostic
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
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 2
#define	_PATH_CONSOLE	"/dev/console"
E 2
I 2
#include <paths.h>

E 2
#define	_PATH_KLOG	"/dev/klog"
D 4
#define	_PATH_LOG	"/dev/log"
E 4
D 2
#define	_PATH_LOGCONF	"/dev/syslog.conf"
#define	_PATH_LOGPID	"/dev/syslog.pid"
E 2
I 2
#define	_PATH_LOGCONF	"/etc/syslog.conf"
#define	_PATH_LOGPID	"/var/run/syslog.pid"
E 2
E 1
