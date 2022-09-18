h21242
s 00011/00001/00029
d D 7.1 90/12/06 13:50:21 bostic 2 1
c add Berkeley specific copyright notice
e
s 00030/00000/00000
d D 1.1 86/01/03 23:49:46 sam 1 0
c date and time created 86/01/03 23:49:46 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*-
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

/*
 * Macros used to define entry points
 * in assembly language routines.
 */
#ifdef GPROF
#define	ENTRY(name, regs) \
	.globl _/**/name; .align 2; _/**/name: .word regs; callf $0,mcount
#define	ASENTRY(name, regs) \
	.globl name; .align 2; name: .word regs; callf $0,mcount
#else
#define	ENTRY(name, regs) \
	.globl _/**/name; .align 2; _/**/name: .word regs
#define	ASENTRY(name, regs) \
	.globl name; .align 2; name: .word regs;
#endif PROF
#define R0	0x0001
#define R1	0x0002
#define R2	0x0004
#define R3	0x0008
#define R4	0x0010
#define R5	0x0020
#define R6	0x0040
#define	R7	0x0080
#define	R8	0x0100
#define	R9	0x0200
#define	R10	0x0400
#define	R11	0x0800
#define	R12	0x1000
E 1
