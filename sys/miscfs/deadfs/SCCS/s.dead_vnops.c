h65432
s 00022/00020/00308
d D 8.3 95/05/14 00:38:44 mckusick 36 35
c convert locking to new model; cleanups
e
s 00002/00002/00326
d D 8.2 94/11/21 15:02:33 mckusick 35 34
c return EOF for read on dead ttys
e
s 00002/00002/00326
d D 8.1 93/06/10 23:35:28 bostic 34 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00326
d D 7.25 93/05/25 15:39:27 mckusick 33 32
c add pathconf
e
s 00002/00001/00324
d D 7.24 92/10/07 17:18:13 margo 32 31
c Add argument to VOP_BMAP.
e
s 00007/00007/00318
d D 7.23 92/07/12 14:21:06 mckusick 31 30
c new include format
e
s 00063/00026/00262
d D 7.22 92/07/03 01:35:34 mckusick 30 29
c add parameter declarations; delete USES
e
s 00002/00002/00286
d D 7.21 92/05/31 21:23:16 heideman 29 28
c syntactic fixups
e
s 00002/00002/00286
d D 7.20 92/05/15 15:36:23 heideman 28 27
c some VOP's rplaced with VCALL
e
s 00014/00080/00274
d D 7.19 92/05/15 13:56:08 heideman 27 26
c vnodeop argument macro expansion
e
s 00176/00259/00178
d D 7.18 92/05/14 17:31:10 heideman 26 17
c vnode interface conversion
e
s 00176/00259/00178
d R 7.18 92/05/14 15:45:00 heideman 25 17
c vnode interface conversion
e
s 00176/00259/00178
d R 7.18 92/05/14 14:50:12 heideman 24 17
c vnode interface conversion
e
s 00176/00260/00177
d R 7.18 92/05/14 12:54:13 heideman 23 17
c vnode interface conversion
e
s 00175/00256/00181
d R 7.18 92/05/14 11:51:33 heideman 22 17
c vnode interface conversion
e
s 00175/00256/00181
d R 7.18 92/05/14 10:31:47 heideman 21 17
c vnode interface conversion
e
s 00175/00256/00181
d R 7.18 92/05/13 23:10:30 heideman 20 17
c vnode interface conversion
e
s 00175/00256/00181
d R 7.18 92/05/13 18:56:46 heideman 19 17
c vnode interface conversion
e
s 00175/00256/00181
d R 7.18 92/05/13 18:28:49 heideman 18 17
c vnode interface conversion
e
s 00002/00001/00435
d D 7.17 92/04/21 13:10:19 mckusick 17 16
c VOP_TRUNCATE now takes a cred argument
e
s 00001/00001/00435
d D 7.16 92/04/21 11:40:07 mckusick 16 15
c vop_truncate takes off_t rather than u_long length op
e
s 00042/00033/00394
d D 7.15 92/02/03 23:24:48 heideman 15 14
c new caling convention for VOP ops
e
s 00036/00000/00391
d D 7.14 91/11/05 15:34:24 mckusick 14 13
c reorganization to move ufsmount ops to be vnode ops
e
s 00176/00041/00215
d D 7.13 91/04/15 23:34:03 mckusick 13 12
c add prototypes for dead vnode ops; add appropriate proc pointers
e
s 00001/00000/00255
d D 7.12 91/02/01 16:21:34 mckusick 12 11
c add POSIX-style byte-level record locking
e
s 00001/00000/00254
d D 7.11 90/08/24 08:49:48 mckusick 11 10
c lint
e
s 00001/00011/00253
d D 7.10 90/06/28 21:17:59 bostic 10 9
c new copyright notice
e
s 00002/00002/00262
d D 7.9 90/02/21 00:08:46 mckusick 9 8
c dead_select gets the file flags
e
s 00013/00000/00251
d D 7.8 90/01/15 18:40:08 mckusick 8 7
c add print and islocked vnode ops
e
s 00001/00000/00250
d D 7.7 90/01/02 19:48:17 mckusick 7 6
c must do biodone on error
e
s 00014/00009/00236
d D 7.6 89/11/22 21:43:01 mckusick 6 5
c read/write no longer take an offp
e
s 00023/00066/00222
d D 7.5 89/11/12 10:40:01 mckusick 5 4
c pull lock check out into a subroutine
e
s 00003/00001/00285
d D 7.4 89/11/12 10:29:40 mckusick 4 3
c set error bit on buffer in dead_strategy
e
s 00027/00001/00259
d D 7.3 89/11/10 12:34:47 mckusick 3 2
c add bmap entry for dead texts
e
s 00015/00005/00245
d D 7.2 89/11/03 09:58:22 mckusick 2 1
c make provision for stat, readdir, and readlink on a dead vnode
e
s 00250/00000/00000
d D 7.1 89/11/02 17:33:50 mckusick 1 0
c date and time created 89/11/02 17:33:50 by mckusick
e
u
U
t
T
I 1
/*
D 34
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 34
I 34
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 34
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
 *
 *	%W% (Berkeley) %G%
 */

