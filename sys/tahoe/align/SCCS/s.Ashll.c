h22432
s 00011/00002/00023
d D 7.1 90/12/06 13:37:23 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00024
d D 1.2 90/12/04 22:39:53 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00025/00000/00000
d D 1.1 86/07/20 11:14:41 sam 1 0
c date and time created 86/07/20 11:14:41 by sam
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

shll(infop)	process_info *infop;
/*
/*	Shift logical left (longword).
/*	Checks for overflow.
/*
/*******************************/
{
	register	long	Register_12;	/* Has to be first reg ! */
	register	long	Register_11;
	register	long	Register_10;
	
	Register_12 = operand(infop,0)->data;
	Register_11 = operand(infop,1)->data;
	Register_10 = psl;
	Set_psl(r10);	/*save the orig CC bits of the psl */
	asm("	shll	r12,r11,r10");
	asm("	movpsl	r12");
	New_cc (Register_12);
	write_back (infop, Register_10, operand(infop,2));
}
E 1
