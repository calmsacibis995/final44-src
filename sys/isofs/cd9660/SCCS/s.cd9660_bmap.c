h08385
s 00007/00007/00069
d D 8.4 94/12/05 21:19:05 mckusick 4 3
c update from mycroft
e
s 00002/00002/00074
d D 8.3 94/01/23 23:50:53 mckusick 3 2
c isofs => cd9660 naming convention
e
s 00000/00006/00076
d D 8.2 94/01/22 20:32:17 hibler 2 1
c get rid of some left over debug stuff
e
s 00082/00000/00000
d D 8.1 94/01/21 18:28:56 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/namei.h>
#include <sys/buf.h>
#include <sys/file.h>
#include <sys/vnode.h>
#include <sys/mount.h>

#include <isofs/cd9660/iso.h>
D 3
#include <isofs/cd9660/isofs_node.h>
E 3
I 3
#include <isofs/cd9660/cd9660_node.h>
E 3

/*
 * Bmap converts a the logical block number of a file to its physical block
 * number on the disk. The conversion is done by using the logical block
 * number to index into the data block (extent) for the file.
 */
int
D 3
isofs_bmap(ap)
E 3
I 3
cd9660_bmap(ap)
E 3
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
		int *a_runp;
	} */ *ap;
{
	struct iso_node *ip = VTOI(ap->a_vp);
	daddr_t lblkno = ap->a_bn;
D 4
	long bsize;
E 4
I 4
	int bshift;
E 4

	/*
	 * Check for underlying vnode requests and ensure that logical
	 * to physical mapping is requested.
	 */
	if (ap->a_vpp != NULL)
		*ap->a_vpp = ip->i_devvp;
	if (ap->a_bnp == NULL)
		return (0);

	/*
	 * Compute the requested block number
	 */
D 4
	bsize = ip->i_mnt->logical_block_size;
	*ap->a_bnp = (ip->iso_start + lblkno) * btodb(bsize);
E 4
I 4
	bshift = ip->i_mnt->im_bshift;
	*ap->a_bnp = (ip->iso_start + lblkno) << (bshift - DEV_BSHIFT);
E 4

	/*
	 * Determine maximum number of readahead blocks following the
	 * requested block.
	 */
	if (ap->a_runp) {
		int nblk;

D 4
		nblk = (ip->i_size - (lblkno + 1) * bsize) / bsize;
E 4
I 4
		nblk = (ip->i_size >> bshift) - (lblkno + 1);
E 4
		if (nblk <= 0)
			*ap->a_runp = 0;
D 4
		else if (nblk >= MAXBSIZE/bsize)
			*ap->a_runp = MAXBSIZE/bsize - 1;
E 4
I 4
		else if (nblk >= (MAXBSIZE >> bshift))
			*ap->a_runp = (MAXBSIZE >> bshift) - 1;
E 4
		else
			*ap->a_runp = nblk;
D 2
{
extern int doclusterread;
if (doclusterread)
printf("ip=%x, size=%x, lblkno=%x, runp=%x\n",
ip, ip->i_size, lblkno, *ap->a_runp);
}
E 2
	}

D 4
	return 0;
E 4
I 4
	return (0);
E 4
}
E 1
