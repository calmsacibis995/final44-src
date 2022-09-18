h25710
s 00002/00002/00032
d D 8.1 93/06/04 13:10:28 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00033
d D 5.3 92/06/23 09:58:29 bostic 3 2
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00001/00001/00033
d D 5.2 91/02/05 00:26:41 torek 2 1
c repair arguments (add const)
e
s 00034/00000/00000
d D 5.1 91/01/20 21:35:03 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>

vsnprintf(str, n, fmt, ap)
	char *str;
	size_t n;
D 2
	char *fmt;
E 2
I 2
	const char *fmt;
E 2
D 3
	_VA_LIST_ ap;
E 3
I 3
	_BSD_VA_LIST_ ap;
E 3
{
	int ret;
	FILE f;

	if ((int)n < 1)
		return (EOF);
	f._flags = __SWR | __SSTR;
	f._bf._base = f._p = (unsigned char *)str;
	f._bf._size = f._w = n - 1;
	ret = vfprintf(&f, fmt, ap);
	*f._p = 0;
	return (ret);
}
E 1
