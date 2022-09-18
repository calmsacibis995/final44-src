h20497
s 00011/00001/00021
d D 7.1 90/12/06 13:36:10 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00021
d D 1.2 90/12/04 22:38:41 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00022/00000/00000
d D 1.1 86/07/20 11:14:07 sam 1 0
c date and time created 86/07/20 11:14:07 by sam
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
cvld(infop)	process_info *infop;
/*
/*	Convert integer to double (into accumulator).
/*
/******************************************************/
{
	register	long	Register_12;	/* Has to be first reg ! */
	register	double	*Register_11;
	register	long	Register_10;

	Register_11 = (double *) &acc_high;
	Register_10 = operand(infop,0)->data;
	Register_12=psl;
	Set_psl(r12);	/* restore the user psl */
	asm ("	cvld	r10");		/* Don't change the order !! */
	asm ("	movpsl	r12");
	asm ("	std	(r11)");
	New_cc (Register_12);
}
E 1
