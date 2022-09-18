h39780
s 00004/00002/00014
d D 7.2 92/06/21 10:33:16 bostic 2 1
c add the rest of the routines to libkern.h; use it in kernel source
e
s 00016/00000/00000
d D 7.1 92/06/20 16:34:55 bostic 1 0
c date and time created 92/06/20 16:34:55 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
unsigned long
E 2
I 2
#include "libkern.h"

u_long
E 2
ulmax(a, b)
D 2
	unsigned long a, b;
E 2
I 2
	u_long a, b;
E 2
{

	return (a > b ? a : b);
}
E 1
