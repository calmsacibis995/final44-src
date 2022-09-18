h29527
s 00002/00001/00254
d D 8.15 95/05/19 15:04:45 pendry 93 92
c accounting for simple locks and unlocks
e
s 00002/00001/00253
d D 8.14 95/05/17 21:19:48 pendry 92 91
c accounting for locks and unlocks
e
s 00009/00001/00245
d D 8.13 95/01/09 18:16:05 cgd 91 90
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00006/00001/00240
d D 8.12 94/08/22 18:15:39 mckusick 90 89
c cannot zero p_hash (without causing grief)
e
s 00003/00003/00238
d D 8.11 94/08/20 17:56:50 mckusick 89 88
c extern allproc and zombproc; eliminate unused pidhashmask
e
s 00022/00017/00219
d D 8.10 94/08/20 16:50:13 mckusick 88 87
c use new queue.h data structures
e
s 00002/00003/00234
d D 8.9 94/05/03 23:17:28 mckusick 87 86
c really minor nits
e
s 00005/00000/00232
d D 8.8 94/01/21 17:25:16 bostic 86 85
c add USL's copyright notice
e
s 00003/00003/00229
d D 8.7 94/01/04 16:16:40 bostic 85 84
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00005/00002/00227
d D 8.6 93/12/13 12:19:33 pendry 84 82
c add p_textvp to track vnode of executable (for procfs)
e
s 00005/00002/00227
d R 8.6 93/12/12 16:34:55 mckusick 83 82
c add p_textvp to track vnode of executable (for procfs)
e
s 00006/00006/00223
d D 8.5 93/09/26 08:59:48 bostic 82 81
c sort P* flags, replace comment on P_WAITED
e
s 00030/00032/00199
d D 8.4 93/09/23 15:29:22 bostic 81 80
c changes for 4.4BSD-Lite requested by USL
e
s 00136/00133/00095
d D 8.3 93/09/21 07:14:19 bostic 80 79
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00001/00227
d D 8.2 93/09/03 16:20:43 mckusick 79 78
c setpri => more descriptive resetpriority
e
s 00002/00002/00226
d D 8.1 93/06/02 19:54:44 bostic 78 77
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00225
d D 7.38 93/05/28 01:43:00 mckusick 77 76
c reorganize to allow pid_t to become u_long
e
s 00000/00005/00228
d D 7.37 92/12/27 08:53:55 hibler 76 75
c SHPUX moved to machine-dep flags
e
s 00008/00009/00225
d D 7.36 92/07/08 00:44:00 torek 75 74
c delete p_utime and p_stime; allproc becomes volatile; lint
e
s 00018/00014/00216
d D 7.35 92/06/20 12:00:04 mckusick 74 73
c move zero'ed things into zero area; add new accounting fields;
c add SPROFIL and SGUID flags; ptrace attach fields; dump unused fields
e
s 00001/00001/00229
d D 7.34 92/05/31 21:21:42 pendry 73 72
c p_dupfd has to be signed
e
s 00003/00003/00227
d D 7.33 92/02/28 17:24:07 bostic 72 71
c sleep, tsleep and wakeup really take void *'s, not caddr_t's.
e
s 00001/00012/00229
d D 7.32 92/02/17 23:45:53 mckusick 71 70
c selinfo moves out to select.h
e
s 00012/00000/00229
d D 7.31 92/02/15 17:05:32 mckusick 70 69
c define struct selinfo; function prototypes for selrecord and selwakeup
e
s 00008/00001/00221
d D 7.30 92/02/05 17:23:49 torek 69 68
c p_regs moves out of proc; add prototypes
e
s 00001/00001/00221
d D 7.29 91/10/31 17:12:38 bostic 68 67
c nothing; comment revision
e
s 00001/00000/00221
d D 7.28 91/05/30 15:05:45 mckusick 67 66
c add SADVLCK to note POSIX style advisory lock
e
s 00005/00004/00216
d D 7.27 91/05/05 18:10:49 bostic 66 65
c new copyright; att/bsd/shared
e
s 00004/00004/00216
d D 7.26 91/05/04 15:09:08 karels 65 64
c p_addr is now struct user *
e
s 00053/00082/00167
d D 7.25 91/04/20 17:55:18 karels 64 63
c add mdproc substruct; mv kinfo_proc to separate header;
c compress flags and rm unused/worthless; curproc is here
e
s 00125/00075/00124
d D 7.24 91/03/17 15:34:05 karels 63 62
c more-or-less working with new proc & user structs
e
s 00002/00001/00197
d D 7.23 91/01/10 23:35:48 mckusick 62 61
c add pointer to dynamically allocated file descriptors
e
s 00006/00010/00192
d D 7.22 90/12/05 15:52:02 mckusick 61 60
c update for new VM
e
s 00001/00001/00201
d D 7.21 90/09/05 10:24:15 mckusick 60 59
c p_dupfd is signed
e
s 00007/00000/00195
d D 7.20 90/07/27 22:40:41 karels 59 58
c parameterize max proc id
e
s 00000/00003/00195
d D 7.19 90/06/25 10:31:04 karels 58 57
c move MAXCOMLEN, MAXLOGNAME to param.h from proc.h; delete CANBSIZ
e
s 00002/00002/00196
d D 7.18 90/06/22 17:19:12 karels 57 56
c remove cursig (use xstat for stop signal/wait); dupfd for grotty
c way that open of /dev/fd/* works
e
s 00005/00000/00193
d D 7.17 90/05/23 18:57:39 marc 56 55
c add macros to reference and release a session structure
e
s 00000/00002/00193
d D 7.16 90/05/18 16:00:45 marc 55 54
c delete PROC_JOBC - now done inline in fixjobc()
e
s 00005/00002/00190
d D 7.15 90/05/18 15:32:13 marc 54 53
c add eproc flag (use spare, hooray!)
e
s 00003/00004/00189
d D 7.14 90/05/18 09:25:15 mckusick 53 52
c SPTECHG needed for hp300
e
s 00008/00008/00185
d D 7.13 90/05/15 22:28:44 mckusick 52 51
c size_t => segsz_t for bostic
e
s 00002/00001/00191
d D 7.12 90/05/09 12:03:11 mckusick 51 50
c merge in hp300 support
e
s 00004/00001/00188
d D 7.11 90/04/05 14:39:08 karels 50 49
c add SSINTR for wakeup; move utime/stime from user to proc (marc)
e
s 00012/00013/00177
d D 7.10 90/03/20 15:58:51 marc 49 48
c proc hash changes, 86 SLOGIN and SPTECHG
e
s 00032/00003/00158
d D 7.9 90/02/16 17:09:32 marc 48 47
c checkpoint state as of 5pm fri; moving kinfo stuff to proc.h (by sklower)
e
s 00006/00004/00155
d D 7.8 89/11/20 18:12:51 marc 47 46
c controlling terminal is a vnode
e
s 00011/00007/00148
d D 7.7 89/08/26 16:42:30 karels 46 45
c posix signals need real uid here; add saved effective uid, gid
e
s 00001/00001/00154
d D 7.6 89/05/29 12:33:20 mckusick 45 44
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00002/00002/00153
d D 7.5 89/05/09 16:35:25 mckusick 44 43
c merge in vnodes
e
s 00004/00003/00151
d D 7.4 89/05/01 23:22:46 marc 43 42
c KTRACE support -- also, make s_count an int
e
s 00035/00004/00119
d D 7.3 88/10/18 15:23:08 marc 42 41
c posix style job control - new process groups
e
s 00004/00000/00119
d D 7.2 86/10/13 21:43:03 karels 41 40
c merge in tahoe system
e
s 00001/00001/00118
d D 7.1 86/06/04 23:26:14 mckusick 40 39
c 4.3BSD release version
e
s 00000/00001/00119
d D 6.6 86/04/12 13:37:08 karels 39 38
c don't need p1br
e
s 00001/00001/00119
d D 6.5 85/10/28 15:04:10 karels 38 37
c use proper types for uids, gids
e
s 00007/00001/00113
d D 6.4 85/06/08 15:04:12 mckusick 37 36
c Add copyright
e
s 00001/00000/00113
d D 6.3 85/05/05 23:26:43 karels 36 35
c add p_p1br (again)
e
s 00006/00002/00107
d D 6.2 84/06/06 23:10:47 sam 35 33
c check in for mike: add kre's changes for separate lists of 
c free, zombie, and active processes
e
s 00001/00000/00109
d R 6.2 84/05/10 09:39:08 karels 34 33
c add pointer to last used proc slot
e
s 00000/00000/00109
d D 6.1 83/07/29 06:13:28 sam 33 32
c 4.2 distribution
e
s 00000/00003/00109
d D 4.24 83/07/01 02:24:59 root 32 31
c purge #if sun's
e
s 00006/00006/00106
d D 4.23 83/06/02 15:52:29 sam 31 30
c new signals
e
s 00003/00013/00109
d D 4.22 83/05/22 17:22:14 sam 30 29
c purge mush; make quota's permanent
e
s 00003/00000/00119
d D 4.21 83/05/18 02:42:13 sam 29 28
c sun changes
e
s 00001/00001/00118
d D 4.20 83/01/20 17:01:22 sam 28 27
c no more SDLYU (yeah)
e
s 00001/00001/00118
d D 4.19 82/12/09 18:53:47 sam 27 26
c put SOWEUPC back for profil
e
s 00001/00013/00118
d D 4.18 82/11/13 23:08:31 sam 26 25
c merge 4.1b and 4.1c
e
s 00011/00001/00120
d D 4.17 82/10/31 16:27:39 root 25 24
c SPTECHG and u_short p_xstat and QUOTA/MUSH grot
e
s 00004/00001/00117
d D 4.16 82/10/21 17:30:41 root 24 23
c lint
e
s 00001/00002/00117
d D 4.15 82/09/08 08:11:31 root 23 22
c label_t now a structure; other misc changes
e
s 00001/00000/00118
d D 4.14 82/09/06 23:01:17 root 22 21
c more timer stuff
e
s 00008/00039/00110
d D 4.13 82/09/04 09:26:35 root 21 20
c get rid of cruddy exit stuff: use a mbuf
e
s 00003/00000/00146
d D 4.12 82/07/17 22:03:44 kre 20 19
c include mush.h & mu_msg.h (to obtain size of mmsgbuf)
e
s 00029/00022/00117
d D 4.11 82/07/16 16:57:40 kre 19 18
c added new fields for QUOTA & mu_msg + SLOGIN flag
e
s 00001/00001/00138
d D 4.10 82/01/30 19:14:49 wnj 18 17
c remove SDETACH
e
s 00001/00000/00138
d D 4.9 81/10/17 16:14:30 wnj 17 16
c cleanup (mpx removal, old tty removal, beginnings of select)
e
s 00002/00002/00136
d D 4.8 81/04/23 01:24:39 wnj 16 15
c SANOM->SSEQL
e
s 00001/00000/00137
d D 4.7 81/04/13 20:40:02 root 15 14
c add p_maxrss
e
s 00002/00002/00135
d D 4.6 81/03/09 00:27:20 wnj 14 13
c lint
e
s 00002/00001/00135
d D 4.5 81/02/27 00:02:07 wnj 13 12
c move to pointer base to allow dyn allocation
e
s 00000/00006/00136
d D 4.4 81/02/26 04:30:11 wnj 12 11
c cosmetics
e
s 00001/00001/00141
d D 4.3 81/02/19 21:41:51 wnj 11 10
c %G%->%E%
e
s 00001/00000/00141
d D 4.2 81/02/15 20:37:30 wnj 10 9
c ast and hard/soft clock
e
s 00000/00000/00141
d D 4.1 80/11/09 17:01:28 bill 9 8
c stamp for 4bsd
e
s 00002/00002/00139
d D 3.7 80/10/13 09:59:25 bill 8 6
c %cpu stuff
e
s 00001/00001/00140
d R 3.7 80/09/18 00:27:05 bill 7 6
c DETACH->ORPHAN
e
s 00021/00019/00120
d D 3.6 80/07/11 08:24:31 bill 6 5
c define SDETACH and SNUSIG
e
s 00001/00001/00138
d D 3.5 80/06/07 02:59:52 bill 5 4
c %H%->%G%
e
s 00001/00001/00138
d D 3.4 80/05/18 11:39:19 bill 4 3
c s/int/long/ in p->p_sig
e
s 00010/00004/00129
d D 3.3 80/05/15 17:17:52 bill 3 2
c new fields for signals
e
s 00001/00000/00132
d D 3.2 80/04/14 18:26:44 bill 2 1
c added STIMO
e
s 00132/00000/00000
d D 3.1 80/04/09 16:24:59 bill 1 0
c date and time created 80/04/09 16:24:59 by bill
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%H%	*/
E 5
I 5
D 11
/*	%M%	%I%	%G%	*/
E 11
I 11
D 37
/*	%M%	%I%	%E%	*/
E 37
I 37
D 66
/*
D 40
 * Copyright (c) 1982 Regents of the University of California.
E 40
I 40
D 46
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 46
I 46
D 63
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 63
I 63
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
E 63
E 46
E 40
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 66
I 66
/*-
D 78
 * Copyright (c) 1986, 1989, 1991 The Regents of the University of California.
 * All rights reserved.
E 78
I 78
 * Copyright (c) 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 86
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 86
E 78
 *
 * %sccs.include.redist.c%
E 66
 *
 *	%W% (Berkeley) %G%
 */
