/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	genassym.c,v $
 * Revision 1.4.1.3  91/03/28  08:43:49  rvb
 * 	Flush THREAD_EXIT & THREAD_EXIT_CODE for X134.
 * 	[91/03/23            rvb]
 * 
 * Revision 1.4.1.2  90/02/09  17:23:20  rvb
 * 	Constants for Mach emulation support.
 * 	[90/02/09            rvb]
 * 
 * Revision 1.4.1.1  90/01/02  13:50:28  rvb
 * 	Flush MACH_TIME.
 * 
 * Revision 1.4  89/04/05  12:57:30  rvb
 * 	X78: no more vmmeter
 * 	[89/03/24            rvb]
 * 
 * Revision 1.3  89/02/26  12:31:18  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *	Still a lot of dead wood to cleanup.
 *
 * 11-Dec-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	For 650, define ssc timer symbolic offsets.
 *
 */

#include <confdep.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)genassym.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/buf.h>
#include <sys/vmparam.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>

#include <kern/thread.h>
#include <kern/task.h>
#include <machine/pcb.h>

#if	MACH_EMULATION
#include <kern/syscall_emulation.h>
#endif	MACH_EMULATION

thread_t	active_threads[1];

main()
{
	register struct proc *p = (struct proc *)0;
	register struct utask *utask = (struct utask *)0;
	register struct uthread *uthread = (struct uthread *)0;
	register struct pcb *pcb = (struct pcb *)0;
	register struct rusage *rup = (struct rusage *)0;
	struct rpb *rp = (struct rpb *)0;
	struct thread *thread = (struct thread *) 0;
	struct task *task = (struct task *) 0;
	struct uuprof *uprof = (struct uuprof *)0;
#if	MACH_EMULATION
	struct eml_dispatch *disp = (struct eml_dispatch *)0;
#endif	MACH_EMULATION

	printf("#ifdef LOCORE\n");
	printf("#define\tP_LINK %d\n", &p->p_link);
	printf("#define\tP_RLINK %d\n", &p->p_rlink);
	printf("#define\tP_PRI %d\n", &p->p_pri);
	printf("#define\tP_STAT %d\n", &p->p_stat);
	printf("#define\tP_CURSIG %d\n", &p->p_cursig);
	printf("#define\tP_SIG %d\n", &p->p_sig);
	printf("#define\tP_FLAG %d\n", &p->p_flag);
	printf("#define\tSSLEEP %d\n", SSLEEP);
	printf("#define\tSRUN %d\n", SRUN);
	printf("#define\tUPAGES %d\n", UPAGES);
	printf("#define\tU_PROCP %d\n", &utask->uu_procp);
	printf("#define\tU_RU %d\n", &utask->uu_ru);
	printf("#define\tRU_MINFLT %d\n", &rup->ru_minflt);
	printf("#define\tPR_BASE %d\n", &uprof->pr_base);
	printf("#define\tPR_SIZE %d\n", &uprof->pr_size);
	printf("#define\tPR_OFF %d\n", &uprof->pr_off);
	printf("#define\tPR_SCALE %d\n", &uprof->pr_scale);
	printf("#define\tU_ERROR %d\n", &uthread->uu_error);
	printf("#define\tU_AR0 %d\n", &uthread->uu_ar0);
	printf("#define\tpcb_fpvalid %d\n", &pcb->pcb_fpvalid);
	printf("#define\tpcb_fps %d\n", &pcb->pcb_fps);
	printf("#define\tUSER_FP 0x%x\n", USER_FP);
	printf("#define\tKDSSEL 0x%x\n", KDSSEL);
	printf("#define\tKTSSSEL 0x%x\n", KTSSSEL);
	printf("#define\tJTSSSEL 0x%x\n", JTSSSEL);
	printf("#define\tTHREAD_PCB %d\n", &thread->pcb);
	printf("#define\tTHREAD_RECOVER %d\n", &thread->recover);
	printf("#define\tTHREAD_TASK %d\n", &thread->task);
#ifdef	THREAD_EXIT
	printf("#define\tTHREAD_EXIT_CODE %d\n", &thread->exit_code);
 	printf("#define\tTHREAD_EXIT %d\n", THREAD_EXIT);
#endif	THREAD_EXIT
	printf("#define\tUTHREAD %d\n", &thread->u_address.uthread);
	printf("#define\tUTASK %d\n", &thread->u_address.utask);
#if	MACH_EMULATION
	printf("#define\tEML_DISPATCH 0x%x\n", &task->eml_dispatch);
	printf("#define\tDISP_COUNT 0x%x\n", &disp->disp_count);
	printf("#define\tDISP_VECTOR 0x%x\n", &disp->disp_vector[0]);
#endif	MACH_EMULATION
	printf("#else\n");
	printf("asm(\".set\tU_ARG,%d\");\n", uthread->uu_arg);
	printf("asm(\".set\tU_QSAVE,%d\");\n", &uthread->uu_qsave);
	printf("#endif\n");
	exit(0);
}
