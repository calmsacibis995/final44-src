h63388
s 00002/00002/00040
d D 8.1 93/06/04 15:11:42 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00041
d D 5.6 91/01/26 15:31:58 bostic 6 5
c stdc.h -> cdefs.h
e
s 00031/00027/00011
d D 5.5 90/05/16 18:37:18 bostic 5 4
c ANSI version
e
s 00010/00005/00028
d D 5.4 88/06/27 18:25:41 bostic 4 3
c install approved copyright notice
e
s 00010/00008/00023
d D 5.3 88/05/25 14:23:59 bostic 3 2
c written by Robert Elz; add Berkeley specific header
e
s 00001/00001/00030
d D 5.2 86/03/09 19:35:52 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00031/00000/00000
d D 5.1 85/08/05 21:43:10 kre 1 0
c date and time created 85/08/05 21:43:10 by kre
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

D 5
strcspn(s, set)
	register char *s, *set;
E 5
I 5
D 6
#include <sys/stdc.h>
E 6
I 6
#include <sys/cdefs.h>
E 6
#include <string.h>

/*
 * Span the complement of string s2.
 */
size_t
strcspn(s1, s2)
	const char *s1;
	register const char *s2;
E 5
{
D 5
	register n = 0;
	register char *p;
	register c;
E 5
I 5
	register const char *p, *spanp;
	register char c, sc;
E 5

D 5
	while (c = *s++) {
		for (p = set; *p; p++)
			if (c == *p)
				break;
		if (*p)
			return (n);
		n++;
	}
	return (n);
E 5
I 5
	/*
	 * Stop as soon as we find any character from s2.  Note that there
	 * must be a NUL in s2; it suffices to stop when we find that, too.
	 */
	for (p = s1;;) {
		c = *p++;
		spanp = s2;
		do {
			if ((sc = *spanp++) == c)
				return (p - 1 - s1);
		} while (sc != 0);
	}
	/* NOTREACHED */
E 5
}
E 1
