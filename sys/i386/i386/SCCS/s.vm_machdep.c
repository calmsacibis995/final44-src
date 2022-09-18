h27185
s 00000/00001/00380
d D 8.3 94/01/21 19:44:53 bostic 21 20
c copyright typo
e
s 00008/00008/00373
d D 8.2 93/09/23 16:42:49 bostic 20 19
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00379
d D 8.1 93/06/11 15:35:12 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/00371
d D 7.10 92/10/11 10:11:08 bostic 18 17
c make kernel includes standard
e
s 00001/00000/00380
d D 7.9 92/05/11 16:53:24 bostic 17 16
c fix NPX device handling; from Pace Willison
e
s 00016/00001/00364
d D 7.8 92/03/13 17:15:47 torek 16 15
c add cpu_coredump; lint in cpu_fork
e
s 00001/00001/00364
d D 7.7 92/03/13 17:07:34 sklower 15 14
c p_regs => p_md.md_regs (checked in for sklower by torek)
e
s 00002/00000/00363
d D 7.6 92/02/05 10:49:44 bostic 14 13
c try the right header one more time
e
s 00007/00032/00356
d D 7.5 92/02/05 10:47:40 bostic 13 12
c compiling without a 386 (no -DNNPX) makes npxproc undefined; from
c Christos Zoulas; put correct copyright notice in place
e
s 00033/00007/00355
d D 7.4 91/11/13 17:45:48 william 12 11
c changes to fix new vm on i386
e
s 00012/00002/00350
d D 7.3 91/05/13 01:11:22 william 11 10
c last whacks, numerious bugs and cleanups, sizing disabled due to
c bug I don't care to chase now, other nicer code withdrawn due to bugs
e
s 00004/00018/00348
d D 7.2 91/05/10 09:22:27 bostic 10 9
c whack on the copyright
e
s 00020/00004/00346
d D 7.1 91/05/09 21:45:00 william 9 8
c changes prior to net2 release
e
s 00104/00014/00246
d D 5.8 91/05/09 19:42:18 william 8 7
c cpu dependant fork and exit
e
s 00050/00330/00210
d D 5.7 91/05/02 11:58:50 william 7 6
c interim version, new vm
e
s 00037/00036/00503
d D 5.6 91/01/19 13:08:18 william 6 5
c reno changes, cleanups, bug fixes
e
s 00008/00008/00531
d D 5.5 90/11/25 16:08:10 bill 5 4
c last changes before merger with reno version. cross fingers.
e
s 00008/00050/00531
d D 5.4 90/11/18 11:30:15 bill 4 3
c fix autoconf, move code to isa.c, remove debugging, drop redundant tlbflushes, macros for tlb et al
e
s 00023/00012/00558
d D 5.3 90/11/14 15:57:33 bill 3 2
c changes to make work
e
s 00038/00025/00532
d D 5.2 90/06/23 19:33:59 donahn 2 1
c improvements
e
s 00557/00000/00000
d D 5.1 90/04/24 19:17:43 william 1 0
c date and time created 90/04/24 19:17:43 by william
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
E 10
I 10
D 19
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * Copyright (c) 1989, 1990 William Jolitz
E 19
I 19
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
E 10
D 21
 * All rights reserved.
E 21
 *
 * This code is derived from software contributed to Berkeley by
D 10
 * the University of Utah, and William Jolitz.
E 10
I 10
 * the Systems Programming Group of the University of Utah Computer
 * Science Department, and William Jolitz.
E 10
 *
I 14
 * %sccs.include.redist.c%
 *
E 14
D 8
 * %sccs.include.386.c%
E 8
I 8
D 12
 * %sccs.include.redist.c%
E 12
I 12
D 13
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 12
E 8
 *
D 12
 *	%W% (Berkeley) %G%
E 12
I 12
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)vm_machdep.c	7.3 (Berkeley) 5/13/91
E 12
 */

I 2
/*
E 13
I 13
 *	%W% (Berkeley) %G%
E 13
I 3
D 10
 * Copyright (c) 1989, 1990 William F. Jolitz
 */

/*
E 3
 * Copyright (c) 1988 University of Utah.
 * All rights reserved.  The Utah Software License Agreement
 * specifies the terms and conditions for redistribution.
 *
E 10
 *	Utah $Hdr: vm_machdep.c 1.16.1.1 89/06/23$
 */
I 11

