h20779
s 00009/00005/00909
d D 8.4 94/02/21 17:43:42 bostic 33 32
c cast alloc's to shut SunOS up
e
s 00005/00005/00909
d D 8.3 94/02/21 15:09:10 bostic 32 31
c first pass at making DB use basic integral types (the Alpha port)
e
s 00008/00009/00906
d D 8.2 93/09/06 09:36:06 bostic 31 30
c always pass the appropriate overflow page address
c needed to handle the case where the last page in the chain is the last
c page of an overflow pair; from Margo Seltzer
e
s 00002/00002/00913
d D 8.1 93/06/06 23:04:27 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00914
d D 5.28 93/06/06 23:04:00 bostic 29 27
c When bumping splitpoint, begin overflow page number offset at 1 not 0
e
s 00002/00002/00913
d R 8.1 93/06/04 15:22:09 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00914
d D 5.27 93/05/25 10:08:27 bostic 27 26
c put SCCS keywords back in
e
s 00008/00001/00907
d D 5.26 93/05/23 13:04:58 bostic 26 25
c Dynamically compute fill factor (if not user specified).  When 
c first overflow page is allocated, set fill factor to the number of entries 
c on overflowing page.  Verify that new fill factor is at least MIN_FFACTOR.
e
s 00006/00006/00902
d D 5.25 93/02/16 12:33:30 bostic 25 24
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00001/00001/00907
d D 5.24 93/02/11 11:39:51 bostic 24 23
c move db.h to the end of the includes, make compat.h work better
e
s 00064/00047/00844
d D 5.23 93/01/17 16:20:24 bostic 23 22
c can't have a global "hashp", pass it around as an argument
c change default_hash to __default_hash for the same reason
e
s 00001/00001/00890
d D 5.22 92/07/17 09:51:51 bostic 22 21
c lint
e
s 00002/00002/00889
d D 5.21 92/07/17 09:47:59 bostic 21 20
c lseek takes an off_t, not a long
e
s 00004/00000/00887
d D 5.20 92/06/04 11:23:17 bostic 20 19
c check __get_buf return status
e
s 00001/00001/00886
d D 5.19 92/05/14 14:36:06 bostic 19 18
c don't add overflow pages to pages that already have overflow pages
e
s 00001/00001/00886
d D 5.18 92/05/11 16:18:30 bostic 18 17
c bitmaps should never be PAGE_INIT'd
e
s 00001/00001/00886
d D 5.17 91/09/11 16:01:51 bostic 17 16
c return -1 on error, not 1 in __put_page
e
s 00043/00011/00844
d D 5.16 91/09/08 13:45:18 bostic 16 15
c bump the hash version to 2; (allocate overflow pages beyond EOF)
e
s 00023/00018/00832
d D 5.15 91/09/08 12:26:40 bostic 15 14
c lint -- unused variables, check return values of some functions
e
s 00631/00660/00219
d D 5.14 91/09/04 12:56:35 bostic 14 13
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00003/00004/00876
d D 5.13 91/06/17 11:55:57 bostic 13 12
c don't use stdio for error messages
e
s 00033/00010/00847
d D 5.12 91/03/12 09:35:22 bostic 12 11
c Make all bucket and overflow addresses unsigned
c Make bitmaps demand loaded rather than load ahead on open
e
s 00004/00004/00853
d D 5.11 91/03/03 14:32:59 bostic 11 10
c DBT data changed to be unsigned, fix routines that take flags
e
s 00001/00001/00856
d D 5.10 91/02/28 12:40:43 bostic 10 9
c pcc (dammit!)
e
s 00003/00001/00854
d D 5.9 91/02/22 17:23:40 bostic 9 8
c ANSI prototypes
e
s 00001/00000/00854
d D 5.8 91/02/22 10:29:27 bostic 8 7
c ANSI fix
e
s 00001/00000/00853
d D 5.7 91/02/21 18:57:47 bostic 7 6
c count bitmaps so they can be free'd
e
s 00017/00020/00836
d D 5.6 91/02/21 18:54:00 bostic 6 5
c make sure free'd overflow pages are not reread from disk and handle
c back-to-back big key pairs during split
e
s 00003/00002/00853
d D 5.5 91/02/21 17:19:56 bostic 5 4
c L_SET -> SEEK_SET
e
s 00001/00001/00854
d D 5.4 91/02/21 17:15:39 bostic 4 3
c don't put namestr into text space -- Thanks ANSI!
e
s 00026/00011/00829
d D 5.3 91/02/19 10:31:59 bostic 3 2
c add "pinning" to the buffer pool
c make -1 mean no open fd instead of 0
e
s 00015/00005/00825
d D 5.2 91/02/14 18:25:42 bostic 2 1
c set file descriptors to be close-on-exec; block signals while
c unlinking the temporary file so we don't get caught
e
s 00830/00000/00000
d D 5.1 91/02/12 20:28:08 bostic 1 0
c date and time created 91/02/12 20:28:08 by bostic
e
u
U
t
T
I 1
/*-
D 30
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
D 26
static char sccsid[] = "%W% (Berkeley) %G%";
E 26
I 26
D 27
static char sccsid[] = "@(#)hash_page.c	5.25 (Berkeley) 2/16/93";
E 27
I 27
static char sccsid[] = "%W% (Berkeley) %G%";
E 27
E 26
#endif /* LIBC_SCCS and not lint */

D 14
/******************************************************************************
PACKAGE:  hashing
E 14
I 14
/*
 * PACKAGE:  hashing
 *
 * DESCRIPTION:
 *	Page manipulation for hashing package.
 *
 * ROUTINES:
 *
 * External
 *	__get_page
 *	__add_ovflpage
 * Internal
 *	overflow_page
 *	open_temp
 */
E 14

D 14
DESCRIPTION: 
	Page manipulation for hashing package.

ROUTINES: 
    External
	__get_page
	__add_ovflpage
    Internal
	overflow_page
	open_temp
******************************************************************************/

E 14
D 23
#include <sys/param.h>
E 23
I 23
#include <sys/types.h>

D 24
#include <db.h>
E 24
#include <errno.h>
E 23
D 9
#include <sys/file.h>
E 9
I 9
#include <fcntl.h>
E 9
I 2
#include <signal.h>
E 2
D 14
#include <assert.h>
E 14
D 23
#include <errno.h>
#include <db.h>
E 23
#include <stdio.h>
I 9
#include <stdlib.h>
#include <string.h>
E 9
I 5
#include <unistd.h>
I 14
#ifdef DEBUG
#include <assert.h>
#endif
I 23

I 24
#include <db.h>
E 24
E 23
E 14
E 5
#include "hash.h"
#include "page.h"
I 14
#include "extern.h"
E 14

D 14
/* Externals */
/* buf.c */
extern BUFHEAD	*__get_buf();
extern void __reclaim_buf();
E 14
I 14
D 15
static void putpair __P((char *, const DBT *, const DBT *));
static int ugly_split __P((u_int, BUFHEAD *, BUFHEAD *, int, int));
static int first_free __P((u_long));
static u_short overflow_page __P((void));
static int open_temp __P((void));
static void squeeze_key __P((u_short *, const DBT *, const DBT *));
static u_long *fetch_bitmap __P((int));
E 15
I 15
D 23
static u_long	*fetch_bitmap __P((int));
E 23
I 23
static u_long	*fetch_bitmap __P((HTAB *, int));
E 23
static u_long	 first_free __P((u_long));
D 23
static int	 open_temp __P((void));
static u_short	 overflow_page __P((void));
E 23
I 23
static int	 open_temp __P((HTAB *));
static u_short	 overflow_page __P((HTAB *));
E 23
static void	 putpair __P((char *, const DBT *, const DBT *));
static void	 squeeze_key __P((u_short *, const DBT *, const DBT *));
D 23
static int	 ugly_split __P((u_int, BUFHEAD *, BUFHEAD *, int, int));
E 23
I 23
static int	 ugly_split
		    __P((HTAB *, u_int, BUFHEAD *, BUFHEAD *, int, int));
E 23
E 15
E 14

D 14
/* big.c */
extern int __big_split();
extern int __big_insert();
extern int __big_delete();
extern int __find_bigpair();

/* dynahash.c */
D 12
extern	int	__call_hash();
E 12
I 12
extern	u_int	__call_hash();
E 12
extern	int	__expand_table();

/* my externals */
extern int __get_page();
extern BUFHEAD *__add_ovflpage();
extern int __split_page();
extern int __addel();

/* my internals */
static u_short overflow_page();
static int open_temp();
I 8
static int ugly_split();
E 8
static void squeeze_key();
static void putpair();
I 12
static u_long *fetch_bitmap();
E 12

#ifdef HASH_STATISTICS
extern long hash_accesses, hash_collisions, hash_expansions, hash_overflows;
#endif
#define	PAGE_INIT(P)					\
{							\
    ((u_short *)P)[0] = 0;				\
    ((u_short *)P)[1] = hashp->BSIZE - 3 * sizeof(u_short);	\
    ((u_short *)P)[2] = hashp->BSIZE;			\
E 14
I 14
#define	PAGE_INIT(P) { \
	((u_short *)(P))[0] = 0; \
	((u_short *)(P))[1] = hashp->BSIZE - 3 * sizeof(u_short); \
	((u_short *)(P))[2] = hashp->BSIZE; \
E 14
}

/*
D 14
	This is called AFTER we have verified that there is room on the
	page for the pair (PAIRFITS has returned true) so we go right
	ahead and start moving stuff on.
*/
E 14
I 14
 * This is called AFTER we have verified that there is room on the page for
 * the pair (PAIRFITS has returned true) so we go right ahead and start moving
 * stuff on.
 */
