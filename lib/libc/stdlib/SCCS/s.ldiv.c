h27798
s 00002/00002/00030
d D 8.1 93/06/04 13:07:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00029
d D 5.2 91/04/16 19:58:36 torek 2 1
c my previous version was wrong; this one is right
e
s 00042/00000/00000
d D 5.1 90/05/16 13:01:54 bostic 1 0
c date and time created 90/05/16 13:01:54 by bostic
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

#include <stdlib.h>		/* ldiv_t */

D 2
/*
 * I AM NOT SURE THIS IS COMPLETELY PORTABLE
 * (or that it is even right)
 */
E 2
ldiv_t
ldiv(num, denom)
	long num, denom;
{
	ldiv_t r;

	/* see div.c for comments */

D 2
	if (num > 0 && denom < 0) {
		num = -num;
		denom = -denom;
	}
E 2
	r.quot = num / denom;
	r.rem = num % denom;
D 2
	if (num < 0 && denom > 0) {
		if (r.rem > 0) {
			r.quot++;
			r.rem -= denom;
		}
E 2
I 2
	if (num >= 0 && r.rem < 0) {
		r.quot++;
		r.rem -= denom;
E 2
	}
	return (r);
}
E 1
