h12315
s 00011/00001/00040
d D 7.1 90/12/06 13:37:50 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00040
d D 1.2 90/12/04 22:40:20 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00041/00000/00000
d D 1.1 86/07/20 11:14:54 sam 1 0
c date and time created 86/07/20 11:14:54 by sam
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

/*
 * Part of the parameter list is set up by locore.s.
 * First 2 dummy variables MUST BE the first local
 * variables; leaving place for registers 0 and 1
 * which are not preserved by the current C compiler.
 * Then, the array of structures and the last_operand
 * HAVE to be in the given order, to correspond to the
 * description of process_info in 'alignment.h'. 
 */
alignment()
{
	long	space_4_Register_1;	/* register 1 */
	long	space_4_Register_0;	/* register 0 */
	struct	oprnd	space_4_decoded[4];
	long	space_4_opcode;
	long	space_4_last_operand;	/* Last operand # processed */
	long	space_4_saved_pc;
	long	space_4_saved_sp;

	register process_info *infop;

	infop = (process_info *)&space_4_saved_sp;
	saved_pc = pc;
	saved_sp = sp;	     			/* For possible exceptions */

	last_operand = -1;   /* To get the operand routine going correctly */

	opCODE = 0xff & *(char *)pc;
	pc++;
	(*Table[opCODE].routine) (infop);	/* Call relevant handler */
	/*
	 * NOTE: nothing should follow, except the return.
	 * The register variables cannot be trusted anymore,
	 * if an exception is signalled.  See 'exception.c'
	 * to understand why.
	 */
}
E 1
