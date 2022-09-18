/*
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
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
 * $Log:	vm_param.h,v $
 * Revision 2.5  93/01/14  17:48:50  danner
 * 	Cleanup.
 * 	[92/06/10            pds]
 * 
 * Revision 2.4  91/05/14  17:02:24  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/02/05  17:37:15  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:15:32  mrt]
 * 
 * Revision 2.2  90/10/12  12:35:53  rpd
 * 	Don't allow this to be included twice.
 * 	[90/10/11            rwd]
 * 
 * Revision 2.1  89/08/03  16:01:52  rwd
 * Created.
 * 
 * Revision 2.3  89/02/25  18:42:06  gm0w
 * 	Changes for cleanup.
 * 
 * 16-Jan-87  David Golub (dbg) at Carnegie-Mellon University
 *	Made vax_ptob return 'unsigned' instead of caddr_t.
 *
 * 20-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	vax/vm_param.h
 *	Author:	Avadis Tevanian, Jr.
 *	Date:	1985
 *
 *	VAX machine dependent virtual memory parameters.
 *	Most of the declarations are preceeded by VAX_ (or vax_)
 *	which is OK because only Vax specific code will be using
 *	them.
 */

#ifndef	_MACH_VAX_VM_PARAM_H_
#define	_MACH_VAX_VM_PARAM_H_

#define BYTE_SIZE	8	/* byte size in bits */

#define VAX_PGBYTES	512	/* bytes per vax page */
#define VAX_PGSHIFT	9	/* number of bits to shift for pages */

/*
 *	Convert bytes to pages and convert pages to bytes.
 *	No rounding is used.
 */

#define	vax_btop(x)		(((unsigned)(x)) >> VAX_PGSHIFT)
#define	vax_ptob(x)		(((unsigned)(x)) << VAX_PGSHIFT)

/*
 *	Round off or truncate to the nearest page.  These will work
 *	for either addresses or counts.  (i.e. 1 byte rounds to 1 page
 *	bytes.
 */

#define vax_round_page(x)	((((unsigned)(x)) + VAX_PGBYTES - 1) & \
					~(VAX_PGBYTES-1))
#define vax_trunc_page(x)	(((unsigned)(x)) & ~(VAX_PGBYTES-1))

#define	VM_MIN_ADDRESS	((vm_offset_t) 0)
#define	VM_MAX_ADDRESS	((vm_offset_t) 0x80000000)

#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t) 0x80000000)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t) 0xffffffff)

#define	KERNEL_STACK_SIZE	(8*512)
#define INTSTACK_SIZE		(4*512)		/* interrupt stack size */

/*
 *	Conversion between VAX pages and VM pages
 */

#define trunc_vax_to_vm(p)	(atop(trunc_page(vax_ptob(p))))
#define round_vax_to_vm(p)	(atop(round_page(vax_ptob(p))))
#define vm_to_vax(p)		(vax_btop(ptoa(p)))

#endif	/* _MACH_VAX_VM_PARAM_H_ */
