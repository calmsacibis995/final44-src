h23752
s 00002/00002/00308
d D 8.1 93/06/04 17:02:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00305
d D 5.4 93/01/10 12:47:53 bostic 4 3
c exp__D, exp__E, log__D, and log__L are private; prepend leading "__"
e
s 00001/00001/00309
d D 5.3 92/12/16 21:59:53 mcilroy 3 2
c Fixed behavior for subnormal returns.
e
s 00181/00196/00129
d D 5.2 92/12/16 18:08:58 bostic 2 1
c new version from Peter McIlroy; note, funded by UUNET
e
s 00325/00000/00000
d D 5.1 92/12/02 15:29:28 bostic 1 0
c original version from Peter McIlroy
c date and time created 92/12/02 15:29:28 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 2
/*
 * This code by P. McIlroy, Oct 1992;
 *
 * The financial support of UUNET Communications Services is greatfully
 * acknowledged.
 */

E 2
#include <math.h>
I 2
#include "mathimpl.h"
E 2
#include <errno.h>

/* METHOD:
 * x < 0: Use reflection formula, G(x) = pi/(sin(pi*x)*x*G(x))
 * 	At negative integers, return +Inf, and set errno.
 *
D 2
 * x < 6.5: use one of two rational approximation,
 *	to log(G(x)), expanded around 2 for x near integral;
 *	around the minimum for x near half-integral.  The two
 *	regions overlap.
 *	In the range [2.0, 2.5], it is necessary to expand around 2.
 *	In the range ~[1.462-.22, 1.462+.25], the expansion around
 *	the minimum is necessary to get <1ulp accuracy.
E 2
I 2
 * x < 6.5:
 *	Use argument reduction G(x+1) = xG(x) to reach the
 *	range [1.066124,2.066124].  Use a rational
 *	approximation centered at the minimum (x0+1) to
 *	ensure monotonicity.
E 2
 *
D 2
 * x >= 6.5: Use the asymptotic approximation (Stirling's formula.)
E 2
I 2
 * x >= 6.5: Use the asymptotic approximation (Stirling's formula)
 *	adjusted for equal-ripples:
E 2
 *
 *	log(G(x)) ~= (x-.5)*(log(x)-1) + .5(log(2*pi)-1) + 1/x*P(1/(x*x))
 *
 *	Keep extra precision in multiplying (x-.5)(log(x)-1), to
 *	avoid premature round-off.
 *
D 2
 * Special values:  NaN, +/-Inf, 0, Negative Integers.
 *	Neg integer: Set overflow trap; return +Inf; errno = EDOM
 *	+Inf: Return +Inf; errno = ERANGE;
 *	-Inf: Return +Inf; errno = EDOM;
 *	NaN:  Return NaN; errno = EDOM;
*/
#define x0 .461632144968362356785
#define LEFT -.3955078125
E 2
I 2
 * Special values:
 *	non-positive integer:	Set overflow trap; return +Inf;
 *	x > 171.63:		Set overflow trap; return +Inf;
 *	NaN: 			Set invalid trap;  return NaN
 *
 * Accuracy: Gamma(x) is accurate to within
 *	x > 0:  error provably < 0.9ulp.
 *	Maximum observed in 1,000,000 trials was .87ulp.
 *	x < 0:
 *	Maximum observed error < 4ulp in 1,000,000 trials.
 */

static double neg_gam __P((double));
static double small_gam __P((double));
static double smaller_gam __P((double));
static struct Double large_gam __P((double));
static struct Double ratfun_gam __P((double, double));

/*
 * Rational approximation, A0 + x*x*P(x)/Q(x), on the interval
 * [1.066.., 2.066..] accurate to 4.25e-19.
 */
#define LEFT -.3955078125	/* left boundary for rat. approx */
#define x0 .461632144968362356785	/* xmin - 1 */

