/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	stack.h,v $
 * Revision 2.2  93/11/17  19:06:19  dbg
 * 	Moved prototypes here from kern/sched_prim.h.
 * 	[93/10/21            dbg]
 * 
 */

/*
 *	Kernel stack manipulation routines.
 */

#ifndef	_KERN_STACK_H_
#define	_KERN_STACK_H_

#include <mach_debug.h>

#include <mach/boolean.h>
#include <mach/machine/vm_types.h>
#include <kern/kern_types.h>

/*
 *	These functions are either defined in kern/thread.c
 *	via machine-dependent stack_attach and stack_detach functions,
 *	or are defined directly by machine-dependent code.
 */

extern void	stack_alloc(
	thread_t	thread,
	no_return	(*resume)(thread_t));
extern boolean_t stack_alloc_try(
	thread_t	thread,
	no_return	(*resume)(thread_t));
extern void	stack_free(
	thread_t	thread);
extern void	stack_privilege(
	thread_t	thread);
extern void	stack_collect(void);

/*
 *	These routines are called by machine-independent
 *	stack allocation code.  They may (but are not
 *	required to be) called by machine-dependent stack
 *	allocation routines.
 */
extern void stack_attach(
	thread_t	thread,
	vm_offset_t	stack,
	no_return	(*resume)(thread_t));

extern vm_offset_t stack_detach(
	thread_t	thread);


#if	MACH_DEBUG
/*
 *	Stack statistics routines.
 */
extern void	stack_init(
	vm_offset_t	stack);
extern void	stack_finalize(
	vm_offset_t	stack);
extern vm_size_t stack_usage(
	vm_offset_t	stack);
extern void	stack_statistics(
	unsigned int	*totalp,
	vm_size_t	*maxusagep);

#endif	/* MACH_DEBUG */



#endif	/* _KERN_STACK_H_ */

