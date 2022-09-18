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
 * $Log:	exception.h,v $
 * Revision 2.6  89/10/15  02:05:21  rpd
 * 	Minor cleanups.
 * 
 * Revision 2.5  89/03/09  20:19:30  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:13:29  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/07  00:52:07  mwyoung
 * Relocated from sys/exception.h
 * 
 * Revision 2.2  88/08/24  02:26:52  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:12:09  mwyoung]
 *
 * 29-Sep-87  David Black (dlb) at Carnegie-Mellon University
 *	Created.
 *
 */

#ifndef	_MACH_EXCEPTION_H_
#define _MACH_EXCEPTION_H_

#include <mach/machine/exception.h>

/*
 *	Machine-independent exception definitions.
 */

#define EXC_BAD_ACCESS		1	/* Could not access memory */
		/* Code contains kern_return_t describing error. */
		/* Subcode contains bad memory address. */

#define EXC_BAD_INSTRUCTION	2	/* Instruction failed */
		/* Illegal or undefined instruction or operand */

#define EXC_ARITHMETIC		3	/* Arithmetic exception */
		/* Exact nature of exception is in code field */

#define EXC_EMULATION		4	/* Emulation instruction */
		/* Emulation support instruction encountered */
		/* Details in code and subcode fields	*/

#define EXC_SOFTWARE		5	/* Software generated exception */
		/* Exact exception is in code field. */
		/* Codes 0 - 0xFFFF reserved to hardware */
		/* Codes 0x10000 - 0x1FFFF reserved for OS emulation (Unix) */

#define EXC_BREAKPOINT		6	/* Trace, breakpoint, etc. */
		/* Details in code field. */

#endif	_MACH_EXCEPTION_H_
