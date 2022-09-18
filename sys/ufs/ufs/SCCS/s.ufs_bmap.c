h09876
s 00010/00009/00259
d D 8.7 95/03/21 01:00:59 mckusick 10 9
c daddr_t => ufs_daddr_t
e
s 00005/00000/00263
d D 8.6 94/01/21 17:30:51 bostic 9 8
c add USL's copyright notice
e
s 00002/00003/00261
d D 8.5 94/01/04 22:19:48 bostic 8 7
c lint
e
s 00000/00002/00264
d D 8.4 93/09/23 16:09:38 bostic 7 6
c changes for 4.4BSD-Lite requested by USL
e
s 00003/00003/00263
d D 8.3 93/09/21 07:24:07 bostic 6 5
c changes for 4.4BSD-Lite requested by USL
e
s 00020/00024/00246
d D 8.2 93/09/05 09:43:38 bostic 5 4
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00268
d D 8.1 93/06/11 16:28:41 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00269
d D 7.3 93/02/02 21:03:43 mckusick 3 2
c getblk takes parameter to indicate interrupt
e
s 00003/00008/00267
d D 7.2 92/12/09 14:23:57 margo 2 1
c get rid of explicit 64K check and debugging printf's
e
s 00275/00000/00000
d D 7.1 92/10/22 18:42:00 margo 1 0
c date and time created 92/10/22 18:42:00 by margo
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989, 1991 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 9
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 9
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/resourcevar.h>
#include <sys/trace.h>

#include <miscfs/specfs/specdev.h>

#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/ufs_extern.h>

/*
 * Bmap converts a the logical block number of a file to its physical block
 * number on the disk. The conversion is done by using the logical block
 * number to index into the array of block pointers described by the dinode.
 */
int
ufs_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
D 10
		daddr_t  a_bn;
E 10
I 10
		ufs_daddr_t a_bn;
E 10
		struct vnode **a_vpp;
D 10
		daddr_t *a_bnp;
E 10
I 10
		ufs_daddr_t *a_bnp;
E 10
		int *a_runp;
	} */ *ap;
{
	/*
	 * Check for underlying vnode requests and ensure that logical
	 * to physical mapping is requested.
	 */
	if (ap->a_vpp != NULL)
		*ap->a_vpp = VTOI(ap->a_vp)->i_devvp;
	if (ap->a_bnp == NULL)
		return (0);

	return (ufs_bmaparray(ap->a_vp, ap->a_bn, ap->a_bnp, NULL, NULL,
	    ap->a_runp));
}

/*
 * Indirect blocks are now on the vnode for the file.  They are given negative
 * logical block numbers.  Indirect blocks are addressed by the negative
 * address of the first data block to which they point.  Double indirect blocks
 * are addressed by one less than the address of the first indirect block to
 * which they point.  Triple indirect blocks are addressed by one less than
 * the address of the first double indirect block to which they point.
 *
 * ufs_bmaparray does the bmap conversion, and if requested returns the
 * array of logical blocks which must be traversed to get to a block.
 * Each entry contains the offset into that block that gets you to the
 * next block and the disk address of the block (if it is assigned).
 */

int
ufs_bmaparray(vp, bn, bnp, ap, nump, runp)
	struct vnode *vp;
D 10
	register daddr_t bn;
	daddr_t *bnp;
E 10
I 10
	ufs_daddr_t bn;
	ufs_daddr_t *bnp;
