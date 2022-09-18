/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	genassym.c,v $
 * Revision 2.6  89/03/09  21:33:07  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/03/07  20:45:01  rpd
 * 	Doesn't need vmmeter.h.
 * 
 * Revision 2.4  89/02/25  19:34:17  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 *  8-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Eliminate a lot of unused symbols.
 *
 * 27-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Need to know KERNEL_STACK_SIZE to setup "init"'s stack.
 *	Need more offsets for new pmap module.
 *
 * 26-Jan-88  Douglas Orr (dorr) at Carnegie-Mellon University
 *	Added symbols for user space emulation library.
 *
 * 11-Nov-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added defines for FPA.
 *
 * 20-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added symbols for profiling buffer, for addupc.
 *
 *  6-Oct-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized TRACE_KDB and KDB_STEP on CS_KDB.
 *
 * 29-Jun-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added no cache bit to definitions of pme's for the eeprom,
 *	clock, memory error register, interrupt control register and
 *	ecc registers.
 *	Conditionalize use of TRACE_KDB and KDB_STEP on CS_KDB.
 *
 * 28-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added support for MACH.
 *
 *  6-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Replaced occurences of "romp" with "sunromp" to avoid 
 *	name conflict with IBM PC RT.
 *	Added definition of "PCB_FLAG" and "THREAD_RECOVER".
 *
 * 28-Jul-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to generate new definitions for Mach to use
 *	in save_context() and load_context().
 *
 */
#ifndef	lint
static  char sccsid[] = "@(#)genassym.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <mach_kdb.h>
#include <mach_emulation.h>
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/vmparam.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/cmap.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>
#include <sys/vmmac.h>

#include <sun3/psl.h>
#include <sun3/mmu.h>
#include <sun3/cpu.h>
#include <sun3/scb.h>
#include <sun3/clock.h>
#include <sun3/memerr.h>
#include <sun3/interreg.h>
#include <sun3/eeprom.h>
#include <sun3/eccreg.h>

#include <sundev/zscom.h>
#include <fpa.h>
#if	NFPA > 0
#include <sundev/fpareg.h>
#endif	NFPA > 0
#include <sun3/pmap.h>
#include <kern/thread.h>

thread_t	active_threads[1];
thread_t	fp_threads[1];
#if	MACH_EMULATION
#include <kern/syscall_emulation.h>
#endif	MACH_EMULATION

struct zsops *zs_proto[] = { 0 };


