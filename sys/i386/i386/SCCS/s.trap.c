h16699
s 00014/00014/00496
d D 8.4 93/09/23 16:42:48 bostic 30 29
c changes for 4.4BSD-Lite requested by USL
e
s 00010/00008/00500
d D 8.3 93/09/21 07:59:06 bostic 29 28
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00506
d D 8.2 93/09/05 09:45:11 mckusick 28 27
c curpri => curpriority
e
s 00002/00002/00506
d D 8.1 93/06/11 15:35:27 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00028/00506
d D 7.15 93/06/10 22:03:20 cgd 26 25
c fix headers which i botched
e
s 00034/00014/00500
d D 7.14 93/06/10 21:55:30 cgd 25 24
c update for new u_quad_t for ticks
e
s 00015/00015/00499
d D 7.13 92/10/11 10:11:06 bostic 24 23
c make kernel includes standard
e
s 00122/00039/00392
d D 7.12 92/07/14 14:53:21 bostic 23 22
c Split out the core part of page fault handling, so it can be called by
c subyte, suword and copyout.  Add a version of copyout that checks for a
c valid user address and user write permission, simulating faults if
c necessary (this is needed to deal with the fact that the 386 does not
c honor read-only pages for kernel accesses).  From Pace Willisson
e
s 00003/00003/00428
d D 7.11 92/05/20 16:47:59 bostic 22 21
c Move copyfault label so EFAULT type user errors will be handled
c correctly, as posted to comp.unix.bsd by pk@cs.few.eur.nl (Paul
c Kranenburg).  Also, handle T_STKFLT|T_USER safely (from 386bsd).
c from Pace Willisson (pace@blitz.com)
e
s 00002/00001/00429
d D 7.10 92/05/11 16:52:52 bostic 21 20
c fix NPX device handling; from Pace Willison
e
s 00003/00003/00427
d D 7.9 92/03/23 16:13:48 mckusick 20 19
c (code) to syscall() must be unsigned to catch negative numbers
e
s 00001/00001/00429
d D 7.8 92/03/20 13:53:39 bostic 19 18
c don't let negative codes get through
e
s 00002/00002/00428
d D 7.7 92/03/13 17:07:32 sklower 18 17
c p_regs => p_md.md_regs (checked in for sklower by torek)
e
s 00000/00001/00456
d D 7.6 91/11/20 17:49:42 mckusick 17 16
c no longer need seg.h
e
s 00037/00006/00420
d D 7.5 91/11/13 17:45:46 william 16 15
c changes to fix new vm on i386
e
s 00020/00063/00406
d D 7.4 91/05/13 01:11:21 william 15 14
c last whacks, numerious bugs and cleanups, sizing disabled due to
c bug I don't care to chase now, other nicer code withdrawn due to bugs
e
s 00017/00017/00452
d D 7.3 91/05/10 10:44:47 karels 14 13
c cleanups
e
s 00037/00033/00432
d D 7.2 91/05/09 21:44:59 william 13 12
c changes prior to net2 release
e
s 00095/00142/00370
d D 7.1 91/05/09 19:28:51 william 12 11
c interim version
e
s 00022/00005/00490
d D 5.10 91/04/15 17:50:15 william 11 10
c working version
e
s 00120/00058/00375
d D 5.9 91/04/15 17:49:17 william 10 9
c interim version
e
s 00010/00049/00423
d D 5.8 91/01/19 13:45:12 william 9 8
c minor cleanup, updated comments to reflect changes
e
s 00153/00068/00319
d D 5.7 91/01/19 13:04:56 william 8 7
c reno changes
e
s 00000/00000/00387
d D 5.6 91/01/15 12:22:05 bill 7 6
c reno changes
e
s 00003/00001/00384
d D 5.5 90/11/25 16:08:12 bill 6 5
c last changes before merger with reno version. cross fingers.
e
s 00045/00088/00340
d D 5.4 90/11/18 11:30:17 bill 5 4
c fix autoconf, move code to isa.c, remove debugging, drop redundant tlbflushes, macros for tlb et al
e
s 00037/00003/00391
d D 5.3 90/11/14 18:00:53 bill 4 3
c working version
e
s 00085/00032/00309
d D 5.2 90/06/23 19:33:53 donahn 3 2
c improvements
e
s 00103/00112/00238
d D 5.1 90/04/24 18:52:42 william 2 1
c 1st Berkeley Release
e
s 00350/00000/00000
d D 1.1 90/03/12 15:48:25 bill 1 0
c date and time created 90/03/12 15:48:25 by bill
e
u
U
t
T
I 4
/*-
D 27
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * This code is derived from software contributed to Berkeley by
 * the University of Utah, and William Jolitz.
 *
D 10
 * %sccs.include.386.c%
E 10
I 10
D 25
 * %sccs.include.redist.c%
E 25
I 25
D 26
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 25
E 10
 *
D 25
 *	%W% (Berkeley) %G%
E 25
I 25
D 26
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)trap.c	7.13 (Berkeley) 10/11/92
E 26
I 26
 *	%W% (Berkeley) %G%
E 26
E 25
 */

E 4
I 1
D 2
/*	trap.c	1.7	86/12/15	*/
E 2
I 2
D 8
/*
I 4
 * Copyright (c) 1989, 1990 William F. Jolitz
 */
E 8
D 10

E 10
/*
E 4
D 10
 * 386 Trap and System call handleing
E 10
I 10
D 12
 * 386 Trap and System call handling
E 12
I 12
 * 386 Trap and System call handleing
E 12
E 10
 */
E 2

I 12
D 24
#include "machine/cpu.h"
E 12
D 2
#include "../tahoe/psl.h"
#include "../tahoe/reg.h"
#include "../tahoe/pte.h"
#include "../tahoe/mtpr.h"
E 2
I 2
D 8
#include "../i386/psl.h"
#include "../i386/reg.h"
#include "../i386/pte.h"
#include "../i386/segments.h"
#include "../i386/frame.h"
E 8
I 8
#include "machine/psl.h"
#include "machine/reg.h"
E 24
I 24
#include <machine/cpu.h>
#include <machine/psl.h>
#include <machine/reg.h>
E 24
D 10
#include "machine/pte.h"
E 10
D 12
#include "machine/segments.h"
#include "machine/frame.h"
E 12
E 8
E 2

D 24
#include "param.h"
#include "systm.h"
D 8
#include "dir.h"
E 8
D 12
#include "user.h"
E 12
#include "proc.h"
I 12
#include "user.h"
E 12
D 17
#include "seg.h"
E 17
#include "acct.h"
#include "kernel.h"
E 24
I 24
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/acct.h>
#include <sys/kernel.h>
E 24
D 2
#define	SYSCALLTRACE
#ifdef SYSCALLTRACE
#include "../sys/syscalls.c"
#endif
E 2
I 2
D 10
#include "vm.h"
#include "cmap.h"
E 10
I 8
#ifdef KTRACE
D 24
#include "ktrace.h"
E 24
I 24
#include <sys/ktrace.h>
E 24
#endif
E 8
E 2

I 10
D 24
#include "vm/vm_param.h"
#include "vm/pmap.h"
#include "vm/vm_map.h"
E 24
I 24
#include <vm/vm_param.h>
#include <vm/pmap.h>
#include <vm/vm_map.h>
E 24
D 16
#include "sys/vmmeter.h"
E 16

E 10
D 2
#include "../tahoe/trap.h"
E 2
I 2
D 8
#include "../i386/trap.h"
E 8
I 8
D 24
#include "machine/trap.h"
I 10
#include "machine/dbg.h"
E 24
I 24
#include <machine/trap.h>
#include <machine/dbg.h>
E 24
E 10
E 8
E 2

I 13

E 13
D 4
#define	USER	040		/* user-mode flag added to type */
E 4
I 4
D 8
#define	USER	0x100		/* user-mode flag added to type */
E 8
I 8
D 12
#define	USER	0x40		/* user-mode flag added to type */
#define	FRMTRAP	0x100		/* distinguish trap from syscall */
E 8
E 4

