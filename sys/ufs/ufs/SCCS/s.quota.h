h63452
s 00002/00002/00179
d D 8.3 94/08/19 00:13:57 mckusick 24 23
c convert freelist and hash list to use queue.h macros
e
s 00023/00023/00158
d D 8.2 94/07/08 22:57:09 mckusick 23 22
c changes for 64-bit machines (from bostic)
e
s 00002/00002/00179
d D 8.1 93/06/11 16:28:38 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00180
d D 7.12 92/07/20 00:57:52 mckusick 21 20
c new hashing scheme
e
s 00001/00001/00180
d D 7.11 92/06/25 13:18:41 mckusick 20 19
c quotactl now takes a real uid_t
e
s 00052/00027/00129
d D 7.10 91/11/01 18:15:07 bostic 19 18
c prototype cleanups
e
s 00009/00000/00147
d D 7.9 91/02/22 11:15:11 donn 18 17
c Prototype declarations.
e
s 00002/00005/00145
d D 7.8 90/09/27 13:58:07 mckusick 17 16
c eliminate things that cannot be included multiple times
e
s 00004/00000/00146
d D 7.7 90/09/11 11:16:31 mckusick 16 15
c protect with _QUOTA_
e
s 00001/00011/00145
d D 7.6 90/06/28 22:30:01 bostic 15 14
c new copyright notice
e
s 00001/00000/00155
d D 7.5 90/05/06 17:39:56 mckusick 14 13
c specify the group in which quota files are created
e
s 00097/00097/00058
d D 7.4 90/05/02 19:30:12 mckusick 13 12
c overhaul to provide for new quota environment
e
s 00010/00005/00145
d D 7.3 88/06/27 18:55:09 bostic 12 11
c install approved copyright notice
e
s 00008/00002/00142
d D 7.2 88/05/20 12:24:26 bostic 11 10
c add Berkeley specific header
e
s 00001/00001/00143
d D 7.1 86/06/04 23:27:02 mckusick 10 9
c 4.3BSD release version
e
s 00002/00002/00142
d D 6.3 85/10/28 15:04:19 karels 9 8
c use proper types for uids, gids
e
s 00007/00001/00137
d D 6.2 85/06/08 15:05:42 mckusick 8 7
c Add copyright
e
s 00000/00000/00138
d D 6.1 83/07/29 06:13:42 sam 7 6
c 4.2 distribution
e
s 00002/00006/00136
d D 4.6 83/05/27 16:15:52 sam 6 5
c move #ifdef's around for easier inclusion
e
s 00007/00004/00135
d D 4.5 83/05/24 10:26:23 sam 5 4
c retry #ifdef's so stuff can be included without #define QUOTA
e
s 00064/00042/00075
d D 4.4 83/05/21 23:18:40 sam 4 3
c make disk block fields long; cleanup
e
s 00024/00120/00093
d D 4.3 83/05/21 16:01:42 sam 3 2
c sorry robert; the devil made me do it (purge mush)
e
s 00003/00000/00210
d D 4.2 82/10/20 01:16:18 root 2 1
c lint
e
s 00210/00000/00000
d D 4.1 82/07/16 16:33:09 kre 1 0
c date and time created 82/07/16 16:33:09 by kre
e
u
U
f i 
t
T
I 1
D 3
/*	%M%	Melb %I%	%E%	*/
E 3
I 3
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
/*
D 10
 * Copyright (c) 1982 Regents of the University of California.
E 10
I 10
D 22
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 10
D 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
I 13
 * This code is derived from software contributed to Berkeley by
 * Robert Elz at The University of Melbourne.
 *
E 13
D 15
 * Redistribution and use in source and binary forms are permitted
D 12
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 12
I 12
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 12
E 11
 *
 *	%W% (Berkeley) %G%
 */
E 8
E 3

I 16
#ifndef _QUOTA_
#define _QUOTA_