E 37
E 11
E 5

I 63
D 64
#include "vm/vm.h"			/* XXX */
E 64
I 64
D 85
#ifndef _PROC_H_
#define	_PROC_H_
E 85
I 85
#ifndef _SYS_PROC_H_
#define	_SYS_PROC_H_
E 85
E 64

I 64
D 80
#include <machine/proc.h>		/* machine-dependent proc substruct */
I 71
#include <sys/select.h>			/* for struct selinfo */
E 80
I 80
#include <machine/proc.h>		/* Machine-dependent proc substruct. */
#include <sys/select.h>			/* For struct selinfo. */
I 88
#include <sys/queue.h>
E 88
E 80
E 71

E 64
E 63
I 25
D 26
#ifdef vax		/* GROT */
#ifndef QUOTA
#define	QUOTA		/* GROT */
#endif
#ifndef MUSH
#define	MUSH		/* GROT */
#endif
#endif			/* GROT */

E 25
I 20
#include "mush.h"
#include "mu_msg.h"

E 26
E 20
/*
I 42
 * One structure allocated per session.
 */
struct	session {
D 47
	struct	proc *s_leader;	/* pointer to session leader */
D 43
	short	s_count;	/* number of pgrps in session */
E 43
I 43
	int	s_count;	/* number of pgrps in session */
E 47
I 47
D 63
	int	s_count;	/* ref cnt; pgrps in session */
	struct	proc *s_leader;	/* session leader */
	struct	vnode *s_ttyvp;	/* vnode of controlling terminal */
	struct	tty *s_ttyp;	/* controlling terminal */
E 63
I 63
D 80
	int	s_count;		/* ref cnt; pgrps in session */
	struct	proc *s_leader;		/* session leader */
	struct	vnode *s_ttyvp;		/* vnode of controlling terminal */
	struct	tty *s_ttyp;		/* controlling terminal */
	char	s_login[MAXLOGNAME];	/* setlogin() name */
E 80
I 80
	int	s_count;		/* Ref cnt; pgrps in session. */
	struct	proc *s_leader;		/* Session leader. */
	struct	vnode *s_ttyvp;		/* Vnode of controlling terminal. */
	struct	tty *s_ttyp;		/* Controlling terminal. */
	char	s_login[MAXLOGNAME];	/* Setlogin() name. */
E 80
E 63
E 47
E 43
};

/*
 * One structure allocated per process group.
 */
struct	pgrp {
D 63
	struct	pgrp *pg_hforw;	/* forward link in hash bucket */
	struct	proc *pg_mem;	/* pointer to pgrp members */
E 63
I 63
D 80
	struct	pgrp *pg_hforw;		/* forward link in hash bucket */
	struct	proc *pg_mem;		/* pointer to pgrp members */
E 63
	struct	session *pg_session;	/* pointer to session */
D 63
	pid_t	pg_id;		/* pgrp id */
E 63
I 63
	pid_t	pg_id;			/* pgrp id */
E 80
I 80
D 88
	struct	pgrp *pg_hforw;		/* Forward link in hash bucket. */
	struct	proc *pg_mem;		/* Pointer to pgrp members. */
E 88
I 88
	LIST_ENTRY(pgrp) pg_hash;	/* Hash chain. */
	LIST_HEAD(, proc) pg_members;	/* Pointer to pgrp members. */
E 88
	struct	session *pg_session;	/* Pointer to session. */
	pid_t	pg_id;			/* Pgrp id. */
E 80
E 63
D 49
	short	pg_jobc;	/* # procs qualifying pgrp for job control */
E 49
I 49
	int	pg_jobc;	/* # procs qualifying pgrp for job control */
E 49
};

