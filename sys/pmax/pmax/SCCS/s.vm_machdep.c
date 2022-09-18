h41461
s 00029/00004/00233
d D 8.3 94/01/04 17:31:42 mckusick 10 9
c fix a bug where after a "swapin" the user area has a different
c virtual to physical mapping (see comments in code). (from Ralph)
e
s 00003/00003/00234
d D 8.2 93/11/30 16:19:39 mckusick 9 8
c swtch => switch
e
s 00002/00002/00235
d D 8.1 93/06/10 23:08:05 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00235
d D 7.7 93/05/09 15:59:44 ralph 7 6
c new improved pmap changes
e
s 00011/00011/00224
d D 7.6 92/10/11 11:23:26 bostic 6 5
c make kernel includes standard
e
s 00008/00001/00227
d D 7.5 92/03/15 19:14:14 ralph 5 4
c snapshot FP regs on core dump
e
s 00016/00000/00212
d D 7.4 92/03/13 17:15:58 torek 4 3
c add cpu_coredump
e
s 00001/00001/00211
d D 7.3 92/02/29 17:54:18 ralph 3 2
c remove p_regs
e
s 00009/00001/00203
d D 7.2 92/02/29 14:12:02 ralph 2 1
c copy floating point registers on fork if still in FP chip.
e
s 00204/00000/00000
d D 7.1 92/01/07 17:29:25 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: vm_machdep.c 1.21 91/04/06$
 *
 *	%W% (Berkeley) %G%
 */

D 6
#include "param.h"
#include "systm.h"
#include "proc.h"
#include "malloc.h"
#include "buf.h"
I 4
#include "vnode.h"
E 4
#include "user.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/malloc.h>
#include <sys/buf.h>
#include <sys/vnode.h>
#include <sys/user.h>
E 6

D 6
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
E 6
I 6
#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
E 6

D 2
#include "pte.h"
E 2
I 2
D 6
#include "../include/pte.h"
E 6
I 6
#include <machine/pte.h>
E 6
E 2

/*
 * Finish a fork operation, with process p2 nearly set up.
 * Copy and update the kernel stack and pcb, making the child
 * ready to run, and marking it so that it can return differently
 * than the parent.  Returns 1 in the child process, 0 in the parent.
 * We currently double-map the user area so that the stack is at the same
 * address in each process; in the future we will probably relocate
 * the frame pointers on the stack after copying.
 */
cpu_fork(p1, p2)
	register struct proc *p1, *p2;
{
	register struct user *up = p2->p_addr;
	register pt_entry_t *pte;
	register int i;
I 2
	extern struct proc *machFPCurProcPtr;
E 2

D 3
	p2->p_regs = up->u_pcb.pcb_regs;
E 3
I 3
	p2->p_md.md_regs = up->u_pcb.pcb_regs;
E 3
	p2->p_md.md_flags = p1->p_md.md_flags & (MDP_FPUSED | MDP_ULTRIX);

	/*
D 10
	 * Convert the user struct virtual address to a physical one
	 * and cache it in the proc struct. Note: if the phyical address
	 * can change (due to memory compaction in kmem_alloc?),
	 * we will have to update things.
E 10
I 10
	 * Cache the PTEs for the user area in the machine dependent
	 * part of the proc struct so cpu_switch() can quickly map in
	 * the user struct and kernel stack. Note: if the virtual address
	 * translation changes (e.g. swapout) we have to update this.
E 10
	 */
	pte = kvtopte(up);
	for (i = 0; i < UPAGES; i++) {
		p2->p_md.md_upte[i] = pte->pt_entry & ~PG_G;
		pte++;
	}
I 2

	/*
	 * Copy floating point state from the FP chip if this process
	 * has state stored there.
	 */
	if (p1 == machFPCurProcPtr)
		MachSaveCurFPState(p1);
E 2

	/*
	 * Copy pcb and stack from proc p1 to p2. 
	 * We do this as cheaply as possible, copying only the active
	 * part of the stack.  The stack and pcb need to agree;
	 */
	p2->p_addr->u_pcb = p1->p_addr->u_pcb;
I 7
	/* cache segtab for ULTBMiss() */
	p2->p_addr->u_pcb.pcb_segtab = (void *)p2->p_vmspace->vm_pmap.pm_segtab;
E 7

	/*
	 * Arrange for a non-local goto when the new process
	 * is started, to resume here, returning nonzero from setjmp.
	 */
#ifdef DIAGNOSTIC
	if (p1 != curproc)
		panic("cpu_fork: curproc");
#endif
	if (copykstack(up)) {
		/*
		 * Return 1 in child.
		 */
		return (1);
	}
	return (0);
I 10
}

/*
 * Finish a swapin operation.
 * We neded to update the cached PTEs for the user area in the
 * machine dependent part of the proc structure.
 */
void
cpu_swapin(p)
	register struct proc *p;
{
	register struct user *up = p->p_addr;
	register pt_entry_t *pte;
	register int i;

	/*
	 * Cache the PTEs for the user area in the machine dependent
	 * part of the proc struct so cpu_switch() can quickly map in
	 * the user struct and kernel stack.
	 */
	pte = kvtopte(up);
	for (i = 0; i < UPAGES; i++) {
		p->p_md.md_upte[i] = pte->pt_entry & ~PG_G;
		pte++;
	}
E 10
}

