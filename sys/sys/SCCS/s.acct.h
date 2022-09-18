h27601
s 00002/00000/00050
d D 8.4 95/01/09 18:16:07 cgd 20 19
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00019/00018/00031
d D 8.3 94/07/10 22:50:48 bostic 19 18
c changes for 64-bit machines
e
s 00005/00000/00044
d D 8.2 94/01/21 17:25:02 bostic 18 17
c add USL's copyright notice
e
s 00002/00002/00042
d D 8.1 93/06/02 19:52:21 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00032/00014
d D 7.3 91/02/15 14:28:31 bostic 16 15
c add Berkeley specific copyright notice
e
s 00001/00002/00045
d D 7.2 89/05/09 16:35:02 mckusick 15 14
c merge in vnodes
e
s 00001/00001/00046
d D 7.1 86/06/04 23:19:39 mckusick 14 13
c 4.3BSD release version
e
s 00002/00002/00045
d D 6.4 85/10/28 15:03:59 karels 13 12
c use proper types for uids, gids
e
s 00007/00001/00040
d D 6.3 85/06/08 14:54:06 mckusick 12 11
c Add copyright
e
s 00007/00000/00034
d D 6.2 84/12/12 09:19:16 karels 11 10
c add AHZ for units of comp_t's
e
s 00000/00000/00034
d D 6.1 83/07/29 06:11:40 sam 10 9
c 4.2 distribution
e
s 00000/00003/00034
d D 4.6 83/07/25 22:47:47 sam 9 8
c purge unused definitions
e
s 00005/00000/00032
d D 4.5 82/10/10 17:12:01 root 8 7
c header file cleanup while moving vax files to their own directory
e
s 00008/00002/00024
d D 4.4 82/07/12 17:14:49 kre 7 5
c new acct flags (more info in no more space in acct file)
e
s 00015/00002/00024
d R 4.4 82/07/12 16:59:52 kre 6 5
c added new acct flags, also var decls for disk space low ...
e
s 00004/00005/00022
d D 4.3 81/03/09 00:25:58 wnj 5 4
c lint
e
s 00001/00001/00026
d D 4.2 81/02/19 21:39:00 wnj 4 3
c %G%->%E%
e
s 00000/00000/00027
d D 4.1 80/11/09 17:00:31 bill 3 2
c stamp for 4bsd
e
s 00001/00001/00026
d D 3.2 80/06/07 02:55:51 bill 2 1
c %H%->%G%
e
s 00027/00000/00000
d D 3.1 80/04/09 16:23:15 bill 1 0
c date and time created 80/04/09 16:23:15 by bill
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%H%	*/
E 2
I 2
D 4
/*	%M%	%I%	%G%	*/
E 4
I 4
D 12
/*	%M%	%I%	%E%	*/
E 12
I 12
D 16
/*
D 14
 * Copyright (c) 1982 Regents of the University of California.
E 14
I 14
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 16
I 16
/*-
D 17
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
D 19
 * Copyright (c) 1990, 1993
E 19
I 19
 * Copyright (c) 1990, 1993, 1994
E 19
 *	The Regents of the University of California.  All rights reserved.
I 18
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 18
E 17
E 16
 *
I 16
 * %sccs.include.redist.c%
 *
E 16
 *	%W% (Berkeley) %G%
 */
E 12
E 4
E 2

/*
D 5
 * Accounting structures
E 5
I 5
D 16
 * Accounting structures;
 * these use a comp_t type which is a 3 bits base 8
 * exponent, 13 bit fraction ``floating point'' number.
I 11
 * Units are 1/AHZ seconds.
E 16
I 16
 * Accounting structures; these use a comp_t type which is a 3 bits base 8
 * exponent, 13 bit fraction ``floating point'' number.  Units are 1/AHZ
 * seconds.
E 16
E 11
E 5
 */
I 5
D 16
typedef	u_short comp_t;
E 16
I 16
D 19
typedef u_short comp_t;
E 19
I 19
typedef u_int16_t comp_t;
E 19
E 16
E 5

