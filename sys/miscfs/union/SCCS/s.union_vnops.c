h52511
s 00007/00000/01624
d D 8.32 95/06/23 13:48:08 pendry 44 43
c bandaid to avoid unlock panic until we do it right;
c trivia: this was the final delta done by CSRG
e
s 00006/00005/01618
d D 8.31 95/05/22 23:26:15 mckusick 43 42
c add in proper layer locking
e
s 00038/00024/01585
d D 8.30 95/05/20 17:10:15 mckusick 42 41
c cleanups (from mycroft)
e
s 00018/00020/01591
d D 8.29 95/05/20 16:22:36 pendry 41 40
c new locking
e
s 00004/00005/01607
d D 8.28 95/05/19 22:08:56 mckusick 40 39
c new mount locking protocol
e
s 00134/00114/01478
d D 8.27 95/05/14 00:48:40 mckusick 39 38
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00020/00002/01572
d D 8.26 95/05/11 16:04:32 pendry 38 37
c add union_revoke operator
e
s 00022/00005/01552
d D 8.25 95/03/24 03:37:00 pendry 37 36
c locking fixes (from jtkohl)
e
s 00016/00016/01541
d D 8.24 95/03/19 00:01:42 mckusick 36 35
c reverse arguments to VOP_LINK (to get them right)
e
s 00001/00001/01556
d D 8.23 95/02/22 19:25:46 mckusick 35 34
c vgone => VOP_REVOKE
e
s 00028/00012/01529
d D 8.22 94/12/10 13:03:08 pendry 34 33
c fix readdir for no-linear stacks
e
s 00007/00005/01534
d D 8.21 94/09/29 08:15:06 pendry 33 32
c ensure unlink/rmdir create whiteouts when appropriate
e
s 00013/00000/01526
d D 8.20 94/08/31 07:02:03 pendry 32 31
c add lease support
e
s 00078/00051/01448
d D 8.19 94/07/28 03:39:21 pendry 31 30
c changes for whiteouts and union filesystem
e
s 00016/00000/01483
d D 8.18 94/06/24 14:43:48 pendry 30 29
c checkpoint (first pass at "...")
e
s 00008/00000/01475
d D 8.17 94/06/17 09:45:53 pendry 29 28
c keep track of parent union node, so allowing .. to refer to
c the correct union node.
e
s 00001/00001/01474
d D 8.16 94/06/16 08:35:23 pendry 28 27
c fixup fsid correctly in union_getattr
e
s 00010/00007/01465
d D 8.15 94/06/04 19:57:16 mckusick 27 25
c add cookie and eofflag parameters to readdir
e
s 00010/00000/01472
d R 8.15 94/06/04 19:48:30 mckusick 26 25
c add cookie and eofflag parameters to readdir
e
s 00002/00001/01470
d D 8.14 94/05/24 04:43:05 pendry 25 24
c in union_lock: don't lock lower layer when reference
c count is zero.  this avoids deadlocking through getnewvnode/vgone.
e
s 00038/00089/01433
d D 8.13 94/05/17 19:33:01 pendry 24 23
c alter link to do a copyup when possible.
c open now uses the abstracted copyup.
e
s 00000/00001/01522
d D 8.12 94/05/10 00:05:57 pendry 23 22
c fix ref panic in link - same as previous panic but covering
c the case where a lower layer link is requested.  need to do a copyup
c to fix this right.
e
s 00000/00003/01523
d D 8.11 94/05/07 13:20:17 pendry 22 21
c fix lock/ref panic
e
s 00042/00001/01484
d D 8.10 94/05/07 13:19:51 pendry 21 20
c keep track of vnode size changes.
e
s 00034/00032/01451
d D 8.9 94/04/29 03:25:52 pendry 20 19
c allow all forms of upper-layer rename.
c don't lock (from) arguments to VOP_RENAME.
c KNF
e
s 00017/00003/01466
d D 8.8 94/04/28 06:36:01 pendry 19 18
c more paranoid checking in union_unlock.
c workaround locking uncertainty in VOP_GETATTR.
c do vgone on anon union_nodes in union_inactive.
e
s 00009/00009/01460
d D 8.7 94/04/24 08:46:23 pendry 18 17
c handle weird cases of stepping back across mount points
e
s 00076/00006/01393
d D 8.6 94/02/17 16:35:58 pendry 17 16
c implement new access policy
c fixup locking for UNMNT_BELOW.
e
s 00015/00005/01384
d D 8.5 94/02/17 11:22:06 pendry 16 15
c re-order locking to avoid races
e
s 00041/00007/01348
d D 8.4 94/02/11 17:08:32 pendry 15 14
c fixup the link count on directories
e
s 00035/00012/01320
d D 8.3 94/02/10 20:32:03 pendry 14 13
c make sure open(..., O_TRUNC) works right.
e
s 00001/00001/01331
d D 8.2 94/02/10 18:52:30 pendry 13 12
c use miscfs include path
e
s 00000/00000/01332
d D 8.1 94/02/10 18:50:25 pendry 12 11
c up to v8
e
s 00004/00025/01328
d D 2.2 94/02/10 18:38:12 pendry 11 10
c cleanup & lint
e
s 00114/00061/01239
d D 2.1 94/02/10 14:08:24 pendry 10 9
c new locking scheme
e
s 00009/00005/01291
d D 1.9 94/02/08 16:16:03 pendry 9 8
c checkpoint
e
s 00006/00002/01290
d D 1.8 94/02/07 21:35:16 pendry 8 7
c checkpoint
e
s 00031/00019/01261
d D 1.7 94/02/07 16:13:14 pendry 7 6
c checkpoint
e
s 00064/00104/01216
d D 1.6 94/02/04 17:50:32 pendry 6 5
c checkpoint
e
s 00061/00080/01259
d D 1.5 94/02/03 20:07:58 pendry 5 4
c checkpoint
e
s 00046/00024/01293
d D 1.4 94/02/03 12:24:48 pendry 4 3
c checkpoint
e
s 00158/00110/01159
d D 1.3 94/02/01 20:45:34 pendry 3 2
c checkpoint
e
s 00753/00275/00516
d D 1.2 94/02/01 17:11:09 pendry 2 1
c checkpoint
e
s 00791/00000/00000
d D 1.1 94/01/28 09:42:44 pendry 1 0
c date and time created 94/01/28 09:42:44 by pendry
e
u
U
t
T
I 1
/*
D 37
 * Copyright (c) 1992, 1993, 1994 The Regents of the University of California.
 * Copyright (c) 1992, 1993, 1994 Jan-Simon Pendry.
 * All rights reserved.
E 37
I 37
 * Copyright (c) 1992, 1993, 1994, 1995 Jan-Simon Pendry.
 * Copyright (c) 1992, 1993, 1994, 1995
 *	The Regents of the University of California.  All rights reserved.
E 37
 *
 * This code is derived from software contributed to Berkeley by
D 2
 * Jan-Simon Pendry and by John Heidemann of the UCLA Ficus project.
E 2
I 2
 * Jan-Simon Pendry.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/file.h>
D 6
#include <sys/filedesc.h>
E 6
#include <sys/time.h>
I 31
#include <sys/stat.h>
E 31
#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
#include <sys/buf.h>
I 11
#include <sys/queue.h>
I 39
#include <sys/lock.h>
E 39
E 11
D 13
#include "union.h"
E 13
I 13
#include <miscfs/union/union.h>
E 13

I 17
D 39
#define FIXUP(un) { \
E 39
I 39
#define FIXUP(un, p) { \
E 39
	if (((un)->un_flags & UN_ULOCK) == 0) { \
D 39
		union_fixup(un); \
E 39
I 39
		union_fixup(un, p); \
E 39
	} \
}

static void
D 39
union_fixup(un)
E 39
I 39
union_fixup(un, p)
E 39
	struct union_node *un;
I 39
	struct proc *p;
E 39
{

D 39
	VOP_LOCK(un->un_uppervp);
E 39
I 39
	vn_lock(un->un_uppervp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
	un->un_flags |= UN_ULOCK;
}

E 17
I 3
D 6
/*
 * Create a shadow directory in the upper layer.
 * The new vnode is returned locked.
 */
E 6
E 3
D 2

int union_bug_bypass = 0;   /* for debugging: enables bypass printf'ing */

/*
 * This is the 10-Apr-92 bypass routine.
 *    This version has been optimized for speed, throwing away some
 * safety checks.  It should still always work, but it's not as
 * robust to programmer errors.
 *    Define SAFETY to include some error checking code.
 *
 * In general, we map all vnodes going down and unmap them on the way back.
 * As an exception to this, vnodes can be marked "unmapped" by setting
 * the Nth bit in operation's vdesc_flags.
 *
 * Also, some BSD vnode operations have the side effect of vrele'ing
 * their arguments.  With stacking, the reference counts are held
 * by the upper node, not the lower one, so we must handle these
 * side-effects here.  This is not of concern in Sun-derived systems
 * since there are no such side-effects.
 *
 * This makes the following assumptions:
 * - only one returned vpp
 * - no INOUT vpp's (Sun's vop_open has one of these)
 * - the vnode operation vector of the first vnode should be used
 *   to determine what implementation of the op should be invoked
 * - all mapped vnodes are of our vnode-type (NEEDSWORK:
 *   problems on rmdir'ing mount points and renaming?)
 */ 
int
union_bypass(ap)
	struct vop_generic_args /* {
		struct vnodeop_desc *a_desc;
		<other random data follows, presumably>
	} */ *ap;
{
	struct vnode **this_vp_p;
	int error;
	struct vnode *old_vps[VDESC_MAX_VPS];
	struct vnode **vps_p[VDESC_MAX_VPS];
	struct vnode ***vppp;
	struct vnodeop_desc *descp = ap->a_desc;
	int reles, i;

	if (union_bug_bypass)
		printf ("union_bypass: %s\n", descp->vdesc_name);

#ifdef SAFETY
	/*
	 * We require at least one vp.
	 */
	if (descp->vdesc_vp_offsets == NULL ||
	    descp->vdesc_vp_offsets[0] == VDESC_NO_OFFSET)
		panic ("union_bypass: no vp's in map.\n");
#endif

	/*
	 * Map the vnodes going in.
	 * Later, we'll invoke the operation based on
	 * the first mapped vnode's operation vector.
	 */
	reles = descp->vdesc_flags;
	for (i = 0; i < VDESC_MAX_VPS; reles >>= 1, i++) {
		if (descp->vdesc_vp_offsets[i] == VDESC_NO_OFFSET)
			break;   /* bail out at end of list */
		vps_p[i] = this_vp_p = 
			VOPARG_OFFSETTO(struct vnode **, descp->vdesc_vp_offsets[i],ap);
		/*
		 * We're not guaranteed that any but the first vnode
		 * are of our type.  Check for and don't map any
		 * that aren't.  (We must always map first vp or vclean fails.)
		 */
		if (i && (*this_vp_p)->v_op != union_vnodeop_p) {
			old_vps[i] = NULL;
		} else {
			old_vps[i] = *this_vp_p;
			*(vps_p[i]) = OTHERVP(*this_vp_p);
			/*
			 * XXX - Several operations have the side effect
			 * of vrele'ing their vp's.  We must account for
			 * that.  (This should go away in the future.)
			 */
			if (reles & 1)
				VREF(*this_vp_p);
		}
			
	}

	/*
	 * Call the operation on the lower layer
	 * with the modified argument structure.
	 */
	error = VCALL(*(vps_p[0]), descp->vdesc_offset, ap);

	/*
	 * Maintain the illusion of call-by-value
	 * by restoring vnodes in the argument structure
	 * to their original value.
	 */
	reles = descp->vdesc_flags;
	for (i = 0; i < VDESC_MAX_VPS; reles >>= 1, i++) {
		if (descp->vdesc_vp_offsets[i] == VDESC_NO_OFFSET)
			break;   /* bail out at end of list */
		if (old_vps[i]) {
			*(vps_p[i]) = old_vps[i];
			if (reles & 1)
				vrele(*(vps_p[i]));
		}
	}

	/*
	 * Map the possible out-going vpp
	 * (Assumes that the lower layer always returns
	 * a VREF'ed vpp unless it gets an error.)
	 */
	if (descp->vdesc_vpp_offset != VDESC_NO_OFFSET &&
	    !(descp->vdesc_flags & VDESC_NOMAP_VPP) &&
	    !error) {
		/*
		 * XXX - even though some ops have vpp returned vp's,
		 * several ops actually vrele this before returning.
		 * We must avoid these ops.
		 * (This should go away when these ops are regularized.)
		 */
		if (descp->vdesc_flags & VDESC_VPP_WILLRELE)
			goto out;
		vppp = VOPARG_OFFSETTO(struct vnode***,
				 descp->vdesc_vpp_offset,ap);
		panic("union: failed to handled returned vnode");
		error = union_allocvp(0, 0, 0, 0, 0, 0);
	}

out:
	return (error);
}

/*
 * Check access permission on the union vnode.
 * The access check being enforced is to check
 * against both the underlying vnode, and any
 * copied vnode.  This ensures that no additional
 * file permissions are given away simply because
 * the user caused an implicit file copy.
 */
int
union_access(ap)
	struct vop_access_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_vp;
		int a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	struct union_node *un = VTOUNION(ap->a_vp);
	struct vnode *vp;

	if (vp = un->un_lowervp) {
		int error;

		error = VOP_ACCESS(vp, ap->a_mode, ap->a_cred, ap->a_p);
		if (error)
			return (error);
	}

	if (vp = un->un_uppervp)
		return (VOP_ACCESS(vp, ap->a_mode, ap->a_cred, ap->a_p));
	
	return (0);
}

E 2
static int
D 6
union_mkshadow(dvp, cnp, vpp)
	struct vnode *dvp;
	struct componentname *cnp;
	struct vnode *vpp;
{
	int error;
	struct vattr va;
	struct proc *p = cnp->cn_proc;
I 5
	struct componentname cn;
E 5
D 3
	int lockparent = (cnp->cn_flags & LOCKPARENT);
E 3

