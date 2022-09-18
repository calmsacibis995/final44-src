h31355
s 00000/00009/00055
d D 8.8 95/04/03 18:30:52 mckusick 12 11
c move out vnops
e
s 00010/00001/00054
d D 8.7 95/03/29 00:05:29 mckusick 11 10
c cleanups; getnewfsid => vfs_getnewfsid; add fdesc_sysctl
e
s 00001/00002/00054
d D 8.6 94/08/20 15:53:48 mckusick 10 9
c update to use queue.h
e
s 00000/00001/00056
d D 8.5 94/01/21 19:51:11 bostic 9 8
c copyright typo
e
s 00005/00000/00052
d D 8.4 94/01/05 12:03:20 pendry 8 7
c handle case where fdesc is mounted twice or more
c general cleanup, remove debug code, lint + KNF.
e
s 00000/00005/00052
d D 8.3 94/01/04 17:14:11 pendry 7 6
c use new VT_ value
e
s 00005/00000/00052
d D 8.2 94/01/04 06:54:08 pendry 6 5
c allocate private VT_ tags
e
s 00002/00002/00050
d D 8.1 93/06/10 23:35:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00003/00027
d D 7.2 93/04/22 02:56:51 pendry 4 3
c merge in new version.
c this time it implements a subset of the /dev namespace
e
s 00000/00000/00030
d D 7.1 92/07/12 14:53:49 mckusick 3 2
c move to rev 7
e
s 00000/00009/00030
d D 1.2 92/07/12 10:08:05 pendry 2 1
c remove private dir structure
e
s 00039/00000/00000
d D 1.1 92/06/03 14:01:18 pendry 1 0
c date and time created 92/06/03 14:01:18 by pendry
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
D 4
 * $Id: fdesc.h,v 1.5 1992/05/30 10:05:34 jsp Exp jsp $
E 4
I 4
 * $Id: fdesc.h,v 1.8 1993/04/06 15:28:33 jsp Exp $
E 4
 */

#ifdef KERNEL
I 6
D 7

#ifndef VT_FDESC
#define VT_FDESC VT_UFS
#endif

E 7
E 6
struct fdescmount {
	struct vnode	*f_root;	/* Root node */
};

I 4
#define FD_ROOT		2
#define FD_DEVFD	3
#define FD_STDIN	4
#define FD_STDOUT	5
#define FD_STDERR	6
#define FD_CTTY		7
#define FD_DESC		8
#define FD_MAX		12

typedef enum {
	Froot,
	Fdevfd,
	Fdesc,
	Flink,
	Fctty
} fdntype;

E 4
struct fdescnode {
I 8
D 10
	struct fdescnode *fd_forw;	/* Hash chain */
	struct fdescnode *fd_back;
E 10
I 10
	LIST_ENTRY(fdescnode) fd_hash;	/* Hash list */
E 10
	struct vnode	*fd_vnode;	/* Back ptr to vnode */
E 8
D 4
	unsigned	f_fd;			/* Fd to be dup'ed */
E 4
I 4
	fdntype		fd_type;	/* Type of this node */
	unsigned	fd_fd;		/* Fd to be dup'ed */
	char		*fd_link;	/* Link to fd/n */
	int		fd_ix;		/* filesystem index */
E 4
D 2
	/*int		f_isroot;*/		/* Is this the root */
E 2
};

#define VFSTOFDESC(mp)	((struct fdescmount *)((mp)->mnt_data))
#define	VTOFDESC(vp) ((struct fdescnode *)(vp)->v_data)

I 4
extern dev_t devctty;
I 8
D 11
extern int fdesc_init __P((void));
E 11
I 11
extern int fdesc_init __P((struct vfsconf *));
E 11
extern int fdesc_root __P((struct mount *, struct vnode **));
E 8
extern int fdesc_allocvp __P((fdntype, int, struct mount *, struct vnode **));
I 11
D 12
#define fdesc_fhtovp ((int (*) __P((struct mount *, struct fid *, \
	    struct mbuf *, struct vnode **, int *, struct ucred **)))eopnotsupp)
#define fdesc_quotactl ((int (*) __P((struct mount *, int, uid_t, caddr_t, \
	    struct proc *)))eopnotsupp)
#define fdesc_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
	    size_t, struct proc *)))eopnotsupp)
#define fdesc_vget ((int (*) __P((struct mount *, ino_t, struct vnode **))) \
	    eopnotsupp)
#define fdesc_vptofh ((int (*) __P((struct vnode *, struct fid *)))eopnotsupp)
E 12
E 11
E 4
D 2
#define	MAXNAMLEN	255

struct	readdir {
	u_long	d_ino;			/* inode number of entry */
	u_short	d_reclen;		/* length of this record */
	u_short	d_namlen;		/* length of string in d_name */
	char	d_name[MAXNAMLEN + 1];	/* name with length <= MAXNAMLEN */
};
E 2
extern int (**fdesc_vnodeop_p)();
extern struct vfsops fdesc_vfsops;
#endif /* KERNEL */
E 1
