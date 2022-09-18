h26244
s 00002/00002/00035
d D 8.1 93/06/10 22:07:40 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00036
d D 7.2 92/10/11 10:50:48 bostic 2 1
c make kernel includes standard
e
s 00037/00000/00000
d D 7.1 92/06/24 01:08:54 torek 1 0
c date and time created 92/06/24 01:08:54 by torek
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "libkern.h"
E 2
I 2
#include <libkern/libkern.h>
E 2

/*
 * Pseudo-random number generator for randomizing the profiling clock,
 * and whatever else we might use it for.  The result is uniform on
 * [0, 2^31 - 1].
 */
u_long
random()
{
	static u_long randseed = 1;
	register long x, hi, lo, t;

	/*
	 * Compute x[n + 1] = (7^5 * x[n]) mod (2^31 - 1).
	 * From "Random number generators: good ones are hard to find",
	 * Park and Miller, Communications of the ACM, vol. 31, no. 10,
	 * October 1988, p. 1195.
	 */
	x = randseed;
	hi = x / 127773;
	lo = x % 127773;
	t = 16807 * lo - 2836 * hi;
	if (t <= 0)
		t += 0x7fffffff;
	randseed = t;
	return (t);
}
E 1
