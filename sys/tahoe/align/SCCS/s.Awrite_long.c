h26991
s 00011/00001/00027
d D 7.1 90/12/06 13:37:42 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00027
d D 1.2 90/12/04 22:40:12 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00028/00000/00000
d D 1.1 86/07/20 11:14:50 sam 1 0
c date and time created 86/07/20 11:14:50 by sam
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

write_longword (infop, longword, where)
process_info	*infop;
long		longword;
struct oprnd 	*where;
/*
/*	Put the longword at the given address in
/*	tahoe's memory.
/*
/**************************************************/
{
	if (! (where->mode & W)) exception(infop, ILL_ADDRMOD);
	switch (where->mode & ADDFIELD)	/* Mask out R/W bits */
	{
	case Add:
	case SPmode:
		put_longword (infop, longword, where->address);
		break;
	case Dir:
		Replace (infop, where->reg_number, longword);
		break;
	default:
		printf("Unknown destination in write_long (alignment code)\n");
	};
}	
E 1
