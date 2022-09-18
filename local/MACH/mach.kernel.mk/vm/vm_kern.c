/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_kern.c,v $
 * Revision 2.22  90/08/15  12:42:46  mrt
 * 	One more fix for careful_copy_to_physical_page macro case.
 * 	[90/08/15            mrt]
 * 
 * Revision 2.21  90/08/14  16:11:39  mrt
 * 	Removed ns3200 conditionals in careful_copy_to_physical_page
 * 	around the call to careful_bcopy. Now each machine type must
 * 	define a careful_bcopy call, unless it defines a macro for
 * 	careful_copy_to_physical_page like the pmax does to catch
 * 	the problem at a higher level.
 * 	[90/08/14            mrt]
 * 
 * Revision 2.20  90/07/03  16:56:41  mrt
 * 	Purge MACH_XP_FPD.
 * 	[90/06/27            dlb]
 * 	Replace copy_user_to_physical_page with careful_copy_to_physical
 * 	page.  Latter routine can copy from either kernel or user space
 * 	to physical memory and catch unrecoverable page faults.
 * 	[90/06/14            dlb]
 * 
 * Revision 2.19  90/03/27  18:56:29  dlb
 * 	Use vm_submap_object in kmem_suballoc.
 * 	[90/03/27            dlb]
 * 
 * Revision 2.18  89/10/11  14:59:00  dlb
 * 	Changed calling sequence of vm_map_pageable.
 * 	[88/11/23            dlb]
 * 
 * Revision 2.17  89/10/10  13:48:00  mwyoung
 * 	Eliminate XP conditionals.
 * 	[89/10/10            mwyoung]
 * 
 * Revision 2.16  89/10/10  11:11:22  mwyoung
 * 	Remove lint: change type for "data_cnt" to vm_size_t in
 * 	routine copy_user_to_physical_page().
 * 	[89/08/07            mwyoung]
 * 	Eliminate kmem_alloc_wait(), kmem_free_wakeup().  The
 * 	kmem_alloc_pageable() and kmem_free() routines now wait, for
 * 	maps that have been so configured.
 * 	[89/07/30            mwyoung]
 * 	Eliminate vm_move().
 * 	[89/06/18            mwyoung]
 * 
 * Revision 2.15  89/10/03  19:29:40  rpd
 * 	Use vme_next, vme_prev, vme_start, vme_end, vm_map_to_entry.
 * 	[89/08/31  21:11:43  rpd]
 * 
 * 	A change from NeXT:  make kmem_mb_alloc call vm_page_wire on
 * 	the pages it gets, so that the wired count gets bumped.
 * 	However, I think this isn't correct, so I left it #if'd out.
 * 	[89/08/19  23:40:21  rpd]
 * 
 * Revision 2.14  89/04/22  15:35:28  gm0w
 * 	Added code in kmem_mb_alloc to verify that requested allocation
 * 	will fit in the map.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.13  89/04/18  21:25:45  mwyoung
 * 	Recent history:
 * 	 	Add call to vm_map_simplify to reduce kernel map fragmentation.
 * 	History condensation:
 * 		Added routines for copying user data to physical
 * 		 addresses.  [rfr, mwyoung]
 * 		Added routines for sleep/wakeup forms, interrupt-time
 * 		 allocation. [dbg]
 * 		Created.  [avie, mwyoung, dbg]
 * 
 */
/*
 *	File:	vm/vm_kern.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Kernel memory management.
 */

#include <kern/assert.h>
#include <mach/kern_return.h>
#include <sys/types.h>

#include <vm/vm_kern.h>
#include <vm/vm_map.h>
#include <vm/vm_page.h>
#include <vm/vm_pageout.h>
#include <mach/vm_param.h>

/*
 *	Variables exported by this module.
 */

vm_map_t	kernel_map;
vm_map_t	kernel_pageable_map;
vm_map_t	user_pt_map;
vm_map_t	mb_map;

vm_offset_t	vm_kern_zero_page;

/*
 *	kmem_alloc_pageable:
 *
 *	Allocate pageable memory to the kernel's address map.
 *	map must be "kernel_map" below.
 */

