h17556
s 00011/00001/00218
d D 7.1 90/12/06 13:50:14 bostic 5 4
c add Berkeley specific copyright notice
e
s 00000/00000/00219
d D 1.4 90/12/04 22:51:37 bostic 4 3
c redo include files for kernel reorg
e
s 00001/00001/00218
d D 1.3 86/01/05 18:51:08 sam 3 2
c working (mostly)
e
s 00020/00046/00199
d D 1.2 86/01/03 23:47:11 sam 2 1
c massive cleanups; use SYS.h macros to allow profiling; moved to 
c tahoemath directory; revamp comments for cpp
e
s 00245/00000/00000
d D 1.1 85/08/02 15:42:30 sam 1 0
c date and time created 85/08/02 15:42:30 by sam
e
u
U
t
T
I 1
D 2
	.data
	.align	2
_twoopi:.long	0x4022F983, 0x6E4E4415 # .double .63661977236758134
	.align	2
_p0:.long	0x40C90FDA, 0x90304197 # .double 1.57079631844
	.align	2
_p1:.long	0xC0255DE0, 0xB36CEE75 # .double -.645963710599
	.align	2
_p2:.long	0x3EA33457, 0xA736E807 # .double .079689678945999999
	.align	2
_p3:.long	0xBC992665, 0x5E9A6554 # .double -.0046737666099999999
	.align	2
_p4:.long	0x3A1ED7FA, 0xCC54924E # .double .000151485129
E 2
I 2
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*-
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 5

D 3
#include "SYS.h"
E 3
I 3
#include "../tahoe/SYS.h"
E 3

E 2
	.text
D 2
LL0:	.align	1
	.globl	_Kcosf
	.set	L18,0x0
	.data
	.text
_Kcosf:	.word	L18
E 2
I 2
ENTRY(Kcosf, 0)
E 2
	tstl	4(fp)		# if (arg < 0)
	jgeq	L23
	lnd	4(fp)
	std	4(fp)		# arg = -arg;
L23:	pushl	20(fp)		# 	hfs
	pushl	$1
	pushl	8(fp)
	pushl	4(fp)
	callf	$20,_sinus
	ret			# return(sinus(arg,1));

D 2
	.align	1
	.globl	_Ksinf
	.set	L25,0x0
	.data
	.text
	.data
	.align	2
L36:	.long	0x47FFF800, 0x00000000 # .double 32764
	.text
	.data
	.align	2
L37:	.long	0x3F800000, 0x00000000 # .double .25
	.text
	.data
	.align	2
L38:	.long	0x41800000, 0x00000000 # .double 4
	.text
	.data
	.align	2
L41:	.long	0x40800000, 0x00000000 # .double 1
	.text
	.set	L29,0x0
	.data
	.text
_Ksinf: .word	L25
E 2
I 2
ENTRY(Ksinf, 0)
E 2
	pushl	20(fp)		# hfs
	pushl	$0
	pushl	8(fp)
	pushl	4(fp)
	callf	$20,_sinus
	ret			# return(sinus(arg, 0));

D 2
	.align	1
_sinus: .word	L29
E 2
I 2
ENTRY(sinus, 0)
E 2
	subl3	$112,fp,sp
	movl	8(fp),-80(fp)
	movl	4(fp),-84(fp)	# x = arg;
	jgeq	L34		# if (x < 0) {
	lnd	-84(fp)
	std	-84(fp)		# x = -x;
	addl2	$2,12(fp)	# quad = quad + 2;}
L34:	pushl	16(fp)
	ldd	_twoopi	
	pushd
	ldd	-84(fp)
	pushd	
	callf	$24,_Kmuld
	movl	r1,-88(fp)
	movl	r0,-84(fp)	# std	-84(fp)	 x = x * twoopi;
	cmpd2	-84(fp),L36	# if (x > 32764) {
	jleq	L35
	pushl	16(fp)		# hfs
	subl3	$60,fp,-(sp)	# &e
	pushl	-80(fp)
	pushl	-84(fp)		# x
	callf	$20,_Kmodf
	clrl	-92+4(fp)
	movl	r0,-92(fp)	# y = modf(x, &e);
	pushl	16(fp)		# hfs
	pushl	$0
	pushl	12(fp)		# quad
	pushl	$0
	pushl	$0		# dummy acc
	callf	$24,_Kcvtld
	pushl	16(fp)		# hfs
	pushl	r1
	pushl	r0 		# pushd	 (double)quad
	ldd	-60(fp)
	pushd			# &e
	callf	$24,_Kaddd
	movl	r1,-56(fp)
	movl	r0,-60(fp) 	# std	-60(fp) e = e + quad;
	pushl	16(fp)		# hfs
	subl3	$68,fp,-(sp)	# &f

	pushl	16(fp)		# hfs
	ldd	-60(fp)
	pushd			# &e
	ldd	L37
	pushd			# 0.25
	callf	$24,_Kmuld

	pushl	r1
	pushl	r0		# pushd	 0.25 * e
	callf	$20,_Kmodf	# modf(0.25 * e, &f);
	
	pushl	16(fp)		# hfs
	movl	r1,-64(fp)
	movl	r0,-68(fp)	# ldd	-68(fp)	 &f
	pushl	r1
	pushl	r0		# pushd
	ldd	L38
	pushd
	callf	$24,_Kmuld	# 4*f
				# std	r0
	pushl	16(fp)		# hfs
	pushl	r1
	pushl	r0		# pushd	
	ldd	-60(fp)
	pushd
	callf	$24,_Ksubd	# e - 4 * f
	ldd	r0		# load acc with result of Ksubd
	cvdl	12(fp)		# quad = (e - 4 * f); }
	jbr	L39
