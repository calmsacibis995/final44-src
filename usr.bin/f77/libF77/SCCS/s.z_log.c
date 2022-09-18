h11480
s 00008/00005/00016
d D 5.3 91/04/12 15:00:29 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00000/00018
d D 5.2 86/11/03 21:26:34 mckusick 3 2
c update for tahoe
e
s 00005/00001/00013
d D 5.1 85/06/07 22:55:23 kre 2 1
c Add copyright
e
s 00014/00000/00000
d D 1.1 83/01/21 11:20:33 dlw 1 0
c date and time created 83/01/21 11:20:33 by dlw
e
u
U
t
T
I 1
D 4
/*
D 2
 *	"%W%"
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
 *
D 4
 *	%W%	%G%
E 4
I 4
 * %sccs.include.proprietary.c%
E 4
E 2
 */
I 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

#include "complex"
I 3
#ifdef tahoe
#define cabs zabs
#endif tahoe
E 3

z_log(r, z)
dcomplex *r, *z;
{
double log(), cabs(), atan2();

r->dimag = atan2(z->dimag, z->dreal);
r->dreal = log( cabs( z->dreal, z->dimag ) );
}
E 1