D 31
#include "param.h"
I 13
#include "systm.h"
E 13
#include "time.h"
#include "vnode.h"
#include "errno.h"
#include "namei.h"
#include "buf.h"
E 31
I 31
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/vnode.h>
#include <sys/errno.h>
#include <sys/namei.h>
#include <sys/buf.h>
E 31

D 13
int	dead_lookup(),
	dead_open(),
	dead_read(),
	dead_write(),
	dead_strategy(),
	dead_ioctl(),
	dead_select(),
	dead_lock(),
I 3
	dead_bmap(),
I 8
	dead_print(),
E 8
E 3
I 2
	dead_ebadf(),
E 2
	dead_badop(),
	dead_nullop();
E 13
I 13
/*
 * Prototypes for dead operations on vnodes.
 */
int	dead_badop(),
	dead_ebadf();
D 26
int	dead_lookup __P((
D 15
		struct vnode *vp,
		struct nameidata *ndp,
		struct proc *p));
E 15
I 15
		struct vnode *dvp,
		struct vnode **vpp,
		struct componentname *cnp));
E 15
#define dead_create ((int (*) __P(( \
D 15
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct proc *p))) dead_badop)
E 15
I 15
		struct vnode *dvp, \
 		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) dead_badop)
E 15
#define dead_mknod ((int (*) __P(( \
D 15
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) dead_badop)
E 15
I 15
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) dead_badop)
E 15
int	dead_open __P((
		struct vnode *vp,
		int mode,
		struct ucred *cred,
		struct proc *p));
#define dead_close ((int (*) __P(( \
		struct vnode *vp, \
		int fflag, \
		struct ucred *cred, \
		struct proc *p))) nullop)
#define dead_access ((int (*) __P(( \
		struct vnode *vp, \
		int mode, \
		struct ucred *cred, \
		struct proc *p))) dead_ebadf)
#define dead_getattr ((int (*) __P(( \
		struct vnode *vp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) dead_ebadf)
#define dead_setattr ((int (*) __P(( \
		struct vnode *vp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) dead_ebadf)
int	dead_read __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
int	dead_write __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
int	dead_ioctl __P((
		struct vnode *vp,
		int command,
		caddr_t data,
		int fflag,
		struct ucred *cred,
		struct proc *p));
int	dead_select __P((
		struct vnode *vp,
		int which,
		int fflags,
		struct ucred *cred,
		struct proc *p));
#define dead_mmap ((int (*) __P(( \
		struct vnode *vp, \
		int fflags, \
		struct ucred *cred, \
		struct proc *p))) dead_badop)
#define dead_fsync ((int (*) __P(( \
		struct vnode *vp, \
		int fflags, \
		struct ucred *cred, \
		int waitfor, \
		struct proc *p))) nullop)
#define dead_seek ((int (*) __P(( \
		struct vnode *vp, \
		off_t oldoff, \
		off_t newoff, \
		struct ucred *cred))) nullop)
#define dead_remove ((int (*) __P(( \
D 15
		struct nameidata *ndp, \
		struct proc *p))) dead_badop)
E 15
I 15
		struct vnode *dvp, \
	        struct vnode *vp, \
		struct componentname *cnp))) dead_badop)
E 15
#define dead_link ((int (*) __P(( \
D 15
		struct vnode *vp, \
		struct nameidata *ndp, \
		struct proc *p))) dead_badop)
E 15
I 15
		register struct vnode *vp, \
		struct vnode *tdvp, \
		struct componentname *cnp))) dead_badop)
E 15
#define dead_rename ((int (*) __P(( \
D 15
		struct nameidata *fndp, \
		struct nameidata *tdnp, \
		struct proc *p))) dead_badop)
E 15
I 15
		struct vnode *fdvp, \
	        struct vnode *fvp, \
		struct componentname *fcnp, \
		struct vnode *tdvp, \
		struct vnode *tvp, \
		struct componentname *tcnp))) dead_badop)
E 15
#define dead_mkdir ((int (*) __P(( \
D 15
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct proc *p))) dead_badop)
E 15
I 15
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) dead_badop)
E 15
#define dead_rmdir ((int (*) __P(( \
D 15
		struct nameidata *ndp, \
		struct proc *p))) dead_badop)
