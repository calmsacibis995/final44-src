/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ufs_vfsops.c,v $
 * Revision 2.14  91/04/05  14:43:32  mbj
 * 	Set the struct statfs f_type to be MOUNT_UFS, just like Reno.
 * 	[91/03/18            dlc]
 * 	Changed ufs_statfs() to simply copy the fsid from the VFS
 * 	structure ala NFS.  This at least allows programs to tell on what
 * 	type of a file system a file resides.
 * 	[91/03/15            dlc]
 * 	Turned on SMART_FSCK code for clean file systems.
 * 	Mount dirty file systems read-only.  Use uprintf() and say
 * 	which path.
 * 	[91/01/14            berman]
 * 	Changed check in mountfs() to only complain if file system
 * 	is really dirty.  Changed message to indicate that mount happens
 * 	anyway.
 * 	[90/01/04            berman]
 * 
 * 	Added a sleep to ufs_umount if the device was EBUSY. This will
 * 	allow any asychronous inode_uncache_try calls to finish.
 * 	[89/12/18            jsb]
 * 
 * Revision 2.13  91/04/02  12:18:58  mbj
 * 	i386&luna88k: no SMART_FSCK
 * 	[91/03/24            rvb]
 * 
 * Revision 2.12  91/01/23  13:31:18  berman
 * 	Turned on SMART_FSCK code for clean file systems.
 * 	Mount dirty file systems read-only.  Use uprintf() and say 
 * 	which path.
 * 	[91/01/10            berman]
 * 
 * Revision 2.11  90/01/11  14:49:52  berman
 * 	Changed check in mountfs() to only complain if file system
 * 	is really dirty.  Changed message to indicate that mount happens
 * 	anyway.
 * 	Added a sleep to ufs_umount if the device was EBUSY. This will
 * 	allow any asychronous inode_uncache_try calls to finish. [jsb]
 * 
 * Revision 2.10  89/10/10  11:02:05  mwyoung
 * 	Don't worry about clearing the object cache in the unmount
 * 	code here -- it is handled more selectively in iflush() now.
 * 	[89/07/20            mwyoung]
 * 
 * Revision 2.9  89/08/28  22:40:35  af
 * 	Made smart fsck a separate conditional.
 * 	Changed call to sbupdate() into code that only writes
 * 	the superblock, NOT the summary information.
 * 	[89/08/05            af]
 * 
 * Revision 2.8  89/08/02  08:46:47  jsb
 * 	Eliminate MACH conditionals. Replace kallocs with zallocs.
 * 	[89/07/31  15:56:31  jsb]
 * 
 * Revision 2.7  89/07/14  15:29:38  rvb
 * 	Added "root" arg to mountfs for "smart fsck" support.
 * 	[89/07/11            af]
 * 
 * Revision 2.6  89/04/22  15:33:32  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.2  89/01/18  01:23:36  jsb
 * 	Include file references; use kalloc instead of zalloc for vfsp's to
 * 	save mem; comment out vnode_swap_preference in mountfs because we
 * 	haven't added it to inode_pager.c.
 * 	MACH: modify ufs_mount to work with cover_mount hack in vfs_mount.
 * 	[89/01/17  15:46:15  jsb]
 * 
 */

/* @(#)ufs_vfsops.c	1.5 87/07/06 3.2/4.3NFSSRC */
/*	@(#)ufs_vfsops.c 1.1 86/09/25 SMI; from UCB 4.1 83/05/27	*/

#define VAXDEBUG
#ifdef	VAXDEBUG
	extern int vaxdebug;
#endif	VAXDEBUG
#if	!(defined(i386) || defined(luna88k))
#define SMART_FSCK 1
#endif	!(defined(i386) || defined(luna88k))

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/inode.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/conf.h>
#include <sys/fs.h>
#include <sys/mount.h>
#include <vm/vm_kern.h>

#define	mountfs mountvfs

/*
 * ufs vfs operations.
 */
int ufs_mount();
int ufs_unmount();
int ufs_root();
int ufs_statfs();
int ufs_sync();
int ufs_vget();

struct vfsops ufs_vfsops = {
	ufs_mount,
	ufs_unmount,
	ufs_root,
	ufs_statfs,
	ufs_sync,
	ufs_vget,
};

/*
 * this is the default filesystem type.
 * this should be setup by the configurator
 */
