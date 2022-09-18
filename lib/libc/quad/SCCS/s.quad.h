h37367
s 00002/00002/00082
d D 8.1 93/06/04 12:57:12 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00083
d D 5.9 92/07/28 17:40:13 bostic 9 8
c make the GNUC 2 test a little more general for now
e
s 00015/00037/00069
d D 5.8 92/06/25 09:34:29 bostic 8 7
c KNF, integrate with standard include files (quad -> quad_t etc.)
e
s 00012/00000/00094
d D 5.7 92/06/21 10:13:43 bostic 7 6
c GCC2 changed the type of the shift count; make this work since we
c still use both compilers.  This should be ripped out as soon as possible.
c From Chris Torek
e
s 00004/00002/00090
d D 5.6 92/06/02 13:38:28 bostic 6 5
c fix header
e
s 00077/00060/00015
d D 5.5 92/06/02 13:35:27 bostic 5 4
c new version from Chris Torek
e
s 00024/00000/00051
d D 5.4 92/05/12 18:22:04 bostic 4 3
c Prepend the gcc-2.1 release copyright notice to all source code
e
s 00010/00037/00041
d D 5.3 92/05/12 18:15:26 bostic 3 2
c use BSD conventions for determining ENDIAN; clean up longlong union
e
s 00003/00001/00075
d D 5.2 92/05/12 16:44:35 bostic 2 1
c BITS_PER_WORD -> (NBBY * sizeof(long))
e
s 00076/00000/00000
d D 5.1 92/05/12 15:20:02 bostic 1 0
c put on a Berkeley copyright notice -- original didn't have a GNU
c copyright, I'll add one as soon as I find out which one to add
c date and time created 92/05/12 15:20:02 by bostic
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
I 5
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
E 5
 * %sccs.include.redist.c%
I 6
 *
 *	%W% (Berkeley) %G%
E 6
I 5
 */

/*
 * Quad arithmetic.
E 5
 *
D 5
 *	%W% (Berkeley) %G%
E 5
I 5
 * This library makes the following assumptions:
 *
D 8
 *  - The type long long (aka quad) exists.
E 8
I 8
 *  - The type long long (aka quad_t) exists.
E 8
 *
 *  - A quad variable is exactly twice as long as `long'.
 *
 *  - The machine's arithmetic is two's complement.
 *
D 8
 * All other machine parameters are encapsulated here.  This library can
 * provide 128-bit arithmetic on a machine with 128-bit quads and 64-bit
 * longs, for instance, or 96-bit arithmetic on machines with 48-bit longs.
E 8
I 8
 * This library can provide 128-bit arithmetic on a machine with 128-bit
 * quads and 64-bit longs, for instance, or 96-bit arithmetic on machines
 * with 48-bit longs.
E 8
E 5
 */

I 4
D 5
/* Copyright (C) 1989, 1992 Free Software Foundation, Inc.
E 5
I 5
D 8
#ifndef SPARC_XXX
#include <machine/endian.h>		/* see #else case */
#else
/*
 * These are for testing and for illustration: we expect <machine/endian.h>
 * to define these.  Actually, these match most big-endian machines; for
 * most little-endian machines, all you need do is exchange _QUAD_HIGHWORD
 * and _QUAD_LOWWORD.
 */
D 6
#define _QUAD_HIGHWORD 0
#define _QUAD_LOWWORD 1
E 6
I 6
#define _QUAD_HIGHWORD	0
#define _QUAD_LOWWORD	1
E 6
#endif
E 5

D 5
This file is part of GNU CC.
E 5
I 5
typedef long long quad;
typedef unsigned long long u_quad;
typedef unsigned long u_long;
E 5

E 8
I 8
#include <sys/types.h>
E 8
D 5
GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.
E 5
I 5
#include <limits.h>
D 8
/*
 * We expect something like these from <limits.h>, which should be provided on
 * any ANSI C system.
#define	USHRT_MAX	0xffff
#define	CHAR_BIT	8
 */
E 8
E 5

D 5
GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
E 5
I 5
/*
D 8
 * Depending on the desired operation, we view a `long long' (aka quad) in
E 8
I 8
 * Depending on the desired operation, we view a `long long' (aka quad_t) in
E 8
 * one or more of the following formats.
 */
union uu {
D 8
	quad	q;		/* as a (signed) quad */
	quad	uq;		/* as an unsigned quad */
E 8
I 8
	quad_t	q;		/* as a (signed) quad */
	quad_t	uq;		/* as an unsigned quad */
E 8
	long	sl[2];		/* as two signed longs */
	u_long	ul[2];		/* as two unsigned longs */
};
E 5

D 5
You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */
E 5
I 5
/*
 * Define high and low longwords.
 */
#define	H		_QUAD_HIGHWORD
#define	L		_QUAD_LOWWORD
E 5

D 5
/* As a special exception, if you link this library with files
   compiled with GCC to produce an executable, this does not cause
   the resulting executable to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */
