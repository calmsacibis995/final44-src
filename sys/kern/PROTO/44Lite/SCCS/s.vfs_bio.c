h37641
s 00195/00122/00118
d D 8.1 94/01/21 18:46:18 mckusick 2 1
c update for 4.4BSD-Lite
e
s 00240/00000/00000
d D 1.1 91/05/11 15:31:10 mckusick 1 0
c date and time created 91/05/11 15:31:10 by mckusick
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 2
I 2
/*-
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 2
 *
 * %sccs.include.redist.c%
 *
D 2
 *	from: @(#)vfs_bio.c	7.40 (Berkeley) 5/8/91
E 2
I 2
 *	from: @(#)vfs_bio.c	8.6 (Berkeley) 1/11/94
E 2
 */

D 2
#include "param.h"
#include "proc.h"
#include "buf.h"
#include "vnode.h"
#include "specdev.h"
#include "mount.h"
#include "trace.h"
#include "resourcevar.h"
E 2
I 2
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/trace.h>
#include <sys/malloc.h>
#include <sys/resourcevar.h>
E 2

/*
D 2
 * Initialize buffers and hash links for buffers.
E 2
I 2
 * Definitions for the buffer hash lists.
E 2
 */
D 2
bufinit()
E 2
I 2
#define	BUFHASH(dvp, lbn)	\
	(&bufhashtbl[((int)(dvp) / sizeof(*(dvp)) + (int)(lbn)) & bufhash])
LIST_HEAD(bufhashhdr, buf) *bufhashtbl, invalhash;
u_long	bufhash;

/*
 * Insq/Remq for the buffer hash lists.
 */
#define	binshash(bp, dp)	LIST_INSERT_HEAD(dp, bp, b_hash)
#define	bremhash(bp)		LIST_REMOVE(bp, b_hash)

/*
 * Definitions for the buffer free lists.
 */
#define	BQUEUES		4		/* number of free buffer queues */

#define	BQ_LOCKED	0		/* super-blocks &c */
#define	BQ_LRU		1		/* lru, useful buffers */
#define	BQ_AGE		2		/* rubbish */
#define	BQ_EMPTY	3		/* buffer headers with no memory */

TAILQ_HEAD(bqueues, buf) bufqueues[BQUEUES];
int needbuffer;

/*
 * Insq/Remq for the buffer free lists.
 */
#define	binsheadfree(bp, dp)	TAILQ_INSERT_HEAD(dp, bp, b_freelist)
#define	binstailfree(bp, dp)	TAILQ_INSERT_TAIL(dp, bp, b_freelist)

void
bremfree(bp)
	struct buf *bp;
E 2
{
I 2
	struct bqueues *dp = NULL;
E 2

	/*
D 2
	 * Body deleted.
E 2
I 2
	 * We only calculate the head of the freelist when removing
	 * the last element of the list as that is the only time that
	 * it is needed (e.g. to reset the tail pointer).
	 *
	 * NB: This makes an assumption about how tailq's are implemented.
E 2
	 */
D 2
	return;
E 2
I 2
	if (bp->b_freelist.tqe_next == NULL) {
		for (dp = bufqueues; dp < &bufqueues[BQUEUES]; dp++)
			if (dp->tqh_last == &bp->b_freelist.tqe_next)
				break;
		if (dp == &bufqueues[BQUEUES])
			panic("bremfree: lost tail");
	}
	TAILQ_REMOVE(dp, bp, b_freelist);
E 2
}

/*
D 2
 * Find the block in the buffer pool.
 * If the buffer is not present, allocate a new buffer and load
 * its contents according to the filesystem fill routine.
E 2
I 2
 * Initialize buffers and hash links for buffers.
E 2
 */
D 2
bread(vp, blkno, size, cred, bpp)
	struct vnode *vp;
	daddr_t blkno;
	int size;
	struct ucred *cred;
	struct buf **bpp;
