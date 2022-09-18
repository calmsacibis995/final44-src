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
 * $Log:	vm_fault.c,v $
 * Revision 2.23  90/09/10  21:10:02  mrt
 * 	Added per-map statistics to support the EVENTS flavor of
 * 	task_info, which wasn't implemented and now is.
 * 	vm_fault_page() now takes an extra parameter which is
 * 	a vm_statistics structure where to cherge the fault to.
 * 	[90/09/10  17:37:29  af]
 * 
 * Revision 2.22  90/07/03  16:56:25  mrt
 * 	Add flush argument to vm_pageout_page.
 * 	[90/06/11            dlb]
 * 
 * Revision 2.21  89/12/22  15:55:31  rpd
 * 	Assert that page is not busy before marking it busy.
 * 	[89/12/21            dlb]
 * 	Check for absent as well as busy before freeing a page when
 * 	pagein fails.
 * 	[89/12/13            dlb]
 * 	Change all occurrences of PAGE_WAKEUP to PAGE_WAKEUP_DONE to
 * 	reflect the fact that they clear the busy flag.  See
 * 	vm/vm_page.h.  Add PAGE_WAKEUP_DONE to vm_fault_unwire().
 * 	[89/12/13            dlb]
 * 
 * 	Break out of fault loop after zero filling in response to
 * 	finding an absent page; the zero filled page was either absent
 * 	or newly allocated and so can't be page locked.
 * 	[89/12/12            dlb]
 * 
 * 	Must recheck page to object relationship before freeing
 * 	page if pagein fails.
 * 	[89/12/11            dlb]
 * 
 * Revision 2.20  89/10/19  13:16:47  af
 * 	Consider paging_offset when looking at external page state.
 * 	[89/10/16  15:31:17  af]
 * 
 * Revision 2.19  89/10/10  11:10:34  mwyoung
 * 	Eliminate non-XP code.
 * 	[89/10/10 mwyoung]
 * 
 * 	Eliminate vm_fault_copy_entry().
 * 	Add vm_fault_copy(), for overwriting a permanent object.
 * 	[89/07/28  16:14:27  mwyoung]
 * 
 * 	Only require read access for the original page once past the
 * 	top-level object... it will only be copied to a new page.
 * 	[89/05/19  17:45:05  mwyoung]
 * 
 * 	Change call to vm_fault_wire() to call vm_fault_wire_fast()
 * 	instead in vm_fault_copy_entry().
 * 	[89/05/04            mwyoung]
 * 
 * 	Also remove "absent" page from pageout queues before zero-filling.
 * 	[89/05/01            mwyoung]
 * 	When transforming an "absent" page into a placeholder page,
 * 	remove it from the page queues.
 * 	[89/04/22            mwyoung]
 * 
 * Revision 2.18  89/10/03  19:28:50  rpd
 * 	Fixed usage of must_be_resident in vm_fault_page when
 * 	descending down shadow chain.  Fixed corresponding
 * 	assertion in vm_fault.
 * 	[89/10/02  16:17:20  rpd]
 * 
 * 	Use vme_start, vme_end when accessing map entries.
 * 	[89/08/31  21:10:05  rpd]
 * 
 * 	Removed vm_fault_copy_entry; it was entirely bogus.
 * 	[89/08/31  19:28:57  rpd]
 * 
 * 	An optimization from NeXT:  when processing a COW fault
 * 	in vm_fault_page, vm_page_deactivate the old page.
 * 	[89/08/19  23:37:48  rpd]
 * 
 * Revision 2.17  89/05/06  02:58:43  rpd
 * 	Picked up fix from mwyoung for a COW-triggered page leak:
 * 	when copying from a copy-on-write page, activate the page
 * 	instead of deactivating it.  Also picked up two innocuous
 * 	VM_PAGE_QUEUES_REMOVE() additions in the "unavailable page" code.
 * 	[89/05/06            rpd]
 * 	Fixed the call to vm_fault_wire_fast in vm_fault_copy_entry.
 * 	[89/05/05            rpd]
 * 
 * Revision 2.16  89/04/18  21:25:12  mwyoung
 * 	Recent history:
 * 		Limit the number of outstanding page requests for
 * 		 non-internal objects.
 * 		Use hint to determine whether a page of temporary memory may
 * 		 have been written to backing storage.
 * 	History condensation:
 * 		Separate fault handling into separate routine (mwyoung).
 * 		Handle I/O errors (dbg, mwyoung).
 * 		Use map_verify technology (mwyoung).
 * 		Allow faults to be interrupted (mwyoung).
 * 		Optimized wiring code (dlb).
 * 		Initial external memory management (mwyoung, bolosky).
 * 		Original version (avie, mwyoung, dbg).
 * 
 */
/*
 *	File:	vm_fault.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Page fault handling module.
 */
#include <mach_pagemap.h>

#include <vm/vm_fault.h>
#include <mach/kern_return.h>
#include <mach/message.h>	/* for error codes */
#include <kern/thread.h>
#include <kern/sched_prim.h>
#include <vm/vm_map.h>
#include <vm/vm_object.h>
#include <vm/vm_page.h>
#include <vm/pmap.h>
#include <mach/vm_statistics.h>
#include <vm/vm_pageout.h>
#include <mach/vm_param.h>
#include <mach/message.h>
#include <mach/memory_object.h>
#include <mach/memory_object_user.h>	/* For memory_object_data_{request,unlock} */

#include <kern/macro_help.h>
#include <kern/xpr.h>

int		VM_OBJECT_ABSENT_MAX = 4;

int		vm_fault_debug = 0;

boolean_t	vm_fault_dirty_handling = FALSE;
boolean_t	vm_fault_interruptible = TRUE;

#include <kern/macro_help.h>

/*
 *	Routine:	vm_fault_page
 *	Purpose:
 *		Find the resident page for the virtual memory
 *		specified by the given virtual memory object
 *		and offset.
 *	Additional arguments:
 *		The required permissions for the page is given
 *		in "fault_type".  Desired permissions are included
 *		in "protection".
 *
 *		If the desired page is known to be resident (for
 *		example, because it was previously wired down), asserting
 *		the "unwiring" parameter will speed the search.
 *
 *		If the operation can be interrupted (by thread_abort
 *		or thread_terminate), then the "interruptible"
 *		parameter should be asserted.
 *
 *	Results:
 *		The page containing the proper data is returned
 *		in "result_page".
 *
 *	In/out conditions:
 *		The source object must be locked and referenced,
 *		and must donate one paging reference.  The reference
 *		is not affected.  The paging reference and lock are
 *		consumed.
 *
 *		If the call succeeds, the object in which "result_page"
 *		resides is left locked and holding a paging reference.
 *		If this is not the original object, a busy page in the
 *		original object is returned in "top_page", to prevent other
 *		callers from pursuing this same data, along with a paging
 *		reference for the original object.  The "top_page" should
 *		be destroyed when this guarantee is no longer required.
 *		The "result_page" is also left busy, and is removed from
 *		any pageout queues.
 */
