h45802
s 00001/00000/00171
d D 8.10 95/06/10 05:43:07 margo 45 44
c Do wakeup on next seg as well as generic cleaner wakeup in case 
c multiple cleaners are running.
e
s 00013/00005/00158
d D 8.9 95/05/20 01:23:11 mckusick 44 43
c merge vfs_lock and vfs_busy; interlock mount points properly
e
s 00002/00001/00161
d D 8.8 95/05/09 12:28:06 mckusick 43 42
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00004/00003/00158
d D 8.7 95/05/08 12:15:15 mckusick 42 41
c update from margo
e
s 00001/00001/00160
d D 8.6 95/03/30 14:20:58 mckusick 41 40
c MOUNT_LFS becomes lfs_mount_type
e
s 00001/00001/00160
d D 8.5 95/03/21 00:27:52 mckusick 40 39
c daddr_t => ufs_daddr_t
e
s 00002/00004/00159
d D 8.4 93/12/30 16:13:43 mckusick 39 38
c new queue structure
e
s 00002/00002/00161
d D 8.3 93/09/23 16:14:15 bostic 38 37
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00161
d D 8.2 93/09/21 07:25:37 bostic 37 36
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00161
d D 8.1 93/06/11 16:27:18 bostic 36 35
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00001/00148
d D 7.19 92/12/10 14:16:54 margo 35 34
c Make WRITE/WAIT thresholds higher.  Add stat counting.
e
s 00017/00007/00132
d D 7.18 92/11/17 13:20:50 margo 34 33
c If out of buffers, sleep rather than return ENOSPC
e
s 00007/00002/00132
d D 7.17 92/09/02 07:57:49 margo 33 32
c Do not invalidate buffers that you return ENOSPC on (they may need 
c to be written later).
e
s 00002/00000/00132
d D 7.16 92/08/26 18:20:20 bostic 32 31
c Wakeup the cleaner when we run out of disk space.
e
s 00044/00016/00088
d D 7.15 92/08/21 17:21:31 bostic 31 30
c Fix threshholds for kicking off a write.  Make lfs_bwrite to inode 
c accounting and available disk block accounting.  Add global to determine if 
c a writer has already been kicked off to free up some buffers.  Add lfs_check 
c routine which determines if there is memory space available.
e
s 00001/00003/00103
d D 7.14 92/08/01 15:40:37 bostic 30 29
c delete VERBOSE #ifdef's
e
s 00004/00002/00102
d D 7.13 92/07/02 23:41:08 mckusick 29 28
c expand vop args
e
s 00000/00006/00104
d D 7.12 92/06/22 22:43:03 bostic 28 27
c delete PMAP_BUG_FIX_HACK for now, until see the bug again
e
s 00008/00007/00102
d D 7.11 92/06/04 09:51:31 heideman 27 26
c registerized vnodeop ops after vnode interface conversion
e
s 00007/00009/00102
d D 7.10 92/05/15 13:55:02 heideman 26 25
c vnodeop argument macro expansion
e
s 00004/00002/00107
d D 7.9 92/05/14 17:28:46 heideman 25 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/14 17:05:03 heideman 24 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/14 16:45:56 heideman 23 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/14 16:35:52 heideman 22 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/14 15:55:45 heideman 21 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/14 15:41:57 heideman 20 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/14 14:47:53 heideman 19 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/14 12:51:15 heideman 18 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/14 11:48:36 heideman 17 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/14 10:29:03 heideman 16 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/13 23:07:26 heideman 15 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/13 18:54:16 heideman 14 12
c vnode interface conversion
e
s 00004/00002/00107
d R 7.9 92/05/13 18:26:23 heideman 13 12
c vnode interface conversion
e
s 00001/00001/00108
d D 7.8 92/04/08 15:08:00 bostic 12 11
c remove the rest of the typedef's
e
s 00013/00006/00096
d D 7.7 92/04/08 14:42:40 staelin 11 10
c don't reassign multiple times; quick hack, don't reassign ifile at all
e
s 00011/00002/00091
d D 7.6 92/02/04 17:11:47 bostic 10 9
c block at bio when reassigning buffer; handle queue count more cleanly
e
s 00007/00005/00086
d D 7.5 92/02/04 12:32:36 bostic 9 8
c minor fix, don't set queue count to 0 unless did something
e
s 00058/00009/00033
d D 7.4 91/12/31 14:09:55 bostic 8 7
c add lfs_flush routine, to flush out B_LOCKED queue periodically
e
s 00001/00002/00041
d D 7.3 91/12/13 12:41:24 bostic 7 6
c no normative chnage, trivial cleanup
e
s 00018/00010/00025
d D 7.2 91/12/06 16:37:28 bostic 6 5
c LFS version 2; use B_LOCKED queue for buffers
e
s 00006/00008/00029
d D 7.1 91/11/01 17:37:02 bostic 5 4
c minor cleanup/explanation
c UFS/FFS split for LFS version 1; lfs moves down one level
e
s 00009/00012/00028
d D 5.4 91/11/01 17:24:33 bostic 4 3
c checkpoint before integration
e
s 00001/00000/00039
d D 5.3 91/10/09 11:21:41 bostic 3 2
c lint
e
s 00012/00007/00027
d D 5.2 91/10/02 09:00:24 bostic 2 1
c checkpoint
e
s 00034/00000/00000
d D 5.1 91/09/25 14:31:19 bostic 1 0
c date and time created 91/09/25 14:31:19 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 5
I 5
D 36
 * Copyright (c) 1991 Regents of the University of California.
