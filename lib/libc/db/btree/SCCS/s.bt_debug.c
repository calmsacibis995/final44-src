h42762
s 00002/00003/00303
d D 8.2 94/02/21 15:08:11 bostic 11 10
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00304
d D 8.1 93/06/04 15:20:13 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00018/00288
d D 5.9 93/05/16 15:44:06 bostic 9 8
c lint; break BTF flags up into btree/recno (B_, R_) categories
e
s 00000/00001/00306
d D 5.8 93/05/01 15:31:22 bostic 8 7
c recognize different byte orders automatically; m_lorder no longer used
e
s 00001/00001/00306
d D 5.7 93/02/14 17:39:17 bostic 7 6
c index -> indx_t
e
s 00001/00001/00306
d D 5.6 93/02/11 11:39:20 bostic 6 5
c move db.h to the end of the includes, make compat.h work better
e
s 00007/00005/00300
d D 5.5 93/01/10 12:24:19 bostic 5 4
c make numbers fixed size so it's easier to read
e
s 00021/00000/00284
d D 5.4 92/12/04 14:15:09 bostic 4 3
c add routine to dump a singlep age
e
s 00002/00000/00282
d D 5.3 92/11/13 16:05:31 bostic 3 2
c prettiness police
e
s 00038/00001/00244
d D 5.2 91/09/12 11:12:16 bostic 2 1
c add routine to dump the meta page
e
s 00245/00000/00000
d D 5.1 91/09/04 12:50:46 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
I 3

E 3
D 6
#include <db.h>
E 6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 3

I 6
#include <db.h>
E 6
E 3
#include "btree.h"

#ifdef DEBUG
/*
 * BT_DUMP -- Dump the tree
 *
 * Parameters:
 *	dbp:	pointer to the DB
 */
void
__bt_dump(dbp)
	DB *dbp;
{
	BTREE *t;
	PAGE *h;
	pgno_t i;
	char *sep;

	t = dbp->internal;
D 2
	(void)fprintf(stderr, "%s: pgsz %d", 
E 2
I 2
	(void)fprintf(stderr, "%s: pgsz %d",
E 2
D 9
	    ISSET(t, BTF_INMEM) ? "memory" : "disk", t->bt_psize);
	if (ISSET(t, BTF_RECNO))
E 9
I 9
	    ISSET(t, B_INMEM) ? "memory" : "disk", t->bt_psize);
	if (ISSET(t, R_RECNO))
E 9
		(void)fprintf(stderr, " keys %lu", t->bt_nrecs);
I 2
#undef X
E 2
#define	X(flag, name) \
	if (ISSET(t, flag)) { \
		(void)fprintf(stderr, "%s%s", sep, name); \
		sep = ", "; \
	}
	if (t->bt_flags) {
		sep = " flags (";
D 9
		X(BTF_DELCRSR,	"DELCRSR");
		X(BTF_FIXEDLEN,	"FIXEDLEN");
		X(BTF_INMEM,	"INMEM");
		X(BTF_NODUPS,	"NODUPS");
		X(BTF_RDONLY,	"RDONLY");
		X(BTF_RECNO,	"RECNO");
		X(BTF_SEQINIT,	"SEQINIT");
		X(BTF_METADIRTY,"METADIRTY");
E 9
I 9
		X(B_DELCRSR,	"DELCRSR");
		X(R_FIXLEN,	"FIXLEN");
		X(B_INMEM,	"INMEM");
		X(B_NODUPS,	"NODUPS");
		X(B_RDONLY,	"RDONLY");
		X(R_RECNO,	"RECNO");
		X(B_SEQINIT,	"SEQINIT");
		X(B_METADIRTY,"METADIRTY");
E 9
		(void)fprintf(stderr, ")\n");
	}
#undef X

	for (i = P_ROOT; (h = mpool_get(t->bt_mp, i, 0)) != NULL; ++i) {
		__bt_dpage(h);
		(void)mpool_put(t->bt_mp, h, 0);
	}
}

/*
I 2
 * BT_DMPAGE -- Dump the meta page
 *
 * Parameters:
 *	h:	pointer to the PAGE
 */
void
__bt_dmpage(h)
	PAGE *h;
{
	BTMETA *m;
	char *sep;

	m = (BTMETA *)h;
	(void)fprintf(stderr, "magic %lx\n", m->m_magic);
	(void)fprintf(stderr, "version %lu\n", m->m_version);
	(void)fprintf(stderr, "psize %lu\n", m->m_psize);
	(void)fprintf(stderr, "free %lu\n", m->m_free);
	(void)fprintf(stderr, "nrecs %lu\n", m->m_nrecs);
	(void)fprintf(stderr, "flags %lu", m->m_flags);
#undef X
#define	X(flag, name) \
	if (m->m_flags & flag) { \
		(void)fprintf(stderr, "%s%s", sep, name); \
		sep = ", "; \
	}
	if (m->m_flags) {
		sep = " (";
D 9
		X(BTF_NODUPS,	"NODUPS");
		X(BTF_RECNO,	"RECNO");
E 9
I 9
		X(B_NODUPS,	"NODUPS");
		X(R_RECNO,	"RECNO");
E 9
		(void)fprintf(stderr, ")");
	}
D 8
	(void)fprintf(stderr, "\nlorder %lu\n", m->m_lorder);
E 8
}