/*
 * cpu_exit is called as the last action during exit.
 * We release the address space and machine-dependent resources,
 * including the memory for the user structure and kernel stack.
D 9
 * Once finished, we call swtch_exit, which switches to a temporary
E 9
I 9
 * Once finished, we call switch_exit, which switches to a temporary
E 9
 * pcb and stack and never returns.  We block memory allocation
D 9
 * until swtch_exit has made things safe again.
E 9
I 9
 * until switch_exit has made things safe again.
E 9
 */
cpu_exit(p)
	struct proc *p;
{
	extern struct proc *machFPCurProcPtr;

	if (machFPCurProcPtr == p)
		machFPCurProcPtr = (struct proc *)0;

	vmspace_free(p->p_vmspace);

	(void) splhigh();
	kmem_free(kernel_map, (vm_offset_t)p->p_addr, ctob(UPAGES));
D 9
	swtch_exit();
E 9
I 9
	switch_exit();
E 9
	/* NOTREACHED */
I 4
}

/*
 * Dump the machine specific header information at the start of a core dump.
D 5
 * XXX should snapshot FPU here?
E 5
 */
cpu_coredump(p, vp, cred)
	struct proc *p;
	struct vnode *vp;
	struct ucred *cred;
{
I 5
	extern struct proc *machFPCurProcPtr;

	/*
	 * Copy floating point state from the FP chip if this process
	 * has state stored there.
	 */
	if (p == machFPCurProcPtr)
		MachSaveCurFPState(p);
E 5

	return (vn_rdwr(UIO_WRITE, vp, (caddr_t)p->p_addr, ctob(UPAGES),
	    (off_t)0, UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, cred, (int *)NULL,
	    p));
E 4
}

/*
 * Move pages from one kernel virtual address to another.
 * Both addresses are assumed to reside in the Sysmap,
 * and size must be a multiple of CLSIZE.
 */
pagemove(from, to, size)
	register caddr_t from, to;
	int size;
{
	register pt_entry_t *fpte, *tpte;

	if (size % CLBYTES)
		panic("pagemove");
	fpte = kvtopte(from);
	tpte = kvtopte(to);
	while (size > 0) {
		MachTLBFlushAddr(from);
		MachTLBUpdate(to, *fpte);
		*tpte++ = *fpte;
		fpte->pt_entry = 0;
		fpte++;
		size -= NBPG;
		from += NBPG;
		to += NBPG;
	}
}

extern vm_map_t phys_map;

/*
 * Map an IO request into kernel virtual address space.  Requests fall into
 * one of five catagories:
 *
 *	B_PHYS|B_UAREA:	User u-area swap.
 *			Address is relative to start of u-area (p_addr).
 *	B_PHYS|B_PAGET:	User page table swap.
 *			Address is a kernel VA in usrpt (Usrptmap).
 *	B_PHYS|B_DIRTY:	Dirty page push.
 *			Address is a VA in proc2's address space.
 *	B_PHYS|B_PGIN:	Kernel pagein of user pages.
 *			Address is VA in user's address space.
 *	B_PHYS:		User "raw" IO request.
 *			Address is VA in user's address space.
 *
 * All requests are (re)mapped into kernel VA space via the phys_map
 */
vmapbuf(bp)
	register struct buf *bp;
{
	register caddr_t addr;
	register vm_size_t sz;
	struct proc *p;
	int off;
	vm_offset_t kva;
	register vm_offset_t pa;

	if ((bp->b_flags & B_PHYS) == 0)
		panic("vmapbuf");
	addr = bp->b_saveaddr = bp->b_un.b_addr;
	off = (int)addr & PGOFSET;
	p = bp->b_proc;
	sz = round_page(bp->b_bcount + off);
	kva = kmem_alloc_wait(phys_map, sz);
	bp->b_un.b_addr = (caddr_t) (kva + off);
	sz = atop(sz);
	while (sz--) {
		pa = pmap_extract(vm_map_pmap(&p->p_vmspace->vm_map),
			(vm_offset_t)addr);
		if (pa == 0)
			panic("vmapbuf: null page frame");
		pmap_enter(vm_map_pmap(phys_map), kva, trunc_page(pa),
			VM_PROT_READ|VM_PROT_WRITE, TRUE);
		addr += PAGE_SIZE;
		kva += PAGE_SIZE;
	}
}

/*
 * Free the io map PTEs associated with this IO operation.
 * We also invalidate the TLB entries and restore the original b_addr.
 */
vunmapbuf(bp)
	register struct buf *bp;
{
	register caddr_t addr = bp->b_un.b_addr;
	register vm_size_t sz;
	vm_offset_t kva;

	if ((bp->b_flags & B_PHYS) == 0)
		panic("vunmapbuf");
	sz = round_page(bp->b_bcount + ((int)addr & PGOFSET));
	kva = (vm_offset_t)((int)addr & ~PGOFSET);
	kmem_free_wakeup(phys_map, kva, sz);
	bp->b_un.b_addr = bp->b_saveaddr;
	bp->b_saveaddr = NULL;
}
E 1
