h10372
s 00004/00005/00258
d D 8.11 95/06/19 11:41:14 mckusick 49 48
c do not return error after sucessful unmount
e
s 00005/00013/00258
d D 8.10 95/05/20 01:23:27 mckusick 48 47
c merge vfs_lock and vfs_busy; interlock mount points properly
e
s 00005/00003/00266
d D 8.9 95/05/10 13:22:17 mckusick 47 46
c mountroot should fail, not panic
e
s 00007/00019/00262
d D 8.8 95/05/10 12:10:22 mckusick 46 45
c use vfs_rootmountalloc
e
s 00000/00001/00281
d D 8.7 95/05/10 09:52:40 mckusick 45 44
c check for forcible unmount at syscall level
e
s 00001/00001/00281
d D 8.6 95/05/09 12:28:47 mckusick 44 43
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00002/00001/00280
d D 8.5 95/03/30 14:22:54 mckusick 43 42
c add ffs_sysctl; MOUNT_MFS goes away
e
s 00002/00002/00279
d D 8.4 94/04/16 06:32:06 bostic 42 41
c merge ffs_root and lfs_root into ufs_root
e
s 00008/00003/00273
d D 8.3 94/01/12 15:35:44 hibler 41 40
c allow (optional) exporting to NFS,
c use new vfs_export routine
e
s 00003/00004/00273
d D 8.2 93/12/30 16:16:47 mckusick 40 39
c new queue structure
e
s 00002/00002/00275
d D 8.1 93/06/11 16:27:35 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00002/00260
d D 7.30 92/12/09 19:29:40 mckusick 38 37
c allow downgrade of read-write to read-only (though I cannot imagine
c why anybody would want to do this on a memory-based filesystem!)
e
s 00001/00001/00261
d D 7.29 92/11/15 21:56:34 mckusick 37 36
c MNT_NOFORCE no longer has its own flag
e
s 00001/00001/00261
d D 7.28 92/10/02 00:19:42 mckusick 36 35
c av_forw/av_back are gone; now use b_actf/b_actb for linking active buffers
e
s 00006/00000/00256
d D 7.27 92/09/22 22:03:05 mckusick 35 34
c rootvp and swapvp now done in ?fs_mountroot
e
s 00001/00000/00255
d D 7.26 92/07/03 01:52:28 mckusick 34 33
c use ffs_vget
e
s 00003/00003/00252
d D 7.25 92/05/14 17:30:23 heideman 33 24
c vnode interface conversion
e
s 00003/00003/00252
d R 7.25 92/05/14 15:44:12 heideman 32 24
c vnode interface conversion
e
s 00003/00003/00252
d R 7.25 92/05/14 14:49:24 heideman 31 24
c vnode interface conversion
e
s 00003/00003/00252
d R 7.25 92/05/14 12:53:20 heideman 30 24
c vnode interface conversion
e
s 00003/00003/00252
d R 7.25 92/05/14 11:50:39 heideman 29 24
c vnode interface conversion
e
s 00003/00003/00252
d R 7.25 92/05/14 10:30:55 heideman 28 24
c vnode interface conversion
e
s 00003/00003/00252
d R 7.25 92/05/13 23:09:32 heideman 27 24
c vnode interface conversion
e
s 00003/00003/00252
d R 7.25 92/05/13 18:56:00 heideman 26 24
c vnode interface conversion
e
s 00003/00003/00252
d R 7.25 92/05/13 18:28:03 heideman 25 24
c vnode interface conversion
e
s 00006/00002/00249
d D 7.24 92/04/19 08:42:25 ralph 24 23
c change rootdev if mfs mini-root present.
e
s 00083/00000/00168
d D 7.23 92/03/22 20:32:25 ralph 23 22
c added support for memory mini-root.
e
s 00003/00001/00165
d D 7.22 91/12/16 15:52:10 mckusick 22 21
c dynamically allocate private part
e
s 00003/00003/00163
d D 7.21 91/11/05 15:46:11 mckusick 21 20
c reorganization to move ufsmount ops to be vnode ops
e
s 00025/00029/00141
d D 7.20 91/11/01 17:12:06 bostic 20 19
c UFS/FFS split for LFS version 1; fixes for mountfs and ufs_statfs calls
e
s 00009/00007/00161
d D 7.19 91/04/16 00:21:05 mckusick 19 18
c add appropriate proc pointers to VFS ops
e
s 00009/00008/00159
d D 7.18 91/03/19 10:30:17 karels 18 17
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00001/00011/00166
d D 7.17 90/06/28 22:29:44 bostic 17 16
c new copyright notice
e
s 00010/00010/00167
d D 7.16 90/06/27 14:40:00 karels 16 15
c better fix for loop if unmount fails; clear signal and wait for another
e
s 00005/00000/00172
d D 7.15 90/06/09 08:18:56 mckusick 15 14
c temporary hack to avoid infinite signals on shutdown
e
s 00007/00006/00165
d D 7.14 90/05/04 20:51:24 mckusick 14 13
c mount struct prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00003/00000/00168
d D 7.13 90/05/02 19:34:40 mckusick 13 12
c add quotactl vfs op
e
s 00011/00012/00157
d D 7.12 90/04/27 16:23:23 karels 12 11
c eliminate longjmp's in the kernel
e
s 00001/00000/00168
d D 7.11 90/04/10 20:11:20 mckusick 11 10
c clear the buffer list before vrele
e
s 00007/00005/00161
d D 7.10 90/03/06 23:30:22 mckusick 10 9
c mntfrom and mnton are now maintained in m_stat
e
s 00003/00002/00163
d D 7.9 90/02/08 17:14:45 marc 9 8
c tsleep
e
s 00001/00002/00164
d D 7.8 89/11/25 15:23:51 mckusick 8 7
c checkalias now sets rdev
e
s 00016/00002/00150
d D 7.7 89/11/24 16:20:19 mckusick 7 6
c return type MOUNT_MFS instead of MOUNT_UFS to statfs
e
s 00004/00000/00148
d D 7.6 89/10/29 23:41:44 mckusick 6 5
c add file system initialization routine; panic if device alias found
e
s 00018/00010/00130
d D 7.5 89/10/24 19:39:24 mckusick 5 4
c create own private data area instead of overloading an inode
e
s 00018/00006/00122
d D 7.4 89/10/20 18:36:30 mckusick 4 3
c allow multiple I/O requests; try to unmount when signalled
e
s 00007/00000/00121
d D 7.3 89/10/19 00:11:03 mckusick 3 2
c allow update of mounted file systems
e
s 00000/00002/00121
d D 7.2 89/09/12 22:06:16 mckusick 2 1
c allow multiple memory based file systems
e
s 00123/00000/00000
d D 7.1 89/09/05 16:20:23 mckusick 1 0
c date and time created 89/09/05 16:20:23 by mckusick
e
u
U
t
T
I 1
/*
D 12
 * Copyright (c) 1989 The Regents of the University of California.
E 12
I 12
D 39
 * Copyright (c) 1989, 1990 The Regents of the University of California.
E 12
 * All rights reserved.
E 39
I 39
D 42
 * Copyright (c) 1989, 1990, 1993
E 42
I 42
 * Copyright (c) 1989, 1990, 1993, 1994
E 42
 *	The Regents of the University of California.  All rights reserved.
E 39
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

D 20
#include "param.h"
I 4
#include "time.h"
I 15
#include "kernel.h"
E 15
D 18
#include "user.h"
E 18
#include "proc.h"
E 4
#include "buf.h"
#include "mount.h"
I 18
#include "signalvar.h"
E 18
D 4
#include "time.h"
E 4
#include "vnode.h"
E 20
I 20
#include <sys/param.h>
I 24
#include <sys/systm.h>
E 24
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/mount.h>
#include <sys/signalvar.h>
#include <sys/vnode.h>
I 22
#include <sys/malloc.h>
E 22
E 20
I 13
D 18
#include "../ufs/quota.h"
E 13
I 9
D 12
#include "tsleep.h"
E 12
E 9
D 5
#include "../ufs/ufsmount.h"
E 5
#include "../ufs/inode.h"
I 5
#include "../ufs/ufsmount.h"
#include "../ufs/mfsnode.h"
E 5
#include "../ufs/fs.h"
E 18

I 18
D 20
#include "quota.h"
#include "inode.h"
#include "ufsmount.h"
#include "mfsnode.h"
#include "fs.h"
E 20
I 20
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/ufs_extern.h>
E 20

I 20
#include <ufs/ffs/fs.h>
#include <ufs/ffs/ffs_extern.h>

#include <ufs/mfs/mfsnode.h>
#include <ufs/mfs/mfs_extern.h>

I 23
caddr_t	mfs_rootbase;	/* address of mini-root in kernel virtual memory */
u_long	mfs_rootsize;	/* size of mini-root in bytes */

