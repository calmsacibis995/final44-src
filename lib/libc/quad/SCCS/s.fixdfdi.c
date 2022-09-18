h53378
s 00002/00002/00034
d D 8.1 93/06/04 12:56:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00009/00031
d D 5.4 92/06/25 09:34:18 bostic 4 3
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00025/00032/00015
d D 5.3 92/06/02 13:35:08 bostic 3 2
c new version from Chris Torek
e
s 00024/00000/00023
d D 5.2 92/05/12 18:22:01 bostic 2 1
c Prepend the gcc-2.1 release copyright notice to all source code
e
s 00023/00000/00000
d D 5.1 92/05/12 15:19:59 bostic 1 0
c put on a Berkeley copyright notice -- original didn't have a GNU
c copyright, I'll add one as soon as I find out which one to add
c date and time created 92/05/12 15:19:59 by bostic
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
E 3
I 3
D 4
#ifndef QUAD_MAX	/* should be in <limits.h> maybe? */
#define	QUAD_MAX ((quad)(((u_quad)1 << (QUAD_BITS - 1)) - 1))
#define	QUAD_MIN (-QUAD_MAX - 1)
#endif
E 3

E 4
D 3
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
__fixdfdi (a)
     double a;
E 3
I 3
/*
 * Convert double to (signed) quad.
 * We clamp anything that is out of range.
 */
D 4
quad
__fixdfdi(double x)
E 4
I 4
quad_t
__fixdfdi(x)
	double x;
E 4
E 3
{
D 3
  long long __fixunsdfdi (double a);

  if (a < 0)
    return - __fixunsdfdi (-a);
  return __fixunsdfdi (a);
E 3
I 3
	if (x < 0)
		if (x <= QUAD_MIN)
			return (QUAD_MIN);
		else
D 4
			return ((quad)-(u_quad)-x);
E 4
I 4
			return ((quad_t)-(u_quad_t)-x);
E 4
	else
		if (x >= QUAD_MAX)
			return (QUAD_MAX);
		else
D 4
			return ((quad)(u_quad)x);
E 4
I 4
			return ((quad_t)(u_quad_t)x);
E 4
E 3
}
E 1
