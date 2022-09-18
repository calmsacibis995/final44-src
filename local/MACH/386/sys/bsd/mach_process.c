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
 * $Log:	mach_process.c,v $
 * Revision 2.11  89/08/08  21:45:58  jsb
 * 	Instruction cache was not flushed properly on mips
 * 	after setting a breakpoint.
 * 	[89/07/28            af]
 * 
 * Revision 2.10  89/05/31  12:27:17  rvb
 * 	Remove cachectl.h and inline it. [af]
 * 
 * Revision 2.9  89/05/30  10:34:59  rvb
 * 	Made it right for mips.
 * 	Removed inclusion of psl.h for ibmrt and mips.
 * 	Cleaned up a little the ibmrt/else case for reading/writing
 * 	the u-area.
 * 	Other minor cleanups.
 * 	[89/04/03            af]
 * 
 * Revision 2.8  89/03/09  19:29:34  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  14:42:52  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:31:54  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/23  22:04:58  af
 * 	Changes for I386: cut in 386 processor registers
 * 	[89/01/09            rvb]
 * 	
 * 	Started fixes for Mips: pulled over code, most of which
 * 	is disabled.
 * 	[89/01/05            af]
 * 
 * Revision 2.4  88/10/18  03:15:08  mwyoung
 * 	Watch out for zero return value from kmem_alloc_wait.
 * 	[88/09/13            mwyoung]
 * 
 *
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	Make sure p_stat is SSTOP in ptrace().
 *
 * 13-Mar-88  David Golub (dbg) at Carnegie-Mellon University
 *	Use vm_map_copy instead of playing with physical pages.
 *
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 13-Oct-87  David Black (dlb) at Carnegie-Mellon University
 *	run_state --> user_stop_count.
 *
 * 24-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	Set modified bit on any pages modified by copy_to_phys.
 *
 * 13-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	If delivering a thread signal, set thread's u.u_cursig.
 *	Optimize and clean up register references.
 *
 *  2-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	Derived from sys_process.c via major rewrite to eliminate
 *	ipc structure and procxmt.
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)sys_process.c	7.1 (Berkeley) 6/5/86
 */

#ifdef	sun		/* Act like SunOS? */
/* Use Sun version of ptrace */
#else	sun
#include <machine/reg.h>
#ifdef	ibmrt
#include <ca/scr.h>
#include <mach/ca/vm_param.h>		/* for KERNEL_STACK_SIZE */
#endif	ibmrt
#if	!defined(ibmrt) && !defined(mips)
#include <machine/psl.h>
#endif	!defined(ibmrt) && !defined(mips)

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/ptrace.h>

#include <kern/task.h>
#include <kern/thread.h>

#include <vm/vm_map.h>
#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <vm/vm_kern.h>

#ifdef	vax
#define NIPCREG 16
int ipcreg[NIPCREG] =
	{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,AP,FP,SP,PC};
#define	PROGRAM_COUNTER		PC
#define	PROCESSOR_STATUS_WORD	PS
#endif	vax

#ifdef	i386
#define NIPCREG 16
int ipcreg[NIPCREG] =
	{EAX,EBX,ECX,EDX,ESI,EDI,EBP,EIP,ESP};
#define	PROGRAM_COUNTER		EIP
#define	PROCESSOR_STATUS_WORD	EFL
#define	PSL_USERSET		EFL_USERSET
#define	PSL_USERCLR		EFL_USERCLR
#define	PSL_T			EFL_TF
#endif	i386

#ifdef	mc68000
#define NIPCREG 17
int ipcreg[NIPCREG] =
        {R0,R1,R2,R3,R4,R5,R6,R7,AR0,AR1,AR2,AR3,AR4,AR5,AR6,AR7,PC};
#define	PROGRAM_COUNTER		PC
#define	PROCESSOR_STATUS_WORD	PS
#endif	mc68000

