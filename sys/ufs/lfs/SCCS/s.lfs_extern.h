h01580
s 00001/00001/00083
d D 8.6 95/05/08 12:15:43 mckusick 40 39
c update from margo
e
s 00004/00001/00080
d D 8.5 95/03/30 14:20:12 mckusick 39 38
c add lfs_sysctl and lfs_mount_type
e
s 00003/00003/00078
d D 8.4 95/03/21 00:27:59 mckusick 38 37
c daddr_t => ufs_daddr_t
e
s 00001/00000/00080
d D 8.3 94/06/16 17:22:36 mckusick 37 36
c break out reclaim operations (from mycroft)
e
s 00001/00002/00079
d D 8.2 94/04/16 06:32:16 bostic 36 35
c merge ffs_root and lfs_root into ufs_root
e
s 00002/00002/00079
d D 8.1 93/06/11 16:27:29 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00077
d D 7.23 92/12/10 14:21:22 margo 34 33
c Add calls to lfs_vref, lfs_vunref.  More args to lfs_seglock.
e
s 00000/00003/00078
d D 7.22 92/10/08 13:45:14 margo 33 32
c Remove lfs_bmap and lfs_bmaparray calls (use ufs ones instead).
e
s 00001/00000/00080
d D 7.21 92/08/26 18:24:21 bostic 32 31
c Add lfs_close to get rid of ITIMES modifying inode IMOD bit without 
c lfs knowing about it.
e
s 00004/00000/00076
d D 7.20 92/08/21 17:26:12 bostic 31 30
c Add lfs_check and lfs_getattr; make lfs_newbuf visible for 
c lfs_syscalls.c
e
s 00003/00001/00073
d D 7.19 92/07/06 18:40:11 mckusick 30 29
c new parameters to fhtovp
e
s 00007/00005/00067
d D 7.18 92/07/05 14:37:33 bostic 29 28
c restructure vnode walk and dirty block invalidation and discard; add
c lock calls to single-thread segment writer
e
s 00010/00002/00062
d D 7.17 92/06/23 00:06:23 bostic 28 27
c directory ops, unmount, minor cleanup; from Margo Seltzer
e
s 00003/00002/00061
d D 7.16 92/05/15 12:20:45 heideman 27 26
c prototypes cleaned up after vn_if change
e
s 00013/00015/00050
d D 7.15 92/05/14 17:55:36 heideman 26 25
c vnode interface conversion
e
s 00001/00001/00064
d D 7.14 92/05/14 16:22:27 heideman 25 17
c FIFOOPS update for vn_if conversion
e
s 00013/00015/00050
d R 7.14 92/05/14 16:00:44 heideman 24 17
c vnode interface conversion
e
s 00013/00015/00050
d R 7.14 92/05/14 14:59:52 heideman 23 17
c vnode interface conversion
e
s 00011/00011/00054
d R 7.14 92/05/14 13:08:17 heideman 22 17
c vnode interface conversion
e
s 00010/00010/00055
d R 7.14 92/05/14 12:04:20 heideman 21 17
c vnode interface conversion
e
s 00010/00010/00055
d R 7.14 92/05/14 11:27:53 heideman 20 17
c vnode interface conversion
e
s 00010/00010/00055
d R 7.14 92/05/13 23:23:38 heideman 19 17
c vnode interface conversion
e
s 00010/00010/00055
d R 7.14 92/05/13 19:06:22 heideman 18 17
c vnode interface conversion
e
s 00001/00001/00064
d D 7.13 92/04/21 13:37:30 mckusick 17 16
c VOP_TRUNCATE now takes a cred argument
e
s 00002/00001/00063
d D 7.12 92/04/21 11:48:16 mckusick 16 15
c ensure proper types for local variables and parameters
e
s 00017/00016/00047
d D 7.11 92/04/08 15:08:02 bostic 15 14
c remove the rest of the typedef's
e
s 00000/00001/00063
d D 7.10 92/03/04 12:41:39 bostic 14 13
c move lfs_ifind into lfs_inode.c, it's only used in one place
e
s 00001/00000/00063
d D 7.9 92/02/04 12:33:13 bostic 13 12
c add lfs_vflush; flush a vnode to disk
e
s 00000/00001/00063
d D 7.8 92/01/18 13:28:55 bostic 12 11
c changes to make lfs_vget retrieve the IFILE inode like any other
c inode
e
s 00001/00001/00063
d D 7.7 92/01/10 16:20:40 mckusick 11 10
c lfs_fhtovp takes an additional parameter
e
s 00001/00000/00063
d D 7.6 91/12/31 14:20:45 bostic 10 9
c add lfs_balloc external declaration
e
s 00000/00001/00063
d D 7.5 91/12/14 18:46:24 bostic 9 8
c inline lfs_iset in lfs_segment.c
e
s 00004/00003/00060
d D 7.4 91/12/06 16:43:46 bostic 8 7
c LFS version 2; minor updates
e
s 00007/00000/00056
d D 7.3 91/11/08 14:16:44 mckusick 7 6
c proper setup for FIFO's
e
s 00012/00010/00044
d D 7.2 91/11/05 15:33:04 mckusick 6 5
c reorganization to move ufsmount ops to be vnode ops
e
s 00004/00004/00050
d D 7.1 91/11/01 17:43:42 bostic 5 4
c don't typedef struct lfs for now
c UFS/FFS split for LFS version 1; lfs moves down one level
e
s 00031/00030/00023
d D 5.4 91/11/01 17:30:20 bostic 4 3
c checkpoint before integration
e
s 00003/00001/00050
d D 5.3 91/10/09 11:24:33 bostic 3 2
c lint
e
s 00005/00000/00046
d D 5.2 91/10/02 09:00:28 bostic 2 1
c checkpoint
e
s 00046/00000/00000
d D 5.1 91/09/25 14:34:06 bostic 1 0
c date and time created 91/09/25 14:34:06 by bostic
e
u
U
t
T
I 1
/*-
D 35
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 35
I 35
D 36
 * Copyright (c) 1991, 1993
E 36
I 36
 * Copyright (c) 1991, 1993, 1994
E 36
 *	The Regents of the University of California.  All rights reserved.
E 35
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct fid;
I 6
struct mount;
E 6
D 4
struct inode;
struct mount;
E 4
I 2
struct nameidata;
E 2
D 8
struct statfs;
E 8
struct proc;
I 8
struct statfs;
struct timeval;
I 16
struct inode;
E 16
struct uio;
I 30
struct mbuf;
E 30
E 8
D 4
struct ucred;
struct vnode;
E 4

D 4
daddr_t	 itod __P((LFS *, ino_t));
int	 lfs_balloc __P((LFS *, VNODE *, daddr_t, int, BUF **));
int	 lfs_bmap __P((struct inode *, daddr_t, daddr_t *));
void	 lfs_bwrite __P((struct buf *));
I 2
void	 lfs_cleaner __P((void));
E 2
int	 lfs_fhtovp __P((struct mount *, struct fid *, struct vnode **));
E 4
I 4
__BEGIN_DECLS
u_long	 cksum __P((void *, size_t));				/* XXX */
I 10
D 38
int	 lfs_balloc __P((struct vnode *, u_long, daddr_t, struct buf **));
E 38
I 38
D 40
int	 lfs_balloc __P((struct vnode *, u_long, ufs_daddr_t, struct buf **));
E 40
I 40
int	 lfs_balloc __P((struct vnode *, int, u_long, ufs_daddr_t, struct buf **));
E 40
E 38
E 10
D 6
int	 lfs_blkatoff __P((struct inode *, off_t, char **, struct buf **));
int	 lfs_bmap __P((INODE *, daddr_t, daddr_t *));
E 6
I 6
D 26
int	 lfs_blkatoff __P((struct vnode *, off_t, char **, struct buf **));
D 15
int	 lfs_bmap __P((VNODE *, daddr_t, VNODE **, daddr_t *));
I 8
int	 lfs_bmaparray __P((VNODE *, daddr_t, daddr_t *, INDIR *, int *));
E 8
E 6
int	 lfs_bwrite __P((BUF *));
E 15
I 15
int	 lfs_bmap __P((struct vnode *, daddr_t, struct vnode **, daddr_t *));
E 26
I 26
int	 lfs_blkatoff __P((struct vop_blkatoff_args *));
D 33
int	 lfs_bmap __P((struct vop_bmap_args *));
E 26
int	 lfs_bmaparray
	    __P((struct vnode *, daddr_t, daddr_t *, INDIR *, int *));
