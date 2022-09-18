h20116
s 00022/00000/00059
d D 8.6 95/03/30 14:17:51 mckusick 30 29
c ufs_args and mfs_args move in from mount.h
e
s 00001/00001/00058
d D 8.5 95/01/02 23:42:45 mckusick 29 28
c quad => int64
e
s 00001/00000/00058
d D 8.4 94/10/27 20:35:43 mckusick 28 27
c add um_savedmaxfilesize to save real value
e
s 00006/00005/00052
d D 8.3 94/07/08 22:58:15 mckusick 27 26
c changes for 64-bit machines (from bostic)
e
s 00002/00006/00055
d D 8.2 94/01/12 15:36:13 hibler 26 25
c reflect FS independent nature of export info.
e
s 00002/00002/00059
d D 8.1 93/06/11 16:29:31 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00000/00051
d D 7.16 92/10/07 17:02:04 margo 24 23
c Add macros to access new fields in ufsmount structure.
e
s 00003/00000/00048
d D 7.15 92/10/07 16:56:37 margo 23 22
c Add fields to ufsmount structure for integration of ffs/lfs_bmap.
e
s 00006/00002/00042
d D 7.14 92/08/11 23:22:21 mckusick 22 21
c use radix tree code to match exported host addresses rather than adhoc hash code
e
s 00002/00000/00042
d D 7.13 92/01/09 22:25:05 mckusick 21 20
c add support for NFS leases
e
s 00000/00008/00042
d D 7.12 91/11/11 11:27:43 bostic 20 19
c move ROOTINO to dinode.h, so applications don't have to include ufsmount.h
e
s 00000/00022/00050
d D 7.11 91/11/05 14:36:21 mckusick 19 18
c reorganization to move ufsmount ops to be vnode ops; delete ops
e
s 00055/00034/00017
d D 7.10 91/11/01 18:01:01 bostic 18 17
c added LFS version 1; add inode ops routines, include ROOTINO #define
e
s 00013/00041/00038
d D 7.9 91/05/08 19:45:27 mckusick 17 16
c new format for prototypes; more precise comments
e
s 00042/00000/00037
d D 7.8 91/04/16 00:08:24 mckusick 16 15
c add prototypes for UFS VFS operations
e
s 00001/00011/00036
d D 7.7 90/06/28 22:31:35 bostic 15 14
c new copyright notice
e
s 00001/00001/00046
d D 7.6 90/05/04 20:51:14 mckusick 14 13
c mount struct prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00012/00008/00035
d D 7.5 90/05/02 19:29:25 mckusick 13 12
c expand to handle user and group quotas; eliminate static mount table
e
s 00000/00001/00043
d D 7.4 90/03/06 23:27:40 mckusick 12 11
c mntname is now maintained in the mount table
e
s 00031/00010/00013
d D 7.3 89/05/09 17:11:03 mckusick 11 10
c merge in vnodes
e
s 00001/00001/00022
d D 7.2 87/06/21 15:27:13 mckusick 10 9
c geteblk => malloc, so m_bufp => m_fs as it should be
e
s 00001/00001/00022
d D 7.1 86/06/04 23:25:10 mckusick 9 8
c 4.3BSD release version
e
s 00007/00001/00016
d D 6.2 85/06/08 15:01:46 mckusick 8 7
c Add copyright
e
s 00000/00000/00017
d D 6.1 83/07/29 06:13:10 sam 7 6
c 4.2 distribution
e
s 00001/00000/00016
d D 4.4 82/07/19 17:40:15 kre 6 5
c added inode pointer to quota file (for disc quotas)
e
s 00004/00001/00012
d D 4.3 81/02/26 23:17:17 wnj 5 4
c #ifdef KERNEL
e
s 00001/00001/00012
d D 4.2 81/02/19 21:41:19 wnj 4 3
c %G%->%E%
e
s 00000/00000/00013
d D 4.1 80/11/09 17:01:14 bill 3 2
c stamp for 4bsd
e
s 00001/00001/00012
d D 3.2 80/06/07 02:58:44 bill 2 1
c %H%->%G%
e
s 00013/00000/00000
d D 3.1 80/04/09 16:24:20 bill 1 0
c date and time created 80/04/09 16:24:20 by bill
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%H%	*/
E 2
I 2
D 4
/*	%M%	%I%	%G%	*/
E 4
I 4
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
/*
D 9
 * Copyright (c) 1982 Regents of the University of California.
E 9
I 9
D 11
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 25
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
E 11
 *
I 11
D 15
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
 *
E 11
 *	%W% (Berkeley) %G%
 */
E 8
E 4
E 2

I 30
/*
 * Arguments to mount UFS-based filesystems
 */
struct ufs_args {
	char	*fspec;			/* block special device to mount */
	struct	export_args export;	/* network export information */
};

#ifdef MFS
/*
 * Arguments to mount MFS
 */
