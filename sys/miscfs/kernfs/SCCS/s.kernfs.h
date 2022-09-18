h58429
s 00011/00000/00030
d D 8.6 95/03/29 00:13:14 mckusick 9 8
c cleanups; getnewfsid => vfs_getnewfsid; add fdesc_sysctl
e
s 00001/00001/00029
d D 8.5 94/06/15 10:41:41 pendry 8 7
c merge netbsd modifications
e
s 00000/00001/00030
d D 8.4 94/01/21 19:56:24 bostic 7 6
c copyright typo
e
s 00000/00005/00031
d D 8.3 94/01/04 17:13:56 pendry 6 5
c use new VT_ value
e
s 00005/00000/00031
d D 8.2 94/01/04 06:54:15 pendry 5 4
c allocate private VT_ tags
e
s 00002/00002/00029
d D 8.1 93/06/10 23:38:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00029
d D 7.3 92/07/19 05:00:17 pendry 3 2
c added default mount point
e
s 00001/00000/00028
d D 7.2 92/07/19 04:56:04 pendry 2 1
c added raw root device support to kernfs
e
s 00028/00000/00000
d D 7.1 92/07/18 16:42:23 pendry 1 0
c date and time created 92/07/18 16:42:23 by pendry
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
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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
 */

I 3
#define	_PATH_KERNFS	"/kern"		/* Default mountpoint */

E 3
#ifdef KERNEL
I 5
D 6

#ifndef VT_KERNFS
#define VT_KERNFS VT_UFS
#endif

E 6
E 5
struct kernfs_mount {
	struct vnode	*kf_root;	/* Root node */
};

struct kernfs_node {
	struct kern_target *kf_kt;
};

#define VFSTOKERNFS(mp)	((struct kernfs_mount *)((mp)->mnt_data))
#define	VTOKERN(vp) ((struct kernfs_node *)(vp)->v_data)

I 9
#define kernfs_fhtovp ((int (*) __P((struct mount *, struct fid *, \
	    struct mbuf *, struct vnode **, int *, struct ucred **)))eopnotsupp)
#define kernfs_quotactl ((int (*) __P((struct mount *, int, uid_t, caddr_t, \
	    struct proc *)))eopnotsupp)
#define kernfs_sync ((int (*) __P((struct mount *, int, struct ucred *, \
	    struct proc *)))nullop)
#define kernfs_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
	    size_t, struct proc *)))eopnotsupp)
#define kernfs_vget ((int (*) __P((struct mount *, ino_t, struct vnode **))) \
	    eopnotsupp)
#define kernfs_vptofh ((int (*) __P((struct vnode *, struct fid *)))eopnotsupp)
E 9
extern int (**kernfs_vnodeop_p)();
extern struct vfsops kernfs_vfsops;
I 2
D 8
extern struct vnode *rrootvp;
E 8
I 8
extern dev_t rrootdev;
E 8
E 2
#endif /* KERNEL */
E 1
