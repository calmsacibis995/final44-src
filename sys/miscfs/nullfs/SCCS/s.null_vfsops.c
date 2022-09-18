h14690
s 00004/00002/00337
d D 8.7 95/05/14 00:42:03 mckusick 15 14
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00002/00337
d D 8.6 95/05/10 11:21:26 pendry 14 13
c VOP_REVOKE(vp, 0) should really be vgone(vp)
e
s 00001/00006/00338
d D 8.5 95/05/10 09:46:20 mckusick 13 12
c check for forcible unmount at syscall level
e
s 00006/00002/00338
d D 8.4 95/03/29 00:19:56 mckusick 12 11
c cleanups; getnewfsid => vfs_getnewfsid; add fdesc_sysctl
e
s 00001/00001/00339
d D 8.3 95/02/23 12:20:37 mckusick 11 9
c vgone => VOP_REVOKE
e
s 00001/00001/00339
d R 8.3 95/02/22 19:18:29 mckusick 10 9
c vgone => VOP_REVOKE
e
s 00000/00001/00340
d D 8.2 94/01/21 19:54:24 bostic 9 8
c copyright typo
e
s 00002/00002/00339
d D 8.1 93/06/10 23:46:09 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00340
d D 7.1 92/07/12 15:10:49 mckusick 7 6
c move to rev 7; new include location; misc syntax niggles
e
s 00009/00031/00332
d D 1.6 92/07/11 15:24:16 heideman 6 5
c cleanup
e
s 00007/00007/00356
d D 1.5 92/07/10 23:17:44 heideman 5 4
c No refcount problems, but no caching.
e
s 00041/00017/00322
d D 1.4 92/07/10 13:46:24 heideman 4 3
c a working version: it does nothing, correctly
e
s 00023/00013/00316
d D 1.3 92/07/07 17:46:37 johnh 3 2
c first draft
e
s 00069/00069/00260
d D 1.2 92/07/07 14:07:45 johnh 2 1
c the great variable renaming
e
s 00329/00000/00000
d D 1.1 92/07/07 13:54:37 johnh 1 0
c date and time created 92/07/07 13:54:37 by johnh
e
u
U
f e 0
t
T
I 1
/*
D 8
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 8
I 8
D 14
 * Copyright (c) 1992, 1993
E 14
I 14
 * Copyright (c) 1992, 1993, 1995
E 14
 *	The Regents of the University of California.  All rights reserved.
E 8
D 9
 * All rights reserved.
E 9
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
D 2
 *	@(#)lofs_vfsops.c	1.2 (Berkeley) 6/18/92
E 2
I 2
D 3
 *	@(#)null_vfsops.c	1.2 (Berkeley) 6/18/92
E 3
I 3
 *	%W% (Berkeley) %G%
E 3
E 2
 *
D 2
 * $Id: lofs_vfsops.c,v 1.9 1992/05/30 10:26:24 jsp Exp jsp $
E 2
I 2
D 3
 * $Id: null_vfsops.c,v 1.9 1992/05/30 10:26:24 jsp Exp jsp $
E 3
I 3
 * @(#)lofs_vfsops.c	1.2 (Berkeley) 6/18/92
 * $Id: lofs_vfsops.c,v 1.9 1992/05/30 10:26:24 jsp Exp jsp $
E 3
E 2
 */

/*
D 2
 * Loopback Filesystem
E 2
I 2
D 3
 * Null layer Filesystem
E 3
I 3
 * Null Layer
 * (See null_vnops.c for a description of what this does.)
E 3
E 2
 */

#include <sys/param.h>
#include <sys/systm.h>
I 15
#include <sys/proc.h>
E 15
#include <sys/time.h>
#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
D 4
#include <lofs/lofs.h>
E 4
I 4
D 7
#include <nullfs/null.h>
E 7
I 7
#include <miscfs/nullfs/null.h>
E 7
E 4

/*
D 3
 * Mount loopback copy of existing name space
E 3
I 3
 * Mount null layer
E 3
 */
I 4
int
E 4
D 2
lofs_mount(mp, path, data, ndp, p)
E 2
I 2
nullfs_mount(mp, path, data, ndp, p)
E 2
	struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
D 4
	USES_VOP_UNLOCK;
E 4
	int error = 0;
