h17052
s 00001/00001/00102
d D 8.6 95/05/21 19:52:21 mckusick 26 25
c inactive becomes real
e
s 00003/00003/00100
d D 8.5 95/05/14 00:44:32 mckusick 25 24
c convert locking to use vop_nolock* functions
e
s 00001/00000/00102
d D 8.4 95/02/22 20:49:02 mckusick 24 23
c define spec_revoke to use vop_revoke
e
s 00001/00000/00101
d D 8.3 94/08/10 23:42:19 mckusick 23 22
c add spec_lease_check
e
s 00002/00000/00099
d D 8.2 94/02/02 13:18:50 mckusick 22 21
c add badop for reallocblks
e
s 00002/00002/00097
d D 8.1 93/06/10 23:47:14 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00098
d D 7.13 93/05/25 15:37:06 mckusick 20 19
c add spec_pathconf
e
s 00001/00000/00097
d D 7.12 92/07/25 20:31:08 mckusick 19 18
c add declaration for spec_vnodeop_p()
e
s 00000/00001/00097
d D 7.11 92/07/02 23:59:05 mckusick 18 17
c vegt goes away
e
s 00001/00001/00097
d D 7.10 92/06/24 19:08:37 mckusick 17 16
c spec_fsync becomes real
e
s 00040/00176/00058
d D 7.9 92/05/14 17:41:28 heideman 16 8
c vnode interface conversion
e
s 00040/00176/00058
d R 7.9 92/05/14 16:00:19 heideman 15 8
c vnode interface conversion
e
s 00040/00176/00058
d R 7.9 92/05/14 14:59:34 heideman 14 8
c vnode interface conversion
e
s 00040/00176/00058
d R 7.9 92/05/14 13:07:48 heideman 13 8
c vnode interface conversion
e
s 00039/00172/00062
d R 7.9 92/05/14 12:03:59 heideman 12 8
c vnode interface conversion
e
s 00039/00172/00062
d R 7.9 92/05/14 11:27:32 heideman 11 8
c vnode interface conversion
e
s 00039/00172/00062
d R 7.9 92/05/13 23:23:16 heideman 10 8
c vnode interface conversion
e
s 00039/00172/00062
d R 7.9 92/05/13 19:06:00 heideman 9 8
c vnode interface conversion
e
s 00002/00001/00232
d D 7.8 92/04/21 13:07:37 mckusick 8 7
c VOP_TRUNCATE now takes a credential argument
e
s 00001/00001/00232
d D 7.7 92/04/21 10:25:38 mckusick 7 6
c vop_truncate takes off_t rather than u_long length op
e
s 00037/00027/00196
d D 7.6 92/02/04 00:22:43 heideman 6 5
c update for new VOP calling convention
e
s 00029/00000/00194
d D 7.5 91/11/05 15:21:30 mckusick 5 4
c reorganization to move ufsmount ops to be vnode ops; add spec ops
e
s 00006/00000/00188
d D 7.4 91/04/19 17:55:07 mckusick 4 3
c add struct stubs to keep prototypes happy
e
s 00144/00000/00044
d D 7.3 91/04/15 23:26:07 mckusick 3 2
c add prototypes for special device vnode ops
e
s 00001/00011/00043
d D 7.2 90/06/28 22:00:46 bostic 2 1
c new copyright notice
e
s 00054/00000/00000
d D 7.1 90/03/27 19:14:34 mckusick 1 0
c break out from vnode.h
e
u
U
t
T
I 1
/*
D 21
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
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
 * This structure defines the information maintained about
 * special devices. It is allocated in checkalias and freed
 * in vgone.
 */
struct specinfo {
	struct	vnode **si_hashchain;
	struct	vnode *si_specnext;
	long	si_flags;
	dev_t	si_rdev;
};
/*
 * Exported shorthand
 */
#define v_rdev v_specinfo->si_rdev
#define v_hashchain v_specinfo->si_hashchain
#define v_specnext v_specinfo->si_specnext
#define v_specflags v_specinfo->si_flags

