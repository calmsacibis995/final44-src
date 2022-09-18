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
 * $Log:	syscall_subr.c,v $
 * Revision 2.21  92/03/27  18:37:49  mja
 * 	Added missing volatile in thread_depress_priority. Pointed out by
 * 	 pds.
 * 	[92/03/25            danner]
 * 
 * Revision 2.20  91/06/24  16:37:15  mbj
 * 	Acquire unix_master() lock for syscalls which need it.
 * 	[91/06/11            mbj]
 * 
 * 	Moved check for signals from htg_unix_syscall_common() out to the
 * 	machine dependent htg_unix_syscall() routines.  The htg_unix_syscall()
 * 	return value must be stored at the appropriate u.u_ar0 location before
 * 	any signal frames are constructed or else it will not be correctly
 * 	reflected in the constructed sigcontext.
 * 	[91/06/07            mbj]
 * 
 * Revision 2.19  91/05/24  15:40:38  mbj
 * 	Support emulation of negative system calls.
 * 	[91/05/24  12:59:25  mbj]
 * 
 * 	Changed htg_unix_syscall() into htg_unix_syscall_common() which is now
 * 	called by machine dependent htg_unix_syscall() routines.  Have
 * 	htg_unix_common() return the Mach status code KERN_ABORTED to indicate
 * 	that JUSTRETURN handling is needed.  This allows htg_unix_syscall() to
 * 	work correctly for syscalls such as SYS_sigreturn.  Also, return
 * 	Mach status codes such KERN_INVALID_ADDRESS for actual Mach errors.
 * 	[91/05/17  13:44:18  mbj]
 * 
 * Revision 2.18  91/04/02  12:14:10  mbj
 * 	In htg_unix_syscall() copy in r_val2 from rv->rv_val2 so that
 * 	the second return value is preserved if not explicitly set.
 * 	[91/03/28            mbj]
 * 
 * 	Initialize r_val1 to 0 before calling syscall subroutines.  Many
 * 	of these expect to be able to return 0 without setting r_val1.
 * 
 * 	Check for signals on the way out of htg_unix_syscall().
 * 	[91/03/21            mbj]
 * 
 * Revision 2.17  89/12/22  15:53:23  rpd
 * 	Only check counts on a multiprocessor; thread_block does these
 * 	checks anyway, but grabs a lock to do them.
 * 	[89/12/01            dlb]
 * 	Check runq counts in swtch() and thread_switch() before calling
 * 	thread_block().
 * 	[89/11/20            dlb]
 * 	Set first_quantum to true when switching to a fixed-priority
 * 	thread.
 * 	[89/11/15            dlb]
 * 	Encase fixed priority support code in MACH_FIXPRI switch.
 * 	[89/11/10            dlb]
 * 
 * Revision 2.16  89/11/20  11:24:10  mja
 * 	Set first_quantum to true when switching to a fixed-priority
 * 	thread.
 * 	[89/11/15            dlb]
 * 	Encase fixed priority support code in MACH_FIXPRI switch.
 * 	[89/11/10            dlb]
 * 
 * Revision 2.15  89/10/11  14:27:10  dlb
 * 	Cope with new timeout_scaling factor units.
 * 	Always restore depressed priority when thread runs again.
 * 	       Insightful suggestion courtesy of mwyoung.
 * 	Set up first_quantum flag and priority for new thread when
 * 	       switching to a fixed priority thread in thread_switch.
 * 	Add thread_switch().
 * 	Change priorities to 0-31 from 0-127.
 * 	Added check for zero length mapping request to map_fd.
 * 
 * Revision 2.14  89/08/02  08:03:41  jsb
 * 	Cleaned up and corrected inode type checks in map_fd, allowing
 * 	map_fd to work on afs and nfs files.
 * 	[89/07/17            jsb]
 * 
 * Revision 2.13  89/05/21  22:27:30  mrt
 * 	Put in Glenn's fix in map_fd to have MACH_VFS case call
 * 	getvnodefp instead of getinode.
 * 	[89/05/21            mrt]
 * 
 * Revision 2.12  89/05/01  17:01:39  rpd
 * 	Added mach_sctimes_port_alloc_dealloc (under MACH_SCTIMES).
 * 	[89/05/01  13:59:45  rpd]
 * 
 * Revision 2.11  89/04/22  15:24:59  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	Removed old MACH ctimes() system call.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.10  89/02/25  18:08:54  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.9  89/01/18  00:50:31  jsb
 * 	Vnode support, including changing EREMOTE to ERFSREMOTE.
 * 	[89/01/17  10:19:30  jsb]
 * 
 * Revision 2.8  88/12/19  02:47:17  mwyoung
 * 	Removed lint.
 * 	[88/12/17            mwyoung]
 * 
 * Revision 2.7  88/10/27  10:47:42  rpd
 * 	Added a bunch of syscalls, conditional under MACH_SCTIMES.
 * 	[88/10/26  14:43:08  rpd]
 * 
 * Revision 2.6  88/08/30  00:05:41  mwyoung
 * 	Turned off handling of CS system calls in htg_unix_syscall.  The
 * 	old code was conditionalized on CS_SYSCALL, but the option file
 * 	was never included, so the code never got compiled.  Well, until
 * 	the CS_SYSCALL was converted to CMUCS... then it wouldn't compile.
 * 	[88/08/28            mwyoung]
 * 
 * Revision 2.5  88/08/25  18:18:36  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Reimplement map_fd using vm_map.
 * 	[88/08/20  03:11:12  mwyoung]
 * 
 * Revision 2.4  88/08/03  15:35:37  dorr
 * Make htg_unix_syscall use return value to indicate
 * failure/success, return special error for restartable
 * syscalls, and return errno as the first return value when
 * applicable.
 * 
 * 10-May-88  Douglas Orr (dorr) at Carnegie-Mellon University
 *	Make htg_unix_syscall use return value to indicate
 *	failure/success, return special error for restartable
 *	syscalls, and return errno as the first return value when
 *	applicable.
 *
 * 26-Apr-88  Alessandro Forin (af) at Carnegie-Mellon University
 *	Fixed syscall_setjmp -> setjmp in htg_unix_syscall.
 *
 * 01-Mar-88  Douglas Orr (dorr) at Carnegie-Mellon University
 *	Added htg_unix_syscall
 *
 * 18-Dec-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Added an extra pair of parens to make map_fd work correctly.
 *
 *  6-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed calling sequence to inode_pager_setup().
 *	Removed old history.
 *
 * 19-Nov-87  Michael Jones (mbj) at Carnegie-Mellon University
 *	Make sure fd passed to map_fd references a local inode before
 *	calling getinode, since getinode will panic for map_fd of RFS files.
 *
 * 11-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS: changes to map_fd and ctimes.
 *
 * 19-Jun-87  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TT: boolean for swtch and swtch_pri is now whether there is
 *	other work that the kernel could run instead of this thread.
 *
 *  7-May-87  David Black (dlb) at Carnegie-Mellon University
 *	New versions of swtch and swtch_pri for MACH_TT.  Both return a
 *	boolean indicating whether a context switch was done.  Documented.
 *
 * 31-Jul-86  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Changed TPswtch_pri to set p_pri to 127 to make sure looping
 *	processes which want to simply reschedule do not monopolize the
 *	cpu.
 *
 *  3-Jul-86  Fil Alleva (faa) at Carnegie-Mellon University
 *	Added TPswtch_pri().  [Added to Mach, 20-jul-86, mwyoung.]
 *
 */

