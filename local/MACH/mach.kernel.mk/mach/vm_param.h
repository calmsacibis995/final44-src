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
 * Revision 2.6  89/10/10  13:36:45  mwyoung
 * 	Use PAGE_SIZE_FIXED to permit PAGE_SIZE (and PAGE_SHIFT) to be
 * 	defined to be constants.
 * 
 * 	Add page_aligned.
 * 
 * 	Prevent this file from being used outside the kernel.  It was a
 * 	serious mistake to ever allow it to be put in the <mach/>
 * 	directory.  This is the first step in returning it to <vm/>.
 * 	[89/10/10            mwyoung]
 * 
 * Revision 2.5  89/05/20  11:16:42  mrt
 * 	Moved non-kernel round_page and trunc_page  macros from here to
 * 	mach_init.h
 * 	[89/05/19            mrt]
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

#ifndef	KERNEL

;YOU HAVE MADE A MISTAKE BY INCLUDING THIS FILE;

THIS FILE SHOULD NOT BE VISIBLE TO USER PROGRAMS.

USE <mach/machine/vm_param.h> TO GET MACHINE-DEPENDENT ADDRESS
SPACE AND PAGE SIZE ITEMS.

USE <mach/machine/vm_types.h> TO GET TYPE DECLARATIONS USED IN
THE MACH KERNEL INTERFACE.

IN ALL PROBABILITY, YOU SHOULD GET ALL OF THE TYPES USED IN THE
INTERFACE FROM <mach/mach_types.h>

#endif	KERNEL

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

/*
 *	Regardless whether it is implemented with a constant or a variable,
 *	the PAGE_SIZE is assumed to be a power of two throughout the
 *	virtual memory system implementation.
 */

#ifndef	PAGE_SIZE_FIXED
#define PAGE_SIZE	page_size	/* size of page in addressible units */
#define PAGE_SHIFT	page_shift	/* number of bits to shift for pages */
#endif	PAGE_SIZE_FIXED

#ifndef	ASSEMBLER
/*
 *	Convert addresses to pages and vice versa.
 *	No rounding is used.
 */

#define atop(x)		(((unsigned)(x)) >> page_shift)
#define ptoa(x)		((vm_offset_t)((x) << page_shift))

/*
 *	Round off or truncate to the nearest page.  These will work
 *	for either addresses or counts.  (i.e. 1 byte rounds to 1 page
 *	bytes.
 */

#define round_page(x)	((vm_offset_t)((((vm_offset_t)(x)) + page_mask) & ~page_mask))
#define trunc_page(x)	((vm_offset_t)(((vm_offset_t)(x)) & ~page_mask))

/*
 *	Determine whether an address is page-aligned, or a count is
 *	an exact page multiple.
 */

#define	page_aligned(x)	((((vm_offset_t) (x)) & page_mask) == 0)

#ifndef	PAGE_SIZE_FIXED
extern vm_size_t	page_size;	/* machine independent page size */
extern vm_size_t	page_mask;	/* page_size - 1; mask for
						   offset within page */
extern int		page_shift;	/* shift to use for page size */
#else	PAGE_SIZE_FIXED
#define	page_mask	(PAGE_SIZE-1)
#endif	PAGE_SIZE_FIXED

extern vm_size_t	mem_size;	/* size of physical memory (bytes) */
extern vm_offset_t	first_addr;	/* first physical page */
extern vm_offset_t	last_addr;	/* last physical page */

#endif	ASSEMBLER
#endif	_MACH_VM_PARAM_H_
