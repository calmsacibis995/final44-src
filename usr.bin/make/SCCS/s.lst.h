h20103
s 00067/00049/00070
d D 8.2 95/04/28 17:08:12 christos 6 5
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00117
d D 8.1 93/06/06 15:15:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00116
d D 5.4 93/05/24 14:45:44 bostic 4 3
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00011/00115
d D 5.3 90/06/01 17:08:45 bostic 3 2
c new copyright notice
e
s 00028/00012/00102
d D 5.2 90/03/11 15:55:17 bostic 2 1
c add Berkeley specific copyright notice
e
s 00114/00000/00000
d D 5.1 90/03/11 15:49:03 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * lst.h --
 *	Header for using the list library
E 2
I 2
/*
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
 * $Id: lst.h,v 1.10 88/11/17 20:51:41 adam Exp $ SPRITE (Berkeley)
E 2
I 2
 *	%W% (Berkeley) %G%
 */

/*-
 * lst.h --
 *	Header for using the list library
E 2
 */
#ifndef _LST_H_
#define _LST_H_

#include	<sprite.h>
I 4
#if __STDC__
#include	<stdlib.h>
#endif
E 4

/*
 * basic typedef. This is what the Lst_ functions handle
 */

typedef	struct	Lst	*Lst;
typedef	struct	LstNode	*LstNode;

#define	NILLST		((Lst) NIL)
#define	NILLNODE	((LstNode) NIL)

/*
 * NOFREE can be used as the freeProc to Lst_Destroy when the elements are
 *	not to be freed.
 * NOCOPY performs similarly when given as the copyProc to Lst_Duplicate.
 */
D 6
#define NOFREE		((void (*)()) 0)
#define NOCOPY		((ClientData (*)()) 0)
E 6
I 6
#define NOFREE		((void (*) __P((ClientData))) 0)
#define NOCOPY		((ClientData (*) __P((ClientData))) 0)
E 6

#define LST_CONCNEW	0   /* create new LstNode's when using Lst_Concat */
#define LST_CONCLINK	1   /* relink LstNode's when using Lst_Concat */

/*
 * Creation/destruction functions
 */
D 6
Lst		  Lst_Init();	    	/* Create a new list */
Lst	    	  Lst_Duplicate();  	/* Duplicate an existing list */
void		  Lst_Destroy();	/* Destroy an old one */
E 6
I 6
/* Create a new list */
Lst		Lst_Init __P((Boolean));
/* Duplicate an existing list */
Lst		Lst_Duplicate __P((Lst, ClientData (*)(ClientData)));
/* Destroy an old one */
void		Lst_Destroy __P((Lst, void (*)(ClientData)));
/* True if list is empty */
Boolean		Lst_IsEmpty __P((Lst));
E 6

D 6
int	    	  Lst_Length();	    	/* Find the length of a list */
Boolean		  Lst_IsEmpty();	/* True if list is empty */

E 6
/*
 * Functions to modify a list
 */
D 6
ReturnStatus	  Lst_Insert();	    	/* Insert an element before another */
ReturnStatus	  Lst_Append();	    	/* Insert an element after another */
ReturnStatus	  Lst_AtFront();    	/* Place an element at the front of
					 * a lst. */
ReturnStatus	  Lst_AtEnd();	    	/* Place an element at the end of a
					 * lst. */
ReturnStatus	  Lst_Remove();	    	/* Remove an element */
ReturnStatus	  Lst_Replace();	/* Replace a node with a new value */
ReturnStatus	  Lst_Move();	    	/* Move an element to another place */
ReturnStatus	  Lst_Concat();	    	/* Concatenate two lists */
E 6
I 6
/* Insert an element before another */
ReturnStatus	Lst_Insert __P((Lst, LstNode, ClientData));
/* Insert an element after another */
ReturnStatus	Lst_Append __P((Lst, LstNode, ClientData));
/* Place an element at the front of a lst. */
ReturnStatus	Lst_AtFront __P((Lst, ClientData));
/* Place an element at the end of a lst. */
ReturnStatus	Lst_AtEnd __P((Lst, ClientData));
/* Remove an element */
ReturnStatus	Lst_Remove __P((Lst, LstNode));
/* Replace a node with a new value */
ReturnStatus	Lst_Replace __P((LstNode, ClientData));
/* Concatenate two lists */
ReturnStatus	Lst_Concat __P((Lst, Lst, int));
E 6

