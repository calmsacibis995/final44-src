/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	trap.c,v $
 * Revision 2.15  91/06/25  17:20:37  mbj
 * 	Set saved rfs syscall number to actual syscall for indirect syscalls.
 * 
 * Revision 2.14  91/06/24  16:38:09  mbj
 * 	Moved check for signals from htg_unix_syscall_common() out to the
 * 	machine dependent htg_unix_syscall() routines.  The htg_unix_syscall()
 * 	return value must be stored at the appropriate u.u_ar0 location before
 * 	any signal frames are constructed or else it will not be correctly
 * 	reflected in the constructed sigcontext.
 * 	[91/06/07            mbj]
 * 
 * Revision 2.13  91/05/24  15:42:27  mbj
 * 	Fixed longstanding range check error when testing for Mach syscalls.
 * 	[91/05/23            mbj]
 * 	Added machine dependent htg_unix_syscall() entry point.
 * 	[91/05/08            mbj]
 * 
 * Revision 2.12  90/09/08  12:01:23  mrt
 * 	Corrected the inlude of builtin/ux_exception.h to
 * 	sys/ux_exception.h.
 * 	[90/09/08            mrt]
 * 
 * Revision 2.11  89/10/11  14:50:36  dlb
 * 	Only check for termination after an AST.  Add rpd fix to
 * 	termination check after page faults.  CHECK_SIGNALS macro change.
 * 	Use csw_needed instead of runrun and friends.
 * 	[89/10/07            dlb]
 * 
 * Revision 2.10  89/03/09  21:38:49  rpd
 * 	More cleanup.
 * 
 * Revision 2.9  89/02/25  19:48:09  gm0w
 * 	Added include of cputypes.h
 * 	[89/02/18            mrt]
 * 
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.8  89/01/18  01:11:31  jsb
 * 	Vnode support: changed EREMOTE to ERFSREMOTE.
 * 	[89/01/16  15:24:18  jsb]
 * 
 * Revision 2.7  88/10/18  03:37:01  mwyoung
 * 	Add check for thread halt in page fault handling.
 * 	[88/09/08            mwyoung]
 * 
 * Revision 2.6  88/08/24  02:11:36  mwyoung
 * 	Use new CMUCS_RFS conditional.
 * 	[88/08/23            mwyoung]
 * 	
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 * Revision 2.4  88/07/17  19:30:13  mwyoung
 * *** empty log message ***
 *
 * Revision 2.5  88/08/22  21:31:41  mja
 * 	Don't clear resource pause notify flag on entry into system
 * 	call; add EDQUOT case to the fspause() check temporarily until
 * 	the two cases are better distinguished; collapse conditionals.
 * 	[88/08/08  17:52:24  mja]
 * 
 * 23-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Distinguish users of kernel VM in a new way.
 *
 *  2-Jun-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: MACH_EXCEPTION is always on.
 *
 * 15-Apr-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	For kernel-only tasks, try faults in the task's map before the
 *	kernel_map.
 *
 * 11-Apr-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed trap() to check to make sure the fpa exists when a
 *	thread bus errors tryihg to touch the FPA.
 *	Added fpa_init() to initialize the FPA for use by a thread
 *	and changed trap() to call it when a thread gets a bus 
 *	error trying to use the FPA.
 *	Added changes from Sun Unix 3.4 to trap():
 *		1) Reset stack pointer to adjusted system sp
 *		   if not in user mode
 *		2) Panic on kernel address errors
 *		3) Added code for FPA bus errors
 *		4) Reorganized code for user bus errors
 *	Changed FPA user bus error code to put state and exception
 *	info in pcb instead of u-area.
 *
 *  8-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Eliminate use of cnt.
 *
 * 27-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Move rfs, vice, and rpause tests after call completes to a
 *	switch statement dependent on u_error != 0.
 *
 * 26-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	In syscall, flush u. in front of references and define uthread
 *	and utask as pointers.  If this is not clear look at user.h
 *	Saves about 8% in getpid syscall test.
 *
 * 25-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Rather than have "u" expand to current_thread()->u_address, have
 *	it expand to the constant U_ADDRESS which is updated by load_context
 *	when the thread changes.  If "u" is defined, then user.h won't define
 *	it.  BUT we can only "extern" U_ADDRESS in sun3/thread.h, so we define
 *	the storage here.
 *
 * 21-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Made addressing exceptions return address as subcode.
 *
 *  7-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Implemented MACH exception handling (from DLB and Karl Hauth).
 *
 * 26-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Check for thread-exit conditions in more places by using
 *	new macros.
 *
 * 10-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Check for abnormal thread exit conditions.  Clean up
 *	conditionals some more.
 *
 * 16-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 * 16-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH_MP:  Flush more incomplete multi-processor code.
 *	[ V5.1(XF19) ]
 *
 * 23-Sep-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Delete unix_master() and unix_swtch to master.  We are not a 
 *	multiprocessor for the present.
 *
 * 20-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	Added thread exception checks for MACH_TT.
 *
 * 28-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed curpri array under MACH_TT.
 *
 * 21-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added code for MACH_TT.
 *
 * 17-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	VICE:  Fixed bug which neglected to reset code at end of system
 *	call.
 *	[ V5.1(F7) ]
 *
 * 12-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	sys/syscalls.c -> bsd/syscalls.c
 *
 * 15-Feb-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to pop system call number off of stack after
 *	making a Mach system call.
 *
 * 13-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  added new required parameter to fspause().
 *	[ V5.1(F2) ]
 *
 *  9-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Updated for NEW_SCHED.
 *
 * 23-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Merged in changes from VAX versions:
 *	changed names for MACH trap tables
 *	Should make MACH_TT work, but the VAX code is ugly and
 *	should be fixed.
 *
 * 15-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified for Mach.
 *
 */

#include <mach_kdb.h>
#include <mach_rfs.h>
#include <vice.h>
#include <cputypes.h>

#ifndef	lint
static	char sccsid[] = "@(#)trap.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/vm.h>
#include <sys/kernel.h>
#include <kern/xpr.h>
#if	MACH_RFS
#ifndef	SYSCALLTRACE
#define SYSCALLTRACE
#endif	SYSCALLTRACE
#endif	MACH_RFS
#ifdef	SYSCALLTRACE
#include <bsd/syscalls.c>
#endif	SYSCALLTRACE

#include <sun/fault.h>
#include <sun/frame.h>
#include <sun3/buserr.h>
#include <sun3/memerr.h>
#include <sun3/mmu.h>
#include <sun3/cpu.h>
#include <sun3/psl.h>
#include <sun3/reg.h>
#include <sun3/trap.h>

