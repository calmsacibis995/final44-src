h03096
s 00004/00000/00047
d D 8.3 95/06/02 17:25:19 ralph 8 7
c final changes for pmax 4.4-Lite II release
e
s 00003/00003/00044
d D 8.2 93/09/23 16:37:55 bostic 7 6
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00045
d D 8.1 93/06/10 23:06:52 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00011/00045
d D 7.5 93/05/09 17:49:21 ralph 5 4
c new improved pmap changes
e
s 00001/00000/00055
d D 7.4 93/02/04 19:55:42 ralph 4 3
c changes for a.out format
e
s 00009/00008/00046
d D 7.3 92/10/11 11:23:10 bostic 3 2
c make kernel includes standard
e
s 00002/00002/00052
d D 7.2 92/06/20 12:04:05 ralph 2 1
c fix pmap cache changes.
e
s 00054/00000/00000
d D 7.1 92/01/07 17:29:20 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define KERNEL

D 3
#include "param.h"
#include "buf.h"
#include "map.h"
#include "proc.h"
#include "mbuf.h"
#include "user.h"
#include "machine/reg.h"
#include "machine/pmap.h"
E 3
I 3
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/user.h>

#include <machine/reg.h>
D 5
#include <machine/pmap.h>
E 5
E 3

main()
{
	register struct proc *p = (struct proc *)0;
	register struct user *up = (struct user *)0;
D 5
	register pmap_hash_t hp = (pmap_hash_t)PMAP_HASH_UADDR;
E 5
	register struct vmmeter *vm = (struct vmmeter *)0;
	register int size, s, n;

D 7
	printf("#define\tP_LINK %d\n", &p->p_link);
	printf("#define\tP_RLINK %d\n", &p->p_rlink);
	printf("#define\tP_PRI %d\n", &p->p_pri);
E 7
I 7
	printf("#define\tP_FORW %d\n", &p->p_forw);
	printf("#define\tP_BACK %d\n", &p->p_back);
	printf("#define\tP_PRIORITY %d\n", &p->p_priority);
E 7
	printf("#define\tP_ADDR %d\n", &p->p_addr);
	printf("#define\tP_UPTE %d\n", p->p_md.md_upte);
	printf("#define\tU_PCB_REGS %d\n", up->u_pcb.pcb_regs);
	printf("#define\tU_PCB_FPREGS %d\n", &up->u_pcb.pcb_regs[F0]);
	printf("#define\tU_PCB_CONTEXT %d\n", &up->u_pcb.pcb_context);
	printf("#define\tU_PCB_ONFAULT %d\n", &up->u_pcb.pcb_onfault);
D 2
	printf("#define\tPMAP_HASH_LOW_OFFSET 0x%x\n", &hp->low);
	printf("#define\tPMAP_HASH_HIGH_OFFSET 0x%x\n", &hp->high);
E 2
I 2
D 5
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
E 5
I 5
	printf("#define\tU_PCB_SEGTAB %d\n", &up->u_pcb.pcb_segtab);
E 5
I 4
	printf("#define\tVM_MIN_ADDRESS 0x%x\n", VM_MIN_ADDRESS);
I 5
	printf("#define\tVM_MIN_KERNEL_ADDRESS 0x%x\n", VM_MIN_KERNEL_ADDRESS);
E 5
E 4
	printf("#define\tV_SWTCH %d\n", &vm->v_swtch);
	printf("#define\tSIGILL %d\n", SIGILL);
	printf("#define\tSIGFPE %d\n", SIGFPE);
	exit(0);
}
I 8

panic()
{
}
E 8
E 1