/*
E 42
D 63
 * One structure allocated per active
 * process. It contains all data needed
 * about the process while the
 * process may be swapped out.
 * Other per process data (user.h)
 * is swapped with the process.
E 63
I 63
 * Description of a process.
D 80
 * This structure contains the information needed to manage a thread
 * of control, known in UN*X as a process; it has references to substructures
E 80
I 80
 *
 * This structure contains the information needed to manage a thread of
 * control, known in UN*X as a process; it has references to substructures
E 80
 * containing descriptions of things that the process uses, but may share
 * with related processes.  The process structure and the substructures
D 65
 * are always addressible except for those marked "(proc only)" below,
E 65
I 65
 * are always addressible except for those marked "(PROC ONLY)" below,
E 65
 * which might be addressible only on a processor on which the process
 * is running.
E 63
D 12
 *
 * NB: OFFSETS HERE ARE ALSO DEFINED IN proc.m
E 12
 */
I 48
D 63

E 63
D 58
#define	MAXCOMLEN	16		/* <= MAXNAMLEN, >= sizeof(ac_comm) */
#define	MAXLOGNAME	12		/* >= UT_NAMESIZE */

E 58
E 48
D 21
struct	proc
{
E 21
I 21
struct	proc {
E 21
D 63
	struct	proc *p_link;	/* linked list of running processes */
E 63
I 63
D 80
	struct	proc *p_link;		/* doubly-linked run/sleep queue */
E 80
I 80
D 81
	struct	proc *p_link;		/* Doubly-linked run/sleep queue. */
E 80
E 63
	struct	proc *p_rlink;
I 35
D 63
	struct	proc *p_nxt;	/* linked list of allocated proc slots */
	struct	proc **p_prev;		/* also zombies, and free proc's */
E 35
D 61
	struct	pte *p_addr;	/* u-area kernel map address */
E 61
I 61
	caddr_t	p_addr;		/* kernel virtual address of u-area */
E 61
	char	p_usrpri;	/* user-priority based on p_cpu and p_nice */
	char	p_pri;		/* priority, negative is high */
	char	p_cpu;		/* cpu usage for scheduling */
	char	p_stat;
	char	p_time;		/* resident time for scheduling */
	char	p_nice;		/* nice for cpu usage */
	char	p_slptime;	/* time since last block */
D 3
	int	p_flag;
E 3
I 3
D 57
	char	p_cursig;
E 57
I 57
D 60
	u_char	p_dupfd;	/* sideways return value from fdopen XXX */
E 60
I 60
	char	p_dupfd;	/* sideways return value from fdopen XXX */
E 60
E 57
E 3
D 4
	int	p_sig;		/* signals pending to this process */
E 4
I 4
D 31
	long	p_sig;		/* signals pending to this process */
E 4
D 3
	int	p_ignsig;	/* ignored signals */
E 3
I 3
	long	p_siga0;	/* low bit of 2 bit signal action */
	long	p_siga1;	/* high bit of 2 bit signal action */
#define	p_ignsig p_siga0	/* ignored signal mask */
E 31
I 31
	int	p_sig;		/* signals pending to this process */
	int	p_sigmask;	/* current signal mask */
	int	p_sigignore;	/* signals being ignored */
	int	p_sigcatch;	/* signals being caught by user */
E 63
I 63
D 80
	struct	proc *p_nxt;		/* linked list of active procs */
	struct	proc **p_prev;		/*    and zombies */
E 80
I 80
	struct	proc *p_nxt;		/* Linked list of active procs */
E 81
I 81
	struct	proc *p_forw;		/* Doubly-linked run/sleep queue. */
	struct	proc *p_back;
D 88
	struct	proc *p_next;		/* Linked list of active procs */
E 81
	struct	proc **p_prev;		/*    and zombies. */
E 88
I 88
	LIST_ENTRY(proc) p_list;	/* List of all processes. */
E 88
E 80

