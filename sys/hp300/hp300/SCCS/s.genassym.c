h07696
s 00000/00002/00205
d D 8.3 94/01/04 18:39:14 bostic 17 16
c lint
e
s 00003/00003/00204
d D 8.2 93/09/23 16:19:40 bostic 16 15
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00205
d D 8.1 93/06/10 21:40:43 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00000/00196
d D 7.14 92/12/30 12:54:52 hibler 14 13
c LED defines
e
s 00007/00002/00189
d D 7.13 92/12/27 09:45:50 hibler 13 12
c new frame constants, a couple of flags renamed
e
s 00017/00015/00174
d D 7.12 92/10/11 09:42:33 bostic 12 11
c make kernel includes standard
e
s 00156/00136/00033
d D 7.11 92/07/08 01:07:37 torek 11 10
c major overhaul for legibility
e
s 00002/00001/00167
d D 7.10 92/06/05 15:36:58 hibler 10 9
c merge latest Utah hp300 code including 68040 support
e
s 00000/00004/00168
d D 7.9 91/08/29 23:35:47 mckusick 9 8
c delete nonexistent vmmeter fields
e
s 00003/00002/00169
d D 7.8 91/05/07 10:00:06 hibler 8 7
c  DIO-II support
e
s 00003/00009/00168
d D 7.7 91/05/04 19:36:25 karels 7 6
c pcb_sswap, ssave, sigc are gone; SPTECHG and pcb ast are gone
e
s 00009/00013/00168
d D 7.6 91/04/20 17:28:43 karels 6 5
c new proc, user structs
e
s 00017/00017/00164
d D 7.5 90/12/16 16:36:07 bostic 5 4
c kernel reorg
e
s 00012/00018/00169
d D 7.4 90/12/05 18:53:34 mckusick 4 3
c update from Mike Hibler for new VM and other machine support
e
s 00001/00000/00186
d D 7.3 90/11/01 12:24:33 karels 3 2
c add ENAMETOOLONG
e
s 00001/00001/00185
d D 7.2 90/06/22 09:32:39 hibler 2 1
c T_AST -> T_ASTFLT to be more consisent with VAX
e
s 00186/00000/00000
d D 7.1 90/05/08 18:09:08 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 15
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define KERNEL

D 4
#include "pte.h"

E 4
D 5
#include "param.h"
#include "buf.h"
#include "vmmeter.h"
D 4
#include "vmparam.h"
E 4
#include "user.h"
#include "cmap.h"
#include "map.h"
#include "proc.h"
D 4
#include "text.h"
E 4
#include "mbuf.h"
#include "msgbuf.h"
#include "cpu.h"
#include "trap.h"
#include "psl.h"
#include "reg.h"
E 5
I 5
D 12
#include "sys/param.h"
#include "sys/buf.h"
D 9
#include "sys/vmmeter.h"
E 9
D 6
#include "sys/user.h"
#include "sys/cmap.h"
E 6
#include "sys/map.h"
#include "sys/proc.h"
#include "sys/mbuf.h"
#include "sys/msgbuf.h"
#include "../include/cpu.h"
#include "../include/trap.h"
#include "../include/psl.h"
#include "../include/reg.h"
E 5
#include "clockreg.h"
D 5
#include "syscall.h"
I 4
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "pmap.h"
E 5
I 5
#include "sys/syscall.h"
D 6
#include "vm/vm_param.h"
#include "vm/vm_map.h"
#include "../include/pmap.h"
E 6
I 6
#include "vm/vm.h"
#include "sys/user.h"
#include "pte.h"
E 12
I 12
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

#include <hp300/hp300/clockreg.h>
#include <vm/vm.h>
#include <hp300/hp300/pte.h>
I 14
#ifdef USELEDS
#include <hp300/hp300/led.h>
#endif
E 14
E 12
E 6
E 5
E 4

I 11
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

