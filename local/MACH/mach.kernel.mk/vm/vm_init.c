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
 * $Log:	vm_init.c,v $
 * Revision 2.11  90/07/03  16:56:37  mrt
 * 	Remove !MACH_XP code.
 * 	[90/06/28            dlb]
 * 
 * Revision 2.10  89/04/22  15:35:20  gm0w
 * 	Removed MACH_VFS code.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.9  89/04/18  21:25:30  mwyoung
 * 	Recent history:
 * 	 	Add memory_manager_default_init(), vm_page_module_init().
 * 
 * 	Older history has been integrated into the documentation for
 * 	this module.
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm/vm_init.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Initialize the Virtual Memory subsystem.
 */

#include <mach/machine/vm_types.h>
#include <kern/lock.h>
#include <vm/vm_object.h>
#include <vm/vm_map.h>
#include <vm/vm_page.h>
#include <vm/vm_kern.h>
#include <builtin/inode_pager.h>

/*
 *	vm_init initializes the virtual memory system.
 *	This is done only by the first cpu up.
 *
 *	The start and end address of physical memory is passed in.
 */

void vm_mem_init()
{
	extern vm_offset_t	avail_start, avail_end;
	extern vm_offset_t	virtual_avail, virtual_end;

	/*
	 *	Initializes resident memory structures.
	 *	From here on, all physical memory is accounted for,
	 *	and we use only virtual addresses.
	 */

	virtual_avail = vm_page_startup(avail_start, avail_end, virtual_avail);

	/*
	 *	Initialize other VM packages
	 */

	zone_bootstrap();
	vm_object_init();
	vm_map_init();
	kmem_init(virtual_avail, virtual_end);
	pmap_init(avail_start, avail_end);
	zone_init();
	vm_page_module_init();
	memory_manager_default_init();
}
