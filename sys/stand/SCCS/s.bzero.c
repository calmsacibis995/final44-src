h47507
s 00002/00002/00022
d D 8.1 93/06/11 16:00:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00000/00000
d D 7.1 93/06/11 14:35:11 mckusick 1 0
c date and time created 93/06/11 14:35:11 by mckusick
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
bzero(s1, n)
	void *s1;
	unsigned n;
{
	register char *t = s1;

	while (n != 0) {
		*t++ = 0;
		n--;
	}
}
E 1
