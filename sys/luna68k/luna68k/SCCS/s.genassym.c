h63587
s 00001/00001/00186
d D 8.3 93/12/06 20:19:52 akito 9 8
c sync up to hp300/hp300/genassym.c       8.2 (Berkeley) 9/23/93
e
s 00003/00003/00184
d D 8.2 93/09/23 16:42:53 bostic 8 7
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00185
d D 8.1 93/06/10 22:26:05 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00186
d D 7.6 93/03/17 11:10:28 akito 6 5
c header update
e
s 00003/00002/00184
d D 7.5 93/01/18 19:16:49 akito 5 4
c add KIFF_SIZE macro
e
s 00007/00003/00179
d D 7.4 93/01/02 13:45:17 akito 4 3
c sync up to hp300/hp300/genassym.c       7.13
e
s 00019/00017/00163
d D 7.3 92/10/11 11:07:48 bostic 3 2
c make kernel includes standard
e
s 00137/00121/00043
d D 7.2 92/07/23 16:01:28 fujita 2 1
c update for 4.4BSD-alpha distribution
e
s 00164/00000/00000
d D 7.1 92/06/15 06:38:36 fujita 1 0
c date and time created 92/06/15 06:38:36 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 7
 * Copyright (c) 1982, 1990, 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1982, 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 *
D 4
 * OMRON: $Id: genassym.c,v 1.2 92/06/14 06:15:25 moti Exp $
E 4
I 4
D 6
 * from: hp300/hp300/genassym.c	7.13 (Berkeley) 12/27/92
E 6
I 6
D 9
 * from: hp300/hp300/genassym.c	7.14 (Berkeley) 12/30/92
E 9
I 9
 * from: hp300/hp300/genassym.c	8.2 (Berkeley) 9/23/93
E 9
E 6
E 4
 *
D 2
 * from: hp300/hp300/genassym.c	7.9 (Berkeley) 8/29/91
E 2
I 2
D 4
 * from: hp300/hp300/genassym.c	7.11 (Berkeley) 7/8/92
E 2
 *
E 4
 *	%W% (Berkeley) %G%
 */

#define KERNEL

D 3
#include "sys/param.h"
#include "sys/buf.h"
#include "sys/map.h"
#include "sys/proc.h"
#include "sys/mbuf.h"
#include "sys/msgbuf.h"
#include "../include/cpu.h"
#include "../include/trap.h"
#include "../include/psl.h"
#include "../include/reg.h"
#include "../include/stinger.h"
#include "../dev/pioreg.h"
#include "clockreg.h"
#include "sys/syscall.h"
#include "vm/vm.h"
#include "sys/user.h"
#include "pte.h"
E 3
I 3
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>
#include <sys/syscall.h>
#include <sys/user.h>

#include <machine/cpu.h>
#include <machine/trap.h>
#include <machine/psl.h>
#include <machine/reg.h>
#include <machine/stinger.h>

#include <luna68k/dev/pioreg.h>
#include <luna68k/luna68k/clockreg.h>
#include <vm/vm.h>
#include <luna68k/luna68k/pte.h>
E 3

I 2
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

extern int errno;

void
def(what, val)
	char *what;
	int val;
{

	if (printf("#define\t%s\t%d\n", what, val) < 0) {
		(void)fprintf(stderr, "genassym: printf: %s\n",
		    strerror(errno));
		exit(1);
	}
}

void
flush()
{

	if (fflush(stdout) || fsync(fileno(stdout)) < 0) {
		(void)fprintf(stderr, "genassym: flush stdout: %s\n",
		    strerror(errno));
		exit(1);
	}
}

#define	off(what, s, m)	def(what, (int)offsetof(s, m))

