h54237
s 00019/00018/00308
d D 8.5 94/02/21 15:08:19 bostic 20 19
c first pass at making DB use basic integral types (the Alpha port)
e
s 00001/00001/00325
d D 8.4 93/12/18 11:22:52 bostic 19 18
c typo
e
s 00001/00000/00325
d D 8.3 93/09/14 10:18:15 bostic 18 17
c the __bt_search value shouldn't be stored in a static, can't pin
c across calls in that case
e
s 00017/00011/00308
d D 8.2 93/09/07 11:50:19 bostic 17 16
c add B_DB_{LOCK,SHMEM,TXN}, local copies of DB_{LOCK,SHMEM,TXN}
c add bt_pinned field, if DB_LOCK not set, pin page across calls and don't
c copy key/data pair
e
s 00002/00002/00317
d D 8.1 93/06/04 15:21:12 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00318
d D 5.15 93/05/22 14:12:19 bostic 15 14
c support 64K pages
e
s 00019/00016/00300
d D 5.14 93/05/16 15:42:29 bostic 14 13
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00015/00009/00301
d D 5.13 93/05/01 15:33:46 bostic 13 12
c restore BTF_NODUPS and BTF_RECNO to their original values, and note
c that they cannot be altered
c recognize different byte orders automatically; m_lorder no longer used
e
s 00021/00014/00289
d D 5.12 93/03/19 14:46:41 bostic 12 11
c clean up mmap and file pointer uses in recno interface
e
s 00003/00003/00300
d D 5.11 93/02/16 12:33:49 bostic 11 10
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00009/00009/00294
d D 5.10 93/02/14 17:39:27 bostic 10 9
c index -> indx_t
e
s 00007/00007/00296
d D 5.9 92/11/13 16:04:39 bostic 9 8
c add BTF_RINMEM for recno in memory trees
c add CLR, ISSET
e
s 00001/00001/00302
d D 5.8 92/10/09 16:25:43 bostic 8 7
c implement free page reuse
e
s 00001/00000/00302
d D 5.7 92/06/23 12:38:31 bostic 7 6
c make recno eof flag part of each BT struct
e
s 00002/00001/00300
d D 5.6 91/12/16 14:03:05 bostic 6 5
c fix BTDATAOFF macro to work even if the compiler pads to long boundary
e
s 00018/00009/00283
d D 5.5 91/11/20 11:31:43 bostic 5 4
c can't increment an lvalue, but gcc lets you anyway
e
s 00053/00058/00239
d D 5.4 91/09/12 11:17:04 bostic 4 3
c delete maxkeypage; do pointer arithmetic in the macros instead of using
c += sizeof; consolidate macros; replace minkeypage with bt_ovflsize; lots
c of minor cleanups.
c 
e
s 00238/00241/00059
d D 5.3 91/09/04 12:47:29 bostic 3 2
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00000/00003/00300
d D 5.2 91/02/22 17:16:35 bostic 2 1
c ANSI prototypes
e
s 00303/00000/00000
d D 5.1 91/01/23 08:12:54 mao 1 0
c date and time created 91/01/23 08:12:54 by mao
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
E 3
I 3
D 16
 * Copyright (c) 1991 The Regents of the University of California.
E 3
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
I 3
 *
 *	%W% (Berkeley) %G%
E 3
 */

I 3
#include <mpool.h>

D 4
#define	DEFMAXKEYPAGE	(0)		/* Maximum keys per page */
E 4
#define	DEFMINKEYPAGE	(2)		/* Minimum keys per page */
#define	MINCACHE	(5)		/* Minimum cached pages */
#define	MINPSIZE	(512)		/* Minimum page size */

E 3
/*
D 3
 *  %W% (Berkeley) %G%
E 3
I 3
D 4
 * Page 0 of a btree file contains a BTMETA structure.  The rest of the first
 * page is empty, so that all disk operations are page-aligned.  This page is
 * also used as an out-of-band page, i.e. page pointers that point to nowhere
 * point to page 0.  The m_nrecs field is used only the RECNO code.  This is 
 * because the btree doesn't really need it and it requires that put or delete
 * calls modify the meta data.
E 4
I 4
 * Page 0 of a btree file contains a copy of the meta-data.  This page is also
 * used as an out-of-band page, i.e. page pointers that point to nowhere point
 * to page 0.  Page 1 is the root of the btree.
E 4
E 3
 */
I 3
#define	P_INVALID	 0		/* Invalid tree page number. */
D 4
#define	P_META		 0		/* Tree meta-info page number. */
E 4
I 4
#define	P_META		 0		/* Tree metadata page number. */
E 4
#define	P_ROOT		 1		/* Tree root page number. */
E 3

D 3
typedef char	*BTREE;		/* should really be (void *) */ 
E 3
I 3
D 4
typedef struct BTMETA {
	u_long	m_magic;		/* magic number */
	u_long	m_version;		/* version */
	u_long	m_psize;		/* page size */
	u_long	m_free;			/* page number of first free page */
	u_long	m_nrecs;		/* R: number of records */
#define	SAVEMETA	(BTF_NODUPS | BTF_RECNO)
	u_long	m_flags;		/* bt_flags & SAVEMETA */
	u_long	m_lorder;		/* byte order */
} BTMETA;
E 3

