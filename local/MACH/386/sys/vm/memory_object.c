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
 * $Log:	memory_object.c,v $
 * Revision 2.18  89/04/23  13:25:30  gm0w
 * 	Fixed typo to pmap_page_protect in memory_object_lock_request().
 * 	[89/04/23            gm0w]
 * 
 * Revision 2.17  89/04/22  15:35:09  gm0w
 * 	Commented out check/uprintf if memory_object_data_unavailable
 * 	was called on a permanent object.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.16  89/04/18  21:24:24  mwyoung
 * 	Recent history:
 * 	 	Add vm_set_default_memory_manager(),
 * 		 memory_object_get_attributes().
 * 		Whenever asked to clean a page, use pmap_is_modified, even
 * 		 if not flushing the data.
 * 		Handle fictitious pages when accepting data (or error or
 * 		 unavailable).
 * 		Avoid waiting in memory_object_data_error().
 * 
 * 	Previous history has been integrated into the documentation below.
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm/memory_object.c
 *	Author:	Michael Wayne Young
 *
 *	External memory management interface control functions.
 */
#include <mach_xp_fpd.h>

/*
 *	Interface dependencies:
 */

#include <mach/std_types.h>	/* For pointer_t */
#include <mach/mach_types.h>

#include <mach/kern_return.h>
#include <vm/vm_object.h>
#include <mach/memory_object.h>
#include <mach/memory_object_user.h>
#include <mach/boolean.h>
#include <mach/vm_prot.h>

/*
 *	Implementation dependencies:
 */
#include <vm/vm_page.h>
#include <vm/vm_pageout.h>
#include <vm/pmap.h>		/* For copy_to_phys, pmap_clear_modify */
#include <kern/thread.h>		/* For current_thread() */

#if	!MACH_XP_FPD
#include <vm/vm_kern.h>		/* For kernel_map, vm_move */
#include <vm/vm_map.h>		/* For vm_map_pageable */
#include <kern/ipc_globals.h>
#endif	!MACH_XP_FPD

#include <kern/xpr.h>

int		memory_object_debug = 0;

/*
 */

memory_object_t	memory_manager_default = PORT_NULL;
decl_simple_lock_data(,memory_manager_default_lock)


/*
 *	Important note:
 *		All of these routines gain a reference to the
 *		object (first argument) as part of the automatic
 *		argument conversion. Explicit deallocation is necessary.
 */

