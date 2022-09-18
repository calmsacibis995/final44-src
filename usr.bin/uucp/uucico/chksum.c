/*-
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)chksum.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#ifndef pdp11
chksum (s, n)
register char *s;
register n;
{
	register long sum, x, t;

	sum = 0xffff;
	x = 0;
	do {
		/* Rotate left, copying bit 15 to bit 0 */
		sum <<= 1;
		if (sum & 0x10000)
			sum ^= 0x10001;
		t = sum;
		sum = (sum + (*s++ & 0377)) & 0xffff;
		x += sum ^ n;
		if (sum <= t)
			sum = (sum ^ x) & 0xffff;
	} while (--n > 0);

	return (long) (short) sum;
}
#else pdp11
chksum(s,n)
register char *s;
register n;
{
	register unsigned sum, t;
	register x;

	sum = -1;
	x = 0;

	do {
		if (sum&0x8000) {
			sum <<= 1;
			sum++;
		} else
			sum <<= 1;
		t = sum;
		sum += (unsigned)*s++ & 0377;
		x += sum^n;
		if ((sum&0xffff) <= (t&0xffff)) {
			sum ^= x;
		}
	} while (--n > 0);

	return sum & 0xffff;
}

#endif pdp11
