h30243
s 00042/00021/01733
d D 8.7 95/06/02 17:25:22 ralph 30 29
c final changes for pmax 4.4-Lite II release
e
s 00007/00000/01747
d D 8.6 94/07/03 14:50:57 mckusick 29 28
c minor debug checking code (from Ralph)
e
s 00021/00002/01726
d D 8.5 94/01/11 16:06:42 mckusick 28 27
c don't panic if corrected memory read error (from ralph)
e
s 00015/00015/01713
d D 8.4 93/09/23 16:38:31 bostic 27 26
c changes for 4.4BSD-Lite requested by USL
e
s 00008/00008/01720
d D 8.3 93/09/21 07:59:42 bostic 26 25
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/01726
d D 8.2 93/09/05 09:48:14 mckusick 25 24
c curpri => curpriority
e
s 00002/00002/01726
d D 8.1 93/07/13 17:42:09 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00012/01709
d D 7.21 93/07/13 17:41:35 mckusick 23 21
c additions to allow single stepping (from ralph)
e
s 00002/00002/01719
d R 8.1 93/06/16 16:44:59 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/01715
d D 7.20 93/06/16 16:44:34 mckusick 21 19
c indir => syscall; __indir => __syscall
e
s 00002/00002/01719
d R 8.1 93/06/10 23:07:58 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00002/01703
d D 7.19 93/05/31 17:57:15 ralph 19 18
c print a more useful memory error message for 5000/200
e
s 00002/00007/01703
d D 7.18 93/05/24 18:25:42 ralph 18 17
c remove debug stuff
e
s 00043/00056/01667
d D 7.17 93/05/09 17:42:16 ralph 17 16
c new improved pmap changes
e
s 00000/00072/01723
d D 7.16 93/04/05 21:38:54 ralph 16 15
c remove X kluge
e
s 00046/00028/01749
d D 7.15 93/03/23 18:55:44 ralph 15 14
c changes from Rick Macklem
e
s 00008/00006/01769
d D 7.14 93/03/08 18:54:47 ralph 14 13
c re-enable clock interrupts as soon as possible.
e
s 00189/00002/01586
d D 7.13 93/02/26 19:15:17 ralph 13 12
c added limited stacktrace for panics.
e
s 00114/00004/01474
d D 7.12 92/12/20 11:46:45 ralph 12 11
c changes from Rick Macklem
e
s 00370/00107/01108
d D 7.11 92/11/15 16:30:30 ralph 11 10
c updates from Rick Macklem for maxine.
e
s 00016/00024/01199
d D 7.10 92/10/24 14:14:45 ralph 10 9
c vm_flags changes, changed sigreturn code to be on user stack.
e
s 00020/00020/01203
d D 7.9 92/10/11 11:23:24 bostic 9 8
c make kernel includes standard
e
s 00059/00017/01164
d D 7.8 92/09/13 11:48:58 ralph 8 7
c fix __indir system call
e
s 00040/00035/01141
d D 7.7 92/07/27 21:22:18 ralph 7 6
c changes for profiling and bug fixes.
e
s 00022/00008/01154
d D 7.6 92/06/20 12:02:01 ralph 6 5
c fix 2 set associative pmap cache changes.
e
s 00003/00002/01159
d D 7.5 92/03/23 16:16:28 mckusick 5 4
c (code) to syscall() must be unsigned to catch negative numbers
e
s 00001/00001/01160
d D 7.4 92/03/20 13:55:42 bostic 4 3
c don't let negative system call codes in
e
s 00012/00010/01149
d D 7.3 92/02/29 17:53:00 ralph 3 2
c removed p_regs
e
s 00256/00145/00903
d D 7.2 92/02/29 14:09:37 ralph 2 1
c added support for DS5000
e
s 01048/00000/00000
d D 7.1 92/01/07 17:29:24 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 24
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: trap.c 1.32 91/04/06$
 *
 *	%W% (Berkeley) %G%
 */

D 9
#include "param.h"
#include "systm.h"
#include "proc.h"
#include "kernel.h"
#include "signalvar.h"
I 8
#include "syscall.h"
E 8
#include "user.h"
I 2
#include "buf.h"
E 9
I 9
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/signalvar.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <sys/buf.h>
E 9
E 2
#ifdef KTRACE
D 9
#include "ktrace.h"
E 9
I 9
#include <sys/ktrace.h>
E 9
#endif
D 9
#include "net/netisr.h"
E 9
I 9
#include <net/netisr.h>
E 9

D 9
#include "../include/trap.h"
#include "../include/psl.h"
#include "../include/reg.h"
#include "../include/cpu.h"
D 2
#include "pte.h"
E 2
I 2
#include "../include/pte.h"
#include "../include/mips_opcode.h"
E 2
#include "clockreg.h"
E 9
I 9
#include <machine/trap.h>
#include <machine/psl.h>
#include <machine/reg.h>
#include <machine/cpu.h>
#include <machine/pte.h>
#include <machine/mips_opcode.h>
D 11
#include <pmax/pmax/clockreg.h>
E 11
E 9

D 9
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
E 9
I 9
#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
E 9

I 11
#include <pmax/pmax/clockreg.h>
#include <pmax/pmax/kn01.h>
#include <pmax/pmax/kn02.h>
#include <pmax/pmax/kmin.h>
#include <pmax/pmax/maxine.h>
I 12
#include <pmax/pmax/kn03.h>
E 12
#include <pmax/pmax/asic.h>
#include <pmax/pmax/turbochannel.h>

I 15
#include <pmax/stand/dec_prom.h>

E 15
#include <asc.h>
#include <sii.h>
#include <le.h>
#include <dc.h>

E 11
D 16
/*
 * This is a kludge to allow X windows to work.
 */
#define X_KLUGE

#ifdef X_KLUGE
#define USER_MAP_ADDR	0x4000
D 15
#define NPTES 300
E 15
I 15
#define NPTES 550
E 15
static pt_entry_t UserMapPtes[NPTES];
static unsigned nUserMapPtes;
static pid_t UserMapPid;
#endif

E 16
struct	proc *machFPCurProcPtr;		/* pointer to last proc to use FP */

extern void MachKernGenException();
extern void MachUserGenException();
extern void MachKernIntr();
extern void MachUserIntr();
extern void MachTLBModException();
extern void MachTLBMissException();
D 7
extern void MemErrorInterrupt();
E 7
I 7
D 11
static void MemErrorInterrupt();
E 11
E 7
I 2
extern unsigned MachEmulateBranch();
E 2

void (*machExceptionTable[])() = {
/*
 * The kernel exception handlers.
 */
	MachKernIntr,			/* external interrupt */
	MachKernGenException,		/* TLB modification */
	MachTLBMissException,		/* TLB miss (load or instr. fetch) */
	MachTLBMissException,		/* TLB miss (store) */
	MachKernGenException,		/* address error (load or I-fetch) */
	MachKernGenException,		/* address error (store) */
	MachKernGenException,		/* bus error (I-fetch) */
	MachKernGenException,		/* bus error (load or store) */
	MachKernGenException,		/* system call */
	MachKernGenException,		/* breakpoint */
	MachKernGenException,		/* reserved instruction */
	MachKernGenException,		/* coprocessor unusable */
	MachKernGenException,		/* arithmetic overflow */
	MachKernGenException,		/* reserved */
	MachKernGenException,		/* reserved */
	MachKernGenException,		/* reserved */
/*
 * The user exception handlers.
 */
	MachUserIntr,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
	MachUserGenException,
};

char	*trap_type[] = {
	"external interrupt",
	"TLB modification",
	"TLB miss (load or instr. fetch)",
	"TLB miss (store)",
	"address error (load or I-fetch)",
	"address error (store)",
	"bus error (I-fetch)",
	"bus error (load or store)",
	"system call",
	"breakpoint",
	"reserved instruction",
	"coprocessor unusable",
	"arithmetic overflow",
	"reserved 13",
	"reserved 14",
	"reserved 15",
};

#ifdef DEBUG
#define TRAPSIZE	10
struct trapdebug {		/* trap history buffer for debugging */
	u_int	status;
	u_int	cause;
	u_int	vadr;
	u_int	pc;
	u_int	ra;
	u_int	code;
} trapdebug[TRAPSIZE], *trp = trapdebug;
I 29

u_int	intr_level;		/* number of nested interrupts */
E 29
#endif

I 11
static void pmax_errintr();
static void kn02_errintr(), kn02ba_errintr();
I 12
#ifdef DS5000_240
static void kn03_errintr();
#endif
E 12
static unsigned kn02ba_recover_erradr();
extern tc_option_t tc_slot_info[TC_MAX_LOGICAL_SLOTS];
extern u_long kmin_tc3_imask, xine_tc3_imask;
I 15
extern const struct callback *callv;
E 15
I 12
#ifdef DS5000_240
extern u_long kn03_tc3_imask;
#endif
E 12
int (*pmax_hardware_intr)() = (int (*)())0;
extern volatile struct chiptime *Mach_clock_addr;
I 30
extern long intrcnt[];
E 30

E 11
/*
 * Handle an exception.
 * Called from MachKernGenException() or MachUserGenException()
 * when a processor trap occurs.
 * In the case of a kernel trap, we return the pc where to resume if
 * ((struct pcb *)UADDR)->pcb_onfault is set, otherwise, return old pc.
 */
