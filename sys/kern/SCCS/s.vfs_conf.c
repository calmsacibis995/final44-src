h34946
s 00025/00027/00197
d D 8.11 95/05/10 13:26:11 mckusick 27 26
c add mountroot functions to vfsconf; no longer make FFS default for root
e
s 00071/00082/00153
d D 8.10 95/03/30 14:11:47 mckusick 26 25
c replace vfssw with vfsconf
e
s 00001/00000/00234
d D 8.9 95/03/21 10:47:28 mckusick 25 24
c new include needed for ffs_extern.h
e
s 00001/00012/00233
d D 8.8 94/03/31 08:10:54 pendry 24 23
c eradicate lofs
e
s 00012/00000/00233
d D 8.7 94/01/28 13:16:27 pendry 23 22
c added union fs
e
s 00010/00010/00223
d D 8.6 94/01/25 23:04:32 hibler 22 21
c more ISOFS -> CD9660
e
s 00003/00003/00230
d D 8.5 94/01/25 15:03:54 hibler 21 20
c ISOFS -> CD9660
e
s 00026/00000/00207
d D 8.4 94/01/12 14:42:45 hibler 20 19
c place holders for procfs and afs.
e
s 00011/00000/00196
d D 8.3 93/12/15 02:12:39 pendry 19 18
c added procfs
e
s 00001/00001/00195
d D 8.2 93/09/05 09:36:09 bostic 18 17
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00194
d D 8.1 93/06/10 22:00:33 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00000/00184
d D 7.16 92/07/18 12:59:03 pendry 16 15
c added kernfs
e
s 00026/00002/00158
d D 7.15 92/07/12 11:22:12 heideman 15 14
c add umap and null fs filesystems
e
s 00005/00104/00155
d D 7.14 92/07/06 17:11:04 bostic 14 13
c struct vnodeop_desc *vfs_op_descs[] can be generated mechanically
c move to vnode_if.c
e
s 00000/00002/00259
d D 7.13 92/07/03 01:38:08 mckusick 13 12
c delete vop_vget declaration
e
s 00008/00000/00253
d D 7.12 92/06/23 20:03:23 mckusick 12 11
c add ifdef FIFO's
e
s 00012/00000/00241
d D 7.11 92/06/06 04:57:19 pendry 11 10
c added lofs, fdesc & portal
e
s 00024/00000/00217
d D 7.10 92/06/03 00:07:12 pendry 10 9
c new filesystems: lofs, fdesc, portal.
e
s 00009/00005/00208
d D 7.9 92/05/31 21:35:36 mckusick 9 8
c need ifdefs for optional filesystems
e
s 00144/00000/00069
d D 7.8 92/05/15 12:23:55 heideman 8 7
c new vnode interface config tables added (ops and opvs)
e
s 00001/00000/00068
d D 7.7 92/05/14 12:39:07 heideman 7 6
c sys/vnode.h included for function prototype structures
e
s 00016/00020/00052
d D 7.6 92/02/05 23:12:53 torek 6 5
c make it pretty
e
s 00009/00000/00063
d D 7.5 91/11/01 18:23:53 bostic 5 4
c put FFS stuff on a #define
e
s 00019/00010/00044
d D 7.4 91/11/01 16:39:52 bostic 4 3
c LFS version 1; add LFS file system type
e
s 00001/00011/00053
d D 7.3 90/06/28 21:25:56 bostic 3 2
c new copyright notice
e
s 00010/00001/00054
d D 7.2 89/09/05 23:12:53 mckusick 2 1
c add configuration for memory filesystem
e
s 00055/00000/00000
d D 7.1 89/04/24 20:39:00 mckusick 1 0
c first bootable vnodes
e
u
U
t
T
I 1
/*
D 17
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
D 26
 * Copyright (c) 1989, 1993
E 26
I 26
 * Copyright (c) 1989, 1993, 1995
E 26
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 4
#include "param.h"
#include "mount.h"
E 4
I 4
#include <sys/param.h>
#include <sys/mount.h>
I 7
#include <sys/vnode.h>
E 7
I 5

D 27
#ifdef FFS
I 25
#include <ufs/ufs/dinode.h>
E 25
E 5
#include <ufs/ffs/ffs_extern.h>
E 4

E 27
/*
D 27
 * This specifies the filesystem used to mount the root.
 * This specification should be done by /etc/config.
E 27
I 27
 * These define the root filesystem, device, and root filesystem type.
E 27
 */
