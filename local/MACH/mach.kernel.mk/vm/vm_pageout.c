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
 * $Log:	vm_pageout.c,v $
 * Revision 2.29  90/09/05  15:16:15  bohman
 * 	Changed the value of m->busy from FALSE to TRUE in vm_pageout_scan
 * 	before the call to vm_pageout_out. Corrected a bug that was
 * 	picked up from Mach 3.
 * 	[90/08/30            mrt]
 * 
 * Revision 2.28  90/07/03  16:57:53  mrt
 * 	Add precious functionality.  A precious page must be paged back
 * 	to its manager even if it is clean.
 * 	[90/06/13            dlb]
 * 	Pick up pure kernel version of vm_pageout_page to get "clean
 * 	without flush" functionality.  Bug fix to that version of
 * 	vm_pageout_page; must pick up object lock at end.
 * 	[90/06/11            dlb]
 * 
 * Revision 2.27  89/12/22  15:57:21  rpd
 * 	PAGE_WAKEUP --> PAGE_WAKEUP_DONE to reflect the fact that it
 * 	clears the busy flag.
 * 	[89/12/13            dlb]
 * 	Eliminate page lock when writing back a page.
 * 	[89/11/09            mwyoung]
 * 
 * Revision 2.26  89/11/20  11:24:50  mja
 * 	Eliminate page lock when writing back a page.
 * 	[89/11/09            mwyoung]
 * 
 * Revision 2.25  89/10/19  13:17:17  af
 * 	Account for paging_offset when setting external page state.
 * 	[89/10/16  15:29:08  af]
 * 
 * Revision 2.24  89/10/10  16:47:56  mwyoung
 * 	Improve reserve tuning... it was a little too low.
 * 
 * Revision 2.22  89/10/10  14:16:27  mwyoung
 * 	Correct typo during cleanup.
 * 	[89/10/10            mwyoung]
 * 
 * Revision 2.21  89/10/10  13:48:32  mwyoung
 * 	Eliminate XP conditionals.
 * 	[89/10/10            mwyoung]
 * 
 * Revision 2.20  89/10/10  13:37:14  mwyoung
 * 	Remove laundry count computations, as the count is never used.
 * 	[89/10/10            mwyoung]
 * 
 * Revision 2.19  89/10/10  11:56:04  mwyoung
 * 	Only attempt to collapse if a memory object has not
 * 	been initialized.  Don't bother to PAGE_WAKEUP in
 * 	vm_pageout_scan() before writing back a page -- it
 * 	gets done in vm_pageout_page().
 * 	[89/10/10            mwyoung]
 * 
 * 	Don't reactivate a page when creating a new memory
 * 	object... continue on to page it out immediately.
 * 	[89/09/20            mwyoung]
 * 
 * 	Reverse the sensing of the desperately-short-on-pages tests.
 * 	[89/09/19            mwyoung]
 * 	Check for absent pages before busy pages in vm_pageout_page().
 * 	[89/07/10  00:01:22  mwyoung]
 * 
 * 	Allow dirty pages to be reactivated.
 * 	[89/04/22            mwyoung]
 * 
 * 	Don't clean pages that are absent, in error, or not dirty in
 * 	vm_pageout_page().  These checks were previously issued
 * 	elsewhere.
 * 	[89/04/22            mwyoung]
 * 
 * Revision 2.18  89/06/12  14:53:05  jsb
 * 	Picked up bug fix (missing splimps) from Sequent via dlb.
 * 	[89/06/12  14:39:28  jsb]
 * 
 * Revision 2.17  89/04/18  21:27:08  mwyoung
 * 	Recent history [mwyoung]:
 * 		Keep hint when pages are written out (call
 * 		 vm_external_state_set).
 * 		Use wired-down fictitious page data structure for "holding_page".
 * 	History condensation:
 * 		Avoid flooding memory managers by using timing [mwyoung].
 * 		New pageout daemon for external memory management
 * 		 system [mwyoung].
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm/vm_pageout.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	The proverbial page-out daemon.
 */
#include <mach_pagemap.h>

