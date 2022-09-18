/*
 * Copyright (c) 1994 John S. Dyson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice immediately at the beginning of the file, without modification,
 *    this list of conditions, and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Absolutely no warranty of function or purpose is made by the author
 *    John S. Dyson.
 * 4. Modifications may be freely made to this file if the above conditions
 *    are met.
 *
 * vfs_bio.c,v 1.16 1994/10/23 20:52:11 davidg Exp
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/buf.h>
#include <sys/mount.h>
#include <sys/malloc.h>
#include <sys/resourcevar.h>
#include <sys/proc.h>
#include <vm/vm.h>
#include <vm/vm_pageout.h>

#include <miscfs/specfs/specdev.h>

struct	buf *buf;		/* buffer header pool */
int	nbuf;			/* number of buffer headers calculated elsewhere */
struct swqueue bswlist;

extern	vm_map_t buffer_map, io_map;

void vm_hold_free_pages(vm_offset_t from, vm_offset_t to);
void vm_hold_load_pages(vm_offset_t from, vm_offset_t to);

int needsbuffer;

/*
 * Internal update daemon, process 3
 *	The variable vfs_update_wakeup allows for internal syncs.
 */
int vfs_update_wakeup;

/*
 * Initialize buffer headers and related structures.
 */
void
bufinit()
{
	struct buf *bp;
	int i;
	caddr_t baddr;

	TAILQ_INIT(&bswlist);
	LIST_INIT(&invalhash);

	/* first, make a null hash table */
	for(i=0;i<BUFHSZ;i++)
		LIST_INIT(&bufhashtbl[i]);

	/* next, make a null set of free lists */
	for(i=0;i<BUFFER_QUEUES;i++)
		TAILQ_INIT(&bufqueues[i]);

	baddr = (caddr_t)kmem_alloc_pageable(buffer_map, MAXBSIZE * nbuf);
	/* finally, initialize each buffer header and stick on empty q */
	for(i=0;i<nbuf;i++) {
		bp = &buf[i];
		bzero(bp, sizeof *bp);
		bp->b_flags = B_INVAL;	/* we're just an empty header */
		bp->b_dev = NODEV;
		bp->b_vp = NULL;
		bp->b_rcred = NOCRED;
		bp->b_wcred = NOCRED;
		bp->b_qindex = QUEUE_EMPTY;
		bp->b_vnbufs.le_next = NOLIST;
		bp->b_data = baddr + i * MAXBSIZE;
		TAILQ_INSERT_TAIL(&bufqueues[QUEUE_EMPTY], bp, b_freelist);
		LIST_INSERT_HEAD(&invalhash, bp, b_hash);
	}
}

/*
 * remove the buffer from the appropriate free list
 */
void
bremfree(struct buf *bp)
{
	int s = splbio();
	if( bp->b_qindex != QUEUE_NONE) {
		TAILQ_REMOVE(&bufqueues[bp->b_qindex], bp, b_freelist);
		bp->b_qindex = QUEUE_NONE;
	} else {
		panic("bremfree: removing a buffer when not on a queue");
	}
	splx(s);
}

/*
 * Get a buffer with the specified data.  Look in the cache first.
 */
int
bread(struct vnode *vp, daddr_t blkno, int size, struct ucred *cred,
	struct buf **bpp)
{
	struct buf *bp;

	bp = getblk (vp, blkno, size, 0, 0);
	*bpp = bp;

	/* if not found in cache, do some I/O */
	if ((bp->b_flags & B_CACHE) == 0) {
		if (curproc && curproc->p_stats)	/* count block I/O */
			curproc->p_stats->p_ru.ru_inblock++;
		bp->b_flags |= B_READ;
		bp->b_flags &= ~(B_DONE|B_ERROR|B_INVAL);
		if( bp->b_rcred == NOCRED) {
			if (cred != NOCRED)
				crhold(cred);
			bp->b_rcred = cred;
		}
		VOP_STRATEGY(bp);
		return( biowait (bp));
	}
	
	return (0);
}

/*
 * Operates like bread, but also starts asynchronous I/O on
 * read-ahead blocks.
 */