extern int ufs_mountroot();
int (*rootfsmount)() = ufs_mountroot;
#ifdef	__GNU__
static int getmdev();
#endif	__GNU__

/*
 * Default device to mount on.
 */
struct vnode *rootvp;

/*
 * Mount table.
 */
struct mount	mount[NMOUNT];

/*
 * ufs_mount system call
 */
ufs_mount(vfsp, path, data)
	struct vfs *vfsp;
	char *path;
	caddr_t data;
{
	int error;
	dev_t dev;
	struct vnode *devvp;
	struct ufs_args args;

	/*
	 * Get arguments
	 */
	args.fspec = (char *) data;
	if ((error = getmdev(args.fspec, &dev)) != 0)
		return (error);
	/*
	 * make a special (device) vnode for the filesystem
	 */
	devvp = (struct vnode *)bdevvp(dev);
	/*
	 * Mount the filesystem.
	 */
	error = mountfs(&devvp, path, vfsp, 0);
	if (error) {
		VN_RELE(devvp);
	}
	return (error);
}

/*
 * Called by vfs_mountroot when ufs is going to be mounted as root
 */
ufs_mountroot()
{
	struct vfs *vfsp;
	register struct fs *fsp;
	register int error;

	ZALLOC(vfs_vfs_zone, vfsp, struct vfs *);
	VFS_INIT(vfsp, &ufs_vfsops, (caddr_t)0);
	if (rootdev != NODEV)
		rootvp = (struct vnode *)bdevvp(rootdev);
	error = mountfs(&rootvp, "/", vfsp, 1);
	if (error) {
		ZFREE(vfs_vfs_zone, vfsp);
		return (error);
	}
	error = vfs_add((struct vnode *)0, vfsp, 0);
	if (error) {
		(void) unmount1(vfsp, 0);
		ZFREE(vfs_vfs_zone, vfsp);
		return (error);
	}
	vfs_unlock(vfsp);
	fsp = ((struct mount *)(vfsp->vfs_data))->m_bufp->b_un.b_fs;
	inittodr(fsp->fs_time);
#ifdef	PMAX
	storemnt( ITYPE_UFS, "/",  "root");
#endif	PMAX
	return (0);
}

int
mountfs(devvpp, path, vfsp, is_root)
	struct vnode **devvpp;
	char *path;
	struct vfs *vfsp;
{
	register struct fs *fsp;
	register struct mount *mp = 0;
	register struct buf *bp = 0;
	struct buf *tp = 0;
	int error;
	int blks;
	caddr_t space;
	int i;
	int size;
	u_int len;

	/*
	 * Open block device mounted on.
	 * When bio is fixed for vnodes this can all be vnode operations
	 */
	error = VOP_OPEN(devvpp,
	    (vfsp->vfs_flag & VFS_RDONLY) ? FREAD : FREAD|FWRITE, u.u_cred);
	if (error)
		return (error);
	/*
	 * read in superblock
	 */

	tp = bread(*devvpp, SBLOCK, SBSIZE);
	if (tp->b_flags & B_ERROR)
		goto out;
	/*
	 * check for dev already mounted on
	 */
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) {
		if (mp->m_bufp != 0 && (*devvpp)->v_rdev == mp->m_dev) {
			mp = 0;
			goto out;
		}
	}
	/*
	 * find empty mount table entry
	 */
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) {
		if (mp->m_bufp == 0)
			goto found;
	}
	mp = 0;
	goto out;
found:
	vfsp->vfs_data = (caddr_t)mp;
	mp->m_vfsp = vfsp;
	mp->m_bufp = tp;	/* just to reserve this slot */
	mp->m_dev = NODEV;
	mp->m_devp = VTOI(*devvpp);
	fsp = tp->b_un.b_fs;
	if (fsp->fs_magic != FS_MAGIC || fsp->fs_bsize > MAXBSIZE)
		goto out;
#if	defined(SMART_FSCK) || defined(PMAX)
	if (fsp->fs_clean != FS_CLEAN && fsp->fs_clean != 1 && !is_root) {
	    uprintf("ufs_mount: file system on %s not clean, mounting read only.\n",path);
	    vfsp->vfs_flag |= VFS_RDONLY;
	}
