/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	trap.c,v $
 * Revision 1.11.1.18  91/03/29  16:24:15  rvb
 * 	In use_kdb code, do not play with fp state.
 * 	[91/03/29            rvb]
 * 
 * Revision 1.11.1.17  91/03/28  08:44:41  rvb
 * 	For X134:
 * 		ux_exception.h now in sys vs builtin.
 * 			Only check for termination in response to an AST.
 * 	 	Macro changes - csw_needed, CHECK_SIGNALS.
 * 			Last two from [89/02/02            dlb]
 * 
 * Revision 1.11.1.16  91/01/30  14:35:10  rvb
 * 		Add 3.0 v86_hdw_assist()
 * 	[91/01/30            rvb]
 * 
 * Revision 1.11.1.15  91/01/06  22:11:32  rvb
 * 	Split out trapv86() from trap().
 * 	[90/12/13            rvb]
 * 
 * Revision 1.11.1.14  90/11/27  16:27:41  rvb
 * 	BRB should be for both kernel and user mode traps.  Actually,
 * 	the kernel is the more obvious case.
 * 	[90/11/27            rvb]
 * 
 * Revision 1.11.1.13  90/11/27  13:40:35  rvb
 * 	Enable the Big Red Button.
 * 	[90/10/03            rvb]
 * 
 * Revision 1.11.1.12  90/09/18  08:33:14  rvb
 * 	Allow kernel to do fp iff NFP > 0.  fpsup/fpinit() wants
 * 	to initialize the fp state this causes the kernel to do
 * 	fp -- sigh.
 * 	[90/09/13            rvb]
 * 
 * 	USER T_{E,}NOEXTFLT's call fpnoextflt even if EFL_VM is on.
 * 	[90/09/12            rvb]
 * 
 * Revision 1.11.1.11  90/07/10  11:42:54  rvb
 * 	At least print pc iff its too early to trap to debugger.
 * 	[90/06/15            rvb]
 * 
 * Revision 1.11.1.10  90/06/07  08:04:38  rvb
 * 	use_kdb iff 1 means that T_SGLSTP and T_BRK for user tasks are
 * 	handled by the kernel.  Also some cleanup.
 * 	[90/06/06            rvb]
 * 
 * Revision 1.11.1.9  90/05/16  16:41:55  rvb
 * 	Call kdb(<flt>, ...) when in trouble
 * 
 * Revision 1.11.1.8  90/05/14  13:20:49  rvb
 * 	Bring kdb up to Mach 2.5 production quality. 
 * 	handle T_BPTFLT
 * 	[90/05/10            rvb]
 * 
 * 	Include kupfer's copy-on-reference code
 * 	[90/05/04            rvb]
 * 
 * Revision 1.22  90/05/01  21:29:08  kupfer
 * Implement copy-on-reference.
 * 
 * Revision 1.11.1.7  90/04/15  11:45:43  rvb
 * 	astintr() must check for user profil requests.
 * 	[90/04/13            rvb]
 * 
 * Revision 1.11.1.6  90/03/28  08:30:44  rvb
 * 	v86 changes: EFL_VM [grm]
 * 
 * Revision 1.11.1.5  90/02/28  15:48:38  rvb
 * 	Revision 1.18  90/02/26  17:54:48  kupfer
 * 	Synch with CMU.  h/w workarounds ifdef'd by h/w type.
 * 	Neetness counts.
 * 
 * Revision 1.11.1.4  90/02/01  13:34:20  rvb
 *	Allow user GP_FLT's as bad instruction
 *	fix MACH_KDB == 0
 *	try to handle kdb page faults gracefully
 *	[90/01/29            rvb]
 *   
 * Revision 1.11.1.3  89/12/21  17:49:55  rvb
 *	The kernel may not use floating point.
 *    
 * Revision 1.17  89/12/05  18:05:37  kupfer
 * Fix user page fault code to pass correct subcode to exception handler.
 * 
 * Revision 1.16  89/11/27  22:59:11  kupfer
 * Merge in recent CMU changes.
 * 
 * Revision 1.11.1.2  89/10/30  12:28:52  rvb
 * 	Revision 1.15  89/10/16  16:24:27  kupfer
 * 	Put back single-step fixes & minor cleanups (lost some formatting changes,
 * 	though).
 * 
 * 	Revision 1.14  89/09/27  16:01:53  kupfer
 * 	Get rid of debugging "Utrap" uprintf.
 * 
 * 	Revision 1.13  89/09/26  11:56:14  lance
 * 	X109 checkin
 * 
 * 	Revision 1.11.1.1  89/10/22  11:31:48  rvb
 * 	asm's for floating -> function calls.
 * 
 * 
 * Revision 1.11  89/09/25  15:43:39  rvb
 * 	Don't print pc on fault unless show_pc is on.
 * 	[89/09/25            rvb]
 * 
 * Revision 1.10  89/09/25  12:26:19  rvb
 * 	Changes by Lin for floating point support.
 * 	And fp.h -> fpreg.h
 * 	[89/09/23            rvb]
 * 
 * Revision 1.8  89/08/08  21:46:38  jsb
 * 	For now: have syscalltrace and SEGV's uprintf
 * 	[89/08/03            rvb]
 * 
 * Revision 1.7  89/07/17  10:38:35  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 		fp
 * 	[89/07/11            rvb]
 * 
 * Revision 1.6  89/04/05  12:59:52  rvb
 * 	Improved syscalltrace printout.
 * 	[89/03/30            rvb]
 * 
 * Revision 1.5  89/03/09  20:04:21  rpd
 * 	More cleanup.
 * 
 * Revision 1.4  89/02/26  12:34:44  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 * 29-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Forgot about user-mode KDB trap.  Don't let it raise an
 *	exception.
 *
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)trap.c	7.1 (Berkeley) 6/5/86
 */

