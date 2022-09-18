h26645
s 00008/00005/00026
d D 5.4 91/04/12 14:59:00 bostic 5 4
c new copyright; att/bsd/shared
e
s 00003/00003/00028
d D 5.3 91/01/15 18:16:47 bostic 4 3
c kernel reorg
e
s 00016/00000/00015
d D 5.2 86/11/03 21:00:56 mckusick 3 2
c update for tahoe
e
s 00005/00001/00010
d D 5.1 85/06/07 21:46:16 kre 2 1
c Add copyright
e
s 00011/00000/00000
d D 1.1 83/01/21 11:10:32 dlw 1 0
c date and time created 83/01/21 11:10:32 by dlw
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

I 3
#ifndef tahoe
E 3
double d_sign(a,b)
double *a, *b;
{
double x;
x = (*a >= 0 ? *a : - *a);
return( *b >= 0 ? x : -x);
}
I 3

D 4
#else tahoe
E 4
I 4
#else
E 4

D 4
#include <tahoemath/FP.h>
E 4
I 4
#include <tahoe/math/FP.h>
E 4

double d_sign(a,b)
double *a, *b;
{
double x;
x = *a;
if ((*a < 0) || (*b < 0))
	*(unsigned long *)&x ^= SIGN_BIT;
return(x);
}
D 4
#endif tahoe
E 4
I 4
#endif
E 4
E 3
E 1
