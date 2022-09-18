h15239
s 00005/00003/00349
d D 8.9 95/05/14 00:46:54 mckusick 12 11
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00001/00350
d D 8.8 95/03/29 00:42:42 mckusick 11 10
c correct type for umap_init
e
s 00013/00033/00338
d D 8.7 94/08/20 16:02:59 mckusick 10 9
c update to use LIST macros for hash table
e
s 00002/00001/00369
d D 8.6 94/01/26 21:11:29 mckusick 9 8
c  match pointer type with type of info_mapdata[][] (from Ralph)
e
s 00000/00001/00370
d D 8.5 94/01/21 19:55:29 bostic 8 7
c copyright typo
e
s 00080/00073/00291
d D 8.4 94/01/05 01:02:24 pendry 7 6
c handle wide uid/gid.  lint, KNF
e
s 00002/00002/00362
d D 8.3 94/01/04 17:13:46 pendry 6 5
c use new VT_ value
e
s 00001/00001/00363
d D 8.2 93/12/14 00:44:21 mckusick 5 4
c new vget parameter
e
s 00002/00002/00362
d D 8.1 93/06/10 23:47:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00013/00348
d D 7.1 92/07/12 15:28:50 mckusick 3 2
c move to rev 7; new include location; syntax niggles
e
s 00072/00095/00289
d D 1.2 92/07/11 15:28:36 heideman 2 1
c Porting from null layer
e
s 00384/00000/00000
d D 1.1 92/07/11 09:21:15 heideman 1 0
c date and time created 92/07/11 09:21:15 by heideman
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
D 12
 * Copyright (c) 1992, 1993
E 12
I 12
 * Copyright (c) 1992, 1993, 1995
E 12
 *	The Regents of the University of California.  All rights reserved.
E 4
D 8
 * All rights reserved.