main()
{
	register struct regs *rp = (struct regs *)0;
	register struct context *ctx = (struct context *)0;
	register struct zscom *zs = (struct zscom *)0;
#ifdef	NFPA >0
	struct fpa_device *fpap = (struct fpa_device *)0;
#endif	NFPA
	struct pcb	*pcb = (struct pcb *)0;
	struct pmap	*pmap = (struct pmap *)0;
	struct task	*task = (struct task *)0;
	struct thread	*thread = (struct thread *)0;
	struct vm_map	*vm_map = (struct vm_map *)0;
#if	MACH_EMULATION
	struct eml_dispatch *disp = (struct eml_dispatch *)0;
#endif	MACH_EMULATION
	struct uuprof *uprof = (struct uuprof *)0;

	printf("#define\tSLOAD 0x%x\n", SLOAD);
	printf("#undef\tKERNEL_STACK_SIZE\n");
	printf("#define\tKERNEL_STACK_SIZE 0x%x\n", KERNEL_STACK_SIZE);
	printf("#define\tR_SP 0x%x\n", &rp->r_sp);
	printf("#define\tR_PC 0x%x\n", &rp->r_pc);
#if	MACH_EMULATION
	printf("#define\tR_D0 0x%x\n", &rp->r_dreg[0]);
	printf("#define\tR_D1 0x%x\n", &rp->r_dreg[1]);
#endif	MACH_EMULATION
	printf("#define\tR_SR 0x%x\n", ((int)&rp->r_sr) + sizeof (short));
	printf("#define\tR_VOR 0x%x\n", ((int)&rp->r_pc) + sizeof (int));
	printf("#define\tPCB_REGS 0x%x\n", &pcb->pcb_regs);
	printf("#define\tPCB_A2 0x%x\n", &pcb->pcb_regs.r_areg[2]);
	printf("#define\tPCB_D2 0x%x\n", &pcb->pcb_regs.r_dreg[2]);
	printf("#define\tPCB_KSP 0x%x\n", &pcb->pcb_regs.r_areg[7]);
	printf("#define\tPCB_PC 0x%x\n", &pcb->pcb_regs.r_pc);
	printf("#define\tPCB_SR 0x%x\n", &pcb->pcb_regs.r_sr);
	printf("#define\tPCB_FP_ISTATE 0x%x\n", &pcb->pcb_fp_istate);
	printf("#define\tPCB_FPS_REGS 0x%x\n", pcb->pcb_fp_status.fps_regs);
	printf("#define\tPCB_FPS_CTRL 0x%x\n", &pcb->pcb_fp_status.fps_control);
	printf("#define\tPCB_FLAG 0x%x\n", &pcb->pcb_flag);
#if	MACH_KDB
	printf("#define\tTRACE_KDB_BIT %d\n", bit(TRACE_KDB));
	printf("#define\tKDB_STEP_BIT %d\n", bit(KDB_STEP));
#endif	MACH_KDB
#if	NFPA > 0
	printf("#define\tPCB_FPA_FLAGS 0x%x\n", &pcb->pcb_fpa_flags);
	printf("#define\tPCB_FPA_STATUS 0x%x\n", &pcb->pcb_fpa_status);
	printf("#define\tPCB_FPA_FMTPTR 0x%x\n", &pcb->pcb_fpa_fmtptr);
	printf("#define\tPCB_FPA_PC 0x%x\n", &pcb->pcb_fpa_pc);
	printf("#define\tR_KSTK 0x%x\n", sizeof (struct regs) + sizeof (short));
	printf("#define\tFPA_PIPE_STATUS 0x%x\n", &fpap->fp_pipe_status);
	printf("#define\tFPA_STATE 0x%x\n", &fpap->fp_state);
	printf("#define\tFPA_STABLE 0x%x\n", FPA_STABLE);
	printf("#define\tNOAST_BITS 0x%x\n", ~AST_CLR);
#endif	NFPA > 0
	printf("#define\tAST_SCHED_BIT %d\n", bit(AST_SCHED));
	printf("#define\tAST_STEP_BIT %d\n", bit(AST_STEP));
	printf("#define\tTRACE_USER_BIT %d\n", bit(TRACE_USER));
	printf("#define\tTRACE_AST_BIT %d\n", bit(TRACE_AST));
	printf("#define\tSR_SMODE_BIT %d\n", bit(SR_SMODE));
	printf("#define\tSR_TRACE_BIT %d\n", bit(SR_TRACE));
	printf("#define\tIR_SOFT_INT1_BIT %d\n", bit(IR_SOFT_INT1));
	printf("#define\tIR_SOFT_INT2_BIT %d\n", bit(IR_SOFT_INT2));
	printf("#define\tIR_SOFT_INT3_BIT %d\n", bit(IR_SOFT_INT3));

	printf("#define\tZSSIZE 0x%x\n", sizeof (struct zscom));
	printf("#define\tZS_ADDR 0x%x\n", &zs->zs_addr);
	printf("#define\tCTX_CONTEXT 0x%x\n", &ctx->num);
	printf("#define\tEEPROM_ADDR_MAPVAL 0x%x\n",
	    ((int)EEPROM_ADDR & PAGEADDRBITS) | PAGEBASE);
	printf("#define\tEEPROM_ADDR_PTE 0x%x\n",
	    PG_V | PG_KW | PG_NC | PGT_OBIO | btop(OBIO_EEPROM_ADDR));
	printf("#define\tCLKADDR_MAPVAL 0x%x\n",
	    ((int)CLKADDR & PAGEADDRBITS) | PAGEBASE);
	printf("#define\tCLKADDR_PTE 0x%x\n",
	    PG_V | PG_KW | PG_NC | PGT_OBIO | btop(OBIO_CLKADDR));
	printf("#define\tMEMREG_MAPVAL 0x%x\n",
	    ((int)MEMREG & PAGEADDRBITS) | PAGEBASE);
	printf("#define\tMEMREG_PTE 0x%x\n",
	    PG_V | PG_KW | PG_NC | PGT_OBIO | btop(OBIO_MEMREG));
	printf("#define\tINTERREG_MAPVAL 0x%x\n",
	    ((int)INTERREG & PAGEADDRBITS) | PAGEBASE);
	printf("#define\tINTERREG_PTE 0x%x\n",
	    PG_V | PG_KW | PG_NC | PGT_OBIO | btop(OBIO_INTERREG));
	printf("#define\tECCREG_MAPVAL 0x%x\n",
	    ((int)ECCREG & PAGEADDRBITS) | PAGEBASE);
	printf("#define\tECCREG_PTE 0x%x\n",
	    PG_V | PG_KW | PG_NC | PGT_OBIO | btop(OBIO_ECCREG));
	printf("#define\tSCBSIZE 0x%x\n", sizeof (struct scb));
	printf("#define\tROMP_PRINTF 0x%x\n", &sunromp->v_printf);
	printf("#define\tROMP_ROMVEC_VERSION 0x%x\n", &sunromp->v_romvec_version);
	printf("#define\tROMP_MEMORYBITMAP 0x%x\n", &sunromp->v_memorybitmap);
	printf("#define\tTASK_MAP 0x%x\n", &task->map);
#if	MACH_EMULATION
	printf("#define\tEML_DISPATCH 0x%x\n", &task->eml_dispatch);
	printf("#define\tDISP_COUNT 0x%x\n", &disp->disp_count);
	printf("#define\tDISP_VECTOR 0x%x\n", disp->disp_vector);
#endif	MACH_EMULATION
	printf("#define\tTHREAD_PCB 0x%x\n", &thread->pcb);
	printf("#define\tTHREAD_RECOVER 0x%x\n", &thread->recover);
	printf("#define\tTHREAD_TASK 0x%x\n", &thread->task);
	printf("#define\tVM_MAP_PMAP 0x%x\n", &vm_map->pmap);
	printf("#define\tPMAP_CTX 0x%x\n", &pmap->context);
	printf("#define\tPR_BASE %d\n", &uprof->pr_base);
	printf("#define\tPR_SIZE %d\n", &uprof->pr_size);
	printf("#define\tPR_OFF %d\n", &uprof->pr_off);
	printf("#define\tPR_SCALE %d\n", &uprof->pr_scale);
	exit(0);
}

bit(mask)
	register long mask;
{
	register int i;

	for (i = 0; i < 32; i++) {
		if (mask & 1)
			return (i);
		mask >>= 1;
	}
	exit (1);
}
