h08410
s 00018/00001/00162
d D 8.4 94/04/16 06:31:57 bostic 89 88
c merge ffs_root and lfs_root into ufs_root
e
s 00005/00000/00158
d D 8.3 94/01/21 17:30:57 bostic 88 87
c add USL's copyright notice
e
s 00003/00156/00155
d D 8.2 94/01/12 15:37:04 hibler 87 86
c export routines and ufs_mountedon moved to vfs_subr.c.
e
s 00002/00002/00309
d D 8.1 93/06/11 16:29:15 bostic 86 85
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00306
d D 7.69 93/04/16 17:51:02 mckusick 85 84
c have to call the tree delete function before freeing leaf node
e
s 00001/00000/00306
d D 7.68 93/04/16 15:01:09 mckusick 84 83
c ufs_free_netcred needs a return value
e
s 00004/00005/00302
d D 7.67 93/04/08 16:38:55 sklower 83 82
c new conventions for calling routing layer
e
s 00005/00008/00302
d D 7.66 93/03/22 15:34:11 mckusick 82 81
c avoid null references (from Torek)
e
s 00001/00001/00309
d D 7.65 92/11/14 22:54:21 mckusick 81 80
c ufs_iput is obsoleted by vput
e
s 00000/00033/00310
d D 7.64 92/09/24 21:37:22 bostic 80 79
c printing buffer statistics is done in the vfs layer
e
s 00002/00003/00341
d D 7.63 92/09/14 17:18:55 mckusick 79 78
c ensure that correct value is passed
e
s 00136/00109/00208
d D 7.62 92/08/11 23:47:48 mckusick 78 77
c use radix tree code to match exported host addresses rather than adhoc hash code
e
s 00002/00001/00315
d D 7.61 92/07/13 00:06:43 pendry 77 76
c specdev.h moves to new location
e
s 00150/00000/00166
d D 7.60 92/07/02 20:06:04 mckusick 76 75
c hang_addrlist and free_addrlist move in from nfs/nfs_socket.c
e
s 00001/00001/00165
d D 7.59 92/06/25 13:19:43 mckusick 75 74
c quotactl now takes a real uid_t
e
s 00000/00092/00166
d D 7.58 91/11/05 14:37:56 mckusick 74 73
c reorganization to move ufsmount ops to be vnode ops; 
c ufs_root, ufs_fhtovp, and ufs_vptofh become filesystem specific
e
s 00036/00507/00222
d D 7.57 91/11/01 18:11:07 bostic 73 72
c UFS/FFS split for LFS version 1; delete file layout specific routines:
c ufs_mountroot, ufs_mount, mountfs, ufs_unmount, ufs_statfs, ufs_sync, sbupdate
e
s 00028/00043/00701
d D 7.56 91/06/28 16:36:59 karels 72 71
c rearrange to do getmdev in-line
e
s 00002/00002/00742
d D 7.55 91/06/21 10:54:58 mckusick 71 70
c quotaoff now needs a proc pointer
e
s 00008/00001/00736
d D 7.54 91/04/19 17:08:21 mckusick 70 69
c add global flag to allow forcible unmounts to be attempted;
c when syncing, skip vnodes that are locked
e
s 00004/00003/00733
d D 7.53 91/04/16 14:48:24 mckusick 69 68
c enable forcible unmount
e
s 00029/00035/00707
d D 7.52 91/04/16 00:11:24 mckusick 68 67
c add proc pointers to appropriate VOP, vnode, and VFS operations
e
s 00012/00012/00730
d D 7.51 91/03/19 10:30:41 karels 67 66
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00004/00002/00738
d D 7.50 90/11/28 21:29:22 mckusick 66 65
c allow multiple references when mounting miniroot
e
s 00001/00011/00739
d D 7.49 90/06/28 22:31:12 bostic 65 64
c new copyright notice
e
s 00001/00004/00749
d D 7.48 90/06/24 18:00:56 mckusick 64 63
c no longer map ENOENT to ENODEV in getmdev
e
s 00002/00000/00751
d D 7.47 90/06/03 12:37:24 mckusick 63 62
c have to vrele devvp when just doing an update
e
s 00003/00002/00748
d D 7.46 90/05/10 13:06:32 mckusick 62 61
c get rid of spurious #defines in user.h
e
s 00001/00001/00749
d D 7.45 90/05/10 11:20:03 mckusick 61 60
c use proper error variable
e
s 00003/00005/00747
d D 7.44 90/05/08 14:41:33 mckusick 60 59
c no locking needed in getmdev
e
s 00007/00003/00745
d D 7.43 90/05/08 14:39:47 mckusick 59 58
c when sync'ing, verify that vnode has not been recycled to a new filesystem
e
s 00000/00007/00748
d D 7.42 90/05/05 16:30:22 mckusick 58 57
c no longer need to check um_fs to detect busy;
c vfs_busy ensures single threading
e
s 00046/00043/00709
d D 7.41 90/05/04 20:51:16 mckusick 57 56
c mount struct prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00115/00048/00637
d D 7.40 90/05/02 19:42:51 mckusick 56 55
c add ufs_quotactl; eliminate static mount table; add quota support
e
s 00002/00002/00683
d D 7.39 90/04/10 15:28:47 mckusick 55 54
c have to brelse before close to avoid hanging
e
s 00006/00006/00679
d D 7.38 90/03/27 19:13:02 mckusick 54 53
c break specinfo structure out of vnode.h into specdev.h
e
s 00040/00011/00645
d D 7.37 90/03/09 11:38:09 mckusick 53 52
c mark mounted devices; do not mount devices in use;
c flush out buffers remaining from previous uses
e
s 00020/00002/00636
d D 7.36 90/03/08 15:57:52 mckusick 52 51
c add exportfs functionality
e
s 00019/00013/00619
d D 7.35 90/03/06 23:29:43 mckusick 51 50
c m_bsize, m_fsize, m_fsid are now found in m_stat;
c mounton and mountfrom are now kept in m_stat
e
s 00014/00009/00618
d D 7.34 90/01/13 22:58:11 mckusick 50 49
c take care not to derefernce through NULL (from gmf@osf.org)
e
s 00012/00006/00615
d D 7.33 90/01/04 22:15:44 mckusick 49 48
c rewrite ufs_sync to take advantage of clean/dirty buffer lists
e
s 00001/00003/00620
d D 7.32 89/12/30 22:41:02 mckusick 48 47
c v_mounton is gone; v_count => v_usecount
e
s 00009/00004/00614
d D 7.31 89/11/30 23:00:58 mckusick 47 46
c root is mounted read-only by default; replace bflush with vflushbuf
e
s 00003/00003/00615
d D 7.30 89/11/25 21:36:40 mckusick 46 45
c maintain mount information in v_mounton rather than overloading v_mount
e
s 00007/00006/00611
d D 7.29 89/11/22 21:53:44 mckusick 45 44
c use FSYNC instead of doing iupdat directly
e
s 00003/00001/00614
d D 7.28 89/11/14 13:57:49 mckusick 44 43
c have to vput vnode on error
e
s 00005/00008/00610
d D 7.27 89/11/10 12:28:58 mckusick 43 42
c iflush becomes vflush with hopes of doing forcible unmounting
e
s 00000/00002/00618
d D 7.26 89/10/31 17:19:57 mckusick 42 41
c vnode layer defines f_fsid and f_flags for statfs()
e
s 00003/00001/00617
d D 7.25 89/10/29 23:39:49 mckusick 41 40
c add file system specific initialization routine
e
s 00029/00019/00589
d D 7.24 89/10/24 19:43:29 mckusick 40 39
c iflush takes a mount ptr instead of a dev;
c scan only vnodes associated with the mount point of interest;
c handle restructuring of inodes and vnodes
e
s 00001/00003/00607
d D 7.23 89/10/19 22:50:09 mckusick 39 38
c allow free blocks to go negative; properly account for inodes
e
s 00021/00005/00589
d D 7.22 89/10/19 00:10:36 mckusick 38 37
c expand vfs_add inline; allow update of mounted file systems
e
s 00001/00001/00593
d D 7.21 89/10/13 18:56:59 mckusick 37 36
c `root device' => `root_device' to make it one column entry
e
s 00013/00000/00581
d D 7.20 89/09/05 23:09:28 mckusick 36 35
c add ufs_start routine
e
s 00011/00012/00570
d D 7.19 89/08/26 14:12:35 mckusick 35 34
c generalize the buffer pool so that NFS can become a client
e
s 00021/00003/00561
d D 7.18 89/07/16 15:11:07 mckusick 34 33
c check carefully for stale file handles and return errors
e
s 00001/00001/00563
d D 7.17 89/06/27 23:14:15 mckusick 33 32
c ufs_vptofh is now called by getfh
e
s 00001/00001/00563
d D 7.16 89/06/27 19:18:19 mckusick 32 31
c update reference counts on vnodes using VREF
e
s 00001/00001/00563
d D 7.15 89/06/06 16:52:11 mckusick 31 30
c put in explicit lock so that locking can be checked
e
s 00009/00004/00555
d D 7.14 89/05/27 16:45:47 mckusick 30 29
c fill out implementation of ufs_vptofh (from Rick Macklem)
e
s 00424/00174/00135
d D 7.13 89/05/09 17:22:32 mckusick 29 28
c merge in vnodes
e
s 00001/00001/00308
d D 7.12 89/04/26 19:21:28 mckusick 28 27
c use new form of suser()
e
s 00005/00003/00304
d D 7.11 88/05/24 19:26:08 mckusick 27 26
c lint
e
s 00013/00014/00294
d D 7.10 88/05/22 15:09:10 karels 26 25
c lint
e
s 00001/00000/00307
d D 7.9 88/05/19 22:09:44 karels 25 24
c avoid race between mountfs and update
e
s 00005/00002/00302
d D 7.8 88/05/02 00:03:35 mckusick 24 23
c add compatibility for dynamic cylinder groups;
c delete last reference to fs_dbsize
e
s 00046/00043/00258
d D 7.7 87/11/30 19:40:02 mckusick 23 22
c major cleanup of mountfs and fixed a bug too!
e
s 00019/00020/00282
d D 7.6 87/06/21 15:32:01 mckusick 22 21
c replace geteblk and wmemall with malloc to hold superblock related data
e
s 00001/00000/00301
d D 7.5 87/06/04 14:54:13 karels 21 20
c save cpg in pack label too
e
s 00001/00001/00300
d D 7.4 87/05/03 18:07:25 sam 20 19
c check ip before dereferencing (can only happen when called to mount root)
e
s 00034/00023/00267
d D 7.3 87/04/02 15:49:26 karels 19 17
c working with pack labels
e
s 00091/00023/00267
d D 7.2.1.1 87/04/02 15:41:18 karels 18 17
c add ifdefs for dev_bsize (almost working)
e
s 00003/00000/00287
d D 7.2 87/01/13 17:56:48 mckusick 17 16
c add sanity checks for old file systems
e
s 00001/00001/00286
d D 7.1 86/06/05 00:13:22 mckusick 16 15
c 4.3BSD release version
e
s 00002/00001/00285
d D 6.14 86/04/23 12:28:26 mckusick 15 14
c must invalidate any names for mounted on inode
e
s 00005/00003/00281
d D 6.13 86/02/18 12:34:07 karels 14 13
c don't close, binval on failed mount because already mounted.
e
s 00000/00001/00284
d D 6.12 85/09/04 13:32:39 bloom 13 12
c lint cleanup
e
s 00007/00001/00278
d D 6.11 85/06/08 14:52:23 mckusick 12 11
c Add copyright
e
s 00015/00002/00264
d D 6.10 85/05/22 19:55:32 mckusick 11 10
c differentiate several errors; close special device if mount fails
e
s 00001/00001/00265
d D 6.9 84/09/28 15:53:08 mckusick 10 9
c use macros
e
s 00011/00011/00255
d D 6.8 84/08/29 20:26:19 bloom 9 8
c Change to includes.  no more ../h
e
s 00001/00001/00265
d D 6.7 84/07/18 09:37:31 karels 8 7
c don't zero name, zero pad it.
e
s 00003/00002/00263
d D 6.6 84/07/08 22:35:12 mckusick 7 6
c use new interface to `copyinstr' and `copystr'
e
s 00021/00017/00244
d D 6.5 84/07/08 16:19:48 mckusick 6 5
c rework `namei' interface to eliminate global variables
e
s 00016/00009/00245
d D 6.4 84/06/26 13:51:02 karels 5 4
c check superblock magic, size before copying; better error codes
c from mount
e
s 00004/00002/00250
d D 6.3 84/02/07 14:53:05 karels 4 3
c missing iput's on errors
e
s 00002/00001/00250
d D 6.2 84/01/03 23:41:53 mckusick 3 2
c add system wide cacheing of path names in namei() (from kre)
e
s 00000/00000/00251
d D 6.1 83/07/29 06:43:19 sam 2 1
c 4.2 distribution
e
s 00251/00000/00000
d D 4.1 83/05/27 14:02:54 sam 1 0
c date and time created 83/05/27 14:02:54 by sam
e
u
U
f b 
t
T
I 1
D 12
/*	%M%	%I%	%E%	*/
E 12
I 12
/*
D 16
 * Copyright (c) 1982 Regents of the University of California.
E 16
I 16
D 29
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 16
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 29
I 29
D 72
 * Copyright (c) 1989 The Regents of the University of California.
E 72
I 72
D 73
 * Copyright (c) 1989, 1991 The Regents of the University of California.
E 73
I 73
D 86
 * Copyright (c) 1991 The Regents of the University of California.
E 73
E 72
 * All rights reserved.
E 86
I 86
D 89
 * Copyright (c) 1991, 1993
E 89
I 89
 * Copyright (c) 1991, 1993, 1994
E 89
 *	The Regents of the University of California.  All rights reserved.
I 88
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 88
E 86
E 29
 *
I 29
D 65
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
E 65
I 65
 * %sccs.include.redist.c%
E 65
 *
E 29
 *	%W% (Berkeley) %G%
 */
E 12

I 29
D 35

E 35
E 29
D 9
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/inode.h"
#include "../h/proc.h"
#include "../h/fs.h"
#include "../h/buf.h"
#include "../h/mount.h"
#include "../h/file.h"
D 6
#include "../h/nami.h"
E 6
#include "../h/conf.h"
E 9
I 9
D 73
#include "param.h"
#include "systm.h"
D 29
#include "dir.h"
#include "user.h"
#include "inode.h"
#include "proc.h"
#include "fs.h"
#include "buf.h"
E 29
I 29
D 56
#include "time.h"
E 56
I 56
D 67
#include "user.h"
E 67
I 67
#include "namei.h"
E 67
#include "proc.h"
E 56
#include "kernel.h"
D 56
#include "namei.h"
E 56
#include "vnode.h"
I 54
#include "specdev.h"
E 54
E 29
#include "mount.h"
I 29
#include "buf.h"
I 35
D 56
#include "ucred.h"
E 56
E 35
E 29
#include "file.h"
D 29
#include "conf.h"
I 19
#include "ioctl.h"
E 29
#include "disklabel.h"
D 29
#include "stat.h"
E 29
I 29
#include "ioctl.h"
#include "errno.h"
E 29
I 22
#include "malloc.h"
E 73
I 73
#include <sys/param.h>
I 78
D 87
#include <net/radix.h>
#include <sys/domain.h>
#include <sys/socket.h>
E 87
#include <sys/mbuf.h>
E 78
#include <sys/mount.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/vnode.h>
D 77
#include <sys/specdev.h>
E 77
I 76
D 78
#include <sys/socket.h>
E 78
#include <sys/malloc.h>
D 78
#include <sys/mbuf.h>
#include <netinet/in.h>
E 78
I 77

#include <miscfs/specfs/specdev.h>
E 77
E 76
E 73
I 56
D 67
#include "../ufs/quota.h"
E 56
I 29
#include "../ufs/fs.h"
#include "../ufs/ufsmount.h"
#include "../ufs/inode.h"
E 67
E 29
E 22
E 19
I 18
#include "ioctl.h"
#include "disklabel.h"
#include "stat.h"
E 18
E 9

I 67
D 73
#include "quota.h"
#include "fs.h"
#include "ufsmount.h"
#include "inode.h"
E 73
I 73
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/ufs_extern.h>
E 73

E 67
D 29
smount()
E 29
I 29
D 68
/*
 * ufs vfs operations.
 */
int ufs_mount();
I 36
int ufs_start();
E 36
int ufs_unmount();
int ufs_root();
I 56
int ufs_quotactl();
E 56
int ufs_statfs();
int ufs_sync();
int ufs_fhtovp();
int ufs_vptofh();
I 41
int ufs_init();
E 41

E 68
D 73
struct vfsops ufs_vfsops = {
	ufs_mount,
I 36
	ufs_start,
E 36
	ufs_unmount,
	ufs_root,
I 56
	ufs_quotactl,
E 56
	ufs_statfs,
	ufs_sync,
	ufs_fhtovp,
D 41
	ufs_vptofh
E 41
I 41
	ufs_vptofh,
	ufs_init
E 41
};

E 73
/*
I 70
D 73
 * Flag to allow forcible unmounting.
E 73
I 73
 * Flag to permit forcible unmounting.
E 73
 */
int doforce = 1;

/*
E 70
D 56
 * ufs mount table.
 */
struct ufsmount mounttab[NMOUNT];

/*
E 56
D 38
 * Called by vfs_mountroot when ufs is going to be mounted as root
E 38
I 38
D 73
 * Called by vfs_mountroot when ufs is going to be mounted as root.
E 38
 *
D 38
 * XXX - Need to have a way of figuring the name of the root device
E 38
I 38
 * Name is updated by mount(8) after booting.
E 38
 */
D 37
#define ROOTNAME	"root device"
E 37
I 37
#define ROOTNAME	"root_device"
E 37

ufs_mountroot()
E 29
{
D 29
	register struct a {
		char	*fspec;
		char	*freg;
		int	ronly;
D 6
	} *uap;
E 6
I 6
	} *uap = (struct a *)u.u_ap;
E 6
	dev_t dev;
	register struct inode *ip;
E 29
I 29
	register struct mount *mp;
	extern struct vnode *rootvp;
I 68
	struct proc *p = curproc;	/* XXX */
E 68
	struct ufsmount *ump;
E 29
	register struct fs *fs;
D 13
	register char *cp;
E 13
I 6
D 29
	register struct nameidata *ndp = &u.u_nd;
I 7
	u_int len;
E 29
I 29
	u_int size;
	int error;
E 29
E 7
E 6

D 6
	uap = (struct a *)u.u_ap;
	u.u_error = getmdev(&dev);
E 6
I 6
D 29
	u.u_error = getmdev(&dev, uap->fspec);
E 6
	if (u.u_error)
		return;
D 6
	u.u_dirp = (caddr_t)uap->freg;
D 3
	ip = namei(uchar, LOOKUP, 1);
E 3
I 3
	ip = namei(uchar, LOOKUP | NOCACHE, 1);
E 6
I 6
D 15
	ndp->ni_nameiop = LOOKUP | NOCACHE | FOLLOW;
E 15
I 15
	ndp->ni_nameiop = LOOKUP | FOLLOW;
E 15
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = (caddr_t)uap->freg;
	ip = namei(ndp);
E 6
E 3
	if (ip == NULL)
		return;
D 11
	if (ip->i_count!=1 || (ip->i_mode&IFMT) != IFDIR) {
E 11
I 11
	if (ip->i_count != 1) {
E 11
		iput(ip);
		u.u_error = EBUSY;
		return;
E 29
I 29
	mp = (struct mount *)malloc((u_long)sizeof(struct mount),
		M_MOUNT, M_WAITOK);
D 57
	mp->m_op = &ufs_vfsops;
D 47
	mp->m_flag = 0;
E 47
I 47
	mp->m_flag = M_RDONLY;
E 47
	mp->m_exroot = 0;
I 40
	mp->m_mounth = (struct vnode *)0;
E 57
I 57
	mp->mnt_op = &ufs_vfsops;
	mp->mnt_flag = MNT_RDONLY;
	mp->mnt_exroot = 0;
	mp->mnt_mounth = NULLVP;
E 57
E 40
D 68
	error = mountfs(rootvp, mp);
E 68
I 68
	error = mountfs(rootvp, mp, p);
E 68
	if (error) {
		free((caddr_t)mp, M_MOUNT);
		return (error);
E 29
	}
I 11
D 29
	if ((ip->i_mode&IFMT) != IFDIR) {
		iput(ip);
		u.u_error = ENOTDIR;
		return;
E 29
I 29
D 38
	error = vfs_add((struct vnode *)0, mp, 0);
	if (error) {
E 38
I 38
	if (error = vfs_lock(mp)) {
E 38
D 68
		(void)ufs_unmount(mp, 0);
E 68
I 68
		(void)ufs_unmount(mp, 0, p);
E 68
		free((caddr_t)mp, M_MOUNT);
		return (error);
E 29
	}
I 38
	rootfs = mp;
D 57
	mp->m_next = mp;
	mp->m_prev = mp;
	mp->m_vnodecovered = (struct vnode *)0;
E 57
I 57
	mp->mnt_next = mp;
	mp->mnt_prev = mp;
	mp->mnt_vnodecovered = NULLVP;
E 57
E 38
E 11
D 29
	fs = mountfs(dev, uap->ronly, ip);
D 23
	if (fs == 0)
E 23
I 23
	if (fs == 0) {
		iput(ip);
E 23
		return;
E 29
I 29
	ump = VFSTOUFS(mp);
	fs = ump->um_fs;
I 51
	bzero(fs->fs_fsmnt, sizeof(fs->fs_fsmnt));
E 51
	fs->fs_fsmnt[0] = '/';
D 51
	bzero(fs->fs_fsmnt + 1, sizeof(fs->fs_fsmnt) - 1);
	(void) copystr(ROOTNAME, ump->um_mntname, MNAMELEN - 1, &size);
	bzero(ump->um_mntname + size, MNAMELEN - size);
E 51
I 51
D 57
	bcopy((caddr_t)fs->fs_fsmnt, (caddr_t)mp->m_stat.f_mntonname, MNAMELEN);
	(void) copystr(ROOTNAME, mp->m_stat.f_mntfromname, MNAMELEN - 1, &size);
	bzero(mp->m_stat.f_mntfromname + size, MNAMELEN - size);
	(void) ufs_statfs(mp, &mp->m_stat);
E 57
I 57
	bcopy((caddr_t)fs->fs_fsmnt, (caddr_t)mp->mnt_stat.f_mntonname,
	    MNAMELEN);
	(void) copystr(ROOTNAME, mp->mnt_stat.f_mntfromname, MNAMELEN - 1,
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
D 68
	(void) ufs_statfs(mp, &mp->mnt_stat);
E 68
I 68
	(void) ufs_statfs(mp, &mp->mnt_stat, p);
E 68
E 57
E 51
	vfs_unlock(mp);
	inittodr(fs->fs_time);
	return (0);
}

/*
 * VFS Operations.
 *
 * mount system call
 */
D 68
ufs_mount(mp, path, data, ndp)
E 68
I 68
ufs_mount(mp, path, data, ndp, p)
E 68
D 51
	struct mount *mp;
E 51
I 51
	register struct mount *mp;
E 51
	char *path;
	caddr_t data;
	struct nameidata *ndp;
I 68
	struct proc *p;
E 68
{
	struct vnode *devvp;
	struct ufs_args args;
	struct ufsmount *ump;
	register struct fs *fs;
	u_int size;
	int error;

	if (error = copyin(data, (caddr_t)&args, sizeof (struct ufs_args)))
		return (error);
D 52
	if ((error = getmdev(&devvp, args.fspec, ndp)) != 0)
		return (error);
E 52
I 52
	/*
	 * Process export requests.
	 */
D 57
	if ((args.exflags & M_EXPORTED) || (mp->m_flag & M_EXPORTED)) {
		if (args.exflags & M_EXPORTED)
			mp->m_flag |= M_EXPORTED;
E 57
I 57
	if ((args.exflags & MNT_EXPORTED) || (mp->mnt_flag & MNT_EXPORTED)) {
		if (args.exflags & MNT_EXPORTED)
			mp->mnt_flag |= MNT_EXPORTED;
E 57
		else
D 57
			mp->m_flag &= ~M_EXPORTED;
		if (args.exflags & M_EXRDONLY)
			mp->m_flag |= M_EXRDONLY;
E 57
I 57
			mp->mnt_flag &= ~MNT_EXPORTED;
		if (args.exflags & MNT_EXRDONLY)
			mp->mnt_flag |= MNT_EXRDONLY;
E 57
		else
D 57
			mp->m_flag &= ~M_EXRDONLY;
		mp->m_exroot = args.exroot;
E 57
I 57
			mp->mnt_flag &= ~MNT_EXRDONLY;
		mp->mnt_exroot = args.exroot;
E 57
	}
E 52
D 38
	error = mountfs(devvp, mp);
E 38
I 38
D 57
	if ((mp->m_flag & M_UPDATE) == 0) {
E 57
I 57
D 72
	if ((mp->mnt_flag & MNT_UPDATE) == 0) {
E 57
I 52
D 68
		if ((error = getmdev(&devvp, args.fspec, ndp)) != 0)
E 68
I 68
		if ((error = getmdev(&devvp, args.fspec, ndp, p)) != 0)
E 68
			return (error);
E 52
D 68
		error = mountfs(devvp, mp);
E 68
I 68
		error = mountfs(devvp, mp, p);
E 68
	} else {
E 72
I 72
	/*
	 * If updating, check whether changing from read-only to
	 * read/write; if there is no device name, that's all we do.
	 */
	if (mp->mnt_flag & MNT_UPDATE) {
E 72
		ump = VFSTOUFS(mp);
		fs = ump->um_fs;
D 57
		if (fs->fs_ronly && (mp->m_flag & M_RDONLY) == 0)
E 57
I 57
		if (fs->fs_ronly && (mp->mnt_flag & MNT_RDONLY) == 0)
E 57
			fs->fs_ronly = 0;
D 72
		/*
		 * Verify that the specified device is the one that
		 * is really being used for the root file system.
		 */
E 72
I 52
		if (args.fspec == 0)
			return (0);
D 68
		if ((error = getmdev(&devvp, args.fspec, ndp)) != 0)
E 68
I 68
D 72
		if ((error = getmdev(&devvp, args.fspec, ndp, p)) != 0)
E 68
			return (error);
E 72
I 72
	}
	/*
	 * Not an update, or updating the name: look up the name
	 * and verify that it refers to a sensible block device.
	 */
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = args.fspec;
	if (error = namei(ndp, p))
		return (error);
	devvp = ndp->ni_vp;
	if (devvp->v_type != VBLK) {
		vrele(devvp);
		return (ENOTBLK);
	}
	if (major(devvp->v_rdev) >= nblkdev) {
		vrele(devvp);
		return (ENXIO);
	}
	if ((mp->mnt_flag & MNT_UPDATE) == 0)
		error = mountfs(devvp, mp, p);
	else {
E 72
E 52
		if (devvp != ump->um_devvp)
			error = EINVAL;	/* needs translation */
I 63
		else
			vrele(devvp);
E 63
	}
E 38
	if (error) {
		vrele(devvp);
		return (error);
E 29
I 23
	}
E 23
D 6
	u.u_dirp = uap->freg;
	for (cp = fs->fs_fsmnt; cp < &fs->fs_fsmnt[sizeof(fs->fs_fsmnt) - 2]; )
		if ((*cp++ = uchar()) == 0)
			u.u_dirp--;		/* get 0 again */
	*cp = 0;
E 6
I 6
D 7
	bzero(fs->fs_fsmnt, sizeof(fs->fs_fsmnt));
	copyinstr(uap->freg, fs->fs_fsmnt, sizeof(fs->fs_fsmnt));
E 7
I 7
D 29
	(void) copyinstr(uap->freg, fs->fs_fsmnt, sizeof(fs->fs_fsmnt)-1, &len);
D 8
	bzero(fs->fs_fsmnt, sizeof (fs->fs_fsmnt) - len);
E 8
I 8
	bzero(fs->fs_fsmnt + len, sizeof (fs->fs_fsmnt) - len);
E 29
I 29
	ump = VFSTOUFS(mp);
	fs = ump->um_fs;
	(void) copyinstr(path, fs->fs_fsmnt, sizeof(fs->fs_fsmnt) - 1, &size);
	bzero(fs->fs_fsmnt + size, sizeof(fs->fs_fsmnt) - size);
D 51
	(void) copyinstr(args.fspec, ump->um_mntname, MNAMELEN - 1, &size);
	bzero(ump->um_mntname + size, MNAMELEN - size);
E 51
I 51
D 57
	bcopy((caddr_t)fs->fs_fsmnt, (caddr_t)mp->m_stat.f_mntonname, MNAMELEN);
	(void) copyinstr(args.fspec, mp->m_stat.f_mntfromname, MNAMELEN - 1, 
		&size);
	bzero(mp->m_stat.f_mntfromname + size, MNAMELEN - size);
	(void) ufs_statfs(mp, &mp->m_stat);
E 57
I 57
	bcopy((caddr_t)fs->fs_fsmnt, (caddr_t)mp->mnt_stat.f_mntonname,
	    MNAMELEN);
	(void) copyinstr(args.fspec, mp->mnt_stat.f_mntfromname, MNAMELEN - 1, 
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
D 68
	(void) ufs_statfs(mp, &mp->mnt_stat);
E 68
I 68
	(void) ufs_statfs(mp, &mp->mnt_stat, p);
E 68
E 57
E 51
	return (0);
E 29
E 8
E 7
E 6
}

D 5
/* this routine has lousy error codes */
E 5
D 23
/* this routine has races if running twice */
E 23
D 29
struct fs *
mountfs(dev, ronly, ip)
	dev_t dev;
	int ronly;
	struct inode *ip;
E 29
I 29
/*
 * Common code for mount and mountroot
 */
D 68
mountfs(devvp, mp)
E 68
I 68
mountfs(devvp, mp, p)
E 68
D 53
	struct vnode *devvp;
E 53
I 53
	register struct vnode *devvp;
E 53
	struct mount *mp;
I 68
	struct proc *p;
E 68
E 29
{
D 23
	register struct mount *mp = 0;
	struct buf *tp = 0;
	register struct buf *bp = 0;
E 23
I 23
D 29
	register struct mount *mp;
	struct mount *fmp = NULL;
D 26
	struct buf *tp = NULL;
E 26
	register struct buf *bp = NULL;
E 29
I 29
D 56
	register struct ufsmount *ump;
E 56
I 56
	register struct ufsmount *ump = (struct ufsmount *)0;
E 56
D 53
	struct ufsmount *fmp = NULL;
E 53
	struct buf *bp = NULL;
E 29
E 23
	register struct fs *fs;
I 29
	dev_t dev = devvp->v_rdev;
E 29
D 18
D 19
	int blks;
E 19
I 19
	struct partinfo dpart;
D 29
	int havepart = 0, blks;
E 29
E 19
E 18
I 18
	struct partinfo dpart;
	int havepart = 0, blks;
E 18
D 23
	caddr_t space;
E 23
I 23
	caddr_t base, space;
E 23
D 29
	int i, size;
I 5
	register error;
E 29
I 29
	int havepart = 0, blks;
	int error, i, size;
E 29
I 11
	int needclose = 0;
I 29
D 57
	int ronly = (mp->m_flag & M_RDONLY) != 0;
E 57
I 57
	int ronly = (mp->mnt_flag & MNT_RDONLY) != 0;
I 66
	extern struct vnode *rootvp;
E 66
E 57
E 29
E 11
E 5

I 23
D 29
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) {
		if (mp->m_fs == NULL) {
E 29
I 29
D 53
	for (ump = &mounttab[0]; ump < &mounttab[NMOUNT]; ump++) {
		if (ump->um_fs == NULL) {
E 29
			if (fmp == NULL)
D 29
				fmp = mp;
		} else if (dev == mp->m_dev) {
			u.u_error = EBUSY;		/* XXX */
			return ((struct fs *) NULL);
E 29
I 29
				fmp = ump;
		} else if (dev == ump->um_dev) {
			return (EBUSY);		/* needs translation */
E 29
		}
	}
D 29
	if ((mp = fmp) == NULL) {
		u.u_error = EMFILE;		/* needs translation      XXX */
		return ((struct fs *) NULL);
	}
	mp->m_fs = (struct fs *)1;	/* just to reserve this slot */
	mp->m_dev = dev;
I 25
	mp->m_inodp = NULL;
E 25
E 23
D 5
	u.u_error =
E 5
I 5
	error =
E 5
D 18
D 19
	    (*bdevsw[major(dev)].d_open)(dev, ronly ? FREAD : FREAD|FWRITE);
E 19
I 19
	    (*bdevsw[major(dev)].d_open)(dev, ronly ? FREAD : FREAD|FWRITE,
	        S_IFBLK);
E 29
I 29
	if ((ump = fmp) == NULL)
E 53
I 53
	/*
	 * Disallow multiple mounts of the same device.
D 66
	 * Disallow mounting of a device that is currently in use.
E 66
I 66
	 * Disallow mounting of a device that is currently in use
	 * (except for root, which might share swap device for miniroot).
E 66
	 * Flush out any old buffers remaining from a previous use.
	 */
	if (error = mountedon(devvp))
		return (error);
D 66
	if (vcount(devvp) > 1)
E 66
I 66
	if (vcount(devvp) > 1 && devvp != rootvp)
E 66
		return (EBUSY);
	vinvalbuf(devvp, 1);
D 56
	for (ump = &mounttab[0]; ump < &mounttab[NMOUNT]; ump++)
		if (ump->um_fs == NULL)
			break;
	if (ump >= &mounttab[NMOUNT])
E 53
		return (EMFILE);		/* needs translation */
	ump->um_fs = (struct fs *)1;		/* just to reserve this slot */
D 35
	error = VOP_OPEN(devvp, ronly ? FREAD : FREAD|FWRITE,
		(struct ucred *)0);
E 35
I 35
	error = VOP_OPEN(devvp, ronly ? FREAD : FREAD|FWRITE, NOCRED);
E 35
E 29
E 19
E 18
I 18
	    (*bdevsw[major(dev)].d_open)(dev, ronly ? FREAD : FREAD|FWRITE,
	        S_IFBLK);
E 18
D 5
	if (u.u_error) {
		u.u_error = EIO;
E 5
I 5
D 23
	if (error)
E 5
		goto out;
E 23
I 23
	if (error) {
D 29
		u.u_error = error;
		mp->m_fs = NULL;
		return ((struct fs *) NULL);
E 29
I 29
		ump->um_fs = NULL;
E 56
I 56
D 68
	if (error = VOP_OPEN(devvp, ronly ? FREAD : FREAD|FWRITE, NOCRED))
E 68
I 68
	if (error = VOP_OPEN(devvp, ronly ? FREAD : FREAD|FWRITE, NOCRED, p))
E 68
E 56
		return (error);
E 29
D 56
	}
E 56
E 23
I 11
	needclose = 1;
I 19
D 29
	if ((*bdevsw[major(dev)].d_ioctl)(dev, DIOCGPART,
	    (caddr_t)&dpart, FREAD) == 0) {
E 29
I 29
D 35
	if (VOP_IOCTL(devvp, DIOCGPART, (caddr_t)&dpart, FREAD,
	    (struct ucred *)0) != 0)
E 35
I 35
D 56
	if (VOP_IOCTL(devvp, DIOCGPART, (caddr_t)&dpart, FREAD, NOCRED) != 0)
E 56
I 56
D 68
	if (VOP_IOCTL(devvp, DIOCGPART, (caddr_t)&dpart, FREAD, NOCRED) != 0) {
E 68
I 68
	if (VOP_IOCTL(devvp, DIOCGPART, (caddr_t)&dpart, FREAD, NOCRED, p) != 0)
E 68
E 56
E 35
		size = DEV_BSIZE;
D 56
	else {
E 56
I 56
D 68
	} else {
E 68
I 68
	else {
E 68
E 56
E 29
		havepart = 1;
		size = dpart.disklab->d_secsize;
D 29
	} else
		size = DEV_BSIZE;
E 19
I 18
#ifdef SECSIZE
	/*
	 * If possible, determine hardware sector size
	 * and adjust fsbtodb to correspond.
	 */
#endif SECSIZE
	if ((*bdevsw[major(dev)].d_ioctl)(dev, DIOCGPART,
	    (caddr_t)&dpart, FREAD) == 0) {
		havepart = 1;
		size = dpart.disklab->d_secsize;
#ifdef SECSIZE
		if (size < MINSECSIZE) {
			error = EINVAL;
			goto out;
		}
#endif SECSIZE
	} else
		size = DEV_BSIZE;
#ifdef SECSIZE
	tp = bread(dev, (daddr_t)(SBOFF / size), SBSIZE, size);
#else SECSIZE
E 18
E 11
D 5
	}
E 5
D 26
	tp = bread(dev, SBLOCK, SBSIZE);
I 18
#endif SECSIZE
E 18
D 23
	if (tp->b_flags & B_ERROR)
E 23
I 23
	if (tp->b_flags & B_ERROR) {
E 26
I 26
	bp = bread(dev, SBLOCK, SBSIZE);
	if (bp->b_flags & B_ERROR) {
E 26
		mp->m_fs = NULL;
E 29
I 29
	}
D 35
	if (error = bread(devvp, SBLOCK, SBSIZE, &bp)) {
E 35
I 35
D 56
	if (error = bread(devvp, SBLOCK, SBSIZE, NOCRED, &bp)) {
E 35
		ump->um_fs = NULL;
E 56
I 56
	if (error = bread(devvp, SBLOCK, SBSIZE, NOCRED, &bp))
E 56
E 29
E 23
		goto out;
D 23
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
D 22
		if (mp->m_bufp != 0 && dev == mp->m_dev) {
E 22
I 22
		if (mp->m_fs != NULL && dev == mp->m_dev) {
E 22
			mp = 0;
I 5
			error = EBUSY;
I 14
D 18
D 19
			needclose = 0;
E 19
E 18
E 14
E 5
			goto out;
		}
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
D 22
		if (mp->m_bufp == 0)
E 22
I 22
		if (mp->m_fs == NULL)
E 22
			goto found;
	mp = 0;
I 5
	error = EMFILE;		/* needs translation */
E 5
	goto out;
found:
D 22
	mp->m_bufp = tp;	/* just to reserve this slot */
E 22
I 22
	mp->m_fs = tp->b_un.b_fs;	/* just to reserve this slot */
E 22
	mp->m_dev = NODEV;
D 22
	fs = tp->b_un.b_fs;
E 22
I 22
	fs = mp->m_fs;
E 23
I 23
D 56
	}
E 56
D 26
	fs = tp->b_un.b_fs;
E 26
I 26
	fs = bp->b_un.b_fs;
E 26
E 23
E 22
I 5
D 18
D 19
	if (fs->fs_magic != FS_MAGIC || fs->fs_bsize > MAXBSIZE
	    || fs->fs_bsize < sizeof(struct fs)) {
E 19
I 19
	if (fs->fs_magic != FS_MAGIC || fs->fs_bsize > MAXBSIZE ||
	    fs->fs_bsize < sizeof(struct fs)) {
I 22
D 29
		mp->m_fs = NULL;
E 22
E 19
E 18
I 18
	if (fs->fs_magic != FS_MAGIC || fs->fs_bsize > MAXBSIZE ||
	    fs->fs_bsize < sizeof(struct fs)) {
E 18
		error = EINVAL;		/* also needs translation */
E 29
I 29
D 56
		ump->um_fs = NULL;
		error = EINVAL;		/* XXX also needs translation */
E 56
I 56
		error = EINVAL;		/* XXX needs translation */
E 56
E 29
		goto out;
	}
I 56
	ump = (struct ufsmount *)malloc(sizeof *ump, M_UFSMNT, M_WAITOK);
E 56
E 5
D 22
	bp = geteblk((int)fs->fs_sbsize);
	mp->m_bufp = bp;
	bcopy((caddr_t)tp->b_un.b_addr, (caddr_t)bp->b_un.b_addr,
E 22
I 22
D 27
	mp->m_fs = (struct fs *)malloc(fs->fs_sbsize, M_SUPERBLK, M_WAITOK);
E 27
I 27
D 29
	mp->m_fs = (struct fs *)malloc((u_long)fs->fs_sbsize, M_SUPERBLK,
E 29
I 29
	ump->um_fs = (struct fs *)malloc((u_long)fs->fs_sbsize, M_SUPERBLK,
E 29
	    M_WAITOK);
E 27
D 26
	bcopy((caddr_t)tp->b_un.b_addr, (caddr_t)mp->m_fs,
E 26
I 26
D 29
	bcopy((caddr_t)bp->b_un.b_addr, (caddr_t)mp->m_fs,
E 29
I 29
	bcopy((caddr_t)bp->b_un.b_addr, (caddr_t)ump->um_fs,
E 29
E 26
E 22
	   (u_int)fs->fs_sbsize);
I 47
	if (fs->fs_sbsize < SBSIZE)
		bp->b_flags |= B_INVAL;
E 47
D 26
	brelse(tp);
D 23
	tp = 0;
E 23
I 23
	tp = NULL;
E 26
I 26
	brelse(bp);
	bp = NULL;
E 26
E 23
D 22
	fs = bp->b_un.b_fs;
E 22
I 22
D 29
	fs = mp->m_fs;
E 22
D 5
	if (fs->fs_magic != FS_MAGIC || fs->fs_bsize > MAXBSIZE)
		goto out;
E 5
	fs->fs_ronly = (ronly != 0);
E 29
I 29
	fs = ump->um_fs;
	fs->fs_ronly = ronly;
E 29
	if (ronly == 0)
		fs->fs_fmod = 1;
I 19
	if (havepart) {
		dpart.part->p_fstype = FS_BSDFFS;
		dpart.part->p_fsize = fs->fs_fsize;
		dpart.part->p_frag = fs->fs_frag;
I 21
		dpart.part->p_cpg = fs->fs_cpg;
E 21
D 24
		fs->fs_dbsize = size;
E 24
	}
E 19
I 18
#ifdef SECSIZE
	/*
	 * If we have a disk label, force per-partition
	 * filesystem information to be correct
	 * and set correct current fsbtodb shift.
	 */
#endif SECSIZE
	if (havepart) {
		dpart.part->p_fstype = FS_BSDFFS;
		dpart.part->p_fsize = fs->fs_fsize;
		dpart.part->p_frag = fs->fs_frag;
#ifdef SECSIZE
#ifdef tahoe
		/*
		 * Save the original fsbtodb shift to restore on updates.
		 * (Console doesn't understand fsbtodb changes.)
		 */
		fs->fs_sparecon[0] = fs->fs_fsbtodb;
#endif
		i = fs->fs_fsize / size;
		for (fs->fs_fsbtodb = 0; i > 1; i >>= 1)
			fs->fs_fsbtodb++;
#endif SECSIZE
		fs->fs_dbsize = size;
	}
E 18
	blks = howmany(fs->fs_cssize, fs->fs_fsize);
D 22
	space = wmemall(vmemall, (int)fs->fs_cssize);
E 22
I 22
D 23
	space = (caddr_t)malloc(fs->fs_cssize, M_SUPERBLK, M_WAITOK);
E 22
D 5
	if (space == 0)
E 5
I 5
	if (space == 0) {
E 23
I 23
D 27
	base = space = (caddr_t)malloc(fs->fs_cssize, M_SUPERBLK, M_WAITOK);
E 27
I 27
	base = space = (caddr_t)malloc((u_long)fs->fs_cssize, M_SUPERBLK,
	    M_WAITOK);
E 27
D 29
	if (space == NULL) {
E 23
		error = ENOMEM;
E 5
		goto out;
I 5
	}
E 29
E 5
	for (i = 0; i < blks; i += fs->fs_frag) {
		size = fs->fs_bsize;
		if (i + fs->fs_frag > blks)
			size = (blks - i) * fs->fs_fsize;
I 18
#ifdef SECSIZE
		tp = bread(dev, fsbtodb(fs, fs->fs_csaddr + i), size,
		    fs->fs_dbsize);
#else SECSIZE
E 18
D 26
		tp = bread(dev, fsbtodb(fs, fs->fs_csaddr + i), size);
I 18
#endif SECSIZE
E 18
		if (tp->b_flags&B_ERROR) {
E 26
I 26
D 29
		bp = bread(dev, fsbtodb(fs, fs->fs_csaddr + i), size);
		if (bp->b_flags&B_ERROR) {
E 29
I 29
D 35
		error = bread(devvp, fsbtodb(fs, fs->fs_csaddr + i), size, &bp);
E 35
I 35
		error = bread(devvp, fsbtodb(fs, fs->fs_csaddr + i), size,
			NOCRED, &bp);
E 35
		if (error) {
E 29
E 26
D 22
			wmemfree(space, (int)fs->fs_cssize);
E 22
I 22
D 23
			free(space, M_SUPERBLK);
E 23
I 23
D 27
			free(base, M_SUPERBLK);
E 27
I 27
			free((caddr_t)base, M_SUPERBLK);
E 27
E 23
E 22
			goto out;
		}
D 26
		bcopy((caddr_t)tp->b_un.b_addr, space, (u_int)size);
E 26
I 26
		bcopy((caddr_t)bp->b_un.b_addr, space, (u_int)size);
E 26
D 10
		fs->fs_csp[i / fs->fs_frag] = (struct csum *)space;
E 10
I 10
		fs->fs_csp[fragstoblks(fs, i)] = (struct csum *)space;
E 10
		space += size;
D 26
		brelse(tp);
D 23
		tp = 0;
E 23
I 23
		tp = NULL;
E 26
I 26
		brelse(bp);
		bp = NULL;
E 26
E 23
	}
D 29
	mp->m_inodp = ip;
D 23
	mp->m_dev = dev;
E 23
	if (ip) {
		ip->i_flag |= IMOUNT;
I 15
		cacheinval(ip);
E 15
		iunlock(ip);
	}
E 29
I 29
D 57
	mp->m_data = (qaddr_t)ump;
D 51
	mp->m_bsize = fs->fs_bsize;
	mp->m_fsize = fs->fs_fsize;
	mp->m_fsid.val[0] = (long)dev;
	mp->m_fsid.val[1] = MOUNT_UFS;
E 51
I 51
	mp->m_stat.f_fsid.val[0] = (long)dev;
	mp->m_stat.f_fsid.val[1] = MOUNT_UFS;
I 56
	mp->m_flag |= M_LOCAL;
E 57
I 57
	mp->mnt_data = (qaddr_t)ump;
	mp->mnt_stat.f_fsid.val[0] = (long)dev;
	mp->mnt_stat.f_fsid.val[1] = MOUNT_UFS;
	mp->mnt_flag |= MNT_LOCAL;
E 57
E 56
E 51
	ump->um_mountp = mp;
	ump->um_dev = dev;
	ump->um_devvp = devvp;
D 56
	ump->um_qinod = NULL;
E 56
I 56
	for (i = 0; i < MAXQUOTAS; i++)
		ump->um_quotas[i] = NULLVP;
E 56
I 53
D 54
	devvp->v_specinfo->si_flags |= SI_MOUNTEDON;
E 54
I 54
	devvp->v_specflags |= SI_MOUNTEDON;
E 54
E 53
I 35
D 46
	devvp->v_mount = mp;
E 46
I 46
D 48
	devvp->v_mounton = mp;
E 48
E 46
E 35

E 29
I 17
	/* Sanity checks for old file systems.			   XXX */
	fs->fs_npsect = MAX(fs->fs_npsect, fs->fs_nsect);	/* XXX */
	fs->fs_interleave = MAX(fs->fs_interleave, 1);		/* XXX */
I 19
D 24

E 24
I 24
	if (fs->fs_postblformat == FS_42POSTBLFMT)		/* XXX */
		fs->fs_nrpos = 8;				/* XXX */
E 24
E 19
I 18

E 18
E 17
D 29
	return (fs);
E 29
I 29
	return (0);
E 29
out:
I 55
	if (bp)
		brelse(bp);
E 55
D 5
	u.u_error = EBUSY;
E 5
I 5
D 23
	if (error == 0)
		error = EIO;
I 19
D 20
	if (needclose)
E 20
I 20
	if (needclose && ip)
E 20
		(void) closei((dev_t)ip->i_rdev, IFBLK,
		    ronly? FREAD : FREAD|FWRITE);
E 19
I 18
	if (needclose)
		(void) closei((dev_t)ip->i_rdev, IFBLK,
		    ronly? FREAD : FREAD|FWRITE);
E 18
E 5
	if (ip)
		iput(ip);
D 22
	if (mp)
		mp->m_bufp = 0;
	if (bp)
		brelse(bp);
E 22
I 22
	if (mp && mp->m_fs)
E 23
I 23
	if (needclose)
D 29
		(void) closei(dev, IFBLK, ronly? FREAD : FREAD|FWRITE);
	if (mp->m_fs) {
E 23
		free((caddr_t)mp->m_fs, M_SUPERBLK);
I 23
		mp->m_fs = NULL;
E 29
I 29
D 35
		(void) VOP_CLOSE(devvp, ronly ? FREAD : FREAD|FWRITE,
			(struct ucred *)0);
E 35
I 35
D 68
		(void) VOP_CLOSE(devvp, ronly ? FREAD : FREAD|FWRITE, NOCRED);
E 68
I 68
		(void)VOP_CLOSE(devvp, ronly ? FREAD : FREAD|FWRITE, NOCRED, p);
E 68
E 35
D 56
	if (ump->um_fs) {
E 56
I 56
	if (ump) {
E 56
		free((caddr_t)ump->um_fs, M_SUPERBLK);
D 56
		ump->um_fs = NULL;
E 56
I 56
		free((caddr_t)ump, M_UFSMNT);
D 57
		mp->m_data = (qaddr_t)0;
E 57
I 57
		mp->mnt_data = (qaddr_t)0;
E 57
E 56
E 29
	}
E 23
E 22
D 26
	if (tp)
		brelse(tp);
E 26
I 26
D 55
	if (bp)
		brelse(bp);
E 55
E 26
I 11
D 14
	if (needclose)
		(*bdevsw[major(dev)].d_close)(dev, ronly ? FREAD : FREAD|FWRITE);
	binval(dev);
E 14
I 14
D 18
D 19
	if (needclose) {
		(*bdevsw[major(dev)].d_close)(dev, ronly? FREAD : FREAD|FWRITE);
		binval(dev);
	}
E 19
E 18
E 14
E 11
I 5
D 23
	u.u_error = error;
E 5
	return (0);
E 23
I 23
D 29
	u.u_error = error ? error : EIO;			/* XXX */
	return ((struct fs *) NULL);
E 29
I 29
	return (error);
E 29
E 23
}

I 36
/*
E 73
 * Make a filesystem operational.
 * Nothing to do at the moment.
 */
I 40
/* ARGSUSED */
I 73
int
E 73
E 40
D 68
ufs_start(mp, flags)
E 68
I 68
ufs_start(mp, flags, p)
E 68
	struct mount *mp;
	int flags;
I 68
	struct proc *p;
E 68
{

I 89
	return (0);
}

/*
 * Return the root of a filesystem.
 */
int
ufs_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
	struct vnode *nvp;
	int error;

	if (error = VFS_VGET(mp, (ino_t)ROOTINO, &nvp))
		return (error);
	*vpp = nvp;
E 89
	return (0);
}
E 36
D 29
umount()
{
	struct a {
		char	*fspec;
D 6
	};
E 6
I 6
	} *uap = (struct a *)u.u_ap;
E 29
E 6

D 6
	u.u_error = unmount1(0);
E 6
I 6
D 29
	u.u_error = unmount1(uap->fspec, 0);
E 6
}

D 6
unmount1(forcibly)
E 6
I 6
unmount1(fname, forcibly)
	caddr_t fname;
E 6
	int forcibly;
E 29
I 29
/*
D 73
 * unmount system call
 */
D 56
ufs_unmount(mp, flags)
E 56
I 56
D 68
ufs_unmount(mp, mntflags)
E 68
I 68
ufs_unmount(mp, mntflags, p)
E 68
E 56
	struct mount *mp;
D 56
	int flags;
E 56
I 56
	int mntflags;
I 68
	struct proc *p;
E 68
E 56
E 29
{
D 29
	dev_t dev;
	register struct mount *mp;
D 18
D 19
	int stillopen, flag, error;
E 19
I 19
	int error;
E 19
E 18
I 18
	int error;
E 18
	register struct inode *ip;
E 29
I 29
	register struct ufsmount *ump;
E 29
	register struct fs *fs;
I 29
D 40
	dev_t dev;
E 40
D 56
	int error, ronly;
E 56
I 56
	int i, error, ronly, flags = 0;
E 56
E 29

I 19
D 29
	forcibly = 0;					/* XXX */
E 19
I 18
	forcibly = 0;					/* XXX */
E 18
D 6
	error = getmdev(&dev);
E 6
I 6
	error = getmdev(&dev, fname);
E 6
	if (error)
		return (error);
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
D 22
		if (mp->m_bufp != NULL && dev == mp->m_dev)
E 22
I 22
		if (mp->m_fs != NULL && dev == mp->m_dev)
E 22
			goto found;
	return (EINVAL);
found:
	xumount(dev);	/* remove unused sticky files from text table */
I 3
	nchinval(dev);	/* flush the name cache */
E 3
	update();
E 29
I 29
D 56
	if (flags & MNT_FORCE)
E 56
I 56
D 69
	if (mntflags & MNT_FORCE)
E 56
		return (EINVAL);
I 56
	if (mntflags & MNT_FORCE)
E 69
I 69
	if (mntflags & MNT_FORCE) {
D 70
		if (mp == rootfs)
E 70
I 70
		if (!doforce || mp == rootfs)
E 70
			return (EINVAL);
E 69
		flags |= FORCECLOSE;
I 69
	}
E 69
E 56
I 47
	mntflushbuf(mp, 0);
	if (mntinvalbuf(mp))
		return (EBUSY);
E 47
	ump = VFSTOUFS(mp);
D 40
	dev = ump->um_dev;
E 40
E 29
D 43
#ifdef QUOTA
D 18
D 19
	if ((stillopen = iflush(dev, mp->m_qinod)) < 0 && !forcibly)
E 19
I 19
D 29
	if ((error = iflush(dev, mp->m_qinod)) && !forcibly)
E 29
I 29
D 40
	if (error = iflush(dev, ump->um_qinod))
E 40
I 40
	if (error = iflush(mp, ump->um_qinod))
E 40
E 29
E 19
E 18
I 18
	if ((error = iflush(dev, mp->m_qinod)) && !forcibly)
E 18
#else
D 18
D 19
	if ((stillopen = iflush(dev)) < 0 && !forcibly)
E 19
I 19
D 29
	if ((error = iflush(dev)) && !forcibly)
E 29
I 29
D 40
	if (error = iflush(dev))
E 40
I 40
	if (error = iflush(mp))
E 40
E 29
E 19
E 18
I 18
	if ((error = iflush(dev)) && !forcibly)
E 18
#endif
E 43
I 43
D 50
	if (error = vflush(mp, ITOV(ump->um_qinod), flags))
E 43
D 18
D 19
		return (EBUSY);
	if (stillopen < 0)
		return (EBUSY);			/* XXX */
E 19
I 19
		return (error);
E 50
E 19
E 18
I 18
		return (error);
E 18
#ifdef QUOTA
D 29
	closedq(mp);
E 29
I 29
D 40
	(void)closedq(ump);
E 40
I 40
D 50
	(void) closedq(ump);
E 40
E 29
	/*
D 43
	 * Here we have to iflush again to get rid of the quota inode.
D 18
D 19
	 * A drag, but it would be ugly to cheat, & this doesn't happen often
E 19
I 19
D 29
	 * A drag, but it would be ugly to cheat, & this doesn't happen often.
E 29
I 29
	 * A drag, but it would be ugly to cheat, & this doesn't happen often
E 43
I 43
	 * Here we have to vflush again to get rid of the quota inode.
	 * A drag, but it would be ugly to cheat, & this does not happen often.
E 43
E 29
E 19
E 18
I 18
	 * A drag, but it would be ugly to cheat, & this doesn't happen often.
E 18
	 */
D 40
	(void)iflush(dev, (struct inode *)NULL);
E 40
I 40
D 43
	(void) iflush(mp, (struct inode *)NULL);
E 43
I 43
	if (vflush(mp, (struct vnode *)NULL, MNT_NOFORCE))
		panic("ufs_unmount: quota");
E 50
I 50
D 56
	if (ump->um_qinod) {
		if (error = vflush(mp, ITOV(ump->um_qinod), flags))
E 56
I 56
D 57
	if (mp->m_flag & M_QUOTA) {
E 57
I 57
	if (mp->mnt_flag & MNT_QUOTA) {
E 57
		if (error = vflush(mp, NULLVP, SKIPSYSTEM|flags))
E 56
			return (error);
D 56
		(void) closedq(ump);
E 56
I 56
		for (i = 0; i < MAXQUOTAS; i++) {
			if (ump->um_quotas[i] == NULLVP)
				continue;
D 71
			quotaoff(mp, i);
E 71
I 71
			quotaoff(p, mp, i);
E 71
		}
E 56
		/*
D 56
		 * Here we have to vflush again to get rid of the quota inode.
		 * A drag, but it would be ugly to cheat, and this system
		 * call does not happen often.
E 56
I 56
		 * Here we fall through to vflush again to ensure
		 * that we have gotten rid of all the system vnodes.
E 56
		 */
D 56
		if (vflush(mp, (struct vnode *)NULL, MNT_NOFORCE))
			panic("ufs_unmount: quota");
	} else
E 56
I 56
	}
E 56
E 50
E 43
E 40
#endif
I 50
D 56
	if (error = vflush(mp, (struct vnode *)NULL, flags))
E 56
I 56
	if (error = vflush(mp, NULLVP, flags))
E 56
		return (error);
E 50
D 29
	ip = mp->m_inodp;
	ip->i_flag &= ~IMOUNT;
D 18
D 19
	irele(ip);
E 19
E 18
D 22
	fs = mp->m_bufp->b_un.b_fs;
	wmemfree((caddr_t)fs->fs_csp[0], (int)fs->fs_cssize);
D 18
D 19
	flag = !fs->fs_ronly;
E 19
E 18
	brelse(mp->m_bufp);
	mp->m_bufp = 0;
E 22
I 22
	fs = mp->m_fs;
E 29
I 29
	fs = ump->um_fs;
	ronly = !fs->fs_ronly;
E 29
D 56
	free((caddr_t)fs->fs_csp[0], M_SUPERBLK);
D 29
	free((caddr_t)mp->m_fs, M_SUPERBLK);
D 23
	mp->m_fs = 0;
E 22
	mp->m_dev = 0;
E 23
I 23
	mp->m_fs = NULL;
	mp->m_dev = NODEV;
E 23
	mpurge(mp - &mount[0]);
D 18
D 19
	if (!stillopen) {
		(*bdevsw[major(dev)].d_close)(dev, flag);
		binval(dev);
	}
	return (0);
E 19
I 19
	error = closei(dev, IFBLK, fs->fs_ronly? FREAD : FREAD|FWRITE);
	irele(ip);
E 29
I 29
	free((caddr_t)fs, M_SUPERBLK);
	ump->um_fs = NULL;
	ump->um_dev = NODEV;
E 56
I 53
D 54
	ump->um_devvp->v_specinfo->si_flags &= ~SI_MOUNTEDON;
E 54
I 54
	ump->um_devvp->v_specflags &= ~SI_MOUNTEDON;
E 54
E 53
D 35
	error = VOP_CLOSE(ump->um_devvp, ronly ? FREAD : FREAD|FWRITE,
		(struct ucred *)0);
E 35
I 35
D 68
	error = VOP_CLOSE(ump->um_devvp, ronly ? FREAD : FREAD|FWRITE, NOCRED);
E 68
I 68
	error = VOP_CLOSE(ump->um_devvp, ronly ? FREAD : FREAD|FWRITE,
		NOCRED, p);
E 68
D 46
	ump->um_devvp->v_mount = (struct mount *)0;
E 46
I 46
D 48
	ump->um_devvp->v_mounton = (struct mount *)0;
E 48
E 46
E 35
	vrele(ump->um_devvp);
D 56
	ump->um_devvp = (struct vnode *)0;
E 56
I 56
	free((caddr_t)fs->fs_csp[0], M_SUPERBLK);
	free((caddr_t)fs, M_SUPERBLK);
	free((caddr_t)ump, M_UFSMNT);
D 57
	mp->m_data = (qaddr_t)0;
	mp->m_flag &= ~M_LOCAL;
E 57
I 57
	mp->mnt_data = (qaddr_t)0;
	mp->mnt_flag &= ~MNT_LOCAL;
E 57
E 56
E 29
	return (error);
I 53
}

/*
E 73
D 87
 * Check to see if a filesystem is mounted on a block device.
 */
D 73
mountedon(vp)
E 73
I 73
int
ufs_mountedon(vp)
E 73
	register struct vnode *vp;
{
	register struct vnode *vq;

D 54
	if (vp->v_specinfo->si_flags & SI_MOUNTEDON)
E 54
I 54
	if (vp->v_specflags & SI_MOUNTEDON)
E 54
		return (EBUSY);
	if (vp->v_flag & VALIASED) {
D 54
		for (vq = *vp->v_specinfo->si_hashchain; vq;
		     vq = vq->v_specinfo->si_specnext) {
E 54
I 54
		for (vq = *vp->v_hashchain; vq; vq = vq->v_specnext) {
E 54
			if (vq->v_rdev != vp->v_rdev ||
			    vq->v_type != vp->v_type)
				continue;
D 54
			if (vq->v_specinfo->si_flags & SI_MOUNTEDON)
E 54
I 54
			if (vq->v_specflags & SI_MOUNTEDON)
E 54
				return (EBUSY);
		}
	}
	return (0);
E 53
E 19
E 18
I 18
	error = closei(dev, IFBLK, fs->fs_ronly? FREAD : FREAD|FWRITE);
	irele(ip);
	return (error);
E 18
}

D 29
sbupdate(mp)
E 29
I 29
/*
E 87
D 74
 * Return root of a filesystem
 */
I 73
int
E 73
ufs_root(mp, vpp)
E 29
	struct mount *mp;
I 29
	struct vnode **vpp;
E 29
{
D 22
	register struct fs *fs = mp->m_bufp->b_un.b_fs;
E 22
I 22
D 29
	register struct fs *fs = mp->m_fs;
E 29
I 29
D 40
	struct inode tip, *ip;
E 40
I 40
	register struct inode *ip;
I 73
	struct ufsmount *ump;
E 73
	struct inode *nip;
	struct vnode tvp;
E 40
	int error;

I 73
	ump = VFSTOUFS(mp);
E 73
D 40
	tip.i_dev = VFSTOUFS(mp)->um_dev;
	tip.i_vnode.v_mount = mp;
	error = iget(&tip, (ino_t)ROOTINO, &ip);
E 40
I 40
	tvp.v_mount = mp;
	ip = VTOI(&tvp);
	ip->i_vnode = &tvp;
D 73
	ip->i_dev = VFSTOUFS(mp)->um_dev;
	error = iget(ip, (ino_t)ROOTINO, &nip);
E 40
	if (error)
E 73
I 73
	ip->i_dev = ump->um_dev;
	if (error = (ump->um_iget)(ip, (ino_t)ROOTINO, &nip))
E 73
		return (error);
D 40
	*vpp = ITOV(ip);
E 40
I 40
	*vpp = ITOV(nip);
E 40
	return (0);
}

/*
E 74
I 56
 * Do operations associated with quotas
 */
I 73
int
E 73
D 68
ufs_quotactl(mp, cmds, uid, arg)
E 68
I 68
ufs_quotactl(mp, cmds, uid, arg, p)
E 68
	struct mount *mp;
	int cmds;
D 73
	uid_t uid;
E 73
I 73
D 75
	u_int uid;
E 75
I 75
	uid_t uid;
E 75
E 73
	caddr_t arg;
I 68
	struct proc *p;
E 68
{
D 67
	register struct nameidata *ndp = &u.u_nd;
E 67
D 74
	struct ufsmount *ump = VFSTOUFS(mp);
E 74
I 62
D 67
	struct proc *p = u.u_procp;	/* XXX */
E 67
I 67
D 68
	struct proc *p = curproc;	/* XXX */
E 68
E 67
E 62
	int cmd, type, error;

#ifndef QUOTA
	return (EOPNOTSUPP);
#else
	if (uid == -1)
D 62
		uid = u.u_ruid;
E 62
I 62
D 67
		uid = p->p_ruid;
E 67
I 67
		uid = p->p_cred->p_ruid;
E 67
E 62
	cmd = cmds >> SUBCMDSHIFT;

	switch (cmd) {
	case Q_GETQUOTA:
	case Q_SYNC:
D 62
		if (uid == u.u_ruid)
E 62
I 62
D 67
		if (uid == p->p_ruid)
E 67
I 67
		if (uid == p->p_cred->p_ruid)
E 67
E 62
			break;
		/* fall through */
	default:
D 67
		if (error = suser(ndp->ni_cred, &u.u_acflag))
E 67
I 67
		if (error = suser(p->p_ucred, &p->p_acflag))
E 67
			return (error);
	}

	type = cmd & SUBCMDMASK;
	if ((u_int)type >= MAXQUOTAS)
		return (EINVAL);

	switch (cmd) {

	case Q_QUOTAON:
D 67
		return (quotaon(ndp, mp, type, arg));
E 67
I 67
		return (quotaon(p, mp, type, arg));
E 67

	case Q_QUOTAOFF:
		if (vfs_busy(mp))
			return (0);
D 71
		error = quotaoff(mp, type);
E 71
I 71
		error = quotaoff(p, mp, type);
E 71
		vfs_unbusy(mp);
		return (error);

	case Q_SETQUOTA:
		return (setquota(mp, uid, type, arg));

	case Q_SETUSE:
		return (setuse(mp, uid, type, arg));

	case Q_GETQUOTA:
		return (getquota(mp, uid, type, arg));

	case Q_SYNC:
		if (vfs_busy(mp))
			return (0);
		error = qsync(mp);
		vfs_unbusy(mp);
		return (error);

	default:
		return (EINVAL);
	}
	/* NOTREACHED */
#endif
}

D 73
/*
E 56
 * Get file system statistics.
 */
D 68
ufs_statfs(mp, sbp)
E 68
I 68
ufs_statfs(mp, sbp, p)
E 68
	struct mount *mp;
	register struct statfs *sbp;
I 68
	struct proc *p;
E 68
{
	register struct ufsmount *ump;
	register struct fs *fs;
E 73
I 73
D 80
int syncprt = 0;
E 73

D 73
	ump = VFSTOUFS(mp);
	fs = ump->um_fs;
	if (fs->fs_magic != FS_MAGIC)
		panic("ufs_statfs");
	sbp->f_type = MOUNT_UFS;
D 42
	sbp->f_flags = mp->m_flag &~ (M_MLOCK|M_MWAIT);
E 42
	sbp->f_fsize = fs->fs_fsize;
	sbp->f_bsize = fs->fs_bsize;
	sbp->f_blocks = fs->fs_dsize;
	sbp->f_bfree = fs->fs_cstotal.cs_nbfree * fs->fs_frag +
		fs->fs_cstotal.cs_nffree;
	sbp->f_bavail = (fs->fs_dsize * (100 - fs->fs_minfree) / 100) -
		(fs->fs_dsize - sbp->f_bfree);
D 39
	if (sbp->f_bavail < 0)
		sbp->f_bavail = 0;
	sbp->f_files =  fs->fs_ncg * fs->fs_ipg;
E 39
I 39
	sbp->f_files =  fs->fs_ncg * fs->fs_ipg - ROOTINO;
E 39
	sbp->f_ffree = fs->fs_cstotal.cs_nifree;
D 42
	sbp->f_fsid = mp->m_fsid;
E 42
D 51
	bcopy((caddr_t)fs->fs_fsmnt, (caddr_t)&sbp->f_mntonname[0], MNAMELEN);
	bcopy((caddr_t)ump->um_mntname, (caddr_t)&sbp->f_mntfromname[0],
		MNAMELEN);
E 51
I 51
D 57
	if (sbp != &mp->m_stat) {
		bcopy((caddr_t)mp->m_stat.f_mntonname,
E 57
I 57
	if (sbp != &mp->mnt_stat) {
		bcopy((caddr_t)mp->mnt_stat.f_mntonname,
E 57
			(caddr_t)&sbp->f_mntonname[0], MNAMELEN);
D 57
		bcopy((caddr_t)mp->m_stat.f_mntfromname,
E 57
I 57
		bcopy((caddr_t)mp->mnt_stat.f_mntfromname,
E 57
			(caddr_t)&sbp->f_mntfromname[0], MNAMELEN);
	}
E 51
	return (0);
}

int	syncprt = 0;

E 73
/*
D 73
 * Go through the disk queues to initiate sandbagged IO;
 * go through the inodes to write those that have been modified;
 * initiate the writing of the super block if it has been modified.
I 56
 *
 * Note: we are always called with the filesystem marked `MPBUSY'.
