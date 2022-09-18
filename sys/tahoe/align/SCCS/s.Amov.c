h12438
s 00011/00001/00019
d D 7.1 90/12/06 13:36:45 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00019
d D 1.2 90/12/04 22:39:17 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00020/00000/00000
d D 1.1 86/07/20 11:14:23 sam 1 0
c date and time created 86/07/20 11:14:23 by sam
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
mov(infop) 	process_info *infop;
/*
/*	Move operand
/*
/****************************************/
{
	register	long	Register_12;	/* Has to be first reg ! */
	register	long	Register_11;

	Register_12 = operand(infop, 0)->data;
	Register_11=psl;
	Set_psl(r11);	/* restore the user psl */
	asm ("	movl	r12,r11");
	asm ("	movpsl	r12");
	New_cc (Register_12);
	write_back (infop, Register_11, operand(infop,1));
}	
E 1
