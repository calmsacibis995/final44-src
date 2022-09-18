h04411
s 00033/00016/00474
d D 8.6 95/05/22 23:25:42 mckusick 12 11
c add proper locking
e
s 00028/00000/00462
d D 8.5 95/05/14 00:46:44 mckusick 11 10
c add umap_lock to check VXLOCK and clear interlock before bypassing
e
s 00001/00001/00461
d D 8.4 94/08/20 16:03:00 mckusick 10 9
c update to use LIST macros for hash table
e
s 00054/00051/00408
d D 8.3 94/01/05 01:02:25 pendry 9 8
c handle wide uid/gid.  lint, KNF
e
s 00001/00003/00458
d D 8.2 94/01/04 21:44:38 bostic 8 7
c lint
e
s 00002/00002/00459
d D 8.1 93/06/10 23:47:33 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00461
d D 7.1 92/07/23 16:16:13 mckusick 6 5
c update to rev 7
e
s 00008/00005/00453
d D 1.4 92/07/23 16:15:32 heideman 5 4
c Fix irregularities in rename
e
s 00047/00024/00411
d D 1.3 92/07/12 16:30:29 mckusick 4 2
c move to rev 7; new include location; syntax niggles
e
s 00046/00021/00414
d R 7.1 92/07/12 15:28:52 mckusick 3 2
c move to rev 7; new include location; syntax niggles
e
s 00158/00155/00277
d D 1.2 92/07/11 15:29:11 heideman 2 1
c Porting from null layer
e
s 00432/00000/00000
d D 1.1 92/07/11 09:21:16 heideman 1 0
c date and time created 92/07/11 09:21:16 by heideman
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1992 The Regents of the University of California
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 2
 * This code is derived from the null layer of
 * John Heidemann from the UCLA Ficus project and
 * Jan-Simon Pendry's loopback file system.
E 2
I 2
 * This code is derived from software donated to Berkeley by
 * the UCLA Ficus project.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 4
 *
