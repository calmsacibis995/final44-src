h04395
s 00002/00002/00119
d D 8.1 93/06/04 13:01:33 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00121/00000/00000
d D 5.1 92/06/25 06:17:00 torek 1 0
c date and time created 92/06/25 06:17:00 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: ldexp.c,v 1.1 91/07/07 04:28:19 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
static const char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <machine/ieee.h>
#include <errno.h>

/*
 * double ldexp(double val, int exp)
 * returns: val * (2**exp)
 */
double
ldexp(val, exp)
	double val;
	int exp;
{
	register int oldexp, newexp, mulexp;
	union doub {
		double v;
		struct ieee_double s;
	} u, mul;

	/*
	 * If input is zero, or no change, just return input.
	 * Likewise, if input is Inf or NaN, just return it.
	 */
	u.v = val;
	oldexp = u.s.dbl_exp;
	if (val == 0 || exp == 0 || oldexp == DBL_EXP_INFNAN)
		return (val);

	/*
	 * Compute new exponent and check for over/under flow.
	 * Underflow, unfortunately, could mean switching to denormal.
	 * If result out of range, set ERANGE and return 0 if too small
	 * or Inf if too big, with the same sign as the input value.
	 */
	newexp = oldexp + exp;
	if (newexp >= DBL_EXP_INFNAN) {
		/* u.s.dbl_sign = val < 0; -- already set */
		u.s.dbl_exp = DBL_EXP_INFNAN;
		u.s.dbl_frach = u.s.dbl_fracl = 0;
		errno = ERANGE;
		return (u.v);		/* Inf */
	}
	if (newexp <= 0) {
		/*
		 * The output number is either a denormal or underflows
		 * (see comments in machine/ieee.h).
		 */
		if (newexp <= -DBL_FRACBITS) {
			/* u.s.dbl_sign = val < 0; -- already set */
			u.s.dbl_exp = 0;
			u.s.dbl_frach = u.s.dbl_fracl = 0;
			errno = ERANGE;
			return (u.v);		/* zero */
		}
		/*
		 * We are going to produce a denorm.  Our `exp' argument
		 * might be as small as -2097, and we cannot compute
		 * 2^-2097, so we may have to do this as many as three
		 * steps (not just two, as for positive `exp's below).
		 */
		mul.v = 0;
		while (exp <= -DBL_EXP_BIAS) {
			mul.s.dbl_exp = 1;
			val *= mul.v;
			exp += DBL_EXP_BIAS - 1;
		}
		mul.s.dbl_exp = exp + DBL_EXP_BIAS;
		val *= mul.v;
		return (val);
	}

	/*
	 * Newexp is positive.
	 *
	 * If oldexp is zero, we are starting with a denorm, and simply
	 * adjusting the exponent will produce bogus answers.  We need
	 * to fix that first.
	 */
	if (oldexp == 0) {
		/*
		 * Multiply by 2^mulexp to make the number normalizable.
		 * We cannot multiply by more than 2^1023, but `exp'
		 * argument might be as large as 2046.  A single
		 * adjustment, however, will normalize the number even
		 * for huge `exp's, and then we can use exponent
		 * arithmetic just as for normal `double's.
		 */
		mulexp = exp <= DBL_EXP_BIAS ? exp : DBL_EXP_BIAS;
		mul.v = 0;
		mul.s.dbl_exp = mulexp + DBL_EXP_BIAS;
		val *= mul.v;
		if (mulexp == exp)
			return (val);
		u.v = val;
		newexp -= mulexp;
	}

	/*
	 * Both oldexp and newexp are positive; just replace the
	 * old exponent with the new one.
	 */
	u.s.dbl_exp = newexp;
	return (u.v);
}
E 1
