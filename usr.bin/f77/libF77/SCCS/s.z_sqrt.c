h44915
s 00008/00005/00033
d D 5.4 91/04/12 15:00:31 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00036
d D 5.3 91/01/15 18:16:52 bostic 4 3
c kernel reorg
e
s 00008/00000/00030
d D 5.2 86/11/03 21:28:37 mckusick 3 2
c update for tahoe
e
s 00005/00001/00025
d D 5.1 85/06/07 22:56:20 kre 2 1
c Add copyright
e
s 00026/00000/00000
d D 1.1 83/01/21 11:21:04 dlw 1 0
c date and time created 83/01/21 11:21:04 by dlw
e
u
U
t
T
I 1
D 5
/*
D 2
 *	"%W%"
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
 *
D 5
 *	%W%	%G%
E 5
I 5
 * %sccs.include.proprietary.c%
E 5
E 2
 */
I 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

#include "complex"
I 3
#ifdef tahoe
D 4
#include <tahoemath/FP.h>
E 4
I 4
#include <tahoe/math/FP.h>
E 4
#define cabs zabs
D 4
#endif tahoe
E 4
I 4
#endif
E 4
E 3

z_sqrt(r, z)
dcomplex *r, *z;
{
double mag, sqrt(), cabs();

if( (mag = cabs(z->dreal, z->dimag)) == 0.)
	r->dreal = r->dimag = 0.;
else if(z->dreal > 0)
	{
	r->dreal = sqrt(0.5 * (mag + z->dreal) );
	r->dimag = z->dimag / r->dreal / 2;
	}
else
	{
	r->dimag = sqrt(0.5 * (mag - z->dreal) );
	if(z->dimag < 0)
I 3
#ifndef tahoe
E 3
		r->dimag = - r->dimag;
I 3
#else tahoe
		*((long int *)&r->dimag) ^= SIGN_BIT;
#endif tahoe
E 3
	r->dreal = z->dimag / r->dimag / 2;
	}
}
E 1
