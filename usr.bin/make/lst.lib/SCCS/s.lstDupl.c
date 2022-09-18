h51043
s 00002/00001/00071
d D 8.2 95/04/28 17:21:43 christos 5 4
c upgraded to the latest NetBSD version
e
s 00002/00002/00070
d D 8.1 93/06/06 15:10:32 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00071
d D 5.3 90/06/01 16:58:59 bostic 3 2
c new copyright notice
e
s 00024/00007/00058
d D 5.2 90/03/11 17:02:55 bostic 2 1
c add Berkeley specific copyright notice
e
s 00065/00000/00000
d D 5.1 90/03/11 16:53:37 bostic 1 0
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
 * listDupl.c --
 *	Duplicate a list. This includes duplicating the individual
 *	elements.
D 2
 *
 * Copyright (c) 1988 by the Regents of the University of California
 *
E 2
 */
D 2
#ifndef lint
static char *rcsid =
"$Id: lstDupl.c,v 1.4 88/11/17 20:52:21 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

#include    "lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_Duplicate --
 *	Duplicate an entire list. If a function to copy a ClientData is
 *	given, the individual client elements will be duplicated as well.
 *
 * Results:
 *	The new Lst structure or NILLST if failure.
 *
 * Side Effects:
 *	A new list is created.
 *-----------------------------------------------------------------------
 */
Lst
Lst_Duplicate (l, copyProc)
    Lst     	  l;	    	 /* the list to duplicate */
D 5
    ClientData	  (*copyProc)(); /* A function to duplicate each ClientData */
E 5
I 5
    /* A function to duplicate each ClientData */
    ClientData	  (*copyProc) __P((ClientData));
E 5
{
    register Lst 	nl;
    register ListNode  	ln;
    register List 	list = (List)l;
    
    if (!LstValid (l)) {
	return (NILLST);
    }

    nl = Lst_Init (list->isCirc);
    if (nl == NILLST) {
	return (NILLST);
    }

    ln = list->firstPtr;
    while (ln != NilListNode) {
	if (copyProc != NOCOPY) {
	    if (Lst_AtEnd (nl, (*copyProc) (ln->datum)) == FAILURE) {
		return (NILLST);
	    }
	} else if (Lst_AtEnd (nl, ln->datum) == FAILURE) {
	    return (NILLST);
	}

	if (list->isCirc && ln == list->lastPtr) {
	    ln = NilListNode;
	} else {
	    ln = ln->nextPtr;
	}
    }
	
    return (nl);
}
E 1
