h52477
s 00002/00002/00079
d D 8.1 93/06/04 13:09:03 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00080
d D 5.4 93/03/23 11:36:58 torek 4 3
c shut gcc2 up
e
s 00004/00003/00077
d D 5.3 91/02/23 22:56:44 donn 3 2
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00001/00000/00079
d D 5.2 90/05/17 11:57:24 bostic 2 1
c might as well keep header and source in sync
e
s 00079/00000/00000
d D 5.1 90/05/16 11:30:33 bostic 1 0
c date and time created 90/05/16 11:30:33 by bostic
c new version from Sprite via Chris Torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <limits.h>
#include <ctype.h>
#include <errno.h>
I 2
#include <stdlib.h>
E 2

/*
 * Convert a string to an unsigned long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
unsigned long
strtoul(nptr, endptr, base)
D 3
	char *nptr, **endptr;
E 3
I 3
	const char *nptr;
	char **endptr;
E 3
	register int base;
{
D 3
	register char *s = nptr;
E 3
I 3
	register const char *s = nptr;
E 3
	register unsigned long acc;
	register int c;
	register unsigned long cutoff;
	register int neg = 0, any, cutlim;

	/*
	 * See strtol for comments as to the logic used.
	 */
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;
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
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = ULONG_MAX;
		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
D 3
		*endptr = any ? s - 1 : nptr;
E 3
I 3
D 4
		*endptr = any ? s - 1 : (char *)nptr;
E 4
I 4
		*endptr = (char *)(any ? s - 1 : nptr);
E 4
E 3
	return (acc);
}
E 1