E 15
I 15
		struct vnode *dvp, \
		struct vnode *vp, \
		struct componentname *cnp))) dead_badop)
E 15
#define dead_symlink ((int (*) __P(( \
D 15
		struct nameidata *ndp, \
E 15
I 15
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
E 15
		struct vattr *vap, \
D 15
		char *target, \
		struct proc *p))) dead_badop)
E 15
I 15
		char *target))) dead_badop)
E 15
#define dead_readdir ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		struct ucred *cred, \
		int *eofflagp))) dead_ebadf)
#define dead_readlink ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		struct ucred *cred))) dead_ebadf)
#define dead_abortop ((int (*) __P(( \
D 15
		struct nameidata *ndp))) dead_badop)
E 15
I 15
		struct vnode *dvp, \
		struct componentname *cnp))) dead_badop)
E 15
#define dead_inactive ((int (*) __P(( \
		struct vnode *vp, \
		struct proc *p))) nullop)
#define dead_reclaim ((int (*) __P(( \
		struct vnode *vp))) nullop)
int	dead_lock __P((
		struct vnode *vp));
#define dead_unlock ((int (*) __P(( \
		struct vnode *vp))) nullop)
int	dead_bmap __P((
		struct vnode *vp,
		daddr_t bn,
		struct vnode **vpp,
		daddr_t *bnp));
int	dead_strategy __P((
		struct buf *bp));
int	dead_print __P((
		struct vnode *vp));
#define dead_islocked ((int (*) __P(( \
		struct vnode *vp))) nullop)
#define dead_advlock ((int (*) __P(( \
		struct vnode *vp, \
		caddr_t id, \
		int op, \
		struct flock *fl, \
		int flags))) dead_ebadf)
I 14
#define dead_blkatoff ((int (*) __P(( \
		struct vnode *vp, \
		off_t offset, \
		char **res, \
		struct buf **bpp))) dead_badop)
#define dead_vget ((int (*) __P(( \
		struct mount *mp, \
		ino_t ino, \
		struct vnode **vpp))) dead_badop)
#define dead_valloc ((int (*) __P(( \
		struct vnode *pvp, \
		int mode, \
		struct ucred *cred, \
		struct vnode **vpp))) dead_badop)
#define dead_vfree ((void (*) __P(( \
		struct vnode *pvp, \
		ino_t ino, \
		int mode))) dead_badop)
#define dead_truncate ((int (*) __P(( \
		struct vnode *vp, \
D 16
		u_long length, \
E 16
I 16
		off_t length, \
E 16
D 17
		int flags))) nullop)
E 17
I 17
		int flags, \
		struct ucred *cred))) nullop)
E 17
#define dead_update ((int (*) __P(( \
		struct vnode *vp, \
		struct timeval *ta, \
		struct timeval *tm, \
		int waitfor))) nullop)
#define dead_bwrite ((int (*) __P(( \
		struct buf *bp))) nullop)
