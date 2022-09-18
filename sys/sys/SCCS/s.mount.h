h07524
s 00026/00024/00264
d D 8.21 95/05/20 01:21:50 mckusick 66 65
c merge vfs_lock and vfs_busy; interlock mount points properly
e
s 00004/00001/00284
d D 8.20 95/05/10 13:24:34 mckusick 65 64
c add vfs_rootmountalloc and vfs_mountroot
e
s 00001/00000/00284
d D 8.19 95/05/10 12:43:04 mckusick 64 63
c add vfc_mountroot entry to vfsconf
e
s 00003/00002/00281
d D 8.18 95/05/09 12:03:14 mckusick 63 62
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00079/00186/00204
d D 8.17 95/03/30 14:07:19 mckusick 62 61
c add filesystem type name to statfs structure; type numbers go away;
c add sysctl information for VFS layer and add vfs_sysctl operation;
c move out ufs_args and mfs_args to ufs/ufs/ufsmount.h;
c move out iso_args to isofs/cd9660/cd9660_mount.h;
c move out nfs_args and NFSMNT_* flags to nfs/nfs.h;
c add vfsconf structure
e
s 00016/00018/00374
d D 8.16 95/01/09 18:16:29 cgd 61 60
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00002/00002/00390
d D 8.15 94/07/14 11:47:11 mckusick 60 59
c move mnt_owner into mnt_stat structure, so it is externally visible
e
s 00001/00001/00391
d D 8.14 94/07/13 00:26:23 mckusick 59 58
c add mnt_owner to record uid that did a mount; no longer need MNT_USER
e
s 00000/00001/00392
d D 8.13 94/03/27 08:15:36 bostic 58 57
c The NOTRANS option was one I added to mount.h (but never implemented in the
c FS code).  It turns out that a combination of -norrip and -gen will not do
c name translation.  Hence, we should pull out the -t option for mount_cd9660
c and the ISOFSMNT_NOTRANS flag.
c From: mike@cs.utah.edu (Mike Hibler)
e
s 00001/00000/00392
d D 8.12 94/02/20 16:58:14 pendry 57 56
c add MNT_USER flag
e
s 00001/00001/00391
d D 8.11 94/02/11 18:30:25 pendry 56 55
c fix typo
e
s 00004/00002/00388
d D 8.10 94/01/28 13:16:40 pendry 55 54
c adde union fs
e
s 00004/00004/00386
d D 8.9 94/01/23 23:48:36 mckusick 54 53
c ISOFS => CD9660
e
s 00001/00001/00389
d D 8.8 94/01/23 18:16:43 mckusick 53 52
c last vestage of MOUNT_PC
e
s 00001/00000/00389
d D 8.7 94/01/13 12:59:42 hibler 52 51
c MOUNT_AFS got lost in the last delta
e
s 00057/00017/00332
d D 8.6 94/01/12 14:33:05 hibler 51 50
c reorganization for generic support of export information,
c add ISOFS mount info.
e
s 00001/00000/00348
d D 8.5 94/01/11 23:08:42 mckusick 50 49
c add MNT_ASYNC flag to run your filesystem dangerously
e
s 00014/00013/00334
d D 8.4 94/01/04 15:59:54 mckusick 49 48
c add definition for Andrew filesystem
c renamed MOUNT_PC -> MOUNT_MSDOS
e
s 00004/00002/00343
d D 8.3 93/12/15 02:08:37 pendry 48 47
c added MOUNT_PROCFS
e
s 00011/00009/00334
d D 8.2 93/12/14 00:14:16 mckusick 47 44
c convert mount list and mount point vnode list to use <sys/queue.h>
e
s 00011/00009/00334
d R 8.2 93/12/14 00:03:47 mckusick 46 44
c convert mount list and mount point vnode list to use <sys/queue.h>
e
s 00010/00009/00334
d R 8.2 93/12/13 23:46:38 mckusick 45 44
c convert mount list and mount point vnode list to use <sys/queue.h>
e
s 00002/00002/00341
d D 8.1 93/06/02 19:54:17 bostic 44 43
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00338
d D 7.41 92/11/15 21:54:15 mckusick 43 42
c add RELOAD flag to reload filesystem after fsck; FORCE flag now
c applies to both mount and unmount; pseudo flag WANTRDWR for ro -> rw requests
e
s 00009/00026/00332
d D 7.40 92/08/11 23:21:51 mckusick 42 41
c use radix tree code to match exported host addresses rather than adhoc hash code
e
s 00001/00000/00357
d D 7.39 92/07/20 16:01:37 pendry 41 40
c add flag for union mounts
e
s 00004/00002/00353
d D 7.38 92/07/18 12:56:24 pendry 40 39
c added kernfs
e
s 00018/00001/00337
d D 7.37 92/07/09 22:19:38 mckusick 39 38
c add NULL and UMAP types for heidemann; add filesystem names array
e
s 00005/00002/00333
d D 7.36 92/07/06 18:24:09 mckusick 38 37
c new arguments to FHTOVP
e
s 00003/00000/00332
d D 7.35 92/07/03 01:32:52 mckusick 37 36
c VOP_VGET moves to VFS_VGET
e
s 00006/00007/00326
d D 7.34 92/06/25 12:50:31 mckusick 36 35
c quotactl now takes uid_t; VFS_SYNC gets cred and proc; 
c VFS_FHTOVP drops setgen bogosity
e
s 00001/00000/00332
d D 7.33 92/06/20 16:56:48 mckusick 35 34
c add mnt_maxsymlinklen for short links
e
s 00004/00001/00328
d D 7.32 92/05/31 21:22:11 pendry 34 33
c add types for LOFS, FDESC, PORTAL file systems
e
s 00001/00000/00328
d D 7.31 92/03/17 17:06:33 mckusick 33 32
c add NFSMNT_RESVPORT to request a reserved port on connect
e
s 00073/00020/00255
d D 7.30 92/01/09 21:59:40 mckusick 32 31
c support for NFS leases
e
s 00001/00001/00274
d D 7.29 91/12/19 12:32:02 mckusick 31 30
c fsid_t is not really a quad, it is two longs
e
s 00003/00000/00272
d D 7.28 91/12/14 21:41:42 mckusick 30 29
c pull in <sys/ucred.h> for user programs
e
s 00012/00003/00260
d D 7.27 91/12/14 21:05:33 mckusick 29 28
c additions for new export semantics
e
s 00002/00002/00261
d D 7.26 91/12/14 21:02:34 mckusick 28 27
c statfs.f_bsize => statfs.f_iosize; 
c statfs.f_fsize =>statfs.f_bsize (to be compatible with SunOS naming)
e
s 00001/00001/00262
d D 7.25 91/11/01 16:33:08 bostic 27 26
c lint in vfs_quotactl function prototype
e
s 00011/00010/00252
d D 7.24 91/10/10 10:58:28 bostic 26 25
c add LFS mount type
e
s 00002/00002/00260
d D 7.23 91/09/06 17:26:25 ralph 25 24
c add extern to zero dimention arrays.
e
s 00002/00000/00260
d D 7.22 91/06/03 15:45:06 mckusick 24 23
c hide more kernel-only things
e
s 00038/00050/00222
d D 7.21 91/05/07 19:55:38 karels 23 22
c reformat prototypes to spec, other KNF; #ifdef __STDC__ for structure
c declarations (even though probably not necessary)
e
s 00051/00022/00221
d D 7.20 91/04/15 23:28:10 mckusick 22 21
c add prototypes for VFS ops; add proc pointer to several VFS ops;
c add prototypes for exported VFS routines
e
s 00003/00003/00240
d D 7.19 91/03/16 12:35:41 donn 21 19
c A few more prototype tweaks.
e
s 00001/00001/00242
d R 7.19 91/02/23 16:24:39 donn 20 19
c It's just fhandle_t, not struct fhandle_t!
e
s 00014/00000/00229
d D 7.18 91/02/22 10:37:01 donn 19 18
c Prototype declarations.
e
s 00001/00000/00228
d D 7.17 90/10/01 14:03:27 mckusick 18 17
c add NFSMNT_COMPRESS flag
e
s 00001/00011/00227
d D 7.16 90/06/28 21:59:34 bostic 17 16
c new copyright notice
e
s 00001/00000/00237
d D 7.15 90/06/21 11:57:16 mckusick 16 15
c add spongy mount flag
e
s 00014/00008/00223
d D 7.14 90/05/14 11:26:28 mckusick 15 14
c update from Rick Macklem (for TCP based NFS)
e
s 00035/00035/00196
d D 7.13 90/05/04 20:54:23 mckusick 14 13
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00021/00011/00210
d D 7.12 90/05/02 19:23:29 mckusick 13 12
c add quotactl function; add QUOTA and LOCAL flags
e
s 00035/00035/00185
d D 7.11 90/03/06 16:28:31 mckusick 12 11
c move statfs structure into mount entry to cache info
e
s 00011/00007/00209
d D 7.10 89/10/31 17:16:58 mckusick 11 10
c define set of flags exported by statfs()
e
s 00001/00000/00215
d D 7.9 89/10/29 22:49:56 mckusick 10 9
c add a filesystem init entry to be called at boot time
e
s 00001/00000/00214
d D 7.8 89/10/25 11:21:36 mckusick 9 7
c add reserved field to fid to ensure longword alignment (from Macklem)
e
s 00003/00000/00214
d R 7.8 89/10/24 18:06:26 mckusick 8 7
c put fileno and generation number in file identifier (from Macklem)
e
s 00012/00011/00202
d D 7.7 89/10/24 18:05:43 mckusick 7 6
c add linked list of vnodes associated with the mount point;
c other minor cleanups in formatting
e
s 00001/00000/00212
d D 7.6 89/10/18 19:18:10 mckusick 6 5
c add M_UPDATE flag to allow selective file system update
e
s 00030/00031/00182
d D 7.5 89/09/05 23:08:49 mckusick 5 4
c add VFS_START entry for memory filesystem;
c reorder flags into consistent groups;
c expand size of statfs structure to allow for longer names;
c delete unused macros
e
s 00004/00003/00209
d D 7.4 89/05/27 16:32:16 mckusick 4 3
c further changes from Rick Macklem
e
s 00016/00007/00196
d D 7.3 89/05/09 16:14:58 mckusick 3 2
c changes from Rick Macklem for NFS
e
s 00010/00000/00193
d D 7.2 89/04/24 21:21:51 mckusick 2 1
c update from Rick Macklem for NFS
e
s 00193/00000/00000
d D 7.1 89/04/24 19:09:44 mckusick 1 0
c first bootable vnodes
e
u
U
t
T
I 1
/*
D 26
 * Copyright (c) 1989 The Regents of the University of California.
E 26
I 26
D 44
 * Copyright (c) 1989, 1991 The Regents of the University of California.
E 26
 * All rights reserved.
E 44
I 44
 * Copyright (c) 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 44
 *
D 17
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
 * %sccs.include.redist.c%
E 17
 *
 *	%W% (Berkeley) %G%
 */

