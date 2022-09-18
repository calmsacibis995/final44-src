h37676
s 00003/00003/00446
d D 8.5 95/05/14 00:18:05 mckusick 40 39
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00035/00022/00414
d D 8.4 95/02/14 10:56:20 cgd 39 38
c return types, syscall arg conventions & recording fixes.
e
s 00008/00012/00428
d D 8.3 94/08/22 10:19:59 mckusick 38 37
c use new queue.h data structures
e
s 00002/00002/00438
d D 8.2 93/09/23 15:28:43 bostic 37 36
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00438
d D 8.1 93/06/10 21:57:23 bostic 36 35
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00005/00428
d D 7.22 93/05/27 18:53:21 torek 35 34
c declare all parameters (for gcc -W)
e
s 00008/00008/00425
d D 7.21 92/10/11 10:38:06 bostic 34 33
c make kernel includes standard
e
s 00007/00006/00426
d D 7.20 92/07/10 20:49:48 torek 33 32
c ANSIfy syscall args
e
s 00002/00002/00430
d D 7.19 92/07/07 14:45:51 torek 32 31
c volatile poisoning
e
s 00000/00004/00432
d D 7.18 92/07/03 01:37:35 mckusick 31 30
c delete USES
e
s 00004/00000/00432
d D 7.17 92/05/14 17:32:43 heideman 30 21
c vnode interface conversion
e
s 00004/00000/00432
d R 7.17 92/05/14 15:46:48 heideman 29 21
c vnode interface conversion
e
s 00004/00000/00432
d R 7.17 92/05/14 14:51:40 heideman 28 21
c vnode interface conversion
e
s 00004/00000/00432
d R 7.17 92/05/14 12:55:54 heideman 27 21
c vnode interface conversion
e
s 00004/00000/00432
d R 7.17 92/05/14 11:53:27 heideman 26 21
c vnode interface conversion
e
s 00004/00000/00432
d R 7.17 92/05/14 10:33:35 heideman 25 21
c vnode interface conversion
e
s 00004/00000/00432
d R 7.17 92/05/13 23:12:23 heideman 24 21
c vnode interface conversion
e
s 00004/00000/00432
d R 7.17 92/05/13 18:58:08 heideman 23 21
c vnode interface conversion
e
s 00004/00000/00432
d R 7.17 92/05/13 18:30:19 heideman 22 21
c vnode interface conversion
e
s 00052/00008/00380
d D 7.16 92/03/18 18:19:14 marc 21 20
c add support for context switch tracing
e
s 00004/00003/00384
d D 7.15 91/06/21 10:41:31 mckusick 20 19
c use vn_close rather than vrele after vn_open
e
s 00001/00000/00386
d D 7.14 91/05/28 17:38:55 mckusick 19 18
c vn_open now returns locked, so must unlock when done
e
s 00005/00003/00381
d D 7.13 91/04/15 23:44:55 mckusick 18 17
c mark uses of curproc
e
s 00000/00002/00384
d D 7.12 91/03/25 12:02:42 karels 17 16
c rm user.h; namei.h is in vnode.h
e
s 00023/00023/00363
d D 7.11 91/03/17 15:42:28 karels 16 15
c more-or-less working with new proc & user structs
e
s 00064/00042/00322
d D 7.10 91/02/15 14:07:19 marc 15 14
c add permission checks to allow regular users to run ktrace
e
s 00001/00011/00363
d D 7.9 90/06/28 21:19:59 bostic 14 13
c new copyright notice
e
s 00006/00006/00368
d D 7.8 90/06/28 17:10:31 karels 13 12
c RETURN => return, remove syscontext.h
e
s 00001/00001/00373
d D 7.7 90/06/28 15:18:45 marc 12 11
c disable general use until security checks in place */
e
s 00029/00022/00345
d D 7.6 90/06/22 17:17:53 mckusick 11 10
c new system call convention
e
s 00015/00002/00352
d D 7.5 90/05/10 18:19:48 mckusick 10 9
c lint; stop tracing when write error encountered
e
s 00000/00001/00354
d D 7.4 90/05/10 13:14:22 mckusick 9 8
c no more u_eosys
e
s 00040/00021/00315
d D 7.3 90/04/05 14:46:28 marc 8 7
c u_comm->p_comm, trace signals, minor cleanups, make DESCEND flag on  op, make inherit flag high bit in traceflag
e
s 00004/00002/00332
d D 7.2 89/11/22 17:59:47 mckusick 7 6
c have to pass locked vnode to VOP_WRITE; no longer takes pointer to offset
e
s 00000/00000/00334
d D 7.1 89/09/04 15:12:31 karels 6 5
c rev 7
e
s 00001/00002/00333
d D 1.5 89/07/05 19:23:23 marc 5 4
c add missing bump to reference count
e
s 00059/00100/00276
d D 1.4 89/05/09 17:02:18 mckusick 4 3
c merge in vnodes
e
s 00076/00023/00300
d D 1.3 89/05/01 23:10:53 marc 3 2
c use microtime, be less paranoid about errors, add genio tracing code
e
s 00001/00003/00303
d D 1.2 89/04/26 19:53:53 mckusick 2 1
c use new form of suser()
e
s 00306/00000/00000
d D 1.1 88/12/14 02:58:21 marc 1 0
c date and time created 88/12/14 02:58:21 by marc
e
u
U
t
T
I 1
/*
D 36
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 36
I 36
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 36
 *
D 14
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
 *
 *	%W% (Berkeley) %G%
 */

