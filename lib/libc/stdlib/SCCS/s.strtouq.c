h24839
s 00002/00002/00086
d D 8.1 93/06/04 13:09:07 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00087
d D 5.2 93/03/23 11:37:00 torek 2 1
c shut gcc2 up
e
s 00088/00000/00000
d D 5.1 92/06/26 06:55:56 bostic 1 0
c date and time created 92/06/26 06:55:56 by bostic
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
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>

#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>

/*
 * Convert a string to an unsigned quad integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
u_quad_t
strtouq(nptr, endptr, base)
	const char *nptr;
	char **endptr;
	register int base;
{
	register const char *s = nptr;
	register u_quad_t acc;
	register int c;
	register u_quad_t qbase, cutoff;
	register int neg, any, cutlim;

	/*
	 * See strtoq for comments as to the logic used.
	 */
	s = nptr;
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else { 
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	qbase = (unsigned)base;
	cutoff = (u_quad_t)UQUAD_MAX / qbase;
	cutlim = (u_quad_t)UQUAD_MAX % qbase;
	for (acc = 0, any = 0;; c = *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
			any = -1;
		else {
			any = 1;
			acc *= qbase;
			acc += c;
		}
	}
	if (any < 0) {
		acc = UQUAD_MAX;
		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
D 2
		*endptr = any ? s - 1 : (char *)nptr;
E 2
I 2
		*endptr = (char *)(any ? s - 1 : nptr);
E 2
	return (acc);
}
E 1
