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
 * $Log:	ux_exception.c,v $
 * Revision 2.12  89/05/31  12:28:39  rvb
 * 	Stylistic change. [af]
 * 
 * Revision 2.11  89/05/01  15:22:35  rpd
 * 	Don't initialize task->reply_port here.
 * 	[89/05/01  13:47:05  rpd]
 * 
 * Revision 2.10  89/03/09  19:35:02  rpd
 * 	More cleanup.
 * 
 * Revision 2.9  89/02/25  15:01:01  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.8  89/02/06  23:48:22  mwyoung
 * File relocated from uxkern/ux_exception.c
 * 
 * Revision 2.7  89/01/15  16:36:18  rpd
 * 	Updated includes for the new mach/ directory.
 * 	[89/01/15  15:21:04  rpd]
 * 
 * Revision 2.6  88/09/25  22:16:55  rpd
 * 	Changed includes to the new style.
 * 	Changed to use object_copyin instead of port_copyin,
 * 	and eliminated use of PORT_INVALID.
 * 	[88/09/24  18:14:52  rpd]
 * 
 * Revision 2.5  88/08/06  19:22:38  rpd
 * Eliminated use of kern/mach_ipc_defs.h.
 * 
 * Revision 2.4  88/07/20  21:08:20  rpd
 * Modified to use a port set to eat notifications; this fixes a message leak.
 * Also will now send error messages in response to bogus requests.
 * 
 * Revision 2.3  88/07/17  19:30:39  mwyoung
 * Change use of kernel_only to new kernel_vm_space.
 *
 * 10-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Check error returns from port_copyin().
 *
 * 29-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 *  8-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Rewrite to use local port names and internal kernel rpcs.
 *
 *  4-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Update to exc interface.  Set ipc_kernel in handler thread.
 *	Deallocate thread/task references now returned from convert
 *	routines.
 *
 * 30-Nov-87  David Black (dlb) at Carnegie-Mellon University
 *	Split unix-dependent stuff into this separate file.
 *
 * 30-Oct-87  David Black (dlb) at Carnegie-Mellon University
 *	Get port references right.
 *
 * 19-Oct-87  David Black (dlb) at Carnegie-Mellon University
 *	Removed port_copyout to kernel_task.  mach_ipc.c has been fixed
 *	to allow kernel to send to any port.
 *
 *  1-Oct-87  David Black (dlb) at Carnegie-Mellon University
 *	Created
 *
 */

#include <sys/param.h>
#include <sys/user.h>

#include <mach/boolean.h>
#include <mach/exception.h>
#include <mach/kern_return.h>
#include <mach/message.h>
#include <mach/port.h>
#include <mach/mig_errors.h>
#include <kern/lock.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <kern/sched_prim.h>
#include <kern/ipc_pobj.h>
#include <kern/ipc_copyin.h>
#include <builtin/ux_exception.h>

#include <mach/exc.h>
#include <mach/mach_user_internal.h>

/*
 *	Unix exception handler.
 */

void	ux_exception();

decl_simple_lock_data(,	ux_handler_init_lock)
port_t			ux_exception_port;

/*
 *	Messages.  Receive message must be incredibly large just in case
 *	some bogon sends a truly enormous message to this port.
 */
static struct {
    msg_header_t	h;
    char		d[MSG_SIZE_MAX - (sizeof(msg_header_t))];
} exc_msg;

static struct {
    death_pill_t	pill;
    int			d[2];
} rep_msg;

port_t	ux_handler_task_self;
task_t	ux_handler_task;

