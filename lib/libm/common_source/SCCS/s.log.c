h00419
s 00000/00002/00460
d D 8.2 93/11/30 16:31:15 mckusick 20 19
c lint
e
s 00002/00002/00460
d D 8.1 93/06/04 17:03:39 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00456
d D 5.12 93/01/10 12:55:11 bostic 18 17
c make log tables and A1, A2, A3, A4 static
e
s 00002/00002/00460
d D 5.11 93/01/10 12:47:55 bostic 17 16
c exp__D, exp__E, log__D, and log__L are private; prepend leading "__"
e
s 00285/00006/00177
d D 5.10 93/01/10 10:22:41 bostic 16 15
c make it compile
e
s 00001/00001/00182
d D 5.9 92/12/16 20:01:52 mcilroy 15 14
c 
e
s 00005/00004/00178
d D 5.8 92/12/16 18:30:27 mcilroy 14 13
c 
e
s 00148/00103/00034
d D 5.7 92/12/02 15:31:47 bostic 13 12
c new implementation from Peter McIlroy
e
s 00000/00005/00137
d D 5.6 90/10/09 17:48:29 bostic 12 11
c new copyright notice
e
s 00001/00011/00141
d D 5.5 90/06/01 15:40:58 bostic 11 10
c new copyright notice
e
s 00019/00026/00133
d D 5.4 88/09/22 16:23:24 bostic 10 9
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00010/00005/00149
d D 5.3 88/06/30 17:45:23 bostic 9 8
c install approved copyright notice
e
s 00016/00013/00138
d D 5.2 88/04/29 12:41:56 bostic 8 7
c add Berkeley specific header
e
s 00000/00000/00151
d D 5.1 87/11/30 18:34:04 bostic 7 6
c tahoe release
e
s 00013/00013/00138
d D 1.6 87/07/13 19:20:42 zliu 6 5
c clean-ups.
e
s 00008/00004/00143
d D 1.5 87/07/10 10:36:30 zliu 5 4
c adding _0x macro for TAHOE.
e
s 00003/00003/00144
d D 1.4 87/07/07 01:32:00 zliu 4 3
c first shot at TAHOE.
e
s 00002/00002/00145
d D 1.3 86/03/16 19:08:44 elefunt 3 2
c All instances of "double static" got converted to "static double",
c as it should be.
e
s 00002/00001/00145
d D 1.2 85/09/11 23:54:20 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00146/00000/00000
d D 1.1 85/09/06 17:52:58 zliu 1 0
c date and time created 85/09/06 17:52:58 by zliu
e
u
U
t
T
I 1
D 8
/* 
E 8
I 8
/*
E 8
D 13
 * Copyright (c) 1985 Regents of the University of California.
E 13
I 13
D 19
 * Copyright (c) 1992 Regents of the University of California.
E 13
D 8
 * 
 * Use and reproduction of this software are granted  in  accordance  with
 * the terms and conditions specified in  the  Berkeley  Software  License
 * Agreement (in particular, this entails acknowledgement of the programs'
 * source, and inclusion of this notice) with the additional understanding
 * that  all  recipients  should regard themselves as participants  in  an
 * ongoing  research  project and hence should  feel  obligated  to report
 * their  experiences (good or bad) with these elementary function  codes,
 * using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 8
I 8
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 11
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
D 12
 *
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
E 12
E 8
 */

#ifndef lint
D 2
static char sccsid[] = "%W% (ELEFUNT) %G%";
E 2
I 2
D 8
static char sccsid[] =
"%Z%%M%	4.5 (Berkeley) 8/21/85; %I% (ucb.elefunt) %G%";
E 2
D 6
#endif not lint
E 6
I 6
#endif	/* not lint */
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8
E 6