vm_offset_t kmem_alloc_pageable(map, size)
	vm_map_t		map;
	register vm_size_t	size;
{
	vm_offset_t		addr;
	register kern_return_t	result;

#if	0
	if (map != kernel_map)
		panic("kmem_alloc_pageable: not called with kernel_map");
#endif	0

	size = round_page(size);

	addr = vm_map_min(map);
	result = vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t) 0,
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
vm_offset_t kmem_alloc(map, size)
	register vm_map_t	map;
	register vm_size_t	size;
{
	vm_offset_t		addr;
	register kern_return_t	result;
	register vm_offset_t	offset;
	extern vm_object_t	kernel_object;
	vm_offset_t		i;

	size = round_page(size);

	/*
	 *	Use the kernel object for wired-down kernel pages.
	 *	Assume that no region of the kernel object is
	 *	referenced more than once.
	 */

	addr = vm_map_min(map);
	result = vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t) 0,
				 &addr, size, TRUE);
	if (result != KERN_SUCCESS) {
		return(0);
	}

	/*
	 *	Since we didn't know where the new region would
	 *	start, we couldn't supply the correct offset into
	 *	the kernel object.  Re-allocate that address
	 *	region with the correct offset.
	 */

	offset = addr - VM_MIN_KERNEL_ADDRESS;
	vm_object_reference(kernel_object);

	vm_map_lock(map);
	(void) vm_map_delete(map, addr, addr + size);
	(void) vm_map_insert(map, kernel_object, offset, addr, addr + size);
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

		while ((mem = vm_page_alloc(kernel_object, offset+i))
			    == VM_PAGE_NULL) {
			vm_object_unlock(kernel_object);
			VM_WAIT;
			vm_object_lock(kernel_object);
		}
		vm_page_zero_fill(mem);
		mem->busy = FALSE;
	}
	vm_object_unlock(kernel_object);
		
	/*
	 *	And finally, mark the data as non-pageable.
	 */

	(void) vm_map_pageable(map, (vm_offset_t) addr, addr + size,
		VM_PROT_READ|VM_PROT_WRITE);

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
void kmem_free(map, addr, size)
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
vm_map_t kmem_suballoc(parent, min, max, size, pageable)
	register vm_map_t	parent;
	vm_offset_t		*min, *max;
	register vm_size_t	size;
	boolean_t		pageable;
{
	register kern_return_t	ret;
	vm_map_t	result;

	size = round_page(size);
	*min = (vm_offset_t) vm_map_min(parent);
	/*
	 *	Need reference on submap object because it is internal
	 *	to the vm_system.  vm_object_enter will never be called
	 *	on it (usual source of reference for vm_map_find).
	 */
	vm_object_reference(vm_submap_object);

	ret = vm_map_find(parent, vm_submap_object, (vm_offset_t) 0,
				min, size, TRUE);
	if (ret != KERN_SUCCESS) {
		printf("kmem_suballoc: bad status return of %d.\n", ret);
		panic("kmem_suballoc");
	}
	*max = *min + size;
	pmap_reference(vm_map_pmap(parent));
	result = vm_map_create(vm_map_pmap(parent), *min, *max, pageable);
	if (result == VM_MAP_NULL)
		panic("kmem_suballoc: cannot create submap");
	if ((ret = vm_map_submap(parent, *min, *max, result)) != KERN_SUCCESS)
		panic("kmem_suballoc: unable to change range to submap");
	return(result);
}

#include <kern/lock.h>
#include <kern/zalloc.h>

#if	!defined(careful_copy_to_physical_page)

lock_data_t	v_to_p_lock_data;
lock_t		v_to_p_lock = &v_to_p_lock_data;
zone_t		v_to_p_zone;
boolean_t	v_to_p_initialized = FALSE;


struct 		v_to_p_entry {
		struct v_to_p_entry * 	next;
		vm_offset_t		v;
} * v_to_p_list;

#define V_TO_P_NULL	((struct v_to_p_entry *)0)

