/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sun3_exception.c,v $
 * Revision 2.2  89/02/25  19:47:28  gm0w
 * 	Changes for cleanup.
 * 
 * 10-Feb-89  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added new copyright, fixed includes, and removed else leg
 *	of CMU and MACH conditionals as part of kernel cleanup.
 *
 */
#include <mach/boolean.h>
#include <mach/exception.h>
#include <mach/kern_return.h>
#include <sys/signal.h>

/*
 *	machine_exception translates a mach exception to a unix exception
 *	and code.  This handles all the hardware-specific exceptions for
 *	the sun3.  unix_exception() handles the machine-independent ones.
 */

boolean_t machine_exception(exception, code, subcode, unix_signal, unix_code)
int	exception, code, subcode;
int	*unix_signal, *unix_code;
{
	switch(exception) {

	    case EXC_BAD_INSTRUCTION:
		if (code == EXC_SUN3_FLT_BSUN ||
		    code == EXC_SUN3_FLT_OPERAND_ERROR) {
			*unix_signal = SIGFPE;
		}
		else {
			*unix_signal = SIGILL;
		}
		break;

	    case EXC_ARITHMETIC:
	        *unix_signal = SIGFPE;
		break;

	    case EXC_EMULATION:
	        *unix_signal = SIGEMT;
		break;

	    case EXC_SOFTWARE:
		if (code != EXC_SUN3_CHK && code != EXC_SUN3_TRAPV)
			return(FALSE);

		*unix_signal = SIGFPE;
		break;

	    case EXC_BREAKPOINT:
		*unix_signal = SIGTRAP;
		break;

	    default:
		return(FALSE);
	}
/*
 *	Mach code numbers for the sun3 were carefully chosen to match the
 *	Unix numbers.
 */
	*unix_code = code;
	return(TRUE);
}


