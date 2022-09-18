h24323
s 00002/00002/00011
d D 8.1 93/06/05 11:05:32 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00012
d D 6.5 90/06/27 17:20:54 mckusick 6 5
c move mountdtab to /var/db so it is not purged on reboots
e
s 00001/00001/00012
d D 6.4 90/06/21 09:08:34 mckusick 5 4
c mountdtab goes in /var/run, not /var
e
s 00001/00011/00012
d D 6.3 90/06/01 16:18:33 bostic 4 3
c new copyright notice
e
s 00001/00000/00022
d D 6.2 90/03/15 17:24:56 mckusick 3 1
c store pid in /var/run/mountd.pid for mount to notify of changes
e
s 00001/00000/00022
d R 6.2 90/03/15 16:41:33 mckusick 2 1
c add _PATH_PIDFILE
e
s 00022/00000/00000
d D 6.1 89/11/30 23:58:44 mckusick 1 0
c date and time created 89/11/30 23:58:44 by mckusick
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
#include <paths.h>

#define	_PATH_EXPORTS		"/etc/exports"
D 5
#define	_PATH_RMOUNTLIST	"/var/mountdtab"
E 5
I 5
D 6
#define	_PATH_RMOUNTLIST	"/var/run/mountdtab"
E 6
I 6
#define	_PATH_RMOUNTLIST	"/var/db/mountdtab"
E 6
E 5
I 3
#define _PATH_MOUNTDPID		"/var/run/mountd.pid"
E 3
E 1
