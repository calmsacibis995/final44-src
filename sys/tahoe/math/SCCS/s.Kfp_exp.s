h40747
s 00011/00001/00018
d D 7.1 90/12/06 13:49:55 bostic 5 4
c add Berkeley specific copyright notice
e
s 00002/00002/00017
d D 1.4 90/12/04 22:51:21 bostic 4 3
c redo include files for kernel reorg
e
s 00003/00003/00016
d D 1.3 86/01/05 18:50:52 sam 3 2
c working (mostly)
e
s 00009/00012/00010
d D 1.2 86/01/03 23:46:53 sam 2 1
c massive cleanups; use SYS.h macros to allow profiling; moved to 
c tahoemath directory; revamp comments for cpp
e
s 00022/00000/00000
d D 1.1 85/08/02 15:31:19 sam 1 0
c date and time created 85/08/02 15:31:19 by sam
e
u
U
t
T
I 1
D 2
#include	"fp.h"
#include	"fp_in_krnl.h"
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
E 2

D 2
	.globl	Kfpover
Kfpover:
	.word	0x0000
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

ENTRY(Kfpover, 0)
E 2
	movl	$HUGE0,r0
	movl	$HUGE1,r1
	ret

D 2
	.globl	Kfpunder
Kfpunder:
	.word	0x0000
E 2
I 2
ENTRY(Kfpunder, 0)
E 2
	clrl	r0
	clrl	r1
	ret

D 2
	.globl	Kfpzdiv
Kfpzdiv:
	.word	0x0000
	divl2	$0,r1		# force divission by zero.
E 2
I 2
ENTRY(Kfpzdiv, 0)
	divl2	$0,r1		# force division by zero.
E 2
	ret
E 1
