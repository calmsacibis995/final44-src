h43822
s 00021/00001/00074
d D 8.6 95/03/30 14:15:25 mckusick 30 29
c add definitions for ffs_sysctl values and names
e
s 00008/00008/00067
d D 8.5 95/03/21 00:53:32 mckusick 29 28
c daddr_t => ufs_daddr_t
e
s 00001/00001/00074
d D 8.4 95/01/02 23:39:01 mckusick 28 27
c convert quad => int64_t (from mycroft)
e
s 00001/00002/00074
d D 8.3 94/04/16 06:31:46 bostic 27 26
c merge ffs_root and lfs_root into ufs_root
e
s 00001/00000/00075
d D 8.2 94/02/03 02:55:56 mckusick 26 25
c add definition for ffs_reallocblks
e
s 00002/00002/00073
d D 8.1 93/06/11 16:21:14 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00075
d D 7.15 92/11/13 16:53:35 mckusick 24 23
c ffs_inactive moves to ufs_inactive
e
s 00003/00001/00073
d D 7.14 92/07/06 18:46:21 mckusick 23 21
c new arguments to FHTOVP
e
s 00002/00001/00073
d R 7.14 92/07/06 18:24:40 mckusick 22 21
c new arguments to FHTOVP
e
s 00001/00001/00073
d D 7.13 92/07/03 01:45:25 mckusick 21 20
c ffs_vget moves from VOP to VFS
e
s 00002/00002/00072
d D 7.12 92/06/25 13:27:10 mckusick 20 19
c new parameters to fhtovp and sync
e
s 00000/00002/00074
d D 7.11 92/05/27 22:58:18 mckusick 19 18
c declarations needed by utilities moved from ffs_extern.h to fs.h
e
s 00010/00010/00066
d D 7.10 92/05/15 12:21:57 heideman 18 17
c prototypes cleaned up after vn_if change
e
s 00015/00017/00061
d D 7.9 92/05/14 17:41:36 heideman 17 16
c vnode interface conversion
e
s 00001/00001/00077
d D 7.8 92/05/14 16:21:12 heideman 16 8
c FIFOOPS update for vn_if conversion
e
s 00015/00017/00061
d R 7.8 92/05/14 16:00:27 heideman 15 8
c vnode interface conversion
e
s 00015/00017/00061
d R 7.8 92/05/14 14:59:41 heideman 14 8
c vnode interface conversion
e
s 00013/00013/00065
d R 7.8 92/05/14 13:07:57 heideman 13 8
c vnode interface conversion
e
s 00012/00012/00066
d R 7.8 92/05/14 12:04:06 heideman 12 8
c vnode interface conversion
e
s 00012/00012/00066
d R 7.8 92/05/14 11:27:38 heideman 11 8
c vnode interface conversion
e
s 00012/00012/00066
d R 7.8 92/05/13 23:23:24 heideman 10 8
c vnode interface conversion
e
s 00012/00012/00066
d R 7.8 92/05/13 19:06:07 heideman 9 8
c vnode interface conversion
e
s 00002/00001/00076
d D 7.7 92/05/13 18:10:10 heideman 8 7
c minor syntax change before vnode interface conversion
e
s 00007/00005/00070
d D 7.6 92/04/21 13:40:25 mckusick 7 6
c have to pass down cred to block allocation routines
e
s 00003/00003/00072
d D 7.5 92/04/21 12:00:09 mckusick 6 4
c ensure proper types for local variables and parameters
e
s 00002/00002/00073
d R 7.5 92/03/26 18:39:09 mckusick 5 4
c ensure proper types for local variables and parameters
e
s 00001/00001/00074
d D 7.4 92/01/13 11:36:46 mckusick 4 3
c extensions for new NFS
e
s 00007/00000/00068
d D 7.3 91/11/08 14:17:13 mckusick 3 2
c proper setup for FIFO's
e
s 00013/00008/00055
d D 7.2 91/11/05 14:28:30 mckusick 2 1
c reorganization to move ufsmount ops to be vnode ops
e
s 00063/00000/00000
d D 7.1 91/11/01 17:09:38 bostic 1 0
c UFS/FFS split for LFS version 1
e
u
U
t
T
I 1
/*-
D 25
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
D 27
 * Copyright (c) 1991, 1993
E 27
I 27
 * Copyright (c) 1991, 1993, 1994
E 27
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 30
/*
 * Sysctl values for the fast filesystem.
 */
#define FFS_CLUSTERREAD		1	/* cluster reading enabled */
#define FFS_CLUSTERWRITE	2	/* cluster writing enabled */
#define FFS_REALLOCBLKS		3	/* block reallocation enabled */
#define FFS_ASYNCFREE		4	/* asynchronous block freeing enabled */
#define	FFS_MAXID		5	/* number of valid ffs ids */

#define FFS_NAMES { \
	{ 0, 0 }, \
	{ "doclusterread", CTLTYPE_INT }, \
	{ "doclusterwrite", CTLTYPE_INT }, \
	{ "doreallocblks", CTLTYPE_INT }, \
	{ "doasyncfree", CTLTYPE_INT }, \
}

