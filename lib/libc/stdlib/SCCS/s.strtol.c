h18811
s 00002/00002/00101
d D 8.1 93/06/04 13:08:47 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00102
d D 5.5 93/03/23 11:35:06 torek 6 4
c shut gcc2 up
e
s 00001/00001/00102
d R 5.5 92/03/07 09:17:24 ralph 5 4
c avoid arithmetic overflow in constant expression.
e
s 00004/00003/00099
d D 5.4 91/02/23 22:56:43 donn 4 3
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00002/00000/00100
d D 5.3 90/05/17 11:57:22 bostic 3 2
c might as well keep header and source in sync
e
s 00075/00057/00025
d D 5.2 90/05/16 11:23:44 bostic 2 1
c new version from Sprite via Chris Torek
e
s 00082/00000/00000
d D 5.1 88/07/23 16:25:40 bostic 1 0
c date and time created 88/07/23 16:25:40 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1988 Regents of the University of California.
E 2
I 2
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
E 2
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 2
#include <limits.h>
E 2
#include <ctype.h>
I 2
#include <errno.h>
I 3
#include <stdlib.h>

E 3
E 2

I 2
/*
 * Convert a string to a long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
E 2
long
D 2
strtol(ascii, endp, base)
	register char *ascii;
	char **endp;
E 2
I 2
strtol(nptr, endptr, base)
D 4
	char *nptr, **endptr;
E 4
I 4
	const char *nptr;
	char **endptr;
E 4
E 2
	register int base;
{
D 2
	register long val;
E 2
I 2
D 4
	register char *s = nptr;
E 4
I 4
	register const char *s = nptr;
E 4
	register unsigned long acc;
E 2
	register int c;
D 2
	int negative;
E 2
I 2
	register unsigned long cutoff;
	register int neg = 0, any, cutlim;
E 2

D 2
	for (; isascii(*ascii) && isspace(*ascii); ++ascii);

	negative = 0;
	if (*ascii == '+')
		++ascii;
	else if (*ascii == '-') {
		negative = 1;
		++ascii;
E 2
I 2
	/*
	 * Skip white space and pick up leading +/- sign if any.
	 * If base is 0, allow 0x for hex and 0 for octal, else
	 * assume decimal; if base is already 16, allow 0x.
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
E 2
	}
I 2
	if (base == 0)
		base = c == '0' ? 8 : 10;
E 2

	/*
D 2
	 * ``If base is positive, but not greater than 36, it is used as
	 * the base for the conversion.''
	 *	-- The UNIX System User's Manual, 1986
E 2
I 2
	 * Compute the cutoff value between legal numbers and illegal
	 * numbers.  That is the largest legal value, divided by the
	 * base.  An input number that is greater than this value, if
	 * followed by a legal input character, is too big.  One that
	 * is equal to this value may be valid or not; the limit
	 * between valid and invalid numbers is then based on the last
	 * digit.  For instance, if the range for longs is
	 * [-2147483648..2147483647] and the input base is 10,
	 * cutoff will be set to 214748364 and cutlim to either
	 * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
	 * a value > 214748364, or equal but the next digit is > 7 (or 8),
	 * the number is too big, and we will return a range error.
	 *
	 * Set any if any `digits' consumed; make it negative to indicate
	 * overflow.
E 2
	 */
D 2
	if ((unsigned int)base > 36)
		base = 10;
	else if (base == 0)
		if (*ascii == '0') {
			++ascii;
			if (*ascii == 'X' || *ascii == 'x') {
				++ascii;
				base = 16;
			}
			else
				base = 8;
		}
		else
			base = 10;
	else if (base == 16 && *ascii == '0' &&
	    (*++ascii == 'X' || *ascii == 'x'))
			++ascii;

	for (val = 0; isascii(c = *ascii) && isalnum(c); ++ascii) {
E 2
I 2
	cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
	cutlim = cutoff % (unsigned long)base;
	cutoff /= (unsigned long)base;
	for (acc = 0, any = 0;; c = *s++) {
E 2
		if (isdigit(c))
			c -= '0';
D 2
		else {
			if (isupper(c))
				c = tolower(c);
			c = c - 'a' + 10;
		}
E 2
I 2
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
E 2
		if (c >= base)
			break;
D 2
		val = val * base + c;
E 2
I 2
		if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
E 2
	}
D 2
	if (endp)
		*endp = ascii;
	return(negative ? -val : val);
E 2
I 2
	if (any < 0) {
		acc = neg ? LONG_MIN : LONG_MAX;
		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
D 4
		*endptr = any ? s - 1 : nptr;
E 4
I 4
D 6
		*endptr = any ? s - 1 : (char *)nptr;
E 6
I 6
		*endptr = (char *)(any ? s - 1 : nptr);
E 6
E 4
	return (acc);
E 2
}
E 1