int
breadn(struct vnode *vp, daddr_t blkno, int size,
	daddr_t *rablkno, int *rabsize,
	int cnt, struct ucred *cred, struct buf **bpp)
{
	struct buf *bp, *rabp;
	int i;
	int rv = 0, readwait = 0;

	*bpp = bp = getblk (vp, blkno, size, 0, 0);

	/* if not found in cache, do some I/O */
	if ((bp->b_flags & B_CACHE) == 0) {
		if (curproc && curproc->p_stats)	/* count block I/O */
			curproc->p_stats->p_ru.ru_inblock++;
		bp->b_flags |= B_READ;
		bp->b_flags &= ~(B_DONE|B_ERROR|B_INVAL);
		if( bp->b_rcred == NOCRED) {
			if (cred != NOCRED)
				crhold(cred);
			bp->b_rcred = cred;
		}
		VOP_STRATEGY(bp);
		++readwait;
	}

	for(i=0;i<cnt;i++, rablkno++, rabsize++) {
		if( incore(vp, *rablkno)) {
			continue;
		}
		rabp = getblk (vp, *rablkno, *rabsize, 0, 0);

		if ((rabp->b_flags & B_CACHE) == 0) {
			if (curproc && curproc->p_stats)
				curproc->p_stats->p_ru.ru_inblock++;
			rabp->b_flags |= B_READ | B_ASYNC;
			rabp->b_flags &= ~(B_DONE|B_ERROR|B_INVAL);
			if( rabp->b_rcred == NOCRED) {
				if (cred != NOCRED)
					crhold(cred);
				rabp->b_rcred = cred;
			}
			VOP_STRATEGY(rabp);
		} else {
			brelse(rabp);
		}
	}

	if( readwait) {
		rv = biowait (bp);
	}

	return (rv);
}

/*
 * Write, release buffer on completion.  (Done by iodone
 * if async.)
 */
int
bwrite(struct buf *bp)
{
	int oldflags = bp->b_flags;

	if(bp->b_flags & B_INVAL) {
		brelse(bp);
		return (0);
	} 

	if(!(bp->b_flags & B_BUSY))
		panic("bwrite: buffer is not busy???");

	bp->b_flags &= ~(B_READ|B_DONE|B_ERROR|B_DELWRI);
	bp->b_flags |= B_WRITEINPROG;

	if (oldflags & B_ASYNC) {
		if (oldflags & B_DELWRI) {
			reassignbuf(bp, bp->b_vp);
		} else if( curproc) {
			++curproc->p_stats->p_ru.ru_oublock;
		}
	}

	bp->b_vp->v_numoutput++;
	VOP_STRATEGY(bp);

	if( (oldflags & B_ASYNC) == 0) {
		int rtval = biowait(bp);
		if (oldflags & B_DELWRI) {
			reassignbuf(bp, bp->b_vp);
		} else if( curproc) {
			++curproc->p_stats->p_ru.ru_oublock;
		}
		brelse(bp);
		return (rtval);
	} 

	return(0);
}

int
vn_bwrite(ap)
	struct vop_bwrite_args *ap;
{
	return (bwrite(ap->a_bp));
}

/*
 * Delayed write. (Buffer is marked dirty).
 */
void
bdwrite(struct buf *bp)
{

	if((bp->b_flags & B_BUSY) == 0) {
		panic("bdwrite: buffer is not busy");
	}

	if(bp->b_flags & B_INVAL) {
		brelse(bp);
		return;
	}

	if(bp->b_flags & B_TAPE) {
		bawrite(bp);
		return;
	}
		
	bp->b_flags &= ~B_READ;
	if( (bp->b_flags & B_DELWRI) == 0) {
		if( curproc)
			++curproc->p_stats->p_ru.ru_oublock;
		bp->b_flags |= B_DONE|B_DELWRI;
		reassignbuf(bp, bp->b_vp);
	}
	brelse(bp);
	return;
}

/*
 * Asynchronous write.
 * Start output on a buffer, but do not wait for it to complete.
 * The buffer is released when the output completes.
 */
void
bawrite(struct buf *bp)
{
	bp->b_flags |= B_ASYNC;
	(void) VOP_BWRITE(bp);
}

/*
 * Release a buffer.
 */
