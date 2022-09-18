h31402
s 00002/00002/00032
d D 8.1 93/06/04 12:46:40 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00033
d D 5.4 92/07/26 21:36:53 ralph 4 3
c removed DEFS.h
e
s 00010/00022/00024
d D 5.3 92/03/15 19:25:10 ralph 3 2
c make code more like hp300
e
s 00002/00002/00044
d D 5.2 92/02/29 12:58:56 bostic 2 1
c need DEFS.h for ASMSTR macro
e
s 00046/00000/00000
d D 5.1 92/02/29 12:40:59 bostic 1 0
c date and time created 92/02/29 12:40:59 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

I 2
D 4
#include "DEFS.h"
E 4
I 4
#include <machine/machAsmDefs.h>
E 4

E 2
#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */
D 2

#include "DEFS.h"
E 2

/*
 * double modf(val, iptr)
 *	double val, *iptr;
 * returns: xxx and n (in *iptr) where val == n.xxx
 */
LEAF(modf)
D 3
	li.d	$f6, 4503599627370496.0	# check for value out of range (2**52)
	abs.d	$f0, $f12
	c.lt.d	$f0, $f6
	mfc1	t0, $f13		# get the sign & exponent part
	bc1f	3f			# val is not less than maxint
	add.d	$f2, $f0, $f6		# logical shift right
	sub.d	$f2, $f2, $f6		# logical shift left
	c.le.d	$f2, $f0
	bc1t	1f
	li.d	$f6, 1.0		# adjust due to rounding
	sub.d	$f2, $f2, $f6
1:
	bge	t0, zero, 2f		# jump if val >= 0
	neg.d	$f2, $f0		# negate integer part if val < 0
2:
	s.d	$f2, 0(a2)		# save the integer part
	sub.d	$f0, $f12, $f2		# return the fractional part
	j	ra
3:
	mtc1	zero, $f0		# val was too big so
	mtc1	zero, $f1		#   return fraction of zero
	s.d	$f12, 0(a2)		#   and the original number.
E 3
I 3
	cfc1	t0, $31			# get the control register
	cfc1	t0, $31			# get the control register
	or	t1, t0, 0x3		# set rounding mode to round to zero
	xor	t1, t1, 0x2		#  (i.e., 01)
	ctc1	t1, $31
	cvt.w.d	$f0, $f12		# convert val to integer
	cvt.d.w	$f0, $f0		# convert back to double
	ctc1	t0, $31			# restore old rounding mode
	s.d	$f0, 0(a2)		# save the integer part
	sub.d	$f0, $f12, $f0		# subtract val - integer part
E 3
	j	ra
END(modf)
E 1