E 10
	struct indir *ap;
	int *nump;
	int *runp;
{
	register struct inode *ip;
	struct buf *bp;
	struct ufsmount *ump;
	struct mount *mp;
	struct vnode *devvp;
	struct indir a[NIADDR], *xap;
D 8
	daddr_t *bap, daddr;
E 8
I 8
D 10
	daddr_t daddr;
E 10
I 10
	ufs_daddr_t daddr;
E 10
E 8
	long metalbn;
D 8
	int bb, error, maxrun, num, off;
	struct vop_strategy_args vop_strategy_a;
E 8
I 8
	int error, maxrun, num;
E 8

	ip = VTOI(vp);
	mp = vp->v_mount;
	ump = VFSTOUFS(mp);
#ifdef DIAGNOSTIC
	if (ap != NULL && nump == NULL || ap == NULL && nump != NULL)
		panic("ufs_bmaparray: invalid arguments");
#endif

	if (runp) {
		/*
D 5
		 * XXX If MAXBSIZE is the largest transfer the disks can
		 * handle, we probably want maxrun to be 1 block less so
		 * that we don't create a block larger than the device
		 * can handle.
E 5
I 5
		 * XXX
		 * If MAXBSIZE is the largest transfer the disks can handle,
		 * we probably want maxrun to be 1 block less so that we
		 * don't create a block larger than the device can handle.
E 5
		 */
		*runp = 0;
D 2
		maxrun = MAXBSIZE / mp->mnt_stat.f_iosize -
		    (MAXBSIZE < 64 * 1024 ? 1 : 2);
E 2
I 2
		maxrun = MAXBSIZE / mp->mnt_stat.f_iosize - 1;
E 2
	}

	xap = ap == NULL ? a : ap;
	if (!nump)
		nump = &num;
	if (error = ufs_getlbns(vp, bn, xap, nump))
		return (error);

	num = *nump;
	if (num == 0) {
		*bnp = blkptrtodb(ump, ip->i_db[bn]);
		if (*bnp == 0)
			*bnp = -1;
D 2
		else if (runp) {
E 2
I 2
		else if (runp)
E 2
			for (++bn; bn < NDADDR && *runp < maxrun &&
			    is_sequential(ump, ip->i_db[bn - 1], ip->i_db[bn]);
			    ++bn, ++*runp);
D 2
			printf ("ufs_bmaparray: runlength = %d\n", *runp);
		}
E 2
		return (0);
	}


	/* Get disk address out of indirect block array */
	daddr = ip->i_ib[xap->in_off];

D 7
	/* Fetch through the indirect blocks. */
E 7
	devvp = VFSTOUFS(vp->v_mount)->um_devvp;
D 7

E 7
	for (bp = NULL, ++xap; --num; ++xap) {
		/* 
		 * Exit the loop if there is no disk address assigned yet and
		 * the indirect block isn't in the cache, or if we were
		 * looking for an indirect block and we've found it.
		 */

		metalbn = xap->in_lbn;
		if (daddr == 0 && !incore(vp, metalbn) || metalbn == bn)
			break;
		/*
		 * If we get here, we've either got the block in the cache
		 * or we have a disk address for it, go fetch it.
		 */
		if (bp)
			brelse(bp);

		xap->in_exists = 1;
D 3
		bp = getblk(vp, metalbn, mp->mnt_stat.f_iosize);
E 3
I 3
		bp = getblk(vp, metalbn, mp->mnt_stat.f_iosize, 0, 0);
E 3
		if (bp->b_flags & (B_DONE | B_DELWRI)) {
			trace(TR_BREADHIT, pack(vp, size), metalbn);
		}
#ifdef DIAGNOSTIC
		else if (!daddr)
			panic("ufs_bmaparry: indirect block not in cache");
#endif
		else {
			trace(TR_BREADMISS, pack(vp, size), metalbn);
			bp->b_blkno = blkptrtodb(ump, daddr);
			bp->b_flags |= B_READ;
			VOP_STRATEGY(bp);
			curproc->p_stats->p_ru.ru_inblock++;	/* XXX */
			if (error = biowait(bp)) {
				brelse(bp);
				return (error);
			}
		}

D 6
		daddr = bp->b_un.b_daddr[xap->in_off];
E 6
I 6
D 10
		daddr = ((daddr_t *)bp->b_data)[xap->in_off];
E 10
I 10
		daddr = ((ufs_daddr_t *)bp->b_data)[xap->in_off];
E 10
E 6
D 2
		if (num == 1 && daddr && runp) {
E 2
I 2
		if (num == 1 && daddr && runp)
E 2
			for (bn = xap->in_off + 1;
			    bn < MNINDIR(ump) && *runp < maxrun &&
D 6
			    is_sequential(ump, bp->b_un.b_daddr[bn - 1],
			    bp->b_un.b_daddr[bn]);
E 6
I 6
D 10
			    is_sequential(ump, ((daddr_t *)bp->b_data)[bn - 1],
			    ((daddr_t *)bp->b_data)[bn]);
E 10
I 10
			    is_sequential(ump,
			    ((ufs_daddr_t *)bp->b_data)[bn - 1],
			    ((ufs_daddr_t *)bp->b_data)[bn]);
E 10
E 6
			    ++bn, ++*runp);
D 2
			printf ("ufs_bmaparray: runlength = %d\n", *runp);
		}
E 2
	}
	if (bp)
		brelse(bp);

	daddr = blkptrtodb(ump, daddr);
	*bnp = daddr == 0 ? -1 : daddr;
	return (0);
}