D 13
/* LOG(X)
 * RETURN THE LOGARITHM OF x 
 * DOUBLE PRECISION (VAX D FORMAT 56 bits or IEEE DOUBLE 53 BITS)
 * CODED IN C BY K.C. NG, 1/19/85;
 * REVISED BY K.C. NG on 2/7/85, 3/7/85, 3/24/85, 4/16/85.
E 13
I 13
#include <math.h>
#include <errno.h>

D 16
#include "log_table.h"
E 16
D 15
#include "dmath.h"
E 15
I 15
#include "mathimpl.h"
E 15

/* Table-driven natural logarithm.
E 13
 *
D 13
 * Required system supported functions:
 *	scalb(x,n)
 *	copysign(x,y)
 *	logb(x)	
 *	finite(x)
E 13
I 13
 * This code was derived, with minor modifications, from:
 *	Peter Tang, "Table-Driven Implementation of the
 *	Logarithm in IEEE Floating-Point arithmetic." ACM Trans.
 *	Math Software, vol 16. no 4, pp 378-400, Dec 1990).
E 13
 *
D 13
 * Required kernel function:
 *	log__L(z) 
E 13
I 13
 * Calculates log(2^m*F*(1+f/F)), |f/j| <= 1/256,
 * where F = j/128 for j an integer in [0, 128].
E 13
 *
D 13
 * Method :
 *	1. Argument Reduction: find k and f such that 
 *			x = 2^k * (1+f), 
 *	   where  sqrt(2)/2 < 1+f < sqrt(2) .
E 13
I 13
 * log(2^m) = log2_hi*m + log2_tail*m
 * since m is an integer, the dominant term is exact.
 * m has at most 10 digits (for subnormal numbers),
 * and log2_hi has 11 trailing zero bits.
E 13
 *
D 13
 *	2. Let s = f/(2+f) ; based on log(1+f) = log(1+s) - log(1-s)
 *		 = 2s + 2/3 s**3 + 2/5 s**5 + .....,
 *	   log(1+f) is computed by
E 13
I 13
 * log(F) = logF_hi[j] + logF_lo[j] is in tabular form in log_table.h
 * logF_hi[] + 512 is exact.
E 13
 *
D 13
 *	     		log(1+f) = 2s + s*log__L(s*s)
 *	   where
 *		log__L(z) = z*(L1 + z*(L2 + z*(... (L6 + z*L7)...)))
E 13
I 13
 * log(1+f/F) = 2*f/(2*F + f) + 1/12 * (2*f/(2*F + f))**3 + ...
 * the leading term is calculated to extra precision in two
 * parts, the larger of which adds exactly to the dominant
 * m and F terms.
 * There are two cases:
 *	1. when m, j are non-zero (m | j), use absolute
 *	   precision for the leading term.
 *	2. when m = j = 0, |1-x| < 1/256, and log(x) ~= (x-1).
 *	   In this case, use a relative precision of 24 bits.
 * (This is done differently in the original paper)
E 13
 *
D 13
 *	   See log__L() for the values of the coefficients.
 *
 *	3. Finally,  log(x) = k*ln2 + log(1+f).  (Here n*ln2 will be stored
 *	   in two floating point number: n*ln2hi + n*ln2lo, n*ln2hi is exact
 *	   since the last 20 bits of ln2hi is 0.)
 *
E 13
 * Special cases:
D 13
 *	log(x) is NaN with signal if x < 0 (including -INF) ; 
 *	log(+INF) is +INF; log(0) is -INF with signal;
 *	log(NaN) is that NaN with no signal.
 *
 * Accuracy:
 *	log(x) returns the exact log(x) nearly rounded. In a test run with
 *	1,536,000 random arguments on a VAX, the maximum observed error was
 *	.826 ulps (units in the last place).
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following constants.
 * The decimal values may be used, provided that the compiler will convert
 * from decimal to binary accurately enough to produce the hexadecimal values
 * shown.
 */
E 13
I 13
 *	0	return signalling -Inf
 *	neg	return signalling NaN
 *	+Inf	return +Inf
*/
E 13

D 4
#ifdef VAX	/* VAX D format */
E 4
I 4
D 6
#if (defined(VAX)||defined(TAHOE))	/* VAX D format */
E 6
I 6
D 10
#if defined(vax)||defined(tahoe)	/* VAX D format */
E 10
E 6
E 4
D 13
#include <errno.h>
D 5