I 32
#ifndef KERNEL
#include <sys/ucred.h>
#endif
I 47
#include <sys/queue.h>
I 66
#include <sys/lock.h>
E 66
I 62
#include <net/radix.h>
#include <sys/socket.h>		/* XXX for AF_MAX */
E 62
E 47

E 32
D 31
typedef quad fsid_t;			/* file system id type */
E 31
I 31
D 61
typedef struct { long val[2]; } fsid_t;		/* file system id type */
E 61
I 61
typedef struct { int32_t val[2]; } fsid_t;	/* file system id type */
E 61
E 31

/*
 * File identifier.
 * These are unique per filesystem on a single machine.
 */
#define	MAXFIDSZ	16

struct fid {
	u_short		fid_len;		/* length of data in bytes */
I 9
	u_short		fid_reserved;		/* force longword alignment */
E 9
	char		fid_data[MAXFIDSZ];	/* data (variable length) */
};

/*
I 12
 * file system statistics
 */

I 62
#define MFSNAMELEN	16	/* length of fs type name, including null */
E 62
D 61
#define MNAMELEN 90	/* length of buffer for returned name */
E 61
I 61
#define	MNAMELEN	90	/* length of buffer for returned name */
E 61

struct statfs {
D 62
	short	f_type;			/* type of filesystem (see below) */
E 62
I 62
	short	f_type;			/* filesystem type number */
E 62
	short	f_flags;		/* copy of mount flags */
D 28
	long	f_fsize;		/* fundamental file system block size */
	long	f_bsize;		/* optimal transfer block size */
E 28
I 28
	long	f_bsize;		/* fundamental file system block size */
	long	f_iosize;		/* optimal transfer block size */
E 28
	long	f_blocks;		/* total data blocks in file system */
	long	f_bfree;		/* free blocks in fs */
	long	f_bavail;		/* free blocks avail to non-superuser */
	long	f_files;		/* total file nodes in file system */
	long	f_ffree;		/* free file nodes in fs */
	fsid_t	f_fsid;			/* file system id */
D 60
	long	f_spare[9];		/* spare for later */
E 60
I 60
	uid_t	f_owner;		/* user that mounted the filesystem */
D 62
	long	f_spare[8];		/* spare for later */
E 62
I 62
	long	f_spare[4];		/* spare for later */
	char	f_fstypename[MFSNAMELEN]; /* fs type name */
E 62
E 60
	char	f_mntonname[MNAMELEN];	/* directory on which mounted */
	char	f_mntfromname[MNAMELEN];/* mounted filesystem */
};
I 23

E 23
/*
D 62
 * File system types.
 */
