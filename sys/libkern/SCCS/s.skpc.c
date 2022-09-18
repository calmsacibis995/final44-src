h47268
s 00002/00002/00022
d D 8.1 93/06/10 22:07:38 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00023
d D 7.4 92/10/11 10:50:50 bostic 5 4
c make kernel includes standard
e
s 00004/00002/00020
d D 7.3 92/06/21 10:33:15 bostic 4 3
c add the rest of the routines to libkern.h; use it in kernel source
e
s 00007/00005/00015
d D 7.2 92/06/21 01:38:11 torek 3 1
c get the types right, and get the parameters to locc in the right order!
e
s 00006/00004/00016
d R 7.2 92/06/21 01:33:37 torek 2 1
c get the types right, and get the parameters to locc in the right order!
e
s 00020/00000/00000
d D 7.1 92/06/20 16:34:53 bostic 1 0
c date and time created 92/06/20 16:34:53 by bostic
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
skpc(mask, size, cp)
	register unsigned char mask;
	unsigned int size;
	register unsigned char *cp;
E 3
I 3
skpc(mask0, size, cp0)
	int mask0;
	int size;
	char *cp0;
E 3
{
D 3
	register unsigned char *end;
E 3
I 3
D 4
	register unsigned char *cp, *end, mask;
E 4
I 4
	register u_char *cp, *end, mask;
E 4
E 3

I 3
	mask = mask0;
D 4
	cp = (unsigned char *)cp0;
E 4
I 4
	cp = (u_char *)cp0;
E 4
E 3
	for (end = &cp[size]; cp < end && *cp == mask; ++cp);
	return (end - cp);
}
E 1
