h22580
s 00003/00002/00009
d D 8.2 94/03/27 07:44:04 pendry 7 6
c remove _PATH_EXECDIR, add _PATH_SBIN, _PATH_USRSBIN
e
s 00002/00002/00009
d D 8.1 93/06/05 11:01:29 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00011
d D 6.5 92/01/06 11:13:16 mckusick 5 4
c break out NFS handling (to mount_nfs)
e
s 00001/00011/00011
d D 6.4 90/06/01 16:18:14 bostic 4 3
c new copyright notice
e
s 00001/00000/00021
d D 6.3 90/03/15 17:26:17 mckusick 3 2
c notify mountd of changes by signalling pid stored in /var/run/mountd.pid
e
s 00001/00000/00020
d D 6.2 90/03/08 15:24:34 mckusick 2 1
c add entry for the exports file
e
s 00020/00000/00000
d D 6.1 89/10/17 16:24:25 mckusick 1 0
c date and time created 89/10/17 16:24:25 by mckusick
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 7
 * Copyright (c) 1989, 1993
E 7
I 7
 * Copyright (c) 1989, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 6
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

D 7
#define _PATH_EXECDIR	"/sbin"
E 7
I 7
#define _PATH_SBIN	"/sbin"
#define _PATH_USRSBIN	"/usr/sbin"
E 7
I 2
D 5
#define	_PATH_EXPORTS	"/etc/exports"
E 5
I 3
#define	_PATH_MOUNTDPID	"/var/run/mountd.pid"
E 3
E 2
E 1
