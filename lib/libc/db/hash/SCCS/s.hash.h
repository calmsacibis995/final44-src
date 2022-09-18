h06759
s 00002/00001/00256
d D 8.2 94/02/21 15:09:08 bostic 9 8
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00255
d D 8.1 93/06/04 15:21:48 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00253
d D 5.7 93/05/23 13:03:27 bostic 7 6
c Use 4K page default. Use dynamically computed fill factor default 
c instead of fixed value.
e
s 00004/00001/00252
d D 5.6 91/09/08 13:45:17 bostic 6 5
c bump the hash version to 2; (allocate overflow pages beyond EOF)
e
s 00172/00173/00081
d D 5.5 91/09/04 12:56:23 bostic 5 4
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00002/00003/00252
d D 5.4 91/03/12 09:34:39 bostic 4 3
c Make all bucket and overflow addresses unsigned
c Make bitmaps demand loaded rather than load ahead on open
e
s 00002/00000/00253
d D 5.3 91/02/21 18:57:33 bostic 3 2
c count bitmaps so they can be free'd
e
s 00005/00006/00248
d D 5.2 91/02/19 10:31:09 bostic 2 1
c add "pinning" to the buffer pool
e
s 00254/00000/00000
d D 5.1 91/02/12 20:28:00 bostic 1 0
c date and time created 91/02/12 20:28:00 by bostic
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
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* Operations */
D 5
typedef enum { HASH_GET, HASH_PUT, HASH_PUTNEW, HASH_DELETE, 
		HASH_FIRST, HASH_NEXT } ACTION;
E 5
I 5
typedef enum {
	HASH_GET, HASH_PUT, HASH_PUTNEW, HASH_DELETE, HASH_FIRST, HASH_NEXT
} ACTION;
E 5

/* Buffer Management structures */
typedef struct _bufhead BUFHEAD;

struct _bufhead {
D 5
    BUFHEAD	*prev;		/* LRU links */
    BUFHEAD	*next;		/* LRU links */
    BUFHEAD	*ovfl;		/* Overflow page buffer header */
D 4
    int		addr;		/* Address of this page */
E 4
I 4
    u_int	 addr;		/* Address of this page */
E 4
    char	*page;		/* Actual page data */
D 2
    char	flags;	/* Combination of BUF_MOD, BUF_DISK, BUF_BUCKET */
};

/* Flag Values */
E 2
I 2
    char	flags;	
E 5
I 5
	BUFHEAD	*prev;		/* LRU links */
	BUFHEAD	*next;		/* LRU links */
	BUFHEAD	*ovfl;		/* Overflow page buffer header */
	u_int	 addr;		/* Address of this page */
	char	*page;		/* Actual page data */
	char	 flags;
E 5
E 2
#define	BUF_MOD		0x0001
#define BUF_DISK	0x0002
#define	BUF_BUCKET	0x0004
I 2
#define	BUF_PIN		0x0008
};
E 2

I 5
#define IS_BUCKET(X)	((X) & BUF_BUCKET)
E 5
I 2

E 2
D 5
#define IS_BUCKET(X)	(X & BUF_BUCKET)
E 5
I 5
typedef BUFHEAD **SEGMENT;
E 5

D 5
typedef BUFHEAD	**SEGMENT;

E 5
/* Hash Table Information */
typedef struct hashhdr {	/* Disk resident portion */
D 5
	int magic;	/* Magic NO for hash tables */
	int version;	/* Version ID */
	long lorder;	/* Byte Order */
	int bsize;	/* Bucket/Page Size */
	int bshift;	/* Bucket shift */
	int dsize;	/* Directory Size */
	int ssize;	/* Segment Size */
	int sshift;	/* Segment shift */
	int max_bucket;	/* ID of Maximum bucket in use */
	int high_mask;	/* Mask to modulo into entire table */
	int low_mask;	/* Mask to modulo into lower half of table */
	int ffactor;	/* Fill factor */
	int nkeys;	/* Number of keys in hash table */
	int hdrpages;	/* Size of table header */
	int h_charkey;	/* value of hash(CHARKEY) */
# define NCACHED		32	/* number of bit maps and spare points*/
	int spares[NCACHED];	/* spare pages for overflow */
	u_short bitmaps[NCACHED];	/* address of overflow page bitmaps */
E 5
I 5
	int	magic;		/* Magic NO for hash tables */
	int	version;	/* Version ID */
	long	lorder;		/* Byte Order */
	int	bsize;		/* Bucket/Page Size */
	int	bshift;		/* Bucket shift */
	int	dsize;		/* Directory Size */
	int	ssize;		/* Segment Size */
	int	sshift;		/* Segment shift */
I 6
	int	ovfl_point;	/* Where overflow pages are being allocated */
	int	last_freed;	/* Last overflow page freed */
E 6
	int	max_bucket;	/* ID of Maximum bucket in use */
	int	high_mask;	/* Mask to modulo into entire table */
	int	low_mask;	/* Mask to modulo into lower half of table */
	int	ffactor;	/* Fill factor */
	int	nkeys;		/* Number of keys in hash table */
	int	hdrpages;	/* Size of table header */
	int	h_charkey;	/* value of hash(CHARKEY) */
#define NCACHED	32		/* number of bit maps and spare points */
	int	spares[NCACHED];/* spare pages for overflow */
	u_short	bitmaps[NCACHED];	/* address of overflow page bitmaps */
E 5
} HASHHDR;

