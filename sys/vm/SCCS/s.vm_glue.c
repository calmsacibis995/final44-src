h07894
s 00002/00000/00579
d D 8.9 95/03/04 10:25:17 mckusick 36 35
c at least note what should be done
e
s 00013/00013/00566
d D 8.8 95/01/09 17:47:28 cgd 35 34
c style, 64-bit changes, update printfs for reality, sleep -> tsleep.
e
s 00002/00002/00577
d D 8.7 94/08/20 16:25:51 mckusick 34 33
c use new queue.h data structures
e
s 00002/00000/00577
d D 8.6 94/01/05 11:04:44 mckusick 33 32
c needs to include <machine/cpu.h> for cpu_fork and cpu_swapin
e
s 00006/00000/00571
d D 8.5 94/01/05 09:58:56 mckusick 32 31
c add cpu_swapin call (to notify of user area moving to new physical page(s))
e
s 00013/00012/00558
d D 8.4 93/09/23 16:40:43 bostic 31 30
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00001/00569
d D 8.3 93/09/21 07:43:23 bostic 30 29
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00001/00569
d D 8.2 93/09/05 09:43:27 bostic 29 28
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00568
d D 8.1 93/07/15 16:58:54 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00565
d D 7.26 93/07/15 16:24:50 hibler 27 25
c fix off-by-one errors (from cgd)
e
s 00002/00002/00568
d R 8.1 93/06/11 16:37:30 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00569
d D 7.25 93/06/02 11:08:02 hibler 25 24
c fix minor typo
e
s 00001/00001/00569
d D 7.24 93/05/24 23:40:36 torek 24 23
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00002/00002/00568
d D 7.23 93/04/29 20:37:02 ralph 23 22
c oops, fix \n in panic string.
e
s 00004/00000/00566
d D 7.22 93/04/29 20:35:49 ralph 22 21
c kmem_alloc*() can return zero if no more kernel virtual memory.
e
s 00001/00002/00565
d D 7.21 93/04/28 19:51:27 mckusick 21 20
c set RLIMIT_RSS initial limit to currently available user memory
e
s 00001/00001/00566
d D 7.20 93/01/02 10:43:01 hibler 20 19
c fix a stupid typo
e
s 00024/00004/00543
d D 7.19 92/12/27 08:56:47 hibler 19 18
c hack chgkprot to attempt to allow writing ktext without forcing
c all pages to be writable
e
s 00001/00001/00546
d D 7.18 92/10/11 13:04:00 bostic 18 17
c make kernel includes standard
e
s 00003/00003/00544
d D 7.17 92/07/08 01:01:09 torek 17 16
c volatile poison; splclock => splstatclock
e
s 00001/00001/00546
d D 7.16 92/06/04 14:58:04 mckusick 16 15
c add support for luna68k from Omron
e
s 00020/00009/00527
d D 7.15 92/05/04 17:23:47 bostic 15 14
c new include format; lint
e
s 00002/00000/00534
d D 7.14 92/02/19 18:50:19 mckusick 14 13
c add void decls
e
s 00019/00014/00515
d D 7.13 92/02/19 18:38:53 torek 13 12
c misc cleanups
e
s 00014/00000/00515
d D 7.12 91/11/20 16:39:44 marc 12 11
c 3100 changes (from ralph)
e
s 00007/00007/00508
d D 7.11 91/08/28 15:42:28 mckusick 11 10
c vm_stat is merged into vmmeter structure
e
s 00010/00002/00505
d D 7.10 91/08/15 16:45:18 william 10 9
c temporary and permanent changes for i386, correcting bug where
c the "hole" is allocated as ordinary memory, testing for if we allocate it 
c in the page structures themselves, touchup the "kstack-in-the-user-space" 
c kludge, and obscure fix to spontaineous unwiring of kstack (if ever pagable)
e
s 00007/00007/00500
d D 7.9 91/07/25 23:01:07 mckusick 9 8
c vm_page_free_count moves to vm_stat.free_count
e
s 00002/00001/00505
d D 7.8 91/05/15 20:28:57 mckusick 8 7
c add global variable that can be patched to let buufer pool be read
e
s 00008/00001/00498
d D 7.7 91/05/12 22:05:18 william 7 6
c i386 don't inherit pagetables
e
s 00002/00002/00497
d D 7.6 91/05/10 18:03:06 hibler 6 5
c correct buffer-cache address range check
e
s 00053/00010/00424
d D 7.5 91/05/07 09:44:50 hibler 5 4
c hibler: special checking in kernacc for buffer cache
c hibler: kludge to make sure pcb/kstack pages are referenced and modified
c william: kludge for apparently unworking VM_INHERIT_NONE
e
s 00036/00060/00398
d D 7.4 91/05/02 14:19:54 karels 4 3
c move pcb, stack copy to cpu_fork; copy only useful parts of user struct
e
s 00025/00003/00433
d D 7.3 91/04/21 18:36:07 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00102/00119/00334
d D 7.2 91/04/20 10:48:04 karels 2 1
c fix includes; new proc struct; rm *_NULL;
c procdup => vm_fork; clean up sched, swapout
e
s 00453/00000/00000
d D 7.1 90/12/05 18:07:44 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1987 Carnegie-Mellon University
E 3
D 28
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 28
I 28
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 28
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
D 3
 * The CMU software License Agreement specifies the terms and conditions
 * for use and redistribution.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
