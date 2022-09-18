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
 * $Log:	vm_map.c,v $
 * Revision 2.26  91/02/04  10:24:19  berman
 * 	Added vm_object_lock()/vm_object_unlock() around
 * 	vm_object_page_remove() in vm_map_delete().  [from dlb]
 * 
 * Revision 2.25  91/01/22  16:31:57  mja
 * 	Fix an obscure bug that can panic the system if a fork happens
 * 	to an address space with a wired region.  The problem was that
 * 	vm_map_fork() allowed copy-on-write on wired regions.
 * 	[91/01/16            dlb]
 * 
 * Revision 2.24  90/09/10  21:09:24  mrt
 * 	Zero the stat info when creating a map./
 * 	[90/09/10  17:31:45  af]
 * 
 * Revision 2.23  90/09/07  19:03:00  mrt
 * 	Initialized result=KERN_SUCCESS at begining of
 * 	vm_map_copy_overwrite.
 * 	[90/09/05            mrt]
 * 
 * Revision 2.22  90/09/05  15:21:44  bohman
 * 	Fixed vm_map_copy_overwite to return result rather than
 * 	KERN_SUCCESS.
 * 	[90/09/05            mrt]
 * 
 * Revision 2.21  90/07/03  16:56:52  mrt
 * 	Add vm_map_copy_entry_delete.
 * 	Purge MACH_OLD_VM_COPY.  Minor optimization to vm_map_copyin.
 * 
 * 	Change vm_map_copyout, vm_map_copy_insert, and
 * 	vm_map_copy_overwrite to use a parameter to decide whether
 * 	to destroy copy.  Corresponding change to vm_map_fork.
 * 
 * 	Have vm_map_copyin mark each entry in the copy as single_use
 * 	or not.  single_use == TRUE is only reliable for temporary
 * 	objects; it must be rechecked for permanent ones.  If it's
 * 	FALSE, there is some other use of the object.
 * 	[90/06/26            dlb]
 * 
 * 	Pick up pure kernel optimization to vm_map_copyin that tries to
 * 	avoid making a copy if the source of the copy is being destroyed.
 * 	From dbg.  Also make sure a copy is never wired.
 * 	[90/06/20            dlb]
 * 	Fix vm_map_fork() to take out a sharing map reference for each
 * 	shared region in the parent map, not just the first.  Found by
 * 	Dave Bohman (bohman+@andrew.cmu.edu).
 * 	[90/06/07            dlb]
 * 
 * Revision 2.20  90/03/30  00:21:24  rpd
 * 	Fixed vm_region so that it doesn't treat sub-map entries (only
 * 	found in the kernel map) as regular entries.  Instead, it just
 * 	ignores them and doesn't try to send back an object_name reference.
 * 	[90/03/23            gk]
 * 
 * 	Bug fixes for vm_map_copy technology.  Handle null copy objects
 * 	and zero-sized regions correctly.  In vm_map_copy_overwrite,
 * 	check for null object pointers and corrected hole-checking so
 * 	that overwrites of multiple entries work.
 * 	[90/03/28            rpd]
 * 
 * Revision 2.19  90/03/27  18:57:30  dlb
 * 	Declare vm_submap_object.  It's a placeholder to make sure memory
 * 	allocated for a submap is not coalesced.  Check for it and
 * 	related conditions in vm_map_submap.
 * 	[90/03/27            dlb]
 * 	Bump map zone size to 128k. 
 * 	[90/02/18            dlb]
 * 	Change vm_map_fork to create at most one sharing map for each
 * 	map that is forked.  This fixes problem whereby a fork of
 * 	a task with lots of shared memory could exhaust the map zone.
 * 	[90/02/08            dlb]
 * 
 * Revision 2.18  90/03/08  23:13:41  af
 * 	Added vm_map_machine_attributes().
 * 	Correct check for holes in vm_map_copy_overwrite() [mwyoung]
 * 
 * Revision 2.17  89/12/23  13:57:48  rpd
 * 	Fixed syntax errors in vm_map_print.
 * 
 * Revision 2.16  89/12/22  16:29:39  rpd
 * 	Fixed use of vm_object_copy_slowly in vm_map_copyin.
 * 	Restored similar fix to vm_map_copy_entry.
 * 	[89/12/01  13:56:30  rpd]
 * 
 * Revision 2.15  89/12/22  15:55:54  rpd
 * 	Make sure object lock is held before calling
 * 	vm_object_copy_slowly.  Release old destination object in wired
 * 	case of vm_map_copy_entry.  Fixes from rpd.
 * 	[89/12/15            dlb]
 * 	Modify vm_map_pageable to allow both user and kernel to wire
 * 	memory.  New routine is vm_map_pageable_common, but should be
 * 	called via macros in vm/vm_map.h.
 * 	[89/12/11            dlb]
 * 
 * Revision 2.14  89/10/11  14:59:28  dlb
 * 	Modify vm_map_pageable to create new objects BEFORE clipping
 * 	map entries to avoid object proliferation.
 * 	[88/11/30            dlb]
 * 		
 * 	Check for holes when wiring memory in vm_map_pageable.
 * 	Pass requested access type to vm_map_pageable and check it.
 * 	[88/11/21            dlb]
 * 
 * Revision 2.13  89/10/10  11:21:06  mwyoung
 * 	Add back old form of vm_map_copy technology as an option in case
 * 	something goes dreadfully wrong.
 * 	[89/10/05  17:02:40  mwyoung]
 * 
 * 	Handle overwriting permanent objects in vm_map_copy_overwrite().
 * 
 * 	Put optimized copy path in vm_map_fork().
 * 	[89/10/01  23:24:32  mwyoung]
 * 
 * 	Integrate the "wait for space" option for kernel maps
 * 	into this module.
 * 
 * 	Add vm_map_copyin(), vm_map_copyout(), vm_map_copy_discard() to
 * 	perform map copies.
 * 
 * 	Convert vm_map_entry_create(), vm_map_clip_{start,end} so that
 * 	they may be used with either a vm_map_t or a vm_map_copy_t.
 * 
 * Revision 2.12  89/10/03  19:29:54  rpd
 * 	Use vme_next, vme_prev, vme_start, vme_end, vm_map_to_entry.
 * 	[89/08/31  21:12:23  rpd]
 * 
 * 	In vm_map_copy_entry: use uprintf instead of printf when warning
 * 	about copying over permanent data.  When copying from a wired entry,
 * 	use vm_object_copy_slowly directly instead of vm_fault_copy_entry.
 * 	[89/08/31  19:30:56  rpd]
 * 
 * 	Picked up NeXT change to vm_region:  now if you give it an address
 * 	in the middle of an entry, it will use the start of the entry.
 * 	[89/08/20  23:19:39  rpd]
 * 
 * 	A bug fix from NeXT:  vm_map_protect wasn't unlocking in the is_sub_map
 * 	case.  Also, fixed vm_map_copy_entry to not take the address
 * 	of needs_copy, because it is a bit-field now.
 * 	[89/08/19  23:43:55  rpd]
 * 
 * Revision 2.11  89/04/18  21:25:58  mwyoung
 * 	Recent history [mwyoung]:
 * 		Add vm_map_simplify() to keep kernel maps more compact.
 * 	Condensed history:
 * 		Add vm_map_enter(). [mwyoung]
 * 		Return a "version" from vm_map_lookup() to simplify
 * 		 locking. [mwyoung]
 * 		Get pageability changes right.  [dbg, dlb]
 * 		Original implementation.  [avie, mwyoung, dbg]
 * 
 */
/*
 *	File:	vm/vm_map.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Virtual memory mapping module.
 */

#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <kern/zalloc.h>
#include <mach/kern_return.h>
#include <vm/vm_page.h>
#include <vm/vm_object.h>
#include <mach/port.h>
#include <mach/vm_attributes.h>
#include <vm/vm_fault.h>

/*
 *	Virtual memory maps provide for the mapping, protection,
 *	and sharing of virtual memory objects.  In addition,
 *	this module provides for an efficient virtual copy of
 *	memory from one map to another.
 *
 *	Synchronization is required prior to most operations.
 *
 *	Maps consist of an ordered doubly-linked list of simple
 *	entries; a single hint is used to speed up lookups.
 *
 *	In order to properly represent the sharing of virtual
 *	memory regions among maps, the map structure is bi-level.
 *	Top-level ("address") maps refer to regions of sharable
 *	virtual memory.  These regions are implemented as
 *	("sharing") maps, which then refer to the actual virtual
 *	memory objects.  When two address maps "share" memory,
 *	their top-level maps both have references to the same
 *	sharing map.  When memory is virtual-copied from one
 *	address map to another, the references in the sharing
 *	maps are actually copied -- no copying occurs at the
 *	virtual memory object level.
 *
 *	Since portions of maps are specified by start/end addreses,
 *	which may not align with existing map entries, all
 *	routines merely "clip" entries to these start/end values.
 *	[That is, an entry is split into two, bordering at a
 *	start or end value.]  Note that these clippings may not
 *	always be necessary (as the two resulting entries are then
 *	not changed); however, the clipping is done for convenience.
 *	No attempt is currently made to "glue back together" two
 *	abutting entries.
 *
 *	As mentioned above, virtual copy operations are performed
 *	by copying VM object references from one sharing map to
 *	another, and then marking both regions as copy-on-write.
 *	It is important to note that only one writeable reference
 *	to a VM object region exists in any map -- this means that
 *	shadow object creation can be delayed until a write operation
 *	occurs.
 */

zone_t		vm_map_zone;		/* zone for vm_map structures */
zone_t		vm_map_entry_zone;	/* zone for vm_map_entry structures */
zone_t		vm_map_kentry_zone;	/* zone for kernel entry structures */
zone_t		vm_map_copy_zone;	/* zone for vm_map_copy structures */

boolean_t	vm_map_lookup_entry();	/* forward declaration */

/*
 *	Placeholder object for submap operations.  This object is dropped
 *	into the range by a call to vm_map_find, and removed when
 *	vm_map_submap creates the submap.
 */

vm_object_t	vm_submap_object;

/*
 *	vm_map_init:
 *
 *	Initialize the vm_map module.  Must be called before
 *	any other vm_map routines.
 *
 *	Map and entry structures are allocated from zones -- we must
 *	initialize those zones.
 *
 *	There are three zones of interest:
 *
 *	vm_map_zone:		used to allocate maps.
 *	vm_map_entry_zone:	used to allocate map entries.
 *	vm_map_kentry_zone:	used to allocate map entries for the kernel.
 *
 *	The kernel allocates map entries from a special zone that is initially
 *	"crammed" with memory.  It would be difficult (perhaps impossible) for
 *	the kernel to allocate more memory to a entry zone when it became
 *	empty since the very act of allocating memory implies the creatio
 *	of a new entry.  Further, since the kernel map is created from the
 *	map zone, the map zone is initially "crammed" with enough memory
 *	to fullfill that need.
 */

void vm_map_init()
{
	extern vm_offset_t	map_data, kentry_data;
	extern vm_size_t	map_data_size, kentry_data_size;

	vm_map_zone = zinit((vm_size_t) sizeof(struct vm_map), 128*1024,
					PAGE_SIZE, FALSE, "maps");
	vm_map_entry_zone = zinit((vm_size_t) sizeof(struct vm_map_entry),
					1024*1024, PAGE_SIZE*5,
					FALSE, "non-kernel map entries");
	vm_map_kentry_zone = zinit((vm_size_t) sizeof(struct vm_map_entry),
					kentry_data_size, kentry_data_size,
					FALSE, "kernel map entries");

	vm_map_copy_zone = zinit((vm_size_t) sizeof(struct vm_map_copy),
					16*1024, PAGE_SIZE, FALSE,
					"map copies");

	/*
	 *	Cram the map and kentry zones with initial data.
	 */
	zcram(vm_map_zone, map_data, map_data_size);
	zcram(vm_map_kentry_zone, kentry_data, kentry_data_size);

	/*
	 *	Submap object is initialized by vm_object_init.
	 */
}

/*
 *	vm_map_create:
 *
 *	Creates and returns a new empty VM map with
 *	the given physical map structure, and having
 *	the given lower and upper address bounds.
 */
vm_map_t vm_map_create(pmap, min, max, pageable)
	pmap_t		pmap;
	vm_offset_t	min, max;
	boolean_t	pageable;
{
	register vm_map_t	result;

	ZALLOC(vm_map_zone, result, vm_map_t);
	if (result == VM_MAP_NULL)
		panic("vm_map_create: out of maps");

	result->vme_next = result->vme_prev = vm_map_to_entry(result);
	result->nentries = 0;
	result->size = 0;
	result->ref_count = 1;
	result->pmap = pmap;
	result->is_main_map = TRUE;
	result->min_offset = min;
	result->max_offset = max;
	result->entries_pageable = pageable;
	result->wait_for_space = FALSE;
	result->first_free = vm_map_to_entry(result);
	result->hint = vm_map_to_entry(result);
	vm_map_lock_init(result);
	simple_lock_init(&result->ref_lock);
	simple_lock_init(&result->hint_lock);
	bzero(&result->vm_stat, sizeof(result->vm_stat));

	return(result);
}

/*
 *	vm_map_entry_create:	[ internal use only ]
 *
 *	Allocates a VM map entry for insertion in the
 *	given map (or map copy).  No fields are filled.
 */
#define	vm_map_entry_create(map)			\
	_vm_map_entry_create(				\
		(map)->entries_pageable ?		\
		vm_map_entry_zone :			\
		vm_map_kentry_zone)