#endif	defined(SMART_FSCK) || defined(PMAX)
	/*
	 * Copy the super block into a buffer in it's native size.
	 */
	bp = geteblk((int)fsp->fs_sbsize);
	mp->m_bufp = bp;
	bcopy((caddr_t)tp->b_un.b_addr, (caddr_t)bp->b_un.b_addr,
	   (u_int)fsp->fs_sbsize);
	brelse(tp);
	tp = 0;
	fsp = bp->b_un.b_fs;
	if (vfsp->vfs_flag & VFS_RDONLY) {
		fsp->fs_ronly = 1;
	} else {
		fsp->fs_fmod = 1;
		fsp->fs_ronly = 0;
		fsp->fs_clean = 0;	/* mounted writeable ==> dirty */
	}
	vfsp->vfs_bsize = fsp->fs_bsize;
	/*
	 * Read in cyl group info
	 */
	blks = howmany(fsp->fs_cssize, fsp->fs_fsize);
	space = (caddr_t)kalloc(fsp->fs_cssize);
	if (space == 0)
		goto out;
	for (i = 0; i < blks; i += fsp->fs_frag) {
		size = fsp->fs_bsize;
		if (i + fsp->fs_frag > blks)
			size = (blks - i) * fsp->fs_fsize;
		tp = bread(mp->m_devp, (daddr_t)fsbtodb(fsp, fsp->fs_csaddr+i),
		    size);
		if (tp->b_flags&B_ERROR) {
			kfree(space, fsp->fs_cssize);
			goto out;
		}
		bcopy((caddr_t)tp->b_un.b_addr, space, (u_int)size);
		fsp->fs_csp[i / fsp->fs_frag] = (struct csum *)space;
		space += size;
		brelse(tp);
		tp = 0;
	}
	/*
	 *  Enable first file system/inodes full console messages and calculate
	 *  low water pause/high water resume marks for fragments and inodes.
 	 *
	 *  Fragment water marks:
	 *  lo - (1 or minfree)% of total (but <= 100)
	 *  hi - 2* lo (but <= 200)
	 *
	 *  Inode water marks:
	 *  lo/hi - 1% of total (but <= 50)
	 */
	fsp->fs_flags  &= ~(URPW_FNOSPC|URPW_INOSPC);
	FS_FLOWAT(fsp) = ((fsp->fs_dsize * fsp->fs_minfree)/100);
	FS_FHIWAT(fsp) = FS_FLOWAT(fsp);
	if (FS_FHIWAT(fsp) > 100)
		FS_FHIWAT(fsp) += 100;
	else
		FS_FHIWAT(fsp) *= 2;
	FS_ILOWAT(fsp) = ((fsp->fs_ncg * fsp->fs_ipg)/100);
	if (FS_ILOWAT(fsp) > 50)
	    FS_ILOWAT(fsp) = 50;
	FS_IHIWAT(fsp) = FS_ILOWAT(fsp);
#ifdef	DEBUG
	printf("flowat=%d, fhiwat=%d, ilowat=%d, ihiwat=%d\n",
	       FS_FLOWAT(fs), FS_FHIWAT(fs), FS_ILOWAT(fs), FS_IHIWAT(fs));
#endif	DEBUG
	mp->m_dev = ITOV(mp->m_devp)->v_rdev;
	vfsp->vfs_fsid.val[0] = (long)mp->m_dev;
	vfsp->vfs_fsid.val[1] = MOUNT_UFS;
	(void) copystr(path, fsp->fs_fsmnt, sizeof(fsp->fs_fsmnt)-1, &len);
	bzero(fsp->fs_fsmnt + len, sizeof (fsp->fs_fsmnt) - len);
/*	FIXME FIXME
	vnode_swap_preference(mp->m_devp, FALSE, FALSE);
*/
	return (0);
out:
	if (mp)
		mp->m_bufp = 0;
	if (bp)
		brelse(bp);
	if (tp)
		brelse(tp);
	(void) VOP_CLOSE(*devvpp,
	    (vfsp->vfs_flag & VFS_RDONLY) ? FREAD : FREAD|FWRITE, u.u_cred);
	return (EBUSY);
}

/*
 * The System V Interface Definition requires a "umount" operation
 * which takes a device pathname as an argument.  This requires this
 * to be a system call.
 */

