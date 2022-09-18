h39977
s 00002/00001/00222
d D 8.10 95/05/14 00:39:34 mckusick 19 18
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00002/00221
d D 8.9 95/05/10 11:21:03 pendry 18 17
c VOP_REVOKE(vp, 0) should really be vgone(vp)
e
s 00001/00006/00222
d D 8.8 95/05/10 09:40:12 mckusick 17 16
c check for forcible unmount at syscall level
e
s 00010/00000/00218
d D 8.7 95/04/03 18:37:41 mckusick 16 15
c move in definitions from fdesc.h
e
s 00003/00047/00215
d D 8.6 95/03/29 00:05:29 mckusick 15 14
c cleanups; getnewfsid => vfs_getnewfsid; add fdesc_sysctl
e
s 00001/00001/00261
d D 8.5 95/02/23 12:19:12 mckusick 14 12
c vgone => VOP_REVOKE
e
s 00001/00001/00261
d R 8.5 95/02/22 19:19:09 mckusick 13 12
c vgone => VOP_REVOKE
e
s 00000/00001/00262
d D 8.4 94/01/21 19:51:11 bostic 12 11
c copyright typo
e
s 00015/00051/00248
d D 8.3 94/01/05 12:03:21 pendry 11 10
c handle case where fdesc is mounted twice or more
c general cleanup, remove debug code, lint + KNF.
e
s 00000/00001/00299
d D 8.2 94/01/04 18:50:02 bostic 10 9
c lint
e
s 00002/00002/00298
d D 8.1 93/06/10 23:35:46 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00298
d D 7.4 93/04/29 23:46:39 pendry 8 7
c don't mark as a local filesystem
e
s 00005/00004/00294
d D 7.3 93/04/22 02:56:53 pendry 7 6
c merge in new version.
c this time it implements a subset of the /dev namespace
e
s 00001/00001/00297
d D 7.2 92/12/01 14:52:41 mckusick 6 5
c RLIMIT_OFILE => RLIMIT_NOFILE for compatibility with other UNIX's
e
s 00000/00000/00298
d D 7.1 92/07/12 14:53:50 mckusick 5 4
c move to rev 7
e
s 00001/00001/00297
d D 1.4 92/07/12 14:26:03 mckusick 4 3
c new location
e
s 00017/00001/00281
d D 1.3 92/07/12 09:23:50 pendry 3 2
c move fdesc_vget
e
s 00000/00015/00282
d D 1.2 92/06/03 14:25:14 pendry 2 1
c remove misc debug messages
e
s 00297/00000/00000
d D 1.1 92/06/03 14:01:18 pendry 1 0
c date and time created 92/06/03 14:01:18 by pendry
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 9
I 9
D 18
 * Copyright (c) 1992, 1993
E 18
I 18
 * Copyright (c) 1992, 1993, 1995
E 18
 *	The Regents of the University of California.  All rights reserved.
E 9
D 12
 * All rights reserved.
E 12
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 7
 * $Id: fdesc_vfsops.c,v 1.6 1992/05/30 10:25:59 jsp Exp jsp $
E 7
I 7
 * $Id: fdesc_vfsops.c,v 1.9 1993/04/06 15:28:33 jsp Exp $
E 7
 */

/*
 * /dev/fd Filesystem
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
#include <sys/filedesc.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
D 4
#include <fdesc/fdesc.h>
E 4
I 4
#include <miscfs/fdesc/fdesc.h>
E 4

D 7
static u_short fdesc_mntid;
E 7
I 7
D 11
dev_t devctty;
E 7

fdesc_init()
{
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_init\n");		/* printed during system boot */
#endif
I 7
	devctty = makedev(nchrdev, 0);
E 7
}

E 11
/*
 * Mount the per-process file descriptors (/dev/fd)
 */
I 11
int
E 11
fdesc_mount(mp, path, data, ndp, p)
	struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
	int error = 0;
	u_int size;
	struct fdescmount *fmp;
	struct vnode *rvp;

D 11
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_mount(mp = %x)\n", mp);
#endif

E 11
	/*
	 * Update is a no-op
	 */
	if (mp->mnt_flag & MNT_UPDATE)
		return (EOPNOTSUPP);

D 7
	error = getnewvnode(VT_UFS, mp, fdesc_vnodeop_p, &rvp);	/* XXX */
