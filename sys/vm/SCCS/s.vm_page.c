h20397
s 00030/00016/00654
d D 8.4 95/01/09 17:50:17 cgd 20 19
c KNF, and 64-bit safety.
e
s 00002/00002/00668
d D 8.3 94/03/21 16:39:39 hibler 19 18
c round kentry_data_size to a page since pmap_bootstrap_alloc will
c anyway (we needlessly waste space ow)
e
s 00034/00038/00636
d D 8.2 93/12/30 16:01:05 mckusick 18 17
c convert to use new queue structures
e
s 00002/00002/00672
d D 8.1 93/06/11 16:38:13 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00672
d D 7.15 93/02/10 20:44:55 mckusick 16 15
c have to account for one extra needed page
e
s 00030/00032/00644
d D 7.14 92/10/01 17:54:18 mckusick 15 14
c convert vm_page bit fields to flags
e
s 00006/00005/00670
d D 7.13 92/05/04 17:05:40 bostic 14 13
c new include format
e
s 00001/00001/00674
d D 7.12 92/02/24 09:24:30 mckusick 13 12
c lint
e
s 00005/00051/00670
d D 7.11 92/02/19 18:06:33 torek 12 11
c move definition of vm_page_init into vm_page.h so can be shared
e
s 00002/00000/00719
d D 7.10 91/11/20 16:36:58 marc 11 10
c 3100 changes (from ralph)
e
s 00028/00054/00691
d D 7.9 91/08/29 17:29:16 william 10 8
c added pmap_bootstrap_alloc() to deal with machine dependent
c allocation of memory before malloc() can be used.
e
s 00053/00079/00666
d R 7.9 91/08/29 16:43:47 william 9 8
c added pmap_bootstrap_alloc() to deal with machine dependant
c allocation of memory before malloc() can be used.
e
s 00024/00024/00721
d D 7.8 91/08/28 15:39:33 mckusick 8 7
c vm_stat is merged into vmmeter structure
e
s 00001/00001/00744
d D 7.7 91/08/16 17:40:24 mckusick 7 6
c lint
e
s 00017/00000/00728
d D 7.6 91/08/15 16:45:19 william 6 5
c temporary and permanent changes for i386, correcting bug where
c the "hole" is allocated as ordinary memory, testing for if we allocate it 
c in the page structures themselves, touchup the "kstack-in-the-user-space" 
c kludge, and obscure fix to spontaineous unwiring of kstack (if ever pagable)
e
s 00025/00037/00703
d D 7.5 91/07/25 23:04:00 mckusick 5 4
c numerous statistics move to vm_stat;
c software page size now set by vm_set_page_size
e
s 00021/00000/00719
d D 7.4 91/05/07 09:30:06 hibler 4 3
c added DEBUG version of vm_page_init to init the 
c pagerowned and ptpage fields
e
s 00027/00004/00692
d D 7.3 91/04/21 18:36:18 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00010/00012/00686
d D 7.2 91/04/20 10:50:16 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00698/00000/00000
d D 7.1 90/12/05 18:08:21 mckusick 1 0
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
D 17
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
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
 *	Resident memory management module.
 */

D 2
#include "types.h"
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_page.h"
#include "../vm/vm_prot.h"
#include "../vm/vm_statistics.h"
#include "../vm/vm_pageout.h"
#include "../vm/pmap.h"
E 2
I 2
D 14
#include "param.h"
E 14
I 14
#include <sys/param.h>
#include <sys/systm.h>
E 14
E 2

I 2
D 14
#include "vm.h"
#include "vm_map.h"
#include "vm_page.h"
#include "vm_pageout.h"
E 14
I 14
#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_map.h>
#include <vm/vm_pageout.h>
E 14

E 2
/*
 *	Associated with page of user-allocatable memory is a
 *	page structure.
 */

D 18
queue_head_t	*vm_page_buckets;		/* Array of buckets */
E 18
I 18
struct pglist	*vm_page_buckets;		/* Array of buckets */
E 18
int		vm_page_bucket_count = 0;	/* How big is array? */
int		vm_page_hash_mask;		/* Mask for hash function */
simple_lock_data_t	bucket_lock;		/* lock for all buckets XXX */

D 5
vm_size_t	page_size  = 4096;
vm_size_t	page_mask  = 4095;
int		page_shift = 12;

E 5
D 18
queue_head_t	vm_page_queue_free;
queue_head_t	vm_page_queue_active;
queue_head_t	vm_page_queue_inactive;
E 18
I 18
struct pglist	vm_page_queue_free;
struct pglist	vm_page_queue_active;
struct pglist	vm_page_queue_inactive;
E 18
simple_lock_data_t	vm_page_queue_lock;
simple_lock_data_t	vm_page_queue_free_lock;

