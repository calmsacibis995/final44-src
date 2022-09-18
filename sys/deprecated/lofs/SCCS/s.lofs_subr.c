h55174
s 00000/00001/00198
d D 8.5 94/01/21 19:52:43 bostic 9 8
c copyright typo
e
s 00005/00101/00194
d D 8.4 94/01/05 12:30:33 pendry 8 7
c remove debug code, general cleanup.  KNF.
e
s 00000/00002/00295
d D 8.3 94/01/04 21:34:15 bostic 7 6
c lint
e
s 00002/00002/00295
d D 8.2 94/01/04 06:54:26 pendry 6 5
c allocate private VT_ tags
e
s 00002/00002/00295
d D 8.1 93/06/10 23:42:48 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00296
d D 7.2 93/05/05 05:22:31 pendry 4 3
c add missing return value.
e
s 00001/00001/00296
d D 7.1 92/07/12 14:52:44 mckusick 3 2
c move to rev 7; new location; syntactic niggles
e
s 00003/00003/00294
d D 1.2 92/06/18 15:02:04 pendry 2 1
c fix data initialisation
e
s 00297/00000/00000
d D 1.1 92/06/03 14:19:09 pendry 1 0
c date and time created 92/06/03 14:19:09 by pendry
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
 * $Id: lofs_subr.c,v 1.11 1992/05/30 10:05:43 jsp Exp jsp $
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
D 3
#include <lofs/lofs.h>
E 3
I 3
#include <miscfs/lofs/lofs.h>
E 3

#define LOG2_SIZEVNODE 7		/* log2(sizeof struct vnode) */
#define	NLOFSCACHE 16
#define	LOFS_NHASH(vp) ((((u_long)vp)>>LOG2_SIZEVNODE) & (NLOFSCACHE-1))

/*
 * Loopback cache:
 * Each cache entry holds a reference to the target vnode
 * along with a pointer to the alias vnode.  When an
 * entry is added the target vnode is VREF'd.  When the
 * alias is removed the target vnode is vrele'd.
 */

/*
 * Cache head
 */
struct lofscache {
	struct lofsnode	*ac_forw;
	struct lofsnode	*ac_back;
};

static struct lofscache lofscache[NLOFSCACHE];

/*
 * Initialise cache headers
 */
I 8
int
E 8
lofs_init()
{
	struct lofscache *ac;
D 8
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_init\n");		/* printed during system boot */
#endif
E 8

	for (ac = lofscache; ac < lofscache + NLOFSCACHE; ac++)
		ac->ac_forw = ac->ac_back = (struct lofsnode *) ac;
I 8

	return (0);
E 8
}

/*
 * Compute hash list for given target vnode
 */
static struct lofscache *
lofs_hash(targetvp)
struct vnode *targetvp;
{
I 8

E 8
	return (&lofscache[LOFS_NHASH(targetvp)]);
}

/*
 * Make a new lofsnode node.
 * Vp is the alias vnode, lofsvp is the target vnode.
 * Maintain a reference to (targetvp).
 */
static void
lofs_alloc(vp, targetvp)
	struct vnode *vp;
	struct vnode *targetvp;
{
	struct lofscache *hd;
	struct lofsnode *a;

D 8
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_alloc(%x, %x)\n", vp, targetvp);
#endif

E 8
D 2
	MALLOC(vp->v_data, void *, sizeof(struct lofsnode), M_TEMP, M_WAITOK);
 	a = LOFSP(vp);
E 2
I 2
	MALLOC(a, struct lofsnode *, sizeof(struct lofsnode), M_TEMP, M_WAITOK);
E 2
	a->a_vnode = vp;
I 2
	vp->v_data = a;
E 2
	VREF(targetvp);
D 2
	LOFSP(vp)->a_lofsvp = targetvp;
E 2
I 2
	a->a_lofsvp = targetvp;
E 2
	hd = lofs_hash(targetvp);
	insque(a, hd);

D 8
#ifdef LOFS_DIAGNOSTIC
	vprint("alloc vp", vp);
	vprint("alloc targetvp", targetvp);
#endif
E 8
}

D 8
#ifdef LOFS_DIAGNOSTIC
void
lofs_flushmp(mp)
	struct mount *mp;
{
	struct lofscache *ac;
	int i = 0;
	struct lofsnode *roota;
E 8

D 8
	printf("lofs_flushmp(%x)\n", mp);

	roota = LOFSP(VFSTOLOFS(mp)->rootvp);

	for (ac = lofscache; ac < lofscache + NLOFSCACHE; ac++) {
		struct lofsnode *a = ac->ac_forw;
		while (a != (struct lofsnode *) ac) {
			if (a != roota && a->a_vnode->v_mount == mp) {
				struct vnode *vp = a->a_lofsvp;
				if (vp) {
					a->a_lofsvp = 0;
					vprint("would vrele", vp);
					/*vrele(vp);*/
					i++;
				}
			}
			a = a->a_forw;
		}
	}
	if (i > 0)
		printf("lofsnode: vrele'd %d aliases\n", i);
}
#endif

