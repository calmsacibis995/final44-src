/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mount.h,v $
 * Revision 2.6  89/04/22  15:32:03  gm0w
 * 	Removed MACH_VFS changes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.5  89/03/09  22:05:51  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  17:54:53  gm0w
 * 	Made the MACH_VFS conditionals always true outside
 * 	of the kernel. Made the VICE conditionals always
 * 	false outside the kernel for X75 binary compatibility.
 * 	(needs to be fixed )
 * 	[89/02/14            mrt]
 * 
 * Revision 2.3  89/01/18  01:17:33  jsb
 * 	Vnode support: fairly massive changes.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.2  88/08/24  02:36:24  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:17:44  mwyoung]
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merge VICE changes -- include vice.h and change to #if VICE.
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  added fields to mount entries to allow determination
 *	of whether file system is handled by Venus or not.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mount.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_MOUNT_H_
#define _SYS_MOUNT_H_

#ifdef	KERNEL
#include <vice.h>
#endif	KERNEL

#include <sys/types.h>

/*
 * Mount structure.
 * One allocated on every mount.
 * Used to find the super block.
 */
struct	mount
{
	struct	vfs *m_vfsp;	/* fs pointer for this filesystem */
	dev_t	m_dev;		/* device mounted */
	struct	buf *m_bufp;	/* pointer to superblock */
	struct	inode *m_devp;	/* inode pointer for block device i/o */
	struct	inode *m_inodp;	/* pointer to mounted on inode */
	struct	inode *m_qinod;	/* QUOTA: pointer to quota file */
	u_short	m_qflags;	/* QUOTA: filesystem flags */
	u_long	m_btimelimit;	/* QUOTA: block time limit */
	u_long	m_ftimelimit;	/* QUOTA: file time limit */
#if	VICE
	char	m_remote;	/* remote file system */
	char	m_mounted;	/* TRUE if this structure is in use */
	struct  inode *m_parent;/* The parent directory to the mounted on 
				   inode.  Bogus method of handling chdir .. 
				   out of remote file system */
#endif	VICE
};

#ifdef	KERNEL
#include <sys/param.h>		/* for NMOUNT */

/*
 * mount table
 */
extern struct	mount mount[NMOUNT];
extern struct	mount *getmp();
#endif	KERNEL
#endif	_SYS_MOUNT_H_
