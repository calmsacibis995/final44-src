/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987,1986 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 *	File:	vax/pcb.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young, David Golub,
 *		1986.
 *
 *	Vax PCB management
 *
 * HISTORY
 * $Log:	pcb.c,v $
 * Revision 2.7  92/01/03  20:33:15  dbg
 * 	Add user_stack_low and set_user_regs for passing control to
 * 	bootstrap in user space.
 * 	[91/08/02            dbg]
 * 
 * Revision 2.6  91/07/31  18:19:48  dbg
 * 	Add thread_set_syscall_return.
 * 	[91/07/30  17:24:07  dbg]
 * 
 * Revision 2.5  91/05/14  17:45:20  mrt
 * 	Correcting copyright
 * 
 * Revision 2.4  91/05/08  13:20:43  dbg
 * 	Support for stack switching.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.3  91/03/16  15:02:17  rpd
 * 	Added continuation argument to stack_attach.
 * 	[91/03/14            rpd]
 * 
 * Revision 2.2  91/01/08  16:42:07  rpd
 * 	Added KEEP_STACKS support.
 * 	[91/01/06            rpd]
 * 
 * Revision 2.1  89/08/03  16:11:56  rwd
 * Created.
 * 
 * 31-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Moved PCB to top of kernel stack, to allow for a per-thread
 *	'private data' area at the base of the kernel stack.  Removed
 *	non-MACH code.
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

#include <mach_debug.h>

#include <mach/kern_return.h>
#include <mach/thread_status.h>
#include <mach/vm_param.h>

#include <kern/counters.h>
#include <kern/mach_param.h>
#include <kern/sched_prim.h>
#include <kern/thread.h>
#include <vm/vm_kern.h>
#include <vm/pmap.h>

#include <vax/thread.h>
#include <vax/psl.h>

zone_t pcb_zone;

extern void	Thread_continue();
extern thread_t	Switch_context();

/*
 *	Initialize PCB module.
 */
void
pcb_module_init()
{
	pcb_zone = zinit(sizeof(struct vax_pcb),
			 THREAD_MAX * sizeof(struct vax_pcb),
			 THREAD_CHUNK * sizeof(struct vax_pcb),
			 FALSE, "pcb");
}

/*
 *	stack_attach:
 *
 *	Attach a kernel stack to a thread.
 */

void stack_attach(thread, stack, continuation)
	register thread_t thread;
	register vm_offset_t stack;
	void (*continuation)();
{
	register struct vax_kernel_state *vks;

	counter(if (++c_stacks_current > c_stacks_max)
			c_stacks_max = c_stacks_current);

	thread->kernel_stack = stack;

	/*
	 *	We want to run continuation, giving it as an argument
	 *	the return value from Load_context/Switch_context.
	 *	Thread_continue takes care of the mismatch between
	 *	the argument-passing/return-value conventions.
	 *	This function will not return normally,
	 *	so we don't have to worry about a return address.
	 */

	stack = stack + KERNEL_STACK_SIZE
		- sizeof(struct vax_saved_state *);
	*(struct vax_saved_state **)stack = &thread->pcb->vss;

	vks = (struct vax_kernel_state *)stack - 1;

	vks->handler = 0;
	vks->mask = 0x2fc00000;			/* callS, r6..r11 */
	vks->ap = 0;
	vks->fp = 0;
	vks->pc = (int) Thread_continue;
	vks->r6 = (int) continuation;

	vks->arg_count = 3;

	thread->pcb->vks_p = vks;
}

/*
 *	stack_detach:
 *
 *	Detaches a kernel stack from a thread, returning the old stack.
 */

vm_offset_t stack_detach(thread)
	register thread_t	thread;
{
	register vm_offset_t	stack;

	counter(if (--c_stacks_current < c_stacks_min)
			c_stacks_min = c_stacks_current);

	stack = thread->kernel_stack;
	thread->kernel_stack = 0;

	return stack;
}

/*
 *	stack_handoff:
 *
 *	Move the current thread's kernel stack to the new thread.
 */
void stack_handoff(old, new)
	register thread_t	old;
	register thread_t	new;
{
	register int		mycpu = cpu_number();

	/*
	 * Switch address spaces if switching tasks.
	 */
    {
	register task_t		old_task = old->task;
	register task_t		new_task = new->task;

	if (old_task != new_task) {
	    PMAP_DEACTIVATE_USER(vm_map_pmap(old_task->map), old, mycpu);
	    PMAP_ACTIVATE_USER(vm_map_pmap(new_task->map), new, mycpu);
	}
    }

    {
	register vm_offset_t	stack;

	/*
	 * Save user stack pointer.
	 */
	old->pcb->v_usp = mfpr(USP);

	/*
	 * Get old stack.
	 */
	stack = current_stack();

	/*
	 *	Switch to new thread
	 */
	active_threads[mycpu] = new;
	mtpr(SSP, new);
	mtpr(USP, new->pcb->v_usp);

	/*
	 * Point exception link at new user registers
	 */
	stack = stack + KERNEL_STACK_SIZE
		- sizeof(struct vax_saved_state *);
	*(struct vax_saved_state **)stack = &new->pcb->vss;

    }
}