E 5
I 5
D 6
#ifdef VAX
E 6
I 6
D 10
#ifdef vax
E 6
#define _0x(A,B)	0x/**/A/**/B
D 6
#else	/* VAX */
E 6
I 6
#else	/* vax */
E 6
#define _0x(A,B)	0x/**/B/**/A
D 6
#endif	/* VAX */
E 6
I 6
#endif	/* vax */
E 6
E 5
D 3
/* double static */
E 3
I 3
/* static double */
E 3
/* ln2hi  =  6.9314718055829871446E-1    , Hex  2^  0   *  .B17217F7D00000 */
/* ln2lo  =  1.6465949582897081279E-12   , Hex  2^-39   *  .E7BCD5E4F1D9CC */
/* sqrt2  =  1.4142135623730950622E0     ; Hex  2^  1   *  .B504F333F9DE65 */
D 5
static long     ln2hix[] = { 0x72174031, 0x0000f7d0};
static long     ln2lox[] = { 0xbcd52ce7, 0xd9cce4f1};
static long     sqrt2x[] = { 0x04f340b5, 0xde6533f9};
E 5
I 5
static long     ln2hix[] = { _0x(7217,4031), _0x(0000,f7d0)};
static long     ln2lox[] = { _0x(bcd5,2ce7), _0x(d9cc,e4f1)};
static long     sqrt2x[] = { _0x(04f3,40b5), _0x(de65,33f9)};
E 5
#define    ln2hi    (*(double*)ln2hix)
#define    ln2lo    (*(double*)ln2lox)
#define    sqrt2    (*(double*)sqrt2x)
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe)	*/
E 6
D 3
double static
E 3
I 3
static double
E 3
ln2hi  =  6.9314718036912381649E-1    , /*Hex  2^ -1   *  1.62E42FEE00000 */
ln2lo  =  1.9082149292705877000E-10   , /*Hex  2^-33   *  1.A39EF35793C76 */
sqrt2  =  1.4142135623730951455E0     ; /*Hex  2^  0   *  1.6A09E667F3BCD */
D 6
#endif
E 6
I 6
#endif	/* defined(vax)||defined(tahoe)	*/
E 10
I 10
#include "mathimpl.h"
E 13
I 13
#if defined(vax) || defined(tahoe)
D 14
#define _IEEE	0
#define TRUNC(x) (double) (float) (x)
E 14
I 14
#define _IEEE		0
#define TRUNC(x)	x = (double) (float) (x)
E 14
#else
D 16
#define _IEEE	1
E 16
I 16
#define _IEEE		1
E 16
D 14
#define TRUNC(x) *(((int *) &x) + 1) &= 0xf8000000
#define infnan(x) 0.0
E 14
I 14
#define endian		(((*(int *) &one)) ? 1 : 0)
#define TRUNC(x)	*(((int *) &x) + endian) &= 0xf8000000
#define infnan(x)	0.0
E 14
#endif
E 13
E 10
E 6

I 16
#define N 128

/* Table of log(Fj) = logF_head[j] + logF_tail[j], for Fj = 1+j/128.
 * Used for generation of extend precision logarithms.
 * The constant 35184372088832 is 2^45, so the divide is exact.
 * It ensures correct reading of logF_head, even for inaccurate
 * decimal-to-binary conversion routines.  (Everybody gets the
 * right answer for integers less than 2^53.)
 * Values for log(F) were generated using error < 10^-57 absolute
 * with the bc -l package.
*/
D 18
double	A1 = 	  .08333333333333178827;
double	A2 = 	  .01250000000377174923;
double	A3 =	 .002232139987919447809;
double	A4 =	.0004348877777076145742;
E 18
I 18
static double	A1 = 	  .08333333333333178827;
static double	A2 = 	  .01250000000377174923;
static double	A3 =	 .002232139987919447809;
static double	A4 =	.0004348877777076145742;
E 18

