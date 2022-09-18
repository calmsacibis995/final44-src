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
 * Revision 2.18  91/09/12  15:39:54  berman
 * 	Picked up change from Benjamin Britt (britt@ISI.EDU)
 * 	Fixed calls to vm_map_copyout() from ptrace_read_data and
 * 	ptrace_write_data to discard map copy object.
 * 	[91/09/12            berman]
 * 
 * Revision 2.17  91/04/03  12:59:16  mbj
 * 	Omron changes[sic]
 * 
 * Revision 2.16  90/10/18  15:41:39  mrt
 * 	Added include of kern/sched_prim.h
 * 	[90/10/18            mrt]
 * 
 * Revision 2.15  90/10/18  13:04:25  mrt
 * 	Fixed ptrace() to wakeup for real a thtread that got a signal.
 * 	[90/09/23            af]
 * 
 * Revision 2.14  90/08/30  10:58:50  bohman
 * 	Changes for mac2.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.13  89/10/19  13:14:02  af
 * 	Fixed Mips case that got botched in previous merge.
 * 	Also, added a 'flush' argument to the ptrace_write_data()
 * 	function, in anticipation of other architectures (besides MIPS)
 * 	which will need to flush the Icache in ptrace.
 * 	[89/10/14            af]
 * 
 * Revision 2.12  89/10/10  10:47:04  mwyoung
 * 	Separate out the routines to read/write user address spaces
 * 	so that they may be used in architecture-specific ptrace modules.
 * 	[89/10/07            mwyoung]
 * 	Use new vm_map_copy technology.
 * 	[89/10/07  19:13:32  mwyoung]
 * 
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

#if	defined(luna88k)
#include <machine/m88k.h>
#endif	/* defined(luna88k) */

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
#include <kern/sched_prim.h>

#include <vm/vm_map.h>
#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <vm/vm_kern.h>

#if	defined(mac2)
#else	defined(mac2)
#if	defined(sun)
/* Use Sun version of ptrace */
#else	defined(sun)

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

#if	defined(luna88k)
int     ipcreg[] = {R0, R1, R2, R3, R4, R5, R6, R7,
		    R8, R9, R10,R11,R12,R13,R14,R15,
		    R16,R17,R18,R19,R20,R21,R22,R23,
		    R24,R25,R26,R27,R28,R29,R30,R31,
		    RSXIP,RSNIP,RSFIP,
		    RFPECR,RFPHS1,RFPLS1,RFPHS2,RFPLS2,
		    RFPPT,RFPRH,RFPRL,RFPIT,RFPSR,RFPCR
		};
#define NIPCREG (sizeof(ipcreg)/sizeof(ipcreg[0]))
#define	PROCESSOR_STATUS_WORD	PS
#endif	/* defined(luna88k) */

#ifdef	mips
#define	PROGRAM_COUNTER		EF_EPC
#endif	mips

#define ALIGNED(addr,size)	(((unsigned)(addr)&((size)-1))==0)

#if     defined(luna88k)

#define INST_NONE  	0	/* not branch, jump, trap */
#define INST_TRAP   	1	/* trap instruction */
#define INST_BRANCH 	2	/* jump or non-conditional branch */
#define INST_COND 	3	/* conditional branch */
#define	INST_COND_N	4	/* delayed conditional branch */

struct target_result
 {
	int code;	      /* see defines INST_NONE, etc above */
	int *target_addr;     /* target address if type 3 or 4 */
 };
