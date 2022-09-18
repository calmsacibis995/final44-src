h51689
s 00011/00001/00091
d D 7.1 90/12/06 13:37:54 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00091
d D 1.2 90/12/04 22:40:25 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00092/00000/00000
d D 1.1 86/07/20 11:14:55 sam 1 0
c date and time created 86/07/20 11:14:55 by sam
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
 * Signal an exception. It will be handled by 'locore.s'. Here, I:
 *	1) Put the exception code where it belongs on the stack.
 *	2) Restore pc and sp to show that the current opcode
 *		'was not executed'.
 *	3) Execute one big non-local-goto. In the process we take care
 *		to reset the current HW fp such that 'alignment' will
 *		indeed return to 'locore.s'.
 *		IMPORTANT NOTE : the process I use will NOT restore
 *		all registers (like normal returns) so the call to the
 *		handling routine HAS TO BE the last thing in 'alignment'.
 *		Otherwise, all its own register variables will be a mess !!
 *		I also know that 'alignment' itself WILL restore all
 *		registers for 'locore.s' since its entry mask is all-1.
 */
exception(infop, type, param1, param2)
process_info *infop;
int	type, param1, param2;
{
	register long *my_fp;
	register long *current_fp, *prev_fp;

	my_fp = (long *)&infop-1 ;
	infop->ret_exception = type;
	switch (type) {
	case ARITHMETIC:
		infop->ret_code = param1;
		break;
	case ILL_ACCESS:
		infop->ret_addr = param1;
		infop->ret_code = param2;
		break;
	case ALIGNMENT:
	case ILL_ADDRMOD:
	case ILL_OPRND:
		break;
	default :
		printf ("Bad exception type %d (alignment code)\n", type);
		break;
	}
/*
 * Now the big trick. Look up the stack until the frame of
 * 'alignment' is found. prev_fp will point to it and current_fp
 * will then point to the frame of whoever 'alignment' called.
 * This should better work ...
 */
	prev_fp = my_fp;
	while (prev_fp != &fp) {
		current_fp = prev_fp;
		prev_fp = (long *) *prev_fp;
	}
/*
 * Found it. Now fool the HW into thinking that 'alignment' called
 * us directly here, so this routine's 'return' will go back
 * all the way to 'alignment', stopping any further emulation
 * for the current offending opcode.
 *  "fool the HW..." ha ha, am I realy fooling myself ?
 */
	*my_fp = *current_fp;
	*(my_fp - 2) = *(current_fp -2);	/* Alter program counter */
/*
 * Without further ado, just go back now !!!!
 */
}

not_needed (infop)
process_info *infop;
{
/*
 * Shouldn't ever come to this routine.
 */

	printf ("Opcode 0x%x should not trap to alignment code.",
		opCODE);
	printf (" OS or machine problem!! \n");
}


cannot_do (infop)
process_info *infop;
{
/*
 * Some opcode-caused alignments cannot be emulated. See table.c for
 * specific reasons. Reflect this back to the process as alignment
 * exception.
 */
	exception (infop, ALIGNMENT);
}
E 1
