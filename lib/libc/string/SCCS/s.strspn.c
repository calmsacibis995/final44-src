h05227
s 00002/00002/00033
d D 8.1 93/06/04 15:12:42 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00034
d D 5.8 91/01/26 15:32:08 bostic 8 7
c stdc.h -> cdefs.h
e
s 00001/00011/00034
d D 5.7 90/06/01 14:46:57 bostic 7 6
c new copyright notice
e
s 00021/00016/00024
d D 5.6 90/05/17 15:35:56 bostic 6 5
c use Chris's version, need to return size_t
e
s 00002/00000/00038
d D 5.5 90/05/17 12:05:46 bostic 5 4
c keep string.h and source in sync
e
s 00010/00005/00028
d D 5.4 88/06/27 18:25:47 bostic 4 3
c install approved copyright notice
e
s 00010/00008/00023
d D 5.3 88/05/25 14:24:03 bostic 3 2
c written by Robert Elz; add Berkeley specific header
e
s 00001/00001/00030
d D 5.2 86/03/09 19:36:30 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00031/00000/00000
d D 5.1 85/08/05 21:43:08 kre 1 0
c date and time created 85/08/05 21:43:08 by kre
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1985 Regents of the University of California.
E 6
I 6
D 9
 * Copyright (c) 1989 The Regents of the University of California.
E 6
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
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
D 6
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
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
D 8
#include <sys/stdc.h>
E 8
I 8
#include <sys/cdefs.h>
E 8
E 6
I 5
#include <string.h>

E 5
D 6
strspn(s, set)
	register char *s, *set;
E 6
I 6
/*
 * Span the string s2 (skip characters that are in s2).
 */
size_t
strspn(s1, s2)
	const char *s1;
	register const char *s2;
E 6
{
D 6
	register n = 0;
	register char *p;
	register c;
E 6
I 6
	register const char *p = s1, *spanp;
	register char c, sc;
E 6

D 6
	while (c = *s++) {
		for (p = set; *p; p++)
			if (c == *p)
				break;
		if (!*p)
			return (n);
		n++;
	}
	return (n);
E 6
I 6
	/*
	 * Skip any characters in s2, excluding the terminating \0.
	 */
cont:
	c = *p++;
	for (spanp = s2; (sc = *spanp++) != 0;)
		if (sc == c)
			goto cont;
	return (p - 1 - s1);
E 6
}
E 1