E 11
D 10
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)vm_machdep.c	7.1 (Berkeley) 6/5/86
 */
E 2

E 10
D 6
#include "pte.h"
E 6
I 6
D 7
#include "machine/pte.h"
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
D 18
#include "param.h"
#include "systm.h"
#include "proc.h"
#include "malloc.h"
#include "buf.h"
I 16
#include "vnode.h"
E 16
#include "user.h"
E 18
I 18
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/malloc.h>
#include <sys/buf.h>
#include <sys/vnode.h>
#include <sys/user.h>
E 18
E 8
E 7
E 6

D 7
#include "param.h"
#include "systm.h"
D 6
#include "dir.h"
E 6
#include "user.h"
#include "proc.h"
#include "cmap.h"
#include "mount.h"
#include "vm.h"
#include "text.h"
E 7
I 7
D 8
#include "machine/cpu.h"
E 8
I 8
D 18
#include "../include/cpu.h"
E 18
I 18
#include <machine/cpu.h>
E 18
E 8
E 7

D 7
#include "buf.h"
E 7
I 7
D 8
#include "vm/vm_param.h"
#include "vm/pmap.h"
#include "vm/vm_map.h"
E 8
I 8
D 18
#include "vm/vm.h"
#include "vm/vm_kern.h"
E 18
I 18
#include <vm/vm.h>
#include <vm/vm_kern.h>
E 18
E 8
E 7

D 4
#include "dbg.h"
I 3

#define load_cr3(s)	{long phys; \
	phys = (long)(s) /*| 0x80000000 */ ;\
	__asm ( "movl %0,%%eax; movl %%eax,%%cr3" : : "g" (phys) : "ax" ) ; }

E 4
E 3
/*
I 8
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
	int foo, offset, addr, i;
	extern char kstack[];
I 12
	extern int mvesp();
E 12

	/*
	 * Copy pcb and stack from proc p1 to p2. 
	 * We do this as cheaply as possible, copying only the active
	 * part of the stack.  The stack and pcb need to agree;
	 * this is tricky, as the final pcb is constructed by savectx,
	 * but its frame isn't yet on the stack when the stack is copied.
D 20
	 * swtch compensates for this when the child eventually runs.
E 20
I 20
	 * mi_switch compensates for this when the child eventually runs.
E 20
	 * This should be done differently, with a single call
	 * that copies and updates the pcb+stack,
	 * replacing the bcopy and savectx.
	 */
	p2->p_addr->u_pcb = p1->p_addr->u_pcb;
D 12
	offset = (caddr_t)&foo - kstack;
E 12
I 12
	offset = mvesp() - (int)kstack;
E 12
	bcopy((caddr_t)kstack + offset, (caddr_t)p2->p_addr + offset,
	    (unsigned) ctob(UPAGES) - offset);
D 15
	p2->p_regs = p1->p_regs;
E 15
I 15
	p2->p_md.md_regs = p1->p_md.md_regs;
E 15

	/*
	 * Wire top of address space of child to it's u.
	 * First, fault in a page of pte's to map it.
	 */
        addr = trunc_page((u_int)vtopte(kstack));
