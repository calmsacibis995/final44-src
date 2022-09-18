h24431
s 00008/00005/00023
d D 5.3 91/04/12 14:59:48 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00000/00025
d D 5.2 86/11/03 21:15:36 mckusick 3 2
c update for tahoe
e
s 00005/00001/00020
d D 5.1 85/06/07 22:19:44 kre 2 1
c Add copyright
e
s 00021/00000/00000
d D 1.1 83/01/21 11:16:55 dlw 1 0
c date and time created 83/01/21 11:16:55 by dlw
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

pow_zz(r,a,b)
dcomplex *r, *a, *b;
{
double logr, logi, x, y;
double log(), exp(), cos(), sin(), atan2(), cabs();

logr = log( cabs(a->dreal, a->dimag) );
logi = atan2(a->dimag, a->dreal);

x = exp( logr * b->dreal - logi * b->dimag );
y = logr * b->dimag + logi * b->dreal;

r->dreal = x * cos(y);
r->dimag = x * sin(y);
}
E 1
