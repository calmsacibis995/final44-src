h30414
s 00003/00003/00066
d D 8.2 93/09/23 16:41:00 bostic 9 8
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00067
d D 8.1 93/06/11 15:02:38 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00011/00067
d D 7.7 93/05/13 19:49:58 utashiro 7 6
c change for new pmap interface.
e
s 00001/00000/00077
d D 7.6 93/03/10 04:47:32 utashiro 6 5
c added VM_MIN_ADDRESS
e
s 00000/00002/00077
d D 7.5 93/03/09 23:53:42 utashiro 5 4
c cleanup header and machine dependency.
e
s 00000/00009/00079
d D 7.4 93/01/20 00:15:07 utashiro 4 3
c Removed unnecessary lines.
e
s 00015/00015/00073
d D 7.3 92/12/17 01:28:27 utashiro 3 2
c make kernel includes standard
e
s 00002/00002/00086
d D 7.2 92/06/25 18:34:51 utashiro 2 1
c change for new pmap hash scheme
e
s 00088/00000/00000
d D 7.1 92/06/04 16:06:53 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define KERNEL

D 3
#include "../include/fix_machine_type.h"
E 3
I 3
D 5
#include <machine/fix_machine_type.h>
E 3

E 5
D 3
#include "sys/param.h"
#include "sys/buf.h"
#include "sys/dir.h"
#include "sys/map.h"
#include "sys/proc.h"
#include "sys/mbuf.h"
#include "sys/user.h"
#include "sys/msgbuf.h"
#include "sys/syscall.h"
#include "sys/signal.h"
#include "vm/vm.h"
#include "../include/reg.h"
#include "../include/pte.h"
#include "../include/pmap.h"
E 3
I 3
#include <sys/param.h>
#include <sys/buf.h>
D 4
#include <sys/dir.h>
E 4
#include <sys/map.h>
#include <sys/proc.h>
D 4
#include <sys/mbuf.h>
E 4
#include <sys/user.h>
D 4
#include <sys/msgbuf.h>
#include <sys/syscall.h>
#include <sys/signal.h>
#include <vm/vm.h>
E 4
#include <machine/reg.h>
#include <machine/pte.h>
D 7
#include <machine/pmap.h>
E 7
E 3

main()
{
	register struct proc *p = (struct proc *)0;
D 7
	register pmap_hash_t hp = (pmap_hash_t)PMAP_HASH_UADDR;
E 7
	register struct vmmeter *vm = (struct vmmeter *)0;
	register struct user *up = (struct user *)0;
	register struct rusage *rup = (struct rusage *)0;
	register struct pcb *pcb = (struct pcb *)0;

	/*
	 * struct proc
	 */
D 9
	printf("#define\tP_LINK %d\n", &p->p_link);
	printf("#define\tP_RLINK %d\n", &p->p_rlink);
E 9
I 9
	printf("#define\tP_FORW %d\n", &p->p_forw);
	printf("#define\tP_BACK %d\n", &p->p_back);
E 9
	printf("#define\tP_ADDR %d\n", &p->p_addr);
	printf("#define\tP_UPTE %d\n", p->p_md.md_upte);
D 9
	printf("#define\tP_PRI %d\n", &p->p_pri);
E 9
I 9
	printf("#define\tP_PRIORITY %d\n", &p->p_priority);
E 9
	printf("#define\tP_STAT %d\n", &p->p_stat);
	printf("#define\tP_PID %d\n", &p->p_pid);
	printf("#define\tP_WCHAN %d\n", &p->p_wchan);
	printf("#define\tP_FLAG %d\n", &p->p_flag);

	/*
	 * struct vmmeter
	 */
	printf("#define\tV_SWTCH %d\n", &vm->v_swtch);
	printf("#define\tV_TRAP %d\n", &vm->v_trap);
	printf("#define\tV_SYSCALL %d\n", &vm->v_syscall);
	printf("#define\tV_INTR %d\n", &vm->v_intr);
	printf("#define\tV_SOFT %d\n", &vm->v_soft);
	printf("#define\tV_FAULTS %d\n", &vm->v_faults);

	/*
	 * struct user
	 */
	printf("#define\tU_PCB_REGS %d\n", up->u_pcb.pcb_regs);
	printf("#define\tU_PCB_FPREGS %d\n", &up->u_pcb.pcb_regs[F0]);
	printf("#define\tU_PCB_CONTEXT %d\n", &up->u_pcb.pcb_context);
	printf("#define\tU_PCB_ONFAULT %d\n", &up->u_pcb.pcb_onfault);

D 2
	printf("#define\tPMAP_HASH_LOW_OFFSET 0x%x\n", &hp->low);
	printf("#define\tPMAP_HASH_HIGH_OFFSET 0x%x\n", &hp->high);
E 2
I 2
D 7
	printf("#define\tPMAP_HASH_LOW_OFFSET 0x%x\n", &hp->pmh_pte[0].low);
	printf("#define\tPMAP_HASH_HIGH_OFFSET 0x%x\n", &hp->pmh_pte[0].high);
E 2
	printf("#define\tPMAP_HASH_KPAGES %d\n", PMAP_HASH_KPAGES);
	printf("#define\tPMAP_HASH_KADDR 0x%x\n", PMAP_HASH_KADDR);
	printf("#define\tPMAP_HASH_SIZE_SHIFT %d\n", PMAP_HASH_SIZE_SHIFT);
	printf("#define\tPMAP_HASH_SHIFT1 %d\n", PMAP_HASH_SHIFT1);
	printf("#define\tPMAP_HASH_SHIFT2 %d\n", PMAP_HASH_SHIFT2);
	printf("#define\tPMAP_HASH_MASK1 0x%x\n", PMAP_HASH_MASK1);
	printf("#define\tPMAP_HASH_MASK2 0x%x\n", PMAP_HASH_MASK2);
E 7
I 7
	printf("#define\tU_PCB_SEGTAB %d\n", &up->u_pcb.pcb_segtab);
E 7
I 6
	printf("#define\tVM_MIN_ADDRESS 0x%x\n", VM_MIN_ADDRESS);
I 7
	printf("#define\tVM_MIN_KERNEL_ADDRESS 0x%x\n", VM_MIN_KERNEL_ADDRESS);
E 7
E 6

	printf("#define\tNBPW %d\n", NBPW);

	printf("#define\tSIGILL %d\n", SIGILL);
	printf("#define\tSIGFPE %d\n", SIGFPE);
D 4

	printf("#define\tSYS_execve %d\n", SYS_execve);
	printf("#define\tSYS_exit %d\n", SYS_exit);
E 4

	exit(0);
}
E 1
