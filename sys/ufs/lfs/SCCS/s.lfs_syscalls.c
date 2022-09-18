h58090
s 00001/00004/00544
d D 8.10 95/05/14 00:29:05 mckusick 54 53
c delete paranoia; get lock status from lock manager
e
s 00021/00009/00527
d D 8.9 95/05/08 12:17:12 mckusick 53 52
c update from margo
e
s 00005/00005/00531
d D 8.8 95/03/28 22:48:42 mckusick 52 51
c getvfs => vfs_getvfs
e
s 00006/00006/00530
d D 8.7 95/03/21 00:28:02 mckusick 51 50
c daddr_t => ufs_daddr_t
e
s 00001/00001/00535
d D 8.6 94/06/16 10:26:54 mckusick 50 49
c dumb error (from mycroft)
e
s 00022/00018/00514
d D 8.5 94/04/20 14:49:22 bostic 49 48
c In lfs_markv, we need to check if there are blocks in the current
c file_info structure before we try to write the meta-data.  If we
c do not do this, then the act of writing the meta-data can cause
c a segment write.  This will cause the number of active FINFO structures
c to go to zero.  When the meta-data write returns, lfs_markv was checking
c if there were no data blocks for the current file.  If there were none,
c lfs_markv was decrementing the count of FINFOs and making it go 
c negative.  From: margo@das.harvard.edu
e
s 00028/00011/00504
d D 8.4 94/01/13 18:52:45 bostic 48 47
c the Sparc isn't handling structures passed to the kernel correctly
c change LFS routines that take fsid_t's to take fsid_t *'s.
e
s 00007/00007/00508
d D 8.3 93/09/23 16:18:18 bostic 47 46
c changes for 4.4BSD-Lite requested by USL
e
s 00007/00006/00508
d D 8.2 93/09/21 07:30:46 bostic 46 45
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00512
d D 8.1 93/06/11 16:28:00 bostic 45 44
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00513
d D 7.30 93/02/02 21:06:56 mckusick 44 43
c getblk takes parameter to indicate interrupt
e
s 00022/00018/00492
d D 7.29 93/02/02 08:11:44 margo 43 42
c Move argument structure declaration outside of function.
e
s 00019/00020/00491
d D 7.28 92/12/10 14:27:41 margo 42 41
c Move allocation and deallocation out of syscall now that it's in 
c lfs_seglock and lfs_segunlock.  Use lfs_vref and lfs_vunref to access vnodes. 
c Call unlocking hash lookup instead of ihashget.
e
s 00002/00002/00509
d D 7.27 92/11/14 23:00:35 mckusick 41 40
c ufs_iput is obsoleted by vput
e
s 00001/00001/00510
d D 7.26 92/10/24 10:00:44 margo 40 39
c Check all flags, not just B_CACHE to determine if block was in cache.
e
s 00037/00013/00474
d D 7.25 92/10/08 13:46:46 margo 39 38
c Add argument to bmap.  Fix accounting of segment summary bytes in 
c lfs_bmarkv.  Use new queue structures.
e
s 00016/00005/00471
d D 7.24 92/10/01 08:55:42 margo 38 37
c Initialize file info pointer fields for first iteration.  Also, 
c change test for fastvget to pass the inode when it's present.  Release bp 
c and return BUSY if segment being cleaned is active (shouldn't happen).
e
s 00017/00001/00459
d D 7.23 92/09/03 08:25:21 margo 37 36
c Make sure inode MOD bit gets set lfs_markv.  Make lfs_markv behave 
c more like lfs_writefile -- initialize sp->fip fields, increment count of 
c finfos in segment and initialize sp->start_lbp.
e
s 00012/00012/00448
d D 7.22 92/09/02 08:05:59 bostic 36 35
c Get ifile inode address from superblock not ifile.  During bmapv, 
c skip block_infos that merely describe Inodes (we were calling VOP_BMAP on 
c them.  Get rid of ctime check; it made us keep blocks we shouldn't.
e
s 00007/00005/00453
d D 7.21 92/08/26 18:21:56 bostic 35 34
c Make sure that inodes are locked after you copy contents from user 
c space (cleaner).  Compare inode change time, not modify time for
c determining if blocks are live and move segment summary initialization
c out of segclean.
e
s 00010/00005/00448
d D 7.20 92/08/25 14:52:22 bostic 34 33
c Segment structure now takes a vnode, make sure it gets set up and 
c maintained properly.
e
s 00206/00079/00247
d D 7.19 92/08/21 17:29:27 bostic 33 32
c Make lfs_markv perform segment writing.  It sets up its data and 
c uses gatherblock and writeseg to output the results of segment cleaning. 
c Data is left in user space until the writer needs to copy it.  Add code to 
c use inodes from cleaner if they are up to date.
e
s 00000/00012/00326
d D 7.18 92/08/01 15:40:43 bostic 32 31
c delete VERBOSE #ifdef's
e
s 00009/00009/00329
d D 7.17 92/08/01 15:29:58 bostic 31 30
c get ifile address out of superblock; fix byte accounting
e
s 00008/00000/00330
d D 7.16 92/07/23 16:29:11 bostic 30 29
c Do block accounting in terms of sectors.  Do block accounting for 
c inode blocks and segment summary blocks when the segment is marked clean.
e
s 00002/00002/00328
d D 7.15 92/07/07 17:34:36 mckusick 29 28
c volatile poison
e
s 00003/00008/00327
d D 7.14 92/07/03 01:53:07 mckusick 28 26
c delete USES; VOP_VGET => VFS_VGET
e
s 00000/00005/00330
d R 7.14 92/07/02 23:41:36 mckusick 27 26
c delete USES_VOP
e
s 00003/00001/00332
d D 7.13 92/06/23 11:25:30 bostic 26 25
c select(2) race condition with small timeout values; bug net2/sys/11
e
s 00001/00001/00332
d D 7.12 92/06/19 19:22:39 mckusick 25 24
c timeval => timespec in vattr and dinode
e
s 00011/00006/00322
d D 7.11 92/05/14 17:29:52 heideman 24 11
c vnode interface conversion
e
s 00011/00006/00322
d R 7.11 92/05/14 17:06:03 heideman 23 11
c vnode interface conversion
e
s 00011/00006/00322
d R 7.11 92/05/14 16:47:04 heideman 22 11
c vnode interface conversion
e
s 00011/00006/00322
d R 7.11 92/05/14 16:36:55 heideman 21 11
c vnode interface conversion
e
s 00011/00006/00322
d R 7.11 92/05/14 15:57:24 heideman 20 11
c vnode interface conversion
e
s 00011/00006/00322
d R 7.11 92/05/14 15:43:05 heideman 19 11
c vnode interface conversion
e
s 00011/00006/00322
d R 7.11 92/05/14 14:48:50 heideman 18 11
c vnode interface conversion
e
s 00011/00006/00322
d R 7.11 92/05/14 12:52:39 heideman 17 11
c vnode interface conversion
e
s 00011/00006/00322
d R 7.11 92/05/14 11:49:57 heideman 16 11
c vnode interface conversion
e
s 00020/00003/00325
d R 7.11 92/05/14 10:30:13 heideman 15 11
c vnode interface conversion
e
s 00041/00006/00322
d R 7.11 92/05/13 23:08:45 heideman 14 11
c vnode interface conversion
e
s 00041/00006/00322
d R 7.11 92/05/13 18:55:20 heideman 13 11
c vnode interface conversion
e
s 00041/00006/00322
d R 7.11 92/05/13 18:27:24 heideman 12 11
c vnode interface conversion
e
s 00001/00001/00327
d D 7.10 92/05/13 15:03:12 mckusick 11 10
c inode times are now timevals
e
s 00006/00006/00322
d D 7.9 92/03/18 11:17:26 bostic 10 9
c no changes, just make it a little more obvious
e
s 00005/00005/00323
d D 7.8 92/03/03 11:53:39 bostic 9 7
c free'ing wrong pointer on error
e
s 00012/00008/00320
d R 7.8 92/03/03 11:50:22 bostic 8 7
c free'ing the wrong pointer when copyin fails; minor cleanups
e
s 00046/00019/00282
d D 7.7 92/01/10 16:02:40 bostic 7 6
c various bug fixes to make system calls work; from Carl
e
s 00001/00001/00300
d D 7.6 91/12/31 15:01:40 bostic 6 5
c nbytes shouldn't include superblocks or summary blocks
e
s 00040/00018/00261
d D 7.5 91/12/31 14:59:07 bostic 5 4
c fix lfs_markv code to check right order of things, deciding what block
c to use; minor cleanups, use LFS_UBWRITE
e
s 00001/00000/00278
d D 7.4 91/12/15 16:29:20 bostic 4 3
c update byte count on segments marked clean
e
s 00003/00003/00275
d D 7.3 91/12/14 18:46:40 bostic 3 2
c use LFS_IRELEASE/LFS_IWRITE macros
e
s 00008/00000/00270
d D 7.2 91/12/14 16:55:41 bostic 2 1
c update cleaner info when marking a segment clean
e
s 00270/00000/00000
d D 7.1 91/12/11 14:38:06 bostic 1 0
c LFS version 2; cleaner system calls
c date and time created 91/12/11 14:38:06 by bostic
e
u
U
t
T
I 1
/*-
D 45
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 45
I 45
D 49
 * Copyright (c) 1991, 1993
E 49
I 49
 * Copyright (c) 1991, 1993, 1994
E 49
 *	The Regents of the University of California.  All rights reserved.
E 45
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <sys/malloc.h>
#include <sys/kernel.h>

#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>
I 33
#include <ufs/ufs/ufs_extern.h>
E 33

#include <ufs/lfs/lfs.h>
#include <ufs/lfs/lfs_extern.h>
I 37
D 39
#define INC_FINFO(SP) \
	++((SEGSUM *)((SP)->segsum))->ss_nfinfo
E 39
I 39
#define BUMP_FIP(SP) \
	(SP)->fip = (FINFO *) (&(SP)->fip->fi_blocks[(SP)->fip->fi_nblocks])
E 39
E 37

I 39
#define INC_FINFO(SP) ++((SEGSUM *)((SP)->segsum))->ss_nfinfo
#define DEC_FINFO(SP) --((SEGSUM *)((SP)->segsum))->ss_nfinfo

/*
 * Before committing to add something to a segment summary, make sure there
 * is enough room.  S is the bytes added to the summary.
 */
#define	CHECK_SEG(s)			\
if (sp->sum_bytes_left < (s)) {		\
	(void) lfs_writeseg(fs, sp);	\
D 42
	lfs_initseg(fs, sp);		\
E 42
}
E 39
I 33
struct buf *lfs_fakebuf __P((struct vnode *, int, size_t, caddr_t));

I 53
int debug_cleaner = 0;
int clean_vnlocked = 0;
int clean_inlocked = 0;

E 53
E 33
/*
 * lfs_markv:
 *
 * This will mark inodes and blocks dirty, so they are written into the log.
 * It will block until all the blocks have been written.  The segment create
 * time passed in the block_info and inode_info structures is used to decide
 * if the data is valid for each block (in case some process dirtied a block
 * or inode that is being cleaned between the determination that a block is
 * live and the lfs_markv call).
 *
 *  0 on success
 * -1/errno is return on error.
 */
I 43
struct lfs_markv_args {
D 48
	fsid_t fsid;		/* file system */
E 48
I 48
	fsid_t *fsidp;		/* file system */
E 48
	BLOCK_INFO *blkiov;	/* block array */
	int blkcnt;		/* count of block array entries */
};
E 43
int
lfs_markv(p, uap, retval)
	struct proc *p;
D 43
	struct args {
		fsid_t fsid;		/* file system */
		BLOCK_INFO *blkiov;	/* block array */
		int blkcnt;		/* count of block array entries */
D 33
		INODE_INFO *inoiov;	/* inode array */
		int inocnt;		/* count of inode array entries */
E 33
	} *uap;
E 43
I 43
	struct lfs_markv_args *uap;
E 43
	int *retval;
{
I 33
	struct segment *sp;
E 33
I 24
D 28
	USES_VOP_BMAP;
	USES_VOP_BWRITE;
	USES_VOP_VGET;
E 28
E 24
	BLOCK_INFO *blkp;
	IFILE *ifp;
D 33
	INODE_INFO *inop;
	struct buf *bp;
E 33
I 33
	struct buf *bp, **bpp;
E 33
I 5
	struct inode *ip;
E 5
	struct lfs *fs;
	struct mount *mntp;
	struct vnode *vp;
I 48
	fsid_t fsid;
E 48
I 7
	void *start;
E 7
I 5
	ino_t lastino;
E 5
D 33
	daddr_t daddr;
E 33
I 33
D 51
	daddr_t b_daddr, v_daddr;
E 51
I 51
	ufs_daddr_t b_daddr, v_daddr;
E 51
E 33
	u_long bsize;
	int cnt, error;

I 7
D 32
#ifdef VERBOSE
	printf("lfs_markv\n");
#endif
E 32
E 7
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
D 33

E 33
D 48
	if ((mntp = getvfs(&uap->fsid)) == NULL)
E 48
I 48

	if (error = copyin(uap->fsidp, &fsid, sizeof(fsid_t)))
		return (error);
D 52
	if ((mntp = getvfs(&fsid)) == NULL)
E 52
I 52
	if ((mntp = vfs_getvfs(&fsid)) == NULL)
E 52
E 48
		return (EINVAL);
I 33
D 42
	/* Initialize a segment. */
	sp = malloc(sizeof(struct segment), M_SEGMENT, M_WAITOK);
	sp->bpp = malloc(((LFS_SUMMARY_SIZE - sizeof(SEGSUM)) /
	    sizeof(daddr_t) + 1) * sizeof(struct buf *), M_SEGMENT, M_WAITOK);
	sp->seg_flags = SEGM_CKP;
I 34
	sp->vp = NULL;
E 42
E 34
E 33

	cnt = uap->blkcnt;
D 7
	blkp = malloc(cnt * sizeof(BLOCK_INFO), M_SEGMENT, M_WAITOK);
E 7
I 7
D 10
	start = blkp = malloc(cnt * sizeof(BLOCK_INFO), M_SEGMENT, M_WAITOK);
E 7
	if (error = copyin(uap->blkiov, blkp, cnt * sizeof(BLOCK_INFO))) {
E 10
I 10
	start = malloc(cnt * sizeof(BLOCK_INFO), M_SEGMENT, M_WAITOK);
D 33
	if (error = copyin(uap->blkiov, start, cnt * sizeof(BLOCK_INFO))) {
E 10
D 9
		free(blkp, M_SEGMENT);
E 9
I 9
		free(start, M_SEGMENT);
E 9
		return (error);
	}
E 33
I 33
	if (error = copyin(uap->blkiov, start, cnt * sizeof(BLOCK_INFO)))
		goto err1;
E 33

D 33
	/*
D 5
	 * Mark blocks/inodes dirty.  For blocks, we get the vnode, and check
	 * to see if the modified or disk address is newer than the cleaner
	 * thinks.  If so, we're done.  Otherwise, we get the block, from core
	 * if we have it, otherwise from the cleaner, and write it.  Note that
	 * errors are mostly ignored.  If we can't get the info, the block is
	 * probably not all that useful, and hopefully subsequent calls from
	 * the cleaner will fix everything.
E 5
I 5
	 * Mark blocks/inodes dirty.  Note that errors are mostly ignored.  If
	 * we can't get the info, the block is probably not all that useful,
	 * and hopefully subsequent calls from the cleaner will fix everything.
E 5
	 */
E 33
I 33
	/* Mark blocks/inodes dirty.  */
E 33
I 5
	fs = VFSTOUFS(mntp)->um_lfs;
E 5
D 9
	bsize = VFSTOUFS(mntp)->um_lfs->lfs_bsize;
E 9
I 9
	bsize = fs->lfs_bsize;
E 9
D 5
	for (; cnt--; ++blkp) {
		if (lfs_vget(mntp, blkp->bi_inode, &vp) ||
		    VTOI(vp)->i_mtime >= blkp->bi_segcreate ||
		    lfs_bmap(vp, blkp->bi_lbn, NULL, &daddr) ||
		    daddr != blkp->bi_daddr)
E 5
I 5
D 10
	for (lastino = LFS_UNUSED_INUM; cnt--; ++blkp) {
E 10
I 10
D 33
	for (lastino = LFS_UNUSED_INUM, blkp = start; cnt--; ++blkp) {
E 33
I 33
	error = 0;

D 42
	lfs_seglock(fs);
	lfs_initseg(fs, sp);
	sp->seg_flags |= SEGM_CLEAN;
E 42
I 42
	lfs_seglock(fs, SEGM_SYNC | SEGM_CLEAN);
	sp = fs->lfs_sp;
E 42
	for (v_daddr = LFS_UNUSED_DADDR, lastino = LFS_UNUSED_INUM,
	    blkp = start; cnt--; ++blkp) {
E 33
E 10
		/*
		 * Get the IFILE entry (only once) and see if the file still
		 * exists.
		 */
		if (lastino != blkp->bi_inode) {
I 33
			if (lastino != LFS_UNUSED_INUM) {
I 39
				/* Finish up last file */
E 39
D 34
				lfs_updatemeta(sp, vp);
E 34
I 34
D 49
				lfs_updatemeta(sp);
E 34
				lfs_writeinode(fs, sp, ip);
D 42
				vput(vp);
E 42
I 42
				lfs_vunref(vp);
E 42
I 37
D 39
				if (sp->fip->fi_nblocks) {
					INC_FINFO(sp);
					sp->fip =
					(FINFO *) (&sp->fip->fi_blocks[sp->fip->fi_nblocks]);
E 39
I 39
				if (sp->fip->fi_nblocks)
					BUMP_FIP(sp);
				else  {
E 49
I 49
				if (sp->fip->fi_nblocks == 0) {
E 49
					DEC_FINFO(sp);
					sp->sum_bytes_left +=
D 49
						sizeof(FINFO) - sizeof(daddr_t);

E 49
I 49
D 51
					    sizeof(FINFO) - sizeof(daddr_t);
E 51
I 51
					    sizeof(FINFO) - sizeof(ufs_daddr_t);
E 51
				} else {
					lfs_updatemeta(sp);
					BUMP_FIP(sp);
E 49
E 39
				}
I 49

				lfs_writeinode(fs, sp, ip);
				lfs_vunref(vp);
E 49
D 39
				sp->start_lbp = &sp->fip->fi_blocks[0];
D 38
				sp->fip->fi_version = blkp->bi_version;
				sp->fip->fi_nblocks = 0;
				sp->fip->fi_ino = blkp->bi_inode;
E 38
E 37
I 36
				sp->vp = NULL;
E 39
E 36
			}
I 39

			/* Start a new file */
			CHECK_SEG(sizeof(FINFO));
D 51
			sp->sum_bytes_left -= sizeof(FINFO) - sizeof(daddr_t);
E 51
I 51
			sp->sum_bytes_left -= sizeof(FINFO) - sizeof(ufs_daddr_t);
E 51
			INC_FINFO(sp);
			sp->start_lbp = &sp->fip->fi_blocks[0];
			sp->vp = NULL;
E 39
I 38
			sp->fip->fi_version = blkp->bi_version;
			sp->fip->fi_nblocks = 0;
			sp->fip->fi_ino = blkp->bi_inode;
E 38
E 33
			lastino = blkp->bi_inode;
D 36
			LFS_IENTRY(ifp, fs, blkp->bi_inode, bp);
D 33
			daddr = ifp->if_daddr;
E 33
I 33
			v_daddr = ifp->if_daddr;
E 33
			brelse(bp);
E 36
I 36
			if (blkp->bi_inode == LFS_IFILE_INUM)
				v_daddr = fs->lfs_idaddr;
			else {
				LFS_IENTRY(ifp, fs, blkp->bi_inode, bp);
				v_daddr = ifp->if_daddr;
				brelse(bp);
			}
E 36
D 33
			if (daddr == LFS_UNUSED_DADDR)
E 33
I 33
			if (v_daddr == LFS_UNUSED_DADDR)
E 33
				continue;
I 39

E 39
D 33
		}

		/*
		 * Get the vnode/inode.  If the inode modification time is
		 * earlier than the segment in which the block was found then
		 * they have to be valid, skip other checks.
		 */
D 24
		if (lfs_vget(mntp, blkp->bi_inode, &vp))
E 24
I 24
D 28
		if (LFS_VGET(mntp, blkp->bi_inode, &vp))
E 28
I 28
		if (VFS_VGET(mntp, blkp->bi_inode, &vp))
E 33
I 33
			/* Get the vnode/inode. */
			if (lfs_fastvget(mntp, blkp->bi_inode, v_daddr, &vp,
D 38
			    blkp->bi_lbn == LFS_UNUSED_LBN ? NULL :
			    blkp->bi_bp)) {
E 38
I 38
			    blkp->bi_lbn == LFS_UNUSED_LBN ? 
			    blkp->bi_bp : NULL)) {
E 38
#ifdef DIAGNOSTIC
				printf("lfs_markv: VFS_VGET failed (%d)\n",
				    blkp->bi_inode);
I 53
				panic("lfs_markv VFS_VGET FAILED");
E 53
#endif
I 34
				lastino = LFS_UNUSED_INUM;
E 34
D 39
				v_daddr == LFS_UNUSED_DADDR;
E 39
I 39
				v_daddr = LFS_UNUSED_DADDR;
E 39
				continue;
			}
I 34
			sp->vp = vp;
E 34
			ip = VTOI(vp);
		} else if (v_daddr == LFS_UNUSED_DADDR)
E 33
E 28
E 24
E 5
			continue;
I 5
D 33
		ip = VTOI(vp);
E 33
D 7
		if (ip->i_mtime > blkp->bi_segcreate) {
			/* Check to see if the block has been replaced. */
			if (lfs_bmap(vp, blkp->bi_lbn, NULL, &daddr))
				continue;
			if (daddr != blkp->bi_daddr)
				continue;
E 7
I 7

I 33
		/* If this BLOCK_INFO didn't contain a block, keep going. */
		if (blkp->bi_lbn == LFS_UNUSED_LBN)
			continue;
E 33
D 36
		/*
D 35
		 * If modify time later than segment create time, see if the
E 35
I 35
		 * If change time later than segment create time, see if the
E 35
		 * block has been replaced.
		 */
D 11
		if (ip->i_mtime > blkp->bi_segcreate &&
E 11
I 11
D 25
		if (ip->i_mtime.tv_sec > blkp->bi_segcreate &&
E 25
I 25
D 35
		if (ip->i_mtime.ts_sec > blkp->bi_segcreate &&
E 35
I 35
		if (ip->i_ctime.ts_sec > blkp->bi_segcreate &&
E 35
E 25
E 11
D 24
		    (lfs_bmap(vp, blkp->bi_lbn, NULL, &daddr) ||
E 24
I 24
D 33
		    (VOP_BMAP(vp, blkp->bi_lbn, NULL, &daddr) ||
E 24
		    daddr != blkp->bi_daddr)) {
			vput(vp);
E 33
I 33
		    (VOP_BMAP(vp, blkp->bi_lbn, NULL, &b_daddr) ||
		    b_daddr != blkp->bi_daddr))
E 36
I 36
D 39
		if (VOP_BMAP(vp, blkp->bi_lbn, NULL, &b_daddr) ||
E 39
I 39
		if (VOP_BMAP(vp, blkp->bi_lbn, NULL, &b_daddr, NULL) ||
E 39
		    b_daddr != blkp->bi_daddr)
E 36
E 33
			continue;
I 33
		/*
		 * If we got to here, then we are keeping the block.  If it
		 * is an indirect block, we want to actually put it in the
		 * buffer cache so that it can be updated in the finish_meta
		 * section.  If it's not, we need to allocate a fake buffer
		 * so that writeseg can perform the copyin and write the buffer.
		 */
		if (blkp->bi_lbn >= 0)	/* Data Block */
			bp = lfs_fakebuf(vp, blkp->bi_lbn, bsize,
			    blkp->bi_bp);
		else {
D 44
			bp = getblk(vp, blkp->bi_lbn, bsize);
E 44
I 44
			bp = getblk(vp, blkp->bi_lbn, bsize, 0, 0);
E 44
D 40
			if (!(bp->b_flags & B_CACHE) &&
E 40
I 40
			if (!(bp->b_flags & (B_DELWRI | B_DONE | B_CACHE)) &&
E 40
D 46
			    (error = copyin(blkp->bi_bp, bp->b_un.b_addr,
E 46
I 46
			    (error = copyin(blkp->bi_bp, bp->b_data,
E 46
D 53
			    bsize)))
E 53
I 53
			    blkp->bi_size)))
E 53
				goto err2;
			if (error = VOP_BWRITE(bp))
				goto err2;
E 33
E 7
		}
D 33

		/* Get the block (from core or the cleaner) and write it. */
E 5
		bp = getblk(vp, blkp->bi_lbn, bsize);
I 7
		vput(vp);
E 7
		if (!(bp->b_flags & B_CACHE) &&
D 9
		    (error = copyin(blkp->bi_bp, bp->b_un.b_daddr, bsize))) {
E 9
I 9
		    (error = copyin(blkp->bi_bp, bp->b_un.b_addr, bsize))) {
E 9
			brelse(bp);
D 9
			free(blkp, M_SEGMENT);
E 9
I 9
			free(start, M_SEGMENT);
E 9
			return (error);
		}
D 24
		lfs_bwrite(bp);
E 24
I 24
		VOP_BWRITE(bp);
E 33
I 33
D 34
		lfs_gatherblock(sp, bp, NULL);
E 34
I 34
		while (lfs_gatherblock(sp, bp, NULL));
E 34
E 33
E 24
D 5
		brelse(bp);
E 5
	}
I 33
D 34
	lfs_updatemeta(sp, vp);
	lfs_writeinode(fs, sp, ip);
	vput(vp);
E 34
I 34
	if (sp->vp) {
I 37
D 39
		if (sp->fip->fi_nblocks)
			INC_FINFO(sp);
E 39
E 37
D 49
		lfs_updatemeta(sp);
E 49
I 49
		if (sp->fip->fi_nblocks == 0) {
			DEC_FINFO(sp);
			sp->sum_bytes_left +=
D 51
			    sizeof(FINFO) - sizeof(daddr_t);
E 51
I 51
			    sizeof(FINFO) - sizeof(ufs_daddr_t);
E 51
		} else
			lfs_updatemeta(sp);

E 49
		lfs_writeinode(fs, sp, ip);
D 42
		vput(vp);
E 42
I 42
		lfs_vunref(vp);
E 42
I 39
D 49
		if (!sp->fip->fi_nblocks) {
			DEC_FINFO(sp);
			sp->sum_bytes_left += sizeof(FINFO) - sizeof(daddr_t);
		}
E 49
E 39
	}
E 34
	(void) lfs_writeseg(fs, sp);
	lfs_segunlock(fs);
E 33
D 7
	free(blkp, M_SEGMENT);
E 7
I 7
	free(start, M_SEGMENT);
I 33
D 42
	free(sp->bpp, M_SEGMENT);
	free(sp, M_SEGMENT);
E 42
	return (error);
I 49

E 49
/*
D 49
 * XXX If we come in to error 2, we might have indirect blocks that were
E 49
I 49
 * XXX
 * If we come in to error 2, we might have indirect blocks that were
E 49
 * updated and now have bad block pointers.  I don't know what to do
 * about this.
 */
E 33
E 7

D 33
	cnt = uap->inocnt;
D 7
	inop = malloc(cnt * sizeof(INODE_INFO), M_SEGMENT, M_WAITOK);
E 7
I 7
D 10
	start = inop = malloc(cnt * sizeof(INODE_INFO), M_SEGMENT, M_WAITOK);
E 7
	if (error = copyin(uap->inoiov, inop, cnt * sizeof(INODE_INFO))) {
E 10
I 10
	start = malloc(cnt * sizeof(INODE_INFO), M_SEGMENT, M_WAITOK);
	if (error = copyin(uap->inoiov, start, cnt * sizeof(INODE_INFO))) {
E 10
D 9
		free(inop, M_SEGMENT);
E 9
I 9
		free(start, M_SEGMENT);
E 9
		return (error);
	}

D 5
	fs = VFSTOUFS(mntp)->um_lfs;
E 5
D 10
	for (; cnt--; ++inop) {
E 10
I 10
	for (inop = start; cnt--; ++inop) {
E 10
D 31
		LFS_IENTRY(ifp, fs, inop->ii_inode, bp);
		daddr = ifp->if_daddr;
D 3
		brelse(bp);
E 3
I 3
D 5
		LFS_IRELEASE(fs, bp);
E 5
I 5
		brelse(bp);
E 31
I 31
		if (inop->ii_inode == LFS_IFILE_INUM)
			daddr = fs->lfs_idaddr;
		else {
			LFS_IENTRY(ifp, fs, inop->ii_inode, bp);
			daddr = ifp->if_daddr;
			brelse(bp);
		}

E 31
E 5
E 3
		if (daddr != inop->ii_daddr)
			continue;
		/*
		 * XXX
		 * This is grossly inefficient since the cleaner just handed
		 * us a copy of the inode and we're going to have to seek
		 * to get our own.  The fix requires creating a version of
		 * lfs_vget that takes the copy and uses it instead of reading
		 * from disk, if it's not already in the cache.
		 */
D 7
		if (!lfs_vget(mntp, inop->ii_inode, &vp))
E 7
I 7
D 24
		if (!lfs_vget(mntp, inop->ii_inode, &vp)) {
E 24
I 24
D 28
		if (!LFS_VGET(mntp, inop->ii_inode, &vp)) {
E 28
I 28
		if (!VFS_VGET(mntp, inop->ii_inode, &vp)) {
E 28
E 24
E 7
			VTOI(vp)->i_flag |= IMOD;
I 7
			vput(vp);
		}	
E 7
	}
E 33
I 33
D 42
err2:	vput(vp);
E 42
I 42
err2:	lfs_vunref(vp);
E 42
	/* Free up fakebuffers */
	for (bpp = --sp->cbpp; bpp >= sp->bpp; --bpp)
		if ((*bpp)->b_flags & B_CALL) {
			brelvp(*bpp);
			free(*bpp, M_SEGMENT);
		} else
			brelse(*bpp);
	lfs_segunlock(fs);
D 48
err1:
E 48
I 48
err1:	
E 48
D 42
	free(sp->bpp, M_SEGMENT);
	free(sp, M_SEGMENT);
E 42
E 33
D 7
	free(inop, M_SEGMENT);
E 7
I 7
	free(start, M_SEGMENT);
E 7
D 33
	return (lfs_segwrite(mntp, 1));
E 33
I 33
D 49
	return(error);
E 49
I 49
	return (error);
E 49
E 33
}

/*
 * lfs_bmapv:
 *
D 5
 * This will fill in the current disk address for arrays of inodes and blocks.
E 5
I 5
 * This will fill in the current disk address for arrays of blocks.
E 5
 *
 *  0 on success
 * -1/errno is return on error.
 */
I 43
struct lfs_bmapv_args {
D 48
	fsid_t fsid;		/* file system */
E 48
I 48
	fsid_t *fsidp;		/* file system */
E 48
	BLOCK_INFO *blkiov;	/* block array */
	int blkcnt;		/* count of block array entries */
};
E 43
int
lfs_bmapv(p, uap, retval)
	struct proc *p;
D 43
	struct args {
		fsid_t fsid;		/* file system */
		BLOCK_INFO *blkiov;	/* block array */
		int blkcnt;		/* count of block array entries */
	} *uap;
E 43
I 43
	struct lfs_bmapv_args *uap;
E 43
	int *retval;
{
I 24
D 28
	USES_VOP_BMAP;
	USES_VOP_VGET;
E 28
E 24
	BLOCK_INFO *blkp;
	struct mount *mntp;
I 53
	struct ufsmount *ump;
E 53
	struct vnode *vp;
I 48
	fsid_t fsid;
E 48
I 7
	void *start;
E 7
D 51
	daddr_t daddr;
E 51
I 51
	ufs_daddr_t daddr;
E 51
D 7
	int cnt, error;
E 7
I 7
	int cnt, error, step;
E 7

I 7
D 32
#ifdef VERBOSE
	printf("lfs_bmapv\n");
#endif
E 32
E 7
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
D 33

E 33
D 48
	if ((mntp = getvfs(&uap->fsid)) == NULL)
E 48
I 48

	if (error = copyin(uap->fsidp, &fsid, sizeof(fsid_t)))
		return (error);
D 52
	if ((mntp = getvfs(&fsid)) == NULL)
E 52
I 52
	if ((mntp = vfs_getvfs(&fsid)) == NULL)
E 52
E 48
		return (EINVAL);

	cnt = uap->blkcnt;
D 7
	blkp = malloc(cnt * sizeof(BLOCK_INFO), M_SEGMENT, M_WAITOK);
E 7
I 7
	start = blkp = malloc(cnt * sizeof(BLOCK_INFO), M_SEGMENT, M_WAITOK);
E 7
	if (error = copyin(uap->blkiov, blkp, cnt * sizeof(BLOCK_INFO))) {
		free(blkp, M_SEGMENT);
		return (error);
	}

D 7
	for (; cnt--; ++blkp)
		blkp->bi_daddr = 
		    lfs_vget(mntp, blkp->bi_inode, &vp) ||
		    lfs_bmap(vp, blkp->bi_lbn, NULL, &daddr) ?
			LFS_UNUSED_DADDR : daddr;
	free(blkp, M_SEGMENT);
E 7
I 7
	for (step = cnt; step--; ++blkp) {
I 36
		if (blkp->bi_lbn == LFS_UNUSED_LBN)
			continue;
I 42
D 53
		/* Could be a deadlock ? */
E 42
E 36
D 24
		if (lfs_vget(mntp, blkp->bi_inode, &vp))
E 24
I 24
D 28
		if (LFS_VGET(mntp, blkp->bi_inode, &vp))
E 28
I 28
		if (VFS_VGET(mntp, blkp->bi_inode, &vp))
E 53
I 53
		/*
		 * A regular call to VFS_VGET could deadlock
		 * here.  Instead, we try an unlocked access.
		 */
		ump = VFSTOUFS(mntp);
		if ((vp =
		    ufs_ihashlookup(ump->um_dev, blkp->bi_inode)) != NULL) {
			if (VOP_BMAP(vp, blkp->bi_lbn, NULL, &daddr, NULL))
				daddr = LFS_UNUSED_DADDR;
		} else if (VFS_VGET(mntp, blkp->bi_inode, &vp))
E 53
E 28
E 24
			daddr = LFS_UNUSED_DADDR;
D 53
		else {
E 53
I 53
		else  {
E 53
D 24
			if (lfs_bmap(vp, blkp->bi_lbn, NULL, &daddr))
E 24
I 24
D 39
			if (VOP_BMAP(vp, blkp->bi_lbn, NULL, &daddr))
E 39
I 39
			if (VOP_BMAP(vp, blkp->bi_lbn, NULL, &daddr, NULL))
E 39
E 24
				daddr = LFS_UNUSED_DADDR;
			vput(vp);
		}
		blkp->bi_daddr = daddr;
        }
	copyout(start, uap->blkiov, cnt * sizeof(BLOCK_INFO));
	free(start, M_SEGMENT);
E 7
	return (0);
}

/*
 * lfs_segclean:
 *
 * Mark the segment clean.
 *
 *  0 on success
 * -1/errno is return on error.
 */
I 43
struct lfs_segclean_args {
D 48
	fsid_t fsid;		/* file system */
E 48
I 48
	fsid_t *fsidp;		/* file system */
E 48
	u_long segment;		/* segment number */
}; 
E 43
int
lfs_segclean(p, uap, retval)
	struct proc *p;
D 43
	struct args {
		fsid_t fsid;		/* file system */
		u_long segment;		/* segment number */
	} *uap;
E 43
I 43
	struct lfs_segclean_args *uap;
E 43
	int *retval;
{
I 2
	CLEANERINFO *cip;
E 2
	SEGUSE *sup;
	struct buf *bp;
	struct mount *mntp;
	struct lfs *fs;
I 48
	fsid_t fsid;
E 48
	int error;

I 7
D 32
#ifdef VERBOSE
	printf("lfs_segclean\n");
#endif
E 32
E 7
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
D 33

E 33
D 48
	if ((mntp = getvfs(&uap->fsid)) == NULL)
E 48
I 48

	if (error = copyin(uap->fsidp, &fsid, sizeof(fsid_t)))
		return (error);
D 52
	if ((mntp = getvfs(&fsid)) == NULL)
E 52
I 52
	if ((mntp = vfs_getvfs(&fsid)) == NULL)
E 52
E 48
		return (EINVAL);

	fs = VFSTOUFS(mntp)->um_lfs;
I 2

I 38
	if (datosn(fs, fs->lfs_curseg) == uap->segment)
		return (EBUSY);

E 38
E 2
	LFS_SEGENTRY(sup, fs, uap->segment, bp);
I 38
	if (sup->su_flags & SEGUSE_ACTIVE) {
		brelse(bp);
D 49
		return(EBUSY);
E 49
I 49
		return (EBUSY);
E 49
	}
E 38
I 33
	fs->lfs_avail += fsbtodb(fs, fs->lfs_ssize) - 1;
E 33
I 30
	fs->lfs_bfree += (sup->su_nsums * LFS_SUMMARY_SIZE / DEV_BSIZE) +
	    sup->su_ninos * btodb(fs->lfs_bsize);
E 30
	sup->su_flags &= ~SEGUSE_DIRTY;
I 4
D 6
	sup->su_nbytes = sup->su_flags & SEGUSE_SUPERBLOCK ? LFS_SBPAD : 0;
E 6
I 6
D 31
	sup->su_nbytes = 0;
E 31
I 31
D 35
	sup->su_nbytes -= sup->su_nsums * LFS_SUMMARY_SIZE;
E 31
I 30
	sup->su_ninos = 0;
	sup->su_nsums = 0;
E 35
I 35
D 36
printf ("segclean: segment %d has %d bytes %d sums %d ninos\n",
uap->segment, sup->su_nbytes, sup->su_nsums, sup->su_ninos);
E 36
E 35
E 30
E 6
E 4
D 3
	brelse(bp);
E 3
I 3
D 5
	LFS_IWRITE(fs, bp);
E 5
I 5
D 33
	LFS_UBWRITE(bp);
E 33
I 33
	(void) VOP_BWRITE(bp);
E 33
E 5
E 3
I 2

	LFS_CLEANERINFO(cip, fs, bp);
	++cip->clean;
	--cip->dirty;
D 3
	brelse(bp);
E 3
I 3
D 5
	LFS_IWRITE(fs, bp);
E 5
I 5
D 33
	LFS_UBWRITE(bp);
E 33
I 33
	(void) VOP_BWRITE(bp);
	wakeup(&fs->lfs_avail);
E 33
I 30
D 31
	/*
	 * Count all the blocks in the segment as being free again.
	 */
	fs->lfs_bfree += fs->lfs_ssize;
E 30
E 5
E 3

E 31
E 2
	return (0);
}

/*
 * lfs_segwait:
 *
 * This will block until a segment in file system fsid is written.  A timeout
 * in milliseconds may be specified which will awake the cleaner automatically.
 * An fsid of -1 means any file system, and a timeout of 0 means forever.
 *
 *  0 on success
 *  1 on timeout
 * -1/errno is return on error.
 */
I 43
struct lfs_segwait_args {
D 48
	fsid_t fsid;		/* file system */
E 48
I 48
	fsid_t *fsidp;		/* file system */
E 48
	struct timeval *tv;	/* timeout */
};
E 43
int
lfs_segwait(p, uap, retval)
	struct proc *p;
D 43
	struct args {
		fsid_t fsid;		/* file system */
		struct timeval *tv;	/* timeout */
	} *uap;
E 43
I 43
	struct lfs_segwait_args *uap;
E 43
	int *retval;
{
	extern int lfs_allclean_wakeup;
	struct mount *mntp;
	struct timeval atv;
I 48
	fsid_t fsid;
E 48
	void *addr;
	u_long timeout;
	int error, s;

I 7
D 32
#ifdef VERBOSE
	printf("lfs_segwait\n");
#endif
E 32
E 7
D 33
	if (error = suser(p->p_ucred, &p->p_acflag))
E 33
I 33
	if (error = suser(p->p_ucred, &p->p_acflag)) {
E 33
		return (error);
D 33

E 33
I 33
}
E 33
#ifdef WHEN_QUADS_WORK
D 48
	if (uap->fsid == (fsid_t)-1)
E 48
I 48
	if (error = copyin(uap->fsidp, &fsid, sizeof(fsid_t)))
		return (error);
	if (fsid == (fsid_t)-1)
E 48
		addr = &lfs_allclean_wakeup;
	else {
D 48
		if ((mntp = getvfs(&uap->fsid)) == NULL)
E 48
I 48
D 52
		if ((mntp = getvfs(&fsid)) == NULL)
E 52
I 52
		if ((mntp = vfs_getvfs(&fsid)) == NULL)
E 52
E 48
			return (EINVAL);
		addr = &VFSTOUFS(mntp)->um_lfs->lfs_nextseg;
	}
#else
D 48
	if ((mntp = getvfs(&uap->fsid)) == NULL)
E 48
I 48
	if (error = copyin(uap->fsidp, &fsid, sizeof(fsid_t)))
		return (error);
D 52
	if ((mntp = getvfs(&fsid)) == NULL)
E 52
I 52
	if ((mntp = vfs_getvfs(&fsid)) == NULL)
E 52
E 48
		addr = &lfs_allclean_wakeup;
	else
		addr = &VFSTOUFS(mntp)->um_lfs->lfs_nextseg;
#endif

	if (uap->tv) {
		if (error = copyin(uap->tv, &atv, sizeof(struct timeval)))
			return (error);
		if (itimerfix(&atv))
			return (EINVAL);
D 26
		s = splhigh(); timevaladd(&atv, &time); splx(s);
E 26
I 26
D 29
		s = splhigh();
		timevaladd(&atv, &time);
E 29
I 29
		s = splclock();
		timevaladd(&atv, (struct timeval *)&time);
E 29
E 26
		timeout = hzto(&atv);
I 26
		splx(s);
E 26
	} else
		timeout = 0;

	error = tsleep(addr, PCATCH | PUSER, "segment", timeout);
	return (error == ERESTART ? EINTR : 0);
I 33
}

/*
 * VFS_VGET call specialized for the cleaner.  The cleaner already knows the
 * daddr from the ifile, so don't look it up again.  If the cleaner is
 * processing IINFO structures, it may have the ondisk inode already, so
 * don't go retrieving it again.
 */
int
lfs_fastvget(mp, ino, daddr, vpp, dinp)
	struct mount *mp;
	ino_t ino;
D 51
	daddr_t daddr;
E 51
I 51
	ufs_daddr_t daddr;
E 51
	struct vnode **vpp;
	struct dinode *dinp;
{
	register struct inode *ip;
	struct vnode *vp;
	struct ufsmount *ump;
	struct buf *bp;
	dev_t dev;
	int error;

	ump = VFSTOUFS(mp);
	dev = ump->um_dev;
D 37
	if ((*vpp = ufs_ihashget(dev, ino)) != NULL)
E 37
I 37
D 42
	if ((*vpp = ufs_ihashget(dev, ino)) != NULL) {
E 42
I 42
	/*
	 * This is playing fast and loose.  Someone may have the inode
	 * locked, in which case they are going to be distinctly unhappy
	 * if we trash something.
	 */
	if ((*vpp = ufs_ihashlookup(dev, ino)) != NULL) {
		lfs_vref(*vpp);
		if ((*vpp)->v_flag & VXLOCK)
D 53
			printf ("Cleaned vnode VXLOCKED\n");
E 53
I 53
			clean_vnlocked++;
E 53
E 42
		ip = VTOI(*vpp);
I 42
D 47
		if (ip->i_flags & ILOCKED)
			printf ("Cleaned vnode ILOCKED\n");
E 42
I 38
D 46
		if (!(ip->i_flag & IMOD)) {
E 46
I 46
		if (!(ip->i_flag & IMODIFIED)) {
E 47
I 47
D 50
		if (ip->i_flags & IN_LOCKED)
E 50
I 50
D 54
		if (ip->i_flag & IN_LOCKED)
E 54
I 54
		if (lockstatus(&ip->i_lock))
E 54
E 50
D 53
			printf("cleaned vnode locked\n");
		if (!(ip->i_flag & IN_MODIFIED)) {
E 53
I 53
			clean_inlocked++;
		if (!(ip->i_flag & IN_MODIFIED))
E 53
E 47
E 46
			++ump->um_lfs->lfs_uinodes;
D 46
			ip->i_flag |= IMOD;
E 46
I 46
D 47
			ip->i_flag |= IMODIFIED;
E 47
I 47
D 53
			ip->i_flag |= IN_MODIFIED;
E 47
E 46
		}
E 53
E 38
D 46
		ip->i_flag |= IMOD;
E 46
I 46
D 47
		ip->i_flag |= IMODIFIED;
E 47
I 47
		ip->i_flag |= IN_MODIFIED;
E 47
E 46
E 37
		return (0);
I 37
	}
E 37

	/* Allocate new vnode/inode. */
	if (error = lfs_vcreate(mp, ino, &vp)) {
		*vpp = NULL;
		return (error);
	}

	/*
	 * Put it onto its hash chain and lock it so that other requests for
	 * this inode will block if they arrive while we are sleeping waiting
	 * for old data structures to be purged or for the contents of the
	 * disk portion of this inode to be read.
	 */
	ip = VTOI(vp);
	ufs_ihashins(ip);

	/*
	 * XXX
	 * This may not need to be here, logically it should go down with
	 * the i_devvp initialization.
	 * Ask Kirk.
	 */
	ip->i_lfs = ump->um_lfs;

	/* Read in the disk contents for the inode, copy into the inode. */
	if (dinp)
		if (error = copyin(dinp, &ip->i_din, sizeof(struct dinode)))
			return (error);
	else {
		if (error = bread(ump->um_devvp, daddr,
		    (int)ump->um_lfs->lfs_bsize, NOCRED, &bp)) {
			/*
			 * The inode does not contain anything useful, so it
			 * would be misleading to leave it on its hash chain.
			 * Iput() will return it to the free list.
			 */
			ufs_ihashrem(ip);

			/* Unlock and discard unneeded inode. */
D 41
			ufs_iput(ip);
E 41
I 41
D 42
			vput(vp);
E 42
I 42
			lfs_vunref(vp);
E 42
E 41
			brelse(bp);
			*vpp = NULL;
			return (error);
		}
D 46
		ip->i_din = *lfs_ifind(ump->um_lfs, ino, bp->b_un.b_dino);
E 46
I 46
		ip->i_din =
		    *lfs_ifind(ump->um_lfs, ino, (struct dinode *)bp->b_data);
E 46
		brelse(bp);
	}
I 35
D 54

	/* Inode was just read from user space or disk, make sure it's locked */
D 47
	ip->i_flag |= ILOCKED;
E 47
I 47
	ip->i_flag |= IN_LOCKED;
E 54
E 47
E 35

	/*
	 * Initialize the vnode from the inode, check for aliases.  In all
	 * cases re-init ip, the underlying vnode/inode may have changed.
	 */
	if (error = ufs_vinit(mp, lfs_specop_p, LFS_FIFOOPS, &vp)) {
D 41
		ufs_iput(ip);
E 41
I 41
D 42
		vput(vp);
E 42
I 42
		lfs_vunref(vp);
E 42
E 41
		*vpp = NULL;
		return (error);
	}
	/*
	 * Finish inode initialization now that aliasing has been resolved.
	 */
	ip->i_devvp = ump->um_devvp;
D 46
	ip->i_flag |= IMOD;
E 46
I 46
D 47
	ip->i_flag |= IMODIFIED;
E 47
I 47
	ip->i_flag |= IN_MODIFIED;
E 47
E 46
	++ump->um_lfs->lfs_uinodes;
	VREF(ip->i_devvp);
	*vpp = vp;
	return (0);
}
struct buf *
lfs_fakebuf(vp, lbn, size, uaddr)
	struct vnode *vp;
	int lbn;
	size_t size;
	caddr_t uaddr;
{
	struct buf *bp;

	bp = lfs_newbuf(vp, lbn, 0);
	bp->b_saveaddr = uaddr;
	bp->b_bufsize = size;
	bp->b_bcount = size;
	bp->b_flags |= B_INVAL;
D 49
	return(bp);
E 49
I 49
	return (bp);
E 49
E 33
}
E 1
