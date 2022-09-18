h55989
s 00002/00002/00368
d D 8.1 93/06/04 17:01:09 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00368
d D 5.8 93/01/10 12:47:50 bostic 10 9
c exp__D, exp__E, log__D, and log__L are private; prepend leading "__"
e
s 00003/00001/00367
d D 5.7 92/12/16 22:37:48 mcilroy 9 8
c replaced missing lines in comment section.
e
s 00002/00002/00366
d D 5.6 92/12/14 19:31:00 mcilroy 8 7
c 
e
s 00135/00110/00233
d D 5.5 92/12/14 19:23:54 mcilroy 7 6
c replaced expansions for x in [1.25, 4], [4, 30]
e
s 00319/00100/00024
d D 5.4 92/12/02 15:08:13 bostic 6 5
c new version from Peter McIlroy
e
s 00005/00004/00119
d D 5.3 91/04/20 14:21:36 bostic 5 4
c new copyright; att/bsd/shared
e
s 00009/00001/00114
d D 5.2 88/04/29 12:20:35 bostic 4 3
c add Berkeley copyright; NOTE: this code is AT&T derived!
e
s 00000/00000/00115
d D 5.1 87/11/30 18:33:55 bostic 3 2
c tahoe release
e
s 00001/00001/00114
d D 1.2 85/09/11 23:53:43 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00115/00000/00000
d D 1.1 85/09/06 17:52:44 zliu 1 0
c date and time created 85/09/06 17:52:44 by zliu
e
u
U
t
T
I 1
D 2
/* %W% (ELEFUNT) %G% */
E 2
I 2
D 4
/*	%Z%%M%	4.2 (Berkeley) 8/21/85; %I% (ucb.elefunt) %G% */
E 4
I 4
D 5
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 6
 * Copyright (c) 1985 The Regents of the University of California.
E 6
I 6
D 11
 * Copyright (c) 1992 The Regents of the University of California.
E 6
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 6
 * %sccs.include.proprietary.c%
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4
E 2

D 7
/*
D 6
	C program for floating point error function
E 6
I 6
 * ====================================================
 * Copyright (C) 1992 by Sun Microsystems, Inc.
E 7
I 7
/* Modified Nov 30, 1992 P. McILROY:
 *	Replaced expansions for x >= 1.25 (error 1.7ulp vs ~6ulp)
 * Replaced even+odd with direct calculation for x < .84375,
 * to avoid destructive cancellation.
E 7
 *
D 7
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
E 7
I 7
 * Performance of erfc(x):
 * In 300000 trials in the range [.83, .84375] the
 * maximum observed error was 3.6ulp.
E 7
 *
D 7
 * ******************* WARNING ********************
 * This is an alpha version of SunPro's FDLIBM (Freely
 * Distributable Math Library) for IEEE double precision 
 * arithmetic. FDLIBM is a basic math library written
 * in C that runs on machines that conform to IEEE 
 * Standard 754/854. This alpha version is distributed 
 * for testing purpose. Those who use this software 
 * should report any bugs to 
E 7
I 7
 * In [.84735,1.25] the maximum observed error was <2.5ulp in
 * 100000 runs in the range [1.2, 1.25].
E 7
 *
D 7
 *		fdlibm-comments@sunpro.eng.sun.com
 *
 * -- K.C. Ng, Oct 12, 1992
 * ************************************************
E 7
I 7
 * In [1.25,26] (Not including subnormal results)
 * the error is < 1.7ulp.
E 7
 */
E 6

D 6
	erf(x) returns the error function of its argument
	erfc(x) returns 1.0-erf(x)
E 6
I 6
D 7
/* Modified Nov 30, 1992 P. McILROY:
 *	Replaced expansion for x > 6
 *	Add #ifdef's for vax/tahoe.
 */
E 6

E 7
D 6
	erf(x) is defined by
	${2 over sqrt(pi)} int from 0 to x e sup {-t sup 2} dt$
