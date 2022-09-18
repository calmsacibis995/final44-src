h33880
s 00015/00015/01388
d D 8.4 93/09/23 16:41:07 bostic 16 15
c changes for 4.4BSD-Lite requested by USL
e
s 00008/00008/01395
d D 8.3 93/09/21 07:59:28 bostic 15 14
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/01401
d D 8.2 93/09/05 09:49:25 mckusick 14 13
c curpri => curpriority
e
s 00002/00002/01401
d D 8.1 93/06/16 16:48:38 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/01397
d D 7.11 93/06/16 16:48:20 mckusick 12 10
c indir => syscall; __indir => __syscall
e
s 00002/00002/01401
d R 8.1 93/06/11 15:03:06 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00007/01401
d D 7.10 93/05/30 20:08:00 utashiro 10 9
c removed unnecessary printf
e
s 00038/00049/01370
d D 7.9 93/05/13 19:50:01 utashiro 9 8
c change for new pmap interface.
e
s 00009/00075/01410
d D 7.8 93/04/08 02:36:50 utashiro 8 7
c removed X_KLUGE
c Changed asynchronous bus error handling.
e
s 00140/00080/01345
d D 7.7 93/03/09 23:57:22 utashiro 7 6
c better NEWS-OS compatibility
c restore onfault flag in interrupt handler
c added traceback function
e
s 00032/00060/01393
d D 7.6 93/01/20 00:22:02 utashiro 6 5
c Same changes as pmax.
e
s 00023/00023/01430
d D 7.5 92/12/17 01:28:22 utashiro 5 4
c make kernel includes standard
e
s 00043/00005/01410
d D 7.4 92/12/16 20:53:54 utashiro 4 3
c Handle __indir().
e
s 00038/00031/01377
d D 7.3 92/07/28 17:33:48 bostic 3 2
c update from Kazumasa Utashiro
e
s 00029/00170/01379
d D 7.2 92/06/25 18:42:37 utashiro 2 1
c deleted DECstation staff
c changes from pmax/trap.c
e
s 01549/00000/00000
d D 7.1 92/06/04 16:06:57 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 13
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department, Ralph Campbell, Sony Corp. and Kazumasa Utashiro
 * of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: trap.c 1.32 91/04/06$
 *
 *	%W% (Berkeley) %G%
 */

D 5
#include "../include/fix_machine_type.h"
#include "param.h"
#include "systm.h"
#include "proc.h"
#include "kernel.h"
#include "signalvar.h"
I 4
#include "syscall.h"
E 4
#include "user.h"
#include "buf.h"
E 5
I 5
D 7
#include <machine/fix_machine_type.h>
E 7
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/signalvar.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <sys/buf.h>
E 5
#ifdef KTRACE
D 5
#include "ktrace.h"
E 5
I 5
#include <sys/ktrace.h>
E 5
#endif
D 5
#include "net/netisr.h"
E 5
I 5
#include <net/netisr.h>
E 5

D 5
#include "../include/trap.h"
#include "../include/psl.h"
#include "../include/reg.h"
#include "../include/cpu.h"
#include "../include/pte.h"
#include "../include/mips_opcode.h"
#include "../include/adrsmap.h"
E 5
I 5
#include <machine/trap.h>
#include <machine/psl.h>
#include <machine/reg.h>
#include <machine/cpu.h>
#include <machine/pte.h>
#include <machine/mips_opcode.h>
#include <machine/adrsmap.h>
E 5
D 2
#if defined(DS3100) || defined(DS5000)
#include "clockreg.h"
#endif
E 2

D 5
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
E 5
I 5
#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
E 5

D 2
#ifdef news3400
E 2
#include "lp.h"
#include "bm.h"
#include "ms.h"
#include "en.h"
D 5
#include "../hbdev/dmac_0448.h"
#include "../sio/scc.h"
E 5
I 5
#include <news3400/hbdev/dmac_0448.h>
#include <news3400/sio/scc.h>
E 5
D 2
#endif
E 2

D 8
/*
 * This is a kludge to allow X windows to work.
 */
D 2
#define X_KLUGE
E 2
I 2
#undef X_KLUGE
E 2

#ifdef X_KLUGE
#define USER_MAP_ADDR	0x4000
#define NPTES 300
static pt_entry_t UserMapPtes[NPTES];
static unsigned nUserMapPtes;
static pid_t UserMapPid;
#endif

E 8
struct	proc *machFPCurProcPtr;		/* pointer to last proc to use FP */

extern void MachKernGenException();
extern void MachUserGenException();
extern void MachKernIntr();
extern void MachUserIntr();
extern void MachTLBModException();
extern void MachTLBMissException();
D 3
extern void MemErrorInterrupt();
E 3
I 3
D 6
static void MemErrorInterrupt();
E 6
E 3
extern unsigned MachEmulateBranch();

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
#endif

/*
 * Handle an exception.
 * Called from MachKernGenException() or MachUserGenException()
 * when a processor trap occurs.
 * In the case of a kernel trap, we return the pc where to resume if
 * ((struct pcb *)UADDR)->pcb_onfault is set, otherwise, return old pc.
 */