#include <fpa.h>
#if	NFPA > 0
#include <sundev/fpareg.h>
#include <sun3/enable.h>
extern short fpa_exist;
extern enum fpa_state fpa_state;
#endif	NFPA > 0

#include <kern/thread.h>
#include <kern/task.h>
#include <vm/vm_kern.h>
#include <vm/vm_map.h>
#include <mach/vm_param.h>
#include <mach/kern_return.h>
#include <kern/syscall_sw.h>

#include <mach/exception.h>
#include <sys/ux_exception.h>
#include <mach_emulation.h>
#if	MACH_EMULATION
#include <kern/syscall_emulation.h>
#include <kern/parallel.h>
#include <sys/syscall.h>
#endif	MACH_EMULATION

#define USER	0x400		/* user-mode flag added to type */

extern struct	sysent	cmusysent[];
extern int ncmusysent;
extern int nallsysent;
extern struct sysent sysent[];
extern int nsysent;

extern long	master_idle;
struct	u_address	U_ADDRESS;

char	*trap_type[] = {
	"Vector address 0x0",
	"Vector address 0x4",
	"Bus error",
	"Address error",
	"Illegal instruction",
	"Divide by zero",
	"CHK, CHK2 instruction",
	"TRAPV, cpTRAPcc, cpTRAPcc instruction",
	"Privilege violation",
	"Trace",
	"1010 emulator trap",
	"1111 emulator trap",
	"Vector address 0x30",
	"Coprocessor protocol error",
	"Stack format error",
	"Uninitialized interrupt",
	"Vector address 0x40",
	"Vector address 0x44",
	"Vector address 0x48",
	"Vector address 0x4c",
	"Vector address 0x50",
	"Vector address 0x54",
	"Vector address 0x58",
	"Vector address 0x5c",
	"Spurious interrupt",
};
#if	MACH_KDB
/*
 *  Need this accessible to the kernel debugger.
 */
int	TRAP_TYPES =	(sizeof trap_type / sizeof trap_type[0]);
#else	MACH_KDB
#define TRAP_TYPES	(sizeof trap_type / sizeof trap_type[0])
#endif	MACH_KDB

#define DEBUG	1

#if	defined(DEBUG) || defined(lint)
int tdebug  = 0;
int tudebug = 0;
int lodebug = 0;
int bedebug = 0;
#else
#define tdebug	0
#define tudebug	0
#define lodebug	0
#define bedebug	0
#endif	defined(DEBUG) || defined(lint)

u_char	getsegmap();
long	getpgmap();

/*
 * Called from the trap handler when a processor trap occurs.
 * Returns amount to adjust the stack:  > 0 removes bus error
 * info, == 0 does nothing.
 */
int
trap(type, regs, fmt)
	int type;
	struct regs regs;
	struct stkfmt fmt;
{
	register struct regs *locregs = &regs;
	register int i = 0;
	struct proc *p;
	struct timeval syst;
	int nosig = 0;
	int besize = 0;
	int be = (type == T_BUSERR)? getbuserr() : 0;
	int	exception, code;
	int	subcode = 0;
	register struct pcb *pcb;

	if (!current_thread() && ! ((type == T_BUSERR) && nofault)) {
		printf("trap type = %x\n", type);
		halt("trap in boot phase");
	}

	if (tdebug || !current_thread() && ! ((type == T_BUSERR) && nofault)) {
		i = type/sizeof (int);
		if ((unsigned)i < TRAP_TYPES)
			printf("trap: %s\n", trap_type[i]);
		showregs("trap", type, locregs, &fmt, be);
	}
	if (USERMODE(locregs->r_sr)) {
		syst = u.u_ru.ru_stime;
		type |= USER;
		u.u_ar0 = &locregs->r_dreg[0];
		current_thread()->pcb->user_regs =
					(struct sun_saved_state *)locregs;
	} else {
		/* reset sp value to adjusted system sp */ 
		locregs->r_sp = (int)&fmt.f_beibase;
		switch (fmt.f_stkfmt) {
		case SF_NORMAL:
		case SF_THROWAWAY:
			break;
		case SF_NORMAL6:
			locregs->r_sp += sizeof (struct bei_normal6);
			break;
		case SF_COPROC:
			locregs->r_sp += sizeof (struct bei_coproc);
			break;
		case SF_MEDIUM:
			locregs->r_sp += sizeof (struct bei_medium);
			break;
		case SF_LONGB:
			locregs->r_sp += sizeof (struct bei_longb);
			break;
		default:
			panic("bad system stack format");
			/*NOTREACHED*/
		}
	}


