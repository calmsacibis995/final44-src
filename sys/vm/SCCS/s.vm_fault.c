h03078
s 00016/00001/01010
d D 8.6 95/05/11 14:17:29 mckusick 24 23
c take the pmap_page_protect outside the page queue lock (from hibler)
e
s 00004/00002/01007
d D 8.5 95/01/09 17:50:21 cgd 23 22
c KNF, and 64-bit safety.
e
s 00005/00003/01004
d D 8.4 94/01/12 15:55:52 hibler 22 21
c keep track of a few more vmmeter statistics.
e
s 00002/00004/01005
d D 8.3 93/12/30 16:01:10 mckusick 21 20
c convert to use new queue structures
e
s 00001/00000/01008
d D 8.2 93/10/01 17:14:52 hibler 20 19
c when making copy of a page, make sure original is deactivated 
c (note we activate first so that deactivate does the right thing)
e
s 00002/00002/01006
d D 8.1 93/06/11 16:37:26 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/01007
d D 7.18 93/05/24 23:40:33 torek 18 17
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00010/00003/00998
d D 7.17 93/03/09 10:58:57 hibler 17 16
c attempt to recover from failure of vm_fault in vm_fault_wire
e
s 00007/00045/00994
d D 7.16 92/11/29 10:23:32 hibler 16 15
c no more page_lock, PG_ABSENT
e
s 00025/00027/01014
d D 7.15 92/10/01 17:54:20 mckusick 15 14
c convert vm_page bit fields to flags
e
s 00028/00028/01013
d D 7.14 92/09/21 21:46:14 hibler 14 13
c deal with VM_PAGER_ERROR
c did a little cleanup and clarified some comments
e
s 00001/00004/01040
d D 7.13 92/06/05 21:31:16 hibler 13 12
c correct incorrect comment
e
s 00000/00001/01044
d D 7.12 92/06/02 16:39:13 mckusick 12 11
c it is not really a panic, just a thought
e
s 00006/00004/01039
d D 7.11 92/05/04 17:21:55 bostic 11 10
c new include format
e
s 00002/00000/01041
d D 7.10 92/04/25 20:21:00 ralph 10 9
c set page clean after vm_pager_get().
e
s 00001/00001/01040
d D 7.9 92/03/09 22:49:40 mckusick 9 8
c fix from Donn Seeley to make shadow pages pageable
e
s 00007/00007/01034
d D 7.8 91/08/28 15:40:06 mckusick 8 7
c vm_stat is merged into vmmeter structure
e
s 00002/00002/01039
d D 7.7 91/07/25 23:01:54 mckusick 7 6
c vm_page_active_count and vm_page_inactive_count move to vm_stat
e
s 00008/00023/01033
d D 7.6 91/05/07 09:31:39 hibler 6 5
c don't perform the "single use" check, it was broken anyway
c pmap_remove_all -> pmap_page_protect
e
s 00021/00024/01035
d D 7.5 91/04/20 10:50:06 karels 5 4
c fix includes; new proc struct; rm *_NULL
e
s 00019/00018/01040
d D 7.4 91/03/27 11:32:17 mckusick 4 3
c copyright revision request from CMU
e
s 00007/00003/01051
d D 7.3 91/03/27 09:58:23 mckusick 3 2
c Mike's comments on the copyright notice
e
s 00022/00004/01032
d D 7.2 91/03/19 20:57:10 mckusick 2 1
c update CMU copyright and distribution notice
e
s 01036/00000/00000
d D 7.1 90/12/05 18:07:38 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 2
 * Copyright (c) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 * Copyright (c) 1987 Carnegie-Mellon University
E 2
I 2
D 4
 * Copyright (c) 1987 Carnegie-Mellon University.
E 4
I 4
D 19
 * Copyright (c) 1991 Regents of the University of California.
E 4
E 2
D 3
 * Copyright (c) 1991 Regents of the University of California.
E 3
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
I 4
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 *
 * Copyright (c) 1987, 1990 Carnegie-Mellon University.
 * All rights reserved.
 *
E 4
D 3
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
E 3
I 2
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
D 4
 * Carnegie Mellon requests users of this software to return to Carnegie
 * any improvements or extensions that they make and grant Carnegie
 * the rights to redistribute these changes.  We can be reached at
 * mach@cs.cmu.edu or
 *	Project Mach
 *	School of Computer Science
 *	Carnegie Mellon University
 *	Pittsburgh PA 15213-3890
E 4
I 4
 * Carnegie Mellon requests users of this software to return to
E 4
I 3
 *
I 4
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
E 4
 *
D 4
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
E 3
E 2
 *
D 2
 * The CMU software License Agreement specifies the terms and conditions
 * for use and redistribution.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
E 4
I 4
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
E 4
 */

/*
 *	Page fault handling module.
 */

