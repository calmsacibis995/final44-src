h30333
s 00005/00000/00038
d D 8.2 94/01/21 16:53:04 bostic 11 10
c add USL's copyright notice
e
s 00002/00002/00036
d D 8.1 93/06/02 20:05:35 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00033
d D 5.4 91/04/03 16:11:50 bostic 9 8
c protect all user-level include files against reinclusion
e
s 00011/00019/00022
d D 5.3 91/02/05 17:10:47 bostic 8 7
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00040
d D 5.2 90/05/29 19:26:47 bostic 7 6
c C++ wants the prototypes, too
e
s 00011/00015/00030
d D 5.1 90/05/25 18:07:47 bostic 6 5
c POSIX 1003.1
e
s 00004/00004/00041
d D 4.5 90/03/13 17:41:36 mckusick 5 4
c endgrent and setgrfile return void, not int
e
s 00017/00003/00028
d D 4.4 90/03/06 15:45:23 bostic 4 3
c add ANSI C prototypes
e
s 00009/00010/00022
d D 4.3 89/03/02 20:52:06 bostic 3 2
c add _PATH, comments, setgroupent(), define all routines
e
s 00025/00003/00007
d D 4.2 88/09/20 16:33:42 bostic 2 1
c add rest of routines; Berkeley copyright
e
s 00010/00000/00000
d D 4.1 83/05/03 13:47:59 sam 1 0
c date and time created 83/05/03 13:47:59 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 6
/*
 * Copyright (c) 1988 The Regents of the University of California.
E 6
I 6
/*-
D 10
 * Copyright (c) 1989 The Regents of the University of California.
E 6
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 11
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 11
E 10
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */
E 2

I 9
#ifndef _GRP_H_
#define	_GRP_H_

E 9
I 6
#ifndef _POSIX_SOURCE
E 6
I 3
#define	_PATH_GROUP		"/etc/group"
I 6
#endif
E 6

E 3
D 2
struct	group { /* see getgrent(3) */
E 2
I 2
struct group {
E 2
D 3
	char	*gr_name;
	char	*gr_passwd;
	int	gr_gid;
	char	**gr_mem;
E 3
I 3
	char	*gr_name;		/* group name */
	char	*gr_passwd;		/* group password */
	int	gr_gid;			/* group id */
	char	**gr_mem;		/* group members */
E 3
};

D 2
struct group *getgrent(), *getgrgid(), *getgrnam();
E 2
I 2
D 3
struct group *getgrent();
struct group *getgrgid();
struct group *getgrnam();
int setgrent();
void endgrent();
void setgrfile();
E 3
I 3
D 4
struct group *getgrent(), *getgrgid(), *getgrnam();
void endgrent(), setgrfile();
int setgroupent(), setgrent();
E 4
I 4
D 7
#ifdef __STDC__
E 7
I 7
D 8
#if __STDC__ || c_plusplus
E 7
D 6
extern struct group *getgrent(void);
E 6
extern struct group *getgrgid(gid_t);
extern struct group *getgrnam(const char *);
E 8
I 8
#include <sys/cdefs.h>

__BEGIN_DECLS
struct group *getgrgid __P((gid_t));
struct group *getgrnam __P((const char *));
E 8
I 6
#ifndef _POSIX_SOURCE
D 8
extern struct group *getgrent(void);
E 6
extern int setgrent(void);
D 5
extern int endgrent(void);
extern int setgrfile(const char *);
E 5
I 5
extern void endgrent(void);
extern void setgrfile(const char *);
E 5
extern int setgroupent(int);
E 8
I 8
struct group *getgrent __P((void));
int setgrent __P((void));
void endgrent __P((void));
void setgrfile __P((const char *));
int setgroupent __P((int));
E 8
I 6
#endif
E 6
D 8
#else
D 6
extern struct group *getgrent();
E 6
extern struct group *getgrgid();
extern struct group *getgrnam();
I 6
#ifndef _POSIX_SOURCE
extern struct group *getgrent();
E 6
extern int setgrent();
D 5
extern int endgrent();
extern int setgrfile();
E 5
I 5
extern void endgrent();
extern void setgrfile();
E 5
extern int setgroupent();
I 6
#endif
E 6
#endif
E 8
I 8
__END_DECLS
I 9

#endif /* !_GRP_H_ */
E 9
E 8
E 4
E 3
E 2
E 1