struct mfs_args {
	char	*fspec;			/* name to export for statfs */
	struct	export_args export;	/* if exported MFSes are supported */
	caddr_t	base;			/* base of file system in memory */
	u_long	size;			/* size of file system */
};
#endif /* MFS */

#ifdef KERNEL
E 30
D 20
/*
D 17
 * Mount structure.
 * One allocated on every mount.
 * Used to find the super block.
E 17
I 17
D 18
 * This structure describes the UFS specific mount structure data.
E 18
I 18
 * The root inode is the root of the file system.  Inode 0 can't be used for
 * normal purposes and historically bad blocks were linked to inode 1, thus
 * the root inode is 2. (inode 1 is no longer used for this purpose, however
 * numerous dump tapes make this assumption, so we are stuck with it).
E 18
E 17
 */
D 11
struct	mount
{
	dev_t	m_dev;		/* device mounted */
D 10
	struct	buf *m_bufp;	/* pointer to superblock */
E 10
I 10
	struct	fs *m_fs;	/* pointer to superblock */
E 10
	struct	inode *m_inodp;	/* pointer to mounted on inode */
I 6
	struct	inode *m_qinod;	/* QUOTA: pointer to quota file */
E 11
I 11
D 18
struct	ufsmount {
	struct	mount *um_mountp;	/* vfs structure for this filesystem */
	dev_t	um_dev;			/* device mounted */
	struct	vnode *um_devvp;	/* vnode for block device mounted */
	struct	fs *um_fs;		/* pointer to superblock */
D 13
	struct	inode *um_qinod;	/* QUOTA: pointer to quota file */
E 13
I 13
	struct	vnode *um_quotas[MAXQUOTAS]; /* pointer to quota files */
	struct	ucred *um_cred[MAXQUOTAS]; /* cred for access to quota file */
	time_t	um_btime[MAXQUOTAS];	/* block quota time limit */
	time_t	um_itime[MAXQUOTAS];	/* inode quota time limit */
	char	um_qflags[MAXQUOTAS];	/* quota specific flags, see below */
E 18
I 18
#define	ROOTINO	((ino_t)2)

E 20
struct buf;
struct inode;
struct nameidata;
struct timeval;
struct ucred;
struct uio;
struct vnode;
I 22
D 26
struct radix_node_head;
#ifndef AF_MAX
#include <sys/socket.h>
#endif
E 26
I 26
struct netexport;
E 26
E 22

/* This structure describes the UFS specific mount structure data. */
struct ufsmount {
	struct	mount *um_mountp;		/* filesystem vfs structure */
	dev_t	um_dev;				/* device mounted */
	struct	vnode *um_devvp;		/* block device mounted vnode */
I 27

E 27
	union {					/* pointer to superblock */
		struct	lfs *lfs;		/* LFS */
		struct	fs *fs;			/* FFS */
	} ufsmount_u;
#define	um_fs	ufsmount_u.fs
#define	um_lfs	ufsmount_u.lfs
I 27

E 27
	struct	vnode *um_quotas[MAXQUOTAS];	/* pointer to quota files */
	struct	ucred *um_cred[MAXQUOTAS];	/* quota file access cred */
I 23
	u_long	um_nindir;			/* indirect ptrs per block */
	u_long	um_bptrtodb;			/* indir ptr to disk block */
	u_long	um_seqinc;			/* inc between seq blocks */
E 23
	time_t	um_btime[MAXQUOTAS];		/* block quota time limit */
	time_t	um_itime[MAXQUOTAS];		/* inode quota time limit */
	char	um_qflags[MAXQUOTAS];		/* quota specific flags */
I 21
D 22
	struct	netaddrhash um_defexported;	/* Default export */
	struct	netaddrhash *um_netaddr[NETHASHSZ+1]; /* Net addr hash lists */
E 22
I 22
D 26
	struct	netcred um_defexported;		/* Default export */
	struct	radix_node_head *um_rtable[AF_MAX+1]; /* Individual exports */
E 26
I 26
	struct	netexport um_export;		/* export information */
I 28
D 29
	quad_t	um_savedmaxfilesize;		/* XXX - limit maxfilesize */
E 29
I 29
	int64_t	um_savedmaxfilesize;		/* XXX - limit maxfilesize */
E 29
E 28
E 26
E 22
E 21
D 19

