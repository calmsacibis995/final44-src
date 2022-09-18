h04099
s 00004/00004/00984
d D 8.7 95/02/19 07:44:48 cgd 39 38
c rather than passing sy_narg around, pass sy_argsize
e
s 00020/00005/00968
d D 8.6 94/06/01 16:50:27 hibler 38 37
c avoid crashing on RTE with odd-address PC, it appears that the
c address fault is generated in supervisor mode and not user mode
e
s 00004/00005/00969
d D 8.5 94/01/04 22:27:02 bostic 37 36
c lint
e
s 00009/00009/00965
d D 8.4 93/09/23 16:37:21 bostic 36 35
c changes for 4.4BSD-Lite requested by USL
e
s 00004/00004/00970
d D 8.3 93/09/21 07:39:18 bostic 35 34
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00001/00973
d D 8.2 93/09/03 16:10:59 mckusick 34 33
c curpri => curpriority
e
s 00002/00002/00972
d D 8.1 93/06/16 16:40:20 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00970
d D 7.27 93/06/16 16:35:37 mckusick 32 30
c indir => syscall; __indir => __syscall
e
s 00002/00002/00972
d R 8.1 93/06/10 21:41:41 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00031/00944
d D 7.26 92/12/27 09:54:20 hibler 30 29
c cleanup, SHPUX has moved
e
s 00019/00019/00956
d D 7.25 92/10/11 09:42:49 bostic 29 28
c make kernel includes standard
e
s 00006/00002/00969
d D 7.24 92/09/21 21:34:08 hibler 28 27
c addupc_intr -> addupc_task and convert stat ticks to prof ticks
e
s 00005/00005/00966
d D 7.23 92/07/09 17:07:29 mckusick 27 26
c syntax cleanups for __indir
e
s 00155/00187/00816
d D 7.22 92/07/08 01:15:45 torek 26 25
c merge common syscall and trap return code; new rusage and profiling;
c reorganize syscall handling
e
s 00007/00000/00996
d D 7.21 92/06/30 13:51:30 torek 25 23
c avoid servicing page faults on the interrupt stack
e
s 00006/00000/00996
d R 7.21 92/06/30 13:30:14 torek 24 23
c avoid servicing page faults on the interrupt stack
e
s 00443/00009/00553
d D 7.20 92/06/05 15:36:54 hibler 23 22
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00561
d D 7.19 92/03/20 12:51:55 hibler 22 21
c make code argument to syscall unsigned
c negative syscall nums did nasty things to the kernel
e
s 00002/00002/00560
d D 7.18 92/02/05 17:20:07 mckusick 21 20
c p_regs moves to p_md.md_regs
e
s 00000/00001/00562
d D 7.17 91/11/20 17:47:06 mckusick 20 19
c delete unneeded seg.h
e
s 00000/00001/00563
d D 7.16 91/08/28 15:49:48 mckusick 19 18
c no longer need to include vmmeter.h
e
s 00000/00000/00564
d D 7.15 91/08/02 12:02:18 karels 18 14
i 17
c apply fixes in 7.14.1.3 to main branch
e
s 00007/00004/00565
d D 7.14.1.3 91/08/02 12:01:09 karels 17 16
c fix precedence bug introduced in 7.14, don't leave at splclock
e
s 00002/00000/00567
d D 7.14.1.2 91/05/28 17:34:17 mckusick 16 15
c add check for lock count
e
s 00006/00000/00561
d D 7.14.1.1 91/05/19 14:40:00 mckusick 15 14
c name resolution checking (need kern/kern_malloc.c 7.25.1.1,
c kern/vfs_lookup.c 7.31.1.1, kern/vfs_syscalls.c 7.70.1.1,
c nfs/nfs_serv.c 7.40.1.1, nfs/nfs_syscalls.c 7.26.1.1,
c ufs/ufs_vnops.c 7.64.1.1, and hp300/hp300/trap.c 7.14.1.1)
e
s 00026/00027/00535
d D 7.14 91/05/09 18:26:24 karels 14 13
c mv USER to trap.h T_USER, other cleanups
e
s 00002/00002/00560
d D 7.13 91/05/07 14:32:20 karels 13 12
c errno doesn't need to be masked to u_char
e
s 00039/00033/00523
d D 7.12 91/05/07 09:59:05 hibler 12 11
c new stack adjustment code
c new handling of stack limit violations
e
s 00006/00006/00550
d D 7.11 91/05/04 19:30:43 karels 11 10
c u. is gone, use p_addr; ast's no longer per-process, but global
e
s 00071/00074/00485
d D 7.10 91/04/20 17:20:13 karels 10 9
c new proc struct; mv u_ar0; u.u_procp => curproc; fix includes;
c runrun => want_resched; add proc arg to psig, trapsignal
e
s 00019/00019/00540
d D 7.9 90/12/16 16:36:42 bostic 9 8
c kernel reorg
e
s 00059/00163/00500
d D 7.8 90/12/05 18:53:40 mckusick 8 7
c update from Mike Hibler for new VM and other machine support
e
s 00009/00006/00654
d D 7.7 90/06/25 14:29:23 karels 7 6
c use struct pointer for args (void * may be different on some machines)
e
s 00014/00018/00646
d D 7.6 90/06/24 15:03:24 karels 6 5
c new syscall convention
e
s 00006/00015/00658
d D 7.5 90/06/22 09:32:25 hibler 5 4
c T_AST -> T_ASTFLT to be more consisent with VAX
e
s 00001/00001/00672
d D 7.4 90/05/29 13:12:15 mckusick 4 3
c new calling convension for system calls
e
s 00018/00032/00655
d D 7.3 90/05/25 16:04:02 mckusick 3 2
c update from Mike Hibler at Utah
e
s 00056/00071/00631
d D 7.2 90/05/25 15:56:48 karels 2 1
c first try at updating for new signal mechanism
e
s 00702/00000/00000
d D 7.1 90/05/08 18:09:14 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
f b 
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 33
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 33
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 12
 * from: Utah $Hdr: trap.c 1.28 89/09/25$
E 12
I 12
D 23
 * from: Utah $Hdr: trap.c 1.32 91/04/06$
E 23
I 23
D 30
 * from: Utah $Hdr: trap.c 1.35 91/12/26$
E 30
I 30
 * from: Utah $Hdr: trap.c 1.37 92/12/20$
E 30
E 23
E 12
 *
 *	%W% (Berkeley) %G%
 */

I 10
D 29
#include "param.h"
#include "systm.h"
#include "proc.h"
D 20
#include "seg.h"
E 20
#include "acct.h"
#include "kernel.h"
#include "signalvar.h"
#include "resourcevar.h"
I 26
#include "syscall.h"
E 26
#include "syslog.h"
#include "user.h"
E 29
I 29
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
E 29
#ifdef KTRACE
D 29
#include "ktrace.h"
E 29
I 29
#include <sys/ktrace.h>
E 29
#endif

I 11
D 29
#include "../include/psl.h"
E 11
#include "../include/trap.h"
E 10
D 9
#include "cpu.h"
#include "psl.h"
#include "reg.h"
D 8
#include "pte.h"
E 8
#include "mtpr.h"
E 9
I 9
#include "../include/cpu.h"
D 11
#include "../include/psl.h"
E 11
#include "../include/reg.h"
#include "../include/mtpr.h"
E 29
I 29
#include <machine/psl.h>
#include <machine/trap.h>
#include <machine/cpu.h>
#include <machine/reg.h>
#include <machine/mtpr.h>
E 29
E 9

D 9
#include "param.h"
#include "systm.h"
#include "user.h"
#include "proc.h"
#include "seg.h"
#include "trap.h"
#include "acct.h"
#include "kernel.h"
D 8
#include "vm.h"
#include "cmap.h"
E 8
#include "syslog.h"
E 9
I 9
D 10
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/seg.h"
#include "../include/trap.h"
#include "sys/acct.h"
#include "sys/kernel.h"
#include "sys/syslog.h"
E 9
#ifdef KTRACE
D 9
#include "ktrace.h"
E 9
I 9
#include "sys/ktrace.h"
E 9
#endif

