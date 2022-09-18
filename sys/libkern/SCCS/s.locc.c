h38573
s 00002/00002/00022
d D 8.1 93/06/10 22:07:46 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00023
d D 7.4 92/10/11 10:50:48 bostic 4 3
c make kernel includes standard
e
s 00005/00003/00019
d D 7.3 92/06/21 10:33:12 bostic 3 2
c add the rest of the routines to libkern.h; use it in kernel source
e
s 00006/00004/00016
d D 7.2 92/06/21 01:33:39 torek 2 1
c get the types right, and get the parameters to locc in the right order!
e
s 00020/00000/00000
d D 7.1 92/06/20 16:34:45 bostic 1 0
c date and time created 92/06/20 16:34:45 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 3
D 4
#include "libkern.h"
E 4
I 4
#include <libkern/libkern.h>
E 4

E 3
int
D 2
locc(mask, size, cp)
	register unsigned char mask;
E 2
I 2
locc(mask0, cp0, size)
	int mask0;
	char *cp0;
E 2
D 3
	unsigned int size;
E 3
I 3
	u_int size;
E 3
D 2
	register unsigned char *cp;
E 2
{
D 2
	register unsigned char *end;
E 2
I 2
D 3
	register unsigned char *cp, *end, mask;
E 3
I 3
	register u_char *cp, *end, mask;
E 3
E 2

I 2
	mask = mask0;
D 3
	cp = (unsigned char *)cp0;
E 3
I 3
	cp = (u_char *)cp0;
E 3
E 2
	for (end = &cp[size]; cp < end && *cp != mask; ++cp);
	return (end - cp);
}
E 1