E 16
I 2
D 5
#ifdef QUOTA
E 5
E 2
/*
D 4
 *	Various junk to do with various quotas (etc) imposed upon
 *	the average user (big brother finally hits unix)
E 4
I 4
D 13
 * MELBOURNE DISC QUOTAS
E 13
I 13
 * Definitions for disk quotas imposed on the average user
 * (big brother finally hits UNIX).
E 13
E 4
 *
D 4
 *	The following structure exists in core for each logged on user
 *	It contains global junk relevant to that user's quotas
E 4
I 4
D 13
 * Various junk to do with various quotas (etc) imposed upon
 * the average user (big brother finally hits UNIX).
E 4
 *
D 4
 *	The u_quota field of each user struct contains a pointer to
 *	the quota struct relevant to the current process, this is changed
 *	by 'setuid' sys call, &/or by the Q_SETUID quota() call
E 4
I 4
 * The following structure exists in core for each logged on user.
 * It contains global junk relevant to that user's quotas.
 *
 * The u_quota field of each user struct contains a pointer to
 * the quota struct relevant to the current process, this is changed
 * by 'setuid' sys call, &/or by the Q_SETUID quota() call.
E 13
I 13
D 19
 * The following constants define the amount of time given a user
 * before the soft limits are treated as hard limits (usually resulting
 * in an allocation failure). The timer is started when the user crosses
 * their soft limit, it is reset when they go below their soft limit.
E 19
I 19
 * The following constants define the amount of time given a user before the
 * soft limits are treated as hard limits (usually resulting in an allocation
 * failure). The timer is started when the user crosses their soft limit, it
 * is reset when they go below their soft limit.
E 19
E 13
E 4
 */
D 3

typedef	long	class_t;

struct quinfo {
	u_short	qu_shares;	/* allocated shares (MUSH) */
	short	qu_plim;	/* process limit */
	long	qu_syflags;	/* system permission flags */
	float	qu_usage;	/* current resource usage (MUSH) */
	class_t	qu_class;	/* user classes (MUSH) */
};

E 3
D 5
#ifdef	KERNEL
E 5
I 5
D 6
#ifdef KERNEL
E 6
E 5
D 13
struct quota {
D 3
	struct	quota	*q_forw;	/* hash chain - MUST be first */
	struct	quota	*q_back;	/* hash chain - MUST be last */
	char	q_flg;			/* struct management flags */
	char	q_lcnt;			/* count of logins for user */
E 3
I 3
	struct	quota *q_forw, *q_back;	/* hash chain, MUST be first */
E 3
	short	q_cnt;			/* ref count (# processes) */
D 9
	short	q_uid;			/* real uid of owner */
E 9
I 9
	uid_t	q_uid;			/* real uid of owner */
E 9
D 3
	short	q_nice;			/* nice added to p_cpu (MUSH) */
	short	q_acnt;			/* count of 'at' processes (MUSH) */
	union	{
		struct	{
			long	Q_rate;	/* recent work rate (MUSH) */
			long	Q_cost;	/* cost in recent period (MUSH) */
		} q_s1;
		struct	{
			struct quota *Q_freef;
			struct quota **Q_freeb;
		} q_s2;
	} q_u;
	struct	quinfo q_uinfo;		/* user limits & usage (MUSH) */
E 3
I 3
D 4
	char	q_flg;			/* struct management flags */
E 4
I 4
	int	q_flags;		/* struct management flags */
E 4
#define	Q_LOCK	0x01		/* quota struct locked (for disc i/o) */
#define	Q_WANT	0x02		/* issue a wakeup when lock goes off */
#define	Q_NEW	0x04		/* new quota - no proc1 msg sent yet */
#define	Q_NDQ	0x08		/* account has NO disc quota */
	struct	quota *q_freef, **q_freeb;
E 3
	struct	dquot *q_dq[NMOUNT];	/* disc quotas for mounted filesys's */
};
E 13
I 13
D 23
#define	MAX_IQ_TIME	(7*24*60*60)	/* 1 week */
#define	MAX_DQ_TIME	(7*24*60*60)	/* 1 week */
E 23
I 23
#define	MAX_IQ_TIME	(7*24*60*60)	/* seconds in 1 week */
#define	MAX_DQ_TIME	(7*24*60*60)	/* seconds in 1 week */
E 23
E 13
D 4
#define	NOQUOT	((struct quota *) 0)
D 3
#define	q_rate		q_u.q_s1.Q_rate
#define	q_cost		q_u.q_s1.Q_cost
#define	q_freef		q_u.q_s2.Q_freef
#define	q_freeb		q_u.q_s2.Q_freeb
#define	q_shares	q_uinfo.qu_shares
#define	q_plim		q_uinfo.qu_plim
#define	q_syflags	q_uinfo.qu_syflags
#define	q_usage		q_uinfo.qu_usage
#define	q_class		q_uinfo.qu_class
E 3
#endif
E 4

