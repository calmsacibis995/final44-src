h09439
s 00011/00001/00018
d D 7.1 90/12/06 13:37:28 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00018
d D 1.2 90/12/04 22:39:58 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00019/00000/00000
d D 1.1 86/07/20 11:14:43 sam 1 0
c date and time created 86/07/20 11:14:43 by sam
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
std(infop)	process_info *infop;
/*
/*	Store accumulator (double) in destination.
/*
/*************************************************/
{
	quadword ac;

	ac.high = acc_high;
	ac.low = acc_low;
	write_quadword (infop, ac, operand(infop,0) );
	if (ac.high < 0) negative_1; else negative_0;
	if ( (ac.high & 0xff800000) == 0 ) zero_1; else zero_0;
	carry_1;
	overflow_0;
}
E 1
