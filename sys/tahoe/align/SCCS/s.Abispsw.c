h60002
s 00011/00001/00013
d D 7.1 90/12/06 13:35:54 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00013
d D 1.2 90/12/04 22:38:22 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00014/00000/00000
d D 1.1 86/07/20 11:13:58 sam 1 0
c date and time created 86/07/20 11:13:58 by sam
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
bispsw(infop)	process_info *infop;
/*
/*	Bits set in PSW.
/*
/*************************************/
{
	register int mask;

	mask = operand(infop,0)->data;
	psl |= mask & 0x7f;
}
E 1
