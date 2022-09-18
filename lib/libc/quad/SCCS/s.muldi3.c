h37949
s 00002/00002/00218
d D 8.1 93/06/04 12:56:59 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00215
d D 5.8 92/06/25 09:34:26 bostic 8 7
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00001/00001/00218
d D 5.7 92/06/02 23:11:05 torek 7 6
c rm extraneous `>> 16'
e
s 00190/00062/00029
d D 5.6 92/06/02 13:35:22 bostic 6 5
c new version from Chris Torek
e
s 00024/00000/00067
d D 5.5 92/05/12 18:22:07 bostic 5 4
c Prepend the gcc-2.1 release copyright notice to all source code
e
s 00001/00001/00066
d D 5.4 92/05/12 18:16:59 bostic 4 3
c size_t is unsigned long for these routines
e
s 00011/00000/00056
d D 5.3 92/05/12 15:19:17 bostic 3 2
c put on a Berkeley copyright notice -- original didn't have a GNU
c copyright, I'll add one as soon as I find out which one to add
e
s 00004/00002/00052
d D 5.2 91/11/19 14:57:05 mckusick 2 1
c remove libc dependencies
e
s 00054/00000/00000
d D 5.1 91/11/19 14:54:08 mckusick 1 0
c date and time created 91/11/19 14:54:08 by mckusick
e
u
U
t
T
I 3
/*-
D 9
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
I 6
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
E 6
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 5
D 6
/* Copyright (C) 1989, 1992 Free Software Foundation, Inc.
E 6
I 6
#include "quad.h"
E 6

D 6
This file is part of GNU CC.
E 6
I 6
/*
 * Multiply two quads.
 *
 * Our algorithm is based on the following.  Split incoming quad values
 * u and v (where u,v >= 0) into
 *
 *	u = 2^n u1  *  u0	(n = number of bits in `u_long', usu. 32)
 *
 * and 
 *
 *	v = 2^n v1  *  v0
 *
 * Then
 *
 *	uv = 2^2n u1 v1  +  2^n u1 v0  +  2^n v1 u0  +  u0 v0
 *	   = 2^2n u1 v1  +     2^n (u1 v0 + v1 u0)   +  u0 v0
 *
 * Now add 2^n u1 v1 to the first term and subtract it from the middle,
 * and add 2^n u0 v0 to the last term and subtract it from the middle.
 * This gives:
 *
 *	uv = (2^2n + 2^n) (u1 v1)  +
 *	         (2^n)    (u1 v0 - u1 v1 + u0 v1 - u0 v0)  +
 *	       (2^n + 1)  (u0 v0)
 *
 * Factoring the middle a bit gives us:
 *
 *	uv = (2^2n + 2^n) (u1 v1)  +			[u1v1 = high]
 *		 (2^n)    (u1 - u0) (v0 - v1)  +	[(u1-u0)... = mid]
 *	       (2^n + 1)  (u0 v0)			[u0v0 = low]
 *
 * The terms (u1 v1), (u1 - u0) (v0 - v1), and (u0 v0) can all be done
 * in just half the precision of the original.  (Note that either or both
 * of (u1 - u0) or (v0 - v1) may be negative.)
 *
 * This algorithm is from Knuth vol. 2 (2nd ed), section 4.3.3, p. 278.
 *
 * Since C does not give us a `long * long = quad' operator, we split
 * our input quads into two longs, then split the two longs into two
 * shorts.  We can then calculate `short * short = long' in native
 * arithmetic.
 *
 * Our product should, strictly speaking, be a `long quad', with 128
 * bits, but we are going to discard the upper 64.  In other words,
 * we are not interested in uv, but rather in (uv mod 2^2n).  This
 * makes some of the terms above vanish, and we get:
 *
 *	(2^n)(high) + (2^n)(mid) + (2^n + 1)(low)
 *
 * or
 *
 *	(2^n)(high + mid + low) + low
 *
 * Furthermore, `high' and `mid' can be computed mod 2^n, as any factor
 * of 2^n in either one will also vanish.  Only `low' need be computed
 * mod 2^2n, and only because of the final term above.
 */
D 8
static quad __lmulq(u_long, u_long);
E 8
I 8
static quad_t __lmulq(u_long, u_long);
E 8
E 6

D 6
GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.
E 6
I 6
D 8
quad
__muldi3(quad a, quad b)
E 8
I 8
quad_t
__muldi3(a, b)
	quad_t a, b;
E 8
{
	union uu u, v, low, prod;
	register u_long high, mid, udiff, vdiff;
	register int negall, negmid;
#define	u1	u.ul[H]
#define	u0	u.ul[L]
#define	v1	v.ul[H]
#define	v0	v.ul[L]
E 6

D 6
GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
E 6
I 6
	/*
	 * Get u and v such that u, v >= 0.  When this is finished,
	 * u1, u0, v1, and v0 will be directly accessible through the
	 * longword fields.
	 */
	if (a >= 0)
		u.q = a, negall = 0;
	else
		u.q = -a, negall = 1;
	if (b >= 0)
		v.q = b;
	else
		v.q = -b, negall ^= 1;
E 6

D 6
You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */
E 6
I 6
	if (u1 == 0 && v1 == 0) {
		/*
		 * An (I hope) important optimization occurs when u1 and v1
		 * are both 0.  This should be common since most numbers
		 * are small.  Here the product is just u0*v0.
		 */
		prod.q = __lmulq(u0, v0);
	} else {
		/*
		 * Compute the three intermediate products, remembering
		 * whether the middle term is negative.  We can discard
		 * any upper bits in high and mid, so we can use native
		 * u_long * u_long => u_long arithmetic.
		 */
		low.q = __lmulq(u0, v0);
E 6

D 6
/* As a special exception, if you link this library with files
   compiled with GCC to produce an executable, this does not cause
   the resulting executable to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */
E 6
I 6
		if (u1 >= u0)
			negmid = 0, udiff = u1 - u0;
		else
			negmid = 1, udiff = u0 - u1;
		if (v0 >= v1)
			vdiff = v0 - v1;
		else
			vdiff = v1 - v0, negmid ^= 1;
		mid = udiff * vdiff;
E 6

E 5
E 3
I 1
D 6
#include "longlong.h"
E 6
I 6
		high = u1 * v1;
E 6

D 6
static void bmul ();
E 6
I 6
		/*
		 * Assemble the final product.
		 */
		prod.ul[H] = high + (negmid ? -mid : mid) + low.ul[L] +
		    low.ul[H];
		prod.ul[L] = low.ul[L];
	}
	return (negall ? -prod.q : prod.q);
#undef u1
#undef u0
#undef v1
#undef v0
}
E 6

D 6
long long 
__muldi3 (u, v)
     long long u, v;
E 6
I 6
/*
 * Multiply two 2N-bit longs to produce a 4N-bit quad, where N is half
 * the number of bits in a long (whatever that is---the code below
 * does not care as long as quad.h does its part of the bargain---but
 * typically N==16).
 *
 * We use the same algorithm from Knuth, but this time the modulo refinement
 * does not apply.  On the other hand, since N is half the size of a long,
 * we can get away with native multiplication---none of our input terms
 * exceeds (ULONG_MAX >> 1).
 *
 * Note that, for u_long l, the quad-precision result
 *
 *	l << N
 *
 * splits into high and low longs as HHALF(l) and LHUP(l) respectively.
 */
D 8
static quad
E 8
I 8
static quad_t
E 8
__lmulq(u_long u, u_long v)
E 6
{
D 6
  long a[2], b[2], c[2][2];
  long_long w;
  long_long uu, vv;
E 6
I 6
	u_long u1, u0, v1, v0, udiff, vdiff, high, mid, low;
	u_long prodh, prodl, was;
	union uu prod;
	int neg;
E 6

D 6
  uu.ll = u;
  vv.ll = v;
E 6
I 6
	u1 = HHALF(u);
	u0 = LHALF(u);
	v1 = HHALF(v);
	v0 = LHALF(v);
E 6

D 6
  a[HIGH] = uu.s.high;
  a[LOW] = uu.s.low;
  b[HIGH] = vv.s.high;
  b[LOW] = vv.s.low;
E 6
I 6
	low = u0 * v0;
E 6

D 6
  bmul (a, b, c, sizeof a, sizeof b);
E 6
I 6
	/* This is the same small-number optimization as before. */
	if (u1 == 0 && v1 == 0)
		return (low);
E 6

D 6
  w.s.high = c[LOW][HIGH];
  w.s.low = c[LOW][LOW];
  return w.ll;
}
E 6
I 6
	if (u1 >= u0)
		udiff = u1 - u0, neg = 0;
	else
		udiff = u0 - u1, neg = 1;
	if (v0 >= v1)
		vdiff = v0 - v1;
	else
		vdiff = v1 - v0, neg ^= 1;
	mid = udiff * vdiff;
E 6

D 6
static void 
bmul (a, b, c, m, n)
    unsigned short *a, *b, *c;
D 4
    size_t m, n;
E 4
I 4
    unsigned long m, n;
E 4
{
  int i, j;
I 2
  unsigned short *d;
E 2
  unsigned long acc;
E 6
I 6
	high = u1 * v1;
E 6

D 2
  bzero (c, m + n);

E 2
D 6
  m /= sizeof *a;
  n /= sizeof *b;
E 6
I 6
	/* prod = (high << 2N) + (high << N); */
	prodh = high + HHALF(high);
	prodl = LHUP(high);
E 6
I 2

D 6
  for (i = m + n, d = c; i-- > 0; *d++ = 0)
    ;
E 2

  for (j = little_end (n); is_not_msd (j, n); j = next_msd (j))
    {
      unsigned short *c1 = c + j + little_end (2);
      acc = 0;
      for (i = little_end (m); is_not_msd (i, m); i = next_msd (i))
	{
	  /* Widen before arithmetic to avoid loss of high bits.  */
	  acc += (unsigned long) a[i] * b[j] + c1[i];
	  c1[i] = acc & low16;
	  acc = acc >> 16;
E 6
I 6
	/* if (neg) prod -= mid << N; else prod += mid << N; */
	if (neg) {
		was = prodl;
		prodl -= LHUP(mid);
		prodh -= HHALF(mid) + (prodl > was);
	} else {
		was = prodl;
		prodl += LHUP(mid);
D 7
		prodh += HHALF(mid >> 16) + (prodl < was);
E 7
I 7
		prodh += HHALF(mid) + (prodl < was);
E 7
E 6
	}
D 6
      c1[i] = acc;
    }
E 6
I 6

	/* prod += low << N */
	was = prodl;
	prodl += LHUP(low);
	prodh += HHALF(low) + (prodl < was);
	/* ... + low; */
	if ((prodl += low) < low)
		prodh++;

	/* return 4N-bit product */
	prod.ul[H] = prodh;
	prod.ul[L] = prodl;
	return (prod.q);
E 6
}
E 1