/*
 * Node-specific functions
 */
D 6
LstNode		  Lst_First();	    	/* Return first element in list */
LstNode		  Lst_Last();	    	/* Return last element in list */
LstNode		  Lst_Succ();	    	/* Return successor to given element */
LstNode		  Lst_Pred();	    	/* Return predecessor to given
					 * element */
ClientData	  Lst_Datum();	    	/* Get datum from LstNode */
E 6
I 6
/* Return first element in list */
LstNode		Lst_First __P((Lst));
/* Return last element in list */
LstNode		Lst_Last __P((Lst));
/* Return successor to given element */
LstNode		Lst_Succ __P((LstNode));
/* Get datum from LstNode */
ClientData	Lst_Datum __P((LstNode));
E 6

/*
 * Functions for entire lists
 */
D 6
LstNode		  Lst_Find();	    	/* Find an element in a list */
LstNode		  Lst_FindFrom();	/* Find an element starting from
					 * somewhere */
LstNode	    	  Lst_Member();	    	/* See if the given datum is on the
					 * list. Returns the LstNode containing
					 * the datum */
int	    	  Lst_Index();	    	/* Returns the index of a datum in the
					 * list, starting from 0 */
void		  Lst_ForEach();	/* Apply a function to all elements of
					 * a lst */
void	    	  Lst_ForEachFrom();  	/* Apply a function to all elements of
					 * a lst starting from a certain point.
					 * If the list is circular, the
					 * application will wrap around to the
					 * beginning of the list again. */
E 6
I 6
/* Find an element in a list */
LstNode		Lst_Find __P((Lst, ClientData, 
			      int (*)(ClientData, ClientData)));
/* Find an element starting from somewhere */
LstNode		Lst_FindFrom __P((Lst, LstNode, ClientData,
				  int (*cProc)(ClientData, ClientData)));
/* 
 * See if the given datum is on the list. Returns the LstNode containing
 * the datum
 */
LstNode		Lst_Member __P((Lst, ClientData));
/* Apply a function to all elements of a lst */
void		Lst_ForEach __P((Lst, int (*)(ClientData, ClientData),
				 ClientData));
E 6
/*
I 6
 * Apply a function to all elements of a lst starting from a certain point.
 * If the list is circular, the application will wrap around to the
 * beginning of the list again.
 */
void		Lst_ForEachFrom __P((Lst, LstNode,
				     int (*)(ClientData, ClientData),
				     ClientData));
/*
E 6
 * these functions are for dealing with a list as a table, of sorts.
 * An idea of the "current element" is kept and used by all the functions
 * between Lst_Open() and Lst_Close().
 */
D 6
ReturnStatus	  Lst_Open();	    	/* Open the list */
LstNode		  Lst_Prev();	    	/* Previous element */
LstNode		  Lst_Cur();	    	/* The current element, please */
LstNode		  Lst_Next();	    	/* Next element please */
Boolean		  Lst_IsAtEnd();	/* Done yet? */
void		  Lst_Close();	    	/* Finish table access */
E 6
I 6
/* Open the list */
ReturnStatus	Lst_Open __P((Lst));
/* Next element please */
LstNode		Lst_Next __P((Lst));
/* Done yet? */
Boolean		Lst_IsAtEnd __P((Lst));
/* Finish table access */
void		Lst_Close __P((Lst));
E 6

/*
 * for using the list as a queue
 */
D 6
ReturnStatus	  Lst_EnQueue();	/* Place an element at tail of queue */
ClientData	  Lst_DeQueue();	/* Remove an element from head of
					 * queue */
E 6
I 6
/* Place an element at tail of queue */
ReturnStatus	Lst_EnQueue __P((Lst, ClientData));
/* Remove an element from head of queue */
ClientData	Lst_DeQueue __P((Lst));
E 6

D 6
#endif _LST_H_
E 6
I 6
#endif /* _LST_H_ */
E 6
E 1
