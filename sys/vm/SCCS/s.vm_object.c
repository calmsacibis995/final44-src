h29149
s 00002/00005/01421
d D 8.7 95/05/11 12:52:42 mckusick 23 21
c fix locking bug in vm_object_terminate (from hibler)
e
s 00001/00001/01425
d R 8.7 95/05/10 17:46:32 mckusick 22 21
c only unlock object if we have not already done so
e
s 00037/00021/01389
d D 8.6 95/01/09 17:50:22 cgd 21 20
c KNF, and 64-bit safety.
e
s 00001/00001/01409
d D 8.5 94/03/22 12:44:53 hibler 20 19
c correction to last delta: VM_OBJECT_NULL -> NULL
e
s 00008/00000/01402
d D 8.4 94/03/21 16:46:38 hibler 19 18
c another relevant fix from Mach 3.0
e
s 00063/00072/01339
d D 8.3 94/01/12 16:01:04 hibler 18 17
c mods to vm_object_page_clean in support of msync,
c keep vmmeter statistics,
c get rid of unused vm_object_shutdown,
c a couple of vm_object_collapse bug fixes from Mach 3.0.
e
s 00052/00083/01359
d D 8.2 93/12/30 16:01:21 mckusick 17 16
c convert to use new queue structures
e
s 00002/00002/01440
d D 8.1 93/06/11 16:38:06 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/01440
d D 7.14 93/05/24 23:40:34 torek 15 14
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00001/00001/01441
d D 7.13 92/10/07 22:26:33 mckusick 14 13
c new cache link names
e
s 00016/00015/01426
d D 7.12 92/10/01 17:54:23 mckusick 13 12
c convert vm_page bit fields to flags
e
s 00012/00004/01429
d D 7.11 92/05/04 17:23:30 bostic 12 11
c new include format; lint; function prototype
e
s 00005/00005/01428
d D 7.10 92/01/14 15:43:37 marc 11 10
c have to avoid use of dequeue which causes problems on the MIPS
e
s 00000/00000/01433
d D 7.9 91/11/20 16:35:01 marc 10 8
i 9
c merge in 7.7.1.1 (ralphs 3100 changes)
e
s 00003/00003/01418
d D 7.7.1.1 91/11/20 16:32:16 marc 9 7
c 3100 changes (from ralph)
e
s 00070/00058/01363
d D 7.8 91/10/21 13:11:35 hibler 8 7
c in vm_object_page_clean avoid races with pageout daemon
e
s 00008/00010/01413
d D 7.7 91/08/28 15:44:56 mckusick 7 6
c vm_stat is merged into vmmeter structure;
c can_persist and internal bit fields replaced with flags
e
s 00001/00001/01422
d D 7.6 91/08/16 17:41:21 mckusick 6 5
c lint
e
s 00002/00002/01421
d D 7.5 91/07/25 23:02:17 mckusick 5 4
c vm_page_active_count and vm_page_inactive_count move to vm_stat
e
s 00007/00011/01416
d D 7.4 91/05/07 09:35:07 hibler 4 3
c pmap_remove_all -> pmap_page_protect
c copy_on_write bit no longer relied on
e
s 00027/00004/01400
d D 7.3 91/04/21 18:36:15 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00044/00046/01360
d D 7.2 91/04/20 10:50:12 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 01406/00000/00000
d D 7.1 90/12/05 18:08:13 mckusick 1 0
c adopted from Mach 2.5
e
u
U
f b 
t
T
I 1
/* 
D 3
 * Copyright (c) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 * Copyright (c) 1987 Carnegie-Mellon University
E 3
D 16
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
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
 *	Virtual memory object module.
 */

D 12
#include "param.h"
#include "malloc.h"
E 12
I 12
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
E 12
D 2
#include "../vm/vm_param.h"
#include "lock.h"
#include "../vm/vm_page.h"
#include "../vm/vm_map.h"
#include "../vm/vm_object.h"
E 2

I 2
D 12
#include "vm.h"
#include "vm_page.h"
E 12
I 12
#include <vm/vm.h>
#include <vm/vm_page.h>
E 12

E 2
/*
 *	Virtual memory objects maintain the actual data
 *	associated with allocated virtual memory.  A given
 *	page of memory exists within exactly one object.
 *
 *	An object is only deallocated when all "references"
 *	are given up.  Only one "reference" to a given
 *	region of an object should be writeable.
 *
 *	Associated with each object is a list of all resident
 *	memory pages belonging to that object; this list is
 *	maintained by the "vm_page" module, and locked by the object's
 *	lock.
 *
 *	Each object also records a "pager" routine which is
 *	used to retrieve (and store) pages to the proper backing
 *	storage.  In addition, objects may be backed by other
 *	objects from which they were virtual-copied.
 *
 *	The only items within the object structure which are
 *	modified after time of creation are:
 *		reference count		locked by object's lock
 *		pager routine		locked by object's lock
 *
 */

struct vm_object	kernel_object_store;
struct vm_object	kmem_object_store;

#define	VM_OBJECT_HASH_COUNT	157

D 17
int		vm_cache_max = 100;	/* can patch if necessary */
queue_head_t	vm_object_hashtable[VM_OBJECT_HASH_COUNT];
E 17
I 17
int	vm_cache_max = 100;	/* can patch if necessary */
struct	vm_object_hash_head vm_object_hashtable[VM_OBJECT_HASH_COUNT];
E 17

long	object_collapses = 0;
long	object_bypasses  = 0;

I 12
static void _vm_object_allocate __P((vm_size_t, vm_object_t));

E 12
/*
 *	vm_object_init:
 *
 *	Initialize the VM objects module.
 */
D 9
void vm_object_init()
E 9
I 9
D 21
void vm_object_init(size)
E 21
I 21
void
vm_object_init(size)
E 21
	vm_size_t	size;
E 9
{
	register int	i;

D 17
	queue_init(&vm_object_cached_list);
	queue_init(&vm_object_list);
E 17
I 17
	TAILQ_INIT(&vm_object_cached_list);
	TAILQ_INIT(&vm_object_list);
E 17
	vm_object_count = 0;
	simple_lock_init(&vm_cache_lock);
	simple_lock_init(&vm_object_list_lock);

	for (i = 0; i < VM_OBJECT_HASH_COUNT; i++)
D 17
		queue_init(&vm_object_hashtable[i]);
E 17
I 17
		TAILQ_INIT(&vm_object_hashtable[i]);
E 17

	kernel_object = &kernel_object_store;
D 9
	_vm_object_allocate(VM_MAX_KERNEL_ADDRESS - VM_MIN_KERNEL_ADDRESS,
			kernel_object);
E 9
I 9
	_vm_object_allocate(size, kernel_object);
E 9

	kmem_object = &kmem_object_store;
	_vm_object_allocate(VM_KMEM_SIZE + VM_MBUF_SIZE, kmem_object);
}

/*
 *	vm_object_allocate:
 *
 *	Returns a new object with the given size.
 */

D 21
vm_object_t vm_object_allocate(size)
E 21
I 21
vm_object_t
vm_object_allocate(size)
E 21
	vm_size_t	size;
{
	register vm_object_t	result;

	result = (vm_object_t)
		malloc((u_long)sizeof *result, M_VMOBJ, M_WAITOK);

	_vm_object_allocate(size, result);

	return(result);
}

