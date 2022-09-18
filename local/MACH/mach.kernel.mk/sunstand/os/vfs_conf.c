/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vfs_conf.c,v $
 * Revision 2.2  89/07/12  01:15:40  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)vfs_conf.c 1.5 88/02/08 SMI	*/

#include <sys/param.h>
#include <sys/vfs.h>
#include <sys/bootconf.h>

#ifdef UFS
extern	struct vfsops ufs_vfsops;	/* XXX Should be ifdefed */
#endif

#ifdef NFS
extern	struct vfsops nfs_vfsops;
#endif

#ifdef PCFS
extern	struct vfsops pcfs_vfsops;
#endif

struct vfssw vfssw[] = {
#ifdef UFS
	"4.2", &ufs_vfsops,	/* 0 = MOUNT_UFS */
#else
	(char *)0, (struct vfsops *)0,
#endif
#ifdef NFS
	"nfs", &nfs_vfsops,	/* 1 = MOUNT_NFS */
#else
	(char *)0, (struct vfsops *)0,
#endif
#ifdef PCFS
	"pc", &pcfs_vfsops,	/* 2 = MOUNT_PC */
#else
	(char *)0, (struct vfsops *)0,
#endif
};

/*
 * Stolen from ../sun/bootconf.c
 */

struct bootobj rootfs = {
	{ "",           "",     0, 0, (struct vnode *)0 },
};
