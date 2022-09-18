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
 * Revision 2.26  90/07/20  08:47:21  mrt
 * 		Bug fix to memory_object_lock_request to avoid corrupting
 * 		offsets for pageout.  Found by rwd.
 * 	[90/07/20            dlb]
 * 
 * Revision 2.25  90/07/05  12:29:11  mrt
 * 	Bug fix to make multiple entry page stealing work.
 * 	[90/07/05            dlb]
 * 
 * Revision 2.24  90/07/05  12:17:23  mrt
 * 	Fix bugs and improve handling of paging references in
 * 	memory_object_lock_request.
 * 	[90/07/03            dlb]
 * 	Reject attempts to pagein partial pages.
 * 	Modify page stealing code to deal with multi-page pageins.
 * 	Add annoying printf for pager_cache.
 * 
 * 	Purge MACH_XP_FPD.
 * 	Precious pages are returned to the manager w/o changing postion
 * 	on the pageout queues.  Non-precious pages are freed.
 * 
 * 	Gut memory_object_data_provided, and replace by calling
 * 	memory_object_data_supply. 
 * 
 * 	Remove vm_map_copy_discard operations done by ipc code.  Add
 * 	discard argument (FALSE) to vm_map_copyout to tell it not
 * 	to discard copies.
 * 
 * 	First version of page-stealing code.  Also remove erroneous free
 * 	of fictitious page in memory_object_data_provided.  Remove
 * 	memory_object_debug code.
 * 
 * 	Add memory_object_data_supply.  Still needs page stealing code.
 * 	Use careful_copy_to_physical_page in memory_object_data_provided.
 * 	Remove pager_data_provided_inline.
 * 
 * 	Support precious pages in memory_object_lock_request.  Note that
 * 	flushing by itself drops their contents on the floor; cleaning
 * 	and flushing returns clean precious pages to the manager (as
 * 	well as any dirty pages).
 * 
 * 	Pick up new version of memory_object_lock_request from pure
 * 	kernel to get "clean without flush" functionality.  This also
 * 	sends pages to pager in contiguous chunks.  Also convert
 * 	vm_set_default_memory_manager to use the privileged host post.
 * 	[90/06/11            dlb]
 * 
 * Revision 2.22  89/12/22  15:55:18  rpd
 * 	Fix placeholder page handling in memory_object_data_provided.  Old
 * 	code was calling zalloc while holding a lock.
 * 	[89/12/13  19:58:28  dlb]
 * 
 * 	Don't clear busy flags on any pages in memory_object_lock_page
 * 	(from memory_object_lock_request)!!  Implemented by changing
 * 	PAGE_WAKEUP to not clear busy flag and using PAGE_WAKEUP_DONE
 * 	when it must be cleared.  See vm/vm_page.h.  With dbg's help.
 * 	[89/12/13            dlb]
 * 
 * 	Don't activate fictitious pages after freeing them in
 * 	memory_object_data_{unavailable,error}.  Add missing lock and
 * 	unlock of page queues when activating pages in same routines.
 * 	[89/12/11            dlb]
 * 	Retry lookup after using CLEAN_DIRTY_PAGES in
 * 	memory_object_lock_request().  Also delete old version of
 * 	memory_object_data_provided().  From mwyoung.
 * 	[89/11/17            dlb]
 * 
 * Revision 2.21  89/10/11  14:58:32  dlb
 * 	New calling sequence for vm_map_pageable.
 * 	[89/01/26            dlb]
 * 
 * Revision 2.20  89/10/10  15:12:31  mwyoung
 * 	Fix minor typo.
 * 
 * Revision 2.19  89/10/10  11:06:05  mwyoung
 * 	Save all page-cleaning operations until it becomes necessary
 * 	to block in memory_object_lock_request().
 * 	[89/09/30  18:07:16  mwyoung]
 * 
 * 	Split out a per-page routine for lock requests.
 * 	[89/08/20  19:47:42  mwyoung]
 * 
 * 	Verify that the user memory used in memory_object_data_provided()
 * 	is valid, even if it won't be used to fill a page request.
 * 	[89/08/01  14:58:21  mwyoung]
 * 
 * 	Make memory_object_data_provided atomic, interruptible, and serializable
 * 	when handling multiple pages.  Add optimization for single-page
 * 	operations.
 * 	[89/05/12  16:06:13  mwyoung]
 * 
 * 	Simplify lock/clean/flush sequences memory_object_lock_request.
 * 	Correct error in call to pmap_page_protect() there.
 * 	Make error/absent pages eligible for pageout.
 * 	[89/04/22            mwyoung]
 * 
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
#include <mach/message.h>

