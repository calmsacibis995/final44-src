h53509
s 00000/00000/00085
d D 8.2 95/04/28 17:21:53 christos 6 5
c upgraded to the latest NetBSD version
e
s 00002/00002/00083
d D 8.1 93/06/06 15:10:50 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00083
d D 5.4 93/05/24 14:46:53 bostic 4 3
c update, bug fix, ANSI C, lint from Christos Zoulas
c see ../SCCS/README.christos for details
e
s 00001/00011/00085
d D 5.3 90/06/01 16:59:49 bostic 3 2
c new copyright notice
e
s 00024/00014/00072
d D 5.2 90/03/11 17:03:05 bostic 2 1
c add Berkeley specific copyright notice
e
s 00086/00000/00000
d D 5.1 90/03/11 16:53:48 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
D 5
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/*-
 * lstForEachFrom.c --
 *	Perform a given function on all elements of a list starting from
 *	a given point.
D 2
 *
 * Copyright (c) 1988 by University of California Regents
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  Neither the University of California nor
 * Adam de Boor makes any representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
E 2
 */
D 2
#ifndef lint
static char *rcsid =
"$Id: lstForEachFrom.c,v 1.8 89/07/13 13:55:55 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

#include	"lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_ForEachFrom --
 *	Apply the given function to each element of the given list. The
 *	function should return 0 if traversal should continue and non-
 *	zero if it should abort. 
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Only those created by the passed-in function.
 *
 *-----------------------------------------------------------------------
 */
/*VARARGS2*/
void
Lst_ForEachFrom (l, ln, proc, d)
    Lst	    	    	l;
    LstNode    	  	ln;
    register int	(*proc)();
    register ClientData	d;
{
    register ListNode	tln = (ListNode)ln;
    register List 	list = (List)l;
    register ListNode	next;
    Boolean 	    	done;
    int     	    	result;
    
    if (!LstValid (list) || LstIsEmpty (list)) {
	return;
    }
    
    do {
	/*
	 * Take care of having the current element deleted out from under
	 * us.
	 */
	
	next = tln->nextPtr;
	
D 4
	tln->useCount++;
E 4
I 4
	(void) tln->useCount++;
E 4
	result = (*proc) (tln->datum, d);
D 4
	tln->useCount--;
E 4
I 4
	(void) tln->useCount--;
E 4

	/*
	 * We're done with the traversal if
	 *  - nothing's been added after the current node and
	 *  - the next node to examine is the first in the queue or
	 *    doesn't exist.
	 */
	done = (next == tln->nextPtr &&
		(next == NilListNode || next == list->firstPtr));
	
	next = tln->nextPtr;

	if (tln->flags & LN_DELETED) {
	    free((char *)tln);
	}
	tln = next;
    } while (!result && !LstIsEmpty(list) && !done);
    
}
D 4

E 4
E 1
