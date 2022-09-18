h14707
s 00005/00000/00059
d D 8.2 94/01/21 16:53:05 bostic 22 21
c add USL's copyright notice
e
s 00002/00002/00057
d D 8.1 93/06/02 20:06:13 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00058
d D 5.13 91/05/28 12:26:26 bostic 20 19
c document behavior re: the terminating null of password
e
s 00005/00003/00054
d D 5.12 91/04/21 14:21:37 bostic 19 18
c #define '_' as indicated the extended format
e
s 00005/00000/00052
d D 5.11 91/04/03 16:18:56 bostic 18 17
c protect all user-level include files against reinclusion
e
s 00002/00002/00050
d D 5.10 91/03/03 13:33:42 bostic 17 16
c move password databases back into /etc, rename for db(3) interface
e
s 00006/00007/00046
d D 5.9 91/02/22 08:43:58 bostic 16 15
c setpwfile has gone away
e
s 00002/00002/00051
d D 5.8 91/02/14 15:28:45 bostic 15 14
c since db(3) appends ".db", don't need it here.
e
s 00008/00004/00045
d D 5.7 91/02/12 20:08:56 bostic 14 13
c rework the password subsystem
e
s 00011/00019/00038
d D 5.6 91/02/05 17:10:48 bostic 13 12
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00056
d D 5.5 90/05/29 19:26:51 bostic 12 11
c C++ wants the prototypes, too
e
s 00022/00026/00035
d D 5.4 90/05/25 18:21:51 bostic 11 10
c POSIX 1003.1
e
s 00004/00004/00057
d D 5.3 90/03/13 17:44:42 mckusick 10 9
c endpwent and setpwfile return void
e
s 00002/00000/00059
d D 5.2 90/03/12 11:01:24 mckusick 9 8
c have to include <sys/types.h> since now using u_long
e
s 00017/00003/00042
d D 5.1 90/03/06 15:57:05 bostic 8 7
c add ANSI C prototypes
e
s 00002/00002/00043
d D 5.0 90/02/12 12:19:18 bostic 7 6
c make time values u_long's -- should eventually be time_t's.
c yank to 5.0
e
s 00002/00000/00043
d D 4.5 89/09/18 14:50:55 bostic 6 5
c add password length define
e
s 00002/00002/00041
d D 4.4 89/04/14 17:31:22 bostic 5 4
c *sigh* can't use something needing sys/types.h
e
s 00021/00015/00022
d D 4.3 89/02/22 11:05:30 bostic 4 3
c shadow passwords
e
s 00027/00005/00010
d D 4.2 88/09/20 16:33:58 bostic 3 1
c add rest of routines, Berkeley copyright
e
s 00004/00000/00015
d R 4.2 83/12/02 16:31:31 ralph 2 1
c new getpwnam and getpwuid which need ndbm.h
e
s 00015/00000/00000
d D 4.1 83/05/03 13:48:10 sam 1 0
c date and time created 83/05/03 13:48:10 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
D 11
/*
 * Copyright (c) 1988 The Regents of the University of California.
E 11
I 11
/*-
D 21
 * Copyright (c) 1989 The Regents of the University of California.
E 11
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 22
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 22
E 21
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
 *
 *	%W% (Berkeley) %G%
 */
E 3

I 18
#ifndef _PWD_H_
#define	_PWD_H_

E 18
I 9
#include <sys/types.h>

I 11
#ifndef _POSIX_SOURCE
E 11
E 9
I 4
#define	_PATH_PASSWD		"/etc/passwd"
#define	_PATH_MASTERPASSWD	"/etc/master.passwd"
D 14
#define	_PATH_MKPASSWD		"/usr/sbin/mkpasswd"
#define	_PATH_PTMP		"/etc/ptmp"
E 14

D 14
#define	_PW_KEYBYNAME		'0'
#define	_PW_KEYBYUID		'1'
E 14
I 14
D 15
#define	_PATH_MP_DB		"/var/db/pwd.db"
#define	_PATH_SMP_DB		"/var/db/spwd.db"
E 15
I 15
D 17
#define	_PATH_MP_DB		"/var/db/pwd"
#define	_PATH_SMP_DB		"/var/db/spwd"
E 17
I 17
#define	_PATH_MP_DB		"/etc/pwd.db"
#define	_PATH_SMP_DB		"/etc/spwd.db"
E 17
E 15

#define	_PATH_PWD_MKDB		"/usr/sbin/pwd_mkdb"

D 19
#define	_PW_KEYBYNAME		'1'
#define	_PW_KEYBYNUM		'2'
#define	_PW_KEYBYUID		'3'
E 19
I 19
#define	_PW_KEYBYNAME		'1'	/* stored by name */
#define	_PW_KEYBYNUM		'2'	/* stored by entry in the "file" */
#define	_PW_KEYBYUID		'3'	/* stored by uid */