I 8
D 9
#include "../vm/vm_param.h"
#include "../vm/pmap.h"
#include "../vm/vm_map.h"
#include "vmmeter.h"
E 9
I 9
#include "vm/vm_param.h"
E 10
I 10
D 29
#include "vm/vm.h"
E 10
#include "vm/pmap.h"
E 29
I 29
#include <vm/vm.h>
#include <vm/pmap.h>
E 29
D 10
#include "vm/vm_map.h"
#include "sys/vmmeter.h"
E 10
I 10
D 19
#include "vmmeter.h"
E 19
E 10
E 9

E 8
#ifdef HPUXCOMPAT
D 23
#include "../hpux/hpux.h"
E 23
I 23
D 29
#include "hp/hpux/hpux.h"
E 29
I 29
#include <hp/hpux/hpux.h>
E 29
E 23
#endif

D 14
#define	USER	040		/* user-mode flag added to type */

E 14
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

I 12
/*
 * Size of various exception stack frames (minus the standard 8 bytes)
 */
short	exframesize[] = {
	FMT0SIZE,	/* type 0 - normal (68020/030/040) */
	FMT1SIZE,	/* type 1 - throwaway (68020/030/040) */
	FMT2SIZE,	/* type 2 - normal 6-word (68020/030/040) */
D 23
	-1,		/* type 3 - FP post-instruction (68040) */
E 23
I 23
	FMT3SIZE,	/* type 3 - FP post-instruction (68040) */
E 23
	-1, -1, -1,	/* type 4-6 - undefined */
D 23
	-1,		/* type 7 - access error (68040) */
E 23
I 23
	FMT7SIZE,	/* type 7 - access error (68040) */
E 23
	58,		/* type 8 - bus fault (68010) */
	FMT9SIZE,	/* type 9 - coprocessor mid-instruction (68020/030) */
	FMTASIZE,	/* type A - short bus fault (68020/030) */
	FMTBSIZE,	/* type B - long bus fault (68020/030) */
	-1, -1, -1, -1	/* type C-F - undefined */
};

I 23
D 26
#if defined(HP380)
E 26
I 26
#ifdef HP380
E 26
#define KDFAULT(c)	(mmutype == MMU_68040 ? \
			    ((c) & SSW4_TMMASK) == SSW4_TMKD : \
			    ((c) & (SSW_DF|FC_SUPERD)) == (SSW_DF|FC_SUPERD))
#define WRFAULT(c) 	(mmutype == MMU_68040 ? \
			    ((c) & SSW4_RW) == 0 : \
			    ((c) & (SSW_DF|SSW_RW)) == SSW_DF)
#else
#define KDFAULT(c)	(((c) & (SSW_DF|SSW_FCMASK)) == (SSW_DF|FC_SUPERD))
#define WRFAULT(c)	(((c) & (SSW_DF|SSW_RW)) == SSW_DF)
#endif

E 23
E 12
#ifdef DEBUG
int mmudebug = 0;
I 23
int mmupid = -1;
#define MDB_FOLLOW	1
#define MDB_WBFOLLOW	2
#define MDB_WBFAILED	4
#define MDB_ISPID(p)	(p) == mmupid
E 23
#endif

/*
I 26
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
#ifdef HP380
	int beenhere = 0;

again:
#endif
	/* take pending signals */
	while ((sig = CURSIG(p)) != 0)
D 36
		psig(sig);
	p->p_pri = p->p_usrpri;
E 36
I 36
		postsig(sig);
	p->p_priority = p->p_usrpri;
E 36
	if (want_resched) {
		/*
		 * Since we are curproc, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 35
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 35
I 35
		 * If that happened after we put ourselves on the run queue
D 36
		 * but before we swtch()'ed, we might not be on the queue
E 36
I 36
		 * but before we mi_switch()'ed, we might not be on the queue
E 36
		 * indicated by our priority.
E 35
		 */
		s = splstatclock();
D 35
		setrq(p);
E 35
I 35
		setrunqueue(p);
E 35
		p->p_stats->p_ru.ru_nivcsw++;
D 36
		swtch();
E 36
I 36
		mi_switch();
E 36
		splx(s);
		while ((sig = CURSIG(p)) != 0)
D 36
			psig(sig);
E 36
I 36
			postsig(sig);
E 36
	}

	/*
	 * If profiling, charge system time to the trapped pc.
	 */
D 28
	if (p->p_flag & SPROFIL)
		addupc_intr(p, fp->f_pc, (int)(p->p_sticks - oticks));
E 28
I 28
D 36
	if (p->p_flag & SPROFIL) {
E 36
I 36
	if (p->p_flag & P_PROFIL) {
E 36
		extern int psratio;

		addupc_task(p, fp->f_pc,
			    (int)(p->p_sticks - oticks) * psratio);
	}
E 28
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
	}
#endif
D 34
	curpri = p->p_pri;
E 34
I 34
D 36
	curpriority = p->p_pri;
E 36
I 36
	curpriority = p->p_priority;
E 36
E 34
}

/*
E 26
D 14
 * Called from the trap handler when a processor trap occurs.
E 14
I 14
 * Trap is called from locore to handle most types of processor traps,
 * including events such as simulated software interrupts/AST's.
 * System calls are broken out for efficiency.
E 14
 */
/*ARGSUSED*/
trap(type, code, v, frame)
	int type;
	unsigned code;
	register unsigned v;
	struct frame frame;
{
D 37
	register int i;
D 26
	unsigned ucode = 0;
D 10
	register struct proc *p = u.u_procp;
E 10
I 10
	register struct proc *p = curproc;
E 10
	struct timeval syst;
E 26
I 26
	unsigned ucode;
E 37
I 37
	extern char fswintr[];
E 37
	register struct proc *p;
I 37
	register int i;
	u_int ucode;
E 37
	u_quad_t sticks;
E 26
D 37
	unsigned ncode;
I 17
D 26
	int s;
I 23
#if defined(HP380)
	int beenhere = 0;
#endif
E 26
I 25
	extern char fswintr[];
E 37
E 25
E 23
E 17

