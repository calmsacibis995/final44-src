h58763
s 00002/00002/00040
d D 8.1 93/06/04 15:12:23 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00041
d D 5.6 91/01/26 15:32:04 bostic 7 6
c stdc.h -> cdefs.h
e
s 00030/00023/00012
d D 5.5 90/05/17 10:42:15 bostic 6 5
c ANSI version from Chris
e
s 00006/00004/00029
d D 5.4 90/02/15 17:24:35 marc 5 4
c was completely broken
e
s 00026/00018/00007
d D 5.3 88/07/18 16:43:26 bostic 4 3
c rewritten from manual page; add Berkeley specific header
e
s 00002/00002/00023
d D 5.2 86/03/09 19:58:48 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00021
d D 5.1 85/06/05 12:38:10 mckusick 2 1
c Add copyright
e
s 00022/00000/00000
d D 4.1 80/12/21 16:40:20 wnj 1 0
c date and time created 80/12/21 16:40:20 by wnj
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
 * Copy s2 to s1, truncating or null-padding to always copy n bytes
 * return s1
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

I 7
#include <sys/cdefs.h>
E 7
I 6
#include <string.h>
D 7
#include <sys/stdc.h>
E 7

/*
 * Copy src to dst, truncating or null-padding to always copy n bytes.
 * Return dst.
 */
E 6
E 4
char *
D 4
strncpy(s1, s2, n)
register char *s1, *s2;
E 4
I 4
D 6
strncpy(to, from, cnt)
	register char *to, *from;
	register int cnt;
E 6
I 6
strncpy(dst, src, n)
	char *dst;
	const char *src;
	register size_t n;
E 6
E 4
{
D 4
	register i;
	register char *os1;
E 4
I 4
D 6
	char *save = to;
E 6
I 6
	if (n != 0) {
		register char *d = dst;
		register const char *s = src;
E 6
E 4

D 4
	os1 = s1;
	for (i = 0; i < n; i++)
		if ((*s1++ = *s2++) == '\0') {
			while (++i < n)
				*s1++ = '\0';
			return(os1);
		}
	return(os1);
E 4
I 4
D 5
	for (; cnt && (*from = *to); --cnt, ++from, ++to);
	for (; cnt; --cnt, ++from)
		*from = '\0';
	return(save);
E 5
I 5
D 6
	for (; cnt && (*to = *from); --cnt, ++from, ++to)
		;
	if (cnt)
		bzero(to, cnt);

	return (save);
E 6
I 6
		do {
			if ((*d++ = *s++) == 0) {
				/* NUL pad the remaining n-1 bytes */
				while (--n != 0)
					*d++ = 0;
				break;
			}
		} while (--n != 0);
	}
	return (dst);
E 6
E 5
E 4
}
E 1
