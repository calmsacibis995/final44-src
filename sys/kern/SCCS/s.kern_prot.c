h56810
s 00123/00113/00452
d D 8.9 95/02/14 10:37:47 cgd 68 67
c new argument passing conventions.  minor type size cleanup.
e
s 00002/00001/00563
d D 8.8 95/01/09 18:22:29 cgd 67 66
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00036/00012/00528
d D 8.7 94/11/01 21:27:09 hibler 66 65
c emulate the other common case of setreuid (setregid):
c setting both effective and real to the same value
e
s 00001/00001/00539
d D 8.6 94/01/21 19:47:30 bostic 65 64
c copyright typo
e
s 00005/00000/00535
d D 8.5 94/01/21 17:17:42 bostic 64 63
c add USL's copyright notice
e
s 00004/00006/00531
d D 8.4 94/01/06 09:14:21 bostic 63 62
c minor simplification of cfree, from Jan-Simon Pendry <jsp@sequent.com>
e
s 00004/00004/00533
d D 8.3 94/01/05 12:01:03 mckusick 62 61
c lint
e
s 00006/00006/00531
d D 8.2 93/09/23 15:36:36 bostic 61 60
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00535
d D 8.1 93/06/10 22:02:17 bostic 60 59
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00535
d D 7.30 92/12/09 19:20:44 marc 59 58
c enterpgrp now returns a value
e
s 00008/00008/00530
d D 7.29 92/12/09 19:20:20 mckusick 58 57
c new include syntax
e
s 00005/00002/00533
d D 7.28 92/07/19 23:45:04 mckusick 57 56
c transfer proc ownership when doing setuid()
e
s 00056/00000/00479
d D 7.27 92/07/13 11:25:12 mckusick 56 55
c put back a semblance of setreuid and setregid compatibility
e
s 00012/00022/00467
d D 7.26 92/07/13 11:05:56 mckusick 55 54
c update to use uid_t and gid_t
e
s 00052/00039/00437
d D 7.25 92/07/10 21:02:08 torek 54 53
c ANSIfy syscall args
e
s 00000/00089/00476
d D 7.24 92/07/09 14:56:01 torek 53 52
c delete osetreuid as it is simulated in libc/compat-43;
c delete osetregid as it is unneeded.
e
s 00007/00000/00558
d D 7.23 92/06/23 19:56:21 mckusick 52 51
c set SUGID when user/group when permissions change (to avoid 
c unscrupulous attaches)
e
s 00005/00005/00553
d D 7.22 92/02/14 17:08:50 torek 51 50
c merge in COMPAT_SUNOS
e
s 00011/00012/00547
d D 7.21 91/05/03 17:30:26 karels 50 49
c in setpgid, check target's pid against pgrp, not ours; don't need "targ" on
c everything
e
s 00020/00020/00539
d D 7.20 91/04/12 17:29:03 marc 49 48
c fix tests in setpgid()
e
s 00090/00083/00469
d D 7.19 91/03/17 15:41:52 karels 48 47
c more-or-less working with new proc & user structs
e
s 00004/00001/00548
d D 7.18 91/02/06 10:01:55 karels 47 46
c fix old comment
e
s 00035/00047/00514
d D 7.17 91/01/10 19:41:31 bostic 46 45
c bug: setgroups never called crcopy(); other stuff, change crcopy to
c not copy if cr_ref == 1, exec code doesn't check; make the comments prettier
e
s 00001/00001/00560
d D 7.16 90/10/19 16:29:11 mckusick 45 44
c copyinstr/copyoutstr now return ENAMETOOLONG when name is too long
e
s 00013/00013/00548
d D 7.15 90/07/26 21:35:14 karels 44 43
c cleaned-up cleanups: make getgroups look like setgroups
e
s 00009/00010/00552
d D 7.14 90/07/23 13:16:29 bostic 43 42
c setgroups check int > NGROUPS, so negative would fail; minor cleanup
e
s 00001/00011/00561
d D 7.13 90/06/28 21:21:06 bostic 42 41
c new copyright notice
e
s 00042/00042/00530
d D 7.12 90/06/28 17:10:45 karels 41 40
c RETURN => return, remove syscontext.h
e
s 00322/00149/00250
d D 7.11 90/06/21 21:42:57 karels 40 39
c add setuid, seteuid, setgid, setegid per POSIX proposal;
c break out geteuid, getegid, getppid; new syscall convention
e
s 00000/00001/00399
d D 7.10 90/05/04 14:11:12 mckusick 39 38
c delete unneeded headers
e
s 00000/00006/00400
d D 7.9 90/04/27 09:56:24 mckusick 38 37
c no longer have per user quota structures
e
s 00060/00052/00346
d D 7.8 90/03/31 14:45:09 karels 37 36
c move euids, etc. to proc (for signals); mv logname there (for ps);
c s/[gs]etlogname/[gs]etlogin/
e
s 00003/00001/00395
d D 7.7 89/05/18 18:56:36 kfall 36 35
c setlogname: null terminate name
e
s 00000/00010/00396
d D 7.6 89/05/01 22:30:34 mckusick 35 33
i 34
c integrate back branch -r7.1.1.1
e
s 00123/00065/00193
d D 7.1.1.1 89/05/01 22:27:34 mckusick 34 28
c merge in vnode changes
e
s 00016/00012/00326
d D 7.5 89/04/26 19:41:43 mckusick 33 32
c use new form of suser()
e
s 00002/00002/00336
d D 7.4 89/04/25 14:42:26 mckusick 32 31
c ../machine => machine
e
s 00037/00000/00301
d D 7.3 89/03/07 00:26:21 kfall 31 30
c add get/set logname system calls
e
s 00055/00012/00246
d D 7.2 88/10/18 15:14:46 marc 30 28
c posix style job control - new process groups
e
s 00001/00001/00257
d R 7.2 87/07/20 15:29:50 mckusick 29 28
c delete unneeded header files
e
s 00001/00001/00257
d D 7.1 86/06/05 00:03:39 mckusick 28 27
c 4.3BSD release version
e
s 00001/00001/00257
d D 6.8 86/02/23 23:09:00 karels 27 26
c lint
e
s 00003/00003/00255
d D 6.7 86/02/20 15:25:16 karels 26 25
c use gid_t consistently
e
s 00001/00001/00257
d D 6.6 85/12/19 14:37:24 karels 25 24
c maintain p_uid with u.u_uid
e
s 00007/00001/00251
d D 6.5 85/06/08 14:37:01 mckusick 24 23
c Add copyright
e
s 00000/00001/00252
d D 6.4 85/03/19 20:48:44 mckusick 23 22
c eliminate extraneous include of conf.h
e
s 00023/00015/00230
d D 6.3 85/03/18 15:18:53 karels 22 21
c add gid_t for groups; copy u.u_groups to int array for copyin/out
e
s 00014/00014/00231
d D 6.2 84/08/29 20:19:56 bloom 21 20
c Change to includes.  no more ../h
e
s 00000/00000/00245
d D 6.1 83/07/29 06:33:30 sam 20 19
c 4.2 distribution
e
s 00000/00077/00245
d D 5.17 83/05/27 12:46:57 sam 19 18
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00028/00002/00294
d D 5.16 83/03/31 13:46:40 sam 18 17
c add NOGROUP identifier; add groupmember function; tighten group 
c lookup loop to stop at first NOGROUP entry
e
s 00003/00007/00293
d D 5.15 83/02/20 14:52:57 sam 17 14
c fix incompatibility between access and setgid
e
s 00004/00008/00292
d R 5.15 83/02/16 18:19:05 sam 16 14
c fix access and problems with setgid and saccess
e
s 00006/00006/00294
d R 5.15 83/02/10 18:41:46 sam 15 14
c groups set members are shorts, not ints; hz no longer in systm.h
e
s 00006/00008/00294
d D 5.14 82/12/28 23:46:46 sam 14 13
c copyin & copyout now return EFAULT and all callers uniformly 
c return (or ignore) this value
e
s 00002/00001/00300
d D 5.13 82/12/17 11:44:18 sam 13 12
c sun merge
e
s 00006/00008/00295
d D 5.12 82/11/22 16:59:08 sam 12 11
c doing it wrong -- p_uid
e
s 00071/00002/00232
d D 5.11 82/11/13 22:50:14 sam 11 10
c merge of 4.1b and 4.1c
e
s 00000/00000/00234
d D 5.10 82/10/20 02:57:56 root 10 9
c lint
e
s 00002/00002/00232
d D 5.9 82/10/17 21:49:03 root 9 8
c more lint
e
s 00000/00001/00234
d D 5.8 82/10/10 15:07:54 root 8 7
c split header files over to vax directories
e
s 00000/00002/00235
d D 5.7 82/09/12 01:57:02 root 7 6
c drop printfs
e
s 00003/00002/00234
d D 5.6 82/09/06 22:49:04 root 6 5
c 
e
s 00001/00001/00235
d D 5.5 82/08/24 23:24:17 root 5 4
c nit bug
e
s 00057/00031/00179
d D 5.4 82/08/24 15:04:57 root 4 3
c new groups stuff
e
s 00144/00008/00066
d D 5.3 82/07/24 18:09:55 root 3 2
c merge with calder
e
s 00007/00000/00067
d D 5.2 82/07/22 13:22:57 kre 2 1
c disc quotas / mush
e
s 00067/00000/00000
d D 5.1 82/07/15 20:11:02 root 1 0
c date and time created 82/07/15 20:11:02 by root
e
u
U
f b 
t
T
I 1
D 24
/*	%M%	%I%	%E%	*/
E 24
I 24
/*
D 28
 * Copyright (c) 1982 Regents of the University of California.
E 28
I 28
D 34
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 28
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 34
I 34
D 40
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 40
I 40
D 48
 * Copyright (c) 1982, 1986, 1989, 1990 Regents of the University of California.
E 40
 * All rights reserved.
E 48
I 48
D 60
 * Copyright (c) 1982, 1986, 1989, 1990, 1991 Regents of the University
 * of California.  All rights reserved.
E 60
I 60
 * Copyright (c) 1982, 1986, 1989, 1990, 1991, 1993
D 65
 *	Regents of the University of California.  All rights reserved.
E 65
I 65
 *	The Regents of the University of California.  All rights reserved.
E 65
I 64
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 64
E 60
E 48
E 34
 *
I 34
D 42
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
E 42
I 42
 * %sccs.include.redist.c%
E 42
 *
E 34
 *	%W% (Berkeley) %G%
 */
