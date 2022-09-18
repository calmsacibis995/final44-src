h28430
s 00002/00002/00506
d D 8.2 94/02/21 17:43:57 bostic 9 8
c cast alloc's to shut SunOS up
e
s 00002/00002/00506
d D 8.1 93/06/06 22:49:09 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00501
d D 5.6 93/06/06 22:49:05 bostic 7 5
c don't collide with err(3)
e
s 00002/00002/00505
d R 8.1 93/06/04 15:23:24 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00505
d D 5.5 93/02/19 16:35:12 bostic 5 4
c initialize function pointers (lint)
e
s 00004/00002/00501
d D 5.4 93/02/11 11:42:11 bostic 4 3
c move db.h to the end of the includes, make compat.h work better
e
s 00001/00001/00502
d D 5.3 91/11/24 11:06:20 bostic 3 2
c free the mpool structure on close, don't free pages anymore, they're
c allocated as part of the header
e
s 00001/00001/00502
d D 5.2 91/11/20 11:33:14 bostic 2 1
c can't increment/decrement void *, but gcc lets you anyway
e
s 00503/00000/00000
d D 5.1 91/09/04 11:38:07 bostic 1 0
c checkpoint btree mpool
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/stat.h>
I 4

E 4
#include <errno.h>
D 4
#include <db.h>
#include <unistd.h>
E 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 4
#include <unistd.h>

#include <db.h>
E 4
#define	__MPOOLINTERFACE_PRIVATE
#include "mpool.h"

static BKT *mpool_bkt __P((MPOOL *));
static BKT *mpool_look __P((MPOOL *, pgno_t));
static int  mpool_write __P((MPOOL *, BKT *));
#ifdef DEBUG
D 7
static void err __P((const char *fmt, ...));
E 7
I 7
static void __mpoolerr __P((const char *fmt, ...));
E 7
#endif

/*
 * MPOOL_OPEN -- initialize a memory pool.
 *
 * Parameters:
 *	key:		Shared buffer key.
 *	fd:		File descriptor.
 *	pagesize:	File page size.
 *	maxcache:	Max number of cached pages.
 *
 * Returns:
 *	MPOOL pointer, NULL on error.
 */
MPOOL *
mpool_open(key, fd, pagesize, maxcache)
	DBT *key;
	int fd;
	pgno_t pagesize, maxcache;
{
	struct stat sb;
	MPOOL *mp;
	int entry;

	if (fstat(fd, &sb))
		return (NULL);
	/* XXX
	 * We should only set st_size to 0 for pipes -- 4.4BSD has the fix so
	 * that stat(2) returns true for ISSOCK on pipes.  Until then, this is
	 * fairly close.
	 */
	if (!S_ISREG(sb.st_mode)) {
		errno = ESPIPE;
		return (NULL);
	}

D 9
	if ((mp = malloc(sizeof(MPOOL))) == NULL)
E 9
I 9
	if ((mp = (MPOOL *)malloc(sizeof(MPOOL))) == NULL)
E 9
		return (NULL);
	mp->free.cnext = mp->free.cprev = (BKT *)&mp->free;
	mp->lru.cnext = mp->lru.cprev = (BKT *)&mp->lru;
	for (entry = 0; entry < HASHSIZE; ++entry)
		mp->hashtable[entry].hnext = mp->hashtable[entry].hprev = 
		    mp->hashtable[entry].cnext = mp->hashtable[entry].cprev =
		    (BKT *)&mp->hashtable[entry];
	mp->curcache = 0;
	mp->maxcache = maxcache;
	mp->pagesize = pagesize;
	mp->npages = sb.st_size / pagesize;
	mp->fd = fd;
I 5
	mp->pgcookie = NULL;
	mp->pgin = mp->pgout = NULL;
E 5

#ifdef STATISTICS
	mp->cachehit = mp->cachemiss = mp->pagealloc = mp->pageflush = 
	    mp->pageget = mp->pagenew = mp->pageput = mp->pageread = 
	    mp->pagewrite = 0;
#endif
	return (mp);
}

