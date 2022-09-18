/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)r_tan.c	5.5 (Berkeley) 4/12/91";
#endif /* not lint */

#ifndef tahoe
float r_tan(x)
float *x;
{
double tan();
return( tan(*x) );
}

#else tahoe

/*
	SINGLE PRECISION floating point tangent

	sin/cos is used after argument reduction to [0,pi/4] range.
	since x is in this range, tan(x) is in [0,1] range and
	no overflow can occur here.
*/

#include <errno.h>

int	errno;
static double invpi = 1.27323954473516268;  /* 4/pi */

#ifndef __GNUC__
fortran float sin(), cos();
#else
#define	sin(x) \
({ \
	float __result; \
	asm("ldd %1; cvdf; sinf; stf %0" : "=rm" (__result) : "rm" (x)); \
	__result; \
})
#define	cos(x) \
({ \
	float __result; \
	asm("ldd %1; cvdf; cosf; stf %0" : "=rm" (__result) : "rm" (x)); \
	__result; \
})
#endif

float
r_tan(parg)
float *parg;
{
	double arg;
	double modf();
	float flmax_();
	double temp, e, x, xsq;
	int sign;
	int flag, i;

	arg = *parg;
	flag = 0;
	sign = 1.;
	if(arg < 0.){		/* tan(-arg) = -tan(arg) */
		arg = -arg;
		sign = -1.;
	}
	arg = arg*invpi;   /*overflow?*/
	x = modf(arg,&e);
	i = e;
	switch(i%4) {
	case 1:			/* 2nd octant: tan(x) = 1/tan(1-x) */
		x = 1. - x;
		flag = 1;
		break;

	case 2:			/* 3rd octant: tan(x) = -1/tan(x) */
		sign = - sign;
		flag = 1;
		break;

	case 3:			/* 4th octant: tan(x) = -tan(1-x) */
		x = 1. - x;
		sign = - sign;
		break;

	case 0:			/* 1st octant */
		break;
	}
	x = x/invpi;

	temp = sin(x)/cos(x);

	if(flag == 1) {
		if(temp == 0.) {	/* check for singular "point" */
			errno = ERANGE;
			if (sign>0)
				return(flmax_());
			return(-flmax_());
		}
		temp = 1./temp;
	}
	return(sign*temp);
}

#endif tahoe