	/*
	 * policy: when creating the shadow directory in the
	 * upper layer, create it owned by the current user,
	 * group from parent directory, and mode 777 modified
	 * by umask (ie mostly identical to the mkdir syscall).
	 * (jsp, kb)
	 * TODO: create the directory owned by the user who
	 * did the mount (um->um_cred).
	 */

I 5
	/*
	 * A new componentname structure must be faked up because
	 * there is no way to know where the upper level cnp came
	 * from or what it is being used for.  This must duplicate
	 * some of the work done by NDINIT, some of the work done
	 * by namei, some of the work done by lookup and some of
	 * the work done by VOP_LOOKUP when given a CREATE flag.
	 * Conclusion: Horrible.
	 *
	 * The pathname buffer will be FREEed by VOP_MKDIR.
	 */
	cn.cn_pnbuf = malloc(cnp->cn_namelen+1, M_NAMEI, M_WAITOK);
	bcopy(cnp->cn_nameptr, cn.cn_pnbuf, cnp->cn_namelen+1);

	cn.cn_nameiop = CREATE;
	cn.cn_flags = HASBUF | SAVENAME | ISLASTCN;
	cn.cn_proc = cnp->cn_proc;
	cn.cn_cred = cnp->cn_cred;
	cn.cn_nameptr = cn.cn_pnbuf;
	cn.cn_namelen = cnp->cn_namelen;
	cn.cn_hash = cnp->cn_hash;
	cn.cn_consume = cnp->cn_consume;

E 5
	VATTR_NULL(&va);
	va.va_type = VDIR;
	va.va_mode = UN_DIRMODE &~ p->p_fd->fd_cmask;
D 3
	if (lockparent)
		VOP_UNLOCK(dvp);
E 3
I 3
D 5
	VOP_UNLOCK(dvp);
E 5
I 5

	/* LEASE_CHECK: dvp is locked */
E 5
E 3
	LEASE_CHECK(dvp, p, p->p_ucred, LEASE_WRITE);
I 5

E 5
I 3
	VREF(dvp);
I 5
	error = VOP_MKDIR(dvp, vpp, &cn, &va);
E 5
E 3
	VOP_LOCK(dvp);
D 5
	error = VOP_MKDIR(dvp, vpp, cnp, &va);
D 3
	if (lockparent)
		VOP_LOCK(dvp);
E 3
I 3
	VOP_LOCK(dvp);
E 5
E 3
	return (error);
}

static int
E 6
D 4
union_lookup1(dvp, vpp, cnp)
E 4
I 4
D 18
union_lookup1(udvp, dvp, vpp, cnp)
E 18
I 18
union_lookup1(udvp, dvpp, vpp, cnp)
E 18
	struct vnode *udvp;
E 4
D 18
	struct vnode *dvp;
E 18
I 18
	struct vnode **dvpp;
