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
 * $Log:	trap.c,v $
 * Revision 2.11  89/03/09  22:22:07  rpd
 * 	More cleanup.
 * 
 * Revision 2.10  89/02/26  10:48:53  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.9  89/01/18  01:21:12  jsb
 * 	Vnode support: changed EREMOTE to ERFSREMOTE.
 * 	[89/01/16  15:27:41  jsb]
 * 
 * Revision 2.8  88/12/19  02:55:25  mwyoung
 * 	Remove old MACH conditionals.
 * 	[88/12/14            mwyoung]
 * 
 * Revision 2.7  88/10/18  03:41:50  mwyoung
 * 	Check for thread halt after user page fault.
 * 	[88/09/16            mwyoung]
 * 
 * Revision 2.6  88/08/22  21:32:50  mja
 * 	Don't clear resource pause notify flag on entry into system
 * 	call; add EDQUOT case to the fspause() check temporarily until
 * 	the two cases are better distinguished; collapse conditionals.
 * 	[88/08/08  18:00:11  mja]
 * 
 * Revision 2.5  88/08/10  10:37:30  rvb
 * *** empty log message ***
 * 
 * Revision ?????
 * For kernel_only tasks, try faults first on the task's map, then
 * the kernel_map (only after failure).  Avoids contention on the
 * kernel_map locks (and possible deadlock in the inode_pager under
 * MACH_XP).
 * 
 * 20-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Try to boot user from master, if there are idle slaves.
 *
 * 11-Apr-88  David Golub (dbg) at Carnegie-Mellon University
 *	Make work for MACH-only processes (no proc structure).
 *
 * 29-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Forgot about user-mode KDB trap.  Don't let it raise an
 *	exception.
 *
 * 24-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Implemented MACH exception handling.
 *
 * 21-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Check for thread-exit conditions in more places by using new
 *	macros.
 *
 *  7-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Check for abnormal thread exit conditions.
 *
 * 26-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Enable syscall's switch to master/slave only for multiple CPUS.
 *	Fix include file conventions.  Removed MACH_VM code for handling
 *	traps that aren't signaled by locore (PROTFLT, SEGFLT, TABLEFLT).
 *
 * 16-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 * 16-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Another NCPUS > 1 conditional around unix_lock.
 *	[ V5.1(XF19) ]
 *
 * 10-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Install fix from Bob Baron to conditionalize unix_lock
 *	manipulations on NCPUS > 1.
 *	[ V5.1(XF18) ]
 *
 *  5-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Corrected use of FAULT_ERROR when setting the recovery address.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 01-Oct-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Copyin/Copyout do not use THREAD_RECOVER - fault handler notices if
 *	they were executing based on PC and goes to proper recovery address.
 *
 * 26-Sep-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed unix_master calls from code that could never
 *	be executed (old BSD VM code).
 *
 * 25-Sep-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Fix SIGCLEANUP wrt. unix_master.
 *
 * 11-Sep-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	MUST do unix_master to guarantee that  "unix kernel"
 *	operations are locked.  First step in parallelizing
 *	the kernel.
 *	Unix_master() calls must be bracketed with unix_release().
 *	TT locking around addupc.
 *
 * 20-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TT: Added thread exception checks in trap() and syscall().
 *	Removed ACALLpsig(), as it is no longer used.
 *
 * 12-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Don't do thread locking when setting the whichq field in
 *	syscall.  This should be safe since we are running and no one
 *	will touch this field.
 *
 * 12-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Eliminate most of the direct u-area references in syscall to
 *	keep reasonable system call overhead.
 *
 * 29-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	No longer handle fork/vfork here under MACH_TT.
 *
 * 17-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fix console system call trace to terminate lines properly and
 *	added process ID stamp as well as provision to trace only a
 *	specific process.  This mode is probably useful less often than
 *	the XPR_DEBUG version but at least now it works.  Also, fixed
 *	some minor conditional compilation problems with XPR hooks.
 *	VICE:  Fixed bug which neglected to reset code at end of system
 *	call.
 *	[ V5.1(F7) ]
 *
 * 12-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	sys/syscalls.c -> bsd/syscalls.c
 *
 *  9-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Use thread_bind to temporarily bind a thread onto the master CPU
 *	to execute a non-parallel system call.  The old thread_force
 *	routine didn't allow for MACH routines that would allow a thread
 *	to migrate onto a slave processor.
 *
 *  1-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Updated for real thread implementation.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged in my support for real thread implementation.
 *
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: Added new required parameter to fspause().
 *	[ V5.1(F1) ]
 *
 * 28-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for NEW_SCHED.
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 15-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Call thread_start with "usermode" parameter.
 *
 * 30-Sep-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make fork and vfork work when MACH_TT is turned on.
 *
 *  6-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Did the generalization to allow any kernel submap to take faults.
 *
 * 23-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Forced include of "param.h" to find "../h" version.
 *
 * 29-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Allow kernel page faults on user_pt_map.
 *
 * 25-Jun-86  David Golub (dbg) at Carnegie-Mellon University
 *	Updated trap name table for MACH_VM traps.
 *
 *  3-Jun-86  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Fixed ACALLpsig to switch to master CPU and call psig when a
 *	signal has occurred in an ACALL.
 *
 *  2-Jun-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Cause a bad fault to generate a SIGSEGV instead of a SIGBUS.
 *	The Bourne shell actually depends on this!
 *
 * 25-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to new virtual memory code.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 03-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Changed system call execution to detect
 *	temporary resource exhaustion errors and enter resource pauses
 *	when appropriate.
 *	[V1(1)]
 *	
 * 26-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Added support for local system calls using
 *	negative indices into the sysent[] table.
 *
 * 18-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS_RFS:  Changed system call execution to set u_syscode
 *	field in U area and interpret the special EREMOTE error on
 *	return.
 *
 * 22-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS_KDB:  Changed to forward all unexpected traps to the
 *	kernel debugger.
 *
 * 15-Nov-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Add ACALLpsig() to avoid having so much trash in locore.s
 *	The routine checks for whether to psig or not.
 *
 * 25-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)trap.c	7.1 (Berkeley) 6/5/86
 */
 