I 24
static	int mfs_minor;	/* used for building internal dev_t */

E 24
E 23
E 20
E 18
D 2
extern int mfs_running;			/* 1 => daemon has started running */
E 2
D 33
extern struct vnodeops mfs_vnodeops;
E 33
I 33
extern int (**mfs_vnodeop_p)();
E 33

/*
 * mfs vfs operations.
 */
D 20
int mfs_mount();
int mfs_start();
int ufs_unmount();
int ufs_root();
I 13
int ufs_quotactl();
E 13
D 7
int ufs_statfs();
E 7
I 7
int mfs_statfs();
E 7
int ufs_sync();
int ufs_fhtovp();
int ufs_vptofh();
I 6
int mfs_init();
E 6

E 20
struct vfsops mfs_vfsops = {
	mfs_mount,
	mfs_start,
D 20
	ufs_unmount,
E 20
I 20
	ffs_unmount,
E 20
D 21
	ufs_root,
E 21
I 21
D 42
	ffs_root,
E 42
I 42
	ufs_root,
E 42
E 21
I 13
	ufs_quotactl,
E 13
D 7
	ufs_statfs,
E 7
I 7
	mfs_statfs,
E 7
D 20
	ufs_sync,
E 20
I 20
	ffs_sync,
I 34
	ffs_vget,
E 34
E 20
D 21
	ufs_fhtovp,
	ufs_vptofh,
E 21
I 21
	ffs_fhtovp,
	ffs_vptofh,
E 21
I 6
	mfs_init,
I 43
	ffs_sysctl,
E 43
E 6
};
I 23