vm_fault_return_t vm_fault_page(object, offset,
				fault_type, must_be_resident, interruptible,
				protection,
				result_page, top_page,
				vm_meter)
 /* Arguments: */
	register
	vm_object_t	object;		/* Object to begin search */
	register
	vm_offset_t	offset;		/* Offset into object */
	vm_prot_t	fault_type;	/* What access is requested */
	boolean_t	must_be_resident;/* Must page be resident? */
	boolean_t	interruptible;	/* May fault be interrupted? */
 /* Modifies in place: */
	vm_prot_t	*protection;	/* Protection for mapping */
 /* Returns: */
	vm_page_t	*result_page;	/* Page found, if successful */
	vm_page_t	*top_page;	/* Page in top object, if
					 * not result_page.
					 */
/* Updates: */
	vm_statistics_t	 vm_meter;	/* Who to charge this fault to */
{
	register
	vm_page_t	m;
	vm_object_t	first_object = object;
	vm_offset_t	first_offset = offset;
	vm_page_t	first_m;
	vm_object_t	next_object;
	vm_object_t	copy_object;
	boolean_t	look_for_page;
	vm_prot_t	access_required = fault_type;

	vm_stat.faults++;		/* needs lock XXX */
	vm_meter->faults++;

/*
 *	Recovery actions
 */
#define RELEASE_PAGE(m)					\
	MACRO_BEGIN					\
	PAGE_WAKEUP_DONE(m);				\
	vm_page_lock_queues();				\
	vm_page_activate(m);				\
	vm_page_unlock_queues();			\
	MACRO_END

#define UNLOCK_THINGS					\
	MACRO_BEGIN					\
	vm_object_paging_end(object);			\
	vm_object_unlock(object);			\
	if (object != first_object) {			\
		vm_object_lock(first_object);		\
		VM_PAGE_FREE(first_m);			\
		vm_object_paging_end(first_object);	\
		vm_object_unlock(first_object);		\
	}						\
	MACRO_END

	XPR(XPR_VM_FAULT, ("vm_fault_page: object %x, offset %x",
		object, offset));

	first_m = VM_PAGE_NULL;

	if (vm_fault_dirty_handling) {
		/*
		 *	If we aren't asking for write permission,
		 *	then don't give it away.  We're using write
		 *	faults to set the dirty bit.
		 */
		if (!(fault_type & VM_PROT_WRITE))
			*protection &= ~VM_PROT_WRITE;
	}

	if (!vm_fault_interruptible)
		interruptible = FALSE;

	/*
	 *	INVARIANTS (through entire routine):
	 *
	 *	1)	At all times, we must either have the object
	 *		lock or a busy page in some object to prevent
	 *		some other thread from trying to bring in
	 *		the same page.
	 *
	 *		Note that we cannot hold any locks during the
	 *		pager access or when waiting for memory, so
	 *		we use a busy page then.
	 *
	 *		Note also that we aren't as concerned about
	 *		more than one thread attempting to pager_data_unlock
	 *		the same page at once, so we don't hold the page
	 *		as busy then, but do record the highest unlock
	 *		value so far.  [Unlock requests may also be delivered
	 *		out of order.]
	 *
	 *	2)	Once we have a busy page, we must remove it from
	 *		the pageout queues, so that the pageout daemon
	 *		will not grab it away.
	 *
	 *	3)	To prevent another thread from racing us down the
	 *		shadow chain and entering a new page in the top
	 *		object before we do, we must keep a busy page in
	 *		the top object while following the shadow chain.
	 *
	 *	4)	We must increment paging_in_progress on any object
	 *		for which we have a busy page, to prevent
	 *		vm_object_collapse from removing the busy page
	 *		without our noticing.
	 */

	/*
	 *	Search for the page at object/offset.
	 */

	object = first_object;
	offset = first_offset;

	/*
	 *	See whether this page is resident
	 */

	while (TRUE) {
		m = vm_page_lookup(object, offset);
		if (m != VM_PAGE_NULL) {
			/*
			 *	If the page is in error, give up now.
			 */

			if (m->error) {
				VM_PAGE_FREE(m);
				UNLOCK_THINGS;
				return(VM_FAULT_MEMORY_ERROR);
			}

			/*
			 *	If the page has been requested, but the
			 *	requestor has abandoned it, we can claim
			 *	responsibility for the page.
			 */

			if (m->fictitious) {
				/* XXXO Not yet implemented.
				 * Not required for correctness.
				 */
			}

			/*
			 *	If the page is being brought in,
			 *	wait for it and then retry.
			 *
			 *	A possible optimization: if the page is known
			 *	to be resident, we can ignore pages that are absent
			 *	(regardless whether they're busy).
			 */
			if (m->busy) {
				kern_return_t	wait_result;

				PAGE_ASSERT_WAIT(m, interruptible);
				vm_object_unlock(object);
				thread_block();
				wait_result = current_thread()->wait_result;
				vm_object_lock(object);
				if (wait_result == THREAD_RESTART) {
					UNLOCK_THINGS;
					return(VM_FAULT_RETRY);
				}
				if (wait_result != THREAD_AWAKENED) {
					/*
					 *	Our fault was interrupted.
					 *
					 *	A page may still be dedicated
					 *	to the request that we have made.
					 *	We cannot free that page now,
					 *	else we might issue another
					 *	request for the same data.
					 *
					 *	The number of absent pages is
					 *	limited (before issuing a request)
					 *	to prevent an errant memory manager
					 *	from consuming too much memory.
					 *
					 *	To further reduce the memory
					 *	devoted to the aborted page fault,
					 *	we can install a fictitious page
					 *	in place of the real page.
					 *	XXXO This isn't done yet.
					 */

#ifdef	XXXO
					m = vm_page_lookup(object, offset);
					if ((m != VM_PAGE_NULL) &&
					     m->busy && m->absent) {
					     	/* Replace with a fictitious page */
					}
#endif	XXXO
					UNLOCK_THINGS;
					return(VM_FAULT_INTERRUPTED);
				}
				continue;
			}

			/*
			 *	If the page isn't busy, but is absent,
			 *	then it was deemed "unavailable".
			 */

			if (m->absent) {
				/*
				 * Remove the non-existent page (unless it's
				 * in the top object) and move on down to the
				 * next object (if there is one).
				 */
				offset += object->shadow_offset;
				access_required = VM_PROT_READ;
				next_object = object->shadow;
				if (next_object == VM_OBJECT_NULL) {
					assert(!must_be_resident);

					/*
					 * Absent page at bottom of shadow
					 * chain; zero fill the page we left
					 * busy in the first object, and flush
					 * the absent page.
					 */
					if (object != first_object) {
						VM_PAGE_FREE(m);
						vm_object_paging_end(object);
						vm_object_unlock(object);
						object = first_object;
						offset = first_offset;
						m = first_m;
						first_m = VM_PAGE_NULL;
						vm_object_lock(object);
					} else {
						m->absent = FALSE;
						m->busy = TRUE;
						vm_object_absent_release(object);

						vm_page_lock_queues();
						VM_PAGE_QUEUES_REMOVE(m);
						vm_page_unlock_queues();
					}

					assert(	(first_m == VM_PAGE_NULL) &&
						(m->object == object) &&
						(!m->absent) &&	(m->busy)
						);

					assert(!m->active && !m->inactive);

					/*
					 *  Drop the lock while zero filling
					 *  page.  Then break because this
					 *  is the page we wanted.  Checking
					 *  the page lock is a waste of time;
					 *  this page was either absent or
					 *  newly allocated -- in both cases
					 *  it can't be page locked by a pager.
					 */
					vm_object_unlock(object);

					vm_page_zero_fill(m);
					vm_meter->zero_fill_count++;

					vm_object_lock(object);
					break;
				} else {
					if (must_be_resident) {
						vm_object_paging_end(object);
					} else if (object != first_object) {
						vm_object_paging_end(object);
						VM_PAGE_FREE(m);
					} else {
						first_m = m;
						m->absent = FALSE;
						vm_object_absent_release(object);
						m->busy = TRUE;

						vm_page_lock_queues();
						VM_PAGE_QUEUES_REMOVE(m);
						vm_page_unlock_queues();
					}
					vm_object_lock(next_object);
					vm_object_unlock(object);
					object = next_object;
					vm_object_paging_begin(object);
					continue;
				}
			}

			/*
			 *	If the desired access to this page has
			 *	been locked out, request that it be unlocked.
			 */

			if (access_required & m->page_lock) {
				if ((access_required & m->unlock_request) != access_required) {
					vm_prot_t	new_unlock_request;
					kern_return_t	rc;
					
					if (!object->pager_ready) {
						vm_object_assert_wait(object,
							VM_OBJECT_EVENT_PAGER_READY,
							interruptible);
						UNLOCK_THINGS;
						thread_block();
						return((current_thread()->wait_result != THREAD_AWAKENED) ?
							VM_FAULT_INTERRUPTED :
							VM_FAULT_RETRY);
					}

					new_unlock_request = m->unlock_request =
						(access_required | m->unlock_request);
					vm_object_unlock(object);
					if ((rc = memory_object_data_unlock(
						object->pager,
						object->pager_request,
						offset + object->paging_offset,
						PAGE_SIZE,
						new_unlock_request))
					     != KERN_SUCCESS) {
					     	printf("vm_fault: pager_data_unlock failed\n");
						vm_object_lock(object);
						UNLOCK_THINGS;
						return((rc == SEND_INTERRUPTED) ?
							VM_FAULT_INTERRUPTED :
							VM_FAULT_MEMORY_ERROR);
					}
					vm_object_lock(object);
					continue;
				}

				PAGE_ASSERT_WAIT(m, interruptible);
				UNLOCK_THINGS;
				thread_block();
				return((current_thread()->wait_result != THREAD_AWAKENED) ?
					VM_FAULT_INTERRUPTED :
					VM_FAULT_RETRY);
			}

			/*
			 *	Remove the page from the pageout daemon's
			 *	reach while we play with it.
			 */

			vm_page_lock_queues();
			if (m->inactive) {
				vm_stat.reactivations++;
				vm_meter->reactivations++;
			}

			VM_PAGE_QUEUES_REMOVE(m);
			vm_page_unlock_queues();

			/*
			 *	Mark page busy for other threads.
			 */
			assert(!m->busy);
			m->busy = TRUE;
			assert(!m->absent);
			break;
		}

		look_for_page =
			(object->pager_created)
#if	MACH_PAGEMAP
			&& (vm_external_state_get(object->existence_info, offset + object->paging_offset) !=
			 VM_EXTERNAL_STATE_ABSENT)
#endif	MACH_PAGEMAP
			 ;

		if ((look_for_page || (object == first_object))
				 && !must_be_resident) {
			/*
			 *	Allocate a new page for this object/offset
			 *	pair.
			 */

			m = vm_page_alloc(object, offset);

			if (m == VM_PAGE_NULL) {
				UNLOCK_THINGS;
				return(VM_FAULT_MEMORY_SHORTAGE);
			}
		}

		if (look_for_page && !must_be_resident) {
			kern_return_t	rc;

			/*
			 *	If the memory manager is not ready, we
			 *	cannot make requests.
			 */
			if (!object->pager_ready) {
				vm_object_assert_wait(object,
					VM_OBJECT_EVENT_PAGER_READY,
					interruptible);
				VM_PAGE_FREE(m);
				UNLOCK_THINGS;
				thread_block();
				return((current_thread()->wait_result != THREAD_AWAKENED) ?
					VM_FAULT_INTERRUPTED :
					VM_FAULT_RETRY);
			}

			/*
			 *	If there are too many outstanding page requests
			 *	pending on this object, we wait for them
			 *	to be resolved now.
			 */

			if (!object->internal &&
			    (object->absent_count > VM_OBJECT_ABSENT_MAX)) {
				vm_object_absent_assert_wait(object, interruptible);
				VM_PAGE_FREE(m);
				UNLOCK_THINGS;
				thread_block();
				return((current_thread()->wait_result != THREAD_AWAKENED) ?
					VM_FAULT_INTERRUPTED :
					VM_FAULT_RETRY);
			}

			/*
			 *	Indicate that the page is waiting for data from
			 *	the memory manager.
			 *
			 *	Record our identity in the page, so we can
			 *	correctly handle it if we abort our fault.
			 */

			m->absent = TRUE;
			object->absent_count++;

			/*
			 *	We have a busy page, so we can
			 *	release the object lock.
			 */
			vm_object_unlock(object);

			/*
			 *	Call the memory manager to retrieve the data.
			 */

			XPR(XPR_VM_FAULT, ("vm_fault: requesting data, object 0x%x, offset 0x%x",
				object, m->offset));

			vm_stat.pageins++;
			vm_meter->pageins++;

			if ((rc = memory_object_data_request(object->pager, 
				object->pager_request,
				m->offset + object->paging_offset, 
				PAGE_SIZE, access_required)) != KERN_SUCCESS) {
				if (rc != SEND_INTERRUPTED)
					printf("%s(0x%x, 0x%x, 0x%x, 0x%x, 0x%x) failed, %d\n",
						"pager_data_request",
						object->pager,
						object->pager_request,
						m->offset + object->paging_offset, 
						PAGE_SIZE, access_required, rc);
				/*
				 *	Don't want to leave a busy page around,
				 *	but the data request may have blocked,
				 *	so check if it's still there and busy.
				 */
				vm_object_lock(object);
				if (m == vm_page_lookup(object,offset) &&
				    m->absent && m->busy)
					VM_PAGE_FREE(m);
				UNLOCK_THINGS;
				return((rc == SEND_INTERRUPTED) ?
					VM_FAULT_INTERRUPTED :
					VM_FAULT_MEMORY_ERROR);
			}
			
			/*
			 * Retry with same object/offset, since new data may
			 * be in a different page (i.e., m is meaningless at
			 * this point).
			 */
			vm_object_lock(object);
			continue;
		}

		/*
		 * For the XP system, the only case in which we get here is if
		 * object has no pager (or unwiring).  If the pager doesn't
		 * have the page this is handled in the m->absent case above
		 * (and if you change things here you should look above).
		 */
		if (object == first_object)
			first_m = m;

		/*
		 *	Move on to the next object.  Lock the next
		 *	object before unlocking the current one.
		 */

		offset += object->shadow_offset;
		access_required = VM_PROT_READ;
		next_object = object->shadow;
		if (next_object == VM_OBJECT_NULL) {
			assert(!must_be_resident);

			/*
			 *	If there's no object left, fill the page
			 *	in the top object with zeros.
			 */
			if (object != first_object) {
				vm_object_paging_end(object);
				vm_object_unlock(object);

				object = first_object;
				offset = first_offset;
				m = first_m;
				vm_object_lock(object);
			}

			first_m = VM_PAGE_NULL;

			assert(m->busy && !m->absent &&
				!m->active && !m->inactive);

			vm_object_unlock(object);
			vm_page_zero_fill(m);
			vm_meter->zero_fill_count++;
			vm_object_lock(object);
			break;
		}
		else {
			vm_object_lock(next_object);
			if ((object != first_object) || must_be_resident)
				vm_object_paging_end(object);
			vm_object_unlock(object);
			object = next_object;
			vm_object_paging_begin(object);
		}
	}

	/*
	 *	PAGE HAS BEEN FOUND.
	 *
	 *	This page (m) is:
	 *		busy, so that we can play with it;
	 *		not absent, so that nobody else will fill it;
	 *		ineligible for pageout;
	 *
	 *	The top-level page (first_m) is:
	 *		VM_PAGE_NULL if the page was found in the
	 *		 top-level object;
	 *		busy, not absent, and ineligible for pageout.
	 *
	 *	The current object (object) is locked.  A paging
	 *	reference is held for the current and top-level
	 *	objects.
	 */

#if	EXTRA_ASSERTIONS
	assert(m->busy && !m->absent && !m->active && !m->inactive);
	assert((first_m == VM_PAGE_NULL) ||
		(first_m->busy && !first_m->absent &&
		 !first_m->active && !first_m->inactive));
#endif	EXTRA_ASSERTIONS

	/*
	 *	If the page is being written, but isn't
	 *	already owned by the top-level object,
	 *	we have to copy it into a new page owned
	 *	by the top-level object.
	 */

	if (object != first_object) {
	    	/*
		 *	We only really need to copy if we
		 *	want to write it.
		 */

	    	if (fault_type & VM_PROT_WRITE) {
			assert(!must_be_resident);

			/*
			 *	If we try to collapse first_object at this
			 *	point, we may deadlock when we try to get
			 *	the lock on an intermediate object (since we
			 *	have the bottom object locked).  We can't
			 *	unlock the bottom object, because the page
			 *	we found may move (by collapse) if we do.
			 *
			 *	Instead, we first copy the page.  Then, when
			 *	we have no more use for the bottom object,
			 *	we unlock it and try to collapse.
			 *
			 *	Note that we copy the page even if we didn't
			 *	need to... that's the breaks.
			 */

		    	/*
			 *	We already have an empty page in
			 *	first_object - use it.
			 */

			vm_object_unlock(object);
			vm_page_copy(m, first_m);
			vm_object_lock(object);

			assert(!first_m->absent);

			/*
			 *	If another map is truly sharing this
			 *	page with us, we have to flush all
			 *	uses of the original page, since we
			 *	can't distinguish those which want the
			 *	original from those which need the
			 *	new copy.
			 *
			 *	XXXO If we know that only one map has
			 *	access to this page, then we could
			 *	avoid the pmap_page_protect() call.
			 */

			vm_page_lock_queues();
			vm_page_activate(m);
			vm_page_deactivate(m);
			pmap_page_protect(m->phys_addr, VM_PROT_NONE);
			vm_page_unlock_queues();

			/*
			 *	We no longer need the old page or object.
			 */
			PAGE_WAKEUP_DONE(m);
			vm_object_paging_end(object);
			vm_object_unlock(object);

			/*
			 *	Only use the new page below...
			 */

			vm_stat.cow_faults++;
			vm_meter->cow_faults++;
			m = first_m;
			object = first_object;
			offset = first_offset;
			first_m = VM_PAGE_NULL;

			/*
			 *	Now that we've gotten the copy out of the
			 *	way, let's try to collapse the top object.
			 */
			vm_object_lock(object);
			/*
			 *	But we have to play ugly games with
			 *	paging_in_progress to do that...
			 */
			vm_object_paging_end(object);
			vm_object_collapse(object);
			vm_object_paging_begin(object);
		}
		else {
		    	*protection &= (~VM_PROT_WRITE);
		}
	} else while ((copy_object = first_object->copy) != VM_OBJECT_NULL) {
		vm_offset_t	copy_offset;
		vm_page_t	copy_m;

		/*
		 *	If the page is being written, but hasn't been
		 *	copied to the copy-object, we have to copy it there.
		 */

		if ((fault_type & VM_PROT_WRITE) == 0) {
			*protection &= ~VM_PROT_WRITE;
			break;
		}

		/*
		 *	If the page was guaranteed to be resident,
		 *	we must have already performed the copy.
		 */

		if (must_be_resident)
			break;

		/*
		 *	Try to get the lock on the copy_object.
		 */
		if (!vm_object_lock_try(copy_object)) {
			vm_object_unlock(object);
			/* should spin a bit here... */
			vm_object_lock(object);
			continue;
		}

		/*
		 *	Make another reference to the copy-object,
		 *	to keep it from disappearing during the
		 *	copy.
		 */
		assert(copy_object->ref_count > 0);
		copy_object->ref_count++;

		/*
		 *	Does the page exist in the copy?
		 */
		copy_offset = first_offset - copy_object->shadow_offset;
		copy_m = vm_page_lookup(copy_object, copy_offset);
		if (copy_m != VM_PAGE_NULL) {
			if (copy_m->busy) {
				/*
				 *	If the page is being brought
				 *	in, wait for it and then retry.
				 */
				PAGE_ASSERT_WAIT(copy_m, interruptible);
				RELEASE_PAGE(m);
				copy_object->ref_count--;
				assert(copy_object->ref_count > 0);
				vm_object_unlock(copy_object);
				UNLOCK_THINGS;
				thread_block();
				return((current_thread()->wait_result != THREAD_AWAKENED) ?
					VM_FAULT_INTERRUPTED :
					VM_FAULT_RETRY);
			}
		}

		 else {
			/*
			 *	Allocate a page for the copy
			 */
			copy_m = vm_page_alloc(copy_object,
							copy_offset);
			if (copy_m == VM_PAGE_NULL) {
				/*
				 *	Wait for a page, then retry.
				 */
				RELEASE_PAGE(m);
				copy_object->ref_count--;
				assert(copy_object->ref_count > 0);
				vm_object_unlock(copy_object);
				UNLOCK_THINGS;
				return(VM_FAULT_MEMORY_SHORTAGE);
			}

			/*
			 *	Must copy page into copy-object.
			 */

			vm_page_copy(m, copy_m);
			
			/*
			 *	If the old page was in use by any users
			 *	of the copy-object, it must be removed
			 *	from all pmaps.  (We can't know which
			 *	pmaps use it.)
			 */

			vm_page_lock_queues();
			pmap_page_protect(m->phys_addr, VM_PROT_NONE);
			copy_m->dirty = TRUE;
			vm_page_unlock_queues();

			/*
			 *	If there's a pager, then immediately
			 *	page out this page, using the "initialize"
			 *	option.  Else, we use the copy.
			 */

		 	if (!copy_object->pager_created) {
				vm_page_lock_queues();
				vm_page_activate(copy_m);
				vm_page_unlock_queues();
				PAGE_WAKEUP_DONE(copy_m);
			} else {
				/*
				 *	Prepare the page for pageout:
				 *
				 *	Since it was just allocated,
				 *	it is not on a pageout queue, but
				 *	it is busy.
				 */

				copy_m->busy = FALSE;

				/*
				 *	Unlock everything except the
				 *	copy_object itself.
				 */

				vm_object_unlock(object);

				vm_pageout_page(copy_m, TRUE, TRUE);

				/*
				 *	Since the pageout may have
				 *	temporarily dropped the
				 *	copy_object's lock, we
				 *	check whether we'll have
				 *	to deallocate the hard way.
				 */

				if ((copy_object->shadow != object) ||
				    (copy_object->ref_count == 1)) {
					vm_object_unlock(copy_object);
					vm_object_deallocate(copy_object);
					vm_object_lock(object);
					continue;
				}
				
				/*
				 *	Pick back up the old object's
				 *	lock.  [It is safe to do so,
				 *	since it must be deeper in the
				 *	object tree.]
				 */
				
				vm_object_lock(object);
			}

			/*
			 *	Because we're pushing a page upward
			 *	in the object tree, we must restart
			 *	any faults that are waiting here.
			 *	[Note that this is an expansion of
			 *	PAGE_WAKEUP that uses the THREAD_RESTART
			 *	wait result].  Can't turn off the page's
			 *	busy bit because we're not done with it.
			 */
			 
			if (m->wanted) {
				m->wanted = FALSE;
				thread_wakeup_with_result((int) m,
					THREAD_RESTART);
			}
		}

		/*
		 *	The reference count on copy_object must be
		 *	at least 2: one for our extra reference,
		 *	and at least one from the outside world
		 *	(we checked that when we last locked
		 *	copy_object).
		 */
		copy_object->ref_count--;
		assert(copy_object->ref_count > 0);
		vm_object_unlock(copy_object);

		break;
	}

	*result_page = m;
	*top_page = first_m;

#undef	UNLOCK_THINGS
#undef	RELEASE_PAGE

	/*
	 *	If the page can be written, assume that it will be.
	 *	[Earlier, we restrict the permission to allow write
	 *	access only if the fault so required, so we don't
	 *	mark read-only data as dirty.]
	 */

	if (vm_fault_dirty_handling && (*protection & VM_PROT_WRITE))
		m->dirty = TRUE;

	return(VM_FAULT_SUCCESS);
}

