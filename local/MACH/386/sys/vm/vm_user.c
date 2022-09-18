/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_user.c,v $
 * Revision 2.12  89/04/18  21:30:56  mwyoung
 * 	All relevant history has been integrated into the documentation below.
 * 
 */
/*
 *	File:	vm/vm_user.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	User-exported virtual memory functions.
 */
#include <mach_xp.h>

#include <sys/types.h>

#include <mach/vm_param.h>
#include <vm/vm_object.h>
#include <vm/vm_map.h>
#include <vm/vm_page.h>
#include <mach/vm_statistics.h>

#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <kern/task.h>

#include <mach/std_types.h>	/* to get pointer_t */
#include <mach/mach_types.h>	/* to get vm_address_t */
#include <kern/ipc_globals.h>

#include <mach/memory_object.h>

vm_statistics_data_t	vm_stat;

#if	MACH_XP
#else	MACH_XP
#include <kern/lock.h>
lock_data_t		vm_alloc_lock;

/*
 *	vm_user_init initializes the vm_alloc lock.  XXX
 */
void
vm_user_init()
{
	lock_init(&vm_alloc_lock, TRUE);
}
#endif	MACH_XP


/*
 *	vm_allocate allocates "zero fill" memory in the specfied
 *	map.
 */
kern_return_t vm_allocate(map, addr, size, anywhere)
	register vm_map_t	map;
	register vm_offset_t	*addr;
	register vm_size_t	size;
	boolean_t		anywhere;
{
	kern_return_t	result;

	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);
	if (size == 0) {
		*addr = 0;
		return(KERN_SUCCESS);
	}

	if (anywhere)
		*addr = vm_map_min(map);
	else
		*addr = trunc_page(*addr);
	size = round_page(size);

	result = vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t) 0, addr,
			size, anywhere);

	return(result);
}

/*
 *	vm_deallocate deallocates the specified range of addresses in the
 *	specified address map.
 */
kern_return_t vm_deallocate(map, start, size)
	register vm_map_t	map;
	vm_offset_t		start;
	vm_size_t		size;
{
	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);

	if (size == (vm_offset_t) 0)
		return(KERN_SUCCESS);

	return(vm_map_remove(map, trunc_page(start), round_page(start+size)));
}

/*
 *	vm_inherit sets the inheritence of the specified range in the
 *	specified map.
 */
kern_return_t vm_inherit(map, start, size, new_inheritance)
	register vm_map_t	map;
	vm_offset_t		start;
	vm_size_t		size;
	vm_inherit_t		new_inheritance;
{
	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);

	return(vm_map_inherit(map, trunc_page(start), round_page(start+size), new_inheritance));
}

/*
 *	vm_protect sets the protection of the specified range in the
 *	specified map.
 */

kern_return_t vm_protect(map, start, size, set_maximum, new_protection)
	register vm_map_t	map;
	vm_offset_t		start;
	vm_size_t		size;
	boolean_t		set_maximum;
	vm_prot_t		new_protection;
{
	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);

	return(vm_map_protect(map, trunc_page(start), round_page(start+size), new_protection, set_maximum));
}

kern_return_t vm_statistics(map, stat)
	vm_map_t	map;
	vm_statistics_data_t	*stat;
{
	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);
	
	*stat = vm_stat;

	stat->pagesize = PAGE_SIZE;
	stat->free_count = vm_page_free_count;
	stat->active_count = vm_page_active_count;
	stat->inactive_count = vm_page_inactive_count;
	stat->wire_count = vm_page_wire_count;

	return(KERN_SUCCESS);
}

kern_return_t vm_read(map, address, size, data, data_size)
	vm_map_t	map;
	vm_address_t	address;
	vm_size_t	size;
	pointer_t	*data;
	vm_size_t	*data_size;
{
	kern_return_t	error;
	vm_offset_t	ipc_address;

	if ((round_page(address) != address) || (round_page(size) != size))
		return(KERN_INVALID_ARGUMENT);

	if ((error = vm_allocate(ipc_soft_map, &ipc_address, size, TRUE)) != KERN_SUCCESS) {
		printf("vm_read: kernel error %d\n", error);
		return(KERN_RESOURCE_SHORTAGE);
	}

	if ((error = vm_map_copy(ipc_soft_map, map, ipc_address, size, address, FALSE, FALSE)) == KERN_SUCCESS) {
		*data = ipc_address;
		*data_size = size;
	}
	return(error);
}

