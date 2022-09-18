h62841
s 00002/00002/00022
d D 8.1 93/06/06 15:03:10 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00015
d D 5.1 91/04/17 18:03:14 bostic 2 1
c new copyright; att/bsd/shared
e
s 00017/00000/00000
d D 1.1 88/06/08 15:14:35 jak 1 0
c date and time created 88/06/08 15:14:35 by jak
e
u
U
t
T
I 2
/*-
D 3
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include <stdio.h>

getnum()
{
	int c, n;

	n = 0;
	while ((c=getchar()) >= '0' && c <= '9')
		n = n*10 + c - '0';
	if (c == EOF)
		return(-1);
	return(n);
}
E 1
