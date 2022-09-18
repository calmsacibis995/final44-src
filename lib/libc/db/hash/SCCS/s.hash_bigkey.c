h12153
s 00003/00005/00638
d D 8.2 94/02/21 17:43:40 bostic 12 11
c cast alloc's to shut SunOS up
e
s 00002/00002/00641
d D 8.1 93/06/04 15:21:54 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00635
d D 5.10 93/02/16 12:33:29 bostic 10 9
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00001/00001/00642
d D 5.9 93/02/11 11:39:48 bostic 9 8
c move db.h to the end of the includes, make compat.h work better
e
s 00053/00040/00590
d D 5.8 93/01/17 16:20:21 bostic 8 7
c can't have a global "hashp", pass it around as an argument
c change default_hash to __default_hash for the same reason
e
s 00006/00007/00624
d D 5.7 91/09/08 12:17:32 bostic 7 6
c delete unused arguments to big_delete, big_keydata; check return
c value of big_return
e
s 00503/00518/00128
d D 5.6 91/09/04 12:56:25 bostic 6 5
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00005/00002/00641
d D 5.5 91/03/12 09:33:55 bostic 5 4
c Make all bucket and overflow addresses unsigned
e
s 00005/00005/00638
d D 5.4 91/03/03 14:32:55 bostic 4 3
c DBT data changed to be unsigned, fix routines that take flags
e
s 00001/00001/00642
d D 5.3 91/02/24 16:44:23 bostic 3 2
c There was a reason they included <sys/param.h>  (MIN, MAX)
e
s 00003/00002/00640
d D 5.2 91/02/22 17:23:34 bostic 2 1
c ANSI prototypes
e
s 00642/00000/00000
d D 5.1 91/02/12 20:27:54 bostic 1 0
c date and time created 91/02/12 20:27:54 by bostic
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 6
/******************************************************************************
E 6
I 6
/*
 * PACKAGE: hash
 * DESCRIPTION:
 *	Big key/data handling for the hashing package.
 *
 * ROUTINES:
 * External
 *	__big_keydata
 *	__big_split
 *	__big_insert
 *	__big_return
 *	__big_delete
 *	__find_last_page
 * Internal
 *	collect_key
 *	collect_data
 */
E 6

D 6
PACKAGE: hash

DESCRIPTION: 
	Big key/data handling for the hashing package.

ROUTINES: 
    External
	__big_keydata
	__big_split
	__big_insert
	__big_return
	__big_delete
	__find_last_page
    Internal
	collect_key
	collect_data
******************************************************************************/
/* Includes */
E 6
D 2
#include <sys/param.h>
#include <sys/file.h>
E 2
I 2
D 3
#include <sys/types.h>
E 3
I 3
#include <sys/param.h>
E 3
E 2
D 6
#include <assert.h>
E 6
D 8
#include <errno.h>
E 8
I 8

E 8
D 9
#include <db.h>
E 9
I 8
#include <errno.h>
E 8
#include <stdio.h>
I 2
#include <stdlib.h>
#include <string.h>
I 8

E 8
I 6
#ifdef DEBUG
#include <assert.h>
#endif
I 8

I 9
#include <db.h>
E 9
E 8
E 6
E 2
#include "hash.h"
#include "page.h"
I 6
#include "extern.h"
E 6

D 6
/* Externals */
/* buf.c */
extern BUFHEAD *__get_buf();
E 6
I 6
D 8
static int collect_key __P((BUFHEAD *, int, DBT *, int));
static int collect_data __P((BUFHEAD *, int, int));
E 8
I 8
static int collect_key __P((HTAB *, BUFHEAD *, int, DBT *, int));
static int collect_data __P((HTAB *, BUFHEAD *, int, int));
E 8
E 6

I 5
D 6
/* dynahash.c */
extern	u_int call_hash();

E 5
/* page.c */
extern BUFHEAD *__add_ovflpage();

/* My externals */
extern int __big_keydata();
extern int __big_split();
extern int __big_insert();
extern int __big_return();
extern int __big_delete();
extern u_short __find_last_page();
extern int __find_bigpair();

/* My internals */
static int collect_key();
static int collect_data();

#ifdef HASH_STATISTICS
extern long hash_accesses, hash_collisions, hash_expansions, hash_overflows;
#endif
E 6
/*
D 6
Big_insert

You need to do an insert and the key/data pair is too big
0 ==> OK
-1 ==> ERROR
*/
E 6
I 6
 * Big_insert
 *
 * You need to do an insert and the key/data pair is too big
 *
 * Returns:
 * 0 ==> OK
 *-1 ==> ERROR
 */
E 6
extern int
D 6
__big_insert ( bufp, key, val )
BUFHEAD *bufp;
DBT	*key, *val;
E 6
I 6
D 8
__big_insert(bufp, key, val)
E 8
I 8
__big_insert(hashp, bufp, key, val)
	HTAB *hashp;
E 8
	BUFHEAD *bufp;
	const DBT *key, *val;
