h62883
s 00002/00002/00062
d D 8.1 93/06/04 15:12:55 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00060
d D 5.8 91/02/24 13:57:55 bostic 8 7
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00062
d D 5.7 90/06/01 14:47:07 bostic 7 6
c new copyright notice
e
s 00002/00001/00071
d D 5.6 90/05/17 12:05:48 bostic 6 5
c keep string.h and source in sync
e
s 00042/00027/00030
d D 5.5 88/08/01 19:53:31 bostic 5 4
c Chris Torek's version, much faster
e
s 00010/00005/00047
d D 5.4 88/06/27 18:25:51 bostic 4 3
c install approved copyright notice
e
s 00011/00009/00041
d D 5.3 88/05/25 14:24:05 bostic 3 2
c written by Robert Elz; add Berkeley specific header
e
s 00001/00001/00049
d D 5.2 86/03/09 19:36:48 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00050/00000/00000
d D 5.1 85/08/05 21:43:11 kre 1 0
c date and time created 85/08/05 21:43:11 by kre
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 5
 * Copyright (c) 1985 Regents of the University of California.
E 5
I 5
D 9
 * Copyright (c) 1988 Regents of the University of California.
E 5
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
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

I 5
D 6
#include <stdio.h>
E 6
I 6
#include <stddef.h>
#include <string.h>
E 6

E 5
char *
D 5
strtok(s, sep)
	register char *s, *sep;
E 5
I 5
strtok(s, delim)
D 8
	register char *s, *delim;
E 8
I 8
	register char *s;
	register const char *delim;
E 8
E 5
{
D 5
	register char *p;
	register c;
	static char *lasts;
E 5
I 5
	register char *spanp;
	register int c, sc;
	char *tok;
	static char *last;
E 5

D 5
	if (s == 0)
		s = lasts;
	if (s == 0)
		return (0);
E 5

D 5
	while (c = *s) {
		if (!index(sep, c))
			break;
		s++;
E 5
I 5
	if (s == NULL && (s = last) == NULL)
		return (NULL);

	/*
	 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
D 8
	for (spanp = delim; (sc = *spanp++) != 0;) {
E 8
I 8
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
E 8
		if (c == sc)
			goto cont;
E 5
	}

D 5
	if (c == '\0') {
		lasts = 0;
		return (0);
E 5
I 5
	if (c == 0) {		/* no non-delimiter characters */
		last = NULL;
		return (NULL);
E 5
	}
I 5
	tok = s - 1;
E 5

D 5
	for (p = s; c = *++p; )
		if (index(sep, c))
			break;

	if (c == '\0')
		lasts = 0;
	else {
		*p++ = '\0';
		lasts = p;
E 5
I 5
	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;) {
		c = *s++;
D 8
		spanp = delim;
E 8
I 8
		spanp = (char *)delim;
E 8
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
E 5
	}
D 5
	return (s);
E 5
I 5
	/* NOTREACHED */
E 5
}
E 1
