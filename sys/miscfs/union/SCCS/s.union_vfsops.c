h45529
s 00004/00003/00465
d D 8.20 95/05/20 07:30:41 pendry 32 31
c VOP_UNLOCK vrele -> vput
e
s 00003/00002/00465
d D 8.19 95/05/14 00:48:43 mckusick 31 30
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00003/00003/00464
d D 8.18 95/05/10 11:22:46 pendry 30 29
c VOP_REVOKE(vp, 0) should really be vgone(vp)
e
s 00001/00006/00466
d D 8.17 95/05/10 09:48:25 mckusick 29 28
c check for forcible unmount at syscall level
e
s 00018/00060/00454
d D 8.16 95/03/29 00:50:12 mckusick 28 27
c cleanups; getnewfsid => vfs_getnewfsid; add sysctl
e
s 00001/00001/00513
d D 8.15 95/02/23 12:24:35 mckusick 27 25
c vgone => VOP_REVOKE
e
s 00001/00001/00513
d R 8.15 95/02/22 19:26:14 mckusick 26 25
c vgone => VOP_REVOKE
e
s 00011/00007/00503
d D 8.14 94/12/30 02:07:30 pendry 25 24
c union_statfs should only return free space information
c about the upper layer.
e
s 00002/00001/00508
d D 8.13 94/12/10 13:03:10 pendry 24 23
c fix readdir for no-linear stacks
e
s 00016/00050/00493
d D 8.12 94/07/28 03:39:24 pendry 23 22
c changes for whiteouts and union filesystem
e
s 00031/00005/00512
d D 8.11 94/06/17 09:45:56 pendry 22 21
c keep track of parent union node, so allowing .. to refer to
c the correct union node.
e
s 00002/00002/00515
d D 8.10 94/05/24 04:42:06 pendry 21 20
c put : after <xxx> strings
e
s 00000/00006/00517
d D 8.9 94/04/29 03:24:01 pendry 20 19
c remove (now) useless diagnostic message
e
s 00000/00001/00523
d D 8.8 94/04/24 08:45:45 pendry 19 18
c VROOT flag is set in union_allocvp
e
s 00003/00003/00521
d D 8.7 94/03/05 10:50:22 pendry 18 17
c change tag in mnt_stat structure so that
c the mounted filesystem appears as
c <above>/some/where, instead of un-above:/some/where
e
s 00011/00001/00513
d D 8.6 94/02/21 12:44:30 pendry 17 16
c in mount, do the target lookup with the
c real user, not the effective user.  ie simulate access().
e
s 00018/00007/00496
d D 8.5 94/02/20 17:18:22 pendry 16 15
c add privilege checks etc to support user mounts
e
s 00032/00008/00471
d D 8.4 94/02/17 16:36:00 pendry 15 14
c implement new access policy
c fixup locking for UNMNT_BELOW.
e
s 00001/00001/00478
d D 8.3 94/02/11 14:37:32 pendry 14 13
c union_statfs should identify itself, not the upper layer
e
s 00001/00001/00478
d D 8.2 94/02/10 18:52:29 pendry 13 12
c use miscfs include path
e
s 00000/00000/00479
d D 8.1 94/02/10 18:50:26 pendry 12 11
c up to v8
e
s 00001/00000/00478
d D 2.2 94/02/10 18:38:14 pendry 11 10
c cleanup & lint
e
s 00001/00000/00477
d D 2.1 94/02/10 14:08:26 pendry 10 9
c new locking scheme
e
s 00108/00035/00369
d D 1.9 94/02/08 16:16:05 pendry 9 8
c checkpoint
e
s 00000/00000/00404
d D 1.8 94/02/07 21:35:18 pendry 8 7
c checkpoint
e
s 00000/00000/00404
d D 1.7 94/02/07 16:13:18 pendry 7 6
c checkpoint
e
s 00014/00001/00390
d D 1.6 94/02/04 17:50:34 pendry 6 5
c checkpoint
e
s 00021/00007/00370
d D 1.5 94/02/03 20:08:00 pendry 5 4
c checkpoint
e
s 00003/00001/00374
d D 1.4 94/02/03 12:25:01 pendry 4 3
c checkpoint
e
s 00015/00004/00360
d D 1.3 94/02/01 20:45:36 pendry 3 2
c checkpoint
e
s 00000/00000/00364
d D 1.2 94/02/01 17:11:11 pendry 2 1
c checkpoint
e
s 00364/00000/00000
d D 1.1 94/01/28 09:42:44 pendry 1 0
c date and time created 94/01/28 09:42:44 by pendry
e
u
U
t
T
I 1
/*
D 30
 * Copyright (c) 1994 The Regents of the University of California.
 * Copyright (c) 1994 Jan-Simon Pendry.
E 30
I 30
 * Copyright (c) 1994, 1995 The Regents of the University of California.
 * Copyright (c) 1994, 1995 Jan-Simon Pendry.
E 30
 * All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
D 5
 * Null Layer
 * (See union_vnops.c for a description of what this does.)
E 5
I 5
 * Union Layer
E 5
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
I 6
#include <sys/filedesc.h>
I 11
#include <sys/queue.h>
E 11
E 6
D 13
#include "union.h"
E 13
I 13
#include <miscfs/union/union.h>
E 13

/*
 * Mount union filesystem
 */