#include <vm/vm_page.h>
#include <vm/pmap.h>
#include <vm/vm_object.h>
#include <vm/vm_pageout.h>
#include <mach/vm_statistics.h>
#include <mach/vm_param.h>
#include <kern/thread_swap.h>
#include <kern/kern_port.h>		/* For PORT_OBJECT_PAGING_REQUEST */
#include <kern/ipc_pobj.h>
#include <kern/xpr.h>
#include <mach/mach_types.h>
#include <mach/memory_object.h>
#include <mach/memory_object_user.h>
#include <mach/memory_object_default.h>
#include <machine/machparam.h>			/* for spl's */

#include <machine/vm_tuning.h>

int	vm_pageout_debug = 0;
int	vm_pageout_double_laundry_count = 0;

int	vm_pageout_reserved_internal = 0;
int	vm_pageout_reserved_external = 0;

int	vm_pageout_burst_max = 10;
int	vm_pageout_burst_wait = 5;

boolean_t	vm_pageout_reactivate_dirty_pages = TRUE;

/*
 *	Routine:	vm_pageout_page
 *	Purpose:
 *		Causes the specified page to be written back to
 *		the appropriate memory object.
 *
 *		The "initial" argument specifies whether this
 *		data is an initialization only, and should use
 *		memory_object_data_initialize instead of memory_object_data_write.
 *
 *	In/out conditions:
 *		The page in question must not be on any pageout queues.
 *		The object to which it belongs must be locked.
 *	Implementation:
 *		Move this page to a completely new object.
 */
vm_page_t
vm_pageout_setup(m, paging_offset, new_object, new_offset, flush)
	register vm_page_t	m;
	vm_offset_t		paging_offset;
	register vm_object_t	new_object;
	vm_offset_t		new_offset;
	boolean_t		flush;
{
	register vm_object_t	old_object = m->object;
	kern_return_t	rc;
	register vm_page_t	holding_page;
	register vm_page_t	new_m;

	XPR(XPR_VM_PAGEOUT, ("vm_pageout_page: begin %x", m));

	/*
	 *	If we are not flushing the page, allocate a
	 *	page in the object.  If we cannot get the
	 *	page, flush instead.
	 */
	if (!flush) {
		vm_object_lock(new_object);
		new_m = vm_page_alloc(new_object, new_offset);
		if (new_m == VM_PAGE_NULL)
			flush = TRUE;
		vm_object_unlock(new_object);
	}

	if (flush) {
		/*
		 *	Create a place-holder page where the old one was,
		 *	to prevent anyone from attempting to page in this
		 *	page while we`re unlocked.
		 */
		holding_page = (vm_page_t) zalloc(vm_page_fictitious_zone);

		vm_object_lock(old_object);
		vm_page_remove(m);
		PAGE_WAKEUP_DONE(m);

		vm_page_init(holding_page,
			old_object,
			m->offset,
			(vm_offset_t) 0);
		holding_page->fictitious = TRUE;

		/*
		 *	Record that this page has been written out
		 */
#if	MACH_PAGEMAP
		vm_external_state_set(old_object->existence_info,
					paging_offset,
					VM_EXTERNAL_STATE_EXISTS);
#endif	MACH_PAGEMAP

		vm_object_unlock(old_object);

		vm_object_lock(new_object);

		/*
		 *	Move this page into the new object
		 */

		vm_page_insert(m, new_object, new_offset);
		m->dirty = TRUE;
		m->precious = FALSE;
		m->page_lock = VM_PROT_NONE;
		m->unlock_request = VM_PROT_NONE;
	}
	else {
		/*
		 *	Copy the data into the new page,
		 *	and mark the new page as clean.
		 */
		vm_page_copy(m, new_m);

		vm_object_lock(old_object);
		m->dirty = FALSE;
		pmap_clear_modify(m->phys_addr);

		/*
		 *	Deactivate old page.
		 */
		vm_page_lock_queues();
		vm_page_deactivate(m);
		vm_page_unlock_queues();

		PAGE_WAKEUP_DONE(m);

		/*
		 *	Record that this page has been written out
		 */

#if	MACH_PAGEMAP
		vm_external_state_set(old_object->existence_info,
					paging_offset,
					VM_EXTERNAL_STATE_EXISTS);
#endif	MACH_PAGEMAP

		vm_object_unlock(old_object);

		vm_object_lock(new_object);

		/*
		 *	Use the new page below.
		 */
		m = new_m;
		m->dirty = TRUE;
		assert(!m->precious);
		PAGE_WAKEUP_DONE(m);
	}

	/*
	 *	Make the old page eligible for replacement again; if a
	 *	user-supplied memory manager fails to release the page,
	 *	it will be paged out again to the default memory manager.
	 *
	 *	Note that pages written to the default memory manager
	 *	must be wired down -- in return, it guarantees to free
	 *	this page, rather than reusing it.
	 */

	vm_page_lock_queues();
	vm_stat.pageouts++;
	if (old_object->internal)
		vm_page_wire(m);
	 else
		vm_page_activate(m);
	vm_page_unlock_queues();

	/*
	 *	Mark the page as in the laundry, so we can detect
	 *	pages which aren't released, and so we can decide
	 *	when to stop the pageout scan.
	 */

	if (m->laundry) {
		if (vm_pageout_debug)
			printf("vm_pageout_page: double laundry, object 0x%x offset 0x%x page 0x%x physical 0x%x!\n",
			       old_object, paging_offset, m, m->phys_addr);
		vm_pageout_double_laundry_count++;
	}
	m->laundry = TRUE;
	
	/*
	 *	Since IPC operations may block, we drop locks now.
	 *	[The placeholder page is busy, and we still have
	 *	paging_in_progress incremented.]
	 */

	vm_object_unlock(new_object);

	/*
	 *	Return the placeholder page to simplify cleanup.
	 */
	return (flush ? holding_page : VM_PAGE_NULL);
}