/*
 * Called by main() when mfs is going to be mounted as root.
D 46
 *
 * Name is updated by mount(8) after booting.
E 46
 */
D 24
#define ROOTNAME	"root_device"
E 24
I 24
D 46
#define ROOTNAME	"mfs_root"
E 24

E 46
mfs_mountroot()
{
	extern struct vnode *rootvp;
D 46
	register struct fs *fs;
	register struct mount *mp;
E 46
I 46
	struct fs *fs;
	struct mount *mp;
E 46
	struct proc *p = curproc;	/* XXX */
	struct ufsmount *ump;
	struct mfsnode *mfsp;
D 46
	u_int size;
E 46
	int error;

I 35
	/*
	 * Get vnodes for swapdev and rootdev.
	 */
D 47
	if (bdevvp(swapdev, &swapdev_vp) || bdevvp(rootdev, &rootvp))
		panic("mfs_mountroot: can't setup bdevvp's");

E 47
I 47
	if ((error = bdevvp(swapdev, &swapdev_vp)) ||
	    (error = bdevvp(rootdev, &rootvp))) {
		printf("mfs_mountroot: can't setup bdevvp's");
		return (error);
	}
E 47
E 35
D 46
	mp = malloc((u_long)sizeof(struct mount), M_MOUNT, M_WAITOK);
I 40
	bzero((char *)mp, (u_long)sizeof(struct mount));
E 40
	mp->mnt_op = &mfs_vfsops;
	mp->mnt_flag = MNT_RDONLY;
E 46
I 46
	if (error = vfs_rootmountalloc("mfs", "mfs_root", &mp))
		return (error);
E 46
D 40
	mp->mnt_mounth = NULLVP;
E 40
	mfsp = malloc(sizeof *mfsp, M_MFSNODE, M_WAITOK);
	rootvp->v_data = mfsp;
D 33
	rootvp->v_op = &mfs_vnodeops;
E 33
I 33
	rootvp->v_op = mfs_vnodeop_p;
E 33
I 24
	rootvp->v_tag = VT_MFS;
E 24
	mfsp->mfs_baseoff = mfs_rootbase;
	mfsp->mfs_size = mfs_rootsize;
	mfsp->mfs_vnode = rootvp;
	mfsp->mfs_pid = p->p_pid;
	mfsp->mfs_buflist = (struct buf *)0;
	if (error = ffs_mountfs(rootvp, mp, p)) {
I 46
		mp->mnt_vfc->vfc_refcount--;
I 48
		vfs_unbusy(mp, p);
E 48
E 46
		free(mp, M_MOUNT);
		free(mfsp, M_MFSNODE);
		return (error);
	}
D 48
	if (error = vfs_lock(mp)) {
		(void)ffs_unmount(mp, 0, p);
I 46
		mp->mnt_vfc->vfc_refcount--;
E 46
		free(mp, M_MOUNT);
		free(mfsp, M_MFSNODE);
		return (error);
	}
E 48
I 48
	simple_lock(&mountlist_slock);
E 48
D 40
	rootfs = mp;
	mp->mnt_next = mp;
	mp->mnt_prev = mp;
E 40
I 40
D 44
	TAILQ_INSERT_TAIL(&mountlist, mp, mnt_list);
E 44
I 44
	CIRCLEQ_INSERT_TAIL(&mountlist, mp, mnt_list);
I 48
	simple_unlock(&mountlist_slock);
E 48
E 44
D 45
	mp->mnt_flag |= MNT_ROOTFS;
E 45
E 40
D 46
	mp->mnt_vnodecovered = NULLVP;
E 46
	ump = VFSTOUFS(mp);
	fs = ump->um_fs;
D 46
	bzero(fs->fs_fsmnt, sizeof(fs->fs_fsmnt));
	fs->fs_fsmnt[0] = '/';
	bcopy((caddr_t)fs->fs_fsmnt, (caddr_t)mp->mnt_stat.f_mntonname,
	    MNAMELEN);
	(void) copystr(ROOTNAME, mp->mnt_stat.f_mntfromname, MNAMELEN - 1,
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
E 46
I 46
	(void) copystr(mp->mnt_stat.f_mntonname, fs->fs_fsmnt, MNAMELEN - 1, 0);
E 46
	(void)ffs_statfs(mp, &mp->mnt_stat, p);
D 48
	vfs_unlock(mp);
E 48
I 48
	vfs_unbusy(mp, p);
E 48
	inittodr((time_t)0);
	return (0);
}

/*
 * This is called early in boot to set the base address and size
 * of the mini-root.
 */
mfs_initminiroot(base)
	caddr_t base;
{
	struct fs *fs = (struct fs *)(base + SBOFF);
	extern int (*mountroot)();

	/* check for valid super block */
	if (fs->fs_magic != FS_MAGIC || fs->fs_bsize > MAXBSIZE ||
	    fs->fs_bsize < sizeof(struct fs))
		return (0);
	mountroot = mfs_mountroot;
	mfs_rootbase = base;
	mfs_rootsize = fs->fs_fsize * fs->fs_size;
I 24
	rootdev = makedev(255, mfs_minor++);
E 24
	return (mfs_rootsize);
}
E 23

/*
 * VFS Operations.
 *
 * mount system call
 */
I 5
/* ARGSUSED */
I 20
int
E 20
E 5
D 19
mfs_mount(mp, path, data, ndp)
E 19
I 19
mfs_mount(mp, path, data, ndp, p)
E 19
D 10
	struct mount *mp;
E 10
I 10
	register struct mount *mp;
E 10
	char *path;
	caddr_t data;
	struct nameidata *ndp;
I 19
	struct proc *p;
E 19
{
	struct vnode *devvp;
	struct mfs_args args;
	struct ufsmount *ump;
	register struct fs *fs;
I 5
	register struct mfsnode *mfsp;
E 5
D 24
	static int mfs_minor;
E 24
	u_int size;
D 38
	int error;
E 38
I 38
	int flags, error;
E 38

I 41
	if (error = copyin(data, (caddr_t)&args, sizeof (struct mfs_args)))
		return (error);

E 41
I 38
	/*
	 * If updating, check whether changing from read-only to
	 * read/write; if there is no device name, that's all we do.
	 */
E 38
I 3
D 14
	if (mp->m_flag & M_UPDATE) {
E 14
I 14
	if (mp->mnt_flag & MNT_UPDATE) {
E 14
		ump = VFSTOUFS(mp);
		fs = ump->um_fs;
D 14
		if (fs->fs_ronly && (mp->m_flag & M_RDONLY) == 0)
E 14
I 14
D 38
		if (fs->fs_ronly && (mp->mnt_flag & MNT_RDONLY) == 0)
E 38
I 38
		if (fs->fs_ronly == 0 && (mp->mnt_flag & MNT_RDONLY)) {
			flags = WRITECLOSE;
			if (mp->mnt_flag & MNT_FORCE)
				flags |= FORCECLOSE;
D 48
			if (vfs_busy(mp))
				return (EBUSY);
			error = ffs_flushfiles(mp, flags, p);
			vfs_unbusy(mp);
			if (error)
E 48
I 48
			if (error = ffs_flushfiles(mp, flags, p))
E 48
				return (error);
		}
		if (fs->fs_ronly && (mp->mnt_flag & MNT_WANTRDWR))
E 38
E 14
			fs->fs_ronly = 0;
I 41
#ifdef EXPORTMFS
		if (args.fspec == 0)
			return (vfs_export(mp, &ump->um_export, &args.export));
#endif
E 41
		return (0);
	}
E 3
D 41
	if (error = copyin(data, (caddr_t)&args, sizeof (struct mfs_args)))
		return (error);
E 41
D 5
	if ((error = bdevvp(NODEV, &devvp)) != 0)
E 5
I 5
D 33
	error = getnewvnode(VT_MFS, (struct mount *)0, &mfs_vnodeops, &devvp);
E 33
I 33
	error = getnewvnode(VT_MFS, (struct mount *)0, mfs_vnodeop_p, &devvp);
E 33
	if (error)
E 5
		return (error);
D 5
	devvp->v_op = &mfs_vnodeops;
E 5
I 5
	devvp->v_type = VBLK;
E 5
D 8
	devvp->v_rdev = makedev(255, mfs_minor++);
I 6
	if (checkalias(devvp, (struct mount *)0) != NULL)
E 8
I 8
	if (checkalias(devvp, makedev(255, mfs_minor++), (struct mount *)0))
E 8
		panic("mfs_mount: dup dev");
E 6
D 5
	VTOI(devvp)->i_diroff = (long)args.base;
	VTOI(devvp)->i_endoff = args.size;
E 5
I 5
D 22
	mfsp = VTOMFS(devvp);
E 22
I 22
	mfsp = (struct mfsnode *)malloc(sizeof *mfsp, M_MFSNODE, M_WAITOK);
	devvp->v_data = mfsp;
E 22
	mfsp->mfs_baseoff = args.base;
	mfsp->mfs_size = args.size;
	mfsp->mfs_vnode = devvp;
D 18
	mfsp->mfs_pid = u.u_procp->p_pid;
E 18
I 18
D 19
	mfsp->mfs_pid = curproc->p_pid;
E 19
I 19
	mfsp->mfs_pid = p->p_pid;
E 19
E 18
	mfsp->mfs_buflist = (struct buf *)0;
E 5
D 10
	error = mountfs(devvp, mp);
	if (error) {
E 10
I 10
D 20
	if (error = mountfs(devvp, mp)) {
E 20
I 20
	if (error = ffs_mountfs(devvp, mp, p)) {
E 20
I 11
		mfsp->mfs_buflist = (struct buf *)-1;
E 11
E 10
		vrele(devvp);
		return (error);
	}
	ump = VFSTOUFS(mp);
	fs = ump->um_fs;
	(void) copyinstr(path, fs->fs_fsmnt, sizeof(fs->fs_fsmnt) - 1, &size);
	bzero(fs->fs_fsmnt + size, sizeof(fs->fs_fsmnt) - size);
D 10
	(void) copyinstr(args.name, ump->um_mntname, MNAMELEN - 1, &size);
	bzero(ump->um_mntname + size, MNAMELEN - size);
E 10
I 10
D 14
	bcopy((caddr_t)fs->fs_fsmnt, (caddr_t)mp->m_stat.f_mntonname, MNAMELEN);
	(void) copyinstr(args.name, mp->m_stat.f_mntfromname, MNAMELEN - 1,
E 14
I 14
	bcopy((caddr_t)fs->fs_fsmnt, (caddr_t)mp->mnt_stat.f_mntonname,
		MNAMELEN);
D 41
	(void) copyinstr(args.name, mp->mnt_stat.f_mntfromname, MNAMELEN - 1,
E 41
I 41
	(void) copyinstr(args.fspec, mp->mnt_stat.f_mntfromname, MNAMELEN - 1,
E 41
E 14
		&size);
D 14
	bzero(mp->m_stat.f_mntfromname + size, MNAMELEN - size);
	(void) mfs_statfs(mp, &mp->m_stat);
E 14
I 14
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
D 20
	(void) mfs_statfs(mp, &mp->mnt_stat);
E 20
I 20
	(void) mfs_statfs(mp, &mp->mnt_stat, p);
E 20
E 14
E 10
	return (0);
}

I 12
int	mfs_pri = PWAIT | PCATCH;		/* XXX prob. temp */

E 12
/*
 * Used to grab the process and keep it in the kernel to service
 * memory filesystem I/O requests.
 *
 * Loop servicing I/O requests.
 * Copy the requested data into or out of the memory filesystem
 * address space.
 */
/* ARGSUSED */
I 20
int
E 20
D 19
mfs_start(mp, flags)
E 19
I 19
mfs_start(mp, flags, p)
E 19
	struct mount *mp;
	int flags;
I 19
	struct proc *p;
E 19
{
	register struct vnode *vp = VFSTOUFS(mp)->um_devvp;
D 5
	register struct inode *ip = VTOI(vp);
E 5
I 5
	register struct mfsnode *mfsp = VTOMFS(vp);
E 5
	register struct buf *bp;
	register caddr_t base;
I 16
D 18
	struct proc *p = u.u_procp;
E 18
I 18
D 19
	struct proc *p = curproc;
E 19
E 18
E 16
I 12
D 49
	int error = 0;
E 49
E 12

D 2
	mfs_running++;
E 2
D 4
	sleep((caddr_t)vp, PRIBIO);
E 4
D 5
	base = (caddr_t)ip->i_diroff;
E 5
I 5
	base = mfsp->mfs_baseoff;
E 5
D 4
	while (bp = (struct buf *)ip->i_spare[0]) {
		mfs_doio(bp, base);
		wakeup((caddr_t)bp);
		sleep((caddr_t)vp, PRIBIO);
E 4
I 4
D 12
	if (setjmp(&u.u_qsave)) {
		/*
		 * We have received a signal, so try to unmount.
		 */
		(void) dounmount(mp, MNT_NOFORCE);
	} else {
D 9
		sleep((caddr_t)vp, PWAIT);
E 9
I 9
		tsleep((caddr_t)vp, PWAIT, SLP_MFS, 0);
E 9
	}
E 12
D 5
	while (ip->i_spare[0] != -1) {
		while (bp = (struct buf *)ip->i_spare[0]) {
			ip->i_spare[0] = (long)bp->av_forw;
E 5
I 5
	while (mfsp->mfs_buflist != (struct buf *)(-1)) {
		while (bp = mfsp->mfs_buflist) {
D 36
			mfsp->mfs_buflist = bp->av_forw;
E 36
I 36
			mfsp->mfs_buflist = bp->b_actf;
E 36
E 5
			mfs_doio(bp, base);
			wakeup((caddr_t)bp);
		}
D 9
		sleep((caddr_t)vp, PWAIT);
E 9
I 9
D 12
		tsleep((caddr_t)vp, PWAIT, SLP_MFS, 0);
E 12
I 12
D 16
		if (error = tsleep((caddr_t)vp, mfs_pri, "mfsidl", 0)) {
I 15
			/*
			 * Give other processes a chance to run.
			 */
			sleep(&lbolt, PVFS);
E 15
			/*
			 * We have received a signal, so try to unmount.
			 */
			(void) dounmount(mp, MNT_NOFORCE);
		}
E 16
I 16
		/*
		 * If a non-ignored signal is received, try to unmount.
		 * If that fails, clear the signal (it has been "processed"),
		 * otherwise we will loop here, as tsleep will always return
		 * EINTR/ERESTART.
		 */
D 49
		if (error = tsleep((caddr_t)vp, mfs_pri, "mfsidl", 0))
D 19
			if (dounmount(mp, MNT_NOFORCE) != 0)
E 19
I 19
D 37
			if (dounmount(mp, MNT_NOFORCE, p) != 0)
E 37
I 37
			if (dounmount(mp, 0, p) != 0)
E 37
E 19
				CLRSIG(p, CURSIG(p));
E 49
I 49
		if (tsleep((caddr_t)vp, mfs_pri, "mfsidl", 0) &&
		    dounmount(mp, 0, p) != 0)
			CLRSIG(p, CURSIG(p));
E 49
E 16
E 12
E 9
E 4
	}
D 12
	return (0);
E 12
I 12
D 49
	return (error);
E 49
I 49
	return (0);
E 49
E 12
I 7
}

/*
 * Get file system statistics.
 */
D 19
mfs_statfs(mp, sbp)
E 19
I 19
mfs_statfs(mp, sbp, p)
E 19
	struct mount *mp;
	struct statfs *sbp;
I 19
	struct proc *p;
E 19
{
	int error;

D 19
	error = ufs_statfs(mp, sbp);
E 19
I 19
D 20
	error = ufs_statfs(mp, sbp, p);
E 20
I 20
	error = ffs_statfs(mp, sbp, p);
E 20
E 19
D 43
	sbp->f_type = MOUNT_MFS;
E 43
I 43
	sbp->f_type = mp->mnt_vfc->vfc_typenum;
E 43
	return (error);
E 7
}
E 1
