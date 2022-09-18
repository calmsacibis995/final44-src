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
 * $Log:	old_pageout.c,v $
 * Revision 2.7  89/04/18  21:24:37  mwyoung
 * 	THIS FILE IS DEFUNCT.  MAKE NEW IMPROVEMENTS TO THE
 * 	PAGEOUT DAEMON IN "vm/vm_pageout.c".
 * 
 * 	Old non-MACH_XP pageout daemon.  No history is relevant.
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

#include <vm/vm_page.h>
#include <vm/pmap.h>
#include <vm/vm_object.h>
#include <vm/vm_pageout.h>
#include <mach/vm_statistics.h>
#include <mach/vm_param.h>
#include <kern/thread_swap.h>
#include <vm/vm_pager.h>

int	vm_pages_needed;		/* Event on which pageout daemon sleeps */
int	vm_pageout_free_min = 0;	/* Stop pageout to wait for pagers at this free level */

int	vm_page_free_min_sanity = 40;

/*
 *	vm_pageout_scan does the dirty work for the pageout daemon.
 */
vm_pageout_scan()
{
	register vm_page_t	m;
	register int		page_shortage;
	register int		s;
	register int		pages_freed;

	/*
	 *	Only continue when we want more pages to be "free"
	 */

	s = splimp();
	simple_lock(&vm_page_queue_free_lock);
	if (vm_page_free_count < vm_page_free_target) {
		/*
		 *	See whether the physical mapping system
		 *	knows of any pages which are not being used.
		 */
		 
		simple_unlock(&vm_page_queue_free_lock);
		splx(s);
		swapout_threads();

		/*
		 *	And be sure the pmap system is updated so
		 *	we can scan the inactive queue.
		 */

		pmap_update();
	}
	else {
		simple_unlock(&vm_page_queue_free_lock);
		splx(s);
	}

	/*
	 *	Acquire the resident page system lock,
	 *	as we may be changing what's resident quite a bit.
	 */
	vm_page_lock_queues();

	/*
	 *	Start scanning the inactive queue for pages we can free.
	 *	We keep scanning until we have enough free pages or
	 *	we have scanned through the entire queue.  If we
	 *	encounter dirty pages, we start cleaning them.
	 */

	pages_freed = 0;
	m = (vm_page_t) queue_first(&vm_page_queue_inactive);
	while (!queue_end(&vm_page_queue_inactive, (queue_entry_t) m)) {
		vm_page_t	next;

		s = splimp();
		simple_lock(&vm_page_queue_free_lock);
		if (vm_page_free_count >= vm_page_free_target) {
			simple_unlock(&vm_page_queue_free_lock);
			splx(s);
			break;
		}
		simple_unlock(&vm_page_queue_free_lock);
		splx(s);

		if (m->clean) {
			next = (vm_page_t) queue_next(&m->pageq);
			if (pmap_is_referenced(VM_PAGE_TO_PHYS(m))) {
				vm_page_activate(m);
				vm_stat.reactivations++;
			}
			else {
				register vm_object_t	object;
				object = m->object;
				if (!vm_object_lock_try(object)) {
					/*
					 *	Can't lock object -
					 *	skip page.
					 */
					m = next;
					continue;
				}
				pmap_remove_all(VM_PAGE_TO_PHYS(m));
				if (pmap_is_modified(VM_PAGE_TO_PHYS(m))) {
					m->clean = FALSE;
					goto now_dirty;
				}
				vm_page_free(m);	/* will dequeue */
				pages_freed++;
				vm_object_unlock(object);
			}
			m = next;
		}
		else {
			now_dirty: ;

			/*
			 *	If a page is dirty, then it is either
			 *	being washed (but not yet cleaned)
			 *	or it is still in the laundry.  If it is
			 *	still in the laundry, then we start the
			 *	cleaning operation.
			 */

			if (m->laundry) {
				/*
				 *	Clean the page and remove it from the
				 *	laundry.
				 *
				 *	We set the busy bit to cause
				 *	potential page faults on this page to
				 *	block.
				 *
				 *	And we set pageout-in-progress to keep
				 *	the object from disappearing during
				 *	pageout.  This guarantees that the
				 *	page won't move from the inactive
				 *	queue.  (However, any other page on
				 *	the inactive queue may move!)
				 */

				register vm_object_t	object;
				register memory_object_t	pager;
				boolean_t	pageout_succeeded;

				object = m->object;
				if (!vm_object_lock_try(object)) {
					/*
					 *	Skip page if we can't lock
					 *	its object
					 */
					m = (vm_page_t) queue_next(&m->pageq);
					continue;
				}

				pmap_remove_all(VM_PAGE_TO_PHYS(m));
				m->busy = TRUE;
				vm_stat.pageouts++;

				/*
				 *	Try to collapse the object before
				 *	making a pager for it.  We must
				 *	unlock the page queues first.
				 */
				vm_page_unlock_queues();

				vm_object_collapse(object);

				object->paging_in_progress++;
				vm_object_unlock(object);

				/*
				 *	Do a wakeup here in case the following
				 *	operations block.
				 */
				thread_wakeup((int) &vm_page_free_count);

				/*
				 *	If there is no pager for the page,
				 *	use the default pager.  If there's
				 *	no place to put the page at the
				 *	moment, leave it in the laundry and
				 *	hope that there will be paging space
				 *	later.
				 */

				if ((pager = object->pager) == MEMORY_OBJECT_NULL) {
					pager = vm_pager_allocate(object->size);
					if (pager != MEMORY_OBJECT_NULL) {
						vm_object_setpager(object,
							pager, 0, FALSE);
					}
				}

				pageout_succeeded = FALSE;
				if (pager != MEMORY_OBJECT_NULL) {
				    if (vm_pager_put(pager, m) == PAGER_SUCCESS) {
					pageout_succeeded = TRUE;
				    }
				}

				vm_object_lock(object);
				vm_page_lock_queues();
				/*
				 *	If page couldn't be paged out, then
				 *	reactivate the page so it doesn't
				 *	clog the inactive list.  (We will try
				 *	paging out it again later).
				 */
				next = (vm_page_t) queue_next(&m->pageq);
				if (pageout_succeeded)
					m->laundry = FALSE;
				else
					vm_page_activate(m);

				pmap_clear_reference(VM_PAGE_TO_PHYS(m));
				m->busy = FALSE;
				PAGE_WAKEUP(m);

				object->paging_in_progress--;
				thread_wakeup((int) object);
				vm_object_unlock(object);
				m = next;
			}
			else
				m = (vm_page_t) queue_next(&m->pageq);
		}
	}
	
	/*
	 *	Compute the page shortage.  If we are still very low on memory
	 *	be sure that we will move a minimal amount of pages from active
	 *	to inactive.
	 */

	page_shortage = vm_page_inactive_target - vm_page_inactive_count;
	page_shortage -= vm_page_free_count;

	if ((page_shortage <= 0) && (pages_freed == 0))
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

/*
 *	vm_pageout is the high level pageout daemon.
 */

void vm_pageout()
{
	(void) spl0();

	/*
	 *	Initialize some paging parameters.
	 */

	if (vm_page_free_min == 0) {
		vm_page_free_min = vm_page_free_count / 20;
		if (vm_page_free_min < 3)
			vm_page_free_min = 3;

		if (vm_page_free_min > vm_page_free_min_sanity)
			vm_page_free_min = vm_page_free_min_sanity;
	}

	if (vm_page_free_reserved == 0) {
		if ((vm_page_free_reserved = vm_page_free_min / 2) < 10)
			vm_page_free_reserved = 10;
	}
	if (vm_pageout_free_min == 0) {
		if ((vm_pageout_free_min = vm_page_free_reserved / 2) > 10)
			vm_pageout_free_min = 10;
	}

	if (vm_page_free_target == 0)
		vm_page_free_target = (vm_page_free_min * 4) / 3;

	if (vm_page_inactive_target == 0)
		vm_page_inactive_target = vm_page_free_min * 2;

	if (vm_page_free_target <= vm_page_free_min)
		vm_page_free_target = vm_page_free_min + 1;

	if (vm_page_inactive_target <= vm_page_free_target)
		vm_page_inactive_target = vm_page_free_target + 1;

	/*
	 *	The pageout daemon is never done, so loop
	 *	forever.
	 */

	simple_lock(&vm_pages_needed_lock);
	while (TRUE) {
		thread_sleep((int) &vm_pages_needed,
			     simple_lock_addr(vm_pages_needed_lock),
			     FALSE);
		vm_pageout_scan();
		simple_lock(&vm_pages_needed_lock);
		thread_wakeup((int) &vm_page_free_count);
	}
}