E 30
struct buf;
I 2
struct fid;
E 2
struct fs;
struct inode;
struct mount;
struct nameidata;
struct proc;
struct statfs;
struct timeval;
struct ucred;
struct uio;
struct vnode;
I 23
struct mbuf;
E 23
I 30
struct vfsconf;
E 30

__BEGIN_DECLS
D 7
int	ffs_alloc __P((struct inode *, daddr_t, daddr_t, int, daddr_t *));
int	ffs_balloc __P((struct inode *, daddr_t, int, struct buf **, int));
E 7
I 7
int	ffs_alloc __P((struct inode *,
D 29
	    daddr_t, daddr_t, int, struct ucred *, daddr_t *));
E 29
I 29
	    ufs_daddr_t, ufs_daddr_t, int, struct ucred *, ufs_daddr_t *));
E 29
int	ffs_balloc __P((struct inode *,
D 29
	    daddr_t, int, struct ucred *, struct buf **, int));
E 29
I 29
	    ufs_daddr_t, int, struct ucred *, struct buf **, int));
E 29
E 7
D 2
int	ffs_blkatoff __P((struct inode *, off_t, char **, struct buf **));
E 2
I 2
D 17
int	ffs_blkatoff __P((struct vnode *, off_t, char **, struct buf **));
E 17
I 17
D 18
int	ffs_blkatoff __P((struct vop_blkatoff_args *)); /* XXX */
E 18
I 18
int	ffs_blkatoff __P((struct vop_blkatoff_args *));
E 18
E 17
E 2
D 6
int	ffs_blkfree __P((struct inode *, daddr_t, off_t));
E 6
I 6
D 29
int	ffs_blkfree __P((struct inode *, daddr_t, long));
E 6
daddr_t	ffs_blkpref __P((struct inode *, daddr_t, int, daddr_t *));
E 29
I 29
int	ffs_blkfree __P((struct inode *, ufs_daddr_t, long));
ufs_daddr_t ffs_blkpref __P((struct inode *, ufs_daddr_t, int, ufs_daddr_t *));
E 29
D 2
int	ffs_bmap __P((struct inode *, daddr_t, daddr_t *));
E 2
I 2
D 17
int	ffs_bmap __P((struct vnode *, daddr_t, struct vnode **, daddr_t *));
E 17
I 17
D 18
int	ffs_bmap __P((struct vop_bmap_args *)); /* XXX */
E 18
I 18
int	ffs_bmap __P((struct vop_bmap_args *));
E 18
E 17
E 2
D 29
void	ffs_clrblock __P((struct fs *, u_char *, daddr_t));
E 29
I 29
void	ffs_clrblock __P((struct fs *, u_char *, ufs_daddr_t));
E 29
I 2
D 4
int	ffs_fhtovp __P((struct mount *, struct fid *, struct vnode **));
E 4
I 4
D 20
int	ffs_fhtovp __P((struct mount *, struct fid *, int, struct vnode **));
E 20
I 20
D 23
int	ffs_fhtovp __P((struct mount *, struct fid *, struct vnode **));
E 23
I 23
int	ffs_fhtovp __P((struct mount *, struct fid *, struct mbuf *,
	    struct vnode **, int *, struct ucred **));
E 23
E 20
E 4
E 2
D 28
void	ffs_fragacct __P((struct fs *, int, long [], int));
E 28
I 28
void	ffs_fragacct __P((struct fs *, int, int32_t [], int));
E 28
D 17
int	ffs_fsync
	    __P((struct vnode *, int, struct ucred *, int, struct proc *));
D 2
int	ffs_ialloc __P((struct inode *, int, struct ucred *, struct inode **));
void	ffs_ifree __P((struct inode *, ino_t, int));
int	ffs_iget __P((struct inode *, ino_t, struct inode **));
E 2
I 2
int	ffs_inactive __P((struct vnode *, struct proc *));
E 17
I 17
int	ffs_fsync __P((struct vop_fsync_args *));
D 18
int	ffs_inactive __P((struct vop_inactive_args *)); /* XXX */
E 18
I 18
D 24
int	ffs_inactive __P((struct vop_inactive_args *));
E 24
E 18
E 17
E 2
D 30
int	ffs_init __P((void));
E 30
I 30
int	ffs_init __P((struct vfsconf *));
E 30
D 29
int	ffs_isblock __P((struct fs *, u_char *, daddr_t));
E 29
I 29
int	ffs_isblock __P((struct fs *, u_char *, ufs_daddr_t));
E 29
D 2
int	ffs_itrunc __P((struct inode *, u_long, int));
int	ffs_iupdat
	    __P((struct inode *, struct timeval *, struct timeval *, int));
E 2
int	ffs_mount __P((struct mount *,
	    char *, caddr_t, struct nameidata *, struct proc *));
