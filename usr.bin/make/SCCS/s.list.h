h32743
s 00000/00000/00272
d D 8.2 95/04/28 17:08:11 christos 6 5
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00270
d D 8.1 93/06/06 15:15:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00271
d D 5.4 93/05/24 14:45:43 bostic 4 3
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00011/00271
d D 5.3 90/06/01 17:08:39 bostic 3 2
c new copyright notice
e
s 00028/00005/00258
d D 5.2 90/03/11 15:55:15 bostic 2 1
c add Berkeley specific copyright notice
e
s 00263/00000/00000
d D 5.1 90/03/11 15:49:01 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
/*
D 2
 * list.h --
E 2
I 2
D 5
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 5
I 5
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
E 2
 *
D 2
 * Structures, macros, and routines exported by the List module.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
D 2
 * Copyright (C) 1985 Regents of the University of California
 * All rights reserved.
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
 *
D 2
 * rcsid "$Id: list.h,v 2.1 89/07/03 15:56:45 adam Exp $ SPRITE (Berkeley)"
E 2
I 2
 *	%W% (Berkeley) %G%
 */

/*
 * list.h --
 *
 * Structures, macros, and routines exported by the List module.
E 2
 */

#ifndef _LIST
#define _LIST

#ifndef _SPRITE
#include "sprite.h"
#endif _SPRITE

/*
 * This module defines the list abstraction, which enables one to link
 * together arbitrary data structures.  Lists are doubly-linked and
 * circular.  A list contains a header followed by its real members, if
 * any.  (An empty list therefore consists of a single element, the
 * header,  whose nextPtr and prevPtr fields point to itself).  To refer
 * to a list as a whole, the user keeps a pointer to the header; that
 * header is initialized by a call to List_Init(), which creates an empty
 * list given a pointer to a List_Links structure (described below).
 * 
 * The links are contained in a two-element structure called List_Links.
 * A list joins List_Links records (that is, each List_Links structure
 * points to other List_Links structures), but if the List_Links is the
 * first field within a larger structure, then the larger structures are
 * effectively linked together as follows:
 * 
 *	      header
 *	  (List_Links)		   first elt.		    second elt.
 *	-----------------	-----------------	----------------- 
 * ..->	|    nextPtr	| ---->	|  List_Links	| ---->	|  List_Links	|----..
 *	| - - - - - - -	|	|		|	|		| 
 * ..--	|    prevPtr	| <----	|		| <----	|		|<---..
 *	-----------------	- ---  ---  ---	-	- ---  ---  ---	-
 *				|    rest of	|	|    rest of	| 
 *				|   structure	|	|   structure	| 
 *				|		|	|		|
 *				|      ...	|	|      ...	| 
 *				-----------------	----------------- 
 * 
 * It is possible to link structures through List_Links fields that are
 * not at the beginning of the larger structure, but it is then necessary
 * to perform pointer arithmetic to find the beginning of the larger
 * structure, given a pointer to some point within it.
 * 
 * A typical structure might be something like:
 * 
 *      typedef struct {
 *                  List_Links links;
 *                  char ch;
 *                  integer flags;
 *      } EditChar;
 *  
 * Before an element is inserted in a list for the first time, it must
 * be initialized by calling the macro List_InitElement().
 */


/*
 * data structure for lists
 */

typedef struct List_Links {
    struct List_Links *prevPtr;
    struct List_Links *nextPtr;
} List_Links;

/*
 * procedures
 */

void	List_Init();    /* initialize a header to a list */
void    List_Insert();  /* insert an element into a list */
void 	List_Remove();  /* remove an element from a list */
void 	List_Move();    /* move an element elsewhere in a list */

/*
 * ----------------------------------------------------------------------------
 *
 * List_InitElement --
 *
 *      Initialize a list element.  Must be called before an element is first
 *	inserted into a list.
 *
 * ----------------------------------------------------------------------------
 */
#define List_InitElement(elementPtr) \
    (elementPtr)->prevPtr = (List_Links *) NIL; \
    (elementPtr)->nextPtr = (List_Links *) NIL;
    
/*
 * Macros for stepping through or selecting parts of lists
 */

/*
 * ----------------------------------------------------------------------------
 *
 * LIST_FORALL --
 *
 *      Macro to loop through a list and perform an operation on each member.
 *
 *      Usage: LIST_FORALL(headerPtr, itemPtr) {
 *                 / * 
 *                   * operation on itemPtr, which points to successive members
 *                   * of the list
 *                   * 
 *                   * It may be appropriate to first assign
 *                   *          foobarPtr = (Foobar *) itemPtr;
 *                   * to refer to the entire Foobar structure.
 *                   * /
 *             }
 *
 *      Note: itemPtr must be a List_Links pointer variable, and headerPtr
 *      must evaluate to a pointer to a List_Links structure.
 *
 * ----------------------------------------------------------------------------
 */

