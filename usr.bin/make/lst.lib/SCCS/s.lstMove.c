h42395
s 00024/00014/00053
d D 5.2 90/03/11 17:03:20 bostic 2 1
c add Berkeley specific copyright notice
e
s 00067/00000/00000
d D 5.1 90/03/11 16:54:02 bostic 1 0
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
 * LstMove.c --
 *	Move an existing node after or before one in the same or different
 *	list.
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
"$Id: lstMove.c,v 1.6 89/06/13 15:01:48 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

#include	"lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_Move --
 *	Move a node after or before a destination node. The nodes do not
 *	need to be in the same list, of course.
 *
 * Results:
 *	SUCCESS or FAILURE.
 *
 * Side Effects:
 *	The firstPtr and lastPtr fields of either or both of the involved
 *	lists may be altered to reflect reality.
 *
 *-----------------------------------------------------------------------
 */
ReturnStatus
Lst_Move (ls, lns, ld, lnd, before)
    Lst	    	    	ls; 	/* Source list */
    register LstNode  	lns;	/* source list node */
    Lst	    	    	ld; 	/* Destination list */
    register LstNode  	lnd;	/* destination list node */
    Boolean		before;	/* true if should use Lst_Insert */
{
    ClientData	d;
    ReturnStatus	rval;
    
    if (lns == NILLNODE || lnd == NILLNODE) {
	return (FAILURE);
    }
    
    d = ((ListNode)lns)->datum;
    
    if (Lst_Remove (ls, lns) == FAILURE) {
	return (FAILURE);
    }
    
    if (before == TRUE) {
	rval = Lst_Insert (ld, lnd, d);
    } else {
	rval = Lst_Append (ld, lnd, d);
    }
    
    return (rval);
}

E 1