E 4
D 3
/* #define	DEBUG */
E 3
I 3
/*
D 4
 * There are five page layouts in the btree: btree internal pages, btree leaf
 * pages, recno internal pages, recno leaf pages and overflow pages.  Each type
 * of page starts with a page header as typed by PAGE.
E 4
I 4
 * There are five page layouts in the btree: btree internal pages (BINTERNAL),
 * btree leaf pages (BLEAF), recno internal pages (RINTERNAL), recno leaf pages
 * (RLEAF) and overflow pages.  All five page types have a page header (PAGE).
D 20
 * This implementation requires that longs within structures are NOT padded.
E 20
I 20
 * This implementation requires that values within structures NOT be padded.
E 20
 * (ANSI C permits random padding.)  If your compiler pads randomly you'll have
 * to do some work to get this package to run.
E 4
 */
D 17
typedef struct PAGE {
E 17
I 17
typedef struct _page {
E 17
	pgno_t	pgno;			/* this page's page number */
	pgno_t	prevpg;			/* left sibling */
	pgno_t	nextpg;			/* right sibling */
E 3

D 3
#define RET_ERROR	-1
#define RET_SUCCESS	 0
#define RET_SPECIAL	 1
E 3
I 3
#define	P_BINTERNAL	0x01		/* btree internal page */
#define	P_BLEAF		0x02		/* leaf page */
#define	P_OVERFLOW	0x04		/* overflow page */
#define	P_RINTERNAL	0x08		/* recno internal page */
#define	P_RLEAF		0x10		/* leaf page */
#define P_TYPE		0x1f		/* type mask */
E 3
D 20

E 20
D 3
#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif /* ndef TRUE */
E 3
I 3
#define	P_PRESERVE	0x20		/* never delete this chain of pages */
D 20
	u_long	flags;
E 20
I 20
	u_int32_t flags;
E 20
E 3

D 3
#ifndef NULL
#define NULL	0
#endif /* ndef NULL */
E 3
I 3
D 10
	index_t	lower;			/* lower bound of free space on page */
	index_t	upper;			/* upper bound of free space on page */
	index_t	linp[1];		/* long-aligned VARIABLE LENGTH DATA */
E 10
I 10
	indx_t	lower;			/* lower bound of free space on page */
	indx_t	upper;			/* upper bound of free space on page */
D 20
	indx_t	linp[1];		/* long-aligned VARIABLE LENGTH DATA */
E 20
I 20
	indx_t	linp[1];		/* indx_t-aligned VAR. LENGTH DATA */
E 20
E 10
} PAGE;
E 3

D 2
/* libc */
extern char *malloc();

E 2
D 3
/* these are defined in lrucache.c */
extern char	*lruinit();
extern char	*lruget();
extern char	*lrugetnew();
extern int	lrusync();
extern int	lruwrite();
extern int	lrurelease();
extern void	lrufree();
E 3
I 3
/* First and next index. */
D 6
#define	BTDATAOFF	(sizeof(PAGE) - sizeof(index_t))
E 6
I 6
#define	BTDATAOFF	(sizeof(pgno_t) + sizeof(pgno_t) + sizeof(pgno_t) + \
D 10
			    sizeof(u_long) + sizeof(index_t) + sizeof(index_t))
E 6
#define	NEXTINDEX(p)	(((p)->lower - BTDATAOFF) / sizeof(index_t))
E 10
I 10
D 20
			    sizeof(u_long) + sizeof(indx_t) + sizeof(indx_t))
E 20
I 20
			    sizeof(u_int32_t) + sizeof(indx_t) + sizeof(indx_t))
E 20
#define	NEXTINDEX(p)	(((p)->lower - BTDATAOFF) / sizeof(indx_t))
E 10
E 3

D 3
/* these are defined here */
extern BTREE	bt_open();
extern int	bt_close();
extern int	bt_delete();
extern int	bt_get();
extern int	bt_put();
extern int	bt_seq();
extern int	bt_sync();

E 3
/*
D 3
 *  Private types.  What you choose for these depends on how big you
 *  want to let files get, and how big you want to let pages get.
E 3
I 3
 * For pages other than overflow pages, there is an array of offsets into the
 * rest of the page immediately following the page header.  Each offset is to
 * an item which is unique to the type of page.  The h_lower offset is just
 * past the last filled-in index.  The h_upper offset is the first item on the
 * page.  Offsets are from the beginning of the page.
 *
 * If an item is too big to store on a single page, a flag is set and the item
 * is a { page, size } pair such that the page is the first page of an overflow
 * chain with size bytes of item.  Overflow pages are simply bytes without any
 * external structure.
 *
D 20
 * The size and page number fields in the items are long aligned so they can be
 * manipulated without copying.
E 20
I 20
 * The page number and size fields in the items are pgno_t-aligned so they can
 * be manipulated without copying.  (This presumes that 32 bit items can be
 * manipulated on this system.)
E 20
E 3
 */
