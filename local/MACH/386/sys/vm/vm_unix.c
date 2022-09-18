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
 * $Log:	vm_unix.c,v $
 * Revision 2.17  89/08/08  21:50:42  jsb
 * 	Preserve text and data start info in fakeu.  Needed for debuggers, to
 * 	look at corefiles without the info provided by the image file.
 * 	[89/07/25            af]
 * 
 * Revision 2.16  89/05/06  02:59:06  rpd
 * 	Purged task_by_pid.
 * 	[89/05/05  20:52:53  rpd]
 * 
 * Revision 2.15  89/04/22  15:35:37  gm0w
 * 	Changed to always use new user identity recorded in u.u_identity.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.14  89/04/18  21:30:08  mwyoung
 * 	History condensation:
 * 		Support for vnodes (jsb).
 * 		Routines to create a vm_object/memory_object for
 * 		 use by mmap() (jjc, mwyoung, dbg, rvb).
 * 		Routines to get task ports based on process ID  (mwyoung, rpd).
 * 		Routine to get fake "u" area (avie, dbg, dlb).
 * 		Process creation hackery (avie, mwyoung, dbg, dlb).
 * 		Basic glue for Mach VM: useracc, vslock, [fs]u{byte,word},
 * 		 etc. (mwyoung, avie, dbg).
 * 
 */

#include <cputypes.h>
#include <mach_debug.h>
#include <mach_xp.h>
#include <mach_emulation.h>

#include <kern/task.h>
#include <kern/thread.h>
#include <mach/time_value.h>
#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <vm/vm_page.h>
#include <kern/parallel.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/vm.h>
#include <sys/file.h>
#include <sys/inode.h>
#include <sys/buf.h>
#include <sys/mount.h>
#include <sys/trace.h>
#include <sys/map.h>
#include <sys/kernel.h>

#include <vm/vm_kern.h>
#include <mach/port.h>
#include <kern/kern_obj.h>
#include <kern/ipc_pobj.h>
#include <kern/ipc_copyout.h>

#include <mach/memory_object.h>

useracc(addr, len, prot)
	caddr_t	addr;
	u_int	len;
	int	prot;
{
	return (vm_map_check_protection(
			current_task()->map,
			trunc_page(addr), round_page(addr+len-1),
			prot == B_READ ? VM_PROT_READ : VM_PROT_WRITE));
}

vslock(addr, len)
	caddr_t	addr;
	int	len;
{
	vm_map_pageable(current_task()->map, trunc_page(addr),
				round_page(addr+len-1), FALSE);
}

vsunlock(addr, len, dirtied)
	caddr_t	addr;
	int	len;
	int dirtied;
{
#ifdef	lint
	dirtied++;
#endif	lint
	vm_map_pageable(current_task()->map, trunc_page(addr),
				round_page(addr+len-1), TRUE);
}

#if	defined(sun3) || defined(sun4) || balance || defined(i386) || defined(mips)
/* These architectures have faster assembly-language versions */
#else	defined(sun3) || defined(sun4) || balance || defined(i386) || defined(mips)
subyte(addr, byte)
	caddr_t addr;
	char byte;
{
	return (copyout((caddr_t) &byte, addr, sizeof(char)) == 0 ? 0 : -1);
}

suibyte(addr, byte)
	caddr_t addr;
	char byte;
{
	return (copyout((caddr_t) &byte, addr, sizeof(char)) == 0 ? 0 : -1);
}

int fubyte(addr)
	caddr_t addr;
{
	char byte;

	if (copyin(addr, (caddr_t) &byte, sizeof(char)))
		return(-1);
	return((unsigned) byte);
}

int fuibyte(addr)
	caddr_t addr;
{
	char byte;

	if (copyin(addr, (caddr_t) &byte, sizeof(char)))
		return(-1);
	return((unsigned) byte);
}

suword(addr, word)
	caddr_t addr;
	int word;
{
	return (copyout((caddr_t) &word, addr, sizeof(int)) == 0 ? 0 : -1);
}

