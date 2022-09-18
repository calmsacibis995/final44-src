h43829
s 00001/00001/00901
d D 8.5 93/12/06 20:25:57 akito 12 11
c sync up tp hp300/hp300/trap.c   8.4 (Berkeley) 9/23/93
e
s 00009/00009/00893
d D 8.4 93/09/23 16:43:01 bostic 11 10
c changes for 4.4BSD-Lite requested by USL
e
s 00004/00004/00898
d D 8.3 93/09/21 07:59:17 bostic 10 9
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00001/00901
d D 8.2 93/09/05 09:46:16 mckusick 9 8
c curpri => curpriority
e
s 00002/00002/00900
d D 8.1 93/06/16 16:47:43 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00898
d D 7.6 93/06/16 16:47:18 mckusick 7 5
c indir => syscall; __indir => __syscall
e
s 00002/00002/00900
d R 8.1 93/06/10 22:26:57 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00368/00000/00534
d D 7.5 93/05/12 04:13:16 akito 5 4
c LUNA-II (68040 based LUNA) support
e
s 00014/00031/00520
d D 7.4 93/01/02 13:48:58 akito 4 3
c sync up to hp300/hp300/trap.c   7.26
e
s 00018/00018/00533
d D 7.3 92/10/11 11:07:56 bostic 3 2
c make kernel includes standard
e
s 00145/00118/00406
d D 7.2 92/07/23 16:01:33 fujita 2 1
c update for 4.4BSD-alpha distribution
e
s 00524/00000/00000
d D 7.1 92/06/15 06:38:51 fujita 1 0
c date and time created 92/06/15 06:38:51 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992 OMRON Corporation.
D 8
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: trap.c 1.35 91/12/26$
D 4
 * OMRON: $Id: trap.c,v 1.2 92/06/14 06:23:41 moti Exp $
E 4
I 4
D 12
 * from: hp300/hp300/trap.c	7.26 (Berkeley) 12/27/92
E 12
I 12
 * from: hp300/hp300/trap.c	8.4 (Berkeley) 9/23/93
E 12
E 4
 *
D 2
 * from: hp300/hp300/trap.c	7.20 (Berkeley) 6/5/92
E 2
I 2
D 4
 * from: hp300/hp300/trap.c     7.23 (Berkeley) 7/9/92
E 2
 *
E 4
 *	%W% (Berkeley) %G%
 */

D 3
#include "param.h"
#include "systm.h"
#include "proc.h"
#include "acct.h"
#include "kernel.h"
#include "signalvar.h"
#include "resourcevar.h"
I 2
#include "syscall.h"
E 2
#include "syslog.h"
#include "user.h"
E 3
I 3
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/acct.h>
#include <sys/kernel.h>
#include <sys/signalvar.h>
#include <sys/resourcevar.h>
#include <sys/syscall.h>
#include <sys/syslog.h>
#include <sys/user.h>
E 3
#ifdef KTRACE
D 3
#include "ktrace.h"
E 3
I 3
#include <sys/ktrace.h>
E 3
#endif

D 3
#include "../include/psl.h"
#include "../include/trap.h"
#include "../include/cpu.h"
#include "../include/reg.h"
#include "../include/mtpr.h"
E 3
I 3
#include <machine/psl.h>
#include <machine/trap.h>
#include <machine/cpu.h>
#include <machine/reg.h>
#include <machine/mtpr.h>
E 3

D 3
#include "vm/vm.h"
#include "vm/pmap.h"
E 3
I 3
#include <vm/vm.h>
#include <vm/pmap.h>
E 3

struct	sysent	sysent[];
int	nsysent;

char	*trap_type[] = {
	"Bus error",
	"Address error",
	"Illegal instruction",
	"Zero divide",
	"CHK instruction",
	"TRAPV instruction",
	"Privilege violation",
	"Trace trap",
	"MMU fault",
	"SSIR trap",
	"Format error",
	"68881 exception",
	"Coprocessor violation",
	"Async system trap"
};
#define	TRAP_TYPES	(sizeof trap_type / sizeof trap_type[0])

/*
 * Size of various exception stack frames (minus the standard 8 bytes)
 */
short	exframesize[] = {
	FMT0SIZE,	/* type 0 - normal (68020/030/040) */
	FMT1SIZE,	/* type 1 - throwaway (68020/030/040) */
	FMT2SIZE,	/* type 2 - normal 6-word (68020/030/040) */
	FMT3SIZE,	/* type 3 - FP post-instruction (68040) */
	-1, -1, -1,	/* type 4-6 - undefined */
	FMT7SIZE,	/* type 7 - access error (68040) */
	58,		/* type 8 - bus fault (68010) */
	FMT9SIZE,	/* type 9 - coprocessor mid-instruction (68020/030) */
	FMTASIZE,	/* type A - short bus fault (68020/030) */
	FMTBSIZE,	/* type B - long bus fault (68020/030) */
	-1, -1, -1, -1	/* type C-F - undefined */
};

I 5
#ifdef LUNA2
#define KDFAULT(c)	(mmutype == MMU_68040 ? \
			    ((c) & SSW4_TMMASK) == SSW4_TMKD : \
			    ((c) & (SSW_DF|FC_SUPERD)) == (SSW_DF|FC_SUPERD))