D 4
extern int ufs_mountroot();
int (*mountroot)() = ufs_mountroot;
E 4
I 4
D 27
int (*mountroot)() = ffs_mountroot;
I 5
#endif
E 5
E 4

/*
 * These define the root filesystem and device.
 */
E 27
struct mount *rootfs;
D 18
struct vnode *rootdir;
E 18
I 18
struct vnode *rootvnode;
I 27
int (*mountroot)() = NULL;
E 27
E 18

I 27
/*
 * Set up the initial array of known filesystem types.
 */
E 27
I 26
extern	struct vfsops ufs_vfsops;
I 27
extern	int ffs_mountroot();
E 27
extern	struct vfsops lfs_vfsops;
I 27
extern	int lfs_mountroot();
E 27
extern	struct vfsops mfs_vfsops;
I 27
extern	int mfs_mountroot();
E 27
extern	struct vfsops cd9660_vfsops;
I 27
extern	int cd9660_mountroot();
E 27
extern	struct vfsops msdos_vfsops;
extern	struct vfsops adosfs_vfsops;
extern	struct vfsops nfs_vfsops;
I 27
extern	int nfs_mountroot();
E 27
extern	struct vfsops afs_vfsops;
extern	struct vfsops procfs_vfsops;
extern	struct vfsops null_vfsops;
extern	struct vfsops union_vfsops;
extern	struct vfsops umap_vfsops;
extern	struct vfsops portal_vfsops;
extern	struct vfsops fdesc_vfsops;
extern	struct vfsops kernfs_vfsops;

E 26
/*
 * Set up the filesystem operations for vnodes.
D 26
 * The types are defined in mount.h.
E 26
 */
I 26
static struct vfsconf vfsconflist[] = {

