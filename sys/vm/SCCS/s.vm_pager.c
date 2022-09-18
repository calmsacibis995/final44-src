h06278
s 00021/00001/00354
d D 8.7 94/07/07 21:55:57 hibler 19 18
c don't use GCC-isms in MI code (from cgd)
e
s 00127/00042/00228
d D 8.6 94/01/12 16:05:53 hibler 18 17
c multi-page interface for get/put.
e
s 00000/00001/00270
d D 8.5 94/01/04 22:23:53 bostic 17 16
c lint
e
s 00003/00006/00268
d D 8.4 93/12/30 16:01:32 mckusick 16 15
c convert to use new queue structures
e
s 00015/00003/00259
d D 8.3 93/11/14 13:57:06 hibler 15 14
c keep indices constant even if a pager is not configured
e
s 00003/00002/00259
d D 8.2 93/11/10 10:58:30 torek 14 13
c finish up new device pager: all pagers get offsets
e
s 00002/00002/00259
d D 8.1 93/06/11 16:38:28 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00015/00252
d D 7.12 93/04/17 18:54:16 torek 12 11
c all pagers change from pseudo-devices to options
e
s 00002/00002/00265
d D 7.11 93/02/03 20:54:14 mckusick 11 10
c avoid panic's on msync'ing active pages
e
s 00001/00001/00266
d D 7.10 92/11/29 10:22:20 hibler 10 9
c cleanup
e
s 00005/00005/00262
d D 7.9 92/10/01 17:54:26 mckusick 9 8
c convert vm_page bit fields to flags
e
s 00009/00005/00258
d D 7.8 92/05/04 17:25:25 bostic 8 7
c new include format; lint
e
s 00006/00006/00257
d D 7.7 92/03/01 15:28:10 mckusick 7 6
c allow subset of pagers to be defined (net2/sys/7)
e
s 00004/00001/00259
d D 7.6 91/08/28 15:47:10 mckusick 6 5
c can_persist bit field replaced with a flag
e
s 00011/00007/00249
d D 7.5 91/07/15 16:54:27 mckusick 5 4
c avoid illegal &0 definitions (from bowen@cs.Buffalo.EDU)
e
s 00023/00018/00233
d D 7.4 91/05/07 09:36:16 hibler 4 3
c use pmap_enter/remove instead of hard PTE ops
c (requires kludge in pmap module)
e
s 00027/00004/00224
d D 7.3 91/04/21 18:36:22 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00021/00022/00207
d D 7.2 91/04/20 10:50:21 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00229/00000/00000
d D 7.1 90/12/05 18:08:35 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1985, 1986 Avadis Tevanian, Jr., Michael Wayne Young
 * Copyright (c) 1987 Carnegie-Mellon University
E 3
D 13
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
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
 * Authors: Avadis Tevanian, Jr., Michael Wayne Young
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

/*
 *	Paging space routine stubs.  Emulates a matchmaker-like interface
 *	for builtin pagers.
 */

D 8
#include "param.h"
D 2
#include "queue.h"
E 2
#include "malloc.h"
E 8
I 8
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
E 8

D 2
#include "../vm/vm_param.h"
#include "../vm/vm_pager.h"
#include "../vm/vm_page.h"
#include "../vm/vm_prot.h"
#include "../vm/vm_map.h"
#include "../vm/vm_kern.h"
E 2
I 2
D 8
#include "vm.h"
#include "vm_page.h"
#include "vm_kern.h"
E 8
I 8
#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_kern.h>
E 8
E 2

D 2
#include "../vm/pmap.h"
E 2
I 2
D 4
#ifdef hp300
#include "../hp300/hp300/pte.h"			/* XXX XXX XXX */
#endif
E 2

E 4
D 12
#include "swappager.h"
I 2
D 5

E 5
E 2
#if NSWAPPAGER > 0
E 12
I 12
#ifdef SWAPPAGER
E 12
extern struct pagerops swappagerops;
I 5
D 12
#define	swappagerops_p	&swappagerops
E 12
E 5
D 7
#else
D 2
#define	swappagerops	PAGER_OPS_NULL
E 2
I 2
D 5
#define	swappagerops	NULL
E 5
I 5
#define	swappagerops_p	NULL
E 7
E 5
E 2
#endif
I 5

