h32554
s 00002/00002/00070
d D 8.1 93/06/06 15:50:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00066
d D 5.2 91/04/16 14:52:45 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00002/00063
d D 5.1 85/06/06 15:58:43 dist 2 1
c Add copyright
e
s 00065/00000/00000
d D 1.1 82/01/18 19:21:33 linton 1 0
c date and time created 82/01/18 19:21:33 by linton
e
u
U
t
T
I 1
D 2
/* Copyright (c) 1982 Regents of the University of California */
E 2
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
E 3
 */
E 2

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
E 2

/*
 * A recursive tree search routine to test if two trees
 * are structurally equivalent.
 */

#include "defs.h"
#include "tree.h"
#include "tree.rep"

BOOLEAN tr_equal(t1, t2)
register NODE *t1;
register NODE *t2;
{
	if (t1 == NIL && t2 == NIL) {
		return(TRUE);
	}
	if (t1 == NIL || t2 == NIL) {
		return(FALSE);
	}
	if (t1->op != t2->op || degree(t1->op) != degree(t2->op)) {
		return(FALSE);
	}
	switch(degree(t1->op)) {
		case LEAF:
			switch(t1->op) {
				case O_NAME:
					return(t1->nameval == t2->nameval);

				case O_QNAME:
					if (!tr_equal(t1->right, t2->right)) {
						return(FALSE);
					}
					return(tr_equal(t1->left, t2->left));

				case O_LCON:
					return(t1->lconval == t2->lconval);

				case O_FCON:
					return(t1->fconval == t2->fconval);

				case O_SCON:
					return(t1->sconval == t2->sconval);

				default:
					panic("tr_equal: leaf %d\n", t1->op);
			}
			/*NOTREACHED*/

		case BINARY:
			if (!tr_equal(t1->right, t2->right)) {
				return(FALSE);
			}
			/* else fall through */
		case UNARY:
			return(tr_equal(t1->left, t2->left));

		default:
			panic("tr_equal: bad degree for op %d\n", t1->op);
	}
	/*NOTREACHED*/
}
E 1
