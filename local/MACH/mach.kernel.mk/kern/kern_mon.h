/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kern_mon.h,v $
 * Revision 2.3  89/10/15  02:04:43  rpd
 * 	Minor cleanups.
 * 
 * Revision 2.2  89/10/11  14:11:05  dlb
 * 	Reorganize buffer structures to use descriptor substructures.
 * 	General cleanup and bug fixes.
 * 
 * Revision 2.1.1.4  89/08/02  23:49:31  dlb
 * 	No more kern_mon_param.h
 * 	[89/08/02            dlb]
 * 
 * Revision 2.1.1.3  89/08/02  23:39:29  dlb
 * 	Move constant definitions here from mach/kern_mon_param.h.
 * 	[89/08/02            dlb]
 * 
 * Revision 2.1.1.2  89/08/02  22:58:36  dlb
 * 	Cleanup changes.
 * 	[89/08/02            dlb]
 * 
 * Revision 2.1.1.1  89/07/25  18:46:00  dlb
 * 	Removed externs for kern_mon_btime[].  Removed kern_mon_get_btime()
 * 	macros.  Modified kern_mon_store_times() to store only one timestamp.
 * 	[89/04/16            tfl]
 * 
 * 	Moved the buffer storage part of the sensor code to sensor calls
 * 	in kernel_monitor.c  Added tests for existence of monitor before 
 * 	getting timestamps and saving threads.  Also modified the macros
 * 	to make them of more general utility.  Now the procedure calls
 * 	are made only if the sensor will fire (a monitor exists for the
 * 	thread).
 * 	[88/10/24            tfl]
 * 
 * 	Created.  Based on previous, single user version of kernel monitor
 * 	[88/04/15            tfl]
 * 
 */

/*
 *	File:	kern/kern_mon.h
 *	Author:	Ted Lehr
 *
 *	Copyright (C) 1987, Ted Lehr
 *
 * 	Kernel Monitoring Header file containing Macros and variable
 *	declarations.
 *
 */

#ifndef _KERN_KERN_MON_H_
#define _KERN_KERN_MON_H_

#include <cpus.h>

#include <kern/zalloc.h>
#include <kern/timer.h>
#include <sys/time.h>
#include <vm/vm_kern.h>
#include <mach/kern_return.h>
#include <mach/kernel_event.h>

#define MONITOR_RUN 		0x4		/* monitor fire state 	    */
#define MONITOR_PAUSE		0x3		/* monitor pause state	    */
#define MONITOR_SHUTDOWN	0x2		/* monitor shutdown state   */
#define MONITOR_CPU_OFF	        0x1		/* cpu shutdown state 	    */
#define MONITOR_OFF		0		/* monitor off state 	    */
#define MONITOR_OVFLOW		0x80000000	/* buffer overflow case     */
#define MONITOR_READING	        0x1		/* set when reading buffers */
#define MONITOR_NOT_READING	0		/* set when not reading     */
#define MONITOR_NO_ID		0xffffffff	/* id of irrelevant threads */
#define MONITOR_NO		0x0		/* for setting flag	    */
#define MONITOR_YES		0x1		/* for setting flag	    */

#define MONITOR_MAX             32              /* Max number of monitors   */
#define MONITOR_CHUNK            2              /* Allocation Chunk         */

extern int
monitor_old_thread();		

extern void
monitor_new_thread();		

extern kern_return_t
monitor_create();

extern kern_return_t
monitor_terminate();

extern kern_return_t
monitor_resume();

extern kern_return_t
monitor_suspend();

extern kern_return_t
monitor_read();

extern kern_return_t
thread_monitor();

extern kern_return_t
thread_unmonitor();

extern void
monitor_init();

extern void
monitor_reference();

extern void
monitor_deallocate();

extern void
all_monitor_enqueue();

extern void 
all_monitor_remqueue();

extern void
thread_monitor_dequeue();

extern void
monitor_cpu_out();

extern void
monitor_cpu_in();

