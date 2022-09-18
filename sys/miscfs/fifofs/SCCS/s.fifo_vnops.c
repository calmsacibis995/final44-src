h08655
s 00050/00026/00439
d D 8.10 95/05/27 23:05:44 mckusick 37 36
c allow opening for reading and writing (from mycroft)
e
s 00012/00000/00453
d D 8.9 95/05/22 23:07:33 mckusick 36 35
c have to have fifo_inactive so can unlock at its end
e
s 00017/00037/00436
d D 8.8 95/05/14 00:40:23 mckusick 35 34
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00001/00000/00472
d D 8.7 95/02/22 20:52:22 mckusick 34 33
c add fifo_revoke
e
s 00002/00001/00470
d D 8.6 95/02/06 04:34:54 pendry 33 32
c fix cpy date & bmap args structure
e
s 00002/00000/00469
d D 8.5 95/02/06 04:30:15 pendry 32 31
c ensure bmap run list is initialised
e
s 00001/00000/00468
d D 8.4 94/08/10 23:58:36 mckusick 31 30
c add vop_lease
e
s 00004/00004/00464
d D 8.3 94/06/15 16:51:19 mkm 30 29
c Kill the evil U-word!  And fix the order of some casted arguments.
c (from mycroft)
e
s 00000/00002/00468
d D 8.2 94/01/04 18:50:55 bostic 29 28
c lint
e
s 00002/00002/00468
d D 8.1 93/06/10 23:36:28 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00467
d D 7.19 93/05/26 17:33:36 mckusick 27 26
c allow fifo wait to be interruptable
e
s 00028/00000/00442
d D 7.18 93/05/25 15:32:19 mckusick 26 25
c add fifo_pathconf
e
s 00021/00021/00421
d D 7.17 92/07/12 14:35:58 mckusick 25 24
c new include format; misc syntactic cleanup
e
s 00078/00032/00364
d D 7.16 92/07/03 01:36:09 mckusick 24 23
c add parameter declarations; delete USES; delete fifo_vget
e
s 00021/00018/00375
d D 7.15 92/06/04 09:41:24 heideman 23 22
c registerized vnodeop ops after vnode interface conversion
e
s 00050/00134/00343
d D 7.14 92/05/15 13:56:18 heideman 22 21
c vnodeop argument macro expansion
e
s 00162/00095/00315
d D 7.13 92/05/14 17:31:20 heideman 21 12
c vnode interface conversion
e
s 00162/00095/00315
d R 7.13 92/05/14 15:45:12 heideman 20 12
c vnode interface conversion
e
s 00162/00095/00315
d R 7.13 92/05/14 14:50:23 heideman 19 12
c vnode interface conversion
e
s 00162/00096/00314
d R 7.13 92/05/14 12:54:25 heideman 18 12
c vnode interface conversion
e
s 00162/00096/00314
d R 7.13 92/05/14 11:51:47 heideman 17 12
c vnode interface conversion
e
s 00162/00096/00314
d R 7.13 92/05/14 10:31:59 heideman 16 12
c vnode interface conversion
e
s 00167/00096/00314
d R 7.13 92/05/13 23:10:42 heideman 15 12
c vnode interface conversion
e
s 00167/00096/00314
d R 7.13 92/05/13 18:56:57 heideman 14 12
c vnode interface conversion
e
s 00167/00096/00314
d R 7.13 92/05/13 18:28:58 heideman 13 12
c vnode interface conversion
e
s 00001/00001/00409
d D 7.12 92/05/11 17:52:49 mckusick 12 11
c missing flags argument to sosend (from forys@snake.cs.utah.edu)
e
s 00015/00006/00395
d D 7.11 92/04/09 15:22:58 mckusick 11 10
c unlock while waiting for data (from forys@cs.utah.edu)
e
s 00001/00000/00400
d D 7.10 92/02/15 17:32:32 mckusick 10 9
c must include proc before tty.h and socketvar.h
e
s 00006/00007/00394
d D 7.9 92/02/03 23:27:23 heideman 9 8
c new calling convention for VOP ops
e
s 00007/00000/00394
d D 7.8 91/11/05 15:34:38 mckusick 8 7
c reorganization to move ufsmount ops to be vnode ops
e
s 00041/00046/00353
d D 7.7 91/04/15 23:38:17 mckusick 7 6
c use prototypes for fifo vnode ops (from fifo.h); add appropriate proc pointers
e
s 00006/00014/00393
d D 7.6 91/03/17 15:41:17 karels 6 5
c more-or-less working with new proc & user structs
e
s 00016/00000/00391
d D 7.5 91/02/01 16:21:55 mckusick 5 4
c add POSIX-style byte-level record locking
e
s 00001/00011/00390
d D 7.4 90/06/28 21:18:15 bostic 4 3
c new copyright notice
e
s 00008/00001/00393
d D 7.3 90/03/27 19:23:26 mckusick 3 2
c do not lose memory on error
e
s 00005/00004/00389
d D 7.2 90/03/26 20:31:20 karels 2 1
c it's tsleep; it looks like this
e
s 00393/00000/00000
d D 7.1 90/03/05 19:14:10 mckusick 1 0
c date and time created 90/03/05 19:14:10 by mckusick
e
u
U
t
T
I 1
/*
D 28
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 28
I 28
D 33
 * Copyright (c) 1990, 1993
E 33
I 33
 * Copyright (c) 1990, 1993, 1995
E 33
 *	The Regents of the University of California.  All rights reserved.
E 28
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

D 25
#include "param.h"
I 10
#include "proc.h"
E 10
#include "time.h"
#include "namei.h"
#include "vnode.h"
#include "socket.h"
#include "socketvar.h"
#include "stat.h"
I 6
#include "systm.h"
E 6
#include "ioctl.h"
#include "file.h"
I 7
#include "fifo.h"
E 7
#include "errno.h"
#include "malloc.h"
E 25
I 25
#include <sys/param.h>
I 35
#include <sys/systm.h>
E 35
#include <sys/proc.h>
#include <sys/time.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/stat.h>
D 35
#include <sys/systm.h>
E 35
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/errno.h>
#include <sys/malloc.h>
#include <miscfs/fifofs/fifo.h>
E 25

/*
 * This structure is associated with the FIFO vnode and stores
 * the state associated with the FIFO.
 */