vm_map_entry_t _vm_map_entry_create(zone)
	zone_t		zone;
{
	vm_map_entry_t	entry;

	ZALLOC(zone, entry, vm_map_entry_t);
	if (entry == VM_MAP_ENTRY_NULL)
		panic("vm_map_entry_create: out of map entries");

	return(entry);
}

/*
 *	vm_map_entry_dispose:	[ internal use only ]
 *
 *	Inverse of vm_map_entry_create.
 */
#define	vm_map_entry_dispose(map, entry) \
	_vm_map_entry_dispose( \
		(map)->entries_pageable ? \
			vm_map_entry_zone : \
			vm_map_kentry_zone, \
		entry)
void _vm_map_entry_dispose(zone, entry)
	zone_t		zone;
	vm_map_entry_t	entry;
{
	ZFREE(zone, (vm_offset_t) entry);
}

/*
 *	vm_map_entry_{un,}link:
 *
 *	Insert/remove entries from maps (or map copies).
 */
#define vm_map_entry_link(map, after_where, entry)		\
		MACRO_BEGIN					\
		(map)->nentries++;				\
		(entry)->vme_prev = (after_where);		\
		(entry)->vme_next = (after_where)->vme_next;	\
		(entry)->vme_prev->vme_next =			\
		 (entry)->vme_next->vme_prev = (entry);		\
		MACRO_END
#define vm_map_entry_unlink(map, entry) \
		MACRO_BEGIN \
		(map)->nentries--; \
		(entry)->vme_next->vme_prev = (entry)->vme_prev; \
		(entry)->vme_prev->vme_next = (entry)->vme_next; \
		MACRO_END

/*
 *	vm_map_reference:
 *
 *	Creates another valid reference to the given map.
 *
 */
void vm_map_reference(map)
	register vm_map_t	map;
{
	if (map == VM_MAP_NULL)
		return;

	simple_lock(&map->ref_lock);
	map->ref_count++;
	simple_unlock(&map->ref_lock);
}

/*
 *	vm_map_deallocate:
 *
 *	Removes a reference from the specified map,
 *	destroying it if no references remain.
 *	The map should not be locked.
 */
void vm_map_deallocate(map)
	register vm_map_t	map;
{
	register int		c;

	if (map == VM_MAP_NULL)
		return;

	simple_lock(&map->ref_lock);
	c = --map->ref_count;
	simple_unlock(&map->ref_lock);

	if (c > 0) {
		return;
	}

	/*
	 *	Lock the map, to wait out all other references
	 *	to it.
	 */

	vm_map_lock(map);

	(void) vm_map_delete(map, map->min_offset, map->max_offset);

	pmap_destroy(map->pmap);

	ZFREE(vm_map_zone, (vm_offset_t) map);
}

/*
 *	vm_map_insert:	[ internal use only ]
 *
 *	Inserts the given whole VM object into the target
 *	map at the specified address range.  The object's
 *	size should match that of the address range.
 *
 *	Requires that the map be locked, and leaves it so.
 */
kern_return_t vm_map_insert(map, object, offset, start, end)
	vm_map_t	map;
	vm_object_t	object;
	vm_offset_t	offset;
	vm_offset_t	start;
	vm_offset_t	end;
{
	register vm_map_entry_t		new_entry;
	register vm_map_entry_t		prev_entry;
	vm_map_entry_t			temp_entry;

	/*
	 *	Check that the start and end points are not bogus.
	 */

	if ((start < map->min_offset) || (end > map->max_offset) ||
			(start >= end))
		return(KERN_INVALID_ADDRESS);

	/*
	 *	Find the entry prior to the proposed
	 *	starting address; if it's part of an
	 *	existing entry, this range is bogus.
	 */

	if (vm_map_lookup_entry(map, start, &temp_entry))
		return(KERN_NO_SPACE);

	prev_entry = temp_entry;

	/*
	 *	Assert that the next entry doesn't overlap the
	 *	end point.
	 */

	if ((prev_entry->vme_next != vm_map_to_entry(map)) &&
	    (prev_entry->vme_next->vme_start < end))
		return(KERN_NO_SPACE);

	/*
	 *	See if we can avoid creating a new entry by
	 *	extending one of our neighbors.
	 */

	if (object == VM_OBJECT_NULL) {
		if ((prev_entry != vm_map_to_entry(map)) &&
		    (prev_entry->vme_end == start) &&
		    (map->is_main_map) &&
		    (prev_entry->is_a_map == FALSE) &&
		    (prev_entry->is_sub_map == FALSE) &&
		    (prev_entry->inheritance == VM_INHERIT_DEFAULT) &&
		    (prev_entry->protection == VM_PROT_DEFAULT) &&
		    (prev_entry->max_protection == VM_PROT_DEFAULT) &&
		    (prev_entry->wired_count == 0)) {

			if (vm_object_coalesce(prev_entry->object.vm_object,
					VM_OBJECT_NULL,
					prev_entry->offset,
					(vm_offset_t) 0,
					(vm_size_t)(prev_entry->vme_end
						     - prev_entry->vme_start),
					(vm_size_t)(end - prev_entry->vme_end))) {
				/*
				 *	Coalesced the two objects - can extend
				 *	the previous map entry to include the
				 *	new range.
				 */
				map->size += (end - prev_entry->vme_end);
				prev_entry->vme_end = end;
				return(KERN_SUCCESS);
			}
		}
	}

	/*
	 *	Create a new entry
	 */

	new_entry = vm_map_entry_create(map);
	new_entry->vme_start = start;
	new_entry->vme_end = end;

	new_entry->is_a_map = FALSE;
	new_entry->is_sub_map = FALSE;
	new_entry->object.vm_object = object;
	new_entry->offset = offset;

	new_entry->copy_on_write = FALSE;
	new_entry->needs_copy = FALSE;

	if (map->is_main_map) {
		new_entry->inheritance = VM_INHERIT_DEFAULT;
		new_entry->protection = VM_PROT_DEFAULT;
		new_entry->max_protection = VM_PROT_DEFAULT;
		new_entry->wired_count = 0;
		new_entry->user_wired_count = 0;
	}

	/*
	 *	Insert the new entry into the list
	 */

	vm_map_entry_link(map, prev_entry, new_entry);
	map->size += new_entry->vme_end - new_entry->vme_start;

	/*
	 *	Update the free space hint
	 */

	if ((map->first_free == prev_entry) && (prev_entry->vme_end >= new_entry->vme_start))
		map->first_free = new_entry;

	return(KERN_SUCCESS);
}

/*
 *	SAVE_HINT:
 *
 *	Saves the specified entry as the hint for
 *	future lookups.  Performs necessary interlocks.
 */
#define SAVE_HINT(map,value) \
		simple_lock(&(map)->hint_lock); \
		(map)->hint = (value); \
		simple_unlock(&(map)->hint_lock);

/*
 *	vm_map_lookup_entry:	[ internal use only ]
 *
 *	Finds the map entry containing (or
 *	immediately preceding) the specified address
 *	in the given map; the entry is returned
 *	in the "entry" parameter.  The boolean
 *	result indicates whether the address is
 *	actually contained in the map.
 */
boolean_t vm_map_lookup_entry(map, address, entry)
	register vm_map_t	map;
	register vm_offset_t	address;
	vm_map_entry_t		*entry;		/* OUT */
{
	register vm_map_entry_t		cur;
	register vm_map_entry_t		last;

	/*
	 *	Start looking either from the head of the
	 *	list, or from the hint.
	 */

	simple_lock(&map->hint_lock);
	cur = map->hint;
	simple_unlock(&map->hint_lock);

	if (cur == vm_map_to_entry(map))
		cur = cur->vme_next;

	if (address >= cur->vme_start) {
	    	/*
		 *	Go from hint to end of list.
		 *
		 *	But first, make a quick check to see if
		 *	we are already looking at the entry we
		 *	want (which is usually the case).
		 *	Note also that we don't need to save the hint
		 *	here... it is the same hint (unless we are
		 *	at the header, in which case the hint didn't
		 *	buy us anything anyway).
		 */
		last = vm_map_to_entry(map);
		if ((cur != last) && (cur->vme_end > address)) {
			*entry = cur;
			return(TRUE);
		}
	}
	else {
	    	/*
		 *	Go from start to hint, *inclusively*
		 */
		last = cur->vme_next;
		cur = vm_map_first_entry(map);
	}

	/*
	 *	Search linearly
	 */

	while (cur != last) {
		if (cur->vme_end > address) {
			if (address >= cur->vme_start) {
			    	/*
				 *	Save this lookup for future
				 *	hints, and return
				 */

				*entry = cur;
				SAVE_HINT(map, cur);
				return(TRUE);
			}
			break;
		}
		cur = cur->vme_next;
	}
	*entry = cur->vme_prev;
	SAVE_HINT(map, *entry);
	return(FALSE);
}

/*
 *	vm_map_find finds an unallocated region in the target address
 *	map with the given length.  The search is defined to be
 *	first-fit from the specified address; the region found is
 *	returned in the same parameter.
 *
 */
kern_return_t vm_map_find(map, object, offset, addr, length, find_space)
	vm_map_t	map;
	vm_object_t	object;
	vm_offset_t	offset;
	vm_offset_t	*addr;		/* IN/OUT */
	vm_size_t	length;
	boolean_t	find_space;
{
	register vm_map_entry_t	entry;
	register vm_offset_t	start;
	register vm_offset_t	end;
	kern_return_t		result;

 StartAgain: ;

	start = *addr;

	vm_map_lock(map);

	if (find_space) {
		/*
		 *	Calculate the first possible address.
		 */

		if (start < map->min_offset)
			start = map->min_offset;
		if (start > map->max_offset) {
			vm_map_unlock(map);
			return (KERN_NO_SPACE);
		}

		/*
		 *	Look for the first possible address;
		 *	if there's already something at this
		 *	address, we have to start after it.
		 */

		if (start == map->min_offset) {
			if ((entry = map->first_free) != vm_map_to_entry(map))
				start = entry->vme_end;
		} else {
			vm_map_entry_t	tmp_entry;
			if (vm_map_lookup_entry(map, start, &tmp_entry))
				start = tmp_entry->vme_end;
			entry = tmp_entry;
		}

		/*
		 *	In any case, the "entry" always precedes
		 *	the proposed new region throughout the
		 *	loop:
		 */

		while (TRUE) {
			register vm_map_entry_t	next;

		    	/*
			 *	Find the end of the proposed new region.
			 *	Be sure we didn't go beyond the end, or
			 *	wrap around the address.
			 */

			end = start + length;

			if ((end > map->max_offset) || (end < start)) {
				if (map->wait_for_space) {
					if (length <= (map->max_offset - map->min_offset)) {
						assert_wait((int) map, TRUE);
						vm_map_unlock(map);
						thread_block();
						goto StartAgain;
					}
				}
				
				vm_map_unlock(map);
				return (KERN_NO_SPACE);
			}

			/*
			 *	If there are no more entries, we must win.
			 */

			next = entry->vme_next;
			if (next == vm_map_to_entry(map))
				break;

			/*
			 *	If there is another entry, it must be
			 *	after the end of the potential new region.
			 */

			if (next->vme_start >= end)
				break;

			/*
			 *	Didn't fit -- move to the next entry.
			 */

			entry = next;
			start = entry->vme_end;
		}
		*addr = start;
		
		SAVE_HINT(map, entry);
	}

	result = vm_map_insert(map, object, offset, start, start + length);
	
	vm_map_unlock(map);
	return(result);
}

/*
 *	Routine:	vm_map_enter
 *
 *	Description:
 *		Allocate a range in the specified virtual address map.
 *		The resulting range will refer to memory defined by
 *		the given memory object and offset into that object.
 *
 *		Arguments are as defined in the vm_map call.
 *	Assumptions:
 *		Unlike vm_map_insert, this routine assumes that it
 *		is being called on a main map (not a sharing map).
 */
