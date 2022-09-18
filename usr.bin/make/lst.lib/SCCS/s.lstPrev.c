h04667
s 00024/00014/00062
d D 5.2 90/03/11 17:03:25 bostic 2 1
c add Berkeley specific copyright notice
e
s 00076/00000/00000
d D 5.1 90/03/11 16:54:09 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
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
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/*-
 * LstPrev.c --
 *	Get the node previous to the current one in the list and make it the
 *	current node.
 *	The sequential functions access the list in a slightly different way.
 *	CurPtr points to their idea of the current node in the list and they
 *	access the list based on it. Because the list is circular, Lst_Next
 *	and Lst_Prev will go around the list forever. Lst_IsAtEnd must be
 *	used to determine when to stop.
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
"$Id: lstPrev.c,v 1.8 88/11/17 20:53:54 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

#include	"lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_Prev --
 *	Return the node previous to the current one for the given list.
 *
 * Results:
 *	The previous node or NILLNODE if the list hasn't been opened
 *	yet or the beginning was reached.
 *
 * Side Effects:
 *	the curPtr is changed to reflect reality.
 *
 *-----------------------------------------------------------------------
 */
LstNode
Lst_Prev (l)
    Lst	    	  	l;
{
    register ListNode	tln;
    register List 	list = (List)l;
    
    if ((LstValid (l) == FALSE) ||
	(list->isOpen == FALSE)) {
	    return (NILLNODE);
    }
    
    list->prevPtr = list->curPtr;
    
    if (list->curPtr == NilListNode) {
	if (list->atEnd == Unknown) {
	    list->curPtr = tln = list->lastPtr;
	    list->atEnd = Middle;
	} else {
	    tln = NilListNode;
	    list->atEnd = Head;
	}
    } else {
	tln = list->curPtr->prevPtr;
	list->curPtr = tln;
	if (tln == list->lastPtr || tln == NilListNode) {
	    list->atEnd = Head;
	} else {
	    list->atEnd = Middle;
	}
    }
    
    return ((LstNode)tln);
}

E 1
