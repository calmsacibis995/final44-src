/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pcb.h,v $
 * Revision 2.5  89/03/09  21:37:04  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:46:19  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.3  88/08/24  02:10:31  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  19:03:22  mwyoung]
 * 
 * 28-Nov-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added missing #ifdef KERNEL bracketing around ast uses.
 *	[ V5.1(XF21) ]
 *
 * 11-Nov-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added fields to pcb for keeping floating point accelerator
 *	flags, state, exception info., and registers.
 *
 * 30-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	LOCORE -> ASSEMBLER.
 *
 * 21-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added pointer to user registers.
 *
 * 05-Mar-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added pcb_exec field to pcb to hold a.out header so it can
 *	be passed onto the debuggers in the core file.
 *
 * 29-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added fields to PCB for keeping floating point processor
 *	state and one flag for rescheduling, single stepping, and
 *	tracing.
 *	Changed "aston" macro to use flag instead of "pcb_p0lr".
 *
 */

/*	@(#)pcb.h 1.1 86/02/03 SMI	*/

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#ifndef	PCB_H_
#define PCB_H_

#ifndef	ASSEMBLER
#include <sys/exec.h>
#endif	ASSEMBLER
#include <sun3/reg.h>
#ifndef	ASSEMBLER
#include <mach/sun3/thread_status.h>
#endif	ASSEMBLER

/*
 * Sun software process control block
 */

#ifndef	ASSEMBLER
struct pcb {
	struct regs		pcb_regs;	/* saved registers */
        struct fp_status	pcb_fp_status;	/* user visible fpp state */
	struct fp_istate 	pcb_fp_istate;	/* internal fpp state */
	int			pcb_flag;
	struct	exec		pcb_exec;	/* a.out hdr. saved for debuggers */
	struct sun_saved_state	*user_regs;	/* user registers */
	short			pcb_fpa_flags; 	/* if zero, pcb_fpa_*'s are meaningless */
	struct fpa_status	pcb_fpa_status; /* saved/restored on ctx switches */
	struct fpa_exception {
		char	*fe_fmtptr;/* points to space holding bus error frame */
		int	fe_pc; /* pc of user code where the bus error occurs */
	} pcb_fpa_exception;
#define pcb_fpa_fmtptr		pcb_fpa_exception.fe_fmtptr
#define pcb_fpa_pc		pcb_fpa_exception.fe_pc
	fpa_long		pcb_fpa_data[FPA_NDATA_REGS];	/* fpa reg.s */
};
#endif

#define AST_SCHED	0x80000000	/* force a reschedule */
#define AST_STEP	0x40000000	/* force a single step */
#define TRACE_USER	0x20000000	/* user has requested tracing */
#define TRACE_AST	0x10000000	/* AST has requested tracing */
#define TRACE_PENDING	0x08000000	/* trace caught in supervisor mode */
#define TRACE_KDB	0x04000000	/* KDB has requested tracing */
#define KDB_STEP	0x02000000	/* force a single step for KDB */
#define AST_CLR		0xf8000000
#define PME_CLR		0
#define AST_NONE	0

#ifdef	KERNEL
#define aston()		{current_thread()->pcb->pcb_flag |= AST_SCHED;}
#endif	KERNEL

#endif	PCB_H_