D 2
	struct lofs_args args;
E 2
I 2
	struct null_args args;
E 2
D 3
	struct vnode *vp;
E 3
I 3
	struct vnode *lowerrootvp, *vp;
E 3
D 2
	struct vnode *rootvp;
	struct lofsmount *amp;
E 2
I 2
	struct vnode *nullm_rootvp;
D 6
	struct null_mount *amp;
E 6
I 6
	struct null_mount *xmp;
E 6
E 2
	u_int size;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_mount(mp = %x)\n", mp);
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("nullfs_mount(mp = %x)\n", mp);
E 2
#endif

	/*
	 * Update is a no-op
	 */
	if (mp->mnt_flag & MNT_UPDATE) {
		return (EOPNOTSUPP);
D 2
		/* return VFS_MOUNT(VFSTOLOFS(mp)->looped_vfs, path, data, ndp, p);*/
E 2
I 2
		/* return VFS_MOUNT(MOUNTTONULLMOUNT(mp)->nullm_vfs, path, data, ndp, p);*/
E 2
	}

	/*
	 * Get argument
	 */
D 2
	if (error = copyin(data, (caddr_t)&args, sizeof(struct lofs_args)))
E 2
I 2
	if (error = copyin(data, (caddr_t)&args, sizeof(struct null_args)))
E 2
		return (error);

	/*
D 5
	 * Find target node
E 5
I 5
	 * Find lower node
E 5
	 */
	NDINIT(ndp, LOOKUP, FOLLOW|WANTPARENT|LOCKLEAF,
		UIO_USERSPACE, args.target, p);
	if (error = namei(ndp))
		return (error);

	/*
D 5
	 * Sanity check on target vnode
E 5
I 5
	 * Sanity check on lower vnode
E 5
	 */
D 3
	vp = ndp->ni_vp;
E 3
I 3
	lowerrootvp = ndp->ni_vp;
E 3
D 2
#ifdef LOFS_DIAGNOSTIC
E 2
I 2
D 6
#ifdef NULLFS_DIAGNOSTIC
E 2
D 3
	printf("vp = %x, check for VDIR...\n", vp);
E 3
I 3
	printf("vp = %x, check for VDIR...\n", lowerrootvp);
E 3
#endif
E 6
I 6

E 6
	vrele(ndp->ni_dvp);
D 6
	ndp->ni_dvp = 0;
E 6
I 6
	ndp->ni_dvp = NULL;
E 6