	switch (type) {

	case T_ADDRERR:			/* kernel address error */
		/* 
		 * On 68020, addresses errors can only happen
		 * when executing instructions on an odd boundary.
		 * Therefore, we cannot have gotten here as a
		 * result of copyin/copyout request - so panic.
		 */
	default:
	die:
#if	MACH_KDB
		if (kdb_trap(type, &regs))
			return(0);
		/* fall through */
#endif	MACH_KDB
		(void) spl7();
		showregs((char *)0, fmt.f_vector, locregs, &fmt, be);
		traceback((long)locregs->r_areg[6], (long)locregs->r_sp);
		i = fmt.f_vector/sizeof (int);
		if (i < TRAP_TYPES)
			panic(trap_type[i]);
		panic("trap");
		/*NOTREACHED*/

	case T_BUSERR:
		if (be & BE_TIMEOUT)
			DELAY(2000);	/* allow for refresh recovery time */

		/* may have been expected by C (e.g., Multibus probe) */
		if (nofault) {
			label_t *ftmp;

			ftmp = nofault;
			nofault = 0;
			longjmp(ftmp);
		}
#if	NFPA > 0
		/*
		 * If enable register is not turned on, try to initialize the
		 * FPA.  Otherwise, panic if can't initialize FPA.
		 * In case of FPA bus error in the kernel mode, shutdown
		 * FPA, instead of panic'ing the system.
		 */
		if (fpa_exist && (be & BE_FPAENA) && fpa_state != FPA_DISABLED)
			if (fpa_init(current_thread()) == 0)
				return(0);
		if (be & BE_FPAENA)
			panic("FPA not enabled");
		if (be & BE_FPABERR) {
			showregs("FPA KERNEL BUS ERROR", fmt.f_vector, locregs,
			    &fmt, be);
			traceback((long)locregs->r_areg[6],
			    (long)locregs->r_sp);
			printf("FPA BUS ERROR: IERR == %x\n", fpa->fp_ierr);
			fpa_shutdown();
			exception = EXC_BAD_ACCESS;
			code = KERN_INVALID_ADDRESS;
			subcode = (int)fpa;	/* fpa address as indicator */
			break;
		}
#endif	NFPA > 0
		/* may be fault caused by transfer to/from user space */
		/* In MACH it's OK for the kernel to fault in some things */

		switch (fmt.f_stkfmt) {
		case SF_MEDIUM: {
			struct bei_medium *beip =
			    (struct bei_medium *)&fmt.f_beibase;

			besize = sizeof (struct bei_medium);
#if	NFPA > 0
#ifdef	SUN3_260
			if (fpa_exist && fpa_state != FPA_DISABLED &&
			    ((char *)beip->bei_fault >= (char *)fpa && 
			    (char *)beip->bei_fault < (char *)fpa +
			    sizeof(struct fpa_device)))
				if (fpa_init(current_thread()) == 0)
					return(0);
#endif	SUN3_260
#endif	NFPA > 0
			if (beip->bei_dfault) {
			    code = pagefault(beip->bei_fault, beip->bei_rw ?
				VM_PROT_READ : VM_PROT_READ | VM_PROT_WRITE,
				locregs);
			    if (code == KERN_SUCCESS)
			    	return(0);
			    subcode = beip->bei_fault;
			}
			break;
			}
		case SF_LONGB: {
			struct bei_longb *beip =
			    (struct bei_longb *)&fmt.f_beibase;

			besize = sizeof (struct bei_longb);
#if	NFPA > 0
#ifdef	SUN3_260
			if (fpa_exist && fpa_state != FPA_DISABLED &&
			    ((char *)beip->bei_fault >= (char *)fpa && 
			    (char *)beip->bei_fault < (char *)fpa +
			    sizeof(struct fpa_device)))
				if (fpa_init(current_thread()) == 0)
					return(0);
#endif	SUN3_260
#endif	NFPA > 0
			if (beip->bei_dfault) {
			    code = pagefault(beip->bei_fault, beip->bei_rw ?
				VM_PROT_READ : VM_PROT_READ | VM_PROT_WRITE,
				locregs);
			    if (code == KERN_SUCCESS)
			    	return(0);
			    subcode = beip->bei_fault;
			}
			break;
			}
		default:
			panic("bad bus error stack format");
		}
#if	MACH_KDB
		{
			/*
			 *	The kernel debugger has its own
			 *	recovery hook.
			 */
			extern int kdbtrapok;
			if (kdbtrapok) {
				kdb_trap(type, &regs);
				return(besize);
			}
		}
#endif	MACH_KDB

		if (lodebug) {
			showregs("lofault", type, locregs, &fmt, be);
			traceback((long)locregs->r_areg[6],
			    (long)locregs->r_sp);
		}
		if (current_thread()->recover == 0)
			goto die;

		locregs->r_pc = current_thread()->recover;
		current_thread()->recover = 0;
		return (besize);

	case T_ADDRERR + USER:		/* user address error */
		if (tudebug)
			showregs("USER ADDRESS ERROR", type, locregs, &fmt, be);
		/*
		 *	On 68020 this happens only when executing code at
		 *	an odd address
		 */
		exception = EXC_BAD_INSTRUCTION;
		code = fmt.f_vector;
		switch (fmt.f_stkfmt) {
		case SF_MEDIUM:
			besize = sizeof (struct bei_medium);
			break;
		case SF_LONGB:
			besize = sizeof (struct bei_longb);
			break;
		default:
			panic("bad address error stack format");
		}
		break;

	case T_SPURIOUS:
	case T_SPURIOUS + USER:		/* spurious interrupt */
		i = spl7();
		printf("spurious level %d interrupt\n", (i & SR_INTPRI) >> 8);
		(void) splx(i);
		return (0);

	case T_PRIVVIO + USER:		/* privileged instruction fault */
		if (tudebug)
			showregs("USER PRIVILEGED INSTRUCTION", type, locregs,
			    &fmt, be);
		exception = EXC_BAD_INSTRUCTION;
		code = EXC_SUN3_PRIVILEGE_VIOLATION;
		break;

	case T_COPROCERR + USER:	/* coprocessor protocol error */
		/*
		 * Dump out obnoxious info to warn user
		 * that something isn't right w/ the 68881
		 */
		showregs("USER COPROCESSOR PROTOCOL ERROR", type, locregs,
		    &fmt, be);
		exception = EXC_BAD_INSTRUCTION;
		code = EXC_SUN3_COPROCESSOR;
		break;

	case T_M_BADTRAP + USER:	/* (some) undefined trap */
	case T_ILLINST + USER:		/* illegal instruction fault */
		if (tudebug)
			showregs("USER ILLEGAL INSTRUCTION", type, locregs,
			    &fmt, be);
		exception = EXC_BAD_INSTRUCTION;
		code = fmt.f_vector;
		break;

	case T_M_FLOATERR + USER:	/* (some) floating error trap */
	case T_ZERODIV + USER:		/* divide by zero */
		code = fmt.f_vector;
		if (code == EXC_SUN3_FLT_BSUN ||
		    code == EXC_SUN3_FLT_OPERAND_ERROR) {
			exception = EXC_BAD_INSTRUCTION;
		}
		else {
			exception = EXC_ARITHMETIC;
		}
		break;

	case T_CHKINST + USER:		/* CHK [CHK2] instruction */
	case T_TRAPV + USER:		/* TRAPV [cpTRAPcc TRAPcc] instr */
		exception = EXC_SOFTWARE;
		code = fmt.f_vector;
		break;


	/*
	 * User bus error.  Try to handle FPA, then pagefault, and
	 * failing that, grow that stack automatically if a data fault.
	 */
	case T_BUSERR + USER:

		if (be & BE_TIMEOUT)
			DELAY(2000);	/* allow for refresh recovery time */

		/*
		 * Copy the "rerun" bits to the "fault" bits.
		 *
		 * This is what is going on here (don't believe
		 * the 2nd edition 68020 description in section
		 * 6.4.1, it is full of errors).  A rerun bit
		 * being on means that the prefetch failed.  A
		 * fault bit being on means the processor tried
		 * to use bad prefetch data.  Upon return via
		 * the RTE instruction, the '20 will retry the
		 * instruction access only if BOTH the rerun and
		 * the corresponding fault bit is on.
		 *
		 * We need to do guarantee that any time we have a
		 * fault that we have actually just run the cycle,
		 * otherwise the current external state (i.e. the
		 * bus error register) might not anything to do with
		 * what really happened to cause the prefetch to fail.
		 * For example the prefetch might have occured previous
		 * to an earlier bus error exception whose handling
		 * might have resolved the prefetch problem.  Thus by
		 * copying the "rerun" bits, we force the `20 to rerun
		 * every previously faulted prefetch upon return from
		 * this bus error.  This way we are guaranteed that we
		 * never get a "bogus" '20 internal bus error when it
		 * attempts to use a previously faulted prefetch.  On
		 * the downside, this hack might make the kernel fix up
		 * a prefetch fault that the '20 was not going to use.
		 * What we really need is a "don't know anything about
		 * a prefetch bit".  If we had something like that then 
		 * the '20 could know enough to rerun the prefetch, but
		 * only if it turns out that it really needs it.
		 *
		 * RISC does have its advantages.
		 *
		 * N.B.  This code depends on not having an executable
		 * where the last instruction in the text segment is
		 * too close the end of a page.  We don't want to get
		 * ourselves in trouble trying to fix up a fault beyond
		 * the end of the text segment.  But because the loader
		 * already pads out by an additional page when it sees
		 * this problem due to microcode bugs with the first
		 * year or so worth of '20 chips, we shouldn't get be
		 * in trouble here.
		 */

		switch (fmt.f_stkfmt) {
		case SF_MEDIUM: {
			struct bei_medium *beip =
			    (struct bei_medium *)&fmt.f_beibase;

			besize = sizeof (struct bei_medium);
			beip->bei_faultc = beip->bei_rerunc;
			beip->bei_faultb = beip->bei_rerunb;
			break;
			}
		case SF_LONGB: {
			struct bei_longb *beip =
			    (struct bei_longb *)&fmt.f_beibase;

			besize = sizeof (struct bei_longb);
			beip->bei_faultc = beip->bei_rerunc;
			beip->bei_faultb = beip->bei_rerunb;
			break;
			}
		default:
			panic("bad bus error stack format");
		}

#if	NFPA > 0
		pcb = current_thread()->pcb;
		if (fpa_exist && (be & BE_FPAENA) && fpa_state != FPA_DISABLED)
			if (fpa_init(current_thread()) == 0)
				return(0);
		if (be & (BE_FPAENA | BE_FPABERR)) {
			/*
		 	 * FPA exception from FPA board.
		 	 * We save bus error PC in pcb_fpa_pc and save the
		 	 * current bus error information at pcb_fpa_fmtptr.
		 	 * Other information saved are: (high core) the bus
		 	 * error exception frame, a short of frame type and
		 	 * vector offset, the struct regs, a long of AST bits
			 * of pcb_flag, short indicating the size of this area,
			 * and a short indicating the size to restore to
			 * the kernel stack.
		 	 * The exception frame is rte'ed to 68020 when
		 	 * pcb_fpa_pc equals kernel stack's PC in syscall: of
			 * locore.s.
		 	 */
			struct fpa_stack {
				short	fpst_save_size;
				short	fpst_alloc_size;
				long	fpst_ast_bits;
				struct regs fpst_regs;
				short	fpst_stkfmt;
				struct bei_longb  fpst_longb;
			} *fp;

			code = (be & BE_FPAENA) ? FPE_FPA_ENABLE
					: FPE_FPA_ERROR;
			if (pcb->pcb_fpa_fmtptr == NULL) {
				/* First FPA exception, alloc space */
				pcb->pcb_fpa_fmtptr = (char *)kmem_alloc(
				    kernel_map, sizeof (struct fpa_stack));
				fp = (struct fpa_stack *)pcb->pcb_fpa_fmtptr;
				fp->fpst_alloc_size = sizeof (struct fpa_stack);
			} else
				fp = (struct fpa_stack *)pcb->pcb_fpa_fmtptr;

			pcb->pcb_fpa_pc = u.u_ar0[PC];
			fp->fpst_ast_bits = pcb->pcb_flag & AST_CLR;
			/*
			 * Current kernel stack: (high core)exception stk,
			 * a short(stkfmt+vector offset), regs(low core).
			 * We save regs, a short(stkfmt+vector offset),
			 * and the exception stack.
			 */
			fp->fpst_save_size = sizeof (struct regs)
			    + sizeof (short) + besize;
			bcopy((caddr_t)&regs, (caddr_t)&fp->fpst_regs,
			    (u_int)fp->fpst_save_size);
			exception = EXC_ARITHMETIC;
			break;
		}
#endif	NFPA > 0
		if (be & ~(BE_INVALID|BE_PROTERR)){
			/*
			 * Some other error indicated in the bus error
			 * invalid so there is nothing we can do now.
			 */
		} else if (fmt.f_stkfmt == SF_MEDIUM) {
			struct bei_medium *beip =
			    (struct bei_medium *)&fmt.f_beibase;

#if	NFPA > 0
#ifdef	SUN3_260
			if (fpa_exist && fpa_state != FPA_DISABLED &&
			    ((char *)beip->bei_fault >= (char *)fpa && 
			    (char *)beip->bei_fault < (char *)fpa +
			    sizeof(struct fpa_device)))
				if (fpa_init(current_thread()) == 0)
					return(0);		    
#endif	SUN3_260
#endif	NFPA > 0
			if ((bedebug && (beip->bei_faultb || beip->bei_faultc))
			    || (bedebug > 1 && beip->bei_fault))
				printf("medium fault b %d %x, c %d %x, d %d %x\n",
				    beip->bei_faultb, locregs->r_pc + 4,
				    beip->bei_faultc, locregs->r_pc + 2,
				    beip->bei_dfault, beip->bei_fault);

			if (beip->bei_dfault) {
				code = pagefault(beip->bei_fault,
				    beip->bei_rw ? VM_PROT_READ : VM_PROT_READ
				    | VM_PROT_WRITE, locregs);
				if (code == KERN_SUCCESS)
					return (0);
				subcode = beip->bei_fault;
				if (grow((unsigned)beip->bei_fault)) {
					nosig = 1;
					besize = 0;
					goto out;
				}
			} else if (beip->bei_faultc) {
				code = pagefault(locregs->r_pc+2,
					    VM_PROT_READ, locregs);
				if (code == KERN_SUCCESS)
					return (0);
				subcode = locregs->r_pc+2;
			}
			else if (beip->bei_faultb) {
				code = pagefault(locregs->r_pc+4,
				    VM_PROT_READ, locregs);
				if (code == KERN_SUCCESS)
					return (0);
				subcode = locregs->r_pc+4;
			}
		} else {
			struct bei_longb *beip =
			    (struct bei_longb *)&fmt.f_beibase;
#if	NFPA > 0
#ifdef	SUN3_260
			if (fpa_exist && fpa_state != FPA_DISABLED &&
			    ((char *)beip->bei_fault >= (char *)fpa && 
			    (char *)beip->bei_fault < (char *)fpa +
			    sizeof(struct fpa_device)))
				if (fpa_init(current_thread()) == 0)
					return(0);		    
#endif	SUN3_260
#endif	NFPA > 0
			if ((bedebug && (beip->bei_faultb || beip->bei_faultc))
			    || (bedebug > 1 && beip->bei_fault))
				printf("long fault b %d %x, c %d %x, d %d %x\n",
				    beip->bei_faultb, beip->bei_stageb,
				    beip->bei_faultc, beip->bei_stageb-2,
				    beip->bei_dfault, beip->bei_fault);

			if (beip->bei_dfault) {
				code = pagefault(beip->bei_fault,
				    beip->bei_rw ? VM_PROT_READ : VM_PROT_READ
				    | VM_PROT_WRITE, locregs);
				if (code == KERN_SUCCESS)
					return (0);
				subcode = beip->bei_fault;
				if (grow((unsigned)beip->bei_fault)) {
					nosig = 1;
					besize = 0;
					goto out;
				}
			} else if (beip->bei_faultc) {
				code = pagefault(beip->bei_stageb-2,
				    VM_PROT_READ, locregs);
				if (code == KERN_SUCCESS)
					return (0);
				subcode = beip->bei_stageb-2;
			}
			else if (beip->bei_faultb) {
				code = pagefault(beip->bei_stageb,
				    VM_PROT_READ, locregs);
				if (code == KERN_SUCCESS)
					return (0);
				subcode = beip->bei_stageb;
			}
		}
		if (tudebug)
			showregs("USER BUS ERROR", type, locregs, &fmt, be);
		exception = EXC_BAD_ACCESS;
		break;

	case T_TRACE:			/* caused by tracing trap instr */
#if	MACH_KDB
		if (current_thread()->pcb->pcb_flag & TRACE_KDB) {
			/*
			 *	trap to kernel debugger
			 */
			current_thread()->pcb->pcb_flag &= ~TRACE_KDB;
			kdb_trap(T_TRACE, &regs);
			return(0);
		}
#endif	MACH_KDB
		current_thread()->pcb->pcb_flag |= TRACE_PENDING;
		return (0);

	case T_TRACE + USER:		/* trace trap */
#if	MACH_KDB
		if (current_thread()->pcb->pcb_flag & TRACE_KDB) {
			/*
			 *	trap to kernel debugger
			 */
			current_thread()->pcb->pcb_flag &= ~TRACE_KDB;
			kdb_trap(T_TRACE, &regs);
			return(0);
		}
#endif	MACH_KDB
		dotrace(locregs);
		goto out;

	case T_BRKPT + USER:		/* bpt instruction (trap #15) fault */
		exception = EXC_BREAKPOINT;
		code = EXC_SUN3_BREAKPOINT;
		break;

	case T_EMU1010 + USER:		/* 1010 emulator trap */
	case T_EMU1111 + USER:		/* 1111 emulator trap */
		exception = EXC_EMULATION;
		code = fmt.f_vector;
		break;
	}

