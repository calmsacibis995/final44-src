h42534
s 00001/00006/00166
d D 8.7 95/05/10 09:47:18 mckusick 7 6
c check for forcible unmount at syscall level
e
s 00017/00048/00155
d D 8.6 95/03/29 00:36:25 mckusick 6 5
c cleanups; getnewfsid => vfs_getnewfsid; add sysctl
e
s 00001/00015/00202
d D 8.5 94/06/15 12:30:53 pendry 5 4
c merge in netbsd changes.
c security fixes, curproc becomes symlink, misc other trash.
e
s 00002/00002/00215
d D 8.4 94/01/21 19:59:10 bostic 4 3
c copyright typo
e
s 00000/00001/00217
d D 8.3 94/01/17 14:43:06 pendry 3 2
c lint
e
s 00002/00002/00216
d D 8.2 94/01/06 10:01:17 pendry 2 1
c fix name of filesystem for "df"
e
s 00218/00000/00000
d D 8.1 94/01/05 12:34:12 pendry 1 0
c date and time created 94/01/05 12:34:12 by pendry
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1993 The Regents of the University of California.
E 4
 * Copyright (c) 1993 Jan-Simon Pendry
D 4
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * From:
 *	$Id: procfs_vfsops.c,v 3.1 1993/12/15 09:40:17 jsp Exp $
 */

/*
 * procfs VFS interface
 */

#include <sys/param.h>
I 6
#include <sys/systm.h>
E 6
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/syslog.h>
#include <sys/mount.h>
#include <sys/signalvar.h>
#include <sys/vnode.h>
#include <miscfs/procfs/procfs.h>
#include <vm/vm.h>			/* for PAGE_SIZE */

/*
 * VFS Operations.
 *
 * mount system call
 */
/* ARGSUSED */
procfs_mount(mp, path, data, ndp, p)
	struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
	u_int size;
D 3
	int error;
E 3

	if (UIO_MX & (UIO_MX-1)) {
		log(LOG_ERR, "procfs: invalid directory entry size");
		return (EINVAL);
	}

	if (mp->mnt_flag & MNT_UPDATE)
		return (EOPNOTSUPP);

	mp->mnt_flag |= MNT_LOCAL;
	mp->mnt_data = 0;
D 6
	getnewfsid(mp, MOUNT_PROCFS);
E 6
I 6
	vfs_getnewfsid(mp);
E 6

	(void) copyinstr(path, (caddr_t)mp->mnt_stat.f_mntonname, MNAMELEN, &size);
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);

D 2
	size = sizeof("proc") - 1;
	bcopy("proc", mp->mnt_stat.f_mntfromname, size);
E 2
I 2
	size = sizeof("procfs") - 1;
	bcopy("procfs", mp->mnt_stat.f_mntfromname, size);
E 2
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);

	return (0);
}

/*
 * unmount system call
 */
procfs_unmount(mp, mntflags, p)
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
	int error;
D 7
	extern int doforce;
E 7
	int flags = 0;

D 7
	if (mntflags & MNT_FORCE) {
		/* procfs can never be rootfs so don't check for it */
		if (!doforce)
			return (EINVAL);
E 7
I 7
	if (mntflags & MNT_FORCE)
E 7
		flags |= FORCECLOSE;
D 7
	}
E 7

	if (error = vflush(mp, 0, flags))
		return (error);

	return (0);
}

procfs_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
D 5
	struct pfsnode *pfs;
	struct vnode *vp;
	int error;
E 5

D 5
	error = procfs_allocvp(mp, &vp, (pid_t) 0, Proot);
	if (error)
		return (error);

	vp->v_type = VDIR;
	vp->v_flag = VROOT;
	pfs = VTOPFS(vp);

	*vpp = vp;
	return (0);
E 5
I 5
	return (procfs_allocvp(mp, vpp, 0, Proot));
E 5
}

D 5
/*
 */
E 5
/* ARGSUSED */
procfs_start(mp, flags, p)
	struct mount *mp;
	int flags;
	struct proc *p;
{

	return (0);
}

/*
 * Get file system statistics.
 */
procfs_statfs(mp, sbp, p)
	struct mount *mp;
	struct statfs *sbp;
	struct proc *p;
{
D 6
	sbp->f_type = MOUNT_PROCFS;
E 6
	sbp->f_bsize = PAGE_SIZE;
	sbp->f_iosize = PAGE_SIZE;
	sbp->f_blocks = 1;	/* avoid divide by zero in some df's */
	sbp->f_bfree = 0;
	sbp->f_bavail = 0;
	sbp->f_files = maxproc;			/* approx */
	sbp->f_ffree = maxproc - nprocs;	/* approx */

	if (sbp != &mp->mnt_stat) {
I 6
		sbp->f_type = mp->mnt_vfc->vfc_typenum;
E 6
		bcopy(&mp->mnt_stat.f_fsid, &sbp->f_fsid, sizeof(sbp->f_fsid));
		bcopy(mp->mnt_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->mnt_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
	}

	return (0);
}

D 6

procfs_quotactl(mp, cmds, uid, arg, p)
	struct mount *mp;
	int cmds;
	uid_t uid;
	caddr_t arg;
	struct proc *p;
E 6
I 6
procfs_init(vfsp)
	struct vfsconf *vfsp;
E 6
{

D 6
	return (EOPNOTSUPP);
}

procfs_sync(mp, waitfor)
	struct mount *mp;
	int waitfor;
{

E 6
	return (0);
}

D 6
procfs_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{
E 6
I 6
#define procfs_fhtovp ((int (*) __P((struct mount *, struct fid *, \
	    struct mbuf *, struct vnode **, int *, struct ucred **)))einval)
#define procfs_quotactl ((int (*) __P((struct mount *, int, uid_t, caddr_t, \
	    struct proc *)))eopnotsupp)
#define procfs_sync ((int (*) __P((struct mount *, int, struct ucred *, \
	    struct proc *)))nullop)
#define procfs_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
	    size_t, struct proc *)))eopnotsupp)
#define procfs_vget ((int (*) __P((struct mount *, ino_t, struct vnode **))) \
	    eopnotsupp)
#define procfs_vptofh ((int (*) __P((struct vnode *, struct fid *)))einval)
E 6

D 6
	return (EOPNOTSUPP);
}

procfs_fhtovp(mp, fhp, vpp)
	struct mount *mp;
	struct fid *fhp;
	struct vnode **vpp;
{

	return (EINVAL);
}

procfs_vptofh(vp, fhp)
	struct vnode *vp;
	struct fid *fhp;
{

	return EINVAL;
}

procfs_init()
{

	return (0);
}

E 6
struct vfsops procfs_vfsops = {
	procfs_mount,
	procfs_start,
	procfs_unmount,
	procfs_root,
	procfs_quotactl,
	procfs_statfs,
	procfs_sync,
	procfs_vget,
	procfs_fhtovp,
	procfs_vptofh,
	procfs_init,
I 6
	procfs_sysctl,
E 6
};
E 1
