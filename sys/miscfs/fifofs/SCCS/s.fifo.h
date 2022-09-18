h38250
s 00001/00001/00060
d D 8.6 95/05/21 18:09:34 mckusick 21 20
c fifo_inactive becomes real
e
s 00003/00003/00058
d D 8.5 95/05/14 00:40:04 mckusick 20 19
c locking uses vop_nolock* functions
e
s 00001/00000/00060
d D 8.4 95/02/22 20:51:27 mckusick 19 18
c define fifo_revoke to use vop_revoke
e
s 00001/00000/00059
d D 8.3 94/08/10 23:41:14 mckusick 18 17
c add fifo_lease_check
e
s 00002/00000/00057
d D 8.2 94/02/02 13:18:26 mckusick 17 16
c add badop for reallocblks
e
s 00002/00002/00055
d D 8.1 93/06/10 23:36:24 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00056
d D 7.8 93/05/25 15:32:17 mckusick 15 14
c add fifo_pathconf
e
s 00000/00001/00056
d D 7.7 92/07/02 23:59:04 mckusick 14 13
c vegt goes away
e
s 00040/00176/00017
d D 7.6 92/05/14 17:41:17 heideman 13 5
c vnode interface conversion
e
s 00040/00176/00017
d R 7.6 92/05/14 16:00:11 heideman 12 5
c vnode interface conversion
e
s 00040/00176/00017
d R 7.6 92/05/14 14:59:27 heideman 11 5
c vnode interface conversion
e
s 00040/00176/00017
d R 7.6 92/05/14 13:07:38 heideman 10 5
c vnode interface conversion
e
s 00039/00172/00021
d R 7.6 92/05/14 12:03:51 heideman 9 5
c vnode interface conversion
e
s 00039/00172/00021
d R 7.6 92/05/14 11:27:23 heideman 8 5
c vnode interface conversion
e
s 00039/00172/00021
d R 7.6 92/05/13 23:23:07 heideman 7 5
c vnode interface conversion
e
s 00039/00172/00021
d R 7.6 92/05/13 19:05:53 heideman 6 5
c vnode interface conversion
e
s 00002/00001/00191
d D 7.5 92/04/21 13:07:38 mckusick 5 4
c VOP_TRUNCATE now takes a credential argument
e
s 00001/00001/00191
d D 7.4 92/04/21 10:25:37 mckusick 4 3
c vop_truncate takes off_t rather than u_long length op
e
s 00036/00027/00156
d D 7.3 92/02/04 00:23:04 heideman 3 2
c update for new VOP calling convention
e
s 00029/00000/00154
d D 7.2 91/11/05 15:21:03 mckusick 2 1
c reorganization to move ufsmount ops to be vnode ops; add fifo ops
e
s 00154/00000/00000
d D 7.1 91/04/15 23:35:20 mckusick 1 0
c date and time created 91/04/15 23:35:20 by mckusick
e
u
U
t
T
I 1
/*
D 16
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifdef FIFO
/*
 * Prototypes for fifo operations on vnodes.
 */
int	fifo_badop(),
	fifo_ebadf();

D 13
int	fifo_lookup __P((
D 3
		struct vnode *vp,
		struct nameidata *ndp,
		struct proc *p));
E 3
I 3
		struct vnode *dvp,
		struct vnode **vpp,
		struct componentname *cnp));
E 3
#define fifo_create ((int (*) __P(( \
D 3
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct proc *p))) fifo_badop)
E 3
I 3
		struct vnode *dvp, \
 		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) fifo_badop)
E 3
#define fifo_mknod ((int (*) __P(( \
D 3
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) fifo_badop)
E 3
I 3
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) fifo_badop)
E 3
int	fifo_open __P((
		struct vnode *vp,
		int mode,
		struct ucred *cred,
		struct proc *p));
int	fifo_close __P((
		struct vnode *vp,
		int fflag,
		struct ucred *cred,
		struct proc *p));
#define fifo_access ((int (*) __P(( \
		struct vnode *vp, \
		int mode, \
		struct ucred *cred, \
		struct proc *p))) fifo_ebadf)
#define fifo_getattr ((int (*) __P(( \
		struct vnode *vp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) fifo_ebadf)
#define fifo_setattr ((int (*) __P(( \
		struct vnode *vp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) fifo_ebadf)
int	fifo_read __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
int	fifo_write __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
int	fifo_ioctl __P((
		struct vnode *vp,
		int command,
		caddr_t data,
		int fflag,
		struct ucred *cred,
		struct proc *p));
int	fifo_select __P((
		struct vnode *vp,
		int which,
		int fflags,
		struct ucred *cred,
		struct proc *p));
