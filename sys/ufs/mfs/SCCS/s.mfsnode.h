h15523
s 00003/00003/00057
d D 8.3 95/05/19 23:50:22 mckusick 24 23
c use nolock* functions
e
s 00001/00000/00059
d D 8.2 93/08/11 13:22:49 mckusick 23 22
c add mfs_pathconf
e
s 00002/00002/00057
d D 8.1 93/06/11 16:27:49 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00059
d D 7.13 92/07/03 01:51:40 mckusick 21 20
c delete mfs_vget
e
s 00000/00001/00060
d D 7.12 92/06/25 13:22:08 mckusick 20 19
c delete mfs_fsync define as it is now a real function
e
s 00002/00002/00059
d D 7.11 92/05/27 16:13:37 mckusick 19 17
c need real bwrite routine
e
s 00002/00002/00059
d R 7.11 92/05/27 16:07:45 mckusick 18 17
c need real bwrite routine
e
s 00032/00145/00029
d D 7.10 92/05/14 17:41:59 heideman 17 9
c vnode interface conversion
e
s 00032/00145/00029
d R 7.10 92/05/14 16:00:53 heideman 16 9
c vnode interface conversion
e
s 00032/00145/00029
d R 7.10 92/05/14 14:59:58 heideman 15 9
c vnode interface conversion
e
s 00032/00145/00029
d R 7.10 92/05/14 13:08:26 heideman 14 9
c vnode interface conversion
e
s 00031/00141/00033
d R 7.10 92/05/14 12:04:27 heideman 13 9
c vnode interface conversion
e
s 00031/00141/00033
d R 7.10 92/05/14 11:28:00 heideman 12 9
c vnode interface conversion
e
s 00031/00141/00033
d R 7.10 92/05/13 23:23:46 heideman 11 9
c vnode interface conversion
e
s 00031/00141/00033
d R 7.10 92/05/13 19:06:28 heideman 10 9
c vnode interface conversion
e
s 00002/00001/00172
d D 7.9 92/04/21 13:11:16 mckusick 9 8
c VOP_TRUNCATE now takes a cred argument
e
s 00001/00001/00172
d D 7.8 92/04/21 11:41:58 mckusick 8 7
c vop_truncate takes off_t rather than u_long length op
e
s 00036/00027/00137
d D 7.7 92/02/03 22:21:09 heideman 7 6
c new calling convention
e
s 00000/00002/00164
d D 7.6 91/12/16 15:31:02 mckusick 6 5
c mfs_reclaim becomes a real function
e
s 00029/00000/00137
d D 7.5 91/11/05 15:43:39 mckusick 5 4
c reorganization to move ufsmount ops to be vnode ops
e
s 00002/00035/00135
d D 7.4 91/11/01 17:16:17 bostic 4 3
c UFS/FFS split for LFS version 1; move prototypes into mfs_extern.h
e
s 00142/00000/00028
d D 7.3 91/04/16 00:09:01 mckusick 3 2
c add prototypes for MFS vnode operations
e
s 00001/00011/00027
d D 7.2 90/06/28 22:29:57 bostic 2 1
c new copyright notice
e
s 00038/00000/00000
d D 7.1 89/10/24 19:37:14 mckusick 1 0
c date and time created 89/10/24 19:37:14 by mckusick
e
u
U
t
T
I 1
/*
D 22
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
D 4
 * This structure defines the control data for the memory
 * based file system.
E 4
I 4
 * This structure defines the control data for the memory based file system.
E 4
 */

struct mfsnode {
	struct	vnode *mfs_vnode;	/* vnode associated with this mfsnode */
	caddr_t	mfs_baseoff;		/* base of file system in memory */
	long	mfs_size;		/* size of memory file system */
	pid_t	mfs_pid;		/* supporting process pid */
	struct	buf *mfs_buflist;	/* list of I/O requests */
	long	mfs_spare[4];
};

/*
 * Convert between mfsnode pointers and vnode pointers
 */
#define VTOMFS(vp)	((struct mfsnode *)(vp)->v_data)
#define MFSTOV(mfsp)	((mfsp)->mfs_vnode)
I 3

D 4
/*
 * Prototypes for MFS operations on vnodes.
 */
int	mfs_badop();
E 4
I 4
/* Prototypes for MFS operations on vnodes. */
E 4
D 17
#define mfs_lookup ((int (*) __P(( \
D 7
		struct vnode *vp, \
		struct nameidata *ndp, \
		struct proc *p))) mfs_badop)
E 7
I 7
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp))) mfs_badop)
E 7
#define mfs_create ((int (*) __P(( \
D 7
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct proc *p))) mfs_badop)
E 7
I 7
		struct vnode *dvp, \
 		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) mfs_badop)
E 7
#define mfs_mknod ((int (*) __P(( \
D 7
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) mfs_badop)
E 7
I 7
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) mfs_badop)
E 7
D 4
int	mfs_open __P((
		struct vnode *vp,
		int mode,
		struct ucred *cred,
		struct proc *p));