I 3
 *
 *
 * Copyright (c) 1987, 1990 Carnegie-Mellon University.
 * All rights reserved.
 * 
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND 
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
E 3
 */

D 15
#include "param.h"
#include "systm.h"
D 2
#include "user.h"
E 2
#include "proc.h"
I 2
#include "resourcevar.h"
E 2
#include "buf.h"
I 2
#include "user.h"
E 15
I 15
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
#include <sys/buf.h>
#include <sys/user.h>
E 15
E 2

D 2
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_page.h"
#include "../vm/vm_kern.h"
E 2
I 2
D 15
#include "vm.h"
#include "vm_page.h"
#include "vm_kern.h"
E 15
I 15
#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_kern.h>
E 15
E 2

I 33
#include <machine/cpu.h>

E 33
int	avefree = 0;		/* XXX */
unsigned maxdmap = MAXDSIZ;	/* XXX */
I 8
int	readbuffers = 0;	/* XXX allow kgdb to read kernel buffer pool */
E 8

I 15
int
E 15
kernacc(addr, len, rw)
	caddr_t addr;
	int len, rw;
{
	boolean_t rv;
I 5
	vm_offset_t saddr, eaddr;
E 5
	vm_prot_t prot = rw == B_READ ? VM_PROT_READ : VM_PROT_WRITE;

D 5
	rv = vm_map_check_protection(kernel_map, trunc_page(addr),
				     round_page(addr+len-1), prot);
E 5
I 5
	saddr = trunc_page(addr);
D 27
	eaddr = round_page(addr+len-1);
E 27
I 27
	eaddr = round_page(addr+len);
E 27
	rv = vm_map_check_protection(kernel_map, saddr, eaddr, prot);
	/*
	 * XXX there are still some things (e.g. the buffer cache) that
	 * are managed behind the VM system's back so even though an
	 * address is accessible in the mind of the VM system, there may
	 * not be physical pages where the VM thinks there is.  This can
	 * lead to bogus allocation of pages in the kernel address space
	 * or worse, inconsistencies at the pmap level.  We only worry
	 * about the buffer cache for now.
	 */
D 6
	if (rv && (saddr >= (vm_offset_t)buffers ||
		   eaddr < (vm_offset_t)buffers + MAXBSIZE * nbuf))
E 6
I 6
D 8
	if (rv && (eaddr > (vm_offset_t)buffers &&
E 8
I 8
	if (!readbuffers && rv && (eaddr > (vm_offset_t)buffers &&
E 8
		   saddr < (vm_offset_t)buffers + MAXBSIZE * nbuf))
E 6
		rv = FALSE;
E 5
	return(rv == TRUE);
}

I 15
int
E 15
useracc(addr, len, rw)
	caddr_t addr;
	int len, rw;
{
	boolean_t rv;
	vm_prot_t prot = rw == B_READ ? VM_PROT_READ : VM_PROT_WRITE;

D 2
	rv = vm_map_check_protection(u.u_procp->p_map, trunc_page(addr),
				     round_page(addr+len-1), prot);
E 2
I 2
	rv = vm_map_check_protection(&curproc->p_vmspace->vm_map,
D 27
	    trunc_page(addr), round_page(addr+len-1), prot);
E 27
I 27
	    trunc_page(addr), round_page(addr+len), prot);
E 27
E 2
	return(rv == TRUE);
}

#ifdef KGDB
/*
D 4
 * Change protections on kernel pages from addr to addr+size
E 4
I 4
 * Change protections on kernel pages from addr to addr+len
E 4
 * (presumably so debugger can plant a breakpoint).
D 19
 * All addresses are assumed to reside in the Sysmap,
E 19
I 19
 *
 * We force the protection change at the pmap level.  If we were
 * to use vm_map_protect a change to allow writing would be lazily-
 * applied meaning we would still take a protection fault, something
 * we really don't want to do.  It would also fragment the kernel
 * map unnecessarily.  We cannot use pmap_protect since it also won't
 * enforce a write-enable request.  Using pmap_enter is the only way
 * we can ensure the change takes place properly.
E 19
 */
I 15
void
E 15
chgkprot(addr, len, rw)
	register caddr_t addr;
	int len, rw;
{
D 19
	vm_prot_t prot = rw == B_READ ? VM_PROT_READ : VM_PROT_WRITE;
E 19
I 19
	vm_prot_t prot;
	vm_offset_t pa, sva, eva;
E 19

D 19
	vm_map_protect(kernel_map, trunc_page(addr),
		       round_page(addr+len-1), prot, FALSE);
E 19
I 19
	prot = rw == B_READ ? VM_PROT_READ : VM_PROT_READ|VM_PROT_WRITE;
D 27
	eva = round_page(addr + len - 1);
E 27
I 27
	eva = round_page(addr + len);
E 27
	for (sva = trunc_page(addr); sva < eva; sva += PAGE_SIZE) {
		/*
		 * Extract physical address for the page.
		 * We use a cheezy hack to differentiate physical
		 * page 0 from an invalid mapping, not that it
		 * really matters...
		 */
		pa = pmap_extract(kernel_pmap, sva|1);
		if (pa == 0)
			panic("chgkprot: invalid page");
D 20
		pmap_enter(kernel_pmap, sva, pva&~1, prot, TRUE);
E 20
I 20
		pmap_enter(kernel_pmap, sva, pa&~1, prot, TRUE);
E 20
	}
E 19
}
#endif

I 15
void
E 15
vslock(addr, len)
	caddr_t	addr;
	u_int	len;
{
D 2
	vm_map_pageable(u.u_procp->p_map, trunc_page(addr),
E 2
I 2
	vm_map_pageable(&curproc->p_vmspace->vm_map, trunc_page(addr),
E 2
D 27
			round_page(addr+len-1), FALSE);
E 27
I 27
			round_page(addr+len), FALSE);
E 27
}

I 15
void
E 15
vsunlock(addr, len, dirtied)
	caddr_t	addr;
	u_int	len;
	int dirtied;
{
#ifdef	lint
	dirtied++;
D 24
#endif	lint
E 24
I 24
#endif
E 24
D 2
	vm_map_pageable(u.u_procp->p_map, trunc_page(addr),
E 2
I 2
	vm_map_pageable(&curproc->p_vmspace->vm_map, trunc_page(addr),
E 2
D 27
			round_page(addr+len-1), TRUE);
E 27
I 27
			round_page(addr+len), TRUE);
E 27
}

I 4
/*
 * Implement fork's actions on an address space.
 * Here we arrange for the address space to be copied or referenced,
 * allocate a user struct (pcb and kernel stack), then call the
 * machine-dependent layer to fill those in and make the new process
 * ready to run.
 * NOTE: the kernel stack may be at a different location in the child
 * process, and thus addresses of automatic variables may be invalid
 * after cpu_fork returns in the child process.  We do nothing here
 * after cpu_fork returns.
 */
I 15
int
E 15
E 4
D 2
procdup(p, isvfork)
	register struct proc *p;
E 2
I 2
vm_fork(p1, p2, isvfork)
	register struct proc *p1, *p2;
E 2
	int isvfork;
{
	register struct user *up;
	vm_offset_t addr;
D 4
	vm_size_t size;
E 4

I 7
#ifdef i386
	/*
	 * avoid copying any of the parent's pagetables or other per-process
	 * objects that reside in the map by marking all of them non-inheritable
	 */
	(void)vm_map_inherit(&p1->p_vmspace->vm_map,
		UPT_MIN_ADDRESS-UPAGES*NBPG, VM_MAX_ADDRESS, VM_INHERIT_NONE);
#endif
E 7
D 2
#if 0
	/*
	 * Duplicate the process address space.
	 * XXX if this is a vfork we arrange to share data/stack to
	 *     preserve brain-dead semantics of vfork().
	 * XXX this doesn't work due to a bug in the VM code.
	 *     Once a process has done a vfork setting up sharing maps,
	 *     any future forks may fail as the source VM range doesn't
	 *     properly get write-protected.  This causes the parent to
	 *     not create copies and instead modifies the originals.
	 *     If the parent activates before the child, the child will
	 *     get a corrupted address space.
	 */
	if (isvfork) {
		addr = trunc_page(u.u_daddr);
		size = ctob(u.u_dsize);
		(void) vm_map_inherit(u.u_procp->p_map, addr,
				      addr + size, VM_INHERIT_SHARE);
		(void) vm_map_inherit(u.u_procp->p_map, u.u_maxsaddr,
				      VM_MAX_ADDRESS, VM_INHERIT_SHARE);
	}
E 2
I 2
	p2->p_vmspace = vmspace_fork(p1->p_vmspace);

#ifdef SYSVSHM
	if (p1->p_vmspace->vm_shm)
		shmfork(p1, p2, isvfork);
E 2
#endif
D 2
	p->p_map = vm_map_fork(u.u_procp->p_map);
#if 0
	if (isvfork) {
		(void) vm_map_inherit(u.u_procp->p_map, addr,
				      addr + size, VM_INHERIT_COPY);
		(void) vm_map_inherit(u.u_procp->p_map, u.u_maxsaddr,
				      VM_MAX_ADDRESS, VM_INHERIT_COPY);
	}
#endif
E 2
I 2

I 10
#ifndef	i386
E 10
E 2
	/*
D 4
	 * Allocate a wired-down (for now) u-area for the process
E 4
I 4
	 * Allocate a wired-down (for now) pcb and kernel stack for the process
E 4
	 */
D 4
	size = round_page(ctob(UPAGES));
	addr = kmem_alloc_pageable(kernel_map, size);
D 2
	vm_map_pageable(kernel_map, addr, addr+size, FALSE);
	p->p_addr = (caddr_t)addr;
E 2
I 2
	vm_map_pageable(kernel_map, addr, addr + size, FALSE);
	p2->p_addr = (caddr_t)addr;
E 4
I 4
	addr = kmem_alloc_pageable(kernel_map, ctob(UPAGES));
I 22
	if (addr == 0)
D 23
		panic("vm_fork: no more kernel virtual memory\n");
E 23
I 23
		panic("vm_fork: no more kernel virtual memory");
E 23
E 22
	vm_map_pageable(kernel_map, addr, addr + ctob(UPAGES), FALSE);
I 10
#else
/* XXX somehow, on 386, ocassionally pageout removes active, wired down kstack,
and pagetables, WITHOUT going thru vm_page_unwire! Why this appears to work is
not yet clear, yet it does... */
	addr = kmem_alloc(kernel_map, ctob(UPAGES));
I 22
	if (addr == 0)
D 23
		panic("vm_fork: no more kernel virtual memory\n");
E 23
I 23
		panic("vm_fork: no more kernel virtual memory");
E 23
E 22
#endif
E 10
E 4
E 2
	up = (struct user *)addr;
I 4
	p2->p_addr = up;
E 4

	/*
D 4
	 * Update the current u-area and copy it to the new one
I 2
	 * THIS SHOULD BE DONE DIFFERENTLY, probably with a single
	 * machine-dependent call that copies and updates the pcb+stack,
	 * replacing the resume and savectx.
E 2
	 */
D 2
	resume(pcbb(u.u_procp));
	bcopy(u.u_procp->p_addr, p->p_addr, size);
	up->u_procp = p;
	PMAP_ACTIVATE(p->p_map->pmap, (struct pcb *)p->p_addr);
E 2
I 2
	resume(pcbb(p1));
	bcopy(p1->p_addr, p2->p_addr, size);
	/*
E 4
	 * p_stats and p_sigacts currently point at fields
	 * in the user struct but not at &u, instead at p_addr.
I 4
	 * Copy p_sigacts and parts of p_stats; zero the rest
	 * of p_stats (statistics).
E 4
	 */
D 4
	p2->p_stats = &((struct user *)p2->p_addr)->u_stats;
	p2->p_sigacts = &((struct user *)p2->p_addr)->u_sigacts;
E 4
I 4
	p2->p_stats = &up->u_stats;
	p2->p_sigacts = &up->u_sigacts;
	up->u_sigacts = *p1->p_sigacts;
	bzero(&up->u_stats.pstat_startzero,
	    (unsigned) ((caddr_t)&up->u_stats.pstat_endzero -
	    (caddr_t)&up->u_stats.pstat_startzero));
	bcopy(&p1->p_stats->pstat_startcopy, &up->u_stats.pstat_startcopy,
	    ((caddr_t)&up->u_stats.pstat_endcopy -
	     (caddr_t)&up->u_stats.pstat_startcopy));
E 4
E 2

I 5
#ifdef i386
D 7
	/* bug in inherit_none? */
E 7
	{ u_int addr = UPT_MIN_ADDRESS - UPAGES*NBPG; struct vm_map *vp;

	vp = &p2->p_vmspace->vm_map;
D 10
	(void)vm_map_pageable(vp, addr, 0xfe000000 - addr, TRUE);
	(void)vm_deallocate(vp, addr, 0xfe000000 - addr);
E 10
I 10
	(void)vm_deallocate(vp, addr, UPT_MAX_ADDRESS - addr);
E 10
	(void)vm_allocate(vp, &addr, UPT_MAX_ADDRESS - addr, FALSE);
	(void)vm_map_inherit(vp, addr, UPT_MAX_ADDRESS, VM_INHERIT_NONE);
	}
#endif
E 5
	/*
I 2
D 4
	 * Clear vm statistics of new process.
E 4
I 4
	 * cpu_fork will copy and update the kernel stack and pcb,
	 * and make the child ready to run.  It marks the child
	 * so that it can return differently than the parent.
	 * It returns twice, once in the parent process and
	 * once in the child.
E 4
	 */
D 4
	bzero((caddr_t)&up->u_stats.p_ru, sizeof (struct rusage));
	bzero((caddr_t)&up->u_stats.p_cru, sizeof (struct rusage));

	PMAP_ACTIVATE(&p2->p_vmspace->vm_pmap, (struct pcb *)p2->p_addr, 0);

	/*
E 2
	 * Arrange for a non-local goto when the new process
	 * is started, to resume here, returning nonzero from setjmp.
	 */
	up->u_pcb.pcb_sswap = (int *)&u.u_ssave;
	if (savectx(&up->u_ssave)) {
		/*
		 * Return 1 in child.
		 */
		return (1);
	}
D 2

	/*
	 * Clear vm statistics of new process.
	 */
	bzero((caddr_t)&up->u_ru, sizeof (struct rusage));
	bzero((caddr_t)&up->u_cru, sizeof (struct rusage));
	up->u_outime = 0;
E 2
	return (0);
E 4
I 4
	return (cpu_fork(p1, p2));
E 4
}

/*
D 2
 * XXX Scaled down version from vm_page.c
E 2
I 2
 * Set default limits for VM system.
 * Called for proc 0, and then inherited by all others.
E 2
 */
I 15
void
E 15
D 2
vminit()
E 2
I 2
vm_init_limits(p)
	register struct proc *p;
E 2
{
I 2

E 2
	/*
	 * Set up the initial limits on process VM.
	 * Set the maximum resident set size to be all
	 * of (reasonably) available memory.  This causes
	 * any single, large process to start random page
	 * replacement once it fills memory.
	 */
D 2
        u.u_rlimit[RLIMIT_STACK].rlim_cur = DFLSSIZ;
        u.u_rlimit[RLIMIT_STACK].rlim_max = MAXSSIZ;
        u.u_rlimit[RLIMIT_DATA].rlim_cur = DFLDSIZ;
        u.u_rlimit[RLIMIT_DATA].rlim_max = MAXDSIZ;
	u.u_rlimit[RLIMIT_RSS].rlim_cur = u.u_rlimit[RLIMIT_RSS].rlim_max =
E 2
I 2
        p->p_rlimit[RLIMIT_STACK].rlim_cur = DFLSSIZ;
        p->p_rlimit[RLIMIT_STACK].rlim_max = MAXSSIZ;
        p->p_rlimit[RLIMIT_DATA].rlim_cur = DFLDSIZ;
        p->p_rlimit[RLIMIT_DATA].rlim_max = MAXDSIZ;
D 21
	p->p_rlimit[RLIMIT_RSS].rlim_cur = p->p_rlimit[RLIMIT_RSS].rlim_max =
E 2
D 9
		ptoa(vm_page_free_count);
E 9
I 9
D 11
		ptoa(vm_stat.free_count);
E 11
I 11
		ptoa(cnt.v_free_count);
E 21
I 21
	p->p_rlimit[RLIMIT_RSS].rlim_cur = ptoa(cnt.v_free_count);
E 21
E 11
E 9
D 2
	proc[0].p_maxrss = vm_page_free_count;
E 2
}

D 18
#include "../vm/vm_pageout.h"
E 18
I 18
#include <vm/vm_pageout.h>
E 18

#ifdef DEBUG
int	enableswap = 1;
int	swapdebug = 0;
#define	SDB_FOLLOW	1
#define SDB_SWAPIN	2
#define SDB_SWAPOUT	4
#endif

/*
 * Brutally simple:
 *	1. Attempt to swapin every swaped-out, runnable process in
 *	   order of priority.
 *	2. If not enough memory, wake the pageout daemon and let it
 *	   clear some space.
 */
I 15
void
E 15
D 29
sched()
E 29
I 29
scheduler()
E 29
{
D 2
	register struct proc *rp;
	register int rppri;
	struct proc *inp;
	int inpri;
E 2
I 2
	register struct proc *p;
	register int pri;
	struct proc *pp;
	int ppri;
E 2
	vm_offset_t addr;
	vm_size_t size;

loop:
#ifdef DEBUG
D 13
	if (!enableswap) {
D 2
		inp = NULL;
E 2
I 2
		pp = NULL;
E 2
		goto noswap;
	}
E 13
I 13
	while (!enableswap)
D 35
		sleep((caddr_t)&proc0, PVM);
E 35
I 35
		tsleep((caddr_t)&proc0, PVM, "noswap", 0);
E 35
E 13
#endif
D 2
	wantin = 0;
	inp = NULL;
	inpri = -20000;
	for (rp = allproc; rp != NULL; rp = rp->p_nxt)
		if (rp->p_stat == SRUN && (rp->p_flag & SLOAD) == 0) {
			rppri = rp->p_time +
				rp->p_slptime - (rp->p_nice-NZERO)*8;
			if (rppri > inpri) {
				inp = rp;
				inpri = rppri;
E 2
I 2
	pp = NULL;
	ppri = INT_MIN;
D 13
	for (p = allproc; p != NULL; p = p->p_nxt)
E 13
I 13
D 17
	for (p = allproc; p != NULL; p = p->p_nxt) {
E 17
I 17
D 31
	for (p = (struct proc *)allproc; p != NULL; p = p->p_nxt) {
E 17
E 13
		if (p->p_stat == SRUN && (p->p_flag & SLOAD) == 0) {
			pri = p->p_time + p->p_slptime - p->p_nice * 8;
E 31
I 31
D 34
	for (p = (struct proc *)allproc; p != NULL; p = p->p_next) {
E 34
I 34
	for (p = allproc.lh_first; p != 0; p = p->p_list.le_next) {
E 34
		if (p->p_stat == SRUN && (p->p_flag & P_INMEM) == 0) {
I 36
			/* XXX should also penalize based on vm_swrss */
E 36
			pri = p->p_swtime + p->p_slptime - p->p_nice * 8;
E 31
			if (pri > ppri) {
				pp = p;
				ppri = pri;
E 2
			}
		}
I 13
	}
E 13
#ifdef DEBUG
	if (swapdebug & SDB_FOLLOW)
D 2
		printf("sched: running, procp %x pri %d\n", inp, inpri);
E 2
I 2
D 35
		printf("sched: running, procp %x pri %d\n", pp, ppri);
E 35
I 35
		printf("scheduler: running, procp %x pri %d\n", pp, ppri);
E 35
E 2
D 13
noswap:
E 13
#endif
	/*
	 * Nothing to do, back to sleep
	 */
D 2
	if ((rp = inp) == NULL) {
		(void) splhigh();
		runout++;
		sleep((caddr_t)&runout, PVM);
		(void) spl0();
E 2
I 2
	if ((p = pp) == NULL) {
D 35
		sleep((caddr_t)&proc0, PVM);
E 35
I 35
		tsleep((caddr_t)&proc0, PVM, "scheduler", 0);
E 35
E 2
		goto loop;
	}
I 2

E 2
	/*
	 * We would like to bring someone in.
	 * This part is really bogus cuz we could deadlock on memory
	 * despite our feeble check.
I 36
	 * XXX should require at least vm_swrss / 2
E 36
	 */
	size = round_page(ctob(UPAGES));
D 2
	addr = (vm_offset_t) rp->p_addr;
E 2
I 2
	addr = (vm_offset_t) p->p_addr;
E 2
D 9
	if (vm_page_free_count > atop(size)) {
E 9
I 9
D 11
	if (vm_stat.free_count > atop(size)) {
E 11
I 11
	if (cnt.v_free_count > atop(size)) {
E 11
E 9
#ifdef DEBUG
		if (swapdebug & SDB_SWAPIN)
			printf("swapin: pid %d(%s)@%x, pri %d free %d\n",
D 2
			       rp->p_pid, rp->p_comm, rp->p_addr,
			       inpri, vm_page_free_count);
E 2
I 2
			       p->p_pid, p->p_comm, p->p_addr,
D 9
			       ppri, vm_page_free_count);
E 9
I 9
D 11
			       ppri, vm_stat.free_count);
E 11
I 11
			       ppri, cnt.v_free_count);
E 11
E 9
E 2
#endif
		vm_map_pageable(kernel_map, addr, addr+size, FALSE);
I 32
		/*
		 * Some architectures need to be notified when the
		 * user area has moved to new physical page(s) (e.g.
		 * see pmax/pmax/vm_machdep.c).
		 */
		cpu_swapin(p);
E 32
D 17
		(void) splclock();
E 17
I 17
		(void) splstatclock();
E 17
D 2
		if (rp->p_stat == SRUN)
			setrq(rp);
		rp->p_flag |= SLOAD;
E 2
I 2
		if (p->p_stat == SRUN)
D 30
			setrq(p);
E 30
I 30
			setrunqueue(p);
E 30
D 31
		p->p_flag |= SLOAD;
E 31
I 31
		p->p_flag |= P_INMEM;
E 31
E 2
		(void) spl0();
D 2
		rp->p_time = 0;
E 2
I 2
D 31
		p->p_time = 0;
E 31
I 31
		p->p_swtime = 0;
E 31
E 2
		goto loop;
	}
	/*
	 * Not enough memory, jab the pageout daemon and wait til the
	 * coast is clear.
	 */
#ifdef DEBUG
	if (swapdebug & SDB_FOLLOW)
D 35
		printf("sched: no room for pid %d(%s), free %d\n",
E 35
I 35
		printf("scheduler: no room for pid %d(%s), free %d\n",
E 35
D 2
		       rp->p_pid, rp->p_comm, vm_page_free_count);
E 2
I 2
D 9
		       p->p_pid, p->p_comm, vm_page_free_count);
E 9
I 9
D 11
		       p->p_pid, p->p_comm, vm_stat.free_count);
E 11
I 11
		       p->p_pid, p->p_comm, cnt.v_free_count);
E 11
E 9
E 2
#endif
	(void) splhigh();
	VM_WAIT;
	(void) spl0();
#ifdef DEBUG
	if (swapdebug & SDB_FOLLOW)
D 9
		printf("sched: room again, free %d\n", vm_page_free_count);
E 9
I 9
D 11
		printf("sched: room again, free %d\n", vm_stat.free_count);
E 11
I 11
D 35
		printf("sched: room again, free %d\n", cnt.v_free_count);
E 35
I 35
		printf("scheduler: room again, free %d\n", cnt.v_free_count);
E 35
E 11
E 9
#endif
	goto loop;
}

D 31
#define	swappable(p) \
D 2
	(((p)->p_flag & (SSYS|SULOCK|SLOAD|SKEEP|SWEXIT|SPHYSIO)) == SLOAD)
E 2
I 2
	(((p)->p_flag & (SSYS|SLOAD|SKEEP|SWEXIT|SPHYSIO)) == SLOAD)
E 31
I 31
#define	swappable(p)							\
	(((p)->p_flag &							\
	    (P_SYSTEM | P_INMEM | P_NOSWAP | P_WEXIT | P_PHYSIO)) == P_INMEM)
E 31
E 2

/*
 * Swapout is driven by the pageout daemon.  Very simple, we find eligible
 * procs and unwire their u-areas.  We try to always "swap" at least one
 * process in case we need the room for a swapin.
I 2
 * If any procs have been sleeping/stopped for at least maxslp seconds,
 * they are swapped.  Else, we swap the longest-sleeping or stopped process,
 * if any, otherwise the longest-resident process.
E 2
 */
I 15
void
E 15
swapout_threads()
{
D 2
	register struct proc *rp;
E 2
I 2
	register struct proc *p;
E 2
	struct proc *outp, *outp2;
	int outpri, outpri2;
	int didswap = 0;
	extern int maxslp;

#ifdef DEBUG
	if (!enableswap)
		return;
#endif
	outp = outp2 = NULL;
D 2
	outpri = outpri2 = -20000;
	for (rp = allproc; rp != NULL; rp = rp->p_nxt) {
		if (!swappable(rp))
E 2
I 2
	outpri = outpri2 = 0;
D 17
	for (p = allproc; p != NULL; p = p->p_nxt) {
E 17
I 17
D 31
	for (p = (struct proc *)allproc; p != NULL; p = p->p_nxt) {
E 31
I 31
D 34
	for (p = (struct proc *)allproc; p != NULL; p = p->p_next) {
E 34
I 34
	for (p = allproc.lh_first; p != 0; p = p->p_list.le_next) {
E 34
E 31
E 17
		if (!swappable(p))
E 2
			continue;
D 2
		switch(rp->p_stat) {
E 2
I 2
		switch (p->p_stat) {
E 2
		case SRUN:
D 2
			if (rp->p_slptime > outpri2) {
				outp2 = rp;
				outpri2 = rp->p_slptime;
E 2
I 2
D 31
			if (p->p_time > outpri2) {
E 31
I 31
			if (p->p_swtime > outpri2) {
E 31
				outp2 = p;
D 31
				outpri2 = p->p_time;
E 31
I 31
				outpri2 = p->p_swtime;
E 31
E 2
			}
			continue;
			
		case SSLEEP:
		case SSTOP:
D 2
			if (rp->p_slptime > maxslp) {
				swapout(rp);
E 2
I 2
D 25
			if (p->p_slptime > maxslp) {
E 25
I 25
			if (p->p_slptime >= maxslp) {
E 25
				swapout(p);
E 2
				didswap++;
D 2
			} else if (rp->p_slptime > outpri) {
				outp = rp;
				outpri = rp->p_slptime;
E 2
I 2
			} else if (p->p_slptime > outpri) {
				outp = p;
				outpri = p->p_slptime;
E 2
			}
			continue;
		}
	}
	/*
	 * If we didn't get rid of any real duds, toss out the next most
	 * likely sleeping/stopped or running candidate.  We only do this
	 * if we are real low on memory since we don't gain much by doing
	 * it (UPAGES pages).
	 */
	if (didswap == 0 &&
D 9
	    vm_page_free_count <= atop(round_page(ctob(UPAGES)))) {
E 9
I 9
D 11
	    vm_stat.free_count <= atop(round_page(ctob(UPAGES)))) {
E 11
I 11
	    cnt.v_free_count <= atop(round_page(ctob(UPAGES)))) {
E 11
E 9
D 2
		if ((rp = outp) == 0)
			rp = outp2;
E 2
I 2
		if ((p = outp) == 0)
			p = outp2;
E 2
#ifdef DEBUG
		if (swapdebug & SDB_SWAPOUT)
D 2
			printf("swapout_threads: no duds, try procp %x\n", rp);
E 2
I 2
			printf("swapout_threads: no duds, try procp %x\n", p);
E 2
#endif
D 2
		if (rp)
			swapout(rp);
E 2
I 2
		if (p)
			swapout(p);
E 2
	}
}

I 15
void
E 15
swapout(p)
	register struct proc *p;
{
	vm_offset_t addr;
	vm_size_t size;

#ifdef DEBUG
	if (swapdebug & SDB_SWAPOUT)
		printf("swapout: pid %d(%s)@%x, stat %x pri %d free %d\n",
		       p->p_pid, p->p_comm, p->p_addr, p->p_stat,
D 9
		       p->p_slptime, vm_page_free_count);
E 9
I 9
D 11
		       p->p_slptime, vm_stat.free_count);
E 11
I 11
		       p->p_slptime, cnt.v_free_count);
E 11
E 9
#endif
	size = round_page(ctob(UPAGES));
	addr = (vm_offset_t) p->p_addr;
I 5
D 16
#ifdef hp300
E 16
I 16
#if defined(hp300) || defined(luna68k)
E 16
	/*
	 * Ugh!  u-area is double mapped to a fixed address behind the
	 * back of the VM system and accesses are usually through that
	 * address rather than the per-process address.  Hence reference
	 * and modify information are recorded at the fixed address and
	 * lost at context switch time.  We assume the u-struct and
	 * kernel stack are always accessed/modified and force it to be so.
	 */
	{
		register int i;
		volatile long tmp;

		for (i = 0; i < UPAGES; i++) {
			tmp = *(long *)addr; *(long *)addr = tmp;
			addr += NBPG;
		}
		addr = (vm_offset_t) p->p_addr;
	}
#endif
I 12
#ifdef mips
	/*
	 * Be sure to save the floating point coprocessor state before
	 * paging out the u-struct.
	 */
	{
		extern struct proc *machFPCurProcPtr;

		if (p == machFPCurProcPtr) {
			MachSaveCurFPState(p);
			machFPCurProcPtr = (struct proc *)0;
		}
	}
#endif
E 12
I 10
#ifndef	i386 /* temporary measure till we find spontaineous unwire of kstack */
E 10
E 5
	vm_map_pageable(kernel_map, addr, addr+size, TRUE);
D 2
	pmap_collect(vm_map_pmap(p->p_map));
E 2
I 2
	pmap_collect(vm_map_pmap(&p->p_vmspace->vm_map));
I 10
#endif
E 10
E 2
	(void) splhigh();
D 31
	p->p_flag &= ~SLOAD;
E 31
I 31
	p->p_flag &= ~P_INMEM;
E 31
	if (p->p_stat == SRUN)
		remrq(p);
	(void) spl0();
D 31
	p->p_time = 0;
E 31
I 31
	p->p_swtime = 0;
E 31
}

/*
 * The rest of these routines fake thread handling
 */

void
assert_wait(event, ruptible)
D 35
	int event;
E 35
I 35
	void *event;
E 35
	boolean_t ruptible;
{
#ifdef lint
	ruptible++;
#endif
D 2
	u.u_procp->p_thread = event;
E 2
I 2
	curproc->p_thread = event;
E 2
}

void
thread_block()
{
	int s = splhigh();

D 2
	if (u.u_procp->p_thread)
		sleep((caddr_t)u.u_procp->p_thread, PVM);
E 2
I 2
	if (curproc->p_thread)
D 35
		sleep((caddr_t)curproc->p_thread, PVM);
E 35
I 35
		tsleep(curproc->p_thread, PVM, "thrd_block", 0);
E 35
E 2
	splx(s);
}

I 14
void
E 14
D 2
void
E 2
thread_sleep(event, lock, ruptible)
D 35
	int event;
E 35
I 35
	void *event;
E 35
	simple_lock_t lock;
	boolean_t ruptible;
{
I 35
	int s = splhigh();

E 35
#ifdef lint
	ruptible++;
#endif
D 35
	int s = splhigh();

E 35
D 2
	u.u_procp->p_thread = event;
E 2
I 2
	curproc->p_thread = event;
E 2
	simple_unlock(lock);
D 2
	if (u.u_procp->p_thread)
		sleep((caddr_t)u.u_procp->p_thread, PVM);
E 2
I 2
	if (curproc->p_thread)
D 35
		sleep((caddr_t)event, PVM);
E 35
I 35
		tsleep(event, PVM, "thrd_sleep", 0);
E 35
E 2
	splx(s);
}

I 14
void
E 14
D 2
void
E 2
thread_wakeup(event)
D 35
	int event;
E 35
I 35
	void *event;
E 35
{
	int s = splhigh();

D 35
	wakeup((caddr_t)event);
E 35
I 35
	wakeup(event);
E 35
	splx(s);
}

/*
 * DEBUG stuff
 */

int indent = 0;

I 13
#include <machine/stdarg.h>		/* see subr_prf.c */

E 13
/*ARGSUSED2*/
I 15
void
E 15
D 13
iprintf(a, b, c, d, e, f, g, h)
	char *a;
E 13
I 13
#if __STDC__
iprintf(const char *fmt, ...)
#else
iprintf(fmt /* , va_alist */)
	char *fmt;
	/* va_dcl */
#endif
E 13
{
	register int i;
I 13
	va_list ap;
E 13

D 5
	for (i = indent; i > 0; ) {
		if (i >= 8) {
			putchar('\t', 1, (caddr_t)0);
			i -= 8;
		} else {
			putchar(' ', 1, (caddr_t)0);
			i--;
		}
E 5
I 5
D 13
	i = indent;
	while (i >= 8) {
E 13
I 13
	for (i = indent; i >= 8; i -= 8)
E 13
		printf("\t");
D 13
		i -= 8;
E 5
	}
I 5
	for (; i > 0; --i)
E 13
I 13
	while (--i >= 0)
E 13
		printf(" ");
E 5
D 13
	printf(a, b, c, d, e, f, g, h);
E 13
I 13
	va_start(ap, fmt);
	printf("%r", fmt, ap);
	va_end(ap);
E 13
}
E 1