E 2
main()
{
D 2
	register struct proc *p = (struct proc *)0;
	register struct vmmeter *vm = (struct vmmeter *)0;
	register struct user *up = (struct user *)0;
	register struct rusage *rup = (struct rusage *)0;
	struct vmspace *vms = (struct vmspace *)0;
	pmap_t pmap = (pmap_t)0;
	struct pcb *pcb = (struct pcb *)0;
E 2
D 5
	struct KernInter *KernInter = (struct KernInter *)0;
E 5
	struct pio *pio = (struct pio *)PIO0_ADDR;
	register unsigned i;

D 2
	printf("#define\tP_LINK %d\n", &p->p_link);
	printf("#define\tP_RLINK %d\n", &p->p_rlink);
	printf("#define\tP_VMSPACE %d\n", &p->p_vmspace);
	printf("#define\tVM_PMAP %d\n", &vms->vm_pmap);
	printf("#define\tPM_STCHG %d\n", &pmap->pm_stchanged);
	printf("#define\tP_ADDR %d\n", &p->p_addr);
	printf("#define\tP_PRI %d\n", &p->p_pri);
	printf("#define\tP_STAT %d\n", &p->p_stat);
	printf("#define\tP_WCHAN %d\n", &p->p_wchan);
	printf("#define\tP_FLAG %d\n", &p->p_flag);
	printf("#define\tSSLEEP %d\n", SSLEEP);
	printf("#define\tSRUN %d\n", SRUN);
	printf("#define\tV_SWTCH %d\n", &vm->v_swtch);
	printf("#define\tV_TRAP %d\n", &vm->v_trap);
	printf("#define\tV_SYSCALL %d\n", &vm->v_syscall);
	printf("#define\tV_INTR %d\n", &vm->v_intr);
	printf("#define\tV_SOFT %d\n", &vm->v_soft);
	printf("#define\tV_FAULTS %d\n", &vm->v_faults);
	printf("#define\tKI_MAXADDR %d\n", &KernInter->maxaddr);
	printf("#define\tUPAGES %d\n", UPAGES);
	printf("#define\tHIGHPAGES %d\n", HIGHPAGES);
	printf("#define\tP1PAGES %d\n", P1PAGES);
	printf("#define\tCLSIZE %d\n", CLSIZE);
	printf("#define\tNBPG %d\n", NBPG);
	printf("#define\tNPTEPG %d\n", NPTEPG);
	printf("#define\tPGSHIFT %d\n", PGSHIFT);
	printf("#define\tSYSPTSIZE %d\n", SYSPTSIZE);
	printf("#define\tUSRPTSIZE %d\n", USRPTSIZE);
	printf("#define\tUSRIOSIZE %d\n", USRIOSIZE);
#ifdef SYSVSHM
	printf("#define\tSHMMAXPGS %d\n", SHMMAXPGS);
#endif
	printf("#define\tUSRSTACK %d\n", USRSTACK);
	printf("#define\tKERNELSTACK %d\n", KERNELSTACK);
	printf("#define\tMSGBUFPTECNT %d\n", btoc(sizeof (struct msgbuf)));
	printf("#define\tNMBCLUSTERS %d\n", NMBCLUSTERS);
	printf("#define\tMCLBYTES %d\n", MCLBYTES);
	printf("#define\tNKMEMCLUSTERS %d\n", NKMEMCLUSTERS);
	printf("#define\tU_PROF %d\n", &up->u_stats.p_prof);
	printf("#define\tU_PROFSCALE %d\n", &up->u_stats.p_prof.pr_scale);
	printf("#define\tRU_MINFLT %d\n", &rup->ru_minflt);
	printf("#define\tT_BUSERR %d\n", T_BUSERR);
	printf("#define\tT_ADDRERR %d\n", T_ADDRERR);
	printf("#define\tT_ILLINST %d\n", T_ILLINST);
	printf("#define\tT_ZERODIV %d\n", T_ZERODIV);
	printf("#define\tT_CHKINST %d\n", T_CHKINST);
	printf("#define\tT_TRAPVINST %d\n", T_TRAPVINST);
	printf("#define\tT_PRIVINST %d\n", T_PRIVINST);
	printf("#define\tT_TRACE %d\n", T_TRACE);
	printf("#define\tT_MMUFLT %d\n", T_MMUFLT);
	printf("#define\tT_SSIR %d\n", T_SSIR);
	printf("#define\tT_FMTERR %d\n", T_FMTERR);
	printf("#define\tT_COPERR %d\n", T_COPERR);
	printf("#define\tT_FPERR %d\n", T_FPERR);
	printf("#define\tT_ASTFLT %d\n", T_ASTFLT);
	printf("#define\tT_TRAP15 %d\n", T_TRAP15);
	printf("#define\tT_FPEMULI %d\n", T_FPEMULI);
	printf("#define\tT_FPEMULD %d\n", T_FPEMULD);
	printf("#define\tPSL_S %d\n", PSL_S);
	printf("#define\tPSL_IPL7 %d\n", PSL_IPL7);
	printf("#define\tPSL_LOWIPL %d\n", PSL_LOWIPL);
	printf("#define\tPSL_HIGHIPL %d\n", PSL_HIGHIPL);
	printf("#define\tPSL_USER %d\n", PSL_USER);
	printf("#define\tSPL1 %d\n", PSL_S | PSL_IPL1);
	printf("#define\tSPL2 %d\n", PSL_S | PSL_IPL2);
	printf("#define\tSPL3 %d\n", PSL_S | PSL_IPL3);
	printf("#define\tSPL4 %d\n", PSL_S | PSL_IPL4);
	printf("#define\tSPL5 %d\n", PSL_S | PSL_IPL5);
	printf("#define\tSPL6 %d\n", PSL_S | PSL_IPL6);
	printf("#define\tFC_USERD %d\n", FC_USERD);
	printf("#define\tFC_PURGE %d\n", FC_PURGE);
	printf("#define\tCACHE_ON %d\n", CACHE_ON);
	printf("#define\tCACHE_OFF %d\n", CACHE_OFF);
	printf("#define\tCACHE_CLR %d\n", CACHE_CLR);
	printf("#define\tIC_CLEAR %d\n", IC_CLEAR);
	printf("#define\tDC_CLEAR %d\n", DC_CLEAR);
	printf("#define\tPG_V %d\n", PG_V);
	printf("#define\tPG_NV %d\n", PG_NV);
	printf("#define\tPG_RO %d\n", PG_RO);
	printf("#define\tPG_RW %d\n", PG_RW);
	printf("#define\tPG_CI %d\n", PG_CI);
	printf("#define\tPG_PROT %d\n", PG_PROT);
	printf("#define\tPG_FRAME %d\n", PG_FRAME);
	printf("#define\tSG_V %d\n", SG_V);
	printf("#define\tSG_NV %d\n", SG_NV);
	printf("#define\tSG_RW %d\n", SG_RW);
	printf("#define\tSG_FRAME %d\n", SG_FRAME);
	printf("#define\tSG_ISHIFT %d\n", SG_ISHIFT);
	printf("#define\tPCB_FLAGS %d\n", &pcb->pcb_flags);
	printf("#define\tPCB_PS %d\n", &pcb->pcb_ps);
	printf("#define\tPCB_USTP %d\n", &pcb->pcb_ustp);
	printf("#define\tPCB_USP %d\n", &pcb->pcb_usp);
	printf("#define\tPCB_REGS %d\n", pcb->pcb_regs);
	printf("#define\tPCB_ONFAULT %d\n", &pcb->pcb_onfault);
	printf("#define\tPCB_FPCTX %d\n", &pcb->pcb_fpregs);
	printf("#define\tSIZEOF_PCB %d\n", sizeof(struct pcb));
	printf("#define\tSP %d\n", SP);
	printf("#define\tB_READ %d\n", B_READ);
	printf("#define\tENOENT %d\n", ENOENT);
	printf("#define\tEFAULT %d\n", EFAULT);
	printf("#define\tENAMETOOLONG %d\n", ENAMETOOLONG);
	printf("#define\tPIO0_A %d\n", &pio->a_port);
	printf("#define\tPIO0_B %d\n", &pio->b_port);
	printf("#define\tPIO0_CTL %d\n", &pio->control_port);
	printf("#define\tPIO_MODED %d\n", PIO_MODED);
	printf("#define\tCLOCK_REG %d\n", CLOCK_REG);
	printf("#define\tCLK_INT %d\n", CLK_INT);
	printf("#define\tCLK_CLR %d\n", CLK_CLR);
	printf("#define\tSYS_exit %d\n", SYS_exit);
	printf("#define\tSYS_execve %d\n", SYS_execve);
	printf("#define\tSYS_sigreturn %d\n", SYS_sigreturn);
E 2
I 2
	def("UPAGES", UPAGES);
	def("NBPG", NBPG);
	def("PGSHIFT", PGSHIFT);
	def("USRSTACK", USRSTACK);
	def("KERNELSTACK", KERNELSTACK);
D 5
	def("KI_MAXADDR", &KernInter->maxaddr);
E 5
I 5
	
	def("KIFF_SIZE", sizeof(struct KernInter));
	off("KI_MAXADDR", struct KernInter, maxaddr);
E 5

D 8
	off("P_LINK", struct proc, p_link);
	off("P_RLINK", struct proc, p_rlink);
E 8
I 8
	off("P_FORW", struct proc, p_forw);
	off("P_BACK", struct proc, p_back);
E 8
	off("P_VMSPACE", struct proc, p_vmspace);
	off("P_ADDR", struct proc, p_addr);
D 8
	off("P_PRI", struct proc, p_pri);
E 8
I 8
	off("P_PRIORITY", struct proc, p_priority);
E 8
	off("P_STAT", struct proc, p_stat);
	off("P_WCHAN", struct proc, p_wchan);
	off("P_FLAG", struct proc, p_flag);
I 4
	off("P_MDFLAG", struct proc, p_md.md_flags);
E 4
	def("SSLEEP", SSLEEP);
	def("SRUN", SRUN);

	off("VM_PMAP", struct vmspace, vm_pmap);
	off("PM_STCHG", struct pmap, pm_stchanged);

	off("V_SWTCH", struct vmmeter, v_swtch);
	off("V_INTR", struct vmmeter, v_intr);

	def("T_BUSERR", T_BUSERR);
	def("T_ADDRERR", T_ADDRERR);
	def("T_ILLINST", T_ILLINST);
	def("T_ZERODIV", T_ZERODIV);
	def("T_CHKINST", T_CHKINST);
	def("T_TRAPVINST", T_TRAPVINST);
	def("T_PRIVINST", T_PRIVINST);
	def("T_TRACE", T_TRACE);
	def("T_MMUFLT", T_MMUFLT);
	def("T_SSIR", T_SSIR);
	def("T_FMTERR", T_FMTERR);
	def("T_COPERR", T_COPERR);
	def("T_FPERR", T_FPERR);
	def("T_ASTFLT", T_ASTFLT);
	def("T_TRAP15", T_TRAP15);
	def("T_FPEMULI", T_FPEMULI);
	def("T_FPEMULD", T_FPEMULD);

	def("PSL_S", PSL_S);
	def("PSL_IPL7", PSL_IPL7);
	def("PSL_LOWIPL", PSL_LOWIPL);
	def("PSL_HIGHIPL", PSL_HIGHIPL);
	def("PSL_USER", PSL_USER);
	def("SPL1", PSL_S | PSL_IPL1);
	def("SPL2", PSL_S | PSL_IPL2);
	def("SPL3", PSL_S | PSL_IPL3);
	def("SPL4", PSL_S | PSL_IPL4);
	def("SPL5", PSL_S | PSL_IPL5);
	def("SPL6", PSL_S | PSL_IPL6);

	def("FC_USERD", FC_USERD);
	def("FC_PURGE", FC_PURGE);
	def("CACHE_ON", CACHE_ON);
	def("CACHE_OFF", CACHE_OFF);
	def("CACHE_CLR", CACHE_CLR);
	def("IC_CLEAR", IC_CLEAR);
	def("DC_CLEAR", DC_CLEAR);

	def("PG_V", PG_V);
	def("PG_NV", PG_NV);
	def("PG_RO", PG_RO);
	def("PG_RW", PG_RW);
	def("PG_CI", PG_CI);
	def("PG_PROT", PG_PROT);
	def("PG_FRAME", PG_FRAME);
	def("SG_V", SG_V);
	def("SG_NV", SG_NV);
	def("SG_RW", SG_RW);
	def("SG_FRAME", SG_FRAME);
	def("SG_ISHIFT", SG_ISHIFT);

	off("PCB_FLAGS", struct pcb, pcb_flags);
	off("PCB_PS", struct pcb, pcb_ps);
	off("PCB_USTP", struct pcb, pcb_ustp);
	off("PCB_USP", struct pcb, pcb_usp);
	off("PCB_REGS", struct pcb, pcb_regs);
	off("PCB_ONFAULT", struct pcb, pcb_onfault);
	off("PCB_FPCTX", struct pcb, pcb_fpregs);
	def("SIZEOF_PCB", sizeof(struct pcb));
I 4

	/* exception frame offset/sizes */
	off("FR_SP", struct frame, f_regs[15]);
	off("FR_HW", struct frame, f_sr);
	off("FR_ADJ", struct frame, f_stackadj);
E 4

	def("SYS_exit", SYS_exit);
	def("SYS_execve", SYS_execve);
	def("SYS_sigreturn", SYS_sigreturn);

	def("EFAULT", EFAULT);
	def("ENAMETOOLONG", ENAMETOOLONG);

	def("CLOCK_REG", CLOCK_REG);
	def("CLK_INT", CLK_INT);
	def("CLK_CLR", CLK_CLR);

	def("PIO0_A", &pio->a_port);
	def("PIO0_B", &pio->b_port);
	def("PIO0_CTL", &pio->control_port);
	def("PIO_MODED", PIO_MODED);

E 2
#ifdef	OLD_LUNA
D 2
	printf("define\tFLINE_VEC %d\n",44); /* F-Line excep vector offset */
	printf("define\tCOPRO_VEC %d\n",52); /* Coprocessor prot. offset */
E 2
I 2
	def("FLINE_VEC", 44); /* F-Line excep vector offset */
	def("COPRO_VEC", 52); /* Coprocessor prot. offset */
E 2
#endif
	exit(0);
}
E 1
