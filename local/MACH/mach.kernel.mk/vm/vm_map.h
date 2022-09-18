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
 * $Log:	vm_map.h,v $
 * Revision 2.15  90/09/10  21:09:17  mrt
 * 	Added vm_map_t->vm_stat, to support task_info(events).
 * 	[90/09/06            af]
 * 
 * Revision 2.14  90/07/03  16:57:20  mrt
 * 	Purge MACH_OLD_VM_COPY.
 * 	[90/06/26            dlb]
 * 	Add single_use field to map entries for use in map copies.
 * 	See vm_map_copyin.
 * 	[90/06/20            dlb]
 * 
 * Revision 2.13  90/03/27  18:58:59  dlb
 * 	Declare vm_submap_object for use with vm_map_submap.
 * 	[90/03/27            dlb]
 * 
 * Revision 2.12  89/12/22  15:56:30  rpd
 * 	Make both wired counts short.
 * 	[89/12/15            dlb]
 * 	Add user_wired_count field and vm_map_pageable macros.
 * 	[89/12/11            dlb]
 * 
 * Revision 2.11  89/10/10  11:23:39  mwyoung
 * 	Added documentation for exported routines.
 * 
 * 	Add vm_map_t->wait_for_space field.
 * 
 * 	Add vm_map_copy_t type, associated routine declarations, and
 * 	documentation.
 * 
 * 	Allow for old implementation of vm_map_copy technology
 * 	in case the new one is believed to be suspect.
 * 	[89/06/26  19:05:20  mwyoung]
 * 
 * Revision 2.10  89/10/03  19:30:29  rpd
 * 	Introduced vm_map_links, which contains those map entry fields
 * 	used in the map structure.
 * 	[89/08/31  21:13:56  rpd]
 * 
 * 	Optimization from NeXT:  is_a_map, is_sub_map, copy_on_write,
 * 	needs_copy are now bit-fields.
 * 	[89/08/19  23:44:53  rpd]
 * 
 * Revision 2.9  89/04/18  21:26:14  mwyoung
 * 	Reset history.  All relevant material is in the documentation
 * 	here, and in the implementation file ("vm/vm_map.c").
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm/vm_map.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Virtual memory map module definitions.
 *
 * Contributors:
 *	avie, dlb, mwyoung
 */

#ifndef	_VM_VM_MAP_H_
#define _VM_VM_MAP_H_

#include <mach/kern_return.h>
#include <mach/boolean.h>
#include <mach/machine/vm_types.h>
#include <mach/vm_prot.h>
#include <mach/vm_inherit.h>
#include <mach/vm_statistics.h>
#include <vm/pmap.h>
#include <vm/vm_object.h>
#include <kern/lock.h>
#include <kern/macro_help.h>

/*
 *	Types defined:
 *
 *	vm_map_t		the high-level address map data structure.
 *	vm_map_entry_t		an entry in an address map.
 *	vm_map_version_t	a timestamp of a map, for use with vm_map_lookup
 *	vm_map_copy_t		represents memory copied from an address map,
 *				 used for inter-map copy operations
 */

/*
 *	Type:		vm_map_object_t [internal use only]
 *
 *	Description:
 *		The target of an address mapping, either a virtual
 *		memory object or a sharing map that denotes sharing
 *		with other address maps.
 */
typedef union vm_map_object {
	struct vm_object	*vm_object;	/* object object */
	struct vm_map		*share_map;	/* share map */
	struct vm_map		*sub_map;	/* belongs to another map */
} vm_map_object_t;

/*
 *	Type:		vm_map_entry_t [internal use only]
 *
 *	Description:
 *		A single mapping within an address map.
 *
 *	Implementation:
 *		Address map entries consist of start and end addresses,
 *		a VM object (or sharing map) and offset into that object,
 *		and user-exported inheritance and protection information.
 *		Control information for virtual copy operations is also
 *		stored in the address map entry.
 */
struct vm_map_links {
	struct vm_map_entry	*prev;		/* previous entry */
	struct vm_map_entry	*next;		/* next entry */
	vm_offset_t		start;		/* start address */
	vm_offset_t		end;		/* end address */
};