I 10
/* has physical page allocation been initialized? */
boolean_t vm_page_startup_initialized;

E 10
vm_page_t	vm_page_array;
long		first_page;
long		last_page;
vm_offset_t	first_phys_addr;
vm_offset_t	last_phys_addr;
I 5
vm_size_t	page_mask;
int		page_shift;
E 5

D 5
int	vm_page_free_count;
int	vm_page_active_count;
int	vm_page_inactive_count;
int	vm_page_wire_count;
int	vm_page_laundry_count;

int	vm_page_free_target = 0;
int	vm_page_free_min = 0;
int	vm_page_inactive_target = 0;
int	vm_page_free_reserved = 0;

E 5
/*
 *	vm_set_page_size:
 *
 *	Sets the page size, perhaps based upon the memory
 *	size.  Must be called before any use of page-size
 *	dependent functions.
 *
D 5
 *	Sets page_shift and page_mask from page_size.
E 5
I 5
D 8
 *	Sets page_shift and page_mask from vm_stat.page_size.
E 8
I 8
 *	Sets page_shift and page_mask from cnt.v_page_size.
E 8
E 5
 */
D 20
void vm_set_page_size()
E 20
I 20
void
vm_set_page_size()
E 20
{
D 5
	page_mask = page_size - 1;
E 5

D 5
	if ((page_mask & page_size) != 0)
E 5
I 5
D 8
	if (vm_stat.page_size == 0)
		vm_stat.page_size = DEFAULT_PAGE_SIZE;
	page_mask = vm_stat.page_size - 1;
	if ((page_mask & vm_stat.page_size) != 0)
E 8
I 8
	if (cnt.v_page_size == 0)
		cnt.v_page_size = DEFAULT_PAGE_SIZE;
	page_mask = cnt.v_page_size - 1;
	if ((page_mask & cnt.v_page_size) != 0)
E 8
E 5
		panic("vm_set_page_size: page size not a power of two");
D 5

E 5
	for (page_shift = 0; ; page_shift++)
D 5
		if ((1 << page_shift) == page_size)
E 5
I 5
D 8
		if ((1 << page_shift) == vm_stat.page_size)
E 8
I 8
		if ((1 << page_shift) == cnt.v_page_size)
E 8
E 5
			break;
}


/*
 *	vm_page_startup:
 *
 *	Initializes the resident memory module.
 *
 *	Allocates memory for the page cells, and
 *	for the object/offset-to-page hash table headers.
 *	Each page cell is initialized and placed on the free list.
 */
D 10
vm_offset_t vm_page_startup(start, end, vaddr)
	register vm_offset_t	start;
	vm_offset_t	end;
	register vm_offset_t	vaddr;
E 10
I 10
D 20
void vm_page_startup(start, end)
E 20
I 20
void
vm_page_startup(start, end)
E 20
	vm_offset_t	*start;
	vm_offset_t	*end;
