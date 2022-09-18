h36176
s 00024/00018/00047
d D 5.2 90/03/11 17:03:30 bostic 2 1
c add Berkeley specific copyright notice
e
s 00065/00000/00000
d D 5.1 90/03/11 16:54:15 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * listSetCirc.c --
 *	Change the library's notion of the circularity of a list.
E 2
I 2
/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
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
 * Copyright (c) 1988 by Adam de Boor
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  The University of California nor
 * Adam de Boor makes any representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 *
 *
E 2
I 2
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
E 2
 */
I 2

E 2
#ifndef lint
D 2
static char *rcsid =
"$Id: lstSetCirc.c,v 1.3 88/11/17 20:54:04 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * listSetCirc.c --
 *	Change the library's notion of the circularity of a list.
 */
E 2

#include	"lstInt.h"

/*
 *------------------------------------------------------------
 * Lst_SetCirc --
 *	change the circularity of a list
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	The circularity of the list is set appropriately. The head and
 *	tail of the list will be linked or unlinked as necessary
 *------------------------------------------------------------
 */
void
Lst_SetCirc (l, circ)
    Lst	    	  l;
    Boolean	  circ;
{
    register List list = (List) l;

    /*
     * if this isn't a change, do nothing.
     */
    if ((list->isCirc && circ) || (!list->isCirc && !circ)) {
	return;
    }
    list->isCirc = circ;
    
    if (LstIsEmpty (l)) {
	return;
    }
    
    if (circ) {
	list->firstPtr->prevPtr = list->lastPtr;
	list->lastPtr->nextPtr = list->firstPtr;
    } else {
	list->firstPtr->prevPtr = NilListNode;
	list->lastPtr->nextPtr = NilListNode;
    }
}
E 1