E 2
#define a0_hi 0.88560319441088874992
#define a0_lo -.00000000000000004996427036469019695
I 2
#define P0	 6.21389571821820863029017800727e-01
#define P1	 2.65757198651533466104979197553e-01
#define P2	 5.53859446429917461063308081748e-03
#define P3	 1.38456698304096573887145282811e-03
#define P4	 2.40659950032711365819348969808e-03
#define Q0	 1.45019531250000000000000000000e+00
#define Q1	 1.06258521948016171343454061571e+00
#define Q2	-2.07474561943859936441469926649e-01
#define Q3	-1.46734131782005422506287573015e-01
#define Q4	 3.07878176156175520361557573779e-02
#define Q5	 5.12449347980666221336054633184e-03
#define Q6	-1.76012741431666995019222898833e-03
#define Q7	 9.35021023573788935372153030556e-05
#define Q8	 6.13275507472443958924745652239e-06
/*
 * Constants for large x approximation (x in [6, Inf])
 * (Accurate to 2.8*10^-19 absolute)
 */
E 2
#define lns2pi_hi 0.418945312500000
#define lns2pi_lo -.000006779295327258219670263595
I 2
#define Pa0	 8.33333333333333148296162562474e-02
#define Pa1	-2.77777777774548123579378966497e-03
#define Pa2	 7.93650778754435631476282786423e-04
#define Pa3	-5.95235082566672847950717262222e-04
#define Pa4	 8.41428560346653702135821806252e-04
#define Pa5	-1.89773526463879200348872089421e-03
#define Pa6	 5.69394463439411649408050664078e-03
#define Pa7	-1.44705562421428915453880392761e-02
E 2

D 2
#define UNDERFL (1e-1020 * 1e-1020)
double small_gam(double);
double smaller_gam(double);
struct Double large_gam(double);
double neg_gam(double);
struct Double ratfun_gam(double, double);
/**
#define NP 5
static double P[] = {
	0.57410538218150719558252603747,
	0.24541366696467897812183878159,
	0.00513973619299223308948265654,
	0.00129391688253677823901288679,
	0.00222188711638167000692045683
};
#define NQ 9
static double Q[] = {
	1.33984375,
	0.981446340605471312379393111769,
	-0.19172028764767945485658628968,
	-0.13543838178180836462338731962,
	0.028432780865671299780350622655,
	0.004720852857293747484312973484,
	-0.00162320758342873413572482466,
	8.63879091186865255905247274e-05,
	5.67776543645974456238616906e-06,
	-1.1130244665113561369974706e-08
};
/**/
#define P0	.621389571821820863029017800727g
#define P1	.265757198651533466104979197553,
#define P2	.00553859446429917461063308081748,
#define P3	.00138456698304096573887145282811,
#define P4	.00240659950032711365819348969808
E 2
I 2
static const double zero = 0., one = 1.0, tiny = 1e-300;
static int endian;
/*
 * TRUNC sets trailing bits in a floating-point number to zero.
 * is a temporary variable.
 */
#if defined(vax) || defined(tahoe)
#define _IEEE		0
#define TRUNC(x)	x = (double) (float) (x)
#else
#define _IEEE		1
#define TRUNC(x)	*(((int *) &x) + endian) &= 0xf8000000
#define infnan(x)	0.0
#endif
E 2

D 2
#define Q0	1.4501953125
#define Q1	1.06258521948016171343454061571
#define Q2	-.207474561943859936441469926649
#define Q3	-.146734131782005422506287573015
#define Q4	.0307878176156175520361557573779
#define Q5	.00512449347980666221336054633184
#define Q6	-.00176012741431666995019222898833
#define Q7	.0000935021023573788935372153030556
#define Q8	.00000613275507472443958924745652239

#define Pa0	.0833333333333333148296162562474
#define Pa1	-.00277777777774548123579378966497
#define Pa2	.000793650778754435631476282786423
#define Pa3	-.000595235082566672847950717262222
#define Pa4	.000841428560346653702135821806252
#define Pa5	-.00189773526463879200348872089421
#define Pa6	.00569394463439411649408050664078
#define Pa7	-.0144705562421428915453880392761

static struct Double	large_gam __P((double));
static double	 	neg_gam __P((double));
static struct Double	ratfun_gam __P((double, double));
static double	 	small_gam __P((double));
static double	 	smaller_gam __P((double));