#include <cpus.h>
#include <fp.h>

#include <mach_kdb.h>
#include <mach_rfs.h>
#include <vice.h>

#include <i386/psl.h>
#include <i386/reg.h>
#include <i386/debug.h>
#include <i386/pmap.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <i386/trap.h>
#include <i386/fpreg.h>
#include <sys/acct.h>
#include <sys/kernel.h>
#include <kern/xpr.h>
#if	MACH_RFS
#ifndef	SYSCALLTRACE
#define SYSCALLTRACE
#endif	SYSCALLTRACE
#endif	MACH_RFS

#undef	SYSCALLTRACE
#define SYSCALLTRACE
#ifdef	SYSCALLTRACE
#include <bsd/syscalls.c>
#endif

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
#ifdef	THREAD_EXIT
#include <builtin/ux_exception.h>
#else	THREAD_EXIT
#include <sys/ux_exception.h>
#endif	THREAD_EXIT

#define USER	040		/* user-mode flag added to type */

extern struct	sysent	cmusysent[];
extern int ncmusysent;
extern int nallsysent;
struct	sysent	sysent[];
int	nsysent;

#ifdef	SYSCALLTRACE
int syscalltrace = 0;
#endif

char	*trap_type[] = {
	"Divide error",
	"Debug trap",
	"NMI",
	"Breakpoint",
	"Overflow",
	"Bounds check",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"(reserved)",
	"Invalid TSS",
	"Segmentation",
	"Stack bounds",
	"General protection",
	"Page fault",
	"(reserved)",
	"Coprocessor error"
};

/*
 *  Need this accessible to the kernel debugger.
 */
int	TRAP_TYPES =	(sizeof trap_type / sizeof trap_type[0]);
int	show_pc = 0;
#if	MACH_KDB
extern int kdbactive;
extern int kdbtrapok;
extern int kdb_singlestep;
#endif	MACH_KDB

int use_kdb = 0;
int brb = 1;

/*
 *	Mach trap handler.  Called from locore when a processor trap
 *	occurs.
 */
