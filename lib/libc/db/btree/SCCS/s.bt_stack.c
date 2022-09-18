h22265
s 00001/00001/00065
d D 8.3 94/02/21 17:43:21 bostic 7 6
c cast alloc's to shut SunOS up
e
s 00001/00001/00065
d D 8.2 94/02/21 15:08:17 bostic 6 5
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00064
d D 8.1 93/06/04 15:21:04 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00065
d D 5.4 93/02/11 11:39:30 bostic 4 3
c move db.h to the end of the includes, make compat.h work better
e
s 00003/00001/00063
d D 5.3 92/11/13 16:05:36 bostic 3 2
c prettiness police
e
s 00005/00005/00059
d D 5.2 91/09/12 11:43:23 bostic 2 1
c bt_push -> __bt_push
e
s 00064/00000/00000
d D 5.1 91/09/04 12:50:48 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
D 3
#include <errno.h>
E 3
I 3

E 3
D 4
#include <db.h>
E 4
I 3
#include <errno.h>
E 3
#include <stdio.h>
#include <stdlib.h>
I 3

I 4
#include <db.h>
E 4
E 3
#include "btree.h"

/*
 * When a page splits, a new record has to be inserted into its parent page.
 * This page may have to split as well, all the way up to the root.  Since
 * parent pointers in each page would be expensive, we maintain a stack of
 * parent pages as we descend the tree.
 *
 * XXX
D 2
 * This is a problem for multiple users -- if user a creates a stack, then user
 * b splits the tree, then user a tries to split the tree, there's a new level
 * in the tree that user b doesn't know about.
E 2
I 2
 * This is a concurrency problem -- if user a builds a stack, then user b
 * splits the tree, then user a tries to split the tree, there's a new level
 * in the tree that user a doesn't know about.
E 2
 */

/*
D 2
 * BT_PUSH -- Push parent page info onto the stack (LIFO).
E 2
I 2
 * __BT_PUSH -- Push parent page info onto the stack (LIFO).
E 2
 *
 * Parameters:
 *	t:	tree
 *	pgno:	page
 *	index:	page index
 *
 * Returns:
 * 	RET_ERROR, RET_SUCCESS
 */
int
D 2
bt_push(t, pgno, index)
E 2
I 2
__bt_push(t, pgno, index)
E 2
	BTREE *t;
	pgno_t pgno;
D 6
	int index;
E 6
I 6
	indx_t index;
E 6
{
	if (t->bt_sp == t->bt_maxstack) {
		t->bt_maxstack += 50;
D 7
		if ((t->bt_stack = realloc(t->bt_stack,
E 7
I 7
		if ((t->bt_stack = (EPGNO *)realloc(t->bt_stack,
E 7
		    t->bt_maxstack * sizeof(EPGNO))) == NULL) {
			t->bt_maxstack -= 50;
			return (RET_ERROR);
		}
	}

	t->bt_stack[t->bt_sp].pgno = pgno;
	t->bt_stack[t->bt_sp].index = index;
	++t->bt_sp;
	return (RET_SUCCESS);
}
E 1
