h33484
s 00002/00002/00042
d D 8.1 93/06/04 13:10:33 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00043
d D 5.2 92/06/23 09:58:31 bostic 2 1
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00044/00000/00000
d D 5.1 91/04/15 11:47:41 donn 1 0
c date and time created 91/04/15 11:47:41 by donn
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
 * Donn Seeley at UUNET Technologies, Inc.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>
#include <string.h>

/* ARGSUSED */
static int
eofread(cookie, buf, len)
	void *cookie;
	char *buf;
	int len;
{

	return (0);
}

vsscanf(str, fmt, ap)
	const char *str;
	const char *fmt;
D 2
	_VA_LIST_ ap;
E 2
I 2
	_BSD_VA_LIST_ ap;
E 2
{
	int ret;
	FILE f;

	f._flags = __SRD;
	f._bf._base = f._p = (unsigned char *)str;
	f._bf._size = f._r = strlen(str);
	f._read = eofread;
	f._ub._base = NULL;
	f._lb._base = NULL;
	return (__svfscanf(&f, fmt, ap));
}
E 1