E 12
struct	sysent sysent[];
int	nsysent;
I 15
unsigned rcr2();
extern short cpl;


E 15
I 8
D 9
#include "dbg.h"
E 9
E 8
D 2

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
	"Kernel debugger trap",			/* T_KDBTRAP */
};
int	TRAP_TYPES = sizeof (trap_type) / sizeof (trap_type[0]);

E 2
I 2
D 5
#include "dbg.h"
E 5
E 2
/*
D 9
 * Called from the trap handler when a processor trap occurs.
E 9
I 9
 * trap(frame):
 *	Exception, fault, and trap interface to BSD kernel. This
 * common code is called from assembly language IDT gate entry
 * routines that prepare a suitable stack frame, and restore this
 * frame after the exception has been processed. Note that the
 * effect is as if the arguments were passed call by reference.
E 9
 */
I 13
D 15
extern caddr_t edata;
E 13
I 2
D 8
unsigned *rcr2(), Sysbase;
E 8
I 8
unsigned rcr2(), Sysbase;
E 8
extern short cpl;
I 10
int um;
E 15
I 15

E 15
E 10
E 2
/*ARGSUSED*/
D 2
trap(sp, type, hfs, accmst, acclst, dbl, code, pc, psl)
	unsigned type, code;
E 2
I 2
trap(frame)
	struct trapframe frame;
