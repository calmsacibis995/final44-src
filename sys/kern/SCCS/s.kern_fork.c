h18033
s 00007/00009/00254
d D 8.8 95/02/14 10:26:51 cgd 63 62
c new argument passing conventions.  minor type size cleanup.
e
s 00011/00037/00252
d D 8.7 94/08/22 10:20:10 mckusick 62 61
c use new queue.h data structures
e
s 00004/00004/00285
d D 8.6 94/04/08 22:35:45 mckusick 61 60
c cleanup code and comment on maximum number of processes (from cgd)
e
s 00005/00000/00284
d D 8.5 94/01/21 17:17:39 bostic 60 59
c add USL's copyright notice
e
s 00005/00000/00279
d D 8.4 93/12/13 12:22:09 pendry 59 58
c add p_textvp to track vnode of executable (for procfs)
e
s 00018/00019/00261
d D 8.3 93/09/23 15:41:36 bostic 58 57
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00001/00279
d D 8.2 93/09/21 07:32:48 bostic 57 56
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00278
d D 8.1 93/06/10 21:57:16 bostic 56 55
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00279
d D 7.42 93/03/03 16:01:43 mckusick 55 54
c do not inherit SHPUX
e
s 00012/00012/00268
d D 7.41 92/12/09 19:23:27 mckusick 54 53
c new include syntax
e
s 00023/00007/00257
d D 7.40 92/09/22 22:35:36 mckusick 53 52
c carefully cast volitile pointers to avoid code reordering (from torek@lbl)
e
s 00014/00014/00250
d D 7.39 92/07/19 23:35:19 mckusick 52 51
c avoid linear scan through proc table to find number of processes
e
s 00005/00002/00259
d D 7.38 92/07/10 20:49:13 torek 51 50
c ANSIfy syscall args
e
s 00004/00004/00257
d D 7.37 92/07/07 14:45:25 torek 50 49
c volatile poisoning
e
s 00003/00010/00258
d D 7.36 92/06/20 11:57:26 mckusick 49 48
c things moved into zero range; inherit profiling from parent
e
s 00001/00000/00267
d D 7.35 92/06/02 21:28:48 mckusick 48 47
c NULL out p_wmesg
e
s 00003/00001/00264
d D 7.34 92/05/27 18:21:04 mckusick 47 46
c have to save away the newly malloc'ed proc
e
s 00019/00023/00246
d D 7.33 92/05/20 17:36:58 mckusick 46 45
c allocate proc structure before allocate process id; bug that if
c p_pgid == pid + 1 could end up not finding a process using the new pid
e
s 00003/00003/00266
d D 7.32 92/02/14 17:02:32 torek 45 44
c lint; have to set p_stat early to protect against early usage
e
s 00000/00001/00269
d D 7.31 91/11/19 23:48:58 torek 44 43
c purge seg.h
e
s 00001/00001/00269
d D 7.30 91/09/06 15:46:13 ralph 43 42
c fix comment
e
s 00001/00000/00269
d D 7.29 91/05/15 21:02:44 mckusick 42 41
c need to set reference count on copied credential
e
s 00004/00000/00265
d D 7.28 91/05/15 19:24:01 mckusick 41 40
c XXX need to initialize spare fields (should be in zero range)
e
s 00006/00004/00259
d D 7.27 91/05/04 16:27:59 karels 40 39
c mv init of p_regs to cpu_fork; cosmetic changes
e
s 00015/00012/00248
d D 7.26 91/04/20 14:43:51 karels 39 38
c rm unneeded proc flags; set up for cpu_fork to relocate kernel stack;
c use tsleep for ppwait (vfork, etc)
e
s 00146/00166/00114
d D 7.25 91/03/17 15:42:25 karels 38 37
c more-or-less working with new proc & user structs
c merge newproc into fork, clone proc by bcopy/bzero, lots of cleanup
e
s 00002/00000/00278
d D 7.24 91/02/11 09:56:11 karels 37 36
c need to copy sv{u,g}id in fork!
e
s 00002/00010/00276
d D 7.23 91/01/10 23:43:55 mckusick 36 35
c add dynamically allocated file descriptors
e
s 00007/00043/00279
d D 7.22 90/12/05 16:34:50 mckusick 35 34
c update for new VM
e
s 00000/00001/00322
d D 7.21 90/08/24 08:49:39 mckusick 34 33
c delete unneeded header file
e
s 00002/00002/00321
d D 7.20 90/07/27 22:40:21 karels 33 32
c parameterize max proc id
e
s 00001/00011/00322
d D 7.19 90/06/28 21:19:29 bostic 32 31
c new copyright notice
e
s 00004/00004/00329
d D 7.18 90/06/28 17:10:22 karels 31 30
c RETURN => return, remove syscontext.h
e
s 00037/00028/00296
d D 7.17 90/06/05 22:02:01 mckusick 30 29
c update to new system call convention; expunge more u.u_error
e
s 00003/00001/00321
d D 7.16 90/05/17 18:00:00 marc 29 27
c only copy SCTTY if proc *has* a ctty
e
s 00003/00001/00321
d R 7.16 90/05/17 17:41:18 marc 28 27
c only copy SCTTY flag if the session still has a controlling terminal
e
s 00002/00002/00320
d D 7.15 90/05/15 22:05:11 bostic 27 26
c rename size_t to segsz_t for ANSI C
e
s 00004/00003/00318
d D 7.14 90/05/10 18:03:43 mckusick 26 25
c merge in support for hp300 from Utah
e
s 00007/00002/00314
d D 7.13 90/05/01 11:20:17 marc 25 24
c initialize [us]time
e
s 00000/00004/00316
d D 7.12 90/04/27 09:55:19 mckusick 24 23
c no longer have per user quota structures
e
s 00011/00006/00309
d D 7.11 90/04/05 15:08:48 marc 23 22
c p_comm, p_logname, ktrace inherit flag in traceflag, p_hash
e
s 00001/00001/00314
d D 7.10 89/11/20 18:22:14 marc 22 21
c propagate SCTTY
e
s 00003/00001/00312
d D 7.9 89/09/03 18:18:31 karels 21 20
c move real uid, gid to proc structure; remove SOUSIG
e
s 00002/00004/00311
d D 7.8 89/07/05 18:14:48 marc 20 19
c grab vnode reference, not inode reference
e
s 00002/00002/00313
d D 7.7 89/06/27 19:26:37 mckusick 19 18
c update reference counts on vnodes using VREF
e
s 00020/00009/00295
d D 7.6 89/05/09 17:02:16 mckusick 18 17
c merge in vnodes
e
s 00013/00000/00291
d D 7.5 89/05/01 23:08:28 marc 17 16
c KTRACE code
e
s 00004/00004/00287
d D 7.4 89/04/25 14:48:09 mckusick 16 15
c ../machine => machine
e
s 00006/00003/00285
d D 7.3 88/10/18 15:14:29 marc 15 14
c posix style job control - new process groups
e
s 00004/00000/00284
d D 7.2 86/11/03 11:59:44 karels 14 13
c merge in tahoe support
e
s 00001/00001/00283
d D 7.1 86/06/05 00:02:50 mckusick 13 12
c 4.3BSD release version
e
s 00002/00002/00282
d D 6.9 86/02/23 23:08:50 karels 12 11
c lint
e
s 00001/00001/00283
d D 6.8 86/02/20 15:58:23 karels 11 10
c cleanups from Sam: format, spl's, ptrace defs
e
s 00007/00001/00277
d D 6.7 85/06/08 14:36:09 mckusick 10 9
c Add copyright
e
s 00001/00001/00277
d D 6.6 85/05/27 19:53:59 karels 9 8
c implement high-water mark on file descriptors in use
e
s 00014/00014/00264
d D 6.5 84/08/29 20:19:31 bloom 8 7
c Change to includes.  no more ../h
e
s 00001/00001/00277
d D 6.4 84/07/14 14:46:10 sam 7 6
c starting time of proc now timeval
e
s 00004/00003/00274
d D 6.3 84/06/06 23:21:31 sam 6 5
c Berkeley coding standards committee in action (clean up your act Mike)
e
s 00046/00023/00231
d D 6.2 84/05/22 11:44:25 karels 5 4
c linked lists of active, zombie and free procs; avoid linear proc
c searches wherever possible
e
s 00000/00000/00254
d D 6.1 83/07/29 06:33:01 sam 4 3
c 4.2 distribution
e
s 00000/00004/00254
d D 4.3 83/06/14 01:37:13 sam 3 2
c revamp locking to be done at the file table level
e
s 00005/00004/00253
d D 4.2 83/06/02 15:56:51 sam 2 1
c new signals
e
s 00257/00000/00000
d D 4.1 83/05/27 14:02:45 sam 1 0
c date and time created 83/05/27 14:02:45 by sam
e
u
U
t
T
I 1
D 10
/*	%M%	%I%	%E%	*/
E 10
I 10
/*
D 13
 * Copyright (c) 1982 Regents of the University of California.
E 13
I 13
D 18
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 13
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
D 39
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 39
I 39
D 56
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
E 39
 * All rights reserved.
E 56
I 56
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 60
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 60
E 56
E 18
 *
I 18
D 32
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
E 32
I 32
 * %sccs.include.redist.c%
E 32
 *
E 18
 *	%W% (Berkeley) %G%
 */
