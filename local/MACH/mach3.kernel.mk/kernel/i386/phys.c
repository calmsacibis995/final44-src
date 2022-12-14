/* 
 * Mach Operating System
 * Copyright (c) 1993,1991,1990,1989 Carnegie Mellon University
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
 * $Log:	phys.c,v $
 * Revision 2.9  93/11/17  16:37:48  dbg
 * 	De-linted.  Removed copy_to_phys and copy_from_phys
 * 	(unused).
 * 	[93/09/29            dbg]
 * 
 * Revision 2.8  91/05/18  14:30:02  rpd
 * 	Added vm_page_fictitious_addr assertions.
 * 	[91/04/10            rpd]
 * 
 * Revision 2.7  91/05/14  16:13:29  mrt
 * 	Correcting copyright
 * 
 * Revision 2.6  91/05/08  12:41:06  dbg
 * 	More cleanup.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.5  91/03/16  14:45:06  rpd
 * 	Added resume, continuation arguments to vm_fault.
 * 	[91/02/05            rpd]
 * 
 * Revision 2.4  91/02/05  17:13:36  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:36:36  mrt]
 * 
 * Revision 2.3  90/12/04  14:46:19  jsb
 * 	Changes for merged intel/pmap.{c,h}.
 * 	[90/12/04  11:17:19  jsb]
 * 
 * Revision 2.2  90/05/03  15:35:56  dbg
 * 	Use 'write' bit in pte instead of protection field.
 * 	[90/03/25            dbg]
 * 
 * 	Use bzero instead of bclear.
 * 	[90/02/15            dbg]
 * 
 * Revision 1.3  89/02/26  12:32:59  gm0w
 * 	Changes for cleanup.
 * 
 */
 
#include <mach/boolean.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <vm/vm_map.h>
#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>

#include <i386/pmap.h>
#include <mach/i386/vm_param.h>

#include <kern/memory.h>	/* bcopy, bzero */

/*
 *	kvtophys(addr)
 *
 *	Convert a kernel virtual address to a physical address
 */
vm_offset_t
kvtophys(
	vm_offset_t addr)
{
	pt_entry_t *pte;

	if ((pte = pmap_pte(kernel_pmap, addr)) == PT_ENTRY_NULL)
		return 0;
	return i386_trunc_page(*pte) | (addr & INTEL_OFFMASK);
}

/*
 *	pmap_zero_page zeros the specified (machine independent) page.
 */
void pmap_zero_page(
	vm_offset_t p)
{
	assert(p != vm_page_fictitious_addr);
	bzero((void *) phystokv(p), PAGE_SIZE);
}

/*
 *	pmap_copy_page copies the specified (machine independent) pages.
 */
void pmap_copy_page(
	vm_offset_t src,
	vm_offset_t dst)
{
	assert(src != vm_page_fictitious_addr);
	assert(dst != vm_page_fictitious_addr);

	bcopy((void *) phystokv(src), (void *) phystokv(dst), PAGE_SIZE);
}

