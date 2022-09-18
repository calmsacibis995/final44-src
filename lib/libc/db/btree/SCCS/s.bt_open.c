h14161
s 00002/00002/00412
d D 8.5 94/02/21 17:43:16 bostic 37 36
c cast alloc's to shut SunOS up
e
s 00010/00010/00404
d D 8.4 94/02/21 15:08:12 bostic 36 35
c first pass at making DB use basic integral types (the Alpha port)
e
s 00006/00008/00408
d D 8.3 93/09/16 16:42:03 bostic 35 34
c clear the DB structure (bt_pinned wasn't initialized)
e
s 00018/00004/00398
d D 8.2 93/09/07 11:48:54 bostic 34 33
c add DB_ flags to __bt_open
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00400
d D 8.1 93/06/04 15:20:29 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00000/00386
d D 5.31 93/05/24 08:56:12 bostic 32 31
c add in __bt_fd, to return a file descriptor
e
s 00004/00004/00382
d D 5.30 93/05/22 14:11:40 bostic 31 30
c support 64K pages
e
s 00008/00008/00378
d D 5.29 93/05/16 15:41:38 bostic 30 29
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00001/00001/00385
d D 5.28 93/05/07 10:34:24 bostic 29 28
c type mismatch
e
s 00041/00014/00345
d D 5.27 93/05/01 15:37:09 bostic 28 27
c recognize different byte orders automatically; m_lorder no longer used
e
s 00001/00001/00358
d D 5.26 93/02/16 12:33:43 bostic 27 26
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00006/00006/00353
d D 5.25 93/02/14 17:39:19 bostic 26 25
c index -> indx_t
e
s 00002/00002/00357
d D 5.24 93/02/11 11:39:22 bostic 25 24
c move db.h to the end of the includes, make compat.h work better
e
s 00002/00003/00357
d D 5.23 92/11/18 15:06:36 bostic 24 23
c use __USE_OPEN_FLAGS macro from db.h
e
s 00011/00007/00349
d D 5.22 92/11/13 16:03:18 bostic 23 22
c use SET/ISSET, lint
e
s 00014/00003/00342
d D 5.21 92/10/04 16:48:31 bostic 22 21
c don't permit O_WRONLY
e
s 00001/00000/00344
d D 5.20 92/09/02 10:15:43 bostic 21 19
c initialize cachesize if openinfo not specified
e
s 00003/00002/00342
d R 5.20 92/09/02 10:13:05 bostic 20 19
c initialize cachesize if openinfo not specified
e
s 00001/00001/00343
d D 5.19 92/08/31 09:09:36 bostic 19 18
c typo, F_SETFL -> F_SETFD
e
s 00003/00001/00341
d D 5.18 92/07/17 09:52:01 bostic 18 17
c lint
e
s 00002/00001/00340
d D 5.17 92/05/15 16:19:08 bostic 17 16
c add O_EXLOCK and O_SHLOCK to open flags
e
s 00001/00001/00340
d D 5.16 91/12/16 14:01:57 bostic 16 15
c don't bother with the macros, performance isn't an issue here
e
s 00001/00001/00340
d D 5.15 91/12/09 15:26:59 bostic 15 14
c programmer head space error
e
s 00001/00000/00340
d D 5.14 91/11/22 18:11:54 bostic 14 13
c initialize bt_flags field, bozo
e
s 00004/00003/00336
d D 5.13 91/10/27 16:10:16 bostic 13 12
c initialize page size so recognize when the user doesn't!
e
s 00001/00001/00338
d D 5.12 91/10/10 19:20:41 bostic 12 11
c typo on meta bit checking
e
s 00026/00025/00313
d D 5.11 91/09/12 11:05:40 bostic 11 10
c remove maxkeypage, fix minkeypage and rename to bt_ovflsize; fix flags
c bugs, filter bugs, zero out the meta page
e
s 00251/00639/00087
d D 5.10 91/09/04 12:47:10 bostic 10 9
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00034/00028/00692
d D 5.9 91/05/07 10:00:26 bostic 9 8
c change calling convention -- needs to take a DB, not DB->internal
e
s 00001/00000/00719
d D 5.8 91/04/02 08:43:15 bostic 8 7
c add DB.type field to reflect type of underlying database
e
s 00002/00002/00717
d D 5.7 91/03/03 14:33:18 bostic 7 6
c DBT data changed to be unsigned
e
s 00004/00004/00715
d D 5.6 91/02/23 09:23:52 bostic 6 5
c make flags right
e
s 00009/00007/00710
d D 5.5 91/02/22 17:16:32 bostic 5 4
c ANSI prototypes
e
s 00018/00007/00699
d D 5.4 91/02/18 22:48:32 mao 4 3
c fix stack management bug
e
s 00038/03312/00668
d D 5.3 91/01/23 08:10:44 mao 3 2
c split up modules into smaller files
e
s 00006/00012/03974
d D 5.2 91/01/08 17:05:26 bostic 2 1
c errno is defined in <sys/errno.h; BTREEMAGIC/BTREEVERSION are in <db.h>
e
s 03986/00000/00000
d D 5.1 91/01/07 12:41:16 bostic 1 0
c date and time created 91/01/07 12:41:16 by bostic
e
u
U
t
T
I 1
/*-
D 33
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 33
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

/*
D 10
 *  btree.c -- implementation of btree access method for 4.4BSD.
E 10
I 10
 * Implementation of btree access method for 4.4BSD.
E 10
 *
D 10
 *	The design here is based on that of the btree access method used
 *	in the Postgres database system at UC Berkeley.  The implementation
 *	is wholly independent of the Postgres code.
 *
 *	This implementation supports btrees on disk (supply a filename) or
 *	in memory (don't).  Public interfaces defined here are:
 *
 *		btree_open()	-- wrapper; returns a filled DB struct for
 *				   a btree.
 *
 *		bt_open()	-- open a new or existing btree.
 *		bt_get()	-- fetch data from a tree by key.
 *		bt_seq()	-- do a sequential scan on a tree.
 *		bt_put()	-- add data to a tree by key.
 *		bt_delete()	-- remove data from a tree by key.
 *		bt_close()	-- close a btree.
 *		bt_sync()	-- force btree pages to disk (disk trees only).
E 10
I 10
 * The design here was originally based on that of the btree access method
 * used in the Postgres database system at UC Berkeley.  This implementation
 * is wholly independent of the Postgres code.
E 10
 */

#include <sys/param.h>
D 5
#include <sys/file.h>
E 5
#include <sys/stat.h>
I 18

D 23
#include <signal.h>
E 18
D 5
#include <sys/signal.h>
#include <sys/errno.h>
I 3
#include <sys/types.h>
E 5
I 5
D 10
#include <signal.h>
#include <errno.h>
E 10
#include <fcntl.h>
I 10
#include <errno.h>
#include <limits.h>
E 23
D 25
#define	__DBINTERFACE_PRIVATE
E 10
E 5
E 3
#include <db.h>
E 25
I 23
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
E 23
I 5
D 10
#include <stdlib.h>
#include <string.h>
E 10
I 10
#include <stdio.h>
E 10
D 23
#include <unistd.h>
E 23
I 10
#include <stdlib.h>
I 11
#include <string.h>
I 23
#include <unistd.h>

I 25
D 36
#define	__DBINTERFACE_PRIVATE
E 36
#include <db.h>
E 25
E 23
E 11
E 10
E 5
I 3
#include "btree.h"
E 3

I 28
static int byteorder __P((void));
E 28
D 3
#ifndef BLSWAP
#define BLSWAP(a) { \
        register unsigned long _t; \
        _t = (a); \
        (a) >>= 24; \
        (a) |= (_t & 0x00ff0000) >>  8; \
        (a) |= (_t & 0x0000ff00) <<  8; \
        (a) |= (_t & 0x000000ff) << 24; \
}
#endif /* ndef BLSWAP */

typedef char	*BTREE;		/* should really be (void *) */ 

/* #define	DEBUG */

#define RET_ERROR	-1
#define RET_SUCCESS	 0
#define RET_SPECIAL	 1

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif /* ndef TRUE */

D 2
extern int errno;

E 2
/* libc */
extern char *malloc();

/* these are defined in lrucache.c */
extern char	*lruinit();
extern char	*lruget();
extern char	*lrugetnew();
extern int	lrusync();
extern int	lruwrite();
extern int	lrurelease();
extern void	lrufree();

/* these are defined here */
BTREE	bt_open();
int	bt_close();
int	bt_delete();
int	bt_get();
int	bt_put();
int	bt_seq();
int	bt_sync();

/*
 *  Private types.  What you choose for these depends on how big you
 *  want to let files get, and how big you want to let pages get.
 */

typedef u_long	index_t;	/* so # bytes on a page fits in a long */
typedef u_long	pgno_t;		/* so # of pages in a btree fits in a long */

/*
 *  When we do searches, we push the parent page numbers onto a stack
 *  as we descend the tree.  This is so that for insertions, we can
 *  find our way back up to do internal page insertions and splits.
 */

typedef struct BTSTACK {
	pgno_t		bts_pgno;
	struct BTSTACK	*bts_next;
} BTSTACK;

/*
 *  Every btree page has a header that looks like this.  Flags are given
 *  in the #define's for the F_ flags (see below).
 */

typedef struct BTHEADER {
	pgno_t h_pgno;		/* page number of this page */
	pgno_t h_prevpg;	/* left sibling */
	pgno_t h_nextpg;	/* right sibling */

#define F_LEAF		0x01	/* leaf page, contains user data */
#define F_CONT		0x02	/* continuation page (large items) */
#define F_DIRTY		0x04	/* need to write to disk */
#define F_PRESERVE	0x08	/* never delete this chain of pages */

	u_long h_flags;		/* page state */
	index_t h_lower;	/* lower bound of free space on page */
	index_t h_upper;	/* upper bound of free space on page */
	index_t h_linp[1];	/* VARIABLE LENGTH DATA AT END OF STRUCT */
} BTHEADER;

/*
 *  HTBUCKETs are hash table buckets for looking up pages of in-memory
 *  btrees by page number.  We use this indirection, rather than direct
 *  pointers, so that the code for manipulating in-memory trees is the
 *  same as that for manipulating on-disk trees.
 */

typedef struct HTBUCKET {
	pgno_t		ht_pgno;
	BTHEADER	*ht_page;
	struct HTBUCKET	*ht_next;
} HTBUCKET;

typedef HTBUCKET	**HTABLE;

/* minimum size we'll let a page be */
#define MINPSIZE	512

/* default cache size, in bytes */
#define DEFCACHE	(20 * 1024)

/* hash table size for in-memory trees */
#define	HTSIZE		128

/* generate a hash key from a page number */
#define HASHKEY(pgno)	((pgno - 1) % HTSIZE)

/*
 *  Disk btrees have a file descriptor, and may also have an lru buffer
 *  cache, if the user asked for one.
 */

typedef struct BTDISK {
	int	d_fd;
	char	*d_cache;
} BTDISK;

/*
 *  Cursors keep track of the current location in a sequential scan of
 *  the database.  Since btrees impose a total ordering on keys, we can
 *  walk forward or backward through the database from any point.  Cursors
 *  survive updates to the tree, and can be used to delete a particular
 *  record.
 */

typedef struct CURSOR {
	pgno_t		c_pgno;		/* pgno of current item in scan */
	index_t		c_index;	/* index of current item in scan */
	char		*c_key;		/* current key, used for updates */

#define CRSR_BEFORE	0x01

	u_char		c_flags;	/* to handle updates properly */
} CURSOR;

/*
 *  The private btree data structure.  The user passes a pointer to one of
 *  these when we are to manipulate a tree, but the BTREE type is opaque
 *  to him.
 */

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

/*
 *  The first thing in a btree file is a BTMETA structure.  The rest of
 *  the first page is empty, so that all disk operations are page-aligned.
 */

typedef struct BTMETA {
	u_long	m_magic;
	u_long	m_version;
	size_t	m_psize;
	pgno_t	m_free;
	u_long	m_flags;
	u_long	m_lorder;
} BTMETA;

#define P_NONE		0		/* invalid page number in tree */
#define P_ROOT		1		/* page number of root pg in btree */

#define NORELEASE	0		/* don't release a page during write */
#define RELEASE		1		/* release a page during write */

#define INSERT		0		/* doing an insert operation */
#define DELETE		1		/* doing a delete operation */

D 2
/* magic number for identifying btree files */
#define BTREEMAGIC	053162L		/* magic */
#define BTREEVERSION	2		/* last changed 6 jan 1991 */

E 2
/* get the next free index on a btree page */
#define NEXTINDEX(p)	((((int)(p)->h_lower) - ((int)((((char *)(&(p)->h_linp[0]))) - ((char *) (p)))))/(sizeof(index_t)))

/* is a BTITEM actually on the btree page? */
#define VALIDITEM(t, i)	((i)->bti_index < NEXTINDEX((t)->bt_curpage))

/* guarantee longword alignment so structure refs work */
#define LONGALIGN(p) (((long)(p) + 3) & ~ 0x03)

/* get a particular datum (or idatum) off a page */
#define GETDATUM(h,i)	 (((char *) h) + h->h_linp[i])

/* is a {key,datum} too big to put on a single page? */
#define TOOBIG(t, sz)	(sz >= t->bt_psize / 5)

/* is this a disk tree or a memory tree? */
#define ISDISK(t)	(t->bt_fname != (char *) NULL)

/* does the disk tree use a cache? */
#define ISCACHE(t)	(t->bt_s.bt_d.d_cache != (char *) NULL)

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

