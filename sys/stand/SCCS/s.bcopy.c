h51701
s 00002/00002/00024
d D 8.1 93/06/11 16:00:37 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00000/00000
d D 7.1 93/06/11 14:35:10 mckusick 1 0
c date and time created 93/06/11 14:35:10 by mckusick
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * This is designed to be small, not fast.
 */
void
bcopy(s1, s2, n)
	const void *s1;
	void *s2;
	unsigned n;
{
	register const char *f = s1;
	register char *t = s2;

	while (n != 0) {
		*t++ = *f++;
		n--;
	}
}
E 1
