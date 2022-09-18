h42466
s 00000/00000/00047
d D 8.2 95/04/28 17:21:46 christos 5 4
c upgraded to the latest NetBSD version
e
s 00002/00002/00045
d D 8.1 93/06/06 15:10:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00046
d D 5.3 90/06/01 16:59:08 bostic 3 2
c new copyright notice
e
s 00024/00014/00033
d D 5.2 90/03/11 17:02:56 bostic 2 1
c add Berkeley specific copyright notice
e
s 00047/00000/00000
d D 5.1 90/03/11 16:53:38 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * LstEnQueue.c--
 *	Treat the list as a queue and place a datum at its end
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
"$Id: lstEnQueue.c,v 1.4 88/11/17 20:52:26 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * LstEnQueue.c--
 *	Treat the list as a queue and place a datum at its end
 */
E 2

#include	"lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_EnQueue --
 *	Add the datum to the tail of the given list.
 *
 * Results:
 *	SUCCESS or FAILURE as returned by Lst_Append.
 *
 * Side Effects:
 *	the lastPtr field is altered all the time and the firstPtr field
 *	will be altered if the list used to be empty.
 *
 *-----------------------------------------------------------------------
 */
ReturnStatus
Lst_EnQueue (l, d)
    Lst	    	  l;
    ClientData	  d;
{
    if (LstValid (l) == FALSE) {
	return (FAILURE);
    }
    
    return (Lst_Append (l, Lst_Last(l), d));
}

E 1