unsigned
D 2
trap(statusReg, causeReg, vadr, pc, args /* XXX */)
E 2
I 2
trap(statusReg, causeReg, vadr, pc, args)
E 2
	unsigned statusReg;	/* status register at time of the exception */
	unsigned causeReg;	/* cause register at time of exception */
	unsigned vadr;		/* address (if any) the fault occured on */
	unsigned pc;		/* program counter where to continue */
{
	register int type, i;
	unsigned ucode = 0;
	register struct proc *p = curproc;
D 7
	struct timeval syst;
E 7
I 7
	u_quad_t sticks;
E 7
	vm_prot_t ftype;
	extern unsigned onfault_table[];

#ifdef DEBUG
	trp->status = statusReg;
	trp->cause = causeReg;
	trp->vadr = vadr;
	trp->pc = pc;
D 3
	trp->ra = !USERMODE(statusReg) ? ((int *)&args)[19] : p->p_regs[RA];
E 3
I 3
	trp->ra = !USERMODE(statusReg) ? ((int *)&args)[19] :
		p->p_md.md_regs[RA];
E 3
	trp->code = 0;
	if (++trp == &trapdebug[TRAPSIZE])
		trp = trapdebug;
#endif

	cnt.v_trap++;
	type = (causeReg & MACH_CR_EXC_CODE) >> MACH_CR_EXC_CODE_SHIFT;
	if (USERMODE(statusReg)) {
		type |= T_USER;
D 7
		syst = p->p_stime;
E 7
I 7
		sticks = p->p_sticks;
E 7
	}

	/*
	 * Enable hardware interrupts if they were on before.
	 * We only respond to software interrupts when returning to user mode.
	 */
	if (statusReg & MACH_SR_INT_ENA_PREV)
		splx((statusReg & MACH_HARD_INT_MASK) | MACH_SR_INT_ENA_CUR);

	switch (type) {
	case T_TLB_MOD:
I 7
		/* check for kernel address */
E 7
		if ((int)vadr < 0) {
			register pt_entry_t *pte;
			register unsigned entry;
D 17
#ifndef ATTR
E 17
			register vm_offset_t pa;
D 17
#endif
E 17

			pte = kvtopte(vadr);
			entry = pte->pt_entry;
I 17
#ifdef DIAGNOSTIC
			if (!(entry & PG_V) || (entry & PG_M))
				panic("trap: ktlbmod: invalid pte");
#endif
E 17
			if (entry & PG_RO) {
				/* write to read only page in the kernel */
				ftype = VM_PROT_WRITE;
				goto kernel_fault;
			}
			entry |= PG_M;
			pte->pt_entry = entry;
D 17
			vadr &= PG_FRAME;
			printf("trap: TLBupdate hi %x lo %x i %x\n", vadr,
				entry, MachTLBUpdate(vadr, entry)); /* XXX */
E 17
I 17
			vadr &= ~PGOFSET;
D 18
			printf("trap: ktlbmod: TLBupdate hi %x lo %x i %x\n",
				vadr, entry,
				MachTLBUpdate(vadr, entry)); /* XXX */
E 18
I 18
			MachTLBUpdate(vadr, entry);
E 18
			pa = entry & PG_FRAME;
E 17
#ifdef ATTR
D 17
			pmap_attributes[atop(entry - KERNBASE)] |= PMAP_ATTR_MOD;
E 17
I 17
			pmap_attributes[atop(pa)] |= PMAP_ATTR_MOD;
E 17
#else
D 17
			pa = entry & PG_FRAME;
E 17
			if (!IS_VM_PHYSADDR(pa))
D 17
				panic("trap: kmod");
E 17
I 17
				panic("trap: ktlbmod: unmanaged page");
E 17
D 10
			PHYS_TO_VM_PAGE(pa)->clean = FALSE;
E 10
I 10
			PHYS_TO_VM_PAGE(pa)->flags &= ~PG_CLEAN;
E 10
#endif
			return (pc);
		}
		/* FALLTHROUGH */

	case T_TLB_MOD+T_USER:
	    {
D 17
		pmap_hash_t hp;
#ifndef ATTR
		vm_offset_t pa;
#endif
#ifdef DIAGNOSTIC
		extern pmap_hash_t zero_pmap_hash;
		extern pmap_t cur_pmap;
E 17
I 17
		register pt_entry_t *pte;
		register unsigned entry;
		register vm_offset_t pa;
		pmap_t pmap = &p->p_vmspace->vm_pmap;
E 17

D 10
		if (cur_pmap->pm_hash == zero_pmap_hash)
E 10
I 10
D 17
		if (cur_pmap->pm_hash == zero_pmap_hash ||
		    cur_pmap->pm_hash == (pmap_hash_t)0)
E 10
			panic("tlbmod");
E 17
I 17
		if (!(pte = pmap_segmap(pmap, vadr)))
			panic("trap: utlbmod: invalid segmap");
		pte += (vadr >> PGSHIFT) & (NPTEPG - 1);
		entry = pte->pt_entry;
#ifdef DIAGNOSTIC
		if (!(entry & PG_V) || (entry & PG_M))
			panic("trap: utlbmod: invalid pte");
E 17
#endif
D 17
		hp = &((pmap_hash_t)PMAP_HASH_UADDR)[PMAP_HASH(vadr)];
D 6
		if (hp->low & PG_RO) {
E 6
I 6
		if (((hp->pmh_pte[0].high ^ vadr) & ~PGOFSET) == 0)
			i = 0;
		else if (((hp->pmh_pte[1].high ^ vadr) & ~PGOFSET) == 0)
			i = 1;
		else
			panic("trap: tlb umod not found");
		if (hp->pmh_pte[i].low & PG_RO) {
E 17
I 17
		if (entry & PG_RO) {
			/* write to read only page */
E 17
E 6
			ftype = VM_PROT_WRITE;
			goto dofault;
		}
D 6
		hp->low |= PG_M;
		printf("trap: TLBupdate hi %x lo %x i %x\n", hp->high, hp->low,
			MachTLBUpdate(hp->high, hp->low)); /* XXX */
E 6
I 6
D 17
		hp->pmh_pte[i].low |= PG_M;
		printf("trap: TLBupdate hi %x lo %x i %x\n",
			hp->pmh_pte[i].high, hp->pmh_pte[i].low,
			MachTLBUpdate(hp->pmh_pte[i].high, hp->pmh_pte[i].low)); /* XXX */
E 17
I 17
		entry |= PG_M;
		pte->pt_entry = entry;
		vadr = (vadr & ~PGOFSET) |
			(pmap->pm_tlbpid << VMMACH_TLB_PID_SHIFT);
D 18
		printf("trap: utlbmod: TLBupdate hi %x lo %x i %x\n",
			vadr, entry, MachTLBUpdate(vadr, entry)); /* XXX */
E 18
I 18
		MachTLBUpdate(vadr, entry);
E 18
		pa = entry & PG_FRAME;
E 17
E 6
#ifdef ATTR
D 6
		pmap_attributes[atop(hp->low - KERNBASE)] |= PMAP_ATTR_MOD;
E 6
I 6
D 17
		pmap_attributes[atop(hp->pmh_pte[i].low - KERNBASE)] |=
			PMAP_ATTR_MOD;
E 17
I 17
		pmap_attributes[atop(pa)] |= PMAP_ATTR_MOD;
E 17
E 6
#else
D 6
		pa = hp->low & PG_FRAME;
E 6
I 6
D 17
		pa = hp->pmh_pte[i].low & PG_FRAME;
E 17
E 6
		if (!IS_VM_PHYSADDR(pa))
D 17
			panic("trap: umod");
E 17
I 17
			panic("trap: utlbmod: unmanaged page");
E 17
D 10
		PHYS_TO_VM_PAGE(pa)->clean = FALSE;
E 10
I 10
		PHYS_TO_VM_PAGE(pa)->flags &= ~PG_CLEAN;
E 10
#endif
		if (!USERMODE(statusReg))
			return (pc);
		goto out;
	    }

	case T_TLB_LD_MISS:
	case T_TLB_ST_MISS:
		ftype = (type == T_TLB_ST_MISS) ? VM_PROT_WRITE : VM_PROT_READ;
I 7
		/* check for kernel address */
E 7
		if ((int)vadr < 0) {
			register vm_offset_t va;
			int rv;

		kernel_fault:
			va = trunc_page((vm_offset_t)vadr);
			rv = vm_fault(kernel_map, va, ftype, FALSE);
			if (rv == KERN_SUCCESS)
				return (pc);
			if (i = ((struct pcb *)UADDR)->pcb_onfault) {
				((struct pcb *)UADDR)->pcb_onfault = 0;
				return (onfault_table[i]);
			}
			goto err;
		}
I 10
		/*
		 * It is an error for the kernel to access user space except
		 * through the copyin/copyout routines.
		 */
		if ((i = ((struct pcb *)UADDR)->pcb_onfault) == 0)
			goto err;
E 10
I 7
		/* check for fuswintr() or suswintr() getting a page fault */
D 10
		if ((i = ((struct pcb *)UADDR)->pcb_onfault) == 4)
E 10
I 10
		if (i == 4)
E 10
			return (onfault_table[i]);
E 7
		goto dofault;

	case T_TLB_LD_MISS+T_USER:
		ftype = VM_PROT_READ;
		goto dofault;

	case T_TLB_ST_MISS+T_USER:
		ftype = VM_PROT_WRITE;
	dofault:
	    {
		register vm_offset_t va;
D 17
		register struct vmspace *vm = p->p_vmspace;
		register vm_map_t map = &vm->vm_map;
E 17
I 17
		register struct vmspace *vm;
		register vm_map_t map;
E 17
		int rv;

I 17
		vm = p->p_vmspace;
		map = &vm->vm_map;
E 17
D 16
#ifdef X_KLUGE
		if (p->p_pid == UserMapPid &&
		    (va = pmax_btop(vadr - USER_MAP_ADDR)) < nUserMapPtes) {
			register pt_entry_t *pte;

			pte = &UserMapPtes[va];
			MachTLBWriteRandom((vadr & PG_FRAME) |
				(vm->vm_pmap.pm_tlbpid << VMMACH_TLB_PID_SHIFT),
				pte->pt_entry);
			return (pc);
		}
#endif
E 16
		va = trunc_page((vm_offset_t)vadr);
		rv = vm_fault(map, va, ftype, FALSE);
D 17
		if (rv != KERN_SUCCESS) {
			printf("vm_fault(%x, %x, %x, 0) -> %x ADR %x PC %x RA %x\n",
				map, va, ftype, rv, vadr, pc,
				!USERMODE(statusReg) ? ((int *)&args)[19] :
D 3
					p->p_regs[RA]); /* XXX */
E 3
I 3
					p->p_md.md_regs[RA]); /* XXX */
E 3
D 13
			printf("\tpid %d %s PC %x RA %x\n", p->p_pid,
E 13
I 13
			printf("\tpid %d %s PC %x RA %x SP %x\n", p->p_pid,
E 13
D 3
				p->p_comm, p->p_regs[PC], p->p_regs[RA]); /* XXX */
E 3
I 3
				p->p_comm, p->p_md.md_regs[PC],
D 13
				p->p_md.md_regs[RA]); /* XXX */
E 13
I 13
				p->p_md.md_regs[RA],
				p->p_md.md_regs[SP]); /* XXX */
E 13
E 3
D 14
			trapDump("vm_fault");
E 14
		}
E 17
		/*
		 * If this was a stack access we keep track of the maximum
		 * accessed stack size.  Also, if vm_fault gets a protection
		 * failure it is due to accessing the stack region outside
		 * the current limit and we need to reflect that as an access
		 * error.
		 */
		if ((caddr_t)va >= vm->vm_maxsaddr) {
			if (rv == KERN_SUCCESS) {
				unsigned nss;

				nss = clrnd(btoc(USRSTACK-(unsigned)va));
				if (nss > vm->vm_ssize)
					vm->vm_ssize = nss;
			} else if (rv == KERN_PROTECTION_FAILURE)
				rv = KERN_INVALID_ADDRESS;
		}
		if (rv == KERN_SUCCESS) {
			if (!USERMODE(statusReg))
				return (pc);
			goto out;
		}
		if (!USERMODE(statusReg)) {
			if (i = ((struct pcb *)UADDR)->pcb_onfault) {
				((struct pcb *)UADDR)->pcb_onfault = 0;
				return (onfault_table[i]);
			}
			goto err;
		}
		ucode = vadr;
		i = (rv == KERN_PROTECTION_FAILURE) ? SIGBUS : SIGSEGV;
		break;
	    }

	case T_ADDR_ERR_LD+T_USER:	/* misaligned or kseg access */
D 10
		if (vadr == KERNBASE) {
			struct args {
				int	i[1];
			} args;
			int rval[2];

			/*
			 * Assume a signal handler is trying to return
			 * (see sendsig() and sigreturn()). We have to
			 * pop the sigframe struct to get the address of
			 * the sigcontext.
			 */
D 3
			args.i[0] = p->p_regs[SP] + 4 * sizeof(int);
E 3
I 3
			args.i[0] = p->p_md.md_regs[SP] + 4 * sizeof(int);
E 3
			(void) sigreturn(curproc, &args, rval);
			goto out;
		}
		/* FALLTHROUGH */

E 10
	case T_ADDR_ERR_ST+T_USER:	/* misaligned or kseg access */
	case T_BUS_ERR_IFETCH+T_USER:	/* BERR asserted to cpu */
	case T_BUS_ERR_LD_ST+T_USER:	/* BERR asserted to cpu */
		i = SIGSEGV;
		break;

	case T_SYSCALL+T_USER:
	    {
D 3
		register int *locr0 = p->p_regs;
E 3
I 3
		register int *locr0 = p->p_md.md_regs;
E 3
		register struct sysent *callp;
D 5
		int code, numsys;
E 5
I 5
		unsigned int code;
		int numsys;
E 5
		struct args {
			int i[8];
		} args;
		int rval[2];
		struct sysent *systab;
D 2
		extern unsigned MachEmulateBranch();
E 2
		extern int nsysent;
#ifdef ULTRIXCOMPAT
		extern struct sysent ultrixsysent[];
		extern int ultrixnsysent;
#endif

		cnt.v_syscall++;
		/* compute next PC after syscall instruction */
		if ((int)causeReg < 0)
			locr0[PC] = MachEmulateBranch(locr0, pc, 0, 0);
		else
			locr0[PC] += 4;
		systab = sysent;
		numsys = nsysent;
#ifdef ULTRIXCOMPAT
		if (p->p_md.md_flags & MDP_ULTRIX) {
			systab = ultrixsysent;
			numsys = ultrixnsysent;
		}
#endif
		code = locr0[V0];
D 8
		if (code == 0) {			/* indir */
E 8
I 8
		switch (code) {
D 21
		case SYS_indir:
E 21
I 21
		case SYS_syscall:
E 21
			/*
			 * Code is first argument, followed by actual args.
			 */
E 8
			code = locr0[A0];
			if (code >= numsys)
D 8
				callp = &systab[0];	/* indir (illegal) */
E 8
I 8
D 21
				callp = &systab[SYS_indir]; /* (illegal) */
E 21
I 21
				callp = &systab[SYS_syscall]; /* (illegal) */
E 21
E 8
			else
				callp = &systab[code];
D 30
			i = callp->sy_narg;
E 30
I 30
			i = callp->sy_argsize;
E 30
			args.i[0] = locr0[A1];
			args.i[1] = locr0[A2];
			args.i[2] = locr0[A3];
D 30
			if (i > 3) {
E 30
I 30
			if (i > 3 * sizeof(register_t)) {
E 30
				i = copyin((caddr_t)(locr0[SP] +
D 8
						3 * sizeof(int)),
E 8
I 8
D 30
						4 * sizeof(int)),
E 30
I 30
						4 * sizeof(register_t)),
E 30
E 8
					(caddr_t)&args.i[3],
D 30
					(u_int)(i - 3) * sizeof(int));
E 30
I 30
					(u_int)(i - 3 * sizeof(register_t)));
E 30
				if (i) {
					locr0[V0] = i;
					locr0[A3] = 1;
#ifdef KTRACE
					if (KTRPOINT(p, KTR_SYSCALL))
						ktrsyscall(p->p_tracep, code,
D 30
							callp->sy_narg, args.i);
E 30
I 30
							callp->sy_argsize,
							args.i);
E 30
#endif
					goto done;
				}
			}
D 8
		} else {
E 8
I 8
			break;

D 21
		case SYS___indir:
E 21
I 21
		case SYS___syscall:
E 21
			/*
D 21
			 * Like indir, but code is a quad, so as to maintain
E 21
I 21
			 * Like syscall, but code is a quad, so as to maintain
E 21
			 * quad alignment for the rest of the arguments.
			 */
			code = locr0[A0 + _QUAD_LOWWORD];
E 8
D 4
			if (code >= numsys)
E 4
I 4
D 5
			if ((u_int)code >= numsys)
E 5
I 5
			if (code >= numsys)
E 5
E 4
D 8
				callp = &systab[0];	/* indir (illegal) */
E 8
I 8
D 21
				callp = &systab[SYS_indir]; /* (illegal) */
E 21
I 21
				callp = &systab[SYS_syscall]; /* (illegal) */
E 21
E 8
			else
				callp = &systab[code];
D 30
			i = callp->sy_narg;
E 30
I 30
			i = callp->sy_argsize;
E 30
I 8
			args.i[0] = locr0[A2];
			args.i[1] = locr0[A3];
D 30
			if (i > 2) {
E 30
I 30
			if (i > 2 * sizeof(register_t)) {
E 30
				i = copyin((caddr_t)(locr0[SP] +
D 30
						4 * sizeof(int)),
E 30
I 30
						4 * sizeof(register_t)),
E 30
					(caddr_t)&args.i[2],
D 30
					(u_int)(i - 2) * sizeof(int));
E 30
I 30
					(u_int)(i - 2 * sizeof(register_t)));
E 30
				if (i) {
					locr0[V0] = i;
					locr0[A3] = 1;
#ifdef KTRACE
					if (KTRPOINT(p, KTR_SYSCALL))
						ktrsyscall(p->p_tracep, code,
D 30
							callp->sy_narg, args.i);
E 30
I 30
							callp->sy_argsize,
							args.i);
E 30
#endif
					goto done;
				}
			}
			break;

		default:
			if (code >= numsys)