E 6
I 6
/* double erf(double x)
 * double erfc(double x)
 *			     x
 *		      2      |\
 *     erf(x)  =  ---------  | exp(-t*t)dt
 *		   sqrt(pi) \|
 *			     0
 *
 *     erfc(x) =  1-erf(x)
 *
 * Method:
 *      1. Reduce x to |x| by erf(-x) = -erf(x)
 *	2. For x in [0, 0.84375]
 *	    erf(x)  = x + x*P(x^2)
 *          erfc(x) = 1 - erf(x)           if x<=0.25
 *                  = 0.5 + ((0.5-x)-x*P)  if x in [0.25,0.84375]
 *	   where
 *			2		 2	  4		  20  
 *              P =  P(x ) = (p0 + p1 * x + p2 * x + ... + p10 * x  )
 * 	   is an approximation to (erf(x)-x)/x with precision
 *
 *						 -56.45
 *			| P - (erf(x)-x)/x | <= 2
 *	
 *
 *	   Remark. The formula is derived by noting
 *          erf(x) = (2/sqrt(pi))*(x - x^3/3 + x^5/10 - x^7/42 + ....)
 *	   and that
 *          2/sqrt(pi) = 1.128379167095512573896158903121545171688
I 9
 *	   is close to one. The interval is chosen because the fixed
E 9
D 7
 *	   is close to one. The interval is chosen because the fixed
E 7
 *	   point of erf(x) is near 0.6174 (i.e., erf(x)=x when x is
 *	   near 0.6174), and by some experiment, 0.84375 is chosen to
 * 	   guarantee the error is less than one ulp for erf.
 *
 *      3. For x in [0.84375,1.25], let s = x - 1, and
 *         c = 0.84506291151 rounded to single (24 bits)
 *         	erf(x)  = c  + P1(s)/Q1(s)
 *         	erfc(x) = (1-c)  - P1(s)/Q1(s)
 *         	|P1/Q1 - (erf(x)-c)| <= 2**-59.06
 *	   Remark: here we use the taylor series expansion at x=1.
 *		erf(1+s) = erf(1) + s*Poly(s)
 *			 = 0.845.. + P1(s)/Q1(s)
 *	   That is, we use rational approximation to approximate
 *			erf(1+s) - (c = (single)0.84506291151)
 *	   Note that |P1/Q1|< 0.078 for x in [0.84375,1.25]
 *	   where 
D 9
 *		P1(s) = degree 7 poly in s
E 9
I 9
 *		P1(s) = degree 6 poly in s
 *		Q1(s) = degree 6 poly in s
E 9
 *
D 7
 *      4. For x in [1.25,6],
 *         	erf(x)  = 1 - erfc(x)
 *		erfc(x) = exp(-x*x)*(1/x)*R1(1/x)/S1(1/x)
 *	where 
 *		R1(y) = degree 7 poly in y, (y=1/x)
 *		S1(y) = degree 8 poly in y
E 7
I 7
 *	4. For x in [1.25, 2]; [2, 4]
 *         	erf(x)  = 1.0 - tiny
 *		erfc(x)	= (1/x)exp(-x*x-(.5*log(pi) -.5z + R(z)/S(z))
E 7
 *
D 7
 *      5. For x in [6,28]
E 7
I 7
 *	Where z = 1/(x*x), R is degree 9, and S is degree 3;
 *	
 *      5. For x in [4,28]
E 7
 *         	erf(x)  = 1.0 - tiny
D 7
 *		erfc(x)	= (1/x)exp(-x*x-(.5*log(pi)+eps) + zP(z))
E 7
I 7
 *		erfc(x)	= (1/x)exp(-x*x-(.5*log(pi)+eps + zP(z))
E 7
 *
D 7
 *	Where P is degree 9 polynomial in z = 1/(x*x)
E 7
I 7
 *	Where P is degree 14 polynomial in 1/(x*x).
E 7
 *
 *      Notes:
 *	   Here 4 and 5 make use of the asymptotic series
 *			  exp(-x*x)
 *		erfc(x) ~ ---------- * ( 1 + Poly(1/x^2) );
 *			  x*sqrt(pi)
 *
 *		where for z = 1/(x*x)
 *		P(z) ~ z/2*(-1 + z*3/2*(1 + z*5/2*(-1 + z*7/2*(1 +...))))
 *
 *	   Thus we use rational approximation to approximate
D 7
 *              erfc*x*exp(x*x) ~ 1/sqrt(pi) 
E 7
I 7
 *              erfc*x*exp(x*x) ~ 1/sqrt(pi);
E 7
 *
 *		The error bound for the target function, G(z) for
D 7
 *		case 5 is
 * 		|eps + 1/(x*x)P(1/x*x) - G(x)|	< 2**(-58.34)
 *		For case 4,
 *      	|R2/S2 - erfc*x*exp(x*x)|	< 2**(-61.52)
E 7
I 7
 *		the interval
 *		[4, 28]:
 * 		|eps + 1/(z)P(z) - G(z)| < 2**(-56.61)
 *		for [2, 4]:
 *      	|R(z)/S(z) - G(z)|	 < 2**(-58.24)
 *		for [1.25, 2]:
 *		|R(z)/S(z) - G(z)|	 < 2**(-58.12)
E 7
 *
 *      6. For inf > x >= 28
 *         	erf(x)  = 1 - tiny  (raise inexact)
 *         	erfc(x) = tiny*tiny (raise underflow)
 *
 *      7. Special cases:
 *         	erf(0)  = 0, erf(inf)  = 1, erf(-inf) = -1,
 *         	erfc(0) = 1, erfc(inf) = 0, erfc(-inf) = 2, 
 *	   	erfc/erf(NaN) is NaN
 */