kern_return_t vm_fault(map, vaddr, fault_type, change_wiring)
	vm_map_t	map;
	vm_offset_t	vaddr;
	vm_prot_t	fault_type;
	boolean_t	change_wiring;
{
	vm_map_version_t	version;	/* Map version for verificiation */
	boolean_t		wired;		/* Should mapping be wired down? */
	vm_object_t		object;		/* Top-level object */
	vm_offset_t		offset;		/* Top-level offset */
	vm_prot_t		prot;		/* Protection for mapping */
	vm_object_t		old_copy_object; /* Saved copy object */
	vm_page_t		result_page;	/* Result of vm_fault_page */
	vm_page_t		top_page;	/* Placeholder page */
	boolean_t		su;		/* Rubbish */
	kern_return_t		result;

	register
	vm_page_t		m;		/* Fast access to result_page */

	XPR(XPR_VM_FAULT, ("vm_fault: map %x, vaddr %x, fault_type %x, wiring %x",
			map, vaddr, fault_type, change_wiring));
    RetryFault: ;

	/*
	 *	Find the backing store object and offset into
	 *	it to begin the search.
	 */

	if ((result = vm_map_lookup(&map, vaddr, fault_type, &version,
			&object, &offset,
			&prot, &wired, &su)) != KERN_SUCCESS) {
		return(result);
	}

	/*
	 *	If the page is wired, we must fault for the current protection
	 *	value, to avoid further faults.
	 */

	if (wired)
		fault_type = prot;

   	/*
	 *	Make a reference to this object to
	 *	prevent its disposal while we are messing with
	 *	it.  Once we have the reference, the map is free
	 *	to be diddled.  Since objects reference their
	 *	shadows (and copies), they will stay around as well.
	 */

	assert(object->ref_count > 0);
	object->ref_count++;
	vm_object_paging_begin(object);

	result = vm_fault_page(object, offset, fault_type,
			(change_wiring && !wired), !change_wiring,
			&prot, &result_page, &top_page, &map->vm_stat);

	/*
	 *	If we didn't succeed, lose the object reference immediately.
	 */

	if (result != VM_FAULT_SUCCESS)
		vm_object_deallocate(object);

	/*
	 *	See why we failed, and take corrective action.
	 */

	switch (result) {
		case VM_FAULT_SUCCESS:
			break;
		case VM_FAULT_RETRY:
			goto RetryFault;
		case VM_FAULT_INTERRUPTED:
			return(KERN_SUCCESS);
		case VM_FAULT_MEMORY_SHORTAGE:
			VM_WAIT;
			goto RetryFault;
		case VM_FAULT_MEMORY_ERROR:
			return(KERN_MEMORY_ERROR);
	}

	m = result_page;

	assert((change_wiring && !wired) ?
	       (top_page == VM_PAGE_NULL) :
	       ((top_page == VM_PAGE_NULL) == (m->object == object)));
	assert(!(m->active || m->inactive));

	/*
	 *	How to clean up the result of vm_fault_page.  This
	 *	happens whether the mapping is entered or not.
	 */

#define UNLOCK_AND_DEALLOCATE				\
	MACRO_BEGIN					\
	vm_object_paging_end(m->object);		\
	vm_object_unlock(m->object);			\
	if (top_page != VM_PAGE_NULL) {			\
		vm_object_lock(object);			\
		VM_PAGE_FREE(top_page);			\
		vm_object_paging_end(object);		\
		vm_object_unlock(object);		\
	}						\
	vm_object_deallocate(object);			\
	MACRO_END

	/*
	 *	What to do with the resulting page from vm_fault_page
	 *	if it doesn't get entered into the physical map:
	 */

#define RELEASE_PAGE(m)					\
	MACRO_BEGIN					\
	PAGE_WAKEUP_DONE(m);				\
	vm_page_lock_queues();				\
	vm_page_activate(m);				\
	vm_page_unlock_queues();			\
	MACRO_END

	/*
	 *	We must verify that the maps have not changed
	 *	since our last lookup.
	 */

	old_copy_object = m->object->copy;

	vm_object_unlock(m->object);
	while (!vm_map_verify(map, &version)) {
		vm_object_t	retry_object;
		vm_offset_t	retry_offset;
		vm_prot_t	retry_prot;

		/*
		 *	To avoid trying to write_lock the map while another
		 *	thread has it read_locked (in vm_map_pageable), we
		 *	do not try for write permission.  If the page is
		 *	still writable, we will get write permission.  If it
		 *	is not, or has been marked needs_copy, we enter the
		 *	mapping without write permission, and will merely
		 *	take another fault.
		 */
		result = vm_map_lookup(&map, vaddr,
				fault_type & ~VM_PROT_WRITE, &version,
				&retry_object, &retry_offset, &retry_prot,
				&wired, &su);

		if (result != KERN_SUCCESS) {
			vm_object_lock(m->object);
			RELEASE_PAGE(m);
			UNLOCK_AND_DEALLOCATE;
			return(result);
		}

		vm_object_unlock(retry_object);
		vm_object_lock(m->object);

		if ((retry_object != object) ||
				(retry_offset != offset)) {
			RELEASE_PAGE(m);
			UNLOCK_AND_DEALLOCATE;
			goto RetryFault;
		}

		/*
		 *	Check whether the protection has changed or the object
		 *	has been copied while we left the map unlocked.
		 */
		prot &= retry_prot;
		vm_object_unlock(m->object);
	}
	vm_object_lock(m->object);

	/*
	 *	If the copy object changed while the top-level object
	 *	was unlocked, then we must take away write permission.
	 */

	if (m->object->copy != old_copy_object)
		prot &= ~VM_PROT_WRITE;

	/*
	 *	If we want to wire down this page, but no longer have
	 *	adequate permissions, we must start all over.
	 */

	if (wired && (prot != fault_type)) {
		RELEASE_PAGE(m);
		UNLOCK_AND_DEALLOCATE;
		goto RetryFault;
	}
		

	/*
	 *	It's critically important that a wired-down page be faulted
	 *	only once in each map for which it is wired.
	 */

	assert(!(m->active || m->inactive));

	vm_object_unlock(m->object);

	/*
	 *	Put this page into the physical map.
	 *	We had to do the unlock above because pmap_enter
	 *	may cause other faults.   We don't put the
	 *	page back on the active queue until later so
	 *	that the page-out daemon won't find us (yet).
	 */

	PMAP_ENTER(map->pmap, vaddr, m, prot, wired);

	/*
	 *	If the page is not wired down, then put it where the
	 *	pageout daemon can find it.
	 */
	vm_object_lock(m->object);
	vm_page_lock_queues();
	if (change_wiring) {
		if (wired)
			vm_page_wire(m);
		else
			vm_page_unwire(m);
	}
	else
		vm_page_activate(m);
	vm_page_unlock_queues();

	/*
	 *	Unlock everything, and return
	 */

	vm_map_verify_done(map, &version);
	PAGE_WAKEUP_DONE(m);

	UNLOCK_AND_DEALLOCATE;

#undef	UNLOCK_AND_DEALLOCATE
#undef	RELEASE_PAGE

	return(KERN_SUCCESS);
}

