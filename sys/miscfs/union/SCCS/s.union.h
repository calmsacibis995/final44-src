h41967
s 00002/00001/00101
d D 8.9 94/12/10 13:03:06 pendry 20 19
c fix readdir for no-linear stacks
e
s 00002/00000/00100
d D 8.8 94/09/29 08:15:37 pendry 19 18
c add union_dowhiteout
e
s 00002/00000/00098
d D 8.7 94/07/28 03:39:20 pendry 18 17
c changes for whiteouts and union filesystem
e
s 00001/00000/00097
d D 8.6 94/06/17 09:43:16 pendry 17 16
c keep track of parent union node, so allowing .. to refer to
e
s 00004/00002/00093
d D 8.5 94/05/17 19:29:57 pendry 16 15
c abstract copyup function
e
s 00003/00000/00092
d D 8.4 94/05/07 13:18:23 pendry 15 14
c keep track of vnode size changes.
e
s 00002/00001/00090
d D 8.3 94/04/28 06:31:12 pendry 14 13
c add caching flag
e
s 00001/00000/00090
d D 8.2 94/02/17 16:35:56 pendry 13 12
c implement new access policy
c fixup locking for UNMNT_BELOW.
e
s 00000/00000/00090
d D 8.1 94/02/10 18:50:24 pendry 12 11
c up to v8
e
s 00003/00008/00087
d D 2.2 94/02/10 18:38:10 pendry 11 10
c cleanup & lint
e
s 00011/00002/00084
d D 2.1 94/02/10 14:08:22 pendry 10 9
c new locking scheme
e
s 00006/00000/00080
d D 1.9 94/02/08 16:15:59 pendry 9 8
c checkpoint
e
s 00003/00000/00077
d D 1.8 94/02/07 21:35:13 pendry 8 7
c checkpoint
e
s 00005/00001/00072
d D 1.7 94/02/07 16:13:09 pendry 7 6
c checkpoint
e
s 00005/00006/00068
d D 1.6 94/02/04 17:50:30 pendry 6 5
c checkpoint
e
s 00008/00001/00066
d D 1.5 94/02/03 20:08:01 pendry 5 4
c checkpoint
e
s 00002/00002/00065
d D 1.4 94/02/03 12:25:15 pendry 4 3
c checkpoint
e
s 00001/00001/00066
d D 1.3 94/02/01 20:45:31 pendry 3 2
c checkpoint
e
s 00000/00000/00067
d D 1.2 94/02/01 17:11:08 pendry 2 1
c checkpoint
e
s 00067/00000/00000
d D 1.1 94/01/28 09:42:42 pendry 1 0
c date and time created 94/01/28 09:42:42 by pendry
e
u
U
t
T
I 1
/*
 * Copyright (c) 1994 The Regents of the University of California.
 * Copyright (c) 1994 Jan-Simon Pendry.
 * All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct union_args {
	char		*target;	/* Target of loopback  */
I 9
	int		mntflags;	/* Options on the mount */
E 9
};
I 9

#define UNMNT_ABOVE	0x0001		/* Target appears below mount point */
#define UNMNT_BELOW	0x0002		/* Target appears below mount point */
#define UNMNT_REPLACE	0x0003		/* Target replaces mount point */
#define UNMNT_OPMASK	0x0003
E 9

struct union_mount {
	struct vnode	*um_uppervp;
	struct vnode	*um_lowervp;
	struct ucred	*um_cred;	/* Credentials of user calling mount */
I 6
	int		um_cmode;	/* cmask from mount process */
I 13
	int		um_op;		/* Operation mode */
E 13
E 6
};

D 6
/* begin XXX */
#define VT_UNION VT_LOFS
/*#define MOUNT_UNION 15*/
/* end XXX */

E 6
#ifdef KERNEL

/*
 * DEFDIRMODE is the mode bits used to create a shadow directory.
 */
#define VRWXMODE (VREAD|VWRITE|VEXEC)
#define VRWMODE (VREAD|VWRITE)
#define UN_DIRMODE ((VRWXMODE)|(VRWXMODE>>3)|(VRWXMODE>>6))
#define UN_FILEMODE ((VRWMODE)|(VRWMODE>>3)|(VRWMODE>>6))

/*
 * A cache of vnode references
 */
