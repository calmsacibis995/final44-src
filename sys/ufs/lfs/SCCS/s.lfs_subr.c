h52829
s 00001/00001/00158
d D 8.4 95/05/08 12:16:57 mckusick 30 29
c update from margo
e
s 00003/00002/00156
d D 8.3 95/03/21 00:27:50 mckusick 29 28
c daddr_t => ufs_daddr_t
e
s 00002/00002/00156
d D 8.2 93/09/21 07:24:39 bostic 28 27
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00156
d D 8.1 93/06/11 16:27:57 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00084/00006/00074
d D 7.14 92/12/10 14:15:26 margo 26 25
c Extend lfs_seglock and lfs_segunlock to allow the same process 
c to continue adding to a segment when it requests a seglock.  lfs_seglock
c and lfs_segunlock are really the entry and exit routines to writing.
e
s 00024/00062/00056
d D 7.13 92/07/05 14:39:39 bostic 25 24
c describe ap (Kirk); delete lfs_mntinvalbuf, lfs_vinvalbuf, add
c lfs_seglock/unlock
e
s 00069/00001/00049
d D 7.12 92/06/23 00:06:33 bostic 24 23
c directory ops, unmount, minor cleanup; from Margo Seltzer
e
s 00007/00015/00043
d D 7.11 92/05/15 13:55:29 heideman 23 22
c vnodeop argument macro expansion
e
s 00010/00005/00048
d D 7.10 92/05/14 17:29:42 heideman 22 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/14 17:05:55 heideman 21 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/14 16:46:52 heideman 20 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/14 16:36:46 heideman 19 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/14 15:57:12 heideman 18 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/14 15:42:46 heideman 17 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/14 14:48:43 heideman 16 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/14 12:52:29 heideman 15 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/14 11:49:47 heideman 14 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/14 10:30:02 heideman 13 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/13 23:08:34 heideman 12 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/13 18:55:11 heideman 11 9
c vnode interface conversion
e
s 00010/00005/00048
d R 7.10 92/05/13 18:27:15 heideman 10 9
c vnode interface conversion
e
s 00000/00022/00053
d D 7.9 92/03/04 12:41:34 bostic 9 8
c move lfs_ifind into lfs_inode.c, it's only used in one place
e
s 00000/00019/00075
d D 7.8 92/01/18 13:28:50 bostic 8 7
c changes to make lfs_vget retrieve the IFILE inode like any other
c inode
e
s 00000/00002/00094
d D 7.7 92/01/09 08:39:27 bostic 7 6
c lfs_itod CAN return LFS_UNUSED_ADDRESS since lfs_bmapv and lfs_markv
c can be passed blocks which belong to deleted files.
e
s 00001/00001/00095
d D 7.6 91/12/31 14:55:07 bostic 6 5
c delete LFS_IRELEASE, just do a brelse
e
s 00002/00030/00094
d D 7.5 91/12/14 18:44:36 bostic 5 4
c inline lfs_iset in lfs_segment.c; use LFS_IRELEASE/LFS_IWRITE macros
e
s 00006/00023/00118
d D 7.4 91/12/06 16:35:20 bostic 4 3
c LFS version 2; move lfs_getversion to lfs_segment.c
e
s 00005/00003/00136
d D 7.3 91/11/05 15:28:37 mckusick 3 2
c reorganization to move ufsmount ops to be vnode ops; blkatoff
e
s 00001/00001/00138
d D 7.2 91/11/01 17:52:15 bostic 2 1
c fix copyright, this was done from scratch
e
s 00139/00000/00000
d D 7.1 91/11/01 17:47:01 bostic 1 0
c UFS/FFS split for LFS version 1; lfs moves down one level
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1986, 1989, 1991 Regents of the University of California.
E 2
I 2
D 27
 * Copyright (c) 1991 Regents of the University of California.
E 2
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/buf.h>
I 24
#include <sys/mount.h>
I 26
#include <sys/malloc.h>
#include <sys/proc.h>
E 26
E 24

#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
D 24

