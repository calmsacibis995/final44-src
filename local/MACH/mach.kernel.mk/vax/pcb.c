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
 * $Log:	pcb.c,v $
 * Revision 2.5  89/02/25  20:26:43  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/08/25  18:22:20  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Implement THREAD_STATE_FLAVOR_LIST flavor of thread state.
 * 	[88/08/11  18:50:23  mwyoung]
 * 
 *  4-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	Remove pcb_addr from thread structure.
 *
 * 31-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Initialize pmap portion of PCB here.  We can't assume that a
 *	pmap_activate will do everything.
 *
 * 14-Mar-88  David Golub (dbg) at Carnegie-Mellon University
 *	Ensure that appropriate PSL bits are turned off if compatibility
 *	mode is set.
 *
 * 12-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Modify for new thread_status interface.
 *
 * 15-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Make pcb_init take a thread pointer instead of a pcb pointer as
 *	a parameter.  Remove dead code.
 *
 * 15-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH_TT: De-linted.
 *
 * 11-Jul-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Add space for a calling frame at the top of a kernel stack,
 *	and properly initialize frame pointer in thread_start().
 *
 * 10-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TT: added dummy pcb_synch() routine.
 *
 * 28-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added count parameters to thread_getstatus and thread_setstatus.
 *
 * 29-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added thread_dup for proper handling of fork under Unix
 *	compatibility.
 *
 * 27-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added thread_setstatus machine dependent routine which is used to
 *	set the user register state.
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 15-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Use the "mode" argument to thread_start to determine if thread
 *	executes in kernel or user state.
 *
 * 30-Sep-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Add thread_start routine which is the machine dependent routine
 *	for starting a thread.
 *
 * 29-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added include of <sys/types.h>.
 *
 */
/*
 *	File:	vax/pcb.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young, David Golub
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young,
 *					David Golub
 *
 *	Vax PCB management
 */

#include <vax/pcb.h>
#include <vax/mtpr.h>
#include <vax/psl.h>
#include <kern/thread.h>
#include <mach/thread_status.h>
#include <mach/vm_param.h>
#include <sys/types.h>		/* for caddr_t in use of bzero */
#include <vax/frame.h>

void pcb_init(thread, ksp)
	register thread_t	thread;
	register vm_offset_t	ksp;
{
	register struct pcb	*pcb = thread->pcb;
	register struct vax_saved_state		*saved_state;

	int	thread_bootstrap();

	bzero((caddr_t)pcb, sizeof(struct pcb));

	/*
	 *	Set up thread to start at user bootstrap.  The frame
	 *	pointer is setup to point to the frame that corresponds
	 *	to the user's state (thread_bootstrap will perform a
	 *	ret instruction to simulate returning from a trap).
	 *
	 */
	pcb->pcb_pc = (int) thread_bootstrap;
	pcb->pcb_psl = 0;	/* kernel mode */
	saved_state = (struct vax_saved_state *)
				(ksp + KERNEL_STACK_SIZE -
					sizeof(struct vax_saved_state));
	pcb->pcb_ksp = ((int) saved_state) - 8;
	pcb->pcb_fp = pcb->pcb_ksp;

	/*
	 *	Initialize the PCB versions of the mapping information
	 */

	PMAP_PCB_INITIALIZE(pcb);

	/*
	 *	Guarantee that the bootstrapped thread will be in user
	 *	mode (this psl assignment above executes the bootstrap
	 *	code in kernel mode).  Note, this is the only user register
	 *	that we set.  All others are assumed to be random unless
	 *	the user sets them.
	 */
	saved_state->ps = PSL_CURMOD|PSL_PRVMOD;
	saved_state->nargs = 0;		/* easier here */

	pcb->pcb_ssp = (int)thread;	/* SSP is used for current thread */
	pcb->pcb_esp = -1;		/* ESP is not used at all */
}

/*
 *	Set up the context for the very first thread to execute
 *	(which is passed in as the parameter).
 */
void initial_context(thread)
	thread_t	thread;
{
	active_threads[cpu_number()] = thread;
	pmap_activate(vm_map_pmap(thread->task->map), thread, cpu_number());
}

/*
 *	thread_start:
 *
 *	Start a thread at the specified routine.  The thread must
 *	be in a suspended state.
 */