kern_return_t	vm_fault_wire_fast();

/*
 *	vm_fault_wire:
 *
 *	Wire down a range of virtual addresses in a map.
 */
void vm_fault_wire(map, entry)
	vm_map_t	map;
	vm_map_entry_t	entry;
{

	register vm_offset_t	va;
	register pmap_t		pmap;
	register vm_offset_t	end_addr = entry->vme_end;

	pmap = vm_map_pmap(map);

	/*
	 *	Inform the physical mapping system that the
	 *	range of addresses may not fault, so that
	 *	page tables and such can be locked down as well.
	 */

	pmap_pageable(pmap, entry->vme_start, end_addr, FALSE);

	/*
	 *	We simulate a fault to get the page and enter it
	 *	in the physical map.
	 */

	for (va = entry->vme_start; va < end_addr; va += PAGE_SIZE) {
		if (vm_fault_wire_fast(map, va, entry) != KERN_SUCCESS)
			(void) vm_fault(map, va, VM_PROT_NONE, TRUE);
	}
}

/*
 *	vm_fault_unwire:
 *
 *	Unwire a range of virtual addresses in a map.
 */
void vm_fault_unwire(map, entry)
	vm_map_t	map;
	vm_map_entry_t	entry;
{

	register vm_offset_t	va;
	register pmap_t		pmap;
	register vm_offset_t	end_addr = entry->vme_end;
	vm_object_t		object;

	pmap = vm_map_pmap(map);

	object = (entry->is_a_map || entry->is_sub_map)
			? VM_OBJECT_NULL : entry->object.vm_object;

	/*
	 *	Since the pages are wired down, we must be able to
	 *	get their mappings from the physical map system.
	 */

	for (va = entry->vme_start; va < end_addr; va += PAGE_SIZE) {
		pmap_change_wiring(pmap, va, FALSE);

		if (object == VM_OBJECT_NULL) {
			vm_map_lock_set_recursive(map);
			(void) vm_fault(map, va, VM_PROT_NONE, TRUE);
			vm_map_lock_clear_recursive(map);
		} else {
		 	vm_prot_t	prot;
			vm_page_t	result_page;
			vm_page_t	top_page;
			vm_fault_return_t result;

			do {
				prot = VM_PROT_NONE;

				vm_object_lock(object);
				vm_object_paging_begin(object);
			 	result = vm_fault_page(object,
						entry->offset +
						  (va - entry->vme_start),
						VM_PROT_NONE, TRUE,
						FALSE, &prot,
						&result_page,
						&top_page,
						&map->vm_stat);
			} while (result == VM_FAULT_RETRY);

			if (result != VM_FAULT_SUCCESS)
				panic("vm_fault_unwire: failure");

			vm_page_lock_queues();
			vm_page_unwire(result_page);
			vm_page_unlock_queues();
			PAGE_WAKEUP_DONE(result_page);
			vm_object_paging_end(result_page->object);
			vm_object_unlock(result_page->object);

			if (top_page != VM_PAGE_NULL) {
				if (vm_fault_debug & 0x10)
					printf("vm_fault_unwire: found a top page!\n");
				vm_object_lock(object);
				VM_PAGE_FREE(top_page);
				vm_object_paging_end(object);
				vm_object_unlock(object);
			}
		}
	}

	/*
	 *	Inform the physical mapping system that the range
	 *	of addresses may fault, so that page tables and
	 *	such may be unwired themselves.
	 */

	pmap_pageable(pmap, entry->vme_start, end_addr, TRUE);

}

