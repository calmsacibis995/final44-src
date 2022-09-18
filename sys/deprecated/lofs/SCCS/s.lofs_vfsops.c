h08862
s 00000/00001/00302
d D 8.3 94/01/21 19:52:45 bostic 7 6
c copyright typo
e
s 00017/00054/00286
d D 8.2 94/01/05 12:30:34 pendry 6 5
c remove debug code, general cleanup.  KNF.
e
s 00002/00002/00338
d D 8.1 93/06/10 23:42:53 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00004/00339
d D 7.1 92/07/12 14:52:46 mckusick 4 3
c move to rev 7; new location; syntactic niggles
e
s 00022/00008/00321
d D 1.3 92/07/12 10:08:39 pendry 3 2
c new vop conventions
e
s 00001/00001/00328
d D 1.2 92/06/18 15:02:25 pendry 2 1
c don't call the sync routine on the underlying filesystem
e
s 00329/00000/00000
d D 1.1 92/06/03 14:19:09 pendry 1 0
c date and time created 92/06/03 14:19:09 by pendry
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
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
D 7
 * All rights reserved.
E 7
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: lofs_vfsops.c,v 1.9 1992/05/30 10:26:24 jsp Exp jsp $
 */

/*
 * Loopback Filesystem
 */

#include <sys/param.h>
#include <sys/systm.h>
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
#include <miscfs/lofs/lofs.h>
E 4

/*
 * Mount loopback copy of existing name space
 */
I 6
int
E 6
lofs_mount(mp, path, data, ndp, p)
	struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
D 3
	USES_VOP_UNLOCK;
E 3
	int error = 0;
	struct lofs_args args;
	struct vnode *vp;
	struct vnode *rootvp;
	struct lofsmount *amp;
	u_int size;

D 6
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_mount(mp = %x)\n", mp);
#endif

E 6
	/*
	 * Update is a no-op
	 */
D 6
	if (mp->mnt_flag & MNT_UPDATE) {
E 6
I 6
	if (mp->mnt_flag & MNT_UPDATE)
E 6
		return (EOPNOTSUPP);
D 6
		/* return VFS_MOUNT(VFSTOLOFS(mp)->looped_vfs, path, data, ndp, p);*/
	}
E 6

	/*
	 * Get argument
	 */
	if (error = copyin(data, (caddr_t)&args, sizeof(struct lofs_args)))
		return (error);

	/*
	 * Find target node
	 */
	NDINIT(ndp, LOOKUP, FOLLOW|WANTPARENT|LOCKLEAF,
		UIO_USERSPACE, args.target, p);
	if (error = namei(ndp))
		return (error);

	/*
	 * Sanity check on target vnode
	 */
	vp = ndp->ni_vp;
D 6
#ifdef LOFS_DIAGNOSTIC
	printf("vp = %x, check for VDIR...\n", vp);
#endif
E 6
	vrele(ndp->ni_dvp);
	ndp->ni_dvp = 0;

	if (vp->v_type != VDIR) {
		vput(vp);
		return (EINVAL);
	}

D 6
#ifdef LOFS_DIAGNOSTIC
	printf("mp = %x\n", mp);
#endif

E 6
	amp = (struct lofsmount *) malloc(sizeof(struct lofsmount),
				M_UFSMNT, M_WAITOK);	/* XXX */

	/*
	 * Save reference to underlying target FS
	 */
	amp->looped_vfs = vp->v_mount;

	/*
	 * Save reference.  Each mount also holds
	 * a reference on the root vnode.
	 */
	error = make_lofs(mp, &vp);
	/*
	 * Unlock the node (either the target or the alias)
	 */
	VOP_UNLOCK(vp);
	/*
	 * Make sure the node alias worked
	 */
	if (error) {
		vrele(vp);
		free(amp, M_UFSMNT);	/* XXX */
		return (error);
	}

	/*
	 * Keep a held reference to the root vnode.
	 * It is vrele'd in lofs_unmount.
	 */
	rootvp = vp;
	rootvp->v_flag |= VROOT;
	amp->rootvp = rootvp;
	if (LOFSVP(rootvp)->v_mount->mnt_flag & MNT_LOCAL)
		mp->mnt_flag |= MNT_LOCAL;
	mp->mnt_data = (qaddr_t) amp;
	getnewfsid(mp, MOUNT_LOFS);

	(void) copyinstr(path, mp->mnt_stat.f_mntonname, MNAMELEN - 1, &size);
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);
	(void) copyinstr(args.target, mp->mnt_stat.f_mntfromname, MNAMELEN - 1, 
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
D 6
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_mount: target %s, alias at %s\n",
		mp->mnt_stat.f_mntfromname, mp->mnt_stat.f_mntonname);
#endif
E 6
	return (0);
}

/*
 * VFS start.  Nothing needed here - the start routine
 * on the underlying filesystem will have been called
 * when that filesystem was mounted.
 */
I 6
int
E 6
lofs_start(mp, flags, p)
	struct mount *mp;
	int flags;
	struct proc *p;
{
I 6

E 6
	return (0);
D 6
	/* return VFS_START(VFSTOLOFS(mp)->looped_vfs, flags, p); */
E 6
}

/*
 * Free reference to looped FS
 */
I 6
int
E 6
lofs_unmount(mp, mntflags, p)
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
	struct vnode *rootvp = VFSTOLOFS(mp)->rootvp;
	int error;
	int flags = 0;
	extern int doforce;

