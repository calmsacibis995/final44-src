h45324
s 00002/00002/00011
d D 8.1 93/06/04 15:25:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00000/00000
d D 5.1 91/09/11 16:29:28 bostic 1 0
c date and time created 91/09/11 16:29:28 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

enum SRCHOP { SDELETE, SINSERT, SEARCH};	/* Rec_search operation. */

#include "../btree/btree.h"
#include "extern.h"
E 1
