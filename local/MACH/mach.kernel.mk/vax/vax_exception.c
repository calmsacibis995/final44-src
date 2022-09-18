/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vax_exception.c,v $
 * Revision 2.2  89/02/26  10:49:41  gm0w
 * 	Changes for cleanup.
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
		    case EXC_VAX_PRIVINST:
			*unix_code = ILL_PRIVIN_FAULT;
			break;
		    case EXC_VAX_RESOPND:
			*unix_code = ILL_RESOP_FAULT;
			break;
		    case EXC_VAX_RESADDR:
			*unix_code = ILL_RESAD_FAULT;
			break;
		    case EXC_VAX_COMPAT:
			*unix_code = subcode;
			break;
		    default:
			return(FALSE);
		}
		break;

	    case EXC_ARITHMETIC:
	        *unix_signal = SIGFPE;
		switch (code) {
		    case EXC_VAX_INT_OVF:
			*unix_code = FPE_INTOVF_TRAP;
			break;
		    case EXC_VAX_INT_DIV:
			*unix_code = FPE_INTDIV_TRAP;
			break;
		    case EXC_VAX_FLT_OVF_T:
			*unix_code = FPE_FLTOVF_TRAP;
			break;
		    case EXC_VAX_FLT_DIV_T:
			*unix_code = FPE_FLTDIV_TRAP;
			break;
		    case EXC_VAX_FLT_UND_T:
			*unix_code = FPE_FLTUND_TRAP;
			break;
		    case EXC_VAX_DEC_OVF:
			*unix_code = FPE_DECOVF_TRAP;
			break;
		    case EXC_VAX_FLT_OVF_F:
			*unix_code = FPE_FLTOVF_FAULT;
			break;
		    case EXC_VAX_FLT_DIV_F:
			*unix_code = FPE_FLTDIV_FAULT;
			break;
		    case EXC_VAX_FLT_UND_F:
			*unix_code = FPE_FLTUND_FAULT;
			break;
		    default:
			return(FALSE);
		}
		break;

	    case EXC_SOFTWARE:
		if (code !=  EXC_VAX_SUB_RNG)
		    return(FALSE);

		*unix_signal = SIGFPE;
		*unix_code = FPE_SUBRNG_TRAP;
		break;

	    case EXC_BREAKPOINT:
		*unix_signal = SIGTRAP;
		break;

	    default:
		return(FALSE);
	}
	return(TRUE);
}
