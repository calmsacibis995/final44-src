h34450
s 00044/00039/00073
d D 8.3 95/02/14 10:31:55 cgd 42 41
c new argument passing conventions.  minor type size cleanup.
e
s 00003/00000/00109
d D 8.2 93/11/14 14:03:43 hibler 41 40
c missing permission check on sethostname
e
s 00002/00002/00107
d D 8.1 93/06/10 21:58:13 bostic 40 39
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00108
d D 7.24 93/04/27 15:13:11 mckusick 39 38
c sysctl.h needs vm/vm.h
e
s 00035/00033/00073
d D 7.23 93/04/05 15:33:41 torek 38 36
c {set,get}hostname and gethostid are needed for COMPAT_SUNOS too.
c (note that sethostid is not---SunOS has no way to alter the host ID)
e
s 00003/00001/00105
d R 7.23 93/04/05 15:18:44 torek 37 36
c SunOS compat needs get/set host name/id too
e
s 00004/00004/00102
d D 7.22 93/04/04 13:15:16 mckusick 36 35
c {get,set}host{name,id} become COMPAT
e
s 00028/00034/00078
d D 7.21 93/02/04 01:11:15 mckusick 35 34
c get/set hostname and hostid are subsumed by sysctl and become COMPAT_43
e
s 00005/00005/00107
d D 7.20 92/10/11 10:38:15 bostic 34 33
c make kernel includes standard
e
s 00024/00017/00088
d D 7.19 92/07/10 21:04:38 torek 33 32
c ANSIfy syscall args
e
s 00004/00000/00101
d D 7.18 92/03/18 18:06:06 sklower 32 31
c define hostname, hostnamelen, and hostid
e
s 00004/00009/00097
d D 7.17 91/04/20 15:33:46 karels 31 30
c rm user.h; rm old syscall stubs that just error; oquota does ENOSYS w/o signal
e
s 00003/00003/00103
d D 7.16 91/03/17 15:41:29 karels 30 29
c more-or-less working with new proc & user structs
e
s 00001/00000/00105
d D 7.15 90/08/24 10:40:56 bostic 29 28
c litn
e
s 00001/00011/00104
d D 7.14 90/06/28 21:22:03 bostic 28 27
c new copyright notice
e
s 00012/00012/00103
d D 7.13 90/06/28 17:11:06 karels 27 26
c RETURN => return, remove syscontext.h
e
s 00034/00019/00081
d D 7.12 90/06/21 21:33:36 karels 26 25
c new syscall convention
e
s 00001/00001/00099
d D 7.11 90/05/15 14:26:07 mckusick 25 24
c get rid of unneeded register declaration
e
s 00006/00000/00094
d D 7.10 90/05/02 19:05:53 mckusick 24 23
c add oldquota call
e
s 00020/00015/00074
d D 7.9 90/05/02 19:05:32 mckusick 23 22
c convert to new syscall convention
e
s 00005/00000/00084
d D 7.8 89/11/20 18:16:29 marc 22 21
c deprecate vhangup
e
s 00000/00001/00084
d D 7.7 89/05/05 00:06:50 mckusick 21 20
c delete unneeded include of dir.h
e
s 00000/00024/00085
d D 7.6 89/05/02 11:15:14 mckusick 20 18
i 19
c integrate back branch -r7.2.1.1
e
s 00038/00013/00343
d D 7.2.1.1 89/05/02 11:10:09 mckusick 19 15
c merge in vnode changes
e
s 00007/00005/00067
d D 7.5 89/04/26 19:41:36 mckusick 18 17
c use new form of suser()
e
s 00004/00005/00068
d D 7.4 89/02/23 14:52:53 marc 17 16
c remove unnecessary register temp
e
s 00000/00283/00073
d D 7.3 88/08/27 15:46:10 karels 16 15
c rm 4.1 compat
e
s 00001/00001/00355
d D 7.2 87/02/26 18:09:59 karels 15 14
c do reboot more flexibly
e
s 00001/00001/00355
d D 7.1 86/06/05 00:05:24 mckusick 14 13
c 4.3BSD release version
e
s 00001/00001/00355
d D 6.7 86/03/04 19:54:53 karels 13 11
c consistency
e
s 00356/00000/00000
d R 6.7 86/03/04 19:25:17 karels 12 11
c consistency
e
s 00004/00003/00352
d D 6.6 86/02/20 20:46:55 karels 11 10
c spls
e
s 00001/00001/00354
d D 6.5 85/11/28 10:34:51 bloom 10 9
c hostid should be a long
e
s 00007/00001/00348
d D 6.4 85/06/08 14:39:19 mckusick 9 8
c Add copyright
e
s 00001/00001/00348
d D 6.3 85/03/12 13:53:29 mckusick 8 7
c add another bit to sigvec() flags to disable system call restart
e
s 00007/00007/00342
d D 6.2 84/08/29 20:20:46 bloom 7 6
c Change to includes.  no more ../h
e
s 00000/00000/00349
d D 6.1 83/07/29 06:34:48 sam 6 5
c 4.2 distribution
e
s 00001/00012/00348
d D 4.5 83/06/21 20:35:53 sam 5 4
c change NOCOMPAT to COMPAT and make it work
e
s 00011/00005/00349
d D 4.4 83/06/09 21:59:48 sam 4 3
c "final" sigvec interface?
e
s 00017/00051/00337
d D 4.3 83/06/02 15:57:11 sam 3 2
c new signals
e
s 00022/00001/00366
d D 4.2 83/05/31 01:03:49 sam 2 1
c collect all the compatibility stuff in single files
e
s 00367/00000/00000
d D 4.1 83/05/27 14:02:49 sam 1 0
c date and time created 83/05/27 14:02:49 by sam
e
u
U
f b 
t
T
I 1
D 9
/*	%M%	%I%	%E%	*/
E 9
I 9
/*
D 14
 * Copyright (c) 1982 Regents of the University of California.
E 14
I 14
D 19
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 19
I 19
D 40
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 40
I 40
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 40
E 19
 *
I 19
D 28
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
E 28
I 28
 * %sccs.include.redist.c%
E 28
 *
E 19
 *	%W% (Berkeley) %G%
 */
