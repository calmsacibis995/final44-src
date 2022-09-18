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
 * Revision 2.16  90/07/03  16:58:20  mrt
 * 	Add discard argument to vm_map_copy_overwrite calls.
 * 	[90/06/21            dlb]
 * 
 * Revision 2.15  90/03/08  23:13:57  af
 * 	Added vm_machine_attribute().
 * 	[90/01/14            af]
 * 
 * Revision 2.14  89/10/10  13:49:10  mwyoung
 * 	Eliminate XP conditionals.  Add uprintf in
 * 	deprecated vm_allocate_with_pager call.
 * 	[89/10/10            mwyoung]
 * 
 * Revision 2.13  89/10/10  13:18:04  mwyoung
 * 	Use new vm_map_copy technology.
 * 	[89/06/26  19:07:31  mwyoung]
 * 
 * Revision 2.12  89/04/18  21:30:56  mwyoung
 * 	All relevant history has been integrated into the documentation below.
 * 
 */
/*
 *	File:	vm/vm_user.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Virtual memory functions exported to users.
 *	[See "mach/mach.defs" for full interface definition.]
 */

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
	vm_map_copy_t	ipc_address;

	if ((trunc_page(address) != address) || (trunc_page(size) != size))
		return(KERN_INVALID_ARGUMENT);

	if ((error = vm_map_copyin(map, address, size, FALSE, &ipc_address))
			== KERN_SUCCESS) {
		*data = (pointer_t) ipc_address;
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
	if ((trunc_page(address) != address) || (trunc_page(size) != size))
		return(KERN_INVALID_ARGUMENT);

	return(vm_map_copy_overwrite(
			map,
			address,
			(vm_map_copy_t) data,
			FALSE /* interruptible XXX */,
			FALSE /* don't discard copy */));
}

kern_return_t vm_copy(map, source_address, size, dest_address)
	vm_map_t	map;
	vm_address_t	source_address;
	vm_size_t	size;
	vm_address_t	dest_address;
{
	vm_map_copy_t	copy;
	kern_return_t	error;

	if ( (trunc_page(source_address) != source_address) || (trunc_page(dest_address) != dest_address)
	     || (trunc_page(size) != size) )
		return(KERN_INVALID_ARGUMENT);

	if ((error = vm_map_copyin(map, source_address, size, FALSE, &copy))
			!= KERN_SUCCESS)
		return(error);

	error = vm_map_copy_overwrite(map, dest_address, copy,
		FALSE /* interruptible XXX */,
		TRUE /* discard copy */);

	return(error);
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

	if (memory_object == MEMORY_OBJECT_NULL) {
		object = VM_OBJECT_NULL;
		offset = 0;
		copy = FALSE;
	} else if ((object = vm_object_enter(memory_object, size, FALSE))
			== VM_OBJECT_NULL)
		return(KERN_INVALID_ARGUMENT);

	/*
	 *	Perform the copy if requested
	 */

	if (copy) {
		vm_object_t	new_object;
		vm_offset_t	new_offset;

		result = vm_object_copy_strategically(object, offset, size,
				&new_object, &new_offset,
				&copy);

		/*
		 *	Throw away the reference to the
		 *	original object, as it won't be mapped.
		 */

		vm_object_deallocate(object);

		if (result != KERN_SUCCESS)
			return(result);

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
	uprintf("vm_allocate_with_pager: use vm_map_instead!\n");

	return ((pager == MEMORY_OBJECT_NULL) ?
		KERN_INVALID_ARGUMENT :
		vm_map(map, addr, size, 0, find_space,
		pager, pager_offset, FALSE,
		VM_PROT_ALL, VM_PROT_ALL, VM_INHERIT_COPY)
		);
}

/*
 * Handle machine-specific attributes for a mapping, such
 * as cachability, migrability, etc.
 */
kern_return_t vm_machine_attribute(map, address, size, attribute, value)
	vm_map_t	map;
	vm_address_t	address;
	vm_size_t	size;
	vm_machine_attribute_t	attribute;
	vm_machine_attribute_val_t* value;		/* IN/OUT */
{
	extern kern_return_t	vm_map_machine_attribute();

	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);

	return vm_map_machine_attribute(map, address, size, attribute, value);
}