E 33
D 26
int	 lfs_bwrite __P((struct buf *));
E 26
I 26
int	 lfs_bwrite __P((struct vop_bwrite_args *));
I 31
D 38
int	 lfs_check __P((struct vnode *, daddr_t));
E 38
I 38
int	 lfs_check __P((struct vnode *, ufs_daddr_t));
E 38
I 32
int	 lfs_close __P((struct vop_close_args *));
E 32
E 31
I 28
int	 lfs_create __P((struct vop_create_args *));
E 28
E 26
E 15
I 6
D 11
int	 lfs_fhtovp __P((struct mount *, struct fid *, struct vnode **));
E 11
I 11
D 29
int	 lfs_fhtovp __P((struct mount *, struct fid *, int, struct vnode **));
E 29
I 29
D 30
int	 lfs_fhtovp __P((struct mount *, struct fid *, struct vnode **));
E 30
I 30
int	 lfs_fhtovp __P((struct mount *, struct fid *, struct mbuf *,
	    struct vnode **, int *, struct ucred **));
E 30
E 29
E 11
E 6
D 26
int	 lfs_fsync
	     __P((struct vnode *, int, struct ucred *, int, struct proc *));
E 4
D 5
u_long	 lfs_getversion __P((LFS *fs, ino_t));
E 5
I 5
D 8
u_long	 lfs_getversion __P((struct lfs *fs, ino_t));
E 8
E 5
I 3
D 4
void	 lfs_hqueue __P((INODE *));
E 3
ino_t	 lfs_ialloc __P((LFS *, struct inode *, struct inode **,
	     struct ucred *));