E 6

D 6
	the entry for erfc is provided because of the
	extreme loss of relative accuracy if erf(x) is
	called for large x and the result subtracted
	from 1. (e.g. for x= 10, 12 places are lost).
E 6
I 6
#if defined(vax) || defined(tahoe)
#define _IEEE	0
#define TRUNC(x) (double) (float) (x)
#else
#define _IEEE	1
#define TRUNC(x) *(((int *) &x) + 1) &= 0xf8000000
#define infnan(x) 0.0
#endif
E 6

D 6
	There are no error returns.
E 6
I 6
#ifdef _IEEE_LIBM
/*
 * redefining "___function" to "function" in _IEEE_LIBM mode
 */
#include "ieee_libm.h"
#endif
E 6

D 6
	Calls exp.
E 6
I 6
static double
tiny	    = 1e-300,
half	    = 0.5,
one	    = 1.0,
two	    = 2.0,
c 	    = 8.45062911510467529297e-01, /* (float)0.84506291151 */
/*
D 7
 * Coefficients for approximation to  erf on [0,0.84375]
E 7
I 7
 * Coefficients for approximation to erf in [0,0.84375]
E 7
 */
p0t8 = 1.02703333676410051049867154944018394163280,
p0 =   1.283791670955125638123339436800229927041e-0001,
p1 =  -3.761263890318340796574473028946097022260e-0001,
p2 =   1.128379167093567004871858633779992337238e-0001,
p3 =  -2.686617064084433642889526516177508374437e-0002,
p4 =   5.223977576966219409445780927846432273191e-0003,
p5 =  -8.548323822001639515038738961618255438422e-0004,
p6 =   1.205520092530505090384383082516403772317e-0004,
p7 =  -1.492214100762529635365672665955239554276e-0005,
p8 =   1.640186161764254363152286358441771740838e-0006,
p9 =  -1.571599331700515057841960987689515895479e-0007,
D 7
p10=   1.073087585213621540635426191486561494058e-0008,
E 7
I 7
p10=   1.073087585213621540635426191486561494058e-0008;
E 7
/*
D 7
 * Coefficients for approximation to  erf  in [0.84375,1.25] 
E 7
I 7
 * Coefficients for approximation to erf in [0.84375,1.25] 
E 7
 */
I 7
static double
E 7
pa0 =  -2.362118560752659485957248365514511540287e-0003,
pa1 =   4.148561186837483359654781492060070469522e-0001,
pa2 =  -3.722078760357013107593507594535478633044e-0001,
pa3 =   3.183466199011617316853636418691420262160e-0001,
pa4 =  -1.108946942823966771253985510891237782544e-0001,
pa5 =   3.547830432561823343969797140537411825179e-0002,
pa6 =  -2.166375594868790886906539848893221184820e-0003,
qa1 =   1.064208804008442270765369280952419863524e-0001,
qa2 =   5.403979177021710663441167681878575087235e-0001,
qa3 =   7.182865441419627066207655332170665812023e-0002,
qa4 =   1.261712198087616469108438860983447773726e-0001,
qa5 =   1.363708391202905087876983523620537833157e-0002,
D 7
qa6 =   1.198449984679910764099772682882189711364e-0002,
E 7
I 7
qa6 =   1.198449984679910764099772682882189711364e-0002;
E 7
/*
D 7
 * Coefficients for approximation to  erfc in [1.25,6]
 */
