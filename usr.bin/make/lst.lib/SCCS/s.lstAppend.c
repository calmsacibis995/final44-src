h54984
s 00000/00000/00087
d D 8.2 95/04/28 17:21:34 christos 5 4
c upgraded to the latest NetBSD version
e
s 00002/00002/00085
d D 8.1 93/06/06 15:10:08 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00086
d D 5.3 90/06/01 16:57:48 bostic 3 2
c new copyright notice
e
s 00024/00014/00073
d D 5.2 90/03/11 17:02:41 bostic 2 1
c add Berkeley specific copyright notice
e
s 00087/00000/00000
d D 5.1 90/03/11 16:53:21 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * LstAppend.c --
 *	Add a new node with a new datum after an existing node
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
 * Copyright (c) 1988 by University of California Regents
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
"$Id: lstAppend.c,v 1.6 89/06/13 15:01:33 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * LstAppend.c --
 *	Add a new node with a new datum after an existing node
 */
E 2

#include	"lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_Append --
 *	Create a new node and add it to the given list after the given node.
 *
 * Results:
 *	SUCCESS if all went well.
 *
 * Side Effects:
 *	A new ListNode is created and linked in to the List. The lastPtr
 *	field of the List will be altered if ln is the last node in the
 *	list. lastPtr and firstPtr will alter if the list was empty and
 *	ln was NILLNODE.
 *
 *-----------------------------------------------------------------------
 */
ReturnStatus
Lst_Append (l, ln, d)
    Lst	  	l;	/* affected list */
    LstNode	ln;	/* node after which to append the datum */
    ClientData	d;	/* said datum */
{
    register List 	list;
    register ListNode	lNode;
    register ListNode	nLNode;
    
    if (LstValid (l) && (ln == NILLNODE && LstIsEmpty (l))) {
	goto ok;
    }
    
    if (!LstValid (l) || LstIsEmpty (l)  || ! LstNodeValid (ln, l)) {
	return (FAILURE);
    }
    ok:
    
    list = (List)l;
    lNode = (ListNode)ln;

    PAlloc (nLNode, ListNode);
    nLNode->datum = d;
    nLNode->useCount = nLNode->flags = 0;
    
    if (lNode == NilListNode) {
	if (list->isCirc) {
	    nLNode->nextPtr = nLNode->prevPtr = nLNode;
	} else {
	    nLNode->nextPtr = nLNode->prevPtr = NilListNode;
	}
	list->firstPtr = list->lastPtr = nLNode;
    } else {
	nLNode->prevPtr = lNode;
	nLNode->nextPtr = lNode->nextPtr;
	
	lNode->nextPtr = nLNode;
	if (nLNode->nextPtr != NilListNode) {
	    nLNode->nextPtr->prevPtr = nLNode;
	}
	
	if (lNode == list->lastPtr) {
	    list->lastPtr = nLNode;
	}
    }
    
    return (SUCCESS);
}

E 1
