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
 * $Log:	vm_resident.c,v $
 * Revision 2.17  89/08/02  08:13:38  jsb
 * 	Increased zdata_size to allow for more zones (for afs, nfs, ...).
 * 	[89/07/31  17:13:06  jsb]
 * 
 * Revision 2.16  89/06/12  14:53:18  jsb
 * 	Picked up bug fix (missing splimp) from Sequent via dlb.
 * 	[89/06/12  14:38:34  jsb]
 * 
 * Revision 2.15  89/06/02  11:38:00  rvb
 * 	Changed from 8 to 15 the threshold that triggers invocation of
 * 	Debugger() in vm_page_alloc().  On the M500 with few buffers
 * 	was causing trouble. [af]
 * 
 * Revision 2.14  89/04/18  21:29:17  mwyoung
 * 	Recent history:
 * 		Add vm_page_fictitious_zone.
 * 		Handle absent pages in vm_page_free().
 * 		Eliminate use of owner and clean fields to vm_page_t.
 * 	History condensation:
 * 	 	Reorganize vm_page_startup to avoid bad physical addresses.
 * 		Use a template for initialization [mwyoung].
 * 		Provide separate vm_page_init() function for outside use [mwyoung].
 * 		Split up page system lock [dbg].
 * 		Initial external memory management integration [bolosky, mwyoung].
 * 		Plenty of bug fixes [dbg, avie, mwyoung].
 * 		Converted to active/inactive/free list queues [avie].
 * 		Created [avie].
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm/vm_page.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Resident memory management module.
 */
#include <cpus.h>
#include <mach_xp.h>

#include <kern/task.h>
#include <sys/types.h>
#include <vm/vm_map.h>
#include <vm/vm_page.h>
#include <mach/vm_prot.h>
#include <mach/vm_statistics.h>
#include <vm/vm_pageout.h>
#include <kern/zalloc.h>
#include <machine/machparam.h>		/* for spl's */

#include <vm/pmap.h>

#include <kern/xpr.h>

#if	MACH_XP
#include <kern/thread.h>
#endif	MACH_XP

/*
 *	Associated with page of user-allocatable memory is a
 *	page structure.
 */

vm_offset_t	map_data;
vm_size_t	map_data_size;

vm_offset_t	kentry_data;
vm_size_t	kentry_data_size;

int		kentry_count = 1024;		/* To init kentry_data_size */

vm_offset_t	zdata;
vm_size_t	zdata_size;

queue_head_t	*vm_page_buckets;		/* Array of buckets */
int		vm_page_bucket_count = 0;	/* How big is array? */
int		vm_page_hash_mask;		/* Mask for hash function */
decl_simple_lock_data(,bucket_lock)		/* lock for all buckets XXX */

vm_size_t	page_size  = 4096;
vm_size_t	page_mask  = 4095;
int		page_shift = 12;

queue_head_t	vm_page_queue_free;
queue_head_t	vm_page_queue_active;
queue_head_t	vm_page_queue_inactive;
decl_simple_lock_data(,vm_page_queue_lock)
decl_simple_lock_data(,vm_page_queue_free_lock)
boolean_t	vm_page_free_wanted;

vm_page_t	vm_page_array;
vm_offset_t	vm_page_array_next;
vm_offset_t	vm_page_array_end;
vm_size_t	vm_page_array_size = 0;

long		first_page;
long		last_page;
vm_offset_t	first_phys_addr;
vm_offset_t	last_phys_addr;

int	vm_page_free_count;
int	vm_page_active_count;
int	vm_page_inactive_count;
int	vm_page_wire_count;
int	vm_page_laundry_count;

int	vm_page_free_target = 0;
int	vm_page_free_min = 0;
int	vm_page_inactive_target = 0;
int	vm_page_free_reserved = 0;

struct vm_page	vm_page_template;

zone_t	vm_page_fictitious_zone;

/*
 *	vm_set_page_size:
 *
 *	Sets the page size, perhaps based upon the memory
 *	size.  Must be called before any use of page-size
 *	dependent functions.
 *
 *	Sets page_shift and page_mask from page_size.
 */
void vm_set_page_size()
{
	page_mask = page_size - 1;

	if ((page_mask & page_size) != 0)
		panic("vm_set_page_size: page size not a power of two");

	for (page_shift = 0; ; page_shift++)
		if ((1 << page_shift) == page_size)
			break;
}

