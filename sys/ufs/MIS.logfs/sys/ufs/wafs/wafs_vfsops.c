#ifdef CLFS
/*
 * CLFS
 * $Log: wafs_vfsops.c,v $
 * Revision 1.14  1994/12/27  21:39:15  margo
 * Add checkpoint handling.  During a sync, force sync of ffs so
 * that log can be reclaimed.
 *
 * Revision 1.13  1994/11/15  22:23:50  margo
 * Merge lastrec and lastlen into nextrec.
 *
 * Revision 1.12  1994/10/25  14:31:23  margo
 * Convert to use the new vfs_export interface.
 *
 * Revision 1.11  1994/10/04  18:29:04  margo
 * Make sure that wafs includes get included in both AIX and BSD.
 *
 * Revision 1.10  1994/10/04  17:02:30  margo
 * Make 4.4Lite version compile under BSD4.4-Lite.
 *
 * Revision 1.2  1994/09/27  18:53:27  jat
 * Fixed includes for alternate AIX/SPARC building.
 *
 * Revision 1.1  1994/09/26  18:47:43  jat
 * Initial WAFS checkin.
 *
 */
#endif
/*
 * Copyright (c) 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1994
 *	The President and Fellows of Harvard University.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$Id: wafs_vfsops.c,v 1.14 1994/12/27 21:39:15 margo Exp margo $
 */
static char *rcsid = "$Id: wafs_vfsops.c,v 1.14 1994/12/27 21:39:15 margo Exp margo $";

#ifdef CLFS
#include <sys/bsd_param.h>
#include <clfs_param.h>
#include <sys/cdefs.h>
#include <sys/ucred.h>
#include <sys/param.h>
#include <sys/vnode.h>
#include <sys/compat.h>
#include <sys/bsd_types.h>
#include <sys/socket.h>
#include <sys/mbuf.h>
#include <sys/file.h>
#include <sys/disklabel.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/malloc.h>

#include <miscfs/specfs/specdev.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufs_extern.h>

#else /* CLFS */

#include <sys/param.h>
#include <sys/malloc.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <sys/socket.h>
#include <sys/mount.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/file.h>
#include <sys/disklabel.h>
#include <sys/ioctl.h>
#include <sys/errno.h>

#include <miscfs/specfs/specdev.h>

#include <ufs/ufs/quota.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufs_extern.h>

#include <ufs/logging/lffs_extern.h>
#endif /* CLFS */

#include <ufs/wafs/wafs.h>
#include <ufs/wafs/wnode.h>
#include <ufs/wafs/wafs_extern.h>


#ifdef AIX
extern int 	(**glue_ufs_vnodeops)();
extern int	(**glue_spec_vnodeop_p)();
extern int	ffs_unsupp();
struct bsd_vfsops wafs_vfsops = {
	wafs_mount,
	ffs_unsupp,	/* wafs_start NOT_SUPPORTED */
	wafs_unmount,
	wafs_root,
	ffs_unsupp,	/* wafs_quotactl NOT_SUPPORTED */
	wafs_statfs,
	wafs_sync,
	wafs_vget,
	ffs_unsupp,	/* wafs_fhtovp NOT_YET */
	ffs_unsupp,	/* wafs_vptofh NOT_YET */
	wafs_init,
};
#else
struct vfsops wafs_vfsops = {
	wafs_mount,
	ufs_start,
	wafs_unmount,
	wafs_root,
	ufs_quotactl,
	wafs_statfs,
	wafs_sync,
	wafs_vget,
	wafs_fhtovp,
	wafs_vptofh,
	ufs_init,
};
#endif

#ifdef AIX
extern struct  timestruc_t tod;
#endif

/*
 * VFS Operations.
 *
 * mount system call
 */
int
wafs_mount(mp, path, data, ndp, p)
#ifdef AIX
	register struct bsd_mount *mp;
#else
	register struct mount *mp;
#endif
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
#ifdef AIX
	struct ufs_args *args;
	aix_vnode_t *aix_devvp, *aix_frootvp;
#else
	struct ufs_args args;
#endif
	struct vnode *devvp, *frootvp;
	struct ufsmount *ump;
	register struct wafs *wafs;
	u_int size;
	int error, flags;