kern_return_t vm_map_enter(
		map,
		address, size, mask, anywhere,
		object, offset, needs_copy,
		cur_protection, max_protection,	inheritance)
	register
	vm_map_t	map;
	vm_offset_t	*address;	/* IN/OUT */
	vm_size_t	size;
	vm_offset_t	mask;
	boolean_t	anywhere;
	vm_object_t	object;
	vm_offset_t	offset;
	boolean_t	needs_copy;
	vm_prot_t	cur_protection;
	vm_prot_t	max_protection;
	vm_inherit_t	inheritance;
{
	register vm_map_entry_t	entry;
	register vm_offset_t	start;
	register vm_offset_t	end;
	kern_return_t		result = KERN_SUCCESS;

#define RETURN(value)	{ result = value; goto BailOut; }

 StartAgain: ;

	start = *address;

	if (anywhere) {
		vm_map_lock(map);

		/*
		 *	Calculate the first possible address.
		 */

		if (start < map->min_offset)
			start = map->min_offset;
		if (start > map->max_offset)
			RETURN(KERN_NO_SPACE);

		/*
		 *	Look for the first possible address;
		 *	if there's already something at this
		 *	address, we have to start after it.
		 */

		if (start == map->min_offset) {
			if ((entry = map->first_free) != vm_map_to_entry(map))
				start = entry->vme_end;
		} else {
			vm_map_entry_t	tmp_entry;
			if (vm_map_lookup_entry(map, start, &tmp_entry))
				start = tmp_entry->vme_end;
			entry = tmp_entry;
		}

		/*
		 *	In any case, the "entry" always precedes
		 *	the proposed new region throughout the
		 *	loop:
		 */

		while (TRUE) {
			register vm_map_entry_t	next;

		    	/*
			 *	Find the end of the proposed new region.
			 *	Be sure we didn't go beyond the end, or
			 *	wrap around the address.
			 */

			start = ((start + mask) & ~mask);
			end = start + size;

			if ((end > map->max_offset) || (end < start)) {
				if (map->wait_for_space) {
					if (size <= (map->max_offset - map->min_offset)) {
						assert_wait((int) map, TRUE);
						vm_map_unlock(map);
						thread_block();
						goto StartAgain;
					}
				}
				
				RETURN(KERN_NO_SPACE);
			}

			/*
			 *	If there are no more entries, we must win.
			 */

			next = entry->vme_next;
			if (next == vm_map_to_entry(map))
				break;

			/*
			 *	If there is another entry, it must be
			 *	after the end of the potential new region.
			 */

			if (next->vme_start >= end)
				break;

			/*
			 *	Didn't fit -- move to the next entry.
			 */

			entry = next;
			start = entry->vme_end;
		}
		*address = start;
	} else {
		vm_map_entry_t		temp_entry;

		/*
		 *	Verify that:
		 *		the address doesn't itself violate
		 *		the mask requirement.
		 */

		if ((start & mask) != 0)
			return(KERN_NO_SPACE);

		vm_map_lock(map);

		/*
		 *	...	the address is within bounds
		 */

		end = start + size;

		if ((start < map->min_offset) ||
		    (end > map->max_offset) ||
		    (start >= end)) {
			RETURN(KERN_INVALID_ADDRESS);
		}

		/*
		 *	...	the starting address isn't allocated
		 */

		if (vm_map_lookup_entry(map, start, &temp_entry))
			RETURN(KERN_NO_SPACE);

		entry = temp_entry;

		/*
		 *	...	the next region doesn't overlap the
		 *		end point.
		 */

		if ((entry->vme_next != vm_map_to_entry(map)) &&
		    (entry->vme_next->vme_start < end))
			RETURN(KERN_NO_SPACE);
	}

	/*
	 *	At this point,
	 *		"start" and "end" should define the endpoints of the
	 *			available new range, and
	 *		"entry" should refer to the region before the new
	 *			range, and
	 *
	 *		the map should be locked.
	 */

	/*
	 *	See whether we can avoid creating a new entry (and object) by
	 *	extending one of our neighbors.  [So far, we only attempt to
	 *	extend from below.]
	 */

	if ((object == VM_OBJECT_NULL) &&
	    (entry != vm_map_to_entry(map)) &&
	    (entry->vme_end == start) &&
	    (!entry->is_a_map) &&
	    (!entry->is_sub_map) &&
	    (entry->inheritance == inheritance) &&
	    (entry->protection == cur_protection) &&
	    (entry->max_protection == max_protection) &&
	    (entry->wired_count == 0)) {
		if (vm_object_coalesce(entry->object.vm_object,
				VM_OBJECT_NULL,
				entry->offset,
				(vm_offset_t) 0,
				(vm_size_t)(entry->vme_end - entry->vme_start),
				(vm_size_t)(end - entry->vme_end))) {

			/*
			 *	Coalesced the two objects - can extend
			 *	the previous map entry to include the
			 *	new range.
			 */
			map->size += (end - entry->vme_end);
			entry->vme_end = end;
			RETURN(KERN_SUCCESS);
		}
	}

	/*
	 *	Create a new entry
	 */

	/**/ {
	register vm_map_entry_t	new_entry;

	new_entry = vm_map_entry_create(map);

	new_entry->vme_start = start;
	new_entry->vme_end = end;

	new_entry->is_a_map = FALSE;
	new_entry->is_sub_map = FALSE;
	new_entry->object.vm_object = object;
	new_entry->offset = offset;

	new_entry->needs_copy =
	new_entry->copy_on_write = needs_copy;

	new_entry->inheritance = inheritance;
	new_entry->protection = cur_protection;
	new_entry->max_protection = max_protection;
	new_entry->wired_count = 0;
	new_entry->user_wired_count = 0;

	/*
	 *	Insert the new entry into the list
	 */

	vm_map_entry_link(map, entry, new_entry);
	map->size += size;

	/*
	 *	Update the free space hint and the lookup hint
	 */

	if ((map->first_free == entry) && (entry->vme_end >= new_entry->vme_start))
		map->first_free = new_entry;

	SAVE_HINT(map, new_entry);
	/**/ }

 BailOut: ;

	vm_map_unlock(map);
	return(result);

#undef	RETURN
}

/*
 *	vm_map_clip_start:	[ internal use only ]
 *
 *	Asserts that the given entry begins at or after
 *	the specified address; if necessary,
 *	it splits the entry into two.
 */
#define vm_map_clip_start(map, entry, startaddr) \
	MACRO_BEGIN					\
	if ((startaddr) > (entry)->vme_start) {		\
		vm_map_entry_t clip_entry =		\
			vm_map_entry_create(map);	\
		_vm_map_clip_start(			\
			(entry),			\
			startaddr,			\
			clip_entry			\
			);				\
		vm_map_entry_link(map,			\
			(entry)->vme_prev,		\
			clip_entry);			\
	}						\
	MACRO_END

/*
 *	This routine is called only when it is known that
 *	the entry must be split.
 */
void _vm_map_clip_start(entry, start, new_entry)
	register vm_map_entry_t	entry;
	register vm_offset_t	start;
	register vm_map_entry_t	new_entry;
{
	/*
	 *	Split off the front portion --
	 *	note that we must insert the new
	 *	entry BEFORE this one, so that
	 *	this entry has the specified starting
	 *	address.
	 */

	*new_entry = *entry;

	new_entry->vme_end = start;
	entry->offset += (start - entry->vme_start);
	entry->vme_start = start;

	if (entry->is_a_map || entry->is_sub_map)
	 	vm_map_reference(new_entry->object.share_map);
	else
		vm_object_reference(new_entry->object.vm_object);
}

/*
 *	vm_map_clip_end:	[ internal use only ]
 *
 *	Asserts that the given entry ends at or before
 *	the specified address; if necessary,
 *	it splits the entry into two.
 */
void _vm_map_clip_end();
#define vm_map_clip_end(map, entry, endaddr)		\
	MACRO_BEGIN					\
	if ((endaddr) < (entry)->vme_end) {		\
		vm_map_entry_t clip_entry =		\
			vm_map_entry_create(map);	\
		_vm_map_clip_end(			\
			(entry),			\
			(endaddr),			\
			clip_entry			\
			);				\
		vm_map_entry_link(map,			\
			(entry),			\
			clip_entry);			\
	}						\
	MACRO_END

/*
 *	This routine is called only when it is known that
 *	the entry must be split.
 */
void _vm_map_clip_end(entry, end, new_entry)
	register vm_map_entry_t	entry;
	register vm_offset_t	end;
	register vm_map_entry_t	new_entry;
{
	/*
	 *	Fill in an entry to be placed
	 *	AFTER the specified entry
	 */

	*new_entry = *entry;

	new_entry->vme_start = entry->vme_end = end;
	new_entry->offset += (end - entry->vme_start);

	if (entry->is_a_map || entry->is_sub_map)
	 	vm_map_reference(new_entry->object.share_map);
	else
		vm_object_reference(new_entry->object.vm_object);
}

/*
 *	VM_MAP_RANGE_CHECK:	[ internal use only ]
 *
 *	Asserts that the starting and ending region
 *	addresses fall within the valid range of the map.
 */
#define VM_MAP_RANGE_CHECK(map, start, end)		\
		{					\
		if (start < vm_map_min(map))		\
			start = vm_map_min(map);	\
		if (end > vm_map_max(map))		\
			end = vm_map_max(map);		\
		if (start > end)			\
			start = end;			\
		}

/*
 *	vm_map_submap:		[ kernel use only ]
 *
 *	Mark the given range as handled by a subordinate map.
 *
 *	This range must have been created with vm_map_find using
 *	the vm_submap_object, and no other operations may have been
 *	performed on this range prior to calling vm_map_submap.
 *
 *	Only a limited number of operations can be performed
 *	within this rage after calling vm_map_submap:
 *		vm_fault
 *	[Don't try vm_map_copyin!]
 *
 *	To remove a submapping, one must first remove the
 *	range from the superior map, and then destroy the
 *	submap (if desired).  [Better yet, don't try it.]
 */
kern_return_t vm_map_submap(map, start, end, submap)
	register vm_map_t	map;
	register vm_offset_t	start;
	register vm_offset_t	end;
	vm_map_t		submap;
{
	vm_map_entry_t		entry;
	register kern_return_t	result = KERN_INVALID_ARGUMENT;
	register vm_object_t	object;

	vm_map_lock(map);

	VM_MAP_RANGE_CHECK(map, start, end);

	if (vm_map_lookup_entry(map, start, &entry)) {
		vm_map_clip_start(map, entry, start);
	}
	 else
		entry = entry->vme_next;

	vm_map_clip_end(map, entry, end);

	if ((entry->vme_start == start) && (entry->vme_end == end) &&
	    (!entry->is_a_map) &&
	    ((object = entry->object.vm_object) == vm_submap_object) &&
	    (!entry->copy_on_write) &&
	    (object->resident_page_count == 0) &&
	    (object->copy == VM_OBJECT_NULL) &&
	    (object->shadow == VM_OBJECT_NULL) &&
	    (!object->pager_created)) {
		entry->is_a_map = FALSE;
		entry->object.vm_object = VM_OBJECT_NULL;
		vm_object_deallocate(object);
		entry->is_sub_map = TRUE;
		vm_map_reference(entry->object.sub_map = submap);
		result = KERN_SUCCESS;
	}
	vm_map_unlock(map);

	return(result);
}

/*
 *	vm_map_protect:
 *
 *	Sets the protection of the specified address
 *	region in the target map.  If "set_max" is
 *	specified, the maximum protection is to be set;
 *	otherwise, only the current protection is affected.
 */
kern_return_t vm_map_protect(map, start, end, new_prot, set_max)
	register vm_map_t	map;
	register vm_offset_t	start;
	register vm_offset_t	end;
	register vm_prot_t	new_prot;
	register boolean_t	set_max;
{
	register vm_map_entry_t		current;
	vm_map_entry_t			entry;

	vm_map_lock(map);

	VM_MAP_RANGE_CHECK(map, start, end);

	if (vm_map_lookup_entry(map, start, &entry)) {
		vm_map_clip_start(map, entry, start);
	}
	 else
		entry = entry->vme_next;

	/*
	 *	Make a first pass to check for protection
	 *	violations.
	 */

	current = entry;
	while ((current != vm_map_to_entry(map)) && (current->vme_start < end)) {
		if (current->is_sub_map) {
			vm_map_unlock(map);
			return(KERN_INVALID_ARGUMENT);
		}
		if ((new_prot & current->max_protection) != new_prot) {
			vm_map_unlock(map);
			return(KERN_PROTECTION_FAILURE);
		}

		current = current->vme_next;
	}

	/*
	 *	Go back and fix up protections.
	 *	[Note that clipping is not necessary the second time.]
	 */

	current = entry;

	while ((current != vm_map_to_entry(map)) && (current->vme_start < end)) {
		vm_prot_t	old_prot;

		vm_map_clip_end(map, current, end);

		old_prot = current->protection;
		if (set_max)
			current->protection =
				(current->max_protection = new_prot) &
					old_prot;
		else
			current->protection = new_prot;

		/*
		 *	Update physical map if necessary.
		 *	Worry about copy-on-write here -- CHECK THIS XXX
		 */

		if (current->protection != old_prot) {

#define MASK(entry)	((entry)->copy_on_write ? ~VM_PROT_WRITE : \
							VM_PROT_ALL)
#define	max(a,b)	((a) > (b) ? (a) : (b))
#define min(a,b)	((a) < (b) ? (a) : (b))

			if (current->is_a_map) {
				vm_map_entry_t	share_entry;
				vm_offset_t	share_end;

				vm_map_lock(current->object.share_map);
				(void) vm_map_lookup_entry(
						current->object.share_map,
						current->offset,
						&share_entry);
				share_end = current->offset +
					(current->vme_end - current->vme_start);
				while ((share_entry !=
					vm_map_to_entry(current->object.share_map)) &&
					(share_entry->vme_start < share_end)) {

					pmap_protect(map->pmap,
						(max(share_entry->vme_start,
							current->offset) -
							current->offset +
							current->vme_start),
						min(share_entry->vme_end,
							share_end) -
						current->offset +
						current->vme_start,
						current->protection &
						    MASK(share_entry));

					share_entry = share_entry->vme_next;
				}
				vm_map_unlock(current->object.share_map);
			}
			else
			 	pmap_protect(map->pmap, current->vme_start,
					current->vme_end,
					current->protection & MASK(entry));
#undef	max
#undef	min
#undef	MASK
		}
		current = current->vme_next;
	}

	vm_map_unlock(map);
	return(KERN_SUCCESS);
}

/*
 *	vm_map_inherit:
 *
 *	Sets the inheritance of the specified address
 *	range in the target map.  Inheritance
 *	affects how the map will be shared with
 *	child maps at the time of vm_map_fork.
 */
