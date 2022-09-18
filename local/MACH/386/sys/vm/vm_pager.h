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
 * $Log:	vm_pager.h,v $
 * Revision 2.8  89/04/18  21:29:01  mwyoung
 * 	History condensation: nothing new since last purge.
 * 	Participants so far: (mwyoung, avie, dbg, bolosky).
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm_pager.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Pager routine interface definition
 */

#ifndef	_VM_VM_PAGER_H_
#define _VM_VM_PAGER_H_

#include <mach_xp.h>

#include <mach/memory_object.h>

#if	MACH_XP
#define vm_pager_t	memory_object_t
#define vm_pager_null	(PORT_NULL)

extern void		vm_pager_init();

#else	MACH_XP
#include <mach/boolean.h>
/*
 *	For non-XP, a pager is a pointer to either an istruct or a
 *	dev_pager.  These two structures share the "is_device" boolean
 *	as the first field, which vm uses to dispatch to the correct
 *	routine.  The "pager_struct" defined here is only a convenience 
 *	for vm.
 */
struct	pager_struct {
		boolean_t	is_device;
	};

#define PAGER_SUCCESS		0	/* page read or written */
#define PAGER_ABSENT		1	/* pager does not have page */
#define PAGER_ERROR		2	/* pager unable to read or write page */

typedef	int		pager_return_t;

typedef	port_t		paging_object_t;
typedef	port_t		vm_pager_request_t;

extern memory_object_t	vm_pager_allocate();
extern boolean_t	vm_pager_alloc();
extern boolean_t	vm_pager_dealloc();
extern pager_return_t	vm_pager_get();
extern pager_return_t	vm_pager_put();
extern boolean_t	vm_pager_has_page();
#endif	MACH_XP

#endif	_VM_VM_PAGER_H_
