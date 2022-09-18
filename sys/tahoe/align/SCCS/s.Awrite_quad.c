h48118
s 00011/00001/00034
d D 7.1 90/12/06 13:37:43 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00034
d D 1.2 90/12/04 22:40:14 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00035/00000/00000
d D 1.1 86/07/20 11:14:51 sam 1 0
c date and time created 86/07/20 11:14:51 by sam
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

write_quadword (infop, qword, where)
process_info	*infop;
quadword 	qword;
struct oprnd 	*where;
/*
/*	Put the quadword at the given address in memory.
/*	
/*
/**************************************************/
{
	if (! (where->mode & W)) exception(infop, ILL_ADDRMOD);
	switch (where->mode & ADDFIELD)	/* Mask out R/W bits */
	{
	case Add:
		put_longword (infop, qword.high, where->address);
		where->address += 4;
		put_longword (infop, qword.low, where->address);
		break;
	case Dir:
		if ( where->reg_number >= SPOINTER || (where->reg_number & 1) == 1 )
			exception (infop, ILL_OPRND); 
		Replace (infop, where->reg_number, qword.high);
		Replace (infop, where->reg_number+1, qword.low);
		break;
	case SPmode:
		exception(infop, ILL_ADDRMOD);
		break;
	default:
		printf("Unknown destination in write_quad (alignment code)\n");
	};
}	
E 1