E 8
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
D 3
 *	@(#)lofs_subr.c	1.2 (Berkeley) 6/18/92
E 3
I 3
 *	%W% (Berkeley) %G%
E 3
 *
D 7
 * $Id: lofs_subr.c,v 1.11 1992/05/30 10:05:43 jsp Exp jsp $
E 7
I 7
D 12
 * $Id: lofs_subr.c, v 1.11 1992/05/30 10:05:43 jsp Exp jsp $
E 12
I 12
 * From: $Id: lofs_subr.c, v 1.11 1992/05/30 10:05:43 jsp Exp jsp $
E 12
E 7
 */

#include <sys/param.h>
#include <sys/systm.h>
I 12
#include <sys/proc.h>
E 12
#include <sys/time.h>
#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
D 3
#include <umapfs/umap.h>
E 3
I 3
#include <miscfs/umapfs/umap.h>
E 3

#define LOG2_SIZEVNODE 7		/* log2(sizeof struct vnode) */
#define	NUMAPNODECACHE 16
D 7
#define	UMAP_NHASH(vp) ((((u_long)vp)>>LOG2_SIZEVNODE) & (NUMAPNODECACHE-1))
E 7
I 7
D 10
#define	UMAP_NHASH(vp) ((((u_long) vp)>>LOG2_SIZEVNODE) & (NUMAPNODECACHE-1))
E 10
E 7

/*
 * Null layer cache:
 * Each cache entry holds a reference to the target vnode
 * along with a pointer to the alias vnode.  When an
 * entry is added the target vnode is VREF'd.  When the
 * alias is removed the target vnode is vrele'd.
 */

D 10
/*
 * Cache head
 */
struct umap_node_cache {
	struct umap_node	*ac_forw;
	struct umap_node	*ac_back;
};
E 10
I 10
#define	UMAP_NHASH(vp) \
	(&umap_node_hashtbl[(((u_long)vp)>>LOG2_SIZEVNODE) & umap_node_hash])
LIST_HEAD(umap_node_hashhead, umap_node) *umap_node_hashtbl;
u_long umap_node_hash;
E 10

D 10
static struct umap_node_cache umap_node_cache[NUMAPNODECACHE];

E 10
/*
 * Initialise cache headers
 */
D 11
umapfs_init()
E 11
I 11
umapfs_init(vfsp)
	struct vfsconf *vfsp;
E 11
{
D 10
	struct umap_node_cache *ac;
E 10
I 10

E 10
#ifdef UMAPFS_DIAGNOSTIC
	printf("umapfs_init\n");		/* printed during system boot */
#endif
D 10

	for (ac = umap_node_cache; ac < umap_node_cache + NUMAPNODECACHE; ac++)
		ac->ac_forw = ac->ac_back = (struct umap_node *) ac;
E 10
I 10
	umap_node_hashtbl = hashinit(NUMAPNODECACHE, M_CACHE, &umap_node_hash);
E 10
}

/*
D 10
 * Compute hash list for given target vnode
 */
static struct umap_node_cache *
umap_node_hash(targetvp)
D 7
struct vnode *targetvp;
E 7
I 7
	struct vnode *targetvp;
E 7
{
I 3

E 3
	return (&umap_node_cache[UMAP_NHASH(targetvp)]);
}

/*
E 10
I 7
 * umap_findid is called by various routines in umap_vnodeops.c to
 * find a user or group id in a map.
 */
static u_long
umap_findid(id, map, nentries)
	u_long id;
	u_long map[][2];
	int nentries;
{
	int i;

	/* Find uid entry in map */
	i = 0;
	while ((i<nentries) && ((map[i][0]) != id))
		i++;

	if (i < nentries)
		return (map[i][1]);
	else
		return (-1);

}

/*
 * umap_reverse_findid is called by umap_getattr() in umap_vnodeops.c to
 * find a user or group id in a map, in reverse.
 */
u_long
umap_reverse_findid(id, map, nentries)
	u_long id;
	u_long map[][2];
	int nentries;
{
	int i;

	/* Find uid entry in map */
	i = 0;
	while ((i<nentries) && ((map[i][1]) != id))
		i++;

	if (i < nentries)
		return (map[i][0]);
	else
		return (-1);

}

/*
E 7
D 2
 * Make a new umap_node node.
 * Vp is the alias vnode, lofsvp is the target vnode.
 * Maintain a reference to (targetvp).
 */
static void
umap_node_alloc(vp, targetvp)
	struct vnode *vp;
	struct vnode *targetvp;
{
	struct umap_node_cache *hd;
	struct umap_node *a;

#ifdef UMAPFS_DIAGNOSTIC
	printf("umap_node_alloc(%x, %x)\n", vp, targetvp);
#endif

	MALLOC(a, struct umap_node *, sizeof(struct umap_node), M_TEMP, M_WAITOK);
	vp->v_type = targetvp->v_type;
	a->umap_vnode = vp;
	vp->v_data = a;
	VREF(targetvp);   /* Extra VREF will be vrele'd in umap_node_create */
	a->umap_lowervp = targetvp;
	hd = umap_node_hash(targetvp);
	insque(a, hd);

#ifdef UMAPFS_DIAGNOSTIC
	vprint("umap_node_alloc vp", vp);
	vprint("umap_node_alloc targetvp", targetvp);
#endif
}

#ifdef UMAPFS_DIAGNOSTIC
/*
 * NEEDSWORK:  The ability to set lowervp to umap here
 * implies that one can never count on lowervp staying umap
 * (even if vp is locked).  This seems quite bad.  Think
 * about these things.
 */
void
umap_node_flushmp (mp)
	struct mount *mp;
{
	struct umap_node_cache *ac;
	int i = 0;
	struct umap_node *roota;

	printf("umap_node_flushmp (%x)\n", mp);

	roota = VTOUMAP(MOUNTTOUMAPMOUNT(mp)->umapm_rootvp);

	for (ac = umap_node_cache; ac < umap_node_cache + NUMAPNODECACHE; ac++) {
		struct umap_node *a = ac->ac_forw;
		while (a != (struct umap_node *) ac) {
			if (a != roota && a->umap_vnode->v_mount == mp) {
				struct vnode *vp = a->umap_lowervp;
				if (vp) {
					a->umap_lowervp = 0;
					vprint("umap_flushmp: would vrele", vp);
					/*vrele(vp);*/
					i++;
				}
			}
			a = a->umap_forw;
		}
	}
	if (i > 0)
		printf("umap_node: vrele'd %d aliases\n", i);
}
#endif

/*
E 2
 * Return alias for target vnode if already exists, else 0.
 */
D 2
static struct umap_node *
E 2
I 2
static struct vnode *
E 2
umap_node_find(mp, targetvp)
	struct mount *mp;
	struct vnode *targetvp;
{
I 12
	struct proc *p = curproc;		/* XXX */
E 12
D 10
	struct umap_node_cache *hd;
E 10
I 10
	struct umap_node_hashhead *hd;
E 10
	struct umap_node *a;
I 2
	struct vnode *vp;
E 2

#ifdef UMAPFS_DIAGNOSTIC
	printf("umap_node_find(mp = %x, target = %x)\n", mp, targetvp);
#endif

	/*
	 * Find hash base, and then search the (two-way) linked
	 * list looking for a umap_node structure which is referencing
	 * the target vnode.  If found, the increment the umap_node
	 * reference count (but NOT the target vnode's VREF counter).
	 */
D 10
	hd = umap_node_hash(targetvp);

I 2
 loop:
E 2
	for (a = hd->ac_forw; a != (struct umap_node *) hd; a = a->umap_forw) {
E 10
I 10
	hd = UMAP_NHASH(targetvp);
loop:
	for (a = hd->lh_first; a != 0; a = a->umap_hash.le_next) {
E 10
D 3
		if (a->umap_lowervp == targetvp && a->umap_vnode->v_mount == mp) {
E 3
I 3
		if (a->umap_lowervp == targetvp &&
		    a->umap_vnode->v_mount == mp) {
E 3
D 2
#ifdef UMAPFS_DIAGNOSTIC
			printf("umap_node_find(%x): found (%x,%x)->%x\n",
				targetvp, mp, a->umap_vnode, targetvp);
#endif
			return (a);
E 2
I 2
			vp = UMAPTOV(a);
			/*
			 * We need vget for the VXLOCK
			 * stuff, but we don't want to lock
			 * the lower node.
			 */
D 5
			if (vget_nolock(vp)) {
E 5
I 5
D 12
			if (vget(vp, 0)) {
E 12
I 12
			if (vget(vp, 0, p)) {
E 12
E 5
D 7
				printf ("null_node_find: vget failed.\n");
E 7
I 7
#ifdef UMAPFS_DIAGNOSTIC
				printf ("umap_node_find: vget failed.\n");
#endif
E 7
				goto loop;
D 3
			};
E 3
I 3
			}
E 3
			return (vp);
E 2
		}
	}

#ifdef UMAPFS_DIAGNOSTIC
	printf("umap_node_find(%x, %x): NOT found\n", mp, targetvp);
#endif

	return (0);
}

/*
I 2
 * Make a new umap_node node.
 * Vp is the alias vnode, lofsvp is the target vnode.
 * Maintain a reference to (targetvp).
 */
static int
umap_node_alloc(mp, lowervp, vpp)
	struct mount *mp;
	struct vnode *lowervp;
	struct vnode **vpp;
{
D 10
	struct umap_node_cache *hd;
E 10
I 10
	struct umap_node_hashhead *hd;
E 10
	struct umap_node *xp;
	struct vnode *othervp, *vp;
	int error;

D 6
	if (error = getnewvnode(VT_UFS, mp, umap_vnodeop_p, vpp))
		return (error);	/* XXX: VT_UMAP above */
E 6
I 6
	if (error = getnewvnode(VT_UMAP, mp, umap_vnodeop_p, vpp))
		return (error);
E 6
	vp = *vpp;

D 3
	MALLOC(xp, struct umap_node *, sizeof(struct umap_node), M_TEMP, M_WAITOK);
E 3
I 3
	MALLOC(xp, struct umap_node *, sizeof(struct umap_node),
	    M_TEMP, M_WAITOK);
E 3
	vp->v_type = lowervp->v_type;
	xp->umap_vnode = vp;
	vp->v_data = xp;
	xp->umap_lowervp = lowervp;
	/*
	 * Before we insert our new node onto the hash chains,
	 * check to see if someone else has beaten us to it.
	 * (We could have slept in MALLOC.)
	 */
	if (othervp = umap_node_find(lowervp)) {
		FREE(xp, M_TEMP);
		vp->v_type = VBAD;	/* node is discarded */
		vp->v_usecount = 0;	/* XXX */
		*vpp = othervp;
D 3
		return 0;
	};
E 3
I 3
		return (0);
	}
E 3
	VREF(lowervp);   /* Extra VREF will be vrele'd in umap_node_create */
D 10
	hd = umap_node_hash(lowervp);
	insque(xp, hd);
E 10
I 10
	hd = UMAP_NHASH(lowervp);
	LIST_INSERT_HEAD(hd, xp, umap_hash);
E 10
D 3
	return 0;
E 3
I 3
	return (0);
E 3
}


/*
E 2
 * Try to find an existing umap_node vnode refering
 * to it, otherwise make a new umap_node vnode which
 * contains a reference to the target vnode.
 */
int
umap_node_create(mp, targetvp, newvpp)
	struct mount *mp;
	struct vnode *targetvp;
	struct vnode **newvpp;
{
D 2
	struct umap_node *ap;
E 2
	struct vnode *aliasvp;

D 2
	ap = umap_node_find(mp, targetvp);

	if (ap) {
E 2
I 2
	if (aliasvp = umap_node_find(mp, targetvp)) {
E 2
		/*
		 * Take another reference to the alias vnode
		 */
#ifdef UMAPFS_DIAGNOSTIC
		vprint("umap_node_create: exists", ap->umap_vnode);
#endif
D 2
		aliasvp = ap->umap_vnode;
		VREF(aliasvp);
E 2
I 2
		/* VREF(aliasvp); */
E 2
	} else {
		int error;

		/*
		 * Get new vnode.
		 */
#ifdef UMAPFS_DIAGNOSTIC
		printf("umap_node_create: create new alias vnode\n");
#endif
D 2
		if (error = getnewvnode(VT_UFS, mp, umap_vnodeop_p, &aliasvp))
			return (error);	/* XXX: VT_LOFS above */

E 2
		/*
		 * Make new vnode reference the umap_node.
		 */
D 2
		umap_node_alloc(aliasvp, targetvp);
E 2
I 2
		if (error = umap_node_alloc(mp, targetvp, &aliasvp))
D 3
			return error;
E 3
I 3
			return (error);
E 3
E 2

		/*
		 * aliasvp is already VREF'd by getnewvnode()
		 */
	}

	vrele(targetvp);

#ifdef UMAPFS_DIAGNOSTIC
	vprint("umap_node_create: alias", aliasvp);
	vprint("umap_node_create: target", targetvp);
#endif

	*newvpp = aliasvp;
	return (0);
}
I 3

E 3
#ifdef UMAPFS_DIAGNOSTIC
int umap_checkvp_barrier = 1;
struct vnode *
umap_checkvp(vp, fil, lno)
	struct vnode *vp;
	char *fil;
	int lno;
{
	struct umap_node *a = VTOUMAP(vp);
#if 0
	/*
	 * Can't do this check because vop_reclaim runs
	 * with funny vop vector.
	 */
	if (vp->v_op != umap_vnodeop_p) {
		printf ("umap_checkvp: on non-umap-node\n");
		while (umap_checkvp_barrier) /*WAIT*/ ;
		panic("umap_checkvp");
D 3
	};
E 3
I 3
	}
E 3
#endif
	if (a->umap_lowervp == NULL) {
		/* Should never happen */
		int i; u_long *p;
		printf("vp = %x, ZERO ptr\n", vp);
		for (p = (u_long *) a, i = 0; i < 8; i++)
			printf(" %x", p[i]);
		printf("\n");
		/* wait for debugger */
		while (umap_checkvp_barrier) /*WAIT*/ ;
		panic("umap_checkvp");
	}
	if (a->umap_lowervp->v_usecount < 1) {
		int i; u_long *p;
		printf("vp = %x, unref'ed lowervp\n", vp);
		for (p = (u_long *) a, i = 0; i < 8; i++)
			printf(" %x", p[i]);
		printf("\n");
		/* wait for debugger */
		while (umap_checkvp_barrier) /*WAIT*/ ;
		panic ("umap with unref'ed lowervp");
D 3
	};
E 3
I 3
	}
E 3
#if 0
	printf("umap %x/%d -> %x/%d [%s, %d]\n",
	        a->umap_vnode, a->umap_vnode->v_usecount,
		a->umap_lowervp, a->umap_lowervp->v_usecount,
		fil, lno);
#endif
D 3
	return a->umap_lowervp;
E 3
I 3
	return (a->umap_lowervp);
E 3
}
#endif

/* umap_mapids maps all of the ids in a credential, both user and group. */

D 2
umap_mapids(credp,usermap,unentries,groupmap,gnentries)
E 2
I 2
D 7
umap_mapids(v_mount,credp)
E 7
I 7
void
umap_mapids(v_mount, credp)
E 7
	struct mount *v_mount;
E 2
	struct ucred *credp;
D 2
	int * usermap, groupmap;
	int unentries,gnentries;
E 2
{
D 2
	int i,gid,uid;
E 2
I 2
D 7
	int i,gid,uid,unentries,gnentries,*groupmap,*usermap;
E 7
I 7
D 9
	int i, unentries, gnentries, *groupmap, *usermap;
E 9
I 9
	int i, unentries, gnentries;
	u_long *groupmap, *usermap;
E 9
	uid_t uid;
	gid_t gid;
E 7
E 2

I 2
	unentries =  MOUNTTOUMAPMOUNT(v_mount)->info_nentries;
	usermap =  &(MOUNTTOUMAPMOUNT(v_mount)->info_mapdata[0][0]);
	gnentries =  MOUNTTOUMAPMOUNT(v_mount)->info_gnentries;
	groupmap =  &(MOUNTTOUMAPMOUNT(v_mount)->info_gmapdata[0][0]);

E 2
	/* Find uid entry in map */

D 7
	uid = umap_findid(credp->cr_uid,usermap,unentries);
E 7
I 7
	uid = (uid_t) umap_findid(credp->cr_uid, usermap, unentries);
E 7

D 7
	if (uid != -1) {
D 2
		credp->cr_ruid =
E 2
		credp->cr_uid =
			(u_short)uid;
	} else 
D 2
		credp->cr_ruid = credp->cr_uid = (u_short)NOBODY;
E 2
I 2
		credp->cr_uid = (u_short)NOBODY;
E 7
I 7
	if (uid != -1)
		credp->cr_uid = uid;
	else
		credp->cr_uid = (uid_t) NOBODY;
E 7
E 2

I 7
#ifdef notdef
	/* cr_gid is the same as cr_groups[0] in 4BSD */

E 7
	/* Find gid entry in map */

D 7
	gid = umap_findid(credp->cr_gid,groupmap,gnentries);
E 7
I 7
	gid = (gid_t) umap_findid(credp->cr_gid, groupmap, gnentries);
E 7

D 7
	if (gid != -1) {
D 2
		credp->cr_rgid =
E 2
		credp->cr_gid =
			(u_short)gid;
	} else 
D 2
		credp->cr_rgid = credp->cr_gid = (u_short)NULLGROUP;
E 2
I 2
		credp->cr_gid = (u_short)NULLGROUP;
E 7
I 7
	if (gid != -1)
		credp->cr_gid = gid;
	else
		credp->cr_gid = NULLGROUP;
#endif
E 7
E 2

	/* Now we must map each of the set of groups in the cr_groups 
		structure. */

	i = 0;
D 7
	while (credp->cr_groups[i] != 0)
	{
		gid = umap_findid(credp->cr_groups[i],groupmap,
			gnentries);
		
		if (gid != -1) 
			credp->cr_groups[i++] = (u_short)gid;
		else
			credp->cr_groups[i++] = (u_short)NULLGROUP;
E 7
I 7
	while (credp->cr_groups[i] != 0) {
		gid = (gid_t) umap_findid(credp->cr_groups[i],
					groupmap, gnentries);
E 7

I 7
		if (gid != -1)
			credp->cr_groups[i++] = gid;
		else
			credp->cr_groups[i++] = NULLGROUP;
E 7
	}
D 7
}

/* umap_findid is called by various routines in umap_vnodeops.c to
 * find a user or group id in a map.
 */

umap_findid(id,map,nentries)
	ushort id;
	int map[][2];
	int nentries;
{
	int i;

	/* Find uid entry in map */
	i = 0;
	while ((i<nentries) && ((u_short)(map[i][0] ) != id))
		i++;

	if ( i < nentries )
		return (map[i][1]);
	else
		return (-1);

}

/* umap_reverse_findid is called by umap_getattr() in umap_vnodeops.c to
 * find a user or group id in a map, in reverse.
 */

umap_reverse_findid(id,map,nentries)
	ushort id;
	int map[][2];
	int nentries;
{
	int i;

	/* Find uid entry in map */
	i = 0;
	while ((i<nentries) && ((u_short)(map[i][1] ) != id))
		i++;

	if ( i < nentries )
		return (map[i][0]);
	else
		return (-1);

E 7
}
D 3

E 3
E 1
