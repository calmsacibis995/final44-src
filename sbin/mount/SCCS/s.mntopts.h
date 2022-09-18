h11236
s 00017/00015/00037
d D 8.7 95/03/29 21:24:37 mckusick 7 6
c allow setting of alternate flags (from FreeBSD
e
s 00001/00001/00051
d D 8.6 94/07/07 16:01:02 mckusick 6 5
c wrong sense on force
e
s 00004/00000/00048
d D 8.5 94/06/23 22:12:02 mckusick 5 4
c handle userquota and groupquota (from deraadt@fsa.ca)
e
s 00005/00003/00043
d D 8.4 94/06/16 17:53:43 mckusick 4 3
c add the noauto option
e
s 00001/00001/00045
d D 8.3 94/03/27 23:05:04 pendry 3 2
c fix typo "exec" -> "force"
e
s 00011/00011/00035
d D 8.2 94/03/27 15:00:44 bostic 2 1
c make async, sync match between .h and man page
e
s 00047/00000/00000
d D 8.1 94/03/27 08:07:56 bostic 1 0
c date and time created 94/03/27 08:07:56 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *      The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct mntopt {
	const char *m_option;	/* option name */
	int m_inverse;		/* if a negative option, eg "dev" */
	int m_flag;		/* bit to set, eg. MNT_RDONLY */
I 7
	int m_altloc;		/* 1 => set bit in altflags */
E 7
};

/* User-visible MNT_ flags. */
D 2
#define MOPT_ASYNC		{ "async",	 0, MNT_ASYNC }
#define MOPT_NODEV		{ "dev",	 1, MNT_NODEV }
#define MOPT_NOEXEC		{ "exec",	 1, MNT_NOEXEC }
#define MOPT_NOSUID		{ "suid",	 1, MNT_NOSUID }
#define MOPT_RDONLY		{ "rdonly",	 0, MNT_RDONLY }
#define MOPT_SYNCHRONOUS	{ "synchronous", 0, MNT_SYNCHRONOUS }
#define MOPT_UNION		{ "union",	 0, MNT_UNION }
E 2
I 2
D 7
#define MOPT_ASYNC		{ "async",	0, MNT_ASYNC }
#define MOPT_NODEV		{ "dev",	1, MNT_NODEV }
#define MOPT_NOEXEC		{ "exec",	1, MNT_NOEXEC }
#define MOPT_NOSUID		{ "suid",	1, MNT_NOSUID }
#define MOPT_RDONLY		{ "rdonly",	0, MNT_RDONLY }
#define MOPT_SYNC		{ "sync",	0, MNT_SYNCHRONOUS }
#define MOPT_UNION		{ "union",	0, MNT_UNION }
I 5
#define MOPT_USERQUOTA		{ "userquota",	0, 0 }
#define MOPT_GROUPQUOTA		{ "groupquota",	0, 0 }
E 7
I 7
#define MOPT_ASYNC		{ "async",	0, MNT_ASYNC, 0 }
#define MOPT_NODEV		{ "dev",	1, MNT_NODEV, 0 }
#define MOPT_NOEXEC		{ "exec",	1, MNT_NOEXEC, 0 }
#define MOPT_NOSUID		{ "suid",	1, MNT_NOSUID, 0 }
#define MOPT_RDONLY		{ "rdonly",	0, MNT_RDONLY, 0 }
#define MOPT_SYNC		{ "sync",	0, MNT_SYNCHRONOUS, 0 }
#define MOPT_UNION		{ "union",	0, MNT_UNION, 0 }
#define MOPT_USERQUOTA		{ "userquota",	0, 0, 0 }
#define MOPT_GROUPQUOTA		{ "groupquota",	0, 0, 0 }
E 7
E 5
E 2

/* Control flags. */
D 2
#define MOPT_FORCE		{ "exec",	 1, MNT_FORCE }
#define MOPT_UPDATE		{ "update",	 0, MNT_UPDATE }
E 2
I 2
D 3
#define MOPT_FORCE		{ "exec",	1, MNT_FORCE }
E 3
I 3
D 6
#define MOPT_FORCE		{ "force",	1, MNT_FORCE }
E 6
I 6
D 7
#define MOPT_FORCE		{ "force",	0, MNT_FORCE }
E 6
E 3
#define MOPT_UPDATE		{ "update",	0, MNT_UPDATE }
E 2
D 4

/* Support for old-style "ro", "rw" flags. */
E 4
D 2
#define MOPT_RO			{ "ro",		 0, MNT_RDONLY }
#define MOPT_RW			{ "rw",		 1, MNT_RDONLY }
E 2
I 2
#define MOPT_RO			{ "ro",		0, MNT_RDONLY }
#define MOPT_RW			{ "rw",		1, MNT_RDONLY }
E 7
I 7
#define MOPT_FORCE		{ "force",	0, MNT_FORCE, 0 }
#define MOPT_UPDATE		{ "update",	0, MNT_UPDATE, 0 }
#define MOPT_RO			{ "ro",		0, MNT_RDONLY, 0 }
#define MOPT_RW			{ "rw",		1, MNT_RDONLY, 0 }
E 7
E 2

I 4
/* This is parsed by mount(8), but is ignored by specific mount_*(8)s. */
D 7
#define MOPT_AUTO		{ "auto",	0, 0 }
E 7
I 7
#define MOPT_AUTO		{ "auto",	0, 0, 0 }
E 7

E 4
#define MOPT_FSTAB_COMPAT						\
	MOPT_RO,							\
D 4
	MOPT_RW
E 4
I 4
	MOPT_RW,							\
	MOPT_AUTO
E 4

/* Standard options which all mounts can understand. */
#define MOPT_STDOPTS							\
I 5
	MOPT_USERQUOTA,							\
	MOPT_GROUPQUOTA,						\
E 5
	MOPT_FSTAB_COMPAT,						\
	MOPT_NODEV,							\
	MOPT_NOEXEC,							\
	MOPT_NOSUID,							\
	MOPT_RDONLY,							\
	MOPT_UNION

D 7
void getmntopts __P((const char *, const struct mntopt *, int *));
E 7
I 7
void getmntopts __P((const char *, const struct mntopt *, int *, int *));
extern int getmnt_silent;
E 7
E 1
