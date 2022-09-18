h04474
s 00019/00018/00906
d D 8.17 95/05/22 23:06:59 mckusick 32 31
c follow proper locking protocol
e
s 00002/00000/00922
d D 8.16 95/05/21 18:03:03 mckusick 31 30
c inactive routine must unlock node
e
s 00010/00008/00912
d D 8.15 95/05/14 00:39:34 mckusick 30 29
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00000/00918
d D 8.14 95/04/03 18:37:58 mckusick 29 28
c add revoke operator
e
s 00017/00037/00901
d D 8.13 95/03/29 00:05:30 mckusick 28 27
c cleanups; getnewfsid => vfs_getnewfsid; add fdesc_sysctl
e
s 00012/00032/00926
d D 8.12 94/08/20 15:53:49 mckusick 27 26
c update to use queue.h
e
s 00003/00003/00955
d D 8.11 94/07/21 13:59:00 pendry 26 25
c change the way directories are reported.
c don't fake them into fifos any more - instead twiddle the x bits off.
c this is to prevent fts/ls from getting too confused.
e
s 00010/00000/00948
d D 8.10 94/06/04 19:33:19 mckusick 25 24
c add cookie and eofflag parameters to readdir
e
s 00000/00001/00948
d D 8.9 94/01/21 19:51:12 bostic 24 23
c copyright typo
e
s 00037/00000/00912
d D 8.8 94/01/14 08:29:30 pendry 23 22
c add pathconf entry point
e
s 00091/00119/00821
d D 8.7 94/01/05 12:03:22 pendry 22 21
c handle case where fdesc is mounted twice or more
c general cleanup, remove debug code, lint + KNF.
e
s 00000/00001/00940
d D 8.6 94/01/04 18:50:03 bostic 21 20
c lint
e
s 00001/00001/00940
d D 8.5 94/01/04 06:54:09 pendry 20 19
c allocate private VT_ tags
e
s 00001/00001/00940
d D 8.4 93/12/30 16:17:21 mckusick 19 18
c vget now locks optionally
e
s 00001/00001/00940
d D 8.3 93/09/23 16:42:00 bostic 18 17
c changes for 4.4BSD-Lite requested by USL
e
s 00004/00004/00937
d D 8.2 93/08/15 14:05:56 mckusick 17 16
c fixes from Mike Hibler
e
s 00002/00002/00939
d D 8.1 93/06/18 17:08:54 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00940
d D 7.9 93/06/18 17:08:26 mckusick 15 13
c lint
e
s 00002/00002/00939
d R 8.1 93/06/10 23:35:50 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00006/00920
d D 7.8 93/04/30 01:12:19 pendry 13 12
c add support for stat on socket descriptors
e
s 00007/00000/00919
d D 7.7 93/04/30 00:34:22 pendry 12 11
c don't allow directories to show up in /dev/fd
e
s 00006/00002/00913
d D 7.6 93/04/28 16:15:33 pendry 11 10
c fix vnode allocation once more
e
s 00002/00002/00913
d D 7.5 93/04/28 15:23:44 mckusick 10 9
c have to vget vnodes with zero references
e
s 00468/00077/00447
d D 7.4 93/04/22 02:56:54 pendry 9 8
c merge in new version.
c this time it implements a subset of the /dev namespace
e
s 00001/00001/00523
d D 7.3 93/03/11 07:44:53 pendry 8 7
c ignore setattr on sockets, instead of reporting an error.
e
s 00003/00004/00521
d D 7.2 92/07/13 15:50:21 pendry 7 6
c fix typos
e
s 00000/00000/00525
d D 7.1 92/07/12 14:53:51 mckusick 6 5
c move to rev 7
e
s 00073/00032/00452
d D 1.5 92/07/12 14:33:06 mckusick 5 4
c misc syntactic cleanups
e
s 00005/00003/00479
d D 1.4 92/07/12 10:08:06 pendry 4 3
c remove private dir structure
e
s 00001/00005/00481
d D 1.3 92/07/12 09:23:52 pendry 3 2
c move fdesc_vget
e
s 00049/00045/00437
d D 1.2 92/06/18 15:01:21 pendry 2 1
c local variables
e
s 00482/00000/00000
d D 1.1 92/06/03 14:01:18 pendry 1 0
c date and time created 92/06/03 14:01:18 by pendry
e
u
U
t
T
I 1
/*
D 16
 * Copyright (c) 1992 The Regents of the University of California
D 9
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 9
I 9
 * Copyright (c) 1990, 1992, 1993 Jan-Simon Pendry
E 16
I 16
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
E 9
D 24
 * All rights reserved.
E 24
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 9
 * $Id: fdesc_vnops.c,v 1.7 1992/05/30 10:05:34 jsp Exp jsp $
E 9
I 9
 * $Id: fdesc_vnops.c,v 1.12 1993/04/06 16:17:17 jsp Exp $
E 9
 */

/*
 * /dev/fd Filesystem
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/proc.h>
I 9
#include <sys/kernel.h>	/* boottime */
E 9
#include <sys/resourcevar.h>
#include <sys/filedesc.h>
#include <sys/vnode.h>
#include <sys/malloc.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/buf.h>
I 4
#include <sys/dirent.h>
E 4
D 5
#include <fdesc/fdesc.h>
E 5
I 5
#include <miscfs/fdesc/fdesc.h>
E 5

I 9
D 18
#define cttyvp(p) ((p)->p_flag&SCTTY ? (p)->p_session->s_ttyvp : NULL)
E 18
I 18
#define cttyvp(p) ((p)->p_flag & P_CONTROLT ? (p)->p_session->s_ttyvp : NULL)
E 18

#define FDL_WANT	0x01
#define FDL_LOCKED	0x02
D 22
static int fdescvplock;
static struct vnode *fdescvp[FD_MAX];
E 22
I 22
static int fdcache_lock;
E 22

I 22
dev_t devctty;

E 22
#if (FD_STDIN != FD_STDOUT-1) || (FD_STDOUT != FD_STDERR-1)
FD_STDIN, FD_STDOUT, FD_STDERR must be a sequence n, n+1, n+2
#endif

I 22
D 27
#define	NFDCACHE 3
#define	FD_NHASH(ix) ((ix) & NFDCACHE)
E 27
I 27
#define	NFDCACHE 4
E 27

D 27
/*
 * Cache head
 */
struct fdcache {
	struct fdescnode	*fc_forw;
	struct fdescnode	*fc_back;
};
E 27
I 27
#define FD_NHASH(ix) \
	(&fdhashtbl[(ix) & fdhash])
LIST_HEAD(fdhashhead, fdescnode) *fdhashtbl;
u_long fdhash;
E 27

D 27
static struct fdcache fdcache[NFDCACHE];

E 27
/*
 * Initialise cache headers
 */
D 28
fdesc_init()
E 28
I 28
fdesc_init(vfsp)
	struct vfsconf *vfsp;
