h27812
s 00011/00001/00023
d D 7.1 90/12/06 13:36:03 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00023
d D 1.2 90/12/04 22:38:34 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00024/00000/00000
d D 1.1 86/07/20 11:14:04 sam 1 0
c date and time created 86/07/20 11:14:04 by sam
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
cmpd2(infop)	process_info *infop;
/*
/*	Compare operand 1 with operand 2 (double). 
/*
/****************************************************/
{
	register double	*Register_12;	/* Has to be first reg ! */
	register double	*Register_11;
	register long	Register_10;

	Register_12 = (double *) &operand(infop,0)->data;
	Register_11 = (double *) &operand(infop,1)->data;
	if ( reserved( *(long *)Register_12 ) ||
	     reserved( *(long *)Register_11 ) )
			exception(infop, ILL_OPRND);
	Register_10=psl;
	Set_psl(r10);	/* restore the user psl */
	asm ("	cmpd2	(r12),(r11)");
	asm ("	movpsl	r10");
	New_cc (Register_10);
}
E 1
