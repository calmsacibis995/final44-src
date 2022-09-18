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
 * Revision 2.8  89/03/09  04:50:05  rpd
 * 	More cleanup.  Ripped out MACH_TIME.
 * 
 * Revision 2.7  89/02/25  20:18:57  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  88/12/19  02:53:45  mwyoung
 * 	Remove lint; fix include file references.
 * 
 * 29-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Merged in MACH_EMULATION symbols.
 *
 * 14-Apr-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added THREAD_KERNEL_STACK.
 *
 *  8-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Eliminated lots of unused fields.
 *
 * 11-Dec-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	For 650, define ssc timer symbolic offsets.
 *
 *  8-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added THREAD_EXIT_CODE and THREAD_EXIT for new thread termination
 *	logic.
 *
 * 26-Oct-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	Changes for 650.
 *
 * 20-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added symbols for profiling buffer, for addupc.
 *
 *  2-Jun-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed U_QSAVE and U_EOSYS (no longer used).  Changed UTASK
 *	to refer to thread->uaddress.utask.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	No P_WCHAN for MACH.
 *
 *  1-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added THREAD_TASK.
 *
 * 31-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Conditionalized several symbols under not MACH.
 *
 * 29-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed INCLUDE_VERSION.  locore.s include version.h directly.
 *
 * 01-Oct-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added include of "confdep.h"
 *
 * 11-Aug-86  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added u_ar0.
 *
 * 24-Jul-86  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added u_comm offset.
 *
 * 10-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added INCLUDE_VERSION.
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 *  2-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed the "#define KERNEL" since the real way to do this is
 *	via the Makefile.  No appropriate ifdef's apply, so I just
 *	deleted the line.
 *
 * 2-Aug-85	David L. Black at CMU.  Added stuff for user timing;
 *	offsets into timeval and timerec structures, sizes of proc
 *	and uproc structures.
 *
 * 13-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added some stuff for ultrix.
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)genassym.c	7.1 (Berkeley) 6/5/86
 */

#include <confdep.h>
#include <mach_emulation.h>

#include <vax/pte.h>

#include <sys/param.h>
#include <sys/buf.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/map.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>
#include <sys/proc.h>
#include <vax/rpb.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>

struct uba_hd uba_hd[1];

#include <kern/thread.h>
#include <kern/task.h>

thread_t	active_threads[1];
struct percpu	percpu[1];

#if	MACH_EMULATION
#include <kern/syscall_emulation.h>
#endif	MACH_EMULATION

#if	VAX650
#include <vax/ka650.h>
#endif	VAX650

#if	VAX650 || VAX6200
#include <vax/clock.h>
#endif	VAX650 || VAX6200
main()
{
	register struct proc *p = (struct proc *)0;
	register struct uba_regs *uba = (struct uba_regs *)0;
	register struct uba_hd *uh = (struct uba_hd *)0;
	register struct utask *utask = (struct utask *)0;
	register struct uthread *uthread = (struct uthread *)0;
	register struct rusage *rup = (struct rusage *)0;
	struct rpb *rp = (struct rpb *)0;
	struct thread *thread = (struct thread *) 0;
	struct task *task = (struct task *) 0;
	struct uuprof *uprof = (struct uuprof *)0;
#if	VAX650 || VAX6200
	struct ssclock *ssclock = (struct ssclock *)0;
#endif	VAX650 || VAX6200
#if	MACH_EMULATION
	struct eml_dispatch *disp = (struct eml_dispatch *)0;
#endif	MACH_EMULATION

	printf("#ifdef LOCORE\n");
	printf("#define\tP_CURSIG %d\n", &p->p_cursig);
	printf("#define\tP_SIG %d\n", &p->p_sig);
	printf("#define\tP_FLAG %d\n", &p->p_flag);
	printf("#define\tUBA_BRRVR %d\n", uba->uba_brrvr);
	printf("#define\tUH_UBA %d\n", &uh->uh_uba);
	printf("#define\tUH_VEC %d\n", &uh->uh_vec);
	printf("#define\tUH_SIZE %d\n", sizeof (struct uba_hd));
	printf("#define\tRP_FLAG %d\n", &rp->rp_flag);
	printf("#define\tU_PROCP %d\n", &utask->uu_procp);
	printf("#define\tU_RU %d\n", &utask->uu_ru);
	printf("#define\tRU_MINFLT %d\n", &rup->ru_minflt);
	printf("#define\tPR_BASE %d\n", &uprof->pr_base);
	printf("#define\tPR_SIZE %d\n", &uprof->pr_size);
	printf("#define\tPR_OFF %d\n", &uprof->pr_off);
	printf("#define\tPR_SCALE %d\n", &uprof->pr_scale);
	printf("#define\tU_ERROR %d\n", &uthread->uu_error);
	printf("#define\tU_AR0 %d\n", &uthread->uu_ar0);
	printf("#define\tTHREAD_PCB %d\n", &thread->pcb);
	printf("#define\tTHREAD_RECOVER %d\n", &thread->recover);
	printf("#define\tTHREAD_TASK %d\n", &thread->task);
	printf("#define\tTHREAD_EXIT_CODE %d\n", &thread->exit_code);
	printf("#define\tTHREAD_EXIT %d\n", THREAD_EXIT);
	printf("#define\tTHREAD_KERNEL_STACK %d\n", &thread->kernel_stack);
	printf("#define\tUTHREAD %d\n", &thread->u_address.uthread);
	printf("#define\tUTASK %d\n", &thread->u_address.utask);
#if	MACH_EMULATION
	printf("#define\tEML_DISPATCH 0x%x\n", &task->eml_dispatch);
	printf("#define\tDISP_COUNT 0x%x\n", &disp->disp_count);
	printf("#define\tDISP_VECTOR 0x%x\n", disp->disp_vector);
#endif	MACH_EMULATION
#if	VAX650 || VAX6200
	printf("#define\tSSC_TCR0 %d\n", &ssclock->ssc_tcr0);
#endif	VAX650 || VAX6200
	printf("#else\n");
	printf("asm(\".set\tU_ARG,%d\");\n", uthread->uu_arg);
	printf("asm(\".set\tU_QSAVE,%d\");\n", &uthread->uu_qsave);
	printf("#endif\n");
}
