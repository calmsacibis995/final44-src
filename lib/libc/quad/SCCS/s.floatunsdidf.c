h28651
s 00002/00002/00031
d D 8.1 93/06/04 12:56:42 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00031
d D 5.2 92/06/25 09:34:23 bostic 2 1
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00032/00000/00000
d D 5.1 92/06/02 13:39:25 bostic 1 0
c date and time created 92/06/02 13:39:25 by bostic
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
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include "quad.h"

/*
 * Convert (unsigned) quad to double.
 * This is exactly like floatdidf.c except that negatives never occur.
 */
double
D 2
__floatunsdidf(u_quad x)
E 2
I 2
__floatunsdidf(x)
	u_quad_t x;
E 2
{
	double d;
	union uu u;

	u.uq = x;
	d = (double)u.ul[H] * ((1 << (LONG_BITS - 2)) * 4.0);
	d += u.ul[L];
	return (d);
}
E 1
