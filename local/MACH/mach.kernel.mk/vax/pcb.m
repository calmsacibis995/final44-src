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
 * $Log:	pcb.m,v $
 * Revision 2.2  89/02/25  20:26:58  gm0w
 * 	Changes for cleanup.
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)pcb.m	7.1 (Berkeley) 6/5/86
 */

/*
 * VAX process control block
 */
	.set	PCB_KSP,	0
	.set	PCB_ESP,	4
	.set	PCB_SSP,	8
	.set	PCB_USP,	12
	.set	PCB_R0,		16
	.set	PCB_R1,		20
	.set	PCB_R2,		24
	.set	PCB_R3,		28
	.set	PCB_R4,		32
	.set	PCB_R5,		36
	.set	PCB_R6,		40
	.set	PCB_R7,		44
	.set	PCB_R8,		48
	.set	PCB_R9,		52
	.set	PCB_R10,	56
	.set	PCB_R11,	60
	.set	PCB_R12,	64
	.set	PCB_R13,	68
	.set	PCB_PC,		72
	.set	PCB_PSL,	76
	.set	PCB_P0BR,	80
	.set	PCB_P0LR,	84
	.set	PCB_P1BR,	88
	.set	PCB_P1LR,	92
/*
 * Software pcb extension
 */
	.set	PCB_SZPT,	96	/* number of user page table pages */
	.set	PCB_CMAP2,	100	/* saved cmap2 across cswitch (ick) */
	.set	PCB_SSWAP,	104	/* flag for non-local goto */
	.set	PCB_SIGC,	108	/* signal trampoline code */
