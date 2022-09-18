h64128
s 00002/00002/00251
d D 8.1 93/06/04 12:57:09 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00250
d D 5.7 92/06/25 09:34:28 bostic 7 6
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00219/00203/00033
d D 5.6 92/06/02 13:35:25 bostic 6 5
c new version from Chris Torek
e
s 00024/00000/00212
d D 5.5 92/05/12 18:21:59 bostic 5 4
c Prepend the gcc-2.1 release copyright notice to all source code
e
s 00016/00004/00196
d D 5.4 92/05/12 18:14:27 bostic 4 3
c avoid use of alloca
e
s 00011/00000/00189
d D 5.3 92/05/12 15:19:16 bostic 3 2
c put on a Berkeley copyright notice -- original didn't have a GNU
c copyright, I'll add one as soon as I find out which one to add
e
s 00006/00002/00183
d D 5.2 91/11/19 14:57:04 mckusick 2 1
c remove libc dependencies
e
s 00185/00000/00000
d D 5.1 91/11/19 14:51:13 mckusick 1 0
c date and time created 91/11/19 14:51:13 by mckusick
e
u
U
t
T
I 3
/*-
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
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
/*
 * Multiprecision divide.  This algorithm is from Knuth vol. 2 (2nd ed),
 * section 4.3.1, pp. 257--259.
 */
E 6

D 6
This file is part of GNU CC.
E 6
I 6
#include "quad.h"
E 6

D 6
GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.
E 6
I 6
#define	B	(1 << HALF_BITS)	/* digit base */
E 6

D 6
GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
E 6
I 6
/* Combine two `digits' to make a single two-digit number. */
#define	COMBINE(a, b) (((u_long)(a) << HALF_BITS) | (b))
E 6

D 6
You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, if you link this library with files
   compiled with GCC to produce an executable, this does not cause
   the resulting executable to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

E 5
I 4
#include <unistd.h>

E 4
E 3
I 1
#include "longlong.h"

static int bshift ();

/* Divide a by b, producing quotient q and remainder r.

       sizeof a is m
       sizeof b is n
       sizeof q is m - n
       sizeof r is n

   The quotient must fit in m - n bytes, i.e., the most significant
   n digits of a must be less than b, and m must be greater than n.  */

/* The name of this used to be __div_internal,
   but that is too long for SYSV.  */

void 
__bdiv (a, b, q, r, m, n)
     unsigned short *a, *b, *q, *r;
D 4
     size_t m, n;
E 4
I 4
     unsigned long m, n;