boolean_t	vm_resident_new_initialization = TRUE;

/*
 *	vm_page_startup:
 *
 *	Initializes the resident memory module.
 *
 *	Allocates memory for the page cells, and
 *	for the object/offset-to-page hash table headers.
 *	Each page cell is initialized and placed on the free list.
 */
vm_offset_t vm_page_startup(start, end, vaddr)
	register vm_offset_t	start;
	vm_offset_t	end;
	register vm_offset_t	vaddr;
{
	register vm_page_t	m;
	register queue_t	bucket;
	int			i;

	/*
	 *	Initialize the vm_page template.
	 *	[Indented items must be reset later.]
	 */

	m = &vm_page_template;
	 m->object = VM_OBJECT_NULL;
	 m->offset = 0;
	m->wire_count = 0;

	m->inactive = FALSE;
	m->active = FALSE;
	m->laundry = FALSE;
	m->dirty = FALSE;
	m->free = FALSE;

	m->busy = TRUE;
	m->wanted = FALSE;
	m->tabled = FALSE;
	m->fictitious = FALSE;
	m->absent = FALSE;
	m->error = FALSE;
	
	 m->phys_addr = 0;

	m->page_lock = VM_PROT_NONE;
	m->unlock_request = VM_PROT_NONE;
	m->max_mapping = VM_PROT_NONE;

	/*
	 *	Initialize the page queues.
	 */

	simple_lock_init(&vm_page_queue_free_lock);
	simple_lock_init(&vm_page_queue_lock);

	queue_init(&vm_page_queue_free);
	queue_init(&vm_page_queue_active);
	queue_init(&vm_page_queue_inactive);

	vm_page_free_wanted = FALSE;

	/*
	 *	Normalize the physical address range
	 */

	start = round_page(start);
	end = trunc_page(end);

	/*
	 *	Allocate (and initialize) the virtual-to-physical
	 *	table hash buckets.
	 *
	 *	The number of buckets should be a power of two to
	 *	get a good hash function.  The following computation
	 *	chooses the first power of two that is greater
	 *	than the number of physical pages in the system.
	 */

	vm_page_buckets = (queue_t) vaddr;
	if (vm_page_bucket_count == 0) {
		vm_page_bucket_count = 1;
		while (vm_page_bucket_count < atop(end - start))
			vm_page_bucket_count <<= 1;
	}

	vm_page_hash_mask = vm_page_bucket_count - 1;

	if (vm_page_hash_mask & vm_page_bucket_count)
		printf("vm_page_startup: WARNING -- strange page hash\n");

	/*
	 *	Validate these addresses.
	 */

#define PMAP_MAP(size)							\
	MACRO_BEGIN							\
	vm_size_t	o;						\
	vm_size_t	amount_to_map;					\
									\
	amount_to_map = round_page(size);				\
	for (o = amount_to_map; o != 0; o -= PAGE_SIZE) {		\
		while (!pmap_valid_page(start))				\
			start += PAGE_SIZE;				\
		pmap_enter(kernel_pmap, vaddr, start,			\
			VM_PROT_READ|VM_PROT_WRITE, FALSE);		\
		vaddr += PAGE_SIZE;					\
		start += PAGE_SIZE;					\
	}								\
	blkclr((caddr_t) (vaddr - amount_to_map), amount_to_map);	\
	MACRO_END

	PMAP_MAP(vm_page_bucket_count * sizeof(queue_head_t));

	for (bucket = vm_page_buckets, i = vm_page_bucket_count; i--; bucket++)
		queue_init(bucket);

	simple_lock_init(&bucket_lock);

	/*
	 *	Steal pages for some zones that cannot be
	 *	dynamically allocated.
	 */

	/**/ {
	vm_size_t	size;

	zdata_size = round_page(128 * sizeof(struct zone));
	zdata = (vm_offset_t) vaddr;
	size = zdata_size;

	map_data_size = round_page(10 * sizeof(struct vm_map));
	map_data = (vm_offset_t) vaddr + size;
	size += map_data_size;

	kentry_data_size = round_page(kentry_count*sizeof(struct vm_map_entry));
	kentry_data = (vm_offset_t) vaddr + size;
	size += kentry_data_size;

	PMAP_MAP(size);
	/**/ }

	first_page = atop(first_phys_addr = start);
	last_page = atop(last_phys_addr = end - 1);

	if (vm_page_array_size == 0)
		vm_page_array_size = atop(end - start) *
					sizeof(struct vm_page);

	vm_page_array = (vm_page_t) (vm_page_array_next = vaddr);
	vm_page_array_end = (vaddr += round_page(vm_page_array_size));

	vm_page_create(start, (end - start), pmap_valid_page);

#if	!MACH_XP
	/*
	 *	Initialize vm_pages_needed lock here - don't wait for pageout
	 *	daemon	XXX
	 */
	simple_lock_init(&vm_pages_needed_lock);

#endif	!MACH_XP
	return(vaddr);
}

