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
 * $Log:	mach_redefines.h,v $
 * Revision 2.6  90/07/03  16:37:56  mrt
 * 	Remove XP conditionals and !XP vm_allocate_with_pager.
 * 	Remove pager_cache redefine.
 * 	[90/06/28            dlb]
 * 
 * Revision 2.5  89/03/09  20:13:56  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:06:11  gm0w
 * 	Kernel code cleanup.
 * 	Put entire file under #indef KERNEL.
 * 	[89/02/15            mrt]
 * 
 *  2-Jul-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Include "vm/vm_pager.h" to get types for
 *	vm_allocate_with_pager's dummy.
 *
 * 16-Feb-88  David Golub (dbg) at Carnegie-Mellon University
 *	Undefine vm_allocate_with_pager if not running XP system.
 *
 * 21-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Created.  Temporary file to disable task_create and
 *	task_terminate until they can operate independently
 *	of BSD code.
 */

#ifndef	_KERN_MACH_REDEFINES_H_
#define _KERN_MACH_REDEFINES_H_

#define task_create	task_create_not_implemented
/*ARGSUSED*/
kern_return_t task_create(parent_task, inherit_memory, child_task)
	task_t		parent_task;
	boolean_t	inherit_memory;
	task_t		*child_task;
{
	uprintf("task_create is not implemented yet\n");
	return(KERN_FAILURE);
}

#define task_terminate	task_terminate_not_implemented
/*ARGSUSED*/
kern_return_t task_terminate(task)
	task_t		task;
{
	uprintf("task_terminate is not implemented yet\n");
	return(KERN_FAILURE);
}

#endif	_KERN_MACH_REDEFINES_H_
