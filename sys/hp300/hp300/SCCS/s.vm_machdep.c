h54257
s 00018/00012/00352
d D 8.6 94/01/12 14:39:02 hibler 20 19
c use pmap routines to do pagemove.
e
s 00000/00002/00364
d D 8.5 94/01/04 22:27:20 bostic 19 18
c lint
e
s 00089/00000/00277
d D 8.4 93/11/14 14:23:40 hibler 18 17
c MAPPEDCOPY code: routines for mapped copyin/copyout
e
s 00004/00004/00273
d D 8.3 93/09/23 16:37:34 bostic 17 16
c changes for 4.4BSD-Lite requested by USL
e
s 00005/00004/00272
d D 8.2 93/09/21 07:41:06 bostic 16 15
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00274
d D 8.1 93/06/10 21:41:45 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00004/00269
d D 7.14 92/12/27 09:55:12 hibler 14 13
c cleanup
e
s 00011/00011/00262
d D 7.13 92/10/11 09:42:51 bostic 13 12
c make kernel includes standard
e
s 00005/00016/00268
d D 7.12 92/06/05 15:36:59 hibler 12 11
c merge latest Utah hp300 code including 68040 support
e
s 00025/00000/00259
d D 7.11 92/03/13 17:03:51 mckusick 11 10
c add cpu_coredump for machine dependent coredump state
e
s 00037/00006/00222
d D 7.10 91/05/07 10:00:49 hibler 10 9
c DIO-II support
c fix for fork code
e
s 00071/00001/00157
d D 7.9 91/05/04 19:36:56 karels 9 8
c add cpu_fork, cpu_exit
e
s 00009/00010/00149
d D 7.8 91/04/20 17:29:41 karels 8 7
c fix includes; new proc struct
e
s 00011/00011/00148
d D 7.7 90/12/16 16:36:49 bostic 7 6
c kernel reorg
e
s 00044/00443/00115
d D 7.6 90/12/05 18:53:43 mckusick 6 5
c update from Mike Hibler for new VM and other machine support
e
s 00003/00005/00555
d D 7.5 90/06/21 16:22:23 mckusick 5 4
c chgprot returns error code
e
s 00001/00002/00559
d D 7.4 90/06/05 23:15:05 mckusick 4 3
c return actual error code
e
s 00000/00006/00561
d D 7.3 90/05/25 16:05:06 mckusick 3 2
c "update from Mike Hibler at Utah"
e
s 00002/00004/00565
d D 7.2 90/05/16 20:15:54 mckusick 2 1
c mounttab is gone!
e
s 00569/00000/00000
d D 7.1 90/05/08 18:09:15 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 15
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 10
 * from: Utah $Hdr: vm_machdep.c 1.18 89/08/23$
E 10
I 10
 * from: Utah $Hdr: vm_machdep.c 1.21 91/04/06$
E 10
 *
 *	%W% (Berkeley) %G%
 */

D 7
#include "param.h"
#include "systm.h"
#include "user.h"
#include "proc.h"
#include "cmap.h"
D 3
#include "mount.h"
E 3
D 2
#include "../ufs/ufsmount.h"
E 2
D 6
#include "vm.h"
#include "text.h"
E 6
#include "malloc.h"
#include "buf.h"
E 7
I 7
D 8
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/cmap.h"
#include "sys/malloc.h"
#include "sys/buf.h"
E 8
I 8
D 13
#include "param.h"
#include "systm.h"
#include "proc.h"
#include "malloc.h"
#include "buf.h"
I 11
#include "vnode.h"
E 11
I 9
#include "user.h"
E 13
I 13
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/malloc.h>
#include <sys/buf.h>
#include <sys/vnode.h>
#include <sys/user.h>
E 13
E 9
E 8
E 7

D 7
#include "cpu.h"
E 7
I 7
D 13
#include "../include/cpu.h"
E 13
I 13
#include <machine/cpu.h>
E 13
E 7
D 6
#include "pte.h"
E 6