#endif  /* defined(luna88k) */

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

	int		*locr0;

	uap = (struct a *)u.u_ap;

	/*
	 *	Intercept and deal with "please trace me" request.
	 */
	if (uap->req <= 0) {
		u.u_procp->p_flag |= STRC;
#if	defined(luna88k)
                u.u_procp->u_next1.addr = DEST_NULL;
                u.u_procp->u_next2.addr = DEST_NULL;
#endif	/* defined(luna88k) */
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
		u.u_error = ptrace_read_data(p,
				(vm_offset_t)uap->addr,
				sizeof(int),
				(caddr_t)&u.u_r.r_val1);
		break;



	case PT_WRITE_I:
	case PT_WRITE_D:
		u.u_error = ptrace_write_data(p,
				(vm_offset_t)uap->addr,
				sizeof(int),
				(caddr_t)&uap->data,
				(caddr_t)&u.u_r.r_val1,
				(uap->req == PT_WRITE_I));
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

#if	defined(luna88k)
		if (!ALIGNED(i, sizeof(int)))
			goto error;
#endif	/* defined(luna88k) */

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

#if	defined(luna88k)
			uap->data = (uap->data & PSR_SET_BY_USER) | PSR_USER;
#else	/* not defined(luna88k) */
			uap->data = (uap->data | PSL_USERSET) & ~PSL_USERCLR;
#endif	/* not defined(luna88k) */

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

#if	defined(luna88k)
			locr0[RSXIP] = 0;
			locr0[RSNIP] = (int)uap->addr|NIP_V;
			locr0[RSFIP] = ((int)uap->addr+4)|FIP_V;
#else	/* not defined(luna88k) */
			locr0[PROGRAM_COUNTER] = (int)uap->addr;
#endif  /* not defined(luna88k) */

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

#if	defined(luna88k)
		 {
		  int *next_inst;      	/* holds the next instruction pointer */
		  int *target_inst;	/* holds target of branch or jump */

		  struct target_result t_result;

		  /* clear any previous step breakpoint */

		  if (p->u_next1.addr)		/* do we have a trap here? */
		   {				/* if so, restore inst */
			store_instruction
			 (
				p,        	/* pass the proc pointer */
				p->u_next1.addr,/* pass the inst address */ 
				p->u_next1.data	/* pass the inst to restore */
			 );
			p->u_next1.addr = DEST_NULL;  /* clear the entry */
		   }

		  if (p->u_next2.addr)		/* do we have a trap here? */
		   {				/* if so, restore inst */
			store_instruction
			 (
				p,        	/* pass the proc pointer */
				p->u_next2.addr,/* pass the inst address */ 
				p->u_next2.data	/* pass the inst to restore */
			 );
			p->u_next2.addr = DEST_NULL;  /* clear the entry */
		   }


		  /* 
		   * Now we look at the next instruction.  If it is a branch,
		   * jump or trap which can transfer control to other than the
		   * next instruction, we set two step breakpoints (one for
		   * the next instruction and one for one other possible target
		   * (traps might have even more than one but I can't guess
		   * where that might be).
		   */ 

                  next_inst = (int *)(locr0[RSNIP] & ~(FIP_V | FIP_E));  

		  target_check(p, next_inst, &t_result);
		  target_inst = t_result.target_addr;

		  switch (t_result.code)
		   {

		    /* The next instruction does not do anything special to
		     * to the instruction pointer (it is not a jump, branch
 		     * or trap).  Just set one breakpoint at the instruction
		     * following the nip
		     */
		    case INST_NONE:
                      p->u_next1.addr = next_inst + 1;
	  	      p->u_next1.data = fetch_instruction(p, next_inst + 1);
                      store_instruction(p, p->u_next1.addr, STEP_BREAK_INST);

                      p->u_next2.addr = DEST_NULL;  /* clear second bpt entry */

		      break;

		    /*
		     * The next instruction is a trap instruction which may
		     * get special handling by the operating system (it may
		     * be a system call).  Put breakpoints at both of the
		     * next instructions to try to intercept the return from
		     * the system call.
		     */
		    case INST_TRAP:
                      p->u_next1.addr = next_inst + 1;
		      p->u_next1.data = fetch_instruction(p, next_inst + 1);
                      store_instruction(p, p->u_next1.addr, STEP_BREAK_INST);

                      p->u_next2.addr = next_inst + 2;
		      p->u_next2.data = fetch_instruction(p, next_inst + 2);
                      store_instruction(p, p->u_next2.addr, STEP_BREAK_INST);

		      break;

		    /*
	             * The next instruction is a jump or non-conditional
		     * branch.  We know we will take the branch so just  
		     * set one breakpoint at the target of the branch.
		     */
		    case INST_BRANCH:
                      p->u_next1.addr = target_inst;
		      p->u_next1.data = fetch_instruction(p, target_inst);
                      store_instruction(p, p->u_next1.addr, STEP_BREAK_INST);

                      p->u_next2.addr = DEST_NULL;  /* clear second bpt entry */

		      break;

		    /*
	             * The next instruction is a conditional branch.  We 
		     * must set two step breakpoints here.  One is at FIP+4
		     * in case we don't take the branch and one is at
		     * the target of the branch. 
		     */
		    case INST_COND:
                      p->u_next1.addr = next_inst + 1;
		      p->u_next1.data = fetch_instruction(p, next_inst + 1);
                      store_instruction(p, p->u_next1.addr, STEP_BREAK_INST);

                      p->u_next2.addr = target_inst;
		      p->u_next2.data = fetch_instruction(p, target_inst);
                      store_instruction(p, p->u_next2.addr, STEP_BREAK_INST);

		      break;

		    /*
		     * The next instruction is a delayed conditional branch.
		     * We must set two breakpoints here as with a normal 
		     * conditional branch but the first breakpoint goes at 
		     * FIP+8 in case we don't take the branch and the second
		     * one is at the target of the branch.
		     */
		    case INST_COND_N:
                      p->u_next1.addr = next_inst + 2;
		      p->u_next1.data = fetch_instruction(p, next_inst + 2);
                      store_instruction(p, p->u_next1.addr, STEP_BREAK_INST);

                      p->u_next2.addr = target_inst;
		      p->u_next2.data = fetch_instruction(p, target_inst);
                      store_instruction(p, p->u_next2.addr, STEP_BREAK_INST);
		  }

		 }
#else   /* not defined(luna88k) */
			locr0[PROCESSOR_STATUS_WORD] |= PSL_T;
#endif  /* not defined(luna88k) */

#endif	mips

	resume:
		p->p_stat = SRUN;
		if (p->thread && p->p_cursig)
			clear_wait(p->thread, THREAD_INTERRUPTED, TRUE);
		task_resume(p->task);
		break;
		
	default:
	error:
		u.u_error = EIO;
	}
}
#endif	sun
#endif defined(mac2)

