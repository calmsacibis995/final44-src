h33410
s 00014/00014/00312
d D 7.14 93/09/23 16:39:30 bostic 22 21
c changes for 4.4BSD-Lite requested by USL
e
s 00008/00008/00318
d D 7.13 93/09/21 08:00:19 bostic 21 20
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00324
d D 7.12 93/09/05 09:50:39 mckusick 20 19
c curpri => curpriority
e
s 00013/00013/00313
d D 7.11 90/12/16 16:46:53 bostic 19 18
c kernel reorg
e
s 00008/00005/00318
d D 7.10 90/06/25 14:29:35 karels 18 17
c use struct pointer for args (void * may be different on some machines)
e
s 00016/00017/00307
d D 7.9 90/06/24 15:04:50 karels 17 16
c new syscall convention; fix up indir code; syscall 63 no longer special
e
s 00001/00001/00323
d D 7.8 90/05/29 13:07:55 mckusick 16 15
c new calling convension for system calls
e
s 00020/00022/00304
d D 7.7 90/04/03 21:54:57 karels 15 14
c ISSIG => CURSIG; remove setjmp; use ERESTART to indicate restart
c of current syscall; reduce use of u.u_error; check for signals after giving
c up CPU
e
s 00016/00012/00310
d D 7.6 90/04/01 13:43:18 marc 14 13
c changes to syscall tracing (checked in by karels)
e
s 00015/00032/00307
d D 7.5 89/09/03 18:46:13 karels 13 12
c expunge u_code (pass directly); move nosys; regularize SIGBUS;
c comment out bogus KSP inval code (probably should remove)
e
s 00001/00002/00337
d D 7.4 89/07/04 09:58:46 mckusick 12 11
c pass &u to syscall routines (eventually to become a syscontext)
e
s 00000/00004/00339
d D 7.3 89/07/04 09:55:04 karels 11 10
c get rid of old compatibility code
e
s 00010/00023/00333
d D 7.2 89/07/04 09:52:28 marc 10 9
c KTRACE code
e
s 00013/00006/00344
d D 7.1 88/05/21 18:36:29 karels 9 8
c bring up to revision 7 for tahoe release
e
s 00001/00001/00349
d D 1.8 88/05/21 17:07:15 karels 8 7
c rename KDB => KADB
e
s 00006/00006/00344
d D 1.7 86/12/15 20:27:52 sam 7 6
c lint
e
s 00006/00001/00344
d D 1.6 86/11/25 16:43:13 sam 6 5
c kdb additions
e
s 00002/00002/00343
d D 1.5 86/07/16 08:27:55 sam 5 4
c mnemon spl's
e
s 00001/00001/00344
d D 1.4 86/01/09 01:23:56 sam 4 3
c typo
e
s 00018/00006/00327
d D 1.3 86/01/07 23:15:53 sam 3 2
c must insure bus errors and ksp not valid signals are handled 
c on the kernel stack (rather than the interrupt stack); do this by posting 
c an ast and reentering the kernel to service the posted signal on the kernel stack
e
s 00117/00259/00216
d D 1.2 86/01/05 18:42:44 sam 2 1
c 1st working version
e
s 00475/00000/00000
d D 1.1 85/07/22 21:00:29 sam 1 0
c date and time created 85/07/22 21:00:29 by sam
e
u
U
t
T
I 1
D 2
/*	trap.c	4.10	84/02/09	*/
E 2
I 2
D 9
/*	%M%	%I%	%E%	*/
E 9
I 9
/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 9
E 2

D 2
#include "../machine/psl.h"
#include "../machine/reg.h"
#include "../machine/pte.h"
E 2
I 2
D 9
#include "../tahoe/psl.h"
#include "../tahoe/reg.h"
#include "../tahoe/pte.h"
#include "../tahoe/mtpr.h"
E 2

E 9
D 2
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/seg.h"
#include "../machine/trap.h"
#include "../h/acct.h"
#include "../h/kernel.h"
#include "../machine/mtpr.h"
E 2
I 2
D 19
#include "param.h"
#include "systm.h"
D 12
#include "dir.h"
E 12
#include "user.h"
#include "proc.h"
#include "seg.h"
#include "acct.h"
#include "kernel.h"
E 19
I 19
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/seg.h"
#include "sys/acct.h"
#include "sys/kernel.h"
E 19
I 9