E 10
{
D 10
	register vm_offset_t	mapped;
E 10
	register vm_page_t	m;
D 18
	register queue_t	bucket;
E 18
I 18
	register struct pglist	*bucket;
E 18
	vm_size_t		npages;
D 10
	register vm_offset_t	new_start;
E 10
	int			i;
	vm_offset_t		pa;
D 10

E 10
	extern	vm_offset_t	kentry_data;
	extern	vm_size_t	kentry_data_size;


	/*
	 *	Initialize the locks
	 */

	simple_lock_init(&vm_page_queue_free_lock);
	simple_lock_init(&vm_page_queue_lock);

	/*
	 *	Initialize the queue headers for the free queue,
	 *	the active queue and the inactive queue.
	 */

D 18
	queue_init(&vm_page_queue_free);
	queue_init(&vm_page_queue_active);
	queue_init(&vm_page_queue_inactive);
E 18
I 18
	TAILQ_INIT(&vm_page_queue_free);
	TAILQ_INIT(&vm_page_queue_active);
	TAILQ_INIT(&vm_page_queue_inactive);
E 18

	/*
D 10
	 *	Allocate (and initialize) the hash table buckets.
E 10
I 10
	 *	Calculate the number of hash table buckets.
E 10
	 *
	 *	The number of buckets MUST BE a power of 2, and
	 *	the actual value is the next power of 2 greater
	 *	than the number of physical pages in the system.
	 *
	 *	Note:
	 *		This computation can be tweaked if desired.
	 */

D 10
	vm_page_buckets = (queue_t) vaddr;
	bucket = vm_page_buckets;
E 10
	if (vm_page_bucket_count == 0) {
		vm_page_bucket_count = 1;
D 10
		while (vm_page_bucket_count < atop(end - start))
E 10
I 10
		while (vm_page_bucket_count < atop(*end - *start))
E 10
			vm_page_bucket_count <<= 1;
	}

	vm_page_hash_mask = vm_page_bucket_count - 1;

	/*
D 10
	 *	Validate these addresses.
E 10
I 10
	 *	Allocate (and initialize) the hash table buckets.
E 10
	 */
I 10
D 18
	vm_page_buckets = (queue_t) pmap_bootstrap_alloc(vm_page_bucket_count
		* sizeof(struct queue_entry));
E 18
I 18
	vm_page_buckets = (struct pglist *)
	    pmap_bootstrap_alloc(vm_page_bucket_count * sizeof(struct pglist));
E 18
	bucket = vm_page_buckets;
E 10

D 10
	new_start = round_page(((queue_t)start) + vm_page_bucket_count);
	mapped = vaddr;
	vaddr = pmap_map(mapped, start, new_start,
			VM_PROT_READ|VM_PROT_WRITE);
	start = new_start;
	blkclr((caddr_t) mapped, vaddr - mapped);
	mapped = vaddr;

E 10
	for (i = vm_page_bucket_count; i--;) {
D 18
		queue_init(bucket);
E 18
I 18
		TAILQ_INIT(bucket);
E 18
		bucket++;
	}

	simple_lock_init(&bucket_lock);

	/*
D 10
	 *	round (or truncate) the addresses to our page size.
E 10
I 10
	 *	Truncate the remainder of physical memory to our page size.
E 10
	 */

D 10
	end = trunc_page(end);
E 10
I 10
	*end = trunc_page(*end);
E 10

	/*
	 *	Pre-allocate maps and map entries that cannot be dynamically
	 *	allocated via malloc().  The maps include the kernel_map and
	 *	kmem_map which must be initialized before malloc() will
	 *	work (obviously).  Also could include pager maps which would
	 *	be allocated before kmeminit.
	 *
	 *	Allow some kernel map entries... this should be plenty
	 *	since people shouldn't be cluttering up the kernel
	 *	map (they should use their own maps).
	 */

D 19
	kentry_data_size = MAX_KMAP * sizeof(struct vm_map) +
			   MAX_KMAPENT * sizeof(struct vm_map_entry);
E 19
I 19
	kentry_data_size = round_page(MAX_KMAP*sizeof(struct vm_map) +
				      MAX_KMAPENT*sizeof(struct vm_map_entry));
E 19
D 10
	kentry_data_size = round_page(kentry_data_size);
	kentry_data = (vm_offset_t) vaddr;
	vaddr += kentry_data_size;
E 10
I 10
	kentry_data = (vm_offset_t) pmap_bootstrap_alloc(kentry_data_size);
E 10

	/*
D 10
	 *	Validate these zone addresses.
	 */

	new_start = start + (vaddr - mapped);
	pmap_map(mapped, start, new_start, VM_PROT_READ|VM_PROT_WRITE);
	blkclr((caddr_t) mapped, (vaddr - mapped));
	mapped = vaddr;
	start = new_start;

	/*
E 10
 	 *	Compute the number of pages of memory that will be
	 *	available for use (taking into account the overhead
	 *	of a page structure per page).
	 */

D 5
	vm_page_free_count = npages =
E 5
I 5
D 8
	vm_stat.free_count = npages =
E 8
I 8
D 16
	cnt.v_free_count = npages =
E 8
E 5
D 10
		(end - start)/(PAGE_SIZE + sizeof(struct vm_page));
E 10
I 10
		(*end - *start)/(PAGE_SIZE + sizeof(struct vm_page));
E 16
I 16
	cnt.v_free_count = npages = (*end - *start + sizeof(struct vm_page))
		/ (PAGE_SIZE + sizeof(struct vm_page));
E 16
E 10

	/*
D 10
	 *	Initialize the mem entry structures now, and
	 *	put them in the free queue.
E 10
I 10
	 *	Record the extent of physical memory that the
	 *	virtual memory system manages.
E 10
	 */

D 10
	m = vm_page_array = (vm_page_t) vaddr;
	first_page = start;
E 10
I 10
	first_page = *start;
E 10
	first_page += npages*sizeof(struct vm_page);
	first_page = atop(round_page(first_page));
	last_page  = first_page + npages - 1;

	first_phys_addr = ptoa(first_page);
	last_phys_addr  = ptoa(last_page) + PAGE_MASK;

I 6

D 10
#ifdef i386
	/* XXX - waiting for pmap_bootstrap_malloc() (or somebody like him) */
	if (first_phys_addr > 0xa0000)
		panic("vm_page_startup: fell into the hole");
#endif
E 10
E 6
	/*
D 10
	 *	Validate these addresses.
E 10
I 10
	 *	Allocate and clear the mem entry structures.
E 10
	 */

D 10
	new_start = start + (round_page(m + npages) - mapped);
	mapped = pmap_map(mapped, start, new_start,
			VM_PROT_READ|VM_PROT_WRITE);
	start = new_start;
E 10
I 10
	m = vm_page_array = (vm_page_t)
		pmap_bootstrap_alloc(npages * sizeof(struct vm_page));
E 10

	/*
D 10
	 *	Clear all of the page structures
E 10
I 10
	 *	Initialize the mem entry structures now, and
	 *	put them in the free queue.
E 10
	 */
D 10
	blkclr((caddr_t)m, npages * sizeof(*m));
E 10

	pa = first_phys_addr;
	while (npages--) {
D 15
		m->copy_on_write = FALSE;
		m->wanted = FALSE;
		m->inactive = FALSE;
		m->active = FALSE;
		m->busy = FALSE;
E 15
I 15
		m->flags = 0;
E 15
D 2
		m->object = VM_OBJECT_NULL;
E 2
I 2
		m->object = NULL;
E 2
		m->phys_addr = pa;
I 6
#ifdef i386
		if (pmap_isvalidphys(m->phys_addr)) {
D 18
			queue_enter(&vm_page_queue_free, m, vm_page_t, pageq);
E 18
I 18
			TAILQ_INSERT_TAIL(&vm_page_queue_free, m, pageq);
E 18
		} else {
			/* perhaps iomem needs it's own type, or dev pager? */
D 15
			m->fictitious = 1;
			m->busy = TRUE;
E 15
I 15
			m->flags |= PG_FICTITIOUS | PG_BUSY;
E 15
D 8
			vm_stat.free_count--;
E 8
I 8
			cnt.v_free_count--;
E 8
		}
#else /* i386 */
E 6
D 18
		queue_enter(&vm_page_queue_free, m, vm_page_t, pageq);
E 18
I 18
		TAILQ_INSERT_TAIL(&vm_page_queue_free, m, pageq);
E 18
I 6
#endif /* i386 */
E 6
		m++;
		pa += PAGE_SIZE;
	}

	/*
	 *	Initialize vm_pages_needed lock here - don't wait for pageout
	 *	daemon	XXX
	 */
	simple_lock_init(&vm_pages_needed_lock);

D 10
	return(mapped);
E 10
I 10
	/* from now on, pmap_bootstrap_alloc can't be used */
	vm_page_startup_initialized = TRUE;
E 10
}

