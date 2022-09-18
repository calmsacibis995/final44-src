h06760
s 00009/00002/00028
d D 5.3 91/04/12 15:00:32 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00004/00028
d D 5.2 86/11/03 21:54:46 mckusick 2 1
c tahoe only
e
s 00032/00000/00000
d D 5.1 86/11/03 20:00:15 mckusick 1 0
c from CCI
e
u
U
t
T
I 1
D 3
/*
 *	%W%	%G%
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 3
 */
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

D 2
/*
 *	"@(#)zabs.c	1.1"
 */

E 2
I 2
#ifdef tahoe
E 2
/* THIS IS BASED ON TAHOE FP REPRESENTATION */
#include <tahoemath/FP.h>

double zabs(real, imag)
double real, imag;
{
double temp, sqrt();

if(real < 0)
	*(long int *)&real ^= SIGN_BIT;
if(imag < 0)
	*(long int *)&imag ^= SIGN_BIT;
if(imag > real){
	temp = real;
	real = imag;
	imag = temp;
}
if(imag == 0.)		/* if((real+imag) == real) */
	return(real);

temp = imag/real;
temp = real*sqrt(1.0 + temp*temp);  /*overflow!!*/
return(temp);
}
I 2
#endif tahoe
E 2
E 1
