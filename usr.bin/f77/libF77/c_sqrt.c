/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)c_sqrt.c	5.4 (Berkeley) 4/12/91";
#endif /* not lint */

#include "complex"
#ifdef tahoe
#include <tahoe/math/FP.h>
#endif 

c_sqrt(r, z)
complex *r, *z;
{
double mag, sqrt(), cabs();

if( (mag = cabs(z->real, z->imag)) == 0.)
	r->real = r->imag = 0.;
else if(z->real > 0)
	{
	r->real = sqrt(0.5 * (mag + z->real) );
	r->imag = z->imag / r->real / 2;
	}
else
	{
	r->imag = sqrt(0.5 * (mag - z->real) );
	if(z->imag < 0)
#ifndef tahoe
		r->imag = - r->imag;
#else tahoe
		*(unsigned long*)&(r->imag) ^= SIGN_BIT;
#endif tahoe
	r->real = z->imag / r->imag /2;
	}
}