D 9
	(void)vm_fault(p2->p_vmspace->vm_map,
E 9
I 9
D 12
	(void)vm_fault(&p2->p_vmspace->vm_map,
E 9
		trunc_page((u_int)vtopte(kstack)), VM_PROT_READ, FALSE);
E 12
I 12
	(void)vm_map_pageable(&p2->p_vmspace->vm_map, addr, addr+NBPG, FALSE);
E 12
	for (i=0; i < UPAGES; i++)
D 9
		pmap_enter(p2->p_vmspace->vm_pmap, kstack+i*NBPG,
			pmap_extract(kernel_pmap, p2->p_addr), VM_PROT_READ, 1);
E 9
I 9
D 16
		pmap_enter(&p2->p_vmspace->vm_pmap, kstack+i*NBPG,
E 16
I 16
		pmap_enter(&p2->p_vmspace->vm_pmap, (vm_offset_t)kstack+i*NBPG,
E 16
D 12
			pmap_extract(kernel_pmap, ((int)p2->p_addr)+i*NBPG), VM_PROT_READ, 1);
E 9

E 12
I 12
			pmap_extract(kernel_pmap, ((int)p2->p_addr)+i*NBPG),
			VM_PROT_READ, 1);
E 12
	pmap_activate(&p2->p_vmspace->vm_pmap, &up->u_pcb);

	/*
	 * 
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

I 17
#include "npx.h"
E 17
I 13
#if NNPX > 0
E 13
I 11
extern struct proc *npxproc;
I 13
#endif
E 13

E 11
I 9
#ifdef notyet
E 9
/*
 * cpu_exit is called as the last action during exit.
 *
 * We change to an inactive address space and a "safe" stack,
 * passing thru an argument to the new stack. Now, safely isolated
 * from the resources we're shedding, we release the address space
 * and any remaining machine-dependent resources, including the
 * memory for the user structure and kernel stack.
 *
D 20
 * Next, we assign a dummy context to be written over by swtch,
E 20
I 20
 * Next, we assign a dummy context to be written over by mi_switch,
E 20
 * calling it to send this process off to oblivion.
D 20
 * [The nullpcb allows us to minimize cost in swtch() by not having
E 20
I 20
 * [The nullpcb allows us to minimize cost in mi_switch() by not having
E 20
 * a special case].
 */
D 20
struct proc *swtch_to_inactive();
E 20
I 20
struct proc *switch_to_inactive();
E 20
cpu_exit(p)
D 9
	struct proc *p;
E 9
I 9
	register struct proc *p;
E 9
{
D 20
	static struct pcb nullpcb;	/* pcb to overwrite on last swtch */
E 20
I 20
	static struct pcb nullpcb;	/* pcb to overwrite on last switch */
E 20

I 13
#if NNPX > 0
E 13
I 11
	/* free cporcessor (if we have it) */
	if( p == npxproc) npxproc =0;
I 13
#endif
E 13

E 11
	/* move to inactive space and stack, passing arg accross */
D 20
	p = swtch_to_inactive(p);
E 20
I 20
	p = switch_to_inactive(p);
E 20

	/* drop per-process resources */
	vmspace_free(p->p_vmspace);
	kmem_free(kernel_map, (vm_offset_t)p->p_addr, ctob(UPAGES));

	p->p_addr = (struct user *) &nullpcb;
D 20
	swtch();
E 20
I 20
	mi_switch();
E 20
	/* NOTREACHED */
}
I 9
#else
cpu_exit(p)
	register struct proc *p;
{
	
D 11
	(void) vm_map_remove(&p->p_vmspace->vm_map, VM_MIN_ADDRESS,
		    VM_MAXUSER_ADDRESS);
E 11
I 11
	/* free coprocessor (if we have it) */
I 13
#if NNPX > 0
E 13
	if( p == npxproc) npxproc =0;
I 13
#endif
E 13

	curproc = p;
E 11
D 20
	swtch();
E 20
I 20
	mi_switch();
E 20
}
I 11

E 11
cpu_wait(p) struct proc *p; {
I 11

E 11
	/* drop per-process resources */
	vmspace_free(p->p_vmspace);
	kmem_free(kernel_map, (vm_offset_t)p->p_addr, ctob(UPAGES));
}
#endif
I 16

/*
 * Dump the machine specific header information at the start of a core dump.
 */
cpu_coredump(p, vp, cred)
	struct proc *p;
	struct vnode *vp;
	struct ucred *cred;
{

	return (vn_rdwr(UIO_WRITE, vp, (caddr_t) p->p_addr, ctob(UPAGES),
	    (off_t)0, UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, cred, (int *)NULL,
	    p));
}
E 16
E 9

/*
E 8
 * Set a red zone in the kernel stack after the u. area.
 */
setredzone(pte, vaddr)
	u_short *pte;
	caddr_t vaddr;
{
/* eventually do this by setting up an expand-down stack segment
   for ss0: selector, allowing stack access down to top of u.
   this means though that protection violations need to be handled
   thru a double fault exception that must do an integral task
   switch to a known good context, within which a dump can be
   taken. a sensible scheme might be to save the initial context
   used by sched (that has physical memory mapped 1:1 at bottom)
   and take the dump while still in mapped mode */
}

/*
D 7
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
D 6
		u.u_error = ENOMEM;
		return (1);
E 6
I 6
		return (ENOMEM);
E 6
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
D 3
	load_cr3(_cr3());
E 3
I 3
D 4
	load_cr3(u.u_pcb.pcb_ptd);
E 4
I 4
D 5
	tlbflush();
E 5
I 5
D 6
	load_cr3(u.u_pcb.pcb_ptd);
E 6
I 6
	load_cr3(u.u_pcb.pcb_cr3);
E 6
E 5
E 4
E 3
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
D 6
	if (!isatsv(u.u_procp, v)) {
		u.u_error = EFAULT;
		return (0);
	}
E 6
I 6
	if (!isatsv(u.u_procp, v))
		return (EFAULT);
E 6
	tp = vtotp(u.u_procp, v);
	pte = tptopte(u.u_procp, tp);
	if (pte->pg_fod == 0 && pte->pg_pfnum) {
		c = &cmap[pgtocm(pte->pg_pfnum)];
D 6
		if (c->c_blkno && c->c_mdev != MSWAPX)
			munhash(mount[c->c_mdev].m_dev,
			    (daddr_t)(u_long)c->c_blkno);
E 6
I 6
		if (c->c_blkno)
			munhash(c->c_vp, (daddr_t)(u_long)c->c_blkno);
E 6
	}
	*(u_int *)pte &= ~PG_PROT;
	*(u_int *)pte |= tprot;
D 3
	load_cr3(_cr3());
E 3
I 3
D 4
	load_cr3(u.u_pcb.pcb_ptd);
E 4
I 4
D 5
	tlbflush();
E 5
I 5
D 6
	load_cr3(u.u_pcb.pcb_ptd);
E 5
E 4
E 3
	return (1);
E 6
I 6
	load_cr3(u.u_pcb.pcb_cr3);
	return (0);
E 6
}

settprot(tprot)
	long tprot;
{
	register u_int *ptaddr, i;

	ptaddr = (u_int *)u.u_procp->p_p0br;
	for (i = 0; i < u.u_tsize; i++) {
		ptaddr[i] &= ~PG_PROT;
		ptaddr[i] |= tprot;
	}
D 3
	load_cr3(_cr3());
E 3
I 3
D 4
	load_cr3(u.u_pcb.pcb_ptd);
E 4
I 4
D 5
	tlbflush();
E 5
I 5
D 6
	load_cr3(u.u_pcb.pcb_ptd);
E 6
I 6
	load_cr3(u.u_pcb.pcb_cr3);
E 6
E 5
E 4
E 3
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
D 4
/*pg("setptlr(%x,%x), was %d",region, nlen, olen);*/
E 4
	if ((change = olen - nlen) <= 0)
		return;
	if (region == 0)
		pte = u.u_pcb.pcb_p0br + u.u_pcb.pcb_p0lr;
	else
		pte = u.u_pcb.pcb_p1br + u.u_pcb.pcb_p1lr - change;
D 4
/*printf("p0b %x p0l %x", u.u_pcb.pcb_p0br, u.u_pcb.pcb_p0lr);
printf("p1b %x p1l %x pte %x", u.u_pcb.pcb_p1br, u.u_pcb.pcb_p1lr, pte);*/
E 4
	do {
		*(u_int *)pte++ = 0;
	} while (--change);
	/* short cut newptes */
D 3
	load_cr3(_cr3());
E 3
I 3
D 4
	load_cr3(u.u_pcb.pcb_ptd);
E 4
I 4
D 5
	tlbflush();
E 5
I 5
D 6
	load_cr3(u.u_pcb.pcb_ptd);
E 6
I 6
	load_cr3(u.u_pcb.pcb_cr3);
E 6
E 5
E 4
E 3
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
D 3
	load_cr3(_cr3());
E 3
I 3
D 4
	load_cr3(u.u_pcb.pcb_ptd);
E 4
I 4
D 5
	tlbflush();
E 5
I 5
D 6
	load_cr3(u.u_pcb.pcb_ptd);
E 6
I 6
	load_cr3(u.u_pcb.pcb_cr3);
E 6
E 5
E 4
E 3
}

