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
 * Revision 2.24  90/09/10  21:09:47  mrt
 * 	Fixed vm_page_zero_fill() to account for zerofills itself
 * 	in the vm_stat structure, rather then relying on the caller.
 * 	[90/09/10  17:34:09  af]
 * 
 * Revision 2.23  90/08/30  11:51:41  bohman
 * 	Made vm_page_free() not mess with vm_page_wire_count
 * 	for private pages.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.22  90/07/03  16:58:04  mrt
 * 	Add init of precious bit and other bits to vm_page_template.
 * 	[90/06/13            dlb]
 * 	Pick up pure kernel changes: make vm_page_free handle wired
 * 	count correctly.  Make vm_page_deactivate work on pages that
 * 	aren't active.  Also increase number of kernel map entries.
 * 	[90/06/11            dlb]
 * 	Reserved more virtual addresses in vm_page_startup for the
 * 	vm_page_array. The sun may call vm_page_create after autoconf
 * 	to give back some physical memory and may need those addresses.
 * 	[90/06/19            mrt]
 * 
 * Revision 2.21  89/12/22  15:57:32  rpd
 * 	Remove scaffolding code -- Bug found.
 * 	[89/12/21            dlb]
 * 	Added scaffolding code to panic in vm_page_activate; looking for
 * 	XP bug that crashes kernel when heavy use is made of memory objects
 * 	backed by netmemory server on a multiprocessor.
 * 
 * 	PAGE_WAKEUP --> PAGE_WAKEUP_DONE in vm_page_free() to reflect
 * 	the fact that it clears the busy flag.  Remove PAGE_WAKEUP from
 * 	vm_page_unwire; callers are responsible for this, and it didn't
 * 	work right if the page was wired more than once.
 * 	[89/12/13            dlb]
 * 
 * Revision 2.20  89/10/10  14:28:55  mwyoung
 * 	Retract special preemption technology for pageout daemon.
 * 	[89/10/10            mwyoung]
 * 
 * Revision 2.19  89/10/10  13:16:33  mwyoung
 * 	Add documentation of global variables.
 * 
 * 	Remove XP conditionals.
 * 	[89/10/10 mwyoung]
 * 
 * 	Declare vm_page_bucket_t for VP table; add count and lock fields.
 * 	[89/04/29            mwyoung]
 * 
 * 	Separate "private" from "fictitious" page attributes.
 * 	[89/04/22            mwyoung]
 * 
 * Revision 2.18  89/10/03  19:31:46  rpd
 * 	Made the deactivate-behind optimization conditional on
 * 	vm_page_alloc_deactivate_behind, which is FALSE for now.
 * 	[89/08/31  19:32:59  rpd]
 * 
 * 	I turned on the deactivate-behind optimization in vm_page_alloc.
 * 	Not sure why it didn't seem to work when I first tried it.
 * 	[89/08/20  23:21:04  rpd]
 * 
 * 	Optimization from NeXT:  changed vm_page_alloc to detect sequential
 * 	access and inactivate the previous page.  I'm not sure this works
 * 	yet, so it is #if'd out.
 * 	[89/08/19  23:49:18  rpd]
 * 
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
#include <kern/thread.h>

/*
 *	Associated with page of user-allocatable memory is a
 *	page structure.
 */

/*
 *	This module maps and initializes memory for several
 *	other modules at bootstrap time.  The following
 *	addresses and sizes describe these boot-time mappings.
 */
vm_offset_t	map_data;
vm_size_t	map_data_size;
vm_offset_t	kentry_data;
vm_size_t	kentry_data_size;
int		kentry_count = 1536;		/* To init kentry_data_size */
vm_offset_t	zdata;
vm_size_t	zdata_size;

/*
 *	The vm_page_lookup() routine, which provides for fast
 *	(virtual memory object, offset) to page lookup, employs
 *	the following hash table.  The vm_page_{insert,remove}
 *	routines install and remove associations in the table.
 *	[This table is often called the virtual-to-physical,
 *	or VP, table.]
 */
typedef struct {
	queue_head_t	pages;
	int		count;
	decl_simple_lock_data(,lock)
} vm_page_bucket_t;

vm_page_bucket_t *vm_page_buckets;		/* Array of buckets */
int		vm_page_bucket_count = 0;	/* How big is array? */
int		vm_page_hash_mask;		/* Mask for hash function */

/*
 *	The virtual page size is currently implemented as a runtime
 *	variable, but is constant once initialized using vm_set_page_size.
 *	This initialization must be done in the machine-dependent
 *	bootstrap sequence, before calling other machine-independent
 *	initializations.
 *
 *	All references to the virtual page size outside this
 *	module must use the PAGE_SIZE constant.
 */