E 7
I 7
	error = fdesc_allocvp(Froot, FD_ROOT, mp, &rvp);
E 7
	if (error)
		return (error);

	MALLOC(fmp, struct fdescmount *, sizeof(struct fdescmount),
				M_UFSMNT, M_WAITOK);	/* XXX */
	rvp->v_type = VDIR;
	rvp->v_flag |= VROOT;
D 11
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_mount: root vp = %x\n", rvp);
#endif
E 11
	fmp->f_root = rvp;
D 8
	mp->mnt_flag |= MNT_LOCAL;
E 8
I 8
	/* XXX -- don't mark as local to work around fts() problems */
	/*mp->mnt_flag |= MNT_LOCAL;*/
E 8
	mp->mnt_data = (qaddr_t) fmp;
D 15
	getnewfsid(mp, MOUNT_FDESC);
E 15
I 15
	vfs_getnewfsid(mp);
E 15

	(void) copyinstr(path, mp->mnt_stat.f_mntonname, MNAMELEN - 1, &size);
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);
	bzero(mp->mnt_stat.f_mntfromname, MNAMELEN);
	bcopy("fdesc", mp->mnt_stat.f_mntfromname, sizeof("fdesc"));
D 11
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_mount: at %s\n", mp->mnt_stat.f_mntonname);
#endif
E 11
	return (0);
}

I 11
int
E 11
fdesc_start(mp, flags, p)
	struct mount *mp;
	int flags;
	struct proc *p;
{
	return (0);
}

I 11
int
E 11
fdesc_unmount(mp, mntflags, p)
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
	int error;
	int flags = 0;
D 17
	extern int doforce;
E 17
	struct vnode *rootvp = VFSTOFDESC(mp)->f_root;

D 11
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_unmount(mp = %x)\n", mp);
#endif

E 11
D 17
	if (mntflags & MNT_FORCE) {
		/* fdesc can never be rootfs so don't check for it */
		if (!doforce)
			return (EINVAL);
E 17
I 17
	if (mntflags & MNT_FORCE)
E 17
		flags |= FORCECLOSE;
D 17
	}
E 17

	/*
	 * Clear out buffer cache.  I don't think we
	 * ever get anything cached at this level at the
	 * moment, but who knows...
	 */
I 3
D 11
#if 0
E 3
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_unmount: calling mntflushbuf\n");
#endif
	mntflushbuf(mp, 0); 
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_unmount: calling mntinvalbuf\n");
#endif
	if (mntinvalbuf(mp, 1))
		return (EBUSY);
I 3
#endif
E 11
E 3
	if (rootvp->v_usecount > 1)
		return (EBUSY);
D 11
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_unmount: calling vflush\n");
#endif
E 11
	if (error = vflush(mp, rootvp, flags))
		return (error);

D 11
#ifdef FDESC_DIAGNOSTIC
	vprint("fdesc root", rootvp);
#endif	 
E 11
	/*
	 * Release reference on underlying root vnode
	 */
	vrele(rootvp);
	/*
	 * And blow it away for future re-use
	 */
D 14
	vgone(rootvp);
E 14
I 14
D 18
	VOP_REVOKE(rootvp, 0);
E 18
I 18
	vgone(rootvp);
E 18
E 14
	/*
	 * Finally, throw away the fdescmount structure
	 */
	free(mp->mnt_data, M_UFSMNT);	/* XXX */
	mp->mnt_data = 0;
D 11
	return 0;
E 11
I 11

	return (0);
E 11
}

I 11
int
E 11
fdesc_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
I 19
	struct proc *p = curproc;	/* XXX */
E 19
D 3
	USES_VOP_LOCK;
E 3
	struct vnode *vp;
D 10
	int error;
E 10

D 11
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_root(mp = %x)\n", mp);
#endif

E 11
	/*
	 * Return locked reference to root.
	 */
D 2
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_root: fdesc = %x\n", VFSTOFDESC(mp));
#endif
E 2
	vp = VFSTOFDESC(mp)->f_root;
D 2
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_root: root = %x\n", vp);
#endif
E 2
	VREF(vp);
D 2
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_root: calling VOP_LOCK\n");
#endif
E 2
D 19
	VOP_LOCK(vp);
E 19
I 19
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 19
D 2
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_root: back from VOP_LOCK\n");
#endif
E 2
	*vpp = vp;