D 12
#define type frame.tf_trapno
E 12
I 12
D 15
/*#define type frame.tf_trapno
E 12
#define code frame.tf_err
D 12
#define pc frame.tf_eip
E 12
I 12
#define pc frame.tf_eip*/
E 15
E 12
E 2
{
D 2
	int r0, r1;		/* must reserve space */
	register int *locr0 = ((int *)&psl)-PS;
E 2
I 2
D 5
	register int *locr0 = ((int *)&frame)/*-PS*/;
E 5
I 5
D 12
	register int *locr0 = ((int *)&frame);
E 12
E 5
E 2
	register int i;
D 12
	register struct proc *p;
E 12
I 12
	register struct proc *p = curproc;
E 12
D 25
	struct timeval syst;
E 25
I 25
	u_quad_t sticks;
E 25
I 2
D 13
	extern int nofault;
E 13
I 8
D 12
	int ucode;
E 12
I 12
	int ucode, type, code, eva;
I 16
	extern int cold;
E 16
E 12
D 10
	int oar0;
E 10
E 8
E 2

I 16
if(cold) goto we_re_toast;
E 16
I 10
D 13
#define DEBUG
E 13
E 10
I 8
D 15
#ifdef DEBUG
D 12
dprintf(DALLTRAPS, "\n%d. trap",u.u_procp->p_pid);
E 12
I 12
/*dprintf(DALLTRAPS, "\n%d(%s). trap",p->p_pid, p->p_comm);*/
E 12
dprintf(DALLTRAPS, " pc:%x cs:%x ds:%x eflags:%x isp %x\n",
		frame.tf_eip, frame.tf_cs, frame.tf_ds, frame.tf_eflags,
		frame.tf_isp);
dprintf(DALLTRAPS, "edi %x esi %x ebp %x ebx %x esp %x\n",
		frame.tf_edi, frame.tf_esi, frame.tf_ebp,
		frame.tf_ebx, frame.tf_esp);
dprintf(DALLTRAPS, "edx %x ecx %x eax %x\n",
		frame.tf_edx, frame.tf_ecx, frame.tf_eax);
D 10
p=u.u_procp;
E 10
I 10
D 12
/*p=u.u_procp;
E 12
I 12
/*
E 12
E 10
dprintf(DALLTRAPS, "sig %x %x %x \n",
D 10
		p->p_sigignore, p->p_sigcatch, p->p_sigmask);
E 10
I 10
		p->p_sigignore, p->p_sigcatch, p->p_sigmask); */
E 10
dprintf(DALLTRAPS, " ec %x type %x cpl %x ",
		frame.tf_err&0xffff, frame.tf_trapno, cpl);
I 10
D 12
/*pg("trap cr2 %x", rcr2());*/
E 12
I 12
D 13
pg("trap cr2 %x", rcr2());
E 13
I 13
printf("trap cr2 %x ", rcr2());
E 13
E 12
E 10
#endif
E 8
I 3
D 5
#ifdef DEBUG
E 3
D 2
#ifdef lint
	r0 = 0; r0 = r0; r1 = 0; r1 = r1;
#endif
E 2
I 2
dprintf(DALLTRAPS, "%d. trap",u.u_procp->p_pid);
dprintf(DALLTRAPS, "\npc:%x cs:%x ds:%x eflags:%x isp %x\n",
		frame.tf_eip, frame.tf_cs, frame.tf_ds, frame.tf_eflags,
		frame.tf_isp);
dprintf(DALLTRAPS, "edi %x esi %x ebp %x ebx %x esp %x\n",
		frame.tf_edi, frame.tf_esi, frame.tf_ebp,
		frame.tf_ebx, frame.tf_esp);
dprintf(DALLTRAPS, "edx %x ecx %x eax %x\n",
		frame.tf_edx, frame.tf_ecx, frame.tf_eax);
dprintf(DALLTRAPS|DPAUSE, "ec %x type %x cr0 %x cr2 %x cpl %x \n",
		frame.tf_err, frame.tf_trapno, rcr0(), rcr2(), cpl);
I 3
#endif
E 5
E 3

I 10
/*if(um && frame.tf_trapno == 0xc && (rcr2()&0xfffff000) == 0){
	if (ISPL(locr0[tCS]) != SEL_UPL) {
D 13
		if(nofault) goto anyways;
E 13
I 13
		if(curpcb->pcb_onfault) goto anyways;
E 13
		locr0[tEFLAGS] |= PSL_T;
		*(int *)PTmap |= 1; load_cr3(rcr3());
E 15
I 15
	frame.tf_eflags &= ~PSL_NT;	/* clear nested trap XXX */
	type = frame.tf_trapno;
	
D 22
	if (curpcb->pcb_onfault && frame.tf_trapno != 0xc) {
		frame.tf_eip = (int)curpcb->pcb_onfault;
E 22
I 22
	if (curpcb && curpcb->pcb_onfault && frame.tf_trapno != 0xc) {
copyfault:	frame.tf_eip = (int)curpcb->pcb_onfault;
E 22
E 15
		return;
	}
D 15
} else if (um) {
printf("p %x ", *(int *) PTmap);
*(int *)PTmap &= 0xfffffffe; load_cr3(rcr3());
printf("p %x ", *(int *) PTmap);
}
anyways:
E 15

D 15
if(pc == 0) um++;*/

E 10
D 3
	locr0[tEFLAGS] &= ~PSL_NT;	/* clear nested trap */
E 3
I 3
D 12
	locr0[tEFLAGS] &= ~PSL_NT;	/* clear nested trap XXX */
E 3
D 5
if(nofault && frame.tf_trapno != 0xc)
	{ locr0[tEIP] = nofault; return;}
E 5
I 5
D 8
	if(nofault && frame.tf_trapno != 0xc) {
		locr0[tEIP] = nofault; return;
	}
E 8
I 8
if(nofault && frame.tf_trapno != 0xc)
	{ locr0[tEIP] = nofault; return;}
E 12
I 12
	frame.tf_eflags &= ~PSL_NT;	/* clear nested trap XXX */
	type = frame.tf_trapno;
D 13
	if(nofault && frame.tf_trapno != 0xc)
		{ frame.tf_eip = nofault; return;}
E 13
I 13
	if(curpcb->pcb_onfault && frame.tf_trapno != 0xc)
		{ frame.tf_eip = (int)curpcb->pcb_onfault; return;}
E 13
E 12
E 8
E 5

E 15
E 2
D 12
	syst = u.u_ru.ru_stime;
I 8
D 10
oar0= u.u_ar0;
E 10
E 8
D 2
	if (USERMODE(locr0[PS])) {
E 2
I 2
D 4
	if (ISPL(locr0[tCS]) == SEL_UPL) {
E 4
I 4
D 5
	if (ISPL(locr0[tCS]) == SEL_UPL /*&& cpl == 0*/) {
#ifdef DEBUG
if(cpl) pg("user cpl %x trap %d", cpl, frame.tf_trapno);
if(((unsigned)frame.tf_eip) >= 0xfe000000) pg("user eip %x", frame.tf_eip);
#endif
E 5
I 5
	if (ISPL(locr0[tCS]) == SEL_UPL) {
E 12
I 12
D 25
	syst = p->p_stime;
E 25
	if (ISPL(frame.tf_cs) == SEL_UPL) {
E 12
E 5
E 4
E 2
D 13
		type |= USER;
E 13
I 13
		type |= T_USER;
E 13
D 12
		u.u_ar0 = locr0;
E 12
I 12
D 18
		p->p_regs = (int *)&frame;
E 18
I 18
		p->p_md.md_regs = (int *)&frame;
E 18
I 13
		curpcb->pcb_flags |= FM_TRAP;	/* used by sendsig */
I 25
		sticks = p->p_sticks;
E 25
E 13
E 12
	}
I 13
D 15
if((caddr_t)p < edata) printf("trap with curproc garbage ");
if((caddr_t)p->p_regs < edata) printf("trap with pregs garbage ");
E 15
E 13
I 12

E 12
I 8
	ucode=0;
I 12
	eva = rcr2();
	code = frame.tf_err;
E 12
E 8
	switch (type) {

	default:
I 3
D 15
bit_sucker:
E 15
I 15
	we_re_toast:
E 15
E 3
#ifdef KDB
		if (kdb_trap(&psl))
			return;
#endif
I 4
D 5
splhigh();
E 4
D 2
		printf("trap type %d, code = %x, pc = %x\n", type, code, pc);
E 2
I 2
		printf("trap type %d, code = %x, pc = %x cs = %x, eflags = %x\n", type, code, pc, frame.tf_cs, frame.tf_eflags);
E 5
I 5
D 8
		printf("trap type %d code %x pc %x cs %x eflags %x\n",
			type, code, pc, frame.tf_cs, frame.tf_eflags);
E 8
I 8

D 12
splhigh();
printf("cr2 %x cpl %x ", rcr2(), cpl);
		printf("trap type %d, code = %x, pc = %x cs = %x, eflags = %x\n", type, code, pc, frame.tf_cs, frame.tf_eflags);
E 12
I 12
		printf("trap type %d code = %x eip = %x cs = %x eflags = %x ",
			frame.tf_trapno, frame.tf_err, frame.tf_eip,
			frame.tf_cs, frame.tf_eflags);
		printf("cr2 %x cpl %x\n", eva, cpl);
E 12
E 8
E 5
E 2
D 13
		type &= ~USER;
E 13
I 13
		type &= ~T_USER;
E 13
I 8
D 12
pg("panic");
E 12
E 8
D 2
		if (type < TRAP_TYPES && trap_type[type])
			panic(trap_type[type]);
		else
			panic("trap");
E 2
I 2
		panic("trap");
E 2
		/*NOTREACHED*/

I 3
D 13
	case T_SEGNPFLT + USER:
E 3
	case T_PROTFLT + USER:		/* protection fault */
E 13
I 13
D 14
	case T_SEGNPFLT + T_USER:
	case T_PROTFLT + T_USER:		/* protection fault */
E 14
I 14
	case T_SEGNPFLT|T_USER:
I 22
	case T_STKFLT|T_USER:		/* 386bsd */
E 22
	case T_PROTFLT|T_USER:		/* protection fault */
E 14
E 13
I 10
D 22
copyfault:
E 22
E 10
I 3
D 8
		u.u_code = code + BUS_SEGM_FAULT ;
E 8
I 8
		ucode = code + BUS_SEGM_FAULT ;
E 8
E 3
		i = SIGBUS;
		break;

D 13
	case T_PRIVINFLT + USER:	/* privileged instruction fault */
	case T_RESADFLT + USER:		/* reserved addressing fault */
D 3
	case T_RESOPFLT + USER:		/* resereved operand fault */
E 3
I 3
	case T_RESOPFLT + USER:		/* reserved operand fault */
	case T_FPOPFLT + USER:		/* coprocessor operand fault */
E 3
D 2
	case T_ALIGNFLT + USER:		/* unaligned data fault */
E 2
D 8
		u.u_code = type &~ USER;
E 8
I 8
		ucode = type &~ USER;
E 13
I 13
D 14
	case T_PRIVINFLT + T_USER:	/* privileged instruction fault */
	case T_RESADFLT + T_USER:		/* reserved addressing fault */
	case T_RESOPFLT + T_USER:		/* reserved operand fault */
	case T_FPOPFLT + T_USER:		/* coprocessor operand fault */
E 14
I 14
	case T_PRIVINFLT|T_USER:	/* privileged instruction fault */
	case T_RESADFLT|T_USER:		/* reserved addressing fault */
	case T_RESOPFLT|T_USER:		/* reserved operand fault */
	case T_FPOPFLT|T_USER:		/* coprocessor operand fault */
E 14
		ucode = type &~ T_USER;
E 13
E 8
		i = SIGILL;
		break;

D 13
	case T_ASTFLT + USER:		/* Allow process switch */
E 13
I 13
D 14
	case T_ASTFLT + T_USER:		/* Allow process switch */
E 14
I 14
	case T_ASTFLT|T_USER:		/* Allow process switch */
E 14
E 13
	case T_ASTFLT:
		astoff();
D 12
		if ((u.u_procp->p_flag & SOWEUPC) && u.u_prof.pr_scale) {
			addupc(pc, &u.u_prof, 1);
			u.u_procp->p_flag &= ~SOWEUPC;
E 12
I 12
D 30
		if ((p->p_flag & SOWEUPC) && p->p_stats->p_prof.pr_scale) {
E 30
I 30
		if ((p->p_flag & P_OWEUPC) && p->p_stats->p_prof.pr_scale) {
E 30
			addupc(frame.tf_eip, &p->p_stats->p_prof, 1);
D 30
			p->p_flag &= ~SOWEUPC;
E 30
I 30
			p->p_flag &= ~P_OWEUPC;
E 30
E 12
		}
		goto out;

D 3
	case T_ARITHTRAP + USER:
E 3
I 3
D 13
	case T_DNA + USER:
E 13
I 13
D 14
	case T_DNA + T_USER:
E 14
I 14
	case T_DNA|T_USER:
E 14
E 13
D 8
		u.u_code = FPE_FPU_NP_TRAP;
E 8
I 8
D 21
#ifdef	NPX
E 21
I 21
#include "npx.h"
#if NNPX > 0
E 21
I 12
		/* if a transparent fault (due to context switch "late") */
E 12
		if (npxdna()) return;
#endif
		ucode = FPE_FPU_NP_TRAP;
E 8
		i = SIGFPE;
		break;

D 13
	case T_BOUND + USER:
E 13
I 13
D 14
	case T_BOUND + T_USER:
E 14
I 14
	case T_BOUND|T_USER:
E 14
E 13
D 8
		u.u_code = FPE_SUBRNG_TRAP;
E 8
I 8
		ucode = FPE_SUBRNG_TRAP;
E 8
		i = SIGFPE;
		break;

D 13
	case T_OFLOW + USER:
E 13
I 13
D 14
	case T_OFLOW + T_USER:
E 14
I 14
	case T_OFLOW|T_USER:
E 14
E 13
D 8
		u.u_code = FPE_INTOVF_TRAP;
E 8
I 8
		ucode = FPE_INTOVF_TRAP;
E 8
		i = SIGFPE;
		break;

E 3
I 2
D 13
	case T_DIVIDE + USER:
E 13
I 13
D 14
	case T_DIVIDE + T_USER:
E 14
I 14
	case T_DIVIDE|T_USER:
E 14
E 13
I 3
D 8
		u.u_code = FPE_INTDIV_TRAP;
E 8
I 8
		ucode = FPE_INTDIV_TRAP;
E 8
		i = SIGFPE;
		break;

D 13
	case T_ARITHTRAP + USER:
E 13
I 13
D 14
	case T_ARITHTRAP + T_USER:
E 14
I 14
	case T_ARITHTRAP|T_USER:
E 14
E 13
E 3
E 2
D 8
		u.u_code = code;
E 8
I 8
		ucode = code;
E 8
		i = SIGFPE;
		break;
I 8

E 8
D 5

E 5
I 5
D 9
#ifdef notdef
E 5
	/*
	 * If the user SP is above the stack segment,
	 * grow the stack automatically.
	 */
I 2
	case T_STKFLT + USER:
E 2
	case T_SEGFLT + USER:
D 2
		if (grow((unsigned)locr0[SP]) || grow(code))
E 2
I 2
D 5
		if (grow((unsigned)locr0[tESP]) /*|| grow(code)*/)
E 5
I 5
D 8
		if (grow((unsigned)locr0[tESP]))
E 8
I 8
		if (grow((unsigned)locr0[tESP]) /*|| grow(code)*/)
E 8
E 5
E 2
			goto out;
I 2
D 3
xxx:
E 3
I 3
D 8
		u.u_code = code;
E 8
I 8
		ucode = code;
E 8
E 3
E 2
		i = SIGSEGV;
		break;

	case T_TABLEFLT:		/* allow page table faults in kernel */
	case T_TABLEFLT + USER:		/* page table fault */
		panic("ptable fault");
I 5
#endif
E 5

E 9
	case T_PAGEFLT:			/* allow page faults in kernel mode */
I 6
D 15
		if (code & PGEX_P) goto bit_sucker;
E 15
I 15
		if (code & PGEX_P) goto we_re_toast;

E 15
		/* fall into */
E 6
D 13
	case T_PAGEFLT + USER:		/* page fault */
E 13
I 13
D 14
	case T_PAGEFLT + T_USER:		/* page fault */
E 14
I 14
	case T_PAGEFLT|T_USER:		/* page fault */
E 14
E 13
D 2
		i = u.u_error;
		pagein(code, 0);
		u.u_error = i;
E 2
I 2
D 5
			{ register u_int vp;
			struct pte *pte;
E 5
I 5
D 10
		{	register u_int vp;
			u_int ea;
E 10
I 10
	    {
		register vm_offset_t va;
I 12
		register struct vmspace *vm = p->p_vmspace;
E 12
		register vm_map_t map;
		int rv;
		vm_prot_t ftype;
		extern vm_map_t kernel_map;
D 23
		unsigned nss,v;
E 23
E 10
E 5

I 11
D 12
		va = trunc_page((vm_offset_t)rcr2());
E 12
I 12
		va = trunc_page((vm_offset_t)eva);
E 12
E 11
I 10
		/*
		 * It is only a kernel address space fault iff:
D 13
		 * 	1. (type & USER) == 0  and
		 * 	2. nofault not set or
		 *	3. nofault set but supervisor space data fault
E 13
I 13
		 * 	1. (type & T_USER) == 0  and
		 * 	2. pcb_onfault not set or
		 *	3. pcb_onfault set but supervisor space fault
E 13
		 * The last can occur during an exec() copyin where the
		 * argument space is lazy-allocated.
		 */
D 11
		if (type == T_PAGEFLT && (!nofault/*|| (code & PGEX_U) == 0*/))
E 11
I 11
D 13
		/*if (type == T_PAGEFLT && !nofault)*/
E 13
I 13
D 15
		/*if (type == T_PAGEFLT && !curpcb->pcb_onfault)*/
E 15
E 13
		if (type == T_PAGEFLT && va >= 0xfe000000)
E 11
			map = kernel_map;
		else
D 12
			map = u.u_procp->p_map;
E 12
I 12
			map = &vm->vm_map;
E 12
		if (code & PGEX_W)
			ftype = VM_PROT_READ | VM_PROT_WRITE;
		else
			ftype = VM_PROT_READ;
D 11
		va = trunc_page((vm_offset_t)rcr2());
E 11
I 11

E 11
E 10
I 8
D 23
#ifdef DEBUG
D 10
dprintf(DPAGIN|DALLTRAPS, "pf code %x pc %x usp %x cr2 %x |",
		code, frame.tf_eip, frame.tf_esp, rcr2());
E 10
I 10
		if (map == kernel_map && va == 0) {
D 12
			printf("trap: bad kernel access at %x\n", v);
E 12
I 12
			printf("trap: bad kernel access at %x\n", va);
E 12
D 15
			goto bit_sucker;
E 15
I 15
			goto we_re_toast;
E 15
		}
E 10
#endif
E 8
D 3
			if (rcr2() >= &Sysbase) goto xxx;
			vp = btop((int)rcr2());
			if (vp >= dptov(u.u_procp, u.u_procp->p_dsize) &&
			    vp < sptov(u.u_procp, u.u_procp->p_ssize-1)) {
				if (grow((unsigned)locr0[tESP]) || grow(rcr2()))
				goto out;
				else	{
if(nofault) { locr0[tEIP] = nofault; return;}
printf("didnt");
				i = SIGSEGV;
E 3
I 3
D 5
			if(u.u_procp->p_pid == 2) goto bit_sucker;
#define PGEX_P	0x01
			if (rcr2() >= &Sysbase || code & PGEX_P) {
E 5
I 5
D 10
			ea = (u_int)rcr2();

			/* out of bounds reference */
D 6
			if (ea >= &Sysbase && code & PGEX_P) {
E 6
I 6
D 8
			if (ea >= &Sysbase || code & PGEX_P) {
E 6
E 5
				u.u_code = code + BUS_PAGE_FAULT;
E 8
I 8
			if (ea >= (u_int)&Sysbase || code & PGEX_P) {
				ucode = code + BUS_PAGE_FAULT;
E 8
				i = SIGBUS;
E 3
				break;
E 10
I 10
		/*
		 * XXX: rude hack to make stack limits "work"
		 */
D 11
#ifdef notyet
E 11
		nss = 0;
D 12
		if ((caddr_t)va >= u.u_maxsaddr && map != kernel_map) {
E 12
I 12
		if ((caddr_t)va >= vm->vm_maxsaddr && map != kernel_map) {
E 12
			nss = clrnd(btoc(USRSTACK-(unsigned)va));
D 12
			if (nss > btoc(u.u_rlimit[RLIMIT_STACK].rlim_cur)) {
E 12
I 12
			if (nss > btoc(p->p_rlimit[RLIMIT_STACK].rlim_cur)) {
E 12
I 11
D 15
pg("stk fuck");
E 15
E 11
				rv = KERN_FAILURE;
				goto nogo;
E 10
I 3
D 5
			} else {
				vp = btop((int)rcr2());
				if (vp >= dptov(u.u_procp, u.u_procp->p_dsize)
				&& vp < sptov(u.u_procp, u.u_procp->p_ssize-1)){
					if (grow((unsigned)locr0[tESP])
					|| grow(rcr2()))
						goto out;
					else	if (nofault) {
						locr0[tEIP] = nofault;
						return;
					}
#ifdef DEBUG
pg("didnt ");
printf("\npc:%x cs:%x ds:%x eflags:%x isp %x\n",
		frame.tf_eip, frame.tf_cs, frame.tf_ds, frame.tf_eflags,
		frame.tf_isp);
printf("edi %x esi %x ebp %x ebx %x esp %x\n",
		frame.tf_edi, frame.tf_esi, frame.tf_ebp,
		frame.tf_ebx, frame.tf_esp);
printf("edx %x ecx %x eax %x\n",
		frame.tf_edx, frame.tf_ecx, frame.tf_eax);
printf("ec %x type %x cr0 %x cr2 %x cpl %x \n",
		frame.tf_err, frame.tf_trapno, rcr0(), rcr2(), cpl);
#endif
					i = SIGSEGV;
					break;
E 3
				}
I 3
				i = u.u_error;
				pagein(rcr2(), 0);
				u.u_error = i;
				if (type == T_PAGEFLT) return;
E 5
I 5
			}
E 5
D 10

D 5
				if(nofault) {
E 5
I 5
			/* stack reference to the running process? */
			vp = btop(ea);
			if (vp >= dptov(u.u_procp, u.u_procp->p_dsize)
			&& vp < sptov(u.u_procp, u.u_procp->p_ssize-1)){
				/* attempt to grow stack */
				if (grow((unsigned)locr0[tESP]) || grow(ea)) {
D 8
					if (type == T_PAGEFLT) return;
E 8
I 8
					if (type == T_PAGEFLT)
{
u.u_ar0 = oar0;
return;
}
E 8
					goto out;
				} else	if (nofault) {
I 8
u.u_ar0 = oar0;
E 8
E 5
					locr0[tEIP] = nofault;
					return;
				}
D 5
				goto out;
E 5
I 5
				i = SIGSEGV;
I 8
				ucode = code + BUS_PAGE_FAULT;
E 8
				break;
E 5
E 3
			}
I 5

D 8
			i = u.u_error;
			pagein(ea, 0);
			u.u_error = i;
E 8
I 8
			pagein(ea, 0, code);
E 8
			if (type == T_PAGEFLT) return;
E 10
I 10
		}
E 23
I 23
		rv = user_page_fault(p, map, va, ftype, type);
E 23
I 15

E 15
D 11
#endif
E 11
I 11
D 23
		/* check if page table is mapped, if not, fault it first */
D 12
		if (!PTD[(va>>PD_SHIFT)&1023].pd_v) {
E 12
I 12
#define pde_v(v) (PTD[((v)>>PD_SHIFT)&1023].pd_v)
		if (!pde_v(va)) {
E 12
			v = trunc_page(vtopte(va));
D 15
/*pg("pt fault");*/
E 15
			rv = vm_fault(map, v, ftype, FALSE);
			if (rv != KERN_SUCCESS) goto nogo;
			/* check if page table fault, increment wiring */
			vm_map_pageable(map, v, round_page(v+1), FALSE);
		} else v=0;
E 11
		rv = vm_fault(map, va, ftype, FALSE);
E 23
		if (rv == KERN_SUCCESS) {
D 23
			/*
			 * XXX: continuation of rude stack hack
			 */
D 12
			if (nss > u.u_ssize)
				u.u_ssize = nss;
E 12
I 12
			if (nss > vm->vm_ssize)
				vm->vm_ssize = nss;
E 12
I 11
			va = trunc_page(vtopte(va));
			/* for page table, increment wiring
			   as long as not a page table fault as well */
			if (!v && type != T_PAGEFLT)
			  vm_map_pageable(map, va, round_page(va+1), FALSE);
E 23
E 11
			if (type == T_PAGEFLT)
				return;
E 10
			goto out;
E 5
D 3
			i = u.u_error;
			pagein(rcr2(), 0);
			u.u_error = i;
E 2
		if (type == T_PAGEFLT)
D 2
			return;
		goto out;
E 2
I 2
				return;
if(nofault) { locr0[tEIP] = nofault; return;}
			goto out;
	}
E 3
I 3
		}
I 10
D 23
nogo:
E 23
I 23

E 23
I 11
D 15
/*pg("nogo");*/
E 15
E 11
		if (type == T_PAGEFLT) {
D 13
			if (nofault)
E 13
I 13
			if (curpcb->pcb_onfault)
E 13
				goto copyfault;
			printf("vm_fault(%x, %x, %x, 0) -> %x\n",
			       map, va, ftype, rv);
D 11
			printf("  type %x, code [mmu,,ssw]: %x\n",
E 11
I 11
			printf("  type %x, code %x\n",
E 11
			       type, code);
D 15
			goto bit_sucker;
E 15
I 15
			goto we_re_toast;
E 15
		}
		i = (rv == KERN_PROTECTION_FAILURE) ? SIGBUS : SIGSEGV;
		break;
	    }
E 10
E 3
E 2

I 3
	case T_TRCTRAP:	 /* trace trap -- someone single stepping lcall's */
D 12
		locr0[tEFLAGS] &= ~PSL_T;
E 12
I 12
		frame.tf_eflags &= ~PSL_T;
E 12
I 10
D 15
if (um) {*(int *)PTmap &= 0xfffffffe; load_cr3(rcr3()); }
E 15

E 10
			/* Q: how do we turn it on again? */
I 8
D 10
u.u_ar0 = oar0;
E 10
E 8
		return;
	
E 3
D 13
	case T_BPTFLT + USER:		/* bpt instruction fault */
	case T_TRCTRAP + USER:		/* trace trap */
E 13
I 13
D 14
	case T_BPTFLT + T_USER:		/* bpt instruction fault */
	case T_TRCTRAP + T_USER:		/* trace trap */
E 14
I 14
	case T_BPTFLT|T_USER:		/* bpt instruction fault */
	case T_TRCTRAP|T_USER:		/* trace trap */
E 14
E 13
D 2
		locr0[PS] &= ~PSL_T;
E 2
I 2
D 12
		locr0[tEFLAGS] &= ~PSL_T;
E 12
I 12
		frame.tf_eflags &= ~PSL_T;
E 12
E 2
		i = SIGTRAP;
		break;

I 5
D 9
#ifdef notdef
E 5
	/*
	 * For T_KSPNOTVAL and T_BUSERR, can not allow spl to
	 * drop to 0 as clock could go off and we would end up
	 * doing an rei to the interrupt stack at ipl 0 (a
	 * reserved operand fault).  Instead, we allow psignal
	 * to post an ast, then return to user mode where we
	 * will reenter the kernel on the kernel's stack and
	 * can then service the signal.
	 */
	case T_KSPNOTVAL:
		if (noproc)
			panic("ksp not valid");
		/* fall thru... */
	case T_KSPNOTVAL + USER:
		printf("pid %d: ksp not valid\n", u.u_procp->p_pid);
		/* must insure valid kernel stack pointer? */
D 8
		psignal(u.u_procp, SIGKILL);
E 8
I 8
		trapsignal(SIGKILL,0|FRMTRAP);
u.u_ar0 = oar0;
E 8
		return;

	case T_BUSERR + USER:
D 8
		u.u_code = code;
		psignal(u.u_procp, SIGBUS);
E 8
I 8
		trapsignal(SIGBUS, code|FRMTRAP);
u.u_ar0 = oar0;
E 8
		return;
I 5
#endif

E 9
#include "isa.h"
#if	NISA > 0
	case T_NMI:
D 13
	case T_NMI + USER:
E 13
I 13
D 14
	case T_NMI + T_USER:
E 14
I 14
	case T_NMI|T_USER:
E 14
E 13
I 12
		/* machine/parity/power fail/"kitchen sink" faults */
E 12
		if(isa_nmi(code) == 0) return;
D 15
		else goto bit_sucker;
E 15
I 15
		else goto we_re_toast;
E 15
#endif
E 5
	}
I 10
D 15
/*if(u.u_procp && (u.u_procp->p_pid == 1 || u.u_procp->p_pid == 3)) {
	if( *(u_char *) 0xf7c != 0xc7) {
		printf("%x!", *(u_char *) 0xf7c);
		*(u_char *) 0xf7c = 0xc7;
	}
}*/
E 15
I 15

E 15
E 10
D 8
	psignal(u.u_procp, i);
E 8
I 8
D 12
	trapsignal(i, ucode|FRMTRAP);
E 12
I 12
	trapsignal(p, i, ucode);
E 12
D 13
	if ((type & USER) == 0)
E 13
I 13
	if ((type & T_USER) == 0)
E 13
D 10
{
u.u_ar0 = oar0;
E 10
		return;
D 10
}
E 10
E 8
out:
D 12
	p = u.u_procp;
I 2
D 8

D 3
if(p->p_cursig)
printf("out cursig %x flg %x sig %x ign %x msk %x\n", 
	p->p_cursig,
	p->p_flag, p->p_sig, p->p_sigignore, p->p_sigmask);

E 3
E 2
	if (p->p_cursig || ISSIG(p))
D 2
		psig();
E 2
I 2
		psig(1);
E 8
I 8
	if (i = CURSIG(p))
		psig(i,FRMTRAP);
E 12
I 12
	while (i = CURSIG(p))
D 30
		psig(i);
E 12
E 8
E 2
	p->p_pri = p->p_usrpri;
E 30
I 30
		postsig(i);
	p->p_priority = p->p_usrpri;
E 30
D 12
	if (runrun) {
E 12
I 12
	if (want_resched) {
I 16
		int pl;
I 29

E 29
E 16
E 12
		/*
D 12
		 * Since we are u.u_procp, clock will normally just change
E 12
I 12
		 * Since we are curproc, clock will normally just change
E 12
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 29
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 29
I 29
		 * If that happened after we put ourselves on the run queue
D 30
		 * but before we swtch()'ed, we might not be on the queue
E 30
I 30
		 * but before we switched, we might not be on the queue
E 30
		 * indicated by our priority.
E 29
		 */
D 16
		(void) splclock();
E 16
I 16
		pl = splclock();
E 16
D 29
		setrq(p);
E 29
I 29
		setrunqueue(p);
E 29
D 12
		u.u_ru.ru_nivcsw++;
E 12
I 12
		p->p_stats->p_ru.ru_nivcsw++;
E 12
D 30
		swtch();
E 30
I 30
		mi_switch();
E 30
I 16
		splx(pl);
E 16
I 4
D 8
		(void)spl0();
E 8
I 8
D 12
		if (i = CURSIG(p))
			psig(i,FRMTRAP);
E 12
I 12
		while (i = CURSIG(p))
D 30
			psig(i);
E 30
I 30
			postsig(i);
E 30
E 12
E 8
E 4
	}
D 12
	if (u.u_prof.pr_scale) {
E 12
I 12
	if (p->p_stats->p_prof.pr_scale) {
E 12
D 25
		int ticks;
D 12
		struct timeval *tv = &u.u_ru.ru_stime;
E 12
I 12
		struct timeval *tv = &p->p_stime;
E 25
I 25
		u_quad_t ticks = p->p_sticks - sticks;
E 25
E 12

D 25
		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
E 25
D 12
		if (ticks)
D 2
			addupc(locr0[PC], &u.u_prof, ticks);
E 2
I 2
			addupc(pc, &u.u_prof, ticks);
E 12
I 12
		if (ticks) {
#ifdef PROFTIMER
			extern int profscale;
			addupc(frame.tf_eip, &p->p_stats->p_prof,
			    ticks * profscale);
#else
			addupc(frame.tf_eip, &p->p_stats->p_prof, ticks);
#endif
		}
E 12
E 2
	}
D 28
	curpri = p->p_pri;
E 28
I 28
D 30
	curpriority = p->p_pri;
E 30
I 30
	curpriority = p->p_priority;
E 30
E 28
I 13
	curpcb->pcb_flags &= ~FM_TRAP;	/* used by sendsig */
E 13
I 8
D 10
u.u_ar0 = oar0;
E 10
I 10
D 12
/*if(u.u_procp->p_pid == 3)
		locr0[tEFLAGS] |= PSL_T;
if(u.u_procp->p_pid == 1 && (pc == 0xec9 || pc == 0xebd))
		locr0[tEFLAGS] |= PSL_T;*/
I 11
spl0(); /*XXX*/
E 11
E 10
E 8
I 2
#undef type
#undef code
#undef pc
E 12
I 12
D 16
	spl0(); /*XXX*/
E 16
E 12
E 2
}

D 2
#ifdef SYSCALLTRACE
int	syscalltrace = 0;
#endif

E 2
/*
D 9
 * Called from locore when a system call occurs
E 9
I 9
 * syscall(frame):
 *	System call request from POSIX system call gate interface to kernel.
 * Like trap(), argument is call by reference.
E 9
 */
I 2
D 3
int fuckup;
E 3
E 2
/*ARGSUSED*/
D 2
syscall(sp, type, hfs, accmst, acclst, dbl, code, pc, psl)
	unsigned code;
E 2
I 2
syscall(frame)
D 12
	struct syscframe frame;
D 10
#define code frame.sf_eax	/* note: written over! */
E 10
I 10
/*#define code frame.sf_eax	/* note: written over! */
E 10
#define pc frame.sf_eip
E 12
I 12
	volatile struct syscframe frame;
E 12
E 2
{
D 2
	int r0, r1;			/* must reserve space */
	register int *locr0 = ((int *)&psl)-PS;
E 2
I 2
D 5
	register int *locr0 = ((int *)&frame)/*-PS*/;
E 5
I 5
D 8
	register int *locr0 = ((int *)&frame);
E 8
I 8
D 9
	register int *locr0 = ((int *)&frame)/*-PS*/;
E 9
I 9
	register int *locr0 = ((int *)&frame);
E 9
E 8
E 5
E 2
	register caddr_t params;
	register int i;
	register struct sysent *callp;
D 12
	register struct proc *p;
E 12
I 12
	register struct proc *p = curproc;
E 12
D 25
	struct timeval syst;
E 25
I 25
	u_quad_t sticks;
E 25
D 8
	int opc;
E 8
I 8
	int error, opc;
	int args[8], rval[2];
I 10
D 15
int code;
E 15
I 15
D 20
	int code;
E 20
I 20
	unsigned int code;
E 20
E 15
E 10
E 8

#ifdef lint
	r0 = 0; r0 = r0; r1 = 0; r1 = r1;
#endif
D 12
	syst = u.u_ru.ru_stime;
I 8
	p = u.u_procp;
E 8
D 2
	if (!USERMODE(locr0[PS]))
E 2
I 2
	if (ISPL(locr0[sCS]) != SEL_UPL)
I 8
{
printf("\npc:%x cs:%x eflags:%x\n",
		frame.sf_eip, frame.sf_cs, frame.sf_eflags);
printf("edi %x esi %x ebp %x ebx %x esp %x\n",
		frame.sf_edi, frame.sf_esi, frame.sf_ebp,
		frame.sf_ebx, frame.sf_esp);
printf("edx %x ecx %x eax %x\n", frame.sf_edx, frame.sf_ecx, frame.sf_eax);
printf("cr0 %x cr2 %x cpl %x \n", rcr0(), rcr2(), cpl);
E 12
I 12
D 25
	syst = p->p_stime;
E 25
I 25
	sticks = p->p_sticks;
E 25
	if (ISPL(frame.sf_cs) != SEL_UPL)
E 12
E 8
I 3
D 5
{
printf("\npc:%x cs:%x eflags:%x\n",
		frame.sf_eip, frame.sf_cs, frame.sf_eflags);
printf("edi %x esi %x ebp %x ebx %x esp %x\n",
		frame.sf_edi, frame.sf_esi, frame.sf_ebp,
		frame.sf_ebx, frame.sf_esp);
printf("edx %x ecx %x eax %x\n", frame.sf_edx, frame.sf_ecx, frame.sf_eax);
printf("cr0 %x cr2 %x cpl %x \n", rcr0(), rcr2(), cpl);
E 5
E 3
E 2
		panic("syscall");
I 8
D 12
}
I 10
if (um) {*(int *)PTmap &= 0xfffffffe; load_cr3(rcr3()); }
/*if(u.u_procp && (u.u_procp->p_pid == 1 || u.u_procp->p_pid == 3)) {
	if( *(u_char *) 0xf7c != 0xc7) {
		printf("%x!", *(u_char *) 0xf7c);
		*(u_char *) 0xf7c = 0xc7;
	}
}*/
E 10
E 8
I 3
D 5
}
I 4
#ifdef DEBUG
if(cpl) pg("User cpl %x", cpl);
#endif
E 5
E 4
E 3
	u.u_ar0 = locr0;
D 2
	if (code == 139) {			/* 4.2 COMPATIBILTY XXX */
		osigcleanup();			/* 4.2 COMPATIBILTY XXX */
		goto done;			/* 4.2 COMPATIBILTY XXX */
	}
	params = (caddr_t)locr0[FP] + NBPW;
E 2
I 2
D 3
svfpsp();
E 3
	params = (caddr_t)locr0[sESP] + NBPW ;
I 10
code = frame.sf_eax;
E 12
E 10
E 2
D 8
	u.u_error = 0;
E 8
I 8

I 12
	code = frame.sf_eax;
D 18
	p->p_regs = (int *)&frame;
E 18
I 18
	p->p_md.md_regs = (int *)&frame;
E 18
I 16
	curpcb->pcb_flags &= ~FM_TRAP;	/* used by sendsig */
E 16
D 13
	params = (caddr_t)frame.sf_esp + sizeof(int);
E 13
I 13
	params = (caddr_t)frame.sf_esp + sizeof (int) ;
E 13

E 12
E 8
D 2
/* BEGIN GROT */
E 2
	/*
D 2
	 * Try to reconstruct pc, assuming code
	 * is an immediate constant
E 2
I 2
	 * Reconstruct pc, assuming lcall $X,y is 7 bytes, as it is always.
E 2
	 */
D 2
	opc = pc - 2;		/* short literal */
	if (code > 0x3f) {
		opc--;				/* byte immediate */
		if (code > 0x7f) {
			opc--;			/* word immediate */
			if (code > 0x7fff)
				opc -= 2;	/* long immediate */
		}
	}
/* END GROT */
E 2
I 2
D 12
	opc = pc - 7;
E 12
I 12
	opc = frame.sf_eip - 7;
E 12
E 2
D 19
	callp = (code >= nsysent) ? &sysent[63] : &sysent[code];
E 19
I 19
D 20
	callp = ((u_int)code >= nsysent) ? &sysent[63] : &sysent[code];
E 20
I 20
	callp = (code >= nsysent) ? &sysent[63] : &sysent[code];
E 20
E 19
	if (callp == sysent) {
D 20
		i = fuword(params);
E 20
I 20
		code = fuword(params);
E 20
D 12
		params += NBPW;
E 12
I 12
D 13
		params += sizeof(int);
E 13
I 13
		params += sizeof (int);
E 13
E 12
		callp = (code >= nsysent) ? &sysent[63] : &sysent[code];
	}
I 8
D 10
/*dprintf(DALLSYSC,"%d. call %d ", p->p_pid, code);*/
E 10
I 10
D 15
dprintf(DALLSYSC,"%d. call %d ", p->p_pid, code);
E 15
I 15

E 15
E 10
E 8
I 2
D 4
/*dprintf(DALLSYSC,"%d. call %d\n", u.u_procp->p_pid, code);*/
E 4
I 4
D 5
dprintf(DALLSYSC,"%d. call %d\n", u.u_procp->p_pid, code);
E 5
E 4
E 2
	if ((i = callp->sy_narg * sizeof (int)) &&
D 8
	    (u.u_error = copyin(params, (caddr_t)u.u_arg, (u_int)i)) != 0) {
D 2
		locr0[R0] = u.u_error;
		locr0[PS] |= PSL_C;	/* carry bit */
E 2
I 2
		locr0[sEAX] = u.u_error;
E 8
I 8
	    (error = copyin(params, (caddr_t)args, (u_int)i))) {
D 10
		locr0[sEAX] = (u_char) error;
E 10
I 10
D 12
		locr0[sEAX] = /*(u_char)*/ error;
E 10
E 8
		locr0[sEFLAGS] |= PSL_C;	/* carry bit */
I 8
D 10
#ifdef KTRACE
E 10
I 10
#ifdef KTRACEx
E 12
I 12
		frame.sf_eax = error;
		frame.sf_eflags |= PSL_C;	/* carry bit */
#ifdef KTRACE
E 12
E 10
		if (KTRPOINT(p, KTR_SYSCALL))
			ktrsyscall(p->p_tracep, code, callp->sy_narg, &args);
#endif
E 8
E 2
		goto done;
	}
D 8
	u.u_r.r_val1 = 0;
D 2
	u.u_r.r_val2 = locr0[R1];
E 2
I 2
	u.u_r.r_val2 = locr0[sEDX];
E 2
	if (setjmp(&u.u_qsave)) {
		if (u.u_error == 0 && u.u_eosys != RESTARTSYS)
			u.u_error = EINTR;
	} else {
		u.u_eosys = NORMALRETURN;
D 2
#ifdef SYSCALLTRACE
		if (syscalltrace) {
			register int a;
			char *cp;

			if (code >= nsysent)
				printf("0x%x", code);
			else
				printf("%s", syscallnames[code]);
			cp = "(";
			for (a = 0; a < callp->sy_narg; a++) {
				printf("%s%x", cp, u.u_arg[a]);
				cp = ", ";
			}
			if (a)
				printf(")");
			printf("\n");
		}
#endif
E 2
		(*callp->sy_call)();
	}
I 2
D 3
/*rsfpsp();*/
E 3
E 2
	if (u.u_eosys == NORMALRETURN) {
		if (u.u_error) {
D 2
			locr0[R0] = u.u_error;
			locr0[PS] |= PSL_C;	/* carry bit */
E 2
I 2
D 5
/*dprintf(DSYSFAIL,"%d. fail %d %d\n",u.u_procp->p_pid,  code, u.u_error);*/
E 5
			locr0[sEAX] = u.u_error;
E 8
I 8
D 10
#ifdef KTRACE
E 10
I 10
D 12
#ifdef KTRACEx
E 12
I 12
#ifdef KTRACE
E 12
E 10
	if (KTRPOINT(p, KTR_SYSCALL))
		ktrsyscall(p->p_tracep, code, callp->sy_narg, &args);
#endif
	rval[0] = 0;
D 12
	rval[1] = locr0[sEDX];
E 12
I 12
	rval[1] = frame.sf_edx;
E 12
	error = (*callp->sy_call)(p, args, rval);
	if (error == ERESTART)
D 12
		pc = opc;
E 12
I 12
		frame.sf_eip = opc;
E 12
	else if (error != EJUSTRETURN) {
		if (error) {
D 10
			locr0[sEAX] = (u_char) error;
E 10
I 10
D 12
			locr0[sEAX] = error;
E 10
E 8
			locr0[sEFLAGS] |= PSL_C;	/* carry bit */
E 12
I 12
			frame.sf_eax = error;
			frame.sf_eflags |= PSL_C;	/* carry bit */
E 12
E 2
		} else {
D 2
			locr0[PS] &= ~PSL_C;	/* clear carry bit */
			locr0[R0] = u.u_r.r_val1;
			locr0[R1] = u.u_r.r_val2;
E 2
I 2
D 8
			locr0[sEFLAGS] &= ~PSL_C;	/* clear carry bit */
			locr0[sEAX] = u.u_r.r_val1;
			locr0[sEDX] = u.u_r.r_val2;
E 8
I 8
D 12
			locr0[sEAX] = rval[0];
			locr0[sEDX] = rval[1];
			locr0[sEFLAGS] &= ~PSL_C;	/* carry bit */
E 12
I 12
			frame.sf_eax = rval[0];
			frame.sf_edx = rval[1];
			frame.sf_eflags &= ~PSL_C;	/* carry bit */
E 12
E 8
E 2
		}
D 8
	} else if (u.u_eosys == RESTARTSYS)
		pc = opc;
	/* else if (u.u_eosys == JUSTRETURN) */
E 8
I 8
	}
	/* else if (error == EJUSTRETURN) */
E 8
		/* nothing to do */
done:
I 8
	/*
	 * Reinitialize proc pointer `p' as it may be different
	 * if this is a child returning from fork syscall.
	 */
E 8
D 12
	p = u.u_procp;
D 8
	if (p->p_cursig || ISSIG(p))
D 2
		psig();
E 2
I 2
		psig(0);
E 8
I 8
	/*
	 * XXX the check for sigreturn ensures that we don't
	 * attempt to set up a call to a signal handler (sendsig) before
	 * we have cleaned up the stack from the last call (sigreturn).
	 * Allowing this seems to lock up the machine in certain scenarios.
	 * What should really be done is to clean up the signal handling
	 * so that this is not a problem.
	 */
#include "syscall.h"
	if (code != SYS_sigreturn && (i = CURSIG(p)))
		psig(i,0);
E 12
I 12
	p = curproc;
	while (i = CURSIG(p))
D 30
		psig(i);
E 12
E 8
E 2
	p->p_pri = p->p_usrpri;
E 30
I 30
		postsig(i);
	p->p_priority = p->p_usrpri;
E 30
D 12
	if (runrun) {
E 12
I 12
	if (want_resched) {
I 16
		int pl;
I 29

E 29
E 16
E 12
		/*
D 14
		 * Since we are u.u_procp, clock will normally just change
E 14
I 14
		 * Since we are curproc, clock will normally just change
E 14
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 29
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 29
I 29
		 * If that happened after we put ourselves on the run queue
D 30
		 * but before we swtch()'ed, we might not be on the queue
E 30
I 30
		 * but before we switched, we might not be on the queue
E 30
		 * indicated by our priority.
E 29
		 */
D 16
		(void) splclock();
E 16
I 16
		pl = splclock();
E 16
D 29
		setrq(p);
E 29
I 29
		setrunqueue(p);
E 29
D 12
		u.u_ru.ru_nivcsw++;
E 12
I 12
		p->p_stats->p_ru.ru_nivcsw++;
E 12
D 30
		swtch();
E 30
I 30
		mi_switch();
E 30
I 16
		splx(pl);
E 16
I 4
D 8
		(void)spl0();
E 8
I 8
D 12
		if (code != SYS_sigreturn && (i = CURSIG(p)))
			psig(i,0);
E 12
I 12
		while (i = CURSIG(p))
D 30
			psig(i);
E 30
I 30
			postsig(i);
E 30
E 12
E 8
E 4
	}
D 12
	if (u.u_prof.pr_scale) {
E 12
I 12
	if (p->p_stats->p_prof.pr_scale) {
E 12
D 25
		int ticks;
D 12
		struct timeval *tv = &u.u_ru.ru_stime;
E 12
I 12
		struct timeval *tv = &p->p_stime;
E 25
I 25
		u_quad_t ticks = p->p_sticks - sticks;
E 25
E 12

D 25
		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
E 25
D 8
		if (ticks)
D 2
			addupc(locr0[PC], &u.u_prof, ticks);
E 2
I 2
			addupc(opc, &u.u_prof, ticks);
E 8
I 8
		if (ticks) {
#ifdef PROFTIMER
			extern int profscale;
D 12
			addupc(pc, &u.u_prof, ticks * profscale);
E 12
I 12
			addupc(frame.sf_eip, &p->p_stats->p_prof,
			    ticks * profscale);
E 12
#else
D 12
			addupc(pc, &u.u_prof, ticks);
E 12
I 12
			addupc(frame.sf_eip, &p->p_stats->p_prof, ticks);
E 12
#endif
		}
E 8
E 2
	}
D 28
	curpri = p->p_pri;
E 28
I 28
D 30
	curpriority = p->p_pri;
E 30
I 30
	curpriority = p->p_priority;
E 30
E 28
I 8
D 10
#ifdef KTRACE
E 10
I 10
D 12
#ifdef KTRACEx
E 12
I 12
#ifdef KTRACE
E 12
E 10
	if (KTRPOINT(p, KTR_SYSRET))
		ktrsysret(p->p_tracep, code, error, rval[0]);
#endif
I 23
}

int
user_page_fault (p, map, addr, ftype, type)
struct proc *p;
vm_map_t map;
caddr_t addr;
vm_prot_t ftype;
int type;
{
	struct vmspace *vm;
	vm_offset_t va;
	int rv;
	extern vm_map_t kernel_map;
	unsigned nss, v;

	vm = p->p_vmspace;

	va = trunc_page((vm_offset_t)addr);

	/*
	 * XXX: rude hack to make stack limits "work"
	 */
	nss = 0;
	if ((caddr_t)va >= vm->vm_maxsaddr && map != kernel_map) {
		nss = clrnd(btoc(USRSTACK - (unsigned)va));
		if (nss > btoc(p->p_rlimit[RLIMIT_STACK].rlim_cur))
			return (KERN_FAILURE);
	}

	/* check if page table is mapped, if not, fault it first */
#define pde_v(v) (PTD[((v)>>PD_SHIFT)&1023].pd_v)
	if (!pde_v(va)) {
		v = trunc_page(vtopte(va));
		if ((rv = vm_fault(map, v, ftype, FALSE)) != KERN_SUCCESS)
			return (rv);
		/* check if page table fault, increment wiring */
		vm_map_pageable(map, v, round_page(v+1), FALSE);
	} else
		v = 0;

	if ((rv = vm_fault(map, va, ftype, FALSE)) != KERN_SUCCESS)
		return (rv);

	/*
	 * XXX: continuation of rude stack hack
	 */
	if (nss > vm->vm_ssize)
		vm->vm_ssize = nss;
	va = trunc_page(vtopte(va));
	/*
	 * for page table, increment wiring
	 * as long as not a page table fault as well
	 */
	if (!v && type != T_PAGEFLT)
		vm_map_pageable(map, va, round_page(va+1), FALSE);
	return (KERN_SUCCESS);
}

int
user_write_fault (addr)
void *addr;
{
	if (user_page_fault (curproc, &curproc->p_vmspace->vm_map,
			     addr, VM_PROT_READ | VM_PROT_WRITE,
			     T_PAGEFLT) == KERN_SUCCESS)
		return (0);
	else
		return (EFAULT);
}

int
copyout (from, to, len)
void *from;
void *to;
u_int len;
{
	u_int *pte, *pde;
	int rest_of_page;
	int thistime;
	int err;

	/* be very careful not to overflow doing this check */
	if (to >= (void *)USRSTACK || (void *)USRSTACK - to < len)
		return (EFAULT);

	pte = (u_int *)vtopte (to);
	pde = (u_int *)vtopte (pte);

	rest_of_page = PAGE_SIZE - ((int)to & (PAGE_SIZE - 1));

	while (1) {
		thistime = len;
		if (thistime > rest_of_page)
			thistime = rest_of_page;

		if ((*pde & PG_V) == 0
		    || (*pte & (PG_V | PG_UW)) != (PG_V | PG_UW))
			if (err = user_write_fault (to))
				return (err);

		bcopy (from, to, thistime);

		len -= thistime;

		/*
		 * Break out as soon as possible in the common case
		 * that the whole transfer is containted in one page.
		 */
		if (len == 0)
			break;

		from += thistime;
		to += thistime;
		pte++;
		pde = (u_int *)vtopte (pte);
		rest_of_page = PAGE_SIZE;
	}

	return (0);
E 23
E 8
I 4
D 5
dprintf(DALLSYSC,"%d. rtn to %x %x\n",
	u.u_procp->p_pid, frame.sf_eip, frame.sf_cs);
#ifdef DEBUG
if(cpl) {
 printf("uSer cpl %x syscall %d\n", cpl, callp - sysent);
 spl0();
E 5
D 12
}
D 5
#endif
E 4
}
E 5

I 8
#ifdef notdef
E 8
/*
 * nonexistent system call-- signal process (may want to handle it)
 * flag error if process won't see signal immediately
 * Q: should we do that all the time ??
 */
nosys()
{

	if (u.u_signal[SIGSYS] == SIG_IGN || u.u_signal[SIGSYS] == SIG_HOLD)
		u.u_error = EINVAL;
	psignal(u.u_procp, SIGSYS);
}
I 8
#endif
E 8

D 3
#ifdef notdef
E 3
/*
 * Ignored system call
 */
nullsys()
{
I 8

E 12
E 8
D 5

E 5
}
D 3
#endif
E 3
E 1
