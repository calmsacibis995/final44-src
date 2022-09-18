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
 * $Log:	asm.h,v $
 * Revision 2.4  89/03/09  22:12:44  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:11:15  gm0w
 * 	Changes for cleanup.
 * 
 *  5-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Moved CPU_NUMBER_R0 here from vax/cpu.h.  Made it dispatch
 *	to a model-dependent cpu_number routine; the ESP hack is not
 *	reliable.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created with defintions for ENTRY and JSBENTRY.
 *
 */
/*
 *	File:	vax/asm.h
 *	Author:	Avadis Tevanian, Jr.
 */

#include <cpus.h>

#ifdef	GPROF
#define ENTRY(name, regs) \
	.globl _/**/name; .align 1; _/**/name: .word regs; jsb mcount
#define JSBENTRY(name, regs) \
	.globl _/**/name; _/**/name: \
	movl fp,-(sp); movab -12(sp),fp; pushr $(regs); jsb mcount; \
	popr $(regs); movl (sp)+,fp
#else
#define ENTRY(name, regs) \
	.globl _/**/name; .align 1; _/**/name: .word regs
#define JSBENTRY(name, regs) \
	.globl _/**/name; _/**/name:
#endif	GPROF

#define R0	0x01
#define R1	0x02
#define R2	0x04
#define R3	0x08
#define R4	0x10
#define R5	0x20
#define R6	0x40
#define R7	0x80
#define R8	0x100
#define R9	0x200
#define R10	0x400
#define R11	0x800

#if	NCPUS == 1
#define CPU_NUMBER_R0	clrl	r0
#else	NCPUS == 1
#define CPU_NUMBER_R0	jsb	*_Cpu_number_ptr
#endif	NCPUS == 1