E 5
I 5
/*
D 8
 * Total number of bits in a quad and in the pieces that make it up.
E 8
I 8
 * Total number of bits in a quad_t and in the pieces that make it up.
E 8
 * These are used for shifting, and also below for halfword extraction
 * and assembly.
 */
D 8
#define	QUAD_BITS	(sizeof(quad) * CHAR_BIT)
E 8
I 8
#define	QUAD_BITS	(sizeof(quad_t) * CHAR_BIT)
E 8
#define	LONG_BITS	(sizeof(long) * CHAR_BIT)
#define	HALF_BITS	(sizeof(long) * CHAR_BIT / 2)
E 5

E 4
D 5
/* More subroutines needed by GCC output code on some machines.  */
/* Compile this one with gcc.  */
I 2
#include <sys/param.h>
E 5
I 5
/*
 * Extract high and low shortwords from longword, and move low shortword of
 * longword to upper half of long, i.e., produce the upper longword of
D 8
 * ((quad)(x) << (number_of_bits_in_long/2)).  (`x' must actually be u_long.)
E 8
I 8
 * ((quad_t)(x) << (number_of_bits_in_long/2)).  (`x' must actually be u_long.)
E 8
 *
 * These are used in the multiply code, to split a longword into upper
D 8
 * and lower halves, and to reassemble a product as a quad, shifted left
E 8
I 8
 * and lower halves, and to reassemble a product as a quad_t, shifted left
E 8
 * (sizeof(long)*CHAR_BIT/2).
 */
#define	HHALF(x)	((x) >> HALF_BITS)
#define	LHALF(x)	((x) & ((1 << HALF_BITS) - 1))
#define	LHUP(x)		((x) << HALF_BITS)
E 5
E 2

D 2
#include "config.h"
E 2
D 3
#include <stddef.h>
I 2

E 3
D 5
#define	BITS_PER_WORD	(NBBY * sizeof(long))
E 2

D 3
#ifndef SItype
#define SItype long int
#endif

/* long long ints are pairs of long ints in the order determined by
   WORDS_BIG_ENDIAN.  */

#ifdef WORDS_BIG_ENDIAN
  struct longlong {long high, low;};
#else
  struct longlong {long low, high;};
#endif

E 3
/* We need this union to unpack/pack longlongs, since we don't have
   any arithmetic yet.  Incoming long long parameters are stored
   into the `ll' field, and the unpacked result is read from the struct
   longlong.  */

D 3
typedef union
{
  struct longlong s;
  long long ll;
  SItype i[2];
  unsigned SItype ui[2];
E 3
I 3
typedef union {
	long long ll;
	struct { long val[2]; } s;
E 3
} long_long;
I 3
#define high val[_QUAD_HIGHWORD]
#define low val[_QUAD_LOWWORD]
E 3

I 3
#define HIGH _QUAD_HIGHWORD
#define LOW _QUAD_LOWWORD

E 3
/* Internally, long long ints are strings of unsigned shorts in the
D 3
   order determined by BYTES_BIG_ENDIAN.  */
E 3
I 3
   order determined by BYTE_ORDER.  */
E 3

#define B 0x10000
#define low16 (B - 1)

D 3
#ifdef BYTES_BIG_ENDIAN

/* Note that HIGH and LOW do not describe the order
   of words in a long long.  They describe the order of words
   in vectors ordered according to the byte order.  */

#define HIGH 0
#define LOW 1

E 3
I 3
#if BYTE_ORDER == BIG_ENDIAN
E 3
#define big_end(n)	0 
#define little_end(n)	((n) - 1)
#define next_msd(i)	((i) - 1)
#define next_lsd(i)	((i) + 1)
#define is_not_msd(i,n)	((i) >= 0)
#define is_not_lsd(i,n)	((i) < (n))
D 3

E 3
#else
D 3

#define LOW 0
#define HIGH 1

E 3
#define big_end(n)	((n) - 1)
#define little_end(n)	0 
#define next_msd(i)	((i) + 1)
#define next_lsd(i)	((i) - 1)
#define is_not_msd(i,n)	((i) < (n))
#define is_not_lsd(i,n)	((i) >= 0)
D 3

E 3
#endif
E 5
I 5
D 8
extern u_quad __qdivrem(u_quad u, u_quad v, u_quad *rem);
E 8
I 8
extern u_quad_t __qdivrem __P((u_quad_t u, u_quad_t v, u_quad_t *rem));
E 8
I 7

/*
 * XXX
 * Compensate for gcc 1 vs gcc 2.  Gcc 1 defines ?sh?di3's second argument
D 8
 * as u_quad, while gcc 2 correctly uses int.  Unfortunately, we still use
E 8
I 8
 * as u_quad_t, while gcc 2 correctly uses int.  Unfortunately, we still use
E 8
 * both compilers.
 */
D 9
#ifdef sparc
E 9
I 9
#if __GNUC__ >= 2
E 9
typedef unsigned int	qshift_t;
#else
D 8
typedef u_quad		qshift_t;
E 8
I 8
typedef u_quad_t	qshift_t;
E 8
#endif
E 7
E 5
E 1
