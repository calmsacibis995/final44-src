h06557
s 00011/00001/00016
d D 7.1 90/12/06 13:37:11 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00016
d D 1.2 90/12/04 22:39:41 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00017/00000/00000
d D 1.1 86/07/20 11:14:35 sam 1 0
c date and time created 86/07/20 11:14:35 by sam
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
pushx(infop)	process_info *infop;
/*
/*	Push operand on the stack.
/*
/******************************************/
{
	register long quantity;

	quantity = operand(infop,0)->data ;
	if (quantity < 0) negative_1; else negative_0;
	if (quantity == 0) zero_1; else zero_0;
	overflow_0; carry_1;
	push (infop, quantity);
}
E 1