E 5
 * All rights reserved.
E 36
I 36
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 36
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
D 4
#ifdef LOGFS
E 2
#include "param.h"
#include "proc.h"
#include "buf.h"
#include "vnode.h"
#include "specdev.h"
#include "mount.h"
#include "trace.h"
#include "resourcevar.h"
#include "lfs.h"
E 4
I 4
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/buf.h>
I 8
#include <sys/vnode.h>
E 8
#include <sys/resourcevar.h>
I 8
#include <sys/mount.h>
I 34
#include <sys/kernel.h>
E 34
E 8
E 4

I 8
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>

E 8
I 4
D 5
#include <lfs/lfs.h>
#include <lfs/lfs_extern.h>
E 5
I 5
#include <ufs/lfs/lfs.h>
#include <ufs/lfs/lfs_extern.h>
E 5

I 8
/*
 * LFS block write function.
 *
 * XXX
 * No write cost accounting is done.
 * This is almost certainly wrong for synchronous operations and NFS.
 */
I 32
int	lfs_allclean_wakeup;		/* Cleaner wakeup address. */
E 32
int	locked_queue_count;		/* XXX Count of locked-down buffers. */
I 31
int	lfs_writing;			/* Set if already kicked off a writer
					   because of buffer space */
I 35
/*
E 35
#define WRITE_THRESHHOLD	((nbuf >> 2) - 10)
#define WAIT_THRESHHOLD		((nbuf >> 1) - 10)
I 35
*/
#define WAIT_THRESHHOLD         (nbuf - (nbuf >> 2) - 10)
#define WRITE_THRESHHOLD        ((nbuf >> 1) - 10)
E 35
I 34
#define LFS_BUFWAIT	2
E 34
E 31

E 8
E 4
D 6
/*
D 2
 * lfs_bwrite --
 *	LFS version of bawrite, bdwrite, bwrite.  Set the delayed write flag
 *	and use reassignbuf to move the buffer from the clean list to the
 *	dirty one.  Then unlock the buffer.
E 2
I 2
 * LFS version of bawrite, bdwrite, bwrite.  Set the delayed write flag and
 * use reassignbuf to move the buffer from the clean list to the dirty one,
 * then unlock the buffer.
I 5
 *
 * XXX No accounting for the cost of the write is currently done.
 * XXX This is almost certainly wrong for synchronous operations, i.e. NFS.
E 5
E 2
 */
E 6
I 3
D 4
void
E 4
I 4
int
E 4
E 3
D 25
lfs_bwrite(bp)
D 12
	register BUF *bp;
E 12
I 12
	register struct buf *bp;
E 25
I 25
D 29
lfs_bwrite (ap)
	struct vop_bwrite_args *ap;
E 29
I 29
lfs_bwrite(ap)
	struct vop_bwrite_args /* {
		struct buf *a_bp;
	} */ *ap;