kern_return_t vm_map_inherit(map, start, end, new_inheritance)
	register vm_map_t	map;
	register vm_offset_t	start;
	register vm_offset_t	end;
	register vm_inherit_t	new_inheritance;
{
	register vm_map_entry_t	entry;
	vm_map_entry_t	temp_entry;

	switch (new_inheritance) {
	case VM_INHERIT_NONE:
	case VM_INHERIT_COPY:
	case VM_INHERIT_SHARE:
		break;
	default:
		return(KERN_INVALID_ARGUMENT);
	}

	vm_map_lock(map);

	VM_MAP_RANGE_CHECK(map, start, end);

	if (vm_map_lookup_entry(map, start, &temp_entry)) {
		entry = temp_entry;
		vm_map_clip_start(map, entry, start);
	}
	else
		entry = temp_entry->vme_next;

	while ((entry != vm_map_to_entry(map)) && (entry->vme_start < end)) {
		vm_map_clip_end(map, entry, end);

		entry->inheritance = new_inheritance;

		entry = entry->vme_next;
	}

	vm_map_unlock(map);
	return(KERN_SUCCESS);
}

/*
 *	vm_map_pageable_common:
 *
 *	Sets the pageability of the specified address
 *	range in the target map.  Regions specified
 *	as not pageable require locked-down physical
 *	memory and physical page maps.  access_type indicates
 *	types of accesses that must not generate page faults.
 *	This is checked against protection of memory being locked-down.
 *	access_type of VM_PROT_NONE makes memory pageable.
 *
 *	The map must not be locked, but a reference
 *	must remain to the map throughout the call.
 *
 *	Callers should use macros in vm/vm_map.h (i.e. vm_map_pageable,
 *	or vm_map_pageable_user); don't call vm_map_pageable directly.
 */
kern_return_t vm_map_pageable_common(map, start, end, access_type, user_wire)
	register vm_map_t	map;
	register vm_offset_t	start;
	register vm_offset_t	end;
	register vm_prot_t	access_type;
	boolean_t		user_wire;
{
	register vm_map_entry_t	entry;
	vm_map_entry_t		start_entry;

	vm_map_lock(map);

	VM_MAP_RANGE_CHECK(map, start, end);

	if (vm_map_lookup_entry(map, start, &start_entry)) {
		entry = start_entry;
		/*
		 *	vm_map_clip_start will be done later.
		 */
	}
	else {
		/*
		 *	Start address is not in map; this is fatal.
		 */
		vm_map_unlock(map);
		return(KERN_FAILURE);
	}

	/*
	 *	Actions are rather different for wiring and unwiring,
	 *	so we have two separate cases.
	 */

	if (access_type == VM_PROT_NONE) {

		vm_map_clip_start(map, entry, start);

		/*
		 *	Unwiring.  First ensure that the range to be
		 *	unwired is really wired down.
		 */
		while ((entry != vm_map_to_entry(map)) &&
		       (entry->vme_start < end)) {

		    if ((entry->wired_count == 0) ||
		    	((entry->vme_end < end) && 
			 ((entry->vme_next == vm_map_to_entry(map)) ||
			  (entry->vme_next->vme_start > entry->vme_end))) ||
			(user_wire && (entry->user_wired_count == 0))) {
			    vm_map_unlock(map);
			    return(KERN_INVALID_ARGUMENT);
		    }
		    entry = entry->vme_next;
		}

		/*
		 *	Now decrement the wiring count for each region.
		 *	If a region becomes completely unwired,
		 *	unwire its physical pages and mappings.
		 */
		entry = start_entry;
		while ((entry != vm_map_to_entry(map)) &&
		       (entry->vme_start < end)) {
		    vm_map_clip_end(map, entry, end);

		    if (user_wire) {
			if (--(entry->user_wired_count) == 0)
			    entry->wired_count--;
		    }
		    else {
			entry->wired_count--;
		    }
		    
		    if (entry->wired_count == 0)
			vm_fault_unwire(map, entry);

		    entry = entry->vme_next;
		}
	}

	else {
		/*
		 *	Wiring.  We must do this in two passes:
		 *
		 *	1.  Holding the write lock, we create any shadow
		 *	    or zero-fill objects that need to be created.
		 *	    Then we clip each map entry to the region to be
		 *	    wired and increment its wiring count.  We
		 *	    create objects before clipping the map entries
		 *	    to avoid object proliferation.
		 *
		 *	2.  We downgrade to a read lock, and call
		 *	    vm_fault_wire to fault in the pages for any
		 *	    newly wired area (wired_count is 1).
		 *
		 *	Downgrading to a read lock for vm_fault_wire avoids
		 *	a possible deadlock with another thread that may have
		 *	faulted on one of the pages to be wired (it would mark
		 *	the page busy, blocking us, then in turn block on the
		 *	map lock that we hold).  Because of problems in the
		 *	recursive lock package, we cannot upgrade to a write
		 *	lock in vm_map_lookup.  Thus, any actions that require
		 *	the write lock must be done beforehand.  Because we
		 *	keep the read lock on the map, the copy-on-write
		 *	status of the entries we modify here cannot change.
		 */

		/*
		 *	Pass 1.
		 */
		while ((entry != vm_map_to_entry(map)) &&
		       (entry->vme_start < end)) {

		    if (entry->wired_count == 0) {

			/*
			 *	Perform actions of vm_map_lookup that need
			 *	the write lock on the map: create a shadow
			 *	object for a copy-on-write region, or an
			 *	object for a zero-fill region.
			 *
			 *	We don't have to do this for entries that
			 *	point to sharing maps, because we won't hold
			 *	the lock on the sharing map.
			 */
			if (!entry->is_a_map) {
			    if (entry->needs_copy &&
				((entry->protection & VM_PROT_WRITE) != 0)) {

				vm_object_shadow(&entry->object.vm_object,
						&entry->offset,
						(vm_size_t)(entry->vme_end
							- entry->vme_start));
				entry->needs_copy = FALSE;
			    }
			    else if (entry->object.vm_object ==
				VM_OBJECT_NULL) {
				    entry->object.vm_object =
				        vm_object_allocate(
					    (vm_size_t)(entry->vme_end 
				    			- entry->vme_start));
				    entry->offset = (vm_offset_t)0;
			    }
			}
		    }
		    vm_map_clip_start(map, entry, start);
		    vm_map_clip_end(map, entry, end);

		    if (user_wire) {
			if ((entry->user_wired_count)++ == 0)
			    entry->wired_count++;
		    }
		    else {
			entry->wired_count++;
		    }

		    /*
		     *	Check for holes and protection mismatch.
		     *  Holes: Next entry should be contiguous unless
		     *		this is the end of the region.
		     *	Protection: Access requested must be allowed.
		     */
		    if (((entry->vme_end < end) && 
			 ((entry->vme_next == vm_map_to_entry(map)) ||
			  (entry->vme_next->vme_start > entry->vme_end))) ||
			((entry->protection & access_type) != access_type)) {
			    /*
			     *	Found a hole or protection problem.
			     *	Object creation actions
			     *	do not need to be undone, but the
			     *	wired counts need to be restored.
			     */
			    while ((entry != vm_map_to_entry(map)) &&
				(entry->vme_end > start)) {
				    if (user_wire) {
					if (--(entry->user_wired_count) == 0)
					    entry->wired_count--;
				    }
				    else {
				       entry->wired_count--;
				    }

				    entry = entry->vme_prev;
			    }

			    vm_map_unlock(map);
			    return(KERN_FAILURE);
		    }
		    entry = entry->vme_next;
		}

		/*
		 *	Pass 2.
		 */

		vm_map_lock_set_recursive(map);
		vm_map_lock_write_to_read(map);

		entry = start_entry;
		while (entry != vm_map_to_entry(map) &&
			entry->vme_start < end) {
		    /*
		     *	Wiring cases:
		     *	    Kernel: wired == 1 && user_wired == 0
		     *	    User:   wired == 1 && user_wired == 1
		     *
		     *  Don't need to wire if either is > 1.  wired = 0 &&
		     *	user_wired == 1 can't happen.
		     */

		    /*
		     *	XXX This assumes that the faults always succeed.
		     */
		    if ((entry->wired_count == 1) &&
			(entry->user_wired_count <= 1)) {
			    vm_fault_wire(map, entry);
		    }
		    entry = entry->vme_next;
		}

		vm_map_lock_clear_recursive(map);
	}

	vm_map_unlock(map);

	return(KERN_SUCCESS);
}

/*
 *	vm_map_entry_unwire:	[ internal use only ]
 *
 *	Make the region specified by this entry pageable.
 *
 *	The map in question should be locked.
 *	[This is the reason for this routine's existence.]
 */
void vm_map_entry_unwire(map, entry)
	vm_map_t		map;
	register vm_map_entry_t	entry;
{
	vm_fault_unwire(map, entry);
	entry->wired_count = 0;
	entry->user_wired_count = 0;
}

/*
 *	vm_map_entry_delete:	[ internal use only ]
 *
 *	Deallocate the given entry from the target map.
 */		
void vm_map_entry_delete(map, entry)
	register vm_map_t	map;
	register vm_map_entry_t	entry;
{
	if (entry->wired_count != 0)
		vm_map_entry_unwire(map, entry);
		
	vm_map_entry_unlink(map, entry);
	map->size -= entry->vme_end - entry->vme_start;

	if (entry->is_a_map || entry->is_sub_map)
		vm_map_deallocate(entry->object.share_map);
	else
	 	vm_object_deallocate(entry->object.vm_object);

	vm_map_entry_dispose(map, entry);
}

/*
 *	vm_map_delete:	[ internal use only ]
 *
 *	Deallocates the given address range from the target
 *	map.
 *
 *	When called with a sharing map, removes pages from
 *	that region from all physical maps.
 */
kern_return_t vm_map_delete(map, start, end)
	register vm_map_t	map;
	vm_offset_t		start;
	register vm_offset_t	end;
{
	register vm_map_entry_t	entry;
	vm_map_entry_t		first_entry;

	/*
	 *	Find the start of the region, and clip it
	 */

	if (!vm_map_lookup_entry(map, start, &first_entry))
		entry = first_entry->vme_next;
	else {
		entry = first_entry;
		vm_map_clip_start(map, entry, start);

		/*
		 *	Fix the lookup hint now, rather than each
		 *	time though the loop.
		 */

		SAVE_HINT(map, entry->vme_prev);
	}

	/*
	 *	Save the free space hint
	 */

	if (map->first_free->vme_start >= start)
		map->first_free = entry->vme_prev;

	/*
	 *	Step through all entries in this region
	 */

	while ((entry != vm_map_to_entry(map)) && (entry->vme_start < end)) {
		vm_map_entry_t		next;
		register vm_offset_t	s, e;
		register vm_object_t	object;
		extern vm_object_t	kernel_object;

		vm_map_clip_end(map, entry, end);

		next = entry->vme_next;
		s = entry->vme_start;
		e = entry->vme_end;

		/*
		 *	Unwire before removing addresses from the pmap;
		 *	otherwise, unwiring will put the entries back in
		 *	the pmap.
		 */

		object = entry->object.vm_object;
		if (entry->wired_count != 0)
			vm_map_entry_unwire(map, entry);

		/*
		 *	If this is a sharing map, we must remove
		 *	*all* references to this data, since we can't
		 *	find all of the physical maps which are sharing
		 *	it.
		 */

		if (object == kernel_object) {
		    vm_object_lock(object);
		    vm_object_page_remove(object, entry->offset,
					  entry->offset + (e - s));
		    vm_object_unlock(object);
		} else if (!map->is_main_map)
			vm_object_pmap_remove(object,
					 entry->offset,
					 entry->offset + (e - s));
		 else
			pmap_remove(map->pmap, s, e);

		/*
		 *	Delete the entry (which may delete the object)
		 *	only after removing all pmap entries pointing
		 *	to its pages.  (Otherwise, its page frames may
		 *	be reallocated, and any modify bits will be
		 *	set in the wrong object!)
		 */

		vm_map_entry_delete(map, entry);
		entry = next;
	}

	if (map->wait_for_space)
		thread_wakeup((int) map);

	return(KERN_SUCCESS);
}

/*
 *	vm_map_remove:
 *
 *	Remove the given address range from the target map.
 *	This is the exported form of vm_map_delete.
 */
kern_return_t vm_map_remove(map, start, end)
	register vm_map_t	map;
	register vm_offset_t	start;
	register vm_offset_t	end;
{
	register kern_return_t	result;

	vm_map_lock(map);
	VM_MAP_RANGE_CHECK(map, start, end);
	result = vm_map_delete(map, start, end);
	vm_map_unlock(map);

	return(result);
}

/*
 *	vm_map_check_protection:
 *
 *	Assert that the target map allows the specified
 *	privilege on the entire address region given.
 *	The entire region must be allocated.
 */
boolean_t vm_map_check_protection(map, start, end, protection)
	register vm_map_t	map;
	register vm_offset_t	start;
	register vm_offset_t	end;
	register vm_prot_t	protection;
{
	register vm_map_entry_t	entry;
	vm_map_entry_t		tmp_entry;

	if (!vm_map_lookup_entry(map, start, &tmp_entry))
		return(FALSE);
	entry = tmp_entry;

	while (start < end) {
		if (entry == vm_map_to_entry(map))
			return(FALSE);

		/* No holes allowed! */
		if (start < entry->vme_start)
			return(FALSE);

		/* Check protection associated with entry. */
		if ((entry->protection & protection) != protection)
			return(FALSE);

		/* Proceed to next entry */
		start = entry->vme_end;
		entry = entry->vme_next;
	}
	return(TRUE);
}