struct union_node {
D 11
	struct union_node	*un_next;	/* Hash chain */
E 11
I 11
	LIST_ENTRY(union_node)	un_cache;	/* Hash chain */
E 11
I 4
	struct vnode		*un_vnode;	/* Back pointer */
E 4
	struct vnode	        *un_uppervp;	/* overlaying object */
	struct vnode	        *un_lowervp;	/* underlying object */
	struct vnode		*un_dirvp;	/* Parent dir of uppervp */
I 17
	struct vnode		*un_pvp;	/* Parent vnode */
E 17
D 4
	struct vnode		*un_vnode;	/* Back pointer */
E 4
	char			*un_path;	/* saved component name */
I 6
D 7
	int			un_open;	/* # of opens on lowervp */
E 7
I 7
	int			un_hash;	/* saved un_path hash value */
	int			un_openl;	/* # of opens on lowervp */
E 7
E 6
D 14
	int			un_flags;
E 14
I 14
	unsigned int		un_flags;
I 20
	struct vnode		**un_dircache;	/* cached union stack */
E 20
I 15
	off_t			un_uppersz;	/* size of upper object */
	off_t			un_lowersz;	/* size of lower object */
E 15
E 14
I 7
#ifdef DIAGNOSTIC
E 7
	pid_t			un_pid;
I 7
#endif
E 7
};

D 10
#define UN_WANT 0x01
#define UN_LOCKED 0x02
E 10
I 10
#define UN_WANT		0x01
#define UN_LOCKED	0x02
#define UN_ULOCK	0x04		/* Upper node is locked */
#define UN_KLOCK	0x08		/* Keep upper node locked on vput */
I 14
#define UN_CACHED	0x10		/* In union cache */
E 14

D 11
#define LOCKUVP(un) \
		(((un)->un_flags & UN_ULOCK) ? \
		  (0) : \
		  (((un)->un_flags |= UN_ULOCK), VOP_LOCK((un)->un_uppervp)))
#define UNLOCKUVP(un) \
		((un)->un_flags &= ~UN_ULOCK)
E 10

E 11
D 4
extern int union_node_create __P((struct mount *mp, struct vnode *target, struct vnode **vpp));
E 4
I 4
D 5
extern int union_allocvp __P((struct vnode **, struct mount *, struct vnode *, struct vnode *, struct componentname *, struct vnode *, struct vnode *));
E 5
I 5
extern int union_allocvp __P((struct vnode **, struct mount *,
				struct vnode *, struct vnode *,
				struct componentname *, struct vnode *,
D 20
				struct vnode *));
E 20
I 20
				struct vnode *, int));
E 20
D 16
extern int union_copyfile __P((struct proc *, struct ucred *,
				struct vnode *, struct vnode *));
E 16
I 16
extern int union_copyfile __P((struct vnode *, struct vnode *,
					struct ucred *, struct proc *));
extern int union_copyup __P((struct union_node *, int, struct ucred *,
				struct proc *));
I 19
extern int union_dowhiteout __P((struct union_node *, struct ucred *,
					struct proc *));
E 19
E 16
I 6
extern int union_mkshadow __P((struct union_mount *, struct vnode *,
				struct componentname *, struct vnode **));
I 18
extern int union_mkwhiteout __P((struct union_mount *, struct vnode *,
				struct componentname *, char *));
E 18
E 6
extern int union_vn_create __P((struct vnode **, struct union_node *,
D 6
				int, struct proc *));
E 6
I 6
				struct proc *));
I 8
extern int union_cn_close __P((struct vnode *, int, struct ucred *,
				struct proc *));
E 8
I 7
extern void union_removed_upper __P((struct union_node *un));
I 8
extern struct vnode *union_lowervp __P((struct vnode *));
I 11
extern void union_newlower __P((struct union_node *, struct vnode *));
extern void union_newupper __P((struct union_node *, struct vnode *));
I 15
extern void union_newsize __P((struct vnode *, off_t, off_t));
E 15
E 11
E 8
E 7
E 6
E 5
E 4

#define	MOUNTTOUNIONMOUNT(mp) ((struct union_mount *)((mp)->mnt_data))
#define	VTOUNION(vp) ((struct union_node *)(vp)->v_data)
#define	UNIONTOV(un) ((un)->un_vnode)
#define	LOWERVP(vp) (VTOUNION(vp)->un_lowervp)
D 3
#define	UPPERVP(vp) (VTOUNION(vp)->un_lowervp)
E 3
I 3
#define	UPPERVP(vp) (VTOUNION(vp)->un_uppervp)
E 3
#define OTHERVP(vp) (UPPERVP(vp) ? UPPERVP(vp) : LOWERVP(vp))

extern int (**union_vnodeop_p)();
extern struct vfsops union_vfsops;
#endif /* KERNEL */
E 1