D 11
#include "param.h"
E 11
I 11
#include <sys/param.h>
#include <sys/systm.h>
E 11
D 5
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_object.h"
#include "../vm/vm_page.h"
#include "../vm/pmap.h"
#include "../vm/vm_statistics.h"
#include "../vm/vm_pageout.h"
E 5

I 5
D 11
#include "vm.h"
#include "vm_page.h"
#include "vm_pageout.h"
E 11
I 11
#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_pageout.h>
E 11

E 5
/*
 *	vm_fault:
 *
 *	Handle a page fault occuring at the given address,
 *	requiring the given permissions, in the map specified.
 *	If successful, the page is inserted into the
 *	associated physical map.
 *
 *	NOTE: the given address should be truncated to the
 *	proper page address.
 *
 *	KERN_SUCCESS is returned if the page fault is handled; otherwise,
 *	a standard error specifying why the fault is fatal is returned.
 *
 *
 *	The map in question must be referenced, and remains so.
 *	Caller may hold no locks.
 */
I 11
int
E 11
vm_fault(map, vaddr, fault_type, change_wiring)
	vm_map_t	map;
	vm_offset_t	vaddr;
	vm_prot_t	fault_type;
	boolean_t	change_wiring;
{
	vm_object_t		first_object;
	vm_offset_t		first_offset;
	vm_map_entry_t		entry;
	register vm_object_t	object;
	register vm_offset_t	offset;
	register vm_page_t	m;
	vm_page_t		first_m;
	vm_prot_t		prot;
	int			result;
	boolean_t		wired;
	boolean_t		su;
	boolean_t		lookup_still_valid;
	boolean_t		page_exists;
	vm_page_t		old_m;
	vm_object_t		next_object;

D 8
	vm_stat.faults++;		/* needs lock XXX */
E 8
I 8
D 22
	cnt.v_vm_faults++;		/* needs lock XXX */
E 22
I 22
	cnt.v_faults++;		/* needs lock XXX */
E 22
E 8
/*
 *	Recovery actions
 */
#define	FREE_PAGE(m)	{				\
	PAGE_WAKEUP(m);					\
	vm_page_lock_queues();				\
	vm_page_free(m);				\
	vm_page_unlock_queues();			\
}

#define	RELEASE_PAGE(m)	{				\
	PAGE_WAKEUP(m);					\
	vm_page_lock_queues();				\
	vm_page_activate(m);				\
	vm_page_unlock_queues();			\
}

#define	UNLOCK_MAP	{				\
	if (lookup_still_valid) {			\
		vm_map_lookup_done(map, entry);		\
		lookup_still_valid = FALSE;		\
	}						\
}

#define	UNLOCK_THINGS	{				\
	object->paging_in_progress--;			\
	vm_object_unlock(object);			\
	if (object != first_object) {			\
		vm_object_lock(first_object);		\
		FREE_PAGE(first_m);			\
		first_object->paging_in_progress--;	\
		vm_object_unlock(first_object);		\
	}						\
	UNLOCK_MAP;					\
}

#define	UNLOCK_AND_DEALLOCATE	{			\
	UNLOCK_THINGS;					\
	vm_object_deallocate(first_object);		\
}

    RetryFault: ;

	/*
	 *	Find the backing store object and offset into
	 *	it to begin the search.
	 */

	if ((result = vm_map_lookup(&map, vaddr, fault_type, &entry,
			&first_object, &first_offset,
			&prot, &wired, &su)) != KERN_SUCCESS) {
		return(result);
	}
	lookup_still_valid = TRUE;

	if (wired)
		fault_type = prot;

D 5
	first_m = VM_PAGE_NULL;
E 5
I 5
	first_m = NULL;