E 26
I 26
int	dead_lookup __P((struct vop_lookup_args *));
#define dead_create ((int (*) __P((struct  vop_create_args *)))dead_badop)
#define dead_mknod ((int (*) __P((struct  vop_mknod_args *)))dead_badop)
int	dead_open __P((struct vop_open_args *));
#define dead_close ((int (*) __P((struct  vop_close_args *)))nullop)
#define dead_access ((int (*) __P((struct  vop_access_args *)))dead_ebadf)
#define dead_getattr ((int (*) __P((struct  vop_getattr_args *)))dead_ebadf)
#define dead_setattr ((int (*) __P((struct  vop_setattr_args *)))dead_ebadf)
int	dead_read __P((struct vop_read_args *));
int	dead_write __P((struct vop_write_args *));
int	dead_ioctl __P((struct vop_ioctl_args *));
int	dead_select __P((struct vop_select_args *));
#define dead_mmap ((int (*) __P((struct  vop_mmap_args *)))dead_badop)
#define dead_fsync ((int (*) __P((struct  vop_fsync_args *)))nullop)
#define dead_seek ((int (*) __P((struct  vop_seek_args *)))nullop)
#define dead_remove ((int (*) __P((struct  vop_remove_args *)))dead_badop)
#define dead_link ((int (*) __P((struct  vop_link_args *)))dead_badop)
#define dead_rename ((int (*) __P((struct  vop_rename_args *)))dead_badop)
#define dead_mkdir ((int (*) __P((struct  vop_mkdir_args *)))dead_badop)
#define dead_rmdir ((int (*) __P((struct  vop_rmdir_args *)))dead_badop)
#define dead_symlink ((int (*) __P((struct  vop_symlink_args *)))dead_badop)
#define dead_readdir ((int (*) __P((struct  vop_readdir_args *)))dead_ebadf)
#define dead_readlink ((int (*) __P((struct  vop_readlink_args *)))dead_ebadf)
#define dead_abortop ((int (*) __P((struct  vop_abortop_args *)))dead_badop)
#define dead_inactive ((int (*) __P((struct  vop_inactive_args *)))nullop)
#define dead_reclaim ((int (*) __P((struct  vop_reclaim_args *)))nullop)
int	dead_lock __P((struct vop_lock_args *));
D 36
#define dead_unlock ((int (*) __P((struct  vop_unlock_args *)))nullop)
E 36
I 36
#define dead_unlock ((int (*) __P((struct vop_unlock_args *)))vop_nounlock)
E 36
int	dead_bmap __P((struct vop_bmap_args *));
int	dead_strategy __P((struct vop_strategy_args *));
int	dead_print __P((struct vop_print_args *));
D 36
#define dead_islocked ((int (*) __P((struct  vop_islocked_args *)))nullop)
E 36
I 36
#define dead_islocked ((int(*) __P((struct vop_islocked_args *)))vop_noislocked)
E 36
I 33
#define dead_pathconf ((int (*) __P((struct  vop_pathconf_args *)))dead_ebadf)
E 33
#define dead_advlock ((int (*) __P((struct  vop_advlock_args *)))dead_ebadf)
#define dead_blkatoff ((int (*) __P((struct  vop_blkatoff_args *)))dead_badop)
D 30
#define dead_vget ((int (*) __P((struct  vop_vget_args *)))dead_badop)
E 30
#define dead_valloc ((int (*) __P((struct  vop_valloc_args *)))dead_badop)
#define dead_vfree ((int (*) __P((struct  vop_vfree_args *)))dead_badop)
#define dead_truncate ((int (*) __P((struct  vop_truncate_args *)))nullop)
#define dead_update ((int (*) __P((struct  vop_update_args *)))nullop)
#define dead_bwrite ((int (*) __P((struct  vop_bwrite_args *)))nullop)
E 26
E 14
E 13

D 26
struct vnodeops dead_vnodeops = {
	dead_lookup,	/* lookup */
D 13
	dead_badop,	/* create */
	dead_badop,	/* mknod */
E 13
I 13
	dead_create,	/* create */
	dead_mknod,	/* mknod */
E 13
	dead_open,	/* open */
D 13
	dead_nullop,	/* close */
D 2
	dead_badop,	/* access */
	dead_badop,	/* getattr */
	dead_badop,	/* setattr */
E 2
I 2
	dead_ebadf,	/* access */
	dead_ebadf,	/* getattr */
	dead_ebadf,	/* setattr */
E 13
I 13
	dead_close,	/* close */
	dead_access,	/* access */
	dead_getattr,	/* getattr */
	dead_setattr,	/* setattr */
E 13
E 2
	dead_read,	/* read */
	dead_write,	/* write */
	dead_ioctl,	/* ioctl */
	dead_select,	/* select */
D 13
	dead_badop,	/* mmap */
	dead_nullop,	/* fsync */
	dead_nullop,	/* seek */
	dead_badop,	/* remove */
	dead_badop,	/* link */
	dead_badop,	/* rename */
	dead_badop,	/* mkdir */
	dead_badop,	/* rmdir */
	dead_badop,	/* symlink */
D 2
	dead_badop,	/* readdir */
	dead_badop,	/* readlink */
E 2
I 2
	dead_ebadf,	/* readdir */
	dead_ebadf,	/* readlink */
E 2
	dead_badop,	/* abortop */
	dead_nullop,	/* inactive */
	dead_nullop,	/* reclaim */
E 13
I 13
	dead_mmap,	/* mmap */
	dead_fsync,	/* fsync */
	dead_seek,	/* seek */
	dead_remove,	/* remove */
	dead_link,	/* link */
	dead_rename,	/* rename */
	dead_mkdir,	/* mkdir */
	dead_rmdir,	/* rmdir */
	dead_symlink,	/* symlink */
	dead_readdir,	/* readdir */
	dead_readlink,	/* readlink */
	dead_abortop,	/* abortop */
	dead_inactive,	/* inactive */
	dead_reclaim,	/* reclaim */
E 13
	dead_lock,	/* lock */
D 13
	dead_nullop,	/* unlock */
E 13
I 13
	dead_unlock,	/* unlock */
E 13
D 3
	dead_badop,	/* bmap */
E 3
I 3
	dead_bmap,	/* bmap */
E 3
	dead_strategy,	/* strategy */
I 8
	dead_print,	/* print */
D 13
	dead_nullop,	/* islocked */
I 12
	dead_ebadf,	/* advlock */
E 13
I 13
	dead_islocked,	/* islocked */
	dead_advlock,	/* advlock */
I 14
	dead_blkatoff,	/* blkatoff */
	dead_vget,	/* vget */
	dead_valloc,	/* valloc */
	dead_vfree,	/* vfree */
	dead_truncate,	/* truncate */
	dead_update,	/* update */
	dead_bwrite,	/* bwrite */
E 26
I 26
int (**dead_vnodeop_p)();
struct vnodeopv_entry_desc dead_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, dead_lookup },	/* lookup */
	{ &vop_create_desc, dead_create },	/* create */
	{ &vop_mknod_desc, dead_mknod },	/* mknod */
