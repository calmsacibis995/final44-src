h33479
s 00002/00002/00244
d D 8.11 95/05/14 00:42:43 mckusick 16 15
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00002/00244
d D 8.10 95/05/10 11:21:37 pendry 15 14
c VOP_REVOKE(vp, 0) should really be vgone(vp)
e
s 00001/00006/00245
d D 8.9 95/05/10 09:46:48 mckusick 14 13
c check for forcible unmount at syscall level
e
s 00016/00052/00235
d D 8.8 95/03/29 00:23:57 mckusick 13 12
c cleanups; getnewfsid => vfs_getnewfsid; add fdesc_sysctl
e
s 00001/00001/00286
d D 8.7 95/02/23 12:22:10 mckusick 12 9
c vgone => VOP_REVOKE
e
s 00001/00001/00286
d R 8.8 95/02/23 12:21:15 mckusick 11 10
c vgone => VOP_REVOKE
e
s 00001/00001/00286
d R 8.7 95/02/22 19:14:36 mckusick 10 9
c vgone => VOP_REVOKE
e
s 00000/00001/00287
d D 8.6 94/01/21 19:53:28 bostic 9 8
c copyright typo
e
s 00011/00041/00277
d D 8.5 94/01/05 12:12:52 pendry 8 7
c remove debug code.  KNF
e
s 00010/00011/00308
d D 8.4 94/01/04 21:38:40 bostic 7 6
c lint, KNF
e
s 00001/00011/00318
d D 8.3 94/01/04 21:35:56 bostic 6 5
c lint
e
s 00001/00001/00328
d D 8.2 94/01/04 06:54:33 pendry 5 4
c allocate private VT_ tags
e
s 00002/00002/00327
d D 8.1 93/06/10 23:46:40 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00004/00320
d D 7.1 92/07/12 15:18:53 mckusick 3 2
c move to rev 7; new include location; syntax niggles
e
s 00012/00001/00312
d D 1.2 92/07/12 09:02:19 pendry 2 1
c enter portal_vget
e
s 00313/00000/00000
d D 1.1 92/06/03 14:26:05 pendry 1 0
c date and time created 92/06/03 14:26:05 by pendry
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 4
I 4
D 15
 * Copyright (c) 1992, 1993
E 15
I 15
 * Copyright (c) 1992, 1993, 1995
E 15
 *	The Regents of the University of California.  All rights reserved.
E 4
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
 *
 * $Id: portal_vfsops.c,v 1.5 1992/05/30 10:25:27 jsp Exp jsp $
 */

/*
 * Portal Filesystem
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/proc.h>
D 3
/*#include <sys/resourcevar.h>*/
E 3
#include <sys/filedesc.h>
#include <sys/file.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/domain.h>
#include <sys/un.h>
D 3
#include <portal/portal.h>
E 3
I 3
#include <miscfs/portal/portal.h>
E 3

D 7
static u_short portal_mntid;

int portal_init()
E 7
I 7
int
D 13
portal_init()
E 13
I 13
portal_init(vfsp)
	struct vfsconf *vfsp;
E 13
E 7
{
I 3

E 3
D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_init\n");		/* printed during system boot */
#endif
E 8
I 8
	return (0);
E 8
}

/*
 * Mount the per-process file descriptors (/dev/fd)
 */
I 8
int
E 8
portal_mount(mp, path, data, ndp, p)
	struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
D 7
	int error = 0;
E 7
I 7
	struct file *fp;
E 7
	struct portal_args args;
D 7
	u_int size;
E 7
	struct portalmount *fmp;
D 7
	struct vnode *rvp;
D 6
	struct sockaddr_un *unp;
E 6
	struct file *fp;
E 7
	struct socket *so;
I 7
	struct vnode *rvp;
	u_int size;
	int error;
E 7
D 6
	char cfile[MAXPATHLEN];
E 6

D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_mount(mp = %x)\n", mp);
#endif