I 5
D 6
#ifdef QUOTA
E 6
E 5
D 3
#define	QF_KASYNC	0x02		/* kill async procs at logout */
#define	QF_FASTTY	0x04		/* permitted to raise tty speed */
#define	QF_NASYNC	0x08		/* nice async procs at logout */
#define	QF_MODTTY	0x10		/* permitted to modify other tty */
#define	QF_UMASK	0x20		/* not permitted to alter umask */

E 3
D 4
#ifdef	KERNEL
E 4
I 4
D 13
#define	NOQUOTA	((struct quota *) 0)
E 13
I 13
/*
D 19
 * The following constants define the usage of the quota file array
 * in the ufsmount structure and dquot array in the inode structure.
 * The semantics of the elements of these arrays are defined in the
 * routine getinoquota; the remainder of the quota code treats them
 * generically and need not be inspected when changing the size of
 * the array.
E 19
I 19
 * The following constants define the usage of the quota file array in the
 * ufsmount structure and dquot array in the inode structure.  The semantics
 * of the elements of these arrays are defined in the routine getinoquota;
 * the remainder of the quota code treats them generically and need not be
 * inspected when changing the size of the array.
E 19
 */
#define	MAXQUOTAS	2
#define	USRQUOTA	0	/* element used for user quotas */
#define	GRPQUOTA	1	/* element used for group quotas */
E 13

I 6
D 13
#if defined(KERNEL) && defined(QUOTA)
E 6
E 4
D 3
struct quota *quota, *quotaNQUOTA;
E 3
I 3
struct	quota *quota, *quotaNQUOTA;
E 3
int	nquota;
D 3
struct quota *getquota(), *qfind();
E 3
I 3
struct	quota *getquota(), *qfind();
E 13
I 13
/*
 * Definitions for the default names of the quotas files.
 */
#define INITQFNAMES { \
	"user",		/* USRQUOTA */ \
	"group",	/* GRPQUOTA */ \
	"undefined", \
};
D 17
#ifndef KERNEL
char *qfname = "quota";
char *qfextension[] = INITQFNAMES;
I 14
char *quotagroup = "operator";
E 14
E 13
E 3
#endif
E 17
I 17
D 19
#define QUOTAFILENAME "quota"
#define QUOTAGROUP "operator"
E 19
I 19
#define	QUOTAFILENAME	"quota"
#define	QUOTAGROUP	"operator"
E 19
E 17
I 5
D 6
#endif
E 6
E 5

D 3
/*	q_flg flags	*/
#define	Q_LOCK		0x01		/* quota struct locked (for disc i/o) */
#define	Q_WANT		0x02		/* issue a wakeup when lock goes off */
#define	Q_NEW		0x04		/* new quota - no proc1 msg sent yet */
#define	Q_NDQ		0x08		/* account has NO disc quota */

E 3
/*
D 4
 *	The following structure defines the format of the disc quota file
 *	(as it appears on disc) - the file is an array of these structures
 *	indexed by user number. A sys call (setquota) establishes the
 *	inode for each applicable file (a pointer is retained in the mount
 *	structure)
E 4
I 4
D 13
 * The following structure defines the format of the disc quota file
 * (as it appears on disc) - the file is an array of these structures
 * indexed by user number.  The setquota sys call establishes the inode
 * for each quota file (a pointer is retained in the mount structure).
E 4
 *
D 4
 *	nb: warning fields contain the number of warnings left before
 *		allocation is halted completely
E 4
I 4
 * The following constants define the number of warnings given a user
 * before the soft limits are treated as hard limits (usually resulting
 * in an allocation failure).  The warnings are normally manipulated
 * each time a user logs in through the Q_DOWARN quota call.  If
 * the user logs in and is under the soft limit the warning count
 * is reset to MAX_*_WARN, otherwise a message is printed and the
 * warning count is decremented.  This makes MAX_*_WARN equivalent to
 * the number of logins before soft limits are treated as hard limits.
E 13
I 13
D 19
 * Command definitions for the 'quotactl' system call.
 * The commands are broken into a main command defined below
 * and a subcommand that is used to convey the type of
 * quota that is being manipulated (see above).
E 19
I 19
 * Command definitions for the 'quotactl' system call.  The commands are
 * broken into a main command defined below and a subcommand that is used
 * to convey the type of quota that is being manipulated (see above).
E 19
E 13
E 4
 */
