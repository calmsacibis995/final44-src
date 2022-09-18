h51757
s 00005/00002/00316
d D 8.2 94/02/21 17:43:41 bostic 14 13
c cast alloc's to shut SunOS up
e
s 00002/00002/00316
d D 8.1 93/06/04 15:21:58 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00317
d D 5.12 93/02/11 11:39:49 bostic 12 11
c move db.h to the end of the includes, make compat.h work better
e
s 00021/00013/00297
d D 5.11 93/01/17 16:20:22 bostic 11 10
c can't have a global "hashp", pass it around as an argument
c change default_hash to __default_hash for the same reason
e
s 00002/00001/00308
d D 5.10 92/09/29 13:22:42 margo 10 9
c Do not allow the number of buffers to go negative.
e
s 00002/00002/00307
d D 5.9 91/09/08 12:30:27 bostic 9 8
c lint
e
s 00235/00246/00074
d D 5.8 91/09/04 12:56:28 bostic 8 7
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00002/00002/00318
d D 5.7 91/03/12 09:34:05 bostic 7 6
c Make all bucket and overflow addresses unsigned
e
s 00001/00001/00319
d D 5.6 91/02/24 16:44:24 bostic 6 5
c There was a reason they included <sys/param.h>  (MIN, MAX)
e
s 00003/00003/00317
d D 5.5 91/02/22 17:23:35 bostic 5 4
c ANSI prototypes
e
s 00007/00002/00313
d D 5.4 91/02/21 19:00:54 bostic 4 3
c make sure oaddr doesn't get set on empty pages
e
s 00005/00003/00310
d D 5.3 91/02/21 18:54:02 bostic 3 2
c make sure free'd overflow pages are not reread from disk and handle
c back-to-back big key pairs during split
e
s 00056/00046/00257
d D 5.2 91/02/19 10:29:27 bostic 2 1
c add "pinning" to the buffer pool
e
s 00303/00000/00000
d D 5.1 91/02/12 20:27:56 bostic 1 0
c date and time created 91/02/12 20:27:56 by bostic
e
u
U
t
T
I 1
/*-
D 13
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 8
/******************************************************************************
E 8
I 8
/*
 * PACKAGE: hash
 *
 * DESCRIPTION:
 *	Contains buffer management
 *
 * ROUTINES:
 * External
 *	__buf_init
 *	__get_buf
 *	__buf_free
 *	__reclaim_buf
 * Internal
 *	newbuf
 */
E 8

D 8
PACKAGE: hash

DESCRIPTION: 
	Contains buffer management

ROUTINES: 
    External
	__buf_init
	__get_buf
	__buf_free
	__reclaim_buf
    Internal
	newbuf

******************************************************************************/
E 8
D 5
#include <sys/param.h>
#include <sys/file.h>
E 5
I 5
D 6
#include <sys/types.h>
E 6
I 6
#include <sys/param.h>
I 11

E 11
E 6
E 5
D 8
#include <assert.h>
E 8
I 8
D 12
#include <db.h>
E 12
E 8
#include <errno.h>
D 5
#include "hash.h"
E 5
#include <stdio.h>
I 5
#include <stdlib.h>
I 8
#ifdef DEBUG
#include <assert.h>
#endif
I 11

I 12
#include <db.h>
E 12
E 11
E 8
#include "hash.h"
I 8
#include "page.h"
#include "extern.h"
E 8
E 5

D 8
/* Externals */
extern HTAB	*hashp;
E 8
I 8
D 11
static BUFHEAD *newbuf __P((u_int, BUFHEAD *));
E 11
I 11
static BUFHEAD *newbuf __P((HTAB *, u_int, BUFHEAD *));
E 11
E 8

D 8
/* My internals */
static BUFHEAD *newbuf();