D 19
#include "psl.h"
#include "reg.h"
#include "pte.h"
#include "mtpr.h"
E 19
I 19
#include "../include/psl.h"
#include "../include/reg.h"
#include "../include/pte.h"
#include "../include/mtpr.h"
E 19
D 10

E 9
#define	SYSCALLTRACE
E 2
#ifdef SYSCALLTRACE
#include "../sys/syscalls.c"
E 10
I 10
#ifdef KTRACE
D 19
#include "ktrace.h"
E 19
I 19
#include "sys/ktrace.h"
E 19
E 10
#endif
D 2
#include "../machine/fp_in_krnl.h"
E 2

I 2
D 19
#include "../tahoe/trap.h"
E 19
I 19
#include "../include/trap.h"
E 19

E 2
#define	USER	040		/* user-mode flag added to type */

D 2
struct	sysent	sysent[];
int nsysent;
E 2
I 2
struct	sysent sysent[];
int	nsysent;
E 2

I 2
char	*trap_type[] = {
	"Reserved addressing mode",		/* T_RESADFLT */
	"Privileged instruction",		/* T_PRIVINFLT */
	"Reserved operand",			/* T_RESOPFLT */
	"Breakpoint",				/* T_BPTFLT */
	0,
	"Kernel call",				/* T_SYSCALL */
	"Arithmetic trap",			/* T_ARITHTRAP */
	"System forced exception",		/* T_ASTFLT */
	"Segmentation fault",			/* T_SEGFLT */
	"Protection fault",			/* T_PROTFLT */
	"Trace trap",				/* T_TRCTRAP */
	0,
	"Page fault",				/* T_PAGEFLT */
	"Page table fault",			/* T_TABLEFLT */
	"Alignment fault",			/* T_ALIGNFLT */
	"Kernel stack not valid",		/* T_KSPNOTVAL */
	"Bus error",				/* T_BUSERR */
I 6
D 13
	"Kernel debugger trap",			/* T_KDBTRAP */
E 13
I 13
	"Kernel debugger request",		/* T_KDBTRAP */
E 13
E 6
};
D 6
#define	TRAP_TYPES	(sizeof (trap_type) / sizeof (trap_type[0]))
E 6
I 6
int	TRAP_TYPES = sizeof (trap_type) / sizeof (trap_type[0]);
E 6

E 2
/*
 * Called from the trap handler when a processor trap occurs.
 */
I 2
/*ARGSUSED*/
E 2
trap(sp, type, hfs, accmst, acclst, dbl, code, pc, psl)
D 2
unsigned code;
E 2
I 2
D 13
	unsigned type, code;
E 13
I 13
	unsigned type, code;	/* kdb assumes these are *not* registers */
