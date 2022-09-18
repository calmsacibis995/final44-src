h54864
s 00002/00002/00051
d D 8.1 93/06/04 13:05:52 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00020/00027
d D 5.2 91/04/16 19:58:35 torek 2 1
c my previous version was wrong; this one is right
e
s 00044/00000/00000
d D 5.1 90/05/16 12:52:07 bostic 1 0
c date and time created 90/05/16 12:52:07 by bostic
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdlib.h>		/* div_t */

D 2
/*
 * I AM NOT SURE THIS IS COMPLETELY PORTABLE
 * (or that it is even right)
 */
E 2
div_t
div(num, denom)
	int num, denom;
{
	div_t r;

D 2
	/* avoid deep thought */
	if (num > 0 && denom < 0) {
		num = -num;
		denom = -denom;
	}
E 2
	r.quot = num / denom;
	r.rem = num % denom;
D 2
	if (num < 0 && denom > 0) {
		/*
		 * Machine division and remainer may work either way.  The
		 * ANSI standard says that |r.quot| < |n/d| (where n/d
		 * computed in infinite precision).  If the remainder is
		 * positive, we got the `wrong' answer, so fix it.
		 */
		if (r.rem > 0) {
			r.quot++;
			r.rem -= denom;
		}
E 2
I 2
	/*
	 * The ANSI standard says that |r.quot| <= |n/d|, where
	 * n/d is to be computed in infinite precision.  In other
	 * words, we should always truncate the quotient towards
	 * 0, never -infinity.
	 *
	 * Machine division and remainer may work either way when
	 * one or both of n or d is negative.  If only one is
	 * negative and r.quot has been truncated towards -inf,
	 * r.rem will have the same sign as denom and the opposite
	 * sign of num; if both are negative and r.quot has been
	 * truncated towards -inf, r.rem will be positive (will
	 * have the opposite sign of num).  These are considered
	 * `wrong'.
	 *
	 * If both are num and denom are positive, r will always
	 * be positive.
	 *
	 * This all boils down to:
	 *	if num >= 0, but r.rem < 0, we got the wrong answer.
	 * In that case, to get the right answer, add 1 to r.quot and
	 * subtract denom from r.rem.
	 */
	if (num >= 0 && r.rem < 0) {
		r.quot++;
		r.rem -= denom;
E 2
	}
	return (r);
}
E 1
