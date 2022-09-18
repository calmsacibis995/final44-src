h54967
s 00001/00001/00412
d D 8.2 93/11/30 16:27:42 mckusick 10 9
c lint
e
s 00002/00002/00411
d D 8.1 93/06/04 17:03:02 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00378/00171/00035
d D 5.5 92/12/16 18:06:00 bostic 8 7
c new versions from Peter McIlroy (derived from Sun Microsystems release)
e
s 00005/00004/00201
d D 5.4 91/04/20 14:21:37 bostic 7 6
c new copyright; att/bsd/shared
e
s 00018/00016/00187
d D 5.3 88/09/22 16:23:17 bostic 6 5
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00008/00003/00195
d D 5.2 88/04/29 12:18:42 bostic 5 4
c add Berkeley copyright; NOTE: this code is AT&T derived!
e
s 00000/00000/00198
d D 5.1 87/11/30 18:34:00 bostic 4 3
c tahoe release
e
s 00007/00007/00191
d D 1.3 87/07/13 19:20:36 zliu 3 2
c clean-ups.
e
s 00002/00001/00196
d D 1.2 85/09/11 23:54:06 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00197/00000/00000
d D 1.1 85/09/06 17:52:52 zliu 1 0
c date and time created 85/09/06 17:52:52 by zliu
e
u
U
t
T
I 5
D 7
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 8
 * Copyright (c) 1985 The Regents of the University of California.
E 8
I 8
D 9
 * Copyright (c) 1992 The Regents of the University of California.
E 8
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
 * %sccs.include.proprietary.c%
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
 */

E 5
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (ELEFUNT) %G%";
E 2
I 2
D 5
static char sccsid[] =
"%Z%%M%	4.2 (Berkeley) 8/21/85; %I% (ucb.elefunt) %G%";
E 2
D 3
#endif not lint
E 3
I 3
#endif	/* not lint */
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5
E 3

/*
D 8
	floating point Bessel's function
	of the first and second kinds
	of order zero
E 8
I 8
 * 16 December 1992
 * Minor modifications by Peter McIlroy to adapt non-IEEE architecture.
 */
E 8

D 8
	j0(x) returns the value of J0(x)
	for all real values of x.
E 8
I 8
/*
 * ====================================================
 * Copyright (C) 1992 by Sun Microsystems, Inc.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 *
 * ******************* WARNING ********************
 * This is an alpha version of SunPro's FDLIBM (Freely
 * Distributable Math Library) for IEEE double precision 
 * arithmetic. FDLIBM is a basic math library written
 * in C that runs on machines that conform to IEEE 
 * Standard 754/854. This alpha version is distributed 
 * for testing purpose. Those who use this software 
 * should report any bugs to 
 *
 *		fdlibm-comments@sunpro.eng.sun.com
 *
 * -- K.C. Ng, Oct 12, 1992
 * ************************************************
 */
E 8

D 8
	There are no error returns.
	Calls sin, cos, sqrt.