E 18
	struct vnode **vpp;
	struct componentname *cnp;
{
	int error;
I 39
	struct proc *p = cnp->cn_proc;
E 39
	struct vnode *tdvp;
I 18
	struct vnode *dvp;
E 18
	struct mount *mp;

I 18
	dvp = *dvpp;

E 18
I 5
	/*
	 * If stepping up the directory tree, check for going
	 * back across the mount point, in which case do what
	 * lookup would do by stepping back down the mount
	 * hierarchy.
	 */
E 5
	if (cnp->cn_flags & ISDOTDOT) {
D 18
		for (;;) {
E 18
I 18
		while ((dvp != udvp) && (dvp->v_flag & VROOT)) {
E 18
D 9
			if ((dvp->v_flag & VROOT) == 0 ||
			    (cnp->cn_flags & NOCROSSMOUNT))
E 9
I 9
			/*
			 * Don't do the NOCROSSMOUNT check
			 * at this level.  By definition,
			 * union fs deals with namespaces, not
			 * filesystems.
			 */
D 18
			if ((dvp->v_flag & VROOT) == 0)
E 9
				break;

E 18
			tdvp = dvp;
D 18
			dvp = dvp->v_mount->mnt_vnodecovered;
E 18
I 18
			*dvpp = dvp = dvp->v_mount->mnt_vnodecovered;
E 18
			vput(tdvp);
			VREF(dvp);
D 39
			VOP_LOCK(dvp);
E 39
I 39
			vn_lock(dvp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
		}
	}
D 7
	
E 7
I 7

E 7
        error = VOP_LOOKUP(dvp, &tdvp, cnp);
	if (error)
		return (error);

I 5
	/*
D 7
	 * If going back up the directory tree, then the parent directory
	 * will have been unlocked, unless lookup found the last
	 * component.  In which case, re-lock the node here to allow
	 * it to be unlocked again (phew) in union_lookup.
E 7
I 7
	 * The parent directory will have been unlocked, unless lookup
	 * found the last component.  In which case, re-lock the node
	 * here to allow it to be unlocked again (phew) in union_lookup.
E 7
	 */
D 7
	if ((cnp->cn_flags & ISDOTDOT) && !(cnp->cn_flags & ISLASTCN))
E 7
I 7
	if (dvp != tdvp && !(cnp->cn_flags & ISLASTCN))
E 7
D 39
		VOP_LOCK(dvp);
E 39
I 39
		vn_lock(dvp, LK_EXCLUSIVE | LK_RETRY, p);
E 39

E 5
	dvp = tdvp;
I 5

	/*
	 * Lastly check if the current node is a mount point in
D 9
	 * which cse walk up the mount hierarchy making sure not to
E 9
I 9
	 * which case walk up the mount hierarchy making sure not to
E 9
	 * bump into the root of the mount tree (ie. dvp != udvp).
	 */
E 5
D 4
	while ((dvp->v_type == VDIR) && (mp = dvp->v_mountedhere) &&
E 4
I 4
	while (dvp != udvp && (dvp->v_type == VDIR) &&
D 9
	       (mp = dvp->v_mountedhere) &&
E 4
	       (cnp->cn_flags & NOCROSSMOUNT) == 0) {
E 9
I 9
	       (mp = dvp->v_mountedhere)) {
E 9

D 40
		if (mp->mnt_flag & MNT_MLOCK) {
			mp->mnt_flag |= MNT_MWAIT;
			sleep((caddr_t) mp, PVFS);
E 40
I 40
		if (vfs_busy(mp, 0, 0, p))
E 40
			continue;
D 40
		}
E 40

D 40
		if (error = VFS_ROOT(mp, &tdvp)) {
E 40
I 40
		error = VFS_ROOT(mp, &tdvp);
		vfs_unbusy(mp, p);
		if (error) {
E 40
			vput(dvp);
			return (error);
		}

D 3
		vput(tdvp);
E 3
I 3
		vput(dvp);
E 3
		dvp = tdvp;
	}

	*vpp = dvp;
	return (0);
}

int
union_lookup(ap)
	struct vop_lookup_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
	} */ *ap;
{
I 3
	int error;
E 3
	int uerror, lerror;
	struct vnode *uppervp, *lowervp;
	struct vnode *upperdvp, *lowerdvp;
	struct vnode *dvp = ap->a_dvp;
D 4
	struct union_node *dun = VTOUNION(ap->a_dvp);
E 4
I 4
	struct union_node *dun = VTOUNION(dvp);
E 4
	struct componentname *cnp = ap->a_cnp;
I 39
	struct proc *p = cnp->cn_proc;
E 39
	int lockparent = cnp->cn_flags & LOCKPARENT;
I 5
	int rdonly = cnp->cn_flags & RDONLY;
I 6
	struct union_mount *um = MOUNTTOUNIONMOUNT(dvp->v_mount);
I 17
	struct ucred *saved_cred;
I 31
	int iswhiteout;
	struct vattr va;
E 31
E 17
E 6
E 5

I 30
#ifdef notyet
	if (cnp->cn_namelen == 3 &&
			cnp->cn_nameptr[2] == '.' &&
			cnp->cn_nameptr[1] == '.' &&
			cnp->cn_nameptr[0] == '.') {
		dvp = *ap->a_vpp = LOWERVP(ap->a_dvp);
		if (dvp == NULLVP)
			return (ENOENT);
		VREF(dvp);
D 39
		VOP_LOCK(dvp);
E 39
I 39
		vn_lock(dvp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
		if (!lockparent || !(cnp->cn_flags & ISLASTCN))
D 39
			VOP_UNLOCK(ap->a_dvp);
E 39
I 39
			VOP_UNLOCK(ap->a_dvp, 0, p);
E 39
		return (0);
	}
#endif

E 30
I 3
	cnp->cn_flags |= LOCKPARENT;

E 3
	upperdvp = dun->un_uppervp;
	lowerdvp = dun->un_lowervp;
I 3
D 6
	uppervp = 0;
	lowervp = 0;
E 6
I 6
	uppervp = NULLVP;
	lowervp = NULLVP;
I 31
	iswhiteout = 0;
E 31
E 6
E 3

	/*
	 * do the lookup in the upper level.
	 * if that level comsumes additional pathnames,
	 * then assume that something special is going
	 * on and just return that vnode.
	 */
D 4
	uppervp = 0;
E 4
D 20
	if (upperdvp) {
E 20
I 20
	if (upperdvp != NULLVP) {
E 20
I 17
D 39
		FIXUP(dun);
E 39
I 39
		FIXUP(dun, p);
E 39
E 17
I 3
D 10
		VOP_LOCK(upperdvp);
E 10
E 3
D 4
		uerror = union_lookup1(upperdvp, &uppervp, cnp);
I 3
		VOP_UNLOCK(upperdvp);
E 4
I 4
D 6
		uerror = union_lookup1(
			MOUNTTOUNIONMOUNT(dvp->v_mount)->um_uppervp,
			upperdvp, &uppervp, cnp);
E 6
I 6
D 18
		uerror = union_lookup1(um->um_uppervp, upperdvp,
E 18
I 18
		uerror = union_lookup1(um->um_uppervp, &upperdvp,
E 18
					&uppervp, cnp);
E 6
D 10
		if (uppervp != upperdvp)
			VOP_UNLOCK(upperdvp);
E 10
I 10
		/*if (uppervp == upperdvp)
			dun->un_flags |= UN_KLOCK;*/
E 10
E 4

E 3
		if (cnp->cn_consume != 0) {
			*ap->a_vpp = uppervp;
I 3
			if (!lockparent)
				cnp->cn_flags &= ~LOCKPARENT;
E 3
			return (uerror);
		}
I 31
		if (uerror == ENOENT || uerror == EJUSTRETURN) {
			if (cnp->cn_flags & ISWHITEOUT) {
				iswhiteout = 1;
			} else if (lowerdvp != NULLVP) {
				lerror = VOP_GETATTR(upperdvp, &va,
					cnp->cn_cred, cnp->cn_proc);
				if (lerror == 0 && (va.va_flags & OPAQUE))
					iswhiteout = 1;
			}
		}
E 31
D 3
		if (!lockparent)
			VOP_LOCK(upperdvp);
E 3
	} else {
		uerror = ENOENT;
	}

	/*
	 * in a similar way to the upper layer, do the lookup
	 * in the lower layer.   this time, if there is some
	 * component magic going on, then vput whatever we got
	 * back from the upper layer and return the lower vnode
	 * instead.
	 */
D 4
	lowervp = 0;
E 4
D 20
	if (lowerdvp) {
E 20
I 20
D 31
	if (lowerdvp != NULLVP) {
E 31
I 31
	if (lowerdvp != NULLVP && !iswhiteout) {
E 31
E 20
I 10
		int nameiop;

E 10
I 3
D 39
		VOP_LOCK(lowerdvp);
E 39
I 39
		vn_lock(lowerdvp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
I 10

		/*
		 * Only do a LOOKUP on the bottom node, since
		 * we won't be making changes to it anyway.
		 */
		nameiop = cnp->cn_nameiop;
		cnp->cn_nameiop = LOOKUP;
I 17
		if (um->um_op == UNMNT_BELOW) {
			saved_cred = cnp->cn_cred;
			cnp->cn_cred = um->um_cred;
		}
E 17
E 10
E 3
D 4
		lerror = union_lookup1(lowerdvp, &lowervp, cnp);
I 3
		VOP_UNLOCK(lowerdvp);
E 4
I 4
D 6
		lerror = union_lookup1(
			MOUNTTOUNIONMOUNT(dvp->v_mount)->um_lowervp,
			lowerdvp, &lowervp, cnp);
E 6
I 6
D 18
		lerror = union_lookup1(um->um_lowervp, lowerdvp,
E 18
I 18
		lerror = union_lookup1(um->um_lowervp, &lowerdvp,
E 18
D 10
					&lowervp, cnp);
E 10
I 10
				&lowervp, cnp);
I 17
		if (um->um_op == UNMNT_BELOW)
			cnp->cn_cred = saved_cred;
E 17
		cnp->cn_nameiop = nameiop;

E 10
E 6
		if (lowervp != lowerdvp)
D 39
			VOP_UNLOCK(lowerdvp);
E 39
I 39
			VOP_UNLOCK(lowerdvp, 0, p);
E 39
E 4

E 3
		if (cnp->cn_consume != 0) {
D 20
			if (uppervp) {
E 20
I 20
			if (uppervp != NULLVP) {
E 20
D 10
				vput(uppervp);
E 10
I 10
				if (uppervp == upperdvp)
					vrele(uppervp);
				else
					vput(uppervp);
E 10
D 6
				uppervp = 0;
E 6
I 6
				uppervp = NULLVP;
E 6
			}
			*ap->a_vpp = lowervp;
I 3
			if (!lockparent)
				cnp->cn_flags &= ~LOCKPARENT;
E 3
			return (lerror);
		}
D 3
		if (!lockparent)
			VOP_LOCK(lowerdvp);
E 3
	} else {
		lerror = ENOENT;
I 29
		if ((cnp->cn_flags & ISDOTDOT) && dun->un_pvp != NULLVP) {
			lowervp = LOWERVP(dun->un_pvp);
			if (lowervp != NULLVP) {
				VREF(lowervp);
D 39
				VOP_LOCK(lowervp);
E 39
I 39
				vn_lock(lowervp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
				lerror = 0;
			}
		}
E 29
	}

I 3
	if (!lockparent)
		cnp->cn_flags &= ~LOCKPARENT;

E 3
	/*
	 * at this point, we have uerror and lerror indicating
	 * possible errors with the lookups in the upper and lower
	 * layers.  additionally, uppervp and lowervp are (locked)
	 * references to existing vnodes in the upper and lower layers.
	 *
	 * there are now three cases to consider.
	 * 1. if both layers returned an error, then return whatever
	 *    error the upper layer generated.
	 *
	 * 2. if the top layer failed and the bottom layer succeeded
	 *    then two subcases occur.
	 *    a.  the bottom vnode is not a directory, in which
	 *	  case just return a new union vnode referencing
	 *	  an empty top layer and the existing bottom layer.
	 *    b.  the bottom vnode is a directory, in which case
	 *	  create a new directory in the top-level and
	 *	  continue as in case 3.
	 *
	 * 3. if the top layer succeeded then return a new union
	 *    vnode referencing whatever the new top layer and
	 *    whatever the bottom layer returned.
	 */

I 7
	*ap->a_vpp = NULLVP;

E 7
	/* case 1. */
	if ((uerror != 0) && (lerror != 0)) {
D 6
		*ap->a_vpp = 0;
E 6
I 6
D 7
		*ap->a_vpp = NULLVP;
E 7
E 6
		return (uerror);
	}

	/* case 2. */
	if (uerror != 0 /* && (lerror == 0) */ ) {
		if (lowervp->v_type == VDIR) { /* case 2b. */
I 10
			dun->un_flags &= ~UN_ULOCK;
D 39
			VOP_UNLOCK(upperdvp);
E 39
I 39
			VOP_UNLOCK(upperdvp, 0, p);
E 39
E 10
I 3
D 4
			VOP_LOCK(upperdvp);
E 4
I 4
D 5
			if (uppervp != upperdvp)
				VOP_LOCK(upperdvp);
E 5
I 5
D 6
			VOP_LOCK(upperdvp);
E 5
E 4
E 3
			uerror = union_mkshadow(upperdvp, cnp, &uppervp);
I 3
D 4
			VOP_UNLOCK(upperdvp);
E 4
I 4
			if (uppervp != upperdvp)
				VOP_UNLOCK(upperdvp);
E 6
I 6
			uerror = union_mkshadow(um, upperdvp, cnp, &uppervp);
I 10
D 39
			VOP_LOCK(upperdvp);
E 39
I 39
			vn_lock(upperdvp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
			dun->un_flags |= UN_ULOCK;

E 10
E 6
E 4
E 3
			if (uerror) {
D 20
				if (lowervp) {
E 20
I 20
				if (lowervp != NULLVP) {
E 20
					vput(lowervp);
D 6
					lowervp = 0;
E 6
I 6
					lowervp = NULLVP;
E 6
				}
				return (uerror);
			}
		}
	}

D 3
	return (union_allocvp(ap->a_vpp, dvp->v_mount, dvp, cnp,
			      uppervp, lowervp));
E 3
I 3
D 4
	error = union_allocvp(ap->a_vpp, dvp->v_mount, dvp, cnp,
E 4
I 4
D 6
	error = union_allocvp(ap->a_vpp, dvp->v_mount, dvp, upperdvp, cnp,
E 4
			      uppervp, lowervp);

E 6
D 10
	if (uppervp)
		VOP_UNLOCK(uppervp);
E 10
D 20
	if (lowervp)
E 20
I 20
	if (lowervp != NULLVP)
E 20
D 39
		VOP_UNLOCK(lowervp);
E 39
I 39
		VOP_UNLOCK(lowervp, 0, p);
E 39

I 6
	error = union_allocvp(ap->a_vpp, dvp->v_mount, dvp, upperdvp, cnp,
D 34
			      uppervp, lowervp);
E 34
I 34
			      uppervp, lowervp, 1);
E 34

E 6
	if (error) {
D 20
		if (uppervp)
E 20
I 20
		if (uppervp != NULLVP)
E 20
D 10
			vrele(uppervp);
E 10
I 10
			vput(uppervp);
E 10
D 20
		if (lowervp)
E 20
I 20
		if (lowervp != NULLVP)
E 20
			vrele(lowervp);
	} else {
D 4
		if (!lockparent)
			VOP_UNLOCK(*ap->a_vpp);
E 4
I 4
D 5
		if (!lockparent && (*ap->a_vpp != dvp))
			VOP_UNLOCK(dvp);
E 5
I 5
		if (*ap->a_vpp != dvp)
			if (!lockparent || !(cnp->cn_flags & ISLASTCN))
D 39
				VOP_UNLOCK(dvp);
E 39
I 39
				VOP_UNLOCK(dvp, 0, p);
E 39
E 5
E 4
	}

	return (error);
E 3
}

I 2
int
union_create(ap)
	struct vop_create_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
{
	struct union_node *un = VTOUNION(ap->a_dvp);
	struct vnode *dvp = un->un_uppervp;
I 39
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
E 39

D 20
	if (dvp) {
E 20
I 20
	if (dvp != NULLVP) {
E 20
		int error;
		struct vnode *vp;
I 34
		struct mount *mp;
E 34
D 4
		struct mount *mp = ap->a_dvp->v_mount;
E 4

I 17
D 39
		FIXUP(un);
E 39
I 39
		FIXUP(un, p);
E 39

E 17
		VREF(dvp);
D 10
		VOP_LOCK(dvp);
E 10
I 10
		un->un_flags |= UN_KLOCK;
I 34
		mp = ap->a_dvp->v_mount;
E 34
E 10
		vput(ap->a_dvp);
D 39
		error = VOP_CREATE(dvp, &vp, ap->a_cnp, ap->a_vap);
E 39
I 39
		error = VOP_CREATE(dvp, &vp, cnp, ap->a_vap);
E 39
		if (error)
			return (error);

I 6
D 10
		VOP_UNLOCK(vp);

E 10
E 6
D 39
		error = union_allocvp(
				ap->a_vpp,
D 4
				mp,
E 4
I 4
D 34
				ap->a_dvp->v_mount,
				ap->a_dvp,
E 34
I 34
				mp,
E 34
E 4
D 3
				un->un_uppervp,
E 3
I 3
				NULLVP,
I 34
				NULLVP,
E 34
E 3
				ap->a_cnp,
				vp,
D 34
				NULLVP);
E 34
I 34
				NULLVP,
				1);
E 39
I 39
		error = union_allocvp(ap->a_vpp, mp, NULLVP, NULLVP, cnp, vp,
				NULLVP, 1);
E 39
E 34
I 3
D 6
		VOP_UNLOCK(vp);
E 6
		if (error)
D 10
			vrele(vp);
E 10
I 10
			vput(vp);
E 10
E 3
		return (error);
	}

	vput(ap->a_dvp);
	return (EROFS);
}

int
I 31
union_whiteout(ap)
	struct vop_whiteout_args /* {
		struct vnode *a_dvp;
		struct componentname *a_cnp;
		int a_flags;
	} */ *ap;
{
	struct union_node *un = VTOUNION(ap->a_dvp);
I 39
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
E 39

	if (un->un_uppervp == NULLVP)
		return (EOPNOTSUPP);

D 39
	FIXUP(un);
	return (VOP_WHITEOUT(un->un_uppervp, ap->a_cnp, ap->a_flags));
E 39
I 39
	FIXUP(un, p);
	return (VOP_WHITEOUT(un->un_uppervp, cnp, ap->a_flags));
E 39
}

int
E 31
union_mknod(ap)
	struct vop_mknod_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
{
	struct union_node *un = VTOUNION(ap->a_dvp);
	struct vnode *dvp = un->un_uppervp;
I 39
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
E 39

D 20
	if (dvp) {
E 20
I 20
	if (dvp != NULLVP) {
E 20
		int error;
		struct vnode *vp;
I 34
		struct mount *mp;
E 34
D 4
		struct mount *mp = ap->a_dvp->v_mount;
E 4

I 17
D 39
		FIXUP(un);
E 39
I 39
		FIXUP(un, p);
E 39

E 17
		VREF(dvp);
D 10
		VOP_LOCK(dvp);
E 10
I 10
		un->un_flags |= UN_KLOCK;
I 34
		mp = ap->a_dvp->v_mount;
E 34
E 10
		vput(ap->a_dvp);
D 39
		error = VOP_MKNOD(dvp, &vp, ap->a_cnp, ap->a_vap);
E 39
I 39
		error = VOP_MKNOD(dvp, &vp, cnp, ap->a_vap);
E 39
		if (error)
			return (error);

D 3
		error = union_allocvp(
				ap->a_vpp,
				mp,
				un->un_uppervp,
				ap->a_cnp,
				vp,
				NULLVP);
E 3
I 3
D 20
		if (vp) {
E 20
I 20
		if (vp != NULLVP) {
E 20
I 6
D 10
			VOP_UNLOCK(vp);

E 10
E 6
D 39
			error = union_allocvp(
					ap->a_vpp,
D 4
					mp,
E 4
I 4
D 34
					ap->a_dvp->v_mount,
					ap->a_dvp,
E 34
I 34
					mp,
E 34
E 4
					NULLVP,
I 34
					NULLVP,
E 34
					ap->a_cnp,
					vp,
D 34
					NULLVP);
E 34
I 34
					NULLVP,
					1);
E 39
I 39
			error = union_allocvp(ap->a_vpp, mp, NULLVP, NULLVP,
					cnp, vp, NULLVP, 1);
E 39
E 34
D 6
			VOP_UNLOCK(vp);
E 6
			if (error)
D 10
				vrele(vp);
E 10
I 10
				vput(vp);
E 10
		}
E 3
		return (error);
	}

	vput(ap->a_dvp);
	return (EROFS);
}

E 2
D 5
/*
 * copyfile.  copy the vnode (fvp) to the vnode (tvp)
D 2
 * using a sequence of reads and writes.
E 2
I 2
 * using a sequence of reads and writes.  both (fvp)
 * and (tvp) are locked on entry and exit.
E 2
 */
static int
union_copyfile(p, cred, fvp, tvp)
	struct proc *p;
	struct ucred *cred;
	struct vnode *fvp;
	struct vnode *tvp;
{
	char *buf;
	struct uio uio;
	struct iovec iov;
	int error = 0;
	off_t offset;

	/*
	 * strategy:
	 * allocate a buffer of size MAXBSIZE.
	 * loop doing reads and writes, keeping track
	 * of the current uio offset.
	 * give up at the first sign of trouble.
	 */

	uio.uio_procp = p;
	uio.uio_segflg = UIO_SYSSPACE;
	offset = 0;

	VOP_UNLOCK(fvp);				/* XXX */
	LEASE_CHECK(fvp, p, cred, LEASE_READ);
	VOP_LOCK(fvp);					/* XXX */
	VOP_UNLOCK(tvp);				/* XXX */
	LEASE_CHECK(tvp, p, cred, LEASE_WRITE);
	VOP_LOCK(tvp);					/* XXX */

	buf = malloc(MAXBSIZE, M_TEMP, M_WAITOK);
	do {
		uio.uio_iov = &iov;
		uio.uio_iovcnt = 1;
		iov.iov_base = buf;
		iov.iov_len = MAXBSIZE;
		uio.uio_resid = iov.iov_len;
		uio.uio_offset = offset;
		uio.uio_rw = UIO_READ;
		error = VOP_READ(fvp, &uio, 0, cred);

		if (error == 0) {
			uio.uio_iov = &iov;
			uio.uio_iovcnt = 1;
			iov.iov_base = buf;
			iov.iov_len = MAXBSIZE - uio.uio_resid;
			uio.uio_rw = UIO_WRITE;
			uio.uio_resid = iov.iov_len;
			uio.uio_offset = offset;

			do {
				error = VOP_WRITE(tvp, &uio, 0, cred);
			} while (error == 0 && uio.uio_resid > 0);
			if (error == 0)
				offset = uio.uio_offset;
		}
	} while ((uio.uio_resid == 0) && (error == 0));

	free(buf, M_TEMP);
	return (error);
}

E 5
int
union_open(ap)
	struct vop_open_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_vp;
		int a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	struct union_node *un = VTOUNION(ap->a_vp);
I 3
	struct vnode *tvp;
E 3
	int mode = ap->a_mode;
	struct ucred *cred = ap->a_cred;
	struct proc *p = ap->a_p;
I 3
	int error;
E 3

	/*
	 * If there is an existing upper vp then simply open that.
	 */
D 2
	if (un->un_uppervp)
		return (VOP_OPEN(un->un_uppervp, mode, cred, p));
E 2
I 2
D 3
	if (un->un_uppervp) {
		int error;
E 2

I 2
		VOP_LOCK(un->un_uppervp);
		error = VOP_OPEN(un->un_uppervp, mode, cred, p);
		VOP_UNLOCK(un->un_lowervp);

		return (error);
	}

E 2
	/*
	 * If the lower vnode is being opened for writing, then
	 * copy the file contents to the upper vnode and open that,
	 * otherwise can simply open the lower vnode.
	 */
	if ((ap->a_mode & FWRITE) && (un->un_lowervp->v_type == VREG)) {
		int error;
		struct nameidata nd;
		struct filedesc *fdp = p->p_fd;
		int fmode;
		int cmode;

E 3
I 3
	tvp = un->un_uppervp;
	if (tvp == NULLVP) {
E 3
		/*
D 3
		 * Open the named file in the upper layer.  Note that
		 * the file may have come into existence *since* the lookup
		 * was done, since the upper layer may really be a
		 * loopback mount of some other filesystem... so open
		 * the file with exclusive create and barf if it already
		 * exists.
		 * XXX - perhaps shoudl re-lookup the node (once more with
		 * feeling) and simply open that.  Who knows.
E 3
I 3
		 * If the lower vnode is being opened for writing, then
		 * copy the file contents to the upper vnode and open that,
		 * otherwise can simply open the lower vnode.
E 3
		 */
D 3
		NDINIT(&nd, CREATE, 0, UIO_SYSSPACE, un->un_path, p);
		fmode = (O_CREAT|O_TRUNC|O_EXCL);
		cmode = UN_FILEMODE & ~fdp->fd_cmask;
		error = vn_open(&nd, fmode, cmode);
		if (error)
			return (error);
D 2
		un->un_uppervp = nd.ni_vp;
E 2
I 2
		un->un_uppervp = nd.ni_vp;	/* XXX */
		/* at this point, uppervp is locked */
E 3
I 3
		tvp = un->un_lowervp;
		if ((ap->a_mode & FWRITE) && (tvp->v_type == VREG)) {
D 6
			struct nameidata nd;
			struct filedesc *fdp = p->p_fd;
E 6
D 5
			int fmode;
E 5
I 5
D 24
			struct vnode *vp;
D 6
			/*int fmode;*/
E 5
			int cmode;
E 6
I 6
			int i;
E 6
E 3

E 2
D 3
		/*
		 * Now, if the file is being opened with truncation, then
		 * the (new) upper vnode is ready to fly, otherwise the
		 * data from the lower vnode must be copied to the upper
		 * layer first.  This only works for regular files (check
		 * is made above).
		 */
		if ((mode & O_TRUNC) == 0) {
			/* XXX - should not ignore errors from VOP_CLOSE */
I 2
			VOP_LOCK(un->un_lowervp);
E 2
			error = VOP_OPEN(un->un_lowervp, FREAD, cred, p);
			if (error == 0) {
				error = union_copyfile(p, cred,
					       un->un_lowervp, un->un_uppervp);
				(void) VOP_CLOSE(un->un_lowervp, FREAD);
E 3
I 3
			/*
			 * Open the named file in the upper layer.  Note that
			 * the file may have come into existence *since* the
			 * lookup was done, since the upper layer may really
			 * be a loopback mount of some other filesystem...
			 * so open the file with exclusive create and barf if
			 * it already exists.
D 7
			 * XXX - perhaps shoudl re-lookup the node (once more
E 7
I 7
			 * XXX - perhaps should re-lookup the node (once more
E 7
			 * with feeling) and simply open that.  Who knows.
			 */
I 5
D 6
			/*
E 5
			NDINIT(&nd, CREATE, 0, UIO_SYSSPACE, un->un_path, p);
			fmode = (O_CREAT|O_TRUNC|O_EXCL);
I 5
			*/
E 5
			cmode = UN_FILEMODE & ~fdp->fd_cmask;
D 5
			error = vn_open(&nd, fmode, cmode);
E 5
I 5
			error = union_vn_create(&vp, un, cmode, p);
E 6
I 6
			error = union_vn_create(&vp, un, p);
E 6
E 5
			if (error)
				return (error);
D 5
			un->un_uppervp = nd.ni_vp;	/* XXX */
E 5
I 5
D 10
			un->un_uppervp = vp;	/* XXX */
E 10
I 10

E 10
E 5
			/* at this point, uppervp is locked */
I 10
D 11
			un->un_uppervp = vp;	/* XXX */
E 11
I 11
			union_newupper(un, vp);
E 11
			un->un_flags |= UN_ULOCK;
E 10

			/*
			 * Now, if the file is being opened with truncation,
			 * then the (new) upper vnode is ready to fly,
			 * otherwise the data from the lower vnode must be
			 * copied to the upper layer first.  This only works
			 * for regular files (check is made above).
			 */
			if ((mode & O_TRUNC) == 0) {
				/*
				 * XXX - should not ignore errors
				 * from VOP_CLOSE
				 */
D 5
				VOP_LOCK(un->un_lowervp);
E 5
I 5
				VOP_LOCK(tvp);
E 5
				error = VOP_OPEN(tvp, FREAD, cred, p);
				if (error == 0) {
					error = union_copyfile(p, cred,
						       tvp, un->un_uppervp);
					VOP_UNLOCK(tvp);
					(void) VOP_CLOSE(tvp, FREAD);
				} else {
					VOP_UNLOCK(tvp);
				}
I 10

I 17
#ifdef UNION_DIAGNOSTIC
E 17
D 14
				un->un_flags &= ~UN_ULOCK;
E 10
				VOP_UNLOCK(un->un_uppervp);
D 7
				(void) VOP_CLOSE(un->un_uppervp, FWRITE);
E 7
I 7
D 8
				union_vn_close(un->un_uppervp, FWRITE);
E 8
I 8
				union_vn_close(un->un_uppervp, FWRITE, cred, p);
E 8
E 7
				VOP_LOCK(un->un_uppervp);
I 10
				un->un_flags |= UN_ULOCK;

E 14
E 10
I 6
				if (!error)
D 7
					uprintf("union: copied up\n",
E 7
I 7
					uprintf("union: copied up %s\n",
E 7
								un->un_path);
I 17
#endif
E 17
E 6
E 3
			}
I 6

I 14
			un->un_flags &= ~UN_ULOCK;
			VOP_UNLOCK(un->un_uppervp);
			union_vn_close(un->un_uppervp, FWRITE, cred, p);
			VOP_LOCK(un->un_uppervp);
			un->un_flags |= UN_ULOCK;

E 14
			/*
			 * Subsequent IOs will go to the top layer, so
			 * call close on the lower vnode and open on the
			 * upper vnode to ensure that the filesystem keeps
			 * its references counts right.  This doesn't do
			 * the right thing with (cred) and (FREAD) though.
			 * Ignoring error returns is not righ, either.
			 */
D 7
			for (i = 0; i < un->un_open; i++) {
E 7
I 7
			for (i = 0; i < un->un_openl; i++) {
E 7
				(void) VOP_CLOSE(tvp, FREAD);
				(void) VOP_OPEN(un->un_uppervp, FREAD, cred, p);
			}
D 7
			un->un_open = 0;
E 7
I 7
			un->un_openl = 0;
E 7

E 24
I 24
			error = union_copyup(un, (mode&O_TRUNC) == 0, cred, p);
E 24
E 6
I 2
D 3
			VOP_UNLOCK(un->un_lowervp);
E 3
I 3
			if (error == 0)
				error = VOP_OPEN(un->un_uppervp, mode, cred, p);
E 3
D 10
			VOP_UNLOCK(un->un_uppervp);
E 10
E 2
D 3
			(void) VOP_CLOSE(un->un_uppervp, FWRITE);
I 2
			VOP_LOCK(un->un_uppervp);
E 3
I 3
			return (error);
E 3
E 2
		}
I 10

		/*
		 * Just open the lower vnode
		 */
E 10
I 6
D 7
		un->un_open++;
E 7
I 7
		un->un_openl++;
I 10
D 39
		VOP_LOCK(tvp);
E 39
I 39
		vn_lock(tvp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
		error = VOP_OPEN(tvp, mode, cred, p);
D 39
		VOP_UNLOCK(tvp);
E 39
I 39
		VOP_UNLOCK(tvp, 0, p);
E 39

		return (error);
E 10
E 7
E 6
D 3
		if (error == 0)
			error = VOP_OPEN(un->un_uppervp, FREAD, cred, p);
		return (error);
E 3
	}

I 17
D 39
	FIXUP(un);
E 39
I 39
	FIXUP(un, p);
E 39

E 17
D 3
	return (VOP_OPEN(un->un_lowervp, mode, cred, p));
E 3
I 3
D 10
	VOP_LOCK(tvp);
E 10
	error = VOP_OPEN(tvp, mode, cred, p);
D 10
	VOP_UNLOCK(tvp);
E 10

	return (error);
E 3
}

I 2
int
union_close(ap)
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
I 6
	struct union_node *un = VTOUNION(ap->a_vp);
	struct vnode *vp;
E 6

D 6
	return (VOP_CLOSE(OTHERVP(ap->a_vp), ap->a_fflag, ap->a_cred, ap->a_p));
E 6
I 6
D 20
	if (un->un_uppervp) {
E 20
I 20
D 42
	if (un->un_uppervp != NULLVP) {
E 20
		vp = un->un_uppervp;
	} else {
E 42
I 42
	if ((vp = un->un_uppervp) == NULLVP) {
E 42
D 7
#ifdef DIAGNOSTIC
		if (un->un_open <= 0)
			panic("union: un_open cnt");
E 7
I 7
#ifdef UNION_DIAGNOSTIC
		if (un->un_openl <= 0)
			panic("union: un_openl cnt");
E 7
#endif
D 7
		--un->un_open;
E 7
I 7
		--un->un_openl;
E 7
		vp = un->un_lowervp;
	}
D 7
	
E 7
I 7

E 7
D 42
	return (VOP_CLOSE(vp, ap->a_fflag, ap->a_cred, ap->a_p));
E 42
I 42
	ap->a_vp = vp;
	return (VCALL(vp, VOFFSET(vop_close), ap));
E 42
E 6
}

E 2
/*
I 2
 * Check access permission on the union vnode.
 * The access check being enforced is to check
 * against both the underlying vnode, and any
 * copied vnode.  This ensures that no additional
 * file permissions are given away simply because
 * the user caused an implicit file copy.
 */
int
union_access(ap)
	struct vop_access_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_vp;
		int a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	struct union_node *un = VTOUNION(ap->a_vp);
I 39
	struct proc *p = ap->a_p;
E 39
I 3
D 16
	int error = 0;
E 16
I 16
	int error = EACCES;
E 16
E 3
	struct vnode *vp;

I 17
D 20
	if (vp = un->un_uppervp) {
E 20
I 20
	if ((vp = un->un_uppervp) != NULLVP) {
E 20
D 39
		FIXUP(un);
		return (VOP_ACCESS(vp, ap->a_mode, ap->a_cred, ap->a_p));
E 39
I 39
		FIXUP(un, p);
D 42
		return (VOP_ACCESS(vp, ap->a_mode, ap->a_cred, p));
E 42
I 42
		ap->a_vp = vp;
		return (VCALL(vp, VOFFSET(vop_access), ap));
E 42
E 39
	}

E 17
D 20
	if (vp = un->un_lowervp) {
E 20
I 20
	if ((vp = un->un_lowervp) != NULLVP) {
E 20
D 3
		int error;

E 3
I 3
D 39
		VOP_LOCK(vp);
E 3
		error = VOP_ACCESS(vp, ap->a_mode, ap->a_cred, ap->a_p);
E 39
I 39
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
D 42
		error = VOP_ACCESS(vp, ap->a_mode, ap->a_cred, p);
E 42
I 42
		ap->a_vp = vp;
		error = VCALL(vp, VOFFSET(vop_access), ap);
E 42
E 39
I 17
		if (error == 0) {
			struct union_mount *um = MOUNTTOUNIONMOUNT(vp->v_mount);

D 42
			if (um->um_op == UNMNT_BELOW)
				error = VOP_ACCESS(vp, ap->a_mode,
D 39
						um->um_cred, ap->a_p);
E 39
I 39
						um->um_cred, p);
E 42
I 42
			if (um->um_op == UNMNT_BELOW) {
				ap->a_cred = um->um_cred;
				error = VCALL(vp, VOFFSET(vop_access), ap);
			}
E 42
E 39
		}
E 17
I 3
D 39
		VOP_UNLOCK(vp);
E 39
I 39
		VOP_UNLOCK(vp, 0, p);
E 39
E 3
		if (error)
			return (error);
	}

D 3
	if (vp = un->un_uppervp)
		return (VOP_ACCESS(vp, ap->a_mode, ap->a_cred, ap->a_p));
	
	return (0);
E 3
I 3
D 10
	if (vp = un->un_uppervp) {
		VOP_LOCK(vp);
E 10
I 10
D 17
	if (vp = un->un_uppervp)
E 10
		error = VOP_ACCESS(vp, ap->a_mode, ap->a_cred, ap->a_p);
D 10
		VOP_UNLOCK(vp);
	}
E 10

E 17
	return (error);
E 3
}

/*
E 2
D 21
 *  We handle getattr only to change the fsid.
E 21
I 21
 * We handle getattr only to change the fsid and
 * track object sizes
E 21
 */
int
union_getattr(ap)
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	int error;
I 3
D 15
	struct vnode *vp = OTHERVP(ap->a_vp);
I 10
	int dolock = (vp == LOWERVP(ap->a_vp));
E 15
I 15
	struct union_node *un = VTOUNION(ap->a_vp);
	struct vnode *vp = un->un_uppervp;
I 39
	struct proc *p = ap->a_p;
E 39
	struct vattr *vap;
	struct vattr va;
E 15
E 10
E 3

D 3
	if (error = union_bypass(ap))
		return (error);
E 3
I 3
D 10
	VOP_LOCK(vp);
E 10
I 10
D 15
	if (dolock)
E 15
I 15

	/*
	 * Some programs walk the filesystem hierarchy by counting
	 * links to directories to avoid stat'ing all the time.
	 * This means the link count on directories needs to be "correct".
	 * The only way to do that is to call getattr on both layers
	 * and fix up the link count.  The link count will not necessarily
	 * be accurate but will be large enough to defeat the tree walkers.
	 */

	vap = ap->a_vap;

	vp = un->un_uppervp;
	if (vp != NULLVP) {
I 17
D 19
		FIXUP(un);
E 19
I 19
		/*
		 * It's not clear whether VOP_GETATTR is to be
		 * called with the vnode locked or not.  stat() calls
		 * it with (vp) locked, and fstat calls it with
		 * (vp) unlocked.
		 * In the mean time, compensate here by checking
		 * the union_node's lock flag.
		 */
		if (un->un_flags & UN_LOCKED)
D 39
			FIXUP(un);
E 39
I 39
			FIXUP(un, p);
E 39

E 19
E 17
		error = VOP_GETATTR(vp, vap, ap->a_cred, ap->a_p);
		if (error)
			return (error);
I 21
		union_newsize(ap->a_vp, vap->va_size, VNOVAL);
E 21
	}

	if (vp == NULLVP) {
		vp = un->un_lowervp;
	} else if (vp->v_type == VDIR) {
		vp = un->un_lowervp;
		vap = &va;
	} else {
		vp = NULLVP;
	}

	if (vp != NULLVP) {
E 15
D 34
		VOP_LOCK(vp);
E 34
E 10
D 15
	error = VOP_GETATTR(vp, ap->a_vap, ap->a_cred, ap->a_p);
D 10
	VOP_UNLOCK(vp);
E 10
I 10
	if (dolock)
E 15
I 15
		error = VOP_GETATTR(vp, vap, ap->a_cred, ap->a_p);
E 15
D 34
		VOP_UNLOCK(vp);
E 34
I 15
		if (error)
			return (error);
I 21
		union_newsize(ap->a_vp, VNOVAL, vap->va_size);
E 21
	}
E 15
E 10

E 3
D 15
	/* Requires that arguments be restored. */
	ap->a_vap->va_fsid = ap->a_vp->v_mount->mnt_stat.f_fsid.val[0];
E 15
I 15
	if ((vap != ap->a_vap) && (vap->va_type == VDIR))
		ap->a_vap->va_nlink += vap->va_nlink;

D 28
	vap->va_fsid = ap->a_vp->v_mount->mnt_stat.f_fsid.val[0];
E 28
I 28
	ap->a_vap->va_fsid = ap->a_vp->v_mount->mnt_stat.f_fsid.val[0];
E 28
E 15
	return (0);
}

I 2
int
D 3
lofs_setattr(ap)
E 3
I 3
union_setattr(ap)
E 3
	struct vop_setattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	struct union_node *un = VTOUNION(ap->a_vp);
I 39
	struct proc *p = ap->a_p;
E 39
	int error;

D 14
	if (un->un_uppervp) {
E 14
I 14
	/*
	 * Handle case of truncating lower object to zero size,
	 * by creating a zero length upper object.  This is to
	 * handle the case of open with O_TRUNC and O_CREAT.
	 */
	if ((un->un_uppervp == NULLVP) &&
	    /* assert(un->un_lowervp != NULLVP) */
D 31
	    (un->un_lowervp->v_type == VREG) &&
	    (ap->a_vap->va_size == 0)) {
		struct vnode *vp;

		error = union_vn_create(&vp, un, ap->a_p);
E 31
I 31
	    (un->un_lowervp->v_type == VREG)) {
		error = union_copyup(un, (ap->a_vap->va_size != 0),
						ap->a_cred, ap->a_p);
E 31
		if (error)
			return (error);
D 31

		/* at this point, uppervp is locked */
		union_newupper(un, vp);

		VOP_UNLOCK(vp);
		union_vn_close(un->un_uppervp, FWRITE, ap->a_cred, ap->a_p);
		VOP_LOCK(vp);
		un->un_flags |= UN_ULOCK;
E 31
	}

	/*
	 * Try to set attributes in upper layer,
	 * otherwise return read-only filesystem error.
	 */
	if (un->un_uppervp != NULLVP) {
I 17
D 39
		FIXUP(un);
E 39
I 39
		FIXUP(un, p);
E 39
E 17
E 14
D 10
		VOP_LOCK(un->un_uppervp);
E 10
		error = VOP_SETATTR(un->un_uppervp, ap->a_vap,
					ap->a_cred, ap->a_p);
I 21
		if ((error == 0) && (ap->a_vap->va_size != VNOVAL))
			union_newsize(ap->a_vp, ap->a_vap->va_size, VNOVAL);
E 21
D 10
		VOP_UNLOCK(un->un_uppervp);
E 10
	} else {
D 14
		/*
		 * XXX should do a copyfile (perhaps only if
		 * the file permission change, which would not
		 * track va_ctime correctly).
		 */
E 14
		error = EROFS;
	}

	return (error);
}

int
union_read(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	int error;
I 39
	struct proc *p = ap->a_uio->uio_procp;
E 39
	struct vnode *vp = OTHERVP(ap->a_vp);
I 10
	int dolock = (vp == LOWERVP(ap->a_vp));
E 10

D 3
	VOP_LOCKvp);
E 3
I 3
D 10
	VOP_LOCK(vp);
E 10
I 10
	if (dolock)
D 39
		VOP_LOCK(vp);
E 39
I 39
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
I 17
	else
D 39
		FIXUP(VTOUNION(ap->a_vp));
E 39
I 39
		FIXUP(VTOUNION(ap->a_vp), p);
E 39
E 17
E 10
E 3
	error = VOP_READ(vp, ap->a_uio, ap->a_ioflag, ap->a_cred);
D 3
	VOP_UNLOCKvp);
E 3
I 3
D 10
	VOP_UNLOCK(vp);
E 10
I 10
	if (dolock)
D 39
		VOP_UNLOCK(vp);
E 39
I 39
		VOP_UNLOCK(vp, 0, p);
E 39
E 10
E 3

I 21
	/*
	 * XXX
	 * perhaps the size of the underlying object has changed under
	 * our feet.  take advantage of the offset information present
	 * in the uio structure.
	 */
	if (error == 0) {
		struct union_node *un = VTOUNION(ap->a_vp);
		off_t cur = ap->a_uio->uio_offset;

		if (vp == un->un_uppervp) {
			if (cur > un->un_uppersz)
				union_newsize(ap->a_vp, cur, VNOVAL);
		} else {
			if (cur > un->un_lowersz)
				union_newsize(ap->a_vp, VNOVAL, cur);
		}
	}

E 21
	return (error);
}

int
union_write(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	int error;
D 31
	struct vnode *vp = OTHERVP(ap->a_vp);
I 10
	int dolock = (vp == LOWERVP(ap->a_vp));
E 31
I 31
	struct vnode *vp;
	struct union_node *un = VTOUNION(ap->a_vp);
I 39
	struct proc *p = ap->a_uio->uio_procp;
E 39
E 31
E 10

D 10
	VOP_LOCK(vp);
E 10
I 10
D 31
	if (dolock)
		VOP_LOCK(vp);
I 17
	else
		FIXUP(VTOUNION(ap->a_vp));
E 31
I 31
	vp = UPPERVP(ap->a_vp);
	if (vp == NULLVP)
		panic("union: missing upper layer in write");

D 39
	FIXUP(un);
E 39
I 39
	FIXUP(un, p);
E 39
E 31
E 17
E 10
	error = VOP_WRITE(vp, ap->a_uio, ap->a_ioflag, ap->a_cred);
D 10
	VOP_UNLOCK(vp);
E 10
I 10
D 31
	if (dolock)
		VOP_UNLOCK(vp);
E 31
I 21

	/*
	 * the size of the underlying object may be changed by the
	 * write.
	 */
	if (error == 0) {
D 31
		struct union_node *un = VTOUNION(ap->a_vp);
E 31
		off_t cur = ap->a_uio->uio_offset;

D 31
		if (vp == un->un_uppervp) {
			if (cur > un->un_uppersz)
				union_newsize(ap->a_vp, cur, VNOVAL);
		} else {
			if (cur > un->un_lowersz)
				union_newsize(ap->a_vp, VNOVAL, cur);
		}
E 31
I 31
		if (cur > un->un_uppersz)
			union_newsize(ap->a_vp, cur, VNOVAL);
E 31
	}
E 21
E 10

	return (error);
}

I 32
union_lease(ap)
	struct vop_lease_args /* {
		struct vnode *a_vp;
		struct proc *a_p;
		struct ucred *a_cred;
		int a_flag;
	} */ *ap;
{
I 42
	register struct vnode *ovp = OTHERVP(ap->a_vp);
E 42

D 42
	return (VOP_LEASE(OTHERVP(ap->a_vp), ap->a_p, ap->a_cred, ap->a_flag));
E 42
I 42
	ap->a_vp = ovp;
	return (VCALL(ovp, VOFFSET(vop_lease), ap));
E 42
}

E 32
int
union_ioctl(ap)
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
		int  a_command;
		caddr_t  a_data;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
I 42
	register struct vnode *ovp = OTHERVP(ap->a_vp);
E 42

D 42
	return (VOP_IOCTL(OTHERVP(ap->a_vp), ap->a_command, ap->a_data,
				ap->a_fflag, ap->a_cred, ap->a_p));
E 42
I 42
	ap->a_vp = ovp;
	return (VCALL(ovp, VOFFSET(vop_ioctl), ap));
E 42
}

int
union_select(ap)
	struct vop_select_args /* {
		struct vnode *a_vp;
		int  a_which;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
I 42
	register struct vnode *ovp = OTHERVP(ap->a_vp);
E 42

D 42
	return (VOP_SELECT(OTHERVP(ap->a_vp), ap->a_which, ap->a_fflags,
				ap->a_cred, ap->a_p));
E 42
I 42
	ap->a_vp = ovp;
	return (VCALL(ovp, VOFFSET(vop_select), ap));
E 42
}

int
I 38
union_revoke(ap)
	struct vop_revoke_args /* {
		struct vnode *a_vp;
		int a_flags;
I 39
		struct proc *a_p;
E 39
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;

	if (UPPERVP(vp))
		VOP_REVOKE(UPPERVP(vp), ap->a_flags);
	if (LOWERVP(vp))
D 39
		VOP_REVOKE(UPPERVP(vp), ap->a_flags);
E 39
I 39
		VOP_REVOKE(LOWERVP(vp), ap->a_flags);
E 39
	vgone(vp);
}

int
E 38
union_mmap(ap)
	struct vop_mmap_args /* {
		struct vnode *a_vp;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
I 42
	register struct vnode *ovp = OTHERVP(ap->a_vp);
E 42

D 42
	return (VOP_MMAP(OTHERVP(ap->a_vp), ap->a_fflags,
				ap->a_cred, ap->a_p));
E 42
I 42
	ap->a_vp = ovp;
	return (VCALL(ovp, VOFFSET(vop_mmap), ap));
E 42
}

int
union_fsync(ap)
	struct vop_fsync_args /* {
		struct vnode *a_vp;
		struct ucred *a_cred;
		int  a_waitfor;
		struct proc *a_p;
	} */ *ap;
{
	int error = 0;
I 39
	struct proc *p = ap->a_p;
E 39
	struct vnode *targetvp = OTHERVP(ap->a_vp);

D 20
	if (targetvp) {
E 20
I 20
	if (targetvp != NULLVP) {
E 20
D 10
		VOP_LOCK(targetvp);
E 10
I 10
		int dolock = (targetvp == LOWERVP(ap->a_vp));

		if (dolock)
D 39
			VOP_LOCK(targetvp);
E 39
I 39
			vn_lock(targetvp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
I 17
		else
D 39
			FIXUP(VTOUNION(ap->a_vp));
E 17
E 10
		error = VOP_FSYNC(targetvp, ap->a_cred,
					ap->a_waitfor, ap->a_p);
E 39
I 39
			FIXUP(VTOUNION(ap->a_vp), p);
		error = VOP_FSYNC(targetvp, ap->a_cred, ap->a_waitfor, p);
E 39
D 10
		VOP_UNLOCK(targetvp);
E 10
I 10
		if (dolock)
D 39
			VOP_UNLOCK(targetvp);
E 39
I 39
			VOP_UNLOCK(targetvp, 0, p);
E 39
E 10
	}

	return (error);
}

int
union_seek(ap)
	struct vop_seek_args /* {
		struct vnode *a_vp;
		off_t  a_oldoff;
		off_t  a_newoff;
		struct ucred *a_cred;
	} */ *ap;
{
I 42
	register struct vnode *ovp = OTHERVP(ap->a_vp);
E 42

D 42
	return (VOP_SEEK(OTHERVP(ap->a_vp), ap->a_oldoff, ap->a_newoff, ap->a_cred));
E 42
I 42
	ap->a_vp = ovp;
	return (VCALL(ovp, VOFFSET(vop_seek), ap));
E 42
}

int
union_remove(ap)
	struct vop_remove_args /* {
		struct vnode *a_dvp;
		struct vnode *a_vp;
		struct componentname *a_cnp;
	} */ *ap;
{
	int error;
	struct union_node *dun = VTOUNION(ap->a_dvp);
	struct union_node *un = VTOUNION(ap->a_vp);
I 39
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
E 39

D 20
	if (dun->un_uppervp && un->un_uppervp) {
E 20
I 20
D 31
	if (dun->un_uppervp != NULLVP && un->un_uppervp != NULLVP) {
E 31
I 31
	if (dun->un_uppervp == NULLVP)
		panic("union remove: null upper vnode");

	if (un->un_uppervp != NULLVP) {
E 31
E 20
		struct vnode *dvp = dun->un_uppervp;
		struct vnode *vp = un->un_uppervp;
I 33
D 39
		struct componentname *cnp = ap->a_cnp;
E 39
E 33

I 17
D 39
		FIXUP(dun);
E 39
I 39
		FIXUP(dun, p);
E 39
E 17
		VREF(dvp);
D 10
		VOP_LOCK(dvp);
E 10
I 10
		dun->un_flags |= UN_KLOCK;
E 10
		vput(ap->a_dvp);
I 17
D 39
		FIXUP(un);
E 39
I 39
		FIXUP(un, p);
E 39
E 17
		VREF(vp);
D 10
		VOP_LOCK(vp);
E 10
I 10
		un->un_flags |= UN_KLOCK;
E 10
		vput(ap->a_vp);

I 31
D 33
		if (un->un_lowervp != NULLVP)
			ap->a_cnp->cn_flags |= DOWHITEOUT;
E 31
		error = VOP_REMOVE(dvp, vp, ap->a_cnp);
E 33
I 33
		if (union_dowhiteout(un, cnp->cn_cred, cnp->cn_proc))
			cnp->cn_flags |= DOWHITEOUT;
		error = VOP_REMOVE(dvp, vp, cnp);
E 33
I 7
		if (!error)
			union_removed_upper(un);
D 31

		/*
		 * XXX: should create a whiteout here
		 */
E 31
E 7
	} else {
D 31
		/*
		 * XXX: should create a whiteout here
		 */
E 31
I 31
D 39
		FIXUP(dun);
E 39
I 39
		FIXUP(dun, p);
E 39
		error = union_mkwhiteout(
			MOUNTTOUNIONMOUNT(UNIONTOV(dun)->v_mount),
			dun->un_uppervp, ap->a_cnp, un->un_path);
E 31
		vput(ap->a_dvp);
		vput(ap->a_vp);
D 31
		error = EROFS;
E 31
	}

	return (error);
}

int
union_link(ap)
	struct vop_link_args /* {
		struct vnode *a_vp;
		struct vnode *a_tdvp;
		struct componentname *a_cnp;
	} */ *ap;
{
D 24
	int error;
	struct union_node *dun = VTOUNION(ap->a_vp);
	struct union_node *un = VTOUNION(ap->a_tdvp);
E 24
I 24
	int error = 0;
I 39
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
E 39
	struct union_node *un;
	struct vnode *vp;
	struct vnode *tdvp;
E 24

D 20
	if (dun->un_uppervp && un->un_uppervp) {
E 20
I 20
D 24
	if (dun->un_uppervp != NULLVP && un->un_uppervp != NULLVP) {
E 20
		struct vnode *dvp = dun->un_uppervp;
		struct vnode *vp = un->un_uppervp;
E 24
I 24
D 36
	un = VTOUNION(ap->a_vp);
E 36
I 36
	un = VTOUNION(ap->a_tdvp);
E 36
E 24

I 17
D 24
		FIXUP(dun);
E 17
		VREF(dvp);
D 10
		VOP_LOCK(dvp);
E 10
I 10
		dun->un_flags |= UN_KLOCK;
E 10
		vput(ap->a_vp);
I 17
D 22
		FIXUP(un);
E 17
		VREF(vp);
		vrele(ap->a_tdvp);
E 22

		error = VOP_LINK(dvp, vp, ap->a_cnp);
E 24
I 24
D 36
	if (ap->a_vp->v_op != ap->a_tdvp->v_op) {
		tdvp = ap->a_tdvp;
E 36
I 36
	if (ap->a_tdvp->v_op != ap->a_vp->v_op) {
		vp = ap->a_vp;
E 36
E 24
	} else {
D 24
		/*
D 20
		 * XXX: need to copy to upper layer
E 20
I 20
		 * XXX: perhaps could copy to upper layer
E 20
		 * and do the link there.
		 */
		vput(ap->a_vp);
E 24
I 24
D 36
		struct union_node *tdun = VTOUNION(ap->a_tdvp);
		if (tdun->un_uppervp == NULLVP) {
			VOP_LOCK(ap->a_tdvp);
			if (un->un_uppervp == tdun->un_dirvp) {
E 36
I 36
		struct union_node *tun = VTOUNION(ap->a_vp);
		if (tun->un_uppervp == NULLVP) {
D 39
			VOP_LOCK(ap->a_vp);
E 39
I 39
			vn_lock(ap->a_vp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
			if (un->un_uppervp == tun->un_dirvp) {
E 36
				un->un_flags &= ~UN_ULOCK;
D 39
				VOP_UNLOCK(un->un_uppervp);
E 39
I 39
				VOP_UNLOCK(un->un_uppervp, 0, p);
E 39
			}
D 36
			error = union_copyup(tdun, 1, ap->a_cnp->cn_cred,
E 36
I 36
D 39
			error = union_copyup(tun, 1, ap->a_cnp->cn_cred,
E 36
						ap->a_cnp->cn_proc);
E 39
I 39
			error = union_copyup(tun, 1, cnp->cn_cred, p);
E 39
D 36
			if (un->un_uppervp == tdun->un_dirvp) {
E 36
I 36
			if (un->un_uppervp == tun->un_dirvp) {
E 36
D 39
				VOP_LOCK(un->un_uppervp);
E 39
I 39
				vn_lock(un->un_uppervp,
						LK_EXCLUSIVE | LK_RETRY, p);
E 39
				un->un_flags |= UN_ULOCK;
			}
D 36
			VOP_UNLOCK(ap->a_tdvp);
E 36
I 36
D 39
			VOP_UNLOCK(ap->a_vp);
E 39
I 39
			VOP_UNLOCK(ap->a_vp, 0, p);
E 39
E 36
		}
D 36
		tdvp = tdun->un_uppervp;
E 36
I 36
		vp = tun->un_uppervp;
E 36
	}

D 36
	vp = un->un_uppervp;
	if (vp == NULLVP)
E 36
I 36
	tdvp = un->un_uppervp;
	if (tdvp == NULLVP)
E 36
E 24
D 23
		vrele(ap->a_tdvp);
E 23
		error = EROFS;
I 24

	if (error) {
D 36
		vput(ap->a_vp);
E 36
I 36
		vput(ap->a_tdvp);
E 36
		return (error);
E 24
	}

D 24
	return (error);
E 24
I 24
D 39
	FIXUP(un);
E 39
I 39
	FIXUP(un, p);
E 39
D 36
	VREF(vp);
E 36
I 36
	VREF(tdvp);
E 36
	un->un_flags |= UN_KLOCK;
D 36
	vput(ap->a_vp);
E 36
I 36
	vput(ap->a_tdvp);
E 36

D 39
	return (VOP_LINK(vp, tdvp, ap->a_cnp));
E 39
I 39
	return (VOP_LINK(vp, tdvp, cnp));
E 39
E 24
}

int
union_rename(ap)
	struct vop_rename_args  /* {
		struct vnode *a_fdvp;
		struct vnode *a_fvp;
		struct componentname *a_fcnp;
		struct vnode *a_tdvp;
		struct vnode *a_tvp;
		struct componentname *a_tcnp;
	} */ *ap;
{
	int error;

	struct vnode *fdvp = ap->a_fdvp;
	struct vnode *fvp = ap->a_fvp;
	struct vnode *tdvp = ap->a_tdvp;
	struct vnode *tvp = ap->a_tvp;

	if (fdvp->v_op == union_vnodeop_p) {	/* always true */
		struct union_node *un = VTOUNION(fdvp);
D 6
		if (un->un_uppervp == 0) {
E 6
I 6
		if (un->un_uppervp == NULLVP) {
E 6
D 31
			error = EROFS;
E 31
I 31
			/*
			 * this should never happen in normal
			 * operation but might if there was
			 * a problem creating the top-level shadow
			 * directory.
			 */
			error = EXDEV;
E 31
			goto bad;
		}

I 17
D 20
		FIXUP(un);
E 20
E 17
		fdvp = un->un_uppervp;
		VREF(fdvp);
		vrele(ap->a_fdvp);
	}

	if (fvp->v_op == union_vnodeop_p) {	/* always true */
		struct union_node *un = VTOUNION(fvp);
D 6
		if (un->un_uppervp == 0) {
E 6
I 6
		if (un->un_uppervp == NULLVP) {
E 6
D 31
			error = EROFS;
E 31
I 31
			/* XXX: should do a copyup */
			error = EXDEV;
E 31
			goto bad;
		}

I 31
		if (un->un_lowervp != NULLVP)
			ap->a_fcnp->cn_flags |= DOWHITEOUT;

E 31
I 17
D 20
		FIXUP(un);
E 20
E 17
		fvp = un->un_uppervp;
		VREF(fvp);
		vrele(ap->a_fvp);
	}

	if (tdvp->v_op == union_vnodeop_p) {
		struct union_node *un = VTOUNION(tdvp);
D 6
		if (un->un_uppervp == 0) {
E 6
I 6
		if (un->un_uppervp == NULLVP) {
I 20
			/*
			 * this should never happen in normal
			 * operation but might if there was
			 * a problem creating the top-level shadow
			 * directory.
			 */
E 20
E 6
D 31
			error = EROFS;
E 31
I 31
			error = EXDEV;
E 31
			goto bad;
		}

		tdvp = un->un_uppervp;
		VREF(tdvp);
D 10
		VOP_LOCK(tdvp);
E 10
I 10
		un->un_flags |= UN_KLOCK;
E 10
D 6
		vput(ap->a_fdvp);
E 6
I 6
		vput(ap->a_tdvp);
E 6
	}

D 20
	if (tvp && tvp->v_op == union_vnodeop_p) {
E 20
I 20
	if (tvp != NULLVP && tvp->v_op == union_vnodeop_p) {
E 20
		struct union_node *un = VTOUNION(tvp);
D 6
		if (un->un_uppervp == 0) {
E 6
I 6
D 20
		if (un->un_uppervp == NULLVP) {
E 6
			error = EROFS;
			goto bad;
		}
E 20

		tvp = un->un_uppervp;
D 20
		VREF(tvp);
D 10
		VOP_LOCK(tvp);
E 10
I 10
		un->un_flags |= UN_KLOCK;
E 20
I 20
		if (tvp != NULLVP) {
			VREF(tvp);
			un->un_flags |= UN_KLOCK;
		}
E 20
E 10
		vput(ap->a_tvp);
	}

	return (VOP_RENAME(fdvp, fvp, ap->a_fcnp, tdvp, tvp, ap->a_tcnp));

bad:
	vrele(fdvp);
	vrele(fvp);
	vput(tdvp);
D 20
	if (tvp)
E 20
I 20
	if (tvp != NULLVP)
E 20
		vput(tvp);

	return (error);
}

int
union_mkdir(ap)
	struct vop_mkdir_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
{
	struct union_node *un = VTOUNION(ap->a_dvp);
	struct vnode *dvp = un->un_uppervp;
I 39
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
E 39

D 20
	if (dvp) {
E 20
I 20
	if (dvp != NULLVP) {
E 20
		int error;
		struct vnode *vp;
D 4
		struct mount *mp = ap->a_dvp->v_mount;
E 4

I 17
D 39
		FIXUP(un);
E 39
I 39
		FIXUP(un, p);
E 39
E 17
		VREF(dvp);
D 10
		VOP_LOCK(dvp);
E 10
I 10
		un->un_flags |= UN_KLOCK;
E 10
D 34
		vput(ap->a_dvp);
E 34
I 34
D 39
		VOP_UNLOCK(ap->a_dvp);
E 34
		error = VOP_MKDIR(dvp, &vp, ap->a_cnp, ap->a_vap);
E 39
I 39
		VOP_UNLOCK(ap->a_dvp, 0, p);
		error = VOP_MKDIR(dvp, &vp, cnp, ap->a_vap);
E 39
D 34
		if (error)
E 34
I 34
		if (error) {
			vrele(ap->a_dvp);
E 34
			return (error);
I 34
		}
E 34

I 6
D 10
		VOP_UNLOCK(vp);
E 10
E 6
D 39
		error = union_allocvp(
				ap->a_vpp,
D 4
				mp,
E 4
I 4
				ap->a_dvp->v_mount,
				ap->a_dvp,
E 4
D 3
				un->un_uppervp,
E 3
I 3
				NULLVP,
E 3
				ap->a_cnp,
				vp,
D 34
				NULLVP);
E 34
I 34
				NULLVP,
				1);
E 39
I 39
		error = union_allocvp(ap->a_vpp, ap->a_dvp->v_mount, ap->a_dvp,
				NULLVP, cnp, vp, NULLVP, 1);
E 39
		vrele(ap->a_dvp);
E 34
I 3
D 6
		VOP_UNLOCK(vp);
E 6
		if (error)
D 10
			vrele(vp);
E 10
I 10
			vput(vp);
E 10
E 3
		return (error);
	}

	vput(ap->a_dvp);
	return (EROFS);
}

int
union_rmdir(ap)
	struct vop_rmdir_args /* {
		struct vnode *a_dvp;
		struct vnode *a_vp;
		struct componentname *a_cnp;
	} */ *ap;
{
	int error;
	struct union_node *dun = VTOUNION(ap->a_dvp);
	struct union_node *un = VTOUNION(ap->a_vp);
I 39
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
E 39

D 20
	if (dun->un_uppervp && un->un_uppervp) {
E 20
I 20
D 31
	if (dun->un_uppervp != NULLVP && un->un_uppervp != NULLVP) {
E 31
I 31
	if (dun->un_uppervp == NULLVP)
		panic("union rmdir: null upper vnode");

	if (un->un_uppervp != NULLVP) {
E 31
E 20
		struct vnode *dvp = dun->un_uppervp;
		struct vnode *vp = un->un_uppervp;
I 33
D 39
		struct componentname *cnp = ap->a_cnp;
E 39
E 33

I 17
D 39
		FIXUP(dun);
E 39
I 39
		FIXUP(dun, p);
E 39
E 17
		VREF(dvp);
D 10
		VOP_LOCK(dvp);
E 10
I 10
		dun->un_flags |= UN_KLOCK;
E 10
		vput(ap->a_dvp);
I 17
D 39
		FIXUP(un);
E 39
I 39
		FIXUP(un, p);
E 39
E 17
		VREF(vp);
D 10
		VOP_LOCK(vp);
E 10
I 10
		un->un_flags |= UN_KLOCK;
E 10
		vput(ap->a_vp);

I 31
D 33
		if (un->un_lowervp != NULLVP)
			ap->a_cnp->cn_flags |= DOWHITEOUT;
E 33
I 33
		if (union_dowhiteout(un, cnp->cn_cred, cnp->cn_proc))
			cnp->cn_flags |= DOWHITEOUT;
E 33
E 31
D 10
		error = VOP_REMOVE(dvp, vp, ap->a_cnp);
E 10
I 10
		error = VOP_RMDIR(dvp, vp, ap->a_cnp);
E 10
I 7
		if (!error)
			union_removed_upper(un);
D 31

		/*
		 * XXX: should create a whiteout here
		 */
E 31
E 7
	} else {
D 31
		/*
		 * XXX: should create a whiteout here
		 */
E 31
I 31
D 39
		FIXUP(dun);
E 39
I 39
		FIXUP(dun, p);
E 39
		error = union_mkwhiteout(
			MOUNTTOUNIONMOUNT(UNIONTOV(dun)->v_mount),
			dun->un_uppervp, ap->a_cnp, un->un_path);
E 31
		vput(ap->a_dvp);
		vput(ap->a_vp);
D 31
		error = EROFS;
E 31
	}

	return (error);
}

int
union_symlink(ap)
	struct vop_symlink_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
		char *a_target;
	} */ *ap;
{
	struct union_node *un = VTOUNION(ap->a_dvp);
	struct vnode *dvp = un->un_uppervp;
I 39
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
E 39

D 20
	if (dvp) {
E 20
I 20
	if (dvp != NULLVP) {
E 20
		int error;
		struct vnode *vp;
		struct mount *mp = ap->a_dvp->v_mount;

I 17
D 39
		FIXUP(un);
E 39
I 39
		FIXUP(un, p);
E 39
E 17
		VREF(dvp);
D 10
		VOP_LOCK(dvp);
E 10
I 10
		un->un_flags |= UN_KLOCK;
E 10
		vput(ap->a_dvp);
D 39
		error = VOP_SYMLINK(dvp, &vp, ap->a_cnp,
					ap->a_vap, ap->a_target);
E 39
I 39
		error = VOP_SYMLINK(dvp, &vp, cnp, ap->a_vap, ap->a_target);
E 39
D 3
		if (error)
			return (error);

		error = union_allocvp(
				ap->a_vpp,
				mp,
				un->un_uppervp,
				ap->a_cnp,
				vp,
				NULLVP);
		vput(*ap->a_vpp);
E 3
I 3
D 6
		*ap->a_vpp = 0;
E 6
I 6
		*ap->a_vpp = NULLVP;
E 6
E 3
		return (error);
	}

	vput(ap->a_dvp);
	return (EROFS);
}

E 2
/*
 * union_readdir works in concert with getdirentries and
 * readdir(3) to provide a list of entries in the unioned
 * directories.  getdirentries is responsible for walking
 * down the union stack.  readdir(3) is responsible for
 * eliminating duplicate names from the returned data stream.
 */
int
union_readdir(ap)
	struct vop_readdir_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
I 27
		int *a_eofflag;
		u_long *a_cookies;
		int a_ncookies;
E 27
	} */ *ap;
{
I 2
D 27
	int error = 0;
E 2
	struct union_node *un = VTOUNION(ap->a_vp);
E 27
I 27
D 39
	register struct union_node *un = VTOUNION(ap->a_vp);
	register struct vnode *uvp = un->un_uppervp;
E 39
I 39
	struct union_node *un = VTOUNION(ap->a_vp);
	struct vnode *uvp = un->un_uppervp;
	struct proc *p = ap->a_uio->uio_procp;
E 39
E 27

D 2
	if (un->un_uppervp)
		return (union_bypass(ap));
E 2
I 2
D 10
	if (un->un_uppervp) {
D 8
		struct vnode *vp = OTHERVP(ap->a_vp);
E 8
I 8
		struct vnode *vp = un->un_uppervp;
E 10
I 10
D 17
	if (un->un_uppervp)
E 17
I 17
D 20
	if (un->un_uppervp) {
E 20
I 20
D 27
	if (un->un_uppervp != NULLVP) {
E 20
		FIXUP(un);
E 17
		error = VOP_READDIR(un->un_uppervp, ap->a_uio, ap->a_cred);
I 17
	}
E 27
I 27
	if (uvp == NULLVP)
		return (0);
E 27
E 17
E 10
E 8
E 2

D 2
	return (0);
E 2
I 2
D 10
		VOP_LOCK(vp);
		error = VOP_READLINK(vp, ap->a_uio, ap->a_cred);
		VOP_UNLOCK(vp);
	}

E 10
D 27
	return (error);
E 27
I 27
D 39
	FIXUP(un);
E 39
I 39
	FIXUP(un, p);
E 39
	ap->a_vp = uvp;
D 42
	return (VOCALL(uvp->v_op, VOFFSET(vop_readdir), ap));
E 42
I 42
	return (VCALL(uvp, VOFFSET(vop_readdir), ap));
E 42
E 27
E 2
}

int
I 2
union_readlink(ap)
	struct vop_readlink_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
	} */ *ap;
{
	int error;
I 39
	struct uio *uio = ap->a_uio;
	struct proc *p = uio->uio_procp;
E 39
	struct vnode *vp = OTHERVP(ap->a_vp);
I 10
	int dolock = (vp == LOWERVP(ap->a_vp));
E 10

D 10
	VOP_LOCK(vp);
E 10
I 10
	if (dolock)
D 39
		VOP_LOCK(vp);
E 39
I 39
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
I 17
	else
D 39
		FIXUP(VTOUNION(ap->a_vp));
E 17
E 10
	error = VOP_READLINK(vp, ap->a_uio, ap->a_cred);
E 39
I 39
		FIXUP(VTOUNION(ap->a_vp), p);
D 42
	error = VOP_READLINK(vp, uio, ap->a_cred);
E 42
I 42
	ap->a_vp = vp;
	error = VCALL(vp, VOFFSET(vop_readlink), ap);
E 42
E 39
D 10
	VOP_UNLOCK(vp);
E 10
I 10
	if (dolock)
D 39
		VOP_UNLOCK(vp);
E 39
I 39
		VOP_UNLOCK(vp, 0, p);
E 39
E 10

	return (error);
}

int
union_abortop(ap)
	struct vop_abortop_args /* {
		struct vnode *a_dvp;
		struct componentname *a_cnp;
	} */ *ap;
{
	int error;
I 39
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
E 39
D 3
	struct vnode *vp = OTHERVP(a->a_dvp);
E 3
I 3
	struct vnode *vp = OTHERVP(ap->a_dvp);
E 3
	struct union_node *un = VTOUNION(ap->a_dvp);
	int islocked = un->un_flags & UN_LOCKED;
I 10
	int dolock = (vp == LOWERVP(ap->a_dvp));
E 10

D 10
	if (islocked)
E 10
I 10
D 17
	if (islocked && dolock)
E 10
		VOP_LOCK(vp);
E 17
I 17
	if (islocked) {
		if (dolock)
D 39
			VOP_LOCK(vp);
E 39
I 39
			vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
		else
D 39
			FIXUP(VTOUNION(ap->a_dvp));
E 39
I 39
			FIXUP(VTOUNION(ap->a_dvp), p);
E 39
	}
E 17
D 39
	error = VOP_ABORTOP(vp, ap->a_cnp);
E 39
I 39
D 42
	error = VOP_ABORTOP(vp, cnp);
E 42
I 42
	ap->a_dvp = vp;
	error = VCALL(vp, VOFFSET(vop_abortop), ap);
E 42
E 39
D 10
	if (islocked)
E 10
I 10
	if (islocked && dolock)
E 10
D 39
		VOP_UNLOCK(vp);
E 39
I 39
		VOP_UNLOCK(vp, 0, p);
E 39

	return (error);
}

int
E 2
union_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 39
		struct proc *a_p;
E 39
	} */ *ap;
{
I 19
D 41
	struct union_node *un = VTOUNION(ap->a_vp);
E 41
I 41
	struct vnode *vp = ap->a_vp;
	struct proc *p = ap->a_p;
	struct union_node *un = VTOUNION(vp);
E 41
I 34
	struct vnode **vpp;
E 34
E 19

	/*
	 * Do nothing (and _don't_ bypass).
	 * Wait to vrele lowervp until reclaim,
	 * so that until then our union_node is in the
	 * cache and reusable.
	 *
	 * NEEDSWORK: Someday, consider inactive'ing
	 * the lowervp and then trying to reactivate it
	 * with capabilities (v_id)
	 * like they do in the name lookup cache code.
	 * That's too much work for now.
	 */
I 4

D 7
#ifdef DIAGNOSTIC
E 7
I 7
D 41
#ifdef UNION_DIAGNOSTIC
E 7
D 19
	struct union_node *un = VTOUNION(ap->a_vp);

E 19
	if (un->un_flags & UN_LOCKED)
		panic("union: inactivating locked node");
I 19
	if (un->un_flags & UN_ULOCK)
		panic("union: inactivating w/locked upper node");
E 19
#endif
I 34

E 41
	if (un->un_dircache != 0) {
		for (vpp = un->un_dircache; *vpp != NULLVP; vpp++)
			vrele(*vpp);
		free(un->un_dircache, M_TEMP);
		un->un_dircache = 0;
	}
E 34
I 19

I 41
	VOP_UNLOCK(vp, 0, p);

E 41
	if ((un->un_flags & UN_CACHED) == 0)
D 35
		vgone(ap->a_vp);
E 35
I 35
D 38
		VOP_REVOKE(ap->a_vp, 0);
E 38
I 38
D 41
		vgone(ap->a_vp);
E 41
I 41
		vgone(vp);
E 41
E 38
E 35
E 19

E 4
	return (0);
}

int
union_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
{
D 11
	struct vnode *vp = ap->a_vp;
	struct union_node *un = VTOUNION(vp);
	struct vnode *uppervp = un->un_uppervp;
	struct vnode *lowervp = un->un_lowervp;
	struct vnode *dirvp = un->un_dirvp;
	char *path = un->un_path;
E 11

D 11
	/*
	 * Note: in vop_reclaim, vp->v_op == dead_vnodeop_p,
	 * so we can't call VOPs on ourself.
	 */
	/* After this assignment, this node will not be re-used. */
D 6
	un->un_uppervp = 0;
	un->un_lowervp = 0;
	un->un_dirvp = 0;
E 6
I 6
	un->un_uppervp = NULLVP;
	un->un_lowervp = NULLVP;
	un->un_dirvp = NULLVP;
E 6
	un->un_path = NULL;
	union_freevp(vp);
	if (uppervp)
		vrele(uppervp);
	if (lowervp)
		vrele(lowervp);
	if (dirvp)
		vrele(dirvp);
	if (path)
		free(path, M_TEMP);
E 11
I 11
	union_freevp(ap->a_vp);

E 11
	return (0);
}

I 2
int
union_lock(ap)
	struct vop_lock_args *ap;
{
D 16
	struct union_node *un = VTOUNION(ap->a_vp);
E 16
I 16
	struct vnode *vp = ap->a_vp;
I 39
	struct proc *p = ap->a_p;
	int flags = ap->a_flags;
E 39
	struct union_node *un;
I 41
	int error;
E 41
E 16
E 2

I 16
D 43
start:
E 43
D 39
	while (vp->v_flag & VXLOCK) {
E 39
I 39
D 41
	if ((flags & LK_INTERLOCK) == 0)
		simple_lock(&vp->v_interlock);
	if (vp->v_flag & VXLOCK) {
E 39
		vp->v_flag |= VXWANT;
E 41
I 41

D 43
	if (flags & LK_INTERLOCK) {
E 41
D 39
		sleep((caddr_t)vp, PINOD);
E 39
I 39
		simple_unlock(&vp->v_interlock);
D 41
		tsleep((caddr_t)vp, PINOD, "unionlk1", 0);
		return (ENOENT);
E 41
I 41
		flags &= ~LK_INTERLOCK;
E 41
E 39
	}
E 43
I 43
	vop_nolock(ap);
I 44
	/*
	 * Need to do real lockmgr-style locking here.
	 * in the mean time, draining won't work quite right,
	 * which could lead to a few race conditions.
	 * the following test was here, but is not quite right, we
	 * still need to take the lock:
E 44
	if ((flags & LK_TYPE_MASK) == LK_DRAIN)
		return (0);
I 44
	 */
E 44
	flags &= ~LK_INTERLOCK;
E 43
I 39
D 41
	simple_unlock(&vp->v_interlock);
	flags &= ~LK_INTERLOCK;
E 41
E 39

I 43
start:
E 43
	un = VTOUNION(vp);

E 16
I 10
D 20
	if (un->un_uppervp) {
E 20
I 20
	if (un->un_uppervp != NULLVP) {
E 20
D 25
		if ((un->un_flags & UN_ULOCK) == 0) {
E 25
I 25
		if (((un->un_flags & UN_ULOCK) == 0) &&
		    (vp->v_usecount != 0)) {
E 25
D 16
			VOP_LOCK(un->un_uppervp);
E 16
D 37
			un->un_flags |= UN_ULOCK;
E 37
I 16
D 39
			VOP_LOCK(un->un_uppervp);
E 39
I 39
D 41
			if (vn_lock(un->un_uppervp, flags, p))
				goto start;
E 41
I 41
			error = vn_lock(un->un_uppervp, flags, p);
			if (error)
				return (error);
E 41
E 39
I 37
			un->un_flags |= UN_ULOCK;
E 37
E 16
		}
#ifdef DIAGNOSTIC
D 38
		if (un->un_flags & UN_KLOCK)
E 38
I 38
		if (un->un_flags & UN_KLOCK) {
E 38
D 37
			panic("union: dangling upper lock");
E 37
I 37
			vprint("union: dangling klock", vp);
			panic("union: dangling upper lock (%lx)", vp);
I 38
		}
E 38
E 37
#endif
	}

E 10
I 3
D 16
	while (un->un_flags & UN_LOCKED) {
E 16
I 16
	if (un->un_flags & UN_LOCKED) {
E 16
E 3
I 2
#ifdef DIAGNOSTIC
D 3
	if (un->un_pid == curproc->p_pid)
		panic("union: locking agsinst myself");
E 3
I 3
D 4
		if (un->un_pid == curproc->p_pid)
			panic("union: locking agsinst myself");
E 4
I 4
		if (curproc && un->un_pid == curproc->p_pid &&
			    un->un_pid > -1 && curproc->p_pid > -1)
			panic("union: locking against myself");
E 4
E 3
#endif
D 3
	while (un->un_flags & UN_LOCKED) {
E 3
		un->un_flags |= UN_WANT;
D 39
		sleep((caddr_t) &un->un_flags, PINOD);
E 39
I 39
		tsleep((caddr_t)&un->un_flags, PINOD, "unionlk2", 0);
E 39
I 16
		goto start;
E 16
	}
D 16
	un->un_flags |= UN_LOCKED;
E 16
I 4

E 4
#ifdef DIAGNOSTIC
D 4
	un->un_pid = curproc->p_pid;
E 4
I 4
	if (curproc)
		un->un_pid = curproc->p_pid;
	else
		un->un_pid = -1;
E 4
#endif
I 8

I 16
	un->un_flags |= UN_LOCKED;
E 16
	return (0);
E 8
}

I 37
/*
 * When operations want to vput() a union node yet retain a lock on
 * the upper vnode (say, to do some further operations like link(),
 * mkdir(), ...), they set UN_KLOCK on the union node, then call
 * vput() which calls VOP_UNLOCK() and comes here.  union_unlock()
 * unlocks the union node (leaving the upper vnode alone), clears the
 * KLOCK flag, and then returns to vput().  The caller then does whatever
 * is left to do with the upper vnode, and ensures that it gets unlocked.
 *
 * If UN_KLOCK isn't set, then the upper vnode is unlocked here.
 */
E 37
E 2
int
I 2
union_unlock(ap)
D 41
	struct vop_lock_args *ap;
E 41
I 41
	struct vop_unlock_args /* {
		struct vnode *a_vp;
		int a_flags;
		struct proc *a_p;
	} */ *ap;
E 41
{
	struct union_node *un = VTOUNION(ap->a_vp);
I 39
	struct proc *p = ap->a_p;
E 39

#ifdef DIAGNOSTIC
D 3
	if (un->un_pid != curproc->p_pid)
		panic("union: unlocking other process's union node");
E 3
	if ((un->un_flags & UN_LOCKED) == 0)
		panic("union: unlock unlocked node");
I 3
D 4
	if (un->un_pid != curproc->p_pid)
E 4
I 4
	if (curproc && un->un_pid != curproc->p_pid &&
			curproc->p_pid > -1 && un->un_pid > -1)
E 4
		panic("union: unlocking other process's union node");
E 3
#endif

	un->un_flags &= ~UN_LOCKED;
I 10

	if ((un->un_flags & (UN_ULOCK|UN_KLOCK)) == UN_ULOCK)
D 39
		VOP_UNLOCK(un->un_uppervp);
E 39
I 39
		VOP_UNLOCK(un->un_uppervp, 0, p);
E 39

	un->un_flags &= ~(UN_ULOCK|UN_KLOCK);

E 10
	if (un->un_flags & UN_WANT) {
		un->un_flags &= ~UN_WANT;
		wakeup((caddr_t) &un->un_flags);
	}

#ifdef DIAGNOSTIC
	un->un_pid = 0;
#endif
I 43
	vop_nounlock(ap);
E 43
I 8

	return (0);
E 8
}

int
union_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
		int *a_runp;
	} */ *ap;
{
	int error;
I 39
	struct proc *p = curproc;		/* XXX */
E 39
	struct vnode *vp = OTHERVP(ap->a_vp);
I 10
	int dolock = (vp == LOWERVP(ap->a_vp));
E 10

D 10
	VOP_LOCK(vp);
E 10
I 10
	if (dolock)
D 39
		VOP_LOCK(vp);
E 39
I 39
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
I 17
	else
D 39
		FIXUP(VTOUNION(ap->a_vp));
E 39
I 39
		FIXUP(VTOUNION(ap->a_vp), p);
E 39
E 17
E 10
D 42
	error = VOP_BMAP(vp, ap->a_bn, ap->a_vpp, ap->a_bnp, ap->a_runp);
E 42
I 42
	ap->a_vp = vp;
	error = VCALL(vp, VOFFSET(vop_bmap), ap);
E 42
D 10
	VOP_UNLOCK(vp);
E 10
I 10
	if (dolock)
D 39
		VOP_UNLOCK(vp);
E 39
I 39
		VOP_UNLOCK(vp, 0, p);
E 39
E 10

	return (error);
}

int
E 2
union_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;

	printf("\ttag VT_UNION, vp=%x, uppervp=%x, lowervp=%x\n",
			vp, UPPERVP(vp), LOWERVP(vp));
I 37
	if (UPPERVP(vp) != NULLVP)
		vprint("union: upper", UPPERVP(vp));
	if (LOWERVP(vp) != NULLVP)
		vprint("union: lower", LOWERVP(vp));

E 37
	return (0);
}

I 2
int
union_islocked(ap)
	struct vop_islocked_args /* {
		struct vnode *a_vp;
	} */ *ap;
{
E 2

D 2
/*
 * XXX - vop_strategy must be hand coded because it has no
 * vnode in its arguments.
 * This goes away with a merged VM/buffer cache.
 */
E 2
I 2
	return ((VTOUNION(ap->a_vp)->un_flags & UN_LOCKED) ? 1 : 0);
}

E 2
int
D 2
union_strategy(ap)
	struct vop_strategy_args /* {
		struct buf *a_bp;
E 2
I 2
union_pathconf(ap)
	struct vop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		int *a_retval;
E 2
	} */ *ap;
{
D 2
	struct buf *bp = ap->a_bp;
E 2
	int error;
I 39
	struct proc *p = curproc;		/* XXX */
E 39
D 2
	struct vnode *savedvp;
E 2
I 2
	struct vnode *vp = OTHERVP(ap->a_vp);
I 10
	int dolock = (vp == LOWERVP(ap->a_vp));
E 10
E 2

D 2
	savedvp = bp->b_vp;
	bp->b_vp = OTHERVP(bp->b_vp);
E 2
I 2
D 10
	VOP_LOCK(vp);
E 10
I 10
	if (dolock)
D 39
		VOP_LOCK(vp);
E 39
I 39
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 39
I 17
	else
D 39
		FIXUP(VTOUNION(ap->a_vp));
E 39
I 39
		FIXUP(VTOUNION(ap->a_vp), p);
E 39
E 17
E 10
D 42
	error = VOP_PATHCONF(vp, ap->a_name, ap->a_retval);
E 42
I 42
	ap->a_vp = vp;
	error = VCALL(vp, VOFFSET(vop_pathconf), ap);
E 42
D 10
	VOP_UNLOCK(vp);
E 10
I 10
	if (dolock)
D 39
		VOP_UNLOCK(vp);
E 39
I 39
		VOP_UNLOCK(vp, 0, p);
E 39
E 10
E 2

D 2
#ifdef DIAGNOSTIC
	if (bp->b_vp == 0)
		panic("union_strategy: nil vp");
	if (((bp->b_flags & B_READ) == 0) &&
	    (bp->b_vp == LOWERVP(savedvp)))
		panic("union_strategy: writing to lowervp");
#endif
E 2
I 2
	return (error);
}
E 2

D 2
	error = VOP_STRATEGY(bp);
	bp->b_vp = savedvp;
E 2
I 2
int
union_advlock(ap)
	struct vop_advlock_args /* {
		struct vnode *a_vp;
		caddr_t  a_id;
		int  a_op;
		struct flock *a_fl;
		int  a_flags;
	} */ *ap;
{
I 42
	register struct vnode *ovp = OTHERVP(ap->a_vp);
E 42
E 2

D 2
	return (error);
E 2
I 2
D 42
	return (VOP_ADVLOCK(OTHERVP(ap->a_vp), ap->a_id, ap->a_op,
				ap->a_fl, ap->a_flags));
E 42
I 42
	ap->a_vp = ovp;
	return (VCALL(ovp, VOFFSET(vop_advlock), ap));
E 42
E 2
}


/*
D 2
 * XXX - like vop_strategy, vop_bwrite must be hand coded because it has no
E 2
I 2
 * XXX - vop_strategy must be hand coded because it has no
E 2
 * vnode in its arguments.
 * This goes away with a merged VM/buffer cache.
 */
int
D 2
union_bwrite(ap)
	struct vop_bwrite_args /* {
E 2
I 2
union_strategy(ap)
	struct vop_strategy_args /* {
E 2
		struct buf *a_bp;
	} */ *ap;
{
	struct buf *bp = ap->a_bp;
	int error;
	struct vnode *savedvp;

	savedvp = bp->b_vp;
D 2
	bp->b_vp = UPPERVP(bp->b_vp);
E 2
I 2
	bp->b_vp = OTHERVP(bp->b_vp);
E 2

#ifdef DIAGNOSTIC
D 6
	if (bp->b_vp == 0)
E 6
I 6
	if (bp->b_vp == NULLVP)
E 6
D 2
		panic("union_bwrite: no upper vp");
E 2
I 2
		panic("union_strategy: nil vp");
	if (((bp->b_flags & B_READ) == 0) &&
	    (bp->b_vp == LOWERVP(savedvp)))
		panic("union_strategy: writing to lowervp");
E 2
#endif

D 2
	error = VOP_BWRITE(bp);

E 2
I 2
	error = VOP_STRATEGY(bp);
E 2
	bp->b_vp = savedvp;

	return (error);
}

D 2
int
union_lock(ap)
	struct vop_lock_args *ap;
{
	struct union_node *un = VTOUNION(ap->a_vp);

#ifdef DIAGNOSTIC
	if (un->un_pid == curproc->p_pid)
		panic("union: locking agsinst myself");
#endif
	while (un->un_flags & UN_LOCKED) {
		un->un_flags |= UN_WANT;
		sleep((caddr_t) &un->un_flags, PINOD);
	}
	un->un_flags |= UN_LOCKED;
#ifdef DIAGNOSTIC
	un->un_pid = curproc->p_pid;
#endif

	if (un->un_lowervp && !VOP_ISLOCKED(un->un_lowervp))
		VOP_LOCK(un->un_lowervp);
	if (un->un_uppervp && !VOP_ISLOCKED(un->un_uppervp))
		VOP_LOCK(un->un_uppervp);
}

int
union_unlock(ap)
	struct vop_lock_args *ap;
{
	struct union_node *un = VTOUNION(ap->a_vp);

#ifdef DIAGNOSTIC
	if (un->un_pid != curproc->p_pid)
		panic("union: unlocking other process's union node");
	if ((un->un_flags & UN_LOCKED) == 0)
		panic("union: unlock unlocked node");
#endif

	if (un->un_uppervp && VOP_ISLOCKED(un->un_uppervp))
		VOP_UNLOCK(un->un_uppervp);
	if (un->un_lowervp && VOP_ISLOCKED(un->un_lowervp))
		VOP_UNLOCK(un->un_lowervp);

	un->un_flags &= ~UN_LOCKED;
	if (un->un_flags & UN_WANT) {
		un->un_flags &= ~UN_WANT;
		wakeup((caddr_t) &un->un_flags);
	}

#ifdef DIAGNOSTIC
	un->un_pid = 0;
#endif
}

E 2
/*
 * Global vfs data structures
 */
int (**union_vnodeop_p)();
D 2
struct vnodeopv_entry_desc union_vnodeop_entries[] = {
	{ &vop_default_desc, union_bypass },

	{ &vop_getattr_desc, union_getattr },
	{ &vop_inactive_desc, union_inactive },
	{ &vop_reclaim_desc, union_reclaim },
	{ &vop_print_desc, union_print },

	{ &vop_strategy_desc, union_strategy },
	{ &vop_bwrite_desc, union_bwrite },

	{ &vop_lock_desc, union_lock }, 
	{ &vop_unlock_desc, union_unlock }, 

E 2
I 2
D 3
struct vnodeopv_entry_desc lofs_vnodeop_entries[] = {
E 3
I 3
struct vnodeopv_entry_desc union_vnodeop_entries[] = {
E 3
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, union_lookup },		/* lookup */
	{ &vop_create_desc, union_create },		/* create */
I 31
	{ &vop_whiteout_desc, union_whiteout },		/* whiteout */
E 31
	{ &vop_mknod_desc, union_mknod },		/* mknod */
	{ &vop_open_desc, union_open },			/* open */
	{ &vop_close_desc, union_close },		/* close */
	{ &vop_access_desc, union_access },		/* access */
	{ &vop_getattr_desc, union_getattr },		/* getattr */
	{ &vop_setattr_desc, union_setattr },		/* setattr */
	{ &vop_read_desc, union_read },			/* read */
	{ &vop_write_desc, union_write },		/* write */
I 32
	{ &vop_lease_desc, union_lease },		/* lease */
E 32
	{ &vop_ioctl_desc, union_ioctl },		/* ioctl */
	{ &vop_select_desc, union_select },		/* select */
I 38
	{ &vop_revoke_desc, union_revoke },		/* revoke */
E 38
	{ &vop_mmap_desc, union_mmap },			/* mmap */
	{ &vop_fsync_desc, union_fsync },		/* fsync */
	{ &vop_seek_desc, union_seek },			/* seek */
	{ &vop_remove_desc, union_remove },		/* remove */
	{ &vop_link_desc, union_link },			/* link */
	{ &vop_rename_desc, union_rename },		/* rename */
	{ &vop_mkdir_desc, union_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, union_rmdir },		/* rmdir */
	{ &vop_symlink_desc, union_symlink },		/* symlink */
	{ &vop_readdir_desc, union_readdir },		/* readdir */
	{ &vop_readlink_desc, union_readlink },		/* readlink */
	{ &vop_abortop_desc, union_abortop },		/* abortop */
	{ &vop_inactive_desc, union_inactive },		/* inactive */
	{ &vop_reclaim_desc, union_reclaim },		/* reclaim */
	{ &vop_lock_desc, union_lock },			/* lock */
	{ &vop_unlock_desc, union_unlock },		/* unlock */
	{ &vop_bmap_desc, union_bmap },			/* bmap */
	{ &vop_strategy_desc, union_strategy },		/* strategy */
	{ &vop_print_desc, union_print },		/* print */
	{ &vop_islocked_desc, union_islocked },		/* islocked */
	{ &vop_pathconf_desc, union_pathconf },		/* pathconf */
	{ &vop_advlock_desc, union_advlock },		/* advlock */
#ifdef notdef
	{ &vop_blkatoff_desc, union_blkatoff },		/* blkatoff */
	{ &vop_valloc_desc, union_valloc },		/* valloc */
	{ &vop_vfree_desc, union_vfree },		/* vfree */
	{ &vop_truncate_desc, union_truncate },		/* truncate */
	{ &vop_update_desc, union_update },		/* update */
	{ &vop_bwrite_desc, union_bwrite },		/* bwrite */
#endif
E 2
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
struct vnodeopv_desc union_vnodeop_opv_desc =
	{ &union_vnodeop_p, union_vnodeop_entries };
E 1