typedef struct DATUM {
	size_t d_ksize;		/* size of key */
	size_t d_dsize;		/* size of data */

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
static BTITEM	*_bt_search();
static BTITEM	*_bt_searchr();
static BTHEADER	*_bt_allocpg();
static index_t	_bt_binsrch();
static int	_bt_isonpage();
static BTITEM	*_bt_first();
static int	_bt_release();
static int	_bt_wrtmeta();
static int	_bt_delindir();
static int	_bt_pgout();
static int	_bt_pgin();
static int	_bt_fixscan();
static int	_bt_indirect();
static int	_bt_crsrdel();

extern int strcmp();

static BTREEINFO _DefaultBTInfo = {
E 3
I 3
D 10
BTREEINFO _DefaultBTInfo = {
E 3
	0,	/* flags */
	0,	/* cachesize */
	0,	/* psize */
	strcmp,	/* compare */
	0
};
E 10
I 10
static int nroot __P((BTREE *));
static int tmp __P((void));
E 10

/*
D 10
 *  BTREE_OPEN -- Wrapper routine to open a btree.
E 10
I 10
 * __BT_OPEN -- Open a btree.
E 10
 *
D 10
 *	Creates and fills a DB struct, and calls the routine that actually
 *	opens the btree.
E 10
I 10
 * Creates and fills a DB struct, and calls the routine that actually
 * opens the btree.
E 10
 *
D 10
 *	Parameters:
 *		f:  filename to open
 *		flags:  flag bits passed to open
 *		mode:  permission bits, used if O_CREAT specified
 *		b:  BTREEINFO pointer
E 10
I 10
 * Parameters:
 *	fname:	filename (NULL for in-memory trees)
 *	flags:	open flag bits
 *	mode:	open permission bits
 *	b:	BTREEINFO pointer
E 10
 *
D 10
 *	Returns:
 *		Filled-in DBT on success; NULL on failure, with errno
 *		set as appropriate.
E 10
I 10
 * Returns:
 *	NULL on failure, pointer to DB on success.
E 10
 *
D 10
 *	Side Effects:
 *		Allocates memory for the DB struct.
E 10
 */
D 10

E 10
DB *
D 10
btree_open(f, flags, mode, b)
D 5
	char *f;
E 5
I 5
	const char *f;
E 5
	int flags;
	int mode;
D 5
	BTREEINFO *b;
E 5
I 5
	const BTREEINFO *b;
E 10
I 10
D 34
__bt_open(fname, flags, mode, openinfo)
E 34
I 34
__bt_open(fname, flags, mode, openinfo, dflags)
E 34
	const char *fname;
D 34
	int flags, mode;
E 34
I 34
	int flags, mode, dflags;
E 34
	const BTREEINFO *openinfo;
E 10
E 5
{
I 36
	struct stat sb;
E 36
D 10
	DB *db;
	BTREE t;

	if ((db = (DB *) malloc((unsigned) sizeof(DB))) == (DB *) NULL)
		return ((DB *) NULL);

	if ((t = bt_open(f, flags, mode, b)) == (BTREE) NULL) {
		(void) free ((char *) db);
		return ((DB *) NULL);
	}

	db->internal = (char *) t;
	db->close = bt_close;
D 5
	db->delete = bt_delete;
E 5
I 5
	db->del = bt_delete;
E 5
	db->get = bt_get;
	db->put = bt_put;
	db->seq = bt_seq;
	db->sync = bt_sync;
I 8
	db->type = DB_BTREE;
E 8

	return (db);
}

/*
 *  BT_OPEN -- Open a btree.
 *
 *	This routine creates the correct kind (disk or in-memory) of
 *	btree and initializes it as required.
 *
 *	Parameters:
 *		f -- name of btree (NULL for in-memory btrees)
 *		flags -- flags passed to open()
 *		mode -- mode passed to open ()
 *		b -- BTREEINFO structure, describing btree
 *
 *	Returns:
 *		(Opaque) pointer to the btree.  On failure, returns NULL
 *		with errno set as appropriate.
 *
 *	Side Effects:
 *		Allocates memory, opens files.
 */

BTREE
bt_open(f, flags, mode, b)
	char *f;
	int flags;
	int mode;
	BTREEINFO *b;
{
	BTREE_P t;
	HTABLE ht;
	int nbytes;
	int fd;
	CURSOR *c;
E 10
I 10
D 11
	BTREE *t;
	DB *dbp;
E 11
E 10
	BTMETA m;
I 11
	BTREE *t;
E 11
D 10
	struct stat buf;
E 10
I 10
	BTREEINFO b;
I 11
	DB *dbp;
E 11
	pgno_t ncache;
D 36
	struct stat sb;
D 28
	int nr;
E 28
I 28
	int machine_lorder, nr;
E 36
I 36
	ssize_t nr;
	int machine_lorder;
E 36
E 28
E 10

I 23
	t = NULL;

E 23
D 10
	/* use the default info if none was provided */
	if (b == (BTREEINFO *) NULL)
		b = &_DefaultBTInfo;

	if ((t = (BTREE_P) malloc((unsigned) sizeof *t)) == (BTREE_P) NULL)
		return ((BTREE) NULL);

	if (b->compare)
		t->bt_compare = b->compare;
	else
		t->bt_compare = strcmp;

	t->bt_fname = f;
	t->bt_curpage = (BTHEADER *) NULL;
	t->bt_free = P_NONE;
	c = &(t->bt_cursor);
	c->c_pgno = P_NONE;
	c->c_index = 0;
	c->c_flags = (u_char) NULL;
	c->c_key = (char *) NULL;
	t->bt_stack = (BTSTACK *) NULL;
	t->bt_flags = 0;

E 10
	/*
D 10
	 *  If no file name was supplied, this is an in-memory btree.
	 *  Otherwise, it's a disk-based btree.
E 10
I 10
	 * Intention is to make sure all of the user's selections are okay
	 * here and then use them without checking.  Can't be complete, since
	 * we don't know the right page size, lorder or flags until the backing
	 * file is opened.  Also, the file's page size can cause the cachesize
	 * to change.
E 10
	 */
I 28
	machine_lorder = byteorder();
E 28
D 10
	if (f == (char *) NULL) {
		/* in memory */
		if ((t->bt_psize = b->psize) < MINPSIZE) {
			if (t->bt_psize != 0) {
				(void) free ((char *) t);
				errno = EINVAL;
				return ((BTREE) NULL);
			}
			t->bt_psize = getpagesize();
		}
E 10
I 10
	if (openinfo) {
		b = *openinfo;
E 10

D 10
		nbytes = HTSIZE * sizeof(HTBUCKET *);
		if ((ht = (HTABLE) malloc((unsigned) nbytes))
		    == (HTABLE) NULL) {
			(void) free((char *) t);
			return ((BTREE) NULL);
		}
		(void) bzero((char *) ht, nbytes);
		t->bt_s.bt_ht = ht;
		t->bt_npages = 0;
		t->bt_lorder = BYTE_ORDER;
		if (!(b->flags & R_DUP))
			t->bt_flags |= BTF_NODUPS;
	} else {
		/* on disk */
		if ((fd = open(f, O_RDONLY, 0)) < 0) {
			/* doesn't exist yet, be sure page is big enough */
			if ((t->bt_psize = b->psize) < sizeof(BTHEADER)
			    && b->psize != 0) {
				(void) free((char *) t);
				errno = EINVAL;
				return ((BTREE) NULL);
			}
			if (b->lorder == 0)
				b->lorder = BYTE_ORDER;
E 10
I 10
		/* Flags: R_DUP. */
D 11
		if (b.flags && b.flags != R_DUP)
E 11
I 11
		if (b.flags & ~(R_DUP))
E 11
			goto einval;
E 10

D 10
			if (b->lorder != BIG_ENDIAN
			    && b->lorder != LITTLE_ENDIAN) {
				(void) free((char *) t);
				errno = EINVAL;
				return ((BTREE) NULL);
			}
			t->bt_lorder = b->lorder;
			if (!(b->flags & R_DUP))
				t->bt_flags |= BTF_NODUPS;
		} else {
			/* exists, get page size from file */
			if (read(fd, &m, sizeof(m)) < sizeof(m)) {
				(void) close(fd);
				(void) free((char *) t);
				errno = EINVAL;
				return ((BTREE) NULL);
			}
E 10
I 10
		/*
D 26
		 * Page size must be index_t aligned and >= MINPSIZE.  Default
E 26
I 26
		 * Page size must be indx_t aligned and >= MINPSIZE.  Default
E 26
		 * page size is set farther on, based on the underlying file
		 * transfer size.
		 */
		if (b.psize &&
D 31
		    (b.psize < MINPSIZE || b.psize > MAX_PAGE_OFFSET ||
E 31
I 31
		    (b.psize < MINPSIZE || b.psize > MAX_PAGE_OFFSET + 1 ||
E 31
D 26
		    b.psize & sizeof(index_t) - 1))
E 26
I 26
		    b.psize & sizeof(indx_t) - 1))
E 26
D 13
				goto einval;
E 13
I 13
			goto einval;
E 13
D 11
#ifdef notdef
		if (b.maxkeypage && b.maxkeypage < 1) 
			goto einval;
E 11
E 10

I 11
		/* Minimum number of keys per page; absolute minimum is 2. */
E 11
D 10
			/* lorder always stored in host-independent format */
			NTOHL(m.m_lorder);
			if (m.m_lorder != BIG_ENDIAN
			    && m.m_lorder != LITTLE_ENDIAN) {
				(void) free((char *) t);
				errno = EINVAL;
				return ((BTREE) NULL);
			}
			t->bt_lorder = m.m_lorder;

			if (t->bt_lorder != BYTE_ORDER) {
				BLSWAP(m.m_magic);
				BLSWAP(m.m_version);
				BLSWAP(m.m_psize);
				BLSWAP(m.m_free);
				BLSWAP(m.m_flags);
			}

			if (m.m_magic != BTREEMAGIC
			    || m.m_version != BTREEVERSION
			    || m.m_psize < MINPSIZE) {
				(void) close(fd);
				(void) free((char *) t);
#ifndef EFTYPE
#define EFTYPE	-100
E 10
I 10
		if (b.minkeypage) {
			if (b.minkeypage < 2)
				goto einval;
		} else
D 11
			b.minkeypage = 2;
#else
		b.maxkeypage = DEFMAXKEYPAGE;
		b.minkeypage = DEFMINKEYPAGE;
E 10
#endif
D 10
				errno = EFTYPE;
				return ((BTREE) NULL);
			}
			t->bt_psize = m.m_psize;
			t->bt_free = m.m_free;
			t->bt_flags |= (m.m_flags & BTF_NODUPS) | BTF_METAOK;
			(void) close(fd);
E 10
I 10
		
E 11
I 11
			b.minkeypage = DEFMINKEYPAGE;

E 11
		/* If no comparison, use default comparison and prefix. */
		if (b.compare == NULL) {
			b.compare = __bt_defcmp;
			if (b.prefix == NULL)
				b.prefix = __bt_defpfx;
E 10
		}

D 10
		/* now open the file the way the user wanted it */
		if ((t->bt_s.bt_d.d_fd = open(f, flags, mode)) < 0) {
			(void) free ((char *) t);
			return ((BTREE) NULL);
		}
E 10
I 10
		if (b.lorder == 0)
D 28
			b.lorder = BYTE_ORDER;
		else if (b.lorder != BIG_ENDIAN && b.lorder != LITTLE_ENDIAN)
			goto einval;
E 28
I 28
			b.lorder = machine_lorder;
E 28
	} else {
I 13
		b.compare = __bt_defcmp;
I 21
		b.cachesize = 0;
E 21
E 13
		b.flags = 0;
I 13
D 28
		b.lorder = BYTE_ORDER;
E 28
I 28
		b.lorder = machine_lorder;
E 28
E 13
D 11
		b.maxkeypage = DEFMAXKEYPAGE;
E 11
		b.minkeypage = DEFMINKEYPAGE;
D 13
		b.compare = __bt_defcmp;
E 13
		b.prefix = __bt_defpfx;
D 13
		b.lorder = BYTE_ORDER;
E 13
I 13
		b.psize = 0;
E 13
	}
E 10

I 28
	/* Check for the ubiquitous PDP-11. */
	if (b.lorder != BIG_ENDIAN && b.lorder != LITTLE_ENDIAN)
		goto einval;

E 28
I 4
D 10
		/* access method files are always close-on-exec */
		if (fcntl(t->bt_s.bt_d.d_fd, F_SETFL, 1) == -1) {
			(void) close(t->bt_s.bt_d.d_fd);
			(void) free ((char *) t);
			return ((BTREE) NULL);
		}
E 10
I 10
	/* Allocate and initialize DB and BTREE structures. */
D 37
	if ((t = malloc(sizeof(BTREE))) == NULL)
E 37
I 37
	if ((t = (BTREE *)malloc(sizeof(BTREE))) == NULL)
E 37
		goto err;
D 35
	t->bt_fd = -1;			/* Don't close unopened fd on error. */
	if ((t->bt_dbp = dbp = malloc(sizeof(DB))) == NULL)
		goto err;
E 35
I 35
	memset(t, 0, sizeof(BTREE));
E 35
	t->bt_bcursor.pgno = P_INVALID;
D 35
	t->bt_bcursor.index = 0;
	t->bt_stack = NULL;
	t->bt_sp = t->bt_maxstack = 0;
	t->bt_kbuf = t->bt_dbuf = NULL;
	t->bt_kbufsz = t->bt_dbufsz = 0;
E 35
I 35
	t->bt_fd = -1;			/* Don't close unopened fd on error. */
E 35
I 28
	t->bt_lorder = b.lorder;
E 28
D 11
	t->bt_maxkeypage = b.maxkeypage;
	t->bt_minkeypage = b.minkeypage;
E 11
	t->bt_order = NOT;
	t->bt_cmp = b.compare;
	t->bt_pfx = b.prefix;
I 35
	t->bt_rfd = -1;

D 37
	if ((t->bt_dbp = dbp = malloc(sizeof(DB))) == NULL)
E 37
I 37
	if ((t->bt_dbp = dbp = (DB *)malloc(sizeof(DB))) == NULL)
E 37
		goto err;
E 35
I 14
	t->bt_flags = 0;
I 28
	if (t->bt_lorder != machine_lorder)
D 30
		SET(t, BTF_NEEDSWAP);
E 30
I 30
		SET(t, B_NEEDSWAP);
E 30
E 28
E 14
E 10

E 4
D 10
		/* get number of pages, page size if necessary */
		(void) fstat(t->bt_s.bt_d.d_fd, &buf);
		if (t->bt_psize == 0)
			t->bt_psize = buf.st_blksize;
		t->bt_npages = (pgno_t) (buf.st_size / t->bt_psize);
E 10
I 10
	dbp->type = DB_BTREE;
	dbp->internal = t;
	dbp->close = __bt_close;
	dbp->del = __bt_delete;
I 32
	dbp->fd = __bt_fd;
E 32
	dbp->get = __bt_get;
	dbp->put = __bt_put;
	dbp->seq = __bt_seq;
	dbp->sync = __bt_sync;
E 10

D 10
		/* page zero is metadata, doesn't count */
		if (t->bt_npages > 0)
			--(t->bt_npages);
E 10
I 10
	/*
	 * If no file name was supplied, this is an in-memory btree and we
	 * open a backing temporary file.  Otherwise, it's a disk-based tree.
	 */
	if (fname) {
I 22
		switch(flags & O_ACCMODE) {
		case O_RDONLY:
D 30
			SET(t, BTF_RDONLY);
E 30
I 30
			SET(t, B_RDONLY);
E 30
			break;
		case O_RDWR:
			break;
		case O_WRONLY:
		default:
			goto einval;
		}
		
E 22
D 17
#define	USEFLAGS	(O_CREAT|O_EXCL|O_RDONLY|O_RDWR|O_TRUNC|O_WRONLY)
E 17
I 17
D 24
#define	USEFLAGS \
D 22
	(O_CREAT|O_EXCL|O_EXLOCK|O_RDONLY|O_RDWR|O_SHLOCK|O_TRUNC|O_WRONLY)
E 22
I 22
	(O_CREAT|O_EXCL|O_EXLOCK|O_RDONLY|O_RDWR|O_SHLOCK|O_TRUNC)
E 22
E 17
		if ((t->bt_fd = open(fname, flags & USEFLAGS, mode)) < 0)
E 24
I 24
D 34
		if ((t->bt_fd =
		    open(fname, flags & __USE_OPEN_FLAGS, mode)) < 0)
E 34
I 34
		if ((t->bt_fd = open(fname, flags, mode)) < 0)
E 34
E 24
			goto err;
D 22
		if ((flags & O_ACCMODE) == O_RDONLY)
			SET(t, BTF_RDONLY);
E 22
E 10

D 10
		if (b->cachesize == 0)
			b->cachesize = DEFCACHE;
E 10
I 10
	} else {
I 22
		if ((flags & O_ACCMODE) != O_RDWR)
			goto einval;
E 22
		if ((t->bt_fd = tmp()) == -1)
			goto err;
D 30
		SET(t, BTF_INMEM);
E 30
I 30
		SET(t, B_INMEM);
E 30
	}
E 10

D 10
		/* get an lru buffer cache, if the user asked for one */
		if ((b->cachesize / t->bt_psize) > 0) {
			BTDISK *d = &(t->bt_s.bt_d);
E 10
I 10
D 19
	if (fcntl(t->bt_fd, F_SETFL, 1) == -1)
E 19
I 19
	if (fcntl(t->bt_fd, F_SETFD, 1) == -1)
E 19
		goto err;
E 10

D 10
			d->d_cache = lruinit(d->d_fd,
D 3
					     b->cachesize / t->bt_psize,
					     t->bt_psize,
E 3
I 3
					     (int) (b->cachesize / t->bt_psize),
					     (int) t->bt_psize,
E 3
					     (char *) t->bt_lorder,
					     _bt_pgin, _bt_pgout);
E 10
I 10
	if (fstat(t->bt_fd, &sb))
		goto err;
	if (sb.st_size) {
		nr = read(t->bt_fd, &m, sizeof(BTMETA));
		if (nr < 0)
			goto err;
		if (nr != sizeof(BTMETA))
			goto eftype;
E 10

D 10
			if (d->d_cache == (char *) NULL) {
				(void) free((char *) t);
				return ((BTREE) NULL);
			}
E 10
I 10
		/*
		 * Read in the meta-data.  This can change the notion of what
		 * the lorder, page size and flags are, and, when the page size
D 28
		 * changes the cachesize value can change as well.
		 *
		 * Lorder is always stored in host-independent format.
E 28
I 28
		 * changes, the cachesize value can change too.  If the user
		 * specified the wrong byte order for an existing database, we
		 * don't bother to return an error, we just clear the NEEDSWAP
		 * bit.
E 28
		 */
D 15
		NTOHL(m.m_lorder);
E 15
I 15
D 16
		m.m_lorder = NTOHL(m.m_lorder);
E 16
I 16
D 28
		m.m_lorder = ntohl(m.m_lorder);
E 16
E 15
		if (m.m_lorder != BIG_ENDIAN && m.m_lorder != LITTLE_ENDIAN)
			goto eftype;
		if (m.m_lorder != BYTE_ORDER) {
E 28
I 28
		if (m.m_magic == BTREEMAGIC)
D 30
			CLR(t, BTF_NEEDSWAP);
E 30
I 30
			CLR(t, B_NEEDSWAP);
E 30
		else {
D 30
			SET(t, BTF_NEEDSWAP);
E 30
I 30
			SET(t, B_NEEDSWAP);
E 30
E 28
D 36
			BLSWAP(m.m_magic);
			BLSWAP(m.m_version);
			BLSWAP(m.m_psize);
			BLSWAP(m.m_free);
			BLSWAP(m.m_nrecs);
			BLSWAP(m.m_flags);
E 36
I 36
			M_32_SWAP(m.m_magic);
			M_32_SWAP(m.m_version);
			M_32_SWAP(m.m_psize);
			M_32_SWAP(m.m_free);
			M_32_SWAP(m.m_nrecs);
			M_32_SWAP(m.m_flags);
E 36
E 10
		}
D 10
	}
E 10
I 10
		if (m.m_magic != BTREEMAGIC || m.m_version != BTREEVERSION)
			goto eftype;
D 31
		if (m.m_psize < MINPSIZE || m.m_psize > MAX_PAGE_OFFSET ||
E 31
I 31
		if (m.m_psize < MINPSIZE || m.m_psize > MAX_PAGE_OFFSET + 1 ||
E 31
D 26
		    m.m_psize & sizeof(index_t) - 1)
E 26
I 26
		    m.m_psize & sizeof(indx_t) - 1)
E 26
			goto eftype;
D 12
		if (m.m_flags | ~SAVEMETA)
E 12
I 12
		if (m.m_flags & ~SAVEMETA)
E 12
			goto eftype;
E 10
D 11

E 11
D 10
	/* remember if tree was opened for write */
	if (((flags & O_WRONLY) == O_WRONLY)
	    || ((flags & O_RDWR) == O_RDWR))
		t->bt_flags |= BTF_ISWRITE;

	return ((BTREE) t);
}

/*
 *  BT_GET -- Get an entry from a btree.
 *
 *	Does a key lookup in the tree to find the specified key, and returns
 *	the key/data pair found.
 *
 *	Parameters:
 *		tree -- btree in which to do lookup
 *		key -- key to find
 *		data -- pointer to DBT in which to return data
 *		flag -- ignored
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR, or RET_SPECIAL if the key is not
 *		found.  If key is not found, nothing is stored in the
 *		return DBT 'data'.
 *
 *	Side Effects:
 *		None.
 *
 *	Warnings:
 *		Return data is statically allocated, and will be overwritten
 *		at the next call.
 */

int
D 9
bt_get(tree, key, data, flag)
	BTREE tree;
	DBT *key;
	DBT *data;
E 9
I 9
bt_get(dbp, key, data, flag)
	DB *dbp; 
	DBT *key, *data;
E 9
D 6
	int flag;
E 6
I 6
	u_long flag;
E 6
{
D 9
	BTREE_P t = (BTREE_P) tree;
E 9
I 9
	BTREE_P t = (BTREE_P) (dbp->internal);
E 9
	BTHEADER *h;
	DATUM *d;
	BTITEM *item;

I 3
#ifdef lint
	flag = flag;
#endif /* lint */

E 3
	/* lookup */
	item = _bt_search(t, key);
D 4
	if (item == (BTITEM *) NULL)
		return (RET_ERROR);
E 4

	/* clear parent pointer stack */
	while (_bt_pop(t) != P_NONE)
		continue;

I 4
	if (item == (BTITEM *) NULL)
		return (RET_ERROR);

E 4
	h = (BTHEADER *) t->bt_curpage;
	data->size = 0;
D 7
	data->data = (char *) NULL;
E 7
I 7
	data->data = (u_char *) NULL;
E 7

	/* match? */
	if (VALIDITEM(t, item)
	    && _bt_cmp(t, key->data, item->bti_index) == 0) {
		d = (DATUM *) GETDATUM(h, item->bti_index);
		return (_bt_buildret(t, d, data, key));
E 10
I 10
		b.psize = m.m_psize;
D 11
		t->bt_flags = m.m_flags;
E 11
I 11
		t->bt_flags |= m.m_flags;
E 11
		t->bt_free = m.m_free;
D 28
		t->bt_lorder = m.m_lorder;
E 28
		t->bt_nrecs = m.m_nrecs;
	} else {
		/*
		 * Set the page size to the best value for I/O to this file.
		 * Don't overflow the page offset type.
		 */
		if (b.psize == 0) {
			b.psize = sb.st_blksize;
			if (b.psize < MINPSIZE)
				b.psize = MINPSIZE;
D 31
			if (b.psize > MAX_PAGE_OFFSET)
				b.psize = MAX_PAGE_OFFSET;
E 31
I 31
			if (b.psize > MAX_PAGE_OFFSET + 1)
				b.psize = MAX_PAGE_OFFSET + 1;
E 31
		}
I 28

		/* Set flag if duplicates permitted. */
E 28
D 11
		t->bt_flags = b.flags & R_DUP ? 0 : BTF_NODUPS;
E 11
I 11
D 23
		t->bt_flags |= b.flags & R_DUP ? 0 : BTF_NODUPS;
E 23
I 23
		if (!(b.flags & R_DUP))
D 30
			SET(t, BTF_NODUPS);
E 30
I 30
			SET(t, B_NODUPS);
E 30
I 28

E 28
E 23
E 11
		t->bt_free = P_INVALID;
D 28
		t->bt_lorder = b.lorder;
E 28
		t->bt_nrecs = 0;
D 30
		SET(t, BTF_METADIRTY);
E 30
I 30
		SET(t, B_METADIRTY);
E 30
E 10
	}

D 10
	/* nope */
	return (RET_SPECIAL);
}
E 10
I 10
	t->bt_psize = b.psize;
E 10

D 10
/*
 *  BT_PUT -- Add an entry to a btree.
 *
 *	The specified (key, data) pair is added to the tree.  If the tree
 *	was created for unique keys only, then duplicates will not be
 *	entered.  If the requested key exists in the tree, it will be over-
 *	written unless the flags parameter is R_NOOVERWRITE, in which case
 *	the update will not be done.  If duplicate keys are permitted in the
 *	tree, duplicates will be inserted and will not overwrite existing
 *	keys.  Nodes are split as required.
 *
 *	Parameters:
 *		tree -- btree in which to put the new entry
 *		key -- key component to add
 *		data -- data corresponding to key
 *		flag -- R_NOOVERWRITE or zero.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR, or RET_SPECIAL if the
 *		NOOVERWRITE flag was set and the specified key exists
 *		in the database.
 *
 *	Side Effects:
 *		None.
 */
E 10
I 10
	/* Set the cache size; must be a multiple of the page size. */
	if (b.cachesize && b.cachesize & b.psize - 1)
		b.cachesize += (~b.cachesize & b.psize - 1) + 1;
	if (b.cachesize < b.psize * MINCACHE)
		b.cachesize = b.psize * MINCACHE;
E 10

D 10
int
D 9
bt_put(tree, key, data, flag)
	BTREE tree;
	DBT *key;
	DBT *data;
E 9
I 9
bt_put(dbp, key, data, flag)
	DB *dbp;
	DBT *key, *data;
E 9
D 6
	int flag;
E 6
I 6
	u_long flag;
E 6
{
D 9
	BTREE_P t = (BTREE_P) tree;
E 9
I 9
	BTREE_P t;
E 9
	BTITEM *item;
E 10
I 10
	/* Calculate number of pages to cache. */
	ncache = (b.cachesize + t->bt_psize - 1) / t->bt_psize;
E 10

I 9
D 10
	t = (BTREE_P)dbp->internal;

E 9
	/* look for this key in the tree */
	item = _bt_search(t, key);

E 10
	/*
D 10
	 *  If this tree was originally created without R_DUP, then duplicate
	 *  keys are not allowed.  We need to check this at insertion time.
E 10
I 10
D 11
	 * The btree data structure requires that at least two keys can fit
	 * on a page, but other than that there's no fixed requirement.  The
	 * user can specify the minimum number per page, and we translate
	 * that into the maximum number of bytes a key can use before being
	 * placed on an overflow page.
E 11
I 11
	 * The btree data structure requires that at least two keys can fit on
	 * a page, but other than that there's no fixed requirement.  The user
	 * specified a minimum number per page, and we translated that into the
	 * number of bytes a key/data pair can use before being placed on an
	 * overflow page.  This calculation includes the page header, the size
	 * of the index referencing the leaf item and the size of the leaf item
	 * structure.  Also, don't let the user specify a minkeypage such that
	 * a key/data pair won't fit even if both key and data are on overflow
	 * pages.
E 11
E 10
	 */
I 10
D 11
	t->bt_minkeypage = (t->bt_psize - BTDATAOFF) / b.minkeypage;
E 11
I 11
	t->bt_ovflsize = (t->bt_psize - BTDATAOFF) / b.minkeypage -
D 26
	    (sizeof(index_t) + NBLEAFDBT(0, 0));
	if (t->bt_ovflsize < NBLEAFDBT(NOVFLSIZE, NOVFLSIZE) + sizeof(index_t))
E 26
I 26
	    (sizeof(indx_t) + NBLEAFDBT(0, 0));
	if (t->bt_ovflsize < NBLEAFDBT(NOVFLSIZE, NOVFLSIZE) + sizeof(indx_t))
E 26
		t->bt_ovflsize =
D 26
		    NBLEAFDBT(NOVFLSIZE, NOVFLSIZE) + sizeof(index_t);
E 26
I 26
		    NBLEAFDBT(NOVFLSIZE, NOVFLSIZE) + sizeof(indx_t);
E 26
E 11
E 10

D 10
	if (VALIDITEM(t, item) && _bt_cmp(t, key->data, item->bti_index) == 0) {
		if ((t->bt_flags & BTF_NODUPS) && flag == R_NOOVERWRITE) {
D 4
			if (_bt_delone(t, item->bti_index) == RET_ERROR)
E 4
I 4
			if (_bt_delone(t, item->bti_index) == RET_ERROR) {
				while (_bt_pop(t) != P_NONE)
					continue;
E 4
				return (RET_ERROR);
I 4
			}
E 4
		}
	}
E 10
I 10
	/* Initialize the buffer pool. */
	if ((t->bt_mp =
	    mpool_open(NULL, t->bt_fd, t->bt_psize, ncache)) == NULL)
		goto err;
D 11
	mpool_filter(t->bt_mp, __bt_pgin, __bt_pgout, t);
E 11
I 11
D 23
	if (NOTSET(t, BTF_INMEM))
E 23
I 23
D 30
	if (!ISSET(t, BTF_INMEM))
E 30
I 30
	if (!ISSET(t, B_INMEM))
E 30
E 23
		mpool_filter(t->bt_mp, __bt_pgin, __bt_pgout, t);
E 11
E 10

D 10
	return (_bt_insert(t, item, key, data, flag));
}
E 10
I 10
	/* Create a root page if new tree. */
	if (nroot(t) == RET_ERROR)
		goto err;
E 10

I 34
	/* Global flags. */
	if (dflags & DB_LOCK)
		SET(t, B_DB_LOCK);
	if (dflags & DB_SHMEM)
		SET(t, B_DB_SHMEM);
	if (dflags & DB_TXN)
		SET(t, B_DB_TXN);

E 34
D 10
/*
 *  BT_DELETE -- delete a key from the tree.
 *
 *	Deletes all keys (and their associated data items) matching the
 *	supplied key from the tree.  If the flags entry is R_CURSOR, then
 *	the current item in the active scan is deleted.
 *
 *	Parameters:
 *		tree -- btree from which to delete key
 *		key -- key to delete
 *		flags -- R_CURSOR or zero
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR, or RET_SPECIAL if the specified
 *		key was not in the tree.
 *
 *	Side Effects:
 *		None.
 */
E 10
I 10
	return (dbp);
E 10

D 10
int
D 9
bt_delete(tree, key, flags)
	BTREE tree;
E 9
I 9
bt_delete(dbp, key, flags)
	DB *dbp;
E 9
	DBT *key;
D 6
	int flags;
E 6
I 6
	u_long flags;
E 6
{
D 9
	BTREE_P t = (BTREE_P) tree;
E 9
I 9
	BTREE_P t;
E 9
	BTHEADER *h;
	BTITEM *item;
	int ndel = 0;
E 10
I 10
einval:	errno = EINVAL;
	goto err;
E 10

I 9
D 10
	t = (BTREE_P)dbp->internal;
E 10
I 10
eftype:	errno = EFTYPE;
	goto err;
E 10

E 9
D 10
	if (flags == R_CURSOR)
		return (_bt_crsrdel(t));

	/* find the first matching key in the tree */
	item = _bt_first(t, key);
	h = t->bt_curpage;

I 4
	/* don't need the descent stack for deletes */
	while (_bt_pop(t) != P_NONE)
		continue;

E 4
	/* delete all matching keys */
	for (;;) {
		while (VALIDITEM(t, item)
		       && (_bt_cmp(t, key->data, item->bti_index) == 0)) {
			if (_bt_delone(t, item->bti_index) == RET_ERROR)
				return (RET_ERROR);
			ndel++;
		}

		if (VALIDITEM(t, item) || h->h_nextpg == P_NONE)
			break;

		/* next page, if necessary */
		do {
			if (_bt_getpage(t, h->h_nextpg) == RET_ERROR)
				return (RET_ERROR);
			h = t->bt_curpage;
		} while (NEXTINDEX(h) == 0 && h->h_nextpg != P_NONE);

		item->bti_pgno = h->h_pgno;
		item->bti_index = 0;

		if (!VALIDITEM(t, item)
		    || _bt_cmp(t, key->data, item->bti_index) != 0)
			break;
E 10
I 10
err:	if (t) {
		if (t->bt_dbp)
			free(t->bt_dbp);
		if (t->bt_fd != -1)
			(void)close(t->bt_fd);
		free(t);
E 10
	}
D 4

	/* clean up the parent stack */
	while (_bt_pop(t) != P_NONE)
		continue;
E 4
D 10

	/* flush changes to disk */
	if (ISDISK(t)) {
		if (h->h_flags & F_DIRTY) {
			if (_bt_write(t, t->bt_curpage, NORELEASE) == RET_ERROR)
				return (RET_ERROR);
		}
	}

	if (ndel == 0)
		return (RET_SPECIAL);

	return (RET_SUCCESS);
E 10
I 10
	return (NULL);
E 10
}

/*
D 3
 *  _BT_CRSRDEL -- Delete the item pointed to by the cursor.
 *
 *	This routine deletes the item most recently returned by a scan
 *	through the tree.  Since it only makes sense to delete the current
 *	record once, we make sure that we don't try to delete twice without
 *	advancing the scan.
 *
 *	Parameters:
 *		t -- tree in which to do deletion
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		The call to _bt_delone marks the cursor, so we can tell that
 *		the current record has been deleted.
 */

static int
_bt_crsrdel(t)
	BTREE_P t;
{
	CURSOR *c;

	c = &(t->bt_cursor);

	/* a cursor must exist, and can't have deleted the current key yet */
	if (!(t->bt_flags & BTF_SEQINIT) || (c->c_flags & CRSR_BEFORE)) {
		errno = EINVAL;
		return (RET_ERROR);
	}

	if (_bt_getpage(t, c->c_pgno) == RET_ERROR)
		return (RET_ERROR);

	if (c->c_index >= NEXTINDEX(t->bt_curpage)) {
		errno = EINVAL;
		return (RET_ERROR);
	}

	return (_bt_delone(t, c->c_index));
}

/*
 *  _BT_DELONE -- Delete a single entry from a btree.
 *
 *	This routine physically removes a btree entry from a leaf page.
 *	IDATUM items are *never* removed from internal nodes, regardless
 *	of whether the entries that originally caused them to be added
 *	are removed from the tree or not.  In addition, pages made empty
 *	by element deletion are not actually reclaimed.  They are,
 *	however, made available for reuse.
 *
 *	To delete an item from a page, we pack the remaining items at
 *	the end of the page, overwriting the deleted item's entry.  We
 *	move the line pointers backward on the page, overwriting the
 *	original item's line pointer.  This guarantees that the space in
 *	the middle of the page is free -- a property that our insertion
 *	strategy relies on.
 *
 *	This routine doesn't reclaim pages all of whose entries have
 *	been deleted.  These pages are available for reuse, however.
 *	If an item is deleted that was too big to fit on a page, then
 *	the blocks that it occupies are put on a free list for reuse.
 *
 *	Parameters:
 *		t -- btree from which to delete item
 *		index -- index of entry on current page to delete
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Physically changes page layout, adjusts internal page
 *		state to reflect the deletion of the item, and updates
 *		the list of free pages for this tree.
 */

static int
_bt_delone(t, index)
	BTREE_P t;
	index_t index;
{
	char *src, *dest;
	int nbytes, nmoved;
	index_t off;
	index_t top;
	index_t i;
	pgno_t chain;
	BTHEADER *h;
	CURSOR *c;
	DATUM *d;

	/* deletion may confuse an active scan.  fix it.  */
	c = &(t->bt_cursor);
	if (t->bt_flags & BTF_SEQINIT && t->bt_curpage->h_pgno == c->c_pgno)
		if (_bt_fixscan(t, index, (DATUM *) NULL, DELETE) == RET_ERROR)
			return (RET_ERROR);

	h = t->bt_curpage;
	off = h->h_linp[index];
	d = (DATUM *) GETDATUM(h, index);

	/* if this is a big item, reclaim the space it occupies */
	if (d->d_flags & D_BIGKEY) {
		bcopy(&(d->d_bytes[0]),
		      (char *) &chain,
		      sizeof(chain));
		if (_bt_delindir(t, chain) == RET_ERROR)
			return (RET_ERROR);
		h = t->bt_curpage;
		d = (DATUM *) GETDATUM(h, index);
	}
	if (d->d_flags & D_BIGDATA) {
		bcopy(&(d->d_bytes[d->d_ksize]),
		      (char *) &chain,
		      sizeof(chain));
		if (_bt_delindir(t, chain) == RET_ERROR)
			return (RET_ERROR);
		h = t->bt_curpage;
		d = (DATUM *) GETDATUM(h, index);
	}

	/* move the data down on the page */
	nbytes = d->d_ksize + d->d_dsize
		 + (sizeof(DATUM) - sizeof(char));
	nbytes = LONGALIGN(nbytes);
	src = ((char *) h) + h->h_upper;
	dest = src + nbytes;
	nmoved = (int) (((char *) d) - src);
	(void) bcopy(src, dest, nmoved);

	/* next move the line pointers up */
	src = (char *) &(h->h_linp[index + 1]);
	dest = (char *) &(h->h_linp[index]);
	nmoved = (int) (((char *) &(h->h_linp[NEXTINDEX(h)])) - src);
	(void) bcopy(src, dest, nmoved);

	/* remember that we freed up some space */
	h->h_upper += nbytes;
	h->h_lower -= sizeof(index_t);

	/* adjust offsets in line pointers affected by moving the data */
	top = NEXTINDEX(h);
	for (i = 0; i < top; i++) {
		if (h->h_linp[i] < off)
			h->h_linp[i] += nbytes;
	}

	/* it's gone */
	h->h_flags |= F_DIRTY;

	return (RET_SUCCESS);
}

/*
 *  _BT_FIXSCAN -- Adjust a scan to cope with a change in tree structure.
 *
 *	If the user has an active scan on the database, and we delete an
 *	item from the page the cursor is pointing at, we need to figure
 *	out what to do about it.  Basically, the solution is to point
 *	"between" keys in the tree, using the CRSR_BEFORE flag.  The
 *	requirement is that the user should not miss any data in the
 *	tree during a scan, just because he happened to do some deletions
 *	or insertions while it was active.
 *
 *	In order to guarantee that the scan progresses properly, we need
 *	to save the key of any deleted item we were pointing at, so that
 *	we can check later insertions against it.
 *
 *	Parameters:
 *		t -- tree to adjust
 *		index -- index of item at which change was made
 *		newd -- new datum (for insertions only)
 *		op -- operation (DELETE or INSERT) causing change
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR (errno is set).
 *
 *	Side Effects:
 *		None.
 */

static int
_bt_fixscan(t, index, newd, op)
	BTREE_P t;
	index_t index;
	DATUM *newd;
	int op;
{
	BTHEADER *h;
	CURSOR *c;
	DATUM *d;

	h = t->bt_curpage;
	c = &(t->bt_cursor);

	if (op == DELETE) {
		if (index < c->c_index)
			c->c_index--;
		else if (index == c->c_index) {
			if (!(c->c_flags & CRSR_BEFORE)) {
				if (_bt_crsrkey(t) == RET_ERROR)
					return (RET_ERROR);
				c->c_flags |= CRSR_BEFORE;
			}
		}
	} else {
		/*
		 *  If we previously deleted the object at this location,
		 *  and now we're inserting a new one, we need to do the
		 *  right thing -- the cursor should come either before
		 *  or after the new item, depending on the key that was
		 *  here, and the new one.
		 */

		if (c->c_flags & CRSR_BEFORE) {
			if (index <= c->c_index) {
				char *tmp;
				int itmp;
				pgno_t chain;
				int r;

				d = (DATUM *) GETDATUM(t->bt_curpage, index);
				if (d->d_flags & D_BIGKEY) {
					bcopy(&(newd->d_bytes[0]),
					      (char *) &chain,
					      sizeof(chain));
					if (_bt_getbig(t, chain, &tmp, &itmp)
					     == RET_ERROR)
						return (RET_ERROR);
				} else
					tmp = &(newd->d_bytes[0]);

				r = (*(t->bt_compare))(tmp, c->c_key);
				if (r < 0)
					c->c_index++;

				if (d->d_flags & D_BIGKEY)
					(void) free (tmp);
			}
		} else if (index <= c->c_index)
			c->c_index++;
	}
	return (RET_SUCCESS);
}

/*
 *  _BT_CRSRKEY -- Save a copy of the key of the record that the cursor
 *		   is pointing to.  The record is about to be deleted.
 *
 *	Parameters:
 *		t -- btree
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Allocates memory for the copy which should be released when
 *		it is no longer needed.
 */

static int
_bt_crsrkey(t)
	BTREE_P t;
{
	CURSOR *c;
	DATUM *d;
	pgno_t pgno;
	int ignore;

	c = &(t->bt_cursor);
	d = (DATUM *) GETDATUM(t->bt_curpage, c->c_index);

	if (d->d_flags & D_BIGKEY) {
		bcopy(&(d->d_bytes[0]), (char *) &pgno, sizeof(pgno));
		return (_bt_getbig(t, pgno, &(c->c_key), &ignore));
	} else {
		if ((c->c_key = (char *) malloc(d->d_ksize)) == (char *) NULL)
			return (RET_ERROR);

		bcopy(&(d->d_bytes[0]), c->c_key, d->d_ksize);
	}
	return (RET_SUCCESS);
}

/*
 *  _BT_GETBIG -- Get big data from indirect pages.
 *
 *	This routine chases indirect blocks for the big object at the 
 *	specified page to a buffer, and return the address of the buffer.
 *
 *	Parameters:
 *		t -- btree with the indirect blocks
 *		pgno -- page number that starts the chain
 *		p -- (char **) to get the address of the buffer containing
 *		     the key or datum.
 *		sz -- pointer to an int to get the size of the instantiated
 *		      object.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		None.
 */

static int
_bt_getbig(t, pgno, p, sz)
	BTREE_P t;
	pgno_t pgno;
	char **p;
	int *sz;
{
	pgno_t save;
	size_t nbytes;
	size_t nhere;
	BTHEADER *h;
	char *top, *from, *where;

	save = t->bt_curpage->h_pgno;
	if (_bt_getpage(t, pgno) == RET_ERROR)
		return (RET_ERROR);

	h = t->bt_curpage;

	bcopy((char *) &(h->h_linp[0]), (char *) &nbytes, sizeof(nbytes));

	if ((*p = (char *) malloc(nbytes)) == (char *) NULL)
		return (RET_ERROR);

	*sz = nbytes;
	from = ((char *) (&h->h_linp[0])) + sizeof(nbytes);
	top = ((char *) h) + t->bt_psize;

	/* need more space for data? */

	where = *p;

	while (nbytes > 0) {
		nhere = (int) (top - from);
		if (nhere > nbytes) {
			(void) bcopy(from, where, nbytes);
			nbytes = 0;
		} else {
			(void) bcopy(from, where, nhere);
			where += nhere;
			nbytes -= nhere;
			if (_bt_getpage(t, h->h_nextpg) == RET_ERROR)
				return (RET_ERROR);
			h = t->bt_curpage;
			top = ((char *) h) + t->bt_psize;
			from = (char *) &(h->h_linp[0]);
		}
	}

	if (_bt_getpage(t, save) == RET_ERROR)
		return (RET_ERROR);

	return (RET_SUCCESS);
}

/*
 *  _BT_DELINDIR -- Delete a chain of indirect blocks from the btree.
 *
 *	When a large item is deleted from the tree, this routine puts the
 *	space that it occupied onto the free list for later reuse.  The
 *	bt_free entry in the btree structure points at the head of this list.
 *	This value is also stored on disk in the btree's metadata.
 *
 *	Parameters:
 *		t -- btree from which to delete pages
 *		chain -- page number that starts the chain.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Invalidates the current on-disk version of the btree's
 *		metadata (if any), and updates the free list appropriately.
 */

static int
_bt_delindir(t, chain)
	BTREE_P t;
	pgno_t chain;
{
	BTHEADER *h;
	pgno_t save;
	pgno_t oldfree;

	h = t->bt_curpage;
	save = h->h_pgno;
	if (_bt_getpage(t, chain) == RET_ERROR)
		return (RET_ERROR);

	/*
	 *  If some internal node is pointing at this chain, don't
	 *  delete it.
	 */

	if (t->bt_curpage->h_flags & F_PRESERVE) {
		if (_bt_getpage(t, save) == RET_ERROR)
			return (RET_ERROR);
		return (RET_SUCCESS);
	}

	/* if there's nothing on the free list, this is easy... */
	if (t->bt_free == P_NONE) {
		t->bt_free = chain;
	} else {
		oldfree = t->bt_free;

		/* find the end of the data chain for the deleted datum */
		t->bt_free = chain;
		do {
			if (_bt_getpage(t, chain) == RET_ERROR)
				return (RET_ERROR);
			h = t->bt_curpage;
			if (h->h_nextpg != P_NONE)
				chain = h->h_nextpg;
		} while (h->h_nextpg != P_NONE);

		/* link freed pages into free list */
		h->h_nextpg = oldfree;
		if (_bt_write(t, h, RELEASE) == RET_ERROR)
			return (RET_ERROR);
		if (_bt_getpage(t, oldfree) == RET_ERROR)
			return (RET_ERROR);
		h = t->bt_curpage;
		h->h_prevpg = chain;
		if (_bt_write(t, h, RELEASE) == RET_ERROR)
			return (RET_ERROR);
	}

	/* restore the tree's current page pointer */
	if (_bt_getpage(t, save) == RET_ERROR)
		return (RET_ERROR);

	/* we have trashed the tree metadata; rewrite it later */
	t->bt_flags &= ~BTF_METAOK;

	return (RET_SUCCESS);
}

/*
 *  _BT_FIRST -- Find the first item in the tree that matches the supplied
 *		 key.
 *
 *	This routine supports deletion.  When the user supplies a key to
 *	be deleted, we find the first one, and iteratively delete all the
 *	matching ones that follow it.
 *
 *	Parameters:
 *		t -- btree in which to find first occurrence
 *		key -- key to find
 *
 *	Returns:
 *		The BTITEM for the matching item.  If there's no match,
 *		this may point to the first item > than the supplied key,
 *		or off the end of the page.
 *
 *	Warnings:
 *		The BTITEM returned is in static space and will be overwritten
 *		by the next search of any kind in any btree.
 */

static BTITEM *
_bt_first(t, key)
	BTREE_P t;
	DBT *key;
{
	BTHEADER *h;
	BTITEM *item;
	index_t next;
	int r;

	/* find any matching item */
	item = _bt_search(t, key);
	h = t->bt_curpage;
	next = NEXTINDEX(h);

	/* if we're off the end of the page, search failed and we're done */
	if (item->bti_index >= next)
		return (item);

	/* as long as we have an exact match, walk backwards */
	while ((r = _bt_cmp(t, key->data, item->bti_index)) == 0) {

		/* at start of page? */
		if (item->bti_index == 0) {

			/* if no prev page, we're done */
			if (h->h_prevpg == P_NONE)
				return (item);

			/* walk backward, skipping empty pages */
			do {
				if (_bt_getpage(t, h->h_prevpg) == RET_ERROR)
					return ((BTITEM *) NULL);
				h = t->bt_curpage;
			} while (NEXTINDEX(h) == 0 && h->h_prevpg != P_NONE);

			if (NEXTINDEX(h) != 0)
				item->bti_index = NEXTINDEX(h) - 1;
			else
				item->bti_index = 0;

			item->bti_pgno = h->h_pgno;
		} else {
			item->bti_index--;
		}
	}

	/* if we went too far backwards, step forward one entry */
	if (r > 0) {
		if (++(item->bti_index) >= NEXTINDEX(h)
		    && h->h_nextpg != P_NONE) {

			/* walk forward, skipping empty pages */
			do {
				if (_bt_getpage(t, h->h_nextpg) == RET_ERROR)
					return ((BTITEM *) NULL);
				h = t->bt_curpage;
			} while (h->h_nextpg != P_NONE && NEXTINDEX(h) == 0);

			item->bti_index = 0;
			item->bti_pgno = h->h_pgno;
		}
	}

	/* got it */
	return (item);
}

/*
 *  _BT_SEARCH, _BT_SEARCHR -- Search for a particular key in the tree.
 *
 *	Parameters:
 *		t -- btree in which to search
 *		key -- key to find
 *
 *	Returns:
 *		BTITEM for matching item, if any, or the BTITEM for the
 *		location of the key, if it were in the tree.
 *
 *	Warnings:
 *		The BTITEM returned is in static memory, and will be
 *		overwritten by the next search of any kind in any tree.
 */

static BTITEM *
_bt_search(t, key)
	BTREE_P t;
	DBT *key;
{
	/* we want to start all of our searches at the root */
	if (_bt_getpage(t, P_ROOT) == RET_ERROR)
		return ((BTITEM *) NULL);

	return (_bt_searchr(t, key));
}

static BTITEM *
_bt_searchr(t, key)
	BTREE_P t;
	DBT *key;
{
	BTHEADER *h = t->bt_curpage;
	index_t index;
	IDATUM *id;
	DATUM *d;
	static BTITEM item;

	/* do a binary search on the current page */
	index = _bt_binsrch(t, &(key->data[0]));

	/*
	 *  At this point, the binary search terminated because the endpoints
	 *  got too close together, or we have a match.  Figure out which
	 *  case applies and decide what to do based on the page type.
	 */
	if (h->h_flags & F_LEAF) {
		item.bti_pgno = h->h_pgno;
		item.bti_index = index;
		if (index < NEXTINDEX(h))
			d = (DATUM *) GETDATUM(h,index);
		else
			d = (DATUM *) NULL;

		item.bti_datum = d;
		return(&item);
	} else {
		id = (IDATUM *) GETDATUM(h, index);
		_bt_push(t, h->h_pgno);
		if (_bt_getpage(t, id->i_pgno) == RET_ERROR)
			return ((BTITEM *) NULL);
		return (_bt_searchr(t, key));
	}
}

/*
 *  BT_GETPAGE -- Make pgno the current page of the btree.
 *
 *	This routine is just a wrapper that decides whether to call the
 *	memory or disk-based routine to do the work.
 *
 *	Parameters:
 *		t -- btree in which to get page
 *		pgno -- page number to get
 *
 *	Returns:
 *		RET_SUCCESS or RET_ERROR.
 */

static int
_bt_getpage(t, pgno)
	BTREE_P t;
	pgno_t pgno;
{
#ifdef DEBUG
	if (pgno == P_NONE)
		_punt();
#endif /* DEBUG */

	/* see if we can get away without doing any work */
	if (t->bt_curpage != (BTHEADER *) NULL) {
		if (t->bt_curpage->h_pgno == pgno)
			return (RET_SUCCESS);
	}

	if (t->bt_fname == (char *) NULL)
		return (_bt_getmpage(t, pgno));
	else
		return (_bt_getdpage(t, pgno));
}

/*
 *  _BT_GETMPAGE -- Make pgno the current page of the btree.
 *
 *	This routine gets pages for in-memory btrees.
 *
 *	Parameters:
 *		t -- btree in which to get page
 *		pgno -- page number to get
 *
 *	Returns:
 *		RET_SUCCESS or RET_ERROR.
 */

static int
_bt_getmpage(t, pgno)
	register BTREE_P t;
	pgno_t pgno;
{
	int htindex;
	int nbytes;
	BTHEADER *h;
	HTBUCKET *b;

	if (t->bt_curpage == (BTHEADER *) NULL) {
		if (pgno != P_ROOT) {
			errno = EBADF;
			return (RET_ERROR);
		}

		t->bt_npages++;
		h = (BTHEADER *) malloc((unsigned) t->bt_psize);
		if (h == (BTHEADER *) NULL)
			return (RET_ERROR);

		h->h_pgno = P_ROOT;
		h->h_flags = F_LEAF;
		h->h_lower = (index_t)
				(((char *) &(h->h_linp[0])) - ((char *) h));
		h->h_upper = t->bt_psize;
		h->h_prevpg = h->h_nextpg = P_NONE;

		t->bt_curpage = h;

		/* get the root page into the hash table */
		if (_bt_write(t, h, RELEASE) == RET_ERROR)
			return (RET_ERROR);
	}

	htindex = HASHKEY(pgno);

	for (b = t->bt_s.bt_ht[htindex];
	     b != (HTBUCKET *) NULL;
	     b = b->ht_next) {
		if (b->ht_pgno == pgno) {
			t->bt_curpage = b->ht_page;
			return (RET_SUCCESS);
		}
	}
	return (RET_ERROR);
}

/*
 *  _BT_GETDPAGE -- Make pgno the current page of the btree.
 *
 *	This routine gets pages for disk btrees.
 *
 *	Because disk btree pages must be readable across machine architectures,
 *	the btree code writes integers out in network format.  This routine
 *	converts them back to host format before returning the page.
 *
 *	Parameters:
 *		t -- btree in which to get page
 *		pgno -- page number to get
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 */

static int
_bt_getdpage(t, pgno)
	register BTREE_P t;
	pgno_t pgno;
{
	BTHEADER *h;
	char *cache;
	long pos;
	int n, nbytes;

	/* if we have an lru cache, let the cache code do the work */
	if (ISCACHE(t)) {
		cache = t->bt_s.bt_d.d_cache;

		/* release the old page */
		if (t->bt_curpage != (BTHEADER *) NULL) {
			pgno_t opgno = t->bt_curpage->h_pgno;
			t->bt_curpage->h_flags &= ~F_DIRTY;

			if (lruwrite(cache, opgno) < 0)
				return (RET_ERROR);

			lrurelease(cache, opgno);
		}

		if (pgno > t->bt_npages) {
			if ((h = (BTHEADER *) lrugetnew(cache, pgno, &nbytes))
			    == (BTHEADER *) NULL)
				return (RET_ERROR);
			t->bt_npages = pgno;
		} else {
			if ((h = (BTHEADER *) lruget(cache, pgno, &nbytes))
			    == (BTHEADER *) NULL)
				return (RET_ERROR);
		}

		/* init this page, if necessary */
		if (nbytes == 0) {
			h->h_pgno = pgno;
			h->h_flags = F_LEAF;
			h->h_lower = (index_t)
				(((char *) &(h->h_linp[0])) - ((char *) h));
			h->h_upper = t->bt_psize;
			h->h_prevpg = h->h_nextpg = P_NONE;
		}

		t->bt_curpage = h;

		return (RET_SUCCESS);
	}

	/* sync the current page, if necessary */
	if (t->bt_curpage != (BTHEADER *) NULL) {
		if (t->bt_curpage->h_flags & F_DIRTY)
			if (_bt_write(t, t->bt_curpage, RELEASE) == RET_ERROR)
				return (RET_ERROR);
	} else {
		if (t->bt_npages == 0)
			t->bt_npages = 1;

		/* if no current page, get space for one */
		if ((t->bt_curpage = (BTHEADER *) malloc((unsigned) t->bt_psize))
		    == (BTHEADER *) NULL) {
			return (RET_ERROR);
		}
	}

	n = t->bt_psize;
	pos = (long) (pgno * n);

	/* seek to correct location in file */
	if (lseek(t->bt_s.bt_d.d_fd, pos, L_SET) != pos) {
		return (RET_ERROR);
	}

	/* read the page */
	if ((nbytes = read(t->bt_s.bt_d.d_fd, t->bt_curpage, n)) < n) {

		/*
		 *  If we didn't get a full page, we must have gotten no
		 *  data at all -- in which case we're trying to read a
		 *  root page that doesn't exist yet.  This is the only
		 *  case in which this is okay.  If this happens, construct
		 *  an empty root page by hand.
		 */
		if (nbytes != 0 || pgno != P_ROOT) {
			errno = EBADF;
			return (RET_ERROR);
		}

		h = (BTHEADER *) t->bt_curpage;
		h->h_pgno = pgno;
		h->h_flags = F_LEAF;
		h->h_lower = (index_t)
				(((char *) &(h->h_linp[0])) - ((char *) h));
		h->h_upper = t->bt_psize;
		h->h_prevpg = h->h_nextpg = P_NONE;
	} else
		(void) _bt_pgin(t->bt_curpage, (char *) t->bt_lorder);

	return (RET_SUCCESS);
}

/*
 *  _BT_PGOUT, _BT_PGIN -- Convert host-specific number layout to/from
 *			   the host-independent format stored on disk.
 *
 *	Parameters:
 *		h -- page to convert
 *		_lorder -- byte order for pages (stored as a char * in the
 *			   cache, and passed around as a magic cookie).
 *
 *	Returns:
 *		RET_SUCCESS (lru code requires a return value).
 *
 *	Side Effects:
 *		Layout of tree metadata on the page is changed in place.
 *
 *	Warnings:
 *		Everywhere else in the code, the types pgno_t and index_t
 *		are opaque.  These two routines know what they really
 *		are.
 */

static int
_bt_pgout(h, _lorder)
	BTHEADER *h;
	char *_lorder;
{
	int i;
	int top;
	int lorder;
	DATUM *d;
	IDATUM *id;
	size_t chain;

	lorder = (int) _lorder;
	if (lorder == BYTE_ORDER)
		return (RET_SUCCESS);

	if (h->h_flags & F_LEAF) {
		if (h->h_flags & F_CONT) {
			if (h->h_prevpg == P_NONE) {
				size_t longsz;

				(void) bcopy((char *) &(h->h_linp[0]),
					      (char *) &longsz,
					      sizeof(longsz));
				BLSWAP(longsz);
				(void) bcopy((char *) &longsz,
					      (char *) &(h->h_linp[0]),
					      sizeof(longsz));
			}
		} else {
			top = NEXTINDEX(h);
			for (i = 0; i < top; i++) {
				d = (DATUM *) GETDATUM(h, i);
				if (d->d_flags & D_BIGKEY) {
					(void) bcopy((char *) &(d->d_bytes[0]),
						      (char *) &chain,
						      sizeof(chain));
					BLSWAP(chain);
					(void) bcopy((char *) &chain,
						      (char *) &(d->d_bytes[0]),
						      sizeof(chain));
				}
				if (d->d_flags & D_BIGDATA) {
					(void) bcopy((char *) &(d->d_bytes[d->d_ksize]),
						      (char *) &chain,
						      sizeof(chain));
					BLSWAP(chain);
					(void) bcopy((char *) &chain,
						      (char *) &(d->d_bytes[d->d_ksize]),
						      sizeof(chain));
				}
				BLSWAP(d->d_dsize);
				BLSWAP(d->d_ksize);
				BLSWAP(d->d_flags);
				BLSWAP(h->h_linp[i]);
			}
		}
	} else {
		top = NEXTINDEX(h);
		for (i = 0; i < top; i++) {
			id = (IDATUM *) GETDATUM(h, i);
			BLSWAP(id->i_size);
			BLSWAP(id->i_pgno);
			BLSWAP(id->i_flags);
			if (id->i_flags & D_BIGKEY) {
				(void) bcopy((char *) &(id->i_bytes[0]),
					      (char *) &chain,
					      sizeof(chain));
				BLSWAP(chain);
				(void) bcopy((char *) &chain,
					      (char *) &(id->i_bytes[0]),
					      sizeof(chain));
			}
			BLSWAP(h->h_linp[i]);
		}
	}
	BLSWAP(h->h_flags);
	BLSWAP(h->h_pgno);
	BLSWAP(h->h_prevpg);
	BLSWAP(h->h_nextpg);
	BLSWAP(h->h_lower);
	BLSWAP(h->h_upper);

	return (RET_SUCCESS);
}

static int
_bt_pgin(h, _lorder)
	BTHEADER *h;
	char *_lorder;
{
	int i;
	int top;
	int lorder;
	DATUM *d;
	IDATUM *id;
	size_t chain;

	/*
	 *  If btree pages are to be stored in the host byte order, don't
	 *  bother swapping.
	 */
	lorder = (int) _lorder;
	if (lorder == BYTE_ORDER)
		return (RET_SUCCESS);

	BLSWAP(h->h_upper);
	BLSWAP(h->h_lower);
	BLSWAP(h->h_nextpg);
	BLSWAP(h->h_prevpg);
	BLSWAP(h->h_pgno);
	BLSWAP(h->h_flags);

	if (h->h_flags & F_LEAF) {
		if (h->h_flags & F_CONT) {
			if (h->h_prevpg == P_NONE) {
				size_t longsz;

				(void) bcopy((char *) &(h->h_linp[0]),
					      (char *) &longsz,
					      sizeof(longsz));
				BLSWAP(longsz);
				(void) bcopy((char *) &longsz,
					      (char *) &(h->h_linp[0]),
					      sizeof(longsz));
			}
		} else {
			top = NEXTINDEX(h);
			for (i = 0; i < top; i++) {
				BLSWAP(h->h_linp[i]);
				d = (DATUM *) GETDATUM(h, i);
				BLSWAP(d->d_dsize);
				BLSWAP(d->d_ksize);
				BLSWAP(d->d_flags);
				if (d->d_flags & D_BIGKEY) {
					(void) bcopy((char *) &(d->d_bytes[0]),
						      (char *) &chain,
						      sizeof(chain));
					BLSWAP(chain);
					(void) bcopy((char *) &chain,
						      (char *) &(d->d_bytes[0]),
						      sizeof(chain));
				}
				if (d->d_flags & D_BIGDATA) {
					(void) bcopy((char *) &(d->d_bytes[d->d_ksize]),
						      (char *) &chain,
						      sizeof(chain));
					BLSWAP(chain);
					(void) bcopy((char *) &chain,
						      (char *) &(d->d_bytes[d->d_ksize]),
						      sizeof(chain));
				}
			}
		}
	} else {
		top = NEXTINDEX(h);
		for (i = 0; i < top; i++) {
			BLSWAP(h->h_linp[i]);
			id = (IDATUM *) GETDATUM(h, i);
			BLSWAP(id->i_size);
			BLSWAP(id->i_pgno);
			BLSWAP(id->i_flags);
			if (id->i_flags & D_BIGKEY) {
				(void) bcopy((char *) &(id->i_bytes[0]),
					      (char *) &chain,
					      sizeof(chain));
				BLSWAP(chain);
				(void) bcopy((char *) &chain,
					      (char *) &(id->i_bytes[0]),
					      sizeof(chain));
			}
		}
	}
	return (RET_SUCCESS);
}

/*
E 3
D 10
 *  BT_SYNC -- sync the btree to disk.
E 10
I 10
 * NROOT -- Create the root of a new tree.
E 10
 *
D 10
 *	Parameters:
 *		tree -- btree to sync.
E 10
I 10
 * Parameters:
 *	t:	tree
E 10
 *
D 10
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
E 10
I 10
 * Returns:
 *	RET_ERROR, RET_SUCCESS
E 10
 */
D 10

D 9
bt_sync(tree)
	BTREE tree;
E 9
I 9
bt_sync(dbp)
	DB *dbp;
E 10
I 10
static int
nroot(t)
	BTREE *t;
E 10
E 9
{
D 9
	BTREE_P t = (BTREE_P) tree;
E 9
I 9
D 10
	BTREE_P t;
E 9
	BTHEADER *h;
	pgno_t pgno;
E 10
I 10
	PAGE *meta, *root;
	pgno_t npg;
E 10

I 9
D 10
	t = (BTREE_P)dbp->internal;

E 9
	/* if this is an in-memory btree, syncing is a no-op */
	if (!ISDISK(t))
E 10
I 10
	if ((meta = mpool_get(t->bt_mp, 0, 0)) != NULL) {
		mpool_put(t->bt_mp, meta, 0);
E 10
		return (RET_SUCCESS);
D 10

	h = (BTHEADER *) t->bt_curpage;
	h->h_flags &= ~F_DIRTY;

	if (ISCACHE(t)) {
		pgno = t->bt_curpage->h_pgno;
		if (_bt_write(t, h, RELEASE) == RET_ERROR)
			return(RET_ERROR);
		if (lrusync(t->bt_s.bt_d.d_cache) < RET_ERROR)
			return (RET_ERROR);
		if (_bt_getpage(t, pgno) == RET_ERROR)
			return (RET_ERROR);
	} else {
		if (_bt_write(t, h, NORELEASE) == RET_ERROR)
			return (RET_ERROR);
E 10
	}
I 10
	if (errno != EINVAL)
		return (RET_ERROR);
E 10

D 10
	return (fsync(t->bt_s.bt_d.d_fd));
}
E 10
I 10
	if ((meta = mpool_new(t->bt_mp, &npg)) == NULL)
		return (RET_ERROR);
E 10

D 10
/*
D 3
 *  _BT_INSERT -- Insert a new user datum in the btree.
 *
 *	This routine is called by bt_put, the public interface, once the
 *	location for the new item is known.  We do the work here, and
 *	handle splits if necessary.
 *
 *	Parameters:
 *		t -- btree in which to do the insertion.
 *		item -- BTITEM describing location of new datum
 *		key -- key to insert
 *		data -- data associated with key
 *		flag -- magic cookie passed recursively to bt_put if we
 *			have to do a split
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 */

static int
_bt_insert(t, item, key, data, flag)
	BTREE_P t;
	BTITEM *item;
	DBT *key;
	DBT *data;
	int flag;
{
	index_t index;
	BTHEADER *h;
	DATUM *d;
	int nbytes;
	int status;
	pgno_t pgno;
	int keysize, datasize;
	int bigkey, bigdata;

	if (_bt_getpage(t, item->bti_pgno) == RET_ERROR)
		return (RET_ERROR);
	h = t->bt_curpage;

	if (TOOBIG(t, data->size)) {
		bigdata = TRUE;
		datasize = sizeof(pgno_t);
	} else {
		bigdata = FALSE;
		datasize = data->size;
	}

	if (TOOBIG(t, key->size)) {
		bigkey = TRUE;
		keysize = sizeof(pgno_t);
	} else {
		bigkey = FALSE;
		keysize = key->size;
	}

	nbytes = keysize + datasize + (sizeof(DATUM) - sizeof(char));
	nbytes = LONGALIGN(nbytes) + sizeof(index_t);

	/* if there's not enough room here, split the page */
	if ((h->h_upper - h->h_lower) < nbytes) {
		if (_bt_split(t) == RET_ERROR)
			return (RET_ERROR);

		/* okay, try again */
		return (bt_put(t, key, data, flag));
	}

	/* put together a leaf page datum from the key/data pair */
	index = item->bti_index;
	nbytes = keysize + datasize + (sizeof(DATUM) - sizeof(char));

	if ((d = (DATUM *) malloc((unsigned) nbytes)) == (DATUM *) NULL)
		return (RET_ERROR);

	d->d_ksize = keysize;
	d->d_dsize = datasize;
	d->d_flags = 0;

	if (bigkey) {
		if (_bt_indirect(t, key, &pgno) == RET_ERROR)
			return (RET_ERROR);
		(void) bcopy((char *) &pgno, &(d->d_bytes[0]), sizeof(pgno));
		d->d_flags |= D_BIGKEY;
		if (_bt_getpage(t, item->bti_pgno) == RET_ERROR)
			return (RET_ERROR);
	} else {
		if (d->d_ksize > 0) {
			(void) bcopy((char *) key->data,
				      (char *) &(d->d_bytes[0]),
				      (int) d->d_ksize);
		}
	}

	if (bigdata) {
		if (_bt_indirect(t, data, &pgno) == RET_ERROR)
			return (RET_ERROR);
		(void) bcopy((char *) &pgno,
			     &(d->d_bytes[keysize]),
			     sizeof(pgno));
		d->d_flags |= D_BIGDATA;
		if (_bt_getpage(t, item->bti_pgno) == RET_ERROR)
			return (RET_ERROR);
	} else {
		if (d->d_dsize > 0) {
			(void) bcopy((char *) data->data,
				      (char *) &(d->d_bytes[keysize]),
				      (int) d->d_dsize);
		}
	}

	/* do the insertion */
	status = _bt_insertat(t, d, index);

	(void) free((char *) d);

	return (status);
}

/*
 *  _BT_INDIRECT -- Write a series of indirect pages for big objects.
 *
 *	A chain of indirect pages looks like
 *
 *	   +-------------------+   +---------------------+
 *	   |hdr|size|	       |   |hdr|		 |
 *	   +---+----+	       |   +---+		 |
 *	   |   ... data ...    |   |   ... data ...	 |    ...
 *	   |		       |   |			 |
 *	   +-------------------+   +---------------------+
 *
 *	where hdr is a standard btree page header (with the indirect bit
 *	set), size on the first page is the real size of the datum, and
 *	data are bytes of the datum, split across as many pages as necessary.
 *	Indirect pages are chained together with the h_prevpg and h_nextpg
 *	entries of the page header struct.
 *
 *	A single DBT is written per chain, so space on the last page is
 *	wasted.
 *
 *	We return the page number of the start of the chain.
 *
 *	When a big object is deleted from a tree, the space that it occupied
 *	is placed on a free list for later reuse.  This routine checks that
 *	free list before allocating new pages to the big datum being inserted.
 *
 *	Parameters:
 *		t -- btree in which to store indirect blocks
 *		data -- DBT with the big datum in it
 *		pgno -- place to put the starting page number of the chain
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Current page is changed on return.
 */

static int
_bt_indirect(t, data, pgno)
	BTREE_P t;
	DBT *data;
	pgno_t *pgno;
{
	pgno_t save;
	pgno_t prev;
	char *top;
	char *where;
	char *from;
	size_t dsize;
	pgno_t nextchn;
	int ischain;
	BTHEADER *cur;

	/* get set for first page in chain */
	prev = P_NONE;
	dsize = data->size;
	from = (char *) data->data;

	/* if there are blocks on the free list, use them first */
	if ((*pgno = t->bt_free) == P_NONE) {
		if ((cur = _bt_allocpg(t)) == (BTHEADER *) NULL)
			return (RET_ERROR);

		ischain = 0;
		*pgno = cur->h_pgno = ++(t->bt_npages);
	} else {
		if (_bt_getpage(t, *pgno) == RET_ERROR)
			return (RET_ERROR);
		ischain = 1;
		cur = t->bt_curpage;
	}

	cur->h_flags = F_CONT|F_LEAF;
	(void) bcopy((char *) &dsize, (char *) &cur->h_linp[0], sizeof(size_t));
	where = ((char *) (&cur->h_linp[0])) + sizeof(size_t);

	/* fill and write pages in the chain */
	for (;;) {
		int nhere;

		top = ((char *) cur) + t->bt_psize;
		cur->h_prevpg = prev;
		nextchn = cur->h_nextpg;
		nhere = (int) (top - where);

		if (nhere >= dsize) {
			(void) bcopy(from, where, (int) dsize);
			cur->h_nextpg = P_NONE;
			dsize = 0;
		} else {
			(void) bcopy(from, where, (int) nhere);
			dsize -= nhere;
			from += nhere;
			if (nextchn == P_NONE)
				cur->h_nextpg = t->bt_npages + 1;
			prev = cur->h_pgno;
		}

		/* current page is ready to go; write it out */
		if (_bt_write(t, cur, RELEASE) == RET_ERROR)
			return (RET_ERROR);

		/* free the current page, if appropriate */
		if (ISDISK(t) && !ISCACHE(t) && !ischain) {
			(void) free ((char *) cur);
		}

		/* done? */
		if (dsize == 0)
			break;

		/* allocate another page */
		if (nextchn == P_NONE) {
			if ((cur = _bt_allocpg(t)) == (BTHEADER *) NULL)
				return (RET_ERROR);
			ischain = 0;
			cur->h_pgno = ++(t->bt_npages);
		} else {
			if (_bt_getpage(t, nextchn) == RET_ERROR)
				return (RET_ERROR);
			ischain = 1;
			cur = t->bt_curpage;
		}
		cur->h_flags = F_LEAF | F_CONT;

		where = (char *) (&cur->h_linp[0]);
	}

	/* if we used pages from the free list, record changes to it */
	if (*pgno == t->bt_free) {
		t->bt_free = nextchn;
		t->bt_flags &= ~BTF_METAOK;
	}

	return (RET_SUCCESS);
}

/*
 *  _BT_SPLIT -- Split a page into two pages.
 *
 *	Splits are caused by insertions, and propogate up the tree in
 *	the usual way.  The root page is always page 1 in the file on
 *	disk, so root splits are handled specially.  On entry to this
 *	routine, t->bt_curpage is the page to be split.
 *
 *	Parameters:
 *		t -- btree in which to do split.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Changes the notion of the current page.
 */

static
_bt_split(t)
	BTREE_P t;
{
	BTHEADER *h;
	BTHEADER *left, *right;
	BTHEADER *next;
	pgno_t nextpgno, parent;
	int nbytes, len;
	IDATUM *id;
	DATUM *d;
	char *src;
	IDATUM *new;
	pgno_t oldchain;
	u_char flags;

	h = (BTHEADER *) t->bt_curpage;

	/* split root page specially, since it must remain page 1 */
	if (h->h_pgno == P_ROOT) {
		return (_bt_splitroot(t));
	}

	/*
	 *  This is a little complicated.  We go to some trouble to
	 *  figure out which of the three possible cases -- in-memory tree,
	 *  disk tree (no cache), and disk tree (cache) -- we have, in order
	 *  to avoid unnecessary copying.  If we have a disk cache, then we
	 *  have to do some extra copying, though, since the cache code
	 *  manages buffers externally to this code.
	 */

	if (ISDISK(t) && ISCACHE(t)) {
		if ((left = (BTHEADER *) malloc((unsigned) t->bt_psize))
		    == (BTHEADER *) NULL)
			return (RET_ERROR);
		left->h_pgno = left->h_prevpg = left->h_nextpg = P_NONE;
		left->h_flags = t->bt_curpage->h_flags;
		left->h_lower = (index_t)
			  (((char *) &(left->h_linp[0])) - ((char *) left));
		left->h_upper = t->bt_psize;

	} else {
		if ((left = _bt_allocpg(t)) == (BTHEADER *) NULL)
			return (RET_ERROR);
	}
	left->h_pgno = h->h_pgno;

	if ((right = _bt_allocpg(t)) == (BTHEADER *) NULL)
		return (RET_ERROR);
	right->h_pgno = ++(t->bt_npages);

	/* now do the split */
	if (_bt_dopsplit(t, left, right) == RET_ERROR)
		return (RET_ERROR);

	right->h_prevpg = left->h_pgno;
	nextpgno = right->h_nextpg = h->h_nextpg;
	left->h_nextpg = right->h_pgno;
	left->h_prevpg = h->h_prevpg;

	/* okay, now use the left half of the page as the new page */
	if (ISDISK(t) && ISCACHE(t)) {
		(void) bcopy((char *) left, (char *) t->bt_curpage,
			     (int) t->bt_psize);
		(void) free ((char *) left);
		left = t->bt_curpage;
	} else {
		(void) free((char *) t->bt_curpage);
		t->bt_curpage = left;
	}

	/*
	 *  Write the new pages out.  We need them to stay where they are
	 *  until we're done updating the parent pages.
	 */

	if (_bt_write(t, left, NORELEASE) == RET_ERROR)
		return (RET_ERROR);
	if (_bt_write(t, right, NORELEASE) == RET_ERROR)
		return (RET_ERROR);

	/* update 'prev' pointer of old neighbor of left */
	if (nextpgno != P_NONE) {
		if (_bt_getpage(t, nextpgno) == RET_ERROR)
			return (RET_ERROR);
		h = t->bt_curpage;
		h->h_prevpg = right->h_pgno;
		h->h_flags |= F_DIRTY;
	}

	if ((parent = _bt_pop(t)) != P_NONE) {
		if (right->h_flags & F_LEAF) {
			d = (DATUM *) GETDATUM(right, 0);
			len = d->d_ksize;
			if (d->d_flags & D_BIGKEY) {
				bcopy(&(d->d_bytes[0]),
				      (char *) &oldchain,
				      sizeof(oldchain));
				if (_bt_markchain(t, oldchain) == RET_ERROR)
					return (RET_ERROR);
				src = (char *) &oldchain;
				flags = D_BIGKEY;
			} else {
				src = (char *) &(d->d_bytes[0]);
				flags = 0;
			}
		} else {
			id = (IDATUM *) GETDATUM(right, 0);
			len = id->i_size;
			flags = id->i_flags;
			src = (char *) &(id->i_bytes[0]);
		}
		nbytes = len + (sizeof(IDATUM) - sizeof(char));
		new = (IDATUM *) malloc((unsigned) nbytes);
		if (new == (IDATUM *) NULL)
			return (RET_ERROR);
		new->i_size = len;
		new->i_pgno = right->h_pgno;
		new->i_flags = flags;
		if (len > 0)
			(void) bcopy(src, (char *) &(new->i_bytes[0]), len);

		nbytes = LONGALIGN(nbytes) + sizeof(index_t);
		if (_bt_getpage(t, parent) == RET_ERROR)
			return (RET_ERROR);

		h = t->bt_curpage;

		/*
		 *  Split the parent if we need to, then reposition the
		 *  tree's current page pointer for the new datum.
		 */
		if ((h->h_upper - h->h_lower) < nbytes) {
			if (_bt_split(t) == RET_ERROR)
				return (RET_ERROR);
			if (_bt_reposition(t, new, parent, right->h_prevpg)
			      == RET_ERROR)
				return (RET_ERROR);
		}

		/* okay, now insert the new idatum */
		if (_bt_inserti(t, new, right->h_prevpg) == RET_ERROR)
			return (RET_ERROR);
	}

	/*
	 *  Okay, split is done; don't need right page stapled down anymore.
	 *  The page we call 'left' above is the new version of the old
	 *  (split) page, so we can't release it.
	 */

	if (_bt_release(t, right) == RET_ERROR)
		return (RET_ERROR);
	if (ISDISK(t) && !ISCACHE(t))
		(void) free((char *) right);

	return (RET_SUCCESS);
}

/*
 *  _BT_MARKCHAIN -- Mark a chain of pages as used by an internal node.
 *
 *	Chains of indirect blocks pointed to by leaf nodes get reclaimed
 *	when the item that points to them gets deleted.  Chains pointed
 *	to by internal nodes never get deleted.  This routine marks a
 *	chain as pointed to by an internal node.
 *
 *	Parameters:
 *		t -- tree in which to mark
 *		chain -- number of first page in chain
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		None.
 */

static int
_bt_markchain(t, chain)
	BTREE_P t;
	pgno_t chain;
{
	pgno_t save;

	save = t->bt_curpage->h_pgno;

	if (_bt_getpage(t, chain) == RET_ERROR)
		return (RET_ERROR);

	t->bt_curpage->h_flags |= (F_DIRTY|F_PRESERVE);

	if (_bt_getpage(t, save) == RET_ERROR)
		return (RET_ERROR);

	return (RET_SUCCESS);
}

/*
 *  _BT_REPOSITION -- Reposition the current page pointer of a btree.
 *
 *	After splitting a node in the tree in order to make room for
 *	an insertion, we need to figure out which page after the split
 *	should get the item we want to insert.  This routine positions
 *	the tree's current page pointer appropriately.
 *
 *	Parameters:
 *		t -- tree to position
 *		new -- the item we want to insert
 *		parent -- parent of the node that we just split
 *		prev -- page number of item directly to the left of
 *			new's position in the tree.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		None.
 */

static int
_bt_reposition(t, new, parent, prev)
	BTREE_P t;
	IDATUM *new;
	pgno_t parent;
	pgno_t prev;
{
	index_t i, next;
	IDATUM *idx;

	if (parent == P_ROOT) {

		/*
		 *  If we just split the root page, then there are guaranteed
		 *  to be exactly two IDATUMs on it.  Look at both of them
		 *  to see if they point to the page that we want.
		 */

		if (_bt_getpage(t, parent) == RET_ERROR)
			return (RET_ERROR);

		next = NEXTINDEX(t->bt_curpage);
		for (i = 0; i < next; i++) {
			idx = (IDATUM *) GETDATUM(t->bt_curpage, i);
			if (_bt_getpage(t, idx->i_pgno) == RET_ERROR)
				return (RET_ERROR);
			if (_bt_isonpage(t, new, prev) == RET_SUCCESS)
				return (RET_SUCCESS);
			if (_bt_getpage(t, parent) == RET_ERROR)
				return (RET_ERROR);
		}
	} else {

		/*
		 *  Get the parent page -- which is where the new item would
		 *  have gone -- and figure out whether the new item now goes
		 *  on the parent, or the page immediately to the right of
		 *  the parent.
		 */

		if (_bt_getpage(t, parent) == RET_ERROR)
			return (RET_ERROR);
		if (_bt_isonpage(t, new, prev) == RET_SUCCESS)
			return (RET_SUCCESS);
		if (_bt_getpage(t, t->bt_curpage->h_nextpg) == RET_ERROR)
			return (RET_ERROR);
		if (_bt_isonpage(t, new, prev) == RET_SUCCESS)
			return (RET_SUCCESS);
	}
	return (RET_ERROR);
}

/*
 *  _BT_ISONPAGE -- Is the IDATUM for a given page number on the current page?
 *
 *	This routine is used by _bt_reposition to decide whether the current
 *	page is the correct one on which to insert a new item.
 *
 *	Parameters:
 *		t -- tree to check
 *		new -- the item that will be inserted (used for binary search)
 *		prev -- page number of page whose IDATUM is immediately to
 *			the left of new's position in the tree.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR (corresponding to TRUE, FALSE).
 */

static int
_bt_isonpage(t, new, prev)
	BTREE_P t;
	IDATUM *new;
	pgno_t prev;
{
	BTHEADER *h = (BTHEADER *) t->bt_curpage;
	index_t i, next;
	IDATUM *idx;

	i = _bt_binsrch(t, &(new->i_bytes[0]));
	while (i != 0 && _bt_cmp(t, &(new->i_bytes[0]), i) == 0)
		--i;
	next = NEXTINDEX(h);
	idx = (IDATUM *) GETDATUM(h, i);
	while (i < next && idx->i_pgno != prev) {
		i++;
		idx = (IDATUM *) GETDATUM(h, i);
	}
	if (idx->i_pgno == prev)
		return (RET_SUCCESS);
	else
		return (RET_ERROR);
}

/*
 *  _BT_SPLITROOT -- Split the root of a btree.
 *
 *	The root page for a btree is always page one.  This means that in
 *	order to split the root, we need to do extra work.
 *
 *	Parameters:
 *		t -- tree to split
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Splits root upward in the usual way, adding two new pages
 *		to the tree (rather than just one, as in usual splits).
 */

static
_bt_splitroot(t)
	BTREE_P t;
{
	BTHEADER *h = t->bt_curpage;
	BTHEADER *left, *right;
	DATUM *d;
	IDATUM *id;
	char *where;
	BTHEADER *where_h;
	pgno_t lastpg;
	char *src, *dest;
	int len, nbytes;
	u_long was_leaf;
	pgno_t oldchain;
	u_char flags;

	/* get two new pages for the split */
	if ((left = _bt_allocpg(t)) == (BTHEADER *) NULL)
		return (RET_ERROR);
	left->h_pgno = ++(t->bt_npages);
	if ((right = _bt_allocpg(t)) == (BTHEADER *) NULL)
		return (RET_ERROR);
	right->h_pgno = ++(t->bt_npages);

	/* do the split */
	if (_bt_dopsplit(t, left, right) == RET_ERROR)
		return (RET_ERROR);

	/* connect the new pages correctly */
	right->h_prevpg = left->h_pgno;
	left->h_nextpg = right->h_pgno;

	/*
	 *  Write the child pages out now.  We need them to remain
	 *  where they are until we finish updating parent pages,
	 *  however.
	 */

	if (_bt_write(t, left, NORELEASE) == RET_ERROR)
		return (RET_ERROR);
	if (_bt_write(t, right, NORELEASE) == RET_ERROR)
		return (RET_ERROR);

	/* now change the root page into an internal page */
	was_leaf = (h->h_flags & F_LEAF);
	h->h_flags &= ~F_LEAF;
	h->h_lower = (index_t) (((char *) (&(h->h_linp[0]))) - ((char *) h));
	h->h_upper = (index_t) t->bt_psize;
	(void) bzero((char *) &(h->h_linp[0]), (int) (h->h_upper - h->h_lower));

	/* put two new keys on root page */
	where_h = left;
	while (where_h) {
		DATUM *data;
		IDATUM *idata;

		if (was_leaf) {
			data = (DATUM *) GETDATUM(where_h, 0);

			if (where_h == left) {
				len = 0;	/* first key in tree is null */
			} else {
				if (data->d_flags & D_BIGKEY) {
					bcopy(&(data->d_bytes[0]),
					      (char *) &oldchain,
					      sizeof(oldchain));
					if (_bt_markchain(t, oldchain) == RET_ERROR)
						return (RET_ERROR);
					src = (char *) &oldchain;
					flags = D_BIGKEY;
				} else {
					src = (char *) &(data->d_bytes[0]);
					flags = 0;
				}
				len = data->d_ksize;
			}
		} else {
			idata = (IDATUM *) GETDATUM(where_h, 0);
			len = idata->i_size;
			flags = idata->i_flags;
			src = &(idata->i_bytes[0]);
		}
		dest = ((char *) h) + h->h_upper;
		nbytes = len + (sizeof (IDATUM) - sizeof(char));
		dest -= LONGALIGN(nbytes);
		id = (IDATUM *) dest;
		id->i_size = len;
		id->i_pgno = where_h->h_pgno;
		id->i_flags = flags;
		if (len > 0)
			(void) bcopy((char *) src, (char *) &(id->i_bytes[0]), len);
		dest -= ((int) h);
		h->h_linp[NEXTINDEX(h)] = (index_t) dest;
		h->h_upper = (index_t) dest;
		h->h_lower += sizeof(index_t);

		/* next page */
		if (where_h == left)
			where_h = right;
		else
			where_h = (BTHEADER *) NULL;
	}

	if (_bt_release(t, left) == RET_ERROR)
		return (RET_ERROR);
	if (_bt_release(t, right) == RET_ERROR)
		return (RET_ERROR);

	/*
	 *  That's it, split is done.  If we're doing a non-cached disk
	 *  btree, we can free up the pages we allocated, as they're on
	 *  disk, now.
	 */

	if (ISDISK(t) && !ISCACHE(t)) {
		(void) free ((char *) left);
		(void) free ((char *) right);
	}

	h->h_flags |= F_DIRTY;

	return (RET_SUCCESS);
}

/*
 *  _BT_DOPSPLIT -- Do the work of splitting a page
 *
 *	This routine takes two page pointers and splits the data on the
 *	current page of the btree between them.
 *
 *	We do a lot of work here to handle duplicate keys on a page; we
 *	have to place these keys carefully to guarantee that later searches
 *	will find them correctly.  See comments in the code below for details.
 *
 *	Parameters:
 *		t -- tree to split
 *		left -- pointer to page to get left half of the data
 *		right -- pointer to page to get right half of the data
 *
 *	Returns:
 *		None.
 */

static
_bt_dopsplit(t, left, right)
	BTREE_P t;
	BTHEADER *left;
	BTHEADER *right;
{
	BTHEADER *h = t->bt_curpage;
	size_t psize;
	char *where;
	BTHEADER *where_h;
	index_t where_i;
	int nbytes, dsize, fixedsize, freespc;
	index_t i;
	index_t save_lower, save_upper, save_i;
	index_t switch_i;
	char *save_key;
	DATUM *d;
	CURSOR *c;
	index_t top;
	int free_save;
	pgno_t chain;
	int ignore;

	/*
	 *  Our strategy is to put half the bytes on each page.  We figure
	 *  out how many bytes we have total, and then move items until
	 *  the last item moved put at least 50% of the data on the left
	 *  page.
	 */
	save_key = (char *) NULL;
	psize = (int) t->bt_psize;
	where = ((char *) left) + psize;
	where_h = left;
	where_i = 0;
	nbytes = psize - (int) ((char *) &(h->h_linp[0]) - ((char *) h));
	freespc = nbytes;

	top = NEXTINDEX(h);
	if (h->h_flags & F_LEAF)
		fixedsize = (sizeof(DATUM) - sizeof(char));
	else
		fixedsize = (sizeof(IDATUM) - sizeof(char));

	save_key = (char *) NULL;

	/* move data */
	for (i = 0; i < top; i++) {

		/*
		 *  Internal and leaf pages have different layouts for
		 *  data items, but in both cases the first entry in the
		 *  data item is a size_t.
		 */
		d = (DATUM *) GETDATUM(h,i);
		if (h->h_flags & F_LEAF) {
			dsize = d->d_ksize + d->d_dsize + fixedsize;
		} else {
			dsize = d->d_ksize + fixedsize;
		}

		/*
		 *  If a page contains duplicate keys, we have to be
		 *  careful about splits.  A sequence of duplicate keys
		 *  may not begin in the middle of one page and end in
		 *  the middle of another; it must begin on a page boundary,
		 *  in order for searches on the internal nodes to work
		 *  correctly.
		 */
		if (where_h == left) {
			if (save_key == (char *) NULL) {
				if (h->h_flags & F_LEAF) {
					if (d->d_flags & D_BIGKEY) {
						free_save = TRUE;
						bcopy(&(d->d_bytes[0]),
						     (char *) &chain,
						     sizeof(chain));
						if (_bt_getbig(t, chain,
							       &save_key,
							       &ignore)
						    == RET_ERROR)
							return (RET_ERROR);
					} else {
						free_save = FALSE;
						save_key = (char *) &(d->d_bytes[0]);
					}
				} else {
					IDATUM *id = (IDATUM *) d;

					if (id->i_flags & D_BIGKEY) {
						free_save = TRUE;
						bcopy(&(id->i_bytes[0]),
						     (char *) &chain,
						     sizeof(chain));
						if (_bt_getbig(t, chain,
							       &save_key,
							       &ignore)
						    == RET_ERROR)
							return (RET_ERROR);
					} else {
						free_save = FALSE;
						save_key = (char *)
							&(id->i_bytes[0]);
					}
				}
				save_i = 0;
				save_lower = where_h->h_lower;
				save_upper = where_h->h_upper;
			} else {
				if (_bt_cmp(t, save_key, i) != 0) {
					save_lower = where_h->h_lower;
					save_upper = where_h->h_upper;
					save_i = i;
				}
				if (h->h_flags & F_LEAF) {
					if (free_save)
						(void) free(save_key);
					if (d->d_flags & D_BIGKEY) {
						free_save = TRUE;
						bcopy(&(d->d_bytes[0]),
						     (char *) &chain,
						     sizeof(chain));
						if (_bt_getbig(t, chain,
							       &save_key,
							       &ignore)
						    == RET_ERROR)
							return (RET_ERROR);
					} else {
						free_save = FALSE;
						save_key = (char *) &(d->d_bytes[0]);
					}
				} else {
					IDATUM *id = (IDATUM *) d;

					if (id->i_flags & D_BIGKEY) {
						free_save = TRUE;
						bcopy(&(id->i_bytes[0]),
						     (char *) &chain,
						     sizeof(chain));
						if (_bt_getbig(t, chain,
							       &save_key,
							       &ignore)
						    == RET_ERROR)
							return (RET_ERROR);
					} else {
						free_save = FALSE;
						save_key = (char *)
							&(id->i_bytes[0]);
					}
				}
			}
		}

		/* copy data and update page state */
		where -= LONGALIGN(dsize);
		(void) bcopy((char *) d, (char *) where, dsize);
		where_h->h_upper = where_h->h_linp[where_i] =
			(index_t) (where - (int) where_h);
		where_h->h_lower += sizeof(index_t);
		where_i++;

		/* if we've moved half, switch to the right-hand page */
		nbytes -= LONGALIGN(dsize) + sizeof(index_t);
		if ((freespc - nbytes) > nbytes) {
			nbytes = 2 * freespc;

			/* identical keys go on the same page */
			if (save_i > 0) {
				/* i gets incremented at loop bottom... */
				i = save_i - 1;
				where_h->h_lower = save_lower;
				where_h->h_upper = save_upper;
			}
			where = ((char *) right) + psize;
			where_h = right;
			switch_i = where_i;
			where_i = 0;
		}
	}

	/*
	 *  If there was an active scan on the database, and we just
	 *  split the page that the cursor was on, we may need to
	 *  adjust the cursor to point to the same entry as before the
	 *  split.
	 */

	c = &(t->bt_cursor);
	if ((t->bt_flags & BTF_SEQINIT)
	    && (c->c_pgno == h->h_pgno)
	    && (c->c_index >= switch_i)) {
		c->c_pgno = where_h->h_pgno;
		c->c_index -= where_i;
	}
	return (RET_SUCCESS);
}

/*
 *  _BT_INSERTI -- Insert IDATUM on current page in the btree.
 *
 *	This routine handles insertions to internal pages after splits
 *	lower in the tree.  On entry, t->bt_curpage is the page to get
 *	the new IDATUM.  We are also given pgno, the page number of the
 *	IDATUM that is immediately left of the new IDATUM's position.
 *	This guarantees that the IDATUM for the right half of the page
 *	after a split goes next to the IDATUM for its left half.
 *
 *	Parameters:
 *		t -- tree in which to do insertion.
 *		id -- new IDATUM to insert
 *		pgno -- page number of IDATUM left of id's position
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 */

static int
_bt_inserti(t, id, pgno)
	BTREE_P t;
	IDATUM *id;
	pgno_t pgno;
{
	BTHEADER *h = t->bt_curpage;
	index_t next, i;
	IDATUM *idx;
	char *key;
	pgno_t chain;
	int free_key;
	int ignore;

	if (id->i_flags & D_BIGKEY) {
		free_key = TRUE;
		bcopy(&(id->i_bytes[0]), (char *) &chain, sizeof(chain));
		if (_bt_getbig(t, chain, &key, &ignore) == RET_ERROR)
			return (RET_ERROR);
	} else {
		free_key = FALSE;
		key = &(id->i_bytes[0]);
	}
	i = _bt_binsrch(t, key);

	next = NEXTINDEX(h);
	while (i < next && _bt_cmp(t, key, i) >= 0)
		i++;

	if (free_key)
		(void) free(key);

	/* okay, now we're close; find adjacent IDATUM */
	for (;;) {
		idx = (IDATUM *) GETDATUM(h,i);
		if (idx->i_pgno == pgno) {
			i++;
			break;
		}
		--i;
	}

	/* correctly positioned, do the insertion */
	return (_bt_insertat(t, id, i));
}

/*
 *  _BT_INSERTAT -- Insert a datum at a given location on the current page.
 *
 *	This routine does insertions on both leaf and internal pages.
 *
 *	Parameters:
 *		t -- tree in which to do insertion.
 *		p -- DATUM or IDATUM to insert.
 *		index -- index in line pointer array to put this item.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Will rearrange line pointers to make space for the new
 *		entry.  This means that any scans currently active are
 *		invalid after this.
 *
 *	Warnings:
 *		There must be sufficient room for the new item on the page.
 */

static int
_bt_insertat(t, p, index)
	BTREE_P t;
	char *p;
	index_t index;
{
	IDATUM *id = (IDATUM *) p;
	DATUM *d = (DATUM *) p;
	BTHEADER *h;
	CURSOR *c;
	index_t nxtindex;
	char *src, *dest;
	int nbytes;

	/* insertion may confuse an active scan.  fix it. */
	c = &(t->bt_cursor);
	if (t->bt_flags & BTF_SEQINIT && t->bt_curpage->h_pgno == c->c_pgno)
		if (_bt_fixscan(t, index, d, INSERT) == RET_ERROR)
			return (RET_ERROR);

	h = t->bt_curpage;
	nxtindex = (index_t) NEXTINDEX(h);

	/*
	 *  If we're inserting at the middle of the line pointer array,
	 *  copy pointers that will follow the new one up on the page.
	 */

	if (index < nxtindex) {
		src = (char *) &(h->h_linp[index]);
		dest = (char *) &(h->h_linp[index + 1]);
		nbytes = (h->h_lower - (src - ((char *) h)))
			 + sizeof(h->h_linp[0]);
		(void) bcopy(src, dest, nbytes);
	}

	/* compute size and copy data to page */
	if (h->h_flags & F_LEAF) {
		nbytes = d->d_ksize + d->d_dsize
			 + (sizeof(DATUM) - sizeof(char));
	} else {
		nbytes = id->i_size + (sizeof(IDATUM) - sizeof(char));
	}
	dest = (((char *) h) + h->h_upper) - LONGALIGN(nbytes);
	(void) bcopy((char *) p, dest, nbytes);

	/* update statistics */
	dest -= (int) h;
	h->h_linp[index] = (index_t) dest;
	h->h_upper = (index_t) dest;
	h->h_lower += sizeof(index_t);

	/* we're done */
	h->h_flags |= F_DIRTY;

	return (RET_SUCCESS);
}

/*
 *  _BT_BINSRCH -- Do a binary search for a given key on the current page.
 *
 *	Searches on internal pages are handled slightly differently from
 *	searches on leaf pages.  This is because internal page searches
 *	find the largest item <= key in the tree, and leaf searches find
 *	the smallest item >= key.  This guarantees that leaf page searches
 *	leave us pointing at the item's correct position, and internal
 *	searches descend the tree correctly.
 *
 *	Parameters:
 *		t -- tree to search
 *		key -- key we're looking for
 *
 *	Returns:
 *		Index of the line pointer array entry for the (closest)
 *		match to key on the current page, with "closest" as defined
 *		above.
 */

static index_t
_bt_binsrch(t, key)
	BTREE_P t;
	char *key;
{
	index_t lbound, ubound, cur;
	BTHEADER *h = t->bt_curpage;
	IDATUM *id;
	int match = 0;
	int r;

	lbound = 0;
	ubound = NEXTINDEX(h);
	if (ubound > 0)
		--ubound;

	/* do a binary search on the current page */
	while ((ubound - lbound) > 1) {
		cur = lbound + ((ubound - lbound) / 2);
		r = _bt_cmp(t, key, cur);

		if (r > 0)
			lbound = cur + 1;
		else if (r < 0)
			ubound = cur;
		else {
			match++;
			break;
		}
	}

	/*
	 *  At this point, the binary search terminated because the endpoints
	 *  got too close together, or we have a match.  Figure out which
	 *  case applies, decide what to do based on the page type (leaf or
	 *  internal), and do the right thing.
	 */
	if (match) {
		return (cur);
	} else if (ubound != lbound) {
		if (h->h_flags & F_LEAF) {
			r = _bt_cmp(t, key, lbound);
			if (r <= 0) {
				return (lbound);
			}
		} else {
			r = _bt_cmp(t, key, ubound);

			/* for internal nodes, move as far left as possible */
			if (r < 0) {
				r = _bt_cmp(t, key, lbound);
				if (r < 0 && lbound > 0)
					--lbound;
				return (lbound);
			} else {
				return (ubound);
			}
		}
	}

	if (h->h_flags & F_LEAF) {
		if (ubound < NEXTINDEX(h)) {
			r = _bt_cmp(t, key, ubound);
			if (r > 0)
				ubound++;
		}
	} else {
		/* for internal pages, move as far left as possible */
		if (ubound == NEXTINDEX(h))
			ubound--;

		while (_bt_cmp(t, key, ubound) < 0)
			ubound--;
	}
	return (ubound);
}

/*
E 3
 *  BT_SEQ -- Sequential scan interface.
 *
 *	This routine supports sequential scans on the btree.  If called with
 *	flags set to R_CURSOR, or if no seq scan has been initialized in the
 *	current tree, we initialize the scan.  Otherwise, we advance the scan
 *	and return the next item.
 *
 *	Scans can be either keyed or non-keyed.  Keyed scans basically have
 *	a starting point somewhere in the middle of the tree.  Non-keyed
 *	scans start at an endpoint.  Also, scans can be backward (descending
 *	order), forward (ascending order), or no movement (keep returning
 *	the same item).
 *
 *	Flags is checked every time we enter the routine, so the user can
 *	change directions on an active scan if desired.  The key argument
 *	is examined only when we initialize the scan, in order to position
 *	it properly.
 *
 *	Items are returned via the key and data arguments passed in.
 *
 *	Parameters:
 *		tree -- btree in which to do scan
 *		key -- key, used to position scan on initialization, and
 *		       used to return key components to the user.
 *		data -- used to return data components to the user.
 *		flags -- specify R_CURSOR, R_FIRST, R_LAST, R_NEXT, or
 *			 R_PREV.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR, or RET_SPECIAL if no more data
 *		exists in the tree in the specified direction.
 *
 *	Side Effects:
 *		Changes the btree's notion of the current position in the
 *		scan.
 *
 *	Warnings:
 *		The key and data items returned are static and will be
 *		overwritten by the next bt_get or bt_seq.
 */

I 3
int
E 3
D 9
bt_seq(tree, key, data, flags)
	BTREE tree;
	DBT *key;
	DBT *data;
E 9
I 9
bt_seq(dbp, key, data, flags)
	DB *dbp;
	DBT *key, *data;
E 9
D 6
	int flags;
E 6
I 6
	u_long flags;
E 6
{
D 9
	BTREE_P t = (BTREE_P) tree;
E 9
I 9
	BTREE_P t;
E 9
	BTHEADER *h;
	DATUM *d;
	int status;

I 9
	t = (BTREE_P)dbp->internal;

E 9
	/* do we need to initialize the scan? */
	if (flags == R_CURSOR || flags == R_LAST || flags == R_FIRST
	    || !(t->bt_flags & BTF_SEQINIT)) {

		/* initialize it */
		status = _bt_seqinit(t, key, flags);
	} else {
		/* just advance the current scan pointer */
		status = _bt_seqadvance(t, flags);
	}

	key->size = data->size = 0;
D 7
	key->data = data->data = (char *) NULL;
E 7
I 7
	key->data = data->data = (u_char *) NULL;
E 7

	h = t->bt_curpage;

	/* is there a valid item at the current scan location? */
	if (status == RET_SPECIAL) {
		if (flags == R_NEXT) {
			if (t->bt_cursor.c_index >= NEXTINDEX(h)) {
				if (NEXTINDEX(h) > 0)
					t->bt_cursor.c_index = NEXTINDEX(h) - 1;
				else
					t->bt_cursor.c_index = 0;
			}
		} else {
			t->bt_cursor.c_index = 0;
		}
		return (RET_SPECIAL);
	} else if (status == RET_ERROR)
E 10
I 10
	if ((root = mpool_new(t->bt_mp, &npg)) == NULL)
E 10
		return (RET_ERROR);

D 10
	/* okay, return the data */
	d = (DATUM *) GETDATUM(h, t->bt_cursor.c_index);

	return (_bt_buildret(t, d, data, key));
E 10
I 10
	if (npg != P_ROOT)
		return (RET_ERROR);
	root->pgno = npg;
	root->prevpg = root->nextpg = P_INVALID;
	root->lower = BTDATAOFF;
	root->upper = t->bt_psize;
	root->flags = P_BLEAF;
I 11
D 27
	bzero(meta, t->bt_psize);
E 27
I 27
	memset(meta, 0, t->bt_psize);
E 27
E 11
	mpool_put(t->bt_mp, meta, MPOOL_DIRTY);
	mpool_put(t->bt_mp, root, MPOOL_DIRTY);
	return (RET_SUCCESS);
E 10
}

D 10
/*
D 3
 *  _BT_BUILDRET -- Build return key/data pair as a result of search or scan.
 *
 *	This routine manages the statically allocated buffers in which we
 *	return data to the user.
 *
 *	Parameters:
 *		t -- btree from which to return datum
 *		d -- DATUM to be returned to the user.
 *		data -- data argument supplied by user for return
 *		key -- key argument supplied by user for return
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		May free and reallocate static buffers, if the data
 *		we want to return is bigger than the space we have to
 *		do so.
 */

static int
_bt_buildret(t, d, data, key)
	BTREE_P t;
	DATUM *d;
	DBT *data;
	DBT *key;
{
	static int _data_s = 0;
	static int _key_s = 0;
	static char *_data = (char *) NULL;
	static char *_key = (char *) NULL;
	char *from, *where, *top;
	pgno_t save;
	pgno_t chain;
	size_t nbytes;
	size_t nhere;
	BTHEADER *h;

	if (d->d_flags & D_BIGKEY) {
		if (_key != (char *) NULL)
			(void) free(_key);
		(void) bcopy((char *) &(d->d_bytes[0]),
		      	     (char *) &chain,
		      	     sizeof(chain));
		if (_bt_getbig(t, chain, &_key, &_key_s) == RET_ERROR)
			return (RET_ERROR);
		key->data = _key;
		key->size = _key_s;
	} else {
		/* need more space for key? */
		if (d->d_ksize > _key_s) {
			if (_key != (char *) NULL)
				(void) free (_key);
			if ((_key = (char *) malloc((unsigned) d->d_ksize))
			    == (char *) NULL)
				return (RET_ERROR);
			_key_s = d->d_ksize;
		}

		key->data = _key;
		if ((key->size = d->d_ksize) > 0)
			(void) bcopy(&(d->d_bytes[0]),
				     _key,
				     (int) d->d_ksize);
	}

	if (d->d_flags & D_BIGDATA) {
		if (_data != (char *) NULL)
			(void) free(_data);
		(void) bcopy(&(d->d_bytes[d->d_ksize]),
		      	     (char *) &chain,
		      	     sizeof(chain));
		if (_bt_getbig(t, chain, &_data, &_data_s) == RET_ERROR)
			return (RET_ERROR);
		data->data = _data;
		data->size = _data_s;
	} else {
		/* need more space for data? */
		if (d->d_dsize > _data_s) {
			if (_data != (char *) NULL)
				(void) free (_data);
			if ((_data = (char *) malloc((unsigned) d->d_dsize))
			    == (char *) NULL)
				return (RET_ERROR);
			_data_s = d->d_dsize;
		}

		data->data = _data;

		if ((data->size = d->d_dsize) > 0)
			(void) bcopy(&(d->d_bytes[d->d_ksize]),
				      _data,
				      d->d_dsize);
	}

	return (RET_SUCCESS);
}

/*
 *  _BT_SEQINIT -- Initialize a sequential scan on the btree.
 *
 *	Sets the tree's notion of the current scan location correctly
 *	given a key and a direction.
 *
 *	Parameters:
 *		t -- tree in which to initialize scan
 *		key -- key for initial scan position
 *		flags -- R_NEXT, R_PREV
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR, or RET_SPECIAL if there's no data
 *		in the tree to scan.
 *
 *	Side Effects:
 *		Changes current scan position for the tree.  Almost certainly
 *		changes current page, as well.  Sets BTF_SEQINIT bit in tree
 *		flags, so that we know we've initialized a scan.
 */

static int
_bt_seqinit(t, key, flags)
	BTREE_P t;
	DBT *key;
	int flags;
{
	BTITEM *item;
	BTHEADER *h;
	CURSOR *c;
	IDATUM *id;
	pgno_t pgno;
	index_t index;
	index_t last;

	/*
	 *  Figure out if we really have to search for the key that the
	 *  user supplied.  If key is null, then this is an unkeyed scan
	 *  and we can just start from an endpoint.
	 */

	c = &(t->bt_cursor);

	if (flags == R_CURSOR) {
		if (key->data != (char *) NULL) {

			/* key supplied, find it */
			item = _bt_search(t, key);
			c->c_index = item->bti_index;
			c->c_pgno = t->bt_curpage->h_pgno;
		} else {
			errno = EINVAL;
			return (RET_ERROR);
		}

	} else {

		/*
		 *  Unkeyed scan.  For backward scans, find the last item
		 *  in the tree; for forward scans, find the first item.
		 */

		if (_bt_getpage(t, P_ROOT) == RET_ERROR)
			return (RET_ERROR);
		h = t->bt_curpage;
		if (flags == R_LAST || flags == R_PREV) {

			/* backward scan */
			while (!(h->h_flags & F_LEAF)) {
				last = NEXTINDEX(h) - 1;
				id = (IDATUM *) GETDATUM(h,last);
				if (_bt_getpage(t, id->i_pgno) == RET_ERROR)
					return (RET_ERROR);
				h = t->bt_curpage;
			}

			/* skip empty pages */
			while (NEXTINDEX(h) == 0 && h->h_prevpg != P_NONE) {
				if (_bt_getpage(t, h->h_prevpg) == RET_ERROR)
					return (RET_ERROR);
				h = t->bt_curpage;
			}

			c->c_pgno = h->h_pgno;
			if (NEXTINDEX(h) > 0)
				c->c_index = NEXTINDEX(h) - 1;
			else
				c->c_index = 0;
		} else if (flags == R_FIRST || flags == R_NEXT) {
			/* forward scan */
			while (!(h->h_flags & F_LEAF)) {
				id = (IDATUM *) GETDATUM(h,0);
				if (_bt_getpage(t, id->i_pgno) == RET_ERROR)
					return (RET_ERROR);
				h = t->bt_curpage;
			}

			/* skip empty pages */
			while (NEXTINDEX(h) == 0 && h->h_nextpg != P_NONE) {
				if (_bt_getpage(t, h->h_nextpg) == RET_ERROR)
					return (RET_ERROR);
				h = t->bt_curpage;
			}

			c->c_pgno = h->h_pgno;
			c->c_index = 0;
		} else {
			/* no flags passed in */
			errno = EINVAL;
			return (RET_ERROR);
		}
	}

	/* okay, scan is initialized */
	t->bt_flags |= BTF_SEQINIT;

	if (c->c_index == NEXTINDEX(t->bt_curpage))
		return (RET_SPECIAL);

	return (RET_SUCCESS);
}

/*
 *  _BT_SEQADVANCE -- Advance the sequential scan on this tree.
 *
 *	Moves the current location pointer for the scan on this tree one
 *	spot in the requested direction.
 *
 *	Parameters:
 *		t -- btree being scanned
 *		flags -- for R_NEXT, R_PREV
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR, or RET_SPECIAL if there is no
 *		more data in the specified direction.
 *
 *	Side Effects:
 *		May change current page.
 */

static int
_bt_seqadvance(t, flags)
	BTREE_P t;
	int flags;
{
	BTHEADER *h;
	CURSOR *c;
	index_t index;

	c = &(t->bt_cursor);
	index = c->c_index;

	if (_bt_getpage(t, c->c_pgno) == RET_ERROR)
		return (RET_ERROR);
	h = t->bt_curpage;

	/* by the time we get here, don't need the cursor key anymore */
	if (c->c_key != (char *) NULL)
		(void) free(c->c_key);

	if (flags == R_NEXT) {

		/*
		 *  This is a forward scan.  If the cursor is pointing
		 *  at a virtual record (that is, it was pointing at
		 *  a record that got deleted), then we should return
		 *  the record it's pointing at now.  Otherwise, we
		 *  should advance the scan.  In either case, we need
		 *  to be careful not to run off the end of the current
		 *  page.
		 */

		if (c->c_flags & CRSR_BEFORE) {

			if (index >= NEXTINDEX(h)) {
				/* out of items on this page, get next page */
				if (h->h_nextpg == P_NONE) {
					/* tell caller we're done... */
					c->c_index = NEXTINDEX(h);
					return (RET_SPECIAL);
				}

				/* skip empty pages */
				do {
					if (_bt_getpage(t, h->h_nextpg)
					    == RET_ERROR) {
						c->c_index = NEXTINDEX(h);
						return (RET_ERROR);
					}
					h = t->bt_curpage;
					c->c_pgno = h->h_pgno;
				} while (NEXTINDEX(h) == 0
					 && h->h_nextpg != P_NONE);

				if (NEXTINDEX(h) == 0) {
					/* tell caller we're done */
					c->c_index = NEXTINDEX(h);
					return (RET_SPECIAL);
				}
				index = 0;
			}
			c->c_flags &= ~CRSR_BEFORE;

		} else if (++index >= NEXTINDEX(h)) {

			/* out of items on this page, get next page */
			if (h->h_nextpg == P_NONE) {
				/* tell caller we're done... */
				c->c_index = NEXTINDEX(h);
				return (RET_SPECIAL);
			}

			/* skip empty pages */
			do {
				if (_bt_getpage(t, h->h_nextpg) == RET_ERROR) {
					c->c_index = NEXTINDEX(h);
					return (RET_ERROR);
				}
				h = t->bt_curpage;
				c->c_pgno = h->h_pgno;
			} while (NEXTINDEX(h) == 0 && h->h_nextpg != P_NONE);

			if (NEXTINDEX(h) == 0) {
				/* tell caller we're done */
				c->c_index = NEXTINDEX(h);
				return (RET_SPECIAL);
			}
			index = 0;
		}
	} else if (flags == R_PREV) {

		/* for backward scans, life is substantially easier */
		c->c_flags &= ~CRSR_BEFORE;
		if (c->c_key != (char *) NULL) {
			(void) free(c->c_key);
			c->c_key = (char *) NULL;
		}

		if (index == 0) {

			/* we may be done */
			c->c_index = 0;

			/* out of items on this page, get next page */
			if (h->h_prevpg == P_NONE)
				return (RET_SPECIAL);

			/* skip empty pages */
			do {
				if (_bt_getpage(t, h->h_prevpg) == RET_ERROR)
					return (RET_ERROR);
				h = t->bt_curpage;
				c->c_pgno = h->h_pgno;
			} while (NEXTINDEX(h) == 0 && h->h_prevpg != P_NONE);

			if (NEXTINDEX(h) == 0)
				return (RET_SPECIAL);

			index = NEXTINDEX(h) - 1;
		} else
			--index;
	} else {
		/* must specify a direction */
		errno = EINVAL;
		return (RET_ERROR);
	}

	c->c_index = index;
	return (RET_SUCCESS);
}

/*
E 3
 *  BT_CLOSE -- Close a btree
 *
 *	Parameters:
 *		tree -- tree to close
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Frees space occupied by the tree.
 */

int
D 9
bt_close(tree)
	BTREE tree;
E 9
I 9
bt_close(dbp)
	DB *dbp;
E 10
I 10
static int
tmp()
E 10
E 9
{
D 9
	BTREE_P t = (BTREE_P) tree;
	int i;
	BTHEADER *h;
	char *cache;
E 9
D 10
	struct HTBUCKET *b, *sb;
I 9
	BTREE_P t;
	BTHEADER *h;
E 9
	HTABLE ht;
D 9
	int fd;
E 9
I 9
	int fd, i;
	char *cache;
E 10
I 10
	sigset_t set, oset;
	int fd;
	char *envtmp;
	char path[MAXPATHLEN];
E 10

D 10
	t = (BTREE_P)dbp->internal;
E 10
I 10
	envtmp = getenv("TMPDIR");
	(void)snprintf(path,
	    sizeof(path), "%s/bt.XXXXXX", envtmp ? envtmp : "/tmp");
E 10
E 9

D 10
	if (t->bt_cursor.c_key != (char *) NULL)
		(void) free(t->bt_cursor.c_key);

	if (!ISDISK(t)) {
		/* in-memory tree, release hash table memory */
		ht = t->bt_s.bt_ht;
		for (i = 0; i < HTSIZE; i++) {
			if ((b = ht[i]) == (struct HTBUCKET *) NULL)
				break;
			do {
				sb = b;
				(void) free((char *) b->ht_page);
				b = b->ht_next;
				(void) free((char *) sb);
			} while (b != (struct HTBUCKET *) NULL);
		}
		(void) free ((char *) ht);
		(void) free ((char *) t);
		return (RET_SUCCESS);
	}

	if ((t->bt_flags & BTF_ISWRITE) && !(t->bt_flags & BTF_METAOK)) {
I 3
		if (_bt_wrtmeta(t) == RET_ERROR)
			return (RET_ERROR);
	}

	if (t->bt_curpage != (BTHEADER *) NULL) {
		h = t->bt_curpage;
		if (h->h_flags & F_DIRTY) {
			if (_bt_write(t, h, RELEASE) == RET_ERROR)
				return (RET_ERROR);
		} else {
			if (_bt_release(t, h) == RET_ERROR)
				return (RET_ERROR);
		}

		/* flush and free the cache, if there is one */
		if (ISCACHE(t)) {
			cache = t->bt_s.bt_d.d_cache;
			if (lrusync(cache) == RET_ERROR)
				return (RET_ERROR);
			lrufree(cache);
		}
		(void) free ((char *) h);
	}

	fd = t->bt_s.bt_d.d_fd;
	(void) free ((char *) t);
	return (close(fd));
E 10
I 10
D 18
	sigfillset(&set);
E 18
I 18
	(void)sigfillset(&set);
E 18
	(void)sigprocmask(SIG_BLOCK, &set, &oset);
	if ((fd = mkstemp(path)) != -1)
		(void)unlink(path);
	(void)sigprocmask(SIG_SETMASK, &oset, NULL);
	return(fd);
I 28
}

static int
byteorder()
{
D 36
	u_long x;			/* XXX: 32-bit assumption. */
E 36
I 36
	u_int32_t x;
E 36
D 29
	char *p;
E 29
I 29
	u_char *p;
E 29

	x = 0x01020304;
	p = (u_char *)&x;
	switch (*p) {
	case 1:
		return (BIG_ENDIAN);
	case 4:
		return (LITTLE_ENDIAN);
	default:
		return (0);
	}
I 32
}

int
__bt_fd(dbp)
        const DB *dbp;
{
	BTREE *t;

	t = dbp->internal;

I 34
	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	/* In-memory database can't have a file descriptor. */
E 34
	if (ISSET(t, B_INMEM)) {
		errno = ENOENT;
		return (-1);
	}
	return (t->bt_fd);
E 32
E 28
E 10
}
E 3
D 3
		if (_bt_wrtmeta(t) == RET_ERROR)
			return (RET_ERROR);
	}

	if (t->bt_curpage != (BTHEADER *) NULL) {
		h = t->bt_curpage;
		if (h->h_flags & F_DIRTY) {
			if (_bt_write(t, h, RELEASE) == RET_ERROR)
				return (RET_ERROR);
		} else {
			if (_bt_release(t, h) == RET_ERROR)
				return (RET_ERROR);
		}

		/* flush and free the cache, if there is one */
		if (ISCACHE(t)) {
			cache = t->bt_s.bt_d.d_cache;
			lrusync(cache);
			lrufree(cache);
		}
I 2
		(void) free ((char *) h);
	}

	fd = t->bt_s.bt_d.d_fd;
	(void) free ((char *) t);
	return (close(fd));
E 2
D 2
		(void) free ((char *) h);
	}

	fd = t->bt_s.bt_d.d_fd;
	(void) free ((char *) t);
	return (close(fd));
E 2
}

/*
 *  _BT_ALLOCPG -- allocate a new page in the btree.
 *
 *	This is called when we split a page, to get space to do the split.
 *	For disk btrees, these pages are released when the split is done.
 *	For memory btrees, they are not.
 *
 *	Parameters:
 *		t -- tree in which to do split
 *
 *	Returns:
 *		Pointer to the newly-allocated page
 */

static BTHEADER *
_bt_allocpg(t)
	BTREE_P t;
{
	BTHEADER *h = t->bt_curpage;
	BTHEADER *nh;
	char *cache;
	int nbytes;

	/* if we have a cache, let the cache code do the work */
	if (ISDISK(t) && ISCACHE(t)) {
		nh = (BTHEADER *) lrugetnew(t->bt_s.bt_d.d_cache,
					    t->bt_npages + 1,
					    &nbytes);
	} else {
		nh = (BTHEADER *) malloc((unsigned) t->bt_psize);
	}

	if (nh != (BTHEADER *) NULL) {
		nh->h_pgno = nh->h_prevpg = nh->h_nextpg = P_NONE;
		nh->h_flags = h->h_flags;
		nh->h_lower = (index_t)
				(((char *) &(nh->h_linp[0])) - ((char *) nh));
		nh->h_upper = t->bt_psize;
	}

	return (nh);
}

/*
 *  _BT_WRITE -- Write a specific page to a btree file.
 *
 *	Parameters:
 *		t -- btree to get the page
 *		h -- page to write
 *		relflag -- (int) this page may/may not be released
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Writes a metadata page if none has been written yet.
 */

static int
_bt_write(t, h, relflag)
	BTREE_P t;
	BTHEADER *h;
	int relflag;
{
	long pos;
	int htindex;
	HTBUCKET *b;
	char *cache;
	BTMETA m;
	pgno_t pgno;

	h->h_flags &= ~F_DIRTY;
	if (ISDISK(t)) {

		/* if we haven't done so yet, write the metadata */
		if (!(t->bt_flags & BTF_METAOK)) {
			if (_bt_wrtmeta(t) == RET_ERROR)
				return (RET_ERROR);
		}

		pgno = h->h_pgno;


		/* if we have a cache, let the cache code do the work */
		if ((cache = t->bt_s.bt_d.d_cache) != (char *) NULL) {
			if (lruwrite(cache, pgno) == RET_ERROR)
				return (RET_ERROR);
			if (relflag && lrurelease(cache, pgno) == RET_ERROR)
				return (RET_ERROR);
				
		} else {
			(void) _bt_pgout(h, (char *) t->bt_lorder);
			/* now write the current page */
			pos = (long) (pgno * t->bt_psize);
			if (lseek(t->bt_s.bt_d.d_fd, pos, L_SET) != pos)
				return (RET_ERROR);
			if (write(t->bt_s.bt_d.d_fd, h, t->bt_psize)
			    < t->bt_psize)
				return (RET_ERROR);
			if (!relflag)
				(void) _bt_pgin(h, (char *) t->bt_lorder);
		}
	} else {
		/* in-memory btree */
		htindex = HASHKEY(h->h_pgno);

		/* see if we need to overwrite existing entry */
		for (b = t->bt_s.bt_ht[htindex];
		     b != (HTBUCKET *) NULL;
		     b = b->ht_next) {
			if (b->ht_pgno == h->h_pgno) {
				b->ht_page = h;
				return (RET_SUCCESS);
			}
		}

		/* new entry, write it */
		b = (HTBUCKET *) malloc((unsigned) sizeof (HTBUCKET));
		if (b == (HTBUCKET *) NULL)
			return (RET_ERROR);

		b->ht_pgno = h->h_pgno;
		b->ht_page = h;
		b->ht_next = t->bt_s.bt_ht[htindex];
		t->bt_s.bt_ht[htindex] = b;
	}
	return (RET_SUCCESS);
}

/*
 *  _BT_RELEASE -- Release a locked-down cache page
 *
 *	During page splits, we want to force pages out to the cache
 *	before we actually release them, in some cases.  This routine
 *	releases such a page when it is no longer needed.
 *
 *	Parameters:
 *		t -- btree in which to release page
 *		h -- page to release
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		None.
 */

static int
_bt_release(t, h)
	BTREE_P t;
	BTHEADER *h;
{
	if (ISDISK(t) && ISCACHE(t)) {
		if (lrurelease(t->bt_s.bt_d.d_cache, h->h_pgno) < 0)
			return (RET_ERROR);
	}
	return (RET_SUCCESS);
}

/*
 *  _BT_WRTMETA -- Write metadata to the btree.
 *
 *	Parameters:
 *		t -- tree to which to write
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 */

static int
_bt_wrtmeta(t)
	BTREE_P t;
{
	BTMETA m;

	if (lseek(t->bt_s.bt_d.d_fd, 0l, L_SET) != 0l)
		return (RET_ERROR);

	/* lorder has to be in host-independent format */
	m.m_lorder = (u_long) htonl((long) t->bt_lorder);

	m.m_magic = BTREEMAGIC;
	m.m_version = BTREEVERSION;
	m.m_psize = t->bt_psize;
	m.m_free = t->bt_free;
	m.m_flags = t->bt_flags & BTF_NODUPS;

	if (t->bt_lorder != BYTE_ORDER) {
		BLSWAP(m.m_magic);
		BLSWAP(m.m_version);
		BLSWAP(m.m_psize);
		BLSWAP(m.m_free);
		BLSWAP(m.m_flags);
	}

	if (write(t->bt_s.bt_d.d_fd, &m, sizeof(m))
	    != sizeof(m)) {
		return (RET_ERROR);
	}

	t->bt_flags |= BTF_METAOK;

	return (RET_SUCCESS);
}

#ifdef DEBUG
void
_btdump(tree)
	BTREE tree;
{
	BTREE_P t = (BTREE_P) tree;
	DATUM *d;
	IDATUM *id;
	BTHEADER *h;
	pgno_t npages;
	pgno_t i;
	index_t cur, top;

	npages = t->bt_npages;
	(void) printf("\"%s\" fd %d pgsz %d curpg %d @ 0x%lx",
		t->bt_fname, t->bt_s.bt_d.d_fd,
		t->bt_psize, t->bt_curpage);
	(void) printf("npg %d cmp 0x%lx flags=(", npages, t->bt_compare);
	if (t->bt_flags & BTF_SEQINIT)
		(void) printf("BTF_SEQINIT");
	(void) printf(")\n");

	for (i = P_ROOT; i <= npages; i++) {
		if (_bt_getpage(t, i) == RET_ERROR)
			_punt();
		h = t->bt_curpage;
		top = NEXTINDEX(h);
		(void) printf("    page %d:\n", i);
		(void) printf("\tpgno %d prev %d next %d\n",
			h->h_pgno, h->h_prevpg, h->h_nextpg);
		(void) printf("\tlower %d upper %d nextind %d flags (",
			h->h_lower, h->h_upper, top);
		if (h->h_flags & F_LEAF)
			(void) printf("F_LEAF");
		else
			(void) printf("<internal>");
		if (h->h_flags & F_DIRTY)
			(void) printf("|F_DIRTY");
		if (h->h_flags & F_PRESERVE)
			(void) printf("|F_PRESERVE");
		if (h->h_flags & F_CONT) {
			(void) printf("|F_CONT)");
			if (h->h_prevpg == P_NONE) {
				size_t longsz;
				(void) bcopy((char *) &(h->h_linp[0]),
					      (char *) &longsz,
					      sizeof(longsz));
				printf("\n\t\t(chain start, data length %ld)",
					longsz);
			}
			printf("\n");
			continue;
		}
		(void) printf(")\n");
		for (cur = 0; cur < top; cur++) {
			(void) printf("\t  [%d] off %d ", cur, h->h_linp[cur]);
			if (h->h_flags & F_LEAF) {
				d = (DATUM *) GETDATUM(h,cur);
				(void) printf("ksize %d", d->d_ksize);
				if (d->d_flags & D_BIGKEY)
					(void) printf(" (indirect)");
				(void) printf("; dsize %d", d->d_dsize);
				if (d->d_flags & D_BIGDATA)
					(void) printf(" (indirect)");
			} else {
				id = (IDATUM *) GETDATUM(h,cur);
				(void) printf("size %d pgno %d",
					id->i_size, id->i_pgno);
				if (id->i_flags & D_BIGKEY)
					(void) printf(" (indirect)");
			}
			(void) printf("\n");
		}
		(void) printf("\n");
	}
}
#endif /* DEBUG */

/*
 *  _BT_CMP -- Compare a key to a given item on the current page.
 *
 *	This routine is a wrapper for the user's comparison function.
 *
 *	Parameters:
 *		t -- tree in which to do comparison
 *		p -- pointer to one argument for the comparison function
 *		n -- index of item to supply second arg to comparison function
 *
 *	Returns:
 *		< 0 if p is < item at n
 *		= 0 if p is = item at n
 *		> 0 if p is > item at n
 */

static int
_bt_cmp(t, p, n)
	BTREE_P t;
	char *p;
	index_t n;
{
	BTHEADER *h;
	IDATUM *id;
	DATUM *d;
	char *arg;
	int ignore;
	int free_arg;
	pgno_t chain;
	int r;

	h = t->bt_curpage;

	/*
	 *  The left-most key at any level of the tree on internal pages
	 *  is guaranteed (artificially, by the code here) to be less than
	 *  any user key.  This saves us from having to update the leftmost
	 *  key when the user inserts a new key in the tree smaller than
	 *  anything we've seen yet.
	 */

	if (h->h_prevpg == P_NONE && !(h->h_flags & F_LEAF) && n == 0)
		return (1);

	if (h->h_flags & F_LEAF) {
		d = (DATUM *) GETDATUM(h,n);
		if (d->d_flags & D_BIGKEY) {
			free_arg = TRUE;
			bcopy(&(d->d_bytes[0]), (char *) &chain, sizeof(chain));
			if (_bt_getbig(t, chain, &arg, &ignore) == RET_ERROR)
				return (RET_ERROR);
		} else {
			free_arg = FALSE;
			arg = &(d->d_bytes[0]);
		}
	} else {
		id = (IDATUM *) GETDATUM(h,n);
		if (id->i_flags & D_BIGKEY) {
			free_arg = TRUE;
			bcopy(&(id->i_bytes[0]),
			      (char *) &chain,
			      sizeof(chain));
			if (_bt_getbig(t, chain, &arg, &ignore) == RET_ERROR)
				return (RET_ERROR);
		} else {
			free_arg = FALSE;
			arg = &(id->i_bytes[0]);
		}
	}
	r = (*(t->bt_compare))(p, arg);

	if (free_arg)
		(void) free(arg);

	return (r);
}

/*
 *  _BT_PUSH/_BT_POP -- Push/pop a parent page number on the parent stack.
 *
 *	When we descend the tree, we keep track of parent pages in order
 *	to handle splits on insertions.
 *
 *	Parameters:
 *		t -- tree for which to push parent
 *		pgno -- page number to push (_bt_push only)
 *
 *	Returns:
 *		None.
 */

static
_bt_push(t, pgno)
	BTREE_P t;
	pgno_t pgno;
{
	BTSTACK *new;

	new = (BTSTACK *) malloc((unsigned) sizeof(BTSTACK));
	new->bts_pgno = pgno;
	new->bts_next = t->bt_stack;
	t->bt_stack = new;
}

static
_bt_pop(t)
	BTREE_P t;
{
	BTSTACK *s;
	pgno_t p = P_NONE;

	if ((s = t->bt_stack) != (BTSTACK *) NULL) {
		p = s->bts_pgno;
		t->bt_stack = s->bts_next;
		(void) free ((char *) s);
	}
	return (p);
}

#ifdef DEBUG
_punt()
{
	int pid;

	pid = getpid();
	(void) kill(pid, SIGILL);
}
#endif /* DEBUG */
E 3
E 1
