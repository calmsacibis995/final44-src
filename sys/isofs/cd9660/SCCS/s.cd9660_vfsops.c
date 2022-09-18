h47534
s 00002/00003/00772
d D 8.18 95/05/22 23:03:46 mckusick 19 18
c simpler checkalias protocol
e
s 00004/00007/00771
d D 8.17 95/05/20 01:24:29 mckusick 18 17
c merge vfs_lock and vfs_busy; interlock mount points properly
e
s 00004/00002/00774
d D 8.16 95/05/14 00:35:35 mckusick 17 16
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00005/00002/00771
d D 8.15 95/05/10 13:19:03 mckusick 16 15
c mountroot should fail, not panic
e
s 00006/00021/00767
d D 8.14 95/05/10 11:58:00 mckusick 15 14
c use vfs_rootmountalloc
e
s 00008/00013/00780
d D 8.13 95/05/10 10:55:10 mckusick 14 13
c cleanups (from mycroft)
e
s 00001/00007/00792
d D 8.12 95/05/10 09:53:14 mckusick 13 12
c check for forcible unmount at syscall level
e
s 00001/00001/00798
d D 8.11 95/05/09 12:14:37 mckusick 12 11
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00003/00001/00796
d D 8.10 95/03/30 14:25:45 mckusick 11 10
c add cd9660_sysctl; MOUNT_CD9660 goes away
e
s 00001/00004/00796
d D 8.9 94/12/05 22:37:35 mckusick 10 8
c changes from version set by mycroft
e
s 00000/00003/00797
d R 8.9 94/12/05 22:25:06 mckusick 9 8
c things from mycroft that don't match
e
s 00025/00019/00775
d D 8.8 94/12/05 21:56:59 mckusick 8 7
c update from mycroft
e
s 00004/00001/00790
d D 8.7 94/11/30 10:45:26 mckusick 7 6
c uninitialized variable (from ralph)
e
s 00050/00045/00741
d D 8.6 94/07/24 22:39:45 mckusick 6 5
c more bugfixes from mycroft
e
s 00219/00086/00567
d D 8.5 94/07/13 16:41:26 mckusick 5 4
c update for 4.4BSD-Lite (from mycroft)
e
s 00005/00007/00648
d D 8.4 94/06/14 12:00:15 mkm 4 3
c have to init vfs list; use ufs doforce flag; formatting
c (from Wolfgang Solfrank via mycroft)
e
s 00002/00001/00653
d D 8.3 94/01/31 20:43:15 hibler 3 2
c zero the iso_mount struct after allocation
e
s 00032/00032/00622
d D 8.2 94/01/23 23:50:54 mckusick 2 1
c isofs => cd9660 naming convention
e
s 00654/00000/00000
d D 8.1 94/01/21 18:29:00 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <miscfs/specfs/specdev.h>
#include <sys/mount.h>
#include <sys/buf.h>
#include <sys/file.h>
#include <sys/dkbad.h>
#include <sys/disklabel.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/malloc.h>
I 5
#include <sys/stat.h>
E 5

#include <isofs/cd9660/iso.h>
D 2
#include <isofs/cd9660/isofs_node.h>
E 2
I 2
#include <isofs/cd9660/cd9660_node.h>
I 11
#include <isofs/cd9660/cd9660_mount.h>
E 11
E 2

extern int enodev ();