#define	MOUNT_NONE	0
D 49
#define	MOUNT_UFS	1
#define	MOUNT_NFS	2
#define	MOUNT_MFS	3
#define	MOUNT_PC	4
D 26
#define	MOUNT_MAXTYPE	4
E 26
I 26
#define	MOUNT_LFS	5
D 34
#define	MOUNT_MAXTYPE	5
E 34
I 34
#define	MOUNT_LOFS	6
#define	MOUNT_FDESC	7
#define	MOUNT_PORTAL	8
D 39
#define	MOUNT_MAXTYPE	8
E 39
I 39
#define MOUNT_NULL	9
#define MOUNT_UMAP	10
D 40
#define	MOUNT_MAXTYPE	10
E 40
I 40
#define MOUNT_KERNFS	11
D 48
#define	MOUNT_MAXTYPE	11
E 48
I 48
#define MOUNT_PROCFS	12
#define MOUNT_MAXTYPE	12
E 49
I 49
#define	MOUNT_UFS	1	/* Fast Filesystem */
#define	MOUNT_NFS	2	/* Sun-compatible Network Filesystem */
#define	MOUNT_MFS	3	/* Memory-based Filesystem */
#define	MOUNT_MSDOS	4	/* MS/DOS Filesystem */
#define	MOUNT_LFS	5	/* Log-based Filesystem */
#define	MOUNT_LOFS	6	/* Loopback Filesystem */
#define	MOUNT_FDESC	7	/* File Descriptor Filesystem */
#define	MOUNT_PORTAL	8	/* Portal Filesystem */
D 61
#define MOUNT_NULL	9	/* Minimal Filesystem Layer */
#define MOUNT_UMAP	10	/* User/Group Identifer Remapping Filesystem */
#define MOUNT_KERNFS	11	/* Kernel Information Filesystem */
#define MOUNT_PROCFS	12	/* /proc Filesystem */
I 52
#define MOUNT_AFS	13	/* Andrew Filesystem */
E 52
D 51
#define MOUNT_AFS	13	/* Andrew Filesystem */
#define MOUNT_MAXTYPE	13
E 51
I 51
D 54
#define MOUNT_ISOFS	14	/* ISO9660 (aka CDROM) Filesystem */
E 54
I 54
#define MOUNT_CD9660	14	/* ISO9660 (aka CDROM) Filesystem */
E 54
D 55
#define	MOUNT_MAXTYPE	14
E 55
I 55
#define MOUNT_UNION	15	/* Union (translucent) Filesystem */
E 61
I 61
#define	MOUNT_NULL	9	/* Minimal Filesystem Layer */
#define	MOUNT_UMAP	10	/* User/Group Identifer Remapping Filesystem */
#define	MOUNT_KERNFS	11	/* Kernel Information Filesystem */
#define	MOUNT_PROCFS	12	/* /proc Filesystem */
#define	MOUNT_AFS	13	/* Andrew Filesystem */
#define	MOUNT_CD9660	14	/* ISO9660 (aka CDROM) Filesystem */
#define	MOUNT_UNION	15	/* Union (translucent) Filesystem */
E 61
#define	MOUNT_MAXTYPE	15
E 55
E 51
E 49
E 48
E 40

#define INITMOUNTNAMES { \
	"none",		/*  0 MOUNT_NONE */ \
	"ufs",		/*  1 MOUNT_UFS */ \
	"nfs",		/*  2 MOUNT_NFS */ \
	"mfs",		/*  3 MOUNT_MFS */ \
D 53
	"pc",		/*  4 MOUNT_PC */ \
E 53
I 53
	"msdos",	/*  4 MOUNT_MSDOS */ \
E 53
	"lfs",		/*  5 MOUNT_LFS */ \
	"lofs",		/*  6 MOUNT_LOFS */ \
	"fdesc",	/*  7 MOUNT_FDESC */ \
	"portal",	/*  8 MOUNT_PORTAL */ \
	"null",		/*  9 MOUNT_NULL */ \
	"umap",		/* 10 MOUNT_UMAP */ \
D 40
	0,		/* 11 MOUNT_SPARE */ \
E 40
I 40
	"kernfs",	/* 11 MOUNT_KERNFS */ \
D 48
	0,		/* 12 MOUNT_SPARE */ \
E 48
I 48
	"procfs",	/* 12 MOUNT_PROCFS */ \
D 51
	0,		/* 13 MOUNT_SPARE */ \
E 51
I 51
	"afs",		/* 13 MOUNT_AFS */ \
D 54
	"iso9660fs",	/* 14 MOUNT_ISOFS */ \
E 54
I 54
	"iso9660fs",	/* 14 MOUNT_CD9660 */ \
E 54
D 55
	0,		/* 15 MOUNT_SPARE */ \
E 55
I 55
D 56
	"union",	/* 15 MOUNT_CD9660 */ \
E 56
I 56
	"union",	/* 15 MOUNT_UNION */ \
E 56
	0,		/* 16 MOUNT_SPARE */ \
E 55
E 51
E 48
E 40
}
E 39
E 34
E 26

/*
E 62
E 12
D 26
 * Structure per mounted file system.
 * Each mounted file system has an array of
 * operations and an instance record.
 * The file systems are put on a doubly linked list.
E 26
I 26
 * Structure per mounted file system.  Each mounted file system has an
 * array of operations and an instance record.  The file systems are
 * put on a doubly linked list.
E 26
 */
I 47
LIST_HEAD(vnodelst, vnode);

E 47
struct mount {
D 14
	struct mount	*m_next;		/* next in mount list */
	struct mount	*m_prev;		/* prev in mount list */
	struct vfsops	*m_op;			/* operations on fs */
	struct vnode	*m_vnodecovered;	/* vnode we mounted on */
I 7
	struct vnode	*m_mounth;		/* list of vnodes this mount */
E 7
	int		m_flag;			/* flags */
D 12
	long		m_fsize;		/* fundamental block size */
	long		m_bsize;		/* optimal transfer size */
	fsid_t		m_fsid;			/* identifier */
E 12
	uid_t		m_exroot;		/* exported mapping for uid 0 */
I 12
	struct statfs	m_stat;			/* cache of filesystem stats */
E 12
	qaddr_t		m_data;			/* private data */
E 14
I 14
D 47
	struct mount	*mnt_next;		/* next in mount list */
	struct mount	*mnt_prev;		/* prev in mount list */
E 47
I 47
D 63
	TAILQ_ENTRY(mount) mnt_list;		/* mount list */
E 63
I 63
	CIRCLEQ_ENTRY(mount) mnt_list;		/* mount list */
E 63
E 47
	struct vfsops	*mnt_op;		/* operations on fs */
I 62
	struct vfsconf	*mnt_vfc;		/* configuration info */
E 62
	struct vnode	*mnt_vnodecovered;	/* vnode we mounted on */
D 47
	struct vnode	*mnt_mounth;		/* list of vnodes this mount */
E 47
I 47
	struct vnodelst	mnt_vnodelist;		/* list of vnodes this mount */
I 66
	struct lock	mnt_lock;		/* mount structure lock */
E 66
E 47
	int		mnt_flag;		/* flags */
I 35
	int		mnt_maxsymlinklen;	/* max size of short symlink */
I 59
D 60
	uid_t		mnt_owner;		/* uid that did mount */
E 60
E 59
E 35
D 29
	uid_t		mnt_exroot;		/* exported mapping for uid 0 */
E 29
I 29
D 32
	uid_t		mnt_exroot;		/* XXX - deprecated */
E 32
E 29
	struct statfs	mnt_stat;		/* cache of filesystem stats */
	qaddr_t		mnt_data;		/* private data */
E 14
};

/*
D 5
 * mount flags.
 * M_MLOCK lock the mount entry so that name lookup cannot proceed
 * past the mount point.  This keeps the subtree stable during mounts
 * and unmounts.
E 5
I 5
 * Mount flags.
I 43
 *
 * Unmount uses MNT_FORCE flag.
E 43
E 5
 */
