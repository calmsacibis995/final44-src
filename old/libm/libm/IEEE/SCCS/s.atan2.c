h01554
s 00002/00002/00237
d D 1.4 87/06/29 22:56:39 sam 4 3
c tahoe machine depencencies from pixar!bill
e
s 00004/00003/00235
d D 1.3 85/08/21 13:48:39 miriam 3 2
c Revision by Prof. Kahan.
e
s 00003/00003/00235
d D 1.2 85/06/03 16:15:33 miriam 2 1
c Changes for Prof. Kahan
e
s 00238/00000/00000
d D 1.1 85/05/23 17:12:25 miriam 1 0
c date and time created 85/05/23 17:12:25 by miriam
e
u
U
t
From Prof. Kahan at UC at Berkeley
T
I 1
/* 
 * Copyright (c) 1985 Regents of the University of California.
 * 
 * Use and reproduction of this software are granted  in  accordance  with
 * the terms and conditions specified in  the  Berkeley  Software  License
 * Agreement (in particular, this entails acknowledgement of the programs'
 * source, and inclusion of this notice) with the additional understanding
 * that  all  recipients  should regard themselves as participants  in  an
 * ongoing  research  project and hence should  feel  obligated  to report
 * their  experiences (good or bad) with these elementary function  codes,
 * using "sendbug 4bsd-bugs@BERKELEY", to the authors.
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

/* ATAN2(Y,X)
 * RETURN ARG (X+iY)
 * DOUBLE PRECISION (VAX D format 56 bits, IEEE DOUBLE 53 BITS)
 * CODED IN C BY K.C. NG, 1/8/85; 
D 3
 * REVISED BY K.C. NG on 2/7/85, 2/13/85, 3/7/85, 3/30/85.
E 3
I 3
 * REVISED BY K.C. NG on 2/7/85, 2/13/85, 3/7/85, 3/30/85, 6/29/85.
E 3
 *
 * Required system supported functions :
 *	copysign(x,y)
 *	scalb(x,y)
 *	logb(x)
 *	
 * Method :
 *	1. Reduce y to positive by atan2(y,x)=-atan2(-y,x).
 *	2. Reduce x to positive by (if x and y are unexceptional): 
 *		ARG (x+iy) = arctan(y/x)   	   ... if x > 0,
 *		ARG (x+iy) = pi - arctan[y/(-x)]   ... if x < 0,
 *	3. According to the integer k=4t+0.25 truncated , t=y/x, the argument 
 *	   is further reduced to one of the following intervals and the 
 *	   arctangent of y/x is evaluated by the corresponding formula:
 *
 *         [0,7/16]	   atan(y/x) = t - t^3*(a1+t^2*(a2+...(a10+t^2*a11)...)
 *	   [7/16,11/16]    atan(y/x) = atan(1/2) + atan( (y-x/2)/(x+y/2) )
 *	   [11/16.19/16]   atan(y/x) = atan( 1 ) + atan( (y-x)/(x+y) )
 *	   [19/16,39/16]   atan(y/x) = atan(3/2) + atan( (y-1.5x)/(x+1.5y) )
 *	   [39/16,INF]     atan(y/x) = atan(INF) + atan( -x/y )
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
D 4
#ifdef VAX 	/* VAX D format */
E 4
I 4
#if defined(VAX) || defined(TAHOE) 	/* VAX D format */
E 4
athfhi =  4.6364760900080611433E-1    , /*Hex  2^ -1   *  .ED63382B0DDA7B */
athflo =  1.9338828231967579916E-19   , /*Hex  2^-62   *  .E450059CFE92C0 */
PIo4   =  7.8539816339744830676E-1    , /*Hex  2^  0   *  .C90FDAA22168C2 */	
at1fhi =  9.8279372324732906796E-1    , /*Hex  2^  0   *  .FB985E940FB4D9 */
at1flo = -3.5540295636764633916E-18   , /*Hex  2^-57   * -.831EDC34D6EAEA */
PIo2   =  1.5707963267948966135E0     , /*Hex  2^  1   *  .C90FDAA22168C2 */
PI     =  3.1415926535897932270E0     , /*Hex  2^  2   *  .C90FDAA22168C2 */
a1     =  3.3333333333333473730E-1    , /*Hex  2^ -1   *  .AAAAAAAAAAAB75 */
a2     = -2.0000000000017730678E-1    , /*Hex  2^ -2   * -.CCCCCCCCCD946E */
a3     =  1.4285714286694640301E-1    , /*Hex  2^ -2   *  .92492492744262 */
a4     = -1.1111111135032672795E-1    , /*Hex  2^ -3   * -.E38E38EBC66292 */
a5     =  9.0909091380563043783E-2    , /*Hex  2^ -3   *  .BA2E8BB31BD70C */
a6     = -7.6922954286089459397E-2    , /*Hex  2^ -3   * -.9D89C827C37F18 */
a7     =  6.6663180891693915586E-2    , /*Hex  2^ -3   *  .8886B4AE379E58 */
a8     = -5.8772703698290408927E-2    , /*Hex  2^ -4   * -.F0BBA58481A942 */
a9     =  5.2170707402812969804E-2    , /*Hex  2^ -4   *  .D5B0F3A1AB13AB */
a10    = -4.4895863157820361210E-2    , /*Hex  2^ -4   * -.B7E4B97FD1048F */
a11    =  3.3006147437343875094E-2    , /*Hex  2^ -4   *  .8731743CF72D87 */
a12    = -1.4614844866464185439E-2    ; /*Hex  2^ -6   * -.EF731A2F3476D9 */
#else 	/* IEEE double */
athfhi =  4.6364760900080609352E-1    , /*Hex  2^ -2   *  1.DAC670561BB4F */
athflo =  4.6249969567426939759E-18   , /*Hex  2^-58   *  1.5543B8F253271 */
PIo4   =  7.8539816339744827900E-1    , /*Hex  2^ -1   *  1.921FB54442D18 */
at1fhi =  9.8279372324732905408E-1    , /*Hex  2^ -1   *  1.F730BD281F69B */
at1flo = -2.4407677060164810007E-17   , /*Hex  2^-56   * -1.C23DFEFEAE6B5 */
PIo2   =  1.5707963267948965580E0     , /*Hex  2^  0   *  1.921FB54442D18 */
PI     =  3.1415926535897931160E0     , /*Hex  2^  1   *  1.921FB54442D18 */
a1     =  3.3333333333333942106E-1    , /*Hex  2^ -2   *  1.55555555555C3 */
a2     = -1.9999999999979536924E-1    , /*Hex  2^ -3   * -1.9999999997CCD */
a3     =  1.4285714278004377209E-1    , /*Hex  2^ -3   *  1.24924921EC1D7 */
a4     = -1.1111110579344973814E-1    , /*Hex  2^ -4   * -1.C71C7059AF280 */
a5     =  9.0908906105474668324E-2    , /*Hex  2^ -4   *  1.745CE5AA35DB2 */
a6     = -7.6919217767468239799E-2    , /*Hex  2^ -4   * -1.3B0FA54BEC400 */
a7     =  6.6614695906082474486E-2    , /*Hex  2^ -4   *  1.10DA924597FFF */
a8     = -5.8358371008508623523E-2    , /*Hex  2^ -5   * -1.DE125FDDBD793 */
a9     =  4.9850617156082015213E-2    , /*Hex  2^ -5   *  1.9860524BDD807 */
a10    = -3.6700606902093604877E-2    , /*Hex  2^ -5   * -1.2CA6C04C6937A */
a11    =  1.6438029044759730479E-2    ; /*Hex  2^ -6   *  1.0D52174A1BB54 */
#endif

