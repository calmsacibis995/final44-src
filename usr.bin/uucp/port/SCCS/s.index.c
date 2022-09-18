h21181
s 00002/00002/00030
d D 8.1 93/06/06 22:13:11 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00024
d D 5.3 91/04/24 17:36:54 bostic 3 2
c new copyright; att/bsd/shared
e
s 00004/00006/00021
d D 5.2 85/01/22 14:09:12 ralph 2 1
c bug fixes and changes from Rick Adams
e
s 00027/00000/00000
d D 5.1 83/07/02 17:57:10 sam 1 0
c date and time created 83/07/02 17:57:10 by sam
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
#endif /* not lint */
E 3

#include <stdio.h>

D 2
/*******
 *	char *
 *	index(str, c)	return pointer to character c
 *	char c, *str;
E 2
I 2
/*
 *	return pointer to character c
E 2
 *
 *	return codes:
 *		NULL  -  character not found
 *		pointer  -  pointer to character
 */

char *
index(str, c)
register char c, *str;
{
	for (; *str != '\0'; str++) {
		if (*str == c)
D 2
			return(str);
E 2
I 2
			return str;
E 2
	}

D 2
	return(NULL);
E 2
I 2
	return NULL;
E 2
}
E 1