/*ARGSUSED*/
trap(r0ptr)
	int *r0ptr;
{
	register int	*locr0 = r0ptr;
	register struct proc *p;
	struct timeval	syst;
	
	vm_map_t	map;
	vm_offset_t	va;
	kern_return_t	result;
	
	int	exc_type, exc_code, exc_subcode;
	
	int	save_error;
	int     type;
	int     code;
	int	s;
	u_int   pc;
	
	type = locr0[TRAPNO];
	code = locr0[ERR];
	pc = locr0[EIP];
	va = (vm_offset_t)_cr2();
	
#ifdef	SYSCALLTRACE
	if (syscalltrace < -1 || !(int)(current_thread()))
		printf("Ktrap: type %x, code %x, pc %x, ar0 %x, va %x\n",
			type, code, pc, locr0, va);
	if (!(int)(current_thread())) {
		int j;
		for (j = 0; j < 10000000; j++);
	}
#endif	SYSCALLTRACE

#define I386_UMODE	(USERMODE(locr0[CS]))
#if	MACH_KDB
	if (!I386_UMODE || kdbactive)
#else	MACH_KDB
	if (!I386_UMODE)
#endif	MACH_KDB
	{
	    /*
	     *	Trap in system mode.  Only page-faults are valid,
	     *	and then only in special circumstances.
	     */

	    switch (type) {
		case T_ENOEXTFLT:	/* software floating trap */
		case T_NOEXTFLT:
#if	NFP > 0
			fpnoextflt(locr0);
			return;
#endif	NFP > 0
	    	case T_EXTOVRFLT:
#ifdef	notdef
			fpextovrflt(locr0);
			return;
#endif	notdef
	    	case T_EXTERRFLT:
#if	NFP > 0
			fpexterrflt(locr0);
			return;
#endif	NFP > 0
			systemdebugtrap(type, locr0);
			panic("The kernel just tried to do a fp op.");
		case T_BPTFLT:
		case T_SGLSTP:
			systemdebugtrap(type, locr0);
			return;

		case T_NMIFLT:
			if (brb) {
				printf("BRB\n");
				systemdebugtrap(type, locr0);
				return;
			}
			goto die;			
		case T_PGFLT:
		case T_SEGNPFLT:
			if (current_thread() != THREAD_NULL) {
				save_error = u.u_error;
				u.u_error = 0;
			}
			if (va >= VM_MIN_KERNEL_ADDRESS) {
				map = kernel_map;
				result = kernel_fault_in(va, code);
			} else {
				map = current_thread()->task->map;
				result = vm_fault(map, trunc_page(va),
						  (code & I386_PTE_KRW)
						  ? VM_PROT_READ|VM_PROT_WRITE
						  : VM_PROT_READ,
						  FALSE);
			}
			if (current_thread() != THREAD_NULL)
				u.u_error = save_error;
			if (result == KERN_SUCCESS)
				return;
			{
				extern int	ALLOW_FAULT_START,
						ALLOW_FAULT_END,
						FAULT_ERROR;
				vm_offset_t	recover = current_thread()->recover;
				
#if	MACH_KDB
				if (kdbtrapok) {
					locr0[EIP] = (int)&FAULT_ERROR;
					return;
				} else
#endif	MACH_KDB

				if (recover == (vm_offset_t)0) {
					if ((vm_offset_t)pc >
					    (vm_offset_t)&ALLOW_FAULT_START
					    && ((vm_offset_t)pc <
						(vm_offset_t)&ALLOW_FAULT_END))
					{
						locr0[EIP] = (int)&FAULT_ERROR;
						return;
					}
				} else {
					/* ???	locr0[EFL] &= ~PSL_FPD; */
					locr0[EIP] = (int)recover;
					return;
				}
			}
			printf("kernel page fault: va = %x, err = %x\n", va,
			       code & 0x7);
			/* Unanticipated page-fault errors in kernel
			   should not happen. */
			/* fall through */
			
		default:
die:
#if	MACH_KDB
			kdb(type, r0ptr);
#else	MACH_KDB
			printf("trap type %d, code = %x, pc = %x, cr2 = %x\n",
			       type, code, pc, va);
#endif	MACH_KDB
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
	
	p = u.u_procp;
	
	if (p) {
		syst = u.u_ru.ru_stime;
		u.u_ar0 = locr0;
	}
	
	exc_code = 0;
	exc_subcode = 0;
	
	switch (type) {
	case T_SGLSTP:
		if (use_kdb) {
			systemdebugtrap(type, locr0);
			return;
		}
		exc_type = EXC_BREAKPOINT;
		exc_code = EXC_I386_SGL;
		break;

	case T_BPTFLT:
		if (use_kdb) {
			systemdebugtrap(type, locr0);
			return;
		}
		exc_type = EXC_BREAKPOINT;
		exc_code = EXC_I386_BPT;
		break;

	case T_STKFLT:
	case T_NMIFLT:
		if (brb) {
			printf("BRB\n");
			systemdebugtrap(type, locr0);
			return;
		}
	case T_DBLFLT:
	case T_INVTSSFLT:
		printf("USER trap type %d, code = %x, pc = %x\n",
		       type, code, pc);
		kdb(type, locr0);
		if ((unsigned) type < TRAP_TYPES)
			panic(trap_type[type]);
		else
			panic("trap");
		return;
		
	case T_GPFLT:
		uprintf("General Protection Fault: trap type %d, code = %x, pc = %x, cr2 = %x\n",
		       type, code, pc, va);
	case T_INVOPFLT:
		exc_type = EXC_BAD_INSTRUCTION;
		exc_code = EXC_I386_INVOP;
		break;

	case T_NOEXTFLT:
	case T_ENOEXTFLT:	/* software floating trap */
		fpnoextflt(locr0);
		goto out;

	case T_EXTOVRFLT:
		fpextovrflt(locr0);
		goto out;
		
	case T_PGFLT:
	case T_SEGNPFLT:
		save_error = u.u_error;
		u.u_error = 0;		/*XXX*/
		
		map = current_thread()->task->map;
		result = vm_fault(map, trunc_page(va), 
				  (code & I386_PTE_KRW)
				    ? VM_PROT_READ|VM_PROT_WRITE
				    : VM_PROT_READ,
				  FALSE);
		u.u_error = save_error;		/*XXX*/
		
		if (result == KERN_SUCCESS) {
			return;
		}
		exc_type = EXC_BAD_ACCESS;
		exc_code = result;
		exc_subcode = va;
		break;
		
	case T_INTOFLT:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_INTO;
		break;
		
	case T_BOUNDFLT:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_BOUND;
		break;
		
	case T_DIVERR:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_DIV;
		break;
		
	case T_EXTERRFLT:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_EXTERR;
		break;
		
	case T_ENDPERR:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_EMERR;
		break;
		
	default:
		printf("trap(user): unknown trap 0x%x\n", type);
#if	MACH_KDB
		kdb(type, r0ptr);
#endif	MACH_KDB
		return;
	}
	if (show_pc && bcmp(u.u_comm, "sh", 2))
		uprintf("Utrap: in %s type %x, code %x, pc %x, ar0 %x, va %x\n",
			u.u_comm, type, code, pc, locr0, va);
	thread_doexception(current_thread(),
			   exc_type, exc_code, exc_subcode);

    out:
	if (p) {
#ifdef	THREAD_EXIT
		if (CHECK_SIGNALS(p, current_thread()->u_address.uthread))
#else	THREAD_EXIT
		if (CHECK_SIGNALS(p, current_thread(),
				  current_thread()->u_address.uthread))
#endif	THREAD_EXIT
		{
			unix_master();
			if (p->p_cursig || issig()) {
				psig();
			}
			unix_release();
		}
	}
		
#ifdef	THREAD_EXIT
	while (thread_should_halt())
		thread_halt_self();

	if (runrun[cpu_number()] && csw_check()) {
		s = splhigh();
		runrun[cpu_number()] = 0;
		u.u_ru.ru_nivcsw++;
		thread_block();
		splx(s);
	}
#else	THREAD_EXIT
	if (csw_needed(current_thread(), current_processor())) {
	    u.u_ru.ru_nivcsw++;
	    thread_block();
	}
#endif	THREAD_EXIT
	if (u.u_prof.pr_scale) {
		int	ticks;
		struct timeval *tv = &u.u_ru.ru_stime;
			
		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			 (tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks)
			addupc(locr0[EIP], &u.u_prof, ticks);
	}
}

/*ARGSUSED*/
trapv86(r0ptr)
	int *r0ptr;
{
	register int	*locr0 = r0ptr;
	register struct proc *p;
	struct timeval	syst;
	
	vm_map_t	map;
	vm_offset_t	va;
	kern_return_t	result;
	
	int	exc_type, exc_code, exc_subcode;
	
	int	save_error;
	int     type;
	int     code;
	int	s;
	u_int   pc;
	
	type = locr0[TRAPNO];
	code = locr0[ERR];
	pc = locr0[EIP];
	va = (vm_offset_t)_cr2();
		
	exc_code = 0;
	exc_subcode = 0;
	
	switch (type) {
	case T_SGLSTP:
		if (use_kdb) {
			systemdebugtrap(type, locr0);
			return;
		}
		exc_type = EXC_BREAKPOINT;
		exc_code = EXC_I386_SGL;
		break;

	case T_BPTFLT:
		if (use_kdb) {
			systemdebugtrap(type, locr0);
			return;
		}
		exc_type = EXC_BREAKPOINT;
		exc_code = EXC_I386_BPT;
		break;

	case T_GPFLT:
	case T_INVOPFLT:
		if (v86_hdw_assist((struct i386_saved_state *) r0ptr))
			return;
		exc_type = EXC_BAD_INSTRUCTION;
		exc_code = EXC_I386_INVOP;
		break;

	case T_STKFLT:
		exc_type = EXC_BAD_INSTRUCTION;
		exc_code = EXC_I386_STKFLT;
		break;

	case T_INTOFLT:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_INTO;
		break;
		
	case T_BOUNDFLT:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_BOUND;
		break;
		
	case T_DIVERR:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_DIV;
		break;
		
	case T_EXTERRFLT:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_EXTERR;
		break;
		
	case T_ENDPERR:
		exc_type = EXC_ARITHMETIC;
		exc_code = EXC_I386_EMERR;
		break;
		
	case T_NOEXTFLT:
	case T_ENOEXTFLT:	/* software floating trap */
		fpnoextflt(locr0);
		goto out;

	case T_EXTOVRFLT:
		fpextovrflt(locr0);
		goto out;
		
	case T_PGFLT:
	case T_SEGNPFLT:
		save_error = u.u_error;
		u.u_error = 0;		/*XXX*/
		
		map = current_thread()->task->map;
		result = vm_fault(map, trunc_page(va), 
				  (code & I386_PTE_KRW)
				    ? VM_PROT_READ|VM_PROT_WRITE
				    : VM_PROT_READ,
				  FALSE);
		u.u_error = save_error;		/*XXX*/
		
		if (result == KERN_SUCCESS) {
			return;
		}
		exc_type = EXC_BAD_ACCESS;
		exc_code = result;
		exc_subcode = va;
		break;
		
	case T_NMIFLT:
		if (brb) {
			printf("BRB\n");
			systemdebugtrap(type, locr0);
			return;
		}
	case T_DBLFLT:
	case T_INVTSSFLT:
		printf("V86 trap type %d, code = %x, pc = %x\n",
		       type, code, pc);
		kdb(type, locr0);
		if ((unsigned) type < TRAP_TYPES)
			panic(trap_type[type]);
		else
			panic("trap");
		return;
		
	default:
		printf("trap(v86): unknown trap 0x%x\n", type);
#if	MACH_KDB
		kdb(type, r0ptr);
#endif	MACH_KDB
		return;
	}
	if (show_pc && bcmp(u.u_comm, "sh", 2))
		uprintf("V86 trap: in %s type %x, code %x, pc %x, ar0 %x, va %x\n",
			u.u_comm, type, code, pc, locr0, va);
	thread_doexception(current_thread(),
			   exc_type, exc_code, exc_subcode);

    out:
	p = u.u_procp;
	if (p) {
#ifdef	THREAD_EXIT
		if (CHECK_SIGNALS(p, current_thread()->u_address.uthread))
#else	THREAD_EXIT
		if (CHECK_SIGNALS(p, current_thread(),
				  current_thread()->u_address.uthread))
#endif	THREAD_EXIT
		{
			unix_master();
			if (p->p_cursig || issig()) {
				psig();
			}
			unix_release();
		}
	}
#ifdef	THREAD_EXIT
	while (thread_should_halt())
		thread_halt_self();

	if (runrun[cpu_number()] && csw_check()) {
		s = splhigh();
		runrun[cpu_number()] = 0;
		u.u_ru.ru_nivcsw++;
		thread_block();
		splx(s);
	}
#else	THREAD_EXIT
	if (csw_needed(current_thread(), current_processor())) {
	    u.u_ru.ru_nivcsw++;
	    thread_block();
	}
#endif	THREAD_EXIT
}

#undef	EFL_ALLCC	/* defined in i386/psl.h */
#define EFL_ALLCC (EFL_CF|EFL_PF|EFL_AF|EFL_ZF|EFL_SF)

#define	EFL_TSAFE \
(EFL_TF|EFL_CF|EFL_PF|EFL_AF|EFL_ZF|EFL_SF|EFL_ALLCC|EFL_DF|EFL_OF)

#define V8(r,i,p) (((r->i&0xffff)<<4)+(0xffff&r->p))
#define ADDR8(i,p) (((i&0xffff)<<4)+(0xffff&p))

int do_iret = 0;
int do_pending_eip = 0;

#define	MAX_INTS	(7)
#define	ASSIST_ADDR	(0xff000)

v86_hdw_assist(regs)
	register struct i386_saved_state *regs;
{
	int opcode = 0;
	struct assist_record {
		int		pending_eip;
		int		interrupts[MAX_INTS];
		int		int_cnt[MAX_INTS];
	} assist;

	if (copyin(V8(regs,cs,eip), &opcode, 1))
		return 0;			/* no opcode ?? */

	if (do_pending_eip) {
		if (copyin(ASSIST_ADDR, &assist, sizeof(assist))) return 0;
	}

	switch (opcode)
	{
	case 0xCF:				/* iret */
	    {
		if (do_iret) {
			u_short * sp;
			u_short flags;
			struct iret_info_struct {
				u_short	ip;
				u_short cs;
				u_short efl;
			} iret_info;
			sp = (u_short *)V8(regs,ss,uesp);
			if (copyin(sp, &iret_info, 6)) return 0;
			regs->eip = iret_info.ip;
			regs->cs  = iret_info.cs;
			if (do_pending_eip) {
				int return_eip;
				return_eip = V8(regs,cs,eip);
				if (return_eip == assist.pending_eip) {
					assist.pending_eip = 0;
					copyout(&assist,ASSIST_ADDR,
							sizeof(int));
				}
			}				
			flags 	  = iret_info.efl;
			flags &=  (0xfff);
			flags |= EFL_IF;
			regs->efl = (regs->efl&0xfffff000)|flags;
			regs->uesp += 6;
			goto handled;
		} else goto not_handled;
	    }
	case 0x9C:				/* pushf */
	    {
		int flags = 0;
		register u_short *uesp;
		regs->uesp -= 2;
		uesp  = (u_short *)V8(regs,ss,uesp);
		flags = regs->efl;
		if (copyout(&flags, uesp, 2)) {
			regs->uesp += 2;
			return 0;
		}
		regs->eip++;
		goto handled;
	    }
	case 0x9D:				/* popd */
	    {
		int flags = 0;
		register u_short *uesp = (u_short *)V8(regs,ss,uesp);

		if (copyin(uesp, &flags, 2)) return 0;

		regs->uesp += 2;
		flags &=  (0xfff);
		flags |= EFL_IF;
		regs->efl = (regs->efl&0xfffff000)|flags;
		regs->eip++;
		goto handled;
	    }
	default:
		goto not_handled;
	}

handled:
	return 1;

not_handled:
	return 0;				/* give to mom */
}

/* 
 * Handle a debug trap from system mode.  This can happen in one of 3 
 * ways:
 * 
 * 1 - A user process did a system call while single-stepping.  Our
 *     action is to set a flag in the pcb so that the user process
 *     will return to single-stepping once the system call is
 *     finished.
 * 2 - Someone is single-step debugging using kdb.  Our action is to 
 *     call kdb and let it deal with it.
 * 3 - We have hit a kernel breakpoint (set by kdb).  Again, our
 *     action is to call kdb.
 * 
 * For the first two cases, we can tell from dr6 that the CPU was 
 * single-stepping.  We distinguish case 1 from case 2 by checking a 
 * flag that kdb has set if it was single-stepping.  Cases 1 and 3 can 
 * happen at any time, so there aren't any global flags we can set to 
 * identify either of those cases.
 */

systemdebugtrap(type, locr0)
	int *locr0;			/* pointer to register stack */
{
	int dr6 = _dr6();
	extern int system_call;

	if (dr6 & DBG_BS) {
		/* single stepping */
#if	MACH_KDB
		if (kdb_singlestep) {
			kdb(T_SGLSTP, locr0);
		} else
#endif	MACH_KDB
		{
			/* 
			 * Additional sanity check.  The trap should 
			 * have happened near the system call entry 
			 * point in locore.
			 */
			if (locr0[EIP] < (int)&system_call ||
			    locr0[EIP] > ((int)&system_call + 10))
				panic("bogus single step trap\n");
			current_thread()->pcb->pcb_flags |=
				PSF_SINGLESTEP;
			locr0[EFL] &= ~EFL_TF;
		}
	} else {
#if	MACH_KDB
		kdb(type, locr0); /* kernel bkpt. */
#else	MACH_KDB
		panic("kdb breakpoint with no kdb.");
#endif	MACH_KDB
	}
}

/* 
 * Handle a page fault from system mode for a kernel page.  This gets 
 * a bit hairy because of copy-on-reference.
 * 
 * First treat the fault as a write fault.  If that works, we've
 * faulted in the page and we're done.  If that fails because of a
 * protection violation and the fault was really a read fault, fault
 * in the page as a read fault.  If this succeeds, call a special pmap 
 * routine to enable access to the page.
 * 
 * XXX The loop is in case another processor (on a multiprocessor)
 * steals the page before we can mark it present.  Note that this code
 * hasn't actually been tested on a multiprocessor.
 */
kern_return_t
kernel_fault_in(va, code)
	vm_offset_t va;
	int code;
{
	kern_return_t result;
	extern int cor_upgrades;	/* see pmap.c */

	va = trunc_page(va);

	if ((result = vm_fault(kernel_map, va, VM_PROT_READ|VM_PROT_WRITE,
			       FALSE)) == KERN_SUCCESS) {
		if (!(code & I386_PTE_KRW))
			cor_upgrades++;
		return(KERN_SUCCESS);
	}
	if (result != KERN_PROTECTION_FAILURE || (code & I386_PTE_KRW))
		return(result);

	/* It was a read fault, and we can't treat it as a write fault. */
	for (;;) {
		if ((result = vm_fault(kernel_map, va, VM_PROT_READ, FALSE))
		    != KERN_SUCCESS)
			return(result);
		if (pmap_mark_valid(va))
			break;
	}

	return(KERN_SUCCESS);
}
			
/*
 * Called from locore when a system call occurs.
 */
/*ARGSUSED*/
syscall(locr0)
	register int *locr0;
{
	short code;
	register caddr_t params;
	register int i;
	register struct sysent *callp = &sysent[20];/* known to be getpid */
	register int	error;
	register struct uthread	*uthread;
	thread_t	t = current_thread();
	int		s;
	register struct proc *p;
	struct timeval syst;
	short	syscode;

	code = locr0[EAX];
	syst = u.u_ru.ru_stime;
	uthread = t->u_address.uthread;
	if (!USERMODE(locr0[CS]))
		panic("syscall");
	uthread->uu_ar0 = locr0;
	if (t->pcb->pcb_flags & PSF_SINGLESTEP) {
		t->pcb->pcb_flags &= ~PSF_SINGLESTEP;
		locr0[EFL] |= EFL_TF;
	}

	if (code == 139) {			/* XXX 4.2 COMPATIBILITY */
#if	NCPUS > 1
		unix_master();
#endif	NCPUS > 1
		osigcleanup();			/* XXX 4.2 COMPATIBILITY */
		goto done;			/* XXX 4.2 COMPATIBILITY */
	}					/* XXX 4.2 COMPATIBILITY */
	params = (caddr_t)locr0[UESP] + NBPW;
	u.u_error = 0;
	callp = ((u_short)(code+ncmusysent) >= nallsysent) ?
		&sysent[63] : &sysent[code];
	if (callp == sysent) {
		i = fuword(params);
		params += NBPW;
		callp = ((u_short)(i+ncmusysent) >= nallsysent) ?
			&sysent[63] : &sysent[i];
		syscode = i;
	}
	else
		syscode = code;
	if ((i = callp->sy_narg * sizeof (int)) &&
	    (error = copyin(params, (caddr_t)uthread->uu_arg,
			    (u_int)i)) != 0) {
		locr0[EAX] = error;
		locr0[EFL] |= EFL_CF;	/* carry bit */
		goto done;
	}
	uthread->uu_r.r_val1 = 0;
	uthread->uu_r.r_val2 = locr0[EDX];
#if	NCPUS > 1
	if (callp->sy_parallel == 0) {
		/*
		 *	System call must execute on master cpu
		 */
		if (t->unix_lock != -1)
			panic("syscall,unix_master(): unix_lock != -1");
		unix_master();		/* hold to master during syscall */
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
				uprintf("[P%d %s]0x%x",
					u.u_procp->p_pid,
					u.u_comm,
					syscode);
			else
				uprintf("[P%d %s]%s",
					u.u_procp->p_pid,
					u.u_comm,
					syscallnames[syscode]);
			cp = "(";
			for (i= 0; i < callp->sy_narg; i++) {
				uprintf("%s%x", cp, u.u_arg[i]);
				cp = ", ";
			}
			if (i)
				cp = ")";
			else
				cp = "";
#ifdef	DDD
			uprintf("%s\n", cp);
#else
			uprintf("%s", cp);
#endif
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
		 *  Show no resource pause conditions.
		 */
		uthread->uu_rpswhich = 0;
		uthread->uu_rpsfs = 0;
		(*(callp->sy_call))();
		error = uthread->uu_error;
		if (syscalltrace && 
		    (syscalltrace == u.u_procp->p_pid || syscalltrace < 0)) {
			if (error)
				uprintf(" = -1 [%d]\n", error);
			else
				uprintf(" = %x:%x\n", uthread->uu_r.r_val1,
						     uthread->uu_r.r_val2);
/*			DELAY(1*200000);*/
	}
	}
#if	MACH_RFS
	/*
	 *  The special error number EREMOTE is used by the remote system call
	 *  facility to short-circuit standard system call processing when the
	 *  equivalent has already been done remotely.  It serves simply to
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
			locr0[EAX] = error;
			locr0[EFL] |= EFL_CF;	/* carry bit */
		} else {
			locr0[EAX] = uthread->uu_r.r_val1;
			locr0[EDX] = uthread->uu_r.r_val2;
			locr0[EFL] &= ~EFL_CF;
		}
	} else if (uthread->uu_eosys == RESTARTSYS)
		/* Back the pc up to before the lcall */
		locr0[EIP] -= 7;
	/* else if (u.u_eosys == JUSTRETURN) */
		/* nothing to do */
done:
	uthread->uu_error = error;
	p = u.u_procp;
	XPR(XPR_SYSCALLS, 
		("syscall end: pid=%d, code=%d, rval1=%d, rval2=%d\n",
		u.u_procp->p_pid, code, u.u_r.r_val1, u.u_r.r_val2));
#ifdef	THREAD_EXIT
	if (CHECK_SIGNALS(p, uthread))
#else	THREAD_EXIT
	if (CHECK_SIGNALS(p, t, uthread))
#endif	THREAD_EXIT
	{
		unix_master();
		if (p->p_cursig || issig()) {
			psig();
		}
		unix_release();
	}
	p->p_pri = p->p_usrpri;
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
#ifdef	THREAD_EXIT
	while (thread_should_halt())
		thread_halt_self();

	if (runrun[cpu_number()] && csw_check()) {
		s = splhigh();
		u.u_ru.ru_nivcsw++;
		runrun[cpu_number()] = 0;
		thread_block();
		splx(s);
	}
#else	THREAD_EXIT
	if (csw_needed(t, current_processor())) {
		u.u_ru.ru_nivcsw++;
		thread_block();
	}
#endif	THREAD_EXIT
	if (u.u_prof.pr_scale) {
		int ticks;
		struct timeval *tv = &u.u_ru.ru_stime;

		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks) {
			simple_lock(&u.u_prof.pr_lock);
			addupc(locr0[EIP], &u.u_prof, ticks);
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
#if	MACH_EXCEPTION
	thread_doexception(current_thread(), EXC_SOFTWARE,
		EXC_UNIX_BAD_SYSCALL, 0);
#else	MACH_EXCEPTION
	psignal(u.u_procp, SIGSYS);
#endif	MACH_EXCEPTION
}

static int fpsw;

nofloat()
{
	_fninit();
	fpsw = _fstcw();
	fpsw &= ~(FPINV | FPZDIV | FPOVR | FPPC);
	fpsw |= FPSIG53 | FPIC;
	_fldcw(fpsw);
	return;
}

astintr(regptr)
	int *regptr;
{
	struct proc *p;
	int s;

	p = u.u_procp;
	if (p) {
#ifdef	THREAD_EXIT
		while (thread_should_halt())
			thread_halt_self();
#endif	THREAD_EXIT
		if (p) {
		    if ((p->p_flag & SOWEUPC) && u.u_prof.pr_scale) {
			addupc(regptr[EIP], &u.u_prof, 1);
			p->p_flag &= ~SOWEUPC;
		    }
		}
#ifdef	THREAD_EXIT
		if (CHECK_SIGNALS(p, current_thread()->u_address.uthread))
#else	THREAD_EXIT
		if (CHECK_SIGNALS(p, current_thread(),
				  current_thread()->u_address.uthread))
#endif	THREAD_EXIT
		{
			unix_master();
			if (p->p_cursig || issig()) {
				psig();
			}
			unix_release();
		}
	}
#ifdef	THREAD_EXIT
	if (runrun[cpu_number()] && csw_check()) {
		s = splhigh();
		runrun[cpu_number()] = 0;
		u.u_ru.ru_nivcsw++;
		thread_block();
		splx(s);
	}
#else	THREAD_EXIT
	if (csw_needed(current_thread(), current_processor())) {
		u.u_ru.ru_nivcsw++;
		thread_block();
	}
#endif	THREAD_EXIT
}