unsigned
trap(statusReg, causeReg, vadr, pc, args)
	unsigned statusReg;	/* status register at time of the exception */
	unsigned causeReg;	/* cause register at time of exception */
	unsigned vadr;		/* address (if any) the fault occured on */
	unsigned pc;		/* program counter where to continue */
{
	register int type, i;
	unsigned ucode = 0;
	register struct proc *p = curproc;
D 3
	struct timeval syst;
E 3
I 3
	u_quad_t sticks;
E 3
	vm_prot_t ftype;
	extern unsigned onfault_table[];

#ifdef DEBUG
	trp->status = statusReg;
	trp->cause = causeReg;
	trp->vadr = vadr;
	trp->pc = pc;
	trp->ra = !USERMODE(statusReg) ? ((int *)&args)[19] :
		p->p_md.md_regs[RA];
	trp->code = 0;
	if (++trp == &trapdebug[TRAPSIZE])
		trp = trapdebug;
#endif

	cnt.v_trap++;
	type = (causeReg & MACH_CR_EXC_CODE) >> MACH_CR_EXC_CODE_SHIFT;
	if (USERMODE(statusReg)) {
		type |= T_USER;
D 3
		syst = p->p_stime;
E 3
I 3
		sticks = p->p_sticks;
E 3
	}

	/*
	 * Enable hardware interrupts if they were on before.
	 * We only respond to software interrupts when returning to user mode.
	 */
	if (statusReg & MACH_SR_INT_ENA_PREV)
		splx((statusReg & MACH_HARD_INT_MASK) | MACH_SR_INT_ENA_CUR);

	switch (type) {
	case T_TLB_MOD:
I 3
		/* check for kernel address */
E 3
		if ((int)vadr < 0) {
			register pt_entry_t *pte;
			register unsigned entry;
D 9
#ifndef ATTR
E 9
			register vm_offset_t pa;
D 9
#endif
E 9

			pte = kvtopte(vadr);
			entry = pte->pt_entry;
I 9
#ifdef DIAGNOSTIC
			if (!(entry & PG_V) || (entry & PG_M))
				panic("trap: ktlbmod: invalid pte");
#endif
E 9
			if (entry & PG_RO) {
				/* write to read only page in the kernel */
				ftype = VM_PROT_WRITE;
				goto kernel_fault;
			}
			entry |= PG_M;
			pte->pt_entry = entry;
D 9
			vadr &= PG_FRAME;
			printf("trap: TLBupdate hi %x lo %x i %x\n", vadr,
				entry, MachTLBUpdate(vadr, entry)); /* XXX */
E 9
I 9
			vadr &= ~PGOFSET;
D 10
			printf("trap: ktlbmod: TLBupdate hi %x lo %x i %x\n",
				vadr, entry,
				MachTLBUpdate(vadr, entry)); /* XXX */
E 10
I 10
			MachTLBUpdate(vadr, entry);
E 10
			pa = entry & PG_FRAME;
E 9
#ifdef ATTR
D 9
			pmap_attributes[atop(entry - KERNBASE)] |= PMAP_ATTR_MOD;
E 9
I 9
			pmap_attributes[atop(pa)] |= PMAP_ATTR_MOD;
E 9
#else
D 9
			pa = entry & PG_FRAME;
E 9
			if (!IS_VM_PHYSADDR(pa))
D 9
				panic("trap: kmod");
E 9
I 9
				panic("trap: ktlbmod: unmanaged page");
E 9
D 6
			PHYS_TO_VM_PAGE(pa)->clean = FALSE;
E 6
I 6
			PHYS_TO_VM_PAGE(pa)->flags &= ~PG_CLEAN;
E 6
#endif
			return (pc);
		}
		/* FALLTHROUGH */

	case T_TLB_MOD+T_USER:
	    {
D 9
		pmap_hash_t hp;
#ifndef ATTR
		vm_offset_t pa;
#endif
#ifdef DIAGNOSTIC
		extern pmap_hash_t zero_pmap_hash;
		extern pmap_t cur_pmap;
E 9
I 9
		register pt_entry_t *pte;
		register unsigned entry;
		register vm_offset_t pa;
		pmap_t pmap = &p->p_vmspace->vm_pmap;
E 9

D 6
		if (cur_pmap->pm_hash == zero_pmap_hash)
E 6
I 6
D 9
		if (cur_pmap->pm_hash == zero_pmap_hash ||
		    cur_pmap->pm_hash == (pmap_hash_t)0)
E 6
			panic("tlbmod");
E 9
I 9
		if (!(pte = pmap_segmap(pmap, vadr)))
			panic("trap: utlbmod: invalid segmap");
		pte += (vadr >> PGSHIFT) & (NPTEPG - 1);
		entry = pte->pt_entry;
#ifdef DIAGNOSTIC
		if (!(entry & PG_V) || (entry & PG_M))
			panic("trap: utlbmod: invalid pte");
E 9
#endif
D 9
		hp = &((pmap_hash_t)PMAP_HASH_UADDR)[PMAP_HASH(vadr)];
D 2
		if (hp->low & PG_RO) {
E 2
I 2
		if (((hp->pmh_pte[0].high ^ vadr) & ~PGOFSET) == 0)
			i = 0;
		else if (((hp->pmh_pte[1].high ^ vadr) & ~PGOFSET) == 0)
			i = 1;
		else
			panic("trap: tlb umod not found");
		if (hp->pmh_pte[i].low & PG_RO) {
E 9
I 9
		if (entry & PG_RO) {
			/* write to read only page */
E 9
E 2
			ftype = VM_PROT_WRITE;
			goto dofault;
		}
D 2
		hp->low |= PG_M;
		printf("trap: TLBupdate hi %x lo %x i %x\n", hp->high, hp->low,
			MachTLBUpdate(hp->high, hp->low)); /* XXX */
E 2
I 2
D 9
		hp->pmh_pte[i].low |= PG_M;
		printf("trap: TLBupdate hi %x lo %x i %x\n",
			hp->pmh_pte[i].high, hp->pmh_pte[i].low,
			MachTLBUpdate(hp->pmh_pte[i].high, hp->pmh_pte[i].low)); /* XXX */
E 9
I 9
		entry |= PG_M;
		pte->pt_entry = entry;
		vadr = (vadr & ~PGOFSET) |
			(pmap->pm_tlbpid << VMMACH_TLB_PID_SHIFT);
D 10
		printf("trap: utlbmod: TLBupdate hi %x lo %x i %x\n",
			vadr, entry, MachTLBUpdate(vadr, entry)); /* XXX */
E 10
I 10
		MachTLBUpdate(vadr, entry);
E 10
		pa = entry & PG_FRAME;
E 9
E 2
#ifdef ATTR
D 2
		pmap_attributes[atop(hp->low - KERNBASE)] |= PMAP_ATTR_MOD;
E 2
I 2
D 9
		pmap_attributes[atop(hp->pmh_pte[i].low - KERNBASE)] |=
			PMAP_ATTR_MOD;
E 9
I 9
		pmap_attributes[atop(pa)] |= PMAP_ATTR_MOD;
E 9
E 2
#else
D 2
		pa = hp->low & PG_FRAME;
E 2
I 2
D 9
		pa = hp->pmh_pte[i].low & PG_FRAME;
E 9
E 2
		if (!IS_VM_PHYSADDR(pa))
D 9
			panic("trap: umod");
E 9
I 9
			panic("trap: utlbmod: unmanaged page");
E 9
D 6
		PHYS_TO_VM_PAGE(pa)->clean = FALSE;
E 6
I 6
		PHYS_TO_VM_PAGE(pa)->flags &= ~PG_CLEAN;
E 6
#endif
		if (!USERMODE(statusReg))
			return (pc);
		goto out;
	    }

	case T_TLB_LD_MISS:
	case T_TLB_ST_MISS:
		ftype = (type == T_TLB_ST_MISS) ? VM_PROT_WRITE : VM_PROT_READ;
I 3
		/* check for kernel address */
E 3
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
I 6
		/*
		 * It is an error for the kernel to access user space except
		 * through the copyin/copyout routines.
		 */
		if ((i = ((struct pcb *)UADDR)->pcb_onfault) == 0)
			goto err;
E 6
I 3
		/* check for fuswintr() or suswintr() getting a page fault */
D 6
		if ((i = ((struct pcb *)UADDR)->pcb_onfault) == 4)
E 6
I 6
		if (i == 4)
E 6
			return (onfault_table[i]);
E 3
		goto dofault;

	case T_TLB_LD_MISS+T_USER:
		ftype = VM_PROT_READ;
		goto dofault;

	case T_TLB_ST_MISS+T_USER:
		ftype = VM_PROT_WRITE;
	dofault:
	    {
		register vm_offset_t va;
D 9
		register struct vmspace *vm = p->p_vmspace;
		register vm_map_t map = &vm->vm_map;
E 9
I 9
		register struct vmspace *vm;
		register vm_map_t map;
E 9
		int rv;

I 9
		vm = p->p_vmspace;
		map = &vm->vm_map;
E 9
D 8
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
E 8
		va = trunc_page((vm_offset_t)vadr);
		rv = vm_fault(map, va, ftype, FALSE);
D 9
		if (rv != KERN_SUCCESS) {
			printf("vm_fault(%x, %x, %x, 0) -> %x ADR %x PC %x RA %x\n",
				map, va, ftype, rv, vadr, pc,
				!USERMODE(statusReg) ? ((int *)&args)[19] :
					p->p_md.md_regs[RA]); /* XXX */
			printf("\tpid %d %s PC %x RA %x\n", p->p_pid,
				p->p_comm, p->p_md.md_regs[PC],
				p->p_md.md_regs[RA]); /* XXX */
#ifdef DEBUG
			trapDump("vm_fault");
#endif
		}
E 9
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
D 6
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
			args.i[0] = p->p_md.md_regs[SP] + 4 * sizeof(int);
			(void) sigreturn(curproc, &args, rval);
			goto out;
		}
		/* FALLTHROUGH */

E 6
	case T_ADDR_ERR_ST+T_USER:	/* misaligned or kseg access */
	case T_BUS_ERR_IFETCH+T_USER:	/* BERR asserted to cpu */
	case T_BUS_ERR_LD_ST+T_USER:	/* BERR asserted to cpu */
		i = SIGSEGV;
		break;

	case T_SYSCALL+T_USER:
	    {
		register int *locr0 = p->p_md.md_regs;
		register struct sysent *callp;
		unsigned int code;
		int numsys;
		struct args {
			int i[8];
		} args;
		int rval[2];
		struct sysent *systab;
		extern int nsysent;
I 7
#ifdef COMPAT_NEWSOS
		extern int nnewssys;
		extern struct sysent newssys[];
#endif
E 7
D 2
#ifdef ULTRIXCOMPAT
		extern struct sysent ultrixsysent[];
		extern int ultrixnsysent;
#endif
E 2

		cnt.v_syscall++;
		/* compute next PC after syscall instruction */
		if ((int)causeReg < 0)
			locr0[PC] = MachEmulateBranch(locr0, pc, 0, 0);
		else
			locr0[PC] += 4;
		systab = sysent;
		numsys = nsysent;
D 2
#ifdef ULTRIXCOMPAT
		if (p->p_md.md_flags & MDP_ULTRIX) {
			systab = ultrixsysent;
			numsys = ultrixnsysent;
		}
#endif
E 2
		code = locr0[V0];
#ifdef COMPAT_NEWSOS
D 2
#define	SYSCALL_BSDOFFSET	1000
		if (code >= SYSCALL_BSDOFFSET)
			code -= SYSCALL_BSDOFFSET;
E 2
I 2
D 7
		if (code >= 1000)
			code -= 1000;			/* too easy */
E 7
I 7
		if (code >= 1000) {
			code -= 1000;
			systab = newssys;
			numsys = nnewssys;
		}
E 7
E 2
#endif
D 4
		if (code == 0) {			/* indir */
E 4
I 4
		switch (code) {
D 12
		case SYS_indir:
E 12
I 12
		case SYS_syscall:
E 12
			/*
			 * Code is first argument, followed by actual args.
			 */
E 4
			code = locr0[A0];
#ifdef COMPAT_NEWSOS
D 2
			if (code >= SYSCALL_BSDOFFSET)
				code -= SYSCALL_BSDOFFSET;
E 2
I 2
D 7
			if (code >= 1000)
				code -= 1000;		/* too easy */
E 7
I 7
			if (code >= 1000) {
				code -= 1000;
				systab = newssys;
				numsys = nnewssys;
			}
E 7
E 2
#endif
			if (code >= numsys)
D 4
				callp = &systab[0];	/* indir (illegal) */
E 4
I 4
D 12
				callp = &systab[SYS_indir]; /* (illegal) */
E 12
I 12
				callp = &systab[SYS_syscall]; /* (illegal) */
E 12
E 4
			else
				callp = &systab[code];
			i = callp->sy_narg;
			args.i[0] = locr0[A1];
			args.i[1] = locr0[A2];
			args.i[2] = locr0[A3];
			if (i > 3) {
				i = copyin((caddr_t)(locr0[SP] +
D 4
						3 * sizeof(int)),
E 4
I 4
						4 * sizeof(int)),
E 4
					(caddr_t)&args.i[3],
					(u_int)(i - 3) * sizeof(int));
				if (i) {
					locr0[V0] = i;
					locr0[A3] = 1;
#ifdef KTRACE
					if (KTRPOINT(p, KTR_SYSCALL))
						ktrsyscall(p->p_tracep, code,
							callp->sy_narg, args.i);
#endif
					goto done;
				}
			}
D 4
		} else {
E 4
I 4
			break;

D 12
		case SYS___indir:
E 12
I 12
		case SYS___syscall:
E 12
			/*
D 12
			 * Like indir, but code is a quad, so as to maintain
E 12
I 12
			 * Like syscall, but code is a quad, so as to maintain
E 12
			 * quad alignment for the rest of the arguments.
			 */
			code = locr0[A0 + _QUAD_LOWWORD];
E 4
			if (code >= numsys)
D 4
				callp = &systab[0];	/* indir (illegal) */
E 4
I 4
D 12
				callp = &systab[SYS_indir]; /* (illegal) */
E 12
I 12
				callp = &systab[SYS_syscall]; /* (illegal) */
E 12
			else
				callp = &systab[code];
			i = callp->sy_narg;
			args.i[0] = locr0[A2];
			args.i[1] = locr0[A3];
			if (i > 2) {
				i = copyin((caddr_t)(locr0[SP] +
						4 * sizeof(int)),
					(caddr_t)&args.i[2],
					(u_int)(i - 2) * sizeof(int));
				if (i) {
					locr0[V0] = i;
					locr0[A3] = 1;
#ifdef KTRACE
					if (KTRPOINT(p, KTR_SYSCALL))
						ktrsyscall(p->p_tracep, code,
							callp->sy_narg, args.i);
#endif
					goto done;
				}
			}
			break;

		default:
			if (code >= numsys)
D 12
				callp = &systab[SYS_indir]; /* (illegal) */
E 12
I 12
				callp = &systab[SYS_syscall]; /* (illegal) */
E 12
E 4
			else
				callp = &systab[code];
			i = callp->sy_narg;
			args.i[0] = locr0[A0];
			args.i[1] = locr0[A1];
			args.i[2] = locr0[A2];
			args.i[3] = locr0[A3];
			if (i > 4) {
				i = copyin((caddr_t)(locr0[SP] +
						4 * sizeof(int)),
					(caddr_t)&args.i[4],
					(u_int)(i - 4) * sizeof(int));
				if (i) {
					locr0[V0] = i;
					locr0[A3] = 1;
#ifdef KTRACE
					if (KTRPOINT(p, KTR_SYSCALL))
						ktrsyscall(p->p_tracep, code,
							callp->sy_narg, args.i);
#endif
					goto done;
				}
			}
		}
#ifdef KTRACE
		if (KTRPOINT(p, KTR_SYSCALL))
			ktrsyscall(p->p_tracep, code, callp->sy_narg, args.i);
#endif
D 2
/*
if (!strcmp(p->p_comm, "ftp"))
printf("syscall: pid=%d, code=%d, pc=0x%x\n", p->p_pid, code, pc);
*/
E 2
		rval[0] = 0;
		rval[1] = locr0[V1];
#ifdef DEBUG
		if (trp == trapdebug)
			trapdebug[TRAPSIZE - 1].code = code;
		else
			trp[-1].code = code;
#endif
D 7
#ifdef COMPAT_NEWSOS
	/* 151 = setenvp, 152 = sysnews, 162 = getdomainname KU:XXX */
	if (code == 151 || code == 152 || code == 162)
		i = 0;
	else
#endif
E 7
		i = (*callp->sy_call)(p, &args, rval);
D 7
if(i==EINVAL)
printf("EINVAL: pid=%d, code=%d\n", p->p_pid, code);
E 7
		/*
		 * Reinitialize proc pointer `p' as it may be different
		 * if this is a child returning from fork syscall.
		 */
		p = curproc;
		locr0 = p->p_md.md_regs;
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
D 6
		if (i == ERESTART)
E 6
I 6
		switch (i) {
		case 0:
			locr0[V0] = rval[0];
			locr0[V1] = rval[1];
			locr0[A3] = 0;
			break;

		case ERESTART:
E 6
			locr0[PC] = pc;
D 6
		else if (i != EJUSTRETURN) {
			if (i) {
				locr0[V0] = i;
				locr0[A3] = 1;
			} else {
				locr0[V0] = rval[0];
				locr0[V1] = rval[1];
				locr0[A3] = 0;
			}
E 6
I 6
			break;

		case EJUSTRETURN:
			break;	/* nothing to do */

		default:
			locr0[V0] = i;
			locr0[A3] = 1;
E 6
		}
D 6
		/* else if (i == EJUSTRETURN) */
			/* nothing to do */
E 6
	done:
#ifdef KTRACE
		if (KTRPOINT(p, KTR_SYSRET))
			ktrsysret(p->p_tracep, code, i, rval[0]);
#endif

		goto out;
	    }

	case T_BREAK+T_USER:
	    {
		register unsigned va, instr;

		/* compute address of break instruction */
		va = pc;
		if ((int)causeReg < 0)
			va += 4;

		/* read break instruction */
D 2
		instr = fuiword(va);
E 2
I 2
		instr = fuiword((caddr_t)va);
E 2
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
		if (i < 0) {
			i = SIGTRAP;
			break;
		}
		p->p_md.md_ss_addr = 0;
		goto out;
	    }

	case T_RES_INST+T_USER:
		i = SIGILL;
		break;

	case T_COP_UNUSABLE+T_USER:
		if ((causeReg & MACH_CR_COP_ERR) != 0x10000000) {
			i = SIGILL;	/* only FPU instructions allowed */
			break;
		}
		MachSwitchFPState(machFPCurProcPtr, p->p_md.md_regs);
		machFPCurProcPtr = p;
		p->p_md.md_regs[PS] |= MACH_SR_COP_1_BIT;
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
I 2
#else
#ifdef DEBUG
I 7
		printf("trap: pid %d %s sig %d adr %x pc %x ra %x\n", p->p_pid,
			p->p_comm, i, vadr, pc, p->p_md.md_regs[RA]); /* XXX */
E 7
		trapDump("trap");
I 7
D 8
		traceback();
E 8
E 7
E 2
#endif
D 2
		printf("trap: pid %d %s sig %d adr %x pc %x ra %x\n", p->p_pid,
			p->p_comm, i, vadr, pc, p->p_md.md_regs[RA]); /* XXX */
		trapDump("unkown exception");
E 2
I 2
#endif
E 2
		panic("trap");
	}
D 9
	printf("trap: pid %d %s sig %d adr %x pc %x ra %x\n", p->p_pid,
E 9
I 9
D 10
	printf("trap: pid %d '%s' sig %d adr %x pc %x ra %x\n", p->p_pid,
E 9
		p->p_comm, i, vadr, pc, p->p_md.md_regs[RA]); /* XXX */
E 10
	trapsignal(p, i, ucode);
out:
	/*
	 * Note: we should only get here if returning to user mode.
	 */
D 3
	astpending = 0;
	while (i = CURSIG(p))
E 3
I 3
	/* take pending signals */
	while ((i = CURSIG(p)) != 0)
E 3
D 16
		psig(i);
	p->p_pri = p->p_usrpri;
E 16
I 16
		postsig(i);
	p->p_priority = p->p_usrpri;
E 16
I 3
	astpending = 0;
E 3
	if (want_resched) {
		int s;

		/*
		 * Since we are curproc, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 15
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 15
I 15
		 * If that happened after we put ourselves on the run queue
D 16
		 * but before we swtch()'ed, we might not be on the queue
E 16
I 16
		 * but before we switch()'ed, we might not be on the queue
E 16
		 * indicated by our priority.
E 15
		 */
D 3
		s = splclock();
E 3
I 3
		s = splstatclock();
E 3
D 15
		setrq(p);
E 15
I 15
		setrunqueue(p);
E 15
		p->p_stats->p_ru.ru_nivcsw++;
D 16
		swtch();
E 16
I 16
		mi_switch();
E 16
		splx(s);
D 3
		while (i = CURSIG(p))
E 3
I 3
		while ((i = CURSIG(p)) != 0)
E 3
D 16
			psig(i);
E 16
I 16
			postsig(i);
E 16
	}
D 3
	if (p->p_stats->p_prof.pr_scale) {
		int ticks;
		struct timeval *tv = &p->p_stime;

		ticks = ((tv->tv_sec - syst.tv_sec) * 1000 +
			(tv->tv_usec - syst.tv_usec) / 1000) / (tick / 1000);
		if (ticks)
			addupc(pc, &p->p_stats->p_prof, ticks);
	}
E 3
I 3
	/*
	 * If profiling, charge system time to the trapped pc.
	 */
D 6
	if (p->p_flag & SPROFIL)
		addupc_task(p, pc, (int)(p->p_sticks - sticks));
E 6
I 6
D 16
	if (p->p_flag & SPROFIL) {
E 16
I 16
	if (p->p_flag & P_PROFIL) {
E 16
		extern int psratio;

		addupc_task(p, pc, (int)(p->p_sticks - sticks) * psratio);
	}
E 6
E 3
D 14
	curpri = p->p_pri;
E 14
I 14
D 16
	curpriority = p->p_pri;
E 16
I 16
	curpriority = p->p_priority;
E 16
E 14
	return (pc);
}

I 8
int	badaddr_flag;

E 8
D 2
#ifdef DS5000
struct	intr_tab intr_tab[8];
#endif

#if defined(DS3100) || defined(DS5100)
int temp; /* XXX ULTRIX compiler bug with -O */
#endif

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
	register unsigned mask;
D 3
	clockframe cf;
E 3
I 3
	struct clockframe cf;
I 7
	int oonfault = ((struct pcb *)UADDR)->pcb_onfault;
E 7
E 3

#ifdef DEBUG
	trp->status = statusReg;
	trp->cause = causeReg;
	trp->vadr = 0;
	trp->pc = pc;
	trp->ra = 0;
	trp->code = 0;
	if (++trp == &trapdebug[TRAPSIZE])
		trp = trapdebug;
#endif

	mask = causeReg & statusReg;	/* pending interrupts & enable mask */
D 2
#ifdef news3400
E 2
D 7
#ifndef NOPRIORITY
E 7
	if (mask & MACH_INT_MASK_5) {		/* level 5 interrupt */
		splx((MACH_SPL_MASK_8 & ~causeReg) | MACH_SR_INT_ENA_CUR);
		printf("level 5 interrupt: PC %x CR %x SR %x\n",
			pc, causeReg, statusReg);
		causeReg &= ~MACH_INT_MASK_5;
	}
	if (mask & MACH_INT_MASK_4) {		/* level 4 interrupt */
		/*
		 * asynchronous bus error
		 */
		splx((MACH_SPL_MASK_7 & ~causeReg) | MACH_SR_INT_ENA_CUR);
D 8
		printf("level 4 interrupt: PC %x CR %x SR %x\n",
			pc, causeReg, statusReg);
E 8
		*(char *)INTCLR0 = INTCLR0_BERR;
		causeReg &= ~MACH_INT_MASK_4;
I 8
#define BADADDR 1
		if (oonfault == BADADDR) {		/* XXX */
			badaddr_flag = 1;
		} else {
			printf("level 4 interrupt: PC %x CR %x SR %x\n",
				pc, causeReg, statusReg);
		}
E 8
	}
	if (mask & MACH_INT_MASK_3) {		/* level 3 interrupt */
		/*
		 * fp error
		 */
		splx((MACH_SPL_MASK_6 & ~causeReg) | MACH_SR_INT_ENA_CUR);
		if (!USERMODE(statusReg)) {
#ifdef DEBUG
			trapDump("fpintr");
#else
			printf("FPU interrupt: PC %x CR %x SR %x\n",
				pc, causeReg, statusReg);
#endif
		} else
			MachFPInterrupt(statusReg, causeReg, pc);
		causeReg &= ~MACH_INT_MASK_3;
	}
	if (mask & MACH_INT_MASK_2) {		/* level 2 interrupt */
		register int stat;

		splx((MACH_SPL_MASK_5 & ~causeReg) | MACH_SR_INT_ENA_CUR);
		stat = *(volatile u_char *)INTST0;
		if (stat & INTST0_TIMINT) {	/* timer */
			static int led_count = 0;

			*(volatile u_char *)INTCLR0 = INTCLR0_TIMINT;
			cf.pc = pc;
D 3
			cf.ps = statusReg;
			hardclock(cf);
E 3
I 3
			cf.sr = statusReg;
			hardclock(&cf);
E 3
			if (++led_count > hz) {
				led_count = 0;
				*(volatile u_char *)DEBUG_PORT ^= DP_LED1;
			}
		}
#if NBM > 0
		if (stat & INTST0_KBDINT)	/* keyboard */
			kbm_rint(SCC_KEYBOARD);
#endif
#if NMS > 0
		if (stat & INTST0_MSINT)	/* mouse */
			kbm_rint(SCC_MOUSE);
#endif
		causeReg &= ~MACH_INT_MASK_2;
	}
	if (mask & MACH_INT_MASK_1) {		/* level 1 interrupt */
		splx((MACH_SPL_MASK_4 & ~causeReg) | MACH_SR_INT_ENA_CUR);
		level1_intr();
		causeReg &= ~MACH_INT_MASK_1;
	}
	if (mask & MACH_INT_MASK_0) {		/* level 0 interrupt */
		splx((MACH_SPL_MASK_3 & ~causeReg) | MACH_SR_INT_ENA_CUR);
		level0_intr();
		causeReg &= ~MACH_INT_MASK_0;
	}
	splx((MACH_SPL_MASK_3 & ~causeReg) | MACH_SR_INT_ENA_CUR);
D 7
#else /* NOPRIORITY */
	/* handle clock interrupts ASAP */
	if (mask & MACH_INT_MASK_2) {		/* level 2 interrupt */
		register int stat;
E 7

D 7
		stat = *(volatile u_char *)INTST0;
		if (stat & INTST0_TIMINT) {	/* timer */
			static int led_count = 0;

			*(volatile u_char *)INTCLR0 = INTCLR0_TIMINT;
			cf.pc = pc;
D 3
			cf.ps = statusReg;
			hardclock(cf);
E 3
I 3
			cf.sr = statusReg;
			hardclock(&cf);
E 3
			if (++led_count > hz) {
				led_count = 0;
				*(volatile u_char *)DEBUG_PORT ^= DP_LED1;
			}
		}
#if NBM > 0
		if (stat & INTST0_KBDINT)	/* keyboard */
			kbm_rint(SCC_KEYBOARD);
#endif
#if NMS > 0
		if (stat & INTST0_MSINT)	/* mouse */
			kbm_rint(SCC_MOUSE);
#endif
		causeReg &= ~MACH_INT_MASK_2;	/* reenable clock interrupts */
	}
	/*
	 * Enable hardware interrupts which were enabled but not pending.
	 * We only respond to software interrupts when returning to spl0.
	 */
	splx((statusReg & ~causeReg & MACH_HARD_INT_MASK)|MACH_SR_INT_ENA_CUR);

	if (mask & MACH_INT_MASK_5) {		/* level 5 interrupt */
		printf("level 5 interrupt: PC %x CR %x SR %x\n",
			pc, causeReg, statusReg);
		;
	}
	if (mask & MACH_INT_MASK_4) {		/* level 4 interrupt */
		/*
		 * asynchronous bus error
		 */
		printf("level 4 interrupt: PC %x CR %x SR %x\n",
			pc, causeReg, statusReg);
		*(char *)INTCLR0 = INTCLR0_BERR;
	}
	if (mask & MACH_INT_MASK_3) {		/* level 3 interrupt */
		/*
		 * fp error
		 */
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
	if (mask & MACH_INT_MASK_1)		/* level 1 interrupt */
		level1_intr();
	if (mask & MACH_INT_MASK_0)		/* level 0 interrupt */
		level0_intr();
#endif /* NOPRIORITY */
E 7
D 2
#endif /* news3400 */
#ifdef DS3100
	/* handle clock interrupts ASAP */
	if (mask & MACH_INT_MASK_3) {
		register volatile struct chiptime *c =
			(volatile struct chiptime *)MACH_CLOCK_ADDR;

		temp = c->regc;	/* clear interrupt bits */
		cf.pc = pc;
		cf.ps = statusReg;
		hardclock(cf);
		causeReg &= ~MACH_INT_MASK_3;	/* reenable clock interrupts */
	}
	/*
	 * Enable hardware interrupts which were enabled but not pending.
	 * We only respond to software interrupts when returning to spl0.
	 */
	splx((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
		MACH_SR_INT_ENA_CUR);
	if (mask & MACH_INT_MASK_0)
		siiintr(0);
	if (mask & MACH_INT_MASK_1)
		leintr(0);
	if (mask & MACH_INT_MASK_2)
		dcintr(0);
	if (mask & MACH_INT_MASK_4)
		MemErrorInterrupt();
#endif /* DS3100 */
#ifdef DS5000
	/* handle clock interrupts ASAP */
	if (mask & MACH_INT_MASK_1) {
		register volatile struct chiptime *c =
			(volatile struct chiptime *)MACH_CLOCK_ADDR;
		register unsigned csr;
		static int warned = 0;

		csr = *(unsigned *)MACH_SYS_CSR_ADDR;
		if ((csr & MACH_CSR_PSWARN) && !warned) {
			warned = 1;
			printf("WARNING: power supply is overheating!\n");
		} else if (warned && !(csr & MACH_CSR_PSWARN)) {
			warned = 0;
			printf("WARNING: power supply is OK again\n");
		}

		temp = c->regc;	/* clear interrupt bits */
		cf.pc = pc;
		cf.ps = statusReg;
		hardclock(cf);
		causeReg &= ~MACH_INT_MASK_1;	/* reenable clock interrupts */
	}
	if (mask & MACH_INT_MASK_0) {
		register unsigned csr;
		register unsigned i, m;

		csr = *(unsigned *)MACH_SYS_CSR_ADDR;
		m = csr & (csr >> MACH_CSR_IOINTEN_SHIFT) & MACH_CSR_IOINT_MASK;
#if 0
		*(unsigned *)MACH_SYS_CSR_ADDR =
			(csr & ~(MACH_CSR_MBZ | 0xFF)) |
			(m << MACH_CSR_IOINTEN_SHIFT);
#endif
		/*
		 * Enable hardware interrupts which were enabled but not
		 * pending. We only respond to software interrupts when
		 * returning to spl0.
		 */
		splx((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
			MACH_SR_INT_ENA_CUR);
		for (i = 0; m; i++, m >>= 1) {
			if (!(m & 1))
				continue;
			if (intr_tab[i].func)
				(*intr_tab[i].func)(intr_tab[i].unit);
			else
				printf("spurious interrupt %d\n", i);
		}
#if 0
		*(unsigned *)MACH_SYS_CSR_ADDR =
			csr & ~(MACH_CSR_MBZ | 0xFF);
#endif
	} else {
		/*
		 * Enable hardware interrupts which were enabled but not
		 * pending. We only respond to software interrupts when
		 * returning to spl0.
		 */
		splx((statusReg & ~causeReg & MACH_HARD_INT_MASK) |
			MACH_SR_INT_ENA_CUR);
	}
	if (mask & MACH_INT_MASK_3)
		MemErrorInterrupt();
#endif /* DS5000 */
#if defined(DS3100) || defined(DS5000)
	if (mask & MACH_INT_MASK_5) {
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
#endif /* DS3100 || DS5000 */
E 2
	if (mask & MACH_SOFT_INT_MASK_0) {
D 3
		clockframe cf;
E 3
I 3
		struct clockframe cf;
E 3

		clearsoftclock();
I 2
		cnt.v_soft++;
E 2
		cf.pc = pc;
D 3
		cf.ps = statusReg;
		softclock(cf);
E 3
I 3
		cf.sr = statusReg;
		softclock();
E 3
	}
	/* process network interrupt if we trapped or will very soon */
	if ((mask & MACH_SOFT_INT_MASK_1) ||
	    netisr && (statusReg & MACH_SOFT_INT_MASK_1)) {
		clearsoftnet();
I 2
		cnt.v_soft++;
E 2
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
I 7
	/* restore onfault flag */
	((struct pcb *)UADDR)->pcb_onfault = oonfault;
E 7
}

/*
 * This is called from MachUserIntr() if astpending is set.
 * This is very similar to the tail of trap().
 */
softintr(statusReg, pc)
	unsigned statusReg;	/* status register at time of the exception */
	unsigned pc;		/* program counter where to continue */
{
	register struct proc *p = curproc;
D 3
	register int i;
E 3
I 3
	int sig;
E 3

	cnt.v_soft++;
D 3
	astpending = 0;
	while (i = CURSIG(p))
		psig(i);
E 3
I 3
	/* take pending signals */
	while ((sig = CURSIG(p)) != 0)
D 16
		psig(sig);
E 3
	p->p_pri = p->p_usrpri;
E 16
I 16
		postsig(sig);
	p->p_priority = p->p_usrpri;
E 16
I 3
	astpending = 0;
D 16
	if (p->p_flag & SOWEUPC) {
		p->p_flag &= ~SOWEUPC;
E 16
I 16
	if (p->p_flag & P_OWEUPC) {
		p->p_flag &= ~P_OWEUPC;
E 16
		ADDUPROF(p);
	}
E 3
	if (want_resched) {
		int s;

		/*
		 * Since we are curproc, clock will normally just change
		 * our priority without moving us from one queue to another
		 * (since the running process is not on a queue.)
D 15
		 * If that happened after we setrq ourselves but before we
		 * swtch()'ed, we might not be on the queue indicated by
		 * our priority.
E 15
I 15
		 * If that happened after we put ourselves on the run queue
D 16
		 * but before we swtch()'ed, we might not be on the queue
E 16
I 16
		 * but before we switch()'ed, we might not be on the queue
E 16
		 * indicated by our priority.
E 15
		 */
D 3
		s = splclock();
E 3
I 3
		s = splstatclock();
E 3
D 15
		setrq(p);
E 15
I 15
		setrunqueue(p);
E 15
		p->p_stats->p_ru.ru_nivcsw++;
D 16
		swtch();
E 16
I 16
		mi_switch();
E 16
		splx(s);
D 3
		while (i = CURSIG(p))
			psig(i);
E 3
I 3
		while ((sig = CURSIG(p)) != 0)
D 16
			psig(sig);
E 16
I 16
			postsig(sig);
E 16
E 3
	}
D 14
	curpri = p->p_pri;
E 14
I 14
D 16
	curpriority = p->p_pri;
E 16
I 16
	curpriority = p->p_priority;
E 16
E 14
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
D 7
		printf("   RA %x code %d\n", trp-> ra, trp->code);
E 7
I 7
		printf("   RA %x code %d\n", trp->ra, trp->code);
E 7
	}
	bzero(trapdebug, sizeof(trapdebug));
	trp = trapdebug;
	splx(s);
D 8
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
E 8
D 6
}
#endif

/*
 *----------------------------------------------------------------------
 *
 * MemErrorInterrupt --
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
I 2
#ifdef NOTDEF
E 2
static void
MemErrorInterrupt()
{
D 2
#ifdef DS3100
	volatile u_short *sysCSRPtr = (u_short *)MACH_SYS_CSR_ADDR;
	u_short csr;
E 2

E 6
D 2
	csr = *sysCSRPtr;

	if (csr & MACH_CSR_MEM_ERR) {
		printf("Memory error at 0x%x\n",
			*(unsigned *)MACH_WRITE_ERROR_ADDR);
		panic("Mem error interrupt");
	}
	*sysCSRPtr = (csr & ~MACH_CSR_MBZ) | 0xff;
#endif /* DS3100 */
#ifdef DS5000
	printf("erradr %x\n", *(unsigned *)MACH_ERROR_ADDR);
	*(unsigned *)MACH_ERROR_ADDR = 0;
	MachEmptyWriteBuffer();
#endif /* DS5000 */
E 2
}
I 2
#endif
E 2

/*
 * Return the resulting PC as if the branch was executed.
 */
unsigned
MachEmulateBranch(regsPtr, instPC, fpcCSR, allowNonBranch)
	unsigned *regsPtr;
	unsigned instPC;
	unsigned fpcCSR;
	int allowNonBranch;
{
	InstFmt inst;
	unsigned retAddr;
	int condition;
	extern unsigned GetBranchDest();

#if 0
	printf("regsPtr=%x PC=%x Inst=%x fpcCsr=%x\n", regsPtr, instPC,
		*(unsigned *)instPC, fpcCSR);
#endif

	inst = *(InstFmt *)instPC;
	switch ((int)inst.JType.op) {
	case OP_SPECIAL:
		switch ((int)inst.RType.func) {
		case OP_JR:
		case OP_JALR:
			retAddr = regsPtr[inst.RType.rs];
			break;

		default:
			if (!allowNonBranch)
				panic("MachEmulateBranch: Non-branch");
			retAddr = instPC + 4;
			break;
		}
		break;

	case OP_BCOND:
		switch ((int)inst.IType.rt) {
		case OP_BLTZ:
		case OP_BLTZAL:
			if ((int)(regsPtr[inst.RType.rs]) < 0)
				retAddr = GetBranchDest((InstFmt *)instPC);
			else
				retAddr = instPC + 8;
			break;

		case OP_BGEZAL:
		case OP_BGEZ:
			if ((int)(regsPtr[inst.RType.rs]) >= 0)
				retAddr = GetBranchDest((InstFmt *)instPC);
			else
				retAddr = instPC + 8;
			break;

		default:
			panic("MachEmulateBranch: Bad branch cond");
		}
		break;

	case OP_J:
	case OP_JAL:
		retAddr = (inst.JType.target << 2) | 
			((unsigned)instPC & 0xF0000000);
		break;

	case OP_BEQ:
		if (regsPtr[inst.RType.rs] == regsPtr[inst.RType.rt])
			retAddr = GetBranchDest((InstFmt *)instPC);
		else
			retAddr = instPC + 8;
		break;

	case OP_BNE:
		if (regsPtr[inst.RType.rs] != regsPtr[inst.RType.rt])
			retAddr = GetBranchDest((InstFmt *)instPC);
		else
			retAddr = instPC + 8;
		break;

	case OP_BLEZ:
		if ((int)(regsPtr[inst.RType.rs]) <= 0)
			retAddr = GetBranchDest((InstFmt *)instPC);
		else
			retAddr = instPC + 8;
		break;

	case OP_BGTZ:
		if ((int)(regsPtr[inst.RType.rs]) > 0)
			retAddr = GetBranchDest((InstFmt *)instPC);
		else
			retAddr = instPC + 8;
		break;

	case OP_COP1:
		switch (inst.RType.rs) {
		case OP_BCx:
		case OP_BCy:
			if ((inst.RType.rt & COPz_BC_TF_MASK) == COPz_BC_TRUE)
				condition = fpcCSR & MACH_FPC_COND_BIT;
			else
				condition = !(fpcCSR & MACH_FPC_COND_BIT);
			if (condition)
				retAddr = GetBranchDest((InstFmt *)instPC);
			else
				retAddr = instPC + 8;
			break;

		default:
			if (!allowNonBranch)
				panic("MachEmulateBranch: Bad coproc branch instruction");
			retAddr = instPC + 4;
		}
		break;

	default:
		if (!allowNonBranch)
			panic("MachEmulateBranch: Non-branch instruction");
		retAddr = instPC + 4;
	}
#if 0
	printf("Target addr=%x\n", retAddr);
#endif
	return (retAddr);
}

unsigned
GetBranchDest(InstPtr)
	InstFmt *InstPtr;
{
	return ((unsigned)InstPtr + 4 + ((short)InstPtr->IType.imm << 2));
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
	register int *locr0 = p->p_md.md_regs;
	int i;

	/* compute next address after current location */
	va = MachEmulateBranch(locr0, locr0[PC], 0, 1);
	if (p->p_md.md_ss_addr || p->p_md.md_ss_addr == va ||
	    !useracc((caddr_t)va, 4, B_READ)) {
		printf("SS %s (%d): breakpoint already set at %x (va %x)\n",
			p->p_comm, p->p_pid, p->p_md.md_ss_addr, va); /* XXX */
		return (EFAULT);
	}
	p->p_md.md_ss_addr = va;
D 2
	p->p_md.md_ss_instr = fuiword(va);
E 2
I 2
	p->p_md.md_ss_instr = fuiword((caddr_t)va);
E 2
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
	printf("SS %s (%d): breakpoint set at %x: %x (pc %x)\n",
		p->p_comm, p->p_pid, p->p_md.md_ss_addr,
		p->p_md.md_ss_instr, locr0[PC]); /* XXX */
	return (0);
}

D 2
#ifdef news3400
E 2
/*
 * news3400 - INT0 service routine.
 *
 * INTST0 bit	4:	dma
 *		3:	slot #1
 *		2:	slot #3
 *		1:	external #1
 *		0:	external #3
 */

#define	LEVEL0_MASK	\
	(INTST1_DMA|INTST1_SLOT1|INTST1_SLOT3|INTST1_EXT1|INTST1_EXT3)

level0_intr()
{
	register int stat;

	stat = *(volatile u_char *)INTST1 & LEVEL0_MASK;
	*(u_char *)INTCLR1 = stat;

	if (stat & INTST1_DMA)
		dma_intr();
	if (stat & INTST1_SLOT1)
		exec_hb_intr2();
#if NEN > 0
	if (stat & INTST1_SLOT3) {
		int s, t;

		s = splimp();
		t = lance_intr();
		(void) splx(s);
		if (t == 0)
			exec_hb_intr4();
	}
#endif
#if NLE > 0
	if (stat & INTST1_SLOT3) {
		int s;

		s = splimp();
		leintr(0);
		(void) splx(s);
	}
#endif
	if (stat & INTST1_EXT1)
		print_int_stat("EXT #1");
	if (stat & INTST1_EXT3)
		print_int_stat("EXT #3");
}

/*
 * news3400 - INT1 service routine.
 *
 * INTST0 bit	1:	centro fault
 *		0:	centro busy
 * INTST1 bit	7:	beep
 *		6:	scc
 *		5:	lance
 */

#define LEVEL1_MASK2	(INTST0_CFLT|INTST0_CBSY)
#define LEVEL1_MASK1	(INTST1_BEEP|INTST1_SCC|INTST1_LANCE)

level1_intr(pc)
	unsigned pc;
{
	register int stat;
	register u_int saved_inten1 = *(u_char *)INTEN1;

	*(u_char *)INTEN1 = 0;		/* disable intr: beep, lance, scc */

	stat = *(volatile u_char *)INTST1 & LEVEL1_MASK1;
	*(u_char *)INTCLR1 = stat;

	stat &= saved_inten1;

	if (stat & INTST1_BEEP) {
		*(volatile u_char *)INTCLR1 = INTCLR1_BEEP;
		print_int_stat("BEEP");
	}
	if (stat & INTST1_SCC) {
		scc_intr();
		if (saved_inten1 & *(u_char *)INTST1 & INTST1_SCC)
			scc_intr();
	}
#if NEN > 0
	if (stat & INTST1_LANCE)
		lance_intr();
#endif
#if NLE > 0
	if (stat & INTST1_LANCE)
		leintr(0);
#endif

	*(u_char *)INTEN1 = saved_inten1;

#if NLP > 0
	/*
	 * The PARK2 cannot find centro interrupt correctly.
	 * We must check it by reading the cause register of cpu
	 * while other interrupts are disabled.
	 */
	{
		register int causereg;
		int s = splhigh();

		causereg = get_causereg();
		(void) splx(s);

		if ((causereg & CAUSE_IP4) == 0)
			return;
	}
#endif

	stat = (int)(*(u_char *)INTST0) & LEVEL1_MASK2;
	*(u_char *)INTCLR0 = stat;

	if (stat & INTST0_CBSY)		/* centro busy */
#if NLP > 0
		lpxint(0);
#else
		printf("stray intr: CBSY\n");
#endif
}

/*
 * DMA interrupt service routine.
 */
dma_intr()
{
        register volatile u_char *gsp = (u_char *)DMAC_GSTAT;
        register u_int gstat = *gsp;
        register int mrqb, i;

	/*
	 * when DMA intrrupt occurs there remain some untransferred data.
	 * wait data transfer completion.
	 */
	mrqb = (gstat & (CH0_INT|CH1_INT|CH2_INT|CH3_INT)) << 1;
	if (gstat & mrqb) {
		/*
		 * SHOULD USE DELAY()
		 */
		for (i = 0; i < 50; i++)
			;
		if (*gsp & mrqb)
			printf("dma_intr: MRQ\n");
	}

	/* SCSI Dispatch */
	if (gstat & CH_INT(CH_SCSI))
		scintr();

#include "fd.h"
#if NFD > 0
        /* FDC Interrupt Dispatch */
	if (gstat & CH_INT(CH_FDC))
		fdc_intr(0);
#endif /* NFD > 0 */

#include "sb.h"
#if NSB > 0
        /* Audio Interface Dispatch */
	sbintr(0);
#endif /* NSB > 0 */

        /* Video I/F Dispatch */
	if (gstat & CH_INT(CH_VIDEO))
		;
}

/*
 * SCC vector interrupt service routine.
 */
scc_intr()
{
	int vec;
	extern int scc_xint(), scc_sint(), scc_rint(), scc_cint();
	static int (*func[])() = {
		scc_xint,
		scc_sint,
		scc_rint,
		scc_cint
	};

	vec = *(volatile u_char *)SCCVECT;
	(*func[(vec & SCC_INT_MASK) >> 1])(vec);
}

print_int_stat(msg)
	char *msg;
{
	int s0 = *(volatile u_char *)INTST0;
	int s1 = *(volatile u_char *)INTST1;

	if (msg)
		printf("%s: ", msg);
	else
		printf("intr: ");
	printf("INTST0=0x%x, INTST1=0x%x.\n", s0, s1);
I 7
}

traceback()
{
	u_int pc, sp;

	getpcsp(&pc, &sp);
	backtr(pc, sp);
}

#define EF_RA   	        92              /* r31: return address */
#define KERN_REG_SIZE		(18 * 4)
#define STAND_FRAME_SIZE	24
#define EF_SIZE			STAND_FRAME_SIZE + KERN_REG_SIZE + 12

extern u_int MachKernGenExceptionEnd[];
extern u_int end[];
#define	ENDOFTXT	(end + 1)

#define VALID_TEXT(pc)	\
	((u_int *)MACH_CODE_START <= (u_int *)MACH_UNCACHED_TO_CACHED(pc) && \
	 (u_int *)MACH_UNCACHED_TO_CACHED(pc) <= (u_int *)ENDOFTXT)

#define ExceptionHandler(x) \
	((u_int*)MachKernGenException < (u_int*)MACH_UNCACHED_TO_CACHED(x) && \
	 (u_int*)MACH_UNCACHED_TO_CACHED(x) < (u_int*)MachKernGenExceptionEnd)

backtr(pc, sp)
	register u_int *pc;
	register caddr_t sp;
{
	int fsize;
	u_int *getra();
	extern int _gp[];

	printf("start trace back pc=%x, sp=%x, pid=%d[%s]\n",
		pc, sp, curproc->p_pid, curproc->p_comm);

	while (VALID_TEXT(pc)) {
		if (sp >= (caddr_t)KERNELSTACK || sp < (caddr_t)UADDR) {
			printf("stack exhausted (sp=0x%x)\n", sp);
			break;
		}
		if (ExceptionHandler(pc)) {
			pc = (u_int *)(*((u_int *)&sp[EF_RA]));
			sp += EF_SIZE;
			printf("trapped from pc=%x, sp=%x\n", pc, sp);
		} else {
			pc = getra(pc, sp, &fsize);
			sp += fsize;
			printf("called from pc=%x, sp=%x\n", pc, sp);
		}
	}
	printf("trace back END. pid=%d[%s]\n", curproc->p_pid, curproc->p_comm);
}

#define	NPCSTOCK	128

u_int *
getra(pc, sp, fsize)
	register int *pc;
	register caddr_t sp;
	int *fsize;
{
	u_int regs[32];
	int *opcs[NPCSTOCK];
	register int i, nbpc = 0;
	int printed = 0;
	InstFmt I;

	*fsize = 0;
	for (i = 0; i < 32; i++) regs[i] = 0;
	for (; (u_int*)MACH_UNCACHED_TO_CACHED(pc) < (u_int*)ENDOFTXT; pc++) {
		I.word = *pc;
		switch (I.IType.op) {

		case OP_ADDIU:
			/* sp += fsize */
			if (I.IType.rs == SP && I.IType.rt == SP)
				*fsize = (u_short)I.IType.imm;
			break;

		case OP_LW:
			if (I.IType.rs != SP)
				break;
			regs[I.IType.rt] = *(u_int *)&sp[(short)I.IType.imm];
			break;

		case OP_BEQ:
			if (I.IType.rs != ZERO || I.IType.rt != ZERO)
				break;
			for (i = 0; i < nbpc; i++)
				if (pc == opcs[i]) {
					/*
					 * Brach constructs infinite loop.
					 */
					if (!printed) {
						printf("branch loop\n");
						printed = 1;
					}
					break;
				}
			if (i == nbpc) {
				opcs[nbpc] = pc;
				nbpc = imin(nbpc + 1, NPCSTOCK);
				pc = pc + (short)I.IType.imm;
			}
			break;

		default:
			break;
		}

		I.word = *(pc - 1);
		if (I.RType.op == OP_SPECIAL && I.RType.func == OP_JR)
			return ((int *)regs[I.RType.rs]);
	}
	printf("pc run out of TEXT\n");
	return (0);
E 7
}
D 2
#endif /* news3400 */
E 2
E 1
