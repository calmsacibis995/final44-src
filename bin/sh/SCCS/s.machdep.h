h14469
s 00001/00001/00024
d D 8.2 95/05/04 17:59:51 christos 3 2
c 
e
s 00002/00002/00023
d D 8.1 93/05/31 15:19:26 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00000
d D 5.1 91/03/07 20:27:36 bostic 1 0
c date and time created 91/03/07 20:27:36 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Most machines require the value returned from malloc to be aligned
 * in some way.  The following macro will get this right on many machines.
 */

#ifndef ALIGN
union align {
	int i;
	char *cp;
};

D 3
#define ALIGN(nbytes)	((nbytes) + sizeof(union align) - 1 &~ (sizeof(union align) - 1))
E 3
I 3
#define ALIGN(nbytes)	(((nbytes) + sizeof(union align) - 1) & ~(sizeof(union align) - 1))
E 3
#endif
E 1