D 11
#define	M_RDONLY	0x01		/* read only filesystem */
#define	M_SYNCHRONOUS	0x02		/* file system written synchronously */
D 5
#define	M_MLOCK		0x04		/* lock so that subtree is stable */
#define	M_MWAIT		0x08		/* someone is waiting for lock */
#define	M_NOEXEC	0x10		/* can't exec from filesystem */
#define	M_NOSUID	0x20		/* don't honor setuid bits on fs */
#define	M_NODEV		0x40		/* don't interpret special files */
E 5
I 5
#define	M_NOEXEC	0x04		/* can't exec from filesystem */
#define	M_NOSUID	0x08		/* don't honor setuid bits on fs */
#define	M_NODEV		0x10		/* don't interpret special files */
E 11
I 11
D 13
#define	M_RDONLY	0x0001		/* read only filesystem */
#define	M_SYNCHRONOUS	0x0002		/* file system written synchronously */
#define	M_NOEXEC	0x0004		/* can't exec from filesystem */
#define	M_NOSUID	0x0008		/* don't honor setuid bits on fs */
#define	M_NODEV		0x0010		/* don't interpret special files */
E 13
I 13
D 14
#define	M_RDONLY	0x00000001	/* read only filesystem */
#define	M_SYNCHRONOUS	0x00000002	/* file system written synchronously */
#define	M_NOEXEC	0x00000004	/* can't exec from filesystem */
#define	M_NOSUID	0x00000008	/* don't honor setuid bits on fs */
#define	M_NODEV		0x00000010	/* don't interpret special files */
E 14
I 14
#define	MNT_RDONLY	0x00000001	/* read only filesystem */
#define	MNT_SYNCHRONOUS	0x00000002	/* file system written synchronously */
#define	MNT_NOEXEC	0x00000004	/* can't exec from filesystem */
#define	MNT_NOSUID	0x00000008	/* don't honor setuid bits on fs */
#define	MNT_NODEV	0x00000010	/* don't interpret special files */
I 41
#define	MNT_UNION	0x00000020	/* union with underlying filesystem */
I 50
#define	MNT_ASYNC	0x00000040	/* file system written asynchronously */
E 50
E 41
I 23

E 23
E 14
E 13
E 11
E 5
/*
 * exported mount flags.
 */
I 29
#define	MNT_EXRDONLY	0x00000080	/* exported read only */
E 29
D 11
#define	M_EXPORTED	0x100		/* file system is exported */
#define	M_EXRDONLY	0x200		/* exported read only */
E 11
I 11
D 13
#define	M_EXPORTED	0x0100		/* file system is exported */
#define	M_EXRDONLY	0x0200		/* exported read only */
E 13
I 13
D 14
#define	M_EXPORTED	0x00000100	/* file system is exported */
#define	M_EXRDONLY	0x00000200	/* exported read only */
E 14
I 14
#define	MNT_EXPORTED	0x00000100	/* file system is exported */
D 29
#define	MNT_EXRDONLY	0x00000200	/* exported read only */
E 29
I 29
#define	MNT_DEFEXPORTED	0x00000200	/* exported to the world */
#define	MNT_EXPORTANON	0x00000400	/* use anon uid mapping for everyone */
#define	MNT_EXKERB	0x00000800	/* exported with Kerberos uid mapping */
E 29
I 23

E 23
E 14
E 13
/*
I 13
 * Flags set by internal operations.
 */
D 14
#define	M_LOCAL		0x00001000	/* filesystem is stored locally */
#define	M_QUOTA		0x00002000	/* quotas are enabled on filesystem */
E 14
I 14
#define	MNT_LOCAL	0x00001000	/* filesystem is stored locally */
#define	MNT_QUOTA	0x00002000	/* quotas are enabled on filesystem */
I 47
#define	MNT_ROOTFS	0x00004000	/* identifies the root filesystem */
I 57
D 59
#define	MNT_USER	0x00008000	/* mounted by a user */
E 59
E 57
E 47
I 23

E 23
E 14
/*
E 13
 * Mask of flags that are visible to statfs()
 */
D 13
#define	M_VISFLAGMASK	0x0fff
E 13
I 13
D 14
#define	M_VISFLAGMASK	0x0000ffff
E 14
I 14
#define	MNT_VISFLAGMASK	0x0000ffff
I 23

E 23
E 14
E 13
E 11
D 5

E 5
/*
D 5
 * Set/clear the M_MLOCK
E 5
I 5
D 66
 * filesystem control flags.
 *
D 14
 * M_MLOCK lock the mount entry so that name lookup cannot proceed
E 14
I 14
 * MNT_MLOCK lock the mount entry so that name lookup cannot proceed
E 14
 * past the mount point.  This keeps the subtree stable during mounts
 * and unmounts.
E 66
I 66
 * External filesystem control flags.
E 66
E 5
 */
D 5
#define	VFSLOCK(mp) { \
	while ((mp)->m_flag & M_MLOCK) { \
		(mp)->m_flag |= M_MWAIT; \
		(void) sleep((caddr_t)(mp), PVFS); \
	} \
	(mp)->m_flag |= M_MLOCK; \
}
E 5
I 5
D 13
#define	M_MLOCK		0x1000		/* lock so that subtree is stable */
#define	M_MWAIT		0x2000		/* someone is waiting for lock */
I 6
#define	M_UPDATE	0x4000		/* not a real mount, just an update */
E 13
I 13
D 14
#define	M_UPDATE	0x00010000	/* not a real mount, just an update */
#define	M_MLOCK		0x00100000	/* lock so that subtree is stable */
#define	M_MWAIT		0x00200000	/* someone is waiting for lock */
#define M_MPBUSY	0x00400000	/* scan of mount point in progress */
#define M_MPWANT	0x00800000	/* waiting for mount point */
#define M_UNMOUNT	0x01000000	/* unmount in progress */
E 14
I 14
#define	MNT_UPDATE	0x00010000	/* not a real mount, just an update */
I 29
#define	MNT_DELEXPORT	0x00020000	/* delete export host lists */
I 43
#define	MNT_RELOAD	0x00040000	/* reload filesystem data */
#define	MNT_FORCE	0x00080000	/* force unmount or readonly change */
E 43
E 29
D 66
#define	MNT_MLOCK	0x00100000	/* lock so that subtree is stable */
#define	MNT_MWAIT	0x00200000	/* someone is waiting for lock */
#define MNT_MPBUSY	0x00400000	/* scan of mount point in progress */
#define MNT_MPWANT	0x00800000	/* waiting for mount point */
E 66
I 66
/*
 * Internal filesystem control flags.
 *
 * MNT_UNMOUNT locks the mount entry so that name lookup cannot proceed
 * past the mount point.  This keeps the subtree stable during mounts
 * and unmounts.
 */
E 66
#define MNT_UNMOUNT	0x01000000	/* unmount in progress */
I 43
D 66
#define MNT_WANTRDWR	0x02000000	/* want upgrade to read/write */
E 66
I 66
#define	MNT_MWAIT	0x02000000	/* waiting for unmount to finish */
#define MNT_WANTRDWR	0x04000000	/* upgrade to read/write requested */
E 66
E 43
E 14
E 13
E 6
E 5

D 5
#define	VFSUNLOCK(mp) { \
	(mp)->m_flag &= ~M_MLOCK; \
	if ((mp)->m_flag&M_MWAIT) { \
		(mp)->m_flag &= ~M_MWAIT; \
		wakeup((caddr_t)(mp)); \
	} \
}

E 5
/*
D 62
 * Operations supported on mounted file system.
E 62
I 62
 * Sysctl CTL_VFS definitions.
 *
 * Second level identifier specifies which filesystem. Second level
 * identifier VFS_GENERIC returns information about all filesystems.
E 62
 */
I 62
#define	VFS_GENERIC		0	/* generic filesystem information */
/*
 * Third level identifiers for VFS_GENERIC are given below; third
 * level identifiers for specific filesystems are given in their
 * mount specific header files.
 */
#define VFS_MAXTYPENUM	1	/* int: highest defined filesystem type */
#define VFS_CONF	2	/* struct: vfsconf for filesystem given
				   as next argument */

/*
 * Flags for various system call interfaces.
 *
 * waitfor flags to vfs_sync() and getfsstat()
 */
#define MNT_WAIT	1
#define MNT_NOWAIT	2

/*
 * Generic file handle
 */
struct fhandle {
	fsid_t	fh_fsid;	/* File system id of mount point */
	struct	fid fh_fid;	/* File sys specific id */
};
typedef struct fhandle	fhandle_t;

/*
 * Export arguments for local filesystem mount calls.
 */