vm_size_t	page_size  = 4096;
vm_size_t	page_mask  = 4095;
int		page_shift = 12;

/*
 *	Resident page structures are initialized from
 *	a template (see vm_page_alloc).
 *
 *	When adding a new field to the virtual memory
 *	object structure, be sure to add initialization
 *	(see vm_page_startup).
 */
struct vm_page	vm_page_template;

/*
 *	Resident pages that represent real memory
 *	are allocated from a free list.
 */
queue_head_t	vm_page_queue_free;
decl_simple_lock_data(,vm_page_queue_free_lock)
boolean_t	vm_page_free_wanted;
int	vm_page_free_count;

/*
 *	The actual memory for these resident page structures
 *	is stolen at bootstrap time.  The vm_page_array_next
 *	and vm_page_array_end variables denote the range of
 *	stolen memory that has not yet been used.
 *
 *	Historically, the resident page structures formed
 *	an array, directly corresponding to physical addresses.
 *	The vm_page_array, first_page and last_page variables
 *	are preserved for debugging.  The first_phys_addr
 *	and last_phys_addr variables are preserved for debugging,
 *	and also for older machine-dependent modules that
 *	may still depend on them.
 */
vm_page_t	vm_page_array;
vm_offset_t	vm_page_array_next;
vm_offset_t	vm_page_array_end;
vm_size_t	vm_page_array_size = 0;

long		first_page;
long		last_page;
vm_offset_t	first_phys_addr;
vm_offset_t	last_phys_addr;

/*
 *	Occasionally, the virtual memory system uses
 *	resident page structures that do not refer to
 *	real pages, for example to leave a page with
 *	important state information in the VP table.
 *
 *	These page structures are allocated the way
 *	most other kernel structures are.
 */
zone_t	vm_page_fictitious_zone;

/*
 *	Resident page structures are also chained on
 *	queues that are used by the page replacement
 *	system (pageout daemon).  These queues are
 *	defined here, but are shared by the pageout
 *	module.
 */
queue_head_t	vm_page_queue_active;
queue_head_t	vm_page_queue_inactive;
decl_simple_lock_data(,vm_page_queue_lock)
int	vm_page_active_count;
int	vm_page_inactive_count;
int	vm_page_wire_count;

/*
 *	Several page replacement parameters are also
 *	shared with this module, so that page allocation
 *	(done here in vm_page_alloc) can trigger the
 *	pageout daemon.
 */
int	vm_page_free_target = 0;
int	vm_page_free_min = 0;
int	vm_page_inactive_target = 0;
int	vm_page_free_reserved = 0;

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
	register vm_page_bucket_t *bucket;
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
	m->free = FALSE;

	m->busy = TRUE;
	m->wanted = FALSE;
	m->tabled = FALSE;
	m->fictitious = FALSE;
	m->private = FALSE;
	m->absent = FALSE;
	m->error = FALSE;
	m->dirty = FALSE;
	m->was_absent = FALSE;
	m->overwriting = FALSE;
	m->precious = FALSE;
	
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

	vm_page_buckets = (vm_page_bucket_t *) vaddr;
	PMAP_MAP(vm_page_bucket_count * sizeof(vm_page_bucket_t));

	for (bucket = vm_page_buckets, i = vm_page_bucket_count; i--; bucket++) {
		queue_init(&bucket->pages);
		bucket->count = 0;
		simple_lock_init(&bucket->lock);
	}

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
	
	/* save enough virtual addresses so that vm_page_create
	   can be called after autoconf to give back unused 
	   physical memory */

	if (vm_page_array_size == 0)
		vm_page_array_size = atop(end - 0) *
					sizeof(struct vm_page);

	vm_page_array = (vm_page_t) (vm_page_array_next = vaddr);
	vm_page_array_end = (vaddr += round_page(vm_page_array_size));

	vm_page_create(start, (end - start), pmap_valid_page);

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
	register vm_page_bucket_t *bucket;
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
	simple_lock(&bucket->lock);
	queue_enter(&bucket->pages, mem, vm_page_t, hashq);
	bucket->count++;
	simple_unlock(&bucket->lock);
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
	register vm_page_bucket_t	*bucket;
	int			spl;

	VM_PAGE_CHECK(mem);

	if (!mem->tabled)
		return;

	/*
	 *	Remove from the object_object/offset hash table
	 */

	bucket = &vm_page_buckets[vm_page_hash(mem->object, mem->offset)];
	spl = splimp();
	simple_lock(&bucket->lock);
	queue_remove(&bucket->pages, mem, vm_page_t, hashq);
	bucket->count--;
	simple_unlock(&bucket->lock);
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
	register vm_page_bucket_t *bucket;
	int			spl;

	/*
	 *	Search the hash table for this object/offset pair
	 */

	bucket = &vm_page_buckets[vm_page_hash(object, offset)];

	spl = splimp();
	simple_lock(&bucket->lock);
	mem = (vm_page_t) queue_first(&bucket->pages);
	while (!queue_end(&bucket->pages, (queue_entry_t) mem)) {
		VM_PAGE_CHECK(mem);
		if ((mem->object == object) && (mem->offset == offset)) {
			simple_unlock(&bucket->lock);
			splx(spl);
			return(mem);
		}
		mem = (vm_page_t) queue_next(&mem->hashq);
	}

	simple_unlock(&bucket->lock);
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
#if	defined(vax) && !defined(lint)
/* for some obscure reason, MP Vaxen don't work with FALSE */
boolean_t	vm_page_alloc_fifo = NCPUS > 1;
#else	defined(vax) && !defined(lint)
boolean_t	vm_page_alloc_fifo = FALSE;
#endif	defined(vax) && !defined(lint)