umount()
{
	struct a {
		char	*fspec;
	} *uap = (struct a *)u.u_ap;
	register struct mount *mp;
	dev_t dev;

	if (!suser())
		return;

#ifdef	PMAX
	/* Make a guess at what a dev_t looks like,
	   in case this is Ultrix' umount */
	if ((vm_offset_t)uap->fspec < VM_MIN_ADDRESS)
		dev = (dev_t)uap->fspec;
	else
#endif	PMAX
	if ((u.u_error = getmdev(uap->fspec, &dev)) != 0)
		return;

	if ((mp = getmp(dev)) == NULL) {
		u.u_error = EINVAL;
		return;
	}

	dounmount(mp->m_vfsp);
#ifdef	PMAX
	if (u.u_error == 0)
		deletemnt_dev(uap->fspec);
#endif	PMAX
}

/*
 * vfs operations
 */

ufs_unmount(vfsp)
	struct vfs *vfsp;
{
	extern int lbolt;
	int errno;

	errno = unmount1(vfsp, 0);
	if (errno == EBUSY) {
		/*
		 *  Wait at least a second, then try again
		 *  iflush asynchronsly attempts to  uncache inodes
		 *  that only the inode_pager is referencing
		 */
		sleep((caddr_t)&lbolt, PZERO);
		sleep((caddr_t)&lbolt, PZERO);
		errno = unmount1(vfsp, 0);
	}
	return errno;
}

unmount1(vfsp, forcibly)
	register struct vfs *vfsp;
	int forcibly;
{
	dev_t dev;
	register struct mount *mp;
	register struct fs *fs;
	register int stillopen;
	int flag;

	mp = (struct mount *)vfsp->vfs_data;
	dev = mp->m_dev;
#ifdef	QUOTA
	if ((stillopen = iflush(dev, mp->m_qinod)) < 0 && !forcibly)
#else
	if ((stillopen = iflush(dev)) < 0 && !forcibly)
#endif
		return (EBUSY);
	if (stillopen < 0)
		return (EBUSY);			/* XXX */
#ifdef	QUOTA
	(void)closedq(mp);
	/*
	 * Here we have to iflush again to get rid of the quota inode.
	 * A drag, but it would be ugly to cheat, & this doesn't happen often
	 */
	(void)iflush(dev, (struct inode *)NULL);
#endif
	fs = mp->m_bufp->b_un.b_fs;
#if	defined(SMART_FSCK) || defined(PMAX)
	/* mark the file system clean */
	if (!fs->fs_ronly) {
		struct buf *bp;
		/* This does "half" of an sbupdate() */
		bp = getblk(mp->m_devp, SBLOCK, (int)fs->fs_bsize);
		bcopy((caddr_t)fs, bp->b_un.b_addr, (u_int)fs->fs_sbsize);
		bp->b_un.b_fs->fs_flowat = 0;
		bp->b_un.b_fs->fs_fhiwat = 0;
		bp->b_un.b_fs->fs_ilowat = 0;
		bp->b_un.b_fs->fs_ihiwat = 0;
		bp->b_un.b_fs->fs_flags = 0;
		bp->b_un.b_fs->fs_clean = FS_CLEAN;
		bwrite(bp);
	}
#endif	defined(SMART_FSCK) || defined(PMAX)
	kfree(fs->fs_csp[0], fs->fs_cssize);
	flag = !fs->fs_ronly;
	brelse(mp->m_bufp);
	mp->m_bufp = 0;
	mp->m_dev = 0;
	if (!stillopen) {
		(void) VOP_CLOSE(ITOV(mp->m_devp), flag, u.u_cred);
		binval(mp->m_devp);
		VN_RELE(mp->m_devp);
		mp->m_devp = (struct inode *)0;
	}
	return (0);
}

/*
 * find root of ufs
 */
int
ufs_root(vfsp, vpp)
	struct vfs *vfsp;
	struct vnode **vpp;
{
	register struct mount *mp;
	register struct inode *ip;

	mp = (struct mount *)vfsp->vfs_data;
	ip = iget(mp->m_dev, mp->m_bufp->b_un.b_fs, (ino_t)ROOTINO);
	if (ip == (struct inode *)0) {
		return (u.u_error);
	}
	iunlock(ip);
	*vpp = ITOV(ip);
	return (0);
}

/*
 * Get file system statistics.
 */
int
ufs_statfs(vfsp, sbp)
register struct vfs *vfsp;
struct statfs *sbp;
{
	register struct fs *fsp;

	fsp = ((struct mount *)vfsp->vfs_data)->m_bufp->b_un.b_fs;
	if (fsp->fs_magic != FS_MAGIC)
		panic("ufs_statfs");