E 2
I 2
void
bufinit()
E 2
{
I 2
	register struct buf *bp;
	struct bqueues *dp;
	register int i;
	int base, residual;
E 2

I 2
	for (dp = bufqueues; dp < &bufqueues[BQUEUES]; dp++)
		TAILQ_INIT(dp);
	bufhashtbl = hashinit(nbuf, M_CACHE, &bufhash);
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
	for (i = 0; i < nbuf; i++) {
		bp = &buf[i];
		bzero((char *)bp, sizeof *bp);
		bp->b_dev = NODEV;
		bp->b_rcred = NOCRED;
		bp->b_wcred = NOCRED;
		bp->b_vnbufs.le_next = NOLIST;
		bp->b_data = buffers + i * MAXBSIZE;
		if (i < residual)
			bp->b_bufsize = (base + 1) * CLBYTES;
		else
			bp->b_bufsize = base * CLBYTES;
		bp->b_flags = B_INVAL;
		dp = bp->b_bufsize ? &bufqueues[BQ_AGE] : &bufqueues[BQ_EMPTY];
		binsheadfree(bp, dp);
		binshash(bp, &invalhash);
	}
}

bread(a1, a2, a3, a4, a5)
	struct vnode *a1;
	daddr_t a2;
	int a3;
	struct ucred *a4;
	struct buf **a5;
{

E 2
	/*
	 * Body deleted.
	 */
	return (EIO);
}

D 2
/*
 * Operates like bread, but also starts I/O on the specified
 * read-ahead block.
 */
breada(vp, blkno, size, rablkno, rabsize, cred, bpp)
	struct vnode *vp;
	daddr_t blkno; int size;
	daddr_t rablkno; int rabsize;
	struct ucred *cred;
	struct buf **bpp;
E 2
I 2
breadn(a1, a2, a3, a4, a5, a6, a7, a8)
	struct vnode *a1;
	daddr_t a2; int a3;
	daddr_t a4[]; int a5[];
	int a6;
	struct ucred *a7;
	struct buf **a8;
E 2
{

	/*
	 * Body deleted.
	 */
	return (EIO);
}

D 2
/*
 * Synchronous write.
 * Release buffer on completion.
 */
bwrite(bp)
	register struct buf *bp;
E 2
I 2
bwrite(a1)
	struct buf *a1;
E 2
{

	/*
	 * Body deleted.
	 */
	return (EIO);
}

D 2
/*
 * Delayed write.
 *
 * The buffer is marked dirty, but is not queued for I/O.
 * This routine should be used when the buffer is expected
 * to be modified again soon, typically a small write that
 * partially fills a buffer.
 *
 * NB: magnetic tapes cannot be delayed; they must be
 * written in the order that the writes are requested.
 */
bdwrite(bp)
	register struct buf *bp;
E 2
I 2
int
vn_bwrite(ap)
	struct vop_bwrite_args *ap;
E 2
{
I 2
	return (bwrite(ap->a_bp));
}
E 2

I 2
bdwrite(a1)
	struct buf *a1;
{

E 2
	/*
	 * Body deleted.
	 */
	return;
}

D 2
/*
 * Asynchronous write.
 * Start I/O on a buffer, but do not wait for it to complete.
 * The buffer is released when the I/O completes.
 */
bawrite(bp)
	register struct buf *bp;
E 2
I 2
bawrite(a1)
	struct buf *a1;
E 2
{

	/*
	 * Body deleted.
	 */
	return;
}

D 2
/*
 * Release a buffer.
 * Even if the buffer is dirty, no I/O is started.
 */
brelse(bp)
	register struct buf *bp;
E 2
I 2
brelse(a1)
	struct buf *a1;
E 2
{

	/*
	 * Body deleted.
	 */
	return;
}

D 2
/*
 * Check to see if a block is currently memory resident.
 */
incore(vp, blkno)
	struct vnode *vp;
	daddr_t blkno;
E 2
I 2
struct buf *
incore(a1, a2)
	struct vnode *a1;
	daddr_t a2;
E 2
{

	/*
	 * Body deleted.
	 */
	return (0);
}