I 12
static void
E 12
_vm_object_allocate(size, object)
	vm_size_t		size;
	register vm_object_t	object;
{
D 17
	queue_init(&object->memq);
E 17
I 17
	TAILQ_INIT(&object->memq);
E 17
	vm_object_lock_init(object);
	object->ref_count = 1;
	object->resident_page_count = 0;
	object->size = size;
D 7
	object->can_persist = FALSE;
E 7
I 7
	object->flags = OBJ_INTERNAL;	/* vm_allocate_with_pager will reset */
E 7
	object->paging_in_progress = 0;
D 2
	object->copy = VM_OBJECT_NULL;
E 2
I 2
	object->copy = NULL;
E 2

	/*
	 *	Object starts out read-write, with no pager.
	 */

D 2
	object->pager = vm_pager_null;
E 2
I 2
	object->pager = NULL;
E 2
D 7
	object->pager_ready = FALSE;
	object->internal = TRUE;	/* vm_allocate_with_pager will reset */
E 7
	object->paging_offset = 0;
D 2
	object->shadow = VM_OBJECT_NULL;
E 2
I 2
	object->shadow = NULL;
E 2
	object->shadow_offset = (vm_offset_t) 0;

	simple_lock(&vm_object_list_lock);
D 17
	queue_enter(&vm_object_list, object, vm_object_t, object_list);
E 17
I 17
	TAILQ_INSERT_TAIL(&vm_object_list, object, object_list);
E 17
	vm_object_count++;
I 18
	cnt.v_nzfod += atop(size);
E 18
	simple_unlock(&vm_object_list_lock);
}

/*
 *	vm_object_reference:
 *
 *	Gets another reference to the given object.
 */
D 21
void vm_object_reference(object)
E 21
I 21
void
vm_object_reference(object)
E 21
	register vm_object_t	object;
{
D 2
	if (object == VM_OBJECT_NULL)
E 2
I 2
	if (object == NULL)
E 2
		return;

	vm_object_lock(object);
	object->ref_count++;
	vm_object_unlock(object);
}

/*
 *	vm_object_deallocate:
 *
 *	Release a reference to the specified object,
 *	gained either through a vm_object_allocate
 *	or a vm_object_reference call.  When all references
 *	are gone, storage associated with this object
 *	may be relinquished.
 *
 *	No object may be locked.
 */
