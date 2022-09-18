h24744
s 00002/00002/00031
d D 8.1 93/06/04 12:57:15 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00030
d D 5.5 92/06/25 09:34:30 bostic 5 4
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00017/00067/00015
d D 5.4 92/06/02 13:35:29 bostic 4 3
c new version from Chris Torek
e
s 00024/00000/00058
d D 5.3 92/05/12 18:22:10 bostic 3 2
c Prepend the gcc-2.1 release copyright notice to all source code
e
s 00001/00001/00057
d D 5.2 92/05/12 18:17:01 bostic 2 1
c size_t is unsigned long for these routines
e
s 00058/00000/00000
d D 5.1 92/05/12 15:20:08 bostic 1 0
c put on a Berkeley copyright notice -- original didn't have a GNU
c copyright, I'll add one as soon as I find out which one to add
c date and time created 92/05/12 15:20:08 by bostic
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
I 4
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
E 4
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 3
D 4
/* Copyright (C) 1989, 1992 Free Software Foundation, Inc.
E 4
I 4
#include "quad.h"
E 4

D 4
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

E 3
#include "longlong.h"

static int bsub ();

long long 
__subdi3 (u, v)
     long long u, v;
E 4
I 4
/*
 * Subtract two quad values.  This is trivial since a one-bit carry
 * from a single u_long difference x-y occurs if and only if (x-y) > x.
 */
D 5
quad
__subdi3(quad a, quad b)
E 5
I 5
quad_t
__subdi3(a, b)
	quad_t a, b;
E 5
E 4
{
D 4
  long a[2], b[2], c[2];
  long_long w;
  long_long uu, vv;
E 4
I 4
	union uu aa, bb, diff;
E 4

D 4
  uu.ll = u;
  vv.ll = v;

  a[HIGH] = uu.s.high;
  a[LOW] = uu.s.low;
  b[HIGH] = vv.s.high;
  b[LOW] = vv.s.low;

  bsub (a, b, c, sizeof c);

  w.s.high = c[HIGH];
  w.s.low = c[LOW];
  return w.ll;
}

static int 
bsub (a, b, c, n)
     unsigned short *a, *b, *c;
D 2
     size_t n;
E 2
I 2
     unsigned long n;
E 2
{
  signed long acc;
  int i;

  n /= sizeof *c;

  acc = 0;
  for (i = little_end (n); is_not_msd (i, n); i = next_msd (i))
    {
      /* Widen before subtracting to avoid loss of high bits.  */
      acc += (long) a[i] - b[i];
      c[i] = acc & low16;
      acc = acc >> 16;
    }
  return acc;
E 4
I 4
	aa.q = a;
	bb.q = b;
	diff.ul[L] = aa.ul[L] - bb.ul[L];
	diff.ul[H] = aa.ul[H] - bb.ul[H] - (diff.ul[L] > aa.ul[L]);
	return (diff.q);
E 4
}
E 1
