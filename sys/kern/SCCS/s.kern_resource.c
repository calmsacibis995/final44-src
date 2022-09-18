h17522
s 00094/00081/00369
d D 8.8 95/02/14 10:38:40 cgd 75 74
c new argument passing conventions.  minor type size cleanup.
e
s 00002/00000/00448
d D 8.7 95/01/09 18:22:21 cgd 74 73
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00006/00008/00442
d D 8.6 94/08/22 10:20:00 mckusick 73 72
c use new queue.h data structures
e
s 00005/00000/00445
d D 8.5 94/01/21 17:17:45 bostic 72 71
c add USL's copyright notice
e
s 00001/00001/00444
d D 8.4 93/12/10 19:51:57 mckusick 71 70
c proper error return from setpriority()
e
s 00002/00002/00443
d D 8.3 93/09/23 15:28:51 bostic 70 69
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00001/00444
d D 8.2 93/09/05 09:36:01 bostic 69 68
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00443
d D 8.1 93/06/10 21:57:44 bostic 68 67
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00443
d D 7.26 93/05/25 17:15:23 mckusick 67 66
c __{g,s}etrlimit => {g,s}etrlimit
e
s 00002/00002/00443
d D 7.25 93/05/17 14:07:22 mckusick 66 65
c truncate, ftruncate, getrlimit, setrlimit become COMPAT_43
e
s 00007/00000/00438
d D 7.24 93/05/01 12:17:54 mckusick 65 63
c add limits on maxproc
e
s 00001/00001/00437
d R 7.24 93/04/20 10:35:19 mckusick 64 63
c accumulate involuntary context switches (from yval@CS.HUJI.AC.IL)
e
s 00008/00000/00430
d D 7.23 93/03/23 10:53:33 mckusick 63 62
c limit maximum file descriptors to maxfiles (from torek)
e
s 00006/00006/00424
d D 7.22 92/10/11 10:38:08 bostic 62 61
c make kernel includes standard
e
s 00036/00029/00394
d D 7.21 92/07/10 21:41:52 torek 61 59
c ANSIfy syscall args
e
s 00036/00029/00394
d R 7.21 92/07/10 21:02:49 torek 60 59
c ANSIfy syscall args
e
s 00024/00012/00399
d D 7.20 92/07/08 19:40:08 torek 59 55
c must add current time fraction in calcru if doing curproc;
c fix typo (missing unary &)
e
s 00024/00012/00399
d R 7.20 92/07/08 19:39:42 torek 58 55
c must add current time fraction in calcru if doing curproc;
c fraction in calcru if doing curproc;
e
s 00024/00012/00399
d R 7.20 92/07/08 19:38:59 torek 57 55
c must add current time fraction in calcru if doing curproc;
e
s 00023/00012/00399
d R 7.20 92/07/08 19:37:44 torek 56 55
c must add current time fraction in calcru if doing curproc;
c fix typo (missing unary &)
e
s 00047/00008/00364
d D 7.19 92/07/08 00:49:39 torek 55 54
c volatile poison; new rusage calculation
e
s 00002/00002/00370
d D 7.18 92/06/23 20:27:03 mckusick 54 53
c merge in changes for Sparc
e
s 00081/00025/00291
d D 7.17 92/05/31 21:38:49 mckusick 53 52
c new 64-bit versions of get/setrlimit
e
s 00001/00001/00315
d D 7.16 92/05/20 17:03:47 bostic 52 51
c fencepost error in ruadd; from Pace Willisson (pace@blitz.com)
e
s 00002/00000/00314
d D 7.15 92/03/15 13:25:52 mckusick 51 50
c do not set soft limit higher than new hard limit (net2/sys/8)
e
s 00002/00001/00312
d D 7.14 92/02/14 17:13:28 torek 50 49
c fix race in use of copied limit structure
e
s 00005/00004/00308
d D 7.13 91/05/09 21:21:27 bostic 49 48
c new copyright; att/bsd/shared
e
s 00026/00000/00286
d D 7.12 91/05/07 09:15:14 hibler 48 47
c new stack limit implementation: when changing limits 
c protect/unprotect the affected areas
e
s 00001/00001/00285
d D 7.11 91/04/20 15:19:15 karels 47 46
c set the new limit copy, not the old!
e
s 00042/00015/00244
d D 7.10 91/03/17 15:42:00 karels 46 45
c more-or-less working with new proc & user structs
c move limits into plimit struct, copy with limcopy
e
s 00015/00015/00244
d D 7.9 90/06/28 17:10:50 karels 45 44
c RETURN => return, remove syscontext.h
e
s 00080/00076/00179
d D 7.8 90/06/21 15:36:49 mckusick 44 43
c new system call convention
e
s 00002/00002/00253
d D 7.7 90/05/10 13:04:00 mckusick 43 42
c get rid of #defines in user.h
e
s 00009/00001/00246
d D 7.6 90/04/03 21:28:15 karels 42 41
c utime/stime now in proc structure, copy to rusage for getrusage
e
s 00000/00001/00247
d D 7.5 89/05/05 00:06:36 mckusick 41 40
c delete unneeded include of dir.h
e
s 00002/00002/00246
d D 7.4 89/04/26 19:41:41 mckusick 40 39
c use new form of suser()
e
s 00021/00013/00227
d D 7.3 88/10/18 15:14:48 marc 39 38
c posix style job control - new process groups
e
s 00000/00007/00240
d D 7.2 87/07/20 15:31:16 mckusick 38 37
c delete unneeded header files
e
s 00001/00001/00246
d D 7.1 86/06/05 00:03:52 mckusick 37 36
c 4.3BSD release version
e
s 00002/00002/00245
d D 6.9 86/05/14 15:53:46 karels 36 35
c missing error return
e
s 00001/00001/00246
d D 6.8 85/10/23 18:14:36 karels 35 34
c maxdsize and maxtsize in bytes; careful of confusing blocks and pages
e
s 00007/00001/00240
d D 6.7 85/06/08 14:37:16 mckusick 34 33
c Add copyright
e
s 00001/00001/00240
d D 6.6 85/05/22 16:15:38 mckusick 33 32
c return EPERM when non-super-user tries to set another process's priority
e
s 00009/00004/00232
d D 6.5 85/03/08 15:43:35 mckusick 32 31
c impose the real vm limit rather than the best guess
e
s 00027/00025/00209
d D 6.4 84/11/20 11:15:28 karels 31 30
c NZERO now 0 (use PRIO_{MIN,MAX}); cleanup u.u_error crap (going to
c toss that sucker!)
e
s 00011/00011/00223
d D 6.3 84/08/29 20:20:02 bloom 30 29
c Change to includes.  no more ../h
e
s 00004/00008/00230
d D 6.2 84/05/22 11:44:49 karels 29 28
c linked lists of active, zombie and free procs; avoid linear proc
c searches wherever possible
e
s 00000/00000/00238
d D 6.1 83/07/29 06:33:36 sam 28 27
c 4.2 distribution
e
s 00000/00083/00238
d D 4.22 83/05/27 12:47:03 sam 27 26
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00001/00001/00320
d D 4.21 83/05/23 00:30:28 sam 26 25
c looking at wrong proc
e
s 00001/00000/00320
d D 4.20 83/02/10 18:41:53 sam 25 23
c groups set members are shorts, not ints; hz no longer in systm.h
e
s 00001/00000/00320
d R 4.20 83/02/10 16:08:50 sam 24 23
c removing hz from systm.h
e
s 00014/00023/00306
d D 4.19 82/12/28 23:46:54 sam 23 22
c copyin & copyout now return EFAULT and all callers uniformly 
c return (or ignore) this value
e
s 00001/00001/00328
d D 4.18 82/12/17 11:44:27 sam 22 21
c sun merge
e
s 00001/00001/00328
d D 4.17 82/10/19 10:30:58 root 21 20
c more lint
e
s 00004/00003/00325
d D 4.16 82/10/17 21:49:10 root 20 19
c more lint
e
s 00001/00001/00327
d D 4.15 82/10/17 14:04:42 root 19 18
c fix lint
e
s 00105/00011/00223
d D 4.14 82/09/12 10:20:26 root 18 17
c 4.2 style
e
s 00012/00119/00222
d D 4.13 82/09/06 22:49:11 root 17 16
c 
e
s 00207/00037/00134
d D 4.12 82/09/04 09:11:33 root 16 15
c compilable 4.2 calls, not tested
e
s 00005/00007/00166
d D 4.11 82/08/22 20:32:56 root 15 14
c write accounting records with rdwri()
e
s 00059/00000/00114
d D 4.10 82/07/24 18:10:07 root 14 13
c merge with calder
e
s 00007/00005/00107
d D 4.9 82/07/12 18:16:32 kre 13 11
c Allow acct file swap w/o losing any info;
c use NODEV for ac_tty if proc had no controlling tty.
e
s 00000/00000/00112
d R 4.9 82/07/12 17:13:11 kre 12 11
c allow acct file switch with no info loss,
c make ac_tty be NODEV if proc has no controlling tty.
e
s 00001/00002/00111
d D 4.8 82/06/10 12:40:48 mckusick 11 10
c change iput() to irele() when releasing unlocked inodes
e
s 00002/00002/00111
d D 4.7 82/06/07 23:53:51 mckusick 10 9
c irele() becomes iunlock(); new irele() does iput() for already unlocked inodes
e
s 00001/00001/00112
d D 4.6 82/02/27 14:54:14 wnj 9 8
c symbolic links
e
s 00004/00004/00109
d D 4.5 81/11/08 16:46:31 wnj 8 7
c plock/prele --> ilock/irele
e
s 00004/00025/00109
d D 4.4 81/03/09 01:46:37 wnj 7 6
c lint and a few minor fixed
e
s 00018/00015/00116
d D 4.3 81/03/09 00:31:53 wnj 6 5
c lint
e
s 00005/00005/00126
d D 4.2 80/11/09 22:59:05 bill 5 4
c minor lint
e
s 00000/00000/00131
d D 4.1 80/11/09 17:31:18 bill 4 3
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00001/00001/00130
d D 3.3 80/06/07 02:44:16 bill 3 2
c %H%->%G%
e
s 00003/00001/00128
d D 3.2 80/04/12 17:30:25 bill 2 1
c save accounting information
e
s 00129/00000/00000
d D 3.1 80/04/09 16:02:50 bill 1 0
c date and time created 80/04/09 16:02:50 by bill
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%H%	*/
E 3
I 3
D 7
/*	%M%	%I%	%G%	*/
E 7
I 7
D 34
/*	%M%	%I%	%E%	*/
E 34
I 34
D 49
/*
D 37
 * Copyright (c) 1982 Regents of the University of California.
E 37
I 37
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 37
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 49
I 49
/*-
D 68
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 68
I 68
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 72
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 72
E 68
 *
 * %sccs.include.redist.c%
E 49
 *
 *	%W% (Berkeley) %G%
 */
