h62383
s 00002/00002/00090
d D 8.1 93/06/04 17:08:18 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00016/00091
d D 5.5 90/10/09 18:10:52 bostic 6 5
c new copyright notice
e
s 00010/00006/00097
d D 5.4 88/06/30 17:38:15 bostic 5 4
c install approved copyright notice
e
s 00016/00010/00087
d D 5.3 88/04/29 13:23:21 bostic 4 3
c add Berkeley specific headers
e
s 00000/00000/00097
d D 5.2 87/11/30 18:49:07 bostic 3 2
c tahoe release
e
s 00000/00000/00097
d D 5.1 87/11/30 18:46:15 bostic 2 1
c tahoe release
e
s 00097/00000/00000
d D 1.1 87/08/04 14:13:53 zliu 1 0
c date and time created 87/08/04 14:13:53 by zliu
e
u
U
t
T
I 1
D 4
# 
E 4
I 4
D 5
#
E 5
E 4
D 7
# Copyright (c) 1987 Regents of the University of California.
D 4
# 
# Use and reproduction of this software are granted  in  accordance  with
# the terms and conditions specified in  the  Berkeley  Software  License
# Agreement (in particular, this entails acknowledgement of the programs'
# source, and inclusion of this notice) with the additional understanding
# that  all  recipients  should regard themselves as participants  in  an
# ongoing  research  project and hence should  feel  obligated  to report
# their  experiences (good or bad) with these elementary function  codes,
# using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 4
I 4
# All rights reserved.
E 7
I 7
# Copyright (c) 1987, 1993
#	The Regents of the University of California.  All rights reserved.
E 7
#
D 6
# Redistribution and use in source and binary forms are permitted
D 5
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 5
I 5
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
#
# All recipients should regard themselves as participants in an ongoing
# research project and hence should feel obligated to report their
# experiences (good or bad) with these elementary function codes, using
# the sendbug(8) program, to the authors.
E 6
I 6
# %sccs.include.redist.sh%
E 6
#
#	%W% (Berkeley) %G%
E 4
#
	.data
	.align	2
_sccsid:
.asciz	"%W%	%I%	(ucb.elefunt)	%G%"

# double precision complex absolute value
# CABS by W. Kahan, 9/7/80.
# Revised for reserved operands by E. LeBlanc, 8/18/82
# argument for complex absolute value by reference, *4(fp)
# argument for cabs and hypot (C fcns) by value, 4(fp)
# output is in r0:r1

	.text
	.align	2
	.globl  _cabs
	.globl  _hypot
	.globl	_z_abs

#	entry for c functions cabs and hypot
_cabs:
_hypot:
	.word	0x807c		# save r2-r6, enable floating overflow
	movl	16(fp),r3
	movl	12(fp),r2	# r2:3 = y
	movl	8(fp),r1
	movl	4(fp),r0	# r0:1 = x
	brb	1f
#	entry for Fortran use, call by:   d = abs(z)
_z_abs:
	.word	0x807c		# save r2-r6, enable floating overflow
	movl	4(fp),r4	# indirect addressing is necessary here
	movl	12(r4),r3	#
	movl	8(r4),r2	# r2:3 = y
	movl	4(r4),r1	#
	movl	(r4),r0		# r0:1 = x
1:	andl3	$0xff800000,r0,r4	# r4 has signed biased exp of x
	cmpl	$0x80000000,r4
	beql	2f		# x is a reserved operand, so return it
	andl3	$0xff800000,r2,r5	# r5 has signed biased exp of y
	cmpl	$0x80000000,r5
	bneq	3f		# y isn't a reserved operand
	movl	r3,r1
	movl	r2,r0		# return y if it's reserved
2:	ret

3:	callf	$4,regs_set	# r0:1 = dsqrt(x^2+y^2)/2^r6
	addl2	r6,r0		# unscaled cdabs in r0:1
	jvc	2b		# unless it overflows
	subl2	$0x800000,r0	# halve r0 to get meaningful overflow
	ldd	r0
	addd	r0		# overflow; r0 is half of true abs value
	ret

regs_set:
	.word	0x0000
	andl2	$0x7fffffff,r0	# r0:r1 = dabs(x)
	andl2	$0x7fffffff,r2	# r2:r3 = dabs(y)
	cmpl	r0,r2
	bgeq	4f
	movl	r1,r5
	movl	r0,r4
	movl	r3,r1
	movl	r2,r0
	movl	r5,r3
	movl	r4,r2		# force y's exp <= x's exp
4:	andl3	$0xff800000,r0,r6	# r6 = exponent(x) + bias(129)
	beql	5f		# if x = y = 0 then cdabs(x,y) = 0
	subl2	$0x47800000,r6	# r6 = exponent(x) - 14
	subl2	r6,r0		# 2^14 <= scaled x < 2^15
	bitl	$0xff800000,r2
	beql	5f		# if y = 0 return dabs(x)
	subl2	r6,r2
	cmpl	$0x37800000,r2	# if scaled y < 2^-18
	bgtr	5f		#   return dabs(x)
	ldd	r0
	muld	r0
	std	r0		# r0:1 = scaled x^2
	ldd	r2
	muld	r2		# acc = scaled y^2
	addd	r0
	std	r0
	pushl	r1
	pushl	r0
	callf	$12,_sqrt	# r0:1 = dsqrt(x^2+y^2)/2^r6
5:	ret
E 1
