/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)pow_ri.c	5.5 (Berkeley) 4/12/91";
#endif /* not lint */

#ifdef tahoe
#define	double	float
#endif /* tahoe */

float
pow_ri(ap, bp)
	float *ap;
	long *bp;
{
	register long n = *bp;
#ifdef tahoe
	register
#endif /* tahoe */
	double y, x = *ap;

	if (!n)
		return((double)1);
	if (n < 0) {
		x = (double)1 / x;
		n = -n;
	}
	while (!(n&1)) {
		x *= x;
		n >>= 1;
	}
	for (y = x; --n > 0; y *= x)
		while (!(n&1)) {
			x *= x;
			n >>= 1;
		}
	return(y);
}
#ifdef tahoe
#undef double
#endif /* tahoe */