/*
 *	Routine:	careful_copy_to_physical_page
 *
 * 	Purpose:	
 *		Copy a virtual page which may be either kernel or
 *		user and may be currently paged out, to a physical
 *		page.  Must be careful of bogus page (non existant, or
 *		manager returns error on pagein).
 *	
 *	Algorithm:
 *		Allocate a kernel virtual address using kmem_alloc_pageable
 *		and pmap_enter and remove the target page m to that address.
 *		For speed, previous kmem_alloc_pageable results are kept
 *		around in a linked list to allow quick reuse.  
 */
careful_copy_to_physical_page(v, m, data_cnt, is_kernel)
	vm_offset_t		v;
	register vm_page_t	m;
	vm_size_t		data_cnt;
	boolean_t		is_kernel;
{
	register struct v_to_p_entry * 	allocated_entry;
	register vm_offset_t		allocated_addr;
	kern_return_t			r;


	/*
	 * Lock access to virtual address list.
	 */
	lock_write(v_to_p_lock);
	if (!v_to_p_initialized) {
		/*
		 * Create a zone for v_to_p_entries.  Setup list.
		 */		
		v_to_p_zone = zinit(sizeof(struct v_to_p_entry),
				sizeof(struct v_to_p_entry), 
				sizeof(struct v_to_p_entry)*1024,
				FALSE, "v_to_p_zone");
		v_to_p_initialized = TRUE;
		v_to_p_list = V_TO_P_NULL;
	}

	while (v_to_p_list == V_TO_P_NULL) {
		/*
		 * Allocate a new entry from zone.
		 */
		v_to_p_list = (struct v_to_p_entry *)zalloc(v_to_p_zone);
		if (v_to_p_list == V_TO_P_NULL) {
			/*
			 * Give someone a chance to return entry to pool.
			 */
			lock_write_done(v_to_p_lock);
			thread_block();
			lock_write(v_to_p_lock);
			continue;
		}
		v_to_p_list->next = V_TO_P_NULL;
		v_to_p_list->v = kmem_alloc_pageable(kernel_map, PAGE_SIZE);
	}

	allocated_entry = v_to_p_list;
	v_to_p_list = v_to_p_list->next;
	lock_write_done(v_to_p_lock);

	allocated_addr = allocated_entry->v;
	pmap_enter(kernel_pmap, allocated_addr, VM_PAGE_TO_PHYS(m),
				VM_PROT_READ|VM_PROT_WRITE, TRUE);

	if (is_kernel)
		r = careful_bcopy((caddr_t) v, (caddr_t) allocated_addr,
			(unsigned int) data_cnt);
	else
		r = copyin((caddr_t) v, (caddr_t) allocated_addr,
			(unsigned int) data_cnt);
			
	pmap_remove(kernel_pmap, allocated_addr, allocated_addr+PAGE_SIZE);

	lock_write(v_to_p_lock);
	allocated_entry->next = v_to_p_list;
	v_to_p_list = allocated_entry;
	lock_done(v_to_p_lock);

	if (r != 0)
		return(KERN_FAILURE);

	return(KERN_SUCCESS);	
}

#endif	!defined(careful_copy_to_physical_page)

/*
 *	Special hack for allocation in mb_map.  Can never wait for pages
 *	(or anything else) in mb_map.
 */