E 29
D 26
#define bp (ap->a_bp)
E 26
E 25
E 12
{
I 27
	register struct buf *bp = ap->a_bp;
I 31
	struct lfs *fs;
	struct inode *ip;
E 31
E 27
I 10
D 34
	int s;
E 34
I 34
D 42
	int error, s;
E 42
I 42
	int db, error, s;
E 42
E 34
E 10
I 6
D 30
#ifdef VERBOSE
printf("lfs_bwrite\n");
#endif
E 30
I 30

E 30
	/*
D 7
	 *
E 7
D 8
	 * LFS version of bawrite, bdwrite, bwrite.  Set the delayed write
	 * flag and use reassignbuf to move the buffer from the clean list
	 * to the dirty one, then unlock the buffer.  Note, we set the
	 * B_LOCKED flag, which causes brelse to move the buffer onto the
	 * LOCKED free list.  This is necessary, otherwise getnewbuf() would
	 * try to reclaim them using bawrite, which isn't going to work.
E 8
I 8
	 * Set the delayed write flag and use reassignbuf to move the buffer
	 * from the clean list to the dirty one.
E 8
	 *
D 8
	 * XXX
	 * No accounting for the cost of the write is currently done.
	 * This is almost certainly wrong for synchronous operations, i.e. NFS.
E 8
I 8
	 * Set the B_LOCKED flag and unlock the buffer, causing brelse to move
	 * the buffer onto the LOCKED free list.  This is necessary, otherwise
	 * getnewbuf() would try to reclaim the buffers using bawrite, which
	 * isn't going to work.
I 33
	 *
	 * XXX we don't let meta-data writes run out of space because they can
	 * come from the segment writer.  We need to make sure that there is
	 * enough space reserved so that there's room to write meta-data
	 * blocks.
E 33
E 8
	 */
I 8
D 11
	if (!(bp->b_flags & B_LOCKED))
E 11
I 11
D 26
	if (!(bp->b_flags & B_LOCKED)) {
E 26
I 26
D 27
	if (!(ap->a_bp->b_flags & B_LOCKED)) {
E 27
I 27
	if (!(bp->b_flags & B_LOCKED)) {
I 31
		fs = VFSTOUFS(bp->b_vp->v_mount)->um_lfs;
D 33
		if (!LFS_FITS(fs, fsbtodb(fs, 1)) && !IS_IFILE(bp)) {
			bp->b_flags |= B_INVAL;
E 33
I 33
D 34
		if (!LFS_FITS(fs, fsbtodb(fs, 1)) && !IS_IFILE(bp) &&
E 34
I 34
D 42
		while (!LFS_FITS(fs, fsbtodb(fs, 1)) && !IS_IFILE(bp) &&
E 42
I 42
		db = fragstodb(fs, numfrags(fs, bp->b_bcount));
		while (!LFS_FITS(fs, db) && !IS_IFILE(bp) &&
E 42
E 34
		    bp->b_lblkno > 0) {
E 33
D 34
			brelse(bp);
E 34
I 34
			/* Out of space, need cleaner to run */
E 34
I 32
			wakeup(&lfs_allclean_wakeup);
I 45
			wakeup(&fs->lfs_nextseg);
E 45
E 32
D 34
			return (ENOSPC);
E 34
I 34
			if (error = tsleep(&fs->lfs_avail, PCATCH | PUSER,
			    "cleaner", NULL)) {
				brelse(bp);
				return (error);
			}
E 34
		}
		ip = VTOI((bp)->b_vp);
D 37
		if (!(ip->i_flag & IMOD))
E 37
I 37
D 38
		if (!(ip->i_flag & IMODIFIED))
E 38
I 38
		if (!(ip->i_flag & IN_MODIFIED))
E 38
E 37
			++fs->lfs_uinodes;
D 37
		ip->i_flag |= IMOD | ICHG | IUPD;			\
E 37
I 37
D 38
		ip->i_flag |= IMODIFIED | ICHANGE | IUPDATE;
E 38
I 38
		ip->i_flag |= IN_CHANGE | IN_MODIFIED | IN_UPDATE;
E 38
E 37
D 42
		fs->lfs_avail -= fsbtodb(fs, 1);
E 42
I 42
		fs->lfs_avail -= db;
E 42
E 31
E 27
E 26
E 11
		++locked_queue_count;
E 8
E 6
I 2
D 5
#ifdef DO_ACCOUNTING
	Not included as this gets called from lots of places where the
	current proc structure is probably wrong.  Ignore for now.
E 2
	curproc->p_stats->p_ru.ru_oublock++;	/* XXX: no one paid yet */
D 2
	bp->b_flags &= ~(B_READ | B_DONE | B_ERROR | B_DELWRI);
	bp->b_flags |= B_DELWRI;
	reassignbuf(bp, bp->b_vp);		/* XXX: do this inline */
E 2
I 2
#endif
E 5
D 7
	bp->b_flags &= ~(B_READ | B_DONE | B_ERROR);
E 7
D 6
	bp->b_flags |= B_WRITE | B_DELWRI;
	reassignbuf(bp, bp->b_vp);		/* XXX: do this inline? */
E 6
I 6
D 11
	bp->b_flags |= B_DELWRI | B_LOCKED;
I 7
	bp->b_flags &= ~(B_READ | B_DONE | B_ERROR);
I 10
	s = splbio();
E 10
E 7
	reassignbuf(bp, bp->b_vp);
I 10
	splx(s);
E 11
I 11
D 26
		bp->b_flags |= B_DELWRI | B_LOCKED;
		bp->b_flags &= ~(B_READ | B_DONE | B_ERROR);
E 26
I 26
D 27
		ap->a_bp->b_flags |= B_DELWRI | B_LOCKED;
		ap->a_bp->b_flags &= ~(B_READ | B_DONE | B_ERROR);
E 27
I 27
		bp->b_flags |= B_DELWRI | B_LOCKED;
D 31
		bp->b_flags &= ~(B_READ | B_DONE | B_ERROR);
E 31
I 31
		bp->b_flags &= ~(B_READ | B_ERROR);
E 31
E 27
E 26
		s = splbio();
D 28
#define	PMAP_BUG_FIX_HACK
#ifdef PMAP_BUG_FIX_HACK
		if (((struct ufsmount *)
D 26
		    (bp->b_vp->v_mount->mnt_data))->um_lfs->lfs_ivnode !=
		    bp->b_vp)
E 26
I 26
D 27
		    (ap->a_bp->b_vp->v_mount->mnt_data))->um_lfs->lfs_ivnode !=
		    ap->a_bp->b_vp)
E 27
I 27
		    (bp->b_vp->v_mount->mnt_data))->um_lfs->lfs_ivnode !=
		    bp->b_vp)
E 27
E 26
#endif
E 28
D 26
		reassignbuf(bp, bp->b_vp);
E 26
I 26
D 27
		reassignbuf(ap->a_bp, ap->a_bp->b_vp);
E 27
I 27
		reassignbuf(bp, bp->b_vp);
E 27
E 26
		splx(s);
	}
E 11
E 10
E 6
E 2
D 26
	brelse(bp);
E 26
I 26
D 27
	brelse(ap->a_bp);
E 27
I 27
	brelse(bp);
E 27
E 26
I 4
	return (0);
I 8
}
I 25
D 26
#undef bp
E 26
E 25

/*
 * XXX
 * This routine flushes buffers out of the B_LOCKED queue when LFS has too
 * many locked down.  Eventually the pageout daemon will simply call LFS
D 9
 * when pages need to be reclaimed.
E 9
I 9
 * when pages need to be reclaimed.  Note, we have one static count of locked
 * buffers, so we can't have more than a single file system.  To make this
 * work for multiple file systems, put the count into the mount structure.
E 9
 */
void
lfs_flush()
{
D 44
	register struct mount *mp;
E 44
I 44
	register struct mount *mp, *nmp;
	struct proc *p = curproc;	/* XXX */
E 44
D 31
	struct mount *omp;
E 31

I 35
#ifdef DOSTATS
	++lfs_stats.write_exceeded;
#endif
E 35
D 9
	/* 800K in a 4K file system. */
	if (locked_queue_count < 200)
E 9
I 9
D 31
	/* 1M in a 4K file system. */
	if (locked_queue_count < 256)
E 31
I 31
	if (lfs_writing)
E 31
E 9
		return;
I 31
	lfs_writing = 1;
E 31
D 39
	mp = rootfs;
	do {
E 39
I 39
D 43
	for (mp = mountlist.tqh_first; mp != NULL; mp = mp->mnt_list.tqe_next) {
E 43
I 43
D 44
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist;
	     mp = mp->mnt_list.cqe_next) {
E 43
E 39
D 31
		/*
		 * The lock check below is to avoid races with mount
		 * and unmount.
		 */
E 31
I 31
		/* The lock check below is to avoid races with unmount. */
E 44
I 44
	simple_lock(&mountlist_slock);
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist; mp = nmp) {
		if (vfs_busy(mp, LK_NOWAIT, &mountlist_slock, p)) {
			nmp = mp->mnt_list.cqe_next;
			continue;
		}
E 44
E 31
D 41
		if (mp->mnt_stat.f_type == MOUNT_LFS &&
E 41
I 41
		if (mp->mnt_stat.f_type == lfs_mount_type &&
E 41
D 31
		    (mp->mnt_flag & (MNT_MLOCK|MNT_RDONLY|MNT_MPBUSY)) == 0 &&
		    !vfs_busy(mp)) {
E 31
I 31
D 44
		    (mp->mnt_flag & (MNT_MLOCK|MNT_RDONLY|MNT_UNMOUNT)) == 0 &&
E 44
I 44
		    (mp->mnt_flag & MNT_RDONLY) == 0 &&
E 44
		    !((((struct ufsmount *)mp->mnt_data))->ufsmount_u.lfs)->lfs_dirops ) {
E 31
I 10
			/*
			 * We set the queue to 0 here because we are about to
			 * write all the dirty buffers we have.  If more come
			 * in while we're writing the segment, they may not
			 * get written, so we want the count to reflect these
			 * new writes after the segwrite completes.
			 */
I 35
#ifdef DOSTATS
			++lfs_stats.flush_invoked;
#endif
E 35
D 31
			locked_queue_count = 0;
E 31
E 10
			lfs_segwrite(mp, 0);
D 31
			omp = mp;
			mp = mp->mnt_next;
			vfs_unbusy(omp);
I 9
D 10
			/* Not exact, but it doesn't matter. */
			locked_queue_count = 0;
E 10
E 9
		} else
			mp = mp->mnt_next;
E 31
I 31
		}
I 44
		simple_lock(&mountlist_slock);
		nmp = mp->mnt_list.cqe_next;
		vfs_unbusy(mp, p);
E 44
D 39
		mp = mp->mnt_next;
E 31
	} while (mp != rootfs);
E 39
I 39
	}
I 44
	simple_unlock(&mountlist_slock);
E 44
E 39
I 31
	lfs_writing = 0;
}

int
lfs_check(vp, blkno)
	struct vnode *vp;
D 40
	daddr_t blkno;
E 40
I 40
	ufs_daddr_t blkno;
E 40
{
	extern int lfs_allclean_wakeup;
	int error;

I 34
	error = 0;
E 34
	if (incore(vp, blkno))
		return (0);
	if (locked_queue_count > WRITE_THRESHHOLD)
		lfs_flush();
D 34
	if (locked_queue_count > WAIT_THRESHHOLD)
		error = tsleep(&lfs_allclean_wakeup, PCATCH | PUSER,
		    "buffers", NULL);
E 34
I 34

	/* If out of buffers, wait on writer */
D 35
	while (locked_queue_count > WAIT_THRESHHOLD)
E 35
I 35
	while (locked_queue_count > WAIT_THRESHHOLD) {
#ifdef DOSTATS
	    ++lfs_stats.wait_exceeded;
#endif
E 35
	    error = tsleep(&locked_queue_count, PCATCH | PUSER, "buffers",
	        hz * LFS_BUFWAIT);
I 35
	}
E 35

E 34
	return (error);
E 31
D 9
	/* Not exact, but it doesn't matter. */
	locked_queue_count = 0;
E 9
E 8
E 4
}
I 2
D 4
#endif /* LOGFS */
E 4
E 2
E 1