/*
 *	vm_fault_wire_fast:
 *
 *	Handle common case of a wire down page fault at the given address.
 *	If successful, the page is inserted into the associated physical map.
 *	The map entry is passed in to avoid the overhead of a map lookup.
 *
 *	NOTE: the given address should be truncated to the
 *	proper page address.
 *
 *	KERN_SUCCESS is returned if the page fault is handled; otherwise,
 *	a standard error specifying why the fault is fatal is returned.
 *
 *	The map in question must be referenced, and remains so.
 *	Caller has a read lock on the map.
 *
 *	This is a stripped version of vm_fault() for wiring pages.  Anything
 *	other than the common case will return KERN_FAILURE, and the caller
 *	is expected to call vm_fault().
 */
kern_return_t vm_fault_wire_fast(map, va, entry)
	vm_map_t	map;
	vm_offset_t	va;
	vm_map_entry_t	entry;
{
	vm_object_t		object;
	vm_offset_t		offset;
	register vm_page_t	m;
	vm_prot_t		prot;

	vm_stat.faults++;		/* needs lock XXX */
	map->vm_stat.faults++;
/*
 *	Recovery actions
 */

#undef	RELEASE_PAGE
#define RELEASE_PAGE(m)	{				\
	PAGE_WAKEUP_DONE(m);				\
	vm_page_lock_queues();				\
	vm_page_unwire(m);				\
	vm_page_unlock_queues();			\
}


