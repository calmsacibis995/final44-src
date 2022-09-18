h35211
s 00002/00000/00016
d D 7.2 92/06/21 10:33:11 bostic 2 1
c add the rest of the routines to libkern.h; use it in kernel source
e
s 00016/00000/00000
d D 7.1 92/06/20 16:34:43 bostic 1 0
c date and time created 92/06/20 16:34:43 by bostic
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

I 2
#include "libkern.h"

E 2
long
lmax(a, b)
	long a, b;
{

	return (a > b ? a : b);
}
E 1
