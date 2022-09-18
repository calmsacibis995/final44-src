h06748
s 00088/00002/00531
d D 8.6 95/05/27 22:25:46 mckusick 14 13
c read-only checking must be done by the filesystem layers
e
s 00094/00022/00439
d D 8.5 95/05/22 23:25:05 mckusick 13 12
c add proper locking and lookup routines; document other needed actions
e
s 00028/00004/00433
d D 8.4 95/05/14 00:41:57 mckusick 12 11
c add null_lock to check VXLOCK and cancel the interlock before bypassing
e
s 00002/00001/00435
d D 8.3 95/02/16 12:05:56 mckusick 11 10
c check for null vp before dereferrencing it (from donn@bsdi.com)
e
s 00001/00001/00435
d D 8.2 94/08/20 15:58:29 mckusick 10 9
c update to use LIST hash structures
e
s 00002/00002/00434
d D 8.1 93/06/10 23:46:12 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00040/00023/00396
d D 7.1 92/07/12 15:10:50 mckusick 8 7
c move to rev 7; new include location; misc syntax niggles
e
s 00142/00112/00277
d D 1.7 92/07/11 15:24:18 heideman 7 6
c cleanup
e
s 00036/00007/00353
d D 1.6 92/07/11 08:46:09 heideman 6 5
c Working, with vnode caching.
e
s 00086/00025/00274
d D 1.5 92/07/10 23:17:45 heideman 5 4
c No refcount problems, but no caching.
e
s 00055/00220/00244
d D 1.4 92/07/10 13:46:25 heideman 4 3
c a working version: it does nothing, correctly
e
s 00165/00665/00299
d D 1.3 92/07/07 17:46:39 johnh 3 2
c first draft
e
s 00229/00229/00735
d D 1.2 92/07/07 14:07:47 johnh 2 1
c the great variable renaming
e
s 00964/00000/00000
d D 1.1 92/07/07 13:54:46 johnh 1 0
c date and time created 92/07/07 13:54:46 by johnh
e
u
U
f e 0
t
T
I 1
/*
D 9
 * Copyright (c) 1992 The Regents of the University of California
D 3
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 3
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 3
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
E 3
I 3
D 7
 * This code is derived from the null layer of
D 4
 * John Heidemann of the UCLA Ficus project and
 * the Jan-Simon Pendry's loopback file system.
E 4
I 4
 * John Heidemann from the UCLA Ficus project and
 * Jan-Simon Pendry's loopback file system.
E 7
I 7
 * This code is derived from software contributed to Berkeley by
 * John Heidemann of the UCLA Ficus project.
E 7
E 4
E 3
 *
 * %sccs.include.redist.c%
 *
D 3
 *	@(#)lofs_vnops.c	1.2 (Berkeley) 6/18/92
E 3
I 3
 *	%W% (Berkeley) %G%
E 3
 *
D 3
 * $Id: lofs_vnops.c,v 1.11 1992/05/30 10:05:43 jsp Exp jsp $
E 3
I 3
 * Ancestors:
 *	@(#)lofs_vnops.c	1.2 (Berkeley) 6/18/92
 *	$Id: lofs_vnops.c,v 1.11 1992/05/30 10:05:43 jsp Exp jsp $
 *	...and...
 *	@(#)null_vnodeops.c 1.20 92/07/07 UCLA Ficus project
E 3
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
 *
I 7
 * (See mount_null(8) for more information.)
 *
E 7
 * The null layer duplicates a portion of the file system
 * name space under a new name.  In this respect, it is
 * similar to the loopback file system.  It differs from
 * the loopback fs in two respects:  it is implemented using
D 4
 * a bypass operation, and it's "null-nodes" stack above
E 4
I 4
D 7
 * a bypass operation, and it's "null-node"s stack above
E 7
I 7
 * a stackable layers techniques, and it's "null-node"s stack above
E 7
E 4
 * all lower-layer vnodes, not just over directory vnodes.
 *
I 7
 * The null layer has two purposes.  First, it serves as a demonstration
 * of layering by proving a layer which does nothing.  (It actually
 * does everything the loopback file system does, which is slightly
 * more than nothing.)  Second, the null layer can serve as a prototype
 * layer.  Since it provides all necessary layer framework,
 * new file system layers can be created very easily be starting
 * with a null layer.
 *
 * The remainder of this man page examines the null layer as a basis
 * for constructing new layers.
 *
 *
 * INSTANTIATING NEW NULL LAYERS
 *
 * New null layers are created with mount_null(8).
 * Mount_null(8) takes two arguments, the pathname
 * of the lower vfs (target-pn) and the pathname where the null
 * layer will appear in the namespace (alias-pn).  After
 * the null layer is put into place, the contents
 * of target-pn subtree will be aliased under alias-pn.
 *
 *
 * OPERATION OF A NULL LAYER
 *
E 7
 * The null layer is the minimum file system layer,
 * simply bypassing all possible operations to the lower layer
D 7
 * for processing there.  All but vop_getattr, _inactive, _reclaim,
 * and _print are bypassed.
E 7
I 7
 * for processing there.  The majority of its activity centers
 * on the bypass routine, though which nearly all vnode operations
 * pass.
E 7
 *
D 7
 * Vop_getattr is not bypassed so that we can change the fsid being
 * returned.  Vop_{inactive,reclaim} are bypassed so that
E 7
I 7
 * The bypass routine accepts arbitrary vnode operations for
 * handling by the lower layer.  It begins by examing vnode
 * operation arguments and replacing any null-nodes by their
 * lower-layer equivlants.  It then invokes the operation
 * on the lower layer.  Finally, it replaces the null-nodes
 * in the arguments and, if a vnode is return by the operation,
 * stacks a null-node on top of the returned vnode.
 *
D 13
 * Although bypass handles most operations, 
 * vop_getattr, _inactive, _reclaim, and _print are not bypassed.
 * Vop_getattr must change the fsid being returned.
E 13
I 13
 * Although bypass handles most operations, vop_getattr, vop_lock,
 * vop_unlock, vop_inactive, vop_reclaim, and vop_print are not
 * bypassed. Vop_getattr must change the fsid being returned.
 * Vop_lock and vop_unlock must handle any locking for the
 * current vnode as well as pass the lock request down.
E 13
 * Vop_inactive and vop_reclaim are not bypassed so that
E 7
D 13
 * they can handle freeing null-layer specific data.
D 7
 * Vop_print is not bypassed for debugging.
E 7
I 7
 * Vop_print is not bypassed to avoid excessive debugging
 * information.
E 13
I 13
 * they can handle freeing null-layer specific data. Vop_print
 * is not bypassed to avoid excessive debugging information.
 * Also, certain vnode operations change the locking state within
 * the operation (create, mknod, remove, link, rename, mkdir, rmdir,
 * and symlink). Ideally these operations should not change the
 * lock state, but should be changed to let the caller of the
 * function unlock them. Otherwise all intermediate vnode layers
 * (such as union, umapfs, etc) must catch these functions to do
 * the necessary locking at their layer.
E 13
E 7
 *
I 4
 *
D 7
 * INVOKING OPERATIONS ON LOWER LAYERS
E 7
I 7
 * INSTANTIATING VNODE STACKS
E 7
 *
I 5
D 7
 * 
E 5
E 4
 * NEEDSWORK: Describe methods to invoke operations on the lower layer
 * (bypass vs. VOP).
E 7
I 7
 * Mounting associates the null layer with a lower layer,
 * effect stacking two VFSes.  Vnode stacks are instead
 * created on demand as files are accessed.
E 7
I 4
 *
I 7
 * The initial mount creates a single vnode stack for the
 * root of the new null layer.  All other vnode stacks
 * are created as a result of vnode operations on
 * this or other null vnode stacks.
E 7
 *
D 7
 * CREATING NEW FILESYSTEM LAYERS
E 7
I 7
 * New vnode stacks come into existance as a result of
 * an operation which returns a vnode.  
 * The bypass routine stacks a null-node above the new
 * vnode before returning it to the caller.
E 7
 *
I 7
 * For example, imagine mounting a null layer with
 * "mount_null /usr/include /dev/layer/null".
D 8
 * Chainging directory to /dev/layer/null will assign
E 8
I 8
 * Changing directory to /dev/layer/null will assign
E 8
 * the root null-node (which was created when the null layer was mounted).
 * Now consider opening "sys".  A vop_lookup would be
 * done on the root null-node.  This operation would bypass through
 * to the lower layer which would return a vnode representing 
 * the UFS "sys".  Null_bypass then builds a null-node
 * aliasing the UFS "sys" and returns this to the caller.
 * Later operations on the null-node "sys" will repeat this
 * process when constructing other vnode stacks.
 *
 *
 * CREATING OTHER FILE SYSTEM LAYERS
 *
E 7
 * One of the easiest ways to construct new file system layers is to make
 * a copy of the null layer, rename all files and variables, and
 * then begin modifing the copy.  Sed can be used to easily rename
 * all variables.
 *
I 7
 * The umap layer is an example of a layer descended from the 
 * null layer.
 *
 *
 * INVOKING OPERATIONS ON LOWER LAYERS
 *
 * There are two techniques to invoke operations on a lower layer 
 * when the operation cannot be completely bypassed.  Each method
 * is appropriate in different situations.  In both cases,
 * it is the responsibility of the aliasing layer to make
 * the operation arguments "correct" for the lower layer
 * by mapping an vnode arguments to the lower layer.
 *
 * The first approach is to call the aliasing layer's bypass routine.
 * This method is most suitable when you wish to invoke the operation
 * currently being hanldled on the lower layer.  It has the advantage
D 8
 * the the bypass routine already must do argument mapping.
E 8
I 8
 * that the bypass routine already must do argument mapping.
E 8
 * An example of this is null_getattrs in the null layer.
 *
 * A second approach is to directly invoked vnode operations on
 * the lower layer with the VOP_OPERATIONNAME interface.
 * The advantage of this method is that it is easy to invoke
 * arbitrary operations on the lower layer.  The disadvantage
 * is that vnodes arguments must be manualy mapped.
 *
E 7
E 4
E 3
E 2
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
#include <sys/buf.h>
D 4
#include <lofs/lofs.h>
E 4
I 4
D 8
#include <nullfs/null.h>
E 8
I 8
#include <miscfs/nullfs/null.h>
E 8
E 4

D 3
/*
 * Basic strategy: as usual, do as little work as possible.
 * Nothing is ever locked in the lofs'ed filesystem, all
 * locks are held in the underlying filesystems.
 */