kern_return_t memory_object_data_provided(object, offset, data, data_cnt, lock_value)
	vm_object_t	object;
	vm_offset_t	offset;
	pointer_t	data;
	unsigned int	data_cnt;
	vm_prot_t	lock_value;
{
	kern_return_t	result = KERN_FAILURE;
	vm_page_t	m;
#if	!MACH_XP_FPD
	pointer_t	original_data = data;
	unsigned int	original_data_cnt = data_cnt;
#endif	!MACH_XP_FPD
	pointer_t	kernel_data = data;

	XPR(XPR_MEMORY_OBJECT, ("memory_object_data_provided, object 0x%x, offset 0x%x",
				object, offset, 0, 0));

	/*
	 *	Look for bogus arguments
	 */

	if (object == VM_OBJECT_NULL)
		return(KERN_INVALID_ARGUMENT);

	if (lock_value & ~VM_PROT_ALL) {
		vm_object_deallocate(object);
		return(KERN_INVALID_ARGUMENT);
	}

	/*
	 *	Adjust the offset from the memory object to the offset
	 *	within the vm_object.  Only accept whole pages.
	 */

	vm_object_lock(object);
	offset -= object->paging_offset;
	vm_object_unlock(object);

	/*
	 *	Accept data one page at a time
	 */

	for (;
	     data_cnt >= PAGE_SIZE;
	     data_cnt -= PAGE_SIZE, data += PAGE_SIZE, offset += PAGE_SIZE) {
		/*
		 *	Move in user's data, and wire it down
		 */
#if	MACH_XP_FPD
		kernel_data = data;
#else	MACH_XP_FPD
		if (vm_move(ipc_soft_map, (vm_offset_t) data, ipc_kernel_map,
			    PAGE_SIZE, FALSE, &kernel_data) != KERN_SUCCESS)
			panic("memory_object_data_provided: cannot move data");

		vm_map_pageable(
			ipc_kernel_map,
			trunc_page((vm_offset_t) kernel_data),
			round_page(((vm_offset_t) kernel_data + PAGE_SIZE)),
			FALSE);
#endif	MACH_XP_FPD

		/*
		 *	Find the page waiting for our data.  If there's no
		 *	page, see whether we can allocate one, but don't bother
		 *	waiting.
		 */

		vm_object_lock(object);
		if ((memory_object_debug & 0x2) && (object->ref_count <= 1))
			printf("memory_object_data_provided: supplying data to a dead object");

		if ((m = vm_page_lookup(object, offset)) == VM_PAGE_NULL) {
			if (memory_object_debug & 0x4) {
				printf("memory_object_data_provided: object providing spurious data");
				printf("; object = 0x%x, offset = 0x%x\n", object, offset);
			}
			if ((m = vm_page_alloc(object, offset)) != VM_PAGE_NULL) {
				m->busy = m->absent = TRUE;
				object->absent_count++;
			} else
				result = KERN_RESOURCE_SHORTAGE;
		}

		/*
		 *	Only overwrite pages that are "absent".
		 *	Maybe someday we'll allow memory managers
		 *	to overwrite live data,	but not yet.
		 */

		if ((m != VM_PAGE_NULL) && m->busy && m->absent) {
#if	1
			/*
			 * [Currently, absent pages aren't placed on
			 * the pageout queues.]
			 */
			assert(!m->active && !m->inactive);
#else	1
			/*
			 *	Remove the page from the paging queues.
			 */

			vm_page_lock_queues();
			VM_PAGE_QUEUES_REMOVE(m);
			vm_page_unlock_queues();
#endif	1

			/*
			 *	If the requestor aborted its page fault,
			 *	then we merely throw this page away.
			 */

			if (m->fictitious) {
				VM_PAGE_FREE(m);
				vm_object_unlock(object);
				continue;
			}

			/*
			 *	Turn off the absent indication, but leave
			 *	the page busy, so we're the only thread
			 *	that can use it.  [The page was already busy,
			 *	so we don't have to take a paging reference
			 *	for ourselves.]
			 */

			m->absent = FALSE;
			vm_object_absent_release(object);

			/*
			 *	Copy in the data.  Since we're holding the
			 *	page busy, we can unlock the object.
			 *	[If MACH_XP_FPD, this is essential, because
			 *	the copy may fault on the user's memory.]
			 */

			vm_object_unlock(object);

#if	MACH_XP_FPD
			if (vm_map_pmap(current_task()->map) != kernel_pmap)
				copy_user_to_physical_page(data, m, data_cnt);
			 else
#endif	MACH_XP_FPD
			copy_to_phys((vm_offset_t) kernel_data, m->phys_addr, data_cnt);

			/*
			 *	Pick the object lock back up, and set the
			 *	page parameters.
			 */

			vm_object_lock(object);
			pmap_clear_modify(m->phys_addr);
			m->page_lock = lock_value;
			m->unlock_request = VM_PROT_NONE;

			/*
			 *	Clear the busy indication, and perform wakeups.
			 */

			PAGE_WAKEUP(m);
			result = KERN_SUCCESS;

			/*
			 *	Reactivate the page
			 */

			vm_page_lock_queues();
			if (!m->active)
				vm_page_activate(m);
			vm_page_unlock_queues();
		}

		vm_object_unlock(object);
	
#if	!MACH_XP_FPD
		vm_deallocate(ipc_kernel_map, kernel_data, PAGE_SIZE);
#endif	!MACH_XP_FPD
	}

#if	!MACH_XP_FPD
	if (original_data_cnt != 0)
		vm_deallocate(ipc_soft_map, original_data, original_data_cnt);
#endif	!MACH_XP_FPD

	if (data_cnt != 0)
		uprintf("memory_object_data_provided: partial page discarded\n");

	vm_object_deallocate(object);
	return(result);
}

kern_return_t pager_data_provided_inline(object, offset, data, lock_value)
	vm_object_t	object;
	vm_offset_t	offset;
	vm_page_data_t	data;
	vm_prot_t	lock_value;
{
#ifdef	lint
	offset++; data[0]++; lock_value++;
#endif	lint

	uprintf("pager_data_provided_inline: no longer supported -- use");
	uprintf(" memory_object_data_provided instead... trust us\n");
	
	vm_object_deallocate(object);
	return(KERN_FAILURE);
}

kern_return_t memory_object_data_error(object, offset, size, error_value)
	vm_object_t	object;
	vm_offset_t	offset;
	vm_size_t	size;
	kern_return_t	error_value;
{
	if (object == VM_OBJECT_NULL)
		return(KERN_INVALID_ARGUMENT);

	if (size != round_page(size))
		return(KERN_INVALID_ARGUMENT);

#if	defined(hc) || defined(lint)
	/* Error value is ignored at this time */
	error_value++;
#endif	defined(hc) || defined(lint)

	vm_object_lock(object);
	offset -= object->paging_offset;

	while (size != 0) {
		register vm_page_t m;

		if (((m = vm_page_lookup(object, offset)) != VM_PAGE_NULL)) {
			if (m->absent) {
				if (m->fictitious) {
					VM_PAGE_FREE(m);
				} else {
					m->busy = FALSE;
					m->absent = FALSE;
					m->error = TRUE;
					vm_object_absent_release(object);
					PAGE_WAKEUP(m);
				}
			}
		}
		size -= PAGE_SIZE;
		offset += PAGE_SIZE;
	 }
	vm_object_unlock(object);

	vm_object_deallocate(object);
	return(KERN_SUCCESS);
}