#ifdef KTRACE

D 34
#include "param.h"
D 4
#include "systm.h"
#include "dir.h"
E 4
D 11
#include "user.h"
E 11
I 11
D 13
#include "syscontext.h"
E 13
I 13
D 16
#include "user.h"
E 16
I 16
D 17
#include "namei.h"
E 17
E 16
E 13
E 11
D 4
#include "assym.s"
E 4
#include "proc.h"
D 4
#include "seg.h"
#include "acct.h"
#include "fs.h"
#include "inode.h"
#include "syslog.h"
#include "kernel.h"
E 4
I 4
#include "file.h"
I 18
#include "namei.h"
E 18
#include "vnode.h"
E 4
#include "ktrace.h"
#include "malloc.h"
I 15
#include "syslog.h"
E 34
I 34
#include <sys/param.h>
I 39
#include <sys/systm.h>
E 39
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/ktrace.h>
#include <sys/malloc.h>
#include <sys/syslog.h>
E 34
I 16
D 17
#include "user.h"		/* XXX for curproc */
E 17
E 16
E 15

I 39
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 39
D 3
#include "../sys/syscalls.c"
E 3
I 3
D 16
#include "syscalls.c"
E 3

extern int nsysent;
extern char *syscallnames[];

E 16
I 3
D 12
int ktrace_nocheck = 1;
E 12
I 12
D 15
int ktrace_nocheck = 0;	/* set to 1 when security checks in place */
E 12

E 15
E 3
struct ktr_header *
ktrgetheader(type)
I 35
	int type;
E 35
{
	register struct ktr_header *kth;
I 16
D 18
	struct proc *p = curproc;
E 18
I 18
	struct proc *p = curproc;	/* XXX */
E 18
E 16

	MALLOC(kth, struct ktr_header *, sizeof (struct ktr_header), 
		M_TEMP, M_WAITOK);
D 4
	if (kth == NULL)
		return (NULL);
E 4
	kth->ktr_type = type;
D 3
	kth->ktr_time = time;
E 3
I 3
	microtime(&kth->ktr_time);
E 3
D 16
	kth->ktr_pid = u.u_procp->p_pid;
D 8
	bcopy(u.u_comm, kth->ktr_comm, MAXCOMLEN);
E 8
I 8
	bcopy(u.u_procp->p_comm, kth->ktr_comm, MAXCOMLEN);
E 16
I 16
	kth->ktr_pid = p->p_pid;
	bcopy(p->p_comm, kth->ktr_comm, MAXCOMLEN);
E 16
E 8
D 4

I 3
	if (kth == NULL)
		printf("ktrgetheader: can't malloc header for %d\n", type);
E 4
E 3
	return (kth);
}

D 4
ktrsyscall(ip, code, narg)
	struct inode *ip;
E 4
I 4
D 11
ktrsyscall(vp, code, narg)
E 11
I 11
D 39
ktrsyscall(vp, code, narg, args)
E 39
I 39
void
ktrsyscall(vp, code, argsize, args)
E 39
E 11
	struct vnode *vp;
I 11
D 39
	int code, narg, args[];
E 39
I 39
	int code, argsize;
	register_t args[];
E 39
E 11
E 4
{
D 21
	struct	ktr_header *kth = ktrgetheader(KTR_SYSCALL);
E 21
I 21
	struct	ktr_header *kth;
E 21
	struct	ktr_syscall *ktp;
D 39
	register len = sizeof(struct ktr_syscall) + (narg * sizeof(int));
E 39
I 39
	register len = sizeof(struct ktr_syscall) + argsize;
E 39
I 21
	struct proc *p = curproc;	/* XXX */
E 21
D 39
	int 	*argp, i;
E 39
I 39
	register_t *argp;
	int i;
E 39

I 21
	p->p_traceflag |= KTRFAC_ACTIVE;
	kth = ktrgetheader(KTR_SYSCALL);
E 21
D 3
	if (kth == NULL) {
		printf("lost syscall trace - no header\n");	/* DEBUG */
E 3
I 3
D 15
	if (kth == NULL)
E 3
		return;
E 15
D 3
	}
E 3
	MALLOC(ktp, struct ktr_syscall *, len, M_TEMP, M_WAITOK);
D 4
	if (ktp == NULL) {
		printf("lost syscall trace - no buffer\n");	/* DEBUG */
		FREE(kth, M_TEMP);
		return;
	}
E 4
	ktp->ktr_code = code;
D 39
	ktp->ktr_narg = narg;
	argp = (int *)((char *)ktp + sizeof(struct ktr_syscall));
	for (i = 0; i < narg; i++)
E 39
I 39
	ktp->ktr_argsize = argsize;
	argp = (register_t *)((char *)ktp + sizeof(struct ktr_syscall));
	for (i = 0; i < (argsize / sizeof *argp); i++)
E 39
D 11
		*argp++ = u.u_arg[i];
E 11
I 11
		*argp++ = args[i];
E 11
	kth->ktr_buf = (caddr_t)ktp;
	kth->ktr_len = len;
D 4
	ktrwrite(ip, kth);
E 4
I 4
	ktrwrite(vp, kth);
E 4
	FREE(ktp, M_TEMP);
	FREE(kth, M_TEMP);
I 21
	p->p_traceflag &= ~KTRFAC_ACTIVE;
E 21
}