ra0 =   5.641895806197543833169694096883621225329e-0001,
ra1 =   7.239004794325021293310782759791744583987e+0000,
ra2 =   4.615482605646378370356340497765510677914e+0001,
ra3 =   1.831130716384318567879039478746072928548e+0002,
ra4 =   4.827304689401256945023566678442020977744e+0002,
ra5 =   8.443683805001379929687313735294340282751e+0002,
ra6 =   9.151771804289399937165800774604677980269e+0002,
ra7 =   4.884236881266866025539987843147838061930e+0002,
sa1 =   1.283080158932067675016971332625972882793e+0001,
sa2 =   8.230730944985601552133528541648529041935e+0001,
sa3 =   3.309746710535947168967275132570416337810e+0002,
sa4 =   8.960238586988354676031385802384985611536e+0002,
sa5 =   1.652440076836585407285764071805622271834e+0003,
sa6 =   2.010492426273281289533320672757992672142e+0003,
sa7 =   1.466304171232599681829476641652969136592e+0003,
sa8 =   4.884237022526160104676542187698268809111e+0002;
E 7
I 7
 * log(sqrt(pi)) for large x expansions.
 * The tail (lsqrtPI_lo) is included in the rational
 * approximations.
*/
static double
   lsqrtPI_hi = .5723649429247000819387380943226;
E 7
/*
D 7
 * Coefficients for approximation to  erfc in [6,28]
E 7
I 7
 * lsqrtPI_lo = .000000000000000005132975581353913;
 *
 * Coefficients for approximation to erfc in [2, 4]
*/
static double
rb0  =	-1.5306508387410807582e-010,	/* includes lsqrtPI_lo */
rb1  =	 2.15592846101742183841910806188e-008,
rb2  =	 6.24998557732436510470108714799e-001,
rb3  =	 8.24849222231141787631258921465e+000,
rb4  =	 2.63974967372233173534823436057e+001,
rb5  =	 9.86383092541570505318304640241e+000,
rb6  =	-7.28024154841991322228977878694e+000,
rb7  =	 5.96303287280680116566600190708e+000,
rb8  =	-4.40070358507372993983608466806e+000,
rb9  =	 2.39923700182518073731330332521e+000,
rb10 =	-6.89257464785841156285073338950e-001,
sb1  =	 1.56641558965626774835300238919e+001,
sb2  =	 7.20522741000949622502957936376e+001,
sb3  =	 9.60121069770492994166488642804e+001;
/*
 * Coefficients for approximation to erfc in [1.25, 2]
*/
static double
rc0  =	-2.47925334685189288817e-007,	/* includes lsqrtPI_lo */
rc1  =	 1.28735722546372485255126993930e-005,
rc2  =	 6.24664954087883916855616917019e-001,
rc3  =	 4.69798884785807402408863708843e+000,
rc4  =	 7.61618295853929705430118701770e+000,
rc5  =	 9.15640208659364240872946538730e-001,
rc6  =	-3.59753040425048631334448145935e-001,
rc7  =	 1.42862267989304403403849619281e-001,
rc8  =	-4.74392758811439801958087514322e-002,
rc9  =	 1.09964787987580810135757047874e-002,
rc10 =	-1.28856240494889325194638463046e-003,
sc1  =	 9.97395106984001955652274773456e+000,
sc2  =	 2.80952153365721279953959310660e+001,
sc3  =	 2.19826478142545234106819407316e+001;
/*
 * Coefficients for approximation to  erfc in [4,28]
E 7
 */