E 4
{
  unsigned long qhat, rhat;
  unsigned long acc;
D 4
  unsigned short *u = (unsigned short *) alloca (m);
  unsigned short *v = (unsigned short *) alloca (n);
  unsigned short *u0, *u1, *u2;
E 4
I 4
  unsigned short array[12];
  unsigned short *u, *v, *u0, *u1, *u2;
E 4
  unsigned short *v0;
  int d, qn;
  int i, j;

I 4
  if (m > 16 || n > 8) {
#ifdef KERNEL
	panic("bdiv: out of space");
E 6
I 6
/* select a type for digits in base B: use unsigned short if they fit */
#if ULONG_MAX == 0xffffffff && USHRT_MAX >= 0xffff
typedef unsigned short digit;
E 6
#else
D 6
#define	EMSG	"bdiv: out of space."
	(void)write(STDERR_FILENO, EMSG, sizeof(EMSG) - 1);
	abort();
E 6
I 6
typedef u_long digit;
E 6
#endif
D 6
  }
  u = &array[0];
  v = &array[m / sizeof(unsigned short)];
E 4
  m /= sizeof *a;
  n /= sizeof *b;
  qn = m - n;
E 6

D 6
  /* Remove leading zero digits from divisor, and the same number of
     digits (which must be zero) from dividend.  */
E 6
I 6
/*
 * Shift p[0]..p[len] left `sh' bits, ignoring any bits that
 * `fall out' the left (there never will be any such anyway).
 * We may assume len >= 0.  NOTE THAT THIS WRITES len+1 DIGITS.
 */
static void
shl(register digit *p, register int len, register int sh)
{
	register int i;
E 6

D 6
  while (b[big_end (n)] == 0)
    {
      r[big_end (n)] = 0;
E 6
I 6
	for (i = 0; i < len; i++)
		p[i] = LHALF(p[i] << sh) | (p[i + 1] >> (HALF_BITS - sh));
	p[i] = LHALF(p[i] << sh);
}
E 6

D 6
      a += little_end (2);
      b += little_end (2);
      r += little_end (2);
      m--;
      n--;
E 6
I 6
/*
 * __qdivrem(u, v, rem) returns u/v and, optionally, sets *rem to u%v.
 *
 * We do this in base 2-sup-HALF_BITS, so that all intermediate products
 * fit within u_long.  As a consequence, the maximum length dividend and
 * divisor are 4 `digits' in this base (they are shorter if they have
 * leading zeros).
 */
D 7
u_quad
__qdivrem(u_quad uq, u_quad vq, u_quad *arq)
E 7
I 7
u_quad_t
__qdivrem(uq, vq, arq)
	u_quad_t uq, vq, *arq;
E 7
{
	union uu tmp;
	digit *u, *v, *q;
	register digit v1, v2;
	u_long qhat, rhat, t;
	int m, n, d, j, i;
	digit uspace[5], vspace[5], qspace[5];
E 6

D 6
      /* Check for zero divisor.  */
      if (n == 0)
D 2
	abort ();
E 2
I 2
      {
	*r /= n;	/* force a divide-by-zero trap */
	return;
      }
E 2
    }
      
  /* If divisor is a single digit, do short division.  */
E 6
I 6
	/*
	 * Take care of special cases: divide by zero, and u < v.
	 */
	if (vq == 0) {
		/* divide by zero. */
		static volatile const unsigned int zero = 0;
E 6

D 6
  if (n == 1)
    {
      acc = a[big_end (m)];
      a += little_end (2);
      for (j = big_end (qn); is_not_lsd (j, qn); j = next_lsd (j))
	{
	  acc = (acc << 16) | a[j];
	  q[j] = acc / *b;
	  acc = acc % *b;
E 6
I 6
		tmp.ul[H] = tmp.ul[L] = 1 / zero;
		if (arq)
			*arq = uq;
		return (tmp.q);
E 6
	}
D 6
      *r = acc;
      return;
    }
E 6
I 6
	if (uq < vq) {
		if (arq)
			*arq = uq;
		return (0);
	}
	u = &uspace[0];
	v = &vspace[0];
	q = &qspace[0];
E 6

D 6
  /* No such luck, must do long division. Shift divisor and dividend
     left until the high bit of the divisor is 1.  */
E 6
I 6
	/*
	 * Break dividend and divisor into digits in base B, then
	 * count leading zeros to determine m and n.  When done, we
	 * will have:
	 *	u = (u[1]u[2]...u[m+n]) sub B
	 *	v = (v[1]v[2]...v[n]) sub B
	 *	v[1] != 0
	 *	1 < n <= 4 (if n = 1, we use a different division algorithm)
	 *	m >= 0 (otherwise u < v, which we already checked)
	 *	m + n = 4
	 * and thus
	 *	m = 4 - n <= 2
	 */
	tmp.uq = uq;
	u[0] = 0;
	u[1] = HHALF(tmp.ul[H]);
	u[2] = LHALF(tmp.ul[H]);
	u[3] = HHALF(tmp.ul[L]);
	u[4] = LHALF(tmp.ul[L]);
	tmp.uq = vq;
	v[1] = HHALF(tmp.ul[H]);
	v[2] = LHALF(tmp.ul[H]);
	v[3] = HHALF(tmp.ul[L]);
	v[4] = LHALF(tmp.ul[L]);
	for (n = 4; v[1] == 0; v++) {
		if (--n == 1) {
			u_long rbj;	/* r*B+u[j] (not root boy jim) */
			digit q1, q2, q3, q4;
E 6

D 6
  for (d = 0; d < 16; d++)
    if (b[big_end (n)] & (1 << (16 - 1 - d)))
      break;

  bshift (a, d, u, 0, m);
  bshift (b, d, v, 0, n);

  /* Get pointers to the high dividend and divisor digits.  */

  u0 = u + big_end (m) - big_end (qn);
  u1 = next_lsd (u0);
  u2 = next_lsd (u1);
  u += little_end (2);

  v0 = v + big_end (n);

  /* Main loop: find a quotient digit, multiply it by the divisor,
     and subtract that from the dividend, shifted over the right amount. */

  for (j = big_end (qn); is_not_lsd (j, qn); j = next_lsd (j))
    {
      /* Quotient digit initial guess: high 2 dividend digits over high
	 divisor digit.  */

      if (u0[j] == *v0)
	{
	  qhat = B - 1;
	  rhat = (unsigned long) *v0 + u1[j];
E 6
I 6
			/*
			 * Change of plan, per exercise 16.
			 *	r = 0;
			 *	for j = 1..4:
			 *		q[j] = floor((r*B + u[j]) / v),
			 *		r = (r*B + u[j]) % v;
			 * We unroll this completely here.
			 */
			t = v[2];	/* nonzero, by definition */
			q1 = u[1] / t;
			rbj = COMBINE(u[1] % t, u[2]);
			q2 = rbj / t;
			rbj = COMBINE(rbj % t, u[3]);
			q3 = rbj / t;
			rbj = COMBINE(rbj % t, u[4]);
			q4 = rbj / t;
			if (arq)
				*arq = rbj % t;
			tmp.ul[H] = COMBINE(q1, q2);
			tmp.ul[L] = COMBINE(q3, q4);
			return (tmp.q);
		}
E 6
	}
D 6
      else
	{
	  unsigned long numerator = ((unsigned long) u0[j] << 16) | u1[j];
	  qhat = numerator / *v0;
	  rhat = numerator % *v0;
	}
E 6

D 6
      /* Now get the quotient right for high 3 dividend digits over
	 high 2 divisor digits.  */
E 6
I 6
	/*
	 * By adjusting q once we determine m, we can guarantee that
	 * there is a complete four-digit quotient at &qspace[1] when
	 * we finally stop.
	 */
	for (m = 4 - n; u[1] == 0; u++)
		m--;
	for (i = 4 - m; --i >= 0;)
		q[i] = 0;
	q += 4 - m;
E 6

D 6
      while (rhat < B && qhat * *next_lsd (v0) > ((rhat << 16) | u2[j]))
	{
	  qhat -= 1;
	  rhat += *v0;
E 6
I 6
	/*
	 * Here we run Program D, translated from MIX to C and acquiring
	 * a few minor changes.
	 *
	 * D1: choose multiplier 1 << d to ensure v[1] >= B/2.
	 */
	d = 0;
	for (t = v[1]; t < B / 2; t <<= 1)
		d++;
	if (d > 0) {
		shl(&u[0], m + n, d);		/* u <<= d */
		shl(&v[1], n - 1, d);		/* v <<= d */
E 6
	}
D 6
	    
      /* Multiply quotient by divisor, subtract from dividend.  */
E 6
I 6
	/*
	 * D2: j = 0.
	 */
	j = 0;
	v1 = v[1];	/* for D3 -- note that v[1..n] are constant */
	v2 = v[2];	/* for D3 */
	do {
		register digit uj0, uj1, uj2;
		
		/*
		 * D3: Calculate qhat (\^q, in TeX notation).
		 * Let qhat = min((u[j]*B + u[j+1])/v[1], B-1), and
		 * let rhat = (u[j]*B + u[j+1]) mod v[1].
		 * While rhat < B and v[2]*qhat > rhat*B+u[j+2],
		 * decrement qhat and increase rhat correspondingly.
		 * Note that if rhat >= B, v[2]*qhat < rhat*B.
		 */
		uj0 = u[j + 0];	/* for D3 only -- note that u[j+...] change */
		uj1 = u[j + 1];	/* for D3 only */
		uj2 = u[j + 2];	/* for D3 only */
		if (uj0 == v1) {
			qhat = B;
			rhat = uj1;
			goto qhat_too_big;
		} else {
			u_long n = COMBINE(uj0, uj1);
			qhat = n / v1;
			rhat = n % v1;
		}
		while (v2 * qhat > COMBINE(rhat, uj2)) {
	qhat_too_big:
			qhat--;
			if ((rhat += v1) >= B)
				break;
		}
		/*
		 * D4: Multiply and subtract.
		 * The variable `t' holds any borrows across the loop.
		 * We split this up so that we do not require v[0] = 0,
		 * and to eliminate a final special case.
		 */
		for (t = 0, i = n; i > 0; i--) {
			t = u[i + j] - v[i] * qhat - t;
			u[i + j] = LHALF(t);
			t = (B - HHALF(t)) & (B - 1);
		}
		t = u[j] - t;
		u[j] = LHALF(t);
		/*
		 * D5: test remainder.
		 * There is a borrow if and only if HHALF(t) is nonzero;
		 * in that (rare) case, qhat was too large (by exactly 1).
		 * Fix it by adding v[1..n] to u[j..j+n].
		 */
		if (HHALF(t)) {
			qhat--;
			for (t = 0, i = n; i > 0; i--) { /* D6: add back. */
				t += u[i + j] + v[i];
				u[i + j] = LHALF(t);
				t = HHALF(t);
			}
			u[j] = LHALF(u[j] + t);
		}
		q[j] = qhat;
	} while (++j <= m);		/* D7: loop on j. */
E 6

D 6
      acc = 0;
      for (i = little_end (n); is_not_msd (i, n); i = next_msd (i))
	{
	  acc += (unsigned long) (u + j)[i] - v[i] * qhat;
	  (u + j)[i] = acc & low16;
	  if (acc < B)
	    acc = 0;
	  else
	    acc = (acc >> 16) | -B;
E 6
I 6
	/*
	 * If caller wants the remainder, we have to calculate it as
	 * u[m..m+n] >> d (this is at most n digits and thus fits in
	 * u[m+1..m+n], but we may need more source digits).
	 */
	if (arq) {
		if (d) {
			for (i = m + n; i > m; --i)
				u[i] = (u[i] >> d) |
				    LHALF(u[i - 1] << (HALF_BITS - d));
			u[i] = 0;
		}
		tmp.ul[H] = COMBINE(uspace[1], uspace[2]);
		tmp.ul[L] = COMBINE(uspace[3], uspace[4]);
		*arq = tmp.q;
E 6
	}

D 6
      q[j] = qhat;

      /* Quotient may have been too high by 1.  If dividend went negative,
	 decrement the quotient by 1 and add the divisor back.  */

      if ((signed long) (acc + u0[j]) < 0)
	{
	  q[j] -= 1;
	  acc = 0;
	  for (i = little_end (n); is_not_msd (i, n); i = next_msd (i))
	    {
	      acc += (unsigned long) (u + j)[i] + v[i];
	      (u + j)[i] = acc & low16;
	      acc = acc >> 16;
	    }
	}
    }

  /* Now the remainder is what's left of the dividend, shifted right
     by the amount of the normalizing left shift at the top.  */

  r[big_end (n)] = bshift (u + 1 + little_end (j - 1),
			   16 - d,
			   r + little_end (2),
			   u[little_end (m - 1)] >> d,
			   n - 1);
}

/* Left shift U by K giving W; fill the introduced low-order bits with
   CARRY_IN.  Length of U and W is N.  Return carry out.  K must be
   in 0 .. 16.  */

static int
bshift (u, k, w, carry_in, n)
     unsigned short *u, *w, carry_in;
     int k, n;
{
  unsigned long acc;
  int i;

  if (k == 0)
    {
D 2
      bcopy (u, w, n * sizeof *u);
E 2
I 2
      while (n-- > 0)
        *w++ = *u++;
E 2
      return 0;
    }

  acc = carry_in;
  for (i = little_end (n); is_not_msd (i, n); i = next_msd (i))
    {
      acc |= (unsigned long) u[i] << k;
      w[i] = acc & low16;
      acc = acc >> 16;
    }
  return acc;
E 6
I 6
	tmp.ul[H] = COMBINE(qspace[1], qspace[2]);
	tmp.ul[L] = COMBINE(qspace[3], qspace[4]);
	return (tmp.q);
E 6
}
E 1