I 3
D 4
#define	LALIGN(l)	(((l) + sizeof(u_long) - 1) & ~(sizeof(u_long) - 1))
E 4
I 4
D 20
#define	LALIGN(n)	(((n) + sizeof(u_long) - 1) & ~(sizeof(u_long) - 1))
E 20
I 20
#define	LALIGN(n) \
	(((n) + sizeof(pgno_t) - 1) & ~(sizeof(pgno_t) - 1))
E 20
E 4
#define	NOVFLSIZE	(sizeof(pgno_t) + sizeof(size_t))
E 3

D 3
typedef u_long	index_t;	/* so # bytes on a page fits in a long */
typedef u_long	pgno_t;		/* so # of pages in a btree fits in a long */

E 3
/*
D 3
 *  When we do searches, we push the parent page numbers onto a stack
 *  as we descend the tree.  This is so that for insertions, we can
 *  find our way back up to do internal page insertions and splits.
E 3
I 3
 * For the btree internal pages, the item is a key.  BINTERNALs are {key, pgno}
 * pairs, such that the key compares less than or equal to all of the records
 * on that page.  For a tree without duplicate keys, an internal page with two
 * consecutive keys, a and b, will have all records greater than or equal to a
 * and less than b stored on the page associated with a.  Duplicate keys are
 * somewhat special and can cause duplicate internal and leaf page records and
 * some minor modifications of the above rule.
E 3
 */
I 3
D 17
typedef struct BINTERNAL {
E 17
I 17
typedef struct _binternal {
E 17
	size_t	ksize;			/* key size */
	pgno_t	pgno;			/* page number stored on */
#define	P_BIGDATA	0x01		/* overflow data */
#define	P_BIGKEY	0x02		/* overflow key */
	u_char	flags;
	char	bytes[1];		/* data */
} BINTERNAL;
E 3

D 3
typedef struct BTSTACK {
	pgno_t		bts_pgno;
	struct BTSTACK	*bts_next;
} BTSTACK;
E 3
I 3
/* Get the page's BINTERNAL structure at index indx. */
#define	GETBINTERNAL(pg, indx) \
	((BINTERNAL *)((char *)(pg) + (pg)->linp[indx]))
E 3

D 3
/*
 *  Every btree page has a header that looks like this.  Flags are given
 *  in the #define's for the F_ flags (see below).
 */
E 3
I 3
/* Get the number of bytes in the entry. */
#define NBINTERNAL(len) \
	LALIGN(sizeof(size_t) + sizeof(pgno_t) + sizeof(u_char) + (len))
E 3

D 3
typedef struct BTHEADER {
	pgno_t h_pgno;		/* page number of this page */
	pgno_t h_prevpg;	/* left sibling */
	pgno_t h_nextpg;	/* right sibling */
E 3
I 3
/* Copy a BINTERNAL entry to the page. */
#define	WR_BINTERNAL(p, size, pgno, flags) { \
D 4
	*(size_t *)p = size; \
	p += sizeof(size_t); \
	*(pgno_t *)p = pgno; \
	p += sizeof(pgno_t); \
	*(u_char *)p = flags; \
	p += sizeof(u_char); \
E 4
I 4
D 5
	*((size_t *)p)++ = size; \
	*((pgno_t *)p)++ = pgno; \
	*((u_char *)p)++ = flags; \
E 5
I 5
	*(size_t *)p = size; \
	p += sizeof(size_t); \
	*(pgno_t *)p = pgno; \
	p += sizeof(pgno_t); \
	*(u_char *)p = flags; \
	p += sizeof(u_char); \
E 5
E 4
}
E 3

D 3
#define F_LEAF		0x01	/* leaf page, contains user data */
#define F_CONT		0x02	/* continuation page (large items) */
#define F_DIRTY		0x04	/* need to write to disk */
#define F_PRESERVE	0x08	/* never delete this chain of pages */

	u_long h_flags;		/* page state */
	index_t h_lower;	/* lower bound of free space on page */
	index_t h_upper;	/* upper bound of free space on page */
	index_t h_linp[1];	/* VARIABLE LENGTH DATA AT END OF STRUCT */
} BTHEADER;

E 3
/*
D 3
 *  HTBUCKETs are hash table buckets for looking up pages of in-memory
 *  btrees by page number.  We use this indirection, rather than direct
 *  pointers, so that the code for manipulating in-memory trees is the
 *  same as that for manipulating on-disk trees.
E 3
I 3
 * For the recno internal pages, the item is a page number with the number of
 * keys found on that page and below.
E 3
 */