E 24

/*
D 3
 * System calls related to protection
E 3
I 3
 * System calls related to processes and protection
E 3
 */

I 13
D 32
D 34
#include "../machine/reg.h"
E 34
I 34
D 35
#include "machine/reg.h"
E 35
E 34

E 32
E 13
I 3
D 4
/* NEED ALLOCATION AND PROTECTION MECHANISM FOR PROCESS GROUPS */

E 4
E 3
D 21
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
D 13
#include "../h/reg.h"
E 13
#include "../h/inode.h"
#include "../h/proc.h"
D 6
#include "../h/clock.h"
E 6
D 8
#include "../h/mtpr.h"
E 8
#include "../h/timeb.h"
#include "../h/times.h"
#include "../h/reboot.h"
#include "../h/fs.h"
#include "../h/conf.h"
#include "../h/buf.h"
#include "../h/mount.h"
I 2
#include "../h/quota.h"
E 21
I 21
D 58
#include "param.h"
I 34
#include "acct.h"
E 34
#include "systm.h"
D 34
#include "dir.h"
E 34
D 40
#include "user.h"
E 40
I 40
D 41
#include "syscontext.h"
E 41
I 41
D 48
#include "user.h"
E 48
I 48
#include "ucred.h"
E 48
E 41
E 40
D 34
#include "inode.h"
E 34
#include "proc.h"
#include "timeb.h"
#include "times.h"
D 40
#include "reboot.h"
D 34
#include "fs.h"
D 23
#include "conf.h"
E 23
#include "buf.h"
E 34
D 39
#include "mount.h"
E 39
D 34
#include "quota.h"
E 34
I 34
#include "buf.h"
#include "../ufs/quota.h"
E 40
#include "malloc.h"
E 58
I 58
#include <sys/param.h>
#include <sys/acct.h>
#include <sys/systm.h>
#include <sys/ucred.h>
#include <sys/proc.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <sys/malloc.h>
E 58
D 37
#define GRPSTART 0
E 37
E 34
I 32

I 54
D 68
struct args {
	int	dummy;
};
E 68
I 68
#include <sys/mount.h>
#include <sys/syscallargs.h>
E 68

E 54
D 40
#include "machine/reg.h"
E 32
E 21
E 2

I 3
getpid()
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
getpid(p, uap, retval)
	struct proc *p;
D 54
	void *uap;
E 54
I 54
D 68
	struct args *uap;
E 54
	int *retval;
E 68
I 68
	void *uap;
	register_t *retval;
E 68
E 40
{

D 40
	u.u_r.r_val1 = u.u_procp->p_pid;
	u.u_r.r_val2 = u.u_procp->p_ppid;
E 40
I 40
	*retval = p->p_pid;
D 51
#ifdef COMPAT_43
E 51
I 51
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 51
D 48
	retval[1] = p->p_ppid;
E 48
I 48
	retval[1] = p->p_pptr->p_pid;
E 48
#endif
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
E 40
}

D 40
getpgrp()
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
getppid(p, uap, retval)
	struct proc *p;
D 54
	void *uap;
E 54
I 54
D 68
	struct args *uap;
E 54
	int *retval;
E 68
I 68
	void *uap;
	register_t *retval;
E 68
E 40
{
D 40
	register struct a {
E 40
I 40

D 48
	*retval = p->p_ppid;
E 48
I 48
	*retval = p->p_pptr->p_pid;
E 48
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
}

I 48
/* Get process group ID; note that POSIX getpgrp takes no parameter */
I 68
int
E 68
E 48
getpgrp(p, uap, retval)
	struct proc *p;
D 48
	struct args {
E 40
		int	pid;
D 40
	} *uap = (struct a *)u.u_ap;
	register struct proc *p;
E 40
I 40
	} *uap;
E 48
I 48
D 54
	void *uap;
E 54
I 54
D 68
	struct args *uap;
E 54
E 48
	int *retval;
E 68
I 68
	void *uap;
	register_t *retval;