/*
 *	Full context switch from old thread to new.
 *	Old thread has a possible continuation.
 */
thread_t switch_context(old, continuation, new)
	register thread_t	old;
	void (*continuation)();
	register thread_t	new;
{
	/*
	 * Switch address spaces if switching tasks.
	 */
    {
	register task_t		old_task = old->task;
	register task_t		new_task = new->task;

	if (old_task != new_task) {
	    register int	mycpu = cpu_number();

	    PMAP_DEACTIVATE_USER(vm_map_pmap(old_task->map), old, mycpu);
	    PMAP_ACTIVATE_USER(vm_map_pmap(new_task->map), new, mycpu);
	}
    }

	return Switch_context(old, continuation, new);
}

void pcb_init(thread)
	register thread_t	thread;
{
	register pcb_t		pcb;

	pcb = (pcb_t) zalloc(pcb_zone);
	if (pcb == 0)
		panic("pcb_init");

	counter(if (++c_threads_current > c_threads_max)
			c_threads_max = c_threads_current);

	/*
	 *	We can't let random values leak out to the user.
	 */
	bzero((char *) pcb, sizeof *pcb);

	/*
	 *	Guarantee that the bootstrapped thread will be in user
	 *	mode.
	 */
	pcb->vss.psl = PSL_CURMOD|PSL_PRVMOD;

	thread->pcb = pcb;
}

void pcb_terminate(thread)
	register thread_t	thread;
{
	register pcb_t		pcb = thread->pcb;

	counter(if (--c_threads_current < c_threads_min)
			c_threads_min = c_threads_current);

	zfree(pcb_zone, (vm_offset_t) pcb);
	thread->pcb = 0;
}

/*
 *	pcb_collect:
 *
 *	Attempt to free excess pcb memory.
 */

void pcb_collect(thread)
	thread_t thread;
{
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

	if (flavor != VAX_THREAD_STATE ||
		count < VAX_THREAD_STATE_COUNT) {
	    return(KERN_INVALID_ARGUMENT);
			/* invalid size structure */
	}

	state = (struct vax_thread_state *) tstate;
	saved_state = &thread->pcb->vss;

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
	if (thread == current_thread())
	    mtpr(USP, state->sp);
	else
	    thread->pcb->v_usp = state->sp;
	saved_state->pc = state->pc;

	/*
	 *	Carefully set PSL bits
	 */
	saved_state->psl = (state->ps | PSL_USERSET) & ~PSL_USERCLR;
	if (saved_state->psl & PSL_CM)
	    saved_state->psl &= ~ (PSL_FPD|PSL_DV|PSL_FU|PSL_IV);

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

	if (flavor == THREAD_STATE_FLAVOR_LIST) {
	    if (*count < 1) {
		return (KERN_INVALID_ARGUMENT);
	    }
	    tstate[0] = VAX_THREAD_STATE;
	    *count = 1;
	    return (KERN_SUCCESS);
	}

	if (flavor != VAX_THREAD_STATE ||
		*count < VAX_THREAD_STATE_COUNT) {
	    return(KERN_INVALID_ARGUMENT);
	}

	state = (struct vax_thread_state *) tstate;
	saved_state = &thread->pcb->vss;

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
	if (thread == current_thread())
	    state->sp = mfpr(USP);
	else
	    state->sp = thread->pcb->v_usp;
	state->pc = saved_state->pc;
	state->ps = saved_state->psl;

	*count = VAX_THREAD_STATE_COUNT;
	return(KERN_SUCCESS);
}

/*
 * Alter the thread`s state so that a following thread_exception_return
 * will make the thread return 'retval' from a syscall.
 */
void
thread_set_syscall_return(thread, retval)
	thread_t	thread;
	kern_return_t	retval;
{
	thread->pcb->vss.r0 = retval;
}

/*
 * Return prefered address of user stack.
 * Always returns low address.  If stack grows up,
 * the stack grows away from this address;
 * if stack grows down, the stack grows towards this
 * address.
 */
vm_offset_t
user_stack_low(stack_size)
	vm_size_t	stack_size;
{
	return (VM_MAX_ADDRESS - stack_size);
}

/*
 * Allocate argument area and set registers for first user thread.
 */
vm_offset_t
set_user_regs(stack_base, stack_size, entry, arg_size)
	vm_offset_t	stack_base;	/* low address */
	vm_offset_t	stack_size;
	int		*entry;
	vm_size_t	arg_size;
{
	vm_offset_t	arg_addr;

	arg_size = (arg_size + sizeof(int) - 1) & ~(sizeof(int)-1);
	arg_addr = stack_base + stack_size - arg_size;

	current_thread()->pcb->vss.pc = entry[0] + 2;	/* skip mask */
	mtpr(USP, (int)arg_addr);

	return (arg_addr);
}