E 8
/* Unlink B from its place in the lru */
D 8
#define BUF_REMOVE(B)			\
{					\
    B->prev->next = B->next;		\
    B->next->prev = B->prev;		\
E 8
I 8
#define BUF_REMOVE(B) { \
	(B)->prev->next = (B)->next; \
	(B)->next->prev = (B)->prev; \
E 8
}

/* Insert B after P */
D 8
#define BUF_INSERT(B,P)			\
{					\
    B->next = P->next;			\
    B->prev = P;			\
    P->next = B;			\
    B->next->prev = B;			\
E 8
I 8
#define BUF_INSERT(B, P) { \
	(B)->next = (P)->next; \
	(B)->prev = (P); \
	(P)->next = (B); \
	(B)->next->prev = (B); \
E 8
}

#define	MRU	hashp->bufhead.next
#define	LRU	hashp->bufhead.prev

D 8
#define MRU_INSERT(B)	BUF_INSERT(B,(&hashp->bufhead))
#define LRU_INSERT(B)	BUF_INSERT(B,LRU)
E 8
I 8
#define MRU_INSERT(B)	BUF_INSERT((B), &hashp->bufhead)
#define LRU_INSERT(B)	BUF_INSERT((B), LRU)
E 8

/*
D 8
    We are looking for a buffer with address "addr".
    If prev_bp is NULL, then address is a bucket index.
    If prev_bp is not NULL, then it points to the page previous
	to an overflow page that we are trying to find.

    CAVEAT:  The buffer header accessed via prev_bp's ovfl field
    may no longer be valid.  Therefore, you must always verify that
    its address matches the address you are seeking.
*/
E 8
I 8
 * We are looking for a buffer with address "addr".  If prev_bp is NULL, then
 * address is a bucket index.  If prev_bp is not NULL, then it points to the
 * page previous to an overflow page that we are trying to find.
 *
 * CAVEAT:  The buffer header accessed via prev_bp's ovfl field may no longer
 * be valid.  Therefore, you must always verify that its address matches the
 * address you are seeking.
 */
E 8
extern BUFHEAD *
D 8
__get_buf ( addr, prev_bp, newpage )
D 7
int	addr;
E 7
I 7
u_int	addr;
E 7
BUFHEAD	*prev_bp;
int	newpage;		/* If prev_bp is set, indicates that this is
					a new overflow page */
E 8
I 8
D 11
__get_buf(addr, prev_bp, newpage)
E 11
I 11
__get_buf(hashp, addr, prev_bp, newpage)
	HTAB *hashp;
E 11
	u_int addr;
	BUFHEAD *prev_bp;
	int newpage;	/* If prev_bp set, indicates a new overflow page. */