void vm_page_create(phys, size, validity_check)
	vm_offset_t	phys;
	vm_size_t	size;
	boolean_t	(*validity_check)();
{
	static
	int		pages_left = 0;
	static
	vm_page_t	p;

	for (; size != 0; size -= PAGE_SIZE, phys += PAGE_SIZE) {
		if ((validity_check == (boolean_t (*)()) 0) ||
		    validity_check(phys)) {
			/*
			 *	If we have no page structures left,
			 *	we'll use this page to make more.
			 */

			if (pages_left == 0) {
				if (vm_page_array_next == vm_page_array_end) {
					printf("vm_page_create: no more space\n");
					return;
				}

				pmap_enter(kernel_pmap, vm_page_array_next,
					phys, VM_PROT_READ|VM_PROT_WRITE, FALSE);

				p = (vm_page_t) vm_page_array_next;
				vm_page_array_next += PAGE_SIZE;
				pages_left = PAGE_SIZE / sizeof(struct vm_page);
			} else {
				vm_page_init(p, VM_OBJECT_NULL, 0, phys);
				vm_page_free(p);

				p++; pages_left--;
			}
		}
	}
}

/*
 *	Routine:	vm_page_module_init
 *	Purpose:
 *		Second initialization pass, to be done after
 *		the basic VM system is ready.
 */
void		vm_page_module_init()
{
	vm_page_fictitious_zone = zinit(
				(vm_size_t) sizeof(struct vm_page),
				VM_MAX_KERNEL_ADDRESS - VM_MIN_KERNEL_ADDRESS,
				PAGE_SIZE,
				FALSE, "fictitious pages");
				
}

/*
 *	vm_page_hash:
 *
 *	Distributes the object/offset key pair among hash buckets.
 *
 *	NOTE:	To get a good hash function, the bucket count should
 *		be a power of two.
 */
#define vm_page_hash(object, offset) \
	(((unsigned)object+(unsigned)atop(offset))&vm_page_hash_mask)

/*
 *	vm_page_insert:		[ internal use only ]
 *
 *	Inserts the given mem entry into the object/object-page
 *	table and object list.
 *
 *	The object and page must be locked.
 */

void vm_page_insert(mem, object, offset)
	register vm_page_t	mem;
	register vm_object_t	object;
	register vm_offset_t	offset;
{
	register queue_t	bucket;
	int			spl;

	VM_PAGE_CHECK(mem);

	if (mem->tabled)
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
	queue_enter(bucket, mem, vm_page_t, hashq);
	simple_unlock(&bucket_lock);
	(void) splx(spl);

	/*
	 *	Now link into the object's list of backed pages.
	 */

	queue_enter(&object->memq, mem, vm_page_t, listq);
	mem->tabled = TRUE;

	/*
	 *	And show that the object has one more resident
	 *	page.
	 */

	object->resident_page_count++;
}

/*
 *	vm_page_remove:		[ internal use only ]
 *
 *	Removes the given mem entry from the object/offset-page
 *	table and the object page list.
 *
 *	The object and page must be locked.
 */