E 10

D 16
#include "../machine/reg.h"
#include "../machine/pte.h"
#include "../machine/psl.h"

E 16
D 8
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/map.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/kernel.h"
#include "../h/proc.h"
#include "../h/inode.h"
#include "../h/seg.h"
#include "../h/vm.h"
#include "../h/text.h"
#include "../h/file.h"
#include "../h/acct.h"
#include "../h/quota.h"
E 8
I 8
D 54
#include "param.h"
#include "systm.h"
#include "map.h"
D 18
#include "dir.h"
E 18
D 30
#include "user.h"
E 30
I 30
D 31
#include "syscontext.h"
E 31
I 31
D 38
#include "user.h"
E 38
I 36
#include "filedesc.h"
E 36
E 31
E 30
#include "kernel.h"
I 38
#include "malloc.h"
E 38
#include "proc.h"
I 38
#include "resourcevar.h"
E 38
D 18
#include "inode.h"
E 18
I 18
#include "vnode.h"
E 18
D 44
#include "seg.h"
E 44
D 35
#include "vm.h"
#include "text.h"
E 35
#include "file.h"
#include "acct.h"
I 23
#include "ktrace.h"
E 54
I 54
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/filedesc.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/acct.h>
#include <sys/ktrace.h>
E 54
E 23
D 18
#include "quota.h"
E 18
I 18
D 34
#include "../ufs/quota.h"
E 34
E 18
I 16

I 51
D 63
struct fork_args {
	int	dummy;
};
E 63
E 51
D 38
#include "machine/reg.h"
D 35
#include "machine/pte.h"
E 35
#include "machine/psl.h"
E 16
E 8

/*
 * fork system call.
 */
E 38
D 30
fork()
E 30
I 30
/* ARGSUSED */
fork(p, uap, retval)
	struct proc *p;
D 40
	struct args *uap;
E 40
I 40
D 45
	void *uap;
E 45
I 45
D 51
	struct args *uap;
E 51
I 51
D 63
	struct fork_args *uap;
E 51
E 45
E 40
	int retval[];
E 63
I 63
	void *uap;
	register_t *retval;
