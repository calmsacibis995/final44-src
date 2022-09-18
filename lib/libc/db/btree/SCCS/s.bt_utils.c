h24831
s 00004/00002/00217
d D 8.4 94/02/21 17:43:22 bostic 15 14
c cast alloc's to shut SunOS up
e
s 00012/00007/00207
d D 8.3 94/02/21 15:08:18 bostic 14 13
c first pass at making DB use basic integral types (the Alpha port)
e
s 00017/00004/00197
d D 8.2 93/09/07 11:51:11 bostic 13 12
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00199
d D 8.1 93/06/04 15:21:07 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00197
d D 5.11 93/05/01 15:28:33 bostic 11 10
c KNF
e
s 00002/00002/00199
d D 5.10 93/02/16 12:33:49 bostic 10 9
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00001/00001/00200
d D 5.9 93/02/11 11:39:31 bostic 9 8
c move db.h to the end of the includes, make compat.h work better
e
s 00002/00002/00199
d D 5.8 92/12/04 14:18:49 bostic 8 7
c copy the length of the data, not the length of the buffer
e
s 00002/00000/00199
d D 5.7 92/11/13 16:05:51 bostic 7 6
c prettiness police
e
s 00004/00003/00195
d D 5.6 92/11/10 10:35:33 bostic 6 5
c increment necessary dsize by 1 so that we don't crash if the first
c record retrieved is 0 length.
e
s 00025/00022/00173
d D 5.5 91/09/12 11:44:27 bostic 5 4
c don't necessarily modify key in key/data return; don't automatically
c assign on realloc so that recovery is possible; fix default prefix routine
e
s 00124/00253/00071
d D 5.4 91/09/04 12:47:28 bostic 4 3
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00004/00004/00320
d D 5.3 91/03/03 14:33:21 bostic 3 2
c DBT data changed to be unsigned
e
s 00002/00000/00322
d D 5.2 91/02/22 17:16:45 bostic 2 1
c ANSI prototypes
e
s 00322/00000/00000
d D 5.1 91/01/23 08:12:51 mao 1 0
c date and time created 91/01/23 08:12:51 by mao
e
u
U
t
T
I 1
/*-
D 12
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 4
#include <sys/types.h>
E 4
I 4
#include <sys/param.h>
I 7

E 7
E 4
D 9
#include <db.h>
E 9
I 4
#include <stdio.h>
E 4
I 2
#include <stdlib.h>
#include <string.h>
I 7

I 9
#include <db.h>
E 9
E 7
E 2
#include "btree.h"

/*
D 4
 *  _BT_BUILDRET -- Build return key/data pair as a result of search or scan.
E 4
I 4
 * __BT_RET -- Build return key/data pair as a result of search or scan.
E 4
 *
D 4
 *	This routine manages the statically allocated buffers in which we
 *	return data to the user.
E 4
I 4
 * Parameters:
 *	t:	tree
 *	d:	LEAF to be returned to the user.
D 5
 *	key:	user's key structure
E 5
I 5
 *	key:	user's key structure (NULL if not to be filled in)
E 5
 *	data:	user's data structure
E 4
 *
D 4
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
E 4
I 4
 * Returns:
 *	RET_SUCCESS, RET_ERROR.
E 4
 */
D 4

E 4
int
D 4
_bt_buildret(t, d, data, key)
	BTREE_P t;
	DATUM *d;
	DBT *data;
	DBT *key;
E 4
I 4
__bt_ret(t, e, key, data)
	BTREE *t;
	EPG *e;
	DBT *key, *data;