struct export_args {
	int	ex_flags;		/* export related flags */
	uid_t	ex_root;		/* mapping for root uid */
	struct	ucred ex_anon;		/* mapping for anonymous user */
	struct	sockaddr *ex_addr;	/* net address to which exported */
	int	ex_addrlen;		/* and the net address length */
	struct	sockaddr *ex_mask;	/* mask of valid bits in saddr */
	int	ex_masklen;		/* and the smask length */
};

/*
 * Filesystem configuration information. One of these exists for each
 * type of filesystem supported by the kernel. These are searched at
 * mount time to identify the requested filesystem.
 */
struct vfsconf {
	struct	vfsops *vfc_vfsops;	/* filesystem operations vector */
	char	vfc_name[MFSNAMELEN];	/* filesystem type name */
	int	vfc_typenum;		/* historic filesystem type number */
	int	vfc_refcount;		/* number mounted of this type */
	int	vfc_flags;		/* permanent flags */
I 64
	int	(*vfc_mountroot)(void);	/* if != NULL, routine to mount root */
E 64
	struct	vfsconf *vfc_next;	/* next in list */
};

E 62
I 24
#ifdef KERNEL
I 62

extern int maxvfsconf;		/* highest defined filesystem type */
extern struct vfsconf *vfsconf;	/* head of list of filesystem types */

/*
 * Operations supported on mounted file system.
 */
E 62
E 24
I 23
#ifdef __STDC__
E 23
I 22
struct nameidata;
I 38
struct mbuf;
E 38
I 23
#endif

E 23
E 22
struct vfsops {
D 22
	int	(*vfs_mount)(	/* mp, path, data, ndp */ );
I 5
	int	(*vfs_start)(	/* mp, flags */ );
E 5
	int	(*vfs_unmount)(	/* mp, forcibly */ );
	int	(*vfs_root)(	/* mp, vpp */ );
I 13
	int	(*vfs_quotactl)(/* mp, cmd, uid, arg */ );
E 13
	int	(*vfs_statfs)(	/* mp, sbp */ );
	int	(*vfs_sync)(	/* mp, waitfor */ );
D 3
	int	(*vfs_fhtovp)(	/* mp, fhp, vpp */ );
I 2
	int	(*vfs_vptofh)(	/* vp, fhp */ );
E 3
I 3
	int	(*vfs_fhtovp)(	/* mp, fidp, vpp */ );
	int	(*vfs_vptofh)(	/* vp, fidp */ );
I 10
	int	(*vfs_init)(	/* */ );
E 22
I 22
D 23
	int	(*vfs_mount)__P((
			struct mount *mp,
			char *path,
			caddr_t data,
			struct nameidata *ndp,
			struct proc *p));
	int	(*vfs_start)__P((
			struct mount *mp,
			int flags,
			struct proc *p));
	int	(*vfs_unmount)__P((
			struct mount *mp,
			int mntflags,
			struct proc *p));
	int	(*vfs_root)__P((
			struct mount *mp,
			struct vnode **vpp));
	int	(*vfs_quotactl)__P((
			struct mount *mp,
			int cmds,
			int uid,		/* should be uid_t */
			caddr_t arg,
			struct proc *p));
	int	(*vfs_statfs)__P((
			struct mount *mp,
			struct statfs *sbp,
			struct proc *p));
	int	(*vfs_sync)__P((
			struct mount *mp,
			int waitfor));
	int	(*vfs_fhtovp)__P((
			struct mount *mp,
			struct fid *fhp,
			struct vnode **vpp));
	int	(*vfs_vptofh)__P((
			struct vnode *vp,
			struct fid *fhp));
	int	(*vfs_init)__P(());
E 23
I 23
	int	(*vfs_mount)	__P((struct mount *mp, char *path, caddr_t data,
				    struct nameidata *ndp, struct proc *p));
	int	(*vfs_start)	__P((struct mount *mp, int flags,
				    struct proc *p));
	int	(*vfs_unmount)	__P((struct mount *mp, int mntflags,
				    struct proc *p));
	int	(*vfs_root)	__P((struct mount *mp, struct vnode **vpp));
D 36
			/* int uid,		should be uid_t */
D 27
	int	(*vfs_quotactl)	__P((struct mount *mp, int cmds, int uid,
E 27
I 27
	int	(*vfs_quotactl)	__P((struct mount *mp, int cmds, u_int uid,
E 36
I 36
	int	(*vfs_quotactl)	__P((struct mount *mp, int cmds, uid_t uid,
E 36
E 27
				    caddr_t arg, struct proc *p));
	int	(*vfs_statfs)	__P((struct mount *mp, struct statfs *sbp,
				    struct proc *p));
D 36
	int	(*vfs_sync)	__P((struct mount *mp, int waitfor));
E 36
I 36
	int	(*vfs_sync)	__P((struct mount *mp, int waitfor,
				    struct ucred *cred, struct proc *p));
I 37
	int	(*vfs_vget)	__P((struct mount *mp, ino_t ino,
				    struct vnode **vpp));
E 37
E 36
	int	(*vfs_fhtovp)	__P((struct mount *mp, struct fid *fhp,
D 32
				    struct vnode **vpp));
E 32
I 32
D 36
				    int setgen, struct vnode **vpp));
E 36
I 36
D 38
				    struct vnode **vpp));
E 38
I 38
				    struct mbuf *nam, struct vnode **vpp,
				    int *exflagsp, struct ucred **credanonp));
E 38
E 36
E 32
	int	(*vfs_vptofh)	__P((struct vnode *vp, struct fid *fhp));
D 26
	int	(*vfs_init)	__P(());
E 26
I 26
D 62
	int	(*vfs_init)	__P((void));
E 62
I 62
	int	(*vfs_init)	__P((struct vfsconf *));
	int	(*vfs_sysctl)	__P((int *, u_int, void *, size_t *, void *,
				    size_t, struct proc *));
E 62
E 26
E 23
E 22
E 10
E 3
E 2
};

D 22
#define VFS_MOUNT(MP, PATH, DATA, NDP) \
D 14
	(*(MP)->m_op->vfs_mount)(MP, PATH, DATA, NDP)
I 5
#define VFS_START(MP, FLAGS)	  (*(MP)->m_op->vfs_start)(MP, FLAGS)
E 5
#define VFS_UNMOUNT(MP, FORCIBLY) (*(MP)->m_op->vfs_unmount)(MP, FORCIBLY)
D 5
#define VFS_ROOT(MP, VPP)	  (*(MP)->m_op->vfs_root)(MP,VPP)
E 5
I 5
#define VFS_ROOT(MP, VPP)	  (*(MP)->m_op->vfs_root)(MP, VPP)
I 13
#define VFS_QUOTACTL(MP, C, U, A) (*(MP)->m_op->vfs_quotactl)(MP, C, U, A)
E 13
E 5
#define VFS_STATFS(MP, SBP)	  (*(MP)->m_op->vfs_statfs)(MP, SBP)
#define VFS_SYNC(MP, WAITFOR)	  (*(MP)->m_op->vfs_sync)(MP, WAITFOR)
D 3
#define VFS_FHTOVP(MP, FHP, VPP)  (*(MP)->m_op->vfs_fhtovp)(MP, FHP, VPP)
I 2
#define	VFS_VPTOFH(VP, FHP)	  (*(VP)->v_mount->m_op->vfs_vptofh)(VP, FHP)
E 3
I 3
#define VFS_FHTOVP(MP, FIDP, VPP) (*(MP)->m_op->vfs_fhtovp)(MP, FIDP, VPP)
#define	VFS_VPTOFH(VP, FIDP)	  (*(VP)->v_mount->m_op->vfs_vptofh)(VP, FIDP)
E 14
I 14
	(*(MP)->mnt_op->vfs_mount)(MP, PATH, DATA, NDP)
