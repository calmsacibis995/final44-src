h16823
s 00002/00002/00046
d D 8.1 93/06/04 12:56:35 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00046
d D 5.4 92/06/25 09:34:22 bostic 4 3
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00029/00039/00018
d D 5.3 92/06/02 13:35:12 bostic 3 2
c new version from Chris Torek
e
s 00024/00000/00033
d D 5.2 92/05/12 18:22:03 bostic 2 1
c Prepend the gcc-2.1 release copyright notice to all source code
e
s 00033/00000/00000
d D 5.1 92/05/12 15:20:01 bostic 1 0
c put on a Berkeley copyright notice -- original didn't have a GNU
c copyright, I'll add one as soon as I find out which one to add
c date and time created 92/05/12 15:20:01 by bostic
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

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

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

#define HIGH_HALFWORD_COEFF (((long long) 1) << (BITS_PER_WORD / 2))
#define HIGH_WORD_COEFF (((long long) 1) << BITS_PER_WORD)

E 3
I 3
/*
 * Convert (signed) quad to double.
 */
E 3
double
D 3
__floatdidf (u)
     long long u;
E 3
I 3
D 4
__floatdidf(quad x)
E 4
I 4
__floatdidf(x)
	quad_t x;
E 4
E 3
{
D 3
  double d;
  int negate = 0;
E 3
I 3
	double d;
	union uu u;
	int neg;
E 3

D 3
  if (u < 0)
    u = -u, negate = 1;
E 3
I 3
	/*
	 * Get an unsigned number first, by negating if necessary.
	 */
	if (x < 0)
		u.q = -x, neg = 1;
	else
		u.q = x, neg = 0;
E 3

D 3
  d = (unsigned int) (u >> BITS_PER_WORD);
  d *= HIGH_HALFWORD_COEFF;
  d *= HIGH_HALFWORD_COEFF;
  d += (unsigned int) (u & (HIGH_WORD_COEFF - 1));
E 3
I 3
	/*
	 * Now u.ul[H] has the factor of 2^32 (or whatever) and u.ul[L]
	 * has the units.  Ideally we could just set d, add LONG_BITS to
	 * its exponent, and then add the units, but this is portable
	 * code and does not know how to get at an exponent.  Machine-
	 * specific code may be able to do this more efficiently.
	 */
	d = (double)u.ul[H] * ((1 << (LONG_BITS - 2)) * 4.0);
	d += u.ul[L];
E 3

D 3
  return (negate ? -d : d);
E 3
I 3
	return (neg ? -d : d);
E 3
}
E 1
