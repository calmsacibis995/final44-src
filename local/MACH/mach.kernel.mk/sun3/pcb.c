/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pcb.c,v $
 * Revision 2.6  89/02/25  19:46:08  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.5  88/08/25  18:20:11  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Correct typo.
 * 	[88/08/12  13:30:43  mwyoung]
 * 	
 * 	Implement THREAD_STATE_FLAVOR_LIST flavor in thread_getstatus.
 * 	[88/08/11  18:49:15  mwyoung]
 * 
 * 17-Mar-88  David Golub (dbg) at Carnegie-Mellon University
 *	Allow thread_setstatus to set the trace bits.
 *
 * 12-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added call to fpa_save() in pcb_synch().
 *	Changed to test FPA_USED bit in pcb_fpa_flags to see if
 *	FPA is being used.
 *
 * 25-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Rather than have "u" expand to current_thread()->u_address, have
 *	it expand to the constant U_ADDRESS which is updated by load_context
 *	when the thread changes.
 *	Define load_context_data() to set U_ADDRESS.utask and U_ADDRESS.uthread.
 *	And be sure to have initial_context call it.
 *
 * 21-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Changed for new thread_status interface.
 *
 * 07-Jan-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added call to fpa_fork_context() in thread_dup() to copy
 *	FPA context from parent to child.
 *	Created pcb_terminate().
 *
 * 17-Nov-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed FPIS_NULLSZ to FPIS_VERSNULL.
 *
 * 15-Dec-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Changed pcb parameter to pcb_init() to be the thread
 *	(so that all functions in this module take consistent 
 *	parameters).
 *
 * 17-Aug-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed thread_{set,get}status to return something of
 *	type kern_return_t.
 *
 * 10-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	Added pcb_synch() stub pending real implementation.
 *
 * 20-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added support for MACH.
 *
 * 23-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added thread_start for MACH option.
 *
 *  9-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Created.
 *
 */

#include <kern/thread.h>
#include <mach/thread_status.h>
#include <mach/vm_param.h>
#include <sun3/pcb.h>
#include <sun3/psl.h>
#include <mach/machine/kern_return.h>
#include <fpa.h>
#if	NFPA >0
#include <sundev/fpareg.h>
#endif	NFPA >0

extern thread_t	fp_threads[];
extern short	fppstate;

void pcb_init(thread, ksp)
	struct thread *thread;
	vm_offset_t	ksp;
{
	struct pcb	*pcb = thread->pcb;

	int	thread_bootstrap();

	struct sun_saved_state	*state;

	bzero((caddr_t)pcb, sizeof(struct pcb));

	/*
	 *	Set up thread to start at user bootstrap.  The user
	 *	register block is put at the top of the kernel stack as
	 *	if the thread had just taken a SYSCALL trap.  Thread-
	 *	bootstrap will simulate returning from a trap.
	 *
	 */

	pcb->pcb_regs.r_pc = (int) thread_bootstrap;
	pcb->pcb_regs.r_sr = SR_LOW;	/* kernel mode, interrupts on */
	state = (struct sun_saved_state *)
		  (ksp + KERNEL_STACK_SIZE - sizeof(struct sun_saved_state));
	/*
	 *	Leave a word on the kernel stack for the return address from
	 *	load_context.
	 */
	pcb->pcb_regs.r_sp = ((int) state) - sizeof(int);

	pcb->user_regs = state;

	/*
	 *	Guarantee that the bootstrapped thread will be in user
	 *	mode (this psl assignment above executes the bootstrap
	 *	code in kernel mode.  Note, this is the only user register
	 *	that we set.  All others are assumed to be random unless
	 *	the user sets them.
	 *
	 *	Also set up the rte frame to return from.
	 */
	state->sr = SR_USER;
	state->stkfmt = 0;	/* short format stack frame */
	state->vector = 0;
}

/*
 *      Set up the context for the very first thread to execute
 *      (which is passed in as the parameter).
 */
void initial_context(thread)
	thread_t	thread;
{
	active_threads[cpu_number()] = thread;
	pmap_activate(vm_map_pmap(thread->task->map), thread, cpu_number());
	load_context_data();
}

/*
 *	thread_start:
 *
 *	Start a thread at the specified routine.  The thread must be in a
 *	suspended state.
 */

thread_start(thread, start, mode)
	thread_t	thread;
	void		(*start)();
	int		mode;
{
	int		start_addr;
	register struct pcb	*pcb;

	pcb = thread->pcb;

	pcb->pcb_regs.r_pc = (int) start;	/* start at the beginning */
	if (mode == THREAD_USERMODE)
		pcb->pcb_regs.r_sr = SR_USER; /* user mode */
	else
		pcb->pcb_regs.r_sr = SR_LOW; /* kernel mode, all interrupts
						enabled */
	/*
	 *	Leave a word at the top of the kernel stack for the
	 *	return address from load_context.
	 */
	pcb->pcb_regs.r_sp = thread->kernel_stack + KERNEL_STACK_SIZE
			- sizeof(int);
	pcb->pcb_regs.r_areg[6] = thread->kernel_stack;	/* for mcount */
}

