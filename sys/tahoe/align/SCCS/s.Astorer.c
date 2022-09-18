h20679
s 00011/00001/00024
d D 7.1 90/12/06 13:37:32 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00024
d D 1.2 90/12/04 22:40:00 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00025/00000/00000
d D 1.1 86/07/20 11:14:44 sam 1 0
c date and time created 86/07/20 11:14:44 by sam
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
storer(infop)	process_info *infop;
/*
/*	Store multiple registers.
/*
/***************************************/
{
	register int mask, next_register, new_address;

	mask = operand(infop,0)->data & 0x3fff;	/* Bits 0 to 13 only */
	new_address = operand(infop,1)->address;
	next_register = 0;				/* Register # */
	while (next_register <= 13)
	{ 
		if (mask & 1 << next_register) 
		{
			put_longword (infop, Register (infop, next_register),
				new_address);
			new_address += 4; 
		}
		next_register++;
	}
}
E 1
