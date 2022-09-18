h65302
s 00002/00002/00022
d D 8.1 93/06/04 15:12:08 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00023
d D 5.5 91/01/26 15:32:00 bostic 6 5
c stdc.h -> cdefs.h
e
s 00012/00017/00012
d D 5.4 90/05/17 10:34:25 bostic 5 4
c ANSI version
e
s 00023/00013/00006
d D 5.3 88/07/18 15:31:52 bostic 4 3
c rewritten from the manual page; add Berkeley specific copyright
e
s 00002/00002/00017
d D 5.2 86/03/09 19:58:07 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00015
d D 5.1 85/06/05 12:37:13 mckusick 2 1
c Add copyright
e
s 00016/00000/00000
d D 4.1 80/12/21 16:40:16 wnj 1 0
c date and time created 80/12/21 16:40:16 by wnj
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
 * Returns the number of
 * non-NULL bytes in string argument.
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
 * %sccs.include.redist.c%
E 5
E 4
 */

D 4
strlen(s)
register char *s;
E 4
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

size_t
E 5
strlen(str)
D 5
	register char *str;
E 5
I 5
	const char *str;
E 5
E 4
{
D 4
	register n;
E 4
I 4
D 5
	register int cnt;
E 5
I 5
	register const char *s;
E 5
E 4

D 4
	n = 0;
	while (*s++)
		n++;
	return(n);
E 4
I 4
D 5
	for (cnt = 0; *str; ++cnt, ++str);
	return(cnt);
E 5
I 5
	for (s = str; *s; ++s);
	return(s - str);
E 5
E 4
}
I 5

E 5
E 1