E 5

   	/*
	 *	Make a reference to this object to
	 *	prevent its disposal while we are messing with
	 *	it.  Once we have the reference, the map is free
	 *	to be diddled.  Since objects reference their
	 *	shadows (and copies), they will stay around as well.
	 */

	vm_object_lock(first_object);

	first_object->ref_count++;
	first_object->paging_in_progress++;

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
	 *		more than one thead attempting to pager_data_unlock
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
D 5
		if (m != VM_PAGE_NULL) {
E 5
I 5
		if (m != NULL) {
E 5
			/*
			 *	If the page is being brought in,
			 *	wait for it and then retry.
			 */
D 15
			if (m->busy) {
E 15
I 15
			if (m->flags & PG_BUSY) {
E 15
#ifdef DOTHREADS
				int	wait_result;

				PAGE_ASSERT_WAIT(m, !change_wiring);
				UNLOCK_THINGS;
				thread_block();
				wait_result = current_thread()->wait_result;
				vm_object_deallocate(first_object);
				if (wait_result != THREAD_AWAKENED)
					return(KERN_SUCCESS);
				goto RetryFault;
#else
				PAGE_ASSERT_WAIT(m, !change_wiring);
				UNLOCK_THINGS;
I 22
				cnt.v_intrans++;
E 22
				thread_block();
				vm_object_deallocate(first_object);
				goto RetryFault;
#endif
			}

D 15
			if (m->absent)
E 15
I 15
D 16
			if (m->flags & PG_ABSENT)
E 15
				panic("vm_fault: absent");

E 16
			/*
D 16
			 *	If the desired access to this page has
			 *	been locked out, request that it be unlocked.
			 */

			if (fault_type & m->page_lock) {
#ifdef DOTHREADS
				int	wait_result;

				if ((fault_type & m->unlock_request) != fault_type)
					panic("vm_fault: pager_data_unlock");

				PAGE_ASSERT_WAIT(m, !change_wiring);
				UNLOCK_THINGS;
				thread_block();
				wait_result = current_thread()->wait_result;
				vm_object_deallocate(first_object);
				if (wait_result != THREAD_AWAKENED)
					return(KERN_SUCCESS);
				goto RetryFault;
#else
				if ((fault_type & m->unlock_request) != fault_type)
					panic("vm_fault: pager_data_unlock");

				PAGE_ASSERT_WAIT(m, !change_wiring);
				UNLOCK_THINGS;
				thread_block();
				vm_object_deallocate(first_object);
				goto RetryFault;
#endif
			}

			/*
E 16
			 *	Remove the page from the pageout daemon's
			 *	reach while we play with it.
			 */

			vm_page_lock_queues();
D 15
			if (m->inactive) {
E 15
I 15
			if (m->flags & PG_INACTIVE) {
E 15
D 21
				queue_remove(&vm_page_queue_inactive, m,
						vm_page_t, pageq);
E 21
I 21
				TAILQ_REMOVE(&vm_page_queue_inactive, m, pageq);
E 21
D 15
				m->inactive = FALSE;
E 15
I 15
				m->flags &= ~PG_INACTIVE;
E 15
D 7
				vm_page_inactive_count--;
E 7
I 7
D 8
				vm_stat.inactive_count--;
E 7
				vm_stat.reactivations++;
E 8
I 8
				cnt.v_inactive_count--;
				cnt.v_reactivated++;
E 8
			} 

D 15
			if (m->active) {
E 15
I 15
			if (m->flags & PG_ACTIVE) {
E 15
D 21
				queue_remove(&vm_page_queue_active, m,
						vm_page_t, pageq);
E 21
I 21
				TAILQ_REMOVE(&vm_page_queue_active, m, pageq);
E 21
D 15
				m->active = FALSE;
E 15
I 15
				m->flags &= ~PG_ACTIVE;
E 15
D 7
				vm_page_active_count--;
E 7
I 7
D 8
				vm_stat.active_count--;
E 8
I 8
				cnt.v_active_count--;
E 8
E 7
			}
			vm_page_unlock_queues();

			/*
			 *	Mark page busy for other threads.
			 */
D 15
			m->busy = TRUE;
			m->absent = FALSE;
E 15
I 15
			m->flags |= PG_BUSY;
D 16
			m->flags &= ~PG_ABSENT;
E 16
E 15
			break;
		}

D 5
		if (((object->pager != vm_pager_null) &&
E 5
I 5
		if (((object->pager != NULL) &&
E 5
				(!change_wiring || wired))
		    || (object == first_object)) {

			/*
			 *	Allocate a new page for this object/offset
			 *	pair.
			 */

			m = vm_page_alloc(object, offset);

D 5
			if (m == VM_PAGE_NULL) {
E 5
I 5
			if (m == NULL) {
E 5
				UNLOCK_AND_DEALLOCATE;
				VM_WAIT;
				goto RetryFault;
			}
		}

D 5
		if ((object->pager != vm_pager_null) &&
E 5
I 5
D 14
		if ((object->pager != NULL) &&
E 5
				(!change_wiring || wired)) {
E 14
I 14
		if (object->pager != NULL && (!change_wiring || wired)) {
E 14
			int rv;

			/*
			 *	Now that we have a busy page, we can
			 *	release the object lock.
			 */
			vm_object_unlock(object);

			/*
			 *	Call the pager to retrieve the data, if any,
			 *	after releasing the lock on the map.
			 */
			UNLOCK_MAP;
I 22
			cnt.v_pageins++;
E 22
D 14

E 14
			rv = vm_pager_get(object->pager, m, TRUE);
I 14

			/*
			 *	Reaquire the object lock to preserve our
			 *	invariant.
			 */
			vm_object_lock(object);

			/*
			 *	Found the page.
			 *	Leave it busy while we play with it.
			 */
E 14
			if (rv == VM_PAGER_OK) {
				/*
D 14
				 *	Found the page.
				 *	Leave it busy while we play with it.
				 */
				vm_object_lock(object);

				/*
E 14
				 *	Relookup in case pager changed page.
				 *	Pager is responsible for disposition
				 *	of old page if moved.
				 */
				m = vm_page_lookup(object, offset);

D 8
				vm_stat.pageins++;
E 8
I 8
D 22
				cnt.v_pageins++;
E 22
I 22
				cnt.v_pgpgin++;
E 22
E 8
D 15
				m->fake = FALSE;
I 10
				m->clean = TRUE;
E 15
I 15
				m->flags &= ~PG_FAKE;
				m->flags |= PG_CLEAN;
E 15
E 10
				pmap_clear_modify(VM_PAGE_TO_PHYS(m));
				break;
			}

			/*
D 14
			 *	Remove the bogus page (which does not
			 *	exist at this object/offset); before
			 *	doing so, we must get back our object
			 *	lock to preserve our invariant.
			 *
			 *	Also wake up any other thread that may want
			 *	to bring in this page.
			 *
			 *	If this is the top-level object, we must
			 *	leave the busy page to prevent another
			 *	thread from rushing past us, and inserting
			 *	the page in that object at the same time
			 *	that we are.
E 14
I 14
			 * IO error or page outside the range of the pager:
			 * cleanup and return an error.
E 14
			 */
D 14

			vm_object_lock(object);
			/*
			 * Data outside the range of the pager; an error
			 */
			if (rv == VM_PAGER_BAD) {
E 14
I 14
			if (rv == VM_PAGER_ERROR || rv == VM_PAGER_BAD) {
E 14
				FREE_PAGE(m);
				UNLOCK_AND_DEALLOCATE;
				return(KERN_PROTECTION_FAILURE); /* XXX */
			}
I 14
			/*
			 * rv == VM_PAGER_FAIL:
			 *
			 * Page does not exist at this object/offset.
			 * Free the bogus page (waking up anyone waiting
			 * for it) and continue on to the next object.
			 *
			 * If this is the top-level object, we must
			 * leave the busy page to prevent another
			 * thread from rushing past us, and inserting
			 * the page in that object at the same time
			 * that we are.
			 */
E 14
			if (object != first_object) {
				FREE_PAGE(m);
D 13
				/*
				 * XXX - we cannot just fall out at this
				 * point, m has been freed and is invalid!
				 */
E 13
I 13
				/* note that `m' is not used after this */
E 13
I 10
D 12
				panic("vm_fault: free page"); /* XXX */
E 12
E 10
			}
		}

		/*
		 * We get here if the object has no pager (or unwiring)
		 * or the pager doesn't have the page.
		 */
		if (object == first_object)
			first_m = m;

		/*
		 *	Move on to the next object.  Lock the next
		 *	object before unlocking the current one.
		 */

		offset += object->shadow_offset;
		next_object = object->shadow;
D 5
		if (next_object == VM_OBJECT_NULL) {
E 5
I 5
		if (next_object == NULL) {
E 5
			/*
			 *	If there's no object left, fill the page
			 *	in the top object with zeros.
			 */
			if (object != first_object) {
				object->paging_in_progress--;
				vm_object_unlock(object);

				object = first_object;
				offset = first_offset;
				m = first_m;
				vm_object_lock(object);
			}
D 5
			first_m = VM_PAGE_NULL;
E 5
I 5
			first_m = NULL;
E 5

			vm_page_zero_fill(m);
D 8
			vm_stat.zero_fill_count++;
E 8
I 8
			cnt.v_zfod++;
E 8
D 15
			m->fake = FALSE;
			m->absent = FALSE;
E 15
I 15
D 16
			m->flags &= ~(PG_FAKE | PG_ABSENT);
E 16
I 16
			m->flags &= ~PG_FAKE;
E 16
E 15
			break;
		}
		else {
			vm_object_lock(next_object);
			if (object != first_object)
				object->paging_in_progress--;
			vm_object_unlock(object);
			object = next_object;
			object->paging_in_progress++;
		}
	}

D 15
	if (m->absent || m->active || m->inactive || !m->busy)
E 15
I 15
D 16
	if ((m->flags & (PG_ABSENT | PG_ACTIVE | PG_INACTIVE)) ||
	    !(m->flags & PG_BUSY))
E 15
		panic("vm_fault: absent or active or inactive or not busy after main loop");
E 16
I 16
	if ((m->flags & (PG_ACTIVE | PG_INACTIVE | PG_BUSY)) != PG_BUSY)
		panic("vm_fault: active, inactive or !busy after main loop");
E 16

	/*
	 *	PAGE HAS BEEN FOUND.
	 *	[Loop invariant still holds -- the object lock
	 *	is held.]
	 */

	old_m = m;	/* save page that would be copied */

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

			vm_page_copy(m, first_m);
D 15
			first_m->fake = FALSE;
			first_m->absent = FALSE;
E 15
I 15
D 16
			first_m->flags &= ~(PG_FAKE | PG_ABSENT);
E 16
I 16
			first_m->flags &= ~PG_FAKE;
E 16
E 15

			/*
			 *	If another map is truly sharing this
			 *	page with us, we have to flush all
			 *	uses of the original page, since we
			 *	can't distinguish those which want the
			 *	original from those which need the
			 *	new copy.
I 6
			 *
			 *	XXX If we know that only one map has
			 *	access to this page, then we could
			 *	avoid the pmap_page_protect() call.
E 6
			 */

			vm_page_lock_queues();
D 6
			if (!su) {
				/*
				 *	Also, once it's no longer in
				 *	use by any maps, move it to
				 *	the inactive queue instead.
				 */

				vm_page_deactivate(m);
				pmap_remove_all(VM_PAGE_TO_PHYS(m));
			}
			else {
				/*
				 *	Old page is only (possibly)
				 *	in use by faulting map.  We
				 *	should do a pmap_remove on
				 *	that mapping, but we know
				 *	that pmap_enter will remove
				 *	the old mapping before
				 *	inserting the new one.
				 */
				vm_page_activate(m);
			}
E 6
I 6
D 9
			vm_page_deactivate(m);
E 9
I 9
			vm_page_activate(m);
I 20
			vm_page_deactivate(m);
E 20
E 9
D 24
			pmap_page_protect(VM_PAGE_TO_PHYS(m), VM_PROT_NONE);
E 24
E 6
			vm_page_unlock_queues();
I 24
			/*
			 * XXX gag!  The page protect has been moved out
			 * of the page queue lock section to avoid a deadlock
			 * in the hp300-style (recursive) pmap module.
			 * If you were on an MP, p_p_protect might result
			 * in a vm_map_pageable(..., TRUE) for the associated
			 * page table page.  This would call vm_fault_unwire
			 * which would try to lock the page queues.
			 * Moving the call out is safe here because the
			 * object is still locked and that will prevent
			 * the pageout daemon from messing with this page
			 * on the inactive list.  (It would move it back to
			 * the active list if it were referenced but
			 * v_p_deallocate clears the ref bit).
			 */
			pmap_page_protect(VM_PAGE_TO_PHYS(m), VM_PROT_NONE);
E 24

			/*
			 *	We no longer need the old page or object.
			 */
			PAGE_WAKEUP(m);
			object->paging_in_progress--;
			vm_object_unlock(object);

			/*
			 *	Only use the new page below...
			 */

D 8
			vm_stat.cow_faults++;
E 8
I 8
			cnt.v_cow_faults++;
E 8
			m = first_m;
			object = first_object;
			offset = first_offset;

			/*
			 *	Now that we've gotten the copy out of the
			 *	way, let's try to collapse the top object.
			 */
			vm_object_lock(object);
			/*
			 *	But we have to play ugly games with
			 *	paging_in_progress to do that...
			 */
			object->paging_in_progress--;
			vm_object_collapse(object);
			object->paging_in_progress++;
		}
		else {
D 22
		    	prot &= (~VM_PROT_WRITE);
E 22
I 22
		    	prot &= ~VM_PROT_WRITE;
E 22
D 15
			m->copy_on_write = TRUE;
E 15
I 15
			m->flags |= PG_COPYONWRITE;
E 15
		}
	}

D 15
	if (m->active || m->inactive)
E 15
I 15
D 16
	if (m->flags & (PG_ACTIVE | PG_INACTIVE))
E 16
I 16
	if (m->flags & (PG_ACTIVE|PG_INACTIVE))
E 16
E 15
		panic("vm_fault: active or inactive before copy object handling");

	/*
	 *	If the page is being written, but hasn't been
	 *	copied to the copy-object, we have to copy it there.
	 */
    RetryCopy:
D 5
	if (first_object->copy != VM_OBJECT_NULL) {
		vm_object_t		copy_object = first_object->copy;
		vm_offset_t		copy_offset;
		vm_page_t		copy_m;
E 5
I 5
	if (first_object->copy != NULL) {
		vm_object_t copy_object = first_object->copy;
		vm_offset_t copy_offset;
		vm_page_t copy_m;
E 5

		/*
		 *	We only need to copy if we want to write it.
		 */
		if ((fault_type & VM_PROT_WRITE) == 0) {
			prot &= ~VM_PROT_WRITE;
D 15
			m->copy_on_write = TRUE;
E 15
I 15
			m->flags |= PG_COPYONWRITE;
E 15
		}
		else {
			/*
			 *	Try to get the lock on the copy_object.
			 */
			if (!vm_object_lock_try(copy_object)) {
				vm_object_unlock(object);
				/* should spin a bit here... */
				vm_object_lock(object);
				goto RetryCopy;
			}

			/*
			 *	Make another reference to the copy-object,
			 *	to keep it from disappearing during the
			 *	copy.
			 */
			copy_object->ref_count++;

			/*
			 *	Does the page exist in the copy?
			 */
			copy_offset = first_offset
				- copy_object->shadow_offset;
			copy_m = vm_page_lookup(copy_object, copy_offset);
D 5
			if (page_exists = (copy_m != VM_PAGE_NULL)) {
E 5
I 5
			if (page_exists = (copy_m != NULL)) {
E 5
D 15
				if (copy_m->busy) {
E 15
I 15
				if (copy_m->flags & PG_BUSY) {
E 15
#ifdef DOTHREADS
					int	wait_result;

					/*
					 *	If the page is being brought
					 *	in, wait for it and then retry.
					 */
					PAGE_ASSERT_WAIT(copy_m, !change_wiring);
					RELEASE_PAGE(m);
					copy_object->ref_count--;
					vm_object_unlock(copy_object);
					UNLOCK_THINGS;
					thread_block();
					wait_result = current_thread()->wait_result;
					vm_object_deallocate(first_object);
					if (wait_result != THREAD_AWAKENED)
						return(KERN_SUCCESS);
					goto RetryFault;
#else
					/*
					 *	If the page is being brought
					 *	in, wait for it and then retry.
					 */
					PAGE_ASSERT_WAIT(copy_m, !change_wiring);
					RELEASE_PAGE(m);
					copy_object->ref_count--;
					vm_object_unlock(copy_object);
					UNLOCK_THINGS;
					thread_block();
					vm_object_deallocate(first_object);
					goto RetryFault;
#endif
				}
			}

			/*
			 *	If the page is not in memory (in the object)
			 *	and the object has a pager, we have to check
			 *	if the pager has the data in secondary
			 *	storage.
			 */
			if (!page_exists) {

				/*
				 *	If we don't allocate a (blank) page
				 *	here... another thread could try
				 *	to page it in, allocate a page, and
				 *	then block on the busy page in its
				 *	shadow (first_object).  Then we'd
				 *	trip over the busy page after we
				 *	found that the copy_object's pager
				 *	doesn't have the page...
				 */
				copy_m = vm_page_alloc(copy_object,
								copy_offset);
D 5
				if (copy_m == VM_PAGE_NULL) {
E 5
I 5
				if (copy_m == NULL) {
E 5
					/*
					 *	Wait for a page, then retry.
					 */
					RELEASE_PAGE(m);
					copy_object->ref_count--;
					vm_object_unlock(copy_object);
					UNLOCK_AND_DEALLOCATE;
					VM_WAIT;
					goto RetryFault;
				}

D 5
			 	if (copy_object->pager != vm_pager_null) {
E 5
I 5
			 	if (copy_object->pager != NULL) {
E 5
					vm_object_unlock(object);
					vm_object_unlock(copy_object);
					UNLOCK_MAP;

					page_exists = vm_pager_has_page(
							copy_object->pager,
							(copy_offset + copy_object->paging_offset));

					vm_object_lock(copy_object);

					/*
					 * Since the map is unlocked, someone
					 * else could have copied this object
					 * and put a different copy_object
					 * between the two.  Or, the last
					 * reference to the copy-object (other
					 * than the one we have) may have
					 * disappeared - if that has happened,
					 * we don't need to make the copy.
					 */
					if (copy_object->shadow != object ||
					    copy_object->ref_count == 1) {
						/*
						 *	Gaah... start over!
						 */
						FREE_PAGE(copy_m);
						vm_object_unlock(copy_object);
						vm_object_deallocate(copy_object);
							/* may block */
						vm_object_lock(object);
						goto RetryCopy;
					}
					vm_object_lock(object);

					if (page_exists) {
						/*
						 *	We didn't need the page
						 */
						FREE_PAGE(copy_m);
					}
				}
			}
			if (!page_exists) {
				/*
				 *	Must copy page into copy-object.
				 */
				vm_page_copy(m, copy_m);
D 15
				copy_m->fake = FALSE;
				copy_m->absent = FALSE;
E 15
I 15
D 16
				copy_m->flags &= ~(PG_FAKE | PG_ABSENT);
E 16
I 16
				copy_m->flags &= ~PG_FAKE;
E 16
E 15

				/*
				 * Things to remember:
				 * 1. The copied page must be marked 'dirty'
				 *    so it will be paged out to the copy
				 *    object.
				 * 2. If the old page was in use by any users
				 *    of the copy-object, it must be removed
				 *    from all pmaps.  (We can't know which
				 *    pmaps use it.)
				 */
				vm_page_lock_queues();
D 6
				pmap_remove_all(VM_PAGE_TO_PHYS(old_m));
E 6
I 6
				pmap_page_protect(VM_PAGE_TO_PHYS(old_m),
						  VM_PROT_NONE);
E 6
D 15
				copy_m->clean = FALSE;
E 15
I 15
				copy_m->flags &= ~PG_CLEAN;
E 15
				vm_page_activate(copy_m);	/* XXX */
				vm_page_unlock_queues();

				PAGE_WAKEUP(copy_m);
			}
			/*
			 *	The reference count on copy_object must be
			 *	at least 2: one for our extra reference,
			 *	and at least one from the outside world
			 *	(we checked that when we last locked
			 *	copy_object).
			 */
			copy_object->ref_count--;
			vm_object_unlock(copy_object);
D 15
			m->copy_on_write = FALSE;
E 15
I 15
			m->flags &= ~PG_COPYONWRITE;
E 15
		}
	}

D 15
	if (m->active || m->inactive)
E 15
I 15
	if (m->flags & (PG_ACTIVE | PG_INACTIVE))
E 15
		panic("vm_fault: active or inactive before retrying lookup");

	/*
	 *	We must verify that the maps have not changed
	 *	since our last lookup.
	 */

	if (!lookup_still_valid) {
		vm_object_t	retry_object;
		vm_offset_t	retry_offset;
		vm_prot_t	retry_prot;

		/*
		 *	Since map entries may be pageable, make sure we can
		 *	take a page fault on them.
		 */
		vm_object_unlock(object);

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
				fault_type & ~VM_PROT_WRITE, &entry,
				&retry_object, &retry_offset, &retry_prot,
				&wired, &su);

		vm_object_lock(object);

		/*
		 *	If we don't need the page any longer, put it on the
		 *	active list (the easiest thing to do here).  If no
		 *	one needs it, pageout will grab it eventually.
		 */

		if (result != KERN_SUCCESS) {
			RELEASE_PAGE(m);
			UNLOCK_AND_DEALLOCATE;
			return(result);
		}

		lookup_still_valid = TRUE;

		if ((retry_object != first_object) ||
				(retry_offset != first_offset)) {
			RELEASE_PAGE(m);
			UNLOCK_AND_DEALLOCATE;
			goto RetryFault;
		}

		/*
		 *	Check whether the protection has changed or the object
		 *	has been copied while we left the map unlocked.
		 *	Changing from read to write permission is OK - we leave
		 *	the page write-protected, and catch the write fault.
		 *	Changing from write to read permission means that we
		 *	can't mark the page write-enabled after all.
		 */
		prot &= retry_prot;
D 15
		if (m->copy_on_write)
E 15
I 15
		if (m->flags & PG_COPYONWRITE)
E 15
			prot &= ~VM_PROT_WRITE;
	}

	/*
	 * (the various bits we're fiddling with here are locked by
	 * the object's lock)
	 */

	/* XXX This distorts the meaning of the copy_on_write bit */

	if (prot & VM_PROT_WRITE)
D 15
		m->copy_on_write = FALSE;
E 15
I 15
		m->flags &= ~PG_COPYONWRITE;
E 15

	/*
	 *	It's critically important that a wired-down page be faulted
	 *	only once in each map for which it is wired.
	 */

D 15
	if (m->active || m->inactive)
E 15
I 15
	if (m->flags & (PG_ACTIVE | PG_INACTIVE))
E 15
		panic("vm_fault: active or inactive before pmap_enter");

	vm_object_unlock(object);

	/*
	 *	Put this page into the physical map.
	 *	We had to do the unlock above because pmap_enter
	 *	may cause other faults.   We don't put the
	 *	page back on the active queue until later so
	 *	that the page-out daemon won't find us (yet).
	 */

D 16
	pmap_enter(map->pmap, vaddr, VM_PAGE_TO_PHYS(m), 
			prot & ~(m->page_lock), wired);
E 16
I 16
	pmap_enter(map->pmap, vaddr, VM_PAGE_TO_PHYS(m), prot, wired);
E 16

	/*
	 *	If the page is not wired down, then put it where the
	 *	pageout daemon can find it.
	 */
	vm_object_lock(object);
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

	PAGE_WAKEUP(m);
	UNLOCK_AND_DEALLOCATE;

	return(KERN_SUCCESS);

}

/*
 *	vm_fault_wire:
 *
 *	Wire down a range of virtual addresses in a map.
 */
D 17
void vm_fault_wire(map, start, end)
E 17
I 17
int
vm_fault_wire(map, start, end)
E 17
	vm_map_t	map;
	vm_offset_t	start, end;
{
D 17

E 17
	register vm_offset_t	va;
	register pmap_t		pmap;
I 17
	int			rv;
E 17

	pmap = vm_map_pmap(map);

	/*
	 *	Inform the physical mapping system that the
	 *	range of addresses may not fault, so that
	 *	page tables and such can be locked down as well.
	 */

	pmap_pageable(pmap, start, end, FALSE);

	/*
	 *	We simulate a fault to get the page and enter it
	 *	in the physical map.
	 */

	for (va = start; va < end; va += PAGE_SIZE) {
D 17
		(void) vm_fault(map, va, VM_PROT_NONE, TRUE);
E 17
I 17
		rv = vm_fault(map, va, VM_PROT_NONE, TRUE);
		if (rv) {
			if (va != start)
				vm_fault_unwire(map, start, va);
			return(rv);
		}
E 17
	}
I 17
	return(KERN_SUCCESS);
E 17
}


/*
 *	vm_fault_unwire:
 *
 *	Unwire a range of virtual addresses in a map.
 */
D 23
void vm_fault_unwire(map, start, end)
E 23
I 23
void
vm_fault_unwire(map, start, end)
E 23
	vm_map_t	map;
	vm_offset_t	start, end;
{

	register vm_offset_t	va, pa;
	register pmap_t		pmap;

	pmap = vm_map_pmap(map);

	/*
	 *	Since the pages are wired down, we must be able to
	 *	get their mappings from the physical map system.
	 */

	vm_page_lock_queues();

	for (va = start; va < end; va += PAGE_SIZE) {
		pa = pmap_extract(pmap, va);
		if (pa == (vm_offset_t) 0) {
			panic("unwire: page not in pmap");
		}
		pmap_change_wiring(pmap, va, FALSE);
		vm_page_unwire(PHYS_TO_VM_PAGE(pa));
	}
	vm_page_unlock_queues();

	/*
	 *	Inform the physical mapping system that the range
	 *	of addresses may fault, so that page tables and
	 *	such may be unwired themselves.
	 */

	pmap_pageable(pmap, start, end, TRUE);

}

/*
 *	Routine:
 *		vm_fault_copy_entry
 *	Function:
 *		Copy all of the pages from a wired-down map entry to another.
 *
 *	In/out conditions:
 *		The source and destination maps must be locked for write.
 *		The source map entry must be wired down (or be a sharing map
 *		entry corresponding to a main map entry that is wired down).
 */

D 23
void vm_fault_copy_entry(dst_map, src_map, dst_entry, src_entry)
E 23
I 23
void
vm_fault_copy_entry(dst_map, src_map, dst_entry, src_entry)
E 23
	vm_map_t	dst_map;
	vm_map_t	src_map;
	vm_map_entry_t	dst_entry;
	vm_map_entry_t	src_entry;
{

	vm_object_t	dst_object;
	vm_object_t	src_object;
	vm_offset_t	dst_offset;
	vm_offset_t	src_offset;
	vm_prot_t	prot;
	vm_offset_t	vaddr;
	vm_page_t	dst_m;
	vm_page_t	src_m;

#ifdef	lint
	src_map++;
D 18
#endif	lint
E 18
I 18
#endif
E 18

	src_object = src_entry->object.vm_object;
	src_offset = src_entry->offset;

	/*
	 *	Create the top-level object for the destination entry.
	 *	(Doesn't actually shadow anything - we copy the pages
	 *	directly.)
	 */
	dst_object = vm_object_allocate(
			(vm_size_t) (dst_entry->end - dst_entry->start));

	dst_entry->object.vm_object = dst_object;
	dst_entry->offset = 0;

	prot  = dst_entry->max_protection;

	/*
	 *	Loop through all of the pages in the entry's range, copying
	 *	each one from the source object (it should be there) to the
	 *	destination object.
	 */
	for (vaddr = dst_entry->start, dst_offset = 0;
	     vaddr < dst_entry->end;
	     vaddr += PAGE_SIZE, dst_offset += PAGE_SIZE) {

		/*
		 *	Allocate a page in the destination object
		 */
		vm_object_lock(dst_object);
		do {
			dst_m = vm_page_alloc(dst_object, dst_offset);
D 5
			if (dst_m == VM_PAGE_NULL) {
E 5
I 5
			if (dst_m == NULL) {
E 5
				vm_object_unlock(dst_object);
				VM_WAIT;
				vm_object_lock(dst_object);
			}
D 5
		} while (dst_m == VM_PAGE_NULL);
E 5
I 5
		} while (dst_m == NULL);
E 5

		/*
		 *	Find the page in the source object, and copy it in.
		 *	(Because the source is wired down, the page will be
		 *	in memory.)
		 */
		vm_object_lock(src_object);
		src_m = vm_page_lookup(src_object, dst_offset + src_offset);
D 5
		if (src_m == VM_PAGE_NULL)
E 5
I 5
		if (src_m == NULL)
E 5
			panic("vm_fault_copy_wired: page missing");

		vm_page_copy(src_m, dst_m);

		/*
		 *	Enter it in the pmap...
		 */
		vm_object_unlock(src_object);
		vm_object_unlock(dst_object);

		pmap_enter(dst_map->pmap, vaddr, VM_PAGE_TO_PHYS(dst_m),
				prot, FALSE);

		/*
		 *	Mark it no longer busy, and put it on the active list.
		 */
		vm_object_lock(dst_object);
		vm_page_lock_queues();
		vm_page_activate(dst_m);
		vm_page_unlock_queues();
		PAGE_WAKEUP(dst_m);
		vm_object_unlock(dst_object);
	}

}
E 1