E 34
E 7
E 3

D 30
#include "../h/param.h"
#include "../h/systm.h"
D 17
#include "../h/acct.h"
E 17
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/inode.h"
#include "../h/proc.h"
#include "../h/seg.h"
I 14
#include "../h/fs.h"
I 15
#include "../h/uio.h"
I 16
#include "../h/vm.h"
I 25
#include "../h/kernel.h"
E 30
I 30
D 62
#include "param.h"
I 59
#include "kernel.h"
E 59
D 38
#include "systm.h"
E 38
D 41
#include "dir.h"
E 41
D 44
#include "user.h"
E 44
I 44
D 45
#include "syscontext.h"
E 45
I 45
D 46
#include "user.h"
E 46
I 46
#include "resourcevar.h"
#include "malloc.h"
E 46
E 45
E 44
D 38
#include "inode.h"
E 38
#include "proc.h"
E 62
I 62
#include <sys/param.h>
I 75
#include <sys/systm.h>
E 75
#include <sys/kernel.h>
I 63
#include <sys/file.h>
E 63
#include <sys/resourcevar.h>
#include <sys/malloc.h>
#include <sys/proc.h>
E 62
D 38
#include "seg.h"
#include "fs.h"
#include "uio.h"
#include "vm.h"
#include "kernel.h"
E 38
E 30
E 25
E 16
E 15
E 14

I 75
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 75
I 48
D 62
#include "vm/vm.h"
E 62
I 62
#include <vm/vm.h>
E 62

I 75
int	donice __P((struct proc *curp, struct proc *chgp, int n));
int	dosetrlimit __P((struct proc *p, u_int which, struct rlimit *limp));

E 75
E 48
I 18
/*
 * Resource controls and accounting.
 */