E 4
{
D 4
	static int _data_s = 0;
	static int _key_s = 0;
	static char *_data = (char *) NULL;
	static char *_key = (char *) NULL;
	pgno_t chain;
E 4
I 4
	register BLEAF *bl;
I 5
	register void *p;
E 5
E 4

D 4
	if (d->d_flags & D_BIGKEY) {
		if (_key != (char *) NULL)
			(void) free(_key);
		(void) bcopy((char *) &(d->d_bytes[0]),
		      	     (char *) &chain,
		      	     sizeof(chain));
		if (_bt_getbig(t, chain, &_key, &_key_s) == RET_ERROR)
E 4
I 4
	bl = GETBLEAF(e->page, e->index);

I 13
	/*
	 * We always copy big keys/data to make them contigous.  Otherwise,
	 * we leave the page pinned and don't copy unless the user specified
	 * concurrent access.
	 */
E 13
D 5
	if (bl->flags & P_BIGKEY) {
		if (__ovfl_get(t, bl->bytes,
		    &key->size, &t->bt_kbuf, &t->bt_kbufsz))
E 4
			return (RET_ERROR);
D 3
		key->data = _key;
E 3
I 3
D 4
		key->data = (u_char *)_key;
E 3
		key->size = _key_s;
E 4
	} else {
D 4
		/* need more space for key? */
		if (d->d_ksize > _key_s) {
			if (_key != (char *) NULL)
				(void) free (_key);
			if ((_key = (char *) malloc((unsigned) d->d_ksize))
			    == (char *) NULL)
E 4
I 4
		if (bl->ksize > t->bt_kbufsz) {
			if ((t->bt_kbuf =
			    realloc(t->bt_kbuf, bl->ksize)) == NULL)
E 4
				return (RET_ERROR);
D 4
			_key_s = d->d_ksize;
E 4
I 4
			t->bt_kbufsz = bl->ksize;
E 4
		}
D 4

D 3
		key->data = _key;
E 3
I 3
		key->data = (u_char *)_key;
E 3
		if ((key->size = d->d_ksize) > 0)
			(void) bcopy(&(d->d_bytes[0]),
				     _key,
				     (int) d->d_ksize);
E 4
I 4
		bcopy(bl->bytes, t->bt_kbuf, t->bt_kbufsz);
		key->size = bl->ksize;
E 4
	}
I 4
	key->data = t->bt_kbuf;
E 4

E 5
D 4
	if (d->d_flags & D_BIGDATA) {
		if (_data != (char *) NULL)
			(void) free(_data);
		(void) bcopy(&(d->d_bytes[d->d_ksize]),
		      	     (char *) &chain,
		      	     sizeof(chain));
		if (_bt_getbig(t, chain, &_data, &_data_s) == RET_ERROR)
E 4
I 4
	if (bl->flags & P_BIGDATA) {
		if (__ovfl_get(t, bl->bytes + bl->ksize,
		    &data->size, &t->bt_dbuf, &t->bt_dbufsz))
E 4
			return (RET_ERROR);
D 3
		data->data = _data;
E 3
I 3
D 4
		data->data = (u_char *)_data;
E 3
		data->size = _data_s;
E 4
D 13
	} else {
E 13
I 13
		data->data = t->bt_dbuf;
	} else if (ISSET(t, B_DB_LOCK)) {
E 13
D 4
		/* need more space for data? */
		if (d->d_dsize > _data_s) {
			if (_data != (char *) NULL)
				(void) free (_data);
			if ((_data = (char *) malloc((unsigned) d->d_dsize))
			    == (char *) NULL)
E 4
I 4
D 6
		if (bl->dsize > t->bt_dbufsz) {
D 5
			if ((t->bt_dbuf =
			    realloc(t->bt_dbuf, bl->dsize)) == NULL)
E 5
I 5
			if ((p = realloc(t->bt_dbuf, bl->dsize)) == NULL)
E 6
I 6
		/* Use +1 in case the first record retrieved is 0 length. */
		if (bl->dsize + 1 > t->bt_dbufsz) {
D 15
			if ((p = realloc(t->bt_dbuf, bl->dsize + 1)) == NULL)
E 15
I 15
			if ((p =
			    (void *)realloc(t->bt_dbuf, bl->dsize + 1)) == NULL)
E 15
E 6
E 5
E 4
				return (RET_ERROR);
I 5
			t->bt_dbuf = p;
E 5
D 4
			_data_s = d->d_dsize;
E 4
I 4
D 6
			t->bt_dbufsz = bl->dsize;
E 6
I 6
			t->bt_dbufsz = bl->dsize + 1;
E 6
E 4
		}
D 4

D 3
		data->data = _data;
E 3
I 3
		data->data = (u_char *)_data;
E 3

		if ((data->size = d->d_dsize) > 0)
			(void) bcopy(&(d->d_bytes[d->d_ksize]),
				      _data,
				      (size_t) (d->d_dsize));
E 4
I 4
D 8
		bcopy(bl->bytes + bl->ksize, t->bt_dbuf, t->bt_dbufsz);
E 8
I 8
D 10
		bcopy(bl->bytes + bl->ksize, t->bt_dbuf, bl->dsize);
E 10
I 10
		memmove(t->bt_dbuf, bl->bytes + bl->ksize, bl->dsize);
E 10
E 8
		data->size = bl->dsize;
I 13
		data->data = t->bt_dbuf;
	} else {
		data->size = bl->dsize;
		data->data = bl->bytes + bl->ksize;
E 13
E 4
	}
I 4
D 13
	data->data = t->bt_dbuf;
E 13
E 4

I 5
	if (key == NULL)
		return (RET_SUCCESS);

	if (bl->flags & P_BIGKEY) {
		if (__ovfl_get(t, bl->bytes,
		    &key->size, &t->bt_kbuf, &t->bt_kbufsz))
			return (RET_ERROR);
D 13
	} else {
E 13
I 13
		key->data = t->bt_kbuf;
	} else if (ISSET(t, B_DB_LOCK)) {
E 13
		if (bl->ksize > t->bt_kbufsz) {
D 15
			if ((p = realloc(t->bt_kbuf, bl->ksize)) == NULL)
E 15
I 15
			if ((p =
			    (void *)realloc(t->bt_kbuf, bl->ksize)) == NULL)
E 15
				return (RET_ERROR);
			t->bt_kbuf = p;
			t->bt_kbufsz = bl->ksize;
		}
D 8
		bcopy(bl->bytes, t->bt_kbuf, t->bt_kbufsz);
E 8
I 8
D 10
		bcopy(bl->bytes, t->bt_kbuf, bl->ksize);
E 10
I 10
		memmove(t->bt_kbuf, bl->bytes, bl->ksize);
E 10
E 8
		key->size = bl->ksize;
I 13
		key->data = t->bt_kbuf;
	} else {
		key->size = bl->ksize;
		key->data = bl->bytes;
E 13
	}
D 13
	key->data = t->bt_kbuf;
E 13
E 5
	return (RET_SUCCESS);
}

/*
D 4
 *  _BT_CMP -- Compare a key to a given item on the current page.
E 4
I 4
 * __BT_CMP -- Compare a key to a given record.
E 4
 *
D 4
 *	This routine is a wrapper for the user's comparison function.
E 4
I 4
 * Parameters:
 *	t:	tree
 *	k1:	DBT pointer of first arg to comparison
 *	e:	pointer to EPG for comparison
E 4
 *
D 4
 *	Parameters:
 *		t -- tree in which to do comparison
 *		p -- pointer to one argument for the comparison function
 *		n -- index of item to supply second arg to comparison function
 *
 *	Returns:
 *		< 0 if p is < item at n
 *		= 0 if p is = item at n
 *		> 0 if p is > item at n
E 4
I 4
 * Returns:
 *	< 0 if k1 is < record
 *	= 0 if k1 is = record
 *	> 0 if k1 is > record
E 4
 */
D 4

E 4
int
D 4
_bt_cmp(t, p, n)
	BTREE_P t;
	char *p;
	index_t n;
E 4
I 4
__bt_cmp(t, k1, e)
	BTREE *t;
	const DBT *k1;
	EPG *e;
E 4
{
D 4
	BTHEADER *h;
	IDATUM *id;
	DATUM *d;
	char *arg;
	int ignore;
	int free_arg;
	pgno_t chain;
	int r;
E 4
I 4
	BINTERNAL *bi;
	BLEAF *bl;
	DBT k2;
	PAGE *h;
	void *bigkey;
E 4

D 4
	h = t->bt_curpage;

E 4
	/*
D 4
	 *  The left-most key at any level of the tree on internal pages
	 *  is guaranteed (artificially, by the code here) to be less than
	 *  any user key.  This saves us from having to update the leftmost
	 *  key when the user inserts a new key in the tree smaller than
	 *  anything we've seen yet.
E 4
I 4
	 * The left-most key on internal pages, at any level of the tree, is
	 * guaranteed by the following code to be less than any user key.
	 * This saves us from having to update the leftmost key on an internal
	 * page when the user inserts a new key in the tree smaller than
	 * anything we've yet seen.
E 4
	 */
D 4

	if (h->h_prevpg == P_NONE && !(h->h_flags & F_LEAF) && n == 0)
E 4
I 4
	h = e->page;
	if (e->index == 0 && h->prevpg == P_INVALID && !(h->flags & P_BLEAF))
E 4
		return (1);

D 4
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
E 4
I 4
	bigkey = NULL;
	if (h->flags & P_BLEAF) {
		bl = GETBLEAF(h, e->index);
		if (bl->flags & P_BIGKEY)
			bigkey = bl->bytes;
		else {
			k2.data = bl->bytes;
			k2.size = bl->ksize;
E 4
		}
	} else {
D 4
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
E 4
I 4
		bi = GETBINTERNAL(h, e->index);
		if (bi->flags & P_BIGKEY)
			bigkey = bi->bytes;
		else {
			k2.data = bi->bytes;
			k2.size = bi->ksize;
E 4
		}
	}
D 4
	r = (*(t->bt_compare))(p, arg);
E 4

D 4
	if (free_arg)
		(void) free(arg);

	return (r);
E 4
I 4
	if (bigkey) {
		if (__ovfl_get(t, bigkey,
		    &k2.size, &t->bt_dbuf, &t->bt_dbufsz))
			return (RET_ERROR);
		k2.data = t->bt_dbuf;
	}
D 11
	return((*t->bt_cmp)(k1, &k2));
E 11
I 11
	return ((*t->bt_cmp)(k1, &k2));
E 11
E 4
}

/*
D 4
 *  _BT_PUSH/_BT_POP -- Push/pop a parent page number on the parent stack.
E 4
I 4
 * __BT_DEFCMP -- Default comparison routine.
E 4
 *
D 4
 *	When we descend the tree, we keep track of parent pages in order
 *	to handle splits on insertions.
E 4
I 4
 * Parameters:
 *	a:	DBT #1
 *	b: 	DBT #2
E 4
 *
D 4
 *	Parameters:
 *		t -- tree for which to push parent
 *		pgno -- page number to push (_bt_push only)
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
E 4
I 4
 * Returns:
 *	< 0 if a is < b
 *	= 0 if a is = b
 *	> 0 if a is > b
E 4
 */
D 4

E 4
int
D 4
_bt_push(t, pgno)
	BTREE_P t;
	pgno_t pgno;
E 4
I 4
__bt_defcmp(a, b)
	const DBT *a, *b;
E 4
{
I 14
	register size_t len;
E 14
D 4
	BTSTACK *new;
E 4
I 4
	register u_char *p1, *p2;
D 14
	register int diff, len;
E 14
E 4

I 14
	/*
	 * XXX
	 * If a size_t doesn't fit in an int, this routine can lose.
	 * What we need is a integral type which is guaranteed to be
	 * larger than a size_t, and there is no such thing.
	 */
E 14
D 4
	if ((new = (BTSTACK *) malloc((unsigned) sizeof(BTSTACK)))
	    ==  (BTSTACK *) NULL)
		return (RET_ERROR);
	new->bts_pgno = pgno;
	new->bts_next = t->bt_stack;
	t->bt_stack = new;

	return (RET_SUCCESS);
E 4
I 4
	len = MIN(a->size, b->size);
	for (p1 = a->data, p2 = b->data; len--; ++p1, ++p2)
D 14
		if (diff = *p1 - *p2)
D 11
			return(diff);
	return(a->size - b->size);
E 11
I 11
			return (diff);
	return (a->size - b->size);
E 14
I 14
		if (*p1 != *p2)
			return ((int)*p1 - (int)*p2);
	return ((int)a->size - (int)b->size);
E 14
E 11
E 4
}

D 4
pgno_t
_bt_pop(t)
	BTREE_P t;
E 4
I 4
/*
 * __BT_DEFPFX -- Default prefix routine.
 *
 * Parameters:
 *	a:	DBT #1
 *	b: 	DBT #2
 *
 * Returns:
 *	Number of bytes needed to distinguish b from a.
 */
D 14
int
E 14
I 14
size_t
E 14
__bt_defpfx(a, b)
	const DBT *a, *b;
E 4
{
D 4
	BTSTACK *s;
	pgno_t p = P_NONE;
E 4
I 4
	register u_char *p1, *p2;
D 14
	register int len;
	int cnt;
E 14
I 14
	register size_t cnt, len;
E 14
E 4

D 4
	if ((s = t->bt_stack) != (BTSTACK *) NULL) {
		p = s->bts_pgno;
		t->bt_stack = s->bts_next;
		(void) free ((char *) s);
	}
	return (p);
E 4
I 4
	cnt = 1;
	len = MIN(a->size, b->size);
	for (p1 = a->data, p2 = b->data; len--; ++p1, ++p2, ++cnt)
		if (*p1 != *p2)
D 11
			return(cnt);
E 11
I 11
			return (cnt);
E 11
D 5
	if (a->size == b->size)
		return (a->size);
	return(a->size + 1);
E 5
I 5

	/* a->size must be <= b->size, or they wouldn't be in this order. */
	return (a->size < b->size ? a->size + 1 : a->size);
E 5
E 4
}
D 4

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

#ifdef DEBUG
_punt()
{
	int pid;

	pid = getpid();
	(void) kill(pid, SIGILL);
}
#endif /* DEBUG */
E 4
E 1
