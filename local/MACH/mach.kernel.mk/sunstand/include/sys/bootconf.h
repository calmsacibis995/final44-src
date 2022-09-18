/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	bootconf.h,v $
 * Revision 2.2  89/07/11  23:35:07  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)bootconf.h 1.4 88/02/08 SMI	*/

/*
 * Boot time configuration information objects
 */

#define	MAXFSNAME	16
#define	MAXOBJNAME	128
/*
 * Boot configuration information
 */
struct bootobj {
	char	bo_fstype[MAXFSNAME];	/* filesystem type name (e.g. nfs) */
	char	bo_name[MAXOBJNAME];	/* name of object */
	int	bo_flags;		/* flags, see below */
	int	bo_size;		/* number of blocks */
	struct vnode *bo_vp;		/* vnode of object */
};

/*
 * flags
 */
#define	BO_VALID	0x01		/* all information in object is valid */
#define	BO_BUSY		0x02		/* object is busy */

extern struct bootobj rootfs;
extern struct bootobj dumpfile;
extern struct bootobj swapfile;