E 24
#include <ufs/lfs/lfs.h>
#include <ufs/lfs/lfs_extern.h>

/*
 * Return buffer with the contents of block "offset" from the beginning of
 * directory "ip".  If "res" is non-zero, fill it in with a pointer to the
 * remaining space in the directory.
 */
int
D 3
lfs_blkatoff(ip, offset, res, bpp)
	struct inode *ip;
E 3
I 3
D 22
lfs_blkatoff(vp, offset, res, bpp)
	struct vnode *vp;
E 3
	off_t offset;
	char **res;
	struct buf **bpp;
E 22
I 22
D 25
lfs_blkatoff (ap)
	struct vop_blkatoff_args *ap;
E 25
I 25
lfs_blkatoff(ap)
	struct vop_blkatoff_args /* {
		struct vnode *a_vp;
		off_t a_offset;
		char **a_res;
		struct buf **a_bpp;
	} */ *ap;
E 25
D 23
#define vp (ap->a_vp)
#define offset (ap->a_offset)
#define res (ap->a_res)
#define bpp (ap->a_bpp)
E 23
E 22
{
	register struct lfs *fs;
I 3
	struct inode *ip;
E 3
	struct buf *bp;
D 29
	daddr_t lbn;
E 29
I 29
	ufs_daddr_t lbn;
E 29
	int bsize, error;

I 3
D 23
	ip = VTOI(vp);
E 23
I 23
	ip = VTOI(ap->a_vp);
E 23
E 3
	fs = ip->i_lfs;
D 23
	lbn = lblkno(fs, offset);
E 23
I 23
	lbn = lblkno(fs, ap->a_offset);
E 23
D 30
	bsize = blksize(fs);
E 30
I 30
	bsize = blksize(fs, ip, lbn);
E 30

D 23
	*bpp = NULL;
D 3
	if (error = bread(ITOV(ip), lbn, bsize, NOCRED, &bp)) {
E 3
I 3
	if (error = bread(vp, lbn, bsize, NOCRED, &bp)) {
E 23
I 23
	*ap->a_bpp = NULL;
	if (error = bread(ap->a_vp, lbn, bsize, NOCRED, &bp)) {
E 23
E 3
		brelse(bp);
		return (error);
	}
D 23
	if (res)
		*res = bp->b_un.b_addr + blkoff(fs, offset);
	*bpp = bp;
E 23
I 23
	if (ap->a_res)
D 28
		*ap->a_res = bp->b_un.b_addr + blkoff(fs, ap->a_offset);
E 28
I 28
		*ap->a_res = (char *)bp->b_data + blkoff(fs, ap->a_offset);
E 28
	*ap->a_bpp = bp;
E 23
	return (0);
I 24
}

I 26

E 26
D 25
int
lfs_mntinvalbuf(mp)
	struct mount *mp;
E 25
I 25
/*
 * lfs_seglock --
 *	Single thread the segment writer.
 */
void
D 26
lfs_seglock(fs)
E 26
I 26
lfs_seglock(fs, flags)
E 26
	struct lfs *fs;
I 26
	unsigned long flags;
E 26
E 25
{
D 25
	struct vnode *vp;
	int dirty;

	dirty = 0;
	if ((mp->mnt_flag & MNT_MPBUSY) == 0)
		panic("lfs_mntinvalbuf: not busy");
loop:
	for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf) {
		if (VTOI(vp)->i_number == LFS_IFILE_INUM)
			continue;
		if (vget(vp))
			goto loop;
		dirty += lfs_vinvalbuf(vp);
		vput(vp);
		if (vp->v_mount != mp)
			goto loop;
	}
	return (dirty);
E 25
I 25
D 26
	while (fs->lfs_seglock)
		(void)tsleep(&fs->lfs_seglock, PRIBIO + 1, "lfs seglock", 0);
E 26
I 26
	struct segment *sp;
	int s;

	if (fs->lfs_seglock)
		if (fs->lfs_lockpid == curproc->p_pid) {
			++fs->lfs_seglock;
			fs->lfs_sp->seg_flags |= flags;
			return;			
		} else while (fs->lfs_seglock)
			(void)tsleep(&fs->lfs_seglock, PRIBIO + 1,
			    "lfs seglock", 0);

E 26
	fs->lfs_seglock = 1;
E 25
D 26
}
E 26
I 26
	fs->lfs_lockpid = curproc->p_pid;
E 26

I 26
	sp = fs->lfs_sp = malloc(sizeof(struct segment), M_SEGMENT, M_WAITOK);
	sp->bpp = malloc(((LFS_SUMMARY_SIZE - sizeof(SEGSUM)) /
D 29
	    sizeof(daddr_t) + 1) * sizeof(struct buf *), M_SEGMENT, M_WAITOK);
E 29
I 29
	    sizeof(ufs_daddr_t) + 1) * sizeof(struct buf *),
	    M_SEGMENT, M_WAITOK);