E 9

D 7
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/kernel.h"
#include "../h/proc.h"
#include "../h/reboot.h"
E 7
I 7
D 34
#include "param.h"
#include "systm.h"
D 21
#include "dir.h"
E 21
D 23
#include "user.h"
E 23
I 23
D 27
#include "syscontext.h"
E 27
I 27
D 31
#include "user.h"
E 31
E 27
E 23
#include "kernel.h"
#include "proc.h"
#include "reboot.h"
E 34
I 34
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/reboot.h>
I 39
#include <vm/vm.h>
E 39
I 35
#include <sys/sysctl.h>
E 35
E 34
E 7
D 2
#include "../h/quota.h"
E 2

I 32
D 35
char	hostname[MAXHOSTNAMELEN];
int	hostnamelen;
long	hostid;
E 35
I 35
D 42
struct reboot_args {
	int	opt;
};
E 42
I 42
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 42
/* ARGSUSED */
I 42
int
E 42
reboot(p, uap, retval)
	struct proc *p;
D 42
	struct reboot_args *uap;
	int *retval;
E 42
I 42
	struct reboot_args /* {
		syscallarg(int) opt;
	} */ *uap;
	register_t *retval;
E 42
{
	int error;
E 35

I 35
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
D 42
	boot(uap->opt);
E 42
I 42
	boot(SCARG(uap, opt));
E 42
	return (0);
}

D 38
#ifdef COMPAT_43
E 38
I 38
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 38

I 38
D 42
struct gethostname_args {
	char	*hostname;
	u_int	len;
};
E 42
/* ARGSUSED */
D 42
ogethostname(p, uap, retval)
E 42
I 42
int
compat_43_gethostname(p, uap, retval)
E 42
	struct proc *p;
D 42
	struct gethostname_args *uap;
	int *retval;
E 42
I 42
	struct compat_43_gethostname_args /* {
		syscallarg(char *) hostname;
		syscallarg(u_int) len;
	} */ *uap;
	register_t *retval;