D 2
struct vfsops isofs_vfsops = {
	isofs_mount,
	isofs_start,
	isofs_unmount,
	isofs_root,
	isofs_quotactl,
	isofs_statfs,
	isofs_sync,
	isofs_vget,
	isofs_fhtovp,
	isofs_vptofh,
	isofs_init,
E 2
I 2
struct vfsops cd9660_vfsops = {
I 8
D 10
	MOUNT_CD9660,
E 10
E 8
	cd9660_mount,
	cd9660_start,
	cd9660_unmount,
	cd9660_root,
	cd9660_quotactl,
	cd9660_statfs,
	cd9660_sync,
	cd9660_vget,
	cd9660_fhtovp,
	cd9660_vptofh,
	cd9660_init,
I 11
	cd9660_sysctl
E 11
E 2
};

/*
 * Called by vfs_mountroot when iso is going to be mounted as root.
D 15
 *
 * Name is updated by mount(8) after booting.
E 15
 */
D 15
#define ROOTNAME	"root_device"
E 15

static iso_mountfs();

D 2
isofs_mountroot()
E 2
I 2
cd9660_mountroot()
E 2
{
D 15
	register struct mount *mp;
E 15
I 15
	struct mount *mp;
E 15
	extern struct vnode *rootvp;
	struct proc *p = curproc;	/* XXX */
D 15
	struct iso_mnt *imp;
	register struct fs *fs;
	u_int size;
	int error;
E 15
	struct iso_args args;
I 15
	int error;
E 15
	
	/*
	 * Get vnodes for swapdev and rootdev.
	 */
D 16
	if (bdevvp(swapdev, &swapdev_vp) || bdevvp(rootdev, &rootvp))
D 2
		panic("isofs_mountroot: can't setup bdevvp's");
E 2
I 2
		panic("cd9660_mountroot: can't setup bdevvp's");
E 16
I 16
	if ((error = bdevvp(swapdev, &swapdev_vp)) ||
	    (error = bdevvp(rootdev, &rootvp))) {
		printf("cd9660_mountroot: can't setup bdevvp's");
		return (error);
	}
E 16
E 2

D 15
	mp = malloc((u_long)sizeof(struct mount), M_MOUNT, M_WAITOK);
	bzero((char *)mp, (u_long)sizeof(struct mount));
D 2
	mp->mnt_op = &isofs_vfsops;
E 2
I 2
	mp->mnt_op = &cd9660_vfsops;
E 2
	mp->mnt_flag = MNT_RDONLY;
I 4
	LIST_INIT(&mp->mnt_vnodelist);
E 15
I 15
	if (error = vfs_rootmountalloc("cd9660", "root_device", &mp))
		return (error);
E 15
E 4
	args.flags = ISOFSMNT_ROOT;
	if (error = iso_mountfs(rootvp, mp, p, &args)) {
I 15
		mp->mnt_vfc->vfc_refcount--;
I 18
		vfs_unbusy(mp, p);
E 18
E 15
		free(mp, M_MOUNT);
		return (error);
	}
D 18
	if (error = vfs_lock(mp)) {
D 2
		(void)isofs_unmount(mp, 0, p);
E 2
I 2
		(void)cd9660_unmount(mp, 0, p);
I 15
		mp->mnt_vfc->vfc_refcount--;
E 15
E 2
		free(mp, M_MOUNT);
		return (error);
	}
E 18
I 18
	simple_lock(&mountlist_slock);
E 18
D 12
	TAILQ_INSERT_TAIL(&mountlist, mp, mnt_list);
E 12
I 12
	CIRCLEQ_INSERT_TAIL(&mountlist, mp, mnt_list);
I 18
	simple_unlock(&mountlist_slock);
E 18
E 12
D 13
	mp->mnt_flag |= MNT_ROOTFS;
E 13
D 15
	mp->mnt_vnodecovered = NULLVP;
	imp = VFSTOISOFS(mp);
D 14
	bzero(imp->im_fsmnt, sizeof(imp->im_fsmnt));
	imp->im_fsmnt[0] = '/';
	bcopy((caddr_t)imp->im_fsmnt, (caddr_t)mp->mnt_stat.f_mntonname,
	    MNAMELEN);
E 14
I 14
	(void) copystr("/", mp->mnt_stat.f_mntonname, MNAMELEN - 1,
	    &size);
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);
E 14
	(void) copystr(ROOTNAME, mp->mnt_stat.f_mntfromname, MNAMELEN - 1,
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
E 15
D 2
	(void) isofs_statfs(mp, &mp->mnt_stat, p);
E 2
I 2
D 14
	(void) cd9660_statfs(mp, &mp->mnt_stat, p);
E 14
I 14
	(void)cd9660_statfs(mp, &mp->mnt_stat, p);
E 14
E 2
D 18
	vfs_unlock(mp);
E 18
I 18
	vfs_unbusy(mp, p);
E 18
	return (0);
}

/*
D 4
 * Flag to allow forcible unmounting.
 */
int iso_doforce = 1;

/*
E 4
 * VFS Operations.
 *
 * mount system call
 */
D 2
isofs_mount(mp, path, data, ndp, p)
E 2
I 2
cd9660_mount(mp, path, data, ndp, p)
E 2
	register struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
	struct vnode *devvp;
	struct iso_args args;
	u_int size;
	int error;
	struct iso_mnt *imp;
	
	if (error = copyin(data, (caddr_t)&args, sizeof (struct iso_args)))
		return (error);
	
	if ((mp->mnt_flag & MNT_RDONLY) == 0)
		return (EROFS);
	
	/*
	 * If updating, check whether changing from read-only to
	 * read/write; if there is no device name, that's all we do.
	 */
	if (mp->mnt_flag & MNT_UPDATE) {
		imp = VFSTOISOFS(mp);
		if (args.fspec == 0)
			return (vfs_export(mp, &imp->im_export, &args.export));
	}
	/*
	 * Not an update, or updating the name: look up the name
	 * and verify that it refers to a sensible block device.
	 */
	NDINIT(ndp, LOOKUP, FOLLOW, UIO_USERSPACE, args.fspec, p);
	if (error = namei(ndp))
		return (error);
	devvp = ndp->ni_vp;