E 29
	sp->seg_flags = flags;
	sp->vp = NULL;
	(void) lfs_initseg(fs);

	/*
	 * Keep a cumulative count of the outstanding I/O operations.  If the
	 * disk drive catches up with us it could go to zero before we finish,
	 * so we artificially increment it by one until we've scheduled all of
	 * the writes we intend to do.
	 */
	s = splbio();
	++fs->lfs_iocount;
	splx(s);
}
E 26
/*
D 25
 * For LFS, we need to do two passes.  First we need to wait on any dirty and
 * busy buffers.  Once we've guaranteed that all the buffers are unbusy, we
 * can do the segment write.  Then we need to go through and invalidate all
 * the buffers on the clean list.
E 25
I 25
 * lfs_segunlock --
 *	Single thread the segment writer.
E 25
 */
D 25
int
lfs_vinvalbuf(vp)
	register struct vnode *vp;
E 25
I 25
void
lfs_segunlock(fs)
	struct lfs *fs;
E 25
{
D 25
	register struct buf *bp;
	struct buf *nbp, *blist;
	int s, dirty = 0;

loop:	for (bp = vp->v_dirtyblkhd; bp; bp = nbp) {
		nbp = bp->b_blockf;
		s = splbio();
		if (bp->b_flags & B_BUSY) {
			bp->b_flags |= B_WANTED;
			sleep((caddr_t)bp, PRIBIO + 1);
			splx(s);
			goto loop;
		}
		bremfree(bp);
		splx(s);
		dirty++;
		brelse(bp);
	}
	if (dirty)
		lfs_segwrite(vp->v_mount, 0);

	/* Remove blocks from the clean list. */
	for (bp = vp->v_cleanblkhd; bp; bp = nbp) {
		nbp = bp->b_blockf;
		bremfree(bp);
		bp->b_flags |= B_INVAL;
		brelse(bp);
	}

	if (vp->v_dirtyblkhd || vp->v_cleanblkhd)
		panic("lfs_vinvalbuf: flush failed");
	return (dirty);
E 25
I 25
D 26
	fs->lfs_seglock = 0;
	wakeup(&fs->lfs_seglock);	/* XXX: May not be necessary. */
E 26
I 26
	struct segment *sp;
	unsigned long sync, ckp;
	int s;

	if (fs->lfs_seglock == 1) {

		sp = fs->lfs_sp;
		sync = sp->seg_flags & SEGM_SYNC;
		ckp = sp->seg_flags & SEGM_CKP;
		if (sp->bpp != sp->cbpp) {
			/* Free allocated segment summary */
			fs->lfs_offset -= LFS_SUMMARY_SIZE / DEV_BSIZE;
			brelvp(*sp->bpp);
D 28
			free((*sp->bpp)->b_un.b_addr, M_SEGMENT);
E 28
I 28
			free((*sp->bpp)->b_data, M_SEGMENT);
E 28
			free(*sp->bpp, M_SEGMENT);
		} else
			printf ("unlock to 0 with no summary");
		free(sp->bpp, M_SEGMENT);
		free(sp, M_SEGMENT);

		/*
		 * If the I/O count is non-zero, sleep until it reaches zero.
		 * At the moment, the user's process hangs around so we can
		 * sleep.
		 */
		s = splbio();
		--fs->lfs_iocount;
		/*
		 * We let checkpoints happen asynchronously.  That means
		 * that during recovery, we have to roll forward between
		 * the two segments described by the first and second
		 * superblocks to make sure that the checkpoint described
		 * by a superblock completed.
		 */
		if (sync && fs->lfs_iocount)
		    (void)tsleep(&fs->lfs_iocount, PRIBIO + 1, "lfs vflush", 0);
		splx(s);
		if (ckp) {
			fs->lfs_nactive = 0;
			lfs_writesuper(fs);
		}
		--fs->lfs_seglock;
		fs->lfs_lockpid = 0;
		wakeup(&fs->lfs_seglock);
	} else if (fs->lfs_seglock == 0) {
		panic ("Seglock not held");
	} else {
		--fs->lfs_seglock;
	}
E 26
E 25
E 24
}
I 22
D 23
#undef vp
#undef offset
#undef res
#undef bpp
E 23
E 22
D 9

