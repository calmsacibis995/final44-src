h64653
s 00002/00002/00016
d D 8.1 93/06/10 21:45:15 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00000/00000
d D 7.1 92/03/18 16:33:37 bostic 1 0
c date and time created 92/03/18 16:33:37 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* Relocation format. */
struct relocation_info {
	int r_address;			/* offset in text or data segment */
	unsigned int r_symbolnum : 24,	/* ordinal number of add symbol */
			 r_pcrel :  1,	/* 1 if value should be pc-relative */
			r_length :  2,	/* log base 2 of value's width */
			r_extern :  1,	/* 1 if need to add symbol to value */
				 :  4;	/* reserved */
};
E 1