/*
E 7
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
D 3
	fpte = &Sysmap[btop(from)];
	tpte = &Sysmap[btop(to)];
E 3
I 3
D 6
	fpte = &Sysmap[btop(from-0xfe000000)];
	tpte = &Sysmap[btop(to-0xfe000000)];
E 6
I 6
D 7
	fpte = &Sysmap[btop(from -0xfe000000)];
	tpte = &Sysmap[btop(to -0xfe000000)];
E 7
I 7
	fpte = kvtopte(from);
	tpte = kvtopte(to);
E 7
E 6
E 3
	while (size > 0) {
		*tpte++ = *fpte;
		*(int *)fpte++ = 0;
		from += NBPG;
		to += NBPG;
		size -= NBPG;
	}
D 3
	load_cr3(_cr3());
E 3
I 3
D 4
	load_cr3(u.u_pcb.pcb_ptd);
E 4
I 4
D 5
	tlbflush();
E 5
I 5
D 6
	load_cr3(u.u_pcb.pcb_ptd);
E 6
I 6
D 8
	load_cr3(u.u_pcb.pcb_cr3);
E 8
I 8
	tlbflush();
E 8
E 6
E 5
E 4
E 3
}

/*
I 7
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

#ifdef notdef
/*
E 7
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
	p = u.u_procp;
	page = btop(addr);
	if (page < dptov(p, p->p_dsize) || page > sptov(p, p->p_ssize))
		return(1);
	return(0);
}

probew(addr)
	register u_int addr;
{
	register int page;
	register struct proc *p;

	if (addr >= USRSTACK)
		return(0);
	p = u.u_procp;
	page = btop(addr);
	if (page < dptov(p, p->p_dsize) || page > sptov(p, p->p_ssize))
I 2
D 4
/*
E 2
{
D 2
dprintf(DPHYS,"vtopte %x %x\n", vtopte(p, page), *(int *)vtopte(p, page) );
E 2
I 2
dprintf(DPHYS,"vtopte %x %x\n", vtopte(p, page), *(int *)vtopte(p, page) );*/
E 4
E 2
		return((*(int *)vtopte(p, page) & PG_PROT) == PG_UW);