E 8
I 8
/* double j0(double x), y0(double x)
 * Bessel function of the first and second kinds of order zero.
 * Method -- j0(x):
 *	1. For tiny x, we use j0(x) = 1 - x^2/4 + x^4/64 - ...
 *	2. Reduce x to |x| since j0(x)=j0(-x),  and
 *	   for x in (0,2)
 *		j0(x) = 1-z/4+ z^2*R0/S0,  where z = x*x;
 *	   (precision:  |j0-1+z/4-z^2R0/S0 |<2**-63.67 )
 *	   for x in (2,inf)
 * 		j0(x) = sqrt(2/(pi*x))*(p0(x)*cos(x0)-q0(x)*sin(x0))
 * 	   where x0 = x-pi/4. It is better to compute sin(x0),cos(x0)
 *	   as follow:
 *		cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
 *			= 1/sqrt(2) * (cos(x) + sin(x))
 *		sin(x0) = sin(x)cos(pi/4)-cos(x)sin(pi/4)
 *			= 1/sqrt(2) * (sin(x) - cos(x))
 * 	   (To avoid cancellation, use
 *		sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
 * 	    to compute the worse one.)
 *	   
 *	3 Special cases
 *		j0(nan)= nan
 *		j0(0) = 1
 *		j0(inf) = 0
 *		
 * Method -- y0(x):
 *	1. For x<2.
 *	   Since 
 *		y0(x) = 2/pi*(j0(x)*(ln(x/2)+Euler) + x^2/4 - ...)
 *	   therefore y0(x)-2/pi*j0(x)*ln(x) is an even function.
 *	   We use the following function to approximate y0,
 *		y0(x) = U(z)/V(z) + (2/pi)*(j0(x)*ln(x)), z= x^2
 *	   where 
 *		U(z) = u0 + u1*z + ... + u6*z^6
 *		V(z) = 1  + v1*z + ... + v4*z^4
 *	   with absolute approximation error bounded by 2**-72.
 *	   Note: For tiny x, U/V = u0 and j0(x)~1, hence
 *		y0(tiny) = u0 + (2/pi)*ln(tiny), (choose tiny<2**-27)
 *	2. For x>=2.
 * 		y0(x) = sqrt(2/(pi*x))*(p0(x)*cos(x0)+q0(x)*sin(x0))
 * 	   where x0 = x-pi/4. It is better to compute sin(x0),cos(x0)
 *	   by the method mentioned above.
 *	3. Special cases: y0(0)=-inf, y0(x<0)=NaN, y0(inf)=0.
 */
E 8

D 8
	There is a niggling bug in J0 which
	causes errors up to 2e-16 for x in the
	interval [-8,8].
	The bug is caused by an inappropriate order
	of summation of the series.  rhm will fix it
	someday.
E 8
I 8
#include <math.h>
#include <float.h>
#if defined(vax) || defined(tahoe)
#define _IEEE	0
#else
#define _IEEE	1
#define infnan(x) (0.0)
#endif
E 8

D 8
	Coefficients are from Hart & Cheney.
	#5849 (19.22D)
	#6549 (19.25D)
	#6949 (19.41D)
E 8
I 8
static double pzero __P((double)), qzero __P((double));
E 8

D 8
	y0(x) returns the value of Y0(x)
	for positive real values of x.
	For x<=0, if on the VAX, error number EDOM is set and
	the reserved operand fault is generated;
	otherwise (an IEEE machine) an invalid operation is performed.
E 8
I 8
static double 
huge 	= 1e300,
zero    = 0.0,
one	= 1.0,
invsqrtpi= 5.641895835477562869480794515607725858441e-0001,
tpi	= 0.636619772367581343075535053490057448,
 		/* R0/S0 on [0, 2.00] */
r02 =   1.562499999999999408594634421055018003102e-0002,
r03 =  -1.899792942388547334476601771991800712355e-0004,
r04 =   1.829540495327006565964161150603950916854e-0006,
r05 =  -4.618326885321032060803075217804816988758e-0009,
s01 =   1.561910294648900170180789369288114642057e-0002,
s02 =   1.169267846633374484918570613449245536323e-0004,
s03 =   5.135465502073181376284426245689510134134e-0007,
s04 =   1.166140033337900097836930825478674320464e-0009;
E 8

D 8
	Calls sin, cos, sqrt, log, j0.
