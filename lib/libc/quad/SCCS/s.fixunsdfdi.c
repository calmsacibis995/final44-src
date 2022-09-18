h54954
s 00002/00002/00068
d D 8.1 93/06/04 12:56:27 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00065
d D 5.5 92/07/13 21:25:21 torek 5 4
c work around gcc bug comparing double with unsigned quad
e
s 00004/00007/00061
d D 5.4 92/06/25 09:34:21 bostic 4 3
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00051/00049/00017
d D 5.3 92/06/02 13:35:10 bostic 3 2
c new version from Chris Torek
e
s 00024/00000/00042
d D 5.2 92/05/12 18:22:02 bostic 2 1
c Prepend the gcc-2.1 release copyright notice to all source code
e
s 00042/00000/00000
d D 5.1 92/05/12 15:20:00 bostic 1 0
c put on a Berkeley copyright notice -- original didn't have a GNU
c copyright, I'll add one as soon as I find out which one to add
c date and time created 92/05/12 15:20:00 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
I 3
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
E 3
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 2
D 3
/* Copyright (C) 1989, 1992 Free Software Foundation, Inc.
E 3
I 3
#include "quad.h"
E 3

D 3
This file is part of GNU CC.
E 3
I 3
D 4
#ifndef UQUAD_MAX	/* should be in <limits.h> maybe? */
#define	UQUAD_MAX ((u_quad)0 - 1)
#endif
E 3

E 4
D 3
GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.
E 3
I 3
#define	ONE_FOURTH	(1 << (LONG_BITS - 2))
#define	ONE_HALF	(ONE_FOURTH * 2.0)
#define	ONE		(ONE_FOURTH * 4.0)
E 3

D 3
GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, if you link this library with files
   compiled with GCC to produce an executable, this does not cause
   the resulting executable to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

E 2
#include "longlong.h"

#define HIGH_WORD_COEFF (((long long) 1) << BITS_PER_WORD)

long long
__fixunsdfdi (a)
     double a;
E 3
I 3
/*
 * Convert double to (unsigned) quad.
 * Not sure what to do with negative numbers---for now, anything out
 * of range becomes UQUAD_MAX.
 */
D 4
u_quad
__fixunsdfdi(double x)
E 4
I 4
u_quad_t
__fixunsdfdi(x)
	double x;
E 4
E 3
{
D 3
  double b;
  unsigned long long v;
E 3
I 3
	double toppart;
	union uu t;
E 3

D 3
  if (a < 0)
    return 0;

  /* Compute high word of result, as a flonum.  */
  b = (a / HIGH_WORD_COEFF);
  /* Convert that to fixed (but not to long long!),
     and shift it into the high word.  */
  v = (unsigned long int) b;
  v <<= BITS_PER_WORD;
  /* Remove high part from the double, leaving the low part as flonum.  */
  a -= (double)v;
  /* Convert that to fixed (but not to long long!) and add it in.
     Sometimes A comes out negative.  This is significant, since
     A has more bits than a long int does.  */
  if (a < 0)
    v -= (unsigned long int) (- a);
  else
    v += (unsigned long int) a;
  return v;
E 3
I 3
	if (x < 0)
		return (UQUAD_MAX);	/* ??? should be 0?  ERANGE??? */
I 5
#ifdef notdef				/* this falls afoul of a GCC bug */
E 5
	if (x >= UQUAD_MAX)
		return (UQUAD_MAX);
I 5
#else					/* so we wire in 2^64-1 instead */
	if (x >= 18446744073709551615.0)
		return (UQUAD_MAX);
#endif
E 5
	/*
	 * Get the upper part of the result.  Note that the divide
	 * may round up; we want to avoid this if possible, so we
	 * subtract `1/2' first.
	 */
	toppart = (x - ONE_HALF) / ONE;
	/*
D 4
	 * Now build a u_quad out of the top part.  The difference
E 4
I 4
	 * Now build a u_quad_t out of the top part.  The difference
E 4
	 * between x and this is the bottom part (this may introduce
	 * a few fuzzy bits, but what the heck).  With any luck this
	 * difference will be nonnegative: x should wind up in the
	 * range [0..ULONG_MAX].  For paranoia, we assume [LONG_MIN..
	 * 2*ULONG_MAX] instead.
	 */
	t.ul[H] = (unsigned long)toppart;
	t.ul[L] = 0;
	x -= (double)t.uq;
	if (x < 0) {
		t.ul[H]--;
		x += ULONG_MAX;
	}
	if (x > ULONG_MAX) {
		t.ul[H]++;
		x -= ULONG_MAX;
	}
	t.ul[L] = (u_long)x;
	return (t.uq);
E 3
}
E 1
