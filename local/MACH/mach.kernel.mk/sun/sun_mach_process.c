/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*	@(#)sys_process.c 1.1 86/02/03 SMI; from UCB 5.10 83/07/01	*/
/*
 * HISTORY
 * $Log:	sun_mach_process.c,v $
 * Revision 2.7  89/10/10  10:58:52  mwyoung
 * 	Use standardized ptrace routines for reading/writing user
 * 	address spaces.
 * 	[89/10/07            mwyoung]
 * 
 * Revision 2.6  89/07/11  13:55:42  jjc
 * 	Modified for Sun 4.
 * 	[88/07/08            jjc]
 * 
 * Revision 2.5  89/04/23  13:22:39  gm0w
 * 	Moved the statement that sets victim_map to before victim_map is
 * 	used in the PTRACE_WRITETEXT case.  Fix from jjc.
 * 	[89/04/23            gm0w]
 * 
 * Revision 2.4  89/03/09  21:31:22  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:32:04  gm0w
 * 	Fixed includes as part of kernel cleanup.
 * 	[89/02/08            jjc]
 * 
 * 17-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	Make sure p_stat is SSTOP in ptrace().
 *
 * 25-Apr-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to get and set FPA registers.
 *
 * 17-Mar-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: changed to run completely in caller process, without
 *	waking up the victim.  Renamed file to 'sun_mach_process.c'.
 *
 * 26-Oct-87  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TT: Fixed entry test logic to make attach operation work.
 *	Update to sig_lock logic.
 *
 * 30-Sep-87  David Black (dlb) at Carnegie-Mellon University
 *	replaced proc lock with sig lock
 *
 * 24-Aug-87  Karl Hauth (hauth) at Carnegie-Mellon University
 *	Set p->p_stat to SRUN before doing task_resume() in runchild(),
 *	and now check for (p->task->run_state != TASK_WAITING) rather
 *	than (p->thread->state != THREAD_STOPPED) in ptrace(), both
 *	under the direction of dlb, to whom much thanks is owed.
 *
 * 20-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TT: Thread exception support.  Also fixed exit sequence
 *	when killing child.
 *
 * 16-Jul-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in MACH_TT changes from sys_process.c.
 *
 * 31-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Minimal support for MACH_TT (enough for proper compilation, will
 *	have to be checked later).
 *
 * 04-Mar-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified for Mach.
 *
 */
#include <cputypes.h>


#include <machine/reg.h>
#include <machine/psl.h>
#include <machine/vmparam.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/user.h>
#include <sys/proc.h>

#include <mach/vm_param.h>
#include <vm/vm_kern.h>
#include <vm/vm_map.h>
#include <kern/thread.h>

#include <sun/ptrace.h>
#ifdef sun
#include "fpa.h"
#if NFPA > 0
#include <sundev/fpareg.h>
#endif NFPA > 0
#endif sun

#ifdef	mc68000
#define NIPCREG 17
int ipcreg[NIPCREG] =
	{R0,R1,R2,R3,R4,R5,R6,R7,AR0,AR1,AR2,AR3,AR4,AR5,AR6,AR7,PC};
#endif	mc68000
#ifdef	sparc
#define	NIPCREG 17
int ipcreg[NIPCREG] =
	{PC,nPC,G1,G2,G3,G4,G5,G6,G7,O0,O1,O2,O3,O4,O5,O6,O7};
#endif	sparc

#define PHYSOFF(p, o) \
	((physadr)(p)+((o)/sizeof (((physadr)0)->r[0])))


/*
 * sys-trace system call.
 */
ptrace()
{
	register struct proc *p;
	register struct a {
		enum ptracereq req;
		int	pid;
		caddr_t	addr;
		int	data;
		caddr_t addr2;
	} *uap;

	thread_t	thread;
	struct uthread	*uthread;
	int		*locr0;
	struct pcb	*pcb;

	int		i;
	int		*up;

#ifdef	sun3
	extern short	fppstate;
#endif	sun3

	uap = (struct a *)u.u_ap;

	/*
	 *	Intercept and deal with "please trace me" request.
	 */
	if (uap->req == PTRACE_TRACEME) {
		u.u_procp->p_flag |= STRC;
		u.u_procp->p_tptr = u.u_procp->p_pptr;
		return;
	}

	/*
	 *	Locate victim, and make sure it is traceable.
	 */
	p = pfind(uap->pid);
	if (p == NULL) {
		u.u_error = ESRCH;
		return;
	}
	if (uap->req == PTRACE_ATTACH) {
		if ((u.u_uid && u.u_uid != p->p_uid) || (p->p_flag & STRC)) {
			u.u_error = EPERM;
			return;
		}
		/*
		 * Tell him we're tracing him and stop him where he is.
		 */
		p->p_flag |= STRC;
		p->p_tptr = u.u_procp;
		psignal(p, SIGSTOP);
		return;
	}
	if (p->task->user_stop_count == 0 || p->p_stat != SSTOP ||
		p->p_tptr != u.u_procp ||
	    !(p->p_flag & STRC)) {
		u.u_error = ESRCH;
		return;
	}
#ifdef sparc
	/*
	 * For sparc, the pc must be aligned to a four byte boundary.
	 * Special case: addr == 1, continue where we were.
	 */
	if ((uap->req == PTRACE_CONT) && ((int)uap->addr & 0x3) &&
	   ((int)uap->addr != 1)) {
		u.u_error = EINVAL;
		return;
	}
#endif sparc

	/*
	 *	Identify victim.
	 */
	thread = p->thread;
	pcb = thread->pcb;
	uthread = thread->u_address.uthread;
	locr0 = uthread->uu_ar0;

	u.u_r.r_val1 = 0;

	switch (uap->req) {

	case PTRACE_PEEKTEXT:
	case PTRACE_PEEKDATA:
		u.u_error = ptrace_read_data(p,
				(vm_offset_t)uap->addr,
				sizeof(int),
				(caddr_t)&u.u_r.r_val1);
		break;



	case PTRACE_POKETEXT:
	case PTRACE_POKEDATA:
		u.u_error = ptrace_write_data(p,
				(vm_offset_t)uap->addr,
				sizeof(int),
				(caddr_t)&uap->data,
				(caddr_t) 0);
		break;		
		
	case PTRACE_PEEKUSER:
		/*
		 *	Read victim's U area or registers.
		 *	Offsets are into BSD kernel stack, and must be
		 *	faked to match MACH.
		 */
		i = (int)uap->addr;
		if (i < 0 || i >= ctob(UPAGES))
			goto error;
		if (i < sizeof(struct user)) {
		    /*
		     *	We want data from the U area.  Fake it up,
		     *	then pull out the desired int.
		     */
		    struct user	fake_uarea;

		    bzero((caddr_t)&fake_uarea, sizeof(struct user));
		    fake_u(&fake_uarea, thread);
		    u.u_r.r_val1 = *(int *)PHYSOFF(&fake_uarea, i);
		}
		else {
		    /*
		     *	Assume we want data from the kernel stack, most
		     *	likely the user's registers.
		     */
		    u.u_r.r_val1 = *(int *)
		    	PHYSOFF(thread->kernel_stack
				+ (KERNEL_STACK_SIZE - ctob(UPAGES)), i);
		}
		break;

	case PTRACE_POKEUSER:
		i = (int) uap->addr;

		/*
		 *	Write one of the user's registers.
		 *	Convert the offset (in old-style Uarea/kernel stack)
		 *	into the corresponding offset into the saved
		 *	register set.
		 */
		up = (int *)PHYSOFF(thread->kernel_stack
				+ (KERNEL_STACK_SIZE - ctob(UPAGES)), i);
		for (i = 0; i < NIPCREG; i++)
			if (up == &locr0[ipcreg[i]])
				goto ok;
		if (up == &locr0[PS]) {
#if	sun4
			uap->data &= PSL_USERMASK;
#else	sun4
			uap->data |= PSL_USERSET;
			uap->data &=  ~PSL_USERCLR;
#endif	sun4
			goto ok;
		}
		goto error;

	ok:
		*up = uap->data;
		break;

	/* read registers - copy from the u area to the ipc buffer */
	case PTRACE_GETREGS:
		if (copyout((caddr_t)locr0,
			    uap->addr,
			    sizeof(struct regs)) != 0) {
			u.u_error = EIO;
		}
		break;

	/* write registers - copy from the ipc buffer to the u area */
	case PTRACE_SETREGS:
	    {
		struct regs	ip_regs;
#if	sun4
		int		oldpsr;

		oldpsr = locr0[PSR];	/* save psr for static parts */
#endif	sun4
		if (copyin(uap->addr, (caddr_t)&ip_regs,
			   sizeof(ip_regs)) != 0) {
			u.u_error = EIO;
			break;
		}
#ifdef sparc
                if ((ip_regs.r_pc & 03) || (ip_regs.r_npc & 03)) {
                        u.u_error = EINVAL;
                        break;
                }
#endif sparc
		bcopy((caddr_t)&ip_regs, (caddr_t)locr0, sizeof(struct regs));
#if	sun3
		locr0[PS] = (locr0[PS] | PSL_USERSET) &~ PSL_USERCLR;
#endif	sun3
#if	sun4
		/*
		 *	User only gets to change integer condition codes in psr
		 */
		locr0[PSR] = (oldpsr&~PSL_USERMASK) | (locr0[PS]&PSL_USERMASK);
#endif	sun4
		break;
	    }

	/*
	 * Read floating point registers -
	 * Copy from the u area to the ipc buffer,
	 * after setting the fps_flags and fps_code
	 * from the internal fpp info.
	 */
	case PTRACE_GETFPREGS:
#if	sun4
		if (copyout((caddr_t)&pcb->pcb_fpu, uap->addr,
			sizeof(pcb->pcb_fpu)) != 0) {
			u.u_error = EIO;
		}
#else	sun4
		if (fppstate == 0) {
			u.u_error = EIO;
		} else {
			pcb->pcb_fp_status.fps_flags =
				EXT_FPS_FLAGS(&pcb->pcb_fp_istate);
			pcb->pcb_fp_status.fps_code = uthread->uu_code;

			if (copyout((caddr_t)&pcb->pcb_fp_status, uap->addr,
				sizeof(pcb->pcb_fp_status)) != 0) {
				u.u_error = EIO;
			}
		}
#endif	sun4
		break;

	/*
	 * Write floating point registers -
	 * Copy from the ipc buffer to the u area,
	 * and set u.u_code from the code in fp_status,
	 * then initialize the fpp registers.
	 */
	case PTRACE_SETFPREGS:
	    {
#if	sun4
		struct fpu	ip_fpu;

		if (copyin(uap->addr, (caddr_t)&ip_fpu,
		    sizeof(ip_fpu)) != 0) {
			u.u_error = EIO;
			break;
		}
		pcb->pcb_fpu = ip_fpu;
#else	sun4
		struct fp_status	ip_fp_status;

		if (copyin(uap->addr, (caddr_t)&ip_fp_status,
		    sizeof(ip_fp_status)) != 0) {
			u.u_error = EIO;
			break;
		}
		if (fppstate == 0) {
			u.u_error = EIO;
		} else {
			pcb->pcb_fp_status = ip_fp_status;
			uthread->uu_code =
				pcb->pcb_fp_status.fps_code;
		}
#endif	sun4
		break;
	    }
#if NFPA > 0
	/* Read FPA registers from pcb to buffer and then copyout buffer */
	case PTRACE_GETFPAREGS:
	    {
		struct fpa_regs ip_fpa_regs;	/* FPA processor regs */
#define ip_fpa_flags	ip_fpa_regs.fpar_flags
#define ip_fpa_state	ip_fpa_regs.fpar_status.fpas_state
#define ip_fpa_status	ip_fpa_regs.fpar_status
#define ip_fpa_data	ip_fpa_regs.fpar_data

		if (!pcb->pcb_fpa_flags)
			goto error;
		ip_fpa_flags = pcb->pcb_fpa_flags;
		ip_fpa_status = pcb->pcb_fpa_status;
		bcopy((char *)pcb->pcb_fpa_data, (char *)ip_fpa_data,
		      sizeof (pcb->pcb_fpa_data)); /* copy from pcb */
		if (copyout((caddr_t)&ip_fpa_regs, uap->addr,
		    sizeof (ip_fpa_regs)) != 0) {
			u.u_error = EIO;
		}
		break;
	    }
	/*
	 * Write FPA registers from buffer to the pcb
	 * board.  U.u_fpa_flags, FPA STATE register, and WSTATUS register
	 * are protected from being written.
	 */
	case PTRACE_SETFPAREGS:
	    {
		struct fpa_regs ip_fpa_regs;	/* FPA processor regs */

		if (copyin(uap->addr, (caddr_t)&ip_fpa_regs,
		    sizeof (ip_fpa_regs)) != 0) {
			u.u_error = EIO;
			break;
		}
		if (!pcb->pcb_fpa_flags)
			goto error;
		/* STATE reg is protected from being modified */
		ip_fpa_state = pcb->pcb_fpa_status.fpas_state;
		pcb->pcb_fpa_status = ip_fpa_status;
		bcopy((char *)ip_fpa_data, (char *)pcb->pcb_fpa_data,
		      sizeof (pcb->pcb_fpa_data)); /* copy to fpa */
		break;
	    }
#endif NFPA > 0

	/* set signal and continue */
	/* one version causes a trace-trap */
	case PTRACE_SINGLESTEP:
	/* one version stops tracing */
#if	sun4
		goto error;
#endif	sun4
	case PTRACE_DETACH:
	case PTRACE_CONT:
		if ((int)uap->addr != 1){
			locr0[PC] = (int)uap->addr;
#ifdef sparc
			locr0[nPC] = (int)uap->addr + 4;
#endif sparc
		}

		if ((unsigned)uap->data > NSIG)
			goto error;

		if (sigmask(p->p_cursig) & threadmask)
			uthread->uu_cursig = 0;

		p->p_cursig = uap->data;	/* see issig */

		if (sigmask(uap->data) & threadmask)
			uthread->uu_cursig = uap->data;

#if	sun4
#else	sun4
		if (uap->req == PTRACE_SINGLESTEP) 
			locr0[PS] |= PSL_T;
		else
#endif	sun4
		if (uap->req == PTRACE_DETACH) {
			p->p_flag &= ~STRC;
			p->p_tptr = 0;
		}
	resume:
		p->p_stat = SRUN;
		task_resume(p->task);
		break;

	/* force exit */
	case PTRACE_KILL:
		p->p_flag &= ~STRC;
		p->p_tptr = 0;
		p->p_cursig += NSIG;
		goto resume;

	case PTRACE_READDATA:
	case PTRACE_READTEXT:
		/**/ {
		vm_offset_t	my_page;

		my_page = kmem_alloc_pageable(kernel_pageable_map, PAGE_SIZE);
		while (uap->data > 0) {
			vm_size_t	size = uap->data;

			if (size > PAGE_SIZE)
				size = PAGE_SIZE;

			u.u_error = ptrace_read_data(p,
					(vm_offset_t)uap->addr,
					size,
					(caddr_t) my_page);

			if (u.u_error)
				break;

			if (copyout((caddr_t) my_page,
					uap->addr2,
					size) != 0) {
				u.u_error = EFAULT;
				break;
			}

			uap->addr  += size;
			uap->data  -= size;
			uap->addr2 += size;
		}
		kmem_free(kernel_pageable_map, my_page, PAGE_SIZE);
		/**/ }
		break;		
		
	case PTRACE_WRITEDATA:
	case PTRACE_WRITETEXT:
		/**/ {
		vm_offset_t	my_page;

		my_page = kmem_alloc_pageable(kernel_pageable_map, PAGE_SIZE);
		while (uap->data > 0) {
			vm_size_t		size = uap->data;

			if (size > PAGE_SIZE)
				size = PAGE_SIZE;

			if (copyin(uap->addr2, (caddr_t) my_page,
					size) != 0) {
				u.u_error = EFAULT;
				break;
			}
			u.u_error = ptrace_write_data(p,
					(vm_offset_t)uap->addr,
					size,
					(caddr_t) my_page,
					(caddr_t) 0);

			if (u.u_error)
				break;

			
			uap->addr  += size;
			uap->data  -= size;
			uap->addr2 += size;
		}
		kmem_free(kernel_pageable_map, my_page, PAGE_SIZE);
		/**/ }
		break;		
		
	default:
	error:
		u.u_error = EIO;
	}
}