/*
 * Create an array of logical block number/offset pairs which represent the
 * path of indirect blocks required to access a data block.  The first "pair"
 * contains the logical block number of the appropriate single, double or
 * triple indirect block and the offset into the inode indirect block array.
 * Note, the logical block number of the inode single/double/triple indirect
 * block appears twice in the array, once with the offset into the i_ib and
 * once with the offset into the page itself.
 */
int
ufs_getlbns(vp, bn, ap, nump)
	struct vnode *vp;
D 10
	register daddr_t bn;
E 10
I 10
	ufs_daddr_t bn;
E 10
	struct indir *ap;
	int *nump;
{
	long metalbn, realbn;
	struct ufsmount *ump;
D 5
	int j, numlevels, off, sh;
E 5
I 5
	int blockcnt, i, numlevels, off;
E 5

	ump = VFSTOUFS(vp->v_mount);
	if (nump)
		*nump = 0;
	numlevels = 0;
	realbn = bn;
	if ((long)bn < 0)
		bn = -(long)bn;

	/* The first NDADDR blocks are direct blocks. */
	if (bn < NDADDR)
		return (0);

	/* 
	 * Determine the number of levels of indirection.  After this loop
D 5
	 * is done, sh indicates the number of data blocks possible at the
	 * given level of indirection, and NIADDR - j is the number of levels
	 * of indirection needed to locate the requested block.
E 5
I 5
	 * is done, blockcnt indicates the number of data blocks possible
	 * at the given level of indirection, and NIADDR - i is the number
	 * of levels of indirection needed to locate the requested block.
E 5
	 */
D 5
	bn -= NDADDR;
	sh = 1;
	for (j = NIADDR; j > 0; j--) {
		sh *= MNINDIR(ump);
		if (bn < sh)
E 5
I 5
	for (blockcnt = 1, i = NIADDR, bn -= NDADDR;; i--, bn -= blockcnt) {
		if (i == 0)
			return (EFBIG);
		blockcnt *= MNINDIR(ump);
		if (bn < blockcnt)
E 5
			break;
D 5
		bn -= sh;
E 5
	}
D 5
	if (j == 0)
		return (EFBIG);
E 5

	/* Calculate the address of the first meta-block. */
	if (realbn >= 0)
D 5
		metalbn = -(realbn - bn + NIADDR - j);
E 5
I 5
		metalbn = -(realbn - bn + NIADDR - i);
E 5
	else
D 5
		metalbn = -(-realbn - bn + NIADDR - j);
E 5
I 5
		metalbn = -(-realbn - bn + NIADDR - i);
E 5

	/* 
	 * At each iteration, off is the offset into the bap array which is
	 * an array of disk addresses at the current level of indirection.
	 * The logical block number and the offset in that block are stored
	 * into the argument array.
	 */
D 5
	++numlevels;
E 5
	ap->in_lbn = metalbn;
D 5
	ap->in_off = off = NIADDR - j;
E 5
I 5
	ap->in_off = off = NIADDR - i;
E 5
	ap->in_exists = 0;
	ap++;
D 5
	for (; j <= NIADDR; j++) {
E 5
I 5
	for (++numlevels; i <= NIADDR; i++) {
E 5
		/* If searching for a meta-data block, quit when found. */
		if (metalbn == realbn)
			break;

D 5
		sh /= MNINDIR(ump);
		off = (bn / sh) % MNINDIR(ump);
E 5
I 5
		blockcnt /= MNINDIR(ump);
		off = (bn / blockcnt) % MNINDIR(ump);
E 5

		++numlevels;
		ap->in_lbn = metalbn;
		ap->in_off = off;
		ap->in_exists = 0;
		++ap;

D 5
		metalbn -= -1 + off * sh;
E 5
I 5
		metalbn -= -1 + off * blockcnt;
E 5
	}
	if (nump)
		*nump = numlevels;
	return (0);
}
E 1