/*
 * MPOOL_FILTER -- initialize input/output filters.
 *
 * Parameters:
 *	pgin:		Page in conversion routine.
 *	pgout:		Page out conversion routine.
 *	pgcookie:	Cookie for page in/out routines.
 */
void
mpool_filter(mp, pgin, pgout, pgcookie)
	MPOOL *mp;
	void (*pgin) __P((void *, pgno_t, void *));
	void (*pgout) __P((void *, pgno_t, void *));
	void *pgcookie;
{
	mp->pgin = pgin;
	mp->pgout = pgout;
	mp->pgcookie = pgcookie;
}
	
/*
 * MPOOL_NEW -- get a new page
 *
 * Parameters:
 *	mp:		mpool cookie
 *	pgnoadddr:	place to store new page number
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
void *
mpool_new(mp, pgnoaddr)
	MPOOL *mp;
	pgno_t *pgnoaddr;
{
	BKT *b;
	BKTHDR *hp;

#ifdef STATISTICS
	++mp->pagenew;
#endif
	/*
	 * Get a BKT from the cache.  Assign a new page number, attach it to
	 * the hash and lru chains and return.
	 */
	if ((b = mpool_bkt(mp)) == NULL)
		return (NULL);
	*pgnoaddr = b->pgno = mp->npages++;
	b->flags = MPOOL_PINNED;
	inshash(b, b->pgno);
	inschain(b, &mp->lru);
	return (b->page);
}

/*
 * MPOOL_GET -- get a page from the pool
 *
 * Parameters:
 *	mp:	mpool cookie
 *	pgno:	page number
 *	flags:	not used
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
void *
mpool_get(mp, pgno, flags)
	MPOOL *mp;
	pgno_t pgno;
	u_int flags;		/* XXX not used? */
{
	BKT *b;
	BKTHDR *hp;
	off_t off;
	int nr;

	/*
	 * If asking for a specific page that is already in the cache, find
	 * it and return it.
	 */
	if (b = mpool_look(mp, pgno)) {
#ifdef STATISTICS
		++mp->pageget;
#endif
#ifdef DEBUG
		if (b->flags & MPOOL_PINNED)
D 7
			err("mpool_get: page %d already pinned", b->pgno);
E 7
I 7
			__mpoolerr("mpool_get: page %d already pinned",
			    b->pgno);
E 7
#endif
		rmchain(b);
		inschain(b, &mp->lru);
		b->flags |= MPOOL_PINNED;
		return (b->page);
	}

	/* Not allowed to retrieve a non-existent page. */
	if (pgno >= mp->npages) {
		errno = EINVAL;
		return (NULL);
	}

	/* Get a page from the cache. */
	if ((b = mpool_bkt(mp)) == NULL)
		return (NULL);
	b->pgno = pgno;
	b->flags = MPOOL_PINNED;

#ifdef STATISTICS
	++mp->pageread;
#endif
	/* Read in the contents. */
	off = mp->pagesize * pgno;
	if (lseek(mp->fd, off, SEEK_SET) != off)
		return (NULL);
	if ((nr = read(mp->fd, b->page, mp->pagesize)) != mp->pagesize) {
		if (nr >= 0)
			errno = EFTYPE;
		return (NULL);
	}
	if (mp->pgin)
		(mp->pgin)(mp->pgcookie, b->pgno, b->page);

	inshash(b, b->pgno);
	inschain(b, &mp->lru);
#ifdef STATISTICS
	++mp->pageget;
#endif
	return (b->page);
}