D 2
/*
 * Check to see if a block is currently memory resident.
 * If it is resident, return it. If it is not resident,
 * allocate a new buffer and assign it to the block.
 */
E 2
struct buf *
D 2
getblk(vp, blkno, size)
	register struct vnode *vp;
	daddr_t blkno;
	int size;
E 2
I 2
getblk(a1, a2, a3, a4, a5)
	struct vnode *a1;
	daddr_t a2;
	int a3, a4, a5;
E 2
{

	/*
	 * Body deleted.
	 */
D 2
	return (0);
E 2
I 2
	return ((struct buf *)0);
E 2
}

D 2
/*
 * Allocate a buffer.
 * The caller will assign it to a block.
 */
E 2
struct buf *
D 2
geteblk(size)
	int size;
E 2
I 2
geteblk(a1)
	int a1;
E 2
{

	/*
	 * Body deleted.
	 */
D 2
	return (0);
E 2
I 2
	return ((struct buf *)0);
E 2
}

D 2
/*
 * Expand or contract the actual memory allocated to a buffer.
 * If no memory is available, release buffer and take error exit.
 */
allocbuf(tp, size)
	register struct buf *tp;
	int size;
E 2
I 2
allocbuf(a1, a2)
	struct buf *a1;
	int a2;
E 2
{

	/*
	 * Body deleted.
	 */
	return (0);
}

D 2
/*
 * Find a buffer which is available for use.
 * Select something from a free list.
 * Preference is to AGE list, then LRU list.
 */
E 2
struct buf *
D 2
getnewbuf()
E 2
I 2
getnewbuf(a1, a2)
	int a1, a2;
E 2
{

	/*
	 * Body deleted.
	 */
D 2
	return (0);
E 2
I 2
	return ((struct buf *)0);
E 2
}

D 2
/*
 * Wait for I/O to complete.
 *
 * Extract and return any errors associated with the I/O.
 * If the error flag is set, but no specific error is
 * given, return EIO.
 */
biowait(bp)
	register struct buf *bp;
E 2
I 2
biowait(a1)
	struct buf *a1;
E 2
{

	/*
	 * Body deleted.
	 */
	return (EIO);
}

D 2
/*
 * Mark I/O complete on a buffer.
 *
 * If a callback has been requested, e.g. the pageout
 * daemon, do so. Otherwise, awaken waiting processes.
 */
biodone(bp)
	register struct buf *bp;
E 2
I 2
void
biodone(a1)
	struct buf *a1;
E 2
{

	/*
	 * Body deleted.
	 */
D 2
	 return;
E 2
I 2
	return;
E 2
}
I 2

int
count_lock_queue()
{

	/*
	 * Body deleted.
	 */
	return (0);
}

#ifdef DIAGNOSTIC
/*
 * Print out statistics on the current allocation of the buffer pool.
 * Can be enabled to print out on every ``sync'' by setting "syncprt"
 * in vfs_syscalls.c using sysctl.
 */
void
vfs_bufstats()
{
	int s, i, j, count;
	register struct buf *bp;
	register struct bqueues *dp;
	int counts[MAXBSIZE/CLBYTES+1];
	static char *bname[BQUEUES] = { "LOCKED", "LRU", "AGE", "EMPTY" };

	for (dp = bufqueues, i = 0; dp < &bufqueues[BQUEUES]; dp++, i++) {
		count = 0;
		for (j = 0; j <= MAXBSIZE/CLBYTES; j++)
			counts[j] = 0;
		s = splbio();
		for (bp = dp->tqh_first; bp; bp = bp->b_freelist.tqe_next) {
			counts[bp->b_bufsize/CLBYTES]++;
			count++;
		}
		splx(s);
		printf("%s: total-%d", bname[i], count);
		for (j = 0; j <= MAXBSIZE/CLBYTES; j++)
			if (counts[j] != 0)
				printf(", %d-%d", j * CLBYTES, counts[j]);
		printf("\n");
	}
}
#endif /* DIAGNOSTIC */
E 2
E 1
