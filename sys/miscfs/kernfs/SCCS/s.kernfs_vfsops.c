h35105
s 00002/00001/00229
d D 8.10 95/05/14 00:40:51 mckusick 16 15
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00002/00228
d D 8.9 95/05/10 11:21:13 pendry 15 14
c VOP_REVOKE(vp, 0) should really be vgone(vp)
e
s 00001/00006/00229
d D 8.8 95/05/10 09:45:42 mckusick 14 13
c check for forcible unmount at syscall level
e
s 00006/00050/00229
d D 8.7 95/03/29 00:13:14 mckusick 13 12
c cleanups; getnewfsid => vfs_getnewfsid; add fdesc_sysctl
e
s 00001/00001/00278
d D 8.6 95/02/23 12:19:52 mckusick 12 10
c vgone => VOP_REVOKE
e
s 00001/00001/00278
d R 8.6 95/02/22 19:17:37 mckusick 11 10
c vgone => VOP_REVOKE
e
s 00019/00043/00260
d D 8.5 94/06/15 10:41:42 pendry 10 9
c merge netbsd modifications
e
s 00000/00001/00303
d D 8.4 94/01/21 19:56:25 bostic 9 8
c copyright typo
e
s 00000/00001/00304
d D 8.3 94/01/04 18:53:45 bostic 8 7
c lint
e
s 00001/00001/00304
d D 8.2 94/01/04 06:54:16 pendry 7 6
c allocate private VT_ tags
e
s 00002/00002/00303
d D 8.1 93/06/10 23:38:28 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00014/00302
d D 7.5 92/08/03 00:54:08 pendry 5 4
c clean up
e
s 00000/00001/00316
d D 7.4 92/08/01 04:23:09 pendry 4 3
c remove decl of spec_vnodeop_p
e
s 00053/00001/00264
d D 7.3 92/07/19 04:56:05 pendry 3 2
c added raw root device support to kernfs
e
s 00003/00003/00262
d D 7.2 92/07/18 17:09:24 pendry 2 1
c minor cleanup
e
s 00265/00000/00000
d D 7.1 92/07/18 16:42:23 pendry 1 0
c date and time created 92/07/18 16:42:23 by pendry
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 6
I 6
D 15
 * Copyright (c) 1992, 1993
E 15
I 15
 * Copyright (c) 1992, 1993, 1995
E 15
 *	The Regents of the University of California.  All rights reserved.
E 6
D 9
 * All rights reserved.
E 9
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Kernel params Filesystem
 */

#include <sys/param.h>
#include <sys/systm.h>
D 3
#include <sys/time.h>
E 3
I 3
#include <sys/conf.h>
E 3
#include <sys/types.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
I 3

#include <miscfs/specfs/specdev.h>
D 4
extern int (**spec_vnodeop_p)();
E 4
E 3
#include <miscfs/kernfs/kernfs.h>

I 3
D 10
struct vnode *rrootvp;
E 10
I 10
dev_t rrootdev = NODEV;
E 10

D 10
/*
 * Create a vnode for a character device.
 */
int
cdevvp(dev, vpp)
	dev_t dev;
	struct vnode **vpp;
E 10
I 10
D 13
kernfs_init()
E 13
I 13
kernfs_init(vfsp)
	struct vfsconf *vfsp;
E 13
E 10
{
D 10
	register struct vnode *vp;
	struct vnode *nvp;
	int error;
E 10

I 13
	return (0);
E 13
D 10
	if (dev == NODEV)
		return (0);
	error = getnewvnode(VT_NON, (struct mount *)0, spec_vnodeop_p, &nvp);
	if (error) {
		*vpp = 0;
		return (error);
	}
	vp = nvp;
	vp->v_type = VCHR;
	if (nvp = checkalias(vp, dev, (struct mount *)0)) {
		vput(vp);
		vp = nvp;
	}
	*vpp = vp;
	return (0);
E 10
}