	/* substructures: */
D 80
	struct	pcred *p_cred;		/* process owner's identity */
	struct	filedesc *p_fd;		/* ptr to open files structure */
D 65
	struct	pstats *p_stats;	/* accounting/statistics (proc only) */
E 65
I 65
	struct	pstats *p_stats;	/* accounting/statistics (PROC ONLY) */
E 65
	struct	plimit *p_limit;	/* process limits */
	struct	vmspace *p_vmspace;	/* address space */
D 65
	struct	sigacts *p_sigacts;	/* signal actions, state (proc only) */
E 65
I 65
	struct	sigacts *p_sigacts;	/* signal actions, state (PROC ONLY) */
E 80
I 80
	struct	pcred *p_cred;		/* Process owner's identity. */
	struct	filedesc *p_fd;		/* Ptr to open files structure. */
	struct	pstats *p_stats;	/* Accounting/statistics (PROC ONLY). */
	struct	plimit *p_limit;	/* Process limits. */
	struct	vmspace *p_vmspace;	/* Address space. */
	struct	sigacts *p_sigacts;	/* Signal actions, state (PROC ONLY). */
E 80
E 65

#define	p_ucred		p_cred->pc_ucred
#define	p_rlimit	p_limit->pl_rlimit

E 63
E 31
D 80
	int	p_flag;
E 3
D 38
	short	p_uid;		/* user id, used to direct tty signals */
E 38
I 38
D 46
	uid_t	p_uid;		/* user id, used to direct tty signals */
E 46
I 46
D 63
	uid_t	p_uid;		/* effective user id */
	uid_t	p_ruid;		/* real user id */
	uid_t	p_svuid;	/* saved effective user id */
	gid_t	p_rgid;		/* real group id */
	gid_t	p_svgid;	/* saved effective group id */
E 63
I 63
	char	p_stat;
E 80
I 80
	int	p_flag;			/* P_* flags. */
	char	p_stat;			/* S* process status. */
E 80
D 74
/*	char	p_space; */
E 74
I 74
D 77
	char	p_pad1;
E 77
I 77
	char	p_pad1[3];
E 77
E 74

E 63
E 46
E 38
D 42
	short	p_pgrp;		/* name of process group leader */
	short	p_pid;		/* unique process id */
	short	p_ppid;		/* process id of parent */
E 42
I 42
D 80
	pid_t	p_pid;		/* unique process id */
D 63
	pid_t	p_ppid;		/* process id of parent */
E 42
D 21
	short	p_poip;		/* count of page outs in progress */
	short	p_szpt;		/* copy of page table size */
E 21
I 21
D 25
	short	p_xstat;	/* Exit status for wait */
E 25
I 25
D 57
	u_short	p_xstat;	/* Exit status for wait */
E 57
I 57
	u_short	p_xstat;	/* Exit status for wait; also stop signal */
E 57
E 25
D 46
	struct	rusage *p_ru;	/* mbuf holding exit information */
E 46
I 46
	struct	rusage *p_ru;	/* exit information */
E 46
D 30
	short	p_poip;	/* page outs in progress */
	short	p_szpt;	/* copy of page table size */
E 30
I 30
D 61
	short	p_poip;		/* page outs in progress */
	short	p_szpt;		/* copy of page table size */
E 30
E 21
D 52
	size_t	p_tsize;	/* size of text (clicks) */
	size_t	p_dsize;	/* size of data space (clicks) */
I 51
	size_t	p_mmsize;	/* size of mapmem beyond p_dsize (clicks) */
E 51
	size_t	p_ssize;	/* copy of stack size (clicks) */
	size_t 	p_rssize; 	/* current resident set size in clicks */
I 15
	size_t	p_maxrss;	/* copy of u.u_limit[MAXRSS] */
E 15
	size_t	p_swrss;	/* resident set size before last swap */
E 52
I 52
	segsz_t p_tsize;	/* size of text (clicks) */
	segsz_t p_dsize;	/* size of data space (clicks) */
	segsz_t p_mmsize;	/* size of mapmem beyond p_dsize (clicks) */
	segsz_t p_ssize;	/* copy of stack size (clicks) */
E 61
I 61
	struct	vm_map *p_map;	/* VM address map */
	caddr_t	p_shm;		/* SYS5 shared memory private data */
	int	p_thread;	/* id for this "thread" (Mach glue) XXX */
D 62
	int	p_pad1[2];
E 62
I 62
	struct	filedesc *p_fd;	/* ptr to open files structure */
	int	p_pad1;
E 62
E 61
	segsz_t p_rssize; 	/* current resident set size in clicks */
	segsz_t p_maxrss;	/* copy of u.u_limit[MAXRSS] */
	segsz_t p_swrss;	/* resident set size before last swap */
E 52
	swblk_t	p_swaddr;	/* disk address of u area when swapped */
	caddr_t p_wchan;	/* event process is awaiting */
D 61
	struct	text *p_textp;	/* pointer to text structure */
D 21
	int	p_clktim;	/* time to alarm clock signal */
E 21
	struct	pte *p_p0br;	/* page table base P0BR */
I 36
D 39
	struct	pte *p_p1br;	/* page table base P1BR */
E 39
E 36
	struct	proc *p_xlink;	/* linked list of procs sharing same text */
E 61
I 61
	int	pad2[3];
E 61
D 8
	short	p_faults;	/* faults in last second */
	short	p_aveflt;	/* average of p_faults into past */
E 8
I 8
D 46
	short	p_cpticks;	/* ticks of cpu time */
E 46
I 46
	int	p_cpticks;	/* ticks of cpu time */
E 46
D 45
	float	p_pctcpu;	/* %cpu for this process during p_time */
E 45
I 45
	fixpt_t	p_pctcpu;	/* %cpu for this process during p_time */
E 45
E 8
	short	p_ndx;		/* proc index for memall (because of vfork) */
E 63
D 49
	short	p_idhash;	/* hashed based on p_pid for kill+exit+... */
E 49
I 49
	struct	proc *p_hash;	/* hashed based on p_pid for kill+exit+... */
I 63
	struct	proc *p_pgrpnxt; /* pointer to next process in process group */
E 63
E 49
I 3
	struct	proc *p_pptr;	/* pointer to process structure of parent */
I 19
D 63
	struct	proc *p_cptr;	/* pointer to youngest living child */
E 63
	struct	proc *p_osptr;	/* pointer to older sibling processes */
E 80
I 80
	pid_t	p_pid;			/* Process identifier. */
D 88
	struct	proc *p_hash;	 /* Hashed based on p_pid for kill+exit+... */
	struct	proc *p_pgrpnxt; /* Pointer to next process in process group. */
	struct	proc *p_pptr;	 /* Pointer to process structure of parent. */
	struct	proc *p_osptr;	 /* Pointer to older sibling processes. */
E 88
I 88
	LIST_ENTRY(proc) p_pglist;	/* List of processes in pgrp. */
	struct	proc *p_pptr;	 	/* Pointer to parent process. */
	LIST_ENTRY(proc) p_sibling;	/* List of sibling processes. */
	LIST_HEAD(, proc) p_children;	/* Pointer to list of children. */
E 88
E 80
I 63

D 80
/* The following fields are all zeroed upon creation in fork */
E 80
I 80
/* The following fields are all zeroed upon creation in fork. */
E 80
D 88
#define	p_startzero	p_ysptr
E 63
D 80
	struct	proc *p_ysptr;	/* pointer to younger siblings */
I 42
D 63
	struct 	pgrp *p_pgrp;	/* pointer to process group */
#define p_session p_pgrp->pg_session
#define p_pgid	p_pgrp->pg_id
	struct	proc *p_pgrpnxt; /* pointer to next process in process group */
E 42
I 26
	struct	itimerval p_realtimer;
E 63
I 63
	struct	proc *p_cptr;	/* pointer to youngest living child */
I 74
	pid_t	p_oppid;	/* save parent pid during ptrace XXX */
D 77
	short	p_dupfd;	/* sideways return value from fdopen XXX */
E 77
I 77
	int	p_dupfd;	/* sideways return value from fdopen XXX */
E 80
I 80
	struct	proc *p_ysptr;	 /* Pointer to younger siblings. */
	struct	proc *p_cptr;	 /* Pointer to youngest living child. */
E 88
I 88
#define	p_startzero	p_oppid

E 88
	pid_t	p_oppid;	 /* Save parent pid during ptrace. XXX */
	int	p_dupfd;	 /* Sideways return value from fdopen. XXX */
E 80
E 77
E 74

	/* scheduling */
D 80
	u_int	p_cpu;		/* cpu usage for scheduling */
	int	p_cpticks;	/* ticks of cpu time */
	fixpt_t	p_pctcpu;	/* %cpu for this process during p_time */
	caddr_t p_wchan;	/* event process is awaiting */
I 74
	char	*p_wmesg;	/* reason for sleep */
E 74
	u_int	p_time;		/* resident/nonresident time for swapping */
	u_int	p_slptime;	/* time since last block */
E 80
I 80
D 81
	u_int	p_cpu;		 /* Time averaged value of p_cpticks. */
E 81
I 81
	u_int	p_estcpu;	 /* Time averaged value of p_cpticks. */
E 81
	int	p_cpticks;	 /* Ticks of cpu time. */
D 81
	fixpt_t	p_pctcpu;	 /* %cpu for this process during p_time */
E 81
I 81
	fixpt_t	p_pctcpu;	 /* %cpu for this process during p_swtime */
E 81
	void	*p_wchan;	 /* Sleep address. */
	char	*p_wmesg;	 /* Reason for sleep. */
D 81
	u_int	p_time;		 /* Time swapped in or out. */
E 81
I 81
	u_int	p_swtime;	 /* Time swapped in or out. */
E 81
	u_int	p_slptime;	 /* Time since last blocked. */
E 80

D 80
	struct	itimerval p_realtimer;	/* alarm timer */
D 74
	struct	timeval p_utime;	/* user time */
	struct	timeval p_stime;	/* system time */
E 74
I 74
	struct	timeval p_rtime;	/* real time */
	u_quad_t p_uticks;		/* statclock hits in user mode */
	u_quad_t p_sticks;		/* statclock hits in system mode */
	u_quad_t p_iticks;		/* statclock hits processing intr */
E 80
I 80
	struct	itimerval p_realtimer;	/* Alarm timer. */
	struct	timeval p_rtime;	/* Real time. */
	u_quad_t p_uticks;		/* Statclock hits in user mode. */
	u_quad_t p_sticks;		/* Statclock hits in system mode. */
	u_quad_t p_iticks;		/* Statclock hits processing intr. */
E 80
E 74

E 63
I 30
D 51
	struct	quota *p_quota;	/* quotas for this process */
E 51
I 43
D 47
	int	p_traceflag;	/* kernel tracing flags (facilities) */
E 47
I 47
D 80
	int	p_traceflag;	/* kernel trace points */
E 47
D 44
	struct	inode *p_tracep;/* trace to inode */
E 44
I 44
	struct	vnode *p_tracep;/* trace to vnode */
E 80
I 80
	int	p_traceflag;		/* Kernel trace points. */
	struct	vnode *p_tracep;	/* Trace to vnode. */
E 80
I 63

D 80
	int	p_sig;		/* signals pending to this process */
E 80
I 80
D 81
	int	p_sig;			/* Signals arrived but not delivered. */
E 81
I 81
	int	p_siglist;		/* Signals arrived but not delivered. */
E 81
E 80

I 74
D 75
	struct	timeval p_utime; /* user time */
	struct	timeval p_stime; /* system time */
	long	p_spare[2];	/* tmp spares to avoid shifting eproc */
E 75
I 75
D 77
	long	p_spare[6];	/* tmp spares to avoid shifting eproc */
E 77
I 77
D 80
	long	p_spare[6];	/* pad to 256 and to avoid shifting eproc */
E 80
I 80
D 84
	long	p_spare[6];		/* pad to 256, avoid shifting eproc. */
E 84
I 84
	struct	vnode *p_textvp;	/* Vnode of executable. */
I 88
D 90
	LIST_ENTRY(proc) p_hash;	/* Hash chain. */
E 90
E 88
E 84
E 80
E 77
E 75

I 84
D 88
	long	p_spare[5];		/* pad to 256, avoid shifting eproc. */
E 88
I 88
D 92
	long	p_spare[3];		/* pad to 256, avoid shifting eproc. */
E 92
I 92
D 93
	int	p_locks;		/* DEBUG: lockmgr count of held locks */
E 93
I 93
	short	p_locks;		/* DEBUG: lockmgr count of held locks */
	short	p_simple_locks;		/* DEBUG: count of held simple locks */
E 93
	long	p_spare[2];		/* pad to 256, avoid shifting eproc. */
E 92
E 88

E 84
E 74
D 80
/* end area that is zeroed on creation */
E 80
I 80
/* End area that is zeroed on creation. */
E 80
D 90
#define	p_endzero	p_startcopy
E 90
I 90
#define	p_endzero	p_hash.le_next