void vm_page_remove(mem)
	register vm_page_t	mem;
{
	register queue_t	bucket;
	int			spl;

	VM_PAGE_CHECK(mem);

	if (!mem->tabled)
		return;

	/*
	 *	Remove from the object_object/offset hash table
	 */

	bucket = &vm_page_buckets[vm_page_hash(mem->object, mem->offset)];
	spl = splimp();
	simple_lock(&bucket_lock);
	queue_remove(bucket, mem, vm_page_t, hashq);
	simple_unlock(&bucket_lock);
	(void) splx(spl);

	/*
	 *	Now remove from the object's list of backed pages.
	 */

	queue_remove(&mem->object->memq, mem, vm_page_t, listq);

	/*
	 *	And show that the object has one fewer resident
	 *	page.
	 */

	mem->object->resident_page_count--;

	mem->tabled = FALSE;
}

/*
 *	vm_page_lookup:
 *
 *	Returns the page associated with the object/offset
 *	pair specified; if none is found, VM_PAGE_NULL is returned.
 *
 *	The object must be locked.  No side effects.
 */

vm_page_t vm_page_lookup(object, offset)
	register vm_object_t	object;
	register vm_offset_t	offset;
{
	register vm_page_t	mem;
	register queue_t	bucket;
	int			spl;

	/*
	 *	Search the hash table for this object/offset pair
	 */

	bucket = &vm_page_buckets[vm_page_hash(object, offset)];

	spl = splimp();
	simple_lock(&bucket_lock);
	mem = (vm_page_t) queue_first(bucket);
	while (!queue_end(bucket, (queue_entry_t) mem)) {
		VM_PAGE_CHECK(mem);
		if ((mem->object == object) && (mem->offset == offset)) {
			simple_unlock(&bucket_lock);
			splx(spl);
			return(mem);
		}
		mem = (vm_page_t) queue_next(&mem->hashq);
	}

	simple_unlock(&bucket_lock);
	splx(spl);
	return(VM_PAGE_NULL);
}

/*
 *	vm_page_rename:
 *
 *	Move the given memory entry from its
 *	current object to the specified target object/offset.
 *
 *	The object must be locked.
 */
void vm_page_rename(mem, new_object, new_offset)
	register vm_page_t	mem;
	register vm_object_t	new_object;
	vm_offset_t		new_offset;
{
	if (mem->object == new_object)
		return;

	vm_page_lock_queues();	/* keep page from moving out from
				   under pageout daemon */

	XPR(XPR_VM_PAGE, ("vm_page_rename: page %x, new object %x, offset %x\n",
		mem, new_object, new_offset));

    	vm_page_remove(mem);
	vm_page_insert(mem, new_object, new_offset);
	vm_page_unlock_queues();
}

/*
 *	vm_page_init:
 *
 *	Initialize the given vm_page, entering it into
 *	the VP table at the given (object, offset),
 *	and noting its physical address.
 *
 *	Implemented using a template set up in vm_page_startup.
 *	All fields except those passed as arguments are static.
 */
void		vm_page_init(mem, object, offset, phys_addr)
	vm_page_t	mem;
	vm_object_t	object;
	vm_offset_t	offset;
	vm_offset_t	phys_addr;
{
#define vm_page_init(page, object, offset, pa)  { \
		register \
		vm_offset_t	a = (pa); \
		*(page) = vm_page_template; \
		(page)->phys_addr = a; \
		if ((object) != VM_OBJECT_NULL) \
			vm_page_insert((page), (object), (offset)); \
	}

	vm_page_init(mem, object, offset, phys_addr);
}

boolean_t	vm_page_alloc_verify = FALSE;
#ifdef	vax
/* for some obscure reason, MP Vaxen don't work with FALSE */
boolean_t	vm_page_alloc_fifo = NCPUS > 1;
#else	vax
boolean_t	vm_page_alloc_fifo = FALSE;
#endif	vax

/*
 *	vm_page_alloc:
 *
 *	Allocate and return a memory cell associated
 *	with this VM object/offset pair.
 *
 *	Object must be locked.
 */
