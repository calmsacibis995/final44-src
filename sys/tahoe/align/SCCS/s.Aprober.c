h33077
s 00011/00001/00026
d D 7.1 90/12/06 13:37:06 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00026
d D 1.2 90/12/04 22:39:36 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00027/00000/00000
d D 1.1 86/07/20 11:14:31 sam 1 0
c date and time created 86/07/20 11:14:31 by sam
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

#define	PSL_USER	PSL_CURMOD
prober(infop)	process_info *infop;
/*
/*	Probe read accessability.
/*
/*************************************/
{
	register	long	Register_12;	/* Has to be first reg ! */
	register	long	Register_11;
	register	long	Register_10;
	register	long	Register_9;

	Register_9 = operand(infop,0)->data & 1;	/* Required mode */
	if (psl & PSL_USER) Register_9 = 1;		/* user can't probe as
							 *  kernel ! */
	Register_10 = operand(infop,1)->address;	/* Base address */
	Register_11 = operand(infop,2)->data;		/* Length */
	Register_12=psl;
	Set_psl(r12);	/* restore the user psl */
	asm ("	prober	r9,(r10),r11");
	asm ("	movpsl	r12");
	New_cc (Register_12);
}
E 1