E 56
 */
ufs_sync(mp, waitfor)
	struct mount *mp;
	int waitfor;
{
I 40
	register struct vnode *vp;
E 40
	register struct inode *ip;
	register struct ufsmount *ump = VFSTOUFS(mp);
	register struct fs *fs;
I 49
D 59
	struct vnode *nvp;
E 59
E 49
D 45
	int error = 0;
E 45
I 45
	int error, allerror = 0;
E 45
D 58
	static int updlock = 0;
E 58

	if (syncprt)
		bufstats();
D 58
	if (updlock)
		return (EBUSY);
E 58
	fs = ump->um_fs;
D 58
	if (fs == (struct fs *)1)
		return (0);
	updlock++;
E 58
	/*
	 * Write back modified superblock.
	 * Consistency check that the superblock
	 * is still in the buffer cache.
	 */
	if (fs->fs_fmod != 0) {
		if (fs->fs_ronly != 0) {		/* XXX */
			printf("fs = %s\n", fs->fs_fsmnt);
			panic("update: rofs mod");
		}
		fs->fs_fmod = 0;
		fs->fs_time = time.tv_sec;
D 61
		error = sbupdate(ump, waitfor);
E 61
I 61
		allerror = sbupdate(ump, waitfor);
E 61
	}
	/*
	 * Write back each (modified) inode.
	 */
D 40
	for (ip = inode; ip < inodeNINODE; ip++) {
		if (ip->i_devvp != ump->um_devvp ||
		    (ip->i_flag & ILOCKED) != 0 || ITOV(ip)->v_count == 0 ||
E 40
I 40
D 49
	for (vp = mp->m_mounth; vp; vp = vp->v_mountf) {
E 49
I 49
loop:
D 57
	for (vp = mp->m_mounth; vp; vp = nvp) {
E 57
I 57
D 59
	for (vp = mp->mnt_mounth; vp; vp = nvp) {
E 57
		nvp = vp->v_mountf;
E 59
I 59
	for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf) {
		/*
		 * If the vnode that we are about to sync is no longer
		 * associated with this mount point, start over.
		 */
		if (vp->v_mount != mp)
			goto loop;
I 70
		if (VOP_ISLOCKED(vp))
			continue;
E 70
E 59
E 49
		ip = VTOI(vp);
D 45
		if ((ip->i_flag & ILOCKED) != 0 || ITOV(ip)->v_count == 0 ||
E 45
I 45
D 48
		if ((ip->i_flag & ILOCKED) != 0 || vp->v_count == 0 ||
E 48
I 48
D 49
		if ((ip->i_flag & ILOCKED) != 0 || vp->v_usecount == 0 ||
E 48
E 45
E 40
		    (ip->i_flag & (IMOD|IACC|IUPD|ICHG)) == 0)
E 49
I 49
		if ((ip->i_flag & (IMOD|IACC|IUPD|ICHG)) == 0 &&
		    vp->v_dirtyblkhd == NULL)
E 49
			continue;
D 31
		ip->i_flag |= ILOCKED;
E 31
I 31
D 45
		ILOCK(ip);
E 45
E 31
D 32
		ITOV(ip)->v_count++;
E 32
I 32
D 40
		VREF(ITOV(ip));
E 40
I 40
D 49
		VREF(vp);
E 40
E 32
D 45
		error = iupdat(ip, &time, &time, waitfor == MNT_WAIT);
		iput(ip);
E 45
I 45
		VOP_LOCK(vp);
D 47
		if (error = VOP_FSYNC(vp, 0, NOCRED, waitfor))
E 47
I 47
		if (error = VOP_FSYNC(vp, 0, NOCRED, MNT_NOWAIT))
E 49
I 49
		if (vget(vp))
			goto loop;
		if (vp->v_dirtyblkhd)
			vflushbuf(vp, 0);
		if ((ip->i_flag & (IMOD|IACC|IUPD|ICHG)) &&
		    (error = iupdat(ip, &time, &time, 0)))
E 49
E 47
			allerror = error;
		vput(vp);
E 45
	}
D 58
	updlock = 0;
E 58
	/*
D 47
	 * Force stale buffer cache information to be flushed.
E 47
I 47
	 * Force stale file system control information to be flushed.
E 47
	 */
D 35
	bflush(ump->um_devvp->v_rdev);
E 35
I 35
D 46
	bflush(ump->um_devvp->v_mount);
E 46
I 46
D 47
	bflush(ump->um_devvp->v_mounton);
E 47
I 47
	vflushbuf(ump->um_devvp, waitfor == MNT_WAIT ? B_SYNC : 0);
I 56
#ifdef QUOTA
	qsync(mp);
#endif
E 56
E 47
E 46
E 35
D 45
	return (error);
E 45
I 45
	return (allerror);
E 45
}

/*
 * Write a superblock and associated information back to disk.
 */
sbupdate(mp, waitfor)
	struct ufsmount *mp;
	int waitfor;
{
	register struct fs *fs = mp->um_fs;
E 29
E 22
	register struct buf *bp;
	int blks;
	caddr_t space;
D 29
	int i, size;
E 29
I 29
	int i, size, error = 0;
E 29

I 18
#ifdef SECSIZE
	bp = getblk(mp->m_dev, (daddr_t)fsbtodb(fs, SBOFF / fs->fs_fsize),
	    (int)fs->fs_sbsize, fs->fs_dbsize);
#else SECSIZE
E 18
D 29
	bp = getblk(mp->m_dev, SBLOCK, (int)fs->fs_sbsize);
E 29
I 29
	bp = getblk(mp->um_devvp, SBLOCK, (int)fs->fs_sbsize);
E 29
I 18
#endif SECSIZE
E 18
	bcopy((caddr_t)fs, bp->b_un.b_addr, (u_int)fs->fs_sbsize);
I 24
	/* Restore compatibility to old file systems.		   XXX */
	if (fs->fs_postblformat == FS_42POSTBLFMT)		/* XXX */
		bp->b_un.b_fs->fs_nrpos = -1;			/* XXX */
E 24
I 18
#ifdef SECSIZE
#ifdef tahoe
	/* restore standard fsbtodb shift */
	bp->b_un.b_fs->fs_fsbtodb = fs->fs_sparecon[0];
	bp->b_un.b_fs->fs_sparecon[0] = 0;
#endif
#endif SECSIZE
E 18
D 29
	bwrite(bp);
E 29
I 29
	if (waitfor == MNT_WAIT)
		error = bwrite(bp);
	else
		bawrite(bp);
E 29
	blks = howmany(fs->fs_cssize, fs->fs_fsize);
	space = (caddr_t)fs->fs_csp[0];
	for (i = 0; i < blks; i += fs->fs_frag) {
		size = fs->fs_bsize;
		if (i + fs->fs_frag > blks)
			size = (blks - i) * fs->fs_fsize;
I 18
#ifdef SECSIZE
		bp = getblk(mp->m_dev, fsbtodb(fs, fs->fs_csaddr + i), size,
		    fs->fs_dbsize);
#else SECSIZE
E 18
D 29
		bp = getblk(mp->m_dev, fsbtodb(fs, fs->fs_csaddr + i), size);
E 29
I 29
		bp = getblk(mp->um_devvp, fsbtodb(fs, fs->fs_csaddr + i), size);
E 29
I 18
#endif SECSIZE
E 18
		bcopy(space, bp->b_un.b_addr, (u_int)size);
		space += size;
D 29
		bwrite(bp);
E 29
I 29
		if (waitfor == MNT_WAIT)
			error = bwrite(bp);
		else
			bawrite(bp);
E 29
	}
I 29
	return (error);
E 29
}

/*
E 73
D 29
 * Common code for mount and umount.
E 29
I 29
 * Print out statistics on the current allocation of the buffer pool.
 * Can be enabled to print out on every ``sync'' by setting "syncprt"
 * above.
 */
D 73
bufstats()
E 73
I 73
void
ufs_bufstats()
E 73
{
	int s, i, j, count;
	register struct buf *bp, *dp;
	int counts[MAXBSIZE/CLBYTES+1];
	static char *bname[BQUEUES] = { "LOCKED", "LRU", "AGE", "EMPTY" };

	for (bp = bfreelist, i = 0; bp < &bfreelist[BQUEUES]; bp++, i++) {
		count = 0;
		for (j = 0; j <= MAXBSIZE/CLBYTES; j++)
			counts[j] = 0;
		s = splbio();
		for (dp = bp->av_forw; dp != bp; dp = dp->av_forw) {
			counts[dp->b_bufsize/CLBYTES]++;
			count++;
		}
		splx(s);
		printf("%s: total-%d", bname[i], count);
		for (j = 0; j <= MAXBSIZE/CLBYTES; j++)
			if (counts[j] != 0)
				printf(", %d-%d", j * CLBYTES, counts[j]);
		printf("\n");
I 76
	}
}

E 80
/*
D 87
 * Build hash lists of net addresses and hang them off the mount point.
 * Called by ufs_mount() to set up the lists of export addresses.
 */
ufs_hang_addrlist(mp, argp)
	struct mount *mp;
	struct ufs_args *argp;
{
D 78
	register struct netaddrhash *np, **hnp;
E 78
I 78
	register struct netcred *np;
	register struct radix_node_head *rnh;
E 78
	register int i;
I 78
	struct radix_node *rn;
E 78
	struct ufsmount *ump;
D 78
	struct sockaddr *saddr;
	struct mbuf *nam, *msk = (struct mbuf *)0;
	union nethostaddr netmsk;
E 78
I 78
	struct sockaddr *saddr, *smask = 0;
	struct domain *dom;
E 78
	int error;

I 82
	ump = VFSTOUFS(mp);
E 82
D 78
	if (error = sockargs(&nam, (caddr_t)argp->saddr, argp->slen, MT_SONAME))
		return (error);
	saddr = mtod(nam, struct sockaddr *);
	ump = VFSTOUFS(mp);
	if (saddr->sa_family == AF_INET &&
		((struct sockaddr_in *)saddr)->sin_addr.s_addr == INADDR_ANY) {
		m_freem(nam);
E 78
I 78
	if (argp->slen == 0) {
E 78
		if (mp->mnt_flag & MNT_DEFEXPORTED)
			return (EPERM);
		np = &ump->um_defexported;
D 78
		np->neth_exflags = argp->exflags;
		np->neth_anon = argp->anon;
		np->neth_anon.cr_ref = 1;
E 78
I 78
		np->netc_exflags = argp->exflags;
		np->netc_anon = argp->anon;
		np->netc_anon.cr_ref = 1;
E 78
		mp->mnt_flag |= MNT_DEFEXPORTED;
		return (0);
	}
D 78
	if (argp->msklen > 0) {
		if (error = sockargs(&msk, (caddr_t)argp->smask, argp->msklen,
		    MT_SONAME)) {
			m_freem(nam);
			return (error);
		}

E 78
I 78
	i = sizeof(struct netcred) + argp->slen + argp->msklen;
	np = (struct netcred *)malloc(i, M_NETADDR, M_WAITOK);
	bzero((caddr_t)np, i);
	saddr = (struct sockaddr *)(np + 1);
	if (error = copyin(argp->saddr, (caddr_t)saddr, argp->slen))
		goto out;
	if (saddr->sa_len > argp->slen)
		saddr->sa_len = argp->slen;
	if (argp->msklen) {
		smask = (struct sockaddr *)((caddr_t)saddr + argp->slen);
		if (error = copyin(argp->saddr, (caddr_t)smask, argp->msklen))
			goto out;
		if (smask->sa_len > argp->msklen)
			smask->sa_len = argp->msklen;
	}
D 82
	ump = VFSTOUFS(mp);
E 82
	i = saddr->sa_family;
	if ((rnh = ump->um_rtable[i]) == 0) {
E 78
		/*
D 78
		 * Scan all the hash lists to check against duplications.
		 * For the net list, try both masks to catch a subnet
		 * of another network.
E 78
I 78
		 * Seems silly to initialize every AF when most are not
		 * used, do so on demand here
E 78
		 */
D 78
		hnp = &ump->um_netaddr[NETMASK_HASH];
		np = *hnp;
		if (saddr->sa_family == AF_INET)
			netmsk.had_inetaddr =
			    mtod(msk, struct sockaddr_in *)->sin_addr.s_addr;
		else
			netmsk.had_nam = msk;
		while (np) {
			if (netaddr_match(np->neth_family, &np->neth_haddr,
			    &np->neth_hmask, nam) ||
			    netaddr_match(np->neth_family, &np->neth_haddr,
			    &netmsk, nam)) {
				m_freem(nam);
				m_freem(msk);
				return (EPERM);
E 78
I 78
		for (dom = domains; dom; dom = dom->dom_next)
			if (dom->dom_family == i && dom->dom_rtattach) {
				dom->dom_rtattach((void **)&ump->um_rtable[i],
					dom->dom_rtoffset);
				break;
E 78
			}
D 78
			np = np->neth_next;
E 78
I 78
		if ((rnh = ump->um_rtable[i]) == 0) {
			error = ENOBUFS;
			goto out;
E 78
		}
D 78
		for (i = 0; i < NETHASHSZ; i++) {
			np = ump->um_netaddr[i];
			while (np) {
				if (netaddr_match(np->neth_family,
				    &np->neth_haddr, &netmsk, nam)) {
					m_freem(nam);
					m_freem(msk);
					return (EPERM);
				}
				np = np->neth_next;
			}
		}
	} else {
		hnp = &ump->um_netaddr[NETADDRHASH(saddr)];
		np = ump->um_netaddr[NETMASK_HASH];
		while (np) {
			if (netaddr_match(np->neth_family, &np->neth_haddr,
			    &np->neth_hmask, nam)) {
				m_freem(nam);
				return (EPERM);
			}
			np = np->neth_next;
		}
		np = *hnp;
		while (np) {
			if (netaddr_match(np->neth_family, &np->neth_haddr,
			    (union nethostaddr *)0, nam)) {
				m_freem(nam);
				return (EPERM);
			}
			np = np->neth_next;
		}
E 78
	}
D 78
	np = (struct netaddrhash *) malloc(sizeof(struct netaddrhash),
	    M_NETADDR, M_WAITOK);
	np->neth_family = saddr->sa_family;
	if (saddr->sa_family == AF_INET) {
		np->neth_inetaddr =
		    ((struct sockaddr_in *)saddr)->sin_addr.s_addr;
		m_freem(nam);
		if (msk) {
			np->neth_inetmask = netmsk.had_inetaddr;
			m_freem(msk);
			if (np->neth_inetaddr &~ np->neth_inetmask)
				return (EPERM);
		} else
			np->neth_inetmask = 0xffffffff;
	} else {
		np->neth_nam = nam;
		np->neth_msk = msk;
E 78
I 78
D 83
	rn = (*rnh->rnh_add)((caddr_t)saddr, (caddr_t)smask, rnh->rnh_treetop,
	    np->netc_rnodes);
E 83
I 83
	rn = (*rnh->rnh_addaddr)((caddr_t)saddr, (caddr_t)smask, rnh,
		np->netc_rnodes);
E 83
	if (rn == 0 || np != (struct netcred *)rn) { /* already exists */
		error = EPERM;
		goto out;
E 78
	}
D 78
	np->neth_exflags = argp->exflags;
	np->neth_anon = argp->anon;
	np->neth_anon.cr_ref = 1;
	np->neth_next = *hnp;
	*hnp = np;
E 78
I 78
	np->netc_exflags = argp->exflags;
	np->netc_anon = argp->anon;
	np->netc_anon.cr_ref = 1;
E 78
	return (0);
I 78
out:
	free(np, M_NETADDR);
	return (error);
E 78
}

I 78
/* ARGSUSED */
static int
ufs_free_netcred(rn, w)
	struct radix_node *rn;
	caddr_t w;
{
I 85
	register struct radix_node_head *rnh = (struct radix_node_head *)w;

	(*rnh->rnh_deladdr)(rn->rn_key, rn->rn_mask, rnh);
E 85
	free((caddr_t)rn, M_NETADDR);
I 84
	return (0);
E 84
}
	

E 78
/*
 * Free the net address hash lists that are hanging off the mount points.
 */
void
ufs_free_addrlist(ump)
	struct ufsmount *ump;
{
D 78
	register struct netaddrhash *np, *onp;
E 78
	register int i;
I 78
	register struct radix_node_head *rnh;
E 78

D 78
	for (i = 0; i <= NETHASHSZ; i++) {
		np = ump->um_netaddr[i];
		ump->um_netaddr[i] = (struct netaddrhash *)0;
		while (np) {
			onp = np;
			np = np->neth_next;
			if (onp->neth_family != AF_INET) {
				m_freem(onp->neth_nam);
				m_freem(onp->neth_msk);
			}
			free((caddr_t)onp, M_NETADDR);
E 78
I 78
	for (i = 0; i <= AF_MAX; i++)
		if (rnh = ump->um_rtable[i]) {
D 83
			(*rnh->rnh_walk)(rnh->rnh_treetop,
				ufs_free_netcred, (caddr_t)0);
E 83
I 83
D 85
			(*rnh->rnh_walktree)(rnh, ufs_free_netcred, (caddr_t)0);
E 85
I 85
			(*rnh->rnh_walktree)(rnh, ufs_free_netcred,
			    (caddr_t)rnh);
E 85
E 83
			free((caddr_t)rnh, M_RTABLE);
			ump->um_rtable[i] = 0;
E 78
		}
I 78
}

/*
E 87
 * This is the generic part of fhtovp called after the underlying
 * filesystem has validated the file handle.
 *
 * Verify that a host should have access to a filesystem, and if so
 * return a vnode for the presented file handle.
 */
int
D 79
ufs_check_export(mp, fhp, nam, vpp, exflagsp, credanonp)
E 79
I 79
ufs_check_export(mp, ufhp, nam, vpp, exflagsp, credanonp)
E 79
	register struct mount *mp;
D 79
	struct fid *fhp;
E 79
I 79
	struct ufid *ufhp;
E 79
	struct mbuf *nam;
	struct vnode **vpp;
	int *exflagsp;
	struct ucred **credanonp;
{
D 79
	register struct ufid *ufhp;
E 79
	register struct inode *ip;
	register struct netcred *np;
	register struct ufsmount *ump = VFSTOUFS(mp);
D 87
	register struct radix_node_head *rnh;
E 87
	struct vnode *nvp;
D 87
	struct sockaddr *saddr;
E 87
	int error;

	/*
	 * Get the export permission structure for this <mp, client> tuple.
	 */
D 87
	if ((mp->mnt_flag & MNT_EXPORTED) == 0)
E 87
I 87
	np = vfs_export_lookup(mp, &ump->um_export, nam);
	if (np == NULL)
E 87
		return (EACCES);
D 82
	if (nam == NULL) {
		np = NULL;
	} else {
E 82
I 82
D 87
	np = NULL;
	if (nam != NULL) {
E 82
		saddr = mtod(nam, struct sockaddr *);
		rnh = ump->um_rtable[saddr->sa_family];
D 82
		if (rnh == NULL) {
			np = NULL;
		} else {
E 82
I 82
		if (rnh != NULL) {
E 82
			np = (struct netcred *)
D 83
			    (*rnh->rnh_match)((caddr_t)saddr, rnh->rnh_treetop);
E 83
I 83
			    (*rnh->rnh_matchaddr)((caddr_t)saddr, rnh);
E 83
D 82
			if (np->netc_rnodes->rn_flags & RNF_ROOT)
E 82
I 82
			if (np && np->netc_rnodes->rn_flags & RNF_ROOT)
E 82
				np = NULL;
		}
E 78
E 76
	}
I 78
	if (np == NULL) {
		/*
		 * If no address match, use the default if it exists.
		 */
		if ((mp->mnt_flag & MNT_DEFEXPORTED) == 0)
			return (EACCES);
		np = &ump->um_defexported;
	}
E 87
I 87

E 87
	if (error = VFS_VGET(mp, ufhp->ufid_ino, &nvp)) {
		*vpp = NULLVP;
		return (error);
	}
	ip = VTOI(nvp);
	if (ip->i_mode == 0 || ip->i_gen != ufhp->ufid_gen) {
D 81
		ufs_iput(ip);
E 81
I 81
		vput(nvp);
E 81
		*vpp = NULLVP;
		return (ESTALE);
	}
	*vpp = nvp;
	*exflagsp = np->netc_exflags;
	*credanonp = &np->netc_anon;
	return (0);
E 78
D 74
}

/*
 * File handle to vnode
I 34
 *
 * Have to be really careful about stale file handles:
D 73
 * - check that the inode number is in range
E 73
I 73
 * - check that the inode number is valid
E 73
 * - call iget() to get the locked inode
 * - check for an unallocated inode (i_mode == 0)
 * - check that the generation number matches
E 34
 */
I 73
int
E 73
ufs_fhtovp(mp, fhp, vpp)
D 34
	struct mount *mp;
E 34
I 34
	register struct mount *mp;
E 34
	struct fid *fhp;
	struct vnode **vpp;
{
D 73
	register struct ufid *ufhp;
I 34
	register struct fs *fs;
E 73
E 34
D 40
	struct inode tip, *ip;
E 40
I 40
	register struct inode *ip;
I 73
	register struct ufid *ufhp;
	struct ufsmount *ump;
E 73
	struct inode *nip;
	struct vnode tvp;
E 40
	int error;

	ufhp = (struct ufid *)fhp;
I 34
D 73
	fs = VFSTOUFS(mp)->um_fs;
	if (ufhp->ufid_ino < ROOTINO ||
	    ufhp->ufid_ino >= fs->fs_ncg * fs->fs_ipg) {
D 57
		*vpp = (struct vnode *)0;
E 57
I 57
		*vpp = NULLVP;
E 57
		return (EINVAL);
	}
E 73
I 73
	ump = VFSTOUFS(mp);
E 73
E 34
D 40
	tip.i_dev = VFSTOUFS(mp)->um_dev;
	tip.i_vnode.v_mount = mp;
	if (error = iget(&tip, ufhp->ufid_ino, &ip)) {
E 40
I 40
	tvp.v_mount = mp;
	ip = VTOI(&tvp);
	ip->i_vnode = &tvp;
D 73
	ip->i_dev = VFSTOUFS(mp)->um_dev;
	if (error = iget(ip, ufhp->ufid_ino, &nip)) {
E 73
I 73
	ip->i_dev = ump->um_dev;
	if (error = (ump->um_iget)(ip, ufhp->ufid_ino, &nip)) {
E 73
E 40
D 34
		*vpp = NULL;
E 34
I 34
D 57
		*vpp = (struct vnode *)0;
E 57
I 57
		*vpp = NULLVP;
E 57
E 34
		return (error);
	}
I 40
	ip = nip;
E 40
I 34
	if (ip->i_mode == 0) {
D 73
		iput(ip);
E 73
I 73
		ufs_iput(ip);
E 73
D 57
		*vpp = (struct vnode *)0;
E 57
I 57
		*vpp = NULLVP;
E 57
		return (EINVAL);
	}
E 34
	if (ip->i_gen != ufhp->ufid_gen) {
D 73
		iput(ip);
E 73
I 73
		ufs_iput(ip);
E 73
D 34
		*vpp = NULL;
E 34
I 34
D 57
		*vpp = (struct vnode *)0;
E 57
I 57
		*vpp = NULLVP;
E 57
E 34
		return (EINVAL);
	}
	*vpp = ITOV(ip);
	return (0);
}

/*
D 33
 * Vnode pointer to File handle, should never happen.
E 33
I 33
 * Vnode pointer to File handle
E 33
 */
/* ARGSUSED */
D 30
ufs_vptofh(mp, fhp, vpp)
	struct mount *mp;
E 30
I 30
ufs_vptofh(vp, fhp)
	struct vnode *vp;
E 30
	struct fid *fhp;
D 30
	struct vnode **vpp;
E 30
{
I 30
D 73
	register struct inode *ip = VTOI(vp);
E 73
I 73
	register struct inode *ip;
E 73
	register struct ufid *ufhp;
E 30

I 73
	ip = VTOI(vp);
E 73
D 30
	return (EINVAL);
E 30
I 30
	ufhp = (struct ufid *)fhp;
	ufhp->ufid_len = sizeof(struct ufid);
	ufhp->ufid_ino = ip->i_number;
	ufhp->ufid_gen = ip->i_gen;
D 72
	return (0);
E 30
}

/*
D 60
 * Common code for mount and quota.
E 60
E 29
 * Check that the user's argument is a reasonable
 * thing on which to mount, and return the device number if so.
 */
D 6
getmdev(pdev)
E 6
I 6
D 29
getmdev(pdev, fname)
E 29
I 29
D 68
getmdev(devvpp, fname, ndp)
E 68
I 68
getmdev(devvpp, fname, ndp, p)
E 68
	struct vnode **devvpp;
E 29
	caddr_t fname;
E 6
D 29
	dev_t *pdev;
E 29
I 29
	register struct nameidata *ndp;
I 68
	struct proc *p;
E 68
E 29
{
D 29
	dev_t dev;
	register struct inode *ip;
I 6
	register struct nameidata *ndp = &u.u_nd;
E 29
I 29
	register struct vnode *vp;
	int error;
E 29
E 6

D 28
	if (!suser())
E 28
I 28
D 29
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 28
		return (u.u_error);
D 6
	ip = namei(uchar, LOOKUP, 1);
E 6
I 6
	ndp->ni_nameiop = LOOKUP | FOLLOW;
E 29
I 29
D 60
	ndp->ni_nameiop = LOOKUP | LOCKLEAF | FOLLOW;
E 60
I 60
	ndp->ni_nameiop = LOOKUP | FOLLOW;
E 60
E 29
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = fname;
D 29
	ip = namei(ndp);
E 6
D 11
	if (ip == NULL)
E 11
I 11
	if (ip == NULL) {
		if (u.u_error == ENOENT)
			return (ENODEV); /* needs translation */
E 11
		return (u.u_error);
E 29
I 29
D 64
	if (error = namei(ndp)) {
		if (error == ENOENT)
			return (ENODEV);	/* needs translation */
E 64
I 64
D 67
	if (error = namei(ndp))
E 67
I 67
D 68
	if (error = namei(ndp, curproc))		/* XXX */
E 68
I 68
	if (error = namei(ndp, p))
E 68
E 67
E 64
		return (error);
E 29
I 11
D 64
	}
E 64
E 11
D 4
	if ((ip->i_mode&IFMT) != IFBLK)
E 4
I 4
D 29
	if ((ip->i_mode&IFMT) != IFBLK) {
		iput(ip);
E 29
I 29
	vp = ndp->ni_vp;
	if (vp->v_type != VBLK) {
D 60
		vput(vp);
E 60
I 60
		vrele(vp);
E 60
E 29
E 4
		return (ENOTBLK);
I 4
	}
E 4
D 29
	dev = (dev_t)ip->i_rdev;
I 4
	iput(ip);
E 4
	if (major(dev) >= nblkdev)
E 29
I 29
D 44
	if (major(vp->v_rdev) >= nblkdev)
E 44
I 44
	if (major(vp->v_rdev) >= nblkdev) {
D 60
		vput(vp);
E 60
I 60
		vrele(vp);
E 60
E 44
E 29
		return (ENXIO);
I 44
	}
E 44
D 4
	iput(ip);
E 4
D 29
	*pdev = dev;
E 29
I 29
D 60
	iunlock(VTOI(vp));
E 60
	*devvpp = vp;
E 72
E 29
	return (0);
E 74
}
E 1