#ifdef	ibmrt
#define NIPCREG 18	 /* allow modification of only these u area variables */
int ipcreg[NIPCREG] =
	{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15,IAR,MQ};
#define	PROGRAM_COUNTER		IAR
#define	PROCESSOR_STATUS_WORD	ICSCS
#define	PSL_USERSET		ICSCS_USERSET
#define	PSL_USERCLR		ICSCS_USERCLR
#define	PSL_T			ICSCS_INSTSTEP
#endif	ibmrt

#ifdef	balance
int	ipcreg[] = {R0,R1,R2,R3,R4,R5,R6,R7,FP,SP,PC};
#define NIPCREG	(sizeof(ipcreg)/sizeof(ipcreg[0]))
#define	PROGRAM_COUNTER		PC
#define	PROCESSOR_STATUS_WORD	PS
#endif	balance

#ifdef	multimax
/* 
 *	Multimax does this differently; see mmax/mmax_ptrace.c
 *	and mmax/mmax_ptrace.h for details.
 */
#define	get_ptrace_u mmax_get_ptrace_u
#define set_ptrace_u mmax_set_ptrace_u
#define	PROGRAM_COUNTER		PC
#define	PROCESSOR_STATUS_WORD	PS
#endif	multimax

#ifdef	mips
#define	PROGRAM_COUNTER		EF_EPC
#endif	mips

#define ALIGNED(addr,size)	(((unsigned)(addr)&((size)-1))==0)

/*
 * sys-trace system call.
 */