E 28
{
D 27
	struct fdcache *fc;
E 27

	devctty = makedev(nchrdev, 0);
D 27

	for (fc = fdcache; fc < fdcache + NFDCACHE; fc++)
		fc->fc_forw = fc->fc_back = (struct fdescnode *) fc;
E 27
I 27
	fdhashtbl = hashinit(NFDCACHE, M_CACHE, &fdhash);
E 27
}

D 27
/*
 * Compute hash list for given target vnode
 */
static struct fdcache *
fdesc_hash(ix)
	int ix;
{

	return (&fdcache[FD_NHASH(ix)]);
}

E 27
int
E 22
fdesc_allocvp(ftype, ix, mp, vpp)
	fdntype ftype;
	int ix;
	struct mount *mp;
	struct vnode **vpp;
{
I 30
	struct proc *p = curproc;	/* XXX */
E 30
D 22
	struct vnode **nvpp = 0;
E 22
I 22
D 27
	struct fdcache *fc;
E 27
I 27
	struct fdhashhead *fc;
E 27
	struct fdescnode *fd;
E 22
	int error = 0;

I 27
	fc = FD_NHASH(ix);
E 27
I 11
loop:
E 11
D 22
	/* get stashed copy of the vnode */
	if (ix >= 0 && ix < FD_MAX) {
		nvpp = &fdescvp[ix];
D 10
		if (*nvpp) {
E 10
I 10
D 11
		if (*nvpp && vget(*nvpp) == 0) {
E 11
I 11
		if (*nvpp) {
D 19
			if (vget(*nvpp))
E 19
I 19
			if (vget(*nvpp, 1))
E 22
I 22
D 27
	fc = fdesc_hash(ix);
	for (fd = fc->fc_forw; fd != (struct fdescnode *) fc; fd = fd->fd_forw) {
E 27
I 27
	for (fd = fc->lh_first; fd != 0; fd = fd->fd_hash.le_next) {
E 27
		if (fd->fd_ix == ix && fd->fd_vnode->v_mount == mp) {
D 30
			if (vget(fd->fd_vnode, 0))
E 30
I 30
			if (vget(fd->fd_vnode, 0, p))
E 30
E 22
E 19
				goto loop;
E 11
D 22
			VOP_UNLOCK(*nvpp);
E 10
			*vpp = *nvpp;
E 22
I 22
			*vpp = fd->fd_vnode;
E 22
D 10
			VREF(*nvpp);
E 10
			return (error);
		}
	}

	/*
	 * otherwise lock the array while we call getnewvnode
	 * since that can block.
	 */ 
D 11
	while (fdescvplock & FDL_LOCKED) {
E 11
I 11
D 22
	if (fdescvplock & FDL_LOCKED) {
E 11
		fdescvplock |= FDL_WANT;
		sleep((caddr_t) &fdescvplock, PINOD);
E 22
I 22
	if (fdcache_lock & FDL_LOCKED) {
		fdcache_lock |= FDL_WANT;
		sleep((caddr_t) &fdcache_lock, PINOD);
E 22
I 11
		goto loop;
E 11
	}
D 22
	fdescvplock |= FDL_LOCKED;
E 22
I 22
	fdcache_lock |= FDL_LOCKED;
E 22

D 20
	error = getnewvnode(VT_UFS, mp, fdesc_vnodeop_p, vpp);
E 20
I 20
	error = getnewvnode(VT_FDESC, mp, fdesc_vnodeop_p, vpp);
E 20
	if (error)
		goto out;
D 22
	MALLOC((*vpp)->v_data, void *, sizeof(struct fdescnode), M_TEMP, M_WAITOK);
	if (nvpp)
		*nvpp = *vpp;
	VTOFDESC(*vpp)->fd_type = ftype;
	VTOFDESC(*vpp)->fd_fd = -1;
	VTOFDESC(*vpp)->fd_link = 0;
	VTOFDESC(*vpp)->fd_ix = ix;
E 22
I 22
	MALLOC(fd, void *, sizeof(struct fdescnode), M_TEMP, M_WAITOK);
	(*vpp)->v_data = fd;
	fd->fd_vnode = *vpp;
	fd->fd_type = ftype;
	fd->fd_fd = -1;
	fd->fd_link = 0;
	fd->fd_ix = ix;
D 27
	fc = fdesc_hash(ix);
	insque(fd, fc);
E 27
I 27
	LIST_INSERT_HEAD(fc, fd, fd_hash);
E 27
E 22

out:;
D 22
	fdescvplock &= ~FDL_LOCKED;
E 22
I 22
	fdcache_lock &= ~FDL_LOCKED;
E 22

D 22
	if (fdescvplock & FDL_WANT) {
		fdescvplock &= ~FDL_WANT;
		wakeup((caddr_t) &fdescvplock);
E 22
I 22
	if (fdcache_lock & FDL_WANT) {
		fdcache_lock &= ~FDL_WANT;
		wakeup((caddr_t) &fdcache_lock);
E 22
	}

	return (error);
}

E 9
/*
 * vp is the current namei directory
 * ndp is the name to locate in that directory...
 */
I 22
int
E 22
D 5
fdesc_lookup (ap)
	struct vop_lookup_args *ap;
E 5
I 5
fdesc_lookup(ap)
	struct vop_lookup_args /* {
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
	} */ *ap;
E 5
{
D 3
	/*USES_VOP_LOCK;*/
E 3
I 2
	struct vnode **vpp = ap->a_vpp;
	struct vnode *dvp = ap->a_dvp;
E 2
D 32
	char *pname;
	struct proc *p;
	int nfiles;
E 32
I 32
	struct componentname *cnp = ap->a_cnp;
	char *pname = cnp->cn_nameptr;
	struct proc *p = cnp->cn_proc;
	int nfiles = p->p_fd->fd_nfiles;
E 32
	unsigned fd;
	int error;
	struct vnode *fvp;
I 9
	char *ln;
E 9

D 22
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_lookup(%x)\n", ap);
D 2
	printf("fdesc_lookup(dp = %x, vpp = %x, cnp = %x)\n", ap->a_dvp, ap->a_vpp, ap->a_cnp);
E 2
I 2
	printf("fdesc_lookup(dp = %x, vpp = %x, cnp = %x)\n", dvp, vpp, ap->a_cnp);
E 2
#endif
E 22
D 32
	pname = ap->a_cnp->cn_nameptr;
D 22
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_lookup(%s)\n", pname);
#endif
E 22
	if (ap->a_cnp->cn_namelen == 1 && *pname == '.') {
E 32
I 32
	VOP_UNLOCK(dvp, 0, p);
	if (cnp->cn_namelen == 1 && *pname == '.') {
E 32
D 2
		*ap->a_vpp = ap->a_dvp;
		VREF(ap->a_dvp);	
		/*VOP_LOCK(ap->a_dvp);*/
E 2
I 2
		*vpp = dvp;
		VREF(dvp);	
D 9
		/*VOP_LOCK(dvp);*/
E 9
I 9
D 30
		VOP_LOCK(dvp);
E 30
I 30
D 32
		vn_lock(dvp, LK_EXCLUSIVE | LK_RETRY, p);
E 32
I 32
		vn_lock(dvp, LK_SHARED | LK_RETRY, p);
E 32
E 30
E 9
E 2
		return (0);
	}

D 32
	p = ap->a_cnp->cn_proc;
	nfiles = p->p_fd->fd_nfiles;

E 32
D 9
	fd = 0;
	while (*pname >= '0' && *pname <= '9') {
		fd = 10 * fd + *pname++ - '0';
		if (fd >= nfiles)
E 9
I 9
	switch (VTOFDESC(dvp)->fd_type) {
	default:
	case Flink:
	case Fdesc:
	case Fctty:
		error = ENOTDIR;
		goto bad;

	case Froot:
D 32
		if (ap->a_cnp->cn_namelen == 2 && bcmp(pname, "fd", 2) == 0) {
E 32
I 32
		if (cnp->cn_namelen == 2 && bcmp(pname, "fd", 2) == 0) {
E 32
			error = fdesc_allocvp(Fdevfd, FD_DEVFD, dvp->v_mount, &fvp);
			if (error)
				goto bad;
			*vpp = fvp;
			fvp->v_type = VDIR;
D 30
			VOP_LOCK(fvp);
E 30
I 30
D 32
			vn_lock(fvp, LK_EXCLUSIVE | LK_RETRY, p);
E 32
I 32
			vn_lock(fvp, LK_SHARED | LK_RETRY, p);
E 32
E 30
D 22
#ifdef FDESC_DIAGNOSTIC
			printf("fdesc_lookup: newvp = %x\n", fvp);
#endif
E 22
			return (0);
		}

D 32
		if (ap->a_cnp->cn_namelen == 3 && bcmp(pname, "tty", 3) == 0) {
E 32
I 32
		if (cnp->cn_namelen == 3 && bcmp(pname, "tty", 3) == 0) {
E 32
			struct vnode *ttyvp = cttyvp(p);
			if (ttyvp == NULL) {
				error = ENXIO;
				goto bad;
			}
			error = fdesc_allocvp(Fctty, FD_CTTY, dvp->v_mount, &fvp);
			if (error)
				goto bad;
			*vpp = fvp;
			fvp->v_type = VFIFO;
D 30
			VOP_LOCK(fvp);
E 30
I 30
D 32
			vn_lock(fvp, LK_EXCLUSIVE | LK_RETRY, p);
E 32
I 32
			vn_lock(fvp, LK_SHARED | LK_RETRY, p);
E 32
E 30
D 22
#ifdef FDESC_DIAGNOSTIC
			printf("fdesc_lookup: ttyvp = %x\n", fvp);
#endif
E 22
			return (0);
		}

		ln = 0;
D 32
		switch (ap->a_cnp->cn_namelen) {
E 32
I 32
		switch (cnp->cn_namelen) {
E 32
		case 5:
			if (bcmp(pname, "stdin", 5) == 0) {
				ln = "fd/0";
				fd = FD_STDIN;
			}
E 9
			break;
D 9
	}
E 9
I 9
		case 6:
			if (bcmp(pname, "stdout", 6) == 0) {
				ln = "fd/1";
				fd = FD_STDOUT;
			} else
			if (bcmp(pname, "stderr", 6) == 0) {
				ln = "fd/2";
				fd = FD_STDERR;
			}
			break;
		}
E 9

I 9
		if (ln) {
E 9
D 22
#ifdef FDESC_DIAGNOSTIC
D 9
	printf("fdesc_lookup: fd = %d, *pname = %x\n", fd, *pname);
E 9
I 9
			printf("fdesc_lookup: link -> %s\n", ln);
E 9
#endif
E 22
D 2
	if (*pname == '/') {
		error = ENOTDIR;
		goto bad;
	}

E 2
D 9
	if (*pname != '\0') {
		error = ENOENT;
		goto bad;
	}
E 9
I 9
			error = fdesc_allocvp(Flink, fd, dvp->v_mount, &fvp);
			if (error)
				goto bad;
			VTOFDESC(fvp)->fd_link = ln;
			*vpp = fvp;
			fvp->v_type = VLNK;
D 30
			VOP_LOCK(fvp);
E 30
I 30
D 32
			vn_lock(fvp, LK_EXCLUSIVE | LK_RETRY, p);
E 32
I 32
			vn_lock(fvp, LK_SHARED | LK_RETRY, p);
E 32
E 30
D 22
#ifdef FDESC_DIAGNOSTIC
			printf("fdesc_lookup: newvp = %x\n", fvp);
#endif
E 22
			return (0);
		} else {
			error = ENOENT;
			goto bad;
		}
E 9

D 9
	if (fd >= nfiles || p->p_fd->fd_ofiles[fd] == NULL) {
		error = EBADF;
		goto bad;
	}
E 9
I 9
D 22
		/* fall through */
E 22
I 22
		/* FALL THROUGH */
E 22
E 9

I 9
	case Fdevfd:
D 32
		if (ap->a_cnp->cn_namelen == 2 && bcmp(pname, "..", 2) == 0) {
			error = fdesc_root(dvp->v_mount, vpp);
			return (error);
E 32
I 32
		if (cnp->cn_namelen == 2 && bcmp(pname, "..", 2) == 0) {
			if (error = fdesc_root(dvp->v_mount, vpp))
				goto bad;
			return (0);
E 32
		}

		fd = 0;
		while (*pname >= '0' && *pname <= '9') {
			fd = 10 * fd + *pname++ - '0';
			if (fd >= nfiles)
				break;
		}

E 9
D 22
#ifdef FDESC_DIAGNOSTIC
D 9
	printf("fdesc_lookup: allocate new vnode\n");
E 9
I 9
		printf("fdesc_lookup: fd = %d, *pname = %x\n", fd, *pname);
E 9
#endif
E 22
D 2
	error = getnewvnode(VT_UFS, ap->a_dvp->v_mount, fdesc_vnodeop_p, &fvp);
E 2
I 2
D 9
	error = getnewvnode(VT_UFS, dvp->v_mount, fdesc_vnodeop_p, &fvp);
E 2
	if (error)
		goto bad;
	MALLOC(fvp->v_data, void *, sizeof(struct fdescnode), M_TEMP, M_WAITOK);
	VTOFDESC(fvp)->f_fd = fd;
D 7
	/*VTOFDESC(fvp)->f_isroot = 0;*/
E 7
D 2
	*ap->a_vpp = fvp;
E 2
I 2
	*vpp = fvp;
E 9
I 9
		if (*pname != '\0') {
			error = ENOENT;
			goto bad;
		}

		if (fd >= nfiles || p->p_fd->fd_ofiles[fd] == NULL) {
			error = EBADF;
			goto bad;
		}

E 9
E 2
D 22
#ifdef FDESC_DIAGNOSTIC
D 9
	printf("fdesc_lookup: newvp = %x\n", fvp);
E 9
I 9
		printf("fdesc_lookup: allocate new vnode\n");
E 9
#endif
E 22
D 9
	return (0);
E 9
I 9
		error = fdesc_allocvp(Fdesc, FD_DESC+fd, dvp->v_mount, &fvp);
		if (error)
			goto bad;
		VTOFDESC(fvp)->fd_fd = fd;
I 32
		vn_lock(fvp, LK_SHARED | LK_RETRY, p);
E 32
		*vpp = fvp;
D 22
#ifdef FDESC_DIAGNOSTIC
		printf("fdesc_lookup: newvp = %x\n", fvp);
#endif
E 22
		return (0);
	}
E 9

bad:;
I 32
	vn_lock(dvp, LK_SHARED | LK_RETRY, p);
E 32
D 2
	*ap->a_vpp = NULL;
E 2
I 2
	*vpp = NULL;
E 2
D 22
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_lookup: error = %d\n", error);
#endif
E 22
	return (error);
}

I 22
int
E 22
D 5
fdesc_open (ap)
	struct vop_open_args *ap;
E 5
I 5
fdesc_open(ap)
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 5
{
I 2
	struct vnode *vp = ap->a_vp;
I 9
	int error = 0;
E 9

E 2
D 9
	/*
	 * Can always open the root (modulo perms)
	 */
D 2
	if (ap->a_vp->v_flag & VROOT)
E 2
I 2
	if (vp->v_flag & VROOT)
E 2
		return (0);
E 9
I 9
	switch (VTOFDESC(vp)->fd_type) {
	case Fdesc:
		/*
		 * XXX Kludge: set p->p_dupfd to contain the value of the
		 * the file descriptor being sought for duplication. The error 
		 * return ensures that the vnode for this device will be
		 * released by vn_open. Open will detect this special error and
		 * take the actions in dupfdopen.  Other callers of vn_open or
		 * VOP_OPEN will simply report the error.
		 */
		ap->a_p->p_dupfd = VTOFDESC(vp)->fd_fd;	/* XXX */
		error = ENODEV;
		break;
E 9

D 9
	/*
	 * XXX Kludge: set ap->a_p->p_dupfd to contain the value of the
	 * the file descriptor being sought for duplication. The error 
	 * return ensures that the vnode for this device will be released
	 * by vn_open. Open will detect this special error and take the
	 * actions in dupfdopen.  Other callers of vn_open or VOP_OPEN
	 * will simply report the error.
	 */
D 2
	ap->a_p->p_dupfd = VTOFDESC(ap->a_vp)->f_fd;	/* XXX */
E 2
I 2
	ap->a_p->p_dupfd = VTOFDESC(vp)->f_fd;	/* XXX */
E 2
	return (ENODEV);
E 9
I 9
	case Fctty:
		error = cttyopen(devctty, ap->a_mode, 0, ap->a_p);
		break;
	}

	return (error);
E 9
}

static int
fdesc_attr(fd, vap, cred, p)
	int fd;
	struct vattr *vap;
	struct ucred *cred;
	struct proc *p;
{
D 3
	USES_VOP_GETATTR;
E 3
	struct filedesc *fdp = p->p_fd;
	struct file *fp;
I 13
	struct stat stb;
E 13
	int error;

D 22
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_attr: fd = %d, nfiles = %d\n", fd, fdp->fd_nfiles);
#endif
	if (fd >= fdp->fd_nfiles || (fp = fdp->fd_ofiles[fd]) == NULL) {
#ifdef FDESC_DIAGNOSTIC
		printf("fdesc_attr: fp = %x (EBADF)\n", fp);
#endif
E 22
I 22
	if (fd >= fdp->fd_nfiles || (fp = fdp->fd_ofiles[fd]) == NULL)
E 22
		return (EBADF);
D 22
	}
E 22

D 13
	/*
	 * Can stat the underlying vnode, but not sockets because
	 * they don't use struct vattrs.  Well, we could convert from
	 * a struct stat back to a struct vattr, later...
	 */
E 13
	switch (fp->f_type) {
	case DTYPE_VNODE:
		error = VOP_GETATTR((struct vnode *) fp->f_data, vap, cred, p);
I 12
		if (error == 0 && vap->va_type == VDIR) {
			/*
D 26
			 * don't allow directories to show up because
			 * that causes loops in the namespace.
E 26
I 26
			 * directories can cause loops in the namespace,
			 * so turn off the 'x' bits to avoid trouble.
E 26
			 */
D 26
			vap->va_type = VFIFO;
E 26
I 26
			vap->va_mode &= ~((VEXEC)|(VEXEC>>3)|(VEXEC>>6));
E 26
		}
E 12
		break;

	case DTYPE_SOCKET:
D 13
		error = EOPNOTSUPP;
E 13
I 13
		error = soo_stat((struct socket *)fp->f_data, &stb);
		if (error == 0) {
			vattr_null(vap);
			vap->va_type = VSOCK;
			vap->va_mode = stb.st_mode;
			vap->va_nlink = stb.st_nlink;
			vap->va_uid = stb.st_uid;
			vap->va_gid = stb.st_gid;
			vap->va_fsid = stb.st_dev;
			vap->va_fileid = stb.st_ino;
			vap->va_size = stb.st_size;
			vap->va_blocksize = stb.st_blksize;
			vap->va_atime = stb.st_atimespec;
			vap->va_mtime = stb.st_mtimespec;
			vap->va_ctime = stb.st_ctimespec;
			vap->va_gen = stb.st_gen;
			vap->va_flags = stb.st_flags;
			vap->va_rdev = stb.st_rdev;
			vap->va_bytes = stb.st_blocks * stb.st_blksize;
		}
E 13
		break;

	default:
		panic("fdesc attr");
		break;
	}

D 22
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_attr: returns error %d\n", error);
#endif
E 22
	return (error);
}

I 22
int
E 22
D 5
fdesc_getattr (ap)
	struct vop_getattr_args *ap;
E 5
I 5
fdesc_getattr(ap)
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 5
{
I 2
	struct vnode *vp = ap->a_vp;
	struct vattr *vap = ap->a_vap;
E 2
	unsigned fd;
D 15
	int error;
E 15
I 15
	int error = 0;
E 15

D 2
	if (ap->a_vp->v_flag & VROOT) {
E 2
I 2
D 9
	if (vp->v_flag & VROOT) {
E 9
E 2
D 22
#ifdef FDESC_DIAGNOSTIC
D 9
		printf("fdesc_getattr: stat rootdir\n");
E 9
I 9
	printf("fdesc_getattr: stat type = %d\n", VTOFDESC(vp)->fd_type);
E 9
#endif
I 9

E 22
	switch (VTOFDESC(vp)->fd_type) {
	case Froot:
	case Fdevfd:
	case Flink:
	case Fctty:
E 9
D 2
		bzero((caddr_t) ap->a_vap, sizeof(*ap->a_vap));
		vattr_null(ap->a_vap);
		ap->a_vap->va_type = VDIR;
		ap->a_vap->va_mode = S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH;
		ap->a_vap->va_nlink = 2;
		ap->a_vap->va_uid = 0;
		ap->a_vap->va_gid = 0;
		ap->a_vap->va_fsid = ap->a_vp->v_mount->mnt_stat.f_fsid.val[0];
		ap->a_vap->va_fileid = 2;
		/* ap->a_vap->va_qsize = 0; */
		ap->a_vap->va_size = DEV_BSIZE;
		ap->a_vap->va_blocksize = DEV_BSIZE;
		microtime(&ap->a_vap->va_atime);
		ap->a_vap->va_mtime = ap->a_vap->va_atime;
		ap->a_vap->va_ctime = ap->a_vap->va_ctime;
		ap->a_vap->va_gen = 0;
		ap->a_vap->va_flags = 0;
		ap->a_vap->va_rdev = 0;
		/* ap->a_vap->va_qbytes = 0; */
		ap->a_vap->va_bytes = 0;
E 2
I 2
		bzero((caddr_t) vap, sizeof(*vap));
		vattr_null(vap);
D 9
		vap->va_type = VDIR;
		vap->va_mode = S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH;
		vap->va_nlink = 2;
E 9
I 9
		vap->va_fileid = VTOFDESC(vp)->fd_ix;

		switch (VTOFDESC(vp)->fd_type) {
		case Flink:
			vap->va_mode = S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH;
			vap->va_type = VLNK;
			vap->va_nlink = 1;
D 22
			/* vap->va_qsize = strlen(VTOFDESC(vp)->fd_link); */
E 22
			vap->va_size = strlen(VTOFDESC(vp)->fd_link);
			break;

		case Fctty:
			vap->va_mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
			vap->va_type = VFIFO;
			vap->va_nlink = 1;
D 22
			/* vap->va_qsize = 0; */
E 22
			vap->va_size = 0;
			break;

		default:
			vap->va_mode = S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH;
			vap->va_type = VDIR;
			vap->va_nlink = 2;
D 22
			/* vap->va_qsize = 0; */
E 22
			vap->va_size = DEV_BSIZE;
			break;
		}
E 9
		vap->va_uid = 0;
		vap->va_gid = 0;
		vap->va_fsid = vp->v_mount->mnt_stat.f_fsid.val[0];
D 9
		vap->va_fileid = 2;
		/* vap->va_qsize = 0; */
		vap->va_size = DEV_BSIZE;
E 9
		vap->va_blocksize = DEV_BSIZE;
D 9
		microtime(&vap->va_atime);
E 9
I 9
		vap->va_atime.ts_sec = boottime.tv_sec;
		vap->va_atime.ts_nsec = 0;
E 9
		vap->va_mtime = vap->va_atime;
D 17
		vap->va_ctime = vap->va_ctime;
E 17
I 17
		vap->va_ctime = vap->va_mtime;
E 17
		vap->va_gen = 0;
		vap->va_flags = 0;
		vap->va_rdev = 0;
D 22
		/* vap->va_qbytes = 0; */
E 22
		vap->va_bytes = 0;
E 2
D 9
		return (0);
E 9
I 9
		break;

	case Fdesc:
D 22
#ifdef FDESC_DIAGNOSTIC
		printf("fdesc_getattr: stat desc #%d\n", VTOFDESC(vp)->fd_fd);
#endif
E 22
		fd = VTOFDESC(vp)->fd_fd;
		error = fdesc_attr(fd, vap, ap->a_cred, ap->a_p);
		break;

	default:
		panic("fdesc_getattr");
		break;	
E 9
	}

D 2
	fd = VTOFDESC(ap->a_vp)->f_fd;
	error = fdesc_attr(fd, ap->a_vap, ap->a_cred, ap->a_p);
E 2
I 2
D 9
	fd = VTOFDESC(vp)->f_fd;
	error = fdesc_attr(fd, vap, ap->a_cred, ap->a_p);
E 9
E 2
	if (error == 0)
D 2
		ap->a_vp->v_type = ap->a_vap->va_type;
E 2
I 2
		vp->v_type = vap->va_type;
I 9

D 22
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_getattr: stat returns 0\n");
#endif
E 22
E 9
E 2
	return (error);
}

I 22
int
E 22
D 5
fdesc_setattr (ap)
	struct vop_setattr_args *ap;
E 5
I 5
fdesc_setattr(ap)
	struct vop_setattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 5
{
D 3
	USES_VOP_SETATTR;
E 3
	struct filedesc *fdp = ap->a_p->p_fd;
	struct file *fp;
	unsigned fd;
	int error;

	/*
	 * Can't mess with the root vnode
	 */
D 9
	if (ap->a_vp->v_flag & VROOT)
E 9
I 9
	switch (VTOFDESC(ap->a_vp)->fd_type) {
	case Fdesc:
		break;

	case Fctty:
		return (0);

	default:
E 9
		return (EACCES);
I 9
	}
E 9

D 9
	fd = VTOFDESC(ap->a_vp)->f_fd;
E 9
I 9
	fd = VTOFDESC(ap->a_vp)->fd_fd;
E 9
D 22
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_setattr: fd = %d, nfiles = %d\n", fd, fdp->fd_nfiles);
#endif
E 22
	if (fd >= fdp->fd_nfiles || (fp = fdp->fd_ofiles[fd]) == NULL) {
D 22
#ifdef FDESC_DIAGNOSTIC
		printf("fdesc_setattr: fp = %x (EBADF)\n", fp);
#endif
E 22
		return (EBADF);
	}

	/*
	 * Can setattr the underlying vnode, but not sockets!
	 */
	switch (fp->f_type) {
	case DTYPE_VNODE:
		error = VOP_SETATTR((struct vnode *) fp->f_data, ap->a_vap, ap->a_cred, ap->a_p);
		break;

	case DTYPE_SOCKET:
D 8
		error = EOPNOTSUPP;
E 8
I 8
		error = 0;
E 8
		break;

	default:
		panic("fdesc setattr");
		break;
	}

D 22
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_setattr: returns error %d\n", error);
#endif
E 22
	return (error);
}

I 9
#define UIO_MX 16

static struct dirtmp {
	u_long d_fileno;
	u_short d_reclen;
	u_short d_namlen;
	char d_name[8];
} rootent[] = {
	{ FD_DEVFD, UIO_MX, 2, "fd" },
	{ FD_STDIN, UIO_MX, 5, "stdin" },
	{ FD_STDOUT, UIO_MX, 6, "stdout" },
	{ FD_STDERR, UIO_MX, 6, "stderr" },
	{ FD_CTTY, UIO_MX, 3, "tty" },
	{ 0 }
};

I 22
int
E 22
E 9
D 5
fdesc_readdir (ap)
	struct vop_readdir_args *ap;
E 5
I 5
fdesc_readdir(ap)
	struct vop_readdir_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
I 25
		int *a_eofflag;
		u_long *a_cookies;
		int a_ncookies;
E 25
	} */ *ap;
E 5
{
I 2
	struct uio *uio = ap->a_uio;
E 2
	struct filedesc *fdp;
	int i;
	int error;
I 25

	/*
	 * We don't allow exporting fdesc mounts, and currently local
	 * requests do not need cookies.
	 */
	if (ap->a_ncookies)
		panic("fdesc_readdir: not hungry");
E 25

D 9
#define UIO_MX 16
E 9
I 9
	switch (VTOFDESC(ap->a_vp)->fd_type) {
	case Fctty:
		return (0);
E 9

I 9
	case Fdesc:
		return (ENOTDIR);

	default:
		break;
	}

E 9
D 2
	fdp = ap->a_uio->uio_procp->p_fd;
	i = ap->a_uio->uio_offset / UIO_MX;
E 2
I 2
	fdp = uio->uio_procp->p_fd;
I 9

	if (VTOFDESC(ap->a_vp)->fd_type == Froot) {
		struct dirent d;
		struct dirent *dp = &d;
		struct dirtmp *dt;

		i = uio->uio_offset / UIO_MX;
		error = 0;

		while (uio->uio_resid > 0) {
			dt = &rootent[i];
			if (dt->d_fileno == 0) {
				/**eofflagp = 1;*/
				break;
			}
			i++;
			
			switch (dt->d_fileno) {
			case FD_CTTY:
				if (cttyvp(uio->uio_procp) == NULL)
					continue;
				break;

			case FD_STDIN:
			case FD_STDOUT:
			case FD_STDERR:
D 17
				if ((i-FD_STDIN) >= fdp->fd_nfiles)
E 17
I 17
				if ((dt->d_fileno-FD_STDIN) >= fdp->fd_nfiles)
E 17
					continue;
D 17
				if (fdp->fd_ofiles[i-FD_STDIN] == NULL)
E 17
I 17
				if (fdp->fd_ofiles[dt->d_fileno-FD_STDIN] == NULL)
E 17
					continue;
				break;
			}
D 17
			bzero(dp, UIO_MX);
E 17
I 17
			bzero((caddr_t) dp, UIO_MX);
E 17
			dp->d_fileno = dt->d_fileno;
			dp->d_namlen = dt->d_namlen;
			dp->d_type = DT_UNKNOWN;
			dp->d_reclen = dt->d_reclen;
			bcopy(dt->d_name, dp->d_name, dp->d_namlen+1);
			error = uiomove((caddr_t) dp, UIO_MX, uio);
			if (error)
				break;
		}
		uio->uio_offset = i * UIO_MX;
		return (error);
	}

E 9
	i = uio->uio_offset / UIO_MX;
E 2
	error = 0;
D 2
	while (ap->a_uio->uio_resid > 0) {
E 2
I 2
	while (uio->uio_resid > 0) {
E 2
D 22
		if (i >= fdp->fd_nfiles) {
D 3
			*ap->a_eofflagp = 1;
E 3
I 3
			/* *ap->a_eofflagp = 1; */
E 22
I 22
		if (i >= fdp->fd_nfiles)
E 22
E 3
			break;
D 22
		}
E 22
I 22

E 22
		if (fdp->fd_ofiles[i] != NULL) {
D 4
			struct readdir d;
			struct readdir *dp = &d;
E 4
I 4
			struct dirent d;
			struct dirent *dp = &d;
I 22

E 22
E 4
D 21
			char *cp = dp->d_name;
E 21
D 9
#ifdef FDESC_FILEID
			struct vattr va;
#endif
E 9
			bzero((caddr_t) dp, UIO_MX);

			dp->d_namlen = sprintf(dp->d_name, "%d", i);
D 22
			/*
			 * Fill in the remaining fields
			 */
E 22
			dp->d_reclen = UIO_MX;
D 4
			dp->d_ino = i + 3;
E 4
I 4
			dp->d_type = DT_UNKNOWN;
D 9
			dp->d_fileno = i + 3;
E 4
#ifdef FDESC_FILEID
E 9
I 9
			dp->d_fileno = i + FD_STDIN;
E 9
			/*
D 9
			 * If we want the file ids to match the
			 * we must call getattr on the underlying file.
			 * fdesc_attr may return an error, in which case
			 * we ignore the returned file id.
			 */
			error = fdesc_attr(i, &va, ap->a_cred, p);
			if (error == 0)
				dp->d_ino = va.va_fileid;
#endif
			/*
E 9
			 * And ship to userland
			 */
D 2
			error = uiomove((caddr_t) dp, UIO_MX, ap->a_uio);
E 2
I 2
			error = uiomove((caddr_t) dp, UIO_MX, uio);
E 2
			if (error)
				break;
		}
		i++;
	}

D 2
	ap->a_uio->uio_offset = i * UIO_MX;
E 2
I 2
	uio->uio_offset = i * UIO_MX;
E 2
	return (error);
}

I 9
int
fdesc_readlink(ap)
	struct vop_readlink_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
	} */ *ap;
{
D 22
	register struct vnode *vp = ap->a_vp;
E 22
I 22
	struct vnode *vp = ap->a_vp;
E 22
	int error;

	if (vp->v_type != VLNK)
		return (EPERM);

	if (VTOFDESC(vp)->fd_type == Flink) {
		char *ln = VTOFDESC(vp)->fd_link;
		error = uiomove(ln, strlen(ln), ap->a_uio);
	} else {
		error = EOPNOTSUPP;
	}

	return (error);
}

I 22
int
E 22
fdesc_read(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	int error = EOPNOTSUPP;

	switch (VTOFDESC(ap->a_vp)->fd_type) {
	case Fctty:
		error = cttyread(devctty, ap->a_uio, ap->a_ioflag);
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}
	
	return (error);
}

I 22
int
E 22
fdesc_write(ap)
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	int error = EOPNOTSUPP;

	switch (VTOFDESC(ap->a_vp)->fd_type) {
	case Fctty:
		error = cttywrite(devctty, ap->a_uio, ap->a_ioflag);
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}
	
	return (error);
}

I 22
int
E 22
fdesc_ioctl(ap)
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
		int  a_command;
		caddr_t  a_data;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	int error = EOPNOTSUPP;

D 22
#ifdef FDESC_DIAGNOSTIC
	printf("fdesc_ioctl: type = %d, command = %x\n",
			VTOFDESC(ap->a_vp)->fd_type, ap->a_command);
#endif
E 22
	switch (VTOFDESC(ap->a_vp)->fd_type) {
	case Fctty:
		error = cttyioctl(devctty, ap->a_command, ap->a_data,
					ap->a_fflag, ap->a_p);
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}
	
	return (error);
}

I 22
int
E 22
fdesc_select(ap)
	struct vop_select_args /* {
		struct vnode *a_vp;
		int  a_which;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	int error = EOPNOTSUPP;

	switch (VTOFDESC(ap->a_vp)->fd_type) {
	case Fctty:
		error = cttyselect(devctty, ap->a_fflags, ap->a_p);
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}
	
	return (error);
}

I 22
int
E 22
E 9
D 5
fdesc_inactive (ap)
	struct vop_inactive_args *ap;
E 5
I 5
fdesc_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 31
		struct proc *a_p;
E 31
	} */ *ap;
E 5
{
I 2
	struct vnode *vp = ap->a_vp;

E 2
	/*
	 * Clear out the v_type field to avoid
	 * nasty things happening in vgone().
	 */
I 31
	VOP_UNLOCK(vp, 0, ap->a_p);
E 31
D 2
	ap->a_vp->v_type = VNON;
E 2
I 2
	vp->v_type = VNON;
E 2
D 22
#ifdef FDESC_DIAGNOSTIC
D 2
	printf("fdesc_inactive(%x)\n", ap->a_vp);
E 2
I 2
	printf("fdesc_inactive(%x)\n", vp);
E 2
#endif
E 22
	return (0);
}

I 22
int
E 22
D 5
fdesc_reclaim (ap)
	struct  vop_reclaim_args *ap;
E 5
I 5
fdesc_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 5
{
	struct vnode *vp = ap->a_vp;
I 27
	struct fdescnode *fd = VTOFDESC(vp);
E 27
I 9
D 22
	int ix;
E 22

D 22
#ifdef FDESC_DIAGNOSTIC
E 9
	printf("fdesc_reclaim(%x)\n", vp);
I 9
#endif
	ix = VTOFDESC(vp)->fd_ix;
	if (ix >= 0 && ix < FD_MAX) {
		if (fdescvp[ix] != vp)
			panic("fdesc_reclaim");
		fdescvp[ix] = 0;
	}
E 9
	if (vp->v_data) {
		FREE(vp->v_data, M_TEMP);
		vp->v_data = 0;
	}
E 22
I 22
D 27
	remque(VTOFDESC(vp));
E 27
I 27
	LIST_REMOVE(fd, fd_hash);
E 27
	FREE(vp->v_data, M_TEMP);
	vp->v_data = 0;

E 22
	return (0);
}

/*
I 23
 * Return POSIX pathconf information applicable to special devices.
 */
fdesc_pathconf(ap)
	struct vop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		int *a_retval;
	} */ *ap;
{

	switch (ap->a_name) {
	case _PC_LINK_MAX:
		*ap->a_retval = LINK_MAX;
		return (0);
	case _PC_MAX_CANON:
		*ap->a_retval = MAX_CANON;
		return (0);
	case _PC_MAX_INPUT:
		*ap->a_retval = MAX_INPUT;
		return (0);
	case _PC_PIPE_BUF:
		*ap->a_retval = PIPE_BUF;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		return (0);
	case _PC_VDISABLE:
		*ap->a_retval = _POSIX_VDISABLE;
		return (0);
	default:
		return (EINVAL);
	}
	/* NOTREACHED */
}

/*
E 23
 * Print out the contents of a /dev/fd vnode.
 */
/* ARGSUSED */
I 22
int
E 22
D 5
fdesc_print (ap)
	struct vop_print_args *ap;
E 5
I 5
fdesc_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 5
{
I 5

E 5
	printf("tag VT_NON, fdesc vnode\n");
I 5
	return (0);
E 5
}

/*void*/
I 22
int
E 22
D 5
fdesc_vfree (ap)
	struct vop_vfree_args *ap;
E 5
I 5
fdesc_vfree(ap)
	struct vop_vfree_args /* {
		struct vnode *a_pvp;
		ino_t a_ino;
		int a_mode;
	} */ *ap;
E 5
{

D 5
	return;
E 5
I 5
	return (0);
E 5
}

/*
D 28
 * /dev/fd vnode unsupported operation
 */
I 22
int
E 22
fdesc_enotsupp()
{
I 5

E 5
	return (EOPNOTSUPP);
}

/*
E 28
 * /dev/fd "should never get here" operation
 */
I 22
int
E 22
fdesc_badop()
{
I 5

E 5
	panic("fdesc: bad op");
	/* NOTREACHED */
}

D 28
/*
 * /dev/fd vnode null operation
 */
I 22
int
E 22
fdesc_nullop()
{
I 5

E 5
	return (0);
}

#define fdesc_create ((int (*) __P((struct  vop_create_args *)))fdesc_enotsupp)
#define fdesc_mknod ((int (*) __P((struct  vop_mknod_args *)))fdesc_enotsupp)
E 28
I 28
#define fdesc_create ((int (*) __P((struct  vop_create_args *)))eopnotsupp)
#define fdesc_mknod ((int (*) __P((struct  vop_mknod_args *)))eopnotsupp)
E 28
#define fdesc_close ((int (*) __P((struct  vop_close_args *)))nullop)
#define fdesc_access ((int (*) __P((struct  vop_access_args *)))nullop)
D 9
#define fdesc_read ((int (*) __P((struct  vop_read_args *)))fdesc_enotsupp)
#define fdesc_write ((int (*) __P((struct  vop_write_args *)))fdesc_enotsupp)
#define fdesc_ioctl ((int (*) __P((struct  vop_ioctl_args *)))fdesc_enotsupp)
#define fdesc_select ((int (*) __P((struct  vop_select_args *)))fdesc_enotsupp)
E 9
D 28
#define fdesc_mmap ((int (*) __P((struct  vop_mmap_args *)))fdesc_enotsupp)
E 28
I 28
#define fdesc_mmap ((int (*) __P((struct  vop_mmap_args *)))eopnotsupp)
I 29
#define	fdesc_revoke vop_revoke
E 29
E 28
#define fdesc_fsync ((int (*) __P((struct  vop_fsync_args *)))nullop)
#define fdesc_seek ((int (*) __P((struct  vop_seek_args *)))nullop)
D 28
#define fdesc_remove ((int (*) __P((struct  vop_remove_args *)))fdesc_enotsupp)
#define fdesc_link ((int (*) __P((struct  vop_link_args *)))fdesc_enotsupp)
#define fdesc_rename ((int (*) __P((struct  vop_rename_args *)))fdesc_enotsupp)
#define fdesc_mkdir ((int (*) __P((struct  vop_mkdir_args *)))fdesc_enotsupp)
#define fdesc_rmdir ((int (*) __P((struct  vop_rmdir_args *)))fdesc_enotsupp)
D 5
#define fdesc_symlink ((int (*) __P((struct  vop_symlink_args *)))fdesc_enotsupp)
#define fdesc_readlink ((int (*) __P((struct  vop_readlink_args *)))fdesc_enotsupp)
E 5
I 5
#define fdesc_symlink ((int (*) __P((struct vop_symlink_args *)))fdesc_enotsupp)
E 28
I 28
#define fdesc_remove ((int (*) __P((struct  vop_remove_args *)))eopnotsupp)
#define fdesc_link ((int (*) __P((struct  vop_link_args *)))eopnotsupp)
#define fdesc_rename ((int (*) __P((struct  vop_rename_args *)))eopnotsupp)
#define fdesc_mkdir ((int (*) __P((struct  vop_mkdir_args *)))eopnotsupp)
#define fdesc_rmdir ((int (*) __P((struct  vop_rmdir_args *)))eopnotsupp)
#define fdesc_symlink ((int (*) __P((struct vop_symlink_args *)))eopnotsupp)
E 28
D 7
#define fdesc_readlink
E 7
I 7
D 9
#define fdesc_readlink \
E 7
	((int (*) __P((struct  vop_readlink_args *)))fdesc_enotsupp)
E 9
E 5
#define fdesc_abortop ((int (*) __P((struct  vop_abortop_args *)))nullop)
D 30
#define fdesc_lock ((int (*) __P((struct  vop_lock_args *)))nullop)
#define fdesc_unlock ((int (*) __P((struct  vop_unlock_args *)))nullop)
E 30
I 30
#define fdesc_lock ((int (*) __P((struct  vop_lock_args *)))vop_nolock)
#define fdesc_unlock ((int (*) __P((struct  vop_unlock_args *)))vop_nounlock)
E 30
#define fdesc_bmap ((int (*) __P((struct  vop_bmap_args *)))fdesc_badop)
#define fdesc_strategy ((int (*) __P((struct  vop_strategy_args *)))fdesc_badop)
D 30
#define fdesc_islocked ((int (*) __P((struct  vop_islocked_args *)))nullop)
E 30
I 30
#define fdesc_islocked \
	((int (*) __P((struct vop_islocked_args *)))vop_noislocked)
E 30
D 5
#define fdesc_advlock ((int (*) __P((struct  vop_advlock_args *)))fdesc_enotsupp)
#define fdesc_blkatoff ((int (*) __P((struct  vop_blkatoff_args *)))fdesc_enotsupp)
E 5
I 5
D 28
#define fdesc_advlock ((int (*) __P((struct vop_advlock_args *)))fdesc_enotsupp)
E 28
I 28
#define fdesc_advlock ((int (*) __P((struct vop_advlock_args *)))eopnotsupp)
E 28
D 7
#define fdesc_blkatoff
E 7
I 7
#define fdesc_blkatoff \
E 7
D 28
	((int (*) __P((struct  vop_blkatoff_args *)))fdesc_enotsupp)
E 5
#define fdesc_vget ((int (*) __P((struct  vop_vget_args *)))fdesc_enotsupp)
E 28
I 28
	((int (*) __P((struct  vop_blkatoff_args *)))eopnotsupp)
E 28
#define fdesc_valloc ((int(*) __P(( \
		struct vnode *pvp, \
		int mode, \
		struct ucred *cred, \
D 28
		struct vnode **vpp))) fdesc_enotsupp)
E 28
I 28
		struct vnode **vpp))) eopnotsupp)
E 28
D 5
#define fdesc_truncate ((int (*) __P((struct  vop_truncate_args *)))fdesc_enotsupp)
E 5
I 5
D 7
#define fdesc_truncate
E 7
I 7
#define fdesc_truncate \
E 7
D 28
	((int (*) __P((struct  vop_truncate_args *)))fdesc_enotsupp)
E 5
#define fdesc_update ((int (*) __P((struct  vop_update_args *)))fdesc_enotsupp)
#define fdesc_bwrite ((int (*) __P((struct  vop_bwrite_args *)))fdesc_enotsupp)
E 28
I 28
	((int (*) __P((struct  vop_truncate_args *)))eopnotsupp)
#define fdesc_update ((int (*) __P((struct  vop_update_args *)))eopnotsupp)
#define fdesc_bwrite ((int (*) __P((struct  vop_bwrite_args *)))eopnotsupp)
E 28

int (**fdesc_vnodeop_p)();
struct vnodeopv_entry_desc fdesc_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, fdesc_lookup },	/* lookup */
	{ &vop_create_desc, fdesc_create },	/* create */
	{ &vop_mknod_desc, fdesc_mknod },	/* mknod */
D 5
	{ &vop_open_desc, fdesc_open },	/* open */
E 5
I 5
	{ &vop_open_desc, fdesc_open },		/* open */
E 5
	{ &vop_close_desc, fdesc_close },	/* close */
	{ &vop_access_desc, fdesc_access },	/* access */
	{ &vop_getattr_desc, fdesc_getattr },	/* getattr */
	{ &vop_setattr_desc, fdesc_setattr },	/* setattr */
D 5
	{ &vop_read_desc, fdesc_read },	/* read */
E 5
I 5
	{ &vop_read_desc, fdesc_read },		/* read */
E 5
	{ &vop_write_desc, fdesc_write },	/* write */
	{ &vop_ioctl_desc, fdesc_ioctl },	/* ioctl */
	{ &vop_select_desc, fdesc_select },	/* select */
I 29
	{ &vop_revoke_desc, fdesc_revoke },	/* revoke */
E 29
D 5
	{ &vop_mmap_desc, fdesc_mmap },	/* mmap */
E 5
I 5
	{ &vop_mmap_desc, fdesc_mmap },		/* mmap */
E 5
	{ &vop_fsync_desc, fdesc_fsync },	/* fsync */
D 5
	{ &vop_seek_desc, fdesc_seek },	/* seek */
E 5
I 5
	{ &vop_seek_desc, fdesc_seek },		/* seek */
E 5
	{ &vop_remove_desc, fdesc_remove },	/* remove */
D 5
	{ &vop_link_desc, fdesc_link },	/* link */
E 5
I 5
	{ &vop_link_desc, fdesc_link },		/* link */
E 5
	{ &vop_rename_desc, fdesc_rename },	/* rename */
	{ &vop_mkdir_desc, fdesc_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, fdesc_rmdir },	/* rmdir */
	{ &vop_symlink_desc, fdesc_symlink },	/* symlink */
	{ &vop_readdir_desc, fdesc_readdir },	/* readdir */
	{ &vop_readlink_desc, fdesc_readlink },	/* readlink */
	{ &vop_abortop_desc, fdesc_abortop },	/* abortop */
	{ &vop_inactive_desc, fdesc_inactive },	/* inactive */
	{ &vop_reclaim_desc, fdesc_reclaim },	/* reclaim */
D 5
	{ &vop_lock_desc, fdesc_lock },	/* lock */
E 5
I 5
	{ &vop_lock_desc, fdesc_lock },		/* lock */
E 5
	{ &vop_unlock_desc, fdesc_unlock },	/* unlock */
D 5
	{ &vop_bmap_desc, fdesc_bmap },	/* bmap */
E 5
I 5
	{ &vop_bmap_desc, fdesc_bmap },		/* bmap */
E 5
	{ &vop_strategy_desc, fdesc_strategy },	/* strategy */
	{ &vop_print_desc, fdesc_print },	/* print */
	{ &vop_islocked_desc, fdesc_islocked },	/* islocked */
I 23
	{ &vop_pathconf_desc, fdesc_pathconf },	/* pathconf */
E 23
	{ &vop_advlock_desc, fdesc_advlock },	/* advlock */
	{ &vop_blkatoff_desc, fdesc_blkatoff },	/* blkatoff */
D 3
	{ &vop_vget_desc, fdesc_vget },	/* vget */
E 3
	{ &vop_valloc_desc, fdesc_valloc },	/* valloc */
	{ &vop_vfree_desc, fdesc_vfree },	/* vfree */
	{ &vop_truncate_desc, fdesc_truncate },	/* truncate */
	{ &vop_update_desc, fdesc_update },	/* update */
	{ &vop_bwrite_desc, fdesc_bwrite },	/* bwrite */
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
struct vnodeopv_desc fdesc_vnodeop_opv_desc =
	{ &fdesc_vnodeop_p, fdesc_vnodeop_entries };
E 1