typedef
struct kernel_monitor_buffer {
    kern_mon_event_t  	buffer_head;    /* kernel event buffers   */
    kern_mon_event_t	buffer_end;	/* Pointers to end */
    kern_mon_event_t  	write_ptr;    	/* Pointers to next write */
    kern_mon_event_t  	read_ptr;	/* Pointers to next read  */
} monitor_buffer, *monitor_buffer_t;

typedef
struct		kernel_monitor_object {
    unsigned int 	bytes_in_all_bufs;	/* bytes in global buf    */
    unsigned int 	max_events_cpu_buf;	/* events per cpu buf     */
    monitor_buffer	buffer[NCPUS];		/* buffer pointers	  */
    kern_mon_event_t  	ptr_to_reader_buf;	/* pointer to reader buf  */
    kern_mon_event_t  	ptr_to_all_bufs;    	/* mem ptr for all bufs   */
    char		processor_state[NCPUS]; /* Cpu state checks	  */
    char		read_flag;		/* For copyout signal 	  */
    char		global_state;	    	/* Monitor state checks   */
    unsigned int	ref_count;	        /* reference counter  	  */
    simple_lock_data_t	lock;	  	        /* Lock for atomicity 	  */
    queue_head_t	monitored_threads;	/* monitored threads queue*/
    queue_chain_t	all_monitors;	  	/* entry monitors list 	  */  
    port_t		monitor_self;		/* the monitor port	  */
} monitor, *monitor_t;


/*  global data structures */
extern
queue_head_t	 	all_monitors;		/* queue of all monitors  */
decl_simple_lock_data(extern,all_monitors_lock)	/* lock for monitor queue */

#define MONITOR_NULL	((monitor_t) 0)	/* NULL monitor pointer checks */


/***********************************************************************
 *	Macros:		monitor_lock
 *			monitor_unlock
 *
 *	Functions:
 *  		Defines two commonly used lock statments.
 */
#define	monitor_lock(m)		simple_lock(&m->lock)
#define monitor_unlock(m)	simple_unlock(&m->lock)


/***********************************************************************
 *  	Macro:		kern_mon_store_times()
 *
 *	Function:
 *		Gets a timestamp using the appropriate function and
 *		stores it in event buffer.
 */
#if     STAT_TIME
#define kern_mon_store_times(event) {				        \
	struct timeval  km_time;					\
	microtime(&km_time);						\
	event->lo_time = km_time.tv_usec;				\
	event->hi_time = km_time.tv_sec;				\
	}
#else	STAT_TIME
#define kern_mon_store_times(event) {				        \
	event->lo_time = get_timestamp();				\
	}
#endif  STAT_TIME

/***********************************************************************/


/***********************************************************************
 *  	Macro:		kern_mon_thread_sensor()
 *
 *	Function:
 *        Called in thread_block() and thread_switch() (in sched_prim.c).  
 *	  To be placed in kern/sched_prim.c before the load_context() calls
 *	  in thread_block() and thread_switch().
 *
 *        If old_thread is not NULL, then that means it the thread it points
 *	  to has a monitor associated with it.  Thus we make a call to a
 *	  sensor.   The monitor_old_thread() call returns non-zero if 
 *        both old_thread and new_thread have pointers to the same
 *        monitor indicating that information about new_thread was recorded
 *        in the old_thread portion of sensor.  
 *
 *	  If old_thread is NULL, then new_thread is still tested to
 *	  see if it has a monitor associated with it.
 */

#define kern_mon_thread_sensor(old_thread, new_thread,my_cpu)		\
									\
if (old_thread->monitor_obj != MONITOR_NULL) {			        \
  if((monitor_old_thread(old_thread,new_thread,my_cpu) == MONITOR_YES) &&\
     (new_thread->monitor_obj != MONITOR_NULL) 	) {			\
     monitor_new_thread(new_thread,my_cpu);				\
  }									\
} else { 								\
  if (new_thread->monitor_obj != MONITOR_NULL) {			\
	monitor_new_thread(new_thread, my_cpu);				\
  }									\
}

/***********************************************************************/

#endif	_KERN_KERN_MON_H_