void	ux_handler()
{
	register kern_return_t	r;
	port_name_t		ux_notify_port;
	port_name_t		ux_local_port;
	port_set_name_t		ux_set;
	extern void		task_name();

	ux_handler_task = current_task();
	ux_handler_task->kernel_vm_space = TRUE;
	current_thread()->ipc_kernel = TRUE;

	simple_lock(&ux_handler_init_lock);

	ux_handler_task_self = task_self();

	/*
	 *	Allocate a port set that we will receive on.
	 */
	r = port_set_allocate(ux_handler_task_self, &ux_set);
	if (r != KERN_SUCCESS)
		panic("ux_handler: port_set_allocate failed");

	/*
	 *	Allocate an exception port and use object_copyin to
	 *	translate it to the global name.  Put it into the set.
	 */
	r = port_allocate(ux_handler_task_self, &ux_local_port);
	if (r != KERN_SUCCESS)
		panic("ux_handler: port_allocate failed");
	r = port_set_add(ux_handler_task_self, ux_set, ux_local_port);
	if (r != KERN_SUCCESS)
		panic("ux_handler: port_set_add failed");
	ux_exception_port = ux_local_port;
	if (!object_copyin(ux_handler_task, ux_exception_port,
			   MSG_TYPE_PORT, FALSE,
			   (kern_obj_t *) &ux_exception_port))
		panic("ux_handler: object_copyin(ux_exception_port) failed");

	/*
	 *	Get a hold of our notify port.  Put it into the set.
	 */
	ux_notify_port = task_notify();
	r = port_set_add(ux_handler_task_self, ux_set, ux_notify_port);
	if (r != KERN_SUCCESS)
		panic("ux_handler: port_set_add failed");

	/*
	 *	Release kernel to continue.
	 */
	thread_wakeup((int) &ux_exception_port);
	simple_unlock(&ux_handler_init_lock);

	task_name("exception hdlr");

	/* Message handling loop. */

 	for (;;) {
		exc_msg.h.msg_local_port = ux_set;
		exc_msg.h.msg_size = sizeof(exc_msg);

		r = msg_receive(&exc_msg.h, MSG_OPTION_NONE, 0);
		if (r != RCV_SUCCESS) {
			printf("error code %d\n", r);
			panic("exception_handler: receive failed");
		}
			
		if (exc_msg.h.msg_local_port == ux_notify_port)
			/* ignore notifications */;
		else if (exc_msg.h.msg_local_port == ux_local_port) {
			register port_name_t	rep_port;

			(void) exc_server(&exc_msg.h, &rep_msg.pill.Head);
			rep_port = rep_msg.pill.Head.msg_remote_port;
			if ((rep_port != PORT_NULL) &&
			    (rep_msg.pill.RetCode != MIG_NO_REPLY)) {
				/* might fail if client died */
				/* XXX might block? */
				(void) msg_send(&rep_msg.pill.Head,
						MSG_OPTION_NONE, 0);

				/* XXX rep_port might be important */
				(void) port_deallocate(ux_handler_task_self,
						       rep_port);
			}
		} else
			panic("ux_handler: strange port");
	}
}

kern_return_t
catch_exception_raise(exception_port, thread_port, task_port,
	exception, code, subcode)
port_t		exception_port, thread_port, task_port;
int		exception, code, subcode;
{
    thread_t	thread;
    task_t	task;
    int		signal = 0;
    int		ret = KERN_SUCCESS;

#ifdef	lint
    exception_port++;
#endif	lint

    /*
     *	Convert local port names to structure pointers.  Have object_copyin
     *	deallocate our rights to the ports.  (it returns a reference).
     */
    if (!object_copyin(ux_handler_task, task_port,
		       MSG_TYPE_PORT, TRUE,
		       (kern_obj_t *) &task_port))
	return(KERN_INVALID_ARGUMENT);

    if (!object_copyin(ux_handler_task, thread_port,
		       MSG_TYPE_PORT, TRUE,
		       (kern_obj_t *) &thread_port)) {
	port_release(task_port);
	return(KERN_INVALID_ARGUMENT);
    }

    task = convert_port_to_task(task_port);
    thread = convert_port_to_thread(thread_port);

    /*
     *	Catch bogus ports
     */
    if (task != TASK_NULL && thread != THREAD_NULL) {

	    /*
	     *	Convert exception to unix signal and code.
	     */
	    ux_exception(exception, code, subcode, &signal,
		&thread->u_address.uthread->uu_code);

	    /*
	     *	Send signal.
	     */
	    if (signal != 0)
		thread_psignal(thread, signal);
    }
    else {
	ret = KERN_INVALID_ARGUMENT;
    }

    /*
     *	Delete the references acquired in the convert routines.
     */
    if (task != TASK_NULL) 
	task_deallocate(task);

    if (thread != THREAD_NULL)
	thread_deallocate(thread);

    /*
     *	Delete the port references that came from port_copyin.
     */
    port_release(task_port);
    port_release(thread_port);

    return(ret);
}


boolean_t	machine_exception();

/*
 *	ux_exception translates a mach exception, code and subcode to
 *	a signal and u.u_code.  Calls machine_exception (machine dependent)
 *	to attempt translation first.
 */

void ux_exception(exception, code, subcode, ux_signal, ux_code)
int	exception, code, subcode;
int	*ux_signal, *ux_code;
{
	/*
	 *	Try machine-dependent translation first.
	 */
	if (machine_exception(exception, code, subcode, ux_signal, 
	    ux_code))
		return;
	
	switch(exception) {

	    case EXC_BAD_ACCESS:
		if (code == KERN_INVALID_ADDRESS)
		    *ux_signal = SIGSEGV;
		else
		    *ux_signal = SIGBUS;
		break;

	    case EXC_BAD_INSTRUCTION:
	        *ux_signal = SIGILL;
		break;

	    case EXC_ARITHMETIC:
	        *ux_signal = SIGFPE;
		break;

	    case EXC_EMULATION:
		*ux_signal = SIGEMT;
		break;

	    case EXC_SOFTWARE:
		switch (code) {
		    case EXC_UNIX_BAD_SYSCALL:
			*ux_signal = SIGSYS;
			break;
		    case EXC_UNIX_BAD_PIPE:
		    	*ux_signal = SIGPIPE;
			break;
		}
		break;

	    case EXC_BREAKPOINT:
		*ux_signal = SIGTRAP;
		break;
	}
}