boolean_t	vm_page_alloc_deactivate_behind = FALSE;

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
		if (current_thread()->vm_privilege)
			printf("vm_page_alloc: cannot allocate to vm-privileged thread\n");
		simple_unlock(&vm_page_queue_free_lock);
		splx(spl);
		return(VM_PAGE_NULL);
	}

	if ((vm_page_free_count < vm_page_free_reserved) && !current_thread()->vm_privilege) {
		simple_unlock(&vm_page_queue_free_lock);
		splx(spl);
		return(VM_PAGE_NULL);
	}
	if (vm_page_free_count < (vm_page_free_reserved - 15))
		Debugger("vm_page_alloc");


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
		thread_wakeup((int) &vm_page_free_wanted);

	/*
	 *	Detect sequential access and inactivate previous page
	 */

	if (vm_page_alloc_deactivate_behind &&
	    (offset == object->last_alloc + PAGE_SIZE)) {
		vm_page_t	last_mem;

		last_mem = vm_page_lookup(object, object->last_alloc);
		if (last_mem != VM_PAGE_NULL) {
			vm_page_lock_queues();
			vm_page_deactivate(last_mem);
			vm_page_unlock_queues();
		}
	}
	object->last_alloc = offset;

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

	if (mem->wire_count != 0) {
		if (!mem->private)
			vm_page_wire_count--;
		mem->wire_count = 0;
	}

	if (mem->laundry)
		mem->laundry = FALSE;

	PAGE_WAKEUP_DONE(mem);

	if (mem->absent)
		vm_object_absent_release(mem->object);

	if (!mem->private) {
		if (mem->fictitious) {
			zfree(vm_page_fictitious_zone, (vm_offset_t)mem);
		} else {
			int	spl;

			spl = splimp();
			simple_lock(&vm_page_queue_free_lock);
			queue_enter(&vm_page_queue_free, mem, vm_page_t, pageq);
			mem->free = TRUE;
			vm_page_free_count++;

			if (vm_page_free_wanted) {
				thread_wakeup((int) &vm_page_free_count);
				vm_page_free_wanted = FALSE;
			}

			simple_unlock(&vm_page_queue_free_lock);
			splx(spl);
		}
	}
}

void		vm_page_free_synchronized(m)
	vm_page_t	m;
{
	vm_page_lock_queues();
	vm_page_free(m);
	vm_page_unlock_queues();
}

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

	if (m->active) {
		pmap_clear_reference(VM_PAGE_TO_PHYS(m));
		queue_remove(&vm_page_queue_active, m, vm_page_t, pageq);
		m->active = FALSE;
		vm_page_active_count--;
	}
	if (m->wire_count == 0 && !m->inactive) {
		queue_enter(&vm_page_queue_inactive, m, vm_page_t, pageq);
		m->inactive = TRUE;
		vm_page_inactive_count++;
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
 */
void vm_page_zero_fill(m)
	vm_page_t	m;
{
	VM_PAGE_CHECK(m);

	XPR(XPR_VM_PAGE, ("vm_page_zero_fill: page %x, object %x, offset %x\n",
		m, m->object, m->offset));

	pmap_zero_page(m->phys_addr);
	vm_stat.zero_fill_count++;
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
		(p->private ? " private" : ""));
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