D 2
 * Ancestors:
 *	@(#)lofs_vnops.c	1.2 (Berkeley) 6/18/92
 *	$Id: lofs_vnops.c,v 1.11 1992/05/30 10:05:43 jsp Exp jsp $
 *	...and...
 *	@(#)umap_vnodeops.c 1.20 92/07/07 UCLA Ficus project
E 2
I 2
 * @(#)umap_vnops.c       1.5 (Berkeley) 7/10/92
E 4
E 2
 */

/*
 * Umap Layer
D 2
 *
 * The umap layer duplicates a portion of the file system
 * name space under a new name.  In this respect, it is
 * similar to the loopback file system.  It differs from
 * the loopback fs in two respects:  it is implemented using
 * a bypass operation, and it's "umap-node"s stack above
 * all lower-layer vnodes, not just over directory vnodes.
 *
 * The umap layer is the minimum file system layer,
 * simply bypassing all possible operations to the lower layer
 * for processing there.  All but vop_getattr, _inactive, _reclaim,
 * and _print are bypassed.
 *
 * Vop_getattr is not bypassed so that we can change the fsid being
 * returned.  Vop_{inactive,reclaim} are bypassed so that
 * they can handle freeing umap-layer specific data.
 * Vop_print is not bypassed for debugging.
 *
 *
 * INVOKING OPERATIONS ON LOWER LAYERS
 *
 * NEEDSWORK: Describe methods to invoke operations on the lower layer
 * (bypass vs. VOP).
 *
 *
 * CREATING NEW FILESYSTEM LAYERS
 *
 * One of the easiest ways to construct new file system layers is to make
 * a copy of the umap layer, rename all files and variables, and
 * then begin modifing the copy.  Sed can be used to easily rename
 * all variables.
 *
E 2
 */

#include <sys/param.h>
#include <sys/systm.h>
D 2
#include <sys/user.h>
#include <sys/proc.h>
E 2
#include <sys/time.h>
#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
#include <sys/buf.h>
D 4
#include <umapfs/umap.h>
E 4
I 4
#include <miscfs/umapfs/umap.h>
E 4


int umap_bug_bypass = 0;   /* for debugging: enables bypass printf'ing */

/*
 * This is the 10-Apr-92 bypass routine.
D 2
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
E 2
I 2
 * See null_vnops.c:null_bypass for more details.
E 2
 */ 
int
umap_bypass(ap)
D 4
	struct vop_generic_args *ap;
E 4
I 4
	struct vop_generic_args /* {
		struct vnodeop_desc *a_desc;
		<other random data follows, presumably>
	} */ *ap;
E 4
{
	extern int (**umap_vnodeop_p)();  /* not extern, really "forward" */
D 8
	int *mapdata, nentries ;
	int *gmapdata, gnentries ;
D 2
	struct ucred **credpp,*credp, *savecredp, *saveucredp ;
E 2
I 2
	struct ucred **credpp,*credp, *savecredp, *saveucredp, *savecompcredp ;
E 8
I 8
D 9
	struct ucred **credpp,*credp, *savecredp, *savecompcredp;
E 8
	struct ucred *compcredp;
E 2
	register struct vnode **this_vp_p;
E 9
I 9
	struct ucred **credpp = 0, *credp = 0;
	struct ucred *savecredp, *savecompcredp = 0;
	struct ucred *compcredp = 0;
	struct vnode **this_vp_p;
E 9
	int error;
D 2
	struct vnode *old_vps[VDESC_MAX_VPS];
E 2
I 2
D 9
	struct vnode *old_vps[VDESC_MAX_VPS], *vp1;
E 9
I 9
	struct vnode *old_vps[VDESC_MAX_VPS];
	struct vnode *vp1 = 0;
E 9
E 2
	struct vnode **vps_p[VDESC_MAX_VPS];
	struct vnode ***vppp;
	struct vnodeop_desc *descp = ap->a_desc;
	int reles, i;
I 2
D 9
	struct componentname **compnamepp;
E 9
I 9
	struct componentname **compnamepp = 0;
E 9
E 2

	if (umap_bug_bypass)
		printf ("umap_bypass: %s\n", descp->vdesc_name);

#ifdef SAFETY
	/*
	 * We require at least one vp.
	 */
D 2
	if (descp->vdesc_vp_offsets==UMAP ||
	    descp->vdesc_vp_offsets[0]==VDESC_NO_OFFSET)
E 2
I 2
	if (descp->vdesc_vp_offsets == NULL ||
	    descp->vdesc_vp_offsets[0] == VDESC_NO_OFFSET)
E 2
		panic ("umap_bypass: no vp's in map.\n");
#endif

	/*
	 * Map the vnodes going in.
	 * Later, we'll invoke the operation based on
	 * the first mapped vnode's operation vector.
	 */
	reles = descp->vdesc_flags;
D 2
	for (i=0; i<VDESC_MAX_VPS; reles>>=1, i++) {
		if (descp->vdesc_vp_offsets[i]==VDESC_NO_OFFSET)
E 2
I 2
	for (i = 0; i < VDESC_MAX_VPS; reles >>= 1, i++) {
		if (descp->vdesc_vp_offsets[i] == VDESC_NO_OFFSET)
E 2
			break;   /* bail out at end of list */
		vps_p[i] = this_vp_p = 
D 9
			VOPARG_OFFSETTO(struct vnode**,descp->vdesc_vp_offsets[i],ap);
E 9
I 9
			VOPARG_OFFSETTO(struct vnode**, descp->vdesc_vp_offsets[i], ap);
E 9

D 9
		if (i == 0)
		{
E 9
I 9
		if (i == 0) {
E 9
			vp1 = *vps_p[0];
		}

		/*
		 * We're not guaranteed that any but the first vnode
		 * are of our type.  Check for and don't map any
D 2
		 * that aren't.
E 2
I 2
		 * that aren't.  (Must map first vp or vclean fails.)
E 2
		 */

D 2
		if ((*this_vp_p)->v_op != umap_vnodeop_p) {
			old_vps[i] = UMAP;
E 2
I 2
		if (i && (*this_vp_p)->v_op != umap_vnodeop_p) {
			old_vps[i] = NULL;
E 2
		} else {
			old_vps[i] = *this_vp_p;
			*(vps_p[i]) = UMAPVPTOLOWERVP(*this_vp_p);
			if (reles & 1)
				VREF(*this_vp_p);
D 2
		};
E 2
I 2
		}
E 2
			
D 2
	};
E 2
I 2
	}
E 2

D 2
	/* Doctor the credentials.  (That's the purpose of this layer.) */
E 2
I 2
	/*
	 * Fix the credentials.  (That's the purpose of this layer.)
	 */
E 2

	if (descp->vdesc_cred_offset != VDESC_NO_OFFSET) {

		credpp = VOPARG_OFFSETTO(struct ucred**, 
		    descp->vdesc_cred_offset, ap);

		/* Save old values */

		savecredp = (*credpp);
D 2
		saveucredp = u.u_cred;
		(*credpp) = u.u_cred = crdup(savecredp);
E 2
I 2
		(*credpp) = crdup(savecredp);
E 2
		credp = *credpp;

D 9
		if (umap_bug_bypass && credp->cr_uid != 0 )
E 9
I 9
		if (umap_bug_bypass && credp->cr_uid != 0)
E 9
			printf("umap_bypass: user was %d, group %d\n", 
D 9
			    credp->cr_uid,credp->cr_gid);
E 9
I 9
			    credp->cr_uid, credp->cr_gid);
E 9

D 2
		nentries =  MOUNTTOUMAPMOUNT(vp1->v_vfsp)->info_nentries;
		mapdata =  &(MOUNTTOUMAPMOUNT(vp1->v_vfsp)->info_mapdata[0][0]);
		gnentries =  MOUNTTOUMAPMOUNT(vp1->v_vfsp)->info_gnentries;
		gmapdata =  &(MOUNTTOUMAPMOUNT(vp1->v_vfsp)->info_gmapdata[0][0]);

		if (umap_bug_bypass && credp->cr_uid != 0 )
			printf("nentries = %d, gnentries = %d\n", nentries, 
			    gnentries);

E 2
		/* Map all ids in the credential structure. */

D 2
		umap_mapids(credp,mapdata,nentries,gmapdata,gnentries);
E 2
I 2
D 9
		umap_mapids(vp1->v_mount,credp);
E 9
I 9
		umap_mapids(vp1->v_mount, credp);
E 9
E 2

D 9
		if (umap_bug_bypass && credp->cr_uid != 0 )
E 9
I 9
		if (umap_bug_bypass && credp->cr_uid != 0)
E 9
			printf("umap_bypass: user now %d, group %d\n", 
D 9
			    credp->cr_uid,credp->cr_gid);
E 9
I 9
			    credp->cr_uid, credp->cr_gid);
E 9
	}

I 2
	/* BSD often keeps a credential in the componentname structure
	 * for speed.  If there is one, it better get mapped, too. 
	 */

	if (descp->vdesc_componentname_offset != VDESC_NO_OFFSET) {

		compnamepp = VOPARG_OFFSETTO(struct componentname**, 
		    descp->vdesc_componentname_offset, ap);

		compcredp = (*compnamepp)->cn_cred;
		savecompcredp = compcredp;
		compcredp = (*compnamepp)->cn_cred = crdup(savecompcredp);

D 9
		if (umap_bug_bypass && compcredp->cr_uid != 0 )
E 9
I 9
		if (umap_bug_bypass && compcredp->cr_uid != 0)
E 9
			printf("umap_bypass: component credit user was %d, group %d\n", 
D 9
			    compcredp->cr_uid,compcredp->cr_gid);
E 9
I 9
			    compcredp->cr_uid, compcredp->cr_gid);
E 9

		/* Map all ids in the credential structure. */

D 9
		umap_mapids(vp1->v_mount,compcredp);
E 9
I 9
		umap_mapids(vp1->v_mount, compcredp);
E 9

D 9
		if (umap_bug_bypass && compcredp->cr_uid != 0 )
E 9
I 9
		if (umap_bug_bypass && compcredp->cr_uid != 0)
E 9
			printf("umap_bypass: component credit user now %d, group %d\n", 
D 9
			    compcredp->cr_uid,compcredp->cr_gid);
E 9
I 9
			    compcredp->cr_uid, compcredp->cr_gid);
E 9
	}

E 2
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
D 2
	for (i=0; i<VDESC_MAX_VPS; reles>>=1, i++) {
		if (descp->vdesc_vp_offsets[i]==VDESC_NO_OFFSET)
E 2
I 2
	for (i = 0; i < VDESC_MAX_VPS; reles >>= 1, i++) {
		if (descp->vdesc_vp_offsets[i] == VDESC_NO_OFFSET)
E 2
			break;   /* bail out at end of list */
		if (old_vps[i]) {
			*(vps_p[i]) = old_vps[i];
			if (reles & 1)
				vrele(*(vps_p[i]));
		};
	};

	/*
	 * Map the possible out-going vpp
	 * (Assumes that the lower layer always returns
	 * a VREF'ed vpp unless it gets an error.)
	 */
	if (descp->vdesc_vpp_offset != VDESC_NO_OFFSET &&
	    !(descp->vdesc_flags & VDESC_NOMAP_VPP) &&
	    !error) {
D 2
		/*
		 * XXX - even though symlink has a vpp arg,
		 * it doesn't return a VREF'ed vpp in that
		 * field.  The vpp arg should become a vp
		 * arg.
		 */
		if (descp == VDESC(vop_symlink)) {
#ifdef UMAPFS_DIAGNOSTIC
			printf("umap_bypass (symlink), lowervp->usecount = %d\n", (**vppp)->v_usecount);
#endif
			return (error);
		};
		vppp=VOPARG_OFFSETTO(struct vnode***,
E 2
I 2
		if (descp->vdesc_flags & VDESC_VPP_WILLRELE)
			goto out;
		vppp = VOPARG_OFFSETTO(struct vnode***,
E 2
D 9
				 descp->vdesc_vpp_offset,ap);
E 9
I 9
				 descp->vdesc_vpp_offset, ap);
E 9
		error = umap_node_create(old_vps[0]->v_mount, **vppp, *vppp);
	};

I 2
 out:
E 2
	/* 
	 * Free duplicate cred structure and restore old one.
	 */
	if (descp->vdesc_cred_offset != VDESC_NO_OFFSET) {
D 9
		if (umap_bug_bypass && credp->cr_uid != 0 )
		printf("umap_bypass: returning-user was %d\n", credp->cr_uid);
E 9
I 9
		if (umap_bug_bypass && credp && credp->cr_uid != 0)
			printf("umap_bypass: returning-user was %d\n",
					credp->cr_uid);
E 9

		crfree(credp);
		(*credpp) = savecredp;
D 2
		u.u_cred = saveucredp;
E 2
D 9
		if (umap_bug_bypass && (*credpp)->cr_uid != 0 )
E 9
I 9
		if (umap_bug_bypass && credpp && (*credpp)->cr_uid != 0)
E 9
		 	printf("umap_bypass: returning-user now %d\n\n", 
			    (*credpp)->cr_uid);
	}

I 2
	if (descp->vdesc_componentname_offset != VDESC_NO_OFFSET) {
D 9
		if (umap_bug_bypass && compcredp->cr_uid != 0 )
E 9
I 9
		if (umap_bug_bypass && compcredp && compcredp->cr_uid != 0)
E 9
		printf("umap_bypass: returning-component-user was %d\n", 
D 9
		    compcredp->cr_uid);
E 9
I 9
				compcredp->cr_uid);
E 9

		crfree(compcredp);
		(*compnamepp)->cn_cred = savecompcredp;
D 9
		if (umap_bug_bypass && (*credpp)->cr_uid != 0 )
		 	printf("umap_bypass: returning-component-user now %d\n\n", 
			    compcredp->cr_uid);
E 9
I 9
		if (umap_bug_bypass && credpp && (*credpp)->cr_uid != 0)
		 	printf("umap_bypass: returning-component-user now %d\n", 
					compcredp->cr_uid);
E 9
	}

E 2
	return (error);
}