	/*
	 *	Exception occurred -- clear pending trace. XXX
	 */
	current_thread()->pcb->pcb_flag &= ~TRACE_PENDING;
	thread_doexception(current_thread(), exception, code, subcode);
out:
	p = u.u_procp;
	if (current_thread()->pcb->pcb_flag & TRACE_PENDING)
		dotrace(locregs);
	if (CHECK_SIGNALS(p, current_thread(), current_thread()->u_address.uthread)) {
		if (p->p_cursig || issig())
			psig();
	}
	p->p_pri = p->p_usrpri;
	if (USERMODE(locregs->r_sr)) {
		/*
		 *	If trapped from user mode, handle possible
		 *	rescheduling.
		 */
		if (csw_needed(current_thread(), current_processor())) {
			u.u_ru.ru_nivcsw++;
			thread_block();
		}
	}
	if (u.u_prof.pr_scale) {
		int ticks;
		struct timeval *tv = &u.u_ru.ru_stime;

		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks)
			addupc(locregs->r_pc, &u.u_prof, ticks);
	}
	return (besize);
}

#ifdef	SYSCALLTRACE
int syscalltrace = 0;
int syscalltracing = 0;
int syscallhalt = 0;
#endif
/*
 * Called from the trap handler when a system call occurs
 */