D 7
#define a0_hi	-0.5723649429247001929610405568		/* ~-.5log(pi) */
#define a0_lo	-0.0000000000000000189783711362898601
E 7
I 7
static double
rd0  =	-2.1491361969012978677e-016,	/* includes lsqrtPI_lo */
rd1  =	-4.99999999999640086151350330820e-001,
rd2  =	 6.24999999772906433825880867516e-001,
rd3  =	-1.54166659428052432723177389562e+000,
rd4  =	 5.51561147405411844601985649206e+000,
rd5  =	-2.55046307982949826964613748714e+001,
rd6  =	 1.43631424382843846387913799845e+002,
rd7  =	-9.45789244999420134263345971704e+002,
rd8  =	 6.94834146607051206956384703517e+003,
rd9  =	-5.27176414235983393155038356781e+004,
rd10 =	 3.68530281128672766499221324921e+005,
rd11 =	-2.06466642800404317677021026611e+006,
rd12 =	 7.78293889471135381609201431274e+006,
rd13 =	-1.42821001129434127360582351685e+007;
E 7
E 6

D 6
	Coefficients for large x are #5667 from Hart & Cheney (18.72D).
*/
E 6
I 6
D 7
#define P0	-4.99999999999749700219098258458e-0001	/* -1	   /2 	*/
#define P1	 6.24999999807451578348604925850e-0001	/* 5/2	   /4	*/
#define P2	-1.54166659013994022942029005208e+0001	/* -37/3   /8	*/
#define P3	 5.51560710872094706047619183664e+0001	/* 353/4   /16	*/
#define P4	-2.55036053070125880992691236315e+0002	/* -4081/5 /32	*/
#define P5	 1.43505282730286381820405949838e+0002	/* 55205/6 /64	*/
#define P6	-9.36421869861889035746571607888e+0002	/* ....etc....	*/
#define P7	 6.51030087738772090233396738768e+0003	
#define P8	-3.98835620275180117459967732430e+0004
#define P9	 1.44460450428346201078966259956e+0005
E 6

D 6
#define M 7
#define N 9
static double torp = 1.1283791670955125738961589031;
static double p1[] = {
	0.804373630960840172832162e5,
	0.740407142710151470082064e4,
	0.301782788536507577809226e4,
	0.380140318123903008244444e2,
	0.143383842191748205576712e2,
	-.288805137207594084924010e0,
	0.007547728033418631287834e0,
};
static double q1[]  = {
	0.804373630960840172826266e5,
	0.342165257924628539769006e5,
	0.637960017324428279487120e4,
	0.658070155459240506326937e3,
	0.380190713951939403753468e2,
	0.100000000000000000000000e1,
	0.0,
};
static double p2[]  = {
	0.18263348842295112592168999e4,
	0.28980293292167655611275846e4,
	0.2320439590251635247384768711e4,
	0.1143262070703886173606073338e4,
	0.3685196154710010637133875746e3,
	0.7708161730368428609781633646e2,
	0.9675807882987265400604202961e1,
	0.5641877825507397413087057563e0,
	0.0,
};
static double q2[]  = {
	0.18263348842295112595576438e4,
	0.495882756472114071495438422e4,
	0.60895424232724435504633068e4,
	0.4429612803883682726711528526e4,
	0.2094384367789539593790281779e4,
	0.6617361207107653469211984771e3,
	0.1371255960500622202878443578e3,
	0.1714980943627607849376131193e2,
	1.0,
};
E 6