E 63
E 30
{
I 30
D 38
	int error;
E 38
E 30

D 35
	u.u_cdmap = zdmap;
	u.u_csmap = zdmap;
D 30
	if (swpexpand(u.u_dsize, u.u_ssize, &u.u_cdmap, &u.u_csmap) == 0) {
		u.u_r.r_val2 = 0;
		return;
E 30
I 30
	if (error = swpexpand(u.u_dsize, u.u_ssize, &u.u_cdmap, &u.u_csmap)) {
		retval[1] = 0;
D 31
		RETURN (error);
E 31
I 31
		return (error);
E 31
E 30
	}
E 35
D 30
	fork1(0);
E 30
I 30
D 31
	RETURN (fork1(p, 0, retval));
E 31
I 31
	return (fork1(p, 0, retval));
E 31
E 30
}

D 30
vfork()
E 30
I 30
/* ARGSUSED */
vfork(p, uap, retval)
	struct proc *p;
D 40
	struct args *uap;
E 40
I 40
D 45
	void *uap;
E 45
I 45
D 51
	struct args *uap;
E 51
I 51
D 63
	struct fork_args *uap;
E 51
E 45
E 40
	int retval[];
E 63
I 63
	void *uap;
	register_t *retval;
E 63
E 30
{

D 30
	fork1(1);
E 30
I 30
D 31
	RETURN (fork1(p, 1, retval));
E 31
I 31
	return (fork1(p, 1, retval));
E 31
E 30
}

I 38
int	nprocs = 1;		/* process 0 */

E 38
D 30
fork1(isvfork)
	int isvfork;
E 30
I 30
fork1(p1, isvfork, retval)
	register struct proc *p1;
D 63
	int isvfork, retval[];
E 63
I 63
	int isvfork;
	register_t *retval;
E 63
E 30
{
D 30
	register struct proc *p1, *p2;
	register a;
E 30
I 30
	register struct proc *p2;
D 38
	register int a;
E 38
I 38
D 52
	register int count, uid;
E 52
I 52
	register uid_t uid;
E 52
I 47
	struct proc *newproc;
E 47
I 46
	struct proc **hash;
I 52
	int count;
E 52
E 46
	static int nextpid, pidchecked = 0;
E 38
E 30

D 38
	a = 0;
D 5
	p2 = NULL;
	for (p1 = proc; p1 < procNPROC; p1++) {
		if (p1->p_stat==NULL && p2==NULL)
			p2 = p1;
		else {
			if (p1->p_uid==u.u_uid && p1->p_stat!=NULL)
E 5
I 5
D 30
	if (u.u_uid != 0) {
		for (p1 = allproc; p1; p1 = p1->p_nxt)
			if (p1->p_uid == u.u_uid)
E 30
I 30
	if (p1->p_uid != 0) {
E 38
I 38
D 52
	count = 0;
	if ((uid = p1->p_ucred->cr_uid) != 0) {
E 38
D 50
		for (p2 = allproc; p2; p2 = p2->p_nxt)
E 50
I 50
		for (p2 = (struct proc *)allproc; p2; p2 = p2->p_nxt)
E 50
D 38
			if (p2->p_uid == p1->p_uid)
E 30
E 5
				a++;
E 38
I 38
			if (p2->p_ucred->cr_uid == uid)
				count++;
E 38
D 5
		}
E 5
I 5
D 30
		for (p1 = zombproc; p1; p1 = p1->p_nxt)
			if (p1->p_uid == u.u_uid)
E 30
I 30
		for (p2 = zombproc; p2; p2 = p2->p_nxt)
D 38
			if (p2->p_uid == p1->p_uid)
E 30
				a++;
E 38
I 38
			if (p2->p_ucred->cr_uid == uid)
				count++;
E 38
E 5
	}
E 52
	/*
D 38
	 * Disallow if
	 *  No processes at all;
	 *  not su and too many procs owned; or
	 *  not su and would take last slot.
E 38
I 38
D 43
	 * Although process entries are dynamically entries,
E 43
I 43
D 46
	 * Although process entries are dynamically created,
E 43
	 * we still keep a global limit on the maximum number
	 * we will create.  Don't allow a nonprivileged user
	 * to exceed its current limit or to bring us within one
	 * of the global limit; don't let root exceed the limit.
	 * nprocs is the current number of processes,
	 * maxproc is the limit.
E 46
I 46
	 * Although process entries are dynamically created, we still keep
	 * a global limit on the maximum number we will create.  Don't allow
D 52
	 * a nonprivileged user to exceed its current limit or to bring us
	 * within one of the global limit; don't let root exceed the limit.
	 * nprocs is the current number of processes, maxproc is the limit.
E 52
I 52
D 61
	 * a nonprivileged user to bring the system within one of the global
	 * limit; don't let root exceed the limit. The variable nprocs is
	 * the current number of processes, maxproc is the limit.
E 61
I 61
	 * a nonprivileged user to use the last process; don't let root
	 * exceed the limit. The variable nprocs is the current number of
	 * processes, maxproc is the limit.
E 61
E 52
E 46
E 38
	 */
I 52
	uid = p1->p_cred->p_ruid;
E 52
I 5
D 38
	p2 = freeproc;
E 5
	if (p2==NULL)
E 38
I 38
D 39
	retval[1] = 0;
E 39
D 61
	if (nprocs >= maxproc || uid == 0 && nprocs >= maxproc + 1) {
E 61
I 61
	if ((nprocs >= maxproc - 1 && uid != 0) || nprocs >= maxproc) {
E 61
E 38
		tablefull("proc");
D 5
	if (p2==NULL || (u.u_uid!=0 && (p2==procNPROC-1 || a>MAXUPRC))) {
E 5
I 5
D 30
	if (p2==NULL || (u.u_uid!=0 && (p2->p_nxt == NULL || a>MAXUPRC))) {
E 5
		u.u_error = EAGAIN;
E 30
I 30
D 38
	if (p2 == NULL ||
	    (p1->p_uid != 0 && (p2->p_nxt == NULL || a > MAXUPRC))) {
E 30
D 35
		if (!isvfork) {
D 12
			(void) vsexpand(0, &u.u_cdmap, 1);
			(void) vsexpand(0, &u.u_csmap, 1);
E 12
I 12
D 27
			(void) vsexpand((size_t)0, &u.u_cdmap, 1);
			(void) vsexpand((size_t)0, &u.u_csmap, 1);
E 27
I 27
			(void) vsexpand((segsz_t)0, &u.u_cdmap, 1);
			(void) vsexpand((segsz_t)0, &u.u_csmap, 1);
E 27
E 12
		}
E 35
D 30
		goto out;
E 30
I 30
		retval[1] = 0;
E 38
		return (EAGAIN);
E 30
	}
I 63

E 63
D 30
	p1 = u.u_procp;
E 30
D 38
	if (newproc(isvfork)) {
D 30
		u.u_r.r_val1 = p1->p_pid;
		u.u_r.r_val2 = 1;  /* child */
E 30
I 30
		retval[0] = p1->p_pid;
		retval[1] = 1;  /* child */
E 30
D 7
		u.u_start = time.tv_sec;
E 7
I 7
D 25
		u.u_start = time;
E 25
E 7
		u.u_acflag = AFORK;
D 30
		return;
E 30
I 30
		return (0);
E 30
	}
D 30
	u.u_r.r_val1 = p2->p_pid;

out:
	u.u_r.r_val2 = 0;
E 30
I 30
	retval[0] = p2->p_pid;
	retval[1] = 0;
	return (0);
E 30
}
E 38
I 38
D 52
	if (count > p1->p_rlimit[RLIMIT_NPROC].rlim_cur)
E 52
I 52
	/*
	 * Increment the count of procs running with this uid. Don't allow
	 * a nonprivileged user to exceed their current limit.
	 */
	count = chgproccnt(uid, 1);
	if (uid != 0 && count > p1->p_rlimit[RLIMIT_NPROC].rlim_cur) {
		(void)chgproccnt(uid, -1);
E 52
		return (EAGAIN);
I 52
	}
E 52
E 38

I 46
	/* Allocate new proc. */
D 47
	MALLOC(p2, struct proc *, sizeof(struct proc), M_PROC, M_WAITOK);
E 47
I 47
	MALLOC(newproc, struct proc *, sizeof(struct proc), M_PROC, M_WAITOK);
E 47

E 46
D 38
/*
 * Create a new process-- the internal version of
 * sys fork.
 * It returns 1 in the new process, 0 in the old.
 */
newproc(isvfork)
	int isvfork;
{
D 5
	register struct proc *p;
E 5
	register struct proc *rpp, *rip;
D 36
	register int n;
E 36
	register struct file *fp;
I 5
	static int pidchecked = 0;
E 5

E 38
D 5
	p = NULL;
E 5
	/*
D 38
	 * First, just locate a slot for a process
	 * and copy the useful info from this process into it.
	 * The panic "cannot happen" because fork has already
	 * checked for the existence of a slot.
E 38
I 38
D 46
	 * Find an unused process ID.
	 * We remember a range of unused IDs ready to use
	 * (from nextpid+1 through pidchecked-1).
E 46
I 46
	 * Find an unused process ID.  We remember a range of unused IDs
	 * ready to use (from nextpid+1 through pidchecked-1).
E 46
E 38
	 */
D 5
retry:
E 5
D 38
	mpid++;
E 38
I 38
	nextpid++;
E 38
I 5
retry:
E 5
D 33
	if (mpid >= 30000) {
E 33
I 33
D 38
	if (mpid >= PID_MAX) {
E 33
D 5
		mpid = 0;
		goto retry;
E 5
I 5
		mpid = 100;
E 38
I 38
	/*
	 * If the process ID prototype has wrapped around,
	 * restart somewhat above 0, as the low-numbered procs
	 * tend to include daemons that don't exit.
	 */
	if (nextpid >= PID_MAX) {
		nextpid = 100;
E 38
		pidchecked = 0;
E 5
	}
D 5
	for (rpp = proc; rpp < procNPROC; rpp++) {
		if (rpp->p_stat == NULL && p==NULL)
			p = rpp;
		if (rpp->p_pid==mpid || rpp->p_pgrp==mpid)
			goto retry;
E 5
I 5
D 38
	if (mpid >= pidchecked) {
E 38
I 38
	if (nextpid >= pidchecked) {
E 38
		int doingzomb = 0;
I 6

E 6
D 33
		pidchecked = 30000;
E 33
I 33
		pidchecked = PID_MAX;
E 33
		/*
D 38
		 * Scan the proc table to check whether this pid
E 38
I 38
		 * Scan the active and zombie procs to check whether this pid
E 38
		 * is in use.  Remember the lowest pid that's greater
D 38
		 * than mpid, so we can avoid checking for a while.
E 38
I 38
		 * than nextpid, so we can avoid checking for a while.
E 38
		 */
D 38
		rpp = allproc;
E 38
I 38
D 50
		p2 = allproc;
E 50
I 50
D 62
		p2 = (struct proc *)allproc;
E 62
I 62
		p2 = allproc.lh_first;
E 62
E 50
E 38
again:
D 38
		for (; rpp != NULL; rpp = rpp->p_nxt) {
D 6
			if (rpp->p_pid==mpid || rpp->p_pgrp==mpid) {
E 6
I 6
D 15
			if (rpp->p_pid == mpid || rpp->p_pgrp == mpid) {
E 15
I 15
			if (rpp->p_pid == mpid || rpp->p_pgrp->pg_id == mpid) {
E 15
E 6
				mpid++;
				if (mpid >= pidchecked)
E 38
I 38
D 58
		for (; p2 != NULL; p2 = p2->p_nxt) {
E 58
I 58
D 62
		for (; p2 != NULL; p2 = p2->p_next) {
E 62
I 62
		for (; p2 != 0; p2 = p2->p_list.le_next) {
E 62
E 58
D 46
			if (p2->p_pid == nextpid ||
E 46
I 46
			while (p2->p_pid == nextpid ||
E 46
			    p2->p_pgrp->pg_id == nextpid) {
				nextpid++;
				if (nextpid >= pidchecked)
E 38
					goto retry;
			}
D 6
			if ((rpp->p_pid > mpid) && (pidchecked > rpp->p_pid))
E 6
I 6
D 38
			if (rpp->p_pid > mpid && pidchecked > rpp->p_pid)
E 6
				pidchecked = rpp->p_pid;
D 6
			if ((rpp->p_pgrp > mpid) && (pidchecked > rpp->p_pgrp))
E 6
I 6
D 15
			if (rpp->p_pgrp > mpid && pidchecked > rpp->p_pgrp)
E 6
				pidchecked = rpp->p_pgrp;
E 15
I 15
			if (rpp->p_pgrp->pg_id > mpid && 
			    pidchecked > rpp->p_pgrp->pg_id)
				pidchecked = rpp->p_pgrp->pg_id;
E 38
I 38
			if (p2->p_pid > nextpid && pidchecked > p2->p_pid)
				pidchecked = p2->p_pid;
			if (p2->p_pgrp->pg_id > nextpid && 
			    pidchecked > p2->p_pgrp->pg_id)
				pidchecked = p2->p_pgrp->pg_id;
E 38
E 15
		}
		if (!doingzomb) {
			doingzomb = 1;
D 38
			rpp = zombproc;
E 38
I 38
D 62
			p2 = zombproc;
E 62
I 62
			p2 = zombproc.lh_first;
E 62
E 38
			goto again;
		}
E 5
	}
D 5
	if ((rpp = p) == NULL)
E 5
I 5
D 38
	if ((rpp = freeproc) == NULL)
E 5
		panic("no procs");
E 38
D 63

E 63
I 5
D 38
	freeproc = rpp->p_nxt;			/* off freeproc */
	rpp->p_nxt = allproc;			/* onto allproc */
	rpp->p_nxt->p_prev = &rpp->p_nxt;	/*   (allproc is never NULL) */
	rpp->p_prev = &allproc;
	allproc = rpp;
E 38

E 5
D 46
	/*
I 38
	 * Allocate new proc.
	 * Link onto allproc (this should probably be delayed).
	 */
	MALLOC(p2, struct proc *, sizeof(struct proc), M_PROC, M_WAITOK);
E 46
I 46
D 53
	/* Link onto allproc (this should probably be delayed). */
E 53
I 53
D 62
	/*
	 * Link onto allproc (this should probably be delayed).
	 * Heavy use of volatile here to prevent the compiler from
	 * rearranging code.  Yes, it *is* terribly ugly, but at least
	 * it works.
	 */
E 62
E 53
E 46
	nprocs++;
I 47
	p2 = newproc;
E 47
I 45
D 53
	p2->p_stat = SIDL;			/* protect against others */
I 46
	p2->p_pid = nextpid;
E 46
E 45
D 50
	p2->p_nxt = allproc;
E 50
I 50
	p2->p_nxt = (struct proc *)allproc;
E 50
	p2->p_nxt->p_prev = &p2->p_nxt;		/* allproc is never NULL */
D 50
	p2->p_prev = &allproc;
E 50
I 50
	p2->p_prev = (struct proc **)&allproc;
E 50
	allproc = p2;
E 53
I 53
D 62
#define	Vp2 ((volatile struct proc *)p2)
	Vp2->p_stat = SIDL;			/* protect against others */
	Vp2->p_pid = nextpid;
	/*
	 * This is really:
D 58
	 *	p2->p_nxt = allproc;
	 *	allproc->p_prev = &p2->p_nxt;
E 58
I 58
	 *	p2->p_next = allproc;
	 *	allproc->p_prev = &p2->p_next;
E 58
	 *	p2->p_prev = &allproc;
	 *	allproc = p2;
	 * The assignment via allproc is legal since it is never NULL.
	 */
D 58
	*(volatile struct proc **)&Vp2->p_nxt = allproc;
E 58
I 58
	*(volatile struct proc **)&Vp2->p_next = allproc;
E 58
	*(volatile struct proc ***)&allproc->p_prev =
D 58
	    (volatile struct proc **)&Vp2->p_nxt;
E 58
I 58
	    (volatile struct proc **)&Vp2->p_next;
E 58
	*(volatile struct proc ***)&Vp2->p_prev = &allproc;
	allproc = Vp2;
#undef Vp2
E 62
I 62
	p2->p_stat = SIDL;			/* protect against others */
	p2->p_pid = nextpid;
	LIST_INSERT_HEAD(&allproc, p2, p_list);
E 62
E 53
D 58
	p2->p_link = NULL;			/* shouldn't be necessary */
	p2->p_rlink = NULL;			/* shouldn't be necessary */
E 58
I 58
	p2->p_forw = p2->p_back = NULL;		/* shouldn't be necessary */
I 62
	LIST_INSERT_HEAD(PIDHASH(p2->p_pid), p2, p_hash);
E 62
E 58

I 46
D 62
	/* Insert on the hash chain. */
	hash = &pidhash[PIDHASH(p2->p_pid)];
	p2->p_hash = *hash;
	*hash = p2;

E 62
E 46
	/*
E 38
	 * Make a proc table entry for the new process.
I 38
	 * Start by zeroing the section of proc that is zero-initialized,
	 * then copy the section that is copied directly from the parent.
E 38
	 */
D 38
	rip = u.u_procp;
D 24
#ifdef QUOTA
	rpp->p_quota = rip->p_quota;
	rpp->p_quota->q_cnt++;
#endif
E 24
I 14
#if defined(tahoe)
	rpp->p_ckey = rip->p_ckey;
	rpp->p_dkey = 0;
#endif
E 14
	rpp->p_stat = SIDL;
	timerclear(&rpp->p_realtimer.it_value);
D 2
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGI|SNUSIG));
E 2
I 2
D 18
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGI|SOUSIG));
E 18
I 18
D 21
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGV|SOUSIG));
E 21
I 21
D 22
	rpp->p_flag = SLOAD | (rip->p_flag & SPAGV);
E 22
I 22
D 26
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGV|SCTTY));
E 26
I 26
D 29
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGV|SCTTY|SHPUX));
E 29
I 29
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGV|SHPUX));
	if (rip->p_session->s_ttyvp != NULL && rip->p_flag & SCTTY)
		rpp->p_flag |= SCTTY;
E 29
E 26
E 22
E 21
E 18
E 2
D 35
	if (isvfork) {
E 35
I 35
	if (isvfork)
E 35
		rpp->p_flag |= SVFORK;
D 35
		rpp->p_ndx = rip->p_ndx;
	} else
		rpp->p_ndx = rpp - proc;
E 35
I 35
	rpp->p_ndx = rpp - proc;
E 35
I 23
	bcopy(rip->p_comm, rpp->p_comm, MAXCOMLEN+1);
	bcopy(rip->p_logname, rpp->p_logname, MAXLOGNAME);
E 23
	rpp->p_uid = rip->p_uid;
I 21
	rpp->p_ruid = rip->p_ruid;
I 37
	rpp->p_svuid = rip->p_svuid;
E 37
	rpp->p_rgid = rip->p_rgid;
I 37
	rpp->p_svgid = rip->p_svgid;
E 37
E 21
	rpp->p_pgrp = rip->p_pgrp;
I 15
	rpp->p_pgrpnxt = rip->p_pgrpnxt;
	rip->p_pgrpnxt = rpp;
E 15
	rpp->p_nice = rip->p_nice;
D 35
	rpp->p_textp = isvfork ? 0 : rip->p_textp;
E 35
	rpp->p_pid = mpid;
	rpp->p_ppid = rip->p_pid;
	rpp->p_pptr = rip;
	rpp->p_osptr = rip->p_cptr;
	if (rip->p_cptr)
		rip->p_cptr->p_ysptr = rpp;
	rpp->p_ysptr = NULL;
	rpp->p_cptr = NULL;
	rip->p_cptr = rpp;
	rpp->p_time = 0;
I 25
	bzero((caddr_t)&rpp->p_utime, sizeof (struct timeval));
	bzero((caddr_t)&rpp->p_stime, sizeof (struct timeval));
E 25
	rpp->p_cpu = 0;
D 2
	rpp->p_siga0 = rip->p_siga0;
	rpp->p_siga1 = rip->p_siga1;
	/* take along any pending signals, like stops? */
E 2
I 2
	rpp->p_sigmask = rip->p_sigmask;
	rpp->p_sigcatch = rip->p_sigcatch;
	rpp->p_sigignore = rip->p_sigignore;
D 35
	/* take along any pending signals like stops? */
E 2
	if (isvfork) {
D 26
		rpp->p_tsize = rpp->p_dsize = rpp->p_ssize = 0;
		rpp->p_szpt = clrnd(ctopt(UPAGES));
E 26
I 26
		rpp->p_tsize = rpp->p_dsize = rpp->p_mmsize = rpp->p_ssize = 0;
		rpp->p_szpt = clrnd(ctopt(HIGHPAGES));
E 26
		forkstat.cntvfork++;
		forkstat.sizvfork += rip->p_dsize + rip->p_ssize;
	} else {
		rpp->p_tsize = rip->p_tsize;
		rpp->p_dsize = rip->p_dsize;
I 26
		rpp->p_mmsize = rip->p_mmsize;
E 26
		rpp->p_ssize = rip->p_ssize;
		rpp->p_szpt = rip->p_szpt;
		forkstat.cntfork++;
		forkstat.sizfork += rip->p_dsize + rip->p_ssize;
	}
E 35
I 17
#ifdef KTRACE
D 23
	if (rip->p_flag&SKTR) {
		rpp->p_flag |= SKTR;
E 23
I 23
	if (rip->p_traceflag&KTRFAC_INHERIT) {
		rpp->p_traceflag = rip->p_traceflag;
E 23
D 20
		if ((rpp->p_tracep = rip->p_tracep) != NULL) {
			igrab(rpp->p_tracep);
			iunlock(rpp->p_tracep);
		}
E 20
I 20
		if ((rpp->p_tracep = rip->p_tracep) != NULL)
			VREF(rpp->p_tracep);
E 20
D 23
		rpp->p_traceflag = rip->p_traceflag;
E 23
	} else {
		rpp->p_tracep = NULL;
		rpp->p_traceflag = 0;
E 38
I 38
	bzero(&p2->p_startzero,
	    (unsigned) ((caddr_t)&p2->p_endzero - (caddr_t)&p2->p_startzero));
	bcopy(&p1->p_startcopy, &p2->p_startcopy,
	    (unsigned) ((caddr_t)&p2->p_endcopy - (caddr_t)&p2->p_startcopy));
I 48
D 49
	p2->p_wmesg = NULL;	/* XXX - should be in zero range */
E 48
I 41
	p2->p_spare[0] = 0;	/* XXX - should be in zero range */
	p2->p_spare[1] = 0;	/* XXX - should be in zero range */
	p2->p_spare[2] = 0;	/* XXX - should be in zero range */
	p2->p_spare[3] = 0;	/* XXX - should be in zero range */
E 49
E 41

	/*
	 * Duplicate sub-structures as needed.
	 * Increase reference counts on shared objects.
I 39
	 * The p_stats and p_sigacts substructs are set in vm_fork.
E 39
	 */
I 49
D 55
	p2->p_flag = SLOAD | (p1->p_flag & SHPUX);
E 55
I 55
D 58
	p2->p_flag = SLOAD;
E 55
	if (p1->p_flag & SPROFIL)
E 58
I 58
	p2->p_flag = P_INMEM;
	if (p1->p_flag & P_PROFIL)
E 58
		startprofclock(p2);
E 49
	MALLOC(p2->p_cred, struct pcred *, sizeof(struct pcred),
	    M_SUBPROC, M_WAITOK);
	bcopy(p1->p_cred, p2->p_cred, sizeof(*p2->p_cred));
I 42
	p2->p_cred->p_refcnt = 1;
E 42
	crhold(p1->p_ucred);

I 59
	/* bump references to the text vnode (for procfs) */
	p2->p_textvp = p1->p_textvp;
	if (p2->p_textvp)
		VREF(p2->p_textvp);

E 59
	p2->p_fd = fdcopy(p1);
D 39
	p2->p_stats = p1->p_stats;		/* XXX move; in u. */
E 39
	/*
	 * If p_limit is still copy-on-write, bump refcnt,
	 * otherwise get a copy that won't be modified.
	 * (If PL_SHAREMOD is clear, the structure is shared
	 * copy-on-write.)
	 */
	if (p1->p_limit->p_lflags & PL_SHAREMOD)
		p2->p_limit = limcopy(p1->p_limit);
	else {
		p2->p_limit = p1->p_limit;
		p2->p_limit->p_refcnt++;
E 38
	}
D 38
#endif
E 17
	rpp->p_rssize = 0;
	rpp->p_maxrss = rip->p_maxrss;
	rpp->p_wchan = 0;
	rpp->p_slptime = 0;
	rpp->p_pctcpu = 0;
	rpp->p_cpticks = 0;
E 38
I 38
D 39
	p2->p_sigacts = p1->p_sigacts;		/* XXX move; in u. */
E 39

D 39
	p2->p_flag = SLOAD | (p1->p_flag & (SPAGV|SHPUX));
E 39
I 39
D 49
	p2->p_flag = SLOAD | (p1->p_flag & SHPUX);
E 49
E 39
D 58
	if (p1->p_session->s_ttyvp != NULL && p1->p_flag & SCTTY)
		p2->p_flag |= SCTTY;
E 58
I 58
	if (p1->p_session->s_ttyvp != NULL && p1->p_flag & P_CONTROLT)
		p2->p_flag |= P_CONTROLT;
E 58
	if (isvfork)
D 58
		p2->p_flag |= SPPWAIT;
E 58
I 58
		p2->p_flag |= P_PPWAIT;
E 58
D 45
	p2->p_stat = SIDL;
E 45
D 46
	p2->p_pid = nextpid;
E 38
D 23
	n = PIDHASH(rpp->p_pid);
D 5
	p->p_idhash = pidhash[n];
E 5
I 5
	rpp->p_idhash = pidhash[n];
E 5
	pidhash[n] = rpp - proc;
E 23
I 23
	{
D 38
	struct proc **hash = &pidhash[PIDHASH(rpp->p_pid)];
E 38
I 38
	struct proc **hash = &pidhash[PIDHASH(p2->p_pid)];
E 38

D 38
	rpp->p_hash = *hash;
	*hash = rpp;
E 38
I 38
	p2->p_hash = *hash;
	*hash = p2;
E 38
	}
E 46
E 23
D 35
	multprog++;
E 35
D 38

E 38
I 38
D 62
	p2->p_pgrpnxt = p1->p_pgrpnxt;
	p1->p_pgrpnxt = p2;
E 62
I 62
	LIST_INSERT_AFTER(p1, p2, p_pglist);
E 62
	p2->p_pptr = p1;
D 62
	p2->p_osptr = p1->p_cptr;
	if (p1->p_cptr)
		p1->p_cptr->p_ysptr = p2;
	p1->p_cptr = p2;
E 62
I 62
	LIST_INSERT_HEAD(&p1->p_children, p2, p_sibling);
	LIST_INIT(&p2->p_children);

E 62
#ifdef KTRACE
E 38
	/*
D 38
	 * Increase reference counts on shared objects.
E 38
I 38
	 * Copy traceflag and tracefile if enabled.
	 * If not inherited, these were zeroed above.
E 38
	 */
D 9
	for (n = 0; n < NOFILE; n++) {
E 9
I 9
D 36
	for (n = 0; n <= u.u_lastfile; n++) {
E 9
		fp = u.u_ofile[n];
		if (fp == NULL)
			continue;
		fp->f_count++;
D 3
		if (u.u_pofile[n]&UF_SHLOCK)
			((struct inode *)fp->f_data)->i_shlockc++;
		if (u.u_pofile[n]&UF_EXLOCK)
			((struct inode *)fp->f_data)->i_exlockc++;
E 3
	}
E 36
I 36
D 38
	rpp->p_fd = fddup(rip->p_fd, 0);
E 36
I 35
#ifdef SYSVSHM
	if (rip->p_shm)
		shmfork(rip, rpp, isvfork);
E 38
I 38
	if (p1->p_traceflag&KTRFAC_INHERIT) {
		p2->p_traceflag = p1->p_traceflag;
		if ((p2->p_tracep = p1->p_tracep) != NULL)
			VREF(p2->p_tracep);
	}
E 38
D 49
#endif
E 35
D 18
	u.u_cdir->i_count++;
E 18
I 18
D 19
	u.u_cdir->v_count++;
E 19
I 19
D 36
	VREF(u.u_cdir);
E 19
E 18
	if (u.u_rdir)
D 18
		u.u_rdir->i_count++;
E 18
I 18
D 19
		u.u_rdir->v_count++;
E 19
I 19
		VREF(u.u_rdir);
E 36
E 19
D 38
	crhold(u.u_cred);
E 38
E 18

I 38
D 40
	p2->p_regs = p1->p_regs;		 /* XXX move this */
E 40
#if defined(tahoe)
	p2->p_vmspace->p_ckey = p1->p_vmspace->p_ckey; /* XXX move this */
E 49
#endif

E 38
	/*
D 5
	 * Partially simulate the environment
	 * of the new process so that when it is actually
	 * created (by copying) it will look right.
E 5
	 * This begins the section where we must prevent the parent
	 * from being swapped.
	 */
D 38
	rip->p_flag |= SKEEP;
D 25
	if (procdup(rpp, isvfork))
E 25
I 25
	if (procdup(rpp, isvfork)) {
E 38
I 38
D 58
	p1->p_flag |= SKEEP;
E 58
I 58
	p1->p_flag |= P_NOSWAP;
E 58
I 39
	/*
	 * Set return values for child before vm_fork,
	 * so they can be copied to child stack.
	 * We return parent pid, and mark as child in retval[1].
I 40
	 * NOTE: the kernel stack may be at a different location in the child
	 * process, and thus addresses of automatic variables (including retval)
	 * may be invalid after vm_fork returns in the child process.
E 40
	 */
	retval[0] = p1->p_pid;
	retval[1] = 1;
E 39
	if (vm_fork(p1, p2, isvfork)) {
		/*
D 39
		 * Child process.  Set start time, return parent pid,
		 * and mark as child in retval[1].
E 39
I 39
		 * Child process.  Set start time and get to work.
E 39
		 */
E 38
		(void) splclock();
D 38
		u.u_start = time;
E 38
I 38
		p2->p_stats->p_start = time;
E 38
		(void) spl0();
E 25
D 38
		return (1);
E 38
I 38
D 39
		retval[0] = p1->p_pid;
		retval[1] = 1;
E 39
		p2->p_acflag = AFORK;
		return (0);
E 38
I 25
	}
E 25

	/*
	 * Make child runnable and add to run queue.
	 */
D 11
	(void) spl6();
E 11
I 11
D 38
	(void) splclock();
E 11
	rpp->p_stat = SRUN;
	setrq(rpp);
E 38
I 38
	(void) splhigh();
	p2->p_stat = SRUN;
D 57
	setrq(p2);
E 57
I 57
	setrunqueue(p2);
E 57
E 38
	(void) spl0();

	/*
D 38
	 * Cause child to take a non-local goto as soon as it runs.
	 * On older systems this was done with SSWAP bit in proc
	 * table; on VAX we use u.u_pcb.pcb_sswap so don't need
	 * to do rpp->p_flag |= SSWAP.  Actually do nothing here.
	 */
	/* rpp->p_flag |= SSWAP; */

	/*
E 38
	 * Now can be swapped.
	 */
D 38
	rip->p_flag &= ~SKEEP;
E 38
I 38
D 58
	p1->p_flag &= ~SKEEP;
E 58
I 58
	p1->p_flag &= ~P_NOSWAP;
E 58
E 38

	/*
D 35
	 * If vfork make chain from parent process to child
	 * (where virtal memory is temporarily).  Wait for
	 * child to finish, steal virtual memory back,
	 * and wakeup child to let it die.
E 35
I 35
D 40
	 * XXX preserve synchronization semantics of vfork
E 40
I 40
D 58
	 * Preserve synchronization semantics of vfork.
E 40
I 38
	 * If waiting for child to exec or exit, set SPPWAIT
	 * on child, and sleep on our proc (in case of exit).
E 58
I 58
	 * Preserve synchronization semantics of vfork.  If waiting for
	 * child to exec or exit, set P_PPWAIT on child, and sleep on our
	 * proc (in case of exit).
E 58
E 38
E 35
	 */
D 38
	if (isvfork) {
D 35
		u.u_procp->p_xlink = rpp;
E 35
		u.u_procp->p_flag |= SNOVM;
		while (rpp->p_flag & SVFORK)
			sleep((caddr_t)rpp, PZERO - 1);
		if ((rpp->p_flag & SLOAD) == 0)
			panic("newproc vfork");
D 35
		uaccess(rpp, Vfmap, &vfutl);
		u.u_procp->p_xlink = 0;
		vpassvm(rpp, u.u_procp, &vfutl, &u, Vfmap);
E 35
		u.u_procp->p_flag &= ~SNOVM;
D 35
		rpp->p_ndx = rpp - proc;
E 35
		rpp->p_flag |= SVFDONE;
		wakeup((caddr_t)rpp);
	}
E 38
I 38
	if (isvfork)
D 58
		while (p2->p_flag & SPPWAIT)
D 39
			sleep((caddr_t)p1, PZERO - 1);
E 39
I 39
			tsleep((caddr_t)p1, PWAIT, "ppwait", 0);
E 58
I 58
		while (p2->p_flag & P_PPWAIT)
			tsleep(p1, PWAIT, "ppwait", 0);
E 58
E 39
E 38

	/*
D 38
	 * 0 return means parent.
E 38
I 38
D 39
	 * Return child pid to parent process.
	 * retval[1] was set above.
E 39
I 39
	 * Return child pid to parent process,
	 * marking us as parent via retval[1].
E 39
E 38
	 */
I 38
	retval[0] = p2->p_pid;
I 39
	retval[1] = 0;
E 39
E 38
	return (0);
}
E 1
