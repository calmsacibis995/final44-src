h31641
s 00000/00001/00044
d D 8.5 94/01/21 19:52:42 bostic 7 6
c copyright typo
e
s 00001/00005/00044
d D 8.4 94/01/05 12:30:32 pendry 6 5
c remove debug code, general cleanup.  KNF.
e
s 00000/00005/00049
d D 8.3 94/01/04 17:14:03 pendry 5 4
c use new VT_ value
e
s 00005/00000/00049
d D 8.2 94/01/04 06:54:25 pendry 4 3
c allocate private VT_ tags
e
s 00002/00002/00047
d D 8.1 93/06/10 23:42:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00049
d D 7.1 92/07/12 14:52:17 mckusick 2 1
c move to rev 7
e
s 00049/00000/00000
d D 1.1 92/06/03 14:19:08 pendry 1 0
c date and time created 92/06/03 14:19:08 by pendry
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
D 7
 * All rights reserved.
E 7
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: lofs.h,v 1.8 1992/05/30 10:05:43 jsp Exp jsp $
 */

struct lofs_args {
	char		*target;	/* Target of loopback  */
};

struct lofsmount {
	struct mount	*looped_vfs;
	struct vnode	*rootvp;	/* Reference to root lofsnode */
};

#ifdef KERNEL
I 4
D 5

#ifndef VT_LOFS
#define VT_LOFS VT_UFS
#endif

E 5
E 4
/*
 * A cache of vnode references
 */
struct lofsnode {
	struct lofsnode	*a_forw;	/* Hash chain */
	struct lofsnode	*a_back;
	struct vnode	*a_lofsvp;	/* Aliased vnode - VREFed once */
	struct vnode	*a_vnode;	/* Back pointer to vnode/lofsnode */
};

I 6
extern int lofs_init __P((void));
E 6
extern int make_lofs __P((struct mount *mp, struct vnode **vpp));

#define	VFSTOLOFS(mp) ((struct lofsmount *)((mp)->mnt_data))
#define	LOFSP(vp) ((struct lofsnode *)(vp)->v_data)
D 6
#ifdef LOFS_DIAGNOSTIC
extern struct vnode *lofs_checkvp __P((struct vnode *vp, char *fil, int lno));
#define	LOFSVP(vp) lofs_checkvp(vp, __FILE__, __LINE__)
#else
E 6
#define	LOFSVP(vp) (LOFSP(vp)->a_lofsvp)
D 6
#endif
E 6

extern int (**lofs_vnodeop_p)();
extern struct vfsops lofs_vfsops;
#endif /* KERNEL */
E 1
