/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
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
 * $Log:	machine.h,v $
 * Revision 2.2  93/11/17  19:07:23  dbg
 * 	Created.
 * 	[93/11/03            dbg]
 * 
 */

/*
 *	Routines to control CPUS, exported from
 *	kern/machine.c and machine-dependent files.
 */

#ifndef	_KERN_MACHINE_H_
#define	_KERN_MACHINE_H_

#include <cpus.h>

#include <mach/boolean.h>
#include <mach/host_info.h>
#include <mach/kern_return.h>
#include <mach/machine.h>
#include <mach/processor_info.h>

#include <kern/host.h>
#include <kern/kern_types.h>

/*
 *	Machine-independent data structures and routines:
 */

extern struct machine_info	machine_info;
extern struct machine_slot	machine_slot[NCPUS];

extern void
cpu_up(
	int	cpu);

extern void
cpu_down(
	int	cpu);

extern kern_return_t
host_reboot(
	host_t	host,
	int	options);

extern kern_return_t
host_get_boot_info(
	host_t			priv_host,
	kernel_boot_info_t	boot_info);

extern kern_return_t
processor_assign(
	processor_t	processor,
	processor_set_t new_pset,
	boolean_t	wait);

extern kern_return_t
processor_shutdown(
	processor_t	processor);

#if	NCPUS > 1
extern void action_thread_init(void);
extern no_return action_thread(void);
#endif

/*
 *	Machine-dependent routines
 */
extern void
machine_init(void);

extern no_return
halt_cpu(void);

extern void
halt_all_cpus(
	boolean_t	reboot);

#if	NCPUS > 1
extern void
switch_to_shutdown_context(
	thread_t	thread,
	no_return	(*shutdown)(processor_t),
	processor_t	processor);

extern kern_return_t
cpu_start(int processor_number);

extern kern_return_t
cpu_control(
	int		processor_number,
	processor_info_t info,
	natural_t	count);

extern void
start_other_cpus(void);

extern void
slave_machine_init(void);
#endif	/* NCPUS > 1 */

#endif	/* _KERN_MACHINE_H_ */