#if	defined(luna88k)

#define	IMM_16	    0x0000ffff 		/* 16-bit immediate displacement */
#define IMM_16_SIGN 0x00008000 		/* sign bit for 16-bit displacement */
#define IMM_16_EXT  0xffff0000 		/* sign extend field for 16-bit disp */
#define IMM_26      0x03ffffff 		/* 26-bit immediate displacement */
#define IMM_26_SIGN 0x02000000 		/* sign bit for 26-bit displacement */
#define IMM_26_EXT  0xfc000000 		/* sign extend field for 26-bit disp */

#define JUMP_REG    0x0000001f 		/* target register for jumps */

#define BRANCH_MASK 0xf8000000 		/* mask for all branch instructions */
#define	BRANCH_DLY  0x04000000 		/* delay bit for branch instructions */
#define	JUMP_MASK   0xfc00fbe0 		/* mask for jump instructions */
#define JUMP_DLY    0x00000400 		/* delay bit for jump instructions */
#define TRAP_MASK   0xfc00fe00 		/* mask for traps */

#define INSTRUCTION_BYTES 4		/* bytes per MC88100 instruction */

static void
target_check(p, next_inst, t_result)
struct proc *p;			/* pointer to proc structure for this thread */
int *next_inst;			/* pointer to next instruction to execute */
struct target_result *t_result;	/* pointer to result structure */
{
	int nip_instruction;	/* actual next instruction fetched from code */
	int nip_opcode;		/* only relevant opcode fields of next inst */
	int displacement;	/* displacement for branch targets */
	int jump_reg;		/* register for jump targets */

	nip_instruction = fetch_instruction(p, next_inst); /* fetch next inst */
	
	/*	
	 * First check if we have a branch instruction.  If it is a bb0,
	 * bb1, or bcnd, we extract a 16-bit offset.  If it is a br or bsr,
	 * we extract a 26-bit offset. 
	 */
	nip_opcode = nip_instruction & BRANCH_MASK;	/* mask for branch */ 	

	switch (nip_opcode)	
	 {
	    case 0xd0000000:	/* instruction is bb0 or bb0.n */
	    case 0xd8000000:	/* instruction is bb1 or bb1.n */
	    case 0xe8000000:	/* instruction is bcnd or bcnd.n */

		displacement = nip_instruction & IMM_16;
		if (displacement & IMM_16_SIGN)	    /* if the sign bit is set */
			displacement |= IMM_16_EXT; /* must sign extend it */

		if (nip_instruction & BRANCH_DLY)    /* delayed branch set? */
			t_result->code = INST_COND_N;/* report delayed branch */
		else
			t_result->code = INST_COND;  /* else normal branch */

		t_result->target_addr = next_inst + displacement;

		return;		/* return with details in t_result */

	    case 0xc0000000:	/* instruction is a br or br.n */
	    case 0xc8000000:	/* instruction is a bsr or bsr.n */

		displacement = nip_instruction & IMM_26;
		if (displacement & IMM_26_SIGN)	    /* if the sign bit is set */
			displacement |= IMM_26_EXT; /* must sign extend */

		t_result->code = INST_BRANCH;	   /* non-conditional branch */

		t_result->target_addr = next_inst + displacement;

		return;		/* return with details in t_result */
		

	    default:

		break;		/* not a branch, continue with next check */

	 }
		