int
union_mount(mp, path, data, ndp, p)
	struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
	struct proc *p;
{
	int error = 0;
	struct union_args args;
D 9
	struct vnode *lowerrootvp;
	struct vnode *upperrootvp;
E 9
I 9
	struct vnode *lowerrootvp = NULLVP;
	struct vnode *upperrootvp = NULLVP;
E 9
D 23
	struct union_mount *um;
E 23
I 23
	struct union_mount *um = 0;
E 23
I 9
	struct ucred *cred = 0;
I 17
	struct ucred *scred;
E 17
I 15
	struct vattr va;
E 15
	char *cp;
	int len;
E 9
	u_int size;

#ifdef UNION_DIAGNOSTIC
	printf("union_mount(mp = %x)\n", mp);
#endif

	/*
	 * Update is a no-op
	 */
D 5
	if (mp->mnt_flag & MNT_UPDATE)
E 5
I 5
	if (mp->mnt_flag & MNT_UPDATE) {
		/*
		 * Need to provide.
		 * 1. a way to convert between rdonly and rdwr mounts.
		 * 2. support for nfs exports.
		 */
E 5
D 9
		return (EOPNOTSUPP);
E 9
I 9
		error = EOPNOTSUPP;
		goto bad;
E 9
I 5
	}
E 5

	/*
I 9
D 23
	 * Take a copy of the process's credentials.  This isn't
	 * quite right since the euid will always be zero and we
	 * want to get the "real" users credentials.  So fix up
	 * the uid field after taking the copy.
	 */
	cred = crdup(p->p_ucred);
	cred->cr_uid = p->p_cred->p_ruid;