struct vm_map_entry {
	struct vm_map_links	links;		/* links to other entries */
#define vme_prev		links.prev
#define vme_next		links.next
#define vme_start		links.start
#define vme_end			links.end
	union vm_map_object	object;		/* object I point to */
	vm_offset_t		offset;		/* offset into object */
	unsigned int
	/* boolean_t */		is_a_map:1,	/* Is "object" a map? */
	/* boolean_t */		is_sub_map:1,	/* Is "object" a submap? */
		/* Only used when object is a vm_object: */
	/* boolean_t */		copy_on_write:1,/* is data copy-on-write */
	/* boolean_t */		needs_copy:1,	/* does object need to be
						 * copied */
		/* Only used in map copies */
	/* boolean_t */		single_use:1;	/* do we have sole use of
						 * this data */
		/* Only in task maps: */
	vm_prot_t		protection;	/* protection code */
	vm_prot_t		max_protection;	/* maximum protection */
	vm_inherit_t		inheritance;	/* inheritance */
	short			wired_count;	/* can be paged if = 0 */
	short			user_wired_count; /* for vm_wire */
};

typedef struct vm_map_entry	*vm_map_entry_t;

#define VM_MAP_ENTRY_NULL	((vm_map_entry_t) 0)

/*
 *	Type:		vm_map_t [exported; contents invisible]
 *
 *	Description:
 *		An address map -- a directory relating valid
 *		regions of a task's address space to the corresponding
 *		virtual memory objects.
 *
 *	Implementation:
 *		Maps are doubly-linked lists of map entries, sorted
 *		by address.  One hint is used to start
 *		searches again from the last successful search,
 *		insertion, or removal.  Another hint is used to
 *		quickly find free space.
 *
 *		The same address map structure is also used to
 *		represent the contents of memory regions shared
 *		by more than one task.  When used this way, an
 *		address map is called a "sharing map".
 */
typedef struct vm_map {
	lock_data_t		lock;		/* Lock for map data */
	struct vm_map_links	links;		/* links to the entries */
#define min_offset		links.start	/* start of range */
#define max_offset		links.end	/* end of range */
	int			nentries;	/* Number of entries */
	pmap_t			pmap;		/* Physical map */
	vm_size_t		size;		/* virtual size */
	boolean_t		is_main_map;	/* Am I a main map? */
	int			ref_count;	/* Reference count */
	decl_simple_lock_data(,	ref_lock)	/* Lock for ref_count field */
	vm_map_entry_t		hint;		/* hint for quick lookups */
	decl_simple_lock_data(,	hint_lock)	/* lock for hint storage */
	vm_map_entry_t		first_free;	/* First free space hint */
	boolean_t		entries_pageable; /* map entries pageable?? */
	boolean_t		wait_for_space;	/* Should callers wait for space? */
	unsigned int		timestamp;	/* Version number */
	vm_statistics_data_t	vm_stat;
} *vm_map_t;

#define		VM_MAP_NULL	((vm_map_t) 0)

#define vm_map_to_entry(map)	((struct vm_map_entry *) &(map)->links)
#define vm_map_first_entry(map)	((map)->links.next)
#define vm_map_last_entry(map)	((map)->links.prev)

/*
 *	Type:		vm_map_version_t [exported; contents invisible]
 *
 *	Description:
 *		Map versions may be used to quickly validate a previous
 *		lookup operation.
 *
 *	Usage note:
 *		Because they are bulky objects, map versions are usually
 *		passed by reference.
 *
 *	Implementation:
 *		Since lookup operations may involve both a main map and
 *		a sharing map, it is necessary to have a timestamp from each.
 *		[If the main map timestamp has changed, the share_map and
 *		associated timestamp are no longer valid; therefore, the
 *		map version does not include a reference for the embedded
 *		share_map.]
 */
typedef struct {
	unsigned int	main_timestamp;
	vm_map_t	share_map;
	unsigned int	share_timestamp;
} vm_map_version_t;

/*
 *	Type:		vm_map_copy_t [exported; contents invisible]
 *
 *	Description:
 *		A map copy object represents a region of virtual memory
 *		that has been copied from an address map but is still
 *		in transit.
 *
 *		A map copy object may only be used by a single thread
 *		at a time.
 *
 *	Implementation:
 *		The map copy object is very similar to the main
 *		address map in structure, and as a result, some
 *		of the internal maintenance functions/macros can
 *		be used with either address maps or map copy objects.
 *
 *		The map copy object contains a header links
 *		entry onto which the other entries that represent
 *		the region are chained.  The endpoints in the
 *		header entry are used to record the original page
 *		alignment of the source region.
 */