int	ffs_mountfs __P((struct vnode *, struct mount *, struct proc *));
int	ffs_mountroot __P((void));
D 17
int	ffs_read __P((struct vnode *, struct uio *, int, struct ucred *));
E 17
I 17
D 18
int	ffs_read __P((struct vop_read_args *)); /* XXX */
E 18
I 18
int	ffs_read __P((struct vop_read_args *));
I 26
int	ffs_reallocblks __P((struct vop_reallocblks_args *));
E 26
E 18
E 17
D 7
int	ffs_realloccg
D 6
	    __P((struct inode *, off_t, daddr_t, int, int, struct buf **));
E 6
I 6
	    __P((struct inode *, daddr_t, daddr_t, int, int, struct buf **));
E 7
I 7
int	ffs_realloccg __P((struct inode *,
D 29
	    daddr_t, daddr_t, int, int, struct ucred *, struct buf **));
E 29
I 29
	    ufs_daddr_t, ufs_daddr_t, int, int, struct ucred *, struct buf **));
E 29
E 7
E 6
D 17
int	ffs_reclaim __P((struct vnode *));
E 17
I 17
D 18
int	ffs_reclaim __P((struct vop_reclaim_args *)); /* XXX */
E 18
I 18
int	ffs_reclaim __P((struct vop_reclaim_args *));
E 18
E 17
I 2
D 27
int	ffs_root __P((struct mount *, struct vnode **));
E 27
E 2
D 29
void	ffs_setblock __P((struct fs *, u_char *, daddr_t));
E 29
I 29
void	ffs_setblock __P((struct fs *, u_char *, ufs_daddr_t));
E 29
int	ffs_statfs __P((struct mount *, struct statfs *, struct proc *));
D 20
int	ffs_sync __P((struct mount *, int));
E 20
I 20
int	ffs_sync __P((struct mount *, int, struct ucred *, struct proc *));
I 30
int	ffs_sysctl __P((int *, u_int, void *, size_t *, void *, size_t,
	    struct proc *));
E 30
E 20
I 2
D 6
int	ffs_truncate __P((struct vnode *, u_long, int));
E 6
I 6
D 7
int	ffs_truncate __P((struct vnode *, off_t, int));
E 7
I 7
D 17
int	ffs_truncate __P((struct vnode *, off_t, int, struct ucred *));
E 17
I 17
D 18
int	ffs_truncate __P((struct vop_truncate_args *)); /* XXX */
E 18
I 18
int	ffs_truncate __P((struct vop_truncate_args *));
E 18
E 17
E 7
E 6
E 2
int	ffs_unmount __P((struct mount *, int, struct proc *));
I 2
D 17
int	ffs_update
	    __P((struct vnode *, struct timeval *, struct timeval *, int));
int	ffs_valloc __P((struct vnode *, int, struct ucred *, struct vnode **));
void	ffs_vfree __P((struct vnode *, ino_t, int));
int	ffs_vget __P((struct mount *, ino_t, struct vnode **));
E 17
I 17
int	ffs_update __P((struct vop_update_args *));
D 18
int	ffs_valloc __P((struct vop_valloc_args *)); /* XXX */
void	ffs_vfree __P((struct vop_vfree_args *)); /* XXX */
int	ffs_vget __P((struct vop_vget_args *)); /* XXX */
E 18
I 18
int	ffs_valloc __P((struct vop_valloc_args *));
int	ffs_vfree __P((struct vop_vfree_args *));
D 21
int	ffs_vget __P((struct vop_vget_args *));
E 21
I 21
int	ffs_vget __P((struct mount *, ino_t, struct vnode **));
E 21
E 18
E 17
int	ffs_vptofh __P((struct vnode *, struct fid *));
E 2
D 17
int	ffs_write __P((struct vnode *, struct uio *, int, struct ucred *));
E 17
I 17
D 18
int	ffs_write __P((struct vop_write_args *)); /* XXX */
E 18
I 18
int	ffs_write __P((struct vop_write_args *));
E 18
E 17

int	bwrite();		/* FFS needs a bwrite routine.  XXX */

#ifdef DIAGNOSTIC
void	ffs_checkoverlap __P((struct buf *, struct inode *));
#endif
__END_DECLS

D 19
extern int inside[], around[];
extern u_char *fragtbl[];
E 19
I 3
D 8
extern struct vnodeops ffs_vnodeops, ffs_specops;
E 8
I 8
D 17
extern struct vnodeops ffs_vnodeops;
extern struct vnodeops ffs_specops;
E 17
I 17
extern int (**ffs_vnodeop_p)();
extern int (**ffs_specop_p)();
E 17
E 8
#ifdef FIFO
D 17
extern struct vnodeops ffs_fifoops;
E 17
I 17
extern int (**ffs_fifoop_p)();
E 17
D 16
#define FFS_FIFOOPS &ffs_fifoops
E 16
I 16
#define FFS_FIFOOPS ffs_fifoop_p
E 16
#else
#define FFS_FIFOOPS NULL
#endif
E 3
E 1
