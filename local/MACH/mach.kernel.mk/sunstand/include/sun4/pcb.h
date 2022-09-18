/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pcb.h,v $
 * Revision 2.2  89/07/11  23:32:30  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)pcb.h 1.5 88/02/08 SMI	*/

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#ifndef _PCB_
#define _PCB_

/*
 * Sun software process control block
 */

#include <machine/reg.h>

#define	MAXWIN	12		/* max number of windows currently supported */

/*
 * The system actually supports one more than the above number.
 * There is always one window reserved for trap handlers that
 * never has to be saved into the pcb struct.
 */

#ifndef LOCORE
struct pcb {
	label_t	pcb_regs;	/* saved pc and sp */
	int	pcb_psr; 	/* processor status word */
	struct	pte *pcb_p0br;	/* pseudo-P0BR for Sun */
	int	pcb_p0lr;	/* pseudo-P0LR for Sun */
	struct	pte *pcb_p1br;	/* pseudo-P1BR for Sun */
	int	pcb_p1lr;	/* pseudo-P1LR for Sun */
	int	pcb_szpt; 	/* number of pages of user page table */
	int	*pcb_sswap;
	int	pcb_uwm;	/* user window mask */
	struct	rwindow pcb_wbuf[MAXWIN]; /* user window save buffer */
	char	*pcb_spbuf[MAXWIN]; /* sp's for each wbuf */
	int	pcb_wbcnt;	/* number of saved windows in pcb_wbuf */
	struct	fpu pcb_fpu;	/* fpu state */
	int	pcb_flags;	/* various state flags */
	int	pcb_wocnt;	/* window overflow count */
	int	pcb_wucnt;	/* window underflow count */
};

#define pcb_pc		pcb_regs.val[0]
#define pcb_sp		pcb_regs.val[1]

#define	aston()		{u.u_pcb.pcb_p0lr |= AST_SCHED;}

#define astoff()	{u.u_pcb.pcb_p0lr &= ~AST_SCHED;}

#endif !LOCORE

/* pcb_p0lr */
#define	AST_SCHED	0x80000000	/* force a reschedule */
#define	AST_CLR		0x80000000
#define	PME_CLR		0
#define	AST_NONE	0

/* pcb_flags */
#define CLEAN_WINDOWS	0x1		/* keep user regs clean */
#define FIX_ALIGNMENT	0x2		/* fix unaligned references */

#endif _PCB_
