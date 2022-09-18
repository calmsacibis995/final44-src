h10742
s 00000/00000/00084
d D 8.2 95/04/28 17:23:15 christos 6 5
c pgraded to the latest version from NetBSD
e
s 00002/00002/00082
d D 8.1 93/06/06 15:13:40 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00083
d D 5.4 90/12/28 18:07:14 bostic 4 3
c replace hash.c; speedup/cleanup from Chris Torek
e
s 00001/00011/00083
d D 5.3 90/06/01 17:00:16 bostic 3 2
c new copyright notice
e
s 00022/00012/00072
d D 5.2 90/03/12 08:13:48 bostic 2 1
c add Berkeley specific copyright
e
s 00084/00000/00000
d D 5.1 90/03/12 08:13:12 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * lstInt.h --
 *	Internals for the list library
E 2
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
 *
D 2
 * $Id: lstInt.h,v 1.11 89/06/13 15:01:46 adam Exp $ SPRITE (Berkeley)
E 2
I 2
 *	%W% (Berkeley) %G%
 */

/*-
 * lstInt.h --
 *	Internals for the list library
E 2
 */
#ifndef _LSTINT_H_
#define _LSTINT_H_

#include	  "lst.h"

typedef struct ListNode {
	struct ListNode	*prevPtr;   /* previous element in list */
	struct ListNode	*nextPtr;   /* next in list */
	short	    	useCount:8, /* Count of functions using the node.
				     * node may not be deleted until count
				     * goes to 0 */
 	    	    	flags:8;    /* Node status flags */
	ClientData	datum;	    /* datum associated with this element */
} *ListNode;
/*
 * Flags required for synchronization
 */
#define LN_DELETED  	0x0001      /* List node should be removed when done */

#define NilListNode	((ListNode)-1)

typedef enum {
    Head, Middle, Tail, Unknown
} Where;

typedef struct	{
	ListNode  	firstPtr; /* first node in list */
	ListNode  	lastPtr;  /* last node in list */
	Boolean	  	isCirc;	  /* true if the list should be considered
				   * circular */
/*
 * fields for sequential access
 */
	Where	  	atEnd;	  /* Where in the list the last access was */
	Boolean	  	isOpen;	  /* true if list has been Lst_Open'ed */
	ListNode  	curPtr;	  /* current node, if open. NilListNode if
				   * *just* opened */
	ListNode  	prevPtr;  /* Previous node, if open. Used by
				   * Lst_Remove */
} *List;

#define NilList	  	((List)-1)

/*
 * PAlloc (var, ptype) --
 *	Allocate a pointer-typedef structure 'ptype' into the variable 'var'
 */
D 4
#define	PAlloc(var,ptype)	var = (ptype) Malloc (sizeof (*var))
E 4
I 4
#define	PAlloc(var,ptype)	var = (ptype) malloc (sizeof (*var))
E 4

/*
 * LstValid (l) --
 *	Return TRUE if the list l is valid
 */
#define LstValid(l)	(((Lst)l == NILLST) ? FALSE : TRUE)

/*
 * LstNodeValid (ln, l) --
 *	Return TRUE if the LstNode ln is valid with respect to l
 */
#define LstNodeValid(ln, l)	((((LstNode)ln) == NILLNODE) ? FALSE : TRUE)

/*
 * LstIsEmpty (l) --
 *	TRUE if the list l is empty.
 */
#define LstIsEmpty(l)	(((List)l)->firstPtr == NilListNode)

#endif _LSTINT_H_
E 1
