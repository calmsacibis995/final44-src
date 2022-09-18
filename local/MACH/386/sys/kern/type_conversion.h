/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	type_conversion.h,v $
 * Revision 2.2  89/05/21  22:29:43  mrt
 * 	Created by moving the kernel-only definitions out of
 * 	mach_types.h.
 * 	[89/05/18            mrt]
 * 
 */
#ifndef	_KERN_TYPE_CONVERSION_H_
#define	_KERN_TYPE_CONVERSION_H_

#include <mach/port.h>
#include <kern/task.h> 
#include <kern/thread.h>
#include <vm/vm_map.h>


/*
 *	Conversion routines, to let Matchmaker do this for
 *	us automagically.
 */

extern task_t convert_port_to_task( /* port_t x */ );
extern thread_t convert_port_to_thread( /* port_t x */ );
extern vm_map_t convert_port_to_map( /* port_t x */ );
extern port_t convert_task_to_port( /* task_t x */ );
extern port_t convert_thread_to_port( /* thread_t x */ );

#endif	_KERN_TYPE_CONVERSION_H_