I 61
D 75
struct getpriority_args {
	int	which;
	int	who;
};
E 75
I 75
int
E 75
E 61
E 18
I 16
D 44
getpriority()
{
	register struct a {
E 44
I 44
getpriority(curp, uap, retval)
	struct proc *curp;
D 61
	register struct args {
E 44
		int	which;
		int	who;
D 44
	} *uap = (struct a *)u.u_ap;
E 44
I 44
	} *uap;
E 61
I 61
D 75
	register struct getpriority_args *uap;
E 61
	int *retval;
E 75
I 75
	register struct getpriority_args /* {
		syscallarg(int) which;
		syscallarg(int) who;
	} */ *uap;
	register_t *retval;
E 75
{
E 44
	register struct proc *p;
I 31
D 39
	int low = PRIO_MAX + 1;
E 39
I 39
	register int low = PRIO_MAX + 1;
E 39
E 31

D 31
	u.u_r.r_val1 = NZERO+20;
	u.u_error = ESRCH;
E 31
D 75
	switch (uap->which) {
E 75
I 75
	switch (SCARG(uap, which)) {
E 75

	case PRIO_PROCESS:
D 75
		if (uap->who == 0)
E 75
I 75
		if (SCARG(uap, who) == 0)
E 75
D 44
			p = u.u_procp;
E 44
I 44
			p = curp;
E 44
		else
D 75
			p = pfind(uap->who);
E 75
I 75
			p = pfind(SCARG(uap, who));
E 75
		if (p == 0)
D 36
			return;
E 36
I 36
			break;
E 36
D 26
		u.u_r.r_val1 = u.u_procp->p_nice;
E 26
I 26
D 31
		u.u_r.r_val1 = p->p_nice;
E 26
I 18
		u.u_error = 0;
E 31
I 31
		low = p->p_nice;
E 31
E 18
		break;

D 39
	case PRIO_PGRP:
E 39
I 39
	case PRIO_PGRP: {
		register struct pgrp *pg;

E 39
D 75
		if (uap->who == 0)
E 75
I 75
		if (SCARG(uap, who) == 0)
E 75
D 39
			uap->who = u.u_procp->p_pgrp;
D 18
		for (p = proc; p < procNPROC; p++)
E 18
I 18
D 29
		for (p = proc; p < procNPROC; p++) {
			if (p->p_stat == NULL)
				continue;
E 29
I 29
		for (p = allproc; p != NULL; p = p->p_nxt) {
E 29
E 18
			if (p->p_pgrp == uap->who &&
D 31
			    p->p_nice < u.u_r.r_val1) {
				u.u_r.r_val1 = p->p_nice;
				u.u_error = 0;
			}
E 31
I 31
			    p->p_nice < low)
E 39
I 39
D 44
			pg = u.u_procp->p_pgrp;
E 44
I 44
			pg = curp->p_pgrp;
E 44
D 75
		else if ((pg = pgfind(uap->who)) == NULL)
E 75
I 75
		else if ((pg = pgfind(SCARG(uap, who))) == NULL)
E 75
			break;
D 73
		for (p = pg->pg_mem; p != NULL; p = p->p_pgrpnxt) {
E 73
I 73
		for (p = pg->pg_members.lh_first; p != 0;
D 75
		     p = p->p_pglist.le_next)
E 75
I 75
		     p = p->p_pglist.le_next) {
E 75
E 73
			if (p->p_nice < low)
E 39
				low = p->p_nice;
I 75
		}
E 75
E 31
I 18
D 73
		}
E 73
E 18
		break;
I 39
	}
E 39

I 18
	case PRIO_USER:
D 75
		if (uap->who == 0)
D 44
			uap->who = u.u_uid;
E 44
I 44
D 46
			uap->who = p->p_uid;
E 46
I 46
			uap->who = curp->p_ucred->cr_uid;
E 75
I 75
		if (SCARG(uap, who) == 0)
			SCARG(uap, who) = curp->p_ucred->cr_uid;
E 75
E 46
E 44
D 29
		for (p = proc; p < procNPROC; p++) {
			if (p->p_stat == NULL)
				continue;
E 29
I 29
D 55
		for (p = allproc; p != NULL; p = p->p_nxt) {
E 55
I 55
D 70
		for (p = (struct proc *)allproc; p != NULL; p = p->p_nxt) {
E 70
I 70
D 73
		for (p = (struct proc *)allproc; p != NULL; p = p->p_next) {
E 70
E 55
E 29
D 46
			if (p->p_uid == uap->who &&
E 46
I 46
			if (p->p_ucred->cr_uid == uap->who &&
E 46
D 31
			    p->p_nice < u.u_r.r_val1) {
				u.u_r.r_val1 = p->p_nice;
				u.u_error = 0;
			}
E 31
I 31
			    p->p_nice < low)
E 73
I 73
		for (p = allproc.lh_first; p != 0; p = p->p_list.le_next)
D 75
			if (p->p_ucred->cr_uid == uap->who && p->p_nice < low)
E 75
I 75
			if (p->p_ucred->cr_uid == SCARG(uap, who) &&
			    p->p_nice < low)
E 75
E 73
				low = p->p_nice;
E 31
D 73
		}
E 73
		break;

E 18
	default:
D 44
		u.u_error = EINVAL;
D 31
		break;
E 31
I 31
		return;
E 44
I 44
D 45
		RETURN (EINVAL);
E 45
I 45
		return (EINVAL);
E 45
E 44
E 31
	}
D 31
	u.u_r.r_val1 -= NZERO;
E 31
I 31
D 44
	if (low == PRIO_MAX + 1) {
		u.u_error = ESRCH;
		return;
	}
	u.u_r.r_val1 = low;
E 44
I 44
	if (low == PRIO_MAX + 1)
D 45
		RETURN (ESRCH);
E 45
I 45
		return (ESRCH);
E 45
	*retval = low;
D 45
	RETURN (0);
E 45
I 45
	return (0);
E 45
E 44
E 31
}

I 61
D 75
struct setpriority_args {
	int	which;
	int	who;
	int	prio;
};
E 75
E 61
D 44
setpriority()
{
	register struct a {
E 44
I 44
/* ARGSUSED */
I 75
int
E 75
setpriority(curp, uap, retval)
	struct proc *curp;
D 61
	register struct args {
E 44
		int	which;
		int	who;
		int	prio;
D 44
	} *uap = (struct a *)u.u_ap;
E 44
I 44
	} *uap;
E 61
I 61
D 75
	register struct setpriority_args *uap;
E 61
	int *retval;
E 75
I 75
	register struct setpriority_args /* {
		syscallarg(int) which;
		syscallarg(int) who;
		syscallarg(int) prio;
	} */ *uap;
	register_t *retval;
E 75
{
E 44
	register struct proc *p;
I 31
D 44
	int found = 0;
E 44
I 44
	int found = 0, error = 0;
E 44
E 31

D 31
	u.u_error = ESRCH;
E 31
D 75
	switch (uap->which) {
E 75
I 75
	switch (SCARG(uap, which)) {
E 75

	case PRIO_PROCESS:
D 18
		p = pfind(uap->who);
E 18
I 18
D 75
		if (uap->who == 0)
E 75
I 75
		if (SCARG(uap, who) == 0)
E 75
D 44
			p = u.u_procp;
E 44
I 44
			p = curp;
E 44
		else
D 75
			p = pfind(uap->who);
E 75
I 75
			p = pfind(SCARG(uap, who));
E 75
E 18
		if (p == 0)
D 36
			return;
E 36
I 36
			break;
E 36
D 44
		donice(p, uap->prio);
E 44
I 44
D 75
		error = donice(curp, p, uap->prio);
E 75
I 75
		error = donice(curp, p, SCARG(uap, prio));
E 75
E 44
I 31
		found++;
E 31
		break;

D 39
	case PRIO_PGRP:
E 39
I 39
	case PRIO_PGRP: {
		register struct pgrp *pg;
		 
E 39
I 18
D 75
		if (uap->who == 0)
E 75
I 75
		if (SCARG(uap, who) == 0)
E 75
D 39
			uap->who = u.u_procp->p_pgrp;
E 18
D 29
		for (p = proc; p < procNPROC; p++)
E 29
I 29
		for (p = allproc; p != NULL; p = p->p_nxt)
E 29
D 31
			if (p->p_pgrp == uap->who)
E 31
I 31
			if (p->p_pgrp == uap->who) {
E 31
				donice(p, uap->prio);
I 31
				found++;
			}
E 39
I 39
D 44
			pg = u.u_procp->p_pgrp;
E 44
I 44
			pg = curp->p_pgrp;
E 44
D 75
		else if ((pg = pgfind(uap->who)) == NULL)
E 75
I 75
		else if ((pg = pgfind(SCARG(uap, who))) == NULL)
E 75
			break;
D 73
		for (p = pg->pg_mem; p != NULL; p = p->p_pgrpnxt) {
E 73
I 73
D 75
		for (p = pg->pg_members.lh_first; p != 0; p = p->p_pglist.le_next) {
E 73
D 44
			donice(p, uap->prio);
E 44
I 44
			error = donice(curp, p, uap->prio);
E 75
I 75
		for (p = pg->pg_members.lh_first; p != 0;
		    p = p->p_pglist.le_next) {
			error = donice(curp, p, SCARG(uap, prio));
E 75
E 44
			found++;
		}
E 39
E 31
		break;
I 39
	}
E 39

I 18
	case PRIO_USER:
D 75
		if (uap->who == 0)
D 44
			uap->who = u.u_uid;
E 44
I 44
D 46
			uap->who = p->p_uid;
E 46
I 46
			uap->who = curp->p_ucred->cr_uid;
E 75
I 75
		if (SCARG(uap, who) == 0)
			SCARG(uap, who) = curp->p_ucred->cr_uid;
E 75
E 46
E 44
D 29
		for (p = proc; p < procNPROC; p++)
E 29
I 29
D 55
		for (p = allproc; p != NULL; p = p->p_nxt)
E 55
I 55
D 70
		for (p = (struct proc *)allproc; p != NULL; p = p->p_nxt)
E 70
I 70
D 73
		for (p = (struct proc *)allproc; p != NULL; p = p->p_next)
E 73
I 73
		for (p = allproc.lh_first; p != 0; p = p->p_list.le_next)
E 73
E 70
E 55
E 29
D 31
			if (p->p_uid == uap->who)
E 31
I 31
D 46
			if (p->p_uid == uap->who) {
E 46
I 46
D 75
			if (p->p_ucred->cr_uid == uap->who) {
E 46
E 31
D 44
				donice(p, uap->prio);
E 44
I 44
				error = donice(curp, p, uap->prio);
E 75
I 75
			if (p->p_ucred->cr_uid == SCARG(uap, who)) {
				error = donice(curp, p, SCARG(uap, prio));
E 75
E 44
I 31
				found++;
			}
E 31
		break;

E 18
	default:
D 44
		u.u_error = EINVAL;
D 31
		break;
E 31
I 31
		return;
E 44
I 44
D 45
		RETURN (EINVAL);
E 45
I 45
		return (EINVAL);
E 45
E 44
E 31
	}
I 31
	if (found == 0)
D 44
		u.u_error = ESRCH;
E 44
I 44
D 45
		RETURN (ESRCH);
	RETURN (0);
E 45
I 45
		return (ESRCH);
D 71
	return (0);
E 71
I 71
	return (error);
E 71
E 45
E 44
E 31
}

I 75
int
E 75
D 44
donice(p, n)
	register struct proc *p;
E 44
I 44
donice(curp, chgp, n)
	register struct proc *curp, *chgp;
E 44
	register int n;
{
I 46
	register struct pcred *pcred = curp->p_cred;
E 46

D 43
	if (u.u_uid && u.u_ruid &&
	    u.u_uid != p->p_uid && u.u_ruid != p->p_uid) {
E 43
I 43
D 44
	if (u.u_uid && u.u_procp->p_ruid &&
	    u.u_uid != p->p_uid && u.u_procp->p_ruid != p->p_uid) {
E 43
D 18
		u.u_error = EPERM;
E 18
I 18
D 33
		u.u_error = EACCES;
E 33
I 33
		u.u_error = EPERM;
E 33
E 18
		return;
	}
E 44
I 44
D 46
	if (curp->p_uid && curp->p_ruid &&
	    curp->p_uid != chgp->p_uid && curp->p_ruid != chgp->p_uid)
E 46
I 46
	if (pcred->pc_ucred->cr_uid && pcred->p_ruid &&
	    pcred->pc_ucred->cr_uid != chgp->p_ucred->cr_uid &&
	    pcred->p_ruid != chgp->p_ucred->cr_uid)
E 46
		return (EPERM);
E 44
D 18
	n += p->p_nice;
E 18
I 18
D 31
	n += NZERO;
E 18
	if (n >= 2*NZERO)
		n = 2*NZERO - 1;
	if (n < 0)
		n = 0;
E 31
I 31
	if (n > PRIO_MAX)
		n = PRIO_MAX;
	if (n < PRIO_MIN)
		n = PRIO_MIN;
E 31
D 18
	if (n < p->p_nice && !suser())
E 18
I 18
D 40
	if (n < p->p_nice && !suser()) {
E 40
I 40
D 44
	if (n < p->p_nice && suser(u.u_cred, &u.u_acflag)) {
E 40
		u.u_error = EACCES;
E 18
		return;
I 18
	}
E 18
	p->p_nice = n;
	(void) setpri(p);
E 44
I 44
D 46
	if (n < chgp->p_nice && suser(u.u_cred, &u.u_acflag))
E 46
I 46
	if (n < chgp->p_nice && suser(pcred->pc_ucred, &curp->p_acflag))
E 46
		return (EACCES);
	chgp->p_nice = n;
D 69
	(void) setpri(chgp);
E 69
I 69
	(void)resetpriority(chgp);
E 69
	return (0);
E 44
D 31
	if (u.u_error == ESRCH)
		u.u_error = 0;
E 31
}

I 53
D 54
#ifdef COMPAT_43
E 54
I 54
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
I 61
D 75
struct setrlimit_args {
	u_int	which;
	struct	orlimit *lim;
};
E 75
E 61
E 54
E 53
D 17
setlimit()
E 17
I 17
D 44
setrlimit()
E 17
{
	register struct a {
E 44
I 44
/* ARGSUSED */
D 66
setrlimit(p, uap, retval)
E 66
I 66
D 75
osetrlimit(p, uap, retval)
E 75
I 75
int
compat_43_setrlimit(p, uap, retval)
E 75
E 66
	struct proc *p;
D 61
	register struct args {
E 44
		u_int	which;
D 53
		struct	rlimit *lim;
E 53
I 53
		struct	orlimit *lim;
E 53
D 44
	} *uap = (struct a *)u.u_ap;
E 44
I 44
	} *uap;
E 61
I 61
D 75
	register struct setrlimit_args *uap;
E 61
	int *retval;
E 75
I 75
	struct compat_43_setrlimit_args /* {
		syscallarg(u_int) which;
		syscallarg(struct ogetrlimit *) rlp;
	} */ *uap;
	register_t *retval;
E 75
{
E 44
D 53
	struct rlimit alim;
	register struct rlimit *alimp;
I 32
D 35
	extern int maxdmap;
E 35
I 35
	extern unsigned maxdmap;
E 53
I 53
	struct orlimit olim;
	struct rlimit lim;
E 53
I 44
	int error;
E 44
E 35
E 32

I 53
D 75
	if (error =
	    copyin((caddr_t)uap->lim, (caddr_t)&olim, sizeof (struct orlimit)))
E 75
I 75
	if (error = copyin((caddr_t)SCARG(uap, rlp), (caddr_t)&olim,
	    sizeof (struct orlimit)))
E 75
		return (error);
	lim.rlim_cur = olim.rlim_cur;
	lim.rlim_max = olim.rlim_max;
D 75
	return (dosetrlimit(p, uap->which, &lim));
E 75
I 75
	return (dosetrlimit(p, SCARG(uap, which), &lim));
E 75
}

I 61
D 75
struct getrlimit_args {
	u_int	which;
	struct	orlimit *rlp;
};
E 75
E 61
/* ARGSUSED */
D 66
getrlimit(p, uap, retval)
E 66
I 66
D 75
ogetrlimit(p, uap, retval)
E 75
I 75
int
compat_43_getrlimit(p, uap, retval)
E 75
E 66
	struct proc *p;
D 61
	register struct args {
		u_int	which;
		struct	orlimit *rlp;
	} *uap;
E 61
I 61
D 75
	register struct getrlimit_args *uap;
E 61
	int *retval;
E 75
I 75
	register struct compat_43_getrlimit_args /* {
		syscallarg(u_int) which;
		syscallarg(struct ogetrlimit *) rlp;
	} */ *uap;
	register_t *retval;
E 75
{
	struct orlimit olim;

E 53
D 44
	if (uap->which >= RLIM_NLIMITS) {
		u.u_error = EINVAL;
		return;
	}
E 44
I 44
D 75
	if (uap->which >= RLIM_NLIMITS)
E 75
I 75
	if (SCARG(uap, which) >= RLIM_NLIMITS)
E 75
D 45
		RETURN (EINVAL);
E 45
I 45
		return (EINVAL);
E 45
E 44
D 46
	alimp = &u.u_rlimit[uap->which];
E 46
I 46
D 53
	alimp = &p->p_rlimit[uap->which];
E 53
I 53
D 75
	olim.rlim_cur = p->p_rlimit[uap->which].rlim_cur;
E 75
I 75
	olim.rlim_cur = p->p_rlimit[SCARG(uap, which)].rlim_cur;
E 75
	if (olim.rlim_cur == -1)
		olim.rlim_cur = 0x7fffffff;
D 75
	olim.rlim_max = p->p_rlimit[uap->which].rlim_max;
E 75
I 75
	olim.rlim_max = p->p_rlimit[SCARG(uap, which)].rlim_max;
E 75
	if (olim.rlim_max == -1)
		olim.rlim_max = 0x7fffffff;
D 75
	return (copyout((caddr_t)&olim, (caddr_t)uap->rlp, sizeof(olim)));
E 75
I 75
	return (copyout((caddr_t)&olim, (caddr_t)SCARG(uap, rlp),
	    sizeof(olim)));
E 75
}
D 54
#endif /* COMPAT_43 */
E 54
I 54
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 54

I 61
D 75
struct __setrlimit_args {
	u_int	which;
	struct	rlimit *lim;
};
E 75
E 61
/* ARGSUSED */
I 75
int
E 75
D 67
__setrlimit(p, uap, retval)
E 67
I 67
setrlimit(p, uap, retval)
E 67
	struct proc *p;
D 61
	register struct args {
		u_int	which;
		struct	rlimit *lim;
	} *uap;
E 61
I 61
D 75
	register struct __setrlimit_args *uap;
E 61
	int *retval;
E 75
I 75
	register struct setrlimit_args /* {
		syscallarg(u_int) which;
		syscallarg(struct rlimit *) rlp;
	} */ *uap;
	register_t *retval;
E 75
{
	struct rlimit alim;
	int error;

E 53
E 46
D 23
	if (copyin((caddr_t)uap->lim, (caddr_t)&alim, sizeof (struct rlimit))) {
		u.u_error = EFAULT;
E 23
I 23
D 44
	u.u_error = copyin((caddr_t)uap->lim, (caddr_t)&alim,
		sizeof (struct rlimit));
	if (u.u_error)
E 23
		return;
E 44
I 44
D 75
	if (error =
	    copyin((caddr_t)uap->lim, (caddr_t)&alim, sizeof (struct rlimit)))
E 75
I 75
	if (error = copyin((caddr_t)SCARG(uap, rlp), (caddr_t)&alim,
	    sizeof (struct rlimit)))
E 75
D 45
		RETURN (error);
E 45
I 45
		return (error);
E 45
E 44
D 23
	}
E 23
D 53
	if (alim.rlim_cur > alimp->rlim_max || alim.rlim_max > alimp->rlim_max)
E 53
I 53
D 75
	return (dosetrlimit(p, uap->which, &alim));
E 75
I 75
	return (dosetrlimit(p, SCARG(uap, which), &alim));
E 75
}

I 75
int
E 75
dosetrlimit(p, which, limp)
	struct proc *p;
	u_int which;
	struct rlimit *limp;
{
	register struct rlimit *alimp;
	extern unsigned maxdmap;
	int error;

	if (which >= RLIM_NLIMITS)
		return (EINVAL);
	alimp = &p->p_rlimit[which];
	if (limp->rlim_cur > alimp->rlim_max || 
	    limp->rlim_max > alimp->rlim_max)
E 53
D 40
		if (!suser())
E 40
I 40
D 44
		if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 40
			return;
E 44
I 44
D 46
		if (error = suser(u.u_cred, &u.u_acflag))
E 46
I 46
		if (error = suser(p->p_ucred, &p->p_acflag))
E 46
D 45
			RETURN (error);
E 45
I 45
			return (error);
I 51
D 53
	if (alim.rlim_cur > alim.rlim_max)
		alim.rlim_cur = alim.rlim_max;
E 53
I 53
	if (limp->rlim_cur > limp->rlim_max)
		limp->rlim_cur = limp->rlim_max;
E 53
E 51
I 46
	if (p->p_limit->p_refcnt > 1 &&
	    (p->p_limit->p_lflags & PL_SHAREMOD) == 0) {
		p->p_limit->p_refcnt--;
		p->p_limit = limcopy(p->p_limit);
I 50
D 53
		alimp = &p->p_rlimit[uap->which];
E 53
I 53
		alimp = &p->p_rlimit[which];
E 53
E 50
	}

E 46
E 45
E 44
D 53
	switch (uap->which) {
E 53
I 53
	switch (which) {
E 53

	case RLIMIT_DATA:
D 32
		if (alim.rlim_cur > ctob(MAXDSIZ))
			alim.rlim_cur = ctob(MAXDSIZ);
E 32
I 32
D 53
		if (alim.rlim_cur > maxdmap)
			alim.rlim_cur = maxdmap;
		if (alim.rlim_max > maxdmap)
			alim.rlim_max = maxdmap;
E 53
I 53
		if (limp->rlim_cur > maxdmap)
			limp->rlim_cur = maxdmap;
		if (limp->rlim_max > maxdmap)
			limp->rlim_max = maxdmap;
E 53
E 32
		break;

	case RLIMIT_STACK:
D 32
		if (alim.rlim_cur > ctob(MAXSSIZ))
			alim.rlim_cur = ctob(MAXSSIZ);
E 32
I 32
D 53
		if (alim.rlim_cur > maxdmap)
			alim.rlim_cur = maxdmap;
		if (alim.rlim_max > maxdmap)
			alim.rlim_max = maxdmap;
E 53
I 53
		if (limp->rlim_cur > maxdmap)
			limp->rlim_cur = maxdmap;
		if (limp->rlim_max > maxdmap)
			limp->rlim_max = maxdmap;
E 53
I 48
		/*
		 * Stack is allocated to the max at exec time with only
		 * "rlim_cur" bytes accessible.  If stack limit is going
		 * up make more accessible, if going down make inaccessible.
		 */
D 53
		if (alim.rlim_cur != alimp->rlim_cur) {
E 53
I 53
		if (limp->rlim_cur != alimp->rlim_cur) {
E 53
			vm_offset_t addr;
			vm_size_t size;
			vm_prot_t prot;

D 53
			if (alim.rlim_cur > alimp->rlim_cur) {
E 53
I 53
			if (limp->rlim_cur > alimp->rlim_cur) {
E 53
				prot = VM_PROT_ALL;
D 53
				size = alim.rlim_cur - alimp->rlim_cur;
				addr = USRSTACK - alim.rlim_cur;
E 53
I 53
				size = limp->rlim_cur - alimp->rlim_cur;
				addr = USRSTACK - limp->rlim_cur;
E 53
			} else {
				prot = VM_PROT_NONE;
D 53
				size = alimp->rlim_cur - alim.rlim_cur;
E 53
I 53
				size = alimp->rlim_cur - limp->rlim_cur;
E 53
				addr = USRSTACK - alimp->rlim_cur;
			}
			addr = trunc_page(addr);
			size = round_page(size);
			(void) vm_map_protect(&p->p_vmspace->vm_map,
					      addr, addr+size, prot, FALSE);
		}
I 63
		break;

	case RLIMIT_NOFILE:
		if (limp->rlim_cur > maxfiles)
			limp->rlim_cur = maxfiles;
		if (limp->rlim_max > maxfiles)
			limp->rlim_max = maxfiles;
E 63
E 48
E 32
		break;
I 65

	case RLIMIT_NPROC:
		if (limp->rlim_cur > maxproc)
			limp->rlim_cur = maxproc;
		if (limp->rlim_max > maxproc)
			limp->rlim_max = maxproc;
		break;
E 65
	}
D 47
	*alimp = alim;
E 47
I 47
D 50
	p->p_rlimit[uap->which] = alim;
E 50
I 50
D 53
	*alimp = alim;
E 53
I 53
	*alimp = *limp;
E 53
E 50
E 47
D 46
	if (uap->which == RLIMIT_RSS)
D 44
		u.u_procp->p_maxrss = alim.rlim_cur/NBPG;
E 44
I 44
		p->p_maxrss = alim.rlim_cur/NBPG;
E 46
D 45
	RETURN (0);
E 45
I 45
	return (0);
E 45
E 44
}

I 61
D 75
struct __getrlimit_args {
	u_int	which;
	struct	rlimit *rlp;
};
E 75
E 61
D 17
getlimit()
E 17
I 17
D 44
getrlimit()
E 17
{
	register struct a {
E 44
I 44
/* ARGSUSED */
I 75
int
E 75
D 53
getrlimit(p, uap, retval)
E 53
I 53
D 67
__getrlimit(p, uap, retval)
E 67
I 67
getrlimit(p, uap, retval)
E 67
E 53
	struct proc *p;
D 61
	register struct args {
E 44
		u_int	which;
		struct	rlimit *rlp;
D 44
	} *uap = (struct a *)u.u_ap;
E 44
I 44
	} *uap;
E 61
I 61
D 75
	register struct __getrlimit_args *uap;
E 61
	int *retval;
E 75
I 75
	register struct getrlimit_args /* {
		syscallarg(u_int) which;
		syscallarg(struct rlimit *) rlp;
	} */ *uap;
	register_t *retval;
E 75
{
E 44

D 44
	if (uap->which >= RLIM_NLIMITS) {
		u.u_error = EINVAL;
		return;
	}
D 20
	if (copyout((caddr_t)&u.u_rlimit[uap->which], uap->rlp,
E 20
I 20
D 23
	if (copyout((caddr_t)&u.u_rlimit[uap->which], (caddr_t)uap->rlp,
E 20
	    sizeof (struct rlimit))) {
		u.u_error = EFAULT;
		return;
	}
E 23
I 23
	u.u_error = copyout((caddr_t)&u.u_rlimit[uap->which], (caddr_t)uap->rlp,
	    sizeof (struct rlimit));
E 44
I 44
D 75
	if (uap->which >= RLIM_NLIMITS)
E 75
I 75
	if (SCARG(uap, which) >= RLIM_NLIMITS)
E 75
D 45
		RETURN (EINVAL);
	RETURN (copyout((caddr_t)&u.u_rlimit[uap->which], (caddr_t)uap->rlp,
E 45
I 45
		return (EINVAL);
D 46
	return (copyout((caddr_t)&u.u_rlimit[uap->which], (caddr_t)uap->rlp,
E 46
I 46
D 75
	return (copyout((caddr_t)&p->p_rlimit[uap->which], (caddr_t)uap->rlp,
E 46
E 45
	    sizeof (struct rlimit)));
E 75
I 75
	return (copyout((caddr_t)&p->p_rlimit[SCARG(uap, which)],
	    (caddr_t)SCARG(uap, rlp), sizeof (struct rlimit)));
E 75
E 44
E 23
}

I 55
/*
 * Transform the running time and tick information in proc p into user,
 * system, and interrupt time usage.
 */
I 74
void
E 74
calcru(p, up, sp, ip)
	register struct proc *p;
	register struct timeval *up;
	register struct timeval *sp;
	register struct timeval *ip;
{
D 59
	register u_quad_t usec, st, ut, it, tot;
	struct timeval rtime;
	int s;
E 59
I 59
	register u_quad_t u, st, ut, it, tot;
	register u_long sec, usec;
	register int s;
	struct timeval tv;
E 59

D 59
	/* Get a consistent picture, then do the computation. */
E 59
	s = splstatclock();
	st = p->p_sticks;
	ut = p->p_uticks;
	it = p->p_iticks;
D 59
	rtime = p->p_rtime;
E 59
	splx(s);

	tot = st + ut + it;
	if (tot == 0) {
		up->tv_sec = up->tv_usec = 0;
		sp->tv_sec = sp->tv_usec = 0;
		if (ip != NULL)
			ip->tv_sec = ip->tv_usec = 0;
		return;
	}
D 59
	usec = rtime.tv_sec * 1000000 + rtime.tv_usec;
	st = (usec * st) / tot;
E 59
I 59

	sec = p->p_rtime.tv_sec;
	usec = p->p_rtime.tv_usec;
	if (p == curproc) {
		/*
		 * Adjust for the current time slice.  This is actually fairly
		 * important since the error here is on the order of a time
		 * quantum, which is much greater than the sampling error.
		 */
		microtime(&tv);
		sec += tv.tv_sec - runtime.tv_sec;
		usec += tv.tv_usec - runtime.tv_usec;
	}
	u = sec * 1000000 + usec;
	st = (u * st) / tot;
E 59
	sp->tv_sec = st / 1000000;
	sp->tv_usec = st % 1000000;
D 59
	ut = (usec * ut) / tot;
E 59
I 59
	ut = (u * ut) / tot;
E 59
	up->tv_sec = ut / 1000000;
	up->tv_usec = ut % 1000000;
	if (ip != NULL) {
D 59
		it = (usec * it) / tot;
E 59
I 59
		it = (u * it) / tot;
E 59
		ip->tv_sec = it / 1000000;
		ip->tv_usec = it % 1000000;
	}
}

I 61
D 75
struct getrusage_args {
	int	who;
	struct	rusage *rusage;
};
E 75
E 61
E 55
D 44
getrusage()
{
	register struct a {
E 44
I 44
/* ARGSUSED */
I 75
int
E 75
getrusage(p, uap, retval)
	register struct proc *p;
D 61
	register struct args {
E 44
		int	who;
		struct	rusage *rusage;
D 44
	} *uap = (struct a *)u.u_ap;
E 44
I 44
	} *uap;
E 61
I 61
D 75
	register struct getrusage_args *uap;
E 61
	int *retval;
E 75
I 75
	register struct getrusage_args /* {
		syscallarg(int) who;
		syscallarg(struct rusage *) rusage;
	} */ *uap;
	register_t *retval;
E 75
{
E 44
	register struct rusage *rup;
I 42
D 44
	struct proc *p = u.u_procp;
E 44
E 42

D 75
	switch (uap->who) {
E 75
I 75
	switch (SCARG(uap, who)) {
E 75

D 42
	case RUSAGE_SELF:
E 42
I 42
D 59
	case RUSAGE_SELF: {
E 59
I 59
	case RUSAGE_SELF:
E 59
D 55
		int s;

E 55
E 42
D 46
		rup = &u.u_ru;
E 46
I 46
		rup = &p->p_stats->p_ru;
E 46
I 42
D 55
		s = splclock();
		rup->ru_stime = p->p_stime;
		rup->ru_utime = p->p_utime;
		splx(s);
E 55
I 55
D 59
		calcru(p, &rup->ru_utime, rup->ru_stime, NULL);
E 59
I 59
		calcru(p, &rup->ru_utime, &rup->ru_stime, NULL);
E 59
E 55
E 42
		break;
I 42
D 59
	}
E 59
E 42

	case RUSAGE_CHILDREN:
D 46
		rup = &u.u_cru;
E 46
I 46
		rup = &p->p_stats->p_cru;
E 46
		break;

	default:
D 44
		u.u_error = EINVAL;
		return;
E 44
I 44
D 45
		RETURN (EINVAL);
E 45
I 45
		return (EINVAL);
E 45
E 44
	}
D 20
	if (copyout((caddr_t)rup, uap->rusage, sizeof (struct rusage))) {
E 20
I 20
D 23
	if (copyout((caddr_t)rup, (caddr_t)uap->rusage,
	    sizeof (struct rusage))) {
E 20
		u.u_error = EFAULT;
		return;
	}
E 23
I 23
D 44
	u.u_error = copyout((caddr_t)rup, (caddr_t)uap->rusage,
	    sizeof (struct rusage));
E 44
I 44
D 45
	RETURN (copyout((caddr_t)rup, (caddr_t)uap->rusage,
E 45
I 45
D 75
	return (copyout((caddr_t)rup, (caddr_t)uap->rusage,
E 75
I 75
	return (copyout((caddr_t)rup, (caddr_t)SCARG(uap, rusage),
E 75
E 45
	    sizeof (struct rusage)));
E 44
E 23
}

I 74
void
E 74
ruadd(ru, ru2)
	register struct rusage *ru, *ru2;
{
D 19
	register int *ip, *ip2;
E 19
I 19
D 21
	register u_int *ip, *ip2;
E 21
I 21
	register long *ip, *ip2;
E 21
E 19
	register int i;

	timevaladd(&ru->ru_utime, &ru2->ru_utime);
	timevaladd(&ru->ru_stime, &ru2->ru_stime);
	if (ru->ru_maxrss < ru2->ru_maxrss)
		ru->ru_maxrss = ru2->ru_maxrss;
	ip = &ru->ru_first; ip2 = &ru2->ru_first;
D 52
	for (i = &ru->ru_last - &ru->ru_first; i > 0; i--)
E 52
I 52
	for (i = &ru->ru_last - &ru->ru_first; i >= 0; i--)
E 52
		*ip++ += *ip2++;
I 46
}

/*
 * Make a copy of the plimit structure.
 * We share these structures copy-on-write after fork,
 * and copy when a limit is changed.
 */
struct plimit *
limcopy(lim)
	struct plimit *lim;
{
	register struct plimit *copy;

	MALLOC(copy, struct plimit *, sizeof(struct plimit),
	    M_SUBPROC, M_WAITOK);
	bcopy(lim->pl_rlimit, copy->pl_rlimit,
	    sizeof(struct rlimit) * RLIM_NLIMITS);
	copy->p_lflags = 0;
	copy->p_refcnt = 1;
	return (copy);
E 46
}
D 27

E 16
I 6
D 17
struct	inode *acctp;
I 14
struct	inode *savacctp;
E 14

I 14
long	acctlow	= 2;		/* stop accounting when < 2% data space left */
long	accthigh = 4;		/* resume when space risen to > 4% */

E 14
E 6
/*
 * Perform process accounting functions.
 */
D 6

E 6
sysacct()
E 17
I 17
#ifndef NOCOMPAT
onice()
E 17
{
D 17
	register struct inode *ip;
E 17
	register struct a {
D 17
		char	*fname;
E 17
I 17
		int	niceness;
E 17
D 18
	} *uap;
E 18
I 18
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
E 18

D 18
	uap = (struct a *)u.u_ap;
D 17
	if (suser()) {
I 14
		if (savacctp) {
			acctp = savacctp;
			savacctp = NULL;
		}
E 14
		if (uap->fname==NULL) {
D 7
			if (acctp) {
				plock(acctp);
				iput(acctp);
E 7
I 7
			if (ip = acctp) {
D 8
				plock(ip);
E 8
I 8
D 11
				ilock(ip);
E 8
				iput(ip);
E 11
I 11
				irele(ip);
E 11
E 7
				acctp = NULL;
			}
			return;
		}
D 13
		if (acctp) {
			u.u_error = EBUSY;
			return;
		}
E 13
D 9
		ip = namei(uchar, 0);
E 9
I 9
		ip = namei(uchar, 0, 1);
E 9
		if(ip == NULL)
			return;
		if((ip->i_mode & IFMT) != IFREG) {
			u.u_error = EACCES;
			iput(ip);
			return;
		}
I 13
		if (acctp && (acctp->i_number != ip->i_number ||
		    acctp->i_dev != ip->i_dev))
			irele(acctp);
E 13
		acctp = ip;
D 8
		prele(ip);
E 8
I 8
D 10
		irele(ip);
E 10
I 10
		iunlock(ip);
E 10
E 8
	}
E 17
I 17
	donice(u.u_procp, uap->niceness);
E 18
I 18
	donice(p, (p->p_nice-NZERO)+uap->niceness);
E 18
E 17
}
I 17
D 18
#endif
E 18
E 17

I 18
#include "../h/times.h"

E 18
I 6
D 17
struct	acct acctbuf;
E 6
/*
 * On exit, write a record on the accounting file.
 */
acct()
E 17
I 17
otimes()
E 17
{
I 18
	register struct a {
		struct	tms *tmsb;
	} *uap = (struct a *)u.u_ap;
	struct tms atms;
E 18
D 17
	register i;
	register struct inode *ip;
	off_t siz;
I 6
	register struct acct *ap = &acctbuf;
E 17
E 6

I 14
D 17
	if (savacctp && savacctp->i_fs->fs_cstotal.cs_nbfree >
	    accthigh * savacctp->i_fs->fs_dsize / 100) {
		acctp = savacctp;
		savacctp = NULL;
		printf("Accounting resumed\n");
	}
E 14
	if ((ip=acctp)==NULL)
		return;
I 14
	if (acctp->i_fs->fs_cstotal.cs_nbfree <
	    acctlow * acctp->i_fs->fs_dsize / 100) {
		savacctp = acctp;
		acctp = NULL;
		printf("Accounting suspended\n");
		return;
	}
E 14
D 8
	plock(ip);
E 8
I 8
	ilock(ip);
E 8
D 6
	for (i=0; i<sizeof(acctbuf.ac_comm); i++)
		acctbuf.ac_comm[i] = u.u_comm[i];
D 5
	acctbuf.ac_utime = compress(u.u_vm.vm_utime);
	acctbuf.ac_stime = compress(u.u_vm.vm_stime);
	acctbuf.ac_etime = compress(time - u.u_start);
E 5
I 5
	acctbuf.ac_utime = compress((long)u.u_vm.vm_utime);
	acctbuf.ac_stime = compress((long)u.u_vm.vm_stime);
	acctbuf.ac_etime = compress((long)(time - u.u_start));
E 5
	acctbuf.ac_btime = u.u_start;
	acctbuf.ac_uid = u.u_ruid;
	acctbuf.ac_gid = u.u_rgid;
	acctbuf.ac_mem = 0;
E 6
I 6
	for (i=0; i<sizeof(ap->ac_comm); i++)
		ap->ac_comm[i] = u.u_comm[i];
D 16
	ap->ac_utime = compress((long)u.u_vm.vm_utime);
	ap->ac_stime = compress((long)u.u_vm.vm_stime);
E 16
I 16
	ap->ac_utime = compress((long)u.u_ru.ru_utime.tv_sec);
	ap->ac_stime = compress((long)u.u_ru.ru_stime.tv_sec);
E 16
	ap->ac_etime = compress((long)(time - u.u_start));
	ap->ac_btime = u.u_start;
	ap->ac_uid = u.u_ruid;
	ap->ac_gid = u.u_rgid;
	ap->ac_mem = 0;
E 6
D 2
	acctbuf.ac_io = 0;
E 2
I 2
D 16
	if (i = u.u_vm.vm_utime + u.u_vm.vm_stime)
D 6
		acctbuf.ac_mem = (u.u_vm.vm_ixrss + u.u_vm.vm_idsrss) / i;
D 5
	acctbuf.ac_io = compress(u.u_vm.vm_inblk + u.u_vm.vm_oublk);
E 5
I 5
	acctbuf.ac_io = compress((long)(u.u_vm.vm_inblk + u.u_vm.vm_oublk));
E 5
E 2
	acctbuf.ac_tty = u.u_ttyd;
	acctbuf.ac_flag = u.u_acflag;
E 6
I 6
		ap->ac_mem = (u.u_vm.vm_ixrss + u.u_vm.vm_idsrss) / i;
	ap->ac_io = compress((long)(u.u_vm.vm_inblk + u.u_vm.vm_oublk));
E 16
I 16
	if (i = u.u_ru.ru_utime.tv_sec + u.u_ru.ru_stime.tv_sec)
		ap->ac_mem =
		    (u.u_ru.ru_ixrss + u.u_ru.ru_idrss + u.u_ru.ru_isrss) / i;
	ap->ac_io = compress((long)(u.u_ru.ru_inblock + u.u_ru.ru_oublock));
E 16
D 13
	ap->ac_tty = u.u_ttyd;
E 13
I 13
	if (u.u_ttyp)
		ap->ac_tty = u.u_ttyd;
	else
		ap->ac_tty = NODEV;
E 13
	ap->ac_flag = u.u_acflag;
E 6
	siz = ip->i_size;
D 15
	u.u_offset = siz;
D 6
	u.u_base = (caddr_t)&acctbuf;
E 6
I 6
	u.u_base = (caddr_t)ap;
E 6
	u.u_count = sizeof(acctbuf);
	u.u_segflg = 1;
	u.u_error = 0;
	writei(ip);
	if(u.u_error)
E 15
I 15
	u.u_error =
	    rdwri(UIO_WRITE, ip, (caddr_t)ap, sizeof (acctbuf), siz,
		1, (int *)0);
	if (u.u_error)
E 15
		ip->i_size = siz;
D 8
	prele(ip);
E 8
I 8
D 10
	irele(ip);
E 10
I 10
	iunlock(ip);
E 17
I 17
D 18
	/* XXX */
E 18
I 18
	atms.tms_utime = scale60(&u.u_ru.ru_utime);
	atms.tms_stime = scale60(&u.u_ru.ru_stime);
	atms.tms_cutime = scale60(&u.u_cru.ru_utime);
	atms.tms_cstime = scale60(&u.u_cru.ru_stime);
D 20
	if (copyout((caddr_t)&atms, uap->tmsb, sizeof (atms))) {
E 20
I 20
D 23
	if (copyout((caddr_t)&atms, (caddr_t)uap->tmsb, sizeof (atms))) {
E 20
		u.u_error = EFAULT;
		return;
	}
E 23
I 23
	u.u_error = copyout((caddr_t)&atms, (caddr_t)uap->tmsb, sizeof (atms));
E 23
E 18
E 17
E 10
E 8
}

I 18
scale60(tvp)
	register struct timeval *tvp;
{

	return (tvp->tv_sec * 60 + tvp->tv_usec / 16667);
}

D 22
#include <vtimes.h>
E 22
I 22
#include "../h/vtimes.h"
E 22

E 18
D 17
/*
 * Produce a pseudo-floating point representation
 * with 3 bits base-8 exponent, 13 bits fraction.
 */
compress(t)
D 5
register time_t t;
E 5
I 5
register long t;
E 17
I 17
ovtimes()
E 17
E 5
{
I 18
	register struct a {
		struct	vtimes *par;
		struct	vtimes *chi;
	} *uap = (struct a *)u.u_ap;
	struct vtimes avt;
E 18
D 17
	register exp = 0, round = 0;
E 17

D 17
	while (t >= 8192) {
		exp++;
		round = t&04;
		t >>= 3;
	}
	if (round) {
		t++;
		if (t >= 8192) {
			t >>= 3;
			exp++;
		}
	}
	return((exp<<13) + t);
E 17
I 17
D 18
	/* XXX */
E 18
I 18
	if (uap->par) {
		getvtimes(&u.u_ru, &avt);
D 23
		if (copyout((caddr_t)&avt, (caddr_t)uap->par, sizeof (avt))) {
			u.u_error = EFAULT;
E 23
I 23
		u.u_error = copyout((caddr_t)&avt, (caddr_t)uap->par,
			sizeof (avt));
		if (u.u_error)
E 23
			return;
D 23
		}
E 23
	}
	if (uap->chi) {
		getvtimes(&u.u_cru, &avt);
D 23
		if (copyout((caddr_t)&avt, (caddr_t)uap->chi, sizeof (avt))) {
			u.u_error = EFAULT;
E 23
I 23
		u.u_error = copyout((caddr_t)&avt, (caddr_t)uap->chi,
			sizeof (avt));
		if (u.u_error)
E 23
			return;
D 23
		}
E 23
	}
E 18
E 17
I 14
}

I 18
getvtimes(aru, avt)
	register struct rusage *aru;
	register struct vtimes *avt;
{

	avt->vm_utime = scale60(&aru->ru_utime);
	avt->vm_stime = scale60(&aru->ru_stime);
	avt->vm_idsrss = ((aru->ru_idrss+aru->ru_isrss) / hz) * 60;
	avt->vm_ixrss = aru->ru_ixrss / hz * 60;
	avt->vm_maxrss = aru->ru_maxrss;
	avt->vm_majflt = aru->ru_majflt;
	avt->vm_minflt = aru->ru_minflt;
	avt->vm_nswap = aru->ru_nswap;
	avt->vm_inblk = aru->ru_inblock;
	avt->vm_oublk = aru->ru_oublock;
}

E 18
D 16
vtimes()
E 16
I 16
D 17
#ifndef NOCOMPAT
onice()
E 17
I 17
ovlimit()
E 17
E 16
{
D 17
	register struct a {
D 16
		struct	vtimes *par_vm;
		struct	vtimes *ch_vm;
	} *uap = (struct a *)u.u_ap;
E 16
I 16
		int	niceness;
	} *uap;
E 17
E 16

I 18
	u.u_error = EACCES;
E 18
D 16
	if (uap->par_vm == 0)
		goto onlych;
	if (copyout((caddr_t)&u.u_vm, (caddr_t)uap->par_vm,
	    sizeof(struct vtimes)) < 0)
		u.u_error = EFAULT;
onlych:
	if (uap->ch_vm == 0)
		return;
	if (copyout((caddr_t)&u.u_cvm, (caddr_t)uap->ch_vm,
	    sizeof(struct vtimes)) < 0)
		u.u_error = EFAULT;
E 16
I 16
D 17
	uap = (struct a *)u.u_ap;
	donice(u.u_procp, uap->niceness);
E 17
E 16
}
E 27
D 16

vmsadd(vp, wp)
	register struct vtimes *vp, *wp;
{

	vp->vm_utime += wp->vm_utime;
	vp->vm_stime += wp->vm_stime;
	vp->vm_nswap += wp->vm_nswap;
	vp->vm_idsrss += wp->vm_idsrss;
	vp->vm_ixrss += wp->vm_ixrss;
	if (vp->vm_maxrss < wp->vm_maxrss)
		vp->vm_maxrss = wp->vm_maxrss;
	vp->vm_majflt += wp->vm_majflt;
	vp->vm_minflt += wp->vm_minflt;
	vp->vm_inblk += wp->vm_inblk;
	vp->vm_oublk += wp->vm_oublk;
E 14
D 7
}

/*
 * lock user into core as much
 * as possible. swapping may still
 * occur if core grows.
 */
syslock()
{
	register struct proc *p;
	register struct a {
		int	flag;
	} *uap;

	uap = (struct a *)u.u_ap;
	if(suser()) {
		p = u.u_procp;
		p->p_flag &= ~SULOCK;
		if(uap->flag)
			p->p_flag |= SULOCK;
	}
E 7
}
E 16
I 16
D 17
#endif
E 17
E 16
E 1