D 6
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
E 6
I 6
D 7
#include "../vm/vm_param.h"
#include "../vm/pmap.h"
#include "../vm/vm_map.h"
E 7
I 7
D 8
#include "vm/vm_param.h"
E 8
I 8
D 13
#include "vm/vm.h"
E 8
D 9
#include "vm/pmap.h"
E 9
I 9
#include "vm/vm_kern.h"
E 9
D 8
#include "vm/vm_map.h"
E 8
I 8
#include "pte.h"
E 13
I 13
#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <hp300/hp300/pte.h>
E 13
I 9

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
D 10
	int foo, offset;
E 10
I 10
	int offset;
	extern caddr_t getsp();
E 10
	extern char kstack[];

I 14
	p2->p_md.md_regs = p1->p_md.md_regs;
	p2->p_md.md_flags = (p1->p_md.md_flags & ~(MDP_AST|MDP_HPUXTRACE));

E 14
	/*
	 * Copy pcb and stack from proc p1 to p2. 
	 * We do this as cheaply as possible, copying only the active
	 * part of the stack.  The stack and pcb need to agree;
	 * this is tricky, as the final pcb is constructed by savectx,
	 * but its frame isn't yet on the stack when the stack is copied.
D 17
	 * swtch compensates for this when the child eventually runs.
E 17
I 17
	 * switch compensates for this when the child eventually runs.
E 17
	 * This should be done differently, with a single call
	 * that copies and updates the pcb+stack,
	 * replacing the bcopy and savectx.
	 */
	p2->p_addr->u_pcb = p1->p_addr->u_pcb;
D 10
	offset = (caddr_t)&foo - kstack;
E 10
I 10
	offset = getsp() - kstack;
E 10
	bcopy((caddr_t)kstack + offset, (caddr_t)p2->p_addr + offset,
	    (unsigned) ctob(UPAGES) - offset);
D 10
	p2->p_regs = p1->p_regs;
E 10

	PMAP_ACTIVATE(&p2->p_vmspace->vm_pmap, &up->u_pcb, 0);

	/*
D 10
	 * 
E 10
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
D 17
 * Once finished, we call swtch_exit, which switches to a temporary
E 17
I 17
 * Once finished, we call switch_exit, which switches to a temporary
E 17
 * pcb and stack and never returns.  We block memory allocation
D 17
 * until swtch_exit has made things safe again.
E 17
I 17
 * until switch_exit has made things safe again.
E 17
 */
cpu_exit(p)
	struct proc *p;
{

	vmspace_free(p->p_vmspace);

	(void) splimp();
	kmem_free(kernel_map, (vm_offset_t)p->p_addr, ctob(UPAGES));
D 17
	swtch_exit();
E 17
I 17
	switch_exit();
E 17
	/* NOTREACHED */
I 11
}

/*
 * Dump the machine specific header information at the start of a core dump.
 */
cpu_coredump(p, vp, cred)
	struct proc *p;
	struct vnode *vp;
	struct ucred *cred;
{
D 19
	int error;

E 19
#ifdef HPUXCOMPAT
	/*
D 14
	 * BLETCH!  If we loaded from an HPUX format binary file
	 * we have to dump an HPUX style user struct so that the
	 * HPUX debuggers can grok it.
E 14
I 14
	 * If we loaded from an HP-UX format binary file we dump enough
	 * of an HP-UX style user struct so that the HP-UX debuggers can
	 * grok it.
E 14
	 */
D 14
	if (p->p_addr->u_pcb.pcb_flags & PCB_HPUXBIN)
E 14
I 14
	if (p->p_md.md_flags & MDP_HPUX)
E 14
		return (hpuxdumpu(vp, cred));
#endif
	return (vn_rdwr(UIO_WRITE, vp, (caddr_t) p->p_addr, ctob(UPAGES),
	    (off_t)0, UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, cred, (int *) NULL,
	    p));
E 11
}
E 9
E 8
E 7
E 6

/*
D 6
 * Check for valid program size
 * NB - Check data and data growth separately as they may overflow 
 * when summed together.
 */