vm_page_t vm_page_alloc(object, offset)
	vm_object_t	object;
	vm_offset_t	offset;
{
	register vm_page_t	mem;
	int		spl;

	spl = splimp();				/* XXX */
	simple_lock(&vm_page_queue_free_lock);
	if (queue_empty(&vm_page_queue_free)) {
#if	MACH_XP
		if (current_thread()->vm_privilege)
			printf("vm_page_alloc: cannot allocate to vm-privileged thread\n");
#endif	MACH_XP
		simple_unlock(&vm_page_queue_free_lock);
		splx(spl);
		return(VM_PAGE_NULL);
	}

#if	MACH_XP
	if ((vm_page_free_count < vm_page_free_reserved) && !current_thread()->vm_privilege) {
		simple_unlock(&vm_page_queue_free_lock);
		splx(spl);
		return(VM_PAGE_NULL);
	}
	if (vm_page_free_count < (vm_page_free_reserved - 15))
		Debugger("vm_page_alloc");

#endif	MACH_XP

	if (vm_page_alloc_fifo) {
		queue_remove_first(&vm_page_queue_free, mem, vm_page_t, pageq);
	} else {
		queue_remove_last(&vm_page_queue_free, mem, vm_page_t, pageq);
	}

	vm_page_free_count--;
	simple_unlock(&vm_page_queue_free_lock);
	splx(spl);

	if (vm_page_alloc_verify && !pmap_verify_free(mem->phys_addr))
		Debugger("vm_page_alloc: page is in use!\n");

	vm_page_init(mem, object, offset, mem->phys_addr);

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

	if ((vm_page_free_count < vm_page_free_min) ||
			((vm_page_free_count < vm_page_free_target) &&
			(vm_page_inactive_count < vm_page_inactive_target)))
#if	MACH_XP
		thread_wakeup((int) &vm_page_free_wanted);
#else	MACH_XP
		thread_wakeup((int) &vm_pages_needed);
#endif	MACH_XP
	return(mem);
}

/*
 *	vm_page_free:
 *
 *	Returns the given page to the free list,
 *	disassociating it with any VM object.
 *
 *	Object and page queues must be locked prior to entry.
 */
void vm_page_free(mem)
	register vm_page_t	mem;
{
	if (mem->free) {
		printf("vm_page_free: duplicate free page %x\n", mem);
		panic("vm_page_free");
	}

	vm_page_remove(mem);
	VM_PAGE_QUEUES_REMOVE(mem);

#if	MACH_XP
	if (mem->laundry)
		mem->laundry = FALSE;
	if (vm_page_laundry_count > 0)
		vm_page_laundry_count--;

#endif	MACH_XP

	PAGE_WAKEUP(mem);

	if (mem->absent)
		vm_object_absent_release(mem->object);

	if (!mem->fictitious) {
		int	spl;

		spl = splimp();
		simple_lock(&vm_page_queue_free_lock);
		queue_enter(&vm_page_queue_free, mem, vm_page_t, pageq);
		mem->free = TRUE;
		vm_page_free_count++;

#if	MACH_XP
		if (vm_page_free_wanted) {
			thread_wakeup((int) &vm_page_free_count);
			vm_page_free_wanted = FALSE;
		}
#endif	MACH_XP
		simple_unlock(&vm_page_queue_free_lock);
		splx(spl);
	}
}

void		vm_page_free_synchronized(m)
	vm_page_t	m;
{
	vm_page_lock_queues();
	vm_page_free(m);
	vm_page_unlock_queues();
}

#if	MACH_XP
void		vm_wait()
{
	int s;

	s = splimp();
	simple_lock(&vm_page_queue_free_lock);
	if (!vm_page_free_wanted) {
		vm_page_free_wanted = TRUE;
		thread_wakeup((int)&vm_page_free_wanted);
	}
	thread_sleep((int)&vm_page_free_count,
		     simple_lock_addr(vm_page_queue_free_lock),
		     FALSE);
	splx(s);
}
#endif	MACH_XP

/*
 *	vm_page_wire:
 *
 *	Mark this page as wired down by yet
 *	another map, removing it from paging queues
 *	as necessary.
 *
 *	The page's object and the page queues must be locked.
 */
void vm_page_wire(mem)
	register vm_page_t	mem;
{
	VM_PAGE_CHECK(mem);

	if (mem->wire_count == 0) {
		VM_PAGE_QUEUES_REMOVE(mem);
		vm_page_wire_count++;
	}
	mem->wire_count++;
}

/*
 *	vm_page_unwire:
 *
 *	Release one wiring of this page, potentially
 *	enabling it to be paged again.
 *
 *	The page's object and the page queues must be locked.
 */