kern_return_t vm_write(map, address, data, size)
	vm_map_t	map;
	vm_address_t	address;
	pointer_t	data;
	vm_size_t	size;
{
	if ((round_page(address) != address) || (round_page(size) != size))
		return(KERN_INVALID_ARGUMENT);

	return(vm_map_copy(map, ipc_soft_map, address, size, data, FALSE, FALSE));
}

kern_return_t vm_copy(map, source_address, size, dest_address)
	vm_map_t	map;
	vm_address_t	source_address;
	vm_size_t	size;
	vm_address_t	dest_address;
{
	if ( (round_page(source_address) != source_address) || (round_page(dest_address) != dest_address)
	     || (round_page(size) != size) )
		return(KERN_INVALID_ARGUMENT);

	return(vm_map_copy(map, map, dest_address, size, source_address, FALSE, FALSE));
}


/*
 *	Routine:	vm_map
 */
kern_return_t vm_map(
		target_map,
		address, size, mask, anywhere,
		memory_object, offset,
		copy,
		cur_protection, max_protection,	inheritance)
	vm_map_t	target_map;
	vm_offset_t	*address;
	vm_size_t	size;
	vm_offset_t	mask;
	boolean_t	anywhere;
	memory_object_t	memory_object;
	vm_offset_t	offset;
	boolean_t	copy;
	vm_prot_t	cur_protection;
	vm_prot_t	max_protection;
	vm_inherit_t	inheritance;
{
	register
	vm_object_t	object;
	register
	kern_return_t	result;

	if (target_map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);

	*address = trunc_page(*address);
	size = round_page(size);

#if	MACH_XP
	if (memory_object == MEMORY_OBJECT_NULL) {
		object = VM_OBJECT_NULL;
		offset = 0;
		copy = FALSE;
	} else if ((object = vm_object_enter(memory_object, size, FALSE))
			== VM_OBJECT_NULL)
		return(KERN_INVALID_ARGUMENT);
#else	MACH_XP
	/*
	 *	Lookup the pager/paging-space in the object cache.
	 *	If it's not there, then create a new object and cache
	 *	it.
	 */
	lock_write(&vm_alloc_lock);
	object = vm_object_lookup(memory_object);
	vm_stat.lookups++;
	if (object == VM_OBJECT_NULL) {
		/*
		 *	Need a new object.
		 */
		object = vm_object_allocate(size);
		/*
		 *	Associate the object with the pager and
		 *	put it in the cache.
		 */
		if (memory_object != MEMORY_OBJECT_NULL) {
			vm_object_setpager(object, memory_object,
				(vm_offset_t) 0, TRUE);
			vm_object_enter(object, memory_object);
		}
	}
	else {
		vm_stat.hits++;
	}
	lock_write_done(&vm_alloc_lock);
	object->internal = FALSE;
#endif	MACH_XP

	/*
	 *	Perform the copy if requested
	 */

	if (copy) {
		vm_object_t	new_object;
		vm_offset_t	new_offset;
		boolean_t	src_needs_copy;

		vm_object_copy(object, offset, size,
				&new_object, &new_offset,
				&src_needs_copy, &copy, TRUE);

		/*
		 *	Since the "source" has not been mapped,
		 *	we ignore the "src_needs_copy" value.
		 *
		 *	Also, throw away the reference to the
		 *	original object, as it won't be mapped.
		 */

		vm_object_deallocate(object);

		if (new_object == VM_OBJECT_NULL)
			return(KERN_FAILURE); /* XXX */

		object = new_object;
		offset = new_offset;
	}

	if ((result = vm_map_enter(target_map,
				address, size, mask, anywhere,
				object, offset,
				copy,
				cur_protection, max_protection, inheritance
				)) != KERN_SUCCESS)
		vm_object_deallocate(object);
	return(result);
}

kern_return_t vm_allocate_with_pager(map, addr, size, find_space, pager,
		pager_offset)
	register vm_map_t	map;
	register vm_offset_t	*addr;
	register vm_size_t	size;
	boolean_t		find_space;
	memory_object_t		pager;
	vm_offset_t		pager_offset;
{
	return ((pager == MEMORY_OBJECT_NULL) ?
		KERN_INVALID_ARGUMENT :
		vm_map(map, addr, size, 0, find_space,
		pager, pager_offset, FALSE,
		VM_PROT_ALL, VM_PROT_ALL, VM_INHERIT_COPY)
		);
}