#include <mach_emulation.h>
#include <mach_fixpri.h>
#include <mach_sctimes.h>
#include <mach_vfs.h>
#include <stat_time.h>
#include <cpus.h>

#include <kern/thread.h>
#include <mach/thread_switch.h>

#include <sys/user.h>
#include <sys/proc.h>

#include <mach/boolean.h>
#include <kern/ipc_pobj.h>
#include <kern/kern_port.h>
#include <kern/sched.h>
#include <kern/sched_prim_macros.h>
#include <kern/thread.h>
#if	MACH_EMULATION
#include <kern/syscall_emulation.h>
#include <vice.h>
#include <kern/parallel.h>
#if	MACH_RFS
#ifndef	SYSCALLTRACE
#define	SYSCALLTRACE
#endif	SYSCALLTRACE
#endif	MACH_RFS
#include <kern/xpr.h>
#endif	MACH_EMULATION
#include <machine/cpu.h>
#include <kern/processor.h>
#if	MACH_SCTIMES
#include <mach/port.h>
#include <vm/vm_kern.h>
#endif	MACH_SCTIMES

#if	MACH_FIXPRI
#include <mach/policy.h>
#endif	MACH_FIXPRI

/*
 *	Note that we've usurped the name "swtch" from its
 *	previous use.
 */

