h30879
s 00095/00005/00266
d D 8.3 93/12/06 20:27:13 akito 8 7
c sync up to hp300/hp300/vm_machdep.c     8.4 (Berkeley) 11/14/93
e
s 00004/00004/00267
d D 8.2 93/09/23 16:43:04 bostic 7 6
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00269
d D 8.1 93/06/10 22:27:00 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00268
d D 7.5 93/05/12 04:13:41 akito 5 4
c LUNA-II (68040 based LUNA) support
e
s 00004/00003/00264
d D 7.4 93/01/03 12:50:55 akito 4 3
c sync up to hp300/hp300/vm_machdep.c     7.14
e
s 00001/00001/00266
d D 7.3 92/12/10 13:54:19 akito 3 2
c include <luna68k/luna68k/pte.h>, not <pte.h>
e
s 00011/00011/00256
d D 7.2 92/10/11 11:07:57 bostic 2 1
c make kernel includes standard
e
s 00267/00000/00000
d D 7.1 92/06/15 06:38:55 fujita 1 0
c date and time created 92/06/15 06:38:55 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992 OMRON Corporation.
D 6
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: vm_machdep.c 1.21 91/04/06$
D 4
 * OMRON: $Id: vm_machdep.c,v 1.2 92/06/14 06:24:23 moti Exp $
E 4
I 4
D 8
 * from: hp300/hp300/vm_machdep.c	7.14 (Berkeley) 12/27/92
E 8
I 8
 * from: hp300/hp300/vm_machdep.c	8.4 (Berkeley) 11/14/93
E 8
E 4
 *
D 4
 * from: hp300/hp300/vm_machdep.c	7.12 (Berkeley) 6/5/92
 *
E 4
 *	%W% (Berkeley) %G%
 */

D 2
#include "param.h"
#include "systm.h"
#include "proc.h"
#include "malloc.h"
#include "buf.h"
#include "vnode.h"
#include "user.h"
E 2
I 2
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/malloc.h>
#include <sys/buf.h>
#include <sys/vnode.h>
#include <sys/user.h>
E 2

D 2
#include "../include/cpu.h"
E 2
I 2
#include <machine/cpu.h>
E 2

D 2
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "pte.h"
E 2
I 2
#include <vm/vm.h>
#include <vm/vm_kern.h>
D 3
#include <pte.h>
E 3
I 3
#include <luna68k/luna68k/pte.h>
E 3
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
	int offset;
	extern caddr_t getsp();
	extern char kstack[];
I 4

	p2->p_md.md_regs = p1->p_md.md_regs;
	p2->p_md.md_flags = (p1->p_md.md_flags & ~(MDP_AST|MDP_HPUXTRACE));
E 4

	/*
	 * Copy pcb and stack from proc p1 to p2. 
	 * We do this as cheaply as possible, copying only the active
	 * part of the stack.  The stack and pcb need to agree;
	 * this is tricky, as the final pcb is constructed by savectx,
	 * but its frame isn't yet on the stack when the stack is copied.
D 7
	 * swtch compensates for this when the child eventually runs.
E 7
I 7
	 * switch compensates for this when the child eventually runs.
E 7
	 * This should be done differently, with a single call
	 * that copies and updates the pcb+stack,
	 * replacing the bcopy and savectx.
	 */
	p2->p_addr->u_pcb = p1->p_addr->u_pcb;
	offset = getsp() - kstack;
	bcopy((caddr_t)kstack + offset, (caddr_t)p2->p_addr + offset,
	    (unsigned) ctob(UPAGES) - offset);

	PMAP_ACTIVATE(&p2->p_vmspace->vm_pmap, &up->u_pcb, 0);

	/*
	 * Arrange for a non-local goto when the new process
	 * is started, to resume here, returning nonzero from setjmp.
	 */
	if (savectx(up, 1)) {
		/*
		 * Return 1 in child.
		 */
		return (1);
	}
	return (0);
}

