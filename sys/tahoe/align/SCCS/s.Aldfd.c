h11055
s 00011/00001/00018
d D 7.1 90/12/06 13:36:37 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00018
d D 1.2 90/12/04 22:39:09 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00019/00000/00000
d D 1.1 86/07/20 11:14:20 sam 1 0
c date and time created 86/07/20 11:14:20 by sam
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
ldfd(infop)	process_info *infop;
/*
/*	Load into accumulator float operand converted to double.
/*
/***************************************************************/
{
	register struct oprnd *oprnd_pnt;

	oprnd_pnt = operand(infop,0);
	if ( reserved( oprnd_pnt->data ) ) 
		exception(infop, ILL_OPRND);
	acc_high = oprnd_pnt->data ;
	acc_low = 0;
	psl |= PSL_DBL;
	infop->acc_dbl = 1;
}
E 1