I 3
D 17
typedef struct RINTERNAL {
E 17
I 17
typedef struct _rinternal {
E 17
	recno_t	nrecs;			/* number of records */
	pgno_t	pgno;			/* page number stored below */
} RINTERNAL;
E 3

D 3
typedef struct HTBUCKET {
	pgno_t		ht_pgno;
	BTHEADER	*ht_page;
	struct HTBUCKET	*ht_next;
} HTBUCKET;
E 3
I 3
/* Get the page's RINTERNAL structure at index indx. */
#define	GETRINTERNAL(pg, indx) \
	((RINTERNAL *)((char *)(pg) + (pg)->linp[indx]))
E 3

D 3
typedef HTBUCKET	**HTABLE;
E 3
I 3
/* Get the number of bytes in the entry. */
#define NRINTERNAL \
	LALIGN(sizeof(recno_t) + sizeof(pgno_t))
E 3

D 3
/* minimum size we'll let a page be */
#define MINPSIZE	512
E 3
I 3
/* Copy a RINTERAL entry to the page. */
#define	WR_RINTERNAL(p, nrecs, pgno) { \
D 4
	*(size_t *)p = nrecs; \
	p += sizeof(recno_t); \
E 4
I 4
D 5
	*((recno_t *)p)++ = nrecs; \
E 5
I 5
	*(recno_t *)p = nrecs; \
	p += sizeof(recno_t); \
E 5
E 4
	*(pgno_t *)p = pgno; \
}
E 3

D 3
/* default cache size, in bytes */
#define DEFCACHE	(20 * 1024)
E 3
I 3
/* For the btree leaf pages, the item is a key and data pair. */
D 17
typedef struct BLEAF {
E 17
I 17
typedef struct _bleaf {
E 17
	size_t	ksize;			/* size of key */
	size_t	dsize;			/* size of data */
	u_char	flags;			/* P_BIGDATA, P_BIGKEY */
	char	bytes[1];		/* data */
} BLEAF;
E 3

D 3
/* hash table size for in-memory trees */
#define	HTSIZE		128
E 3
I 3
/* Get the page's BLEAF structure at index indx. */
#define	GETBLEAF(pg, indx) \
	((BLEAF *)((char *)(pg) + (pg)->linp[indx]))
E 3

D 3
/* generate a hash key from a page number */
#define HASHKEY(pgno)	((pgno - 1) % HTSIZE)
E 3
I 3
/* Get the number of bytes in the entry. */
D 4
#define NBLEAF(p) \
	LALIGN(sizeof(size_t) + sizeof(size_t) + sizeof(u_char) + \
	    (p)->ksize + (p)->dsize)
E 4
I 4
#define NBLEAF(p)	NBLEAFDBT((p)->ksize, (p)->dsize)
E 4
E 3

D 3
/*
 *  Disk btrees have a file descriptor, and may also have an lru buffer
 *  cache, if the user asked for one.
 */
E 3
I 3
/* Get the number of bytes in the user's key/data pair. */
#define NBLEAFDBT(ksize, dsize) \
	LALIGN(sizeof(size_t) + sizeof(size_t) + sizeof(u_char) + \
	    (ksize) + (dsize))
E 3

D 3
typedef struct BTDISK {
	int	d_fd;
	char	*d_cache;
} BTDISK;
E 3
I 3
/* Copy a BLEAF entry to the page. */
#define	WR_BLEAF(p, key, data, flags) { \
D 4
	*(size_t *)p = key->size; \
	p += sizeof(size_t); \
	*(size_t *)p = data->size; \
	p += sizeof(size_t); \
	*(u_char *)p = flags; \
	p += sizeof(u_char); \
E 4
I 4
D 5
	*((size_t *)p)++ = key->size; \
	*((size_t *)p)++ = data->size; \
	*((u_char *)p)++ = flags; \
E 5
I 5
	*(size_t *)p = key->size; \
	p += sizeof(size_t); \
	*(size_t *)p = data->size; \
	p += sizeof(size_t); \
	*(u_char *)p = flags; \
	p += sizeof(u_char); \
E 5
E 4
D 11
	bcopy(key->data, p, key->size); \
E 11
I 11
	memmove(p, key->data, key->size); \
E 11
	p += key->size; \
D 11
	bcopy(data->data, p, data->size); \
E 11
I 11
	memmove(p, data->data, data->size); \
E 11
}
E 3

D 3
/*
 *  Cursors keep track of the current location in a sequential scan of
 *  the database.  Since btrees impose a total ordering on keys, we can
 *  walk forward or backward through the database from any point.  Cursors
 *  survive updates to the tree, and can be used to delete a particular
 *  record.
 */
E 3
I 3
/* For the recno leaf pages, the item is a data entry. */
D 17
typedef struct RLEAF {
E 17
I 17
typedef struct _rleaf {
E 17
	size_t	dsize;			/* size of data */
	u_char	flags;			/* P_BIGDATA */
	char	bytes[1];
} RLEAF;
E 3

D 3
typedef struct CURSOR {
	pgno_t		c_pgno;		/* pgno of current item in scan */
	index_t		c_index;	/* index of current item in scan */
	char		*c_key;		/* current key, used for updates */
E 3
I 3
/* Get the page's RLEAF structure at index indx. */
#define	GETRLEAF(pg, indx) \
	((RLEAF *)((char *)(pg) + (pg)->linp[indx]))
E 3

D 3
#define CRSR_BEFORE	0x01
E 3
I 3
/* Get the number of bytes in the entry. */
D 4
#define NRLEAF(p) \
	LALIGN(sizeof(size_t) + sizeof(u_char) + (p)->dsize)
E 4
I 4
#define NRLEAF(p)	NRLEAFDBT((p)->dsize)
E 4
E 3

D 3
	u_char		c_flags;	/* to handle updates properly */
} CURSOR;
E 3
I 3
/* Get the number of bytes from the user's data. */
#define	NRLEAFDBT(dsize) \
	LALIGN(sizeof(size_t) + sizeof(u_char) + (dsize))
E 3

D 3
/*
 *  The private btree data structure.  The user passes a pointer to one of
 *  these when we are to manipulate a tree, but the BTREE type is opaque
 *  to him.
 */
E 3
I 3
/* Copy a RLEAF entry to the page. */
#define	WR_RLEAF(p, data, flags) { \
D 4
	*(size_t *)p = data->size; \
	p += sizeof(size_t); \
	*(u_char *)p = flags; \
	p += sizeof(u_char); \
E 4
I 4
D 5
	*((size_t *)p)++ = data->size; \
	*((u_char *)p)++ = flags; \
E 5
I 5
	*(size_t *)p = data->size; \
	p += sizeof(size_t); \
	*(u_char *)p = flags; \
	p += sizeof(u_char); \
E 5
E 4
D 11
	bcopy(data->data, p, data->size); \
E 11
I 11
	memmove(p, data->data, data->size); \
E 11
}
E 3