E 8
{
D 8
    register int	segment_ndx;
    register	BUFHEAD	*bp;
    register	unsigned	is_disk = 0;
I 3
    register	unsigned	is_disk_mask = 0;
E 3
    SEGMENT	segp;
E 8
I 8
	register BUFHEAD *bp;
D 9
	register u_int is_disk, is_disk_mask;
	register int segment_ndx;
E 9
I 9
	register u_int is_disk_mask;
	register int is_disk, segment_ndx;
E 9
	SEGMENT segp;
E 8

D 8
    if ( prev_bp ) {
	bp = prev_bp->ovfl;
	if ( !bp || (bp->addr != addr) ) bp = NULL;
	if ( !newpage ) is_disk = BUF_DISK;
    }
    else {
	/* Grab buffer out of directory */
	segment_ndx = addr & ( hashp->SGSIZE - 1 );
E 8
I 8
	is_disk = 0;
	is_disk_mask = 0;
	if (prev_bp) {
		bp = prev_bp->ovfl;
		if (!bp || (bp->addr != addr))
			bp = NULL;
		if (!newpage)
			is_disk = BUF_DISK;
	} else {
		/* Grab buffer out of directory */
		segment_ndx = addr & (hashp->SGSIZE - 1);
E 8

D 8
	/*
	 * valid segment ensured by __call_hash()
	 */
	segp = hashp->dir[addr >> hashp->SSHIFT];
E 8
I 8
		/* valid segment ensured by __call_hash() */
		segp = hashp->dir[addr >> hashp->SSHIFT];
E 8
#ifdef DEBUG
D 8
	assert(segp != NULL);
E 8
I 8
		assert(segp != NULL);
E 8
#endif
D 8
	bp = PTROF(segp[segment_ndx]);
D 3
	is_disk = ISDISK(segp[segment_ndx]);
E 3
I 3
	is_disk_mask = ISDISK(segp[segment_ndx]); 
	is_disk = is_disk_mask || !hashp->new_file; 
E 3
    } 
E 8
I 8
		bp = PTROF(segp[segment_ndx]);
		is_disk_mask = ISDISK(segp[segment_ndx]);
		is_disk = is_disk_mask || !hashp->new_file;
	}
E 8

D 8
    if ( !bp ) {
	bp = newbuf ( addr, prev_bp );
D 3
	if ( !bp || __get_page ( bp->page, addr, !prev_bp, (int)is_disk, 0 )) {
E 3
I 3
	if ( !bp || __get_page ( bp->page, addr, !prev_bp, is_disk, 0 )) {
E 3
	    return(NULL);
E 8
I 8
	if (!bp) {
D 11
		bp = newbuf(addr, prev_bp);
		if (!bp || __get_page(bp->page, addr, !prev_bp, is_disk, 0))
E 11
I 11
		bp = newbuf(hashp, addr, prev_bp);
		if (!bp ||
		    __get_page(hashp, bp->page, addr, !prev_bp, is_disk, 0))
E 11
			return (NULL);
		if (!prev_bp)
			segp[segment_ndx] =
			    (BUFHEAD *)((u_int)bp | is_disk_mask);
	} else {
		BUF_REMOVE(bp);
		MRU_INSERT(bp);
E 8
	}
D 8
	if ( !prev_bp ) {
D 3
	    segp[segment_ndx] = (BUFHEAD *)((unsigned)bp | is_disk);
E 3
I 3
	    segp[segment_ndx] = (BUFHEAD *)((unsigned)bp | is_disk_mask );
E 3
	}
    } else {
	BUF_REMOVE ( bp );
	MRU_INSERT ( bp );
    }
    return(bp);
E 8
I 8
	return (bp);
E 8
}

/*
D 8
    We need a buffer for this page. Either allocate one, or
    evict a resident one (if we have as many buffers as we're
    allowed) and put this one in.

    If newbuf finds an error (returning NULL), it also sets errno
*/
E 8
I 8
 * We need a buffer for this page. Either allocate one, or evict a resident
 * one (if we have as many buffers as we're allowed) and put this one in.
 *
 * If newbuf finds an error (returning NULL), it also sets errno.
 */
E 8
static BUFHEAD *
D 8
newbuf ( addr, prev_bp )
D 7
int	addr;
E 7
I 7
u_int	addr;
E 7
BUFHEAD	*prev_bp;
E 8
I 8
D 11
newbuf(addr, prev_bp)
	u_int   addr;
E 11
I 11
newbuf(hashp, addr, prev_bp)
	HTAB *hashp;
	u_int addr;
E 11
	BUFHEAD *prev_bp;
E 8
{
D 8
    register	BUFHEAD	*bp;	/* The buffer we're going to use */
    register	BUFHEAD	*xbp;	/* Temp pointer */
    register	BUFHEAD *next_xbp;
    int	segment_ndx;
    u_short	*shortp;
    u_short	oaddr;
    SEGMENT	segp;
E 8
I 8
	register BUFHEAD *bp;		/* The buffer we're going to use */
	register BUFHEAD *xbp;		/* Temp pointer */
	register BUFHEAD *next_xbp;
	SEGMENT segp;
	int segment_ndx;
	u_short oaddr, *shortp;
E 8

I 4
D 8
    oaddr = 0;
E 4
D 2
    if ( hashp->nbufs ) {
E 2
I 2
    bp = LRU;
    /* 
	If LRU buffer is pinned, the buffer pool is too small.
	We need to allocate more buffers
    */
    if ( hashp->nbufs || (bp->flags & BUF_PIN) ) {
E 2
	/* Allocate a new one */
	bp = (BUFHEAD *)malloc ( sizeof (struct _bufhead) );
	if ( !bp || !(bp->page = (char *)malloc ( hashp->BSIZE )) ) {
	    return (NULL);
	}
	hashp->nbufs--;
    } else {
	/* Kick someone out */
D 2
	bp = LRU;
E 2
	BUF_REMOVE( bp );
	/* 
D 2
	    Set oaddr before __put_page so that you get it 
	    before bytes are swapped
E 2
I 2
	    If this is an overflow page with addr 0, it's already
	    been flushed back in an overflow chain and initialized
E 2
	*/
D 2
	shortp = (u_short *)bp->page;
	oaddr = shortp[shortp[0]-1];
	if ( (bp->flags & BUF_MOD) && 
	     __put_page(bp->page, bp->addr, (int)IS_BUCKET(bp->flags), 0) ) {
	    return(NULL);
	}
	/* 
	    Update the pointer to this page (i.e. invalidate it).
E 2
I 2
	if ( (bp->addr != 0) || (bp->flags & BUF_BUCKET) ) {
	    /* 
		Set oaddr before __put_page so that you get it 
		before bytes are swapped
	    */
	    shortp = (u_short *)bp->page;
D 4
	    oaddr = shortp[shortp[0]-1];
E 4
I 4
	    if ( shortp[0] ) {
		oaddr = shortp[shortp[0]-1];
	    }
E 4
	    if ( (bp->flags & BUF_MOD) && 
		 __put_page(bp->page, bp->addr, (int)IS_BUCKET(bp->flags), 0) ) {
		return(NULL);
	    }
	    /* 
		Update the pointer to this page (i.e. invalidate it).
E 8
I 8
	oaddr = 0;
	bp = LRU;
	/*
	 * If LRU buffer is pinned, the buffer pool is too small. We need to
	 * allocate more buffers.
	 */
	if (hashp->nbufs || (bp->flags & BUF_PIN)) {
		/* Allocate a new one */
D 14
		bp = malloc(sizeof(struct _bufhead));
		if (!bp || !(bp->page = malloc(hashp->BSIZE)))
E 14
I 14
		if ((bp = (BUFHEAD *)malloc(sizeof(BUFHEAD))) == NULL)
E 14
			return (NULL);
I 14
		if ((bp->page = (char *)malloc(hashp->BSIZE)) == NULL) {
			free(bp);
			return (NULL);
		}
E 14
D 10
		hashp->nbufs--;
E 10
I 10
		if (hashp->nbufs)
			hashp->nbufs--;
E 10
	} else {
		/* Kick someone out */
		BUF_REMOVE(bp);
		/*
		 * If this is an overflow page with addr 0, it's already been
		 * flushed back in an overflow chain and initialized.
		 */
		if ((bp->addr != 0) || (bp->flags & BUF_BUCKET)) {
			/*
			 * Set oaddr before __put_page so that you get it
			 * before bytes are swapped.
			 */
			shortp = (u_short *)bp->page;
			if (shortp[0])
				oaddr = shortp[shortp[0] - 1];
D 11
			if ((bp->flags & BUF_MOD) && __put_page(bp->page,
E 11
I 11
			if ((bp->flags & BUF_MOD) && __put_page(hashp, bp->page,
E 11
			    bp->addr, (int)IS_BUCKET(bp->flags), 0))
				return (NULL);
			/*
			 * Update the pointer to this page (i.e. invalidate it).
			 *
			 * If this is a new file (i.e. we created it at open
			 * time), make sure that we mark pages which have been
			 * written to disk so we retrieve them from disk later,
			 * rather than allocating new pages.
			 */
			if (IS_BUCKET(bp->flags)) {
				segment_ndx = bp->addr & (hashp->SGSIZE - 1);
				segp = hashp->dir[bp->addr >> hashp->SSHIFT];
#ifdef DEBUG
				assert(segp != NULL);
#endif
E 8
E 2

D 2
	    If this is a new file (i.e. we created it at open time), 
	    make sure that we mark pages which have been written to 
	    disk so we retrieve them from disk later, rather than
	    allocating new pages.
	*/
E 2
I 2
D 8
		If this is a new file (i.e. we created it at open time), 
		make sure that we mark pages which have been written to 
		disk so we retrieve them from disk later, rather than
		allocating new pages.
	    */
E 8
I 8
				if (hashp->new_file &&
				    ((bp->flags & BUF_MOD) ||
				    ISDISK(segp[segment_ndx])))
					segp[segment_ndx] = (BUFHEAD *)BUF_DISK;
				else
					segp[segment_ndx] = NULL;
			}
			/*
			 * Since overflow pages can only be access by means of
			 * their bucket, free overflow pages associated with
			 * this bucket.
			 */
			for (xbp = bp; xbp->ovfl;) {
				next_xbp = xbp->ovfl;
				xbp->ovfl = 0;
				xbp = next_xbp;
E 8
E 2

D 2
	if ( IS_BUCKET(bp->flags)) {
	    segment_ndx = bp->addr & ( hashp->SGSIZE - 1 );
E 2
I 2
D 8
	    if ( IS_BUCKET(bp->flags)) {
		segment_ndx = bp->addr & ( hashp->SGSIZE - 1 );
E 8
I 8
				/* Check that ovfl pointer is up date. */
				if (IS_BUCKET(xbp->flags) ||
				    (oaddr != xbp->addr))
					break;
E 8
E 2

D 2
	    segp = hashp->dir[bp->addr >> hashp->SSHIFT];
E 2
I 2
D 8
		segp = hashp->dir[bp->addr >> hashp->SSHIFT];
E 2

D 2
	    assert(segp != NULL);
E 2
I 2
		assert(segp != NULL);
E 2

D 2
	    if ( hashp->new_file && 
		 ((bp->flags & BUF_MOD) || ISDISK(segp[segment_ndx])) ) {
		segp[segment_ndx] = (BUFHEAD *)BUF_DISK;
	    } else segp[segment_ndx] = NULL;
	}
E 2
I 2
		if ( hashp->new_file && 
		     ((bp->flags & BUF_MOD) || ISDISK(segp[segment_ndx])) ) {
		    segp[segment_ndx] = (BUFHEAD *)BUF_DISK;
		} else segp[segment_ndx] = NULL;
	    }
E 2

D 2
	/*
	    Since overflow pages can only be access by means of
	    their bucket, free overflow pages associated with this
	    bucket.
	*/
	for ( xbp = bp; xbp->ovfl; ) {
E 2
I 2
	    /*
		Since overflow pages can only be access by means of
		their bucket, free overflow pages associated with this
		bucket.
	    */
	    for ( xbp = bp; xbp->ovfl; ) {
E 2

D 2
	    next_xbp = xbp->ovfl;
	    xbp->ovfl = 0;
	    xbp = next_xbp;
E 2
I 2
		next_xbp = xbp->ovfl;
		xbp->ovfl = 0;
		xbp = next_xbp;
E 2

D 2
	    /* Check that ovfl pointer is up date */
	    if ( IS_BUCKET(xbp->flags) || (oaddr != xbp->addr) ) break;
E 2
I 2
		/* Check that ovfl pointer is up date */
		if ( IS_BUCKET(xbp->flags) || (oaddr != xbp->addr) ) break;
E 2

D 2
	    shortp = (u_short *)xbp->page;
	    oaddr = shortp[shortp[0]-1];	/* set before __put_page */
	    if ( (xbp->flags & BUF_MOD) &&
		__put_page ( xbp->page, xbp->addr, 0, 0 ) ) {
		return(NULL);
E 2
I 2
		shortp = (u_short *)xbp->page;
D 4
		oaddr = shortp[shortp[0]-1];	/* set before __put_page */
E 4
I 4
		if ( shortp[0] ) {
		    oaddr = shortp[shortp[0]-1];  /* set before __put_page */
E 8
I 8
				shortp = (u_short *)xbp->page;
				if (shortp[0])
					/* set before __put_page */
					oaddr = shortp[shortp[0] - 1];
D 11
				if ((xbp->flags & BUF_MOD) &&
				    __put_page(xbp->page, xbp->addr, 0, 0))
E 11
I 11
				if ((xbp->flags & BUF_MOD) && __put_page(hashp,
				    xbp->page, xbp->addr, 0, 0))
E 11
					return (NULL);
				xbp->addr = 0;
				xbp->flags = 0;
				BUF_REMOVE(xbp);
				LRU_INSERT(xbp);
			}
E 8
		}
E 4
D 8
		if ( (xbp->flags & BUF_MOD) &&
		    __put_page ( xbp->page, xbp->addr, 0, 0 ) ) {
		    return(NULL);
		}
		xbp->addr = 0;
		xbp->flags = 0;
		BUF_REMOVE ( xbp );
		LRU_INSERT ( xbp );
E 2
	    }
E 8
D 2
	    xbp->addr = 0;
	    xbp->flags = 0;
	    BUF_REMOVE ( xbp );
	    LRU_INSERT ( xbp );
E 2
	}
D 8
    }
E 8

D 8
    /* Now assign this buffer */
    bp->addr = addr;
E 8
I 8
	/* Now assign this buffer */
	bp->addr = addr;
E 8
#ifdef DEBUG1
D 8
    fprintf ( stderr, "NEWBUF1: %d->ovfl was %d is now %d\n", bp->addr,
		(bp->ovfl?bp->ovfl->addr:0),  0);
E 8
I 8
	(void)fprintf(stderr, "NEWBUF1: %d->ovfl was %d is now %d\n",
	    bp->addr, (bp->ovfl ? bp->ovfl->addr : 0), 0);
E 8
#endif
D 8
    bp->ovfl = NULL;
    if ( prev_bp ) {
	/* 
	    If prev_bp is set, this is an overflow page, hook it in to the
	    buffer overflow links
	*/
E 8
I 8
	bp->ovfl = NULL;
	if (prev_bp) {
		/*
		 * If prev_bp is set, this is an overflow page, hook it in to
		 * the buffer overflow links.
		 */
E 8
#ifdef DEBUG1
D 8
	fprintf ( stderr, "NEWBUF2: %d->ovfl was %d is now %d\n", prev_bp->addr,
		    (prev_bp->ovfl?bp->ovfl->addr:0),  
		    (bp?bp->addr: 0));
E 8
I 8
		(void)fprintf(stderr, "NEWBUF2: %d->ovfl was %d is now %d\n",
		    prev_bp->addr, (prev_bp->ovfl ? bp->ovfl->addr : 0),
		    (bp ? bp->addr : 0));
E 8
#endif
D 8
	prev_bp->ovfl = bp;
	bp->flags = 0;
    } else bp->flags = BUF_BUCKET;
    MRU_INSERT ( bp );
    return ( bp );
E 8
I 8
		prev_bp->ovfl = bp;
		bp->flags = 0;
	} else
		bp->flags = BUF_BUCKET;
	MRU_INSERT(bp);
	return (bp);
E 8
}

extern void
D 8
__buf_init ( nbytes )
int	nbytes;
E 8
I 8
D 11
__buf_init(nbytes)
E 11
I 11
__buf_init(hashp, nbytes)
	HTAB *hashp;
E 11
	int nbytes;
E 8
{
D 8
    int	npages;
    BUFHEAD	*bfp = &(hashp->bufhead);
E 8
I 8
	BUFHEAD *bfp;
	int npages;
E 8

D 8
    npages = (nbytes + hashp->BSIZE - 1) >> hashp->BSHIFT;
    npages = MAX ( npages, MIN_BUFFERS );
E 8
I 8
	bfp = &(hashp->bufhead);
	npages = (nbytes + hashp->BSIZE - 1) >> hashp->BSHIFT;
	npages = MAX(npages, MIN_BUFFERS);
E 8

D 8
    hashp->nbufs = npages;
    bfp->next = bfp;
    bfp->prev = bfp;
    /*
	This space is calloc'd so these are already null

	bfp->ovfl = NULL;
	bfp->flags = 0;
	bfp->page = NULL;
	bfp->addr = 0;
    */
E 8
I 8
	hashp->nbufs = npages;
	bfp->next = bfp;
	bfp->prev = bfp;
	/*
	 * This space is calloc'd so these are already null.
	 *
	 * bfp->ovfl = NULL;
	 * bfp->flags = 0;
	 * bfp->page = NULL;
	 * bfp->addr = 0;
	 */
E 8
}

extern int
D 8
__buf_free ( do_free, to_disk )
int	do_free;
int	to_disk;
E 8
I 8
D 11
__buf_free(do_free, to_disk)
E 11
I 11
__buf_free(hashp, do_free, to_disk)
	HTAB *hashp;
E 11
	int do_free, to_disk;
E 8
{
D 8
    BUFHEAD	*bp;
E 8
I 8
	BUFHEAD *bp;
E 8

D 8
    /* Need to make sure that buffer manager has been initialized */
    if ( !LRU ) {
	return(0);
    }

    for ( bp = LRU; bp != &hashp->bufhead; ) {
	/* Check that the buffer is valid */
	if ( bp->addr || IS_BUCKET(bp->flags) ) {
	    if ( to_disk && (bp->flags & BUF_MOD) &&
		 __put_page (bp->page, bp->addr, IS_BUCKET(bp->flags), 0 )) {
		return (-1);
	    }
E 8
I 8
	/* Need to make sure that buffer manager has been initialized */
	if (!LRU)
		return (0);
	for (bp = LRU; bp != &hashp->bufhead;) {
		/* Check that the buffer is valid */
		if (bp->addr || IS_BUCKET(bp->flags)) {
			if (to_disk && (bp->flags & BUF_MOD) &&
D 11
			    __put_page(bp->page,
E 11
I 11
			    __put_page(hashp, bp->page,
E 11
			    bp->addr, IS_BUCKET(bp->flags), 0))
				return (-1);
		}
		/* Check if we are freeing stuff */
		if (do_free) {
			if (bp->page)
				free(bp->page);
			BUF_REMOVE(bp);
			free(bp);
			bp = LRU;
		} else
			bp = bp->prev;
E 8
	}
D 8

	/* Check if we are freeing stuff */
	if ( do_free ) {
	    if ( bp->page ) free ( bp->page );
	    BUF_REMOVE(bp);
	    (void)free ( bp );
	    bp = LRU;
	} else bp = bp->prev;
    }

    return(0);
E 8
I 8
	return (0);
E 8
}

extern void
D 8
__reclaim_buf ( bp )
BUFHEAD	*bp;
E 8
I 8
D 11
__reclaim_buf(bp)
E 11
I 11
__reclaim_buf(hashp, bp)
	HTAB *hashp;
E 11
	BUFHEAD *bp;
E 8
{
D 8
    bp->ovfl = 0;
    bp->addr = 0;
    bp->flags = 0;
    BUF_REMOVE ( bp );
    LRU_INSERT ( bp );
E 8
I 8
	bp->ovfl = 0;
	bp->addr = 0;
	bp->flags = 0;
	BUF_REMOVE(bp);
	LRU_INSERT(bp);
E 8
}
E 1
