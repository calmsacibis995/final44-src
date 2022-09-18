h15445
s 00002/00002/00042
d D 8.1 93/06/06 14:55:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00035
d D 4.3 91/04/17 17:56:38 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00037
d D 4.2 83/04/25 23:59:24 mckusick 2 1
c 
e
s 00037/00000/00000
d D 4.1 83/02/24 12:56:19 mckusick 1 0
c date and time created 83/02/24 12:56:19 by mckusick
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include <stdio.h>
main()
{
	int f, c;

	f = creat(".ocopy", 0666);
	while (read(0, &c, 1) == 1) {
		write (1, &c, 1);
		put(c, f);
	}
	fl(f);
	close(f);
}

static char ln[BUFSIZ];
char *p = ln;
put(c, f)
{
	*p++ = c;
	if (c == '\n') {
		fl(f);
		p=ln;
	}
}
fl(f)
{
	register char *s;

	s = ln;
	while (*s == '$' && *(s+1) == ' ')
		s += 2;
	write(f, s, p-s);
}
E 1
