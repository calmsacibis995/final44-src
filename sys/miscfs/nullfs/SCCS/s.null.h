h48846
s 00001/00002/00047
d D 8.3 94/08/20 15:58:27 mckusick 12 11
c update to use LIST hash structures
e
s 00000/00001/00049
d D 8.2 94/01/21 19:54:22 bostic 11 10
c copyright typo
e
s 00002/00002/00048
d D 8.1 93/06/10 23:46:02 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00050
d D 7.1 92/07/12 15:10:19 mckusick 9 8
c move to rev 7
e
s 00001/00002/00050
d D 1.7 92/07/11 15:24:14 heideman 8 7
c cleanup
e
s 00003/00002/00049
d D 1.6 92/07/11 08:46:07 heideman 7 6
c Working, with vnode caching.
e
s 00001/00000/00050
d D 1.5 92/07/10 23:17:42 heideman 6 5
c No refcount problems, but no caching.
e
s 00003/00003/00047
d D 1.4 92/07/10 13:46:22 heideman 5 4
c a working version: it does nothing, correctly
e
s 00002/00001/00048
d D 1.3 92/07/07 17:49:12 johnh 4 2
c a first draft
e
s 00002/00001/00048
d R 1.3 92/07/07 17:46:33 johnh 3 2
c first draft
e
s 00018/00018/00031
d D 1.2 92/07/07 14:07:42 johnh 2 1
c the great variable renaming
e
s 00049/00000/00000
d D 1.1 92/07/07 13:54:20 johnh 1 0
c date and time created 92/07/07 13:54:20 by johnh
e
u
U
f e 0
t
T
I 1
/*
D 10
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
D 11
 * All rights reserved.
E 11
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
D 8
 *	@(#)lofs.h	1.1 (Berkeley) 6/3/92
E 8
I 8
 *	%W% (Berkeley) %G%
E 8
 *
 * $Id: lofs.h,v 1.8 1992/05/30 10:05:43 jsp Exp jsp $
 */

D 2
struct lofs_args {
E 2
I 2
struct null_args {
E 2
	char		*target;	/* Target of loopback  */
};

D 2
struct lofsmount {
	struct mount	*looped_vfs;
	struct vnode	*rootvp;	/* Reference to root lofsnode */
E 2
I 2
struct null_mount {
	struct mount	*nullm_vfs;
	struct vnode	*nullm_rootvp;	/* Reference to root null_node */
E 2
};

#ifdef KERNEL
/*
 * A cache of vnode references
 */
D 2
struct lofsnode {
	struct lofsnode	*a_forw;	/* Hash chain */
	struct lofsnode	*a_back;
	struct vnode	*a_lofsvp;	/* Aliased vnode - VREFed once */
	struct vnode	*a_vnode;	/* Back pointer to vnode/lofsnode */
E 2
I 2
struct null_node {
D 12
	struct null_node	*null_forw;	/* Hash chain */
	struct null_node	*null_back;
E 12
I 12
	LIST_ENTRY(null_node)	null_hash;	/* Hash list */
E 12
D 7
	struct vnode	*null_lowervp;	/* Aliased vnode - VREFed once */
	struct vnode	*null_vnode;	/* Back pointer to vnode/null_node */
E 7
I 7
	struct vnode	        *null_lowervp;	/* VREFed once */
	struct vnode		*null_vnode;	/* Back pointer */
D 8
	int			null_isinactive;
E 8
E 7
E 2
};

D 2
extern int make_lofs __P((struct mount *mp, struct vnode **vpp));
E 2
I 2
D 5
extern int make_null_node __P((struct mount *mp, struct vnode **vpp));
E 5
I 5
extern int null_node_create __P((struct mount *mp, struct vnode *target, struct vnode **vpp));
E 5
E 2

D 2
#define	VFSTOLOFS(mp) ((struct lofsmount *)((mp)->mnt_data))
#define	LOFSP(vp) ((struct lofsnode *)(vp)->v_data)
#ifdef LOFS_DIAGNOSTIC
extern struct vnode *lofs_checkvp __P((struct vnode *vp, char *fil, int lno));
#define	LOFSVP(vp) lofs_checkvp(vp, __FILE__, __LINE__)
E 2
I 2
#define	MOUNTTONULLMOUNT(mp) ((struct null_mount *)((mp)->mnt_data))
D 4
#define	VTONULLNODE(vp) ((struct null_node *)(vp)->v_data)
E 4
I 4
#define	VTONULL(vp) ((struct null_node *)(vp)->v_data)
I 6
#define	NULLTOV(xp) ((xp)->null_vnode)
E 6
E 4
#ifdef NULLFS_DIAGNOSTIC
extern struct vnode *null_checkvp __P((struct vnode *vp, char *fil, int lno));
D 5
#define	NULLTOLOWERVP(vp) null_checkvp(vp, __FILE__, __LINE__)
E 5
I 5
#define	NULLVPTOLOWERVP(vp) null_checkvp((vp), __FILE__, __LINE__)
E 5
E 2
#else
D 2
#define	LOFSVP(vp) (LOFSP(vp)->a_lofsvp)
E 2
I 2
D 5
#define	NULLTOLOWERVP(vp) (VTONULLNODE(vp)->null_lowervp)
E 5
I 5
#define	NULLVPTOLOWERVP(vp) (VTONULL(vp)->null_lowervp)
E 5
E 2
#endif

D 2
extern int (**lofs_vnodeop_p)();
extern struct vfsops lofs_vfsops;
E 2
I 2
extern int (**null_vnodeop_p)();
extern struct vfsops null_vfsops;
E 2
#endif /* KERNEL */
I 4
D 9

E 9
E 4
E 1