load_context_data()
{
	U_ADDRESS.uthread = active_threads[cpu_number()]->u_address.uthread;
	U_ADDRESS.utask   = active_threads[cpu_number()]->u_address.utask;
}

/*
 *	thread_setstatus:
 *
 *	Set the status of the specified thread.
 */

kern_return_t thread_setstatus(thread, flavor, tstate, count)
	thread_t		thread;
	int			flavor;
	thread_state_t		tstate;
	unsigned int		count;
{
	register struct sun_thread_state	*state;
	register struct sun_saved_state		*saved_state;
	register struct pcb			*pcb;

	if (flavor == SUN_THREAD_STATE_REGS) {
	    if (count < SUN_THREAD_STATE_REGS_COUNT) {
		return(KERN_INVALID_ARGUMENT);
	    }
	    state = (struct sun_thread_state *) tstate;

	    pcb = thread->pcb;
	    saved_state = pcb->user_regs;

	    saved_state->d0 = state->d0;
	    saved_state->d1 = state->d1;
	    saved_state->d2 = state->d2;
	    saved_state->d3 = state->d3;
	    saved_state->d4 = state->d4;
	    saved_state->d5 = state->d5;
	    saved_state->d6 = state->d6;
	    saved_state->d7 = state->d7;

	    saved_state->a0 = state->a0;
	    saved_state->a1 = state->a1;
	    saved_state->a2 = state->a2;
	    saved_state->a3 = state->a3;
	    saved_state->a4 = state->a4;
	    saved_state->a5 = state->a5;
	    saved_state->a6 = state->a6;

	    saved_state->sp = state->sp;
	    saved_state->pc = state->pc;

	    /*
	     *	Enforce user mode status register:
	     *	must have user mode, user stack, interrupt priority 0.
	     *	User may set trace bits, but both trace bits cannot be
	     *	on (undefined).
	     */
	    saved_state->sr = state->sr & ~(SR_SMODE|SR_MASTER|SR_INTPRI);
	    if ((saved_state->sr & (SR_T1|SR_T0)) == (SR_T1|SR_T0))
		saved_state->sr &= ~SR_T0;

	    if (fppstate > 0) {
		/*
		 *	FP registers are in the pcb
		 */
		if (pcb->pcb_fp_status.fps_flags == FPS_UNUSED) {
		    /* how do we make load_context load new FP
		       register values? */
		}
		pcb->pcb_fp_status = state->fp;

		/*
		 *	Force fp registers to be reloaded if this thread was
		 *	the last thread to use the floating-point hardware.
		 */
		if (thread == fp_threads[0])
		    fp_threads[0] = THREAD_NULL;
	    }
	    return(KERN_SUCCESS);
	}
	else if (flavor == SUN_THREAD_STATE_FPA) {
	    if (count < SUN_THREAD_STATE_FPA_COUNT)
		return(KERN_INVALID_ARGUMENT);
	
#if	NFPA > 0
	    /*
	     *	Set this thread's FPA registers	XXX
	     */
#else	NFPA > 0
	    return(KERN_FAILURE);		/* no FPA */
#endif	NFPA > 0
	}
	else {
	    return(KERN_INVALID_ARGUMENT);
	}
}

/*
 *	thread_getstatus:
 *
 *	Get the status of the specified thread.
 */

