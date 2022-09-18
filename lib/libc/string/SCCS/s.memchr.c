h41031
s 00002/00002/00031
d D 8.1 93/06/04 15:10:41 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00032
d D 5.6 91/01/26 15:31:50 bostic 6 5
c stdc.h -> cdefs.h
e
s 00022/00020/00011
d D 5.5 90/05/15 14:07:06 bostic 5 4
c ANSI C version from Chris Torek
e
s 00010/00005/00021
d D 5.4 88/06/27 18:25:34 bostic 4 3
c install approved copyright notice
e
s 00010/00008/00016
d D 5.3 88/05/25 14:23:52 bostic 3 2
c written by Robert Elz; add Berkeley specific header
e
s 00001/00001/00023
d D 5.2 86/03/09 19:33:58 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00024/00000/00000
d D 5.1 85/08/05 21:43:13 kre 1 0
c date and time created 85/08/05 21:43:13 by kre
e
u
U
t
T
I 1
D 5
/*
 * Copyright (c) 1985 Regents of the University of California.
E 5
I 5
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
E 5
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 5
E 4
E 3
 */

D 3
/*
 * Sys5 compat routine
 */

E 3
D 2
#ifndef lint
E 2
I 2
#if defined(LIBC_SCCS) && !defined(lint)
E 2
D 3
static char sccsid[] = "%W% (Berkeley) %E%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */
E 3

I 6
#include <sys/cdefs.h>
E 6
D 5
char *
E 5
I 5
#include <string.h>
D 6
#include <sys/stdc.h>
E 6

void *
E 5
memchr(s, c, n)
D 5
	register char *s;
	register c, n;
E 5
I 5
	const void *s;
	register unsigned char c;
	register size_t n;
E 5
{
D 5
	while (--n >= 0)
		if (*s++ == c)
			return (--s);
	return (0);
E 5
I 5
	if (n != 0) {
		register const unsigned char *p = s;

		do {
			if (*p++ == c)
				return ((void *)(p - 1));
		} while (--n != 0);
	}
	return (NULL);
E 5
}
E 1