/*
 *	Implementation dependencies:
 */
#include <vm/vm_page.h>
#include <vm/vm_pageout.h>
#include <vm/pmap.h>		/* For pmap_clear_modify */
#include <kern/thread.h>	/* For current_thread() */
#include <kern/host.h>		/* host_t for vm_set_default_memory_manager */
#include <vm/vm_kern.h>		/* For careful_copy_to_phys */
#include <vm/vm_map.h>		/* For vm_map_copy routines */
#include <kern/ipc_globals.h>	/* For ipc_kernel_map */
#include <kern/kern_port.h>

#include <kern/xpr.h>

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

/*
 *	memory_object_data_provided will be obsolete soon.
 *	Use memory_object_data_supply (and its page stealing
 *	code) instead.
 */

kern_return_t
memory_object_data_provided(object, offset, data, data_cnt, lock_value)
	vm_object_t	object;
	vm_offset_t	offset;
	vm_map_copy_t	data;
	register
	unsigned int	data_cnt;
	vm_prot_t	lock_value;
{
	return(memory_object_data_supply(object, offset, data, data_cnt,
		FALSE, lock_value, FALSE, PORT_NULL));
}

int		memory_object_stolen_count = 0;

/*
 *	Limit on size of precious data that can be handled by one supply.
 * 	Chosen so that vm_map_copyout of precious data cannot fail.
 *
 * XXX	Should be defined in header file, tied to size of ipc_kernel_map, and
 * XXX	made visible to users.  Current value is one quarter the map size.
 */

#define	MEMORY_OBJECT_SUPPLY_PRECIOUS_LIMIT	256*1024

