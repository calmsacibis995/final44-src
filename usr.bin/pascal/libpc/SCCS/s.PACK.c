h40666
s 00002/00002/00053
d D 8.1 93/06/06 15:17:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00003/00046
d D 1.4 90/04/09 18:26:53 bostic 4 3
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00002/00048
d D 1.3 81/06/10 00:39:10 mckusic 3 2
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00005/00005/00045
d D 1.2 81/03/07 15:59:07 mckusic 2 1
c merge in onyx changes
e
s 00050/00000/00000
d D 1.1 80/10/30 00:34:07 mckusick 1 0
c date and time created 80/10/30 00:34:07 by mckusick
e
u
U
t
T
I 1
D 4
/* Copyright (c) 1979 Regents of the University of California */
E 4
I 4
/*-
D 5
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */
E 4

D 4
static char sccsid[] = "%Z%%M% %I% %G%";

E 4
I 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4
D 3
#include "h01errs.h"
E 3

/*
 * pack(a,i,z)
 *
 * with:	a: array[m..n] of t
 *	z: packed array[u..v] of t
 *
 * semantics:	for j := u to v do
 *			z[j] := a[j-u+i];
 *
 * need to check:
 *	1. i >= m
 *	2. i+(v-u) <= n		(i.e. i-m <= (n-m)-(v-u))
 *
 * on stack:	lv(z), lv(a), rv(i) (len 4)
 *
 * move w(t)*(v-u+1) bytes from lv(a)+w(t)*(i-m) to lv(z)
 */

PACK(i, a, z, size_a, lb_a, ub_a, size_z)

D 2
	int	i;	/* subscript into a to begin packing */
E 2
I 2
	long	i;	/* subscript into a to begin packing */
E 2
	char	*a;	/* pointer to structure a */
	char	*z;	/* pointer to structure z */
D 2
	int	size_a;	/* sizeof(a_type) */
	int	lb_a;	/* lower bound of structure a */
	int	ub_a;	/* (upper bound of a) - (lb_a + sizeof(z_type)) */
	int	size_z;	/* sizeof(z_type) */
E 2
I 2
	long	size_a;	/* sizeof(a_type) */
	long	lb_a;	/* lower bound of structure a */
	long	ub_a;	/* (upper bound of a) - (lb_a + sizeof(z_type)) */
	long	size_z;	/* sizeof(z_type) */
E 2
{
	int		subscr;
	register char	*cp;
	register char	*zp = z;
	register char	*limit;

	subscr = i - lb_a;
	if (subscr < 0 || subscr > ub_a) {
D 3
		ERROR(EPACK, i);
E 3
I 3
		ERROR("i = %D: Bad i to pack(a,i,z)\n", i);
E 3
		return;
	}
	cp = &a[subscr * size_a];
	limit = cp + size_z;
	do	{
		*zp++ = *cp++;
	} while (cp < limit);
}
E 1
