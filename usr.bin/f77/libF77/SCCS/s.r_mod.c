h13006
s 00008/00005/00038
d D 5.6 91/04/12 15:00:01 bostic 7 6
c new copyright; att/bsd/shared
e
s 00003/00003/00040
d D 5.5 91/01/15 18:16:49 bostic 6 5
c kernel reorg
e
s 00022/00000/00021
d D 5.4 86/11/03 21:18:09 mckusick 5 4
c update for tahoe
e
s 00004/00001/00017
d D 5.3 85/07/09 15:34:03 jerry 4 3
c do store in global to force convert to float despite C bug.
e
s 00001/00001/00017
d D 5.2 85/07/08 14:31:11 jerry 3 2
c declare function as float, not double.
e
s 00005/00001/00013
d D 5.1 85/06/07 22:26:47 kre 2 1
c Add copyright
e
s 00014/00000/00000
d D 1.1 83/01/21 11:18:10 dlw 1 0
c date and time created 83/01/21 11:18:10 by dlw
e
u
U
t
T
I 1
D 7
/*
D 2
 *	"%W%"
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 7
 *
D 7
 *	%W%	%G%
E 7
I 7
 * %sccs.include.proprietary.c%
E 7
E 2
 */
I 7

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 7

I 5
#ifndef tahoe
E 5
I 4
float flt_retval;

E 4
D 3
double r_mod(x,y)
E 3
I 3
float r_mod(x,y)
E 3
float *x, *y;
{
double floor(), quotient = *x / *y;
if (quotient >= 0.0)
	quotient = floor(quotient);
else
	quotient = -floor(-quotient);
D 4
return(*x - (*y) * quotient );
E 4
I 4
flt_retval = *x - (*y) * quotient ;
return(flt_retval);
E 4
}
I 5

D 6
#else tahoe
E 6
I 6
#else
E 6

/*   THIS IS BASED ON THE TAHOE REPR. FOR FLOATING POINT */
D 6
#include <tahoemath/FP.h>
E 6
I 6
#include <tahoe/math/FP.h>
E 6

double r_mod(x,y)
float *x, *y;
{
double floor(), quotient = *x / *y;
if (quotient >= 0.0)
	quotient = floor(quotient);
else {
	*(unsigned long *)&quotient ^= SIGN_BIT;
	quotient = floor(quotient);
	if (quotient != 0)
		*(unsigned long *)&quotient ^= SIGN_BIT;
	}
return(*x - (*y) * quotient );
}
D 6
#endif tahoe
E 6
I 6
#endif
E 6
E 5
E 1