chksize(ts, ids, uds, ss)
	unsigned ts, ids, uds, ss;
{
	extern unsigned maxtsize;

	if (ctob(ts) > maxtsize ||
	    ctob(ids) > u.u_rlimit[RLIMIT_DATA].rlim_cur ||
	    ctob(uds) > u.u_rlimit[RLIMIT_DATA].rlim_cur ||
	    ctob(ids + uds) > u.u_rlimit[RLIMIT_DATA].rlim_cur ||
	    ctob(ss) > u.u_rlimit[RLIMIT_STACK].rlim_cur) {
D 4
		u.u_error = ENOMEM;
		return (1);
E 4
I 4
		return (ENOMEM);
E 4
	}
	return (0);
}

/*ARGSUSED*/
newptes(pte, v, size)
	struct pte *pte;
	u_int v;
	register int size;
{
	register caddr_t a;

#ifdef lint
	pte = pte;
#endif
	if (size >= 8)
		TBIAU();
	else {
		a = ptob(v);
		while (size > 0) {
			TBIS(a);
			a += NBPG;
			size--;
		}
	}
	DCIU();
}

/*
 * Change protection codes of text segment.
 * Have to flush translation buffer since this
 * affect virtual memory mapping of current process.
 */
chgprot(addr, tprot)
	caddr_t addr;
	long tprot;
{
	unsigned v;
	int tp;
	register struct pte *pte;
	register struct cmap *c;

	v = clbase(btop(addr));
D 5
	if (!isatsv(u.u_procp, v)) {
		u.u_error = EFAULT;
		return (0);
	}
E 5
I 5
	if (!isatsv(u.u_procp, v))
		return (EFAULT);
E 5
	tp = vtotp(u.u_procp, v);
	pte = tptopte(u.u_procp, tp);
	if (pte->pg_fod == 0 && pte->pg_pfnum) {
		c = &cmap[pgtocm(pte->pg_pfnum)];
D 2
		if (c->c_blkno && c->c_mdev != MSWAPX)
			munhash(mounttab[c->c_mdev].um_devvp,
			    (daddr_t)(u_long)c->c_blkno);
E 2
I 2
		if (c->c_blkno)
			munhash(c->c_vp, (daddr_t)(u_long)c->c_blkno);
E 2
	}
	*(u_int *)pte &= ~PG_PROT;
	*(u_int *)pte |= tprot;
	TBIS(addr);
D 5
	return (1);
E 5
I 5
	return (0);
E 5
}

settprot(tprot)
	long tprot;
{
	register u_int *pte, i;

	pte = (u_int *)u.u_procp->p_p0br;
	for (i = 0; i < u.u_tsize; i++, pte++) {
		*pte &= ~PG_PROT;
		*pte |= tprot;
	}
	TBIAU();
}

/*
 * Simulate effect of VAX region length registers.
 * The one case where we must do anything is if a region has shrunk.
 * In that case we must invalidate all the PTEs for the no longer valid VAs.
 */
setptlr(region, nlen)
	int nlen;
{
	register struct pte *pte;
	register int change;
	int olen;

	if (region == 0) {
		olen = u.u_pcb.pcb_p0lr;
		u.u_pcb.pcb_p0lr = nlen;
	} else {
		olen = P1PAGES - u.u_pcb.pcb_p1lr;
		u.u_pcb.pcb_p1lr = nlen;
		nlen = P1PAGES - nlen;
	}
	if ((change = olen - nlen) <= 0)
		return;
	if (region == 0)
		pte = u.u_pcb.pcb_p0br + u.u_pcb.pcb_p0lr;
	else
		pte = u.u_pcb.pcb_p1br + u.u_pcb.pcb_p1lr - change;
	do {
		*(u_int *)pte++ = PG_NV;
	} while (--change);
	/* short cut newptes */
	TBIAU();
	DCIU();
}

/*
 * Map `size' bytes of physical memory starting at `paddr' into
 * kernel VA space using PTEs starting at `pte'.  Read/write and
 * cache-inhibit status are specified by `prot'.
 */ 
