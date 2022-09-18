/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	task.c,v $
 * Revision 2.11  89/06/27  00:24:48  rpd
 * 	Added support for TASK_KERNEL_PORT (using task_tself).
 * 	[89/06/26  23:55:57  rpd]
 * 
 * Revision 2.10  89/05/06  02:57:13  rpd
 * 	Purged <kern/task_statistics.h>.  Purged xxx_task_* routines.
 * 	[89/05/05  20:42:07  rpd]
 * 
 * Revision 2.9  89/02/25  18:09:19  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.8  89/01/15  16:27:25  rpd
 * 	Added all_tasks, all_tasks_lock definitions.
 * 	[89/01/15  15:07:32  rpd]
 * 
 * Revision 2.7  88/12/19  02:47:46  mwyoung
 * 	Remove lint.
 * 	[88/12/09            mwyoung]
 * 
 * Revision 2.6  88/10/11  10:21:38  rpd
 * 	Changed includes to the new style.
 * 	Rewrote task_threads; the old version could return
 * 	an inconsistent picture of the task.
 * 	[88/10/05  10:28:13  rpd]
 * 
 * Revision 2.5  88/08/06  18:25:53  rpd
 * Changed to use ipc_task_lock/ipc_task_unlock macros.
 * Eliminated use of kern/mach_ipc_defs.h.
 * Enable kernel_task for IPC access.  (See hack in task_by_unix_pid to
 * allow a user to get the kernel_task's port.)
 * Made kernel_task's ref_count > 0, so that task_reference/task_deallocate
 * works on it.  (Previously the task_deallocate would try to destroy it.)
 * 
 * Revision 2.4  88/07/20  16:40:17  rpd
 * Removed task_ports (replaced by port_names).
 * Didn't leave xxx form, because it wasn't implemented.
 * 
 * Revision 2.3  88/07/17  17:55:52  mwyoung
 * Split up uses of task.kernel_only field.  Condensed history.
 * 
 * Revision 2.2.1.1  88/06/28  20:46:20  mwyoung
 * Split up uses of task.kernel_only field.  Condensed history.
 * 
 * 21-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Split up uses of task.kernel_only field.  Condensed history.
 *
 * 27-Jan-88  Douglas Orr (dorr) at Carnegie-Mellon University
 *	Init user space library structures.
 *
 * 21-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Task_create no longer returns the data port.  Task_status and
 *	task_set_notify are obsolete (use task_{get,set}_special_port).
 *
 * 21-Jan-88  Karl Hauth (hauth) at Carnegie-Mellon University
 *	task_info(kernel_task, ...) now looks explicitly in the
 *	kernel_map, so it actually returns useful numbers.
 *
 * 17-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added new task interfaces: task_suspend, task_resume,
 *	task_info, task_get_special_port, task_set_special_port.
 *	Old interfaces remain (temporarily) for binary
 *	compatibility, prefixed with 'xxx_'.
 *
 *  3-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Implemented better task termination base on task active field:
 *		1.  task_terminate sets active field to false.
 *		2.  All but the most simple task operations check the
 *			active field and abort if it is false.
 *		3.  task_{hold, dowait, release} now return kern_return_t's.
 *		4.  task_dowait has a second parameter to ignore active
 *			field if called from task_terminate.
 *	Task terminate acquires extra reference to current thread before
 *	terminating it (see thread_terminate()).
 *
 *  6-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Moved ipc_task_terminate to task_terminate, to shut down other
 *	threads that are manipulating the task via its task_port.
 *	Changed task_terminate to terminate all threads in the task.
 *
 * 29-Jul-87  David Golub (dbg) at Carnegie-Mellon University
 *	Fix task_suspend not to hold the task if the task has been
 *	resumed.  Change task_hold/task_wait so that if the current
 *	thread is in the task, it is not held until after all of the
 *	other threads in the task have stopped.  Make task_terminate be
 *	able to terminate the current task.
 */
/*
 *	File:	kern/task.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young, David Golub,
 *		David Black
 *
 *	Task management primitives implementation.
 */

#include <kern/mach_param.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <kern/zalloc.h>
#include <mach/machine/vm_types.h>
#include <mach/vm_param.h>
#include <vm/vm_kern.h>		/* for kernel_map */
#include <kern/ipc_tt.h>
#include <kern/ipc_globals.h>	/* for ipc_kernel_map */
#include <mach_emulation.h>
#include <mach/task_info.h>
#include <mach/task_special_ports.h>

queue_head_t all_tasks; /* list of all tasks in the system */
decl_simple_lock_data(,all_tasks_lock) /* lock for task list */

task_t	kernel_task;
zone_t	task_zone;

extern zone_t	u_zone;		/* UNIX */

void task_init()
{
	task_zone = zinit(
			sizeof(struct task),
			TASK_MAX * sizeof(struct task),
			TASK_CHUNK * sizeof(struct task),
			FALSE, "tasks");

	queue_init(&all_tasks);
	simple_lock_init(&all_tasks_lock);
/*	(void) task_create(TASK_NULL, FALSE, &kernel_task);*/
	kernel_task = (task_t) zalloc(task_zone);
	kernel_task->ref_count = 1;
	kernel_task->map = kernel_map;
	simple_lock_init(&kernel_task->lock);
	ipc_task_init(kernel_task, TASK_NULL);
	ipc_task_enable(kernel_task);
}

kern_return_t task_create(parent_task, inherit_memory, child_task)
	task_t		parent_task;
	boolean_t	inherit_memory;
	task_t		*child_task;		/* OUT */
{
	register task_t	new_task;

	new_task = (task_t) zalloc(task_zone);
	if (new_task == TASK_NULL) {
		panic("task_create: no memory for task structure");
	}

	new_task->u_address = (struct utask *) zalloc(u_zone);	/* UNIX */
	new_task->ref_count = 1;

	if (inherit_memory)
		new_task->map = vm_map_fork(parent_task->map);
	else
		new_task->map = vm_map_create(pmap_create(0),
					round_page(VM_MIN_ADDRESS),
					trunc_page(VM_MAX_ADDRESS), TRUE);

	simple_lock_init(&new_task->lock);
	queue_init(&new_task->thread_list);
	new_task->suspend_count = 0;
	new_task->active = TRUE;
	new_task->user_suspend_count = 0;
	new_task->user_stop_count = 0;
	new_task->thread_count = 0;
#if	MACH_EMULATION	
	new_task->eml_dispatch = EML_DISPATCH_NULL;
#endif	MACH_EMULATION	
	*child_task = new_task;

	new_task->kernel_ipc_space = FALSE;
	new_task->kernel_vm_space = FALSE;
	ipc_task_init(new_task, parent_task);

	new_task->total_user_time.seconds = 0;
	new_task->total_user_time.microseconds = 0;
	new_task->total_system_time.seconds = 0;
	new_task->total_system_time.microseconds = 0;

	simple_lock(&all_tasks_lock);
	queue_enter(&all_tasks, new_task, task_t, all_tasks);
	simple_unlock(&all_tasks_lock);

	ipc_task_enable(new_task);
	return(KERN_SUCCESS);
}

/*
 *	task_deallocate:
 *
 *	Give up a reference to the specified task and destroy it if there
 *	are no other references left.  It is assumed that the current thread
 *	is never in this task.
 */
void task_deallocate(task)
	register task_t	task;
{
	register int	c;

	if (task == TASK_NULL)
		return;

	task_lock(task);
	c = --(task->ref_count);
	task_unlock(task);
	if (c != 0)
		return;
	simple_lock(&all_tasks_lock);
	queue_remove(&all_tasks, task, task_t, all_tasks);
	simple_unlock(&all_tasks_lock);
	vm_map_deallocate(task->map);
	zfree(u_zone, (vm_offset_t) task->u_address);
	zfree(task_zone, (vm_offset_t) task);
}

void task_reference(task)
	register task_t	task;
{
	if (task == TASK_NULL)
		return;

	task_lock(task);
	task->ref_count++;
	task_unlock(task);
}

/*
 *	task_terminate:
 *
 *	Terminate the specified task.  See comments on thread_terminate
 *	(kern/thread.c) about problems with terminating the "current task."
 */
kern_return_t task_terminate(task)
	register task_t	task;
{
	register thread_t	thread, cur_thread;
	register queue_head_t	*list;

	if (task == TASK_NULL)
		return(KERN_INVALID_ARGUMENT);

	list = &task->thread_list;

	/*
	 *	Deactivate task so that it can't be terminated again,
	 *	and so lengthy operations in progress will abort.
	 *
	 *	If the current thread is in this task, remove it from
	 *	the task's thread list to keep the thread-termination
	 *	loop simple.
	 */
	cur_thread = current_thread();
	task_lock(task);
	if (!task->active) {
		/*
		 *	Task is already being terminated.
		 */
		task_unlock(task);
		return(KERN_FAILURE);
	}
	task->active = FALSE;
	if (cur_thread->task == task) {
		queue_remove(list, cur_thread, thread_t, thread_list);
		task_unlock(task);
		/*
		 *	Shut down this thread's ipc now because it must
		 *	be left alone to terminate the task.
		 */
		ipc_thread_disable(cur_thread);
		ipc_thread_terminate(cur_thread);
	}
	else {
		task_unlock(task);
	}
	

	/*
	 *	Prevent further execution of the task.  ipc_task_disable
	 *	prevents further task operations via the task port.
	 *	If this is the current task, the current thread will
	 *	be left running.
	 */
	ipc_task_disable(task);
	(void) task_hold(task);
	(void) task_dowait(task,TRUE);			/* may block */

	/*
	 *	Terminate each thread in the task.
	 *
	 *	The task_port is closed down, so no more thread_create
	 *	operations can be done.  Thread_terminate closes the
	 *	thread port for each thread; when that is done, the
	 *	thread will eventually disappear.  Thus the loop will
	 *	terminate.
	 */
	task_lock(task);
	while (!queue_empty(list)) {
		thread = (thread_t) queue_first(list);
		task_unlock(task);
		(void) thread_terminate(thread);	/* may block */
		task_lock(task);
	}
	task_unlock(task);

	/*
	 *	Shut down IPC.
	 */
	ipc_task_terminate(task);

#if	MACH_EMULATION
	eml_task_exit(task);
#endif	MACH_EMULATION	

	/*
	 *	Deallocate the (hopefully) last reference of the task.
	 */
	task_deallocate(task);

	/*
	 *	If the current thread is in this task, it has not yet
	 *	been terminated (since it was removed from the task's
	 *	thread-list).  Put it back in the thread list (for
	 *	completeness), and terminate it.  Since it holds the
	 *	last reference to the task, terminating it will deallocate
	 *	the task.
	 */
	if (cur_thread->task == task) {
		task_lock(task);
		queue_enter(list, cur_thread, thread_t, thread_list);
		task_unlock(task);
		(void) thread_terminate(cur_thread);
	}

	return(KERN_SUCCESS);
}

/*
 *	task_hold:
 *
 *	Suspend execution of the specified task.
 *	This is a recursive-style suspension of the task, a count of
 *	suspends is maintained.
 */
kern_return_t task_hold(task)
	register task_t	task;
{
	register queue_head_t	*list;
	register thread_t	thread, cur_thread;

	cur_thread = current_thread();

	task_lock(task);
	if (!task->active) {
		task_unlock(task);
		return(KERN_FAILURE);
	}

	task->suspend_count++;

	/*
	 *	Iterate through all the threads and hold them.
	 *	Do not hold the current thread if it is within the
	 *	task.
	 */
	list = &task->thread_list;
	thread = (thread_t) queue_first(list);
	while (!queue_end(list, (queue_entry_t) thread)) {
		if (thread != cur_thread)
			thread_hold(thread);
		thread = (thread_t) queue_next(&thread->thread_list);
	}
	task_unlock(task);
	return(KERN_SUCCESS);
}

/*
 *	task_dowait:
 *
 *	Wait until the task has really been suspended (all of the threads
 *	are stopped).  Skip the current thread if it is within the task.
 *
 *	If task is deactivated while waiting, return a failure code unless
 *	must_wait is true.
 */
kern_return_t task_dowait(task, must_wait)
	register task_t	task;
	boolean_t must_wait;
{
	register queue_head_t	*list;
	register thread_t	thread, cur_thread, prev_thread;
	register kern_return_t	ret = KERN_SUCCESS;

	/*
	 *	Iterate through all the threads.
	 *	While waiting for each thread, we gain a reference to it
	 *	to prevent it from going away on us.  This guarantees
	 *	that the "next" thread in the list will be a valid thread.
	 *
	 *	We depend on the fact that if threads are created while
	 *	we are looping through the threads, they will be held
	 *	automatically.  We don't care about threads that get
	 *	deallocated along the way (the reference prevents it
	 *	from happening to the thread we are working with).
	 *
	 *	If the current thread is in the affected task, it is skipped.
	 *
	 *	If the task is deactivated before we're done, and we don't
	 *	have to wait for it (must_wait is FALSE), just bail out.
	 */
	cur_thread = current_thread();

	list = &task->thread_list;
	prev_thread = THREAD_NULL;
	task_lock(task);
	thread = (thread_t) queue_first(list);
	while (!queue_end(list, (queue_entry_t) thread)) {
		if (!(task->active) && !(must_wait)) {
			ret = KERN_FAILURE;
			break;
		}
		if (thread != cur_thread) {
			thread_reference(thread);
			task_unlock(task);
			if (prev_thread != THREAD_NULL)
				thread_deallocate(prev_thread);
							/* may block */
			thread_dowait(thread);		/* may block */
			prev_thread = thread;
			task_lock(task);
		}
		thread = (thread_t) queue_next(&thread->thread_list);
	}
	task_unlock(task);
	if (prev_thread != THREAD_NULL)
		thread_deallocate(prev_thread);		/* may block */
	return(ret);	
}

kern_return_t task_release(task)
	register task_t	task;
{
	register queue_head_t	*list;
	register thread_t	thread, next;

	task_lock(task);
	if (!task->active) {
		task_unlock(task);
		return(KERN_FAILURE);
	}

	task->suspend_count--;

	/*
	 *	Iterate through all the threads and release them
	 */
	list = &task->thread_list;
	thread = (thread_t) queue_first(list);
	while (!queue_end(list, (queue_entry_t) thread)) {
		next = (thread_t) queue_next(&thread->thread_list);
		thread_release(thread);
		thread = next;
	}
	task_unlock(task);
	return(KERN_SUCCESS);
}

/*
 *	task_halt:
 *
 *	Halt all threads in the task.  Do not halt the current thread if
 *	it is within the task.
 *
 *	If task is deactivated while waiting, return a failure code unless
 *	must_wait is true.
 */
kern_return_t task_halt(task, must_wait)
	register task_t	task;
	boolean_t must_wait;
{
	register queue_head_t	*list;
	register thread_t	thread, cur_thread, prev_thread;
	register kern_return_t	ret = KERN_SUCCESS;

	/*
	 *	Iterate through all the threads.
	 *	While waiting for each thread, we gain a reference to it
	 *	to prevent it from going away on us.  This guarantees
	 *	that the "next" thread in the list will be a valid thread.
	 *
	 *	If the current thread is in the affected task, it is skipped.
	 *
	 *	If the task is deactivated before we're done, and we don't
	 *	have to wait for it (must_wait is FALSE), just bail out.
	 */
	cur_thread = current_thread();

	list = &task->thread_list;
	prev_thread = THREAD_NULL;
	task_lock(task);
	thread = (thread_t) queue_first(list);
	while (!queue_end(list, (queue_entry_t) thread)) {
		if (!(task->active) && !(must_wait)) {
			ret = KERN_FAILURE;
			break;
		}
		if (thread != cur_thread) {
			thread_reference(thread);
			task_unlock(task);
			if (prev_thread != THREAD_NULL)
				thread_deallocate(prev_thread);
							/* may block */
			thread_halt(thread);		/* may block */
			prev_thread = thread;
			task_lock(task);
		}
		thread = (thread_t) queue_next(&thread->thread_list);
	}
	task_unlock(task);
	if (prev_thread != THREAD_NULL)
		thread_deallocate(prev_thread);		/* may block */
	return(ret);	
}

kern_return_t task_threads(task, thread_list, count)
	task_t		task;
	thread_array_t	*thread_list;
	unsigned int	*count;
{
	unsigned int actual;	/* this many threads */
	thread_t thread;
	port_t *threads;
	int i;

	vm_size_t size;
	vm_offset_t addr;

	if (task == TASK_NULL)
		return KERN_INVALID_ARGUMENT;

	size = 0; addr = 0;

	for (;;) {
		vm_size_t size_needed;

		task_lock(task);
		if (!task->active) {
			task_unlock(task);
			return KERN_FAILURE;
		}

		actual = task->thread_count;

		/* do we have the memory we need? */

		size_needed = actual * sizeof(port_t);
		if (size_needed <= size)
			break;

		/* unlock the task and allocate more memory */
		task_unlock(task);

		if (size != 0)
			(void) kmem_free(ipc_kernel_map, addr, size);

		size = round_page(2 * size_needed);

		/* allocate memory non-pageable, so don't fault
		   while holding locks */

		(void) vm_allocate(ipc_kernel_map, &addr, size, TRUE);
		(void) vm_map_pageable(ipc_kernel_map,
				       addr, addr + size, FALSE);
	}

	/* OK, have memory and the task is locked & active */

	threads = (port_t *) addr;

	for (i = 0, thread = (thread_t) queue_first(&task->thread_list);
	     i < actual;
	     i++, thread = (thread_t) queue_next(&thread->thread_list))
		threads[i] = convert_thread_to_port(thread);
	assert(queue_end(&task->thread_list, (queue_entry_t) thread));

	/* can unlock task now that we've got the thread ports */
	task_unlock(task);

	if (actual == 0) {
		/* no threads, so return null pointer and deallocate memory */
		*thread_list = 0;
		*count = 0;

		if (size != 0)
			(void) kmem_free(ipc_kernel_map, addr, size);
	} else {
		vm_size_t size_used;

		*thread_list = threads;
		*count = actual;

		size_used = round_page(actual * sizeof(thread_t));

		/* finished touching it, so make the memory pageable */
		(void) vm_map_pageable(ipc_kernel_map,
				       addr, addr + size_used, TRUE);

		/* free any unused memory */
		if (size_used != size)
			(void) kmem_free(ipc_kernel_map,
					 addr + size_used, size - size_used);
	}

	return KERN_SUCCESS;
}

kern_return_t task_suspend(task)
	register task_t	task;
{
	register boolean_t	hold;

	if (task == TASK_NULL)
		return(KERN_INVALID_ARGUMENT);

	hold = FALSE;
	task_lock(task);
	if ((task->user_stop_count)++ == 0)
		hold = TRUE;
	task_unlock(task);

	/*
	 *	If the stop count was positive, the task is
	 *	already stopped and we can exit.
	 */
	if (!hold) {
		return (KERN_SUCCESS);
	}

	/*
	 *	Hold all of the threads in the task, and wait for
	 *	them to stop.  If the current thread is within
	 *	this task, hold it separately so that all of the
	 *	other threads can stop first.
	 */

	if (task_hold(task) != KERN_SUCCESS)
		return(KERN_FAILURE);

	if (task_dowait(task, FALSE) != KERN_SUCCESS)
		return(KERN_FAILURE);

	if (current_task() == task) {
		thread_hold(current_thread());
		thread_dowait(current_thread());
	}

	return(KERN_SUCCESS);
}

kern_return_t task_resume(task)
	register task_t	task;
{
	register boolean_t	release;

	if (task == TASK_NULL)
		return(KERN_INVALID_ARGUMENT);

	release = FALSE;
	task_lock(task);
	if (task->user_stop_count > 0) {
		if (--(task->user_stop_count) == 0)
	    		release = TRUE;
	}
	else {
		task_unlock(task);
		return(KERN_FAILURE);
	}
	task_unlock(task);

	/*
	 *	Release the task if necessary.
	 */
	if (release)
		return(task_release(task));

	return(KERN_SUCCESS);
}

kern_return_t task_info(task, flavor, task_info_out, task_info_count)
	task_t			task;
	int			flavor;
	task_info_t		task_info_out;	/* pointer to OUT array */
	unsigned int		*task_info_count;	/* IN/OUT */
{
	task_basic_info_t	basic_info;
	vm_map_t		map;

	extern task_t		first_task;	/* kernel task */

	if (task == TASK_NULL)
		return(KERN_INVALID_ARGUMENT);

	/*
	 *	Only one flavor of information returned at the moment.
	 */
	if (flavor != TASK_BASIC_INFO ||
	    *task_info_count < TASK_BASIC_INFO_COUNT) {
		return(KERN_INVALID_ARGUMENT);
	}

	basic_info = (task_basic_info_t) task_info_out;

	map = (task == first_task) ? kernel_map : task->map;

	basic_info->virtual_size  = map->size;
	basic_info->resident_size = pmap_resident_count(map->pmap)
					   * PAGE_SIZE;
	basic_info->base_priority =
		(task == first_task) ? BASEPRI_SYSTEM : BASEPRI_USER;
				/* may change later XXX */

	task_lock(task);
	basic_info->suspend_count = task->user_stop_count;
	basic_info->user_time.seconds
				= task->total_user_time.seconds;
	basic_info->user_time.microseconds
				= task->total_user_time.microseconds;
	basic_info->system_time.seconds
				= task->total_system_time.seconds;
	basic_info->system_time.microseconds 
				= task->total_system_time.microseconds;
	task_unlock(task);

	*task_info_count = TASK_BASIC_INFO_COUNT;

	return(KERN_SUCCESS);
}

/*
 *	Special version of task_suspend that doesn't wait.
 *	Called only from interrupt level (U*X psignal).
 *	Will go away when signal code becomes sane.
 */
kern_return_t task_suspend_nowait(task)
	register task_t	task;
{
	register boolean_t	hold;

	if (task == TASK_NULL)
		return(KERN_INVALID_ARGUMENT);

	hold = FALSE;
	task_lock(task);
	if ((task->user_stop_count)++ == 0)
		hold = TRUE;
	task_unlock(task);

	/*
	 *	If the stop count was positive, the task is
	 *	already stopped and we can exit.
	 */
	if (!hold) {
		return (KERN_SUCCESS);
	}

	/*
	 *	Hold all of the threads in the task.
	 *	If the current thread is within
	 *	this task, hold it separately so that all of the
	 *	other threads can stop first.
	 */

	if (task_hold(task) != KERN_SUCCESS)
		return(KERN_FAILURE);

	if (current_task() == task) {
		thread_hold(current_thread());
	}

	return(KERN_SUCCESS);
}

kern_return_t task_get_special_port(task, which_port, port)
	task_t		task;
	int		which_port;
	port_t		*port;
{
	port_t		*portp;

	if (task == TASK_NULL)
		return(KERN_INVALID_ARGUMENT);

	switch (which_port) {
	    case TASK_KERNEL_PORT:
		portp = &task->task_tself;
		break;
	    case TASK_NOTIFY_PORT:
		portp = &task->task_notify;
		break;
	    case TASK_EXCEPTION_PORT:
		portp = &task->exception_port;
		break;
	    case TASK_BOOTSTRAP_PORT:
		portp = &task->bootstrap_port;
		break;
	    default:
		return(KERN_INVALID_ARGUMENT);
	}

	ipc_task_lock(task);
	if (!task->ipc_active) {
		ipc_task_unlock(task);
		return(KERN_FAILURE);
	}
	
	if ((*port = *portp) != PORT_NULL) {
		port_reference(*portp);
	}
	ipc_task_unlock(task);

	return(KERN_SUCCESS);
}

kern_return_t task_set_special_port(task, which_port, port)
	task_t		task;
	int		which_port;
	port_t		port;
{
	port_t		*portp;
	port_t		old_port;

	if (task == TASK_NULL)
		return(KERN_INVALID_ARGUMENT);

	switch (which_port) {
	    case TASK_KERNEL_PORT:
		portp = &task->task_tself;
		break;
	    case TASK_NOTIFY_PORT:
		portp = &task->task_notify;
		break;
	    case TASK_EXCEPTION_PORT:
		portp = &task->exception_port;
		break;
	    case TASK_BOOTSTRAP_PORT:
		portp = &task->bootstrap_port;
		break;
	    default:
		return(KERN_INVALID_ARGUMENT);
	}

	ipc_task_lock(task);
	if (!task->ipc_active) {
		ipc_task_unlock(task);
		return(KERN_FAILURE);
	}
	
	old_port = *portp;
	if ((*portp = port) != PORT_NULL)
		port_reference(port);

	ipc_task_unlock(task);

	if (old_port != PORT_NULL)
		port_release(old_port);

	return(KERN_SUCCESS);
}