#include <mach_kdb.h>
#include <mach_rfs.h>
#include <vice.h>

#include <vax/psl.h>
#include <vax/reg.h>
#include <vax/pte.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <vax/trap.h>
#include <sys/acct.h>
#include <sys/kernel.h>
#if	MACH_RFS
#ifndef	SYSCALLTRACE
#define SYSCALLTRACE
#endif	SYSCALLTRACE
#endif	MACH_RFS
#ifdef	SYSCALLTRACE
#include <bsd/syscalls.c>
#endif

#include <vax/mtpr.h>
#include <vax/cpu.h>

#include <kern/xpr.h>
#include <kern/thread.h>
#include <kern/parallel.h>
#include <mach/thread_status.h>
#include <kern/task.h>
#include <vm/vm_kern.h>
#include <vm/vm_map.h>
#include <mach/vm_param.h>
#include <mach/kern_return.h>
#include <kern/sched_prim.h>
#include <mach/exception.h>
#include <builtin/ux_exception.h>
#define USER	040		/* user-mode flag added to type */

extern struct	sysent	cmusysent[];
extern int ncmusysent;
extern int nallsysent;
struct	sysent	sysent[];
int	nsysent;

char	*trap_type[] = {
	"Reserved addressing mode",
	"Privileged instruction",
	"Reserved operand",
	"Breakpoint",
	"Xfc trap",
	"Syscall trap",
	"Arithmetic fault",
	"Ast trap",
	"Segmentation fault",
	"Protection fault",
	"Trace trap",
	"Compatibility mode trap",
	"",
	"",
	"Read fault",
	"Write fault",
};

/*
 *  Need this accessible to the kernel debugger.
 */
int	TRAP_TYPES =	(sizeof trap_type / sizeof trap_type[0]);

/*
 *	Mach trap handler.  Called from locore when a processor trap
 *	occurs.
 */
