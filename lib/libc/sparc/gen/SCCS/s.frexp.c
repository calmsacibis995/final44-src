h47066
s 00002/00002/00050
d D 8.1 93/06/04 13:01:19 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00052/00000/00000
d D 5.1 92/06/25 06:16:59 torek 1 0
c date and time created 92/06/25 06:16:59 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: frexp.c,v 1.1 91/07/07 04:45:01 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <machine/ieee.h>

/*
 * Split the given value into a fraction in the range [0.5, 1.0) and
 * an exponent, such that frac * (2^exp) == value.  If value is 0,
 * return 0.
 */
double
frexp(value, eptr)
	double value;
	int *eptr;
{
	union {
                double v;
		struct ieee_double s;
	} u;

	if (value) {
		/*
		 * Fractions in [0.5..1.0) have an exponent of 2^-1.
		 * Leave Inf and NaN alone, however.
		 * WHAT ABOUT DENORMS?
		 */
		u.v = value;
		if (u.s.dbl_exp != DBL_EXP_INFNAN) {
			*eptr = u.s.dbl_exp - (DBL_EXP_BIAS - 1);
			u.s.dbl_exp = DBL_EXP_BIAS - 1;
		}
		return (u.v);
	} else {
		*eptr = 0;
		return ((double)0);
	}
}
E 1