#undef	UNLOCK_THINGS
#define UNLOCK_THINGS	{				\
	object->paging_in_progress--;			\
	vm_object_unlock(object);			\
}

#undef	UNLOCK_AND_DEALLOCATE
#define UNLOCK_AND_DEALLOCATE	{			\
	UNLOCK_THINGS;					\
	vm_object_deallocate(object);			\
}
/*
 *	Give up and have caller do things the hard way.
 */

#define GIVE_UP {					\
	UNLOCK_AND_DEALLOCATE;				\
	return(KERN_FAILURE);				\
}


	/*
	 *	If this entry is not directly to a vm_object, bail out.
	 */
	if ((entry->is_a_map) || (entry->is_sub_map))
		return(KERN_FAILURE);

	/*
	 *	Find the backing store object and offset into it.
	 */

	object = entry->object.vm_object;
	offset = (va - entry->vme_start) + entry->offset;
	prot = entry->protection;

   	/*
	 *	Make a reference to this object to prevent its
	 *	disposal while we are messing with it.
	 */

	vm_object_lock(object);
	assert(object->ref_count > 0);
	object->ref_count++;
	object->paging_in_progress++;

	/*
	 *	INVARIANTS (through entire routine):
	 *
	 *	1)	At all times, we must either have the object
	 *		lock or a busy page in some object to prevent
	 *		some other thread from trying to bring in
	 *		the same page.
	 *
	 *	2)	Once we have a busy page, we must remove it from
	 *		the pageout queues, so that the pageout daemon
	 *		will not grab it away.
	 *
	 */

	/*
	 *	Look for page in top-level object.  If it's not there or
	 *	there's something going on, give up.
	 */
	m = vm_page_lookup(object, offset);
	if ((m == VM_PAGE_NULL) || (m->error) ||
	    (m->busy) || (m->absent) || (prot & m->page_lock)) {
		GIVE_UP;
	}

	/*
	 *	Wire the page down now.  All bail outs beyond this
	 *	point must unwire the page.  
	 */

	vm_page_lock_queues();
	vm_page_wire(m);
	vm_page_unlock_queues();

	/*
	 *	Mark page busy for other threads.
	 */
	assert(!m->busy);
	m->busy = TRUE;
	assert(!m->absent);

	/*
	 *	Give up if the page is being written and there's a copy object
	 */
	if ((object->copy != VM_OBJECT_NULL) && (prot & VM_PROT_WRITE)) {
		RELEASE_PAGE(m);
		GIVE_UP;
	}

	/*
	 *	Put this page into the physical map.
	 *	We have to unlock the object because pmap_enter
	 *	may cause other faults.   
	 */
	vm_object_unlock(object);

	PMAP_ENTER(map->pmap, va, m, prot, TRUE);

	/*
	 *	Must relock object so that paging_in_progress can be cleared.
	 */
	vm_object_lock(object);

	/*
	 *	Unlock everything, and return
	 */

	PAGE_WAKEUP_DONE(m);
	UNLOCK_AND_DEALLOCATE;

	return(KERN_SUCCESS);

}

