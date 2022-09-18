h41114
s 00005/00001/00023
d D 8.4 95/06/19 18:12:26 eric 10 9
c default scanf on; always use /etc/sendmail.cf regardless of vendor
c preferences
e
s 00004/00000/00020
d D 8.3 95/05/13 15:05:57 eric 9 8
c put getcanonname into service switch
e
s 00000/00004/00020
d D 8.2 93/08/20 11:51:56 eric 8 7
c more on elimination of frozen config files
e
s 00002/00002/00022
d D 8.1 93/06/07 10:31:23 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00016
d D 6.5 93/02/23 10:09:37 eric 6 5
c allow compile time specification of sendmail.cf and .fc too
e
s 00006/00004/00012
d D 6.4 93/02/23 10:06:41 eric 5 4
c allow definition of _PATH_SENDMAILPID in Makefile
e
s 00004/00000/00012
d D 6.3 93/02/21 14:43:19 eric 4 3
c put pid file in /var/run on 4.4bsd (not /etc)
e
s 00003/00002/00009
d D 6.2 93/02/20 13:46:26 eric 3 2
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00000/00000/00011
d D 6.1 92/12/21 16:08:07 eric 2 1
c Release 6
e
s 00011/00000/00000
d D 5.1 90/04/19 10:03:45 bostic 1 0
c date and time created 90/04/19 10:03:45 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#define	_PATH_SENDMAILCF	"/etc/sendmail.cf";
#define	_PATH_SENDMAILFC	"/etc/sendmail.fc";
E 3
I 3
D 6
#define	_PATH_SENDMAILCF	"/etc/sendmail.cf"
#define	_PATH_SENDMAILFC	"/etc/sendmail.fc"
E 6
I 6
#ifndef _PATH_SENDMAILCF
D 10
# define _PATH_SENDMAILCF	"/etc/sendmail.cf"
E 10
I 10
# if defined(USE_VENDOR_CF_PATH) && defined(_PATH_VENDOR_CF)
#  define _PATH_SENDMAILCF	_PATH_VENDOR_CF
# else
#  define _PATH_SENDMAILCF	"/etc/sendmail.cf"
# endif
E 10
#endif

D 8
#ifndef _PATH_SENDMAILFC
# define _PATH_SENDMAILFC	"/etc/sendmail.fc"
#endif

E 8
E 6
I 4
D 5
#ifdef BSD4_4
#define _PATH_SENDMAILPID	"/var/run/sendmail.pid"
#else
E 4
#define _PATH_SENDMAILPID	"/etc/sendmail.pid"
E 5
I 5
#ifndef _PATH_SENDMAILPID
# ifdef BSD4_4
#  define _PATH_SENDMAILPID	"/var/run/sendmail.pid"
# else
#  define _PATH_SENDMAILPID	"/etc/sendmail.pid"
# endif
E 5
I 4
#endif
I 9

#ifndef _PATH_HOSTS
# define _PATH_HOSTS		"/etc/hosts"
#endif
E 9
E 4
E 3
E 1
