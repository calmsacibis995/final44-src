/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)r_mod.c	5.6 (Berkeley) 4/12/91";
#endif /* not lint */

#ifndef tahoe
float flt_retval;

float r_mod(x,y)
float *x, *y;
{
double floor(), quotient = *x / *y;
if (quotient >= 0.0)
	quotient = floor(quotient);
else
	quotient = -floor(-quotient);
flt_retval = *x - (*y) * quotient ;
return(flt_retval);
}

#else

/*   THIS IS BASED ON THE TAHOE REPR. FOR FLOATING POINT */
#include <tahoe/math/FP.h>

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
#endif
