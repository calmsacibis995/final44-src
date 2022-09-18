h64496
s 00003/00003/00131
d D 8.2 93/09/23 16:42:43 bostic 19 18
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00132
d D 8.1 93/06/11 15:34:41 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00013/00121
d D 5.16 92/10/11 10:10:55 bostic 17 16
c make kernel includes standard
e
s 00001/00000/00133
d D 5.15 92/07/14 14:47:20 bostic 16 15
c Add PDRSHIFT, which is used by the new suword and subyte.
c (from Pace Willisson)
e
s 00004/00006/00129
d D 5.14 91/11/07 18:03:03 sklower 15 14
c finish job kirk started
e
s 00000/00003/00135
d D 5.13 91/08/29 23:40:20 mckusick 14 13
c delete nonexistent vmmeter fields
e
s 00000/00001/00138
d D 5.12 91/08/15 17:37:35 william 13 12
c forget about cmap.h
e
s 00000/00001/00139
d D 5.11 91/05/10 14:27:18 william 12 11
c delete P1PAGES value
e
s 00027/00027/00113
d D 5.10 91/05/09 18:23:22 william 11 10
c final version, name cleanups
e
s 00012/00014/00128
d D 5.9 91/05/09 18:22:33 william 10 9
c interim version, we lose a u.
e
s 00009/00004/00133
d D 5.8 91/05/01 09:38:47 william 9 8
c addeded profiling
e
s 00041/00032/00096
d D 5.7 91/05/01 09:37:28 william 8 7
c interim version
e
s 00026/00012/00102
d D 5.6 91/01/19 12:40:29 william 7 6
c reno changes
e
s 00000/00000/00114
d D 5.5 91/01/15 12:22:01 bill 6 5
c reno changes
e
s 00002/00000/00112
d D 5.4 90/11/14 15:32:41 bill 5 4
c chip bug define relayed to assembler
e
s 00001/00000/00111
d D 5.3 90/11/14 13:38:41 bill 4 3
c added emc context save struct
e
s 00002/00000/00109
d D 5.2 90/11/14 13:03:02 bill 3 2
c pass USRIO constant, added interrupt mask to pcb
e
s 00018/00003/00091
d D 5.1 90/04/24 18:52:13 william 2 1
c 1st Berkeley Release
e
s 00094/00000/00000
d D 1.1 90/03/12 15:47:54 bill 1 0
c date and time created 90/03/12 15:47:54 by bill
e
u
U
t
T
I 1
D 2
#ifndef lint
static char sccsid[] = "@(#)genassym.c	1.7 (Berkeley) 10/28/87";
#endif
E 2
I 2
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
E 8
I 8
D 18
 * Copyright (c) 1982, 1990 The Regents of the University of California.
E 8
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 7
 * %sccs.include.noredist.c%
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 7
#include "../i386/pte.h"
E 7
I 7
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
D 8
#define	KERNEL
#include "machine/pte.h"
E 8
E 7

I 15
#define KERNEL

E 15
D 8
#include "param.h"
D 7
#include "vmmeter.h"
#include "vmparam.h"
E 7
#include "buf.h"
D 7
#include "dir.h"
E 7
I 7
#include "vmmeter.h"
#include "machine/vmparam.h"
E 7
#include "user.h"
#include "cmap.h"
#include "map.h"
#include "proc.h"
#include "text.h"
#include "mbuf.h"
#include "msgbuf.h"
E 8
I 8
D 17
#include "sys/param.h"
#include "sys/buf.h"
D 15
#include "sys/vmmeter.h"
E 15
D 10
#include "sys/user.h"
E 10
D 13
#include "sys/cmap.h"
E 13
#include "sys/map.h"
#include "sys/proc.h"
I 10
D 15
#include "sys/user.h"
E 15
E 10
#include "sys/mbuf.h"
#include "sys/msgbuf.h"
I 10
D 15
#include "sys/resourcevar.h"
E 15
E 10
E 8
I 7
#include "machine/cpu.h"
#include "machine/trap.h"
#include "machine/psl.h"
#include "machine/reg.h"
D 8
#include "syscall.h"
E 8
I 8
#include "sys/syscall.h"
D 15
#include "vm/vm_param.h"
#include "vm/vm_map.h"
#include "machine/pmap.h"
E 15
I 15
#include "vm/vm.h"
#include "sys/user.h"
E 17
I 17
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>
#include <machine/cpu.h>
#include <machine/trap.h>
#include <machine/psl.h>
#include <machine/reg.h>
#include <sys/syscall.h>
#include <vm/vm.h>
#include <sys/user.h>
E 17
E 15
E 8
E 7

