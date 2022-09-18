h15449
s 00016/00010/00414
d D 8.4 95/01/09 17:50:19 cgd 15 14
c KNF, and 64-bit safety.
e
s 00000/00076/00424
d D 8.3 94/01/12 15:44:18 hibler 14 13
c get rid of vm_move.
e
s 00000/00002/00500
d D 8.2 94/01/04 22:22:31 bostic 13 12
c lint
e
s 00002/00002/00500
d D 8.1 93/06/11 16:37:39 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00501
d D 7.11 93/05/24 23:40:32 torek 11 10
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00002/00002/00500
d D 7.10 92/10/01 17:54:19 mckusick 10 9
c convert vm_page bit fields to flags
e
s 00006/00005/00496
d D 7.9 92/05/04 17:06:03 bostic 9 8
c new include format
e
s 00001/00001/00500
d D 7.8 92/02/19 22:31:05 torek 8 7
c vm_map_findspace returns 0 on success, not failure
e
s 00001/00001/00500
d D 7.7 92/02/19 19:00:36 mckusick 7 6
c cleanup the buggies
e
s 00048/00068/00453
d D 7.6 92/02/19 18:46:07 torek 6 5
c split vm_map_findspace out of vm_map_find
e
s 00001/00001/00520
d D 7.5 92/02/19 18:35:58 torek 5 4
c eliminate pmap_kernel()
e
s 00004/00001/00517
d D 7.4 91/05/07 09:30:54 hibler 4 3
c panic if map allocation fails and canwait has been specified
c (hokey, we should really wait like we are supposed to)
e
s 00027/00004/00491
d D 7.3 91/04/21 18:36:10 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00015/00017/00480
d D 7.2 91/04/20 10:50:08 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00497/00000/00000
d D 7.1 90/12/05 18:07:56 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 * Copyright (c) 1987 Carnegie-Mellon University
E 3
D 12
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
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
 *	Kernel memory management.
 */

D 2
#include "types.h"
E 2
I 2
D 9
#include "param.h"
E 9
I 9
#include <sys/param.h>
#include <sys/systm.h>
E 9
E 2

D 2
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_page.h"
#include "../vm/vm_pageout.h"
#include "../vm/vm_kern.h"
E 2
I 2
D 9
#include "vm.h"
#include "vm_page.h"
#include "vm_pageout.h"
#include "vm_kern.h"
E 9
I 9
#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_pageout.h>
#include <vm/vm_kern.h>
E 9
E 2

/*
 *	kmem_alloc_pageable:
 *
 *	Allocate pageable memory to the kernel's address map.
 *	map must be "kernel_map" below.
 */
D 15

vm_offset_t kmem_alloc_pageable(map, size)
E 15
I 15
vm_offset_t
kmem_alloc_pageable(map, size)
E 15
	vm_map_t		map;
	register vm_size_t	size;
{
	vm_offset_t		addr;
	register int		result;

#if	0
	if (map != kernel_map)
		panic("kmem_alloc_pageable: not called with kernel_map");
D 11
#endif	0
E 11
I 11
#endif
E 11

	size = round_page(size);

	addr = vm_map_min(map);
D 2
	result = vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t) 0,
E 2
I 2
	result = vm_map_find(map, NULL, (vm_offset_t) 0,
E 2
				&addr, size, TRUE);
	if (result != KERN_SUCCESS) {
		return(0);
	}

	return(addr);
}

/*
 *	Allocate wired-down memory in the kernel's address map
 *	or a submap.
 */
D 15
vm_offset_t kmem_alloc(map, size)
E 15
I 15
vm_offset_t
kmem_alloc(map, size)
E 15
	register vm_map_t	map;
	register vm_size_t	size;
{
	vm_offset_t		addr;
D 13
	register int		result;
E 13
	register vm_offset_t	offset;
	extern vm_object_t	kernel_object;
	vm_offset_t		i;

	size = round_page(size);

	/*
	 *	Use the kernel object for wired-down kernel pages.
	 *	Assume that no region of the kernel object is
	 *	referenced more than once.
	 */

D 6
	addr = vm_map_min(map);
D 2
	result = vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t) 0,
E 2
I 2
	result = vm_map_find(map, NULL, (vm_offset_t) 0,
E 2
				 &addr, size, TRUE);
	if (result != KERN_SUCCESS) {
		return(0);
	}