D 3

E 3
D 4
typedef	unsigned short	dlim_t;

struct	dqblk {
	dlim_t	dqb_ilim;	/* max num allocated inodes + 1 */
	dlim_t	dqb_iq;		/* preferred inode limit */
	dlim_t	dqb_inod;	/* current num allocated inodes */
	dlim_t	dqb_iwarn;	/* # warnings about excessive inodes */
E 4
I 3
D 13
#define	MAX_IQ_WARN	3
E 3
D 4
	dlim_t	dqb_blim;	/* abs limit on disc blks alloc */
	dlim_t	dqb_quot;	/* preferred limit on disc blks */
	dlim_t	dqb_blks;	/* current block count */
	dlim_t	dqb_dwarn;	/* # warnings about excessive disc use */
E 4
D 3
};
#define	MAX_IQ_WARN	3
E 3
#define	MAX_DQ_WARN	3
E 13
I 13
#define SUBCMDMASK	0x00ff
#define SUBCMDSHIFT	8
#define	QCMD(cmd, type)	(((cmd) << SUBCMDSHIFT) | ((type) & SUBCMDMASK))
E 13
I 4

I 13
#define	Q_QUOTAON	0x0100	/* enable quotas */
#define	Q_QUOTAOFF	0x0200	/* disable quotas */
#define	Q_GETQUOTA	0x0300	/* get limits and usage */
#define	Q_SETQUOTA	0x0400	/* set limits and usage */
#define	Q_SETUSE	0x0500	/* set usage */
#define	Q_SYNC		0x0600	/* sync disk copy of a filesystems quotas */

/*
 * The following structure defines the format of the disk quota file
 * (as it appears on disk) - the file is an array of these structures
 * indexed by user or group number.  The setquota system call establishes
 * the vnode for each quota file (a pointer is retained in the ufsmount
 * structure).
 */
