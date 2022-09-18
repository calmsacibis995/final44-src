/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pcb.h,v $
 * Revision 2.2  89/07/11  23:28:47  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)pcb.h 5.7 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#include <machine/reg.h>

/*
 * Sun software process control block
 */

#ifndef LOCORE
struct pcb {
	label_t	pcb_regs;	/* saved registers */
	int	pcb_sr; 	/* program status word */
	struct	pte *pcb_p0br;	/* pseudo-P0BR for Sun */
	int	pcb_p0lr;	/* pseudo-P0LR for Sun */
	struct	pte *pcb_p1br;	/* pseudo-P1BR for Sun */
	int	pcb_p1lr;	/* pseudo-P1LR for Sun */
	int	pcb_szpt; 	/* number of pages of user page table */
	int	*pcb_sswap;
	struct fp_status u_fp_status;	/* user visible fpp state */
/*
 * Struct for the internal state of the MC68881
 * This is the maximum allowed by the coprocessor interface for internal state.
 */
#define	FPIS_BUFSIZ	0x100
	struct fp_istate {
		unsigned char	fpis_vers;	/* version number */
		unsigned char	fpis_bufsiz;	/* size of info in fpis_buf */
		unsigned short	fpis_reserved;	/* reserved word */
		unsigned char	fpis_buf[FPIS_BUFSIZ];	/* fpp internal state buffer */
	} u_fp_istate;	/* internal fpp state */
	/* fpa only */
	short	u_fpa_flags; /* if zero, u_fpa_*'s are meaningless */
	struct fpa_status u_fpa_status; /* saved/restored on ctx switches */
	struct fpa_exception {
		caddr_t	fe_fmtptr; /* points to space holding bus error frame */
		int	fe_pc; /* pc of user code where the bus error occurs */
	} u_fpa_exception;
#define u_fpa_fmtptr		u_fpa_exception.fe_fmtptr
#define u_fpa_pc		u_fpa_exception.fe_pc
	/* end fpa only */
};
#endif

#define	AST_SCHED	0x80000000	/* force a reschedule */
#define	AST_STEP	0x40000000	/* force a single step */
#define	TRACE_USER	0x20000000	/* user has requested tracing */
#define	TRACE_AST	0x10000000	/* AST has requested tracing */
#define	TRACE_PENDING	0x08000000	/* trace caught in supervisor mode */
#define	AST_CLR		0xf8000000
#define	PME_CLR		0
#define	AST_NONE	0

#define	aston()		{u.u_pcb.pcb_p0lr |= AST_SCHED;}
