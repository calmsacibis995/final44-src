h56877
s 00000/00000/00088
d D 8.2 95/04/28 17:21:57 christos 5 4
c upgraded to the latest NetBSD version
e
s 00002/00002/00086
d D 8.1 93/06/06 15:11:22 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00087
d D 5.3 90/06/01 17:00:57 bostic 3 2
c new copyright notice
e
s 00024/00014/00074
d D 5.2 90/03/11 17:03:21 bostic 2 1
c add Berkeley specific copyright notice
e
s 00088/00000/00000
d D 5.1 90/03/11 16:54:04 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
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
 * LstNext.c --
 *	Return the next node for a list.
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
"$Id: lstNext.c,v 1.8 88/11/17 20:53:40 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

#include	"lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_Next --
 *	Return the next node for the given list.
 *
 * Results:
 *	The next node or NILLNODE if the list has yet to be opened. Also
 *	if the list is non-circular and the end has been reached, NILLNODE
 *	is returned.
 *
 * Side Effects:
 *	the curPtr field is updated.
 *
 *-----------------------------------------------------------------------
 */
LstNode
Lst_Next (l)
    Lst	    	  l;
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
	    /*
	     * If we're just starting out, atEnd will be Unknown.
	     * Then we want to start this thing off in the right
	     * direction -- at the start with atEnd being Middle.
	     */
	    list->curPtr = tln = list->firstPtr;
	    list->atEnd = Middle;
	} else {
	    tln = NilListNode;
	    list->atEnd = Tail;
	}
    } else {
	tln = list->curPtr->nextPtr;
	list->curPtr = tln;

	if (tln == list->firstPtr || tln == NilListNode) {
	    /*
	     * If back at the front, then we've hit the end...
	     */
	    list->atEnd = Tail;
	} else {
	    /*
	     * Reset to Middle if gone past first.
	     */
	    list->atEnd = Middle;
	}
    }
    
    return ((LstNode)tln);
}

E 1