kern_return_t memory_object_data_unavailable(object, offset, size)
	vm_object_t	object;
	vm_offset_t	offset;
	vm_size_t	size;
{
	XPR(XPR_MEMORY_OBJECT, ("memory_object_data_unavailable, object 0x%x, offset 0x%x",
				object, offset, 0, 0));

	if (object == VM_OBJECT_NULL)
		return(KERN_INVALID_ARGUMENT);

	if (size != round_page(size))
		return(KERN_INVALID_ARGUMENT);

/*
	if (!object->temporary) {
		uprintf("memory_object_data_unavailable: called on a permanent object -- converted to memory_object_data_error\n");
		return(memory_object_data_error(object, offset, size, KERN_SUCCESS));
	}
*/
	vm_object_lock(object);
	offset -= object->paging_offset;

	while (size != 0) {
		register vm_page_t m;

		if (((m = vm_page_lookup(object, offset)) != VM_PAGE_NULL)) {
			/*
			 *	We're looking for pages that are both busy and
			 *	absent (waiting to be filled), converting them
			 *	to just absent.
			 *
			 *	Pages that are just busy can be ignored entirely.
			 */
			if (m->busy && m->absent) {
				if (m->fictitious)
					VM_PAGE_FREE(m);
				 else
					PAGE_WAKEUP(m);
			}
		}
		size -= PAGE_SIZE;
		offset += PAGE_SIZE;
	 }
	vm_object_unlock(object);

	vm_object_deallocate(object);
	return(KERN_SUCCESS);
}

kern_return_t	memory_object_lock_request(object, offset, size, should_clean, should_flush, prot, reply_to)
	register
	vm_object_t	object;
	register
	vm_offset_t	offset;
	register
	vm_size_t	size;
	boolean_t	should_clean;
	boolean_t	should_flush;
	vm_prot_t	prot;
	port_t		reply_to;
{
	vm_offset_t	original_offset = offset;
	vm_size_t	original_size = size;

	if (object == VM_OBJECT_NULL)
		return(KERN_FAILURE);

	size = round_page(size);

	vm_object_lock(object);
	offset -= object->paging_offset;

	if (atop(size) > object->resident_page_count) {
		/* XXX
		 *	Should search differently!
		 *	Must be careful to preserve ordering appearance.
		 */;
	}
		
	for (; size != 0; size -= PAGE_SIZE, offset += PAGE_SIZE) {
		register vm_page_t m;

		while ((m = vm_page_lookup(object, offset)) != VM_PAGE_NULL) {
			if (m->absent)
				break;

			if (m->busy || (m->wire_count != 0)) {
				PAGE_ASSERT_WAIT(m, FALSE);
				vm_object_unlock(object);
				thread_block();
				vm_object_lock(object);
				continue;
			}

			/*
			 *	Check for cleaning and flushing before worrying
			 *	about locking
			 */

			vm_page_lock_queues();

			/*
			 *	XXX Optimize these sequences
			 */

			if (should_clean || should_flush) {
				if (m->active)
					vm_page_deactivate(m);

				if (should_flush) {
					pmap_page_protect(m->phys_addr, VM_PROT_NONE);
					pmap_update();
				}

				if (should_clean && !m->dirty)
					m->dirty = pmap_is_modified(m->phys_addr);
			}

			if (should_clean && m->dirty) {
				assert(!m->active);
				VM_PAGE_QUEUES_REMOVE(m);

				vm_page_unlock_queues();
				if (!should_flush) {
					pmap_page_protect(m->phys_addr, VM_PROT_NONE);
					pmap_update();
				}
				vm_pageout_page(m, FALSE);
				break;
			}

			if (should_flush) {
				vm_page_free(m);
				vm_page_unlock_queues();
				break;
			}
			vm_page_unlock_queues();

			/*
			 *	If we are decreasing permission, do it now;
			 *	else, let the fault handler take care of it.
			 */

			if ((m->page_lock ^ prot) & prot)
				pmap_page_protect(m->phys_addr, VM_PROT_ALL & ~prot);
			else
				PAGE_WAKEUP(m);

			m->page_lock = prot;
			m->unlock_request = VM_PROT_NONE;
			break;
		}
	}

	if (reply_to != PORT_NULL) {
		/*
		 *	Prevent the control port from being destroyed
		 *	while we're making the completed call.
		 */

		vm_object_paging_begin(object);
		vm_object_unlock(object);

		(void) memory_object_lock_completed(reply_to, object->pager_request, original_offset, original_size);

		vm_object_lock(object);
		vm_object_paging_end(object);
	}

	vm_object_unlock(object);
	vm_object_deallocate(object);
	return(KERN_SUCCESS);
}