I 39
void
E 39
D 4
ktrsysret(ip, code)
	struct inode *ip;
E 4
I 4
D 11
ktrsysret(vp, code)
E 11
I 11
ktrsysret(vp, code, error, retval)
E 11
	struct vnode *vp;
I 11
	int code, error, retval;
E 11
E 4
{
D 21
	struct ktr_header *kth = ktrgetheader(KTR_SYSRET);
E 21
I 21
	struct ktr_header *kth;
E 21
D 8
	struct ktr_sysret *ktp;
E 8
I 8
	struct ktr_sysret ktp;
I 21
	struct proc *p = curproc;	/* XXX */
E 21
E 8

I 21
	p->p_traceflag |= KTRFAC_ACTIVE;
	kth = ktrgetheader(KTR_SYSRET);
E 21
D 3
	if (kth == NULL) {
		printf("lost syscall ret - no header\n");	/* DEBUG */
E 3
I 3
D 15
	if (kth == NULL)
E 3
		return;
E 15
D 3
	}
E 3
D 8
	MALLOC(ktp, struct ktr_sysret *, sizeof(struct ktr_sysret),
		M_TEMP , M_WAITOK);
D 4
	if (ktp == NULL) {
		printf("lost syscall ret - no buffer\n");	/* DEBUG */
		FREE(kth, M_TEMP);
		return;
	}
E 4
	ktp->ktr_code = code;
	ktp->ktr_eosys = u.u_eosys;
	ktp->ktr_error = u.u_error;
	ktp->ktr_retval = u.u_r.r_val1;		/* what about val2 ? */
E 8
I 8
	ktp.ktr_code = code;
D 9
	ktp.ktr_eosys = u.u_eosys;
E 9
D 11
	ktp.ktr_error = u.u_error;
	ktp.ktr_retval = u.u_r.r_val1;		/* what about val2 ? */
E 11
I 11
	ktp.ktr_error = error;
	ktp.ktr_retval = retval;		/* what about val2 ? */
E 11
E 8

D 8
	kth->ktr_buf = (caddr_t)ktp;
E 8
I 8
	kth->ktr_buf = (caddr_t)&ktp;
E 8
	kth->ktr_len = sizeof(struct ktr_sysret);

D 4
	ktrwrite(ip, kth);
E 4
I 4
	ktrwrite(vp, kth);
E 4
D 8
	FREE(ktp, M_TEMP);
E 8
	FREE(kth, M_TEMP);
I 21
	p->p_traceflag &= ~KTRFAC_ACTIVE;
E 21
}

I 39
void
E 39
D 4
ktrnamei(ip, path)
	struct inode *ip;
E 4
I 4
ktrnamei(vp, path)
	struct vnode *vp;
E 4
	char *path;
{
D 21
	struct ktr_header *kth = ktrgetheader(KTR_NAMEI);
E 21
I 21
	struct ktr_header *kth;
	struct proc *p = curproc;	/* XXX */
E 21

I 21
	p->p_traceflag |= KTRFAC_ACTIVE;
	kth = ktrgetheader(KTR_NAMEI);
E 21
D 3
	if (kth == NULL) {
		printf("lost namei - no header\n");	/* DEBUG */
E 3
I 3
D 15
	if (kth == NULL)
E 3
		return;
E 15
D 3
	}
E 3
	kth->ktr_len = strlen(path);
	kth->ktr_buf = path;

D 4
	ktrwrite(ip, kth);
E 4
I 4
	ktrwrite(vp, kth);
E 4
	FREE(kth, M_TEMP);
I 21
	p->p_traceflag &= ~KTRFAC_ACTIVE;
E 21
}

I 39
void
E 39
I 3
D 4
ktrgenio(ip, fd, rw, iov, len)
	struct inode *ip;
E 4
I 4
D 11
ktrgenio(vp, fd, rw, iov, len)
E 11
I 11
ktrgenio(vp, fd, rw, iov, len, error)
E 11
	struct vnode *vp;
I 11
	int fd;