/*
 *	vm_map_copy_entry_delete:	[ internal use only ]
 *
 *	Deallocate the given entry from the target map copy.
 */		

#define	vm_map_copy_entry_delete_macro(copy, entry)		\
	MACRO_BEGIN						\
	vm_map_entry_unlink(copy, entry);			\
	vm_object_deallocate(entry->object.vm_object);		\
	vm_map_entry_dispose(copy, entry);			\
	MACRO_END

void vm_map_copy_entry_delete(copy, entry)
	register vm_map_copy_t	copy;
	register vm_map_entry_t	entry;
{
	vm_map_copy_entry_delete_macro(copy, entry);
}

/*
 *	Routine:	vm_map_copy_discard
 *
 *	Description:
 *		Dispose of a map copy object (returned by
 *		vm_map_copyin).
 */
void		vm_map_copy_discard(copy)
	vm_map_copy_t	copy;
{
	if (copy == VM_MAP_COPY_NULL)
		return;

	while (vm_map_copy_first_entry(copy) != vm_map_copy_to_entry(copy)) {
		vm_map_entry_t	entry = vm_map_copy_first_entry(copy);

		vm_map_copy_entry_delete_macro(copy, entry);
	}
	zfree(vm_map_copy_zone, (vm_offset_t) copy);
}

/*
 *	Routine:	vm_map_copy_overwrite
 *
 *	Description:
 *		Copy the memory described by the map copy
 *		object (copy; returned by vm_map_copyin) onto
 *		the specified destination region (dst_map, dst_addr).
 *		The destination must be writeable.
 *
 *		Unlike vm_map_copyout, this routine actually
 *		writes over previously-mapped memory.  If the
 *		previous mapping was to a permanent (user-supplied)
 *		memory object, it is preserved.
 *
 *		The attributes (protection and inheritance) of the
 *		destination region are preserved.
 *
 *		The map copy object is destroyed if discard is
 *		specified as TRUE.  If it is not destroyed,
 *		it may no longer contain any valid data.
 *
 *	Implementation notes:
 *		To overwrite temporary virtual memory, it is
 *		sufficient to remove the previous mapping and insert
 *		the new copy.  This replacement is done either on
 *		the whole region (if no permanent virtual memory
 *		objects are embedded in the destination region) or
 *		in individual map entries.
 *
 *		To overwrite permanent virtual memory, it is
 *		necessary to copy each page, as the external
 *		memory management interface currently does not
 *		provide any optimizations.
 *
 *		Once a page of permanent memory has been overwritten,
 *		it is impossible to interrupt this function; otherwise,
 *		the call would be neither atomic nor location-independent.
 *		The kernel-state portion of a user thread must be
 *		interruptible.
 *
 *		It may be expensive to forward all requests that might
 *		overwrite permanent memory (vm_write, vm_copy) to
 *		uninterruptible kernel threads.  This routine may be
 *		called by interruptible threads; however, success is
 *		not guaranteed -- if the request cannot be performed
 *		atomically and interruptibly, an error indication is
 *		returned.
 */
kern_return_t
vm_map_copy_overwrite(dst_map, dst_addr, copy, interruptible, discard)
	vm_map_t	dst_map;
	vm_offset_t	dst_addr;
	vm_map_copy_t	copy;
	boolean_t	interruptible;
	boolean_t	discard;
{
	vm_size_t	size;
	vm_offset_t	start;
	vm_map_entry_t	tmp_entry;
	vm_map_entry_t	entry;
	kern_return_t	result;

	boolean_t	contains_maps = FALSE;
	boolean_t	contains_permanent_objects = FALSE;

	interruptible = FALSE;	/* XXX */
	result = KERN_SUCCESS;
	/*
	 *	Check for null copy object.
	 */

	if (copy == VM_MAP_COPY_NULL)
		return(KERN_SUCCESS);

	/*
	 *	Currently this routine only handles page-aligned
	 *	regions.  Eventually, it should handle misalignments
	 *	by actually copying pages.
	 */

	assert(page_aligned(copy->min_offset));
	assert(page_aligned(copy->max_offset));
	assert(page_aligned(dst_addr));

	size = copy->max_offset - copy->min_offset;

	if (size == 0) {
		result = KERN_SUCCESS;
		goto OverwriteDone;
	}

	/*
	 *	Verify that the destination is all writeable
	 *	initially.
	 */

	vm_map_lock(dst_map);
	if (!vm_map_lookup_entry(dst_map, dst_addr, &tmp_entry)) {
		vm_map_unlock(dst_map);
		result = KERN_INVALID_ADDRESS;
		goto OverwriteDone;
	}
	vm_map_clip_start(dst_map, tmp_entry, dst_addr);
	for (entry = tmp_entry;;) {
		vm_size_t	sub_size = (entry->vme_end - entry->vme_start);
		vm_map_entry_t	next = entry->vme_next;
		
		if ( ! (entry->protection & VM_PROT_WRITE)) {
			vm_map_unlock(dst_map);
			result = KERN_PROTECTION_FAILURE;
			goto OverwriteDone;
		}

		if (size <= sub_size)
			break;

		if ((next == vm_map_to_entry(dst_map)) ||
		    (next->vme_start != entry->vme_end)) {
			vm_map_unlock(dst_map);
			result = KERN_INVALID_ADDRESS;
			goto OverwriteDone;
		}

		/*
		 *	Check for submaps and for permanent objects
		 *	in the destination.
		 */

		if (entry->is_a_map) {
			contains_maps = TRUE;

			if (interruptible) {
				vm_map_t	sub_map = entry->object.sub_map;
				vm_map_entry_t	sub_entry;
			
				vm_map_lock_read(sub_map);
				(void) vm_map_lookup_entry(
					entry->object.sub_map,
					entry->offset,
					&sub_entry);

				if ((sub_entry->object.vm_object
							!= VM_OBJECT_NULL) &&
				    !sub_entry->object.vm_object->temporary)
					contains_permanent_objects = TRUE;
				vm_map_unlock(sub_map);
			}
		} else if ((entry->object.vm_object != VM_OBJECT_NULL) &&
			   !entry->object.vm_object->temporary)
			contains_permanent_objects = TRUE;

		size -= sub_size;
		entry = next;
	}

	/*
	 *	If there are permanent objects in the destination, then
	 *	the copy cannot be interrupted.
	 */

	if (interruptible && contains_permanent_objects) {
		result = KERN_FAILURE;	/* XXX */
		goto OverwriteDone;
	}

	/*
	 *	If the destination consists entirely of top-level
	 *	map entries, then remove them quickly and insert the
	 *	new entries.
	 */

	if (!contains_maps) {
		/* XXXO Complete the optimization */
	}

	/*
	 *
	 *	Make a second pass, overwriting the data
	 *	At the beginning of each loop iteration,
	 *	the next entry to be overwritten is "tmp_entry"
	 *	(initially, the value returned from the lookup above),
	 *	and the starting address expected in that entry
	 *	is "start".
	 */

	start = dst_addr;

	while (vm_map_copy_first_entry(copy) != vm_map_copy_to_entry(copy)) {
		vm_map_entry_t	copy_entry = vm_map_copy_first_entry(copy);
		vm_size_t	copy_size = (copy_entry->vme_end - copy_entry->vme_start);
		vm_map_t	sub_map = VM_MAP_NULL;
		vm_object_t	object;
		
		entry = tmp_entry;
		size = (entry->vme_end - entry->vme_start);


		/*
		 *	Make sure that no holes popped up in the
		 *	address map, and that the protection is
		 *	still valid, in case the map was unlocked
		 *	earlier.
		 */

		if (entry->vme_start != start) {
			vm_map_unlock(dst_map);
			result = KERN_INVALID_ADDRESS;
			goto OverwriteDone;
		}
		assert(entry != vm_map_to_entry(dst_map));

		/*
		 *	Check protection again
		 */

		if ( ! (entry->protection & VM_PROT_WRITE)) {
			vm_map_unlock(dst_map);
			result = KERN_PROTECTION_FAILURE;
			goto OverwriteDone;
		}

		/*
		 *	Adjust to source size first
		 */

		if (copy_size < size) {
			vm_map_clip_end(dst_map, entry, entry->vme_start + copy_size);
			size = copy_size;
		}

		/*
		 *	Follow submap
		 */

		if (entry->is_a_map) {
			vm_map_entry_t	sub_entry;
			vm_size_t	sub_size;
			
			sub_map = entry->object.sub_map;
			vm_map_lock(sub_map);
			(void) vm_map_lookup_entry(
					sub_map,
					entry->offset,
					&sub_entry);
			vm_map_clip_start(sub_map, sub_entry, entry->offset);

			entry = sub_entry;

			if ((sub_size = entry->vme_end - entry->vme_start) < size) {
				vm_map_clip_end(dst_map, tmp_entry, tmp_entry->vme_start + sub_size);
				size = sub_size;
			} else if (sub_size > size) {
				vm_map_clip_end(sub_map, sub_entry, sub_entry->vme_start + size);
			}
		}

		/*
		 *	Adjust to destination size
		 */

		if (size < copy_size) {
			vm_map_clip_end(copy, copy_entry, copy_entry->vme_start + size);
			copy_size = size;
		}

		assert((entry->vme_end - entry->vme_start) == size);
		assert((tmp_entry->vme_end - tmp_entry->vme_start) == size);
		assert((copy_entry->vme_end - copy_entry->vme_start) == size);

		/*
		 *	If the destination contains temporary memory, we can
		 *	perform the copy by throwing it away and installing
		 *	the source data.
		 */

		object = entry->object.vm_object;
		if ((object == VM_OBJECT_NULL) || object->temporary) {
			vm_object_t	old_object = entry->object.vm_object;
			vm_offset_t	old_offset = entry->offset;

			entry->object = copy_entry->object;
			entry->offset = copy_entry->offset;
			entry->needs_copy = copy_entry->needs_copy;
			entry->copy_on_write = copy_entry->copy_on_write;
			entry->wired_count = 0;
			entry->user_wired_count = 0;

			vm_map_entry_unlink(copy, copy_entry);
			vm_map_entry_dispose(copy, copy_entry);

			vm_object_pmap_protect(
				old_object,
				old_offset,
				size,
				(tmp_entry->is_a_map ?
					PMAP_NULL : dst_map->pmap),
				tmp_entry->vme_start,
				VM_PROT_NONE);
				
			if (tmp_entry->is_a_map)
				vm_map_unlock(tmp_entry->object.sub_map);

			vm_object_deallocate(old_object);

			/*
			 *	Set up for the next iteration.  The map
			 *	has not been unlocked, so the next
			 *	address should be at the end of this
			 *	entry, and the next map entry should be
			 *	the one following it.
			 */

			start = tmp_entry->vme_end;
			tmp_entry = tmp_entry->vme_next;
		} else {
			vm_map_version_t	version;
			vm_object_t		dst_object = entry->object.vm_object;
			vm_offset_t		dst_offset = entry->offset;

			/*
			 *	Take an object reference, and record
			 *	the map version information so that the
			 *	map can be safely unlocked.
			 */

			vm_object_reference(dst_object);

			version.main_timestamp = dst_map->timestamp;
			if ((version.share_map = sub_map) != VM_MAP_NULL) {
				version.share_timestamp = sub_map->timestamp;
				vm_map_unlock(sub_map);
			} else
				version.share_map = dst_map;

			vm_map_unlock(dst_map);

			/*
			 *	Copy as much as possible in one pass
			 */

			copy_size = size;
			result = vm_fault_copy(
					copy_entry->object.vm_object,
					copy_entry->offset,
					&copy_size,
					dst_object,
					dst_offset,
					dst_map,
					&version,
					FALSE /* XXX interruptible */ );

			/*
			 *	Release the object reference
			 */

			vm_object_deallocate(dst_object);

			/*
			 *	If a hard error occurred, return it now
			 */

			if (result != KERN_SUCCESS) 
				goto OverwriteDone;

			if (copy_size != 0) {
				/*
				 *	If the entire region was not copied, then split
				 *	off the part that was successful.
				 */

				if (copy_size != size)
					vm_map_clip_start(copy, copy_entry, copy_entry->vme_start + copy_size);

				/*
				 *	Dispose of the succesfully copied region
				 */

				vm_map_entry_unlink(copy, copy_entry);
				vm_map_entry_dispose(copy, copy_entry);
			}

			/*
			 *	Pick up in the destination map where we left off.
			 *
			 *	Use the version information to avoid a lookup
			 *	in the normal case.
			 */

			vm_map_lock(dst_map);
			if ((version.main_timestamp + 1) == dst_map->timestamp) {
				if (copy_size != size)
					vm_map_clip_start(dst_map, entry, entry->vme_start + copy_size);
				tmp_entry = entry->vme_next;
			} else {
				vm_offset_t	new_start = entry->vme_start + copy_size;
				if (!vm_map_lookup_entry(dst_map, new_start, &tmp_entry)) {
					vm_map_unlock(dst_map);
					result = KERN_INVALID_ADDRESS;
					goto OverwriteDone;
				}
				vm_map_clip_start(dst_map, tmp_entry, new_start);
				start = new_start;
			}
		}

	}
	vm_map_unlock(dst_map);

	/*
	 *	Throw away the vm_map_copy object if specified.
	 */
OverwriteDone:

	if (discard)
		vm_map_copy_discard(copy);

	return(result);
}