int fuword(addr)
	caddr_t addr;
{
	int word;

	if (copyin(addr, (caddr_t) &word, sizeof(int)))
		return(-1);
	return(word);
}

#ifndef	vax
/* suiword and fuiword are the same as suword and fuword, respectively */

suiword(addr, word)
	caddr_t addr;
	int word;
{
	return (copyout((caddr_t) &word, addr, sizeof(int)) == 0 ? 0 : -1);
}

int fuiword(addr)
	caddr_t addr;
{
	int word;

	if (copyin(addr, (caddr_t) &word, sizeof(int)))
		return(-1);
	return(word);
}
#endif	vax
#endif	defined(sun3) || defined(sun4) || balance || defined(i386) || defined(mips)

swapon()
{
}

thread_t procdup(child, parent)
	struct proc *child, *parent;
{
	thread_t	thread;
	task_t		task;
 	kern_return_t	result;

	result = task_create(parent->task, TRUE, &task);
	if(result != KERN_SUCCESS)
	    printf("fork/procdup: task_create failed. Code: 0x%x\n", result);
	child->task = task;

	/* XXX Cheat to get proc pointer into task structure */
	task->proc_index = child - proc;

	result = thread_create(task, &thread);
	if(result != KERN_SUCCESS)
	    printf("fork/procdup: thread_create failed. Code: 0x%x\n", result);

	child->thread = thread;
	thread->priority = current_thread()->priority;
	/*
	 *	Don't need to lock thread here because it can't
	 *	possibly execute and no one else knows about it.
	 */
	compute_priority(thread);

	bcopy((caddr_t) parent->task->u_address,
	      (caddr_t) task->u_address,
	      (unsigned) sizeof(struct utask));
	bcopy((caddr_t) parent->thread->u_address.uthread,
	      (caddr_t) thread->u_address.uthread,
	      (unsigned) sizeof(struct uthread));
	thread->u_address.utask->uu_procp = child;
	bzero((caddr_t) &thread->u_address.utask->uu_ru,
			sizeof(struct rusage));
	bzero((caddr_t) &thread->u_address.utask->uu_cru,
			sizeof(struct rusage));
	thread->u_address.utask->uu_outime = 0;
#if	MACH_EMULATION	
	if (task->eml_dispatch = parent->task->eml_dispatch) {
		task->eml_dispatch->disp_count =
			parent->task->eml_dispatch->disp_count;
		task->eml_dispatch->eml_ref++;
	    }
#endif	MACH_EMULATION
	return(thread);
}

#ifndef	vax
chgprot(_addr, prot)
	caddr_t		_addr;
	vm_prot_t	prot;
{
	vm_offset_t	addr = (vm_offset_t) _addr;

	return(vm_map_protect(current_task()->map,
				trunc_page(addr),
				round_page(addr + 1),
				prot, FALSE) == KERN_SUCCESS);
}
#endif	vax

kern_return_t	unix_pid(t, x)
	task_t	t;
	int	*x;
{
	if (t == TASK_NULL) {
		*x = -1;
		return(KERN_FAILURE);
	} else {
		*x =  proc[t->proc_index].p_pid;
		return(KERN_SUCCESS);
	}
}

/*
 *	Routine:	task_by_unix_pid
 *	Purpose:
 *		Get the task port for another "process", named by its
 *		process ID on the same host as "target_task".
 *
 *		Only permitted to privileged processes, or processes
 *		with the same user ID.
 */
