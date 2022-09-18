h18784
s 00002/00002/00190
d D 8.1 93/06/11 15:09:45 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00189
d D 7.4 93/04/20 06:14:01 torek 4 3
c spelling; fpu_norm fix from elf
e
s 00004/00004/00188
d D 7.3 92/10/11 12:41:23 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00187
d D 7.2 92/07/21 16:39:09 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00187/00000/00000
d D 7.1 92/07/13 00:42:20 torek 1 0
c date and time created 92/07/13 00:42:20 by torek
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
 * from: $Header: fpu_subr.c,v 1.2 92/06/17 05:41:35 torek Exp $
E 4
I 4
 * from: $Header: fpu_subr.c,v 1.4 92/12/01 08:46:52 torek Exp $
E 4
 */

/*
 * FPU subroutines.
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

/*
 * Shift the given number right rsh bits.  Any bits that `fall off' will get
 * shoved into the sticky field; we return the resulting sticky.  Note that
 * shifting NaNs is legal (this will never shift all bits out); a NaN's
 * sticky field is ignored anyway.
 */
int
fpu_shr(register struct fpn *fp, register int rsh)
{
	register u_int m0, m1, m2, m3, s;
	register int lsh;

#ifdef DIAGNOSTIC
	if (rsh <= 0 || (fp->fp_class != FPC_NUM && !ISNAN(fp)))
		panic("fpu_rightshift 1");
#endif

	m0 = fp->fp_mant[0];
	m1 = fp->fp_mant[1];
	m2 = fp->fp_mant[2];
	m3 = fp->fp_mant[3];

	/* If shifting all the bits out, take a shortcut. */
	if (rsh >= FP_NMANT) {
#ifdef DIAGNOSTIC
		if ((m0 | m1 | m2 | m3) == 0)
			panic("fpu_rightshift 2");
#endif
		fp->fp_mant[0] = 0;
		fp->fp_mant[1] = 0;
		fp->fp_mant[2] = 0;
		fp->fp_mant[3] = 0;
#ifdef notdef
		if ((m0 | m1 | m2 | m3) == 0)
			fp->fp_class = FPC_ZERO;
		else
#endif
			fp->fp_sticky = 1;
		return (1);
	}

	/* Squish out full words. */
	s = fp->fp_sticky;
	if (rsh >= 32 * 3) {
		s |= m3 | m2 | m1;
		m3 = m0, m2 = 0, m1 = 0, m0 = 0;
	} else if (rsh >= 32 * 2) {
		s |= m3 | m2;
		m3 = m1, m2 = m0, m1 = 0, m0 = 0;
	} else if (rsh >= 32) {
		s |= m3;
		m3 = m2, m2 = m1, m1 = m0, m0 = 0;
	}

	/* Handle any remaining partial word. */
	if ((rsh &= 31) != 0) {
		lsh = 32 - rsh;
		s |= m3 << lsh;
		m3 = (m3 >> rsh) | (m2 << lsh);
		m2 = (m2 >> rsh) | (m1 << lsh);
		m1 = (m1 >> rsh) | (m0 << lsh);
		m0 >>= rsh;
	}
	fp->fp_mant[0] = m0;
	fp->fp_mant[1] = m1;
	fp->fp_mant[2] = m2;
	fp->fp_mant[3] = m3;
	fp->fp_sticky = s;
	return (s);
}

/*
 * Force a number to be normal, i.e., make its fraction have all zero
 * bits before FP_1, then FP_1, then all 1 bits.  This is used for denorms
 * and (sometimes) for intermediate results.
 *
 * Internally, this may use a `supernormal' -- a number whose fp_mant
 * is greater than or equal to 2.0 -- so as a side effect you can hand it
 * a supernormal and it will fix it (provided fp->fp_mant[3] == 0).
 */
void
fpu_norm(register struct fpn *fp)
{
	register u_int m0, m1, m2, m3, top, sup, nrm;
	register int lsh, rsh, exp;

	exp = fp->fp_exp;
	m0 = fp->fp_mant[0];
	m1 = fp->fp_mant[1];
	m2 = fp->fp_mant[2];
	m3 = fp->fp_mant[3];

	/* Handle severe subnormals with 32-bit moves. */
	if (m0 == 0) {
		if (m1)
			m0 = m1, m1 = m2, m2 = m3, m3 = 0, exp -= 32;
		else if (m2)
			m0 = m2, m1 = m3, m2 = 0, m3 = 0, exp -= 2 * 32;
		else if (m3)
D 4
			m0 = m2, m1 = m3, m2 = 0, m3 = 0, exp -= 2 * 32;
E 4
I 4
			m0 = m3, m1 = 0, m2 = 0, m3 = 0, exp -= 3 * 32;
E 4
		else {
			fp->fp_class = FPC_ZERO;
			return;
		}
	}

	/* Now fix any supernormal or remaining subnormal. */
	nrm = FP_1;
	sup = nrm << 1;
	if (m0 >= sup) {
		/*
		 * We have a supernormal number.  We need to shift it right.
		 * We may assume m3==0.
		 */
		for (rsh = 1, top = m0 >> 1; top >= sup; rsh++)	/* XXX slow */
			top >>= 1;
		exp += rsh;
		lsh = 32 - rsh;
		m3 = m2 << lsh;
		m2 = (m2 >> rsh) | (m1 << lsh);
		m1 = (m1 >> rsh) | (m0 << lsh);
		m0 = top;
	} else if (m0 < nrm) {
		/*
		 * We have a regular denorm (a subnormal number), and need
		 * to shift it left.
		 */
		for (lsh = 1, top = m0 << 1; top < nrm; lsh++)	/* XXX slow */
			top <<= 1;
		exp -= lsh;
		rsh = 32 - lsh;
		m0 = top | (m1 >> rsh);
		m1 = (m1 << lsh) | (m2 >> rsh);
		m2 = (m2 << lsh) | (m3 >> rsh);
		m3 <<= lsh;
	}

	fp->fp_exp = exp;
	fp->fp_mant[0] = m0;
	fp->fp_mant[1] = m1;
	fp->fp_mant[2] = m2;
	fp->fp_mant[3] = m3;
}

/*
 * Concoct a `fresh' Quiet NaN per Appendix N.
 * As a side effect, we set NV (invalid) for the current exceptions.
 */
struct fpn *
fpu_newnan(register struct fpemu *fe)
{
	register struct fpn *fp;

	fe->fe_cx = FSR_NV;
	fp = &fe->fe_f3;
	fp->fp_class = FPC_QNAN;
	fp->fp_sign = 0;
	fp->fp_mant[0] = FP_1 - 1;
	fp->fp_mant[1] = fp->fp_mant[2] = fp->fp_mant[3] = ~0;
	return (fp);
}
E 1