/*
 *	swtch and swtch_pri both attempt to context switch (logic in
 *	thread_block no-ops the context switch if nothing would happen).
 *	A boolean is returned that indicates whether there is anything
 *	else runnable.
 *
 *	This boolean can be used by a thread waiting on a
 *	lock or condition:  If FALSE is returned, the thread is justified
 *	in becoming a resource hog by continuing to spin because there's
 *	nothing else useful that the processor could do.  If TRUE is
 *	returned, the thread should make one more check on the
 *	lock and then be a good citizen and really suspend.
 */

void thread_depress_priority();
kern_return_t thread_depress_abort();

boolean_t swtch()
{
	register processor_t	myprocessor;

#if	NCPUS > 1
	myprocessor = current_processor();
	if (myprocessor->runq.count == 0 &&
	    myprocessor->processor_set->runq.count == 0)
		return(FALSE);
#endif	NCPUS > 1

	thread_block();

	myprocessor = current_processor();
	return(myprocessor->runq.count > 0 ||
	    myprocessor->processor_set->runq.count > 0);
}

boolean_t  swtch_pri(pri)
	int pri;
{
	register boolean_t	result;
	register thread_t	thread = current_thread();
#ifdef	lint
	pri++;
#endif	lint

	/*
	 *	XXX need to think about depression duration.
	 *	XXX currently using min quantum.
	 */
	thread_depress_priority(thread, min_quantum);
	result = swtch();
	if (thread->depress_priority >= 0)
		thread_depress_abort(thread);
	return(result);
}

extern unsigned int timeout_scaling_factor;

/*
 *	thread_switch:
 *
 *	Context switch.  User may supply thread hint.
 *
 *	Fixed priority threads that call this get what they asked for
 *	even if that violates priority order.
 */
kern_return_t thread_switch(thread_name, option, option_time)
int	thread_name, option, option_time;
{
    register thread_t		cur_thread = current_thread();
    register processor_t	myprocessor;
    kern_port_t			port;

    /*
     *	Process option.
     */
    switch (option) {
	case SWITCH_OPTION_NONE:
	    /*
	     *	Nothing to do.
	     */
	    break;

	case SWITCH_OPTION_DEPRESS:
	    /*
	     *	Depress priority for given time.
	     */
	    thread_depress_priority(cur_thread, option_time);
	    break;

	case SWITCH_OPTION_WAIT:
	    thread_will_wait_with_timeout(cur_thread,
		(1000*option_time)/timeout_scaling_factor);
	    break;

	default:
	    return(KERN_INVALID_ARGUMENT);
    }
    
    /*
     *	Check and act on thread hint if appropriate.
     */
    if (thread_name != 0 &&
	port_translate(cur_thread->task, thread_name, &port)) {
	    /*
	     *	Get corresponding thread.
	     */
	    if (port_object_type(port) == PORT_OBJECT_THREAD) {
		register thread_t thread;
		register int s;

		thread = (thread_t) port_object_get(port);
		/*
		 *	Check if the thread is in the right pset. Then
		 *	pull it off its run queue.  If it
		 *	doesn't come, then it's not eligible.
		 */
		s = splsched();
		thread_lock(thread);
		if ((thread->processor_set == cur_thread->processor_set)
		    && (rem_runq(thread) != RUN_QUEUE_NULL)) {
			/*
			 *	Hah, got it!!
			 */
			thread_unlock(thread);
			(void) splx(s);
			port_unlock(port);
#if	MACH_FIXPRI
			if (thread->policy == POLICY_FIXEDPRI) {
			    myprocessor = current_processor();
			    myprocessor->quantum = thread->sched_data;
			    myprocessor->first_quantum = TRUE;
			}
#endif	MACH_FIXPRI
			thread_run(thread);
			/*
			 *  Restore depressed priority			 
			 */
			if (cur_thread->depress_priority >= 0)
				thread_depress_abort(cur_thread);

			return(KERN_SUCCESS);
		}
		thread_unlock(thread);
		(void) splx(s);
	    }
	    port_unlock(port);
    }

    /*
     *	No handoff hint supplied, or hint was wrong.  Call thread_block() in
     *	hopes of running something else.  If nothing else is runnable,
     *	thread_block will detect this.  WARNING: thread_switch with no
     *	option will not do anything useful if the thread calling it is the
     *	highest priority thread (can easily happen with a collection
     *	of timesharing threads).
     */
#if	NCPUS > 1
    myprocessor = current_processor();
    if (myprocessor->processor_set->runq.count > 0 ||
	myprocessor->runq.count > 0)
#endif	NCPUS > 1
	    thread_block();

    /*
     *  Restore depressed priority			 
     */
    if (cur_thread->depress_priority >= 0)
	thread_depress_abort(cur_thread);
    return(KERN_SUCCESS);
}