	/*
	 * Ensure the *real* user has write permission on the
	 * mounted-on directory.  This allows the mount_union
	 * command to be made setuid root so allowing anyone
	 * to do union mounts onto any directory on which they
D 15
	 * have write permission.
E 15
I 15
D 16
	 * have write (also delete and rename) permission.
E 16
I 16
	 * have write permission and which they also own.
E 16
E 15
	 */
D 16
	error = VOP_ACCESS(mp->mnt_vnodecovered, VWRITE, cred, p);
	if (error)
		goto bad;
E 16
I 15
	error = VOP_GETATTR(mp->mnt_vnodecovered, &va, cred, p);
	if (error)
		goto bad;
D 16
	if ((va.va_mode & VSVTX) &&
	    (va.va_uid != 0) &&
	    (va.va_uid != cred->cr_uid)) {
E 16
I 16
	if ((va.va_uid != cred->cr_uid) && 
	    (cred->cr_uid != 0)) {
E 16
		error = EACCES;
		goto bad;
	}
I 16
	error = VOP_ACCESS(mp->mnt_vnodecovered, VWRITE, cred, p);
	if (error)
		goto bad;
E 16
E 15

	/*
E 23
E 9
	 * Get argument
	 */
	if (error = copyin(data, (caddr_t)&args, sizeof(struct union_args)))
D 9
		return (error);
E 9
I 9
		goto bad;
E 9

	lowerrootvp = mp->mnt_vnodecovered;
	VREF(lowerrootvp);

	/*
D 17
	 * Find upper node
E 17
I 17
D 23
	 * Find upper node.  Use the real process credentials,
	 * not the effective ones since this will have come
	 * through a setuid process (mount_union).  All this
	 * messing around with permissions is entirely bogus
	 * and should be removed by allowing any user straight
	 * past the mount system call.
E 23
I 23
	 * Find upper node.
E 23
E 17
	 */
I 17
D 23
	scred = p->p_ucred;
	p->p_ucred = cred;
E 23
E 17
	NDINIT(ndp, LOOKUP, FOLLOW|WANTPARENT,
	       UIO_USERSPACE, args.target, p);
I 17
D 23
	p->p_ucred = scred;
E 23

E 17
D 9
	if (error = namei(ndp)) {
		vrele(lowerrootvp);
		return (error);
	}
E 9
I 9
	if (error = namei(ndp))
		goto bad;

E 9
	upperrootvp = ndp->ni_vp;
	vrele(ndp->ni_dvp);
	ndp->ni_dvp = NULL;

	if (upperrootvp->v_type != VDIR) {
I 6
D 9
		vrele(lowerrootvp);
E 6
		vrele(upperrootvp);
		return (EINVAL);
E 9
I 9
		error = EINVAL;
		goto bad;
E 9
	}
	
	um = (struct union_mount *) malloc(sizeof(struct union_mount),
				M_UFSMNT, M_WAITOK);	/* XXX */

	/*
	 * Keep a held reference to the target vnodes.
	 * They are vrele'd in union_unmount.
I 9
	 *
	 * Depending on the _BELOW flag, the filesystems are
	 * viewed in a different order.  In effect, this is the
	 * same as providing a mount under option to the mount syscall.
E 9
	 */
D 9
	um->um_lowervp = lowerrootvp;
	um->um_uppervp = upperrootvp;
	/*
	 * Take a copy of the process's credentials.  This isn't
	 * quite right since the euid will always be zero and we
	 * want to get the "real" users credentials.  So fix up
	 * the uid field after taking the copy.
	 */
	um->um_cred = crdup(p->p_ucred);
	um->um_cred->cr_uid = p->p_cred->p_ruid;
E 9
I 9

D 15
	switch (args.mntflags & UNMNT_OPMASK) {
E 15
I 15
	um->um_op = args.mntflags & UNMNT_OPMASK;
	switch (um->um_op) {
E 15
	case UNMNT_ABOVE:
		um->um_lowervp = lowerrootvp;
		um->um_uppervp = upperrootvp;
		break;

	case UNMNT_BELOW:
		um->um_lowervp = upperrootvp;
		um->um_uppervp = lowerrootvp;
		break;

	case UNMNT_REPLACE:
		vrele(lowerrootvp);
		lowerrootvp = NULLVP;
		um->um_uppervp = upperrootvp;
		um->um_lowervp = lowerrootvp;
		break;

	default:
		error = EINVAL;
		goto bad;
	}

D 23
	um->um_cred = cred;
E 23
I 23
	/*
	 * Unless the mount is readonly, ensure that the top layer
	 * supports whiteout operations
	 */
	if ((mp->mnt_flag & MNT_RDONLY) == 0) {
		error = VOP_WHITEOUT(um->um_uppervp, (struct componentname *) 0, LOOKUP);
		if (error)
			goto bad;
	}

	um->um_cred = p->p_ucred;
	crhold(um->um_cred);
E 23
E 9
I 6
	um->um_cmode = UN_DIRMODE &~ p->p_fd->fd_cmask;
E 6

I 6
	/*
	 * Depending on what you think the MNT_LOCAL flag might mean,
	 * you may want the && to be || on the conditional below.
	 * At the moment it has been defined that the filesystem is
	 * only local if it is all local, ie the MNT_LOCAL flag implies
	 * that the entire namespace is local.  If you think the MNT_LOCAL
	 * flag implies that some of the files might be stored locally
	 * then you will want to change the conditional.
	 */
E 6
D 5
	if ((lowerrootvp->v_mount->mnt_flag & MNT_LOCAL) ||
E 5
I 5
D 9
	if ((lowerrootvp->v_mount->mnt_flag & MNT_LOCAL) &&
E 5
	    (upperrootvp->v_mount->mnt_flag & MNT_LOCAL))
E 9
I 9
D 15
	if (((um->um_lowervp == NULLVP) ||
	     (um->um_lowervp->v_mount->mnt_flag & MNT_LOCAL)) &&
	    (um->um_uppervp->v_mount->mnt_flag & MNT_LOCAL))
E 9
		mp->mnt_flag |= MNT_LOCAL;
E 15
I 15
	if (um->um_op == UNMNT_ABOVE) {
		if (((um->um_lowervp == NULLVP) ||
		     (um->um_lowervp->v_mount->mnt_flag & MNT_LOCAL)) &&
		    (um->um_uppervp->v_mount->mnt_flag & MNT_LOCAL))
			mp->mnt_flag |= MNT_LOCAL;
	}
E 15
I 6

E 6
I 5
	/*
	 * Copy in the upper layer's RDONLY flag.  This is for the benefit
	 * of lookup() which explicitly checks the flag, rather than asking
	 * the filesystem for it's own opinion.  This means, that an update
	 * mount of the underlying filesystem to go from rdonly to rdwr
	 * will leave the unioned view as read-only.
	 */
D 9
	mp->mnt_flag |= (upperrootvp->v_mount->mnt_flag & MNT_RDONLY);
E 9
I 9
	mp->mnt_flag |= (um->um_uppervp->v_mount->mnt_flag & MNT_RDONLY);
I 16

D 23
	/*
	 * This is a user mount.  Privilege check for unmount
	 * will be done in union_unmount.
	 */
	mp->mnt_flag |= MNT_USER;

E 23
E 16
E 9
E 5
	mp->mnt_data = (qaddr_t) um;
D 28
	getnewfsid(mp, MOUNT_UNION);
E 28
I 28
	vfs_getnewfsid(mp);
E 28

	(void) copyinstr(path, mp->mnt_stat.f_mntonname, MNAMELEN - 1, &size);
	bzero(mp->mnt_stat.f_mntonname + size, MNAMELEN - size);
D 5
	(void) copyinstr(args.target, mp->mnt_stat.f_mntfromname, MNAMELEN - 1, 
	    &size);
	bzero(mp->mnt_stat.f_mntfromname + size, MNAMELEN - size);
E 5
I 5
D 9
	bcopy("union:", mp->mnt_stat.f_mntfromname, 6);
	(void) copyinstr(args.target, mp->mnt_stat.f_mntfromname + 6,
			MNAMELEN - 1 - 6, &size);
	bzero(mp->mnt_stat.f_mntfromname + 6 + size, MNAMELEN - 6 - size);
E 9
I 9

D 15
	switch (args.mntflags & UNMNT_OPMASK) {
E 15
I 15
	switch (um->um_op) {
E 15
	case UNMNT_ABOVE:
D 18
		cp = "un-above:";
E 18
I 18
D 21
		cp = "<above>";
E 21
I 21
		cp = "<above>:";
E 21
E 18
		break;
	case UNMNT_BELOW:
D 18
		cp = "un-below:";
E 18
I 18
D 21
		cp = "<below>";
E 21
I 21
		cp = "<below>:";
E 21
E 18
		break;
	case UNMNT_REPLACE:
D 18
		cp = "replace:";
E 18
I 18
		cp = "";
E 18
		break;
	}
	len = strlen(cp);
	bcopy(cp, mp->mnt_stat.f_mntfromname, len);

	cp = mp->mnt_stat.f_mntfromname + len;
	len = MNAMELEN - len;

	(void) copyinstr(args.target, cp, len - 1, &size);
	bzero(cp + size, len - size);

E 9
E 5
#ifdef UNION_DIAGNOSTIC
D 9
	printf("union_mount: upper %s, lower at %s\n",
E 9
I 9
	printf("union_mount: from %s, on %s\n",
E 9
		mp->mnt_stat.f_mntfromname, mp->mnt_stat.f_mntonname);
#endif
	return (0);
I 9

bad:
I 23
	if (um)
		free(um, M_UFSMNT);
E 23
	if (cred)
		crfree(cred);
	if (upperrootvp)
		vrele(upperrootvp);
	if (lowerrootvp)
		vrele(lowerrootvp);
	return (error);
E 9
}

/*
 * VFS start.  Nothing needed here - the start routine
 * on the underlying filesystem(s) will have been called
 * when that filesystem was mounted.
 */
int
union_start(mp, flags, p)
	struct mount *mp;
	int flags;
	struct proc *p;
{

	return (0);
}

/*
 * Free reference to union layer
 */
int
union_unmount(mp, mntflags, p)
	struct mount *mp;
	int mntflags;
	struct proc *p;
{
	struct union_mount *um = MOUNTTOUNIONMOUNT(mp);
	struct vnode *um_rootvp;
	int error;
I 22
	int freeing;
E 22
	int flags = 0;
D 29
	extern int doforce;
E 29

#ifdef UNION_DIAGNOSTIC
	printf("union_unmount(mp = %x)\n", mp);
#endif
I 16
D 23

	/* only the mounter, or superuser can unmount */
	if ((p->p_cred->p_ruid != um->um_cred->cr_uid) &&
	    (error = suser(p->p_ucred, &p->p_acflag)))
		return (error);
E 23
E 16

D 29
	if (mntflags & MNT_FORCE) {
		/* union can never be rootfs so don't check for it */
		if (!doforce)
			return (EINVAL);
E 29
I 29
	if (mntflags & MNT_FORCE)
E 29
		flags |= FORCECLOSE;
D 29
	}
E 29

	if (error = union_root(mp, &um_rootvp))
		return (error);
I 22

	/*
	 * Keep flushing vnodes from the mount list.
	 * This is needed because of the un_pvp held
	 * reference to the parent vnode.
	 * If more vnodes have been freed on a given pass,
	 * the try again.  The loop will iterate at most
	 * (d) times, where (d) is the maximum tree depth
	 * in the filesystem.
	 */
	for (freeing = 0; vflush(mp, um_rootvp, flags) != 0;) {
		struct vnode *vp;
		int n;

		/* count #vnodes held on mount list */
		for (n = 0, vp = mp->mnt_vnodelist.lh_first;
				vp != NULLVP;
				vp = vp->v_mntvnodes.le_next)
			n++;

		/* if this is unchanged then stop */
		if (n == freeing)
			break;

		/* otherwise try once more time */
		freeing = n;
	}

	/* At this point the root vnode should have a single reference */
E 22
D 3
	if (um_rootvp->v_usecount > 1)
E 3
I 3
	if (um_rootvp->v_usecount > 1) {
		vput(um_rootvp);
E 3
		return (EBUSY);
D 3
	if (error = vflush(mp, um_rootvp, flags))
E 3
I 3
	}
D 22
	if (error = vflush(mp, um_rootvp, flags)) {
		vput(um_rootvp);
E 3
		return (error);
I 3
	}
E 22
E 3

#ifdef UNION_DIAGNOSTIC
D 22
	vprint("alias root of lower", um_rootvp);
E 22
I 22
	vprint("union root", um_rootvp);
E 22
#endif	 
	/*
	 * Discard references to upper and lower target vnodes.
	 */
D 9
	vrele(um->um_lowervp);
E 9
I 9
	if (um->um_lowervp)
		vrele(um->um_lowervp);
E 9
	vrele(um->um_uppervp);
	crfree(um->um_cred);
	/*
	 * Release reference on underlying root vnode
	 */
D 3
	vrele(um_rootvp);
E 3
I 3
	vput(um_rootvp);
E 3
	/*
	 * And blow it away for future re-use
	 */
D 27
	vgone(um_rootvp);
E 27
I 27
D 30
	VOP_REVOKE(um_rootvp, 0);
E 30
I 30
	vgone(um_rootvp);
E 30
E 27
	/*
	 * Finally, throw away the union_mount structure
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
union_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
I 31
	struct proc *p = curproc;	/* XXX */
E 31
	struct union_mount *um = MOUNTTOUNIONMOUNT(mp);
	int error;
I 15
	int loselock;
E 15

D 20
#ifdef UNION_DIAGNOSTIC
	printf("union_root(mp = %x, lvp = %x, uvp = %x)\n", mp,
			um->um_lowervp,
			um->um_uppervp);
#endif

E 20
	/*
	 * Return locked reference to root.
	 */
I 3
	VREF(um->um_uppervp);
I 10
D 15
	VOP_LOCK(um->um_uppervp);
E 15
I 15
	if ((um->um_op == UNMNT_BELOW) &&
	     VOP_ISLOCKED(um->um_uppervp)) {
		loselock = 1;
	} else {
D 31
		VOP_LOCK(um->um_uppervp);
E 31
I 31
		vn_lock(um->um_uppervp, LK_EXCLUSIVE | LK_RETRY, p);
E 31
		loselock = 0;
	}
E 15
E 10
D 9
	VREF(um->um_lowervp);
E 9
I 9
	if (um->um_lowervp)
		VREF(um->um_lowervp);
E 9
E 3
D 4
	error = union_allocvp(vpp, mp, (struct vnode *) 0,
E 4
I 4
	error = union_allocvp(vpp, mp,
			      (struct vnode *) 0,
			      (struct vnode *) 0,
E 4
			      (struct componentname *) 0,
			      um->um_uppervp,
D 24
			      um->um_lowervp);
E 24
I 24
			      um->um_lowervp,
			      1);
E 24
D 3
	if (error == 0)
E 3
I 3

	if (error) {
I 15
D 32
		if (!loselock)
D 31
			VOP_UNLOCK(um->um_uppervp);
E 31
I 31
			VOP_UNLOCK(um->um_uppervp, 0, p);
E 31
E 15
		vrele(um->um_uppervp);
E 32
I 32
		if (loselock)
			vrele(um->um_uppervp);
		else
			vput(um->um_uppervp);
E 32
D 9
		vrele(um->um_lowervp);
E 9
I 9
		if (um->um_lowervp)
			vrele(um->um_lowervp);
E 9
	} else {
E 3
D 19
		(*vpp)->v_flag |= VROOT;
E 19
I 15
		if (loselock)
			VTOUNION(*vpp)->un_flags &= ~UN_ULOCK;
E 15
I 3
	}
E 3

	return (error);
}

int
D 28
union_quotactl(mp, cmd, uid, arg, p)
	struct mount *mp;
	int cmd;
	uid_t uid;
	caddr_t arg;
	struct proc *p;
{

	return (EOPNOTSUPP);
}

int
E 28
union_statfs(mp, sbp, p)
	struct mount *mp;
	struct statfs *sbp;
	struct proc *p;
{
	int error;
	struct union_mount *um = MOUNTTOUNIONMOUNT(mp);
	struct statfs mstat;
	int lbsize;

#ifdef UNION_DIAGNOSTIC
	printf("union_statfs(mp = %x, lvp = %x, uvp = %x)\n", mp,
			um->um_lowervp,
	       		um->um_uppervp);
#endif

	bzero(&mstat, sizeof(mstat));

D 9
	error = VFS_STATFS(um->um_lowervp->v_mount, &mstat, p);
	if (error)
		return (error);
E 9
I 9
	if (um->um_lowervp) {
		error = VFS_STATFS(um->um_lowervp->v_mount, &mstat, p);
		if (error)
			return (error);
	}
E 9

	/* now copy across the "interesting" information and fake the rest */
#if 0
	sbp->f_type = mstat.f_type;
	sbp->f_flags = mstat.f_flags;
	sbp->f_bsize = mstat.f_bsize;
	sbp->f_iosize = mstat.f_iosize;
#endif
	lbsize = mstat.f_bsize;
	sbp->f_blocks = mstat.f_blocks;
	sbp->f_bfree = mstat.f_bfree;
	sbp->f_bavail = mstat.f_bavail;
	sbp->f_files = mstat.f_files;
	sbp->f_ffree = mstat.f_ffree;

	error = VFS_STATFS(um->um_uppervp->v_mount, &mstat, p);
	if (error)
		return (error);

D 14
	sbp->f_type = mstat.f_type;
E 14
I 14
D 28
	sbp->f_type = MOUNT_UNION;
E 28
E 14
	sbp->f_flags = mstat.f_flags;
	sbp->f_bsize = mstat.f_bsize;
	sbp->f_iosize = mstat.f_iosize;

	/*
	 * if the lower and upper blocksizes differ, then frig the
	 * block counts so that the sizes reported by df make some
	 * kind of sense.  none of this makes sense though.
	 */

D 25
	if (mstat.f_bsize != lbsize) {
E 25
I 25
	if (mstat.f_bsize != lbsize)
E 25
		sbp->f_blocks = sbp->f_blocks * lbsize / mstat.f_bsize;
D 25
		sbp->f_bfree = sbp->f_bfree * lbsize / mstat.f_bsize;
		sbp->f_bavail = sbp->f_bavail * lbsize / mstat.f_bsize;
	}
E 25
I 25

	/*
	 * The "total" fields count total resources in all layers,
	 * the "free" fields count only those resources which are
	 * free in the upper layer (since only the upper layer
	 * is writeable).
	 */
E 25
	sbp->f_blocks += mstat.f_blocks;
D 25
	sbp->f_bfree += mstat.f_bfree;
	sbp->f_bavail += mstat.f_bavail;
E 25
I 25
	sbp->f_bfree = mstat.f_bfree;
	sbp->f_bavail = mstat.f_bavail;
E 25
	sbp->f_files += mstat.f_files;
D 25
	sbp->f_ffree += mstat.f_ffree;
E 25
I 25
	sbp->f_ffree = mstat.f_ffree;
E 25

	if (sbp != &mp->mnt_stat) {
I 28
		sbp->f_type = mp->mnt_vfc->vfc_typenum;
E 28
		bcopy(&mp->mnt_stat.f_fsid, &sbp->f_fsid, sizeof(sbp->f_fsid));
		bcopy(mp->mnt_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->mnt_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
	}
	return (0);
}

D 28
int
union_sync(mp, waitfor, cred, p)
	struct mount *mp;
	int waitfor;
	struct ucred *cred;
	struct proc *p;
{
E 28
I 28
/*
 * XXX - Assumes no data cached at union layer.
 */
#define union_sync ((int (*) __P((struct mount *, int, struct ucred *, \
	    struct proc *)))nullop)
E 28

D 28
	/*
	 * XXX - Assumes no data cached at union layer.
	 */
	return (0);
}
E 28
I 28
#define union_fhtovp ((int (*) __P((struct mount *, struct fid *, \
	    struct mbuf *, struct vnode **, int *, struct ucred **)))eopnotsupp)
