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
 * $Log:	pcb.h,v $
 * Revision 2.6  89/03/09  22:20:02  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:26:52  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/07/17  19:34:07  mwyoung
 * *** empty log message ***
 * 
 * Revision 2.3  88/06/28  20:58:32  mwyoung
 * MACH: Remove unused software additions to the pcb.
 * 
 * 29-Feb-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Remove unused software additions to the pcb.
 *
 * 15-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added declaration of pcb_terminate.
 *
 * 28-Nov-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added missing #ifdef KERNEL bracketing around ast uses.
 *	[ V5.1(XF21) ]
 *
 * 29-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Remove include of pmap.h, we are only using a struct pointer
 *	here, hence we do not need the include.
 *
 * 28-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Directly define ASTLVL here (avoiding include of mtpr.h which
 *	fouls up kernel debugger compilation).
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)pcb.h	7.1 (Berkeley) 6/5/86
 */
#ifndef	_PCB_
#define _PCB_

/*
 * VAX process control block
 */

struct pcb
{
	int	pcb_ksp; 	/* kernel stack pointer */
	int	pcb_esp; 	/* exec stack pointer */
	int	pcb_ssp; 	/* supervisor stack pointer */
	int	pcb_usp; 	/* user stack pointer */
	int	pcb_r0; 
	int	pcb_r1; 
	int	pcb_r2; 
	int	pcb_r3; 
	int	pcb_r4; 
	int	pcb_r5; 
	int	pcb_r6; 
	int	pcb_r7; 
	int	pcb_r8; 
	int	pcb_r9; 
	int	pcb_r10; 
	int	pcb_r11; 
	int	pcb_r12; 
#define pcb_ap pcb_r12
	int	pcb_r13; 
#define pcb_fp pcb_r13
	int	pcb_pc; 	/* program counter */
	int	pcb_psl; 	/* program status longword */
	struct pt_entry	*pcb_p0br;
	int	pcb_p0lr; 	/* seg 0 length register and astlevel */
	struct pt_entry	*pcb_p1br;
	int	pcb_p1lr; 	/* seg 1 length register and pme */
};

#define ASTLVL	0x13		/* asynchronous system trap level */
#define AST_NONE	0x04000000	/* ast level */
#define AST_USER	0x03000000	/* ast for user mode */

#define ASTLVL_NONE	4
#define ASTLVL_USER	3

#define AST_CLR		0x07000000
#define PME_CLR		0x80000000

#ifdef	KERNEL
#define aston() \
	{ \
		mtpr(ASTLVL, ASTLVL_USER); \
	}

#define astoff() \
	{ \
		mtpr(ASTLVL, ASTLVL_NONE); \
	}

/*
 *	Kernel routines for manipulating pcb.
 */
void	pcb_init();

/*
 *	pcb_terminate and pcb_synch are unneeded on the VAX.
 */
#define pcb_terminate(thread)
#define pcb_synch(thread)

#endif	KERNEL
#endif	_PCB_