D 5
typedef	unsigned short comp_t;	/* "floating pt": 3 bits base 8 exp, 13 bits fraction */
E 5
D 16
struct	acct
{
	char	ac_comm[10];		/* Accounting command name */
	comp_t	ac_utime;		/* Accounting user time */
	comp_t	ac_stime;		/* Accounting system time */
	comp_t	ac_etime;		/* Accounting elapsed time */
	time_t	ac_btime;		/* Beginning time */
D 13
	short	ac_uid;			/* Accounting user ID */
	short	ac_gid;			/* Accounting group ID */
E 13
I 13
	uid_t	ac_uid;			/* Accounting user ID */
	gid_t	ac_gid;			/* Accounting group ID */
E 13
	short	ac_mem;			/* average memory usage */
	comp_t	ac_io;			/* number of disk IO blocks */
	dev_t	ac_tty;			/* control typewriter */
	char	ac_flag;		/* Accounting flag */
E 16
I 16
struct acct {
D 19
	char	ac_comm[10];	/* command name */
	comp_t	ac_utime;	/* user time */
	comp_t	ac_stime;	/* system time */
	comp_t	ac_etime;	/* elapsed time */
	time_t	ac_btime;	/* starting time */
	uid_t	ac_uid;		/* user id */
	gid_t	ac_gid;		/* group id */
	short	ac_mem;		/* average memory usage */
	comp_t	ac_io;		/* count of IO blocks */
	dev_t	ac_tty;		/* controlling tty */
#define	AFORK	0x01			/* forked but not execed */
#define	ASU	0x02			/* used super-user permissions */
#define	ACOMPAT	0x04			/* used compatibility mode */
#define	ACORE	0x08			/* dumped core */
#define	AXSIG	0x10			/* killed by a signal */
	char	ac_flag;	/* accounting flags */
E 19
I 19
	char	  ac_comm[10];	/* command name */
	comp_t	  ac_utime;	/* user time */
	comp_t	  ac_stime;	/* system time */
	comp_t	  ac_etime;	/* elapsed time */
	time_t	  ac_btime;	/* starting time */
	uid_t	  ac_uid;	/* user id */
	gid_t	  ac_gid;	/* group id */
	u_int16_t ac_mem;	/* average memory usage */
	comp_t	  ac_io;	/* count of IO blocks */
	dev_t	  ac_tty;	/* controlling tty */

#define	AFORK	0x01		/* fork'd but not exec'd */
#define	ASU	0x02		/* used super-user permissions */
#define	ACOMPAT	0x04		/* used compatibility mode */
#define	ACORE	0x08		/* dumped core */
#define	AXSIG	0x10		/* killed by a signal */
	u_int8_t  ac_flag;	/* accounting flags */
E 19
E 16
};
D 5

extern	struct	acct	acctbuf;
extern	struct	inode	*acctp;		/* inode of accounting file */
E 5

D 7
#define	AFORK	01		/* has executed fork, but no exec */
#define	ASU	02		/* used super-user privileges */
E 7
I 7
D 16
#define	AFORK	0001		/* has executed fork, but no exec */
#define	ASU	0002		/* used super-user privileges */
#define	ACOMPAT	0004		/* used compatibility mode */
#define	ACORE	0010		/* dumped core */
#define	AXSIG	0020		/* killed by a signal */
I 11

E 16
/*
D 16
 * 1/AHZ is the granularity of the data encoded in the various
 * comp_t fields.  This is not necessarily equal to hz.
E 16
I 16
 * 1/AHZ is the granularity of the data encoded in the comp_t fields.
 * This is not necessarily equal to hz.
E 16
 */
D 16
#define AHZ 64
E 16
I 16
#define	AHZ	64
E 16
E 11

D 9
#define	ACCTLO	30		/* acctg off when space < this */
#define	ACCTHI	100		/* acctg resumes at this level */
I 8

E 9
#ifdef KERNEL
D 15
struct	acct	acctbuf;
struct	inode	*acctp;
E 15
I 15
D 16
struct	vnode	*acctp;
E 16
I 16
struct vnode	*acctp;
I 20

int	acct_process __P((struct proc *p));
E 20
E 16
E 15
#endif
E 8
E 7
E 1