/*
 *	thread_depress_priority
 *
 *	Depress thread's priority to lowest possible for specified period.
 *	Intended for use when thread wants a lock but doesn't know which
 *	other thread is holding it.  As with thread_switch, fixed
 *	priority threads get exactly what they asked for.  Users access
 *	this by the SWITCH_OPTION_DEPRESS option to thread_switch.
 */
void
thread_depress_priority(thread, depress_time)
register thread_t thread;
int	depress_time;
{
    int		s;
    void	thread_depress_timeout();

    depress_time = (1000*depress_time)/timeout_scaling_factor;

    s = splsched();
    thread_lock(thread);

    /*
     *	If thread is already depressed, override previous depression.
     */
    if (thread->depress_priority >= 0) {
#if NCPUS > 1
	if (untimeout_try(thread_depress_timeout, thread) == FALSE) {
	  volatile int *depress_priority;
	    /*
	     *	Handle multiprocessor race condition.  Some other processor
	     *	is trying to timeout the old depress.  This should be rare.
	     */
	    thread_unlock(thread);
	    (void) splx(s);

	    /*
	     *	Wait for the timeout to do its thing.
	     */
	    depress_priority = &(thread->depress_priority);
	    while (*depress_priority >= 0)
	       continue;

	    /*
	     * Relock the thread and depress its priority.
	     */
	    s = splsched();
	    thread_lock(thread);

	    thread->depress_priority = thread->priority;
	    thread->priority = 31;
	    thread->sched_pri = 31;
	}
#else	NCPUS > 1
	untimeout(thread_depress_timeout, thread);
#endif	NCPUS > 1
    }
    else {
	/*
	 *	Save current priority, then set priority and
	 *	sched_pri to their lowest possible values.
	 */
	thread->depress_priority = thread->priority;
	thread->priority = 31;
        thread->sched_pri = 31;
    }
    timeout(thread_depress_timeout, (caddr_t)thread, depress_time);

    thread_unlock(thread);
    (void) splx(s);

}	
    
/*
 *	thread_depress_timeout:
 *
 *	Timeout routine for priority depression.
 */
void
thread_depress_timeout(thread)
register thread_t thread;
{
    int s;

    s = splsched();
    thread_lock(thread);
    /*
     *	Make sure thread is depressed, then undepress it.
     */
    if (thread->depress_priority >= 0) {
	thread->priority = thread->depress_priority;
	thread->depress_priority = -1;
	compute_priority(thread);
    }
    else {
	panic("thread_depress_timeout: thread not depressed!");
    }
    thread_unlock(thread);
    (void) splx(s);
}

/*
 *	thread_depress_abort:
 *
 *	Prematurely abort priority depression if there is one.
 */
kern_return_t
thread_depress_abort(thread)
register thread_t	thread;
{
    kern_return_t	ret = KERN_SUCCESS;
    int	s;

    if (thread == THREAD_NULL) {
	return(KERN_INVALID_ARGUMENT);
    }

    s = splsched();
    thread_lock(thread);
    
    /*
     *	Only restore priority if thread is depressed and we can
     *	grab the depress timeout off of the callout queue.
     */
    if (thread->depress_priority >= 0) {
#if	NCPUS > 1
	if (untimeout_try(thread_depress_timeout, thread)) {
#else	NCPUS > 1
	untimeout(thread_depress_timeout, thread);
#endif	NCPUS > 1
	    thread->priority = thread->depress_priority;
	    thread->depress_priority = -1;
	    compute_priority(thread);
#if	NCPUS > 1
	}
	else {
	    ret = KERN_FAILURE;
	}
#endif	NCPUS > 1
    }

    thread_unlock(thread);
    (void) splx(s);
    return(ret);
}