/*
 * cpu_exit is called as the last action during exit.
 * We release the address space and machine-dependent resources,
 * including the memory for the user structure and kernel stack.
D 7
 * Once finished, we call swtch_exit, which switches to a temporary
E 7
I 7
 * Once finished, we call switch_exit, which switches to a temporary
E 7
 * pcb and stack and never returns.  We block memory allocation
D 7
 * until swtch_exit has made things safe again.
E 7
I 7
 * until switch_exit has made things safe again.
E 7
 */
cpu_exit(p)
	struct proc *p;
{

	vmspace_free(p->p_vmspace);

	(void) splimp();
	kmem_free(kernel_map, (vm_offset_t)p->p_addr, ctob(UPAGES));
D 7
	swtch_exit();
E 7
I 7
	switch_exit();
E 7
	/* NOTREACHED */
}

/*
 * Dump the machine specific header information at the start of a core dump.
 */
cpu_coredump(p, vp, cred)
	struct proc *p;
	struct vnode *vp;
	struct ucred *cred;
{
	int error;

	return (vn_rdwr(UIO_WRITE, vp, (caddr_t) p->p_addr, ctob(UPAGES),
	    (off_t)0, UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, cred, (int *) NULL,
	    p));
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
	register struct pte *fpte, *tpte;

	if (size % CLBYTES)
		panic("pagemove");
	fpte = kvtopte(from);
	tpte = kvtopte(to);
	while (size > 0) {
		*tpte++ = *fpte;
		*(int *)fpte++ = PG_NV;
		TBIS(from);
		TBIS(to);
		from += NBPG;
		to += NBPG;
		size -= NBPG;
	}
I 5
#ifdef LUNA2
	DCIS();
#endif
E 5
}

/*
 * Map `size' bytes of physical memory starting at `paddr' into
 * kernel VA space at `vaddr'.  Read/write and cache-inhibit status
 * are specified by `prot'.
 */ 
physaccess(vaddr, paddr, size, prot)
	caddr_t vaddr, paddr;
	register int size, prot;
{
	register struct pte *pte;
	register u_int page;

	pte = kvtopte(vaddr);
	page = (u_int)paddr & PG_FRAME;
	for (size = btoc(size); size; size--) {
		*(int *)pte++ = PG_V | prot | page;
		page += NBPG;
	}
	TBIAS();
}

physunaccess(vaddr, size)
	caddr_t vaddr;
	register int size;
{
	register struct pte *pte;

	pte = kvtopte(vaddr);
	for (size = btoc(size); size; size--)
		*(int *)pte++ = PG_NV;
	TBIAS();
}

/*
 * Set a red zone in the kernel stack after the u. area.
 * We don't support a redzone right now.  It really isn't clear
 * that it is a good idea since, if the kernel stack were to roll
 * into a write protected page, the processor would lock up (since
 * it cannot create an exception frame) and we would get no useful
 * post-mortem info.  Currently, under the DEBUG option, we just
 * check at every clock interrupt to see if the current k-stack has
 * gone too far (i.e. into the "redzone" page) and if so, panic.
 * Look at _lev6intr in locore.s for more details.
 */
/*ARGSUSED*/
setredzone(pte, vaddr)
	struct pte *pte;
	caddr_t vaddr;
{
}

/*
 * Convert kernel VA to physical address
 */
kvtop(addr)
	register caddr_t addr;
{
	vm_offset_t va;

	va = pmap_extract(kernel_pmap, (vm_offset_t)addr);
	if (va == 0)
		panic("kvtop: zero page frame");
	return((int)va);
}

extern vm_map_t phys_map;

/*
 * Map an IO request into kernel virtual address space.
 *
 * XXX we allocate KVA space by using kmem_alloc_wait which we know
 * allocates space without backing physical memory.  This implementation
 * is a total crock, the multiple mappings of these physical pages should
 * be reflected in the higher-level VM structures to avoid problems.
 */
