/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	io_map.c,v $
 * Revision 2.1  89/08/03  16:29:19  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	VM routines for hardware initialization.  Run with mapping
 *	enabled, but MACH VM not set up.
 */

#include <mach/vm_param.h>

#include <vax/mtpr.h>
#include <vax/pmap.h>
#include <vax/scb.h>

extern vm_offset_t	avail_start;	/* first available physical address */
extern vm_offset_t	avail_end;	/* end of physical memory */
extern vm_offset_t	virtual_avail;	/* first available virtual address */
extern vm_offset_t	virtual_end;	/* end of virtual memory */

extern pt_entry_t	*vax_vsbr;

#define	pmap_syspte(va)	(&vax_vsbr[vax_btop((va) - VM_MIN_KERNEL_ADDRESS)])

/*
 *	Allocate virtual memory, and map physical memory (usually
 *	in IO space) to it.
 */
vm_offset_t
io_map(phys_addr, size)
	vm_offset_t		phys_addr;
	register vm_size_t	size;
{
	register pt_entry_t	*pte;
	register int		template;
	vm_offset_t		start;

	size = vax_round_page(size);

	start = virtual_avail;
	pte = pmap_syspte(virtual_avail);

	template = VAX_PTE_VALID | VAX_PTE_KW | vax_btop(phys_addr);

	while (size != 0) {
	    *(int *)pte++ = template++;
	    size -= VAX_PGBYTES;
	    virtual_avail += VAX_PGBYTES;
	}
	return (start);
}

/*
 *	Deallocate virtual memory that was mapped by the last io_map
 *	call.
 */
void
io_unmap(addr, size)
	vm_offset_t		addr;
	register vm_size_t	size;
{
	register pt_entry_t	*pte;

	size = vax_round_page(size);

	if (addr + size != virtual_avail)
	    panic("io_unmap");

	pte = pmap_syspte(virtual_avail);

	while (size != 0) {
	    size -= VAX_PGBYTES;
	    virtual_avail -= VAX_PGBYTES;
	    *(int *)--pte = 0;
	    mtpr(TBIS, (int)virtual_avail);
	}
}

/*
 *	Fix up the virtual address space when all io_map calls are done.
 */
void
io_map_done()
{
	virtual_avail = round_page(virtual_avail);
}

/*
 *	Map memory for IO.
 */
void
ioaccess(phys_addr, virt_addr, size)
	vm_offset_t		phys_addr, virt_addr;
	register vm_size_t	size;
{
	register pt_entry_t	*pte;
	register int		template;

	pte = pmap_syspte(virt_addr);
	template = VAX_PTE_VALID | VAX_PTE_KW | vax_btop(phys_addr);

	while (size != 0) {
	    *(int *)pte++ = template++;
	    size -= VAX_PGBYTES;
	}
	mtpr(TBIA, 0);
}

/*
 * Write-protect SCB.
 */
void
scb_write_protect()
{
	register pt_entry_t *	pte;
	register int		size;

	pte = pmap_syspte((vm_offset_t)&scb);
	size = vax_btop((vm_offset_t)&scb_end - (vm_offset_t)&scb);

	while (size > 0) {
	    *(int *)pte = (*(int *)pte & VAX_PTE_PFN)
			| VAX_PTE_VALID | VAX_PTE_KR;

	    pte++;
	    size--;
	}
	mtpr(TBIA, 0);
}
