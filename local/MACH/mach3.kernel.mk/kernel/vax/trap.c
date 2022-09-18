/* 
 * Mach Operating System
 * Copyright (c) 1993,1990,1989,1988 Carnegie Mellon University
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
 * HISTORY
 * $Log:	trap.c,v $
 * Revision 2.9  93/02/01  09:52:17  danner
 * 	Added bcopy and bzero fro routines that couldn't find it from
 * 	 inline.
 * 	[93/01/26            danner]
 * 
 * Revision 2.8  91/05/14  17:46:21  mrt
 * 	Correcting copyright
 * 
 * Revision 2.7  91/05/08  13:28:02  dbg
 * 	Add stack switching support.
 * 	Add user_page_fault_continue.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.6  91/03/16  15:02:48  rpd
 * 	Hacked for AST interface changes.
 * 	[91/03/15            rpd]
 * 
 * 	Added resume, continuation arguments to vm_fault.
 * 	[91/03/13            rpd]
 * 
 * Revision 2.5  91/01/08  16:42:30  rpd
 * 	Added KEEP_STACKS support.
 * 	[91/01/07            rpd]
 * 	Added continuation argument to thread_block.
 * 	[90/12/08            rpd]
 * 
 * Revision 2.4  90/10/25  14:49:17  rwd
 * 	Added watchpoint support.
 * 	[90/10/18            rpd]
 * 
 * Revision 2.3  90/06/02  15:08:53  rpd
 * 	Updated to new csw_needed macro.
 * 	[90/03/26  23:05:45  rpd]
 * 
 * Revision 2.2  89/09/08  11:28:00  dbg
 * 	On page fault in kernel mode: if the current task's map is a
 * 	submap of the kernel and the address falls within it, try it
 * 	first.  Avoids deadlock (on the kernel map) with other kernel
 * 	tasks.
 * 	[89/07/25            dbg]
 * 
 * 27-Apr-89  David Golub (dbg) at Carnegie-Mellon University
 *	Made compile without KDB. (Fix from rfr)
 *
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 * Hardware trap/fault handler.
 */

#include <cpus.h>
#include <mach_pcsample.h>
#include <mach_kdb.h>

#include <vax/psl.h>
#include <vax/trap.h>
#include <vax/mtpr.h>

#include <mach/exception.h>
#include <mach/kern_return.h>
#include <mach/vm_param.h>

#include <vm/vm_kern.h>
#include <vm/vm_map.h>

#include <kern/thread.h>
#include <kern/task.h>
#include <kern/sched.h>
#include <kern/sched_prim.h>

#if	MACH_KDB
boolean_t	debug_all_traps_with_kdb = FALSE;
extern struct db_watchpoint *db_watchpoint_list;
extern boolean_t db_watchpoints_inserted;

void
thread_kdb_return()
{
	register thread_t thread = current_thread();
	register struct vax_saved_state *regs = &thread->pcb->vss;

	if (kdb_trap(regs)) {
		thread_exception_return();
		/*NOTREACHED*/
	}
}
#endif	MACH_KDB

/*
 * Fault recovery in copyin/copyout routines.
 */
struct recovery {
	int	fault_addr;
	int	recover_addr;
};

extern struct recovery	recover_table[];
extern struct recovery	recover_table_end[];

void
kernel_trap(regs)
	struct vax_saved_state *regs;
{
	register thread_t	thread = current_thread();

	/*
	 * Trap in system mode.  Only page-faults are valid,
	 * and then only in special circumstances.
	 */

