h08212
s 00004/00002/00377
d D 8.8 95/05/14 00:46:55 mckusick 13 12
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00002/00377
d D 8.7 95/05/10 11:22:29 pendry 12 11
c VOP_REVOKE(vp, 0) should really be vgone(vp)
e
s 00001/00006/00378
d D 8.6 95/05/10 09:47:53 mckusick 11 10
c check for forcible unmount at syscall level
e
s 00005/00002/00379
d D 8.5 95/03/29 00:42:56 mckusick 10 9
c cleanups; getnewfsid => vfs_getnewfsid; add sysctl
e
s 00001/00001/00380
d D 8.4 95/02/23 12:23:41 mckusick 9 7
c vgone => VOP_REVOKE
e
s 00001/00001/00380
d R 8.4 95/02/22 19:13:33 mckusick 8 7
c vgone => VOP_REVOKE
e
s 00000/00001/00381
d D 8.3 94/01/21 19:55:30 bostic 7 6
c copyright typo
e
s 00015/00014/00367
d D 8.2 94/01/13 12:17:03 bostic 6 5
c lint/KNF, by Jan-Simon and I
e
s 00002/00002/00379
d D 8.1 93/06/10 23:47:30 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00379
d D 7.2 92/07/12 16:34:35 pendry 4 3
c new location for umap.h
e
s 00001/00001/00380
d D 7.1 92/07/12 15:28:51 mckusick 3 2
c move to rev 7; new include location; syntax niggles
e
s 00020/00027/00361
d D 1.2 92/07/11 15:28:54 heideman 2 1
c Porting from null layer
e
s 00388/00000/00000
d D 1.1 92/07/11 09:21:15 heideman 1 0
c date and time created 92/07/11 09:21:15 by heideman
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 5
I 5
D 12
 * Copyright (c) 1992, 1993
E 12
I 12
 * Copyright (c) 1992, 1993, 1995
E 12
 *	The Regents of the University of California.  All rights reserved.
E 5
D 7
 * All rights reserved.
E 7
 *
 * This code is derived from software donated to Berkeley by
D 2
 * Jan-Simon Pendry.
E 2
I 2
 * the UCLA Ficus project.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 2
 * @(#)lofs_vfsops.c	1.2 (Berkeley) 6/18/92
 * $Id: lofs_vfsops.c,v 1.9 1992/05/30 10:26:24 jsp Exp jsp $
E 2
I 2
 * @(#)null_vfsops.c       1.5 (Berkeley) 7/10/92
E 2
 */

/*
D 2
 * Null Layer
 * (See umap_vnops.c for a description of what this does.)
E 2
I 2
 * Umap Layer
D 4
 * (See mount_umap(8) for a descritpion of this layer.)
E 4
I 4
 * (See mount_umap(8) for a description of this layer.)
E 4
E 2
 */

#include <sys/param.h>
#include <sys/systm.h>
I 13
#include <sys/proc.h>
E 13
#include <sys/time.h>
#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
D 4
#include <umapfs/umap.h>
E 4
I 4
#include <miscfs/umapfs/umap.h>
E 4

/*
 * Mount umap layer
 */
int
umapfs_mount(mp, path, data, ndp, p)
	struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
D 6
	int i;
	int error = 0;
E 6
	struct umap_args args;
	struct vnode *lowerrootvp, *vp;
	struct vnode *umapm_rootvp;
	struct umap_mount *amp;
	u_int size;
I 6
	int error;
E 6

#ifdef UMAPFS_DIAGNOSTIC
	printf("umapfs_mount(mp = %x)\n", mp);
#endif

	/*
	 * Update is a no-op
	 */
	if (mp->mnt_flag & MNT_UPDATE) {
		return (EOPNOTSUPP);
D 6
		/* return VFS_MOUNT(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, path, data, ndp, p);*/
E 6
I 6
		/* return (VFS_MOUNT(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, path, data, ndp, p));*/
E 6
	}

	/*
	 * Get argument
	 */
	if (error = copyin(data, (caddr_t)&args, sizeof(struct umap_args)))
		return (error);

	/*
D 2
	 * Find target node
E 2
I 2
	 * Find lower node
E 2
	 */
	NDINIT(ndp, LOOKUP, FOLLOW|WANTPARENT|LOCKLEAF,
		UIO_USERSPACE, args.target, p);
	if (error = namei(ndp))
		return (error);

	/*
D 2
	 * Sanity check on target vnode
E 2
I 2
	 * Sanity check on lower vnode
E 2
	 */
	lowerrootvp = ndp->ni_vp;
#ifdef UMAPFS_DIAGNOSTIC
	printf("vp = %x, check for VDIR...\n", lowerrootvp);
#endif
	vrele(ndp->ni_dvp);
	ndp->ni_dvp = 0;

D 2
	/*
	 * NEEDSWORK: Is this really bad, or just not
	 * the way it's been?
	 */
E 2
	if (lowerrootvp->v_type != VDIR) {
		vput(lowerrootvp);
		return (EINVAL);
	}

#ifdef UMAPFS_DIAGNOSTIC
	printf("mp = %x\n", mp);
#endif

	amp = (struct umap_mount *) malloc(sizeof(struct umap_mount),
				M_UFSMNT, M_WAITOK);	/* XXX */

	/*
D 2
	 * Save reference to underlying target FS
E 2
I 2
	 * Save reference to underlying FS
E 2
	 */
	amp->umapm_vfs = lowerrootvp->v_mount;

	/* 
	 * Now copy in the number of entries and maps for umap mapping.
	 */
D 2

E 2
	amp->info_nentries = args.nentries;
	amp->info_gnentries = args.gnentries;
	error = copyin(args.mapdata, (caddr_t)amp->info_mapdata, 
D 2
	    8*args.nentries);
E 2
I 2
D 6
	    2*sizeof(int)*args.nentries);
E 2
	if (error) return (error);
E 6
I 6
	    2*sizeof(u_long)*args.nentries);
	if (error)
		return (error);
