h40085
s 00011/00002/00027
d D 7.1 90/12/06 13:36:23 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00028
d D 1.2 90/12/04 22:38:55 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00029/00000/00000
d D 1.1 86/07/20 11:14:14 sam 1 0
c date and time created 86/07/20 11:14:14 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/

E 3
I 3
/*-
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

D 2
#include "../tahoealign/align.h"
E 2
I 2
#include "align.h"
E 2
emul(infop)	process_info *infop;
/*
/*	Extended precision multiplication.
/*
/***************************************/
{
	register long Register_12;	/* multiplicand */
	register long Register_11;	/* product least */
	register long Register_10;	/* product most */
	register long Register_9;	/* addend */
	register long Register_8;	/* multiplier */
	quadword result;

	Register_8 = operand(infop, 0)->data;
	Register_12 = operand(infop, 1)->data;
	Register_9 = operand(infop, 2)->data;
	Register_10=psl;
	Set_psl(r10);	/* restore the user psl */
	asm ("	emul	r8,r12,r9,r10");
	asm ("	movpsl	r8");
	New_cc (Register_8);
	result.high = Register_10;
	result.low  = Register_11;
	write_quadword (infop, result, operand(infop, 3));
}
E 1