/*
 * Pageout and remove a page.
 * Object is locked and page is busy.
 */
void
vm_pageout_page(m, initial, flush)
	register vm_page_t	m;
	boolean_t		initial;
	boolean_t		flush;
{
	register vm_object_t	old_object;
	register vm_object_t	new_object;
	register vm_page_t	holding_page;
	vm_offset_t		paging_offset;
	kern_return_t		rc;
	register boolean_t	precious_clean;

	assert(m->busy);

	/*
	 *	Cleaning but not flushing a clean precious page is a no-op.
	 *	Also note whether page is clean and precious
	 *	now because vm_pageout_setup will mark it dirty and !precious
	 *
	 *	XXX all current callers of vm_pageout_page want to flush
	 */
	precious_clean = (!m->dirty) && m->precious;
	if (precious_clean && !flush) {
	    PAGE_WAKEUP_DONE(m);
	    return;
	}

	/*
	 *	Verify that we really want to clean this page
	 */

	if (m->absent || m->error || (!m->dirty && !m->precious)) {
		VM_PAGE_FREE(m);
		return;
	}

	/*
	 *	Create a paging reference to let us play with the object.
	 */
	old_object = m->object;
	paging_offset = m->offset + old_object->paging_offset;
	vm_object_paging_begin(old_object);
	vm_object_unlock(old_object);

	/*
	 *	Allocate a new object into which we can put the page.
	 */
	new_object = vm_object_allocate(PAGE_SIZE);

	/*
	 *	Move the page into the new object.
	 */
	holding_page = vm_pageout_setup(m,
				paging_offset,
				new_object,
				0,		/* new offset */
				flush);		/* flush */

	/*
	 *	Write the data to its pager.
	 *
	 *	XXX data_return and data_write to be combined later
	 */
	rc = (*(initial ? memory_object_data_initialize
			: (precious_clean ? memory_object_data_return
					  : memory_object_data_write)))
		(old_object->pager,
		 old_object->pager_request,
		 paging_offset,
		 (pointer_t)new_object,
		 PAGE_SIZE);

	/*
	 *	Clean up.
	 */
	vm_object_lock(old_object);
	if (holding_page != VM_PAGE_NULL) {
	    vm_page_free(holding_page);
	}
	vm_object_paging_end(old_object);
}

/*
 *	vm_pageout_scan does the dirty work for the pageout daemon.
 */