E 6
I 2

#ifdef UMAP_DIAGNOSTIC
E 2
	printf("umap_mount:nentries %d\n",args.nentries);
D 2
	for (i=0; i<args.nentries;i++)
E 2
I 2
	for (i = 0; i < args.nentries; i++)
E 2
		printf("   %d maps to %d\n", amp->info_mapdata[i][0],
	 	    amp->info_mapdata[i][1]);
I 2
#endif
E 2

	error = copyin(args.gmapdata, (caddr_t)amp->info_gmapdata, 
D 2
	    8*args.nentries);
E 2
I 2
D 6
	    2*sizeof(int)*args.nentries);
E 2
	if (error) return (error);
E 6
I 6
	    2*sizeof(u_long)*args.nentries);
	if (error)
		return (error);
E 6
I 2

#ifdef UMAP_DIAGNOSTIC
E 2
	printf("umap_mount:gnentries %d\n",args.gnentries);
D 2
	for (i=0; i<args.gnentries;i++)
E 2
I 2
	for (i = 0; i < args.gnentries; i++)
E 2
		printf("	group %d maps to %d\n", 
		    amp->info_gmapdata[i][0],
	 	    amp->info_gmapdata[i][1]);
I 2
#endif
E 2


	/*
	 * Save reference.  Each mount also holds
	 * a reference on the root vnode.
	 */
	error = umap_node_create(mp, lowerrootvp, &vp);
	/*
D 2
	 * Unlock the node (either the target or the alias)
E 2
I 2
	 * Unlock the node (either the lower or the alias)
E 2
	 */
D 13
	VOP_UNLOCK(vp);
E 13
I 13
	VOP_UNLOCK(vp, 0, p);
E 13
	/*
	 * Make sure the node alias worked
	 */
	if (error) {
		vrele(lowerrootvp);
		free(amp, M_UFSMNT);	/* XXX */
		return (error);
	}

	/*
	 * Keep a held reference to the root vnode.
	 * It is vrele'd in umapfs_unmount.
	 */
	umapm_rootvp = vp;
	umapm_rootvp->v_flag |= VROOT;
	amp->umapm_rootvp = umapm_rootvp;
	if (UMAPVPTOLOWERVP(umapm_rootvp)->v_mount->mnt_flag & MNT_LOCAL)
		mp->mnt_flag |= MNT_LOCAL;
	mp->mnt_data = (qaddr_t) amp;