	/*
	 * Man page says f_type is 0, but let's set it the way Reno does for
	 * application source compatibility
	 */
	sbp->f_type = MOUNT_UFS;
	sbp->f_bsize = fsp->fs_fsize;
	sbp->f_blocks = fsp->fs_dsize;
	sbp->f_bfree =
	    fsp->fs_cstotal.cs_nbfree * fsp->fs_frag +
		fsp->fs_cstotal.cs_nffree;
	/*
	 * avail = MAX(max_avail - used, 0)
	 */
	sbp->f_bavail =
	    (fsp->fs_dsize * (100 - fsp->fs_minfree) / 100) -
		 (fsp->fs_dsize - sbp->f_bfree);
	/*
	 * inodes
	 */
	sbp->f_files =  fsp->fs_ncg * fsp->fs_ipg;
	sbp->f_ffree = fsp->fs_cstotal.cs_nifree;

	/* XXX This should be a real fsid, but this will do for now */
	bcopy((caddr_t)&vfsp->vfs_fsid,
	      (caddr_t)&sbp->f_fsid, sizeof (fsid_t));

	return (0);
}

/*
 * Flush any pending I/O.
 */
int
ufs_sync()
{
	update();
	return (0);
}

sbupdate(mp)
	struct mount *mp;
{
	register struct fs *fs = mp->m_bufp->b_un.b_fs;
	register struct buf *bp;
	int blks;
	caddr_t space;
	int i, size;

	bp = getblk(mp->m_devp, SBLOCK, (int)fs->fs_sbsize);
	bcopy((caddr_t)fs, bp->b_un.b_addr, (u_int)fs->fs_sbsize);
	/*
	 *  These fields are supposed to be zero in 4.2 super-blocks and are
	 *  currently maintained only internally so we can just zero them here
	 *  (in the outgoing copy) for now.  Perhaps someday it will make sense
	 *  to record some of them on disk...
	 */
	bp->b_un.b_fs->fs_flowat = 0;
	bp->b_un.b_fs->fs_fhiwat = 0;
	bp->b_un.b_fs->fs_ilowat = 0;
	bp->b_un.b_fs->fs_ihiwat = 0;
	bp->b_un.b_fs->fs_flags = 0;
	bwrite(bp);
	blks = howmany(fs->fs_cssize, fs->fs_fsize);
	space = (caddr_t)fs->fs_csp[0];
	for (i = 0; i < blks; i += fs->fs_frag) {
		size = fs->fs_bsize;
		if (i + fs->fs_frag > blks)
			size = (blks - i) * fs->fs_fsize;
		bp = getblk(mp->m_devp, (daddr_t)fsbtodb(fs, fs->fs_csaddr+i),
		    size);
		bcopy(space, bp->b_un.b_addr, (u_int)size);
		space += size;
		bwrite(bp);
	}
}

/*
 * Common code for mount and umount.
 * Check that the user's argument is a reasonable
 * thing on which to mount, and return the device number if so.
 */
#ifndef	PMAX
static int
#endif	PMAX
getmdev(fspec, pdev)
	char *fspec;
	dev_t *pdev;
{
	register int error;
	struct vnode *vp;

	/*
	 * Get the device to be mounted
	 */
	error =
	    lookupname(fspec, UIO_USERSPACE, FOLLOW_LINK,
		(struct vnode **)0, &vp);
	if (error)
		return (error);
	if ((vp->v_mode&VFMT) != VBLK) {
		VN_RELE(vp);
		return (ENOTBLK);
	}
	*pdev = vp->v_rdev;
	VN_RELE(vp);
	if (major(*pdev) >= nblkdev)
		return (ENXIO);
	return (0);
}

ufs_vget(vfsp, vpp, fidp)
	struct vfs *vfsp;
	struct vnode **vpp;
	struct fid *fidp;
{
	register struct ufid *ufid;
	register struct inode *ip;
	register struct mount *mp;

	mp = (struct mount *)vfsp->vfs_data;
	ufid = (struct ufid *)fidp;
	ip = iget(mp->m_dev, mp->m_bufp->b_un.b_fs, ufid->ufid_ino);
	if (ip == NULL) {
		*vpp = NULL;
		return (0);
	}
	if (ip->i_gen != ufid->ufid_gen) {
		idrop(ip);
		*vpp = NULL;
		return (0);
	}
	iunlock(ip);
	*vpp = ITOV(ip);
	return (0);
}
