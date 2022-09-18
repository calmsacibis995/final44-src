/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	snode.h,v $
 * Revision 2.6  89/08/02  08:09:41  jsb
 * 	Declare specfs zones.
 * 	[89/07/31  16:45:48  jsb]
 * 
 * Revision 2.5  89/04/22  15:30:24  gm0w
 * 	Minor changes for HC.
 * 	[89/04/22            gm0w]
 * 	Updated for new inode header code.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  21:01:27  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:17:05  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:08:49  jsb
 * 	Include file references.
 * 	[89/01/17  15:06:36  jsb]
 * 
 */
/* @(#)snode.h	1.2 87/06/30 3.2/4.3NFSSRC */
/*      @(#)snode.h 1.1 86/09/25 SMI      */
 
/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#include <kern/zalloc.h>

/*
 * The SNODE represents a special file in any filesystem. There is
 * one snode for each active special file. Filesystems which support
 * special files use specvp(vp, dev) to convert a normal vnode to a
 * special vnode in the ops create, mkdir, and lookup.
 */


struct snode {
	struct	vnode s_vnode;		/* vnode associated with this snode */
	struct	vnode *s_realvp;	/* the vnode for the filesystem entry */
	struct	vnode *s_bdevvp;	/* blk device vnode (shared with fs) */
	u_short	s_flag;			/* flags, see below */
	daddr_t	s_lastr;		/* last read (read-ahead) */
	struct timeval  s_atime;	/* time of last access */
	struct timeval  s_mtime;	/* time of last modification */
	struct timeval  s_ctime;	/* time of last attributes change */
	caddr_t	s_private;		/* private data struct */
};

/* flags */
#define SLOCKED		0x01		/* snode is locked */
#define SUPD		0x02		/* update device access time */
#define SACC		0x04		/* update device modification time */
#define SWANT		0x10		/* some process waiting on lock */
#define SCHG		0x40		/* update device change time */

/*
 * Convert between vnode and snode
 */
#define VTOS(vp)	((struct snode *)(vp))
#define STOV(sp)	((struct vnode *)(sp))

#define snode_next(sp)	(VTOS(STOV(sp)->v_next))

/*
 * Lock and unlock snodes.
 */
#define SNLOCK(sp) { \
	while ((sp)->s_flag & SLOCKED) { \
		(sp)->s_flag |= SWANT; \
		(void) sleep((caddr_t)(sp), PINOD); \
	} \
	(sp)->s_flag |= SLOCKED; \
}

#define SNUNLOCK(sp) { \
	(sp)->s_flag &= ~SLOCKED; \
	if ((sp)->s_flag & SWANT) { \
		(sp)->s_flag &= ~SWANT; \
		wakeup((caddr_t)(sp)); \
	} \
}

/*
 * construct a spec vnode for a given device
 */
struct vnode *specvp();

extern zone_t specfs_snode_zone;
extern zone_t specfs_vattr_zone;
