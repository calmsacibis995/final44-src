/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	bdev_vnodeops.c,v $
 * Revision 2.9  90/07/03  16:47:11  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:12:18  mrt]
 * 
 * Revision 2.8  89/10/03  19:27:09  rpd
 * 	Added bdev_badop entry to vnodeops, for new VOP_NLINKS.
 * 	[89/10/02  16:02:42  rpd]
 * 
 * Revision 2.7  89/08/02  08:09:08  jsb
 * 	Eliminated MACH conditionals. Use zalloc in place of kalloc.
 * 	[89/07/31  16:36:41  jsb]
 * 
 * Revision 2.6  89/05/11  14:42:09  gm0w
 * 	Added vn_read1dir vnode op entry.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.5  89/04/22  15:30:07  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  21:00:57  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:16:38  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:07:25  jsb
 * 	Include file references.
 * 	[89/01/17  15:05:41  jsb]
 * 
 *  9-Mar-88 John Seamons (jks) at NeXT
 *	Attach vm_info structure to dev_vnode.
 *
 * 27-Oct-87  Peter King (king) at NeXT, Inc.
 * 	Original Sun source, ported to Mach.
 *
 */ 

/* @(#)bdev_vnodeops.c	1.3 87/06/30 3.2/4.3NFSSRC */
#ifndef	lint
static  char sccsid[] = "@(#)bdev_vnodeops.c 1.1 86/09/25";
#endif

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */


#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/inode.h>
#include <sys/stat.h>
#include <kern/mfs.h>
#include <kern/kalloc.h>

zone_t specfs_devvnode_zone;

/*
 * Convert a block dev into a vnode pointer suitable for bio.
 */

struct dev_vnode {
	struct vnode dv_vnode;
	struct dev_vnode *dv_link;
} *dev_vnode_headp;

bdev_badop()
{

	panic("bdev_badop");
}

/*ARGSUSED*/
int
bdev_open(vpp, flag, cred)
	struct vnode **vpp;
	int flag;
	struct ucred *cred;
{

	return ((*bdevsw[major((*vpp)->v_rdev)].d_open)((*vpp)->v_rdev, flag,
		NULL, S_IFBLK));
}

/*ARGSUSED*/
int
bdev_close(vp, flag, cred)
	struct vnode *vp;
	int flag;
	struct ucred *cred;
{

	/*
	 * On last close of a block device (that isn't mounted)
	 * we must invalidate any in core blocks, so that
	 * we can, for instance, change floppy disks.
	 */
	bflush(vp);
	binval(vp);
	return((*bdevsw[major(vp->v_rdev)].d_close)(vp->v_rdev, flag, S_IFBLK));
}

/*
 * For now, the only value we actually return is size.
 */
/*ARGSUSED*/
int
bdev_getattr(vp, vap, cred)
	struct vnode *vp;
	register struct vattr *vap;
	struct ucred *cred;
{
	int (*size)();

	bzero((caddr_t) vap, sizeof (struct vattr));
	size = bdevsw[major(vp->v_rdev)].d_psize;
	if (size) {
		vap->va_size = (*size)(vp->v_rdev) * DEV_BSIZE;
	}
	return (0);
}

/*ARGSUSED*/
int
bdev_inactive(vp)
	struct vnode *vp;
{

	/* could free the vnode here */
	return (0);
}

int
bdev_strategy(bp)
	struct buf *bp;
{

	(*bdevsw[major(ITOV(bp->b_ip)->v_rdev)].d_strategy)(bp);
	return (0);
}

struct vnodeops dev_vnode_ops = {
	bdev_open,
	bdev_close,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_getattr,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_inactive,
	bdev_badop,
	bdev_strategy,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,
	bdev_badop,	/* nlinks */
};

/*
 * Convert a block device into a special purpose vnode for bio
 */
struct vnode *
bdevvp(dev)
	dev_t dev;
{
	register struct dev_vnode *dvp;
	register struct dev_vnode *endvp;

	endvp = (struct dev_vnode *)0;
	for (dvp = dev_vnode_headp; dvp; dvp = dvp->dv_link) {
		if (dvp->dv_vnode.v_rdev == dev) {
			VN_HOLD(&dvp->dv_vnode);
			return (&dvp->dv_vnode);
		}
		endvp = dvp;
	}
	ZALLOC(specfs_devvnode_zone, dvp, struct dev_vnode *);
	bzero((caddr_t)dvp, sizeof (struct dev_vnode));
	dvp->dv_vnode.v_count = 1;
	dvp->dv_vnode.v_type = ITYPE_BDEV;
	dvp->dv_vnode.v_rdev = dev;
	dvp->dv_vnode.v_vm_info = (struct vm_info*) zalloc (vm_info_zone);
	if (endvp != (struct dev_vnode *)0) {
		endvp->dv_link = dvp;
	} else {
		dev_vnode_headp = dvp;
	}
	return (&dvp->dv_vnode);
}

bdev_vnodeops_zone_init()
{
	specfs_devvnode_zone	= zinit(sizeof(struct dev_vnode), 1024*1024,
					0, FALSE, "specfs devvnode");
}