typedef struct vm_map_copy {
	struct vm_map_links	links;
	unsigned int		nentries;
	boolean_t		entries_pageable;
} *vm_map_copy_t;

#define	VM_MAP_COPY_NULL	((vm_map_copy_t) 0)

#define vm_map_copy_to_entry(map)		\
		((struct vm_map_entry *) &(map)->links)
#define vm_map_copy_first_entry(map)		\
		((map)->links.next)
#define vm_map_copy_last_entry(map)		\
		((map)->links.prev)

/*
 *	Macros:		vm_map_lock, etc. [internal use only]
 *	Description:
 *		Perform locking on the data portion of a map.
 */

#define vm_map_lock_init(map)			\
MACRO_BEGIN					\
	lock_init(&(map)->lock, TRUE);		\
	(map)->timestamp = 0;			\
MACRO_END

#define vm_map_lock(map)			\
MACRO_BEGIN					\
	lock_write(&(map)->lock);		\
	(map)->timestamp++;			\
MACRO_END

#define vm_map_unlock(map)	lock_write_done(&(map)->lock)
#define vm_map_lock_read(map)	lock_read(&(map)->lock)
#define vm_map_unlock_read(map)	lock_read_done(&(map)->lock)
#define vm_map_lock_write_to_read(map) \
		lock_write_to_read(&(map)->lock)
#define vm_map_lock_read_to_write(map) \
		(lock_read_to_write(&(map)->lock) || (((map)->timestamp++), 0))
#define vm_map_lock_set_recursive(map) \
		lock_set_recursive(&(map)->lock)
#define vm_map_lock_clear_recursive(map) \
		lock_clear_recursive(&(map)->lock)

/*
 *	Exported procedures that operate on vm_map_t.
 */

extern void		vm_map_init();		/* Initialize the module */

extern vm_map_t		vm_map_create();	/* Create an empty map */
extern vm_map_t		vm_map_fork();		/* Create a map in the image
						 * of an existing map */

extern void		vm_map_reference();	/* Gain a reference to
						 * an existing map */
extern void		vm_map_deallocate();	/* Lose a reference */

extern kern_return_t	vm_map_enter();		/* Enter a mapping */
extern kern_return_t	vm_map_remove();	/* Deallocate a region */
extern kern_return_t	vm_map_protect();	/* Change protection */
extern kern_return_t	vm_map_inherit();	/* Change inheritance */

extern kern_return_t	vm_map_find();		/* Old allocation primitive */
extern void		vm_map_print();		/* Debugging: print a map */

extern kern_return_t	vm_map_lookup();	/* Look up an address */
extern boolean_t	vm_map_verify();	/* Verify that a previous
						 * lookup is still valid */
extern void		vm_map_verify_done();	/* Indicate that the operation
						 * requiring a verified lookup
						 * is complete. */

extern kern_return_t	vm_map_copyin();	/* Make a copy of a region */
extern kern_return_t	vm_map_copyout();	/* Place a copy into a map */
extern kern_return_t	vm_map_copy_overwrite();/* Overwrite existing memory
						 * with a copy */
extern void		vm_map_copy_discard();	/* Discard a copy without
						 * using it */

/*
 *	Functions implemented as macros
 */
#define		vm_map_min(map)		((map)->min_offset)
						/* Lowest valid address in
						 * a map */

#define		vm_map_max(map)		((map)->max_offset)
						/* Highest valid address */

#define		vm_map_pmap(map)	((map)->pmap)
						/* Physical map associated
						 * with this address map */

/*
 *	Pageability functions.  Includes macro to preserve old interface.
 */
extern kern_return_t	vm_map_pageable_common();

#define vm_map_pageable(map, s, e, access)	\
		vm_map_pageable_common(map, s, e, access, FALSE)

#define vm_map_pageable_user(map, s, e, access)	\
		vm_map_pageable_common(map, s, e, access, TRUE)

/*
 *	Submap object.  Must be used to create memory to be put
 *	in a submap by vm_map_submap.
 */
extern vm_object_t	vm_submap_object;

#endif	_VM_VM_MAP_H_