#define VFS_START(MP, FLAGS)	  (*(MP)->mnt_op->vfs_start)(MP, FLAGS)
#define VFS_UNMOUNT(MP, FORCIBLY) (*(MP)->mnt_op->vfs_unmount)(MP, FORCIBLY)
E 22
I 22
#define VFS_MOUNT(MP, PATH, DATA, NDP, P) \
	(*(MP)->mnt_op->vfs_mount)(MP, PATH, DATA, NDP, P)
#define VFS_START(MP, FLAGS, P)	  (*(MP)->mnt_op->vfs_start)(MP, FLAGS, P)
#define VFS_UNMOUNT(MP, FORCE, P) (*(MP)->mnt_op->vfs_unmount)(MP, FORCE, P)
E 22
#define VFS_ROOT(MP, VPP)	  (*(MP)->mnt_op->vfs_root)(MP, VPP)
D 22
#define VFS_QUOTACTL(MP, C, U, A) (*(MP)->mnt_op->vfs_quotactl)(MP, C, U, A)
#define VFS_STATFS(MP, SBP)	  (*(MP)->mnt_op->vfs_statfs)(MP, SBP)
E 22
I 22
#define VFS_QUOTACTL(MP,C,U,A,P)  (*(MP)->mnt_op->vfs_quotactl)(MP, C, U, A, P)
#define VFS_STATFS(MP, SBP, P)	  (*(MP)->mnt_op->vfs_statfs)(MP, SBP, P)
E 22
D 36
#define VFS_SYNC(MP, WAITFOR)	  (*(MP)->mnt_op->vfs_sync)(MP, WAITFOR)
D 32
#define VFS_FHTOVP(MP, FIDP, VPP) (*(MP)->mnt_op->vfs_fhtovp)(MP, FIDP, VPP)
E 32
I 32
#define VFS_FHTOVP(MP, FIDP, SG, VPP) \
	(*(MP)->mnt_op->vfs_fhtovp)(MP, FIDP, SG, VPP)
E 36
I 36
#define VFS_SYNC(MP, WAIT, C, P)  (*(MP)->mnt_op->vfs_sync)(MP, WAIT, C, P)
I 37
#define VFS_VGET(MP, INO, VPP)	  (*(MP)->mnt_op->vfs_vget)(MP, INO, VPP)
E 37
D 38
#define VFS_FHTOVP(MP, FIDP, VPP) (*(MP)->mnt_op->vfs_fhtovp)(MP, FIDP, VPP)
E 38
I 38
#define VFS_FHTOVP(MP, FIDP, NAM, VPP, EXFLG, CRED) \
	(*(MP)->mnt_op->vfs_fhtovp)(MP, FIDP, NAM, VPP, EXFLG, CRED)
E 38
E 36
E 32
#define	VFS_VPTOFH(VP, FIDP)	  (*(VP)->v_mount->mnt_op->vfs_vptofh)(VP, FIDP)
I 24
D 62
#endif /* KERNEL */
E 62
E 24
E 14
E 3
E 2

/*
I 12
D 62
 * Flags for various system call interfaces.
 *
E 12
D 43
 * forcibly flags for vfs_umount().
E 43
D 12
 * waitfor flags to vfs_sync()
E 12
I 12
 * waitfor flags to vfs_sync() and getfsstat()
E 12
 */
D 43
#define MNT_FORCE	1
#define MNT_NOFORCE	2
E 43
#define MNT_WAIT	1
#define MNT_NOWAIT	2
D 12

/*
 * file system statistics
 */

D 5
#define MNAMELEN 32	/* length of buffer for returned name */
E 5
I 5
#define MNAMELEN 90	/* length of buffer for returned name */
E 5

struct statfs {
	short	f_type;			/* type of filesystem (see below) */
	short	f_flags;		/* copy of mount flags */
	long	f_fsize;		/* fundamental file system block size */
	long	f_bsize;		/* optimal transfer block size */
	long	f_blocks;		/* total data blocks in file system */
	long	f_bfree;		/* free blocks in fs */
	long	f_bavail;		/* free blocks avail to non-superuser */
	long	f_files;		/* total file nodes in file system */
	long	f_ffree;		/* free file nodes in fs */
	fsid_t	f_fsid;			/* file system id */
D 5
	long	f_spare[6];		/* spare for later */
E 5
I 5
	long	f_spare[9];		/* spare for later */
E 5
	char	f_mntonname[MNAMELEN];	/* directory on which mounted */
	char	f_mntfromname[MNAMELEN];/* mounted filesystem */
};
/*
 * File system types.
 */
#define	MOUNT_NONE	0
#define	MOUNT_UFS	1
#define	MOUNT_NFS	2
D 5
#define	MOUNT_PC	3
#define	MOUNT_MAXTYPE	3
E 5
I 5
#define MOUNT_MFS	3
#define	MOUNT_PC	4
#define	MOUNT_MAXTYPE	4
E 12
E 5

/*
D 7
 * Arguments to mount UFS
 */
struct ufs_args {
	char	*fspec;
};

I 3
/*
E 7
 * Generic file handle
 */
struct fhandle {
	fsid_t	fh_fsid;	/* File system id of mount point */
D 32
	struct	fid fh_fid;	/* Id of file */
E 32
I 32
	struct	fid fh_fid;	/* File sys specific id */
E 32
};
typedef struct fhandle	fhandle_t;
I 5

I 7
D 42
/*
I 32
 * Network address hash list element
 */
union nethostaddr {
	u_long had_inetaddr;
	struct mbuf *had_nam;
};
E 42
I 42
#ifdef KERNEL
#include <net/radix.h>
I 51
#include <sys/socket.h>		/* XXX for AF_MAX */
E 51
E 42

D 42
struct netaddrhash {
	struct netaddrhash *neth_next;
	struct ucred	neth_anon;
	u_short		neth_family;
	union nethostaddr neth_haddr;
	union nethostaddr neth_hmask;
	int		neth_exflags;
};
#define	neth_inetaddr	neth_haddr.had_inetaddr
#define	neth_inetmask	neth_hmask.had_inetaddr
#define	neth_nam	neth_haddr.had_nam
#define	neth_msk	neth_hmask.had_nam

E 42
/*
E 62
D 42
 * Network address hashing defs.
E 42
I 42
 * Network address lookup element
E 42
 */
D 42
#define	NETHASHSZ	8	/* Must be a power of 2 <= 256 */
#define	NETMASK_HASH	NETHASHSZ /* Last hash table element is for networks */
#define	NETADDRHASH(a)	\
	(((a)->sa_family == AF_INET) ? ((a)->sa_data[5] & (NETHASHSZ - 1)) : \
	 (((a)->sa_family == AF_ISO) ? iso_addrhash(a) : 0))
E 42
I 42
struct netcred {
	struct	radix_node netc_rnodes[2];
	int	netc_exflags;
	struct	ucred netc_anon;
};
I 51

/*
 * Network export information
 */
struct netexport {
	struct	netcred ne_defexported;		      /* Default export */
	struct	radix_node_head *ne_rtable[AF_MAX+1]; /* Individual exports */
};
E 51
D 62
#endif /* KERNEL */
E 62
E 42

/*
I 51
D 62
 * Export arguments for local filesystem mount calls.
 */