void
brelse(struct buf *bp)
{
	int x;

	/* anyone need a "free" block? */
	x=splbio();
	if (needsbuffer) {
		needsbuffer = 0;
		wakeup((caddr_t)&needsbuffer);
	}

	/* anyone need this block? */
	if (bp->b_flags & B_WANTED) {
		bp->b_flags &= ~(B_WANTED|B_AGE);
		wakeup((caddr_t)bp);
	}

	if (bp->b_flags & B_LOCKED)
		bp->b_flags &= ~B_ERROR;

	if ((bp->b_flags & (B_NOCACHE|B_INVAL|B_ERROR)) ||
		(bp->b_bufsize <= 0)) {
		bp->b_flags |= B_INVAL;
		bp->b_flags &= ~(B_DELWRI|B_CACHE);
		if(bp->b_vp)
			brelvp(bp);
	}

	if( bp->b_qindex != QUEUE_NONE)
		panic("brelse: free buffer onto another queue???");

	/* enqueue */
	/* buffers with no memory */
	if(bp->b_bufsize == 0) {
		bp->b_qindex = QUEUE_EMPTY;
		TAILQ_INSERT_HEAD(&bufqueues[QUEUE_EMPTY], bp, b_freelist);
		LIST_REMOVE(bp, b_hash);
		LIST_INSERT_HEAD(&invalhash, bp, b_hash);
		bp->b_dev = NODEV;
	/* buffers with junk contents */
	} else if(bp->b_flags & (B_ERROR|B_INVAL|B_NOCACHE)) {
		bp->b_qindex = QUEUE_AGE;
		TAILQ_INSERT_HEAD(&bufqueues[QUEUE_AGE], bp, b_freelist);
		LIST_REMOVE(bp, b_hash);
		LIST_INSERT_HEAD(&invalhash, bp, b_hash);
		bp->b_dev = NODEV;
	/* buffers that are locked */
	} else if(bp->b_flags & B_LOCKED) {
		bp->b_qindex = QUEUE_LOCKED;
		TAILQ_INSERT_TAIL(&bufqueues[QUEUE_LOCKED], bp, b_freelist);
	/* buffers with stale but valid contents */
	} else if(bp->b_flags & B_AGE) {
		bp->b_qindex = QUEUE_AGE;
		TAILQ_INSERT_TAIL(&bufqueues[QUEUE_AGE], bp, b_freelist);
	/* buffers with valid and quite potentially reuseable contents */
	} else {
		bp->b_qindex = QUEUE_LRU;
		TAILQ_INSERT_TAIL(&bufqueues[QUEUE_LRU], bp, b_freelist);
	}

	/* unlock */
	bp->b_flags &= ~(B_WANTED|B_BUSY|B_ASYNC|B_NOCACHE|B_AGE);
	splx(x);
}

int freebufspace;
int allocbufspace;

/*
 * Find a buffer header which is available for use.
 */
struct buf *
getnewbuf(int slpflag, int slptimeo)
{
	struct buf *bp;
	int s;
	s = splbio();
start:
	/* can we constitute a new buffer? */
	if ((bp = bufqueues[QUEUE_EMPTY].tqh_first)) {
		if( bp->b_qindex != QUEUE_EMPTY)
			panic("getnewbuf: inconsistent EMPTY queue");
		bremfree(bp);
		goto fillbuf;
	}

	if ((bp = bufqueues[QUEUE_AGE].tqh_first)) {
		if( bp->b_qindex != QUEUE_AGE)
			panic("getnewbuf: inconsistent AGE queue");
		bremfree(bp);
	} else if ((bp = bufqueues[QUEUE_LRU].tqh_first)) {
		if( bp->b_qindex != QUEUE_LRU)
			panic("getnewbuf: inconsistent LRU queue");
		bremfree(bp);
	} else	{
		/* wait for a free buffer of any kind */
		needsbuffer = 1;
		tsleep((caddr_t)&needsbuffer, PRIBIO, "newbuf", 0);
		splx(s);
		return (0);
	}


	/* if we are a delayed write, convert to an async write */
	if (bp->b_flags & B_DELWRI) {
		bp->b_flags |= B_BUSY;
		bawrite (bp);
		goto start;
	}

	if(bp->b_vp)
		brelvp(bp);

	/* we are not free, nor do we contain interesting data */
	if (bp->b_rcred != NOCRED)
		crfree(bp->b_rcred);
	if (bp->b_wcred != NOCRED)
		crfree(bp->b_wcred);
fillbuf:
	bp->b_flags = B_BUSY;
	LIST_REMOVE(bp, b_hash);
	LIST_INSERT_HEAD(&invalhash, bp, b_hash);
	splx(s);
	bp->b_dev = NODEV;
	bp->b_vp = NULL;
	bp->b_blkno = bp->b_lblkno = 0;
	bp->b_iodone = 0;
	bp->b_error = 0;
	bp->b_resid = 0;
	bp->b_bcount = 0;
	bp->b_wcred = bp->b_rcred = NOCRED;
	bp->b_dirtyoff = bp->b_dirtyend = 0;
	bp->b_validoff = bp->b_validend = 0;
	return (bp);
}