physaccess(pte, paddr, size, prot)
	register struct pte *pte;
	caddr_t paddr;
	register int size;
{
	register u_int page;

	page = (u_int)paddr & PG_FRAME;
	for (size = btoc(size); size; size--) {
		*(int *)pte = PG_V | prot | page;
		page += NBPG;
		pte++;
	}
	TBIAS();
}

/*
E 6
 * Move pages from one kernel virtual address to another.
 * Both addresses are assumed to reside in the Sysmap,
 * and size must be a multiple of CLSIZE.
 */
pagemove(from, to, size)
	register caddr_t from, to;
	int size;
{
D 20
	register struct pte *fpte, *tpte;
E 20
I 20
	register vm_offset_t pa;
E 20

D 20
	if (size % CLBYTES)
E 20
I 20
#ifdef DEBUG
	if (size & CLOFSET)
E 20
		panic("pagemove");
D 20
	fpte = kvtopte(from);
	tpte = kvtopte(to);
E 20
I 20
#endif
E 20
	while (size > 0) {
D 20
		*tpte++ = *fpte;
		*(int *)fpte++ = PG_NV;
		TBIS(from);
		TBIS(to);
		from += NBPG;
		to += NBPG;
		size -= NBPG;
E 20
I 20
		pa = pmap_extract(kernel_pmap, (vm_offset_t)from);
#ifdef DEBUG
		if (pa == 0)
			panic("pagemove 2");
		if (pmap_extract(kernel_pmap, (vm_offset_t)to) != 0)
			panic("pagemove 3");
#endif
		pmap_remove(kernel_pmap,
			    (vm_offset_t)from, (vm_offset_t)from + PAGE_SIZE);
		pmap_enter(kernel_pmap,
			   (vm_offset_t)to, pa, VM_PROT_READ|VM_PROT_WRITE, 1);
		from += PAGE_SIZE;
		to += PAGE_SIZE;
		size -= PAGE_SIZE;
E 20
	}
I 6
D 10
	/* buffer pages not CI with new VM */
E 10
D 20
	DCIS();
E 20
I 10
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
E 10
E 6
}

D 6
#ifdef KGDB
E 6
/*
D 6
 * Change protections on kernel pages from addr to addr+size
 * (presumably so debugger can plant a breakpoint).
 * All addresses are assumed to reside in the Sysmap,
E 6
I 6
 * Set a red zone in the kernel stack after the u. area.
 * We don't support a redzone right now.  It really isn't clear
 * that it is a good idea since, if the kernel stack were to roll
 * into a write protected page, the processor would lock up (since
 * it cannot create an exception frame) and we would get no useful
 * post-mortem info.  Currently, under the DEBUG option, we just
 * check at every clock interrupt to see if the current k-stack has
 * gone too far (i.e. into the "redzone" page) and if so, panic.
 * Look at _lev6intr in locore.s for more details.
E 6
 */
D 6
chgkprot(addr, size, rw)
	register caddr_t addr;
	int size, rw;
E 6
I 6
/*ARGSUSED*/
setredzone(pte, vaddr)
	struct pte *pte;
	caddr_t vaddr;
E 6
{
D 6
	register struct pte *pte;

	pte = &Sysmap[btop(addr)];
	while (size > 0) {
		pte->pg_prot = rw == B_WRITE? 0 : 1;
		TBIS(addr);
		addr += NBPG;
		size -= NBPG;
		pte++;
	}
E 6
}
D 6
#endif
E 6

/*
D 6
 * The probe[rw] routines should probably be redone in assembler
 * for efficiency.
 */
prober(addr)
	register u_int addr;
{
	register int page;
	register struct proc *p;

	if (addr >= USRSTACK)
		return(0);
#ifdef HPUXCOMPAT
	if (ISHPMMADDR(addr))
		addr = HPMMBASEADDR(addr);
#endif
	page = btop(addr);
	p = u.u_procp;
	if (page < dptov(p, p->p_dsize) || page > sptov(p, p->p_ssize))
		return(1);
#ifdef MAPMEM
	if (page < dptov(p, p->p_dsize+p->p_mmsize) &&
	    (*(int *)vtopte(p, page) & (PG_FOD|PG_V)) == (PG_FOD|PG_V))
		return(1);
#endif
	return(0);
}

