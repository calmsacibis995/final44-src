/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	vfs_bio.c,v $
 * Revision 2.10  91/04/10  16:35:58  mbj
 * 	Undid one change in binvalfree().  It was not necessary to
 * 	compare the b_dev for binvalfree.
 * 	[91/03/14            berman]
 * 
 * Revision 2.9  91/01/23  13:31:22  berman
 * 	Changed tests in binval() binvalfree() and bflush() to depend on
 * 	bp->b_dev and vp->v_rdev.  These are more in spirit with the
 * 	original code and work correctly when accessing unmounted block
 * 	devices.
 * 	[91/01/23            berman]
 * 
 * Revision 2.8  89/10/03  19:28:12  rpd
 * 	Removed dlb's invalid-buffer hack in bwrite; panic instead.
 * 	Modified brelse to handle B_USELESS.  Removed jsb's hack
 * 	to binval; made it panic when it sees B_DELWRI buffers.
 * 	[89/10/02  16:11:31  rpd]
 * 
 * Revision 2.7  89/08/02  08:11:26  jsb
 * 	Eliminated MACH conditionals.
 * 	[89/07/31  16:03:43  jsb]
 * 
 * Revision 2.6  89/05/01  17:03:33  rpd
 * 	Picked up fix from dlb for bwrite, to keep it from writing
 * 	an invalid (B_INVAL) buffer.
 * 	[89/05/01  14:09:15  rpd]
 * 
 * Revision 2.5  89/04/22  15:34:06  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  22:44:14  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:12:49  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:24:57  jsb
 * 	Include file references; change binval() to compare dev_t's, not vnodes
 * 	(since there are at least two vnodes associated with each open block
 * 	device, and the comparison was failing when it wan't suppose to).
 * 	[89/01/17  15:56:25  jsb]
 *
 * 26-Oct-87  Peter King (king) at NeXT
 *	Original Sun source, upgraded to Mach
 */ 

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include <sys/vm.h>
#include <sys/trace.h>
#include <sys/inode.h>

int	BQ_AGE_DISABLE = 1;

struct	buf *buf;		/* the buffer pool itself */
char	*buffers;
int	nbuf,			/* number of buffer headers */
	bufpages;		/* number of memory pages in the buffer pool */

struct	bufhd bufhash[BUFHSZ];	/* heads of hash lists */
struct	buf bfreelist[BQUEUES];	/* heads of available lists */

#ifdef	TRACE
char	traceflags[TR_NFLAGS];
struct	proc *traceproc;
int	tracebuf[TRCSIZ];
unsigned tracex;
int	tracewhich;
#endif	TRACE

/*
 * Read in (if necessary) the block and return a buffer pointer.
 */
struct buf *
bread(vp, blkno, size)
	struct vnode *vp;
	daddr_t blkno;
	int size;
{
	register struct buf *bp;

	if (size == 0)
		panic("bread: size 0");
	bp = getblk(vp, blkno, size);
	if (bp->b_flags&B_DONE) {
		trace(TR_BREADHIT, vp, blkno);
		return (bp);
	}
	bp->b_flags |= B_READ;
	if (bp->b_bcount > bp->b_bufsize)
		panic("bread");
	VOP_STRATEGY(bp);
	trace(TR_BREADMISS, vp, blkno);
	u.u_ru.ru_inblock++;		/* pay for read */
	biowait(bp);
	return (bp);
}

/*
 * Read in the block, like bread, but also start I/O on the
 * read-ahead block (which is not allocated to the caller)
 */
struct buf *
breada(vp, blkno, size, rablkno, rabsize)
	struct vnode *vp;
	daddr_t blkno; int size;
	daddr_t rablkno; int rabsize;
{
	register struct buf *bp, *rabp;

	bp = NULL;
	/*
	 * If the block isn't in core, then allocate
	 * a buffer and initiate i/o (getblk checks
	 * for a cache hit).
	 */
	if (!incore(vp, blkno)) {
		bp = getblk(vp, blkno, size);
		if ((bp->b_flags&B_DONE) == 0) {
			bp->b_flags |= B_READ;
			if (bp->b_bcount > bp->b_bufsize)
				panic("breada");
			VOP_STRATEGY(bp);
			trace(TR_BREADMISS, vp, blkno);
			u.u_ru.ru_inblock++;		/* pay for read */
		} else
			trace(TR_BREADHIT, vp, blkno);
	}

	/*
	 * If there's a read-ahead block, start i/o
	 * on it also (as above).
	 */
	if (rablkno && !incore(vp, rablkno)) {
		rabp = getblk(vp, rablkno, rabsize);
		if (rabp->b_flags & B_DONE) {
			brelse(rabp);
			trace(TR_BREADHITRA, vp, blkno);
		} else {
			rabp->b_flags |= B_READ|B_ASYNC;
			if (rabp->b_bcount > rabp->b_bufsize)
				panic("breadrabp");
			VOP_STRATEGY(rabp);
			trace(TR_BREADMISSRA, vp, rablock);
			u.u_ru.ru_inblock++;		/* pay in advance */
		}
	}

	/*
	 * If block was in core, let bread get it.
	 * If block wasn't in core, then the read was started
	 * above, and just wait for it.
	 */
	if (bp == NULL)
		return (bread(vp, blkno, size));
	biowait(bp);
	return (bp);
}

/*
 * Write the buffer, waiting for completion.
 * Then release the buffer.
 */
bwrite(bp)
	register struct buf *bp;
{
	register flag;

	flag = bp->b_flags;
	bp->b_flags &= ~(B_READ | B_DONE | B_ERROR | B_DELWRI);
	if (flag & B_INVAL)
		panic("bwrite: invalid buffer");
	if ((flag&B_DELWRI) == 0)
		u.u_ru.ru_oublock++;		/* noone paid yet */
	trace(TR_BWRITE, bp->b_vp, bp->b_blkno);
	if (bp->b_bcount > bp->b_bufsize)
		panic("bwrite");
	VOP_STRATEGY(bp);

	/*
	 * If the write was synchronous, then await i/o completion.
	 * If the write was "delayed", then we put the buffer on
	 * the q of blocks awaiting i/o completion status.
	 */
	if ((flag&B_ASYNC) == 0) {
		biowait(bp);
		brelse(bp);
	} else if (flag & B_DELWRI)
		bp->b_flags |= B_AGE;
}

/*
 * Release the buffer, marking it so that if it is grabbed
 * for another purpose it will be written out before being
 * given up (e.g. when writing a partial block where it is
 * assumed that another write for the same block will soon follow).
 * This can't be done for magtape, since writes must be done
 * in the same order as requested.
 */
bdwrite(bp)
	register struct buf *bp;
{

	if ((bp->b_flags&B_DELWRI) == 0)
		u.u_ru.ru_oublock++;		/* noone paid yet */
#ifdef	notdef
	/*
	 * This does not work for buffers associated with
	 * vnodes that are remote - they have no dev.
	 * Besides, we don't use bio with tapes, so rather
	 * than develop a fix, we just ifdef this out for now.
	 */
	if (bdevsw[major(bp->b_dev)].d_flags & B_TAPE)
		bawrite(bp);
	else {
		bp->b_flags |= B_DELWRI | B_DONE;
		brelse(bp);
	}
#endif
	bp->b_flags |= B_DELWRI | B_DONE;
	brelse(bp);
}

/*
 * Release the buffer, start I/O on it, but don't wait for completion.
 */
bawrite(bp)
	register struct buf *bp;
{

	bp->b_flags |= B_ASYNC;
	bwrite(bp);
}

/*
 * Release the buffer, with no I/O implied.
 */
brelse(bp)
	register struct buf *bp;
{
	register struct buf *flist;
	register s;

	/*
	 * If someone's waiting for the buffer, or
	 * is waiting for a buffer wake 'em up.
	 */
	if (bp->b_flags&B_WANTED)
		wakeup((caddr_t)bp);
	if (bfreelist[0].b_flags&B_WANTED) {
		bfreelist[0].b_flags &= ~B_WANTED;
		wakeup((caddr_t)bfreelist);
	}
	if (bp->b_flags & B_NOCACHE) {
		bp->b_flags |= B_INVAL;
	}
	if (bp->b_flags&B_ERROR)
		if (bp->b_flags & B_LOCKED)
			bp->b_flags &= ~B_ERROR;	/* try again later */
		else
			brelvp(bp);

	/*
	 * Stick the buffer back on a free list.
	 */
	s = spl6();
	if (bp->b_bufsize <= 0) {
		/* block has no buffer ... put at front of unused buffer list */
		flist = &bfreelist[BQ_EMPTY];
		binsheadfree(bp, flist);
	} else if (bp->b_flags & (B_ERROR|B_INVAL)) {
		/* block has no info ... put at front of most free list */
		flist = &bfreelist[BQ_AGE];
		binsheadfree(bp, flist);
	} else {
		if (bp->b_flags & B_LOCKED)
			flist = &bfreelist[BQ_LOCKED];
		else if (((bp->b_flags & B_AGE) && (BQ_AGE_DISABLE == 0)) ||
			 (bp->b_flags & B_USELESS))
			flist = &bfreelist[BQ_AGE];
		else
			flist = &bfreelist[BQ_LRU];
		binstailfree(bp, flist);
	}
	bp->b_flags &= ~(B_WANTED|B_BUSY|B_ASYNC|B_AGE|B_NOCACHE|B_USELESS);
	(void) splx(s);
}

/*
 * See if the block is associated with some buffer
 * (mainly to avoid getting hung up on a wait in breada)
 */
incore(vp, blkno)
	struct vnode *vp;
	daddr_t blkno;
{
	register struct buf *bp;
	register struct buf *dp;

	dp = BUFHASH(vp, blkno);
	for (bp = dp->b_forw; bp != dp; bp = bp->b_forw)
		if (bp->b_blkno == blkno && ITOV(bp->b_ip) == vp &&
		    (bp->b_flags & B_INVAL) == 0)
			return (1);
	return (0);
}

struct buf *
baddr(vp, blkno, size)
	struct vnode *vp;
	daddr_t blkno;
	int size;
{

	if (incore(vp, blkno))
		return (bread(vp, blkno, size));
	return (0);
}

/*
 * Assign a buffer for the given block.  If the appropriate
 * block is already associated, return it; otherwise search
 * for the oldest non-busy buffer and reassign it.
 *
 * We use splx here because this routine may be called
 * on the interrupt stack during a dump, and we don't
 * want to lower the ipl back to 0.
 */
struct buf *
getblk(vp, blkno, size)
	struct vnode *vp;
	daddr_t blkno;
	int size;
{
	register struct buf *bp, *dp;
	int s;

	if (vp == (struct vnode *)0) {
		printf("vp=0x%x, blkno=0x%x, size=0x%x\n", vp, blkno, size);
		panic("getblk: Illegal vnode pointer");
	}
	if ((unsigned)blkno >= 1 << (sizeof(int)*NBBY-DEV_BSHIFT))    /* XXX */
		blkno = 1 << ((sizeof(int)*NBBY-DEV_BSHIFT) + 1);
	/*
	 * Search the cache for the block.  If we hit, but
	 * the buffer is in use for i/o, then we wait until
	 * the i/o has completed.
	 */
	dp = BUFHASH(vp, blkno);
loop:
	for (bp = dp->b_forw; bp != dp; bp = bp->b_forw) {
		if (bp->b_blkno != blkno || ITOV(bp->b_ip) != vp ||
		    bp->b_flags&B_INVAL)
			continue;
		s = spl6();
		if (bp->b_flags&B_BUSY) {
			bp->b_flags |= B_WANTED;
			(void) sleep((caddr_t)bp, PRIBIO+1);
			(void) splx(s);
			goto loop;
		}
		(void) splx(s);
		notavail(bp);
		if (brealloc(bp, size) == 0)
			goto loop;
		bp->b_flags |= B_CACHE;
		return (bp);
	}
/*
	if (major(dev) >= nblkdev)
		panic("blkdev");
*/
#if	VME
	{ extern int paging_no_sleep;
	if (paging_no_sleep == 1)
		paging_no_sleep = 2;
	}
#endif	VME
	bp = getnewbuf();
	bfree(bp);
	bremhash(bp);
	bsetvp(bp, vp);
	bp->b_dev = vp->v_rdev;
	bp->b_blkno = blkno;
	bp->b_error = 0;
	bp->b_resid = 0;
	binshash(bp, dp);
	if (brealloc(bp, size) == 0)
		goto loop;
	return (bp);
}

/*
 * get an empty block,
 * not assigned to any particular device
 */
struct buf *
geteblk(size)
	int size;
{
	register struct buf *bp, *flist;

loop:
	bp = getnewbuf();
	bp->b_flags |= B_INVAL;
	bfree(bp);
	bremhash(bp);
	flist = &bfreelist[BQ_AGE];
	brelvp(bp);
	bp->b_error = 0;
	bp->b_resid = 0;
	binshash(bp, flist);
	if (brealloc(bp, size) == 0)
		goto loop;
	return (bp);
}

/*
 * Allocate space associated with a buffer.
 * If can't get space, buffer is released
 */
brealloc(bp, size)
	register struct buf *bp;
	int size;
{
	daddr_t start, last;
	register struct buf *ep;
	struct buf *dp;
	int s;

	/*
	 * First need to make sure that all overlaping previous I/O
	 * is dispatched with.
	 */
	if (size == bp->b_bcount)
		return (1);
	if (size < bp->b_bcount) { 
		if (bp->b_flags & B_DELWRI) {
			bwrite(bp);
			return (0);
		}
		if (bp->b_flags & B_LOCKED)
			panic("brealloc");
		return (allocbuf(bp, size));
	}
	bp->b_flags &= ~B_DONE;
	if (bp->b_ip == (struct inode *) 0)
		return (allocbuf(bp, size));

	/*
	 * Search cache for any buffers that overlap the one that we
	 * are trying to allocate. Overlapping buffers must be marked
	 * invalid, after being written out if they are dirty. (indicated
	 * by B_DELWRI) A disk block must be mapped by at most one buffer
	 * at any point in time. Care must be taken to avoid deadlocking
	 * when two buffer are trying to get the same set of disk blocks.
	 */
	start = bp->b_blkno;
	last = start + btodb(size) - 1;
	dp = BUFHASH(bp->b_vp, bp->b_blkno);
loop:
	for (ep = dp->b_forw; ep != dp; ep = ep->b_forw) {
		if (ep == bp || ep->b_vp != bp->b_vp || (ep->b_flags&B_INVAL))
			continue;
		/* look for overlap */
		if (ep->b_bcount == 0 || ep->b_blkno > last ||
		    ep->b_blkno + btodb(ep->b_bcount) <= start)
			continue;
		s = spl6();
		if (ep->b_flags&B_BUSY) {
			ep->b_flags |= B_WANTED;
			(void) sleep((caddr_t)ep, PRIBIO+1);
			(void) splx(s);
			goto loop;
		}
		(void) splx(s);
		notavail(ep);
		if (ep->b_flags & B_DELWRI) {
			bwrite(ep);
			goto loop;
		}
		ep->b_flags |= B_INVAL;
		brelse(ep);
	}
	return (allocbuf(bp, size));
}

/*
 * Find a buffer which is available for use.
 * Select something from a free list.
 * Preference is to AGE list, then LRU list.
 */
struct buf *
getnewbuf()
{
	register struct buf *bp, *dp;
	int s;

loop:
	s = spl6();
	for (dp = &bfreelist[BQ_AGE]; dp > bfreelist; dp--)
		if (dp->av_forw != dp)
			break;
	if (dp == bfreelist) {		/* no free blocks */
		dp->b_flags |= B_WANTED;
		(void) sleep((caddr_t)dp, PRIBIO+1);
		(void) splx(s);
		goto loop;
	}
	(void) splx(s);
	bp = dp->av_forw;
	notavail(bp);
	if (bp->b_flags & B_DELWRI) {
		bp->b_flags |= B_ASYNC;
		bwrite(bp);
		goto loop;
	}
	brelvp(bp);
	trace(TR_BRELSE, bp->b_vp, bp->b_blkno);
	bp->b_flags = B_BUSY;
	return (bp);
}

/*
 * Wait for I/O completion on the buffer; return errors
 * to the user.
 */
biowait(bp)
	register struct buf *bp;
{
	int s;

	s = spl6();
	while ((bp->b_flags&B_DONE)==0)
		(void) sleep((caddr_t)bp, PRIBIO);
	(void) splx(s);
	if (u.u_error == 0)			/* XXX */
		u.u_error = geterror(bp);
}

/*
 * Mark I/O complete on a buffer.
 * If someone should be called, e.g. the pageout
 * daemon, do so.  Otherwise, wake up anyone
 * waiting for it.
 */
biodone(bp)
	register struct buf *bp;
{

	if (bp->b_flags & B_DONE)
		panic("dup biodone");
	bp->b_flags |= B_DONE;
	if (bp->b_flags & B_CALL) {
		bp->b_flags &= ~B_CALL;
		(*bp->b_iodone)(bp);
		return;
	}
	if (bp->b_flags&B_ASYNC)
		brelse(bp);
	else {
		bp->b_flags &= ~B_WANTED;
		wakeup((caddr_t)bp);
	}
}

/*
 * Insure that no part of a specified block is in an incore buffer.
 */
blkflush(vp, blkno, size)
	struct vnode *vp;
	daddr_t blkno;
	u_long size;
{
	register struct buf *ep;
	struct buf *dp;
	daddr_t start, last;
	int s;

	start = blkno;
	last = start + btodb(size) - 1;
	dp = BUFHASH(vp, blkno);
loop:
	for (ep = dp->b_forw; ep != dp; ep = ep->b_forw) {
		if (ITOV(ep->b_ip) != vp || (ep->b_flags&B_INVAL))
			continue;
		/* look for overlap */
		if (ep->b_bcount == 0 || ep->b_blkno > last ||
		    ep->b_blkno + btodb(ep->b_bcount) <= start)
			continue;
		s = spl6();
		if (ep->b_flags&B_BUSY) {
			ep->b_flags |= B_WANTED;
			(void) sleep((caddr_t)ep, PRIBIO+1);
			(void) splx(s);
			goto loop;
		}
		if (ep->b_flags & B_DELWRI) {
			(void) splx(s);
			notavail(ep);
			bwrite(ep);
			goto loop;
		}
		(void) splx(s);
	}
}

/*
 * Make sure all write-behind blocks
 * associated with vp
 * are flushed out.
 * (from fsync)
 */
bflush(vp)
	struct vnode *vp;
{
	register struct buf *bp;
	register struct buf *flist;
	int s;

loop:
	s = spl6();
	for (flist = bfreelist; flist < &bfreelist[BQ_EMPTY]; flist++)
	for (bp = flist->av_forw; bp != flist; bp = bp->av_forw) {
		if ((bp->b_flags & B_DELWRI) == 0)
			continue;
		if (vp == (struct vnode *) 0 || vp->v_rdev == bp->b_dev) {
			bp->b_flags |= B_ASYNC;
			notavail(bp);
			(void) splx(s);
			bwrite(bp);
			goto loop;
		}
	}
	(void) splx(s);
}

/*
 * Invalidate blocks associated with vp which are on the freelist.
 * Make sure all write-behind blocks associated with vp are flushed out.
 */
binvalfree(vp)
	struct vnode *vp;
{
	register struct buf *bp;
	register struct buf *flist;
	int s;

loop:
	s = spl6();
	for (flist = bfreelist; flist < &bfreelist[BQ_EMPTY]; flist++)
	for (bp = flist->av_forw; bp != flist; bp = bp->av_forw) {
		if (vp == ITOV(bp->b_ip) || vp == (struct vnode *) 0) {
			if (bp->b_flags & B_DELWRI) {
				bp->b_flags |= B_ASYNC;
				notavail(bp);
				(void) splx(s);
				bwrite(bp);
			} else {
				bp->b_flags |= B_INVAL;
				brelvp(bp);
				(void) splx(s);
			}
			goto loop;
		}
	}
	(void) splx(s);
}

/*
 * Pick up the device's error number and pass it to the user;
 * if there is an error but the number is 0 set a generalized
 * code.  Actually the latter is always true because devices
 * don't yet return specific errors.
 */
geterror(bp)
	register struct buf *bp;
{
	int error = 0;

	if (bp->b_flags&B_ERROR)
		if ((error = bp->b_error)==0)
			return (EIO);
	return (error);
}

/*
 * Invalidate in core blocks belonging to closed or umounted filesystem
 *
 * This is not nicely done at all - the buffer ought to be removed from the
 * hash chains & have its dev/blkno fields clobbered, but unfortunately we
 * can't do that here, as it is quite possible that the block is still
 * being used for i/o. Eventually, all disc drivers should be forced to
 * have a close routine, which ought ensure that the queue is empty, then
 * properly flush the queues. Until that happy day, this suffices for
 * correctness.						... kre
 * This routine assumes that all the buffers have been written.
 */
binval(vp)
	struct vnode *vp;
{
	register struct buf *bp;
	register struct bufhd *hp;
#define dp ((struct buf *)hp)

loop:
	for (hp = bufhash; hp < &bufhash[BUFHSZ]; hp++)
		for (bp = dp->b_forw; bp != dp; bp = bp->b_forw)
			if ((vp->v_rdev == bp->b_dev) && (bp->b_flags & B_INVAL) == 0) {
				if (bp->b_flags & B_DELWRI)
					panic("binval");
				bp->b_flags |= B_INVAL;
				brelvp(bp);
				goto loop;
			}
}

bsetvp(bp, vp)
	struct buf *bp;
	struct vnode *vp;
{
	if (bp->b_vp) {
		brelvp(bp);
	}
	VN_HOLD(vp);
	bp->b_ip = VTOI(vp);
}

brelvp(bp)
	struct buf *bp;
{
	struct vnode *vp;

	if (bp->b_ip == (struct inode *) 0) {
		return;
	}
	vp = ITOV(bp->b_ip);	/* save vp because VN_RELE may sleep */
	bp->b_ip = (struct inode *) 0;
	VN_RELE(vp);
}