/*
 * MPOOL_PUT -- return a page to the pool
 *
 * Parameters:
 *	mp:	mpool cookie
 *	page:	page pointer
 *	pgno:	page number
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
mpool_put(mp, page, flags)
	MPOOL *mp;
	void *page;
	u_int flags;
{
	BKT *baddr;
#ifdef DEBUG
	BKT *b;
#endif

#ifdef STATISTICS
	++mp->pageput;
#endif
D 2
	baddr = page - sizeof(BKT);
E 2
I 2
	baddr = (BKT *)((char *)page - sizeof(BKT));
E 2
#ifdef DEBUG
	if (!(baddr->flags & MPOOL_PINNED))
D 7
		err("mpool_put: page %d not pinned", b->pgno);
E 7
I 7
		__mpoolerr("mpool_put: page %d not pinned", b->pgno);
E 7
	for (b = mp->lru.cnext; b != (BKT *)&mp->lru; b = b->cnext) {
		if (b == (BKT *)&mp->lru)
D 7
			err("mpool_put: %0x: bad address", baddr);
E 7
I 7
			__mpoolerr("mpool_put: %0x: bad address", baddr);
E 7
		if (b == baddr)
			break;
	}
#endif
	baddr->flags &= ~MPOOL_PINNED;
	baddr->flags |= flags & MPOOL_DIRTY;
	return (RET_SUCCESS);
}

/*
 * MPOOL_CLOSE -- close the buffer pool
 *
 * Parameters:
 *	mp:	mpool cookie
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
mpool_close(mp)
	MPOOL *mp;
{
	BKT *b, *next;

	/* Free up any space allocated to the lru pages. */
	for (b = mp->lru.cprev; b != (BKT *)&mp->lru; b = next) {
		next = b->cprev;
D 3
		free(b->page);
E 3
		free(b);
	}
I 3
	free(mp);
E 3
	return (RET_SUCCESS);
}

/*
 * MPOOL_SYNC -- sync the file to disk.
 *
 * Parameters:
 *	mp:	mpool cookie
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
mpool_sync(mp)
	MPOOL *mp;
{
	BKT *b;

	for (b = mp->lru.cprev; b != (BKT *)&mp->lru; b = b->cprev)
		if (b->flags & MPOOL_DIRTY && mpool_write(mp, b) == RET_ERROR)
			return (RET_ERROR);
	return (fsync(mp->fd) ? RET_ERROR : RET_SUCCESS);
}

/*
 * MPOOL_BKT -- get/create a BKT from the cache
 *
 * Parameters:
 *	mp:	mpool cookie
 *
 * Returns:
 *	NULL on failure and a pointer to the BKT on success	
 */
static BKT *
mpool_bkt(mp)
	MPOOL *mp;
{
	BKT *b;

	if (mp->curcache < mp->maxcache)
		goto new;

	/*
	 * If the cache is maxxed out, search the lru list for a buffer we
	 * can flush.  If we find one, write it if necessary and take it off
	 * any lists.  If we don't find anything we grow the cache anyway.
	 * The cache never shrinks.
	 */
	for (b = mp->lru.cprev; b != (BKT *)&mp->lru; b = b->cprev)
		if (!(b->flags & MPOOL_PINNED)) {
			if (b->flags & MPOOL_DIRTY &&
			    mpool_write(mp, b) == RET_ERROR)
				return (NULL);
			rmhash(b);
			rmchain(b);
#ifdef STATISTICS
			++mp->pageflush;
#endif
#ifdef DEBUG
			{
				void *spage;
				spage = b->page;
				memset(b, 0xff, sizeof(BKT) + mp->pagesize);
				b->page = spage;
			}
#endif
			return (b);
		}

D 9
new:	if ((b = malloc(sizeof(BKT) + mp->pagesize)) == NULL)
E 9
I 9
new:	if ((b = (BKT *)malloc(sizeof(BKT) + mp->pagesize)) == NULL)
E 9
		return (NULL);
#ifdef STATISTICS
	++mp->pagealloc;
#endif
#ifdef DEBUG
	memset(b, 0xff, sizeof(BKT) + mp->pagesize);
#endif
	b->page = (char *)b + sizeof(BKT);
	++mp->curcache;
	return (b);
}