/*
I 4
 * BT_DNPAGE -- Dump the page
 *
 * Parameters:
 *	n:	page number to dump.
 */
void
__bt_dnpage(dbp, pgno)
	DB *dbp;
	pgno_t pgno;
{
	BTREE *t;
	PAGE *h;

	t = dbp->internal;
	if ((h = mpool_get(t->bt_mp, pgno, 0)) != NULL) {
		__bt_dpage(h);
		(void)mpool_put(t->bt_mp, h, 0);
	}
}

/*
E 4
E 2
 * BT_DPAGE -- Dump the page
 *
 * Parameters:
 *	h:	pointer to the PAGE
 */
void
__bt_dpage(h)
	PAGE *h;
{
	BINTERNAL *bi;
	BLEAF *bl;
	RINTERNAL *ri;
	RLEAF *rl;
D 7
	index_t cur, top;
E 7
I 7
	indx_t cur, top;
E 7
	char *sep;

	(void)fprintf(stderr, "    page %d: (", h->pgno);
I 2
#undef X
E 2
#define	X(flag, name) \
	if (h->flags & flag) { \
		(void)fprintf(stderr, "%s%s", sep, name); \
		sep = ", "; \
	}
	sep = "";
	X(P_BINTERNAL,	"BINTERNAL")		/* types */
	X(P_BLEAF,	"BLEAF")
	X(P_RINTERNAL,	"RINTERNAL")		/* types */
	X(P_RLEAF,	"RLEAF")
	X(P_OVERFLOW,	"OVERFLOW")
	X(P_PRESERVE,	"PRESERVE");
	(void)fprintf(stderr, ")\n");
#undef X

	(void)fprintf(stderr, "\tprev %2d next %2d", h->prevpg, h->nextpg);
	if (h->flags & P_OVERFLOW)
		return;

	top = NEXTINDEX(h);
	(void)fprintf(stderr, " lower %3d upper %3d nextind %d\n",
	    h->lower, h->upper, top);
	for (cur = 0; cur < top; cur++) {
		(void)fprintf(stderr, "\t[%03d] %4d ", cur, h->linp[cur]);
		switch(h->flags & P_TYPE) {
		case P_BINTERNAL:
			bi = GETBINTERNAL(h, cur);
			(void)fprintf(stderr,
D 5
			    "size %2d pgno %2d", bi->ksize, bi->pgno);
E 5
I 5
			    "size %03d pgno %03d", bi->ksize, bi->pgno);
E 5
			if (bi->flags & P_BIGKEY)
				(void)fprintf(stderr, " (indirect)");
			else if (bi->ksize)
D 5
				(void)fprintf(stderr, " {%s}", bi->bytes);
E 5
I 5
				(void)fprintf(stderr,
D 9
				    " {%.*s}", bi->ksize, bi->bytes);
E 9
I 9
				    " {%.*s}", (int)bi->ksize, bi->bytes);
E 9
E 5
			break;
		case P_RINTERNAL:
			ri = GETRINTERNAL(h, cur);
D 5
			(void)fprintf(stderr, "entries %2d pgno %2d",
E 5
I 5
			(void)fprintf(stderr, "entries %03d pgno %03d",
E 5
				ri->nrecs, ri->pgno);
			break;
		case P_BLEAF:
			bl = GETBLEAF(h, cur);
			if (bl->flags & P_BIGKEY)
				(void)fprintf(stderr,
				    "big key page %lu size %u/",
				    *(pgno_t *)bl->bytes,
				    *(size_t *)(bl->bytes + sizeof(pgno_t)));
			else if (bl->ksize)
				(void)fprintf(stderr, "%s/", bl->bytes);
			if (bl->flags & P_BIGDATA)
				(void)fprintf(stderr,
				    "big data page %lu size %u",
				    *(pgno_t *)(bl->bytes + bl->ksize),
				    *(size_t *)(bl->bytes + bl->ksize +
				    sizeof(pgno_t)));
			else if (bl->dsize)
D 9
				(void)fprintf(stderr,
D 5
				    "%s", bl->bytes + bl->ksize);
E 5
I 5
				    "%.*s", bl->dsize, bl->bytes + bl->ksize);
E 9
I 9
				(void)fprintf(stderr, "%.*s",
				    (int)bl->dsize, bl->bytes + bl->ksize);
E 9
E 5
			break;
		case P_RLEAF:
			rl = GETRLEAF(h, cur);
			if (rl->flags & P_BIGDATA)
				(void)fprintf(stderr,
				    "big data page %lu size %u",
				    *(pgno_t *)rl->bytes,
				    *(size_t *)(rl->bytes + sizeof(pgno_t)));
			else if (rl->dsize)
D 5
				(void)fprintf(stderr, "%s", rl->bytes);
E 5
I 5
				(void)fprintf(stderr,
D 9
				    "%.*s", rl->dsize, rl->bytes);
E 9
I 9
				    "%.*s", (int)rl->dsize, rl->bytes);