/*
 *	vm_page_hash:
 *
 *	Distributes the object/offset key pair among hash buckets.
 *
 *	NOTE:  This macro depends on vm_page_bucket_count being a power of 2.
 */
#define vm_page_hash(object, offset) \
D 20
	(((unsigned)object+(unsigned)atop(offset))&vm_page_hash_mask)
E 20
I 20
	(((unsigned long)object+(unsigned long)atop(offset))&vm_page_hash_mask)
E 20

/*
 *	vm_page_insert:		[ internal use only ]
 *
 *	Inserts the given mem entry into the object/object-page
 *	table and object list.
 *
 *	The object and page must be locked.
 */

D 10
void vm_page_insert(mem, object, offset)
E 10
I 10
D 13
static void vm_page_insert(mem, object, offset)
E 13
I 13
D 20
void vm_page_insert(mem, object, offset)
E 20
I 20
void
vm_page_insert(mem, object, offset)
E 20
E 13
E 10
	register vm_page_t	mem;
	register vm_object_t	object;
	register vm_offset_t	offset;
{
D 18
	register queue_t	bucket;
E 18
I 18
	register struct pglist	*bucket;
E 18
	int			spl;

	VM_PAGE_CHECK(mem);

D 15
	if (mem->tabled)
E 15
I 15
	if (mem->flags & PG_TABLED)
E 15
		panic("vm_page_insert: already inserted");

	/*
	 *	Record the object/offset pair in this page
	 */

	mem->object = object;
	mem->offset = offset;

	/*
	 *	Insert it into the object_object/offset hash table
	 */

	bucket = &vm_page_buckets[vm_page_hash(object, offset)];
	spl = splimp();
	simple_lock(&bucket_lock);
D 18
	queue_enter(bucket, mem, vm_page_t, hashq);
E 18
I 18
	TAILQ_INSERT_TAIL(bucket, mem, hashq);
E 18
	simple_unlock(&bucket_lock);
	(void) splx(spl);

	/*
	 *	Now link into the object's list of backed pages.
	 */

D 18
	queue_enter(&object->memq, mem, vm_page_t, listq);
E 18
I 18
	TAILQ_INSERT_TAIL(&object->memq, mem, listq);
E 18
D 15
	mem->tabled = TRUE;
E 15
I 15
	mem->flags |= PG_TABLED;
E 15

	/*
	 *	And show that the object has one more resident
	 *	page.
	 */

	object->resident_page_count++;
}

