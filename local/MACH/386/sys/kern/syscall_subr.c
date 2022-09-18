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
 * Revision 2.14.2.2  91/03/29  17:30:20  rvb
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
#include <mach_sctimes.h>
#include <mach_vfs.h>

#include <kern/thread.h>

#include <sys/user.h>
#include <sys/proc.h>

#include <mach/boolean.h>
#include <kern/sched.h>
#if	MACH_EMULATION
#include <kern/syscall_emulation.h>
#include <vice.h>
#include <kern/parallel.h>
#endif	MACH_EMULATION
#include <machine/cpu.h>
#if	MACH_SCTIMES
#include <mach/port.h>
#include <vm/vm_kern.h>
#endif	MACH_SCTIMES

/*
 *	Note that we've usurped the name "swtch" from its
 *	previous use.
 */

/*
 *	swtch and swtch_pri both check to see if there's anything useful
 *	to context switch to.  If not no context switch occurs.  In any case
 *	a boolean is returned that indicates whether there is anything
 *	else that the kernel would rather run.
 *
 *	This boolean can be productively used by a thread waiting on a
 *	lock or condition:  If FALSE is returned, the thread is justified
 *	in becoming a resource hog by continuing to spin because there's
 *	nothing else useful that the processor could do.  If TRUE is
 *	returned, the thread should make one more check on the
 *	lock and then be a good citizen and really suspend.
 */

boolean_t swtch()
{
	register int mycpu;
	register boolean_t result;

	/*
	 *	Bump runrun to allow preemption by thread at same priority.
	 */
	runrun[cpu_number()]++;
	if (csw_check()) {
		u.u_ru.ru_nvcsw++;
		thread_block();

		mycpu = cpu_number();
		runrun[mycpu]++;
		result = csw_check();
		runrun[mycpu]--;
		return(result);
	}
	else {
		return(FALSE);
	}
	/*NOTREACHED*/
}

boolean_t swtch_pri(pri)
	int pri;
{
#ifdef	lint
	pri++;
#endif	lint

	u.u_procp->p_pri = 127;
	current_thread()->sched_pri = 127;
	return(swtch());
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
/*
 *	honest-to-god_unix_syscall: 
 *
 *	Calls the indicated syscall, passing the given args and returning
 *	result(s), error and eosys in rv.  htg_unix_syscall() is intended
 *	to be machine independent which is why it doesn't peel arguments off
 *	the user's stack, return results in registers, etc.  It is intended
 *	to be a general way of providing kernel syscall services in an
 *	emulation environment (for when it absolutely, positively has to be a syscall).
 */
htg_unix_syscall( code, argv, rv )
	int		code;		/* syscall # */
	caddr_t		* argv;		/* arg vector */
	syscall_val_t 	* rv;
{
	extern 		int nsysent;
	struct sysent 	* callp;
	int		syscalltrace = 0;
	register struct proc *p;

#if	0	/* Was CS_SYSCALL, but the option file was not included */
	if (code < -ncmusysent)
		callp = &sysent[63];
	else if (code < 0) 
		callp = &cmusysent[code + ncmusysent];
	else
		callp = (code >= nsysent) ? &sysent[63] : &sysent[code];
#else	0
	if (code < 0)
		code = 63;
	u.u_error = 0;
	callp = (code >= nsysent) ? &sysent[63] : &sysent[code];
#endif	0

	/* copy in the user args */
	if (copyin(&rv->rv_val2, &u.u_r.r_val2, sizeof(u.u_r.r_val2))) {
		u.u_error = EFAULT;
		goto bad;
	}
	if (callp->sy_narg) {
		if (copyin(argv, (caddr_t)u.u_arg, (callp->sy_narg)*NBPW)) {
			u.u_error = EFAULT;
			goto bad;
		}
	}
	u.u_ap = u.u_arg;

	/*
	 *	SUN swapped JUSTRETURN and NORMALRETURN - we swap
	 *	them back.
	 */
	u.u_error = 0;
	u.u_r.r_val1 = 0;

	if (setjmp(&u.u_qsave)) {
		if (u.u_error == 0 && u.u_eosys != RESTARTSYS)
			u.u_error = EINTR;
	} else {
		u.u_eosys = NORMALRETURN;

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

		if (syscalltrace) {
			register int i;
			char *cp;

			cp = "(";
			for (i= 0; i < callp->sy_narg; i++) {
				printf("%s%x", cp, u.u_arg[i]);
				cp = ", ";
			}
			if (i)
				putchar(')', 0);
			putchar('\n', 0);
		}

		/* actually call the routine */
		(*(callp->sy_call))(u.u_ap);

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
			    case ENOSPC:
				{
					/*
					 *  SEE NOTE in syscall()
					 */
					if (fspause(0))
						u.u_eosys = RESTARTSYS;
					break;
				}
				/*
				 *  TODO:  Handle these error numbers, also.
				 */
			    case EAGAIN:
			    case ENOMEM:
			    case ENFILE:
				break;
			}
		if (syscalltrace)
			printf( "rc=%x val=%x\n", u.u_error, u.u_r.r_val1 );
	}

    bad:
	/*
	 *  return the error bit, the eosys indicator (so the
	 *  caller can restart the syscall) and the two potential
	 *  return values
	 */
	if (u.u_eosys == RESTARTSYS) u.u_error = ERESTART;
	if (u.u_error) u.u_r.r_val1 = u.u_error;

	if ( copyout( &u.u_r.r_val1, &rv->rv_val1, sizeof(rv->rv_val1) ) 
	    || copyout( &u.u_r.r_val2, &rv->rv_val2, sizeof(rv->rv_val2) ) )
		/* 
		 * we're kind of stuck if we fault copying out the error.
		 * we don't want to return unix errors directly, because mach syscalls
		 * return kern_return_t's.  So, the syscall will fail with some
		 * bogus errno in this case.
		 */
		u.u_error = EFAULT;	

	p = u.u_procp;
	if (p) {
		if (CHECK_SIGNALS(p, current_thread()->u_address.uthread)) {
			unix_master();
			if (p->p_cursig || issig()) {
				psig();
			}
			unix_release();
		}
	}

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