void vm_page_unwire(mem)
	register vm_page_t	mem;
{
	VM_PAGE_CHECK(mem);

	if (--mem->wire_count == 0) {
		queue_enter(&vm_page_queue_active, mem, vm_page_t, pageq);
		vm_page_active_count++;
		mem->active = TRUE;
		vm_page_wire_count--;
		PAGE_WAKEUP(mem);
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
void vm_page_deactivate(m)
	register vm_page_t	m;
{
	VM_PAGE_CHECK(m);

	/*
	 *	Only move active pages -- ignore locked or already
	 *	inactive ones.
	 */

	if (m->active) {
		pmap_clear_reference(VM_PAGE_TO_PHYS(m));
		queue_remove(&vm_page_queue_active, m, vm_page_t, pageq);
		queue_enter(&vm_page_queue_inactive, m, vm_page_t, pageq);
		m->active = FALSE;
		m->inactive = TRUE;
		vm_page_active_count--;
		vm_page_inactive_count++;
#if	!MACH_XP
		if (pmap_is_modified(VM_PAGE_TO_PHYS(m)))
			m->clean = FALSE;

		m->laundry = !m->clean;
#endif	!MACH_XP
	}
}

/*
 *	vm_page_activate:
 *
 *	Put the specified page on the active list (if appropriate).
 *
 *	The page queues must be locked.
 */

void vm_page_activate(m)
	register vm_page_t	m;
{
	VM_PAGE_CHECK(m);

	if (m->inactive) {
		queue_remove(&vm_page_queue_inactive, m, vm_page_t,
						pageq);
		vm_page_inactive_count--;
		m->inactive = FALSE;
	}
	if (m->wire_count == 0) {
		if (m->active)
			panic("vm_page_activate: already active");

		queue_enter(&vm_page_queue_active, m, vm_page_t, pageq);
		m->active = TRUE;
		vm_page_active_count++;
	}
}

/*
 *	vm_page_zero_fill:
 *
 *	Zero-fill the specified page.
 *	Written as a standard pagein routine, to
 *	be used by the zero-fill object.
 */

boolean_t vm_page_zero_fill(m)
	vm_page_t	m;
{
	VM_PAGE_CHECK(m);

	XPR(XPR_VM_PAGE, ("vm_page_zero_fill: page %x, object %x, offset %x\n",
		m, m->object, m->offset));

	pmap_zero_page(VM_PAGE_TO_PHYS(m));
	return(TRUE);
}

/*
 *	vm_page_copy:
 *
 *	Copy one page to another
 */

void vm_page_copy(src_m, dest_m)
	vm_page_t	src_m;
	vm_page_t	dest_m;
{
	VM_PAGE_CHECK(src_m);
	VM_PAGE_CHECK(dest_m);

	XPR(XPR_VM_PAGE, ("vm_page_copy: from object %x, offset %x, to object %x, offset %x\n",
		src_m->object, src_m->offset, dest_m->object, dest_m->offset));

	pmap_copy_page(VM_PAGE_TO_PHYS(src_m), VM_PAGE_TO_PHYS(dest_m));
}

#include <mach_kdb.h>
#if	MACH_KDB
#define printf	kdbprintf

/*
 *	Routine:	vm_page_print [exported]
 */
void		vm_page_print(p)
	vm_page_t	p;
{
	iprintf("Page 0x%X: object 0x%X,", (int) p, (int) p->object);
	 printf(" offset 0x%X", (int) p->offset);
	 printf("wire_count %d,", p->wire_count);
	 printf(" %s",
		(p->active ? "active" : (p->inactive ? "inactive" : "loose")));
	 printf("%s",
		(p->free ? " free" : ""));
	 printf("%s ",
		(p->laundry ? " laundry" : ""));
	 printf("%s",
		(p->dirty ? "dirty" : "clean"));
	 printf("%s",
	 	(p->busy ? " busy" : ""));
	 printf("%s",
	 	(p->absent ? " absent" : ""));
	 printf("%s",
	 	(p->error ? " errror" : ""));
	 printf("%s",
		(p->fictitious ? " fictitious" : ""));
	 printf("%s",
		(p->wanted ? " wanted" : ""));
	 printf("%s,",
		(p->tabled ? "" : "not_tabled"));
	 printf("phys_addr = 0x%X, lock = 0x%X, unlock_request = 0x%X\n",
	 	(int) p->phys_addr,
		(int) p->page_lock,
		(int) p->unlock_request);
}
#endif	MACH_KDB
