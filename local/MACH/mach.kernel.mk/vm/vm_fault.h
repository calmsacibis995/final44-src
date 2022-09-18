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
 * $Log:	vm_fault.h,v $
 * Revision 2.7  89/10/10  11:11:02  mwyoung
 * 	Eliminate vm_fault_copy_entry().  Add vm_fault_copy().
 * 	[89/07/28            mwyoung]
 * 
 * Revision 2.6  89/04/18  21:25:22  mwyoung
 * 	Reset history.
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm/vm_fault.h
 *
 *	Page fault handling module declarations.
 */

#ifndef	_VM_VM_FAULT_H_
#define _VM_VM_FAULT_H_

#include <mach/kern_return.h>

/*
 *	Page fault handling based on vm_object only.
 */

typedef	int		vm_fault_return_t;
#define VM_FAULT_SUCCESS	0
#define VM_FAULT_RETRY		1
#define VM_FAULT_INTERRUPTED	2
#define VM_FAULT_MEMORY_SHORTAGE 3
#define VM_FAULT_MEMORY_ERROR	4

extern vm_fault_return_t vm_fault_page();

/*
 *	Page fault handling based on vm_map (or entries therein)
 */

extern kern_return_t	vm_fault();
extern void		vm_fault_wire();
extern void		vm_fault_unwire();

extern kern_return_t	vm_fault_copy();	/* Copy pages from
						 * one object to another
						 */

#endif	_VM_VM_FAULT_H_