syscall(code, regs)
	int code;
	struct regs regs;
{
	struct timeval syst;
	short int syst_flag;
	register struct utask *utask = u.utask;
	register struct uthread *uthread = u.uthread;

	if (u_prof.pr_scale) {
		syst = u_ru.ru_stime;
		syst_flag = 1;
	} else
		syst_flag = 0;
#ifdef	notdef
	if (!USERMODE(regs.r_sr))
		panic("syscall");
#endif
	{
	/*
	 * At this point we declare a number of register variables.
	 * syscall_setjmp (called below) does not preserve the values
	 * of register variables, so we limit their scope to this block.
	 */
	register struct regs *locregs;
	register struct sysent *callp;

	locregs = &regs;
	u_ar0 = &locregs->r_dreg[0];
	current_thread()->pcb->user_regs =
				(struct sun_saved_state *)locregs;
	/*
	 *	CMU system calls have negative numbers
	 */
	if (code < 0) {
		if (code < -ncmusysent &&
		    code > -mach_trap_count) {
			regs.r_dreg[0] = do_mach_syscall(code, locregs);
			regs.r_sp += sizeof(int);	/* pop syscall # */
			goto out;
		}
		else if (code < -ncmusysent)
			callp = &sysent[63];	/* undefined */
		else
			callp = &cmusysent[code + ncmusysent];
	}
	else
		callp = (code >= nsysent) ? &sysent[63] : &sysent[code];
	u_error = 0;
	if (callp->sy_narg) {
		if (fulwds((caddr_t)locregs->r_sp + 2 * NBPW, (caddr_t)u_arg,
		    callp->sy_narg)) {
			u_error = EFAULT;
			goto bad;
		}
	}
	u_ap = u_arg;
	u_r.r_val1 = 0;
	u_r.r_val2 = regs.r_dreg[1];
	/*
	 * Syscall_setjmp is a special setjmp that only saves a6 and sp.
	 * The result is a significant speedup of this critical path,
	 * but meanwhile all the register variables have the wrong
	 * values after a longjmp returns here.
	 * This is the reason for the limited scope of the register
	 * variables in this routine - the values may go away here.
	 */
	/*
	 *	SUN swapped JUSTRETURN and NORMALRETURN - we swap
	 *	them back.
	 */
	if (syscall_setjmp(&u_qsave)) {
		if (u_error == 0 && u_eosys != RESTARTSYS)
			u_error = EINTR;
	} else {
		u_eosys = NORMALRETURN;
#ifdef	SYSCALLTRACE
		if (syscalltrace &&
		    (syscalltrace < 0 || syscalltrace == u_procp->p_pid))
		syscalltracing = 1;
		if (syscalltracing) {
			register int i;
			char *cp;

			if (code >= nsysent || code < 0)
				printf("[%d]<%d>#%d",
					u_procp->p_pid, code, callp->sy_narg);
/*			else
				printf("[%d]<%s>#%d",
					u_procp->p_pid, syscallnames[code], callp->sy_narg);
*/			cp = "(";
			for (i= 0; i < callp->sy_narg && i < 6; i++) {
				printf("%s%x", cp, u_arg[i]);
				cp = ", ";
			}
			printf(")" );
		}
#endif
		XPR(XPR_SYSCALLS, ("syscall start: %c%c%c%c%c%c\n",
			u_comm[0], u_comm[1], u_comm[2],
			u_comm[3], u_comm[4], u_comm[5]));
		XPR(XPR_SYSCALLS, 
		("syscall start %d: args=0x%x, 0x%x, 0x%x, 0x%x\n", 
			code, u_arg[0], u_arg[1], u_arg[2],
			u_arg[3], u_arg[4]));
#if	MACH_RFS
		/*
		 *  Remember the system call we are executing so that it
		 *  can be handled remotely if need be.
		 */
		u_rfsncnt = 0;
		u_rfscode = code;
#endif	MACH_RFS
#if	VICE
		u_rmt_ncnt = 0;
		u_rmt_code = code;
#endif	VICE
		/*
		 *  Show no resource pause conditions (except for a possible
		 *  polled pause in the process of being retried).
		 */
		u_rpswhich &= URPW_NOTIFY;
		u_rpsfs = 0;
		(*(callp->sy_call))(u_ap);
	}
	/* end of scope of register variables above */
	}
#if	MACH_RFS
	u_rfscode = 0;
#endif	MACH_RFS
#if	VICE
	u_rmt_code = 0;
#endif	VICE
	if (u_error)
	switch (u_error)
	{
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
	    case ERFSREMOTE:
		u_error = 0;
		break;
#endif	MACH_RFS
#if	VICE
	    case EVICEOP:
		u_error = 0;
		break;
#endif	VICE
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
		    u_eosys = RESTARTSYS;
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
	/*
	 *	Sun swapped JUSTRETURN and NORMALRETURN
	 */
	if (u_eosys == RESTARTSYS)
		regs.r_pc -= 2;	/* re-execute TRAP #0 */
	else if (u_eosys == NORMALRETURN) {
		regs.r_sp += sizeof (int);	/* pop syscall # */
		if (u_error) {
bad:
#ifdef	SYSCALLTRACE
			if (syscalltracing)
				printf(":: error=%d\n", u_error);
#endif
			regs.r_dreg[0] = u_error;
			regs.r_sr |= SR_CC;	/* carry bit */
		} else {
#ifdef	SYSCALLTRACE
			if (syscalltracing)
				printf(":: r0 = %x, r1 = %x\n",
					u_r.r_val1, u_r.r_val2);
#endif
			regs.r_sr &= ~SR_CC;
			regs.r_dreg[0] = u_r.r_val1;
			regs.r_dreg[1] = u_r.r_val2;
		}
#ifdef	SYSCALLTRACE
		if (syscalltracing) {
			syscalltracing = 0;
			if (syscallhalt++ > 1000) {
				halt("1000 syscalls");
				syscallhalt = 0;
			}
		}
#endif
	}
out:
	if (current_thread()->pcb->pcb_flag & TRACE_PENDING)
		dotrace(&regs);
	XPR(XPR_SYSCALLS, 
		("syscall end: pid=%d, code=%d, dreg0=%d, dreg1=%d\n",
		u_procp->p_pid, code, regs.r_dreg[0], regs.r_dreg[1]));
	{
	/* scope for use of register variable p */
	register struct proc *p;

	p = u_procp;
	if (CHECK_SIGNALS(p, current_thread(), uthread)) {
		if (p->p_cursig || issig())
			psig();
	}
	if (csw_needed(current_thread(),current_processor())) {
		u_ru.ru_nivcsw++;
		thread_block();
	}
	if (syst_flag) {
		int ticks;
		struct timeval *tv = &u_ru.ru_stime;

		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks)
			addupc(regs.r_pc, &u_prof, ticks);
	}
	}
}

