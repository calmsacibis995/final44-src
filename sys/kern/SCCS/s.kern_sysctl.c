h43838
s 00001/00001/00766
d D 8.9 95/05/20 01:19:16 mckusick 56 55
c sysctl_vnode passes a proc pointer
e
s 00004/00006/00763
d D 8.8 95/03/30 14:08:59 mckusick 55 54
c enable vfs_sysctl; fix range bug in debug code
e
s 00062/00054/00707
d D 8.7 95/02/14 10:23:43 cgd 54 53
c new argument passing conversion.  minor type size cleanups.
e
s 00001/00001/00760
d D 8.6 95/01/18 15:27:01 mckusick 53 52
c always lock except when doing vnodes
e
s 00004/00004/00757
d D 8.5 94/08/22 10:19:51 mckusick 52 51
c use new queue.h data structures
e
s 00001/00001/00760
d D 8.4 94/04/14 10:52:06 mckusick 51 50
c phase error on length computation (from Mark Dapoz md@bsc.no)
e
s 00004/00000/00757
d D 8.3 94/01/06 16:32:21 mckusick 50 49
c update to approximate process resident set size (from hibler)
e
s 00003/00003/00754
d D 8.2 93/09/23 15:26:54 bostic 49 48
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00755
d D 8.1 93/06/16 14:32:42 bostic 48 47
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/00752
d D 7.45 93/06/16 14:32:11 mckusick 47 45
c supress warnings
e
s 00002/00002/00752
d R 8.1 93/06/10 21:58:05 bostic 46 45
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00753
d D 7.44 93/06/04 17:02:29 mckusick 45 44
c only set hostnamelen when setting new hostname
e
s 00000/00018/00754
d D 7.43 93/05/25 17:15:48 mckusick 44 43
c gone are things that belong in pathconf
e
s 00001/00001/00771
d D 7.42 93/05/20 21:22:25 mckusick 43 42
c add CPU_MACHDEP
e
s 00004/00001/00767
d D 7.41 93/05/20 12:52:15 mckusick 42 41
c add KERN_BOOTTIME
e
s 00001/00001/00767
d D 7.40 93/05/12 16:53:33 mckusick 41 40
c more accurate check on KERN_PROC specifications
e
s 00001/00001/00767
d D 7.39 93/05/05 15:45:28 mckusick 40 39
c KERN_NO_TRUNC is true, we don't truncate file names
e
s 00044/00015/00724
d D 7.38 93/05/04 09:00:04 bostic 39 37
c fold rest of POSIX 1003.1, 1003.2 configurable system variables into sysctl
e
s 00002/00000/00739
d R 7.38 93/05/03 17:00:12 bostic 38 37
c add POSIX 1003.2 version
e
s 00002/00002/00737
d D 7.37 93/05/01 13:52:55 mckusick 37 36
c delete hardware speed, add machine byte order
e
s 00001/00004/00738
d D 7.36 93/04/27 15:09:58 mckusick 36 35
c kinfo_proc is merged into sysctl.h
e
s 00003/00000/00739
d D 7.35 93/04/27 00:47:13 mckusick 35 34
c add KERN_MAXVNODES
e
s 00042/00010/00697
d D 7.34 93/04/27 00:31:34 mckusick 34 33
c add support for kernel profiling; add sysctl_struct; eliminate trailing blanks
e
s 00052/00003/00655
d D 7.33 93/04/19 00:24:03 mckusick 33 32
c add support for debugging variables
e
s 00001/00001/00657
d D 7.32 93/04/04 13:15:45 mckusick 32 31
c getkerninfo becomes COMPAT
e
s 00018/00019/00640
d D 7.31 93/03/04 17:58:50 bostic 31 30
c change buffer lengths of sysctl(2) to be size_t's
c change array size of sysctl(2) to be u_int's
e
s 00006/00002/00653
d D 7.30 93/03/04 16:56:29 mckusick 30 29
c don't try to copy in/out size if not requested in getkerninfo (hibler)
e
s 00030/00014/00625
d D 7.29 93/03/03 15:06:31 mckusick 29 28
c add security level to kern_sysctl
e
s 00003/00002/00636
d D 7.28 93/02/21 13:52:11 ralph 28 27
c don't write through *oldlenp if oldp is NULL. (see sethostname())
e
s 00008/00002/00630
d D 7.27 93/02/10 19:39:53 mckusick 27 26
c eliminate need for kinfo.h
e
s 00471/00148/00161
d D 7.26 93/02/04 01:22:15 mckusick 26 25
c kern_kinfo becomes kern_sysctl; major overhaul and merger with BSDI
c contributed interface
e
s 00009/00009/00300
d D 7.25 92/10/11 10:38:05 bostic 25 24
c make kernel includes standard
e
s 00007/00006/00302
d D 7.24 92/07/10 20:49:25 torek 24 23
c ANSIfy syscall args
e
s 00001/00001/00307
d D 7.23 92/07/07 14:44:54 torek 23 22
c volatile poisoning
e
s 00005/00000/00303
d D 7.22 92/06/02 21:26:11 mckusick 22 21
c skip SIDL processes
e
s 00009/00001/00294
d D 7.21 92/02/25 17:17:53 mckusick 21 20
c add stubs for getting load average and clock rate
e
s 00033/00015/00262
d D 7.20 92/02/05 22:29:55 torek 20 19
c minor cleanups; sparc vmspace is too big to fit in eproc
e
s 00003/00005/00274
d D 7.19 91/11/16 12:36:03 ralph 19 18
c move copyin() call so if uap->size pointer is null, still return size
e
s 00005/00000/00274
d D 7.18 91/08/28 15:31:15 mckusick 18 17
c add support to get vmtotal structure calculated
e
s 00059/00001/00215
d D 7.17 91/06/26 13:57:53 marc 17 16
c KINFO_FILE to extract file structures
e
s 00001/00001/00215
d D 7.16 91/06/07 09:36:59 karels 16 15
c consistency with tty.c about value for "no pgrp"
e
s 00004/00001/00212
d D 7.15 91/05/05 09:01:21 karels 15 14
c proc 0 has no p_pptr
e
s 00039/00025/00174
d D 7.14 91/04/20 14:45:19 karels 14 13
c move eproc copy to fill_eproc so coredump can use it
e
s 00009/00006/00190
d D 7.13 91/03/17 15:42:22 karels 13 12
c more-or-less working with new proc & user structs
e
s 00002/00018/00194
d D 7.12 90/12/05 16:35:22 mckusick 12 11
c update for new VM
e
s 00001/00011/00211
d D 7.11 90/06/28 21:19:41 bostic 11 10
c new copyright notice
e
s 00010/00008/00212
d D 7.10 90/06/22 17:17:56 mckusick 10 9
c new system call convention
e
s 00011/00012/00209
d D 7.9 90/06/22 15:10:25 marc 9 8
c checked in for marc by mckusick
e
s 00009/00003/00212
d D 7.8 90/05/01 11:20:31 marc 8 7
c add kinfo_vnode, special case not locking pages (XXX)
e
s 00002/00002/00213
d D 7.7 90/04/10 18:08:45 marc 7 6
c return controlling tty even if proc has lost it.
e
s 00018/00021/00197
d D 7.6 90/04/05 15:11:44 marc 6 5
c single thread
e
s 00040/00024/00178
d D 7.5 90/02/22 15:33:30 marc 5 4
c checkpoint before removing extra estimation pass
e
s 00056/00048/00146
d D 7.4 90/02/14 10:37:39 marc 4 3
c This version compiles, not yet tested! (by kls).
e
s 00012/00020/00182
d D 7.3 90/02/14 10:32:16 marc 3 2
c checkpoint by sklower before re-arranging
e
s 00003/00000/00199
d D 7.2 90/01/31 16:58:54 mckusick 2 1
c get minimal set of include files
e
s 00199/00000/00000
d D 7.1 90/01/31 16:29:37 marc 1 0
c date and time created 90/01/31 16:29:37 by marc
e
u
U
t
T
I 1
D 26
/*
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 26
I 26
/*-
D 48
 * Copyright (c) 1982, 1986, 1989, 1993 Regents of the University of California.
E 26
 * All rights reserved.
E 48
I 48
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 48
 *
I 26
 * This code is derived from software contributed to Berkeley by
 * Mike Karels at Berkeley Software Design, Inc.
 *
E 26
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
 *
 *	%W% (Berkeley) %G%
 */

