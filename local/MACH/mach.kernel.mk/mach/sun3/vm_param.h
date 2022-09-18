/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_param.h,v $
 * Revision 2.5  89/03/09  20:23:48  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:40:56  gm0w
 * 	Changes for cleanup.
 * 
 * 05-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added sun_trunc_page, fixed up includes.
 *
 * 23-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Don't allocate VM over the PROM monitor.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Define INTSTACK_SIZE.
 *
 * 23-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added KERNEL_STACK_SIZE in anticipation of MACH.
 *
 *  4-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Created.
 *
 */

#ifndef	_MACH_SUN3_VM_PARAM_H_
#define _MACH_SUN3_VM_PARAM_H_

#define BYTE_SIZE	8	/* byte size in bits */

#define SUN3_PGBYTES	8192	/* bytes per sun3 page */
#define SUN3_PGSHIFT	13	/* number of bits to shift for pages */

/*
 * KERNELBASE is the virtual address which
 * the kernel mapping starts in all contexts.
 */
#define KERNELBASE	0x0E000000

#define VM_MIN_ADDRESS	((vm_offset_t)0)
#define VM_MAX_ADDRESS	((vm_offset_t)KERNELBASE)

/*
 * The value of VM_MAX_KERNEL_ADDRESS should equal
 * MONSTART, defined in <mon/sunromvec.h>.
 */
#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t)KERNELBASE)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t)0x0FE00000)

#define sun_round_page(x) (((unsigned)(x)+SUN3_PGBYTES-1) & ~(SUN3_PGBYTES-1))
#define sun_trunc_page(x) ((unsigned)(x) & ~(SUN3_PGBYTES-1))

#define KERNEL_STACK_SIZE	(SUN3_PGBYTES)	/* must be at least one page */
#define INTSTACK_SIZE		(3*512)

#endif	_MACH_SUN3_VM_PARAM_H_