/*
 * Check to see if a block is currently memory resident.
 */
struct buf *
incore(struct vnode *vp, daddr_t blkno)
{
	struct buf *bp;
	struct bufhashhdr *bh;

	int s = splbio();

	bh = BUFHASH(vp, blkno);
	bp = bh->lh_first;

	/* Search hash chain */
	while (bp) {
#ifdef DEBUG
		if( (bp < buf) || (bp >= buf + nbuf)) {
			printf("incore: buf out of range: %p, hash: %d\n",
				bp, bh - bufhashtbl); 
			panic("incore: buf fault");
		}
#endif
		/* hit */
		if (bp->b_lblkno == blkno && bp->b_vp == vp
			&& (bp->b_flags & B_INVAL) == 0) {
			splx(s);
			return (bp);
		}
		bp = bp->b_hash.le_next;
	}
	splx(s);

	return(0);
}

/*
 * Get a block given a specified block and offset into a file/device.
 */
struct buf *
getblk(struct vnode *vp, daddr_t blkno, int size, int slpflag, int slptimeo)
{
	struct buf *bp;
	int s;
	struct bufhashhdr *bh;

	s = splbio();
loop:
	if ((bp = incore(vp, blkno))) {
		if (bp->b_flags & B_BUSY) {
			bp->b_flags |= B_WANTED;
			tsleep ((caddr_t)bp, PRIBIO, "getblk", 0);
			goto loop;
		}
		bp->b_flags |= B_BUSY | B_CACHE;
		bremfree(bp);
		/*
		 * check for size inconsistancies
		 */
		if (bp->b_bcount != size) {
			printf("getblk: invalid buffer size: %ld\n", bp->b_bcount);
			bp->b_flags |= B_INVAL;
			VOP_BWRITE(bp);
			goto loop;
		}
	} else {
		if ((bp = getnewbuf(0, 0)) == 0)
			goto loop;
		bp->b_blkno = bp->b_lblkno = blkno;
		bgetvp(vp, bp);
		LIST_REMOVE(bp, b_hash);
		bh = BUFHASH(vp, blkno);
		LIST_INSERT_HEAD(bh, bp, b_hash);
		allocbuf(bp, size);
	}
	splx(s);
	return (bp);
}

/*
 * Get an empty, disassociated buffer of given size.
 */
struct buf *
geteblk(int size)
{
	struct buf *bp;
	while ((bp = getnewbuf(0, 0)) == 0)
		;
	allocbuf(bp, size);
	bp->b_flags |= B_INVAL;
	return (bp);
}

/*
 * Modify the length of a buffer's underlying buffer storage without
 * destroying information (unless, of course the buffer is shrinking).
 */
void
allocbuf(struct buf *bp, int size)
{

	int newbsize = round_page(size);

	if( newbsize == bp->b_bufsize) {
		bp->b_bcount = size;
		return;
	} else if( newbsize < bp->b_bufsize) {
		vm_hold_free_pages(
			(vm_offset_t) bp->b_data + newbsize,
			(vm_offset_t) bp->b_data + bp->b_bufsize);
	} else if( newbsize > bp->b_bufsize) {
		vm_hold_load_pages( 
			(vm_offset_t) bp->b_data + bp->b_bufsize,
			(vm_offset_t) bp->b_data + newbsize);
	}

	/* adjust buffer cache's idea of memory allocated to buffer contents */
	freebufspace -= newbsize - bp->b_bufsize;
	allocbufspace += newbsize - bp->b_bufsize;

	bp->b_bufsize = newbsize;
	bp->b_bcount = size;
}

/*
 * Wait for buffer I/O completion, returning error status.
 */
int
biowait(register struct buf *bp)
{
	int s;

	s = splbio();
	while ((bp->b_flags & B_DONE) == 0)
		tsleep((caddr_t)bp, PRIBIO, "biowait", 0);
	if((bp->b_flags & B_ERROR) || bp->b_error) {
		if ((bp->b_flags & B_INVAL) == 0) {
			bp->b_flags |= B_INVAL;
			bp->b_dev = NODEV;
			LIST_REMOVE(bp, b_hash);
			LIST_INSERT_HEAD(&invalhash, bp, b_hash);
		}
		if (!bp->b_error)
			bp->b_error = EIO;
		else
			bp->b_flags |= B_ERROR;
		splx(s);
		return (bp->b_error);
	} else {
		splx(s);
		return (0);
	}
}