/*ARGSUSED*/
trap(sp, type, code, pc, psl)
	int		sp, type;
	unsigned	code;
	int		pc, psl;
{
	register int	*locr0 = ((int *)&psl) - PS;

	register struct proc *p;
	struct timeval	syst;

	vm_map_t	map;
	kern_return_t	result;

	int	exc_type, exc_code, exc_subcode;

	int	save_error;

	if (!USERMODE(locr0[PS])) {
	    /*
	     *	Trap in system mode.  Only page-faults are valid,
	     *	and then only in special circumstances.
	     */

	    switch (type) {
		case T_READ_FAULT:
		case T_WRITE_FAULT:
		    if (current_thread() != THREAD_NULL) {
			save_error = u.u_error;
			u.u_error = 0;
		    }
		    if ( ((vm_offset_t) code >= VM_MIN_KERNEL_ADDRESS) &&
		         (!current_thread()->task->kernel_vm_space))
			map = kernel_map;
		    else
			map = current_thread()->task->map;

		    result = vm_fault(map,
				trunc_page((vm_offset_t)code),
				(type == T_READ_FAULT)
				    ? VM_PROT_READ
				    : VM_PROT_READ|VM_PROT_WRITE,
				FALSE);

		    if ((result != KERN_SUCCESS) &&
		        ((vm_offset_t) code >= VM_MIN_KERNEL_ADDRESS)) {
		    		result = vm_fault(kernel_map,
					trunc_page((vm_offset_t)code),
					(type == T_READ_FAULT)
					    ? VM_PROT_READ
					    : VM_PROT_READ|VM_PROT_WRITE,
					FALSE);
		    }
		    if (current_thread() != THREAD_NULL) {
			u.u_error = save_error;
		    }

		    if (result == KERN_SUCCESS) {
			return;
		    }

#if	MACH_KDB
		    {
			extern int kdbtrapok;
			if (kdbtrapok) {
			    (void) kdb_trap(&psl);
			    return;
			}
		    }
#endif	MACH_KDB
		    {
			extern int	ALLOW_FAULT_START,
					ALLOW_FAULT_END,
					FAULT_ERROR;

			vm_offset_t	recover;

			recover = current_thread()->recover;
			if (recover == (vm_offset_t)0) {
			    if ((vm_offset_t)pc >
			        (vm_offset_t)&ALLOW_FAULT_START
			     && (vm_offset_t)pc <
				(vm_offset_t)&ALLOW_FAULT_END) {

				recover = (vm_offset_t) &FAULT_ERROR;
			    }
			}
			if (recover != (vm_offset_t)0) {
			    locr0[PS] &= ~PSL_FPD;
			    locr0[PC] = (int)recover;
			    return;
			}
		    }
		    /* Unanticipated page-fault errors in kernel
		       should not happen. */
		    /* fall through */

		default:
#if	MACH_KDB
		    if (kdb_trap(&psl))
			return;
#endif	MACH_KDB
		    printf("trap type %d, code = %x, pc = %x\n",
			   type, code, pc);
		    if ((unsigned) type < TRAP_TYPES)
			panic(trap_type[type]);
		    else
			panic("trap");
		    return;
	    }
	}

	/*
	 *	Trap from user mode.
	 */

	type |= USER;
	p = u.u_procp;

	if (p) {
	    syst = u.u_ru.ru_stime;
	    u.u_ar0 = locr0;
	}

	exc_code = 0;
	exc_subcode = 0;

	switch (type) {
	    case T_PRIVINFLT|USER:
		exc_type = EXC_BAD_INSTRUCTION;
		exc_code = EXC_VAX_PRIVINST;
		break;

	    case T_RESADFLT|USER:
		exc_type = EXC_BAD_INSTRUCTION;
		exc_code = EXC_VAX_RESADDR;
		break;

	    case T_RESOPFLT|USER:
		exc_type = EXC_BAD_INSTRUCTION;
		exc_code = EXC_VAX_RESOPND;
		break;
	
	    case T_ASTFLT|USER:
		astoff();
		if (p) {
		    if ((p->p_flag & SOWEUPC) && u.u_prof.pr_scale) {
			addupc(pc, &u.u_prof, 1);
			p->p_flag &= ~SOWEUPC;
		    }
		}
		goto out;

	    case T_ARITHTRAP|USER:
		if (code == EXC_VAX_SUB_RNG)
		    exc_type = EXC_SOFTWARE;
		else
		    exc_type = EXC_ARITHMETIC;
		exc_code = code;
		break;

	    case T_READ_FAULT|USER:
	    case T_WRITE_FAULT|USER:

		save_error = u.u_error;
		u.u_error = 0;		/*XXX*/

		map = current_thread()->task->map;
		result = vm_fault(map,
				trunc_page((vm_offset_t)code),
				(type == (T_READ_FAULT|USER))
				    ? VM_PROT_READ
				    : VM_PROT_READ|VM_PROT_WRITE,
				FALSE);
		u.u_error = save_error;		/*XXX*/

		while (thread_should_halt())
			thread_halt_self();

		if (result == KERN_SUCCESS) {
		    return;
		}
		exc_type = EXC_BAD_ACCESS;
		exc_code = result;
		exc_subcode = code;
		break;

	    case T_BPTFLT|USER:
		exc_type = EXC_BREAKPOINT;
		exc_code = EXC_VAX_BPT;
		psl &= ~PSL_T;
		break;

	    case T_TRCTRAP|USER:
		exc_type = EXC_BREAKPOINT;
		exc_code = EXC_VAX_TRACE;
		psl &= ~PSL_T;
		break;

	    case T_XFCFLT|USER:
		exc_type = EXC_EMULATION;
		break;
		

	    case T_COMPATFLT|USER:
		u.u_acflag |= ACOMPAT;
		exc_type = EXC_BAD_INSTRUCTION;
		exc_code = EXC_VAX_COMPAT;
		exc_subcode = code;
		break;

	    default:
#if	MACH_KDB
		(void) kdb_trap(&psl);
#endif	MACH_KDB
		return;
	}
	thread_doexception(current_thread(),
			   exc_type, exc_code, exc_subcode);

    out:
	if (p) {
	    if (CHECK_SIGNALS(p, current_thread()->u_address.uthread)) {
		unix_master();
		if (p->p_cursig || issig())
		    psig();
		unix_release();
	    }
	}

	while (thread_should_halt())
	    thread_halt_self();

	if (runrun[cpu_number()] && csw_check()) {
	    (void) splhigh();
	    runrun[cpu_number()] = 0;
	    u.u_ru.ru_nivcsw++;
	    thread_block();
	}

	if (u.u_prof.pr_scale) {
	    int	ticks;
	    struct timeval *tv = &u.u_ru.ru_stime;

	    ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
	    if (ticks)
		addupc(locr0[PC], &u.u_prof, ticks);
	}
}

