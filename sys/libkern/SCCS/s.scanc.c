h49583
s 00002/00002/00022
d D 8.1 93/06/10 22:07:43 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00023
d D 7.4 92/10/11 10:50:49 bostic 5 4
c make kernel includes standard
e
s 00006/00004/00018
d D 7.3 92/06/21 10:33:14 bostic 4 3
c add the rest of the routines to libkern.h; use it in kernel source
e
s 00004/00002/00018
d D 7.2 92/06/21 01:37:17 torek 3 1
c get the types right, and get the parameters to locc in the right order!
e
s 00003/00001/00019
d R 7.2 92/06/21 01:33:38 torek 2 1
c get the types right, and get the parameters to locc in the right order!
e
s 00020/00000/00000
d D 7.1 92/06/20 16:34:51 bostic 1 0
c date and time created 92/06/20 16:34:51 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 4
D 5
#include "libkern.h"
E 5
I 5
#include <libkern/libkern.h>
E 5

E 4
int
D 3
scanc(size, cp, table, mask)
E 3
I 3
scanc(size, cp, table, mask0)
E 3
D 4
	unsigned int size;
	register unsigned char *cp, table[];
E 4
I 4
	u_int size;
	register u_char *cp, table[];
E 4
D 3
	register unsigned char mask;
E 3
I 3
	int mask0;
E 3
{
D 4
	register unsigned char *end;
I 3
	register unsigned char mask;
E 4
I 4
	register u_char *end;
	register u_char mask;
E 4
E 3

I 3
	mask = mask0;
E 3
	for (end = &cp[size]; cp < end && (table[*cp] & mask) == 0; ++cp);
	return (end - cp);
}
E 1