E 11
E 4
	enum uio_rw rw;
	register struct iovec *iov;
I 35
	int len, error;
E 35
{
D 21
	struct ktr_header *kth = ktrgetheader(KTR_GENIO);
E 21
I 21
	struct ktr_header *kth;
E 21
	register struct ktr_genio *ktp;
	register caddr_t cp;
	register int resid = len, cnt;
I 21
	struct proc *p = curproc;	/* XXX */
E 21
	
D 11
	if (kth == NULL || u.u_error)
E 11
I 11
D 15
	if (kth == NULL || error)
E 15
I 15
	if (error)
E 15
E 11
		return;
I 21
	p->p_traceflag |= KTRFAC_ACTIVE;
	kth = ktrgetheader(KTR_GENIO);
E 21
	MALLOC(ktp, struct ktr_genio *, sizeof(struct ktr_genio) + len,
		M_TEMP, M_WAITOK);
D 4
	if (ktp == NULL) {
		printf("lost ktr_genio data buffer\n");
		FREE(kth, M_TEMP);
		return;
	}
E 4
	ktp->ktr_fd = fd;
	ktp->ktr_rw = rw;
	cp = (caddr_t)((char *)ktp + sizeof (struct ktr_genio));
	while (resid > 0) {
		if ((cnt = iov->iov_len) > resid)
			cnt = resid;
D 10
		if (copyin(iov->iov_base, cp, cnt))
E 10
I 10
		if (copyin(iov->iov_base, cp, (unsigned)cnt))
E 10
			goto done;
		cp += cnt;
		resid -= cnt;
		iov++;
	}
	kth->ktr_buf = (caddr_t)ktp;
	kth->ktr_len = sizeof (struct ktr_genio) + len;

D 4
	ktrwrite(ip, kth);
E 4
I 4
	ktrwrite(vp, kth);
E 4
done:
	FREE(kth, M_TEMP);
	FREE(ktp, M_TEMP);
I 21
	p->p_traceflag &= ~KTRFAC_ACTIVE;
E 21
}

I 39
void
E 39
I 8
ktrpsig(vp, sig, action, mask, code)
D 35
	struct	vnode *vp;
	sig_t	action;
E 35
I 35
	struct vnode *vp;
	int sig;
	sig_t action;
	int mask, code;
E 35
{
D 21
	struct ktr_header *kth = ktrgetheader(KTR_PSIG);
E 21
I 21
	struct ktr_header *kth;
E 21
	struct ktr_psig	kp;
I 21
	struct proc *p = curproc;	/* XXX */
E 21

I 21
	p->p_traceflag |= KTRFAC_ACTIVE;
	kth = ktrgetheader(KTR_PSIG);
E 21
D 15
	if (kth == NULL)
		return;
E 15
	kp.signo = (char)sig;
	kp.action = action;
	kp.mask = mask;
	kp.code = code;
	kth->ktr_buf = (caddr_t)&kp;
	kth->ktr_len = sizeof (struct ktr_psig);

	ktrwrite(vp, kth);
	FREE(kth, M_TEMP);
I 21
	p->p_traceflag &= ~KTRFAC_ACTIVE;
E 21
}

I 39
void
E 39
I 21
ktrcsw(vp, out, user)
D 35
	struct	vnode *vp;
	int	out, user;
E 35
I 35
	struct vnode *vp;
	int out, user;
E 35
{
	struct ktr_header *kth;
	struct	ktr_csw kc;
	struct proc *p = curproc;	/* XXX */

	p->p_traceflag |= KTRFAC_ACTIVE;
	kth = ktrgetheader(KTR_CSW);
	kc.out = out;
	kc.user = user;
	kth->ktr_buf = (caddr_t)&kc;
	kth->ktr_len = sizeof (struct ktr_csw);

	ktrwrite(vp, kth);
	FREE(kth, M_TEMP);
	p->p_traceflag &= ~KTRFAC_ACTIVE;
}

E 21
/* Interface and common routines */

E 8
E 3
/*
 * ktrace system call
 */
