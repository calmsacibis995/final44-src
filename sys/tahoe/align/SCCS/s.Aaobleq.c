h31144
s 00011/00001/00021
d D 7.1 90/12/06 13:35:48 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00021
d D 1.2 90/12/04 22:38:15 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00022/00000/00000
d D 1.1 86/07/20 11:13:54 sam 1 0
c date and time created 86/07/20 11:13:54 by sam
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
aobleq(infop)	process_info *infop;
/*
/*	Add one, branch if less or equal.
/*	Can't use real HW opcodes since we don't want to branch here.
/*
/*******************************************/
{
	register long limit, index, new_address, complement;

	limit = operand(infop,0)->data;
	index = operand(infop,1)->data;
	complement =  limit + ~index;
	if ( complement < 0){ carry_0; negative_1;} else{negative_0; carry_1;}
	if ( complement == 0) zero_1; else zero_0;
	overflow_0;  
	write_back (infop, index+1, operand(infop,1));
	new_address = operand(infop,2)->address;
	if (!negative || zero) pc = new_address;
}
E 1