E 42
{
	int name;

	name = KERN_HOSTNAME;
D 42
	return (kern_sysctl(&name, 1, uap->hostname, &uap->len, 0, 0));
E 42
I 42
	return (kern_sysctl(&name, 1, SCARG(uap, hostname), &SCARG(uap, len),
	    0, 0));
E 42
}

D 42
struct sethostname_args {
	char	*hostname;
	u_int	len;
};
E 42
/* ARGSUSED */
D 42
osethostname(p, uap, retval)
E 42
I 42
int
compat_43_sethostname(p, uap, retval)
E 42
	struct proc *p;
D 42
	register struct sethostname_args *uap;
	int *retval;
E 42
I 42
	register struct compat_43_sethostname_args /* {
		syscallarg(char *) hostname;
		syscallarg(u_int) len;
	} */ *uap;
	register_t *retval;
E 42
{
	int name;
I 41
	int error;
E 41

I 41
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
E 41
	name = KERN_HOSTNAME;
D 42
	return (kern_sysctl(&name, 1, 0, 0, uap->hostname, uap->len));
E 42
I 42
	return (kern_sysctl(&name, 1, 0, 0, SCARG(uap, hostname),
	    SCARG(uap, len)));
E 42
}

E 38
D 42
extern long hostid;

E 35
I 33
struct gethostid_args {
	int	dummy;
};
E 42
E 33
E 32
D 26
gethostid()
E 26
I 26
/* ARGSUSED */
D 36
gethostid(p, uap, retval)
E 36
I 36
D 42
ogethostid(p, uap, retval)
E 42
I 42
int
compat_43_gethostid(p, uap, retval)
E 42
E 36
	struct proc *p;
D 33
	void *uap;
	long *retval;
E 33
I 33
D 42
	struct gethostid_args *uap;
	int *retval;
E 42
I 42
	void *uap;
	register_t *retval;
E 42
E 33
E 26
{

D 26
	u.u_r.r_val1 = hostid;
E 26
I 26
D 33
	*retval = hostid;
E 33
I 33
D 42
	*(long *)retval = hostid;
E 42
I 42
	*(int32_t *)retval = hostid;
E 42
E 33
E 26
I 23
D 27
	RETURN (0);
E 27
I 27
	return (0);
E 27
E 23
}
I 38
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 38