E 5
D 12
#include "vnodepager.h"
#if NVNODEPAGER > 0
E 12
I 12
#ifdef VNODEPAGER
E 12
extern struct pagerops vnodepagerops;
I 5
D 12
#define	vnodepagerops_p	&vnodepagerops
E 12
E 5
D 7
#else
D 2
#define	vnodepagerops	PAGER_OPS_NULL
E 2
I 2
D 5
#define	vnodepagerops	NULL
E 5
I 5
#define	vnodepagerops_p	NULL
E 7
E 5
E 2
#endif
I 5

E 5
D 12
#include "devpager.h"
#if NDEVPAGER > 0
E 12
I 12
#ifdef DEVPAGER
E 12
extern struct pagerops devicepagerops;
I 5
D 12
#define	devicepagerops_p &devicepagerops
E 12
E 5
D 7
#else
D 2
#define	devicepagerops	PAGER_OPS_NULL
E 2
I 2
D 5
#define	devicepagerops	NULL
E 5
I 5
#define	devicepagerops_p NULL
E 7
E 5
E 2
#endif

struct pagerops *pagertab[] = {
I 7
D 12
#if NSWAPPAGER > 0
E 7
D 5
	&swappagerops,		/* PG_SWAP */
	&vnodepagerops,		/* PG_VNODE */
	&devicepagerops,	/* PG_DEV */
E 5
I 5
	swappagerops_p,		/* PG_SWAP */
E 12
I 12
#ifdef SWAPPAGER
	&swappagerops,		/* PG_SWAP */
I 15
#else
	NULL,
E 15
E 12
I 7
#endif
D 12
#if NVNODEPAGER > 0
E 7
	vnodepagerops_p,	/* PG_VNODE */
E 12
I 12
#ifdef VNODEPAGER
	&vnodepagerops,		/* PG_VNODE */
I 15
#else
	NULL,
E 15
E 12
I 7
#endif
D 12
#if NDEVPAGER > 0
E 7
	devicepagerops_p,	/* PG_DEV */
E 12
I 12
#ifdef DEVPAGER
	&devicepagerops,	/* PG_DEV */
I 15
#else
	NULL,
E 15
E 12
I 7
#endif
E 7
E 5
};
int npagers = sizeof (pagertab) / sizeof (pagertab[0]);

D 2
struct pagerops *dfltpagerops = PAGER_OPS_NULL;	/* default pager */
E 2
I 2
struct pagerops *dfltpagerops = NULL;	/* default pager */
E 2

/*
 * Kernel address space for mapping pages.
 * Used by pagers where KVAs are needed for IO.
I 18
 *
 * XXX needs to be large enough to support the number of pending async
 * cleaning requests (NPENDINGIO == 64) * the maximum swap cluster size
 * (MAXPHYS == 64k) if you want to get the most efficiency.
E 18
 */
D 18
#define PAGER_MAP_SIZE	(256 * PAGE_SIZE)
E 18
I 18
#define PAGER_MAP_SIZE	(4 * 1024 * 1024)

E 18
vm_map_t pager_map;
I 18
boolean_t pager_map_wanted;
E 18
I 4
vm_offset_t pager_sva, pager_eva;
E 4