/*
 * Finish I/O on a buffer, calling an optional function.
 * This is usually called from interrupt level, so process blocking
 * is not *a good idea*.
 */
void
biodone(register struct buf *bp)
{
	int s;
	s = splbio();
	bp->b_flags |= B_DONE;

	if ((bp->b_flags & B_READ) == 0)  {
		vwakeup(bp);
	}

#ifdef BOUNCE_BUFFERS
	if (bp->b_flags & B_BOUNCE)
		vm_bounce_free(bp);
#endif

	/* call optional completion function if requested */
	if (bp->b_flags & B_CALL) {
		bp->b_flags &= ~B_CALL;
		(*bp->b_iodone)(bp);
		splx(s);
		return;
	}

/*
 * For asynchronous completions, release the buffer now. The brelse
 *	checks for B_WANTED and will do the wakeup there if necessary -
 *	so no need to do a wakeup here in the async case.
 */

	if (bp->b_flags & B_ASYNC) {
		brelse(bp);
	} else {
		bp->b_flags &= ~B_WANTED;
		wakeup((caddr_t) bp);
	}
	splx(s);
}

int
count_lock_queue()
{
	int count;
	struct buf *bp;
	
	count = 0;
	for(bp = bufqueues[QUEUE_LOCKED].tqh_first;
	    bp != NULL;
	    bp = bp->b_freelist.tqe_next)
		count++;
	return(count);
}

int vfs_update_interval = 30;

void
vfs_update() {
	(void) spl0();
	while(1) {
		tsleep((caddr_t)&vfs_update_wakeup, PRIBIO, "update",
			hz * vfs_update_interval);
		vfs_update_wakeup = 0;
		sync(curproc, NULL, NULL);
	}
}

#if 0
#define MAXFREEBP 128
#define LDFREE_BUSY 1
#define LDFREE_WANT 2
int loadfreeing;
struct buf *freebp[MAXFREEBP];
#endif
/*
 * these routines are not in the correct place (yet)
 * also they work *ONLY* for kernel_pmap!!!
 */
void
vm_hold_load_pages(vm_offset_t froma, vm_offset_t toa) {
	vm_offset_t pg;
	vm_page_t p;
	vm_offset_t from = round_page(froma);
	vm_offset_t to = round_page(toa);

	for(pg = from ; pg < to ; pg += PAGE_SIZE) {

	tryagain:
#if 0
/*
 * don't allow buffer cache to cause VM paging
 */
		if ( cnt.v_free_count < cnt.v_free_min) {
			if( !loadfreeing ) {
				int n=0;
				struct buf *bp;
				loadfreeing = LDFREE_BUSY;
				while( (cnt.v_free_count <= cnt.v_free_min) && 
					(n < MAXFREEBP)) {
					bp = geteblk(0);
					if( bp)
						freebp[n++] = bp;
					else
						break;
				}
				while(--n >= 0) {
					brelse(freebp[n]);
				}
				if( loadfreeing & LDFREE_WANT)
					wakeup((caddr_t) &loadfreeing);
				loadfreeing = 0;
			} else {
				loadfreeing |= LDFREE_WANT;
				tsleep(&loadfreeing, PRIBIO, "biofree", 0);
			}
		}
#endif
		if ((curproc != pageproc) && (cnt.v_free_count <=
			cnt.v_free_reserved + (toa-froma) / PAGE_SIZE)) {
			VM_WAIT;
			goto tryagain;
		}

		p =  vm_page_alloc(kernel_object, pg - VM_MIN_KERNEL_ADDRESS);
		if( !p) {
			VM_WAIT;
			goto tryagain;
		}

		vm_page_wire(p);
		pmap_kenter( pg, VM_PAGE_TO_PHYS(p));
	}
}

void
vm_hold_free_pages(vm_offset_t froma, vm_offset_t toa) 
{
	vm_offset_t pg;
	vm_page_t p;
	vm_offset_t from = round_page(froma);
	vm_offset_t to = round_page(toa);
	
	for(pg = from ; pg < to ; pg += PAGE_SIZE) {
		p = PHYS_TO_VM_PAGE( pmap_kextract( pg));
		pmap_kremove( pg);
		vm_page_free(p);
	}
}

void
bufstats()
{
}