vm_offset_t kmem_mb_alloc(map, size)
	register vm_map_t	map;
	vm_size_t		size;
{
	vm_object_t		object;
	register vm_map_entry_t	entry;
	vm_offset_t		addr;
	register int		npgs;
	register vm_page_t	m;
	register vm_offset_t	vaddr, offset, cur_off;

	/*
	 *	Only do this on the mb_map.
	 */
	if (map != mb_map)
		panic("You fool!");

	size = round_page(size);

	vm_map_lock(map);
	entry = map->vme_next;
	if (entry == vm_map_to_entry(map)) {
		/*
		 *	Map is empty.  Do things normally the first time...
		 *	this will allocate the entry and the object to use.
		 */
		vm_map_unlock(map);
		addr = vm_map_min(map);
		if (vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t) 0,
			&addr, size, TRUE) != KERN_SUCCESS)
			return (0);
		(void) vm_map_pageable(map, addr, addr + size,
			VM_PROT_READ|VM_PROT_WRITE);
		return(addr);
	}
	/*
	 *	Map already has an entry.  We must be extending it.
	 */
	if (!(entry == map->vme_prev &&
	      entry->is_a_map == FALSE &&
	      entry->vme_start == vm_map_min(map) &&
	      entry->max_protection == VM_PROT_DEFAULT &&
	      entry->protection == VM_PROT_DEFAULT &&
	      entry->inheritance == VM_INHERIT_DEFAULT &&
	      entry->wired_count != 0)) {
		/*
		 *	Someone's not playing by the rules...
		 */
		panic("mb_map abused even more than usual");
	}

	/*
	 *      Verify that the requested allocation will
	 *      fit in the map
	 */
	if ((entry->vme_end + size) > vm_map_max(map)) {
		panic("kmem_mb_alloc: Not extending, size+end > max[map]\n");
		vm_map_unlock(map);
		return(0);
	}

	/*
	 *	extend the entry
	 */
	object = entry->object.vm_object;
	offset = (entry->vme_end - entry->vme_start) + entry->offset;
	addr   = entry->vme_end;
	entry->vme_end += size;

	/*
	 *	Since we may not have enough memory, and we may not
	 *	block, we first allocate all the memory up front, pulling
	 *	it off the active queue to prevent pageout.  We then can
	 *	either enter the pages, or free whatever we tried to get.
	 */

	vm_object_lock(object);
	cur_off = offset;
	npgs = atop(size);
	while (npgs) {
		m = vm_page_alloc(object, cur_off);
		if (m == VM_PAGE_NULL) {
			/*
			 *	Not enough pages, and we can't
			 *	wait, so free everything up.
			 */
			while (cur_off > offset) {
				cur_off -= PAGE_SIZE;
				m = vm_page_lookup(object, cur_off);
				/*
				 *	Don't have to lock the queues here
				 *	because we know that the pages are
				 *	not on any queues.
				 */
				vm_page_free(m);
			}
			vm_object_unlock(object);

			/*
			 *	Shrink the map entry back to its old size.
			 */
			entry->vme_end -= size;
			vm_map_unlock(map);
			return(0);
		}

		/*
		 *	We want zero-filled memory
		 */

		vm_page_zero_fill(m);

		/*
		 *	Since no other process can see these pages, we don't
		 *	have to bother with the busy bit.
		 */

		m->busy = FALSE;

		npgs--;
		cur_off += PAGE_SIZE;
	}

	vm_object_unlock(object);

	/*
	 *	Map entry is already marked non-pageable.
	 *	Loop thru pages, entering them in the pmap.
	 *	(We can't add them to the wired count without
	 *	wrapping the vm_page_queue_lock in splimp...)
	 */
	vaddr = addr;
	cur_off = offset;
	while (vaddr < entry->vme_end) {
		vm_object_lock(object);
		m = vm_page_lookup(object, cur_off);
#if	0
		vm_page_wire(m);
#endif
		vm_object_unlock(object);
		pmap_enter(map->pmap, vaddr, VM_PAGE_TO_PHYS(m),
			entry->protection, TRUE);
		vaddr += PAGE_SIZE;
		cur_off += PAGE_SIZE;
	}
	vm_map_unlock(map);

	return(addr);
}

/*
 *	kmem_init:
 *
 *	Initialize the kernel's virtual memory map, taking
 *	into account all memory allocated up to this time.
 */
void kmem_init(start, end)
	vm_offset_t	start;
	vm_offset_t	end;
{
	vm_offset_t	addr;
	extern vm_map_t	kernel_map;

	kernel_map = vm_map_create(pmap_kernel(), VM_MIN_KERNEL_ADDRESS, end,
				FALSE);

	addr = VM_MIN_KERNEL_ADDRESS;
	(void) vm_map_find(kernel_map, VM_OBJECT_NULL, (vm_offset_t) 0,
				&addr, (start - VM_MIN_KERNEL_ADDRESS),
				FALSE);


	vm_kern_zero_page = kmem_alloc(kernel_map, PAGE_SIZE);

#if	!defined(careful_copy_to_physical_page)
	v_to_p_initialized = FALSE;
	lock_init(v_to_p_lock, TRUE);
#endif	!defined(careful_copy_to_physical_page)
}