	/*
	 * Not copied, not zero'ed.
	 * Belongs after p_pid, but here to avoid shifting proc elements.
	 */
	LIST_ENTRY(proc) p_hash;	/* Hash chain. */
E 90

D 80
/* The following fields are all copied upon creation in fork */
	sigset_t p_sigmask;	/* current signal mask */
E 80
I 80
/* The following fields are all copied upon creation in fork. */
D 84
	sigset_t p_sigmask;	/* Current signal mask. */
E 84
E 80
#define	p_startcopy	p_sigmask
I 84

	sigset_t p_sigmask;	/* Current signal mask. */
E 84
D 80
	sigset_t p_sigignore;	/* signals being ignored */
	sigset_t p_sigcatch;	/* signals being caught by user */
E 80
I 80
	sigset_t p_sigignore;	/* Signals being ignored. */
	sigset_t p_sigcatch;	/* Signals being caught by user. */
E 80

D 80
	u_char	p_pri;		/* priority, negative is high */
	u_char	p_usrpri;	/* user-priority based on p_cpu and p_nice */
	char	p_nice;		/* nice for cpu usage */
E 80
I 80
D 81
	u_char	p_pri;		/* Process priority. */
E 81
I 81
	u_char	p_priority;	/* Process priority. */
E 81
	u_char	p_usrpri;	/* User-priority based on p_cpu and p_nice. */
	char	p_nice;		/* Process "nice" value. */
E 80
D 64
/*	char	p_space; */
E 64
I 64
D 74
/*	char	p_space1; */
E 74
I 74
	char	p_comm[MAXCOMLEN+1];
E 74
E 64

D 80
	struct 	pgrp *p_pgrp;	/* pointer to process group */
E 80
I 80
	struct 	pgrp *p_pgrp;	/* Pointer to process group. */
E 80
E 63
I 48
D 74
	char	p_comm[MAXCOMLEN+1];
E 74
D 63
	char	p_logname[MAXLOGNAME];
	char	*p_wmesg;
I 50
	struct	timeval p_utime; /* user time */
	struct	timeval p_stime; /* system time */
E 50
E 48
E 44
E 43
I 41
#if defined(tahoe)
	int	p_ckey;		/* code cache key */
	int	p_dkey;		/* data cache key */
#endif
E 63
I 63

D 80
/* end area that is copied on creation */
E 80
I 80
/* End area that is copied on creation. */
E 80
D 74
#define	p_endcopy	p_wmesg
	char	*p_wmesg;	/* reason for sleep */
E 74
I 74
#define	p_endcopy	p_thread
E 74
D 80
	int	p_thread;	/* id for this "thread" (Mach glue) XXX */
D 65
	caddr_t	p_addr;		/* kernel virtual address of u-area */
E 65
I 65
	struct	user *p_addr;	/* kernel virtual addr of u-area (PROC ONLY) */
E 65
D 74
	swblk_t	p_swaddr;	/* disk address of u area when swapped */
E 74
D 69
	int	*p_regs;	/* saved registers during syscall/trap */
E 69
I 64
	struct	mdproc p_md;	/* any machine-dependent fields */
E 80
I 80
D 91
	int	p_thread;	/* Id for this "thread"; Mach glue. XXX */
E 91
I 91