D 10
	getnewfsid(mp, MOUNT_LOFS);
E 10
I 10
	vfs_getnewfsid(mp);
E 10

	(void) copyinstr(path, mp->mnt_stat.f_mntonname, MNAMELEN - 1, &size);
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);
	(void) copyinstr(args.target, mp->mnt_stat.f_mntfromname, MNAMELEN - 1, 
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
#ifdef UMAPFS_DIAGNOSTIC
D 2
	printf("umapfs_mount: target %s, alias at %s\n",
E 2
I 2
	printf("umapfs_mount: lower %s, alias at %s\n",
E 2
		mp->mnt_stat.f_mntfromname, mp->mnt_stat.f_mntonname);
#endif
	return (0);
}

/*
 * VFS start.  Nothing needed here - the start routine
 * on the underlying filesystem will have been called
 * when that filesystem was mounted.
 */
int
umapfs_start(mp, flags, p)
	struct mount *mp;
	int flags;
	struct proc *p;
{
	return (0);
D 6
	/* return VFS_START(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, flags, p); */
E 6
I 6
	/* return (VFS_START(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, flags, p)); */
E 6
}

/*
 * Free reference to umap layer
 */
int
umapfs_unmount(mp, mntflags, p)
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
	struct vnode *umapm_rootvp = MOUNTTOUMAPMOUNT(mp)->umapm_rootvp;
	int error;
	int flags = 0;
D 11
	extern int doforce;
E 11

#ifdef UMAPFS_DIAGNOSTIC
	printf("umapfs_unmount(mp = %x)\n", mp);
#endif

D 11
	if (mntflags & MNT_FORCE) {
		/* lofs can never be rootfs so don't check for it */
		if (!doforce)
			return (EINVAL);
E 11
I 11
	if (mntflags & MNT_FORCE)
E 11
		flags |= FORCECLOSE;
D 11
	}
E 11

	/*
	 * Clear out buffer cache.  I don't think we
	 * ever get anything cached at this level at the
	 * moment, but who knows...
	 */
D 3
#if 0
E 3
I 3
#ifdef notyet
E 3
	mntflushbuf(mp, 0); 
	if (mntinvalbuf(mp, 1))
		return (EBUSY);
#endif
	if (umapm_rootvp->v_usecount > 1)
		return (EBUSY);
	if (error = vflush(mp, umapm_rootvp, flags))
		return (error);

#ifdef UMAPFS_DIAGNOSTIC
D 2
	/*
	 * Flush any remaining vnode references
	 */
	umap_node_flushmp (mp);
#endif

#ifdef UMAPFS_DIAGNOSTIC
	vprint("alias root of target", umapm_rootvp);
E 2
I 2
	vprint("alias root of lower", umapm_rootvp);
E 2
#endif	 
	/*
	 * Release reference on underlying root vnode
	 */
	vrele(umapm_rootvp);
	/*
	 * And blow it away for future re-use
	 */
D 9
	vgone(umapm_rootvp);
E 9
I 9
D 12
	VOP_REVOKE(umapm_rootvp, 0);
E 12
I 12
	vgone(umapm_rootvp);
E 12
E 9
	/*
	 * Finally, throw away the umap_mount structure
	 */
	free(mp->mnt_data, M_UFSMNT);	/* XXX */
	mp->mnt_data = 0;
D 6
	return 0;
E 6
I 6
	return (0);
E 6
}

int
umapfs_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
I 13
	struct proc *p = curproc;	/* XXX */
E 13
	struct vnode *vp;

#ifdef UMAPFS_DIAGNOSTIC
	printf("umapfs_root(mp = %x, vp = %x->%x)\n", mp,
			MOUNTTOUMAPMOUNT(mp)->umapm_rootvp,
			UMAPVPTOLOWERVP(MOUNTTOUMAPMOUNT(mp)->umapm_rootvp)
			);