E 2
double
gamma(x)
	double x;
{
D 2
	double zero = 0;
E 2
	struct Double u;
D 2
	if (x > 6 + x0 + LEFT) {
E 2
I 2
	endian = (*(int *) &one) ? 1 : 0;

	if (x >= 6) {
E 2
		if(x > 171.63)
D 2
			return(1.0/zero);
E 2
I 2
			return(one/zero);
E 2
		u = large_gam(x);
D 4
		return(exp__D(u.a, u.b));
E 4
I 4
		return(__exp__D(u.a, u.b));
E 4
	} else if (x >= 1.0 + LEFT + x0)
		return (small_gam(x));
D 2
	else if (x > 1e-18)
E 2
I 2
	else if (x > 1.e-17)
E 2
		return (smaller_gam(x));
D 2
	else if(x > 0) {
		1 + 1e-20;	/* raise inexact flag */
		return(1/x);
	}
	else if (x <= 0)
E 2
I 2
	else if (x > -1.e-17) {
		if (x == 0.0)
			if (!_IEEE) return (infnan(ERANGE));
			else return (one/x);
		one+1e-20;		/* Raise inexact flag. */
		return (one/x);
	} else if (!finite(x)) {
		if (_IEEE)		/* x = NaN, -Inf */
			return (x*x);
		else
			return (infnan(EDOM));
	 } else
E 2
		return (neg_gam(x));
D 2
	else {				/* x = NaN */
		errno = EDOM;
		return (x);
	}
E 2
}
D 2

/* TRUNC sets trailing bits in a floating-point number to zero.
 * is a temporary variable.
*/

#if defined(vax) || defined(tahoe)
#define _IEEE	0
#define TRUNC(x) (double) (float) (x)
#else
#define _IEEE	1
#define TRUNC(x) *(((int *) &x) + 1) &= 0xf8000000
#define infnan(x) 0.0
#endif

/* Accurate to max(ulp(1/128) absolute, 2^-75 relative) error. */
E 2
I 2
/*
 * Accurate to max(ulp(1/128) absolute, 2^-66 relative) error.
 */
E 2
static struct Double
large_gam(x)
	double x;
{
	double z, p;
	int i;
	struct Double t, u, v;
D 2
	pua = (long *) &u.a, pua++;
	pva = (long *) &v.a, pva++;
	if (x == infinity()) {
		u.b = 0, u.a = x;
		return u;
	}
	z = 1.0/(x*x);
	p = Pa0+z*(Pa1+z*(Pa2+z*(Pa3+z*(Pa4+z*Pa5+z*(Pa6+z*Pa7)))));
	p = p/x;			/* |e| < 2.8e-18 */
					/* 0 < p < 1/64 (at x = 5.5) */
E 2
I 2

	z = one/(x*x);
	p = Pa0+z*(Pa1+z*(Pa2+z*(Pa3+z*(Pa4+z*(Pa5+z*(Pa6+z*Pa7))))));
	p = p/x;

E 2
D 4
	u = log__D(x);
E 4
I 4
	u = __log__D(x);
E 4
D 2
	u.a -= 1.0;
E 2
I 2
	u.a -= one;
E 2
	v.a = (x -= .5);
	TRUNC(v.a);
	v.b = x - v.a;
	t.a = v.a*u.a;			/* t = (x-.5)*(log(x)-1) */
	t.b = v.b*u.a + x*u.b;
	/* return t.a + t.b + lns2pi_hi + lns2pi_lo + p */
D 2
	t.b += lns2pi_lo; t.b += p;	/* small pieces ( < 1/64, assuming t < 1e14) */
E 2
I 2
	t.b += lns2pi_lo; t.b += p;
E 2
	u.a = lns2pi_hi + t.b; u.a += t.a;
	u.b = t.a - u.a;
	u.b += lns2pi_hi; u.b += t.b;
	return (u);
}
D 2
/* Good to < 1 ulp.  (provably .90 ulp; .87 ulp on 1,000,000 runs.)
   It also has correct monotonicity.
E 2
I 2
/*
 * Good to < 1 ulp.  (provably .90 ulp; .87 ulp on 1,000,000 runs.)
 * It also has correct monotonicity.
E 2
 */
static double
small_gam(x)
	double x;
{
D 2
	double y, t;
E 2
I 2
	double y, ym1, t, x1;
E 2
	struct Double yy, r;
D 2
	pt = ((long *) &t)+1;
	pra = ((long *) &r.a)+1;
	y = x - 1;
E 2
I 2
	y = x - one;
	ym1 = y - one;
E 2
	if (y <= 1.0 + (LEFT + x0)) {
		yy = ratfun_gam(y - x0, 0);
		return (yy.a + yy.b);
	}
D 2
	r.a = y--;
E 2
I 2
	r.a = y;
E 2
	TRUNC(r.a);
D 2
	yy.a = r.a - 1.0;
E 2
I 2
	yy.a = r.a - one;
	y = ym1;
E 2
	yy.b = r.b = y - yy.a;
D 2
	for (; --y > 1.0 + (LEFT + x0); yy.a--) {
			t = r.a*yy.a;
			r.b = r.a*yy.b + y*r.b;
			r.a = t + r.b;
			TRUNC(r.a);
			t -= r.a;
			r.b += t;
	}				/* now want r * gamma(y); */
E 2
I 2
	/* Argument reduction: G(x+1) = x*G(x) */
	for (ym1 = y-one; ym1 > LEFT + x0; y = ym1--, yy.a--) {
		t = r.a*yy.a;
		r.b = r.a*yy.b + y*r.b;
		r.a = t;
		TRUNC(r.a);
		r.b += (t - r.a);
	}
	/* Return r*gamma(y). */
E 2
	yy = ratfun_gam(y - x0, 0);
D 2
	y = r.b*(yy.a+yy.b) + r.a*yy.b;
E 2
I 2
	y = r.b*(yy.a + yy.b) + r.a*yy.b;
E 2
	y += yy.a*r.a;
	return (y);
}
D 2
/* Good on (0, 1+x0+LEFT].  Accurate to 1ulp on [.25+x0+LEFT, 1+x0+LEFT].
 * Below this, x+LEFT-x0 introduces additional rounding errror of .5ulp.
E 2
I 2
/*
 * Good on (0, 1+x0+LEFT].  Accurate to 1ulp.
E 2
 */
static double
smaller_gam(x)
	double x;
{
	double t, d;
	struct Double r, xx;
	if (x < x0 + LEFT) {
		t = x, TRUNC(t);
		d = (t+x)*(x-t);
		t *= t;
D 2
		xx.a = ((d+t) + x), TRUNC(xx.a);
E 2
I 2
		xx.a = (t + x), TRUNC(xx.a);
E 2
		xx.b = x - xx.a; xx.b += t; xx.b += d;
D 2
		t = (1.0-x0); t += x;
		d = (1.0-x0); d -= t; d += x;
E 2
I 2
		t = (one-x0); t += x;
		d = (one-x0); d -= t; d += x;
E 2
		x = xx.a + xx.b;
	} else {
		xx.a =  x, TRUNC(xx.a);
		xx.b = x - xx.a;
		t = x - x0;
		d = (-x0 -t); d += x;
	}
	r = ratfun_gam(t, d);
	d = r.a/x, TRUNC(d);
	r.a -= d*xx.a; r.a -= d*xx.b; r.a += r.b;
	return (d + r.a/x);
}
D 2
/* returns (z+c)^2 * P(z)/Q(z) + a0 */
E 2
I 2
/*
 * returns (z+c)^2 * P(z)/Q(z) + a0
 */
E 2
static struct Double
ratfun_gam(z, c)
	double z, c;
{
	int i;
D 2
	double p, q, hi, lo;
	struct Double r;
E 2
I 2
	double p, q;
	struct Double r, t;
E 2

	q = Q0 +z*(Q1+z*(Q2+z*(Q3+z*(Q4+z*(Q5+z*(Q6+z*(Q7+z*Q8)))))));
	p = P0 + z*(P1 + z*(P2 + z*(P3 + z*P4)));

D 2
	/* return r.a + r.b = a0 + (z+c)^2 * p/q, with r.a truncated to 26 bits. */
E 2
I 2
	/* return r.a + r.b = a0 + (z+c)^2*p/q, with r.a truncated to 26 bits. */
E 2
	p = p/q;
D 2
	hi = z, TRUNC(hi);		/* hi+lo ~= z + c */
		lo = z - hi; lo += c;
	lo *= (hi+z);			/* q+lo = (z+c)*(z+c) */
	q = hi*hi;
	hi = (q + lo), TRUNC(hi);	/* hi+lo = q+lo */
		q -= hi;
		lo += q;
	z = p, TRUNC(z);		/* z+q = p */
		q = p - z;
	lo = lo*p + hi*q + a0_lo;
	hi *= z;
	r.a = hi + a0_hi, TRUNC(r.a);
	r.b = ((a0_hi-r.a) + hi) + lo;
	return (r);
E 2
I 2
	t.a = z, TRUNC(t.a);		/* t ~= z + c */
	t.b = (z - t.a) + c;
	t.b *= (t.a + z);
	q = (t.a *= t.a);		/* t = (z+c)^2 */
	TRUNC(t.a);
	t.b += (q - t.a);
	r.a = p, TRUNC(r.a);		/* r = P/Q */
	r.b = p - r.a;
	t.b = t.b*p + t.a*r.b + a0_lo;
	t.a *= r.a;			/* t = (z+c)^2*(P/Q) */
	r.a = t.a + a0_hi, TRUNC(r.a);
	r.b = ((a0_hi-r.a) + t.a) + t.b;
	return (r);			/* r = a0 + t */
E 2
}
D 2
#define lpi_hi 1.1447298858494001638
#define lpi_lo .0000000000000000102659511627078262
/* Error: within 3.5 ulp for x < 171.  For large x, see lgamma. */
E 2
I 2

E 2
static double
neg_gam(x)
	double x;
{
	int sgn = 1;
	struct Double lg, lsine;
D 2
	double y, z, one = 1.0, zero = 0.0;
E 2
I 2
	double y, z;

E 2
	y = floor(x + .5);
D 2
	if (y == x) {
		if (-x == infinity()) {	/* G(-inf) = NaN */
			errno = EDOM;
			return (signaling_nan(0));
		}
		errno = ERANGE;
		return (one/zero);	/* G(-(integer) -> oo */
	}
E 2
I 2
	if (y == x)		/* Negative integer. */
		if(!_IEEE)
			return (infnan(ERANGE));
		else
			return (one/zero);
E 2
	z = fabs(x - y);
D 2
	y = ceil(x);
	if (y*.5 == ceil(.5*y)) {
E 2
I 2
	y = .5*ceil(x);
	if (y == ceil(y))
E 2
		sgn = -1;
D 2
		printf("neg\n");
	}
	if (x < 1 - (6 + x0 + LEFT)) {
		if(x < -190) {
			UNDERFL;
			z = .5*ceil(x);
			if (z==ceil(z)) return (-0);
			else return (0);
		}
		y = 1 - x;
		if (1 - y == x) {
			lg = large_gam(y);
			lsine = log__D(sin(M_PI*z));
		} else {
			x = -x;
			lg = large_gam(x);
			lsine = log__D(x*sin(M_PI*z));
		}
		lg.b += lsine.b - lpi_lo;
		y = (-(lg.b + lsine.a) + lpi_hi) - lg.a;
		z = -lg.a - y; z+= lpi_hi; z -= lsine.a; z -= lg.b;
E 2
I 2
	if (z < .25)
		z = sin(M_PI*z);
	else
		z = cos(M_PI*(0.5-z));
	/* Special case: G(1-x) = Inf; G(x) may be nonzero. */
	if (x < -170) {
		if (x < -190)
			return ((double)sgn*tiny*tiny);
		y = one - x;		/* exact: 128 < |x| < 255 */
		lg = large_gam(y);
D 4
		lsine = log__D(M_PI/z);	/* = TRUNC(log(u)) + small */
		lg.a -= lsine.a;	/* exact (opposite signs) */
E 4
I 4
		lsine = __log__D(M_PI/z);	/* = TRUNC(log(u)) + small */
		lg.a -= lsine.a;		/* exact (opposite signs) */
E 4
		lg.b -= lsine.b;
		y = -(lg.a + lg.b);
D 3
		z = (y - lg.a) - lg.b;
E 3
I 3
		z = (y + lg.a) + lg.b;
E 3
E 2
D 4
		y = exp__D(y, z);
E 4
I 4
		y = __exp__D(y, z);
E 4
D 2
		if(sgn < 0) y = -y;
E 2
I 2
		if (sgn < 0) y = -y;
E 2
		return (y);
	}
D 2
	y = 1-x;
	if (1-y == x)
		y = ngamma(y);
E 2
I 2
	y = one-x;
	if (one-y == x)
		y = gamma(y);
E 2
	else		/* 1-x is inexact */
D 2
		y = -x*ngamma(-x);
E 2
I 2
		y = -x*gamma(-x);
E 2
	if (sgn < 0) y = -y;
D 2
	return (M_PI / (y*sin(M_PI*z)));
E 2
I 2
	return (M_PI / (y*z));
E 2
}
E 1