kern_return_t	task_by_unix_pid(target_task, pid, t)
	task_t		target_task;
	int		pid;
	task_t		*t;
{
	struct proc	*p;
	kern_return_t kr = KERN_SUCCESS;

	if ((target_task == TASK_NULL) ||
	    (target_task->proc_index == 0))
		return KERN_INVALID_ARGUMENT;

	unix_master();

	/* XXX groupmember(2) */

#if	MACH_DEBUG
	if (pid == -1) {
		if (groupmember(2) || suser())
			*t = kernel_task;
		else
			kr = KERN_PROTECTION_FAILURE;
	} else
#endif	MACH_DEBUG
	if (pid == 0) {
		if (groupmember(2) || suser())
			*t = proc[0].task;
		else
			kr = KERN_PROTECTION_FAILURE;
	} else if (((p = pfind(pid)) != (struct proc *) 0) &&
		   (p->p_stat != SZOMB)) {
		if ((p->p_uid == proc[target_task->proc_index].p_uid) ||
		    groupmember(2) ||
		    suser())
			*t = p->task;
		else
			kr = KERN_PROTECTION_FAILURE;
	} else
		kr = KERN_INVALID_ARGUMENT;

	unix_release();
	return kr;
}

#if	!MACH_XP
/*
 *	Header to point to a 'device' object and the list
 *	of page structures allocated for it.
 */
struct dev_pager {
	boolean_t	is_device;	/* !is_device ==> this is an istruct.
					   used by vm */
    	vm_object_t	object;
	vm_offset_t	start;	/* start... */
	vm_size_t	size;	/* and size of memory allocated
				   to hold vm_page structures */
};
typedef struct dev_pager	*dev_pager_t;

/*
 *	Create an object to represent pre-existing physical memory
 *	attached to a device (e.g., a frame buffer).
 *
 *	Parameters:
 *		dev		Device that object should map
 *		mapfun		Returns the physical page number
 *				for a page within the device
 *		prot		Protection code to pass to mapfun
 *		offset		Byte offset within device to start
 *				mapping (a page multiple)
 *		size		Number of bytes to map (a page
 *				multiple).
 *	Assumptions:
 *		If the VM page size is N machine pages, those N pages
 *		are physically contiguous, as there is only one VM page
 *		structure to map all N of those pages.  This is NOT
 *		checked.
 *		
 *
 */
memory_object_t memory_object_special(dev, mapfun, prot, offset, size)
	dev_t		dev;
	int		(*mapfun)();
	int		prot;
	vm_offset_t	offset;
	vm_size_t	size;
{
	memory_object_t	memory_object;
	vm_object_t	object;
	int		num_pages;
	vm_offset_t	memory_start;
	vm_size_t	memory_size;
	dev_pager_t	handle;
	vm_page_t	pg_cur;
	int		i;

	num_pages = atop(size);

	/*
	 *	Allocate an object
	 */
	object = vm_object_allocate(size);

	/*
	 *	Grab enough memory for vm_page structures to
	 *	represent all pages in the object, and a little
	 *	bit more for a handle on them.
	 */
	memory_size = round_page(num_pages * sizeof(struct vm_page)
				+ sizeof(struct dev_pager));
	memory_start = kmem_alloc(kernel_map, memory_size);

	handle = (dev_pager_t) memory_start;

	/*
	 *	Fill in the handle
	 */
	handle->is_device = TRUE;
	handle->object = object;
	handle->start  = memory_start;
	handle->size   = memory_size;

	/*
	 *	Fill in each page with the proper physical address,
	 *	and attach it to the object.  Mark it as wired-down
	 *	to keep the pageout daemon's hands off it.
	 */

	pg_cur = (vm_page_t) (memory_start + sizeof(struct dev_pager));
	for (i = 0;
	     i < num_pages;
	     i++, pg_cur++) {
#if	defined(sun3) || defined(sun4)
		int		pfn;
		unsigned int	type;
 
  		pg_cur->wire_count = 1;
		pfn = (*mapfun)(dev, offset + ptoa(i), prot);
		pg_cur->phys_addr = pmap_phys_address(pfn);
#else	defined(sun3) || defined(sun4)
		pg_cur->wire_count = 1;
		/*
		 *	mapfun takes a byte offset, but returns
		 *	a machine-dependent page number (was originally
		 *	a page-table entry, but we won't talk about that).
		 */
		pg_cur->phys_addr = (vm_offset_t) ptob((*mapfun)(dev,
							offset + ptoa(i),
							prot));
#endif	defined(sun3) || defined(sun4)
		/*
		 *	Don't need to lock object - it's not visible
		 *	to anything else.
		 */
		vm_page_insert(pg_cur, object, ptoa(i));
	}

	/*
	 *	Make the object's pager be the 'device' pager
	 *	so that the page structures will be deallocated.
	 *	They can't go onto the free page list!
	 */
	memory_object = (memory_object_t) handle;
	vm_object_setpager(object, memory_object, (vm_offset_t) 0, FALSE);
	vm_object_enter(object, memory_object);

	return (memory_object);
}