/*
 *	vm_page_remove:		[ internal use only ]
I 10
 *				NOTE: used by device pager as well -wfj
E 10
 *
 *	Removes the given mem entry from the object/offset-page
 *	table and the object page list.
 *
 *	The object and page must be locked.
 */

D 20
void vm_page_remove(mem)
E 20
I 20
void
vm_page_remove(mem)
E 20
	register vm_page_t	mem;
{
D 18
	register queue_t	bucket;
E 18
I 18
	register struct pglist	*bucket;
E 18
	int			spl;

	VM_PAGE_CHECK(mem);

D 15
	if (!mem->tabled)
E 15
I 15
	if (!(mem->flags & PG_TABLED))
E 15
		return;

	/*
	 *	Remove from the object_object/offset hash table
	 */

	bucket = &vm_page_buckets[vm_page_hash(mem->object, mem->offset)];
	spl = splimp();
	simple_lock(&bucket_lock);
D 18
	queue_remove(bucket, mem, vm_page_t, hashq);
E 18
I 18
	TAILQ_REMOVE(bucket, mem, hashq);
E 18
	simple_unlock(&bucket_lock);
	(void) splx(spl);

	/*
	 *	Now remove from the object's list of backed pages.
	 */

D 18
	queue_remove(&mem->object->memq, mem, vm_page_t, listq);
E 18
I 18
	TAILQ_REMOVE(&mem->object->memq, mem, listq);
E 18

	/*
	 *	And show that the object has one fewer resident
	 *	page.
	 */

	mem->object->resident_page_count--;

D 15
	mem->tabled = FALSE;
E 15
I 15
	mem->flags &= ~PG_TABLED;
E 15
}

/*
 *	vm_page_lookup:
 *
 *	Returns the page associated with the object/offset
D 2
 *	pair specified; if none is found, VM_PAGE_NULL is returned.
E 2
I 2
 *	pair specified; if none is found, NULL is returned.
E 2
 *
 *	The object must be locked.  No side effects.
 */

D 20
vm_page_t vm_page_lookup(object, offset)
E 20
I 20
vm_page_t
vm_page_lookup(object, offset)
E 20
	register vm_object_t	object;
	register vm_offset_t	offset;
{
	register vm_page_t	mem;
D 18
	register queue_t	bucket;
E 18
I 18
	register struct pglist	*bucket;
E 18
	int			spl;

	/*
	 *	Search the hash table for this object/offset pair
	 */

	bucket = &vm_page_buckets[vm_page_hash(object, offset)];

	spl = splimp();
	simple_lock(&bucket_lock);
D 18
	mem = (vm_page_t) queue_first(bucket);
	while (!queue_end(bucket, (queue_entry_t) mem)) {
E 18
I 18
	for (mem = bucket->tqh_first; mem != NULL; mem = mem->hashq.tqe_next) {
E 18
		VM_PAGE_CHECK(mem);
		if ((mem->object == object) && (mem->offset == offset)) {
			simple_unlock(&bucket_lock);
			splx(spl);
			return(mem);
		}
D 18
		mem = (vm_page_t) queue_next(&mem->hashq);
E 18
	}

	simple_unlock(&bucket_lock);
	splx(spl);
D 2
	return(VM_PAGE_NULL);
E 2
I 2
	return(NULL);
E 2
}

/*
 *	vm_page_rename:
 *
 *	Move the given memory entry from its
 *	current object to the specified target object/offset.
 *
 *	The object must be locked.
 */
D 20
void vm_page_rename(mem, new_object, new_offset)
E 20
I 20
void
vm_page_rename(mem, new_object, new_offset)
E 20
	register vm_page_t	mem;
	register vm_object_t	new_object;
	vm_offset_t		new_offset;
{
	if (mem->object == new_object)
		return;

	vm_page_lock_queues();	/* keep page from moving out from
				   under pageout daemon */
    	vm_page_remove(mem);
	vm_page_insert(mem, new_object, new_offset);
	vm_page_unlock_queues();
}

D 12
void		vm_page_init(mem, object, offset)
	vm_page_t	mem;
	vm_object_t	object;
	vm_offset_t	offset;
{
I 4
#ifdef DEBUG
E 4
#define	vm_page_init(mem, object, offset)  {\
		(mem)->busy = TRUE; \
		(mem)->tabled = FALSE; \
		vm_page_insert((mem), (object), (offset)); \
		(mem)->absent = FALSE; \
		(mem)->fictitious = FALSE; \
		(mem)->page_lock = VM_PROT_NONE; \
		(mem)->unlock_request = VM_PROT_NONE; \
		(mem)->laundry = FALSE; \
		(mem)->active = FALSE; \
		(mem)->inactive = FALSE; \
		(mem)->wire_count = 0; \
		(mem)->clean = TRUE; \
		(mem)->copy_on_write = FALSE; \
		(mem)->fake = TRUE; \
I 4
		(mem)->pagerowned = FALSE; \
		(mem)->ptpage = FALSE; \
E 4
	}
I 4
#else
#define	vm_page_init(mem, object, offset)  {\
		(mem)->busy = TRUE; \
		(mem)->tabled = FALSE; \
		vm_page_insert((mem), (object), (offset)); \
		(mem)->absent = FALSE; \
		(mem)->fictitious = FALSE; \
		(mem)->page_lock = VM_PROT_NONE; \
		(mem)->unlock_request = VM_PROT_NONE; \
		(mem)->laundry = FALSE; \
		(mem)->active = FALSE; \
		(mem)->inactive = FALSE; \
		(mem)->wire_count = 0; \
		(mem)->clean = TRUE; \
		(mem)->copy_on_write = FALSE; \
		(mem)->fake = TRUE; \
	}
