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
 * $Log:	mach_user_internal.c,v $
 * Revision 2.7  90/07/03  16:38:00  mrt
 * 	Add memory_object_data_supply.
 * 	[90/06/20            dlb]
 * 
 * Revision 2.6  89/05/06  02:56:58  rpd
 * 	Include just those routines used, instead of <mach/mach_user.c>.
 * 	[89/05/06  02:41:22  rpd]
 * 
 * Revision 2.5  89/04/09  01:55:35  rpd
 * 	Added MIG_NO_STRINGS.
 * 	[89/04/09  01:50:41  rpd]
 * 
 * Revision 2.4  89/03/09  20:14:02  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:06:18  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/15  16:25:19  rpd
 * 	Updated includes for the new mach/ directory.
 * 	[89/01/15  15:03:54  rpd]
 * 
 */
/*
 *	File:	kern/mach_user_internal.c
 *
 *	Internal form of the mach_user interface, for
 *	use by builtin (kernel-mode) tasks that wish to
 *	use the RPC interface anyway.
 */

#undef	KERNEL
#define MIG_NO_STRINGS	/* tells Mig code to not include strings.h  */
#define _MACH_INIT_	/* tells mach_types.h to not include mach_init.h */
#include <mach/mach_user_internal.h>	/* renames user stubs to _EXTERNAL */

#include <mach/memory_object_data_error.c>
#include <mach/memory_object_data_supply.c>
#include <mach/memory_object_data_provided.c>
#include <mach/memory_object_data_unavailable.c>
#include <mach/memory_object_set_attributes.c>
#include <mach/port_allocate.c>
#include <mach/port_deallocate.c>
#include <mach/port_set_add.c>
#include <mach/port_set_allocate.c>
#include <mach/port_set_backlog.c>
#include <mach/vm_allocate.c>
#include <mach/vm_deallocate.c>
#include <mach/vm_set_default_memory_manager.c>
