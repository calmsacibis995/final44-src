/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	phys.c,v $
 * Revision 1.3.1.1  90/03/12  11:17:19  rvb
 * 	Corrected userwrite and moved it to pmap.c
 * 	[90/03/12            rvb]
 * 
 * Revision 1.3  89/02/26  12:32:59  gm0w
 * 	Changes for cleanup.
 * 
 */
 
#include <mach/boolean.h>
#include <sys/errno.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <sys/types.h>
#include <vm/vm_map.h>
#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <vm/vm_kern.h>

#include <i386/cpu.h>
#include <i386/pmap.h>
#include <mach/i386/vm_param.h>

/*
 *	pmap_zero_page zeros the specified (machine independent) page.
 */
pmap_zero_page(p)
	vm_offset_t p;
{

	bclear(phystokv(p), PAGE_SIZE);
	return;
}

/*
 *	pmap_copy_page copies the specified (machine independent) pages.
 */
pmap_copy_page(src, dst)
	vm_offset_t src, dst;
{

	bcopy(phystokv(src), phystokv(dst), PAGE_SIZE);
	return;
}

/*
 *	copy_to_phys(src_addr_v, dst_addr_p, count)
 *
 *	Copy virtual memory to physical memory
 */
copy_to_phys(src_addr_v, dst_addr_p, count)
	vm_offset_t src_addr_v, dst_addr_p;
	int count;
{

	bcopy(src_addr_v, phystokv(dst_addr_p), count);
	return;
}

/*
 *	copy_from_phys(src_addr_p, dst_addr_v, count)
 *
 *	Copy physical memory to virtual memory.  The virtual memory
 *	is assumed to be present (e.g. the buffer pool).
 */
copy_from_phys(src_addr_p, dst_addr_v, count)
	vm_offset_t src_addr_p, dst_addr_v;
	int count;
{

	bcopy(phystokv(src_addr_p), dst_addr_v, count);
	return;
}

/*
 *	kvtophys(addr)
 *
 *	Convert a kernel virtual address to a physical address
 */
kvtophys(addr)
vm_offset_t addr;
{
	pt_entry_t *pte;

	if ((pte = pmap_pte(kernel_pmap, addr)) == PT_ENTRY_NULL)
		return(0);
	return(i386_trunc_page(*(int *)pte) | (addr & I386_OFFMASK));
}