E 8
I 8
double
j0(x) 
	double x;
{
	double z, s,c,ss,cc,r,u,v;
E 8

D 8
	The values of Y0 have not been checked
	to more than ten places.
E 8
I 8
	if (!finite(x))
		if (_IEEE) return one/(x*x);
		else return (0);
	x = fabs(x);
	if (x >= 2.0) {	/* |x| >= 2.0 */
		s = sin(x);
		c = cos(x);
		ss = s-c;
		cc = s+c;
		if (x < .5 * DBL_MAX) {  /* make sure x+x not overflow */
		    z = -cos(x+x);
		    if ((s*c)<zero) cc = z/ss;
		    else 	    ss = z/cc;
		}
	/*
	 * j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
	 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
	 */
		if (_IEEE && x> 6.80564733841876927e+38) /* 2^129 */
			z = (invsqrtpi*cc)/sqrt(x);
		else {
		    u = pzero(x); v = qzero(x);
		    z = invsqrtpi*(u*cc-v*ss)/sqrt(x);
		}
		return z;
	}
	if (x < 1.220703125e-004) {		   /* |x| < 2**-13 */
	    if (huge+x > one) {			   /* raise inexact if x != 0 */
	        if (x < 7.450580596923828125e-009) /* |x|<2**-27 */
			return one;
	        else return (one - 0.25*x*x);
	    }
	}
	z = x*x;
	r =  z*(r02+z*(r03+z*(r04+z*r05)));
	s =  one+z*(s01+z*(s02+z*(s03+z*s04)));
	if (x < one) {			/* |x| < 1.00 */
	    return (one + z*(-0.25+(r/s)));
	} else {
	    u = 0.5*x;
	    return ((one+u)*(one-u)+z*(r/s));
	}
}
E 8

D 8
	Coefficients are from Hart & Cheney.
	#6245 (18.78D)
	#6549 (19.25D)
	#6949 (19.41D)
*/
E 8
I 8
static double
u00 =  -7.380429510868722527422411862872999615628e-0002,
u01 =   1.766664525091811069896442906220827182707e-0001,
u02 =  -1.381856719455968955440002438182885835344e-0002,
u03 =   3.474534320936836562092566861515617053954e-0004,
u04 =  -3.814070537243641752631729276103284491172e-0006,
u05 =   1.955901370350229170025509706510038090009e-0008,
u06 =  -3.982051941321034108350630097330144576337e-0011,
v01 =   1.273048348341237002944554656529224780561e-0002,
v02 =   7.600686273503532807462101309675806839635e-0005,
v03 =   2.591508518404578033173189144579208685163e-0007,
v04 =   4.411103113326754838596529339004302243157e-0010;
E 8

D 6
#include <math.h>
E 6
I 6
D 8
#include "mathimpl.h"
E 8
I 8
double
y0(x) 
	double x;
{
D 10
	double z, s,c,ss,cc,u,v,j0();
E 10
I 10
	double z, s, c, ss, cc, u, v;
E 10
    /* Y0(NaN) is NaN, y0(-inf) is Nan, y0(inf) is 0  */
	if (!finite(x))
		if (_IEEE)
			return (one/(x+x*x));
		else
			return (0);
        if (x == 0)
		if (_IEEE)	return (-one/zero);
		else		return(infnan(-ERANGE));
        if (x<0)
		if (_IEEE)	return (zero/zero);
		else		return (infnan(EDOM));
        if (x >= 2.00) {	/* |x| >= 2.0 */
        /* y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x0)+q0(x)*cos(x0))
         * where x0 = x-pi/4
         *      Better formula:
         *              cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
         *                      =  1/sqrt(2) * (sin(x) + cos(x))
         *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
         *                      =  1/sqrt(2) * (sin(x) - cos(x))
         * To avoid cancellation, use
         *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
         * to compute the worse one.
         */
                s = sin(x);
                c = cos(x);
                ss = s-c;
                cc = s+c;
	/*
	 * j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
	 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
	 */
                if (x < .5 * DBL_MAX) {  /* make sure x+x not overflow */
                    z = -cos(x+x);
                    if ((s*c)<zero) cc = z/ss;
                    else            ss = z/cc;
                }
                if (_IEEE && x > 6.80564733841876927e+38) /* > 2^129 */
			z = (invsqrtpi*ss)/sqrt(x);
                else {
                    u = pzero(x); v = qzero(x);
                    z = invsqrtpi*(u*ss+v*cc)/sqrt(x);
                }
                return z;
	}
	if (x <= 7.450580596923828125e-009) {		/* x < 2**-27 */
	    return (u00 + tpi*log(x));
	}
	z = x*x;
	u = u00+z*(u01+z*(u02+z*(u03+z*(u04+z*(u05+z*u06)))));
	v = one+z*(v01+z*(v02+z*(v03+z*v04)));
	return (u/v + tpi*(j0(x)*log(x)));
}
E 8

