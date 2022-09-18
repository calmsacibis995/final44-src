/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kdb_print.h,v $
 * Revision 2.7.2.1  90/05/14  13:21:43  rvb
 * 	Fix typo add a break after 'k case
 * 	[90/05/10            rvb]
 * 
 * Revision 2.7  89/03/09  20:13:09  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  18:04:50  gm0w
 * 	Kernel code cleanup.	
 * 	Put entire file under #ifdef KERNEL
 * 	[89/02/15            mrt]
 * 
 * Revision 2.5  88/12/19  02:45:52  mwyoung
 * 	Remove lint.
 * 	[88/12/09            mwyoung]
 * 	
 * 	Add more printing functions.
 * 	[88/12/05            mwyoung]
 * 
 * Revision 2.4  88/10/26  05:35:11  mwyoung
 * 	In print_thread, split up the printing of the state flags into
 * 	separate printf's, as the RT/PC's kdbprintf only accepts three
 * 	arguments.  [Once we're splitting it up, why go half way?]
 * 	
 * 	Move 'k' here.
 * 	[88/10/26            mwyoung]
 * 
 * Revision 2.3  88/10/25  04:12:52  mwyoung
 * 	Don't include <sys/user.h>, as it can't be multiply included.
 * 	[88/10/25            mwyoung]
 * 
 * Revision 2.2  88/10/25  03:46:03  mwyoung
 * 	Created.
 * 	[88/10/24            mwyoung]
 * 
 */
/*
 *	File:	kern/kdb_print.h
 *
 *	Machine-independent printing routines for KDB.
 *
 *	Because of routine name remappings, this file should not
 *	be compiled directly, but should instead be included by
 *	another KDB source file.
 */

#ifndef	_KERN_KDB_PRINT_H_
#define _KERN_KDB_PRINT_H_

#include <mach/time_value.h>
#include <mach/boolean.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <kern/queue.h>

extern	print_stack_trace();

print_thread(thread)
	thread_t	thread;
{
	time_value_t	user_time;
	time_value_t	system_time;

	printf(" %c", (thread->state & TH_RUN)  ? 'R' : ' ');
	printf( "%c", (thread->state & TH_WAIT) ? 'W' : ' ');
	printf( "%c", (thread->state & TH_SUSP) ? 'S' : ' ');
	printf( "%c", (!thread->interruptible)  ? 'N' : ' ');
	printf( "%s", (thread->state & TH_SWAPPED)
						? "(swapped)" : "");

	if (thread->state & TH_WAIT ) {
		printf(" ");
		psymoff((long)thread->wait_event, ISYM, "");
	}
	else {
		thread_read_times(thread, &user_time, &system_time);
		printf(" pri = %D, %Du %Ds %Dc",
			thread->sched_pri,
			user_time.seconds,
			system_time.seconds,
			thread->cpu_usage);
	}

	printf("\n");
}

print_task_long(task, thread_print_routine)
	task_t		task;
	int		(*thread_print_routine)();
{
	thread_t	thread;

	printf("task 0x%X [%-20.20s]: ", task,
#ifdef	u_comm
		task->u_address ? task->u_address->uu_comm : ""
#else	u_comm
		""
#endif	u_comm
		);
	if (task->thread_count == 0) {
		printf("no threads\n");
	}
	else if (task->thread_count > 1) {
		printf("%d threads:\n",
				task->thread_count);
	}
	thread = (thread_t) queue_first(
			&task->thread_list);
	while (!queue_end(&task->thread_list, (queue_entry_t) thread)) {
		printf("thread 0x%X ", thread);
		(void) thread_print_routine(thread);
		thread = (thread_t) queue_next(&thread->thread_list);
	}
}

int		print_task_short_per_line = 8;
int		print_task_short_counter = 0;

print_task_short(task, routine)
	task_t		task;
	int		(*routine)();
{
#ifdef	lint
	(void) (*routine)();
#endif	lint

	if (print_task_short_counter++ == print_task_short_per_line) {
		printf("\n");
		print_task_short_counter = 1;
	}
	printf("%X ", task);
}

print_all_tasks(task_print_routine, thread_print_routine)
	int		(*task_print_routine)();
	int		(*thread_print_routine)();
{
	task_t		task;

	task = (task_t) queue_first(&all_tasks);
	while (!queue_end(&all_tasks, (queue_entry_t) task)) {
		(void) task_print_routine(task, thread_print_routine);
		task = (task_t) queue_next(&task->all_tasks);
	}
}

#if	NCPUS <= 1
#define freeze_all_processors(x)
#define thaw_all_processors()
#endif	NCPUS <= 1

/*
 */

#ifndef	ADDRESS_WAS_SPECIFIED
#define ADDRESS_WAS_SPECIFIED	adrflg
#endif	ADDRESS_WAS_SPECIFIED

#ifndef	ADDRESS_VALUE
#define ADDRESS_VALUE		adrval
#endif	ADDRESS_VALUE

/*
 *	Define the standard KDB commands
 */

#define KDB_PRINT_CASES							\
	case 'k':							\
		print_stack_trace(current_thread());			\
		break;							\
	case 'K':							\
		if (ADDRESS_WAS_SPECIFIED)				\
			print_stack_trace((thread_t) ADDRESS_VALUE);	\
		break;							\
	case 'l':							\
		if (ADDRESS_WAS_SPECIFIED)				\
			print_task_long((task_t) ADDRESS_VALUE,		\
						 print_thread);		\
		 else							\
			print_all_tasks(print_task_long, print_thread);	\
		break;							\
									\
	case 'L':							\
		print_all_tasks(print_task_long, print_stack_trace);	\
		break;							\
									\
	case 'Q':							\
		print_all_tasks(print_task_short, (int (*)()) 0);	\
		printf("\n");						\
		break;							\
	case 'f':							\
	case 'F':							\
		freeze_all_processors(cpu_number());			\
		break;							\
	case 't':							\
	case 'T':							\
		thaw_all_processors();					\
		break;							\
	case 'm':							\
		vm_map_print(dot);					\
		break;							\
	case 'P':							\
		switch(nextchar()) {					\
			extern void vm_object_print();			\
			extern void vm_map_print();			\
			extern void vm_page_print();			\
			extern void port_print();			\
									\
			case 't':					\
				break;					\
			case 'T':					\
				break;					\
			case 'p':					\
				port_print(dot);			\
				break;					\
			case 's':					\
				break;					\
			case 'I':					\
				break;					\
			case 'O':					\
				vm_object_print(dot);			\
				break;					\
			case 'M':					\
				vm_map_print(dot);			\
				break;					\
			case 'P':					\
				vm_page_print(dot);			\
				break;					\
			default:					\
				printf("cannot print unknown object\n");\
				break;					\
		}							\
		break;							

#endif	_KERN_KDB_PRINT_H_