ptrace()
{
	register struct proc *p;
	register struct a {
		int	req;
		int	pid;
		int	*addr;
		int	data;
	} *uap;

	vm_map_t	victim_map;
	vm_offset_t	start_addr, end_addr,
			kern_addr, offset;
	vm_size_t	size;
	boolean_t	change_protection;
	int		*locr0;
	int		olddata;

	uap = (struct a *)u.u_ap;

	/*
	 *	Intercept and deal with "please trace me" request.
	 */
	if (uap->req <= 0) {
		u.u_procp->p_flag |= STRC;
		return;
	}

	/*
	 *	Locate victim, and make sure it is traceable.
	 */
	p = pfind(uap->pid);
	if (p == 0 || p->task->user_stop_count == 0 ||
	    p->p_stat != SSTOP || p->p_ppid != u.u_procp->p_pid ||
	    !(p->p_flag & STRC)) {
		u.u_error = ESRCH;
		return;
	}

	/*
	 *	Mach version of ptrace executes request directly here,
	 *	thus simplifying the interaction of ptrace and signals.
	 */
	switch (uap->req) {

	case PT_READ_I:
	case PT_READ_D:
		/*
		 *	Read victim's memory
		 */
#ifdef	mips
		if (!ALIGNED(uap->addr, sizeof(int)))
			goto error;
#endif	mips
		start_addr = trunc_page(uap->addr);
		end_addr = round_page(uap->addr + sizeof(int));
		size = end_addr - start_addr;

		victim_map = p->task->map;

		/*
		 *	Allocate some pageable memory in the kernel map,
		 *	and copy the victim's memory to it.
		 */
		kern_addr = kmem_alloc_wait(kernel_pageable_map, size);
		if (kern_addr == 0)
			panic("ptrace: cannot allocate memory");
		if (vm_map_copy(kernel_pageable_map, victim_map,
			kern_addr, size, start_addr, FALSE, FALSE)
		    != KERN_SUCCESS) {
			u.u_error = EIO;
		}
		else {
		    /*
		     *	Read the data from the copy in the kernel map.
		     *	Use bcopy to avoid alignment restrictions.
		     */
		    offset = (vm_offset_t) uap->addr - start_addr;
		    bcopy((caddr_t)(kern_addr + offset),
			  (caddr_t)&u.u_r.r_val1,
			  sizeof(int));
		}

		/*
		 *	Discard the kernel's copy.
		 */
		kmem_free_wakeup(kernel_pageable_map, kern_addr, size);
		break;

	case PT_WRITE_I:
	case PT_WRITE_D:
		/*
		 *	Write victim's memory
		 */
#ifdef	mips
		if (!ALIGNED(uap->addr, sizeof(int)))
			goto error;
#endif	mips
		start_addr = trunc_page(uap->addr);
		end_addr = round_page(uap->addr + sizeof(int));
		size = end_addr - start_addr;

		victim_map = p->task->map;

		/*
		 *	Obtain write access to the page.
		 */
		change_protection = FALSE;
		if (!vm_map_check_protection(victim_map, start_addr, end_addr,
		    VM_PROT_WRITE)) {
			change_protection = TRUE;
			if (vm_map_protect(victim_map, start_addr, end_addr,
			    VM_PROT_READ|VM_PROT_WRITE|VM_PROT_EXECUTE,
			    FALSE) != KERN_SUCCESS) {
				u.u_error = EIO;
				break;
			}
		}

		/*
		 *	Allocate some pageable memory in the kernel map,
		 *	and copy the victim's memory to it.
		 */
		kern_addr = kmem_alloc_wait(kernel_pageable_map, size);
		if (vm_map_copy(kernel_pageable_map, victim_map,
			kern_addr, size, start_addr, FALSE, FALSE)
		    != KERN_SUCCESS) {
			u.u_error = EIO;
		}
		else {
		    /*
		     *	Change the data in the copy in the kernel map.
		     *	Use bcopy to avoid alignment restrictions.
		     */
		    offset = (vm_offset_t)uap->addr - start_addr;
#ifdef	mips
		    /* return old value */
		    bcopy((caddr_t)(kern_addr + offset),
		    	  &olddata,
			  sizeof(int));
#endif	mips
		    bcopy((caddr_t)&uap->data,
			  (caddr_t)(kern_addr + offset),
			  sizeof(int));

		    /*
		     *	Copy it back to the victim.
		     */
		    if (vm_map_copy(victim_map, kernel_pageable_map,
			start_addr, size, kern_addr, FALSE, FALSE)
				!= KERN_SUCCESS) {
			u.u_error = EIO;
		    }
#ifdef	mips
		    /*
		     *	Flush Icache, if we changed the victim's code.
		     *	Also, return previous value.
		    */
		    else if (uap->req == PT_WRITE_I)
			ptrace_user_flush(victim_map, uap->addr, sizeof(int));
		    u.u_r.r_val1 = olddata;
#endif	mips
		}

		/*
		 *	Re-protect the victim's memory.
		 */
		if (change_protection)
		    (void) vm_map_protect(victim_map, start_addr, end_addr,
					VM_PROT_READ|VM_PROT_EXECUTE, FALSE);

		/*
		 *	Discard the kernel's copy.
		 */
		kmem_free_wakeup(kernel_pageable_map, kern_addr, size);

		break;

	case PT_READ_U:
		/*
		 *	Read victim's U-area or registers.
		 *	Offsets are into BSD kernel stack, and must
		 *	be faked to match MACH.
		 */
#if	defined(multimax) || defined(mips)
		if (get_ptrace_u(uap->addr, &(u.u_r.r_val1), p->thread)
		    != 0)
			goto error;
		break;
#else	defined(multimax) || defined(mips)
	    {
		register int	i, off;
		struct user	fake_uarea;

		i = (int)uap->addr;

		if (i < 0 || i >= ctob(UPAGES))
			goto error;

#ifdef	ibmrt
		if (!ALIGNED(i, sizeof(int)))
			goto error;
		/*
		 *	U-area and kernel stack are swapped
		 */
		i -= (ctob(UPAGES) - sizeof(struct user));
		off = i + ctob(UPAGES);
		if (i >= 0) {
#else	ibmrt
		off = i;
		if (i < sizeof(struct user)) {
#endif	ibmrt
		    /*
		     *	We want data from the U area.  Fake it up,
		     *	then pull out the desired int.
		     */
		    bzero((caddr_t)&fake_uarea, sizeof(struct user));
		    fake_u(&fake_uarea, p->thread);
		    u.u_r.r_val1 = *(int *)(((caddr_t)&fake_uarea) + i);
		}
		else {
		    /*
		     *	Assume we want data from the kernel stack, most
		     *	likely the user's registers.
		     *
		     */
		    u.u_r.r_val1 = *(int *)(
			((caddr_t)p->thread->kernel_stack)
			+ (KERNEL_STACK_SIZE - ctob(UPAGES))
			+ off);
		}
		break;
	    }
#endif	defined(multimax) || defined(mips)

	case PT_WRITE_U:
		/*
		 *	Write victim's registers.
		 *	Offsets are into BSD kernel stack, and must
		 *	be faked to match MACH.
		 */
#if	defined(multimax) || defined(mips)
		if (set_ptrace_u(uap->addr, uap->data, p->thread) != 0)
			goto error;
		break;
#else	defined(multimax) || defined(mips)
	    {
		register int	i, off;
		register int	*reg_addr;

		i = (int)uap->addr;
#ifdef	ibmrt
		i -= (ctob(UPAGES) - sizeof(struct user));
		off = i - ctob(UPAGES);
#else	ibmrt
		off = i;
#endif	ibmrt
		/*
		 *	Write one of the user's registers.
		 *	Convert the offset (in old-style Uarea/kernel stack)
		 *	into the corresponding offset into the saved
		 *	register set.
		 */
		reg_addr = (int *)(((caddr_t)p->thread->kernel_stack)
				+ (KERNEL_STACK_SIZE - ctob(UPAGES))
				+ off);

		locr0 = p->thread->u_address.uthread->uu_ar0;

		for (i = 0; i < NIPCREG; i++)
			if (reg_addr == &locr0[ipcreg[i]])
				goto ok;

		if (reg_addr == &locr0[PROCESSOR_STATUS_WORD]) {
			uap->data = (uap->data | PSL_USERSET) & ~PSL_USERCLR;
#ifdef	vax
			/* special problems with compatibility mode */
			if (uap->data & PSL_CM)
			    uap->data &= ~(PSL_FPD|PSL_DV|PSL_FU|PSL_IV);
#endif	vax
		} else {
		    goto error;
		}

	ok:
		*reg_addr = uap->data;
		break;
	    }
#endif	defined(multimax) || defined(mips)

	case PT_KILL:
		/*
		 *	Tell child process to kill itself after it
		 *	is resumed by adding NSIG to p_cursig. [see issig]
		 */
		p->p_cursig += NSIG;
		goto resume;

	case PT_STEP:			/* single step the child */
	case PT_CONTINUE:		/* continue the child */
		locr0 = p->thread->u_address.uthread->uu_ar0;
		if ((int)uap->addr != 1) {
#ifdef	mips
			if (!ALIGNED(uap->addr, sizeof(int)))
				goto error;
#endif	mips
			locr0[PROGRAM_COUNTER] = (int)uap->addr;
		}

		if ((unsigned)uap->data > NSIG)
			goto error;

		if (sigmask(p->p_cursig) & threadmask)
		   p->thread->u_address.uthread->uu_cursig = 0;
		p->p_cursig = uap->data;	/* see issig */
		if (sigmask(uap->data) & threadmask)
		    p->thread->u_address.uthread->uu_cursig = uap->data;

#ifdef	mips
		p->thread->pcb->pcb_sstep = uap->req;
#else	mips
		if (uap->req == PT_STEP) 
			locr0[PROCESSOR_STATUS_WORD] |= PSL_T;
#endif	mips

	resume:
		p->p_stat = SRUN;
		task_resume(p->task);
		break;
		
	default:
	error:
		u.u_error = EIO;
	}
}
#endif	sun