E 13
E 2
{
D 2
	/* Next 2 dummy variables MUST BE the first local */
	/* variables; leaving place for registers 0 and 1 */
	/* which are not preserved by the 'cct' */

	int	dumm1;		/* register 1 */
	int	dumm0;		/* register 0 */
	register dumm3;		/* register 12 is the 1'st register variable */
				/* in TAHOE  (register 11 in VAX) */

E 2
I 2
	int r0, r1;		/* must reserve space */
E 2
	register int *locr0 = ((int *)&psl)-PS;
	register int i;
I 13
	unsigned ucode = code;
E 13
	register struct proc *p;
	struct timeval syst;
D 2
	char	*typename;
E 2

I 2
#ifdef lint
	r0 = 0; r0 = r0; r1 = 0; r1 = r1;
#endif
E 2
	syst = u.u_ru.ru_stime;
	if (USERMODE(locr0[PS])) {
		type |= USER;
		u.u_ar0 = locr0;
	}
	switch (type) {

D 2
	default: switch (type) {
		case T_RESADFLT:
			typename = "reserved addressing mode";break;
		case T_PRIVINFLT:
			typename = "illegal opcode";break;
		case T_RESOPFLT:
			typename = "reserved operand";break;
		case T_BPTFLT:
			typename = "breakpoint";break;
		case T_SYSCALL:
			typename = "kernel call";break;
		case T_ARITHTRAP:
			typename = "arithmetic exception";break;
		case T_ASTFLT:
			typename = "system forced exception";break;
		case T_SEGFLT:
			typename = "limit fault";break;
		case T_PROTFLT:
			typename = "illegal access type";break;
		case T_TRCTRAP:
			typename = "trace trap";break;
		case T_PAGEFLT:
			typename = "page fault";break;
		case T_TABLEFLT:
			typename = "page table fault";break;
		case T_ALIGNFLT:
			typename = "alignment fault";break;
		case T_KSPNOTVAL:
			typename = "kernel stack not valid";break;
		}
		printf("System trap (%s), code = %x, pc = %x\n", 
				typename, code, pc);
		panic("trap");
E 2
I 2
	default:
I 6
D 8
#ifdef KDB
E 8
I 8
#ifdef KADB
E 8
		if (kdb_trap(&psl))
			return;
#endif
E 6
		printf("trap type %d, code = %x, pc = %x\n", type, code, pc);
		type &= ~USER;
		if (type < TRAP_TYPES && trap_type[type])
			panic(trap_type[type]);
		else
			panic("trap");
		/*NOTREACHED*/
E 2

D 2
	case T_PROTFLT + USER:	/* protection fault */
E 2
I 2
	case T_PROTFLT + USER:		/* protection fault */
E 2
		i = SIGBUS;
		break;

	case T_PRIVINFLT + USER:	/* privileged instruction fault */
D 2
	case T_RESADFLT + USER:	/* reserved addressing fault */
	case T_RESOPFLT + USER:	/* resereved operand fault */
	case T_ALIGNFLT + USER:	/* unaligned data fault */
E 2
I 2
	case T_RESADFLT + USER:		/* reserved addressing fault */
	case T_RESOPFLT + USER:		/* resereved operand fault */
	case T_ALIGNFLT + USER:		/* unaligned data fault */
E 2
D 13
		u.u_code = type &~ USER;
E 13
I 13
		ucode = type &~ USER;
E 13
		i = SIGILL;
		break;

D 2
	case T_ASTFLT + USER:	/* Allow process switch */
E 2
I 2
	case T_ASTFLT + USER:		/* Allow process switch */
E 2
	case T_ASTFLT:
		astoff();
D 22
		if ((u.u_procp->p_flag & SOWEUPC) && u.u_prof.pr_scale) {
E 22
I 22
		if ((u.u_procp->p_flag & P_OWEUPC) && u.u_prof.pr_scale) {
E 22
			addupc(pc, &u.u_prof, 1);
D 22
			u.u_procp->p_flag &= ~SOWEUPC;
E 22
I 22
			u.u_procp->p_flag &= ~P_OWEUPC;
E 22
		}
		goto out;

	case T_ARITHTRAP + USER:
D 13
		u.u_code = code;
E 13
		i = SIGFPE;
		break;

	/*
	 * If the user SP is above the stack segment,
	 * grow the stack automatically.
	 */
	case T_SEGFLT + USER:
		if (grow((unsigned)locr0[SP]) || grow(code))
			goto out;
		i = SIGSEGV;
		break;

D 2
	case T_TABLEFLT:		/* allow page table faults in kernel mode */
	case T_TABLEFLT + USER:   /* page table fault */
E 2
I 2
	case T_TABLEFLT:		/* allow page table faults in kernel */
	case T_TABLEFLT + USER:		/* page table fault */
E 2
		panic("ptable fault");

D 2
	case T_PAGEFLT:		/* allow page faults in kernel mode */
	case T_PAGEFLT + USER:	/* page fault */
E 2
I 2
	case T_PAGEFLT:			/* allow page faults in kernel mode */
	case T_PAGEFLT + USER:		/* page fault */
E 2
D 17
		i = u.u_error;
E 17
D 2
		if(fastreclaim(code) == 0)
			pagein(code, 0);
E 2
I 2
		pagein(code, 0);
E 2
D 17
		u.u_error = i;
E 17
		if (type == T_PAGEFLT)
			return;
		goto out;

D 2
	case T_BPTFLT + USER:	/* bpt instruction fault */
	case T_TRCTRAP + USER:	/* trace trap */
E 2
I 2
	case T_BPTFLT + USER:		/* bpt instruction fault */
	case T_TRCTRAP + USER:		/* trace trap */
E 2
		locr0[PS] &= ~PSL_T;
		i = SIGTRAP;
		break;
I 2

I 13
#ifdef notdef
	/* THIS CODE IS BOGUS- delete? (KSP not valid is unrecoverable)
	   And what does KSPNOTVAL in user-mode mean? */
E 13
I 3
	/*
	 * For T_KSPNOTVAL and T_BUSERR, can not allow spl to
	 * drop to 0 as clock could go off and we would end up
	 * doing an rei to the interrupt stack at ipl 0 (a
	 * reserved operand fault).  Instead, we allow psignal
	 * to post an ast, then return to user mode where we
	 * will reenter the kernel on the kernel's stack and
	 * can then service the signal.
	 */
E 3
E 2
	case T_KSPNOTVAL:
I 3
		if (noproc)
			panic("ksp not valid");
		/* fall thru... */
E 3
	case T_KSPNOTVAL + USER:
D 3
		i = SIGKILL;	/* There is nothing to do but to kill the 
				 * process.. */
		printf("KSP NOT VALID.\n");
		break;
E 3
I 3
D 4
		printf("pid %d: ksp not valid\n", u.u._procp->p_pid);
E 4
I 4
		printf("pid %d: ksp not valid\n", u.u_procp->p_pid);
I 13
panic("ksp not valid - 2");
E 13
E 4
		/* must insure valid kernel stack pointer? */
		psignal(u.u_procp, SIGKILL);
		return;
I 13
#endif
E 13
E 3

I 2
	case T_BUSERR + USER:
D 3
		i = SIGBUS;
E 3
D 13
		u.u_code = code;
D 3
		break;
E 3
I 3
		psignal(u.u_procp, SIGBUS);
		return;
E 13
I 13
		i = SIGBUS;
		break;
E 13
E 3
E 2
	}
D 13
	psignal(u.u_procp, i);
E 13
I 13
	trapsignal(i, ucode);
E 13
out:
	p = u.u_procp;
D 13
	if (p->p_cursig || ISSIG(p))
E 13
I 13
D 15
	if (ISSIG(p))
E 13
		psig();
E 15
I 15
	if (i = CURSIG(p))
D 22
		psig(i);
E 15
	p->p_pri = p->p_usrpri;
E 22
I 22
		postsig(i);
	p->p_priority = p->p_usrpri;
E 22
	if (runrun) {
		/*
		 * Since we are u.u_procp, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 21
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 21
I 21
		 * If that happened after we put ourselves on the run queue
D 22
		 * but before we swtch()'ed, we might not be on the queue
E 22
I 22
		 * but before we Xswitch()'ed, we might not be on the queue
E 22
		 * indicated by our priority.
E 21
		 */
D 5
		(void) spl8();
E 5
I 5
		(void) splclock();
E 5
D 21
		setrq(p);
E 21
I 21
		setrunqueue(p);
E 21
		u.u_ru.ru_nivcsw++;
D 22
		swtch();
E 22
I 22
		Xswitch();
E 22
I 13
D 15
		if (ISSIG(p))
			psig();
E 15
I 15
		if (i = CURSIG(p))
D 22
			psig(i);
E 22
I 22
			postsig(i);
E 22
E 15
E 13
	}
	if (u.u_prof.pr_scale) {
		int ticks;
		struct timeval *tv = &u.u_ru.ru_stime;

		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks)
			addupc(locr0[PC], &u.u_prof, ticks);
	}
D 20
	curpri = p->p_pri;
E 20
I 20
D 22
	curpriority = p->p_pri;
E 22
I 22
	curpriority = p->p_priority;
E 22
E 20
}

