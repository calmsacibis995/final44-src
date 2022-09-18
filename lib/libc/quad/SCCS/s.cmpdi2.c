h58749
s 00002/00002/00031
d D 8.1 93/06/04 12:55:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00031
d D 5.5 92/06/25 09:34:16 bostic 5 4
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00017/00040/00015
d D 5.4 92/06/02 13:35:05 bostic 4 3
c new version from Chris Torek
e
s 00024/00000/00031
d D 5.3 92/05/12 18:22:00 bostic 3 2
c Prepend the gcc-2.1 release copyright notice to all source code
e
s 00001/00001/00030
d D 5.2 92/05/12 18:16:25 bostic 2 1
c SItype becomes explicit `long int'
e
s 00031/00000/00000
d D 5.1 92/05/12 15:19:57 bostic 1 0
c put on a Berkeley copyright notice -- original didn't have a GNU
c copyright, I'll add one as soon as I find out which one to add
c date and time created 92/05/12 15:19:57 by bostic
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

D 2
SItype
E 2
I 2
long int
E 2
__cmpdi2 (a, b)
     long long a, b;
E 4
I 4
/*
 * Return 0, 1, or 2 as a <, =, > b respectively.
 * Both a and b are considered signed---which means only the high word is
 * signed.
 */
int
D 5
__cmpdi2(quad a, quad b)
E 5
I 5
__cmpdi2(a, b)
	quad_t a, b;
E 5
E 4
{
D 4
  long_long au, bu;
E 4
I 4
	union uu aa, bb;
E 4

D 4
  au.ll = a, bu.ll = b;

  if (au.s.high < bu.s.high)
    return 0;
  else if (au.s.high > bu.s.high)
    return 2;
  if ((unsigned) au.s.low < (unsigned) bu.s.low)
    return 0;
  else if ((unsigned) au.s.low > (unsigned) bu.s.low)
    return 2;
  return 1;
E 4
I 4
	aa.q = a;
	bb.q = b;
	return (aa.sl[H] < bb.sl[H] ? 0 : aa.sl[H] > bb.sl[H] ? 2 :
	    aa.ul[L] < bb.ul[L] ? 0 : aa.ul[L] > bb.ul[L] ? 2 : 1);
E 4
}
E 1