	void	*p_thread;	/* Id for this "thread"; Mach glue. XXX */
E 91
	struct	user *p_addr;	/* Kernel virtual addr of u-area (PROC ONLY). */
	struct	mdproc p_md;	/* Any machine-dependent fields. */
E 80
E 64

D 80
	u_short	p_xstat;	/* Exit status for wait; also stop signal */
D 73
	u_short	p_dupfd;	/* sideways return value from fdopen XXX */
E 73
I 73
D 74
	short	p_dupfd;	/* sideways return value from fdopen XXX */
E 74
E 73
	u_short	p_acflag;	/* accounting flags */
D 64
/*	u_short	p_space; */
E 64
I 64
D 74
/*	short	p_space2; */
E 74
E 64
	struct	rusage *p_ru;	/* exit information XXX */
E 80
I 80
	u_short	p_xstat;	/* Exit status for wait; also stop signal. */
	u_short	p_acflag;	/* Accounting flags. */
	struct	rusage *p_ru;	/* Exit information. XXX */
E 80
D 87

E 87
D 74
	long	p_spare[4];	/* tmp spares to avoid shifting eproc */
E 74
E 63
E 41
E 30
I 29
D 32
#ifdef sun
	struct	context *p_ctx;	/* pointer to current context */
#endif
E 32
E 29
E 26
I 24
D 30
#ifdef QUOTA
E 24
	struct	quota *p_quota;	/* quotas for this process (MUSH) */
I 24
#endif
#ifdef MUSH
E 24
	mmsgbuf	p_mb;		/* pending message */
	int	p_msgflgs;	/* message flags */
I 24
#endif
E 30
E 24
I 21
D 26
	struct	itimerval p_realtimer;
E 26
I 22
D 23
	int	p_XXX;		/* XXX */
E 22
	struct	timeval p_seltimer;
E 23
I 23
D 24
	int	p_SSS[3];
E 24
E 23
E 21
E 19
E 3
};

I 63
#define	p_session	p_pgrp->pg_session
#define	p_pgid		p_pgrp->pg_id

D 80
/* MOVE TO ucred.h? */
E 80
I 80
/* Status values. */
#define	SIDL	1		/* Process being created by fork. */
#define	SRUN	2		/* Currently runnable. */
#define	SSLEEP	3		/* Sleeping on an address. */
#define	SSTOP	4		/* Process debugging or suspension. */
#define	SZOMB	5		/* Awaiting collection by parent. */

/* These flags are kept in p_flags. */
D 81
#define	SADVLCK	0x0000001	/* Process may hold a POSIX advisory lock. */
#define	SCTTY	0x0000002	/* Has a controlling terminal. */
#define	SLOAD	0x0000004	/* Loaded into memory. */
#define	SNOCLDSTOP 0x0000008	/* No SIGCHLD when children stop. */
#define	SPPWAIT	0x0000010	/* Parent is waiting for child to exec/exit. */
#define	SPROFIL	0x0000020	/* Has started profiling. */
#define	SSEL	0x0000040	/* Selecting; wakeup/waiting danger. */
#define	SSINTR	0x0000080	/* Sleep is interruptible. */
#define	SSYS	0x0000100	/* System proc: no sigs, stats or swapping. */
#define	STIMO	0x0000200	/* Timing out during sleep. */
#define	STRC	0x0000400	/* Process being debugged. */
#define	SUGID	0x0000800	/* Had set id privileges since last exec. */
#define	SWEXIT	0x0001000	/* Working on exiting. */
#define	SWTED	0x0002000	/* Process being debugged. */
#define SEXEC	0x0004000	/* Process called exec. */
E 81
I 81
#define	P_ADVLOCK	0x00001	/* Process may hold a POSIX advisory lock. */
#define	P_CONTROLT	0x00002	/* Has a controlling terminal. */
#define	P_INMEM		0x00004	/* Loaded into memory. */
#define	P_NOCLDSTOP	0x00008	/* No SIGCHLD when children stop. */
#define	P_PPWAIT	0x00010	/* Parent is waiting for child to exec/exit. */
#define	P_PROFIL	0x00020	/* Has started profiling. */
#define	P_SELECT	0x00040	/* Selecting; wakeup/waiting danger. */
#define	P_SINTR		0x00080	/* Sleep is interruptible. */
D 82
#define	P_SYSTEM	0x00100	/* System proc: no sigs, stats or swapping. */
#define	P_TIMEOUT	0x00200	/* Timing out during sleep. */
#define	P_TRACED	0x00400	/* Debugged process being traced. */
#define	P_SUGID		0x00800	/* Had set id privileges since last exec. */
#define	P_WEXIT		0x01000	/* Working on exiting. */
#define	P_WAITED	0x02000	/* Process being debugged. */
E 82
I 82
#define	P_SUGID		0x00100	/* Had set id privileges since last exec. */
#define	P_SYSTEM	0x00200	/* System proc: no sigs, stats or swapping. */
#define	P_TIMEOUT	0x00400	/* Timing out during sleep. */
#define	P_TRACED	0x00800	/* Debugged process being traced. */
#define	P_WAITED	0x01000	/* Debugging process has waited for child. */
#define	P_WEXIT		0x02000	/* Working on exiting. */
E 82
D 87
#define P_EXEC		0x04000	/* Process called exec. */
E 87
I 87
#define	P_EXEC		0x04000	/* Process called exec. */
E 87
E 81

D 81
/* The following three should probably be changed into a hold count. */
#define	SKEEP	0x0008000	/* Another flag to prevent swap out. */
#define	SLOCK	0x0010000	/* Process being swapped out. */
#define	SPHYSIO	0x0020000	/* Doing physical I/O. */
E 81
I 81
/* Should probably be changed into a hold count. */
#define	P_NOSWAP	0x08000	/* Another flag to prevent swap out. */
#define	P_PHYSIO	0x10000	/* Doing physical I/O. */
E 81

D 81
/* The following should be moved to machine-dependent areas. */
#define	SOWEUPC	0x0040000	/* Owe process an addupc() call at next ast. */
E 81
I 81
/* Should be moved to machine-dependent areas. */
#define	P_OWEUPC	0x20000	/* Owe process an addupc() call at next ast. */
E 81

E 80
/*
D 80
 * Shareable process credentials (always resident).
 * This includes a reference to the current user credentials
 * as well as real and saved ids that may be used to change ids.
E 80
I 80
 * MOVE TO ucred.h?
 *
 * Shareable process credentials (always resident).  This includes a reference
 * to the current user credentials as well as real and saved ids that may be
 * used to change ids.
E 80
 */
struct	pcred {
D 80
	struct	ucred *pc_ucred;	/* current credentials */
	uid_t	p_ruid;			/* real user id */
	uid_t	p_svuid;		/* saved effective user id */
	gid_t	p_rgid;			/* real group id */
	gid_t	p_svgid;		/* saved effective group id */
	int	p_refcnt;		/* number of references */
E 80
I 80
	struct	ucred *pc_ucred;	/* Current credentials. */
	uid_t	p_ruid;			/* Real user id. */
	uid_t	p_svuid;		/* Saved effective user id. */
	gid_t	p_rgid;			/* Real group id. */
	gid_t	p_svgid;		/* Saved effective group id. */
	int	p_refcnt;		/* Number of references. */
E 80
};

I 70
D 71
/*
 * Used to maintain information about processes that wish to be
 * notified when I/O becomes possible.
 */
struct selinfo {
	pid_t	si_pid;		/* process to be notified */
	short	si_flags;	/* see below */
};
#define	SI_COLL	0x0001		/* collision occurred */

E 71
E 70
E 63
I 48
D 64
/* 
D 63
 * proc ops return arrays of augmented proc structures
E 63
I 63
 * getkerninfo() proc ops return arrays of augmented proc structures:
E 63
 */
struct kinfo_proc {
	struct	proc kp_proc;			/* proc structure */
	struct	eproc {
		struct	proc *e_paddr;		/* address of proc */
		struct	session *e_sess;	/* session pointer */
I 63
		struct	pcred e_pcred;		/* process credentials */
		struct	ucred e_ucred;		/* current credentials */
		struct	vmspace e_vm;		/* address space */
E 63
		pid_t	e_pgid;			/* process group id */
		short	e_jobc;			/* job control counter */
D 54
		dev_t	e_tdev;			/* controlling tty */
E 54
I 54
		dev_t	e_tdev;			/* controlling tty dev */
E 54
		pid_t	e_tpgid;		/* tty process group id */
		struct	session *e_tsess;	/* tty session pointer */
#define	WMESGLEN	7
		char	e_wmesg[WMESGLEN+1];	/* wchan message */
D 52
		size_t	e_xsize;		/* text size */
E 52
I 52
		segsz_t e_xsize;		/* text size */
E 52
		short	e_xrssize;		/* text rss */
		short	e_xccount;		/* text references */
		short	e_xswrss;
D 54
		long	e_spare[8];
E 54
I 54
		long	e_flag;
#define	EPROC_CTTY	0x01	/* controlling tty vnode active */
#define	EPROC_SLEADER	0x02	/* session leader */
		long	e_spare[7];
E 54
	} kp_eproc;
};
E 64
I 64
D 80
/* stat codes */
#define	SSLEEP	1		/* awaiting an event */
#define	SWAIT	2		/* (abandoned state) */
#define	SRUN	3		/* running */
#define	SIDL	4		/* intermediate state in process creation */
#define	SZOMB	5		/* intermediate state in process termination */
#define	SSTOP	6		/* process being traced */
E 64

I 64
/* flag codes */
#define	SLOAD	0x0000001	/* in core */
D 68
#define	SSYS	0x0000002	/* swapper or pager process */
E 68
I 68
#define	SSYS	0x0000002	/* system proc: no sigs, stats or swapping */
E 68
#define	SSINTR	0x0000004	/* sleep is interruptible */
#define	SCTTY	0x0000008	/* has a controlling terminal */
#define	SPPWAIT	0x0000010	/* parent is waiting for child to exec/exit */
#define SEXEC	0x0000020	/* process called exec */
#define	STIMO	0x0000040	/* timing out during sleep */
#define	SSEL	0x0000080	/* selecting; wakeup/waiting danger */
#define	SWEXIT	0x0000100	/* working on exiting */
#define	SNOCLDSTOP 0x0000200	/* no SIGCHLD when children stop */
/* the following three should probably be changed into a hold count */
#define	SLOCK	0x0000400	/* process being swapped out */
#define	SKEEP	0x0000800	/* another flag to prevent swap out */
#define	SPHYSIO	0x0001000	/* doing physical i/o */
#define	STRC	0x0004000	/* process is being traced */
#define	SWTED	0x0008000	/* another tracing flag */
I 74
#define	SUGID	0x0020000	/* had set id privileges since last exec */
E 74
I 67
#define	SADVLCK	0x0040000	/* process may hold a POSIX advisory lock */
I 74
#define	SPROFIL	0x0080000	/* has started profiling */
E 74
E 67
/* the following should be moved to machine-dependent areas */
#define	SOWEUPC	0x0002000	/* owe process an addupc() call at next ast */
D 76
#ifdef HPUXCOMPAT
#define	SHPUX	0x0010000	/* HP-UX process (HPUXCOMPAT) */
#else
#define	SHPUX	0		/* not HP-UX process (HPUXCOMPAT) */
#endif
E 76
D 74
/* not currently in use (never set) */
#define	SPAGE	0x0020000	/* process in page wait state */
E 74

E 80
E 64
E 48
D 35
#define	PIDHSZ		63
#define	PIDHASH(pid)	((pid) % PIDHSZ)
E 35
I 35
D 49
#define	PIDHSZ		64
#define	PIDHASH(pid)	((pid) & (PIDHSZ - 1))
E 35

E 49
#ifdef KERNEL
I 59
/*
D 80
 * We use process IDs <= PID_MAX;
 * PID_MAX + 1 must also fit in a pid_t
 * (used to represent "no process group").
E 80
I 80
 * We use process IDs <= PID_MAX; PID_MAX + 1 must also fit in a pid_t,
 * as it is used to represent "no process group".
E 80
 */
#define	PID_MAX		30000
#define	NO_PID		30001
E 59
D 42
short	pidhash[PIDHSZ];
E 42
I 42
D 49
pid_t	pidhash[PIDHSZ];
E 42
D 30

E 30
struct	proc *pfind();
I 42
struct	pgrp *pgrphash[PIDHSZ];
struct 	pgrp *pgfind();		/* find process group by id */
E 42
D 30
#endif

#ifdef	KERNEL
E 30
D 13
extern	struct proc proc[];	/* the proc table itself */
E 13
I 13
D 14
extern	struct proc *proc, *procNPROC;	/* the proc table itself */
extern	int nproc;
E 14
I 14
struct	proc *proc, *procNPROC;	/* the proc table itself */
E 49
I 49
D 88
#define	PIDHASH(pid)	((pid) & pidhashmask)
E 88
I 64

#define SESS_LEADER(p)	((p)->p_session->s_leader == (p))
#define	SESSHOLD(s)	((s)->s_count++)
D 80
#define	SESSRELE(s)	{ \
		if (--(s)->s_count == 0) \
			FREE(s, M_SESSION); \
	}
