h29626
s 00002/00002/00183
d D 8.1 93/06/11 15:09:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00183
d D 7.4 93/04/20 06:18:55 torek 4 3
c spelling
e
s 00004/00004/00181
d D 7.3 92/10/11 12:41:17 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00180
d D 7.2 92/07/21 16:39:02 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00180/00000/00000
d D 7.1 92/07/13 00:42:16 torek 1 0
c date and time created 92/07/13 00:42:16 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: fpu_add.c,v 1.3 92/06/17 18:11:43 mccanne Exp $
E 4
I 4
 * from: $Header: fpu_add.c,v 1.4 92/11/26 01:39:46 torek Exp $
E 4
 */

/*
 * Perform an FPU add (return x + y).
 *
 * To subtract, negate y and call add.
 */

D 3
#include "sys/types.h"
E 3
I 3
#include <sys/types.h>
E 3

D 3
#include "machine/reg.h"
E 3
I 3
#include <machine/reg.h>
E 3

D 3
#include "fpu_arith.h"
#include "fpu_emu.h"
E 3
I 3
#include <sparc/fpu/fpu_arith.h>
#include <sparc/fpu/fpu_emu.h>
E 3

struct fpn *
fpu_add(fe)
	register struct fpemu *fe;
{
	register struct fpn *x = &fe->fe_f1, *y = &fe->fe_f2, *r;
	register u_int r0, r1, r2, r3;
	register int rd;

	/*
	 * Put the `heavier' operand on the right (see fpu_emu.h).
	 * Then we will have one of the following cases, taken in the
	 * following order:
	 *
	 *  - y = NaN.  Implied: if only one is a signalling NaN, y is.
	 *	The result is y.
	 *  - y = Inf.  Implied: x != NaN (is 0, number, or Inf: the NaN
	 *    case was taken care of earlier).
	 *	If x = -y, the result is NaN.  Otherwise the result
	 *	is y (an Inf of whichever sign).
	 *  - y is 0.  Implied: x = 0.
	 *	If x and y differ in sign (one positive, one negative),
	 *	the result is +0 except when rounding to -Inf.  If same:
	 *	+0 + +0 = +0; -0 + -0 = -0.
	 *  - x is 0.  Implied: y != 0.
	 *	Result is y.
	 *  - other.  Implied: both x and y are numbers.
	 *	Do addition a la Hennessey & Patterson.
	 */
	ORDER(x, y);
	if (ISNAN(y))
		return (y);
	if (ISINF(y)) {
		if (ISINF(x) && x->fp_sign != y->fp_sign)
			return (fpu_newnan(fe));
		return (y);
	}
	rd = ((fe->fe_fsr >> FSR_RD_SHIFT) & FSR_RD_MASK);
	if (ISZERO(y)) {
		if (rd != FSR_RD_RM)	/* only -0 + -0 gives -0 */
			y->fp_sign &= x->fp_sign;
		else			/* any -0 operand gives -0 */
			y->fp_sign |= x->fp_sign;
		return (y);
	}
	if (ISZERO(x))
		return (y);
	/*
	 * We really have two numbers to add, although their signs may
	 * differ.  Make the exponents match, by shifting the smaller
	 * number right (e.g., 1.011 => 0.1011) and increasing its
	 * exponent (2^3 => 2^4).  Note that we do not alter the exponents
	 * of x and y here.
	 */
	r = &fe->fe_f3;
	r->fp_class = FPC_NUM;
	if (x->fp_exp == y->fp_exp) {
		r->fp_exp = x->fp_exp;
		r->fp_sticky = 0;
	} else {
		if (x->fp_exp < y->fp_exp) {
			/*
			 * Try to avoid subtract case iii (see below).
			 * This also guarantees that x->fp_sticky = 0.
			 */
			SWAP(x, y);
		}
		/* now x->fp_exp > y->fp_exp */
		r->fp_exp = x->fp_exp;
		r->fp_sticky = fpu_shr(y, x->fp_exp - y->fp_exp);
	}
	r->fp_sign = x->fp_sign;
	if (x->fp_sign == y->fp_sign) {
		FPU_DECL_CARRY

		/*
		 * The signs match, so we simply add the numbers.  The result
		 * may be `supernormal' (as big as 1.111...1 + 1.111...1, or
		 * 11.111...0).  If so, a single bit shift-right will fix it
		 * (but remember to adjust the exponent).
		 */
		/* r->fp_mant = x->fp_mant + y->fp_mant */
		FPU_ADDS(r->fp_mant[3], x->fp_mant[3], y->fp_mant[3]);
		FPU_ADDCS(r->fp_mant[2], x->fp_mant[2], y->fp_mant[2]);
		FPU_ADDCS(r->fp_mant[1], x->fp_mant[1], y->fp_mant[1]);
		FPU_ADDC(r0, x->fp_mant[0], y->fp_mant[0]);
		if ((r->fp_mant[0] = r0) >= FP_2) {
			(void) fpu_shr(r, 1);
			r->fp_exp++;
		}
	} else {
		FPU_DECL_CARRY

		/*
		 * The signs differ, so things are rather more difficult.
		 * H&P would have us negate the negative operand and add;
		 * this is the same as subtracting the negative operand.
		 * This is quite a headache.  Instead, we will subtract
		 * y from x, regardless of whether y itself is the negative
		 * operand.  When this is done one of three conditions will
		 * hold, depending on the magnitudes of x and y:
		 *   case i)   |x| > |y|.  The result is just x - y,
		 *	with x's sign, but it may need to be normalized.
		 *   case ii)  |x| = |y|.  The result is 0 (maybe -0)
		 *	so must be fixed up.
		 *   case iii) |x| < |y|.  We goofed; the result should
		 *	be (y - x), with the same sign as y.
		 * We could compare |x| and |y| here and avoid case iii,
		 * but that would take just as much work as the subtract.
		 * We can tell case iii has occurred by an overflow.
		 *
		 * N.B.: since x->fp_exp >= y->fp_exp, x->fp_sticky = 0.
		 */
		/* r->fp_mant = x->fp_mant - y->fp_mant */
		FPU_SET_CARRY(y->fp_sticky);
		FPU_SUBCS(r3, x->fp_mant[3], y->fp_mant[3]);
		FPU_SUBCS(r2, x->fp_mant[2], y->fp_mant[2]);
		FPU_SUBCS(r1, x->fp_mant[1], y->fp_mant[1]);
		FPU_SUBC(r0, x->fp_mant[0], y->fp_mant[0]);
		if (r0 < FP_2) {
			/* cases i and ii */
			if ((r0 | r1 | r2 | r3) == 0) {
				/* case ii */
				r->fp_class = FPC_ZERO;
				r->fp_sign = rd == FSR_RD_RM;
				return (r);
			}
		} else {
			/*
			 * Oops, case iii.  This can only occur when the
			 * exponents were equal, in which case neither
			 * x nor y have sticky bits set.  Flip the sign
			 * (to y's sign) and negate the result to get y - x.
			 */
#ifdef DIAGNOSTIC
			if (x->fp_exp != y->fp_exp || r->fp_sticky)
				panic("fpu_add");
#endif
			r->fp_sign = y->fp_sign;
			FPU_SUBS(r3, 0, r3);
			FPU_SUBCS(r2, 0, r2);
			FPU_SUBCS(r1, 0, r1);
			FPU_SUBC(r0, 0, r0);
		}
		r->fp_mant[3] = r3;
		r->fp_mant[2] = r2;
		r->fp_mant[1] = r1;
		r->fp_mant[0] = r0;
		if (r0 < FP_1)
			fpu_norm(r);
	}
	return (r);
}
E 1