probew(addr)
	register u_int addr;
{
	register int page;
	register struct proc *p;

	if (addr >= USRSTACK)
		return(0);
#ifdef HPUXCOMPAT
	if (ISHPMMADDR(addr))
		addr = HPMMBASEADDR(addr);
#endif
	page = btop(addr);
	p = u.u_procp;
	if (page < dptov(p, p->p_dsize) || page > sptov(p, p->p_ssize))
		return((*(int *)vtopte(p, page) & PG_PROT) == PG_RW);
#ifdef MAPMEM
	if (page < dptov(p, p->p_dsize+p->p_mmsize))
		return((*(int *)vtopte(p, page) & (PG_FOD|PG_V|PG_PROT))
		       == (PG_FOD|PG_V|PG_RW));
#endif
	return(0);
}

/*
 * NB: assumes a physically contiguous kernel page table
 *     (makes life a LOT simpler).
 */
kernacc(addr, count, rw)
	register caddr_t addr;
	int count, rw;
{
	register struct ste *ste;
	register struct pte *pte;
	register u_int ix, cnt;
	extern long Syssize;

	if (count <= 0)
		return(0);
	ix = ((int)addr & SG_IMASK) >> SG_ISHIFT;
	cnt = (((int)addr + count + (1<<SG_ISHIFT)-1) & SG_IMASK) >> SG_ISHIFT;
	cnt -= ix;
	for (ste = &Sysseg[ix]; cnt; cnt--, ste++)
		/* should check SG_PROT, but we have no RO segments now */
		if (ste->sg_v == 0)
			return(0);
	ix = btop(addr);
	cnt = btop(addr+count+NBPG-1);
	if (cnt > (u_int)&Syssize)
		return(0);
	cnt -= ix;
	for (pte = &Sysmap[ix]; cnt; cnt--, pte++)
		if (pte->pg_v == 0 || (rw == B_WRITE && pte->pg_prot == 1))
			return(0);
	return(1);
}

useracc(addr, count, rw)
	register caddr_t addr;
	unsigned count;
{
	register int (*func)();
	register u_int addr2;
	extern int prober(), probew();

	if (count <= 0)
		return(0);
	addr2 = (u_int) addr;
	addr += count;
	func = (rw == B_READ) ? prober : probew;
	do {
		if ((*func)(addr2) == 0)
			return(0);
		addr2 = (addr2 + NBPG) & ~PGOFSET;
	} while (addr2 < (u_int)addr);
	return(1);
}

/*
E 6
 * Convert kernel VA to physical address
 */
kvtop(addr)
	register caddr_t addr;
{
D 6
	register int pf;
E 6
I 6
	vm_offset_t va;
E 6

D 6
	pf = Sysmap[btop(addr)].pg_pfnum;
	if (pf == 0)
E 6
I 6
	va = pmap_extract(kernel_pmap, (vm_offset_t)addr);
	if (va == 0)
E 6
		panic("kvtop: zero page frame");
D 6
	return((u_int)ptob(pf) + ((int)addr & PGOFSET));
E 6
I 6
	return((int)va);
E 6
}

D 6
struct ste *
vtoste(p, va)
	register struct proc *p;
	register u_int va;
{
	register struct ste *ste;
E 6
I 6
extern vm_map_t phys_map;
E 6

D 6
	ste = (struct ste *)((u_int)p->p_p0br + p->p_szpt * NBPG);
	return(ste + ((va & SG_IMASK) >> SG_ISHIFT));
}

initustp(p)
	register struct proc *p;
{
	return((int)Usrptmap[btokmx(p->p_p0br) + p->p_szpt].pg_pfnum);
}