	switch (regs->exception) {
	    case EXC_BAD_ACCESS:
	    {
		register vm_map_t	map;
		register vm_offset_t	address = (vm_offset_t) regs->subcode;
		kern_return_t		result;

		/*
		 * If the current map is a submap of the kernel map,
		 * and the address is within that map, fault on that
		 * map.  If the same check is done in vm_fault
		 * (vm_map_lookup), we may deadlock on the kernel map
		 * lock.
		 */
		if (thread == THREAD_NULL)
		    map = kernel_map;
		else {
		    map = thread->task->map;
		    if (address < vm_map_min(map) ||
			address >= vm_map_max(map))
			map = kernel_map;
		}

		result = vm_fault(map,
				  trunc_page(address),
				  regs->code,
				  FALSE,
				  FALSE,
				  (void (*)()) 0);
		if (result == KERN_SUCCESS) {
#if	MACH_KDB
		    if (db_watchpoint_list &&
			db_watchpoints_inserted &&
			(regs->code & VM_PROT_WRITE) &&
			db_find_watchpoint(map, address, regs))
		    {
			regs->exception = T_WATCHPOINT;
			kdb_trap(regs);
		    }
#endif	MACH_KDB
		    return;
		}
	    }
	    {
		register struct recovery *rp;

		for (rp = recover_table;
		     rp < recover_table_end;
		     rp++) {
		    if (regs->pc == rp->fault_addr) {
			regs->pc = rp->recover_addr;
			regs->psl &= ~PSL_FPD;
			return;
		    }
		}
	    }
		/*
		 * Unanticipated page-fault errors in kernel
		 * should not happen.
		 */
		/* fall through */

	    default:
#if	MACH_KDB
		if (kdb_trap(regs))
		    return;
#endif	MACH_KDB
		panic("trap type %d, code = %x, pc = %x\n",
			   regs->exception,
			   regs->code,
			   regs->pc);
		return;
	}
}

void	user_page_fault_continue();	/* forward */

void
user_trap(regs)
	register struct vax_saved_state *regs;
{
	register thread_t	thread = current_thread();
	register kern_return_t	result;

	/*
	 *	Trap from user mode.
	 */

	switch (regs->exception) {
	    case T_KDB_ENTRY:
#if	MACH_KDB
		(void) kdb_trap(regs);
#endif	MACH_KDB
		return;

	    case EXC_BAD_ACCESS:
		result = vm_fault(thread->task->map,
				trunc_page((vm_offset_t)regs->subcode),
				regs->code,
				FALSE,
				FALSE,
				user_page_fault_continue);
		/*NOTREACHED*/
		break;

	    case EXC_ARITHMETIC:
		regs->code = regs->subcode;
		regs->subcode = 0;
		if (regs->code == EXC_VAX_SUB_RNG)
		    regs->exception = EXC_SOFTWARE;
		break;

	    case EXC_BREAKPOINT:
		regs->psl &= ~PSL_T;
		break;

	}

#if	MACH_KDB
	if (debug_all_traps_with_kdb)
	    (void) kdb_trap(regs);
	else
#endif	MACH_KDB
	exception(regs->exception, regs->code, regs->subcode);
	/*NOTREACHED*/
}

void
user_page_fault_continue(kr)
	kern_return_t kr;
{
	register thread_t thread = current_thread();
	register struct vax_saved_state *regs;

	regs = &thread->pcb->vss;

	if (kr == KERN_SUCCESS) {
#if	MACH_KDB
		if (db_watchpoint_list &&
		    db_watchpoints_inserted &&
		    (regs->code & VM_PROT_WRITE) &&
		    db_find_watchpoint(
			thread->task->map,
		       (vm_offset_t)regs->subcode,
		       regs))
		{
		    regs->exception = T_WATCHPOINT;
		    kdb_trap(regs);
		}
#endif	MACH_KDB
		thread_exception_return();
		/*NOTREACHED*/
	}
	regs->code = kr;

#if	MACH_KDB
	if (debug_all_traps_with_kdb &&
	    kdb_trap(regs)) {
		thread_exception_return();
		/*NOTREACHED*/
	}
#endif	MACH_KDB

	exception(regs->exception, regs->code, regs->subcode);
	/*NOTREACHED*/
}

#if     MACH_PCSAMPLE > 0
/*
 * return saved state for interrupted user thread
 */
unsigned interrupted_pc(thread_t t)
{
    struct vax_saved_state *frame = &t->pcb->vss;
    return (unsigned) frame->pc;
}
#endif  /* MACH_PCSAMPLE > 0*/

#undef bcopy
#undef bzero

bcopy(void *a,void *b,unsigned count)
{
  return _bcopy(a,b,count);
}

bzero(void *a, unsigned count)
{
  return _bzero(a,count);
}
