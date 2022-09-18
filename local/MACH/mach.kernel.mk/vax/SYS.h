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
 * $Log:	SYS.h,v $
 * Revision 2.3  89/03/09  22:12:36  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:11:08  gm0w
 * 	Changes for cleanup.
 * 
 */

#ifdef	GPROF
#define ENTRY(name, regs) \
	.globl _/**/name; .align 2; _/**/name: .word regs; jsb mcount
#define JENTRY(name) \
	.globl _/**/name; .align 2; _/**/name: jsb jmcount
#else
#define ENTRY(name, regs) \
	.globl _/**/name; .align 2; _/**/name: .word regs
#define JENTRY(name) \
	.globl _/**/name; .align 2; _/**/name:
#endif	PROF