I 33
D 39
struct ktrace_args {
	char	*fname;
	int	ops;
	int	facs;
	int	pid;
};
E 39
E 33
D 11
ktrace()
{
D 4
	register struct inode *ip = NULL;
E 4
	register struct a {
E 11
I 11
/* ARGSUSED */
I 39
int
E 39
ktrace(curp, uap, retval)
	struct proc *curp;
D 33
	register struct args {
E 11
		char	*fname;
		int	ops;
		int	facs;
D 3
		pid_t	pid;
E 3
I 3
		int	pid;
E 3
D 11
	} *uap = (struct a *)u.u_ap;
E 11
I 11
	} *uap;
E 33
I 33
D 39
	register struct ktrace_args *uap;
E 33
	int *retval;
E 39
I 39
	register struct ktrace_args /* {
		syscallarg(char *) fname;
		syscallarg(int) ops;
		syscallarg(int) facs;
		syscallarg(int) pid;
	} */ *uap;
	register_t *retval;
E 39
{
I 30
D 31
	USES_VOP_UNLOCK;
E 31
E 30
E 11
I 4
	register struct vnode *vp = NULL;
E 4
D 16
	register struct nameidata *ndp = &u.u_nd;
E 16
	register struct proc *p;
I 8
D 15
	register ops = KTROP(uap->ops);
E 15
E 8
	struct pgrp *pg;
D 8
	register int ops = uap->ops&0x3;
E 8
D 15
	register int facs = uap->facs;
I 3
	register int ret = 0;
E 15
I 15
D 39
	int facs = uap->facs & ~KTRFAC_ROOT;
	int ops = KTROP(uap->ops);
	int descend = uap->ops & KTRFLAG_DESCEND;
E 39
I 39
	int facs = SCARG(uap, facs) & ~KTRFAC_ROOT;
	int ops = KTROP(SCARG(uap, ops));
	int descend = SCARG(uap, ops) & KTRFLAG_DESCEND;
E 39
	int ret = 0;
E 15
I 11
	int error = 0;
I 16
	struct nameidata nd;
E 16
E 11
E 3

I 21
	curp->p_traceflag |= KTRFAC_ACTIVE;
E 21
D 15
	/*
	 * Until security implications are thought through,
D 3
	 * limit tracing to root.
E 3
I 3
	 * limit tracing to root (unless ktrace_nocheck is set).
E 3
	 */
D 2
	if (!suser()) {
		u.u_error = EACCES;
E 2
I 2
D 11
	if (!ktrace_nocheck && (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 2
		return;
E 11
I 11
	if (!ktrace_nocheck && (error = suser(u.u_cred, &u.u_acflag)))
D 13
		RETURN (error);
E 13
I 13
		return (error);
E 15
E 13
E 11
D 2
	}
E 2
	if (ops != KTROP_CLEAR) {
		/*
		 * an operation which requires a file argument.
		 */
D 4
		ndp->ni_nameiop = LOOKUP | FOLLOW;
E 4
D 16
		ndp->ni_segflg = UIO_USERSPACE;
		ndp->ni_dirp = uap->fname;
D 4
		ip = namei(ndp);
		if (ip == NULL)
E 4
I 4
D 11
		if (u.u_error = vn_open(ndp, FREAD|FWRITE, 0))
E 4
			return;
E 11
I 11
		if (error = vn_open(ndp, FREAD|FWRITE, 0))
E 16
I 16
D 21
		nd.ni_segflg = UIO_USERSPACE;
		nd.ni_dirp = uap->fname;
		if (error = vn_open(&nd, curp, FREAD|FWRITE, 0))
E 21
I 21
D 39
		NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->fname, curp);
E 39
I 39
		NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, fname),
		    curp);
E 39
		if (error = vn_open(&nd, FREAD|FWRITE, 0)) {
			curp->p_traceflag &= ~KTRFAC_ACTIVE;
E 21
E 16
D 13
			RETURN (error);
E 13
I 13
			return (error);
I 21
		}
E 21
E 13
E 11
I 3
D 4
		if (access(ip, IWRITE)) {
			iput(ip);
			return;
		}
E 3
		if ((ip->i_mode&IFMT) != IFREG) {
E 4
I 4
D 16
		vp = ndp->ni_vp;
E 16
I 16
		vp = nd.ni_vp;
I 19
D 40
		VOP_UNLOCK(vp);
E 40
I 40
		VOP_UNLOCK(vp, 0, p);
E 40
E 19
E 16
		if (vp->v_type != VREG) {
E 4
D 11
			u.u_error = EACCES;
E 11
D 4
			iput(ip);
E 4
I 4
D 20
			vrele(vp);
E 20
I 20
			(void) vn_close(vp, FREAD|FWRITE, curp->p_ucred, curp);
I 21
			curp->p_traceflag &= ~KTRFAC_ACTIVE;
E 21
E 20
E 4
D 11
			return;
E 11
I 11
D 13
			RETURN (EACCES);
E 13
I 13
			return (EACCES);
E 13
E 11
		}
D 4
		if (ip->i_fs->fs_ronly) {
			u.u_error = EROFS;
			iput(ip);
			return;
		}
		iunlock(ip);
E 4
	}
	/*
	 * Clear all uses of the tracefile
	 */
	if (ops == KTROP_CLEARFILE) {
D 32
		for (p = allproc; p != NULL; p = p->p_nxt) {
E 32
I 32
D 37
		for (p = (struct proc *)allproc; p != NULL; p = p->p_nxt) {
E 37
I 37
D 38
		for (p = (struct proc *)allproc; p != NULL; p = p->p_next) {
E 38
I 38
		for (p = allproc.lh_first; p != 0; p = p->p_list.le_next) {
E 38
E 37
E 32
D 4
			if (p->p_tracep == ip) {
E 4
I 4
			if (p->p_tracep == vp) {
E 4
D 8
				p->p_flag &= ~SKTR;
E 8
D 15
				p->p_tracep = NULL;
				p->p_traceflag = 0;
D 4
				irele(ip);
E 4
I 4
				vrele(vp);
E 15
I 15
				if (ktrcanset(curp, p)) {
					p->p_tracep = NULL;
					p->p_traceflag = 0;
D 20
					vrele(vp);
E 20
I 20
					(void) vn_close(vp, FREAD|FWRITE,
						p->p_ucred, p);
E 20
				} else
					error = EPERM;
E 15
E 4
			}
		}
		goto done;
	}
D 8

E 8
	/*
D 15
	 * need something to (un)trace
E 15
I 15
	 * need something to (un)trace (XXX - why is this here?)
E 15
	 */
	if (!facs) {
D 11
		u.u_error = EINVAL;
E 11
I 11
		error = EINVAL;
E 11
		goto done;
	}
D 8

E 8
I 8
	/* 
D 15
	 * doit
E 15
I 15
	 * do it
E 15
	 */
E 8
D 39
	if (uap->pid < 0) {
E 39
I 39
	if (SCARG(uap, pid) < 0) {
E 39
I 15
		/*
		 * by process group
		 */
E 15
D 39
		pg = pgfind(-uap->pid);
E 39
I 39
		pg = pgfind(-SCARG(uap, pid));
E 39
		if (pg == NULL) {
D 11
			u.u_error = ESRCH;
E 11
I 11
			error = ESRCH;
E 11
			goto done;
		}
D 38
		for (p = pg->pg_mem; p != NULL; p = p->p_pgrpnxt)
E 38
I 38
		for (p = pg->pg_members.lh_first; p != 0; p = p->p_pglist.le_next)
E 38
D 8
			if (uap->ops&KTROP_INHERITFLAG)
E 8
I 8
D 15
			if (uap->ops&KTRFLAG_DESCEND)
E 8
D 3
				ktrsetchildren(p, ops, facs, ip);
E 3
I 3
D 4
				ret |= ktrsetchildren(p, ops, facs, ip);
E 4
I 4
				ret |= ktrsetchildren(p, ops, facs, vp);
E 15
I 15
			if (descend)
				ret |= ktrsetchildren(curp, p, ops, facs, vp);
E 15
E 4
E 3
			else 
D 3
				ktrops(p, ops, facs, ip);
E 3
I 3
D 4
				ret |= ktrops(p, ops, facs, ip);
E 4
I 4
D 15
				ret |= ktrops(p, ops, facs, vp);
E 15
I 15
				ret |= ktrops(curp, p, ops, facs, vp);
E 15
E 4
E 3
					
	} else {
I 15
		/*
		 * by pid
		 */
E 15
D 39
		p = pfind(uap->pid);
E 39
I 39
		p = pfind(SCARG(uap, pid));
E 39
		if (p == NULL) {
D 11
			u.u_error = ESRCH;
E 11
I 11
			error = ESRCH;
E 11
			goto done;
		}
D 8
		if (uap->ops&KTROP_INHERITFLAG)
E 8
I 8
D 15
		if (ops&KTRFLAG_DESCEND)
E 8
D 3
			ktrsetchildren(p, ops, facs, ip);
E 3
I 3
D 4
			ret |= ktrsetchildren(p, ops, facs, ip);
E 4
I 4
			ret |= ktrsetchildren(p, ops, facs, vp);
E 15
I 15
		if (descend)
			ret |= ktrsetchildren(curp, p, ops, facs, vp);
E 15
E 4
E 3
		else
D 3
			ktrops(p, ops, facs, ip);
E 3
I 3
D 4
			ret |= ktrops(p, ops, facs, ip);
E 4
I 4
D 15
			ret |= ktrops(p, ops, facs, vp);
E 15
I 15
			ret |= ktrops(curp, p, ops, facs, vp);
E 15
E 4
E 3
	}
I 3
	if (!ret)
D 11
		u.u_error = EPERM;
E 11
I 11
		error = EPERM;
E 11
E 3
done:
D 4
	if (ip != NULL)
		irele(ip);
E 4
I 4
	if (vp != NULL)
D 20
		vrele(vp);
E 20
I 20
		(void) vn_close(vp, FWRITE, curp->p_ucred, curp);
I 21
	curp->p_traceflag &= ~KTRFAC_ACTIVE;
E 21
E 20
I 11
D 13
	RETURN (error);
E 13
I 13
	return (error);
E 13
E 11
E 4
}

I 35
int
E 35
D 4
ktrops(p, ops, facs, ip)
E 4
I 4
D 15
ktrops(p, ops, facs, vp)
E 4
	struct proc *p;
E 15
I 15
ktrops(curp, p, ops, facs, vp)
D 35
	struct proc *curp, *p;
E 35
I 35
	struct proc *p, *curp;
	int ops, facs;
E 35
E 15
D 4
	struct inode *ip;
E 4
I 4
	struct vnode *vp;
E 4
{
I 3

D 15
	if (u.u_uid && u.u_uid != p->p_uid)
E 15
I 15
	if (!ktrcanset(curp, p))
E 15
D 13
		return 0;
E 13
I 13
		return (0);
E 13
E 3
	if (ops == KTROP_SET) {
D 4
		if (p->p_tracep != ip) {
E 4
I 4
D 8
		if (p->p_tracep != vp) {
E 8
I 8
		if (p->p_tracep != vp) { 
E 8
E 4
			/*
			 * if trace file already in use, relinquish
			 */
			if (p->p_tracep != NULL)
D 4
				irele(p->p_tracep);
			igrab(ip);
			p->p_tracep = ip;
			iunlock(ip);
E 4
I 4
				vrele(p->p_tracep);
D 5
			if (vp->v_count == 0)
				panic("ktrace: bad vnode");
E 5
I 5
			VREF(vp);
E 5
			p->p_tracep = vp;
E 4
		}
		p->p_traceflag |= facs;
I 15
D 16
		if (curp->p_uid == 0)
E 16
I 16
		if (curp->p_ucred->cr_uid == 0)
E 16
			p->p_traceflag |= KTRFAC_ROOT;
E 15
	} else {	
		/* KTROP_CLEAR */
D 8
		if ((p->p_traceflag &= ~facs) == 0) {
E 8
I 8
D 15
		if (((p->p_traceflag &= ~facs) & ~KTRFAC_INHERIT) == 0) {
E 15
I 15
		if (((p->p_traceflag &= ~facs) & KTRFAC_MASK) == 0) {
E 15
			/* no more tracing */
			p->p_traceflag = 0;
E 8
			if (p->p_tracep != NULL) {
D 4
				irele(p->p_tracep);
E 4
I 4
				vrele(p->p_tracep);
E 4
				p->p_tracep = NULL;
			}
D 3
			p->p_flag &= SKTR;
E 3
I 3
D 8
			p->p_flag &= ~SKTR;
E 8
E 3
		}
	}
I 3

D 15
	return 1;
E 15
I 15
	return (1);
E 15
E 3
}
D 3
		
E 3
I 3

E 3
D 4
ktrsetchildren(top, ops, facs, ip)
E 4
I 4
D 15
ktrsetchildren(top, ops, facs, vp)
E 4
	struct proc *top;
E 15
I 15
ktrsetchildren(curp, top, ops, facs, vp)
	struct proc *curp, *top;
I 35
	int ops, facs;
E 35
E 15
D 4
	struct inode *ip;
E 4
I 4
	struct vnode *vp;
E 4
{
	register struct proc *p;
D 10
	register int ndx;
E 10
I 3
	register int ret = 0;
E 3

	p = top;
	for (;;) {
D 3
		if (ops == KTROP_SET)
E 3
I 3
D 4
		if ((ret |= ktrops(p, ops, facs, ip)) && ops == KTROP_SET)
E 4
I 4
D 8
		if ((ret |= ktrops(p, ops, facs, vp)) && ops == KTROP_SET)
E 4
E 3
			p->p_flag |= SKTR;
E 8
I 8
D 15
		ret |= ktrops(p, ops, facs, vp);
E 15
I 15
		ret |= ktrops(curp, p, ops, facs, vp);
E 15
E 8
D 3
		ktrops(p, ops, facs, ip);
E 3
		/*
		 * If this process has children, descend to them next,
		 * otherwise do any siblings, and if done with this level,
		 * follow back up the tree (but not past top).
		 */
D 38
		if (p->p_cptr)
			p = p->p_cptr;
		else if (p == top)
D 3
			return;
E 3
I 3
D 15
			return ret;
E 15
I 15
			return (ret);
E 15
E 3
		else if (p->p_osptr)
			p = p->p_osptr;
E 38
I 38
		if (p->p_children.lh_first)
			p = p->p_children.lh_first;
E 38
		else for (;;) {
D 38
			p = p->p_pptr;
E 38
			if (p == top)
D 3
				return;
E 3
I 3
D 15
				return ret;
E 15
I 15
				return (ret);
E 15
E 3
D 38
			if (p->p_osptr) {
				p = p->p_osptr;
E 38
I 38
			if (p->p_sibling.le_next) {
				p = p->p_sibling.le_next;
E 38
				break;
			}
I 38
			p = p->p_pptr;
E 38
		}
	}
I 3
	/*NOTREACHED*/
E 3
}

D 4
ktrwrite(ip, kth)
	register struct inode *ip;
	struct ktr_header *kth;
E 4
I 4
ktrwrite(vp, kth)
	struct vnode *vp;
	register struct ktr_header *kth;
E 4
{
I 30
D 31
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
	USES_VOP_WRITE;
E 31
E 30
D 4
	int save = u.u_error;
	int osize;
	
I 3
	if (ip == NULL)
E 4
I 4
	struct uio auio;
	struct iovec aiov[2];
I 10
D 18
	struct proc *p;
E 18
I 18
	register struct proc *p = curproc;	/* XXX */
E 18
E 10
D 7
	int offset, error;
E 7
I 7
	int error;
E 7

	if (vp == NULL)
E 4
		return;
E 3
D 4
	ilock(ip);
	osize = ip->i_size;
	u.u_error = 0;
	u.u_error = rdwri(UIO_WRITE, ip, (caddr_t)kth, 
			sizeof(struct ktr_header), ip->i_size, 1, (int *)0);
	if (u.u_error) {
		itrunc(ip, (u_long)osize);
		goto end;
	}
E 4
I 4
	auio.uio_iov = &aiov[0];
	auio.uio_offset = 0;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_rw = UIO_WRITE;
	aiov[0].iov_base = (caddr_t)kth;
	aiov[0].iov_len = sizeof(struct ktr_header);
	auio.uio_resid = sizeof(struct ktr_header);
	auio.uio_iovcnt = 1;
I 18
	auio.uio_procp = (struct proc *)0;
E 18
E 4
	if (kth->ktr_len > 0) {
D 4
		u.u_error = rdwri(UIO_WRITE, ip, kth->ktr_buf,
			    kth->ktr_len, ip->i_size, 1, (int *)0);
		if (u.u_error)
			itrunc(ip, (u_long)osize);
E 4
I 4
		auio.uio_iovcnt++;
		aiov[1].iov_base = kth->ktr_buf;
		aiov[1].iov_len = kth->ktr_len;
		auio.uio_resid += kth->ktr_len;
E 4
	}
D 4
end:
	u.u_error = save;
	iunlock(ip);
E 4
I 4
D 7
	error = VOP_WRITE(vp, &auio, &offset, IO_UNIT|IO_APPEND, u.u_cred);
E 7
I 7
D 40
	VOP_LOCK(vp);
E 40
I 40
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 40
D 16
	error = VOP_WRITE(vp, &auio, IO_UNIT|IO_APPEND, u.u_cred);
E 16
I 16
D 18
	error = VOP_WRITE(vp, &auio, IO_UNIT|IO_APPEND, curproc->p_ucred);
E 18
I 18
	error = VOP_WRITE(vp, &auio, IO_UNIT|IO_APPEND, p->p_ucred);
E 18
E 16
D 40
	VOP_UNLOCK(vp);
E 40
I 40
	VOP_UNLOCK(vp, 0, p);
E 40
I 10
	if (!error)
		return;
	/*
	 * If error encountered, give up tracing on this vnode.
	 */
D 15
	uprintf("\ntrace write failed with errno %d, tracing stopped\n", error);
E 15
I 15
D 16
	log(LOG_NOTICE, "ktrace write failed, errno %d, tracing stopped\n", error);
E 16
I 16
	log(LOG_NOTICE, "ktrace write failed, errno %d, tracing stopped\n",
	    error);
E 16
E 15
D 32
	for (p = allproc; p != NULL; p = p->p_nxt) {
E 32
I 32
D 37
	for (p = (struct proc *)allproc; p != NULL; p = p->p_nxt) {
E 37
I 37
D 38
	for (p = (struct proc *)allproc; p != NULL; p = p->p_next) {
E 38
I 38
	for (p = allproc.lh_first; p != 0; p = p->p_list.le_next) {
E 38
E 37
E 32
		if (p->p_tracep == vp) {
			p->p_tracep = NULL;
			p->p_traceflag = 0;
			vrele(vp);
		}
	}
E 10
E 7
E 4
}
I 15

/*
 * Return true if caller has permission to set the ktracing state
 * of target.  Essentially, the target can't possess any
 * more permissions than the caller.  KTRFAC_ROOT signifies that
 * root previously set the tracing status on the target process, and 
 * so, only root may further change it.
 *
D 16
 * TODO: check groups  (have to wait till group list is moved
 *       out of u.  use caller effective gid.
E 16
I 16
 * TODO: check groups.  use caller effective gid.
E 16
 */
D 16
ktrcanset(caller, target)
	register struct proc *caller, *target;
E 16
I 16
ktrcanset(callp, targetp)
	struct proc *callp, *targetp;
E 16
{
D 16
	if ((caller->p_uid == target->p_ruid &&
E 16
I 16
	register struct pcred *caller = callp->p_cred;
	register struct pcred *target = targetp->p_cred;

	if ((caller->pc_ucred->cr_uid == target->p_ruid &&
E 16
	     target->p_ruid == target->p_svuid &&
	     caller->p_rgid == target->p_rgid &&	/* XXX */
	     target->p_rgid == target->p_svgid &&
D 16
	     (target->p_traceflag & KTRFAC_ROOT) == 0) ||
	     caller->p_uid == 0)
E 16
I 16
	     (targetp->p_traceflag & KTRFAC_ROOT) == 0) ||
	     caller->pc_ucred->cr_uid == 0)
E 16
		return (1);

	return (0);
}

E 15
D 4

E 4
#endif
E 1