struct export_args {
	int	ex_flags;		/* export related flags */
	uid_t	ex_root;		/* mapping for root uid */
	struct	ucred ex_anon;		/* mapping for anonymous user */
	struct	sockaddr *ex_addr;	/* net address to which exported */
	int	ex_addrlen;		/* and the net address length */
	struct	sockaddr *ex_mask;	/* mask of valid bits in saddr */
	int	ex_masklen;		/* and the smask length */
};

/*
E 51
E 32
D 26
 * Arguments to mount UFS
E 26
I 26
D 29
 * Arguments to mount LFS/UFS
E 29
I 29
 * Arguments to mount UFS-based filesystems
E 29
E 26
 */
I 30
D 32
#ifndef KERNEL
#include <sys/ucred.h>
#endif
E 32
E 30
struct ufs_args {
D 51
	char	*fspec;		/* block special device to mount */
	int	exflags;	/* export related flags */
	uid_t	exroot;		/* mapping for root uid */
I 29
	struct	ucred anon;	/* mapping for anonymous user */
	struct	sockaddr *saddr;/* net address to which exported */
	int	slen;		/* and the net address length */
	struct	sockaddr *smask;/* mask of valid bits in saddr */
	int	msklen;		/* and the smask length */
E 51
I 51
	char	*fspec;			/* block special device to mount */
	struct	export_args export;	/* network export information */
E 51
E 29
};

E 7
#ifdef MFS
/*
 * Arguments to mount MFS
 */
struct mfs_args {
D 7
	char	*name;
	caddr_t	base;
	u_long size;
E 7
I 7
D 51
	char	*name;		/* name to export for statfs */
	caddr_t	base;		/* base address of file system in memory */
	u_long size;		/* size of file system */
E 51
I 51
	char	*fspec;			/* name to export for statfs */
	struct	export_args export;	/* if exported MFSes are supported */
	caddr_t	base;			/* base of file system in memory */
D 61
	u_long size;			/* size of file system */
E 61
I 61
	u_long	size;			/* size of file system */
E 61
E 51
E 7
};
D 26
#endif MFS
E 26
I 26
#endif /* MFS */
E 26
E 5

I 51
D 54
#ifdef ISOFS
E 54
I 54
#ifdef CD9660
E 54
/*
 * Arguments to mount ISO 9660 filesystems.
 */
struct iso_args {
D 61
	char *fspec;			/* block special device to mount */
E 61
I 61
	char	*fspec;			/* block special device to mount */
E 61
	struct	export_args export;	/* network export info */
D 61
	int flags;			/* mounting flags, see below */

E 61
I 61
	int	flags;			/* mounting flags, see below */
E 61
};
D 61
#define ISOFSMNT_NORRIP		0x00000001 /* disable Rock Ridge Ext.*/
#define ISOFSMNT_GENS		0x00000002 /* enable generation numbers */
#define ISOFSMNT_EXTATT		0x00000004 /* enable extended attributes */
E 61
I 61
#define	ISOFSMNT_NORRIP	0x00000001	/* disable Rock Ridge Ext.*/
#define	ISOFSMNT_GENS	0x00000002	/* enable generation numbers */
#define	ISOFSMNT_EXTATT	0x00000004	/* enable extended attributes */
E 61
D 58
#define ISOFSMNT_NOTRANS	0x00000008 /* disable filename translation */
E 58
D 54
#endif /* ISOFS */
E 54
I 54
#endif /* CD9660 */
E 54

E 51
E 3
#ifdef NFS
I 2
/*
 * File Handle (32 bytes for version 2), variable up to 1024 for version 3
 */