E 6
/*
D 6
 * Initialize segment table to reflect PTEs in Usrptmap.
 * Segment table address is given by Usrptmap index of p_szpt.
 */
initsegt(p)
	register struct proc *p;
{
	register int i, k, sz;
	register struct ste *ste;
	extern struct ste *vtoste();

	k = btokmx(p->p_p0br);
	ste = vtoste(p, 0);
	/* text and data */
	sz = ctopt(p->p_tsize + p->p_dsize + p->p_mmsize);
	for (i = 0; i < sz; i++, ste++) {
		*(int *)ste = SG_RW | SG_V;
		ste->sg_pfnum = Usrptmap[k++].pg_pfnum;
	}
	/*
	 * Bogus!  The kernelmap may map unused PT pages
	 * (since we don't shrink PTs) so we need to skip over
	 * those STEs.  We should really free the unused PT
	 * pages in expand().
	 */
	sz += ctopt(p->p_ssize + HIGHPAGES);
	if (sz < p->p_szpt)
		k += p->p_szpt - sz;
	/* hole */
	sz = NPTEPG - ctopt(p->p_ssize + HIGHPAGES);
	for ( ; i < sz; i++, ste++)
		*(int *)ste = SG_NV;
	/* stack and u-area */
	sz = NPTEPG;
	for ( ; i < sz; i++, ste++) {
		*(int *)ste = SG_RW | SG_V;
		ste->sg_pfnum = Usrptmap[k++].pg_pfnum;
	}
}

/*
 * Allocate/free cache-inhibited physical memory.
 * Assumes that malloc returns page aligned memory for requests which are
 * a multiple of the page size.  Hence, size must be such a multiple.
 */
caddr_t
cialloc(sz)
	int sz;
{
	caddr_t kva;
	register int npg, *pte;

	if (sz & CLOFSET)
		return(NULL);
	kva = (caddr_t)malloc(sz, M_DEVBUF, M_NOWAIT);
	if (kva) {
		if (!claligned(kva))
			panic("cialloc");
		pte = (int *)kvtopte(kva);
		npg = btoc(sz);
		while (--npg >= 0)
			*pte++ |= PG_CI;
		TBIAS();
	}
	return(kva);
}

cifree(kva, sz)
	caddr_t kva;
	int sz;
{
	register int npg, *pte;

	if (sz & CLOFSET)
		panic("cifree");
	pte = (int *)kvtopte(kva);
	npg = btoc(sz);
	while (--npg >= 0)
		*pte++ &= ~PG_CI;
	TBIAS();
	free(kva, M_DEVBUF);
}

extern char usrio[];
extern struct pte Usriomap[];
struct map *useriomap;
int usriowanted;

/*
E 6
D 12
 * Map an IO request into kernel virtual address space.  Requests fall into
 * one of five catagories:
E 12
I 12
 * Map an IO request into kernel virtual address space.
E 12
 *
D 12
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
 * All requests are (re)mapped into kernel VA space via the useriomap
 * (a name with only slightly more meaning than "kernelmap")
E 12
I 12
 * XXX we allocate KVA space by using kmem_alloc_wait which we know
 * allocates space without backing physical memory.  This implementation
 * is a total crock, the multiple mappings of these physical pages should
 * be reflected in the higher-level VM structures to avoid problems.
E 12
 */