int union_init __P((struct vfsconf *));
#define union_quotactl ((int (*) __P((struct mount *, int, uid_t, caddr_t, \
	    struct proc *)))eopnotsupp)
#define union_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
	    size_t, struct proc *)))eopnotsupp)
#define union_vget ((int (*) __P((struct mount *, ino_t, struct vnode **))) \
	    eopnotsupp)
#define union_vptofh ((int (*) __P((struct vnode *, struct fid *)))eopnotsupp)
E 28

D 28
int
union_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{
	
	return (EOPNOTSUPP);
}

int
union_fhtovp(mp, fidp, nam, vpp, exflagsp, credanonp)
	struct mount *mp;
	struct fid *fidp;
	struct mbuf *nam;
	struct vnode **vpp;
	int *exflagsp;
	struct ucred **credanonp;
{

	return (EOPNOTSUPP);
}

int
union_vptofh(vp, fhp)
	struct vnode *vp;
	struct fid *fhp;
{

	return (EOPNOTSUPP);
}

int union_init __P((void));

E 28
struct vfsops union_vfsops = {
	union_mount,
	union_start,
	union_unmount,
	union_root,
	union_quotactl,
	union_statfs,
	union_sync,
	union_vget,
	union_fhtovp,
	union_vptofh,
	union_init,
I 28
	union_sysctl,
E 28
};
E 1
