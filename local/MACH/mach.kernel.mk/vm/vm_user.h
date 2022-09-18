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
 * $Log:	vm_user.h,v $
 * Revision 2.5  89/04/18  21:31:31  mwyoung
 * 	Reset history.
 * 
 */
/*
 *	File:	vm/vm_user.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Declarations of user-visible virtual address space
 *	management functionality.
 */

#ifndef	_VM_VM_USER_H_
#define _VM_VM_USER_H_

#include <mach/kern_return.h>

extern kern_return_t	vm_allocate();
extern kern_return_t	vm_deallocate();
extern kern_return_t	vm_inherit();
extern kern_return_t	vm_protect();
extern kern_return_t	vm_statistics();
extern kern_return_t	vm_read();
extern kern_return_t	vm_write();
extern kern_return_t	vm_copy();
extern kern_return_t	vm_map();

#endif	_VM_VM_USER_H_