void		vm_pageout_scan()
{
	register vm_page_t	m;
	int		page_shortage;
	int		pages_moved;
	int		burst_count;
	register
	int		s;
	int		free;

	/*
	 *	Only continue when we want more pages to be "free"
	 */

	s = splimp();
	simple_lock(&vm_page_queue_free_lock);
	free = vm_page_free_count;
	simple_unlock(&vm_page_queue_free_lock);
	splx(s);

	if (free < vm_page_free_target) {
		swapout_threads();

		/*
		 *	Be sure the pmap system is updated so
		 *	we can scan the inactive queue.
		 */

		pmap_update();
	}

	/*
	 *	Start scanning the inactive queue for pages we can free.
	 *	We keep scanning until we have enough free pages or
	 *	we have scanned through the entire queue.  If we
	 *	encounter dirty pages, we start cleaning them.
	 *
	 *	NOTE:	The page queues lock is not held at loop entry,
	 *		but *is* held upon loop exit.
	 */

	pages_moved = burst_count = 0;

	while (TRUE) {
		register
		vm_object_t	object;

		vm_page_lock_queues();

		m = (vm_page_t) queue_first(&vm_page_queue_inactive);
		if (queue_end(&vm_page_queue_inactive, (queue_entry_t) m))
			break;

		/*
		 *	If there are enough free pages, stop anyway.
		 */

		s = splimp();
		simple_lock(&vm_page_queue_free_lock);
		free = vm_page_free_count;
		simple_unlock(&vm_page_queue_free_lock);
		splx(s);

		if (free >= vm_page_free_target)
			break;

		/*
		 *	If we've moved a bunch of pages, pause to let
		 *	the memory manager(s) catch up.  This should
		 *	be dynamically tuned, but isn't yet.
		 */

		if (burst_count >= vm_pageout_burst_max) {
			assert_wait(0, TRUE);
			thread_set_timeout(vm_pageout_burst_wait);
			vm_page_unlock_queues();
			thread_block();
			burst_count = 0;
			continue;
		}

		/*
		 */

		object = m->object;

		/*
		 *	If we're extremely tight on pages, we can only
		 *	send pages to the (trusted) default pager.
		 */

		if (free < vm_pageout_reserved_internal) {
			if (!object->internal) {
				/*
				 *	[Don't count this as a reactivation.]
				 */

				vm_page_activate(m);
				vm_page_unlock_queues();
				continue;
			}

			/*
			 *	Stop working entirely when down to that
			 *	portion of the reserved pool that
			 *	is required by the default memory manager.
			 */

			if (free < vm_pageout_reserved_external) {
				/* XXX If the burst_wait is computed
				 * dynamically, it would probably be
				 * wise to change this one to a fixed
				 * timeout.
				 */
				assert_wait(0, TRUE);
				thread_set_timeout(vm_pageout_burst_wait);
				vm_page_unlock_queues();
				thread_block();
				continue;
			}
		}

		/*
		 *	If it's being used, merely reactivate.
		 */

		if (pmap_is_referenced(m->phys_addr)) {
			vm_page_activate(m);
			vm_stat.reactivations++;
			vm_page_unlock_queues();
			continue;
		}

		/*
		 *	Try to lock object; since we've got the
		 *	page queues lock, we can only try for this one.
		 */
		if (!vm_object_lock_try(object)) {
			/*
			 *	Move page to end and continue.
			 */
			queue_remove(&vm_page_queue_inactive, m, vm_page_t, pageq);
			queue_enter(&vm_page_queue_inactive, m,	vm_page_t, pageq);
			vm_page_unlock_queues();
			continue;
		}

		/*
		 *	Remove the page from the inactive list.
		 */

		queue_remove(&vm_page_queue_inactive, m, vm_page_t, pageq);
		vm_page_inactive_count--;
		m->inactive = FALSE;
		m->busy = TRUE;

		/*
		 *	Eliminate all mappings
		 */

		pmap_page_protect(m->phys_addr, VM_PROT_NONE);
		if (!m->dirty)
			m->dirty = pmap_is_modified(m->phys_addr);

		/*
		 *	If it's clean, we can merely free the page unless
		 *	it's precious.
		 */

		if (!m->dirty && !m->precious) {
			vm_page_free(m);
			pages_moved++;
			vm_object_unlock(object);
			vm_page_unlock_queues();
			continue;
		}

		vm_page_unlock_queues();

		/*
		 *	If there is no memory object for the page, create
		 *	one and hand it to the default pager.
		 *	[First try to collapse, so we don't create
		 *	one unnecessarily.]
		 */

		if (!object->pager_initialized)
			vm_object_collapse(object);
		if (!object->pager_initialized)
			vm_object_pager_create(object);

		m->busy = TRUE;
		vm_pageout_page(m, FALSE, TRUE);	/* flush it */
		vm_object_unlock(object);
		pages_moved++;
		burst_count++;
	}

	/*
	 *	Compute the page shortage.  If we are still very low on memory
	 *	be sure that we will move a minimal number of pages from
	 *	active to inactive.
	 */

	page_shortage = vm_page_inactive_target - vm_page_inactive_count;

	if ((page_shortage <= 0) && (pages_moved == 0))
		page_shortage = 1;

	while (page_shortage > 0) {
		/*
		 *	Move some more pages from active to inactive.
		 */

		if (queue_empty(&vm_page_queue_active)) {
			break;
		}
		m = (vm_page_t) queue_first(&vm_page_queue_active);
		vm_page_deactivate(m);
		page_shortage--;
	}

	vm_page_unlock_queues();
}

