h43105
s 00001/00000/00110
d D 8.2 95/05/04 18:00:01 christos 4 3
c 
e
s 00002/00002/00108
d D 8.1 93/05/31 15:20:01 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00046/00102
d D 5.2 92/06/23 18:05:31 marc 2 1
c cleanup.  remove unneeded routines
e
s 00148/00000/00000
d D 5.1 91/03/07 20:27:47 bostic 1 0
c date and time created 91/03/07 20:27:47 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * String functions.
 *
 *	equal(s1, s2)		Return true if strings are equal.
 *	scopy(from, to)		Copy a string.
 *	scopyn(from, to, n)	Like scopy, but checks for overflow.
D 2
 *	strchr(s, c)		Find first occurance of c in s.
 *	bcopy(from, to, n)	Copy a block of memory.
E 2
 *	number(s)		Convert a string of digits to an integer.
 *	is_number(s)		Return true if s is a string of digits.
 */

I 4
#include <stdlib.h>
E 4
#include "shell.h"
#include "syntax.h"
#include "error.h"
#include "mystring.h"


char nullstr[1];		/* zero length string */

I 2
/*
 * equal - #defined in mystring.h
 */
E 2

/*
I 2
 * scopy - #defined in mystring.h
 */


/*
E 2
 * scopyn - copy a string from "from" to "to", truncating the string
 *		if necessary.  "To" is always nul terminated, even if
 *		truncation is performed.  "Size" is the size of "to".
 */

void
scopyn(from, to, size)
	register char const *from;
	register char *to;
	register int size;
	{

	while (--size > 0) {
		if ((*to++ = *from++) == '\0')
			return;
	}
	*to = '\0';
D 2
}


/*
 * strchr - find first occurrence of a character in a string.
 */

#ifndef SYS5
char *
mystrchr(s, charwanted)
	char const *s;
	register char charwanted;
	{
	register char const *scan;

	/*
	 * The odd placement of the two tests is so NUL is findable.
	 */
	for (scan = s ; *scan != charwanted ; )	/* ++ moved down for opt. */
		if (*scan++ == '\0')
			return NULL;
	return (char *)scan;
}
#endif



/*
 * bcopy - copy bytes
 *
 * This routine was derived from code by Henry Spencer.
 */

void
mybcopy(src, dst, length)
	pointer dst;
	const pointer src;
	register int length;
	{
	register char *d = dst;
	register char *s = src;

	while (--length >= 0)
		*d++ = *s++;
E 2
}


/*
 * prefix -- see if pfx is a prefix of string.
 */

int
prefix(pfx, string)
	register char const *pfx;
	register char const *string;
	{
	while (*pfx) {
		if (*pfx++ != *string++)
			return 0;
	}
	return 1;
}


/*
 * Convert a string of digits to an integer, printing an error message on
 * failure.
 */

int
number(s)
	const char *s;
	{

	if (! is_number(s))
		error2("Illegal number", (char *)s);
	return atoi(s);
}



/*
 * Check for a valid number.  This should be elsewhere.
 */

int
is_number(p)
	register const char *p;
	{
	do {
		if (! is_digit(*p))
			return 0;
	} while (*++p != '\0');
	return 1;
}
E 1