E 14
static void
putpair(p, key, val)
D 14
char *p;
DBT *key;
DBT *val;
E 14
I 14
	char *p;
	const DBT *key, *val;
E 14
{
D 14
	register u_short n;
	register u_short off;
	register u_short *bp = (u_short *) p;
E 14
I 14
	register u_short *bp, n, off;
E 14

D 14
/* enter the key first */
E 14
I 14
	bp = (u_short *)p;

	/* Enter the key first. */
E 14
	n = bp[0];

	off = OFFSET(bp) - key->size;
D 14
	bcopy( key->data, p+off, key->size );
E 14
I 14
D 25
	bcopy(key->data, p + off, key->size);
E 25
I 25
	memmove(p + off, key->data, key->size);
E 25
E 14
	bp[++n] = off;

D 14
/* now the data */
E 14
I 14
	/* Now the data. */
E 14
	off -= val->size;
D 14
	bcopy(val->data,  p + off, val->size);
E 14
I 14
D 25
	bcopy(val->data, p + off, val->size);
E 25
I 25
	memmove(p + off, val->data, val->size);
E 25
E 14
	bp[++n] = off;

D 14
/* adjust page info */
E 14
I 14
	/* Adjust page info. */
E 14
	bp[0] = n;
D 14
	bp[n+1] = off - ((n+3)*sizeof(u_short));
	bp[n+2] = off;
	return;
E 14
I 14
	bp[n + 1] = off - ((n + 3) * sizeof(u_short));
	bp[n + 2] = off;
E 14
}
I 14

E 14
/*
D 14
    0 OK
    -1 error
*/
E 14
I 14
 * Returns:
 *	 0 OK
 *	-1 error
 */
E 14
extern int
D 23
__delpair(bufp, ndx)
E 23
I 23
__delpair(hashp, bufp, ndx)
	HTAB *hashp;
E 23
D 14
BUFHEAD *bufp;
register int ndx;
E 14
I 14
	BUFHEAD *bufp;
	register int ndx;
