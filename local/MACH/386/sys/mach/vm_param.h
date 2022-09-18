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
 * $Log:	vm_param.h,v $
 * Revision 2.5  89/05/20  11:16:42  mrt
 * 	Moved non-kernel round_page and trunc_page  macros from here to
 * 	mach_init.h
 * 	[89/05/19            mrt]
 * 
 * Revision 2.4  89/03/09  20:25:19  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:42:23  gm0w
 * 	Changes for cleanup.
 * 
 * 15-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Coalesced includes, documented use of PAGE_SIZE and PAGE_SHIFT.
 *
 * 15-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed include of <mach_init.h> before non-kernel definitions
 *	of trunc/round page macros.  When this is included, it makes it
 *	impossible for user programs to include system header files to
 *	retrieve kernel data structures.  (For example, the user level
 *	mach_init will cause a task to be a port, making it impossible
 *	to get the real kernel definition of a task).
 *
 *  7-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added non-KERNEL definitions of round_page, trunc_page.
 *
 * 21-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added page_mask.  Changed types of page_size and page_mask
 *	to vm_size_t.
 *
 *  9-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	mach/vm_param.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Machine independent virtual memory parameters.
 *
 */

#ifndef	_MACH_VM_PARAM_H_
#define _MACH_VM_PARAM_H_

#include <mach/machine/vm_param.h>
#include <mach/machine/vm_types.h>

/*
 *	The machine independent pages are refered to as PAGES.  A page
 *	is some number of hardware pages, depending on the target machine.
 */

/*
 *	All references to the size of a page should be done with PAGE_SIZE
 *	or PAGE_SHIFT.  The fact they are variables is hidden here so that
 *	we can easily make them constant if we so desire.
 */

#define PAGE_SIZE	page_size	/* size of page in addressible units */
#define PAGE_SHIFT	page_shift	/* number of bits to shift for pages */

#ifndef	ASSEMBLER
/*
 *	Convert addresses to pages and vice versa.
 *	No rounding is used.
 */

#ifdef	KERNEL
#define atop(x)		(((unsigned)(x)) >> page_shift)
#define ptoa(x)		((vm_offset_t)((x) << page_shift))
#endif	KERNEL

/*
 *	Round off or truncate to the nearest page.  These will work
 *	for either addresses or counts.  (i.e. 1 byte rounds to 1 page
 *	bytes.
 */

#ifdef	KERNEL
#define round_page(x)	((vm_offset_t)((((vm_offset_t)(x)) + page_mask) & ~page_mask))
#define trunc_page(x)	((vm_offset_t)(((vm_offset_t)(x)) & ~page_mask))
#endif	KERNEL


#ifdef	KERNEL
extern vm_size_t	page_size;	/* machine independent page size */
extern vm_size_t	page_mask;	/* page_size - 1; mask for
						   offset within page */
extern int		page_shift;	/* shift to use for page size */

extern vm_size_t	mem_size;	/* size of physical memory (bytes) */
extern vm_offset_t	first_addr;	/* first physical page */
extern vm_offset_t	last_addr;	/* last physical page */
#endif	KERNEL

#endif	ASSEMBLER
#endif	_MACH_VM_PARAM_H_