struct fifoinfo {
	struct socket	*fi_readsock;
	struct socket	*fi_writesock;
	long		fi_readers;
	long		fi_writers;
};

D 7
int	fifo_lookup(),
	fifo_open(),
	fifo_read(),
	fifo_write(),
	fifo_strategy(),
	fifo_bmap(),
	fifo_ioctl(),
	fifo_select(),
	fifo_lock(),
	fifo_unlock(),
	fifo_close(),
	fifo_print(),
I 5
	fifo_advlock(),
E 5
	fifo_ebadf(),
	fifo_badop(),
D 6
	fifo_nullop();
E 6
I 6
	nullop();
E 6

E 7
D 21
struct vnodeops fifo_vnodeops = {
	fifo_lookup,		/* lookup */
D 7
	fifo_badop,		/* create */
	fifo_badop,		/* mknod */
E 7
I 7
	fifo_create,		/* create */
	fifo_mknod,		/* mknod */
E 7
	fifo_open,		/* open */
	fifo_close,		/* close */
D 7
	fifo_ebadf,		/* access */
	fifo_ebadf,		/* getattr */
	fifo_ebadf,		/* setattr */
E 7
I 7
	fifo_access,		/* access */
	fifo_getattr,		/* getattr */
	fifo_setattr,		/* setattr */
E 7
	fifo_read,		/* read */
	fifo_write,		/* write */
	fifo_ioctl,		/* ioctl */
	fifo_select,		/* select */
D 7
	fifo_badop,		/* mmap */
D 6
	fifo_nullop,		/* fsync */
E 6
I 6
	nullop,			/* fsync */
E 6
	fifo_badop,		/* seek */
	fifo_badop,		/* remove */
	fifo_badop,		/* link */
	fifo_badop,		/* rename */
	fifo_badop,		/* mkdir */
	fifo_badop,		/* rmdir */
	fifo_badop,		/* symlink */
	fifo_badop,		/* readdir */
	fifo_badop,		/* readlink */
	fifo_badop,		/* abortop */
D 6
	fifo_nullop,		/* inactive */
	fifo_nullop,		/* reclaim */
E 6
I 6
	nullop,			/* inactive */
	nullop,			/* reclaim */
E 7
I 7
	fifo_mmap,		/* mmap */
	fifo_fsync,		/* fsync */
	fifo_seek,		/* seek */
	fifo_remove,		/* remove */
	fifo_link,		/* link */
	fifo_rename,		/* rename */
	fifo_mkdir,		/* mkdir */
	fifo_rmdir,		/* rmdir */
	fifo_symlink,		/* symlink */
	fifo_readdir,		/* readdir */
	fifo_readlink,		/* readlink */
	fifo_abortop,		/* abortop */
	fifo_inactive,		/* inactive */
	fifo_reclaim,		/* reclaim */
E 7
E 6
	fifo_lock,		/* lock */
	fifo_unlock,		/* unlock */
	fifo_bmap,		/* bmap */
D 7
	fifo_badop,		/* strategy */
E 7
I 7
	fifo_strategy,		/* strategy */
E 7
	fifo_print,		/* print */
D 6
	fifo_nullop,		/* islocked */
E 6
I 6
D 7
	nullop,			/* islocked */
E 7
I 7
	fifo_islocked,		/* islocked */
E 7
E 6
I 5
	fifo_advlock,		/* advlock */
I 8
	fifo_blkatoff,		/* blkatoff */
	fifo_vget,		/* vget */
	fifo_valloc,		/* valloc */
	fifo_vfree,		/* vfree */
	fifo_truncate,		/* truncate */
	fifo_update,		/* update */
	fifo_bwrite,		/* bwrite */
E 21
I 21
int (**fifo_vnodeop_p)();
struct vnodeopv_entry_desc fifo_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, fifo_lookup },		/* lookup */
	{ &vop_create_desc, fifo_create },		/* create */
	{ &vop_mknod_desc, fifo_mknod },		/* mknod */
D 25
	{ &vop_open_desc, fifo_open },		/* open */
E 25
I 25
	{ &vop_open_desc, fifo_open },			/* open */
