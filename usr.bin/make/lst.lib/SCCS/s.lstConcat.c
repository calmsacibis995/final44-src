h38213
s 00002/00000/00148
d D 8.2 95/04/28 17:21:37 christos 5 4
c upgraded to the latest NetBSD version
e
s 00002/00002/00146
d D 8.1 93/06/06 15:10:19 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00147
d D 5.3 90/06/01 16:58:22 bostic 3 2
c new copyright notice
e
s 00024/00015/00134
d D 5.2 90/03/11 17:02:48 bostic 2 1
c add Berkeley specific copyright notice
e
s 00149/00000/00000
d D 5.1 90/03/11 16:53:28 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * listConcat.c --
 *	Function to concatentate two lists.
E 2
I 2
/*
D 4
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
E 2
 *
D 2
 * Copyright (c) 1988 by the Regents of the University of California
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
D 2
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  Neither the University of California nor
 * Adam de Boor makes any representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 *
E 2
I 2
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
E 2
 */
I 2

E 2
#ifndef lint
D 2
static char *rcsid =
"$Id: lstConcat.c,v 1.6 89/07/06 12:50:04 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * listConcat.c --
 *	Function to concatentate two lists.
 */
E 2

#include    "lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_Concat --
 *	Concatenate two lists. New elements are created to hold the data
 *	elements, if specified, but the elements themselves are not copied.
 *	If the elements should be duplicated to avoid confusion with another
 *	list, the Lst_Duplicate function should be called first.
 *	If LST_CONCLINK is specified, the second list is destroyed since
 *	its pointers have been corrupted and the list is no longer useable.
 *
 * Results:
 *	SUCCESS if all went well. FAILURE otherwise.
 *
 * Side Effects:
 *	New elements are created and appended the the first list.
 *-----------------------------------------------------------------------
 */
ReturnStatus
Lst_Concat (l1, l2, flags)
    Lst    	  	l1; 	/* The list to which l2 is to be appended */
    Lst    	  	l2; 	/* The list to append to l1 */
    int	   	  	flags;  /* LST_CONCNEW if LstNode's should be duplicated
				 * LST_CONCLINK if should just be relinked */
{
    register ListNode  	ln;     /* original LstNode */
    register ListNode  	nln;    /* new LstNode */
    register ListNode  	last;   /* the last element in the list. Keeps
				 * bookkeeping until the end */
    register List 	list1 = (List)l1;
    register List 	list2 = (List)l2;

    if (!LstValid (l1) || !LstValid (l2)) {
	return (FAILURE);
    }

    if (flags == LST_CONCLINK) {
	if (list2->firstPtr != NilListNode) {
	    /*
	     * We set the nextPtr of the
	     * last element of list two to be NIL to make the loop easier and
	     * so we don't need an extra case should the first list turn
	     * out to be non-circular -- the final element will already point
	     * to NIL space and the first element will be untouched if it
	     * existed before and will also point to NIL space if it didn't.
	     */
	    list2->lastPtr->nextPtr = NilListNode;
	    /*
	     * So long as the second list isn't empty, we just link the
	     * first element of the second list to the last element of the
	     * first list. If the first list isn't empty, we then link the
	     * last element of the list to the first element of the second list
	     * The last element of the second list, if it exists, then becomes
	     * the last element of the first list.
	     */
	    list2->firstPtr->prevPtr = list1->lastPtr;
	    if (list1->lastPtr != NilListNode) {
 		list1->lastPtr->nextPtr = list2->firstPtr;
I 5
	    } else {
		list1->firstPtr = list2->firstPtr;
E 5
	    }
	    list1->lastPtr = list2->lastPtr;
	}
	if (list1->isCirc && list1->firstPtr != NilListNode) {
	    /*
	     * If the first list is supposed to be circular and it is (now)
	     * non-empty, we must make sure it's circular by linking the
	     * first element to the last and vice versa
	     */
	    list1->firstPtr->prevPtr = list1->lastPtr;
	    list1->lastPtr->nextPtr = list1->firstPtr;
	}
	free ((Address)l2);
    } else if (list2->firstPtr != NilListNode) {
	/*
	 * We set the nextPtr of the last element of list 2 to be nil to make
	 * the loop less difficult. The loop simply goes through the entire
	 * second list creating new LstNodes and filling in the nextPtr, and
	 * prevPtr to fit into l1 and its datum field from the
	 * datum field of the corresponding element in l2. The 'last' node
	 * follows the last of the new nodes along until the entire l2 has
	 * been appended. Only then does the bookkeeping catch up with the
	 * changes. During the first iteration of the loop, if 'last' is nil,
	 * the first list must have been empty so the newly-created node is
	 * made the first node of the list.
	 */
	list2->lastPtr->nextPtr = NilListNode;
	for (last = list1->lastPtr, ln = list2->firstPtr;
	     ln != NilListNode;
	     ln = ln->nextPtr)
	{
	    PAlloc (nln, ListNode);
	    nln->datum = ln->datum;
	    if (last != NilListNode) {
		last->nextPtr = nln;
	    } else {
		list1->firstPtr = nln;
	    }
	    nln->prevPtr = last;
	    nln->flags = nln->useCount = 0;
	    last = nln;
	}

	/*
	 * Finish bookkeeping. The last new element becomes the last element
	 * of list one. 
	 */
	list1->lastPtr = last;

	/*
	 * The circularity of both list one and list two must be corrected
	 * for -- list one because of the new nodes added to it; list two
	 * because of the alteration of list2->lastPtr's nextPtr to ease the
	 * above for loop.
	 */
	if (list1->isCirc) {
	    list1->lastPtr->nextPtr = list1->firstPtr;
	    list1->firstPtr->prevPtr = list1->lastPtr;
	} else {
	    last->nextPtr = NilListNode;
	}

	if (list2->isCirc) {
	    list2->lastPtr->nextPtr = list2->firstPtr;
	}
    }

    return (SUCCESS);
}
	
E 1