	/* Fast Filesystem */
E 26
I 5
#ifdef FFS
E 5
D 26
extern	struct vfsops ufs_vfsops;
I 6
#define	UFS_VFSOPS	&ufs_vfsops
#else
#define	UFS_VFSOPS	NULL
E 26
I 26
D 27
	{ &ufs_vfsops, "ufs", 1, 0, MNT_LOCAL, NULL },
E 27
I 27
	{ &ufs_vfsops, "ufs", 1, 0, MNT_LOCAL, ffs_mountroot, NULL },
E 27
E 26
E 6
I 5
#endif
E 5

I 26
	/* Log-based Filesystem */
E 26
D 4
#ifdef NFS
extern	struct vfsops nfs_vfsops;
E 4
I 4
#ifdef LFS
D 26
extern	struct vfsops lfs_vfsops;
I 6
#define	LFS_VFSOPS	&lfs_vfsops
#else
#define	LFS_VFSOPS	NULL
E 26
I 26
D 27
	{ &lfs_vfsops, "lfs", 5, 0, MNT_LOCAL, NULL },
E 27
I 27
	{ &lfs_vfsops, "lfs", 5, 0, MNT_LOCAL, lfs_mountroot, NULL },
E 27
E 26
E 6
E 4
#endif

I 26
	/* Memory-based Filesystem */
E 26
I 2
#ifdef MFS
D 26
extern	struct vfsops mfs_vfsops;
I 6
#define	MFS_VFSOPS	&mfs_vfsops
#else
#define	MFS_VFSOPS	NULL
E 26
I 26
D 27
	{ &mfs_vfsops, "mfs", 3, 0, MNT_LOCAL, NULL },
E 27
I 27
	{ &mfs_vfsops, "mfs", 3, 0, MNT_LOCAL, mfs_mountroot, NULL },
E 27
E 26
E 6
#endif

I 4
D 26
#ifdef NFS
extern	struct vfsops nfs_vfsops;
I 6
#define	NFS_VFSOPS	&nfs_vfsops
#else
#define	NFS_VFSOPS	NULL
E 26
I 26
	/* ISO9660 (aka CDROM) Filesystem */
#ifdef CD9660
D 27
	{ &cd9660_vfsops, "cd9660", 14, 0, MNT_LOCAL, NULL },
E 27
I 27
	{ &cd9660_vfsops, "cd9660", 14, 0, MNT_LOCAL, cd9660_mountroot, NULL },
E 27
E 26
E 6
#endif

I 10
D 24
#ifdef LOFS
extern	struct vfsops lofs_vfsops;
#define	LOFS_VFSOPS	&lofs_vfsops
#else
#define	LOFS_VFSOPS	NULL
#endif

E 24
D 26
#ifdef FDESC
extern	struct vfsops fdesc_vfsops;
#define	FDESC_VFSOPS	&fdesc_vfsops
#else
#define	FDESC_VFSOPS	NULL
E 26
I 26
	/* MSDOS Filesystem */
#ifdef MSDOS
D 27
	{ &msdos_vfsops, "msdos", 4, 0, MNT_LOCAL, NULL },
E 27
I 27
	{ &msdos_vfsops, "msdos", 4, 0, MNT_LOCAL, NULL, NULL },
E 27
E 26
#endif

D 26
#ifdef PORTAL
extern	struct vfsops portal_vfsops;
#define	PORTAL_VFSOPS	&portal_vfsops
#else
#define	PORTAL_VFSOPS	NULL
E 26
I 26
	/* AmigaDOS Filesystem */
#ifdef ADOSFS
D 27
	{ &adosfs_vfsops, "adosfs", 16, 0, MNT_LOCAL, NULL },
E 27
I 27
	{ &adosfs_vfsops, "adosfs", 16, 0, MNT_LOCAL, NULL, NULL },
E 27
E 26
#endif

I 15
D 26
#ifdef NULLFS
extern	struct vfsops null_vfsops;
#define NULL_VFSOPS	&null_vfsops
#else
#define NULL_VFSOPS	NULL
E 26
I 26
	/* Sun-compatible Network Filesystem */
#ifdef NFS
D 27
	{ &nfs_vfsops, "nfs", 2, 0, 0, NULL },
E 27
I 27
	{ &nfs_vfsops, "nfs", 2, 0, 0, nfs_mountroot, NULL },
E 27
E 26
#endif

D 26
#ifdef UMAPFS
extern	struct vfsops umap_vfsops;
#define UMAP_VFSOPS	&umap_vfsops
#else
#define UMAP_VFSOPS	NULL
E 26
I 26
	/* Andrew Filesystem */
#ifdef AFS
D 27
	{ &afs_vfsops, "andrewfs", 13, 0, 0, NULL },
E 27
I 27
	{ &afs_vfsops, "andrewfs", 13, 0, 0, afs_mountroot, NULL },
E 27
E 26
#endif

I 16
D 26
#ifdef KERNFS
extern	struct vfsops kernfs_vfsops;
#define KERNFS_VFSOPS	&kernfs_vfsops
#else
#define KERNFS_VFSOPS	NULL
E 26
I 26
	/* /proc Filesystem */
#ifdef PROCFS
D 27
	{ &procfs_vfsops, "procfs", 12, 0, 0, NULL },
E 27
I 27
	{ &procfs_vfsops, "procfs", 12, 0, 0, NULL, NULL },
E 27
E 26
#endif
E 16

I 19
D 26
#ifdef PROCFS
extern	struct vfsops procfs_vfsops;
#define PROCFS_VFSOPS	&procfs_vfsops
#else
#define PROCFS_VFSOPS	NULL
E 26
I 26
	/* Loopback (Minimal) Filesystem Layer */
#ifdef NULLFS
D 27
	{ &null_vfsops, "loopback", 9, 0, 0, NULL },
E 27
I 27
	{ &null_vfsops, "loopback", 9, 0, 0, NULL, NULL },
E 27
E 26
#endif
E 19
I 16

I 20
D 26
#ifdef AFS
extern	struct vfsops afs_vfsops;
#define AFS_VFSOPS	&afs_vfsops
#else
#define AFS_VFSOPS	NULL
E 26
I 26
	/* Union (translucent) Filesystem */
#ifdef UNION
D 27
	{ &union_vfsops, "union", 15, 0, 0, NULL },
E 27
I 27
	{ &union_vfsops, "union", 15, 0, 0, NULL, NULL },
E 27
E 26
#endif

D 21
#ifdef ISOFS
E 21
I 21
D 26
#ifdef CD9660
E 21
D 22
extern	struct vfsops isofs_vfsops;
#define ISOFS_VFSOPS	&isofs_vfsops
E 22
I 22
extern	struct vfsops cd9660_vfsops;
#define CD9660_VFSOPS	&cd9660_vfsops
E 22
#else
D 22
#define ISOFS_VFSOPS	NULL
E 22
I 22
#define CD9660_VFSOPS	NULL
E 26
I 26
	/* User/Group Identifer Remapping Filesystem */
#ifdef UMAPFS
D 27
	{ &umap_vfsops, "umap", 10, 0, 0, NULL },
E 27
I 27
	{ &umap_vfsops, "umap", 10, 0, 0, NULL, NULL },
E 27
E 26
E 22
#endif

I 23
D 26
#ifdef UNION
extern	struct vfsops union_vfsops;
#define	UNION_VFSOPS	&union_vfsops
#else
#define	UNION_VFSOPS	NULL
E 26
I 26
	/* Portal Filesystem */
#ifdef PORTAL
D 27
	{ &portal_vfsops, "portal", 8, 0, 0, NULL },
E 27
I 27
	{ &portal_vfsops, "portal", 8, 0, 0, NULL, NULL },
E 27
E 26
#endif

E 23
E 20
E 16
E 15
E 10
E 4
E 2
D 26
struct vfsops *vfssw[] = {
D 4
	(struct vfsops *)0,	/* 0 = MOUNT_NONE */
E 4
I 4
	NULL,			/* 0 = MOUNT_NONE */
I 5
D 6
#ifdef FFS
E 5
E 4
	&ufs_vfsops,		/* 1 = MOUNT_UFS */
I 5
#else
	NULL,
#endif
E 5
#ifdef NFS
	&nfs_vfsops,		/* 2 = MOUNT_NFS */
#else
D 4
	(struct vfsops *)0,
E 4
I 4
	NULL,
E 4
#endif
D 2
	(struct vfsops *)0,	/* 3 = MOUNT_PC */
E 2
I 2
#ifdef MFS
	&mfs_vfsops,		/* 3 = MOUNT_MFS */
#else
D 4
	(struct vfsops *)0,
E 4
I 4
	NULL,
E 4
#endif
E 6
I 6
	UFS_VFSOPS,		/* 1 = MOUNT_UFS */
	NFS_VFSOPS,		/* 2 = MOUNT_NFS */
	MFS_VFSOPS,		/* 3 = MOUNT_MFS */
E 6
D 4
	(struct vfsops *)0,	/* 4 = MOUNT_PC */
E 4
I 4
	NULL,			/* 4 = MOUNT_PC */
D 6
#ifdef LFS
	&lfs_vfsops,		/* 5 = MOUNT_LFS */
#else
	NULL,
#endif
E 6
I 6
	LFS_VFSOPS,		/* 5 = MOUNT_LFS */
I 10
D 24
	LOFS_VFSOPS,		/* 6 = MOUNT_LOFS */
E 24
I 24
	NULL,			/* 6 = MOUNT_LOFS */
E 24
	FDESC_VFSOPS,		/* 7 = MOUNT_FDESC */
	PORTAL_VFSOPS,		/* 8 = MOUNT_PORTAL */
I 15
	NULL_VFSOPS,		/* 9 = MOUNT_NULL */
	UMAP_VFSOPS,		/* 10 = MOUNT_UMAP */
I 16
	KERNFS_VFSOPS,		/* 11 = MOUNT_KERNFS */
I 19
	PROCFS_VFSOPS,		/* 12 = MOUNT_PROCFS */
I 20
	AFS_VFSOPS,		/* 13 = MOUNT_AFS */
D 21
	ISOFS_VFSOPS,		/* 14 = MOUNT_ISOFS */
E 21
I 21
D 22
	ISOFS_VFSOPS,		/* 14 = MOUNT_CD9660 */
E 22
I 22
	CD9660_VFSOPS,		/* 14 = MOUNT_CD9660 */
I 23
	UNION_VFSOPS,		/* 15 = MOUNT_UNION */
E 23
E 22
E 21
E 20
E 19
E 16
	0
E 26
I 26
	/* File Descriptor Filesystem */
#ifdef FDESC
D 27
	{ &fdesc_vfsops, "fdesc", 7, 0, 0, NULL },
E 27
I 27
	{ &fdesc_vfsops, "fdesc", 7, 0, 0, NULL, NULL },
E 27
#endif