E 80
I 80
#define	SESSRELE(s) {							\
	if (--(s)->s_count == 0)					\
		FREE(s, M_SESSION);					\
}
E 80

E 64
D 80
extern	int pidhashmask;		/* in param.c */
extern	struct proc *pidhash[];		/* in param.c */
struct	proc *pfind();			/* find process by id */
extern	struct pgrp *pgrphash[];	/* in param.c */
struct 	pgrp *pgfind();			/* find process group by id */
D 63
struct	proc *proc, *procNPROC;		/* the proc table itself */
E 49
I 35
struct	proc *freeproc, *zombproc, *allproc;
E 63
I 63
D 64
struct	proc *zombproc, *allproc;
E 64
I 64
D 74
struct	proc *zombproc, *allproc;	/* lists of procs in various states */
E 74
I 74
D 75
struct	proc *allproc;			/* list of active procs */
E 75
I 75
volatile struct proc *allproc;		/* list of active procs */
E 75
struct	proc *zombproc;			/* list of zombie procs */
E 74
E 64
extern	struct proc proc0;		/* process slot for swapper */
struct	proc *initproc, *pageproc;	/* process slots for init, pager */
D 64
#ifdef notyet
struct	proc *curproc;			/* current running proc */
#endif
E 63
D 49
			/* lists of procs in various states */
E 49
I 49
					/* lists of procs in various states */
E 64
I 64
extern	struct proc *curproc;		/* current running proc */
E 64
E 49
E 35
D 63
int	nproc;
E 63
I 63
extern	int nprocs, maxproc;		/* current and max number of procs */
E 80
I 80
D 88
extern struct proc *pidhash[];		/* In param.c. */
extern struct pgrp *pgrphash[];		/* In param.c. */
E 88
I 88
#define	PIDHASH(pid)	(&pidhashtbl[(pid) & pidhash])
extern LIST_HEAD(pidhashhead, proc) *pidhashtbl;
extern u_long pidhash;

#define	PGRPHASH(pgid)	(&pgrphashtbl[(pgid) & pgrphash])
extern LIST_HEAD(pgrphashhead, pgrp) *pgrphashtbl;
extern u_long pgrphash;

E 88
extern struct proc *curproc;		/* Current running proc. */
extern struct proc proc0;		/* Process slot for swapper. */
extern int nprocs, maxproc;		/* Current and max number of procs. */
D 89
extern int pidhashmask;			/* In param.c. */
E 89
E 80
E 63
E 14
E 13

D 12
#ifdef FASTVAX
E 12
D 80
#define	NQS	32		/* 32 run queues */
E 80
I 80
D 87
volatile struct proc *allproc; 		/* List of active procs. */
E 87
I 87
D 88
volatile struct proc *allproc;		/* List of active procs. */
E 87
struct proc *zombproc;			/* List of zombie procs. */
E 88
I 88
D 89
extern LIST_HEAD(, proc) allproc;	/* List of all processes. */
extern LIST_HEAD(, proc) zombproc;	/* List of zombie processes. */
E 89
I 89
LIST_HEAD(proclist, proc);
extern struct proclist allproc;		/* List of all processes. */
extern struct proclist zombproc;	/* List of zombie processes. */
E 89
E 88
struct proc *initproc, *pageproc;	/* Process slots for init, pager. */

#define	NQS	32			/* 32 run queues. */
int	whichqs;			/* Bit mask summary of non-empty Q's. */
E 80
struct	prochd {
D 80
	struct	proc *ph_link;	/* linked list of running processes */
E 80
I 80
	struct	proc *ph_link;		/* Linked list of running processes. */
E 80
	struct	proc *ph_rlink;
} qs[NQS];
I 63

E 63
D 80
int	whichqs;		/* bit mask summarizing non-empty qs's */
E 80
I 80
struct proc *pfind __P((pid_t));	/* Find process by id. */
struct pgrp *pgfind __P((pid_t));	/* Find process group by id. */
E 80
I 69

I 91
int	chgproccnt __P((uid_t uid, int diff));
int	enterpgrp __P((struct proc *p, pid_t pgid, int mksess));
void	fixjobc __P((struct proc *p, struct pgrp *pgrp, int entering));
int	inferior __P((struct proc *p));
int	leavepgrp __P((struct proc *p));
E 91
D 72
int	sleep __P((caddr_t chan, int pri));
int	tsleep __P((caddr_t chan, int pri, char *wmesg, int timo));
E 72
I 72
D 75
int	sleep __P((void *chan, int pri));
E 75
I 75
D 80
void	sleep __P((void *chan, int pri));
E 80
E 75
D 81
int	tsleep __P((void *chan, int pri, char *wmesg, int timo));
E 81
I 81
void	mi_switch __P((void));
I 91
void	pgdelete __P((struct pgrp *pgrp));
void	procinit __P((void));
E 91
E 81
E 72
D 75
int	unsleep __P((struct proc *));
D 72
int	wakeup __P((caddr_t));
E 72
I 72
int	wakeup __P((void *chan));
E 72
int	setrun __P((struct proc *));
int	setpri __P((struct proc *));
E 75
I 75
D 80
void	unsleep __P((struct proc *));
void	wakeup __P((void *chan));
void	setrun __P((struct proc *));
E 80
D 79
void	setpri __P((struct proc *));
E 79
I 79
void	resetpriority __P((struct proc *));
I 80
void	setrunnable __P((struct proc *));
void	setrunqueue __P((struct proc *));
void	sleep __P((void *chan, int pri));
E 80
E 79
D 81
void	swtch __P((void));
E 81
I 81
int	tsleep __P((void *chan, int pri, char *wmesg, int timo));
E 81
E 75
I 70
D 71
void	selrecord __P((struct proc *selector, struct selinfo *));
void	selwakeup __P((struct selinfo *));
E 71
E 70
D 80

E 80
I 80
void	unsleep __P((struct proc *));
void	wakeup __P((void *chan));
E 80
E 69
I 64
#endif	/* KERNEL */
E 64
I 42
D 81

E 81
D 64
#define SESS_LEADER(p)	((p)->p_session->s_leader == (p))
I 56
#define	SESSHOLD(s)	((s)->s_count++)
#define	SESSRELE(s)	{ \
		if (--(s)->s_count == 0) \
			FREE(s, M_SESSION); \
		}
E 56
D 55
#define PGRP_JOBC(p)	(((p)->p_pgrp != (p)->p_pptr->p_pgrp) && \
			((p)->p_session == (p)->p_pptr->p_session))
E 55
E 42
D 12
#else
struct	proc *runq;
#endif
E 12
#endif

/* stat codes */
#define	SSLEEP	1		/* awaiting an event */
#define	SWAIT	2		/* (abandoned state) */
#define	SRUN	3		/* running */
#define	SIDL	4		/* intermediate state in process creation */
#define	SZOMB	5		/* intermediate state in process termination */
#define	SSTOP	6		/* process being traced */