E 68
{
E 40

D 40
	if (uap->pid == 0)
D 30
		uap->pid = u.u_procp->p_pid;
	p = pfind(uap->pid);
	if (p == 0) {
E 30
I 30
		p = u.u_procp;
	else if ((p = pfind(uap->pid)) == 0) {
E 30
		u.u_error = ESRCH;
		return;
	}
D 30
	u.u_r.r_val1 = p->p_pgrp;
E 30
I 30
	u.u_r.r_val1 = p->p_pgrp->pg_id;
E 40
I 40
D 48
	if (uap->pid != 0 && (p = pfind(uap->pid)) == 0)
D 41
		RETURN (ESRCH);
E 41
I 41
		return (ESRCH);
E 48
E 41
	*retval = p->p_pgrp->pg_id;
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
E 40
E 30
}

E 3
D 40
getuid()
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
getuid(p, uap, retval)
	struct proc *p;
D 54
	void *uap;
E 54
I 54
D 68
	struct args *uap;
E 54
	int *retval;
E 68
I 68
	void *uap;
	register_t *retval;
E 68
E 40
{

D 37
	u.u_r.r_val1 = u.u_ruid;
	u.u_r.r_val2 = u.u_uid;
E 37
I 37
D 40
	u.u_r.r_val1 = u.u_procp->p_ruid;
	u.u_r.r_val2 = u.u_cred->cr_uid;
E 40
I 40
D 48
	*retval = p->p_ruid;
E 48
I 48
	*retval = p->p_cred->p_ruid;
E 48
D 51
#ifdef COMPAT_43
E 51
I 51
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 51
D 48
	retval[1] = u.u_cred->cr_uid;
E 48
I 48
	retval[1] = p->p_ucred->cr_uid;
E 48
#endif
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
E 40
E 37
}

I 3
D 40
getgid()
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
geteuid(p, uap, retval)
	struct proc *p;
D 54
	void *uap;
E 54
I 54
D 68
	struct args *uap;
E 54
	int *retval;
E 68
I 68
	void *uap;
	register_t *retval;
E 68
E 40
{

D 37
	u.u_r.r_val1 = u.u_rgid;
	u.u_r.r_val2 = u.u_gid;
E 37
I 37
D 40
	u.u_r.r_val1 = u.u_procp->p_rgid;
	u.u_r.r_val2 = u.u_cred->cr_groups[0];
E 40
I 40
D 48
	*retval = u.u_cred->cr_uid;
E 48
I 48
	*retval = p->p_ucred->cr_uid;
E 48
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
E 40
E 37
}

D 4
getgrp()
E 4
I 4
D 40
getgroups()
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
getgid(p, uap, retval)
	struct proc *p;
D 54
	void *uap;
E 54
I 54
D 68
	struct args *uap;
E 54
	int *retval;
E 68
I 68
	void *uap;
	register_t *retval;
E 68
E 40
E 4
{
D 40
	register struct	a {
E 40
I 40

D 48
	*retval = p->p_rgid;
E 48
I 48
	*retval = p->p_cred->p_rgid;
E 48
D 51
#ifdef COMPAT_43
E 51
I 51
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 51
D 48
	retval[1] = u.u_cred->cr_groups[0];
E 48
I 48
	retval[1] = p->p_ucred->cr_groups[0];
E 48
#endif
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
}

/*
D 46
 * Get effective group ID.
 * The "egid" is groups[0], and thus could be obtained via getgroups;
 * this is somewhat painful to do correctly in a library function,
 * this the existence of this syscall.
E 46
I 46
 * Get effective group ID.  The "egid" is groups[0], and could be obtained
 * via getgroups.  This syscall exists because it is somewhat painful to do
 * correctly in a library function.
E 46
 */
/* ARGSUSED */
I 68
int
E 68
getegid(p, uap, retval)
	struct proc *p;
D 54
	void *uap;
E 54
I 54
D 68
	struct args *uap;
E 54
	int *retval;
E 68
I 68
	void *uap;
	register_t *retval;
E 68
{
D 46

E 46
D 48
	*retval = u.u_cred->cr_groups[0];
E 48
I 48

	*retval = p->p_ucred->cr_groups[0];
E 48
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
}

I 54
D 68
struct getgroups_args {
	u_int	gidsetsize;
D 55
	int	*gidset;		/* XXX not yet POSIX */
E 55
I 55
	gid_t	*gidset;
E 55
};
E 68
I 68
int
E 68
E 54
getgroups(p, uap, retval)
	struct proc *p;
D 54
	register struct	arg {
E 40
I 4
D 9
		int	gidsetsize;
E 9
I 9
		u_int	gidsetsize;
E 9
E 4
D 40
		int	*gidset;
	} *uap = (struct a *)u.u_ap;
E 40
I 40
		int	*gidset;		/* XXX not yet POSIX */
	} *uap;
E 54
I 54
D 68
	register struct	getgroups_args *uap;
E 54
	int *retval;
E 68
I 68
	register struct getgroups_args /* {
		syscallarg(u_int) gidsetsize;
		syscallarg(gid_t *) gidset;
	} */ *uap;
	register_t *retval;
E 68
{
I 48
	register struct pcred *pc = p->p_cred;
E 48
E 40
I 4
D 22
	register int *gp;
E 22
I 22
D 55
	register gid_t *gp;
	register int *lp;
E 55
I 44
	register u_int ngrp;
E 44
D 55
	int groups[NGROUPS];
E 55
I 40
	int error;
E 40
E 22
E 4

D 4
	if (copyout((caddr_t)u.u_grps, (caddr_t)uap->gidset,
	    sizeof (u.u_grps))) {
E 4
I 4
D 34
	for (gp = &u.u_groups[NGROUPS]; gp > u.u_groups; gp--)
D 22
		if (gp[-1] >= 0)
E 22
I 22
		if (gp[-1] != NOGROUP)
E 22
			break;
	if (uap->gidsetsize < gp - u.u_groups) {
E 34
I 34
D 44
	if (uap->gidsetsize == 0) {
E 44
I 44
D 68
	if ((ngrp = uap->gidsetsize) == 0) {
E 68
I 68
	if ((ngrp = SCARG(uap, gidsetsize)) == 0) {
E 68
E 44
D 37
		u.u_r.r_val1 = u.u_ngroups - GRPSTART;
E 37
I 37
D 40
		u.u_r.r_val1 = u.u_cred->cr_ngroups;
E 37
		return;
E 40
I 40
D 48
		*retval = u.u_cred->cr_ngroups;
E 48
I 48
		*retval = pc->pc_ucred->cr_ngroups;
E 48
D 41
		RETURN (0);
E 41
I 41
		return (0);
E 41
E 40
	}
D 37
	if (uap->gidsetsize < u.u_ngroups - GRPSTART) {
E 37
I 37
D 40
	if (uap->gidsetsize < u.u_cred->cr_ngroups) {
E 37
E 34
		u.u_error = EINVAL;
		return;
	}
E 40
I 40
D 44
	if (uap->gidsetsize < u.u_cred->cr_ngroups)
E 44
I 44
D 48
	if (ngrp < u.u_cred->cr_ngroups)
E 48
I 48
	if (ngrp < pc->pc_ucred->cr_ngroups)
E 48
E 44
D 41
		RETURN (EINVAL);
E 41
I 41
		return (EINVAL);
E 41
E 40
D 34
	uap->gidsetsize = gp - u.u_groups;
D 14
	if (copyout((caddr_t)u.u_groups, (caddr_t)uap->gidset,
	    uap->gidsetsize * sizeof (u.u_groups[0]))) {
E 4
		u.u_error = EFAULT;
E 14
I 14
D 22
	u.u_error = copyout((caddr_t)u.u_groups, (caddr_t)uap->gidset,
	    uap->gidsetsize * sizeof (u.u_groups[0]));
E 22
I 22
	for (lp = groups, gp = u.u_groups; lp < &groups[uap->gidsetsize]; )
E 34
I 34
D 37
	uap->gidsetsize = u.u_ngroups - GRPSTART;
	gp = &u.u_groups[GRPSTART];
E 37
I 37
D 44
	uap->gidsetsize = u.u_cred->cr_ngroups;
	gp = u.u_cred->cr_groups;
E 37
	for (lp = groups; lp < &groups[uap->gidsetsize]; )
E 44
I 44
D 48
	ngrp = u.u_cred->cr_ngroups;
	for (gp = u.u_cred->cr_groups, lp = groups; lp < &groups[ngrp]; )
E 48
I 48
	ngrp = pc->pc_ucred->cr_ngroups;
D 55
	for (gp = pc->pc_ucred->cr_groups, lp = groups; lp < &groups[ngrp]; )
E 48
E 44
E 34
		*lp++ = *gp++;
D 40
	u.u_error = copyout((caddr_t)groups, (caddr_t)uap->gidset,
	    uap->gidsetsize * sizeof (groups[0]));
E 22
	if (u.u_error)
E 14
		return;
D 14
	}
E 14
I 4
	u.u_r.r_val1 = uap->gidsetsize;
E 40
I 40
	if (error = copyout((caddr_t)groups, (caddr_t)uap->gidset,
D 44
	    uap->gidsetsize * sizeof (groups[0])))
E 44
I 44
	    ngrp * sizeof (groups[0])))
E 55
I 55
	if (error = copyout((caddr_t)pc->pc_ucred->cr_groups,
D 68
	    (caddr_t)uap->gidset, ngrp * sizeof(gid_t)))
E 68
I 68
	    (caddr_t)SCARG(uap, gidset), ngrp * sizeof(gid_t)))
E 68
E 55
E 44
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
D 44
	*retval = uap->gidsetsize;
E 44
I 44
	*retval = ngrp;
E 44
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
E 40
E 4
}

I 30
D 40
setsid()
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
setsid(p, uap, retval)
D 48
	struct proc *p;
E 48
I 48
	register struct proc *p;
E 48
D 54
	void *uap;
E 54
I 54
D 68
	struct args *uap;
E 54
	int *retval;
E 68
I 68
	void *uap;
	register_t *retval;
E 68
E 40
{
D 40
	register struct proc *p = u.u_procp;
E 40

D 40
	if ((p->p_pgid == p->p_pid) || pgfind(p->p_pid))
		u.u_error = EPERM;
	else {
E 40
I 40
	if (p->p_pgid == p->p_pid || pgfind(p->p_pid)) {
D 41
		RETURN (EPERM);
E 41
I 41
		return (EPERM);
E 41
	} else {
E 40
D 48
		pgmv(p, p->p_pid, 1);
E 48
I 48
D 59
		enterpgrp(p, p->p_pid, 1);
E 59
I 59
		(void)enterpgrp(p, p->p_pid, 1);
E 59
E 48
D 40
		u.u_r.r_val1 = p->p_pid;
E 40
I 40
		*retval = p->p_pid;
D 41
		RETURN (0);
E 41
I 41
		return (0);
E 41
E 40
	}
D 40
	return;
E 40
}

/*
D 40
 * set process group
E 40
I 40
D 48
 * set process group (setpgrp/setpgid)
E 48
I 48
 * set process group (setpgid/old setpgrp)
E 48
E 40
 *
D 37
 * if target pid != caller's pid
 *	pid must be an inferior
 *	pid must be in same session
 *	pid can't have done an exec
 *	there must exist a pid with pgid in same session 
 * pid must not be session leader
E 37
I 37
D 48
 * caller does setpgrp(pid, pgid)
E 48
I 48
D 49
 * caller does setpgid(pid, pgid)
E 49
I 49
 * caller does setpgid(targpid, targpgid)
E 49
E 48
 *
 * pid must be caller or child of caller (ESRCH)
 * if a child
 *	pid must be in same session (EPERM)
 *	pid can't have done an exec (EACCES)
 * if pgid != pid
 * 	there must exist some pid in same session having pgid (EPERM)
 * pid must not be session leader (EPERM)
E 37
 */
I 54
D 68
struct setpgid_args {
	int	pid;	/* target process id */
	int	pgid;	/* target pgrp id */
};
E 68
E 54
E 30
D 40
setpgrp()
{
D 30
	register struct proc *p;
E 30
	register struct a {
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
D 48
setpgrp(cp, uap, retval)
E 48
I 48
D 49
setpgid(cp, uap, retval)
E 48
	struct proc *cp;
E 49
I 49
setpgid(curp, uap, retval)
	struct proc *curp;
E 49
D 54
	register struct args {
E 40
D 49
		int	pid;
D 30
		int	pgrp;
E 30
I 30
		int	pgid;
E 49
I 49
D 50
		int	targpid;	/* target process id */
		int	targpgid;	/* target pgrp id */
E 50
I 50
		int	pid;	/* target process id */
		int	pgid;	/* target pgrp id */
E 50
E 49
E 30
D 40
	} *uap = (struct a *)u.u_ap;
E 40
I 40
	} *uap;
E 54
I 54
D 68
	register struct setpgid_args *uap;
E 54
	int *retval;
E 68
I 68
	register struct setpgid_args /* {
		syscallarg(int) pid;
		syscallarg(int) pgid;
	} */ *uap;
	register_t *retval;
E 68
{
E 40
I 30
D 49
	register struct proc *p;
	register struct pgrp *pgrp;
E 49
I 49
	register struct proc *targp;		/* target process */
D 50
	register struct pgrp *targpgrp;		/* target pgrp */
E 50
I 50
	register struct pgrp *pgrp;		/* target pgrp */
E 50
E 49
E 30

D 40
	if (uap->pid == 0)
D 30
		uap->pid = u.u_procp->p_pid;
	p = pfind(uap->pid);
	if (p == 0) {
E 30
I 30
		p = u.u_procp;
	else if ((p = pfind(uap->pid)) == 0 || !inferior(p)) {
E 30
		u.u_error = ESRCH;
		return;
	}
I 4
D 30
/* need better control mechanisms for process groups */
E 4
	if (p->p_uid != u.u_uid && u.u_uid && !inferior(p)) {
E 30
I 30
	else if (p != u.u_procp) { 
		if (p->p_session != u.u_procp->p_session) {
			u.u_error = EPERM;
			return;
		}
		if (p->p_flag&SEXEC) {
			u.u_error = EACCES;
			return;
		}
	}
	if (SESS_LEADER(p)) {
E 30
		u.u_error = EPERM;
		return;
	}
E 40
I 40
D 49
	if (uap->pid != 0) {
		if ((p = pfind(uap->pid)) == 0 || !inferior(p))
E 49
I 49
D 50
	if (uap->targpid && uap->targpid != curp->p_pid) {
		if ((targp = pfind(uap->targpid)) == 0 || !inferior(targp))
E 50
I 50
D 68
	if (uap->pid != 0 && uap->pid != curp->p_pid) {
		if ((targp = pfind(uap->pid)) == 0 || !inferior(targp))
E 68
I 68
	if (SCARG(uap, pid) != 0 && SCARG(uap, pid) != curp->p_pid) {
		if ((targp = pfind(SCARG(uap, pid))) == 0 || !inferior(targp))
E 68
E 50
E 49
D 41
			RETURN (ESRCH);
E 41
I 41
			return (ESRCH);
E 41
D 49
		if (p->p_session != cp->p_session)
E 49
I 49
		if (targp->p_session != curp->p_session)
E 49
D 41
			RETURN (EPERM);
E 41
I 41
			return (EPERM);
E 41
D 49
		if (p->p_flag&SEXEC)
E 49
I 49
D 61
		if (targp->p_flag&SEXEC)
E 61
I 61
		if (targp->p_flag & P_EXEC)
E 61
E 49
D 41
			RETURN (EACCES);
E 41
I 41
			return (EACCES);
E 41
	} else
D 49
		p = cp;
	if (SESS_LEADER(p))
E 49
I 49
		targp = curp;
	if (SESS_LEADER(targp))
E 49
D 41
		RETURN (EPERM);
E 41
I 41
		return (EPERM);
E 41
E 40
D 30
	p->p_pgrp = uap->pgrp;
E 30
I 30
D 49
	if (uap->pgid == 0)
		uap->pgid = p->p_pid;
D 46
	else if ((uap->pgid != p->p_pid) &&
		(((pgrp = pgfind(uap->pgid)) == 0) || 
		   pgrp->pg_mem == NULL ||
D 40
	           pgrp->pg_session != u.u_procp->p_session)) {
		u.u_error = EPERM;
		return;
	}
E 40
I 40
	           pgrp->pg_session != u.u_procp->p_session))
D 41
		RETURN (EPERM);
E 41
I 41
		return (EPERM);
E 41
E 40
	/*
D 40
	 * done checking, now doit
E 40
I 40
	 * done checking, now do it
E 40
	 */
E 46
I 46
	else if (uap->pgid != p->p_pid)
		if ((pgrp = pgfind(uap->pgid)) == 0 ||
		    pgrp->pg_mem == NULL ||
	            pgrp->pg_session != cp->p_session)
E 49
I 49
D 50
	if (uap->targpgid == 0)
		uap->targpgid = curp->p_pid;
	else if (uap->targpgid != curp->p_pid)
		if ((targpgrp = pgfind(uap->targpgid)) == 0 ||
		    targpgrp->pg_mem == NULL ||
	            targpgrp->pg_session != curp->p_session)
E 50
I 50
D 68
	if (uap->pgid == 0)
		uap->pgid = targp->p_pid;
	else if (uap->pgid != targp->p_pid)
		if ((pgrp = pgfind(uap->pgid)) == 0 ||
E 68
I 68
	if (SCARG(uap, pgid) == 0)
		SCARG(uap, pgid) = targp->p_pid;
	else if (SCARG(uap, pgid) != targp->p_pid)
		if ((pgrp = pgfind(SCARG(uap, pgid))) == 0 ||
E 68
	            pgrp->pg_session != curp->p_session)
E 50
E 49
			return (EPERM);
E 46
D 48
	pgmv(p, uap->pgid, 0);
E 48
I 48
D 49
	enterpgrp(p, uap->pgid, 0);
E 49
I 49
D 50
	enterpgrp(targp, uap->targpgid, 0);
E 50
I 50
D 59
	enterpgrp(targp, uap->pgid, 0);
E 50
E 49
E 48
I 40
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 59
I 59
D 68
	return (enterpgrp(targp, uap->pgid, 0));
E 68
I 68
	return (enterpgrp(targp, SCARG(uap, pgid), 0));
E 68
E 59
E 41
E 40
E 30
}

I 54
D 68
struct setuid_args {
D 55
	int	uid;
E 55
I 55
	uid_t	uid;
E 55
};
E 68
E 54
E 3
D 11
setuid()
E 11
I 11
D 40
setreuid()
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
setuid(p, uap, retval)
D 48
	register struct proc *p;
E 48
I 48
	struct proc *p;
E 48
D 54
	struct args {
		int	uid;
	} *uap;
E 54
I 54
D 68
	struct setuid_args *uap;
E 54
	int *retval;
E 68
I 68
	struct setuid_args /* {
		syscallarg(uid_t) uid;
	} */ *uap;
	register_t *retval;
E 68
E 40
E 11
{
I 48
	register struct pcred *pc = p->p_cred;
E 48
I 11
D 40
	struct a {
E 40
I 40
	register uid_t uid;
	int error;

D 68
	uid = uap->uid;
E 68
I 68
	uid = SCARG(uap, uid);
E 68
D 48
	if (uid != p->p_ruid && (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	if (uid != pc->p_ruid &&
	    (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
	/*
D 46
	 * Everything's okay, do it.
	 * Copy credentials so other references do not
	 * see our changes.
E 46
I 46
D 57
	 * Everything's okay, do it.  Copy credentials so other references do
	 * not see our changes.
E 57
I 57
	 * Everything's okay, do it.
	 * Transfer proc count to new user.
	 * Copy credentials so other references do not see our changes.
E 57
E 46
	 */
I 57
	(void)chgproccnt(pc->p_ruid, -1);
	(void)chgproccnt(uid, 1);
E 57
D 46
	if (u.u_cred->cr_ref > 1)
		u.u_cred = crcopy(u.u_cred);
E 46
I 46
D 48
	u.u_cred = crcopy(u.u_cred);
E 46
	u.u_cred->cr_uid = uid;
	p->p_uid = uid;
	p->p_ruid = uid;
	p->p_svuid = uid;
E 48
I 48
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_uid = uid;
	pc->p_ruid = uid;
	pc->p_svuid = uid;
I 52
D 61
	p->p_flag |= SUGID;
E 61
I 61
	p->p_flag |= P_SUGID;
E 61
E 52
E 48
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
}

I 54
D 68
struct seteuid_args {
D 55
	int	euid;
E 55
I 55
	uid_t	euid;
E 55
};
E 68
E 54
/* ARGSUSED */
I 68
int
E 68
seteuid(p, uap, retval)
D 48
	register struct proc *p;
E 48
I 48
	struct proc *p;
E 48
D 54
	struct args {
		int	euid;
	} *uap;
E 54
I 54
D 68
	struct seteuid_args *uap;
E 54
	int *retval;
E 68
I 68
	struct seteuid_args /* {
		syscallarg(uid_t) euid;
	} */ *uap;
	register_t *retval;
E 68
{
I 48
	register struct pcred *pc = p->p_cred;
E 48
	register uid_t euid;
	int error;

D 68
	euid = uap->euid;
E 68
I 68
	euid = SCARG(uap, euid);
E 68
D 48
	if (euid != p->p_ruid && euid != p->p_svuid &&
	    (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	if (euid != pc->p_ruid && euid != pc->p_svuid &&
	    (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
	/*
D 46
	 * Everything's okay, do it.
	 * Copy credentials so other references do not
	 * see our changes.
E 46
I 46
	 * Everything's okay, do it.  Copy credentials so other references do
	 * not see our changes.
E 46
	 */
D 46
	if (u.u_cred->cr_ref > 1)
		u.u_cred = crcopy(u.u_cred);
E 46
I 46
D 48
	u.u_cred = crcopy(u.u_cred);
E 46
	u.u_cred->cr_uid = euid;
	p->p_uid = euid;
E 48
I 48
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_uid = euid;
I 52
D 61
	p->p_flag |= SUGID;
E 61
I 61
	p->p_flag |= P_SUGID;
E 61
E 52
E 48
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
}

I 54
D 68
struct setgid_args {
D 55
	int	gid;
E 55
I 55
	gid_t	gid;
E 55
};
E 68
E 54
/* ARGSUSED */
I 68
int
E 68
setgid(p, uap, retval)
	struct proc *p;
D 54
	struct args {
		int	gid;
	} *uap;
E 54
I 54
D 68
	struct setgid_args *uap;
E 54
	int *retval;
E 68
I 68
	struct setgid_args /* {
		syscallarg(gid_t) gid;
	} */ *uap;
	register_t *retval;
E 68
{
I 48
	register struct pcred *pc = p->p_cred;
E 48
	register gid_t gid;
	int error;

D 68
	gid = uap->gid;
E 68
I 68
	gid = SCARG(uap, gid);
E 68
D 48
	if (gid != p->p_rgid && (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	if (gid != pc->p_rgid && (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
D 46
	if (u.u_cred->cr_ref > 1)
		u.u_cred = crcopy(u.u_cred);
E 46
I 46
D 48
	u.u_cred = crcopy(u.u_cred);
E 46
	p->p_rgid = gid;
	u.u_cred->cr_groups[0] = gid;
	p->p_svgid = gid;		/* ??? */
E 48
I 48
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_groups[0] = gid;
	pc->p_rgid = gid;
	pc->p_svgid = gid;		/* ??? */
I 52
D 61
	p->p_flag |= SUGID;
E 61
I 61
	p->p_flag |= P_SUGID;
E 61
E 52
E 48
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
}

I 54
D 68
struct setegid_args {
D 55
	int	egid;
E 55
I 55
	gid_t	egid;
E 55
};
E 68
E 54
/* ARGSUSED */
I 68
int
E 68
setegid(p, uap, retval)
	struct proc *p;
D 54
	struct args {
		int	egid;
	} *uap;
E 54
I 54
D 68
	struct setegid_args *uap;
E 54
	int *retval;
E 68
I 68
	struct setegid_args /* {
		syscallarg(gid_t) egid;
	} */ *uap;
	register_t *retval;
E 68
{
I 48
	register struct pcred *pc = p->p_cred;
E 48
	register gid_t egid;
	int error;

D 68
	egid = uap->egid;
E 68
I 68
	egid = SCARG(uap, egid);
E 68
D 48
	if (egid != p->p_rgid && egid != p->p_svgid &&
	    (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	if (egid != pc->p_rgid && egid != pc->p_svgid &&
	    (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
D 46
	if (u.u_cred->cr_ref > 1)
		u.u_cred = crcopy(u.u_cred);
E 46
I 46
D 48
	u.u_cred = crcopy(u.u_cred);
E 46
	u.u_cred->cr_groups[0] = egid;
E 48
I 48
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_groups[0] = egid;
I 52
D 61
	p->p_flag |= SUGID;
E 61
I 61
	p->p_flag |= P_SUGID;
E 61
E 52
E 48
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
}

I 54
D 68
struct setgroups_args {
	u_int	gidsetsize;
D 55
	int	*gidset;
E 55
I 55
	gid_t	*gidset;
E 55
};
E 68
E 54
D 51
#ifdef COMPAT_43
E 51
I 51
D 53
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 51
/* ARGSUSED */
osetreuid(p, uap, retval)
	register struct proc *p;
	struct args {
E 40
		int	ruid;
		int	euid;
	} *uap;
I 37
D 40
	register struct proc *p = u.u_procp;
E 37
	register int ruid, euid;
E 40
I 40
	int *retval;
{
I 48
	register struct pcred *pc = p->p_cred;
E 48
	register uid_t ruid, euid;
	int error;
E 40

D 40
	uap = (struct a *)u.u_ap;
	ruid = uap->ruid;
	if (ruid == -1)
E 40
I 40
	if (uap->ruid == -1)
E 40
D 37
		ruid = u.u_ruid;
D 33
D 34
	if (u.u_ruid != ruid && u.u_uid != ruid && !suser())
E 34
I 34
	if (u.u_ruid != ruid && u.u_uid != ruid &&
E 37
I 37
D 48
		ruid = p->p_ruid;
E 48
I 48
		ruid = pc->p_ruid;
E 48
D 40
#ifdef COMPAT_43
E 40
I 40
	else
		ruid = uap->ruid;
	/*
D 46
	 * Allow setting real uid to previous effective,
	 * for swapping real and effective.
	 * This should be:
	 *   if (ruid != p->p_ruid && (error = suser(u.u_cred, &u.u_acflag)))
E 46
I 46
	 * Allow setting real uid to previous effective, for swapping real and
	 * effective.  This should be:
	 *
D 48
	 * if (ruid != p->p_ruid && (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	 * if (ruid != pc->p_ruid &&
	 *     (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
E 46
	 */
E 40
D 46
	if (ruid != p->p_ruid && ruid != u.u_cred->cr_uid /* XXX */ && 
E 46
I 46
D 48
	if (ruid != p->p_ruid && ruid != u.u_cred->cr_uid /* XXX */ &&
E 46
E 37
D 40
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
I 37
#else
	if (ruid != p->p_ruid && (u.u_error = suser(u.u_cred, &u.u_acflag)))
#endif
E 37
E 34
E 33
I 33
D 35
	if (u.u_ruid != ruid && u.u_uid != ruid &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 35
E 33
		return;
	euid = uap->euid;
	if (euid == -1)
E 40
I 40
	    (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	if (ruid != pc->p_ruid && ruid != pc->pc_ucred->cr_uid /* XXX */ &&
	    (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
	if (uap->euid == -1)
E 40
D 37
		euid = u.u_uid;
D 33
D 34
	if (u.u_ruid != euid && u.u_uid != euid && !suser())
E 34
I 34
	if (u.u_ruid != euid && u.u_uid != euid &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 37
I 37
D 48
		euid = u.u_cred->cr_uid;
E 48
I 48
		euid = pc->pc_ucred->cr_uid;
E 48
I 40
	else
		euid = uap->euid;
E 40
D 48
	if (euid != u.u_cred->cr_uid && euid != p->p_ruid &&
D 40
	    euid != p->p_svuid && (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 37
E 34
E 33
I 33
D 35
	if (u.u_ruid != euid && u.u_uid != euid &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 35
E 33
		return;
E 40
I 40
	    euid != p->p_svuid && (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	if (euid != pc->pc_ucred->cr_uid && euid != pc->p_ruid &&
	    euid != pc->p_svuid && (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
E 40
	/*
D 46
	 * Everything's okay, do it.
I 34
	 * Copy credentials so other references do not
	 * see our changes.
E 46
I 46
	 * Everything's okay, do it.  Copy credentials so other references do
	 * not see our changes.
E 46
E 34
	 */
D 12
	if (ruid != u.u_ruid) {
E 12
D 38
#ifdef QUOTA
D 12
		if (u.u_quota->q_uid != ruid) {
			qclean();
			qstart(getquota(ruid, 0, 0));
		}
#endif
		u.u_procp->p_uid = ruid;
		u.u_ruid = ruid;
E 12
I 12
	if (u.u_quota->q_uid != ruid) {
		qclean();
D 27
		qstart(getquota(ruid, 0, 0));
E 27
I 27
		qstart(getquota((uid_t)ruid, 0, 0));
E 27
E 12
	}
I 12
#endif
E 38
I 34
D 46
	if (u.u_cred->cr_ref > 1)
		u.u_cred = crcopy(u.u_cred);
E 46
I 46
D 48
	u.u_cred = crcopy(u.u_cred);
E 46
E 34
D 25
	u.u_procp->p_uid = ruid;
E 25
I 25
D 37
	u.u_procp->p_uid = euid;
E 25
	u.u_ruid = ruid;
E 12
	u.u_uid = euid;
E 37
I 37
	u.u_cred->cr_uid = euid;
	p->p_uid = euid;
	p->p_ruid = ruid;
E 48
I 48
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_uid = euid;
	pc->p_ruid = ruid;
I 52
	p->p_flag |= SUGID;
E 52
E 48
I 40
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
E 40
E 37
}

D 19
#ifndef NOCOMPAT
osetuid()
{
E 11
	register uid;
	register struct a {
		int	uid;
	} *uap;

	uap = (struct a *)u.u_ap;
	uid = uap->uid;
	if (u.u_ruid == uid || u.u_uid == uid || suser()) {
I 2
#ifdef QUOTA
		if (u.u_quota->q_uid != uid) {
			qclean();
			qstart(getquota(uid, 0, 0));
		}
#endif
E 2
		u.u_uid = uid;
		u.u_procp->p_uid = uid;
		u.u_ruid = uid;
	}
}
I 11
#endif
E 11

E 19
D 3
getgid()
{

	u.u_r.r_val1 = u.u_rgid;
	u.u_r.r_val2 = u.u_gid;
}

E 3
D 11
setgid()
E 11
I 11
D 40
setregid()
{
	register struct a {
E 40
I 40
/* ARGSUSED */
osetregid(p, uap, retval)
D 48
	struct proc *p;
E 48
I 48
	register struct proc *p;
E 48
	struct args {
E 40
		int	rgid;
		int	egid;
	} *uap;
D 40
	register int rgid, egid;
I 37
	register struct proc *p = u.u_procp;
E 40
I 40
	int *retval;
{
I 48
	register struct pcred *pc = p->p_cred;
E 48
	register gid_t rgid, egid;
	int error;
E 40
E 37

D 40
	uap = (struct a *)u.u_ap;
	rgid = uap->rgid;
	if (rgid == -1)
E 40
I 40
	if (uap->rgid == -1)
E 40
D 37
		rgid = u.u_rgid;
D 33
D 34
	if (u.u_rgid != rgid && u.u_gid != rgid && !suser())
E 34
I 34
	if (u.u_rgid != rgid && u.u_gid != rgid &&
E 37
I 37
D 48
		rgid = p->p_rgid;
E 48
I 48
		rgid = pc->p_rgid;
E 48
D 40
#ifdef COMPAT_43_XXX
E 40
I 40
	else
		rgid = uap->rgid;
	/*
D 46
	 * Allow setting real gid to previous effective,
	 * for swapping real and effective.  This didn't really work
	 * correctly in 4.[23], but is preserved so old stuff doesn't fail.
	 * This should be:
	 *  if (rgid != p->p_rgid && (error = suser(u.u_cred, &u.u_acflag)))
E 46
I 46
	 * Allow setting real gid to previous effective, for swapping real and
	 * effective.  This didn't really work correctly in 4.[23], but is
	 * preserved so old stuff doesn't fail.  This should be:
	 *
D 48
	 * if (rgid != p->p_rgid && (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	 * if (rgid != pc->p_rgid &&
	 *     (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
E 46
	 */
E 40
D 48
	if (rgid != p->p_rgid && rgid != u.u_cred->cr_groups[0] /* XXX */ &&
E 37
D 40
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
I 37
#else
	if (rgid != p->p_rgid && (u.u_error = suser(u.u_cred, &u.u_acflag)))
#endif
E 37
E 34
E 33
I 33
D 35
	if (u.u_rgid != rgid && u.u_gid != rgid &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 35
E 33
		return;
	egid = uap->egid;
	if (egid == -1)
E 40
I 40
	    (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	if (rgid != pc->p_rgid && rgid != pc->pc_ucred->cr_groups[0] /* XXX */ &&
	    (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
	if (uap->egid == -1)
E 40
D 37
		egid = u.u_gid;
D 33
D 34
	if (u.u_rgid != egid && u.u_gid != egid && !suser())
E 34
I 34
	if (u.u_rgid != egid && u.u_gid != egid &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 37
I 37
D 48
		egid = u.u_cred->cr_groups[0];
E 48
I 48
		egid = pc->pc_ucred->cr_groups[0];
E 48
I 40
	else
		egid = uap->egid;
E 40
D 46
	if (egid != u.u_cred->cr_groups[0] && egid != p->p_rgid && 
E 46
I 46
D 48
	if (egid != u.u_cred->cr_groups[0] && egid != p->p_rgid &&
E 46
D 40
	    egid != p->p_svgid && (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 37
E 34
E 33
I 33
D 35
	if (u.u_rgid != egid && u.u_gid != egid &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 35
E 33
		return;
E 40
I 40
	    egid != p->p_svgid && (error = suser(u.u_cred, &u.u_acflag)))
E 48
I 48
	if (egid != pc->pc_ucred->cr_groups[0] && egid != pc->p_rgid &&
	    egid != pc->p_svgid && (error = suser(pc->pc_ucred, &p->p_acflag)))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
E 40
D 34
	if (u.u_rgid != rgid) {
		leavegroup(u.u_rgid);
D 17
		(void) entergroup(u.u_rgid);
E 17
I 17
D 26
		(void) entergroup(rgid);
E 26
I 26
		(void) entergroup((gid_t)rgid);
E 26
E 17
		u.u_rgid = rgid;
	}
E 34
I 34
D 46
	if (u.u_cred->cr_ref > 1)
		u.u_cred = crcopy(u.u_cred);
E 46
I 46
D 48
	u.u_cred = crcopy(u.u_cred);
E 46
D 37
	u.u_rgid = rgid;
E 34
D 17
	if (u.u_gid != egid) {
		leavegroup(u.u_gid);
		(void) entergroup(egid);
		u.u_gid = egid;
	}
E 17
I 17
	u.u_gid = egid;
E 37
I 37
	p->p_rgid = rgid;
	u.u_cred->cr_groups[0] = egid;
E 48
I 48
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_groups[0] = egid;
	pc->p_rgid = rgid;
I 52
	p->p_flag |= SUGID;
E 52
E 48
I 40
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
E 40
E 37
E 17
}
I 40
D 51
#endif
E 51
I 51
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 51
E 40

E 53
D 19
#ifndef NOCOMPAT
osetgid()
E 11
{
	register gid;
	register struct a {
		int	gid;
	} *uap;

	uap = (struct a *)u.u_ap;
	gid = uap->gid;
	if (u.u_rgid == gid || u.u_gid == gid || suser()) {
I 4
D 17
		leavegroup(u.u_gid); leavegroup(u.u_rgid);
E 17
I 17
		leavegroup(u.u_rgid);
E 17
		(void) entergroup(gid);
E 4
		u.u_gid = gid;
		u.u_rgid = gid;
	}
}
I 3

E 19
D 4
setgrp()
E 4
I 4
D 40
setgroups()
E 4
{
	register struct	a {
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
setgroups(p, uap, retval)
	struct proc *p;
D 54
	struct args {
E 40
I 4
D 9
		int	gidsetsize;
E 9
I 9
		u_int	gidsetsize;
E 9
E 4
		int	*gidset;
D 40
	} *uap = (struct a *)u.u_ap;
E 40
I 40
	} *uap;
E 54
I 54
D 68
	struct setgroups_args *uap;
E 54
	int *retval;
E 68
I 68
	struct setgroups_args /* {
		syscallarg(u_int) gidsetsize;
		syscallarg(gid_t *) gidset;
	} */ *uap;
	register_t *retval;
E 68
{
I 48
	register struct pcred *pc = p->p_cred;
E 48
E 40
I 4
D 22
	register int *gp;
E 22
I 22
D 55
	register gid_t *gp;
E 55
I 43
D 44
	register u_int ngrps;
E 44
I 44
	register u_int ngrp;
E 44
E 43
D 55
	register int *lp;
D 34
	int groups[NGROUPS];
E 34
I 34
D 40
	int ngrp, groups[NGROUPS];
E 40
I 40
D 43
	int error, ngrp, groups[NGROUPS];
E 43
I 43
	int error, groups[NGROUPS];
E 55
I 55
	int error;
E 55
E 43
E 40
E 34
E 22
E 4

D 6
	if (suser())
E 6
I 6
D 7
printf("gidsetsize %d, gidset %x\n", uap->gidsetsize, uap->gidset);
E 7
D 33
D 34
	if (!suser())
E 34
I 34
D 35
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 35
E 34
E 33
I 33
D 40
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 33
E 6
		return;
E 40
I 40
D 48
	if (error = suser(u.u_cred, &u.u_acflag))
E 48
I 48
	if (error = suser(pc->pc_ucred, &p->p_acflag))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
E 40
D 4
	if (copyin((caddr_t)uap->gidset, (caddr_t)u.u_grps,
	    sizeof (u.u_grps))) {
		u.u_error = EFAULT;
E 4
I 4
D 34
	if (uap->gidsetsize > sizeof (u.u_groups) / sizeof (u.u_groups[0])) {
E 34
I 34
D 37
	ngrp = uap->gidsetsize + GRPSTART;
	if (ngrp > sizeof (u.u_groups) / sizeof (u.u_groups[0])) {
E 37
I 37
D 43
	ngrp = uap->gidsetsize;
D 40
	if (ngrp > NGROUPS) {
E 37
E 34
		u.u_error = EINVAL;
E 4
		return;
	}
D 4
}

/* BEGIN DEFUNCT */
osetgrp()
{
	register struct	a {
		int *ngrps;
		int *ogrps;
	} *uap = (struct a *)u.u_ap;
	int thegroups[NGRPS/(sizeof(int)*8)];

	if (uap->ogrps && copyout((caddr_t)u.u_grps, (caddr_t)uap->ogrps,
	    sizeof (thegroups))) {
E 4
I 4
D 14
	if (copyin((caddr_t)uap->gidset, (caddr_t)u.u_groups,
	    uap->gidsetsize * sizeof (u.u_groups[0]))) {
E 4
		u.u_error = EFAULT;
E 14
I 14
D 22
	u.u_error = copyin((caddr_t)uap->gidset, (caddr_t)u.u_groups,
	    uap->gidsetsize * sizeof (u.u_groups[0]));
E 22
I 22
	u.u_error = copyin((caddr_t)uap->gidset, (caddr_t)groups,
E 40
I 40
	if (ngrp > NGROUPS)
E 43
I 43
D 44
	if ((ngrps = uap->gidsetsize) > NGROUPS)
E 44
I 44
D 68
	if ((ngrp = uap->gidsetsize) > NGROUPS)
E 68
I 68
	ngrp = SCARG(uap, gidsetsize);
	if (ngrp < 1 || ngrp > NGROUPS)
E 68
E 44
E 43
D 41
		RETURN (EINVAL);
E 41
I 41
		return (EINVAL);
E 41
D 43
	error = copyin((caddr_t)uap->gidset, (caddr_t)groups,
E 40
	    uap->gidsetsize * sizeof (groups[0]));
E 22
D 40
	if (u.u_error)
E 14
		return;
E 40
I 40
	if (error)
E 43
I 43
D 55
	if (error = copyin((caddr_t)uap->gidset, (caddr_t)groups,
D 44
	    ngrps * sizeof (groups[0])))
E 44
I 44
	    ngrp * sizeof (groups[0])))
E 44
E 43
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 55
I 46
D 48
	u.u_cred = crcopy(u.u_cred);
E 46
E 41
E 40
D 14
	}
E 14
I 6
D 7
printf("copied in %d %d ... \n", u.u_groups[0], u.u_groups[1]);
E 7
E 6
D 4
	if (uap->ngrps == 0)
		return;
	if (copyin((caddr_t)uap->ngrps, (caddr_t)thegroups,
	    sizeof (thegroups))) {
		u.u_error = EFAULT;
		return;
	}
	if (suser())
		bcopy((caddr_t)thegroups, (caddr_t)u.u_grps, sizeof (u.u_grps));
E 4
I 4
D 22
	for (gp = &u.u_groups[uap->gidsetsize]; gp < &u.u_groups[NGROUPS]; gp++)
E 22
I 22
D 34
	for (lp = groups, gp = u.u_groups; lp < &groups[uap->gidsetsize]; )
E 34
I 34
D 37
	gp = &u.u_groups[GRPSTART];
E 37
I 37
D 43
	gp = u.u_cred->cr_groups;
E 37
	for (lp = groups; lp < &groups[uap->gidsetsize]; )
E 34
		*gp++ = *lp++;
D 34
	for ( ; gp < &u.u_groups[NGROUPS]; gp++)
E 22
D 18
		*gp = -1;
E 18
I 18
		*gp = NOGROUP;
E 34
I 34
D 37
	u.u_ngroups = ngrp;
E 37
I 37
	u.u_cred->cr_ngroups = ngrp;
E 43
I 43
D 44
	u.u_cred->cr_ngroups = ngrps;
E 44
I 44
	u.u_cred->cr_ngroups = ngrp;
E 48
I 48
	pc->pc_ucred = crcopy(pc->pc_ucred);
I 55
D 68
	if (error = copyin((caddr_t)uap->gidset,
E 68
I 68
	if (error = copyin((caddr_t)SCARG(uap, gidset),
E 68
	    (caddr_t)pc->pc_ucred->cr_groups, ngrp * sizeof(gid_t)))
		return (error);
E 55
	pc->pc_ucred->cr_ngroups = ngrp;
E 48
E 44
D 55
	/* convert from int's to gid_t's */
D 44
	for (gp = u.u_cred->cr_groups, lp = groups; ngrps--; *gp++ = *lp++)
		/* void */;
E 44
I 44
D 48
	for (gp = u.u_cred->cr_groups, lp = groups; ngrp--; )
E 48
I 48
	for (gp = pc->pc_ucred->cr_groups, lp = groups; ngrp--; )
E 48
		*gp++ = *lp++;
E 55
I 52
D 61
	p->p_flag |= SUGID;
E 61
I 61
	p->p_flag |= P_SUGID;
E 61
E 52
E 44
E 43
I 40
D 41
	RETURN (0);
E 41
I 41
	return (0);
E 41
E 40
E 37
E 34
E 18
E 4
}
D 19

/*
 * Pid of zero implies current process.
 * Pgrp -1 is getpgrp system call returning
 * current process group.
 */
osetpgrp()
{
	register struct proc *p;
	register struct a {
		int	pid;
		int	pgrp;
	} *uap;

	uap = (struct a *)u.u_ap;
	if (uap->pid == 0)
		p = u.u_procp;
	else {
		p = pfind(uap->pid);
		if (p == 0) {
			u.u_error = ESRCH;
			return;
		}
	}
	if (uap->pgrp <= 0) {
		u.u_r.r_val1 = p->p_pgrp;
		return;
	}
	if (p->p_uid != u.u_uid && u.u_uid && !inferior(p)) {
		u.u_error = EPERM;
		return;
	}
	p->p_pgrp = uap->pgrp;
}
/* END DEFUNCT */
E 19
I 4

I 56
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
D 68
struct setreuid_args {
	int	ruid;
	int	euid;
};
E 68
/* ARGSUSED */
D 68
osetreuid(p, uap, retval)
E 68
I 68
int
compat_43_setreuid(p, uap, retval)
E 68
	register struct proc *p;
D 68
	struct setreuid_args *uap;
	int *retval;
E 68
I 68
	struct compat_43_setreuid_args /* {
		syscallarg(int) ruid;
		syscallarg(int) euid;
	} */ *uap;
	register_t *retval;
E 68
{
	register struct pcred *pc = p->p_cred;
D 66
	struct seteuid_args args;
E 66
I 66
	union {
		struct setuid_args sa;
		struct seteuid_args ea;
	} args;
E 66

	/*
D 66
	 * we assume that the intent of setting ruid is to be able to get
	 * back ruid priviledge. So we make sure that we will be able to
	 * do so, but do not actually set the ruid.
E 66
I 66
	 * If ruid == euid then setreuid is being used to emulate setuid,
	 * just do it.
E 66
	 */
I 66
D 68
	if (uap->ruid != -1 && uap->ruid == uap->euid) {
		args.sa.uid = uap->ruid;
E 68
I 68
	if (SCARG(uap, ruid) != -1 && SCARG(uap, ruid) == SCARG(uap, euid)) {
		SCARG(&args.sa, uid) = SCARG(uap, ruid);
E 68
		return (setuid(p, &args.sa, retval));
	}
	/*
	 * Otherwise we assume that the intent of setting ruid is to be
	 * able to get back ruid priviledge (i.e. swapping ruid and euid).
	 * So we make sure that we will be able to do so, but do not
	 * actually set the ruid.
	 */
E 66
D 62
	if (uap->ruid != -1 && uap->ruid != pc->p_ruid &&
E 62
I 62
D 68
	if (uap->ruid != (uid_t)-1 && uap->ruid != pc->p_ruid &&
E 62
	    uap->ruid != pc->p_svuid)
E 68
I 68
	if (SCARG(uap, ruid) != (uid_t)-1 && SCARG(uap, ruid) != pc->p_ruid &&
	    SCARG(uap, ruid) != pc->p_svuid)
E 68
		return (EPERM);
D 62
	if (uap->euid == -1)
E 62
I 62
D 68
	if (uap->euid == (uid_t)-1)
E 68
I 68
	if (SCARG(uap, euid) == (uid_t)-1)
E 68
E 62
		return (0);
D 66
	args.euid = uap->euid;
	return (seteuid(p, &args, retval));
E 66
I 66
D 68
	args.ea.euid = uap->euid;
E 68
I 68
	SCARG(&args.ea, euid) = SCARG(uap, euid);
E 68
	return (seteuid(p, &args.ea, retval));
E 66
}

D 68
struct setregid_args {
	int	rgid;
	int	egid;
};
E 68
/* ARGSUSED */
D 68
osetregid(p, uap, retval)
E 68
I 68
int
compat_43_setregid(p, uap, retval)
E 68
	register struct proc *p;
D 68
	struct setregid_args *uap;
	int *retval;
E 68
I 68
	struct compat_43_setregid_args /* {
		syscallarg(int) rgid;
		syscallarg(int) egid;
	} */ *uap;
	register_t *retval;
E 68
{
	register struct pcred *pc = p->p_cred;
D 66
	struct setegid_args args;
E 66
I 66
	union {
		struct setgid_args sa;
		struct setegid_args ea;
	} args;
E 66

	/*
D 66
	 * we assume that the intent of setting rgid is to be able to get
	 * back rgid priviledge. So we make sure that we will be able to
	 * do so, but do not actually set the rgid.
E 66
I 66
	 * If rgid == egid then setreuid is being used to emulate setgid,
	 * just do it.
E 66
	 */
I 66
D 68
	if (uap->rgid != -1 && uap->rgid == uap->egid) {
		args.sa.gid = uap->rgid;
E 68
I 68
	if (SCARG(uap, rgid) != -1 && SCARG(uap, rgid) == SCARG(uap, egid)) {
		SCARG(&args.sa, gid) = SCARG(uap, rgid);
E 68
		return (setgid(p, &args.sa, retval));
	}
	/*
	 * Otherwise we assume that the intent of setting rgid is to be
	 * able to get back rgid priviledge (i.e. swapping rgid and egid).
	 * So we make sure that we will be able to do so, but do not
	 * actually set the rgid.
	 */
E 66
D 62
	if (uap->rgid != -1 && uap->rgid != pc->p_rgid &&
E 62
I 62
D 68
	if (uap->rgid != (gid_t)-1 && uap->rgid != pc->p_rgid &&
E 62
	    uap->rgid != pc->p_svgid)
E 68
I 68
	if (SCARG(uap, rgid) != (gid_t)-1 && SCARG(uap, rgid) != pc->p_rgid &&
	    SCARG(uap, rgid) != pc->p_svgid)
E 68
		return (EPERM);
D 62
	if (uap->egid == -1)
E 62
I 62
D 68
	if (uap->egid == (gid_t)-1)
E 68
I 68
	if (SCARG(uap, egid) == (gid_t)-1)
E 68
E 62
		return (0);
D 66
	args.egid = uap->egid;
	return (setegid(p, &args, retval));
E 66
I 66
D 68
	args.ea.egid = uap->egid;
E 68
I 68
	SCARG(&args.ea, egid) = SCARG(uap, egid);
E 68
	return (setegid(p, &args.ea, retval));
E 66
}
#endif /* defined(COMPAT_43) || defined(COMPAT_SUNOS) */

E 56
I 18
/*
D 34
 * Group utility functions.
E 34
I 34
 * Check if gid is a member of the group set.
E 34
 */
I 68
int
E 68
D 34

/*
 * Delete gid from the group set.
 */
E 18
leavegroup(gid)
E 34
I 34
groupmember(gid, cred)
E 34
D 26
	int gid;
E 26
I 26
	gid_t gid;
I 34
	register struct ucred *cred;
E 34
E 26
{
D 22
	register int *gp;
E 22
I 22
	register gid_t *gp;
I 34
	gid_t *egp;
E 34
E 22

D 34
	for (gp = u.u_groups; gp < &u.u_groups[NGROUPS]; gp++)
E 34
I 34
	egp = &(cred->cr_groups[cred->cr_ngroups]);
	for (gp = cred->cr_groups; gp < egp; gp++)
E 34
		if (*gp == gid)
D 34
			goto found;
	return;
found:
	for (; gp < &u.u_groups[NGROUPS-1]; gp++)
		*gp = *(gp+1);
D 5
	*gp = 0;
E 5
I 5
D 18
	*gp = -1;
E 18
I 18
	*gp = NOGROUP;
E 34
I 34
			return (1);
	return (0);
E 34
E 18
E 5
}

I 18
/*
D 34
 * Add gid to the group set.
E 34
I 34
D 47
 * Test if the current user is the super user.
E 47
I 47
 * Test whether the specified credentials imply "super-user"
 * privilege; if so, and we have accounting info, set the flag
 * indicating use of super-powers.
 * Returns 0 or error.
E 47
E 34
 */
I 68
int
E 68
E 18
D 34
entergroup(gid)
D 26
	int gid;
E 26
I 26
	gid_t gid;
E 34
I 34
suser(cred, acflag)
	struct ucred *cred;
D 67
	short *acflag;
E 67
I 67
	u_short *acflag;
E 67
E 34
E 26
{
D 22
	register int *gp;
E 22
I 22
D 34
	register gid_t *gp;
E 34
E 22
D 46

E 46
D 22
	for (gp = u.u_groups; gp < &u.u_groups[NGROUPS]; gp++)
E 22
I 22
D 34
	for (gp = u.u_groups; gp < &u.u_groups[NGROUPS]; gp++) {
E 22
		if (*gp == gid)
			return (0);
D 22
	for (gp = u.u_groups; gp < &u.u_groups[NGROUPS]; gp++)
		if (*gp < 0) {
E 22
I 22
		if (*gp == NOGROUP) {
E 22
			*gp = gid;
			return (0);
		}
E 34
I 34
	if (cred->cr_uid == 0) {
		if (acflag)
			*acflag |= ASU;
		return (0);
E 34
I 22
	}
E 22
D 34
	return (-1);
E 34
I 34
	return (EPERM);
E 34
I 18
}

/*
D 34
 * Check if gid is a member of the group set.
E 34
I 34
 * Allocate a zeroed cred structure.
E 34
 */
D 34
groupmember(gid)
D 22
	int gid;
E 22
I 22
	gid_t gid;
E 34
I 34
struct ucred *
crget()
E 34
E 22
{
D 22
	register int *gp;
E 22
I 22
D 34
	register gid_t *gp;
E 34
I 34
	register struct ucred *cr;
E 34
E 22

D 34
	if (u.u_gid == gid)
		return (1);
	for (gp = u.u_groups; gp < &u.u_groups[NGROUPS] && *gp != NOGROUP; gp++)
		if (*gp == gid)
			return (1);
	return (0);
E 34
I 34
	MALLOC(cr, struct ucred *, sizeof(*cr), M_CRED, M_WAITOK);
	bzero((caddr_t)cr, sizeof(*cr));
	cr->cr_ref = 1;
D 40
	return(cr);
E 40
I 40
	return (cr);
E 40
}

/*
 * Free a cred structure.
 * Throws away space when ref count gets to 0.
 */
I 67
void
E 67
crfree(cr)
	struct ucred *cr;
{
D 40
	int	s = splimp();
E 40
I 40
D 48
	int s = splimp();
E 48
I 48
D 63
	int s = splimp();			/* ??? */
E 63
I 63
	int s;
E 63
E 48
E 40

D 63
	if (--cr->cr_ref != 0) {
		(void) splx(s);
		return;
	}
	FREE((caddr_t)cr, M_CRED);
E 63
I 63
	s = splimp();				/* ??? */
	if (--cr->cr_ref == 0)
		FREE((caddr_t)cr, M_CRED);
E 63
	(void) splx(s);
}

/*
 * Copy cred structure to a new one and free the old one.
 */
struct ucred *
crcopy(cr)
	struct ucred *cr;
{
	struct ucred *newcr;

I 46
	if (cr->cr_ref == 1)
		return (cr);
E 46
	newcr = crget();
	*newcr = *cr;
	crfree(cr);
	newcr->cr_ref = 1;
D 40
	return(newcr);
E 40
I 40
	return (newcr);
E 40
}

/*
 * Dup cred struct to a new held one.
 */
struct ucred *
crdup(cr)
	struct ucred *cr;
{
	struct ucred *newcr;

	newcr = crget();
	*newcr = *cr;
	newcr->cr_ref = 1;
D 40
	return(newcr);
E 40
I 40
	return (newcr);
E 40
E 34
E 18
}
I 31

/*
D 37
 * Get login name of process owner, if available
E 37
I 37
 * Get login name, if available.
E 37
 */
I 54
D 68
struct getlogin_args {
	char	*namebuf;
	u_int	namelen;
};
E 68
E 54
D 37

getlogname()
E 37
I 37
D 40
getlogin()
E 37
{
	struct a {
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
getlogin(p, uap, retval)
	struct proc *p;
D 54
	struct args {
E 40
		char	*namebuf;
		u_int	namelen;
D 40
	} *uap = (struct a *)u.u_ap;
E 40
I 40
	} *uap;
E 54
I 54
D 68
	struct getlogin_args *uap;
E 54
	int *retval;
E 68
I 68
	struct getlogin_args /* {
		syscallarg(char *) namebuf;
		syscallarg(u_int) namelen;
	} */ *uap;
	register_t *retval;
E 68
{
E 40

D 37
	if (uap->namelen > sizeof (u.u_logname))
		uap->namelen = sizeof (u.u_logname);
	u.u_error = copyout((caddr_t)u.u_logname, (caddr_t)uap->namebuf,
		uap->namelen);
E 37
I 37
D 40
	if (uap->namelen > sizeof (u.u_procp->p_logname))
		uap->namelen = sizeof (u.u_procp->p_logname);
	u.u_error = copyout((caddr_t)u.u_procp->p_logname, 
			     (caddr_t)uap->namebuf, uap->namelen);
E 40
I 40
D 48
	if (uap->namelen > sizeof (p->p_logname))
		uap->namelen = sizeof (p->p_logname);
D 41
	RETURN (copyout((caddr_t)p->p_logname, (caddr_t)uap->namebuf,
E 41
I 41
	return (copyout((caddr_t)p->p_logname, (caddr_t)uap->namebuf,
E 41
	    uap->namelen));
E 48
I 48
D 68
	if (uap->namelen > sizeof (p->p_pgrp->pg_session->s_login))
		uap->namelen = sizeof (p->p_pgrp->pg_session->s_login);
E 68
I 68
	if (SCARG(uap, namelen) > sizeof (p->p_pgrp->pg_session->s_login))
		SCARG(uap, namelen) = sizeof (p->p_pgrp->pg_session->s_login);
E 68
	return (copyout((caddr_t) p->p_pgrp->pg_session->s_login,
D 68
	    (caddr_t) uap->namebuf, uap->namelen));
E 68
I 68
	    (caddr_t) SCARG(uap, namebuf), SCARG(uap, namelen)));
E 68
E 48
E 40
E 37
}

/*
D 37
 * Set login name of process owner
E 37
I 37
 * Set login name.
E 37
 */
I 54
D 68
struct setlogin_args {
	char	*namebuf;
};
E 68
E 54
D 37

setlogname()
E 37
I 37
D 40
setlogin()
E 37
{
	struct a {
E 40
I 40
/* ARGSUSED */
I 68
int
E 68
setlogin(p, uap, retval)
	struct proc *p;
D 54
	struct args {
E 40
		char	*namebuf;
D 37
		u_int	namelen;
E 37
D 40
	} *uap = (struct a *)u.u_ap;
E 40
I 40
	} *uap;
E 54
I 54
D 68
	struct setlogin_args *uap;
E 54
	int *retval;
E 68
I 68
	struct setlogin_args /* {
		syscallarg(char *) namebuf;
	} */ *uap;
	register_t *retval;
E 68
{
E 40
I 37
	int error;
E 37

D 33
	if(suser()) {
		if(uap->namelen > sizeof (u.u_logname) - 1)
			u.u_error = EINVAL;
		else
			u.u_error = copyin((caddr_t)uap->namebuf,
				(caddr_t)u.u_logname, uap->namelen);
	} 
E 33
I 33
D 40
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
D 37
	if (uap->namelen > sizeof (u.u_logname) - 1)
		u.u_error = EINVAL;
D 36
	else
E 36
I 36
	else {
		u.u_logname[uap->namelen] = NULL;
E 36
		u.u_error = copyin((caddr_t)uap->namebuf,
			(caddr_t)u.u_logname, uap->namelen);
I 36
	}
E 37
I 37
	error = copyinstr((caddr_t)uap->namebuf, (caddr_t)u.u_procp->p_logname,
	    sizeof (u.u_procp->p_logname) - 1, (int *) 0);
E 40
I 40
D 48
	if (error = suser(u.u_cred, &u.u_acflag))
E 48
I 48
	if (error = suser(p->p_ucred, &p->p_acflag))
E 48
D 41
		RETURN (error);
E 41
I 41
		return (error);
E 41
D 48
	error = copyinstr((caddr_t)uap->namebuf, (caddr_t)p->p_logname,
D 46
	    sizeof (p->p_logname) - 1, (int *) 0);
E 46
I 46
	    sizeof (p->p_logname) - 1, (u_int *)0);
E 46
E 40
D 45
	if (error == ENOENT)		/* name too long */
E 45
I 45
	if (error == ENAMETOOLONG)		/* name too long */
E 48
I 48
D 68
	error = copyinstr((caddr_t) uap->namebuf,
E 68
I 68
	error = copyinstr((caddr_t) SCARG(uap, namebuf),
E 68
	    (caddr_t) p->p_pgrp->pg_session->s_login,
	    sizeof (p->p_pgrp->pg_session->s_login) - 1, (u_int *)0);
	if (error == ENAMETOOLONG)
E 48
E 45
		error = EINVAL;
D 40
	u.u_error = error;
E 40
I 40
D 41
	RETURN (error);
E 41
I 41
	return (error);
E 41
E 40
E 37
E 36
E 33
}
E 31
E 4
E 3
E 1