E 25
	{ &vop_close_desc, fifo_close },		/* close */
	{ &vop_access_desc, fifo_access },		/* access */
	{ &vop_getattr_desc, fifo_getattr },		/* getattr */
	{ &vop_setattr_desc, fifo_setattr },		/* setattr */
D 25
	{ &vop_read_desc, fifo_read },		/* read */
E 25
I 25
	{ &vop_read_desc, fifo_read },			/* read */
E 25
	{ &vop_write_desc, fifo_write },		/* write */
I 31
	{ &vop_lease_desc, fifo_lease_check },		/* lease */
E 31
	{ &vop_ioctl_desc, fifo_ioctl },		/* ioctl */
	{ &vop_select_desc, fifo_select },		/* select */
I 34
	{ &vop_revoke_desc, fifo_revoke },		/* revoke */
E 34
D 25
	{ &vop_mmap_desc, fifo_mmap },		/* mmap */
E 25
I 25
	{ &vop_mmap_desc, fifo_mmap },			/* mmap */
E 25
	{ &vop_fsync_desc, fifo_fsync },		/* fsync */
D 25
	{ &vop_seek_desc, fifo_seek },		/* seek */
E 25
I 25
	{ &vop_seek_desc, fifo_seek },			/* seek */
E 25
	{ &vop_remove_desc, fifo_remove },		/* remove */
D 25
	{ &vop_link_desc, fifo_link },		/* link */
E 25
I 25
	{ &vop_link_desc, fifo_link },			/* link */
E 25
	{ &vop_rename_desc, fifo_rename },		/* rename */
	{ &vop_mkdir_desc, fifo_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, fifo_rmdir },		/* rmdir */
	{ &vop_symlink_desc, fifo_symlink },		/* symlink */
	{ &vop_readdir_desc, fifo_readdir },		/* readdir */
	{ &vop_readlink_desc, fifo_readlink },		/* readlink */
	{ &vop_abortop_desc, fifo_abortop },		/* abortop */
	{ &vop_inactive_desc, fifo_inactive },		/* inactive */
	{ &vop_reclaim_desc, fifo_reclaim },		/* reclaim */
D 25
	{ &vop_lock_desc, fifo_lock },		/* lock */
E 25
I 25
	{ &vop_lock_desc, fifo_lock },			/* lock */
E 25
	{ &vop_unlock_desc, fifo_unlock },		/* unlock */
D 25
	{ &vop_bmap_desc, fifo_bmap },		/* bmap */
E 25
I 25
	{ &vop_bmap_desc, fifo_bmap },			/* bmap */
E 25
	{ &vop_strategy_desc, fifo_strategy },		/* strategy */
	{ &vop_print_desc, fifo_print },		/* print */
	{ &vop_islocked_desc, fifo_islocked },		/* islocked */
I 26
	{ &vop_pathconf_desc, fifo_pathconf },		/* pathconf */
E 26
	{ &vop_advlock_desc, fifo_advlock },		/* advlock */
	{ &vop_blkatoff_desc, fifo_blkatoff },		/* blkatoff */
D 24
	{ &vop_vget_desc, fifo_vget },		/* vget */
E 24
	{ &vop_valloc_desc, fifo_valloc },		/* valloc */
	{ &vop_vfree_desc, fifo_vfree },		/* vfree */
	{ &vop_truncate_desc, fifo_truncate },		/* truncate */
	{ &vop_update_desc, fifo_update },		/* update */
	{ &vop_bwrite_desc, fifo_bwrite },		/* bwrite */
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 21
E 8
E 5
};
I 21
struct vnodeopv_desc fifo_vnodeop_opv_desc =
	{ &fifo_vnodeop_p, fifo_vnodeop_entries };
E 21

/*
 * Trivial lookup routine that always fails.
 */
D 7
fifo_lookup(vp, ndp)
E 7
I 7
/* ARGSUSED */
D 9
fifo_lookup(vp, ndp, p)
E 7
	struct vnode *vp;
	struct nameidata *ndp;
I 7
	struct proc *p;
E 9
I 9
D 21
fifo_lookup(dvp, vpp, cnp)
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
E 21
I 21
D 24
fifo_lookup (ap)
	struct vop_lookup_args *ap;
E 24
I 24
fifo_lookup(ap)
	struct vop_lookup_args /* {
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
	} */ *ap;
E 24
D 22
#define dvp (ap->a_dvp)
#define vpp (ap->a_vpp)
#define cnp (ap->a_cnp)
E 22
E 21
E 9
E 7
{
D 9

	ndp->ni_dvp = vp;
	ndp->ni_vp = NULL;
E 9
I 9
	
D 22
	*vpp = NULL;
E 22
I 22
	*ap->a_vpp = NULL;
E 22
E 9
	return (ENOTDIR);
}
I 21
D 22
#undef dvp
#undef vpp
#undef cnp
E 22
E 21

/*
 * Open called to set up a new instance of a fifo or
 * to find an active instance of a fifo.
 */
/* ARGSUSED */
D 7
fifo_open(vp, mode, cred)
E 7
I 7
D 21
fifo_open(vp, mode, cred, p)
E 7
	register struct vnode *vp;
	int mode;
	struct ucred *cred;
I 7
	struct proc *p;
