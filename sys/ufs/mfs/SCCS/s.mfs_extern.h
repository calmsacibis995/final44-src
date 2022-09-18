h61538
s 00002/00001/00034
d D 8.4 95/03/30 14:22:02 mckusick 14 13
c fix prototype for mfs_init
e
s 00001/00000/00034
d D 8.3 95/02/22 20:54:52 mckusick 13 12
c define mfs_revoke to be vop_revoke
e
s 00001/00001/00033
d D 8.2 94/06/16 17:12:36 mckusick 12 11
c break out reclaim operations (from mycroft)
e
s 00002/00002/00032
d D 8.1 93/06/11 16:27:30 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00012/00026
d D 7.3 92/05/14 17:42:11 heideman 10 2
c vnode interface conversion
e
s 00008/00012/00026
d R 7.3 92/05/14 16:01:04 heideman 9 2
c vnode interface conversion
e
s 00008/00012/00026
d R 7.3 92/05/14 15:00:06 heideman 8 2
c vnode interface conversion
e
s 00008/00012/00026
d R 7.3 92/05/14 13:08:34 heideman 7 2
c vnode interface conversion
e
s 00008/00012/00026
d R 7.3 92/05/14 12:04:34 heideman 6 2
c vnode interface conversion
e
s 00008/00012/00026
d R 7.3 92/05/14 11:28:06 heideman 5 2
c vnode interface conversion
e
s 00008/00012/00026
d R 7.3 92/05/13 23:23:54 heideman 4 2
c vnode interface conversion
e
s 00008/00012/00026
d R 7.3 92/05/13 19:06:33 heideman 3 2
c vnode interface conversion
e
s 00001/00000/00037
d D 7.2 91/12/16 15:31:16 mckusick 2 1
c mfs_reclaim becomes a real function
e
s 00037/00000/00000
d D 7.1 91/11/01 17:16:45 bostic 1 0
c UFS/FFS split for LFS version 1
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct buf;
struct mount;
struct nameidata;
struct proc;
struct statfs;
struct ucred;
struct vnode;
I 14
struct vfsconf;
E 14

__BEGIN_DECLS
int	mfs_badop __P((void));
D 10
int	mfs_bmap __P((struct vnode *vp,
	    daddr_t bn, struct vnode **vpp, daddr_t *bnp));
int	mfs_close __P((struct vnode *vp,
	    int flag, struct ucred *cred, struct proc *p));
E 10
I 10
int	mfs_bmap __P((struct vop_bmap_args *));
int	mfs_close __P((struct vop_close_args *));
E 10
void	mfs_doio __P((struct buf *bp, caddr_t base));
D 10
int	mfs_inactive __P((struct vnode *vp, struct proc *p));
I 2
int	mfs_reclaim __P((struct vnode *vp));
E 10
I 10
int	mfs_inactive __P((struct vop_inactive_args *)); /* XXX */
D 12
int	mfs_reclaim __P((struct vop_reclaim_args *)); /* XXX */
E 12
I 12
int	mfs_reclaim __P((struct vop_reclaim_args *));
E 12
E 10
E 2
D 14
int	mfs_init __P((void));
E 14
I 14
int	mfs_init __P((struct vfsconf *));
E 14
D 10
int	mfs_ioctl __P((struct vnode *vp, int com,
	    caddr_t data, int fflag, struct ucred *cred, struct proc *p));
E 10
I 10
int	mfs_ioctl __P((struct vop_ioctl_args *));
E 10
int	mfs_mount __P((struct mount *mp,
	    char *path, caddr_t data, struct nameidata *ndp, struct proc *p));
D 10
int	mfs_open __P((struct vnode *vp,
	    int mode, struct ucred *cred, struct proc *p));
int	mfs_print __P((struct vnode *vp));
E 10
I 10
int	mfs_open __P((struct vop_open_args *));
int	mfs_print __P((struct vop_print_args *)); /* XXX */
I 13
#define	mfs_revoke vop_revoke
E 13
E 10
int	mfs_start __P((struct mount *mp, int flags, struct proc *p));
int	mfs_statfs __P((struct mount *mp, struct statfs *sbp, struct proc *p));
D 10
int	mfs_strategy __P((struct buf *bp));
E 10
I 10
int	mfs_strategy __P((struct vop_strategy_args *)); /* XXX */
E 10
__END_DECLS
E 1