/*
 * Flags for specinfo
 */
#define	SI_MOUNTEDON	0x0001	/* block special device is mounted on */

/*
 * Special device management
 */
#define	SPECHSZ	64
#if	((SPECHSZ&(SPECHSZ-1)) == 0)
#define	SPECHASH(rdev)	(((rdev>>5)+(rdev))&(SPECHSZ-1))
#else
#define	SPECHASH(rdev)	(((unsigned)((rdev>>5)+(rdev)))%SPECHSZ)
#endif

struct vnode *speclisth[SPECHSZ];
I 3

/*
 * Prototypes for special file operations on vnodes.
 */
I 19
extern	int (**spec_vnodeop_p)();
E 19
I 4
struct	nameidata;
I 6
struct	componentname;
E 6
struct	ucred;
struct	flock;
struct	buf;
struct	uio;

E 4
int	spec_badop(),
	spec_ebadf();

D 16
int	spec_lookup __P((
D 6
		struct vnode *vp,
		struct nameidata *ndp,
		struct proc *p));
E 6
I 6
		struct vnode *dvp,
		struct vnode **vpp,
		struct componentname *cnp));
E 6
#define spec_create ((int (*) __P(( \
D 6
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct proc *p))) spec_badop)
E 6
I 6
		struct vnode *dvp, \
 		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) spec_badop)
E 6
#define spec_mknod ((int (*) __P(( \
D 6
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) spec_badop)
E 6
I 6
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) spec_badop)
E 6
int	spec_open __P((
		struct vnode *vp,
		int mode,
		struct ucred *cred,
		struct proc *p));
int	spec_close __P((
		struct vnode *vp,
		int fflag,
		struct ucred *cred,
		struct proc *p));
#define spec_access ((int (*) __P(( \
		struct vnode *vp, \
		int mode, \
		struct ucred *cred, \
		struct proc *p))) spec_ebadf)
#define spec_getattr ((int (*) __P(( \
		struct vnode *vp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) spec_ebadf)
#define spec_setattr ((int (*) __P(( \
		struct vnode *vp, \
		struct vattr *vap, \
		struct ucred *cred, \
		struct proc *p))) spec_ebadf)
int	spec_read __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
int	spec_write __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
int	spec_ioctl __P((
		struct vnode *vp,
		int command,
		caddr_t data,
		int fflag,
		struct ucred *cred,
		struct proc *p));
int	spec_select __P((
		struct vnode *vp,
		int which,
		int fflags,
		struct ucred *cred,
		struct proc *p));
#define spec_mmap ((int (*) __P(( \
		struct vnode *vp, \
		int fflags, \
		struct ucred *cred, \
		struct proc *p))) spec_badop)
#define spec_fsync ((int (*) __P(( \
		struct vnode *vp, \
		int fflags, \
		struct ucred *cred, \
		int waitfor, \
		struct proc *p))) nullop)
#define spec_seek ((int (*) __P(( \
		struct vnode *vp, \
		off_t oldoff, \
		off_t newoff, \
		struct ucred *cred))) spec_badop)
#define spec_remove ((int (*) __P(( \
D 6
		struct nameidata *ndp, \
		struct proc *p))) spec_badop)
E 6
I 6
		struct vnode *dvp, \
	        struct vnode *vp, \
		struct componentname *cnp))) spec_badop)
E 6
#define spec_link ((int (*) __P(( \
D 6
		struct vnode *vp, \
		struct nameidata *ndp, \
		struct proc *p))) spec_badop)
E 6
I 6
		register struct vnode *vp, \
		struct vnode *tdvp, \
		struct componentname *cnp))) spec_badop)
E 6
#define spec_rename ((int (*) __P(( \
D 6
		struct nameidata *fndp, \
		struct nameidata *tdnp, \
		struct proc *p))) spec_badop)