E 6
{
D 6
    char	*cp = bufp->page;	/* Character pointer of p */
    register u_short	*p = (u_short *)cp;
    char	*key_data, *val_data;
    int		key_size, val_size;
    int		n;
    u_short	space, move_bytes, off;
E 6
I 6
	register u_short *p;
	int key_size, n, val_size;
	u_short space, move_bytes, off;
	char *cp, *key_data, *val_data;
E 6

D 4
    key_data = key->data;
E 4
I 4
D 6
    key_data = (char *)key->data;
E 4
    key_size = key->size;
D 4
    val_data = val->data;
E 4
I 4
    val_data = (char *)val->data;
E 4
    val_size = val->size;
E 6
I 6
	cp = bufp->page;		/* Character pointer of p. */
	p = (u_short *)cp;
E 6

D 6
    /* First move the Key */
    for ( space = FREESPACE(p) - BIGOVERHEAD; 
	  key_size; 
	  space = FREESPACE(p) - BIGOVERHEAD ) {
	move_bytes = MIN(space, key_size);
	off = OFFSET(p) - move_bytes;
	bcopy (key_data, cp+off, move_bytes );
	key_size -= move_bytes;
	key_data += move_bytes;
	n = p[0];
	p[++n] = off;
	p[0] = ++n;
	FREESPACE(p) = off - PAGE_META(n);
	OFFSET(p) = off;
	p[n] = PARTIAL_KEY;
	bufp = __add_ovflpage(bufp);
	if ( !bufp ) {
	    return(-1);
E 6
I 6
	key_data = (char *)key->data;
	key_size = key->size;
	val_data = (char *)val->data;
	val_size = val->size;

	/* First move the Key */
	for (space = FREESPACE(p) - BIGOVERHEAD; key_size;
	    space = FREESPACE(p) - BIGOVERHEAD) {
		move_bytes = MIN(space, key_size);
		off = OFFSET(p) - move_bytes;
D 10
		bcopy(key_data, cp + off, move_bytes);
E 10
I 10
		memmove(cp + off, key_data, move_bytes);
E 10
		key_size -= move_bytes;
		key_data += move_bytes;
		n = p[0];
		p[++n] = off;
		p[0] = ++n;
		FREESPACE(p) = off - PAGE_META(n);
		OFFSET(p) = off;
		p[n] = PARTIAL_KEY;
D 8
		bufp = __add_ovflpage(bufp);
E 8
I 8
		bufp = __add_ovflpage(hashp, bufp);
E 8
		if (!bufp)
			return (-1);
		n = p[0];
		if (!key_size)
			if (FREESPACE(p)) {
				move_bytes = MIN(FREESPACE(p), val_size);
				off = OFFSET(p) - move_bytes;
				p[n] = off;
D 10
				bcopy(val_data, cp + off, move_bytes);
E 10
I 10
				memmove(cp + off, val_data, move_bytes);
E 10
				val_data += move_bytes;
				val_size -= move_bytes;
				p[n - 2] = FULL_KEY_DATA;
				FREESPACE(p) = FREESPACE(p) - move_bytes;
				OFFSET(p) = off;
			} else
				p[n - 2] = FULL_KEY;
		p = (u_short *)bufp->page;
		cp = bufp->page;
		bufp->flags |= BUF_MOD;
E 6
	}
D 6
	n = p[0];
	if ( !key_size ) {
	    if ( FREESPACE(p) ) {
		move_bytes = MIN (FREESPACE(p), val_size);
E 6
I 6

	/* Now move the data */
	for (space = FREESPACE(p) - BIGOVERHEAD; val_size;
	    space = FREESPACE(p) - BIGOVERHEAD) {
		move_bytes = MIN(space, val_size);
		/*
		 * Here's the hack to make sure that if the data ends on the
		 * same page as the key ends, FREESPACE is at least one.
		 */
		if (space == val_size && val_size == val->size)
			move_bytes--;
E 6
		off = OFFSET(p) - move_bytes;
D 6
		p[n] = off;
		bcopy ( val_data, cp + off, move_bytes );
		val_data += move_bytes;
E 6
I 6
D 10
		bcopy(val_data, cp + off, move_bytes);
E 10
I 10
		memmove(cp + off, val_data, move_bytes);
E 10
E 6
		val_size -= move_bytes;
D 6
		p[n-2] = FULL_KEY_DATA;
		FREESPACE(p) = FREESPACE(p) - move_bytes;
E 6
I 6
		val_data += move_bytes;
		n = p[0];
		p[++n] = off;
		p[0] = ++n;
		FREESPACE(p) = off - PAGE_META(n);
E 6
		OFFSET(p) = off;
D 6
	    }
	    else p[n-2] = FULL_KEY;
E 6
I 6
		if (val_size) {
			p[n] = FULL_KEY;
D 8
			bufp = __add_ovflpage(bufp);
E 8
I 8
			bufp = __add_ovflpage(hashp, bufp);
E 8
			if (!bufp)
				return (-1);
			cp = bufp->page;
			p = (u_short *)cp;
		} else
			p[n] = FULL_KEY_DATA;
		bufp->flags |= BUF_MOD;
E 6
	}
D 6
	p = (u_short *)bufp->page;
	cp = bufp->page;
	bufp->flags |= BUF_MOD;
    }

    /* Now move the data */
    for ( space = FREESPACE(p) - BIGOVERHEAD; 
	  val_size; 
	  space = FREESPACE(p) - BIGOVERHEAD ) {
	move_bytes = MIN(space, val_size);
	/*
	    Here's the hack to make sure that if the data ends
	    on the same page as the key ends, FREESPACE is
	    at least one
	*/
	if ( space == val_size && val_size == val->size ) {
	    move_bytes--;
	}
	off = OFFSET(p) - move_bytes;
	bcopy (val_data, cp+off, move_bytes );
	val_size -= move_bytes;
	val_data += move_bytes;
	n = p[0];
	p[++n] = off;
	p[0] = ++n;
	FREESPACE(p) = off - PAGE_META(n);
	OFFSET(p) = off;
	if ( val_size ) {
	    p[n] = FULL_KEY;
	    bufp = __add_ovflpage (bufp);
	    if ( !bufp ) {
		return(-1);
	    }
	    cp = bufp->page;
	    p = (u_short *)cp;
	} else {
	    p[n] = FULL_KEY_DATA;
	}
	bufp->flags |= BUF_MOD;
    }
    return(0);
E 6
I 6
	return (0);
E 6
}

/*
D 6
    Called when bufp's page  contains a partial key (index should be 1)

    All pages in the big key/data pair except bufp are freed.  We cannot
    free bufp because the page pointing to it is lost and we can't
    get rid of its pointer.

    Returns 0 => OK
	    -1 => ERROR
*/
E 6
I 6
 * Called when bufp's page  contains a partial key (index should be 1)
 *
 * All pages in the big key/data pair except bufp are freed.  We cannot
 * free bufp because the page pointing to it is lost and we can't get rid
 * of its pointer.
 *
 * Returns:
 * 0 => OK
 *-1 => ERROR
 */
E 6
extern int
D 6
__big_delete (bufp, ndx)
BUFHEAD	*bufp;
int	ndx;
E 6
I 6
D 7
__big_delete(bufp, ndx)
E 7
I 7
D 8
__big_delete(bufp)
E 8
I 8
__big_delete(hashp, bufp)
	HTAB *hashp;
E 8
E 7
	BUFHEAD *bufp;
D 7
	int ndx;
E 7
E 6
{
D 6
	register	BUFHEAD		*rbufp = bufp;
	register	BUFHEAD		*last_bfp = NULL;
	char	*cp;
	u_short	*bp = (u_short *)bufp->page;
	u_short	*xbp;
	u_short	pageno = 0;
	u_short	off, free_sp;
	int	key_done = 0;
	int	n;
E 6
I 6
	register BUFHEAD *last_bfp, *rbufp;
	u_short *bp, pageno;
	int key_done, n;
E 6

I 6
	rbufp = bufp;
	last_bfp = NULL;
	bp = (u_short *)bufp->page;
	pageno = 0;
	key_done = 0;

E 6
	while (!key_done || (bp[2] != FULL_KEY_DATA)) {
D 6
	    if ( bp[2] == FULL_KEY || bp[2] == FULL_KEY_DATA ) key_done = 1;
E 6
I 6
		if (bp[2] == FULL_KEY || bp[2] == FULL_KEY_DATA)
			key_done = 1;
E 6

D 6
	    /*
		If there is freespace left on a FULL_KEY_DATA page,
		then the data is short and fits entirely on this
		page, and this is the last page.
	    */
	    if ( bp[2] == FULL_KEY_DATA && FREESPACE(bp) ) break;
	    pageno = bp[bp[0]-1];
	    rbufp->flags |= BUF_MOD;
	    rbufp = __get_buf ( pageno, rbufp, 0 );
	    if ( last_bfp ) __free_ovflpage(last_bfp);
	    last_bfp = rbufp;
	    if ( !rbufp ) return(-1);			/* Error */
	    bp = (u_short *)rbufp->page;
E 6
I 6
		/*
		 * If there is freespace left on a FULL_KEY_DATA page, then
		 * the data is short and fits entirely on this page, and this
		 * is the last page.
		 */
		if (bp[2] == FULL_KEY_DATA && FREESPACE(bp))
			break;
		pageno = bp[bp[0] - 1];
		rbufp->flags |= BUF_MOD;
D 8
		rbufp = __get_buf(pageno, rbufp, 0);
E 8
I 8
		rbufp = __get_buf(hashp, pageno, rbufp, 0);
E 8
		if (last_bfp)
D 8
			__free_ovflpage(last_bfp);
E 8
I 8
			__free_ovflpage(hashp, last_bfp);
E 8
		last_bfp = rbufp;
		if (!rbufp)
			return (-1);		/* Error. */
		bp = (u_short *)rbufp->page;
E 6
	}

D 6
	/* 
	    If we get here then rbufp points to the last page of
	    the big key/data pair.  Bufp points to the first
	    one -- it should now be empty pointing to the next
	    page after this pair.  Can't free it because we don't
	    have the page pointing to it.
	*/
E 6
I 6
	/*
	 * If we get here then rbufp points to the last page of the big
	 * key/data pair.  Bufp points to the first one -- it should now be
	 * empty pointing to the next page after this pair.  Can't free it
	 * because we don't have the page pointing to it.
	 */
E 6

D 6
	/* This is information from the last page of the pair */
E 6
I 6
	/* This is information from the last page of the pair. */
E 6
	n = bp[0];
D 6
	pageno = bp[n-1];
E 6
I 6
	pageno = bp[n - 1];
E 6

D 6
	/* Now, bp is the first page of the pair */
E 6
I 6
	/* Now, bp is the first page of the pair. */
E 6
	bp = (u_short *)bufp->page;
D 6
	if ( n > 2 ) {
	    /* There is an overflow page */
	    bp[1] = pageno;
	    bp[2] = OVFLPAGE;
	    bufp->ovfl = rbufp->ovfl;
	} else {
	    /* This is the last page */
	    bufp->ovfl = NULL;
	}
E 6
I 6
	if (n > 2) {
		/* There is an overflow page. */
		bp[1] = pageno;
		bp[2] = OVFLPAGE;
		bufp->ovfl = rbufp->ovfl;
	} else
		/* This is the last page. */
		bufp->ovfl = NULL;
E 6
	n -= 2;
	bp[0] = n;
	FREESPACE(bp) = hashp->BSIZE - PAGE_META(n);
	OFFSET(bp) = hashp->BSIZE - 1;

	bufp->flags |= BUF_MOD;
D 6
	if ( rbufp ) __free_ovflpage(rbufp);
	if ( last_bfp != rbufp ) __free_ovflpage(last_bfp);
E 6
I 6
	if (rbufp)
D 8
		__free_ovflpage(rbufp);
E 8
I 8
		__free_ovflpage(hashp, rbufp);
E 8
	if (last_bfp != rbufp)
D 8
		__free_ovflpage(last_bfp);
E 8
I 8
		__free_ovflpage(hashp, last_bfp);
E 8
E 6

	hashp->NKEYS--;
D 6
	return(0);
E 6
I 6
	return (0);
E 6
}
D 6

E 6
/*
D 6
    0 = key not found
    -1 = get next overflow page
    -2 means key not found and this is big key/data
    -3 error
*/
E 6
I 6
 * Returns:
 *  0 = key not found
 * -1 = get next overflow page
 * -2 means key not found and this is big key/data
 * -3 error
 */
E 6
extern int
D 6
__find_bigpair(bufp, ndx, key, size )
BUFHEAD	*bufp;
int	ndx;
char	*key;
int	size;
E 6
I 6
D 8
__find_bigpair(bufp, ndx, key, size)
E 8
I 8
__find_bigpair(hashp, bufp, ndx, key, size)
	HTAB *hashp;
E 8
	BUFHEAD *bufp;
	int ndx;
	char *key;
	int size;
E 6
{
D 6
    register	u_short	*bp = (u_short *)bufp->page;
    register	char	*p = bufp->page;
    int		ksize = size;
    char	*kkey = key;
    u_short	bytes;
E 6
I 6
	register u_short *bp;
	register char *p;
	int ksize;
	u_short bytes;
	char *kkey;
E 6

I 6
	bp = (u_short *)bufp->page;
	p = bufp->page;
	ksize = size;
	kkey = key;
E 6

D 6
    for ( bytes = hashp->BSIZE - bp[ndx]; 
	  bytes <= size && bp[ndx+1] == PARTIAL_KEY; 
	  bytes = hashp->BSIZE - bp[ndx] ) {

	if ( bcmp ( p+bp[ndx], kkey, bytes ))return(-2);
	kkey += bytes;
	ksize -= bytes;
	bufp = __get_buf ( bp[ndx+2], bufp, 0 );
	if ( !bufp ) {
	    return(-3);
E 6
I 6
	for (bytes = hashp->BSIZE - bp[ndx];
	    bytes <= size && bp[ndx + 1] == PARTIAL_KEY;
	    bytes = hashp->BSIZE - bp[ndx]) {
D 10
		if (bcmp(p + bp[ndx], kkey, bytes))
E 10
I 10
		if (memcmp(p + bp[ndx], kkey, bytes))
E 10
			return (-2);
		kkey += bytes;
		ksize -= bytes;
D 8
		bufp = __get_buf(bp[ndx + 2], bufp, 0);
E 8
I 8
		bufp = __get_buf(hashp, bp[ndx + 2], bufp, 0);
E 8
		if (!bufp)
			return (-3);
		p = bufp->page;
		bp = (u_short *)p;
		ndx = 1;
E 6
	}
D 6
	p = bufp->page;
	bp = (u_short *)p;
	ndx = 1;
    }
E 6

D 6
    if ( (bytes != ksize) || bcmp ( p+bp[ndx], kkey, bytes )) {
E 6
I 6
D 10
	if (bytes != ksize || bcmp(p + bp[ndx], kkey, bytes)) {
E 10
I 10
	if (bytes != ksize || memcmp(p + bp[ndx], kkey, bytes)) {
E 10
E 6
#ifdef HASH_STATISTICS
D 6
	hash_collisions++;
E 6
I 6
		++hash_collisions;
E 6
#endif
D 6
	return(-2);
    }
    else return (ndx);
E 6
I 6
		return (-2);
	} else
		return (ndx);
E 6
}

D 6

E 6
/*
D 6
    Given the buffer pointer of the first overflow page of a big pair, 
    find the end of the big pair

    This will set bpp to the buffer header of the last page of the big pair.  
    It will return the pageno of the overflow page following the last page of 
    the pair; 0 if there isn't any (i.e. big pair is the last key in the 
    bucket)
*/
E 6
I 6
 * Given the buffer pointer of the first overflow page of a big pair,
 * find the end of the big pair
 *
 * This will set bpp to the buffer header of the last page of the big pair.
 * It will return the pageno of the overflow page following the last page
 * of the pair; 0 if there isn't any (i.e. big pair is the last key in the
 * bucket)
 */
E 6
extern u_short
D 6
__find_last_page ( bpp )
BUFHEAD	**bpp;
E 6
I 6
D 8
__find_last_page(bpp)
E 8
I 8
__find_last_page(hashp, bpp)
	HTAB *hashp;
E 8
	BUFHEAD **bpp;
E 6
{
D 6
	int	n;
	u_short	pageno;
	BUFHEAD	*bufp = *bpp;
	u_short	*bp = (u_short *)bufp->page;
E 6
I 6
	BUFHEAD *bufp;
	u_short *bp, pageno;
	int n;
E 6

D 6
	while ( 1 ) {
	    n = bp[0];
E 6
I 6
	bufp = *bpp;
	bp = (u_short *)bufp->page;
	for (;;) {
		n = bp[0];
E 6

D 6
	    /*
		This is the last page if:
			the tag is FULL_KEY_DATA and either
				only 2 entries
				OVFLPAGE marker is explicit
				there is freespace on the page
	    */
	    if ( bp[2] == FULL_KEY_DATA &&
		 ((n == 2) ||  (bp[n] == OVFLPAGE) || (FREESPACE(bp)) ) ) break;
E 6
I 6
		/*
		 * This is the last page if: the tag is FULL_KEY_DATA and
		 * either only 2 entries OVFLPAGE marker is explicit there
		 * is freespace on the page.
		 */
		if (bp[2] == FULL_KEY_DATA &&
		    ((n == 2) || (bp[n] == OVFLPAGE) || (FREESPACE(bp))))
			break;
E 6

D 6
	    pageno = bp[n-1];
	    bufp = __get_buf ( pageno, bufp, 0 );
	    if ( !bufp ) return (0);		/* Need to indicate an error! */
	    bp = (u_short *)bufp->page;
E 6
I 6
		pageno = bp[n - 1];
D 8
		bufp = __get_buf(pageno, bufp, 0);
E 8
I 8
		bufp = __get_buf(hashp, pageno, bufp, 0);
E 8
		if (!bufp)
			return (0);	/* Need to indicate an error! */
		bp = (u_short *)bufp->page;
E 6
	}

	*bpp = bufp;
D 6
	if ( bp[0] > 2 ) return ( bp[3] );
	else return(0);
E 6
I 6
	if (bp[0] > 2)
		return (bp[3]);
	else
		return (0);
E 6
}

D 6

E 6
/*
D 6
    Return the data for the key/data pair
    that begins on this page at this index
    (index should always be 1)
*/
E 6
I 6
 * Return the data for the key/data pair that begins on this page at this
 * index (index should always be 1).
 */
E 6
extern int
D 6
__big_return ( bufp, ndx, val, set_current )
BUFHEAD	*bufp;
int	ndx;
DBT	*val;
int	set_current;
E 6
I 6
D 8
__big_return(bufp, ndx, val, set_current)
E 8
I 8
__big_return(hashp, bufp, ndx, val, set_current)
	HTAB *hashp;
E 8
	BUFHEAD *bufp;
	int ndx;
	DBT *val;
	int set_current;
E 6
{
D 6
    BUFHEAD	*save_p;
    u_short	save_addr;
    u_short	*bp = (u_short *)bufp->page;
    u_short	off, len;
    char	*cp, *tp;
E 6
I 6
	BUFHEAD *save_p;
	u_short *bp, len, off, save_addr;
	char *tp;
E 6

D 6
    while ( bp[ndx+1] == PARTIAL_KEY ) {
	bufp = __get_buf ( bp[bp[0]-1], bufp, 0 );
	if ( !bufp ) return(-1);
E 6
	bp = (u_short *)bufp->page;
D 6
	ndx = 1;
    }
E 6
I 6
	while (bp[ndx + 1] == PARTIAL_KEY) {
D 8
		bufp = __get_buf(bp[bp[0] - 1], bufp, 0);
E 8
I 8
		bufp = __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
E 8
		if (!bufp)
			return (-1);
		bp = (u_short *)bufp->page;
		ndx = 1;
	}
E 6

D 6
    if ( bp[ndx+1] == FULL_KEY ) {
	bufp = __get_buf ( bp[bp[0]-1], bufp, 0 );
	if ( !bufp ) return(-1);
	bp = (u_short *)bufp->page;
	save_p = bufp;
	save_addr = save_p->addr;
	off = bp[1];
	len = 0;
    } else if (!FREESPACE(bp)) {
	/*
	    This is a hack.  We can't distinguish between
	    FULL_KEY_DATA that contains complete data or
	    incomplete data, so we require that if the
	    data  is complete, there is at least 1 byte
	    of free space left.
	*/
	off = bp[bp[0]];
	len = bp[1] - off;
	save_p = bufp;
	save_addr = bufp->addr;
	bufp = __get_buf ( bp[bp[0]-1], bufp, 0 );
	if ( !bufp ) return(-1);
	bp = (u_short *)bufp->page;
    } else {
	/* The data is all on one page */
	tp = (char *)bp;
	off = bp[bp[0]];
D 4
	val->data = tp + off;
E 4
I 4
	val->data = (u_char *)tp + off;
E 4
	val->size = bp[1] - off;
	if ( set_current ) {
	    if ( bp[0] == 2 ) {		/* No more buckets in chain */
		hashp->cpage = NULL;
		hashp->cbucket++;
		hashp->cndx=1;
	    } else  {
		hashp->cpage = __get_buf ( bp[bp[0]-1], bufp, 0 );
		if ( !hashp->cpage )return(-1);
		hashp->cndx = 1;
		if ( !((u_short *)hashp->cpage->page)[0] ) {
		    hashp->cbucket++;
		    hashp->cpage = NULL;
E 6
I 6
	if (bp[ndx + 1] == FULL_KEY) {
D 8
		bufp = __get_buf(bp[bp[0] - 1], bufp, 0);
E 8
I 8
		bufp = __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
E 8
		if (!bufp)
			return (-1);
		bp = (u_short *)bufp->page;
		save_p = bufp;
		save_addr = save_p->addr;
		off = bp[1];
		len = 0;
	} else
		if (!FREESPACE(bp)) {
			/*
			 * This is a hack.  We can't distinguish between
			 * FULL_KEY_DATA that contains complete data or
			 * incomplete data, so we require that if the data
			 * is complete, there is at least 1 byte of free
			 * space left.
			 */
			off = bp[bp[0]];
			len = bp[1] - off;
			save_p = bufp;
			save_addr = bufp->addr;
D 8
			bufp = __get_buf(bp[bp[0] - 1], bufp, 0);
E 8
I 8
			bufp = __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
E 8
			if (!bufp)
				return (-1);
			bp = (u_short *)bufp->page;
		} else {
			/* The data is all on one page. */
			tp = (char *)bp;
			off = bp[bp[0]];
			val->data = (u_char *)tp + off;
			val->size = bp[1] - off;
			if (set_current) {
				if (bp[0] == 2) {	/* No more buckets in
							 * chain */
					hashp->cpage = NULL;
					hashp->cbucket++;
					hashp->cndx = 1;
				} else {
D 8
					hashp->cpage =
					    __get_buf(bp[bp[0] - 1], bufp, 0);
E 8
I 8
					hashp->cpage = __get_buf(hashp,
					    bp[bp[0] - 1], bufp, 0);
E 8
					if (!hashp->cpage)
						return (-1);
					hashp->cndx = 1;
					if (!((u_short *)
					    hashp->cpage->page)[0]) {
						hashp->cbucket++;
						hashp->cpage = NULL;
					}
				}
			}
			return (0);
E 6
		}
D 6
	    }
E 6
I 6

D 7
	val->size = collect_data(bufp, len, set_current);
E 7
I 7
D 8
	val->size = collect_data(bufp, (int)len, set_current);
E 8
I 8
	val->size = collect_data(hashp, bufp, (int)len, set_current);
E 8
E 7
	if (val->size == -1)
		return (-1);
	if (save_p->addr != save_addr) {
		/* We are pretty short on buffers. */
		errno = EINVAL;			/* OUT OF BUFFERS */
		return (-1);
E 6
	}
D 6
	return(0);
    }
    
    val->size = collect_data ( bufp, len, set_current );
    if ( val->size == -1 ) {
	return(-1);
    }
    if ( save_p->addr != save_addr ) {
	/* We are pretty short on buffers */
	errno = EINVAL;		/* OUT OF BUFFERS */
	return(-1);
    }
    bcopy ( (save_p->page)+off, hashp->tmp_buf, len );
D 4
    val->data = hashp->tmp_buf;
E 4
I 4
    val->data = (u_char *)hashp->tmp_buf;
E 4
    return(0);
E 6
I 6
D 10
	bcopy((save_p->page) + off, hashp->tmp_buf, len);
E 10
I 10
	memmove(hashp->tmp_buf, (save_p->page) + off, len);
E 10
	val->data = (u_char *)hashp->tmp_buf;
	return (0);
E 6
}
D 6

E 6
/*
D 6
    Count how big the total datasize is by
    recursing through the pages.  Then allocate
    a buffer and copy the data as you recurse up.
*/
E 6
I 6
 * Count how big the total datasize is by recursing through the pages.  Then
 * allocate a buffer and copy the data as you recurse up.
 */
E 6
static int
D 6
collect_data ( bufp, len, set )
BUFHEAD	*bufp;
int	len;
int	set;
E 6
I 6
D 8
collect_data(bufp, len, set)
E 8
I 8
collect_data(hashp, bufp, len, set)
	HTAB *hashp;
E 8
	BUFHEAD *bufp;
	int len, set;
E 6
{
D 6
    register	char	*p = bufp->page;
    register	u_short	*bp = (u_short *)p;
    u_short	save_addr;
    int	mylen, totlen;
    BUFHEAD	*xbp;
E 6
I 6
	register u_short *bp;
	register char *p;
	BUFHEAD *xbp;
	u_short save_addr;
	int mylen, totlen;
E 6

D 6
    mylen = hashp->BSIZE - bp[1];
    save_addr = bufp->addr;
E 6
I 6
	p = bufp->page;
	bp = (u_short *)p;
	mylen = hashp->BSIZE - bp[1];
	save_addr = bufp->addr;
E 6

D 6
    if ( bp[2] == FULL_KEY_DATA ) {	/* End of Data */
	totlen = len + mylen;
	if ( hashp->tmp_buf ) free (hashp->tmp_buf);
	hashp->tmp_buf = (char *)malloc ( totlen );
	if ( !hashp->tmp_buf ) {
	    return(-1);
	}
	if ( set ) {
	    hashp->cndx = 1;
	    if ( bp[0] == 2 ) {		/* No more buckets in chain */
		hashp->cpage = NULL;
		hashp->cbucket++;
	    } else  {
		hashp->cpage = __get_buf ( bp[bp[0]-1], bufp, 0 );
		if (!hashp->cpage) {
		    return(-1);
		} else if ( !((u_short *)hashp->cpage->page)[0] ) {
		    hashp->cbucket++;
		    hashp->cpage = NULL;
E 6
I 6
	if (bp[2] == FULL_KEY_DATA) {		/* End of Data */
		totlen = len + mylen;
		if (hashp->tmp_buf)
			free(hashp->tmp_buf);
D 12
		hashp->tmp_buf = malloc(totlen);
		if (!hashp->tmp_buf)
E 12
I 12
		if ((hashp->tmp_buf = (char *)malloc(totlen)) == NULL)
E 12
			return (-1);
		if (set) {
			hashp->cndx = 1;
			if (bp[0] == 2) {	/* No more buckets in chain */
				hashp->cpage = NULL;
				hashp->cbucket++;
			} else {
				hashp->cpage =
D 8
				    __get_buf(bp[bp[0] - 1], bufp, 0);
E 8
I 8
				    __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
E 8
				if (!hashp->cpage)
					return (-1);
				else if (!((u_short *)hashp->cpage->page)[0]) {
					hashp->cbucket++;
					hashp->cpage = NULL;
				}
			}
E 6
		}
D 6
	    }
E 6
I 6
	} else {
D 8
		xbp = __get_buf(bp[bp[0] - 1], bufp, 0);
		if (!xbp ||
		    ((totlen = collect_data(xbp, len + mylen, set)) < 1))
E 8
I 8
		xbp = __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
		if (!xbp || ((totlen =
		    collect_data(hashp, xbp, len + mylen, set)) < 1))
E 8
			return (-1);
E 6
	}
D 6
    } else {
	xbp = __get_buf ( bp[bp[0]-1], bufp, 0 );
	if ( !xbp || ((totlen = collect_data ( xbp, len + mylen, set )) < 1) ) {
	    return(-1);
E 6
I 6
	if (bufp->addr != save_addr) {
		errno = EINVAL;			/* Out of buffers. */
		return (-1);
E 6
	}
D 6
    }
    if ( bufp->addr != save_addr ) {
	errno = EINVAL;		/* Out of buffers */
	return(-1);
    }
    bcopy ( (bufp->page) + bp[1], &hashp->tmp_buf[len], mylen );
    return ( totlen );
E 6
I 6
D 10
	bcopy((bufp->page) + bp[1], &hashp->tmp_buf[len], mylen);
E 10
I 10
	memmove(&hashp->tmp_buf[len], (bufp->page) + bp[1], mylen);
E 10
	return (totlen);
E 6
}

/*
D 6
	Fill in the key and data
	for this big pair 
*/
E 6
I 6
 * Fill in the key and data for this big pair.
 */
E 6
extern int
D 6
__big_keydata ( bufp, ndx, key, val, set )
BUFHEAD	*bufp;
int	ndx;
DBT	*key, *val;
int	set;
E 6
I 6
D 7
__big_keydata(bufp, ndx, key, val, set)
E 7
I 7
D 8
__big_keydata(bufp, key, val, set)
E 8
I 8
__big_keydata(hashp, bufp, key, val, set)
	HTAB *hashp;
E 8
E 7
	BUFHEAD *bufp;
D 7
	int ndx;
E 7
	DBT *key, *val;
	int set;
E 6
{
D 6
    key->size = collect_key ( bufp, 0, val, set );
    if ( key->size == -1 ) {
	return (-1);
    }
D 4
    key->data = hashp->tmp_key;
E 4
I 4
    key->data = (u_char *)hashp->tmp_key;
E 4
    return(0);
E 6
I 6
D 8
	key->size = collect_key(bufp, 0, val, set);
E 8
I 8
	key->size = collect_key(hashp, bufp, 0, val, set);
E 8
	if (key->size == -1)
		return (-1);
	key->data = (u_char *)hashp->tmp_key;
	return (0);
E 6
}

/*
D 6
    Count how big the total key size is by
    recursing through the pages.  Then collect
    the data, allocate a buffer and copy the key as
    you recurse up.
*/
E 6
I 6
 * Count how big the total key size is by recursing through the pages.  Then
 * collect the data, allocate a buffer and copy the key as you recurse up.
 */
E 6
static int
D 6
collect_key ( bufp, len, val, set )
BUFHEAD	*bufp;
int	len;
DBT	*val;
int	set;
E 6
I 6
D 8
collect_key(bufp, len, val, set)
E 8
I 8
collect_key(hashp, bufp, len, val, set)
	HTAB *hashp;
E 8
	BUFHEAD *bufp;
	int len;
	DBT *val;
	int set;
E 6
{
D 6
    char	*p = bufp->page;
    u_short	*bp = (u_short *)p;
    u_short	save_addr;
    int	mylen, totlen;
    BUFHEAD	*xbp;
E 6
I 6
	BUFHEAD *xbp;
	char *p;
	int mylen, totlen;
	u_short *bp, save_addr;
E 6

D 6
    mylen = hashp->BSIZE - bp[1];
E 6
I 6
	p = bufp->page;
	bp = (u_short *)p;
	mylen = hashp->BSIZE - bp[1];
E 6

D 6
    save_addr = bufp->addr;
    totlen = len + mylen;
    if ( bp[2] == FULL_KEY || bp[2] == FULL_KEY_DATA ) {/* End of Key */
	if ( hashp->tmp_key ) free (hashp->tmp_key);
	hashp->tmp_key = (char *)malloc ( totlen );
	if ( !hashp->tmp_key ) {
	    return(-1);
E 6
I 6
	save_addr = bufp->addr;
	totlen = len + mylen;
	if (bp[2] == FULL_KEY || bp[2] == FULL_KEY_DATA) {    /* End of Key. */
D 12
		if (hashp->tmp_key)
E 12
I 12
		if (hashp->tmp_key != NULL)
E 12
			free(hashp->tmp_key);
D 12
		hashp->tmp_key = malloc(totlen);
		if (!hashp->tmp_key)
E 12
I 12
		if ((hashp->tmp_key = (char *)malloc(totlen)) == NULL)
E 12
			return (-1);
D 7
		__big_return(bufp, 1, val, set);
E 7
I 7
D 8
		if (__big_return(bufp, 1, val, set))
E 8
I 8
		if (__big_return(hashp, bufp, 1, val, set))
E 8
			return (-1);
E 7
	} else {
D 8
		xbp = __get_buf(bp[bp[0] - 1], bufp, 0);
		if (!xbp ||
		    ((totlen = collect_key(xbp, totlen, val, set)) < 1))
E 8
I 8
		xbp = __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
		if (!xbp || ((totlen =
		    collect_key(hashp, xbp, totlen, val, set)) < 1))
E 8
			return (-1);
E 6
	}
D 6
	__big_return ( bufp, 1, val, set );
    } else {
	xbp = __get_buf (bp[bp[0]-1], bufp, 0);
	if ( !xbp || ((totlen = collect_key (xbp, totlen, val, set)) < 1 ) ) {
	    return(-1);
E 6
I 6
	if (bufp->addr != save_addr) {
		errno = EINVAL;		/* MIS -- OUT OF BUFFERS */
		return (-1);
E 6
	}
D 6
    }
    if ( bufp->addr != save_addr ) {
	errno = EINVAL;		/* MIS -- OUT OF BUFFERS */
	return (-1);
    }
    bcopy ( (bufp->page) + bp[1], &hashp->tmp_key[len], mylen );
    return ( totlen );
E 6
I 6
D 10
	bcopy((bufp->page) + bp[1], &hashp->tmp_key[len], mylen);
E 10
I 10
	memmove(&hashp->tmp_key[len], (bufp->page) + bp[1], mylen);
E 10
	return (totlen);
E 6
}

D 6

E 6
/*
D 6
    return 0 => OK
	   -1 => error
*/
E 6
I 6
 * Returns:
 *  0 => OK
 * -1 => error
 */
E 6
extern int
D 6
__big_split ( op, np, big_keyp, addr, obucket, ret )
BUFHEAD	*op;		/* Pointer to where to put keys that go in old bucket */
BUFHEAD	*np;		/* Pointer to new bucket page */
BUFHEAD	*big_keyp;	/* Pointer to first page containing the big key/data */
u_short	addr;		/* Address of big_keyp */
D 5
int	obucket;	/* Old Bucket */
E 5
I 5
u_int	obucket;	/* Old Bucket */
E 5
SPLIT_RETURN	*ret;
E 6
I 6
D 8
__big_split(op, np, big_keyp, addr, obucket, ret)
E 8
I 8
__big_split(hashp, op, np, big_keyp, addr, obucket, ret)
	HTAB *hashp;
E 8
	BUFHEAD *op;	/* Pointer to where to put keys that go in old bucket */
	BUFHEAD *np;	/* Pointer to new bucket page */
			/* Pointer to first page containing the big key/data */
	BUFHEAD *big_keyp;
	int addr;	/* Address of big_keyp */
	u_int   obucket;/* Old Bucket */
	SPLIT_RETURN *ret;
E 6
{
D 6
    register	u_short	*prev_pagep;
    register	BUFHEAD	*tmpp;
    register	u_short 	*tp;
    BUFHEAD	*bp = big_keyp;
    u_short	off, free_space;
    u_short	n;
E 6
I 6
	register BUFHEAD *tmpp;
	register u_short *tp;
	BUFHEAD *bp;
	DBT key, val;
	u_int change;
	u_short free_space, n, off;
E 6

D 6
    DBT		key, val;
E 6
I 6
	bp = big_keyp;
E 6

D 5
    int		change;
E 5
I 5
D 6
    u_int	change;
E 6
I 6
	/* Now figure out where the big key/data goes */
D 7
	if (__big_keydata(big_keyp, 1, &key, &val, 0))
E 7
I 7
D 8
	if (__big_keydata(big_keyp, &key, &val, 0))
E 8
I 8
	if (__big_keydata(hashp, big_keyp, &key, &val, 0))
E 8
E 7
		return (-1);
D 8
	change = (__call_hash(key.data, key.size) != obucket);
E 8
I 8
	change = (__call_hash(hashp, key.data, key.size) != obucket);
E 8
E 6
E 5

D 6
    /* Now figure out where the big key/data goes */
    if (__big_keydata ( big_keyp, 1, &key, &val, 0 )) {
	return(-1);
    }
    change = (__call_hash ( key.data, key.size ) != obucket );
E 6
I 6
D 8
	if (ret->next_addr = __find_last_page(&big_keyp)) {
		if (!(ret->nextp = __get_buf(ret->next_addr, big_keyp, 0)))
E 8
I 8
	if (ret->next_addr = __find_last_page(hashp, &big_keyp)) {
		if (!(ret->nextp =
		    __get_buf(hashp, ret->next_addr, big_keyp, 0)))
E 8
			return (-1);;
	} else
		ret->nextp = NULL;
E 6

D 6
    if ( ret->next_addr = __find_last_page ( &big_keyp ) ) {
	if (!(ret->nextp = __get_buf ( ret->next_addr, big_keyp, 0 ))) {
	    return(-1);;
	}
    } else {
	ret->nextp = NULL;
    }
E 6
I 6
	/* Now make one of np/op point to the big key/data pair */
#ifdef DEBUG
	assert(np->ovfl == NULL);
#endif
	if (change)
		tmpp = np;
	else
		tmpp = op;
E 6

D 6
    /* Now make one of np/op point to the big key/data pair */
    assert(np->ovfl == NULL);
    if ( change ) tmpp = np;
    else tmpp = op;

    tmpp->flags |= BUF_MOD;
E 6
I 6
	tmpp->flags |= BUF_MOD;
E 6
#ifdef DEBUG1
D 6
    fprintf ( stderr, "BIG_SPLIT: %d->ovfl was %d is now %d\n", tmpp->addr,
		(tmpp->ovfl?tmpp->ovfl->addr:0), 
		(bp?bp->addr:0) );
E 6
I 6
	(void)fprintf(stderr,
	    "BIG_SPLIT: %d->ovfl was %d is now %d\n", tmpp->addr,
	    (tmpp->ovfl ? tmpp->ovfl->addr : 0), (bp ? bp->addr : 0));
E 6
#endif
D 6
    tmpp->ovfl = bp;		/* one of op/np point to big_keyp */
    tp = (u_short *)tmpp->page;
    assert ( FREESPACE(tp) >= OVFLSIZE);
    n = tp[0];
    off = OFFSET(tp);
    free_space = FREESPACE(tp);
    tp[++n] = addr;
    tp[++n] = OVFLPAGE;
    tp[0] = n;
    OFFSET(tp) = off;
    FREESPACE(tp) = free_space - OVFLSIZE;

    /* 
	Finally, set the new and old return values.
	BIG_KEYP contains a pointer to the last page of the big key_data pair.
	Make sure that big_keyp has no following page (2 elements) or create
	an empty following page.
    */

    ret->newp = np;
    ret->oldp = op;

    tp = (u_short *)big_keyp->page;
    big_keyp->flags |= BUF_MOD;
    if ( tp[0] > 2 ) {
	/* 
	    There may be either one or two offsets on this page 
	    If there is one, then the overflow page is linked on
	    normally and tp[4] is OVFLPAGE.  If there are two, tp[4]
	    contains the second offset and needs to get stuffed in
	    after the next overflow page is added
	*/
	n = tp[4];		
	free_space = FREESPACE(tp);
E 6
I 6
	tmpp->ovfl = bp;	/* one of op/np point to big_keyp */
	tp = (u_short *)tmpp->page;
#ifdef DEBUG
	assert(FREESPACE(tp) >= OVFLSIZE);
#endif
	n = tp[0];
E 6
	off = OFFSET(tp);
D 6
	tp[0] -= 2;
	FREESPACE(tp) = free_space + OVFLSIZE;
E 6
I 6
	free_space = FREESPACE(tp);
	tp[++n] = (u_short)addr;
	tp[++n] = OVFLPAGE;
	tp[0] = n;
E 6
	OFFSET(tp) = off;
D 6
	tmpp = __add_ovflpage ( big_keyp );
	if ( !tmpp ) {
	    return(-1);
	}
	tp[4] = n;
    } else {
	tmpp = big_keyp;
    }
E 6
I 6
	FREESPACE(tp) = free_space - OVFLSIZE;
E 6

D 6
    if ( change ) ret->newp = tmpp;
    else ret->oldp = tmpp;
E 6
I 6
	/*
	 * Finally, set the new and old return values. BIG_KEYP contains a
	 * pointer to the last page of the big key_data pair. Make sure that
	 * big_keyp has no following page (2 elements) or create an empty
	 * following page.
	 */
E 6

D 6
    return(0);
E 6
I 6
	ret->newp = np;
	ret->oldp = op;

	tp = (u_short *)big_keyp->page;
	big_keyp->flags |= BUF_MOD;
	if (tp[0] > 2) {
		/*
		 * There may be either one or two offsets on this page.  If
		 * there is one, then the overflow page is linked on normally
		 * and tp[4] is OVFLPAGE.  If there are two, tp[4] contains
		 * the second offset and needs to get stuffed in after the
		 * next overflow page is added.
		 */
		n = tp[4];
		free_space = FREESPACE(tp);
		off = OFFSET(tp);
		tp[0] -= 2;
		FREESPACE(tp) = free_space + OVFLSIZE;
		OFFSET(tp) = off;
D 8
		tmpp = __add_ovflpage(big_keyp);
E 8
I 8
		tmpp = __add_ovflpage(hashp, big_keyp);
E 8
		if (!tmpp)
			return (-1);
		tp[4] = n;
	} else
		tmpp = big_keyp;

	if (change)
		ret->newp = tmpp;
	else
		ret->oldp = tmpp;
	return (0);
E 6
}
E 1