/* Many of these may be unnecessary */
#include <sys/systm.h>
#include <sys/mount.h>
#include <sys/fs.h>
#include <sys/buf.h>
#include <sys/inode.h>
#include <sys/dir.h>
#include <sys/quota.h>
#include <sys/kernel.h>
#include <sys/file.h>

#include <mach/kern_return.h>
#include <kern/task.h>
#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <mach/memory_object.h>
#include <builtin/inode_pager.h>

map_fd(fd, offset, va, findspace, size)
	int		fd;
	vm_offset_t	offset;
	vm_offset_t	*va;
	boolean_t	findspace;
	vm_size_t	size;
{
	struct file	*fp;
	register struct inode	*ip;
	vm_map_t	user_map = current_task()->map;
	kern_return_t	result;
	vm_offset_t	user_addr;
	memory_object_t	pager;

	if (size == 0)
		return(KERN_INVALID_ARGUMENT);

	/*
	 *	Find the inode; verify that it's a regular file.
	 */
	if ((fp = getf(fd)) == NULL || fp->f_type != DTYPE_INODE)
		return(KERN_INVALID_ARGUMENT);
	ip = (struct inode *)fp->f_data;

	if (findspace) {
		user_addr = VM_MIN_ADDRESS;
	}
	else {
		/*
		 *	Get user's address, and eliminate the
		 *	previous contents.
		 */

		if (copyin(va, &user_addr, sizeof(vm_offset_t)))
			return(KERN_INVALID_ADDRESS);
		if ((result = vm_deallocate(user_map, user_addr, size))
				!= KERN_SUCCESS)
			return(result);
	}

	/*
	 *	Map in the file.
	 */

	pager = inode_pager_setup(ip, FALSE, FALSE);
	if (pager == MEMORY_OBJECT_NULL)
		return(KERN_INVALID_ARGUMENT);

	result = vm_map(user_map, &user_addr, size, 0, findspace,
			pager, offset, TRUE,
			VM_PROT_ALL, VM_PROT_ALL, VM_INHERIT_COPY);

	inode_pager_release(pager);

	if (findspace && copyout(&user_addr, va, sizeof(vm_offset_t))) {
		(void) vm_deallocate(user_map, user_addr, size);
		return(KERN_INVALID_ADDRESS);
	}

	return(result);
}


#if	MACH_EMULATION

#ifdef	SYSCALLTRACE
int syscalltrace;
#endif	SYSCALLTRACE

/*
 *	honest-to-god_unix_syscall_common: 
 * 
 * Calls the indicated syscall, passing the given args and returning result(s),
 * error and eosys in rv.  All machine dependent manipulations such as placing
 * special arguments in saved register areas and handling JUSTRETURN register
 * restores are done in machine dependent htg_unix_syscall() routines.  It is
 * intended to be a general way of providing kernel syscall services in an
 * emulation environment (for when it absolutely, positively has to be a
 * syscall).
 * 
 * Returns:
 * 	KERN_SUCCESS	Result(s) in rv[0] (and rv[1])
 * 	KERN_FAILURE	Errno value in rv[0]
 * 	KERN_ABORTED	Causes htg_unix_syscall() routines to JUSTRETURN
 * 	otherwise	Mach error detected (such as KERN_INVALID_ADDRESS)
 * 
 * An eosys of RESTARTSYS is returned as an errno of ERESTART.
 */