vmapbuf(bp)
	register struct buf *bp;
{
D 6
	register int npf, a;
E 6
I 6
	register int npf;
E 6
	register caddr_t addr;
D 6
	register struct pte *pte, *iopte;
E 6
	register long flags = bp->b_flags;
	struct proc *p;
D 6
	int off, s;
E 6
I 6
	int off;
	vm_offset_t kva;
	register vm_offset_t pa;
E 6

	if ((flags & B_PHYS) == 0)
		panic("vmapbuf");
D 6
	/*
	 * Find PTEs for the area to be mapped
	 */
	p = flags&B_DIRTY ? &proc[2] : bp->b_proc;
	addr = bp->b_un.b_addr;
	if (flags & B_UAREA)
		pte = &p->p_addr[btop(addr)];
	else if (flags & B_PAGET)
		pte = &Usrptmap[btokmx((struct pte *)addr)];
	else
		pte = vtopte(p, btop(addr));
	/*
	 * Allocate some kernel PTEs and load them
	 */
E 6
I 6
D 16
	addr = bp->b_saveaddr = bp->b_un.b_addr;
E 16
I 16
	addr = bp->b_saveaddr = bp->b_data;
E 16
E 6
	off = (int)addr & PGOFSET;
D 6
	npf = btoc(bp->b_bcount + off);
	s = splbio();
	while ((a = rmalloc(useriomap, npf)) == 0) {
		usriowanted = 1;
		sleep((caddr_t)useriomap, PSWP);
	}
	splx(s);
	iopte = &Usriomap[a];
	bp->b_saveaddr = bp->b_un.b_addr;
	addr = bp->b_un.b_addr = (caddr_t)(usrio + (a << PGSHIFT)) + off;
E 6
I 6
	p = bp->b_proc;
	npf = btoc(round_page(bp->b_bcount + off));
	kva = kmem_alloc_wait(phys_map, ctob(npf));
D 16
	bp->b_un.b_addr = (caddr_t) (kva + off);
E 16
I 16
	bp->b_data = (caddr_t)(kva + off);
E 16
E 6
	while (npf--) {
D 6
		mapin(iopte, (u_int)addr, pte->pg_pfnum, PG_CI|PG_RW|PG_V);
		iopte++, pte++;
		addr += NBPG;
E 6
I 6
D 8
		pa = pmap_extract(vm_map_pmap(p->p_map), (vm_offset_t)addr);
E 8
I 8
		pa = pmap_extract(vm_map_pmap(&p->p_vmspace->vm_map),
		    (vm_offset_t)addr);
E 8
		if (pa == 0)
			panic("vmapbuf: null page frame");
		pmap_enter(vm_map_pmap(phys_map), kva, trunc_page(pa),
			   VM_PROT_READ|VM_PROT_WRITE, TRUE);
		addr += PAGE_SIZE;
		kva += PAGE_SIZE;
E 6
	}
}

/*
 * Free the io map PTEs associated with this IO operation.
D 12
 * We also invalidate the TLB entries and restore the original b_addr.
E 12
 */
vunmapbuf(bp)
	register struct buf *bp;
{
I 16
	register caddr_t addr;
E 16
D 6
	register int a, npf;
E 6
I 6
	register int npf;
E 6
D 16
	register caddr_t addr = bp->b_un.b_addr;
E 16
D 6
	register struct pte *pte;
	int s;
E 6
I 6
	vm_offset_t kva;
E 6

	if ((bp->b_flags & B_PHYS) == 0)
		panic("vunmapbuf");
I 16
	addr = bp->b_data;
E 16
D 6
	a = (int)(addr - usrio) >> PGSHIFT;
	npf = btoc(bp->b_bcount + ((int)addr & PGOFSET));
	s = splbio();
	rmfree(useriomap, npf, a);
	if (usriowanted) {
		usriowanted = 0;
		wakeup((caddr_t)useriomap); 
	}
	splx(s);
	pte = &Usriomap[a];
	while (npf--) {
		*(int *)pte = PG_NV;
		TBIS((caddr_t)addr);
		addr += NBPG;
		pte++;
	}
E 6
I 6
	npf = btoc(round_page(bp->b_bcount + ((int)addr & PGOFSET)));
	kva = (vm_offset_t)((int)addr & ~PGOFSET);
	kmem_free_wakeup(phys_map, kva, ctob(npf));
E 6
D 3
#if 0
	/* 0 is a valid (and common) user space addr */
	if (bp->b_saveaddr == NULL)
		panic("vunmapbuf: null saveaddr");
#endif
E 3
D 16
	bp->b_un.b_addr = bp->b_saveaddr;
E 16
I 16
	bp->b_data = bp->b_saveaddr;
E 16
	bp->b_saveaddr = NULL;
}
I 18

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
E 18
E 1