#define	_PASSWORD_EFMT1		'_'	/* extended encryption format */
E 19
E 14

I 6
D 20
#define	_PASSWORD_LEN		128
E 20
I 20
#define	_PASSWORD_LEN		128	/* max length, not counting NULL */
E 20
I 11
#endif
E 11

E 6
E 4
D 3
struct	passwd { /* see getpwent(3) */
E 3
I 3
struct passwd {
E 3
D 4
	char	*pw_name;
	char	*pw_passwd;
	int	pw_uid;
	int	pw_gid;
D 3
	int	pw_quota;
	char	*pw_comment;
E 3
I 3
	int	pw_quota;		/* not used */
	char	*pw_comment;		/* not used */
E 3
	char	*pw_gecos;
	char	*pw_dir;
	char	*pw_shell;
E 4
I 4
D 11
	char	*pw_name;			/* user name */
	char	*pw_passwd;			/* encrypted password */
	int	pw_uid;				/* user uid */
	int	pw_gid;				/* user gid */
D 5
	time_t	pw_change;			/* password change time */
E 5
I 5
D 7
	long	pw_change;			/* password change time */
E 7
I 7
	u_long	pw_change;			/* password change time */
E 7
E 5
	char	*pw_class;			/* user access class */
	char	*pw_gecos;			/* Honeywell login info */
	char	*pw_dir;			/* home directory */
	char	*pw_shell;			/* default shell */
D 5
	time_t	pw_expire;			/* account expiration */
E 5
I 5
D 7
	long	pw_expire;			/* account expiration */
E 7
I 7
	u_long	pw_expire;			/* account expiration */
E 11
I 11
	char	*pw_name;		/* user name */
	char	*pw_passwd;		/* encrypted password */
	int	pw_uid;			/* user uid */
	int	pw_gid;			/* user gid */
	time_t	pw_change;		/* password change time */
	char	*pw_class;		/* user access class */
	char	*pw_gecos;		/* Honeywell login info */
	char	*pw_dir;		/* home directory */
	char	*pw_shell;		/* default shell */
	time_t	pw_expire;		/* account expiration */
E 11
E 7
E 5
E 4
};

D 3
struct passwd *getpwent(), *getpwuid(), *getpwnam();
E 3
I 3
D 4
struct passwd *getpwent();
struct passwd *getpwuid();
struct passwd *getpwnam();
int setpwent();
void endpwent();
void setpwfile();
E 4
I 4
D 8
struct passwd *getpwent(), *getpwuid(), *getpwnam();
void endpwent(), setpwfile();
int setpassent(), setpwent();
E 8
I 8
D 12
#ifdef __STDC__
E 12
I 12
D 13
#if __STDC__ || c_plusplus
E 12
D 11
struct passwd *getpwent(void);
struct passwd *getpwuid(int);
E 11
I 11
struct passwd *getpwuid(uid_t);
E 11
struct passwd *getpwnam(const char *);
E 13
I 13
#include <sys/cdefs.h>

__BEGIN_DECLS
D 16
struct passwd *getpwuid __P((uid_t));
struct passwd *getpwnam __P((const char *));
E 16
I 16
struct passwd	*getpwuid __P((uid_t));
struct passwd	*getpwnam __P((const char *));
E 16
E 13
I 11
#ifndef _POSIX_SOURCE
D 13
struct passwd *getpwent(void);
E 11
int setpwent(void);
D 10
int endpwent(void);
int setpwfile(const char *);
E 10
I 10
void endpwent(void);
void setpwfile(const char *);
E 10
int setpassent(int);
E 13
I 13
D 16
struct passwd *getpwent __P((void));
int setpwent __P((void));
void endpwent __P((void));
void setpwfile __P((const char *));
int setpassent __P((int));
E 16
I 16
struct passwd	*getpwent __P((void));
int		 setpassent __P((int));
int		 setpwent __P((void));
void		 endpwent __P((void));
E 16
E 13
I 11
#endif
E 11
D 13
#else
D 11
struct passwd *getpwent();
E 11
struct passwd *getpwuid();
struct passwd *getpwnam();
I 11
#ifndef _POSIX_SOURCE
struct passwd *getpwent();
E 11
int setpwent();
D 10
int endpwent();
int setpwfile();
E 10
I 10
void endpwent();
void setpwfile();
E 10
int setpassent();
I 11
#endif
E 11
#endif
E 13
I 13
__END_DECLS
I 18

#endif /* !_PWD_H_ */
E 18
E 13
E 8
E 4
E 3
E 1