#ifdef CLFS
	CLFSDEBUG("in wafs_mount...\n", NULL);
#endif
#ifdef AIX
	args = (struct ufs_args *)data;
#else
	if (error = copyin(data, (caddr_t)&args, sizeof (struct ufs_args)))
		return (error);
#endif
	/*
	 * If updating, check whether changing from read-only to
	 * read/write; if there is no device name, that's all we do.
	 */
#ifndef CLFS /* CLFS_NOTYET */
	if (mp->mnt_flag & MNT_UPDATE) {
		ump = VFSTOUFS(mp);
		wafs = ump->um_wafs;
		error = 0;
		if (wafs->wafs_ronly == 0 && (mp->mnt_flag & MNT_RDONLY)) {
			flags = WRITECLOSE;
			if (mp->mnt_flag & MNT_FORCE)
				flags |= FORCECLOSE;
			if (vfs_busy(mp))
				return (EBUSY);
			/*
			 * For now, there is only one file; if we
			 * go to multiple files, this will have to change.
			 */
			error = VOP_FSYNC(mp->mnt_vnodelist.lh_first,
			    p->p_ucred, MNT_WAIT, p);
			vfs_unbusy(mp);
		}
		if (!error && (mp->mnt_flag & MNT_RELOAD))
			error = wafs_reload(mp, ndp->ni_cnd.cn_cred, p);
		if (error)
			return (error);
		if (wafs->wafs_ronly && (mp->mnt_flag & MNT_WANTRDWR))
			wafs->wafs_ronly = 0;
		if (args.fspec == 0) {
			/*
			 * Process export requests.
			 */
			return (vfs_export(mp, &ump->um_export, &args.export));
		}
	}
#endif
	/*
	 * Not an update, or updating the name: look up the name
	 * and verify that it refers to a sensible block device.
	 */
#ifdef AIX
	error = lookupvp(args->fspec, 0, &aix_devvp);
	if (error)
		return(error);
	/*
	 * At this point we have an AIX vnode for the device.  We allocate a
	 * BSD vnode to make it easier for all of ffs and the buffer cache to
	 * use devvp.
 	 */
	error = getnewvnode(VT_AIXDEV, NULL, NULL, &devvp);
	if (error) { 
		VNOP_RELE(aix_devvp); /* note: AIX VNOP */
		return(error); 
	}
	devvp->v_gnode.gn_vnode = aix_devvp;
	devvp->v_gnode.gn_ops = NULL; /* not used,only need ops in BSD vnode */
	devvp->v_type = VBLK;
	devvp->v_op = glue_spec_vnodeop_p;
#else
	NDINIT(ndp, LOOKUP, FOLLOW, UIO_USERSPACE, args.fspec, p);
	if (error = namei(ndp))
		return (error);
	devvp = ndp->ni_vp;
#endif

#ifdef AIX
	if (aix_devvp->v_gnode->gn_type != VBLK) {
		vrele(devvp);
		VNOP_RELE(aix_devvp); /* note: AIX VNOP */
		return (ENOTBLK);
	}
#else
	if (devvp->v_type != VBLK) {
		vrele(devvp);
		return (ENOTBLK);
	}
	if (major(devvp->v_rdev) >= nblkdev) {
		vrele(devvp);
		return (ENXIO);
	}
#endif
	if ((mp->mnt_flag & MNT_UPDATE) == 0)
		error = wafs_mountfs(devvp, mp, p);
	else {
#ifndef CLFS /* CLFS_NOTYET */
		if (devvp != ump->um_devvp)
			error = EINVAL;	/* needs translation */
		else
			vrele(devvp);
#endif
	}
	if (error) {
		vrele(devvp);
#ifdef AIX
		VNOP_RELE(aix_devvp); /* note: AIX VNOP */
#endif		
		return (error);
	}
	ump = VFSTOUFS(mp);
	wafs = ump->um_wafs;