/*
 *	Routine:	vm_fault_copy
 *
 *	Purpose:
 *		Copy pages from one virtual memory object to another --
 *		neither the source nor destination pages need be resident.
 *
 *		Before actually copying a page, the version associated with
 *		the destination address map wil be verified.
 *
 *	In/out conditions:
 *		The caller must hold a reference, but not a lock, to each
 *		of the source and destination objects and to the destination map.
 *
 *	Results:
 *		Returns KERN_SUCCESS if no errors were encountered in
 *		reading or writing the data.  Returns KERN_INTERRUPTED if
 *		the operation was interrupted (only possible if the
 *		"interruptible" argument is asserted).  Other return values
 *		indicate a permanent error in copying the data.
 *
 *		The actual amount of data copied will be returned in the
 *		"copy_size" argument.  In the event that the destination map
 *		verification failed, this amount may be less than the amount
 *		requested.
 */
kern_return_t	vm_fault_copy(
			src_object,
			src_offset,
			src_size,
			dst_object,
			dst_offset,
			dst_map,
			dst_version,
			interruptible
			)
	vm_object_t	src_object;
	vm_offset_t	src_offset;
	vm_size_t	*src_size;		/* INOUT */
	vm_object_t	dst_object;
	vm_offset_t	dst_offset;
	vm_map_t	dst_map;
	vm_map_version_t *dst_version;
	boolean_t	interruptible;
{
	vm_page_t		result_page;
	vm_prot_t		prot;
	
	vm_page_t		src_page;
	vm_page_t		src_top_page;

	vm_page_t		dst_page;
	vm_page_t		dst_top_page;

	vm_size_t		amount_done;
	vm_object_t		old_copy_object;

#define	RETURN(x)					\
	MACRO_BEGIN					\
	*src_size = amount_done;			\
	MACRO_RETURN(x);				\
	MACRO_END

	amount_done = 0;
	do { /* while (amount_done != *src_size) */

	    RetrySourceFault: ;

		prot = VM_PROT_READ;

		vm_object_paging_begin(src_object);

		switch (vm_fault_page(src_object, src_offset, VM_PROT_READ,
				FALSE, interruptible,
				&prot, &result_page, &src_top_page,
				&dst_map->vm_stat)) {

			case VM_FAULT_SUCCESS:
				break;
			case VM_FAULT_RETRY:
				goto RetrySourceFault;
			case VM_FAULT_INTERRUPTED:
				RETURN(SEND_INTERRUPTED);
			case VM_FAULT_MEMORY_SHORTAGE:
				VM_WAIT;
				goto RetrySourceFault;
			case VM_FAULT_MEMORY_ERROR:
				return(KERN_MEMORY_ERROR);
		}

		src_page = result_page;

		/* XXX I don't think that src_top_page can be non-null */

		assert((src_top_page == VM_PAGE_NULL) == (src_page->object == src_object));
		assert(!(src_page->active || src_page->inactive));

		/*
		 *	How to clean up the result of vm_fault_page for the
		 *	source page
		 */

#define SOURCE_RELEASE						\
		MACRO_BEGIN					\
		vm_object_lock(src_page->object);		\
		PAGE_WAKEUP_DONE(src_page);			\
		vm_page_lock_queues();				\
		vm_page_activate(src_page);			\
		vm_page_unlock_queues();			\
		vm_object_paging_end(src_page->object);		\
		vm_object_unlock(src_page->object);		\
		if (src_top_page != VM_PAGE_NULL) {		\
			vm_object_lock(src_object);		\
			VM_PAGE_FREE(src_top_page);		\
			vm_object_paging_end(src_object);	\
			vm_object_unlock(src_object);		\
		}						\
		MACRO_END

		assert ((prot & VM_PROT_READ) != VM_PROT_NONE);

		vm_object_unlock(src_page->object);

	    RetryDestinationFault: ;

		prot = VM_PROT_WRITE;

		vm_object_paging_begin(dst_object);

		switch (vm_fault_page(dst_object, dst_offset, VM_PROT_WRITE,
				FALSE, FALSE /* interruptible */,
				&prot, &result_page, &dst_top_page,
				&dst_map->vm_stat)) {

			case VM_FAULT_SUCCESS:
				break;
			case VM_FAULT_RETRY:
				goto RetryDestinationFault;
			case VM_FAULT_INTERRUPTED:
				SOURCE_RELEASE;
				RETURN(SEND_INTERRUPTED);
			case VM_FAULT_MEMORY_SHORTAGE:
				VM_WAIT;
				goto RetryDestinationFault;
			case VM_FAULT_MEMORY_ERROR:
				SOURCE_RELEASE;
				return(KERN_MEMORY_ERROR);
		}
		assert ((prot & VM_PROT_WRITE) != VM_PROT_NONE);

		dst_page = result_page;

		old_copy_object = dst_page->object->copy;

#define DESTINATION_RELEASE					\
		MACRO_BEGIN					\
		vm_object_lock(dst_page->object);		\
		PAGE_WAKEUP_DONE(dst_page);			\
		vm_page_lock_queues();				\
		vm_page_activate(dst_page);			\
		vm_page_unlock_queues();			\
		vm_object_paging_end(dst_page->object);		\
		vm_object_unlock(dst_page->object);		\
		if (dst_top_page != VM_PAGE_NULL) {		\
			vm_object_lock(dst_object);		\
			VM_PAGE_FREE(dst_top_page);		\
			vm_object_paging_end(dst_object);	\
			vm_object_unlock(dst_object);		\
		}						\
		MACRO_END

		vm_object_unlock(dst_page->object);

		if (!vm_map_verify(dst_map, dst_version)) {

		 BailOut: ;

			SOURCE_RELEASE;
			DESTINATION_RELEASE;
			break;
		}


		vm_object_lock(dst_page->object);
		if (dst_page->object->copy != old_copy_object) {
			vm_object_unlock(dst_page->object);
			goto BailOut;
		}
		vm_object_unlock(dst_page->object);

		assert(!(dst_page->active || dst_page->inactive));

		/*
		 *	Copy the page, and note that it is dirty
		 *	immediately.
		 */

		vm_page_copy(src_page, dst_page);
		dst_page->dirty = TRUE;

		/*
		 *	Unlock everything, and return
		 */

		vm_map_verify_done(dst_map, dst_version);

		SOURCE_RELEASE;
		DESTINATION_RELEASE;

		amount_done += PAGE_SIZE;
		src_offset += PAGE_SIZE;
		dst_offset += PAGE_SIZE;

#undef	SOURCE_RELEASE
#undef	DESTINATION_RELEASE

	} while (amount_done != *src_size);

	RETURN(KERN_SUCCESS);
#undef	RETURN

	/*NOTREACHED*/	
}

