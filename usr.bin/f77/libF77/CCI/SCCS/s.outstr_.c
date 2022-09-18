h50049
s 00012/00002/00012
d D 5.2 91/04/12 15:16:02 bostic 2 1
c new copyright; att/bsd/shared
e
s 00014/00000/00000
d D 5.1 86/11/03 20:00:11 mckusick 1 0
c from CCI
e
u
U
t
T
I 1
D 2
/*
 *	%W% (Berkeley) %G%
E 2
I 2
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.proprietary.c%
E 2
 */
I 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include <stdio.h>

/* print a character string */
outstr_(s, n)
register char *s;
register long n;
{
while ( --n >= 0)
	putchar(*s++);
}
E 1
