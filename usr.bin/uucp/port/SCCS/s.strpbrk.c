h05099
s 00002/00002/00029
d D 8.1 93/06/06 22:13:27 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00023
d D 5.2 91/04/24 17:36:57 bostic 2 1
c new copyright; att/bsd/shared
e
s 00024/00000/00000
d D 5.1 85/06/23 15:41:11 bloom 1 0
c date and time created 85/06/23 15:41:11 by bloom
e
u
U
t
T
I 2
/*-
D 3
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
#endif /* not lint */
E 2

/*LINTLIBRARY*/

/*
 * this is like index, but takes a string as the second argument
 */
char *
strpbrk(str, chars)
register char *str, *chars;
{
	register char *cp;

	do {
		cp = chars - 1;
		while (*++cp) {
			if (*str == *cp)
				return str;
		}
	} while (*str++);
	return (char *)0;
}
E 1