int	mfs_close __P((
		struct vnode *vp,
		int fflag,
		struct ucred *cred,
		struct proc *p));
E 4
#define mfs_access ((int (*) __P(( \
		struct vnode *vp, \
		int mode, \
		struct ucred *cred, \
		struct proc *p))) mfs_badop)
#define mfs_getattr ((int (*) __P(( \
		struct vnode *vp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) mfs_badop)
#define mfs_setattr ((int (*) __P(( \
		struct vnode *vp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) mfs_badop)
#define mfs_read ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		int ioflag, \
		struct ucred *cred))) mfs_badop)
#define mfs_write ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		int ioflag, \
		struct ucred *cred))) mfs_badop)
D 4
int	mfs_ioctl __P((
		struct vnode *vp,
		int command,
		caddr_t data,
		int fflag,
		struct ucred *cred,
		struct proc *p));
E 4
#define mfs_select ((int (*) __P(( \
		struct vnode *vp, \
		int which, \
		int fflags, \
		struct ucred *cred, \
		struct proc *p))) mfs_badop)
#define mfs_mmap ((int (*) __P(( \
		struct vnode *vp, \
		int fflags, \
		struct ucred *cred, \
		struct proc *p))) mfs_badop)
#define mfs_fsync ((int (*) __P(( \
		struct vnode *vp, \
		int fflags, \
		struct ucred *cred, \
		int waitfor, \
		struct proc *p))) mfs_badop)
#define mfs_seek ((int (*) __P(( \
		struct vnode *vp, \
		off_t oldoff, \
		off_t newoff, \
		struct ucred *cred))) mfs_badop)
#define mfs_remove ((int (*) __P(( \
D 7
		struct nameidata *ndp, \
		struct proc *p))) mfs_badop)
E 7
I 7
		struct vnode *dvp, \
	        struct vnode *vp, \
		struct componentname *cnp))) mfs_badop)
E 7
#define mfs_link ((int (*) __P(( \
D 7
		struct vnode *vp, \
		struct nameidata *ndp, \
		struct proc *p))) mfs_badop)
E 7
I 7
		register struct vnode *vp, \
		struct vnode *tdvp, \
		struct componentname *cnp))) mfs_badop)
E 7
#define mfs_rename ((int (*) __P(( \
D 7
		struct nameidata *fndp, \
		struct nameidata *tdnp, \
		struct proc *p))) mfs_badop)
E 7
I 7
		struct vnode *fdvp, \
	        struct vnode *fvp, \
		struct componentname *fcnp, \
		struct vnode *tdvp, \
		struct vnode *tvp, \
		struct componentname *tcnp))) mfs_badop)
E 7
#define mfs_mkdir ((int (*) __P(( \
D 7
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct proc *p))) mfs_badop)
E 7
I 7
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) mfs_badop)
E 7
#define mfs_rmdir ((int (*) __P(( \
D 7
		struct nameidata *ndp, \
		struct proc *p))) mfs_badop)
E 7
I 7
		struct vnode *dvp, \
		struct vnode *vp, \
		struct componentname *cnp))) mfs_badop)
E 7
#define mfs_symlink ((int (*) __P(( \
D 7
		struct nameidata *ndp, \
E 7
I 7
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
E 7
		struct vattr *vap, \
D 7
		char *target, \
		struct proc *p))) mfs_badop)
E 7
I 7
		char *target))) mfs_badop)
E 7
#define mfs_readdir ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		struct ucred *cred, \
		int *eofflagp))) mfs_badop)
#define mfs_readlink ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		struct ucred *cred))) mfs_badop)
#define mfs_abortop ((int (*) __P(( \
D 7
		struct nameidata *ndp))) mfs_badop)
E 7
I 7
		struct vnode *dvp, \
		struct componentname *cnp))) mfs_badop)
E 7
D 4
int	mfs_inactive __P((
		struct vnode *vp,
		struct proc *p));
E 4
D 6
#define mfs_reclaim ((int (*) __P(( \
		struct vnode *vp))) nullop)
E 6
#define mfs_lock ((int (*) __P(( \
		struct vnode *vp))) nullop)
#define mfs_unlock ((int (*) __P(( \
		struct vnode *vp))) nullop)
D 4
int	mfs_bmap __P((
		struct vnode *vp,
		daddr_t bn,
		struct vnode **vpp,
		daddr_t *bnp));
int	mfs_strategy __P((
		struct buf *bp));
int	mfs_print __P((
		struct vnode *vp));
E 4
#define mfs_islocked ((int (*) __P(( \
		struct vnode *vp))) nullop)
#define mfs_advlock ((int (*) __P(( \
		struct vnode *vp, \
		caddr_t id, \
		int op, \
		struct flock *fl, \
		int flags))) mfs_badop)
I 5
#define mfs_blkatoff ((int (*) __P(( \
		struct vnode *vp, \
		off_t offset, \
		char **res, \
		struct buf **bpp))) mfs_badop)
