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
 * $Log:	callout_statistics.c,v $
 * Revision 2.7  89/10/11  14:01:29  dlb
 * 	New calling sequence for vm_map_pageable.
 * 	[89/09/01  17:18:58  dlb]
 * 
 * Revision 2.6  89/10/10  10:50:15  mwyoung
 * 	Use vm_map_copyin().
 * 	[89/06/08  18:18:51  mwyoung]
 * 
 * Revision 2.5  89/03/09  20:10:56  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:00:15  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/01/12  07:43:55  rpd
 * 	Updated for new MACH_DEBUG, MACH_CO_INFO, renamed MACH_CO_STATS options,
 * 	and new location of callout_statistics.h in mach_debug/.
 * 	[89/01/12  04:39:48  rpd]
 * 
 * Revision 2.2  88/09/25  22:08:48  rpd
 * 	Updated vm_move calls.
 * 	[88/09/24  17:41:54  rpd]
 * 	
 * 	Added callout_statistics_fudge variable.
 * 	[88/09/12  23:00:47  rpd]
 * 	
 * 	host_callout_info no longer returns a dummy record at the beginning.
 * 	host_callout_statistics_reset no longer resets cos_current_size.
 * 	[88/09/10  01:18:35  rpd]
 * 	
 * 	Implemented host_callout_info.
 * 	[88/09/09  22:45:58  rpd]
 * 	
 * 	Created.
 * 	[88/09/09  04:50:24  rpd]
 * 
 */
/*
 * File:	callout_statistics.c
 * Purpose:
 *	Code for call-out statistics gathering.
 */

#include <mach_debug.h>
#include <mach_co_info.h>
#include <mach_co_stats.h>

#include <mach/kern_return.h>
#include <mach/vm_param.h>
#include <kern/task.h>
#include <kern/lock.h>
#include <sys/callout.h>
#include <machine/machparam.h>		/* for splhigh */
#include <vm/vm_map.h>
#include <mach/vm_prot.h>
#include <kern/ipc_globals.h>
#include <mach_debug/callout_statistics.h>
#include <vm/vm_kern.h>

#if	MACH_DEBUG && MACH_CO_INFO
/*
 *	Routine:	host_callout_info [exported, user]
 *	Purpose:
 *		Return the contents of the call-out queue.
 */
kern_return_t
host_callout_info(target_task, infoArray, infoCnt)
	task_t target_task;
	callout_info_array_t *infoArray;
	unsigned int *infoCnt;
{
	unsigned int actual;	/* this many queue elements */
	unsigned int space;	/* space for this many elements */

	vm_size_t size;
	vm_offset_t addr;

#ifdef	lint
	target_task++;
#endif	lint

	/* initial guess for amount of memory to allocate */
	size = page_size;

	for (;;) {
		register callout_info_t *info;
		register struct callout *event;
		int s;

		/* allocate memory non-pageable, so don't fault
		   while holding locks */
		(void) vm_allocate(ipc_kernel_map, &addr, size, TRUE);
		(void) vm_map_pageable(ipc_kernel_map, addr, addr + size,
				VM_PROT_READ|VM_PROT_WRITE);

		info = (callout_info_t *) addr;
		space = size / sizeof(callout_info_t);
		actual = 0;

		s = splhigh();
		simple_lock(&callout_lock);

		for (event = calltodo.c_next;
		     (actual < space) && (event != 0);
		     actual++, event = event->c_next) {
			info[actual].coi_time = event->c_time;
			info[actual].coi_arg = event->c_arg;
			info[actual].coi_func = event->c_func;
		}

		simple_unlock(&callout_lock);
		splx(s);

		if (event == 0)
			break;

		/* free current memory block */
		(void) kmem_free(ipc_kernel_map, addr, size);

		/* go for another try, allowing for expansion */
		size = round_page(2 * actual * sizeof(callout_info_t));
	}

	if (actual == 0) {
		/* no members, so return null pointer and deallocate memory */
		*infoArray = 0;
		*infoCnt = 0;

		(void) kmem_free(ipc_kernel_map, addr, size);
	} else {
		vm_size_t size_used;
		vm_map_copy_t copied_in_info;

		*infoCnt = actual;

		size_used = round_page(actual * sizeof(callout_info_t));

		/* finished touching it, so make the memory pageable */
		(void) vm_map_pageable(ipc_kernel_map,
				       addr, addr + size_used, VM_PROT_NONE);

		/* the memory needs to be in copied-in form */
		(void) vm_map_copyin(ipc_kernel_map, addr, size_used, TRUE,
				&copied_in_info);
		*infoArray = (callout_info_array_t) copied_in_info;

		/* free any unused memory */
		if (size_used != size)
			kmem_free(
				ipc_kernel_map,
				addr + size_used,
				size - size_used);
	}

	return KERN_SUCCESS;
}
#endif	MACH_DEBUG && MACH_CO_INFO

#if	MACH_CO_STATS
callout_statistics_t callout_statistics;
int callout_statistics_fudge;

#if	MACH_DEBUG
/*
 *	Routine:	host_callout_statistics [exported, user]
 *	Purpose:
 *		Return the accumulated call-out statistics.
 */
kern_return_t
host_callout_statistics(target_task, statistics)
	task_t target_task;
	callout_statistics_t *statistics;
{
	register int s;

	s = splhigh();
	simple_lock(&callout_lock);

	*statistics = callout_statistics;

	simple_unlock(&callout_lock);
	splx(s);

	return KERN_SUCCESS;
}

/*
 *	Routine:	host_callout_statistics_reset [exported, user]
 *	Purpose:
 *		Reset the accumulated call-out statistics.
 */
kern_return_t
host_callout_statistics_reset(target_task)
	task_t target_task;
{
	register int s;

	s = splhigh();
	simple_lock(&callout_lock);

	callout_statistics_fudge = -callout_statistics.cos_current_size;
	callout_statistics.cos_num_timeout = 0;
	callout_statistics.cos_cum_timeout_size = 0;
	callout_statistics.cos_cum_timeout_pos = 0;

	callout_statistics.cos_num_untimeout = 0;
	callout_statistics.cos_num_untimeout_hit = 0;
	callout_statistics.cos_cum_untimeout_size = 0;
	callout_statistics.cos_cum_untimeout_pos = 0;

	callout_statistics.cos_num_softclock = 0;
	callout_statistics.cos_cum_softclock_size = 0;

	simple_unlock(&callout_lock);
	splx(s);

	return KERN_SUCCESS;
}
#endif	MACH_DEBUG
#endif	MACH_CO_STATS
