h40094
s 00002/00002/00033
d D 8.1 93/06/04 15:10:47 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00034
d D 5.6 91/01/26 15:31:51 bostic 6 5
c stdc.h -> cdefs.h
e
s 00024/00018/00012
d D 5.5 90/05/15 14:09:43 bostic 5 4
c ANSI C version from Chris Torek
e
s 00010/00005/00020
d D 5.4 88/06/27 18:25:36 bostic 4 3
c install approved copyright notice
e
s 00010/00008/00015
d D 5.3 88/05/25 14:23:54 bostic 3 2
c written by Robert Elz; add Berkeley specific header
e
s 00001/00001/00022
d D 5.2 86/03/09 19:34:14 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00023/00000/00000
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
I 5
#include <string.h>
D 6
#include <sys/stdc.h>
E 6

/*
 * Compare memory regions.
 */
int
E 5
memcmp(s1, s2, n)
D 5
	register char *s1, *s2;
	register n;
E 5
I 5
	const void *s1, *s2;
	size_t n;
E 5
{
D 5
	while (--n >= 0)
		if (*s1++ != *s2++)
			return (*--s1 - *--s2);
E 5
I 5
	if (n != 0) {
		register const unsigned char *p1 = s1, *p2 = s2;

		do {
			if (*p1++ != *p2++)
				return (*--p1 - *--p2);
		} while (--n != 0);
	}
E 5
	return (0);
}
E 1