E 9
E 5
			break;
		}
		(void)fprintf(stderr, "\n");
	}
}
#endif

#ifdef STATISTICS
/*
 * BT_STAT -- Gather/print the tree statistics
 *
 * Parameters:
 *	dbp:	pointer to the DB
 */
void
__bt_stat(dbp)
	DB *dbp;
{
D 11
	extern u_long bt_cache_hit, bt_cache_miss;
	extern u_long bt_rootsplit, bt_split, bt_sortsplit;
	extern u_long bt_pfxsaved;
E 11
I 11
	extern u_long bt_cache_hit, bt_cache_miss, bt_pfxsaved, bt_rootsplit;
	extern u_long bt_sortsplit, bt_split;
E 11
	BTREE *t;
	PAGE *h;
	pgno_t i, pcont, pinternal, pleaf;
	u_long ifree, lfree, nkeys;
	int levels;

	t = dbp->internal;
	pcont = pinternal = pleaf = 0;
	nkeys = ifree = lfree = 0;
	for (i = P_ROOT; (h = mpool_get(t->bt_mp, i, 0)) != NULL; ++i) {
		switch(h->flags & P_TYPE) {
		case P_BINTERNAL:
		case P_RINTERNAL:
			++pinternal;
			ifree += h->upper - h->lower;
			break;
		case P_BLEAF:
		case P_RLEAF:
			++pleaf;
			lfree += h->upper - h->lower;
			nkeys += NEXTINDEX(h);
			break;
		case P_OVERFLOW:
			++pcont;
			break;
		}
		(void)mpool_put(t->bt_mp, h, 0);
	}

	/* Count the levels of the tree. */
	for (i = P_ROOT, levels = 0 ;; ++levels) {
		h = mpool_get(t->bt_mp, i, 0);
		if (h->flags & (P_BLEAF|P_RLEAF)) {
			if (levels == 0)
				levels = 1;
			(void)mpool_put(t->bt_mp, h, 0);
			break;
		}
D 9
		i = ISSET(t, BTF_RECNO) ?
E 9
I 9
		i = ISSET(t, R_RECNO) ?
E 9
		    GETRINTERNAL(h, 0)->pgno :
		    GETBINTERNAL(h, 0)->pgno;
		(void)mpool_put(t->bt_mp, h, 0);
	}

	(void)fprintf(stderr, "%d level%s with %ld keys",
	    levels, levels == 1 ? "" : "s", nkeys);
D 9
	if (ISSET(t, BTF_RECNO))
E 9
I 9
	if (ISSET(t, R_RECNO))
E 9
		(void)fprintf(stderr, " (%ld header count)", t->bt_nrecs);
	(void)fprintf(stderr,
	    "\n%lu pages (leaf %ld, internal %ld, overflow %ld)\n",
	    pinternal + pleaf + pcont, pleaf, pinternal, pcont);
	(void)fprintf(stderr, "%ld cache hits, %ld cache misses\n",
	    bt_cache_hit, bt_cache_miss);
	(void)fprintf(stderr, "%ld splits (%ld root splits, %ld sort splits)\n",
	    bt_split, bt_rootsplit, bt_sortsplit);
	pleaf *= t->bt_psize - BTDATAOFF;
	if (pleaf)
		(void)fprintf(stderr,
		    "%.0f%% leaf fill (%ld bytes used, %ld bytes free)\n",
		    ((double)(pleaf - lfree) / pleaf) * 100,
		    pleaf - lfree, lfree);
	pinternal *= t->bt_psize - BTDATAOFF;
	if (pinternal)
		(void)fprintf(stderr,
		    "%.0f%% internal fill (%ld bytes used, %ld bytes free\n",
		    ((double)(pinternal - ifree) / pinternal) * 100,
		    pinternal - ifree, ifree);
	if (bt_pfxsaved)
		(void)fprintf(stderr, "prefix checking removed %lu bytes.\n",
		    bt_pfxsaved);
}
#endif
E 1
