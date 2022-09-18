h45238
s 00011/00001/00034
d D 7.1 90/12/06 13:50:19 bostic 5 4
c add Berkeley specific copyright notice
e
s 00000/00000/00035
d D 1.4 90/12/04 22:51:40 bostic 4 3
c redo include files for kernel reorg
e
s 00001/00001/00034
d D 1.3 86/01/05 18:51:13 sam 3 2
c working (mostly)
e
s 00013/00015/00022
d D 1.2 86/01/03 23:47:16 sam 2 1
c massive cleanups; use SYS.h macros to allow profiling; moved to 
c tahoemath directory; revamp comments for cpp
e
s 00037/00000/00000
d D 1.1 85/08/02 15:42:32 sam 1 0
c date and time created 85/08/02 15:42:32 by sam
e
u
U
t
T
I 1
D 2
	.data
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

/*
 * _Ksubf(acc_most,acc_least,op_most,op_least,hfs)
 *
 * subf(d1,d2)
 * {
 * 	return(d1+(-d2));
 * }
 */
E 2
	.text
D 2
LL0:	.align	1
	.globl	_Ksubf
	.set	L12,0xffc
	.data
	.text
_Ksubf:	.word	L12	# _Ksubf(acc_most,acc_least,op_most,op_least,hfs)
E 2
I 2
ENTRY(Ksubf, 0)
E 2
	tstl	4(fp)	# handle (a-b) where a and/or b = 0.0
	jneq	next
	movl	$0,r1
	movl	12(fp),r0
	lnd	r0
	std	r0
	ret
next:
	tstl	12(fp)
	jneq	doit
	movl	$0,r1
	movl	4(fp),r0
	ret
doit:
	lnd	12(fp)	# note: -(0) = 0 by definition!
	pushl	20(fp)	# hfs
	pushd	
	pushl	8(fp)
	pushl	4(fp)	# acc
	callf	$24,_Kaddf
	ret
D 2


/*
 * subf(d1,d2)
 * {
 * 	return(d1+(-d2));
 * }
*/
E 2
E 1
