h10960
s 00011/00001/00017
d D 7.1 90/12/06 13:36:12 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00017
d D 1.2 90/12/04 22:38:44 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00018/00000/00000
d D 1.1 86/07/20 11:14:08 sam 1 0
c date and time created 86/07/20 11:14:08 by sam
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
cvt(infop) 	process_info *infop;
/*
/*	Convert , checks overflow
/*
/****************************************/
{
	register long result;

	result = operand(infop,0)->data;
	if (result < 0 )  negative_1 ; else negative_0;
	if (result == 0 )  zero_1 ; else zero_0;
	carry_1; overflow_0;
		/* Overflow may be set by writing back */
	write_back (infop, result, operand(infop,1) );
}
E 1