task_t	pageout_task;

/*
 *	vm_pageout is the high level pageout daemon.
 */

void vm_pageout()
{
	int		free_after_reserve;
	int		target_less_min;
	int		s;

	pageout_task = current_task();
	pageout_task->kernel_vm_space = TRUE;
	pageout_task->kernel_ipc_space = TRUE;
	pageout_task->ipc_privilege = TRUE;
	current_thread()->vm_privilege = TRUE;

	(void) spl0();

	/*
	 *	Initialize some paging parameters.
	 */

#ifndef	VM_PAGE_FREE_RESERVED
#define	VM_PAGE_FREE_RESERVED			15
#endif	VM_PAGE_FREE_RESERVED
	if (vm_page_free_reserved == 0)
		vm_page_free_reserved = VM_PAGE_FREE_RESERVED;

#ifndef	VM_PAGEOUT_RESERVED_EXTERNAL
#define	VM_PAGEOUT_RESERVED_EXTERNAL(reserve)	((reserve) - 10)
#endif	VM_PAGEOUT_RESERVED_EXTERNAL
	if (vm_pageout_reserved_external == 0)
		vm_pageout_reserved_external =
			VM_PAGEOUT_RESERVED_EXTERNAL(vm_page_free_reserved);

#ifndef	VM_PAGEOUT_RESERVED_INTERNAL
#define	VM_PAGEOUT_RESERVED_INTERNAL(reserve)	((reserve) - 5)
#endif	VM_PAGEOUT_RESERVED_INTERNAL
	if (vm_pageout_reserved_internal == 0)
		vm_pageout_reserved_internal =
			VM_PAGEOUT_RESERVED_INTERNAL(vm_page_free_reserved);

	free_after_reserve = vm_page_free_count - vm_page_free_reserved;

#ifndef	VM_PAGE_FREE_MIN
#define	VM_PAGE_FREE_MIN(free)	(10 + (free) / 100)
#endif	VM_PAGE_FREE_MIN
	if (vm_page_free_min == 0)
		vm_page_free_min = vm_page_free_reserved +
			VM_PAGE_FREE_MIN(free_after_reserve);

#ifndef	VM_PAGE_FREE_TARGET
#define	VM_PAGE_FREE_TARGET(free)	(15 + (free) / 80)
#endif	VM_PAGE_FREE_TARGET
	if (vm_page_free_target == 0)
		vm_page_free_target = vm_page_free_reserved +
			VM_PAGE_FREE_TARGET(free_after_reserve);

	/*
	 *	The default inactive target is rather high.
	 *	A machine that must simulate reference bits should
	 *	choose a small inactive target.
	 */

#ifndef	VM_PAGE_INACTIVE_TARGET
#define	VM_PAGE_INACTIVE_TARGET(free)	((free) * 2 / 3)
#endif	VM_PAGE_INACTIVE_TARGET
	if (vm_page_inactive_target == 0)
		vm_page_inactive_target = 
			VM_PAGE_INACTIVE_TARGET(free_after_reserve);

 	if (vm_page_free_target <= vm_page_free_min)
		vm_page_free_target = vm_page_free_min + 1;

	target_less_min = vm_page_free_target - vm_page_free_min;
	if (vm_page_inactive_target <= target_less_min)
		vm_page_inactive_target = target_less_min + 1;

	/*
	 *	The pageout daemon is never done, so loop
	 *	forever.
	 */

	s = splimp();
	simple_lock(&vm_page_queue_free_lock);
	while (TRUE) {
		if (vm_page_free_wanted)
			simple_unlock(&vm_page_queue_free_lock);
		 else
			thread_sleep((int) &vm_page_free_wanted,
				     simple_lock_addr(vm_page_queue_free_lock),
				     FALSE);
		splx(s);
		vm_pageout_scan();
		s = splimp();
		simple_lock(&vm_page_queue_free_lock);
	}
}