	if (devvp->v_type != VBLK) {
		vrele(devvp);
		return ENOTBLK;
	}
	if (major(devvp->v_rdev) >= nblkdev) {
		vrele(devvp);
		return ENXIO;
	}
	if ((mp->mnt_flag & MNT_UPDATE) == 0)
		error = iso_mountfs(devvp, mp, p, &args);
	else {
		if (devvp != imp->im_devvp)
			error = EINVAL;	/* needs translation */
		else
			vrele(devvp);
	}
	if (error) {
		vrele(devvp);
		return error;
	}
	imp = VFSTOISOFS(mp);
D 14
	(void) copyinstr(path, imp->im_fsmnt, sizeof(imp->im_fsmnt)-1, &size);
	bzero(imp->im_fsmnt + size, sizeof(imp->im_fsmnt) - size);
	bcopy((caddr_t)imp->im_fsmnt, (caddr_t)mp->mnt_stat.f_mntonname,
	    MNAMELEN);
E 14
I 14
	(void) copyinstr(path, mp->mnt_stat.f_mntonname, MNAMELEN - 1, &size);
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);
E 14
	(void) copyinstr(args.fspec, mp->mnt_stat.f_mntfromname, MNAMELEN - 1,
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
D 2
	(void) isofs_statfs(mp, &mp->mnt_stat, p);
E 2
I 2
	(void) cd9660_statfs(mp, &mp->mnt_stat, p);
E 2
	return 0;
}

/*
 * Common code for mount and mountroot
 */
static iso_mountfs(devvp, mp, p, argp)
	register struct vnode *devvp;
	struct mount *mp;
	struct proc *p;
	struct iso_args *argp;
{
	register struct iso_mnt *isomp = (struct iso_mnt *)0;
	struct buf *bp = NULL;
	dev_t dev = devvp->v_rdev;
	caddr_t base, space;
	int havepart = 0, blks;
	int error = EINVAL, i, size;
	int needclose = 0;
	int ronly = (mp->mnt_flag & MNT_RDONLY) != 0;
	extern struct vnode *rootvp;
	int j;
	int iso_bsize;
	int iso_blknum;
	struct iso_volume_descriptor *vdp;
	struct iso_primary_descriptor *pri;
	struct iso_directory_record *rootp;
	int logical_block_size;
	
	if (!ronly)
		return EROFS;
	
	/*
	 * Disallow multiple mounts of the same device.
	 * Disallow mounting of a device that is currently in use
	 * (except for root, which might share swap device for miniroot).
	 * Flush out any old buffers remaining from a previous use.
	 */
	if (error = vfs_mountedon(devvp))
		return error;
	if (vcount(devvp) > 1 && devvp != rootvp)
		return EBUSY;
	if (error = vinvalbuf(devvp, V_SAVE, p->p_ucred, p, 0, 0))
		return (error);

	if (error = VOP_OPEN(devvp, ronly ? FREAD : FREAD|FWRITE, FSCRED, p))
		return error;
	needclose = 1;
	
	/* This is the "logical sector size".  The standard says this
	 * should be 2048 or the physical sector size on the device,
	 * whichever is greater.  For now, we'll just use a constant.
	 */
	iso_bsize = ISO_DEFAULT_BLOCK_SIZE;
	
	for (iso_blknum = 16; iso_blknum < 100; iso_blknum++) {
D 8
		if (error = bread (devvp, btodb(iso_blknum * iso_bsize),
				   iso_bsize, NOCRED, &bp))
E 8
I 8
		if (error = bread(devvp, iso_blknum * btodb(iso_bsize),
				  iso_bsize, NOCRED, &bp))
E 8
			goto out;
		
D 8
		vdp = (struct iso_volume_descriptor *)bp->b_un.b_addr;
E 8
I 8
		vdp = (struct iso_volume_descriptor *)bp->b_data;
E 8
		if (bcmp (vdp->id, ISO_STANDARD_ID, sizeof vdp->id) != 0) {
			error = EINVAL;
			goto out;
		}
		
		if (isonum_711 (vdp->type) == ISO_VD_END) {
			error = EINVAL;
			goto out;
		}
		
		if (isonum_711 (vdp->type) == ISO_VD_PRIMARY)
			break;
		brelse(bp);
	}
	
	if (isonum_711 (vdp->type) != ISO_VD_PRIMARY) {
		error = EINVAL;
		goto out;
	}
	
	pri = (struct iso_primary_descriptor *)vdp;
	
	logical_block_size = isonum_723 (pri->logical_block_size);
	
	if (logical_block_size < DEV_BSIZE || logical_block_size > MAXBSIZE
	    || (logical_block_size & (logical_block_size - 1)) != 0) {
		error = EINVAL;
		goto out;
	}
	
	rootp = (struct iso_directory_record *)pri->root_directory_record;
	
D 3
	isomp = (struct iso_mnt *)malloc(sizeof *isomp,M_ISOFSMNT,M_WAITOK);
E 3
I 3
	isomp = malloc(sizeof *isomp, M_ISOFSMNT, M_WAITOK);
	bzero((caddr_t)isomp, sizeof *isomp);
E 3
	isomp->logical_block_size = logical_block_size;
	isomp->volume_space_size = isonum_733 (pri->volume_space_size);
	bcopy (rootp, isomp->root, sizeof isomp->root);
	isomp->root_extent = isonum_733 (rootp->extent);
	isomp->root_size = isonum_733 (rootp->size);
	
	isomp->im_bmask = logical_block_size - 1;
	isomp->im_bshift = 0;
	while ((1 << isomp->im_bshift) < isomp->logical_block_size)
		isomp->im_bshift++;
	
	bp->b_flags |= B_AGE;
	brelse(bp);
	bp = NULL;
	