E 8
/*
 * Return alias for target vnode if already exists, else 0.
 */
static struct lofsnode *
lofs_find(mp, targetvp)
	struct mount *mp;
	struct vnode *targetvp;
{
	struct lofscache *hd;
	struct lofsnode *a;

D 8
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_find(mp = %x, target = %x)\n", mp, targetvp);
#endif

E 8
	/*
	 * Find hash base, and then search the (two-way) linked
	 * list looking for a lofsnode structure which is referencing
	 * the target vnode.  If found, the increment the lofsnode
	 * reference count (but NOT the target vnode's VREF counter).
	 */
	hd = lofs_hash(targetvp);

	for (a = hd->ac_forw; a != (struct lofsnode *) hd; a = a->a_forw) {
		if (a->a_lofsvp == targetvp && a->a_vnode->v_mount == mp) {
D 8
#ifdef LOFS_DIAGNOSTIC
			printf("lofs_find(%x): found (%x,%x)->%x\n",
				targetvp, mp, a->a_vnode, targetvp);
#endif
E 8
			return (a);
		}
	}

D 8
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_find(%x, %x): NOT found\n", mp, targetvp);
#endif

E 8
	return (0);
}

static int
lofs_alias(mp, targetvp, newvpp)
	struct mount *mp;
	struct vnode *targetvp;
	struct vnode **newvpp;
{
	struct lofsnode *ap;
	struct vnode *aliasvp;

	if (targetvp->v_type != VDIR || targetvp->v_op == lofs_vnodeop_p) {
		*newvpp = targetvp;
D 4
		return;
E 4
I 4
		return (0);
E 4
	}

	ap = lofs_find(mp, targetvp);

	if (ap) {
		/*
		 * Take another reference to the alias vnode
		 */
D 8
#ifdef LOFS_DIAGNOSTIC
		vprint("lofs_alias: exists", ap->a_vnode);
#endif
E 8
		aliasvp = ap->a_vnode;
		VREF(aliasvp);
	} else {
		int error;

		/*
		 * Get new vnode.
		 */
D 8
#ifdef LOFS_DIAGNOSTIC
		printf("lofs_alias: create new alias vnode\n");
#endif
E 8
D 6
		if (error = getnewvnode(VT_UFS, mp, lofs_vnodeop_p, &aliasvp))
			return (error);	/* XXX: VT_LOFS above */
E 6
I 6
		if (error = getnewvnode(VT_LOFS, mp, lofs_vnodeop_p, &aliasvp))
			return (error);
E 6

		/*
		 * Must be a directory
		 */
		aliasvp->v_type = VDIR;

		/*
		 * Make new vnode reference the lofsnode.
		 */
		lofs_alloc(aliasvp, targetvp);

		/*
		 * aliasvp is already VREF'd by getnewvnode()
		 */
	}

	vrele(targetvp);

D 8
#ifdef LOFS_DIAGNOSTIC
	vprint("lofs_alias alias", aliasvp);
	vprint("lofs_alias target", targetvp);
#endif

E 8
	*newvpp = aliasvp;
	return (0);
}

/*
 * Try to find an existing lofsnode vnode refering
 * to it, otherwise make a new lofsnode vnode which
 * contains a reference to the target vnode.
 */
I 8
int
E 8
make_lofs(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
D 7
	int error;
	struct vnode *aliasvp;
E 7
	struct vnode *targetvp;

D 8
#ifdef LOFS_DIAGNOSTIC
	printf("make_lofs(mp = %x, vp = %x\n", mp, *vpp);
#endif

E 8
	/*
	 * (targetvp) is locked at this point.
	 */
	targetvp = *vpp;

D 8
#ifdef LOFS_DIAGNOSTIC
	if (targetvp == 0)
		panic("make_lofs: null vp");
#endif

E 8
	/*
	 * Try to find an existing reference to the target vnodes.
	 */
	return (lofs_alias(mp, targetvp, vpp));
}

D 8
#ifdef LOFS_DIAGNOSTIC
struct vnode *
lofs_checkvp(vp, fil, lno)
	struct vnode *vp;
	char *fil;
	int lno;
{
	struct lofsnode *a = LOFSP(vp);
	if (a->a_lofsvp == 0) {
		int i; u_long *p;
		printf("vp = %x, ZERO ptr\n", vp);
#ifdef notdef
		for (p = (u_long *) a, i = 0; i < 8; i++)
			printf(" %x", p[i]);
		printf("\n");
		DELAY(2000000);
		panic("lofs_checkvp");
#endif
	}
	printf("aliasvp %x/%d -> %x/%d [%s, %d]\n",
		a->a_vnode, a->a_vnode->v_usecount,
		a->a_lofsvp, a->a_lofsvp ? a->a_lofsvp->v_usecount : -42,
		fil, lno);
	return a->a_lofsvp;
}
#endif
E 8
E 1