IFILE	*lfs_ientry __P((LFS *, ino_t));
struct dinode *
	 lfs_ifind __P((LFS *, ino_t, void *));
void	 lfs_ifree __P((struct inode *));
int	 lfs_inactive __P((struct vnode *, struct proc *));
E 4
I 4
D 6
int	 lfs_ialloc __P((INODE *, int, UCRED *, INODE **));
E 6
D 5
DINODE	*lfs_ifind __P((LFS *, ino_t, void *));
E 5
I 5
D 14
DINODE	*lfs_ifind __P((struct lfs *, ino_t, void *));
E 14
E 5
D 6
void	 lfs_ifree __P((INODE *, ino_t, int));
int	 lfs_iget __P((INODE *, ino_t, INODE **));
E 6
D 15
int	 lfs_inactive __P((VNODE *, struct proc *));
E 15
I 15
int	 lfs_inactive __P((struct vnode *, struct proc *));
E 26
I 26
int	 lfs_fsync __P((struct vop_fsync_args *));
I 31
int	 lfs_getattr __P((struct vop_getattr_args *));
E 31
I 29
struct dinode *
	 lfs_ifind __P((struct lfs *, ino_t, struct dinode *));
E 29
int	 lfs_inactive __P((struct vop_inactive_args *));
E 26
E 15
E 4
D 39
int	 lfs_init __P((void));
E 39
I 39
int	 lfs_init __P((struct vfsconf *));
E 39
I 34
int	 lfs_initseg __P((struct lfs *));
E 34
I 28
int	 lfs_link __P((struct vop_link_args *));
E 28
I 2
D 9
void	 lfs_iset __P((INODE *, daddr_t, time_t));
E 9
E 2
D 4
int	 lfs_lookup __P((struct vnode *, struct nameidata *, struct proc *));
D 3
int	 lfs_mount __P((struct mount *, char *, caddr_t, struct nameidata *, struct proc *));
E 3
I 3
int	 lfs_mount __P((struct mount *, char *, caddr_t, struct nameidata *,
	     struct proc *));
