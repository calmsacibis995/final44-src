h61528
s 00002/00002/00072
d D 8.1 93/06/04 17:12:17 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00016/00073
d D 5.4 90/10/09 18:16:11 bostic 8 7
c new copyright notice
e
s 00010/00005/00079
d D 5.3 88/06/30 17:32:18 bostic 7 6
c install approved copyright notice
e
s 00015/00010/00069
d D 5.2 88/04/29 12:36:17 bostic 6 5
c added Berkeley specific header
e
s 00000/00000/00079
d D 5.1 87/11/30 18:49:56 bostic 5 4
c tahoe release
e
s 00004/00002/00075
d D 1.3 85/09/12 22:20:12 elefunt 4 2
c adding sccsid asciz string to each source file.
e
s 00003/00002/00075
d R 1.3 85/09/12 22:15:46 elefunt 3 2
c adding sccsid asciz string to each source file.
e
s 00001/00001/00076
d D 1.2 85/09/12 20:17:02 elefunt 2 1
c 4.3BSD version dated 09/12/85.
e
s 00077/00000/00000
d D 1.1 85/09/06 17:50:17 zliu 1 0
c date and time created 85/09/06 17:50:17 by zliu
e
u
U
t
T
I 1
D 6
# 
E 6
D 9
# Copyright (c) 1985 Regents of the University of California.
D 6
# 
# Use and reproduction of this software are granted  in  accordance  with
# the terms and conditions specified in  the  Berkeley  Software  License
# Agreement (in particular, this entails acknowledgement of the programs'
# source, and inclusion of this notice) with the additional understanding
# that  all  recipients  should regard themselves as participants  in  an
# ongoing  research  project and hence should  feel  obligated  to report
# their  experiences (good or bad) with these elementary function  codes,
# using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 6
I 6
# All rights reserved.
E 9
I 9
# Copyright (c) 1985, 1993
#	The Regents of the University of California.  All rights reserved.
E 9
#
D 8
# Redistribution and use in source and binary forms are permitted
D 7
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 7
#
# All recipients should regard themselves as participants in an ongoing
# research project and hence should feel obligated to report their
# experiences (good or bad) with these elementary function codes, using
# the sendbug(8) program, to the authors.
E 8
I 8
# %sccs.include.redist.sh%
E 8
#
#	%W% (Berkeley) %G%
E 6
#
D 4

D 2
# %W% (ELEFUNT) %G%
E 2
I 2
# %Z%%M%	1.1 (Berkeley) 5/23/85; %I% (ucb.elefunt) %G%
E 4
I 4
	.data
	.align	2
_sccsid:
.asciz	"%Z%%M%	1.1 (Berkeley) 5/23/85; %I% (ucb.elefunt) %G%"
E 4
E 2

# double cbrt(double arg)
# W. Kahan, 10/13/80. revised 1/13/84 for keeping sign symmetry
# error check by E LeBlanc, 8/18/82
# Revised and tested by K.C. Ng, 5/2/85  
# Max error less than 0.667 ulps (unit in the last places)
	.globl	_cbrt
	.globl	_d_cbrt
	.globl  _dcbrt_
	.text
	.align	1

_cbrt:
_d_cbrt:
	.word	0x00fc		# save r2 to r7
	movq	4(ap),r0	# r0 = argument x
	jmp 	dcbrt2
_dcbrt_:
	.word	0x00fc		# save r2 to r7
	movq	*4(ap),r0	# r0 = argument x

dcbrt2:	bicw3	$0x807f,r0,r2	# biased exponent of x
	jeql	return		# dcbrt(0)=0  dcbrt(res)=res. operand
	bicw3	$0x7fff,r0,ap	# ap has sign(x)
	xorw2	ap,r0		# r0 is abs(x)
	movl	r0,r2		# r2 has abs(x)
	rotl	$16,r2,r2	# r2 = |x| with bits unscrambled
	divl2	$3,r2		# rough dcbrt with bias/3
	addl2	B,r2		# restore bias, diminish fraction
	rotl	$16,r2,r2	# r2=|q|=|dcbrt| to 5 bits
	mulf3	r2,r2,r3	# r3 =qq
	divf2	r0,r3		# r3 = qq/x
	mulf2	r2,r3
	addf2	C,r3		# r3 = s = C + qqq/x
	divf3	r3,D,r4		# r4 = D/s
	addf2	E,r4
	addf2	r4,r3		# r3 = s + E + D/s
	divf3	r3,F,r3		# r3 = F / (s + E + D/s)
	addf2	G,r3		# r3 = G + F / (s + E + D/s)
	mulf2	r3,r2		# r2 = qr3 = new q to 23 bits
	clrl	r3		# r2:r3 = q as double float
	muld3	r2,r2,r4	# r4:r5 = qq exactly
	divd2	r4,r0		# r0:r1 = x/(q*q) rounded
	subd3	r2,r0,r6	# r6:r7 = x/(q*q) - q exactly
	movq    r2,r4		# r4:r5 = q
	addw2	$0x80,r4	# r4:r5 = 2 * q
	addd2	r0,r4		# r4:r5 = 2*q + x/(q*q)
	divd2	r4,r6		# r6:r7 = (x/(q*q)-q)/(2*q+x/(q*q))
	muld2	r2,r6		# r6:r7 = q*(x/(q*q)-q)/(2*q+x/(q*q))
	addd3	r6,r2,r0	# r0:r1 = q + r6:r7
	bisw2	ap,r0		# restore the sign bit
return:
	ret			# error less than 0.667 ulps

.data
.align	2
B :	.long		 721142941		# (86-0.03306235651)*(2^23)
C :	.float		0f0.5428571429		# 19/35
D :	.float		0f-0.7053061224		# -864/1225
E :	.float		0f1.414285714		# 99/70
F :	.float		0f1.607142857		# 45/28
G :	.float		0f0.3571428571		# 5/14

E 1