L35:	ldd	-84(fp)		# else {
	cvdl	-96(fp)		# k = x;
	pushl	16(fp)		# hfs
	pushl	$0
	pushl	-96(fp)
	pushl	$0
	pushl	$0		# acc
	callf	$24,_Kcvtld
				# std	r0
	pushl	16(fp)		# hfs
	pushl	r1
	pushl	r0		# pushd	 (double)k
	ldd	-84(fp)
	pushd			# x
	callf	$24,_Ksubd
	movl	r1,-88(fp)
	movl	r0,-92(fp)	# std	-92(fp) y = x - k;
	addl3	-96(fp),12(fp),r0
	andl3	$3,r0,12(fp)	# quad = (quad + k) & 03; }
L39:	bitl	$1,12(fp)	# if (quad & 01)
	jeql	L40
	pushl	16(fp)		# hfs
	ldd	-92(fp)
	pushd			# y
	ldd	L41
	pushd			# 1.0
	callf	$24,_Ksubd
	movl	r1,-88(fp)
	movl	r0,-92(fp)	# std	-92(fp) y = 1 - y;
L40:	cmpl	12(fp),$1	# if (quad > 1)
	jleq	L42
	lnd	-92(fp)
	std	-92(fp)		# y = -y;
L42:	pushl	16(fp)		# hfs
	ldd	-92(fp)
	pushd
	pushd
	callf	$24,_Kmuld	# y*y
	movl	r1,-72(fp)
	movl	r0,-76(fp)	# std	-76(fp)	 ysq=y*y;

	pushl	16(fp)		# hfs
	ldd	-76(fp)
	pushd
	ldd	_p4
	pushd
	callf	$24,_Kmuld	# p4*ysq

	pushl	16(fp)		# hfs
	pushl	_p3+4
	pushl	_p3
	pushl	r1
	pushl	r0		# pushd
	callf	$24,_Kaddd	# p4*ysq+p3

	pushl	16(fp)		# hfs
	pushl	-72(fp)
	pushl	-76(fp)
	pushl	r1
	pushl	r0		# pushd
	callf	$24,_Kmuld	# (p4*ysq+p3)*ysq

	pushl	16(fp)		# hfs
	pushl	_p2+4
	pushl	_p2
	pushl	r1
	pushl	r0		# pushd
	callf	$24,_Kaddd	# (p4*ysq+p3)*ysq+p2

	pushl	16(fp)		# hfs
	pushl	-72(fp)
	pushl	-76(fp)
	pushl	r1
	pushl	r0		# pushd
	callf	$24,_Kmuld	# ((p4*ysq+p3)*ysq+p2)*ysq	

	pushl	16(fp)		# hfs
	pushl	_p1+4
	pushl	_p1
	pushl	r1
	pushl	r0		# pushd
	callf	$24,_Kaddd	# ((p4*ysq+p3)*ysq+p2)*ysq+p1

	pushl	16(fp)		# hfs
	pushl	-72(fp)
	pushl	-76(fp)
	pushl	r1
	pushl	r0		# pushd
	callf	$24,_Kmuld	# (((p4*ysq+p3)*ysq+p2)*ysq+p1)*ysq	

	pushl	16(fp)		# hfs
	pushl	_p0+4
	pushl	_p0
	pushl	r1
	pushl	r0		# pushd
	callf	$24,_Kaddd	# (((p4*ysq+p3)*ysq+p2)*ysq+p1)*ysq+p0	

	pushl	16(fp)		# hfs
	pushl	-88(fp)
	pushl	-92(fp)
	pushl	r1
	pushl	r0		# pushd
	callf	$24,_Kmuld	# ((((p4*ysq+p3)*ysq+p2)*ysq+p1)*ysq+p0)*y;	

	movl	r1,-100(fp)
	movl	r0,-104(fp)	# std	-104(fp) temp1
	ldd	r0
	cvdf
	stf	r0
	ret#1
I 2

	.data
	.align	2
_twoopi:.long	0x4022F983, 0x6E4E4415 # .double .63661977236758134
_p0:	.long	0x40C90FDA, 0x90304197 # .double 1.57079631844
_p1:	.long	0xC0255DE0, 0xB36CEE75 # .double -.645963710599
_p2:	.long	0x3EA33457, 0xA736E807 # .double .079689678945999999
_p3:	.long	0xBC992665, 0x5E9A6554 # .double -.0046737666099999999
_p4:	.long	0x3A1ED7FA, 0xCC54924E # .double .000151485129
L36:	.long	0x47FFF800, 0x00000000 # .double 32764
L37:	.long	0x3F800000, 0x00000000 # .double .25
L38:	.long	0x41800000, 0x00000000 # .double 4
L41:	.long	0x40800000, 0x00000000 # .double 1
E 2
E 1
