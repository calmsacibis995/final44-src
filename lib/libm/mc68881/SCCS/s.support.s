h04490
s 00002/00002/00127
d D 8.1 93/06/04 17:01:47 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00126
d D 5.3 93/05/02 20:28:04 hibler 3 2
c pow_p -> pow_P (though not used anyway)
e
s 00001/00003/00126
d D 5.2 90/05/17 19:04:52 bostic 2 1
c Mike Hibler: compute scalb() using fscale instead of ftwotox/fmul
c as suggested by Tim Moore
e
s 00129/00000/00000
d D 5.1 90/05/17 19:03:53 bostic 1 0
c date and time created 90/05/17 19:03:53 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

	.text
D 3
	.globl	_copysign, _finite, _scalb, _logb, _drem, _pow_p, _atan2__A
E 3
I 3
	.globl	_copysign, _finite, _scalb, _logb, _drem, _pow_P, _atan2__A
E 3

| copysign(x,y) 
| returns x with the sign of y. 
_copysign:
	movl	sp@(4),d0
	movl	sp@(8),d1
	tstw	sp@(12)
	jmi	Lneg
	bclr	#31,d0
	rts
Lneg:
	bset	#31,d0
	rts

| finite(x)
| returns the value TRUE if -INF < x < +INF and returns FALSE otherwise.
_finite:
	movw	#0x7FF0,d0
	movw	sp@(4),d1
	andw	d0,d1
	cmpw	d0,d1
	beq	Lnotfin
	moveq	#1,d0
	rts
Lnotfin:
	clrl	d0
	rts

| scalb(x, N)
| returns  x * (2**N), for integer values N.
_scalb:
	fmoved	sp@(4),fp0
	fbeq	Ldone
D 2
	ftwotoxl	sp@(12),fp1
	fmoved	fp1,sp@-
	fmuld	sp@+,fp0
E 2
I 2
	fscalel	sp@(12),fp0
E 2
Ldone:
	fmoved	fp0,sp@-
	movel	sp@+,d0
	movel	sp@+,d1
	rts

| logb(x)
| returns the unbiased exponent of x, a signed integer in double precision,
| except that logb(0) is -INF, logb(INF) is +INF, and logb(NAN) is that NAN.
_logb:
	movw	sp@(4),d0
	movw	#0x7FF0,d1	| exponent bits
	andw	d1,d0		| mask off all else
	cmpw	d1,d0		| max exponent?
	bne	Lfinite		| no, is finite
	fmoved	sp@(4),fp0	| yes, infinite or NaN
	fbun	Ldone		| NaN returns NaN
	fabsx	fp0		| +-inf returns inf
	jra	Ldone
Lfinite:
	fmoved	sp@(4),fp0	| get entire number
	fbne	Lnonz		| zero?
	flog2x	fp0		| yes, log(0) a convenient source of -inf
	jra	Ldone
Lnonz:
	fgetexpx	fp0	| get exponent
	jra	Ldone

| drem(x,y)
| returns  x REM y  =  x - [x/y]*y , where [x/y] is the integer nearest x/y;
| in half way case, choose the even one.
_drem:
	fmoved	sp@(4),fp0
	fremd	sp@(12),fp0
	fmoved	fp0,sp@-
	movel	sp@+,d0
	movel	sp@+,d1
	rts

D 3
| pow_p(x,y)
E 3
I 3
| pow_P(x,y)
E 3
| return x**y for x with sign=1 and finite y
D 3
_pow_p:
E 3
I 3
_pow_P:
E 3
	flognd	sp@(4),fp0
	fmuld	sp@(12),fp0
	fetoxx	fp0
	fmoved	fp0,sp@-
	movel	sp@+,d0
	movel	sp@+,d1
	rts

| atan2__A(y,x)
| compute atan2(y,x) where x,y are finite and non-zero
| called by atan2() after weeding out all the special cases
_atan2__A:
	moveq	#0,d0		| sign of result
	fmoved	sp@(4),fp0	| get y
	fboge	Lypos		| <0?
	moveq	#1,d0		| yes, result is neg
	fnegx	fp0		| make y pos
Lypos:
	fmoved	sp@(12),fp1	| get x
	fboge	Lxpos		| <0?
	fnegx	fp1		| yes, make x pos
	fdivx	fp1,fp0		| y/x
	fatanx	fp0,fp1		| atan(y/x)
	fmovecr	#0,fp0		| get pi
	fsubx	fp1,fp0		| pi - atan(y/x)
	jra	Lsetsign
Lxpos:
	fdivx	fp1,fp0		| y/x
	fatanx	fp0		| atan(y/x)
Lsetsign:
	tstl	d0		| should be neg?
	jeq	Lrpos		| no, all done
	fnegx	fp0		| yes, negate
Lrpos:
	fmoved	fp0,sp@-
	movel	sp@+,d0
	movel	sp@+,d1
	rts
E 1