D 21
				callp = &systab[SYS_indir]; /* (illegal) */
E 21
I 21
				callp = &systab[SYS_syscall]; /* (illegal) */
E 21
			else
				callp = &systab[code];
D 30
			i = callp->sy_narg;
E 30
I 30
			i = callp->sy_argsize;
E 30
E 8
			args.i[0] = locr0[A0];
			args.i[1] = locr0[A1];
			args.i[2] = locr0[A2];
			args.i[3] = locr0[A3];
D 30
			if (i > 4) {
E 30
I 30
			if (i > 4 * sizeof(register_t)) {
E 30
				i = copyin((caddr_t)(locr0[SP] +
D 30
						4 * sizeof(int)),
E 30
I 30
						4 * sizeof(register_t)),
E 30
					(caddr_t)&args.i[4],
D 30
					(u_int)(i - 4) * sizeof(int));
E 30
I 30
					(u_int)(i - 4 * sizeof(register_t)));
E 30
				if (i) {
					locr0[V0] = i;
					locr0[A3] = 1;
#ifdef KTRACE
					if (KTRPOINT(p, KTR_SYSCALL))
						ktrsyscall(p->p_tracep, code,
D 30
							callp->sy_narg, args.i);
E 30
I 30
							callp->sy_argsize,
							args.i);
E 30
#endif
					goto done;
				}
			}
		}
#ifdef KTRACE
		if (KTRPOINT(p, KTR_SYSCALL))
D 30
			ktrsyscall(p->p_tracep, code, callp->sy_narg, args.i);
E 30
I 30
			ktrsyscall(p->p_tracep, code, callp->sy_argsize, args.i);
E 30
#endif
		rval[0] = 0;
		rval[1] = locr0[V1];
#ifdef DEBUG
		if (trp == trapdebug)
			trapdebug[TRAPSIZE - 1].code = code;
		else
			trp[-1].code = code;
#endif
		i = (*callp->sy_call)(p, &args, rval);
		/*
		 * Reinitialize proc pointer `p' as it may be different
		 * if this is a child returning from fork syscall.
		 */
		p = curproc;
D 3
		locr0 = p->p_regs;
E 3
I 3
		locr0 = p->p_md.md_regs;
E 3
#ifdef DEBUG
		{ int s;
		s = splhigh();
		trp->status = statusReg;
		trp->cause = causeReg;
		trp->vadr = locr0[SP];
		trp->pc = locr0[PC];
		trp->ra = locr0[RA];
		trp->code = -code;
		if (++trp == &trapdebug[TRAPSIZE])
			trp = trapdebug;
		splx(s);
		}
#endif
D 8
		if (i == ERESTART)
E 8
I 8
		switch (i) {
		case 0:
			locr0[V0] = rval[0];
			locr0[V1] = rval[1];
			locr0[A3] = 0;
			break;

		case ERESTART:
E 8
			locr0[PC] = pc;
D 8
		else if (i != EJUSTRETURN) {
			if (i) {
				locr0[V0] = i;
				locr0[A3] = 1;
			} else {
				locr0[V0] = rval[0];
				locr0[V1] = rval[1];
				locr0[A3] = 0;
			}
E 8
I 8
			break;

		case EJUSTRETURN:
			break;	/* nothing to do */

		default:
			locr0[V0] = i;
			locr0[A3] = 1;
E 8
		}
D 8
		/* else if (i == EJUSTRETURN) */
			/* nothing to do */
E 8
	done:
#ifdef KTRACE
		if (KTRPOINT(p, KTR_SYSRET))
			ktrsysret(p->p_tracep, code, i, rval[0]);
#endif
		goto out;
	    }

	case T_BREAK+T_USER:
D 2
		i = SIGTRAP;
		break;
E 2
I 2
	    {
		register unsigned va, instr;
E 2

I 2
		/* compute address of break instruction */
		va = pc;
		if ((int)causeReg < 0)
			va += 4;

		/* read break instruction */
D 6
		instr = fuiword(va);
E 6
I 6
		instr = fuiword((caddr_t)va);
I 23
#if 0
		printf("trap: %s (%d) breakpoint %x at %x: (adr %x ins %x)\n",
			p->p_comm, p->p_pid, instr, pc,
			p->p_md.md_ss_addr, p->p_md.md_ss_instr); /* XXX */
#endif
E 23
E 6
#ifdef KADB
		if (instr == MACH_BREAK_BRKPT || instr == MACH_BREAK_SSTEP)
			goto err;
#endif
		if (p->p_md.md_ss_addr != va || instr != MACH_BREAK_SSTEP) {
			i = SIGTRAP;
			break;
		}

		/* restore original instruction and clear BP  */
		i = suiword((caddr_t)va, p->p_md.md_ss_instr);
		if (i < 0) {
			vm_offset_t sa, ea;
			int rv;

			sa = trunc_page((vm_offset_t)va);
			ea = round_page((vm_offset_t)va+sizeof(int)-1);
			rv = vm_map_protect(&p->p_vmspace->vm_map, sa, ea,
				VM_PROT_DEFAULT, FALSE);
			if (rv == KERN_SUCCESS) {
				i = suiword((caddr_t)va, p->p_md.md_ss_instr);
				(void) vm_map_protect(&p->p_vmspace->vm_map,
					sa, ea, VM_PROT_READ|VM_PROT_EXECUTE,
					FALSE);
			}
		}
D 23
		if (i < 0) {
			i = SIGTRAP;
			break;
		}
E 23
I 23
		if (i < 0)
			printf("Warning: can't restore instruction at %x: %x\n",
				p->p_md.md_ss_addr, p->p_md.md_ss_instr);
E 23
		p->p_md.md_ss_addr = 0;
D 23
		goto out;
E 23
I 23
		i = SIGTRAP;
		break;
E 23
	    }

E 2
	case T_RES_INST+T_USER:
		i = SIGILL;
		break;

	case T_COP_UNUSABLE+T_USER:
		if ((causeReg & MACH_CR_COP_ERR) != 0x10000000) {
			i = SIGILL;	/* only FPU instructions allowed */
			break;
		}
D 3
		MachSwitchFPState(machFPCurProcPtr, p->p_regs);
E 3
I 3
		MachSwitchFPState(machFPCurProcPtr, p->p_md.md_regs);
E 3
		machFPCurProcPtr = p;
D 3
		p->p_regs[PS] |= MACH_SR_COP_1_BIT;
E 3
I 3
		p->p_md.md_regs[PS] |= MACH_SR_COP_1_BIT;
E 3
		p->p_md.md_flags |= MDP_FPUSED;
		goto out;

	case T_OVFLOW+T_USER:
		i = SIGFPE;
		break;

	case T_ADDR_ERR_LD:	/* misaligned access */
	case T_ADDR_ERR_ST:	/* misaligned access */
	case T_BUS_ERR_LD_ST:	/* BERR asserted to cpu */
		if (i = ((struct pcb *)UADDR)->pcb_onfault) {
			((struct pcb *)UADDR)->pcb_onfault = 0;
			return (onfault_table[i]);
		}
		/* FALLTHROUGH */

	default:
	err:
