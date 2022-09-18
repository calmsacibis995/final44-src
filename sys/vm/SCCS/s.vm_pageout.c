h46991
s 00004/00000/00541
d D 8.7 95/06/19 11:42:54 mckusick 18 17
c have to unlock object and page queues before sleeping
e
s 00007/00007/00534
d D 8.6 95/01/09 17:50:26 cgd 17 16
c KNF, and 64-bit safety.
e
s 00001/00001/00540
d D 8.5 94/02/14 09:18:21 hibler 16 15
c null pointer test (from Ralph)
e
s 00314/00098/00227
d D 8.4 94/01/12 16:03:15 hibler 15 14
c prototype clustered pageout interface,
c keep vmmeter stats.
e
s 00006/00019/00319
d D 8.3 93/12/30 16:01:27 mckusick 14 13
c convert to use new queue structures
e
s 00002/00001/00336
d D 8.2 93/11/10 10:58:29 torek 13 12
c finish up new device pager: all pagers get offsets
e
s 00002/00002/00335
d D 8.1 93/06/11 16:38:20 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00000/00331
d D 7.11 93/06/02 11:10:08 hibler 11 10
c hack: initialize vm_page_max_wired (max wired user memory) for mlock
e
s 00132/00154/00199
d D 7.10 92/11/29 10:21:32 hibler 10 9
c mach 2.5/3.0 inspired changes:
c 1. dynamically compute inactive_target before each invokation of
c    vm_pageout_scan (as a function of current active/inactive pages)
c 2. make inactive_target larger to improve chances of reclaim and
c    provide a better approximation of LRU
c 3. allow dirty pages to be reclaimed
c 4. correct computation of page_shortage to avoid excess wakeups
c    from vm_page_alloc
c also some basic code cleanup
e
s 00007/00007/00346
d D 7.9 92/10/01 17:54:25 mckusick 9 8
c convert vm_page bit fields to flags
e
s 00001/00000/00352
d D 7.8 92/09/21 21:45:13 hibler 8 7
c be prepared to handle VM_PAGER_ERROR
e
s 00005/00004/00347
d D 7.7 92/05/04 17:25:12 bostic 7 6
c new include format; lint
e
s 00024/00024/00327
d D 7.6 91/08/28 15:47:52 mckusick 6 5
c vm_stat is merged into vmmeter structure
e
s 00023/00033/00328
d D 7.5 91/07/25 23:03:04 mckusick 5 4
c numerous statistics move to vm_stat
e
s 00013/00008/00348
d D 7.4 91/05/07 09:35:38 hibler 4 3
c keep page frame marked busy while in a pager
c pmap_remove_all -> pmap_page_protect
e
s 00027/00004/00329
d D 7.3 91/04/21 18:36:20 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00007/00009/00326
d D 7.2 91/04/20 10:50:20 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00335/00000/00000
d D 7.1 90/12/05 18:08:28 mckusick 1 0
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
 *	The proverbial page-out daemon.
 */

D 2
#include "types.h"
#include "../vm/vm_page.h"
#include "../vm/pmap.h"
#include "../vm/vm_object.h"
#include "../vm/vm_pageout.h"
#include "../vm/vm_statistics.h"
#include "../vm/vm_param.h"
E 2
I 2
D 7
#include "param.h"
E 7
I 7
#include <sys/param.h>
E 7
E 2

I 2
D 7
#include "vm.h"
#include "vm_page.h"
#include "vm_pageout.h"
E 7
I 7
#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_pageout.h>
E 7

E 2
D 5
int	vm_pages_needed;		/* Event on which pageout daemon sleeps */
int	vm_pageout_free_min = 0;	/* Stop pageout to wait for pagers at this free level */
E 5
I 5
D 15
int	vm_pages_needed;	/* Event on which pageout daemon sleeps */
E 15
I 15
#ifndef VM_PAGE_FREE_MIN
#define VM_PAGE_FREE_MIN	(cnt.v_free_count / 20)
#endif
E 15
E 5

D 15
int	vm_page_free_min_sanity = 40;
E 15
I 15
#ifndef VM_PAGE_FREE_TARGET
#define VM_PAGE_FREE_TARGET	((cnt.v_free_min * 4) / 3)
#endif
E 15

I 15
int	vm_page_free_min_min = 16 * 1024;
int	vm_page_free_min_max = 256 * 1024;

int	vm_pages_needed;	/* Event on which pageout daemon sleeps */