/*
 * Indirect system call.
 * Used to be handled above, in syscall, but then everyone
 * was paying a performance penalty for this rarely-used
 * (and questionable) feature.
 */
indir()
{
	register int code, i;
	register struct sysent *callp;

	code = u.u_arg[0];
	/*
	 *	CMU system calls have negative numbers
	 */
	if (code < 0) {
		if (code < -ncmusysent)
			callp = &sysent[63];	/* undefined */
		else
			callp = &cmusysent[code + ncmusysent];
	}
	else
		callp = (code == 0 || code >= nsysent) ? &sysent[63]
							: &sysent[code];
	if (i = callp->sy_narg) {
		if (fulwds((caddr_t)u.u_ar0[SP] + 3*NBPW, (caddr_t)u.u_arg,
		    i)) {
			u.u_error = EFAULT;
			return;
		}
	}
#if	MACH_RFS
	/*
	 *  Remember the system call we are executing so that it
	 *  can be handled remotely if need be. 
	 *  Note that code has changed since indir() was called.
	 */
	u.u_rfsncnt = 0;
	u.u_rfscode = code;
#endif	MACH_RFS
#if	VICE
	u.u_rmt_ncnt = 0;
	u.u_rmt_code = code;
#endif	VICE
	(*(callp->sy_call))(u.u_ap);
}

#if	MACH_EMULATION
/*
 * honest-to-god_unix_syscall: 
 *
 * Calls the indicated syscall, passing the given args and returning
 * result(s), error and eosys in rv.  htg_unix_syscall() handles any machine
 * dependent argument passing conventions, letting the machine independent
 * htg_unix_syscall_common() routine do most of the work.  It is intended to
 * be a general way of providing kernel syscall services in an emulation
 * environment (for when it absolutely, positively has to be a syscall).
 */