	/*
	 * The following is the inode switch.  It is intended to provide
	 * the interface between the Unix File System semantics and the
	 * on-disk allocation, layout and I/O.
	 */
	int	(*um_blkatoff) __P((struct inode *ip,
		    off_t offset, char **res, struct buf **bpp));
	int	(*um_write) __P((struct vnode *vp,
		    struct uio *uio, int ioflag, struct ucred *cred));
	int	(*um_iget) __P((struct inode *pip,
		    ino_t ino, struct inode **ipp));
	int	(*um_ialloc) __P((struct inode *pip,
		    int mode, struct ucred *cred, struct inode **ipp));
	void	(*um_ifree) __P((struct inode *pip, ino_t ino, int mode));
	int	(*um_itrunc) __P((struct inode *oip, u_long length, int flags));
	int	(*um_iupdat) __P((struct inode *ip,
		    struct timeval *ta, struct timeval *tm, int waitfor));
	int	(*um_bwrite)		/* XXX changes */
		    __P((struct buf *bp));
	int	(*um_bmap)		/* XXX changes */
		    __P((struct inode *ip, daddr_t bn, daddr_t *bnp));
E 19
E 18
E 13
D 12
	char	um_mntname[MNAMELEN];	/* mounted filesystem */
E 12
E 11
E 6
D 5
} mount[NMOUNT];
E 5
I 5
};
I 27

E 27
D 13
#ifdef KERNEL
E 13
D 11
struct	mount mount[NMOUNT];
E 11
I 11
/*
D 13
 * Convert mount ptr to ufsmount ptr.
E 13
I 13
 * Flags describing the state of quotas.
E 13
 */
D 13
#define VFSTOUFS(mp)	((struct ufsmount *)((mp)->m_data))
E 13
I 13
D 18
#define	QTF_OPENING	0x01		/* Q_QUOTAON in progress */
#define	QTF_CLOSING	0x02		/* Q_QUOTAOFF in progress */
E 18
I 18
#define	QTF_OPENING	0x01			/* Q_QUOTAON in progress */
#define	QTF_CLOSING	0x02			/* Q_QUOTAOFF in progress */
E 18
E 13

I 13
D 18
#ifdef KERNEL
E 13
/*
D 13
 * mount table
E 13
I 13
 * Convert mount ptr to ufsmount ptr.
E 13
 */
E 18
I 18
/* Convert mount ptr to ufsmount ptr. */
E 18
D 13
extern struct ufsmount	mounttab[NMOUNT];

E 11
#endif
E 13
I 13
D 14
#define VFSTOUFS(mp)	((struct ufsmount *)((mp)->m_data))
E 14
I 14
#define VFSTOUFS(mp)	((struct ufsmount *)((mp)->mnt_data))
I 24

/*
 * Macros to access file system parameters in the ufsmount structure.
 * Used by ufs_bmap.
 */
D 27
#define	blkptrtodb(ump, b)	((b) << (ump)->um_bptrtodb)
#define	is_sequential(ump, a, b) ((b) == (a) + ump->um_seqinc)
#define MNINDIR(ump)	((ump)->um_nindir)


E 27
I 27
#define MNINDIR(ump)			((ump)->um_nindir)
#define	blkptrtodb(ump, b)		((b) << (ump)->um_bptrtodb)
#define	is_sequential(ump, a, b)	((b) == (a) + ump->um_seqinc)
I 30
#endif /* KERNEL */
E 30
E 27
E 24
E 14
D 18
#endif /* KERNEL */
I 16

/*
 * Prototypes for UFS mount operations
 */
D 17
int	ufs_mount __P((
		struct mount *mp,
		char *path,
		caddr_t data,
		struct nameidata *ndp,
		struct proc *p));
int	ufs_start __P((
		struct mount *mp,
		int flags,
		struct proc *p));
int	ufs_unmount __P((
		struct mount *mp,
		int mntflags,
		struct proc *p));
int	ufs_root __P((
		struct mount *mp,
		struct vnode **vpp));
int	ufs_quotactl __P((
		struct mount *mp,
		int cmds,
		int uid,	/* should be uid_t */
		caddr_t arg,
		struct proc *p));
int	ufs_statfs __P((
		struct mount *mp,
		struct statfs *sbp,
		struct proc *p));
int	ufs_sync __P((
		struct mount *mp,
		int waitfor));
int	ufs_fhtovp __P((
		struct mount *mp,
		struct fid *fhp,
		struct vnode **vpp));
int	ufs_vptofh __P((
		struct vnode *vp,
		struct fid *fhp));
int	ufs_init __P(());
E 17
I 17
int ufs_mount __P((struct mount *mp, char *path, caddr_t data,
	struct nameidata *ndp, struct proc *p));
int ufs_start __P((struct mount *mp, int flags, struct proc *p));
int ufs_unmount __P((struct mount *mp, int mntflags, struct proc *p));
int ufs_root __P((struct mount *mp, struct vnode **vpp));
int ufs_quotactl __P((struct mount *mp, int cmds, int uid, /* should be uid_t */
	caddr_t arg, struct proc *p));
int ufs_statfs __P((struct mount *mp, struct statfs *sbp, struct proc *p));
int ufs_sync __P((struct mount *mp, int waitfor));
int ufs_fhtovp __P((struct mount *mp, struct fid *fhp, struct vnode **vpp));
int ufs_vptofh __P((struct vnode *vp, struct fid *fhp));
int ufs_init __P(());
E 18
E 17
E 16
E 13
E 5
E 1
