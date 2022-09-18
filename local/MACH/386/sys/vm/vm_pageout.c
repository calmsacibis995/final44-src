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
#include <mach_xp.h>
#include <mach_pagemap.h>

#if	MACH_XP
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

int	vm_pageout_internal_only = 0;

int	vm_pageout_burst_max = 10;
int	vm_pageout_burst_wait = 5;

boolean_t	vm_pageout_reactivate_dirty_pages = TRUE;

/*
 *	Routine:	vm_pageout_page
 *	Purpose:
 *		Causes the specified page to be written back to
 *		its pager.  The page in question is not freed here,
 *		but will be freed by the pager when it is done.
 *		The page will be written regardless whether it
 *		is marked as clean.
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
void		vm_pageout_page(m, initial)
	vm_page_t	m;
	boolean_t	initial;
{
	vm_object_t	new_object;
	vm_object_t	old_object = m->object;
	vm_offset_t	paging_offset = m->offset + old_object->paging_offset;
	kern_return_t	rc;
	auto
	vm_page_t	holding_page;

	XPR(XPR_VM_PAGEOUT, ("vm_pageout_page: begin %x %x", m, initial));
	if (m->busy)
		panic("vm_pageout_page: busy page");

	/*
	 *	In order to create a new object, we must unlock
	 *	the old object; before doing so, we mark this page
	 *	busy (to prevent pagein) and increment paging_in_progress
	 *	(to prevent object termination).
	 */

	vm_object_paging_begin(old_object);
	m->busy = TRUE;
	vm_object_unlock(old_object);

	/*
	 *	Create a place-holder page where the old one was, to prevent
	 *	anyone from attempting to page in this page while we're unlocked.
	 */

	holding_page = (vm_page_t) zalloc(vm_page_fictitious_zone);

	vm_object_lock(old_object);
	vm_page_remove(m);
	PAGE_WAKEUP(m);

	vm_page_init(holding_page, old_object, m->offset, (vm_offset_t) 0);
	holding_page->fictitious = TRUE;

	/*
	 *	Record that this page has been written out
	 */

#if	MACH_PAGEMAP
	vm_external_state_set(old_object->existence_info,
				m->offset,
				VM_EXTERNAL_STATE_EXISTS);
#endif	MACH_PAGEMAP

	vm_object_unlock(old_object);

	/*
	 *	Allocate a new object into which we can put the page.
	 *
	 *	If the old object was internal, then we shouldn't
	 *	ever page this out.
	 */

	new_object = vm_object_allocate(PAGE_SIZE);
	vm_object_lock(new_object);

	/*
	 *	Move this page into to the new object
	 */

	vm_page_insert(m, new_object, 0);
	m->dirty = TRUE;

	/*
	 *	Put the old page on the pageout queues; if a bogus
	 *	user-supplied pager fails to release the page, it will
	 *	get paged out again to the default pager.
	 *
	 *	Note that pages written to the default memory manager
	 *	must be wired down.
	 */

	vm_page_lock_queues();
	vm_stat.pageouts++;
	if (old_object->internal)
		m->wire_count++;
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
	 else {
		vm_page_laundry_count++;
		m->laundry = TRUE;
	}
	
	/*
	 *	Since IPC operations may block, we drop locks now.
	 *	[The placeholder page is busy, and we still have paging_in_progress
	 *	incremented.]
	 */

	vm_object_unlock(new_object);

	/*
	 *	Write the data to its pager.
	 *	Note that the data is passed by naming the new object,
	 *	not a virtual address; the pager interface has been
	 *	manipulated to use the "internal memory" data type.
	 *	[The object reference from its allocation is donated
	 *	to the eventual recipient.]
	 */

	if ((rc = (initial ? memory_object_data_initialize : memory_object_data_write)
			(old_object->pager,
			 old_object->pager_request,
			 paging_offset, (pointer_t) new_object, PAGE_SIZE))
					!= KERN_SUCCESS) {
		if (vm_pageout_debug)
			printf("vm_pageout_page: memory_object_data_write failed, %d, page 0x%x\n", rc, m);
		vm_object_deallocate(new_object);
	}

	/*
	 *	Pick back up the old object lock to clean up
	 *	and to meet exit conditions.
	 */

	vm_object_lock(old_object);
	
	/*
	 *	Free the placeholder page to permit pageins to continue
	 *	[Don't need to hold queues lock, since this page should
	 *	never get on the pageout queues!]
	 */
	vm_page_free(holding_page);
	zfree(vm_page_fictitious_zone, (vm_offset_t)holding_page);

	vm_object_paging_end(old_object);
	XPR(XPR_VM_PAGEOUT, ("vm_pageout_page: done %x %x", m, initial));
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

		if (free < vm_pageout_internal_only) {
			if (!object->internal) {
				/*
				 *	[Don't count this as a reactivation.]
				 */

				vm_page_activate(m);
				vm_page_unlock_queues();
				continue;
			}

			/*
			 *	Even then, only work until we get
			 *	to the reserved count.
			 */

			if (free < vm_page_free_reserved) {
				/* XXX If the burst_wait is computed
				 * dynamically, it would probably be
				 * wise to change this one to a fixed
				 * timeout
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

		if (pmap_is_referenced(m->phys_addr) &&
		    (!m->dirty || vm_pageout_reactivate_dirty_pages)) {
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
		 *	If it's clean, we can merely free the page.
		 */

		if (!m->dirty) {
			vm_page_free(m);
			pages_moved++;
			vm_object_unlock(object);
			vm_page_unlock_queues();
			continue;
		}

		vm_page_unlock_queues();

		/*
		 *	If there is no pager for the page, create
		 *	one and hand it to the default pager.
		 *	[First try to collapse, so we don't make
		 *	a pager unnecessarily.]
		 */

		vm_object_collapse(object);

		if (object->pager == MEMORY_OBJECT_NULL) {
			vm_object_pager_create(object);
			vm_page_lock_queues();
			vm_page_activate(m);
			vm_page_unlock_queues();

			PAGE_WAKEUP(m);
			vm_object_unlock(object);
			continue;
		}

		PAGE_WAKEUP(m);

		vm_pageout_page(m, FALSE);
		vm_object_unlock(object);
		pages_moved++;
		burst_count++;
	}

	/*
	 *	Compute the page shortage.  If we are still very low on memory
	 *	be sure that we will move a minimal amount of pages from active
	 *	to inactive.
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
#define	VM_PAGE_FREE_RESERVED			10
#endif	VM_PAGE_FREE_RESERVED
	if (vm_page_free_reserved == 0)
		vm_page_free_reserved = VM_PAGE_FREE_RESERVED;

#ifndef	VM_PAGEOUT_INTERNAL_ONLY
#define	VM_PAGEOUT_INTERNAL_ONLY(reserve)	((reserve) - 4)
#endif	VM_PAGEOUT_INTERNAL_ONLY
	if (vm_pageout_internal_only == 0)
		vm_pageout_internal_only =
			VM_PAGEOUT_INTERNAL_ONLY(vm_page_free_reserved);

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
#else	MACH_XP

#include <vm/old_pageout.c>
#endif	MACH_XP