kern_return_t
htg_unix_syscall(code, argv, rv)
	int		code;		/* syscall # */
	caddr_t		* argv;		/* arg vector */
	syscall_val_t 	* rv;
{
	extern kern_return_t htg_unix_syscall_common();
	register kern_return_t kr;
	register struct proc *p;

	switch (code) {
	/*
	 * Handle syscalls with bizarre parameter passing mechanisms.
	 * Instead of passing parameters in registers, use extra parameters
	 * passed in the htg_unix_syscall() argument lists.
	 */
	case SYS_wait:
		u.u_ar0[PS] |= PSL_ALLCC;	/* Always wait3() */
		if (copyin(argv+0, (caddr_t)&u.u_ar0[R0], NBPW) ||
		    copyin(argv+1, (caddr_t)&u.u_ar0[R1], NBPW)) {
			return KERN_INVALID_ADDRESS;
		}
		break;

	case SYS_sigreturn:
	case 139:	/* osigcleanup */
		/*
		 * osigcleanup() expects a sigcontext ptr at 4(sp).
		 * Ok to poke saved sp since osigcleanup() later sets it.
		 */
		u.u_ar0[SP] = (int)argv - NBPW;
		break;

	default:
		break;
	}

	kr = htg_unix_syscall_common(code, argv, rv);
	if (kr != KERN_ABORTED) {
		/*
		 * Store correct register values before signal processing
		 */
		u.u_ar0[R0] = kr; /* Return kr when not JUSTRETURN semantics */
		u.u_ar0[SP] += NBPW;	/* Pop syscall # from stack */
	}

	p = u.u_procp;
	if (p) {
		if (CHECK_SIGNALS(p, current_thread(),
				  current_thread()->u_address.uthread)) {
			unix_master();
			if (p->p_cursig || issig()) {
				psig();
			}
			unix_release();
		}
	}

	u.u_ar0[SP] -= NBPW;	/* "push" sp so space for syscall #
				   can be "popped" in syscall() */
	return u.u_ar0[R0];
}
#endif	MACH_EMULATION

/*
 * nonexistent system call-- signal process (may want to handle it)
 * flag error if process won't see signal immediately
 * Q: should we do that all the time ??
 */
nosys()
{

	if (u.u_signal[SIGSYS] == SIG_IGN || u.u_signal[SIGSYS] == SIG_HOLD)
		u.u_error = EINVAL;
	thread_doexception(current_thread(), EXC_SOFTWARE,
		EXC_UNIX_BAD_SYSCALL, 0);
}

/*
 *	Set up pointers to simulate system call trap and load initial
 *	program.
 */
sun_load_init_program(regs)
	struct regs	regs;
{
	extern vm_size_t vm_page_free_count;

	u.u_ar0 = &regs.r_dreg[0];
	current_thread()->pcb->user_regs = (struct sun_saved_state *)&regs;
	load_init_program();
	printf("SPACE FREE: before /etc/init = %x[%d]\n",
		vm_page_free_count, vm_page_free_count);
}

/*
 * Handle trace traps, both real and delayed.
 */
dotrace(locregs)
	struct regs *locregs;
{
	register int r, s;
	struct proc *p = u.u_procp;

	s = spl6();
	r = current_thread()->pcb->pcb_flag&AST_CLR;
	current_thread()->pcb->pcb_flag &= ~AST_CLR;
	u.u_ar0[PS] &= ~PSL_T;
	(void) splx(s);
	if (r & TRACE_AST) {
		if (thread_should_halt(current_thread()))
			thread_halt_self();

		if ((p->p_flag&SOWEUPC) && u.u_prof.pr_scale) {
			addupc(locregs->r_pc, &u.u_prof, 1);
			p->p_flag &= ~SOWEUPC;
		}
		if ((r & TRACE_USER) == 0)
			return;
	}
	thread_doexception(current_thread(), EXC_BREAKPOINT,
	    EXC_SUN3_TRACE, 0);
}

/*
 * Print out a traceback for kernel traps
 */
traceback(afp, sp)
	long afp, sp;
{
	u_int tospage = btoc(sp);
	struct frame *fp = (struct frame *)afp;
	static int done = 0;

	if (panicstr && done++ > 0)
		return;

	printf("Begin traceback...fp = %x, sp = %x\n", fp, sp);
	while (btoc(fp) == tospage) {
		if (fp == fp->fr_savfp) {
			printf("FP loop at %x", fp);
			break;
		}
		printf("Called from %x, fp=%x, args=%x %x %x %x\n",
		    fp->fr_savpc, fp->fr_savfp,
		    fp->fr_arg[0], fp->fr_arg[1], fp->fr_arg[2], fp->fr_arg[3]);
		fp = fp->fr_savfp;
	}
	printf("End traceback...\n");
	DELAY(2000000);
}

showregs(str, type, locregs, fmtp, be)
	char *str;
	int type;
	struct regs *locregs;
	struct stkfmt *fmtp;
{
	int *r, s;
	int fcode, accaddr;
	char *why;

	s = spl7();
	printf("%s: %s\n", current_thread() ? u.u_comm : "nemo", str ? str : "");
	printf(
	"trap address 0x%x, pid %d, pc = %x, sr = %x, stkfmt %x, context %x\n",
	    fmtp->f_vector, current_thread() ? u.u_procp->p_pid : 0, locregs->r_pc, locregs->r_sr,
	    fmtp->f_stkfmt, getcontext());
	type &= ~USER;
	if (type == T_BUSERR)
		printf("Bus Error Reg %b\n", be, BUSERR_BITS);
	if (type == T_BUSERR || type == T_ADDRERR) {
		switch (fmtp->f_stkfmt) {
		case SF_MEDIUM: {
			struct bei_medium *beip =
			    (struct bei_medium *)&fmtp->f_beibase;

			fcode = beip->bei_fcode;
			if (beip->bei_dfault) {
				why = "data";
				accaddr = beip->bei_fault;
			} else if (beip->bei_faultc) {
				why = "stage c";
				accaddr = locregs->r_pc+2;
			} else if (beip->bei_faultb) {
				why = "stage b";
				accaddr = locregs->r_pc+4;
			} else {
				why = "unknown";
				accaddr = 0;
			}
			printf("%s fault address %x faultc %d faultb %d ",
			    why, accaddr, beip->bei_faultc, beip->bei_faultb);
			printf("dfault %d rw %d size %d fcode %d\n",
			    beip->bei_dfault, beip->bei_rw,
			    beip->bei_size, fcode);
			break;
			}
		case SF_LONGB: {
			struct bei_longb *beip =
			    (struct bei_longb *)&fmtp->f_beibase;

			fcode = beip->bei_fcode;
			if (beip->bei_dfault) {
				why = "data";
				accaddr = beip->bei_fault;
			} else if (beip->bei_faultc) {
				why = "stage c";
				accaddr = beip->bei_stageb-2;
			} else if (beip->bei_faultb) {
				why = "stage b";
				accaddr = beip->bei_stageb;
			} else {
				why = "unknown";
				accaddr = 0;
			}
			printf("%s fault address %x faultc %d faultb %d ",
			    why, accaddr, beip->bei_faultc, beip->bei_faultb);
			printf("dfault %d rw %d size %d fcode %d\n",
			    beip->bei_dfault, beip->bei_rw,
			    beip->bei_size, fcode);
			break;
			}
		default:
			panic("bad bus error stack format");
		}
		if (fcode == FC_SD || fcode == FC_SP) {
			printf("KERNEL MODE\n");
			printf("page map %x\n", getpgmap((caddr_t)accaddr));
		} else {
		}
	}
	r = &locregs->r_dreg[0];
	printf("D0-D7  %x %x %x %x %x %x %x %x\n",
	    r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7]);
	r = &locregs->r_areg[0];
	printf("A0-A7  %x %x %x %x %x %x %x %x\n",
	    r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7]);
	DELAY(2000000);
	(void) splx(s);
}