	mp->mnt_data = (qaddr_t)isomp;
	mp->mnt_stat.f_fsid.val[0] = (long)dev;
D 2
	mp->mnt_stat.f_fsid.val[1] = MOUNT_ISOFS;
E 2
I 2
D 8
	mp->mnt_stat.f_fsid.val[1] = MOUNT_CD9660;
E 8
I 8
D 10
	mp->mnt_stat.f_fsid.val[1] = makefstype(MOUNT_CD9660);
E 10
I 10
D 11
	mp->mnt_stat.f_fsid.val[1] = MOUNT_CD9660;
E 11
I 11
	mp->mnt_stat.f_fsid.val[1] = mp->mnt_vfc->vfc_typenum;
E 11
E 10
E 8
E 2
	mp->mnt_maxsymlinklen = 0;
	mp->mnt_flag |= MNT_LOCAL;
	isomp->im_mountp = mp;
	isomp->im_dev = dev;
	isomp->im_devvp = devvp;
	
	devvp->v_specflags |= SI_MOUNTEDON;
	
	/* Check the Rock Ridge Extention support */
	if (!(argp->flags & ISOFSMNT_NORRIP)) {
D 8
		if (error = bread (isomp->im_devvp,
				   (isomp->root_extent + isonum_711(rootp->ext_attr_length))
				   * isomp->logical_block_size / DEV_BSIZE,
				   isomp->logical_block_size,NOCRED,&bp))
E 8
I 8
		if (error = bread(isomp->im_devvp,
				  (isomp->root_extent + isonum_711(rootp->ext_attr_length)) <<
				  (isomp->im_bshift - DEV_BSHIFT),
				  isomp->logical_block_size, NOCRED, &bp))
E 8
		    goto out;
		
D 8
		rootp = (struct iso_directory_record *)bp->b_un.b_addr;
E 8
I 8
		rootp = (struct iso_directory_record *)bp->b_data;
E 8
		
D 2
		if ((isomp->rr_skip = isofs_rrip_offset(rootp,isomp)) < 0) {
E 2
I 2
		if ((isomp->rr_skip = cd9660_rrip_offset(rootp,isomp)) < 0) {
E 2
		    argp->flags  |= ISOFSMNT_NORRIP;
		} else {
		    argp->flags  &= ~ISOFSMNT_GENS;
		}
		
		/*
		 * The contents are valid,
		 * but they will get reread as part of another vnode, so...
		 */
		bp->b_flags |= B_AGE;
		brelse(bp);
		bp = NULL;
	}
	isomp->im_flags = argp->flags&(ISOFSMNT_NORRIP|ISOFSMNT_GENS|ISOFSMNT_EXTATT);
	switch (isomp->im_flags&(ISOFSMNT_NORRIP|ISOFSMNT_GENS)) {
	default:
	    isomp->iso_ftype = ISO_FTYPE_DEFAULT;
	    break;
	case ISOFSMNT_GENS|ISOFSMNT_NORRIP:
	    isomp->iso_ftype = ISO_FTYPE_9660;
	    break;
	case 0:
	    isomp->iso_ftype = ISO_FTYPE_RRIP;
	    break;
	}
	
	return 0;
out:
	if (bp)
		brelse(bp);
	if (needclose)
		(void)VOP_CLOSE(devvp, ronly ? FREAD : FREAD|FWRITE, NOCRED, p);
	if (isomp) {
		free((caddr_t)isomp, M_ISOFSMNT);
		mp->mnt_data = (qaddr_t)0;
	}
	return error;
}

/*
 * Make a filesystem operational.
 * Nothing to do at the moment.
 */
/* ARGSUSED */
D 2
isofs_start(mp, flags, p)
E 2
I 2
cd9660_start(mp, flags, p)
E 2
	struct mount *mp;
	int flags;
	struct proc *p;
{
	return 0;
}

/*
 * unmount system call
 */
int
D 2
isofs_unmount(mp, mntflags, p)
E 2
I 2
cd9660_unmount(mp, mntflags, p)
E 2
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
	register struct iso_mnt *isomp;
	int i, error, ronly, flags = 0;
	
D 13
	if (mntflags & MNT_FORCE) {
D 4
		if (!iso_doforce || (mp->mnt_flag & MNT_ROOTFS))
E 4
I 4
		extern int doforce;

		if (!doforce || (mp->mnt_flag & MNT_ROOTFS))
E 4
			return (EINVAL);
E 13
I 13
	if (mntflags & MNT_FORCE)
E 13
		flags |= FORCECLOSE;
D 13
	}
E 13
#if 0
	mntflushbuf(mp, 0);
	if (mntinvalbuf(mp))
		return EBUSY;
#endif
	if (error = vflush(mp, NULLVP, flags))
		return (error);

	isomp = VFSTOISOFS(mp);

#ifdef	ISODEVMAP
	if (isomp->iso_ftype == ISO_FTYPE_RRIP)
		iso_dunmap(isomp->im_dev);
#endif
	