D 36
	{ &vop_open_desc, dead_open },	/* open */
E 36
I 36
	{ &vop_open_desc, dead_open },		/* open */
E 36
	{ &vop_close_desc, dead_close },	/* close */
	{ &vop_access_desc, dead_access },	/* access */
	{ &vop_getattr_desc, dead_getattr },	/* getattr */
	{ &vop_setattr_desc, dead_setattr },	/* setattr */
D 36
	{ &vop_read_desc, dead_read },	/* read */
E 36
I 36
	{ &vop_read_desc, dead_read },		/* read */
E 36
	{ &vop_write_desc, dead_write },	/* write */
	{ &vop_ioctl_desc, dead_ioctl },	/* ioctl */
	{ &vop_select_desc, dead_select },	/* select */
D 36
	{ &vop_mmap_desc, dead_mmap },	/* mmap */
E 36
I 36
	{ &vop_mmap_desc, dead_mmap },		/* mmap */
E 36
	{ &vop_fsync_desc, dead_fsync },	/* fsync */
D 36
	{ &vop_seek_desc, dead_seek },	/* seek */
E 36
I 36
	{ &vop_seek_desc, dead_seek },		/* seek */
E 36
	{ &vop_remove_desc, dead_remove },	/* remove */
D 36
	{ &vop_link_desc, dead_link },	/* link */
E 36
I 36
	{ &vop_link_desc, dead_link },		/* link */
E 36
	{ &vop_rename_desc, dead_rename },	/* rename */
	{ &vop_mkdir_desc, dead_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, dead_rmdir },	/* rmdir */
	{ &vop_symlink_desc, dead_symlink },	/* symlink */
	{ &vop_readdir_desc, dead_readdir },	/* readdir */
	{ &vop_readlink_desc, dead_readlink },	/* readlink */
	{ &vop_abortop_desc, dead_abortop },	/* abortop */
	{ &vop_inactive_desc, dead_inactive },	/* inactive */
	{ &vop_reclaim_desc, dead_reclaim },	/* reclaim */
D 36
	{ &vop_lock_desc, dead_lock },	/* lock */
E 36
I 36
	{ &vop_lock_desc, dead_lock },		/* lock */
E 36
	{ &vop_unlock_desc, dead_unlock },	/* unlock */
D 36
	{ &vop_bmap_desc, dead_bmap },	/* bmap */
E 36
I 36
	{ &vop_bmap_desc, dead_bmap },		/* bmap */
E 36
	{ &vop_strategy_desc, dead_strategy },	/* strategy */
	{ &vop_print_desc, dead_print },	/* print */
	{ &vop_islocked_desc, dead_islocked },	/* islocked */
I 33
	{ &vop_pathconf_desc, dead_pathconf },	/* pathconf */
E 33
	{ &vop_advlock_desc, dead_advlock },	/* advlock */
	{ &vop_blkatoff_desc, dead_blkatoff },	/* blkatoff */
D 30
	{ &vop_vget_desc, dead_vget },	/* vget */
E 30
	{ &vop_valloc_desc, dead_valloc },	/* valloc */
	{ &vop_vfree_desc, dead_vfree },	/* vfree */
	{ &vop_truncate_desc, dead_truncate },	/* truncate */
	{ &vop_update_desc, dead_update },	/* update */
	{ &vop_bwrite_desc, dead_bwrite },	/* bwrite */
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 26
E 14
E 13
E 12
E 8
};
I 26
struct vnodeopv_desc dead_vnodeop_opv_desc =
	{ &dead_vnodeop_p, dead_vnodeop_entries };
E 26

/*
 * Trivial lookup routine that always fails.
 */
D 13
dead_lookup(vp, ndp)
E 13
I 13
/* ARGSUSED */
D 15
dead_lookup(vp, ndp, p)
E 13
	struct vnode *vp;
	struct nameidata *ndp;
