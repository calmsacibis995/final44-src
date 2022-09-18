h33003
s 00011/00001/00096
d D 1.6 91/05/08 14:26:52 bostic 6 5
c new copyright; att/bsd/shared
e
s 00003/00003/00094
d D 1.5 90/12/16 16:44:58 bostic 5 4
c kernel reorg
e
s 00003/00003/00094
d D 1.4 90/06/22 18:48:23 root 4 3
c "root" has had these files checked out forever; seem to all be include
c file changes. -- TK
e
s 00025/00000/00072
d D 1.3 87/10/27 18:47:51 bostic 3 2
c add wbadaddr routine for Harris write-only memory
e
s 00002/00002/00070
d D 1.2 86/12/18 23:52:45 karels 2 1
c fix movob
e
s 00072/00000/00000
d D 1.1 86/01/12 18:05:00 sam 1 0
c date and time created 86/01/12 18:05:00 by sam
e
u
U
t
T
I 1
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 6

D 4
#include "../tahoe/mem.h"
#include "../tahoe/mtpr.h"
#include "../tahoe/SYS.h"
E 4
I 4
D 5
#include "tahoe/mem.h"
#include "tahoe/mtpr.h"
#include "tahoe/SYS.h"
E 5
I 5
#include "../tahoe/mem.h"
#include "../include/mtpr.h"
#include "../tahoe/SYS.h"
E 5
E 4

D 2
	.set	_scb, 0x0	# mask for total disable
E 2
I 2
	.set	_scb, 0x0
E 2
	.set	HIGH, 0x1f	# mask for total disable
	.set	BERVEC, 0x80	# offset into scb of the bus error vector 
	.set	RESTVEC, 0x8	# offset into scb of the restart vector 

ENTRY(mtpr, 0)
	mtpr	8(fp),4(fp)
	ret

ENTRY(mfpr, 0)
	mfpr	4(fp),r0
	ret

ENTRY(bcopy, R2|R1|R0)
	movl	4(fp),r0
	movl	8(fp),r1
	movl	12(fp),r2
	movblk
	ret

/*
 * badaddr(addr, len)
 *	see if access addr with a len type instruction causes a machine check
 *	len is length of access (1=byte, 2=short, 4=long)
 *	r0 = 0 means good(exists); r0 =1 means does not exist.
 */
ENTRY(badaddr, R5|R4|R3|R2|R1)
	mfpr	$IPL,r1
	mtpr	$HIGH,$IPL
	mfpr	$SCBB,r5
	mtpr	$0,$SCBB
	movl	*$BERVEC,r2
	movl	4(fp),r3
	movl	8(fp),r4
	movab	9f,*$BERVEC
	bbc	$0,r4,1f; tstb	(r3)
1:	bbc	$1,r4,1f; tstw	(r3)
1:	bbc	$2,r4,1f; tstl	(r3)
1:	clrl	r0			# made it w/o machine checks
2:	movl	r2,*$BERVEC
	mtpr	r1,$IPL
	mtpr	r5,$SCBB
	ret

I 3
/*
 * wbadaddr(addr, len, value)
 *	see if write of value to addr with a len type instruction causes
 *	a machine check
 *	len is length of access (1=byte, 2=short, 4=long)
 *	r0 = 0 means good(exists); r0 =1 means does not exist.
 */
ENTRY(wbadaddr, R5|R4|R3|R2|R1)
	mfpr	$IPL,r1
	mtpr	$HIGH,$IPL
	mfpr	$SCBB,r5
	mtpr	$0,$SCBB
	movl	*$BERVEC,r2
	movl	4(fp),r3
	movl	8(fp),r4
	movab	9f,*$BERVEC
	bbc	$0,r4,1f; movb	15(fp), (r3)
1:	bbc	$1,r4,1f; movw	14(fp), (r3)
1:	bbc	$2,r4,1f; movl	12(fp), (r3)
1:	clrl	r0			# made it w/o machine checks
2:	movl	r2,*$BERVEC
	mtpr	r1,$IPL
	mtpr	r5,$SCBB
	ret

E 3
	.align	2
9:			# Here we catch buss error (if it comes)
	andl3	4(sp),$ERRCD,r0
	cmpl	r0,$APE
	jneq	1f
	halt			# Address parity error !!!
1:	cmpl	r0,$VBE
	jneq	1f
	halt			# Versabus error
1:
	movl	$1,r0		# Anything else = bad address
	movab	8(sp),sp	# discard buss error trash
	movab	2b,(sp)		# new program counter on stack.
	rei

ENTRY(movow, 0)
	movow	10(fp),*4(fp)
	ret

ENTRY(movob, 0)
D 2
	movob	9(fp),*4(fp)
E 2
I 2
	movob	11(fp),*4(fp)
E 2
	ret
E 1
