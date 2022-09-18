h65092
s 00002/00002/00041
d D 8.1 93/06/02 20:06:10 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00041
d D 5.19 93/05/06 15:05:48 bostic 19 18
c make _PATH_STDPATH include *everything*
e
s 00002/00000/00040
d D 5.18 93/05/03 16:54:20 bostic 18 17
c add "standard utilities" path for POSIX 1003.2 _CS_PATH variable
e
s 00001/00000/00039
d D 5.17 92/04/29 08:19:50 bostic 17 16
c add /etc/shells for the C libarry
e
s 00001/00000/00038
d D 5.16 92/04/24 14:57:05 bostic 16 15
c add _PATH_VARDB, /var/db
e
s 00001/00001/00037
d D 5.15 91/05/29 11:18:56 bostic 15 14
c put /usr/bin first, most stuff is there
e
s 00005/00000/00033
d D 5.14 91/04/03 16:15:46 bostic 14 13
c protect all user-level include files against reinclusion
e
s 00007/00004/00026
d D 5.13 91/02/25 10:18:39 bostic 13 12
c Document trailing slashing on path buildling paths
e
s 00001/00001/00029
d D 5.12 91/02/24 14:08:55 bostic 12 11
c put "." at the end of the default path
e
s 00002/00000/00028
d D 5.11 91/02/23 11:18:00 bostic 11 10
c default path, used by sh(1) and C library exec routines
e
s 00001/00000/00027
d D 5.10 91/02/08 17:20:54 bostic 10 9
c add /var/run/dev.db to global list, used by ttyname(3) and ps(1)
e
s 00001/00000/00026
d D 5.9 91/02/05 17:11:03 bostic 9 8
c add _PATH_VARRUN for /var/run.
e
s 00001/00001/00025
d D 5.8 90/08/24 10:30:24 bostic 8 7
c /usr/man -> /usr/share/man
e
s 00001/00000/00025
d D 5.7 90/06/24 11:33:15 bostic 7 6
c add _PATH_MAILDIR
e
s 00001/00011/00024
d D 5.6 90/06/01 14:01:13 bostic 6 5
c new copyright notice
e
s 00001/00000/00034
d D 5.5 90/02/15 09:19:28 bostic 5 4
c add nologin
e
s 00001/00000/00033
d D 5.4 89/11/14 16:40:14 bostic 4 3
c add _PATH_VARTMP == /var/tmp
e
s 00001/00000/00032
d D 5.3 89/09/22 16:21:02 bostic 3 2
c add default man path
e
s 00001/00000/00031
d D 5.2 89/06/04 09:59:24 bostic 2 1
c add sendmail
e
s 00031/00000/00000
d D 5.1 89/05/24 20:12:19 bostic 1 0
c date and time created 89/05/24 20:12:19 by bostic
e
u
U
t
T
I 1
/*
D 20
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */

I 14
#ifndef _PATHS_H_
#define	_PATHS_H_

E 14
I 13
/* Default search path. */
E 13
I 11
D 12
#define	_PATH_DEFPATH	":/bin:/usr/bin"
E 12
I 12
D 15
#define	_PATH_DEFPATH	"/bin:/usr/bin:"
E 15
I 15
#define	_PATH_DEFPATH	"/usr/bin:/bin"
I 18
/* All standard utilities path. */
D 19
#define	_PATH_STDPATH	"/usr/bin:/bin:/usr/sbin"
E 19
I 19
#define	_PATH_STDPATH \
	"/usr/bin:/bin:/usr/sbin:/sbin:/usr/contrib/bin:/usr/old/bin"
E 19
E 18
E 15
E 12

E 11
#define	_PATH_BSHELL	"/bin/sh"
#define	_PATH_CONSOLE	"/dev/console"
#define	_PATH_CSHELL	"/bin/csh"
D 13
#define	_PATH_DEV	"/dev/"
E 13
I 10
#define	_PATH_DEVDB	"/var/run/dev.db"
E 10
#define	_PATH_DEVNULL	"/dev/null"
#define	_PATH_DRUM	"/dev/drum"
#define	_PATH_KMEM	"/dev/kmem"
I 7
#define	_PATH_MAILDIR	"/var/mail"
E 7
I 3
D 8
#define	_PATH_MAN	"/usr/man"
E 8
I 8
#define	_PATH_MAN	"/usr/share/man"
E 8
E 3
#define	_PATH_MEM	"/dev/mem"
I 5
#define	_PATH_NOLOGIN	"/etc/nologin"
E 5
I 2
#define	_PATH_SENDMAIL	"/usr/sbin/sendmail"
I 17
#define	_PATH_SHELLS	"/etc/shells"
E 17
E 2
D 13
#define	_PATH_TMP	"/tmp/"
E 13
#define	_PATH_TTY	"/dev/tty"
#define	_PATH_UNIX	"/vmunix"
I 9
D 13
#define	_PATH_VARRUN	"/var/run"
E 9
I 4
#define	_PATH_VARTMP	"/var/tmp"
E 13
E 4
#define	_PATH_VI	"/usr/bin/vi"
I 13

/* Provide trailing slash, since mostly used for building pathnames. */
#define	_PATH_DEV	"/dev/"
#define	_PATH_TMP	"/tmp/"
I 16
#define	_PATH_VARDB	"/var/db/"
E 16
#define	_PATH_VARRUN	"/var/run/"
#define	_PATH_VARTMP	"/var/tmp/"
I 14

#endif /* !_PATHS_H_ */
E 14
E 13
E 1
