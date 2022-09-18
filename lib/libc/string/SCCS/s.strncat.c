h59845
s 00002/00002/00040
d D 8.1 93/06/04 15:12:17 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00041
d D 5.6 91/01/26 15:32:02 bostic 7 6
c stdc.h -> cdefs.h
e
s 00030/00023/00012
d D 5.5 90/05/17 10:39:47 bostic 6 5
c ANSI version of strncat.c
e
s 00003/00002/00032
d D 5.4 90/05/15 11:07:49 bostic 5 4
c goes past the end of append string
e
s 00027/00021/00007
d D 5.3 88/07/18 15:44:03 bostic 4 3
c rewritten from the manual page; add Berkeley specific header
e
s 00002/00002/00026
d D 5.2 86/03/09 19:58:23 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00024
d D 5.1 85/06/05 12:37:36 mckusick 2 1
c Add copyright
e
s 00025/00000/00000
d D 4.1 80/12/21 16:40:17 wnj 1 0
c date and time created 80/12/21 16:40:17 by wnj
e
u
U
t
T
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 3
#ifndef lint
E 3
I 3
D 4
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif LIBC_SCCS and not lint
E 3

E 4
E 2
D 6
/*
D 4
 * Concatenate s2 on the end of s1.  S1's space must be large enough.
 * At most n characters are moved.
 * Return s1.
E 4
I 4
 * Copyright (c) 1988 Regents of the University of California.
E 6
I 6
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
E 6
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 6
 * Redistribution and use in source and binary forms are permitted
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
E 6
I 6
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 6
E 4
 */

I 4
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 6
D 7
#include <sys/stdc.h>
E 7
I 7
#include <sys/cdefs.h>
E 7
#include <string.h>

/*
 * Concatenate src on the end of dst.  At most strlen(dst)+n+1 bytes
 * are written at dst (at most n+1 bytes being appended).  Return dst.
 */
E 6
E 4
char *
D 4
strncat(s1, s2, n)
register char *s1, *s2;
register n;
E 4
I 4
D 6
strncat(s, append, cnt)
	register char *s, *append;
	register int cnt;
E 6
I 6
strncat(dst, src, n)
	char *dst;
	const char *src;
	register size_t n;
E 6
E 4
{
I 5
D 6
	register char ch;
E 5
D 4
	register char *os1;
E 4
I 4
	char *save = s;
E 6
I 6
	if (n != 0) {
		register char *d = dst;
		register const char *s = src;
E 6
E 4

D 4
	os1 = s1;
	while (*s1++)
		;
	--s1;
	while (*s1++ = *s2++)
		if (--n < 0) {
			*--s1 = '\0';
			break;
		}
	return(os1);
E 4
I 4
D 6
	for (; *s; ++s);
D 5
	for (; cnt; --cnt)
		*s++ = *append++;
E 5
I 5
	for (; cnt && (ch = *append++); --cnt)
		*s++ = ch;
E 5
	*s = '\0';
	return(save);
E 6
I 6
		while (*d != 0)
			d++;
		do {
			if ((*d = *s++) == 0)
				break;
			d++;
		} while (--n != 0);
		*d = 0;
	}
	return (dst);
E 6
E 4
}
E 1