	isomp->im_devvp->v_specflags &= ~SI_MOUNTEDON;
	error = VOP_CLOSE(isomp->im_devvp, FREAD, NOCRED, p);
	vrele(isomp->im_devvp);
	free((caddr_t)isomp, M_ISOFSMNT);
	mp->mnt_data = (qaddr_t)0;
	mp->mnt_flag &= ~MNT_LOCAL;
	return (error);
}

/*
 * Return root of a filesystem
 */
D 2
isofs_root(mp, vpp)
E 2
I 2
cd9660_root(mp, vpp)
E 2
	struct mount *mp;
	struct vnode **vpp;
{
D 5
	register struct iso_node *ip;
	struct iso_node tip, *nip;
	struct vnode tvp;
E 5
I 5
	struct iso_mnt *imp = VFSTOISOFS(mp);
D 6
	ino_t inum;
	struct vnode *nvp;
E 5
	int error;
E 6
I 6
	struct iso_directory_record *dp =
	    (struct iso_directory_record *)imp->root;
D 8
	ino_t ino;
E 8
I 8
	ino_t ino = isodirino(dp, imp);
E 8
E 6
D 5
	struct iso_mnt *imp = VFSTOISOFS (mp);
	struct iso_directory_record *dp;
E 5
	
D 5
	tvp.v_mount = mp;
	tvp.v_data = &tip;
	ip = VTOI(&tvp);
	ip->i_vnode = &tvp;
	ip->i_dev = imp->im_dev;
	ip->i_diroff = 0;
	dp = (struct iso_directory_record *)imp->root;
	isodirino(&ip->i_number,dp,imp);
E 5
I 5
D 6
	isodirino(&inum, imp->root, imp);
E 6
I 6
D 8
	isodirino(&ino, dp, imp);
E 6
E 5
	
E 8
	/*
	 * With RRIP we must use the `.' entry of the root directory.
D 6
	 * Simply tell iget, that it's a relocated directory.
E 6
I 6
	 * Simply tell vget, that it's a relocated directory.
E 6
	 */
D 5
	error = iso_iget(ip,ip->i_number,
			 imp->iso_ftype == ISO_FTYPE_RRIP,
			 &nip,dp);
	if (error)
		return error;
	*vpp = ITOV(nip);
	return 0;
E 5
I 5
D 6
	if (error = VFS_VGET(mp, inum, &nvp))
		return (error);
	*vpp = nvp;
	return (0);
E 6
I 6
	return (cd9660_vget_internal(mp, ino, vpp,
	    imp->iso_ftype == ISO_FTYPE_RRIP, dp));
E 6
E 5
}

/*
 * Do operations associated with quotas, not supported
 */
/* ARGSUSED */
int
D 2
isofs_quotactl(mp, cmd, uid, arg, p)
E 2
I 2
cd9660_quotactl(mp, cmd, uid, arg, p)
E 2
	struct mount *mp;
	int cmd;
	uid_t uid;
	caddr_t arg;
	struct proc *p;
{

	return (EOPNOTSUPP);
}

/*
 * Get file system statistics.
 */
D 2
isofs_statfs(mp, sbp, p)
E 2
I 2
cd9660_statfs(mp, sbp, p)
E 2
	struct mount *mp;
	register struct statfs *sbp;
	struct proc *p;
{
	register struct iso_mnt *isomp;
	register struct fs *fs;
	