/*
 * Handle page fault for 68020 running Mach
 * Returns 1 if successful
 */
kern_return_t pagefault(faultaddr, faulttype, regs)
register int		faultaddr;
vm_prot_t		faulttype;
register struct regs	*regs;
{
	int		i = 0;
	vm_map_t	first_map;
	vm_map_t	second_map;
	vm_offset_t	recover;
	kern_return_t	result;

	if (current_thread() != THREAD_NULL) {
		i = u.u_error;
		u.u_error = 0;
	}
	/*
	 *	Determine which map to "fault" on.
	 *	If the faulting address is a kernel
	 *	address, make sure we were executing
	 *	in kernel mode.
	 */
	second_map = VM_MAP_NULL;
	if (((vm_offset_t)faultaddr >= KERNELBASE) &&
		!USERMODE(regs->r_sr)) {
		if (current_task()->kernel_vm_space) {
			first_map = current_task()->map;
			second_map = kernel_map;
		} else {
			first_map = kernel_map;
		}
	}
	else {
		first_map = current_task()->map;
	}

	result = vm_fault(first_map,
		trunc_page((vm_offset_t)faultaddr), faulttype,FALSE);

	if ((result != KERN_SUCCESS) && (second_map != VM_MAP_NULL))
		result = vm_fault(second_map,
			trunc_page((vm_offset_t)faultaddr), faulttype,FALSE);

	/*
	 *	Check for halting now, because the route out of the kernel
	 *	doesn't check at all.
	 */

	if (thread_should_halt(current_thread()) && result == KERN_SUCCESS &&
		!USERMODE(regs->r_sr))
			result = KERN_FAILURE;

	if (current_thread() != THREAD_NULL)
		u.u_error = i;
	return(result);
}

/*
 *      This handles a mach syscall (one whose number is less than the cmu
 *      extra syscalls in this implementation).
 */
   
do_mach_syscall(info, locregs)
	register info;
	struct regs *locregs;
{
	int syscall_no, nargs, retval;
	register mach_trap_t	*trap_entry;
     
	/*
	 *	Index into table is positive
	 */
	syscall_no = -info;
	trap_entry = &mach_trap_table[syscall_no];

	/*
	 *	Get the number of arguments from the table, and
	 *	copy them into u.u_arg.  Undo the VAX-specific
	 *	hackery.
	 */
	nargs = (trap_entry->mach_trap_length - 1) / 4;
	if (nargs) {
		if (fulwds((caddr_t)locregs->r_sp + 2 * NBPW, (caddr_t)u.u_arg,
		    nargs)) {
			u.u_error = EFAULT;
			return(-1);
		}
	}
	/*
	 *	Call as a normal function.... since C can't
	 *	push a variable number of arguments on the stack,
	 *	we have to push all possible arguments (7 at the
	 *	moment).
	 */
	/*
	 *	XXX - this doesn't deal with routines that want
	 *	to be exited if a signal happens... but at the
	 *	moment there aren't any! (see syscall_sw.c)
	 */
	retval = (*(trap_entry->mach_trap_function))(u.u_arg[0],
			u.u_arg[1], u.u_arg[2], u.u_arg[3],
			u.u_arg[4], u.u_arg[5], u.u_arg[6]);

	return(retval);
}

#if	NFPA > 0
/*
 *	Initialize FPA
 *
 *	Enable FPA, allocate an FPA context, initialize FPA state
 *	in pcb and FPA itself, and do a destructive FPA RAM test.
 *	Return 0 if successful.
 */
fpa_init(thread)
	thread_t	thread;
{
	register struct pcb		*pcb;
	register struct fpa_device	*rfpa = fpa;

	pcb = thread->pcb;	
	pcb->pcb_fpa_status.fpas_state = fpa_alloc_context();
	if (pcb->pcb_fpa_flags & FPA_CTX_SAVED) {
		/*
		 *	Have old state saved in pcb, so do a full restore
		 */
		fpa_restore(thread, 1);
		pcb->pcb_fpa_flags = FPA_USED;
		return(0);
	}
	else {
		/*
		 *	No old state saved, so start from scratch
		 */
		on_enablereg((u_char)ENA_FPA);	/* Enable FPA */
		pcb->pcb_fpa_flags = FPA_USED;
		pcb->pcb_fpa_fmtptr = NULL;
		pcb->pcb_fpa_pc = 0;
		/* init FPA regs */
		rfpa->fp_clear_pipe = 0; /* clear FPA pipe before write to STATE reg */
		rfpa->fp_state = pcb->pcb_fpa_status.fpas_state;
		/*
		 * Do a destructive RAM test if in 
		 * FPA_MULTI_USER state
		 */
		if (fpa_state == FPA_MULTI_USER) {
			rfpa->fp_restore_mode3_0 = 
					FPA_MODE3_INITVAL;
			if (fparamtest() < 0) {
				printf("FPA RAM test fails, FPA is shutdown!\n");
			 /* if RAM test fails, shut down FPA */
				fpa_shutdown();
			}
		}
		rfpa->fp_imask = rfpa->fp_ierr = rfpa->fp_load_ptr = 0;
		/*
		 *	FPA RAM test successful so return 0.
		 *	Otherwise, return 1 for error.
		 */
		if (fpa_state != FPA_DISABLED)
			return(0);
		else
			return(1);
	}
}
#endif	NFPA > 0
