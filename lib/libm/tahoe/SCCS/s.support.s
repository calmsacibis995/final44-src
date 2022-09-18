h58276
s 00002/00002/00211
d D 8.1 93/06/04 17:08:56 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00005/00214
d D 5.6 90/10/09 18:11:00 bostic 8 7
c new copyright notice
e
s 00001/00011/00217
d D 5.5 90/06/01 15:42:56 bostic 7 6
c new copyright notice
e
s 00010/00005/00218
d D 5.4 88/06/30 17:38:20 bostic 6 5
c install approved copyright notice
e
s 00014/00010/00209
d D 5.3 88/04/29 13:23:27 bostic 5 4
c add Berkeley specific headers
e
s 00000/00000/00219
d D 5.2 87/11/30 18:49:12 bostic 4 3
c tahoe release
e
s 00000/00000/00219
d D 5.1 87/11/30 18:46:18 bostic 3 2
c tahoe release
e
s 00008/00008/00211
d D 1.2 87/07/13 13:06:08 zliu 2 1
c various clean-ups; added Makefile and mcount.sed.
e
s 00219/00000/00000
d D 1.1 87/07/13 12:26:06 zliu 1 0
c date and time created 87/07/13 12:26:06 by zliu
e
u
U
t
T
I 1
D 5
/* 
E 5
I 5
/*
E 5
D 9
 * Copyright (c) 1987 Regents of the University of California.
D 5
 * 
 * Use and reproduction of this software are granted  in  accordance  with
 * the terms and conditions specified in  the  Berkeley  Software  License
 * Agreement (in particular, this entails acknowledgement of the programs'
 * source, and inclusion of this notice) with the additional understanding
 * that  all  recipients  should regard themselves as participants  in  an
 * ongoing  research  project and hence should  feel  obligated  to report
 * their  experiences (good or bad) with these elementary function  codes,
 * using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 5
I 5
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
D 8
 *
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
E 8
E 5
 */
	.data
	.align	2
_sccsid:
	.asciz	"%Z%%M%	%I%	(ucb.elefunt)	%G%"
/*
 * copysign(x,y),
 * logb(x),
 * scalb(x,N),
 * finite(x),
 * drem(x,y),
 * Coded in vax assembly language by K. C. Ng 4/9/85.
 * Re-coded in tahoe assembly language by Z. Alex Liu 7/13/87.
 */
/*
 * double copysign(x,y)
 * double x,y;
 */
	.globl	_copysign
	.text
D 2
	.align	1
E 2
I 2
	.align	2
E 2
_copysign:
	.word	0x0004			# save r2
	movl	8(fp),r1
	movl	4(fp),r0		# r0:r1 = x
	andl3	$0x7f800000,r0,r2	# r2 = biased exponent of x
	beql	1f			# if 0 or reserved op then return x
	andl3	$0x80000000,12(fp),r2	# r2 = sign bit of y at bit-31
	andl2	$0x7fffffff,r0		# replace x by |x|
	orl2	r2,r0			# copy the sign bit of y to x
1:	ret
/*
 * double logb(x)
 * double x;
 */
	.globl	_logb
	.text
D 2
	.align	1
E 2
I 2
	.align	2
E 2
_logb:
D 2
	.word	0x0000
E 2
I 2
	.word	0x0000			# save nothing
E 2
	andl3	$0x7f800000,4(fp),r0	# r0[b23:b30] = biased exponent of x
	beql    1f
	shrl	$23,r0,r0		# r0[b0:b7] = biased exponent of x
	subl2	$129,r0			# r0 = unbiased exponent of x
	cvld	r0			# acc = unbiased exponent of x (double)
	std	r0			# r0 =  unbiased exponent of x (double)
	ret
1:	movl	8(fp),r1		# 8(fp) must be moved first
	movl	4(fp),r0		# r0:r1 = x (zero or reserved op)
	blss	2f			# simply return if reserved op
	movl	$0xfe000000,r1
	movl	$0xcfffffff,r0		# -2147483647.0
2:	ret
/*
 * long finite(x)
 * double x;
 */
	.globl	_finite
	.text
D 2
	.align	1
E 2
I 2
	.align	2
E 2
_finite:
D 2
	.word	0x0000
E 2
I 2
	.word	0x0000			# save nothing
E 2
	andl3	$0xff800000,4(fp),r0	# r0 = sign of x & its biased exponent
	cmpl	r0,$0x80000000		# is x a reserved op?
	beql	1f			# if so, return FALSE (0)
	movl	$1,r0			# else return TRUE (1)
	ret
1:	clrl	r0
	ret
/*
 * double scalb(x,N)
 * double x; int N;
 */
	.globl	_scalb
	.set	ERANGE,34
	.text
D 2
	.align	1
E 2
I 2
	.align	2
E 2
_scalb:
D 2
	.word	0x000c
E 2
I 2
	.word	0x000c			# save r2-r3
E 2
	movl	8(fp),r1
	movl	4(fp),r0		# r0:r1 = x (-128 <= Ex <= 126)
	andl3	$0x7f800000,r0,r3	# r3[b23:b30] = biased exponent of x
	beql	1f			# is x a 0 or a reserved operand?
	movl	12(fp),r2		# r2 = N
	cmpl	r2,$0xff		# if N >= 255
	bgeq	2f			# then the result must overflow
	cmpl	r2,$-0xff		# if N <= -255
	bleq	3f			# then the result must underflow
	shrl	$23,r3,r3		# r3[b0:b7] = biased exponent of x
	addl2	r2,r3			# r3 = biased exponent of the result
	bleq	3f			# if <= 0 then the result underflows
	cmpl	r3,$0x100		# if >= 256 then the result overflows
	bgeq	2f
	shll	$23,r3,r3		# r3[b23:b30] = biased exponent of res.
	andl2	$0x807fffff,r0
	orl2	r3,r0			# r0:r1 = x*2^N