D 5
typedef struct htab {	/* Memory resident data structure */
	HASHHDR hdr;	/* Header */
	int nsegs;	/* Number of allocated segments */
	int exsegs;	/* Number of extra allocated segments */
	int (*hash)();	/* Hash Function */
	int flags;	/* Flag values */
	int fp;		/* File pointer */
	char *tmp_buf;	/* Temporary Buffer for BIG data */
	char *tmp_key;	/* Temporary Buffer for BIG keys */
	BUFHEAD *cpage;	/* Current page */
	int cbucket;	/* Current bucket */
	int cndx;  	/* Index of next item on cpage */
	int errno;	/* Error Number -- for DBM compatability */
	int new_file;	/* Indicates whether fd is backing store or no */
	int save_file;	/* Indicates whether we need to flush file at exit */
E 5
I 5
typedef struct htab {		/* Memory resident data structure */
	HASHHDR hdr;		/* Header */
	int	nsegs;		/* Number of allocated segments */
	int	exsegs;		/* Number of extra allocated segments */
D 9
	int	(*hash) ();	/* Hash Function */
E 9
I 9
	u_int32_t		/* Hash function */
	    (*hash)__P((const void *, size_t));
E 9
	int	flags;		/* Flag values */
	int	fp;		/* File pointer */
	char	*tmp_buf;	/* Temporary Buffer for BIG data */
	char	*tmp_key;	/* Temporary Buffer for BIG keys */
	BUFHEAD *cpage;		/* Current page */
	int	cbucket;	/* Current bucket */
	int	cndx;		/* Index of next item on cpage */
	int	errno;		/* Error Number -- for DBM compatability */
	int	new_file;	/* Indicates if fd is backing store or no */
	int	save_file;	/* Indicates whether we need to flush file at
				 * exit */
E 5
	u_long *mapp[NCACHED];	/* Pointers to page maps */
I 3
D 5
	int nmaps;	/* Initial number of bitmaps */
D 4
	int exmaps;	/* Number of extra allocated bitmaps */
E 4
E 3
	int nbufs;	/* Number of buffers left to allocate */
	BUFHEAD	bufhead; /* Header of buffer lru list */
	SEGMENT	 *dir;	/* Hash Bucket directory */
E 5
I 5
	int	nmaps;		/* Initial number of bitmaps */
	int	nbufs;		/* Number of buffers left to allocate */
	BUFHEAD bufhead;	/* Header of buffer lru list */
	SEGMENT *dir;		/* Hash Bucket directory */
E 5
} HTAB;

D 5

E 5
/*
 * Constants
 */
D 5
#define	MAX_BSIZE		65536	/* 2^16 */
E 5
I 5
#define	MAX_BSIZE		65536		/* 2^16 */
E 5
#define MIN_BUFFERS		6
#define MINHDRSIZE		512
D 5
#define DEF_BUFSIZE		65536	/* 64 K */
#define DEF_BUCKET_SIZE	256
#define DEF_BUCKET_SHIFT	8	/* log2(BUCKET) */
E 5
I 5
#define DEF_BUFSIZE		65536		/* 64 K */
D 7
#define DEF_BUCKET_SIZE		256
#define DEF_BUCKET_SHIFT	8		/* log2(BUCKET) */
E 7
I 7
#define DEF_BUCKET_SIZE		4096
#define DEF_BUCKET_SHIFT	12		/* log2(BUCKET) */
E 7
E 5
#define DEF_SEGSIZE		256
D 5
#define DEF_SEGSIZE_SHIFT		8      /* log2(SEGSIZE)	 */
E 5
I 5
#define DEF_SEGSIZE_SHIFT	8		/* log2(SEGSIZE)	 */
E 5
#define DEF_DIRSIZE		256
D 7
#define DEF_FFACTOR		5
E 7
I 7
#define DEF_FFACTOR		65536
#define MIN_FFACTOR		4
E 7
D 5
#define SPLTMAX		8
#define CHARKEY		"%$sniglet^&"
E 5
I 5
#define SPLTMAX			8
#define CHARKEY			"%$sniglet^&"
E 5
#define NUMKEY			1038583
D 6
#define VERSION_NO		3
E 6
#define BYTE_SHIFT		3
#define INT_TO_BYTE		2
#define INT_BYTE_SHIFT		5
D 5
#define ALL_SET		((unsigned)0xFFFFFFFF)
E 5
I 5
#define ALL_SET			((u_int)0xFFFFFFFF)
E 5
#define ALL_CLEAR		0

I 5
#define PTROF(X)	((BUFHEAD *)((u_int)(X)&~0x3))
#define ISMOD(X)	((u_int)(X)&0x1)
#define DOMOD(X)	((X) = (char *)((u_int)(X)|0x1))
#define ISDISK(X)	((u_int)(X)&0x2)
#define DODISK(X)	((X) = (char *)((u_int)(X)|0x2))
E 5

D 5
#define PTROF(X)	((BUFHEAD *)((unsigned)(X)&~0x3))
#define ISMOD(X)	((unsigned)(X)&0x1)
#define DOMOD(X)	(X = (char *)( (unsigned)X | 0x1))
#define ISDISK(X)	((unsigned)(X)&0x2)
#define DODISK(X)	(X = (char *)( (unsigned)X | 0x2))
E 5
I 5
#define BITS_PER_MAP	32
E 5

D 5
#define BITS_PER_MAP    32

E 5
/* Given the address of the beginning of a big map, clear/set the nth bit */
I 5
#define CLRBIT(A, N)	((A)[(N)/BITS_PER_MAP] &= ~(1<<((N)%BITS_PER_MAP)))
#define SETBIT(A, N)	((A)[(N)/BITS_PER_MAP] |= (1<<((N)%BITS_PER_MAP)))
#define ISSET(A, N)	((A)[(N)/BITS_PER_MAP] & (1<<((N)%BITS_PER_MAP)))
E 5

D 5
#define CLRBIT(A,N) ((A)[N/BITS_PER_MAP] &= ~(1<<(N%BITS_PER_MAP)))
#define SETBIT(A,N) ((A)[N/BITS_PER_MAP] |= (1<<(N%BITS_PER_MAP)))
#define ISSET(A,N) ((A)[N/BITS_PER_MAP] & (1<<(N%BITS_PER_MAP)))

E 5
/* Overflow management */
/*
D 5
	Overflow page numbers are allocated per split point.
	At each doubling of the table, we can allocate extra
	pages.  So, an overflow page number has the top 5 bits
	indicate which split point and the lower 11 bits indicate
	which page at that split point is indicated (pages within
	split points are numberered starting with 1).
E 5
I 5
 * Overflow page numbers are allocated per split point.  At each doubling of
 * the table, we can allocate extra pages.  So, an overflow page number has
 * the top 5 bits indicate which split point and the lower 11 bits indicate
 * which page at that split point is indicated (pages within split points are
 * numberered starting with 1).
 */
E 5

D 5

*/

E 5
#define SPLITSHIFT	11
#define SPLITMASK	0x7FF
D 5
#define SPLITNUM(N)	(((unsigned)N) >> SPLITSHIFT)
#define OPAGENUM(N)	(N & SPLITMASK)
D 4
#define	OADDR_OF(S,O)	((S << SPLITSHIFT) + O)
E 4
I 4
#define	OADDR_OF(S,O)	((unsigned)((unsigned)S << SPLITSHIFT) + O)
E 5
I 5
#define SPLITNUM(N)	(((u_int)(N)) >> SPLITSHIFT)
#define OPAGENUM(N)	((N) & SPLITMASK)
#define	OADDR_OF(S,O)	((u_int)((u_int)(S) << SPLITSHIFT) + (O))
E 5
E 4

#define BUCKET_TO_PAGE(B) \
D 5
	B + hashp->HDRPAGES + (B ? hashp->SPARES[__log2(B+1)-1] : 0)
E 5
I 5
	(B) + hashp->HDRPAGES + ((B) ? hashp->SPARES[__log2((B)+1)-1] : 0)
E 5
#define OADDR_TO_PAGE(B) 	\
D 5
	BUCKET_TO_PAGE ( (1 << SPLITNUM(B)) -1 ) + OPAGENUM(B);
E 5
I 5
	BUCKET_TO_PAGE ( (1 << SPLITNUM((B))) -1 ) + OPAGENUM((B));
E 5

/*
D 5
    page.h contains a detailed description of the page format.
E 5
I 5
 * page.h contains a detailed description of the page format.
 *
 * Normally, keys and data are accessed from offset tables in the top of
 * each page which point to the beginning of the key and data.  There are
 * four flag values which may be stored in these offset tables which indicate
 * the following:
 *
 *
 * OVFLPAGE	Rather than a key data pair, this pair contains
 *		the address of an overflow page.  The format of
 *		the pair is:
 *		    OVERFLOW_PAGE_NUMBER OVFLPAGE
 *
 * PARTIAL_KEY	This must be the first key/data pair on a page
 *		and implies that page contains only a partial key.
 *		That is, the key is too big to fit on a single page
 *		so it starts on this page and continues on the next.
 *		The format of the page is:
 *		    KEY_OFF PARTIAL_KEY OVFL_PAGENO OVFLPAGE
 *		
 *		    KEY_OFF -- offset of the beginning of the key
 *		    PARTIAL_KEY -- 1
 *		    OVFL_PAGENO - page number of the next overflow page
 *		    OVFLPAGE -- 0
 *
 * FULL_KEY	This must be the first key/data pair on the page.  It
 *		is used in two cases.
 *
 *		Case 1:
 *		    There is a complete key on the page but no data
 *		    (because it wouldn't fit).  The next page contains
 *		    the data.
 *
 *		    Page format it:
 *		    KEY_OFF FULL_KEY OVFL_PAGENO OVFL_PAGE
 *
 *		    KEY_OFF -- offset of the beginning of the key
 *		    FULL_KEY -- 2
 *		    OVFL_PAGENO - page number of the next overflow page
 *		    OVFLPAGE -- 0
 *
 *		Case 2:
 *		    This page contains no key, but part of a large
 *		    data field, which is continued on the next page.
 *
 *		    Page format it:
 *		    DATA_OFF FULL_KEY OVFL_PAGENO OVFL_PAGE
 *
 *		    KEY_OFF -- offset of the beginning of the data on
 *				this page
 *		    FULL_KEY -- 2
 *		    OVFL_PAGENO - page number of the next overflow page
 *		    OVFLPAGE -- 0
 *
 * FULL_KEY_DATA 
 *		This must be the first key/data pair on the page.
 *		There are two cases:
 *
 *		Case 1:
 *		    This page contains a key and the beginning of the
 *		    data field, but the data field is continued on the
 *		    next page.
 *
 *		    Page format is:
 *		    KEY_OFF FULL_KEY_DATA OVFL_PAGENO DATA_OFF
 *
 *		    KEY_OFF -- offset of the beginning of the key
 *		    FULL_KEY_DATA -- 3
 *		    OVFL_PAGENO - page number of the next overflow page
 *		    DATA_OFF -- offset of the beginning of the data
 *
 *		Case 2:
 *		    This page contains the last page of a big data pair.
 *		    There is no key, only the  tail end of the data
 *		    on this page.
 *
 *		    Page format is:
 *		    DATA_OFF FULL_KEY_DATA <OVFL_PAGENO> <OVFLPAGE>
 *
 *		    DATA_OFF -- offset of the beginning of the data on
 *				this page
 *		    FULL_KEY_DATA -- 3
 *		    OVFL_PAGENO - page number of the next overflow page
 *		    OVFLPAGE -- 0
 *
 *		    OVFL_PAGENO and OVFLPAGE are optional (they are
 *		    not present if there is no next page).
 */
E 5

D 5
    Normally, keys and data are accessed from offset tables in the
    top of each page which point to the beginning of the key and
    data.  There are four flag values which may be stored in these
    offset tables which indicate the following:

	OVFLPAGE	Rather than a key data pair, this pair contains
			the address of an overflow page.  The format of
			the pair is:
			    OVERFLOW_PAGE_NUMBER OVFLPAGE

	PARTIAL_KEY	This must be the first key/data pair on a page 
			and implies that page contains only a partial key.  
			That is, the key is too big to fit on a single page 
			so it starts on this page and continues on the next.
			The format of the page is:
			    KEY_OFF PARTIAL_KEY OVFL_PAGENO OVFLPAGE
			    
			    KEY_OFF -- offset of the beginning of the key
			    PARTIAL_KEY -- 1
			    OVFL_PAGENO - page number of the next overflow page
			    OVFLPAGE -- 0
	FULL_KEY	This must be the first key/data pair on the page.  It
			is used in two cases.  

			Case 1:
			    There is a complete key on the page but no data
			    (because it wouldn't fit).  The next page contains
			    the data.

			    Page format it:
			    KEY_OFF FULL_KEY OVFL_PAGENO OVFL_PAGE

			    KEY_OFF -- offset of the beginning of the key
			    FULL_KEY -- 2
			    OVFL_PAGENO - page number of the next overflow page
			    OVFLPAGE -- 0

			Case 2:
			    This page contains no key, but part of a large 
			    data field, which is continued on the next page.

			    Page format it:
			    DATA_OFF FULL_KEY OVFL_PAGENO OVFL_PAGE

			    KEY_OFF -- offset of the beginning of the data on
					this page
			    FULL_KEY -- 2
			    OVFL_PAGENO - page number of the next overflow page
			    OVFLPAGE -- 0

	FULL_KEY_DATA	This must be the first key/data pair on the page.
			There are two cases:

			Case 1:
			    This page contains a key and the beginning of the
			    data field, but the data field is continued on the
			    next page.

			    Page format is:
			    KEY_OFF FULL_KEY_DATA OVFL_PAGENO DATA_OFF

			    KEY_OFF -- offset of the beginning of the key
			    FULL_KEY_DATA -- 3
			    OVFL_PAGENO - page number of the next overflow page
			    DATA_OFF -- offset of the beginning of the data 

			Case 2:
			    This page contains the last page of a big data pair.
			    There is no key, only the  tail end of the data 
			    on this page.

			    Page format is:
			    DATA_OFF FULL_KEY_DATA <OVFL_PAGENO> <OVFLPAGE>

			    DATA_OFF -- offset of the beginning of the data on
					this page
			    FULL_KEY_DATA -- 3
			    OVFL_PAGENO - page number of the next overflow page
			    OVFLPAGE -- 0

			    OVFL_PAGENO and OVFLPAGE are optional (they are
			    not present if there is no next page).
*/
I 2

E 5
E 2
#define OVFLPAGE	0
#define PARTIAL_KEY	1
#define FULL_KEY	2
#define FULL_KEY_DATA	3
#define	REAL_KEY	4
I 5

E 5
D 2


E 2
/* Short hands for accessing structure */
D 5
#define BSIZE	hdr.bsize
#define BSHIFT	hdr.bshift
#define DSIZE	hdr.dsize
#define SGSIZE	hdr.ssize
#define SSHIFT	hdr.sshift
#define LORDER	hdr.lorder
E 5
I 5
#define BSIZE		hdr.bsize
#define BSHIFT		hdr.bshift
#define DSIZE		hdr.dsize
#define SGSIZE		hdr.ssize
#define SSHIFT		hdr.sshift
#define LORDER		hdr.lorder
I 6
#define OVFL_POINT	hdr.ovfl_point
#define	LAST_FREED	hdr.last_freed
E 6
E 5
#define MAX_BUCKET	hdr.max_bucket
#define FFACTOR		hdr.ffactor
#define HIGH_MASK	hdr.high_mask
#define LOW_MASK	hdr.low_mask
#define NKEYS		hdr.nkeys
#define HDRPAGES	hdr.hdrpages
#define SPARES		hdr.spares
#define BITMAPS		hdr.bitmaps
#define VERSION		hdr.version
#define MAGIC		hdr.magic
#define NEXT_FREE	hdr.next_free
#define H_CHARKEY	hdr.h_charkey
E 1