E 3
D 10
kernfs_init()
E 10
I 10
void
kernfs_get_rrootdev()
E 10
{
I 10
	static int tried = 0;
E 10
I 3
	int cmaj;
D 10
	int bmaj = major(rootdev);
D 5
	int error = ENOENT;
E 5
I 5
	int error = ENXIO;
E 10
E 5

E 3
D 10
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_init\n");		/* printed during system boot */
#endif
E 10
I 10
	if (tried) {
		/* Already did it once. */
		return;
	}
	tried = 1;
E 10
I 3

I 10
	if (rootdev == NODEV)
		return;
E 10
	for (cmaj = 0; cmaj < nchrdev; cmaj++) {
D 10
		if (cdevsw[cmaj].d_open == bdevsw[bmaj].d_open) {
			dev_t cdev = makedev(cmaj, minor(rootdev));
			error = cdevvp(cdev, &rrootvp);
			if (error == 0)
				break;
		}
E 10
I 10
		rrootdev = makedev(cmaj, minor(rootdev));
		if (chrtoblk(rrootdev) == rootdev)
			return;
E 10
	}
D 10

	if (error) {
		printf("kernfs: no raw boot device\n");
		rrootvp = 0;
	}
E 10
I 10
	rrootdev = NODEV;
	printf("kernfs_get_rrootdev: no raw root device\n");
E 10
E 3
}

/*
 * Mount the Kernel params filesystem
 */
kernfs_mount(mp, path, data, ndp, p)
	struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
	int error = 0;
	u_int size;
	struct kernfs_mount *fmp;
	struct vnode *rvp;

#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_mount(mp = %x)\n", mp);
#endif

	/*
	 * Update is a no-op
	 */
	if (mp->mnt_flag & MNT_UPDATE)
		return (EOPNOTSUPP);

D 7
	error = getnewvnode(VT_UFS, mp, kernfs_vnodeop_p, &rvp);	/* XXX */
E 7
I 7
	error = getnewvnode(VT_KERNFS, mp, kernfs_vnodeop_p, &rvp);	/* XXX */
E 7
	if (error)
		return (error);

	MALLOC(fmp, struct kernfs_mount *, sizeof(struct kernfs_mount),
				M_UFSMNT, M_WAITOK);	/* XXX */
	rvp->v_type = VDIR;
	rvp->v_flag |= VROOT;
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_mount: root vp = %x\n", rvp);
#endif
	fmp->kf_root = rvp;
	mp->mnt_flag |= MNT_LOCAL;
	mp->mnt_data = (qaddr_t) fmp;
D 13
	getnewfsid(mp, MOUNT_KERNFS);
E 13
I 13
	vfs_getnewfsid(mp);
E 13

	(void) copyinstr(path, mp->mnt_stat.f_mntonname, MNAMELEN - 1, &size);
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);
	bzero(mp->mnt_stat.f_mntfromname, MNAMELEN);
	bcopy("kernfs", mp->mnt_stat.f_mntfromname, sizeof("kernfs"));
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_mount: at %s\n", mp->mnt_stat.f_mntonname);
#endif
I 10

	kernfs_get_rrootdev();
E 10
	return (0);
}

kernfs_start(mp, flags, p)
	struct mount *mp;
	int flags;
	struct proc *p;
{
	return (0);
}

kernfs_unmount(mp, mntflags, p)
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
	int error;
	int flags = 0;
D 14
	extern int doforce;
E 14
	struct vnode *rootvp = VFSTOKERNFS(mp)->kf_root;

#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_unmount(mp = %x)\n", mp);
#endif

D 14
	if (mntflags & MNT_FORCE) {
		/* kernfs can never be rootfs so don't check for it */
		if (!doforce)
			return (EINVAL);
E 14
I 14
	if (mntflags & MNT_FORCE)
E 14
		flags |= FORCECLOSE;
D 14
	}
E 14

	/*
	 * Clear out buffer cache.  I don't think we
	 * ever get anything cached at this level at the
	 * moment, but who knows...
	 */
D 5
#if 0
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_unmount: calling mntflushbuf\n");
#endif
D 2
	mntflushbuf(mp, 0); 
E 2
I 2
	mntflushbuf(mp, 0);