I 13
	struct proc *p;
E 15
I 15
int
D 26
dead_lookup(dvp, vpp, cnp)
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
E 26
I 26
D 30
dead_lookup (ap)
	struct vop_lookup_args *ap;
E 30
I 30
dead_lookup(ap)
	struct vop_lookup_args /* {
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
	} */ *ap;
E 30
D 27
#define dvp (ap->a_dvp)
#define vpp (ap->a_vpp)
#define cnp (ap->a_cnp)
E 27
E 26
E 15
E 13
{

D 15
	ndp->ni_dvp = vp;
	ndp->ni_vp = NULL;
E 15
I 15
D 27
	*vpp = NULL;
E 27
I 27
	*ap->a_vpp = NULL;
E 27
E 15
	return (ENOTDIR);
}
I 26
D 27
#undef dvp
#undef vpp
#undef cnp
E 27
E 26

/*
 * Open always fails as if device did not exist.
 */
/* ARGSUSED */
D 13
dead_open(vp, mode, cred)
E 13
I 13
D 26
dead_open(vp, mode, cred, p)
E 13
	struct vnode *vp;
	int mode;
	struct ucred *cred;
I 13
	struct proc *p;
E 26
I 26
D 30
dead_open (ap)
	struct vop_open_args *ap;
E 30
I 30
dead_open(ap)
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 30
D 27
#define vp (ap->a_vp)
#define mode (ap->a_mode)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 27
E 26
E 13
{

	return (ENXIO);
}
I 26
D 27
#undef vp
#undef mode
#undef cred
#undef p
E 27
E 26

/*
 * Vnode op for read
 */
D 6
dead_read(vp, uio, offp, ioflag, cred)
E 6
I 6
/* ARGSUSED */
D 26
dead_read(vp, uio, ioflag, cred)
E 6
	struct vnode *vp;
	struct uio *uio;
D 6
	off_t *offp;
E 6
	int ioflag;
	struct ucred *cred;
E 26
I 26
D 30
dead_read (ap)
	struct vop_read_args *ap;
E 30
I 30
dead_read(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 30
D 27
#define vp (ap->a_vp)
#define uio (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 27
E 26
{
D 5
	int locked = 0;
E 5

D 5
	/*
	 * We have to wait during times when the vnode is
	 * in a state of change.
	 */
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
		locked = 1;
	}
	if (!locked)
E 5
I 5
D 6
	if (!chkvnlock(vp))
E 6
I 6
D 27
	if (chkvnlock(vp))
E 27
I 27
	if (chkvnlock(ap->a_vp))
E 27
		panic("dead_read: lock");
	/*
D 35
	 * Return EOF for character devices, EIO for others
E 35
I 35
	 * Return EOF for tty devices, EIO for others
E 35
	 */
D 27
	if (vp->v_type != VCHR)
E 27
I 27
D 35
	if (ap->a_vp->v_type != VCHR)
E 35
I 35
	if ((ap->a_vp->v_flag & VISTTY) == 0)
E 35
E 27
E 6
E 5
		return (EIO);
D 6
	return (VOP_READ(vp, uio, offp, ioflag, cred));
E 6
I 6
	return (0);
E 6
}
I 26
D 27
#undef vp
#undef uio
#undef ioflag
#undef cred
E 27
E 26

/*
 * Vnode op for write
 */
D 6
dead_write(vp, uio, offp, ioflag, cred)
E 6
I 6
/* ARGSUSED */
D 26
dead_write(vp, uio, ioflag, cred)
E 6
	register struct vnode *vp;
	struct uio *uio;
D 6
	off_t *offp;
E 6
	int ioflag;
	struct ucred *cred;
E 26
I 26
D 30
dead_write (ap)
	struct vop_write_args *ap;
E 30
I 30
dead_write(ap)
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 30
D 27
#define vp (ap->a_vp)
#define uio (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 27
E 26
{
D 5
	int locked = 0;
E 5

D 5
	/*
	 * We have to wait during times when the vnode is
	 * in a state of change.
	 */
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
		locked = 1;
	}
	if (!locked)
E 5
I 5
D 6
	if (!chkvnlock(vp))
E 5
		return (EIO);
	return (VOP_WRITE(vp, uio, offp, ioflag, cred));
E 6
I 6
D 27
	if (chkvnlock(vp))
E 27
I 27
	if (chkvnlock(ap->a_vp))
E 27
		panic("dead_write: lock");
	return (EIO);
E 6
}
I 26
D 27
#undef vp
#undef uio
#undef ioflag
#undef cred
E 27
E 26