D 3
	if (vp->v_type != VDIR) {
		vput(vp);
E 3
I 3
D 6
	/*
D 5
	 * NEEDSWORK: Is this really bad, or just not
E 5
I 5
	 * NEEDSWORK: Is this check really necessary, or just not
E 5
	 * the way it's been?
	 */
	if (lowerrootvp->v_type != VDIR) {
		vput(lowerrootvp);
E 3
		return (EINVAL);
	}

D 2
#ifdef LOFS_DIAGNOSTIC
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
E 2
	printf("mp = %x\n", mp);
#endif

D 2
	amp = (struct lofsmount *) malloc(sizeof(struct lofsmount),
E 2
I 2
	amp = (struct null_mount *) malloc(sizeof(struct null_mount),
E 6
I 6
	xmp = (struct null_mount *) malloc(sizeof(struct null_mount),
E 6
E 2
				M_UFSMNT, M_WAITOK);	/* XXX */

	/*
D 5
	 * Save reference to underlying target FS
E 5
I 5
D 6
	 * Save reference to underlying lower FS
E 6
I 6
	 * Save reference to underlying FS
E 6
E 5
	 */
D 2
	amp->looped_vfs = vp->v_mount;
E 2
I 2
D 3
	amp->nullm_vfs = vp->v_mount;
E 3
I 3
D 6
	amp->nullm_vfs = lowerrootvp->v_mount;
E 6
I 6
	xmp->nullm_vfs = lowerrootvp->v_mount;
E 6
E 3
E 2

	/*
	 * Save reference.  Each mount also holds
	 * a reference on the root vnode.
	 */
D 2
	error = make_lofs(mp, &vp);
E 2
I 2
D 3
	error = make_null_node(mp, &vp);
E 3
I 3
D 4
	error = make_null_node(mp, lowerrootvp, &vp);
E 4
I 4
	error = null_node_create(mp, lowerrootvp, &vp);
E 4
E 3
E 2
	/*
D 5
	 * Unlock the node (either the target or the alias)
E 5
I 5
	 * Unlock the node (either the lower or the alias)
E 5
	 */
D 15
	VOP_UNLOCK(vp);
E 15
I 15
	VOP_UNLOCK(vp, 0, p);
E 15
	/*
	 * Make sure the node alias worked
	 */
	if (error) {
D 3
		vrele(vp);
E 3
I 3
		vrele(lowerrootvp);
E 3
D 6
		free(amp, M_UFSMNT);	/* XXX */
E 6
I 6
		free(xmp, M_UFSMNT);	/* XXX */
E 6
		return (error);
	}

	/*
	 * Keep a held reference to the root vnode.
D 2
	 * It is vrele'd in lofs_unmount.
E 2
I 2
	 * It is vrele'd in nullfs_unmount.
E 2
	 */
D 2
	rootvp = vp;
	rootvp->v_flag |= VROOT;
	amp->rootvp = rootvp;
	if (LOFSVP(rootvp)->v_mount->mnt_flag & MNT_LOCAL)
E 2
I 2
	nullm_rootvp = vp;
	nullm_rootvp->v_flag |= VROOT;
D 6
	amp->nullm_rootvp = nullm_rootvp;
E 6
I 6
	xmp->nullm_rootvp = nullm_rootvp;
E 6
D 4
	if (NULLTOLOWERVP(nullm_rootvp)->v_mount->mnt_flag & MNT_LOCAL)
E 4
I 4
	if (NULLVPTOLOWERVP(nullm_rootvp)->v_mount->mnt_flag & MNT_LOCAL)
E 4
E 2
		mp->mnt_flag |= MNT_LOCAL;
D 6
	mp->mnt_data = (qaddr_t) amp;
E 6
I 6
	mp->mnt_data = (qaddr_t) xmp;
E 6
D 12
	getnewfsid(mp, MOUNT_LOFS);
E 12
I 12
	vfs_getnewfsid(mp);
E 12

	(void) copyinstr(path, mp->mnt_stat.f_mntonname, MNAMELEN - 1, &size);
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);
	(void) copyinstr(args.target, mp->mnt_stat.f_mntfromname, MNAMELEN - 1, 
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_mount: target %s, alias at %s\n",
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
D 5
	printf("nullfs_mount: target %s, alias at %s\n",
E 5
I 5
	printf("nullfs_mount: lower %s, alias at %s\n",
E 5
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
I 4
int
E 4
D 2
lofs_start(mp, flags, p)
E 2
I 2
nullfs_start(mp, flags, p)
E 2
	struct mount *mp;
	int flags;
	struct proc *p;
{
	return (0);
D 2
	/* return VFS_START(VFSTOLOFS(mp)->looped_vfs, flags, p); */
E 2
I 2
	/* return VFS_START(MOUNTTONULLMOUNT(mp)->nullm_vfs, flags, p); */
E 2
}

/*
D 3
 * Free reference to looped FS
E 3
I 3
 * Free reference to null layer
E 3
 */
I 4
int
E 4
D 2
lofs_unmount(mp, mntflags, p)
E 2
I 2
nullfs_unmount(mp, mntflags, p)
E 2
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
D 2
	struct vnode *rootvp = VFSTOLOFS(mp)->rootvp;
E 2
I 2
	struct vnode *nullm_rootvp = MOUNTTONULLMOUNT(mp)->nullm_rootvp;
E 2
	int error;
	int flags = 0;
D 13
	extern int doforce;
E 13

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_unmount(mp = %x)\n", mp);
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("nullfs_unmount(mp = %x)\n", mp);
E 2
#endif

D 13
	if (mntflags & MNT_FORCE) {
		/* lofs can never be rootfs so don't check for it */
		if (!doforce)
			return (EINVAL);
E 13
I 13
	if (mntflags & MNT_FORCE)
E 13
		flags |= FORCECLOSE;
D 13
	}
E 13

	/*
	 * Clear out buffer cache.  I don't think we
	 * ever get anything cached at this level at the
	 * moment, but who knows...
	 */
I 4
#if 0
E 4
	mntflushbuf(mp, 0); 
	if (mntinvalbuf(mp, 1))
		return (EBUSY);
I 4
#endif
E 4
D 2
	if (rootvp->v_usecount > 1)
E 2
I 2
	if (nullm_rootvp->v_usecount > 1)
E 2
		return (EBUSY);
D 2
	if (error = vflush(mp, rootvp, flags))
E 2
I 2
	if (error = vflush(mp, nullm_rootvp, flags))
E 2
		return (error);
D 6

D 2
#ifdef LOFS_DIAGNOSTIC
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
E 2
	/*
	 * Flush any remaining vnode references
	 */
D 2
	lofs_flushmp(mp);
E 2
I 2
	null_node_flushmp (mp);
E 2
#endif
E 6

D 2
#ifdef LOFS_DIAGNOSTIC
	vprint("alias root of target", rootvp);
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
D 5
	vprint("alias root of target", nullm_rootvp);
E 5
I 5
	vprint("alias root of lower", nullm_rootvp);
E 5
E 2
#endif	 
	/*
	 * Release reference on underlying root vnode
	 */
D 2
	vrele(rootvp);
E 2
I 2
	vrele(nullm_rootvp);
E 2
	/*
	 * And blow it away for future re-use
	 */
D 2
	vgone(rootvp);
E 2
I 2
D 11
	vgone(nullm_rootvp);
E 11
I 11
D 14
	VOP_REVOKE(nullm_rootvp, 0);
E 14
I 14
	vgone(nullm_rootvp);
E 14
E 11
E 2
	/*
D 2
	 * Finally, throw away the lofsmount structure
E 2
I 2
	 * Finally, throw away the null_mount structure
E 2
	 */
	free(mp->mnt_data, M_UFSMNT);	/* XXX */
	mp->mnt_data = 0;
	return 0;
}

I 4
int
E 4
D 2
lofs_root(mp, vpp)
E 2
I 2
nullfs_root(mp, vpp)
E 2
	struct mount *mp;
	struct vnode **vpp;
{
I 15
	struct proc *p = curproc;	/* XXX */
E 15
D 4
	USES_VOP_LOCK;
E 4
	struct vnode *vp;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_root(mp = %x, vp = %x->%x)\n", mp,
			VFSTOLOFS(mp)->rootvp,
			LOFSVP(VFSTOLOFS(mp)->rootvp)
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("nullfs_root(mp = %x, vp = %x->%x)\n", mp,
			MOUNTTONULLMOUNT(mp)->nullm_rootvp,
D 4
			NULLTOLOWERVP(MOUNTTONULLMOUNT(mp)->nullm_rootvp)
E 4
I 4
			NULLVPTOLOWERVP(MOUNTTONULLMOUNT(mp)->nullm_rootvp)
E 4
E 2
			);
#endif

	/*
	 * Return locked reference to root.
	 */
D 2
	vp = VFSTOLOFS(mp)->rootvp;
E 2
I 2
	vp = MOUNTTONULLMOUNT(mp)->nullm_rootvp;
E 2
	VREF(vp);
D 15
	VOP_LOCK(vp);
E 15
I 15
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 15
	*vpp = vp;
	return 0;
}

I 4
int
E 4
D 2
lofs_quotactl(mp, cmd, uid, arg, p)
E 2
I 2
nullfs_quotactl(mp, cmd, uid, arg, p)
E 2
	struct mount *mp;
	int cmd;
	uid_t uid;
	caddr_t arg;
	struct proc *p;
{
D 2
	return VFS_QUOTACTL(VFSTOLOFS(mp)->looped_vfs, cmd, uid, arg, p);
E 2
I 2
	return VFS_QUOTACTL(MOUNTTONULLMOUNT(mp)->nullm_vfs, cmd, uid, arg, p);
E 2
}

I 4
int
E 4
D 2
lofs_statfs(mp, sbp, p)
E 2
I 2
nullfs_statfs(mp, sbp, p)
E 2
	struct mount *mp;
	struct statfs *sbp;
	struct proc *p;
{
	int error;
	struct statfs mstat;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_statfs(mp = %x, vp = %x->%x)\n", mp,
			VFSTOLOFS(mp)->rootvp,
			LOFSVP(VFSTOLOFS(mp)->rootvp)
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("nullfs_statfs(mp = %x, vp = %x->%x)\n", mp,
			MOUNTTONULLMOUNT(mp)->nullm_rootvp,
D 4
			NULLTOLOWERVP(MOUNTTONULLMOUNT(mp)->nullm_rootvp)
E 4
I 4
			NULLVPTOLOWERVP(MOUNTTONULLMOUNT(mp)->nullm_rootvp)
E 4
E 2
			);
#endif

	bzero(&mstat, sizeof(mstat));

D 2
	error = VFS_STATFS(VFSTOLOFS(mp)->looped_vfs, &mstat, p);
E 2
I 2
	error = VFS_STATFS(MOUNTTONULLMOUNT(mp)->nullm_vfs, &mstat, p);
E 2
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

D 2
lofs_sync(mp, waitfor)
E 2
I 2
D 4
nullfs_sync(mp, waitfor)
E 2
struct mount *mp;
int waitfor;
E 4
I 4
int
nullfs_sync(mp, waitfor, cred, p)
	struct mount *mp;
	int waitfor;
	struct ucred *cred;
	struct proc *p;
E 4
{
I 3
	/*
D 4
	 * NEEDSWORK: Assumes no data cached at null layer.
	 * Is this true?
E 4
I 4
	 * XXX - Assumes no data cached at null layer.
E 4
	 */
E 3
	return (0);
}

D 2
lofs_fhtovp(mp, fhp, setgen, vpp)
E 2
I 2
D 4
nullfs_fhtovp(mp, fhp, setgen, vpp)
E 4
I 4
int
nullfs_vget(mp, ino, vpp)
E 4
E 2
	struct mount *mp;
D 4
	struct fid *fhp;
	int setgen;
E 4
I 4
	ino_t ino;
E 4
	struct vnode **vpp;
{
D 2
	return VFS_FHTOVP(VFSTOLOFS(mp)->looped_vfs, fhp, setgen, vpp);
E 2
I 2
D 4
	return VFS_FHTOVP(MOUNTTONULLMOUNT(mp)->nullm_vfs, fhp, setgen, vpp);
E 4
I 4
	
	return VFS_VGET(MOUNTTONULLMOUNT(mp)->nullm_vfs, ino, vpp);
E 4
E 2
}

I 4
int
nullfs_fhtovp(mp, fidp, nam, vpp, exflagsp, credanonp)
	struct mount *mp;
	struct fid *fidp;
	struct mbuf *nam;
	struct vnode **vpp;
	int *exflagsp;
	struct ucred**credanonp;
{

	return VFS_FHTOVP(MOUNTTONULLMOUNT(mp)->nullm_vfs, fidp, nam, vpp, exflagsp,credanonp);
}

int
E 4
D 2
lofs_vptofh(vp, fhp)
E 2
I 2
nullfs_vptofh(vp, fhp)
E 2
	struct vnode *vp;
	struct fid *fhp;
{
D 2
	return VFS_VPTOFH(LOFSVP(vp), fhp);
E 2
I 2
D 4
	return VFS_VPTOFH(NULLTOLOWERVP(vp), fhp);
E 4
I 4
	return VFS_VPTOFH(NULLVPTOLOWERVP(vp), fhp);
E 4
E 2
}

D 2
int lofs_init __P((void));
E 2
I 2
D 12
int nullfs_init __P((void));
E 12
I 12
int nullfs_init __P((struct vfsconf *));
E 12
E 2

I 12
#define nullfs_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
	    size_t, struct proc *)))eopnotsupp)

E 12
D 2
struct vfsops lofs_vfsops = {
	lofs_mount,
	lofs_start,
	lofs_unmount,
	lofs_root,
	lofs_quotactl,
	lofs_statfs,
	lofs_sync,
	lofs_fhtovp,
	lofs_vptofh,
	lofs_init,
E 2
I 2
struct vfsops null_vfsops = {
	nullfs_mount,
	nullfs_start,
	nullfs_unmount,
	nullfs_root,
	nullfs_quotactl,
	nullfs_statfs,
	nullfs_sync,
I 4
	nullfs_vget,
E 4
	nullfs_fhtovp,
	nullfs_vptofh,
	nullfs_init,
I 12
	nullfs_sysctl,
E 12
E 2
};
E 1