#ifdef	SYSCALLTRACE
int syscalltrace = 0;
#endif
/*
 * Called from the trap handler when a system call occurs
 */
/*ARGSUSED*/
syscall(sp, type, code, pc, psl)
	short code;
{
	register int *locr0 = ((int *)&psl)-PS;
	register caddr_t params;		/* known to be r10 below */
	register int i;				/* known to be r9 below */
	register int	error;
	register struct uthread	*uthread;
	thread_t	t = current_thread();
	register struct sysent *callp = &sysent[20];/* known to be getpid */
	register struct proc *p;
	int opc;
	struct timeval syst;
	short	syscode;

	syst = u.u_ru.ru_stime;
	/*
	 *	If this is a MACH-only thread, we cannot do U*X system
	 *	calls.
	 */
	if (u.u_procp == (struct proc *)0) {
	    thread_doexception(current_thread(), EXC_SOFTWARE,
		EXC_UNIX_BAD_SYSCALL, 0);	/* XXX */
	    return;
	}
	uthread = t->u_address.uthread;
	if (!USERMODE(locr0[PS]))
		panic("syscall");
	uthread->uu_ar0 = locr0;
	if (code == 139) {			/* XXX 4.2 COMPATIBILITY */
#if	NCPUS > 1
		unix_master();
#endif	NCPUS > 1
		osigcleanup();			/* XXX 4.2 COMPATIBILITY */
		goto done;			/* XXX 4.2 COMPATIBILITY */
	}					/* XXX 4.2 COMPATIBILITY */
	params = (caddr_t)locr0[AP] + NBPW;
	u.u_error = 0;
	opc = pc - 2;
	if ((u_short)code > 63)
		opc -= 2;
	callp = ((u_short)(code+ncmusysent) >= nallsysent) ? &sysent[63] : &sysent[code];
	if (callp == sysent) {
		i = fuword(params);
		params += NBPW;
		callp = ((u_short)(i+ncmusysent) >= nallsysent) ? &sysent[63] : &sysent[i];
		syscode = i;
	}
	else
		syscode = code;
	if ((i = callp->sy_narg * sizeof (int)) &&
	    (error = copyin(params, (caddr_t)uthread->uu_arg, (u_int)i)) != 0) {
		locr0[R0] = error;
		locr0[PS] |= PSL_C;	/* carry bit */
		goto done;
	}
	uthread->uu_r.r_val1 = 0;
	uthread->uu_r.r_val2 = locr0[R1];
#if	NCPUS > 1
	if (callp->sy_parallel == 0) {
		/*
		 *	System call must execute on master cpu
		 */
		if (t->unix_lock != -1)
			panic("syscall,unix_master(): unix_lock != -1");
		unix_master();				/* hold to master during syscall */
	}
#endif	NCPUS > 1
	if (setjmp(&uthread->uu_qsave)) {
		unix_reset();
		if (error == 0 && uthread->uu_eosys != RESTARTSYS)
			error = EINTR;
	} else {
		uthread->uu_eosys = NORMALRETURN;
#ifdef	SYSCALLTRACE
		if (syscalltrace && 
		    (syscalltrace == u.u_procp->p_pid || syscalltrace < 0)) {
#define i	ii
			register int i;
			char *cp;

			if (((u_short)(syscode+ncmusysent) >= nallsysent) ||
					(syscode < 0))
				printf("[%d]0x%x", u.u_procp->p_pid,syscode);
			else
				printf("[%d]%s", u.u_procp->p_pid,syscallnames[syscode]);
			cp = "(";
			for (i= 0; i < callp->sy_narg; i++) {
				printf("%s%x", cp, u.u_arg[i]);
				cp = ", ";
			}
 			if (i)
				cp = ")";
			else
				cp = "";
			printf("%s\n", cp);
#undef	i
		}
#endif
		XPR(XPR_SYSCALLS, ("syscall start: %c%c%c%c%c%c\n",
			u.u_comm[0], u.u_comm[1], u.u_comm[2],
			u.u_comm[3], u.u_comm[4], u.u_comm[5]));
		XPR(XPR_SYSCALLS, 
		("syscall start %d: args=0x%x, 0x%x, 0x%x, 0x%x\n", 
			code, u.u_arg[0], u.u_arg[1], u.u_arg[2],
			u.u_arg[3], u.u_arg[4]));
#if	MACH_RFS
		/*
		 *  Remember the system call we are executing so that it
		 *  can be handled remotely if need be.
		 */
		uthread->uu_rfsncnt = 0;
		uthread->uu_rfscode = code;
#endif	MACH_RFS
#if	VICE
		uthread->uu_rmt_ncnt = 0;
		uthread->uu_rmt_code = code;
#endif	VICE
		/*
		 *  Show no resource pause conditions (except for a possible
		 *  polled pause in the process of being retried).
		 */
		uthread->uu_rpswhich &= URPW_NOTIFY;
		uthread->uu_rpsfs = 0;
		(*(callp->sy_call))();
		error = uthread->uu_error;
	}
#if	MACH_RFS
	/*
	 *  The special error number ERFSREMOTE is used by the remote system
	 *  call facility to short-circuit standard system call processing when
	 *  the equivalent has already been done remotely.  It serves simply to
	 *  unwind the call stack back to this point when the call has actually
	 *  been completed successfully.  It is not an error and should not be
	 *  relected back to the user process.
	 *
	 *  Also, clear the system call code value to indicate that we are no
	 *  longer in a system call.  I don't think this is actually necessary
	 *  since any calls on namei() will probably have to have come through
	 *  a system call and remote processing must have been specifically
	 *  enabled by the caller of namei().  Nevertheless, namei() will still
	 *  check this value before actually making a remote call and it nevers
	 *  hurts to be safe.
	 */
	if (error == ERFSREMOTE)
		error = 0;
	uthread->uu_rfscode = 0;
#endif	MACH_RFS
#if	VICE
	if (error == EVICEOP)
		error = 0;
	uthread->uu_rmt_code = 0;
#endif	VICE
	if (error) switch (error)
	{
	    case EDQUOT:	/* temp == ENOSPC */
	    case ENOSPC:
	    {
		/*
		 *  The error number ENOSPC indicates disk block or inode
		 *  exhaustion on a file system.  When this occurs during a
		 *  system call, the fsfull() routine will record the file
		 *  system pointer and type of failure (1=disk block, 2=inode)
		 *  in the U area.  If we return from a system call with this
		 *  error set, invoke the fspause() routine to determine
		 *  whether or not to enter a resource pause.  It will check
		 *  that the resource pause fields have been set in the U area
		 *  (then clearing them) and that the process has enabled such
		 *  waits before clearing the error number and pausing.  If a
		 *  signal occurs during the sleep, we will return with a false
		 *  value and the error number set back to ENOSPC.  If the wait
		 *  completes successfully, we return here with a true value.
		 *  In this case, we simply restart the current system call to
		 *  retry the operation.
		 *
		 *  Note:  Certain system calls can not be restarted this
		 *  easily since they may partially complete before running
		 *  into a resource problem.  At the moment, the read() and
		 *  write() calls and their variants have this characteristic
		 *  when performing multiple block operations.  Thus, the
		 *  resource exhaustion processing for these calls must be
		 *  handled directly within the system calls themselves.  When
		 *  they return to this point (even with ENOSPC set), the
		 *  resource pause fields in the U area will have been cleared
		 *  by their previous calls on fspause() and no action will be
		 *  taken here.
		 */
		if (fspause(0))
		    u.u_eosys = RESTARTSYS;
		break;
	    }
	    /*
	     *  TODO:  Handle these error numbers, also.
	     */
	    case EAGAIN:
	    case ENOMEM:
	    case ENFILE:
		break;
	}
	if (uthread->uu_eosys == NORMALRETURN) {
		if (error) {
			locr0[R0] = error;
			locr0[PS] |= PSL_C;	/* carry bit */
		} else {
			locr0[R0] = uthread->uu_r.r_val1;
			locr0[R1] = uthread->uu_r.r_val2;
			locr0[PS] &= ~PSL_C;
		}
	} else if (uthread->uu_eosys == RESTARTSYS)
		pc = opc;
	/* else if (u.u_eosys == JUSTRETURN) */
		/* nothing to do */
done:
	uthread->uu_error = error;
	p = u.u_procp;
	XPR(XPR_SYSCALLS, 
		("syscall end: pid=%d, code=%d, rval1=%d, rval2=%d\n",
		u.u_procp->p_pid, code, u.u_r.r_val1, u.u_r.r_val2));
	if (CHECK_SIGNALS(p, uthread)) {
		unix_master();
		if (p->p_cursig || issig())
			psig();
		unix_release();
	}
#if	NCPUS > 1
	/*
	 *	It is OK to go back on a slave
	 */
	if (code == 139 || callp->sy_parallel == 0) { /***/

		unix_release();
		if (t->unix_lock != -1) {
			printf("syscall<%d>: released unix_lock D%d\n",
				u.u_procp-proc, t->unix_lock);
			panic("syscall: unix_lock != -1");
		}
	}
#endif	NCPUS > 1
	while (thread_should_halt())
		thread_halt_self();

	if (runrun[cpu_number()] && csw_check()) {
		(void) splhigh();
		u.u_ru.ru_nivcsw++;
		runrun[cpu_number()] = 0;
		thread_block();
	}
#if	NCPUS > 1
	else 
	if ((cpu_number() == master_cpu) && (idle_count > 0)) {
		(void) splsched();
		thread_block();
	}
#endif	NCPUS > 1
	if (u.u_prof.pr_scale) {
		int ticks;
		struct timeval *tv = &u.u_ru.ru_stime;

		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks)
		{
			simple_lock(&u.u_prof.pr_lock);
			addupc(locr0[PC], &u.u_prof, ticks);
			simple_unlock(&u.u_prof.pr_lock);
		}
	}
}

/*
 * nonexistent system call-- signal process (may want to handle it)
 * flag error if process won't see signal immediately
 * Q: should we do that all the time ??
 */
nosys()
{
/*	uprintf("BAD SYSCALL: %s proc[%d] pid = %d, #%d\n",
		u.u_comm, u.u_procp-proc, u.u_procp->p_pid, u.u_ar0[-3]); /* XXX */

	if (u.u_signal[SIGSYS] == SIG_IGN || u.u_signal[SIGSYS] == SIG_HOLD)
		u.u_error = EINVAL;
	thread_doexception(current_thread(), EXC_SOFTWARE,
		EXC_UNIX_BAD_SYSCALL, 0);
}
