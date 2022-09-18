/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_machdep.c,v $
 * Revision 1.3  89/02/26  12:35:05  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)vm_machdep.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <vm/pmap.h>



/*
 * Move pages from one kernel virtual address to another.
 * Both addresses are assumed to reside in the Sysmap,
 * and size must be a multiple of the page size.
 */
pagemove(from, to, size)
	register caddr_t from, to;
	int size;
{
	register pt_entry_t *fpte, *tpte;

	if (size % I386_PGBYTES)
		panic("pagemove");
	while (size > 0) {
		fpte = pmap_pte(kernel_pmap, from);
		tpte = pmap_pte(kernel_pmap, to);
		*tpte++ = *fpte;
		*(int *)fpte++ = 0;
		from += I386_PGBYTES;
		to += I386_PGBYTES;
		size -= I386_PGBYTES;
	}
	set_cr3(get_cr3());
}
