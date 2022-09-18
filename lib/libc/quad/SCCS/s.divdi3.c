h01542
s 00002/00002/00037
d D 8.1 93/06/04 12:55:38 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00032
d D 5.4 92/06/25 09:34:17 bostic 4 3
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00024/00038/00014
d D 5.3 92/06/02 13:35:06 bostic 3 2
c new version from Chris Torek
e
s 00024/00000/00028
d D 5.2 92/05/12 18:22:00 bostic 2 1
c Prepend the gcc-2.1 release copyright notice to all source code
e
s 00028/00000/00000
d D 5.1 92/05/12 15:19:58 bostic 1 0
c put on a Berkeley copyright notice -- original didn't have a GNU
c copyright, I'll add one as soon as I find out which one to add
c date and time created 92/05/12 15:19:58 by bostic
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

long long
__divdi3 (u, v)
     long long u, v;
E 3
I 3
/*
 * Divide two signed quads.
 * ??? if -1/2 should produce -1 on this machine, this code is wrong
 */
D 4
quad
__divdi3(quad a, quad b)
E 4
I 4
quad_t
__divdi3(a, b)
	quad_t a, b;
E 4
E 3
{
D 3
  if (u < 0)
    if (v < 0)
      return (unsigned long long) -u / (unsigned long long) -v;
    else
      return - ((unsigned long long) -u / (unsigned long long) v);
  else
    if (v < 0)
      return - ((unsigned long long) u / (unsigned long long) -v);
    else
      return (unsigned long long) u / (unsigned long long) v;
E 3
I 3
D 4
	u_quad ua, ub, uq;
E 4
I 4
	u_quad_t ua, ub, uq;
E 4
	int neg;

	if (a < 0)
D 4
		ua = -(u_quad)a, neg = 1;
E 4
I 4
		ua = -(u_quad_t)a, neg = 1;
E 4
	else
		ua = a, neg = 0;
	if (b < 0)
D 4
		ub = -(u_quad)b, neg ^= 1;
E 4
I 4
		ub = -(u_quad_t)b, neg ^= 1;
E 4
	else
		ub = b;
D 4
	uq = __qdivrem(ua, ub, (u_quad *)0);
E 4
I 4
	uq = __qdivrem(ua, ub, (u_quad_t *)0);
E 4
	return (neg ? -uq : uq);
E 3
}
E 1
