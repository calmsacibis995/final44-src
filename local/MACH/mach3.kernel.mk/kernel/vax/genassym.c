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
 * $Log:	genassym.c,v $
 * Revision 2.6  93/02/01  09:52:12  danner
 * 	Add symbols from boot_info.
 * 	[93/01/27            dbg]
 * 
 * Revision 2.5  92/01/03  20:32:45  dbg
 * 	Remove fixed lower bound on emulated system calls.
 * 	[91/11/01            dbg]
 * 
 * Revision 2.4  91/06/20  11:30:28  rvb
 * 	funny thing: before you could not build STD+BI because ka650.h was necessary to define ssc
 * 
 * Revision 2.3  91/05/08  13:17:19  dbg
 * 	Changes for kernel stack switching.
 * 	Undefine 'volatile'.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.2  90/06/02  15:08:12  rpd
 * 	Removed include of confdep.h.
 * 	[90/03/26  23:03:48  rpd]
 * 
 * Revision 2.1  89/08/03  16:18:49  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Rewrote for MACH kernel.  Eliminated old history.
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)genassym.c	7.1 (Berkeley) 6/5/86
 */

/*
 * This may be built with pre-ANSI compilers.
 */
#define	volatile

#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>
#include <vax/rpb.h>

/*
 * Provide external variable definitions.
 */
struct uba_hd uba_hd[1];
struct dev_ops dev_name_list[1];
int	dev_name_count;

#include <kern/thread.h>
#include <kern/task.h>
#include <kern/syscall_emulation.h>
#include <mach/vm_prot.h>
#include <mach/boot_info.h>

#if	VAX650
#include <vax/ka650.h>
#endif	/* VAX650 */
#if	VAX6200
#include <vax/ka6200.h>
#include <vax/cca.h>
#endif	/* VAX6200 */

main()
{
	register struct uba_regs *uba = (struct uba_regs *)0;
	register struct uba_hd *uh = (struct uba_hd *)0;
	struct rpb *rp = (struct rpb *)0;
	struct thread *thread = (struct thread *) 0;
	struct task *task = (struct task *) 0;
	struct eml_dispatch *eml = (struct eml_dispatch *)0;
	struct vax_saved_state *vss = (struct vax_saved_state *)0;
	struct vax_kernel_state *vks = (struct vax_kernel_state *)0;
	struct vax_pcb *pcb = (struct vax_pcb *)0;
	struct boot_info *bi = (struct boot_info *)0;
#if	VAX650
	struct ka650_ssc *ka650_ssc = (struct ka650_ssc *)0;
#endif	/* VAX650 */
#if	VAX6200
	struct ka62a_ssc *ka62a_ssc = (struct ka62a_ssc *)0;
	struct cca *cca = (struct cca *)0;
#endif	/* VAX6200 */

	printf("#define\tUBA_BRRVR %d\n", uba->uba_brrvr);
	printf("#define\tUH_UBA %d\n", &uh->uh_uba);
	printf("#define\tUH_VEC %d\n", &uh->uh_vec);
	printf("#define\tUH_SIZE %d\n", sizeof (struct uba_hd));

	printf("#define\tRP_FLAG %d\n", &rp->rp_flag);

	printf("#define\tTHREAD_PCB %d\n", &thread->pcb);
	printf("#define\tTHREAD_TASK %d\n", &thread->task);
	printf("#define\tTHREAD_KERNEL_STACK %d\n", &thread->kernel_stack);
	printf("#define\tTH_SWAP_FUNC %d\n", &thread->swap_func);

	printf("#define\tPCB_VKS %d\n", &pcb->vks_p);
	printf("#define\tPCB_VUSP %d\n", &pcb->v_usp);

	printf("#define\tVKS_ARGLIST %d\n", &vks->arg_count);

	printf("#define\tR_R2 %d\n", &vss->r2);
	printf("#define\tR_EXC %d\n", &vss->exception);
	printf("#define\tR_CODE %d\n", &vss->code);
	printf("#define\tR_SUBCODE %d\n", &vss->subcode);
	printf("#define\tR_PC %d\n", &vss->pc);
	printf("#define\tR_PSL %d\n", &vss->psl);

	printf("#define\tVM_PROT_READ %d\n", VM_PROT_READ);
	printf("#define\tVM_PROT_WRITE %d\n", VM_PROT_WRITE);

	printf("#define\tEML_DISPATCH %d\n", &task->eml_dispatch);
	printf("#define\tDISP_MIN %d\n", &eml->disp_min);
	printf("#define\tDISP_COUNT %d\n", &eml->disp_count);
	printf("#define\tDISP_VECTOR %d\n", &eml->disp_vector[0]);

	printf("#define\tBI_SYM_SIZE %d\n", &bi->sym_size);
	printf("#define\tBI_BOOT_SIZE %d\n", &bi->boot_size);
	printf("#define\tBI_LOAD_INFO_SIZE %d\n", &bi->load_info_size);
	printf("#define\tBI_SIZE %d\n", sizeof(*bi));

#if	VAX650
	printf("#define\tSSC_TCR0 %d\n", &ka650_ssc->ssc_tcr0);
#endif	/* VAX650 */
#if	VAX6200
#if	!VAX650
	printf("#define\tSSC_TCR0 %d\n", &ka62a_ssc->ssc_tcr0);
#endif	/* !VAX650 */
	printf("#define\tCCA_BITMAP_SZ %d\n", &cca->bitmap_sz);
	printf("#define\tCCA_BITMAP %d\n", &cca->bitmap);
#endif	/* VAX6200 */
}
