h10515
s 00002/00002/00111
d D 8.1 93/06/04 17:08:46 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00005/00113
d D 5.6 90/10/09 18:10:58 bostic 9 8
c new copyright notice
e
s 00001/00011/00117
d D 5.5 90/06/01 15:42:52 bostic 8 7
c new copyright notice
e
s 00010/00005/00118
d D 5.4 88/06/30 17:38:19 bostic 7 6
c install approved copyright notice
e
s 00014/00010/00109
d D 5.3 88/04/29 13:23:26 bostic 6 5
c add Berkeley specific headers
e
s 00000/00000/00119
d D 5.2 87/11/30 18:49:11 bostic 5 4
c tahoe release
e
s 00000/00000/00119
d D 5.1 87/11/30 18:46:17 bostic 4 3
c tahoe release
e
s 00006/00006/00113
d D 1.3 87/07/13 13:06:07 zliu 3 2
c various clean-ups; added Makefile and mcount.sed.
e
s 00001/00001/00118
d D 1.2 87/07/12 12:03:09 zliu 2 1
c lib$dsqrt_r5 should have its .word off (i.e. 0x0).
e
s 00119/00000/00000
d D 1.1 87/07/11 23:36:21 zliu 1 0
c date and time created 87/07/11 23:36:21 by zliu
e
u
U
t
T
I 1
D 6
/* 
E 6
I 6
/*
E 6
D 10
 * Copyright (c) 1987 Regents of the University of California.
D 6
 * 
 * Use and reproduction of this software are granted  in  accordance  with
 * the terms and conditions specified in  the  Berkeley  Software  License
 * Agreement (in particular, this entails acknowledgement of the programs'
 * source, and inclusion of this notice) with the additional understanding
 * that  all  recipients  should regard themselves as participants  in  an
 * ongoing  research  project and hence should  feel  obligated  to report
 * their  experiences (good or bad) with these elementary function  codes,
 * using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 6
I 6
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
D 9
 *
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
E 9
E 6
 */
	.data
	.align	2
_sccsid:
.asciz	"%Z%%M%	%I%	(ucb.elefunt)	%G%"

/*
 * double sqrt(arg)   revised August 15,1982
 * double arg;
 * if(arg<0.0) { _errno = EDOM; return(<a reserved operand>); }
 * if arg is a reserved operand it is returned as it is
 * W. Kahan's magic square root
D 3
 * coded by Heidi Stettner and revised by Emile LeBlanc 8/18/82
 * adapted to run on the CCI 6/32 by Z. Alex Liu 7/11/87
E 3
I 3
 * Coded by Heidi Stettner and revised by Emile LeBlanc 8/18/82.
 * Re-coded in tahoe assembly language by Z. Alex Liu 7/13/87.
E 3
 *
 * entry points:_d_sqrt		address of double arg is on the stack
 *		_sqrt		double arg is on the stack
 */
	.text
D 3
	.align	1
E 3
I 3
	.align	2
E 3
	.globl	_sqrt
	.globl	_d_sqrt
	.globl	libm$dsqrt_r5
	.set	EDOM,33

_d_sqrt:
	.word	0x003c          # save r2-r5
	movl	4(fp),r2
	movl	(r2),r0
	movl	4(r2),r1	# r0:r1 = x
	brb  	1f
_sqrt:
	.word	0x003c          # save r2-r5
	movl    4(fp),r0
	movl	8(fp),r1	# r0:r1 = x
1:	andl3	$0x7f800000,r0,r2	# r2 = biased exponent
	bneq	2f
	ret			# biased exponent is zero -> 0 or reserved op.
/*
 *				# internal procedure
I 3
 *				# ENTRY POINT FOR cdabs and cdsqrt
E 3
 */
D 3
libm$dsqrt_r5:			# ENTRY POINT FOR cdabs and cdsqrt
D 2
	.word	0x003c		# returns double square root scaled by
E 2
I 2
	.word	0x0000		# returns double square root scaled by
E 2
				# 2^r6
E 3
I 3
libm$dsqrt_r5:			# returns double square root scaled by 2^r6
	.word	0x0000		# save nothing
E 3
2:	ldd	r0
	std	r4
	bleq	nonpos		# argument is not positive
	andl3	$0xfffe0000,r4,r2
	shar	$1,r2,r0
	addl2	$0x203c0000,r0	# r0 has magic initial approximation
/*
 *				# Do two steps of Heron's rule
 *				# ((arg/guess)+guess)/2 = better guess
 */
	ldf	r4
	divf	r0
	addf	r0
	stf	r0
	subl2	$0x800000,r0	# divide by two
	ldf	r4
	divf	r0
	addf	r0
	stf	r0
	subl2	$0x800000,r0	# divide by two
/*
 *				# Scale argument and approximation
 *				# to prevent over/underflow
 */
	andl3	$0x7f800000,r4,r1
	subl2	$0x40800000,r1	# r1 contains scaling factor
	subl2	r1,r4		# r4:r5 = n/s
	movl	r0,r2
	subl2	r1,r2		# r2 = a/s
/*
 *				# Cubic step
 *				# b = a+2*a*(n-a*a)/(n+3*a*a) where
 *				# b is better approximation, a is approximation
 *				# and n is the original argument.
 *				# s := scale factor.
 */
	clrl	r1		# r0:r1 = a
	clrl	r3		# r2:r3 = a/s
	ldd	r0		# acc = a
	muld	r2		# acc = a*a/s
	std	r2		# r2:r3 = a*a/s
	negd			# acc = -a*a/s
	addd	r4		# acc = n/s-a*a/s
	std	r4		# r4:r5 = n/s-a*a/s
	addl2	$0x1000000,r2	# r2:r3 = 4*a*a/s
	ldd	r2		# acc = 4*a*a/s
	addd	r4		# acc = n/s+3*a*a/s
	std	r2		# r2:r3 = n/s+3*a*a/s
	ldd	r0		# acc = a
	muld	r4		# acc = a*n/s-a*a*a/s
	divd	r2		# acc = a*(n-a*a)/(n+3*a*a)
	std	r4		# r4:r5 = a*(n-a*a)/(n+3*a*a)
	addl2	$0x800000,r4	# r4:r5 = 2*a*(n-a*a)/(n+3*a*a)
	ldd	r4		# acc = 2*a*(n-a*a)/(n+3*a*a)
	addd	r0		# acc = a+2*a*(n-a*a)/(n+3*a*a)
	std	r0		# r0:r1 = a+2*a*(n-a*a)/(n+3*a*a)
	ret			# rsb
nonpos:
	bneq	negarg
	ret			# argument and root are zero
negarg:
	pushl	$EDOM
	callf	$8,_infnan	# generate the reserved op fault
	ret
E 1
