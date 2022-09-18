/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	qbus.c,v $
 * Revision 2.2  91/06/19  12:01:37  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:50:15  rvb]
 * 
 * Revision 2.1  89/08/03  16:38:19  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 * Routines common to Microvaxes.
 *
 * Assumptions:
 *
 *	All Microvaxen have a Qbus.
 *	All Microvaxen may have a QDSS or QVSS console.
 */
#include <platforms.h>
#include <qd.h>
#include <qv.h>

#if VAX630 || VAX650

#include <vm/vm_kern.h>
#include <mach/vm_param.h>

#include <vax/cpu_data.h>
#include <vax/io_map.h>

#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

qbus_map()
{
	register struct uba_hd *uhp;

	vm_offset_t	qb_mem_space,
			qb_io_space,
			qb_map_space;

	/*
	 * Map the various pieces of the Qbus.
	 */
	qb_mem_space	= io_map((vm_offset_t)QMEM630,
				 QBAPAGES * VAX_PGBYTES);
	qb_io_space	= io_map((vm_offset_t)QIOPAGE630,
				 UBAIOPAGES * VAX_PGBYTES);
	qb_map_space	= io_map((vm_offset_t)QBAMAP630,
				 QBAPAGES * sizeof(struct pte));

	/*
	 * Set up the Qbus as 'unibus' 0.
	 */
	unibus_start[0]	= qb_mem_space;
	unibus_end[0]	= qb_io_space + UBAIOPAGES * VAX_PGBYTES;

	uhp = &uba_hd[0];

	uhp->uh_type	= QBA;
	uhp->uh_uba	= (struct uba_regs *)0xc0000000; /* no adaptor regs */
	uhp->uh_mr	= (struct pte *)qb_map_space;
	uhp->uh_physuba	= (struct uba_regs *)(QBAMAP630 - 0x800);
	uhp->uh_memsize	= QBAPAGES * VAX_PGBYTES;
	uhp->uh_mem	= (caddr_t)qb_mem_space;
	uhp->uh_iopage	= (caddr_t)qb_io_space;

}

#endif	VAX630 || VAX650