/* flag codes */
I 63
/* NEED TO CHECK which of these are still used */
E 63
D 6
#define	SLOAD	0x00001		/* in core */
#define	SSYS	0x00002		/* swapper or pager process */
#define	SLOCK	0x00004		/* process being swapped out */
#define	SSWAP	0x00008		/* save area flag */
#define	STRC	0x00010		/* process is being traced */
#define	SWTED	0x00020		/* another tracing flag */
#define	SULOCK	0x00040		/* user settable lock in core */
#define	SPAGE	0x00080		/* process in page wait state */
#define	SKEEP	0x00100		/* another flag to prevent swap out */
#define	SDLYU	0x00200		/* delayed unlock of pages */
#define	SWEXIT	0x00400		/* working on exiting */
#define	SPHYSIO	0x00800		/* doing physical i/o (bio.c) */
#define	SVFORK	0x01000		/* process resulted from vfork() */
#define	SVFDONE	0x02000		/* another vfork flag */
#define	SNOVM	0x04000		/* no vm, parent in a vfork() */
#define	SPAGI	0x08000		/* init data space on demand, from inode */
#define	SANOM	0x10000		/* system detected anomalous vm behavior */
#define	SUANOM	0x20000		/* user warned of anomalous vm behavior */
I 2
#define	STIMO	0x40000		/* timing out during sleep */
E 6
I 6
D 19
#define	SLOAD	0x000001	/* in core */
#define	SSYS	0x000002	/* swapper or pager process */
#define	SLOCK	0x000004	/* process being swapped out */
#define	SSWAP	0x000008	/* save area flag */
#define	STRC	0x000010	/* process is being traced */
#define	SWTED	0x000020	/* another tracing flag */
#define	SULOCK	0x000040	/* user settable lock in core */
#define	SPAGE	0x000080	/* process in page wait state */
#define	SKEEP	0x000100	/* another flag to prevent swap out */
#define	SDLYU	0x000200	/* delayed unlock of pages */
#define	SWEXIT	0x000400	/* working on exiting */
#define	SPHYSIO	0x000800	/* doing physical i/o (bio.c) */
#define	SVFORK	0x001000	/* process resulted from vfork() */
#define	SVFDONE	0x002000	/* another vfork flag */
#define	SNOVM	0x004000	/* no vm, parent in a vfork() */
#define	SPAGI	0x008000	/* init data space on demand, from inode */
D 16
#define	SANOM	0x010000	/* system detected anomalous vm behavior */
#define	SUANOM	0x020000	/* user warned of anomalous vm behavior */
E 16
I 16
#define	SSEQL	0x010000	/* user warned of sequential vm behavior */
#define	SUANOM	0x020000	/* user warned of random vm behavior */
E 16
#define	STIMO	0x040000	/* timing out during sleep */
E 19
I 19
#define	SLOAD	0x0000001	/* in core */
#define	SSYS	0x0000002	/* swapper or pager process */
#define	SLOCK	0x0000004	/* process being swapped out */
#define	SSWAP	0x0000008	/* save area flag */
#define	STRC	0x0000010	/* process is being traced */
#define	SWTED	0x0000020	/* another tracing flag */
D 50
#define	SULOCK	0x0000040	/* user settable lock in core */
E 50
I 50
#define	SSINTR	0x0000040	/* sleep is interruptible */
E 50
#define	SPAGE	0x0000080	/* process in page wait state */
#define	SKEEP	0x0000100	/* another flag to prevent swap out */
D 28
#define	SDLYU	0x0000200	/* delayed unlock of pages */
E 28
I 28
D 31
/* was SDLYU */
E 31
I 31
D 63
#define	SOMASK	0x0000200	/* restore old mask after taking signal */
E 63
I 63
/*#define SOMASK	0x0000200	/* restore old mask after taking signal */
E 63
E 31
E 28
#define	SWEXIT	0x0000400	/* working on exiting */
D 46
#define	SPHYSIO	0x0000800	/* doing physical i/o (bio.c) */
E 46
I 46
#define	SPHYSIO	0x0000800	/* doing physical i/o */
E 46
D 63
#define	SVFORK	0x0001000	/* process resulted from vfork() */
#define	SVFDONE	0x0002000	/* another vfork flag */
#define	SNOVM	0x0004000	/* no vm, parent in a vfork() */
E 63
I 63
#define	SPPWAIT	0x0001000	/* parent is waiting for child to exec/exit */
#define	SVFORK	SPARSYNC	/* process resulted from vfork() XXX */
/*#define SVFDONE	0x0002000	/* another vfork flag XXX */
/*#define SNOVM	0x0004000	/* no vm, parent in a vfork() XXX */
E 63
D 44
#define	SPAGI	0x0008000	/* init data space on demand, from inode */
E 44
I 44
#define	SPAGV	0x0008000	/* init data space on demand, from vnode */
E 44
#define	SSEQL	0x0010000	/* user warned of sequential vm behavior */
#define	SUANOM	0x0020000	/* user warned of random vm behavior */
#define	STIMO	0x0040000	/* timing out during sleep */
E 19
D 18
#define	SDETACH	0x080000	/* detached inherited by init */
E 18
I 18
D 46
/* was SDETACH */
E 18
D 19
#define	SNUSIG	0x100000	/* using new signal mechanism */
I 10
#define	SOWEUPC	0x200000	/* owe process an addupc() call at next ast */
I 17
#define	SSEL	0x400000	/* selecting; wakeup/waiting danger */
E 19
I 19
D 31
#define	SNUSIG	0x0100000	/* using new signal mechanism */
E 31
I 31
#define	SOUSIG	0x0100000	/* using old signal mechanism */
E 46
I 46
#define	SNOCLDSTOP 0x0080000	/* no SIGCHLD when children stop */
D 47
/* was SOUSIG	0x0100000	/* using old signal mechanism */
E 47
I 47
#define	SCTTY	0x0100000	/* has a controlling terminal */
E 47
E 46
E 31
D 21
#define	SOWEUPC	0x0200000	/* owe process an addupc() call at next ast */
E 21
I 21
D 27
/* unused */
E 27
I 27
#define	SOWEUPC	0x0200000	/* owe process an addupc() call at next ast */
E 27
E 21
#define	SSEL	0x0400000	/* selecting; wakeup/waiting danger */
D 48
#define	SLOGIN	0x0800000	/* a login process (legit child of init) */
E 48
I 48
#define SEXEC	0x0800000	/* process called exec */
I 50
D 53
#define	SULOCK	0x1000000	/* locked in core after swap error XXX */
I 51
#define	SHPUX	0x2000000	/* HP-UX process (HPUXCOMPAT) */
E 51
E 50
E 48
I 25
D 49
#define	SPTECHG	0x1000000	/* pte's for process have changed */
I 42
D 43
#define STRCSYS	0x2000000	/* tracing system calls */
#define STRCSYSI 0x4000000	/* tracing system calls - inherited */
E 43
I 43
D 48
#define SKTR	0x2000000	/* pass kernel tracing flags to children */
E 43
#define SEXEC	0x8000000	/* process called exec */
E 48
I 48
#define	SLOGIN	0x2000000	/* a login process (legit child of init) */
E 49
I 49

#define	SPTECHG	0x0000000	/* pte's for process have changed XXX */
E 53
I 53
#define	SHPUX	0x1000000	/* HP-UX process (HPUXCOMPAT) */
#define	SULOCK	0x2000000	/* locked in core after swap error XXX */
#define	SPTECHG	0x4000000	/* pte's for process have changed XXX */
E 64
I 64
D 85
#endif	/* !_PROC_H_ */
E 85
I 85
#endif	/* !_SYS_PROC_H_ */
E 85
E 64
E 53
E 49
E 48
E 42
E 25
E 19
E 17
E 10
E 6
E 2
D 21

/*
 * parallel proc structure
 * to replace part with times
 * to be passed to parent process
 * in ZOMBIE state.
 *
 * THIS SHOULD BE DONE WITH A union() CONSTRUCTION
 */
struct	xproc
{
	struct	proc *xp_link;
	struct	proc *xp_rlink;
	struct	pte *xp_addr;
	char	xp_usrpri;
	char	xp_pri;		/* priority, negative is high */
	char	xp_cpu;		/* cpu usage for scheduling */
	char	xp_stat;
	char	xp_time;	/* resident time for scheduling */
	char	xp_nice;	/* nice for cpu usage */
	char	xp_slptime;
D 3
	int	xp_flag;
E 3
I 3
	char	p_cursig;
E 3
	int	xp_sig;		/* signals pending to this process */
D 3
	int	xp_ignsig;
E 3
I 3
	int	xp_siga0;
	int	xp_siga1;
	int	xp_flag;
E 3
	short	xp_uid;		/* user id, used to direct tty signals */
	short	xp_pgrp;	/* name of process group leader */
	short	xp_pid;		/* unique process id */
	short	xp_ppid;	/* process id of parent */
	short	xp_xstat;	/* Exit status for wait */
	struct	vtimes xp_vm;
};
E 21
E 1