D 21
void vm_object_deallocate(object)
E 21
I 21
void
vm_object_deallocate(object)
E 21
	register vm_object_t	object;
{
	vm_object_t	temp;

D 2
	while (object != VM_OBJECT_NULL) {
E 2
I 2
	while (object != NULL) {
E 2

		/*
		 *	The cache holds a reference (uncounted) to
		 *	the object; we must lock it before removing
		 *	the object.
		 */

		vm_object_cache_lock();

		/*
		 *	Lose the reference
		 */
		vm_object_lock(object);
		if (--(object->ref_count) != 0) {

			/*
			 *	If there are still references, then
			 *	we are done.
			 */
			vm_object_unlock(object);
			vm_object_cache_unlock();
			return;
		}

		/*
		 *	See if this object can persist.  If so, enter
		 *	it in the cache, then deactivate all of its
		 *	pages.
		 */

D 7
		if (object->can_persist) {
E 7
I 7
		if (object->flags & OBJ_CANPERSIST) {
E 7

D 17
			queue_enter(&vm_object_cached_list, object,
				vm_object_t, cached_list);
E 17
I 17
			TAILQ_INSERT_TAIL(&vm_object_cached_list, object,
				cached_list);
E 17
			vm_object_cached++;
			vm_object_cache_unlock();

			vm_object_deactivate_pages(object);
			vm_object_unlock(object);

			vm_object_cache_trim();
			return;
		}

		/*
		 *	Make sure no one can look us up now.
		 */
		vm_object_remove(object->pager);
		vm_object_cache_unlock();

		temp = object->shadow;
		vm_object_terminate(object);
			/* unlocks and deallocates object */
		object = temp;
	}
}


/*
 *	vm_object_terminate actually destroys the specified object, freeing
 *	up all previously used resources.
 *
 *	The object must be locked.
 */
D 21
void vm_object_terminate(object)
E 21
I 21
void
vm_object_terminate(object)
E 21
	register vm_object_t	object;
{
	register vm_page_t	p;
	vm_object_t		shadow_object;

	/*
	 *	Detach the object from its shadow if we are the shadow's
	 *	copy.
	 */
D 2
	if ((shadow_object = object->shadow) != VM_OBJECT_NULL) {
E 2
I 2
	if ((shadow_object = object->shadow) != NULL) {
E 2
		vm_object_lock(shadow_object);
		if (shadow_object->copy == object)
D 2
			shadow_object->copy = VM_OBJECT_NULL;
E 2
I 2
			shadow_object->copy = NULL;
E 2
#if 0
D 2
		else if (shadow_object->copy != VM_OBJECT_NULL)
E 2
I 2
		else if (shadow_object->copy != NULL)
E 2
			panic("vm_object_terminate: copy/shadow inconsistency");
#endif
		vm_object_unlock(shadow_object);
	}

	/*
D 8
	 *	Wait until the pageout daemon is through
	 *	with the object.
E 8
I 8
	 * Wait until the pageout daemon is through with the object.
E 8
	 */
D 8

	while (object->paging_in_progress != 0) {
E 8
I 8
	while (object->paging_in_progress) {
E 8
D 6
		vm_object_sleep(object, object, FALSE);
E 6
I 6
D 21
		vm_object_sleep((int)object, object, FALSE);
E 21
I 21
		vm_object_sleep(object, object, FALSE);
E 21
E 6
		vm_object_lock(object);
	}

D 8

E 8
	/*
D 8
	 *	While the paging system is locked,
	 *	pull the object's pages off the active
	 *	and inactive queues.  This keeps the
	 *	pageout daemon from playing with them
	 *	during vm_pager_deallocate.
	 *
	 *	We can't free the pages yet, because the
	 *	object's pager may have to write them out
	 *	before deallocating the paging space.
E 8
I 8
	 * If not an internal object clean all the pages, removing them
	 * from paging queues as we go.
I 18
	 *
	 * XXX need to do something in the event of a cleaning error.
E 18
E 8
	 */
D 8

	p = (vm_page_t) queue_first(&object->memq);
	while (!queue_end(&object->memq, (queue_entry_t) p)) {
		VM_PAGE_CHECK(p);

		vm_page_lock_queues();
		if (p->active) {
			queue_remove(&vm_page_queue_active, p, vm_page_t,
						pageq);
			p->active = FALSE;
D 5
			vm_page_active_count--;
E 5
I 5
D 7
			vm_stat.active_count--;
E 7
I 7
			cnt.v_active_count--;
E 7
E 5
		}

		if (p->inactive) {
			queue_remove(&vm_page_queue_inactive, p, vm_page_t,
						pageq);
			p->inactive = FALSE;
D 5
			vm_page_inactive_count--;
E 5
I 5
D 7
			vm_stat.inactive_count--;
E 7
I 7
			cnt.v_inactive_count--;
E 7
E 5
		}
		vm_page_unlock_queues();
		p = (vm_page_t) queue_next(&p->listq);
E 8
I 8
D 23
	if ((object->flags & OBJ_INTERNAL) == 0) {
E 23
I 23
	if ((object->flags & OBJ_INTERNAL) == 0)
E 23
D 18
		vm_object_page_clean(object, 0, 0, TRUE);
E 18
I 18
		(void) vm_object_page_clean(object, 0, 0, TRUE, TRUE);
E 18
D 23
		vm_object_unlock(object);
E 8
	}
E 23
D 8
				
	vm_object_unlock(object);
E 8

D 8
	if (object->paging_in_progress != 0)
		panic("vm_object_deallocate: pageout in progress");

E 8
	/*
D 8
	 *	Clean and free the pages, as appropriate.
	 *	All references to the object are gone,
	 *	so we don't need to lock it.
E 8
I 8
	 * Now free the pages.
	 * For internal objects, this also removes them from paging queues.
E 8
	 */
D 8

D 7
	if (!object->internal) {
E 7
I 7
	if ((object->flags & OBJ_INTERNAL) == 0) {
E 7
		vm_object_lock(object);
		vm_object_page_clean(object, 0, 0);
		vm_object_unlock(object);
	}
E 8
D 17
	while (!queue_empty(&object->memq)) {
		p = (vm_page_t) queue_first(&object->memq);
E 17
I 17
	while ((p = object->memq.tqh_first) != NULL) {
E 17
D 8

E 8
		VM_PAGE_CHECK(p);
D 8

E 8
		vm_page_lock_queues();
		vm_page_free(p);
I 18
		cnt.v_pfree++;
E 18
		vm_page_unlock_queues();
	}
I 8
D 23
	if ((object->flags & OBJ_INTERNAL) == 0)
		vm_object_unlock(object);
E 23
I 23
	vm_object_unlock(object);
E 23
E 8

	/*
D 8
	 *	Let the pager know object is dead.
E 8
I 8
	 * Let the pager know object is dead.
E 8
	 */
D 8

E 8
D 2
	if (object->pager != vm_pager_null)
E 2
I 2
	if (object->pager != NULL)
E 2
		vm_pager_deallocate(object->pager);

D 8

E 8
	simple_lock(&vm_object_list_lock);
D 17
	queue_remove(&vm_object_list, object, vm_object_t, object_list);
E 17
I 17
	TAILQ_REMOVE(&vm_object_list, object, object_list);
E 17
	vm_object_count--;
	simple_unlock(&vm_object_list_lock);

	/*
D 8
	 *	Free the space for the object.
E 8
I 8
	 * Free the space for the object.
E 8
	 */
D 8

E 8
	free((caddr_t)object, M_VMOBJ);
}

/*
 *	vm_object_page_clean
 *
 *	Clean all dirty pages in the specified range of object.
I 18
 *	If syncio is TRUE, page cleaning is done synchronously.
E 18
D 8
 *	Leaves page on whatever queue it is currently on.
E 8
I 8
D 11
 *	If dequeue is TRUE, pages are removed from any paging queue
E 11
I 11
 *	If de_queue is TRUE, pages are removed from any paging queue
E 11
 *	they were on, otherwise they are left on whatever queue they
 *	were on before the cleaning operation began.
E 8
 *
 *	Odd semantics: if start == end, we clean everything.
 *
 *	The object must be locked.
I 18
 *
 *	Returns TRUE if all was well, FALSE if there was a pager error
 *	somewhere.  We attempt to clean (and dequeue) all pages regardless
 *	of where an error occurs.
E 18
 */
I 12
D 18
void
E 12
D 8
vm_object_page_clean(object, start, end)
E 8
I 8
D 11
vm_object_page_clean(object, start, end, dequeue)
E 11
I 11
vm_object_page_clean(object, start, end, de_queue)
E 18
I 18
boolean_t
vm_object_page_clean(object, start, end, syncio, de_queue)
E 18
E 11
E 8
	register vm_object_t	object;
	register vm_offset_t	start;
	register vm_offset_t	end;
I 18
	boolean_t		syncio;
E 18
I 8
D 11
	boolean_t		dequeue;
E 11
I 11
	boolean_t		de_queue;
E 11
E 8
{
	register vm_page_t	p;
I 8
	int onqueue;
I 18
	boolean_t noerror = TRUE;
E 18
E 8

I 18
	if (object == NULL)
		return (TRUE);

	/*
	 * If it is an internal object and there is no pager, attempt to
	 * allocate one.  Note that vm_object_collapse may relocate one
	 * from a collapsed object so we must recheck afterward.
	 */
	if ((object->flags & OBJ_INTERNAL) && object->pager == NULL) {
		vm_object_collapse(object);
		if (object->pager == NULL) {
			vm_pager_t pager;

			vm_object_unlock(object);
			pager = vm_pager_allocate(PG_DFLT, (caddr_t)0,
						  object->size, VM_PROT_ALL,
						  (vm_offset_t)0);
			if (pager)
				vm_object_setpager(object, pager, 0, FALSE);
			vm_object_lock(object);
		}
	}
E 18
D 2
	if (object->pager == vm_pager_null)
E 2
I 2
	if (object->pager == NULL)
E 2
D 18
		return;
E 18
I 18
		return (FALSE);
E 18

again:
I 8
	/*
	 * Wait until the pageout daemon is through with the object.
	 */
	while (object->paging_in_progress) {
D 21
		vm_object_sleep((int)object, object, FALSE);
E 21
I 21
		vm_object_sleep(object, object, FALSE);
E 21
		vm_object_lock(object);
	}
	/*
	 * Loop through the object page list cleaning as necessary.
	 */
E 8
D 17
	p = (vm_page_t) queue_first(&object->memq);
	while (!queue_end(&object->memq, (queue_entry_t) p)) {
E 17
I 17
	for (p = object->memq.tqh_first; p != NULL; p = p->listq.tqe_next) {
E 17
D 18
		if (start == end ||
		    p->offset >= start && p->offset < end) {
E 18
I 18
		if ((start == end || p->offset >= start && p->offset < end) &&
		    !(p->flags & PG_FICTITIOUS)) {
E 18
D 13
			if (p->clean && pmap_is_modified(VM_PAGE_TO_PHYS(p)))
				p->clean = FALSE;
E 13
I 13
			if ((p->flags & PG_CLEAN) &&
			    pmap_is_modified(VM_PAGE_TO_PHYS(p)))
				p->flags &= ~PG_CLEAN;
E 13
I 8
			/*
			 * Remove the page from any paging queue.
			 * This needs to be done if either we have been
			 * explicitly asked to do so or it is about to
			 * be cleaned (see comment below).
			 */
D 11
			if (dequeue || !p->clean) {
E 11
I 11
D 13
			if (de_queue || !p->clean) {
E 13
I 13
			if (de_queue || !(p->flags & PG_CLEAN)) {
E 13
E 11
				vm_page_lock_queues();
D 13
				if (p->active) {
E 13
I 13
				if (p->flags & PG_ACTIVE) {
E 13
D 17
					queue_remove(&vm_page_queue_active,
						     p, vm_page_t, pageq);
E 17
I 17
					TAILQ_REMOVE(&vm_page_queue_active,
						     p, pageq);
E 17
D 13
					p->active = FALSE;
E 13
I 13
					p->flags &= ~PG_ACTIVE;
E 13
					cnt.v_active_count--;
					onqueue = 1;
D 13
				} else if (p->inactive) {
E 13
I 13
				} else if (p->flags & PG_INACTIVE) {
E 13
D 17
					queue_remove(&vm_page_queue_inactive,
						     p, vm_page_t, pageq);
E 17
I 17
					TAILQ_REMOVE(&vm_page_queue_inactive,
						     p, pageq);
E 17
D 13
					p->inactive = FALSE;
E 13
I 13
					p->flags &= ~PG_INACTIVE;
E 13
					cnt.v_inactive_count--;
					onqueue = -1;
				} else
					onqueue = 0;
				vm_page_unlock_queues();
			}
			/*
			 * To ensure the state of the page doesn't change
			 * during the clean operation we do two things.
D 18
			 * First we set the busy bit and invalidate all
			 * mappings to ensure that thread accesses to the
E 18
I 18
			 * First we set the busy bit and write-protect all
			 * mappings to ensure that write accesses to the
E 18
			 * page block (in vm_fault).  Second, we remove
			 * the page from any paging queue to foil the
			 * pageout daemon (vm_pageout_scan).
			 */
E 8
D 4
			pmap_remove_all(VM_PAGE_TO_PHYS(p));
E 4
I 4
D 18
			pmap_page_protect(VM_PAGE_TO_PHYS(p), VM_PROT_NONE);
E 18
I 18
			pmap_page_protect(VM_PAGE_TO_PHYS(p), VM_PROT_READ);
E 18
E 4
D 13
			if (!p->clean) {
				p->busy = TRUE;
E 13
I 13
			if (!(p->flags & PG_CLEAN)) {
				p->flags |= PG_BUSY;
E 13
				object->paging_in_progress++;
				vm_object_unlock(object);
D 18
				(void) vm_pager_put(object->pager, p, TRUE);
E 18
I 18
				/*
				 * XXX if put fails we mark the page as
				 * clean to avoid an infinite loop.
				 * Will loose changes to the page.
				 */
				if (vm_pager_put(object->pager, p, syncio)) {
					printf("%s: pager_put error\n",
					       "vm_object_page_clean");
					p->flags |= PG_CLEAN;
					noerror = FALSE;
				}
E 18
				vm_object_lock(object);
				object->paging_in_progress--;
I 8
D 11
				if (!dequeue && onqueue) {
E 11
I 11
				if (!de_queue && onqueue) {
E 11
					vm_page_lock_queues();
					if (onqueue > 0)
						vm_page_activate(p);
					else
						vm_page_deactivate(p);
					vm_page_unlock_queues();
				}
E 8
D 13
				p->busy = FALSE;
E 13
I 13
				p->flags &= ~PG_BUSY;
E 13
				PAGE_WAKEUP(p);
				goto again;
			}
		}
D 17
		p = (vm_page_t) queue_next(&p->listq);
E 17
	}
I 18
	return (noerror);
E 18
}

/*
 *	vm_object_deactivate_pages
 *
 *	Deactivate all pages in the specified object.  (Keep its pages
 *	in memory even though it is no longer referenced.)
 *
 *	The object must be locked.
 */
I 12
void
E 12
vm_object_deactivate_pages(object)
	register vm_object_t	object;
{
	register vm_page_t	p, next;

D 17
	p = (vm_page_t) queue_first(&object->memq);
	while (!queue_end(&object->memq, (queue_entry_t) p)) {
		next = (vm_page_t) queue_next(&p->listq);
E 17
I 17
	for (p = object->memq.tqh_first; p != NULL; p = next) {
		next = p->listq.tqe_next;
E 17
		vm_page_lock_queues();
		vm_page_deactivate(p);
		vm_page_unlock_queues();
D 17
		p = next;
E 17
	}
}

/*
 *	Trim the object cache to size.
 */
I 12
void
E 12
vm_object_cache_trim()
{
	register vm_object_t	object;

	vm_object_cache_lock();
	while (vm_object_cached > vm_cache_max) {
D 17
		object = (vm_object_t) queue_first(&vm_object_cached_list);
E 17
I 17
		object = vm_object_cached_list.tqh_first;
E 17
		vm_object_cache_unlock();

		if (object != vm_object_lookup(object->pager))
			panic("vm_object_deactivate: I'm sooo confused.");

		pager_cache(object, FALSE);

		vm_object_cache_lock();
	}
	vm_object_cache_unlock();
}

D 18

E 18
/*
D 18
 *	vm_object_shutdown()
 *
 *	Shut down the object system.  Unfortunately, while we
 *	may be trying to do this, init is happily waiting for
 *	processes to exit, and therefore will be causing some objects
 *	to be deallocated.  To handle this, we gain a fake reference
 *	to all objects we release paging areas for.  This will prevent
 *	a duplicate deallocation.  This routine is probably full of
 *	race conditions!
 */

void vm_object_shutdown()
{
	register vm_object_t	object;

	/*
	 *	Clean up the object cache *before* we screw up the reference
	 *	counts on all of the objects.
	 */

	vm_object_cache_clear();

	printf("free paging spaces: ");

	/*
	 *	First we gain a reference to each object so that
	 *	no one else will deallocate them.
	 */

	simple_lock(&vm_object_list_lock);
D 17
	object = (vm_object_t) queue_first(&vm_object_list);
	while (!queue_end(&vm_object_list, (queue_entry_t) object)) {
E 17
I 17
	for (object = vm_object_list.tqh_first;
	     object != NULL;
	     object = object->object_list.tqe_next)
E 17
		vm_object_reference(object);
D 17
		object = (vm_object_t) queue_next(&object->object_list);
	}
E 17
	simple_unlock(&vm_object_list_lock);

	/*
	 *	Now we deallocate all the paging areas.  We don't need
	 *	to lock anything because we've reduced to a single
	 *	processor while shutting down.	This also assumes that
	 *	no new objects are being created.
	 */

D 17
	object = (vm_object_t) queue_first(&vm_object_list);
	while (!queue_end(&vm_object_list, (queue_entry_t) object)) {
E 17
I 17
	for (object = vm_object_list.tqh_first;
	     object != NULL;
	     object = object->object_list.tqe_next) {
E 17
D 2
		if (object->pager != vm_pager_null)
E 2
I 2
		if (object->pager != NULL)
E 2
			vm_pager_deallocate(object->pager);
D 17
		object = (vm_object_t) queue_next(&object->object_list);
E 17
		printf(".");
	}
	printf("done.\n");
}

/*
E 18
 *	vm_object_pmap_copy:
 *
 *	Makes all physical pages in the specified
 *	object range copy-on-write.  No writeable
 *	references to these pages should remain.
 *
 *	The object must *not* be locked.
 */
D 21
void vm_object_pmap_copy(object, start, end)
E 21
I 21
void
vm_object_pmap_copy(object, start, end)
E 21
	register vm_object_t	object;
	register vm_offset_t	start;
	register vm_offset_t	end;
{
	register vm_page_t	p;

D 2
	if (object == VM_OBJECT_NULL)
E 2
I 2
	if (object == NULL)
E 2
		return;

	vm_object_lock(object);
D 17
	p = (vm_page_t) queue_first(&object->memq);
	while (!queue_end(&object->memq, (queue_entry_t) p)) {
E 17
I 17
	for (p = object->memq.tqh_first; p != NULL; p = p->listq.tqe_next) {
E 17
		if ((start <= p->offset) && (p->offset < end)) {
D 4
			if (!p->copy_on_write) {
				pmap_copy_on_write(VM_PAGE_TO_PHYS(p));
				p->copy_on_write = TRUE;
			}
E 4
I 4
			pmap_page_protect(VM_PAGE_TO_PHYS(p), VM_PROT_READ);
D 13
			p->copy_on_write = TRUE;
E 13
I 13
			p->flags |= PG_COPYONWRITE;
E 13
E 4
		}
D 17
		p = (vm_page_t) queue_next(&p->listq);
E 17
	}
	vm_object_unlock(object);
}

/*
 *	vm_object_pmap_remove:
 *
 *	Removes all physical pages in the specified
 *	object range from all physical maps.
 *
 *	The object must *not* be locked.
 */
D 21
void vm_object_pmap_remove(object, start, end)
E 21
I 21
void
vm_object_pmap_remove(object, start, end)
E 21
	register vm_object_t	object;
	register vm_offset_t	start;
	register vm_offset_t	end;
{
	register vm_page_t	p;

D 2
	if (object == VM_OBJECT_NULL)
E 2
I 2
	if (object == NULL)
E 2
		return;

	vm_object_lock(object);
D 17
	p = (vm_page_t) queue_first(&object->memq);
	while (!queue_end(&object->memq, (queue_entry_t) p)) {
E 17
I 17
	for (p = object->memq.tqh_first; p != NULL; p = p->listq.tqe_next)
E 17
D 4
		if ((start <= p->offset) && (p->offset < end)) {
			pmap_remove_all(VM_PAGE_TO_PHYS(p));
		}
E 4
I 4
		if ((start <= p->offset) && (p->offset < end))
			pmap_page_protect(VM_PAGE_TO_PHYS(p), VM_PROT_NONE);
E 4
D 17
		p = (vm_page_t) queue_next(&p->listq);
	}
E 17
	vm_object_unlock(object);
}

/*
 *	vm_object_copy:
 *
 *	Create a new object which is a copy of an existing
 *	object, and mark all of the pages in the existing
 *	object 'copy-on-write'.  The new object has one reference.
 *	Returns the new object.
 *
 *	May defer the copy until later if the object is not backed
 *	up by a non-default pager.
 */
D 21
void vm_object_copy(src_object, src_offset, size,
E 21
I 21
void
vm_object_copy(src_object, src_offset, size,
E 21
		    dst_object, dst_offset, src_needs_copy)
	register vm_object_t	src_object;
	vm_offset_t		src_offset;
	vm_size_t		size;
	vm_object_t		*dst_object;	/* OUT */
	vm_offset_t		*dst_offset;	/* OUT */
	boolean_t		*src_needs_copy;	/* OUT */
{
	register vm_object_t	new_copy;
	register vm_object_t	old_copy;
	vm_offset_t		new_start, new_end;

	register vm_page_t	p;

D 2
	if (src_object == VM_OBJECT_NULL) {
E 2
I 2
	if (src_object == NULL) {
E 2
		/*
		 *	Nothing to copy
		 */
D 2
		*dst_object = VM_OBJECT_NULL;
E 2
I 2
		*dst_object = NULL;
E 2
		*dst_offset = 0;
		*src_needs_copy = FALSE;
		return;
	}

	/*
	 *	If the object's pager is null_pager or the
	 *	default pager, we don't have to make a copy
	 *	of it.  Instead, we set the needs copy flag and
	 *	make a shadow later.
	 */

	vm_object_lock(src_object);
D 2
	if (src_object->pager == vm_pager_null ||
E 2
I 2
	if (src_object->pager == NULL ||
E 2
D 7
	    src_object->internal) {
E 7
I 7
	    (src_object->flags & OBJ_INTERNAL)) {
E 7

		/*
		 *	Make another reference to the object
		 */
		src_object->ref_count++;

		/*
		 *	Mark all of the pages copy-on-write.
		 */
D 17
		for (p = (vm_page_t) queue_first(&src_object->memq);
		     !queue_end(&src_object->memq, (queue_entry_t)p);
		     p = (vm_page_t) queue_next(&p->listq)) {
E 17
I 17
		for (p = src_object->memq.tqh_first; p; p = p->listq.tqe_next)
E 17
			if (src_offset <= p->offset &&
			    p->offset < src_offset + size)
D 13
				p->copy_on_write = TRUE;
E 13
I 13
				p->flags |= PG_COPYONWRITE;
E 13
D 17
		}
E 17
		vm_object_unlock(src_object);

		*dst_object = src_object;
		*dst_offset = src_offset;
		
		/*
		 *	Must make a shadow when write is desired
		 */
		*src_needs_copy = TRUE;
		return;
	}

	/*
	 *	Try to collapse the object before copying it.
	 */
	vm_object_collapse(src_object);

	/*
	 *	If the object has a pager, the pager wants to
	 *	see all of the changes.  We need a copy-object
	 *	for the changed pages.
	 *
	 *	If there is a copy-object, and it is empty,
	 *	no changes have been made to the object since the
	 *	copy-object was made.  We can use the same copy-
	 *	object.
	 */

    Retry1:
	old_copy = src_object->copy;
D 2
	if (old_copy != VM_OBJECT_NULL) {
E 2
I 2
	if (old_copy != NULL) {
E 2
		/*
		 *	Try to get the locks (out of order)
		 */
		if (!vm_object_lock_try(old_copy)) {
			vm_object_unlock(src_object);

			/* should spin a bit here... */
			vm_object_lock(src_object);
			goto Retry1;
		}

		if (old_copy->resident_page_count == 0 &&
D 2
		    old_copy->pager == vm_pager_null) {
E 2
I 2
		    old_copy->pager == NULL) {
E 2
			/*
			 *	Return another reference to
			 *	the existing copy-object.
			 */
			old_copy->ref_count++;
			vm_object_unlock(old_copy);
			vm_object_unlock(src_object);
			*dst_object = old_copy;
			*dst_offset = src_offset;
			*src_needs_copy = FALSE;
			return;
		}
		vm_object_unlock(old_copy);
	}
	vm_object_unlock(src_object);

	/*
	 *	If the object has a pager, the pager wants
	 *	to see all of the changes.  We must make
	 *	a copy-object and put the changed pages there.
	 *
	 *	The copy-object is always made large enough to
	 *	completely shadow the original object, since
	 *	it may have several users who want to shadow
	 *	the original object at different points.
	 */

	new_copy = vm_object_allocate(src_object->size);

    Retry2:
	vm_object_lock(src_object);
	/*
	 *	Copy object may have changed while we were unlocked
	 */
	old_copy = src_object->copy;
D 2
	if (old_copy != VM_OBJECT_NULL) {
E 2
I 2
	if (old_copy != NULL) {
E 2
		/*
		 *	Try to get the locks (out of order)
		 */
		if (!vm_object_lock_try(old_copy)) {
			vm_object_unlock(src_object);
			goto Retry2;
		}

		/*
		 *	Consistency check
		 */
		if (old_copy->shadow != src_object ||
		    old_copy->shadow_offset != (vm_offset_t) 0)
			panic("vm_object_copy: copy/shadow inconsistency");

		/*
		 *	Make the old copy-object shadow the new one.
		 *	It will receive no more pages from the original
		 *	object.
		 */

		src_object->ref_count--;	/* remove ref. from old_copy */
		old_copy->shadow = new_copy;
		new_copy->ref_count++;		/* locking not needed - we
						   have the only pointer */
		vm_object_unlock(old_copy);	/* done with old_copy */
	}

	new_start = (vm_offset_t) 0;	/* always shadow original at 0 */
	new_end   = (vm_offset_t) new_copy->size; /* for the whole object */

	/*
	 *	Point the new copy at the existing object.
	 */

	new_copy->shadow = src_object;
	new_copy->shadow_offset = new_start;
	src_object->ref_count++;
	src_object->copy = new_copy;

	/*
	 *	Mark all the affected pages of the existing object
	 *	copy-on-write.
	 */
D 17
	p = (vm_page_t) queue_first(&src_object->memq);
	while (!queue_end(&src_object->memq, (queue_entry_t) p)) {
E 17
I 17
	for (p = src_object->memq.tqh_first; p != NULL; p = p->listq.tqe_next)
E 17
D 4
		if ((new_start <= p->offset) && (p->offset < new_end)) {
E 4
I 4
		if ((new_start <= p->offset) && (p->offset < new_end))
E 4
D 13
			p->copy_on_write = TRUE;
E 13
I 13
			p->flags |= PG_COPYONWRITE;
E 13
D 4
		}
E 4
D 17
		p = (vm_page_t) queue_next(&p->listq);
	}
E 17

	vm_object_unlock(src_object);

	*dst_object = new_copy;
	*dst_offset = src_offset - new_start;
	*src_needs_copy = FALSE;
}

/*
 *	vm_object_shadow:
 *
 *	Create a new object which is backed by the
 *	specified existing object range.  The source
 *	object reference is deallocated.
 *
 *	The new object and offset into that object
 *	are returned in the source parameters.
 */

D 21
void vm_object_shadow(object, offset, length)
E 21
I 21
void
vm_object_shadow(object, offset, length)
E 21
	vm_object_t	*object;	/* IN/OUT */
	vm_offset_t	*offset;	/* IN/OUT */
	vm_size_t	length;
{
	register vm_object_t	source;
	register vm_object_t	result;

	source = *object;

	/*
	 *	Allocate a new object with the given length
	 */

D 2
	if ((result = vm_object_allocate(length)) == VM_OBJECT_NULL)
E 2
I 2
	if ((result = vm_object_allocate(length)) == NULL)
E 2
		panic("vm_object_shadow: no object for shadowing");

	/*
	 *	The new object shadows the source object, adding
	 *	a reference to it.  Our caller changes his reference
	 *	to point to the new object, removing a reference to
	 *	the source object.  Net result: no change of reference
	 *	count.
	 */
	result->shadow = source;
	
	/*
	 *	Store the offset into the source object,
	 *	and fix up the offset into the new object.
	 */

	result->shadow_offset = *offset;

	/*
	 *	Return the new things
	 */

	*offset = 0;
	*object = result;
}

/*
 *	Set the specified object's pager to the specified pager.
 */

D 21
void vm_object_setpager(object, pager, paging_offset,
E 21
I 21
void
vm_object_setpager(object, pager, paging_offset,
E 21
			read_only)
	vm_object_t	object;
	vm_pager_t	pager;
	vm_offset_t	paging_offset;
	boolean_t	read_only;
{
#ifdef	lint
	read_only++;	/* No longer used */
D 15
#endif	lint
E 15
I 15
#endif
E 15

	vm_object_lock(object);			/* XXX ? */
	object->pager = pager;
	object->paging_offset = paging_offset;
	vm_object_unlock(object);			/* XXX ? */
}

/*
 *	vm_object_hash hashes the pager/id pair.
 */

#define vm_object_hash(pager) \
D 21
	(((unsigned)pager)%VM_OBJECT_HASH_COUNT)
E 21
I 21
	(((unsigned long)pager)%VM_OBJECT_HASH_COUNT)
E 21

/*
 *	vm_object_lookup looks in the object cache for an object with the
 *	specified pager and paging id.
 */

D 21
vm_object_t vm_object_lookup(pager)
E 21
I 21
vm_object_t
vm_object_lookup(pager)
E 21
	vm_pager_t	pager;
{
D 17
	register queue_t		bucket;
E 17
	register vm_object_hash_entry_t	entry;
	vm_object_t			object;

D 17
	bucket = &vm_object_hashtable[vm_object_hash(pager)];

E 17
	vm_object_cache_lock();

D 17
	entry = (vm_object_hash_entry_t) queue_first(bucket);
	while (!queue_end(bucket, (queue_entry_t) entry)) {
E 17
I 17
	for (entry = vm_object_hashtable[vm_object_hash(pager)].tqh_first;
	     entry != NULL;
	     entry = entry->hash_links.tqe_next) {
E 17
		object = entry->object;
		if (object->pager == pager) {
			vm_object_lock(object);
			if (object->ref_count == 0) {
D 17
				queue_remove(&vm_object_cached_list, object,
						vm_object_t, cached_list);
E 17
I 17
				TAILQ_REMOVE(&vm_object_cached_list, object,
					cached_list);
E 17
				vm_object_cached--;
			}
			object->ref_count++;
			vm_object_unlock(object);
			vm_object_cache_unlock();
			return(object);
		}
D 17
		entry = (vm_object_hash_entry_t) queue_next(&entry->hash_links);
E 17
	}

	vm_object_cache_unlock();
D 2
	return(VM_OBJECT_NULL);
E 2
I 2
	return(NULL);
E 2
}

/*
 *	vm_object_enter enters the specified object/pager/id into
 *	the hash table.
 */

D 21
void vm_object_enter(object, pager)
E 21
I 21
void
vm_object_enter(object, pager)
E 21
	vm_object_t	object;
	vm_pager_t	pager;
{
D 17
	register queue_t		bucket;
E 17
I 17
	struct vm_object_hash_head	*bucket;
E 17
	register vm_object_hash_entry_t	entry;

	/*
	 *	We don't cache null objects, and we can't cache
	 *	objects with the null pager.
	 */

D 2
	if (object == VM_OBJECT_NULL)
E 2
I 2
	if (object == NULL)
E 2
		return;
D 2
	if (pager == vm_pager_null)
E 2
I 2
	if (pager == NULL)
E 2
		return;

	bucket = &vm_object_hashtable[vm_object_hash(pager)];
	entry = (vm_object_hash_entry_t)
		malloc((u_long)sizeof *entry, M_VMOBJHASH, M_WAITOK);
	entry->object = object;
D 7
	object->can_persist = TRUE;
E 7
I 7
	object->flags |= OBJ_CANPERSIST;
E 7

	vm_object_cache_lock();
D 17
	queue_enter(bucket, entry, vm_object_hash_entry_t, hash_links);
E 17
I 17
	TAILQ_INSERT_TAIL(bucket, entry, hash_links);
E 17
	vm_object_cache_unlock();
}

/*
 *	vm_object_remove:
 *
 *	Remove the pager from the hash table.
 *	Note:  This assumes that the object cache
 *	is locked.  XXX this should be fixed
 *	by reorganizing vm_object_deallocate.
 */
I 12
void
E 12
vm_object_remove(pager)
	register vm_pager_t	pager;
{
D 17
	register queue_t		bucket;
E 17
I 17
	struct vm_object_hash_head	*bucket;
E 17
	register vm_object_hash_entry_t	entry;
	register vm_object_t		object;

	bucket = &vm_object_hashtable[vm_object_hash(pager)];

D 17
	entry = (vm_object_hash_entry_t) queue_first(bucket);
	while (!queue_end(bucket, (queue_entry_t) entry)) {
E 17
I 17
	for (entry = bucket->tqh_first;
	     entry != NULL;
	     entry = entry->hash_links.tqe_next) {
E 17
		object = entry->object;
		if (object->pager == pager) {
D 17
			queue_remove(bucket, entry, vm_object_hash_entry_t,
					hash_links);
E 17
I 17
			TAILQ_REMOVE(bucket, entry, hash_links);
E 17
			free((caddr_t)entry, M_VMOBJHASH);
			break;
		}
D 17
		entry = (vm_object_hash_entry_t) queue_next(&entry->hash_links);
E 17
	}
}

/*
 *	vm_object_cache_clear removes all objects from the cache.
 *
 */
D 21

void vm_object_cache_clear()
E 21
I 21
void
vm_object_cache_clear()
E 21
{
	register vm_object_t	object;

	/*
	 *	Remove each object in the cache by scanning down the
	 *	list of cached objects.
	 */
	vm_object_cache_lock();
D 17
	while (!queue_empty(&vm_object_cached_list)) {
		object = (vm_object_t) queue_first(&vm_object_cached_list);
E 17
I 17
	while ((object = vm_object_cached_list.tqh_first) != NULL) {
E 17
		vm_object_cache_unlock();

		/* 
		 * Note: it is important that we use vm_object_lookup
		 * to gain a reference, and not vm_object_reference, because
		 * the logic for removing an object from the cache lies in 
		 * lookup.
		 */
		if (object != vm_object_lookup(object->pager))
			panic("vm_object_cache_clear: I'm sooo confused.");
		pager_cache(object, FALSE);

		vm_object_cache_lock();
	}
	vm_object_cache_unlock();
}

boolean_t	vm_object_collapse_allowed = TRUE;
/*
 *	vm_object_collapse:
 *
 *	Collapse an object with the object backing it.
 *	Pages in the backing object are moved into the
 *	parent, and the backing object is deallocated.
 *
 *	Requires that the object be locked and the page
 *	queues be unlocked.
 *
 */
D 21
void vm_object_collapse(object)
E 21
I 21
void
vm_object_collapse(object)
E 21
	register vm_object_t	object;

{
	register vm_object_t	backing_object;
	register vm_offset_t	backing_offset;
	register vm_size_t	size;
	register vm_offset_t	new_offset;
	register vm_page_t	p, pp;

	if (!vm_object_collapse_allowed)
		return;

	while (TRUE) {
		/*
		 *	Verify that the conditions are right for collapse:
		 *
		 *	The object exists and no pages in it are currently
		 *	being paged out (or have ever been paged out).
		 */
D 2
		if (object == VM_OBJECT_NULL ||
E 2
I 2
		if (object == NULL ||
E 2
		    object->paging_in_progress != 0 ||
D 2
		    object->pager != vm_pager_null)
E 2
I 2
		    object->pager != NULL)
E 2
			return;

		/*
		 *		There is a backing object, and
		 */
	
D 2
		if ((backing_object = object->shadow) == VM_OBJECT_NULL)
E 2
I 2
		if ((backing_object = object->shadow) == NULL)
E 2
			return;
	
		vm_object_lock(backing_object);
		/*
		 *	...
		 *		The backing object is not read_only,
		 *		and no pages in the backing object are
		 *		currently being paged out.
		 *		The backing object is internal.
		 */
	
D 7
		if (!backing_object->internal ||
E 7
I 7
		if ((backing_object->flags & OBJ_INTERNAL) == 0 ||
E 7
		    backing_object->paging_in_progress != 0) {
			vm_object_unlock(backing_object);
			return;
		}
	
		/*
		 *	The backing object can't be a copy-object:
		 *	the shadow_offset for the copy-object must stay
		 *	as 0.  Furthermore (for the 'we have all the
		 *	pages' case), if we bypass backing_object and
		 *	just shadow the next object in the chain, old
		 *	pages from that object would then have to be copied
		 *	BOTH into the (former) backing_object and into the
		 *	parent object.
		 */
D 2
		if (backing_object->shadow != VM_OBJECT_NULL &&
		    backing_object->shadow->copy != VM_OBJECT_NULL) {
E 2
I 2
		if (backing_object->shadow != NULL &&
		    backing_object->shadow->copy != NULL) {
E 2
			vm_object_unlock(backing_object);
			return;
		}

		/*
		 *	We know that we can either collapse the backing
		 *	object (if the parent is the only reference to
		 *	it) or (perhaps) remove the parent's reference
		 *	to it.
		 */

		backing_offset = object->shadow_offset;
		size = object->size;

		/*
		 *	If there is exactly one reference to the backing
		 *	object, we can collapse it into the parent.
		 */
	
		if (backing_object->ref_count == 1) {

			/*
			 *	We can collapse the backing object.
			 *
			 *	Move all in-memory pages from backing_object
			 *	to the parent.  Pages that have been paged out
			 *	will be overwritten by any of the parent's
			 *	pages that shadow them.
			 */

D 17
			while (!queue_empty(&backing_object->memq)) {
E 17
I 17
			while ((p = backing_object->memq.tqh_first) != NULL) {
E 17
D 18

E 18
D 17
				p = (vm_page_t)
					queue_first(&backing_object->memq);

E 17
				new_offset = (p->offset - backing_offset);

				/*
				 *	If the parent has a page here, or if
				 *	this page falls outside the parent,
				 *	dispose of it.
				 *
				 *	Otherwise, move it as planned.
				 */

				if (p->offset < backing_offset ||
				    new_offset >= size) {
					vm_page_lock_queues();
					vm_page_free(p);
					vm_page_unlock_queues();
				} else {
				    pp = vm_page_lookup(object, new_offset);
D 2
				    if (pp != VM_PAGE_NULL && !pp->fake) {
E 2
I 2
D 13
				    if (pp != NULL && !pp->fake) {
E 13
I 13
				    if (pp != NULL && !(pp->flags & PG_FAKE)) {
E 13
E 2
					vm_page_lock_queues();
					vm_page_free(p);
					vm_page_unlock_queues();
				    }
				    else {
					if (pp) {
					    /* may be someone waiting for it */
					    PAGE_WAKEUP(pp);
					    vm_page_lock_queues();
					    vm_page_free(pp);
					    vm_page_unlock_queues();
					}
					vm_page_rename(p, object, new_offset);
				    }
				}
			}

			/*
			 *	Move the pager from backing_object to object.
			 *
			 *	XXX We're only using part of the paging space
			 *	for keeps now... we ought to discard the
			 *	unused portion.
			 */

D 18
			object->pager = backing_object->pager;
			object->paging_offset += backing_offset;
E 18
I 18
			if (backing_object->pager) {
				object->pager = backing_object->pager;
				object->paging_offset = backing_offset +
					backing_object->paging_offset;
				backing_object->pager = NULL;
			}
E 18

D 2
			backing_object->pager = vm_pager_null;
E 2
I 2
D 18
			backing_object->pager = NULL;
E 2

E 18
			/*
			 *	Object now shadows whatever backing_object did.
			 *	Note that the reference to backing_object->shadow
			 *	moves from within backing_object to within object.
			 */

			object->shadow = backing_object->shadow;
			object->shadow_offset += backing_object->shadow_offset;
D 2
			if (object->shadow != VM_OBJECT_NULL &&
			    object->shadow->copy != VM_OBJECT_NULL) {
E 2
I 2
			if (object->shadow != NULL &&
			    object->shadow->copy != NULL) {
E 2
				panic("vm_object_collapse: we collapsed a copy-object!");
			}
			/*
			 *	Discard backing_object.
			 *
			 *	Since the backing object has no pages, no
			 *	pager left, and no object references within it,
			 *	all that is necessary is to dispose of it.
			 */

			vm_object_unlock(backing_object);

			simple_lock(&vm_object_list_lock);
D 17
			queue_remove(&vm_object_list, backing_object,
						vm_object_t, object_list);
E 17
I 17
			TAILQ_REMOVE(&vm_object_list, backing_object,
			    object_list);
E 17
			vm_object_count--;
			simple_unlock(&vm_object_list_lock);

			free((caddr_t)backing_object, M_VMOBJ);

			object_collapses++;
		}
		else {
			/*
			 *	If all of the pages in the backing object are
			 *	shadowed by the parent object, the parent
			 *	object no longer has to shadow the backing
			 *	object; it can shadow the next one in the
			 *	chain.
			 *
			 *	The backing object must not be paged out - we'd
			 *	have to check all of the paged-out pages, as
			 *	well.
			 */

D 2
			if (backing_object->pager != vm_pager_null) {
E 2
I 2
			if (backing_object->pager != NULL) {
E 2
				vm_object_unlock(backing_object);
				return;
			}

			/*
			 *	Should have a check for a 'small' number
			 *	of pages here.
			 */

D 17
			p = (vm_page_t) queue_first(&backing_object->memq);
			while (!queue_end(&backing_object->memq,
					  (queue_entry_t) p)) {

E 17
I 17
			for (p = backing_object->memq.tqh_first;
			     p != NULL;
			     p = p->listq.tqe_next) {
E 17
				new_offset = (p->offset - backing_offset);

				/*
				 *	If the parent has a page here, or if
				 *	this page falls outside the parent,
				 *	keep going.
				 *
				 *	Otherwise, the backing_object must be
				 *	left in the chain.
				 */

				if (p->offset >= backing_offset &&
D 18
				    new_offset <= size &&
E 18
I 18
				    new_offset < size &&
E 18
				    ((pp = vm_page_lookup(object, new_offset))
D 2
				      == VM_PAGE_NULL ||
E 2
I 2
				      == NULL ||
E 2
D 13
				     pp->fake)) {
E 13
I 13
				     (pp->flags & PG_FAKE))) {
E 13
					/*
					 *	Page still needed.
					 *	Can't go any further.
					 */
					vm_object_unlock(backing_object);
					return;
				}
D 17
				p = (vm_page_t) queue_next(&p->listq);
E 17
			}

			/*
			 *	Make the parent shadow the next object
			 *	in the chain.  Deallocating backing_object
			 *	will not remove it, since its reference
			 *	count is at least 2.
			 */

D 18
			vm_object_reference(object->shadow = backing_object->shadow);
E 18
I 18
			object->shadow = backing_object->shadow;
			vm_object_reference(object->shadow);
E 18
			object->shadow_offset += backing_object->shadow_offset;

I 19
			/*
			 *	Backing object might have had a copy pointer
			 *	to us.  If it did, clear it. 
			 */
			if (backing_object->copy == object) {
D 20
				backing_object->copy = VM_OBJECT_NULL;
E 20
I 20
				backing_object->copy = NULL;
E 20
			}
	
E 19
			/*	Drop the reference count on backing_object.
			 *	Since its ref_count was at least 2, it
			 *	will not vanish; so we don't need to call
			 *	vm_object_deallocate.
			 */
			backing_object->ref_count--;
			vm_object_unlock(backing_object);

			object_bypasses ++;

		}

		/*
		 *	Try again with this object's new backing object.
		 */
	}
}

/*
 *	vm_object_page_remove: [internal]
 *
 *	Removes all physical pages in the specified
 *	object range from the object's list of pages.
 *
 *	The object must be locked.
 */
D 21
void vm_object_page_remove(object, start, end)
E 21
I 21
void
vm_object_page_remove(object, start, end)
E 21
	register vm_object_t	object;
	register vm_offset_t	start;
	register vm_offset_t	end;
{
	register vm_page_t	p, next;

D 2
	if (object == VM_OBJECT_NULL)
E 2
I 2
	if (object == NULL)
E 2
		return;

D 17
	p = (vm_page_t) queue_first(&object->memq);
	while (!queue_end(&object->memq, (queue_entry_t) p)) {
		next = (vm_page_t) queue_next(&p->listq);
E 17
I 17
	for (p = object->memq.tqh_first; p != NULL; p = next) {
		next = p->listq.tqe_next;
E 17
		if ((start <= p->offset) && (p->offset < end)) {
D 4
			pmap_remove_all(VM_PAGE_TO_PHYS(p));
E 4
I 4
			pmap_page_protect(VM_PAGE_TO_PHYS(p), VM_PROT_NONE);
E 4
			vm_page_lock_queues();
			vm_page_free(p);
			vm_page_unlock_queues();
		}
D 17
		p = next;
E 17
	}
}

/*
 *	Routine:	vm_object_coalesce
 *	Function:	Coalesces two objects backing up adjoining
 *			regions of memory into a single object.
 *
 *	returns TRUE if objects were combined.
 *
 *	NOTE:	Only works at the moment if the second object is NULL -
 *		if it's not, which object do we lock first?
 *
 *	Parameters:
 *		prev_object	First object to coalesce
 *		prev_offset	Offset into prev_object
 *		next_object	Second object into coalesce
 *		next_offset	Offset into next_object
 *
 *		prev_size	Size of reference to prev_object
 *		next_size	Size of reference to next_object
 *
 *	Conditions:
 *	The object must *not* be locked.
 */
D 21
boolean_t vm_object_coalesce(prev_object, next_object,
E 21
I 21
boolean_t
vm_object_coalesce(prev_object, next_object,
E 21
			prev_offset, next_offset,
			prev_size, next_size)

	register vm_object_t	prev_object;
	vm_object_t	next_object;
	vm_offset_t	prev_offset, next_offset;
	vm_size_t	prev_size, next_size;
{
	vm_size_t	newsize;

#ifdef	lint
	next_offset++;
D 15
#endif	lint
E 15
I 15
#endif
E 15

D 2
	if (next_object != VM_OBJECT_NULL) {
E 2
I 2
	if (next_object != NULL) {
E 2
		return(FALSE);
	}

D 2
	if (prev_object == VM_OBJECT_NULL) {
E 2
I 2
	if (prev_object == NULL) {
E 2
		return(TRUE);
	}

	vm_object_lock(prev_object);

	/*
	 *	Try to collapse the object first
	 */
	vm_object_collapse(prev_object);

	/*
	 *	Can't coalesce if:
	 *	. more than one reference
	 *	. paged out
	 *	. shadows another object
	 *	. has a copy elsewhere
	 *	(any of which mean that the pages not mapped to
	 *	prev_entry may be in use anyway)
	 */

	if (prev_object->ref_count > 1 ||
D 2
		prev_object->pager != vm_pager_null ||
		prev_object->shadow != VM_OBJECT_NULL ||
		prev_object->copy != VM_OBJECT_NULL) {
E 2
I 2
		prev_object->pager != NULL ||
		prev_object->shadow != NULL ||
		prev_object->copy != NULL) {
E 2
		vm_object_unlock(prev_object);
		return(FALSE);
	}

	/*
	 *	Remove any pages that may still be in the object from
	 *	a previous deallocation.
	 */

	vm_object_page_remove(prev_object,
			prev_offset + prev_size,
			prev_offset + prev_size + next_size);

	/*
	 *	Extend the object if necessary.
	 */
	newsize = prev_offset + prev_size + next_size;
	if (newsize > prev_object->size)
		prev_object->size = newsize;

	vm_object_unlock(prev_object);
	return(TRUE);
}

/*
 *	vm_object_print:	[ debug ]
 */
D 21
void vm_object_print(object, full)
E 21
I 21
void
vm_object_print(object, full)
E 21
	vm_object_t	object;
	boolean_t	full;
{
	register vm_page_t	p;
	extern indent;

	register int count;

D 2
	if (object == VM_OBJECT_NULL)
E 2
I 2
	if (object == NULL)
E 2
		return;

	iprintf("Object 0x%x: size=0x%x, res=%d, ref=%d, ",
		(int) object, (int) object->size,
		object->resident_page_count, object->ref_count);
	printf("pager=0x%x+0x%x, shadow=(0x%x)+0x%x\n",
	       (int) object->pager, (int) object->paging_offset,
	       (int) object->shadow, (int) object->shadow_offset);
	printf("cache: next=0x%x, prev=0x%x\n",
D 14
	       object->cached_list.next, object->cached_list.prev);
E 14
I 14
D 17
	       object->cached_list.qe_next, object->cached_list.qe_prev);
E 17
I 17
	       object->cached_list.tqe_next, object->cached_list.tqe_prev);
E 17
E 14

	if (!full)
		return;

	indent += 2;
	count = 0;
D 17
	p = (vm_page_t) queue_first(&object->memq);
	while (!queue_end(&object->memq, (queue_entry_t) p)) {
E 17
I 17
	for (p = object->memq.tqh_first; p != NULL; p = p->listq.tqe_next) {
E 17
		if (count == 0)
			iprintf("memory:=");
		else if (count == 6) {
			printf("\n");
			iprintf(" ...");
			count = 0;
		} else
			printf(",");
		count++;

		printf("(off=0x%x,page=0x%x)", p->offset, VM_PAGE_TO_PHYS(p));
D 17
		p = (vm_page_t) queue_next(&p->listq);
E 17
	}
	if (count != 0)
		printf("\n");
	indent -= 2;
}
E 1
