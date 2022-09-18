/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	std_types.h,v $
 * Revision 2.4  89/03/09  20:23:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:40:23  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/15  16:31:59  rpd
 * 	Moved from kern/ to mach/.
 * 	[89/01/15  14:34:14  rpd]
 * 
 * Revision 2.2  89/01/12  07:59:07  rpd
 * 	Created.
 * 	[89/01/12  04:15:40  rpd]
 * 
 */
/*
 *	Mach standard external interface type definitions.
 *
 */

#ifndef	_MACH_STD_TYPES_H_
#define _MACH_STD_TYPES_H_

#define EXPORT_BOOLEAN

#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/machine/vm_types.h>


typedef	vm_offset_t	pointer_t;

#endif	_MACH_STD_TYPES_H_