/*
 *  We handle getattr to change the fsid.
 */
int
umap_getattr(ap)
D 4
	struct vop_getattr_args *ap;
E 4
I 4
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{
	short uid, gid;
D 9
	int error, tmpid, *mapdata, nentries, *gmapdata, gnentries;
E 9
I 9
	int error, tmpid, nentries, gnentries;
	u_long (*mapdata)[2], (*gmapdata)[2];
E 9
I 2
	struct vnode **vp1p;
	struct vnodeop_desc *descp = ap->a_desc;
E 2

D 2
	if (error=umap_bypass(ap))
E 2
I 2
	if (error = umap_bypass(ap))
E 2
D 4
		return error;
E 4
I 4
		return (error);
E 4
	/* Requires that arguments be restored. */
	ap->a_vap->va_fsid = ap->a_vp->v_mount->mnt_stat.f_fsid.val[0];

D 2
	/* umap needs to map the uid and gid returned by a stat
		into the proper values for this site.  This involves
		finding the returned uid in the mapping information,
		translating it into the uid on the other end,
		and filling in the proper field in the vattr
		structure pointed to by ap->a_vap.  The group
		is easier, since currently all groups will be
		translate to the NULLGROUP. */
E 2
I 2
	/*
	 * Umap needs to map the uid and gid returned by a stat
	 * into the proper values for this site.  This involves
	 * finding the returned uid in the mapping information,
	 * translating it into the uid on the other end,
	 * and filling in the proper field in the vattr
	 * structure pointed to by ap->a_vap.  The group
	 * is easier, since currently all groups will be
	 * translate to the NULLGROUP.
	 */
E 2

	/* Find entry in map */

	uid = ap->a_vap->va_uid;
	gid = ap->a_vap->va_gid;
	if (umap_bug_bypass)
D 9
		printf("umap_getattr: mapped uid = %d, mapped gid = %d\n",uid, 
E 9
I 9
		printf("umap_getattr: mapped uid = %d, mapped gid = %d\n", uid, 
E 9
		    gid);

D 9
	vp1p = VOPARG_OFFSETTO(struct vnode**,descp->vdesc_vp_offsets[0],ap);
E 9
I 9
	vp1p = VOPARG_OFFSETTO(struct vnode**, descp->vdesc_vp_offsets[0], ap);
E 9
D 2
	nentries =  MOUNTTOUMAPMOUNT((*vp1p)->v_vfsp)->info_nentries;
	mapdata =  &(MOUNTTOUMAPMOUNT((*vp1p)->v_vfsp)->info_mapdata[0][0]);
	gnentries =  MOUNTTOUMAPMOUNT((*vp1p)->v_vfsp)->info_gnentries;
	gmapdata =  &(MOUNTTOUMAPMOUNT((*vp1p)->v_vfsp)->info_gmapdata[0][0]);
E 2
I 2
	nentries =  MOUNTTOUMAPMOUNT((*vp1p)->v_mount)->info_nentries;
D 9
	mapdata =  &(MOUNTTOUMAPMOUNT((*vp1p)->v_mount)->info_mapdata[0][0]);
E 9
I 9
	mapdata =  (MOUNTTOUMAPMOUNT((*vp1p)->v_mount)->info_mapdata);
E 9
	gnentries =  MOUNTTOUMAPMOUNT((*vp1p)->v_mount)->info_gnentries;
D 9
	gmapdata =  &(MOUNTTOUMAPMOUNT((*vp1p)->v_mount)->info_gmapdata[0][0]);
E 9
I 9
	gmapdata =  (MOUNTTOUMAPMOUNT((*vp1p)->v_mount)->info_gmapdata);
E 9
E 2

	/* Reverse map the uid for the vnode.  Since it's a reverse
		map, we can't use umap_mapids() to do it. */

D 9
	tmpid = umap_reverse_findid(uid,mapdata,nentries);
E 9
I 9
	tmpid = umap_reverse_findid(uid, mapdata, nentries);
E 9

D 9
	if (tmpid != -1 ) {
E 9
I 9
	if (tmpid != -1) {
E 9

D 9
		ap->a_vap->va_uid = (uid_t)tmpid;
E 9
I 9
		ap->a_vap->va_uid = (uid_t) tmpid;
E 9
		if (umap_bug_bypass)
D 9
			printf("umap_getattr: original uid = %d\n",uid);
E 9
I 9
			printf("umap_getattr: original uid = %d\n", uid);
E 9
	} else 
D 9
		ap->a_vap->va_uid = (uid_t)NOBODY;
E 9
I 9
		ap->a_vap->va_uid = (uid_t) NOBODY;
E 9

	/* Reverse map the gid for the vnode. */

D 9
	tmpid = umap_reverse_findid(gid,gmapdata,gnentries);
E 9
I 9
	tmpid = umap_reverse_findid(gid, gmapdata, gnentries);
E 9

	if (tmpid != -1) {

D 9
		ap->a_vap->va_gid = (gid_t)tmpid;
E 9
I 9
		ap->a_vap->va_gid = (gid_t) tmpid;
E 9
		if (umap_bug_bypass)
D 9
			printf("umap_getattr: original gid = %d\n",gid);
E 9
I 9
			printf("umap_getattr: original gid = %d\n", gid);
E 9
	} else
D 9
		ap->a_vap->va_gid = (gid_t)NULLGROUP;
E 9
I 9
		ap->a_vap->va_gid = (gid_t) NULLGROUP;
E 9
	
D 4
	return 0;
E 4
I 4
	return (0);
E 4
}

I 11
/*
D 12
 * We need to verify that we are not being vgoned and then clear
 * the interlock flag as it applies only to our vnode, not the
E 12
I 12
 * We need to process our own vnode lock and then clear the
 * interlock flag as it applies only to our vnode, not the
E 12
 * vnodes below us on the stack.
 */
E 11
int
I 11
umap_lock(ap)
D 12
	struct vop_lock_args *ap;
E 12
I 12
	struct vop_lock_args /* {
		struct vnode *a_vp;
		int a_flags;
		struct proc *a_p;
	} */ *ap;
E 12
{
I 12

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
umap_unlock(ap)
	struct vop_unlock_args /* {
		struct vnode *a_vp;
		int a_flags;
		struct proc *a_p;
	} */ *ap;
{
E 12
	struct vnode *vp = ap->a_vp;
D 12
	int error;
E 12

D 12
	if ((ap->a_flags & LK_INTERLOCK) == 0)
		simple_lock(&vp->v_interlock);
	if (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		simple_unlock(&vp->v_interlock);
		tsleep((caddr_t)vp, PINOD, "unionlk1", 0);
		return (ENOENT);
	}
	simple_unlock(&vp->v_interlock);
E 12
I 12
	vop_nounlock(ap);
E 12
	ap->a_flags &= ~LK_INTERLOCK;
D 12
	if (error = umap_bypass(ap))
		return (error);
	return (0);
E 12
I 12
	return (null_bypass(ap));
E 12
}

int
E 11
D 4
umap_inactive (ap)
	struct vop_inactive_args *ap;
E 4
I 4
umap_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 12
		struct proc *a_p;
E 12
	} */ *ap;
E 4
{
D 2
#ifdef UMAPFS_DIAGNOSTIC
	printf("umap_inactive(ap->a_vp = %x->%x)\n", ap->a_vp, UMAPVPTOLOWERVP(ap->a_vp));
#endif
E 2
	/*
	 * Do nothing (and _don't_ bypass).
	 * Wait to vrele lowervp until reclaim,
	 * so that until then our umap_node is in the
	 * cache and reusable.
	 *
D 2
	 * NEEDSWORK: Someday, consider inactive'ing
	 * the lowervp and then trying to reactivate it
	 * like they do in the name lookup cache code.
	 * That's too much work for now.
E 2
	 */
I 12
	VOP_UNLOCK(ap->a_vp, 0, ap->a_p);
E 12
D 4
	return 0;
E 4
I 4
	return (0);
E 4
}

int
D 4
umap_reclaim (ap)
	struct vop_reclaim_args *ap;
E 4
I 4
umap_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 4
{
D 2
	struct vnode *targetvp;

	/*
	 * Note: at this point, ap->a_vp->v_op == dead_vnodeop_p.
	 */
#ifdef UMAPFS_DIAGNOSTIC
	printf("umap_reclaim(ap->a_vp = %x->%x)\n", ap->a_vp, UMAPVPTOLOWERVP(ap->a_vp));
#endif
	remque(VTOUMAP(ap->a_vp));	     /* NEEDSWORK: What? */
	vrele (UMAPVPTOLOWERVP(ap->a_vp));   /* release lower layer */
	FREE(ap->a_vp->v_data, M_TEMP);
	ap->a_vp->v_data = 0;
	return (0);
E 2
I 2
	struct vnode *vp = ap->a_vp;
	struct umap_node *xp = VTOUMAP(vp);
	struct vnode *lowervp = xp->umap_lowervp;
	
	/* After this assignment, this node will not be re-used. */
	xp->umap_lowervp = NULL;
D 10
	remque(xp);
E 10
I 10
	LIST_REMOVE(xp, umap_hash);
E 10
	FREE(vp->v_data, M_TEMP);
	vp->v_data = NULL;
D 9
	vrele (lowervp);
E 9
I 9
	vrele(lowervp);
E 9
D 4
	return 0;
E 4
I 4
	return (0);
E 4
E 2
}

int
D 2
umap_bmap (ap)
	struct vop_bmap_args *ap;
E 2
I 2
D 4
umap_strategy (ap)
	struct vop_strategy_args *ap;
E 4
I 4
umap_strategy(ap)
	struct vop_strategy_args /* {
		struct buf *a_bp;
	} */ *ap;
E 4
E 2
{
D 2
#ifdef UMAPFS_DIAGNOSTIC
	printf("umap_bmap(ap->a_vp = %x->%x)\n", ap->a_vp, UMAPVPTOLOWERVP(ap->a_vp));
#endif
E 2
I 2
	struct buf *bp = ap->a_bp;
	int error;
	struct vnode *savedvp;
E 2

D 2
	return VOP_BMAP(UMAPVPTOLOWERVP(ap->a_vp), ap->a_bn, ap->a_vpp, ap->a_bnp);
E 2
I 2
	savedvp = bp->b_vp;
	bp->b_vp = UMAPVPTOLOWERVP(bp->b_vp);

	error = VOP_STRATEGY(ap->a_bp);

	bp->b_vp = savedvp;

D 4
	return error;
E 4
I 4
	return (error);
E 4
E 2
}

int
D 2
umap_strategy (ap)
	struct vop_strategy_args *ap;
E 2
I 2
D 4
umap_bwrite (ap)
	struct vop_bwrite_args *ap;
E 4
I 4
umap_bwrite(ap)
	struct vop_bwrite_args /* {
		struct buf *a_bp;
	} */ *ap;
E 4
E 2
{
I 2
	struct buf *bp = ap->a_bp;
E 2
	int error;
	struct vnode *savedvp;

D 2
#ifdef UMAPFS_DIAGNOSTIC
	printf("umap_strategy(vp = %x->%x)\n", ap->a_bp->b_vp, UMAPVPTOLOWERVP(ap->a_bp->b_vp));
#endif
E 2
I 2
	savedvp = bp->b_vp;
	bp->b_vp = UMAPVPTOLOWERVP(bp->b_vp);
E 2

D 2
	savedvp = ap->a_bp->b_vp;
E 2
I 2
	error = VOP_BWRITE(ap->a_bp);
E 2

D 2
	error = VOP_STRATEGY(ap->a_bp);
E 2
I 2
	bp->b_vp = savedvp;
E 2

D 2
	ap->a_bp->b_vp = savedvp;

E 2
D 4
	return error;
E 4
I 4
	return (error);
E 4
}


int
D 4
umap_print (ap)
	struct vop_print_args *ap;
E 4
I 4
umap_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 4
{
D 9
	register struct vnode *vp = ap->a_vp;
	printf ("\ttag VT_UMAPFS, vp=%x, lowervp=%x\n", vp, UMAPVPTOLOWERVP(vp));
E 9
I 9
	struct vnode *vp = ap->a_vp;
	printf("\ttag VT_UMAPFS, vp=%x, lowervp=%x\n", vp, UMAPVPTOLOWERVP(vp));
E 9
D 4
	return 0;
E 4
I 4
	return (0);
E 4
}

I 2
int
umap_rename(ap)
D 4
	struct vop_rename_args *ap;
E 4
I 4
	struct vop_rename_args  /* {
		struct vnode *a_fdvp;
		struct vnode *a_fvp;
		struct componentname *a_fcnp;
		struct vnode *a_tdvp;
		struct vnode *a_tvp;
		struct componentname *a_tcnp;
	} */ *ap;
E 4
{
	int error;
	struct componentname *compnamep;
	struct ucred *compcredp, *savecompcredp;
	struct vnode *vp;
E 2

I 2
D 5
	/* Now map the second componentname structure kept in this vop's
	 * arguments. 
E 5
I 5
	/*
	 * Rename is irregular, having two componentname structures.
	 * We need to map the cre in the second structure,
	 * and then bypass takes care of the rest.
E 5
	 */

	vp = ap->a_fdvp;
	compnamep = ap->a_tcnp;
	compcredp = compnamep->cn_cred;

	savecompcredp = compcredp;
	compcredp = compnamep->cn_cred = crdup(savecompcredp);

D 9
	if (umap_bug_bypass && compcredp->cr_uid != 0 )
E 9
I 9
	if (umap_bug_bypass && compcredp->cr_uid != 0)
E 9
		printf("umap_rename: rename component credit user was %d, group %d\n", 
D 9
		    compcredp->cr_uid,compcredp->cr_gid);
E 9
I 9
		    compcredp->cr_uid, compcredp->cr_gid);
E 9

	/* Map all ids in the credential structure. */

D 9
	umap_mapids(vp->v_mount,compcredp);
E 9
I 9
	umap_mapids(vp->v_mount, compcredp);
E 9

D 9
	if (umap_bug_bypass && compcredp->cr_uid != 0 )
E 9
I 9
	if (umap_bug_bypass && compcredp->cr_uid != 0)
E 9
		printf("umap_rename: rename component credit user now %d, group %d\n", 
D 9
		    compcredp->cr_uid,compcredp->cr_gid);
E 9
I 9
		    compcredp->cr_uid, compcredp->cr_gid);
E 9

D 5
	if (error = umap_bypass(ap))
D 4
		return error;
E 4
I 4
		return (error);
E 5
I 5
	error = umap_bypass(ap);
E 5
E 4
	
	/* Restore the additional mapped componentname cred structure. */

	crfree(compcredp);
	compnamep->cn_cred = savecompcredp;
D 5
	
E 5
I 5

	return error;
E 5
}