D 14
#ifdef SYSCALLTRACE
D 2
int syscalltrace = 0;
E 2
I 2
int	syscalltrace = 0;
E 2
#endif

E 14
/*
D 2
 * Called from the trap handler when a system call occurs
E 2
I 2
 * Called from locore when a system call occurs
E 2
 */
I 2
/*ARGSUSED*/
E 2
syscall(sp, type, hfs, accmst, acclst, dbl, code, pc, psl)
D 2
unsigned code;
E 2
I 2
	unsigned code;
E 2
{
D 2
	/* Next 2 dummy variables MUST BE the first local */
	/* variables; leaving place for registers 0 and 1 */
	/* which are not preserved by the 'cct' */

	int	dumm1;		/* register 1 */
	int	dumm0;		/* register 0 */
	register dumm3;		/* register 12 is the 1'st register variable */
				/* in TAHOE  (register 11 in VAX) */

E 2
I 2
	int r0, r1;			/* must reserve space */
E 2
	register int *locr0 = ((int *)&psl)-PS;
D 2
	register caddr_t params;		/* known to be r10 below */
	register int i;				/* known to be r9 below */
E 2
I 2
	register caddr_t params;
	register int i;
E 2
	register struct sysent *callp;
D 10
	register struct proc *p;
E 10
I 10
	register struct proc *p = u.u_procp;
E 10
D 2
	struct	timeval syst;
E 2
I 2
	struct timeval syst;
E 2
D 15
	int opc;
E 15
I 15
	int error, opc;
I 17
D 18
	int args[8], rval[2];
E 18
I 18
	struct args {
		int i[8];
	} args;
	int rval[2];
E 18
E 17
E 15

I 2
#ifdef lint
	r0 = 0; r0 = r0; r1 = 0; r1 = r1;
#endif
E 2
	syst = u.u_ru.ru_stime;
	if (!USERMODE(locr0[PS]))
		panic("syscall");
	u.u_ar0 = locr0;
D 2
	if (code == 139) {			/* XXX */
		sigcleanup();			/* XXX */
		goto done;			/* XXX */
E 2
I 2
D 11
	if (code == 139) {			/* 4.2 COMPATIBILTY XXX */
		osigcleanup();			/* 4.2 COMPATIBILTY XXX */
		goto done;			/* 4.2 COMPATIBILTY XXX */
E 2
	}
E 11
	params = (caddr_t)locr0[FP] + NBPW;
D 17
	u.u_error = 0;
E 17
D 2
	/*------ DIRTY CODE !!!!!!!!!---------*/
	/* try to reconstruct pc, assuming code is an immediate constant */
E 2
I 2
/* BEGIN GROT */
	/*
	 * Try to reconstruct pc, assuming code
	 * is an immediate constant
	 */
E 2
	opc = pc - 2;		/* short literal */
	if (code > 0x3f) {
D 2
		opc--;	/* byte immediate */
E 2
I 2
		opc--;				/* byte immediate */
E 2
		if (code > 0x7f) {
D 2
			opc--;	/* word immediate */
E 2
I 2
			opc--;			/* word immediate */
E 2
			if (code > 0x7fff)
				opc -= 2;	/* long immediate */
		}
	}
D 2
	/*------------------------------------*/
E 2
I 2
/* END GROT */
E 2
D 17
	callp = (code >= nsysent) ? &sysent[63] : &sysent[code];
	if (callp == sysent) {
		i = fuword(params);
E 17
I 17
	if (code == 0) {			/* indir */
		code = fuword(params);
E 17
		params += NBPW;
D 2
	callp = (code >= nsysent) ? &sysent[63] : &sysent[code];
E 2
I 2
D 17
		callp = (code >= nsysent) ? &sysent[63] : &sysent[code];
E 17
E 2
	}
I 17
	if (code >= nsysent)
		callp = &sysent[0];		/* indir (illegal) */
	else
		callp = &sysent[code];
E 17
D 2
	if (i = callp->sy_narg * sizeof (int)) {
		asm("prober $1,(r10),r9");		/* GROT */
		asm("bnequ ok");			/* GROT */
		u.u_error = EFAULT;			/* GROT */
		goto bad;				/* GROT */
asm("ok:");						/* GROT */
		bcopy(params,u.u_arg,i);
E 2
I 2
	if ((i = callp->sy_narg * sizeof (int)) &&
D 15
	    (u.u_error = copyin(params, (caddr_t)u.u_arg, (u_int)i)) != 0) {
		locr0[R0] = u.u_error;
E 15
I 15
D 17
	    (error = copyin(params, (caddr_t)u.u_arg, (u_int)i)) != 0) {
E 17
I 17
D 18
	    (error = copyin(params, (caddr_t)args, (u_int)i)) != 0) {
E 18
I 18
	    (error = copyin(params, (caddr_t)&args, (u_int)i)) != 0) {
E 18
E 17
		locr0[R0] = error;
E 15
		locr0[PS] |= PSL_C;	/* carry bit */
I 14
#ifdef KTRACE
		if (KTRPOINT(p, KTR_SYSCALL))
D 17
			ktrsyscall(p->p_tracep, code, callp->sy_narg);
E 17
I 17
D 18
			ktrsyscall(p->p_tracep, code, callp->sy_narg, args);
E 18
I 18
			ktrsyscall(p->p_tracep, code, callp->sy_narg, args.i);
E 18
E 17
#endif
E 14
		goto done;
E 2
	}
I 14
#ifdef KTRACE
	if (KTRPOINT(p, KTR_SYSCALL))
D 17
		ktrsyscall(p->p_tracep, code, callp->sy_narg);
E 17
I 17
D 18
		ktrsyscall(p->p_tracep, code, callp->sy_narg, args);
E 18
I 18
		ktrsyscall(p->p_tracep, code, callp->sy_narg, args.i);
E 18
E 17
#endif
E 14
D 2
	u.u_ap = u.u_arg;
	u.u_dirp = (caddr_t)u.u_arg[0];
E 2
D 17
	u.u_r.r_val1 = 0;
D 2
	u.u_r.r_val2 = locr0[R1]; /*------------ CHECK again */
E 2
I 2
	u.u_r.r_val2 = locr0[R1];
E 2
D 15
	if (setjmp(&u.u_qsave)) {
D 2
		if (u.u_error == 0 && u.u_eosys == JUSTRETURN)
E 2
I 2
		if (u.u_error == 0 && u.u_eosys != RESTARTSYS)
E 2
			u.u_error = EINTR;
	} else {
D 2
		u.u_eosys = JUSTRETURN;
E 2
I 2
		u.u_eosys = NORMALRETURN;
E 2
D 10
#ifdef SYSCALLTRACE
		if (syscalltrace) {
D 7
			register int i;
E 7
I 7
			register int a;
E 7
			char *cp;

			if (code >= nsysent)
				printf("0x%x", code);
			else
				printf("%s", syscallnames[code]);
			cp = "(";
D 7
			for (i= 0; i < callp->sy_narg; i++) {
				printf("%s%x", cp, u.u_arg[i]);
E 7
I 7
			for (a = 0; a < callp->sy_narg; a++) {
				printf("%s%x", cp, u.u_arg[a]);
E 7
				cp = ", ";
			}
D 7
			if (i)
				putchar(')', 0);
			putchar('\n', 0);
E 7
I 7
			if (a)
				printf(")");
			printf("\n");
E 7
		}
E 10
I 10
D 14
#ifdef KTRACE
		if (KTRPOINT(p, KTR_SYSCALL))
			ktrsyscall(p->p_tracep, code, callp->sy_narg);
E 10
#endif
E 14
D 2

		(*(callp->sy_call))();
E 2
I 2
D 12
		(*callp->sy_call)();
E 12
I 12
		(*callp->sy_call)(&u);
E 12
E 2
	}
D 2
	if (u.u_eosys == RESTARTSYS)
E 2
I 2
	if (u.u_eosys == NORMALRETURN) {
		if (u.u_error) {
			locr0[R0] = u.u_error;
E 15
I 15
D 16
	error = (*callp->sy_call)(&u);
E 16
I 16
	error = (*callp->sy_call)(u.u_procp, u.u_ap, &u.u_r.r_val1);
E 16
	error = u.u_error;		/* XXX */
E 17
I 17
	rval[0] = 0;
	rval[1] = locr0[R1];
D 18
	error = (*callp->sy_call)(u.u_procp, args, rval);
E 18
I 18
	error = (*callp->sy_call)(u.u_procp, &args, rval);
E 18
E 17
	if (error == ERESTART)
		pc = opc;
	else if (error != EJUSTRETURN) {
		if (error) {
			locr0[R0] = error;
E 15
			locr0[PS] |= PSL_C;	/* carry bit */
		} else {
			locr0[PS] &= ~PSL_C;	/* clear carry bit */
D 17
			locr0[R0] = u.u_r.r_val1;
			locr0[R1] = u.u_r.r_val2;
E 17
I 17
			locr0[R0] = rval[0];
			locr0[R1] = rval[1];
E 17
		}
D 15
	} else if (u.u_eosys == RESTARTSYS)
E 2
		pc = opc;
D 2
	else if (u.u_error) {
bad:
		locr0[R0] = u.u_error;
		locr0[PS] |= PSL_C;	/* carry bit */
	} else {
		locr0[PS] &= ~PSL_C;	/* clear carry bit */
		locr0[R0] = u.u_r.r_val1;
		locr0[R1] = u.u_r.r_val2;
	}
E 2
I 2
	/* else if (u.u_eosys == JUSTRETURN) */
E 15
I 15
	}
	/* else if (error == EJUSTRETURN) */
E 15
		/* nothing to do */
I 10
D 14
#ifdef KTRACE
	if (KTRPOINT(p, KTR_SYSRET))
		ktrsysret(p->p_tracep, code);
#endif
E 14
E 10
E 2
done:
I 14
	/*
	 * Reinitialize proc pointer `p' as it may be different
	 * if this is a child returning from fork syscall.
	 */
E 14
	p = u.u_procp;
D 15
	if (p->p_cursig || ISSIG(p))
		psig();
E 15
I 15
	if (i = CURSIG(p))
D 22
		psig(i);
E 15
	p->p_pri = p->p_usrpri;
E 22
I 22
		postsig(i);
	p->p_priority = p->p_usrpri;
E 22
	if (runrun) {
		/*
		 * Since we are u.u_procp, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 21
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 21
I 21
		 * If that happened after we put ourselves on the run queue
D 22
		 * but before we swtch()'ed, we might not be on the queue
E 22
I 22
		 * but before we Xswitch()'ed, we might not be on the queue
E 22
		 * indicated by our priority.
E 21
		 */
D 5
		(void) spl8();
E 5
I 5
		(void) splclock();
E 5
D 21
		setrq(p);
E 21
I 21
		setrunqueue(p);
E 21
		u.u_ru.ru_nivcsw++;
D 22
		swtch();
E 22
I 22
		Xswitch();
E 22
I 15
		if (i = CURSIG(p))
D 22
			psig(i);
E 22
I 22
			postsig(i);
E 22
E 15
	}
	if (u.u_prof.pr_scale) {
		int ticks;
		struct timeval *tv = &u.u_ru.ru_stime;

		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks)
			addupc(locr0[PC], &u.u_prof, ticks);
	}
D 20
	curpri = p->p_pri;
E 20
I 20
D 22
	curpriority = p->p_pri;
E 22
I 22
	curpriority = p->p_priority;
E 22
E 20
I 14
#ifdef KTRACE
	if (KTRPOINT(p, KTR_SYSRET))
D 17
		ktrsysret(p->p_tracep, code);
E 17
I 17
		ktrsysret(p->p_tracep, code, error, rval[0]);
E 17
#endif
E 14
}
D 13

/*
 * nonexistent system call-- signal process (may want to handle it)
 * flag error if process won't see signal immediately
 * Q: should we do that all the time ??
 */
nosys()
{
I 2

E 2
	if (u.u_signal[SIGSYS] == SIG_IGN || u.u_signal[SIGSYS] == SIG_HOLD)
		u.u_error = EINVAL;
	psignal(u.u_procp, SIGSYS);
}

I 2
#ifdef notdef
E 2
/*
 * Ignored system call
 */
nullsys()
{

}
D 2

fpemulate(hfsreg,acc_most,acc_least,dbl,op_most,op_least,opcode,pc,psl)
{
/*
 * Emulate the F.P. 'opcode'. Update psl flags as necessary.
 * If all OK, set 'opcode' to 0, else to the F.P. exception #.
 * Not all parameter longwords are relevant - depends on opcode.
 *
 * The entry mask is set so ALL registers are saved - courtesy of
 *  locore.s. This enables F.P. opcodes to change 'user' registers
 *  before return.
 */

 /* WARNING!!!! THIS CODE MUST NOT PRODUCE ANY FLOATING POINT EXCEPTIONS. */

	/* Next 2 dummy variables MUST BE the first local */
	/* variables; leaving place for registers 0 and 1 */
	/* which are not preserved by the 'cct' */

	int	dumm1;		/* register 1 */
	int	dumm0;		/* register 0 */
	register dumm3;		/* register 12 is the 1'st register variable */
				/* in TAHOE  (register 11 in VAX) */

	register int *locr0 = ((int *)&psl)-PS; /* R11 */
	int hfs = 0; 			/* returned data about exceptions */
	float (*f_proc)();		/* fp procedure to be called.	*/
	double (*d_proc)();		/* fp procedure to be called.	*/
	int dest_type;			/* float or double.	*/
	union{
		float ff;			/* float result. 	*/
		int fi;
	}f_res;
	union{
		double	dd;			/* double result.	*/
		int	di[2] ;
	}d_res;
	extern float 	Kcvtlf(), Kaddf(), Ksubf(), Kmulf(), Kdivf();
	extern double 	Kcvtld(), Kaddd(), Ksubd(), Kmuld(), Kdivd();
	extern float   	Ksinf(), Kcosf(), Katanf(), Klogf(), Ksqrtf(), Kexpf();
	
	

	switch(opcode & 0x0FF){

	case CVLF:	f_proc = Kcvtlf; dest_type = FLOAT; 
			locr0[PS] &= ~PSL_DBL;break;	/* clear double bit */
	case CVLD:	d_proc = Kcvtld; dest_type = DOUBLE; 
			locr0[PS] |= PSL_DBL; break;	/* turn on double bit */
	case ADDF:	f_proc = Kaddf; dest_type = FLOAT;
			break;
	case ADDD:	d_proc = Kaddd; dest_type = DOUBLE;
			break;
	case SUBF:	f_proc = Ksubf; dest_type = FLOAT;
			break;
	case SUBD:	d_proc = Ksubd; dest_type = DOUBLE;
			break;
	case MULF:	f_proc = Kmulf; dest_type = FLOAT;
			break;
	case MULD:	d_proc = Kmuld; dest_type = DOUBLE;
			break;
	case DIVF:	f_proc = Kdivf; dest_type = FLOAT;
			break;
	case DIVD:	d_proc = Kdivd; dest_type = DOUBLE;
			break;
	case SINF:	f_proc = Ksinf; dest_type = FLOAT;
			break;
	case COSF:	f_proc = Kcosf; dest_type = FLOAT;
			break;
	case ATANF:	f_proc = Katanf; dest_type = FLOAT;
			break;
	case LOGF:	f_proc = Klogf; dest_type = FLOAT;
			break;
	case SQRTF:	f_proc = Ksqrtf; dest_type = FLOAT;
			break;
	case EXPF:	f_proc = Kexpf; dest_type = FLOAT;
			break;
	}

	switch(dest_type){

	case FLOAT: 
		f_res.ff = (*f_proc)(acc_most,acc_least,op_most,op_least,&hfs);

		if (f_res.fi == 0 ) locr0[PS] |= PSL_Z;
		if (f_res.fi < 0 ) locr0[PS] |= PSL_N;
		break;
	case DOUBLE:
		d_res.dd = (*d_proc)(acc_most,acc_least,op_most,op_least,&hfs);
		if ((d_res.di[0] == 0) && (d_res.di[1] == 0))
						locr0[PS] |= PSL_Z;
		if (d_res.di[0] < 0 ) locr0[PS] |= PSL_N;
		break;
	}

	if (hfs & HFS_OVF){
		locr0[PS] |= PSL_V;	/* turn on overflow bit */
		/* if (locr0[PS] & PSL_IV)   {  /* overflow elabled?	*/
			opcode = OVF_EXC;
			u.u_error = (hfs & HFS_DOM) ? EDOM : ERANGE;
			return;
		/*}*/
	}
	else if (hfs & HFS_UNDF){
		if (locr0[PS] & PSL_FU){  /* underflow elabled?	*/
			opcode = UNDF_EXC;
			u.u_error = (hfs & HFS_DOM) ? EDOM : ERANGE;
			return;
		} 
	}
	else if (hfs & HFS_DIVZ){
		opcode = DIV0_EXC;
		return;
	}
	else if (hfs & HFS_DOM)
		u.u_error = EDOM;
	else if (hfs & HFS_RANGE)
		u.u_error = ERANGE;

	switch(dest_type){
	case FLOAT:
		if ((hfs & HFS_OVF) || (hfs & HFS_UNDF)) {
			f_res.ff = 0.0;
			locr0[PS] |= PSL_Z;
		}
		mvtofacc(f_res.ff, &acc_most);
		break;
	case DOUBLE:
		if ((hfs & HFS_OVF) || (hfs & HFS_UNDF)) {
			d_res.dd = 0.0;
			locr0[PS] |= PSL_Z;
		}
		mvtodacc(d_res.di[0], d_res.di[1], &acc_most);
		break;
	}
	opcode=0;
}
E 2
I 2
#endif
E 13
E 2
E 1