#endif
E 4

	vm_page_init(mem, object, offset);
}

E 12
/*
 *	vm_page_alloc:
 *
 *	Allocate and return a memory cell associated
 *	with this VM object/offset pair.
 *
 *	Object must be locked.
 */
D 20
vm_page_t vm_page_alloc(object, offset)
E 20
I 20
vm_page_t
vm_page_alloc(object, offset)
E 20
	vm_object_t	object;
	vm_offset_t	offset;
{
	register vm_page_t	mem;
	int		spl;

	spl = splimp();				/* XXX */
	simple_lock(&vm_page_queue_free_lock);
D 18
	if (queue_empty(&vm_page_queue_free)) {
E 18
I 18
	if (vm_page_queue_free.tqh_first == NULL) {
E 18
		simple_unlock(&vm_page_queue_free_lock);
		splx(spl);
D 2
		return(VM_PAGE_NULL);
E 2
I 2
		return(NULL);
E 2
	}

D 18
	queue_remove_first(&vm_page_queue_free, mem, vm_page_t, pageq);
E 18
I 18
	mem = vm_page_queue_free.tqh_first;
	TAILQ_REMOVE(&vm_page_queue_free, mem, pageq);
E 18

D 5
	vm_page_free_count--;
E 5
I 5
D 8
	vm_stat.free_count--;
E 8
I 8
	cnt.v_free_count--;
E 8
E 5
	simple_unlock(&vm_page_queue_free_lock);
	splx(spl);

D 12
	vm_page_init(mem, object, offset);
E 12
I 12
	VM_PAGE_INIT(mem, object, offset);
E 12

	/*
	 *	Decide if we should poke the pageout daemon.
	 *	We do this if the free count is less than the low
	 *	water mark, or if the free count is less than the high
	 *	water mark (but above the low water mark) and the inactive
	 *	count is less than its target.
	 *
	 *	We don't have the counts locked ... if they change a little,
	 *	it doesn't really matter.
	 */

D 5
	if ((vm_page_free_count < vm_page_free_min) ||
			((vm_page_free_count < vm_page_free_target) &&
			(vm_page_inactive_count < vm_page_inactive_target)))
E 5
I 5
D 8
	if ((vm_stat.free_count < vm_stat.free_min) ||
			((vm_stat.free_count < vm_stat.free_target) &&
			(vm_stat.inactive_count < vm_stat.inactive_target)))
E 8
I 8
D 12
	if ((cnt.v_free_count < cnt.v_free_min) ||
			((cnt.v_free_count < cnt.v_free_target) &&
			(cnt.v_inactive_count < cnt.v_inactive_target)))
E 12
I 12
	if (cnt.v_free_count < cnt.v_free_min ||
	    (cnt.v_free_count < cnt.v_free_target &&
	     cnt.v_inactive_count < cnt.v_inactive_target))
E 12
E 8
E 5
D 7
		thread_wakeup(&vm_pages_needed);
E 7
I 7
D 20
		thread_wakeup((int)&vm_pages_needed);
E 20
I 20
		thread_wakeup(&vm_pages_needed);
E 20
E 7
D 12
	return(mem);
E 12
I 12
	return (mem);
E 12
}

/*
 *	vm_page_free:
 *
 *	Returns the given page to the free list,
 *	disassociating it with any VM object.
 *
 *	Object and page must be locked prior to entry.
 */
D 20
void vm_page_free(mem)
E 20
I 20
void
vm_page_free(mem)
E 20
	register vm_page_t	mem;
{
	vm_page_remove(mem);
D 15
	if (mem->active) {
E 15
I 15
	if (mem->flags & PG_ACTIVE) {
E 15
D 18
		queue_remove(&vm_page_queue_active, mem, vm_page_t, pageq);
E 18
I 18
		TAILQ_REMOVE(&vm_page_queue_active, mem, pageq);
E 18
D 15
		mem->active = FALSE;
E 15
I 15
		mem->flags &= ~PG_ACTIVE;
E 15
D 5
		vm_page_active_count--;
E 5
I 5
D 8
		vm_stat.active_count--;
E 8
I 8
		cnt.v_active_count--;
E 8
E 5
	}

D 15
	if (mem->inactive) {
E 15
I 15
	if (mem->flags & PG_INACTIVE) {
E 15
D 18
		queue_remove(&vm_page_queue_inactive, mem, vm_page_t, pageq);
E 18
I 18
		TAILQ_REMOVE(&vm_page_queue_inactive, mem, pageq);
E 18
D 15
		mem->inactive = FALSE;
E 15
I 15
		mem->flags &= ~PG_INACTIVE;
E 15
D 5
		vm_page_inactive_count--;
E 5
I 5
D 8
		vm_stat.inactive_count--;
E 8
I 8
		cnt.v_inactive_count--;
E 8
E 5
	}

D 15
	if (!mem->fictitious) {
E 15
I 15
	if (!(mem->flags & PG_FICTITIOUS)) {
E 15
		int	spl;

		spl = splimp();
		simple_lock(&vm_page_queue_free_lock);
D 18
		queue_enter(&vm_page_queue_free, mem, vm_page_t, pageq);
E 18
I 18
		TAILQ_INSERT_TAIL(&vm_page_queue_free, mem, pageq);
E 18

D 5
		vm_page_free_count++;
E 5
I 5
D 8
		vm_stat.free_count++;
E 8
I 8
		cnt.v_free_count++;
E 8
E 5
		simple_unlock(&vm_page_queue_free_lock);
		splx(spl);
	}
}

/*
 *	vm_page_wire:
 *
 *	Mark this page as wired down by yet
 *	another map, removing it from paging queues
 *	as necessary.
 *
 *	The page queues must be locked.
 */
D 20
void vm_page_wire(mem)
E 20
I 20
void
vm_page_wire(mem)
E 20
	register vm_page_t	mem;
{
	VM_PAGE_CHECK(mem);

	if (mem->wire_count == 0) {
D 15
		if (mem->active) {
E 15
I 15
		if (mem->flags & PG_ACTIVE) {
E 15
D 18
			queue_remove(&vm_page_queue_active, mem, vm_page_t,
						pageq);
E 18
I 18
			TAILQ_REMOVE(&vm_page_queue_active, mem, pageq);
E 18
D 5
			vm_page_active_count--;
E 5
I 5
D 8
			vm_stat.active_count--;
E 8
I 8
			cnt.v_active_count--;
E 8
E 5
D 15
			mem->active = FALSE;
E 15
I 15
			mem->flags &= ~PG_ACTIVE;
E 15
		}
D 15
		if (mem->inactive) {
E 15
I 15
		if (mem->flags & PG_INACTIVE) {
E 15
D 18
			queue_remove(&vm_page_queue_inactive, mem, vm_page_t,
						pageq);
E 18
I 18
			TAILQ_REMOVE(&vm_page_queue_inactive, mem, pageq);
E 18
D 5
			vm_page_inactive_count--;
E 5
I 5
D 8
			vm_stat.inactive_count--;
E 8
I 8
			cnt.v_inactive_count--;
E 8
E 5
D 15
			mem->inactive = FALSE;
E 15
I 15
			mem->flags &= ~PG_INACTIVE;
E 15
		}
D 5
		vm_page_wire_count++;
E 5
I 5
D 8
		vm_stat.wire_count++;
E 8
I 8
		cnt.v_wire_count++;
E 8
E 5
	}
	mem->wire_count++;
}

/*
 *	vm_page_unwire:
 *
 *	Release one wiring of this page, potentially
 *	enabling it to be paged again.
 *
 *	The page queues must be locked.
 */
D 20
void vm_page_unwire(mem)
E 20
I 20
void
vm_page_unwire(mem)
E 20
	register vm_page_t	mem;
{
	VM_PAGE_CHECK(mem);

	mem->wire_count--;
	if (mem->wire_count == 0) {
D 18
		queue_enter(&vm_page_queue_active, mem, vm_page_t, pageq);
E 18
I 18
		TAILQ_INSERT_TAIL(&vm_page_queue_active, mem, pageq);
E 18
D 5
		vm_page_active_count++;
E 5
I 5
D 8
		vm_stat.active_count++;
E 8
I 8
		cnt.v_active_count++;
E 8
E 5
D 15
		mem->active = TRUE;
E 15
I 15
		mem->flags |= PG_ACTIVE;
E 15
D 5
		vm_page_wire_count--;
E 5
I 5
D 8
		vm_stat.wire_count--;
E 8
I 8
		cnt.v_wire_count--;
E 8
E 5
	}
}

/*
 *	vm_page_deactivate:
 *
 *	Returns the given page to the inactive list,
 *	indicating that no physical maps have access
 *	to this page.  [Used by the physical mapping system.]
 *
 *	The page queues must be locked.
 */
D 20
void vm_page_deactivate(m)
E 20
I 20
void
vm_page_deactivate(m)
E 20
	register vm_page_t	m;
{
	VM_PAGE_CHECK(m);

	/*
	 *	Only move active pages -- ignore locked or already
	 *	inactive ones.
	 */

D 15
	if (m->active) {
E 15
I 15
	if (m->flags & PG_ACTIVE) {
E 15
		pmap_clear_reference(VM_PAGE_TO_PHYS(m));
D 18
		queue_remove(&vm_page_queue_active, m, vm_page_t, pageq);
		queue_enter(&vm_page_queue_inactive, m, vm_page_t, pageq);
E 18
I 18
		TAILQ_REMOVE(&vm_page_queue_active, m, pageq);
		TAILQ_INSERT_TAIL(&vm_page_queue_inactive, m, pageq);
E 18
D 15
		m->active = FALSE;
		m->inactive = TRUE;
E 15
I 15
		m->flags &= ~PG_ACTIVE;
		m->flags |= PG_INACTIVE;
E 15
D 5
		vm_page_active_count--;
		vm_page_inactive_count++;
E 5
I 5
D 8
		vm_stat.active_count--;
		vm_stat.inactive_count++;
E 8
I 8
		cnt.v_active_count--;
		cnt.v_inactive_count++;
E 8
E 5
		if (pmap_is_modified(VM_PAGE_TO_PHYS(m)))
D 15
			m->clean = FALSE;
		m->laundry = !m->clean;
E 15
I 15
			m->flags &= ~PG_CLEAN;
		if (m->flags & PG_CLEAN)
			m->flags &= ~PG_LAUNDRY;
		else
			m->flags |= PG_LAUNDRY;
E 15
	}
}

/*
 *	vm_page_activate:
 *
 *	Put the specified page on the active list (if appropriate).
 *
 *	The page queues must be locked.
 */

D 20
void vm_page_activate(m)
E 20
I 20
void
vm_page_activate(m)
E 20
	register vm_page_t	m;
{
	VM_PAGE_CHECK(m);

D 15
	if (m->inactive) {
E 15
I 15
	if (m->flags & PG_INACTIVE) {
E 15
D 18
		queue_remove(&vm_page_queue_inactive, m, vm_page_t,
						pageq);
E 18
I 18
		TAILQ_REMOVE(&vm_page_queue_inactive, m, pageq);
E 18
D 5
		vm_page_inactive_count--;
E 5
I 5
D 8
		vm_stat.inactive_count--;
E 8
I 8
		cnt.v_inactive_count--;
E 8
E 5
D 15
		m->inactive = FALSE;
E 15
I 15
		m->flags &= ~PG_INACTIVE;
E 15
	}
	if (m->wire_count == 0) {
D 15
		if (m->active)
E 15
I 15
		if (m->flags & PG_ACTIVE)
E 15
			panic("vm_page_activate: already active");

D 18
		queue_enter(&vm_page_queue_active, m, vm_page_t, pageq);
E 18
I 18
		TAILQ_INSERT_TAIL(&vm_page_queue_active, m, pageq);
E 18
D 15
		m->active = TRUE;
E 15
I 15
		m->flags |= PG_ACTIVE;
E 15
D 5
		vm_page_active_count++;
E 5
I 5
D 8
		vm_stat.active_count++;
E 8
I 8
		cnt.v_active_count++;
E 8
E 5
	}
}

/*
 *	vm_page_zero_fill:
 *
 *	Zero-fill the specified page.
 *	Written as a standard pagein routine, to
 *	be used by the zero-fill object.
 */

D 20
boolean_t vm_page_zero_fill(m)
E 20
I 20
boolean_t
vm_page_zero_fill(m)
E 20
	vm_page_t	m;
{
	VM_PAGE_CHECK(m);

I 11
D 15
	m->clean = 0;
E 15
I 15
	m->flags &= ~PG_CLEAN;
E 15
E 11
	pmap_zero_page(VM_PAGE_TO_PHYS(m));
	return(TRUE);
}

/*
 *	vm_page_copy:
 *
 *	Copy one page to another
 */

D 20
void vm_page_copy(src_m, dest_m)
E 20
I 20
void
vm_page_copy(src_m, dest_m)
E 20
	vm_page_t	src_m;
	vm_page_t	dest_m;
{
	VM_PAGE_CHECK(src_m);
	VM_PAGE_CHECK(dest_m);

I 11
D 15
	dest_m->clean = 0;
E 15
I 15
	dest_m->flags &= ~PG_CLEAN;
E 15
E 11
	pmap_copy_page(VM_PAGE_TO_PHYS(src_m), VM_PAGE_TO_PHYS(dest_m));
}
E 1