#ifdef LFFS
	/*
	 * If the log_fs field is filled in then we need verify that
	 * the specified file system is a UFS and that its ID matches
	 * our ID.
	 */
	if (args.log_fs) {
		frootvp = lffs_getvn(p, args.log_fs);
		ump->um_relmp = frootvp->v_mount;
		vrele(frootvp);
		if (ump->um_relmp->mnt_stat.f_type != MOUNT_UFS ||
		    VFSTOUFS(ump->um_relmp)->um_joinid != wafs->wafs_id) {
#ifndef AIX
        		devvp->v_specflags &= ~SI_MOUNTEDON;
#endif
			error = VOP_CLOSE(devvp,
			    wafs->wafs_ronly ? FREAD : FREAD|FWRITE, NOCRED, p);
			vrele(devvp);
#ifdef AIX
			free(wafs);
			free(ump);
			mp->mnt_data = (ulong_t)0;
#else
			free(wafs, M_UFSMNT);
			free(ump, M_UFSMNT);
			mp->mnt_data = (qaddr_t)0;
#endif
			return(EINVAL);
		}
	}
#endif

#ifdef AIX
	bzero(wafs->wafs_fsmnt, sizeof(wafs->wafs_fsmnt));
	strcpy(wafs->wafs_fsmnt, path);
	strcpy(mp->mnt_stat.f_mntonname, wafs->wafs_fsmnt);
	bzero(mp->mnt_stat.f_mntfromname, sizeof(mp->mnt_stat.f_mntfromname));
	strcpy(mp->mnt_stat.f_mntfromname, args->fspec);
#else
	(void) copyinstr(path, wafs->wafs_fsmnt, sizeof(wafs->wafs_fsmnt) - 1,
	    &size);
	bzero(wafs->wafs_fsmnt + size, sizeof(wafs->wafs_fsmnt) - size);
	bcopy((caddr_t)wafs->wafs_fsmnt, (caddr_t)mp->mnt_stat.f_mntonname,
	    MNAMELEN);
	(void) copyinstr(args.fspec, mp->mnt_stat.f_mntfromname, MNAMELEN- 1, 
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
#endif
	(void)wafs_statfs(mp, &mp->mnt_stat, p);
	return (0);
}

#ifndef CLFS /* CLFS_NOTYET */
/*
 * Reload all incore data for a filesystem.  The filesystem must
 * be mounted read-only.
 *
 * Things to do to update the mount:
 *	1) re-read superblock from disk.
 *	2) invalidate all cached file data.
 *	3) re-initialize wnode data for all active vnodes.
 */
wafs_reload(mountp, cred, p)
	register struct mount *mountp;
	struct ucred *cred;
	struct proc *p;
{
	register struct vnode *vp, *nvp, *devvp;
	struct wnode *wp;
	struct csum *space;
	struct buf *bp;
	struct wafs *wafs;
	int i, blks, size, error;

	if ((mountp->mnt_flag & MNT_RDONLY) == 0)
		return (EINVAL);
	/*
	 * Step 1: re-read superblock from disk.
	 */
	if (error = bread(devvp, SBLOCK, WAFS_SBSIZE, NOCRED, &bp))
		return (error);
	/* XXX do we want to add wafs to buf struct? */
	wafs = (struct wafs *)bp->b_data;
	if (wafs->wafs_magic != WAFS_MAGIC || wafs->wafs_bsize > MAXBSIZE ||
	    wafs->wafs_bsize < sizeof(struct wafs)) {
		brelse(bp);
		return (EIO);		/* XXX needs translation */
	}
	wafs = VFSTOUFS(mountp)->um_wafs;
	bcopy(bp->b_data, (caddr_t)wafs, (u_int)wafs->wafs_sbsize);
	if (wafs->wafs_sbsize < WAFS_SBSIZE)
		bp->b_flags |= B_INVAL;
	wafs->wafs_flags &= ~WAFS_MOD;
	brelse(bp);