/*
 * Device ioctl operation.
 */
/* ARGSUSED */
D 13
dead_ioctl(vp, com, data, fflag, cred)
E 13
I 13
D 26
dead_ioctl(vp, com, data, fflag, cred, p)
E 13
	struct vnode *vp;
	register int com;
	caddr_t data;
	int fflag;
	struct ucred *cred;
I 13
	struct proc *p;
E 26
I 26
D 30
dead_ioctl (ap)
	struct vop_ioctl_args *ap;
E 30
I 30
dead_ioctl(ap)
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
		int  a_command;
		caddr_t  a_data;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 30
D 27
#define vp (ap->a_vp)
#define com (ap->a_command)
#define data (ap->a_data)
#define fflag (ap->a_fflag)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 27
E 26
E 13
{
I 26
D 30
	USES_VOP_IOCTL;
E 30
E 26
D 5
	int locked = 0;
E 5

D 5
	/*
	 * We have to wait during times when the vnode is
	 * in a state of change.
	 */
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
		locked = 1;
	}
	if (!locked)
E 5
I 5
D 27
	if (!chkvnlock(vp))
E 27
I 27
	if (!chkvnlock(ap->a_vp))
E 27
E 5
		return (EBADF);
D 13
	return (VOP_IOCTL(vp, com, data, fflag, cred));
E 13
I 13
D 27
	return (VOP_IOCTL(vp, com, data, fflag, cred, p));
E 27
I 27
D 28
	return (VOP_IOCTL(ap->a_vp, ap->a_command, ap->a_data, ap->a_fflag, ap->a_cred, ap->a_p));
E 28
I 28
D 29
	return (VCALL(ap->a_vp, VDESC(vop_ioctl), ap));
E 29
I 29
	return (VCALL(ap->a_vp, VOFFSET(vop_ioctl), ap));
E 29
E 28
E 27
E 13
}
I 26
D 27
#undef vp
#undef com
#undef data
#undef fflag
#undef cred
#undef p
E 27
E 26

/* ARGSUSED */
D 9
dead_select(vp, which, cred)
E 9
I 9
D 13
dead_select(vp, which, fflags, cred)
E 13
I 13
D 26
dead_select(vp, which, fflags, cred, p)
E 13
E 9
	struct vnode *vp;
D 9
	int which;
E 9
I 9
	int which, fflags;
E 9
	struct ucred *cred;
I 13
	struct proc *p;
E 26
I 26
D 30
dead_select (ap)
	struct vop_select_args *ap;
E 30
I 30
dead_select(ap)
	struct vop_select_args /* {
		struct vnode *a_vp;
		int  a_which;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 30
D 27
#define vp (ap->a_vp)
#define which (ap->a_which)
#define fflags (ap->a_fflags)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 27
E 26
E 13
{

	/*
	 * Let the user find out that the descriptor is gone.
	 */
	return (1);
}
I 26
D 27
#undef vp
#undef which
#undef fflags
#undef cred
#undef p
E 27
E 26

/*
 * Just call the device strategy routine
 */
D 26
dead_strategy(bp)
	register struct buf *bp;
E 26
I 26
D 30
dead_strategy (ap)
	struct vop_strategy_args *ap;
E 30
I 30
dead_strategy(ap)
	struct vop_strategy_args /* {
		struct buf *a_bp;
	} */ *ap;
