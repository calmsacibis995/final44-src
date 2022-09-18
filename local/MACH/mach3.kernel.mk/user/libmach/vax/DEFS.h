/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	DEFS.h,v $
 * Revision 2.3  91/07/31  18:31:29  dbg
 * 	Fixes for standard C.
 * 	[91/07/30  17:30:34  dbg]
 * 
 * Revision 2.2  90/06/19  23:04:09  rpd
 * 	Added ENTRY2.
 * 	[90/06/07            rpd]
 * 
 */
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)DEFS.h	5.1 (Berkeley) 5/30/85
 */

#define R0	0x001
#define R1	0x002
#define R2	0x004
#define R3	0x008
#define R4	0x010
#define R5	0x020
#define R6	0x040
#define	R7 	0x080
#define	R8	0x100
#define	R9	0x200
#define	R10	0x400
#define	R11	0x800

#ifdef	__STDC__

#ifdef PROF
#define	ENTRY(x, regs) \
	.globl _ ## x; .align 2; _ ## x ## : .word regs; \
	.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#define	ENTRY2(x, y, regs) \
	.globl _ ## x; .globl _ ## y; .align 2; \
	_ ## x ## : _ ## y ## : .word regs; \
	.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#define	ASENTRY(x, regs) \
	.globl x; .align 2; x: .word regs; \
	.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#else
#define	ENTRY(x, regs) \
	.globl _ ## x; .align 2; _ ## x ## : .word regs
#define	ENTRY2(x, y, regs) \
	.globl _ ## x; .globl _ ## y; .align 2; \
	_ ## x ## : _ ## y ## : .word regs
#define	ASENTRY(x, regs) \
	.globl x; .align 2; x: .word regs
#endif

#else	/* __STDC__ */

#ifdef PROF
#define	ENTRY(x, regs) \
	.globl _/**/x; .align 2; _/**/x: .word regs; \
	.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#define	ENTRY2(x, y, regs) \
	.globl _/**/x; .globl _/**/y; .align 2; _/**/x: _/**/y: .word regs; \
	.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#define	ASENTRY(x, regs) \
	.globl x; .align 2; x: .word regs; \
	.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#else
#define	ENTRY(x, regs) \
	.globl _/**/x; .align 2; _/**/x: .word regs
#define	ENTRY2(x, y, regs) \
	.globl _/**/x; .globl _/**/y; .align 2; _/**/x: _/**/y: .word regs
#define	ASENTRY(x, regs) \
	.globl x; .align 2; x: .word regs
#endif

#endif	/* __STDC__ */