	/* Verify that there is only one node on the vnode chain */
loop:
	for (vp = mountp->mnt_vnodelist.lh_first; vp; vp = nvp) {
		nvp = vp->v_mntvnodes.le_next;
		/*
		 * We should never have an inactive vnodes.
		 */
		if (vp->v_usecount == 0)
			return(EINVAL);
		/*
		 * Should only be a single node with cached data.
		 */
		if (vget(vp, 1))
			goto loop;
		if (vinvalbuf(vp, 0, cred, p, 0, 0))
			panic("wafs_reload: dirty2");
		if (vp->v_mntvnodes.le_next)
			panic("wafs_reload: too many vnodes on chain");
		/*
		 * Step 3: re-initialize wnode data for log.
		 */
		wp = VTOW(vp);
		wp->w_head = wafs->wafs_head;
		wp->w_tail = wafs->wafs_tail;
		wp->w_ctime.ts_sec = wp->w_mtime.ts_sec = wafs->wafs_time;
		wp->w_atime.ts_sec = wafs->wafs_rtime;
		wp->w_nextrec = 0;
		wp->w_type = WAFS_NORECORD;
		if (error = bread(devvp, wp->w_head, (int)wafs->wafs_bsize,
		    NOCRED, &bp)) {
			vput(vp);
			return (error);
		}
		/*
		 * XXX Find last valid log record so that you can set
		 * last_lsn correctly.  Also, does w_flag need to be
		 * changed?
		 */
		brelse(bp);
		vput(vp);
		if (vp->v_mount != mountp)
			goto loop;
	}
	return (0);
}
#endif /* CLFS_NOTYET */

/*
 * Nitty gritty mount code.
 */
int
wafs_mountfs(devvp, mp, p)
	register struct vnode *devvp;
#ifdef AIX
	struct bsd_mount *mp;
#else
	struct mount *mp;
#endif
	struct proc *p;
{
	register struct ufsmount *ump;
	struct buf *bp;
	register struct wafs *wafs;

	dev_t dev = devvp->v_rdev;
	struct partinfo dpart;
	caddr_t base, space;
	int havepart = 0, blks;
	int error, i, size;
	int ronly;
#ifndef AIX
	extern struct vnode *rootvp;
#endif

	/*
	 * Disallow multiple mounts of the same device.
	 * Disallow mounting of a device that is currently in use
	 * Flush out any old buffers remaining from a previous use.
	 */
#ifndef AIX /* STUB: how to check in AIX? */
	if (error = vfs_mountedon(devvp))
		return (error);
	if (vcount(devvp) > 1 && devvp != rootvp)
		return (EBUSY);
#endif
#ifndef CLFS /* CLFS_NOTYET */
	if (error = vinvalbuf(devvp, V_SAVE, p->p_ucred, p, 0, 0))
		return (error);
#endif

	ronly = (mp->mnt_flag & MNT_RDONLY) != 0;
	if (error = VOP_OPEN(devvp, ronly ? FREAD : FREAD|FWRITE, FSCRED, p))
		return (error);
	if (VOP_IOCTL(devvp, DIOCGPART, (caddr_t)&dpart, FREAD, NOCRED, p) != 0)
		size = DEV_BSIZE;
	else {
		havepart = 1;
		size = dpart.disklab->d_secsize;
	}

	bp = NULL;
	ump = NULL;
	if (error = bread(devvp, SBLOCK, WAFS_SBSIZE, NOCRED, &bp))
		goto out;
	wafs = (struct wafs *)bp->b_data;
	if (wafs->wafs_magic != WAFS_MAGIC || wafs->wafs_bsize > MAXBSIZE ||
	    wafs->wafs_bsize < sizeof(struct wafs)) {
		error = EINVAL;		/* XXX needs translation */
		goto out;
	}
#ifdef AIX
	ump = malloc(sizeof *ump);
	bzero((caddr_t)ump, sizeof *ump);
	ump->um_wafs = malloc((u_long)wafs->wafs_sbsize);
#else
	ump = malloc(sizeof *ump, M_UFSMNT, M_WAITOK);
	bzero((caddr_t)ump, sizeof *ump);
	ump->um_wafs = malloc((u_long)wafs->wafs_sbsize, M_UFSMNT,
	    M_WAITOK);
#endif
	bcopy(bp->b_data, ump->um_wafs, (u_int)wafs->wafs_sbsize);
	if (wafs->wafs_sbsize < WAFS_SBSIZE)
		bp->b_flags |= B_INVAL;
	brelse(bp);
	bp = NULL;
	wafs = ump->um_wafs;
	wafs->wafs_ronly = ronly;
	if (ronly == 0)
		wafs->wafs_fmod = 1;
	if (havepart) {
		dpart.part->p_fstype = FS_BSDFFS;
		dpart.part->p_fsize = wafs->wafs_bsize;
		dpart.part->p_frag = 1;
		dpart.part->p_cpg = 0;
	}
	/* Figure out how much space is available in the file system */
#ifdef AIX
	mp->mnt_data = (long)ump;
#else
	mp->mnt_data = (qaddr_t)ump;
#endif
	mp->mnt_stat.f_fsid.val[0] = (long)dev;
	mp->mnt_stat.f_fsid.val[1] = MOUNT_WAFS;
	mp->mnt_maxsymlinklen = -1;
	mp->mnt_flag |= MNT_LOCAL;
	ump->um_mountp = mp;
	ump->um_dev = dev;
	ump->um_devvp = devvp;
	ump->um_joinid = wafs->wafs_id;
	ump->um_nindir = 0;
	ump->um_bptrtodb = 0;
	ump->um_seqinc = 1;
#ifndef AIX
	devvp->v_specflags |= SI_MOUNTEDON;
#endif
	return (0);
out:
	if (bp)
		brelse(bp);
	(void)VOP_CLOSE(devvp, ronly ? FREAD : FREAD|FWRITE, NOCRED, p);
	if (ump) {
#ifdef AIX
		free(ump->um_wafs);
		free(ump);
		mp->mnt_data = (long)0;
#else
		free(ump->um_wafs, M_UFSMNT);
		free(ump, M_UFSMNT);
		mp->mnt_data = (qaddr_t)0;
#endif
	}
	return (error);
}


