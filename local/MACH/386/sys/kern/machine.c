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
 * $Log:	machine.c,v $
 * Revision 2.7  89/02/25  18:06:25  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/01/31  17:25:15  rpd
 * 	Changed printf_cpu_number to new_printf_cpu_number,
 * 	to agree with bsd/{kern_xxx,subr_prf}.c.
 * 
 * Revision 2.5  88/12/19  02:46:04  mwyoung
 * 	Remove lint.
 * 	[88/12/17            mwyoung]
 * 
 * Revision 2.4  88/11/21  16:56:31  rvb
 * 	Only set printf_cpu_number if NCPU > 1 and machine_info.avail_cpus > 1
 * 	[88/11/09            rvb]
 * 
 * Revision 2.3  88/08/09  18:00:19  rvb
 * Use cpu_control() to actually control processors.
 *
 * 24-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Maintain cpu state in cpu_up and cpu_down.
 *
 * 15-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 17-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	Bug fix to cpu_down - update slot structure correctly.
 *
 * 28-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	kern/machine.c
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1987, Avadis Tevanian, Jr.
 *
 *	Support for machine independent machine abstraction.
 */

#include <cpus.h>

#include <mach/kern_return.h>
#include <mach/boolean.h>
#include <mach/machine.h>
#include <kern/task.h>
#include <kern/sched.h>

/*
 *	Exported variables:
 */

struct machine_info	machine_info;
struct machine_slot	machine_slot[NCPUS];

/*XXX These should be somewhere else */
boolean_t		should_exit[NCPUS];
vm_offset_t		interrupt_stack[NCPUS];

/*
 *	host_info:
 *
 *	Return the host_info structure.  This routine is exported to the
 *	user level.
 */
kern_return_t host_info(task, info)
	task_t		task;
	machine_info_t	info;
{
#ifdef	lint
	task++;
#endif	lint
	*info = machine_info;
	return(KERN_SUCCESS);
}

/*
 *	slot_info:
 *
 *	Return the slot_info structure for the specified slot.  This routine
 *	is exported to the user level.
 */
kern_return_t slot_info(task, slot, info)
	task_t		task;
	int		slot;
	machine_slot_t	info;
{
#ifdef	lint
	task++;
#endif	lint
	if ((slot < 0) || (slot >= NCPUS))
		return(KERN_INVALID_ARGUMENT);
	*info = machine_slot[slot];
	return(KERN_SUCCESS);
}

/*
 *	cpu_control:
 *
 *	Support for user control of cpus.  The user indicates which cpu
 *	he is interested in, and whether or not that cpu should be running.
 *
 *	NOT IMPLEMENTED PENDING A MECHANISM TO GIVE ACCESS TO ONLY PRIVILEGED
 *	TASKS.
 */
kern_return_t cpu_control(task, cpu, runnable)
	task_t		task;
	int		cpu;
	boolean_t	runnable;
{
#if	NCPUS > 1
	boolean_t	ret;
#endif	NCPUS > 1
#ifdef	lint
	task++; cpu++; runnable++;
#endif	lint

#if	NCPUS > 1
/*	if (!suser())
		return(KERN_FAILURE);*/

	if (cpu == -1) {
		start_processors(0);
		return KERN_SUCCESS;
	}

	switch (runnable) {
	extern int freeze_control;
	case 6:
		move_console(cpu);
		ret = TRUE;
		break;
	case 5:
		ret = freeze_processor(cpu);
		break;
	case 4:
		freeze_control &= ~(1<<cpu);
		ret = TRUE;
		break;
	case 3:
		ret = halt_processor(cpu);
		break;
	case 2:
		ret = continue_processor(cpu);
		break;
	case 1:
		ret = start_processor(cpu);
		break;
	case 0:
		ret = exit_processor(cpu);
		break;
	default:
		return(KERN_INVALID_ARGUMENT);
	}
	if (ret)
		return(KERN_SUCCESS);
	else
		return(KERN_FAILURE);

#else	NCPUS > 1
	return(KERN_FAILURE);	/* for now */
#endif	NCPUS > 1
}

/*
 *	cpu_up:
 *
 *	Flag specified cpu as up and running.  Called when a processor comes
 *	online.
 *	XXX - no locking.
 */
#if	NCPUS > 1
extern int new_printf_cpu_number;
#endif	NCPUS > 1
cpu_up(cpu)
	int	cpu;
{
	register struct machine_slot	*ms;

	ms = &machine_slot[cpu];
	ms->running = TRUE;
	machine_info.avail_cpus++;
#if	NCPUS > 1
	if (machine_info.avail_cpus > 1)
		new_printf_cpu_number = 1;
#endif	NCPUS > 1
	cpu_state(cpu) = CPU_RUNNING;
	quantum_set();			/* Recompute quantum values */
}

/*
 *	cpu_down:
 *
 *	Flag specified cpu as down.  Called when a processors is about to
 *	go offline.
 *	XXX - no locking.
 */
cpu_down(cpu)
	int	cpu;
{
	register struct machine_slot	*ms;

	ms = &machine_slot[cpu];
	ms->running = FALSE;
	machine_info.avail_cpus--;
#if	NCPUS > 1
	if (machine_info.avail_cpus > 1)
		new_printf_cpu_number = 1;
#endif	NCPUS > 1
	cpu_state(cpu) = CPU_OFF_LINE;
	quantum_set();			/* Recompute quantum values */
}
