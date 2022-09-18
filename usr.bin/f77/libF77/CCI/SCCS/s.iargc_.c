h44038
s 00012/00002/00007
d D 5.2 91/04/12 15:15:57 bostic 2 1
c new copyright; att/bsd/shared
e
s 00009/00000/00000
d D 5.1 86/11/03 20:00:08 mckusick 1 0
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

long int iargc_()
{
extern int xargc;
return ( xargc - 1 );
}
E 1