	isomp = VFSTOISOFS(mp);
D 4
	
E 4
I 4

E 4
D 2
	sbp->f_type = MOUNT_ISOFS;
E 2
I 2
D 8
	sbp->f_type = MOUNT_CD9660;
E 8
I 8
#ifdef COMPAT_09
	sbp->f_type = 5;
#else
	sbp->f_type = 0;
#endif
E 8
E 2
	sbp->f_bsize = isomp->logical_block_size;
	sbp->f_iosize = sbp->f_bsize;	/* XXX */
	sbp->f_blocks = isomp->volume_space_size;
	sbp->f_bfree = 0; /* total free blocks */
	sbp->f_bavail = 0; /* blocks free for non superuser */
	sbp->f_files =  0; /* total files */
	sbp->f_ffree = 0; /* free file nodes */
	if (sbp != &mp->mnt_stat) {
D 14
		bcopy((caddr_t)mp->mnt_stat.f_mntonname,
			(caddr_t)&sbp->f_mntonname[0], MNAMELEN);
		bcopy((caddr_t)mp->mnt_stat.f_mntfromname,
			(caddr_t)&sbp->f_mntfromname[0], MNAMELEN);
E 14
I 14
		bcopy(mp->mnt_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->mnt_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
E 14
	}
I 8
D 10
	strncpy(&sbp->f_fstypename[0], mp->mnt_op->vfs_name, MFSNAMELEN);
	sbp->f_fstypename[MFSNAMELEN] = '\0';
E 10
E 8
	/* Use the first spare for flags: */
	sbp->f_spare[0] = isomp->im_flags;
	return 0;
}

/* ARGSUSED */
int
D 2
isofs_sync(mp, waitfor, cred, p)
E 2
I 2
cd9660_sync(mp, waitfor, cred, p)
E 2
	struct mount *mp;
	int waitfor;
	struct ucred *cred;
	struct proc *p;
{
	return (0);
}

/*
D 5
 * Flat namespace lookup.
 * Currently unsupported.
 */
/* ARGSUSED */
int
D 2
isofs_vget(mp, ino, vpp)
E 2
I 2
cd9660_vget(mp, ino, vpp)
E 2
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{

	return (EOPNOTSUPP);
}

/*
E 5
 * File handle to vnode
 *
 * Have to be really careful about stale file handles:
 * - check that the inode number is in range
 * - call iget() to get the locked inode
 * - check for an unallocated inode (i_mode == 0)
 * - check that the generation number matches
 */

struct ifid {
	ushort	ifid_len;
	ushort	ifid_pad;
	int	ifid_ino;
	long	ifid_start;
};

/* ARGSUSED */
int
D 2
isofs_fhtovp(mp, fhp, nam, vpp, exflagsp, credanonp)
E 2
I 2
cd9660_fhtovp(mp, fhp, nam, vpp, exflagsp, credanonp)
E 2
	register struct mount *mp;
	struct fid *fhp;
	struct mbuf *nam;
	struct vnode **vpp;
	int *exflagsp;
	struct ucred **credanonp;
{
D 5
	struct vnode			tvp;
	int				error;
	int				lbn, off;
	struct ifid			*ifhp;
	struct iso_mnt			*imp;
	struct buf			*bp;
	struct iso_directory_record	*dirp;
	struct iso_node 		tip, *ip, *nip;
	struct netcred			*np;
E 5
I 5
	struct ifid *ifhp = (struct ifid *)fhp;
	register struct iso_node *ip;
	register struct netcred *np;
	register struct iso_mnt *imp = VFSTOISOFS(mp);
	struct vnode *nvp;
	int error;
E 5
	
D 5
	imp = VFSTOISOFS (mp);
	ifhp = (struct ifid *)fhp;
	
E 5
#ifdef	ISOFS_DBG
	printf("fhtovp: ino %d, start %ld\n",
	       ifhp->ifid_ino, ifhp->ifid_start);
#endif
	
I 5
	/*
	 * Get the export permission structure for this <mp, client> tuple.
	 */
E 5
	np = vfs_export_lookup(mp, &imp->im_export, nam);
	if (np == NULL)
		return (EACCES);

D 5
	lbn = iso_lblkno(imp, ifhp->ifid_ino);
E 5
I 5
	if (error = VFS_VGET(mp, ifhp->ifid_ino, &nvp)) {
		*vpp = NULLVP;
		return (error);
	}
	ip = VTOI(nvp);
	if (ip->inode.iso_mode == 0) {
		vput(nvp);
		*vpp = NULLVP;
		return (ESTALE);
	}
	*vpp = nvp;
	*exflagsp = np->netc_exflags;
	*credanonp = &np->netc_anon;
	return (0);
}

int
cd9660_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{

	/*
	 * XXXX
	 * It would be nice if we didn't always set the `relocated' flag
	 * and force the extra read, but I don't want to think about fixing
	 * that right now.
	 */
	return (cd9660_vget_internal(mp, ino, vpp,
I 6
#if 0
E 6
	    VFSTOISOFS(mp)->iso_ftype == ISO_FTYPE_RRIP,
I 6
#else
	    0,
#endif
E 6
	    (struct iso_directory_entry *)0));
}

int
cd9660_vget_internal(mp, ino, vpp, relocated, isodir)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
	int relocated;
	struct iso_directory_record *isodir;
{
D 17
	register struct iso_mnt *imp;
E 17
I 17
	struct proc *p = curproc;	/* XXX */
	struct iso_mnt *imp;
E 17
	struct iso_node *ip;
	struct buf *bp;
	struct vnode *vp, *nvp;
D 6
	int lbn, off;
E 6
	dev_t dev;
	int error;

	imp = VFSTOISOFS(mp);
	dev = imp->im_dev;
	if ((*vpp = cd9660_ihashget(dev, ino)) != NULLVP)
		return (0);

	/* Allocate a new vnode/iso_node. */
	if (error = getnewvnode(VT_ISOFS, mp, cd9660_vnodeop_p, &vp)) {
		*vpp = NULLVP;
		return (error);
	}
	MALLOC(ip, struct iso_node *, sizeof(struct iso_node), M_ISOFSNODE,
	    M_WAITOK);
	bzero((caddr_t)ip, sizeof(struct iso_node));
I 17
	lockinit(&ip->i_lock, PINOD, "isonode", 0, 0);
E 17
	vp->v_data = ip;
	ip->i_vnode = vp;
	ip->i_dev = dev;
	ip->i_number = ino;

