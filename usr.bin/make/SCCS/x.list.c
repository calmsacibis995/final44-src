h02283
s 00001/00011/00154
d D 5.4 90/06/01 17:08:34 bostic 4 3
c new copyright notice
e
s 00004/00006/00161
d D 5.3 90/03/12 12:19:54 bostic 3 2
c rework to always be "make".  Deleted -M, -B, -C, -v.  Partial deletion
c of .NULL.  Never remove leading components in file search.  # is always a
c comment.  Print usage line, not message.  Make vararg'd routines right.
e
s 00026/00007/00141
d D 5.2 90/03/11 16:50:58 bostic 2 1
c add Berkeley specific copyright notices
e
s 00148/00000/00000
d D 5.1 90/03/11 16:48:05 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/* list.c -
 *
 * This file contains procedures for manipulating lists.
 * Structures may be inserted into or deleted from lists, and
 * they may be moved from one place in a list to another.
 *
 * The header file contains macros to help in determining the destination
 * locations for List_Insert and List_Move.  See list.h for details.
D 2
 *
 * Copyright (C) 1985 Regents of the University of California
 * All rights reserved.
E 2
 */
D 2

#ifndef lint
static char rcsid[] = "$Id: list.c,v 2.1 89/06/13 17:25:04 adam Exp $ SPRITE (Berkeley)";
#endif not lint
E 2

#include "sprite.h"
#include "list.h"
D 3
#include "sys.h"
E 3


/*
 * ----------------------------------------------------------------------------
 *
 * List_Insert --
 *
 *	Insert the list element pointed to by itemPtr into a List after 
 *	destPtr.  Perform a primitive test for self-looping by returning
 *	failure if the list element is being inserted next to itself.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The list containing destPtr is modified to contain itemPtr.
 *
 * ----------------------------------------------------------------------------
 */
void
List_Insert(itemPtr, destPtr)
    register	List_Links *itemPtr;	/* structure to insert */
    register	List_Links *destPtr;	/* structure after which to insert it */
{
    if (itemPtr == (List_Links *) NIL || destPtr == (List_Links *) NIL
	    || !itemPtr || !destPtr || (itemPtr == destPtr)) {
D 3
	Sys_Panic(SYS_FATAL,
		  "List_Insert: inserting this item would create a loop.\n");
E 3
I 3
	Punt("List_Insert: inserting this item would create a loop.\n");
E 3
	return;
    }
    itemPtr->nextPtr = destPtr->nextPtr;
    itemPtr->prevPtr = destPtr;
    destPtr->nextPtr->prevPtr = itemPtr;
    destPtr->nextPtr = itemPtr;
}


/*
 * ----------------------------------------------------------------------------
 *
 * List_Remove --
 *
 *	Remove a list element from the list in which it is contained.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The given structure is removed from its containing list.
 *
 * ----------------------------------------------------------------------------
 */
void
List_Remove(itemPtr)
    register	List_Links *itemPtr;	/* list element to remove */
{
    if (itemPtr == (List_Links *) NIL || itemPtr == itemPtr->nextPtr
	    || !itemPtr) {
D 3
	Sys_Panic(SYS_FATAL, "List_Remove: invalid item to remove.\n");
E 3
I 3
	Punt("List_Remove: invalid item to remove.\n");
E 3
    }
    itemPtr->prevPtr->nextPtr = itemPtr->nextPtr;
    itemPtr->nextPtr->prevPtr = itemPtr->prevPtr;
}


/*
 * ----------------------------------------------------------------------------
 *
 * List_Move --
 *
 *	Move the list element referenced by itemPtr to follow destPtr.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	List ordering is modified.
 *
 * ----------------------------------------------------------------------------
 */
void
List_Move(itemPtr, destPtr)
    register List_Links *itemPtr; /* list element to be moved */
    register List_Links *destPtr; /* element after which it is to be placed */
{

    if (itemPtr == (List_Links *) NIL || destPtr == (List_Links *) NIL
	    || !itemPtr || !destPtr) {
D 3
	Sys_Panic(SYS_FATAL, "List_Move: One of the list items is NIL.\n");
E 3
I 3
	Punt("List_Move: One of the list items is NIL.\n");
E 3
    }
    /*
     * It is conceivable that someone will try to move a list element to
     * be after itself.
     */
    if (itemPtr != destPtr) {
	List_Remove(itemPtr);
	List_Insert(itemPtr, destPtr);
    }    
}


/*
 * ----------------------------------------------------------------------------
 *
 * List_Init --
 *
 *	Initialize a header pointer to point to an empty list.  The List_Links
 *	structure must already be allocated.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The header's pointers are modified to point to itself.
 *
 * ----------------------------------------------------------------------------
 */
void
List_Init(headerPtr)
    register List_Links *headerPtr;  /* Pointer to a List_Links structure 
					to be header */
{
    if (headerPtr == (List_Links *) NIL || !headerPtr) {
D 3
	Sys_Panic(SYS_FATAL, "List_Init: invalid header pointer.\n");
E 3
I 3
	Punt("List_Init: invalid header pointer.\n");
E 3
    }
    headerPtr->nextPtr = headerPtr;
    headerPtr->prevPtr = headerPtr;
}
E 1