thread_start(thread, start, mode)
	register thread_t	thread;
	void			(*start)();
	int			mode;
{
	int			start_addr;
	register struct pcb	*pcb;

	start_addr = (int) start + 2;
	pcb = thread->pcb;
	pcb->pcb_pc = start_addr;
	if (mode == THREAD_USERMODE)
		pcb->pcb_psl = PSL_PRVMOD|PSL_CURMOD;	/* user mode */
	else
		pcb->pcb_psl = 0;			/* kernel mode */
	pcb->pcb_ksp = thread->kernel_stack + KERNEL_STACK_SIZE
			- sizeof(struct frame);	/* allow space for a fake stack frame */
	pcb->pcb_fp = pcb->pcb_ksp;
	bzero((caddr_t)pcb->pcb_fp, sizeof(struct frame));
						/* and clear it */
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
	register struct vax_thread_state	*state;
	register struct vax_saved_state		*saved_state;

	if (flavor != VAX_THREAD_STATE || count < VAX_THREAD_STATE_COUNT)
		return(KERN_INVALID_ARGUMENT);

	state = (struct vax_thread_state *) tstate;
	saved_state = USER_REGS(thread);

	saved_state->r0 = state->r0;
	saved_state->r1 = state->r1;
	saved_state->r2 = state->r2;
	saved_state->r3 = state->r3;
	saved_state->r4 = state->r4;
	saved_state->r5 = state->r5;
	saved_state->r6 = state->r6;
	saved_state->r7 = state->r7;
	saved_state->r8 = state->r8;
	saved_state->r9 = state->r9;
	saved_state->r10 = state->r10;
	saved_state->r11 = state->r11;
	saved_state->ap = state->ap;
	saved_state->fp = state->fp;
	saved_state->sp = state->sp;
	saved_state->pc = state->pc;

	/*
	 *	Carefully set PSL bits
	 */
	saved_state->ps = (state->ps | PSL_USERSET) & ~PSL_USERCLR;
	if (saved_state->ps & PSL_CM)
	    saved_state->ps &= ~ (PSL_FPD|PSL_DV|PSL_FU|PSL_IV);

	return(KERN_SUCCESS);
}

/*
 *	thread_getstatus:
 *
 *	Get the status of the specified thread.
 */

kern_return_t thread_getstatus(thread, flavor, tstate, count)
	register thread_t	thread;
	int			flavor;
	thread_state_t		tstate;		/* pointer to OUT array */
	unsigned int		*count;		/* IN/OUT */
{
	register struct vax_thread_state	*state;
	register struct vax_saved_state		*saved_state;

	if (flavor != 0) {
	    if (flavor != VAX_THREAD_STATE ||
		*count < VAX_THREAD_STATE_COUNT) {
		    return(KERN_INVALID_ARGUMENT);
	    }
	}

	switch (flavor) {
		case THREAD_STATE_FLAVOR_LIST:
			if (*count < 1)
				return(KERN_INVALID_ARGUMENT);
			tstate[0] = VAX_THREAD_STATE;
			*count = 1;
			break;
		
		case VAX_THREAD_STATE:
			state = (struct vax_thread_state *) tstate;
			saved_state = USER_REGS(thread);

			state->r0 = saved_state->r0;
			state->r1 = saved_state->r1;
			state->r2 = saved_state->r2;
			state->r3 = saved_state->r3;
			state->r4 = saved_state->r4;
			state->r5 = saved_state->r5;
			state->r6 = saved_state->r6;
			state->r7 = saved_state->r7;
			state->r8 = saved_state->r8;
			state->r9 = saved_state->r9;
			state->r10 = saved_state->r10;
			state->r11 = saved_state->r11;
			state->ap = saved_state->ap;
			state->fp = saved_state->fp;
			state->sp = saved_state->sp;
			state->pc = saved_state->pc;
			state->ps = saved_state->ps;

			*count = VAX_THREAD_STATE_COUNT;
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
 */
thread_dup(parent, child)
	register thread_t	parent, child;
{
	register struct vax_saved_state	*parent_state,
					*child_state;

	/*
	 *	Parent_state is NOT at top of stack - initial process
	 *	has things on stack first (XXX)
	 */
	parent_state = ((struct vax_saved_state *)
			 (parent->u_address.uthread->uu_ar0))
			- 1;
	child_state = USER_REGS(child);
	*child_state = *parent_state;

	child_state->r0 = proc[child->task->proc_index].p_pid;
	child_state->r1 = 1;
	child_state->ps &= ~PSL_C;
}