E 2
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_unmount: calling mntinvalbuf\n");
#endif
	if (mntinvalbuf(mp, 1))
		return (EBUSY);
#endif
E 5
	if (rootvp->v_usecount > 1)
		return (EBUSY);
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_unmount: calling vflush\n");
#endif
	if (error = vflush(mp, rootvp, flags))
		return (error);

#ifdef KERNFS_DIAGNOSTIC
	vprint("kernfs root", rootvp);
D 2
#endif	 
E 2
I 2
#endif
E 2
	/*
	 * Release reference on underlying root vnode
	 */
	vrele(rootvp);
	/*
	 * And blow it away for future re-use
	 */
D 12
	vgone(rootvp);
E 12
I 12
D 15
	VOP_REVOKE(rootvp, 0);
E 15
I 15
	vgone(rootvp);
E 15
E 12
	/*
	 * Finally, throw away the kernfs_mount structure
	 */
	free(mp->mnt_data, M_UFSMNT);	/* XXX */
	mp->mnt_data = 0;
	return 0;
}

kernfs_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
I 16
	struct proc *p = curproc;	/* XXX */
E 16
	struct vnode *vp;
D 8
	int error;
E 8

#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_root(mp = %x)\n", mp);
#endif

	/*
	 * Return locked reference to root.
	 */
	vp = VFSTOKERNFS(mp)->kf_root;
	VREF(vp);
D 16
	VOP_LOCK(vp);
E 16
I 16
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 16
	*vpp = vp;
	return (0);
}

D 13
kernfs_quotactl(mp, cmd, uid, arg, p)
	struct mount *mp;
	int cmd;
	uid_t uid;
	caddr_t arg;
	struct proc *p;
{
	return (EOPNOTSUPP);
}

E 13
kernfs_statfs(mp, sbp, p)
	struct mount *mp;
	struct statfs *sbp;
	struct proc *p;
{
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_statfs(mp = %x)\n", mp);
#endif

D 13
	sbp->f_type = MOUNT_KERNFS;
E 13
	sbp->f_flags = 0;
	sbp->f_bsize = DEV_BSIZE;
	sbp->f_iosize = DEV_BSIZE;
	sbp->f_blocks = 2;		/* 1K to keep df happy */
	sbp->f_bfree = 0;
	sbp->f_bavail = 0;
D 5
	sbp->f_files = 0;		/* Allow for "." */
	sbp->f_ffree = 0;		/* See comments above */
E 5
I 5
	sbp->f_files = 0;
	sbp->f_ffree = 0;
E 5
	if (sbp != &mp->mnt_stat) {
I 13
		sbp->f_type = mp->mnt_vfc->vfc_typenum;
E 13
		bcopy(&mp->mnt_stat.f_fsid, &sbp->f_fsid, sizeof(sbp->f_fsid));
		bcopy(mp->mnt_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->mnt_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
	}
	return (0);
}

D 13
kernfs_sync(mp, waitfor)
	struct mount *mp;
	int waitfor;
{
	return (0);
}

/*
D 2
 * Fdesc flat namespace lookup.
E 2
I 2
 * Kernfs flat namespace lookup.
E 2
 * Currently unsupported.
 */
kernfs_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{

	return (EOPNOTSUPP);
}


kernfs_fhtovp(mp, fhp, setgen, vpp)
	struct mount *mp;
	struct fid *fhp;
	int setgen;
	struct vnode **vpp;
{
	return (EOPNOTSUPP);
}

kernfs_vptofh(vp, fhp)
	struct vnode *vp;
	struct fid *fhp;
{
	return (EOPNOTSUPP);
}

E 13
struct vfsops kernfs_vfsops = {
	kernfs_mount,
	kernfs_start,
	kernfs_unmount,
	kernfs_root,
	kernfs_quotactl,
	kernfs_statfs,
	kernfs_sync,
	kernfs_vget,
	kernfs_fhtovp,
	kernfs_vptofh,
	kernfs_init,
I 13
	kernfs_sysctl,
E 13
};
E 1