#ifdef	notdef

/*
 *	Routine:	vm_fault_page_overwrite
 *
 *	Description:
 *		A form of vm_fault_page that assumes that the
 *		resulting page will be overwritten in its entirety,
 *		making it unnecessary to obtain the correct *contents*
 *		of the page.
 *
 *	Implementation:
 *		XXX Untested.  Also unused.  Eventually, this technology
 *		could be used in vm_fault_copy() to advantage.
 */
vm_fault_return_t vm_fault_page_overwrite(dst_object, dst_offset, result_page)
	register
	vm_object_t	dst_object;
	vm_offset_t	dst_offset;
	vm_page_t	*result_page;	/* OUT */
{
	register
	vm_page_t	dst_page;

#define	interruptible	FALSE	/* XXX */

	while (TRUE) {
		/*
		 *	Look for a page at this offset
		 */

		while ((dst_page = vm_page_lookup(dst_object, dst_offset))
				 == VM_PAGE_NULL) {
			/*
			 *	No page, no problem... just allocate one.
			 */

			dst_page = vm_page_alloc(dst_object, dst_offset);
			if (dst_page == VM_PAGE_NULL) {
				vm_object_unlock(dst_object);
				VM_WAIT;
				vm_object_lock(dst_object);
				continue;
			}

			/*
			 *	Pretend that the memory manager
			 *	write-protected the page.
			 *
			 *	Note that we will be asking for write
			 *	permission without asking for the data
			 *	first.
			 */

			dst_page->overwriting = TRUE;
			dst_page->page_lock = VM_PROT_WRITE;
			dst_page->absent = TRUE;
			dst_object->absent_count++;

			break;

			/*
			 *	When we bail out, we might have to throw
			 *	away the page created here.
			 */

#define	DISCARD_PAGE						\
	MACRO_BEGIN						\
	vm_object_lock(dst_object);				\
	dst_page = vm_page_lookup(dst_object, dst_offset);	\
	if ((dst_page != VM_PAGE_NULL) && dst_page->overwriting) \
	   	VM_PAGE_FREE(dst_page);				\
	vm_object_unlock(dst_object);				\
	MACRO_END
		}

		/*
		 *	If the page is write-protected...
		 */

		if (dst_page->page_lock & VM_PROT_WRITE) {
			/*
			 *	... and an unlock request hasn't been sent
			 */

			if ( ! (dst_page->unlock_request & VM_PROT_WRITE)) {
				vm_prot_t	u;
				kern_return_t	rc;

				/*
				 *	... then send one now.
				 */

				if (!dst_object->pager_ready) {
					vm_object_assert_wait(dst_object,
						VM_OBJECT_EVENT_PAGER_READY,
						interruptible);
					vm_object_unlock(dst_object);
					thread_block();
					if (current_thread()->wait_result !=
					    THREAD_AWAKENED) {
						DISCARD_PAGE;
						return(VM_FAULT_INTERRUPTED);
					}
					continue;
				}

				u = dst_page->unlock_request |= VM_PROT_WRITE;
				vm_object_unlock(dst_object);

				if ((rc = memory_object_data_unlock(
						dst_object->pager,
						dst_object->pager_request,
						dst_offset + dst_object->paging_offset,
						PAGE_SIZE,
						u)) != KERN_SUCCESS) {
				     	printf("vm_object_overwrite: memory_object_data_unlock failed\n");
					DISCARD_PAGE;
					return((rc == SEND_INTERRUPTED) ?
						VM_FAULT_INTERRUPTED :
						VM_FAULT_MEMORY_ERROR);
				}
				vm_object_lock(dst_object);
				continue;
			}

			/* ... fall through to wait below */
		} else {
			/*
			 *	If the page isn't being used for other
			 *	purposes, then we're done.
			 */
			if ( ! (dst_page->busy || dst_page->absent || dst_page->error) )
				break;
		}

		PAGE_ASSERT_WAIT(dst_page, interruptible);
		vm_object_unlock(dst_object);
		thread_block();
		if (current_thread()->wait_result != THREAD_AWAKENED) {
			DISCARD_PAGE;
			return(VM_FAULT_INTERRUPTED);
		}
	}

	*result_page = dst_page;
	return(VM_FAULT_SUCCESS);

#undef	interruptible
#undef	DISCARD_PAGE
}

#endif	notdef