	/* Kernel Information Filesystem */
#ifdef KERNFS
D 27
	{ &kernfs_vfsops, "kernfs", 11, 0, 0, NULL },
E 27
I 27
	{ &kernfs_vfsops, "kernfs", 11, 0, 0, NULL, NULL },
E 27
#endif

E 26
E 15
E 10
E 6
E 4
E 2
};
I 8

I 26
/*
 * Initially the size of the list, vfs_init will set maxvfsconf
 * to the highest defined type number.
 */
int maxvfsconf = sizeof(vfsconflist) / sizeof (struct vfsconf);
struct vfsconf *vfsconf = vfsconflist;
E 26

/*
D 14
 * Vnode_op_descs lists all vnode operations supported.
 * At boot time vfs_op_init examines this list
 * to configure vnode operations vectors.
 */

extern struct vnodeop_desc
	vop_lookup_desc,
	vop_create_desc,
	vop_mknod_desc,
	vop_open_desc,
	vop_close_desc,
	vop_access_desc,
	vop_getattr_desc,
	vop_setattr_desc,
	vop_read_desc,
	vop_write_desc,
	vop_ioctl_desc,
	vop_select_desc,
	vop_mmap_desc,
	vop_fsync_desc,
	vop_seek_desc,
	vop_remove_desc,
	vop_link_desc,
	vop_rename_desc,
	vop_mkdir_desc,
	vop_rmdir_desc,
	vop_symlink_desc,
	vop_readdir_desc,
	vop_readlink_desc,
	vop_abortop_desc,
	vop_inactive_desc,
	vop_reclaim_desc,
	vop_lock_desc,
	vop_unlock_desc,
	vop_bmap_desc,
	vop_strategy_desc,
	vop_print_desc,
	vop_islocked_desc,
	vop_advlock_desc,
	vop_blkatoff_desc,
D 13
	vop_vget_desc,
E 13
	vop_valloc_desc,
	vop_vfree_desc,
	vop_truncate_desc,
	vop_update_desc,
	vop_bwrite_desc,
/* and the default */
	vop_default_desc;

struct vnodeop_desc *vfs_op_descs[] = {
	&vop_default_desc,   /* must be first */
	&vop_lookup_desc,
	&vop_create_desc,
	&vop_mknod_desc,
	&vop_open_desc,
	&vop_close_desc,
	&vop_access_desc,
	&vop_getattr_desc,
	&vop_setattr_desc,
	&vop_read_desc,
	&vop_write_desc,
	&vop_ioctl_desc,
	&vop_select_desc,
	&vop_mmap_desc,
	&vop_fsync_desc,
	&vop_seek_desc,
	&vop_remove_desc,
	&vop_link_desc,
	&vop_rename_desc,
	&vop_mkdir_desc,
	&vop_rmdir_desc,
	&vop_symlink_desc,
	&vop_readdir_desc,
	&vop_readlink_desc,
	&vop_abortop_desc,
	&vop_inactive_desc,
	&vop_reclaim_desc,
	&vop_lock_desc,
	&vop_unlock_desc,
	&vop_bmap_desc,
	&vop_strategy_desc,
	&vop_print_desc,
	&vop_islocked_desc,
	&vop_advlock_desc,
	&vop_blkatoff_desc,
D 13
	&vop_vget_desc,
E 13
	&vop_valloc_desc,
	&vop_vfree_desc,
	&vop_truncate_desc,
	&vop_update_desc,
	&vop_bwrite_desc,
	NULL
};




/*
E 14
 *
D 14
 * vfs_opv_descs enumerates the list of vnode classes,
 * each with it's own vnode operation vector.
 * It is consulted at system
 * boot to build operation vectors.
 * It's also null terminated.
E 14
I 14
 * vfs_opv_descs enumerates the list of vnode classes, each with it's own
 * vnode operation vector.  It is consulted at system boot to build operation
 * vectors.  It is NULL terminated.
E 14
 *
D 14
 * Out-of-kernel, someone else (more knowlegable about what file
 * systems live in this address space) must specify this table.
E 14
I 14
D 15
 * Out-of-kernel, someone else (more knowlegable about what file systems live
 * in this address space) must specify this table.
E 15
E 14
 */
D 14

E 14
extern struct vnodeopv_desc ffs_vnodeop_opv_desc;
extern struct vnodeopv_desc ffs_specop_opv_desc;
extern struct vnodeopv_desc ffs_fifoop_opv_desc;
extern struct vnodeopv_desc lfs_vnodeop_opv_desc;
extern struct vnodeopv_desc lfs_specop_opv_desc;
extern struct vnodeopv_desc lfs_fifoop_opv_desc;
extern struct vnodeopv_desc mfs_vnodeop_opv_desc;
extern struct vnodeopv_desc dead_vnodeop_opv_desc;
extern struct vnodeopv_desc fifo_vnodeop_opv_desc;
extern struct vnodeopv_desc spec_vnodeop_opv_desc;
extern struct vnodeopv_desc nfsv2_vnodeop_opv_desc;
extern struct vnodeopv_desc spec_nfsv2nodeop_opv_desc;
extern struct vnodeopv_desc fifo_nfsv2nodeop_opv_desc;
I 11
D 24
extern struct vnodeopv_desc lofs_vnodeop_opv_desc;
E 24
extern struct vnodeopv_desc fdesc_vnodeop_opv_desc;
extern struct vnodeopv_desc portal_vnodeop_opv_desc;
I 15
extern struct vnodeopv_desc null_vnodeop_opv_desc;
extern struct vnodeopv_desc umap_vnodeop_opv_desc;
I 16
extern struct vnodeopv_desc kernfs_vnodeop_opv_desc;
I 19
extern struct vnodeopv_desc procfs_vnodeop_opv_desc;
I 20
D 22
extern struct vnodeopv_desc isofs_vnodeop_opv_desc;
extern struct vnodeopv_desc isofs_specop_opv_desc;
extern struct vnodeopv_desc isofs_fifoop_opv_desc;
E 22
I 22
extern struct vnodeopv_desc cd9660_vnodeop_opv_desc;
extern struct vnodeopv_desc cd9660_specop_opv_desc;
extern struct vnodeopv_desc cd9660_fifoop_opv_desc;
I 23
extern struct vnodeopv_desc union_vnodeop_opv_desc;
E 23
E 22
E 20
E 19
E 16
E 15
E 11

D 9

E 9
struct vnodeopv_desc *vfs_opv_descs[] = {
	&ffs_vnodeop_opv_desc,
	&ffs_specop_opv_desc,
I 12
#ifdef FIFO
E 12
	&ffs_fifoop_opv_desc,
I 12
#endif
E 12
I 9
	&dead_vnodeop_opv_desc,
I 12
#ifdef FIFO
E 12
	&fifo_vnodeop_opv_desc,
I 12
#endif
E 12
	&spec_vnodeop_opv_desc,
#ifdef LFS
E 9
	&lfs_vnodeop_opv_desc,
	&lfs_specop_opv_desc,
I 12
#ifdef FIFO
E 12
	&lfs_fifoop_opv_desc,
I 9
#endif
I 12
#endif
E 12
#ifdef MFS
E 9
	&mfs_vnodeop_opv_desc,
D 9
	&dead_vnodeop_opv_desc,
	&fifo_vnodeop_opv_desc,
	&spec_vnodeop_opv_desc,
E 9
I 9
#endif
#ifdef NFS
E 9
	&nfsv2_vnodeop_opv_desc,
	&spec_nfsv2nodeop_opv_desc,
I 12
#ifdef FIFO
E 12
	&fifo_nfsv2nodeop_opv_desc,
I 12
#endif
E 12
I 11
D 24
#endif
#ifdef LOFS
	&lofs_vnodeop_opv_desc,
E 24
#endif
#ifdef FDESC
	&fdesc_vnodeop_opv_desc,
#endif
#ifdef PORTAL
	&portal_vnodeop_opv_desc,
I 15
#endif
#ifdef NULLFS
	&null_vnodeop_opv_desc,
#endif
#ifdef UMAPFS
	&umap_vnodeop_opv_desc,
I 16
#endif
#ifdef KERNFS
	&kernfs_vnodeop_opv_desc,
I 19
#endif
#ifdef PROCFS
	&procfs_vnodeop_opv_desc,
I 20
#endif
D 21
#ifdef ISOFS
E 21
I 21
#ifdef CD9660
E 21
D 22
	&isofs_vnodeop_opv_desc,
	&isofs_specop_opv_desc,
E 22
I 22
	&cd9660_vnodeop_opv_desc,
	&cd9660_specop_opv_desc,
E 22
#ifdef FIFO
D 22
	&isofs_fifoop_opv_desc,
E 22
I 22
	&cd9660_fifoop_opv_desc,
E 22
#endif
I 23
#endif
#ifdef UNION
	&union_vnodeop_opv_desc,
E 23
E 20
E 19
E 16
E 15
E 11
I 9
#endif
E 9
	NULL
};
D 9

E 9
E 8
E 1
