h60200
s 00024/00017/00028
d D 5.2 90/03/11 17:03:17 bostic 2 1
c add Berkeley specific copyright notice
e
s 00045/00000/00000
d D 5.1 90/03/11 16:53:59 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * lstLength.c --
 *	Find the length of a lst
E 2
I 2
/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
E 2
 *
D 2
 * Copyright (c) 1988 by the Regents of the University of California
 * Copyright (c) 1988 by Adam de Boor
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
"$Id: lstLength.c,v 1.2 88/11/17 20:53:27 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * lstLength.c --
 *	Find the length of a lst
 */
E 2

#include    "lstInt.h"

int
Lst_Length(l)
    Lst	    l;	  /* List whose length is desired */
{
    register ListNode 	node;
    register List 	list = (List)l;
    register int  	len;

    if (!LstValid(l)) {
	return -1;
    }

    for (len = 0, node = list->firstPtr;
	 node != NilListNode;
	 len++, node = node->nextPtr) {
	if (node == list->firstPtr && len != 0) {
	    break;
	}
    }
    return len;
}
E 1