1:	ret
2:	pushl	$ERANGE			# if the result would overflow
	callf	$8,_infnan		# and _infnan returns
	andl3	$0x80000000,4(fp),r2	# get the sign of input arg
	orl2	r2,r0			# re-attach the sign to r0:r1
	ret
3:	clrl	r1			# if the result would underflow
	clrl	r0			# then return 0
	ret
/*
 * double drem(x,y)
 * double x,y;
 * Returns x-n*y where n=[x/y] rounded (to even in the half way case).
 */
	.globl	_drem
	.set	EDOM,33
	.text
D 2
	.align	1
E 2
I 2
	.align	2
E 2
_drem:
	.word	0x1ffc			# save r2-r12
	movl	16(fp),r3
	movl	12(fp),r2		# r2:r3 = y
	movl	8(fp),r1
	movl	4(fp),r0		# r0:r1 = x
	andl3	$0xff800000,r0,r4
	cmpl	r4,$0x80000000		# is x a reserved operand?
	beql	1f			# if yes then propagate x and return
	andl3	$0xff800000,r2,r4
	cmpl	r4,$0x80000000		# is y a reserved operand?
	bneq	2f
	movl	r3,r1
	movl	r2,r0			# if yes then propagate y and return
1:	ret

2:	tstl	r4			# is y a 0?
	bneq	3f
	pushl	$EDOM			# if so then generate reserved op fault
	callf	$8,_infnan
	ret

3:	andl2	$0x7fffffff,r2		# r2:r3 = y <- |y|
	clrl	r12			# r12 = nx := 0
	cmpl	r2,$0x1c800000		# Ey ? 57 
	bgtr	4f			# if Ey > 57 goto 4
	addl2	$0x1c800000,r2		# scale up y by 2**57
	movl	$0x1c800000,r12		# r12[b23:b30] = nx = 57
4:	pushl	r12			# pushed onto stack: nf := nx
	andl3	$0x80000000,r0,-(sp)	# pushed onto stack: sign of x
	andl2	$0x7fffffff,r0		# r0:r1 = x <- |x|
	movl	r3,r11			# r10:r11 = y1 = y w/ last 27 bits 0
	andl3	$0xf8000000,r10,r11	# clear last 27 bits of y1

Loop:	cmpd2	r0,r2			# x ? y
	bleq	6f			# if x <= y goto 6
 /* 					# begin argument reduction */
	movl	r3,r5
	movl	r2,r4			# r4:r5 = t = y
	movl	r11,r7
	movl	r10,r6			# r6:r7 = t1 = y1
	andl3	$0x7f800000,r0,r8	# r8[b23:b30] = Ex:biased exponent of x
	andl3	$0x7f800000,r2,r9	# r9[b23:b30] = Ey:biased exponent of y
	subl2	r9,r8			# r8[b23:b30] = Ex-Ey
	subl2	$0x0c800000,r8		# r8[b23:b30] = k = Ex-Ey-25
	blss	5f			# if k < 0 goto 5
	addl2	r8,r4			# t += k	
	addl2	r8,r6			# t1 += k, scale up t and t1
5:	ldd	r0			# acc = x
	divd	r4			# acc = x/t
	cvdl	r8			# r8 = n = [x/t] truncated
	cvld	r8			# acc = dble(n)
	std	r8			# r8:r9 = dble(n)
	ldd	r4			# acc = t
	subd	r6			# acc = t-t1
	muld	r8			# acc = n*(t-t1)
	std	r4			# r4:r5 = n*(t-t1)
	ldd	r6			# acc = t1
	muld	r8			# acc = n*t1
	subd	r0			# acc = n*t1-x
	negd				# acc = x-n*t1
	subd	r4			# acc = (x-n*t1)-n*(t-t1)
	std	r0			# r0:r1 = (x-n*t1)-n*(t-t1)
	brb	Loop

6:	movl	r12,r6			# r6 = nx
	beql	7f			# if nx == 0 goto 7
	addl2	r6,r0			# x <- x*2**57:scale x up by nx
	clrl	r12			# clear nx
	brb	Loop

7:	movl	r3,r5
	movl	r2,r4			# r4:r5 = y
	subl2	$0x800000,r4		# r4:r5 = y/2
	cmpd2	r0,r4			# x ? y/2
	blss	9f			# if x < y/2 goto 9
	bgtr	8f			# if x > y/2 goto 8
	ldd	r8			# acc = dble(n)
	cvdl	r8			# r8 = ifix(dble(n))
	bbc	$0,r8,9f		# if the last bit is zero, goto 9
8:	ldd	r0			# acc = x
	subd	r2			# acc = x-y
	std	r0			# r0:r1 = x-y
9:	xorl2	(sp)+,r0		# x^sign (exclusive or)
	movl	(sp)+,r6		# r6 = nf
	andl3	$0x7f800000,r0,r8	# r8 = biased exponent of x
	andl2	$0x807fffff,r0		# r0 = x w/ exponent zapped
	subl2	r6,r8			# r8 = Ex-nf
	bgtr	0f			# if Ex-nf > 0 goto 0
	clrl	r8			# clear r8
	clrl	r0
	clrl	r1			# x underflows to zero
0:	orl2	r8,r0			# put r8 into x's exponent field
	ret
E 1
