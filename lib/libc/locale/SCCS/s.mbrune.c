h32795
s 00002/00002/00084
d D 8.1 93/06/27 19:22:35 bostic 3 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00084
d R 8.1 93/06/04 12:43:15 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00086/00000/00000
d D 5.1 93/05/26 20:28:32 bostic 1 0
c rune support from Paul Borman
c date and time created 93/05/26 20:28:32 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <limits.h>
#include <rune.h>
#include <stddef.h>
#include <string.h>

char *
mbrune(string, c)
	const char *string;
	rune_t c;
{
	char const *result;
	rune_t r;

	while ((r = sgetrune(string, MB_LEN_MAX, &result))) {
		if (r == c)
			return ((char *)string);
		string = result == string ? string + 1 : result;
	}

	return (c == *string ? (char *)string : NULL);
}

char *
mbrrune(string, c)
	const char *string;
	rune_t c;
{
	const char *last = 0;
	char const *result;
	rune_t  r;

	while ((r = sgetrune(string, MB_LEN_MAX, &result))) {
		if (r == c)
			last = string;
		string = result == string ? string + 1 : result;
	}
	return (c == *string ? (char *)string : (char *)last);
}

char *
mbmb(string, pattern)
	const char *string;
	char *pattern;
{
	rune_t first, r;
	size_t plen, slen;
	char const *result;

	plen = strlen(pattern);
	slen = strlen(string);
	if (plen > slen)
		return (0);

	first = sgetrune(pattern, plen, &result);
	if (result == string)
		return (0);

	while (slen >= plen && (r = sgetrune(string, slen, &result))) {
		if (r == first) {
			if (strncmp(string, pattern, slen) == 0)
				return ((char *) string);
		}
		if (result == string) {
			--slen;
			++string;
		} else {
			slen -= result - string;
			string = result;
		}
	}
	return (0);
}
E 1
