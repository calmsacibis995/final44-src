h51456
s 00002/00002/00017
d D 8.1 93/06/10 23:30:42 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00000/00000
d D 7.1 92/11/15 16:50:57 ralph 1 0
c date and time created 92/11/15 16:50:57 by ralph
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <pmax/stand/dec_prom.h>

strcmp(s1, s2)
	char *s1, *s2;
{
	return (callv->strcmp(s1, s2));
}
E 1
