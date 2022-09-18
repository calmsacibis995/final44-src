h43889
s 00005/00000/00034
d D 8.2 94/01/21 16:53:07 bostic 16 15
c add USL's copyright notice
e
s 00002/00002/00032
d D 8.1 93/06/02 20:07:33 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00029
d D 5.11 91/04/03 16:43:45 bostic 14 13
c protect all user-level include files against reinclusion
e
s 00001/00011/00028
d D 5.10 90/06/01 14:02:13 bostic 13 12
c new copyright notice
e
s 00002/00002/00037
d D 5.9 89/05/15 08:40:08 bostic 12 11
c LINE/NAMESIZE typo
e
s 00008/00000/00031
d D 5.8 89/05/10 22:34:03 bostic 11 10
c add lastlog path; add lastlog structure -- lastlog.h removed
e
s 00002/00002/00029
d D 5.7 89/04/17 21:34:10 bostic 10 9
c move utmp, wtmp to /var
e
s 00001/00000/00030
d D 5.6 89/04/02 12:04:03 bostic 9 8
c add wtmp
e
s 00002/00000/00028
d D 5.5 89/03/07 13:25:22 bostic 8 7
c add utmp path
e
s 00001/00001/00027
d D 5.4 88/10/07 17:04:26 marc 7 6
c time_t back to long. - not worth it (mike)
e
s 00006/00003/00022
d D 5.3 88/09/22 10:39:02 bostic 6 5
c add defines for various sizes
e
s 00018/00012/00007
d D 5.2 88/09/20 13:34:31 bostic 5 4
c retype time; add Berkeley specific header
e
s 00007/00001/00012
d D 5.1 85/05/30 09:42:17 dist 4 3
c Add copyright
e
s 00001/00000/00012
d D 4.2 83/05/22 19:22:53 sam 3 1
c add field for remote host name
e
s 00001/00000/00012
d R 4.2 83/05/22 19:13:41 sam 2 1
c add field for remote host name
e
s 00012/00000/00000
d D 4.1 83/05/03 13:48:22 sam 1 0
c date and time created 83/05/03 13:48:22 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
D 5
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 15
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
I 16
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 16
E 15
E 5
 *
I 5
D 13
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
I 13
 * %sccs.include.redist.c%
E 13
 *
E 5
 *	%W% (Berkeley) %G%
 */
E 4

I 14
#ifndef	_UTMP_H_
#define	_UTMP_H_

E 14
I 8
D 10
#define	_PATH_UTMP	"/etc/utmp"
I 9
#define	_PATH_WTMP	"/usr/adm/wtmp"
E 10
I 10
#define	_PATH_UTMP	"/var/run/utmp"
#define	_PATH_WTMP	"/var/log/wtmp"
I 11
#define	_PATH_LASTLOG	"/var/log/lastlog"
E 11
E 10
E 9

E 8
I 6
#define	UT_NAMESIZE	8
#define	UT_LINESIZE	8
#define	UT_HOSTSIZE	16
I 11

struct lastlog {
	time_t	ll_time;
	char	ll_line[UT_LINESIZE];
	char	ll_host[UT_HOSTSIZE];
};

E 11
E 6
D 5
/*
 * Structure of utmp and wtmp files.
 *
 * Assuming the number 8 is unwise.
 */
E 5
struct utmp {
D 5
	char	ut_line[8];		/* tty name */
	char	ut_name[8];		/* user id */
I 3
	char	ut_host[16];		/* host name, if remote */
E 3
	long	ut_time;		/* time on */
E 5
I 5
D 6
	char	ut_line[8];
	char	ut_name[8];
	char	ut_host[16];
E 6
I 6
D 12
	char	ut_line[UT_NAMESIZE];
	char	ut_name[UT_LINESIZE];
E 12
I 12
	char	ut_line[UT_LINESIZE];
	char	ut_name[UT_NAMESIZE];
E 12
	char	ut_host[UT_HOSTSIZE];
E 6
D 7
	time_t	ut_time;
E 7
I 7
	long	ut_time;
E 7
E 5
};
I 14

#endif /* !_UTMP_H_ */
E 14
E 1
