h47127
s 00002/00002/00046
d D 8.1 93/06/06 22:11:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00040
d D 5.4 91/04/24 17:33:51 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00000/00039
d D 5.3 85/06/20 10:13:13 bloom 3 2
c lint fix from rick adams
e
s 00008/00010/00031
d D 5.2 85/01/22 14:10:46 ralph 2 1
c bug fixes and changes from Rick Adams
e
s 00041/00000/00000
d D 5.1 83/07/02 17:57:26 sam 1 0
c date and time created 83/07/02 17:57:26 by sam
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

I 3
/*LINTLIBRARY*/

E 3
D 2
/*******
 *	prefix(s1, s2)	check s2 for prefix s1
 *	char *s1, *s2;
E 2
I 2
/*
 *	check s2 for prefix s1
E 2
 *
 *	return 0 - !=
 *	return 1 - == 
 */

prefix(s1, s2)
register char *s1, *s2;
{
	register char c;

	while ((c = *s1++) == *s2++)
		if (c == '\0')
D 2
			return(1);
	return(c == '\0');
E 2
I 2
			return 1;
	return c == '\0';
E 2
}

D 2
/*******
 *	wprefix(s1, s2)	check s2 for prefix s1 with a wildcard character ?
 *	char *s1, *s2;
E 2
I 2
/*
 *	check s2 for prefix s1 with a wildcard character ?
E 2
 *
 *	return 0 - !=
 *	return 1 - == 
 */

wprefix(s1, s2)
register char *s1, *s2;
{
	register char c;

	while ((c = *s1++) != '\0')
		if (*s2 == '\0'  ||  (c != *s2++  &&  c != '?'))
D 2
			return(0);
	return(1);
E 2
I 2
			return 0;
	return 1;
E 2
}
E 1