E 3
int	 lfs_root __P((struct mount *, struct vnode **));
E 4
I 4
D 5
daddr_t	 lfs_itod __P((LFS *, ino_t));
E 5
I 5
D 12
daddr_t	 lfs_itod __P((struct lfs *, ino_t));
E 12
E 5
D 6
int	 lfs_itrunc __P((INODE *, u_long, int));
int	 lfs_iupdat
	     __P((struct inode *, struct timeval *, struct timeval *, int));
E 6
int	 lfs_makeinode __P((int, struct nameidata *, struct inode **));
I 28
int	 lfs_mkdir __P((struct vop_mkdir_args *));
int	 lfs_mknod __P((struct vop_mknod_args *));
D 29
int	 lfs_mntinvalbuf __P((struct mount *));
E 29
E 28
D 15
int	 lfs_mount
	     __P((MOUNT *, char *, caddr_t, struct nameidata *, struct proc *));
E 15
I 15
int	 lfs_mount __P((struct mount *,
	    char *, caddr_t, struct nameidata *, struct proc *));
E 15
int	 lfs_mountroot __P((void));
I 31
struct buf *
D 38
	 lfs_newbuf __P((struct vnode *, daddr_t, size_t));
E 38
I 38
	 lfs_newbuf __P((struct vnode *, ufs_daddr_t, size_t));
E 38
E 31
D 26
int	 lfs_read __P((struct vnode *, struct uio *, int, struct ucred *));
E 26
I 26
int	 lfs_read __P((struct vop_read_args *));
I 37
int	 lfs_reclaim __P((struct vop_reclaim_args *));
E 37
I 28
int	 lfs_remove __P((struct vop_remove_args *));
int	 lfs_rmdir __P((struct vop_rmdir_args *));
int	 lfs_rename __P((struct vop_rename_args *));
E 28
E 26
I 6
D 36
int	 lfs_root __P((struct mount *, struct vnode **));
E 36
I 29
D 34
void	 lfs_seglock __P((struct lfs *));
E 34
I 34
void	 lfs_seglock __P((struct lfs *, unsigned long flags));
E 34
void	 lfs_segunlock __P((struct lfs *));
E 29
E 6
E 4
I 2
D 15
int	 lfs_segwrite __P((MOUNT *, int));
E 2
D 4
int	 lfs_statfs __P((struct mount *, struct statfs *, struct proc *));
int	 lfs_sync __P((struct mount *, int));
int	 lfs_unmount __P((struct mount *, int, struct proc *));
int	 lfs_vcreate __P((struct mount *, ino_t, struct vnode **));
E 4
I 4
int	 lfs_statfs __P((MOUNT *, struct statfs *, struct proc *));
int	 lfs_sync __P((MOUNT *, int));
I 6
int	 lfs_truncate __P((VNODE *, u_long, int));
E 6
int	 lfs_unmount __P((MOUNT *, int, struct proc *));
E 15
I 15
int	 lfs_segwrite __P((struct mount *, int));
int	 lfs_statfs __P((struct mount *, struct statfs *, struct proc *));
I 28
int	 lfs_symlink __P((struct vop_symlink_args *));
E 28
D 29
int	 lfs_sync __P((struct mount *, int));
E 29
I 29
int	 lfs_sync __P((struct mount *, int, struct ucred *, struct proc *));
I 39
#define	 lfs_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
                                    size_t, struct proc *)))eopnotsupp)