D 6
double
erf(arg) double arg;{
	double erfc();
	int sign;
	double argsq;
	double d, n;
	int i;

	sign = 1;
	if(arg < 0.){
		arg = -arg;
		sign = -1;
E 6
I 6
double erf(x)
E 7
I 7
D 8
double nerf(x)
E 8
I 8
double erf(x)
E 8
E 7
	double x;
{
D 7
	double R,S,P,Q,ax,s,y,z,odd,even,r,fabs(),exp();
E 7
I 7
	double R,S,P,Q,ax,s,y,z,r,fabs(),exp();
E 7
	if(!finite(x)) {		/* erf(nan)=nan */
	    if (isnan(x))
		return(x);
	    return (x > 0 ? one : -one); /* erf(+/-inf)= +/-1 */
E 6
	}
D 6
	if(arg < 0.5){
		argsq = arg*arg;
		for(n=0,d=0,i=M-1; i>=0; i--){
			n = n*argsq + p1[i];
			d = d*argsq + q1[i];
		}
		return(sign*torp*arg*n/d);
E 6
I 6
	if ((ax = x) < 0)
		ax = - ax;
	if (ax < .84375) {
	    if (ax < 3.7e-09) {
		if (ax < 1.0e-308)
		    return 0.125*(8.0*x+p0t8*x);  /*avoid underflow */
		return x + p0*x;
	    }
	    y = x*x;
D 7
	    z = y*y;
	    even = z*(p2+z*(p4+z*(p6+z*(p8+z*p10))));
	    odd  = p1+z*(p3+z*(p5+z*(p7+z*p9)));
	    r = y*odd+even;
E 7
I 7
	    r = y*(p1+y*(p2+y*(p3+y*(p4+y*(p5+
			y*(p6+y*(p7+y*(p8+y*(p9+y*p10)))))))));
E 7
	    return x + x*(p0+r);
E 6
	}
D 6
	if(arg >= 10.)
		return(sign*1.);
	return(sign*(1. - erfc(arg)));
E 6
I 6
	if (ax < 1.25) {		/* 0.84375 <= |x| < 1.25 */
	    s = fabs(x)-one;
	    P = pa0+s*(pa1+s*(pa2+s*(pa3+s*(pa4+s*(pa5+s*pa6)))));
	    Q = one+s*(qa1+s*(qa2+s*(qa3+s*(qa4+s*(qa5+s*qa6)))));
	    if (x>=0)
		return (c + P/Q);
	    else
		return (-c - P/Q);
	}
	if (ax >= 6.0) {		/* inf>|x|>=6 */
	    if (x >= 0.0)
		return (one-tiny);
	    else
		return (tiny-one);
	}
    /* 1.25 <= |x| < 6 */
D 7
 	s = one/fabs(x);
	R=ra0+s*(ra1+s*(ra2+s*(ra3+s*(ra4+s*(ra5+s*(ra6+s*ra7))))));
	S=one+s*(sa1+s*(sa2+s*(sa3+s*(sa4+s*(sa5+s*(sa6+s*(sa7+s*sa8)))))));
	z = exp(-x*x)*(R/S)*s;
E 7
I 7
	z = -ax*ax;
	s = -one/z;
	if (ax < 2.0) {
		R = rc0+s*(rc1+s*(rc2+s*(rc3+s*(rc4+s*(rc5+
			s*(rc6+s*(rc7+s*(rc8+s*(rc9+s*rc10)))))))));
		S = one+s*(sc1+s*(sc2+s*sc3));
	} else {
		R = rb0+s*(rb1+s*(rb2+s*(rb3+s*(rb4+s*(rb5+
			s*(rb6+s*(rb7+s*(rb8+s*(rb9+s*rb10)))))))));
		S = one+s*(sb1+s*(sb2+s*sb3));
	}
	y = (R/S -.5*s) - lsqrtPI_hi;
	z += y;
	z = exp(z)/ax;
E 7
	if (x >= 0)
		return (one-z);
	else
		return (z-one);
E 6
}

D 6
double
erfc(arg) double arg;{
	double erf();
	double exp();
	double n, d;
	int i;

	if(arg < 0.)
		return(2. - erfc(-arg));
/*
	if(arg < 0.5)
		return(1. - erf(arg));
*/
	if(arg >= 10.)
		return(0.);

	for(n=0,d=0,i=N-1; i>=0; i--){
		n = n*arg + p2[i];
		d = d*arg + q2[i];
E 6
I 6
D 7
double erfc(x) 
E 7
I 7
D 8
double nerfc(x) 
E 8
I 8
double erfc(x) 
E 8
E 7
	double x;
{
D 7
	double R,S,P,Q,s,ax,y,odd,even,z,r,fabs(),exp__D();
E 7
I 7
D 10
	double R,S,P,Q,s,ax,y,z,r,fabs(),exp__D();
E 10
I 10
	double R,S,P,Q,s,ax,y,z,r,fabs(),__exp__D();
E 10
E 7
	if (!finite(x)) {
		if (isnan(x))		/* erfc(NaN) = NaN */
			return(x);
		else if (x > 0)		/* erfc(+-inf)=0,2 */
			return 0.0;
		else
			return 2.0;
E 6
	}
D 6
	return(exp(-arg*arg)*n/d);
E 6
I 6
	if ((ax = x) < 0)
		ax = -ax;
	if (ax < .84375) {			/* |x|<0.84375 */
	    if (ax < 1.38777878078144568e-17)  	/* |x|<2**-56 */
		return one-x;
	    y = x*x;
D 7
	    z = y*y;
	    even = z*(p2+z*(p4+z*(p6+z*(p8+z*p10))));
	    odd  = p1+z*(p3+z*(p5+z*(p7+z*p9)));
	    r = y*odd+even;
E 7
I 7
	    r = y*(p1+y*(p2+y*(p3+y*(p4+y*(p5+
			y*(p6+y*(p7+y*(p8+y*(p9+y*p10)))))))));
E 7
	    if (ax < .0625) {  	/* |x|<2**-4 */
		return (one-(x+x*(p0+r)));
	    } else {
		r = x*(p0+r);
		r += (x-half);
	        return (half - r);
	    }
	}
	if (ax < 1.25) {		/* 0.84375 <= |x| < 1.25 */
	    s = ax-one;
	    P = pa0+s*(pa1+s*(pa2+s*(pa3+s*(pa4+s*(pa5+s*pa6)))));
	    Q = one+s*(qa1+s*(qa2+s*(qa3+s*(qa4+s*(qa5+s*qa6)))));
	    if (x>=0) {
	        z  = one-c; return z - P/Q; 
	    } else {
		z = c+P/Q; return one+z;
	    }
	}
	if (ax >= 28)	/* Out of range */
 		if (x>0)
			return (tiny*tiny);
		else
			return (two-tiny);
	z = ax;
	TRUNC(z);
	y = z - ax; y *= (ax+z);
	z *= -z;			/* Here z + y = -x^2 */
D 7
	if (ax >= 6) {			/* 6 <= ax */
E 7
		s = one/(-z-y);		/* 1/(x*x) */
D 7
		R = s*(P0+s*(P1+s*(P2+s*(P3+s*(P4+
			s*(P5+s*(P6+s*(P7+s*(P8+s*P9)))))))));
		y += a0_lo;
	/* return exp(-x^2 + a0_hi + R)/x;	*/
		s = ((R + y) + a0_hi) + z;
		y = (((z-s) + a0_hi) + R) + y;
		r = exp__D(s, y)/x;
	} else {			/* 1.25 <= ax <= 6 */
		s = one/(ax);
	  	R=ra0+s*(ra1+s*(ra2+s*(ra3+s*(ra4+
			s*(ra5+s*(ra6+s*ra7))))));
		S=one+s*(sa1+s*(sa2+s*(sa3+s*(sa4+
			s*(sa5+s*(sa6+s*(sa7+s*sa8)))))));
	  	r = (R/S)/x;
		s = z + y; y = (z-s) + y;
		r *= exp__D(s, y);
E 7
I 7
	if (ax >= 4) {			/* 6 <= ax */
		R = s*(rd1+s*(rd2+s*(rd3+s*(rd4+s*(rd5+
			s*(rd6+s*(rd7+s*(rd8+s*(rd9+s*(rd10
			+s*(rd11+s*(rd12+s*rd13))))))))))));
		y += rd0;
	} else if (ax >= 2) {
		R = rb0+s*(rb1+s*(rb2+s*(rb3+s*(rb4+s*(rb5+
			s*(rb6+s*(rb7+s*(rb8+s*(rb9+s*rb10)))))))));
		S = one+s*(sb1+s*(sb2+s*sb3));
		y += R/S;
		R = -.5*s;
	} else {
		R = rc0+s*(rc1+s*(rc2+s*(rc3+s*(rc4+s*(rc5+
			s*(rc6+s*(rc7+s*(rc8+s*(rc9+s*rc10)))))))));
		S = one+s*(sc1+s*(sc2+s*sc3));
		y += R/S;
		R = -.5*s;
E 7
	}
I 7
	/* return exp(-x^2 - lsqrtPI_hi + R + y)/x;	*/
	s = ((R + y) - lsqrtPI_hi) + z;
	y = (((z-s) - lsqrtPI_hi) + R) + y;
D 10
	r = exp__D(s, y)/x;
E 10
I 10
	r = __exp__D(s, y)/x;
E 10
E 7
	if (x>0)
		return r;
	else
		return two-r;
E 6
}
E 1