I 26
/*
 * sysctl system call.
 */

E 26
I 2
D 25
#include "param.h"
D 14
#include "user.h"
E 14
#include "proc.h"
I 5
D 12
#include "text.h"
E 12
E 5
E 2
#include "kinfo.h"
D 12
#include "vm.h"
E 12
#include "ioctl.h"
#include "tty.h"
#include "buf.h"
I 17
#include "file.h"
E 25
I 25
#include <sys/param.h>
I 26
#include <sys/systm.h>
I 42
#include <sys/kernel.h>
E 42
#include <sys/malloc.h>
E 26
#include <sys/proc.h>
D 26
#include <sys/kinfo.h>
E 26
I 26
#include <sys/file.h>
I 35
#include <sys/vnode.h>
E 35
D 36
#include <sys/sysctl.h>
E 36
#include <sys/unistd.h>
#include <sys/buf.h>
E 26
#include <sys/ioctl.h>
#include <sys/tty.h>
D 26
#include <sys/buf.h>
#include <sys/file.h>
E 26
E 25
E 17
D 36

E 36
I 14
D 25
#include "vm/vm.h"
E 25
I 25
#include <vm/vm.h>
E 25
D 36

D 25
#include "kinfo_proc.h"
E 25
I 25
#include <sys/kinfo_proc.h>
E 36
I 36
#include <sys/sysctl.h>
E 36
E 25

I 54
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 54
E 14
D 4
/* TODO - gather stats on average and max time spent */
E 4
I 4
D 12

E 12
D 26
#define snderr(e) { error = (e); goto release;}
D 8
extern int kinfo_doproc(), kinfo_rtable();
E 8
I 8
D 17
extern int kinfo_doproc(), kinfo_rtable(), kinfo_vnode();
E 17
I 17
extern int kinfo_doproc(), kinfo_rtable(), kinfo_vnode(), kinfo_file();
I 18
D 21
extern int kinfo_meter();
E 21
I 21
extern int kinfo_meter(), kinfo_loadavg(), kinfo_clockrate();
E 21
E 18
E 17
E 8
struct kinfo_lock kinfo_lock;
E 26
I 26
sysctlfn kern_sysctl;
sysctlfn hw_sysctl;
I 33
#ifdef DEBUG
sysctlfn debug_sysctl;
#endif
E 33
extern sysctlfn vm_sysctl;
D 55
extern sysctlfn fs_sysctl;
E 55
I 55
extern sysctlfn vfs_sysctl;
E 55
extern sysctlfn net_sysctl;
extern sysctlfn cpu_sysctl;
E 26