#define LIST_FORALL(headerPtr, itemPtr) \
        for (itemPtr = List_First(headerPtr); \
             !List_IsAtEnd((headerPtr),itemPtr); \
             itemPtr = List_Next(itemPtr))

/*
 * ----------------------------------------------------------------------------
 *
 * List_IsEmpty --
 *
 *      Macro: Boolean value, TRUE if the given list does not contain any
 *      members.
 *
 *      Usage: if (List_IsEmpty(headerPtr)) ...
 *
 * ----------------------------------------------------------------------------
 */

#define List_IsEmpty(headerPtr) \
        ((headerPtr) == (headerPtr)->nextPtr)

/*
 * ----------------------------------------------------------------------------
 *
 * List_IsAtEnd --
 *
 *      Macro: Boolean value, TRUE if itemPtr is after the end of headerPtr
 *      (i.e., itemPtr is the header of the list).
 *
 *      Usage: if (List_IsAtEnd(headerPtr, itemPtr)) ...
 *
 * ----------------------------------------------------------------------------
 */


#define List_IsAtEnd(headerPtr, itemPtr) \
        ((itemPtr) == (headerPtr))


/*
 * ----------------------------------------------------------------------------
 *
 * List_First --
 *
 *      Macro to return the first member in a list, which is the header if
 *      the list is empty.
 *
 *      Usage: firstPtr = List_First(headerPtr);
 *
 * ----------------------------------------------------------------------------
 */

#define List_First(headerPtr) ((headerPtr)->nextPtr)

/*
 * ----------------------------------------------------------------------------
 *
 * List_Last --
 *
 *      Macro to return the last member in a list, which is the header if
 *      the list is empty.
 *
 *      Usage: lastPtr = List_Last(headerPtr);
 *
 * ----------------------------------------------------------------------------
 */

#define List_Last(headerPtr) ((headerPtr)->prevPtr)

/*
 * ----------------------------------------------------------------------------
 *
 * List_Prev --
 *
 *      Macro to return the member preceding the given member in its list.
 *      If the given list member is the first element in the list, List_Prev
 *      returns the list header.
 *
 *      Usage: prevPtr = List_Prev(itemPtr);
 *
 * ----------------------------------------------------------------------------
 */

#define List_Prev(itemPtr) ((itemPtr)->prevPtr)

/*
 * ----------------------------------------------------------------------------
 *
 * List_Next --
 *
 *      Macro to return the member following the given member in its list.
 *      If the given list member is the last element in the list, List_Next
 *      returns the list header.
 *
 *      Usage: nextPtr = List_Next(itemPtr);
 *
 * ----------------------------------------------------------------------------
 */

#define List_Next(itemPtr) ((itemPtr)->nextPtr)


/*
 * ----------------------------------------------------------------------------
 *      The List_Insert procedure takes two arguments.  The first argument
 *      is a pointer to the structure to be inserted into a list, and
 *      the second argument is a pointer to the list member after which
 *      the new element is to be inserted.  Macros are used to determine
 *      which existing member will precede the new one.
 *
 *      The List_Move procedure takes a destination argument with the same
 *      semantics as List_Insert.
 *
 *      The following macros define where to insert the new element
 *      in the list:
 *
 *      LIST_AFTER(itemPtr)     --      insert after itemPtr
 *      LIST_BEFORE(itemPtr)    --      insert before itemPtr
 *      LIST_ATFRONT(headerPtr) --      insert at front of list
 *      LIST_ATREAR(headerPtr)  --      insert at end of list
 *
 *      For example, 
 *
 *              List_Insert(itemPtr, LIST_AFTER(otherPtr));
 *
 *      will insert itemPtr following otherPtr in the list containing otherPtr.
 * ----------------------------------------------------------------------------
 */

#define LIST_AFTER(itemPtr) ((List_Links *) itemPtr)

#define LIST_BEFORE(itemPtr) (((List_Links *) itemPtr)->prevPtr)

#define LIST_ATFRONT(headerPtr) ((List_Links *) headerPtr)

#define LIST_ATREAR(headerPtr) (((List_Links *) headerPtr)->prevPtr)

D 4
#endif _LIST
E 4
I 4
#endif /* _LIST */
E 4
E 1