	cnt.v_trap++;
D 10
	syst = u.u_ru.ru_stime;
E 10
I 10
D 26
	syst = p->p_stime;
E 26
I 26
	p = curproc;
	ucode = 0;
E 26
E 10
	if (USERMODE(frame.f_sr)) {
D 14
		type |= USER;
E 14
I 14
		type |= T_USER;
I 26
		sticks = p->p_sticks;
E 26
E 14
D 10
		u.u_ar0 = frame.f_regs;
E 10
I 10
D 21
		p->p_regs = frame.f_regs;
E 21
I 21
		p->p_md.md_regs = frame.f_regs;
E 21
E 10
	}
	switch (type) {

	default:
dopanic:
D 10
#ifdef KGDB
		if (!panicstr && kgdb_trap(type, code, v, &frame))
			return;
#endif
E 10
		printf("trap type %d, code = %x, v = %x\n", type, code, v);
D 30
		regdump(frame.f_regs, 128);
E 30
I 30
		regdump(&frame, 128);
E 30
D 14
		type &= ~USER;
E 14
I 14
		type &= ~T_USER;
E 14
		if ((unsigned)type < TRAP_TYPES)
			panic(trap_type[type]);
		panic("trap");

	case T_BUSERR:		/* kernel bus error */
D 11
		if (!u.u_pcb.pcb_onfault)
E 11
I 11
		if (!p->p_addr->u_pcb.pcb_onfault)
E 11
			goto dopanic;
		/*
		 * If we have arranged to catch this fault in any of the
		 * copy to/from user space routines, set PC to return to
		 * indicated location and set flag informing buserror code
		 * that it may need to clean up stack frame.
		 */
copyfault:
I 12
		frame.f_stackadj = exframesize[frame.f_format];
		frame.f_format = frame.f_vector = 0;
E 12
D 11
		frame.f_pc = (int) u.u_pcb.pcb_onfault;
E 11
I 11
		frame.f_pc = (int) p->p_addr->u_pcb.pcb_onfault;
E 11
D 12
		frame.f_stackadj = -1;
E 12
		return;

D 14
	case T_BUSERR+USER:	/* bus error */
	case T_ADDRERR+USER:	/* address error */
E 14
I 14
	case T_BUSERR|T_USER:	/* bus error */
	case T_ADDRERR|T_USER:	/* address error */
I 23
		ucode = v;
E 23
E 14
		i = SIGBUS;
		break;

I 38
#ifdef HP380
	case T_ADDRERR:
		/*
		 * Yow!  Looks like we get a kernel exception if the PC
		 * in the RTE frame is odd on a 68040 (not on a 68030).
		 * It comes through as a user exception for access faults
		 * (T_MMUFLT).
		 */
		if (*(short *)frame.f_pc != 0x4e73)
			goto dopanic;
		/* fall through */
#endif

E 38
#ifdef FPCOPROC
	case T_COPERR:		/* kernel coprocessor violation */
#endif
D 23
	case T_FMTERR:		/* kernel format error */
E 23
I 23
	case T_FMTERR|T_USER:	/* do all RTE errors come in as T_USER? */
	case T_FMTERR:		/* ...just in case... */
E 23
D 38
	/*
	 * The user has most likely trashed the RTE or FP state info
	 * in the stack frame of a signal handler.
	 */
E 38
I 38
		/*
		 * The user has most likely trashed the RTE or FP state info
		 * in the stack frame of a signal handler.
		 */
E 38
I 2
D 14
		type |= USER;
E 14
I 14
		type |= T_USER;
E 14
E 2
D 10
		printf("pid %d: kernel %s exception\n", u.u_procp->p_pid,
E 10
I 10
		printf("pid %d: kernel %s exception\n", p->p_pid,
E 10
D 38
		       type==T_COPERR ? "coprocessor" : "format");
E 38
I 38
		       (type==T_COPERR|T_USER) ? "coprocessor" :
		       (type==T_ADDRERR|T_USER) ? "RTE address" :
		       "RTE format");
E 38
D 10
		u.u_signal[SIGILL] = SIG_DFL;
E 10
I 10
		p->p_sigacts->ps_sigact[SIGILL] = SIG_DFL;
E 10
		i = sigmask(SIGILL);
		p->p_sigignore &= ~i;
		p->p_sigcatch &= ~i;
		p->p_sigmask &= ~i;
I 2
		i = SIGILL;
E 2
		ucode = frame.f_format;	/* XXX was ILL_RESAD_FAULT */
D 2
		psignal(u.u_procp, SIGILL);
		goto out;
E 2
I 2
		break;
E 2

#ifdef FPCOPROC
D 14
	case T_COPERR+USER:	/* user coprocessor violation */
E 14
I 14
	case T_COPERR|T_USER:	/* user coprocessor violation */
E 14
	/* What is a proper response here? */
		ucode = 0;
		i = SIGFPE;
		break;

D 12
	case T_FPERR+USER:		/* 68881 exceptions */
E 12
I 12
D 14
	case T_FPERR+USER:	/* 68881 exceptions */
E 14
I 14
	case T_FPERR|T_USER:	/* 68881 exceptions */
E 14
E 12
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

I 23
D 26
#if defined(HP380)
E 26
I 26
#ifdef HP380
E 26
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

E 23
D 14
	case T_ILLINST+USER:	/* illegal instruction fault */
E 14
I 14
	case T_ILLINST|T_USER:	/* illegal instruction fault */
E 14
#ifdef HPUXCOMPAT
D 10
		if (u.u_procp->p_flag & SHPUX) {
E 10
I 10
D 30
		if (p->p_flag & SHPUX) {
E 30
I 30
		if (p->p_md.md_flags & MDP_HPUX) {
E 30
E 10
			ucode = HPUX_ILL_ILLINST_TRAP;
			i = SIGILL;
			break;
		}
		/* fall through */
#endif
D 14
	case T_PRIVINST+USER:	/* privileged instruction fault */
E 14
I 14
	case T_PRIVINST|T_USER:	/* privileged instruction fault */
E 14
#ifdef HPUXCOMPAT
D 10
		if (u.u_procp->p_flag & SHPUX)
E 10
I 10
D 30
		if (p->p_flag & SHPUX)
E 30
I 30
		if (p->p_md.md_flags & MDP_HPUX)
E 30
E 10
			ucode = HPUX_ILL_PRIV_TRAP;
		else
#endif
		ucode = frame.f_format;	/* XXX was ILL_PRIVIN_FAULT */
		i = SIGILL;
		break;

D 14
	case T_ZERODIV+USER:	/* Divide by zero */
E 14
I 14
	case T_ZERODIV|T_USER:	/* Divide by zero */
E 14
#ifdef HPUXCOMPAT
D 10
		if (u.u_procp->p_flag & SHPUX)
E 10
I 10
D 30
		if (p->p_flag & SHPUX)
E 30
I 30
		if (p->p_md.md_flags & MDP_HPUX)
E 30
E 10
			ucode = HPUX_FPE_INTDIV_TRAP;
		else
#endif
		ucode = frame.f_format;	/* XXX was FPE_INTDIV_TRAP */
		i = SIGFPE;
		break;

D 14
	case T_CHKINST+USER:	/* CHK instruction trap */
E 14
I 14
	case T_CHKINST|T_USER:	/* CHK instruction trap */
E 14
#ifdef HPUXCOMPAT
D 10
		if (u.u_procp->p_flag & SHPUX) {
E 10
I 10
D 30
		if (p->p_flag & SHPUX) {
E 30
I 30
		if (p->p_md.md_flags & MDP_HPUX) {
E 30
E 10
			/* handled differently under hp-ux */
			i = SIGILL;
			ucode = HPUX_ILL_CHK_TRAP;
			break;
		}
#endif
		ucode = frame.f_format;	/* XXX was FPE_SUBRNG_TRAP */
		i = SIGFPE;
		break;

D 14
	case T_TRAPVINST+USER:	/* TRAPV instruction trap */
E 14
I 14
	case T_TRAPVINST|T_USER:	/* TRAPV instruction trap */
E 14
#ifdef HPUXCOMPAT
D 10
		if (u.u_procp->p_flag & SHPUX) {
E 10
I 10
D 30
		if (p->p_flag & SHPUX) {
E 30
I 30
		if (p->p_md.md_flags & MDP_HPUX) {
E 30
E 10
			/* handled differently under hp-ux */
			i = SIGILL;
			ucode = HPUX_ILL_TRAPV_TRAP;
			break;
		}
#endif
		ucode = frame.f_format;	/* XXX was FPE_INTOVF_TRAP */
		i = SIGFPE;
		break;

	/*
	 * XXX: Trace traps are a nightmare.
	 *
	 *	HP-UX uses trap #1 for breakpoints,
	 *	HPBSD uses trap #2,
	 *	SUN 3.x uses trap #15,
D 10
	 *	KGDB uses trap #15 (for kernel breakpoints).
E 10
I 10
	 *	KGDB uses trap #15 (for kernel breakpoints; handled elsewhere).
E 10
	 *
	 * HPBSD and HP-UX traps both get mapped by locore.s into T_TRACE.
	 * SUN 3.x traps get passed through as T_TRAP15 and are not really
D 10
	 * supported yet.  KGDB traps are also passed through as T_TRAP15
	 * and are not used yet.
E 10
I 10
	 * supported yet.
E 10
	 */
	case T_TRACE:		/* kernel trace trap */
D 10
	case T_TRAP15:		/* SUN (or KGDB) kernel trace trap */
#ifdef KGDB
		if (kgdb_trap(type, code, v, &frame))
			return;
#endif
E 10
I 10
	case T_TRAP15:		/* SUN trace trap */
E 10
		frame.f_sr &= ~PSL_T;
		i = SIGTRAP;
		break;

D 14
	case T_TRACE+USER:	/* user trace trap */
	case T_TRAP15+USER:	/* SUN user trace trap */
E 14
I 14
	case T_TRACE|T_USER:	/* user trace trap */
	case T_TRAP15|T_USER:	/* SUN user trace trap */
E 14
D 5
#ifdef SUNCOMPAT
		/*
		 * Trap #2 is used to signal a cache flush.
		 * Should we also flush data cache?
		 */
		if (type == T_TRACE+USER && (p->p_flag & SSUN)) {
			ICIA();
			goto out;
		}
#endif
E 5
		frame.f_sr &= ~PSL_T;
		i = SIGTRAP;
		break;

D 5
	case T_AST:		/* system async trap, cannot happen */
E 5
I 5
	case T_ASTFLT:		/* system async trap, cannot happen */
E 5
		goto dopanic;

D 5
	case T_AST+USER:	/* user async trap */
E 5
I 5
D 14
	case T_ASTFLT+USER:	/* user async trap */
E 14
I 14
	case T_ASTFLT|T_USER:	/* user async trap */
E 14
E 5
D 11
		astoff();
E 11
I 11
		astpending = 0;
E 11
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
D 14
	case T_SSIR+USER:
E 14
I 14
	case T_SSIR|T_USER:
E 14
		if (ssir & SIR_NET) {
			siroff(SIR_NET);
			cnt.v_soft++;
			netintr();
		}
		if (ssir & SIR_CLOCK) {
			siroff(SIR_CLOCK);
			cnt.v_soft++;
D 26
			softclock((caddr_t)frame.f_pc, (int)frame.f_sr);
E 26
I 26
			softclock();
E 26
		}
		/*
		 * If this was not an AST trap, we are all done.
		 */
D 5
		if (type != T_AST+USER) {
E 5
I 5
D 14
		if (type != T_ASTFLT+USER) {
E 14
I 14
D 17
		if (type != T_ASTFLT|T_USER) {
E 17
I 17
		if (type != (T_ASTFLT|T_USER)) {
E 17
E 14
E 5
			cnt.v_trap--;
			return;
		}
		spl0();
D 26
#ifndef PROFTIMER
D 10
		if ((u.u_procp->p_flag&SOWEUPC) && u.u_prof.pr_scale) {
			addupc(frame.f_pc, &u.u_prof, 1);
			u.u_procp->p_flag &= ~SOWEUPC;
E 10
I 10
		if ((p->p_flag&SOWEUPC) && p->p_stats->p_prof.pr_scale) {
			addupc(frame.f_pc, &p->p_stats->p_prof, 1);
E 26
I 26
D 36
		if (p->p_flag & SOWEUPC) {
E 26
			p->p_flag &= ~SOWEUPC;
E 36
I 36
		if (p->p_flag & P_OWEUPC) {
			p->p_flag &= ~P_OWEUPC;
E 36
I 26
			ADDUPROF(p);
E 26
E 10
		}
D 26
#endif
E 26
		goto out;

	case T_MMUFLT:		/* kernel mode page fault */
I 25
		/*
		 * If we were doing profiling ticks or other user mode
		 * stuff from interrupt code, Just Say No.
		 */
		if (p->p_addr->u_pcb.pcb_onfault == fswintr)
			goto copyfault;
E 25
D 8
		/*
		 * Could be caused by a page fault in one of the copy to/from
		 * user space routines.  If so, we will have a catch address.
		 */
		if (!u.u_pcb.pcb_onfault)
			goto dopanic;
E 8
		/* fall into ... */

D 14
	case T_MMUFLT+USER:	/* page fault */
E 14
I 14
	case T_MMUFLT|T_USER:	/* page fault */
E 14
D 8
/*
		printf("trap: T_MMUFLT pid %d, code %x, v %x, pc %x, ps %x\n",
		       p->p_pid, code, v, frame.f_pc, frame.f_sr);
*/
		if (v >= USRSTACK) {
			if (type == T_MMUFLT)
				goto copyfault;
			i = SIGSEGV;
			break;
		}
		ncode = code >> 16;
#if defined(HP330) || defined(HP360) || defined(HP370)
E 8
I 8
	    {
		register vm_offset_t va;
I 10
		register struct vmspace *vm = p->p_vmspace;
E 10
		register vm_map_t map;
		int rv;
		vm_prot_t ftype;
		extern vm_map_t kernel_map;
D 12
		unsigned nss;
E 12

I 23
#ifdef DEBUG
		if ((mmudebug & MDB_WBFOLLOW) || MDB_ISPID(p->p_pid))
		printf("trap: T_MMUFLT pid=%d, code=%x, v=%x, pc=%x, sr=%x\n",
		       p->p_pid, code, v, frame.f_pc, frame.f_sr);
#endif
E 23
E 8
		/*
D 8
		 * Crudely map PMMU faults into HP MMU faults.
E 8
I 8
		 * It is only a kernel address space fault iff:
D 14
		 * 	1. (type & USER) == 0  and
E 14
I 14
		 * 	1. (type & T_USER) == 0  and
E 14
		 * 	2. pcb_onfault not set or
		 *	3. pcb_onfault set but supervisor space data fault
		 * The last can occur during an exec() copyin where the
		 * argument space is lazy-allocated.
E 8
		 */
D 8
		if (mmutype != MMU_HP) {
			int ocode = ncode;
			ncode = 0;
			if (ocode & PMMU_WP)
				ncode |= MMU_WPF;
			else if (ocode & PMMU_INV) {
				if ((ocode & PMMU_LVLMASK) == 2)
					ncode |= MMU_PF;
				else 
					ncode |= MMU_PTF;
			}
			/*
			 * RMW cycle, must load ATC by hand
			 */
			else if ((code & (SSW_DF|SSW_RM)) == (SSW_DF|SSW_RM)) {
E 8
I 8
		if (type == T_MMUFLT &&
D 11
		    (!u.u_pcb.pcb_onfault ||
E 11
I 11
D 23
		    (!p->p_addr->u_pcb.pcb_onfault ||
E 11
		     (code & (SSW_DF|FC_SUPERD)) == (SSW_DF|FC_SUPERD)))
E 23
I 23
		    (!p->p_addr->u_pcb.pcb_onfault || KDFAULT(code)))
E 23
			map = kernel_map;
		else
D 10
			map = u.u_procp->p_map;
E 10
I 10
			map = &vm->vm_map;
E 10
D 23
		if ((code & (SSW_DF|SSW_RW)) == SSW_DF)	/* what about RMW? */
E 23
I 23
		if (WRFAULT(code))
E 23
			ftype = VM_PROT_READ | VM_PROT_WRITE;
		else
			ftype = VM_PROT_READ;
		va = trunc_page((vm_offset_t)v);
E 8
#ifdef DEBUG
D 8
				log(LOG_WARNING,
				    "RMW fault at %x: MMUSR %x SSW %x\n",
				    v, ocode, code & 0xFFFF);
#endif
				ploadw((caddr_t)v);
				return;
			}
			/*
			 * Fault with no fault bits, should indicate bad
			 * hardware but we see this on 340s using starbase
			 * sometimes (faults accessing catseye registers)
			 */
			else {
				log(LOG_WARNING,
				    "Bad PMMU fault at %x: MMUSR %x SSW %x\n",
				    v, ocode, code & 0xFFFF);
				return;
			}
#ifdef DEBUG
			if (mmudebug && mmudebug == p->p_pid)
				printf("MMU %d: v%x, os%x, ns%x\n",
				       p->p_pid, v, ocode, ncode);
#endif
		}
#endif
#ifdef DEBUG
		if ((ncode & (MMU_PTF|MMU_PF|MMU_WPF|MMU_FPE)) == 0) {
			printf("T_MMUFLT with no fault bits\n");
E 8
I 8
		if (map == kernel_map && va == 0) {
			printf("trap: bad kernel access at %x\n", v);
E 8
			goto dopanic;
		}
#endif
I 30
#ifdef HPUXCOMPAT
		if (ISHPMMADDR(va)) {
			vm_offset_t bva;

			rv = pmap_mapmulti(map->pmap, va);
			if (rv != KERN_SUCCESS) {
				bva = HPMMBASEADDR(va);
				rv = vm_fault(map, bva, ftype, FALSE);
				if (rv == KERN_SUCCESS)
					(void) pmap_mapmulti(map->pmap, va);
			}
		} else
#endif
E 30
I 12
		rv = vm_fault(map, va, ftype, FALSE);
I 23
#ifdef DEBUG
		if (rv && MDB_ISPID(p->p_pid))
			printf("vm_fault(%x, %x, %x, 0) -> %x\n",
			       map, va, ftype, rv);
#endif
E 23
E 12
D 8
		if (ncode & MMU_PTF) {
#ifdef DEBUG
			/*
			 * NOTE: we use a u_int instead of an ste since the
			 * current compiler generates bogus code for some
			 * bitfield operations (i.e. attempts to access last
			 * word of a page as a longword causing fault).
			 */
			extern struct ste *vtoste();
			u_int *ste = (u_int *)vtoste(p, v);

			if (*ste & SG_V) {
				if (ncode & MMU_WPF) {
					printf("PTF|WPF...\n");
					if (type == T_MMUFLT)
						goto copyfault;
					i = SIGBUS;
					break;
				}
				printf("MMU_PTF with sg_v, ste@%x = %x\n",
				       ste, *ste);
				goto dopanic;
			}
#endif
#ifdef HPUXCOMPAT
			if (ISHPMMADDR(v)) {
				extern struct ste *vtoste();
				u_int *bste, *nste;

				bste = (u_int *)vtoste(p, HPMMBASEADDR(v));
				nste = (u_int *)vtoste(p, v);
				if ((*bste & SG_V) && *nste == SG_NV) {
					*nste = *bste;
					TBIAU();
					return;
				}
			}
#endif
		growit:
			if (type == T_MMUFLT)
				goto copyfault;
			if (grow((unsigned)frame.f_regs[SP]) || grow(v))
				goto out;
			i = SIGSEGV;
			break;
		}
#ifdef HPUXCOMPAT
		if (ISHPMMADDR(v)) {
			TBIS(v);
			v = HPMMBASEADDR(v);
		}
#endif
E 8
		/*
D 8
		 * NOTE: WPF without PG_V is possible
		 * (e.g. attempt to write shared text which is paged out)
E 8
I 8
D 12
		 * XXX: rude hack to make stack limits "work"
E 12
I 12
		 * If this was a stack access we keep track of the maximum
		 * accessed stack size.  Also, if vm_fault gets a protection
		 * failure it is due to accessing the stack region outside
		 * the current limit and we need to reflect that as an access
		 * error.
E 12
E 8
		 */
D 8
		if (ncode & MMU_WPF) {
#ifdef DEBUG
			extern struct ste *vtoste();
			u_int *ste = (u_int *)vtoste(p, v);

			if (!(*ste & SG_V)) {
				printf("MMU_WPF without sg_v, ste@%x = %x\n",
				       ste, *ste);
				goto dopanic;
E 8
I 8
D 12
		nss = 0;
E 12
D 10
		if ((caddr_t)va >= u.u_maxsaddr && map != kernel_map) {
E 10
I 10
		if ((caddr_t)va >= vm->vm_maxsaddr && map != kernel_map) {
E 10
D 12
			nss = clrnd(btoc(USRSTACK-(unsigned)va));
D 10
			if (nss > btoc(u.u_rlimit[RLIMIT_STACK].rlim_cur)) {
E 10
I 10
			if (nss > btoc(p->p_rlimit[RLIMIT_STACK].rlim_cur)) {
E 10
				rv = KERN_FAILURE;
				goto nogo;
E 8
			}
E 12
I 12
			if (rv == KERN_SUCCESS) {
				unsigned nss;

				nss = clrnd(btoc(USRSTACK-(unsigned)va));
				if (nss > vm->vm_ssize)
					vm->vm_ssize = nss;
			} else if (rv == KERN_PROTECTION_FAILURE)
				rv = KERN_INVALID_ADDRESS;
E 12
D 8
#endif
			if (type == T_MMUFLT)
				goto copyfault;
			i = SIGBUS;
			break;
E 8
		}
D 8
		if (ncode & MMU_PF) {
			register u_int vp;
#ifdef DEBUG
			extern struct ste *vtoste();
			u_int *ste = (u_int *)vtoste(p, v);
			struct pte *pte;

			if (!(*ste & SG_V)) {
				printf("MMU_PF without sg_v, ste@%x = %x\n",
				       ste, *ste);
				goto dopanic;
			}
#endif
			vp = btop(v);
			if (vp >= dptov(p, p->p_dsize) &&
			    vp < sptov(p, p->p_ssize-1))
				goto growit;
#ifdef DEBUG
			pte = vtopte(p, vp);
			if (*(u_int *)pte & PG_V) {
				printf("MMU_PF with pg_v, pte = %x\n",
				       *(u_int *)pte);
				goto dopanic;
			}
#endif
D 6
			i = u.u_error;
E 6
			pagein(v, 0);
E 8
I 8
D 12
		rv = vm_fault(map, va, ftype, FALSE);
E 12
		if (rv == KERN_SUCCESS) {
D 12
			/*
			 * XXX: continuation of rude stack hack
			 */
D 10
			if (nss > u.u_ssize)
				u.u_ssize = nss;
E 10
I 10
			if (nss > vm->vm_ssize)
				vm->vm_ssize = nss;
E 12
E 10
E 8
D 6
			u.u_error = i;
E 6
D 23
			if (type == T_MMUFLT)
E 23
I 23
			if (type == T_MMUFLT) {
D 26
#if defined(HP380)
E 26
I 26
#ifdef HP380
E 26
				if (mmutype == MMU_68040)
					(void) writeback(&frame, 1);
#endif
E 23
				return;
I 23
			}
E 23
			goto out;
		}
D 8
#ifdef DEBUG
		printf("T_MMUFLT: unrecognized scenerio\n");
		goto dopanic;
#endif
E 8
I 8
D 12
nogo:
E 12
		if (type == T_MMUFLT) {
D 11
			if (u.u_pcb.pcb_onfault)
E 11
I 11
			if (p->p_addr->u_pcb.pcb_onfault)
E 11
				goto copyfault;
			printf("vm_fault(%x, %x, %x, 0) -> %x\n",
			       map, va, ftype, rv);
			printf("  type %x, code [mmu,,ssw]: %x\n",
			       type, code);
			goto dopanic;
		}
I 10
		ucode = v;
E 10
		i = (rv == KERN_PROTECTION_FAILURE) ? SIGBUS : SIGSEGV;
		break;
	    }
E 8
	}
D 10
	trapsignal(i, ucode);
E 10
I 10
	trapsignal(p, i, ucode);
E 10
D 14
	if ((type & USER) == 0)
E 14
I 14
	if ((type & T_USER) == 0)
E 14
		return;
out:
D 10
	p = u.u_procp;
D 2
	if (p->p_cursig || ISSIG(p))
		psig();
E 2
I 2
	if (i = CURSIG(p))
E 10
I 10
D 26
	while (i = CURSIG(p))
E 10
		psig(i);
E 2
	p->p_pri = p->p_usrpri;
D 10
	if (runrun) {
E 10
I 10
	if (want_resched) {
E 10
		/*
D 10
		 * Since we are u.u_procp, clock will normally just change
E 10
I 10
		 * Since we are curproc, clock will normally just change
E 10
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
		 */
D 17
		(void) splclock();
E 17
I 17
		s = splclock();
E 17
		setrq(p);
D 10
		u.u_ru.ru_nivcsw++;
E 10
I 10
		p->p_stats->p_ru.ru_nivcsw++;
E 10
		swtch();
I 17
		splx(s);
E 17
D 2
		if (ISSIG(p))
			psig();
E 2
I 2
D 10
		if (i = CURSIG(p))
E 10
I 10
		while (i = CURSIG(p))
E 10
			psig(i);
E 2
	}
D 10
	if (u.u_prof.pr_scale) {
E 10
I 10
	if (p->p_stats->p_prof.pr_scale) {
E 10
		int ticks;
D 10
		struct timeval *tv = &u.u_ru.ru_stime;
E 10
I 10
		struct timeval *tv = &p->p_stime;
E 10

		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks) {
#ifdef PROFTIMER
			extern int profscale;
D 10
			addupc(frame.f_pc, &u.u_prof, ticks * profscale);
E 10
I 10
			addupc(frame.f_pc, &p->p_stats->p_prof,
			    ticks * profscale);
E 10
#else
D 10
			addupc(frame.f_pc, &u.u_prof, ticks);
E 10
I 10
			addupc(frame.f_pc, &p->p_stats->p_prof, ticks);
E 10
#endif
		}
	}
I 23
#if defined(HP380)
	/*
	 * Deal with user mode writebacks.
	 * If any writeback fails, go back and attempt signal delivery.
	 * unless we have already been here and attempted the writeback
	 * (e.g. bad address with user ignoring SIGSEGV).  In that case
	 * we just return to the user without sucessfully completing
	 * the writebacks.  Maybe we should just drop the sucker?
	 */
	if (mmutype == MMU_68040 && frame.f_format == FMT7) {
		if (beenhere) {
#ifdef DEBUG
			if (mmudebug & MDB_WBFAILED)
			printf("pid %d(%s): writeback aborted, pc=%x, fa=%x\n",
			       p->p_pid, p->p_comm, frame.f_pc, v);
#endif
			;
		} else if (i = writeback(&frame, 1)) {
			beenhere++;
			ucode = v;
			syst = p->p_stime;
			trapsignal(p, i, ucode);
			goto out;
		}
	}
#endif
E 23
	curpri = p->p_pri;
E 26
I 26
	userret(p, &frame, sticks, v, 1);
E 26
}

I 23
D 26
#if defined(HP380)
E 26
I 26
#ifdef HP380
E 26
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
D 30

#ifdef HPFPLIB
fppanic(frame)
	struct fppanicframe {
		int	fpsaveframe;
		int	regs[16];
		int	fpregs[8*3];
		int	fpcregs[3];
		int	hole[5];
		int	oa6;
		short	sr;
		int	pc;
		short	vector;
	} frame;
{
	printf("FP exception: pid %d(%s): no busy frame, ft=%x pc=%x vec=%x\n",
	       curproc->p_pid, curproc->p_comm,
	       frame.fpsaveframe, frame.pc, frame.vector);
	panic("bad FP exception");
}
E 30
#endif
#endif
D 30
#endif
E 30

E 23
/*
D 14
 * Called from the trap handler when a system call occurs
E 14
I 14
 * Proces a system call.
E 14
 */
D 14
/*ARGSUSED*/
E 14
syscall(code, frame)
D 22
	volatile int code;
E 22
I 22
D 26
	volatile unsigned code;
E 26
I 26
	u_int code;
E 26
E 22
	struct frame frame;
{
	register caddr_t params;
D 26
	register int i;
E 26
	register struct sysent *callp;
D 2
	register struct proc *p;
E 2
I 2
D 10
	register struct proc *p = u.u_procp;
E 10
I 10
D 26
	register struct proc *p = curproc;
E 26
I 26
	register struct proc *p;
E 26
E 10
E 2
D 3
	register struct user *up;
E 3
D 2
	int opc, numsys;
E 2
I 2
D 17
	int error, opc, numsys;
E 17
I 17
D 37
	int error, opc, numsys, s;
E 37
I 37
	int error, opc, numsys;
E 37
I 26
	u_int argsize;
E 26
E 17
I 6
D 7
	int args[8], rval[2];
E 7
I 7
	struct args {
		int i[8];
	} args;
	int rval[2];
E 7
E 6
E 2
D 26
	struct timeval syst;
	struct sysent *systab;
I 23
#if defined(HP380)
	int beenhere = 0;
#endif
E 26
I 26
	u_quad_t sticks;
E 26
E 23
#ifdef HPUXCOMPAT
	extern struct sysent hpuxsysent[];
	extern int hpuxnsysent, notimp();
#endif

D 2
	/*
	 * We assign &u to a local variable for GCC.  This ensures that
	 * we can explicitly reload it after the call to qsetjmp below.
	 * If we don't do this, GCC may itself have assigned &u to a
	 * register variable which will not be properly reloaded, since
	 * GCC knows nothing of the funky semantics of qsetjmp.
	 */
	up = &u;

E 2
I 2
D 3
	up = &u;		/* this should probably be deleted */
E 3
E 2
	cnt.v_syscall++;
D 3
	syst = up->u_ru.ru_stime;
E 3
I 3
D 10
	syst = u.u_ru.ru_stime;
E 10
I 10
D 26
	syst = p->p_stime;
E 26
E 10
E 3
	if (!USERMODE(frame.f_sr))
		panic("syscall");
I 26
	p = curproc;
	sticks = p->p_sticks;
E 26
D 3
	up->u_ar0 = frame.f_regs;
	up->u_error = 0;
E 3
I 3
D 10
	u.u_ar0 = frame.f_regs;
E 10
I 10
D 21
	p->p_regs = frame.f_regs;
E 21
I 21
	p->p_md.md_regs = frame.f_regs;
E 21
E 10
D 6
	u.u_error = 0;
E 6
E 3
	opc = frame.f_pc - 2;
D 26
	systab = sysent;
	numsys = nsysent;
E 26
#ifdef HPUXCOMPAT
D 2
	if (up->u_procp->p_flag & SHPUX) {
E 2
I 2
D 26
	if (p->p_flag & SHPUX) {
E 2
		systab = hpuxsysent;
		numsys = hpuxnsysent;
	}
E 26
I 26
D 30
	if (p->p_flag & SHPUX)
E 30
I 30
	if (p->p_md.md_flags & MDP_HPUX)
E 30
		callp = hpuxsysent, numsys = hpuxnsysent;
	else
E 26
#endif
I 26
		callp = sysent, numsys = nsysent;
E 26
D 14
	params = (caddr_t)frame.f_regs[SP] + NBPW;
E 14
I 14
	params = (caddr_t)frame.f_regs[SP] + sizeof(int);
E 14
D 2
	/*
	 * We use entry 0 instead of 63 to signify an invalid syscall because
	 * HPUX uses 63 and 0 works just as well for our purposes.
	 */
	if (code == 0) {
		i = fuword(params);
E 2
I 2
D 26
	if (code == 0) {			/* indir */
E 26
I 26
	switch (code) {

D 32
	case SYS_indir:
E 32
I 32
	case SYS_syscall:
E 32
		/*
		 * Code is first argument, followed by actual args.
		 */
E 26
		code = fuword(params);
E 2
D 14
		params += NBPW;
E 14
I 14
		params += sizeof(int);
I 30
		/*
		 * XXX sigreturn requires special stack manipulation
		 * that is only done if entered via the sigreturn
		 * trap.  Cannot allow it here so make sure we fail.
		 */
		if (code == SYS_sigreturn)
			code = numsys;
E 30
E 14
D 2
		callp = ((unsigned)i >= numsys) ? &systab[0] : &systab[i];
	} else
		callp = (code >= numsys) ? &systab[0] : &systab[code];
	p = up->u_procp;
E 2
I 2
D 26
	}
	if (code >= numsys)
		callp = &systab[0];		/* indir (illegal) */
	else
		callp = &systab[code];
E 2
	if ((i = callp->sy_narg * sizeof (int)) &&
D 2
	    (up->u_error = copyin(params, (caddr_t)up->u_arg, (u_int)i))) {
E 2
I 2
D 3
	    (error = copyin(params, (caddr_t)up->u_arg, (u_int)i))) {
E 3
I 3
D 6
	    (error = copyin(params, (caddr_t)u.u_arg, (u_int)i))) {
E 6
I 6
D 7
	    (error = copyin(params, (caddr_t)args, (u_int)i))) {
E 7
I 7
	    (error = copyin(params, (caddr_t)&args, (u_int)i))) {
E 26
I 26
		break;

D 27
#ifdef SYS___indir
E 27
D 32
	case SYS___indir:
E 32
I 32
	case SYS___syscall:
E 32
		/*
D 32
		 * Like indir, but code is a quad, so as to maintain
E 32
I 32
		 * Like syscall, but code is a quad, so as to maintain
E 32
		 * quad alignment for the rest of the arguments.
		 */
E 26
E 7
E 6
E 3
E 2
#ifdef HPUXCOMPAT
D 30
		if (p->p_flag & SHPUX)
E 30
I 30
		if (p->p_md.md_flags & MDP_HPUX)
E 30
D 2
			up->u_error = bsdtohpuxerrno(up->u_error);
E 2
I 2
D 26
			error = bsdtohpuxerrno(error);
E 26
I 26
			break;
E 26
E 2
#endif
D 2
		frame.f_regs[D0] = (u_char) up->u_error;
E 2
I 2
D 13
		frame.f_regs[D0] = (u_char) error;
E 13
I 13
D 26
		frame.f_regs[D0] = error;
E 13
E 2
		frame.f_sr |= PSL_C;	/* carry bit */
E 26
I 26
D 27
		code = fuword(params + QUAD_LOWWORD * sizeof(int));
		params += sizeof(quad);
E 27
I 27
		code = fuword(params + _QUAD_LOWWORD * sizeof(int));
		params += sizeof(quad_t);
E 27
		break;
D 27
#endif
E 27

D 27
	/* nothing to do by default */
E 27
I 27
	default:
		/* nothing to do by default */
		break;
E 27
	}
	if (code < numsys)
		callp += code;
	else
D 32
		callp += SYS_indir;	/* => nosys */
E 32
I 32
		callp += SYS_syscall;	/* => nosys */
E 32
D 39
	argsize = callp->sy_narg * sizeof(int);
E 39
I 39
	argsize = callp->sy_argsize;
E 39
	if (argsize && (error = copyin(params, (caddr_t)&args, argsize))) {
E 26
#ifdef KTRACE
D 6
                if (KTRPOINT(p, KTR_SYSCALL))
                        ktrsyscall(p->p_tracep, code, callp->sy_narg);
E 6
I 6
		if (KTRPOINT(p, KTR_SYSCALL))
D 7
			ktrsyscall(p->p_tracep, code, callp->sy_narg, args);
E 7
I 7
D 39
			ktrsyscall(p->p_tracep, code, callp->sy_narg, args.i);
E 39
I 39
			ktrsyscall(p->p_tracep, code, argsize, args.i);
E 39
E 7
E 6
#endif
D 26
		goto done;
E 26
I 26
		goto bad;
E 26
	}
#ifdef KTRACE
D 6
        if (KTRPOINT(p, KTR_SYSCALL))
                ktrsyscall(p->p_tracep, code, callp->sy_narg);
E 6
I 6
	if (KTRPOINT(p, KTR_SYSCALL))
D 7
		ktrsyscall(p->p_tracep, code, callp->sy_narg, args);
E 7
I 7
D 39
		ktrsyscall(p->p_tracep, code, callp->sy_narg, args.i);
E 39
I 39
		ktrsyscall(p->p_tracep, code, argsize, args.i);
E 39
E 7
E 6
#endif
D 3
	up->u_r.r_val1 = 0;
	up->u_r.r_val2 = frame.f_regs[D0];
E 3
I 3
D 6
	u.u_r.r_val1 = 0;
	u.u_r.r_val2 = frame.f_regs[D0];
E 6
I 6
	rval[0] = 0;
	rval[1] = frame.f_regs[D1];
E 6
E 3
D 2
	/*
	 * qsetjmp only saves a6/a7.  This speeds things up in the common
	 * case (where saved values are never used).  There is a side effect
	 * however.  Namely, if we do return via longjmp() we must restore
	 * our own register variables.
	 */
	if (qsetjmp(&up->u_qsave)) {
		up = &u;
		if (up->u_error == 0 && up->u_eosys != RESTARTSYS)
			up->u_error = EINTR;
E 2
#ifdef HPUXCOMPAT
D 2
		/* there are some HPUX calls where we change u_ap */
		if (up->u_ap != up->u_arg) {
			up->u_ap = up->u_arg;
			printf("syscall(%d): u_ap changed\n", code);
		}
E 2
I 2
	/* debug kludge */
	if (callp->sy_call == notimp)
D 5
		error = notimp(code, callp->sy_narg);
E 5
I 5
D 6
		error = notimp(u.u_procp, u.u_ap, &u.u_r.r_val1,
			       code, callp->sy_narg);
E 6
I 6
D 7
		error = notimp(u.u_procp, args, rval, code, callp->sy_narg);
E 7
I 7
D 10
		error = notimp(u.u_procp, args.i, rval, code, callp->sy_narg);
E 10
I 10
D 39
		error = notimp(p, args.i, rval, code, callp->sy_narg);
E 39
I 39
		error = notimp(p, args.i, rval, code, argsize);
E 39
E 10
E 7
E 6
E 5
	else
E 2
#endif
D 2
	} else {
		up->u_eosys = NORMALRETURN;
E 2
I 2
D 3
	error = (*(callp->sy_call))(up);
E 3
I 3
D 4
	error = (*(callp->sy_call))(&u);
E 4
I 4
D 6
	error = (*callp->sy_call)(u.u_procp, u.u_ap, &u.u_r.r_val1);
E 4
E 3
	error = u.u_error;		/* XXX */
E 6
I 6
D 7
	error = (*callp->sy_call)(u.u_procp, args, rval);
E 7
I 7
D 10
	error = (*callp->sy_call)(u.u_procp, &args, rval);
E 10
I 10
D 26
	error = (*callp->sy_call)(p, &args, rval);
I 15
#ifdef DIAGNOSTIC
	if (curproc->p_spare[0])
		panic("syscall: M_NAMEI");
	if (curproc->p_spare[1])
		panic("syscall: STARTSAVE");
I 16
	if (curproc->p_spare[2])
		panic("syscall: LOCK COUNT");
E 16
#endif
E 15
E 10
E 7
E 6
	if (error == ERESTART)
		frame.f_pc = opc;
	else if (error != EJUSTRETURN) {
		if (error) {
E 2
#ifdef HPUXCOMPAT
D 2
		/* debug kludge */
		if (callp->sy_call == notimp)
			notimp(code, callp->sy_narg);
		else
#endif
		(*(callp->sy_call))(up);
	}
	/*
	 * Need to reinit p for two reason.  One, it is a register var
	 * and is not saved in the qsetjmp so a EINTR return will leave
	 * it with garbage.  Two, even on a normal return, it will be
	 * wrong for the child process of a fork (it will point to the
	 * parent).
	 */
	p = up->u_procp;
	if (up->u_eosys == NORMALRETURN) {
		if (up->u_error) {
#ifdef HPUXCOMPAT
E 2
			if (p->p_flag & SHPUX)
D 2
				up->u_error = bsdtohpuxerrno(up->u_error);
E 2
I 2
				error = bsdtohpuxerrno(error);
E 2
#endif
D 2
			frame.f_regs[D0] = (u_char) up->u_error;
E 2
I 2
D 13
			frame.f_regs[D0] = (u_char) error;
E 13
I 13
			frame.f_regs[D0] = error;
E 13
E 2
			frame.f_sr |= PSL_C;	/* carry bit */
I 2
D 3
#ifdef HPUXCOMPAT
			/* there are some HPUX calls where we change u_ap */
			/* is this still needed? */
			if (up->u_ap != up->u_arg) {
				up->u_ap = up->u_arg;
				printf("syscall(%d): u_ap changed\n", code);
			}
#endif
E 3
E 2
		} else {
D 3
			frame.f_regs[D0] = up->u_r.r_val1;
			frame.f_regs[D1] = up->u_r.r_val2;
E 3
I 3
D 6
			frame.f_regs[D0] = u.u_r.r_val1;
			frame.f_regs[D1] = u.u_r.r_val2;
E 6
I 6
			frame.f_regs[D0] = rval[0];
			frame.f_regs[D1] = rval[1];
E 6
E 3
			frame.f_sr &= ~PSL_C;
		}
D 2
	} else if (up->u_eosys == RESTARTSYS)
		frame.f_pc = opc;
	/* else if (up->u_eosys == JUSTRETURN) */
E 2
I 2
	}
	/* else if (error == EJUSTRETURN) */
E 2
		/* nothing to do */
E 26
I 26
		error = (*callp->sy_call)(p, &args, rval);
	switch (error) {
E 26
I 2

E 2
D 26
done:
	/*
I 2
	 * Reinitialize proc pointer `p' as it may be different
	 * if this is a child returning from fork syscall.
	 */
D 3
	p = up->u_procp;
#ifdef I_DONT_UNDERSTAND		/* XXX XXX */
E 3
I 3
D 10
	p = u.u_procp;
E 10
I 10
	p = curproc;
E 10
E 3
D 12
	/*
E 2
D 3
	 * The check for sigreturn (code 103) ensures that we don't
E 3
I 3
	 * XXX the check for sigreturn ensures that we don't
E 3
	 * attempt to set up a call to a signal handler (sendsig) before
	 * we have cleaned up the stack from the last call (sigreturn).
	 * Allowing this seems to lock up the machine in certain scenarios.
	 * What should really be done is to clean up the signal handling
	 * so that this is not a problem.
	 */
D 3
	if (code != 103 && (p->p_cursig || ISSIG(p)))
		psig();
I 2
#else
	if (i = CURSIG(p))
E 3
I 3
D 9
#include "syscall.h"
E 9
I 9
#include "sys/syscall.h"
E 9
D 10
	if (code != SYS_sigreturn && (i = CURSIG(p)))
E 3
		psig(i);
E 10
I 10
	if (code != SYS_sigreturn)
		while (i = CURSIG(p))
			psig(i);
E 12
I 12
	while (i = CURSIG(p))
		psig(i);
E 12
E 10
D 3
#endif
E 3
E 2
	p->p_pri = p->p_usrpri;
D 10
	if (runrun) {
E 10
I 10
	if (want_resched) {
E 26
I 26
	case 0:
E 26
E 10
		/*
D 10
		 * Since we are u.u_procp, clock will normally just change
E 10
I 10
D 26
		 * Since we are curproc, clock will normally just change
E 10
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 26
I 26
		 * Reinitialize proc pointer `p' as it may be different
		 * if this is a child returning from fork syscall.
E 26
		 */
D 17
		(void) splclock();
E 17
I 17
D 26
		s = splclock();
E 17
		setrq(p);
D 3
		up->u_ru.ru_nivcsw++;
E 3
I 3
D 10
		u.u_ru.ru_nivcsw++;
E 10
I 10
		p->p_stats->p_ru.ru_nivcsw++;
E 10
E 3
		swtch();
I 17
		splx(s);
E 17
I 2
D 5
		if (i = CURSIG(p))
E 5
I 5
D 10
		if (code != SYS_sigreturn && (i = CURSIG(p)))
E 5
			psig(i);
E 10
I 10
D 12
		if (code != SYS_sigreturn)
			while (i = CURSIG(p))
				psig(i);
E 12
I 12
		while (i = CURSIG(p))
			psig(i);
E 12
E 10
E 2
	}
D 3
	if (up->u_prof.pr_scale) {
E 3
I 3
D 10
	if (u.u_prof.pr_scale) {
E 10
I 10
	if (p->p_stats->p_prof.pr_scale) {
E 10
E 3
		int ticks;
D 3
		struct timeval *tv = &up->u_ru.ru_stime;
E 3
I 3
D 10
		struct timeval *tv = &u.u_ru.ru_stime;
E 10
I 10
		struct timeval *tv = &p->p_stime;
E 26
I 26
		p = curproc;
		frame.f_regs[D0] = rval[0];
		frame.f_regs[D1] = rval[1];
		frame.f_sr &= ~PSL_C;
		break;
E 26
E 10
E 3

D 26
		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks) {
#ifdef PROFTIMER
			extern int profscale;
D 3
			addupc(frame.f_pc, &up->u_prof, ticks * profscale);
E 3
I 3
D 10
			addupc(frame.f_pc, &u.u_prof, ticks * profscale);
E 10
I 10
			addupc(frame.f_pc, &p->p_stats->p_prof,
			    ticks * profscale);
E 10
E 3
#else
D 3
			addupc(frame.f_pc, &up->u_prof, ticks);
E 3
I 3
D 10
			addupc(frame.f_pc, &u.u_prof, ticks);
E 10
I 10
			addupc(frame.f_pc, &p->p_stats->p_prof, ticks);
E 26
I 26
	case ERESTART:
		frame.f_pc = opc;
		break;

	case EJUSTRETURN:
		break;		/* nothing to do */

	default:
	bad:
#ifdef HPUXCOMPAT
D 30
		if (p->p_flag & SHPUX)
E 30
I 30
		if (p->p_md.md_flags & MDP_HPUX)
E 30
			error = bsdtohpuxerrno(error);
E 26
E 10
E 3
#endif
D 26
		}
E 26
I 26
		frame.f_regs[D0] = error;
		frame.f_sr |= PSL_C;
		break;
E 26
	}
I 23
D 26
#if defined(HP380)
	/*
	 * Deal with writebacks when returning from sigreturn.
	 * They may generate another signal to be processed.
	 * Again, we don't attempt the writeback if we have already
	 * tried and failed (see comment in trap).
	 */
	if (mmutype == MMU_68040 && frame.f_format == FMT7) {
		if (beenhere) {
#ifdef DEBUG
			if (mmudebug & MDB_WBFAILED)
			printf("pid %d(%s): writeback aborted in sigreturn, pc=%x\n",
			       p->p_pid, p->p_comm, frame.f_pc);
#endif
			;
		} else if (i = writeback(&frame, 0)) {
			beenhere++;
			syst = p->p_stime;
			trapsignal(p, i, 0);
			goto done;
		}
	}
#endif
E 23
	curpri = p->p_pri;
E 26
I 26

	userret(p, &frame, sticks, (u_int)0, 0);
E 26
#ifdef KTRACE
D 6
        if (KTRPOINT(p, KTR_SYSRET))
                ktrsysret(p->p_tracep, code);
E 6
I 6
	if (KTRPOINT(p, KTR_SYSRET))
		ktrsysret(p->p_tracep, code, error, rval[0]);
E 6
#endif
}
E 1