E 21
I 21
D 24
fifo_open (ap)
	struct vop_open_args *ap;
E 24
I 24
fifo_open(ap)
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
#define mode (ap->a_mode)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 22
E 21
E 7
{
I 21
D 24
	USES_VOP_CLOSE;
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 24
I 23
D 35
	register struct vnode *vp = ap->a_vp;
E 23
E 21
	register struct fifoinfo *fip;
E 35
I 35
	struct vnode *vp = ap->a_vp;
	struct fifoinfo *fip;
	struct proc *p = ap->a_p;
E 35
	struct socket *rso, *wso;
	int error;
I 2
	static char openstr[] = "fifo";
E 2

D 22
	if ((mode & (FREAD|FWRITE)) == (FREAD|FWRITE))
E 22
I 22
D 37
	if ((ap->a_mode & (FREAD|FWRITE)) == (FREAD|FWRITE))
E 22
		return (EINVAL);
E 37
D 22
	if ((fip = vp->v_fifoinfo) == NULL) {
E 22
I 22
D 23
	if ((fip = ap->a_vp->v_fifoinfo) == NULL) {
E 23
I 23
	if ((fip = vp->v_fifoinfo) == NULL) {
E 23
E 22
		MALLOC(fip, struct fifoinfo *, sizeof(*fip), M_VNODE, M_WAITOK);
D 22
		vp->v_fifoinfo = fip;
E 22
I 22
D 23
		ap->a_vp->v_fifoinfo = fip;
E 23
I 23
		vp->v_fifoinfo = fip;
E 23
E 22
D 3
		if (error = socreate(AF_UNIX, &rso, SOCK_STREAM, 0))
E 3
I 3
D 30
		if (error = socreate(AF_UNIX, &rso, SOCK_STREAM, 0)) {
E 30
I 30
		if (error = socreate(AF_LOCAL, &rso, SOCK_STREAM, 0)) {
E 30
			free(fip, M_VNODE);
D 22
			vp->v_fifoinfo = NULL;
E 22
I 22
D 23
			ap->a_vp->v_fifoinfo = NULL;
E 23
I 23
			vp->v_fifoinfo = NULL;
E 23
E 22
E 3
			return (error);
I 3
		}
E 3
		fip->fi_readsock = rso;
D 30
		if (error = socreate(AF_UNIX, &wso, SOCK_STREAM, 0)) {
E 30
I 30
		if (error = socreate(AF_LOCAL, &wso, SOCK_STREAM, 0)) {
E 30
			(void)soclose(rso);
I 3
			free(fip, M_VNODE);
D 22
			vp->v_fifoinfo = NULL;
E 22
I 22
D 23
			ap->a_vp->v_fifoinfo = NULL;
E 23
I 23
			vp->v_fifoinfo = NULL;
E 23
E 22
E 3
			return (error);
		}
		fip->fi_writesock = wso;
		if (error = unp_connect2(wso, rso)) {
			(void)soclose(wso);
			(void)soclose(rso);
I 3
			free(fip, M_VNODE);
D 22
			vp->v_fifoinfo = NULL;
E 22
I 22
D 23
			ap->a_vp->v_fifoinfo = NULL;
E 23
I 23
			vp->v_fifoinfo = NULL;
E 23
E 22
E 3
			return (error);
		}
I 11
		fip->fi_readers = fip->fi_writers = 0;
E 11
		wso->so_state |= SS_CANTRCVMORE;
		rso->so_state |= SS_CANTSENDMORE;
	}
D 37
	error = 0;
E 37
D 22
	if (mode & FREAD) {
E 22
I 22
	if (ap->a_mode & FREAD) {
E 22
		fip->fi_readers++;
		if (fip->fi_readers == 1) {
			fip->fi_writesock->so_state &= ~SS_CANTSENDMORE;
			if (fip->fi_writers > 0)
				wakeup((caddr_t)&fip->fi_writers);
		}
D 22
		if (mode & O_NONBLOCK)
E 22
I 22
D 37
		if (ap->a_mode & O_NONBLOCK)
E 22
			return (0);
E 37
I 37
	}
	if (ap->a_mode & FWRITE) {
		fip->fi_writers++;
		if (fip->fi_writers == 1) {
			fip->fi_readsock->so_state &= ~SS_CANTRCVMORE;
			if (fip->fi_readers > 0)
				wakeup((caddr_t)&fip->fi_readers);
		}
	}
	if ((ap->a_mode & FREAD) && (ap->a_mode & O_NONBLOCK) == 0) {
E 37
D 11
		while (fip->fi_writers == 0)
D 2
			if (error = isleep((caddr_t)&fip->fi_readers, PZERO + 1,
			    SLP_FIFO_OPEN, 0))
E 2
I 2
			if (error = tsleep((caddr_t)&fip->fi_readers, PSOCK,
			    openstr, 0))
E 11
I 11
		while (fip->fi_writers == 0) {
D 22
			VOP_UNLOCK(vp);
E 22
I 22
D 23
			VOP_UNLOCK(ap->a_vp);
E 23
I 23
D 35
			VOP_UNLOCK(vp);
E 35
I 35
			VOP_UNLOCK(vp, 0, p);
E 35
E 23
E 22
D 27
			error = tsleep((caddr_t)&fip->fi_readers, PSOCK,
				openstr, 0);
E 27
I 27
			error = tsleep((caddr_t)&fip->fi_readers,
			    PCATCH | PSOCK, openstr, 0);
E 27
D 22
			VOP_LOCK(vp);
E 22
I 22
D 23
			VOP_LOCK(ap->a_vp);
E 23
I 23
D 35
			VOP_LOCK(vp);
E 35
I 35
			vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 35
E 23
E 22
			if (error)
E 11
E 2
D 37
				break;
E 37
I 37
				goto bad;
E 37
I 11
		}
E 11
D 37
	} else {
		fip->fi_writers++;
D 22
		if (fip->fi_readers == 0 && (mode & O_NONBLOCK)) {
E 22
I 22
		if (fip->fi_readers == 0 && (ap->a_mode & O_NONBLOCK)) {
E 22
			error = ENXIO;
		} else {
			if (fip->fi_writers == 1) {
				fip->fi_readsock->so_state &= ~SS_CANTRCVMORE;
				if (fip->fi_readers > 0)
					wakeup((caddr_t)&fip->fi_readers);
E 37
I 37
	}
	if (ap->a_mode & FWRITE) {
		if (ap->a_mode & O_NONBLOCK) {
			if (fip->fi_readers == 0) {
				error = ENXIO;
				goto bad;
E 37
			}
I 37
		} else {
E 37
D 11
			while (fip->fi_readers == 0)
D 2
				if (error = isleep((caddr_t)&fip->fi_writers,
				    PZERO + 1, SLP_FIFO_OPEN, 0))
E 2
I 2
				if (error = tsleep((caddr_t)&fip->fi_writers,
				    PSOCK, openstr, 0))
E 11
I 11
			while (fip->fi_readers == 0) {
D 22
				VOP_UNLOCK(vp);
E 22
I 22
D 23
				VOP_UNLOCK(ap->a_vp);
E 23
I 23
D 35
				VOP_UNLOCK(vp);
E 35
I 35
				VOP_UNLOCK(vp, 0, p);
E 35
E 23
E 22
				error = tsleep((caddr_t)&fip->fi_writers,
D 27
					PSOCK, openstr, 0);
E 27
I 27
				    PCATCH | PSOCK, openstr, 0);
E 27
D 22
				VOP_LOCK(vp);
E 22
I 22
D 23
				VOP_LOCK(ap->a_vp);
E 23
I 23
D 35
				VOP_LOCK(vp);
E 35
I 35
				vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 35
E 23
E 22
				if (error)
E 11
E 2
D 37
					break;
E 37
I 37
					goto bad;
E 37
I 11
			}
E 11
		}
	}
I 37
	return (0);
bad:
E 37
	if (error)
D 7
		fifo_close(vp, mode, cred);
E 7
I 7
D 21
		fifo_close(vp, mode, cred, p);
E 21
I 21
D 22
		VOP_CLOSE(vp, mode, cred, p);
E 22
I 22
D 23
		VOP_CLOSE(ap->a_vp, ap->a_mode, ap->a_cred, ap->a_p);
E 23
I 23
D 35
		VOP_CLOSE(vp, ap->a_mode, ap->a_cred, ap->a_p);
E 35
I 35
		VOP_CLOSE(vp, ap->a_mode, ap->a_cred, p);
E 35
E 23
E 22
E 21
E 7
	return (error);
}
I 21
D 22
#undef vp
#undef mode
#undef cred
#undef p
E 22
E 21

/*
 * Vnode op for read
 */
/* ARGSUSED */
D 21
fifo_read(vp, uio, ioflag, cred)
	struct vnode *vp;
	register struct uio *uio;
	int ioflag;
	struct ucred *cred;
E 21
I 21
D 24
fifo_read (ap)
	struct vop_read_args *ap;
E 24
I 24
fifo_read(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
#define uio (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 22
E 21
{
I 21
D 24
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 24
I 23
D 35
	register struct uio *uio = ap->a_uio;
E 23
E 21
D 22
	register struct socket *rso = vp->v_fifoinfo->fi_readsock;
E 22
I 22
	register struct socket *rso = ap->a_vp->v_fifoinfo->fi_readsock;
E 35
I 35
	struct uio *uio = ap->a_uio;
	struct socket *rso = ap->a_vp->v_fifoinfo->fi_readsock;
	struct proc *p = uio->uio_procp;
E 35
E 22
	int error, startresid;

I 7
#ifdef DIAGNOSTIC
E 7
D 22
	if (uio->uio_rw != UIO_READ)
E 22
I 22
D 23
	if (ap->a_uio->uio_rw != UIO_READ)
E 23
I 23
	if (uio->uio_rw != UIO_READ)
E 23
E 22
		panic("fifo_read mode");
I 7
#endif
E 7
D 22
	if (uio->uio_resid == 0)
E 22
I 22
D 23
	if (ap->a_uio->uio_resid == 0)
E 23
I 23
	if (uio->uio_resid == 0)
E 23
E 22
		return (0);
D 22
	if (ioflag & IO_NDELAY)
E 22
I 22
	if (ap->a_ioflag & IO_NDELAY)
E 22
		rso->so_state |= SS_NBIO;
D 22
	startresid = uio->uio_resid;
	VOP_UNLOCK(vp);
	error = soreceive(rso, (struct mbuf **)0, uio, (int *)0,
E 22
I 22
D 23
	startresid = ap->a_uio->uio_resid;
E 23
I 23
	startresid = uio->uio_resid;
E 23
D 35
	VOP_UNLOCK(ap->a_vp);
E 35
I 35
	VOP_UNLOCK(ap->a_vp, 0, p);
E 35
D 23
	error = soreceive(rso, (struct mbuf **)0, ap->a_uio, (int *)0,
E 23
I 23
D 30
	error = soreceive(rso, (struct mbuf **)0, uio, (int *)0,
E 23
E 22
		(struct mbuf **)0, (struct mbuf **)0);
E 30
I 30
	error = soreceive(rso, (struct mbuf **)0, uio, (struct mbuf **)0,
	    (struct mbuf **)0, (int *)0);
E 30
D 22
	VOP_LOCK(vp);
E 22
I 22
D 35
	VOP_LOCK(ap->a_vp);
E 35
I 35
	vn_lock(ap->a_vp, LK_EXCLUSIVE | LK_RETRY, p);
E 35
E 22
	/*
	 * Clear EOF indication after first such return.
	 */
D 22
	if (uio->uio_resid == startresid)
E 22
I 22
D 23
	if (ap->a_uio->uio_resid == startresid)
E 23
I 23
	if (uio->uio_resid == startresid)
E 23
E 22
		rso->so_state &= ~SS_CANTRCVMORE;
D 22
	if (ioflag & IO_NDELAY)
E 22
I 22
	if (ap->a_ioflag & IO_NDELAY)
E 22
		rso->so_state &= ~SS_NBIO;
	return (error);
}
I 21
D 22
#undef vp
#undef uio
#undef ioflag
#undef cred
E 22
E 21

/*
 * Vnode op for write
 */
/* ARGSUSED */
D 21
fifo_write(vp, uio, ioflag, cred)
	struct vnode *vp;
	register struct uio *uio;
	int ioflag;
	struct ucred *cred;
E 21
I 21
D 24
fifo_write (ap)
	struct vop_write_args *ap;
E 24
I 24
fifo_write(ap)
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
#define uio (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 22
E 21
{
I 21
D 24
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 24
E 21
D 22
	struct socket *wso = vp->v_fifoinfo->fi_writesock;
E 22
I 22
	struct socket *wso = ap->a_vp->v_fifoinfo->fi_writesock;
I 35
	struct proc *p = ap->a_uio->uio_procp;
E 35
E 22
	int error;

I 7
#ifdef DIAGNOSTIC
E 7
D 22
	if (uio->uio_rw != UIO_WRITE)
E 22
I 22
	if (ap->a_uio->uio_rw != UIO_WRITE)
E 22
		panic("fifo_write mode");
I 7
#endif
E 7
D 22
	if (ioflag & IO_NDELAY)
E 22
I 22
	if (ap->a_ioflag & IO_NDELAY)
E 22
		wso->so_state |= SS_NBIO;
D 22
	VOP_UNLOCK(vp);
D 12
	error = sosend(wso, (struct mbuf *)0, uio, 0, (struct mbuf *)0);
E 12
I 12
	error = sosend(wso, (struct mbuf *)0, uio, 0, (struct mbuf *)0, 0);
E 12
	VOP_LOCK(vp);
	if (ioflag & IO_NDELAY)
E 22
I 22
D 35
	VOP_UNLOCK(ap->a_vp);
E 35
I 35
	VOP_UNLOCK(ap->a_vp, 0, p);
E 35
	error = sosend(wso, (struct mbuf *)0, ap->a_uio, 0, (struct mbuf *)0, 0);
D 35
	VOP_LOCK(ap->a_vp);
E 35
I 35
	vn_lock(ap->a_vp, LK_EXCLUSIVE | LK_RETRY, p);
E 35
	if (ap->a_ioflag & IO_NDELAY)
E 22
		wso->so_state &= ~SS_NBIO;
	return (error);
}
I 21
D 22
#undef vp
#undef uio
#undef ioflag
#undef cred
E 22
E 21

/*
 * Device ioctl operation.
 */
/* ARGSUSED */
D 7
fifo_ioctl(vp, com, data, fflag, cred)
E 7
I 7
D 21
fifo_ioctl(vp, com, data, fflag, cred, p)
E 7
	struct vnode *vp;
	int com;
	caddr_t data;
	int fflag;
	struct ucred *cred;
I 7
	struct proc *p;
E 21
I 21
D 24
fifo_ioctl (ap)
	struct vop_ioctl_args *ap;
E 24
I 24
fifo_ioctl(ap)
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
		int  a_command;
		caddr_t  a_data;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
#define com (ap->a_command)
#define data (ap->a_data)
#define fflag (ap->a_fflag)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 22
E 21
E 7
{
	struct file filetmp;
I 37
	int error;
E 37
D 29
	int error;
E 29

D 22
	if (com == FIONBIO)
E 22
I 22
	if (ap->a_command == FIONBIO)
E 22
		return (0);
D 22
	if (fflag & FREAD)
		filetmp.f_data = (caddr_t)vp->v_fifoinfo->fi_readsock;
E 22
I 22
D 37
	if (ap->a_fflag & FREAD)
E 37
I 37
	if (ap->a_fflag & FREAD) {
E 37
		filetmp.f_data = (caddr_t)ap->a_vp->v_fifoinfo->fi_readsock;
E 22
D 37
	else
E 37
I 37
		error = soo_ioctl(&filetmp, ap->a_command, ap->a_data, ap->a_p);
		if (error)
			return (error);
	}
	if (ap->a_fflag & FWRITE) {
E 37
D 22
		filetmp.f_data = (caddr_t)vp->v_fifoinfo->fi_writesock;
D 7
	return (soo_ioctl(&filetmp, com, data));
E 7
I 7
	return (soo_ioctl(&filetmp, com, data, p));
E 22
I 22
		filetmp.f_data = (caddr_t)ap->a_vp->v_fifoinfo->fi_writesock;
D 37
	return (soo_ioctl(&filetmp, ap->a_command, ap->a_data, ap->a_p));
E 37
I 37
		error = soo_ioctl(&filetmp, ap->a_command, ap->a_data, ap->a_p);
		if (error)
			return (error);
	}
	return (0);
E 37
E 22
E 7
}
I 21
D 22
#undef vp
#undef com
#undef data
#undef fflag
#undef cred
#undef p
E 22
E 21

/* ARGSUSED */
D 7
fifo_select(vp, which, fflag, cred)
E 7
I 7
D 21
fifo_select(vp, which, fflag, cred, p)
E 7
	struct vnode *vp;
	int which, fflag;
	struct ucred *cred;
I 7
	struct proc *p;
E 21
I 21
D 24
fifo_select (ap)
	struct vop_select_args *ap;
E 24
I 24
fifo_select(ap)
	struct vop_select_args /* {
		struct vnode *a_vp;
		int  a_which;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
#define which (ap->a_which)
#define fflag (ap->a_fflags)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 22
E 21
E 7
{
	struct file filetmp;
I 37
	int ready;
E 37
D 29
	int error;
E 29

D 22
	if (fflag & FREAD)
		filetmp.f_data = (caddr_t)vp->v_fifoinfo->fi_readsock;
E 22
I 22
D 37
	if (ap->a_fflags & FREAD)
E 37
I 37
	if (ap->a_fflags & FREAD) {
E 37
		filetmp.f_data = (caddr_t)ap->a_vp->v_fifoinfo->fi_readsock;
E 22
D 37
	else
E 37
I 37
		ready = soo_select(&filetmp, ap->a_which, ap->a_p);
		if (ready)
			return (ready);
	}
	if (ap->a_fflags & FWRITE) {
E 37
D 22
		filetmp.f_data = (caddr_t)vp->v_fifoinfo->fi_writesock;
D 7
	return (soo_select(&filetmp, which));
E 7
I 7
	return (soo_select(&filetmp, which, p));
E 22
I 22
		filetmp.f_data = (caddr_t)ap->a_vp->v_fifoinfo->fi_writesock;
D 37
	return (soo_select(&filetmp, ap->a_which, ap->a_p));
E 37
I 37
		ready = soo_select(&filetmp, ap->a_which, ap->a_p);
		if (ready)
			return (ready);
	}
	return (0);
E 37
E 22
E 7
}
I 21
D 22
#undef vp
#undef which
#undef fflag
#undef cred
#undef p
E 22
E 21

I 36
int
fifo_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
		struct proc *a_p;
	} */ *ap;
{

	VOP_UNLOCK(ap->a_vp, 0, ap->a_p);
	return (0);
}

E 36
/*
 * This is a noop, simply returning what one has been given.
 */
D 21
fifo_bmap(vp, bn, vpp, bnp)
	struct vnode *vp;
	daddr_t bn;
	struct vnode **vpp;
	daddr_t *bnp;
E 21
I 21
D 24
fifo_bmap (ap)
	struct vop_bmap_args *ap;
E 24
I 24
fifo_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
I 33
		int *a_runp;
E 33
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
#define bn (ap->a_bn)
#define vpp (ap->a_vpp)
#define bnp (ap->a_bnp)
E 22
E 21
{

D 22
	if (vpp != NULL)
		*vpp = vp;
	if (bnp != NULL)
		*bnp = bn;
E 22
I 22
	if (ap->a_vpp != NULL)
		*ap->a_vpp = ap->a_vp;
	if (ap->a_bnp != NULL)
		*ap->a_bnp = ap->a_bn;
I 32
	if (ap->a_runp != NULL)
		*ap->a_runp = 0;
E 32
E 22
D 35
	return (0);
}
I 21
D 22
#undef vp
#undef bn
#undef vpp
#undef bnp
E 22
E 21

/*
 * At the moment we do not do any locking.
 */
/* ARGSUSED */
D 21
fifo_lock(vp)
	struct vnode *vp;
E 21
I 21
D 24
fifo_lock (ap)
	struct vop_lock_args *ap;
E 24
I 24
fifo_lock(ap)
	struct vop_lock_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
E 22
E 21
{

	return (0);
}
I 21
D 22
#undef vp
E 22
E 21

/* ARGSUSED */
D 21
fifo_unlock(vp)
	struct vnode *vp;
E 21
I 21
D 24
fifo_unlock (ap)
	struct vop_unlock_args *ap;
E 24
I 24
fifo_unlock(ap)
	struct vop_unlock_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
E 22
E 21
{

E 35
	return (0);
}
I 21
D 22
#undef vp
E 22
E 21

/*
 * Device close routine
 */
/* ARGSUSED */
D 7
fifo_close(vp, fflag, cred)
E 7
I 7
D 21
fifo_close(vp, fflag, cred, p)
E 7
	register struct vnode *vp;
	int fflag;
	struct ucred *cred;
I 7
	struct proc *p;
E 21
I 21
D 24
fifo_close (ap)
	struct vop_close_args *ap;
E 24
I 24
fifo_close(ap)
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
#define fflag (ap->a_fflag)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 22
E 21
E 7
{
D 22
	register struct fifoinfo *fip = vp->v_fifoinfo;
E 22
I 22
D 23
	register struct fifoinfo *fip = ap->a_vp->v_fifoinfo;
E 23
I 23
	register struct vnode *vp = ap->a_vp;
	register struct fifoinfo *fip = vp->v_fifoinfo;
E 23
E 22
	int error1, error2;

I 37
	if (ap->a_fflag & FREAD) {
		fip->fi_readers--;
		if (fip->fi_readers == 0)
			socantsendmore(fip->fi_writesock);
	}
E 37
D 22
	if (fflag & FWRITE) {
E 22
I 22
	if (ap->a_fflag & FWRITE) {
E 22
		fip->fi_writers--;
		if (fip->fi_writers == 0)
			socantrcvmore(fip->fi_readsock);
D 37
	} else {
		fip->fi_readers--;
		if (fip->fi_readers == 0)
			socantsendmore(fip->fi_writesock);
E 37
	}
D 22
	if (vp->v_usecount > 1)
E 22
I 22
D 23
	if (ap->a_vp->v_usecount > 1)
E 23
I 23
	if (vp->v_usecount > 1)
E 23
E 22
		return (0);
	error1 = soclose(fip->fi_readsock);
	error2 = soclose(fip->fi_writesock);
	FREE(fip, M_VNODE);
D 22
	vp->v_fifoinfo = NULL;
E 22
I 22
D 23
	ap->a_vp->v_fifoinfo = NULL;
E 23
I 23
	vp->v_fifoinfo = NULL;
E 23
E 22
	if (error1)
		return (error1);
	return (error2);
}
I 21
D 22
#undef vp
#undef fflag
#undef cred
#undef p
E 22
E 21

/*
 * Print out the contents of a fifo vnode.
 */
D 21
fifo_print(vp)
	struct vnode *vp;
E 21
I 21
D 24
fifo_print (ap)
	struct vop_print_args *ap;
E 24
I 24
fifo_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
E 22
E 21
{

	printf("tag VT_NON");
D 22
	fifo_printinfo(vp);
E 22
I 22
	fifo_printinfo(ap->a_vp);
E 22
	printf("\n");
}
I 21
D 22
#undef vp
E 22
E 21

/*
 * Print out internal contents of a fifo vnode.
 */
fifo_printinfo(vp)
	struct vnode *vp;
{
	register struct fifoinfo *fip = vp->v_fifoinfo;

	printf(", fifo with %d readers and %d writers",
		fip->fi_readers, fip->fi_writers);
I 26
}

/*
 * Return POSIX pathconf information applicable to fifo's.
 */
fifo_pathconf(ap)
	struct vop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		int *a_retval;
	} */ *ap;
{

	switch (ap->a_name) {
	case _PC_LINK_MAX:
		*ap->a_retval = LINK_MAX;
		return (0);
	case _PC_PIPE_BUF:
		*ap->a_retval = PIPE_BUF;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		return (0);
	default:
		return (EINVAL);
	}
	/* NOTREACHED */
E 26
}

/*
 * Fifo failed operation
 */
fifo_ebadf()
{

	return (EBADF);
I 5
}

/*
 * Fifo advisory byte-level locks.
 */
I 7
/* ARGSUSED */
E 7
D 21
fifo_advlock(vp, id, op, fl, flags)
	struct vnode *vp;
	caddr_t id;
	int op;
	struct flock *fl;
	int flags;
E 21
I 21
D 24
fifo_advlock (ap)
	struct vop_advlock_args *ap;
E 24
I 24
fifo_advlock(ap)
	struct vop_advlock_args /* {
		struct vnode *a_vp;
		caddr_t  a_id;
		int  a_op;
		struct flock *a_fl;
		int  a_flags;
	} */ *ap;
E 24
D 22
#define vp (ap->a_vp)
#define id (ap->a_id)
#define op (ap->a_op)
#define fl (ap->a_fl)
#define flags (ap->a_flags)
E 22
E 21
{

	return (EOPNOTSUPP);
E 5
}
I 21
D 22
#undef vp
#undef id
#undef op
#undef fl
#undef flags
E 22
E 21

/*
 * Fifo bad operation
 */
fifo_badop()
{

	panic("fifo_badop called");
	/* NOTREACHED */
D 6
}

/*
 * Fifo null operation
 */
fifo_nullop()
{

	return (0);
E 6
}
E 1