D 3
typedef struct BTREEDATA_P {
	char		*bt_fname;		/* NULL for in-memory trees */
	union {
		BTDISK	bt_d;			/* for on-disk btrees */
		HTABLE	bt_ht;			/* hash table for mem trees */
	} bt_s;
	size_t		bt_psize;		/* page size for btree pages */
	int		(*bt_compare)();	/* key comparison function */
	pgno_t		bt_npages;		/* number of pages in tree */
	BTHEADER	*bt_curpage;		/* current page contents */
	pgno_t		bt_free;		/* free pg list for big data */
	CURSOR		bt_cursor;		/* cursor for scans */
	BTSTACK		*bt_stack;		/* parent stack for inserts */
	u_long		bt_lorder;		/* byte order (endian.h) */

#define BTF_METAOK	0x01	/* meta-data written to start of file */
#define BTF_SEQINIT	0x02	/* we have called bt_seq */
#define BTF_ISWRITE	0x04	/* tree was opened for write */
#define BTF_NODUPS	0x08	/* tree created for unique keys */

	u_long		bt_flags;		/* btree state */
} BTREEDATA_P;

typedef BTREEDATA_P	*BTREE_P;

E 3
/*
D 3
 *  The first thing in a btree file is a BTMETA structure.  The rest of
 *  the first page is empty, so that all disk operations are page-aligned.
E 3
I 3
 * A record in the tree is either a pointer to a page and an index in the page
 * or a page number and an index.  These structures are used as a cursor, stack
 * entry and search returns as well as to pass records to other routines.
 *
 * One comment about searches.  Internal page searches must find the largest
 * record less than key in the tree so that descents work.  Leaf page searches
 * must find the smallest record greater than key so that the returned index
 * is the record's correct position for insertion.
I 4
 *
 * One comment about cursors.  The cursor key is never removed from the tree,
 * even if deleted.  This is because it is quite difficult to decide where the
 * cursor should be when other keys have been inserted/deleted in the tree;
 * duplicate keys make it impossible.  This scheme does require extra work
 * though, to make sure that we don't perform an operation on a deleted key.
E 4
E 3
 */