E 30
D 27
#define bp (ap->a_bp)
E 27
E 26
{
I 26
D 30
	USES_VOP_STRATEGY;
E 30
E 26
D 5
	int locked = 0;
E 5

D 5
	/*
	 * We have to wait during times when the vnode is
	 * in a state of change.
	 */
	while (bp->b_vp->v_flag & VXLOCK) {
		bp->b_vp->v_flag |= VXWANT;
		sleep((caddr_t)bp->b_vp, PINOD);
		locked = 1;
	}
D 4
	if (!locked)
E 4
I 4
	if (!locked) {
E 5
I 5
D 27
	if (bp->b_vp == NULL || !chkvnlock(bp->b_vp)) {
E 5
		bp->b_flags |= B_ERROR;
I 7
		biodone(bp);
E 27
I 27
	if (ap->a_bp->b_vp == NULL || !chkvnlock(ap->a_bp->b_vp)) {
		ap->a_bp->b_flags |= B_ERROR;
		biodone(ap->a_bp);
E 27
E 7
E 4
		return (EIO);
I 4
	}
E 4
D 27
	return (VOP_STRATEGY(bp));
E 27
I 27
	return (VOP_STRATEGY(ap->a_bp));
E 27
}
I 26
D 27
#undef bp
E 27
E 26

/*
 * Wait until the vnode has finished changing state.
 */
D 26
dead_lock(vp)
	struct vnode *vp;
E 26
I 26
D 30
dead_lock (ap)
	struct vop_lock_args *ap;
E 30
I 30
dead_lock(ap)
	struct vop_lock_args /* {
		struct vnode *a_vp;
I 36
		int a_flags;
		struct proc *a_p;
E 36
	} */ *ap;
E 30
D 27
#define vp (ap->a_vp)
E 27
E 26
{
I 36
	struct vnode *vp = ap->a_vp;
E 36
I 26
D 30
	USES_VOP_LOCK;
E 30
E 26
D 5
	int locked = 0;
E 5

D 5
	/*
	 * We have to wait during times when the vnode is
	 * in a state of change.
	 */
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
		locked = 1;
	}
	if (!locked)
E 5
I 5
D 27
	if (!chkvnlock(vp))
E 27
I 27
D 36
	if (!chkvnlock(ap->a_vp))
E 36
I 36
	/*
	 * Since we are not using the lock manager, we must clear
	 * the interlock here.
	 */
	if (ap->a_flags & LK_INTERLOCK) {
		simple_unlock(&vp->v_interlock);
		ap->a_flags &= ~LK_INTERLOCK;
	}
	if (!chkvnlock(vp))
E 36
E 27
E 5
		return (0);
D 27
	return (VOP_LOCK(vp));
E 27
I 27
D 28
	return (VOP_LOCK(ap->a_vp));
E 28
I 28
D 29
	return (VCALL(ap->a_vp, VDESC(vop_lock), ap));
E 29
I 29
D 36
	return (VCALL(ap->a_vp, VOFFSET(vop_lock), ap));
E 36
I 36
	return (VCALL(vp, VOFFSET(vop_lock), ap));
E 36
E 29
E 28
E 27
I 3
}
I 26
D 27
#undef vp
E 27
E 26

/*
 * Wait until the vnode has finished changing state.
 */
D 26
dead_bmap(vp, bn, vpp, bnp)
	struct vnode *vp;
	daddr_t bn;
	struct vnode **vpp;
	daddr_t *bnp;
E 26
I 26
D 30
dead_bmap (ap)
	struct vop_bmap_args *ap;
E 30
I 30
dead_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
I 32
		int *a_runp;
E 32
	} */ *ap;
E 30
D 27
#define vp (ap->a_vp)
#define bn (ap->a_bn)
#define vpp (ap->a_vpp)
#define bnp (ap->a_bnp)
E 27
E 26
{
I 26
D 30
	USES_VOP_BMAP;
E 30
E 26
D 5
	int locked = 0;
E 5

D 5
	/*
	 * We have to wait during times when the vnode is
	 * in a state of change.
	 */
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
		locked = 1;
	}
	if (!locked)
E 5
I 5
D 27
	if (!chkvnlock(vp))
E 27
I 27
	if (!chkvnlock(ap->a_vp))
E 27
E 5
		return (EIO);
D 27
	return (VOP_BMAP(vp, bn, vpp, bnp));
E 27
I 27
D 32
	return (VOP_BMAP(ap->a_vp, ap->a_bn, ap->a_vpp, ap->a_bnp));
E 32
I 32
	return (VOP_BMAP(ap->a_vp, ap->a_bn, ap->a_vpp, ap->a_bnp, ap->a_runp));
E 32
E 27
I 8
}
I 26
D 27
#undef vp
#undef bn
#undef vpp
#undef bnp
E 27
E 26

/*
 * Print out the contents of a dead vnode.
 */
I 11
/* ARGSUSED */
E 11
D 26
dead_print(vp)
	struct vnode *vp;
E 26
I 26
D 30
dead_print (ap)
	struct vop_print_args *ap;
E 30
I 30
dead_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 30
D 27
#define vp (ap->a_vp)
E 27
E 26
{

	printf("tag VT_NON, dead vnode\n");
E 8
E 3
I 2
}
I 26
D 27
#undef vp
E 27
E 26

/*
 * Empty vnode failed operation
 */
dead_ebadf()
{

	return (EBADF);
E 2
}

/*
 * Empty vnode bad operation
 */
dead_badop()
{

	panic("dead_badop called");
	/* NOTREACHED */
D 36
}

/*
 * Empty vnode null operation
 */
dead_nullop()
{

	return (0);
E 36
I 5
}

/*
 * We have to wait during times when the vnode is
 * in a state of change.
 */
chkvnlock(vp)
	register struct vnode *vp;
{
	int locked = 0;

	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
		locked = 1;
	}
	return (locked);
E 5
}
E 1