I 2
#ifdef KADB
	    {
		extern struct pcb kdbpcb;

		if (USERMODE(statusReg))
			kdbpcb = p->p_addr->u_pcb;
		else {
			kdbpcb.pcb_regs[ZERO] = 0;
			kdbpcb.pcb_regs[AST] = ((int *)&args)[2];
			kdbpcb.pcb_regs[V0] = ((int *)&args)[3];
			kdbpcb.pcb_regs[V1] = ((int *)&args)[4];
			kdbpcb.pcb_regs[A0] = ((int *)&args)[5];
			kdbpcb.pcb_regs[A1] = ((int *)&args)[6];
			kdbpcb.pcb_regs[A2] = ((int *)&args)[7];
			kdbpcb.pcb_regs[A3] = ((int *)&args)[8];
			kdbpcb.pcb_regs[T0] = ((int *)&args)[9];
			kdbpcb.pcb_regs[T1] = ((int *)&args)[10];
			kdbpcb.pcb_regs[T2] = ((int *)&args)[11];
			kdbpcb.pcb_regs[T3] = ((int *)&args)[12];
			kdbpcb.pcb_regs[T4] = ((int *)&args)[13];
			kdbpcb.pcb_regs[T5] = ((int *)&args)[14];
			kdbpcb.pcb_regs[T6] = ((int *)&args)[15];
			kdbpcb.pcb_regs[T7] = ((int *)&args)[16];
			kdbpcb.pcb_regs[T8] = ((int *)&args)[17];
			kdbpcb.pcb_regs[T9] = ((int *)&args)[18];
			kdbpcb.pcb_regs[RA] = ((int *)&args)[19];
			kdbpcb.pcb_regs[MULLO] = ((int *)&args)[21];
			kdbpcb.pcb_regs[MULHI] = ((int *)&args)[22];
			kdbpcb.pcb_regs[PC] = pc;
			kdbpcb.pcb_regs[SR] = statusReg;
			bzero((caddr_t)&kdbpcb.pcb_regs[F0], 33 * sizeof(int));
		}
		if (kdb(causeReg, vadr, p, !USERMODE(statusReg)))
			return (kdbpcb.pcb_regs[PC]);
	    }
I 6
#else
#ifdef DEBUG
		trapDump("trap");
E 6
#endif
I 6
#endif
E 6
E 2
		panic("trap");
	}
D 17
	printf("trap: pid %d %s sig %d adr %x pc %x ra %x\n", p->p_pid,
E 17
I 17
D 18
	printf("trap: pid %d '%s' sig %d adr %x pc %x ra %x\n", p->p_pid,
E 17
D 3
		p->p_comm, i, vadr, pc, p->p_regs[RA]); /* XXX */
E 3
I 3
		p->p_comm, i, vadr, pc, p->p_md.md_regs[RA]); /* XXX */
E 18
E 3
	trapsignal(p, i, ucode);
out:
	/*
	 * Note: we should only get here if returning to user mode.
	 */
D 7
	astpending = 0;
	while (i = CURSIG(p))
E 7
I 7
	/* take pending signals */
	while ((i = CURSIG(p)) != 0)
E 7
D 27
		psig(i);
	p->p_pri = p->p_usrpri;
E 27
I 27
		postsig(i);
	p->p_priority = p->p_usrpri;
E 27
I 7
	astpending = 0;
E 7
	if (want_resched) {
I 2
		int s;

E 2
		/*
		 * Since we are curproc, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 26
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 26
I 26
		 * If that happened after we put ourselves on the run queue
D 27
		 * but before we swtch()'ed, we might not be on the queue
E 27
I 27
		 * but before we switched, we might not be on the queue
E 27
		 * indicated by our priority.
E 26
		 */
D 2
		(void) splclock();
E 2
I 2
D 7
		s = splclock();
E 7
I 7
		s = splstatclock();
E 7
E 2
D 26
		setrq(p);
E 26
I 26
		setrunqueue(p);
E 26
		p->p_stats->p_ru.ru_nivcsw++;
D 27
		swtch();
E 27
I 27
		mi_switch();
E 27
I 2
		splx(s);
E 2
D 7
		while (i = CURSIG(p))
E 7
I 7
		while ((i = CURSIG(p)) != 0)
E 7
D 27
			psig(i);
E 27
I 27
			postsig(i);
E 27
	}
D 7
	if (p->p_stats->p_prof.pr_scale) {
		int ticks;
		struct timeval *tv = &p->p_stime;
E 7

D 7
		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks)
			addupc(pc, &p->p_stats->p_prof, ticks);
	}
E 7
I 7
	/*
	 * If profiling, charge system time to the trapped pc.
	 */
D 10
	if (p->p_flag & SPROFIL)
		addupc_task(p, pc, (int)(p->p_sticks - sticks));
E 10
I 10
D 27
	if (p->p_flag & SPROFIL) {
E 27
I 27
	if (p->p_flag & P_PROFIL) {
E 27
		extern int psratio;

		addupc_task(p, pc, (int)(p->p_sticks - sticks) * psratio);
	}
E 10

E 7
D 25
	curpri = p->p_pri;
E 25
I 25
D 27
	curpriority = p->p_pri;
E 27
I 27
	curpriority = p->p_priority;
E 27
E 25
	return (pc);
}

D 2
int temp; /*XXX*/
E 2
I 2
D 11
#ifdef DS5000
struct	intr_tab intr_tab[8];
#endif
E 2

I 2
D 7
int temp; /* XXX ULTRIX compiler bug with -O */
E 7
I 7
int	temp;		/* XXX ULTRIX compiler bug with -O */
E 7

E 11
E 2
/*
 * Handle an interrupt.
 * Called from MachKernIntr() or MachUserIntr()
 * Note: curproc might be NULL.
 */
interrupt(statusReg, causeReg, pc)
	unsigned statusReg;	/* status register at time of the exception */
	unsigned causeReg;	/* cause register at time of exception */
	unsigned pc;		/* program counter where to continue */
{
D 2
	register int i;
E 2
	register unsigned mask;
D 7
	clockframe cf;
E 7
I 7
	struct clockframe cf;
E 7

#ifdef DEBUG
	trp->status = statusReg;
	trp->cause = causeReg;
	trp->vadr = 0;
	trp->pc = pc;
	trp->ra = 0;
	trp->code = 0;
	if (++trp == &trapdebug[TRAPSIZE])
		trp = trapdebug;
I 29

	intr_level++;
E 29
#endif

	cnt.v_intr++;
	mask = causeReg & statusReg;	/* pending interrupts & enable mask */
I 2
D 11
#ifdef DS3100
E 11
I 11
	if (pmax_hardware_intr)
		splx((*pmax_hardware_intr)(mask, pc, statusReg, causeReg));
	if (mask & MACH_INT_MASK_5) {
I 30
		intrcnt[7]++;
E 30
		if (!USERMODE(statusReg)) {
#ifdef DEBUG
			trapDump("fpintr");
#else
			printf("FPU interrupt: PC %x CR %x SR %x\n",
				pc, causeReg, statusReg);
#endif
		} else
			MachFPInterrupt(statusReg, causeReg, pc);
	}
	if (mask & MACH_SOFT_INT_MASK_0) {
		clearsoftclock();
		cnt.v_soft++;
I 30
		intrcnt[0]++;
E 30
		softclock();
	}
	/* process network interrupt if we trapped or will very soon */
	if ((mask & MACH_SOFT_INT_MASK_1) ||
	    netisr && (statusReg & MACH_SOFT_INT_MASK_1)) {
		clearsoftnet();
		cnt.v_soft++;
I 30
		intrcnt[1]++;
E 30
#ifdef INET
		if (netisr & (1 << NETISR_ARP)) {
			netisr &= ~(1 << NETISR_ARP);
			arpintr();
		}
		if (netisr & (1 << NETISR_IP)) {
			netisr &= ~(1 << NETISR_IP);
			ipintr();
		}
#endif
#ifdef NS
		if (netisr & (1 << NETISR_NS)) {
			netisr &= ~(1 << NETISR_NS);
			nsintr();
		}
#endif
#ifdef ISO
		if (netisr & (1 << NETISR_ISO)) {
			netisr &= ~(1 << NETISR_ISO);
			clnlintr();
		}
#endif
	}
I 29
#ifdef DEBUG
	intr_level--;
#endif
E 29
}

/*
 * Handle pmax (DECstation 2100/3100) interrupts.
 */