E 13
D 23
struct	dqblk {
D 13
	u_long	dqb_bhardlimit;	/* absolute limit on disc blks alloc */
	u_long	dqb_bsoftlimit;	/* preferred limit on disc blks */
E 13
I 13
	u_long	dqb_bhardlimit;	/* absolute limit on disk blks alloc */
	u_long	dqb_bsoftlimit;	/* preferred limit on disk blks */
E 13
	u_long	dqb_curblocks;	/* current block count */
D 13
	u_short	dqb_ihardlimit;	/* maximum # allocated inodes + 1 */
	u_short	dqb_isoftlimit;	/* preferred inode limit */
	u_short	dqb_curinodes;	/* current # allocated inodes */
	u_char	dqb_bwarn;	/* # warnings left about excessive disc use */
	u_char	dqb_iwarn;	/* # warnings left about excessive inodes */
E 13
I 13
	u_long	dqb_ihardlimit;	/* maximum # allocated inodes + 1 */
	u_long	dqb_isoftlimit;	/* preferred inode limit */
	u_long	dqb_curinodes;	/* current # allocated inodes */
	time_t	dqb_btime;	/* time limit for excessive disk use */
	time_t	dqb_itime;	/* time limit for excessive files */
E 23
I 23
struct dqblk {
	u_int32_t dqb_bhardlimit;	/* absolute limit on disk blks alloc */
	u_int32_t dqb_bsoftlimit;	/* preferred limit on disk blks */
	u_int32_t dqb_curblocks;	/* current block count */
	u_int32_t dqb_ihardlimit;	/* maximum # allocated inodes + 1 */
	u_int32_t dqb_isoftlimit;	/* preferred inode limit */
	u_int32_t dqb_curinodes;	/* current # allocated inodes */
	time_t	  dqb_btime;		/* time limit for excessive disk use */
	time_t	  dqb_itime;		/* time limit for excessive files */
E 23
E 13
E 4
I 3
};
E 3

I 13
D 19
#ifdef KERNEL
E 19
E 13
/*
D 4
 *	The following structure records disc usage for a user on a filesystem
 *	There is one allocated for each quota that exists on any filesystem
 *	for the current user. A cache is kept of other recently used entries.
E 4
I 4
D 13
 * The following structure records disc usage for a user on a filesystem.
 * There is one allocated for each quota that exists on any filesystem
 * for the current user. A cache is kept of other recently used entries.
E 13
I 13
 * The following structure records disk usage for a user or group on a
 * filesystem. There is one allocated for each quota that exists on any
 * filesystem for the current user or group. A cache is kept of recently
 * used entries.
E 13
E 4
 */
D 3

E 3
D 23
struct	dquot {
D 3
	struct	dquot	*dq_forw;	/* MUST be first entry */
	struct	dquot	*dq_back;	/* MUST be second entry */
E 3
I 3
D 21
	struct	dquot *dq_forw, *dq_back;/* MUST be first entry */
E 21
I 21
	struct	dquot *dq_forw, **dq_back; /* hash list */
E 21
E 3
D 13
	union	{
D 3
		struct quota *Dq_own;	/* the quota that points to this */
		struct {
			struct dquot *Dq_freef;	/* forward free chain ptr */
			struct dquot **Dq_freeb;/* backward free chain ptr */
E 3
I 3
		struct	quota *Dq_own;	/* the quota that points to this */
		struct {		/* free list */
			struct	dquot *Dq_freef, **Dq_freeb;
E 3
		} dq_f;
	} dq_u;
D 4
	short	dq_flg;
E 4
I 4
	short	dq_flags;
E 13
I 13
	struct	dquot *dq_freef, **dq_freeb; /* free list */
	short	dq_flags;		/* flags, see below */
	short	dq_cnt;			/* count of active references */
	short	dq_spare;		/* unused spare padding */
	short	dq_type;		/* quota type of this dquot */
	u_long	dq_id;			/* identifier this applies to */
E 23
I 23
struct dquot {
D 24
	struct	dquot *dq_forw, **dq_back;	/* hash list */
	struct	dquot *dq_freef, **dq_freeb;	/* free list */
E 24
I 24
	LIST_ENTRY(dquot) dq_hash;	/* hash list */
	TAILQ_ENTRY(dquot) dq_freelist;	/* free list */
E 24
	u_int16_t dq_flags;		/* flags, see below */
	u_int16_t dq_cnt;		/* count of active references */
	u_int16_t dq_spare;		/* unused spare padding */
	u_int16_t dq_type;		/* quota type of this dquot */
	u_int32_t dq_id;		/* identifier this applies to */
E 23
	struct	ufsmount *dq_ump;	/* filesystem that this is taken from */
	struct	dqblk dq_dqb;		/* actual usage & quotas */
};
/*
 * Flag values.
 */
E 13
E 4
I 3
#define	DQ_LOCK		0x01		/* this quota locked (no MODS) */
#define	DQ_WANT		0x02		/* wakeup on unlock */
#define	DQ_MOD		0x04		/* this quota modified since read */
#define	DQ_FAKE		0x08		/* no limits here, just usage */
#define	DQ_BLKS		0x10		/* has been warned about blk limit */
#define	DQ_INODS	0x20		/* has been warned about inode limit */
E 3
D 13
	short	dq_cnt;			/* count of active references */
D 9
	short	dq_uid;			/* user this applies to */
E 9
I 9
	uid_t	dq_uid;			/* user this applies to */
E 9
	dev_t	dq_dev;			/* filesystem this relates to */
	struct dqblk dq_dqb;		/* actual usage & quotas */
};
I 5

D 6
#ifdef QUOTA
E 6
E 5
#define	dq_own		dq_u.Dq_own
#define	dq_freef	dq_u.dq_f.Dq_freef
#define	dq_freeb	dq_u.dq_f.Dq_freeb
E 13
I 13
/*
 * Shorthand notation.
 */
E 13
D 4
#define	dq_ilim		dq_dqb.dqb_ilim
#define	dq_iq		dq_dqb.dqb_iq
#define	dq_inod		dq_dqb.dqb_inod
E 4
I 4
#define	dq_bhardlimit	dq_dqb.dqb_bhardlimit
#define	dq_bsoftlimit	dq_dqb.dqb_bsoftlimit
#define	dq_curblocks	dq_dqb.dqb_curblocks
#define	dq_ihardlimit	dq_dqb.dqb_ihardlimit
#define	dq_isoftlimit	dq_dqb.dqb_isoftlimit
#define	dq_curinodes	dq_dqb.dqb_curinodes
D 13
#define	dq_bwarn	dq_dqb.dqb_bwarn
E 4
#define	dq_iwarn	dq_dqb.dqb_iwarn
E 13
I 13
#define	dq_btime	dq_dqb.dqb_btime
#define	dq_itime	dq_dqb.dqb_itime
E 13
D 4
#define	dq_blim		dq_dqb.dqb_blim
#define	dq_quot		dq_dqb.dqb_quot
#define	dq_blks		dq_dqb.dqb_blks
#define	dq_dwarn	dq_dqb.dqb_dwarn
E 4
I 4

E 4
D 13
#define	NODQUOT		((struct dquot *) 0)
#define	LOSTDQUOT	((struct dquot *) 1)

D 5
#ifdef	KERNEL
E 5
I 5
D 6
#ifdef KERNEL
E 6
I 6
#if defined(KERNEL) && defined(QUOTA)
E 6
E 5
D 3
struct	dquot	*dquot, *dquotNDQUOT;
E 3
I 3
struct	dquot *dquot, *dquotNDQUOT;
E 3
int	ndquot;
D 3
struct	dquot	*discquota(), *inoquota(), *dqalloc();
E 3
I 3
struct	dquot *discquota(), *inoquota(), *dqalloc(), *dqp();
E 3
D 6
#endif
E 6
I 5
#endif
E 5

E 13
D 3
/*	dq_flg flags	*/
#define	DQ_LOCK		0x01		/* this quota locked (no MODS) */
#define	DQ_WANT		0x02		/* wakeup on unlock */
#define	DQ_MOD		0x04		/* this quota modified since read */
#define	DQ_FAKE		0x08		/* no limits here, just usage */
#define	DQ_BLKS		0x10		/* has been warned about blk limit */
#define	DQ_INODS	0x20		/* has been warned about inode limit */

E 3
/*
D 4
 * Commands for the 'quota' system call
E 4
I 4
D 13
 * Definitions for the 'quota' system call.
E 13
I 13
D 19
 * If the system has never checked for a quota for this file,
 * then it is set to NODQUOT. Once a write attempt is made
 * the inode pointer is set to reference a dquot structure.
E 19
I 19
D 23
 * If the system has never checked for a quota for this file, then it is set
 * to NODQUOT.  Once a write attempt is made the inode pointer is set to
 * reference a dquot structure.
E 23
I 23
 * If the system has never checked for a quota for this file, then it is
 * set to NODQUOT.  Once a write attempt is made the inode pointer is set
 * to reference a dquot structure.
E 23
E 19
E 13
E 4
 */
D 13
#define	Q_SETDLIM	1	/* set disc limits & usage */
#define	Q_GETDLIM	2	/* get disc limits & usage */
#define	Q_SETDUSE	3	/* set disc usage only */
D 4
#define	Q_SYNC		4	/* update disc copy if quota usages */
E 4
I 4
#define	Q_SYNC		4	/* update disc copy of quota usages */
E 4
D 3
#define	Q_LOGIN		5	/* Count this as a login process */
#define	Q_LCOUNT	6	/* get count of login processes */
#define	Q_PCOUNT	7	/* get count of processes */
#define	Q_USAGE		8	/* get current usage */
#define	Q_SFLAGS	9	/* set system flags */
#define	Q_SUSAGE	10	/* set usage */
#define	Q_SPLIMIT	11	/* set process limit */
#define	Q_ISLOGIN	12	/* is this a login process ?? */
#define	Q_SCLASS	13	/* set user class */
#define	Q_SCURCL	14	/* set current system classes */
#define	Q_GCURCL	15	/* get current system classes */
E 3
#define	Q_SETUID	16	/* change proc to use quotas for uid */
D 3
#define	Q_FLOGIN	17	/* "fake" login (counts as 1, but isn't) */
#define	Q_SETCOST	18	/* set system charge rates */
#define	Q_GETCOST	19	/* get system charge rates */
#define	Q_SSHARE	20	/* set shares */
#define	Q_SUINFO	21	/* set user info */
#define	Q_GUINFO	22	/* get user info */
#define	Q_ATJOB		23	/* this process is an 'at' job (background) */
#define	Q_ACOUNT	24	/* return count of procs descended from ATJ */
E 3
#define	Q_SETWARN	25	/* alter inode/block warning counts */
#define	Q_DOWARN	26	/* warn user about excessive space/inodes */
E 13
I 13
D 23
#define	NODQUOT		((struct dquot *) 0)
E 23
I 23
#define	NODQUOT		NULL
E 23
E 13
I 4

/*
D 13
 * Used in Q_SETDUSE.
E 13
I 13
 * Flags to chkdq() and chkiq()
E 13
 */
D 13
struct	dqusage {
	u_short	du_curinodes;
	u_long	du_curblocks;
};
E 13
I 13
#define	FORCE	0x01	/* force usage changes independent of limits */
#define	CHOWN	0x02	/* (advisory) change initiated by chown */
E 13

/*
D 13
 * Used in Q_SETWARN.
E 13
I 13
 * Macros to avoid subroutine calls to trivial functions.
E 13
 */
D 13
struct	dqwarn {
	u_char	dw_bwarn;
	u_char	dw_iwarn;
};
E 13
I 13
D 19
#ifndef DIAGNOSTIC
#define	DQREF(dq)	(dq)->dq_cnt++
#else
E 19
I 19
#ifdef DIAGNOSTIC
E 19
#define	DQREF(dq)	dqref(dq)
D 19
#endif /* DIAGNOSTIC */
I 18

E 19
#else
I 19
#define	DQREF(dq)	(dq)->dq_cnt++
#endif
E 19

#include <sys/cdefs.h>

I 19
struct dquot;
struct inode;
struct mount;
struct proc;
struct ucred;
struct ufsmount;
struct vnode;
E 19
__BEGIN_DECLS
D 19
int	quotactl __P((const char *, int, int, void *));
E 19
I 19
int	chkdq __P((struct inode *, long, struct ucred *, int));
int	chkdqchg __P((struct inode *, long, struct ucred *, int));
int	chkiq __P((struct inode *, long, struct ucred *, int));
int	chkiqchg __P((struct inode *, long, struct ucred *, int));
void	dqflush __P((struct vnode *));
int	dqget __P((struct vnode *,
	    u_long, struct ufsmount *, int, struct dquot **));
void	dqinit __P((void));
void	dqref __P((struct dquot *));
void	dqrele __P((struct vnode *, struct dquot *));
int	dqsync __P((struct vnode *, struct dquot *));
int	getinoquota __P((struct inode *));
int	getquota __P((struct mount *, u_long, int, caddr_t));
int	qsync __P((struct mount *mp));
int	quotaoff __P((struct proc *, struct mount *, int));
int	quotaon __P((struct proc *, struct mount *, int, caddr_t));
int	setquota __P((struct mount *, u_long, int, caddr_t));
int	setuse __P((struct mount *, u_long, int, caddr_t));
D 20
int	ufs_quotactl __P((struct mount *, int, u_int, caddr_t, struct proc *));
E 20
I 20
int	ufs_quotactl __P((struct mount *, int, uid_t, caddr_t, struct proc *));
E 20
E 19
__END_DECLS

E 18
D 19
#endif /* KERNEL */
E 19
I 19
#ifdef DIAGNOSTIC
__BEGIN_DECLS
void	chkdquot __P((struct inode *));
__END_DECLS
#endif

E 19
I 16
#endif /* _QUOTA_ */
E 16
E 13
E 4
D 3
#define	Q_KILL		27	/* send signal to procs attatched to quota */
#define	Q_NICE		28	/* set niceness for procs attatched to quota */

/*
 * current class information
 *
 *	records sched biasing for classes that are to have priority
 *	enhanced or degraded
 */

#define	NCLASS	8

struct qclass {
	class_t	class;		/* classes this applies to */
	long	cost;		/* +/- mod to cost incurred */
	short	maxn;		/* in this class, no nice > this */
	short	minn;		/* in this class, no nice < this */
};

#ifdef	KERNEL
struct	qclass	curclass[NCLASS];
E 3
D 5
#endif
E 5
D 3

/*
 * Flag definitions for u_qflags in user struct (u_qflags)
 */
#define	QUF_LOGIN	0x0001		/* this process incremented login cnt */
#define	QUF_ATJ		0x0002		/* this process descended from atrun */
I 2

#endif QUOTA
E 3
E 2
E 1