D 2
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_root(mp = %x) = %x\n", mp, vp);
#endif
E 2
	return (0);
}

I 11
int
E 11
D 15
fdesc_quotactl(mp, cmd, uid, arg, p)
	struct mount *mp;
	int cmd;
	uid_t uid;
	caddr_t arg;
	struct proc *p;
{
I 11

E 11
	return (EOPNOTSUPP);
}

I 11
int
E 15
E 11
fdesc_statfs(mp, sbp, p)
	struct mount *mp;
	struct statfs *sbp;
	struct proc *p;
{
	struct filedesc *fdp;
	int lim;
	int i;
	int last;
	int freefd;

D 11
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_statfs(mp = %x)\n", mp);
#endif

E 11
	/*
	 * Compute number of free file descriptors.
	 * [ Strange results will ensue if the open file
	 * limit is ever reduced below the current number
	 * of open files... ]
	 */
D 6
	lim = p->p_rlimit[RLIMIT_OFILE].rlim_cur;
E 6
I 6
	lim = p->p_rlimit[RLIMIT_NOFILE].rlim_cur;
E 6
	fdp = p->p_fd;
	last = min(fdp->fd_nfiles, lim);
	freefd = 0;
	for (i = fdp->fd_freefile; i < last; i++)
		if (fdp->fd_ofiles[i] == NULL)
			freefd++;

	/*
	 * Adjust for the fact that the fdesc array may not
	 * have been fully allocated yet.
	 */
	if (fdp->fd_nfiles < lim)
		freefd += (lim - fdp->fd_nfiles);

D 15
	sbp->f_type = MOUNT_FDESC;
E 15
	sbp->f_flags = 0;
	sbp->f_bsize = DEV_BSIZE;
	sbp->f_iosize = DEV_BSIZE;
	sbp->f_blocks = 2;		/* 1K to keep df happy */
	sbp->f_bfree = 0;
	sbp->f_bavail = 0;
	sbp->f_files = lim + 1;		/* Allow for "." */
	sbp->f_ffree = freefd;		/* See comments above */
	if (sbp != &mp->mnt_stat) {
I 15
		sbp->f_type = mp->mnt_vfc->vfc_typenum;
E 15
		bcopy(&mp->mnt_stat.f_fsid, &sbp->f_fsid, sizeof(sbp->f_fsid));
		bcopy(mp->mnt_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->mnt_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
	}
	return (0);
}

I 11
int
E 11
fdesc_sync(mp, waitfor)
	struct mount *mp;
	int waitfor;
{
I 11

E 11
	return (0);
}

I 16
#define fdesc_fhtovp ((int (*) __P((struct mount *, struct fid *, \
	    struct mbuf *, struct vnode **, int *, struct ucred **)))eopnotsupp)
#define fdesc_quotactl ((int (*) __P((struct mount *, int, uid_t, caddr_t, \
	    struct proc *)))eopnotsupp)
#define fdesc_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
	    size_t, struct proc *)))eopnotsupp)
#define fdesc_vget ((int (*) __P((struct mount *, ino_t, struct vnode **))) \
	    eopnotsupp)
#define fdesc_vptofh ((int (*) __P((struct vnode *, struct fid *)))eopnotsupp)

E 16
I 3
D 15
/*
 * Fdesc flat namespace lookup.
 * Currently unsupported.
 */
I 11
int
E 11
fdesc_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{

	return (EOPNOTSUPP);
}

D 11

E 11
I 11
int
E 11
E 3
fdesc_fhtovp(mp, fhp, setgen, vpp)
	struct mount *mp;
	struct fid *fhp;
	int setgen;
	struct vnode **vpp;
{
	return (EOPNOTSUPP);
}

I 11
int
E 11
fdesc_vptofh(vp, fhp)
	struct vnode *vp;
	struct fid *fhp;
{
I 11

E 11
	return (EOPNOTSUPP);
}

E 15
struct vfsops fdesc_vfsops = {
	fdesc_mount,
	fdesc_start,
	fdesc_unmount,
	fdesc_root,
	fdesc_quotactl,
	fdesc_statfs,
	fdesc_sync,
I 3
	fdesc_vget,
E 3
	fdesc_fhtovp,
	fdesc_vptofh,
	fdesc_init,
I 15
	fdesc_sysctl,
E 15
};
E 1