/*
 * MPOOL_WRITE -- sync a page to disk
 *
 * Parameters:
 *	mp:	mpool cookie
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
static int
mpool_write(mp, b)
	MPOOL *mp;
	BKT *b;
{
	off_t off;

	if (mp->pgout)
		(mp->pgout)(mp->pgcookie, b->pgno, b->page);

#ifdef STATISTICS
	++mp->pagewrite;
#endif
	off = mp->pagesize * b->pgno;
	if (lseek(mp->fd, off, SEEK_SET) != off)
		return (RET_ERROR);
	if (write(mp->fd, b->page, mp->pagesize) != mp->pagesize)
		return (RET_ERROR);
	b->flags &= ~MPOOL_DIRTY;
	return (RET_SUCCESS);
}

/*
 * MPOOL_LOOK -- lookup a page
 *
 * Parameters:
 *	mp:	mpool cookie
 *	pgno:	page number
 *
 * Returns:
 *	NULL on failure and a pointer to the BKT on success
 */
static BKT *
mpool_look(mp, pgno)
	MPOOL *mp;
	pgno_t pgno;
{
	register BKT *b;
	register BKTHDR *tb;

	/* XXX
	 * If find the buffer, put it first on the hash chain so can
	 * find it again quickly.
	 */
	tb = &mp->hashtable[HASHKEY(pgno)];
	for (b = tb->hnext; b != (BKT *)tb; b = b->hnext)
		if (b->pgno == pgno) {
#ifdef STATISTICS
			++mp->cachehit;
#endif
			return (b);
		}
#ifdef STATISTICS
	++mp->cachemiss;
#endif
	return (NULL);
}

#ifdef STATISTICS
/*
 * MPOOL_STAT -- cache statistics
 *
 * Parameters:
 *	mp:	mpool cookie
 */
void
mpool_stat(mp)
	MPOOL *mp;
{
	BKT *b;
	int cnt;
	char *sep;

	(void)fprintf(stderr, "%lu pages in the file\n", mp->npages);
	(void)fprintf(stderr,
	    "page size %lu, cacheing %lu pages of %lu page max cache\n",
	    mp->pagesize, mp->curcache, mp->maxcache);
	(void)fprintf(stderr, "%lu page puts, %lu page gets, %lu page new\n",
	    mp->pageput, mp->pageget, mp->pagenew);
	(void)fprintf(stderr, "%lu page allocs, %lu page flushes\n",
	    mp->pagealloc, mp->pageflush);
	if (mp->cachehit + mp->cachemiss)
		(void)fprintf(stderr,
		    "%.0f%% cache hit rate (%lu hits, %lu misses)\n", 
		    ((double)mp->cachehit / (mp->cachehit + mp->cachemiss))
		    * 100, mp->cachehit, mp->cachemiss);
	(void)fprintf(stderr, "%lu page reads, %lu page writes\n",
	    mp->pageread, mp->pagewrite);

	sep = "";
	cnt = 0;
	for (b = mp->lru.cnext; b != (BKT *)&mp->lru; b = b->cnext) {
		(void)fprintf(stderr, "%s%d", sep, b->pgno);
		if (b->flags & MPOOL_DIRTY)
			(void)fprintf(stderr, "d");
		if (b->flags & MPOOL_PINNED)
			(void)fprintf(stderr, "P");
		if (++cnt == 10) {
			sep = "\n";
			cnt = 0;
		} else
			sep = ", ";
			
	}
	(void)fprintf(stderr, "\n");
}
#endif

#ifdef DEBUG
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

static void
#if __STDC__
D 7
err(const char *fmt, ...)
E 7
I 7
__mpoolerr(const char *fmt, ...)
E 7
#else
D 7
err(fmt, va_alist)
E 7
I 7
__mpoolerr(fmt, va_alist)
E 7
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	abort();
	/* NOTREACHED */
}
#endif
E 1