E 6
D 3
#ifdef VAX
E 3
I 3
D 8
#if defined(vax)||defined(tahoe)
E 3
#include <errno.h>
D 3
#else	/* IEEE double */
E 3
I 3
#else	/* defined(vax)||defined(tahoe) */
E 3
D 6
static double zero = 0.e0;
E 6
I 6
static const double zero = 0.e0;
E 6
D 3
#endif
E 3
I 3
#endif	/* defined(vax)||defined(tahoe) */
I 6

E 6
E 3
static double pzero, qzero;
D 6
static double tpi	= .6366197723675813430755350535e0;
static double pio4	= .7853981633974483096156608458e0;
static double p1[] = {
E 6
I 6

static const double tpi	= .6366197723675813430755350535e0;
static const double pio4	= .7853981633974483096156608458e0;
static const double p1[] = {
E 6
	0.4933787251794133561816813446e21,
	-.1179157629107610536038440800e21,
	0.6382059341072356562289432465e19,
	-.1367620353088171386865416609e18,
	0.1434354939140344111664316553e16,
	-.8085222034853793871199468171e13,
	0.2507158285536881945555156435e11,
	-.4050412371833132706360663322e8,
	0.2685786856980014981415848441e5,
E 8
I 8
/* The asymptotic expansions of pzero is
 *	1 - 9/128 s^2 + 11025/98304 s^4 - ...,	where s = 1/x.
 * For x >= 2, We approximate pzero by
 * 	pzero(x) = 1 + (R/S)
 * where  R = pr0 + pr1*s^2 + pr2*s^4 + ... + pr5*s^10
 * 	  S = 1 + ps0*s^2 + ... + ps4*s^10
 * and
 *	| pzero(x)-1-R/S | <= 2  ** ( -60.26)
 */
static double pr8[6] = { /* for x in [inf, 8]=1/[0,0.125] */
   0.0,
  -7.031249999999003994151563066182798210142e-0002,
  -8.081670412753498508883963849859423939871e+0000,
  -2.570631056797048755890526455854482662510e+0002,
  -2.485216410094288379417154382189125598962e+0003,
  -5.253043804907295692946647153614119665649e+0003,
E 8
};
D 6
static double q1[] = {
E 6
I 6
D 8
static const double q1[] = {
E 6
	0.4933787251794133562113278438e21,
	0.5428918384092285160200195092e19,
	0.3024635616709462698627330784e17,
	0.1127756739679798507056031594e15,
	0.3123043114941213172572469442e12,
	0.6699987672982239671814028660e9,
	0.1114636098462985378182402543e7,
	0.1363063652328970604442810507e4,
	1.0
E 8
I 8
static double ps8[5] = {
   1.165343646196681758075176077627332052048e+0002,
   3.833744753641218451213253490882686307027e+0003,
   4.059785726484725470626341023967186966531e+0004,
   1.167529725643759169416844015694440325519e+0005,
   4.762772841467309430100106254805711722972e+0004,
E 8
};
D 6
static double p2[] = {
E 6
I 6
D 8
static const double p2[] = {
E 6
	0.5393485083869438325262122897e7,
	0.1233238476817638145232406055e8,
	0.8413041456550439208464315611e7,
	0.2016135283049983642487182349e7,
	0.1539826532623911470917825993e6,
	0.2485271928957404011288128951e4,
	0.0,
E 8
I 8

static double pr5[6] = { /* for x in [8,4.5454]=1/[0.125,0.22001] */
  -1.141254646918944974922813501362824060117e-0011,
  -7.031249408735992804117367183001996028304e-0002,
  -4.159610644705877925119684455252125760478e+0000,
  -6.767476522651671942610538094335912346253e+0001,
  -3.312312996491729755731871867397057689078e+0002,
  -3.464333883656048910814187305901796723256e+0002,
E 8
};
D 6
static double q2[] = {
E 6
I 6
D 8
static const double q2[] = {
E 6
	0.5393485083869438325560444960e7,
	0.1233831022786324960844856182e8,
	0.8426449050629797331554404810e7,
	0.2025066801570134013891035236e7,
	0.1560017276940030940592769933e6,
	0.2615700736920839685159081813e4,
	1.0,
E 8
I 8
static double ps5[5] = {
   6.075393826923003305967637195319271932944e+0001,
   1.051252305957045869801410979087427910437e+0003,
   5.978970943338558182743915287887408780344e+0003,
   9.625445143577745335793221135208591603029e+0003,
   2.406058159229391070820491174867406875471e+0003,
E 8
};
D 6
static double p3[] = {
E 6
I 6
D 8
static const double p3[] = {
E 6
	-.3984617357595222463506790588e4,
	-.1038141698748464093880530341e5,
	-.8239066313485606568803548860e4,
	-.2365956170779108192723612816e4,
	-.2262630641933704113967255053e3,
	-.4887199395841261531199129300e1,
	0.0,
E 8
I 8

static double pr3[6] = {/* for x in [4.547,2.8571]=1/[0.2199,0.35001] */
  -2.547046017719519317420607587742992297519e-0009,
  -7.031196163814817199050629727406231152464e-0002,
  -2.409032215495295917537157371488126555072e+0000,
  -2.196597747348830936268718293366935843223e+0001,
  -5.807917047017375458527187341817239891940e+0001,
  -3.144794705948885090518775074177485744176e+0001,
E 8
};
D 6
static double q3[] = {
E 6
I 6
D 8
static const double q3[] = {
E 6
	0.2550155108860942382983170882e6,
	0.6667454239319826986004038103e6,
	0.5332913634216897168722255057e6,
	0.1560213206679291652539287109e6,
	0.1570489191515395519392882766e5,
	0.4087714673983499223402830260e3,
	1.0,
E 8
I 8
static double ps3[5] = {
   3.585603380552097167919946472266854507059e+0001,
   3.615139830503038919981567245265266294189e+0002,
   1.193607837921115243628631691509851364715e+0003,
   1.127996798569074250675414186814529958010e+0003,
   1.735809308133357510239737333055228118910e+0002,
E 8
};
D 6
static double p4[] = {
E 6
I 6
D 8
static const double p4[] = {
E 6
	-.2750286678629109583701933175e20,
	0.6587473275719554925999402049e20,
	-.5247065581112764941297350814e19,
	0.1375624316399344078571335453e18,
	-.1648605817185729473122082537e16,
	0.1025520859686394284509167421e14,
	-.3436371222979040378171030138e11,
	0.5915213465686889654273830069e8,
	-.4137035497933148554125235152e5,
E 8
I 8

static double pr2[6] = {/* for x in [2.8570,2]=1/[0.3499,0.5] */
  -8.875343330325263874525704514800809730145e-0008,
  -7.030309954836247756556445443331044338352e-0002,
  -1.450738467809529910662233622603401167409e+0000,
  -7.635696138235277739186371273434739292491e+0000,
  -1.119316688603567398846655082201614524650e+0001,
  -3.233645793513353260006821113608134669030e+0000,
E 8
};
D 6
static double q4[] = {
E 6
I 6
D 8
static const double q4[] = {
E 6
	0.3726458838986165881989980e21,
	0.4192417043410839973904769661e19,
	0.2392883043499781857439356652e17,
	0.9162038034075185262489147968e14,
	0.2613065755041081249568482092e12,
	0.5795122640700729537480087915e9,
	0.1001702641288906265666651753e7,
	0.1282452772478993804176329391e4,
	1.0,
E 8
I 8
static double ps2[5] = {
   2.222029975320888079364901247548798910952e+0001,
   1.362067942182152109590340823043813120940e+0002,
   2.704702786580835044524562897256790293238e+0002,
   1.538753942083203315263554770476850028583e+0002,
   1.465761769482561965099880599279699314477e+0001,
E 8
};

I 6
D 8
static void asympt();
E 8
I 8
static double pzero(x)
	double x;
{
	double *p,*q,z,r,s;
	if (x >= 8.00)			   {p = pr8; q= ps8;}
	else if (x >= 4.54545211791992188) {p = pr5; q= ps5;}
	else if (x >= 2.85714149475097656) {p = pr3; q= ps3;}
	else if (x >= 2.00)		   {p = pr2; q= ps2;}
	z = one/(x*x);
	r = p[0]+z*(p[1]+z*(p[2]+z*(p[3]+z*(p[4]+z*p[5]))));
	s = one+z*(q[0]+z*(q[1]+z*(q[2]+z*(q[3]+z*q[4]))));
	return one+ r/s;
}
		
E 8

E 6
D 8
double
j0(arg) double arg;{
	double argsq, n, d;
D 6
	double sin(), cos(), sqrt();
E 6
	int i;
E 8
I 8
/* For x >= 8, the asymptotic expansions of qzero is
 *	-1/8 s + 75/1024 s^3 - ..., where s = 1/x.
 * We approximate pzero by
 * 	qzero(x) = s*(-1.25 + (R/S))
 * where  R = qr0 + qr1*s^2 + qr2*s^4 + ... + qr5*s^10
 * 	  S = 1 + qs0*s^2 + ... + qs5*s^12
 * and
 *	| qzero(x)/s +1.25-R/S | <= 2  ** ( -61.22)
 */
static double qr8[6] = { /* for x in [inf, 8]=1/[0,0.125] */
   0.0,
   7.324218749999350414479738504551775297096e-0002,
   1.176820646822526933903301695932765232456e+0001,
   5.576733802564018422407734683549251364365e+0002,
   8.859197207564685717547076568608235802317e+0003,
   3.701462677768878501173055581933725704809e+0004,
};
static double qs8[6] = {
   1.637760268956898345680262381842235272369e+0002,
   8.098344946564498460163123708054674227492e+0003,
   1.425382914191204905277585267143216379136e+0005,
   8.033092571195144136565231198526081387047e+0005,
   8.405015798190605130722042369969184811488e+0005,
  -3.438992935378666373204500729736454421006e+0005,
};
E 8

D 8
	if(arg < 0.) arg = -arg;
	if(arg > 8.){
		asympt(arg);
		n = arg - pio4;
		return(sqrt(tpi/arg)*(pzero*cos(n) - qzero*sin(n)));
	}
	argsq = arg*arg;
	for(n=0,d=0,i=8;i>=0;i--){
		n = n*argsq + p1[i];
		d = d*argsq + q1[i];
	}
	return(n/d);
}
E 8
I 8
static double qr5[6] = { /* for x in [8,4.5454]=1/[0.125,0.22001] */
   1.840859635945155400568380711372759921179e-0011,
   7.324217666126847411304688081129741939255e-0002,
   5.835635089620569401157245917610984757296e+0000,
   1.351115772864498375785526599119895942361e+0002,
   1.027243765961641042977177679021711341529e+0003,
   1.989977858646053872589042328678602481924e+0003,
};
static double qs5[6] = {
   8.277661022365377058749454444343415524509e+0001,
   2.077814164213929827140178285401017305309e+0003,
   1.884728877857180787101956800212453218179e+0004,
   5.675111228949473657576693406600265778689e+0004,
   3.597675384251145011342454247417399490174e+0004,
  -5.354342756019447546671440667961399442388e+0003,
};
E 8

D 8
double
y0(arg) double arg;{
	double argsq, n, d;
D 6
	double sin(), cos(), sqrt(), log(), j0();
E 6
	int i;
E 8
I 8
static double qr3[6] = {/* for x in [4.547,2.8571]=1/[0.2199,0.35001] */
   4.377410140897386263955149197672576223054e-0009,
   7.324111800429115152536250525131924283018e-0002,
   3.344231375161707158666412987337679317358e+0000,
   4.262184407454126175974453269277100206290e+0001,
   1.708080913405656078640701512007621675724e+0002,
   1.667339486966511691019925923456050558293e+0002,
};
static double qs3[6] = {
   4.875887297245871932865584382810260676713e+0001,
   7.096892210566060535416958362640184894280e+0002,
   3.704148226201113687434290319905207398682e+0003,
   6.460425167525689088321109036469797462086e+0003,
   2.516333689203689683999196167394889715078e+0003,
  -1.492474518361563818275130131510339371048e+0002,
};
E 8

D 8
	if(arg <= 0.){
D 3
#ifdef VAX
E 3
I 3
#if defined(vax)||defined(tahoe)
E 3
D 6
		extern double infnan();
E 6
		return(infnan(EDOM));		/* NaN */
D 3
#else	/* IEEE double */
E 3
I 3
#else	/* defined(vax)||defined(tahoe) */
E 3
		return(zero/zero);	/* IEEE machines: invalid operation */
D 3
#endif
E 3
I 3
#endif	/* defined(vax)||defined(tahoe) */
E 3
	}
	if(arg > 8.){
		asympt(arg);
		n = arg - pio4;
		return(sqrt(tpi/arg)*(pzero*sin(n) + qzero*cos(n)));
	}
	argsq = arg*arg;
	for(n=0,d=0,i=8;i>=0;i--){
		n = n*argsq + p4[i];
		d = d*argsq + q4[i];
	}
	return(n/d + tpi*j0(arg)*log(arg));
}
E 8
I 8
static double qr2[6] = {/* for x in [2.8570,2]=1/[0.3499,0.5] */
   1.504444448869832780257436041633206366087e-0007,
   7.322342659630792930894554535717104926902e-0002,
   1.998191740938159956838594407540292600331e+0000,
   1.449560293478857407645853071687125850962e+0001,
   3.166623175047815297062638132537957315395e+0001,
   1.625270757109292688799540258329430963726e+0001,
};
static double qs2[6] = {
   3.036558483552191922522729838478169383969e+0001,
   2.693481186080498724211751445725708524507e+0002,
   8.447837575953201460013136756723746023736e+0002,
   8.829358451124885811233995083187666981299e+0002,
   2.126663885117988324180482985363624996652e+0002,
  -5.310954938826669402431816125780738924463e+0000,
};
E 8

D 6
static
E 6
I 6
D 8
static void
E 6
asympt(arg) double arg;{
	double zsq, n, d;
	int i;
	zsq = 64./(arg*arg);
	for(n=0,d=0,i=6;i>=0;i--){
		n = n*zsq + p2[i];
		d = d*zsq + q2[i];
	}
	pzero = n/d;
	for(n=0,d=0,i=6;i>=0;i--){
		n = n*zsq + p3[i];
		d = d*zsq + q3[i];
	}
	qzero = (8./arg)*(n/d);
E 8
I 8
static double qzero(x)
	double x;
{
	double *p,*q, s,r,z;
	if (x >= 8.00)			   {p = qr8; q= qs8;}
	else if (x >= 4.54545211791992188) {p = qr5; q= qs5;}
	else if (x >= 2.85714149475097656) {p = qr3; q= qs3;}
	else if (x >= 2.00)		   {p = qr2; q= qs2;}
	z = one/(x*x);
	r = p[0]+z*(p[1]+z*(p[2]+z*(p[3]+z*(p[4]+z*p[5]))));
	s = one+z*(q[0]+z*(q[1]+z*(q[2]+z*(q[3]+z*(q[4]+z*q[5])))));
	return (-.125 + r/s)/x;
E 8
}
E 1
