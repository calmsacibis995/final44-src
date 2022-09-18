/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_pager.c,v $
 * Revision 2.9  89/04/18  21:28:46  mwyoung
 * 	History condensation:
 * 		External memory management interface moved to
 * 		 file "vm/memory_object.c".
 * 		Handle I/O errors more gracefully [dbg].
 * 		Basic external memory management interface
 * 		 implementation [mwyoung, bolosky].
 * 		Handle device mapping [dbg].
 * 		Original work [avie, dbg].
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm/vm_pager.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Paging space routine stubs.  Emulates a matchmaker-like interface
 *	for builtin pagers.
 */
#include <mach_xp.h>

#if	MACH_XP
#else	MACH_XP
#include <mach/kern_return.h>
#include <vm/vm_pager.h>
#include <vm/vm_page.h>
#include <mach/vm_prot.h>
#include <mach/boolean.h>
#include <builtin/inode_pager.h>
#include <kern/xpr.h>

#include <vm/pmap.h>

extern
boolean_t	vm_page_zero_fill();

kern_return_t pager_cache(object, should_cache)
	vm_object_t	object;
	boolean_t	should_cache;
{
	if (object == VM_OBJECT_NULL)
		return(KERN_INVALID_ARGUMENT);

	vm_object_lock(object);
	object->can_persist = should_cache;
	vm_object_unlock(object);

	vm_object_deallocate(object);

	return(KERN_SUCCESS);
}

pager_return_t vm_pager_get(pager, m)
	memory_object_t	pager;
	vm_page_t	m;
{
	pager_return_t	result;

	XPR(XPR_MEMORY_OBJECT, ("vm_pager_get: pager %x, page %x",
				pager, m));
	if (pager == MEMORY_OBJECT_NULL) {
		(void) vm_page_zero_fill(m);
		return(PAGER_SUCCESS);
	}
	if (((struct pager_struct *)pager)->is_device)
		return(device_pagein(m));
	result = inode_pagein(m);
	XPR(XPR_MEMORY_OBJECT, ("vm_pager_get: pager %x, page %x, result %x",
				pager, m, result));
	return(result);
}

pager_return_t vm_pager_put(pager, m)
	memory_object_t	pager;
	vm_page_t	m;
{
	pager_return_t	result;

	XPR(XPR_MEMORY_OBJECT, ("vm_pager_put: pager %x, page %x",
				pager, m));
	if (pager == MEMORY_OBJECT_NULL)
		panic("vm_pager_put: null pager");
	if (((struct pager_struct *)pager)->is_device)
		return(device_pageout(m));
	result = inode_pageout(m);
	XPR(XPR_MEMORY_OBJECT, ("vm_pager_put: pager %x, page %x, result %x",
				pager, m, result));
	return(result);
}

boolean_t vm_pager_deallocate(pager)
	memory_object_t	pager;
{
	if (pager == MEMORY_OBJECT_NULL)
		panic("vm_pager_deallocate: null pager");
	if (((struct pager_struct *)pager)->is_device)
		return(device_dealloc(pager));
	return(inode_dealloc(pager));
}

memory_object_t vm_pager_allocate(size)
	vm_size_t	size;
{
	return(inode_alloc(size));
}

boolean_t vm_pager_has_page(pager, offset)
	memory_object_t	pager;
	vm_offset_t	offset;
{
	if ((pager == MEMORY_OBJECT_NULL) || (((struct pager_struct *)pager)->is_device))
		panic("vm_pager_has_page");
	return(inode_has_page(pager,offset));
}

#endif	MACH_XP