D 2
}
E 2
I 2
D 4
/*}*/
E 4
E 2
	return(0);
}

/*
 * NB: assumes a physically contiguous kernel page table
 *     (makes life a LOT simpler).
 */
kernacc(addr, count, rw)
	register u_int addr;
	int count, rw;
{
	register struct pde *pde;
	register struct pte *pte;
	register int ix, cnt;
	extern long Syssize;

D 2
dprintf(DPHYS,"kernacc %x count %d rw %d", addr, count, rw);
E 2
I 2
D 4
/*dprintf(DPHYS,"kernacc %x count %d rw %d", addr, count, rw);*/
E 4
E 2
	if (count <= 0)
		return(0);
	pde = (struct pde *)((u_int)u.u_procp->p_p0br + u.u_procp->p_szpt * NBPG);
	ix = (addr & PD_MASK) >> PD_SHIFT;
	cnt = ((addr + count + (1 << PD_SHIFT) - 1) & PD_MASK) >> PD_SHIFT;
	cnt -= ix;
	for (pde += ix; cnt; cnt--, pde++)
		if (pde->pd_v == 0)
D 2
{
dprintf(DPHYS,"nope pde %x, idx %x\n", pde, ix);
E 2
I 2
D 4
/*{
dprintf(DPHYS,"nope pde %x, idx %x\n", pde, ix);*/
E 4
E 2
			return(0);
D 2
}
E 2
I 2
D 4
/*}*/
E 4
E 2
	ix = btop(addr-0xfe000000);
	cnt = btop(addr-0xfe000000+count+NBPG-1);
	if (cnt > (int)&Syssize)
D 2
{
dprintf(DPHYS,"nope cnt %x\n", cnt);
E 2
I 2
D 4
/*{
dprintf(DPHYS,"nope cnt %x\n", cnt);*/
E 4
E 2
		return(0);
D 2
}
E 2
I 2
D 4
/*}*/
E 4
E 2
	cnt -= ix;
	for (pte = &Sysmap[ix]; cnt; cnt--, pte++)
		if (pte->pg_v == 0 /*|| (rw == B_WRITE && pte->pg_prot == 1)*/) 
D 2
{
dprintf(DPHYS,"nope pte %x %x, idx %x\n", pte, *(int *)pte, ix);
E 2
I 2
D 4
/*{
dprintf(DPHYS,"nope pte %x %x, idx %x\n", pte, *(int *)pte, ix);*/
E 4
E 2
			return(0);
D 2
}
dprintf(DPHYS,"yup\n");
E 2
I 2
D 4
/*}
dprintf(DPHYS,"yup\n");*/
E 4
E 2
	return(1);
}

