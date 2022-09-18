/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vx_exception.c,v $
 * Revision 1.3  89/02/26  12:35:25  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 *  2-Nov-87  David Golub (dbg) at Carnegie-Mellon University
 *	Created (from mmax file).
 *
 */

#include <mach/boolean.h>
#include <mach/exception.h>
#include <mach/kern_return.h>
#include <sys/signal.h>

/*
 *	machine_exception translates a mach exception to a unix exception
 *	and code.  This handles all the hardware-specific exceptions for
 *	the vax.  unix_exception() handles the machine-independent ones.
 */

boolean_t machine_exception(exception, code, subcode, unix_signal, unix_code)
int	exception, code, subcode;
int	*unix_signal, *unix_code;
{
	switch(exception) {

	    case EXC_BAD_INSTRUCTION:
	        *unix_signal = SIGILL;
		switch (code) {
		    case EXC_I386_INVOP:
			*unix_code = ILL_RESOP_FAULT;
			break;
		    default:
			return(FALSE);
		}
		break;

	    case EXC_ARITHMETIC:
	        *unix_signal = SIGFPE;
		switch (code) {
		    case EXC_I386_INTO:
			*unix_code = FPE_INTOVF_TRAP;
			break;
		    case EXC_I386_DIV:
			*unix_code = FPE_INTDIV_TRAP;
			break;
		    case EXC_I386_BOUND:
			*unix_code = FPE_SUBRNG_TRAP;
			break;
		    case EXC_I386_NOEXT:
		    case EXC_I386_EXTOVR:
		    case EXC_I386_EXTERR:
		    case EXC_I386_EMERR:
			*unix_code = 0;
			break;
		    default:
			return(FALSE);
		}
		break;

	    case EXC_BREAKPOINT:
		*unix_signal = SIGTRAP;
		break;

	    default:
		return(FALSE);
	}
	return(TRUE);
}