E 14
{
D 14
	register u_short *bp = (u_short *) bufp->page;
	register int n = bp[0];
	register u_short newoff;
E 14
I 14
	register u_short *bp, newoff;
	register int n;
E 14
	u_short pairlen;

D 14
	if ( bp[ndx+1] < REAL_KEY ) return ( __big_delete ( bufp, ndx ) );
	if ( ndx != 1 ) newoff = bp[ndx-1];
	else newoff = hashp->BSIZE;
	pairlen = newoff - bp[ndx+1];
E 14
I 14
	bp = (u_short *)bufp->page;
	n = bp[0];
E 14

D 14
	if ( ndx != (n-1) ) {
E 14
I 14
	if (bp[ndx + 1] < REAL_KEY)
D 15
		return (__big_delete(bufp, ndx));
E 15
I 15
D 23
		return (__big_delete(bufp));
E 23
I 23
		return (__big_delete(hashp, bufp));
E 23
E 15
	if (ndx != 1)
		newoff = bp[ndx - 1];
	else
		newoff = hashp->BSIZE;
	pairlen = newoff - bp[ndx + 1];

	if (ndx != (n - 1)) {
E 14
		/* Hard Case -- need to shuffle keys */
		register int i;
		register char *src = bufp->page + (int)OFFSET(bp);
		register char *dst = src + (int)pairlen;
D 14
		bcopy ( src, dst, bp[ndx+1] - OFFSET(bp) );
E 14
I 14
D 25
		bcopy(src, dst, bp[ndx + 1] - OFFSET(bp));
E 25
I 25
		memmove(dst, src, bp[ndx + 1] - OFFSET(bp));
E 25
E 14

		/* Now adjust the pointers */
D 14
		for ( i = ndx+2; i <= n; i += 2 ) {
		    if ( bp[i+1]  == OVFLPAGE ) {
			bp[i-2] = bp[i];
			bp[i-1] = bp[i+1];
		    } else {
			bp[i-2] = bp[i] + pairlen;
			bp[i-1] = bp[i+1] + pairlen;
		    }
E 14
I 14
		for (i = ndx + 2; i <= n; i += 2) {
			if (bp[i + 1] == OVFLPAGE) {
				bp[i - 2] = bp[i];
				bp[i - 1] = bp[i + 1];
			} else {
				bp[i - 2] = bp[i] + pairlen;
				bp[i - 1] = bp[i + 1] + pairlen;
			}
E 14
		}
	}
D 14

E 14
	/* Finally adjust the page data */
	bp[n] = OFFSET(bp) + pairlen;
D 14
	bp[n-1] = bp[n+1] + pairlen + 2 * sizeof(u_short);
	bp[0] = n-2;
E 14
I 14
	bp[n - 1] = bp[n + 1] + pairlen + 2 * sizeof(u_short);
	bp[0] = n - 2;
E 14
	hashp->NKEYS--;

	bufp->flags |= BUF_MOD;
	return (0);
}
/*
D 14
    -1 ==> Error
    0 ==> OK
*/
E 14
I 14
 * Returns:
 *	 0 ==> OK
 *	-1 ==> Error
 */
E 14
extern int
D 23
__split_page(obucket, nbucket)
E 23
I 23
__split_page(hashp, obucket, nbucket)
	HTAB *hashp;
E 23
D 12
int obucket;
int nbucket;
E 12
I 12
D 14
u_int obucket;
u_int nbucket;
E 14
I 14
	u_int obucket, nbucket;
E 14
E 12
{
D 14
	DBT key;
	DBT val;

	register BUFHEAD *new_bufp;
	register BUFHEAD *old_bufp;
E 14
I 14
	register BUFHEAD *new_bufp, *old_bufp;
E 14
	register u_short *ino;
D 14
	register char	*np;
I 3
	int n;
	int ndx;
	int retval;
E 3
	char	*op;
E 14
I 14
	register char *np;
	DBT key, val;
	int n, ndx, retval;
	u_short copyto, diff, off, moved;
	char *op;
E 14

D 14
	u_short copyto = (u_short)hashp->BSIZE;
D 3
	u_short off = (u_short)hashp->BSIZE;
	int n;
E 3
	u_short diff;
I 3
	u_short off = (u_short)hashp->BSIZE;
E 3
	u_short moved;
E 14
I 14
	copyto = (u_short)hashp->BSIZE;
	off = (u_short)hashp->BSIZE;
D 23
	old_bufp = __get_buf(obucket, NULL, 0);
E 23
I 23
	old_bufp = __get_buf(hashp, obucket, NULL, 0);
E 23
I 20
	if (old_bufp == NULL)
		return (-1);
E 20
D 23
	new_bufp = __get_buf(nbucket, NULL, 0);
E 23
I 23
	new_bufp = __get_buf(hashp, nbucket, NULL, 0);
E 23
I 20
	if (new_bufp == NULL)
		return (-1);
E 20
E 14
D 3
	int ndx;
E 3

D 14
	old_bufp = __get_buf ( obucket, NULL, 0 );
	new_bufp = __get_buf ( nbucket, NULL, 0 );
E 14
I 14
	old_bufp->flags |= (BUF_MOD | BUF_PIN);
	new_bufp->flags |= (BUF_MOD | BUF_PIN);
E 14

D 3
	old_bufp->flags |= BUF_MOD;
	new_bufp->flags |= BUF_MOD;
E 3
I 3
D 14
	old_bufp->flags |= (BUF_MOD|BUF_PIN);
	new_bufp->flags |= (BUF_MOD|BUF_PIN);
E 3

E 14
	ino = (u_short *)(op = old_bufp->page);
	np = new_bufp->page;

	moved = 0;

D 14
	for (n = 1, ndx = 1; n < ino[0]; n+=2) {
		if ( ino[n+1] < REAL_KEY ) {
D 3
		    return ( ugly_split( obucket, old_bufp, new_bufp, 
					 copyto, moved ) );
E 3
I 3
		    retval = ugly_split( obucket, old_bufp, new_bufp, 
					 copyto, moved );
		    old_bufp->flags &= ~BUF_PIN;
		    new_bufp->flags &= ~BUF_PIN;
		    return(retval);
		    
E 14
I 14
	for (n = 1, ndx = 1; n < ino[0]; n += 2) {
		if (ino[n + 1] < REAL_KEY) {
D 23
			retval = ugly_split(obucket, old_bufp, new_bufp,
E 23
I 23
			retval = ugly_split(hashp, obucket, old_bufp, new_bufp,
E 23
D 15
			    copyto, moved);
E 15
I 15
			    (int)copyto, (int)moved);
E 15
			old_bufp->flags &= ~BUF_PIN;
			new_bufp->flags &= ~BUF_PIN;
			return (retval);

E 14
E 3
		}
D 11
		key.data = op + ino[n]; 
E 11
I 11
D 14
		key.data = (u_char *)op + ino[n]; 
E 14
I 14
		key.data = (u_char *)op + ino[n];
E 14
E 11
		key.size = off - ino[n];

D 14
		if ( __call_hash ( key.data, key.size ) == obucket ) {
		    /* Don't switch page */
		    diff = copyto - off;
		    if ( diff ) {
			copyto = ino[n+1] + diff;
			bcopy ( op + ino[n+1], op + copyto,  off-ino[n+1]);
			ino[ndx] = copyto + ino[n] - ino[n+1];
			ino[ndx+1] = copyto;
		    } else copyto = ino[n+1];
		    ndx += 2;
E 14
I 14
D 23
		if (__call_hash(key.data, key.size) == obucket) {
E 23
I 23
		if (__call_hash(hashp, key.data, key.size) == obucket) {
E 23
			/* Don't switch page */
			diff = copyto - off;
			if (diff) {
				copyto = ino[n + 1] + diff;
D 25
				bcopy(op + ino[n + 1], op + copyto,
E 25
I 25
				memmove(op + copyto, op + ino[n + 1],
E 25
				    off - ino[n + 1]);
				ino[ndx] = copyto + ino[n] - ino[n + 1];
				ino[ndx + 1] = copyto;
			} else
				copyto = ino[n + 1];
			ndx += 2;
E 14
		} else {
D 14
		    /* Switch page */
D 11
		    val.data = op + ino[n+1];
E 11
I 11
		    val.data = (u_char *)op + ino[n+1];
E 11
		    val.size = ino[n] - ino[n+1];
		    putpair( np, &key, &val);
		    moved +=2;
E 14
I 14
			/* Switch page */
			val.data = (u_char *)op + ino[n + 1];
			val.size = ino[n] - ino[n + 1];
			putpair(np, &key, &val);
			moved += 2;
E 14
		}

D 14
		off = ino[n+1];
E 14
I 14
		off = ino[n + 1];
E 14
	}

	/* Now clean up the page */
	ino[0] -= moved;
D 14
	FREESPACE(ino) = copyto - sizeof(u_short) * (ino[0]+3);
E 14
I 14
	FREESPACE(ino) = copyto - sizeof(u_short) * (ino[0] + 3);
E 14
	OFFSET(ino) = copyto;

#ifdef DEBUG3
D 14
	fprintf(stderr, "split %d/%d\n", 
	       ((u_short *) np)[0] / 2,
	       ((u_short *) op)[0] / 2);
E 14
I 14
	(void)fprintf(stderr, "split %d/%d\n",
	    ((u_short *)np)[0] / 2,
	    ((u_short *)op)[0] / 2);
E 14
#endif
I 3
	/* unpin both pages */
	old_bufp->flags &= ~BUF_PIN;
	new_bufp->flags &= ~BUF_PIN;
E 3
D 14
	return(0);
E 14
I 14
	return (0);
E 14
}
D 14
/*
    0 ==> success
    -1 ==> failure
E 14

D 3
    Called when we encounter an overflow page during split handling.
    this is special cased since we have to begin checking whether
E 3
I 3
D 14
    Called when we encounter an overflow or big key/data page during 
    split handling.
    This is special cased since we have to begin checking whether
E 3
    the key/data pairs fit on their respective pages and because
    we may need overflow pages for both the old and new pages
I 3

    The first page might be a page with regular key/data pairs
    in which case we have a regular overflow condition and just
    need to go on to the next page or it might be a big key/data 
    pair in which case we need to fix the big key/data pair.
E 3
*/
E 14
I 14
/*
 * Called when we encounter an overflow or big key/data page during split
 * handling.  This is special cased since we have to begin checking whether
 * the key/data pairs fit on their respective pages and because we may need
 * overflow pages for both the old and new pages.
 *
 * The first page might be a page with regular key/data pairs in which case
 * we have a regular overflow condition and just need to go on to the next
 * page or it might be a big key/data pair in which case we need to fix the
 * big key/data pair.
 *
 * Returns:
 *	 0 ==> success
 *	-1 ==> failure
 */
E 14
static int
D 14
ugly_split( obucket, old_bufp, new_bufp, copyto, moved )
D 12
int	obucket;	/* Same as __split_page */
E 12
I 12
u_int	obucket;	/* Same as __split_page */
E 12
BUFHEAD	*old_bufp;		
BUFHEAD	*new_bufp;
u_short	copyto;		/* First byte on page which contains key/data values */
int	moved;		/* number of pairs moved to new page */
E 14
I 14
D 23
ugly_split(obucket, old_bufp, new_bufp, copyto, moved)
E 23
I 23
ugly_split(hashp, obucket, old_bufp, new_bufp, copyto, moved)
	HTAB *hashp;
E 23
	u_int obucket;	/* Same as __split_page. */
	BUFHEAD *old_bufp, *new_bufp;
	int copyto;	/* First byte on page which contains key/data values. */
	int moved;	/* Number of pairs moved to new page. */
E 14
{
D 14
    register BUFHEAD *bufp = old_bufp;		/* Buffer header for ino */
    register u_short	*ino = (u_short *)old_bufp->page;	
						/* Page keys come off of */
    register u_short	*np = (u_short *)new_bufp->page;	/* New page */
    register u_short	*op = (u_short *)old_bufp->page;	
						/* Page keys go on to if they
						   aren't moving */
E 14
I 14
	register BUFHEAD *bufp;	/* Buffer header for ino */
	register u_short *ino;	/* Page keys come off of */
	register u_short *np;	/* New page */
	register u_short *op;	/* Page keys go on to if they aren't moving */
E 14

D 14
    char	*cino;				/* Character value of ino */
    BUFHEAD	*last_bfp = NULL;		/* Last buffer header OVFL which
						   needs to be freed */
    u_short	ov_addr, last_addr = 0;
    u_short	n;
    u_short	off;
E 14
I 14
	BUFHEAD *last_bfp;	/* Last buf header OVFL needing to be freed */
	DBT key, val;
	SPLIT_RETURN ret;
D 15
	u_short last_addr, n, off, ov_addr, scopyto;
E 15
I 15
	u_short n, off, ov_addr, scopyto;
E 15
	char *cino;		/* Character value of ino */
E 14

D 14
    DBT	key, val;
    SPLIT_RETURN	ret;
E 14
I 14
	bufp = old_bufp;
	ino = (u_short *)old_bufp->page;
	np = (u_short *)new_bufp->page;
	op = (u_short *)old_bufp->page;
	last_bfp = NULL;
D 15
	last_addr = 0;
E 15
	scopyto = (u_short)copyto;	/* ANSI */
E 14

D 14
    n = ino[0]-1;
    while ( n < ino[0] ) {
D 6
	if ( ino[n+1] == OVFLPAGE ) {
E 6
I 6
	if ( ino[2] < REAL_KEY && ino[2] != OVFLPAGE ) {
	    if (__big_split (old_bufp, new_bufp, bufp, ov_addr, obucket, &ret)) {
		return(-1);
	    }
	    old_bufp = ret.oldp;
	    if ( !old_bufp ) return(-1);
	    op = (u_short *)old_bufp->page;
	    new_bufp = ret.newp;
	    if ( !new_bufp ) return(-1);
	    np = (u_short *)new_bufp->page;
	    bufp = ret.nextp;
	    if ( !bufp ) return(0);
	    cino = (char *)bufp->page;
	    ino = (u_short *)cino;
	    last_bfp = ret.nextp;
	} else if ( ino[n+1] == OVFLPAGE ) {
E 6
	    ov_addr = ino[n];
	    /* 
		Fix up the old page -- the extra 2 are the fields which
		contained the overflow information 
	    */
	    ino[0] -= (moved + 2);
	    FREESPACE(ino) = copyto - sizeof(u_short) * (ino[0]+3);
	    OFFSET(ino) = copyto;
E 14
I 14
	n = ino[0] - 1;
	while (n < ino[0]) {
		if (ino[2] < REAL_KEY && ino[2] != OVFLPAGE) {
I 15
D 31
			/*
			 * Ov_addr gets set before reaching this point; there's
			 * always an overflow page before a big key/data page.
			 */
E 31
E 15
D 23
			if (__big_split(old_bufp,
E 23
I 23
			if (__big_split(hashp, old_bufp,
E 23
D 31
			    new_bufp, bufp, ov_addr, obucket, &ret))
E 31
I 31
			    new_bufp, bufp, bufp->addr, obucket, &ret))
E 31
				return (-1);
			old_bufp = ret.oldp;
			if (!old_bufp)
				return (-1);
			op = (u_short *)old_bufp->page;
			new_bufp = ret.newp;
			if (!new_bufp)
				return (-1);
			np = (u_short *)new_bufp->page;
			bufp = ret.nextp;
			if (!bufp)
				return (0);
			cino = (char *)bufp->page;
			ino = (u_short *)cino;
			last_bfp = ret.nextp;
		} else if (ino[n + 1] == OVFLPAGE) {
			ov_addr = ino[n];
			/*
			 * Fix up the old page -- the extra 2 are the fields
			 * which contained the overflow information.
			 */
			ino[0] -= (moved + 2);
			FREESPACE(ino) =
			    scopyto - sizeof(u_short) * (ino[0] + 3);
			OFFSET(ino) = scopyto;
E 14

D 14
	    bufp = __get_buf ( ov_addr, bufp, 0 );
	    if ( !bufp ) return(-1);
E 14
I 14
D 23
			bufp = __get_buf(ov_addr, bufp, 0);
E 23
I 23
			bufp = __get_buf(hashp, ov_addr, bufp, 0);
E 23
			if (!bufp)
				return (-1);
E 14

D 14
	    ino = (u_short *)bufp->page;
	    n = 1;
	    copyto = hashp->BSIZE;
	    moved = 0;
E 14
I 14
			ino = (u_short *)bufp->page;
			n = 1;
			scopyto = hashp->BSIZE;
			moved = 0;
E 14

D 14
	    if ( last_bfp ) {
		__free_ovflpage( last_bfp);
	    }
	    last_bfp = bufp;
	} 
D 6

	if ( (ino[2] < REAL_KEY) && (ino[2] != OVFLPAGE) ) {
	    if (__big_split (old_bufp,
		new_bufp, bufp, ov_addr, obucket, &ret)) {
		    return(-1);
	    }
	    old_bufp = ret.oldp;
	    if ( !old_bufp ) return(-1);
	    op = (u_short *)old_bufp->page;
	    new_bufp = ret.newp;
	    if ( !new_bufp ) return(-1);
	    np = (u_short *)new_bufp->page;
	    bufp = ret.nextp;
	    if ( !bufp ) return(0);
	    cino = (char *)bufp->page;
	    ino = (u_short *)cino;
	    last_bfp = ret.nextp;
	}
E 6
	
E 14
I 14
			if (last_bfp)
D 23
				__free_ovflpage(last_bfp);
E 23
I 23
				__free_ovflpage(hashp, last_bfp);
E 23
			last_bfp = bufp;
		}
		/* Move regular sized pairs of there are any */
		off = hashp->BSIZE;
		for (n = 1; (n < ino[0]) && (ino[n + 1] >= REAL_KEY); n += 2) {
			cino = (char *)ino;
			key.data = (u_char *)cino + ino[n];
			key.size = off - ino[n];
			val.data = (u_char *)cino + ino[n + 1];
			val.size = ino[n] - ino[n + 1];
			off = ino[n + 1];
E 14

I 3
D 14
	/* Move regular sized pairs of there are any */
E 3
	off = hashp->BSIZE;
	for ( n = 1; (n < ino[0]) && (ino[n+1] >= REAL_KEY); n += 2 ) {
	    cino = (char *)ino;
D 11
	    key.data = cino + ino[n]; 
E 11
I 11
	    key.data = (u_char *)cino + ino[n]; 
E 11
	    key.size = off - ino[n];
D 11
	    val.data = cino + ino[n+1];
E 11
I 11
	    val.data = (u_char *)cino + ino[n+1];
E 11
	    val.size = ino[n] - ino[n+1];
	    off = ino[n+1];

	    if ( __call_hash ( key.data, key.size ) == obucket ) {
		/* Keep on old page */
		if (PAIRFITS(op,(&key),(&val))) putpair((char *)op, &key, &val);
		else {
		    old_bufp = __add_ovflpage ( old_bufp );
		    if ( !old_bufp ) return(-1);
		    op = (u_short *)old_bufp->page;
		    putpair ((char *)op, &key, &val);
E 14
I 14
D 23
			if (__call_hash(key.data, key.size) == obucket) {
E 23
I 23
			if (__call_hash(hashp, key.data, key.size) == obucket) {
E 23
				/* Keep on old page */
				if (PAIRFITS(op, (&key), (&val)))
					putpair((char *)op, &key, &val);
				else {
D 23
					old_bufp = __add_ovflpage(old_bufp);
E 23
I 23
					old_bufp =
					    __add_ovflpage(hashp, old_bufp);
E 23
					if (!old_bufp)
						return (-1);
					op = (u_short *)old_bufp->page;
					putpair((char *)op, &key, &val);
				}
				old_bufp->flags |= BUF_MOD;
			} else {
				/* Move to new page */
				if (PAIRFITS(np, (&key), (&val)))
					putpair((char *)np, &key, &val);
				else {
D 23
					new_bufp = __add_ovflpage(new_bufp);
E 23
I 23
					new_bufp =
					    __add_ovflpage(hashp, new_bufp);
E 23
					if (!new_bufp)
						return (-1);
					np = (u_short *)new_bufp->page;
					putpair((char *)np, &key, &val);
				}
				new_bufp->flags |= BUF_MOD;
			}
E 14
		}
D 14
		old_bufp->flags |= BUF_MOD;
	    } else {
		/* Move to new page */
		if (PAIRFITS(np,(&key),(&val))) putpair((char *)np, &key, &val);
		else {
		    new_bufp = __add_ovflpage ( new_bufp );
		    if ( !new_bufp )return(-1);
		    np = (u_short *)new_bufp->page;
		    putpair ((char *)np, &key, &val);
		} 
		new_bufp->flags |= BUF_MOD;
	    }
E 14
	}
D 14
    }
    if ( last_bfp ) {
	__free_ovflpage(last_bfp);
    }

    return (0);
E 14
I 14
	if (last_bfp)
D 23
		__free_ovflpage(last_bfp);
E 23
I 23
		__free_ovflpage(hashp, last_bfp);
E 23
	return (0);
E 14
}
I 14

E 14
/*
D 14
    Add the given pair to the page
    1 ==> failure
    0 ==> OK
*/
E 14
I 14
 * Add the given pair to the page
 *
 * Returns:
 *	0 ==> OK
 *	1 ==> failure
 */
E 14
extern int
D 23
__addel(bufp, key, val)
E 23
I 23
__addel(hashp, bufp, key, val)
	HTAB *hashp;
E 23
D 14
BUFHEAD	*bufp;
DBT	*key;
DBT	*val;
E 14
I 14
	BUFHEAD *bufp;
	const DBT *key, *val;
E 14
{
D 14
    register u_short *bp = (u_short *)bufp->page;
    register u_short *sop;
    int	do_expand;
E 14
I 14
	register u_short *bp, *sop;
	int do_expand;
E 14

D 14
    do_expand = 0;
    while ( bp[0] &&  (bp[bp[0]] < REAL_KEY) ) {
	/* Exception case */
	if ( bp[2] < REAL_KEY ) {
	    /* This is a big-keydata pair */
	    bufp = __add_ovflpage(bufp);
	    if ( !bufp ) {
		return(-1);
	    }
	    bp = (u_short *)bufp->page;
	} else {
	    /* Try to squeeze key on this page */
	    if ( FREESPACE(bp) > PAIRSIZE(key,val) ) {
		squeeze_key ( bp, key, val );
		return(0);
	    } else {
		bufp = __get_buf ( bp[bp[0]-1], bufp, 0 );
		if (!bufp) {
		    return(-1);
		}
		bp = (u_short *)bufp->page;
	    }
	}
    }
E 14
I 14
	bp = (u_short *)bufp->page;
	do_expand = 0;
D 31
	while (bp[0] && (bp[bp[0]] < REAL_KEY))
E 31
I 31
	while (bp[0] && (bp[2] < REAL_KEY || bp[bp[0]] < REAL_KEY))
E 31
		/* Exception case */
D 19
		if (bp[2] < REAL_KEY) {
E 19
I 19
D 31
		if (bp[2] < REAL_KEY && bp[bp[0]] != OVFLPAGE) {
E 19
			/* This is a big-keydata pair */
D 23
			bufp = __add_ovflpage(bufp);
E 23
I 23
			bufp = __add_ovflpage(hashp, bufp);
E 31
I 31
		if (bp[2] == FULL_KEY_DATA && bp[0] == 2)
			/* This is the last page of a big key/data pair
			   and we need to add another page */
			break;
		else if (bp[2] < REAL_KEY && bp[bp[0]] != OVFLPAGE) {
			bufp = __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
E 31
E 23
			if (!bufp)
				return (-1);
			bp = (u_short *)bufp->page;
		} else
			/* Try to squeeze key on this page */
			if (FREESPACE(bp) > PAIRSIZE(key, val)) {
				squeeze_key(bp, key, val);
				return (0);
			} else {
D 23
				bufp = __get_buf(bp[bp[0] - 1], bufp, 0);
E 23
I 23
				bufp = __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
E 23
				if (!bufp)
					return (-1);
				bp = (u_short *)bufp->page;
			}
E 14

D 14
    if ( PAIRFITS(bp,key,val) ) putpair (bufp->page, key, val);
    else {
	do_expand = 1;
	bufp = __add_ovflpage ( bufp );
	if (!bufp)return(-1);
	sop = (u_short *) bufp->page;
E 14
I 14
	if (PAIRFITS(bp, key, val))
		putpair(bufp->page, key, val);
	else {
		do_expand = 1;
D 23
		bufp = __add_ovflpage(bufp);
E 23
I 23
		bufp = __add_ovflpage(hashp, bufp);
E 23
		if (!bufp)
			return (-1);
		sop = (u_short *)bufp->page;
E 14

D 14
	if ( PAIRFITS(sop, key, val) ) putpair ( (char *)sop, key, val );
	else if ( __big_insert ( bufp, key, val ) ) {
	    return(-1);
E 14
I 14
		if (PAIRFITS(sop, key, val))
			putpair((char *)sop, key, val);
		else
D 23
			if (__big_insert(bufp, key, val))
E 23
I 23
			if (__big_insert(hashp, bufp, key, val))
E 23
				return (-1);
E 14
	}
D 14
    }
    bufp->flags |= BUF_MOD;
    /* 
	If the average number of keys per bucket exceeds the fill factor,
	expand the table
    */
    hashp->NKEYS++;
    if (do_expand || 
	(hashp->NKEYS / (hashp->MAX_BUCKET+1) > hashp->FFACTOR) ) {
	 return(__expand_table());
    }
    return(0);
E 14
I 14
	bufp->flags |= BUF_MOD;
	/*
	 * If the average number of keys per bucket exceeds the fill factor,
	 * expand the table.
	 */
	hashp->NKEYS++;
	if (do_expand ||
	    (hashp->NKEYS / (hashp->MAX_BUCKET + 1) > hashp->FFACTOR))
D 23
		return (__expand_table());
E 23
I 23
		return (__expand_table(hashp));
E 23
	return (0);
E 14
}

/*
D 14
    returns a pointer, NULL on error
*/
E 14
I 14
 *
 * Returns:
 *	pointer on success
 *	NULL on error
 */
E 14
extern BUFHEAD *
D 14
__add_ovflpage ( bufp )
BUFHEAD	*bufp;
E 14
I 14
D 23
__add_ovflpage(bufp)
E 23
I 23
__add_ovflpage(hashp, bufp)
	HTAB *hashp;
E 23
	BUFHEAD *bufp;
E 14
{
D 14
    register	u_short	*sp = (u_short *)bufp->page;

    u_short	ovfl_num;
    u_short	ndx, newoff;
    char	*op;
    DBT	okey, oval;
E 14
I 14
	register u_short *sp;
	u_short ndx, ovfl_num;
E 14
#ifdef DEBUG1
D 14
    int	tmp1, tmp2;
E 14
I 14
	int tmp1, tmp2;
E 14
#endif
D 14

    bufp->flags |= BUF_MOD;
    ovfl_num = overflow_page ();
E 14
I 14
	sp = (u_short *)bufp->page;
I 26

	/* Check if we are dynamically determining the fill factor */
	if (hashp->FFACTOR == DEF_FFACTOR) {
		hashp->FFACTOR = sp[0] >> 1;
		if (hashp->FFACTOR < MIN_FFACTOR)
			hashp->FFACTOR = MIN_FFACTOR;
	}
E 26
	bufp->flags |= BUF_MOD;
D 23
	ovfl_num = overflow_page();
E 23
I 23
	ovfl_num = overflow_page(hashp);
E 23
E 14
#ifdef DEBUG1
D 14
    tmp1 = bufp->addr;
    tmp2 = bufp->ovfl?bufp->ovfl->addr:0;
E 14
I 14
	tmp1 = bufp->addr;
	tmp2 = bufp->ovfl ? bufp->ovfl->addr : 0;
E 14
#endif
D 14
    if (!ovfl_num || !(bufp->ovfl = __get_buf ( ovfl_num, bufp, 1 ))) {
	return(NULL);
    }
    bufp->ovfl->flags |= BUF_MOD;
E 14
I 14
D 23
	if (!ovfl_num || !(bufp->ovfl = __get_buf(ovfl_num, bufp, 1)))
E 23
I 23
	if (!ovfl_num || !(bufp->ovfl = __get_buf(hashp, ovfl_num, bufp, 1)))
E 23
		return (NULL);
	bufp->ovfl->flags |= BUF_MOD;
E 14
#ifdef DEBUG1
D 14
    fprintf ( stderr, "ADDOVFLPAGE: %d->ovfl was %d is now %d\n", tmp1, tmp2, 
		bufp->ovfl->addr );
E 14
I 14
	(void)fprintf(stderr, "ADDOVFLPAGE: %d->ovfl was %d is now %d\n",
	    tmp1, tmp2, bufp->ovfl->addr);
E 14
#endif
D 14
    ndx = sp[0];
    /* 
	Since a pair is allocated on a page only if there's room
	to add an overflow page, we know that the OVFL information
	will fit on the page
    */
    sp[ndx+4] = OFFSET(sp);
    sp[ndx+3] = FREESPACE(sp) - OVFLSIZE;
    sp[ndx+1] = ovfl_num;
    sp[ndx+2] = OVFLPAGE;
    sp[0] = ndx+2;
E 14
I 14
	ndx = sp[0];
	/*
	 * Since a pair is allocated on a page only if there's room to add
	 * an overflow page, we know that the OVFL information will fit on
	 * the page.
	 */
	sp[ndx + 4] = OFFSET(sp);
	sp[ndx + 3] = FREESPACE(sp) - OVFLSIZE;
	sp[ndx + 1] = ovfl_num;
	sp[ndx + 2] = OVFLPAGE;
	sp[0] = ndx + 2;
E 14
#ifdef HASH_STATISTICS
D 14
	    hash_overflows++;
E 14
I 14
	hash_overflows++;
E 14
#endif
D 14
    return(bufp->ovfl);
E 14
I 14
	return (bufp->ovfl);
E 14
}

/*
D 14
    0 indicates SUCCESS
    -1 indicates FAILURE
*/
extern	int
__get_page ( p, bucket, is_bucket, is_disk, is_bitmap )
char	*p;
D 12
int	bucket;
E 12
I 12
u_int	bucket;
E 12
int	is_bucket;
int	is_disk;
int	is_bitmap;
E 14
I 14
 * Returns:
 *	 0 indicates SUCCESS
 *	-1 indicates FAILURE
 */
extern int
D 23
__get_page(p, bucket, is_bucket, is_disk, is_bitmap)
E 23
I 23
__get_page(hashp, p, bucket, is_bucket, is_disk, is_bitmap)
	HTAB *hashp;
E 23
	char *p;
	u_int bucket;
	int is_bucket, is_disk, is_bitmap;
E 14
{
D 14
    register int size;
    register int fd;
    register int page;
    u_short	*bp;
    int		rsize;
E 14
I 14
	register int fd, page, size;
	int rsize;
	u_short *bp;
E 14

D 14
    fd = hashp->fp;
    size = hashp->BSIZE;
E 14
I 14
	fd = hashp->fp;
	size = hashp->BSIZE;
E 14

D 3
    if ( !fd || (hashp->new_file && !is_disk) ) {
E 3
I 3
D 6
    if ( (fd == -1) || (hashp->new_file && !is_disk) ) {
E 6
I 6
D 14
    if ( (fd == -1) || !is_disk ) { 
E 6
E 3
	PAGE_INIT(p);
	return(0);
    }

    if ( is_bucket) page = BUCKET_TO_PAGE (bucket);
    else page = OADDR_TO_PAGE (bucket);
D 5
    if ((lseek ( fd, page << hashp->BSHIFT, L_SET ) == -1) || 
E 5
I 5
    if ((lseek ( fd, page << hashp->BSHIFT, SEEK_SET ) == -1) || 
E 5
	((rsize = read ( fd, p, size )) == -1 )) {
	return(-1);
    } 
    bp = (u_short *)p;
    if ( !rsize ) {
	bp[0] = 0;		/* We hit the EOF, so initialize a new page */
    } else if ( rsize != size ) {
	errno = EFTYPE;		
	return(-1);
    }
    if (!bp[0]) {
	PAGE_INIT(p);
    } else if ( hashp->LORDER != BYTE_ORDER ) {
	register int i;
	register int max;

	if ( is_bitmap ) {
	    max = hashp->BSIZE >> 2;	/* divide by 4 */
	    for ( i=0; i < max; i++ ) {
		BLSWAP(((long *)p)[i]);
	    }
	} else {
	    BSSWAP(bp[0]);
	    max = bp[0] + 2;
	    for ( i=1; i <= max; i++ ) {
		BSSWAP(bp[i]);
	    }
E 14
I 14
	if ((fd == -1) || !is_disk) {
		PAGE_INIT(p);
		return (0);
E 14
	}
D 14
    }
    return (0);
E 14
I 14
	if (is_bucket)
		page = BUCKET_TO_PAGE(bucket);
	else
		page = OADDR_TO_PAGE(bucket);
D 21
	if ((lseek(fd, page << hashp->BSHIFT, SEEK_SET) == -1) ||
E 21
I 21
	if ((lseek(fd, (off_t)page << hashp->BSHIFT, SEEK_SET) == -1) ||
E 21
	    ((rsize = read(fd, p, size)) == -1))
		return (-1);
	bp = (u_short *)p;
	if (!rsize)
		bp[0] = 0;	/* We hit the EOF, so initialize a new page */
	else
		if (rsize != size) {
			errno = EFTYPE;
			return (-1);
		}
D 18
	if (!bp[0]) {
E 18
I 18
	if (!is_bitmap && !bp[0]) {
E 18
		PAGE_INIT(p);
	} else
		if (hashp->LORDER != BYTE_ORDER) {
			register int i, max;

			if (is_bitmap) {
				max = hashp->BSIZE >> 2; /* divide by 4 */
				for (i = 0; i < max; i++)
D 32
					BLSWAP(((long *)p)[i]);
E 32
I 32
					M_32_SWAP(((long *)p)[i]);
E 32
			} else {
D 32
				BSSWAP(bp[0]);
E 32
I 32
				M_16_SWAP(bp[0]);
E 32
				max = bp[0] + 2;
				for (i = 1; i <= max; i++)
D 32
					BSSWAP(bp[i]);
E 32
I 32
					M_16_SWAP(bp[i]);
E 32
			}
		}
	return (0);
E 14
}

D 14
/* 
    Write page p to disk
    -1==>failure
    0==> OK
*/
E 14
I 14
/*
 * Write page p to disk
 *
 * Returns:
 *	 0 ==> OK
 *	-1 ==>failure
 */
E 14
extern int
D 14
__put_page ( p, bucket, is_bucket, is_bitmap )
char	*p;
D 12
int	bucket;
E 12
I 12
u_int	bucket;
E 12
int	is_bucket;
int	is_bitmap;
E 14
I 14
D 23
__put_page(p, bucket, is_bucket, is_bitmap)
E 23
I 23
__put_page(hashp, p, bucket, is_bucket, is_bitmap)
	HTAB *hashp;
E 23
	char *p;
	u_int bucket;
	int is_bucket, is_bitmap;
E 14
{
D 14
    register int size;
    register int fd;
    register int page;
    int	wsize;
E 14
I 14
	register int fd, page, size;
	int wsize;
E 14

D 14
    size = hashp->BSIZE;
D 3
    if ( !hashp->fp && open_temp() ) return (1);
E 3
I 3
    if ( (hashp->fp == -1) && open_temp() ) return (1);
E 3
    fd = hashp->fp;
E 14
I 14
	size = hashp->BSIZE;
D 23
	if ((hashp->fp == -1) && open_temp())
E 23
I 23
	if ((hashp->fp == -1) && open_temp(hashp))
E 23
D 17
		return (1);
E 17
I 17
		return (-1);
E 17
	fd = hashp->fp;
E 14

D 14
    if ( hashp->LORDER != BYTE_ORDER ) {
	register int i;
	register int max;
E 14
I 14
	if (hashp->LORDER != BYTE_ORDER) {
		register int i;
		register int max;
E 14

D 14
	if ( is_bitmap ) {
	    max = hashp->BSIZE >> 2;	/* divide by 4 */
	    for ( i=0; i < max; i++ ) {
		BLSWAP(((long *)p)[i]);
	    }
	} else {
	    max = ((u_short *)p)[0] + 2;
	    for ( i=0; i <= max; i++ ) {
		BSSWAP(((u_short *)p)[i]);
	    }
E 14
I 14
		if (is_bitmap) {
			max = hashp->BSIZE >> 2;	/* divide by 4 */
			for (i = 0; i < max; i++)
D 32
				BLSWAP(((long *)p)[i]);
E 32
I 32
				M_32_SWAP(((long *)p)[i]);
E 32
		} else {
			max = ((u_short *)p)[0] + 2;
			for (i = 0; i <= max; i++)
D 32
				BSSWAP(((u_short *)p)[i]);
E 32
I 32
				M_16_SWAP(((u_short *)p)[i]);
E 32
		}
E 14
	}
D 14
    }
    if (is_bucket ) page = BUCKET_TO_PAGE (bucket);
    else page = OADDR_TO_PAGE ( bucket );
D 5
    if ((lseek ( fd, page << hashp->BSHIFT, L_SET ) == -1) || 
E 5
I 5
    if ((lseek ( fd, page << hashp->BSHIFT, SEEK_SET ) == -1) || 
E 5
	((wsize = write ( fd, p, size )) == -1 )) {
	/* Errno is set */
	return(-1);
    }
    if ( wsize != size ) {
	errno = EFTYPE;	
	return(-1);
    }
    return(0);
E 14
I 14
	if (is_bucket)
		page = BUCKET_TO_PAGE(bucket);
	else
		page = OADDR_TO_PAGE(bucket);
D 21
	if ((lseek(fd, page << hashp->BSHIFT, SEEK_SET) == -1) ||
E 21
I 21
	if ((lseek(fd, (off_t)page << hashp->BSHIFT, SEEK_SET) == -1) ||
E 21
	    ((wsize = write(fd, p, size)) == -1))
		/* Errno is set */
		return (-1);
	if (wsize != size) {
		errno = EFTYPE;
		return (-1);
	}
	return (0);
E 14
}
I 14

E 14
#define BYTE_MASK	((1 << INT_BYTE_SHIFT) -1)
/*
D 14
    Initialize a new bitmap page.  Bitmap pages are left in memory
    once they are read in.
*/
E 14
I 14
 * Initialize a new bitmap page.  Bitmap pages are left in memory
 * once they are read in.
 */
E 14
D 15
extern u_long *
E 15
I 15
extern int
E 15
D 23
__init_bitmap(pnum, nbits, ndx)
E 23
I 23
__init_bitmap(hashp, pnum, nbits, ndx)
	HTAB *hashp;
E 23
D 14
u_short	pnum;
int	nbits;
int	ndx;
E 14
I 14
	int pnum, nbits, ndx;
E 14
{
D 14
    u_long	*ip;
    int		clearints;
    int		clearbytes;
E 14
I 14
	u_long *ip;
	int clearbytes, clearints;
E 14

D 14
    if ( !(ip = (u_long *)malloc (hashp->BSIZE)) ) return (NULL);
I 7
D 12
    hashp->exmaps++;
E 12
I 12
    hashp->nmaps++;
E 12
E 7
    clearints = ((nbits - 1) >> INT_BYTE_SHIFT) + 1;
    clearbytes = clearints << INT_TO_BYTE;
    memset ((char *)ip, 0, clearbytes );
    memset ( ((char *) ip) + clearbytes, 0xFF, 
		hashp->BSIZE-clearbytes );
    ip[clearints-1] = ALL_SET << (nbits & BYTE_MASK);
    SETBIT(ip, 0);
    hashp->BITMAPS[ndx] = pnum;
    hashp->mapp[ndx] = ip;
    return(ip);
E 14
I 14
D 33
	if (!(ip = malloc(hashp->BSIZE)))
E 33
I 33
	if ((ip = (u_long *)malloc(hashp->BSIZE)) == NULL)
E 33
D 15
		return (NULL);
E 15
I 15
		return (1);
E 15
	hashp->nmaps++;
	clearints = ((nbits - 1) >> INT_BYTE_SHIFT) + 1;
	clearbytes = clearints << INT_TO_BYTE;
D 15
	memset((char *)ip, 0, clearbytes);
	memset(((char *)ip) + clearbytes, 0xFF,
E 15
I 15
	(void)memset((char *)ip, 0, clearbytes);
	(void)memset(((char *)ip) + clearbytes, 0xFF,
E 15
	    hashp->BSIZE - clearbytes);
	ip[clearints - 1] = ALL_SET << (nbits & BYTE_MASK);
	SETBIT(ip, 0);
	hashp->BITMAPS[ndx] = (u_short)pnum;
	hashp->mapp[ndx] = ip;
D 15
	return (ip);
E 15
I 15
	return (0);
E 15
E 14
}
I 14

E 14
D 15
static int
E 15
I 15
static u_long
E 15
D 14
first_free ( map )
u_long map;
E 14
I 14
first_free(map)
	u_long map;
E 14
{
D 14
    register u_long      mask;
    register u_long      i;
E 14
I 14
	register u_long i, mask;
E 14

D 14
    mask = 0x1;
    for ( i=0; i < BITS_PER_MAP; i++ ) {
	if ( !(mask & map) ) return(i);
	mask = mask << 1;
    }
    return ( i );
E 14
I 14
	mask = 0x1;
	for (i = 0; i < BITS_PER_MAP; i++) {
		if (!(mask & map))
			return (i);
		mask = mask << 1;
	}
	return (i);
E 14
}

D 14
static u_short
overflow_page ( )
E 14
I 14
D 23
static  u_short
overflow_page()
E 23
I 23
static u_short
overflow_page(hashp)
	HTAB *hashp;
E 23
E 14
{
D 14
    register	int max_free;
    register	int splitnum;
    register	u_long *freep;
    register	int offset;
    u_short	addr;
    int		in_use_bits;
    int		free_page, free_bit;
    int		i, j, bit;
E 14
I 14
	register u_long *freep;
	register int max_free, offset, splitnum;
	u_short addr;
D 16
	int bit, free_bit, free_page, i, in_use_bits, j;
E 16
I 16
	int bit, first_page, free_bit, free_page, i, in_use_bits, j;
E 16
E 14
#ifdef DEBUG2
D 14
    int	tmp1, tmp2;
E 14
I 14
	int tmp1, tmp2;
E 14
#endif
I 14
D 16
	splitnum = __log2(hashp->MAX_BUCKET);
E 16
I 16
	splitnum = hashp->OVFL_POINT;
E 16
	max_free = hashp->SPARES[splitnum];
E 14

D 14
    splitnum = __log2(hashp->MAX_BUCKET);
    max_free = hashp->SPARES[splitnum];
E 14
I 14
	free_page = (max_free - 1) >> (hashp->BSHIFT + BYTE_SHIFT);
	free_bit = (max_free - 1) & ((hashp->BSIZE << BYTE_SHIFT) - 1);
E 14

D 14
    free_page = (max_free-1) >> (hashp->BSHIFT + BYTE_SHIFT);
    free_bit  = (max_free-1) & ((hashp->BSIZE << BYTE_SHIFT) - 1);
E 14
I 14
	/* Look through all the free maps to find the first free block */
D 16
	for (i = 0; i <= free_page; i++) {
E 16
I 16
	first_page = hashp->LAST_FREED >>(hashp->BSHIFT + BYTE_SHIFT);
	for ( i = first_page; i <= free_page; i++ ) {
E 16
		if (!(freep = (u_long *)hashp->mapp[i]) &&
D 23
		    !(freep = fetch_bitmap(i)))
E 23
I 23
		    !(freep = fetch_bitmap(hashp, i)))
E 23
			return (NULL);
		if (i == free_page)
			in_use_bits = free_bit;
		else
			in_use_bits = (hashp->BSIZE << BYTE_SHIFT) - 1;
E 14
D 16

D 14
    /* Look through all the free maps to find the first free block */
    for ( i = 0; i <= free_page; i++ ) {
D 12
	if (!(freep = (u_long *)hashp->mapp[i]) ) return(NULL);
E 12
I 12
	if (!(freep = (u_long *)hashp->mapp[i])  &&
	    !(freep = fetch_bitmap(i)) ) {
	    return ( NULL );
E 14
I 14
		for (j = 0, bit = 0; bit <= in_use_bits;
		    j++, bit += BITS_PER_MAP)
E 16
I 16
		
		if (i == first_page) {
			bit = hashp->LAST_FREED &
			    ((hashp->BSIZE << BYTE_SHIFT) - 1);
			j = bit / BITS_PER_MAP;
			bit = bit & ~(BITS_PER_MAP - 1);
		} else {
			bit = 0;
			j = 0;
		}
		for (; bit <= in_use_bits; j++, bit += BITS_PER_MAP)
E 16
			if (freep[j] != ALL_SET)
				goto found;
E 14
	}
E 12
D 14
	if ( i == free_page ) in_use_bits = free_bit;
	else in_use_bits = (hashp->BSIZE << BYTE_SHIFT) -1;
E 14

D 14
	for (j = 0, bit = 0; bit <= in_use_bits; j++, bit += BITS_PER_MAP ) {
	     if ( freep[j] != ALL_SET ) goto found;
	}
    }
    /* No Free Page Found */
    hashp->SPARES[splitnum]++;
    offset = hashp->SPARES[splitnum] - 
	     (splitnum ? hashp->SPARES[splitnum-1] : 0);
E 14
I 14
	/* No Free Page Found */
I 16
	hashp->LAST_FREED = hashp->SPARES[splitnum];
E 16
	hashp->SPARES[splitnum]++;
	offset = hashp->SPARES[splitnum] -
	    (splitnum ? hashp->SPARES[splitnum - 1] : 0);
E 14

I 16
#define	OVMSG	"HASH: Out of overflow pages.  Increase page size\n"
	if (offset > SPLITMASK) {
		if (++splitnum >= NCACHED) {
			(void)write(STDERR_FILENO, OVMSG, sizeof(OVMSG) - 1);
			return (NULL);
		}
		hashp->OVFL_POINT = splitnum;
		hashp->SPARES[splitnum] = hashp->SPARES[splitnum-1];
		hashp->SPARES[splitnum-1]--;
D 29
		offset = 0;
E 29
I 29
		offset = 1;
E 29
	}

E 16
D 14
    /* Check if we need to allocate a new bitmap page */
    if ( free_bit == (hashp->BSIZE << BYTE_SHIFT) - 1 ) {
	free_page++;
E 14
I 14
	/* Check if we need to allocate a new bitmap page */
	if (free_bit == (hashp->BSIZE << BYTE_SHIFT) - 1) {
		free_page++;
E 14
I 13
D 16
#define	OVMSG	"hash: out of overflow pages; increase page size\n"
E 16
E 13
D 14
	if ( free_page >= NCACHED ) {
D 13
	    fprintf ( stderr, 
		"HASH: Out of overflow pages.  Increase page size\n" );
E 13
I 13
	    (void) write (STDERR_FILENO, OVMSG, sizeof(OVMSG) - 1);
E 13
	    return(NULL);
	}
	/* 
	    This is tricky.  The 1 indicates that you want the
	    new page allocated with 1 clear bit.  Actually, you
	    are going to allocate 2 pages from this map.  The first
	    is going to be the map page, the second is the overflow
	    page we were looking for.  The init_bitmap routine
	    automatically, sets the first bit of itself to indicate
	    that the bitmap itself is in use.  We would explicitly
	    set the second bit, but don't have to if we tell init_bitmap
	    not to leave it clear in the first place.
	*/
	__init_bitmap ( OADDR_OF(splitnum, offset), 1, free_page );
	hashp->SPARES[splitnum]++;
E 14
I 14
		if (free_page >= NCACHED) {
			(void)write(STDERR_FILENO, OVMSG, sizeof(OVMSG) - 1);
			return (NULL);
		}
		/*
		 * This is tricky.  The 1 indicates that you want the new page
		 * allocated with 1 clear bit.  Actually, you are going to
		 * allocate 2 pages from this map.  The first is going to be
		 * the map page, the second is the overflow page we were
		 * looking for.  The init_bitmap routine automatically, sets
		 * the first bit of itself to indicate that the bitmap itself
		 * is in use.  We would explicitly set the second bit, but
		 * don't have to if we tell init_bitmap not to leave it clear
		 * in the first place.
		 */
D 15
		__init_bitmap(OADDR_OF(splitnum, offset), 1, free_page);
E 15
I 15
D 23
		if (__init_bitmap((int)OADDR_OF(splitnum, offset),
E 23
I 23
		if (__init_bitmap(hashp, (int)OADDR_OF(splitnum, offset),
E 23
		    1, free_page))
			return (NULL);
E 15
		hashp->SPARES[splitnum]++;
E 14
#ifdef DEBUG2
D 14
	free_bit = 2;
E 14
I 14
		free_bit = 2;
E 14
#endif
D 14
	offset++;
    } else {
	/* 
		Free_bit addresses the last used bit.  Bump it to
		address the first available bit.
	*/	
	free_bit++;
	SETBIT ( freep, free_bit );
    }
E 14
I 14
		offset++;
I 16
		if (offset > SPLITMASK) {
			if (++splitnum >= NCACHED) {
				(void)write(STDERR_FILENO, OVMSG,
				    sizeof(OVMSG) - 1);
				return (NULL);
			}
			hashp->OVFL_POINT = splitnum;
			hashp->SPARES[splitnum] = hashp->SPARES[splitnum-1];
			hashp->SPARES[splitnum-1]--;
			offset = 0;
		}
E 16
	} else {
		/*
		 * Free_bit addresses the last used bit.  Bump it to address
		 * the first available bit.
		 */
		free_bit++;
		SETBIT(freep, free_bit);
	}
E 14

D 14
    /* Calculate address of the new overflow page */
    if ( offset > SPLITMASK ) {
D 13
	fprintf ( stderr, 
	    "HASH: Out of overflow pages.  Increase page size\n" );
E 13
I 13
	(void) write (STDERR_FILENO, OVMSG, sizeof(OVMSG) - 1);
E 13
	return(NULL);
    }
    addr = OADDR_OF(splitnum, offset);
E 14
I 14
	/* Calculate address of the new overflow page */
D 16
	if (offset > SPLITMASK) {
		(void)write(STDERR_FILENO, OVMSG, sizeof(OVMSG) - 1);
		return (NULL);
	}
E 16
	addr = OADDR_OF(splitnum, offset);
E 14
#ifdef DEBUG2
D 14
    fprintf ( stderr, "OVERFLOW_PAGE: ADDR: %d BIT: %d PAGE %d\n",
		addr, free_bit, free_page );
E 14
I 14
	(void)fprintf(stderr, "OVERFLOW_PAGE: ADDR: %d BIT: %d PAGE %d\n",
	    addr, free_bit, free_page);
E 14
#endif
D 14
    return(addr);
E 14
I 14
	return (addr);
E 14

found:
D 14
    bit = bit + first_free(freep[j]);
    SETBIT(freep,bit);
E 14
I 14
	bit = bit + first_free(freep[j]);
	SETBIT(freep, bit);
E 14
#ifdef DEBUG2
D 14
    tmp1 = bit;
    tmp2 = i;
E 14
I 14
	tmp1 = bit;
	tmp2 = i;
E 14
#endif
D 14
    /* 
	Bits are addressed starting with 0, but overflow pages are
	addressed beginning at 1. Bit is a bit addressnumber, so we 
	need to increment it to convert it to a page number.
    */
    bit = 1 + bit + (i * (hashp->BSIZE << BYTE_SHIFT));
E 14
I 14
	/*
	 * Bits are addressed starting with 0, but overflow pages are addressed
	 * beginning at 1. Bit is a bit addressnumber, so we need to increment
	 * it to convert it to a page number.
	 */
	bit = 1 + bit + (i * (hashp->BSIZE << BYTE_SHIFT));
I 16
	if (bit >= hashp->LAST_FREED)
		hashp->LAST_FREED = bit - 1;
E 16
E 14

D 14
    /* Calculate the split number for this page */
    for ( i = 0; (i < splitnum) && (bit > hashp->SPARES[i]); i++ );
    offset =(i ? bit - hashp->SPARES[i-1] : bit );
    if ( offset >= SPLITMASK ) return(NULL);/* Out of overflow pages */
    addr = OADDR_OF(i, offset);
E 14
I 14
	/* Calculate the split number for this page */
	for (i = 0; (i < splitnum) && (bit > hashp->SPARES[i]); i++);
	offset = (i ? bit - hashp->SPARES[i - 1] : bit);
	if (offset >= SPLITMASK)
		return (NULL);	/* Out of overflow pages */
	addr = OADDR_OF(i, offset);
E 14
#ifdef DEBUG2
D 14
    fprintf ( stderr, "OVERFLOW_PAGE: ADDR: %d BIT: %d PAGE %d\n",
		addr, tmp1, tmp2 );
E 14
I 14
	(void)fprintf(stderr, "OVERFLOW_PAGE: ADDR: %d BIT: %d PAGE %d\n",
	    addr, tmp1, tmp2);
E 14
#endif

D 14
    /* Allocate and return the overflow page */
    return (addr);
E 14
I 14
	/* Allocate and return the overflow page */
	return (addr);
E 14
}

/*
D 14
    Mark this overflow page as free.
*/
__free_ovflpage ( obufp )
BUFHEAD	*obufp;
E 14
I 14
 * Mark this overflow page as free.
 */
extern void
D 23
__free_ovflpage(obufp)
E 23
I 23
__free_ovflpage(hashp, obufp)
	HTAB *hashp;
E 23
	BUFHEAD *obufp;
E 14
{
D 14
    register u_short addr = obufp->addr;
    int	free_page, free_bit;
    int bit_address;
    u_short ndx;
    u_long *freep;
    int j;
E 14
I 14
	register u_short addr;
	u_long *freep;
	int bit_address, free_page, free_bit;
	u_short ndx;
E 14

I 14
	addr = obufp->addr;
E 14
#ifdef DEBUG1
D 14
    fprintf ( stderr, "Freeing %d\n", addr );
E 14
I 14
	(void)fprintf(stderr, "Freeing %d\n", addr);
E 14
#endif
D 14
    ndx = (((u_short)addr) >> SPLITSHIFT);
    bit_address = (ndx ? hashp->SPARES[ndx-1] : 0) + (addr & SPLITMASK) - 1;
    free_page = (bit_address >> (hashp->BSHIFT + BYTE_SHIFT));
    free_bit  = bit_address & ((hashp->BSIZE << BYTE_SHIFT) - 1);
E 14
I 14
	ndx = (((u_short)addr) >> SPLITSHIFT);
	bit_address =
	    (ndx ? hashp->SPARES[ndx - 1] : 0) + (addr & SPLITMASK) - 1;
I 16
	 if (bit_address < hashp->LAST_FREED)
		hashp->LAST_FREED = bit_address;
E 16
	free_page = (bit_address >> (hashp->BSHIFT + BYTE_SHIFT));
	free_bit = bit_address & ((hashp->BSIZE << BYTE_SHIFT) - 1);
E 14

D 12
    freep = hashp->mapp[free_page];
    assert(freep);
E 12
I 12
D 14
    if ( !(freep = hashp->mapp[free_page]) &&
	 !(freep = fetch_bitmap( free_page )) ) {
	/* 
	    This had better never happen.  It means we tried to
	    read a bitmap that has already had overflow pages allocated
	    off it, and we failed to read it from the file
	*/
	assert(0);
    }
E 12
    CLRBIT(freep, free_bit);
E 14
I 14
	if (!(freep = hashp->mapp[free_page]))
D 23
		freep = fetch_bitmap(free_page);
E 23
I 23
		freep = fetch_bitmap(hashp, free_page);
E 23
#ifdef DEBUG
	/*
	 * This had better never happen.  It means we tried to read a bitmap
	 * that has already had overflow pages allocated off it, and we
	 * failed to read it from the file.
	 */
	if (!freep)
		assert(0);
#endif
	CLRBIT(freep, free_bit);
E 14
#ifdef DEBUG2
D 14
    fprintf ( stderr, "FREE_OVFLPAGE: ADDR: %d BIT: %d PAGE %d\n",
		obufp->addr, free_bit, free_page );
E 14
I 14
	(void)fprintf(stderr, "FREE_OVFLPAGE: ADDR: %d BIT: %d PAGE %d\n",
	    obufp->addr, free_bit, free_page);
E 14
#endif
D 14
    __reclaim_buf ( obufp );
    return;
E 14
I 14
D 23
	__reclaim_buf(obufp);
E 23
I 23
	__reclaim_buf(hashp, obufp);
E 23
E 14
}

/*
D 14
0 success
-1 failure
*/
E 14
I 14
 * Returns:
 *	 0 success
 *	-1 failure
 */
E 14
static int
D 23
open_temp()
E 23
I 23
open_temp(hashp)
	HTAB *hashp;
E 23
{
D 2
    char        *namestr = "_hashXXXXXX";
E 2
I 2
D 14
    sigset_t	set, oset;
D 4
    char	*namestr = "_hashXXXXXX";
E 4
I 4
D 10
    char	namestr[] = "_hashXXXXXX";
E 10
I 10
    static char	namestr[] = "_hashXXXXXX";
E 14
I 14
	sigset_t set, oset;
	static char namestr[] = "_hashXXXXXX";
E 14
E 10
E 4
E 2

D 2
    if ((hashp->fp = mkstemp ( namestr )) == -1){
	return (-1);
E 2
I 2
D 14
    /* Block signals; make sure file goes away at process exit. */
    sigemptyset(&set);
    sigaddset(&set, SIGHUP);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGTERM);
    (void)sigprocmask(SIG_BLOCK, &set, &oset);
    if ((hashp->fp = mkstemp ( namestr )) != -1) {
	(void)unlink(namestr);
	(void)fcntl(hashp->fp, F_SETFD, 1);
E 2
    }
D 2
    unlink(namestr);    /* Make sure file goes away at process exit*/
    return(0);
E 2
I 2
    (void)sigprocmask(SIG_SETMASK, &oset, (sigset_t *)NULL);
    return(hashp->fp != -1 ? 0 : -1);
E 14
I 14
	/* Block signals; make sure file goes away at process exit. */
D 22
	sigfillset(&set);
E 22
I 22
	(void)sigfillset(&set);
E 22
	(void)sigprocmask(SIG_BLOCK, &set, &oset);
	if ((hashp->fp = mkstemp(namestr)) != -1) {
		(void)unlink(namestr);
		(void)fcntl(hashp->fp, F_SETFD, 1);
	}
	(void)sigprocmask(SIG_SETMASK, &oset, (sigset_t *)NULL);
	return (hashp->fp != -1 ? 0 : -1);
E 14
E 2
}

D 14
/* 
    We have to know that the key will fit, but the
    last entry on the page is an overflow pair, so we
    need to shift things.
*/
E 14
I 14
/*
 * We have to know that the key will fit, but the last entry on the page is
 * an overflow pair, so we need to shift things.
 */
E 14
static void
D 14
squeeze_key ( sp, key, val )
u_short	*sp;
DBT	*key;
DBT	*val;
E 14
I 14
squeeze_key(sp, key, val)
	u_short *sp;
	const DBT *key, *val;
E 14
{
D 14
    register	char	*p = (char *)sp;
    u_short	free_space, off;
    u_short	pageno, n;
E 14
I 14
	register char *p;
	u_short free_space, n, off, pageno;
E 14

D 14
    n = sp[0];
    free_space = FREESPACE(sp);
    off = OFFSET(sp);
E 14
I 14
	p = (char *)sp;
	n = sp[0];
	free_space = FREESPACE(sp);
	off = OFFSET(sp);
E 14

D 14
    pageno = sp[n-1];
    off -= key->size;
    sp[n-1] = off;
    bcopy ( key->data, p + off, key->size );
    off -= val->size;
    sp[n] = off;
    bcopy ( val->data, p + off, val->size );
    sp[0] = n+2;
    sp[n+1] = pageno;
    sp[n+2] = OVFLPAGE;
    FREESPACE(sp) = free_space - PAIRSIZE(key,val);
    OFFSET(sp) = off;
E 14
I 14
	pageno = sp[n - 1];
	off -= key->size;
	sp[n - 1] = off;
D 25
	bcopy(key->data, p + off, key->size);
E 25
I 25
	memmove(p + off, key->data, key->size);
E 25
	off -= val->size;
	sp[n] = off;
D 25
	bcopy(val->data, p + off, val->size);
E 25
I 25
	memmove(p + off, val->data, val->size);
E 25
	sp[0] = n + 2;
	sp[n + 1] = pageno;
	sp[n + 2] = OVFLPAGE;
	FREESPACE(sp) = free_space - PAIRSIZE(key, val);
	OFFSET(sp) = off;
E 14
}

I 12
static u_long *
D 14
fetch_bitmap ( ndx ) 
int	ndx;
E 14
I 14
D 23
fetch_bitmap(ndx)
E 23
I 23
fetch_bitmap(hashp, ndx)
	HTAB *hashp;
E 23
	int ndx;
E 14
{
D 14
    if ( ndx >= hashp->nmaps  ||
	!(hashp->mapp[ndx] = (u_long *)malloc ( hashp->BSIZE )) ||
	 __get_page ((char *)hashp->mapp[ndx], hashp->BITMAPS[ndx], 0, 1, 1)) {

	    return(NULL);
    }
    return ( hashp->mapp[ndx] );
E 14
I 14
D 33
	if (ndx >= hashp->nmaps ||
	    !(hashp->mapp[ndx] = malloc(hashp->BSIZE)) ||
D 23
	    __get_page((char *)hashp->mapp[ndx],
E 23
I 23
	    __get_page(hashp, (char *)hashp->mapp[ndx],
E 23
	    hashp->BITMAPS[ndx], 0, 1, 1))
E 33
I 33
	if (ndx >= hashp->nmaps)
E 33
		return (NULL);
I 33
	if ((hashp->mapp[ndx] = (u_long *)malloc(hashp->BSIZE)) == NULL)
		return (NULL);
	if (__get_page(hashp,
	    (char *)hashp->mapp[ndx], hashp->BITMAPS[ndx], 0, 1, 1)) {
		free(hashp->mapp[ndx]);
		return (NULL);
	}
E 33
	return (hashp->mapp[ndx]);
E 14
}
I 14

E 14
E 12
#ifdef DEBUG4
D 14
print_chain ( addr )
short	addr;
E 14
I 14
int
print_chain(addr)
	int addr;
E 14
{
D 14
	BUFHEAD	*bufp;
	short	*bp;
	short	oaddr;
E 14
I 14
	BUFHEAD *bufp;
	short *bp, oaddr;
E 14

D 14
	fprintf ( stderr, "%d ", addr );
	bufp = __get_buf ( (int)addr, NULL, 0 );
E 14
I 14
	(void)fprintf(stderr, "%d ", addr);
D 23
	bufp = __get_buf(addr, NULL, 0);
E 23
I 23
	bufp = __get_buf(hashp, addr, NULL, 0);
E 23
E 14
	bp = (short *)bufp->page;
D 14
	while ( bp[0] && 
		((bp[bp[0]] == OVFLPAGE) ||
		 ((bp[0] > 2) && bp[2] < REAL_KEY))) {
		oaddr = bp[bp[0]-1];
		fprintf ( stderr, "%d ", (int)oaddr );
		bufp = __get_buf ( (int)oaddr, bufp, 0 );
E 14
I 14
	while (bp[0] && ((bp[bp[0]] == OVFLPAGE) ||
		((bp[0] > 2) && bp[2] < REAL_KEY))) {
		oaddr = bp[bp[0] - 1];
		(void)fprintf(stderr, "%d ", (int)oaddr);
D 23
		bufp = __get_buf((int)oaddr, bufp, 0);
E 23
I 23
		bufp = __get_buf(hashp, (int)oaddr, bufp, 0);
E 23
E 14
		bp = (short *)bufp->page;
	}
D 14
	fprintf ( stderr, "\n" );
E 14
I 14
	(void)fprintf(stderr, "\n");
E 14
}
#endif
E 1