E 15
I 11
int	vm_page_max_wired = 0;	/* XXX max # of wired pages system-wide */

I 15
#ifdef CLUSTERED_PAGEOUT
#define MAXPOCLUSTER		(MAXPHYS/NBPG)	/* XXX */
int doclustered_pageout = 1;
#endif

E 15
E 11
/*
 *	vm_pageout_scan does the dirty work for the pageout daemon.
 */
I 7
void
E 7
vm_pageout_scan()
{
D 14
	register vm_page_t	m;
E 14
I 14
	register vm_page_t	m, next;
E 14
	register int		page_shortage;
	register int		s;
	register int		pages_freed;
	int			free;
I 15
	vm_object_t		object;
E 15

	/*
	 *	Only continue when we want more pages to be "free"
	 */

I 15
	cnt.v_rev++;

E 15
	s = splimp();
	simple_lock(&vm_page_queue_free_lock);
D 5
	free = vm_page_free_count;
E 5
I 5
D 6
	free = vm_stat.free_count;
E 6
I 6
	free = cnt.v_free_count;
E 6
E 5
	simple_unlock(&vm_page_queue_free_lock);
	splx(s);

D 5
	if (free < vm_page_free_target) {
E 5
I 5
D 6
	if (free < vm_stat.free_target) {
E 6
I 6
	if (free < cnt.v_free_target) {
E 6
E 5
		swapout_threads();

		/*
		 *	Be sure the pmap system is updated so
		 *	we can scan the inactive queue.
		 */

		pmap_update();
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
D 14
	m = (vm_page_t) queue_first(&vm_page_queue_inactive);
	while (!queue_end(&vm_page_queue_inactive, (queue_entry_t) m)) {
D 10
		vm_page_t	next;
E 10
I 10
		vm_page_t next;
E 14
I 14
	for (m = vm_page_queue_inactive.tqh_first; m != NULL; m = next) {
E 14
D 15
		vm_object_t object;
		vm_pager_t pager;
		int pageout_status;
E 10

I 14
		next = m->pageq.tqe_next;
E 15
E 14
		s = splimp();
		simple_lock(&vm_page_queue_free_lock);
D 5
		free = vm_page_free_count;
E 5
I 5
D 6
		free = vm_stat.free_count;
E 6
I 6
		free = cnt.v_free_count;
E 6
E 5
		simple_unlock(&vm_page_queue_free_lock);
		splx(s);
D 15

E 15
D 5
		if (free >= vm_page_free_target)
E 5
I 5
D 6
		if (free >= vm_stat.free_target)
E 6
I 6
		if (free >= cnt.v_free_target)
E 6
E 5
			break;

I 15
		cnt.v_scan++;
		next = m->pageq.tqe_next;

E 15
I 10
		/*
		 * If the page has been referenced, move it back to the
		 * active queue.
		 */
		if (pmap_is_referenced(VM_PAGE_TO_PHYS(m))) {
D 14
			next = (vm_page_t) queue_next(&m->pageq);
E 14
			vm_page_activate(m);
			cnt.v_reactivated++;
D 14
			m = next;
E 14
			continue;
		}

		/*
		 * If the page is clean, free it up.
		 */
E 10
D 9
		if (m->clean) {
E 9
I 9
		if (m->flags & PG_CLEAN) {
E 9
D 14
			next = (vm_page_t) queue_next(&m->pageq);
E 14
D 10
			if (pmap_is_referenced(VM_PAGE_TO_PHYS(m))) {
				vm_page_activate(m);
D 6
				vm_stat.reactivations++;
E 6
I 6
				cnt.v_reactivated++;
E 6
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
E 10
I 10
			object = m->object;
			if (vm_object_lock_try(object)) {
E 10
D 4
				pmap_remove_all(VM_PAGE_TO_PHYS(m));
E 4
I 4
				pmap_page_protect(VM_PAGE_TO_PHYS(m),
						  VM_PROT_NONE);
E 4
D 10
				vm_page_free(m);	/* will dequeue */
E 10
I 10
				vm_page_free(m);
E 10
				pages_freed++;
I 15
				cnt.v_dfree++;
E 15
				vm_object_unlock(object);
			}
D 14
			m = next;
E 14
I 10
			continue;
E 10
		}
D 10
		else {
			/*
			 *	If a page is dirty, then it is either
			 *	being washed (but not yet cleaned)
			 *	or it is still in the laundry.  If it is
			 *	still in the laundry, then we start the
			 *	cleaning operation.
			 */
E 10

D 9
			if (m->laundry) {
E 9
I 9
D 10
			if (m->flags & PG_LAUNDRY) {
E 9
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
E 10
I 10
		/*
		 * If the page is dirty but already being washed, skip it.
		 */
D 14
		if ((m->flags & PG_LAUNDRY) == 0) {
			m = (vm_page_t) queue_next(&m->pageq);
E 14
I 14
		if ((m->flags & PG_LAUNDRY) == 0)
E 14
			continue;
D 14
		}
E 14
E 10

D 10
				register vm_object_t	object;
				register vm_pager_t	pager;
				int			pageout_status;
E 10
I 10
		/*
		 * Otherwise the page is dirty and still in the laundry,
		 * so we start the cleaning operation and remove it from
		 * the laundry.
D 15
		 *
		 * We set the busy bit to cause potential page faults on
		 * this page to block.
		 *
		 * We also set pageout-in-progress to keep the object from
		 * disappearing during pageout.  This guarantees that the
		 * page won't move from the inactive queue.  (However, any
		 * other page on the inactive queue may move!)
E 15
		 */
		object = m->object;
D 14
		if (!vm_object_lock_try(object)) {
			m = (vm_page_t) queue_next(&m->pageq);
E 14
I 14
		if (!vm_object_lock_try(object))
E 14
			continue;
D 14
		}
E 14
D 15
		pmap_page_protect(VM_PAGE_TO_PHYS(m), VM_PROT_NONE);
		m->flags |= PG_BUSY;
E 15
		cnt.v_pageouts++;
I 15
#ifdef CLUSTERED_PAGEOUT
		if (object->pager &&
		    vm_pager_cancluster(object->pager, PG_CLUSTERPUT))
			vm_pageout_cluster(m, object);
		else
#endif
		vm_pageout_page(m, object);
D 17
		thread_wakeup((int) object);
E 17
I 17
		thread_wakeup(object);
E 17
		vm_object_unlock(object);
		/*
		 * Former next page may no longer even be on the inactive
		 * queue (due to potential blocking in the pager with the
		 * queues unlocked).  If it isn't, we just start over.
		 */
D 16
		if ((next->flags & PG_INACTIVE) == 0)
E 16
I 16
		if (next && (next->flags & PG_INACTIVE) == 0)
E 16
			next = vm_page_queue_inactive.tqh_first;
	}
	
	/*
	 *	Compute the page shortage.  If we are still very low on memory
	 *	be sure that we will move a minimal amount of pages from active
	 *	to inactive.
	 */
E 15
E 10

I 15
	page_shortage = cnt.v_inactive_target - cnt.v_inactive_count;
	if (page_shortage <= 0 && pages_freed == 0)
		page_shortage = 1;

	while (page_shortage > 0) {
E 15
D 10
				object = m->object;
				if (!vm_object_lock_try(object)) {
					/*
					 *	Skip page if we can't lock
					 *	its object
					 */
					m = (vm_page_t) queue_next(&m->pageq);
					continue;
				}
E 10
I 10
		/*
D 15
		 * Try to collapse the object before making a pager for it.
		 * We must unlock the page queues first.
E 15
I 15
		 *	Move some more pages from active to inactive.
E 15
		 */
D 15
		vm_page_unlock_queues();
E 15
I 15

		if ((m = vm_page_queue_active.tqh_first) == NULL)
			break;
		vm_page_deactivate(m);
		page_shortage--;
	}

	vm_page_unlock_queues();
}

/*
 * Called with object and page queues locked.
 * If reactivate is TRUE, a pager error causes the page to be
 * put back on the active queue, ow it is left on the inactive queue.
 */
void
vm_pageout_page(m, object)
	vm_page_t m;
	vm_object_t object;
{
	vm_pager_t pager;
	int pageout_status;

	/*
	 * We set the busy bit to cause potential page faults on
	 * this page to block.
	 *
	 * We also set pageout-in-progress to keep the object from
	 * disappearing during pageout.  This guarantees that the
	 * page won't move from the inactive queue.  (However, any
	 * other page on the inactive queue may move!)
	 */
	pmap_page_protect(VM_PAGE_TO_PHYS(m), VM_PROT_NONE);
	m->flags |= PG_BUSY;

	/*
	 * Try to collapse the object before making a pager for it.
	 * We must unlock the page queues first.
	 */
	vm_page_unlock_queues();
	if (object->pager == NULL)
E 15
		vm_object_collapse(object);
E 10

D 4
				pmap_remove_all(VM_PAGE_TO_PHYS(m));
E 4
I 4
D 10
				pmap_page_protect(VM_PAGE_TO_PHYS(m),
						  VM_PROT_NONE);
E 4
D 9
				m->busy = TRUE;
E 9
I 9
				m->flags |= PG_BUSY;
E 9
D 6
				vm_stat.pageouts++;
E 6
I 6
				cnt.v_pageouts++;
E 10
I 10
D 15
		object->paging_in_progress++;
		vm_object_unlock(object);
E 15
I 15
	object->paging_in_progress++;
	vm_object_unlock(object);
E 15
E 10
E 6

I 15
	/*
	 * Do a wakeup here in case the following operations block.
	 */
D 17
	thread_wakeup((int) &cnt.v_free_count);
E 17
I 17
	thread_wakeup(&cnt.v_free_count);
E 17

	/*
	 * If there is no pager for the page, use the default pager.
	 * If there is no place to put the page at the moment,
	 * leave it in the laundry and hope that there will be
	 * paging space later.
	 */
	if ((pager = object->pager) == NULL) {
		pager = vm_pager_allocate(PG_DFLT, (caddr_t)0, object->size,
					  VM_PROT_ALL, (vm_offset_t)0);
		if (pager != NULL)
			vm_object_setpager(object, pager, 0, FALSE);
	}
	pageout_status = pager ? vm_pager_put(pager, m, FALSE) : VM_PAGER_FAIL;
	vm_object_lock(object);
	vm_page_lock_queues();

	switch (pageout_status) {
	case VM_PAGER_OK:
	case VM_PAGER_PEND:
		cnt.v_pgpgout++;
		m->flags &= ~PG_LAUNDRY;
		break;
	case VM_PAGER_BAD:
E 15
D 10
				/*
				 *	Try to collapse the object before
				 *	making a pager for it.  We must
				 *	unlock the page queues first.
				 */
				vm_page_unlock_queues();
E 10
I 10
		/*
D 15
		 * Do a wakeup here in case the following operations block.
E 15
I 15
		 * Page outside of range of object.  Right now we
		 * essentially lose the changes by pretending it
		 * worked.
		 *
		 * XXX dubious, what should we do?
E 15
		 */
D 15
		thread_wakeup((int) &cnt.v_free_count);
E 15
I 15
		m->flags &= ~PG_LAUNDRY;
		m->flags |= PG_CLEAN;
		pmap_clear_modify(VM_PAGE_TO_PHYS(m));
		break;
	case VM_PAGER_AGAIN:
	{
		extern int lbolt;
E 15
E 10

D 10
				vm_object_collapse(object);
E 10
I 10
		/*
D 15
		 * If there is no pager for the page, use the default pager.
		 * If there is no place to put the page at the moment,
		 * leave it in the laundry and hope that there will be
		 * paging space later.
E 15
I 15
		 * FAIL on a write is interpreted to mean a resource
		 * shortage, so we put pause for awhile and try again.
		 * XXX could get stuck here.
E 15
		 */
I 18
		vm_page_unlock_queues();
		vm_object_unlock(object);
E 18
D 15
		if ((pager = object->pager) == NULL) {
			pager = vm_pager_allocate(PG_DFLT, (caddr_t)0,
D 13
						  object->size, VM_PROT_ALL);
E 13
I 13
						  object->size, VM_PROT_ALL,
						  (vm_offset_t)0);
E 13
			if (pager != NULL)
				vm_object_setpager(object, pager, 0, FALSE);
		}
		pageout_status = pager ?
			vm_pager_put(pager, m, FALSE) : VM_PAGER_FAIL;
		vm_object_lock(object);
		vm_page_lock_queues();
E 15
I 15
		(void) tsleep((caddr_t)&lbolt, PZERO|PCATCH, "pageout", 0);
I 18
		vm_object_lock(object);
		vm_page_lock_queues();
E 18
		break;
	}
	case VM_PAGER_FAIL:
	case VM_PAGER_ERROR:
		/*
		 * If page couldn't be paged out, then reactivate
		 * the page so it doesn't clog the inactive list.
		 * (We will try paging out it again later).
		 */
		vm_page_activate(m);
		cnt.v_reactivated++;
		break;
	}
E 15
D 14
		next = (vm_page_t) queue_next(&m->pageq);
E 14
E 10

D 10
				object->paging_in_progress++;
				vm_object_unlock(object);
E 10
I 10
D 15
		switch (pageout_status) {
E 15
I 15
	pmap_clear_reference(VM_PAGE_TO_PHYS(m));

	/*
	 * If the operation is still going, leave the page busy
	 * to block all other accesses.  Also, leave the paging
	 * in progress indicator set so that we don't attempt an
	 * object collapse.
	 */
	if (pageout_status != VM_PAGER_PEND) {
		m->flags &= ~PG_BUSY;
		PAGE_WAKEUP(m);
		object->paging_in_progress--;
	}
}

#ifdef CLUSTERED_PAGEOUT
#define PAGEOUTABLE(p) \
	((((p)->flags & (PG_INACTIVE|PG_CLEAN|PG_LAUNDRY)) == \
	  (PG_INACTIVE|PG_LAUNDRY)) && !pmap_is_referenced(VM_PAGE_TO_PHYS(p)))

/*
 * Attempt to pageout as many contiguous (to ``m'') dirty pages as possible
 * from ``object''.  Using information returned from the pager, we assemble
 * a sorted list of contiguous dirty pages and feed them to the pager in one
 * chunk.  Called with paging queues and object locked.  Also, object must
 * already have a pager.
 */
void
vm_pageout_cluster(m, object)
	vm_page_t m;
	vm_object_t object;
{
	vm_offset_t offset, loff, hoff;
	vm_page_t plist[MAXPOCLUSTER], *plistp, p;
	int postatus, ix, count;

	/*
	 * Determine the range of pages that can be part of a cluster
	 * for this object/offset.  If it is only our single page, just
	 * do it normally.
	 */
	vm_pager_cluster(object->pager, m->offset, &loff, &hoff);
	if (hoff - loff == PAGE_SIZE) {
		vm_pageout_page(m, object);
		return;
	}

	plistp = plist;

	/*
	 * Target page is always part of the cluster.
	 */
	pmap_page_protect(VM_PAGE_TO_PHYS(m), VM_PROT_NONE);
	m->flags |= PG_BUSY;
	plistp[atop(m->offset - loff)] = m;
	count = 1;

	/*
	 * Backup from the given page til we find one not fulfilling
	 * the pageout criteria or we hit the lower bound for the
	 * cluster.  For each page determined to be part of the
	 * cluster, unmap it and busy it out so it won't change.
	 */
	ix = atop(m->offset - loff);
	offset = m->offset;
	while (offset > loff && count < MAXPOCLUSTER-1) {
		p = vm_page_lookup(object, offset - PAGE_SIZE);
		if (p == NULL || !PAGEOUTABLE(p))
			break;
		pmap_page_protect(VM_PAGE_TO_PHYS(p), VM_PROT_NONE);
		p->flags |= PG_BUSY;
		plistp[--ix] = p;
		offset -= PAGE_SIZE;
		count++;
	}
	plistp += atop(offset - loff);
	loff = offset;

	/*
	 * Now do the same moving forward from the target.
	 */
	ix = atop(m->offset - loff) + 1;
	offset = m->offset + PAGE_SIZE;
	while (offset < hoff && count < MAXPOCLUSTER) {
		p = vm_page_lookup(object, offset);
		if (p == NULL || !PAGEOUTABLE(p))
			break;
		pmap_page_protect(VM_PAGE_TO_PHYS(p), VM_PROT_NONE);
		p->flags |= PG_BUSY;
		plistp[ix++] = p;
		offset += PAGE_SIZE;
		count++;
	}
	hoff = offset;

	/*
	 * Pageout the page.
	 * Unlock everything and do a wakeup prior to the pager call
	 * in case it blocks.
	 */
	vm_page_unlock_queues();
	object->paging_in_progress++;
	vm_object_unlock(object);
again:
D 17
	thread_wakeup((int) &cnt.v_free_count);
E 17
I 17
	thread_wakeup(&cnt.v_free_count);
E 17
	postatus = vm_pager_put_pages(object->pager, plistp, count, FALSE);
	/*
	 * XXX rethink this
	 */
	if (postatus == VM_PAGER_AGAIN) {
		extern int lbolt;

		(void) tsleep((caddr_t)&lbolt, PZERO|PCATCH, "pageout", 0);
		goto again;
	} else if (postatus == VM_PAGER_BAD)
		panic("vm_pageout_cluster: VM_PAGER_BAD");
	vm_object_lock(object);
	vm_page_lock_queues();

	/*
	 * Loop through the affected pages, reflecting the outcome of
	 * the operation.
	 */
	for (ix = 0; ix < count; ix++) {
		p = *plistp++;
		switch (postatus) {
E 15
		case VM_PAGER_OK:
		case VM_PAGER_PEND:
D 15
			m->flags &= ~PG_LAUNDRY;
E 15
I 15
			cnt.v_pgpgout++;
			p->flags &= ~PG_LAUNDRY;
E 15
			break;
D 15
		case VM_PAGER_BAD:
			/*
			 * Page outside of range of object.  Right now we
			 * essentially lose the changes by pretending it
			 * worked.
			 *
			 * XXX dubious, what should we do?
			 */
			m->flags &= ~PG_LAUNDRY;
			m->flags |= PG_CLEAN;
			pmap_clear_modify(VM_PAGE_TO_PHYS(m));
			break;
E 15
		case VM_PAGER_FAIL:
		case VM_PAGER_ERROR:
			/*
D 15
			 * If page couldn't be paged out, then reactivate
			 * the page so it doesn't clog the inactive list.
			 * (We will try paging out it again later).
E 15
I 15
			 * Pageout failed, reactivate the target page so it
			 * doesn't clog the inactive list.  Other pages are
			 * left as they are.
E 15
			 */
D 15
			vm_page_activate(m);
E 15
I 15
			if (p == m) {
				vm_page_activate(p);
				cnt.v_reactivated++;
			}
E 15
			break;
		}
E 10
D 15

D 10
				/*
				 *	Do a wakeup here in case the following
				 *	operations block.
				 */
D 5
				thread_wakeup((int) &vm_page_free_count);
E 5
I 5
D 6
				thread_wakeup((int) &vm_stat.free_count);
E 6
I 6
				thread_wakeup((int) &cnt.v_free_count);
E 10
I 10
		pmap_clear_reference(VM_PAGE_TO_PHYS(m));
E 10
E 6
E 5

E 15
I 15
		pmap_clear_reference(VM_PAGE_TO_PHYS(p));
E 15
D 10
				/*
				 *	If there is no pager for the page,
				 *	use the default pager.  If there's
				 *	no place to put the page at the
				 *	moment, leave it in the laundry and
				 *	hope that there will be paging space
				 *	later.
				 */

D 2
				if ((pager = object->pager) == vm_pager_null) {
E 2
I 2
				if ((pager = object->pager) == NULL) {
E 2
					pager = vm_pager_allocate(PG_DFLT,
								  (caddr_t)0,
								  object->size,
								  VM_PROT_ALL);
D 2
					if (pager != vm_pager_null) {
E 2
I 2
					if (pager != NULL) {
E 2
						vm_object_setpager(object,
							pager, 0, FALSE);
					}
				}
				pageout_status = pager ?
					vm_pager_put(pager, m, FALSE) :
					VM_PAGER_FAIL;
				vm_object_lock(object);
				vm_page_lock_queues();
				next = (vm_page_t) queue_next(&m->pageq);

				switch (pageout_status) {
				case VM_PAGER_OK:
				case VM_PAGER_PEND:
D 9
					m->laundry = FALSE;
E 9
I 9
					m->flags &= ~PG_LAUNDRY;
E 9
					break;
				case VM_PAGER_BAD:
					/*
					 * Page outside of range of object.
					 * Right now we essentially lose the
					 * changes by pretending it worked.
					 * XXX dubious, what should we do?
					 */
D 9
					m->laundry = FALSE;
					m->clean = TRUE;
E 9
I 9
					m->flags &= ~PG_LAUNDRY;
					m->flags |= PG_CLEAN;
E 9
					pmap_clear_modify(VM_PAGE_TO_PHYS(m));
					break;
				case VM_PAGER_FAIL:
I 8
				case VM_PAGER_ERROR:
E 8
					/*
					 * If page couldn't be paged out, then
					 * reactivate the page so it doesn't
					 * clog the inactive list.  (We will
					 * try paging out it again later).
					 */
					vm_page_activate(m);
					break;
				}

				pmap_clear_reference(VM_PAGE_TO_PHYS(m));
D 4
				m->busy = FALSE;
				PAGE_WAKEUP(m);
E 4

				/*
D 4
				 * If the operation is still going, leave the
				 * paging in progress indicator set so that we
				 * don't attempt an object collapse.
E 4
I 4
				 * If the operation is still going, leave
				 * the page busy to block all other accesses.
				 * Also, leave the paging in progress
				 * indicator set so that we don't attempt an
				 * object collapse.
E 4
				 */
D 4
				if (pageout_status != VM_PAGER_PEND)
E 4
I 4
				if (pageout_status != VM_PAGER_PEND) {
D 9
					m->busy = FALSE;
E 9
I 9
					m->flags &= ~PG_BUSY;
E 9
					PAGE_WAKEUP(m);
E 4
					object->paging_in_progress--;
I 4
				}
E 4
				thread_wakeup((int) object);
				vm_object_unlock(object);
				m = next;
			}
			else
				m = (vm_page_t) queue_next(&m->pageq);
E 10
I 10
		/*
		 * If the operation is still going, leave the page busy
D 15
		 * to block all other accesses.  Also, leave the paging
		 * in progress indicator set so that we don't attempt an
		 * object collapse.
E 15
I 15
		 * to block all other accesses.
E 15
		 */
D 15
		if (pageout_status != VM_PAGER_PEND) {
			m->flags &= ~PG_BUSY;
			PAGE_WAKEUP(m);
			object->paging_in_progress--;
E 15
I 15
		if (postatus != VM_PAGER_PEND) {
			p->flags &= ~PG_BUSY;
			PAGE_WAKEUP(p);

E 15
E 10
		}
I 10
D 15
		thread_wakeup((int) object);
		vm_object_unlock(object);
E 15
D 14
		m = next;
E 14
E 10
	}
D 15
	
E 15
	/*
D 15
	 *	Compute the page shortage.  If we are still very low on memory
	 *	be sure that we will move a minimal amount of pages from active
	 *	to inactive.
E 15
I 15
	 * If the operation is still going, leave the paging in progress
	 * indicator set so that we don't attempt an object collapse.
E 15
	 */
I 15
	if (postatus != VM_PAGER_PEND)
		object->paging_in_progress--;
E 15

D 5
	page_shortage = vm_page_inactive_target - vm_page_inactive_count;
	page_shortage -= vm_page_free_count;
E 5
I 5
D 6
	page_shortage = vm_stat.inactive_target - vm_stat.inactive_count;
	page_shortage -= vm_stat.free_count;
E 6
I 6
D 15
	page_shortage = cnt.v_inactive_target - cnt.v_inactive_count;
D 10
	page_shortage -= cnt.v_free_count;
E 6
E 5

	if ((page_shortage <= 0) && (pages_freed == 0))
E 10
I 10
	if (page_shortage <= 0 && pages_freed == 0)
E 10
		page_shortage = 1;

	while (page_shortage > 0) {
		/*
		 *	Move some more pages from active to inactive.
		 */

D 14
		if (queue_empty(&vm_page_queue_active)) {
E 14
I 14
		if ((m = vm_page_queue_active.tqh_first) == NULL)
E 14
			break;
D 14
		}
		m = (vm_page_t) queue_first(&vm_page_queue_active);
E 14
		vm_page_deactivate(m);
		page_shortage--;
	}

	vm_page_unlock_queues();
E 15
}
I 15
#endif
E 15

/*
 *	vm_pageout is the high level pageout daemon.
 */

D 17
void vm_pageout()
E 17
I 17
void
vm_pageout()
E 17
{
	(void) spl0();

	/*
	 *	Initialize some paging parameters.
	 */

D 5
	if (vm_page_free_min == 0) {
		vm_page_free_min = vm_page_free_count / 20;
		if (vm_page_free_min < 3)
			vm_page_free_min = 3;
E 5
I 5
D 6
	if (vm_stat.free_min == 0) {
		vm_stat.free_min = vm_stat.free_count / 20;
		if (vm_stat.free_min < 3)
			vm_stat.free_min = 3;
E 6
I 6
	if (cnt.v_free_min == 0) {
D 15
		cnt.v_free_min = cnt.v_free_count / 20;
		if (cnt.v_free_min < 3)
			cnt.v_free_min = 3;
E 6
E 5

D 5
		if (vm_page_free_min > vm_page_free_min_sanity)
			vm_page_free_min = vm_page_free_min_sanity;
E 5
I 5
D 6
		if (vm_stat.free_min > vm_page_free_min_sanity)
			vm_stat.free_min = vm_page_free_min_sanity;
E 6
I 6
		if (cnt.v_free_min > vm_page_free_min_sanity)
			cnt.v_free_min = vm_page_free_min_sanity;
E 15
I 15
		cnt.v_free_min = VM_PAGE_FREE_MIN;
		vm_page_free_min_min /= cnt.v_page_size;
		vm_page_free_min_max /= cnt.v_page_size;
		if (cnt.v_free_min < vm_page_free_min_min)
			cnt.v_free_min = vm_page_free_min_min;
		if (cnt.v_free_min > vm_page_free_min_max)
			cnt.v_free_min = vm_page_free_min_max;
E 15
E 6
E 5
	}

D 5
	if (vm_page_free_reserved == 0) {
		if ((vm_page_free_reserved = vm_page_free_min / 2) < 10)
			vm_page_free_reserved = 10;
	}
	if (vm_pageout_free_min == 0) {
		if ((vm_pageout_free_min = vm_page_free_reserved / 2) > 10)
			vm_pageout_free_min = 10;
	}
E 5
I 5
D 6
	if (vm_stat.free_target == 0)
		vm_stat.free_target = (vm_stat.free_min * 4) / 3;
E 6
I 6
	if (cnt.v_free_target == 0)
D 15
		cnt.v_free_target = (cnt.v_free_min * 4) / 3;
E 15
I 15
		cnt.v_free_target = VM_PAGE_FREE_TARGET;
E 15
E 6
E 5

D 5
	if (vm_page_free_target == 0)
		vm_page_free_target = (vm_page_free_min * 4) / 3;
E 5
I 5
D 6
	if (vm_stat.inactive_target == 0)
		vm_stat.inactive_target = vm_stat.free_min * 2;
E 6
I 6
D 10
	if (cnt.v_inactive_target == 0)
		cnt.v_inactive_target = cnt.v_free_min * 2;
E 6
E 5

E 10
D 5
	if (vm_page_inactive_target == 0)
		vm_page_inactive_target = vm_page_free_min * 2;
E 5
I 5
D 6
	if (vm_stat.free_target <= vm_stat.free_min)
		vm_stat.free_target = vm_stat.free_min + 1;
E 6
I 6
	if (cnt.v_free_target <= cnt.v_free_min)
		cnt.v_free_target = cnt.v_free_min + 1;
I 11

	/* XXX does not really belong here */
	if (vm_page_max_wired == 0)
		vm_page_max_wired = cnt.v_free_count / 3;
E 11
E 6
E 5

D 5
	if (vm_page_free_target <= vm_page_free_min)
		vm_page_free_target = vm_page_free_min + 1;
E 5
I 5
D 6
	if (vm_stat.inactive_target <= vm_stat.free_target)
		vm_stat.inactive_target = vm_stat.free_target + 1;
E 6
I 6
D 10
	if (cnt.v_inactive_target <= cnt.v_free_target)
		cnt.v_inactive_target = cnt.v_free_target + 1;
E 6
E 5

E 10
D 5
	if (vm_page_inactive_target <= vm_page_free_target)
		vm_page_inactive_target = vm_page_free_target + 1;

E 5
	/*
	 *	The pageout daemon is never done, so loop
	 *	forever.
	 */

	simple_lock(&vm_pages_needed_lock);
	while (TRUE) {
D 17
		thread_sleep((int) &vm_pages_needed, &vm_pages_needed_lock,
			     FALSE);
E 17
I 17
		thread_sleep(&vm_pages_needed, &vm_pages_needed_lock, FALSE);
E 17
I 10
		/*
		 * Compute the inactive target for this scan.
		 * We need to keep a reasonable amount of memory in the
		 * inactive list to better simulate LRU behavior.
		 */
		cnt.v_inactive_target =
			(cnt.v_active_count + cnt.v_inactive_count) / 3;
		if (cnt.v_inactive_target <= cnt.v_free_target)
			cnt.v_inactive_target = cnt.v_free_target + 1;

E 10
D 15
		vm_pageout_scan();
E 15
I 15
		/*
		 * Only make a scan if we are likely to do something.
		 * Otherwise we might have been awakened by a pager
		 * to clean up async pageouts.
		 */
		if (cnt.v_free_count < cnt.v_free_target ||
		    cnt.v_inactive_count < cnt.v_inactive_target)
			vm_pageout_scan();
E 15
		vm_pager_sync();
		simple_lock(&vm_pages_needed_lock);
D 5
		thread_wakeup((int) &vm_page_free_count);
E 5
I 5
D 6
		thread_wakeup((int) &vm_stat.free_count);
E 6
I 6
D 17
		thread_wakeup((int) &cnt.v_free_count);
E 17
I 17
		thread_wakeup(&cnt.v_free_count);
E 17
E 6
E 5
	}
}
E 1