vmapbuf(bp)
	register struct buf *bp;
{
	register int npf;
	register caddr_t addr;
	register long flags = bp->b_flags;
	struct proc *p;
	int off;
	vm_offset_t kva;
	register vm_offset_t pa;

	if ((flags & B_PHYS) == 0)
		panic("vmapbuf");
D 8
	addr = bp->b_saveaddr = bp->b_un.b_addr;
E 8
I 8
	addr = bp->b_saveaddr = bp->b_data;
E 8
	off = (int)addr & PGOFSET;
	p = bp->b_proc;
	npf = btoc(round_page(bp->b_bcount + off));
	kva = kmem_alloc_wait(phys_map, ctob(npf));
D 8
	bp->b_un.b_addr = (caddr_t) (kva + off);
E 8
I 8
	bp->b_data = (caddr_t) (kva + off);
E 8
	while (npf--) {
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
 */
vunmapbuf(bp)
	register struct buf *bp;
{
I 8
	register caddr_t addr;
E 8
	register int npf;
D 8
	register caddr_t addr = bp->b_un.b_addr;
E 8
	vm_offset_t kva;

	if ((bp->b_flags & B_PHYS) == 0)
		panic("vunmapbuf");
I 8
	addr = bp->b_data;
E 8
	npf = btoc(round_page(bp->b_bcount + ((int)addr & PGOFSET)));
	kva = (vm_offset_t)((int)addr & ~PGOFSET);
	kmem_free_wakeup(phys_map, kva, ctob(npf));
D 8
	bp->b_un.b_addr = bp->b_saveaddr;
E 8
I 8
	bp->b_data = bp->b_saveaddr;
E 8
	bp->b_saveaddr = NULL;
}
I 8

#ifdef MAPPEDCOPY
u_int mappedcopysize = 4096;

mappedcopyin(fromp, top, count)
	register char *fromp, *top;
	register int count;
{
	register vm_offset_t kva, upa;
	register int off, len;
	int alignable;
	pmap_t upmap;
	extern caddr_t CADDR1;

	kva = (vm_offset_t) CADDR1;
	off = (vm_offset_t)fromp & PAGE_MASK;
	alignable = (off == ((vm_offset_t)top & PAGE_MASK));
	upmap = vm_map_pmap(&curproc->p_vmspace->vm_map);
	while (count > 0) {
		/*
		 * First access of a page, use fubyte to make sure
		 * page is faulted in and read access allowed.
		 */
		if (fubyte(fromp) == -1)
			return (EFAULT);
		/*
		 * Map in the page and bcopy data in from it
		 */
		upa = pmap_extract(upmap, trunc_page(fromp));
		if (upa == 0)
			panic("mappedcopyin");
		len = min(count, PAGE_SIZE-off);
		pmap_enter(kernel_pmap, kva, upa, VM_PROT_READ, TRUE);
		if (len == PAGE_SIZE && alignable && off == 0)
			copypage(kva, top);
		else
			bcopy((caddr_t)(kva+off), top, len);
		fromp += len;
		top += len;
		count -= len;
		off = 0;
	}
	pmap_remove(kernel_pmap, kva, kva+PAGE_SIZE);
	return (0);
}

mappedcopyout(fromp, top, count)
	register char *fromp, *top;
	register int count;
{
	register vm_offset_t kva, upa;
	register int off, len;
	int alignable;
	pmap_t upmap;
	extern caddr_t CADDR2;

	kva = (vm_offset_t) CADDR2;
	off = (vm_offset_t)top & PAGE_MASK;
	alignable = (off == ((vm_offset_t)fromp & PAGE_MASK));
	upmap = vm_map_pmap(&curproc->p_vmspace->vm_map);
	while (count > 0) {
		/*
		 * First access of a page, use subyte to make sure
		 * page is faulted in and write access allowed.
		 */
		if (subyte(top, *fromp) == -1)
			return (EFAULT);
		/*
		 * Map in the page and bcopy data out to it
		 */
		upa = pmap_extract(upmap, trunc_page(top));
		if (upa == 0)
			panic("mappedcopyout");
		len = min(count, PAGE_SIZE-off);
		pmap_enter(kernel_pmap, kva, upa,
			   VM_PROT_READ|VM_PROT_WRITE, TRUE);
		if (len == PAGE_SIZE && alignable && off == 0)
			copypage(fromp, kva);
		else
			bcopy(fromp, (caddr_t)(kva+off), len);
		fromp += len;
		top += len;
		count -= len;
		off = 0;
	}
	pmap_remove(kernel_pmap, kva, kva+PAGE_SIZE);
	return (0);
}
#endif
E 8
E 1