I 38
#ifdef COMPAT_43
E 38
I 33
D 42
struct sethostid_args {
	long	hostid;
};
E 42
E 33
I 29
/* ARGSUSED */
E 29
D 26
sethostid()
{
	struct a {
E 26
I 26
D 36
sethostid(p, uap, retval)
E 36
I 36
D 42
osethostid(p, uap, retval)
E 42
I 42
int
compat_43_sethostid(p, uap, retval)
E 42
E 36
	struct proc *p;
D 33
	struct args {
E 26
D 10
		int	hostid;
E 10
I 10
		long	hostid;
E 10
D 26
	} *uap = (struct a *)u.u_ap;
E 26
I 26
	} *uap;
E 33
I 33
D 42
	struct sethostid_args *uap;
E 33
	int *retval;
E 42
I 42
	struct compat_43_sethostid_args /* {
		syscallarg(int32_t) hostid;
	} */ *uap;
	register_t *retval;
E 42
{
E 26
I 23
	int error;
E 23

D 18
D 19
	if (suser())
		hostid = uap->hostid;
E 19
I 19
D 23
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
E 23
I 23
D 30
	if (error = suser(u.u_cred, &u.u_acflag))
E 30
I 30
	if (error = suser(p->p_ucred, &p->p_acflag))
E 30
D 27
		RETURN (error);
E 27
I 27
		return (error);
E 27
E 23
D 42
	hostid = uap->hostid;
E 42
I 42
	hostid = SCARG(uap, hostid);
E 42
I 23
D 27
	RETURN (0);
E 27
I 27
	return (0);
E 27
E 23
E 19
E 18
I 18
D 20
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
	hostid = uap->hostid;
E 20
E 18
D 38
}

I 33
struct gethostname_args {
	char	*hostname;
	u_int	len;
};
E 33
D 26
gethostname()
{
	register struct a {
E 26
I 26
/* ARGSUSED */
D 36
gethostname(p, uap, retval)
E 36
I 36
ogethostname(p, uap, retval)
E 36
	struct proc *p;
D 33
	struct args {
E 26
		char	*hostname;
D 13
		int	len;
E 13
I 13
		u_int	len;
E 13
D 26
	} *uap = (struct a *)u.u_ap;
E 26
I 26
	} *uap;
E 33
I 33
	struct gethostname_args *uap;
E 33
	int *retval;
{
I 35
	int name;
E 35
E 26
D 17
	register u_int len;
E 17

D 17
	len = uap->len;
	if (len > hostnamelen + 1)
		len = hostnamelen + 1;
	u.u_error = copyout((caddr_t)hostname, (caddr_t)uap->hostname, len);
E 17
I 17
D 35
	if (uap->len > hostnamelen + 1)
		uap->len = hostnamelen + 1;
D 23
	u.u_error = copyout((caddr_t)hostname, (caddr_t)uap->hostname,
		uap->len);
E 23
I 23
D 27
	RETURN (copyout((caddr_t)hostname, (caddr_t)uap->hostname, uap->len));
E 27
I 27
	return (copyout((caddr_t)hostname, (caddr_t)uap->hostname, uap->len));
E 35
I 35
	name = KERN_HOSTNAME;
	return (kern_sysctl(&name, 1, uap->hostname, &uap->len, 0, 0));
E 35
E 27
E 23
E 17
}

I 33
struct sethostname_args {
	char	*hostname;
	u_int	len;
};
E 33
D 26
sethostname()
{
	register struct a {
E 26
I 26
/* ARGSUSED */
D 36
sethostname(p, uap, retval)
E 36
I 36
osethostname(p, uap, retval)
E 36
	struct proc *p;
D 33
	register struct args {
E 26
		char	*hostname;
		u_int	len;
D 26
	} *uap = (struct a *)u.u_ap;
E 26
I 26
	} *uap;
E 33
I 33
	register struct sethostname_args *uap;
E 33
	int *retval;
{
E 26
I 23
D 35
	int error;
E 35
I 35
	int name;
E 35
E 23

D 18
D 19
	if (!suser())
E 19
I 19
D 23
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 19
E 18
I 18
D 20
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 20
E 18
		return;
	if (uap->len > sizeof (hostname) - 1) {
		u.u_error = EINVAL;
		return;
	}
E 23
I 23
D 30
	if (error = suser(u.u_cred, &u.u_acflag))
E 30
I 30
D 35
	if (error = suser(p->p_ucred, &p->p_acflag))
E 30
D 27
		RETURN (error);
E 27
I 27
		return (error);
E 27
	if (uap->len > sizeof (hostname) - 1)
D 27
		RETURN (EINVAL);
E 27
I 27
		return (EINVAL);
E 27
E 23
	hostnamelen = uap->len;
D 23
	u.u_error = copyin((caddr_t)uap->hostname, hostname, uap->len);
E 23
I 23
	error = copyin((caddr_t)uap->hostname, hostname, uap->len);
E 23
	hostname[hostnamelen] = 0;
I 23
D 27
	RETURN (error);
E 27
I 27
	return (error);
E 35
I 35
	name = KERN_HOSTNAME;
	return (kern_sysctl(&name, 1, 0, 0, uap->hostname, uap->len));
E 38
E 35
E 27
E 23
}

I 33
D 35
struct reboot_args {
	int	opt;
};
E 33
D 26
reboot()
{
D 25
	register struct a {
E 25
I 25
	struct a {
E 26
I 26
/* ARGSUSED */
reboot(p, uap, retval)
	struct proc *p;
D 33
	struct args {
E 26
E 25
		int	opt;
D 26
	};
E 26
I 26
	} *uap;
E 33
I 33
	struct reboot_args *uap;
E 33
	int *retval;
{
E 26
I 23
	int error;
E 23

D 18
D 19
	if (suser())
D 15
		boot(RB_BOOT, ((struct a *)u.u_ap)->opt);
E 15
I 15
		boot(((struct a *)u.u_ap)->opt);
E 19
I 19
D 23
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
E 23
I 23
D 30
	if (error = suser(u.u_cred, &u.u_acflag))
E 30
I 30
	if (error = suser(p->p_ucred, &p->p_acflag))
E 30
D 27
		RETURN (error);
E 27
I 27
		return (error);
E 27
E 23
D 26
	boot(((struct a *)u.u_ap)->opt);
E 26
I 26
	boot(uap->opt);
E 26
I 23
D 27
	RETURN (0);
E 27
I 27
	return (0);
E 27
E 23
E 19
E 18
I 18
D 20
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
	boot(((struct a *)u.u_ap)->opt);
E 20
E 18
E 15
}
I 22

D 31
ovhangup()
E 31
I 31
#ifdef COMPAT_43
E 35
D 42
oquota()
E 42
I 42
int
compat_43_quota(p, uap, retval)
	struct proc *p;
	void *uap;
	register_t *retval;
E 42
E 31
{
D 23
	u.u_error = EINVAL;
E 23
I 23

D 27
	RETURN (EINVAL);
E 27
I 27
D 31
	return (EINVAL);
E 31
I 31
	return (ENOSYS);
E 31
E 27
E 23
}
I 24
D 31

oldquota()
{

D 27
	RETURN (EINVAL);
E 27
I 27
	return (EINVAL);
E 27
}
E 31
I 31
D 35
#endif
E 35
I 35
#endif /* COMPAT_43 */
E 35
E 31
E 24
E 22
D 16

D 5
#ifndef NOCOMPAT
E 5
I 5
#ifdef COMPAT
E 5
I 2
#include "../h/quota.h"

E 2
osetuid()
{
	register uid;
	register struct a {
		int	uid;
	} *uap;

	uap = (struct a *)u.u_ap;
	uid = uap->uid;
D 19
	if (u.u_ruid == uid || u.u_uid == uid || suser()) {
E 19
I 19
D 20
	if (u.u_ruid == uid || u.u_uid == uid ||
	    ((u.u_error = suser(u.u_cred, &u.u_acflag)) == 0)) {
E 19
#ifdef QUOTA
		if (u.u_quota->q_uid != uid) {
			qclean();
			qstart(getquota(uid, 0, 0));
		}
#endif
I 19
		if (u.u_cred->cr_ref > 1)
			u.u_cred = crcopy(u.u_cred);
E 19
		u.u_uid = uid;
		u.u_procp->p_uid = uid;
		u.u_ruid = uid;
	}
}

osetgid()
{
	register gid;
	register struct a {
		int	gid;
	} *uap;

	uap = (struct a *)u.u_ap;
	gid = uap->gid;
D 19
	if (u.u_rgid == gid || u.u_gid == gid || suser()) {
E 19
I 19
	if (u.u_rgid == gid || u.u_gid == gid ||
	    ((u.u_error = suser(u.u_cred, &u.u_acflag)) == 0)) {
		if (u.u_cred->cr_ref > 1)
			u.u_cred = crcopy(u.u_cred);
E 19
		leavegroup(u.u_rgid);
		(void) entergroup(gid);
		u.u_gid = gid;
		u.u_rgid = gid;
	}
}

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

otime()
{

	u.u_r.r_time = time.tv_sec;
}

ostime()
{
	register struct a {
		int	time;
	} *uap = (struct a *)u.u_ap;
	struct timeval tv;
I 19
	int s;
E 19

I 19
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
E 19
	tv.tv_sec = uap->time;
	tv.tv_usec = 0;
D 19
	setthetime(&tv);
E 19
I 19
	/* WHAT DO WE DO ABOUT PENDING REAL-TIME TIMEOUTS??? */
	boottime.tv_sec += tv.tv_sec - time.tv_sec;
	s = splhigh(); time = tv; splx(s);
	resettodr();
E 19
}

/* from old timeb.h */
struct timeb {
	time_t	time;
	u_short	millitm;
	short	timezone;
	short	dstflag;
};

oftime()
{
	register struct a {
		struct	timeb	*tp;
	} *uap;
	struct timeb tb;
I 11
	int s;
E 11

	uap = (struct a *)u.u_ap;
D 11
	(void) spl7();
E 11
I 11
	s = splhigh();
E 11
	tb.time = time.tv_sec;
	tb.millitm = time.tv_usec / 1000;
D 11
	(void) spl0();
E 11
I 11
	splx(s);
E 11
	tb.timezone = tz.tz_minuteswest;
	tb.dstflag = tz.tz_dsttime;
	u.u_error = copyout((caddr_t)&tb, (caddr_t)uap->tp, sizeof (tb));
}

oalarm()
{
	register struct a {
		int	deltat;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
D 11
	int s = spl7();
E 11
I 11
	int s = splhigh();
E 11

	untimeout(realitexpire, (caddr_t)p);
	timerclear(&p->p_realtimer.it_interval);
	u.u_r.r_val1 = 0;
	if (timerisset(&p->p_realtimer.it_value) &&
	    timercmp(&p->p_realtimer.it_value, &time, >))
		u.u_r.r_val1 = p->p_realtimer.it_value.tv_sec - time.tv_sec;
	if (uap->deltat == 0) {
		timerclear(&p->p_realtimer.it_value);
		splx(s);
		return;
	}
	p->p_realtimer.it_value = time;
	p->p_realtimer.it_value.tv_sec += uap->deltat;
	timeout(realitexpire, (caddr_t)p, hzto(&p->p_realtimer.it_value));
	splx(s);
}

onice()
{
	register struct a {
		int	niceness;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;

	donice(p, (p->p_nice-NZERO)+uap->niceness);
}

#include "../h/times.h"

otimes()
{
	register struct a {
		struct	tms *tmsb;
	} *uap = (struct a *)u.u_ap;
	struct tms atms;

	atms.tms_utime = scale60(&u.u_ru.ru_utime);
	atms.tms_stime = scale60(&u.u_ru.ru_stime);
	atms.tms_cutime = scale60(&u.u_cru.ru_utime);
	atms.tms_cstime = scale60(&u.u_cru.ru_stime);
	u.u_error = copyout((caddr_t)&atms, (caddr_t)uap->tmsb, sizeof (atms));
}

scale60(tvp)
	register struct timeval *tvp;
{

	return (tvp->tv_sec * 60 + tvp->tv_usec / 16667);
}

#include "../h/vtimes.h"

ovtimes()
{
	register struct a {
		struct	vtimes *par;
		struct	vtimes *chi;
	} *uap = (struct a *)u.u_ap;
	struct vtimes avt;

	if (uap->par) {
		getvtimes(&u.u_ru, &avt);
		u.u_error = copyout((caddr_t)&avt, (caddr_t)uap->par,
			sizeof (avt));
		if (u.u_error)
			return;
	}
	if (uap->chi) {
		getvtimes(&u.u_cru, &avt);
		u.u_error = copyout((caddr_t)&avt, (caddr_t)uap->chi,
			sizeof (avt));
		if (u.u_error)
			return;
	}
I 2
}

D 19
#include "../machine/psl.h"
#include "../machine/reg.h"
E 19
I 19
#include "machine/psl.h"
#include "machine/reg.h"
E 20
E 19

owait()
{
	struct rusage ru;
	struct vtimes *vtp, avt;

	if ((u.u_ar0[PS] & PSL_ALLCC) != PSL_ALLCC) {
		u.u_error = wait1(0, (struct rusage *)0);
		return;
	}
	vtp = (struct vtimes *)u.u_ar0[R1];
	u.u_error = wait1(u.u_ar0[R0], &ru);
	if (u.u_error)
		return;
	getvtimes(&ru, &avt);
	(void) copyout((caddr_t)&avt, (caddr_t)vtp, sizeof (struct vtimes));
E 2
}

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

ovlimit()
{

	u.u_error = EACCES;
D 5
}

okill()
{
	register struct a {
		int	pid;
		int	signo;
	} *uap = (struct a *)u.u_ap;

	u.u_error = kill1(uap->signo < 0,
		uap->signo < 0 ? -uap->signo : uap->signo, uap->pid);
E 5
}

ossig()
{
D 3
	register int (*f)();
E 3
	struct a {
		int	signo;
		int	(*fun)();
D 3
	} *uap;
	register struct proc *p = u.u_procp;
	register a;
	long sigmask;
E 3
I 3
	} *uap = (struct a *)u.u_ap;
D 4
	register int a, (*f)();
E 4
I 4
	register int a;
	struct sigvec vec;
	register struct sigvec *sv = &vec;
E 4
	struct proc *p = u.u_procp;
E 3

D 3
	uap = (struct a *)u.u_ap;
	a = uap->signo & SIGNUMMASK;
E 3
D 4
	f = uap->fun;
E 4
D 3
	if (a<=0 || a>=NSIG || a==SIGKILL || a==SIGSTOP ||
	    a==SIGCONT && (f == SIG_IGN || f == SIG_HOLD)) {
		u.u_error = EINVAL;
		return;
	}
	if ((uap->signo &~ SIGNUMMASK) || (f != SIG_DFL && f != SIG_IGN &&
	    SIGISDEFER(f)))
		u.u_procp->p_flag |= SNUSIG;
	/* 
	 * Don't clobber registers if we are to simulate
	 * a ret+rti.
	 */
	if ((uap->signo&SIGDORTI) == 0)
		u.u_r.r_val1 = (int)u.u_signal[a];
E 3
I 3
	a = uap->signo;
I 4
	sv->sv_handler = uap->fun;
E 4
E 3
	/*
D 3
	 * Change setting atomically.
E 3
I 3
	 * Kill processes trying to use job control facilities
	 * (this'll help us find any vestiges of the old stuff).
E 3
	 */
D 3
	(void) spl6();
	sigmask = 1L << (a-1);
	if (f == SIG_IGN)
		p->p_sig &= ~sigmask;		/* never to be seen again */
	u.u_signal[a] = f;
	if (f != SIG_DFL && f != SIG_IGN && f != SIG_HOLD)
		f = SIG_CATCH;
	if ((int)f & 1)
		p->p_siga0 |= sigmask;
	else
		p->p_siga0 &= ~sigmask;
	if ((int)f & 2)
		p->p_siga1 |= sigmask;
	else
		p->p_siga1 &= ~sigmask;
	(void) spl0();
	/*
	 * Now handle options.
	 */
	if (uap->signo & SIGDOPAUSE) {
		/*
		 * Simulate a PDP11 style wait instrution which
		 * atomically lowers priority, enables interrupts
		 * and hangs.
		 */
		opause();
		/*NOTREACHED*/
E 3
I 3
	if ((a &~ 0377) ||
D 4
	    (f != SIG_DFL && f != SIG_IGN && ((int)f) & 1)) {
E 4
I 4
	    (sv->sv_handler != SIG_DFL && sv->sv_handler != SIG_IGN &&
	     ((int)sv->sv_handler) & 1)) {
E 4
		psignal(p, SIGSYS);
		return;
E 3
	}
D 3
	if (uap->signo & SIGDORTI)
		u.u_eosys = SIMULATERTI;
E 3
I 3
	if (a <= 0 || a >= NSIG || a == SIGKILL || a == SIGSTOP ||
D 4
	    a == SIGCONT && (f == SIG_IGN || f == SIG_HOLD)) {
E 4
I 4
	    a == SIGCONT && sv->sv_handler == SIG_IGN) {
E 4
		u.u_error = EINVAL;
		return;
	}
D 4
	setsignal(a, f, 0);
E 4
I 4
	sv->sv_mask = 0;
D 8
	sv->sv_onstack = 0;
E 8
I 8
	sv->sv_flags = SV_INTERRUPT;
E 8
	u.u_r.r_val1 = (int)u.u_signal[a];
	setsigvec(a, sv);
E 4
	p->p_flag |= SOUSIG;		/* mark as simulating old stuff */
E 3
}
#endif
E 16
E 1
