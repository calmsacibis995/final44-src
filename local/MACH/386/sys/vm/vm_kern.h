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
 * $Log:	vm_kern.h,v $
 * Revision 2.8  89/04/18  21:25:51  mwyoung
 * 	No relevant history.
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm/vm_kern.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Kernel memory management definitions.
 */

#ifndef	_VM_VM_KERN_H_
#define _VM_VM_KERN_H_

#include <mach/kern_return.h>
#include <sys/types.h>
#include <vm/vm_map.h>

extern void		kmem_init();
extern vm_offset_t	kmem_alloc();
extern vm_offset_t	kmem_alloc_pageable();
extern void		kmem_free();
extern vm_map_t	kmem_suballoc();

extern kern_return_t	vm_move();

extern vm_offset_t	kmem_alloc_wait();
extern void		kmem_free_wakeup();

extern vm_offset_t	kmem_mb_alloc();

extern vm_map_t	kernel_map;
extern vm_map_t	kernel_pageable_map;
extern vm_map_t	user_pt_map;
extern vm_map_t	mb_map;

extern vm_offset_t	vm_kern_zero_page;	/* A page full of nothing */

#endif	_VM_VM_KERN_H_