/*
 * unmount system call
 */
int
wafs_unmount(mp, mntflags, p)
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
	register struct ufsmount *ump;
	register struct wafs *wafs;
	struct vnode *frootvp;
	int error, flags, ronly;

#ifdef CLFS
	CLFSDEBUG("in wafs_unmount...\n", NULL);
#endif
	flags = 0;
	if (mntflags & MNT_FORCE) {
		if (mp->mnt_flag & MNT_ROOTFS)
			return (EINVAL);
		flags |= FORCECLOSE;
	}

	ump = VFSTOUFS(mp);

	/*
	 * Only unmount wafs if there is no associated ffs, this
	 * is called from ffs_unmount, or this is a FORCE.
	 */
	if (ump->um_relmp && !(mntflags & (MNT_UNWAFS | MNT_FORCE)))
		return (EBUSY);

	/* XXX Is this the right cred? */
	if (error = wafs_sync(mp, 1, p->p_ucred, p))
		return (error);
	/*
	 * XXX this is probably an unsafe thing to do without
	 * locking the other mp
	 */
#ifdef LFFS
	if (ump->um_relmp) {
		frootvp = VFSTOUFS(ump->um_relmp)->um_relvp;
		if (!(mntflags & MNT_UNWAFS))
			VFSTOUFS(ump->um_relmp)->um_relvp = NULL;
		vrele(frootvp);
	}
#endif

	/* Now, flush all vnodes */
	vflush(mp, NULL, flags & FORCECLOSE ? FORCECLOSE : 0);

	ump = VFSTOUFS(mp);
	wafs = ump->um_wafs;
	ronly = !wafs->wafs_ronly;
#ifndef AIX
	ump->um_devvp->v_specflags &= ~SI_MOUNTEDON;
#endif
	error = VOP_CLOSE(ump->um_devvp, ronly ? FREAD : FREAD|FWRITE,
		NOCRED, p);
	vrele(ump->um_devvp);
#ifdef AIX
	free(wafs);
	free(ump);
	mp->mnt_data = (ulong_t)0;
#else
	free(wafs, M_UFSMNT);
	free(ump, M_UFSMNT);
	mp->mnt_data = (qaddr_t)0;
#endif
	mp->mnt_flag &= ~MNT_LOCAL;
	return (error);
}

/*
 * Return root of a filesystem
 */
int
wafs_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
	struct vnode *nvp;
	int error;

	if (error = VFS_VGET(mp, (ino_t)MASTERLOG, &nvp))
		return (error);
	*vpp = nvp;
	return (0);
}

/*
 * Get file system statistics.
 */
int
wafs_statfs(mp, sbp, p)
#ifdef AIX
	struct bsd_mount *mp;
	register struct bsd_statfs *sbp;