E 11
main()
{
D 11
	register struct proc *p = (struct proc *)0;
	register struct vmmeter *vm = (struct vmmeter *)0;
	register struct user *up = (struct user *)0;
	register struct rusage *rup = (struct rusage *)0;
D 4
	struct text *tp = (struct text *)0;
E 4
I 4
D 6
	vm_map_t map = (vm_map_t)0;
E 6
I 6
	struct vmspace *vms = (struct vmspace *)0;
E 6
	pmap_t pmap = (pmap_t)0;
E 4
	struct pcb *pcb = (struct pcb *)0;
E 11
D 17
	register unsigned i;

E 17
D 11
	printf("#define\tP_LINK %d\n", &p->p_link);
	printf("#define\tP_RLINK %d\n", &p->p_rlink);
D 4
	printf("#define\tP_XLINK %d\n", &p->p_xlink);
E 4
I 4
D 6
	printf("#define\tP_MAP %d\n", &p->p_map);
	printf("#define\tPMAP %d\n", &map->pmap);
E 6
I 6
	printf("#define\tP_VMSPACE %d\n", &p->p_vmspace);
D 7
	printf("#define\tPMAP %d\n", &vms->vm_map.pmap);
E 7
I 7
	printf("#define\tVM_PMAP %d\n", &vms->vm_pmap);
E 7
E 6
	printf("#define\tPM_STCHG %d\n", &pmap->pm_stchanged);
E 4
	printf("#define\tP_ADDR %d\n", &p->p_addr);
	printf("#define\tP_PRI %d\n", &p->p_pri);
	printf("#define\tP_STAT %d\n", &p->p_stat);
	printf("#define\tP_WCHAN %d\n", &p->p_wchan);
D 4
	printf("#define\tP_TSIZE %d\n", &p->p_tsize);
	printf("#define\tP_DSIZE %d\n", &p->p_dsize);
	printf("#define\tP_SSIZE %d\n", &p->p_ssize);
	printf("#define\tP_P0BR %d\n", &p->p_p0br);
	printf("#define\tP_SZPT %d\n", &p->p_szpt);
	printf("#define\tP_TEXTP %d\n", &p->p_textp);
E 4
	printf("#define\tP_FLAG %d\n", &p->p_flag);
	printf("#define\tSSLEEP %d\n", SSLEEP);
	printf("#define\tSRUN %d\n", SRUN);
D 4
	printf("#define\tX_CADDR %d\n", &tp->x_caddr);
E 4
	printf("#define\tV_SWTCH %d\n", &vm->v_swtch);
	printf("#define\tV_TRAP %d\n", &vm->v_trap);
	printf("#define\tV_SYSCALL %d\n", &vm->v_syscall);
	printf("#define\tV_INTR %d\n", &vm->v_intr);
	printf("#define\tV_SOFT %d\n", &vm->v_soft);
D 9
	printf("#define\tV_PDMA %d\n", &vm->v_pdma);
E 9
	printf("#define\tV_FAULTS %d\n", &vm->v_faults);
D 9
	printf("#define\tV_PGREC %d\n", &vm->v_pgrec);
	printf("#define\tV_FASTPGREC %d\n", &vm->v_fastpgrec);
E 9
	printf("#define\tUPAGES %d\n", UPAGES);
	printf("#define\tHIGHPAGES %d\n", HIGHPAGES);
	printf("#define\tP1PAGES %d\n", P1PAGES);
	printf("#define\tCLSIZE %d\n", CLSIZE);
	printf("#define\tNBPG %d\n", NBPG);
I 4
	printf("#define\tNPTEPG %d\n", NPTEPG);
E 4
	printf("#define\tPGSHIFT %d\n", PGSHIFT);
	printf("#define\tSYSPTSIZE %d\n", SYSPTSIZE);
	printf("#define\tUSRPTSIZE %d\n", USRPTSIZE);
	printf("#define\tUSRIOSIZE %d\n", USRIOSIZE);
#ifdef SYSVSHM
	printf("#define\tSHMMAXPGS %d\n", SHMMAXPGS);
#endif
	printf("#define\tUSRSTACK %d\n", USRSTACK);
	printf("#define\tMSGBUFPTECNT %d\n", btoc(sizeof (struct msgbuf)));
	printf("#define\tNMBCLUSTERS %d\n", NMBCLUSTERS);
	printf("#define\tMCLBYTES %d\n", MCLBYTES);
	printf("#define\tNKMEMCLUSTERS %d\n", NKMEMCLUSTERS);
D 6
	printf("#define\tU_PROCP %d\n", &up->u_procp);
	printf("#define\tU_RU %d\n", &up->u_ru);
	printf("#define\tU_PROF %d\n", &up->u_prof);
	printf("#define\tU_PROFSCALE %d\n", &up->u_prof.pr_scale);
E 6
I 6
	printf("#define\tU_PROF %d\n", &up->u_stats.p_prof);
	printf("#define\tU_PROFSCALE %d\n", &up->u_stats.p_prof.pr_scale);
E 6
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
D 2
	printf("#define\tT_AST %d\n", T_AST);
E 2
I 2
	printf("#define\tT_ASTFLT %d\n", T_ASTFLT);
E 2
	printf("#define\tT_TRAP15 %d\n", T_TRAP15);
I 10
	printf("#define\tT_FPEMULI %d\n", T_FPEMULI);
	printf("#define\tT_FPEMULD %d\n", T_FPEMULD);
E 10
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
	printf("#define\tMAXADDR %d\n", MAXADDR);
D 8
	printf("#define\tIOMAPSIZE %d\n", IOMAPSIZE);
	printf("#define\tIOBASE %d\n", IOBASE);
E 8
I 8
	printf("#define\tIIOMAPSIZE %d\n", IIOMAPSIZE);
	printf("#define\tEIOMAPSIZE %d\n", EIOMAPSIZE);
	printf("#define\tINTIOBASE %d\n", INTIOBASE);
E 8
I 4
	printf("#define\tMMUBASE %d\n", MMUBASE);
E 4
	printf("#define\tMMUSTAT %d\n", MMUSTAT);
	printf("#define\tMMUCMD %d\n", MMUCMD);
	printf("#define\tMMUSSTP %d\n", MMUSSTP);
	printf("#define\tMMUUSTP %d\n", MMUUSTP);
	printf("#define\tMMUTBINVAL %d\n", MMUTBINVAL);
	printf("#define\tMMU_BERR %d\n", MMU_BERR);
	printf("#define\tMMU_ENAB %d\n", MMU_ENAB);
	printf("#define\tMMU_FAULT %d\n", MMU_FAULT);
	printf("#define\tMMU_CEN %d\n", MMU_CEN);
	printf("#define\tMMU_IEN %d\n", MMU_IEN);
	printf("#define\tMMU_FPE %d\n", MMU_FPE);
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
I 4
	printf("#define\tSG_ISHIFT %d\n", SG_ISHIFT);
E 4
	printf("#define\tPCB_FLAGS %d\n", &pcb->pcb_flags);
	printf("#define\tPCB_PS %d\n", &pcb->pcb_ps);
	printf("#define\tPCB_USTP %d\n", &pcb->pcb_ustp);
	printf("#define\tPCB_USP %d\n", &pcb->pcb_usp);
	printf("#define\tPCB_REGS %d\n", pcb->pcb_regs);
D 4
	printf("#define\tPCB_P0BR %d\n", &pcb->pcb_p0br);
	printf("#define\tPCB_P0LR %d\n", &pcb->pcb_p0lr);
	printf("#define\tPCB_P1BR %d\n", &pcb->pcb_p1br);
	printf("#define\tPCB_P1LR %d\n", &pcb->pcb_p1lr);
	printf("#define\tPCB_SZPT %d\n", &pcb->pcb_szpt);
E 4
D 10
	printf("#define\tPCB_CMAP2 %d\n", &pcb->pcb_cmap2);
E 10
D 7
	printf("#define\tPCB_SSWAP %d\n", &pcb->pcb_sswap);
	printf("#define\tPCB_SIGC %d\n", pcb->pcb_sigc);
E 7
	printf("#define\tPCB_ONFAULT %d\n", &pcb->pcb_onfault);
	printf("#define\tPCB_FPCTX %d\n", &pcb->pcb_fpregs);
I 7
	printf("#define\tSIZEOF_PCB %d\n", sizeof(struct pcb));
E 7
	printf("#define\tSP %d\n", SP);
	printf("#define\tB_READ %d\n", B_READ);
	printf("#define\tENOENT %d\n", ENOENT);
	printf("#define\tEFAULT %d\n", EFAULT);
I 3
	printf("#define\tENAMETOOLONG %d\n", ENAMETOOLONG);
I 4
	printf("#define\tCLKBASE %d\n", CLKBASE);
E 4
E 3
	printf("#define\tCLKCR1 %d\n", CLKCR1);
	printf("#define\tCLKCR2 %d\n", CLKCR2);
	printf("#define\tCLKCR3 %d\n", CLKCR3);
	printf("#define\tCLKSR %d\n", CLKSR);
	printf("#define\tCLKMSB1 %d\n", CLKMSB1);
	printf("#define\tCLKMSB2 %d\n", CLKMSB2);
	printf("#define\tCLKMSB3 %d\n", CLKMSB3);
	printf("#define\tSYS_exit %d\n", SYS_exit);
D 6
	printf("#define\tSYS_execv %d\n", SYS_execv);
E 6
I 6
	printf("#define\tSYS_execve %d\n", SYS_execve);
E 6
	printf("#define\tSYS_sigreturn %d\n", SYS_sigreturn);
D 7
	for (i = 0; i < 32; i++) {
		if ((1 << i) & SPTECHG)
			printf("#define\tSPTECHGB %d\n", i);
		if ((1 << i) & PCB_AST)
			printf("#define\tPCB_ASTB %d\n", i);
E 7
I 7
	for (i = 0; i < 32; i++)
E 7
		if ((1 << i) & PCB_HPUXTRACE)
			printf("#define\tPCB_TRCB %d\n", i);
E 11
I 11
	/* general constants */
	def("UPAGES", UPAGES);
	def("NBPG", NBPG);
	def("PGSHIFT", PGSHIFT);
	def("USRSTACK", USRSTACK);
	def("MAXADDR", MAXADDR);

	/* proc fields and values */
D 16
	off("P_LINK", struct proc, p_link);
	off("P_RLINK", struct proc, p_rlink);
E 16
I 16
	off("P_FORW", struct proc, p_forw);
	off("P_BACK", struct proc, p_back);
E 16
	off("P_VMSPACE", struct proc, p_vmspace);
	off("P_ADDR", struct proc, p_addr);
D 16
	off("P_PRI", struct proc, p_pri);
E 16
I 16
	off("P_PRIORITY", struct proc, p_priority);
E 16
	off("P_STAT", struct proc, p_stat);
	off("P_WCHAN", struct proc, p_wchan);
	off("P_FLAG", struct proc, p_flag);
I 13
	off("P_MDFLAG", struct proc, p_md.md_flags);
E 13
	def("SSLEEP", SSLEEP);
	def("SRUN", SRUN);

	/* VM structure fields */
	off("VM_PMAP", struct vmspace, vm_pmap);
	off("PM_STCHG", struct pmap, pm_stchanged);

	/* interrupt/fault metering */
	off("V_SWTCH", struct vmmeter, v_swtch);
	off("V_INTR", struct vmmeter, v_intr);

	/* trap types (should just include trap.h?) */
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

	/* PSL values (should just include psl.h?) */
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

	/* magic */
	def("FC_USERD", FC_USERD);
	def("FC_PURGE", FC_PURGE);
	def("INTIOBASE", INTIOBASE);
	def("MMUBASE", MMUBASE);
	def("MMUSTAT", MMUSTAT);
	def("MMUCMD", MMUCMD);
	def("MMUSSTP", MMUSSTP);
	def("MMUUSTP", MMUUSTP);
	def("MMUTBINVAL", MMUTBINVAL);
	def("MMU_BERR", MMU_BERR);
	def("MMU_ENAB", MMU_ENAB);
	def("MMU_FAULT", MMU_FAULT);
	def("MMU_CEN", MMU_CEN);
	def("MMU_IEN", MMU_IEN);
	def("MMU_FPE", MMU_FPE);
	def("CACHE_ON", CACHE_ON);
	def("CACHE_OFF", CACHE_OFF);
	def("CACHE_CLR", CACHE_CLR);
	def("IC_CLEAR", IC_CLEAR);
	def("DC_CLEAR", DC_CLEAR);

	/* pte/ste bits */
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

	/* pcb fields */
D 13
	off("PCB_FLAGS", struct pcb, pcb_flags);
E 13
	off("PCB_PS", struct pcb, pcb_ps);
	off("PCB_USTP", struct pcb, pcb_ustp);
	off("PCB_USP", struct pcb, pcb_usp);
	off("PCB_REGS", struct pcb, pcb_regs);
	off("PCB_ONFAULT", struct pcb, pcb_onfault);
	off("PCB_FPCTX", struct pcb, pcb_fpregs);
	def("SIZEOF_PCB", sizeof(struct pcb));

I 13
	/* exception frame offset/sizes */
	off("FR_SP", struct frame, f_regs[15]);
	off("FR_HW", struct frame, f_sr);
	off("FR_ADJ", struct frame, f_stackadj);

E 13
	/* system calls */
	def("SYS_exit", SYS_exit);
	def("SYS_execve", SYS_execve);
	def("SYS_sigreturn", SYS_sigreturn);

	/* errno */
	def("EFAULT", EFAULT);
	def("ENAMETOOLONG", ENAMETOOLONG);

	/* clock registers */
	def("CLKSR", CLKSR);
	def("CLKMSB1", CLKMSB1);
	def("CLKMSB3", CLKMSB3);

	/* HP-UX trace bit */
D 13
	def("PCB_TRCB", ffs(PCB_HPUXTRACE) - 1);
E 13
I 13
	def("MDP_TRCB", ffs(MDP_HPUXTRACE) - 1);
I 14

#ifdef USELEDS
	/* LEDs */
	def("LED_PULSE", LED_PULSE);
	def("LED_DISK", LED_DISK);
	def("LED_LANRCV", LED_LANRCV);
	def("LED_LANXMT", LED_LANXMT);
#endif
E 14
E 13

E 11
D 7
	}
E 7
	exit(0);
}
E 1
