h11901
s 00011/00001/00062
d D 7.1 90/12/06 13:37:18 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00062
d D 1.2 90/12/04 22:39:48 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00063/00000/00000
d D 1.1 86/07/20 11:14:38 sam 1 0
c date and time created 86/07/20 11:14:38 by sam
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

/*
 * Return the specified register from the big structure.
 */

long
Register (infop, number)
process_info	*infop;
long		number;
{

	switch (number) {
		case 0:	return (r0);
		case 1:	return (r1);
		case 2:	return (r2);
		case 3:	return (r3);
		case 4:	return (r4);
		case 5:	return (r5);
		case 6:	return (r6);
		case 7:	return (r7);
		case 8:	return (r8);
		case 9:	return (r9);
		case 10:	return (r10);
		case 11:	return (r11);
		case 12:	return (r12);
		case 13:	return (fp);
		case 14:	return (sp);
		case 15:	return (pc);
	}
}


/*
 * Replace a given register with the given value.
 */
Replace (infop,number, newvalue)
process_info	*infop;
long		number;
long		newvalue;
{

	switch (number) {
		case 0:	r0 = newvalue; return;
		case 1:	r1 = newvalue; return;
		case 2:	r2 = newvalue; return;
		case 3:	r3 = newvalue; return;
		case 4:	r4 = newvalue; return;
		case 5:	r5 = newvalue; return;
		case 6:	r6 = newvalue; return;
		case 7:	r7 = newvalue; return;
		case 8:	r8 = newvalue; return;
		case 9:	r9 = newvalue; return;
		case 10:	r10 = newvalue; return;
		case 11:	r11 = newvalue; return;
		case 12:	r12 = newvalue; return;
		case 13:	fp = newvalue; return;
		case 14:	sp = newvalue & ~3; return;
		case 15:	pc = newvalue; return;
	}
}
E 1