D 18
double logF_head[N+1] = {
E 18
I 18
static double logF_head[N+1] = {
E 18
	0.,
	.007782140442060381246,
	.015504186535963526694,
	.023167059281547608406,
	.030771658666765233647,
	.038318864302141264488,
	.045809536031242714670,
	.053244514518837604555,
	.060624621816486978786,
	.067950661908525944454,
	.075223421237524235039,
	.082443669210988446138,
	.089612158689760690322,
	.096729626458454731618,
	.103796793681567578460,
	.110814366340264314203,
	.117783035656430001836,
	.124703478501032805070,
	.131576357788617315236,
	.138402322859292326029,
	.145182009844575077295,
	.151916042025732167530,
	.158605030176659056451,
	.165249572895390883786,
	.171850256926518341060,
	.178407657472689606947,
	.184922338493834104156,
	.191394852999565046047,
	.197825743329758552135,
	.204215541428766300668,
	.210564769107350002741,
	.216873938300523150246,
	.223143551314024080056,
	.229374101064877322642,
	.235566071312860003672,
	.241719936886966024758,
	.247836163904594286577,
	.253915209980732470285,
	.259957524436686071567,
	.265963548496984003577,
	.271933715484010463114,
	.277868451003087102435,
	.283768173130738432519,
	.289633292582948342896,
	.295464212893421063199,
	.301261330578199704177,
	.307025035294827830512,
	.312755710004239517729,
	.318453731118097493890,
	.324119468654316733591,
	.329753286372579168528,
	.335355541920762334484,
	.340926586970454081892,
	.346466767346100823488,
	.351976423156884266063,
	.357455888922231679316,
	.362905493689140712376,
	.368325561158599157352,
	.373716409793814818840,
	.379078352934811846353,
	.384411698910298582632,
	.389716751140440464951,
	.394993808240542421117,
	.400243164127459749579,
	.405465108107819105498,
	.410659924985338875558,
	.415827895143593195825,
	.420969294644237379543,
	.426084395310681429691,
	.431173464818130014464,
	.436236766774527495726,
	.441274560805140936281,
	.446287102628048160113,
	.451274644139630254358,
	.456237433481874177232,
	.461175715122408291790,
	.466089729924533457960,
	.470979715219073113985,
	.475845904869856894947,
	.480688529345570714212,
	.485507815781602403149,
	.490303988045525329653,
	.495077266798034543171,
	.499827869556611403822,
	.504556010751912253908,
	.509261901790523552335,
	.513945751101346104405,
	.518607764208354637958,
	.523248143765158602036,
	.527867089620485785417,
	.532464798869114019908,
	.537041465897345915436,
	.541597282432121573947,
	.546132437597407260909,
	.550647117952394182793,
	.555141507540611200965,
	.559615787935399566777,
	.564070138285387656651,
	.568504735352689749561,
	.572919753562018740922,
	.577315365035246941260,
	.581691739635061821900,
	.586049045003164792433,
	.590387446602107957005,
	.594707107746216934174,
	.599008189645246602594,
	.603290851438941899687,
	.607555250224322662688,
	.611801541106615331955,
	.616029877215623855590,
	.620240409751204424537,
	.624433288012369303032,
	.628608659422752680256,
	.632766669570628437213,
	.636907462236194987781,
	.641031179420679109171,
	.645137961373620782978,
	.649227946625615004450,
	.653301272011958644725,
	.657358072709030238911,
	.661398482245203922502,
	.665422632544505177065,
	.669430653942981734871,
	.673422675212350441142,
	.677398823590920073911,
	.681359224807238206267,
	.685304003098281100392,
	.689233281238557538017,
	.693147180560117703862
};

D 18
double logF_tail[N+1] = {
E 18
I 18
static double logF_tail[N+1] = {
E 18
	0.,
	-.00000000000000543229938420049,
	 .00000000000000172745674997061,
	-.00000000000001323017818229233,
	-.00000000000001154527628289872,
	-.00000000000000466529469958300,
	 .00000000000005148849572685810,
	-.00000000000002532168943117445,
	-.00000000000005213620639136504,
	-.00000000000001819506003016881,
	 .00000000000006329065958724544,
	 .00000000000008614512936087814,
	-.00000000000007355770219435028,
	 .00000000000009638067658552277,
	 .00000000000007598636597194141,
	 .00000000000002579999128306990,
	-.00000000000004654729747598444,
	-.00000000000007556920687451336,
	 .00000000000010195735223708472,
	-.00000000000017319034406422306,
	-.00000000000007718001336828098,
	 .00000000000010980754099855238,
	-.00000000000002047235780046195,
	-.00000000000008372091099235912,
	 .00000000000014088127937111135,
	 .00000000000012869017157588257,
	 .00000000000017788850778198106,
	 .00000000000006440856150696891,
	 .00000000000016132822667240822,
	-.00000000000007540916511956188,
	-.00000000000000036507188831790,
	 .00000000000009120937249914984,
	 .00000000000018567570959796010,
	-.00000000000003149265065191483,
	-.00000000000009309459495196889,
	 .00000000000017914338601329117,
	-.00000000000001302979717330866,
	 .00000000000023097385217586939,
	 .00000000000023999540484211737,
	 .00000000000015393776174455408,
	-.00000000000036870428315837678,
	 .00000000000036920375082080089,
	-.00000000000009383417223663699,
	 .00000000000009433398189512690,
	 .00000000000041481318704258568,
	-.00000000000003792316480209314,
	 .00000000000008403156304792424,
	-.00000000000034262934348285429,
	 .00000000000043712191957429145,
	-.00000000000010475750058776541,
	-.00000000000011118671389559323,
	 .00000000000037549577257259853,
	 .00000000000013912841212197565,
	 .00000000000010775743037572640,
	 .00000000000029391859187648000,
	-.00000000000042790509060060774,
	 .00000000000022774076114039555,
	 .00000000000010849569622967912,
	-.00000000000023073801945705758,
	 .00000000000015761203773969435,
	 .00000000000003345710269544082,
	-.00000000000041525158063436123,
	 .00000000000032655698896907146,
	-.00000000000044704265010452446,
	 .00000000000034527647952039772,
	-.00000000000007048962392109746,
	 .00000000000011776978751369214,
	-.00000000000010774341461609578,
	 .00000000000021863343293215910,
	 .00000000000024132639491333131,
	 .00000000000039057462209830700,
	-.00000000000026570679203560751,
	 .00000000000037135141919592021,
	-.00000000000017166921336082431,
	-.00000000000028658285157914353,
	-.00000000000023812542263446809,
	 .00000000000006576659768580062,
	-.00000000000028210143846181267,
	 .00000000000010701931762114254,
	 .00000000000018119346366441110,
	 .00000000000009840465278232627,
	-.00000000000033149150282752542,
	-.00000000000018302857356041668,
	-.00000000000016207400156744949,
	 .00000000000048303314949553201,
	-.00000000000071560553172382115,
	 .00000000000088821239518571855,
	-.00000000000030900580513238244,
	-.00000000000061076551972851496,
	 .00000000000035659969663347830,
	 .00000000000035782396591276383,
	-.00000000000046226087001544578,
	 .00000000000062279762917225156,
	 .00000000000072838947272065741,
	 .00000000000026809646615211673,
	-.00000000000010960825046059278,
	 .00000000000002311949383800537,
	-.00000000000058469058005299247,
	-.00000000000002103748251144494,
	-.00000000000023323182945587408,
	-.00000000000042333694288141916,
	-.00000000000043933937969737844,
	 .00000000000041341647073835565,
	 .00000000000006841763641591466,
	 .00000000000047585534004430641,
	 .00000000000083679678674757695,
	-.00000000000085763734646658640,
	 .00000000000021913281229340092,
	-.00000000000062242842536431148,
	-.00000000000010983594325438430,
	 .00000000000065310431377633651,
	-.00000000000047580199021710769,
	-.00000000000037854251265457040,
	 .00000000000040939233218678664,
	 .00000000000087424383914858291,
	 .00000000000025218188456842882,
	-.00000000000003608131360422557,
	-.00000000000050518555924280902,
	 .00000000000078699403323355317,
	-.00000000000067020876961949060,
	 .00000000000016108575753932458,
	 .00000000000058527188436251509,
	-.00000000000035246757297904791,
	-.00000000000018372084495629058,
	 .00000000000088606689813494916,
	 .00000000000066486268071468700,
	 .00000000000063831615170646519,
	 .00000000000025144230728376072,
	-.00000000000017239444525614834
};

E 16
I 10
D 13
vc(ln2hi, 6.9314718055829871446E-1  ,7217,4031,0000,f7d0,   0, .B17217F7D00000)
vc(ln2lo, 1.6465949582897081279E-12 ,bcd5,2ce7,d9cc,e4f1, -39, .E7BCD5E4F1D9CC)
vc(sqrt2, 1.4142135623730950622E0   ,04f3,40b5,de65,33f9,   1, .B504F333F9DE65)
E 13
I 13
double
#ifdef _ANSI_SOURCE
log(double x)
#else
log(x) double x;
#endif
{
	int m, j;
	double F, f, g, q, u, u2, v, zero = 0.0, one = 1.0;
D 20
	double logb(), ldexp();
E 20
	volatile double u1;
E 13

D 13
ic(ln2hi, 6.9314718036912381649E-1,   -1, 1.62E42FEE00000)
ic(ln2lo, 1.9082149292705877000E-10, -33, 1.A39EF35793C76)
ic(sqrt2, 1.4142135623730951455E0,     0, 1.6A09E667F3BCD)
E 13
I 13
	/* Catch special cases */
	if (x <= 0)
		if (_IEEE && x == zero)	/* log(0) = -Inf */
			return (-one/zero);
		else if (_IEEE)		/* log(neg) = NaN */
			return (zero/zero);
		else if (x == zero)	/* NOT REACHED IF _IEEE */
			return (infnan(-ERANGE));
		else
			return (infnan(EDOM));
	else if (!finite(x))
		if (_IEEE)		/* x = NaN, Inf */
			return (x+x);
		else
			return (infnan(ERANGE));
	
	/* Argument reduction: 1 <= g < 2; x/2^m = g;	*/
	/* y = F*(1 + f/F) for |f| <= 2^-8		*/
E 13

D 13
#ifdef vccast
#define	ln2hi	vccast(ln2hi)
#define	ln2lo	vccast(ln2lo)
#define	sqrt2	vccast(sqrt2)
#endif
E 13
I 13
	m = logb(x);
	g = ldexp(x, -m);
	if (_IEEE && m == -1022) {
		j = logb(g), m += j;
		g = ldexp(g, -j);
	}
	j = N*(g-1) + .5;
	F = (1.0/N) * j + 1;	/* F*128 is an integer in [128, 512] */
	f = g - F;
E 13

I 13
	/* Approximate expansion for log(1+f/F) ~= u + q */
	g = 1/(2*F+f);
	u = 2*f*g;
	v = u*u;
	q = u*v*(A1 + v*(A2 + v*(A3 + v*A4)));
E 13

E 10
D 13
double log(x)
double x;
{
D 10
	static double zero=0.0, negone= -1.0, half=1.0/2.0;
	double logb(),scalb(),copysign(),log__L(),s,z,t;
	int k,n,finite();
E 10
I 10
	const static double zero=0.0, negone= -1.0, half=1.0/2.0;
	double s,z,t;
	int k,n;
E 13
I 13
    /* case 1: u1 = u rounded to 2^-43 absolute.  Since u < 2^-8,
     * 	       u1 has at most 35 bits, and F*u1 is exact, as F has < 8 bits.
     *         It also adds exactly to |m*log2_hi + log_F_head[j] | < 750
    */
	if (m | j)
		u1 = u + 513, u1 -= 513;
E 13
E 10

D 4
#ifndef VAX
E 4
I 4
D 6
#if (!defined(VAX)&&!defined(TAHOE))
E 6
I 6
D 13
#if !defined(vax)&&!defined(tahoe)
E 6
E 4
	if(x!=x) return(x);	/* x is NaN */
D 6
#endif
E 6
I 6
#endif	/* !defined(vax)&&!defined(tahoe) */
E 6
	if(finite(x)) {
	   if( x > zero ) {
E 13
I 13
    /* case 2:	|1-x| < 1/256. The m- and j- dependent terms are zero;
     * 		u1 = u to 24 bits.
    */
	else
		u1 = u, TRUNC(u1);
	u2 = (2.0*(f - F*u1) - u1*f) * g;
			/* u1 + u2 = 2f/(2F+f) to extra precision.	*/
E 13

D 13
	   /* argument reduction */
	      k=logb(x);   x=scalb(x,-k);
	      if(k == -1022) /* subnormal no. */
		   {n=logb(x); x=scalb(x,-n); k+=n;} 
	      if(x >= sqrt2 ) {k += 1; x *= half;}
	      x += negone ;
E 13
I 13
	/* log(x) = log(2^m*F*(1+f/F)) =				*/
	/* (m*log2_hi+logF_head[j]+u1) + (m*log2_lo+logF_tail[j]+q);	*/
	/* (exact) + (tiny)						*/
E 13

D 13
	   /* compute log(1+x)  */
              s=x/(2+x); t=x*x*half;
	      z=k*ln2lo+s*(t+log__L(s*s));
	      x += (z - t) ;
E 13
I 13
	u1 += m*logF_head[N] + logF_head[j];		/* exact */
	u2 = (u2 + logF_tail[j]) + q;			/* tiny */
	u2 += logF_tail[N]*m;
	return (u1 + u2);
}
E 13

D 13
	      return(k*ln2hi+x);
	   }
	/* end of if (x > zero) */
E 13
I 13
D 16
/* Extra precision variant, returning
 * struct {double a, b;}; log(x) = a+b to 63 bits, with
 * a is rounded to 26 bits.
E 16
I 16
/*
 * Extra precision variant, returning struct {double a, b;};
 * log(x) = a+b to 63 bits, with a is rounded to 26 bits.
E 16
 */
struct Double
#ifdef _ANSI_SOURCE
D 17
log__D(double x)
E 17
I 17
__log__D(double x)
E 17
#else
D 17
log__D(x) double x;
E 17
I 17
__log__D(x) double x;
E 17
#endif
{
	int m, j;
D 16
	double F, f, g, q, u, v, u2;
E 16
I 16
	double F, f, g, q, u, v, u2, one = 1.0;
E 16
D 20
	double logb(), ldexp();
E 20
	volatile double u1;
	struct Double r;
E 13

D 13
	   else {
D 4
#ifdef VAX
E 4
I 4
D 6
#if (defined(VAX)||defined(TAHOE))
E 6
I 6
#if defined(vax)||defined(tahoe)
E 6
E 4
D 10
		extern double infnan();
E 10
		if ( x == zero )
		    return (infnan(-ERANGE));	/* -INF */
		else
		    return (infnan(EDOM));	/* NaN */
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe) */
E 6
		/* zero argument, return -INF with signal */
		if ( x == zero )
		    return( negone/zero );
E 13
I 13
	/* Argument reduction: 1 <= g < 2; x/2^m = g;	*/
	/* y = F*(1 + f/F) for |f| <= 2^-8		*/
E 13

D 13
		/* negative argument, return NaN with signal */
		else 
		    return ( zero / zero );
D 6
#endif
E 6
I 6
#endif	/* defined(vax)||defined(tahoe) */
E 6
	    }
E 13
I 13
	m = logb(x);
	g = ldexp(x, -m);
	if (_IEEE && m == -1022) {
		j = logb(g), m += j;
		g = ldexp(g, -j);
E 13
	}
D 13
    /* end of if (finite(x)) */
D 6
    /* NOT REACHED ifdef VAX */
E 6
I 6
    /* NOTREACHED if defined(vax)||defined(tahoe) */
E 13
I 13
	j = N*(g-1) + .5;
	F = (1.0/N) * j + 1;
	f = g - F;
E 13
E 6

D 13
    /* log(-INF) is NaN with signal */
	else if (x<0) 
	    return(zero/zero);      
E 13
I 13
	g = 1/(2*F+f);
	u = 2*f*g;
	v = u*u;
	q = u*v*(A1 + v*(A2 + v*(A3 + v*A4)));
	if (m | j)
		u1 = u + 513, u1 -= 513;
	else
		u1 = u, TRUNC(u1);
	u2 = (2.0*(f - F*u1) - u1*f) * g;
E 13

D 13
    /* log(+INF) is +INF */
	else return(x);      
E 13
I 13
	u1 += m*logF_head[N] + logF_head[j];
E 13

I 13
	u2 +=  logF_tail[j]; u2 += q;
	u2 += logF_tail[N]*m;
	r.a = u1 + u2;			/* Only difference is here */
	TRUNC(r.a);
	r.b = (u1 - r.a) + u2;
	return (r);
E 13
}
E 1