I 24
D 26
struct getkerninfo_args {
	int	op;
	char	*where;
	int	*size;
	int	arg;
E 26
I 26
/*
 * Locking and stats
 */
static struct sysctl_lock {
	int	sl_lock;
	int	sl_want;
	int	sl_locked;
} memlock;

D 54
struct sysctl_args {
	int	*name;
	u_int	namelen;
	void	*old;
D 31
	u_int	*oldlenp;
E 31
I 31
	size_t	*oldlenp;
E 31
	void	*new;
D 31
	u_int	newlen;
E 31
I 31
	size_t	newlen;
E 31
E 26
};
E 24
E 4
D 5
getkinfo()
E 5
I 5
D 10
getkerninfo()
E 5
{
	register struct a {
E 10
I 10
D 26
/* ARGSUSED */
getkerninfo(p, uap, retval)
E 26
I 26

E 54
D 29
#define	STK_PARAMS	32	/* largest old/new values on stack */

E 29
D 39
sysctl(p, uap, retval)
E 39
I 39
int
__sysctl(p, uap, retval)
E 39
E 26
	struct proc *p;
D 24
	register struct args {
E 10
		int	op;
		char	*where;
		int	*size;
		int	arg;
D 10
	} *uap = (struct a *)u.u_ap;
E 10
I 10
	} *uap;
E 24
I 24
D 26
	register struct getkerninfo_args *uap;
E 26
I 26
D 54
	register struct sysctl_args *uap;
E 26
E 24
	int *retval;
E 54
I 54
	register struct __sysctl_args /* {
		syscallarg(int *) name;
		syscallarg(u_int) namelen;
		syscallarg(void *) old;
		syscallarg(size_t *) oldlenp;
		syscallarg(void *) new;
		syscallarg(size_t) newlen;
	} */ *uap;
	register_t *retval;
E 54
{
E 10
D 4
	int wanted;
E 4
I 4
D 5
	int wanted, (*server)(), error = 0;
E 5
I 5
D 19

E 19
E 5
D 13
	int	bufsize,	/* max size of users buffer */
D 6
		copysize, 	/* size copied */
E 6
D 5
		needed,	
		locked;
E 5
I 5
		needed,	locked, (*server)(), error = 0;
E 13
I 13
D 26
	int bufsize;		/* max size of users buffer */
	int needed, locked, (*server)(), error = 0;
E 26
I 26
	int error, dolock = 1;
D 54
	u_int savelen, oldlen = 0;
E 54
I 54
	size_t savelen, oldlen = 0;
E 54
	sysctlfn *fn;
	int name[CTL_MAXNAME];
E 26
E 13
E 5
E 4

I 4
D 5
	while (kinfo_lock.kl_lock) {
		kinfo_lock.kl_want++;
		sleep(&kinfo_lock, PRIBIO+1);
		kinfo_lock.kl_want--;
		kinfo_lock.kl_locked++;
	}
	kinfo_lock.kl_lock++;
E 5
I 5
D 13
	if (error = copyin((caddr_t)uap->size,
				(caddr_t)&bufsize, sizeof (bufsize)))
E 13
I 13
D 19
	if (error = copyin((caddr_t)uap->size, (caddr_t)&bufsize,
	    sizeof (bufsize)))
E 13
D 6
		goto bad;
E 6
I 6
		goto done;
E 6
E 5

E 19
E 4
D 26
	switch (ki_type(uap->op)) {
E 26
I 26
D 54
	if (uap->new != NULL && (error = suser(p->p_ucred, &p->p_acflag)))
E 54
I 54
	if (SCARG(uap, new) != NULL &&
	    (error = suser(p->p_ucred, &p->p_acflag)))
E 54
		return (error);
	/*
	 * all top-level sysctl names are non-terminal
	 */
D 54
	if (uap->namelen > CTL_MAXNAME || uap->namelen < 2)
E 54
I 54
	if (SCARG(uap, namelen) > CTL_MAXNAME || SCARG(uap, namelen) < 2)
E 54
		return (EINVAL);
D 54
	if (error = copyin(uap->name, &name, uap->namelen * sizeof(int)))
E 54
I 54
	if (error =
	    copyin(SCARG(uap, name), &name, SCARG(uap, namelen) * sizeof(int)))
E 54
		return (error);
E 26

D 26
	case KINFO_PROC:
D 4
		u.u_error = kinfo_proc(uap->op, (char *)uap->where, 
				       (int *)uap->size, uap->arg, &wanted);
		if (!u.u_error)
			u.u_r.r_val1 = wanted;
E 4
I 4
		server = kinfo_doproc;
E 26
I 26
	switch (name[0]) {
	case CTL_KERN:
		fn = kern_sysctl;
D 53
		if (name[2] != KERN_VNODE)	/* XXX */
E 53
I 53
		if (name[2] == KERN_VNODE)	/* XXX */
E 53
			dolock = 0;
E 26
E 4
		break;
D 26

I 4
	case KINFO_RT:
		server = kinfo_rtable;
E 26
I 26
	case CTL_HW:
		fn = hw_sysctl;
E 26
		break;
D 26

I 8
	case KINFO_VNODE:
		server = kinfo_vnode;
E 26
I 26
	case CTL_VM:
		fn = vm_sysctl;
E 26
		break;
D 26

I 17
	case KINFO_FILE:
		server = kinfo_file;
E 26
I 26
	case CTL_NET:
		fn = net_sysctl;
E 26
I 18
		break;
D 26

	case KINFO_METER:
		server = kinfo_meter;
E 26
I 26
D 55
#ifdef notyet
	case CTL_FS:
		fn = fs_sysctl;
E 55
I 55
	case CTL_VFS:
		fn = vfs_sysctl;
E 55
E 26
I 21
		break;
I 43
D 55
#endif
E 55
E 43
D 26

	case KINFO_LOADAVG:
		server = kinfo_loadavg;
E 26
I 26
D 33
	case CTL_DEBUG:
		fn = debug_sysctl;
E 26
		break;
E 33
D 26

	case KINFO_CLOCKRATE:
		server = kinfo_clockrate;
E 26
I 26
	case CTL_MACHDEP:
		fn = cpu_sysctl;
E 26
E 21
E 18
		break;
D 26

E 26
I 26
D 43
#endif
E 43
I 33
#ifdef DEBUG
	case CTL_DEBUG:
		fn = debug_sysctl;
		break;
#endif
E 33
E 26
E 17
E 8
E 4
	default:
D 4
		u.u_error = EINVAL;
E 4
I 4
D 5
		snderr(EINVAL);
E 5
I 5
D 26
		error = EINVAL;
D 6
		goto bad;
E 6
I 6
		goto done;
E 26
I 26
		return (EOPNOTSUPP);
E 26
E 6
E 5
E 4
	}
I 6
D 26
	if (uap->where == NULL || uap->size == NULL) {
		error = (*server)(uap->op, NULL, NULL, uap->arg, &needed);
		goto done;
E 26
I 26

D 54
	if (uap->oldlenp &&
	    (error = copyin(uap->oldlenp, &oldlen, sizeof(oldlen))))
E 54
I 54
	if (SCARG(uap, oldlenp) &&
	    (error = copyin(SCARG(uap, oldlenp), &oldlen, sizeof(oldlen))))
E 54
		return (error);
D 54
	if (uap->old != NULL) {
		if (!useracc(uap->old, oldlen, B_WRITE))
E 54
I 54
	if (SCARG(uap, old) != NULL) {
		if (!useracc(SCARG(uap, old), oldlen, B_WRITE))
E 54
			return (EFAULT);
		while (memlock.sl_lock) {
			memlock.sl_want = 1;
			sleep((caddr_t)&memlock, PRIBIO+1);
			memlock.sl_locked++;
		}
		memlock.sl_lock = 1;
		if (dolock)
D 54
			vslock(uap->old, oldlen);
E 54
I 54
			vslock(SCARG(uap, old), oldlen);
E 54
		savelen = oldlen;
E 26
	}
I 19
D 26
	if (error = copyin((caddr_t)uap->size, (caddr_t)&bufsize,
	    sizeof (bufsize)))
		goto done;
E 19
E 6
I 5
	while (kinfo_lock.kl_lock) {
D 20
		kinfo_lock.kl_want++;
		sleep(&kinfo_lock, PRIBIO+1);
		kinfo_lock.kl_want--;
E 20
I 20
		kinfo_lock.kl_want = 1;
		sleep((caddr_t)&kinfo_lock, PRIBIO+1);
E 20
		kinfo_lock.kl_locked++;
E 26
I 26
D 54
	error = (*fn)(name + 1, uap->namelen - 1, uap->old, &oldlen,
D 29
	    uap->new, uap->newlen);
E 29
I 29
	    uap->new, uap->newlen, p);
E 29
	if (uap->old != NULL) {
E 54
I 54
	error = (*fn)(name + 1, SCARG(uap, namelen) - 1, SCARG(uap, old),
	    &oldlen, SCARG(uap, new), SCARG(uap, newlen), p);
	if (SCARG(uap, old) != NULL) {
E 54
		if (dolock)
D 54
			vsunlock(uap->old, savelen, B_WRITE);
E 54
I 54
			vsunlock(SCARG(uap, old), savelen, B_WRITE);
E 54
		memlock.sl_lock = 0;
		if (memlock.sl_want) {
			memlock.sl_want = 0;
			wakeup((caddr_t)&memlock);
		}
E 26
	}
D 20
	kinfo_lock.kl_lock++;
E 20
I 20
D 26
	kinfo_lock.kl_lock = 1;
E 26
I 26
	if (error)
		return (error);
D 54
	if (uap->oldlenp)
		error = copyout(&oldlen, uap->oldlenp, sizeof(oldlen));
E 54
I 54
	if (SCARG(uap, oldlenp))
		error = copyout(&oldlen, SCARG(uap, oldlenp), sizeof(oldlen));
E 54
	*retval = oldlen;
	return (0);
}
E 26
E 20

E 5
I 4
D 6
	if (error = (*server)(uap->op, NULL, NULL, uap->arg, &needed))
		goto release;
	if (uap->where == NULL || uap->size == NULL)
		goto release;  /* only want estimate of bufsize */
D 5
	if (error = copyin((caddr_t)uap->size,
				(caddr_t)&bufsize, sizeof (bufsize)))
		goto release;
E 5
	locked = copysize = MIN(needed, bufsize);
	if (!useracc(uap->where, copysize, B_WRITE))
E 6
I 6
D 26
	if (!useracc(uap->where, bufsize, B_WRITE))
E 6
		snderr(EFAULT);
D 12
	/*
	 * lock down target pages - NEED DEADLOCK AVOIDANCE
	 */
D 6
	if (copysize > ((int)ptob(freemem) - (20 * 1024))) 	/* XXX */
E 6
I 6
	if (bufsize > ((int)ptob(freemem) - (20 * 1024))) 	/* XXX */
E 6
		snderr(ENOMEM);
E 12
D 6
	vslock(uap->where, copysize);
	error = (*server)(uap->op, uap->where, &copysize, uap->arg, &needed);
E 6
I 6
D 8
	vslock(uap->where, bufsize);
E 8
I 8
	if (server != kinfo_vnode)	/* XXX */
		vslock(uap->where, bufsize);
E 8
	locked = bufsize;
	error = (*server)(uap->op, uap->where, &bufsize, uap->arg, &needed);
E 6
D 8
	vsunlock(uap->where, locked, B_WRITE);
E 8
I 8
	if (server != kinfo_vnode)	/* XXX */
		vsunlock(uap->where, locked, B_WRITE);
E 8
D 6
	if (error)
		goto release;
	error = copyout((caddr_t)&copysize,
				(caddr_t)uap->size, sizeof (copysize));
E 4

E 6
I 6
	if (error == 0)
		error = copyout((caddr_t)&bufsize,
				(caddr_t)uap->size, sizeof (bufsize));
E 6
D 4
	return;
E 4
I 4
release:
D 20
	kinfo_lock.kl_lock--;
	if (kinfo_lock.kl_want)
		wakeup(&kinfo_lock);
E 20
I 20
	kinfo_lock.kl_lock = 0;
	if (kinfo_lock.kl_want) {
		kinfo_lock.kl_want = 0;
		wakeup((caddr_t)&kinfo_lock);
E 26
I 26
/*
 * Attributes stored in the kernel.
 */
char hostname[MAXHOSTNAMELEN];
int hostnamelen;
long hostid;
I 29
int securelevel;
E 29

D 29
kern_sysctl(name, namelen, oldp, oldlenp, newp, newlen)
E 29
I 29
/*
 * kernel related system variables.
 */
kern_sysctl(name, namelen, oldp, oldlenp, newp, newlen, p)
E 29
	int *name;
	u_int namelen;
	void *oldp;
D 31
	u_int *oldlenp;
E 31
I 31
	size_t *oldlenp;
E 31
	void *newp;
D 31
	u_int newlen;
E 31
I 31
	size_t newlen;
E 31
I 29
	struct proc *p;
E 29
{
D 29
	int error;
E 29
I 29
D 47
	int error, level;
E 47
I 47
	int error, level, inthostid;
E 47
E 29
	extern char ostype[], osrelease[], version[];

	/* all sysctl names at this level are terminal */
D 34
	if (namelen != 1 && name[0] != KERN_PROC)
E 34
I 34
	if (namelen != 1 && !(name[0] == KERN_PROC || name[0] == KERN_PROF))
E 34
		return (ENOTDIR);		/* overloaded */

	switch (name[0]) {
	case KERN_OSTYPE:
		return (sysctl_rdstring(oldp, oldlenp, newp, ostype));
	case KERN_OSRELEASE:
		return (sysctl_rdstring(oldp, oldlenp, newp, osrelease));
	case KERN_OSREV:
		return (sysctl_rdint(oldp, oldlenp, newp, BSD));
	case KERN_VERSION:
		return (sysctl_rdstring(oldp, oldlenp, newp, version));
D 39
	case KERN_POSIX1:
		return (sysctl_rdint(oldp, oldlenp, newp, _POSIX_VERSION));
E 39
I 39
	case KERN_MAXVNODES:
		return(sysctl_int(oldp, oldlenp, newp, newlen, &desiredvnodes));
E 39
	case KERN_MAXPROC:
		return (sysctl_int(oldp, oldlenp, newp, newlen, &maxproc));
	case KERN_MAXFILES:
		return (sysctl_int(oldp, oldlenp, newp, newlen, &maxfiles));
I 35
D 39
	case KERN_MAXVNODES:
		return(sysctl_int(oldp, oldlenp, newp, newlen, &desiredvnodes));
E 39
E 35
	case KERN_ARGMAX:
		return (sysctl_rdint(oldp, oldlenp, newp, ARG_MAX));
D 39
	case KERN_HOSTNAME:
D 34
		error = sysctl_string(oldp, oldlenp, newp, newlen, 
E 34
I 34
		error = sysctl_string(oldp, oldlenp, newp, newlen,
E 34
		    hostname, sizeof(hostname));
		if (!error)
			hostnamelen = newlen;
		return (error);
	case KERN_HOSTID:
		return (sysctl_int(oldp, oldlenp, newp, newlen, &hostid));
E 39
I 29
	case KERN_SECURELVL:
		level = securelevel;
		if ((error = sysctl_int(oldp, oldlenp, newp, newlen, &level)) ||
		    newp == NULL)
			return (error);
		if (level < securelevel && p->p_pid != 1)
			return (EPERM);
		securelevel = level;
		return (0);
I 39
	case KERN_HOSTNAME:
		error = sysctl_string(oldp, oldlenp, newp, newlen,
		    hostname, sizeof(hostname));
D 45
		if (!error)
E 45
I 45
		if (newp && !error)
E 45
			hostnamelen = newlen;
		return (error);
	case KERN_HOSTID:
D 47
		return (sysctl_int(oldp, oldlenp, newp, newlen, &hostid));
E 47
I 47
		inthostid = hostid;  /* XXX assumes sizeof long <= sizeof int */
		error =  sysctl_int(oldp, oldlenp, newp, newlen, &inthostid);
		hostid = inthostid;
		return (error);
E 47
E 39
E 29
	case KERN_CLOCKRATE:
		return (sysctl_clockrate(oldp, oldlenp));
I 42
	case KERN_BOOTTIME:
		return (sysctl_rdstruct(oldp, oldlenp, newp, &boottime,
		    sizeof(struct timeval)));
E 42
D 39
	case KERN_FILE:
		return (sysctl_file(oldp, oldlenp));
E 39
	case KERN_VNODE:
D 56
		return (sysctl_vnode(oldp, oldlenp));
E 56
I 56
		return (sysctl_vnode(oldp, oldlenp, p));
E 56
	case KERN_PROC:
		return (sysctl_doproc(name + 1, namelen - 1, oldp, oldlenp));
I 39
	case KERN_FILE:
		return (sysctl_file(oldp, oldlenp));
E 39
I 34
#ifdef GPROF
	case KERN_PROF:
		return (sysctl_doprof(name + 1, namelen - 1, oldp, oldlenp,
		    newp, newlen));
#endif
I 39
	case KERN_POSIX1:
		return (sysctl_rdint(oldp, oldlenp, newp, _POSIX_VERSION));
	case KERN_NGROUPS:
		return (sysctl_rdint(oldp, oldlenp, newp, NGROUPS_MAX));
	case KERN_JOB_CONTROL:
		return (sysctl_rdint(oldp, oldlenp, newp, 1));
	case KERN_SAVED_IDS:
#ifdef _POSIX_SAVED_IDS
		return (sysctl_rdint(oldp, oldlenp, newp, 1));
#else
		return (sysctl_rdint(oldp, oldlenp, newp, 0));
#endif
D 44
	case KERN_LINK_MAX:
		return (sysctl_rdint(oldp, oldlenp, newp, LINK_MAX));
	case KERN_MAX_CANON:
		return (sysctl_rdint(oldp, oldlenp, newp, MAX_CANON));
	case KERN_MAX_INPUT:
		return (sysctl_rdint(oldp, oldlenp, newp, MAX_INPUT));
	case KERN_NAME_MAX:
		return (sysctl_rdint(oldp, oldlenp, newp, NAME_MAX));
	case KERN_PATH_MAX:
		return (sysctl_rdint(oldp, oldlenp, newp, PATH_MAX));
	case KERN_PIPE_BUF:
		return (sysctl_rdint(oldp, oldlenp, newp, PIPE_BUF));
	case KERN_CHOWN_RESTRICTED:
		return (sysctl_rdint(oldp, oldlenp, newp, 1));
	case KERN_NO_TRUNC:
D 40
		return (sysctl_rdint(oldp, oldlenp, newp, 0));
E 40
I 40
		return (sysctl_rdint(oldp, oldlenp, newp, 1));
E 40
	case KERN_VDISABLE:
		return (sysctl_rdint(oldp, oldlenp, newp, _POSIX_VDISABLE));
E 44
E 39
E 34
	default:
		return (EOPNOTSUPP);
E 26
	}
E 20
I 5
D 6
bad:
E 6
I 6
D 26
done:
E 6
E 5
D 10
	if (error)
		u.u_error = error;
	else
		u.u_r.r_val1 = needed;
E 10
I 10
	if (!error)
		*retval = needed;
E 26
I 26
	/* NOTREACHED */
}

D 29
hw_sysctl(name, namelen, oldp, oldlenp, newp, newlen)
E 29
I 29
/*
 * hardware related system variables.
 */
hw_sysctl(name, namelen, oldp, oldlenp, newp, newlen, p)
E 29
	int *name;
	u_int namelen;
	void *oldp;
D 31
	u_int *oldlenp;
E 31
I 31
	size_t *oldlenp;
E 31
	void *newp;
D 31
	u_int newlen;
E 31
I 31
	size_t newlen;
E 31
I 29
	struct proc *p;
E 29
{
	extern char machine[], cpu_model[];

	/* all sysctl names at this level are terminal */
	if (namelen != 1)
		return (ENOTDIR);		/* overloaded */

	switch (name[0]) {
	case HW_MACHINE:
		return (sysctl_rdstring(oldp, oldlenp, newp, machine));
	case HW_MODEL:
		return (sysctl_rdstring(oldp, oldlenp, newp, cpu_model));
	case HW_NCPU:
		return (sysctl_rdint(oldp, oldlenp, newp, 1));	/* XXX */
D 37
	case HW_CPUSPEED:
		return (sysctl_rdint(oldp, oldlenp, newp, cpuspeed));
E 37
I 37
	case HW_BYTEORDER:
		return (sysctl_rdint(oldp, oldlenp, newp, BYTE_ORDER));
E 37
	case HW_PHYSMEM:
		return (sysctl_rdint(oldp, oldlenp, newp, ctob(physmem)));
	case HW_USERMEM:
		return (sysctl_rdint(oldp, oldlenp, newp,
		    ctob(physmem - cnt.v_wire_count)));
	case HW_PAGESIZE:
		return (sysctl_rdint(oldp, oldlenp, newp, PAGE_SIZE));
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
}
I 33

#ifdef DEBUG
/*
 * Debugging related system variables.
 */
struct ctldebug debug0, debug1, debug2, debug3, debug4;
struct ctldebug debug5, debug6, debug7, debug8, debug9;
struct ctldebug debug10, debug11, debug12, debug13, debug14;
struct ctldebug debug15, debug16, debug17, debug18, debug19;
static struct ctldebug *debugvars[CTL_DEBUG_MAXID] = {
	&debug0, &debug1, &debug2, &debug3, &debug4,
	&debug5, &debug6, &debug7, &debug8, &debug9,
	&debug10, &debug11, &debug12, &debug13, &debug14,
	&debug15, &debug16, &debug17, &debug18, &debug19,
};
int
debug_sysctl(name, namelen, oldp, oldlenp, newp, newlen, p)
	int *name;
	u_int namelen;
	void *oldp;
	size_t *oldlenp;
	void *newp;
	size_t newlen;
	struct proc *p;
{
	struct ctldebug *cdp;

	/* all sysctl names at this level are name and field */
	if (namelen != 2)
		return (ENOTDIR);		/* overloaded */
	cdp = debugvars[name[0]];
D 55
	if (cdp->debugname == 0)
E 55
I 55
	if (name[0] >= CTL_DEBUG_MAXID || cdp->debugname == 0)
E 55
		return (EOPNOTSUPP);
	switch (name[1]) {
	case CTL_DEBUG_NAME:
		return (sysctl_rdstring(oldp, oldlenp, newp, cdp->debugname));
	case CTL_DEBUG_VALUE:
		return (sysctl_int(oldp, oldlenp, newp, newlen, cdp->debugvar));
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
}
#endif /* DEBUG */
E 33

/*
 * Validate parameters and get old / set new parameters
 * for an integer-valued sysctl function.
 */
sysctl_int(oldp, oldlenp, newp, newlen, valp)
	void *oldp;
D 31
	u_int *oldlenp;
E 31
I 31
	size_t *oldlenp;
E 31
	void *newp;
D 31
	u_int newlen;
E 31
I 31
	size_t newlen;
E 31
	int *valp;
{
	int error = 0;

	if (oldp && *oldlenp < sizeof(int))
		return (ENOMEM);
	if (newp && newlen != sizeof(int))
		return (EINVAL);
	*oldlenp = sizeof(int);
	if (oldp)
		error = copyout(valp, oldp, sizeof(int));
	if (error == 0 && newp)
		error = copyin(newp, valp, sizeof(int));
E 26
	return (error);
E 10
E 4
}

I 26
/*
 * As above, but read-only.
 */
sysctl_rdint(oldp, oldlenp, newp, val)
	void *oldp;
D 31
	u_int *oldlenp;
E 31
I 31
	size_t *oldlenp;
E 31
	void *newp;
	int val;
{
	int error = 0;

	if (oldp && *oldlenp < sizeof(int))
		return (ENOMEM);
	if (newp)
		return (EPERM);
	*oldlenp = sizeof(int);
	if (oldp)
		error = copyout((caddr_t)&val, oldp, sizeof(int));
	return (error);
}

/*
 * Validate parameters and get old / set new parameters
 * for a string-valued sysctl function.
 */
sysctl_string(oldp, oldlenp, newp, newlen, str, maxlen)
	void *oldp;
D 31
	u_int *oldlenp;
E 31
I 31
	size_t *oldlenp;
E 31
	void *newp;
D 31
	u_int newlen;
E 31
I 31
	size_t newlen;
E 31
	char *str;
	int maxlen;
{
	int len, error = 0;

	len = strlen(str) + 1;
	if (oldp && *oldlenp < len)
		return (ENOMEM);
	if (newp && newlen >= maxlen)
		return (EINVAL);
D 28
	*oldlenp = len;
	if (oldp)
E 28
I 28
	if (oldp) {
		*oldlenp = len;
E 28
		error = copyout(str, oldp, len);
I 28
	}
E 28
	if (error == 0 && newp) {
		error = copyin(newp, str, newlen);
		str[newlen] = 0;
	}
	return (error);
}

/*
 * As above, but read-only.
 */
sysctl_rdstring(oldp, oldlenp, newp, str)
	void *oldp;
D 31
	u_int *oldlenp;
E 31
I 31
	size_t *oldlenp;
E 31
	void *newp;
	char *str;
{
	int len, error = 0;

	len = strlen(str) + 1;
	if (oldp && *oldlenp < len)
		return (ENOMEM);
	if (newp)
		return (EPERM);
	*oldlenp = len;
	if (oldp)
		error = copyout(str, oldp, len);
	return (error);
}

/*
I 34
 * Validate parameters and get old / set new parameters
 * for a structure oriented sysctl function.
 */
sysctl_struct(oldp, oldlenp, newp, newlen, sp, len)
	void *oldp;
	size_t *oldlenp;
	void *newp;
	size_t newlen;
	void *sp;
	int len;
{
	int error = 0;

	if (oldp && *oldlenp < len)
		return (ENOMEM);
	if (newp && newlen > len)
		return (EINVAL);
	if (oldp) {
		*oldlenp = len;
		error = copyout(sp, oldp, len);
	}
	if (error == 0 && newp)
		error = copyin(newp, sp, len);
	return (error);
}

/*
E 34
 * Validate parameters and get old parameters
 * for a structure oriented sysctl function.
 */
sysctl_rdstruct(oldp, oldlenp, newp, sp, len)
	void *oldp;
D 31
	u_int *oldlenp;
	void *newp;
	void *sp;
E 31
I 31
	size_t *oldlenp;
	void *newp, *sp;
E 31
	int len;
{
	int error = 0;

	if (oldp && *oldlenp < len)
		return (ENOMEM);
	if (newp)
		return (EPERM);
	*oldlenp = len;
	if (oldp)
		error = copyout(sp, oldp, len);
	return (error);
}

/*
 * Get file structures.
 */
sysctl_file(where, sizep)
	char *where;
D 31
	int *sizep;
E 31
I 31
	size_t *sizep;
E 31
{
	int buflen, error;
	struct file *fp;
	char *start = where;

	buflen = *sizep;
	if (where == NULL) {
		/*
		 * overestimate by 10 files
		 */
		*sizep = sizeof(filehead) + (nfiles + 10) * sizeof(struct file);
		return (0);
	}

	/*
	 * first copyout filehead
	 */
	if (buflen < sizeof(filehead)) {
		*sizep = 0;
		return (0);
	}
	if (error = copyout((caddr_t)&filehead, where, sizeof(filehead)))
		return (error);
D 51
	buflen += sizeof(filehead);
E 51
I 51
	buflen -= sizeof(filehead);
E 51
	where += sizeof(filehead);

	/*
	 * followed by an array of file structures
	 */
D 52
	for (fp = filehead; fp != NULL; fp = fp->f_filef) {
E 52
I 52
	for (fp = filehead.lh_first; fp != 0; fp = fp->f_list.le_next) {
E 52
		if (buflen < sizeof(struct file)) {
			*sizep = where - start;
			return (ENOMEM);
		}
		if (error = copyout((caddr_t)fp, where, sizeof (struct file)))
			return (error);
		buflen -= sizeof(struct file);
		where += sizeof(struct file);
	}
	*sizep = where - start;
	return (0);
}

E 26
D 34
/* 
 * try over estimating by 5 procs 
E 34
I 34
/*
 * try over estimating by 5 procs
E 34
 */
D 26
#define KINFO_PROCSLOP	(5 * sizeof (struct kinfo_proc))
E 26
I 26
#define KERN_PROCSLOP	(5 * sizeof (struct kinfo_proc))
E 26

D 6
int kinfo_proc_userfailed;
int kinfo_proc_wefailed;

E 6
D 4
kinfo_proc(op, where, asize, arg, awanted)
	char *where;
	int *asize, *awanted;
{
	int	bufsize,	/* max size of users buffer */
		copysize, 	/* size copied */
		needed;	
	int locked;
	int error;

	if (error = kinfo_doprocs(op, NULL, NULL, arg, &needed))
		return (error);
	if (where == NULL || asize == NULL) {
		*awanted = needed;
		return (0);
	}
	if (error = copyin((caddr_t)asize, (caddr_t)&bufsize, sizeof (bufsize)))
		return (error);
	needed += KINFO_PROCSLOP;
	locked = copysize = MIN(needed, bufsize);
	if (!useracc(where, copysize, B_WRITE))
		return (EFAULT);
	/*
	 * lock down target pages - NEED DEADLOCK AVOIDANCE
	 */
	if (copysize > ((int)ptob(freemem) - (20 * 1024))) 	/* XXX */
		return (ENOMEM);
	vslock(where, copysize);
	error = kinfo_doprocs(op, where, &copysize, arg, &needed);
	vsunlock(where, locked, B_WRITE);
	if (error)
		return (error);
	*awanted = needed;
	if (error = copyout((caddr_t)&copysize, (caddr_t)asize,
	    sizeof (copysize)))
		return (error);
	
	return (0);
}

E 4
D 5
kinfo_doprocs(op, where, acopysize, arg, aneeded)
E 5
I 5
D 26
kinfo_doproc(op, where, acopysize, arg, aneeded)
I 20
	int op;
E 26
I 26
sysctl_doproc(name, namelen, where, sizep)
	int *name;
D 31
	int namelen;
E 31
I 31
	u_int namelen;
E 31
E 26
E 20
E 5
	char *where;
D 20
	int *acopysize, *aneeded;
E 20
I 20
D 26
	int *acopysize, arg, *aneeded;
E 26
I 26
D 31
	int *sizep;
E 31
I 31
	size_t *sizep;
E 31
E 26
E 20
{
	register struct proc *p;
D 9
	register caddr_t dp = (caddr_t)where;
E 9
I 9
	register struct kinfo_proc *dp = (struct kinfo_proc *)where;
E 9
D 26
	register needed = 0;
D 20
	int buflen;
E 20
I 20
	int buflen = where != NULL ? *acopysize : 0;
E 26
I 26
	register int needed = 0;
	int buflen = where != NULL ? *sizep : 0;
E 26
E 20
	int doingzomb;
D 3
	struct {
		struct	proc *paddr;
		struct	session *session;
		pid_t	pgid;
		short	jobc;
		dev_t	ttydev;
		pid_t	ttypgid;
		struct	session *ttysession;
	} extra;
E 3
I 3
	struct eproc eproc;
E 3
D 9
	struct tty *tp;
E 9
	int error = 0;

I 26
D 41
	if (namelen != 2)
E 41
I 41
	if (namelen != 2 && !(namelen == 1 && name[0] == KERN_PROC_ALL))
E 41
		return (EINVAL);
E 26
D 20
	if (where != NULL)
		buflen = *acopysize;

E 20
D 23
	p = allproc;
E 23
I 23
D 52
	p = (struct proc *)allproc;
E 52
I 52
	p = allproc.lh_first;
E 52
E 23
	doingzomb = 0;
again:
D 49
	for (; p != NULL; p = p->p_nxt) {
E 49
I 49
D 52
	for (; p != NULL; p = p->p_next) {
E 52
I 52
	for (; p != 0; p = p->p_list.le_next) {
E 52
E 49
I 22
		/*
		 * Skip embryonic processes.
		 */
		if (p->p_stat == SIDL)
			continue;
E 22
D 34
		/* 
E 34
I 34
		/*
E 34
		 * TODO - make more efficient (see notes below).
D 34
		 * do by session. 
E 34
I 34
		 * do by session.
E 34
		 */
D 26
		switch (ki_op(op)) {
E 26
I 26
		switch (name[0]) {
E 26

D 26
		case KINFO_PROC_PID:
E 26
I 26
		case KERN_PROC_PID:
E 26
			/* could do this with just a lookup */
D 26
			if (p->p_pid != (pid_t)arg)
E 26
I 26
			if (p->p_pid != (pid_t)name[1])
E 26
				continue;
			break;

D 26
		case KINFO_PROC_PGRP:
E 26
I 26
		case KERN_PROC_PGRP:
E 26
			/* could do this by traversing pgrp */
D 26
			if (p->p_pgrp->pg_id != (pid_t)arg)
E 26
I 26
			if (p->p_pgrp->pg_id != (pid_t)name[1])
E 26
				continue;
			break;

D 26
		case KINFO_PROC_TTY:
E 26
I 26
		case KERN_PROC_TTY:
E 26
D 34
			if ((p->p_flag&SCTTY) == 0 || 
E 34
I 34
D 49
			if ((p->p_flag&SCTTY) == 0 ||
E 49
I 49
			if ((p->p_flag & P_CONTROLT) == 0 ||
E 49
E 34
			    p->p_session->s_ttyp == NULL ||
D 26
			    p->p_session->s_ttyp->t_dev != (dev_t)arg)
E 26
I 26
			    p->p_session->s_ttyp->t_dev != (dev_t)name[1])
E 26
				continue;
			break;

D 26
		case KINFO_PROC_UID:
D 13
			if (p->p_uid != (uid_t)arg)
E 13
I 13
			if (p->p_ucred->cr_uid != (uid_t)arg)
E 26
I 26
		case KERN_PROC_UID:
			if (p->p_ucred->cr_uid != (uid_t)name[1])
E 26
E 13
				continue;
			break;

D 26
		case KINFO_PROC_RUID:
D 13
			if (p->p_ruid != (uid_t)arg)
E 13
I 13
			if (p->p_cred->p_ruid != (uid_t)arg)
E 26
I 26
		case KERN_PROC_RUID:
			if (p->p_cred->p_ruid != (uid_t)name[1])
E 26
E 13
				continue;
			break;
		}
D 20
		if (where != NULL && buflen >= sizeof (struct kinfo_proc)) {
E 20
I 20
D 26
		if (buflen >= sizeof (struct kinfo_proc)) {
E 26
I 26
		if (buflen >= sizeof(struct kinfo_proc)) {
E 26
E 20
I 5
D 12
			register struct text *txt;
E 12
I 9
D 14
			register struct tty *tp;
E 9

E 14
I 14
			fill_eproc(p, &eproc);
E 14
E 5
D 9
			if (error = copyout((caddr_t)p, dp, 
E 9
I 9
D 34
			if (error = copyout((caddr_t)p, &dp->kp_proc, 
E 34
I 34
			if (error = copyout((caddr_t)p, &dp->kp_proc,
E 34
E 9
D 26
			    sizeof (struct proc)))
E 26
I 26
			    sizeof(struct proc)))
E 26
				return (error);
D 9
			dp += sizeof (struct proc);
I 6
			/*
			 *	XXX NEED ALLIGNMENT
			 */
E 9
E 6
D 3
			extra.paddr = p;
			extra.session = p->p_pgrp->pg_session;
			extra.pgid = p->p_pgrp->pg_id;
			extra.jobc = p->p_pgrp->pg_jobc;
E 3
I 3
D 5
			eproc.kp_paddr = p;
			eproc.kp_sess = p->p_pgrp->pg_session;
			eproc.kp_pgid = p->p_pgrp->pg_id;
			eproc.kp_jobc = p->p_pgrp->pg_jobc;
E 5
I 5
D 14
			eproc.e_paddr = p;
			eproc.e_sess = p->p_pgrp->pg_session;
I 13
			eproc.e_pcred = *p->p_cred;
			eproc.e_ucred = *p->p_ucred;
			eproc.e_vm = *p->p_vmspace;
E 13
			eproc.e_pgid = p->p_pgrp->pg_id;
			eproc.e_jobc = p->p_pgrp->pg_jobc;
E 5
E 3
D 7
			tp = p->p_pgrp->pg_session->s_ttyp;
			if ((p->p_flag&SCTTY) && tp != NULL) {
E 7
I 7
D 9
			if (tp = p->p_pgrp->pg_session->s_ttyp) {
				/* up to caller to check for SCTTY */
E 9
I 9
			if ((p->p_flag&SCTTY) && 
			     (tp = eproc.e_sess->s_ttyp)) {
E 9
E 7
D 3
				extra.ttydev = tp->t_dev;
				extra.ttypgid = tp->t_pgrp ? 
E 3
I 3
D 5
				eproc.kp_tdev = tp->t_dev;
				eproc.kp_tpgid = tp->t_pgrp ? 
E 5
I 5
				eproc.e_tdev = tp->t_dev;
				eproc.e_tpgid = tp->t_pgrp ? 
E 5
E 3
					tp->t_pgrp->pg_id : -1;
D 3
				extra.ttysession = tp->t_session;
E 3
I 3
D 5
				eproc.kp_tsess = tp->t_session;
E 5
I 5
				eproc.e_tsess = tp->t_session;
E 5
E 3
			} else
D 3
				extra.ttydev = NODEV;
			if (error = copyout((caddr_t)&extra, dp, 
			    sizeof (extra)))
E 3
I 3
D 5
				eproc.kp_tdev = NODEV;
E 5
I 5
				eproc.e_tdev = NODEV;
I 9
			eproc.e_flag = eproc.e_sess->s_ttyvp ? EPROC_CTTY : 0;
			if (SESS_LEADER(p))
				eproc.e_flag |= EPROC_SLEADER;
E 9
			if (p->p_wmesg)
				strncpy(eproc.e_wmesg, p->p_wmesg, WMESGLEN);
D 12
			if (txt = p->p_textp) {
				eproc.e_xsize = txt->x_size;
				eproc.e_xrssize = txt->x_rssize;
				eproc.e_xccount = txt->x_ccount;
				eproc.e_xswrss = txt->x_swrss;
			} else {
				eproc.e_xsize = eproc.e_xrssize =
				  eproc.e_xccount =  eproc.e_xswrss = 0;
			}
E 12
I 12
			eproc.e_xsize = eproc.e_xrssize = 0;
			eproc.e_xccount =  eproc.e_xswrss = 0;
E 14
E 12
E 5
D 9
			if (error = copyout((caddr_t)&eproc, dp, 
E 9
I 9
D 34
			if (error = copyout((caddr_t)&eproc, &dp->kp_eproc, 
E 34
I 34
			if (error = copyout((caddr_t)&eproc, &dp->kp_eproc,
E 34
E 9
D 26
			    sizeof (eproc)))
E 26
I 26
			    sizeof(eproc)))
E 26
E 3
				return (error);
D 3
			dp += sizeof (extra);
E 3
I 3
D 9
			dp += sizeof (eproc);
E 9
I 9
			dp++;
E 9
E 3
D 26
			buflen -= sizeof (struct kinfo_proc);
E 26
I 26
			buflen -= sizeof(struct kinfo_proc);
E 26
		}
D 26
		needed += sizeof (struct kinfo_proc);
E 26
I 26
		needed += sizeof(struct kinfo_proc);
E 26
	}
	if (doingzomb == 0) {
D 52
		p = zombproc;
E 52
I 52
		p = zombproc.lh_first;
E 52
		doingzomb++;
		goto again;
	}
D 26
	if (where != NULL)
D 9
		*acopysize = dp - where;
E 9
I 9
		*acopysize = (caddr_t)dp - where;
E 9
I 4
	else
		needed += KINFO_PROCSLOP;
E 4
	*aneeded = needed;

E 26
I 26
	if (where != NULL) {
		*sizep = (caddr_t)dp - where;
		if (needed > *sizep)
			return (ENOMEM);
	} else {
		needed += KERN_PROCSLOP;
		*sizep = needed;
	}
E 26
	return (0);
I 14
}

/*
 * Fill in an eproc structure for the specified process.
 */
void
fill_eproc(p, ep)
	register struct proc *p;
	register struct eproc *ep;
{
	register struct tty *tp;

	ep->e_paddr = p;
	ep->e_sess = p->p_pgrp->pg_session;
	ep->e_pcred = *p->p_cred;
	ep->e_ucred = *p->p_ucred;
D 20
	ep->e_vm = *p->p_vmspace;
E 20
I 20
	if (p->p_stat == SIDL || p->p_stat == SZOMB) {
		ep->e_vm.vm_rssize = 0;
		ep->e_vm.vm_tsize = 0;
		ep->e_vm.vm_dsize = 0;
		ep->e_vm.vm_ssize = 0;
#ifndef sparc
		/* ep->e_vm.vm_pmap = XXX; */
#endif
	} else {
		register struct vmspace *vm = p->p_vmspace;

I 50
#ifdef pmap_resident_count
		ep->e_vm.vm_rssize = pmap_resident_count(&vm->vm_pmap); /*XXX*/
#else
E 50
		ep->e_vm.vm_rssize = vm->vm_rssize;
I 50
#endif
E 50
		ep->e_vm.vm_tsize = vm->vm_tsize;
		ep->e_vm.vm_dsize = vm->vm_dsize;
		ep->e_vm.vm_ssize = vm->vm_ssize;
#ifndef sparc
		ep->e_vm.vm_pmap = vm->vm_pmap;
#endif
	}
E 20
D 15
	ep->e_ppid = p->p_pptr->p_pid;
E 15
I 15
	if (p->p_pptr)
		ep->e_ppid = p->p_pptr->p_pid;
	else
		ep->e_ppid = 0;
E 15
	ep->e_pgid = p->p_pgrp->pg_id;
	ep->e_jobc = p->p_pgrp->pg_jobc;
D 34
	if ((p->p_flag&SCTTY) && 
E 34
I 34
D 49
	if ((p->p_flag&SCTTY) &&
E 49
I 49
	if ((p->p_flag & P_CONTROLT) &&
E 49
E 34
	     (tp = ep->e_sess->s_ttyp)) {
		ep->e_tdev = tp->t_dev;
D 16
		ep->e_tpgid = tp->t_pgrp ? tp->t_pgrp->pg_id : -1;
E 16
I 16
		ep->e_tpgid = tp->t_pgrp ? tp->t_pgrp->pg_id : NO_PID;
E 16
		ep->e_tsess = tp->t_session;
	} else
		ep->e_tdev = NODEV;
	ep->e_flag = ep->e_sess->s_ttyvp ? EPROC_CTTY : 0;
	if (SESS_LEADER(p))
		ep->e_flag |= EPROC_SLEADER;
	if (p->p_wmesg)
		strncpy(ep->e_wmesg, p->p_wmesg, WMESGLEN);
	ep->e_xsize = ep->e_xrssize = 0;
	ep->e_xccount = ep->e_xswrss = 0;
I 17
}

D 26
/*
 * Get file structures.
 */
kinfo_file(op, where, acopysize, arg, aneeded)
I 20
	int op;
E 20
	register char *where;
D 20
	int *acopysize, *aneeded;
E 20
I 20
	int *acopysize, arg, *aneeded;
E 26
I 26
#ifdef COMPAT_43
D 27
#include <sys/kinfo.h>
E 27
#include <sys/socket.h>
I 27
#define	KINFO_PROC		(0<<8)
#define	KINFO_RT		(1<<8)
#define	KINFO_VNODE		(2<<8)
#define	KINFO_FILE		(3<<8)
#define	KINFO_METER		(4<<8)
#define	KINFO_LOADAVG		(5<<8)
#define	KINFO_CLOCKRATE		(6<<8)
E 27

D 54
struct getkerninfo_args {
	int	op;
	char	*where;
	int	*size;
	int	arg;
};

D 32
getkerninfo(p, uap, retval)
E 32
I 32
ogetkerninfo(p, uap, retval)
E 54
I 54
compat_43_getkerninfo(p, uap, retval)
E 54
E 32
	struct proc *p;
D 54
	register struct getkerninfo_args *uap;
	int *retval;
E 54
I 54
	register struct compat_43_getkerninfo_args /* {
		syscallarg(int) op;
		syscallarg(char *) where;
		syscallarg(int *) size;
		syscallarg(int) arg;
	} */ *uap;
	register_t *retval;
E 54
E 26
E 20
{
D 26
	int buflen, needed, error;
	struct file *fp;
	char *start = where;
E 26
I 26
	int error, name[5];
D 54
	u_int size;
E 54
I 54
	size_t size;
E 54
E 26

D 26
	if (where == NULL) {
		/*
		 * overestimate by 10 files
		 */
		*aneeded = sizeof (filehead) + 
			(nfiles + 10) * sizeof (struct file);
		return (0);
	}
	buflen = *acopysize;
	needed = 0;
E 26
I 26
D 30
	if (error = copyin((caddr_t)uap->size, (caddr_t)&size, sizeof(size)))
E 30
I 30
D 54
	if (uap->size &&
D 31
	    error = copyin((caddr_t)uap->size, (caddr_t)&size, sizeof(size)))
E 31
I 31
	    (error = copyin((caddr_t)uap->size, (caddr_t)&size, sizeof(size))))
E 54
I 54
	if (SCARG(uap, size) && (error = copyin((caddr_t)SCARG(uap, size),
	    (caddr_t)&size, sizeof(size))))
E 54
E 31
E 30
		return (error);
E 26

D 26
	/*
	 * first copyout filehead
	 */
	if (buflen > sizeof (filehead)) {
		if (error = copyout((caddr_t)&filehead, where,
		    sizeof (filehead)))
			return (error);
		buflen -= sizeof (filehead);
		where += sizeof (filehead);
	}
	needed += sizeof (filehead);
E 26
I 26
D 27
	switch (ki_type(uap->op)) {
E 27
I 27
D 54
	switch (uap->op & 0xff00) {
E 54
I 54
	switch (SCARG(uap, op) & 0xff00) {
E 54
E 27
E 26

D 26
	/*
	 * followed by an array of file structures
	 */
	for (fp = filehead; fp != NULL; fp = fp->f_filef) {
		if (buflen > sizeof (struct file)) {
			if (error = copyout((caddr_t)fp, where,
			    sizeof (struct file)))
				return (error);
			buflen -= sizeof (struct file);
			where += sizeof (struct file);
		}
		needed += sizeof (struct file);
	}
	*acopysize = where - start;
	*aneeded = needed;
E 26
I 26
	case KINFO_RT:
		name[0] = PF_ROUTE;
		name[1] = 0;
D 54
		name[2] = (uap->op & 0xff0000) >> 16;
		name[3] = uap->op & 0xff;
		name[4] = uap->arg;
D 29
		error = net_sysctl(name, 5, uap->where, &size, NULL, 0);
E 29
I 29
		error = net_sysctl(name, 5, uap->where, &size, NULL, 0, p);
E 54
I 54
		name[2] = (SCARG(uap, op) & 0xff0000) >> 16;
		name[3] = SCARG(uap, op) & 0xff;
		name[4] = SCARG(uap, arg);
		error =
		    net_sysctl(name, 5, SCARG(uap, where), &size, NULL, 0, p);
E 54
E 29
		break;
E 26

D 26
	return (0);
E 26
I 26
	case KINFO_VNODE:
		name[0] = KERN_VNODE;
D 29
		error = kern_sysctl(name, 1, uap->where, &size, NULL, 0);
E 29
I 29
D 54
		error = kern_sysctl(name, 1, uap->where, &size, NULL, 0, p);
E 54
I 54
		error =
		    kern_sysctl(name, 1, SCARG(uap, where), &size, NULL, 0, p);
E 54
E 29
		break;

	case KINFO_PROC:
		name[0] = KERN_PROC;
D 54
		name[1] = uap->op & 0xff;
		name[2] = uap->arg;
D 29
		error = kern_sysctl(name, 3, uap->where, &size, NULL, 0);
E 29
I 29
		error = kern_sysctl(name, 3, uap->where, &size, NULL, 0, p);
E 54
I 54
		name[1] = SCARG(uap, op) & 0xff;
		name[2] = SCARG(uap, arg);
		error =
		    kern_sysctl(name, 3, SCARG(uap, where), &size, NULL, 0, p);
E 54
E 29
		break;

	case KINFO_FILE:
		name[0] = KERN_FILE;
D 29
		error = kern_sysctl(name, 1, uap->where, &size, NULL, 0);
E 29
I 29
D 54
		error = kern_sysctl(name, 1, uap->where, &size, NULL, 0, p);
E 54
I 54
		error =
		    kern_sysctl(name, 1, SCARG(uap, where), &size, NULL, 0, p);
E 54
E 29
		break;

	case KINFO_METER:
		name[0] = VM_METER;
D 29
		error = vm_sysctl(name, 1, uap->where, &size, NULL, 0);
E 29
I 29
D 54
		error = vm_sysctl(name, 1, uap->where, &size, NULL, 0, p);
E 54
I 54
		error =
		    vm_sysctl(name, 1, SCARG(uap, where), &size, NULL, 0, p);
E 54
E 29
		break;

	case KINFO_LOADAVG:
		name[0] = VM_LOADAVG;
D 29
		error = vm_sysctl(name, 1, uap->where, &size, NULL, 0);
E 29
I 29
D 54
		error = vm_sysctl(name, 1, uap->where, &size, NULL, 0, p);
E 54
I 54
		error =
		    vm_sysctl(name, 1, SCARG(uap, where), &size, NULL, 0, p);
E 54
E 29
		break;

	case KINFO_CLOCKRATE:
		name[0] = KERN_CLOCKRATE;
D 29
		error = kern_sysctl(name, 1, uap->where, &size, NULL, 0);
E 29
I 29
D 54
		error = kern_sysctl(name, 1, uap->where, &size, NULL, 0, p);
E 54
I 54
		error =
		    kern_sysctl(name, 1, SCARG(uap, where), &size, NULL, 0, p);
E 54
E 29
		break;

	default:
D 29
		return (EINVAL);
E 29
I 29
		return (EOPNOTSUPP);
E 29
	}
	if (error)
		return (error);
	*retval = size;
D 30
	return (copyout((caddr_t)&size, (caddr_t)uap->size, sizeof(size)));
E 30
I 30
D 54
	if (uap->size)
		error = copyout((caddr_t)&size, (caddr_t)uap->size,
E 54
I 54
	if (SCARG(uap, size))
		error = copyout((caddr_t)&size, (caddr_t)SCARG(uap, size),
E 54
		    sizeof(size));
	return (error);
E 30
E 26
E 17
E 14
}
I 26
#endif /* COMPAT_43 */
E 26
E 1