D 3
struct fhandle {
E 3
I 3
D 4
struct nfsv2fh {
E 3
	u_char	fh_bytes[32];
E 4
I 4
union nfsv2fh {
	fhandle_t	fh_generic;
	u_char		fh_bytes[32];
E 4
};
D 3
typedef struct fhandle fhandle_t;
E 3
I 3
D 4
typedef struct nfsv2fh nfsv2fh_t;
E 4
I 4
typedef union nfsv2fh nfsv2fh_t;
E 4
E 3

E 2
/*
 * Arguments to mount NFS
 */
struct nfs_args {
D 15
	struct sockaddr_in	*addr;		/* file server address */
E 15
I 15
D 23
	struct sockaddr		*addr;		/* file server address */
	int			sotype;		/* Socket type */
	int			proto;		/* and Protocol */
E 15
D 3
	fhandle_t		*fh;		/* File handle to be mounted */
E 3
I 3
	nfsv2fh_t		*fh;		/* File handle to be mounted */
E 3
	int			flags;		/* flags */
	int			wsize;		/* write size in bytes */
	int			rsize;		/* read size in bytes */
	int			timeo;		/* initial timeout in .1 secs */
	int			retrans;	/* times to retry send */
	char			*hostname;	/* server's name */
E 23
I 23
	struct sockaddr	*addr;		/* file server address */
I 32
	int		addrlen;	/* length of address */
E 32
	int		sotype;		/* Socket type */
	int		proto;		/* and Protocol */
	nfsv2fh_t	*fh;		/* File handle to be mounted */
	int		flags;		/* flags */
	int		wsize;		/* write size in bytes */
	int		rsize;		/* read size in bytes */
	int		timeo;		/* initial timeout in .1 secs */
	int		retrans;	/* times to retry send */
I 32
	int		maxgrouplist;	/* Max. size of group list */
	int		readahead;	/* # of blocks to readahead */
	int		leaseterm;	/* Term (sec) of lease */
	int		deadthresh;	/* Retrans threshold */
E 32
	char		*hostname;	/* server's name */
E 23
};
I 26

I 32
D 61

E 61
E 32
E 26
/*
 * NFS mount option flags
 */
D 15
#define	NFSMNT_SOFT	0x001	/* soft mount (hard is default) */
#define	NFSMNT_WSIZE	0x002	/* set write size */
#define	NFSMNT_RSIZE	0x004	/* set read size */
#define	NFSMNT_TIMEO	0x008	/* set initial timeout */
#define	NFSMNT_RETRANS	0x010	/* set number of request retrys */
#define	NFSMNT_HOSTNAME	0x020	/* set hostname for error printf */
#define	NFSMNT_INT	0x040	/* allow interrupts on hard mount */
E 15
I 15
D 32
#define	NFSMNT_SOFT	0x0001	/* soft mount (hard is default) */
#define	NFSMNT_WSIZE	0x0002	/* set write size */
#define	NFSMNT_RSIZE	0x0004	/* set read size */
#define	NFSMNT_TIMEO	0x0008	/* set initial timeout */
#define	NFSMNT_RETRANS	0x0010	/* set number of request retrys */
#define	NFSMNT_HOSTNAME	0x0020	/* set hostname for error printf */
#define	NFSMNT_INT	0x0040	/* allow interrupts on hard mount */
#define	NFSMNT_NOCONN	0x0080	/* Don't Connect the socket */
#define	NFSMNT_SCKLOCK	0x0100	/* Lock socket against others */
#define	NFSMNT_WANTSCK	0x0200	/* Want a socket lock */
I 16
#define	NFSMNT_SPONGY	0x0400	/* spongy mount (soft for stat and lookup) */
I 18
#define	NFSMNT_COMPRESS	0x0800	/* Compress nfs rpc xdr */
E 18
E 16
#define	NFSMNT_LOCKBITS	(NFSMNT_SCKLOCK | NFSMNT_WANTSCK)
E 32
I 32
#define	NFSMNT_SOFT		0x00000001  /* soft mount (hard is default) */
#define	NFSMNT_WSIZE		0x00000002  /* set write size */
#define	NFSMNT_RSIZE		0x00000004  /* set read size */
#define	NFSMNT_TIMEO		0x00000008  /* set initial timeout */
D 61
#define	NFSMNT_RETRANS		0x00000010  /* set number of request retrys */
E 61
I 61
#define	NFSMNT_RETRANS		0x00000010  /* set number of request retries */
E 61
#define	NFSMNT_MAXGRPS		0x00000020  /* set maximum grouplist size */
#define	NFSMNT_INT		0x00000040  /* allow interrupts on hard mount */
#define	NFSMNT_NOCONN		0x00000080  /* Don't Connect the socket */
#define	NFSMNT_NQNFS		0x00000100  /* Use Nqnfs protocol */
#define	NFSMNT_MYWRITE		0x00000200  /* Assume writes were mine */
#define	NFSMNT_KERB		0x00000400  /* Use Kerberos authentication */
#define	NFSMNT_DUMBTIMR		0x00000800  /* Don't estimate rtt dynamically */
#define	NFSMNT_RDIRALOOK	0x00001000  /* Do lookup with readdir (nqnfs) */
#define	NFSMNT_LEASETERM	0x00002000  /* set lease term (nqnfs) */
#define	NFSMNT_READAHEAD	0x00004000  /* set read ahead */
#define	NFSMNT_DEADTHRESH	0x00008000  /* set dead server retry thresh */
#define	NFSMNT_NQLOOKLEASE	0x00010000  /* Get lease for lookup */
I 33
#define	NFSMNT_RESVPORT		0x00020000  /* Allocate a reserved port */
E 33
#define	NFSMNT_INTERNAL		0xffe00000  /* Bits set internally */
#define	NFSMNT_MNTD		0x00200000  /* Mnt server for mnt point */
#define	NFSMNT_DISMINPROG	0x00400000  /* Dismount in progress */
#define	NFSMNT_DISMNT		0x00800000  /* Dismounted */
#define	NFSMNT_SNDLOCK		0x01000000  /* Send socket lock */
#define	NFSMNT_WANTSND		0x02000000  /* Want above */
#define	NFSMNT_RCVLOCK		0x04000000  /* Rcv socket lock */
#define	NFSMNT_WANTRCV		0x08000000  /* Want above */
#define	NFSMNT_WAITAUTH		0x10000000  /* Wait for authentication */
#define	NFSMNT_HASAUTH		0x20000000  /* Has authenticator */
#define	NFSMNT_WANTAUTH		0x40000000  /* Wants an authenticator */
#define	NFSMNT_AUTHERR		0x80000000  /* Authentication error */
E 32
E 15
D 26
#endif NFS
E 26
I 26
#endif /* NFS */
E 26

#ifdef KERNEL
/*
E 62
 * exported vnode operations
 */
D 7
extern int	vfs_add();		/* add a new vfs to mounted vfs list */
E 7
D 22
extern void	vfs_remove();		/* remove a vfs from mounted vfs list */
extern int	vfs_lock();		/* lock a vfs */
extern void	vfs_unlock();		/* unlock a vfs */
extern struct	mount *getvfs();	/* return vfs given fsid */
extern struct	mount *rootfs;		/* ptr to root mount structure */
extern struct	vfsops *vfssw[];	/* mount filesystem type switch table */
E 22
I 22
D 47
void	vfs_remove __P((struct mount *mp)); /* remove a vfs from mount list */
int	vfs_lock __P((struct mount *mp));   /* lock a vfs */
void	vfs_unlock __P((struct mount *mp)); /* unlock a vfs */
struct	mount *getvfs __P((fsid_t *fsid));  /* return vfs given fsid */
D 25
struct	mount *rootfs;			    /* ptr to root mount structure */
struct	vfsops *vfssw[];		    /* mount filesystem type table */
E 25
I 25
extern struct	mount *rootfs;		    /* ptr to root mount structure */
extern struct	vfsops *vfssw[];	    /* mount filesystem type table */
E 47
I 47
D 51
int	vfs_lock __P((struct mount *mp));	/* lock a vfs */
void	vfs_unlock __P((struct mount *mp));	/* unlock a vfs */
struct	mount *getvfs __P((fsid_t *fsid));	/* return vfs given fsid */
E 51
I 51
D 62
struct	mount *getvfs __P((fsid_t *));      /* return vfs given fsid */
E 62
D 66
int	vfs_export			    /* process mount export info */
	  __P((struct mount *, struct netexport *, struct export_args *));
I 62
struct	mount *vfs_getvfs __P((fsid_t *));      /* return vfs given fsid */
E 62
struct	netcred *vfs_export_lookup	    /* lookup host in fs export list */
	  __P((struct mount *, struct netexport *, struct mbuf *));
I 65
void	vfs_getnewfsid __P((struct mount *));   /* create a unique fsid */
E 65
int	vfs_lock __P((struct mount *));     /* lock a vfs */
int	vfs_mountedon __P((struct vnode *));/* is a vfs mounted on vp */
I 62
D 65
void	vfs_getnewfsid __P((struct mount *));   /* create a unique fsid */
E 65
I 65
int	vfs_mountroot __P((void));	    /* find and mount root filesystem */
int	vfs_rootmountalloc		    /* alloc root mount structure */
	  __P((char *, char *, struct mount **));
E 65
E 62
void	vfs_unlock __P((struct mount *));   /* unlock a vfs */
E 51
D 63
extern	TAILQ_HEAD(mntlist, mount) mountlist;	/* mounted filesystem list */
E 63
I 63
void	vfs_unmountall __P((void));	    /* unmount all filesystems */
extern	CIRCLEQ_HEAD(mntlist, mount) mountlist;	/* mounted filesystem list */
E 66
I 66
int	vfs_busy __P((struct mount *, int, struct simplelock *, struct proc *));
int	vfs_export __P((struct mount *, struct netexport *,
	    struct export_args *));
struct	netcred *vfs_export_lookup __P((struct mount *, struct netexport *,
	    struct mbuf *));
void	vfs_getnewfsid __P((struct mount *));
struct	mount *vfs_getvfs __P((fsid_t *));
int	vfs_mountedon __P((struct vnode *));
int	vfs_mountroot __P((void));
int	vfs_rootmountalloc __P((char *, char *, struct mount **));
void	vfs_unbusy __P((struct mount *, struct proc *));
void	vfs_unmountall __P((void));
extern	CIRCLEQ_HEAD(mntlist, mount) mountlist;
extern	struct simplelock mountlist_slock;
E 66
E 63
D 62
extern	struct vfsops *vfssw[];			/* filesystem type table */
E 62
E 47
E 25
E 22
I 19
D 23
#else
E 23

I 23
D 62
#else /* KERNEL */
E 62
I 62
#else /* !KERNEL */
E 62

E 23
#include <sys/cdefs.h>

__BEGIN_DECLS
int	fstatfs __P((int, struct statfs *));
D 21
int	getfh __P((const char *, struct fhandle_t *));
int	getfsstat __P((struct statfs **, long, int));
E 21
I 21
int	getfh __P((const char *, fhandle_t *));
int	getfsstat __P((struct statfs *, long, int));
E 21
int	getmntinfo __P((struct statfs **, int));
D 21
int	mount __P((int, const char *, int, caddr_t));
E 21
I 21
D 62
int	mount __P((int, const char *, int, void *));
E 62
I 62
int	mount __P((const char *, const char *, int, void *));
E 62
E 21
int	statfs __P((const char *, struct statfs *));
int	unmount __P((const char *, int));
__END_DECLS

E 19
D 23
#endif
E 23
I 23
#endif /* KERNEL */
E 23
E 1
