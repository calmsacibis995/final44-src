h22662
s 00011/00001/00021
d D 7.1 90/12/06 13:35:58 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00021
d D 1.2 90/12/04 22:38:26 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00022/00000/00000
d D 1.1 86/07/20 11:14:00 sam 1 0
c date and time created 86/07/20 11:14:00 by sam
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
casel(infop)	process_info *infop;
/*
/*	Case (longword).
/*	Can't use real HW opcode, don't want to branch out !
/*
/***********************************/
{
	register long selector, base;
	register unsigned temporary, limit;

	selector = operand(infop,0)->data;
	base = operand(infop,1)->data;
	limit = operand(infop,2)->data;
	if (pc & 1) pc += 1;	/* Displacements are aligned ! */
	temporary = selector - base;
	if (temporary <= limit)
		pc = pc + get_word (infop, (char *)(pc + 2*temporary) );
	else pc = pc + limit*2 + 2;
}
E 1
