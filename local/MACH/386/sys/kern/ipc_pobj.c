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
 * $Log:	ipc_pobj.c,v $
 * Revision 2.7  89/03/05  16:47:15  rpd
 * 	Fixed annoying warning message in convert_port_to_map.
 * 	[89/02/16  13:47:36  rpd]
 * 
 * Revision 2.6  89/02/25  18:03:19  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  88/12/19  02:44:41  mwyoung
 * 	Removed lint.
 * 	[88/12/18            mwyoung]
 * 
 * Revision 2.4  88/10/27  10:46:50  rpd
 * 	Minor cosmetic change.
 * 	[88/10/26  14:42:09  rpd]
 * 
 * Revision 2.3  88/08/25  18:15:51  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Check for null port in conver_task_to_port.
 * 	[88/08/17  19:52:06  mwyoung]
 * 
 * Revision 2.2  88/08/06  18:18:24  rpd
 * Created.
 * 
 */
/*
 * File:	ipc_pobj.c
 * Purpose:
 *	Port object functions; task and thread conversion functions.
 */

#include <kern/kern_port.h>
#include <kern/port_object.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <vm/vm_map.h>
#include <kern/ipc_pobj.h>

#include <kern/macro_help.h>

/*
 *	Port object set/get routines. [exported]
 *
 *	Each port may have an "object" associated with it, to provide
 *	quick lookup of that object for the kernel.
 */

void
port_object_set(port, type, object)
	port_t port;
	port_object_type_t type;
	int object;
{
#define port_object_set(port, type, object) 			\
	MACRO_BEGIN						\
	register kern_port_t _kp = (kern_port_t)(port);		\
	_kp->port_object.kp_type = (type);			\
	_kp->port_object.kp_object = (object);			\
	MACRO_END

	port_object_set(port, type, object);
}

int
port_object_get(port)
	port_t port;
{
#define port_object_get(port)	(((kern_port_t)(port))->port_object.kp_object)

	return port_object_get(port);
}

port_object_type_t
port_object_type(port)
	port_t		port;
{
#define port_object_type(port)	(((kern_port_t)(port))->port_object.kp_type)

	return port_object_type(port);
}

/*
 *	Conversion routines, from port to task/thread/map. [exported]
 */

task_t
convert_port_to_task(_port)
	port_t		_port;
{
	register task_t task;
	kern_port_t port = (kern_port_t) _port;

	if (port == KERN_PORT_NULL)
		return TASK_NULL;

	port_lock(port);

	if (port_object_type(port) == PORT_OBJECT_TASK) {
		task = (task_t) port_object_get(port);
		task_reference(task);
	} else
		task = TASK_NULL;

	port_unlock(port);
	return task;
}

thread_t
convert_port_to_thread(_port)
	port_t		_port;
{
	register thread_t th;
	kern_port_t	port = (kern_port_t) _port;

	if (port == KERN_PORT_NULL)
		return THREAD_NULL;

	port_lock(port);

	if (port_object_type(port) == PORT_OBJECT_THREAD) {
		th = (thread_t) port_object_get(port);
		thread_reference(th);
	} else
		th = THREAD_NULL;

	port_unlock(port);
	return th;
}

vm_map_t
convert_port_to_map(port)
	port_t		port;
{
	register task_t task;
	register vm_map_t map;

	task = convert_port_to_task(port);

	if (task == TASK_NULL)
		return VM_MAP_NULL;

	map = task->map;
	vm_map_reference(map);

	task_deallocate(task);
	return map;
}

port_t
convert_task_to_port(task)
	register task_t task;
{
	register kern_port_t result;

	ipc_task_lock(task);
	if (task->ipc_active) {
		result = (kern_port_t) task->task_self;
		if (result != KERN_PORT_NULL)
		   	port_reference(result);
	} else
		result = KERN_PORT_NULL;

	ipc_task_unlock(task);
	return (port_t) result;
}

port_t
convert_thread_to_port(thread)
	register thread_t thread;
{
	register kern_port_t result;

	ipc_thread_lock(thread);

	result = (kern_port_t) thread->thread_self;
	if (result != KERN_PORT_NULL)
	   	port_reference(result);

	ipc_thread_unlock(thread);
	return (port_t) result;
}