	/*
  	 * Now check for a jump instruction.  Both jmp and jsr use registers
	 * to designate the branch target so we must load the target address
 	 * from the saved exception registers.
	 */
	nip_opcode = nip_instruction & JUMP_MASK;	/* mask for jump */ 	

	switch (nip_opcode)	
	 {
	    case 0xf400c000:	/* instruction is jmp or jmp.n */
	    case 0xf400c800:	/* instruction is jsr or jsr.n */

		jump_reg = nip_instruction & JUMP_REG;

		t_result->code = INST_BRANCH;   /* just an unconditional jump */

		t_result->target_addr=		/* load target from register */
			(int *)(p->thread->u_address.u_ar0[jump_reg]);

		return;		/* return with details in t_result */


	    default:

		break;		/* not a jump, continue with next check */

	 }

	/*
  	 * Now check for a trap instruction.  The most commonly used trap is
	 * tb0 0,r0,0x80 which is a normal (not mach) system call on the 88k.
 	 * System calls will either return to the instruction at nip+4 or
	 * nip+8 depending on whether the call was successful or not.  I do 	
	 * not know all of the possible things traps could do but for now,
	 * I will assume that any tb0, tb1, or tcnd could return to either
   	 * of the following two instructions.  I do not know what to do with
	 * tbnd at this point.
	 */
	nip_opcode = nip_instruction & TRAP_MASK;	/* mask for trap */ 	

	switch (nip_opcode)	
	 {
	    case 0xf000d000:	/* instruction is a tb0 */
	    case 0xf000d800:	/* instruction is a tb1 */
	    case 0xf000e800:	/* instruction is a tcnd */

		t_result->code = INST_TRAP; 	/* indicate we have a trap */

		return;		/* return with details in t_result */

	    default:

		break;		/* not a trap, continue with next check */

	 }

	/*
	 * We did not find any of the instructions that require special
	 * handling.  Just return INST_NONE which will cause only one
	 * single step breakpoint to be set (at the instruction following
	 * nip).
	 */	
	t_result->code = INST_NONE;	/* no special handling for this one */	

	return;

}

/*
 * This routine is used to put an instruction into a users code space.  
 * Currently this routine is used by the single step execution mechanism which
 * is needed by most debuggers.  This routine is normally called before a
 * single step is executed to put a special breakpoint into the user code at 
 * the next instruction to execute.  It is then called when the breakpoint is
 * hit to put back the original user instruction.
 */
store_instruction(p, addr, data)
  struct proc	*p;
  vm_offset_t	addr;
  int 		data;
{

	addr = (vm_offset_t)((int)addr & ~(FIP_V | FIP_E));  /* Clear flags */

	/*
	 * Write instruction to user text space
 	 */
	u.u_error = ptrace_write_data(p, addr, INSTRUCTION_BYTES, &data, 0, 0);

}

/*
 * Fetch an instruction from inferior text space
 */

int
fetch_instruction(p, addr)
  struct proc	 *p;
  vm_offset_t    addr;
{

	int		data;

	/*
	 * Read data to user text space
 	 */
	u.u_error = ptrace_read_data(p, addr, INSTRUCTION_BYTES, &data);

	return(data); 		/* return the fetched instruction */
}
#endif  /* defined(luna88k) */

/*
 *	Convenient routines to read/write process address spaces
 *
 *	XXX If anyone feels like doing some public service,
 *	XXX these routines should be reimplemented using only
 *	XXX the exported Mach interface calls.
 */

