h09305
s 00011/00001/00016
d D 7.1 90/12/06 13:35:52 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00016
d D 1.2 90/12/04 22:38:19 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00017/00000/00000
d D 1.1 86/07/20 11:13:56 sam 1 0
c date and time created 86/07/20 11:13:56 by sam
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
bbs(infop)	process_info *infop;
/*
/*	Branch on bit set.
/*
/********************************/
{
	register int position,base, new_address;

	position = operand(infop,0)-> data & 0x1f;
	base = operand(infop,1)->data;
	new_address = operand(infop,2) -> address;
	negative_0; zero_1; overflow_0; carry_1;
	if  (base & 1 << position) pc = new_address;
}
E 1