D 6
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_unmount(mp = %x)\n", mp);
#endif

E 6
	if (mntflags & MNT_FORCE) {
		/* lofs can never be rootfs so don't check for it */
		if (!doforce)
			return (EINVAL);
		flags |= FORCECLOSE;
	}

	/*
	 * Clear out buffer cache.  I don't think we
	 * ever get anything cached at this level at the
	 * moment, but who knows...
	 */
D 3
	mntflushbuf(mp, 0); 
	if (mntinvalbuf(mp, 1))
		return (EBUSY);
E 3
I 3
D 4
	/* mntflushbuf(mp, 0);  */
	/* if (mntinvalbuf(mp, 1))
		return (EBUSY); */
E 4
E 3
	if (rootvp->v_usecount > 1)
		return (EBUSY);
	if (error = vflush(mp, rootvp, flags))
		return (error);

D 6
#ifdef LOFS_DIAGNOSTIC
E 6
	/*
D 6
	 * Flush any remaining vnode references
	 */
	lofs_flushmp(mp);
#endif

#ifdef LOFS_DIAGNOSTIC
	vprint("alias root of target", rootvp);
#endif	 
	/*
E 6
	 * Release reference on underlying root vnode
	 */
	vrele(rootvp);
	/*
	 * And blow it away for future re-use
	 */
	vgone(rootvp);
	/*
	 * Finally, throw away the lofsmount structure
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

I 6
int
E 6
lofs_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
D 3
	USES_VOP_LOCK;
E 3
	struct vnode *vp;

D 6
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_root(mp = %x, vp = %x->%x)\n", mp,
			VFSTOLOFS(mp)->rootvp,
			LOFSVP(VFSTOLOFS(mp)->rootvp)
			);
#endif

E 6
	/*
	 * Return locked reference to root.
	 */
	vp = VFSTOLOFS(mp)->rootvp;
	VREF(vp);
	VOP_LOCK(vp);
	*vpp = vp;
D 6
	return 0;
E 6
I 6
	return (0);
E 6
}

I 6
int
E 6
lofs_quotactl(mp, cmd, uid, arg, p)
	struct mount *mp;
	int cmd;
	uid_t uid;
	caddr_t arg;
	struct proc *p;
{
D 6
	return VFS_QUOTACTL(VFSTOLOFS(mp)->looped_vfs, cmd, uid, arg, p);
E 6
I 6
	return (VFS_QUOTACTL(VFSTOLOFS(mp)->looped_vfs, cmd, uid, arg, p));
E 6
}

I 6
int
E 6
lofs_statfs(mp, sbp, p)
	struct mount *mp;
	struct statfs *sbp;
	struct proc *p;
{
	int error;
	struct statfs mstat;

D 6
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_statfs(mp = %x, vp = %x->%x)\n", mp,
			VFSTOLOFS(mp)->rootvp,
			LOFSVP(VFSTOLOFS(mp)->rootvp)
			);
#endif

E 6
	bzero(&mstat, sizeof(mstat));

	error = VFS_STATFS(VFSTOLOFS(mp)->looped_vfs, &mstat, p);
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

I 6
int
E 6
lofs_sync(mp, waitfor)
struct mount *mp;
int waitfor;
{
D 2
	return VFS_SYNC(VFSTOLOFS(mp)->looped_vfs, waitfor);
E 2
I 2
	return (0);
E 2
}

D 3
lofs_fhtovp(mp, fhp, setgen, vpp)
E 3
I 3
/*
 * LOFS flat namespace lookup.
 * Currently unsupported.
 */
I 6
int
E 6
lofs_vget(mp, ino, vpp)
E 3
	struct mount *mp;
I 3
	ino_t ino;
	struct vnode **vpp;
{

	return (EOPNOTSUPP);
}

I 6
int
E 6
lofs_fhtovp(mp, fhp, nam, vpp, exflagsp, credanonp)
	register struct mount *mp;
E 3
	struct fid *fhp;
D 3
	int setgen;
E 3
I 3
	struct mbuf *nam;
E 3
	struct vnode **vpp;
I 3
	int *exflagsp;
	struct ucred **credanonp;
E 3
{
D 3
	return VFS_FHTOVP(VFSTOLOFS(mp)->looped_vfs, fhp, setgen, vpp);
E 3
I 3
D 6
	return VFS_FHTOVP(VFSTOLOFS(mp)->looped_vfs, fhp, nam, vpp, exflagsp, credanonp);
E 6
I 6
	return (VFS_FHTOVP(VFSTOLOFS(mp)->looped_vfs, fhp, nam, vpp, exflagsp, credanonp));
E 6
E 3
}

I 6
int
E 6
lofs_vptofh(vp, fhp)
	struct vnode *vp;
	struct fid *fhp;
{
D 6
	return VFS_VPTOFH(LOFSVP(vp), fhp);
E 6
I 6
	return (VFS_VPTOFH(LOFSVP(vp), fhp));
E 6
}
D 6

int lofs_init __P((void));
E 6

struct vfsops lofs_vfsops = {
	lofs_mount,
	lofs_start,
	lofs_unmount,
	lofs_root,
	lofs_quotactl,
	lofs_statfs,
	lofs_sync,
I 3
	lofs_vget,
E 3
	lofs_fhtovp,
	lofs_vptofh,
	lofs_init,
};
E 1