E 8
	/*
	 * Update is a no-op
	 */
	if (mp->mnt_flag & MNT_UPDATE)
		return (EOPNOTSUPP);

	if (error = copyin(data, (caddr_t) &args, sizeof(struct portal_args)))
		return (error);

	if (error = getsock(p->p_fd, args.pa_socket, &fp))
		return (error);
	so = (struct socket *) fp->f_data;
	if (so->so_proto->pr_domain->dom_family != AF_UNIX)
		return (ESOCKTNOSUPPORT);

D 5
	error = getnewvnode(VT_UFS, mp, portal_vnodeop_p, &rvp); /* XXX */
E 5
I 5
	error = getnewvnode(VT_PORTAL, mp, portal_vnodeop_p, &rvp); /* XXX */
E 5
	if (error)
		return (error);
	MALLOC(rvp->v_data, void *, sizeof(struct portalnode),
		M_TEMP, M_WAITOK);

	fmp = (struct portalmount *) malloc(sizeof(struct portalmount),
				 M_UFSMNT, M_WAITOK);	/* XXX */
	rvp->v_type = VDIR;
	rvp->v_flag |= VROOT;
	VTOPORTAL(rvp)->pt_arg = 0;
	VTOPORTAL(rvp)->pt_size = 0;
	VTOPORTAL(rvp)->pt_fileid = PORTAL_ROOTFILEID;
D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_mount: root vp = %x\n", rvp);
#endif
E 8
	fmp->pm_root = rvp;
	fmp->pm_server = fp; fp->f_count++;

	mp->mnt_flag |= MNT_LOCAL;
	mp->mnt_data = (qaddr_t) fmp;
D 13
	getnewfsid(mp, MOUNT_PORTAL);
E 13
I 13
	vfs_getnewfsid(mp);
E 13

D 7
	(void) copyinstr(path, mp->mnt_stat.f_mntonname, MNAMELEN - 1, &size);
E 7
I 7
	(void)copyinstr(path, mp->mnt_stat.f_mntonname, MNAMELEN - 1, &size);
E 7
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);
D 7
	(void) copyinstr(args.pa_config, mp->mnt_stat.f_mntfromname, MNAMELEN - 1,
		&size);
E 7
I 7
	(void)copyinstr(args.pa_config,
	    mp->mnt_stat.f_mntfromname, MNAMELEN - 1, &size);
E 7
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);

#ifdef notdef
	bzero(mp->mnt_stat.f_mntfromname, MNAMELEN);
	bcopy("portal", mp->mnt_stat.f_mntfromname, sizeof("portal"));
#endif

D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_mount: config %s at %s\n",
D 7
			mp->mnt_stat.f_mntfromname, mp->mnt_stat.f_mntonname);
E 7
I 7
	    mp->mnt_stat.f_mntfromname, mp->mnt_stat.f_mntonname);
E 7
#endif
E 8
	return (0);
}

I 8
int
E 8
portal_start(mp, flags, p)
	struct mount *mp;
	int flags;
	struct proc *p;
{
I 3

E 3
	return (0);
}

I 8
int
E 8
portal_unmount(mp, mntflags, p)
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
D 6
	int error;
	int flags = 0;
E 6
D 14
	extern int doforce;
E 14
	struct vnode *rootvp = VFSTOPORTAL(mp)->pm_root;
I 6
	int error, flags = 0;
E 6

D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_unmount(mp = %x)\n", mp);
#endif
E 8

D 14
	if (mntflags & MNT_FORCE) {
		/* portal can never be rootfs so don't check for it */
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
I 2
D 3
#if 0
E 3
I 3
#ifdef notyet
E 3
E 2
D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_unmount: calling mntflushbuf\n");
#endif
E 8
	mntflushbuf(mp, 0); 
D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_unmount: calling mntinvalbuf\n");
#endif
E 8
	if (mntinvalbuf(mp, 1))
		return (EBUSY);
I 2
#endif
E 2
	if (rootvp->v_usecount > 1)
		return (EBUSY);
D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_unmount: calling vflush\n");
#endif
E 8
	if (error = vflush(mp, rootvp, flags))
		return (error);

D 8
#ifdef PORTAL_DIAGNOSTIC
	vprint("portal root", rootvp);
#endif	 
E 8
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
	 * Shutdown the socket.  This will cause the select in the
	 * daemon to wake up, and then the accept will get ECONNABORTED
	 * which it interprets as a request to go and bury itself.
	 */
D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_unmount: shutdown socket\n");
#endif	 
E 8
	soshutdown((struct socket *) VFSTOPORTAL(mp)->pm_server->f_data, 2);
	/*
	 * Discard reference to underlying file.  Must call closef because
	 * this may be the last reference.
	 */
D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_unmount: closef(%x)\n", VFSTOPORTAL(mp)->pm_server);
#endif	 
E 8
	closef(VFSTOPORTAL(mp)->pm_server, (struct proc *) 0);
	/*
	 * Finally, throw away the portalmount structure
	 */
	free(mp->mnt_data, M_UFSMNT);	/* XXX */
	mp->mnt_data = 0;
D 3
	return 0;
E 3
I 3
	return (0);
E 3
}