	/*
	 * Put it onto its hash chain and lock it so that other requests for
	 * this inode will block if they arrive while we are sleeping waiting
	 * for old data structures to be purged or for the contents of the
	 * disk portion of this inode to be read.
	 */
	cd9660_ihashins(ip);

D 6
	lbn = iso_lblkno(imp, ino);
E 5
	if (lbn >= imp->volume_space_size) {
I 5
		vput(vp);
E 5
		printf("fhtovp: lbn exceed volume space %d\n", lbn);
		return (ESTALE);
	}
E 6
I 6
	if (isodir == 0) {
		int lbn, off;

D 8
		lbn = iso_lblkno(imp, ino);
E 8
I 8
		lbn = lblkno(imp, ino);
E 8
		if (lbn >= imp->volume_space_size) {
			vput(vp);
			printf("fhtovp: lbn exceed volume space %d\n", lbn);
			return (ESTALE);
		}
E 6
	
D 5
	off = iso_blkoff(imp, ifhp->ifid_ino);
E 5
I 5
D 6
	off = iso_blkoff(imp, ino);
E 5
	if (off + ISO_DIRECTORY_RECORD_SIZE > imp->logical_block_size) {
I 5
		vput(vp);
E 5
		printf("fhtovp: crosses block boundary %d\n",
		       off + ISO_DIRECTORY_RECORD_SIZE);
		return (ESTALE);
	}
E 6
I 6
D 8
		off = iso_blkoff(imp, ino);
E 8
I 8
		off = blkoff(imp, ino);
E 8
		if (off + ISO_DIRECTORY_RECORD_SIZE > imp->logical_block_size) {
			vput(vp);
			printf("fhtovp: crosses block boundary %d\n",
			       off + ISO_DIRECTORY_RECORD_SIZE);
			return (ESTALE);
		}
E 6
	
D 5
	error = bread(imp->im_devvp, btodb(lbn * imp->logical_block_size),
		      imp->logical_block_size, NOCRED, &bp);
	if (error) {
		printf("fhtovp: bread error %d\n",error);
		brelse(bp);
		return (error);
	}
	
	dirp = (struct iso_directory_record *)(bp->b_un.b_addr + off);
	if (off + isonum_711(dirp->length) > imp->logical_block_size) {
		brelse(bp);
E 5
I 5
D 6
	if (isodir == 0) {
		error = bread(imp->im_devvp, btodb(lbn * imp->logical_block_size),
E 6
I 6
		error = bread(imp->im_devvp,
D 8
			      btodb(lbn * imp->logical_block_size),
E 8
I 8
			      lbn << (imp->im_bshift - DEV_BSHIFT),
E 8
E 6
			      imp->logical_block_size, NOCRED, &bp);
		if (error) {
			vput(vp);
			brelse(bp);
			printf("fhtovp: bread error %d\n",error);
			return (error);
		}
		isodir = (struct iso_directory_record *)(bp->b_data + off);
D 6
	} else
		bp = 0;
E 6

D 6
	if (off + isonum_711(isodir->length) > imp->logical_block_size) {
		vput(vp);
		if (bp != 0)
			brelse(bp);
E 5
		printf("fhtovp: directory crosses block boundary %d[off=%d/len=%d]\n",
D 5
		       off+isonum_711(dirp->length), off,
		       isonum_711(dirp->length));
E 5
I 5
		       off +isonum_711(isodir->length), off,
		       isonum_711(isodir->length));
E 5
		return (ESTALE);
	}
E 6
I 6
		if (off + isonum_711(isodir->length) >
		    imp->logical_block_size) {
			vput(vp);
			if (bp != 0)
				brelse(bp);
			printf("fhtovp: directory crosses block boundary %d[off=%d/len=%d]\n",
			       off +isonum_711(isodir->length), off,
			       isonum_711(isodir->length));
			return (ESTALE);
		}
E 6
	
D 5
	if (isonum_733(dirp->extent) + isonum_711(dirp->ext_attr_length) !=
E 5
I 5
#if 0
D 6
	if (isonum_733(isodir->extent) + isonum_711(isodir->ext_attr_length) !=
E 5
	    ifhp->ifid_start) {
D 5
		brelse(bp);
E 5
I 5
		if (bp != 0)
			brelse(bp);
E 5
		printf("fhtovp: file start miss %d vs %d\n",
D 5
		       isonum_733(dirp->extent)+isonum_711(dirp->ext_attr_length),
E 5
I 5
		       isonum_733(isodir->extent) + isonum_711(isodir->ext_attr_length),
E 5
		       ifhp->ifid_start);
		return (ESTALE);
	}
E 6
I 6
		if (isonum_733(isodir->extent) +
		    isonum_711(isodir->ext_attr_length) != ifhp->ifid_start) {
			if (bp != 0)
				brelse(bp);
			printf("fhtovp: file start miss %d vs %d\n",
			       isonum_733(isodir->extent) + isonum_711(isodir->ext_attr_length),
			       ifhp->ifid_start);
			return (ESTALE);
		}
E 6
D 5
	brelse(bp);
E 5
I 5
#endif
I 6
	} else
		bp = 0;
E 6

	ip->i_mnt = imp;
	ip->i_devvp = imp->im_devvp;
	VREF(ip->i_devvp);

	if (relocated) {
		/*
		 * On relocated directories we must
		 * read the `.' entry out of a dir.
		 */
		ip->iso_start = ino >> imp->im_bshift;
		if (bp != 0)
			brelse(bp);
D 8
		if (error = iso_blkatoff(ip, 0, &bp)) {
E 8
I 8
		if (error = VOP_BLKATOFF(vp, (off_t)0, NULL, &bp)) {
E 8
			vput(vp);
			return (error);
		}
		isodir = (struct iso_directory_record *)bp->b_data;
	}

	ip->iso_extent = isonum_733(isodir->extent);
	ip->i_size = isonum_733(isodir->size);
	ip->iso_start = isonum_711(isodir->ext_attr_length) + ip->iso_extent;
E 5
	
D 5
	ip = &tip;
	tvp.v_mount = mp;
	tvp.v_data = ip;
	ip->i_vnode = &tvp;
	ip->i_dev = imp->im_dev;
	if (error = iso_iget(ip, ifhp->ifid_ino, 0, &nip, dirp)) {
		*vpp = NULLVP;
		printf("fhtovp: failed to get inode\n");
		return (error);
E 5
I 5
	/*
	 * Setup time stamp, attribute
	 */
	vp->v_type = VNON;
	switch (imp->iso_ftype) {
	default:	/* ISO_FTYPE_9660 */
	    {
		struct buf *bp2;
I 8
		int off;
E 8
		if ((imp->im_flags & ISOFSMNT_EXTATT)
D 8
		    && isonum_711(isodir->ext_attr_length))
			iso_blkatoff(ip, -isonum_711(isodir->ext_attr_length),
E 8
I 8
		    && (off = isonum_711(isodir->ext_attr_length)))
			VOP_BLKATOFF(vp, (off_t)-(off << imp->im_bshift), NULL,
E 8
				     &bp2);
I 7
		else
			bp2 = NULL;
E 7
		cd9660_defattr(isodir, ip, bp2);
		cd9660_deftstamp(isodir, ip, bp2);
D 7
		brelse(bp2);
E 7
I 7
		if (bp2)
			brelse(bp2);
E 7
		break;
	    }
	case ISO_FTYPE_RRIP:
		cd9660_rrip_analyze(isodir, ip, imp);
		break;
E 5
	}
D 5
	ip = nip;
E 5
I 5

	if (bp != 0)
		brelse(bp);

E 5
	/*
D 5
	 * XXX need generation number?
E 5
I 5
	 * Initialize the associated vnode
E 5
	 */
D 5
	if (ip->inode.iso_mode == 0) {
		iso_iput(ip);
		*vpp = NULLVP;
		printf("fhtovp: inode mode == 0\n");
		return (ESTALE);
E 5
I 5
	switch (vp->v_type = IFTOVT(ip->inode.iso_mode)) {
	case VFIFO:
#ifdef	FIFO
		vp->v_op = cd9660_fifoop_p;
		break;
#else
		vput(vp);
		return (EOPNOTSUPP);
#endif	/* FIFO */
	case VCHR:
	case VBLK:
		/*
		 * if device, look at device number table for translation
		 */
#ifdef	ISODEVMAP
		if (dp = iso_dmap(dev, ino, 0))
			ip->inode.iso_rdev = dp->d_dev;
#endif
		vp->v_op = cd9660_specop_p;
		if (nvp = checkalias(vp, ip->inode.iso_rdev, mp)) {
			/*
			 * Discard unneeded vnode, but save its iso_node.
I 19
			 * Note that the lock is carried over in the iso_node
			 * to the replacement vnode.
E 19
			 */
D 19
			cd9660_ihashrem(ip);
D 17
			VOP_UNLOCK(vp);
E 17
I 17
			VOP_UNLOCK(vp, 0, p);
E 19
E 17
			nvp->v_data = vp->v_data;
			vp->v_data = NULL;
			vp->v_op = spec_vnodeop_p;
			vrele(vp);
			vgone(vp);
			/*
			 * Reinitialize aliased inode.
			 */
			vp = nvp;
			ip->i_vnode = vp;
D 19
			cd9660_ihashins(ip);
E 19
		}
		break;
E 5
	}
D 5
	*vpp = ITOV(ip);
	*exflagsp = np->netc_exflags;
	*credanonp = &np->netc_anon;
	return 0;
E 5
I 5
	
	if (ip->iso_extent == imp->root_extent)
		vp->v_flag |= VROOT;

	/*
	 * XXX need generation number?
	 */
	
	*vpp = vp;
	return (0);
E 5
}

/*
 * Vnode pointer to File handle
 */
/* ARGSUSED */
D 2
isofs_vptofh(vp, fhp)
E 2
I 2
cd9660_vptofh(vp, fhp)
E 2
	struct vnode *vp;
	struct fid *fhp;
{
	register struct iso_node *ip = VTOI(vp);
	register struct ifid *ifhp;
	register struct iso_mnt *mp = ip->i_mnt;
	
	ifhp = (struct ifid *)fhp;
	ifhp->ifid_len = sizeof(struct ifid);
	
	ifhp->ifid_ino = ip->i_number;
	ifhp->ifid_start = ip->iso_start;
	
#ifdef	ISOFS_DBG
	printf("vptofh: ino %d, start %ld\n",
	       ifhp->ifid_ino,ifhp->ifid_start);
#endif
	return 0;
}
E 1