E 6
	/*
D 6
	 *	Since we didn't know where the new region would
	 *	start, we couldn't supply the correct offset into
	 *	the kernel object.  Re-allocate that address
	 *	region with the correct offset.
E 6
I 6
	 * Locate sufficient space in the map.  This will give us the
	 * final virtual address for the new memory, and thus will tell
	 * us the offset within the kernel map.
E 6
	 */
D 6

E 6
I 6
	vm_map_lock(map);
	if (vm_map_findspace(map, 0, size, &addr)) {
		vm_map_unlock(map);
		return (0);
	}
E 6
	offset = addr - VM_MIN_KERNEL_ADDRESS;
	vm_object_reference(kernel_object);
D 6

	vm_map_lock(map);
	vm_map_delete(map, addr, addr + size);
E 6
	vm_map_insert(map, kernel_object, offset, addr, addr + size);
	vm_map_unlock(map);

	/*
	 *	Guarantee that there are pages already in this object
	 *	before calling vm_map_pageable.  This is to prevent the
	 *	following scenario:
	 *
	 *		1) Threads have swapped out, so that there is a
	 *		   pager for the kernel_object.
	 *		2) The kmsg zone is empty, and so we are kmem_allocing
	 *		   a new page for it.
	 *		3) vm_map_pageable calls vm_fault; there is no page,
	 *		   but there is a pager, so we call
	 *		   pager_data_request.  But the kmsg zone is empty,
	 *		   so we must kmem_alloc.
	 *		4) goto 1
	 *		5) Even if the kmsg zone is not empty: when we get
	 *		   the data back from the pager, it will be (very
	 *		   stale) non-zero data.  kmem_alloc is defined to
	 *		   return zero-filled memory.
	 *
	 *	We're intentionally not activating the pages we allocate
	 *	to prevent a race with page-out.  vm_map_pageable will wire
	 *	the pages.
	 */

	vm_object_lock(kernel_object);
	for (i = 0 ; i < size; i+= PAGE_SIZE) {
		vm_page_t	mem;

D 2
		while ((mem = vm_page_alloc(kernel_object, offset+i))
			    == VM_PAGE_NULL) {
E 2
I 2
		while ((mem = vm_page_alloc(kernel_object, offset+i)) == NULL) {
E 2
			vm_object_unlock(kernel_object);
			VM_WAIT;
			vm_object_lock(kernel_object);
		}
		vm_page_zero_fill(mem);
D 10
		mem->busy = FALSE;
E 10
I 10
		mem->flags &= ~PG_BUSY;
E 10
	}
	vm_object_unlock(kernel_object);
		
	/*
	 *	And finally, mark the data as non-pageable.
	 */

	(void) vm_map_pageable(map, (vm_offset_t) addr, addr + size, FALSE);

	/*
	 *	Try to coalesce the map
	 */

	vm_map_simplify(map, addr);

	return(addr);
}

/*
 *	kmem_free:
 *
 *	Release a region of kernel virtual memory allocated
 *	with kmem_alloc, and return the physical pages
 *	associated with that region.
 */
D 15
void kmem_free(map, addr, size)
E 15
I 15
void
kmem_free(map, addr, size)
E 15
	vm_map_t		map;
	register vm_offset_t	addr;
	vm_size_t		size;
{
	(void) vm_map_remove(map, trunc_page(addr), round_page(addr + size));
}

/*
 *	kmem_suballoc:
 *
 *	Allocates a map to manage a subrange
 *	of the kernel virtual address space.
 *
 *	Arguments are as follows:
 *
 *	parent		Map to take range from
 *	size		Size of range to find
 *	min, max	Returned endpoints of map
 *	pageable	Can the region be paged
 */
