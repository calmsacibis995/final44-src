h10494
s 00002/00002/00027
d D 8.1 93/06/04 15:11:26 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00028
d D 5.5 91/01/26 15:31:56 bostic 6 5
c stdc.h -> cdefs.h
e
s 00018/00018/00011
d D 5.4 90/05/16 18:31:56 bostic 5 4
c compare using unsigned characters
e
s 00022/00010/00007
d D 5.3 88/07/18 16:07:00 bostic 4 3
c rewritten from the manual page; add Berkeley specific header
e
s 00002/00002/00015
d D 5.2 86/03/09 19:57:36 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00013
d D 5.1 85/06/05 12:36:35 mckusick 2 1
c Add copyright
e
s 00014/00000/00000
d D 4.1 80/12/21 16:40:10 wnj 1 0
c date and time created 80/12/21 16:40:10 by wnj
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
D 5
/*
D 4
 * Compare strings:  s1>s2: >0  s1==s2: 0  s1<s2: <0
E 4
I 4
 * Copyright (c) 1988 Regents of the University of California.
E 5
I 5
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
E 5
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
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
E 5
I 5
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 5
E 4
 */

I 4
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 5
D 6
#include <sys/stdc.h>
E 6
I 6
#include <sys/cdefs.h>
E 6
#include <string.h>

/*
 * Compare strings.
 */
int
E 5
E 4
strcmp(s1, s2)
D 4
register char *s1, *s2;
E 4
I 4
D 5
	register char *s1, *s2;
E 5
I 5
	register const char *s1, *s2;
E 5
E 4
{
D 4

	while (*s1 == *s2++)
		if (*s1++=='\0')
E 4
I 4
D 5
	for (; *s1 == *s2; ++s1, ++s2)
		if (!*s1)
E 4
			return(0);
D 4
	return(*s1 - *--s2);
E 4
I 4
	return(*s1 - *s2);
E 5
I 5
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
E 5
E 4
}
E 1