kern_return_t memory_object_data_supply(object, offset, data_copy, data_cnt,
	data_dealloc, lock_value, precious, reply_to)
	register
	vm_object_t	object;
	register
	vm_offset_t	offset;
	vm_map_copy_t	data_copy;	
	unsigned int	data_cnt;
	boolean_t	data_dealloc;
	vm_prot_t	lock_value;
	boolean_t	precious;
	port_t		reply_to;
{
	register
	vm_offset_t	kdata;
	kern_return_t	result = KERN_SUCCESS;
	vm_offset_t	error_offset = 0;
	register
	vm_page_t	m;
	int		absent_count = 0;
	vm_offset_t	kernel_data = 0;
	vm_size_t	original_length;
	vm_offset_t	original_offset;
	vm_object_t	new_object = VM_OBJECT_NULL;
	vm_map_entry_t	entry;
	register
	vm_object_t	source_object;
	register
	vm_page_t	data_m;


	XPR(XPR_MEMORY_OBJECT,
		("memory_object_data_supply, object 0x%x, offset 0x%x",
				object, offset, 0, 0));

#ifdef	lint
	data_dealloc++;
#endif	lint

	/*
	 *	Look for bogus arguments
	 */

	if (object == VM_OBJECT_NULL) {
		return(KERN_INVALID_ARGUMENT);
	}

	if ((lock_value & ~VM_PROT_ALL) ||
	    (precious && (data_cnt > MEMORY_OBJECT_SUPPLY_PRECIOUS_LIMIT))) {
		vm_object_deallocate(object);
		return(KERN_INVALID_ARGUMENT);
	}

	if ((data_cnt % PAGE_SIZE) != 0) {
	    uprintf("memory_object_data_supply: invalid partial pagein\n");
	    vm_object_deallocate(object);
	    return(KERN_INVALID_ARGUMENT);
	}

	/*
	 *	Adjust the offset from the memory object to the offset
	 *	within the vm_object.
	 *
	 *	Once we look at the paging_offset, we must ensure that
	 *	the object cannot be collapsed.  This means taking a
	 *	paging reference for now.
	 */

	original_length = data_cnt;
	original_offset = offset;

	vm_object_lock(object);
	offset -= object->paging_offset;
	vm_object_paging_begin(object);
	vm_object_unlock(object);

	/*
	 *	Page stealing code:  if deallocating source, attempt
	 *	to steal its pages for target.
	 */


	entry = vm_map_copy_first_entry(data_copy);
	source_object = entry->object.vm_object;

	/*
	 *	Loop over copy stealing pages for pagein.  First
	 *	page that cannot be stolen causes break out of loop.
	 *	Second part of routine inserts copy into ipc kernel map
	 *	and copies the remaining pages.
	 */

	while (TRUE) {

		/*
		 *	Must have an object, not the target object.
		 */

		if (source_object == VM_OBJECT_NULL ||
		    source_object == object)
			break;
RetrySteal:
		vm_object_lock(source_object);

		/*
		 *	Can steal if we are the only use of this
		 *	object (ref_count of 1) or this range of
		 *	this object (object is temporary and
		 *	its ref_count was 1 before vm_map_copyin -
		 *	vm_map_copyin sets single_use to say so).
		 */

		if (source_object->ref_count != 1 &&
		    (!source_object->temporary || !entry->single_use)) {

			vm_object_unlock(source_object);
			break;
		}
			
		/*
		 *	Lookup source page.  Cannot steal if it is busy,
		 *	in error, absent, or fictitious.  Cannot steal
		 *	dirty or precious pages from permanent objects.
		 *	Temporary objects do not have precious pages,
		 *	and it is ok to steal dirty pages from them
		 *	because the previous if statement ensures that
		 *	no one will ever use them if we got here.
		 */
		data_m = vm_page_lookup(source_object, entry->offset);

		if (data_m == VM_PAGE_NULL || data_m->busy ||
		    data_m->error || data_m->absent || data_m->fictitious ||
		    (!source_object->temporary &&
		     (data_m->dirty || data_m->precious))) {

			vm_object_unlock(source_object);
			break;
		}		

		/*
		 *	Try to lock target object.  Must unlock source
		 *	if we fail to prevent deadlock.
		 */				

		if (!vm_object_lock_try(object)) {
			vm_object_unlock(source_object);
			/*
			 * Should spin for a while
			 */
			goto RetrySteal;
		}

		/*
		 *	Look up target page and check its state.
		 */

		data_m->was_absent = FALSE;
		m = vm_page_lookup(object,offset);
		if (m != VM_PAGE_NULL) {
		    if (m->absent && m->busy) {

			/*
			 *	Page was requested.  Free the busy
			 *	page waiting for it.  Insertion
			 *	of new page happens below.
			 */

			VM_PAGE_FREE(m);
			data_m->was_absent = TRUE;
		    }
		    else {

			/*
			 *	Page already present; no pagein.
			 *	This is an error if data is precious.
			 */

			if (precious) {
			    result = KERN_MEMORY_PRESENT;
			    error_offset = offset + object->paging_offset;
			}

			vm_object_unlock(object);
			VM_PAGE_FREE(data_m);
			vm_object_unlock(source_object);

			goto StealNextPage;
		    }
		}
		else if (vm_page_free_count < vm_page_free_target) {

		    /*
		     * Page not requested, and system is short on memory.
		     * Pagein does not occur.  Precious data must be returned.
		     */

		    error_offset = offset + object->paging_offset;
		    result = KERN_RESOURCE_SHORTAGE;
		    vm_object_unlock(object);

		    if (precious) {

			/*
			 *	Return page to manager.  We do the dirty
			 *	work here to avoid removing the page from
			 *	the pageout queues.  This prevents a manager
			 *	from flooding the system by continually
			 *	resupplying precious pages; the default
			 *	pager will eventually page them out.
			 *
			 *	Need a new object for pageout, but
			 *	things could change when we
			 *	drop the locks to allocate it.
			 */

			if (new_object == VM_OBJECT_NULL) {
			    vm_object_unlock(source_object);
			    new_object = vm_object_allocate(PAGE_SIZE);
			    goto RetrySteal;
			}

			/*
			 *	Put the page in the new object
			 *	and return it to the manager.  Ok to
			 *	lock new_object because we have only ref.
			 */

			vm_object_lock(new_object);
			vm_page_rename(data_m, new_object, 0);
			vm_object_unlock(source_object);

			data_m->dirty = TRUE;
			data_m->precious = FALSE;
			data_m->page_lock = VM_PROT_NONE;
			data_m->unlock_request = VM_PROT_NONE;
			vm_object_unlock(new_object);

			memory_object_data_return(object->pager,
				object->pager_request, error_offset,
				(pointer_t) new_object, PAGE_SIZE);

			new_object = VM_OBJECT_NULL;

			goto StealNextPage;
		    }
		    else {

			/*
			 *	Not requested, and not precious.
			 *	Free it to help with memory shortage.
			 */

			VM_PAGE_FREE(data_m);
			vm_object_unlock(source_object);

			goto StealNextPage;
		    }

		}

		/*
		 *	Ok to pagein page.  Target object now has no page
		 *	at offset.  First drop in the new page, and make
		 *	it clean.  Then set the page parameters.  Still
		 *	holding both object locks at this point.
		 */

		vm_page_rename(data_m, object, offset);
		data_m->dirty = FALSE;
		pmap_clear_modify(data_m->phys_addr);
		memory_object_stolen_count++;

		data_m->page_lock = lock_value;
		data_m->unlock_request = VM_PROT_NONE;
		data_m->precious = precious;
		
		/*
		 *	Set appropriate pageout state.
		 * XXX	Deactivate may be wrong.
		 */

		vm_page_lock_queues();
		if (!data_m->was_absent)
		    vm_page_deactivate(data_m);
		else if (!data_m->active)
		    vm_page_activate(data_m);
		vm_page_unlock_queues();

		vm_object_unlock(source_object);
		vm_object_unlock(object);

		/*
		 *	Setup to steal next page.
		 *	No object locks are held at this point.
		 */

StealNextPage:

		/*
		 *	Advance to next page in target.
		 */

		offset += PAGE_SIZE;
		data_cnt -= PAGE_SIZE;

		/*
		 *	Check for done.  Send a reply if one was requested.
		 */

		if (data_cnt == 0) {
		    if (reply_to != PORT_NULL) {
			memory_object_supply_completed(
				reply_to,
				object->pager_request,
				original_offset,
				original_length,
				result,
				error_offset);
		    }

		    vm_object_lock(object);
		    vm_object_paging_end(object);
		    vm_object_unlock(object);
		    vm_object_deallocate(object);

		    if (new_object != VM_OBJECT_NULL)
		    	vm_object_deallocate(new_object);

		    return(result);
		}

		/*
		 *	Advance to next page in copy.
		 */

		entry->vme_start += PAGE_SIZE;
		if (entry->vme_start == entry->vme_end) {
		    vm_map_copy_entry_delete(data_copy, entry);
		    entry = vm_map_copy_first_entry(data_copy);
		    source_object = entry->object.vm_object;
		}
		else {
		    entry->offset += PAGE_SIZE;
		}

		/*
		 *	Continue with while loop.
		 */
	}

	if (new_object != VM_OBJECT_NULL) {
		vm_object_deallocate(new_object);
		new_object = VM_OBJECT_NULL;
	}

	/*
	 *	Page stealing code has failed.  Copy the data into the kernel.
	 *	Don'd discard copy; caller (e.g., ipc code) will do that later.
	 *	PRECIOUS_LIMIT guarantees success for precious data.
	 */

	if (vm_map_copyout(ipc_kernel_map, &kernel_data, data_copy, FALSE)
	     != KERN_SUCCESS) {
		if (precious)
			panic("memory_object_data_supply: copyout failure");
		else
			printf("memory_object_data_supply: %s",
			"memory_object_data_supply: cannot move data");
		vm_object_deallocate(object);
		return(KERN_RESOURCE_SHORTAGE);
	}
	kdata = kernel_data;

	/*
	 *	Loop over the data, supplying it a page at a time.
	 */

	vm_object_lock(object);

	for (;
	     data_cnt >= PAGE_SIZE;
	     data_cnt -= PAGE_SIZE, kdata += PAGE_SIZE, offset += PAGE_SIZE) {

		/*
		 *	See whether there is a page waiting for our data.
		 *	If fictitious and absent (and busy?), get rid of it.
		 */

RetryPagein:
		m = vm_page_lookup(object, offset);

		if (m->fictitious) {
		    	if (m->absent) {
				VM_PAGE_FREE(m);
				m = VM_PAGE_NULL;
			}
			else {
				/*
				 *	It's a placeholder for pageout,
				 *	wait for it to be removed.
				 */
				PAGE_ASSERT_WAIT(m, FALSE);
				vm_object_unlock(object);
				thread_block();
				vm_object_lock(object);
				goto RetryPagein;
			}
		}
		if (m == VM_PAGE_NULL) {
			/*
			 *	No page waiting -- see whether we can allocate
			 *	one, but don't bother waiting unless the data
			 *	is precious.
			 */

			if ((m = vm_page_alloc(object, offset))
			    == VM_PAGE_NULL) {

				if (precious) {
					/*
					 *	If we got here, the page
					 *	stealing code could not
					 *	cope with this page.
					 *	Returning it requires
					 *	allocating a page for the
					 *	copy.  Wait and allocate
					 *	the page for pagein instead.
					 */
					vm_object_unlock(object);
					VM_WAIT;
					vm_object_lock(object);

					goto RetryPagein;
				}

				/*
				 *	Won't pagein this page.
				 *	Make a note of it.
				 */

				if (result == KERN_SUCCESS) {
					result = KERN_RESOURCE_SHORTAGE;
					error_offset = offset +
						object->paging_offset;
				}
				
				continue;
			}
		} else {

			/*
			 *	Only overwrite pages that are "absent".
			 *	Drop precious data on floor if corresponding
			 *	page is already present; this is a manager
			 *	error.
			 */

			if (!(m->busy && m->absent)) {
				/*
				 *	This is an error if the supplied data
				 *	is precious.  The supplied (precious)
				 *	data will not be returned.
				 */
				if (precious && result == KERN_SUCCESS) {
					result = KERN_MEMORY_PRESENT;
					error_offset = offset +
						object->paging_offset;
				}
				    
				continue;
			}
		}

		/*
		 *	At this point, the page in question should be
		 *	"busy".  If it was previously requested, then it
		 *	will also be "absent".
		 */

		/*
		 *	Copy in the data.
		 *
		 *	Note that we must unlock the object, because
		 *	the copy may fault (and may be interrupted).
		 *
		 *	Mark page not absent to prevent other threads
		 *	from monkeying with it.
		 */

		m->was_absent = m->absent;
		if (m->absent) {
			absent_count++;
			m->absent = FALSE;
		}

		vm_object_unlock(object);

		if (careful_copy_to_physical_page(kdata, m, data_cnt, TRUE)
		    != KERN_SUCCESS) {

			/*
			 *	Supplied data is bogus.  If the page
			 *	was requested, mark it in error for
			 *	the requestor.  Otherwise free it.
			 *	Precious does not matter because the
			 *	precious data does not exist.
			 */

			if (result == KERN_SUCCESS) {
				result = KERN_MEMORY_ERROR;
				error_offset = offset + object->paging_offset;
			}

			if (m->was_absent) {
				m->error = TRUE;
			}
			else {
				VM_PAGE_FREE(m);
				continue;
			}
		}

		pmap_clear_modify(m->phys_addr);
		vm_object_lock(object);
		
		/*
		 *	Make page eligible for pageout.  Non-requested
		 *	pages get deactivated; first use will activate.
		 *
		 *  XXX Deactivation decision may be wrong.
		 */
		vm_page_lock_queues();
		if (!m->was_absent)
			vm_page_deactivate(m);
		else if (!m->active)
			vm_page_activate(m);
		vm_page_unlock_queues();

		/*
		 *	Set the page parameters.  Ok to do this to
		 *	an error page because the fault handler
		 *	checks for error first.
		 */

		m->page_lock = lock_value;
		m->unlock_request = VM_PROT_NONE;
		m->precious = precious;
		
		PAGE_WAKEUP_DONE(m);
	}

	/*
	 *	Release all of the absent_count references at once.
	 */

	if (absent_count) {
		object->absent_count -= absent_count;
		vm_object_wakeup(object, VM_OBJECT_EVENT_ABSENT_COUNT);
	}

	/*
	 *	Send reply if one was requested.
	 */

SendReply: ;

	if (reply_to != PORT_NULL) {
		vm_object_unlock(object);

		memory_object_supply_completed(
				reply_to,
				object->pager_request,
				original_offset,
				original_length,
				result,
				error_offset);

		vm_object_lock(object);
	}

	vm_object_paging_end(object);
	vm_object_unlock(object);
	vm_object_deallocate(object);

	if (kernel_data != 0)
		vm_deallocate(ipc_kernel_map, kernel_data, original_length);

	return(result);
}