pmax_intr(mask, pc, statusReg, causeReg)
	unsigned mask;
	unsigned pc;
	unsigned statusReg;
	unsigned causeReg;
{
	register volatile struct chiptime *c = Mach_clock_addr;
	struct clockframe cf;
	int temp;

E 11
	/* handle clock interrupts ASAP */
	if (mask & MACH_INT_MASK_3) {
I 30
		intrcnt[6]++;
E 30
D 11
		register volatile struct chiptime *c =
			(volatile struct chiptime *)MACH_CLOCK_ADDR;

E 11
D 7
		temp = c->regc;	/* clear interrupt bits */
E 7
I 7
		temp = c->regc;	/* XXX clear interrupt bits */
E 7
		cf.pc = pc;
D 7
		cf.ps = statusReg;
		hardclock(cf);
E 7
I 7
		cf.sr = statusReg;
		hardclock(&cf);
E 7
D 14
		causeReg &= ~MACH_INT_MASK_3;	/* reenable clock interrupts */
I 11
		splx(MACH_INT_MASK_3 | MACH_SR_INT_ENA_CUR);
E 14
I 14
		/* keep clock interrupts enabled */
		causeReg &= ~MACH_INT_MASK_3;
E 14
E 11
	}
I 14
	/* Re-enable clock interrupts */
	splx(MACH_INT_MASK_3 | MACH_SR_INT_ENA_CUR);
E 14
E 2
D 11
	/*
	 * Enable hardware interrupts which were enabled but not pending.
	 * We only respond to software interrupts when returning to spl0.
	 */
	splx((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
		MACH_SR_INT_ENA_CUR);
E 11
I 11
#if NSII > 0
E 11
D 2
	/*
	 * The first three tests should probably use
	 * some kind of table generated by 'config'.
	 */
E 2
D 30
	if (mask & MACH_INT_MASK_0)
E 30
I 30
	if (mask & MACH_INT_MASK_0) {
		intrcnt[2]++;
E 30
D 2
		siiintr();
E 2
I 2
		siiintr(0);
I 30
	}
E 30
I 11
#endif
#if NLE > 0
E 11
E 2
D 30
	if (mask & MACH_INT_MASK_1)
E 30
I 30
	if (mask & MACH_INT_MASK_1) {
		intrcnt[3]++;
E 30
D 2
		leintr();
E 2
I 2
		leintr(0);
I 30
	}
E 30
I 11
#endif
#if NDC > 0
E 11
E 2
D 30
	if (mask & MACH_INT_MASK_2)
E 30
I 30
	if (mask & MACH_INT_MASK_2) {
		intrcnt[4]++;
E 30
D 2
		dcintr();
	if (mask & MACH_INT_MASK_3) {
E 2
I 2
		dcintr(0);
I 30
	}
E 30
I 11
#endif
E 11
D 30
	if (mask & MACH_INT_MASK_4)
E 30
I 30
	if (mask & MACH_INT_MASK_4) {
		intrcnt[5]++;
E 30
D 11
		MemErrorInterrupt();
#endif /* DS3100 */
#ifdef DS5000
E 11
I 11
		pmax_errintr();
I 30
	}
E 30
	return ((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
		MACH_SR_INT_ENA_CUR);
}

/*
 * Handle hardware interrupts for the KN02. (DECstation 5000/200)
 * Returns spl value.
 */
kn02_intr(mask, pc, statusReg, causeReg)
	unsigned mask;
	unsigned pc;
	unsigned statusReg;
	unsigned causeReg;
{
	register unsigned i, m;
	register volatile struct chiptime *c = Mach_clock_addr;
	register unsigned csr;
	int temp;
	struct clockframe cf;
	static int warned = 0;

E 11
	/* handle clock interrupts ASAP */
	if (mask & MACH_INT_MASK_1) {
E 2
D 11
		register volatile struct chiptime *c =
			(volatile struct chiptime *)MACH_CLOCK_ADDR;
I 2
		register unsigned csr;
		static int warned = 0;
E 2

I 2
		csr = *(unsigned *)MACH_SYS_CSR_ADDR;
		if ((csr & MACH_CSR_PSWARN) && !warned) {
E 11
I 11
		csr = *(unsigned *)MACH_PHYS_TO_UNCACHED(KN02_SYS_CSR);
		if ((csr & KN02_CSR_PSWARN) && !warned) {
E 11
			warned = 1;
			printf("WARNING: power supply is overheating!\n");
D 11
		} else if (warned && !(csr & MACH_CSR_PSWARN)) {
E 11
I 11
		} else if (warned && !(csr & KN02_CSR_PSWARN)) {
E 11
			warned = 0;
			printf("WARNING: power supply is OK again\n");
		}
I 30
		intrcnt[6]++;
E 30

E 2
D 7
		temp = c->regc;	/* clear interrupt bits */
E 7
I 7
		temp = c->regc;	/* XXX clear interrupt bits */
E 7
		cf.pc = pc;
D 7
		cf.ps = statusReg;
		hardclock(cf);
E 7
I 7
		cf.sr = statusReg;
		hardclock(&cf);
E 7
I 2
D 11
		causeReg &= ~MACH_INT_MASK_1;	/* reenable clock interrupts */
E 11
I 11

D 14
		/* Re-enable clock interrupts */
E 14
I 14
		/* keep clock interrupts enabled */
E 14
		causeReg &= ~MACH_INT_MASK_1;
D 14
		splx(MACH_INT_MASK_1 | MACH_SR_INT_ENA_CUR);
E 14
E 11
E 2
	}
I 14
	/* Re-enable clock interrupts */
	splx(MACH_INT_MASK_1 | MACH_SR_INT_ENA_CUR);
E 14
D 2
	if (mask & MACH_INT_MASK_4)
E 2
I 2
	if (mask & MACH_INT_MASK_0) {
I 30
		static int map[8] = { 8, 8, 8, 8, 8, 4, 3, 2 };
E 30
D 11
		register unsigned csr;
		register unsigned i, m;
E 11

D 11
		csr = *(unsigned *)MACH_SYS_CSR_ADDR;
		m = csr & (csr >> MACH_CSR_IOINTEN_SHIFT) & MACH_CSR_IOINT_MASK;
E 11
I 11
		csr = *(unsigned *)MACH_PHYS_TO_UNCACHED(KN02_SYS_CSR);
		m = csr & (csr >> KN02_CSR_IOINTEN_SHIFT) & KN02_CSR_IOINT;
E 11
#if 0
D 11
		*(unsigned *)MACH_SYS_CSR_ADDR =
			(csr & ~(MACH_CSR_MBZ | 0xFF)) |
			(m << MACH_CSR_IOINTEN_SHIFT);
E 11
I 11
		*(unsigned *)MACHPHYS_TO_UNCACHED(KN02_SYS_CSR) =
			(csr & ~(KN02_CSR_WRESERVED | 0xFF)) |
			(m << KN02_CSR_IOINTEN_SHIFT);
E 11
#endif
D 11
		/*
		 * Enable hardware interrupts which were enabled but not
		 * pending. We only respond to software interrupts when
		 * returning to spl0.
		 */
		splx((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
			MACH_SR_INT_ENA_CUR);
E 11
		for (i = 0; m; i++, m >>= 1) {
			if (!(m & 1))
				continue;
I 30
			intrcnt[map[i]]++;
E 30
D 11
			if (intr_tab[i].func)
				(*intr_tab[i].func)(intr_tab[i].unit);
E 11
I 11
			if (tc_slot_info[i].intr)
				(*tc_slot_info[i].intr)(tc_slot_info[i].unit);
E 11
			else
				printf("spurious interrupt %d\n", i);
		}
#if 0
D 11
		*(unsigned *)MACH_SYS_CSR_ADDR =
			csr & ~(MACH_CSR_MBZ | 0xFF);
E 11
I 11
		*(unsigned *)MACH_PHYS_TO_UNCACHED(KN02_SYS_CSR) =
			csr & ~(KN02_CSR_WRESERVED | 0xFF);
E 11
#endif
D 11
	} else {
		/*
		 * Enable hardware interrupts which were enabled but not
		 * pending. We only respond to software interrupts when
		 * returning to spl0.
		 */
		splx((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
			MACH_SR_INT_ENA_CUR);
E 11
	}
D 30
	if (mask & MACH_INT_MASK_3)
E 30
I 30
	if (mask & MACH_INT_MASK_3) {
		intrcnt[5]++;
E 30
E 2
D 11
		MemErrorInterrupt();
I 2
#endif /* DS5000 */
E 2
	if (mask & MACH_INT_MASK_5) {
D 2
		printf("FPU interrupt: PC %x CR %x SR %x\n",
			pc, causeReg, statusReg); /* XXX */
E 2
		if (!USERMODE(statusReg)) {
#ifdef DEBUG
			trapDump("fpintr");
#else
			printf("FPU interrupt: PC %x CR %x SR %x\n",
				pc, causeReg, statusReg);
E 11
I 11
		kn02_errintr();
I 30
	}
E 30
	return ((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
		MACH_SR_INT_ENA_CUR);
}

/*
 * 3min hardware interrupts. (DECstation 5000/1xx)
 */
kmin_intr(mask, pc, statusReg, causeReg)
	unsigned mask;
	unsigned pc;
	unsigned statusReg;
	unsigned causeReg;
{
	register u_int intr;
	register volatile struct chiptime *c = Mach_clock_addr;
	volatile u_int *imaskp =
		(volatile u_int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_IMSK);
	volatile u_int *intrp =
		(volatile u_int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_INTR);
	unsigned int old_mask;
	struct clockframe cf;
	int temp;
	static int user_warned = 0;

	old_mask = *imaskp & kmin_tc3_imask;
	*imaskp = old_mask;

I 15
	if (mask & MACH_INT_MASK_4)
		(*callv->halt)((int *)0, 0);
E 15
	if (mask & MACH_INT_MASK_3) {
		intr = *intrp;
		/* masked interrupts are still observable */
		intr &= old_mask;
	
		if (intr & KMIN_INTR_SCSI_PTR_LOAD) {
			*intrp &= ~KMIN_INTR_SCSI_PTR_LOAD;
D 12
#if NASC > 0
E 12
I 12
#ifdef notdef
E 12
			asc_dma_intr();
E 11
#endif
D 11
		} else
			MachFPInterrupt(statusReg, causeReg, pc);
	}
	if (mask & MACH_SOFT_INT_MASK_0) {
D 7
		clockframe cf;

E 7
		clearsoftclock();
I 6
		cnt.v_soft++;
E 6
D 7
		cf.pc = pc;
		cf.ps = statusReg;
		softclock(cf);
E 7
I 7
		softclock();
E 7
	}
	/* process network interrupt if we trapped or will very soon */
	if ((mask & MACH_SOFT_INT_MASK_1) ||
	    netisr && (statusReg & MACH_SOFT_INT_MASK_1)) {
		clearsoftnet();
I 6
		cnt.v_soft++;
E 6
#ifdef INET
		if (netisr & (1 << NETISR_ARP)) {
			netisr &= ~(1 << NETISR_ARP);
			arpintr();
E 11
		}
D 11
		if (netisr & (1 << NETISR_IP)) {
			netisr &= ~(1 << NETISR_IP);
			ipintr();
E 11
I 11
	
		if (intr & (KMIN_INTR_SCSI_OVRUN | KMIN_INTR_SCSI_READ_E))
			*intrp &= ~(KMIN_INTR_SCSI_OVRUN | KMIN_INTR_SCSI_READ_E);

		if (intr & KMIN_INTR_LANCE_READ_E)
			*intrp &= ~KMIN_INTR_LANCE_READ_E;

		if (intr & KMIN_INTR_TIMEOUT)
			kn02ba_errintr();
	
		if (intr & KMIN_INTR_CLOCK) {
			temp = c->regc;	/* XXX clear interrupt bits */
			cf.pc = pc;
			cf.sr = statusReg;
			hardclock(&cf);
E 11
		}
D 11
#endif
#ifdef NS
		if (netisr & (1 << NETISR_NS)) {
			netisr &= ~(1 << NETISR_NS);
			nsintr();
E 11
I 11
	
		if ((intr & KMIN_INTR_SCC_0) &&
			tc_slot_info[KMIN_SCC0_SLOT].intr)
			(*(tc_slot_info[KMIN_SCC0_SLOT].intr))
			(tc_slot_info[KMIN_SCC0_SLOT].unit);
	
		if ((intr & KMIN_INTR_SCC_1) &&
			tc_slot_info[KMIN_SCC1_SLOT].intr)
			(*(tc_slot_info[KMIN_SCC1_SLOT].intr))
			(tc_slot_info[KMIN_SCC1_SLOT].unit);
	
		if ((intr & KMIN_INTR_SCSI) &&
			tc_slot_info[KMIN_SCSI_SLOT].intr)
			(*(tc_slot_info[KMIN_SCSI_SLOT].intr))
			(tc_slot_info[KMIN_SCSI_SLOT].unit);
	
		if ((intr & KMIN_INTR_LANCE) &&
			tc_slot_info[KMIN_LANCE_SLOT].intr)
			(*(tc_slot_info[KMIN_LANCE_SLOT].intr))
			(tc_slot_info[KMIN_LANCE_SLOT].unit);
	
		if (user_warned && ((intr & KMIN_INTR_PSWARN) == 0)) {
D 15
			*imaskp = 0;
E 15
			printf("%s\n", "Power supply ok now.");
			user_warned = 0;
E 11
		}
D 11
#endif
#ifdef ISO
		if (netisr & (1 << NETISR_ISO)) {
			netisr &= ~(1 << NETISR_ISO);
			clnlintr();
E 11
I 11
		if ((intr & KMIN_INTR_PSWARN) && (user_warned < 3)) {
D 15
			*imaskp = 0;
E 15
			user_warned++;
			printf("%s\n", "Power supply overheating");
E 11
		}
I 11
	}
	if ((mask & MACH_INT_MASK_0) && tc_slot_info[0].intr)
		(*tc_slot_info[0].intr)(tc_slot_info[0].unit);
	if ((mask & MACH_INT_MASK_1) && tc_slot_info[1].intr)
		(*tc_slot_info[1].intr)(tc_slot_info[1].unit);
	if ((mask & MACH_INT_MASK_2) && tc_slot_info[2].intr)
		(*tc_slot_info[2].intr)(tc_slot_info[2].unit);
	return ((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
		MACH_SR_INT_ENA_CUR);
}

/*
D 14
 * Maxine hardwark interrupts. (Personal DECstation 5000/xx)
E 14
I 14
 * Maxine hardware interrupts. (Personal DECstation 5000/xx)
E 14
 */
xine_intr(mask, pc, statusReg, causeReg)
	unsigned mask;
	unsigned pc;
	unsigned statusReg;
	unsigned causeReg;
{
	register u_int intr;
	register volatile struct chiptime *c = Mach_clock_addr;
	volatile u_int *imaskp = (volatile u_int *)
		MACH_PHYS_TO_UNCACHED(XINE_REG_IMSK);
	volatile u_int *intrp = (volatile u_int *)
		MACH_PHYS_TO_UNCACHED(XINE_REG_INTR);
	u_int old_mask;
	struct clockframe cf;
	int temp;
D 12
static int clkticks = 0;
E 12

	old_mask = *imaskp & xine_tc3_imask;
	*imaskp = old_mask;

I 15
	if (mask & MACH_INT_MASK_4)
		(*callv->halt)((int *)0, 0);

E 15
	/* handle clock interrupts ASAP */
	if (mask & MACH_INT_MASK_1) {
		temp = c->regc;	/* XXX clear interrupt bits */
		cf.pc = pc;
		cf.sr = statusReg;
		hardclock(&cf);
D 12
if ((++clkticks % 10000) == 0) printf("TICKKEYY TICKEY!\n");
E 12
		causeReg &= ~MACH_INT_MASK_1;
		/* reenable clock interrupts */
		splx(MACH_INT_MASK_1 | MACH_SR_INT_ENA_CUR);
	}
	if (mask & MACH_INT_MASK_3) {
		intr = *intrp;
		/* masked interrupts are still observable */
		intr &= old_mask;

		if (intr & XINE_INTR_SCSI_PTR_LOAD) {
			*intrp &= ~XINE_INTR_SCSI_PTR_LOAD;
D 12
#if NASC > 0
E 12
I 12
#ifdef notdef
E 12
			asc_dma_intr();
E 11
#endif
I 11
		}
	
		if (intr & (XINE_INTR_SCSI_OVRUN | XINE_INTR_SCSI_READ_E))
			*intrp &= ~(XINE_INTR_SCSI_OVRUN | XINE_INTR_SCSI_READ_E);

		if (intr & XINE_INTR_LANCE_READ_E)
			*intrp &= ~XINE_INTR_LANCE_READ_E;

I 15
		if ((intr & XINE_INTR_SCC_0) &&
			tc_slot_info[XINE_SCC0_SLOT].intr)
			(*(tc_slot_info[XINE_SCC0_SLOT].intr))
			(tc_slot_info[XINE_SCC0_SLOT].unit);
	
		if ((intr & XINE_INTR_DTOP_RX) &&
			tc_slot_info[XINE_DTOP_SLOT].intr)
			(*(tc_slot_info[XINE_DTOP_SLOT].intr))
			(tc_slot_info[XINE_DTOP_SLOT].unit);
	
E 15
		if ((intr & XINE_INTR_FLOPPY) &&
			tc_slot_info[XINE_FLOPPY_SLOT].intr)
			(*(tc_slot_info[XINE_FLOPPY_SLOT].intr))
			(tc_slot_info[XINE_FLOPPY_SLOT].unit);
	
		if ((intr & XINE_INTR_TC_0) &&
			tc_slot_info[0].intr)
			(*(tc_slot_info[0].intr))
			(tc_slot_info[0].unit);
	
I 15
		if ((intr & XINE_INTR_TC_1) &&
			tc_slot_info[1].intr)
			(*(tc_slot_info[1].intr))
			(tc_slot_info[1].unit);
	
E 15
		if ((intr & XINE_INTR_ISDN) &&
			tc_slot_info[XINE_ISDN_SLOT].intr)
			(*(tc_slot_info[XINE_ISDN_SLOT].intr))
			(tc_slot_info[XINE_ISDN_SLOT].unit);
	
		if ((intr & XINE_INTR_SCSI) &&
			tc_slot_info[XINE_SCSI_SLOT].intr)
			(*(tc_slot_info[XINE_SCSI_SLOT].intr))
			(tc_slot_info[XINE_SCSI_SLOT].unit);
	
		if ((intr & XINE_INTR_LANCE) &&
			tc_slot_info[XINE_LANCE_SLOT].intr)
			(*(tc_slot_info[XINE_LANCE_SLOT].intr))
			(tc_slot_info[XINE_LANCE_SLOT].unit);
	
D 15
		if ((intr & XINE_INTR_SCC_0) &&
			tc_slot_info[XINE_SCC0_SLOT].intr)
			(*(tc_slot_info[XINE_SCC0_SLOT].intr))
			(tc_slot_info[XINE_SCC0_SLOT].unit);
	
		if ((intr & XINE_INTR_TC_1) &&
			tc_slot_info[1].intr)
			(*(tc_slot_info[1].intr))
			(tc_slot_info[1].unit);
	
		if ((intr & XINE_INTR_DTOP_RX) &&
			tc_slot_info[XINE_DTOP_SLOT].intr)
			(*(tc_slot_info[XINE_DTOP_SLOT].intr))
			(tc_slot_info[XINE_DTOP_SLOT].unit);
	
E 15
E 11
	}
I 11
	if (mask & MACH_INT_MASK_2)
		kn02ba_errintr();
	return ((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
		MACH_SR_INT_ENA_CUR);
E 11
}

I 12
#ifdef DS5000_240
E 12
/*
I 12
 * 3Max+ hardware interrupts. (DECstation 5000/240) UNTESTED!!
 */
kn03_intr(mask, pc, statusReg, causeReg)
	unsigned mask;
	unsigned pc;
	unsigned statusReg;
	unsigned causeReg;
{
	register u_int intr;
	register volatile struct chiptime *c = Mach_clock_addr;
	volatile u_int *imaskp = (volatile u_int *)
		MACH_PHYS_TO_UNCACHED(KN03_REG_IMSK);
	volatile u_int *intrp = (volatile u_int *)
		MACH_PHYS_TO_UNCACHED(KN03_REG_INTR);
	u_int old_mask;
	struct clockframe cf;
	int temp;
I 15
	static int user_warned = 0;
E 15

	old_mask = *imaskp & kn03_tc3_imask;
	*imaskp = old_mask;

I 15
	if (mask & MACH_INT_MASK_4)
		(*callv->halt)((int *)0, 0);

E 15
	/* handle clock interrupts ASAP */
	if (mask & MACH_INT_MASK_1) {
		temp = c->regc;	/* XXX clear interrupt bits */
		cf.pc = pc;
		cf.sr = statusReg;
		hardclock(&cf);
		causeReg &= ~MACH_INT_MASK_1;
		/* reenable clock interrupts */
		splx(MACH_INT_MASK_1 | MACH_SR_INT_ENA_CUR);
	}
	if (mask & MACH_INT_MASK_0) {
		intr = *intrp;
		/* masked interrupts are still observable */
		intr &= old_mask;

		if (intr & KN03_INTR_SCSI_PTR_LOAD) {
			*intrp &= ~KN03_INTR_SCSI_PTR_LOAD;
#ifdef notdef
			asc_dma_intr();
#endif
		}
	
		if (intr & (KN03_INTR_SCSI_OVRUN | KN03_INTR_SCSI_READ_E))
			*intrp &= ~(KN03_INTR_SCSI_OVRUN | KN03_INTR_SCSI_READ_E);

		if (intr & KN03_INTR_LANCE_READ_E)
			*intrp &= ~KN03_INTR_LANCE_READ_E;

I 15
		if ((intr & KN03_INTR_SCC_0) &&
			tc_slot_info[KN03_SCC0_SLOT].intr)
			(*(tc_slot_info[KN03_SCC0_SLOT].intr))
			(tc_slot_info[KN03_SCC0_SLOT].unit);
	
		if ((intr & KN03_INTR_SCC_1) &&
			tc_slot_info[KN03_SCC1_SLOT].intr)
			(*(tc_slot_info[KN03_SCC1_SLOT].intr))
			(tc_slot_info[KN03_SCC1_SLOT].unit);
	
E 15
		if ((intr & KN03_INTR_TC_0) &&
			tc_slot_info[0].intr)
			(*(tc_slot_info[0].intr))
			(tc_slot_info[0].unit);
	
		if ((intr & KN03_INTR_TC_1) &&
			tc_slot_info[1].intr)
			(*(tc_slot_info[1].intr))
			(tc_slot_info[1].unit);
	
		if ((intr & KN03_INTR_TC_2) &&
			tc_slot_info[2].intr)
			(*(tc_slot_info[2].intr))
			(tc_slot_info[2].unit);
	
		if ((intr & KN03_INTR_SCSI) &&
			tc_slot_info[KN03_SCSI_SLOT].intr)
			(*(tc_slot_info[KN03_SCSI_SLOT].intr))
			(tc_slot_info[KN03_SCSI_SLOT].unit);
	
		if ((intr & KN03_INTR_LANCE) &&
			tc_slot_info[KN03_LANCE_SLOT].intr)
			(*(tc_slot_info[KN03_LANCE_SLOT].intr))
			(tc_slot_info[KN03_LANCE_SLOT].unit);
	
D 15
		if ((intr & KN03_INTR_SCC_0) &&
			tc_slot_info[KN03_SCC0_SLOT].intr)
			(*(tc_slot_info[KN03_SCC0_SLOT].intr))
			(tc_slot_info[KN03_SCC0_SLOT].unit);
	
		if ((intr & KN03_INTR_SCC_1) &&
			tc_slot_info[KN03_SCC1_SLOT].intr)
			(*(tc_slot_info[KN03_SCC1_SLOT].intr))
			(tc_slot_info[KN03_SCC1_SLOT].unit);
	
E 15
I 15
		if (user_warned && ((intr & KN03_INTR_PSWARN) == 0)) {
			printf("%s\n", "Power supply ok now.");
			user_warned = 0;
		}
		if ((intr & KN03_INTR_PSWARN) && (user_warned < 3)) {
			user_warned++;
			printf("%s\n", "Power supply overheating");
		}
E 15
	}
	if (mask & MACH_INT_MASK_3)
		kn03_errintr();
	return ((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
		MACH_SR_INT_ENA_CUR);
}
#endif /* DS5000_240 */

/*
E 12
 * This is called from MachUserIntr() if astpending is set.
 * This is very similar to the tail of trap().
 */
softintr(statusReg, pc)
	unsigned statusReg;	/* status register at time of the exception */
	unsigned pc;		/* program counter where to continue */
{
	register struct proc *p = curproc;
D 7
	register int i;
E 7
I 7
	int sig;
E 7

	cnt.v_soft++;
D 7
	astpending = 0;
	while (i = CURSIG(p))
		psig(i);
E 7
I 7
	/* take pending signals */
	while ((sig = CURSIG(p)) != 0)
D 27
		psig(sig);
E 7
	p->p_pri = p->p_usrpri;
E 27
I 27
		postsig(sig);
	p->p_priority = p->p_usrpri;
E 27
I 7
	astpending = 0;
D 27
	if (p->p_flag & SOWEUPC) {
		p->p_flag &= ~SOWEUPC;
E 27
I 27
	if (p->p_flag & P_OWEUPC) {
		p->p_flag &= ~P_OWEUPC;
E 27
		ADDUPROF(p);
	}
E 7
	if (want_resched) {
I 2
		int s;

E 2
		/*
		 * Since we are curproc, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 26
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 26
I 26
		 * If that happened after we put ourselves on the run queue
D 27
		 * but before we swtch()'ed, we might not be on the queue
E 27
I 27
		 * but before we switched, we might not be on the queue
E 27
		 * indicated by our priority.
E 26
		 */
D 2
		(void) splclock();
E 2
I 2
D 7
		s = splclock();
E 7
I 7
		s = splstatclock();
E 7
E 2
D 26
		setrq(p);
E 26
I 26
		setrunqueue(p);
E 26
		p->p_stats->p_ru.ru_nivcsw++;
D 27
		swtch();
E 27
I 27
		mi_switch();
E 27
I 2
		splx(s);
E 2
D 7
		while (i = CURSIG(p))
			psig(i);
E 7
I 7
		while ((sig = CURSIG(p)) != 0)
D 27
			psig(sig);
E 27
I 27
			postsig(sig);
E 27
E 7
	}
D 25
	curpri = p->p_pri;
E 25
I 25
D 27
	curpriority = p->p_pri;
E 27
I 27
	curpriority = p->p_priority;
E 27
E 25
}

#ifdef DEBUG
trapDump(msg)
	char *msg;
{
	register int i;
	int s;

	s = splhigh();
	printf("trapDump(%s)\n", msg);
	for (i = 0; i < TRAPSIZE; i++) {
		if (trp == trapdebug)
			trp = &trapdebug[TRAPSIZE - 1];
		else
			trp--;
		if (trp->cause == 0)
			break;
		printf("%s: ADR %x PC %x CR %x SR %x\n",
			trap_type[(trp->cause & MACH_CR_EXC_CODE) >>
				MACH_CR_EXC_CODE_SHIFT],
			trp->vadr, trp->pc, trp->cause, trp->status);
		printf("   RA %x code %d\n", trp-> ra, trp->code);
	}
	bzero(trapdebug, sizeof(trapdebug));
	trp = trapdebug;
	splx(s);
D 16
}
#endif

#ifdef X_KLUGE
/*
 * This is a kludge to allow X windows to work.
 */
caddr_t
vmUserMap(size, pa)
	int size;
	unsigned pa;
{
	register caddr_t v;
	unsigned off, entry;

	if (nUserMapPtes == 0)
		UserMapPid = curproc->p_pid;
	else if (UserMapPid != curproc->p_pid)
		return ((caddr_t)0);
	off = pa & PGOFSET;
	size = btoc(off + size);
	if (nUserMapPtes + size > NPTES)
		return ((caddr_t)0);
	v = (caddr_t)(USER_MAP_ADDR + pmax_ptob(nUserMapPtes) + off);
	entry = (pa & 0x9ffff000) | PG_V | PG_M;
	if (pa >= MACH_UNCACHED_MEMORY_ADDR)
		entry |= PG_N;
	while (size > 0) {
		UserMapPtes[nUserMapPtes].pt_entry = entry;
		entry += NBPG;
		nUserMapPtes++;
		size--;
	}
	return (v);
}

vmUserUnmap()
{
	int id;

	nUserMapPtes = 0;
	if (UserMapPid == curproc->p_pid) {
		id = curproc->p_vmspace->vm_pmap.pm_tlbpid;
		if (id >= 0)
			MachTLBFlushPID(id);
	}
	UserMapPid = 0;
E 16
}
#endif

/*
 *----------------------------------------------------------------------
 *
D 11
 * MemErrorInterrupt --
E 11
I 11
 * MemErrorInterrupts --
 *   pmax_errintr - for the DS2100/DS3100
 *   kn02_errintr - for the DS5000/200
 *   kn02ba_errintr - for the DS5000/1xx and DS5000/xx
E 11
 *
 *	Handler an interrupt for the control register.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */
static void
D 11
MemErrorInterrupt()
E 11
I 11
pmax_errintr()
E 11
{
I 2
D 11
#ifdef DS3100
E 2
	volatile u_short *sysCSRPtr = (u_short *)MACH_SYS_CSR_ADDR;
E 11
I 11
	volatile u_short *sysCSRPtr =
		(u_short *)MACH_PHYS_TO_UNCACHED(KN01_SYS_CSR);
E 11
	u_short csr;

	csr = *sysCSRPtr;

D 11
	if (csr & MACH_CSR_MEM_ERR) {
E 11
I 11
	if (csr & KN01_CSR_MERR) {
E 11
		printf("Memory error at 0x%x\n",
D 11
			*(unsigned *)MACH_WRITE_ERROR_ADDR);
E 11
I 11
			*(unsigned *)MACH_PHYS_TO_UNCACHED(KN01_SYS_ERRADR));
E 11
		panic("Mem error interrupt");
	}
D 11
	*sysCSRPtr = (csr & ~MACH_CSR_MBZ) | 0xff;
I 2
#endif /* DS3100 */
#ifdef DS5000
	printf("erradr %x\n", *(unsigned *)MACH_ERROR_ADDR);
	*(unsigned *)MACH_ERROR_ADDR = 0;
E 11
I 11
	*sysCSRPtr = (csr & ~KN01_CSR_MBZ) | 0xff;
}

static void
kn02_errintr()
{
I 19
D 28
	u_int erradr, chksyn;
E 28
I 28
	u_int erradr, chksyn, physadr;
	int i;
E 28
E 19

D 19
	printf("erradr %x\n", *(unsigned *)MACH_PHYS_TO_UNCACHED(KN02_SYS_ERRADR));
	*(unsigned *)MACH_PHYS_TO_UNCACHED(KN02_SYS_ERRADR) = 0;
E 19
I 19
	erradr = *(u_int *)MACH_PHYS_TO_UNCACHED(KN02_SYS_ERRADR);
	chksyn = *(u_int *)MACH_PHYS_TO_UNCACHED(KN02_SYS_CHKSYN);
	*(u_int *)MACH_PHYS_TO_UNCACHED(KN02_SYS_ERRADR) = 0;
E 19
E 11
	MachEmptyWriteBuffer();
I 19

	if (!(erradr & KN02_ERR_VALID))
		return;
I 28
	/* extract the physical word address and compensate for pipelining */
	physadr = erradr & KN02_ERR_ADDRESS;
	if (!(erradr & KN02_ERR_WRITE))
		physadr = (physadr & ~0xfff) | ((physadr & 0xfff) - 5);
	physadr <<= 2;
E 28
	printf("%s memory %s %s error at 0x%x\n",
		(erradr & KN02_ERR_CPU) ? "CPU" : "DMA",
		(erradr & KN02_ERR_WRITE) ? "write" : "read",
		(erradr & KN02_ERR_ECCERR) ? "ECC" : "timeout",
D 28
		(erradr & KN02_ERR_ADDRESS));
E 28
I 28
		physadr);
E 28
	if (erradr & KN02_ERR_ECCERR) {
		*(u_int *)MACH_PHYS_TO_UNCACHED(KN02_SYS_CHKSYN) = 0;
		MachEmptyWriteBuffer();
		printf("ECC 0x%x\n", chksyn);
I 28

		/* check for a corrected, single bit, read error */
		if (!(erradr & KN02_ERR_WRITE)) {
			if (physadr & 0x4) {
				/* check high word */
				if (chksyn & KN02_ECC_SNGHI)
					return;
			} else {
				/* check low word */
				if (chksyn & KN02_ECC_SNGLO)
					return;
			}
		}
E 28
	}
	panic("Mem error interrupt");
E 19
D 11
#endif /* DS5000 */
E 11
I 11
}
I 12

#ifdef DS5000_240
static void
kn03_errintr()
{

	printf("erradr %x\n", *(unsigned *)MACH_PHYS_TO_UNCACHED(KN03_SYS_ERRADR));
	*(unsigned *)MACH_PHYS_TO_UNCACHED(KN03_SYS_ERRADR) = 0;
	MachEmptyWriteBuffer();
}
#endif /* DS5000_240 */
E 12

static void
kn02ba_errintr()
{
	register int mer, adr, siz;
	static int errintr_cnt = 0;

	siz = *(volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_MSR);
	mer = *(volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_MER);
	adr = *(volatile int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_AER);

	/* clear interrupt bit */
	*(unsigned int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_TIMEOUT) = 0;

	errintr_cnt++;
	printf("(%d)%s%x [%x %x %x]\n", errintr_cnt,
	       "Bad memory chip at phys ",
	       kn02ba_recover_erradr(adr, mer),
	       mer, siz, adr);
}

static unsigned
kn02ba_recover_erradr(phys, mer)
	register unsigned phys, mer;
{
	/* phys holds bits 28:2, mer knows which byte */
	switch (mer & KMIN_MER_LASTBYTE) {
	case KMIN_LASTB31:
		mer = 3; break;
	case KMIN_LASTB23:
		mer = 2; break;
	case KMIN_LASTB15:
		mer = 1; break;
	case KMIN_LASTB07:
		mer = 0; break;
	}
	return ((phys & KMIN_AER_ADDR_MASK) | mer);
E 11
E 2
}

D 2
/* machDis.c -
 *
 *     	This contains the routine which disassembles an instruction to find
 *	the target.
 *
 *	Copyright (C) 1989 Digital Equipment Corporation.
 *	Permission to use, copy, modify, and distribute this software and
 *	its documentation for any purpose and without fee is hereby granted,
 *	provided that the above copyright notice appears in all copies.  
 *	Digital Equipment Corporation makes no representations about the
 *	suitability of this software for any purpose.  It is provided "as is"
 *	without express or implied warranty.
 */

#ifndef lint
static char rcsid[] = "$Header: /sprite/src/kernel/mach/ds3100.md/RCS/machDis.c,v 1.1 89/07/11 17:55:43 nelson Exp $ SPRITE (Berkeley)";
#endif not lint

E 2
/*
D 2
 * Define the instruction formats.
 */
typedef union {
	unsigned word;

	struct {
		unsigned imm: 16;
		unsigned f2: 5;
		unsigned f1: 5;
		unsigned op: 6;
	} IType;

	struct {
		unsigned target: 26;
		unsigned op: 6;
	} JType;

	struct {
		unsigned funct: 6;
		unsigned f4: 5;
		unsigned f3: 5;
		unsigned f2: 5;
		unsigned f1: 5;
		unsigned op: 6;
	} RType;

	struct {
		unsigned funct: 6;
		unsigned fd: 5;
		unsigned fs: 5;
		unsigned ft: 5;
		unsigned fmt: 4;
		unsigned : 1;		/* always '1' */
		unsigned op: 6;		/* always '0x11' */
	} FRType;
} InstFmt;

/*
 * Opcodes of the branch instructions.
 */
#define OP_SPECIAL	0x00
#define OP_BCOND	0x01
#define OP_J		0x02
#define	OP_JAL		0x03
#define OP_BEQ		0x04
#define OP_BNE		0x05
#define OP_BLEZ		0x06
#define OP_BGTZ		0x07

/*
 * Branch subops of the special opcode.
 */
#define OP_JR		0x08
#define OP_JALR		0x09

/*
 * Sub-ops for OP_BCOND code.
 */
#define OP_BLTZ		0x00
#define OP_BGEZ		0x01
#define OP_BLTZAL	0x10
#define OP_BGEZAL	0x11

/*
 * Coprocessor branch masks.
 */
#define COPz_BC_MASK	0x1a
#define COPz_BC		0x08
#define COPz_BC_TF_MASK	0x01
#define COPz_BC_TRUE	0x01
#define COPz_BC_FALSE	0x00

/*
 * Coprocessor 1 operation.
 */
#define OP_COP_1	0x11

/*
E 2
 * Return the resulting PC as if the branch was executed.
 */
unsigned
MachEmulateBranch(regsPtr, instPC, fpcCSR, allowNonBranch)
	unsigned *regsPtr;
	unsigned instPC;
	unsigned fpcCSR;
	int allowNonBranch;
{
D 2
	InstFmt *instPtr;
E 2
I 2
	InstFmt inst;
E 2
	unsigned retAddr;
	int condition;
	extern unsigned GetBranchDest();

I 23

	inst = *(InstFmt *)instPC;
E 23
D 2
#ifdef notdef
E 2
I 2
#if 0
E 2
	printf("regsPtr=%x PC=%x Inst=%x fpcCsr=%x\n", regsPtr, instPC,
D 23
		*instPC, fpcCSR);
E 23
I 23
		inst.word, fpcCSR); /* XXX */
E 23
#endif
D 23

D 2
	instPtr = (InstFmt *)instPC;
	switch ((int)instPtr->JType.op) {
E 2
I 2
	inst = *(InstFmt *)instPC;
E 23
	switch ((int)inst.JType.op) {
E 2
	case OP_SPECIAL:
D 2
		switch ((int)instPtr->RType.funct) {
E 2
I 2
		switch ((int)inst.RType.func) {
E 2
		case OP_JR:
		case OP_JALR:
D 2
			retAddr = regsPtr[instPtr->RType.f1];
E 2
I 2
			retAddr = regsPtr[inst.RType.rs];
E 2
			break;

		default:
			if (!allowNonBranch)
				panic("MachEmulateBranch: Non-branch");
			retAddr = instPC + 4;
			break;
		}
		break;

	case OP_BCOND:
D 2
		switch ((int)instPtr->IType.f2) {
E 2
I 2
		switch ((int)inst.IType.rt) {
E 2
		case OP_BLTZ:
		case OP_BLTZAL:
D 2
			if ((int)(regsPtr[instPtr->RType.f1]) < 0)
				retAddr = GetBranchDest(instPtr);
E 2
I 2
			if ((int)(regsPtr[inst.RType.rs]) < 0)
				retAddr = GetBranchDest((InstFmt *)instPC);
E 2
			else
				retAddr = instPC + 8;
			break;

		case OP_BGEZAL:
		case OP_BGEZ:
D 2
			if ((int)(regsPtr[instPtr->RType.f1]) >= 0)
				retAddr = GetBranchDest(instPtr);
E 2
I 2
			if ((int)(regsPtr[inst.RType.rs]) >= 0)
				retAddr = GetBranchDest((InstFmt *)instPC);
E 2
			else
				retAddr = instPC + 8;
			break;

		default:
			panic("MachEmulateBranch: Bad branch cond");
		}
		break;

	case OP_J:
	case OP_JAL:
D 2
		retAddr = (instPtr->JType.target << 2) | 
E 2
I 2
		retAddr = (inst.JType.target << 2) | 
E 2
			((unsigned)instPC & 0xF0000000);
		break;

	case OP_BEQ:
D 2
		if (regsPtr[instPtr->RType.f1] == regsPtr[instPtr->RType.f2])
			retAddr = GetBranchDest(instPtr);
E 2
I 2
		if (regsPtr[inst.RType.rs] == regsPtr[inst.RType.rt])
			retAddr = GetBranchDest((InstFmt *)instPC);
E 2
		else
			retAddr = instPC + 8;
		break;

	case OP_BNE:
D 2
		if (regsPtr[instPtr->RType.f1] != regsPtr[instPtr->RType.f2])
			retAddr = GetBranchDest(instPtr);
E 2
I 2
		if (regsPtr[inst.RType.rs] != regsPtr[inst.RType.rt])
			retAddr = GetBranchDest((InstFmt *)instPC);
E 2
		else
			retAddr = instPC + 8;
		break;

	case OP_BLEZ:
D 2
		if ((int)(regsPtr[instPtr->RType.f1]) <= 0)
			retAddr = GetBranchDest(instPtr);
E 2
I 2
		if ((int)(regsPtr[inst.RType.rs]) <= 0)
			retAddr = GetBranchDest((InstFmt *)instPC);
E 2
		else
			retAddr = instPC + 8;
		break;

	case OP_BGTZ:
D 2
		if ((int)(regsPtr[instPtr->RType.f1]) > 0)
			retAddr = GetBranchDest(instPtr);
E 2
I 2
		if ((int)(regsPtr[inst.RType.rs]) > 0)
			retAddr = GetBranchDest((InstFmt *)instPC);
E 2
		else
			retAddr = instPC + 8;
		break;

D 2
	case OP_COP_1:
		if ((instPtr->RType.f1 & COPz_BC_MASK) == COPz_BC) {
			if ((instPtr->RType.f2 & COPz_BC_TF_MASK) ==
			    COPz_BC_TRUE)
E 2
I 2
	case OP_COP1:
		switch (inst.RType.rs) {
		case OP_BCx:
		case OP_BCy:
			if ((inst.RType.rt & COPz_BC_TF_MASK) == COPz_BC_TRUE)
E 2
				condition = fpcCSR & MACH_FPC_COND_BIT;
			else
				condition = !(fpcCSR & MACH_FPC_COND_BIT);
			if (condition)
D 2
				retAddr = GetBranchDest(instPtr);
E 2
I 2
				retAddr = GetBranchDest((InstFmt *)instPC);
E 2
			else
				retAddr = instPC + 8;
D 2
		} else if (allowNonBranch)
E 2
I 2
			break;

		default:
			if (!allowNonBranch)
				panic("MachEmulateBranch: Bad coproc branch instruction");
E 2
			retAddr = instPC + 4;
D 2
		else
			panic("MachEmulateBranch: Bad coproc branch instruction");
E 2
I 2
		}
E 2
		break;

	default:
		if (!allowNonBranch)
			panic("MachEmulateBranch: Non-branch instruction");
		retAddr = instPC + 4;
	}
D 2
#ifdef notdef
E 2
I 2
#if 0
E 2
D 23
	printf("Target addr=%x\n", retAddr);
E 23
I 23
	printf("Target addr=%x\n", retAddr); /* XXX */
E 23
#endif
	return (retAddr);
}

unsigned
GetBranchDest(InstPtr)
	InstFmt *InstPtr;
{
	return ((unsigned)InstPtr + 4 + ((short)InstPtr->IType.imm << 2));
I 2
}

/*
 * This routine is called by procxmt() to single step one instruction.
 * We do this by storing a break instruction after the current instruction,
 * resuming execution, and then restoring the old instruction.
 */
cpu_singlestep(p)
	register struct proc *p;
{
	register unsigned va;
D 3
	register int *locr0 = p->p_regs;
E 3
I 3
	register int *locr0 = p->p_md.md_regs;
E 3
	int i;

	/* compute next address after current location */
D 23
	va = MachEmulateBranch(locr0, locr0[PC], 0, 1);
E 23
I 23
	va = MachEmulateBranch(locr0, locr0[PC], locr0[FSR], 1);
E 23
	if (p->p_md.md_ss_addr || p->p_md.md_ss_addr == va ||
	    !useracc((caddr_t)va, 4, B_READ)) {
		printf("SS %s (%d): breakpoint already set at %x (va %x)\n",
			p->p_comm, p->p_pid, p->p_md.md_ss_addr, va); /* XXX */
		return (EFAULT);
	}
	p->p_md.md_ss_addr = va;
D 6
	p->p_md.md_ss_instr = fuiword(va);
E 6
I 6
	p->p_md.md_ss_instr = fuiword((caddr_t)va);
E 6
	i = suiword((caddr_t)va, MACH_BREAK_SSTEP);
	if (i < 0) {
		vm_offset_t sa, ea;
		int rv;

		sa = trunc_page((vm_offset_t)va);
		ea = round_page((vm_offset_t)va+sizeof(int)-1);
		rv = vm_map_protect(&p->p_vmspace->vm_map, sa, ea,
			VM_PROT_DEFAULT, FALSE);
		if (rv == KERN_SUCCESS) {
			i = suiword((caddr_t)va, MACH_BREAK_SSTEP);
			(void) vm_map_protect(&p->p_vmspace->vm_map,
				sa, ea, VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
		}
	}
	if (i < 0)
		return (EFAULT);
D 23
	printf("SS %s (%d): breakpoint set at %x: %x (pc %x)\n",
E 23
I 23
#if 0
	printf("SS %s (%d): breakpoint set at %x: %x (pc %x) br %x\n",
E 23
		p->p_comm, p->p_pid, p->p_md.md_ss_addr,
D 23
		p->p_md.md_ss_instr, locr0[PC]); /* XXX */
E 23
I 23
		p->p_md.md_ss_instr, locr0[PC], fuword((caddr_t)va)); /* XXX */
#endif
E 23
	return (0);
E 2
}
I 13

#ifdef DEBUG
kdbpeek(addr)
{
	if (addr & 3) {
		printf("kdbpeek: unaligned address %x\n", addr);
		return (-1);
	}
	return (*(int *)addr);
}

#define MIPS_JR_RA	0x03e00008	/* instruction code for jr ra */

/*
 * Print a stack backtrace.
 */
void
D 17
stacktrace()
E 17
I 17
stacktrace(a0, a1, a2, a3)
	int a0, a1, a2, a3;
E 17
{
	unsigned pc, sp, fp, ra, va, subr;
D 17
	int a0, a1, a2, a3;
E 17
	unsigned instr, mask;
	InstFmt i;
	int more, stksize;
D 17
	int regs[8];
E 17
I 17
	int regs[3];
E 17
	extern setsoftclock();
	extern char start[], edata[];

	cpu_getregs(regs);

	/* get initial values from the exception frame */
	sp = regs[0];
D 17
	pc = regs[2];
E 17
I 17
	pc = regs[1];
E 17
	ra = 0;
D 17
	a0 = regs[3];
	a1 = regs[4];
	a2 = regs[5];
	a3 = regs[6];
	fp = regs[7];
E 17
I 17
	fp = regs[2];
E 17

loop:
	/* check for current PC in the kernel interrupt handler code */
	if (pc >= (unsigned)MachKernIntr && pc < (unsigned)MachUserIntr) {
		/* NOTE: the offsets depend on the code in locore.s */
		printf("interrupt\n");
		a0 = kdbpeek(sp + 36);
		a1 = kdbpeek(sp + 40);
		a2 = kdbpeek(sp + 44);
		a3 = kdbpeek(sp + 48);
		pc = kdbpeek(sp + 20);
		ra = kdbpeek(sp + 92);
		sp = kdbpeek(sp + 100);
		fp = kdbpeek(sp + 104);
	}

	/* check for current PC in the exception handler code */
	if (pc >= 0x80000000 && pc < (unsigned)setsoftclock) {
		ra = 0;
		subr = 0;
		goto done;
	}

	/* check for bad PC */
	if (pc & 3 || pc < 0x80000000 || pc >= (unsigned)edata) {
		printf("PC 0x%x: not in kernel\n", pc);
		ra = 0;
		subr = 0;
		goto done;
	}

	/*
	 * Find the beginning of the current subroutine by scanning backwards
	 * from the current PC for the end of the previous subroutine.
	 */
	va = pc - sizeof(int);
	while ((instr = kdbpeek(va)) != MIPS_JR_RA)
		va -= sizeof(int);
	va += 2 * sizeof(int);	/* skip back over branch & delay slot */
	/* skip over nulls which might separate .o files */
	while ((instr = kdbpeek(va)) == 0)
		va += sizeof(int);
	subr = va;

	/* scan forwards to find stack size and any saved registers */
	stksize = 0;
	more = 3;
	mask = 0;
	for (; more; va += sizeof(int), more = (more == 3) ? 3 : more - 1) {
		/* stop if hit our current position */
		if (va >= pc)
			break;
		instr = kdbpeek(va);
		i.word = instr;
		switch (i.JType.op) {
		case OP_SPECIAL:
			switch (i.RType.func) {
			case OP_JR:
			case OP_JALR:
				more = 2; /* stop after next instruction */
				break;

			case OP_SYSCALL:
			case OP_BREAK:
				more = 1; /* stop now */
			};
			break;

		case OP_BCOND:
		case OP_J:
		case OP_JAL:
		case OP_BEQ:
		case OP_BNE:
		case OP_BLEZ:
		case OP_BGTZ:
			more = 2; /* stop after next instruction */
			break;

		case OP_COP0:
		case OP_COP1:
		case OP_COP2:
		case OP_COP3:
			switch (i.RType.rs) {
			case OP_BCx:
			case OP_BCy:
				more = 2; /* stop after next instruction */
			};
			break;

		case OP_SW:
			/* look for saved registers on the stack */
			if (i.IType.rs != 29)
				break;
			/* only restore the first one */
			if (mask & (1 << i.IType.rt))
				break;
			mask |= 1 << i.IType.rt;
			switch (i.IType.rt) {
			case 4: /* a0 */
				a0 = kdbpeek(sp + (short)i.IType.imm);
				break;

			case 5: /* a1 */
				a1 = kdbpeek(sp + (short)i.IType.imm);
				break;

			case 6: /* a2 */
				a2 = kdbpeek(sp + (short)i.IType.imm);
				break;

			case 7: /* a3 */
				a3 = kdbpeek(sp + (short)i.IType.imm);
				break;

			case 30: /* fp */
				fp = kdbpeek(sp + (short)i.IType.imm);
				break;

			case 31: /* ra */
				ra = kdbpeek(sp + (short)i.IType.imm);
			}
			break;

		case OP_ADDI:
		case OP_ADDIU:
			/* look for stack pointer adjustment */
			if (i.IType.rs != 29 || i.IType.rt != 29)
				break;
			stksize = (short)i.IType.imm;
		}
	}

done:
	printf("%x+%x (%x,%x,%x,%x) ra %x sz %d\n",
		subr, pc - subr, a0, a1, a2, a3, ra, stksize);

	if (ra) {
		if (pc == ra && stksize == 0)
			printf("stacktrace: loop!\n");
		else {
			pc = ra;
			sp -= stksize;
			goto loop;
		}
	}
}
#endif /* DEBUG */
E 13
E 1