/*
 *	Macro:		vm_map_copy_insert
 *	
 *	Description:
 *		Link a copy chain ("copy") into a map at the
 *		specified location (after "where").
 *	Side effects:
 *		The copy chain is gutted in all cases, and destroyed
 *		if discard is TRUE.
 *	Warning:
 *		The arguments are evaluated multiple times.
 *
 */
#define	vm_map_copy_insert(map, where, copy, discard)			\
	MACRO_BEGIN							\
	(((where)->vme_next)->vme_prev = vm_map_copy_last_entry(copy))	\
		->vme_next = ((where)->vme_next);			\
	((where)->vme_next = vm_map_copy_first_entry(copy))		\
		->vme_prev = (where);					\
	(map)->nentries += (copy)->nentries;				\
	if (discard) {							\
		zfree(vm_map_copy_zone, (vm_offset_t) copy);		\
	}								\
	else {								\
		vm_map_copy_first_entry(copy) =				\
		 vm_map_copy_last_entry(copy) = 			\
			vm_map_copy_to_entry(copy);			\
		(copy)->nentries = 0;					\
		(copy)->min_offset = 0;					\
		(copy)->max_offset = 0;					\
	}								\
	MACRO_END

/*
 *	Routine:	vm_map_copyout
 *
 *	Description:
 *		Copy out a copy chain ("copy") into newly-allocated
 *		space in the destination map.  Copy will be gutted
 *		in all cases, but discarded only if discard is TRUE.
 */
kern_return_t vm_map_copyout(dst_map, dst_addr, copy, discard)
	vm_map_t	dst_map;
	vm_offset_t	*dst_addr;	/* OUT */
	vm_map_copy_t	copy;
	boolean_t	discard;
{
	vm_size_t	size;
	vm_size_t	adjustment;
	vm_offset_t	start;
	vm_map_entry_t	last;
	vm_map_entry_t	entry;

	/*
	 *	Check for null copy object.
	 */

	if (copy == VM_MAP_COPY_NULL) {
		*dst_addr = 0;
		return(KERN_SUCCESS);
	}

	/*
	 *	Find space for the data
	 */

	size =	round_page(copy->max_offset) -
		trunc_page(copy->min_offset);

 StartAgain: ;

	vm_map_lock(dst_map);
	start = ((last = dst_map->first_free) == vm_map_to_entry(dst_map)) ?
		vm_map_min(dst_map) : last->vme_end;

	while (TRUE) {
		vm_map_entry_t	next = last->vme_next;
		vm_offset_t	end = start + size;

		if ((end > dst_map->max_offset) || (end < start)) {
			if (dst_map->wait_for_space) {
				if (size <= (dst_map->max_offset - dst_map->min_offset)) {
					assert_wait((int) dst_map, TRUE);
					vm_map_unlock(dst_map);
					thread_block();
					goto StartAgain;
				}
			}
			vm_map_unlock(dst_map);
			if (discard)
				vm_map_copy_discard(copy);
			return(KERN_NO_SPACE);
		}

		if ((next == vm_map_to_entry(dst_map)) || (end < next->vme_start))
			break;

		last = next;
		start = last->vme_end;
	}

	/*
	 *	Since we're going to just drop the map
	 *	entries from the copy into the destination
	 *	map, they must come from the same pool.
	 *
	 *	At the moment, it should not be possible
	 *	for a mismatch to occur.  If it ever becomes
	 *	possible, it would be necessary to make
	 *	a pass to reallocate and copy map entries.
	 */

	if (copy->entries_pageable != dst_map->entries_pageable)
		panic("vm_map_copyout: pageability mismatch");

	/*
	 *	Adjust the addresses in the copy chain, and
	 *	reset the region attributes.
	 */

	adjustment = start - trunc_page(copy->min_offset);
	for (entry = vm_map_copy_first_entry(copy);
	     entry != vm_map_copy_to_entry(copy);
	     entry = entry->vme_next) {
		entry->vme_start += adjustment;
		entry->vme_end += adjustment;

		entry->inheritance = VM_INHERIT_COPY;
		entry->protection = VM_PROT_ALL;
		entry->max_protection = VM_PROT_ALL;
	}

	/*
	 *	Correct the page alignment for the result
	 */

	*dst_addr = start + (copy->min_offset - trunc_page(copy->min_offset));

	/*
	 *	Update the hints and the map size
	 */

	if (dst_map->first_free == last)
		dst_map->first_free = vm_map_copy_last_entry(copy);
	SAVE_HINT(dst_map, vm_map_copy_last_entry(copy));

	dst_map->size += size;

	/*
	 *	Link in the copy and discard if requested.
	 */

	vm_map_copy_insert(dst_map, last, copy, discard);

	vm_map_unlock(dst_map);

	return(KERN_SUCCESS);
}

/*
 *	Routine:	vm_map_copyin
 *
 *	Description:
 *		Copy the specified region (src_addr, len) from the
 *		source address space (src_map), possibly removing
 *		the region from the source address space (src_destroy).
 *
 *	Returns:
 *		A vm_map_copy_t object (copy_result), suitable for
 *		insertion into another address space (using vm_map_copyout),
 *		copying over another address space region (using
 *		vm_map_copy_overwrite).  If the copy is unused, it
 *		should be destroyed (using vm_map_copy_discard).
 *
 *	In/out conditions:
 *		The source map should not be locked on entry.
 */
kern_return_t vm_map_copyin(src_map, src_addr, len, src_destroy, copy_result)
	vm_map_t	src_map;
	vm_offset_t	src_addr;
	vm_size_t	len;
	boolean_t	src_destroy;
	vm_map_copy_t	*copy_result;	/* OUT */
{
	vm_map_entry_t	tmp_entry;	/* Result of last map lookup --
					 * in multi-level lookup, this
					 * entry contains the actual
					 * vm_object/offset.
					 */

	vm_offset_t	src_start;	/* Start of current entry --
					 * where copy is taking place now
					 */
	vm_offset_t	src_done;	/* End of current entry */
	vm_offset_t	src_end;	/* End of entire region to be
					 * copied */

	vm_map_copy_t	copy;		/* Resulting copy */

	boolean_t	single_use;	/* Copy entry is only use of data */

	/*
	 *	Check for copies of zero bytes.
	 */

	if (len == 0) {
		if (src_addr != 0)
			return(KERN_INVALID_ADDRESS);

		*copy_result = VM_MAP_COPY_NULL;
		return(KERN_SUCCESS);
	}

	/*
	 *	Compute start and end of region
	 */

	src_start = trunc_page(src_addr);
	src_end = round_page(src_addr + len);

	/*
	 *	Check that the end address doesn't overflow
	 */

	if (src_end <= src_start)
		if ((src_end < src_start) || (src_start != 0))
			return(KERN_INVALID_ADDRESS);

	/*
	 *	Allocate a header element for the list.
	 *
	 *	Use the start and end in the header to 
	 *	remember the endpoints prior to rounding.
	 */

	copy = (vm_map_copy_t) zalloc(vm_map_copy_zone);
	vm_map_copy_first_entry(copy) =
	 vm_map_copy_last_entry(copy) = vm_map_copy_to_entry(copy);
	copy->nentries = 0;
	copy->entries_pageable = TRUE;

	copy->min_offset = src_addr;
	copy->max_offset = src_addr + len;
	
#define	RETURN(x)						\
	MACRO_BEGIN						\
	vm_map_unlock(src_map);					\
	vm_map_copy_discard(copy);				\
	MACRO_RETURN(x);					\
	MACRO_END

	/*
	 *	Find the beginning of the region.
	 */

 	vm_map_lock(src_map);

	if (!vm_map_lookup_entry(src_map, src_start, &tmp_entry))
		RETURN(KERN_INVALID_ADDRESS);

	/*
	 *	single_use is live on entry to the loop.  It is used
	 *	to avoid getting fooled by object references that
	 *	the clipping operations create.  Initialize it here
	 *	before clipping has a chance to bump a ref count.
	 */

	if (tmp_entry->is_a_map ||
	    (tmp_entry->object.vm_object != VM_OBJECT_NULL &&
	     tmp_entry->object.vm_object->ref_count != 1))
		single_use = FALSE;
	else
		single_use = TRUE;

	vm_map_clip_start(src_map, tmp_entry, src_start);

	/*
	 *	Go through entries until we get to the end.
	 */

	while (TRUE) {
		register
		vm_map_entry_t	src_entry = tmp_entry;	/* Top-level entry */
		boolean_t	is_a_map;		/* A sharing map? */
		vm_size_t	src_size;		/* Size of source
							 * map entry (in both
							 * maps)
							 */

		vm_object_t	src_object;		/* Object to copy */
		vm_offset_t	src_offset;

		boolean_t	src_needs_copy;		/* Should source map
							 * be made read-only
							 * for copy-on-write?
							 */

		vm_map_entry_t	new_entry;		/* Map entry for copy */
		boolean_t	new_entry_needs_copy;	/* Will new entry be COW? */

		boolean_t	was_wired;		/* Was source wired? */
		vm_map_version_t version;		/* Version before locks
							 * dropped to make copy
							 */
		vm_map_t	sub_map;		/* Share map, if present  */

		/*
		 *	Verify that the region can be read.
		 */

		if (! (src_entry->protection & VM_PROT_READ))
			RETURN(KERN_PROTECTION_FAILURE);

		/*
		 *	Clip against the endpoints of the entire region.
		 */

		vm_map_clip_end(src_map, src_entry, src_end);

		src_size = (src_done = src_entry->vme_end) - src_start;

		/*
		 *	If this entry refers to a submap, follow it now.
		 */

		if (is_a_map = src_entry->is_a_map) {
			vm_size_t	sub_size;

			sub_map = src_entry->object.share_map;
			vm_map_lock(sub_map);

			if (!vm_map_lookup_entry(sub_map, src_entry->offset, &tmp_entry))
				panic("vm_map_copyin: submap lookup");

			/*
			 *	Clip both the top-level map entry and the
			 *	sharing map entry to the same (smallest) size.
			 */

			vm_map_clip_start(sub_map, tmp_entry, src_entry->offset);

			sub_size = (tmp_entry->vme_end - tmp_entry->vme_start);
			if (sub_size > src_size) {
				vm_map_clip_end(sub_map, tmp_entry,
					src_entry->offset + src_size);
			} else if (sub_size < src_size) {
				src_done = src_start + (src_size = sub_size);
				vm_map_clip_end(src_map, src_entry, src_done);
			}
		}

		src_object = tmp_entry->object.vm_object;
		src_offset = tmp_entry->offset;
		was_wired = (src_entry->wired_count);

		/*
		 *	Create a new address map entry to
		 *	hold the result.  Fill in the fields from
		 *	the appropriate source entries.
		 */

		new_entry = vm_map_entry_create(copy);
		*new_entry = *src_entry;
		new_entry->wired_count = 0;
		new_entry->user_wired_count = 0;

		if (is_a_map) {
			new_entry->object.vm_object = src_object;
			new_entry->offset = src_offset;
			new_entry->is_sub_map = FALSE;
			new_entry->is_a_map = FALSE;
		}

		/*
		 *	Attempt non-blocking copy-on-write optimizations.
		 */

                if (src_destroy &&
		    (src_object == VM_OBJECT_NULL || src_object->temporary)) {
                	/*
               		 * If we are destroying the source, and the object
                	 * is temporary, we can move the object reference
                	 * from the source to the copy.  The copy is
                	 * copy-on-write only if the source is.
                	 * We make another reference to the object, because
                	 * destroying the source entry will deallocate it.
                	 */
                	vm_object_reference(src_object);

                	goto CopySuccessful;
                }

		if (!was_wired &&
		    vm_object_copy_temporary(
				&new_entry->object.vm_object,
				&new_entry->offset,
				&src_needs_copy,
				&new_entry_needs_copy)) {

			new_entry->needs_copy = new_entry_needs_copy;

			/*
			 *	Temporary copy maps the object in two
			 *	places.  Don't have single_use any longer.
			 */
			single_use = FALSE;

			/*
			 *	Handle copy-on-write obligations
			 */

			if (src_needs_copy && !tmp_entry->needs_copy) {
				vm_object_pmap_protect(
					src_object,
					src_offset,
					src_size,
					(is_a_map ? PMAP_NULL : src_map->pmap),
					src_entry->vme_start,
					src_entry->protection &
					    ~VM_PROT_WRITE);

				tmp_entry->needs_copy =
				 tmp_entry->copy_on_write = TRUE;
			}

			new_entry->copy_on_write = new_entry->needs_copy;

			/*
			 *	The map has never been unlocked, so it's safe to
			 *	move to the next entry rather than doing another
			 *	lookup.
			 */

			if (is_a_map)
				vm_map_unlock(sub_map);

			goto CopySuccessful;
		}

		new_entry->needs_copy = FALSE;

		/*
		 *	Take an object reference, so that we may
		 *	release the map lock(s).
		 */

		assert(src_object != VM_OBJECT_NULL);
		vm_object_reference(src_object);

		/*
		 *	Record the timestamps for later verification.
		 *	Unlock the maps.
		 */

		if (is_a_map) {
			version.share_timestamp = sub_map->timestamp;
			vm_map_unlock(sub_map);
		}

		version.main_timestamp = src_map->timestamp;
		vm_map_unlock(src_map);

		/*
		 *	Perform the copy
		 */

		if (was_wired) {
			vm_object_lock(src_object);
			(void) vm_object_copy_slowly(
					src_object,
					src_offset,
					src_size,
					FALSE,
					&new_entry->object.vm_object);
			/*
			 *	Brand new object, only used by copy.
			 */
			new_entry->offset = 0;
			new_entry->needs_copy = FALSE;
			single_use = TRUE;
		} else {
			kern_return_t	result;
			boolean_t	new_entry_needs_copy;

			result = vm_object_copy_strategically(src_object,
				src_offset,
				src_size,
				&new_entry->object.vm_object,
				&new_entry->offset,
				&new_entry_needs_copy);

			new_entry->copy_on_write =
			 new_entry->needs_copy = new_entry_needs_copy;

			/*
			 *	copy_strategically could have done
			 *	all sorts of magic to make the copy.
			 *	Check the ref count on the new object
			 *	for single use.
			 */
			if (new_entry->object.vm_object->ref_count > 1)
				single_use = FALSE;
			else
				single_use = TRUE;

			if (result != KERN_SUCCESS) {
				vm_map_entry_dispose(copy, new_entry);

				vm_map_lock(src_map);
				RETURN(result);
			}

		}

		/*
		 *	Throw away the extra reference
		 */

		vm_object_deallocate(src_object);

		/*
		 *	Verify that the map has not substantially
		 *	changed while the copy was being made.
		 */

		vm_map_lock(src_map);	/* Increments timestamp once! */

		if (((version.main_timestamp + 1) == src_map->timestamp) &&
			(!is_a_map ||
			 (version.share_timestamp == sub_map->timestamp)) )
			goto CopySuccessful;

		/*
		 *	Simple version comparison failed.
		 *
		 *	Clear all the single use bits in
		 *	entries already copied because they
		 *	could be wrong (overly pessimistic,
		 *	but that's the breaks).
		 */

		for (tmp_entry = vm_map_copy_first_entry(copy);
		     tmp_entry != vm_map_copy_to_entry(copy);
		     tmp_entry = tmp_entry->vme_next) {
				tmp_entry->single_use = FALSE;
		}

		/*
		 *	Retry the lookup and verify that the
		 *	same object/offset are still present.
		 *
		 *	[Note: a memory manager that colludes with
		 *	the calling task can detect that we have
		 *	cheated.  While the map was unlocked, the
		 *	mapping could have been changed and restored.]
		 */

		if (!vm_map_lookup_entry(src_map, src_start, &tmp_entry)) {
			vm_map_entry_dispose(copy, new_entry);
			RETURN(KERN_INVALID_ADDRESS);
		}

		src_entry = tmp_entry;
		vm_map_clip_start(src_map, src_entry, src_start);

		if ((src_entry->protection & VM_PROT_READ) == VM_PROT_NONE)
			goto VerificationFailed;

		if (src_entry->vme_end < new_entry->vme_end)
			src_size = (new_entry->vme_end = src_entry->vme_end) - src_start;

		if (src_entry->is_a_map) {
			vm_size_t	sub_size;
			
			sub_map = src_entry->object.share_map;

			/*
			 *	Check for new object/offset, and clip copy
			 *	entry to the size of the share map entry.
			 */

			vm_map_lock(sub_map);
			(void) vm_map_lookup_entry(sub_map, src_entry->offset, &tmp_entry);
			if ((tmp_entry->object.vm_object != src_object) ||
			    (tmp_entry->offset != src_offset) ) {
				vm_map_unlock(sub_map);
				goto VerificationFailed;
			}

			sub_size = tmp_entry->vme_end - tmp_entry->vme_start;
			if (sub_size < src_size)
				new_entry->vme_end = new_entry->vme_start + (src_size = sub_size);
			vm_map_unlock(sub_map);
		} else {
			if ((src_entry->object.vm_object != src_object) ||
			    (src_entry->offset != src_offset) ) {

				/*
				 *	Verification failed.
				 *
				 *	Start over with this top-level entry.
				 */

			 VerificationFailed: ;

				vm_object_deallocate(
					new_entry->object.vm_object);
				vm_map_entry_dispose(copy, new_entry);
				tmp_entry = src_entry;
				src_done = src_start;
				goto ContinueLoop;
			}
		}

		/*
		 *	Verification succeeded.
		 */

	CopySuccessful: ;

		/*
		 *	Link in the new copy entry.
		 */

		vm_map_entry_link(copy, vm_map_copy_last_entry(copy),
					new_entry);
		new_entry->single_use = single_use;

		/*
		 *	Determine whether the entire region
		 *	has been copied.
		 */

		if (((src_start = src_done) >= src_end) && (src_end != 0))
			break;

		/*
		 *	Verify that there are no gaps in the region
		 */

		tmp_entry = src_entry->vme_next;
		if (tmp_entry->vme_start != src_start)
			RETURN(KERN_INVALID_ADDRESS);

	ContinueLoop: ;

		if (tmp_entry->is_a_map ||
		    (tmp_entry->object.vm_object != VM_OBJECT_NULL &&
		     tmp_entry->object.vm_object->ref_count != 1))
			single_use = FALSE;
		else
			single_use = TRUE;

	}

	if (src_destroy)
		(void) vm_map_delete(src_map, trunc_page(src_addr), src_end);

	vm_map_unlock(src_map);

	*copy_result = copy;
	return(KERN_SUCCESS);

#undef	RETURN
}