main()
{
D 7
	register struct user *u = (struct user *)0;
E 7
D 9
	register struct proc *p = (struct proc *)0;
	register struct vmmeter *vm = (struct vmmeter *)0;
D 7
	register struct pcb *pcb = (struct pcb *)0;
E 7
I 7
	register struct user *up = (struct user *)0;
	register struct rusage *rup = (struct rusage *)0;
E 9
I 9
	struct proc *p = (struct proc *)0;
	struct vmmeter *vm = (struct vmmeter *)0;
	struct user *up = (struct user *)0;
	struct rusage *rup = (struct rusage *)0;
	struct uprof *uprof = (struct uprof *)0;
I 10
	struct vmspace *vms = (struct vmspace *)0;
E 10
E 9
D 8
	struct text *tp = (struct text *)0;
E 8
I 8
	vm_map_t map = (vm_map_t)0;
	pmap_t pmap = (pmap_t)0;
E 8
	struct pcb *pcb = (struct pcb *)0;
	register unsigned i;
E 7

D 8
	printf("#ifdef LOCORE\n");
E 8
I 5
	printf("#define\tI386_CR3PAT %d\n", I386_CR3PAT);
D 7

E 5
	printf("#define\tU_PROCP %d\n", &u->u_procp);
	printf("#define\tU_EOSYS %d\n", &u->u_eosys);
E 7
I 7
D 10
	printf("#define\tU_PROCP %d\n", &up->u_procp);
E 10
	printf("#define\tUDOT_SZ %d\n", sizeof(struct user));
E 7
D 19
	printf("#define\tP_LINK %d\n", &p->p_link);
	printf("#define\tP_RLINK %d\n", &p->p_rlink);
E 19
I 19
	printf("#define\tP_FORW %d\n", &p->p_forw);
	printf("#define\tP_BACK %d\n", &p->p_back);
E 19
D 8
	printf("#define\tP_XLINK %d\n", &p->p_xlink);
E 8
I 8
D 10
	printf("#define\tP_MAP %d\n", &p->p_map);
	printf("#define\tPMAP %d\n", &map->pmap);
	printf("#define\tPM_STCHG %d\n", &pmap->pm_pdchanged);
E 10
I 10
	printf("#define\tP_VMSPACE %d\n", &p->p_vmspace);
	printf("#define\tVM_PMAP %d\n", &vms->vm_pmap);
E 10
E 8
	printf("#define\tP_ADDR %d\n", &p->p_addr);
D 19
	printf("#define\tP_PRI %d\n", &p->p_pri);
E 19
I 19
	printf("#define\tP_PRIORITY %d\n", &p->p_priority);
E 19
	printf("#define\tP_STAT %d\n", &p->p_stat);
	printf("#define\tP_WCHAN %d\n", &p->p_wchan);
D 8
	printf("#define\tP_TSIZE %d\n", &p->p_tsize);
	printf("#define\tP_SSIZE %d\n", &p->p_ssize);
	printf("#define\tP_P0BR %d\n", &p->p_p0br);
	printf("#define\tP_SZPT %d\n", &p->p_szpt);
	printf("#define\tP_TEXTP %d\n", &p->p_textp);
E 8
	printf("#define\tP_FLAG %d\n", &p->p_flag);
I 2
D 7
	printf("#define\tP_CR3 %d\n", &p->p_cr3);
E 7
I 7
	printf("#define\tP_PID %d\n", &p->p_pid);
E 7
E 2
	printf("#define\tSSLEEP %d\n", SSLEEP);
	printf("#define\tSRUN %d\n", SRUN);
	printf("#define\tV_SWTCH %d\n", &vm->v_swtch);
	printf("#define\tV_TRAP %d\n", &vm->v_trap);
	printf("#define\tV_SYSCALL %d\n", &vm->v_syscall);
	printf("#define\tV_INTR %d\n", &vm->v_intr);
	printf("#define\tV_SOFT %d\n", &vm->v_soft);
I 8
D 14
	printf("#define\tV_PDMA %d\n", &vm->v_pdma);
E 14
	printf("#define\tV_FAULTS %d\n", &vm->v_faults);
D 14
	printf("#define\tV_PGREC %d\n", &vm->v_pgrec);
	printf("#define\tV_FASTPGREC %d\n", &vm->v_fastpgrec);
E 14
	printf("#define\tUPAGES %d\n", UPAGES);
	printf("#define\tHIGHPAGES %d\n", HIGHPAGES);
E 8
I 2
D 12
	printf("#define\tP1PAGES %d\n", P1PAGES);
E 12
I 8
	printf("#define\tCLSIZE %d\n", CLSIZE);
E 8
E 2
	printf("#define\tNBPG %d\n", NBPG);
I 8
	printf("#define\tNPTEPG %d\n", NPTEPG);
E 8
	printf("#define\tPGSHIFT %d\n", PGSHIFT);
I 16
	printf("#define\tPDRSHIFT %d\n", PDRSHIFT);
E 16
D 8
	printf("#define\tUPAGES %d\n", UPAGES);
	printf("#define\tCLSIZE %d\n", CLSIZE);
	printf("#define\tMAXPHYS %d\n", MAXPHYS);
E 8
	printf("#define\tSYSPTSIZE %d\n", SYSPTSIZE);
	printf("#define\tUSRPTSIZE %d\n", USRPTSIZE);
I 3
	printf("#define\tUSRIOSIZE %d\n", USRIOSIZE);
I 8
#ifdef SYSVSHM
	printf("#define\tSHMMAXPGS %d\n", SHMMAXPGS);
#endif
	printf("#define\tUSRSTACK %d\n", USRSTACK);
E 8
E 3
	printf("#define\tMSGBUFPTECNT %d\n", btoc(sizeof (struct msgbuf)));
	printf("#define\tNMBCLUSTERS %d\n", NMBCLUSTERS);
	printf("#define\tMCLBYTES %d\n", MCLBYTES);
D 11
	printf("#define\tPCB_LINK %d\n", &pcb->pcbtss.tss_link);
	printf("#define\tPCB_ESP0 %d\n", &pcb->pcbtss.tss_esp0);
	printf("#define\tPCB_SS0 %d\n", &pcb->pcbtss.tss_ss0);
	printf("#define\tPCB_ESP1 %d\n", &pcb->pcbtss.tss_esp1);
	printf("#define\tPCB_SS1 %d\n", &pcb->pcbtss.tss_ss1);
	printf("#define\tPCB_ESP2 %d\n", &pcb->pcbtss.tss_esp2);
	printf("#define\tPCB_SS2 %d\n", &pcb->pcbtss.tss_ss2);
	printf("#define\tPCB_CR3 %d\n", &pcb->pcbtss.tss_cr3);
	printf("#define\tPCB_EIP %d\n", &pcb->pcbtss.tss_eip);
	printf("#define\tPCB_EFLAGS %d\n", &pcb->pcbtss.tss_eflags);
	printf("#define\tPCB_EAX %d\n", &pcb->pcbtss.tss_eax);
	printf("#define\tPCB_ECX %d\n", &pcb->pcbtss.tss_ecx);
	printf("#define\tPCB_EDX %d\n", &pcb->pcbtss.tss_edx);
	printf("#define\tPCB_EBX %d\n", &pcb->pcbtss.tss_ebx);
	printf("#define\tPCB_ESP %d\n", &pcb->pcbtss.tss_esp);
	printf("#define\tPCB_EBP %d\n", &pcb->pcbtss.tss_ebp);
	printf("#define\tPCB_ESI %d\n", &pcb->pcbtss.tss_esi);
	printf("#define\tPCB_EDI %d\n", &pcb->pcbtss.tss_edi);
	printf("#define\tPCB_ES %d\n", &pcb->pcbtss.tss_es);
	printf("#define\tPCB_CS %d\n", &pcb->pcbtss.tss_cs);
	printf("#define\tPCB_SS %d\n", &pcb->pcbtss.tss_ss);
	printf("#define\tPCB_DS %d\n", &pcb->pcbtss.tss_ds);
	printf("#define\tPCB_FS %d\n", &pcb->pcbtss.tss_fs);
	printf("#define\tPCB_GS %d\n", &pcb->pcbtss.tss_gs);
	printf("#define\tPCB_LDT %d\n", &pcb->pcbtss.tss_ldt);
	printf("#define\tPCB_IOOPT %d\n", &pcb->pcbtss.tss_ioopt);
E 11
I 11
	printf("#define\tPCB_LINK %d\n", &pcb->pcb_tss.tss_link);
	printf("#define\tPCB_ESP0 %d\n", &pcb->pcb_tss.tss_esp0);
	printf("#define\tPCB_SS0 %d\n", &pcb->pcb_tss.tss_ss0);
	printf("#define\tPCB_ESP1 %d\n", &pcb->pcb_tss.tss_esp1);
	printf("#define\tPCB_SS1 %d\n", &pcb->pcb_tss.tss_ss1);
	printf("#define\tPCB_ESP2 %d\n", &pcb->pcb_tss.tss_esp2);
	printf("#define\tPCB_SS2 %d\n", &pcb->pcb_tss.tss_ss2);
	printf("#define\tPCB_CR3 %d\n", &pcb->pcb_tss.tss_cr3);
	printf("#define\tPCB_EIP %d\n", &pcb->pcb_tss.tss_eip);
	printf("#define\tPCB_EFLAGS %d\n", &pcb->pcb_tss.tss_eflags);
	printf("#define\tPCB_EAX %d\n", &pcb->pcb_tss.tss_eax);
	printf("#define\tPCB_ECX %d\n", &pcb->pcb_tss.tss_ecx);
	printf("#define\tPCB_EDX %d\n", &pcb->pcb_tss.tss_edx);
	printf("#define\tPCB_EBX %d\n", &pcb->pcb_tss.tss_ebx);
	printf("#define\tPCB_ESP %d\n", &pcb->pcb_tss.tss_esp);
	printf("#define\tPCB_EBP %d\n", &pcb->pcb_tss.tss_ebp);
	printf("#define\tPCB_ESI %d\n", &pcb->pcb_tss.tss_esi);
	printf("#define\tPCB_EDI %d\n", &pcb->pcb_tss.tss_edi);
	printf("#define\tPCB_ES %d\n", &pcb->pcb_tss.tss_es);
	printf("#define\tPCB_CS %d\n", &pcb->pcb_tss.tss_cs);
	printf("#define\tPCB_SS %d\n", &pcb->pcb_tss.tss_ss);
	printf("#define\tPCB_DS %d\n", &pcb->pcb_tss.tss_ds);
	printf("#define\tPCB_FS %d\n", &pcb->pcb_tss.tss_fs);
	printf("#define\tPCB_GS %d\n", &pcb->pcb_tss.tss_gs);
	printf("#define\tPCB_LDT %d\n", &pcb->pcb_tss.tss_ldt);
	printf("#define\tPCB_IOOPT %d\n", &pcb->pcb_tss.tss_ioopt);
E 11
I 8
	printf("#define\tNKMEMCLUSTERS %d\n", NKMEMCLUSTERS);
D 10
	printf("#define\tU_PROCP %d\n", &up->u_procp);
	printf("#define\tU_RU %d\n", &up->u_ru);
	printf("#define\tU_PROF %d\n", &up->u_prof);
	printf("#define\tU_PROFSCALE %d\n", &up->u_prof.pr_scale);
I 9
	printf("#define\tPR_BASE %d\n", &uprof.pr_base);
	printf("#define\tPR_SIZE %d\n", &uprof.pr_size);
	printf("#define\tPR_OFF %d\n", &uprof.pr_off);
	printf("#define\tPR_SCALE %d\n", &uprof.pr_scale);
E 10
I 10
	printf("#define\tU_PROF %d\n", &up->u_stats.p_prof);
	printf("#define\tU_PROFSCALE %d\n", &up->u_stats.p_prof.pr_scale);
	printf("#define\tPR_BASE %d\n", &uprof->pr_base);
	printf("#define\tPR_SIZE %d\n", &uprof->pr_size);
	printf("#define\tPR_OFF %d\n", &uprof->pr_off);
	printf("#define\tPR_SCALE %d\n", &uprof->pr_scale);
E 10
E 9
	printf("#define\tRU_MINFLT %d\n", &rup->ru_minflt);
E 8
I 2
D 7
	printf("#define\tPCB_FPSAV %d\n", &pcb->pcb_fpsav);
E 7
I 7
	printf("#define\tPCB_FLAGS %d\n", &pcb->pcb_flags);
I 10
	printf("#define\tPCB_SAVEFPU %d\n", &pcb->pcb_savefpu);
E 10
	printf("#define\tFP_WASUSED %d\n", FP_WASUSED);
	printf("#define\tFP_NEEDSSAVE %d\n", FP_NEEDSSAVE);
	printf("#define\tFP_NEEDSRESTORE %d\n", FP_NEEDSRESTORE);
	printf("#define\tFP_USESEMC %d\n", FP_USESEMC);
E 7
E 2
D 10
	printf("#define\tPCB_SAVEFPU %d\n", &pcb->pcb_savefpu);
E 10
I 4
	printf("#define\tPCB_SAVEEMC %d\n", &pcb->pcb_saveemc);
E 4
I 2
D 8
	printf("#define\tPCB_P0BR %d\n", &pcb->pcb_p0br);
	printf("#define\tPCB_P1BR %d\n", &pcb->pcb_p1br);
	printf("#define\tPCB_P0LR %d\n", &pcb->pcb_p0lr);
	printf("#define\tPCB_P1LR %d\n", &pcb->pcb_p1lr);
E 2
	printf("#define\tPCB_SZPT %d\n", &pcb->pcb_szpt);
E 8
	printf("#define\tPCB_CMAP2 %d\n", &pcb->pcb_cmap2);
D 11
	printf("#define\tPCB_SSWAP %d\n", &pcb->pcb_sswap);
E 11
	printf("#define\tPCB_SIGC %d\n", pcb->pcb_sigc);
I 3
	printf("#define\tPCB_IML %d\n", &pcb->pcb_iml);
I 11
	printf("#define\tPCB_ONFAULT %d\n", &pcb->pcb_onfault);
E 11
E 3

D 8
	printf("#endif\n");
E 8
I 8
	printf("#define\tB_READ %d\n", B_READ);
	printf("#define\tENOENT %d\n", ENOENT);
	printf("#define\tEFAULT %d\n", EFAULT);
	printf("#define\tENAMETOOLONG %d\n", ENAMETOOLONG);
E 8
	exit(0);
}
E 1