kern_return_t
htg_unix_syscall_common( code, argv, rv )
	int		code;		/* syscall # */
	caddr_t		* argv;		/* arg vector */
	syscall_val_t 	* rv;
{
	extern int nsysent, ncmusysent;
	extern struct sysent cmusysent[];
	struct sysent 	* callp;
	boolean_t	invalid_addr = FALSE;
#if	NCPUS > 1
	thread_t	t = current_thread();
#endif	NCPUS > 1

	callp = (code >= 0)
		? ((code < nsysent) ? &sysent[code] : &sysent[63])
		: ((code >= -ncmusysent) ? &cmusysent[code + ncmusysent]
					 : &sysent[63]);

	/* copy in the user args */
	if (copyin(&rv->rv_val2, &u.u_r.r_val2, sizeof(u.u_r.r_val2))) {
		return KERN_INVALID_ADDRESS;
	}
	if (callp->sy_narg) {
		if (copyin(argv, (caddr_t)u.u_arg, (callp->sy_narg)*NBPW)) {
			return KERN_INVALID_ADDRESS;
		}
	}
	u.u_ap = u.u_arg;
	u.u_error = 0;
	u.u_r.r_val1 = 0;

#if	NCPUS > 1
	if (callp->sy_parallel == 0) {
		/*
		 *	System call must execute on master cpu
		 */
		if (t->unix_lock != -1)
			panic("htg unix_master(): unix_lock != -1");
		unix_master();	/* hold to master during syscall */
	}
#endif	NCPUS > 1

	if (setjmp(&u.u_qsave)) {
		unix_reset();
		if (u.u_error == 0 && u.u_eosys != RESTARTSYS)
			u.u_error = EINTR;
	} else {
		u.u_eosys = NORMALRETURN;

#ifdef	SYSCALLTRACE
		if (syscalltrace && 
		    (syscalltrace == u.u_procp->p_pid || syscalltrace < 0)) {
			register int i;
			char *cp;

			printf("[%d]htg %d", u.u_procp->p_pid, code);
			cp = "(";
			for (i= 0; i < callp->sy_narg; i++) {
				printf("%s%x", cp, u.u_arg[i]);
				cp = ", ";
			}
 			if (i)
				cp = ")";
			else
				cp = "";
			printf("%s\n", cp);
		}
#endif	SYSCALLTRACE
		XPR(XPR_SYSCALLS, ("htg syscall start: %c%c%c%c%c%c\n",
			u.u_comm[0], u.u_comm[1], u.u_comm[2],
			u.u_comm[3], u.u_comm[4], u.u_comm[5]));
		XPR(XPR_SYSCALLS, 
		("htg syscall start %d: args=0x%x, 0x%x, 0x%x, 0x%x\n", 
			code, u.u_arg[0], u.u_arg[1], u.u_arg[2],
			u.u_arg[3], u.u_arg[4]));
#if	MACH_RFS
		/*
		 *  Remember the system call we are executing so that it
		 *  can be handled remotely if need be.
		 */
		u.u_rfsncnt = 0;
		u.u_rfscode = code;
#endif	MACH_RFS
#if	VICE
		u.u_rmt_ncnt = 0;
		u.u_rmt_code = code;
#endif	VICE
		/*
		 *  Show no resource pause conditions.
		 */
		u.u_rpswhich = 0;
		u.u_rpsfs = 0;

		/* actually call the routine */
		(*(callp->sy_call))(u.u_ap);
	}

#if	MACH_RFS
	/*
	 *  SEE NOTE in syscall()
	 */
	if (u.u_error == ERFSREMOTE)
		u.u_error = 0;
	u.u_rfscode = 0;
#endif	MACH_RFS
#if	VICE
	if (u.u_error == EVICEOP)
		u.u_error = 0;
	u.u_rmt_code = 0;
#endif	VICE
	switch (u.u_error)
	{
	    case EDQUOT:	/* temp == ENOSPC */
	    case ENOSPC:
		/*
		 *  SEE NOTE in syscall()
		 */
		if (fspause(0))
			u.u_eosys = RESTARTSYS;
		break;

	    /*
	     *  TODO:  Handle these error numbers, also.
	     */
	    case EAGAIN:
	    case ENOMEM:
	    case ENFILE:
		break;
	}
	XPR(XPR_SYSCALLS, 
	    ("htg syscall end: pid=%d, code=%d, error=%d, val1=%d, rval2=%d\n",
	    u.u_procp->p_pid, code, u.u_error, u.u_r.r_val1, u.u_r.r_val2));

#if	NCPUS > 1
	/*
	 *	It is OK to go back on a slave
	 */
	if (callp->sy_parallel == 0) {
		unix_release();
		if (t->unix_lock != -1) {
			printf("htg <%d>: released unix_lock = %d\n",
				u.u_procp-proc, t->unix_lock);
			panic("htg unix_release(): unix_lock != -1");
		}
	}
#endif	NCPUS > 1

	/*
	 *  return the error bit, the eosys indicator (so the
	 *  caller can restart the syscall) and the two potential
	 *  return values
	 */
	if (u.u_eosys == RESTARTSYS) u.u_error = ERESTART;
	if (u.u_error) u.u_r.r_val1 = u.u_error;

	if (u.u_eosys != JUSTRETURN &&
	    (copyout(&u.u_r.r_val1, &rv->rv_val1, sizeof(rv->rv_val1)) ||
	     copyout(&u.u_r.r_val2, &rv->rv_val2, sizeof(rv->rv_val2))))
		invalid_addr = TRUE;

	if (u.u_eosys == JUSTRETURN) {
		/*
		 * Don't return a kern_return -- just use the register
		 * values set by the system call.
		 */
		return KERN_ABORTED;
	}
	if (invalid_addr) return KERN_INVALID_ADDRESS;
	return( u.u_error ? KERN_FAILURE : KERN_SUCCESS );

}
#endif	MACH_EMULATION

