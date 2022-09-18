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
 * $Log:	pmap.h,v $
 * Revision 2.10  89/09/05  20:46:05  jsb
 * 	Added pmap_phys_to_frame as inverse of pmap_phys_address, for use by
 * 	memory map function in machine-independent pseudo device drivers.
 * 	The correct thing to do, of course, is to change the device driver map
 * 	function spec to return a physical address instead of a frame, but
 * 	this would require changing too many device drivers...
 * 	[89/09/05  16:45:48  jsb]
 * 
 * Revision 2.9  89/08/28  22:40:44  af
 * 	Removed unused and ugly pmap_redzone() from the list of required
 * 	pmap functions.  Made more routines implementable as macros.
 * 	[89/08/05            af]
 * 
 * Revision 2.8  89/04/18  21:24:43  mwyoung
 * 	Recent history [mwyoung]:
 * 	 	Remove pmap_remove_all(), pmap_copy_on_write(), as they're
 * 	 	 no longer required routines.  The machine-independent code
 * 	 	 uses pmap_page_protect() instead.
 * 		Documented interface.  The precise interface specification
 * 		 should be reconstructed from the pmap implementations.
 * 	History condensation:
 * 		Added calls for page locking [mwyoung].
 * 		Added reference bit handling [avie].
 * 		Created [avie].
 * 	[89/04/18            mwyoung]
 * 
 */
/*
 *	File:	vm/pmap.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 *	Machine address mapping definitions -- machine-independent
 *	section.  [For machine-dependent section, see "machine/pmap.h".]
 */

#ifndef	_VM_PMAP_H_
#define _VM_PMAP_H_

#include <machine/pmap.h>
#include <mach/machine/vm_types.h>
#include <mach/boolean.h>

/*
 *	The following is a description of the interface to the
 *	machine-dependent "physical map" data structure.  The module
 *	must provide a "pmap_t" data type that represents the
 *	set of valid virtual-to-physical addresses for one user
 *	address space.  [The kernel address space is represented
 *	by a distinguished "pmap_t".]  The routines described manage
 *	this type, install and update virtual-to-physical mappings,
 *	and perform operations on physical addresses common to
 *	many address spaces.
 */

/*
 *	Routines used for initialization.
 */

extern void		pmap_bootstrap();	/* Initialization,
						 * before running virtual.
						 */
extern void		pmap_init();		/* Initialization,
						 * after kernel runs
						 * in virtual memory.
						 */
extern vm_offset_t	pmap_map();		/* Enter a range of
						 * mappings.
						 */

/*
 *	Routines to manage the physical map data structure.
 */
extern pmap_t		pmap_create();		/* Create a pmap_t. */
#ifndef	pmap_kernel
extern pmap_t		pmap_kernel();		/* Return the kernel's pmap_t. */
#endif	pmap_kernel
extern void		pmap_reference();	/* Gain a reference. */
extern void		pmap_destroy();		/* Release a reference. */

extern void		pmap_enter();		/* Enter a mapping */

/*
 *	Routines that operate on ranges of virtual addresses.
 */
extern void		pmap_remove();		/* Remove mappings. */
extern void		pmap_protect();		/* Change protections. */

/*
 *	Routines to set up hardware state for physical maps to be used.
 */
extern void		pmap_activate();	/* Prepare pmap_t to run
						 * on a given processor.
						 */
extern void		pmap_deactivate();	/* Release pmap_t from
						 * use on processor.
						 */


/*
 *	Routines that operate on physical addresses.
 */
extern void		pmap_page_protect();	/* Restrict access to page. */
extern boolean_t	pmap_valid_page();	/* Is physical address
						 * valid and usable by
						 * machine-independent
						 * VM system?  Used only
						 * at startup.
						 */

/*
 *	Routines to manage reference/modify bits based on
 *	physical addresses, simulating them if not provided
 *	by the hardware.
 */
extern void		pmap_clear_reference();	/* Clear reference bit */
#ifndef	pmap_is_referenced
extern boolean_t	pmap_is_referenced();	/* Return reference bit */
#endif	pmap_is_referenced
extern void		pmap_clear_modify();	/* Clear modify bit */
extern boolean_t	pmap_is_modified();	/* Return modify bit */


/*
 *	Statistics routines
 */
extern void		pmap_statistics();	/* Return statistics */

#ifndef	pmap_resident_count
extern int		pmap_resident_count();
#endif	pmap_resident_count

/*
 *	Sundry required routines
 */
extern vm_offset_t	pmap_extract();		/* Return a virtual-to-physical
						 * mapping, if possible.
						 */
extern boolean_t	pmap_access();		/* Is virtual address valid? */

#ifndef	pmap_update
extern void		pmap_update();		/* Bring maps up to date */
#endif	pmap_update
extern void		pmap_collect();		/* Perform garbage
						 * collection, if any
						 */

extern void		pmap_change_wiring();	/* Specify pageability */

#ifndef	pmap_phys_address
extern vm_offset_t	pmap_phys_address();	/* Transform address
						 * returned by device
						 * driver mapping function
						 * to physical address
						 * known to this module.
						 */
#endif	pmap_phys_address

#ifndef	pmap_phys_to_frame
extern int		pmap_phys_to_frame();	/* Inverse of
						 * pmap_phys_address,
						 * for use by device driver
						 * mapping function in
						 * machine-independent
						 * pseudo-devices.
						 */
#endif	pmap_phys_to_frame

/*
 *	Optional routines
 */
#ifndef	pmap_copy
extern void		pmap_copy();		/* Copy range of
						 * mappings, if desired.
						 */
#endif	pmap_copy


/*
 *	Exported data structures
 */

extern pmap_t	kernel_pmap;			/* The kernel's map */

#endif	_VM_PMAP_H_
