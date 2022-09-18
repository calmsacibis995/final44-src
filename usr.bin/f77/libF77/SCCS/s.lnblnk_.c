h29993
s 00011/00006/00019
d D 5.3 91/04/12 14:59:36 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00024
d D 5.2 85/06/07 23:01:47 kre 3 2
c fix botch in previous delta
e
s 00005/00001/00020
d D 5.1 85/06/07 22:06:23 kre 2 1
c Add copyright
e
s 00021/00000/00000
d D 1.1 81/02/19 21:58:17 dlw 1 0
c date and time created 81/02/19 21:58:17 by dlw
e
u
U
t
T
I 1
D 4
/*
D 2
char id_lnblnk[] = "%W%";
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
E 2
 *
I 2
D 4
 *	%W%	%G%
D 3
 */
E 3
I 3
 *
E 4
I 4
 * %sccs.include.proprietary.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
E 4
E 3
E 2
 * find last occurrence of a non-blank character in string
 *
 * calling sequence:
 *	character*(*) string
 *	indx = lnblnk (string)
 * where:
 *	indx will be the index of the last occurence
 *	of a non-blank character in string, or zero if not found.
 */

long lnblnk_(str, slen)
char *str; long slen;
{
	register char *p = str + slen;

	while (--p >= str && *p == ' ' ) ;
	return((long)(++p - str));
}
E 1
