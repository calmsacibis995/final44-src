h26467
s 00008/00005/00022
d D 5.4 91/04/12 14:58:48 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00025
d D 5.3 91/01/15 18:16:44 bostic 4 3
c kernel reorg
e
s 00011/00000/00016
d D 5.2 86/11/03 20:56:01 mckusick 3 2
c update for tahoe
e
s 00005/00001/00011
d D 5.1 85/06/07 21:40:47 kre 2 1
c Add copyright
e
s 00012/00000/00000
d D 1.1 83/01/21 11:09:17 dlw 1 0
c date and time created 83/01/21 11:09:17 by dlw
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
#endif tahoe
E 4
I 4
#include <tahoe/math/FP.h>
#endif
E 4
E 3

d_cnjg(r, z)
dcomplex *r, *z;
{
r->dreal = z->dreal;
I 3
#ifndef tahoe
E 3
r->dimag = - z->dimag;
I 3
#else tahoe
r->dimag = z->dimag;
if (z->dimag == 0.0)
	return;
else
	*(unsigned long *)&(z->dimag) ^= SIGN_BIT;
#endif tahoe
E 3
}
E 1
