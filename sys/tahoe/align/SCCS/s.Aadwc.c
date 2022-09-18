h48329
s 00011/00001/00032
d D 7.1 90/12/06 13:35:44 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00032
d D 1.2 90/12/04 22:38:11 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00033/00000/00000
d D 1.1 86/07/20 11:13:52 sam 1 0
c date and time created 86/07/20 11:13:52 by sam
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
adwc(infop)	process_info *infop;
/*
/*	Add with carry.
/*	Note : the play with 'tmp' just before the 'asm' line makes
/*		sure that when the adwc opcode is executed, the current
/*		carry in psl is the same as the 'offending' process'.
/*		Don't change unless you know exactly what you're doing.
/*
/*****************************/
{
	register	long	Register_12;	/* Has to be first reg ! */
	register	long	Register_11;
	register	long	Register_10;
	register 	long	tmp;

	Register_12 = operand(infop,0)->data;
	Register_11 = operand(infop,1)->data;
	if (carry)	/* If process' carry set */
		tmp = -1;
	else tmp = 0;
	tmp++;		/* 0 => carry set.  1 => carry clear */

	Register_10=psl;
	Set_psl(r10);	/* restore the user psl */
	asm("	adwc	r11,r12");
	asm("	movpsl	r11");
	New_cc (Register_11);

	write_back(infop, Register_12, operand(infop,1) );
}
E 1