#define fifo_mmap ((int (*) __P(( \
		struct vnode *vp, \
		int fflags, \
		struct ucred *cred, \
		struct proc *p))) fifo_badop)
#define fifo_fsync ((int (*) __P(( \
		struct vnode *vp, \
		int fflags, \
		struct ucred *cred, \
		int waitfor, \
		struct proc *p))) nullop)
#define fifo_seek ((int (*) __P(( \
		struct vnode *vp, \
		off_t oldoff, \
		off_t newoff, \
		struct ucred *cred))) fifo_badop)
#define fifo_remove ((int (*) __P(( \
D 3
		struct nameidata *ndp, \
		struct proc *p))) fifo_badop)
E 3
I 3
		struct vnode *dvp, \
	        struct vnode *vp, \
		struct componentname *cnp))) fifo_badop)
E 3
#define fifo_link ((int (*) __P(( \
D 3
		struct vnode *vp, \
		struct nameidata *ndp, \
		struct proc *p))) fifo_badop)
E 3
I 3
		register struct vnode *vp, \
		struct vnode *tdvp, \
		struct componentname *cnp))) fifo_badop)
E 3
#define fifo_rename ((int (*) __P(( \
D 3
		struct nameidata *fndp, \
		struct nameidata *tdnp, \
		struct proc *p))) fifo_badop)
E 3
I 3
		struct vnode *fdvp, \
	        struct vnode *fvp, \
		struct componentname *fcnp, \
		struct vnode *tdvp, \
		struct vnode *tvp, \
		struct componentname *tcnp))) fifo_badop)
E 3
#define fifo_mkdir ((int (*) __P(( \
D 3
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct proc *p))) fifo_badop)
E 3
I 3
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) fifo_badop)
E 3
#define fifo_rmdir ((int (*) __P(( \
D 3
		struct nameidata *ndp, \
		struct proc *p))) fifo_badop)
E 3
I 3
		struct vnode *dvp, \
		struct vnode *vp, \
		struct componentname *cnp))) fifo_badop)
E 3
#define fifo_symlink ((int (*) __P(( \
D 3
		struct nameidata *ndp, \
E 3
I 3
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
E 3
		struct vattr *vap, \
D 3
		char *target, \
		struct proc *p))) fifo_badop)
E 3
I 3
		char *target))) fifo_badop)
E 3
#define fifo_readdir ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		struct ucred *cred, \
		int *eofflagp))) fifo_badop)
#define fifo_readlink ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		struct ucred *cred))) fifo_badop)
#define fifo_abortop ((int (*) __P(( \
D 3
		struct nameidata *ndp))) fifo_badop)
E 3
I 3
		struct vnode *dvp, \
		struct componentname *cnp))) fifo_badop)
E 3
#define fifo_inactive ((int (*) __P(( \
		struct vnode *vp, \
		struct proc *p))) nullop)
#define fifo_reclaim ((int (*) __P(( \
		struct vnode *vp))) nullop)
int	fifo_lock __P((
		struct vnode *vp));
int	fifo_unlock __P((
		struct vnode *vp));
int	fifo_bmap __P((
		struct vnode *vp,
		daddr_t bn,
		struct vnode **vpp,
		daddr_t *bnp));
#define fifo_strategy ((int (*) __P(( \
		struct buf *bp))) fifo_badop)
int	fifo_print __P((
		struct vnode *vp));
#define fifo_islocked ((int (*) __P(( \
		struct vnode *vp))) nullop)
int	fifo_advlock __P((
		struct vnode *vp,
		caddr_t id,
		int op,
		struct flock *fl,
		int flags));
I 2
#define fifo_blkatoff ((int (*) __P(( \
		struct vnode *vp, \
		off_t offset, \
		char **res, \
		struct buf **bpp))) fifo_badop)
#define fifo_vget ((int (*) __P(( \
		struct mount *mp, \
		ino_t ino, \
		struct vnode **vpp))) fifo_badop)
#define fifo_valloc ((int (*) __P(( \
		struct vnode *pvp, \
		int mode, \
		struct ucred *cred, \
		struct vnode **vpp))) fifo_badop)
#define fifo_vfree ((void (*) __P(( \
		struct vnode *pvp, \
		ino_t ino, \
		int mode))) fifo_badop)
#define fifo_truncate ((int (*) __P(( \
		struct vnode *vp, \
D 4
		u_long length, \
E 4
I 4
		off_t length, \
E 4
D 5
		int flags))) nullop)
E 5
I 5
		int flags, \
		struct ucred *cred))) nullop)