E 6
I 6
		struct vnode *fdvp, \
	        struct vnode *fvp, \
		struct componentname *fcnp, \
		struct vnode *tdvp, \
		struct vnode *tvp, \
		struct componentname *tcnp))) spec_badop)
E 6
#define spec_mkdir ((int (*) __P(( \
D 6
		struct nameidata *ndp, \
		struct vattr *vap, \
		struct proc *p))) spec_badop)
E 6
I 6
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
		struct vattr *vap))) spec_badop)
E 6
#define spec_rmdir ((int (*) __P(( \
D 6
		struct nameidata *ndp, \
		struct proc *p))) spec_badop)
E 6
I 6
		struct vnode *dvp, \
		struct vnode *vp, \
		struct componentname *cnp))) spec_badop)
E 6
#define spec_symlink ((int (*) __P(( \
D 6
		struct nameidata *ndp, \
E 6
I 6
		struct vnode *dvp, \
		struct vnode **vpp, \
		struct componentname *cnp, \
E 6
		struct vattr *vap, \
D 6
		char *target, \
		struct proc *p))) spec_badop)
E 6
I 6
		char *target))) spec_badop)
E 6
#define spec_readdir ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		struct ucred *cred, \
		int *eofflagp))) spec_badop)
#define spec_readlink ((int (*) __P(( \
		struct vnode *vp, \
		struct uio *uio, \
		struct ucred *cred))) spec_badop)
#define spec_abortop ((int (*) __P(( \
D 6
		struct nameidata *ndp))) spec_badop)
E 6
I 6
		struct vnode *dvp, \
		struct componentname *cnp))) spec_badop)
E 6
#define spec_inactive ((int (*) __P(( \
		struct vnode *vp, \
		struct proc *p))) nullop)
#define spec_reclaim ((int (*) __P(( \
		struct vnode *vp))) nullop)
int	spec_lock __P((
		struct vnode *vp));
int	spec_unlock __P((
		struct vnode *vp));
int	spec_bmap __P((
		struct vnode *vp,
		daddr_t bn,
		struct vnode **vpp,
		daddr_t *bnp));
int	spec_strategy __P((
		struct buf *bp));
int	spec_print __P((
		struct vnode *vp));
#define spec_islocked ((int (*) __P(( \
		struct vnode *vp))) nullop)
int	spec_advlock __P((
		struct vnode *vp,
		caddr_t id,
		int op,
		struct flock *fl,
		int flags));
I 5
#define spec_blkatoff ((int (*) __P(( \
		struct vnode *vp, \
		off_t offset, \
		char **res, \
		struct buf **bpp))) spec_badop)
#define spec_vget ((int (*) __P(( \
		struct mount *mp, \
		ino_t ino, \
		struct vnode **vpp))) spec_badop)
#define spec_valloc ((int (*) __P(( \
		struct vnode *pvp, \
		int mode, \
		struct ucred *cred, \
		struct vnode **vpp))) spec_badop)
#define spec_vfree ((void (*) __P(( \
		struct vnode *pvp, \
		ino_t ino, \
		int mode))) spec_badop)
#define spec_truncate ((int (*) __P(( \
		struct vnode *vp, \
D 7
		u_long length, \
E 7
I 7
		off_t length, \
E 7
D 8
		int flags))) nullop)
E 8
I 8
		int flags, \
		struct ucred *cred))) nullop)
E 8
#define spec_update ((int (*) __P(( \
		struct vnode *vp, \
		struct timeval *ta, \
		struct timeval *tm, \
		int waitfor))) nullop)
#define spec_bwrite ((int (*) __P(( \
		struct buf *bp))) nullop)