#else
	struct mount *mp;
	register struct statfs *sbp;
#endif
	struct proc *p;
{
	register struct ufsmount *ump;
	register struct wafs *wafs;
	daddr_t head, tail;

	ump = VFSTOUFS(mp);
	wafs = ump->um_wafs;
	if (wafs->wafs_magic != WAFS_MAGIC)
		panic("wafs_statfs");
	sbp->f_type = MOUNT_WAFS;
	sbp->f_bsize = wafs->wafs_bsize;
	sbp->f_iosize = wafs->wafs_bsize;
	sbp->f_blocks = wafs->wafs_dsize;

	/* Amount free is everything except blocks between tail and head. */
	sbp->f_bfree = wafs->wafs_dsize - 
	    (lblkno(wafs, wafs->wafs_head) - lblkno(wafs, wafs->wafs_tail));

	sbp->f_bavail = sbp->f_bfree;
	sbp->f_files =  1;
	sbp->f_ffree = 0;
	if (sbp != &mp->mnt_stat) {
		bcopy((caddr_t)mp->mnt_stat.f_mntonname,
			(caddr_t)&sbp->f_mntonname[0], MNAMELEN);
		bcopy((caddr_t)mp->mnt_stat.f_mntfromname,
			(caddr_t)&sbp->f_mntfromname[0], MNAMELEN);
	}
	return (0);
}

/*
 * Make sure that all records are written to disk.
 * Note: we are always called with the filesystem marked `MPBUSY'.
 */
int
wafs_sync(mp, waitfor, cred, p)
	struct mount *mp;
	int waitfor;
	struct ucred *cred;
	struct proc *p;
{
	register struct vnode *vp;
	register struct inode *ip;
	register struct ufsmount *ump = VFSTOUFS(mp);
	register struct wafs *wafs;
	off_t checkpoint_lsn;
	long flag;
	int error, allerror = 0;

	wafs = ump->um_wafs;
	wafs->wafs_inchkpt = 1;
	/*
	 * Write back any dirty buffers.
	 */
loop:
	for (vp = mp->mnt_vnodelist.lh_first;
	     vp != NULL;
	     vp = vp->v_mntvnodes.le_next) {
		if (vp->v_mntvnodes.le_next)
			panic("wafs_sync: too many vnodes on chain");

		/* Lock vnode */
		/*
		 * This is where we call to the other file
		 * system and take a checkpoint.
		 */
		checkpoint_lsn = VTOW(vp)->w_head;
		if (error = VOP_FSYNC(vp, cred, waitfor, p))
			allerror = error;
		if (!(mp->mnt_flag & MNT_UNMOUNT) && waitfor &&
		    ump->um_relmp) {
			vfs_busy(ump->um_relmp);
			flag = ump->um_relmp->mnt_flag & MNT_ASYNC;
			ump->um_relmp->mnt_flag &= ~MNT_ASYNC;
			VFS_SYNC(ump->um_relmp, waitfor, cred, p);
			ump->um_relmp->mnt_flag |= flag;
			vfs_unbusy(ump->um_relmp);
		}
		wafs->wafs_tail = VTOW(vp)->w_tail = checkpoint_lsn;
	}


	/*
	 * Write back superblock; it will always be modified since
	 * we just updated the tail. Consistency check that the superblock
	 * is still in the buffer cache.
	 */
	if (wafs->wafs_ronly != 0) {
#ifdef AIX
		wafs->wafs_time = tod.tv_sec;
#else
		wafs->wafs_time = time.tv_sec;
#endif
		allerror = wafs_sbupdate(ump, waitfor);
	}
	wafs->wafs_inchkpt = 0;
	return (allerror);
}

/*
 * Check the vnode chain for our one vnode.  If it is not
 * there, construct the single wnode for this file system
 * from the superblock information.
 */