kern_return_t memory_object_data_error(object, offset, size, error_value)
	vm_object_t	object;
	vm_offset_t	offset;
	vm_size_t	size;
	kern_return_t	error_value;
{
	XPR(XPR_MEMORY_OBJECT, ("memory_object_data_error, object 0x%x, offset 0x%x",
				object, offset, 0, 0));
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

					vm_page_lock_queues();
					if (!m->active)
						vm_page_activate(m);
					vm_page_unlock_queues();
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
				if (m->fictitious) {
					VM_PAGE_FREE(m);
				}
				else {
					PAGE_WAKEUP_DONE(m);
					vm_page_lock_queues();
					if (!m->active)
						vm_page_activate(m);
					vm_page_unlock_queues();
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

/*
 *	Routine:	memory_object_lock_page
 *
 *	Description:
 *		Perform the appropriate lock operations on the
 *		given page.  See the description of
 *		"memory_object_lock_request" for the meanings
 *		of the arguments.
 *
 *		Returns an indication that the operation
 *		completed, blocked, or that the page must
 *		be cleaned.
 */
typedef	int		memory_object_lock_result_t;
#define	MEMORY_OBJECT_LOCK_RESULT_DONE		0
#define	MEMORY_OBJECT_LOCK_RESULT_MUST_BLOCK	1
#define	MEMORY_OBJECT_LOCK_RESULT_MUST_CLEAN	2
#define MEMORY_OBJECT_LOCK_RESULT_MUST_RETURN	3

memory_object_lock_result_t memory_object_lock_page(m, should_clean, should_flush, prot)
	vm_page_t	m;
	boolean_t	should_clean;
	boolean_t	should_flush;
	vm_prot_t	prot;
{
	vm_object_t	object = m->object;

	/*
	 *	Don't worry about pages for which the kernel
	 *	does not have any data.
	 */

	if (m->absent)
		return(MEMORY_OBJECT_LOCK_RESULT_DONE);

	/*
	 *	If we cannot change access to the page,
	 *	either because a mapping is in progress
	 *	(busy page) or because a mapping has been
	 *	wired, then give up.
	 */

	if (m->busy || (m->wire_count != 0)) {
		/*
		 *	If no change would take place
		 *	anyway, return successfully.
		 */

		if (!should_flush &&
		    (m->page_lock == prot)) {
			if (!should_clean ||
			    ((prot & VM_PROT_WRITE) &&
			     !m->dirty &&
			     !pmap_is_modified(m->phys_addr)
			    )
			   ) {
				/*
				 *	Restart page unlock requests,
				 *	even though no change took place.
				 *	[Memory managers may be expecting
				 *	to see new requests.]
				 */
				m->unlock_request = VM_PROT_NONE;
				PAGE_WAKEUP(m);

				return(MEMORY_OBJECT_LOCK_RESULT_DONE);
			}
		}

		return(MEMORY_OBJECT_LOCK_RESULT_MUST_BLOCK);
	}

	/*
	 *	If the page is to be flushed, allow
	 *	that to be done as part of the protection.
	 */

	if (should_flush)
		prot = VM_PROT_ALL;

	/*
	 *	Set the page lock.
	 *
	 *	If we are decreasing permission, do it now;
	 *	else, let the fault handler take care of it.
	 */

	if ((m->page_lock ^ prot) & prot)
		pmap_page_protect(m->phys_addr, VM_PROT_ALL & ~prot);
	m->page_lock = prot;


	/*
	 *	Restart any past unlock requests, even if no
	 *	change was made.
	 */

	m->unlock_request = VM_PROT_NONE;
	PAGE_WAKEUP(m);

	/*
	 *	Handle cleaning.
	 */

	if (should_clean) {
		/*
		 *	Check whether the page is dirty.  If
		 *	write permission has not been removed,
		 *	this may have unpredictable results.
		 */

		if (!m->dirty)
			m->dirty = pmap_is_modified(m->phys_addr);

		/*
		 *	Dirty pages and clean precious pages go back
		 *	to the manager
		 */
		if (m->dirty || (m->precious && should_flush)) {
			/*
			 *	If we weren't planning
			 *	to flush the page anyway,
			 *	we may need to remove the
			 *	page from the pageout
			 *	system and from physical
			 *	maps now.
			 */

			vm_page_lock_queues();
			VM_PAGE_QUEUES_REMOVE(m);
			vm_page_unlock_queues();

			if (!should_flush)
				pmap_page_protect(m->phys_addr,
						VM_PROT_NONE);

			/*
			 *	Cleaning or returning a page will cause
			 *	it to be flushed.
			 */

			if (m->dirty)
			    return(MEMORY_OBJECT_LOCK_RESULT_MUST_CLEAN);
			else
			    /*
			     *	Must be a clean precious page.
			     */
			    return(MEMORY_OBJECT_LOCK_RESULT_MUST_RETURN);
		}
	}

	/*
	 *	Handle flushing.  Precious pages are only returned if
	 *		should_clean is specified (see above).
	 */

	if (should_flush)
		VM_PAGE_FREE(m);

	return(MEMORY_OBJECT_LOCK_RESULT_DONE);
}

/*
 *	Routine:	memory_object_lock_request [user interface]
 *
 *	Description:
 *		Control use of the data associated with the given
 *		memory object.  For each page in the given range,
 *		perform the following operations, in order:
 *			1)  restrict access to the page (disallow
 *			    forms specified by "prot");
 *			2)  write back modifications (if "should_clean"
 *			    is asserted, and the page is dirty); and,
 *			3)  flush the cached copy (if "should_flush"
 *			    is asserted).
 *		The set of pages is defined by a starting offset
 *		("offset") and size ("size").  Only pages with the
 *		same page alignment as the starting offset are
 *		considered.
 *
 *		NOTE: Precious pages are freed by should_flush.  To get them
 *		returned, should_clean AND should_flush are required.
 *
 *		A single acknowledgement is sent (to the "reply_to"
 *		port) when these actions are complete.
 */
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
	register
	vm_page_t	m;
	vm_offset_t	original_offset = offset;
	vm_size_t	original_size = size;
	vm_offset_t	paging_offset = 0;
	vm_object_t	new_object = VM_OBJECT_NULL;
	vm_offset_t	new_offset = 0;
	int		page_lock_result;
	int		pageout_action;


#define	DATA_WRITE_MAX	32
	vm_page_t		holding_pages[DATA_WRITE_MAX];

	/*
	 *	Check for bogus arguments
	 */

	if ((object == VM_OBJECT_NULL) ||
		((prot & ~VM_PROT_ALL) != 0))
			return(KERN_INVALID_ARGUMENT);

	size = round_page(size);

	vm_object_lock(object);
	vm_object_paging_begin(object);
	offset -= object->paging_offset;

	/*
	 *	To avoid blocking while scanning for pages, save
	 *	dirty pages to be cleaned all at once.
	 *
	 *	XXXO A similar strategy could be used to limit the
	 *	number of times that a scan must be restarted for
	 *	other reasons.  Those pages that would require blocking
	 *	could be temporarily collected in another list, or
	 *	their offsets could be recorded in a small array.
	 */

	/*
	 *	The PAGEOUT_PAGES macro sends a contiguous range
	 *	of dirty or clean precious pages (but not both) to the pager
	 *	in one message.  vm_pageout_setup moves these pages into
	 *	a new object and substitutes a 	fictitious holding page
	 *	(and returns it).  These pages prevent pagein events while
	 *	pageout is in progress.  Once the pageout is done, they must
	 *	be freed.  vm_pageout_setup handles copying the page if it
	 *	needs to be cleaned but not flushed.
	 */

#define	PAGEOUT_PAGES					\
MACRO_BEGIN 						\
	register int	i; 				\
							\
	vm_object_unlock(object);			\
							\
	(void) (*((pageout_action == MEMORY_OBJECT_LOCK_RESULT_MUST_CLEAN) \
			? memory_object_data_write	\
			: memory_object_data_return))(	\
		object->pager,				\
		object->pager_request,			\
		paging_offset,				\
		(pointer_t)new_object,			\
		new_offset);				\
							\
	vm_object_lock(object);				\
							\
	for (i = 0; i < atop(new_offset); i++) {	\
	    m = holding_pages[i];			\
	    if (m != VM_PAGE_NULL)			\
		VM_PAGE_FREE(m);			\
	} 						\
 							\
	new_object = VM_OBJECT_NULL;			\
MACRO_END

	for (;
	     size != 0;
	     size -= PAGE_SIZE, offset += PAGE_SIZE)
	{

	    /*
	     *	Must do pending pageouts now if either:
	     *	    - last pass through loop yielded a null page
	     *		(else next page gets wrong offset in new_object).
	     *	    - have gathered maximum number of pages for a pageout
	     */
	    if (new_object != VM_OBJECT_NULL &&
		    (m == VM_PAGE_NULL ||
		     new_offset >= PAGE_SIZE * DATA_WRITE_MAX))
	    {
		PAGEOUT_PAGES;
	    }
	    while ((m = vm_page_lookup(object, offset)) != VM_PAGE_NULL) {
		switch ((page_lock_result = memory_object_lock_page(m,
					should_clean,
					should_flush,
					prot)))
		{
		    case MEMORY_OBJECT_LOCK_RESULT_DONE:
			/*
			 *	End of a cluster of dirty pages.
			 */
			if (new_object != VM_OBJECT_NULL) {
			    PAGEOUT_PAGES;
			    continue;
			}

			break;

		    case MEMORY_OBJECT_LOCK_RESULT_MUST_BLOCK:
			/*
			 *	Since it is necessary to block,
			 *	clean any dirty pages now.
			 */

			if (new_object != VM_OBJECT_NULL) {
				PAGEOUT_PAGES;
				continue;
			}

			PAGE_ASSERT_WAIT(m, FALSE);
			vm_object_unlock(object);
			thread_block();
			vm_object_lock(object);
			continue;

		    case MEMORY_OBJECT_LOCK_RESULT_MUST_CLEAN:
		    case MEMORY_OBJECT_LOCK_RESULT_MUST_RETURN:
			/*
			 *	The clean and return cases are similar,
			 *	but the pages have to be sent to
			 *	the manager separately.
			 */

			if ((new_object != VM_OBJECT_NULL) &&
			    (pageout_action != page_lock_result)) {
				/*
				 *	This destroys new_object.
				 */
				PAGEOUT_PAGES;
			}

			vm_object_unlock(object);

			if (new_object == VM_OBJECT_NULL) {
    			    new_object = vm_object_allocate(original_size);
			    new_offset = 0;
			    paging_offset = m->offset +
					object->paging_offset;
			    pageout_action = page_lock_result;
			}
			/*
			 *	Setup for pageout and remember holding page.
			 */
			holding_pages[atop(new_offset)] =
				vm_pageout_setup(m,
					m->offset + object->paging_offset,
					new_object,
					new_offset,
					should_flush);

			new_offset += PAGE_SIZE;

			vm_object_lock(object);
			break;
		}
		break;
	    }
	}

	/*
	 *	We have completed the scan for applicable pages.
	 *	Clean any pages that have been saved.
	 */

	if (new_object != VM_OBJECT_NULL) {
	    PAGEOUT_PAGES;
	}

	if (reply_to != PORT_NULL) {

		vm_object_unlock(object);

		(void) memory_object_lock_completed(
				reply_to,
				object->pager_request,
				original_offset,
				original_size);

		vm_object_lock(object);
	}

	vm_object_paging_end(object);
	vm_object_unlock(object);
	vm_object_deallocate(object);
	return(KERN_SUCCESS);
}

/*
 *	Annoying printf for obsolete pager_cache call.
 */
kern_return_t	xxx_pager_cache(object, should_cache)
vm_object_t	object;
boolean_t	should_cache;
{
	uprintf("pager_cache is obsolete.  Use memory_object_set_attributes instead.\n");
	return(KERN_FAILURE);
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
	host_t		host;
	memory_object_t	*default_manager;
{
	memory_object_t	old_DMM;

	if (host == HOST_NULL) {
		*default_manager = PORT_NULL;
		return(KERN_INVALID_ARGUMENT);
	}

	simple_lock(&memory_manager_default_lock);

	/*
	 *	Stash the old value, and take a reference
	 *	for our return value.
	 */

	if ((old_DMM = memory_manager_default) != PORT_NULL)
		port_reference((kern_port_t) old_DMM);
	
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
		port_reference((kern_port_t) memory_manager_default);

		if (old_DMM != PORT_NULL)
			port_release((kern_port_t) old_DMM);

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
