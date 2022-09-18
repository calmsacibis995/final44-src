h35844
s 00002/00002/00116
d D 8.1 93/06/04 17:00:48 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00118/00000/00000
d D 5.1 90/05/17 19:18:30 bostic 1 0
c date and time created 90/05/17 19:18:30 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * ATAN2(Y,X)
 * RETURN ARG (X+iY)
 * DOUBLE PRECISION (IEEE DOUBLE 53 BITS)
 *
 * Scaled down version to weed out special cases.  "Normal" cases are
 * handled by calling atan2__A(), an assembly coded support routine in
 * support.s.
 *
 * Required system supported functions :
 *	copysign(x,y)
 *	atan2__A(y,x)
 *	
 * Method :
 *	1. Deal with special cases
 *	2. Call atan2__A() to do the others
 *
 * Special cases:
 * Notations: atan2(y,x) == ARG (x+iy) == ARG(x,y).
 *
 *	ARG( NAN , (anything) ) is NaN;
 *	ARG( (anything), NaN ) is NaN;
 *	ARG(+(anything but NaN), +-0) is +-0  ;
 *	ARG(-(anything but NaN), +-0) is +-PI ;
 *	ARG( 0, +-(anything but 0 and NaN) ) is +-PI/2;
 *	ARG( +INF,+-(anything but INF and NaN) ) is +-0 ;
 *	ARG( -INF,+-(anything but INF and NaN) ) is +-PI;
 *	ARG( +INF,+-INF ) is +-PI/4 ;
 *	ARG( -INF,+-INF ) is +-3PI/4;
 *	ARG( (anything but,0,NaN, and INF),+-INF ) is +-PI/2;
 *
 * Accuracy:
 *	atan2(y,x) returns (PI/pi) * the exact ARG (x+iy) nearly rounded, 
 *	where
 *
 *	in decimal:
 *		pi = 3.141592653589793 23846264338327 ..... 
 *    53 bits   PI = 3.141592653589793 115997963 ..... ,
 *    56 bits   PI = 3.141592653589793 227020265 ..... ,  
 *
 *	in hexadecimal:
 *		pi = 3.243F6A8885A308D313198A2E....
 *    53 bits   PI = 3.243F6A8885A30  =  2 * 1.921FB54442D18	error=.276ulps
 *    56 bits   PI = 3.243F6A8885A308 =  4 * .C90FDAA22168C2    error=.206ulps
 *	
 *	In a test run with 356,000 random argument on [-1,1] * [-1,1] on a
 *	VAX, the maximum observed error was 1.41 ulps (units of the last place)
 *	compared with (PI/pi)*(the exact ARG(x+iy)).
 *
 * Note:
 *	We use machine PI (the true pi rounded) in place of the actual
 *	value of pi for all the trig and inverse trig functions. In general, 
 *	if trig is one of sin, cos, tan, then computed trig(y) returns the 
 *	exact trig(y*pi/PI) nearly rounded; correspondingly, computed arctrig 
 *	returns the exact arctrig(y)*PI/pi nearly rounded. These guarantee the 
 *	trig functions have period PI, and trig(arctrig(x)) returns x for
 *	all critical values x.
 *	
 * Constants:
 * The hexadecimal values are the intended ones for the following constants.
 * The decimal values may be used, provided that the compiler will convert
 * from decimal to binary accurately enough to produce the hexadecimal values
 * shown.
 */

static double 
PIo4   =  7.8539816339744827900E-1    , /*Hex  2^ -1   *  1.921FB54442D18 */
PIo2   =  1.5707963267948965580E0     , /*Hex  2^  0   *  1.921FB54442D18 */
PI     =  3.1415926535897931160E0     ; /*Hex  2^  1   *  1.921FB54442D18 */

double atan2(y,x)
double  y,x;
{  
	static double zero=0, one=1;
	double copysign(),atan2__A(),signy,signx;
	int finite();

    /* if x or y is NAN */
	if(x!=x) return(x); if(y!=y) return(y);

    /* copy down the sign of y and x */
	signy = copysign(one,y);
	signx = copysign(one,x);

    /* when y = 0 */
	if(y==zero) return((signx==one)?y:copysign(PI,signy));

    /* when x = 0 */
	if(x==zero) return(copysign(PIo2,signy));
	    
    /* when x is INF */
	if(!finite(x))
	    if(!finite(y)) 
		return(copysign((signx==one)?PIo4:3*PIo4,signy));
	    else
		return(copysign((signx==one)?zero:PI,signy));

    /* when y is INF */
	if(!finite(y)) return(copysign(PIo2,signy));

    /* else let atan2__A do the work */
	return(atan2__A(y,x));
}
E 1