E 2
/*
 * Global vfs data structures
 */
/*
D 2
 * NEEDSWORK: strategy,bmap are hand coded currently.  They should
E 2
I 2
D 9
 * XXX - strategy,bwrite are hand coded currently.  They should
E 9
I 9
 * XXX - strategy, bwrite are hand coded currently.  They should
E 9
E 2
 * go away with a merged buffer/block cache.
 *
 */
int (**umap_vnodeop_p)();
struct vnodeopv_entry_desc umap_vnodeop_entries[] = {
	{ &vop_default_desc, umap_bypass },

	{ &vop_getattr_desc, umap_getattr },
I 11
	{ &vop_lock_desc, umap_lock },
I 12
	{ &vop_unlock_desc, umap_unlock },
E 12
E 11
	{ &vop_inactive_desc, umap_inactive },
	{ &vop_reclaim_desc, umap_reclaim },
	{ &vop_print_desc, umap_print },
I 5
	{ &vop_rename_desc, umap_rename },
E 5

D 2
	{ &vop_bmap_desc, umap_bmap },
E 2
	{ &vop_strategy_desc, umap_strategy },
I 2
	{ &vop_bwrite_desc, umap_bwrite },
E 2

D 2
	{ (struct vnodeop_desc*)UMAP, (int(*)())UMAP }
E 2
I 2
D 9
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 9
I 9
	{ (struct vnodeop_desc*) NULL, (int(*)()) NULL }
E 9
E 2
};
struct vnodeopv_desc umap_vnodeop_opv_desc =
	{ &umap_vnodeop_p, umap_vnodeop_entries };
E 1