#define mfs_vget ((int (*) __P(( \
		struct mount *mp, \
		ino_t ino, \
		struct vnode **vpp))) mfs_badop)
#define mfs_valloc ((int (*) __P(( \
		struct vnode *pvp, \
		int mode, \
		struct ucred *cred, \
		struct vnode **vpp))) mfs_badop)
#define mfs_vfree ((void (*) __P(( \
		struct vnode *pvp, \
		ino_t ino, \
		int mode))) mfs_badop)
#define mfs_truncate ((int (*) __P(( \
		struct vnode *vp, \
D 8
		u_long length, \
E 8
I 8
		off_t length, \
E 8
D 9
		int flags))) mfs_badop)
E 9
I 9
		int flags, \
		struct ucred *cred))) mfs_badop)
E 9
#define mfs_update ((int (*) __P(( \
		struct vnode *vp, \
		struct timeval *ta, \
		struct timeval *tm, \
		int waitfor))) nullop)
#define mfs_bwrite ((int (*) __P(( \
		struct buf *bp))) nullop)
E 17
I 17
#define mfs_lookup ((int (*) __P((struct  vop_lookup_args *)))mfs_badop)
#define mfs_create ((int (*) __P((struct  vop_create_args *)))mfs_badop)
#define mfs_mknod ((int (*) __P((struct  vop_mknod_args *)))mfs_badop)
#define mfs_access ((int (*) __P((struct  vop_access_args *)))mfs_badop)
#define mfs_getattr ((int (*) __P((struct  vop_getattr_args *)))mfs_badop)
#define mfs_setattr ((int (*) __P((struct  vop_setattr_args *)))mfs_badop)
#define mfs_read ((int (*) __P((struct  vop_read_args *)))mfs_badop)
#define mfs_write ((int (*) __P((struct  vop_write_args *)))mfs_badop)
#define mfs_select ((int (*) __P((struct  vop_select_args *)))mfs_badop)
#define mfs_mmap ((int (*) __P((struct  vop_mmap_args *)))mfs_badop)
D 20
#define mfs_fsync ((int (*) __P((struct  vop_fsync_args *)))mfs_badop)
E 20
#define mfs_seek ((int (*) __P((struct  vop_seek_args *)))mfs_badop)
#define mfs_remove ((int (*) __P((struct  vop_remove_args *)))mfs_badop)
#define mfs_link ((int (*) __P((struct  vop_link_args *)))mfs_badop)
#define mfs_rename ((int (*) __P((struct  vop_rename_args *)))mfs_badop)
#define mfs_mkdir ((int (*) __P((struct  vop_mkdir_args *)))mfs_badop)
#define mfs_rmdir ((int (*) __P((struct  vop_rmdir_args *)))mfs_badop)
#define mfs_symlink ((int (*) __P((struct  vop_symlink_args *)))mfs_badop)
#define mfs_readdir ((int (*) __P((struct  vop_readdir_args *)))mfs_badop)
#define mfs_readlink ((int (*) __P((struct  vop_readlink_args *)))mfs_badop)
#define mfs_abortop ((int (*) __P((struct  vop_abortop_args *)))mfs_badop)
D 24
#define mfs_lock ((int (*) __P((struct  vop_lock_args *)))nullop)
#define mfs_unlock ((int (*) __P((struct  vop_unlock_args *)))nullop)
#define mfs_islocked ((int (*) __P((struct  vop_islocked_args *)))nullop)
E 24
I 24
#define mfs_lock ((int (*) __P((struct  vop_lock_args *)))vop_nolock)
#define mfs_unlock ((int (*) __P((struct  vop_unlock_args *)))vop_nounlock)
#define mfs_islocked ((int(*) __P((struct vop_islocked_args *)))vop_noislocked)
E 24
I 23
#define mfs_pathconf ((int (*) __P((struct  vop_pathconf_args *)))mfs_badop)
E 23
#define mfs_advlock ((int (*) __P((struct  vop_advlock_args *)))mfs_badop)
#define mfs_blkatoff ((int (*) __P((struct  vop_blkatoff_args *)))mfs_badop)
D 21
#define mfs_vget ((int (*) __P((struct  vop_vget_args *)))mfs_badop)
E 21
#define mfs_valloc ((int (*) __P((struct  vop_valloc_args *)))mfs_badop)
#define mfs_vfree ((int (*) __P((struct  vop_vfree_args *)))mfs_badop)
#define mfs_truncate ((int (*) __P((struct  vop_truncate_args *)))mfs_badop)
D 19
#define mfs_update ((int (*) __P((struct  vop_update_args *)))nullop)
#define mfs_bwrite ((int (*) __P((struct  vop_bwrite_args *)))nullop)
E 19
I 19
#define mfs_update ((int (*) __P((struct  vop_update_args *)))mfs_badop)
#define mfs_bwrite ((int (*) __P((struct  vop_bwrite_args *)))vn_bwrite)
E 19
E 17
E 5
E 3
E 1
