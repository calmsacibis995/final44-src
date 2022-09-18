h40873
s 00002/00002/00061
d D 8.1 93/06/06 22:12:46 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00055
d D 4.3 91/04/24 17:42:46 bostic 3 2
c new copyright; att/bsd/shared
e
s 00030/00001/00026
d D 4.2 85/06/19 17:46:08 bloom 2 1
c fix from rick adams
e
s 00027/00000/00000
d D 4.1 85/01/22 13:49:21 ralph 1 0
c date and time created 85/01/22 13:49:21 by ralph
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
#endif /* not lint */
E 3

D 2
long
E 2
I 2
#ifndef pdp11
E 2
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
I 2
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
E 2
E 1