boolean_t device_pagein()
{
	panic("device_pagein called");
}

boolean_t device_pageout()
{
	panic("device_pageout called");
}

/*
 *	Deallocate the page structures allocated for a device pager
 */
boolean_t device_dealloc(pager)
	memory_object_t	pager;
{
	dev_pager_t	handle;
	vm_object_t	object;

	handle = (dev_pager_t) pager;
	object = handle->object;

	/*
	 *	Remove all page structures from the object.
	 *	The object does not need to be locked, since all
	 *	references to it are gone.
	 */
	while (!queue_empty(&object->memq)) {
		vm_page_t	p;

		p = (vm_page_t) queue_first(&object->memq);
		vm_page_remove(p);
	}

	/*
	 *	Free the memory allocated for the page structures
	 *	and handle.
	 */

	kmem_free(kernel_map, handle->start, handle->size);
}
#endif	!MACH_XP

/*
 *	fake_u:
 *
 *	fake a u-area structure for the specified thread.  Only "interesting"
 *	fields are filled in.
 */
fake_u(up, thread)
	register struct user	*up;
	register thread_t	thread;
{
	register struct utask	*utask;
	register struct uthread	*uthread;
	time_value_t	sys_time, user_time;
	register int	s;

	utask = thread->u_address.utask;
	uthread = thread->u_address.uthread;
#undef	u_pcb
	up->u_pcb = *(thread->pcb);
#ifdef	vax
	/*	HACK HACK HACK	- keep adb happy	*/
	up->u_pcb.pcb_ksp = (up->u_pcb.pcb_ksp & 0x0FFFFFFF) | 0x70000000;
	/*	HACK HACK HACK	- keep adb happy	*/
#endif	vax
#undef	u_comm
	bcopy(utask->uu_comm, up->u_comm, sizeof(up->u_comm));
#undef	u_arg
	bcopy((caddr_t)uthread->uu_arg, (caddr_t)up->u_arg, sizeof(up->u_arg));
#undef  u_identity
	up->u_identity = utask->uu_identity;
#undef	u_tsize
	up->u_tsize = utask->uu_tsize;
#undef	u_dsize
	up->u_dsize = utask->uu_dsize;
#undef	u_ssize
	up->u_ssize = utask->uu_ssize;
#undef	u_data_start
	up->u_data_start = utask->uu_data_start;
#undef	u_text_start
	up->u_text_start = utask->uu_text_start;
#undef	u_signal
	bcopy((caddr_t)utask->uu_signal,
	      (caddr_t)up->u_signal,
	      sizeof(up->u_signal));
#undef	u_code
	up->u_code = uthread->uu_code;
#undef	u_procp
	up->u_procp = utask->uu_procp;
#undef	u_ru
	up->u_ru = utask->uu_ru;
	/*
	 *	Times aren't in uarea any more.
	 */
	s = splsched();
	thread_lock(thread);
	thread_read_times(thread, &user_time, &sys_time);
	thread_unlock(thread);
	splx(s);
	up->u_ru.ru_stime.tv_sec = sys_time.seconds;
	up->u_ru.ru_stime.tv_usec = sys_time.microseconds;
	up->u_ru.ru_utime.tv_sec = user_time.seconds;
	up->u_ru.ru_utime.tv_usec = user_time.microseconds;
#undef	u_cru
	up->u_cru = utask->uu_cru;
}
