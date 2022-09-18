h22182
s 00002/00002/00037
d D 8.1 93/06/04 15:12:48 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00038
d D 5.2 91/01/26 15:32:09 bostic 2 1
c stdc.h -> cdefs.h
e
s 00039/00000/00000
d D 5.1 90/05/15 14:56:09 bostic 1 0
c date and time created 90/05/15 14:56:09 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
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

I 2
#include <sys/cdefs.h>
E 2
#include <string.h>
D 2
#include <sys/stdc.h>
E 2

/*
 * Find the first occurrence of find in s.
 */
char *
strstr(s, find)
	register const char *s, *find;
{
	register char c, sc;
	register size_t len;

	if ((c = *find++) != 0) {
		len = strlen(find);
		do {
			do {
				if ((sc = *s++) == 0)
					return (NULL);
			} while (sc != c);
		} while (strncmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}
E 1