E 5
#define fifo_update ((int (*) __P(( \
		struct vnode *vp, \
		struct timeval *ta, \
		struct timeval *tm, \
		int waitfor))) nullop)
#define fifo_bwrite ((int (*) __P(( \
		struct buf *bp))) nullop)
E 13
I 13
int	fifo_lookup __P((struct vop_lookup_args *));
#define fifo_create ((int (*) __P((struct  vop_create_args *)))fifo_badop)
#define fifo_mknod ((int (*) __P((struct  vop_mknod_args *)))fifo_badop)
int	fifo_open __P((struct vop_open_args *));
int	fifo_close __P((struct vop_close_args *));
#define fifo_access ((int (*) __P((struct  vop_access_args *)))fifo_ebadf)
#define fifo_getattr ((int (*) __P((struct  vop_getattr_args *)))fifo_ebadf)
#define fifo_setattr ((int (*) __P((struct  vop_setattr_args *)))fifo_ebadf)
int	fifo_read __P((struct vop_read_args *));
int	fifo_write __P((struct vop_write_args *));
I 18
#define fifo_lease_check ((int (*) __P((struct  vop_lease_args *)))nullop)
E 18
int	fifo_ioctl __P((struct vop_ioctl_args *));
int	fifo_select __P((struct vop_select_args *));
I 19
#define	fifo_revoke vop_revoke
E 19
#define fifo_mmap ((int (*) __P((struct  vop_mmap_args *)))fifo_badop)
#define fifo_fsync ((int (*) __P((struct  vop_fsync_args *)))nullop)
#define fifo_seek ((int (*) __P((struct  vop_seek_args *)))fifo_badop)
#define fifo_remove ((int (*) __P((struct  vop_remove_args *)))fifo_badop)
#define fifo_link ((int (*) __P((struct  vop_link_args *)))fifo_badop)
#define fifo_rename ((int (*) __P((struct  vop_rename_args *)))fifo_badop)
#define fifo_mkdir ((int (*) __P((struct  vop_mkdir_args *)))fifo_badop)
#define fifo_rmdir ((int (*) __P((struct  vop_rmdir_args *)))fifo_badop)
#define fifo_symlink ((int (*) __P((struct  vop_symlink_args *)))fifo_badop)
#define fifo_readdir ((int (*) __P((struct  vop_readdir_args *)))fifo_badop)
#define fifo_readlink ((int (*) __P((struct  vop_readlink_args *)))fifo_badop)
#define fifo_abortop ((int (*) __P((struct  vop_abortop_args *)))fifo_badop)
D 21
#define fifo_inactive ((int (*) __P((struct  vop_inactive_args *)))nullop)
E 21
I 21
int	fifo_inactive __P((struct  vop_inactive_args *));
E 21
#define fifo_reclaim ((int (*) __P((struct  vop_reclaim_args *)))nullop)
D 20
int	fifo_lock __P((struct vop_lock_args *));
int	fifo_unlock __P((struct vop_unlock_args *));
E 20
I 20
#define fifo_lock ((int (*) __P((struct  vop_lock_args *)))vop_nolock)
#define fifo_unlock ((int (*) __P((struct  vop_unlock_args *)))vop_nounlock)
E 20
int	fifo_bmap __P((struct vop_bmap_args *));
#define fifo_strategy ((int (*) __P((struct  vop_strategy_args *)))fifo_badop)
int	fifo_print __P((struct vop_print_args *));
D 20
#define fifo_islocked ((int (*) __P((struct  vop_islocked_args *)))nullop)
E 20
I 20
#define fifo_islocked ((int(*) __P((struct vop_islocked_args *)))vop_noislocked)
E 20
I 15
int	fifo_pathconf __P((struct vop_pathconf_args *));
E 15
int	fifo_advlock __P((struct vop_advlock_args *));
#define fifo_blkatoff ((int (*) __P((struct  vop_blkatoff_args *)))fifo_badop)
D 14
#define fifo_vget ((int (*) __P((struct  vop_vget_args *)))fifo_badop)
E 14
#define fifo_valloc ((int (*) __P((struct  vop_valloc_args *)))fifo_badop)
I 17
#define fifo_reallocblks \
	((int (*) __P((struct  vop_reallocblks_args *)))fifo_badop)
E 17
#define fifo_vfree ((int (*) __P((struct  vop_vfree_args *)))fifo_badop)
#define fifo_truncate ((int (*) __P((struct  vop_truncate_args *)))nullop)
#define fifo_update ((int (*) __P((struct  vop_update_args *)))nullop)
#define fifo_bwrite ((int (*) __P((struct  vop_bwrite_args *)))nullop)
E 13
E 2
#endif /* FIFO */
E 1
