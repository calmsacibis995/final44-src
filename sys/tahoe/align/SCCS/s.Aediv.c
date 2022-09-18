h44797
s 00011/00001/00027
d D 7.1 90/12/06 13:36:22 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00027
d D 1.2 90/12/04 22:38:54 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00028/00000/00000
d D 1.1 86/07/20 11:14:13 sam 1 0
c date and time created 86/07/20 11:14:13 by sam
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
int	zzz1,zzz2,zzz3,zzz4,zzz5;
ediv(infop)	process_info *infop;
/*
/*	Extended precision division.
/*
/***************************************/
{
	register long Register_12;	/* Has to be the first reg !! */
	register long Register_11;	/* remainder */
	register long Register_10;	/* quotient */
	register long Register_9;	/* divident least */
	register long Register_8;	/* divident most */
	register long Register_7;	/* divisor */

	Register_7 = operand(infop, 0)->data;
	Register_8 = operand(infop, 1)->data;
	Register_9 = operand(infop, 1)->data2;
	Register_12=psl;
	Set_psl(r12);	/* restore the user psl */
	asm ("	ediv	r7,r8,r10,r11");
	asm ("	movpsl	r12");
	New_cc (Register_12);
	write_back (infop, Register_10, operand(infop, 2));
	write_back (infop, Register_11, operand(infop, 3));
}
E 1
