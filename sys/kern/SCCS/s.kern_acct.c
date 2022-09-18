h02053
s 00001/00001/00223
d D 8.8 95/05/14 00:18:20 mckusick 57 56
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00007/00007/00217
d D 8.7 95/02/14 10:17:46 cgd 56 55
c access syscall arguments in the new fashion.
e
s 00010/00006/00214
d D 8.6 94/12/10 11:25:16 pendry 55 53
c have to protect acct_process from acctwatch closing the vnode
e
s 00009/00005/00215
d R 8.6 94/12/08 22:10:57 mckusick 54 53
c have to protect acct_process from acctwatch closing the vnode
e
s 00001/00001/00219
d D 8.5 94/08/11 00:24:35 mckusick 53 52
c LEASE_CHECK => VOP_LEASE
e
s 00018/00001/00202
d D 8.4 94/06/02 18:30:28 mckusick 52 51
c check for dead vnodes when doing accounting
e
s 00005/00000/00198
d D 8.3 94/01/21 17:17:32 bostic 51 50
c add USL's copyright notice
e
s 00001/00001/00197
d D 8.2 93/09/23 15:25:58 bostic 50 49
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00196
d D 8.1 93/06/14 15:27:05 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00005/00194
d D 7.29 93/06/14 15:27:01 bostic 48 46
c make function call name match system call name
e
s 00002/00002/00197
d R 8.1 93/06/10 21:56:44 bostic 47 46
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00198
d D 7.28 93/04/27 16:11:51 mckusick 46 45
c bug fixes for LEASES from Rick Macklem
e
s 00010/00010/00188
d D 7.27 93/02/22 18:14:30 mckusick 45 44
c cleanups from Jeff Forys
e
s 00014/00014/00184
d D 7.26 92/10/11 10:37:56 bostic 44 43
c make kernel includes standard
e
s 00004/00003/00194
d D 7.25 92/07/10 20:47:23 torek 43 42
c ANSIfy syscall args
e
s 00010/00009/00187
d D 7.24 92/07/08 00:53:57 torek 42 41
c lint; new rusage calculation; fix account watching frequency
e
s 00000/00001/00196
d D 7.23 92/07/02 23:52:14 mckusick 41 40
c delete USES
e
s 00001/00000/00196
d D 7.22 92/05/14 17:31:36 heideman 40 31
c vnode interface conversion
e
s 00001/00000/00196
d R 7.22 92/05/14 15:45:30 heideman 39 31
c vnode interface conversion
e
s 00001/00000/00196
d R 7.22 92/05/14 14:50:41 heideman 38 31
c vnode interface conversion
e
s 00001/00000/00196
d R 7.22 92/05/14 12:54:45 heideman 37 31
c vnode interface conversion
e
s 00001/00000/00196
d R 7.22 92/05/14 11:52:08 heideman 36 31
c vnode interface conversion
e
s 00001/00000/00196
d R 7.22 92/05/14 10:32:19 heideman 35 31
c vnode interface conversion
e
s 00001/00000/00196
d R 7.22 92/05/13 23:11:05 heideman 34 31
c vnode interface conversion
e
s 00001/00000/00196
d R 7.22 92/05/13 18:57:13 heideman 33 31
c vnode interface conversion
e
s 00001/00000/00196
d R 7.22 92/05/13 18:29:16 heideman 32 31
c vnode interface conversion
e
s 00002/00003/00194
d D 7.21 92/02/03 23:31:25 mckusick 31 30
c vn_open no longer takes a proc (now in ndp)
e
s 00005/00005/00192
d D 7.20 91/06/21 10:41:51 mckusick 30 29
c use vn_close rather than vrele after vn_open
e
s 00001/00000/00196
d D 7.19 91/05/28 17:40:15 mckusick 29 28
c vn_open now returns locked, so must unlock when done
e
s 00011/00002/00185
d D 7.18 91/05/11 14:18:02 mckusick 28 27
c fill out comments
e
s 00005/00004/00182
d D 7.17 91/05/09 21:18:14 bostic 27 26
c new copyright; att/bsd/shared
e
s 00005/00004/00181
d D 7.16 91/04/15 23:53:36 mckusick 26 25
c add proc pointers to appropriate VOP and vnode operations
e
s 00016/00017/00169
d D 7.15 91/03/17 15:42:18 karels 25 24
c more-or-less working with new proc & user structs
e
s 00003/00007/00183
d D 7.14 90/08/22 08:30:19 mckusick 24 23
c use vn_open on accounting file to ensure that quotas get set up (from Torek)
e
s 00000/00001/00190
d D 7.13 90/08/01 17:59:56 mckusick 23 22
c eliminate bogus scaling (from ers@osf.org)
e
s 00007/00008/00184
d D 7.12 90/06/28 17:09:57 karels 22 21
c RETURN => return, remove syscontext.h
e
s 00028/00024/00164
d D 7.11 90/06/21 18:36:34 mckusick 21 20
c new system call convention
e
s 00001/00001/00187
d D 7.10 90/05/17 17:43:27 marc 20 19
c only copy out ctty if proc *has* a ctty
e
s 00001/00001/00187
d D 7.9 90/05/04 20:55:23 mckusick 19 18
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00017/00009/00171
d D 7.8 90/04/05 14:41:50 marc 18 17
c times moved to proc, also ctty to session
e
s 00002/00013/00178
d D 7.7 89/11/02 14:53:49 mckusick 17 16
c Keith Bostic says not so quick with the copyright notice
e
s 00004/00002/00187
d D 7.6 89/09/03 18:22:12 karels 16 15
c ruid, rgid moved to proc
e
s 00075/00052/00114
d D 7.5 89/05/09 17:02:05 mckusick 15 14
c merge in vnodes
e
s 00032/00032/00134
d D 7.4 89/04/26 19:41:46 mckusick 14 13
c use new form of suser()
e
s 00001/00002/00165
d D 7.3 88/10/18 15:08:30 marc 13 12
c bcopy name, don't use counted loop
e
s 00001/00001/00166
d D 7.2 86/11/25 13:58:30 karels 12 11
c race if unlinking acct file
e
s 00001/00001/00166
d D 7.1 86/06/05 00:01:20 mckusick 11 10
c 4.3BSD release version
e
s 00003/00003/00164
d D 6.9 86/02/20 15:58:16 karels 10 9
c cleanups from Sam: format, spl's, ptrace defs
e
s 00007/00001/00160
d D 6.8 85/06/08 14:34:31 mckusick 9 8
c Add copyright
e
s 00005/00000/00156
d D 6.7 85/05/21 15:25:35 mckusick 8 7
c must not enable accounting on read-only file systems
e
s 00002/00002/00154
d D 6.6 84/12/12 09:18:53 karels 7 6
c use AHZ instead of 1<<6.
e
s 00009/00009/00147
d D 6.5 84/08/29 20:18:44 bloom 6 5
c Change to includes.  no more ../h
e
s 00001/00001/00155
d D 6.4 84/07/15 11:53:56 karels 5 4
c typo in memory average calculation
e
s 00022/00010/00134
d D 6.3 84/07/14 14:45:35 sam 4 3
c correct accounting system: report times in 64ths of a second; 
c calculate average memory usage correctly (and returned in units of the 
c software page size so that sa can use getpagesize to figure out kilobytes)
e
s 00005/00002/00139
d D 6.2 84/07/08 16:18:07 mckusick 3 2
c rework `namei' interface to eliminate global variables
e
s 00000/00000/00141
d D 6.1 83/07/29 06:32:11 sam 2 1
c 4.2 distribution
e
s 00141/00000/00000
d D 4.1 83/05/27 14:02:40 sam 1 0
c date and time created 83/05/27 14:02:40 by sam
e
u
U
t
T
I 1
D 9
/*	%M%	%I%	%E%	*/
E 9
I 9
D 27
/*
D 11
 * Copyright (c) 1982 Regents of the University of California.
E 11
I 11
D 15
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
D 17
 * All rights reserved.
E 15
 *
I 15
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
E 17
I 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 27
I 27
/*-
D 49
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
E 49
I 49
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 51
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 51
E 49
 *
 * %sccs.include.proprietary.c%
E 27
E 17
 *
E 15
 *	%W% (Berkeley) %G%
 */
E 9

D 6
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/inode.h"
#include "../h/fs.h"
#include "../h/kernel.h"
#include "../h/acct.h"
D 3
#include "../h/nami.h"
E 3
#include "../h/uio.h"
E 6
I 6
D 44
#include "param.h"
#include "systm.h"
I 16
D 25
#include "time.h"
E 25
I 25
#include "namei.h"
#include "resourcevar.h"
E 25
#include "proc.h"
E 16
D 15
#include "dir.h"
E 15
D 21
#include "user.h"
E 21
I 21
#include "ioctl.h"
#include "termios.h"
#include "tty.h"
D 22
#undef RETURN
#include "syscontext.h"
E 22
I 22
D 25
#include "user.h"
E 25
E 22
E 21
D 15
#include "inode.h"
#include "fs.h"
E 15
I 15
#include "vnode.h"
#include "mount.h"
E 15
#include "kernel.h"
I 24
#include "file.h"
E 24
#include "acct.h"
D 25
#include "uio.h"
E 25
I 15
#include "syslog.h"
E 44
I 44
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/resourcevar.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/termios.h>
#include <sys/tty.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/acct.h>
#include <sys/syslog.h>
I 56
#include <sys/syscallargs.h>
E 56
E 44
I 18
D 21
#include "ioctl.h"
#include "termios.h"
#include "tty.h"
E 21
E 18
E 15
E 6

/*
I 15
 * Values associated with enabling and disabling accounting
 */
int	acctsuspend = 2;	/* stop accounting when < 2% free space left */
int	acctresume = 4;		/* resume when free space risen to > 4% */
D 42
struct	timeval chk = { 15, 0 };/* frequency to check space for accounting */
E 42
I 42
D 45
int	chk = 15;		/* frequency (in seconds) to check space */
E 45
I 45
int	acctchkfreq = 15;	/* frequency (in seconds) to check space */
E 45
E 42

/*
E 15
 * SHOULD REPLACE THIS WITH A DRIVER THAT CAN BE READ TO SIMPLIFY.
 */
D 15
struct	inode *acctp;
struct	inode *savacctp;
E 15
I 15
struct	vnode *acctp;
struct	vnode *savacctp;
E 15

/*
D 28
 * Perform process accounting functions.
E 28
I 28
 * Enable or disable process accounting.
 *
 * If a non-null filename is given, that file is used to store accounting
 * records on process exit. If a null filename is given process accounting
 * is suspended. If accounting is enabled, the system checks the amount
 * of freespace on the filesystem at timeval intervals. If the amount of
 * freespace is below acctsuspend percent, accounting is suspended. If
 * accounting has been suspended, and freespace rises above acctresume,
 * accounting is resumed.
E 28
 */
D 21
sysacct()
E 21
I 21
D 48
/* ARGSUSED */
I 43
struct sysacct_args {
E 48
I 48
D 56
struct acct_args {
E 48
	char	*fname;
};
E 56
E 43
D 48
sysacct(p, uap, retval)
E 48
I 48
acct(p, uap, retval)
E 48
	struct proc *p;
D 43
	struct args {
		char	*fname;
	} *uap;
E 43
I 43
D 48
	struct sysacct_args *uap;
E 48
I 48
D 56
	struct acct_args *uap;
E 48
E 43
	int *retval;
E 56
I 56
	struct acct_args /* {
		syscallarg(char *) path;
	} */ *uap;
	register_t *retval;
E 56
E 21
{
I 40
D 41
	USES_VOP_UNLOCK;
E 41
E 40
D 15
	register struct inode *ip;
E 15
I 15
	register struct vnode *vp;
E 15
D 21
	register struct a {
		char	*fname;
	} *uap = (struct a *)u.u_ap;
E 21
I 3
D 25
	register struct nameidata *ndp = &u.u_nd;
E 25
I 15
D 42
	extern int acctwatch();
E 42
I 42
	extern void acctwatch __P((void *));
E 42
	struct vnode *oacctp;
I 21
	int error;
I 25
	struct nameidata nd;
E 25
E 21
E 15
E 3

D 14
	if (suser()) {
		if (savacctp) {
			acctp = savacctp;
			savacctp = NULL;
E 14
I 14
D 21
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
E 21
I 21
D 25
	if (error = suser(u.u_cred, &u.u_acflag))
E 25
I 25
	if (error = suser(p->p_ucred, &p->p_acflag))
E 25
D 22
		RETURN (error);
E 22
I 22
		return (error);
E 22
E 21
	if (savacctp) {
		acctp = savacctp;
		savacctp = NULL;
	}
D 24
	if (uap->fname==NULL) {
E 24
I 24
D 56
	if (uap->fname == NULL) {
E 56
I 56
	if (SCARG(uap, path) == NULL) {
E 56
E 24
D 15
		if (ip = acctp) {
E 15
I 15
		if (vp = acctp) {
E 15
			acctp = NULL;
D 15
			irele(ip);
E 15
I 15
D 30
			vrele(vp);
E 30
I 30
			error = vn_close(vp, FWRITE, p->p_ucred, p);
E 30
D 42
			untimeout(acctwatch, (caddr_t)&chk);
E 42
I 42
			untimeout(acctwatch, NULL);
E 42
E 15
E 14
		}
D 14
		if (uap->fname==NULL) {
			if (ip = acctp) {
D 12
				irele(ip);
E 12
				acctp = NULL;
I 12
				irele(ip);
E 12
			}
			return;
		}
D 3
		ip = namei(uchar, LOOKUP, 1);
E 3
I 3
		ndp->ni_nameiop = LOOKUP | FOLLOW;
		ndp->ni_segflg = UIO_USERSPACE;
		ndp->ni_dirp = uap->fname;
		ip = namei(ndp);
E 3
D 10
		if(ip == NULL)
E 10
I 10
		if (ip == NULL)
E 10
			return;
D 10
		if((ip->i_mode & IFMT) != IFREG) {
E 10
I 10
		if ((ip->i_mode&IFMT) != IFREG) {
E 10
			u.u_error = EACCES;
			iput(ip);
			return;
		}
I 8
		if (ip->i_fs->fs_ronly) {
			u.u_error = EROFS;
			iput(ip);
			return;
		}
E 8
		if (acctp && (acctp->i_number != ip->i_number ||
		    acctp->i_dev != ip->i_dev))
			irele(acctp);
		acctp = ip;
		iunlock(ip);
E 14
I 14
D 21
		return;
E 21
I 21
D 22
		RETURN (0);
E 22
I 22
D 30
		return (0);
E 30
I 30
		return (error);
E 30
E 22
E 21
E 14
	}
I 14
D 24
	ndp->ni_nameiop = LOOKUP | FOLLOW;
E 24
D 25
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 15
	ip = namei(ndp);
	if (ip == NULL)
E 15
I 15
D 21
	if (u.u_error = namei(ndp))
E 15
		return;
E 21
I 21
D 24
	if (error = namei(ndp))
E 24
I 24
	if (error = vn_open(ndp, FWRITE, 0644))
E 25
I 25
D 31
	nd.ni_segflg = UIO_USERSPACE;
	nd.ni_dirp = uap->fname;
	if (error = vn_open(&nd, p, FWRITE, 0644))
E 31
I 31
D 56
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->fname, p);
E 56
I 56
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 56
	if (error = vn_open(&nd, FWRITE, 0644))
E 31
E 25
E 24
D 22
		RETURN (error);
E 22
I 22
		return (error);
E 22
E 21
D 15
	if ((ip->i_mode&IFMT) != IFREG) {
E 15
I 15
D 25
	vp = ndp->ni_vp;
E 25
I 25
	vp = nd.ni_vp;
I 29
D 57
	VOP_UNLOCK(vp);
E 57
I 57
	VOP_UNLOCK(vp, 0, p);
E 57
E 29
E 25
	if (vp->v_type != VREG) {
E 15
D 21
		u.u_error = EACCES;
E 21
D 15
		iput(ip);
E 15
I 15
D 30
		vrele(vp);
E 30
I 30
		(void) vn_close(vp, FWRITE, p->p_ucred, p);
E 30
E 15
D 21
		return;
E 21
I 21
D 22
		RETURN (EACCES);
E 22
I 22
		return (EACCES);
E 22
E 21
D 24
	}
D 15
	if (ip->i_fs->fs_ronly) {
E 15
I 15
D 19
	if (vp->v_mount->m_flag & M_RDONLY) {
E 19
I 19
	if (vp->v_mount->mnt_flag & MNT_RDONLY) {
E 19
E 15
D 21
		u.u_error = EROFS;
E 21
D 15
		iput(ip);
E 15
I 15
		vrele(vp);
E 15
D 21
		return;
E 21
I 21
D 22
		RETURN (EROFS);
E 22
I 22
		return (EROFS);
E 24
E 22
E 21
	}
D 15
	if (acctp && (acctp->i_number != ip->i_number ||
	    acctp->i_dev != ip->i_dev))
		irele(acctp);
	acctp = ip;
	iunlock(ip);
E 15
I 15
	oacctp = acctp;
	acctp = vp;
	if (oacctp)
D 30
		vrele(oacctp);
E 30
I 30
		error = vn_close(oacctp, FWRITE, p->p_ucred, p);
E 30
D 42
	acctwatch(&chk);
E 42
I 42
	acctwatch(NULL);
E 42
I 21
D 22
	RETURN (0);
E 22
I 22
D 30
	return (0);
E 30
I 30
	return (error);
E 30
E 22
E 21
E 15
E 14
}

D 15
int	acctsuspend = 2;	/* stop accounting when < 2% free space left */
int	acctresume = 4;		/* resume when free space risen to > 4% */

struct	acct acctbuf;
E 15
/*
D 15
 * On exit, write a record on the accounting file.
E 15
I 15
 * Periodically check the file system to see if accounting
D 52
 * should be turned on or off.
E 52
I 52
 * should be turned on or off. Beware the case where the vnode
 * has been vgone()'d out from underneath us, e.g. when the file
 * system containing the accounting file has been forcibly unmounted.
E 52
E 15
 */
D 15
acct()
E 15
I 15
D 42
acctwatch(resettime)
	struct timeval *resettime;
E 42
I 42
/* ARGSUSED */
void
acctwatch(a)
	void *a;
E 42
E 15
{
D 15
	register int i;
	register struct inode *ip;
	register struct fs *fs;
I 4
	register struct rusage *ru;
E 4
	off_t siz;
I 4
	struct timeval t;
E 4
	register struct acct *ap = &acctbuf;
E 15
I 15
	struct statfs sb;
E 15

	if (savacctp) {
I 52
		if (savacctp->v_type == VBAD) {
			(void) vn_close(savacctp, FWRITE, NOCRED, NULL);
			savacctp = NULL;
			return;
		}
E 52
D 15
		fs = savacctp->i_fs;
		if (freespace(fs, fs->fs_minfree + acctresume) > 0) {
E 15
I 15
D 26
		(void)VFS_STATFS(savacctp->v_mount, &sb);
E 26
I 26
		(void)VFS_STATFS(savacctp->v_mount, &sb, (struct proc *)0);
E 26
		if (sb.f_bavail > acctresume * sb.f_blocks / 100) {
E 15
			acctp = savacctp;
			savacctp = NULL;
D 15
			printf("Accounting resumed\n");
E 15
I 15
			log(LOG_NOTICE, "Accounting resumed\n");
I 45
		}
	} else {
		if (acctp == NULL)
E 45
			return;
I 52
		if (acctp->v_type == VBAD) {
			(void) vn_close(acctp, FWRITE, NOCRED, NULL);
			acctp = NULL;
			return;
		}
E 52
I 45
		(void)VFS_STATFS(acctp->v_mount, &sb, (struct proc *)0);
		if (sb.f_bavail <= acctsuspend * sb.f_blocks / 100) {
			savacctp = acctp;
			acctp = NULL;
			log(LOG_NOTICE, "Accounting suspended\n");
E 45
E 15
		}
	}
D 15
	if ((ip = acctp) == NULL)
E 15
I 15
D 45
	if (acctp == NULL)
E 15
		return;
D 15
	fs = acctp->i_fs;
	if (freespace(fs, fs->fs_minfree + acctsuspend) <= 0) {
E 15
I 15
D 26
	(void)VFS_STATFS(acctp->v_mount, &sb);
E 26
I 26
	(void)VFS_STATFS(acctp->v_mount, &sb, (struct proc *)0);
E 26
	if (sb.f_bavail <= acctsuspend * sb.f_blocks / 100) {
E 15
		savacctp = acctp;
		acctp = NULL;
D 15
		printf("Accounting suspended\n");
		return;
E 15
I 15
		log(LOG_NOTICE, "Accounting suspended\n");
E 15
	}
D 15
	ilock(ip);
E 15
I 15
D 42
	timeout(acctwatch, (caddr_t)resettime, hzto(resettime));
E 42
I 42
	timeout(acctwatch, NULL, chk * hz);
E 45
I 45
	timeout(acctwatch, NULL, acctchkfreq * hz);
E 45
E 42
}

/*
D 28
 * On exit, write a record on the accounting file.
E 28
I 28
 * This routine calculates an accounting record for a process and,
 * if accounting is enabled, writes it to the accounting file.
E 28
 */
D 21
acct()
E 21
I 21
D 48
acct(p)
E 48
I 48
acct_process(p)
E 48
	register struct proc *p;
E 21
{
	register struct rusage *ru;
	struct vnode *vp;
D 18
	struct timeval t;
	int i;
E 18
I 18
	struct timeval t, ut, st;
D 55
	int i, s;
E 55
I 55
	int error, i, s;
E 55
E 18
	struct acct acctbuf;
	register struct acct *ap = &acctbuf;
I 18
D 21
	register struct proc *p = u.u_procp;
E 21
E 18

D 55
	if ((vp = acctp) == NULL)
E 55
I 55
	s = splclock();
	if ((vp = acctp) == NULL) {
		splx(s);
E 55
D 21
		return;
E 21
I 21
		return (0);
I 55
	}
E 55
I 52
	if (vp->v_type == VBAD) {
		(void) vn_close(vp, FWRITE, NOCRED, NULL);
		acctp = NULL;
I 55
		splx(s);
E 55
		return (0);
	}
E 52
E 21
E 15
D 13
	for (i = 0; i < sizeof (ap->ac_comm); i++)
		ap->ac_comm[i] = u.u_comm[i];
E 13
I 13
D 18
	bcopy(u.u_comm, ap->ac_comm, sizeof(ap->ac_comm));
E 18
I 18
	bcopy(p->p_comm, ap->ac_comm, sizeof(ap->ac_comm));
E 18
E 13
D 4
	ap->ac_utime = compress((long)u.u_ru.ru_utime.tv_sec);
	ap->ac_stime = compress((long)u.u_ru.ru_stime.tv_sec);
	ap->ac_etime = compress((long)time.tv_sec - u.u_start);
	ap->ac_btime = u.u_start;
E 4
I 4
D 25
	ru = &u.u_ru;
E 25
I 25
	ru = &p->p_stats->p_ru;
I 42
	calcru(p, &ut, &st, NULL);
E 42
E 25
D 18
	ap->ac_utime = compress(ru->ru_utime.tv_sec, ru->ru_utime.tv_usec);
	ap->ac_stime = compress(ru->ru_stime.tv_sec, ru->ru_stime.tv_usec);
E 18
I 18
D 55
	s = splclock();
E 55
D 42
	ut = p->p_utime;
	st = p->p_stime;
E 42
E 18
	t = time;
I 18
D 55
	splx(s);
E 55
	ap->ac_utime = compress(ut.tv_sec, ut.tv_usec);
	ap->ac_stime = compress(st.tv_sec, st.tv_usec);
E 18
D 25
	timevalsub(&t, &u.u_start);
E 25
I 25
	timevalsub(&t, &p->p_stats->p_start);
E 25
	ap->ac_etime = compress(t.tv_sec, t.tv_usec);
D 25
	ap->ac_btime = u.u_start.tv_sec;
E 4
D 16
	ap->ac_uid = u.u_ruid;
	ap->ac_gid = u.u_rgid;
E 16
I 16
D 21
	ap->ac_uid = u.u_procp->p_ruid;
	ap->ac_gid = u.u_procp->p_rgid;
E 21
I 21
	ap->ac_uid = p->p_ruid;
	ap->ac_gid = p->p_rgid;
E 25
I 25
	ap->ac_btime = p->p_stats->p_start.tv_sec;
	ap->ac_uid = p->p_cred->p_ruid;
	ap->ac_gid = p->p_cred->p_rgid;
E 25
E 21
E 16
D 4
	ap->ac_mem = 0;
	if (i = u.u_ru.ru_utime.tv_sec + u.u_ru.ru_stime.tv_sec)
		ap->ac_mem =
		    (u.u_ru.ru_ixrss + u.u_ru.ru_idrss + u.u_ru.ru_isrss) / i;
	ap->ac_io = compress((long)(u.u_ru.ru_inblock + u.u_ru.ru_oublock));
E 4
I 4
D 18
	t = ru->ru_stime;
	timevaladd(&t, &ru->ru_utime);
E 18
I 18
	t = st;
	timevaladd(&t, &ut);
E 18
D 5
	if (i = t.tv_sec / hz + t.tv_usec / tick)
E 5
I 5
	if (i = t.tv_sec * hz + t.tv_usec / tick)
E 5
D 25
		ap->ac_mem = (ru->ru_ixrss+ru->ru_idrss+ru->ru_isrss) / i;
E 25
I 25
		ap->ac_mem = (ru->ru_ixrss + ru->ru_idrss + ru->ru_isrss) / i;
E 25
	else
		ap->ac_mem = 0;
D 23
	ap->ac_mem >>= CLSIZELOG2;
E 23
D 10
	ap->ac_io = compress(ru->ru_inblock + ru->ru_oublock, 0);
E 10
I 10
	ap->ac_io = compress(ru->ru_inblock + ru->ru_oublock, (long)0);
E 10
E 4
D 18
	if (u.u_ttyp)
		ap->ac_tty = u.u_ttyd;
E 18
I 18
D 20
	if (p->p_session->s_ttyp)
E 20
I 20
D 50
	if (p->p_flag&SCTTY && p->p_session->s_ttyp)
E 50
I 50
	if (p->p_flag & P_CONTROLT && p->p_session->s_ttyp)
E 50
E 20
		ap->ac_tty = p->p_session->s_ttyp->t_dev;
E 18
	else
		ap->ac_tty = NODEV;
D 25
	ap->ac_flag = u.u_acflag;
E 25
I 25
	ap->ac_flag = p->p_acflag;
I 46
D 53
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 53
I 53
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 53
E 46
E 25
D 15
	siz = ip->i_size;
	u.u_error = 0;				/* XXX */
	u.u_error =
	    rdwri(UIO_WRITE, ip, (caddr_t)ap, sizeof (acctbuf), siz,
		1, (int *)0);
	if (u.u_error)
		itrunc(ip, (u_long)siz);
	iunlock(ip);
E 15
I 15
D 21
	u.u_error = vn_rdwr(UIO_WRITE, vp, (caddr_t)ap, sizeof (acctbuf),
		(off_t)0, UIO_SYSSPACE, IO_UNIT|IO_APPEND, u.u_cred, (int *)0);
E 21
I 21
D 26
	return (vn_rdwr(UIO_WRITE, vp, (caddr_t)ap, sizeof (acctbuf),
D 25
		(off_t)0, UIO_SYSSPACE, IO_UNIT|IO_APPEND, u.u_cred, (int *)0));
E 25
I 25
	    (off_t)0, UIO_SYSSPACE, IO_UNIT|IO_APPEND, p->p_ucred, (int *)0));
E 26
I 26
D 55
	return (vn_rdwr(UIO_WRITE, vp, (caddr_t)ap, sizeof (acctbuf), (off_t)0,
E 55
I 55
	error = vn_rdwr(UIO_WRITE, vp, (caddr_t)ap, sizeof (acctbuf), (off_t)0,
E 55
		UIO_SYSSPACE, IO_UNIT|IO_APPEND, p->p_ucred, (int *)0,
D 55
		(struct proc *)0));
E 55
I 55
		(struct proc *)0);
	splx(s);
	return (error);
E 55
E 26
E 25
E 21
E 15
}

/*
 * Produce a pseudo-floating point representation
 * with 3 bits base-8 exponent, 13 bits fraction.
 */
D 4
compress(t)
E 4
I 4
compress(t, ut)
E 4
	register long t;
I 4
	long ut;
E 4
{
	register exp = 0, round = 0;

I 4
D 7
	t <<= 6;
E 7
I 7
	t = t * AHZ;  /* compiler will convert only this format to a shift */
E 7
	if (ut)
D 7
		t += ut / (1000000 / (1<<6));
E 7
I 7
		t += ut / (1000000 / AHZ);
E 7
E 4
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
	return ((exp<<13) + t);
}
E 1