useracc(addr, count, rw)
	register u_int addr;
	int count, rw;
{
	register int (*func)();
	register u_int addr2;
	extern int prober(), probew();

D 2
dprintf(DPHYS,"useracc %x count %d rw %d", addr, count, rw);
E 2
I 2
D 4
/*dprintf(DPHYS,"useracc %x count %d rw %d", addr, count, rw);*/
E 4
E 2
	if (count <= 0)
		return(0);
	addr2 = addr;
	addr += count;
	func = (rw == B_READ) ? prober : probew;
	do {
		if ((*func)(addr2) == 0)
D 2
{
dprintf(DPHYS,"nope %x\n", addr);
E 2
I 2
D 4
/*{
dprintf(DPHYS,"nope %x\n", addr);*/
E 4
E 2
			return(0);
D 2
}
E 2
I 2
D 4
/*}*/
E 4
E 2
		addr2 = (addr2 + NBPG) & ~PGOFSET;
	} while (addr2 < addr);
D 2
dprintf(DPHYS,"yup\n", addr);
E 2
I 2
D 4
/*dprintf(DPHYS,"yup\n", addr);*/
E 4
E 2
	return(1);
}
D 7

/*
 * Convert kernel VA to physical address
 */
kvtop(addr)
	register u_int addr;
{
	register int pf;

	pf = Sysmap[btop(addr-0xfe000000)].pg_pfnum;
	if (pf == 0)
		panic("kvtop: zero page frame");
	return((u_int)ptob(pf) + (addr & PGOFSET));
}

struct pde *
vtopde(p, va)
	register struct proc *p;
	register u_int va;
{
	register struct pde *pde;

	pde = (struct pde *)((u_int)p->p_p0br + p->p_szpt * NBPG);
	return(pde + ((va & PD_MASK) >> PD_SHIFT));
}


initcr3(p)
	register struct proc *p;
{
D 3
	return((int)Usrptmap[btokmx(p->p_p0br) + p->p_szpt].pg_pfnum);
E 3
I 3
	return(ctob(Usrptmap[btokmx(p->p_p0br+p->p_szpt*NPTEPG)].pg_pfnum));
D 6
	/*return((int)Usrptmap[btokmx(p->p_p0br) + p->p_szpt].pg_pfnum);*/
E 6
E 3
}

/*
 * Initialize page directory table to reflect PTEs in Usrptmap.
 * Page directory table address is given by Usrptmap index of p_szpt.
 * [used by vgetpt for kernal mode entries, and ptexpand for user mode entries]
 */