#define WRFAULT(c) 	(mmutype == MMU_68040 ? \
			    ((c) & SSW4_RW) == 0 : \
			    ((c) & (SSW_DF|SSW_RW)) == SSW_DF)
#else
E 5
#define KDFAULT(c)	(((c) & (SSW_DF|SSW_FCMASK)) == (SSW_DF|FC_SUPERD))
#define WRFAULT(c)	(((c) & (SSW_DF|SSW_RW)) == SSW_DF)
I 5
#endif
E 5

#ifdef DEBUG
int mmudebug = 0;
int mmupid = -1;
#define MDB_FOLLOW	1
#define MDB_WBFOLLOW	2
#define MDB_WBFAILED	4
#define MDB_ISPID(p)	(p) == mmupid
#endif

/*
I 2
 * trap and syscall both need the following work done before returning
 * to user mode.
 */
static inline void
userret(p, fp, oticks, faultaddr, fromtrap)
	register struct proc *p;
	register struct frame *fp;
	u_quad_t oticks;
	u_int faultaddr;
	int fromtrap;
{
	int sig, s;
I 5
#ifdef LUNA2
	int beenhere = 0;
E 5

I 5
again:
#endif
E 5
	/* take pending signals */
	while ((sig = CURSIG(p)) != 0)
D 11
		psig(sig);
	p->p_pri = p->p_usrpri;
E 11
I 11
		postsig(sig);
	p->p_priority = p->p_usrpri;
E 11
	if (want_resched) {
		/*
		 * Since we are curproc, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 10
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 10
I 10
		 * If that happened after we put ourselves on the run queue
D 11
		 * but before we swtch()'ed, we might not be on the queue
E 11
I 11
		 * but before we switched, we might not be on the queue
E 11
		 * indicated by our priority.
E 10
		 */
		s = splstatclock();
D 10
		setrq(p);
E 10
I 10
		setrunqueue(p);
E 10
		p->p_stats->p_ru.ru_nivcsw++;
D 11
		swtch();
E 11
I 11
		mi_switch();
E 11
		splx(s);
		while ((sig = CURSIG(p)) != 0)
D 11
			psig(sig);
E 11
I 11
			postsig(sig);
E 11
	}

	/*
	 * If profiling, charge system time to the trapped pc.
	 */
D 4
	if (p->p_flag & SPROFIL)
		addupc_intr(p, fp->f_pc, (int)(p->p_sticks - oticks));
#ifdef HP380
	/*
	 * Deal with user mode writebacks (from trap, or from sigreturn).
	 * If any writeback fails, go back and attempt signal delivery.
	 * unless we have already been here and attempted the writeback
	 * (e.g. bad address with user ignoring SIGSEGV).  In that case
	 * we just return to the user without sucessfully completing
	 * the writebacks.  Maybe we should just drop the sucker?
	 */
	if (mmutype == MMU_68040 && fp->f_format == FMT7) {
		if (beenhere) {
#ifdef DEBUG
			if (mmudebug & MDB_WBFAILED)
				printf(fromtrap ?
		"pid %d(%s): writeback aborted, pc=%x, fa=%x\n" :
		"pid %d(%s): writeback aborted in sigreturn, pc=%x\n",
				    p->p_pid, p->p_comm, fp->f_pc, faultaddr);
#endif
		} else if (sig = writeback(fp, fromtrap)) {
			beenhere = 1;
			oticks = p->p_sticks;
			trapsignal(p, sig, faultaddr);
			goto again;
		}
E 4
I 4
D 11
	if (p->p_flag & SPROFIL) {
E 11
I 11
	if (p->p_flag & P_PROFIL) {
E 11
		extern int psratio;

		addupc_task(p, fp->f_pc,
			    (int)(p->p_sticks - oticks) * psratio);
E 4
	}
I 5
#ifdef LUNA2
	/*
	 * Deal with user mode writebacks (from trap, or from sigreturn).
	 * If any writeback fails, go back and attempt signal delivery.
	 * unless we have already been here and attempted the writeback
	 * (e.g. bad address with user ignoring SIGSEGV).  In that case
	 * we just return to the user without sucessfully completing
	 * the writebacks.  Maybe we should just drop the sucker?
	 */
	if (mmutype == MMU_68040 && fp->f_format == FMT7) {
		if (beenhere) {
#ifdef DEBUG
			if (mmudebug & MDB_WBFAILED)
				printf(fromtrap ?
		"pid %d(%s): writeback aborted, pc=%x, fa=%x\n" :
		"pid %d(%s): writeback aborted in sigreturn, pc=%x\n",
				    p->p_pid, p->p_comm, fp->f_pc, faultaddr);
#endif
		} else if (sig = writeback(fp, fromtrap)) {
			beenhere = 1;
			oticks = p->p_sticks;
			trapsignal(p, sig, faultaddr);
			goto again;
		}
	}
#endif
E 5
D 4
#endif
E 4
D 9
	curpri = p->p_pri;
E 9
I 9
D 11
	curpriority = p->p_pri;
E 11
I 11
	curpriority = p->p_priority;
E 11
E 9
}

/*
E 2
 * Trap is called from locore to handle most types of processor traps,
 * including events such as simulated software interrupts/AST's.
 * System calls are broken out for efficiency.
 */
/*ARGSUSED*/
trap(type, code, v, frame)
	int type;
	unsigned code;
	register unsigned v;
	struct frame frame;
{
	register int i;
D 2
	unsigned ucode = 0;
	register struct proc *p = curproc;
	struct timeval syst;
E 2
I 2
	unsigned ucode;
	register struct proc *p;
	u_quad_t sticks;
E 2
	unsigned ncode;
D 2
	int s;
E 2
I 2
	extern char fswintr[];
E 2

	cnt.v_trap++;
D 2
	syst = p->p_stime;
E 2
I 2
	p = curproc;
	ucode = 0;
E 2
	if (USERMODE(frame.f_sr)) {
		type |= T_USER;
I 2
		sticks = p->p_sticks;
E 2
		p->p_md.md_regs = frame.f_regs;
	}
	switch (type) {

	default:
dopanic:
		printf("trap type %d, code = %x, v = %x\n", type, code, v);
D 4
		regdump(frame.f_regs, 128);
E 4
I 4
		regdump(&frame, 128);
E 4
		type &= ~T_USER;
		if ((unsigned)type < TRAP_TYPES)
			panic(trap_type[type]);
		panic("trap");

	case T_BUSERR:		/* kernel bus error */
		if (!p->p_addr->u_pcb.pcb_onfault)
			goto dopanic;
		/*
		 * If we have arranged to catch this fault in any of the
		 * copy to/from user space routines, set PC to return to
		 * indicated location and set flag informing buserror code
		 * that it may need to clean up stack frame.
		 */
copyfault:
		frame.f_stackadj = exframesize[frame.f_format];
		frame.f_format = frame.f_vector = 0;
		frame.f_pc = (int) p->p_addr->u_pcb.pcb_onfault;
		return;

	case T_BUSERR|T_USER:	/* bus error */
	case T_ADDRERR|T_USER:	/* address error */
		ucode = v;
		i = SIGBUS;
		break;

#ifdef FPCOPROC
	case T_COPERR:		/* kernel coprocessor violation */
#endif
	case T_FMTERR|T_USER:	/* do all RTE errors come in as T_USER? */
	case T_FMTERR:		/* ...just in case... */
	/*
	 * The user has most likely trashed the RTE or FP state info
	 * in the stack frame of a signal handler.
	 */
		type |= T_USER;
		printf("pid %d: kernel %s exception\n", p->p_pid,
		       type==T_COPERR ? "coprocessor" : "format");
		p->p_sigacts->ps_sigact[SIGILL] = SIG_DFL;
		i = sigmask(SIGILL);
		p->p_sigignore &= ~i;
		p->p_sigcatch &= ~i;
		p->p_sigmask &= ~i;
		i = SIGILL;
		ucode = frame.f_format;	/* XXX was ILL_RESAD_FAULT */
		break;

#ifdef FPCOPROC
	case T_COPERR|T_USER:	/* user coprocessor violation */
	/* What is a proper response here? */
		ucode = 0;
		i = SIGFPE;
		break;

	case T_FPERR|T_USER:	/* 68881 exceptions */
	/*
	 * We pass along the 68881 status register which locore stashed
	 * in code for us.  Note that there is a possibility that the
	 * bit pattern of this register will conflict with one of the
	 * FPE_* codes defined in signal.h.  Fortunately for us, the
	 * only such codes we use are all in the range 1-7 and the low
	 * 3 bits of the status register are defined as 0 so there is
	 * no clash.
	 */
		ucode = code;
		i = SIGFPE;
		break;
#endif

I 5
#ifdef LUNA2
	case T_FPEMULI|T_USER:	/* unimplemented FP instuction */
	case T_FPEMULD|T_USER:	/* unimplemented FP data type */
		/* XXX need to FSAVE */
		printf("pid %d(%s): unimplemented FP %s at %x (EA %x)\n",
		       p->p_pid, p->p_comm,
		       frame.f_format == 2 ? "instruction" : "data type",
		       frame.f_pc, frame.f_fmt2.f_iaddr);
		/* XXX need to FRESTORE */
		i = SIGFPE;
		break;
#endif

E 5
	case T_ILLINST|T_USER:	/* illegal instruction fault */
	case T_PRIVINST|T_USER:	/* privileged instruction fault */
		ucode = frame.f_format;	/* XXX was ILL_PRIVIN_FAULT */
		i = SIGILL;
		break;

	case T_ZERODIV|T_USER:	/* Divide by zero */
		ucode = frame.f_format;	/* XXX was FPE_INTDIV_TRAP */
		i = SIGFPE;
		break;

	case T_CHKINST|T_USER:	/* CHK instruction trap */
		ucode = frame.f_format;	/* XXX was FPE_SUBRNG_TRAP */
		i = SIGFPE;
		break;

	case T_TRAPVINST|T_USER:	/* TRAPV instruction trap */
		ucode = frame.f_format;	/* XXX was FPE_INTOVF_TRAP */
		i = SIGFPE;
		break;

	/*
	 * XXX: Trace traps are a nightmare.
	 *
	 *	HP-UX uses trap #1 for breakpoints,
	 *	HPBSD uses trap #2,
	 *	SUN 3.x uses trap #15,
	 *	KGDB uses trap #15 (for kernel breakpoints; handled elsewhere).
	 *
	 * HPBSD and HP-UX traps both get mapped by locore.s into T_TRACE.
	 * SUN 3.x traps get passed through as T_TRAP15 and are not really
	 * supported yet.
	 */
	case T_TRACE:		/* kernel trace trap */
	case T_TRAP15:		/* SUN trace trap */
		frame.f_sr &= ~PSL_T;
		i = SIGTRAP;
		break;

	case T_TRACE|T_USER:	/* user trace trap */
	case T_TRAP15|T_USER:	/* SUN user trace trap */
		frame.f_sr &= ~PSL_T;
		i = SIGTRAP;
		break;

	case T_ASTFLT:		/* system async trap, cannot happen */
		goto dopanic;

	case T_ASTFLT|T_USER:	/* user async trap */
		astpending = 0;
		/*
		 * We check for software interrupts first.  This is because
		 * they are at a higher level than ASTs, and on a VAX would
		 * interrupt the AST.  We assume that if we are processing
		 * an AST that we must be at IPL0 so we don't bother to
		 * check.  Note that we ensure that we are at least at SIR
		 * IPL while processing the SIR.
		 */
		spl1();
		/* fall into... */

	case T_SSIR:		/* software interrupt */
	case T_SSIR|T_USER:
		if (ssir & SIR_NET) {
			siroff(SIR_NET);
			cnt.v_soft++;
			netintr();
		}
		if (ssir & SIR_CLOCK) {
			siroff(SIR_CLOCK);
			cnt.v_soft++;
D 2
			softclock((caddr_t)frame.f_pc, (int)frame.f_sr);
E 2
I 2
			softclock();
E 2
		}
		/*
		 * If this was not an AST trap, we are all done.
		 */
		if (type != (T_ASTFLT|T_USER)) {
			cnt.v_trap--;
			return;
		}
		spl0();
D 2
#ifndef PROFTIMER
		if ((p->p_flag&SOWEUPC) && p->p_stats->p_prof.pr_scale) {
			addupc(frame.f_pc, &p->p_stats->p_prof, 1);
E 2
I 2
D 11
		if (p->p_flag & SOWEUPC) {
E 2
			p->p_flag &= ~SOWEUPC;
E 11
I 11
		if (p->p_flag & P_OWEUPC) {
			p->p_flag &= ~P_OWEUPC;
E 11
I 2
			ADDUPROF(p);
E 2
		}
D 2
#endif
E 2
		goto out;

	case T_MMUFLT:		/* kernel mode page fault */
I 2
		/*
		 * If we were doing profiling ticks or other user mode
		 * stuff from interrupt code, Just Say No.
		 */
		if (p->p_addr->u_pcb.pcb_onfault == fswintr)
			goto copyfault;
E 2
		/* fall into ... */

	case T_MMUFLT|T_USER:	/* page fault */
	    {
		register vm_offset_t va;
		register struct vmspace *vm = p->p_vmspace;
		register vm_map_t map;
		int rv;
		vm_prot_t ftype;
		extern vm_map_t kernel_map;

#ifdef DEBUG
		if ((mmudebug & MDB_WBFOLLOW) || MDB_ISPID(p->p_pid))
		printf("trap: T_MMUFLT pid=%d, code=%x, v=%x, pc=%x, sr=%x\n",
		       p->p_pid, code, v, frame.f_pc, frame.f_sr);
#endif
		/*
		 * It is only a kernel address space fault iff:
		 * 	1. (type & T_USER) == 0  and
		 * 	2. pcb_onfault not set or
		 *	3. pcb_onfault set but supervisor space data fault
		 * The last can occur during an exec() copyin where the
		 * argument space is lazy-allocated.
		 */
		if (type == T_MMUFLT &&
		    (!p->p_addr->u_pcb.pcb_onfault || KDFAULT(code)))
			map = kernel_map;
		else
			map = &vm->vm_map;
		if (WRFAULT(code))
			ftype = VM_PROT_READ | VM_PROT_WRITE;
		else
			ftype = VM_PROT_READ;
		va = trunc_page((vm_offset_t)v);
#ifdef DEBUG
		if (map == kernel_map && va == 0) {
			printf("trap: bad kernel access at %x\n", v);
			goto dopanic;
		}
#endif
		rv = vm_fault(map, va, ftype, FALSE);
#ifdef DEBUG
		if (rv && MDB_ISPID(p->p_pid))
			printf("vm_fault(%x, %x, %x, 0) -> %x\n",
			       map, va, ftype, rv);
#endif
		/*
		 * If this was a stack access we keep track of the maximum
		 * accessed stack size.  Also, if vm_fault gets a protection
		 * failure it is due to accessing the stack region outside
		 * the current limit and we need to reflect that as an access
		 * error.
		 */
		if ((caddr_t)va >= vm->vm_maxsaddr && map != kernel_map) {
			if (rv == KERN_SUCCESS) {
				unsigned nss;

				nss = clrnd(btoc(USRSTACK-(unsigned)va));
				if (nss > vm->vm_ssize)
					vm->vm_ssize = nss;
			} else if (rv == KERN_PROTECTION_FAILURE)
				rv = KERN_INVALID_ADDRESS;
		}
		if (rv == KERN_SUCCESS) {
			if (type == T_MMUFLT) {
I 5
#ifdef LUNA2
				if (mmutype == MMU_68040)
					(void) writeback(&frame, 1);
#endif
E 5
				return;
			}
			goto out;
		}
		if (type == T_MMUFLT) {
			if (p->p_addr->u_pcb.pcb_onfault)
				goto copyfault;
			printf("vm_fault(%x, %x, %x, 0) -> %x\n",
			       map, va, ftype, rv);
			printf("  type %x, code [mmu,,ssw]: %x\n",
			       type, code);
			goto dopanic;
		}
		ucode = v;
		i = (rv == KERN_PROTECTION_FAILURE) ? SIGBUS : SIGSEGV;
		break;
	    }
	}
	trapsignal(p, i, ucode);
	if ((type & T_USER) == 0)
		return;
out:
D 2
	while (i = CURSIG(p))
		psig(i);
	p->p_pri = p->p_usrpri;
	if (want_resched) {
		/*
		 * Since we are curproc, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
		 */
		s = splclock();
		setrq(p);
		p->p_stats->p_ru.ru_nivcsw++;
		swtch();
		splx(s);
		while (i = CURSIG(p))
			psig(i);
	}
	if (p->p_stats->p_prof.pr_scale) {
		int ticks;
		struct timeval *tv = &p->p_stime;

		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks) {
#ifdef PROFTIMER
			extern int profscale;
			addupc(frame.f_pc, &p->p_stats->p_prof,
			    ticks * profscale);
#else
			addupc(frame.f_pc, &p->p_stats->p_prof, ticks);
#endif
		}
	}
	curpri = p->p_pri;
E 2
I 2
	userret(p, &frame, sticks, v, 1);
E 2
}
I 5

#ifdef LUNA2
#ifdef DEBUG
struct writebackstats {
	int calls;
	int cpushes;
	int move16s;
	int wb1s, wb2s, wb3s;
	int wbsize[4];
} wbstats;

char *f7sz[] = { "longword", "byte", "word", "line" };
char *f7tt[] = { "normal", "MOVE16", "AFC", "ACK" };
char *f7tm[] = { "d-push", "u-data", "u-code", "M-data",
		 "M-code", "k-data", "k-code", "RES" };
char wberrstr[] =
    "WARNING: pid %d(%s) writeback [%s] failed, pc=%x fa=%x wba=%x wbd=%x\n";
#endif

writeback(fp, docachepush)
	struct frame *fp;
	int docachepush;
{
	register struct fmt7 *f = &fp->f_fmt7;
	register struct proc *p = curproc;
	int err = 0;
	u_int fa;
	caddr_t oonfault = p->p_addr->u_pcb.pcb_onfault;

#ifdef DEBUG
	if ((mmudebug & MDB_WBFOLLOW) || MDB_ISPID(p->p_pid)) {
		printf(" pid=%d, fa=%x,", p->p_pid, f->f_fa);
		dumpssw(f->f_ssw);
	}
	wbstats.calls++;
#endif
	/*
	 * Deal with special cases first.
	 */
	if ((f->f_ssw & SSW4_TMMASK) == SSW4_TMDCP) {
		/*
		 * Dcache push fault.
		 * Line-align the address and write out the push data to
		 * the indicated physical address.
		 */
#ifdef DEBUG
		if ((mmudebug & MDB_WBFOLLOW) || MDB_ISPID(p->p_pid)) {
			printf(" pushing %s to PA %x, data %x",
			       f7sz[(f->f_ssw & SSW4_SZMASK) >> 5],
			       f->f_fa, f->f_pd0);
			if ((f->f_ssw & SSW4_SZMASK) == SSW4_SZLN)
				printf("/%x/%x/%x",
				       f->f_pd1, f->f_pd2, f->f_pd3);
			printf("\n");
		}
		if (f->f_wb1s & SSW4_WBSV)
			panic("writeback: cache push with WB1S valid");
		wbstats.cpushes++;
#endif
		/*
		 * XXX there are security problems if we attempt to do a
		 * cache push after a signal handler has been called.
		 */
		if (docachepush) {
			pmap_enter(kernel_pmap, (vm_offset_t)vmmap,
				   trunc_page(f->f_fa), VM_PROT_WRITE, TRUE);
			fa = (u_int)&vmmap[(f->f_fa & PGOFSET) & ~0xF];
			bcopy((caddr_t)&f->f_pd0, (caddr_t)fa, 16);
			DCFL(pmap_extract(kernel_pmap, (vm_offset_t)fa));
			pmap_remove(kernel_pmap, (vm_offset_t)vmmap,
				    (vm_offset_t)&vmmap[NBPG]);
		} else
			printf("WARNING: pid %d(%s) uid %d: CPUSH not done\n",
			       p->p_pid, p->p_comm, p->p_ucred->cr_uid);
	} else if ((f->f_ssw & (SSW4_RW|SSW4_TTMASK)) == SSW4_TTM16) {
		/*
		 * MOVE16 fault.
		 * Line-align the address and write out the push data to
		 * the indicated virtual address.
		 */
#ifdef DEBUG
		if ((mmudebug & MDB_WBFOLLOW) || MDB_ISPID(p->p_pid))
			printf(" MOVE16 to VA %x(%x), data %x/%x/%x/%x\n",
			       f->f_fa, f->f_fa & ~0xF, f->f_pd0, f->f_pd1,
			       f->f_pd2, f->f_pd3);
		if (f->f_wb1s & SSW4_WBSV)
			panic("writeback: MOVE16 with WB1S valid");
		wbstats.move16s++;
#endif
		if (KDFAULT(f->f_wb1s))
			bcopy((caddr_t)&f->f_pd0, (caddr_t)(f->f_fa & ~0xF), 16);
		else
			err = suline((caddr_t)(f->f_fa & ~0xF), (caddr_t)&f->f_pd0);
		if (err) {
			fa = f->f_fa & ~0xF;
#ifdef DEBUG
			if (mmudebug & MDB_WBFAILED)
				printf(wberrstr, p->p_pid, p->p_comm,
				       "MOVE16", fp->f_pc, f->f_fa,
				       f->f_fa & ~0xF, f->f_pd0);
#endif
		}
	} else if (f->f_wb1s & SSW4_WBSV) {
		/*
		 * Writeback #1.
		 * Position the "memory-aligned" data and write it out.
		 */
		register u_int wb1d = f->f_wb1d;
		register int off;

#ifdef DEBUG
		if ((mmudebug & MDB_WBFOLLOW) || MDB_ISPID(p->p_pid))
			dumpwb(1, f->f_wb1s, f->f_wb1a, f->f_wb1d);
		wbstats.wb1s++;
		wbstats.wbsize[(f->f_wb2s&SSW4_SZMASK)>>5]++;
#endif
		off = (f->f_wb1a & 3) * 8;
		switch (f->f_wb1s & SSW4_SZMASK) {
		case SSW4_SZLW:
			if (off)
				wb1d = (wb1d >> (32 - off)) | (wb1d << off);
			if (KDFAULT(f->f_wb1s))
				*(long *)f->f_wb1a = wb1d;
			else
				err = suword((caddr_t)f->f_wb1a, wb1d);
			break;
		case SSW4_SZB:
			off = 24 - off;
			if (off)
				wb1d >>= off;
			if (KDFAULT(f->f_wb1s))
				*(char *)f->f_wb1a = wb1d;
			else
				err = subyte((caddr_t)f->f_wb1a, wb1d);
			break;
		case SSW4_SZW:
			off = (off + 16) % 32;
			if (off)
				wb1d = (wb1d >> (32 - off)) | (wb1d << off);
			if (KDFAULT(f->f_wb1s))
				*(short *)f->f_wb1a = wb1d;
			else
				err = susword((caddr_t)f->f_wb1a, wb1d);
			break;
		}
		if (err) {
			fa = f->f_wb1a;
#ifdef DEBUG
			if (mmudebug & MDB_WBFAILED)
				printf(wberrstr, p->p_pid, p->p_comm,
				       "#1", fp->f_pc, f->f_fa,
				       f->f_wb1a, f->f_wb1d);
#endif
		}
	}
	/*
	 * Deal with the "normal" writebacks.
	 *
	 * XXX writeback2 is known to reflect a LINE size writeback after
	 * a MOVE16 was already dealt with above.  Ignore it.
	 */
	if (err == 0 && (f->f_wb2s & SSW4_WBSV) &&
	    (f->f_wb2s & SSW4_SZMASK) != SSW4_SZLN) {
#ifdef DEBUG
		if ((mmudebug & MDB_WBFOLLOW) || MDB_ISPID(p->p_pid))
			dumpwb(2, f->f_wb2s, f->f_wb2a, f->f_wb2d);
		wbstats.wb2s++;
		wbstats.wbsize[(f->f_wb2s&SSW4_SZMASK)>>5]++;
#endif
		switch (f->f_wb2s & SSW4_SZMASK) {
		case SSW4_SZLW:
			if (KDFAULT(f->f_wb2s))
				*(long *)f->f_wb2a = f->f_wb2d;
			else
				err = suword((caddr_t)f->f_wb2a, f->f_wb2d);
			break;
		case SSW4_SZB:
			if (KDFAULT(f->f_wb2s))
				*(char *)f->f_wb2a = f->f_wb2d;
			else
				err = subyte((caddr_t)f->f_wb2a, f->f_wb2d);
			break;
		case SSW4_SZW:
			if (KDFAULT(f->f_wb2s))
				*(short *)f->f_wb2a = f->f_wb2d;
			else
				err = susword((caddr_t)f->f_wb2a, f->f_wb2d);
			break;
		}
		if (err) {
			fa = f->f_wb2a;
#ifdef DEBUG
			if (mmudebug & MDB_WBFAILED) {
				printf(wberrstr, p->p_pid, p->p_comm,
				       "#2", fp->f_pc, f->f_fa,
				       f->f_wb2a, f->f_wb2d);
				dumpssw(f->f_ssw);
				dumpwb(2, f->f_wb2s, f->f_wb2a, f->f_wb2d);
			}
#endif
		}
	}
	if (err == 0 && (f->f_wb3s & SSW4_WBSV)) {
#ifdef DEBUG
		if ((mmudebug & MDB_WBFOLLOW) || MDB_ISPID(p->p_pid))
			dumpwb(3, f->f_wb3s, f->f_wb3a, f->f_wb3d);
		wbstats.wb3s++;
		wbstats.wbsize[(f->f_wb3s&SSW4_SZMASK)>>5]++;
#endif
		switch (f->f_wb3s & SSW4_SZMASK) {
		case SSW4_SZLW:
			if (KDFAULT(f->f_wb3s))
				*(long *)f->f_wb3a = f->f_wb3d;
			else
				err = suword((caddr_t)f->f_wb3a, f->f_wb3d);
			break;
		case SSW4_SZB:
			if (KDFAULT(f->f_wb3s))
				*(char *)f->f_wb3a = f->f_wb3d;
			else
				err = subyte((caddr_t)f->f_wb3a, f->f_wb3d);
			break;
		case SSW4_SZW:
			if (KDFAULT(f->f_wb3s))
				*(short *)f->f_wb3a = f->f_wb3d;
			else
				err = susword((caddr_t)f->f_wb3a, f->f_wb3d);
			break;
#ifdef DEBUG
		case SSW4_SZLN:
			panic("writeback: wb3s indicates LINE write");
#endif
		}
		if (err) {
			fa = f->f_wb3a;
#ifdef DEBUG
			if (mmudebug & MDB_WBFAILED)
				printf(wberrstr, p->p_pid, p->p_comm,
				       "#3", fp->f_pc, f->f_fa,
				       f->f_wb3a, f->f_wb3d);
#endif
		}
	}
	p->p_addr->u_pcb.pcb_onfault = oonfault;
	/*
	 * Determine the cause of the failure if any translating to
	 * a signal.  If the corresponding VA is valid and RO it is
	 * a protection fault (SIGBUS) otherwise consider it an
	 * illegal reference (SIGSEGV).
	 */
	if (err) {
		if (vm_map_check_protection(&p->p_vmspace->vm_map,	
					    trunc_page(fa), round_page(fa),
					    VM_PROT_READ) &&
		    !vm_map_check_protection(&p->p_vmspace->vm_map,
					     trunc_page(fa), round_page(fa),
					     VM_PROT_WRITE))
			err = SIGBUS;
		else
			err = SIGSEGV;
	}
	return(err);
}

#ifdef DEBUG
dumpssw(ssw)
	register u_short ssw;
{
	printf(" SSW: %x: ", ssw);
	if (ssw & SSW4_CP)
		printf("CP,");
	if (ssw & SSW4_CU)
		printf("CU,");
	if (ssw & SSW4_CT)
		printf("CT,");
	if (ssw & SSW4_CM)
		printf("CM,");
	if (ssw & SSW4_MA)
		printf("MA,");
	if (ssw & SSW4_ATC)
		printf("ATC,");
	if (ssw & SSW4_LK)
		printf("LK,");
	if (ssw & SSW4_RW)
		printf("RW,");
	printf(" SZ=%s, TT=%s, TM=%s\n",
	       f7sz[(ssw & SSW4_SZMASK) >> 5],
	       f7tt[(ssw & SSW4_TTMASK) >> 3],
	       f7tm[ssw & SSW4_TMMASK]);
}

dumpwb(num, s, a, d)
	int num;
	u_short s;
	u_int a, d;
{
	register struct proc *p = curproc;
	vm_offset_t pa;

	printf(" writeback #%d: VA %x, data %x, SZ=%s, TT=%s, TM=%s\n",
	       num, a, d, f7sz[(s & SSW4_SZMASK) >> 5],
	       f7tt[(s & SSW4_TTMASK) >> 3], f7tm[s & SSW4_TMMASK]);
	printf("               PA ");
	pa = pmap_extract(&p->p_vmspace->vm_pmap, (vm_offset_t)a);
	if (pa == 0)
		printf("<invalid address>");
	else
		printf("%x, current value %x", pa, fuword((caddr_t)a));
	printf("\n");
}
#endif
#endif
E 5

/*
 * Proces a system call.
 */
syscall(code, frame)
D 2
	volatile unsigned code;
E 2
I 2
	u_int code;
E 2
	struct frame frame;
{
	register caddr_t params;
D 2
	register int i;
E 2
	register struct sysent *callp;
D 2
	register struct proc *p = curproc;
E 2
I 2
	register struct proc *p;
E 2
	int error, opc, numsys, s;
I 2
	u_int argsize;
E 2
	struct args {
		int i[8];
	} args;
	int rval[2];
D 2
	struct timeval syst;
	struct sysent *systab;
E 2
I 2
	u_quad_t sticks;
E 2

	cnt.v_syscall++;
D 2
	syst = p->p_stime;
E 2
	if (!USERMODE(frame.f_sr))
		panic("syscall");
I 2
	p = curproc;
	sticks = p->p_sticks;
E 2
	p->p_md.md_regs = frame.f_regs;
	opc = frame.f_pc - 2;
D 2
	systab = sysent;
	numsys = nsysent;
E 2
I 2
	callp = sysent, numsys = nsysent;
E 2
	params = (caddr_t)frame.f_regs[SP] + sizeof(int);
D 2
	if (code == 0) {			/* indir */
E 2
I 2
	switch (code) {

D 7
	case SYS_indir:
E 7
I 7
	case SYS_syscall:
E 7
		/*
		 * Code is first argument, followed by actual args.
		 */
E 2
		code = fuword(params);
		params += sizeof(int);
I 4
		/*
		 * XXX sigreturn requires special stack manipulation
		 * that is only done if entered via the sigreturn
		 * trap.  Cannot allow it here so make sure we fail.
		 */
		if (code == SYS_sigreturn)
			code = numsys;
E 4
I 2
		break;

D 7
	case SYS___indir:
E 7
I 7
	case SYS___syscall:
E 7
		/*
D 7
		 * Like indir, but code is a quad, so as to maintain
E 7
I 7
		 * Like syscall, but code is a quad, so as to maintain
E 7
		 * quad alignment for the rest of the arguments.
		 */
		code = fuword(params + _QUAD_LOWWORD * sizeof(int));
		params += sizeof(quad_t);
		break;

	default:
		/* nothing to do by default */
		break;
E 2
	}
D 2
	if (code >= numsys)
		callp = &systab[0];		/* indir (illegal) */
E 2
I 2
	if (code < numsys)
		callp += code;
E 2
	else
D 2
		callp = &systab[code];
	if ((i = callp->sy_narg * sizeof (int)) &&
	    (error = copyin(params, (caddr_t)&args, (u_int)i))) {
		frame.f_regs[D0] = error;
		frame.f_sr |= PSL_C;	/* carry bit */
E 2
I 2
D 7
		callp += SYS_indir;	/* => nosys */
E 7
I 7
		callp += SYS_syscall;	/* => nosys */
E 7
	argsize = callp->sy_narg * sizeof(int);
	if (argsize && (error = copyin(params, (caddr_t)&args, argsize))) {
E 2
#ifdef KTRACE
		if (KTRPOINT(p, KTR_SYSCALL))
			ktrsyscall(p->p_tracep, code, callp->sy_narg, args.i);
#endif
D 2
		goto done;
E 2
I 2
		goto bad;
E 2
	}
#ifdef KTRACE
	if (KTRPOINT(p, KTR_SYSCALL))
		ktrsyscall(p->p_tracep, code, callp->sy_narg, args.i);
#endif
	rval[0] = 0;
	rval[1] = frame.f_regs[D1];
	error = (*callp->sy_call)(p, &args, rval);
D 2
	if (error == ERESTART)
		frame.f_pc = opc;
	else if (error != EJUSTRETURN) {
		if (error) {
			frame.f_regs[D0] = error;
			frame.f_sr |= PSL_C;	/* carry bit */
		} else {
			frame.f_regs[D0] = rval[0];
			frame.f_regs[D1] = rval[1];
			frame.f_sr &= ~PSL_C;
		}
	}
	/* else if (error == EJUSTRETURN) */
		/* nothing to do */
E 2
I 2
	switch (error) {
E 2

D 2
done:
	/*
	 * Reinitialize proc pointer `p' as it may be different
	 * if this is a child returning from fork syscall.
	 */
	p = curproc;
	while (i = CURSIG(p))
		psig(i);
	p->p_pri = p->p_usrpri;
	if (want_resched) {
E 2
I 2
	case 0:
E 2
		/*
D 2
		 * Since we are curproc, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 2
I 2
		 * Reinitialize proc pointer `p' as it may be different
		 * if this is a child returning from fork syscall.
E 2
		 */
D 2
		s = splclock();
		setrq(p);
		p->p_stats->p_ru.ru_nivcsw++;
		swtch();
		splx(s);
		while (i = CURSIG(p))
			psig(i);
	}
	if (p->p_stats->p_prof.pr_scale) {
		int ticks;
		struct timeval *tv = &p->p_stime;
E 2
I 2
		p = curproc;
		frame.f_regs[D0] = rval[0];
		frame.f_regs[D1] = rval[1];
		frame.f_sr &= ~PSL_C;
		break;
E 2

D 2
		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks) {
#ifdef PROFTIMER
			extern int profscale;
			addupc(frame.f_pc, &p->p_stats->p_prof,
			    ticks * profscale);
#else
			addupc(frame.f_pc, &p->p_stats->p_prof, ticks);
#endif
		}
E 2
I 2
	case ERESTART:
		frame.f_pc = opc;
		break;

	case EJUSTRETURN:
		break;		/* nothing to do */

	default:
	bad:
		frame.f_regs[D0] = error;
		frame.f_sr |= PSL_C;
		break;
E 2
	}
D 2
	curpri = p->p_pri;
E 2
I 2

	userret(p, &frame, sticks, (u_int)0, 0);
E 2
#ifdef KTRACE
	if (KTRPOINT(p, KTR_SYSRET))
		ktrsysret(p->p_tracep, code, error, rval[0]);
#endif
}
E 1