void
vm_pager_init()
{
D 4
	vm_offset_t whocares1, whocares2;
E 4
	struct pagerops **pgops;

	/*
	 * Allocate a kernel submap for tracking get/put page mappings
	 */
D 4
	pager_map = kmem_suballoc(kernel_map, &whocares1, &whocares2,
E 4
I 4
	pager_map = kmem_suballoc(kernel_map, &pager_sva, &pager_eva,
E 4
				  PAGER_MAP_SIZE, FALSE);
	/*
	 * Initialize known pagers
	 */
	for (pgops = pagertab; pgops < &pagertab[npagers]; pgops++)
D 15
		(*(*pgops)->pgo_init)();
E 15
I 15
		if (pgops)
			(*(*pgops)->pgo_init)();
E 15
D 2
	if (dfltpagerops == PAGER_OPS_NULL)
E 2
I 2
	if (dfltpagerops == NULL)
E 2
		panic("no default pager");
}

/*
 * Allocate an instance of a pager of the given type.
I 15
 * Size, protection and offset parameters are passed in for pagers that
 * need to perform page-level validation (e.g. the device pager).
E 15
 */
vm_pager_t
D 14
vm_pager_allocate(type, handle, size, prot)
E 14
I 14
vm_pager_allocate(type, handle, size, prot, off)
E 14
	int type;
	caddr_t handle;
	vm_size_t size;
	vm_prot_t prot;
I 14
	vm_offset_t off;
E 14
{
D 17
	vm_pager_t pager;
E 17
	struct pagerops *ops;

	ops = (type == PG_DFLT) ? dfltpagerops : pagertab[type];
D 14
	return((*ops->pgo_alloc)(handle, size, prot));
E 14
I 14
D 15
	return ((*ops->pgo_alloc)(handle, size, prot, off));
E 15
I 15
	if (ops)
		return ((*ops->pgo_alloc)(handle, size, prot, off));
	return (NULL);
E 15
E 14
}

void
vm_pager_deallocate(pager)
	vm_pager_t	pager;
{
D 2
	if (pager == vm_pager_null)
E 2
I 2
	if (pager == NULL)
E 2
		panic("vm_pager_deallocate: null pager");

D 18
	VM_PAGER_DEALLOC(pager);
E 18
I 18
	(*pager->pg_ops->pgo_dealloc)(pager);
E 18
}

I 8
int
E 8
D 18
vm_pager_get(pager, m, sync)
E 18
I 18
vm_pager_get_pages(pager, mlist, npages, sync)
E 18
	vm_pager_t	pager;
D 18
	vm_page_t	m;
E 18
I 18
	vm_page_t	*mlist;
	int		npages;
E 18
	boolean_t	sync;
{
D 18
	extern boolean_t vm_page_zero_fill();
E 18
I 18
	int rv;
E 18

D 2
	if (pager == vm_pager_null)
E 2
I 2
D 18
	if (pager == NULL)
E 2
		return(vm_page_zero_fill(m) ? VM_PAGER_OK : VM_PAGER_FAIL);
	return(VM_PAGER_GET(pager, m, sync));
E 18
I 18
	if (pager == NULL) {
		rv = VM_PAGER_OK;
		while (npages--)
			if (!vm_page_zero_fill(*mlist)) {
				rv = VM_PAGER_FAIL;
				break;
			} else
				mlist++;
		return (rv);
	}
	return ((*pager->pg_ops->pgo_getpages)(pager, mlist, npages, sync));
E 18
}

I 8
int
E 8
D 18
vm_pager_put(pager, m, sync)
E 18
I 18
vm_pager_put_pages(pager, mlist, npages, sync)
E 18
	vm_pager_t	pager;
D 18
	vm_page_t	m;
E 18
I 18
	vm_page_t	*mlist;
	int		npages;
E 18
	boolean_t	sync;
{
D 2
	if (pager == vm_pager_null)
E 2
I 2
	if (pager == NULL)
E 2
D 18
		panic("vm_pager_put: null pager");
	return(VM_PAGER_PUT(pager, m, sync));
E 18
I 18
		panic("vm_pager_put_pages: null pager");
	return ((*pager->pg_ops->pgo_putpages)(pager, mlist, npages, sync));
E 18
}

I 19
/* XXX compatibility*/
int
vm_pager_get(pager, m, sync)
	vm_pager_t	pager;
	vm_page_t	m;
	boolean_t	sync;
{
	return vm_pager_get_pages(pager, &m, 1, sync);
}

/* XXX compatibility*/
int
vm_pager_put(pager, m, sync)
	vm_pager_t	pager;
	vm_page_t	m;
	boolean_t	sync;
{
	return vm_pager_put_pages(pager, &m, 1, sync);
}

E 19
boolean_t
vm_pager_has_page(pager, offset)
	vm_pager_t	pager;
	vm_offset_t	offset;
{
D 2
	if (pager == vm_pager_null)
E 2
I 2
	if (pager == NULL)
E 2
D 18
		panic("vm_pager_has_page");
	return(VM_PAGER_HASPAGE(pager, offset));
E 18
I 18
		panic("vm_pager_has_page: null pager");
	return ((*pager->pg_ops->pgo_haspage)(pager, offset));
E 18
}

/*
 * Called by pageout daemon before going back to sleep.
 * Gives pagers a chance to clean up any completed async pageing operations.
 */
void
vm_pager_sync()
{
	struct pagerops **pgops;

	for (pgops = pagertab; pgops < &pagertab[npagers]; pgops++)
D 2
		(*(*pgops)->pgo_putpage)(VM_PAGER_NULL, VM_PAGE_NULL, FALSE);
E 2
I 2
D 15
		(*(*pgops)->pgo_putpage)(NULL, NULL, FALSE);
E 15
I 15
		if (pgops)
D 18
			(*(*pgops)->pgo_putpage)(NULL, NULL, FALSE);
E 18
I 18
			(*(*pgops)->pgo_putpages)(NULL, NULL, 0, FALSE);
E 18
E 15
E 2
}

I 18
void
vm_pager_cluster(pager, offset, loff, hoff)
	vm_pager_t	pager;
	vm_offset_t	offset;
	vm_offset_t	*loff;
	vm_offset_t	*hoff;
{
	if (pager == NULL)
		panic("vm_pager_cluster: null pager");
D 19
	return ((*pager->pg_ops->pgo_cluster)(pager, offset, loff, hoff));
E 19
I 19
	((*pager->pg_ops->pgo_cluster)(pager, offset, loff, hoff));
E 19
}

void
vm_pager_clusternull(pager, offset, loff, hoff)
	vm_pager_t	pager;
	vm_offset_t	offset;
	vm_offset_t	*loff;
	vm_offset_t	*hoff;
{
	panic("vm_pager_nullcluster called");
}

E 18
vm_offset_t
D 18
vm_pager_map_page(m)
	vm_page_t	m;
E 18
I 18
vm_pager_map_pages(mlist, npages, canwait)
	vm_page_t	*mlist;
	int		npages;
	boolean_t	canwait;
E 18
{
D 18
	vm_offset_t kva;
E 18
I 18
	vm_offset_t kva, va;
	vm_size_t size;
	vm_page_t m;
E 18

I 18
	/*
	 * Allocate space in the pager map, if none available return 0.
	 * This is basically an expansion of kmem_alloc_wait with optional
	 * blocking on no space.
	 */
	size = npages * PAGE_SIZE;
	vm_map_lock(pager_map);
	while (vm_map_findspace(pager_map, 0, size, &kva)) {
		if (!canwait) {
			vm_map_unlock(pager_map);
			return (0);
		}
		pager_map_wanted = TRUE;
		vm_map_unlock(pager_map);
		(void) tsleep(pager_map, PVM, "pager_map", 0);
		vm_map_lock(pager_map);
	}
	vm_map_insert(pager_map, NULL, 0, kva, kva + size);
	vm_map_unlock(pager_map);

	for (va = kva; npages--; va += PAGE_SIZE) {
		m = *mlist++;
E 18
I 4
#ifdef DEBUG
D 9
	if (!m->busy || m->active)
E 9
I 9
D 10
	if (!(m->flags & PG_BUSY) || (m->flags & PG_ACTIVE))
E 10
I 10
D 11
	if ((m->flags & (PG_BUSY | PG_ACTIVE)) != PG_BUSY)
E 10
E 9
		panic("vm_pager_map_page: page active or not busy");
E 11
I 11
D 18
	if ((m->flags & PG_BUSY) == 0)
		panic("vm_pager_map_page: page not busy");
E 11
D 9
	if (m->pagerowned)
E 9
I 9
	if (m->flags & PG_PAGEROWNED)
E 9
		printf("vm_pager_map_page: page %x already in pager\n", m);
E 18
I 18
		if ((m->flags & PG_BUSY) == 0)
			panic("vm_pager_map_pages: page not busy");
		if (m->flags & PG_PAGEROWNED)
			panic("vm_pager_map_pages: page already in pager");
E 18
#endif
E 4
D 18
	kva = kmem_alloc_wait(pager_map, PAGE_SIZE);
E 18
D 2
#if 1
E 2
I 2
D 4
#ifdef hp300
E 2
	/*
	 * XXX: cannot use pmap_enter as the mapping would be
	 * removed by a pmap_remove_all().
	 */
	*(int *)kvtopte(kva) = VM_PAGE_TO_PHYS(m) | PG_CI | PG_V;
	TBIS(kva);
#else
E 4
I 4
#ifdef DEBUG
D 9
	m->pagerowned = 1;
E 9
I 9
D 18
	m->flags |= PG_PAGEROWNED;
E 18
I 18
		m->flags |= PG_PAGEROWNED;
E 18
E 9
#endif
E 4
D 18
	pmap_enter(vm_map_pmap(pager_map), kva, VM_PAGE_TO_PHYS(m),
		   VM_PROT_DEFAULT, TRUE);
D 4
#endif
E 4
	return(kva);
E 18
I 18
		pmap_enter(vm_map_pmap(pager_map), va, VM_PAGE_TO_PHYS(m),
			   VM_PROT_DEFAULT, TRUE);
	}
	return (kva);
E 18
}

void
D 18
vm_pager_unmap_page(kva)
E 18
I 18
vm_pager_unmap_pages(kva, npages)
E 18
	vm_offset_t	kva;
I 18
	int		npages;
E 18
{
I 18
	vm_size_t size = npages * PAGE_SIZE;

E 18
D 2
#if 1
E 2
I 2
D 4
#ifdef hp300
E 2
	*(int *)kvtopte(kva) = PG_NV;
	TBIS(kva);
E 4
I 4
#ifdef DEBUG
I 18
	vm_offset_t va;
E 18
	vm_page_t m;
I 18
	int np = npages;
E 18

D 18
	m = PHYS_TO_VM_PAGE(pmap_extract(vm_map_pmap(pager_map), kva));
E 18
I 18
	for (va = kva; np--; va += PAGE_SIZE) {
		m = vm_pager_atop(va);
		if (m->flags & PG_PAGEROWNED)
			m->flags &= ~PG_PAGEROWNED;
		else
			printf("vm_pager_unmap_pages: %x(%x/%x) not owned\n",
			       m, va, VM_PAGE_TO_PHYS(m));
	}
E 18
E 4
#endif
I 4
D 18
	pmap_remove(vm_map_pmap(pager_map), kva, kva + PAGE_SIZE);
E 4
	kmem_free_wakeup(pager_map, kva, PAGE_SIZE);
I 4
#ifdef DEBUG
D 9
	if (m->pagerowned)
		m->pagerowned = 0;
E 9
I 9
	if (m->flags & PG_PAGEROWNED)
		m->flags &= ~PG_PAGEROWNED;
E 9
	else
		printf("vm_pager_unmap_page: page %x(%x/%x) not owned\n",
		       m, kva, VM_PAGE_TO_PHYS(m));
#endif
E 18
I 18
	pmap_remove(vm_map_pmap(pager_map), kva, kva + size);
	vm_map_lock(pager_map);
	(void) vm_map_delete(pager_map, kva, kva + size);
	if (pager_map_wanted)
		wakeup(pager_map);
	vm_map_unlock(pager_map);
E 18
E 4
}

I 18
vm_page_t
vm_pager_atop(kva)
	vm_offset_t	kva;
{
	vm_offset_t pa;

	pa = pmap_extract(vm_map_pmap(pager_map), kva);
	if (pa == 0)
		panic("vm_pager_atop");
	return (PHYS_TO_VM_PAGE(pa));
}

E 18
vm_pager_t
D 16
vm_pager_lookup(list, handle)
	register queue_head_t *list;
E 16
I 16
vm_pager_lookup(pglist, handle)
	register struct pagerlst *pglist;
E 16
	caddr_t handle;
{
	register vm_pager_t pager;

D 16
	pager = (vm_pager_t) queue_first(list);
	while (!queue_end(list, (queue_entry_t)pager)) {
E 16
I 16
	for (pager = pglist->tqh_first; pager; pager = pager->pg_list.tqe_next)
E 16
		if (pager->pg_handle == handle)
D 18
			return(pager);
D 16
		pager = (vm_pager_t) queue_next(&pager->pg_list);
	}
E 16
D 2
	return(VM_PAGER_NULL);
E 2
I 2
	return(NULL);
E 18
I 18
			return (pager);
	return (NULL);
E 18
E 2
}

/*
 * This routine gains a reference to the object.
 * Explicit deallocation is necessary.
 */
I 8
int
E 8
pager_cache(object, should_cache)
	vm_object_t	object;
	boolean_t	should_cache;
{
D 2
	if (object == VM_OBJECT_NULL)
E 2
I 2
	if (object == NULL)
E 2
D 18
		return(KERN_INVALID_ARGUMENT);
E 18
I 18
		return (KERN_INVALID_ARGUMENT);
E 18

	vm_object_cache_lock();
	vm_object_lock(object);
D 6
	object->can_persist = should_cache;
E 6
I 6
	if (should_cache)
		object->flags |= OBJ_CANPERSIST;
	else
		object->flags &= ~OBJ_CANPERSIST;
E 6
	vm_object_unlock(object);
	vm_object_cache_unlock();

	vm_object_deallocate(object);

D 18
	return(KERN_SUCCESS);
E 18
I 18
	return (KERN_SUCCESS);
E 18
}
E 1