kern_return_t	memory_object_set_attributes(object, object_ready,
						may_cache, copy_strategy)
	vm_object_t	object;
	boolean_t	object_ready;
	boolean_t	may_cache;
	memory_object_copy_strategy_t copy_strategy;
{
	if (object == VM_OBJECT_NULL)
		return(KERN_INVALID_ARGUMENT);

	/*
	 *	Verify the attributes of importance
	 */

	switch(copy_strategy) {
		case MEMORY_OBJECT_COPY_NONE:
		case MEMORY_OBJECT_COPY_CALL:
		case MEMORY_OBJECT_COPY_DELAY:
			break;
		default:
			vm_object_deallocate(object);
			return(KERN_INVALID_ARGUMENT);
	}

	if (object_ready)
		object_ready = TRUE;
	if (may_cache)
		may_cache = TRUE;

	vm_object_lock(object);

	/*
	 *	Wake up anyone waiting for the ready attribute
	 *	to become asserted.
	 */

	if (object_ready && !object->pager_ready)
		vm_object_wakeup(object, VM_OBJECT_EVENT_PAGER_READY);

	/*
	 *	Copy the attributes
	 */

	object->can_persist = may_cache;
	object->pager_ready = object_ready;
	object->copy_strategy = copy_strategy;

	vm_object_unlock(object);

	vm_object_deallocate(object);

	return(KERN_SUCCESS);
}

kern_return_t	memory_object_get_attributes(object, object_ready,
						may_cache, copy_strategy)
	vm_object_t	object;
	boolean_t	*object_ready;
	boolean_t	*may_cache;
	memory_object_copy_strategy_t *copy_strategy;
{
	if (object == VM_OBJECT_NULL)
		return(KERN_INVALID_ARGUMENT);

	vm_object_lock(object);
	*may_cache = object->can_persist;
	*object_ready = object->pager_ready;
	*copy_strategy = object->copy_strategy;
	vm_object_unlock(object);

	vm_object_deallocate(object);

	return(KERN_SUCCESS);
}

kern_return_t	vm_set_default_memory_manager(host, default_manager)
	task_t		host;
	memory_object_t	*default_manager;
{
	memory_object_t	old_DMM;

	/*
	 *	XXX Until there is a privileged host port, we'll receive
	 *	this call on any task port, but only actually do
	 *	anything in privileged *threads*.
	 */

	if (!current_thread()->vm_privilege) {
		*default_manager = PORT_NULL;
		return(KERN_INVALID_ARGUMENT);
	}

	simple_lock(&memory_manager_default_lock);

	/*
	 *	Stash the old value, and take a reference
	 *	for our return value.
	 */

	if ((old_DMM = memory_manager_default) != PORT_NULL)
		port_reference(old_DMM);
	
	/*
	 *	Record the new value permanently, trading
	 *	references as necessary.
	 *
	 *	Note that it is considered valid to make this
	 *	call with (default_manager == PORT_NULL) merely
	 *	to retrieve the current value.
	 */

	if (*default_manager != PORT_NULL) {
		memory_manager_default = *default_manager;
		port_reference(memory_manager_default);

		if (old_DMM != PORT_NULL)
			port_release(old_DMM);

		/*
		 *	In case anyone's been waiting for a memory
		 *	manager to be established, wake them up.
		 */

		thread_wakeup((int) &memory_manager_default);
	}

	simple_unlock(&memory_manager_default_lock);

	*default_manager = old_DMM;

	return(KERN_SUCCESS);
}

port_t		memory_manager_default_reference()
{
	memory_object_t	DMM;

	simple_lock(&memory_manager_default_lock);
	while ((DMM = memory_manager_default) == PORT_NULL)  {
		thread_sleep((int) &memory_manager_default,
			simple_lock_addr(memory_manager_default_lock),
			FALSE);
		simple_lock(&memory_manager_default_lock);
	}

	port_reference(DMM);
	simple_unlock(&memory_manager_default_lock);

	return(DMM);
}

void		memory_manager_default_init()
{
	memory_manager_default = PORT_NULL;
	simple_lock_init(&memory_manager_default_lock);
}