D 2
initpdt(p, usr)
E 2
I 2
initpdt(p)
E 2
	register struct proc *p;
{
	register int i, k, sz;
	register struct pde *pde, *toppde;
	extern struct pde *vtopde();
	extern Sysbase;

D 4
/*pg("initpdt");*/
E 4
D 2
if(!usr) {
E 2
	/* clear entire map */
	pde = vtopde(p, 0);
D 3
	bzero(pde, NBPG);
E 3
I 3
D 6
	/*bzero(pde, NBPG); */
E 6
I 6
	/*bzero(pde, NBPG);*/
E 6
E 3
	/* map kernel */
	pde = vtopde(p, &Sysbase);
	for (i = 0; i < 5; i++, pde++) {
		*(int *)pde = PG_UW | PG_V;
		pde->pd_pfnum = btoc((unsigned) Sysmap & ~0xfe000000)+i;
	}
	/* map u dot */
	pde = vtopde(p, &u);
	*(int *)pde = PG_UW | PG_V;
	pde->pd_pfnum = Usrptmap[btokmx(p->p_addr)].pg_pfnum;
I 6
/*printf("%d.u. pde %x pfnum %x virt %x\n", p->p_pid, pde, pde->pd_pfnum,
p->p_addr);*/
E 6
D 4
/*printf("%d.u. pde %x pfnum %x virt %x\n", p->p_pid, pde, pde->pd_pfnum,
p->p_addr);*/
E 4
D 2
	return;
}
E 2

	/* otherwise, fill in user map */
	k = btokmx(p->p_p0br);
	pde = vtopde(p, 0);
	toppde = vtopde(p, &u);

	/* text and data */
	sz = ctopt(p->p_tsize + p->p_dsize);
I 6
/*dprintf(DEXPAND,"textdata 0 to %d\n",sz-1);*/
E 6
D 2
dprintf(DEXPAND,"textdata 0 to %d\n",sz-1);
E 2
I 2
D 4
/*dprintf(DEXPAND,"textdata 0 to %d\n",sz-1);*/
E 4
E 2
	for (i = 0; i < sz; i++, pde++) {
		*(int *)pde = PG_UW | PG_V;
		pde->pd_pfnum = Usrptmap[k++].pg_pfnum;
I 6
/*dprintf(DEXPAND,"%d.pde %x pf %x\n", p->p_pid, pde, *(int *)pde);*/
E 6
D 4
/*dprintf(DEXPAND,"%d.pde %x pf %x\n", p->p_pid, pde, *(int *)pde);*/
E 4
	}
	/*
	 * Bogus!  The kernelmap may map unused PT pages
	 * (since we don't shrink PTs) so we need to skip over
	 * those PDEs.  We should really free the unused PT
	 * pages in expand().
	 */
	sz += ctopt(p->p_ssize+UPAGES);
	if (sz < p->p_szpt)
		k += p->p_szpt - sz;
	/* hole */
	sz = NPTEPG - ctopt(p->p_ssize + UPAGES + btoc(&Sysbase));
I 6
/*dprintf(DEXPAND,"zero %d upto %d\n", i, sz-1);*/
E 6
D 2
dprintf(DEXPAND,"zero %d upto %d\n", i, sz-1);
E 2
I 2
D 4
/*dprintf(DEXPAND,"zero %d upto %d\n", i, sz-1);*/
E 4
E 2
	for ( ; i < sz; i++, pde++)
I 6
/* definite bug here... does not hit all entries, but point moot due
to bzero above XXX*/
{
E 6
D 4
/* definite bug here... does not hit all entries, but point moot due
to bzero above XXX*/
{
E 4
		*(int *)pde = 0;
I 6
/*pg("pde %x pf %x", pde, *(int *)pde);*/
}
E 6
D 4
/*pg("pde %x pf %x", pde, *(int *)pde);*/
}
E 4
	/* stack and u-area */
	sz = NPTEPG - ctopt(UPAGES + btoc(&Sysbase));
I 6
/*dprintf(DEXPAND,"stack %d upto %d\n", i, sz-1);*/
E 6
D 2
dprintf(DEXPAND,"stack %d upto %d\n", i, sz-1);
E 2
I 2
D 4
/*dprintf(DEXPAND,"stack %d upto %d\n", i, sz-1);*/
E 4
E 2
	for ( ; i < sz; i++, pde++) {
		*(int *)pde = PG_UW | PG_V;
		pde->pd_pfnum = Usrptmap[k++].pg_pfnum;
I 6
/*pg("pde %x pf %x", pde, *(int *)pde);*/
E 6
D 4
/*pg("pde %x pf %x", pde, *(int *)pde);*/
E 4
	}
I 3
	return(initcr3(p));
E 3
}

#ifdef notdef
/*
 * Allocate wired-down, non-paged, cache-inhibited pages in kernel
 * virtual memory and clear them
 */
caddr_t
cimemall(n)
	int n;
{
	register int npg, a;
	register struct pte *pte;
	extern struct map *kernelmap;

	npg = clrnd(btoc(n));
	a = rmalloc(kernelmap, (long)npg);
	if (a == 0)
		return ((caddr_t)0);
	pte = &Usrptmap[a];
	(void) vmemall(pte, npg, &proc[0], CSYS);
	while (--npg >= 0) {
		*(int *)pte |= (PG_V|PG_KW|PG_CI);
		clearseg((unsigned)pte->pg_pfnum);
		pte++;
	}
	TBIAS();
	return ((caddr_t)kmxtob(a));
}
E 7
#endif

D 7
extern char usrio[];
extern struct pte Usriomap[];
struct map *useriomap;
int usriowanted;
E 7
I 7
extern vm_map_t phys_map;
E 7

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
 * All requests are (re)mapped into kernel VA space via the useriomap
 * (a name with only slightly more meaning than "kernelmap")
 */