E 3

D 3
/*
 * Save a vnode and replace with
 * the lofs'ed one
 */
#define PUSHREF(v, nd) \
{ \
	struct { struct vnode *vnp; } v; \
	v.vnp = (nd); \
D 2
	(nd) = LOFSVP(v.vnp)
E 2
I 2
	(nd) = NULLTOLOWERVP(v.vnp)
E 3
I 3
int null_bug_bypass = 0;   /* for debugging: enables bypass printf'ing */
E 3
E 2

/*
D 3
 * Undo the PUSHREF
 */
#define POP(v, nd) \
	\
	(nd) = v.vnp; \
}


/*
 * vp is the current namei directory
 * ndp is the name to locate in that directory...
 */
D 2
lofs_lookup (ap)
E 2
I 2
null_lookup (ap)
E 2
	struct vop_lookup_args *ap;
E 3
I 3
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
null_bypass(ap)
D 4
	struct nvop_generic_args *ap;
E 4
I 4
D 8
	struct vop_generic_args *ap;
E 8
I 8
	struct vop_generic_args /* {
		struct vnodeop_desc *a_desc;
		<other random data follows, presumably>
	} */ *ap;
E 8
E 4
E 3
{
D 3
	USES_VOP_LOOKUP;
	struct vnode *dvp = ap->a_dvp;
	struct vnode *newvp;
	struct vnode *targetdvp;
E 3
I 3
D 4
	register int this_vp_p;
E 4
I 4
	extern int (**null_vnodeop_p)();  /* not extern, really "forward" */
	register struct vnode **this_vp_p;
E 4
E 3
	int error;
D 3
	int flag = ap->a_cnp->cn_nameiop /*& OPMASK*/;
E 3
I 3
	struct vnode *old_vps[VDESC_MAX_VPS];
	struct vnode **vps_p[VDESC_MAX_VPS];
	struct vnode ***vppp;
	struct vnodeop_desc *descp = ap->a_desc;
D 4
	int maps, reles, i;
E 4
I 4
	int reles, i;
E 4
E 3

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_lookup(ap->a_dvp = %x->%x, \"%s\", op = %d)\n",
		dvp, LOFSVP(dvp), ap->a_cnp->cn_nameptr, flag);
E 2
I 2
D 3
#ifdef NULLFS_DIAGNOSTIC
	printf("null_lookup(ap->a_dvp = %x->%x, \"%s\", op = %d)\n",
		dvp, NULLTOLOWERVP(dvp), ap->a_cnp->cn_nameptr, flag);
E 2
#endif
E 3
I 3
	if (null_bug_bypass)
		printf ("null_bypass: %s\n", descp->vdesc_name);
E 3

I 3
#ifdef SAFETY
E 3
	/*
D 3
	 * (ap->a_dvp) was locked when passed in, and it will be replaced
	 * with the target vnode, BUT that will already have been
D 2
	 * locked when (ap->a_dvp) was locked [see lofs_lock].  all that
E 2
I 2
	 * locked when (ap->a_dvp) was locked [see null_lock].  all that
E 2
	 * must be done here is to keep track of reference counts.
E 3
I 3
	 * We require at least one vp.
E 3
	 */
D 2
	targetdvp = LOFSVP(dvp);
E 2
I 2
D 3
	targetdvp = NULLTOLOWERVP(dvp);
E 2
	/*VREF(targetdvp);*/
D 2
#ifdef LOFS_DIAGNOSTIC
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
E 2
	vprint("lofs VOP_LOOKUP", targetdvp);
E 3
I 3
D 5
	if (descp->vdesc_vp_offsets==NULL ||
	    descp->vdesc_vp_offsets[0]==VDESC_NO_OFFSET)
E 5
I 5
	if (descp->vdesc_vp_offsets == NULL ||
	    descp->vdesc_vp_offsets[0] == VDESC_NO_OFFSET)
E 5
		panic ("null_bypass: no vp's in map.\n");
E 3
#endif

	/*
D 3
	 * Call lookup on the looped vnode
E 3
I 3
	 * Map the vnodes going in.
	 * Later, we'll invoke the operation based on
	 * the first mapped vnode's operation vector.
E 3
	 */
D 3
	error = VOP_LOOKUP(targetdvp, &newvp, ap->a_cnp);
	/*vrele(targetdvp);*/
E 3
I 3
D 4
	maps = descp->vdesc_flags;
	reles = descp->vdesc_rele_flags;
	for (i=0; i<VDESC_MAX_VPS; maps>>=1, reles>>=1, i++) {
E 4
I 4
	reles = descp->vdesc_flags;
D 5
	for (i=0; i<VDESC_MAX_VPS; reles>>=1, i++) {
E 4
		if (descp->vdesc_vp_offsets[i]==VDESC_NO_OFFSET)
E 5
I 5
	for (i = 0; i < VDESC_MAX_VPS; reles >>= 1, i++) {
		if (descp->vdesc_vp_offsets[i] == VDESC_NO_OFFSET)
E 5
			break;   /* bail out at end of list */
D 4
		if (maps & 1)   /* skip vps that aren't to be mapped */
			continue;
E 4
		vps_p[i] = this_vp_p = 
			VOPARG_OFFSETTO(struct vnode**,descp->vdesc_vp_offsets[i],ap);
D 4
		old_vps[i] = *this_vp_p;
		*(vps_p[i]) = NULLTOLOWERVP(VTONULLNODE(*this_vp_p));
		if (reles & 1)
			VREF(*this_vp_p);
E 4
I 4
		/*
		 * We're not guaranteed that any but the first vnode
		 * are of our type.  Check for and don't map any
D 6
		 * that aren't.
E 6
I 6
D 7
		 * that aren't.  (Must map first vp or vclean fails.)
E 7
I 7
		 * that aren't.  (We must always map first vp or vclean fails.)
E 7
E 6
		 */
D 6
		if ((*this_vp_p)->v_op != null_vnodeop_p) {
E 6
I 6
D 11
		if (i && (*this_vp_p)->v_op != null_vnodeop_p) {
E 11
I 11
		if (i && (*this_vp_p == NULL ||
		    (*this_vp_p)->v_op != null_vnodeop_p)) {
E 11
E 6
			old_vps[i] = NULL;
		} else {
			old_vps[i] = *this_vp_p;
			*(vps_p[i]) = NULLVPTOLOWERVP(*this_vp_p);
I 5
			/*
			 * XXX - Several operations have the side effect
			 * of vrele'ing their vp's.  We must account for
			 * that.  (This should go away in the future.)
			 */
E 5
			if (reles & 1)
				VREF(*this_vp_p);
D 5
		};
E 5
I 5
		}
E 5
E 4
			
D 5
	};
E 5
I 5
	}
E 5
E 3

D 3
	if (error) {
		*ap->a_vpp = NULLVP;
D 2
#ifdef LOFS_DIAGNOSTIC
		printf("lofs_lookup(%x->%x) = %d\n", dvp, LOFSVP(dvp), error);
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
		printf("null_lookup(%x->%x) = %d\n", dvp, NULLTOLOWERVP(dvp), error);
E 2
#endif
		return (error);
	}
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_lookup(%x->%x) = OK\n", dvp, LOFSVP(dvp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_lookup(%x->%x) = OK\n", dvp, NULLTOLOWERVP(dvp));
E 2
#endif

	*ap->a_vpp = newvp;

E 3
	/*
D 3
	 * If we just found a directory then make
	 * a loopback node for it and return the loopback
	 * instead of the real vnode.  Otherwise simply
	 * return the aliased directory and vnode.
E 3
I 3
	 * Call the operation on the lower layer
	 * with the modified argument structure.
E 3
	 */
D 3
	if (newvp && newvp->v_type == VDIR && flag == LOOKUP) {
D 2
#ifdef LOFS_DIAGNOSTIC
		printf("lofs_lookup: found VDIR\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
		printf("null_lookup: found VDIR\n");
E 2
#endif
		/*
		 * At this point, newvp is the vnode to be looped.
		 * Activate a loopback and return the looped vnode.
		 */
D 2
		return (make_lofs(dvp->v_mount, ap->a_vpp));
E 2
I 2
		return (make_null_node(dvp->v_mount, ap->a_vpp));
E 2
	}
E 3
I 3
	error = VCALL(*(vps_p[0]), descp->vdesc_offset, ap);
E 3

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_lookup: not VDIR\n");
E 2
I 2
D 3
#ifdef NULLFS_DIAGNOSTIC
	printf("null_lookup: not VDIR\n");
E 2
#endif

	return (0);
}

/*
 * this = ni_dvp
 * ni_dvp references the locked directory.
 * ni_vp is NULL.
 */
D 2
lofs_mknod (ap)
E 2
I 2
null_mknod (ap)
E 2
	struct vop_mknod_args *ap;
{
	USES_VOP_MKNOD;
	int error;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_mknod(vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_mknod(vp = %x->%x)\n", ap->a_dvp, NULLTOLOWERVP(ap->a_dvp));
E 2
#endif

	PUSHREF(xdvp, ap->a_dvp);
	VREF(ap->a_dvp);

	error = VOP_MKNOD(ap->a_dvp, ap->a_vpp, ap->a_cnp, ap->a_vap);

	POP(xdvp, ap->a_dvp);
	vrele(ap->a_dvp);

	return (error);
}

/*
 * this = ni_dvp;
 * ni_dvp references the locked directory
 * ni_vp is NULL.
 */
D 2
lofs_create (ap)
E 2
I 2
null_create (ap)
E 2
	struct vop_create_args *ap;
{
	USES_VOP_CREATE;
	int error;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_create(ap->a_dvp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_create(ap->a_dvp = %x->%x)\n", ap->a_dvp, NULLTOLOWERVP(ap->a_dvp));
E 2
#endif

	PUSHREF(xdvp, ap->a_dvp);
	VREF(ap->a_dvp);

	error = VOP_CREATE(ap->a_dvp, ap->a_vpp, ap->a_cnp, ap->a_vap);

	POP(xdvp, ap->a_dvp);
	vrele(ap->a_dvp);

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_create(ap->a_dvp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_create(ap->a_dvp = %x->%x)\n", ap->a_dvp, NULLTOLOWERVP(ap->a_dvp));
E 2
#endif

	return (error);
}

D 2
lofs_open (ap)
E 2
I 2
null_open (ap)
E 2
	struct vop_open_args *ap;
{
	USES_VOP_OPEN;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_open(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_open(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_OPEN(LOFSVP(ap->a_vp), ap->a_mode, ap->a_cred, ap->a_p);
E 2
I 2
	return VOP_OPEN(NULLTOLOWERVP(ap->a_vp), ap->a_mode, ap->a_cred, ap->a_p);
E 2
}

D 2
lofs_close (ap)
E 2
I 2
null_close (ap)
E 2
	struct vop_close_args *ap;
{
	USES_VOP_CLOSE;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_close(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_close(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_CLOSE(LOFSVP(ap->a_vp), ap->a_fflag, ap->a_cred, ap->a_p);
E 2
I 2
	return VOP_CLOSE(NULLTOLOWERVP(ap->a_vp), ap->a_fflag, ap->a_cred, ap->a_p);
E 2
}

D 2
lofs_access (ap)
E 2
I 2
null_access (ap)
E 2
	struct vop_access_args *ap;
{
	USES_VOP_ACCESS;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_access(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_access(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_ACCESS(LOFSVP(ap->a_vp), ap->a_mode, ap->a_cred, ap->a_p);
E 2
I 2
	return VOP_ACCESS(NULLTOLOWERVP(ap->a_vp), ap->a_mode, ap->a_cred, ap->a_p);
E 2
}

D 2
lofs_getattr (ap)
E 2
I 2
null_getattr (ap)
E 2
	struct vop_getattr_args *ap;
{
	USES_VOP_GETATTR;
	int error;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_getattr(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_getattr(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

E 3
	/*
D 3
	 * Get the stats from the underlying filesystem
E 3
I 3
	 * Maintain the illusion of call-by-value
	 * by restoring vnodes in the argument structure
	 * to their original value.
E 3
	 */
D 2
	error = VOP_GETATTR(LOFSVP(ap->a_vp), ap->a_vap, ap->a_cred, ap->a_p);
E 2
I 2
D 3
	error = VOP_GETATTR(NULLTOLOWERVP(ap->a_vp), ap->a_vap, ap->a_cred, ap->a_p);
E 2
	if (error)
		return (error);
E 3
I 3
D 4
	maps = descp->vdesc_flags;
	reles = descp->vdesc_rele_flags;
	for (i=0; i<VDESC_MAX_VPS; maps>>=1, i++) {
E 4
I 4
	reles = descp->vdesc_flags;
D 5
	for (i=0; i<VDESC_MAX_VPS; reles>>=1, i++) {
E 4
		if (descp->vdesc_vp_offsets[i]==VDESC_NO_OFFSET)
E 5
I 5
	for (i = 0; i < VDESC_MAX_VPS; reles >>= 1, i++) {
		if (descp->vdesc_vp_offsets[i] == VDESC_NO_OFFSET)
E 5
			break;   /* bail out at end of list */
D 4
		if (maps & 1)   /* skip vps that aren't to be mapped */
			continue;
		*(vps_p[i]) = old_vps[i];
		if (reles & 1)
			vrele(*(vps_p[i]));
E 4
I 4
		if (old_vps[i]) {
			*(vps_p[i]) = old_vps[i];
			if (reles & 1)
				vrele(*(vps_p[i]));
D 5
		};
E 4
	};
E 5
I 5
		}
	}
E 5

E 3
	/*
D 3
	 * and replace the fsid field with the loopback number
	 * to preserve the namespace.
E 3
I 3
D 5
	 * Map the possible out-going vpp.
E 5
I 5
	 * Map the possible out-going vpp
	 * (Assumes that the lower layer always returns
	 * a VREF'ed vpp unless it gets an error.)
E 5
E 3
	 */
D 3
	ap->a_vap->va_fsid = ap->a_vp->v_mount->mnt_stat.f_fsid.val[0];
	return (0);
}
E 3
I 3
	if (descp->vdesc_vpp_offset != VDESC_NO_OFFSET &&
	    !(descp->vdesc_flags & VDESC_NOMAP_VPP) &&
	    !error) {
D 5
		vppp=VOPARG_OFFSETTO(struct vnode***,
E 5
I 5
		/*
		 * XXX - even though some ops have vpp returned vp's,
		 * several ops actually vrele this before returning.
		 * We must avoid these ops.
D 7
		 * (This should go away.)
E 7
I 7
		 * (This should go away when these ops are regularized.)
E 7
		 */
D 7
		if (descp->vdesc_flags & VDESC_VPP_WILLRELE) {
#ifdef NULLFS_DIAGNOSTIC
			printf("null_bypass (%s), lowervpp->usecount = %d\n", vdesc->vdesc_name, (**vppp)->v_usecount);
#endif
			return (error);
		}
E 7
I 7
		if (descp->vdesc_flags & VDESC_VPP_WILLRELE)
			goto out;
E 7
		vppp = VOPARG_OFFSETTO(struct vnode***,
E 5
				 descp->vdesc_vpp_offset,ap);
D 4
		error = make_null_node(old_vps[0]->v_mount, **vppp, *vppp);
E 4
I 4
		error = null_node_create(old_vps[0]->v_mount, **vppp, *vppp);
E 4
D 5
	};
E 5
I 5
	}
E 5
E 3

I 7
 out:
E 7
D 2
lofs_setattr (ap)
E 2
I 2
D 3
null_setattr (ap)
E 2
	struct vop_setattr_args *ap;
{
	USES_VOP_SETATTR;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_setattr(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_setattr(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_SETATTR(LOFSVP(ap->a_vp), ap->a_vap, ap->a_cred, ap->a_p);
E 2
I 2
	return VOP_SETATTR(NULLTOLOWERVP(ap->a_vp), ap->a_vap, ap->a_cred, ap->a_p);
E 2
}

D 2
lofs_read (ap)
E 2
I 2
null_read (ap)
E 2
	struct vop_read_args *ap;
{
	USES_VOP_READ;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_read(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_read(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_READ(LOFSVP(ap->a_vp), ap->a_uio, ap->a_ioflag, ap->a_cred);
E 2
I 2
	return VOP_READ(NULLTOLOWERVP(ap->a_vp), ap->a_uio, ap->a_ioflag, ap->a_cred);
E 2
}

D 2
lofs_write (ap)
E 2
I 2
null_write (ap)
E 2
	struct vop_write_args *ap;
{
	USES_VOP_WRITE;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_write(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_write(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_WRITE(LOFSVP(ap->a_vp), ap->a_uio, ap->a_ioflag, ap->a_cred);
E 2
I 2
	return VOP_WRITE(NULLTOLOWERVP(ap->a_vp), ap->a_uio, ap->a_ioflag, ap->a_cred);
E 2
}

D 2
lofs_ioctl (ap)
E 2
I 2
null_ioctl (ap)
E 2
	struct vop_ioctl_args *ap;
{
	USES_VOP_IOCTL;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_ioctl(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_ioctl(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_IOCTL(LOFSVP(ap->a_vp), ap->a_command, ap->a_data, ap->a_fflag, ap->a_cred, ap->a_p);
E 2
I 2
	return VOP_IOCTL(NULLTOLOWERVP(ap->a_vp), ap->a_command, ap->a_data, ap->a_fflag, ap->a_cred, ap->a_p);
E 2
}

D 2
lofs_select (ap)
E 2
I 2
null_select (ap)
E 2
	struct vop_select_args *ap;
{
	USES_VOP_SELECT;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_select(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_select(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_SELECT(LOFSVP(ap->a_vp), ap->a_which, ap->a_fflags, ap->a_cred, ap->a_p);
E 2
I 2
	return VOP_SELECT(NULLTOLOWERVP(ap->a_vp), ap->a_which, ap->a_fflags, ap->a_cred, ap->a_p);
E 2
}

D 2
lofs_mmap (ap)
E 2
I 2
null_mmap (ap)
E 2
	struct vop_mmap_args *ap;
{
	USES_VOP_MMAP;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_mmap(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_mmap(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_MMAP(LOFSVP(ap->a_vp), ap->a_fflags, ap->a_cred, ap->a_p);
E 2
I 2
	return VOP_MMAP(NULLTOLOWERVP(ap->a_vp), ap->a_fflags, ap->a_cred, ap->a_p);
E 2
}

D 2
lofs_fsync (ap)
E 2
I 2
null_fsync (ap)
E 2
	struct vop_fsync_args *ap;
{
	USES_VOP_FSYNC;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_fsync(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_fsync(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_FSYNC(LOFSVP(ap->a_vp), ap->a_fflags, ap->a_cred, ap->a_waitfor, ap->a_p);
E 2
I 2
	return VOP_FSYNC(NULLTOLOWERVP(ap->a_vp), ap->a_fflags, ap->a_cred, ap->a_waitfor, ap->a_p);
E 2
}

D 2
lofs_seek (ap)
E 2
I 2
null_seek (ap)
E 2
	struct vop_seek_args *ap;
{
	USES_VOP_SEEK;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_seek(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_seek(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_SEEK(LOFSVP(ap->a_vp), ap->a_oldoff, ap->a_newoff, ap->a_cred);
E 2
I 2
	return VOP_SEEK(NULLTOLOWERVP(ap->a_vp), ap->a_oldoff, ap->a_newoff, ap->a_cred);
E 2
}

D 2
lofs_remove (ap)
E 2
I 2
null_remove (ap)
E 2
	struct vop_remove_args *ap;
{
	USES_VOP_REMOVE;
	int error;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_remove(ap->a_vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_remove(ap->a_vp = %x->%x)\n", ap->a_dvp, NULLTOLOWERVP(ap->a_dvp));
E 2
#endif

	PUSHREF(xdvp, ap->a_dvp);
	VREF(ap->a_dvp);
	PUSHREF(xvp, ap->a_vp);
	VREF(ap->a_vp);

	error = VOP_REMOVE(ap->a_dvp, ap->a_vp, ap->a_cnp);

	POP(xvp, ap->a_vp);
	vrele(ap->a_vp);
	POP(xdvp, ap->a_dvp);
	vrele(ap->a_dvp);

E 3
	return (error);
}

I 3
D 12

E 12
E 3
/*
I 13
 * We have to carry on the locking protocol on the null layer vnodes
D 14
 * as we progress through the tree.
E 14
I 14
 * as we progress through the tree. We also have to enforce read-only
 * if this layer is mounted read-only.
E 14
 */
null_lookup(ap)
	struct vop_lookup_args /* {
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
	} */ *ap;
{
D 14
	struct proc *p = ap->a_cnp->cn_proc;
E 14
I 14
	struct componentname *cnp = ap->a_cnp;
	struct proc *p = cnp->cn_proc;
	int flags = cnp->cn_flags;
E 14
	struct vop_lock_args lockargs;
	struct vop_unlock_args unlockargs;
	struct vnode *dvp, *vp;
	int error;

I 14
	if ((flags & ISLASTCN) && (ap->a_dvp->v_mount->mnt_flag & MNT_RDONLY) &&
	    (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME))
		return (EROFS);
E 14
	error = null_bypass(ap);
I 14
	if (error == EJUSTRETURN && (flags & ISLASTCN) &&
	    (ap->a_dvp->v_mount->mnt_flag & MNT_RDONLY) &&
	    (cnp->cn_nameiop == CREATE || cnp->cn_nameiop == RENAME))
		error = EROFS;
E 14
	/*
	 * We must do the same locking and unlocking at this layer as 
	 * is done in the layers below us. We could figure this out 
	 * based on the error return and the LASTCN, LOCKPARENT, and
	 * LOCKLEAF flags. However, it is more expidient to just find 
	 * out the state of the lower level vnodes and set ours to the
	 * same state.
	 */
	dvp = ap->a_dvp;
	vp = *ap->a_vpp;
	if (dvp == vp)
		return (error);
	if (!VOP_ISLOCKED(dvp)) {
		unlockargs.a_vp = dvp;
		unlockargs.a_flags = 0;
		unlockargs.a_p = p;
		vop_nounlock(&unlockargs);
	}
	if (vp != NULL && VOP_ISLOCKED(vp)) {
		lockargs.a_vp = vp;
		lockargs.a_flags = LK_SHARED;
		lockargs.a_p = p;
		vop_nolock(&lockargs);
	}
	return (error);
}

/*
I 14
 * Setattr call. Disallow write attempts if the layer is mounted read-only.
 */
int
null_setattr(ap)
	struct vop_setattr_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	struct vattr *vap = ap->a_vap;

  	if ((vap->va_flags != VNOVAL || vap->va_uid != (uid_t)VNOVAL ||
	    vap->va_gid != (gid_t)VNOVAL || vap->va_atime.ts_sec != VNOVAL ||
	    vap->va_mtime.ts_sec != VNOVAL || vap->va_mode != (mode_t)VNOVAL) &&
	    (vp->v_mount->mnt_flag & MNT_RDONLY))
		return (EROFS);
	if (vap->va_size != VNOVAL) {
 		switch (vp->v_type) {
 		case VDIR:
 			return (EISDIR);
 		case VCHR:
 		case VBLK:
 		case VSOCK:
 		case VFIFO:
			return (0);
		case VREG:
		case VLNK:
 		default:
			/*
			 * Disallow write attempts if the filesystem is
			 * mounted read-only.
			 */
			if (vp->v_mount->mnt_flag & MNT_RDONLY)
				return (EROFS);
		}
	}
	return (null_bypass(ap));
}

/*
E 14
E 13
D 3
 * vp is this.
 * ni_dvp is the locked parent of the target.
 * ni_vp is NULL.
E 3
I 3
D 7
 *  We handle getattr to change the fsid.
E 7
I 7
 *  We handle getattr only to change the fsid.
E 7
E 3
 */
D 2
lofs_link (ap)
E 2
I 2
D 3
null_link (ap)
E 2
	struct vop_link_args *ap;
E 3
I 3
int
null_getattr(ap)
D 4
	struct nvop_getattr_args *ap;
E 4
I 4
D 8
	struct vop_getattr_args *ap;
E 8
I 8
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 8
E 4
E 3
{
D 3
	USES_VOP_LINK;
E 3
	int error;
I 13

E 13
D 3

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_link(ap->a_tdvp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_link(ap->a_tdvp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

	PUSHREF(xdvp, ap->a_vp);
	VREF(ap->a_vp);

D 2
	error = VOP_LINK(ap->a_vp, LOFSVP(ap->a_tdvp), ap->a_cnp);
E 2
I 2
	error = VOP_LINK(ap->a_vp, NULLTOLOWERVP(ap->a_tdvp), ap->a_cnp);
E 2

	POP(xdvp, ap->a_vp);
	vrele(ap->a_vp);

	return (error);
E 3
I 3
D 5
	if (error=null_bypass(ap))
E 5
I 5
	if (error = null_bypass(ap))
E 5
D 8
		return error;
E 8
I 8
		return (error);
E 8
	/* Requires that arguments be restored. */
	ap->a_vap->va_fsid = ap->a_vp->v_mount->mnt_stat.f_fsid.val[0];
D 8
	return 0;
E 8
I 8
	return (0);
E 8
E 3
}

I 14
int
null_access(ap)
	struct vop_access_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	mode_t mode = ap->a_mode;

	/*
	 * Disallow write attempts on read-only layers;
	 * unless the file is a socket, fifo, or a block or
	 * character device resident on the file system.
	 */
	if (mode & VWRITE) {
		switch (vp->v_type) {
		case VDIR:
		case VLNK:
		case VREG:
			if (vp->v_mount->mnt_flag & MNT_RDONLY)
				return (EROFS);
			break;
		}
	}
	return (null_bypass(ap));
}

E 14
I 12
/*
D 13
 * We need to verify that we are not being vgoned and then clear
 * the interlock flag as it applies only to our vnode, not the
E 13
I 13
 * We need to process our own vnode lock and then clear the
 * interlock flag as it applies only to our vnode, not the
E 13
 * vnodes below us on the stack.
 */
int
null_lock(ap)
D 13
	struct vop_lock_args *ap;
E 13
I 13
	struct vop_lock_args /* {
		struct vnode *a_vp;
		int a_flags;
		struct proc *a_p;
	} */ *ap;
E 13
{
I 13

	vop_nolock(ap);
	if ((ap->a_flags & LK_TYPE_MASK) == LK_DRAIN)
		return (0);
	ap->a_flags &= ~LK_INTERLOCK;
	return (null_bypass(ap));
}

/*
 * We need to process our own vnode unlock and then clear the
 * interlock flag as it applies only to our vnode, not the
 * vnodes below us on the stack.
 */
int
null_unlock(ap)
	struct vop_unlock_args /* {
		struct vnode *a_vp;
		int a_flags;
		struct proc *a_p;
	} */ *ap;
{
E 13
	struct vnode *vp = ap->a_vp;
D 13
	int error;
E 13
E 12
I 5
D 7
/*
 * XXX - Ideally inactive does not release the lowervp
 * so the null_node can stay around in the cache and be reused.
 * Unfortunately, this currently causes "locking against self"
 * problems in the UFS, so currently AVOID_CACHING hacks
 * around the bug.
 */
D 6
#define AVOID_CACHING
E 6
I 6
/* #define AVOID_CACHING */
E 7
E 6
E 5
I 3

I 12
D 13
	if ((ap->a_flags & LK_INTERLOCK) == 0)
		simple_lock(&vp->v_interlock);
	if (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		simple_unlock(&vp->v_interlock);
		tsleep((caddr_t)vp, PINOD, "unionlk1", 0);
		return (ENOENT);
	}
	simple_unlock(&vp->v_interlock);
E 13
I 13
	vop_nounlock(ap);
E 13
	ap->a_flags &= ~LK_INTERLOCK;
D 13
	if (error = null_bypass(ap))
		return (error);
	return (0);
E 13
I 13
	return (null_bypass(ap));
E 13
}

E 12
D 4
#if 0
E 3
D 2
lofs_rename (ap)
E 2
I 2
null_rename (ap)
E 2
	struct vop_rename_args *ap;
{
	USES_VOP_RENAME;
	struct vnode *fvp, *tvp;
	struct vnode *tdvp;
#if 0
	struct vnode *fsvp, *tsvp;
#endif
	int error;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename(fdvp = %x->%x)\n", ap->a_fdvp, LOFSVP(ap->a_fdvp));
	/*printf("lofs_rename(tdvp = %x->%x)\n", tndp->ni_dvp, LOFSVP(tndp->ni_dvp));*/
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename(fdvp = %x->%x)\n", ap->a_fdvp, NULLTOLOWERVP(ap->a_fdvp));
	/*printf("null_rename(tdvp = %x->%x)\n", tndp->ni_dvp, NULLTOLOWERVP(tndp->ni_dvp));*/
E 2
#endif

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch source dvp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - switch source dvp\n");
E 2
#endif
	/*
	 * Switch source directory to point to lofsed vnode
	 */
	PUSHREF(fdvp, ap->a_fdvp);
	VREF(ap->a_fdvp);

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch source vp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - switch source vp\n");
E 2
#endif
	/*
	 * And source object if it is lofsed...
	 */
	fvp = ap->a_fvp;
D 2
	if (fvp && fvp->v_op == lofs_vnodeop_p) {
		ap->a_fvp = LOFSVP(fvp);
E 2
I 2
	if (fvp && fvp->v_op == null_vnodeop_p) {
		ap->a_fvp = NULLTOLOWERVP(fvp);
E 2
		VREF(ap->a_fvp);
	} else {
		fvp = 0;
	}

#if 0
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch source start vp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - switch source start vp\n");
E 2
#endif
	/*
	 * And source startdir object if it is lofsed...
	 */
	fsvp = fndp->ni_startdir;
D 2
	if (fsvp && fsvp->v_op == lofs_vnodeop_p) {
		fndp->ni_startdir = LOFSVP(fsvp);
E 2
I 2
	if (fsvp && fsvp->v_op == null_vnodeop_p) {
		fndp->ni_startdir = NULLTOLOWERVP(fsvp);
E 2
		VREF(fndp->ni_startdir);
	} else {
		fsvp = 0;
	}
#endif

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch target dvp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - switch target dvp\n");
E 2
#endif
	/*
 	 * Switch target directory to point to lofsed vnode
	 */
	tdvp = ap->a_tdvp;
D 2
	if (tdvp && tdvp->v_op == lofs_vnodeop_p) {
		ap->a_tdvp = LOFSVP(tdvp);
E 2
I 2
	if (tdvp && tdvp->v_op == null_vnodeop_p) {
		ap->a_tdvp = NULLTOLOWERVP(tdvp);
E 2
		VREF(ap->a_tdvp);
	} else {
		tdvp = 0;
	}

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch target vp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - switch target vp\n");
E 2
#endif
	/*
	 * And target object if it is lofsed...
	 */
	tvp = ap->a_tvp;
D 2
	if (tvp && tvp->v_op == lofs_vnodeop_p) {
		ap->a_tvp = LOFSVP(tvp);
E 2
I 2
	if (tvp && tvp->v_op == null_vnodeop_p) {
		ap->a_tvp = NULLTOLOWERVP(tvp);
E 2
		VREF(ap->a_tvp);
	} else {
		tvp = 0;
	}

#if 0
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch target start vp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - switch target start vp\n");
E 2
#endif
	/*
	 * And target startdir object if it is lofsed...
	 */
	tsvp = tndp->ni_startdir;
D 2
	if (tsvp && tsvp->v_op == lofs_vnodeop_p) {
		tndp->ni_startdir = LOFSVP(fsvp);
E 2
I 2
	if (tsvp && tsvp->v_op == null_vnodeop_p) {
		tndp->ni_startdir = NULLTOLOWERVP(fsvp);
E 2
		VREF(tndp->ni_startdir);
	} else {
		tsvp = 0;
	}
#endif

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - VOP_RENAME(%x, %x, %x, %x)\n",
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - VOP_RENAME(%x, %x, %x, %x)\n",
E 2
		ap->a_fdvp, ap->a_fvp, ap->a_tdvp, ap->a_tvp);
	vprint("ap->a_fdvp", ap->a_fdvp);
	vprint("ap->a_fvp", ap->a_fvp);
	vprint("ap->a_tdvp", ap->a_tdvp);
	if (ap->a_tvp) vprint("ap->a_tvp", ap->a_tvp);
	DELAY(16000000);
#endif

	error = VOP_RENAME(ap->a_fdvp, ap->a_fvp, ap->a_fcnp, ap->a_tdvp, ap->a_tvp, ap->a_tcnp);

	/*
	 * Put everything back...
	 */
 
#if 0
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore target startdir\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - restore target startdir\n");
E 2
#endif

	if (tsvp) {
		if (tndp->ni_startdir)
			vrele(tndp->ni_startdir);
		tndp->ni_startdir = tsvp;
	}
#endif

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore target vp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - restore target vp\n");
E 2
#endif

	if (tvp) {
		ap->a_tvp = tvp;
		vrele(ap->a_tvp);
	}

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore target dvp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - restore target dvp\n");
E 2
#endif

	if (tdvp) {
		ap->a_tdvp = tdvp;
		vrele(ap->a_tdvp);
	}

#if 0
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore source startdir\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - restore source startdir\n");
E 2
#endif

	if (fsvp) {
		if (fndp->ni_startdir)
			vrele(fndp->ni_startdir);
		fndp->ni_startdir = fsvp;
	}
#endif

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore source vp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - restore source vp\n");
E 2
#endif


	if (fvp) {
		ap->a_fvp = fvp;
		vrele(ap->a_fvp);
	}

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore source dvp\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rename - restore source dvp\n");
E 2
#endif

	POP(fdvp, ap->a_fdvp);
	vrele(ap->a_fdvp);

	return (error);
}
D 3

/*
 * ni_dvp is the locked (alias) parent.
 * ni_vp is NULL.
 */
D 2
lofs_mkdir (ap)
E 2
I 2
null_mkdir (ap)
E 2
	struct vop_mkdir_args *ap;
{
	USES_VOP_MKDIR;
	int error;
	struct vnode *dvp = ap->a_dvp;
	struct vnode *xdvp;
	struct vnode *newvp;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_mkdir(vp = %x->%x)\n", dvp, LOFSVP(dvp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_mkdir(vp = %x->%x)\n", dvp, NULLTOLOWERVP(dvp));
E 3
E 2
#endif

D 3
	xdvp = dvp;
D 2
	dvp = LOFSVP(xdvp);
E 2
I 2
	dvp = NULLTOLOWERVP(xdvp);
E 2
	/*VREF(dvp);*/
E 3

E 4
D 3
	error = VOP_MKDIR(dvp, &newvp, ap->a_cnp, ap->a_vap);

	if (error) {
		*ap->a_vpp = NULLVP;
		/*vrele(xdvp);*/
		return (error);
	}

	/*
	 * Make a new lofs node
	 */
	/*VREF(dvp);*/

D 2
	error = make_lofs(dvp->v_mount, &newvp);
E 2
I 2
	error = make_null_node(dvp->v_mount, &newvp);
E 2

	*ap->a_vpp = newvp;

	return (error);
}

/*
 * ni_dvp is the locked parent.
 * ni_vp is the entry to be removed.
 */
D 2
lofs_rmdir (ap)
E 2
I 2
null_rmdir (ap)
E 2
	struct vop_rmdir_args *ap;
{
	USES_VOP_RMDIR;
	struct vnode *vp = ap->a_vp;
	struct vnode *dvp = ap->a_dvp;
	int error;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rmdir(dvp = %x->%x)\n", dvp, LOFSVP(dvp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_rmdir(dvp = %x->%x)\n", dvp, NULLTOLOWERVP(dvp));
E 2
#endif

	PUSHREF(xdvp, dvp);
	VREF(dvp);
	PUSHREF(xvp, vp);
	VREF(vp);

	error = VOP_RMDIR(dvp, vp, ap->a_cnp);

	POP(xvp, vp);
	vrele(vp);
	POP(xdvp, dvp);
	vrele(dvp);

	return (error);
}

/*
 * ni_dvp is the locked parent.
 * ni_vp is NULL.
 */
D 2
lofs_symlink (ap)
E 2
I 2
null_symlink (ap)
E 2
	struct vop_symlink_args *ap;
{
	USES_VOP_SYMLINK;
	int error;

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("VOP_SYMLINK(vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("VOP_SYMLINK(vp = %x->%x)\n", ap->a_dvp, NULLTOLOWERVP(ap->a_dvp));
E 2
#endif

	PUSHREF(xdvp, ap->a_dvp);
	VREF(ap->a_dvp);

	error = VOP_SYMLINK(ap->a_dvp, ap->a_vpp, ap->a_cnp, ap->a_vap, ap->a_target);

	POP(xdvp, ap->a_dvp);
	vrele(ap->a_dvp);

	return (error);
}

D 2
lofs_readdir (ap)
E 2
I 2
null_readdir (ap)
E 2
	struct vop_readdir_args *ap;
{
	USES_VOP_READDIR;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_readdir(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_readdir(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_READDIR(LOFSVP(ap->a_vp), ap->a_uio, ap->a_cred, ap->a_eofflagp);
E 2
I 2
	return VOP_READDIR(NULLTOLOWERVP(ap->a_vp), ap->a_uio, ap->a_cred, ap->a_eofflagp);
E 2
}

D 2
lofs_readlink (ap)
E 2
I 2
null_readlink (ap)
E 2
	struct vop_readlink_args *ap;
{
	USES_VOP_READLINK;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_readlink(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_readlink(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 2
#endif

D 2
	return VOP_READLINK(LOFSVP(ap->a_vp), ap->a_uio, ap->a_cred);
E 2
I 2
	return VOP_READLINK(NULLTOLOWERVP(ap->a_vp), ap->a_uio, ap->a_cred);
E 2
}

/*
 * Anyone's guess...
 */
D 2
lofs_abortop (ap)
E 2
I 2
null_abortop (ap)
E 2
	struct vop_abortop_args *ap;
{
	USES_VOP_ABORTOP;
	int error;

	PUSHREF(xdvp, ap->a_dvp);

	error = VOP_ABORTOP(ap->a_dvp, ap->a_cnp);

	POP(xdvp, ap->a_dvp);

	return (error);
}

E 3
I 3
int
E 3
D 2
lofs_inactive (ap)
E 2
I 2
D 8
null_inactive (ap)
E 2
	struct vop_inactive_args *ap;
E 8
I 8
null_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 13
		struct proc *a_p;
E 13
	} */ *ap;
E 8
{
D 3
	USES_VOP_INACTIVE;
D 2
	struct vnode *targetvp = LOFSVP(ap->a_vp);
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_inactive(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 2
I 2
	struct vnode *targetvp = NULLTOLOWERVP(ap->a_vp);
E 3
D 5
#ifdef NULLFS_DIAGNOSTIC
D 3
	printf("null_inactive(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 3
I 3
D 4
	printf("null_inactive(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 4
I 4
	printf("null_inactive(ap->a_vp = %x->%x)\n", ap->a_vp, NULLVPTOLOWERVP(ap->a_vp));
E 5
I 5
D 7
#ifdef AVOID_CACHING
	struct vnode *vp = ap->a_vp;
	struct null_node *xp = VTONULL(vp);
	struct vnode *lowervp = xp->null_lowervp;

	xp->null_lowervp = NULL;
	remque(xp);
	FREE(vp->v_data, M_TEMP);
	vp->v_data = NULL;
	vp->v_type = VBAD;   /* The node is clean (no reclaim needed). */
	vrele (lowervp);
#else
D 6
#ifdef DIAGNOSTIC
	if (VOP_ISLOCKED(ap->a_vp)) {
		panic ("null_inactive: inactive node is locked.");
E 6
I 6
#ifdef DIAGNOSTIC  /* NEEDSWORK: goes away */
	if (VOP_ISLOCKED(NULLVPTOLOWERVP(ap->a_vp))) {
		panic ("null_inactive: inactive's lowervp is locked.");
E 6
	};
E 5
E 4
E 3
E 2
#endif
E 7
D 3

#ifdef DIAGNOSTIC
	{ extern int prtactive;
	if (prtactive && ap->a_vp->v_usecount != 0)
D 2
		vprint("lofs_inactive: pushing active", ap->a_vp);
E 2
I 2
		vprint("null_inactive: pushing active", ap->a_vp);
E 2
	}
#endif

	if (targetvp) {
		vrele(targetvp);
D 2
		LOFSP(ap->a_vp)->a_lofsvp = 0;
E 2
I 2
		VTONULLNODE(ap->a_vp)->null_lowervp = 0;
E 2
	}
E 3
I 3
	/*
I 6
D 7
	 * Remember we're inactive so we 
	 * don't send locks through.
	 */
	VTONULL(ap->a_vp)->null_isinactive = 1;
	/*
E 7
E 6
	 * Do nothing (and _don't_ bypass).
	 * Wait to vrele lowervp until reclaim,
	 * so that until then our null_node is in the
	 * cache and reusable.
	 *
	 * NEEDSWORK: Someday, consider inactive'ing
	 * the lowervp and then trying to reactivate it
I 7
	 * with capabilities (v_id)
E 7
	 * like they do in the name lookup cache code.
	 * That's too much work for now.
	 */
I 13
	VOP_UNLOCK(ap->a_vp, 0, ap->a_p);
E 13
D 8
	return 0;
E 8
I 8
	return (0);
E 8
I 5
D 7
#endif
E 7
E 5
E 3
}

I 5
int
E 5
D 2
lofs_reclaim (ap)
E 2
I 2
D 8
null_reclaim (ap)
E 2
	struct vop_reclaim_args *ap;
E 8
I 8
null_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
I 12
		struct proc *a_p;
E 12
	} */ *ap;
E 8
{
D 4
	USES_VOP_RECLAIM;
E 4
D 5
	struct vnode *targetvp;
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_reclaim(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
D 4
	printf("null_reclaim(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 4
I 4
	printf("null_reclaim(ap->a_vp = %x->%x)\n", ap->a_vp, NULLVPTOLOWERVP(ap->a_vp));
E 5
I 5
	struct vnode *vp = ap->a_vp;
	struct null_node *xp = VTONULL(vp);
	struct vnode *lowervp = xp->null_lowervp;

D 7
#ifdef AVOID_CACHING
	return 0;
#else
E 7
	/*
D 7
	 * Note: at this point, vp->v_op == dead_vnodeop_p,
E 7
I 7
	 * Note: in vop_reclaim, vp->v_op == dead_vnodeop_p,
E 7
	 * so we can't call VOPs on ourself.
	 */
	/* After this assignment, this node will not be re-used. */
D 7
#ifdef DIAGNOSTIC
D 6
	if (lowervp->v_usecount == 1 && ISLOCKED(lowervp)) {
E 6
I 6
	/* XXX - this is only a bug if it's locked by ourselves */
	if (lowervp->v_usecount == 1 && VOP_ISLOCKED(lowervp)) {
E 6
		panic("null_reclaim: lowervp is locked but must go away.");
	};
E 5
E 4
E 2
#endif
E 7
D 2
	remque(LOFSP(ap->a_vp));
	targetvp = LOFSVP(ap->a_vp);
E 2
I 2
D 3
	remque(VTONULLNODE(ap->a_vp));
	targetvp = NULLTOLOWERVP(ap->a_vp);
E 2
	if (targetvp) {
		printf("lofs: delayed vrele of %x\n", targetvp);
		vrele(targetvp);	/* XXX should never happen */
	}
E 3
I 3
D 4
	remque(VTONULLNODE(ap->a_vp));   /* NEEDSWORK: What? */
	vrele (NULLTOLOWERVP(ap->a_vp));   /* release lower layer */
E 4
I 4
D 5
	remque(VTONULL(ap->a_vp));	     /* NEEDSWORK: What? */
	vrele (NULLVPTOLOWERVP(ap->a_vp));   /* release lower layer */
E 4
E 3
	FREE(ap->a_vp->v_data, M_TEMP);
	ap->a_vp->v_data = 0;
	return (0);
E 5
I 5
	xp->null_lowervp = NULL;
D 10
	remque(xp);
E 10
I 10
	LIST_REMOVE(xp, null_hash);
E 10
	FREE(vp->v_data, M_TEMP);
	vp->v_data = NULL;
	vrele (lowervp);
D 8
	return 0;
E 8
I 8
	return (0);
E 8
D 7
#endif
E 7
E 5
}

I 7
D 12

E 12
E 7
I 5
int
E 5
D 2
lofs_lock (ap)
E 2
I 2
D 3
null_lock (ap)
E 2
	struct vop_lock_args *ap;
{
	USES_VOP_LOCK;
	int error;
D 2
	struct vnode *targetvp = LOFSVP(ap->a_vp);
E 2
I 2
	struct vnode *targetvp = NULLTOLOWERVP(ap->a_vp);
E 2

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_lock(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
	/*vprint("lofs_lock ap->a_vp", ap->a_vp);
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_lock(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
	/*vprint("null_lock ap->a_vp", ap->a_vp);
E 2
	if (targetvp)
D 2
		vprint("lofs_lock ->ap->a_vp", targetvp);
E 2
I 2
		vprint("null_lock ->ap->a_vp", targetvp);
E 2
	else
D 2
		printf("lofs_lock ->ap->a_vp = NIL\n");*/
E 2
I 2
		printf("null_lock ->ap->a_vp = NIL\n");*/
E 2
#endif

	if (targetvp) {
		error = VOP_LOCK(targetvp);
		if (error)
			return (error);
	}

	return (0);
}

D 2
lofs_unlock (ap)
E 2
I 2
null_unlock (ap)
E 2
	struct vop_unlock_args *ap;
{
	USES_VOP_UNLOCK;
D 2
	struct vnode *targetvp = LOFSVP(ap->a_vp);
E 2
I 2
	struct vnode *targetvp = NULLTOLOWERVP(ap->a_vp);
E 2

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_unlock(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
	printf("null_unlock(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 2
#endif

	if (targetvp)
		return (VOP_UNLOCK(targetvp));
	return (0);
}

E 3
D 2
lofs_bmap (ap)
E 2
I 2
D 7
null_bmap (ap)
E 2
	struct vop_bmap_args *ap;
E 7
I 7
D 8
null_print (ap)
	struct vop_print_args *ap;
E 8
I 8
null_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 8
E 7
{
D 4
	USES_VOP_BMAP;
E 4
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_bmap(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
D 7
#ifdef NULLFS_DIAGNOSTIC
D 4
	printf("null_bmap(ap->a_vp = %x->%x)\n", ap->a_vp, NULLTOLOWERVP(ap->a_vp));
E 4
I 4
	printf("null_bmap(ap->a_vp = %x->%x)\n", ap->a_vp, NULLVPTOLOWERVP(ap->a_vp));
E 4
E 2
#endif

D 2
	return VOP_BMAP(LOFSVP(ap->a_vp), ap->a_bn, ap->a_vpp, ap->a_bnp);
E 2
I 2
D 4
	return VOP_BMAP(NULLTOLOWERVP(ap->a_vp), ap->a_bn, ap->a_vpp, ap->a_bnp);
E 4
I 4
	return VOP_BMAP(NULLVPTOLOWERVP(ap->a_vp), ap->a_bn, ap->a_vpp, ap->a_bnp);
E 7
I 7
	register struct vnode *vp = ap->a_vp;
	printf ("\ttag VT_NULLFS, vp=%x, lowervp=%x\n", vp, NULLVPTOLOWERVP(vp));
D 8
	return 0;
E 8
I 8
	return (0);
E 8
E 7
E 4
E 2
}

I 7
D 12

E 12
/*
 * XXX - vop_strategy must be hand coded because it has no
 * vnode in its arguments.
 * This goes away with a merged VM/buffer cache.
 */
E 7
I 5
int
E 5
D 2
lofs_strategy (ap)
E 2
I 2
D 8
null_strategy (ap)
E 2
	struct vop_strategy_args *ap;
E 8
I 8
null_strategy(ap)
	struct vop_strategy_args /* {
		struct buf *a_bp;
	} */ *ap;
E 8
{
I 7
	struct buf *bp = ap->a_bp;
E 7
D 4
	USES_VOP_STRATEGY;
E 4
	int error;
I 3
	struct vnode *savedvp;
E 3

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_strategy(vp = %x->%x)\n", ap->a_bp->b_vp, LOFSVP(ap->a_bp->b_vp));
E 2
I 2
D 7
#ifdef NULLFS_DIAGNOSTIC
D 4
	printf("null_strategy(vp = %x->%x)\n", ap->a_bp->b_vp, NULLTOLOWERVP(ap->a_bp->b_vp));
E 4
I 4
	printf("null_strategy(vp = %x->%x)\n", ap->a_bp->b_vp, NULLVPTOLOWERVP(ap->a_bp->b_vp));
E 4
E 2
#endif
E 7
I 7
	savedvp = bp->b_vp;
	bp->b_vp = NULLVPTOLOWERVP(bp->b_vp);
E 7

D 3
	PUSHREF(vp, ap->a_bp->b_vp);
E 3
I 3
D 7
	savedvp = ap->a_bp->b_vp;
E 7
I 7
	error = VOP_STRATEGY(bp);
E 7
E 3

D 7
	error = VOP_STRATEGY(ap->a_bp);
E 7
I 7
	bp->b_vp = savedvp;
E 7

D 3
	POP(vp, ap->a_bp->b_vp);
E 3
I 3
D 7
	ap->a_bp->b_vp = savedvp;
E 3

E 7
D 3
	return (error);
E 3
I 3
D 8
	return error;
E 8
I 8
	return (error);
E 8
E 3
}

I 3
D 12

E 12
I 7
/*
 * XXX - like vop_strategy, vop_bwrite must be hand coded because it has no
 * vnode in its arguments.
 * This goes away with a merged VM/buffer cache.
 */
E 7
int
E 3
D 2
lofs_print (ap)
E 2
I 2
D 7
null_print (ap)
E 2
	struct vop_print_args *ap;
E 7
I 7
D 8
null_bwrite (ap)
	struct vop_bwrite_args *ap;
E 8
I 8
null_bwrite(ap)
	struct vop_bwrite_args /* {
		struct buf *a_bp;
	} */ *ap;
E 8
E 7
{
D 3
	USES_VOP_PRINT;
D 2
	struct vnode *targetvp = LOFSVP(ap->a_vp);
E 2
I 2
	struct vnode *targetvp = NULLTOLOWERVP(ap->a_vp);
E 2
	printf("tag VT_LOFS ref ");
	if (targetvp)
		return (VOP_PRINT(targetvp));
	printf("NULLVP\n");
	return (0);
E 3
I 3
D 7
	register struct vnode *vp = ap->a_vp;
D 4
	printf ("tag VT_NULLFS, vp=%x, lowervp=%x\n", vp, NULLTOLOWERVP(vp));
E 4
I 4
D 5
	printf ("tag VT_NULLFS, vp=%x, lowervp=%x\n", vp, NULLVPTOLOWERVP(vp));
E 5
I 5
	printf ("\ttag VT_NULLFS, vp=%x, lowervp=%x\n", vp, NULLVPTOLOWERVP(vp));
E 5
E 4
	return 0;
E 3
}
E 7
I 7
	struct buf *bp = ap->a_bp;
	int error;
	struct vnode *savedvp;
E 7

I 6
D 7
#if 0
int
null_lock(ap)
	struct vop_lock_args *ap;
{
	if (VTONULL(ap->a_vp)->null_isinactive)
		return 0;
	else return null_bypass(ap);
}
E 7
I 7
	savedvp = bp->b_vp;
	bp->b_vp = NULLVPTOLOWERVP(bp->b_vp);
E 7
E 6
D 2
lofs_islocked (ap)
E 2
I 2
D 3
null_islocked (ap)
E 2
	struct vop_islocked_args *ap;
{
	USES_VOP_ISLOCKED;
D 2
	struct vnode *targetvp = LOFSVP(ap->a_vp);
E 2
I 2
	struct vnode *targetvp = NULLTOLOWERVP(ap->a_vp);
E 2
	if (targetvp)
		return (VOP_ISLOCKED(targetvp));
	return (0);
}
E 3

I 6
D 7
int
null_unlock(ap)
	struct vop_lock_args *ap;
{
	if (VTONULL(ap->a_vp)->null_isinactive)
		return 0;
	else return null_bypass(ap);
E 7
I 7
	error = VOP_BWRITE(bp);

	bp->b_vp = savedvp;

D 8
	return error;
E 8
I 8
	return (error);
E 8
E 7
}
D 7
#endif
E 7
D 8

E 8
I 7

E 7
E 6
D 2
lofs_advlock (ap)
E 2
I 2
D 3
null_advlock (ap)
E 2
	struct vop_advlock_args *ap;
{
	USES_VOP_ADVLOCK;
D 2
	return VOP_ADVLOCK(LOFSVP(ap->a_vp), ap->a_id, ap->a_op, ap->a_fl, ap->a_flags);
E 2
I 2
	return VOP_ADVLOCK(NULLTOLOWERVP(ap->a_vp), ap->a_id, ap->a_op, ap->a_fl, ap->a_flags);
E 2
}

E 3
/*
D 3
 * LOFS directory offset lookup.
 * Currently unsupported.
E 3
I 3
 * Global vfs data structures
E 3
 */
D 2
lofs_blkatoff (ap)
E 2
I 2
D 3
null_blkatoff (ap)
E 2
	struct vop_blkatoff_args *ap;
{

	return (EOPNOTSUPP);
}

E 3
D 7
/*
D 3
 * LOFS flat namespace lookup.
 * Currently unsupported.
E 3
I 3
 * NEEDSWORK: strategy,bmap are hand coded currently.  They should
 * go away with a merged buffer/block cache.
 *
E 3
 */
E 7
D 2
lofs_vget (ap)
E 2
I 2
D 3
null_vget (ap)
E 2
	struct vop_vget_args *ap;
{
E 3
I 3
int (**null_vnodeop_p)();
D 4
struct vnodeopv_entry_desc lofs_vnodeop_entries[] = {
E 4
I 4
struct vnodeopv_entry_desc null_vnodeop_entries[] = {
E 4
	{ &vop_default_desc, null_bypass },
E 3

I 13
	{ &vop_lookup_desc, null_lookup },
I 14
	{ &vop_setattr_desc, null_setattr },
E 14
E 13
D 3
	return (EOPNOTSUPP);
}
E 3
I 3
	{ &vop_getattr_desc, null_getattr },
I 14
	{ &vop_access_desc, null_access },
E 14
I 12
	{ &vop_lock_desc, null_lock },
I 13
	{ &vop_unlock_desc, null_unlock },
E 13
E 12
	{ &vop_inactive_desc, null_inactive },
	{ &vop_reclaim_desc, null_reclaim },
	{ &vop_print_desc, null_print },
I 6
D 7
#if 0
	{ &vop_lock_desc, null_lock },
	{ &vop_unlock_desc, null_unlock },
#endif
E 7
E 6
E 3

D 3
/*
 * LOFS flat namespace allocation.
 * Currently unsupported.
 */
D 2
lofs_valloc (ap)
E 2
I 2
null_valloc (ap)
E 2
	struct vop_valloc_args *ap;
{
E 3
I 3
D 7
	{ &vop_bmap_desc, null_bmap },
E 7
	{ &vop_strategy_desc, null_strategy },
I 7
	{ &vop_bwrite_desc, null_bwrite },
E 7
E 3

D 3
	return (EOPNOTSUPP);
}

/*
 * LOFS flat namespace free.
 * Currently unsupported.
 */
/*void*/
D 2
lofs_vfree (ap)
E 2
I 2
null_vfree (ap)
E 2
	struct vop_vfree_args *ap;
{

	return;
}

/*
 * LOFS file truncation.
 */
D 2
lofs_truncate (ap)
E 2
I 2
null_truncate (ap)
E 2
	struct vop_truncate_args *ap;
{

D 2
	/* Use lofs_setattr */
	printf("lofs_truncate: need to implement!!");
E 2
I 2
	/* Use null_setattr */
	printf("null_truncate: need to implement!!");
E 2
	return (EOPNOTSUPP);
}

/*
 * LOFS update.
 */
D 2
lofs_update (ap)
E 2
I 2
null_update (ap)
E 2
	struct vop_update_args *ap;
{

D 2
	/* Use lofs_setattr */
	printf("lofs_update: need to implement!!");
E 2
I 2
	/* Use null_setattr */
	printf("null_update: need to implement!!");
E 2
	return (EOPNOTSUPP);
}

/*
 * LOFS bwrite
 */
D 2
lofs_bwrite (ap)
E 2
I 2
null_bwrite (ap)
E 2
	struct vop_bwrite_args *ap;
{
	return (EOPNOTSUPP);
}

/*
 * Global vfs data structures for ufs
 */
D 2
int (**lofs_vnodeop_p)();
E 2
I 2
int (**null_vnodeop_p)();
E 2
struct vnodeopv_entry_desc lofs_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
D 2
	{ &vop_lookup_desc, lofs_lookup },		/* lookup */
	{ &vop_create_desc, lofs_create },		/* create */
	{ &vop_mknod_desc, lofs_mknod },		/* mknod */
	{ &vop_open_desc, lofs_open },		/* open */
	{ &vop_close_desc, lofs_close },		/* close */
	{ &vop_access_desc, lofs_access },		/* access */
	{ &vop_getattr_desc, lofs_getattr },		/* getattr */
	{ &vop_setattr_desc, lofs_setattr },		/* setattr */
	{ &vop_read_desc, lofs_read },		/* read */
	{ &vop_write_desc, lofs_write },		/* write */
	{ &vop_ioctl_desc, lofs_ioctl },		/* ioctl */
	{ &vop_select_desc, lofs_select },		/* select */
	{ &vop_mmap_desc, lofs_mmap },		/* mmap */
	{ &vop_fsync_desc, lofs_fsync },		/* fsync */
	{ &vop_seek_desc, lofs_seek },		/* seek */
	{ &vop_remove_desc, lofs_remove },		/* remove */
	{ &vop_link_desc, lofs_link },		/* link */
	{ &vop_rename_desc, lofs_rename },		/* rename */
	{ &vop_mkdir_desc, lofs_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, lofs_rmdir },		/* rmdir */
	{ &vop_symlink_desc, lofs_symlink },		/* symlink */
	{ &vop_readdir_desc, lofs_readdir },		/* readdir */
	{ &vop_readlink_desc, lofs_readlink },		/* readlink */
	{ &vop_abortop_desc, lofs_abortop },		/* abortop */
	{ &vop_inactive_desc, lofs_inactive },		/* inactive */
	{ &vop_reclaim_desc, lofs_reclaim },		/* reclaim */
	{ &vop_lock_desc, lofs_lock },		/* lock */
	{ &vop_unlock_desc, lofs_unlock },		/* unlock */
	{ &vop_bmap_desc, lofs_bmap },		/* bmap */
	{ &vop_strategy_desc, lofs_strategy },		/* strategy */
	{ &vop_print_desc, lofs_print },		/* print */
	{ &vop_islocked_desc, lofs_islocked },		/* islocked */
	{ &vop_advlock_desc, lofs_advlock },		/* advlock */
	{ &vop_blkatoff_desc, lofs_blkatoff },		/* blkatoff */
	{ &vop_vget_desc, lofs_vget },		/* vget */
	{ &vop_valloc_desc, lofs_valloc },		/* valloc */
	{ &vop_vfree_desc, lofs_vfree },		/* vfree */
	{ &vop_truncate_desc, lofs_truncate },		/* truncate */
	{ &vop_update_desc, lofs_update },		/* update */
	{ &vop_bwrite_desc, lofs_bwrite },		/* bwrite */
E 2
I 2
	{ &vop_lookup_desc, null_lookup },		/* lookup */
	{ &vop_create_desc, null_create },		/* create */
	{ &vop_mknod_desc, null_mknod },		/* mknod */
	{ &vop_open_desc, null_open },		/* open */
	{ &vop_close_desc, null_close },		/* close */
	{ &vop_access_desc, null_access },		/* access */
	{ &vop_getattr_desc, null_getattr },		/* getattr */
	{ &vop_setattr_desc, null_setattr },		/* setattr */
	{ &vop_read_desc, null_read },		/* read */
	{ &vop_write_desc, null_write },		/* write */
	{ &vop_ioctl_desc, null_ioctl },		/* ioctl */
	{ &vop_select_desc, null_select },		/* select */
	{ &vop_mmap_desc, null_mmap },		/* mmap */
	{ &vop_fsync_desc, null_fsync },		/* fsync */
	{ &vop_seek_desc, null_seek },		/* seek */
	{ &vop_remove_desc, null_remove },		/* remove */
	{ &vop_link_desc, null_link },		/* link */
	{ &vop_rename_desc, null_rename },		/* rename */
	{ &vop_mkdir_desc, null_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, null_rmdir },		/* rmdir */
	{ &vop_symlink_desc, null_symlink },		/* symlink */
	{ &vop_readdir_desc, null_readdir },		/* readdir */
	{ &vop_readlink_desc, null_readlink },		/* readlink */
	{ &vop_abortop_desc, null_abortop },		/* abortop */
	{ &vop_inactive_desc, null_inactive },		/* inactive */
	{ &vop_reclaim_desc, null_reclaim },		/* reclaim */
	{ &vop_lock_desc, null_lock },		/* lock */
	{ &vop_unlock_desc, null_unlock },		/* unlock */
	{ &vop_bmap_desc, null_bmap },		/* bmap */
	{ &vop_strategy_desc, null_strategy },		/* strategy */
	{ &vop_print_desc, null_print },		/* print */
	{ &vop_islocked_desc, null_islocked },		/* islocked */
	{ &vop_advlock_desc, null_advlock },		/* advlock */
	{ &vop_blkatoff_desc, null_blkatoff },		/* blkatoff */
	{ &vop_vget_desc, null_vget },		/* vget */
	{ &vop_valloc_desc, null_valloc },		/* valloc */
	{ &vop_vfree_desc, null_vfree },		/* vfree */
	{ &vop_truncate_desc, null_truncate },		/* truncate */
	{ &vop_update_desc, null_update },		/* update */
	{ &vop_bwrite_desc, null_bwrite },		/* bwrite */
E 3
E 2
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
D 4
struct vnodeopv_desc lofs_vnodeop_opv_desc =
D 2
	{ &lofs_vnodeop_p, lofs_vnodeop_entries };
E 2
I 2
	{ &null_vnodeop_p, lofs_vnodeop_entries };
E 4
I 4
struct vnodeopv_desc null_vnodeop_opv_desc =
	{ &null_vnodeop_p, null_vnodeop_entries };
E 4
E 2
E 1