D 15
vm_map_t kmem_suballoc(parent, min, max, size, pageable)
E 15
I 15
vm_map_t
kmem_suballoc(parent, min, max, size, pageable)
E 15
	register vm_map_t	parent;
	vm_offset_t		*min, *max;
	register vm_size_t	size;
	boolean_t		pageable;
{
	register int	ret;
	vm_map_t	result;

	size = round_page(size);

	*min = (vm_offset_t) vm_map_min(parent);
D 2
	ret = vm_map_find(parent, VM_OBJECT_NULL, (vm_offset_t) 0,
E 2
I 2
	ret = vm_map_find(parent, NULL, (vm_offset_t) 0,
E 2
				min, size, TRUE);
	if (ret != KERN_SUCCESS) {
		printf("kmem_suballoc: bad status return of %d.\n", ret);
		panic("kmem_suballoc");
	}
	*max = *min + size;
	pmap_reference(vm_map_pmap(parent));
	result = vm_map_create(vm_map_pmap(parent), *min, *max, pageable);
D 2
	if (result == VM_MAP_NULL)
E 2
I 2
	if (result == NULL)
E 2
		panic("kmem_suballoc: cannot create submap");
	if ((ret = vm_map_submap(parent, *min, *max, result)) != KERN_SUCCESS)
		panic("kmem_suballoc: unable to change range to submap");
	return(result);
}

/*
D 14
 *	vm_move:
 *
 *	Move memory from source to destination map, possibly deallocating
 *	the source map reference to the memory.
 *
 *	Parameters are as follows:
 *
 *	src_map		Source address map
 *	src_addr	Address within source map
 *	dst_map		Destination address map
 *	num_bytes	Amount of data (in bytes) to copy/move
 *	src_dealloc	Should source be removed after copy?
 *
 *	Assumes the src and dst maps are not already locked.
 *
 *	Returns new destination address or 0 (if a failure occurs).
 */
vm_offset_t vm_move(src_map,src_addr,dst_map,num_bytes,src_dealloc)
	vm_map_t		src_map;
	register vm_offset_t	src_addr;
	register vm_map_t	dst_map;
	vm_offset_t		num_bytes;
	boolean_t		src_dealloc;
{
	register vm_offset_t	src_start;	/* Beginning of region */
	register vm_size_t	src_size;	/* Size of rounded region */
	vm_offset_t		dst_start;	/* destination address */
	register int		result;

	/*
	 *	Page-align the source region
	 */

	src_start = trunc_page(src_addr);
	src_size = round_page(src_addr + num_bytes) - src_start;

	/*
	 *	If there's no destination, we can be at most deallocating
	 *	the source range.
	 */
D 2
	if (dst_map == VM_MAP_NULL) {
E 2
I 2
	if (dst_map == NULL) {
E 2
		if (src_dealloc)
			if (vm_deallocate(src_map, src_start, src_size)
					!= KERN_SUCCESS) {
				printf("vm_move: deallocate of source");
				printf(" failed, dealloc_only clause\n");
			}
		return(0);
	}

	/*
	 *	Allocate a place to put the copy
	 */

	dst_start = (vm_offset_t) 0;
	if ((result = vm_allocate(dst_map, &dst_start, src_size, TRUE))
				== KERN_SUCCESS) {
		/*
		 *	Perform the copy, asking for deallocation if desired
		 */
		result = vm_map_copy(dst_map, src_map, dst_start, src_size,
					src_start, FALSE, src_dealloc);
	}

	/*
	 *	Return the destination address corresponding to
	 *	the source address given (rather than the front
	 *	of the newly-allocated page).
	 */

	if (result == KERN_SUCCESS)
		return(dst_start + (src_addr - src_start));
	return(0);
}

/*
E 14
 * Allocate wired-down memory in the kernel's address map for the higher
 * level kernel memory allocator (kern/kern_malloc.c).  We cannot use
 * kmem_alloc() because we may need to allocate memory at interrupt
 * level where we cannot block (canwait == FALSE).
 *
 * This routine has its own private kernel submap (kmem_map) and object
 * (kmem_object).  This, combined with the fact that only malloc uses
 * this routine, ensures that we will never block in map or object waits.
 *
 * Note that this still only works in a uni-processor environment and
 * when called at splhigh().
 *
 * We don't worry about expanding the map (adding entries) since entries
 * for wired maps are statically allocated.
 */
vm_offset_t
kmem_malloc(map, size, canwait)
	register vm_map_t	map;
	register vm_size_t	size;
	boolean_t		canwait;
{
	register vm_offset_t	offset, i;
	vm_map_entry_t		entry;
	vm_offset_t		addr;
	vm_page_t		m;
	extern vm_object_t	kmem_object;

	if (map != kmem_map && map != mb_map)
		panic("kern_malloc_alloc: map != {kmem,mb}_map");

	size = round_page(size);
	addr = vm_map_min(map);

D 2
	if (vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t)0,
E 2
I 2
D 6
	if (vm_map_find(map, NULL, (vm_offset_t)0,
E 2
D 4
			&addr, size, TRUE) != KERN_SUCCESS)
E 4
I 4
			&addr, size, TRUE) != KERN_SUCCESS) {
		if (canwait)
			panic("kmem_malloc: kmem_map too small");
E 4
		return(0);
I 4
	}
E 4

E 6
	/*
D 6
	 * Since we didn't know where the new region would start,
	 * we couldn't supply the correct offset into the kmem object.
	 * Re-allocate that address region with the correct offset.
E 6
I 6
	 * Locate sufficient space in the map.  This will give us the
	 * final virtual address for the new memory, and thus will tell
	 * us the offset within the kernel map.
E 6
	 */
I 6
	vm_map_lock(map);
	if (vm_map_findspace(map, 0, size, &addr)) {
		vm_map_unlock(map);
		if (canwait)		/* XXX  should wait */
			panic("kmem_malloc: %s too small",
			    map == kmem_map ? "kmem_map" : "mb_map");
		return (0);
	}
E 6
	offset = addr - vm_map_min(kmem_map);
	vm_object_reference(kmem_object);
D 6

	vm_map_lock(map);
	vm_map_delete(map, addr, addr + size);
E 6
	vm_map_insert(map, kmem_object, offset, addr, addr + size);

	/*
	 * If we can wait, just mark the range as wired
	 * (will fault pages as necessary).
	 */
	if (canwait) {
		vm_map_unlock(map);
		(void) vm_map_pageable(map, (vm_offset_t) addr, addr + size,
				       FALSE);
		vm_map_simplify(map, addr);
		return(addr);
	}

	/*
	 * If we cannot wait then we must allocate all memory up front,
	 * pulling it off the active queue to prevent pageout.
	 */
	vm_object_lock(kmem_object);
	for (i = 0; i < size; i += PAGE_SIZE) {
		m = vm_page_alloc(kmem_object, offset + i);

		/*
		 * Ran out of space, free everything up and return.
		 * Don't need to lock page queues here as we know
		 * that the pages we got aren't on any queues.
		 */
D 2
		if (m == VM_PAGE_NULL) {
E 2
I 2
		if (m == NULL) {
E 2
			while (i != 0) {
				i -= PAGE_SIZE;
				m = vm_page_lookup(kmem_object, offset + i);
				vm_page_free(m);
			}
			vm_object_unlock(kmem_object);
			vm_map_delete(map, addr, addr + size);
			vm_map_unlock(map);
			return(0);
		}
#if 0
		vm_page_zero_fill(m);
#endif
D 10
		m->busy = FALSE;
E 10
I 10
		m->flags &= ~PG_BUSY;
E 10
	}
	vm_object_unlock(kmem_object);

	/*
	 * Mark map entry as non-pageable.
	 * Assert: vm_map_insert() will never be able to extend the previous
	 * entry so there will be a new entry exactly corresponding to this
	 * address range and it will have wired_count == 0.
	 */
	if (!vm_map_lookup_entry(map, addr, &entry) ||
	    entry->start != addr || entry->end != addr + size ||
	    entry->wired_count)
		panic("kmem_malloc: entry not found or misaligned");
	entry->wired_count++;

	/*
	 * Loop thru pages, entering them in the pmap.
	 * (We cannot add them to the wired count without
	 * wrapping the vm_page_queue_lock in splimp...)
	 */
	for (i = 0; i < size; i += PAGE_SIZE) {
		vm_object_lock(kmem_object);
		m = vm_page_lookup(kmem_object, offset + i);
		vm_object_unlock(kmem_object);
		pmap_enter(map->pmap, addr + i, VM_PAGE_TO_PHYS(m),
			   VM_PROT_DEFAULT, TRUE);
	}
	vm_map_unlock(map);

	vm_map_simplify(map, addr);
	return(addr);
}

/*
 *	kmem_alloc_wait
 *
 *	Allocates pageable memory from a sub-map of the kernel.  If the submap
 *	has no room, the caller sleeps waiting for more memory in the submap.
 *
 */
D 15
vm_offset_t kmem_alloc_wait(map, size)
E 15
I 15
vm_offset_t
kmem_alloc_wait(map, size)
E 15
	vm_map_t	map;
	vm_size_t	size;
{
	vm_offset_t	addr;
D 13
	int		result;
E 13

	size = round_page(size);

D 6
	do {
E 6
I 6
	for (;;) {
E 6
		/*
D 6
		 *	To make this work for more than one map,
		 *	use the map's lock to lock out sleepers/wakers.
		 *	Unfortunately, vm_map_find also grabs the map lock.
E 6
I 6
		 * To make this work for more than one map,
		 * use the map's lock to lock out sleepers/wakers.
E 6
		 */
		vm_map_lock(map);
D 6
		lock_set_recursive(&map->lock);

		addr = vm_map_min(map);
D 2
		result = vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t) 0,
E 2
I 2
		result = vm_map_find(map, NULL, (vm_offset_t) 0,
E 2
				&addr, size, TRUE);

		lock_clear_recursive(&map->lock);
		if (result != KERN_SUCCESS) {

			if ( (vm_map_max(map) - vm_map_min(map)) < size ) {
				vm_map_unlock(map);
				return(0);
			}

			assert_wait((int)map, TRUE);
E 6
I 6
D 8
		if (vm_map_findspace(map, 0, size, &addr))
E 8
I 8
		if (vm_map_findspace(map, 0, size, &addr) == 0)
E 8
			break;
		/* no space now; see if we can ever get space */
		if (vm_map_max(map) - vm_map_min(map) < size) {
E 6
			vm_map_unlock(map);
D 6
			thread_block();
E 6
I 6
			return (0);
E 6
		}
D 6
		else {
			vm_map_unlock(map);
		}

	} while (result != KERN_SUCCESS);

	return(addr);
E 6
I 6
D 15
		assert_wait((int)map, TRUE);
E 15
I 15
		assert_wait(map, TRUE);
E 15
		vm_map_unlock(map);
		thread_block();
	}
	vm_map_insert(map, NULL, (vm_offset_t)0, addr, addr + size);
	vm_map_unlock(map);
	return (addr);
E 6
}

/*
 *	kmem_free_wakeup
 *
 *	Returns memory to a submap of the kernel, and wakes up any threads
 *	waiting for memory in that map.
 */
D 15
void	kmem_free_wakeup(map, addr, size)
E 15
I 15
void
kmem_free_wakeup(map, addr, size)
E 15
	vm_map_t	map;
	vm_offset_t	addr;
	vm_size_t	size;
{
	vm_map_lock(map);
	(void) vm_map_delete(map, trunc_page(addr), round_page(addr + size));
D 15
	thread_wakeup((int)map);
E 15
I 15
	thread_wakeup(map);
E 15
	vm_map_unlock(map);
}

/*
D 6
 *	kmem_init:
 *
 *	Initialize the kernel's virtual memory map, taking
 *	into account all memory allocated up to this time.
E 6
I 6
 * Create the kernel map; insert a mapping covering kernel text, data, bss,
 * and all space allocated thus far (`boostrap' data).  The new map will thus
 * map the range between VM_MIN_KERNEL_ADDRESS and `start' as allocated, and
 * the range between `start' and `end' as free.
E 6
 */
D 15
void kmem_init(start, end)
E 15
I 15
void
kmem_init(start, end)
E 15
D 6
	vm_offset_t	start;
	vm_offset_t	end;
E 6
I 6
	vm_offset_t start, end;
E 6
{
D 6
	vm_offset_t	addr;
	extern vm_map_t	kernel_map;
E 6
I 6
	register vm_map_t m;
E 6

D 6
	addr = VM_MIN_KERNEL_ADDRESS;
D 5
	kernel_map = vm_map_create(pmap_kernel(), addr, end, FALSE);
E 5
I 5
	kernel_map = vm_map_create(kernel_pmap, addr, end, FALSE);
E 5
D 2
	(void) vm_map_find(kernel_map, VM_OBJECT_NULL, (vm_offset_t) 0,
E 2
I 2
	(void) vm_map_find(kernel_map, NULL, (vm_offset_t) 0,
E 2
				&addr, (start - VM_MIN_KERNEL_ADDRESS),
				FALSE);
E 6
I 6
D 7
	m = vm_map_create(kernel_pmap, addr, end, FALSE);
E 7
I 7
	m = vm_map_create(kernel_pmap, VM_MIN_KERNEL_ADDRESS, end, FALSE);
E 7
	vm_map_lock(m);
	/* N.B.: cannot use kgdb to debug, starting with this assignment ... */
	kernel_map = m;
	(void) vm_map_insert(m, NULL, (vm_offset_t)0,
	    VM_MIN_KERNEL_ADDRESS, start);
	/* ... and ending with the completion of the above `insert' */
	vm_map_unlock(m);
E 6
}
E 1
