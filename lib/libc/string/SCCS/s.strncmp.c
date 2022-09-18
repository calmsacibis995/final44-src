h25494
s 00002/00002/00028
d D 8.1 93/06/04 15:12:20 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00029
d D 5.6 91/01/26 15:32:03 bostic 7 6
c stdc.h -> cdefs.h
e
s 00001/00011/00029
d D 5.5 90/06/01 14:46:28 bostic 6 5
c new copyright notice
e
s 00020/00010/00020
d D 5.4 90/05/17 10:38:06 bostic 5 4
c ANSI version
e
s 00024/00012/00006
d D 5.3 88/07/18 16:18:15 bostic 4 3
c rewritten from the manual page; add Berkeley specific copyright
e
s 00002/00002/00016
d D 5.2 86/03/09 19:58:35 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00014
d D 5.1 85/06/05 12:37:53 mckusick 2 1
c Add copyright
e
s 00015/00000/00000
d D 4.1 80/12/21 16:40:19 wnj 1 0
c date and time created 80/12/21 16:40:19 by wnj
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
/*
D 4
 * Compare strings (at most n bytes):  s1>s2: >0  s1==s2: 0  s1<s2: <0
E 4
I 4
D 5
 * Copyright (c) 1988 Regents of the University of California.
E 5
I 5
D 8
 * Copyright (c) 1989 The Regents of the University of California.
E 5
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
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
D 5
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 */

D 4
strncmp(s1, s2, n)
register char *s1, *s2;
register n;
{
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */
E 4

D 4
	while (--n >= 0 && *s1 == *s2++)
		if (*s1++ == '\0')
E 4
I 4
D 5
strncmp(s1, s2, cnt)
	register char *s1, *s2;
	register int cnt;
E 5
I 5
D 7
#include <sys/stdc.h>
E 7
I 7
#include <sys/cdefs.h>
E 7
#include <string.h>

int
strncmp(s1, s2, n)
	register const char *s1, *s2;
	register size_t n;
E 5
{
D 5
	for (; cnt && *s1 == *s2; --cnt, ++s1, ++s2)
		if (!*s1)
E 4
			return(0);
D 4
	return(n<0 ? 0 : *s1 - *--s2);
E 4
I 4
	return(cnt ? *s1 - *s2 : 0);
E 5
I 5

	if (n == 0)
		return (0);
	do {
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)--s2);
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return (0);
E 5
E 4
}
E 1
