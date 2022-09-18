h21270
s 00000/00001/00046
d D 8.4 94/01/21 19:53:27 bostic 7 6
c copyright typo
e
s 00000/00005/00047
d D 8.3 94/01/04 17:14:08 pendry 6 5
c use new VT_ value
e
s 00005/00000/00047
d D 8.2 94/01/04 06:54:32 pendry 5 4
c allocate private VT_ tags
e
s 00002/00002/00045
d D 8.1 93/06/10 23:46:38 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00047
d D 7.1 92/07/12 15:20:39 mckusick 3 2
c move to rev 7
e
s 00004/00003/00043
d D 1.2 92/07/12 09:02:02 pendry 2 1
c new cred structure
e
s 00046/00000/00000
d D 1.1 92/06/03 14:26:05 pendry 1 0
c date and time created 92/06/03 14:26:05 by pendry
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
 *
 * $Id: portal.h,v 1.3 1992/05/30 10:05:24 jsp Exp jsp $
 */

struct portal_args {
	char		*pa_config;	/* Config file */
	int		pa_socket;	/* Socket to server */
};

struct portal_cred {
D 2
	uid_t		pcr_uid;	/* From ucred */
	gid_t		pcr_gid;	/* From ucred */
E 2
I 2
	int		pcr_flag;		/* File open mode */
	uid_t		pcr_uid;		/* From ucred */
	short		pcr_ngroups;		/* From ucred */
	gid_t		pcr_groups[NGROUPS];	/* From ucred */
E 2
};
D 2

E 2

#ifdef KERNEL
I 5
D 6

#ifndef VT_PORTAL
#define VT_PORTAL VT_UFS
#endif

E 6
E 5
struct portalmount {
	struct vnode	*pm_root;	/* Root node */
	struct file	*pm_server;	/* Held reference to server socket */
};

struct portalnode {
	int		pt_size;	/* Length of Arg */
	char		*pt_arg;	/* Arg to send to server */
	int		pt_fileid;	/* cookie */
};

#define VFSTOPORTAL(mp)	((struct portalmount *)((mp)->mnt_data))
#define	VTOPORTAL(vp) ((struct portalnode *)(vp)->v_data)

#define PORTAL_ROOTFILEID	2

extern int (**portal_vnodeop_p)();
extern struct vfsops portal_vfsops;
#endif /* KERNEL */
E 1