vmapbuf(bp)
	register struct buf *bp;
{
D 7
	register int npf, a;
E 7
I 7
	register int npf;
E 7
	register caddr_t addr;
D 7
	register struct pte *pte, *iopte;
E 7
	register long flags = bp->b_flags;
	struct proc *p;
D 7
	int off, s;
E 7
I 7
	int off;
	vm_offset_t kva;
	register vm_offset_t pa;
E 7

	if ((flags & B_PHYS) == 0)
		panic("vmapbuf");
D 7
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
I 6

E 6
	/*
	 * Allocate some kernel PTEs and load them
	 */
E 7
I 7
	addr = bp->b_saveaddr = bp->b_un.b_addr;
E 7
	off = (int)addr & PGOFSET;
D 7
	npf = btoc(bp->b_bcount + off);
	s = splbio();
	while ((a = rmalloc(useriomap, npf)) == 0) {
		usriowanted = 1;
		sleep((caddr_t)useriomap, PSWP);
	}
	splx(s);
	iopte = &Usriomap[a];
I 6
	bp->b_saveaddr = bp->b_un.b_addr;
E 6
	addr = bp->b_un.b_addr = (caddr_t)(usrio + (a << PGSHIFT)) + off;
E 7
I 7
	p = bp->b_proc;
	npf = btoc(round_page(bp->b_bcount + off));
	kva = kmem_alloc_wait(phys_map, ctob(npf));
	bp->b_un.b_addr = (caddr_t) (kva + off);
E 7
D 6
	a = btop(addr);
E 6
	while (npf--) {
D 6
		mapin(iopte, a, pte->pg_pfnum, PG_V);
E 6
I 6
D 7
		mapin(iopte, (u_int)addr, pte->pg_pfnum, PG_KW|PG_V);
E 6
		iopte++, pte++;
D 6
		a++;
E 6
I 6
		addr += NBPG;
E 7
I 7
D 8
		pa = pmap_extract(vm_map_pmap(p->p_map), (vm_offset_t)addr);
E 8
I 8
		pa = pmap_extract(&p->p_vmspace->vm_pmap, (vm_offset_t)addr);
E 8
		if (pa == 0)
			panic("vmapbuf: null page frame");
		pmap_enter(vm_map_pmap(phys_map), kva, trunc_page(pa),
			   VM_PROT_READ|VM_PROT_WRITE, TRUE);
		addr += PAGE_SIZE;
		kva += PAGE_SIZE;
E 7
E 6
	}
I 2
D 3
	load_cr3(_cr3());
E 3
I 3
D 4
	load_cr3(u.u_pcb.pcb_ptd);
E 4
I 4
D 5
	tlbflush();
E 5
I 5
D 6
	load_cr3(u.u_pcb.pcb_ptd);
E 6
I 6
D 7
	load_cr3(u.u_pcb.pcb_cr3);
E 7
E 6
E 5
E 4
E 3
E 2
}

/*
 * Free the io map PTEs associated with this IO operation.
D 6
 * We also invalidate the TLB entries.
E 6
I 6
 * We also invalidate the TLB entries and restore the original b_addr.
E 6
 */
vunmapbuf(bp)
	register struct buf *bp;
{
D 7
	register int a, npf;
E 7
I 7
	register int npf;
E 7
	register caddr_t addr = bp->b_un.b_addr;
D 7
	register struct pte *pte;
	int s;
E 7
I 7
	vm_offset_t kva;
E 7

	if ((bp->b_flags & B_PHYS) == 0)
		panic("vunmapbuf");
D 7
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
		*(int *)pte = 0;
		addr += NBPG;
		pte++;
	}
D 6
	/*
	 * If we just completed a dirty page push, we must reconstruct
	 * the original b_addr since cleanup() needs it.
	 */
	if (bp->b_flags & B_DIRTY) {
		a = ((bp - swbuf) * CLSIZE) * KLMAX;
		bp->b_un.b_addr = (caddr_t)ctob(dptov(&proc[2], a));
	}
D 3
	load_cr3(_cr3());
E 3
I 3
D 4
	load_cr3(u.u_pcb.pcb_ptd);
E 4
I 4
D 5
	tlbflush();
E 5
I 5
	load_cr3(u.u_pcb.pcb_ptd);
E 6
I 6
	load_cr3(u.u_pcb.pcb_cr3);
E 7
I 7
	npf = btoc(round_page(bp->b_bcount + ((int)addr & PGOFSET)));
	kva = (vm_offset_t)((int)addr & ~PGOFSET);
	kmem_free_wakeup(phys_map, kva, ctob(npf));
E 7
	bp->b_un.b_addr = bp->b_saveaddr;
	bp->b_saveaddr = NULL;
E 6
E 5
E 4
E 3
}
E 1