I 3
D 17
typedef struct EPGNO {
E 17
I 17
typedef struct _epgno {
E 17
	pgno_t	pgno;			/* the page number */
D 10
	index_t	index;			/* the index on the page */
E 10
I 10
	indx_t	index;			/* the index on the page */
E 10
} EPGNO;
E 3

D 3
typedef struct BTMETA {
	u_long	m_magic;
	u_long	m_version;
	size_t	m_psize;
	pgno_t	m_free;
	u_long	m_flags;
	u_long	m_lorder;
} BTMETA;
E 3
I 3
D 17
typedef struct EPG {
E 17
I 17
typedef struct _epg {
E 17
	PAGE	*page;			/* the (pinned) page */
D 10
	index_t	 index;			/* the index on the page */
E 10
I 10
	indx_t	 index;			/* the index on the page */
E 10
} EPG;
E 3

I 4
/*
 * The metadata of the tree.  The m_nrecs field is used only by the RECNO code.
 * This is because the btree doesn't really need it and it requires that every
 * put or delete call modify the metadata.
 */
D 17
typedef struct BTMETA {
E 17
I 17
typedef struct _btmeta {
E 17
D 20
	u_long	m_magic;		/* magic number */
	u_long	m_version;		/* version */
	u_long	m_psize;		/* page size */
	u_long	m_free;			/* page number of first free page */
	u_long	m_nrecs;		/* R: number of records */
E 20
I 20
	u_int32_t	m_magic;	/* magic number */
	u_int32_t	m_version;	/* version */
	u_int32_t	m_psize;	/* page size */
	u_int32_t	m_free;		/* page number of first free page */
	u_int32_t	m_nrecs;	/* R: number of records */
E 20
D 14
#define	SAVEMETA	(BTF_NODUPS | BTF_RECNO)
E 14
I 14
#define	SAVEMETA	(B_NODUPS | R_RECNO)
E 14
D 20
	u_long	m_flags;		/* bt_flags & SAVEMETA */
D 13
	u_long	m_lorder;		/* byte order */
E 13
I 13
	u_long	m_unused;		/* unused */
E 20
I 20
	u_int32_t	m_flags;	/* bt_flags & SAVEMETA */
	u_int32_t	m_unused;	/* unused */
E 20
E 13
} BTMETA;

E 4
D 3
#define P_NONE		0		/* invalid page number in tree */
#define P_ROOT		1		/* page number of root pg in btree */
E 3
I 3
/* The in-memory btree/recno data structure. */
D 17
typedef struct BTREE {
E 17
I 17
typedef struct _btree {
E 17
	MPOOL	*bt_mp;			/* memory pool cookie */
E 3

D 3
#define NORELEASE	0		/* don't release a page during write */
#define RELEASE		1		/* release a page during write */
E 3
I 3
	DB	*bt_dbp;		/* pointer to enclosing DB */
E 3

I 18
	EPG	bt_cur;			/* current (pinned) page */
E 18
I 17
	PAGE	*bt_pinned;		/* page pinned across calls */

E 17
D 3
#define INSERT		0		/* doing an insert operation */
#define DELETE		1		/* doing a delete operation */
E 3
I 3
D 4
	EPGNO	bt_bcursor;		/* btree cursor */
	recno_t	bt_rcursor;		/* R: recno cursor */
E 4
I 4
	EPGNO	bt_bcursor;		/* B: btree cursor */
	recno_t	bt_rcursor;		/* R: recno cursor (1-based) */
E 4
E 3

D 3
/* get the next free index on a btree page */
#define NEXTINDEX(p)	((((int)(p)->h_lower) - ((int)((((char *)(&(p)->h_linp[0]))) - ((char *) (p)))))/(sizeof(index_t)))
E 3
I 3
#define	BT_POP(t)	(t->bt_sp ? t->bt_stack + --t->bt_sp : NULL)
#define	BT_CLR(t)	(t->bt_sp = 0)
	EPGNO	*bt_stack;		/* stack of parent pages */
	u_int	bt_sp;			/* current stack pointer */
	u_int	bt_maxstack;		/* largest stack */
E 3

D 3
/* is a BTITEM actually on the btree page? */
#define VALIDITEM(t, i)	((i)->bti_index < NEXTINDEX((t)->bt_curpage))
E 3
I 3
	char	*bt_kbuf;		/* key buffer */
	size_t	bt_kbufsz;		/* key buffer size */
	char	*bt_dbuf;		/* data buffer */
	size_t	bt_dbufsz;		/* data buffer size */
E 3

D 3
/* guarantee longword alignment so structure refs work */
#define LONGALIGN(p) (((long)(p) + 3) & ~ 0x03)
E 3
I 3
	int	bt_fd;			/* tree file descriptor */
D 12
	FILE	*bt_rfp;		/* R: record FILE pointer */
	int	bt_rfd;			/* R: record file descriptor */
E 12
E 3

D 3
/* get a particular datum (or idatum) off a page */
#define GETDATUM(h,i)	 (((char *) h) + h->h_linp[i])
E 3
I 3
D 4
	pgno_t	bt_free;		/* next free page */
	size_t	bt_psize;		/* page size */
	int	bt_maxkeypage;		/* maximum keys per page */
	size_t	bt_minkeypage;		/* minimum keys per page */
E 4
I 4
D 8
	pgno_t	bt_free;		/* XXX next free page */
E 8
I 8
	pgno_t	bt_free;		/* next free page */
E 8
D 10
	index_t	bt_psize;		/* page size */
	index_t	bt_ovflsize;		/* cut-off for key/data overflow */
E 10
I 10
D 15
	indx_t	bt_psize;		/* page size */
E 15
I 15
D 20
	u_long	bt_psize;		/* page size */
E 20
I 20
	u_int32_t bt_psize;		/* page size */
E 20
E 15
	indx_t	bt_ovflsize;		/* cut-off for key/data overflow */
E 10
E 4
	int	bt_lorder;		/* byte order */
E 3
D 4

E 4
D 3
/* is a {key,datum} too big to put on a single page? */
#define TOOBIG(t, sz)	(sz >= t->bt_psize / 5)
E 3
I 3
					/* sorted order */
D 19
	enum { NOT, BACK, FORWARD, } bt_order;
E 19
I 19
	enum { NOT, BACK, FORWARD } bt_order;
E 19
	EPGNO	bt_last;		/* last insert */
E 3

D 3
/* is this a disk tree or a memory tree? */
#define ISDISK(t)	(t->bt_fname != (char *) NULL)
E 3
I 3
					/* B: key comparison function */
	int	(*bt_cmp) __P((const DBT *, const DBT *));
					/* B: prefix comparison function */
D 20
	int	(*bt_pfx) __P((const DBT *, const DBT *));
E 20
I 20
	size_t	(*bt_pfx) __P((const DBT *, const DBT *));
E 20
E 3
D 4

E 4
D 3
/* does the disk tree use a cache? */
#define ISCACHE(t)	(t->bt_s.bt_d.d_cache != (char *) NULL)
E 3
I 3
					/* R: recno input function */
D 17
	int	(*bt_irec) __P((struct BTREE *, recno_t));
E 17
I 17
	int	(*bt_irec) __P((struct _btree *, recno_t));
E 17
D 4
	recno_t	bt_nrecs;		/* R: number of records in the tree */
E 4
I 4
D 12
	recno_t	bt_nrecs;		/* R: number of records */
E 12
I 12

	FILE	*bt_rfp;		/* R: record FILE pointer */
	int	bt_rfd;			/* R: record file descriptor */

	caddr_t	bt_cmap;		/* R: current point in mapped space */
E 12
E 4
	caddr_t	bt_smap;		/* R: start of mapped space */
	caddr_t bt_emap;		/* R: end of mapped space */
I 12
	size_t	bt_msize;		/* R: size of mapped region. */

	recno_t	bt_nrecs;		/* R: number of records */
E 12
	size_t	bt_reclen;		/* R: fixed record length */
I 7
D 12
	int	bt_reof;		/* R: end of input file reached. */
E 12
E 7
	u_char	bt_bval;		/* R: delimiting byte/pad character */
E 3

I 13
/*
 * NB:
D 14
 * BTF_NODUPS and BTF_RECNO are stored on disk, and may not be changed.
E 14
I 14
 * B_NODUPS and R_RECNO are stored on disk, and may not be changed.
E 14
 */
E 13
D 3
/*
 *  DATUMs are for user data -- one appears on leaf pages for every
 *  tree entry.  The d_bytes[] array contains the key first, then the data.
 *
 *  If either the key or the datum is too big to store on a single page,
 *  a bit is set in the flags entry, and the d_bytes[] array contains a
 *  pgno pointing to the page at which the data is actually stored.
 *
 *  Note on alignment:  every DATUM is guaranteed to be longword aligned
 *  on the disk page.  In order to force longword alignment of user key
 *  and data values, we must guarantee that the d_bytes[] array starts
 *  on a longword boundary.  This is the reason that d_flags is a u_long,
 *  rather than a u_char (it really only needs to be two bits big).  This
 *  is necessary because we call the user's comparison function with a
 *  pointer to the start of the d_bytes array.  We don't need to force
 *  longword alignment of the data following the key, since that is copied
 *  to a longword-aligned buffer before being returned to the user.
 */
E 3
I 3
D 4
#define	BTF_DELCRSR	0x001		/* B: delete cursor when closes/moves */
E 4
I 4
D 12
#define	BTF_DELCRSR	0x001		/* cursor has been deleted */
E 4
D 9
#define	BTF_FIXEDLEN	0x002		/* fixed length records */
#define	BTF_INMEM	0x004		/* in-memory tree */
E 9
I 9
#define	BTF_FIXEDLEN	0x002		/* R: fixed length records */
#define	BTF_INMEM	0x004		/* B: in-memory tree */
E 9
D 4
#define	BTF_METADIRTY	0x008		/* B: need to write meta-data */
E 4
I 4
#define	BTF_METADIRTY	0x008		/* B: need to write metadata */
E 4
#define	BTF_MODIFIED	0x010		/* tree modified */
D 4
#define	BTF_NODUPS	0x020		/* no duplicate keys permitted */
E 4
I 4
#define	BTF_NODUPS	0x020		/* B: no duplicate keys permitted */
E 4
#define	BTF_RDONLY	0x040		/* read-only tree */
D 9
#define	BTF_RECNO	0x080		/* record oriented tree */
#define	BTF_SEQINIT	0x100		/* sequential scan initialized */
E 9
I 9
#define	BTF_RECNO	0x080		/* R: record oriented tree */
#define	BTF_RINMEM	0x100		/* R: in-memory tree */
#define	BTF_SEQINIT	0x200		/* sequential scan initialized */
E 12
I 12
D 14
#define	BTF_CLOSEFP	0x0001		/* R: opened a file pointer */
#define	BTF_DELCRSR	0x0002		/* cursor has been deleted */
#define	BTF_EOF		0x0004		/* R: end of input file reached. */
#define	BTF_FIXEDLEN	0x0008		/* R: fixed length records */
#define	BTF_INMEM	0x0010		/* B: in-memory tree */
D 13
#define	BTF_MEMMAPPED	0x0020		/* R: memory mapped file. */
#define	BTF_METADIRTY	0x0040		/* B: need to write metadata */
#define	BTF_MODIFIED	0x0080		/* tree modified */
#define	BTF_NODUPS	0x0100		/* B: no duplicate keys permitted */
#define	BTF_RDONLY	0x0200		/* read-only tree */
#define	BTF_RECNO	0x0400		/* R: record oriented tree */
#define	BTF_RINMEM	0x0800		/* R: in-memory tree */
#define	BTF_SEQINIT	0x1000		/* sequential scan initialized */
E 13
I 13
#define	BTF_NODUPS	0x0020		/* B: no duplicate keys permitted */
#define	BTF_MEMMAPPED	0x0040		/* R: memory mapped file. */
#define	BTF_RECNO	0x0080		/* R: record oriented tree */
#define	BTF_METADIRTY	0x0100		/* B: need to write metadata */
#define	BTF_MODIFIED	0x0200		/* tree modified */
#define	BTF_NEEDSWAP	0x0400		/* if byte order requires swapping */
#define	BTF_RDONLY	0x0800		/* read-only tree */
#define	BTF_RINMEM	0x1000		/* R: in-memory tree */
#define	BTF_SEQINIT	0x2000		/* sequential scan initialized */
E 14
I 14
#define	B_DELCRSR	0x00001		/* cursor has been deleted */
#define	B_INMEM		0x00002		/* in-memory tree */
#define	B_METADIRTY	0x00004		/* need to write metadata */
#define	B_MODIFIED	0x00008		/* tree modified */
#define	B_NEEDSWAP	0x00010		/* if byte order requires swapping */
#define	B_NODUPS	0x00020		/* no duplicate keys permitted */
#define	B_RDONLY	0x00040		/* read-only tree */
I 17
#define	R_RECNO		0x00080		/* record oriented tree */
E 17
#define	B_SEQINIT	0x00100		/* sequential scan initialized */

#define	R_CLOSEFP	0x00200		/* opened a file pointer */
#define	R_EOF		0x00400		/* end of input file reached. */
#define	R_FIXLEN	0x00800		/* fixed length records */
#define	R_MEMMAPPED	0x01000		/* memory mapped file. */
D 17
#define	R_RECNO		0x00080		/* record oriented tree */
E 17
#define	R_INMEM		0x02000		/* in-memory file */
#define	R_MODIFIED	0x04000		/* modified file */
#define	R_RDONLY	0x08000		/* read-only file */
I 17

#define	B_DB_LOCK	0x10000		/* DB_LOCK specified. */
#define	B_DB_SHMEM	0x20000		/* DB_SHMEM specified. */
#define	B_DB_TXN	0x40000		/* DB_TXN specified. */
E 17
E 14

E 13
E 12
E 9
D 20
	u_long		bt_flags;	/* btree state */
E 20
I 20
	u_int32_t	bt_flags;	/* btree state */
E 20
} BTREE;
E 3

D 3
typedef struct DATUM {
	size_t d_ksize;		/* size of key */
	size_t d_dsize;		/* size of data */
E 3
I 3
D 9
#define	ISSET(t, f)	((t)->bt_flags & (f))
#define	NOTSET(t, f)	(!((t)->bt_flags & (f)))
E 9
#define	SET(t, f)	((t)->bt_flags |= (f))
D 9
#define	UNSET(t, f)	((t)->bt_flags &= ~(f))
E 9
I 9
#define	CLR(t, f)	((t)->bt_flags &= ~(f))
#define	ISSET(t, f)	((t)->bt_flags & (f))
E 9
E 3

D 3
#define D_BIGDATA	0x01	/* indirect datum ptr flag */
#define D_BIGKEY	0x02	/* indirect key ptr flag */

	u_long d_flags;		/* flags (indirect bit) */
	char d_bytes[1];	/* VARIABLE LENGTH DATA AT END OF STRUCT */
} DATUM;

/* BTITEMs are used to return (page, index, datum) tuples from searches */
typedef struct BTITEM {
	pgno_t bti_pgno;
	index_t bti_index;
	DATUM *bti_datum;
} BTITEM;

/*
 *  IDATUMs are for data stored on internal pages.  This is the (key, pgno)
 *  pair, such that key 'key' is the first entry on page 'pgno'.  If our
 *  internal page contains keys (a) and (b) next to each other, then all
 *  items >= to (a) and < (b) go on the same page as (a).  There are some
 *  gotchas with duplicate keys, however.  See the split code for details.
 *
 *  If a key is too big to fit on a single page, then the i_bytes[] array
 *  contains a pgno pointing to the start of a chain that actually stores
 *  the bytes.  Since items on internal pages are never deleted from the
 *  tree, these indirect chains are marked as special, so that they won't
 *  be deleted if the corresponding leaf item is deleted.
 *
 *  As for DATUMs, IDATUMs have a u_long flag entry (rather than u_char)
 *  in order to guarantee that user keys are longword aligned on the disk
 *  page.
 */

typedef struct IDATUM {
	size_t i_size;
	pgno_t i_pgno;
	u_long i_flags;		/* see DATUM.d_flags, above */
	char i_bytes[1];	/* VARIABLE LENGTH DATA AT END OF STRUCT */
} IDATUM;

/* all private interfaces have a leading _ in their names */
extern BTITEM	*_bt_search();
extern BTITEM	*_bt_searchr();
extern BTHEADER	*_bt_allocpg();
extern index_t	_bt_binsrch();
extern int	_bt_isonpage();
extern BTITEM	*_bt_first();
extern int	_bt_release();
extern int	_bt_wrtmeta();
extern int	_bt_delindir();
extern int	_bt_pgout();
extern int	_bt_pgin();
extern int	_bt_fixscan();
extern int	_bt_indirect();
extern int	_bt_crsrdel();
extern int	_bt_push();
extern pgno_t	_bt_pop();
extern int	strcmp();

E 3
I 3
#include "extern.h"
E 3
E 1
