h24881
s 00002/00002/00048
d D 8.1 93/06/04 13:09:38 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00050/00000/00000
d D 5.1 91/01/20 21:34:59 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
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
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#if __STDC__
snprintf(char *str, size_t n, char const *fmt, ...)
#else
snprintf(str, n, fmt, va_alist)
	char *str;
	size_t n;
	char *fmt;
	va_dcl
#endif
{
	int ret;
	va_list ap;
	FILE f;

	if ((int)n < 1)
		return (EOF);
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	f._flags = __SWR | __SSTR;
	f._bf._base = f._p = (unsigned char *)str;
	f._bf._size = f._w = n - 1;
	ret = vfprintf(&f, fmt, ap);
	*f._p = 0;
	va_end(ap);
	return (ret);
}
E 1
