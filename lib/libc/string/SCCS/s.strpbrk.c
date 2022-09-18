h00247
s 00002/00002/00029
d D 8.1 93/06/04 15:12:29 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00030
d D 5.8 91/01/26 15:32:06 bostic 8 7
c stdc.h -> cdefs.h
e
s 00001/00011/00030
d D 5.7 90/06/01 14:46:37 bostic 7 6
c new copyright notice
e
s 00013/00006/00028
d D 5.6 90/05/17 10:44:16 bostic 6 5
c ANSI C version from Chris
e
s 00009/00011/00025
d D 5.5 89/05/10 16:45:32 bostic 5 4
c store both chars in register to force optimization; Chris's version
e
s 00010/00005/00026
d D 5.4 88/06/27 18:25:42 bostic 4 3
c install approved copyright notice
e
s 00010/00008/00021
d D 5.3 88/05/25 14:24:02 bostic 3 2
c written by Robert Elz; add Berkeley specific header
e
s 00001/00001/00028
d D 5.2 86/03/09 19:36:04 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00029/00000/00000
d D 5.1 85/08/05 21:43:09 kre 1 0
c date and time created 85/08/05 21:43:09 by kre
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1985 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1985, 1993
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 4
E 3
 */

D 3
/*
 * Sys 5 compat routine...
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

I 8
#include <sys/cdefs.h>
E 8
I 6
#include <string.h>
D 8
#include <sys/stdc.h>
E 8

/*
 * Find the first occurrence in s1 of a character in s2 (excluding NUL).
 */
E 6
char *
D 5
strpbrk(s, brk)
	register char *s, *brk;
E 5
I 5
strpbrk(s1, s2)
D 6
	register char *s1, *s2;
E 6
I 6
	register const char *s1, *s2;
E 6
E 5
{
I 6
	register const char *scanp;
E 6
D 5
	register char *p;
	register c;
E 5
I 5
	register int c, sc;
D 6
	register char *scanp;
E 6
E 5

D 5
	while (c = *s) {
		for (p = brk; *p; p++)
			if (c == *p)
				return (s);
		s++;
	}
	return (0);
E 5
I 5
D 6
	for (; c = *s1; ++s1)
		for (scanp = s2; sc = *scanp++;)
E 6
I 6
	while ((c = *s1++) != 0) {
		for (scanp = s2; (sc = *scanp++) != 0;)
E 6
			if (sc == c)
D 6
				return(s1);
	return(0);
E 6
I 6
				return ((char *)(s1 - 1));
	}
	return (NULL);
E 6
E 5
}
E 1
