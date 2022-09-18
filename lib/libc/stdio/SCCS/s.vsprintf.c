h30627
s 00002/00002/00030
d D 8.1 93/06/04 13:10:30 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00031
d D 5.6 92/06/23 09:58:30 bostic 6 5
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00001/00001/00031
d D 5.5 91/02/05 00:27:08 torek 5 4
c repair arguments (add const)
e
s 00016/00013/00016
d D 5.4 91/01/20 21:32:33 bostic 4 3
c new stdio
e
s 00001/00011/00028
d D 5.3 90/06/01 14:44:04 bostic 3 2
c new copyright notice
e
s 00010/00005/00029
d D 5.2 88/06/27 17:50:10 bostic 2 1
c install approved copyright notice
e
s 00034/00000/00000
d D 5.1 88/05/24 18:59:05 bostic 1 0
c date and time created 88/05/24 18:59:05 by bostic
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1988 Regents of the University of California.
E 4
I 4
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
E 4
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
I 4
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
E 4
D 3
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>
D 4
#include <varargs.h>
E 4
I 4
#include <limits.h>
E 4

D 4
int
E 4
vsprintf(str, fmt, ap)
D 4
	char *str, *fmt;
	va_list ap;
E 4
I 4
	char *str;
D 5
	char *fmt;
E 5
I 5
	const char *fmt;
E 5
D 6
	_VA_LIST_ ap;
E 6
I 6
	_BSD_VA_LIST_ ap;
E 6
E 4
{
I 4
	int ret;
E 4
	FILE f;
D 4
	int len;
E 4

D 4
	f._flag = _IOWRT+_IOSTRG;
	f._ptr = str;
	f._cnt = 32767;
	len = _doprnt(fmt, ap, &f);
	*f._ptr = 0;
	return (len);
E 4
I 4
	f._flags = __SWR | __SSTR;
	f._bf._base = f._p = (unsigned char *)str;
	f._bf._size = f._w = INT_MAX;
	ret = vfprintf(&f, fmt, ap);
	*f._p = 0;
	return (ret);
E 4
}
E 1
