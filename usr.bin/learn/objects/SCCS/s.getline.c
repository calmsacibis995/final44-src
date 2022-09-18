h03983
s 00002/00002/00025
d D 8.1 93/06/06 15:03:08 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00018
d D 5.1 91/04/17 18:03:13 bostic 2 1
c new copyright; att/bsd/shared
e
s 00020/00000/00000
d D 1.1 88/06/08 15:14:34 jak 1 0
c date and time created 88/06/08 15:14:34 by jak
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

getline(s, lim)	/* get line into s, return length */
char s[];
int lim;
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return(i);
}
E 1
