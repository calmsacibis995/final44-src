h39150
s 00004/00002/00014
d D 7.2 92/06/21 10:33:13 bostic 2 1
c add the rest of the routines to libkern.h; use it in kernel source
e
s 00016/00000/00000
d D 7.1 92/06/20 16:34:47 bostic 1 0
c date and time created 92/06/20 16:34:47 by bostic
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
unsigned int
E 2
I 2
#include "libkern.h"

u_int
E 2
max(a, b)
D 2
	unsigned int a, b;
E 2
I 2
	u_int a, b;
E 2
{

	return (a > b ? a : b);
}
E 1