D 4
/* Return the current version number for a specific inode. */
u_long
lfs_getversion(fs, ino)
	struct lfs *fs;
	ino_t ino;
{
	BUF *bp;
	IFILE *ifp;
	u_long version;

	/*
	 * Read the appropriate block from the ifile.  Return the
	 * version number.
	 */
	LFS_IENTRY(ifp, fs, ino, bp);
	version = ifp->if_version;
	brelse(bp);
	return (version);
}

E 4
/* Search a block for a specific dinode. */
DINODE *
lfs_ifind(fs, ino, page)
	struct lfs *fs;
	ino_t ino;
	void *page;
{
	register DINODE *dip;
	register int cnt;

D 4
#ifdef ALLOCPRINT
E 4
I 4
#ifdef VERBOSE
E 4
	printf("lfs_ifind: inode %d\n", ino);
#endif
	dip = page;
	for (cnt = INOPB(fs); cnt--; ++dip)
		if (dip->di_inum == ino)
			return (dip);

	panic("lfs_ifind: dinode %u not found", ino);
	/* NOTREACHED */
}
E 9
D 8

D 5
/* Set values in the ifile for the inode. */
void
lfs_iset(ip, daddr, atime)
	INODE *ip;
	daddr_t daddr;
	time_t atime;
{
	BUF *bp;
	IFILE *ifp;
	struct lfs *fs;
	ino_t ino;

D 4
#ifdef ALLOCPRINT
E 4
I 4
#ifdef VERBOSE
E 4
	printf("lfs_iset: setting ino %d daddr %lx time %lx\n",
	    ip->i_number, daddr, atime);
#endif

	fs = ip->i_lfs;
	ino = ip->i_number;
	LFS_IENTRY(ifp, fs, ino, bp);

	ifp->if_daddr = daddr;
	ifp->if_st_atime = atime;
	lfs_bwrite(bp);
}

/* Translate an inode number to a disk address. */
E 5
daddr_t
lfs_itod(fs, ino)
	struct lfs *fs;
	ino_t ino;
{
	BUF *bp;
	IFILE *ifp;
	daddr_t iaddr;

I 4
#ifdef VERBOSE
	printf("lfs_itod %d\n", ino);
#endif
E 4
D 5
	/* Read the appropriate block from the ifile. */
E 5
I 5
	/* Translate an inode number to a disk address. */
E 5
	LFS_IENTRY(ifp, fs, ino, bp);
D 5

E 5
D 7
	if (ifp->if_daddr == LFS_UNUSED_DADDR)
D 4
		panic("itod: unused disk address");
E 4
I 4
		panic("lfs_itod: unused disk address");
E 7
E 4
	iaddr = ifp->if_daddr;
D 5
	brelse(bp);
E 5
I 5
D 6
	LFS_IRELEASE(fs, bp);
E 6
I 6
	brelse(bp);
E 6
E 5
	return (iaddr);
}
E 8
E 1
