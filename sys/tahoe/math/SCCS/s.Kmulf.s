h40423
s 00011/00001/00092
d D 7.1 90/12/06 13:50:07 bostic 5 4
c add Berkeley specific copyright notice
e
s 00002/00002/00091
d D 1.4 90/12/04 22:51:31 bostic 4 3
c redo include files for kernel reorg
e
s 00003/00003/00090
d D 1.3 86/01/05 18:51:02 sam 3 2
c working (mostly)
e
s 00009/00007/00084
d D 1.2 86/01/03 23:47:05 sam 2 1
c massive cleanups; use SYS.h macros to allow profiling; moved to 
c tahoemath directory; revamp comments for cpp
e
s 00091/00000/00000
d D 1.1 85/07/31 21:33:43 sam 1 0
c date and time created 85/07/31 21:33:43 by sam
e
u
U
t
T
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
E 2
I 1

D 2
#include 	"fp.h"
#include 	"fp_in_krnl.h"
E 2
I 2
D 3
#include "fp.h"
#include "Kfp.h"
#include "SYS.h"
E 3
I 3
D 4
#include "../tahoemath/fp.h"
#include "../tahoemath/Kfp.h"
E 4
I 4
#include "../math/fp.h"
#include "../math/Kfp.h"
E 4
#include "../tahoe/SYS.h"
E 3
E 2

I 2
#define	HIDDEN	23	/* here we count from 0 not from 1 as in fp.h */
E 2

D 2
 			/* here we count from 0 not from 1 as in fp.h */
#define	HIDDEN	23	

E 2
I 2
/* 
 * _Kmulf(acc_most,acc_least,op_most,op_least,hfs)
 */
E 2
	.text
D 2
	.globl	_Kmulf	# _Kmulf(acc_most,acc_least,op_most,op_least,hfs)
_Kmulf:	.word	0xffc
E 2
I 2
ENTRY(Kmulf, R5|R4|R3|R2)
E 2
	clrl	r3		/* r3 - sign: 0 for positive,1 for negative. */
	movl	4(fp),r0
	jgeq	1f
	movl	$1,r3
1:	movl	12(fp),r2
	jgeq	2f
	bbc	$0,r3,1f	/* seconed operand is negative. */
	clrl	r3		/* if first was negative, make result positive. */
	jmp	2f
1:	movl	$1,r3		/* if first was positive, make result negative. */
2:	andl2	$EXPMASK,r0	/* compute first 'pure'exponent. */
	jeql	retzero
	shrl	$EXPSHIFT,r0,r0
	subl2	$BIASP1,r0	
	andl2	$EXPMASK,r2	/* compute seconed 'pure'exponent. */
	jeql	retzero
	shrl	$EXPSHIFT,r2,r2
	subl2	$BIASP1,r2
	addl2	r0,r2		/* add the exponents. */
	addl2	$(BIASP1+2),r2
	jleq	underflow
	cmpl	r2,$258		/* normalization can make the exp. smaller. */
	jgeq	overflow
 /*
 *	We have the sign in r3,the exponent in r2,now is the time to
 * 	perform the multiplication...
 */
	/* fetch first fraction: (r0) */
	andl3	$(0!(EXPMASK | SIGNBIT)),4(fp),r0
	orl2	$(0!CLEARHID),r0
	shll	$7,r0,r0	/* leave the sign bit cleared. */
 
	/* fetch seconed fraction: (r4) */
	andl3	$(0!(EXPMASK | SIGNBIT)),12(fp),r4
	orl2	$(0!CLEARHID),r4
	shll	$7,r4,r4	/* leave the sign bit cleared. */

 
	emul	r4,r0,$0,r0
	movl	r0,r4		/* to see how much we realy need to shift. */
	movl	$6,r5		/* r5 - shift counter. */
	shrl	$7,r4,r4	/* dummy shift. */
1:	bbs	$HIDDEN,r4,realshift
	shll	$1,r4,r4
	decl	r2		/* update exponent. */
	jeql	underflow
	decl	r5		/* update shift counter. */
	jmp	1b
realshift:
	shrl	r5,r0,r0
	bbc	$0,r1,shiftmore
	incl	r1		/* rounding. */
shiftmore:
	shrl	$1,r0,r0
comb:
	andl2	$CLEARHID,r0
	shll	$EXPSHIFT,r2,r4
	orl2	r4,r0
	cmpl	r2,$256
	jlss	1f
	orl2	$HFS_OVF,*20(fp)	
sign:
1:	bbc	$0,r3,done
	orl2	$SIGNBIT,r0
done:	ret



  retzero:
	  clrl	r0
	  ret
  overflow:
	orl2	$HFS_OVF,*20(fp)	
	jmp	sign
  underflow:
	orl2	$HFS_UNDF,*20(fp)	
	ret


	
E 1
