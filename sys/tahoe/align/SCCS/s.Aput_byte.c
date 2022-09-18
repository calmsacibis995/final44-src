h18147
s 00011/00001/00022
d D 7.1 90/12/06 13:37:12 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00022
d D 1.2 90/12/04 22:39:42 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00023/00000/00000
d D 1.1 86/07/20 11:14:36 sam 1 0
c date and time created 86/07/20 11:14:36 by sam
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
#include	"../tahoealign/align.h"
E 2
I 2
#include	"align.h"
E 2

put_byte (infop, byte, where)
process_info	*infop;
char		*where;
long		byte;
/*
/*	Put the byte at the given address in memory.
/*	Caveat: It's quite difficult to find a pte reference
/*		fault.  So I took the easy way out and just signal
/*		an illegal access.
/*	
/**************************************************/
{
	register long code;

	code = writeable(infop, where, 1);
	if ( code == TRUE ) {
		*where = byte;
	} else exception (infop, ILL_ACCESS, where, code);
}
E 1
