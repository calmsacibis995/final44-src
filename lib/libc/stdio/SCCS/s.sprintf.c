h39090
s 00002/00002/00047
d D 8.1 93/06/04 13:09:41 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00013/00014
d D 5.7 91/01/20 21:30:14 bostic 10 9
c new stdio
e
s 00001/00011/00026
d D 5.6 90/06/01 14:43:38 bostic 9 8
c new copyright notice
e
s 00010/00005/00027
d D 5.5 88/06/27 17:50:06 bostic 8 7
c install approved copyright notice
e
s 00016/00003/00016
d D 5.4 87/12/12 12:48:42 bostic 7 6
c attach Berkeley header
e
s 00005/00004/00014
d D 5.3 87/10/25 09:48:25 bostic 6 4
c ANSI C; sprintf now returns an int.
e
s 00005/00004/00014
d R 5.3 87/10/22 17:51:52 bostic 5 4
c ANSI C; sprintf now returns an int.
e
s 00002/00002/00016
d D 5.2 86/03/09 20:54:20 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00014
d D 5.1 85/06/05 13:43:27 mckusick 3 2
c Add copyright
e
s 00001/00001/00014
d D 4.2 85/02/13 15:49:14 serge 2 1
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00015/00000/00000
d D 4.1 80/12/21 16:50:57 wnj 1 0
c date and time created 80/12/21 16:50:57 by wnj
e
u
U
t
T
I 7
D 10
/*
 * Copyright (c) 1987 Regents of the University of California.
E 10
I 10
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
E 10
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
I 10
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
E 10
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
 */

E 7
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
D 7
#endif LIBC_SCCS and not lint
E 7
I 7
#endif /* LIBC_SCCS and not lint */
E 7
E 4

E 3
D 7
#include	<stdio.h>
E 7
I 7
#include <stdio.h>
I 10
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <limits.h>
#include "local.h"
E 10
E 7

D 6
char *sprintf(str, fmt, args)
E 6
I 6
D 10
sprintf(str, fmt, args)
E 6
D 7
char *str, *fmt;
E 7
I 7
	char *str, *fmt;
	int args;
E 10
I 10
#if __STDC__
sprintf(char *str, char const *fmt, ...)
#else
sprintf(str, fmt, va_alist)
	char *str;
	char *fmt;
	va_dcl
#endif
E 10
E 7
{
D 2
	struct _iobuf _strbuf;
E 2
I 2
D 10
	FILE _strbuf;
I 6
	int len;
E 10
I 10
	int ret;
	va_list ap;
	FILE f;
E 10
E 6
E 2

D 10
	_strbuf._flag = _IOWRT+_IOSTRG;
	_strbuf._ptr = str;
	_strbuf._cnt = 32767;
D 6
	_doprnt(fmt, &args, &_strbuf);
	putc('\0', &_strbuf);
	return(str);
E 6
I 6
	len = _doprnt(fmt, &args, &_strbuf);
	*_strbuf._ptr = 0;
	return(len);
E 10
I 10
	f._flags = __SWR | __SSTR;
	f._bf._base = f._p = (unsigned char *)str;
	f._bf._size = f._w = INT_MAX;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	ret = vfprintf(&f, fmt, ap);
	va_end(ap);
	*f._p = 0;
	return (ret);
E 10
E 6
}
E 1