int ptrace_read_data(p, address, amount, resulting_data)
	struct proc	*p;
	vm_offset_t	address;
	vm_size_t	amount;
	caddr_t		resulting_data;
{
	vm_map_t	victim_map;
	vm_offset_t	start_addr, end_addr,
			kern_addr, offset;
	vm_size_t	size;
	vm_map_copy_t	copy_result;
	int		result;

	/*
	 *	Read victim's memory
	 */

#ifdef	mips
	if (!ALIGNED((int *) address, amount))
		return(EIO);
#endif	mips

	victim_map = p->task->map;
	vm_map_reference(victim_map);
	if (vm_map_copyin(
		victim_map,
		address,
		amount,
		FALSE,
		&copy_result)
	    != KERN_SUCCESS) {
	    	vm_map_deallocate(victim_map);
		return(EIO);
	}
	vm_map_deallocate(victim_map);
	if (vm_map_copyout(kernel_pageable_map, &kern_addr, copy_result, TRUE)
	    != KERN_SUCCESS) {
		result = EIO;
	}
	else {
	    /*
	     *	Read the data from the copy in the kernel map.
	     *	Use bcopy to avoid alignment restrictions.
	     */
	    bcopy((caddr_t)(kern_addr),
		  resulting_data,
		  amount);
	    result = 0;
	}

	/*
	 *	Discard the kernel's copy.
	 */
	(void) vm_deallocate(kernel_pageable_map, kern_addr, amount);
	return(result);
}


int ptrace_write_data(p, address, amount, new_data, old_data, flush)
	struct proc	*p;
	vm_offset_t	address;
	vm_size_t	amount;
	caddr_t		new_data;
	caddr_t		old_data;
	boolean_t	flush;
{
	vm_map_t	victim_map;
	vm_offset_t	start_addr, end_addr,
			kern_addr, offset;
	vm_size_t	size;
	vm_map_copy_t	copy_result;
	boolean_t	change_protection;
	int		result = 0;

#if	!defined(mips) && defined(lint)
	if (flush) old_data++;
#endif	!defined(mips) && defined(lint)

	/*
	 *	Write victim's memory
	 */
#ifdef	mips
	if (!ALIGNED(address, amount))
		return(EIO);
#endif	mips

	start_addr = trunc_page(address);
	end_addr = round_page(address + amount);
	size = end_addr - start_addr;

	victim_map = p->task->map;

	/*
	 *	Allocate some pageable memory in the kernel map,
	 *	and copy the victim's memory to it.
	 */
	vm_map_reference(victim_map);
	if (vm_map_copyin(victim_map, start_addr, size, FALSE, &copy_result)
	    != KERN_SUCCESS) {
	    	vm_map_deallocate(victim_map);
		return(EIO);
	}
	if (vm_map_copyout(kernel_pageable_map, &kern_addr, copy_result, TRUE)
	    != KERN_SUCCESS) {
	    	vm_map_deallocate(victim_map);
		return(EIO);
	}

	/*
	 *	Change the data in the copy in the kernel map.
	 *	Use bcopy to avoid alignment restrictions.
	 */

	offset = (vm_offset_t)address - start_addr;
#ifdef	mips
	bcopy((caddr_t) (kern_addr + offset), old_data, amount);
#endif	mips
	bcopy(new_data, (caddr_t) (kern_addr + offset), amount);

	/*
	 *	Copy it back to the victim.
	 */

	if (vm_map_copyin(kernel_pageable_map, kern_addr, size, TRUE, &copy_result) != KERN_SUCCESS) {
	    	vm_map_deallocate(victim_map);
		vm_deallocate(kernel_pageable_map, kern_addr, amount);
		return(EIO);
	}

	/*
	 *	Obtain write access to the page.
	 */
	change_protection = FALSE;
	if (!vm_map_check_protection(victim_map, start_addr, end_addr,
	    VM_PROT_WRITE)) {
		change_protection = TRUE;
		(void) vm_map_protect(victim_map, start_addr, end_addr,
			VM_PROT_ALL, FALSE);
	}

	if (vm_map_copy_overwrite(
		victim_map,
		start_addr,
		copy_result,
		FALSE /* XXX interruptible */)
	    != KERN_SUCCESS)
		result = EIO;

	vm_map_copy_discard(copy_result);

	/*
	 *	Re-protect the victim's memory.
	 */
	if (change_protection) {
	    (void) vm_map_protect(victim_map, start_addr, end_addr,
				VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
	}
#ifdef	mips
	/*
	 *	Flush Icache, as we might have changed the victim's code.
	 */
	if (flush)
		ptrace_user_flush(victim_map, start_addr, amount);
#endif	mips

    	vm_map_deallocate(victim_map);

	/*
	 *	Discard the kernel's copy.
	 */
	(void) vm_deallocate(kernel_pageable_map, kern_addr, size);

	return(result);
}
