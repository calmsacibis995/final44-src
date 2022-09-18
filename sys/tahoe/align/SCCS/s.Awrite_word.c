h50325
s 00011/00001/00037
d D 7.1 90/12/06 13:37:45 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00037
d D 1.2 90/12/04 22:40:15 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00038/00000/00000
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

write_word (infop, word, where)
process_info	*infop;
long 		word;
struct oprnd 	*where;
/*
/*	Put the word at the given address in
/*	tahoe's memory.
/*	
/*	1. The least significant word is written.
/*
/**************************************************/
{
	register struct operand_des *look_at;

	look_at = &Table[opCODE].operand[last_operand];
	if (! (look_at->add_modes & NOVF))
		if (word > 0x7fff || word < -0x8000) overflow_1;	
	if (! (where->mode & W)) exception(infop, ILL_ADDRMOD);
	switch (where->mode & ADDFIELD)	/* Mask out R/W bits */
	{
	case Add:
		put_word (infop, word, where->address);
		break;
	case Dir:
		Replace (infop, where->reg_number, word);
		break;
	case SPmode: 
		where->mode = where->mode & ~SPmode | Add; 
		write_longword (infop, word, where);
		break;
	default:
		printf("Unknown destination in write_word (alignment code)\n");
	};
}	
E 1