I 8
int
E 8
portal_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
I 16
	struct proc *p = curproc;	/* XXX */
E 16
D 2
	USES_VOP_LOCK;
E 2
	struct vnode *vp;
D 6
	int error;
E 6

D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_root(mp = %x)\n", mp);
#endif
E 8
D 16

E 16
	/*
	 * Return locked reference to root.
	 */
	vp = VFSTOPORTAL(mp)->pm_root;
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

I 8
int
E 8
D 13
portal_quotactl(mp, cmd, uid, arg, p)
	struct mount *mp;
	int cmd;
	uid_t uid;
	caddr_t arg;
	struct proc *p;
{
I 3

E 3
	return (EOPNOTSUPP);
}

I 8
int
E 13
E 8
portal_statfs(mp, sbp, p)
	struct mount *mp;
	struct statfs *sbp;
	struct proc *p;
{
D 6
	struct filedesc *fdp;
	int lim;
	int i;
	int last;
	int freefd;

E 6
D 8
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_statfs(mp = %x)\n", mp);
#endif
E 8

D 13
	sbp->f_type = MOUNT_PORTAL;
E 13
	sbp->f_flags = 0;
	sbp->f_bsize = DEV_BSIZE;
	sbp->f_iosize = DEV_BSIZE;
	sbp->f_blocks = 2;		/* 1K to keep df happy */
	sbp->f_bfree = 0;
	sbp->f_bavail = 0;
	sbp->f_files = 1;		/* Allow for "." */
	sbp->f_ffree = 0;		/* See comments above */
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

I 8
D 13
int
E 8
portal_sync(mp, waitfor)
	struct mount *mp;
	int waitfor;
{
E 13
I 13
#define portal_fhtovp ((int (*) __P((struct mount *, struct fid *, \
	    struct mbuf *, struct vnode **, int *, struct ucred **)))eopnotsupp)
#define portal_quotactl ((int (*) __P((struct mount *, int, uid_t, caddr_t, \
	    struct proc *)))eopnotsupp)
#define portal_sync ((int (*) __P((struct mount *, int, struct ucred *, \
	    struct proc *)))nullop)
#define portal_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
	    size_t, struct proc *)))eopnotsupp)
#define portal_vget ((int (*) __P((struct mount *, ino_t, struct vnode **))) \
	    eopnotsupp)
#define portal_vptofh ((int (*) __P((struct vnode *, struct fid *)))eopnotsupp)
E 13
I 3

E 3
D 13
	return (0);
}

I 8
int
E 8
I 2
portal_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{

	return (EOPNOTSUPP);
}

I 8
int
E 8
E 2
portal_fhtovp(mp, fhp, vpp)
	struct mount *mp;
	struct fid *fhp;
	struct vnode **vpp;
{
I 3

E 3
	return (EOPNOTSUPP);
}

I 8
int
E 8
portal_vptofh(vp, fhp)
	struct vnode *vp;
	struct fid *fhp;
{
I 3

E 3
	return (EOPNOTSUPP);
}

E 13
struct vfsops portal_vfsops = {
	portal_mount,
	portal_start,
	portal_unmount,
	portal_root,
	portal_quotactl,
	portal_statfs,
	portal_sync,
I 2
	portal_vget,
E 2
	portal_fhtovp,
	portal_vptofh,
	portal_init,
I 13
	portal_sysctl,
E 13
};
E 1
