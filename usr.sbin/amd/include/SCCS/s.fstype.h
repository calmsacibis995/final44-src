h05679
s 00002/00002/00120
d D 8.1 93/06/06 11:58:28 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00117
d D 5.4 92/02/09 08:44:34 pendry 4 3
c merge in new release
e
s 00003/00002/00115
d D 5.3 91/05/12 16:00:47 pendry 3 2
c checkpoint for network tape
e
s 00011/00002/00106
d D 5.2 91/03/17 13:41:04 pendry 2 1
c from amd5.3 alpha11
e
s 00108/00000/00000
d D 5.1 90/07/19 15:39:27 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: fstype.h,v 5.2 90/06/23 22:20:30 jsp Rel $
E 2
I 2
D 3
 * $Id: fstype.h,v 5.2.1.2 90/11/04 23:17:38 jsp Exp $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: fstype.h,v 5.2.1.3 91/05/07 22:19:21 jsp Alpha $
E 4
I 4
 * $Id: fstype.h,v 5.2.2.1 1992/02/09 15:09:57 jsp beta $
E 4
 *
E 3
 */

/*
 * File system types
 */

/*
 * Automount File System
 */
#define HAS_AFS
extern am_ops	afs_ops;	/* Automount file system (this!) */
I 2
extern am_ops	toplvl_ops;	/* Top-level automount file system */
extern am_ops	root_ops;	/* Root file system */
E 2
extern qelem	afs_srvr_list;
extern fserver *find_afs_srvr P((mntfs*));

D 2

E 2
/*
 * Direct Automount File System
 */
#define	HAS_DFS
extern am_ops	dfs_ops;	/* Direct Automount file system (this too) */

/*
 * Error File System
 */
#define HAS_EFS
extern am_ops	efs_ops;	/* Error file system */

/*
 * Inheritance File System
 */
#define HAS_IFS
extern am_ops	ifs_ops;	/* Inheritance file system */

/*
 * Loopback File System
 * LOFS is optional - you can compile without it.
 */
#ifdef OS_HAS_LOFS
/*
 * Most systems can't support this, and in
 * any case most of the functionality is
 * available with Symlink FS.  In fact,
 * lofs_ops is not yet available.
 */
#define HAS_LOFS
extern am_ops lofs_ops;
#endif

/*
 * Netw*rk File System
 * Good, slow, NFS.
 * NFS host - a whole tree
 */
#define HAS_NFS
#define	HAS_HOST
I 2
#define HAS_NFSX
E 2
extern am_ops	nfs_ops;	/* NFS */
I 2
extern am_ops	nfsx_ops;	/* NFS X */
E 2
extern am_ops	host_ops;	/* NFS host */
#ifdef HOST_EXEC
extern char	*host_helper;	/* "/usr/local/etc/amd-host" */
#endif
extern qelem	nfs_srvr_list;
extern fserver *find_nfs_srvr P((mntfs*));

/*
 * Program File System
 * PFS is optional - you can compile without it.
 * This is useful for things like RVD.
 */
#define HAS_PFS
extern am_ops	pfs_ops;	/* PFS */

/*
 * Translucent File System
 * TFS is optional - you can compile without it.
 * This is just plain cute.
 */
#ifdef notdef
extern am_ops	tfs_ops;	/* TFS */
#endif
#undef	HAS_TFS

/*
 * Un*x File System
 * Normal local disk file system.
 */
#define HAS_UFS
extern am_ops	ufs_ops;	/* Un*x file system */

/*
 * Symbolic-link file system
 * A "filesystem" which is just a symbol link.
I 4
 *
 * sfsx also checks that the target of the link exists.
E 4
 */
#define HAS_SFS
extern am_ops	sfs_ops;	/* Symlink FS */
I 4
#define HAS_SFSX
extern am_ops	sfsx_ops;	/* Symlink FS with existence check */
E 4
I 2

/*
 * Union file system
 */
#define	HAS_UNION_FS
extern am_ops	union_ops;	/* Union FS */
E 2
E 1