double atan2(y,x)
double  y,x;
{  
	static double zero=0, one=1, small=1.0E-9, big=1.0E18;
	double copysign(),logb(),scalb(),t,z,signy,signx,hi,lo;
D 3
	int finite(), k;
E 3
I 3
	int finite(), k,m;
E 3

    /* if x or y is NAN */
	if(x!=x) return(x); if(y!=y) return(y);

    /* copy down the sign of y and x */
	signy = copysign(one,y) ;  
	signx = copysign(one,x) ;  

    /* if x is 1.0, goto begin */
	if(x==1) { y=copysign(y,one); t=y; if(finite(t)) goto begin;}

    /* when y = 0 */
	if(y==zero) return((signx==one)?y:copysign(PI,signy));

    /* when x = 0 */
	if(x==zero) return(copysign(PIo2,signy));
	    
    /* when x is INF */
D 2
	if(!finite(x) && x==x)
	    if(!finite(y) && y==y) 
E 2
I 2
	if(!finite(x))
	    if(!finite(y)) 
E 2
		return(copysign((signx==one)?PIo4:3*PIo4,signy));
	    else
		return(copysign((signx==one)?zero:PI,signy));

    /* when y is INF */
D 2
	if(!finite(y) && y==y) return(copysign(PIo2,signy));
E 2
I 2
	if(!finite(y)) return(copysign(PIo2,signy));
E 2


    /* compute y/x */
	x=copysign(x,one); 
	y=copysign(y,one); 
D 3
	if((k=logb(y))-logb(x) > 60) t=big+big; 
E 3
I 3
	if((m=(k=logb(y))-logb(x)) > 60) t=big+big; 
	    else if(m < -80 ) t=y/x;
E 3
	    else { t = y/x ; y = scalb(y,-k); x=scalb(x,-k); }

    /* begin argument reduction */
begin:
	if (t < 2.4375) {		 

	/* truncate 4(t+1/16) to integer for branching */
	    k = 4 * (t+0.0625);
	    switch (k) {

	    /* t is in [0,7/16] */
	    case 0:                    
	    case 1:
		if (t < small) 
		    { big + small ;  /* raise inexact flag */
		      return (copysign((signx>zero)?t:PI-t,signy)); }

		hi = zero;  lo = zero;  break;

	    /* t is in [7/16,11/16] */
	    case 2:                    
		hi = athfhi; lo = athflo;
		z = x+x;
		t = ( (y+y) - x ) / ( z +  y ); break;

	    /* t is in [11/16,19/16] */
	    case 3:                    
	    case 4:
		hi = PIo4; lo = zero;
		t = ( y - x ) / ( x + y ); break;

	    /* t is in [19/16,39/16] */
	    default:                   
		hi = at1fhi; lo = at1flo;
		z = y-x; y=y+y+y; t = x+x;
		t = ( (z+z)-x ) / ( t + y ); break;
	    }
	}
	/* end of if (t < 2.4375) */

	else                           
	{
	    hi = PIo2; lo = zero;

	    /* t is in [2.4375, big] */
	    if (t <= big)  t = - x / y;

	    /* t is in [big, INF] */
	    else          
	      { big+small;	/* raise inexact flag */
		t = zero; }
	}
    /* end of argument reduction */

    /* compute atan(t) for t in [-.4375, .4375] */
	z = t*t;
D 4
#ifdef VAX
E 4
I 4
#if defined(VAX) || defined(TAHOE)
E 4
	z = t*(z*(a1+z*(a2+z*(a3+z*(a4+z*(a5+z*(a6+z*(a7+z*(a8+
			z*(a9+z*(a10+z*(a11+z*a12))))))))))));
#else	/* IEEE double */
	z = t*(z*(a1+z*(a2+z*(a3+z*(a4+z*(a5+z*(a6+z*(a7+z*(a8+
			z*(a9+z*(a10+z*a11)))))))))));
#endif
	z = lo - z; z += t; z += hi;

	return(copysign((signx>zero)?z:PI-z,signy));
}
E 1