kern_return_t thread_getstatus(thread, flavor, tstate, count)
	register thread_t	thread;
	int			flavor;
	thread_state_t		tstate;	/* pointer to OUT array */
	unsigned int		*count;		/* IN/OUT */
{
	register struct sun_thread_state	*state;
	register struct sun_saved_state		*saved_state;
	register struct pcb			*pcb;

	switch (flavor) {
		case THREAD_STATE_FLAVOR_LIST:
			if (*count < 2)
				return(KERN_INVALID_ARGUMENT);
			tstate[0] = SUN_THREAD_STATE_REGS;
			tstate[1] = SUN_THREAD_STATE_FPA;
			*count = 2;
			break;

		case SUN_THREAD_STATE_REGS:
			if (*count < SUN_THREAD_STATE_REGS_COUNT) {
				return(KERN_INVALID_ARGUMENT);
			}

			state = (struct sun_thread_state *) tstate;

			pcb = thread->pcb;
			saved_state = pcb->user_regs;

			state->d0 = saved_state->d0;
			state->d1 = saved_state->d1;
			state->d2 = saved_state->d2;
			state->d3 = saved_state->d3;
			state->d4 = saved_state->d4;
			state->d5 = saved_state->d5;
			state->d6 = saved_state->d6;
			state->d7 = saved_state->d7;
			state->a0 = saved_state->a0;
			state->a1 = saved_state->a1;
			state->a2 = saved_state->a2;
			state->a3 = saved_state->a3;
			state->a4 = saved_state->a4;
			state->a5 = saved_state->a5;
			state->a6 = saved_state->a6;
			state->sp = saved_state->sp;

			state->pc = saved_state->pc;
			state->sr = saved_state->sr;

			if (fppstate > 0) {
				/*
				 *	Fp registers are in the PCB
				 */
				pcb->pcb_fp_status.fps_flags =
					EXT_FPS_FLAGS(&pcb->pcb_fp_istate);
				state->fp = pcb->pcb_fp_status;
			}
			else {
				/*
				 *	No working FP hardware
				 */
				bzero((caddr_t)&state->fp, sizeof(state->fp));
			}
			*count = SUN_THREAD_STATE_REGS_COUNT;
			break;
			
		case SUN_THREAD_STATE_FPA:
			if (*count < SUN_THREAD_STATE_FPA_COUNT)
				return(KERN_INVALID_ARGUMENT);
	
#if	NFPA > 0
			/* XXX There probably should also be a runtime check
			 *     for FPA presence.
			 */
			/*
			 *	Get this thread's FPA registers	XXX
			 */
			*count = SUN_THREAD_STATE_FPA_COUNT;
#else	NFPA > 0
			return(KERN_FAILURE);		/* no FPA */
#endif	NFPA > 0
			break;

		default:
			return(KERN_INVALID_ARGUMENT);
	}
	return(KERN_SUCCESS);
}

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>

/*
 *	thread_dup:
 *
 *	Duplicate the user's state of a thread.  This is only used to perform
 *	the Unix fork operation.
 *
 *	Assumes that the child thread's pcb and user registers have been
 *	initialized as by pcb_init.
 */
thread_dup(parent, child)
	register thread_t	parent, child;
{
	register struct sun_saved_state	*child_state, *parent_state;
	register struct pcb *parentpcb;

	parentpcb = parent->pcb;
	parent_state = parentpcb->user_regs;
	child_state = child->pcb->user_regs;

	*child_state = *parent_state;

	child_state->d0 = proc[child->task->proc_index].p_pid;
	child_state->d1 = 1;
	child_state->sr &= ~SR_CC;

	/*
	 *	Don't forget to pop the system call number from the
	 *	child's stack.
	 */
	child_state->sp += sizeof(int);

	/*
	 *	Copy any floating-point state.
	 */
	pcb_synch(parent);	/* force parent's FP state to memory */
	if (parent->pcb->pcb_fp_istate.fpis_bufsiz != FPIS_VERSNULL) {
	    /*
	     *	Copy floating point state
	     */
	    child->pcb->pcb_fp_status = parent->pcb->pcb_fp_status;
	    child->pcb->pcb_fp_istate = parent->pcb->pcb_fp_istate;
	}
	else {
	    /*
	     *	No floating point state to save - zero it.
	     */
	    bzero((caddr_t)&child->pcb->pcb_fp_status,
			sizeof(struct fp_status));
	    child->pcb->pcb_fp_istate.fpis_bufsiz = FPIS_VERSNULL;
	}

#if	NFPA > 0
	/*
	 *	Copy FPA context from parent to child
	 */
	if (parentpcb->pcb_fpa_flags)
		fpa_fork_context(parent, child);
#endif	NFPA > 0
}

void pcb_terminate(thread)
struct thread *thread;
{
#if	NFPA > 0
	if (thread->pcb->pcb_fpa_flags & FPA_USED)
		fpaclose_thread(thread);
#endif	NFPA > 0
}

/*
 *	pcb_synch() stores registers that the kernel doesn't save
 *	into the pcb.  On the sun, this means floating point registers.
 */
pcb_synch(thread)
	register thread_t	thread;
{
	register struct pcb	*pcb;
 
	if (thread != current_thread()) {
	    /*
	     *	If thread is not running, FP registers have already
	     *	been saved.
	     *
	     *	FPA - XXX
	     */
	    return;
	}

	if (fppstate > 0) {
	    savefppregs();
	    thread->pcb->pcb_fp_status.fps_flags =
			EXT_FPS_FLAGS(&thread->pcb->pcb_fp_istate);
	}
#if	NFPA > 0
	pcb = thread->pcb;
	if ((pcb->pcb_fpa_flags & FPA_USED) && 
			(pcb->pcb_fpa_flags & FPA_CTX_SAVED) == 0){
		fpa_save(thread, 1);
		fpa_free_context(pcb->pcb_fpa_status.fpas_state & FPA_CONTEXT);
		pcb->pcb_fpa_flags |= FPA_CTX_SAVED;
	}
#endif	NFPA > 0
}
