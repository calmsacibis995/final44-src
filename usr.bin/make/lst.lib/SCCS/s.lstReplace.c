h34432
s 00000/00000/00047
d D 8.2 95/04/28 17:21:59 christos 5 4
c upgraded to the latest NetBSD version
e
s 00002/00002/00045
d D 8.1 93/06/06 15:11:38 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00046
d D 5.3 90/06/01 17:01:15 bostic 3 2
c new copyright notice
e
s 00024/00014/00033
d D 5.2 90/03/11 17:03:28 bostic 2 1
c add Berkeley specific copyright notice
e
s 00047/00000/00000
d D 5.1 90/03/11 16:54:13 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * LstReplace.c --
 *	Replace the datum in a node with a new datum
E 2
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
 */
I 2

E 2
#ifndef lint
D 2
static char *rcsid =
"$Id: lstReplace.c,v 1.4 88/11/17 20:54:01 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * LstReplace.c --
 *	Replace the datum in a node with a new datum
 */
E 2

#include	"lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_Replace --
 *	Replace the datum in the given node with the new datum
 *
 * Results:
 *	SUCCESS or FAILURE.
 *
 * Side Effects:
 *	The datum field fo the node is altered.
 *
 *-----------------------------------------------------------------------
 */
ReturnStatus
Lst_Replace (ln, d)
    register LstNode	ln;
    ClientData	  	d;
{
    if (ln == NILLNODE) {
	return (FAILURE);
    } else {
	((ListNode) ln)->datum = d;
	return (SUCCESS);
    }
}

E 1
