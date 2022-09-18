h20348
s 00002/00002/00039
d D 8.1 93/06/04 13:09:24 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00026/00007
d D 5.3 91/01/20 21:28:40 bostic 5 4
c new stdio
e
s 00002/00002/00031
d D 5.2 86/03/09 20:53:31 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00029
d D 5.1 85/06/05 13:42:06 mckusick 3 2
c Add copyright
e
s 00001/00000/00029
d D 4.2 82/10/05 22:44:05 mckusick 2 1
c utilize st_blksize field to optimize size of reads and writes
e
s 00029/00000/00000
d D 4.1 80/12/21 16:50:54 wnj 1 0
c date and time created 80/12/21 16:50:54 by wnj
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

E 5
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4

E 3
D 5
#include	<stdio.h>
E 5
I 5
#include <stdio.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 5

D 5
scanf(fmt, args)
char *fmt;
E 5
I 5
#if __STDC__
scanf(char const *fmt, ...)
#else
scanf(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 5
{
D 5
	return(_doscan(stdin, fmt, &args));
}
E 5
I 5
	int ret;
	va_list ap;
E 5

D 5
fscanf(iop, fmt, args)
FILE *iop;
char *fmt;
{
	return(_doscan(iop, fmt, &args));
}

sscanf(str, fmt, args)
register char *str;
char *fmt;
{
	FILE _strbuf;

	_strbuf._flag = _IOREAD|_IOSTRG;
	_strbuf._ptr = _strbuf._base = str;
	_strbuf._cnt = 0;
	while (*str++)
		_strbuf._cnt++;
I 2
	_strbuf._bufsiz = _strbuf._cnt;
E 2
	return(_doscan(&_strbuf, fmt, &args));
E 5
I 5
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	ret = __svfscanf(stdin, fmt, ap);
	va_end(ap);
	return (ret);
E 5
}
E 1
