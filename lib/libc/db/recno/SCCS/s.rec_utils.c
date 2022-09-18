h41296
s 00003/00002/00085
d D 8.3 94/02/21 17:42:48 bostic 10 9
c cast alloc's to shut SunOS up
e
s 00012/00002/00075
d D 8.2 93/09/07 11:52:55 bostic 9 8
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00075
d D 8.1 93/06/04 15:25:40 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00075
d D 5.7 93/02/16 12:33:14 bostic 7 6
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00001/00001/00076
d D 5.6 93/02/11 11:42:24 bostic 6 5
c move db.h to the end of the includes, make compat.h work better
e
s 00001/00001/00076
d D 5.5 92/12/04 14:20:24 bostic 5 4
c copy the length of the data, not the length of the buffer
e
s 00022/00003/00055
d D 5.4 92/11/13 17:37:45 bostic 4 3
c return the keys as well as the data
e
s 00004/00003/00054
d D 5.3 92/06/23 12:34:31 bostic 3 2
c increment necessary dsize by 1 so that we don't crash if the first
c record retrieved is 0 length.
e
s 00004/00003/00053
d D 5.2 91/09/11 16:29:13 bostic 2 1
c use intermediate on realloc so can recover from failure
e
s 00056/00000/00000
d D 5.1 91/09/04 12:54:11 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
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
I 4

E 4
D 6
#include <db.h>
E 6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 4

I 6
#include <db.h>
E 6
E 4
D 2
#include "../btree/btree.h"
E 2
I 2
#include "recno.h"
E 2

/*
 * __REC_RET -- Build return data as a result of search or scan.
 *
 * Parameters:
 *	t:	tree
 *	d:	LEAF to be returned to the user.
 *	data:	user's data structure
 *
 * Returns:
 *	RET_SUCCESS, RET_ERROR.
 */
int
D 4
__rec_ret(t, e, data)
E 4
I 4
__rec_ret(t, e, nrec, key, data)
E 4
	BTREE *t;
	EPG *e;
D 4
	DBT *data;
E 4
I 4
	recno_t nrec;
	DBT *key, *data;
E 4
{
	register RLEAF *rl;
I 2
D 4
	register char *p;
E 4
I 4
	register void *p;
E 4
E 2

I 4
	if (data == NULL)
		goto retkey;

E 4
	rl = GETRLEAF(e->page, e->index);
I 4

I 9
	/*
	 * We always copy big data to make it contigous.  Otherwise, we
	 * leave the page pinned and don't copy unless the user specified
	 * concurrent access.
	 */
E 9
E 4
	if (rl->flags & P_BIGDATA) {
		if (__ovfl_get(t, rl->bytes,
		    &data->size, &t->bt_dbuf, &t->bt_dbufsz))
			return (RET_ERROR);
D 9
	} else {
E 9
I 9
		data->data = t->bt_dbuf;
	} else if (ISSET(t, B_DB_LOCK)) {
E 9
D 3
		if (rl->dsize > t->bt_dbufsz) {
D 2
			if ((t->bt_dbuf =
			    realloc(t->bt_dbuf, rl->dsize)) == NULL)
E 2
I 2
			if ((p = realloc(t->bt_dbuf, rl->dsize)) == NULL)
E 3
I 3
		/* Use +1 in case the first record retrieved is 0 length. */
		if (rl->dsize + 1 > t->bt_dbufsz) {
D 10
			if ((p = realloc(t->bt_dbuf, rl->dsize + 1)) == NULL)
E 10
I 10
			if ((p =
			    (void *)realloc(t->bt_dbuf, rl->dsize + 1)) == NULL)
E 10
E 3
E 2
				return (RET_ERROR);
I 2
			t->bt_dbuf = p;
E 2
D 3
			t->bt_dbufsz = rl->dsize;
E 3
I 3
			t->bt_dbufsz = rl->dsize + 1;
E 3
		}
D 5
		bcopy(rl->bytes, t->bt_dbuf, t->bt_dbufsz);
E 5
I 5
D 7
		bcopy(rl->bytes, t->bt_dbuf, rl->dsize);
E 7
I 7
		memmove(t->bt_dbuf, rl->bytes, rl->dsize);
E 7
E 5
		data->size = rl->dsize;
I 9
		data->data = t->bt_dbuf;
	} else {
		data->size = rl->dsize;
		data->data = rl->bytes;
E 9
	}
D 9
	data->data = t->bt_dbuf;
E 9

I 4
retkey:	if (key == NULL)
		return (RET_SUCCESS);

I 9
	/* We have to copy the key, it's not on the page. */
E 9
	if (sizeof(recno_t) > t->bt_kbufsz) {
D 10
		if ((p = realloc(t->bt_kbuf, sizeof(recno_t))) == NULL)
E 10
I 10
		if ((p = (void *)realloc(t->bt_kbuf, sizeof(recno_t))) == NULL)
E 10
			return (RET_ERROR);
		t->bt_kbuf = p;
		t->bt_kbufsz = sizeof(recno_t);
	}
D 7
	bcopy(&nrec, t->bt_kbuf, sizeof(recno_t));
E 7
I 7
	memmove(t->bt_kbuf, &nrec, sizeof(recno_t));
E 7
	key->size = sizeof(recno_t);
	key->data = t->bt_kbuf;
E 4
	return (RET_SUCCESS);
}
E 1