#if	MACH_SCTIMES
kern_return_t
mach_sctimes_0()
{
	return KERN_SUCCESS;
}

kern_return_t
mach_sctimes_1(arg0)
{
#ifdef	lint
	arg0++;
#endif	lint
	return KERN_SUCCESS;
}

kern_return_t
mach_sctimes_2(arg0, arg1)
{
#ifdef	lint
	arg0++; arg1++;
#endif	lint
	return KERN_SUCCESS;
}

kern_return_t
mach_sctimes_3(arg0, arg1, arg2)
{
#ifdef	lint
	arg0++; arg1++; arg2++;
#endif	lint
	return KERN_SUCCESS;
}

kern_return_t
mach_sctimes_4(arg0, arg1, arg2, arg3)
{
#ifdef	lint
	arg0++; arg1++; arg2++; arg3++;
#endif	lint
	return KERN_SUCCESS;
}

kern_return_t
mach_sctimes_5(arg0, arg1, arg2, arg3, arg4)
{
#ifdef	lint
	arg0++; arg1++; arg2++; arg3++; arg4++;
#endif	lint
	return KERN_SUCCESS;
}

kern_return_t
mach_sctimes_6(arg0, arg1, arg2, arg3, arg4, arg5)
{
#ifdef	lint
	arg0++; arg1++; arg2++; arg3++; arg4++; arg5++;
#endif	lint
	return KERN_SUCCESS;
}

kern_return_t
mach_sctimes_7()
{
	return KERN_SUCCESS;
}

kern_return_t
mach_sctimes_8(arg0, arg1, arg2, arg3, arg4, arg5)
{
#ifdef	lint
	arg0++; arg1++; arg2++; arg3++; arg4++; arg5++;
#endif	lint
	return KERN_SUCCESS;
}

vm_offset_t mach_sctimes_buffer = 0;
vm_size_t mach_sctimes_bufsize = 0;

kern_return_t
mach_sctimes_9(size)
	vm_size_t size;
{
	register kern_return_t kr;

	if (mach_sctimes_bufsize != 0)
		kmem_free(kernel_map, mach_sctimes_buffer,
			  mach_sctimes_bufsize);

	if (size == 0) {
		mach_sctimes_bufsize = 0;
		kr = KERN_SUCCESS;
	} else {
		mach_sctimes_buffer = kmem_alloc(kernel_map, size);
		if (mach_sctimes_buffer == 0) {
			mach_sctimes_bufsize = 0;
			kr = KERN_FAILURE;
		} else {
			mach_sctimes_bufsize = size;
			kr = KERN_SUCCESS;
		}
	}

	return kr;
}

kern_return_t
mach_sctimes_10(addr, size)
	char *addr;
	vm_size_t size;
{
	register kern_return_t kr;

	if (size > mach_sctimes_bufsize)
		kr = KERN_FAILURE;
	else if (copyin(addr, mach_sctimes_buffer, size))
		kr = KERN_FAILURE;
	else
		kr = KERN_SUCCESS;

	return kr;
}

kern_return_t
mach_sctimes_11(addr, size)
	char *addr;
	vm_size_t size;
{
	register kern_return_t kr;

	if (size > mach_sctimes_bufsize)
		kr = KERN_FAILURE;
	else if (copyout(mach_sctimes_buffer, addr, size))
		kr = KERN_FAILURE;
	else
		kr = KERN_SUCCESS;

	return kr;
}

kern_return_t
mach_sctimes_port_alloc_dealloc(times)
	int times;
{
	task_t self = current_task();
	int i;

	for (i = 0; i < times; i++) {
		port_name_t port;

		(void) port_allocate(self, &port);
		(void) port_deallocate(self, port);
	}

	return KERN_SUCCESS;
}
#endif	MACH_SCTIMES
