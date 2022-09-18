/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	vfs_conf.c,v $
 * Revision 2.7  90/07/03  16:55:51  mrt
 * 	Added VFS and Vnode entry points for the Coda file system.
 * 	[90/05/23            dcs]
 * 
 * Revision 2.6  89/08/02  08:11:46  jsb
 * 	Eliminated MACH conditionals.
 * 	[89/07/31  16:05:08  jsb]
 * 
 * Revision 2.5  89/04/22  15:34:14  gm0w
 * 	Added vnode ops dispatch table.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  22:44:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:12:58  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:25:16  jsb
 * 	Include file references; added entry in vfssw for afs_vfsops.
 * 	[89/01/17  15:57:41  jsb]
 * 
 * 13-Jul-88  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	Added afs support.
 *
 * 26-Oct-87  Peter King (king) at NeXT
 *	Original Sun source.
 */ 

#include <mach_afs.h>
#include <mach_cfs.h>
#include <mach_nfs.h>

/* @(#)vfs_conf.c	1.1 87/06/02 3.2/4.3NFSSRC */
/*	@(#)vfs_conf.c 1.1 86/09/25 SMI	*/

#include <sys/param.h>
#include <sys/inode.h>

extern	struct vfsops ufs_vfsops;	/* XXX Should be ifdefed */

#if	MACH_NFS
extern	struct vfsops nfs_vfsops;
#endif	MACH_NFS

#if	MACH_AFS
extern struct vfsops afs_vfsops;
#endif	MACH_AFS

#ifdef	PCFS
extern	struct vfsops pcfs_vfsops;
#endif

#if	NMACH_CFS
extern struct vfsops cfs_vfsops;
#endif	NMACH_CFS

struct vfsops *vfssw[] = {
	&ufs_vfsops,		/* 0 = MOUNT_UFS */
#if	MACH_NFS
	&nfs_vfsops,		/* 1 = MOUNT_NFS */
#else	MACH_NFS
	(struct vfsops *)0,
#endif	MACH_NFS
#if	PCFS
	&pcfs_vfsops,		/* 2 = MOUNT_PC */
#else	PCFS
	(struct vfsops *)0,
#endif	PCFS
#if	MACH_AFS
	&afs_vfsops,		/* 3 = MOUNT_AFS */
#else	MACH_AFS
	(struct vfsops *)0,
#endif	MACH_AFS
#if	NMACH_CFS
	&cfs_vfsops,		/* 4 = MOUNT_CFS */
#else	NMACH_CFS
	(struct vfsops *)0,
#endif	NMACH_CFS
};

extern struct vnodeops ufs_vnodeops;

#if	MACH_NFS
extern struct vnodeops nfs_vnodeops;
#endif	MACH_NFS

#if	MACH_AFS
extern struct vnodeops afs_vnodeops;
#endif	MACH_AFS

extern struct vnodeops dev_vnode_ops;

extern struct vnodeops spec_vnodeops;

#if	NMACH_CFS
extern struct vnodeops cfs_vnodeops;
#endif	NMACH_CFS

struct vnodeops *vnodesw[] = {
	&ufs_vnodeops,		/* 0 = ITYPE_UFS */
#if	MACH_NFS
	&nfs_vnodeops,		/* 1 = ITYPE_NFS */
#else	MACH_NFS
	(struct vnodeops *)0,
#endif	MACH_NFS
#if	MACH_AFS
	&afs_vnodeops,		/* 2 = ITYPE_AFS */
#else	MACH_AFS
	(struct vnodeops *)0,
#endif	MACH_AFS
	&dev_vnode_ops,		/* 3 = ITYPE_BDEV */
	&spec_vnodeops,		/* 4 = ITYPE_SPEC */
#if	NMACH_CFS
	&cfs_vnodeops,		/* 5 = ITYPE_CFS */
#else	NMACH_CFS
	(struct vnodeops *)0,
#endif	NMACH_CFS	
};