E 39
E 29
D 16
int	 lfs_truncate __P((struct vnode *, u_long, int));
E 16
I 16
D 17
int	 lfs_truncate __P((struct vnode *, off_t, int));
E 17
I 17
D 26
int	 lfs_truncate __P((struct vnode *, off_t, int, struct ucred *));
E 26
I 26
int	 lfs_truncate __P((struct vop_truncate_args *));
E 26
E 17
E 16
int	 lfs_unmount __P((struct mount *, int, struct proc *));
E 15
I 6
D 26
int	 lfs_update
	     __P((struct vnode *, struct timeval *, struct timeval *, int));
D 15
int	 lfs_valloc __P((VNODE *, int, UCRED *, VNODE **));
E 6
int	 lfs_vcreate __P((MOUNT *, ino_t, VNODE **));
I 6
void	 lfs_vfree __P((VNODE *, ino_t, int));
E 15
I 15
int	 lfs_valloc __P((struct vnode *, int, struct ucred *, struct vnode **));
E 26
I 26
int	 lfs_update __P((struct vop_update_args *));
int	 lfs_valloc __P((struct vop_valloc_args *));
E 26
int	 lfs_vcreate __P((struct mount *, ino_t, struct vnode **));
D 26
void	 lfs_vfree __P((struct vnode *, ino_t, int));
E 26
I 26
D 27
void	 lfs_vfree __P((struct vop_vfree_args *));
E 27
I 27
int	 lfs_vfree __P((struct vop_vfree_args *));
E 27
E 26
E 15
I 13
int	 lfs_vflush __P((struct vnode *));
E 13
D 15
int	 lfs_vget __P((struct mount *, ino_t, VNODE **));
E 15
I 15
D 26
int	 lfs_vget __P((struct mount *, ino_t, struct vnode **));
E 26
I 26
D 29
int	 lfs_vget __P((struct vop_vget_args *));
I 28
int	 lfs_vinvalbuf __P((struct vnode *));
E 29
I 29
int	 lfs_vget __P((struct mount *, ino_t, struct vnode **));
E 29
E 28
E 26
E 15
int	 lfs_vptofh __P((struct vnode *, struct fid *));
I 34
int	 lfs_vref __P((struct vnode *));
void	 lfs_vunref __P((struct vnode *));
E 34
E 6
D 26
int	 lfs_write __P((struct vnode *, struct uio *, int, struct ucred *));
E 26
I 26
int	 lfs_write __P((struct vop_write_args *));
E 26
E 4
D 8

E 8
#ifdef DEBUG
D 4
void	dump_super __P((LFS *));
void	dump_dinode __P((struct dinode *));
void	lfs_print_inumber __P((struct vnode *));
I 2
void	lfs_spin __P((void));
E 4
I 4
D 15
void	lfs_dump_dinode __P((DINODE *));
E 15
I 15
void	lfs_dump_dinode __P((struct dinode *));
E 15
D 5
void	lfs_dump_super __P((LFS *));
E 5
I 5
void	lfs_dump_super __P((struct lfs *));
E 5
D 28
int	lfs_umountdebug __P((struct mount *));
int	lfs_vinvalbuf __P((struct vnode *));
E 28
E 4
E 2
#endif
I 4
__END_DECLS
I 39
extern int lfs_mount_type;
E 39
I 7
D 27
extern struct vnodeops lfs_vnodeops, lfs_specops;
E 27
I 27
extern int (**lfs_vnodeop_p)();
extern int (**lfs_specop_p)();
E 27
#ifdef FIFO
D 26
extern struct vnodeops lfs_fifoops;
E 26
I 26
extern int (**lfs_fifoop_p)();
E 26
D 25
#define LFS_FIFOOPS &lfs_fifoops
E 25
I 25
#define LFS_FIFOOPS lfs_fifoop_p
E 25
#else
#define LFS_FIFOOPS NULL
#endif
E 7
E 4
D 6

extern struct vnodeops lfs_vnodeops;
E 6
E 1