int
wafs_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{
	register struct wafs *wafs;
	register struct wnode *wp;
	struct ufsmount *ump;
	struct vnode *vp;
	dev_t dev;
	int error;

	/* Only one inode in this file system */
	if (ino != MASTERLOG)
		return(EINVAL);
loop:
	for (vp = mp->mnt_vnodelist.lh_first;
	     vp != NULL;
	     vp = vp->v_mntvnodes.le_next) {
		wp = VTOW(vp);
		if (wp->w_ino != ino)
			continue;
		*vpp = vp;
		if (vget(vp, 1))
			goto loop;
		return (0);
	}

	/* Allocate a new vnode/wnode. */
	if (error = getnewvnode(VT_WAFS, mp, wafs_vnodeop_p, &vp)) {
		*vpp = NULL;
		return (error);
	}

	ump = VFSTOUFS(mp);
	dev = ump->um_dev;
#ifdef AIX
	MALLOC(wp, struct wnode *, sizeof(struct wnode), type, M_WAITOK);
#else
	wp = malloc(sizeof (struct wnode), M_WAFSNODE, M_WAITOK);
#endif
	bzero((caddr_t)wp, sizeof(struct wnode));
	vp->v_data = wp;
	wp->w_vnode = vp;
	wp->w_fs = wafs = ump->um_wafs;
	wp->w_dev = dev;
	wp->w_ino = ino;
	wp->w_flag = WLOCKED;
#ifndef CLFS /* CLFS_NOTYET */
	if (curproc)
		wp->w_lockholder = curproc->p_pid;
	else
		wp->w_lockholder = -1;
#endif
	wp->w_lastlsn = wafs->wafs_lsn;
	wp->w_head = wafs->wafs_head;
	wp->w_tail = wafs->wafs_tail;
	wp->w_ctime.ts_sec = wp->w_mtime.ts_sec = wafs->wafs_time;
	wp->w_atime.ts_sec = wafs->wafs_rtime;
	wp->w_devvp = ump->um_devvp;
	VREF(wp->w_devvp);

	/* Initialize vnode */
	vp->v_flag |= VROOT;
	vp->v_type = VREG;

	*vpp = vp;
	return (0);
}

#ifndef CLFS /* CLFS_NOTYET */
/*
 * File handle to vnode
 *
 * Have to be really careful about stale file handles:
 * - check that the inode number is valid
 * - call wafs_vget() to get the locked inode
 * - check for an unallocated inode (i_mode == 0)
 * - check that the given client host has export rights and return
 *   those rights via. exflagsp and credanonp
 */
int
wafs_fhtovp(mp, fhp, nam, vpp, exflagsp, credanonp)
	register struct mount *mp;
	struct fid *fhp;
	struct mbuf *nam;
	struct vnode **vpp;
	int *exflagsp;
	struct ucred **credanonp;
{
	register struct ufid *ufhp;
	struct wafs *wafs;

	ufhp = (struct ufid *)fhp;
	wafs = VFSTOUFS(mp)->um_wafs;
	if (ufhp->ufid_ino |= MASTERLOG)
		return (ESTALE);
	return (wafs_check_export(mp, ufhp, nam, vpp, exflagsp, credanonp));
}

/*
 * Vnode pointer to File handle
 */
/* ARGSUSED */
wafs_vptofh(vp, fhp)
	struct vnode *vp;
	struct fid *fhp;
{
	register struct wnode *wp;
	register struct ufid *ufhp;

	wp = VTOW(vp);
	ufhp = (struct ufid *)fhp;
	ufhp->ufid_len = sizeof(struct ufid);
	ufhp->ufid_ino = wp->w_ino;
	ufhp->ufid_gen = 1;	/* XXX Always make it one */
	return (0);
}
#endif /* CLFS_NOTYET */

/*
 * Write a superblock.
 */
int
wafs_sbupdate(ump, waitfor)
	struct ufsmount *ump;
	int waitfor;
{
	register struct wafs *wafs = ump->um_wafs;
	register struct buf *bp;
	struct vnode *vp;
	struct wnode *wp;
	struct mount *mp;
	int error = 0;

	mp = ump->um_mountp;
	if ((wafs->wafs_flags & WAFS_MOD) == 0)
		return(0);

	bp = getblk(ump->um_devvp, SBLOCK, (int)wafs->wafs_sbsize, 0, 0);
	bcopy((caddr_t)wafs, bp->b_data, (u_int)wafs->wafs_sbsize);
	if (waitfor == MNT_WAIT)
		error = bwrite(bp);
	else
		bawrite(bp);
	wafs->wafs_flags &= ~WAFS_MOD;
	return (error);
}
