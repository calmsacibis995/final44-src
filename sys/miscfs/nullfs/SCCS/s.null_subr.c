h26279
s 00003/00001/00246
d D 8.7 95/05/14 00:42:02 mckusick 15 14
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00012/00031/00235
d D 8.6 94/08/20 15:58:28 mckusick 14 13
c update to use LIST hash structures
e
s 00002/00003/00264
d D 8.5 94/06/15 16:48:52 mkm 13 12
c missing argument to vprint (from mycroft)
e
s 00000/00001/00267
d D 8.4 94/01/21 19:54:23 bostic 12 11
c copyright typo
e
s 00002/00002/00266
d D 8.3 94/01/04 17:14:16 pendry 11 10
c use new VT_ value
e
s 00001/00033/00267
d D 8.2 93/12/30 16:17:57 mckusick 10 9
c no longer need non-locking copy of vget
e
s 00002/00002/00298
d D 8.1 93/06/10 23:46:05 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00006/00296
d D 7.1 92/07/12 15:10:48 mckusick 8 7
c move to rev 7; new include location; misc syntax niggles
e
s 00055/00096/00247
d D 1.7 92/07/11 15:24:15 heideman 7 6
c cleanup
e
s 00001/00000/00342
d D 1.6 92/07/11 08:46:08 heideman 6 5
c Working, with vnode caching.
e
s 00135/00066/00207
d D 1.5 92/07/10 23:17:43 heideman 5 4
c No refcount problems, but no caching.
e
s 00001/00001/00272
d D 1.4 92/07/10 13:46:23 heideman 4 3
c a working version: it does nothing, correctly
e
s 00016/00040/00257
d D 1.3 92/07/07 17:46:35 johnh 3 2
c first draft
e
s 00088/00088/00209
d D 1.2 92/07/07 14:07:44 johnh 2 1
c the great variable renaming
e
s 00297/00000/00000
d D 1.1 92/07/07 13:54:29 johnh 1 0
c date and time created 92/07/07 13:54:29 by johnh
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
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 9
I 9
 * Copyright (c) 1992, 1993
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
D 8
 *	@(#)lofs_subr.c	1.2 (Berkeley) 6/18/92
E 8
I 8
 *	%W% (Berkeley) %G%
E 8
 *
 * $Id: lofs_subr.c,v 1.11 1992/05/30 10:05:43 jsp Exp jsp $
 */

#include <sys/param.h>
#include <sys/systm.h>
I 15
#include <sys/proc.h>
E 15
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
D 8
#include <nullfs/null.h>
E 8
I 8
#include <miscfs/nullfs/null.h>
E 8
E 4

#define LOG2_SIZEVNODE 7		/* log2(sizeof struct vnode) */
D 2
#define	NLOFSCACHE 16
#define	LOFS_NHASH(vp) ((((u_long)vp)>>LOG2_SIZEVNODE) & (NLOFSCACHE-1))
E 2
I 2
#define	NNULLNODECACHE 16
D 14
#define	NULL_NHASH(vp) ((((u_long)vp)>>LOG2_SIZEVNODE) & (NNULLNODECACHE-1))
E 14
E 2

/*
D 2
 * Loopback cache:
E 2
I 2
 * Null layer cache:
E 2
D 5
 * Each cache entry holds a reference to the target vnode
E 5
I 5
 * Each cache entry holds a reference to the lower vnode
E 5
 * along with a pointer to the alias vnode.  When an
D 5
 * entry is added the target vnode is VREF'd.  When the
 * alias is removed the target vnode is vrele'd.
E 5
I 5
 * entry is added the lower vnode is VREF'd.  When the
 * alias is removed the lower vnode is vrele'd.
E 5
 */

D 14
/*
 * Cache head
 */
D 2
struct lofscache {
	struct lofsnode	*ac_forw;
	struct lofsnode	*ac_back;
E 2
I 2
struct null_node_cache {
	struct null_node	*ac_forw;
	struct null_node	*ac_back;
E 2
};
E 14
I 14
#define	NULL_NHASH(vp) \
	(&null_node_hashtbl[(((u_long)vp)>>LOG2_SIZEVNODE) & null_node_hash])
LIST_HEAD(null_node_hashhead, null_node) *null_node_hashtbl;
u_long null_node_hash;
E 14

D 2
static struct lofscache lofscache[NLOFSCACHE];
E 2
I 2
D 14
static struct null_node_cache null_node_cache[NNULLNODECACHE];
E 2

E 14
/*
 * Initialise cache headers
 */
D 2
lofs_init()
E 2
I 2
nullfs_init()
E 2
{
D 2
	struct lofscache *ac;
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_init\n");		/* printed during system boot */
E 2
I 2
D 14
	struct null_node_cache *ac;
E 14
I 14

E 14
#ifdef NULLFS_DIAGNOSTIC
	printf("nullfs_init\n");		/* printed during system boot */
E 2
#endif
D 14

D 2
	for (ac = lofscache; ac < lofscache + NLOFSCACHE; ac++)
		ac->ac_forw = ac->ac_back = (struct lofsnode *) ac;
E 2
I 2
	for (ac = null_node_cache; ac < null_node_cache + NNULLNODECACHE; ac++)
		ac->ac_forw = ac->ac_back = (struct null_node *) ac;
E 14
I 14
	null_node_hashtbl = hashinit(NNULLNODECACHE, M_CACHE, &null_node_hash);
E 14
E 2
}

/*
D 5
 * Compute hash list for given target vnode
E 5
I 5
D 14
 * Compute hash list for given lower vnode
E 5
 */
D 2
static struct lofscache *
lofs_hash(targetvp)
E 2
I 2
static struct null_node_cache *
D 5
null_node_hash(targetvp)
E 2
struct vnode *targetvp;
E 5
I 5
null_node_hash(lowervp)
struct vnode *lowervp;
E 5
{
I 7

E 7
D 2
	return (&lofscache[LOFS_NHASH(targetvp)]);
E 2
I 2
D 5
	return (&null_node_cache[NULL_NHASH(targetvp)]);
E 5
I 5
	return (&null_node_cache[NULL_NHASH(lowervp)]);
E 5
E 2
}

D 7
/*
D 2
 * Make a new lofsnode node.
E 2
I 2
 * Make a new null_node node.
E 2
D 5
 * Vp is the alias vnode, lofsvp is the target vnode.
 * Maintain a reference to (targetvp).
E 5
I 5
 * Vp is the alias vnode, lofsvp is the lower vnode.
 * Maintain a reference to (lowervp).
E 5
 */
static void
D 2
lofs_alloc(vp, targetvp)
E 2
I 2
D 5
null_node_alloc(vp, targetvp)
E 5
I 5
null_node_alloc(vp, lowervp)
E 5
E 2
	struct vnode *vp;
D 5
	struct vnode *targetvp;
E 5
I 5
	struct vnode *lowervp;
E 5
{
D 2
	struct lofscache *hd;
	struct lofsnode *a;
E 2
I 2
	struct null_node_cache *hd;
	struct null_node *a;
E 7
E 2
D 10

E 10
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_alloc(%x, %x)\n", vp, targetvp);
E 2
I 2
D 7
#ifdef NULLFS_DIAGNOSTIC
D 5
	printf("null_node_alloc(%x, %x)\n", vp, targetvp);
E 5
I 5
	printf("null_node_alloc(%x, %x)\n", vp, lowervp);
E 5
E 2
#endif

D 2
	MALLOC(a, struct lofsnode *, sizeof(struct lofsnode), M_TEMP, M_WAITOK);
	a->a_vnode = vp;
E 2
I 2
	MALLOC(a, struct null_node *, sizeof(struct null_node), M_TEMP, M_WAITOK);
I 5
	vp->v_type = lowervp->v_type;
E 5
	a->null_vnode = vp;
E 2
	vp->v_data = a;
D 5
	VREF(targetvp);
D 2
	a->a_lofsvp = targetvp;
	hd = lofs_hash(targetvp);
E 2
I 2
	a->null_lowervp = targetvp;
	hd = null_node_hash(targetvp);
E 5
I 5
	VREF(lowervp);   /* Extra VREF will be vrele'd in null_node_create */
	a->null_lowervp = lowervp;
	hd = null_node_hash(lowervp);
E 5
E 2
	insque(a, hd);

D 2
#ifdef LOFS_DIAGNOSTIC
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
E 2
D 5
	vprint("alloc vp", vp);
	vprint("alloc targetvp", targetvp);
E 5
I 5
	vprint("null_node_alloc vp", vp);
	vprint("null_node_alloc lowervp", lowervp);
E 5
#endif
}

D 2
#ifdef LOFS_DIAGNOSTIC
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
E 7
I 3
/*
E 14
D 7
 * NEEDSWORK:  The ability to set lowervp to null here
 * implies that one can never count on lowervp staying null
 * (even if vp is locked).  This seems quite bad.  Think
 * about these things.
 */
E 3
E 2
void
D 2
lofs_flushmp(mp)
E 2
I 2
null_node_flushmp (mp)
E 2
	struct mount *mp;
{
D 2
	struct lofscache *ac;
E 2
I 2
	struct null_node_cache *ac;
E 2
	int i = 0;
D 2
	struct lofsnode *roota;
E 2
I 2
	struct null_node *roota;
E 2

D 2
	printf("lofs_flushmp(%x)\n", mp);
E 2
I 2
	printf("null_node_flushmp (%x)\n", mp);
E 2

D 2
	roota = LOFSP(VFSTOLOFS(mp)->rootvp);
E 2
I 2
D 5
	roota = VTONULLNODE(MOUNTTONULLMOUNT(mp)->nullm_rootvp);
E 5
I 5
	roota = VTONULL(MOUNTTONULLMOUNT(mp)->nullm_rootvp);
E 5
E 2

D 2
	for (ac = lofscache; ac < lofscache + NLOFSCACHE; ac++) {
		struct lofsnode *a = ac->ac_forw;
		while (a != (struct lofsnode *) ac) {
			if (a != roota && a->a_vnode->v_mount == mp) {
				struct vnode *vp = a->a_lofsvp;
E 2
I 2
	for (ac = null_node_cache; ac < null_node_cache + NNULLNODECACHE; ac++) {
		struct null_node *a = ac->ac_forw;
		while (a != (struct null_node *) ac) {
D 5
			if (a != roota && a->null_vnode->v_mount == mp) {
E 5
I 5
			if (a != roota && NULLTOV(a)->v_mount == mp) {
E 5
				struct vnode *vp = a->null_lowervp;
E 2
				if (vp) {
D 2
					a->a_lofsvp = 0;
E 2
I 2
					a->null_lowervp = 0;
E 2
D 5
					vprint("would vrele", vp);
E 5
I 5
					vprint("null_flushmp: would vrele", vp);
E 5
					/*vrele(vp);*/
					i++;
				}
			}
D 2
			a = a->a_forw;
E 2
I 2
			a = a->null_forw;
E 2
		}
	}
	if (i > 0)
D 2
		printf("lofsnode: vrele'd %d aliases\n", i);
E 2
I 2
		printf("null_node: vrele'd %d aliases\n", i);
E 2
}
#endif

/*
E 7
D 5
 * Return alias for target vnode if already exists, else 0.
E 5
I 5
D 10
 * XXX - this should go elsewhere.
 * Just like vget, but with no lock at the end.
E 5
 */
D 2
static struct lofsnode *
lofs_find(mp, targetvp)
E 2
I 2
D 5
static struct null_node *
null_node_find(mp, targetvp)
E 5
I 5
int
vget_nolock(vp)
	register struct vnode *vp;
{
	extern struct vnode *vfreeh, **vfreet;
	register struct vnode *vq;

	if (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
		return (1);
	}
	if (vp->v_usecount == 0) {
		if (vq = vp->v_freef)
			vq->v_freeb = vp->v_freeb;
		else
			vfreet = vp->v_freeb;
		*vp->v_freeb = vq;
		vp->v_freef = NULL;
		vp->v_freeb = NULL;
	}
	VREF(vp);
	/* VOP_LOCK(vp); */
	return (0);
}


/*
E 10
 * Return a VREF'ed alias for lower vnode if already exists, else 0.
 */
static struct vnode *
null_node_find(mp, lowervp)
E 5
E 2
	struct mount *mp;
D 5
	struct vnode *targetvp;
E 5
I 5
	struct vnode *lowervp;
E 5
{
I 15
	struct proc *p = curproc;	/* XXX */
E 15
D 2
	struct lofscache *hd;
	struct lofsnode *a;
E 2
I 2
D 14
	struct null_node_cache *hd;
E 14
I 14
	struct null_node_hashhead *hd;
E 14
	struct null_node *a;
I 5
	struct vnode *vp;
E 5
E 2

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_find(mp = %x, target = %x)\n", mp, targetvp);
E 2
I 2
D 7
#ifdef NULLFS_DIAGNOSTIC
D 5
	printf("null_node_find(mp = %x, target = %x)\n", mp, targetvp);
E 5
I 5
	printf("null_node_find(mp = %x, lower = %x)\n", mp, lowervp);
E 5
E 2
#endif

E 7
	/*
	 * Find hash base, and then search the (two-way) linked
D 2
	 * list looking for a lofsnode structure which is referencing
	 * the target vnode.  If found, the increment the lofsnode
E 2
I 2
	 * list looking for a null_node structure which is referencing
D 5
	 * the target vnode.  If found, the increment the null_node
E 2
	 * reference count (but NOT the target vnode's VREF counter).
E 5
I 5
	 * the lower vnode.  If found, the increment the null_node
	 * reference count (but NOT the lower vnode's VREF counter).
E 5
	 */
D 2
	hd = lofs_hash(targetvp);
E 2
I 2
D 5
	hd = null_node_hash(targetvp);
E 2

E 5
I 5
D 14
	hd = null_node_hash(lowervp);
E 14
I 14
	hd = NULL_NHASH(lowervp);
E 14
loop:
E 5
D 2
	for (a = hd->ac_forw; a != (struct lofsnode *) hd; a = a->a_forw) {
		if (a->a_lofsvp == targetvp && a->a_vnode->v_mount == mp) {
#ifdef LOFS_DIAGNOSTIC
			printf("lofs_find(%x): found (%x,%x)->%x\n",
				targetvp, mp, a->a_vnode, targetvp);
E 2
I 2
D 14
	for (a = hd->ac_forw; a != (struct null_node *) hd; a = a->null_forw) {
E 14
I 14
	for (a = hd->lh_first; a != 0; a = a->null_hash.le_next) {
E 14
D 5
		if (a->null_lowervp == targetvp && a->null_vnode->v_mount == mp) {
E 5
I 5
		if (a->null_lowervp == lowervp && NULLTOV(a)->v_mount == mp) {
E 5
D 7
#ifdef NULLFS_DIAGNOSTIC
			printf("null_node_find(%x): found (%x,%x)->%x\n",
D 5
				targetvp, mp, a->null_vnode, targetvp);
E 5
I 5
				lowervp, mp, NULLTOV(a), lowervp);
E 5
E 2
#endif
E 7
D 5
			return (a);
E 5
I 5
			vp = NULLTOV(a);
			/*
D 7
			 * NEEDSWORK: Don't call the normal vget,
			 * it will do a VOP_LOCK which is bypassed
			 * and will lock against ourselves.
			 * Unfortunately, we need vget for the VXLOCK
			 * stuff.
E 7
I 7
			 * We need vget for the VXLOCK
			 * stuff, but we don't want to lock
			 * the lower node.
E 7
			 */
D 10
			if (vget_nolock(vp)) {
E 10
I 10
D 15
			if (vget(vp, 0)) {
E 15
I 15
			if (vget(vp, 0, p)) {
E 15
E 10
				printf ("null_node_find: vget failed.\n");
				goto loop;
			};
I 6
D 7
			a->null_isinactive = 0;
E 7
E 6
			return (vp);
E 5
		}
	}

D 2
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_find(%x, %x): NOT found\n", mp, targetvp);
E 2
I 2
D 7
#ifdef NULLFS_DIAGNOSTIC
D 5
	printf("null_node_find(%x, %x): NOT found\n", mp, targetvp);
E 5
I 5
	printf("null_node_find(%x, %x): NOT found\n", mp, lowervp);
E 5
E 2
#endif

E 7
D 5
	return (0);
E 5
I 5
	return NULL;
E 5
}

I 5
D 7
#if 1
int null_node_create_barrier = 1;
#endif
E 7

E 5
D 3
static int
D 2
lofs_alias(mp, targetvp, newvpp)
E 2
I 2
null_node_alias(mp, targetvp, newvpp)
E 3
I 3
/*
I 7
 * Make a new null_node node.
 * Vp is the alias vnode, lofsvp is the lower vnode.
 * Maintain a reference to (lowervp).
 */
static int
null_node_alloc(mp, lowervp, vpp)
	struct mount *mp;
	struct vnode *lowervp;
	struct vnode **vpp;
{
D 14
	struct null_node_cache *hd;
E 14
I 14
	struct null_node_hashhead *hd;
E 14
	struct null_node *xp;
	struct vnode *othervp, *vp;
	int error;

D 11
	if (error = getnewvnode(VT_UFS, mp, null_vnodeop_p, vpp))
		return (error);	/* XXX: VT_NULL above */
E 11
I 11
	if (error = getnewvnode(VT_NULL, mp, null_vnodeop_p, vpp))
		return (error);
E 11
	vp = *vpp;

	MALLOC(xp, struct null_node *, sizeof(struct null_node), M_TEMP, M_WAITOK);
	vp->v_type = lowervp->v_type;
	xp->null_vnode = vp;
	vp->v_data = xp;
	xp->null_lowervp = lowervp;
	/*
	 * Before we insert our new node onto the hash chains,
	 * check to see if someone else has beaten us to it.
	 * (We could have slept in MALLOC.)
	 */
	if (othervp = null_node_find(lowervp)) {
		FREE(xp, M_TEMP);
		vp->v_type = VBAD;	/* node is discarded */
		vp->v_usecount = 0;	/* XXX */
		*vpp = othervp;
		return 0;
	};
	VREF(lowervp);   /* Extra VREF will be vrele'd in null_node_create */
D 14
	hd = null_node_hash(lowervp);
	insque(xp, hd);
E 14
I 14
	hd = NULL_NHASH(lowervp);
	LIST_INSERT_HEAD(hd, xp, null_hash);
E 14
	return 0;
}


/*
E 7
 * Try to find an existing null_node vnode refering
 * to it, otherwise make a new null_node vnode which
D 5
 * contains a reference to the target vnode.
E 5
I 5
 * contains a reference to the lower vnode.
E 5
 */
int
D 5
null_node_create(mp, targetvp, newvpp)
E 5
I 5
null_node_create(mp, lowervp, newvpp)
E 5
E 3
E 2
	struct mount *mp;
D 5
	struct vnode *targetvp;
E 5
I 5
	struct vnode *lowervp;
E 5
	struct vnode **newvpp;
{
D 2
	struct lofsnode *ap;
E 2
I 2
D 5
	struct null_node *ap;
E 5
E 2
	struct vnode *aliasvp;

D 2
	if (targetvp->v_type != VDIR || targetvp->v_op == lofs_vnodeop_p) {
E 2
I 2
D 5
	if (targetvp->v_type != VDIR || targetvp->v_op == null_vnodeop_p) {
E 2
		*newvpp = targetvp;
		return;
	}

D 2
	ap = lofs_find(mp, targetvp);
E 2
I 2
	ap = null_node_find(mp, targetvp);
E 2

	if (ap) {
E 5
I 5
	if (aliasvp = null_node_find(mp, lowervp)) {
E 5
		/*
D 5
		 * Take another reference to the alias vnode
E 5
I 5
		 * null_node_find has taken another reference
		 * to the alias vnode.
E 5
		 */
D 2
#ifdef LOFS_DIAGNOSTIC
		vprint("lofs_alias: exists", ap->a_vnode);
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
D 5
		vprint("null_node_alias: exists", ap->null_vnode);
E 5
I 5
		vprint("null_node_create: exists", NULLTOV(ap));
E 5
E 2
#endif
D 2
		aliasvp = ap->a_vnode;
E 2
I 2
D 5
		aliasvp = ap->null_vnode;
E 2
		VREF(aliasvp);
E 5
I 5
		/* VREF(aliasvp); --- done in null_node_find */
E 5
	} else {
		int error;

		/*
		 * Get new vnode.
		 */
D 2
#ifdef LOFS_DIAGNOSTIC
		printf("lofs_alias: create new alias vnode\n");
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
D 5
		printf("null_node_alias: create new alias vnode\n");
E 5
I 5
		printf("null_node_create: create new alias vnode\n");
E 5
E 2
#endif
D 2
		if (error = getnewvnode(VT_UFS, mp, lofs_vnodeop_p, &aliasvp))
E 2
I 2
D 7
		if (error = getnewvnode(VT_UFS, mp, null_vnodeop_p, &aliasvp))
E 2
D 5
			return (error);	/* XXX: VT_LOFS above */
E 5
I 5
			return (error);	/* XXX: VT_NULL above */
E 7
E 5

		/*
D 5
		 * Must be a directory
		 */
		aliasvp->v_type = VDIR;

		/*
E 5
D 2
		 * Make new vnode reference the lofsnode.
E 2
I 2
		 * Make new vnode reference the null_node.
E 2
		 */
D 2
		lofs_alloc(aliasvp, targetvp);
E 2
I 2
D 5
		null_node_alloc(aliasvp, targetvp);
E 5
I 5
D 7
		null_node_alloc(aliasvp, lowervp);
E 7
I 7
		if (error = null_node_alloc(mp, lowervp, &aliasvp))
			return error;
E 7
E 5
E 2

		/*
		 * aliasvp is already VREF'd by getnewvnode()
		 */
	}

D 5
	vrele(targetvp);
E 5
I 5
	vrele(lowervp);
E 5

I 7
#ifdef DIAGNOSTIC
E 7
I 5
	if (lowervp->v_usecount < 1) {
I 7
		/* Should never happen... */
E 7
D 13
		vprint ("null_node_create: alias ");
		vprint ("null_node_create: lower ");
		printf ("null_node_create: lower has 0 usecount.\n");
E 13
I 13
		vprint ("null_node_create: alias ", aliasvp);
		vprint ("null_node_create: lower ", lowervp);
E 13
D 7
		while (null_node_create_barrier) /* wait */ ;
E 7
		panic ("null_node_create: lower has 0 usecount.");
	};
I 7
#endif
E 7

E 5
D 2
#ifdef LOFS_DIAGNOSTIC
	vprint("lofs_alias alias", aliasvp);
	vprint("lofs_alias target", targetvp);
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
D 5
	vprint("null_node_alias alias", aliasvp);
	vprint("null_node_alias target", targetvp);
E 5
I 5
	vprint("null_node_create: alias", aliasvp);
	vprint("null_node_create: lower", lowervp);
E 5
E 2
#endif

	*newvpp = aliasvp;
	return (0);
}
D 3

/*
D 2
 * Try to find an existing lofsnode vnode refering
 * to it, otherwise make a new lofsnode vnode which
E 2
I 2
 * Try to find an existing null_node vnode refering
 * to it, otherwise make a new null_node vnode which
E 2
 * contains a reference to the target vnode.
 */
D 2
make_lofs(mp, vpp)
E 2
I 2
make_null_node(mp, vpp)
E 2
	struct mount *mp;
	struct vnode **vpp;
{
	int error;
	struct vnode *aliasvp;
	struct vnode *targetvp;

E 3
D 2
#ifdef LOFS_DIAGNOSTIC
	printf("make_lofs(mp = %x, vp = %x\n", mp, *vpp);
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
I 5
D 7
int null_checkvp_barrier = 1;
E 7
E 5
D 3
	printf("make_null_node(mp = %x, vp = %x\n", mp, *vpp);
E 2
#endif

	/*
	 * (targetvp) is locked at this point.
	 */
	targetvp = *vpp;

D 2
#ifdef LOFS_DIAGNOSTIC
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
E 2
	if (targetvp == 0)
D 2
		panic("make_lofs: null vp");
E 2
I 2
		panic("make_null_node: null vp");
E 2
#endif

	/*
	 * Try to find an existing reference to the target vnodes.
	 */
D 2
	return (lofs_alias(mp, targetvp, vpp));
E 2
I 2
	return (null_node_alias(mp, targetvp, vpp));
E 2
}

D 2
#ifdef LOFS_DIAGNOSTIC
E 2
I 2
#ifdef NULLFS_DIAGNOSTIC
E 3
E 2
struct vnode *
D 2
lofs_checkvp(vp, fil, lno)
E 2
I 2
null_checkvp(vp, fil, lno)
E 2
	struct vnode *vp;
	char *fil;
	int lno;
{
D 2
	struct lofsnode *a = LOFSP(vp);
	if (a->a_lofsvp == 0) {
E 2
I 2
D 5
	struct null_node *a = VTONULLNODE(vp);
	if (a->null_lowervp == 0) {
E 5
I 5
	struct null_node *a = VTONULL(vp);
D 8
#if 0
E 8
I 8
#ifdef notyet
E 8
	/*
	 * Can't do this check because vop_reclaim runs
	 * with a funny vop vector.
	 */
	if (vp->v_op != null_vnodeop_p) {
		printf ("null_checkvp: on non-null-node\n");
		while (null_checkvp_barrier) /*WAIT*/ ;
		panic("null_checkvp");
	};
#endif
	if (a->null_lowervp == NULL) {
E 5
I 3
		/* Should never happen */
E 3
E 2
		int i; u_long *p;
		printf("vp = %x, ZERO ptr\n", vp);
D 3
#ifdef notdef
E 3
		for (p = (u_long *) a, i = 0; i < 8; i++)
			printf(" %x", p[i]);
		printf("\n");
D 5
		DELAY(2000000);
E 5
I 5
		/* wait for debugger */
		while (null_checkvp_barrier) /*WAIT*/ ;
E 5
D 2
		panic("lofs_checkvp");
E 2
I 2
		panic("null_checkvp");
E 2
D 3
#endif
E 3
	}
D 3
	printf("aliasvp %x/%d -> %x/%d [%s, %d]\n",
E 3
I 3
D 5
	printf("nullvp %x/%d -> %x/%d [%s, %d]\n",
E 3
D 2
		a->a_vnode, a->a_vnode->v_usecount,
		a->a_lofsvp, a->a_lofsvp ? a->a_lofsvp->v_usecount : -42,
E 2
I 2
		a->null_vnode, a->null_vnode->v_usecount,
E 5
I 5
	if (a->null_lowervp->v_usecount < 1) {
		int i; u_long *p;
		printf("vp = %x, unref'ed lowervp\n", vp);
		for (p = (u_long *) a, i = 0; i < 8; i++)
			printf(" %x", p[i]);
		printf("\n");
		/* wait for debugger */
		while (null_checkvp_barrier) /*WAIT*/ ;
		panic ("null with unref'ed lowervp");
	};
D 8
#if 0
E 8
I 8
#ifdef notyet
E 8
	printf("null %x/%d -> %x/%d [%s, %d]\n",
	        NULLTOV(a), NULLTOV(a)->v_usecount,
E 5
D 3
		a->null_lowervp, a->null_lowervp ? a->null_lowervp->v_usecount : -42,
E 3
I 3
		a->null_lowervp, a->null_lowervp->v_usecount,
E 3
E 2
		fil, lno);
I 5
#endif
E 5
D 2
	return a->a_lofsvp;
E 2
I 2
	return a->null_lowervp;
E 2
}
#endif
I 7
D 8


E 8
E 7
E 1