E 16
I 16
int	spec_lookup __P((struct vop_lookup_args *));
#define spec_create ((int (*) __P((struct  vop_create_args *)))spec_badop)
#define spec_mknod ((int (*) __P((struct  vop_mknod_args *)))spec_badop)
int	spec_open __P((struct vop_open_args *));
int	spec_close __P((struct vop_close_args *));
#define spec_access ((int (*) __P((struct  vop_access_args *)))spec_ebadf)
#define spec_getattr ((int (*) __P((struct  vop_getattr_args *)))spec_ebadf)
#define spec_setattr ((int (*) __P((struct  vop_setattr_args *)))spec_ebadf)
int	spec_read __P((struct vop_read_args *));
int	spec_write __P((struct vop_write_args *));
I 23
#define	spec_lease_check ((int (*) __P((struct  vop_lease_args *)))nullop)
E 23
int	spec_ioctl __P((struct vop_ioctl_args *));
int	spec_select __P((struct vop_select_args *));
I 24
#define	spec_revoke vop_revoke
E 24
#define spec_mmap ((int (*) __P((struct  vop_mmap_args *)))spec_badop)
D 17
#define spec_fsync ((int (*) __P((struct  vop_fsync_args *)))nullop)
E 17
I 17
int	spec_fsync __P((struct  vop_fsync_args *));
E 17
#define spec_seek ((int (*) __P((struct  vop_seek_args *)))spec_badop)
#define spec_remove ((int (*) __P((struct  vop_remove_args *)))spec_badop)
#define spec_link ((int (*) __P((struct  vop_link_args *)))spec_badop)
#define spec_rename ((int (*) __P((struct  vop_rename_args *)))spec_badop)
#define spec_mkdir ((int (*) __P((struct  vop_mkdir_args *)))spec_badop)
#define spec_rmdir ((int (*) __P((struct  vop_rmdir_args *)))spec_badop)
#define spec_symlink ((int (*) __P((struct  vop_symlink_args *)))spec_badop)
#define spec_readdir ((int (*) __P((struct  vop_readdir_args *)))spec_badop)
#define spec_readlink ((int (*) __P((struct  vop_readlink_args *)))spec_badop)
#define spec_abortop ((int (*) __P((struct  vop_abortop_args *)))spec_badop)
D 26
#define spec_inactive ((int (*) __P((struct  vop_inactive_args *)))nullop)
E 26
I 26
int	spec_inactive __P((struct  vop_inactive_args *));
E 26
#define spec_reclaim ((int (*) __P((struct  vop_reclaim_args *)))nullop)
D 25
int	spec_lock __P((struct vop_lock_args *));
int	spec_unlock __P((struct vop_unlock_args *));
E 25
I 25
#define spec_lock ((int (*) __P((struct  vop_lock_args *)))vop_nolock)
#define spec_unlock ((int (*) __P((struct  vop_unlock_args *)))vop_nounlock)
E 25
int	spec_bmap __P((struct vop_bmap_args *));
int	spec_strategy __P((struct vop_strategy_args *));
int	spec_print __P((struct vop_print_args *));
D 25
#define spec_islocked ((int (*) __P((struct  vop_islocked_args *)))nullop)
E 25
I 25
#define spec_islocked ((int(*) __P((struct vop_islocked_args *)))vop_noislocked)
E 25
I 20
int	spec_pathconf __P((struct vop_pathconf_args *));
E 20
int	spec_advlock __P((struct vop_advlock_args *));
#define spec_blkatoff ((int (*) __P((struct  vop_blkatoff_args *)))spec_badop)
D 18
#define spec_vget ((int (*) __P((struct  vop_vget_args *)))spec_badop)
E 18
#define spec_valloc ((int (*) __P((struct  vop_valloc_args *)))spec_badop)
I 22
#define spec_reallocblks \
	((int (*) __P((struct  vop_reallocblks_args *)))spec_badop)
E 22
#define spec_vfree ((int (*) __P((struct  vop_vfree_args *)))spec_badop)
#define spec_truncate ((int (*) __P((struct  vop_truncate_args *)))nullop)
#define spec_update ((int (*) __P((struct  vop_update_args *)))nullop)
#define spec_bwrite ((int (*) __P((struct  vop_bwrite_args *)))nullop)
E 16
E 5
E 3
E 1