/*
 *	vm_map_fork:
 *
 *	Create and return a new map based on the old
 *	map, according to the inheritance values on the
 *	regions in that map.
 *
 *	The source map must not be locked.
 */
vm_map_t vm_map_fork(old_map)
	vm_map_t	old_map;
{
	vm_map_t	new_map, new_share_map;
	vm_map_entry_t	old_entry;
	vm_map_entry_t	new_entry;
	pmap_t		new_pmap = pmap_create((vm_size_t) 0);
	vm_size_t	new_size = 0;
	vm_size_t	entry_size;

	vm_map_lock(old_map);

	new_map = vm_map_create(new_pmap,
			old_map->min_offset,
			old_map->max_offset,
			old_map->entries_pageable);

	new_share_map = VM_MAP_NULL;

	for (
	    old_entry = vm_map_first_entry(old_map);
	    old_entry != vm_map_to_entry(old_map);
	    ) {
		if (old_entry->is_sub_map)
			panic("vm_map_fork: encountered a submap");

		entry_size = (old_entry->vme_end - old_entry->vme_start);

		switch (old_entry->inheritance) {
		case VM_INHERIT_NONE:
			break;

		case VM_INHERIT_SHARE:
			/*
			 *	If we don't already have a sharing map:
			 */

			if (!old_entry->is_a_map) {
				vm_map_entry_t	new_share_entry;
			
				/*
				 *	Create exactly one new sharing map
				 *	for use by all VM_INHERIT_SHARE
				 *	entries that don't already reference
				 *	sharing maps.  Each entry needs
				 *	a reference to this map (for pointer
				 *	to it); creation returns an initial
				 *	reference, but subsequent passes
				 *	through this code need an explicit
				 *	reference.
				 */

				if (new_share_map == VM_MAP_NULL) {

					new_share_map = vm_map_create(
						    PMAP_NULL,
			    			    old_map->min_offset,
						    old_map->max_offset,
						    old_map->entries_pageable);

			    		new_share_map->is_main_map = FALSE;
				}
				else {
					vm_map_reference(new_share_map);
				}
			
				/*
				 *	Create a new sharing entry from the
				 *	old task map entry.
				 */

				new_share_entry =
					vm_map_entry_create(new_share_map);
				*new_share_entry = *old_entry;

				/*
				 *	Insert the entry at end of new sharing
				 *	map.  Has to be at end because
				 *	the old map is being scanned forward.
				 */

				vm_map_entry_link(
					new_share_map,
					vm_map_last_entry(new_share_map),
					new_share_entry
					);

				/*
				 *	Fix up the task map entry to refer
				 *	to the sharing map now.
				 */

				old_entry->is_a_map = TRUE;
				old_entry->object.share_map = new_share_map;
				old_entry->offset = old_entry->vme_start;
			}

			/*
			 *	Clone the entry, referencing the sharing map.
			 */

			new_entry = vm_map_entry_create(new_map);
			*new_entry = *old_entry;
			vm_map_reference(new_entry->object.share_map);

			/*
			 *	Insert the entry into the new map -- we
			 *	know we're inserting at the end of the new
			 *	map.
			 */

			vm_map_entry_link(
				new_map,
				vm_map_last_entry(new_map),
				new_entry);

			/*
			 *	Update the physical map
			 */

			pmap_copy(new_map->pmap, old_map->pmap,
				new_entry->vme_start,
				entry_size,
				old_entry->vme_start);

			new_size += entry_size;
			break;

		case VM_INHERIT_COPY:
			if (!old_entry->is_a_map &&
				old_entry->wired_count == 0) {
				boolean_t	src_needs_copy;
				boolean_t	new_entry_needs_copy;

				new_entry = vm_map_entry_create(new_map);
				*new_entry = *old_entry;

				if (vm_object_copy_temporary(
					&new_entry->object.vm_object,
					&new_entry->offset,
					&src_needs_copy,
					&new_entry_needs_copy)) {

					/*
					 *	Handle copy-on-write obligations
					 */

					if (src_needs_copy && !old_entry->needs_copy) {
						vm_object_pmap_protect(
							old_entry->object.vm_object,
							old_entry->offset,
							entry_size,
							old_map->pmap,
							old_entry->vme_start,
							old_entry->protection &
							    ~VM_PROT_WRITE);

						old_entry->copy_on_write =
						 old_entry->needs_copy = TRUE;
					}

					new_entry->copy_on_write =
					 new_entry->needs_copy = new_entry_needs_copy;

					/*
					 *	Insert the entry at the end
					 *	of the map.
					 */

					vm_map_entry_link(new_map,
						vm_map_last_entry(new_map),
						new_entry);


					new_size += entry_size;
					break;
				}

				vm_map_entry_dispose(new_map, new_entry);
			}

			/* INNER BLOCK (copy cannot be optimized) */ {

			vm_offset_t	start = old_entry->vme_start;
			vm_map_copy_t	copy;
			vm_map_entry_t	last = vm_map_last_entry(new_map);

			vm_map_unlock(old_map);
			if (vm_map_copyin(old_map, start, entry_size, FALSE, &copy) 
			    != KERN_SUCCESS) {
			    	vm_map_lock(old_map);
				if (!vm_map_lookup_entry(old_map, start, &last))
					last = last->vme_next;
				old_entry = last;
				/*
				 *	For some error returns, want to
				 *	skip to the next element.
				 */

				continue;
			}

			/*
			 *	Insert the copy into the new map
			 */

			vm_map_copy_insert(new_map, last, copy, TRUE);
			new_size += entry_size;

			/*
			 *	Pick up the traversal at the end of
			 *	the copied region.
			 */

			vm_map_lock(old_map);
			start += entry_size;
			if (!vm_map_lookup_entry(old_map, start, &last))
				last = last->vme_next;
			 else
				vm_map_clip_start(old_map, last, start);
			old_entry = last;

			continue;
			/* INNER BLOCK (copy cannot be optimized) */ }
		}
		old_entry = old_entry->vme_next;
	}

	new_map->size = new_size;
	vm_map_unlock(old_map);

	return(new_map);
}

/*
 *	vm_map_lookup:
 *
 *	Finds the VM object, offset, and
 *	protection for a given virtual address in the
 *	specified map, assuming a page fault of the
 *	type specified.
 *
 *	Returns the (object, offset, protection) for
 *	this address, whether it is wired down, and whether
 *	this map has the only reference to the data in question.
 *	In order to later verify this lookup, a "version"
 *	is returned.
 *
 *	The map should not be locked; it will not be
 *	locked on exit.  In order to guarantee the
 *	existence of the returned object, it is returned
 *	locked.
 *
 *	If a lookup is requested with "write protection"
 *	specified, the map may be changed to perform virtual
 *	copying operations, although the data referenced will
 *	remain the same.
 */
