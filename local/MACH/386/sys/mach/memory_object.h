/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	memory_object.h,v $
 * Revision 2.6  89/03/09  20:21:12  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  18:38:23  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/02/07  00:54:07  mwyoung
 * Relocated from vm/memory_object.h
 * 
 * Revision 2.3  89/01/30  22:08:42  rpd
 * 	Updated includes to the new style.  Fixed log.
 * 	Made variable declarations use "extern".
 * 	[89/01/25  15:25:20  rpd]
 */
/*
 *	File:	memory_object.h
 *	Author:	Michael Wayne Young
 *
 *	External memory management interface definition.
 */

#ifndef	_MACH_MEMORY_OBJECT_H_
#define _MACH_MEMORY_OBJECT_H_

/*
 *	User-visible types used in the external memory
 *	management interface:
 */

#include <mach/port.h>

typedef	port_t		memory_object_t;
					/* Represents a memory object ... */
					/*  Used by user programs to specify */
					/*  the object to map; used by the */
					/*  kernel to retrieve or store data */

typedef	port_t		memory_object_control_t;
					/* Provided to a memory manager; ... */
					/*  used to control a memory object */

typedef	port_t		memory_object_name_t;
					/* Used to describe the memory ... */
					/*  object in vm_regions() calls */

typedef	int		memory_object_copy_strategy_t;
					/* How memory manager handles copy: */
#define		MEMORY_OBJECT_COPY_NONE		0
					/* ... No special support */
#define		MEMORY_OBJECT_COPY_CALL		1
					/* ... Make call on memory manager */
#define		MEMORY_OBJECT_COPY_DELAY 	2
					/* ... Memory manager doesn't ... */
					/*     change data externally. */


#define		MEMORY_OBJECT_NULL	PORT_NULL

/* Obsolete forms of the above names: */
#ifndef	KERNEL
typedef	port_t		paging_object_t;
typedef	port_t		vm_pager_request_t;
typedef	port_t		vm_pager_t;
#define vm_pager_null	((vm_pager_t) 0)
#endif	KERNEL

#ifdef	KERNEL
extern memory_object_t	memory_manager_default;
#endif	KERNEL
#endif	_MACH_MEMORY_OBJECT_H_