#endif

	/*
	 * Return locked reference to root.
	 */
	vp = MOUNTTOUMAPMOUNT(mp)->umapm_rootvp;
	VREF(vp);
D 13
	VOP_LOCK(vp);
E 13
I 13
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 13
	*vpp = vp;
D 6
	return 0;
E 6
I 6
	return (0);
E 6
}

int
umapfs_quotactl(mp, cmd, uid, arg, p)
	struct mount *mp;
	int cmd;
	uid_t uid;
	caddr_t arg;
	struct proc *p;
{
D 6
	return VFS_QUOTACTL(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, cmd, uid, arg, p);
E 6
I 6
	return (VFS_QUOTACTL(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, cmd, uid, arg, p));
E 6
}

int
umapfs_statfs(mp, sbp, p)
	struct mount *mp;
	struct statfs *sbp;
	struct proc *p;
{
	int error;
	struct statfs mstat;

#ifdef UMAPFS_DIAGNOSTIC
	printf("umapfs_statfs(mp = %x, vp = %x->%x)\n", mp,
			MOUNTTOUMAPMOUNT(mp)->umapm_rootvp,
			UMAPVPTOLOWERVP(MOUNTTOUMAPMOUNT(mp)->umapm_rootvp)
			);
#endif

	bzero(&mstat, sizeof(mstat));

	error = VFS_STATFS(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, &mstat, p);
	if (error)
		return (error);

	/* now copy across the "interesting" information and fake the rest */
	sbp->f_type = mstat.f_type;
	sbp->f_flags = mstat.f_flags;
	sbp->f_bsize = mstat.f_bsize;
	sbp->f_iosize = mstat.f_iosize;
	sbp->f_blocks = mstat.f_blocks;
	sbp->f_bfree = mstat.f_bfree;
	sbp->f_bavail = mstat.f_bavail;
	sbp->f_files = mstat.f_files;
	sbp->f_ffree = mstat.f_ffree;
	if (sbp != &mp->mnt_stat) {
		bcopy(&mp->mnt_stat.f_fsid, &sbp->f_fsid, sizeof(sbp->f_fsid));
		bcopy(mp->mnt_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->mnt_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
	}
	return (0);
}

int
umapfs_sync(mp, waitfor, cred, p)
	struct mount *mp;
	int waitfor;
	struct ucred *cred;
	struct proc *p;
{
	/*
	 * XXX - Assumes no data cached at umap layer.
	 */
	return (0);
}

int
umapfs_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{
	
D 6
	return VFS_VGET(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, ino, vpp);
E 6
I 6
	return (VFS_VGET(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, ino, vpp));
E 6
}

int
umapfs_fhtovp(mp, fidp, nam, vpp, exflagsp, credanonp)
	struct mount *mp;
	struct fid *fidp;
	struct mbuf *nam;
	struct vnode **vpp;
	int *exflagsp;
	struct ucred**credanonp;
{

D 6
	return VFS_FHTOVP(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, fidp, nam, vpp, exflagsp,credanonp);
E 6
I 6
	return (VFS_FHTOVP(MOUNTTOUMAPMOUNT(mp)->umapm_vfs, fidp, nam, vpp, exflagsp,credanonp));
E 6
}

int
umapfs_vptofh(vp, fhp)
	struct vnode *vp;
	struct fid *fhp;
{
D 6
	return VFS_VPTOFH(UMAPVPTOLOWERVP(vp), fhp);
E 6
I 6
	return (VFS_VPTOFH(UMAPVPTOLOWERVP(vp), fhp));
E 6
}

D 10
int umapfs_init __P((void));
E 10
I 10
int umapfs_init __P((struct vfsconf *));
#define umapfs_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
	    size_t, struct proc *)))eopnotsupp)
E 10

struct vfsops umap_vfsops = {
	umapfs_mount,
	umapfs_start,
	umapfs_unmount,
	umapfs_root,
	umapfs_quotactl,
	umapfs_statfs,
	umapfs_sync,
	umapfs_vget,
	umapfs_fhtovp,
	umapfs_vptofh,
	umapfs_init,
I 10
	umapfs_sysctl,
E 10
};
E 1