kern_return_t vm_map_lookup(var_map, vaddr, fault_type, out_version,
				object, offset, out_prot, wired, single_use)
	vm_map_t		*var_map;	/* IN/OUT */
	register vm_offset_t	vaddr;
	register vm_prot_t	fault_type;

	vm_map_version_t	*out_version;	/* OUT */
	vm_object_t		*object;	/* OUT */
	vm_offset_t		*offset;	/* OUT */
	vm_prot_t		*out_prot;	/* OUT */
	boolean_t		*wired;		/* OUT */
	boolean_t		*single_use;	/* OUT */
{
	vm_map_t			share_map;
	vm_offset_t			share_offset;
	register vm_map_entry_t		entry;
	register vm_map_t		map = *var_map;
	register vm_prot_t		prot;
	register boolean_t		su;

	RetryLookup: ;

	/*
	 *	Lookup the faulting address.
	 */

	vm_map_lock_read(map);

#define RETURN(why) \
		{ \
		vm_map_unlock_read(map); \
		return(why); \
		}

	/*
	 *	If the map has an interesting hint, try it before calling
	 *	full blown lookup routine.
	 */

	simple_lock(&map->hint_lock);
	entry = map->hint;
	simple_unlock(&map->hint_lock);

	if ((entry == vm_map_to_entry(map)) ||
	    (vaddr < entry->vme_start) || (vaddr >= entry->vme_end)) {
		vm_map_entry_t	tmp_entry;

		/*
		 *	Entry was either not a valid hint, or the vaddr
		 *	was not contained in the entry, so do a full lookup.
		 */
		if (!vm_map_lookup_entry(map, vaddr, &tmp_entry))
			RETURN(KERN_INVALID_ADDRESS);

		entry = tmp_entry;
	}

	/*
	 *	Handle submaps.
	 */

	if (entry->is_sub_map) {
		vm_map_t	old_map = map;

		*var_map = map = entry->object.sub_map;
		vm_map_unlock_read(old_map);
		goto RetryLookup;
	}
		
	/*
	 *	Check whether this task is allowed to have
	 *	this page.
	 */

	prot = entry->protection;
	if ((fault_type & (prot)) != fault_type)
		RETURN(KERN_PROTECTION_FAILURE);

	/*
	 *	If this page is not pageable, we have to get
	 *	it for all possible accesses.
	 */

	if (*wired = (entry->wired_count != 0))
		prot = fault_type = entry->protection;

	/*
	 *	If we don't already have a VM object, track
	 *	it down.
	 */

	if (su = !entry->is_a_map) {
	 	share_map = map;
		share_offset = vaddr;
	}
	else {
		vm_map_entry_t	share_entry;

		/*
		 *	Compute the sharing map, and offset into it.
		 */

		share_map = entry->object.share_map;
		share_offset = (vaddr - entry->vme_start) + entry->offset;

		/*
		 *	Look for the backing store object and offset
		 */

		vm_map_lock_read(share_map);

		if (!vm_map_lookup_entry(share_map, share_offset,
					&share_entry)) {
			vm_map_unlock_read(share_map);
			RETURN(KERN_INVALID_ADDRESS);
		}
		entry = share_entry;
	}

	/*
	 *	If the entry was copy-on-write, we either ...
	 */

	if (entry->needs_copy) {
	    	/*
		 *	If we want to write the page, we may as well
		 *	handle that now since we've got the sharing
		 *	map locked.
		 *
		 *	If we don't need to write the page, we just
		 *	demote the permissions allowed.
		 */

		if (fault_type & VM_PROT_WRITE) {
			/*
			 *	Make a new object, and place it in the
			 *	object chain.  Note that no new references
			 *	have appeared -- one just moved from the
			 *	share map to the new object.
			 */

			if (vm_map_lock_read_to_write(share_map)) {
				if (share_map != map)
					vm_map_unlock_read(map);
				goto RetryLookup;
			}
			share_map->timestamp++;

			vm_object_shadow(
				&entry->object.vm_object,
				&entry->offset,
				(vm_size_t) (entry->vme_end - entry->vme_start));
				
			entry->needs_copy = FALSE;
			
			vm_map_lock_write_to_read(share_map);
		}
		else {
			/*
			 *	We're attempting to read a copy-on-write
			 *	page -- don't allow writes.
			 */

			prot &= (~VM_PROT_WRITE);
		}
	}

	/*
	 *	Create an object if necessary.
	 */
	if (entry->object.vm_object == VM_OBJECT_NULL) {

		if (vm_map_lock_read_to_write(share_map)) {
			if (share_map != map)
				vm_map_unlock_read(map);
			goto RetryLookup;
		}

		entry->object.vm_object = vm_object_allocate(
					(vm_size_t)(entry->vme_end - entry->vme_start));
		entry->offset = 0;
		vm_map_lock_write_to_read(share_map);
	}

	/*
	 *	Return the object/offset from this entry.  If the entry
	 *	was copy-on-write or empty, it has been fixed up.
	 */

	*offset = (share_offset - entry->vme_start) + entry->offset;
	*object = entry->object.vm_object;

	/*
	 *	Return whether this is the only map sharing this data.
	 */

	if (!su) {
		simple_lock(&share_map->ref_lock);
		su = (share_map->ref_count == 1);
		simple_unlock(&share_map->ref_lock);
	}

	*out_prot = prot;
	*single_use = su;

	/*
	 *	Lock the object to prevent it from disappearing
	 */

	vm_object_lock(*object);

	/*
	 *	Save the version numbers and unlock the map(s).
	 */

	if (share_map != map) {
		out_version->share_timestamp = share_map->timestamp;
		vm_map_unlock_read(share_map);
	}
	out_version->share_map = share_map;
	out_version->main_timestamp = map->timestamp;

	vm_map_unlock_read(map);

	return(KERN_SUCCESS);
	
#undef	RETURN
}

/*
 *	vm_map_verify:
 *
 *	Verifies that the map in question has not changed
 *	since the given version.  If successful, the map
 *	will not change until vm_map_verify_done() is called.
 */
boolean_t	vm_map_verify(map, version)
	register
	vm_map_t	map;
	register
	vm_map_version_t *version;	/* REF */
{
	boolean_t	result;

	vm_map_lock_read(map);
	if (result = (map->timestamp == version->main_timestamp)) {
		register
		vm_map_t	share_map = version->share_map;

		if (share_map != map) {
			vm_map_lock_read(version->share_map);
			if (!(result = (share_map->timestamp == version->share_timestamp))) {
				vm_map_unlock_read(share_map);
			}
		}
	}

	if (!result)
		vm_map_unlock_read(map);

	return(result);
}

/*
 *	vm_map_verify_done:
 *
 *	Releases locks acquired by a vm_map_verify.
 */
void		vm_map_verify_done(map, version)
	register vm_map_t	map;
	vm_map_version_t	*version;	/* REF */
{
	if (version->share_map != map)
		vm_map_unlock_read(version->share_map);
	vm_map_unlock_read(map);
}

kern_return_t	vm_region(map, address, size,
				protection, max_protection,
				inheritance, is_shared,
				object_name, offset_in_object)
	vm_map_t	map;
	vm_offset_t	*address;		/* IN/OUT */
	vm_size_t	*size;			/* OUT */
	vm_prot_t	*protection;		/* OUT */
	vm_prot_t	*max_protection;	/* OUT */
	vm_inherit_t	*inheritance;		/* OUT */
	boolean_t	*is_shared;		/* OUT */
	port_t		*object_name;		/* OUT */
	vm_offset_t	*offset_in_object;	/* OUT */
{
	vm_map_entry_t	tmp_entry;
	register
	vm_map_entry_t	entry;
	register
	vm_offset_t	tmp_offset;
	vm_offset_t	start;

	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);
	
	start = *address;

	vm_map_lock_read(map);
	if (!vm_map_lookup_entry(map, start, &tmp_entry)) {
		if ((entry = tmp_entry->vme_next) == vm_map_to_entry(map)) {
			vm_map_unlock_read(map);
		   	return(KERN_NO_SPACE);
		}
	} else {
		entry = tmp_entry;
	}

	start = entry->vme_start;
	*protection = entry->protection;
	*max_protection = entry->max_protection;
	*inheritance = entry->inheritance;
	*address = start;
	*size = (entry->vme_end - start);

	tmp_offset = entry->offset;

	if (entry->is_a_map) {
		register
		vm_map_t	share_map;
		vm_size_t	share_size;

		share_map = entry->object.share_map;

		vm_map_lock_read(share_map);
		(void) vm_map_lookup_entry(share_map, tmp_offset, &tmp_entry);

		if ((share_size = (tmp_entry->vme_end - tmp_offset)) < *size)
			*size = share_size;

		*object_name = vm_object_name(tmp_entry->object.vm_object);
		*offset_in_object = tmp_entry->offset + (tmp_offset - tmp_entry->vme_start);

		*is_shared = (share_map->ref_count != 1);
		vm_map_unlock_read(share_map);
	} else if (entry->is_sub_map) {
		*is_shared = FALSE;
		*object_name = PORT_NULL;
		*offset_in_object = tmp_offset;
	} else {
		*is_shared = FALSE;
		*object_name = vm_object_name(entry->object.vm_object);
		*offset_in_object = tmp_offset;
	}

	vm_map_unlock_read(map);

	return(KERN_SUCCESS);
}

/*
 *	Routine:	vm_map_simplify
 *
 *	Description:
 *		Attempt to simplify the map representation in
 *		the vicinity of the given starting address.
 *	Note:
 *		This routine is intended primarily to keep the
 *		kernel maps more compact -- they generally don't
 *		benefit from the "expand a map entry" technology
 *		at allocation time because the adjacent entry
 *		is often wired down.
 */
void vm_map_simplify(map, start)
	vm_map_t	map;
	vm_offset_t	start;
{
	vm_map_entry_t	this_entry;
	vm_map_entry_t	prev_entry;

	vm_map_lock(map);
	if (
		(vm_map_lookup_entry(map, start, &this_entry)) &&
		((prev_entry = this_entry->vme_prev) != vm_map_to_entry(map)) &&

		(prev_entry->vme_end == start) &&
		(map->is_main_map) &&

		(prev_entry->is_a_map == FALSE) &&
		(prev_entry->is_sub_map == FALSE) &&

		(this_entry->is_a_map == FALSE) &&
		(this_entry->is_sub_map == FALSE) &&

		(prev_entry->inheritance == this_entry->inheritance) &&
		(prev_entry->protection == this_entry->protection) &&
		(prev_entry->max_protection == this_entry->max_protection) &&
		(prev_entry->wired_count == this_entry->wired_count) &&
		(prev_entry->user_wired_count == this_entry->user_wired_count) &&
		
		(prev_entry->copy_on_write == this_entry->copy_on_write) &&
		(prev_entry->needs_copy == this_entry->needs_copy) &&
		
		(prev_entry->object.vm_object == this_entry->object.vm_object) &&
		((prev_entry->offset + (prev_entry->vme_end - prev_entry->vme_start))
		     == this_entry->offset)
	) {
		if (map->first_free == this_entry)
			map->first_free = prev_entry;

		SAVE_HINT(map, prev_entry);
		vm_map_entry_unlink(map, this_entry);
		prev_entry->vme_end = this_entry->vme_end;
	 	vm_object_deallocate(this_entry->object.vm_object);
		vm_map_entry_dispose(map, this_entry);
	}
	vm_map_unlock(map);
}


/*
 *	Routine:	vm_map_machine_attribute
 *	Purpose:
 *		Provide machine-specific attributes to mappings,
 *		such as cachability etc. for machines that provide
 *		them.  NUMA architectures and machines with big/strange
 *		caches will use this.
 *	Note:
 *		Responsibilities for locking and checking are handled here,
 *		everything else in the pmap module. If any non-volatile
 *		information must be kept, the pmap module should handle
 *		it itself. [This assumes that attributes do not
 *		need to be inherited, which seems ok to me]
 */
kern_return_t vm_map_machine_attribute(map, address, size, attribute, value)
	vm_map_t	map;
	vm_offset_t	address;
	vm_size_t	size;
	vm_machine_attribute_t	attribute;
	vm_machine_attribute_val_t* value;		/* IN/OUT */
{
	kern_return_t	ret;

	if (address < vm_map_min(map) ||
	    (address + size) > vm_map_max(map))
		return KERN_INVALID_ARGUMENT;

	vm_map_lock(map);

	ret = pmap_attribute(map->pmap, address, size, attribute, value);

	vm_map_unlock(map);

	return ret;
}


#include <mach_kdb.h>
#if	MACH_KDB

#define printf	kdbprintf

/*
 *	vm_map_print:	[ debug ]
 */
void vm_map_print(map)
	register vm_map_t	map;
{
	register vm_map_entry_t	entry;
	extern int indent;

	iprintf("%s map 0x%X: pmap=0x%X,",
		(map->is_main_map ? "Task" : "Share"),
 		(int) map, (int) (map->pmap));
	 printf("ref=%d,nentries=%d,", map->ref_count, map->nentries);
	 printf("version=%d\n",	map->timestamp);
	indent += 2;
	for (entry = vm_map_first_entry(map);
	     entry != vm_map_to_entry(map);
	     entry = entry->vme_next) {
		iprintf("map entry 0x%X: ", (int) entry);
		 printf("start=0x%X, end=0x%X, ",
			(int) entry->vme_start, (int) entry->vme_end);
		if (map->is_main_map) {
		     	static char *inheritance_name[4] =
				{ "share", "copy", "none", "donate_copy"};
			printf("prot=%X/%X/%s, ",
				entry->protection,
				entry->max_protection,
				inheritance_name[entry->inheritance]);
			if (entry->wired_count != 0) {
				printf("wired(");
				if (entry->user_wired_count != 0)
					printf("u");
				if (entry->wired_count >
				    (entry->user_wired_count == 0) ? 0 : 1)
					printf("k");
				printf(")");
			}
		}

		if (entry->is_a_map) {
		 	printf("share=0x%X, offset=0x%X\n",
				(int) entry->object.share_map,
				(int) entry->offset);
			if ((entry->vme_prev == vm_map_to_entry(map)) || (!entry->vme_prev->is_a_map) ||
			    (entry->vme_prev->object.share_map != entry->object.share_map)) {
				indent += 2;
				vm_map_print(entry->object.share_map);
				indent -= 2;
			}
				
		} else if (entry->is_sub_map) {
		 	printf("submap=0x%X, offset=0x%X\n",
				(int) entry->object.sub_map,
				(int) entry->offset);
		} else {
			printf("object=0x%X, offset=0x%X",
				(int) entry->object.vm_object,
				(int) entry->offset);
			if (entry->copy_on_write)
				printf(", copy (%s)", entry->needs_copy ? "needed" : "done");
			printf("\n");

			if ((entry->vme_prev == vm_map_to_entry(map)) || (entry->vme_prev->is_a_map) ||
			    (entry->vme_prev->object.vm_object != entry->object.vm_object)) {
				indent += 2;
				vm_object_print(entry->object.vm_object);
				indent -= 2;
			}
		}
	}
	indent -= 2;
}
#endif	MACH_KDB

