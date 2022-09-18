/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mount.h,v $
 * Revision 2.2  89/07/12  00:18:15  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)mount.h 2.10 88/02/08 SMI; from UCB 4.4 82/07/19	*/

/*
 * Mount structure.
 * One allocated on every ufs mount.
 * Used to find the super block.
 */
struct	mount {
	struct vfs	*m_vfsp;	/* vfs structure for this filesystem */
	dev_t		m_dev;		/* device mounted */
	struct vnode	*m_devvp;	/* vnode for block device mounted */
	struct buf	*m_bufp;	/* pointer to superblock */
	struct inode	*m_qinod;	/* QUOTA: pointer to quota file */
	u_short		m_qflags;	/* QUOTA: filesystem flags */
	u_long		m_btimelimit;	/* QUOTA: block time limit */
	u_long		m_ftimelimit;	/* QUOTA: file time limit */
	struct mount	*m_nxt;		/* linked list of all mounts */
};

#ifdef KERNEL
/*
 * Convert vfs ptr to mount ptr.
 */
#define VFSTOM(VFSP)	((struct mount *)((VFSP)->vfs_data))

/*
 * mount table
 */
extern struct mount	*mounttab;

/*
 * Operations
 */
struct mount *getmp();
#endif
