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
 * $Log:	kern_mman.c,v $
 * Revision 2.16  89/07/11  13:08:40  jjc
 * 	Changed grow() to do an unsigned comparison between the
 * 	amount to grow the stack and the limit, and convert SINCR
 * 	to bytes not clicks in calculation of amount to grow by.
 * 	[89/01/23            jjc]
 * 
 * Revision 2.15  89/05/30  10:33:35  rvb
 * 	Removed inclusion of psl.h for mips too.
 * 	[89/05/15            af]
 * 
 * Revision 2.14  89/04/22  15:20:36  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.13  89/03/09  19:28:38  rpd
 * 	More cleanup.
 * 
 * Revision 2.12  89/02/25  14:28:28  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.11  89/02/09  04:31:09  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.10  89/01/18  00:36:27  jsb
 * 	Vnode support.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.9  88/12/13  12:02:28  mikeg
 * 	Enclosed modifications to smmap for Suntools in "#ifdef sun"
 * 	conditionals.
 * 
 * Revision 2.8  88/12/08  15:35:24  mikeg
 * 	Modified smmap so that a call to mmap that invokes winmmap
 * 	will have the requested memory marked as MAP_PRIVATE.  This
 * 	allows Suntools to run under Mach.
 * 	[88/11/30  10:18:55  mikeg]
 * 
 * Revision 2.6  88/10/25  03:38:26  mwyoung
 * 	MACH_XP: Get the right offset for objects managed by the
 * 	device_pager.
 * 	[88/10/25            mwyoung]
 * 
 * Revision 2.5  88/10/11  12:07:00  rpd
 * 	Correct mmap() to copy data for MAP_PRIVATE; allow private
 * 	mappings to later increase privileges on the mapped region.
 * 	(From mwyoung.)
 * 	[88/10/11  12:01:46  rpd]
 * 
 * Revision 2.4  88/08/25  18:10:27  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Eliminate old variables in smmap.
 * 	[88/08/21            mwyoung]
 * 	
 * 	Use memory_object_special when not MACH_XP; condense all of
 * 	the mapping operations to a single vm_map call.
 * 	[88/08/21  18:17:24  mwyoung]
 * 	
 * 	Vast simplification of mmap() through use of vm_map().
 * 	Further simplification would be possible if vm_object_special()
 * 	returned a memory object suitable for use in vm_map() instead of
 * 	a vm_object.
 * 	[88/08/20  03:07:54  mwyoung]
 * 
 * Revision 2.3  88/07/17  17:38:39  mwyoung
 * Use new memory object types.
 * 
 * Print the name of the process that can't sbrk.
 * 
 * Revision 2.2.1.2  88/07/04  15:18:40  mwyoung
 * Use new memory object types.
 * 
 * Revision 2.2.1.1  88/06/28  20:14:25  mwyoung
 * Print the name of the process that can't sbrk.
 * 
 *
 *  9-May-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Print the name of the process that can't sbrk.
 *
 * 16-Feb-88  David Golub (dbg) at Carnegie-Mellon University
 *	Correct fix below to return proper U*X return code.  Check that
 *	mapfun is not NULL, nulldev, or nodev when mapping devices.
 *
 * 30-Jan-88  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Added check to smmap to only work on local inodes.
 *
 * 30-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 *  6-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed inode_pager_setup() use to new interface.
 *	Removed meaningless history.
 *
 * 19-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS: Change inode references to vnodes.
 *
 *  9-Apr-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	MACH_XP: Turned off device file mmaping for the interim.
 *
 *  2-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Made mmap handle both special devices and files for all machines.
 *
 * 14-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Made mmap work for character devices to support (sun) frame
 *	buffers.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_mman.c	7.1 (Berkeley) 6/5/86
 */

#include <mach_xp.h>

#include <machine/reg.h>
#if	!defined(ibmrt) && !defined(mips)
#include <machine/psl.h>
#endif	!defined(ibmrt) && !defined(mips)

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/inode.h>
#include <sys/acct.h>
#include <sys/wait.h>
#include <sys/vm.h>
#include <sys/file.h>
#include <sys/vadvise.h>
#include <sys/trace.h>
#include <sys/mman.h>
#include <sys/conf.h>
#include <mach/kern_return.h>
#include <kern/task.h>
#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <mach/memory_object.h>
#include <builtin/inode_pager.h>
#if	MACH_XP
#include <builtin/device_pager.h>
#endif	MACH_XP

sbrk()
{

}

sstk()
{

}

getpagesize()
{

	u.u_r.r_val1 = NBPG * CLSIZE;
}

smmap()
{
	/*
	 *	Map in special device (must be SHARED) or file
	 */
	struct a {
		caddr_t	addr;
		int	len;
		int	prot;
		int	share;
		int	fd;
		off_t	pos;
	} *uap = (struct a *)u.u_ap;
	struct file *fp;
	register struct inode *ip;
	vm_map_t	user_map = current_task()->map;
	kern_return_t	result;
	vm_offset_t	user_addr = (vm_offset_t) uap->addr;
	vm_size_t	user_size = uap->len;
	off_t		file_pos = uap->pos;
	memory_object_t	pager;
	vm_offset_t	pager_offset;
	vm_prot_t	user_prot =
				(uap->prot & PROT_WRITE) ?
					VM_PROT_ALL :
					VM_PROT_READ|VM_PROT_EXECUTE;
	int		realshare = uap->share; /* For winmmap kluge */

#if	MACH_XP
#else	MACH_XP
	extern memory_object_t	memory_object_special();
#endif	MACH_XP

	/*
	 * Only work with local inodes.  Do not use getinode - it will
	 * try to invoke remote filesystem code, which will panic on smmap.
	 */

	GET_FD_FILE(uap->fd, fp);
	if (fp->f_type != DTYPE_INODE) {
		u.u_error = EINVAL;
		return;
	}
	ip = (struct inode *)fp->f_data;

	/*
	 *	We bend a little - round the start and end addresses
	 *	to the nearest page boundary.
	 */
	user_addr = trunc_page(user_addr);
	user_size = round_page(user_size);

	/*
	 *	File can be COPIED at an arbitrary offset.
	 *	File can only be SHARED if the offset is at a
	 *	page boundary.
	 *
	if (uap->share == MAP_SHARED &&
	    (trunc_page(file_pos) != (vm_offset_t)(file_pos))) {
		u.u_error = EINVAL;
		return;
	}

	/*
	 *	File must be writable if mapping will be.
	 */
	if ((uap->prot & PROT_WRITE) && (fp->f_flag&FWRITE) == 0) {
		u.u_error = EINVAL;
		return;
	}
	if ((uap->prot & PROT_READ) && (fp->f_flag&FREAD) == 0) {
		u.u_error = EINVAL;
		return;
	}

	/*
	 *	memory must exist and be writable (even if we're
	 *	just reading)
	 *
	 *	XXX Is this really part of the BSD spec for mmap?
	 *	We'll be replacing the address range anyway.
	 */

	if (!vm_map_check_protection(user_map, user_addr,
				(vm_offset_t)(user_addr + user_size),
				VM_PROT_READ|VM_PROT_WRITE)) {
		u.u_error = EINVAL;
		return;
	}

	if (INODE_TYPE(ip,CHR)) {
		/*
		 *	Map in special device memory.
		 *	Must be shared, since we can't assume that
		 *	this memory can be made copy-on-write.
		 */
		int		off;
		dev_t		dev;
		int		(*mapfun)();
		extern int	nodev();
		extern int	nulldev();
#ifdef	sun	/* Really, dependent on Suntools */
		extern int	winmmap(); /* Needed for Suntools kluge */
#endif	sun

		dev = INODE_RDEV(ip);
		mapfun = cdevsw[major(dev)].d_mmap;
		if (mapfun == nulldev || mapfun == nodev || mapfun == 0) {
			u.u_error = EINVAL;
			return;
		}

#ifdef	sun

	/*
	 *	The following modification is required for running Suntools.  If
	 *	this is a call to winmmap, the Suntools task is trying to map
	 *	in a data structure in the window driver.  That is, it is using
	 *	the mmap call to map some kernel memory into its address space!!
	 *	This klugey use of mmap breaks the Mach VM system, but the
	 *	problem can be avoided by simply not having the memory marked
	 *	as shared.
	 */
		if( mapfun == winmmap )
			realshare = MAP_PRIVATE;
#endif	sun

		for (off=0; off<uap->len; off += NBPG) {
			if ((*mapfun)(dev, file_pos+off, uap->prot) == -1) {
				u.u_error = EINVAL;
				return;
			}
		}

		if (uap->share != MAP_SHARED) {
			u.u_error = EINVAL;
			return;
		}
	
#if	MACH_XP
		pager_offset = (vm_offset_t) file_pos;
		pager = device_pager_create(dev, mapfun, uap->prot,
				pager_offset, user_size);
#else	MACH_XP
		pager = memory_object_special(dev, mapfun, uap->prot,
				(vm_offset_t) file_pos, user_size);
		pager_offset = 0;
#endif	MACH_XP
		if (pager == PORT_NULL) {
			u.u_error = EINVAL;
			return;
		}
	}
	else {
		/*
		 *	Map in a file.  May be PRIVATE (copy-on-write)
		 *	or SHARED (changes go back to file)
		 */

		/*
		 *	Only allow regular files for the moment.
		 */
		if (!INODE_TYPE(ip,REG)) {
			u.u_error = EINVAL;
			return;
		}
		
		if ((pager = inode_pager_setup(ip, FALSE, FALSE))
				== MEMORY_OBJECT_NULL) {
			u.u_error = KERN_INVALID_ARGUMENT;
			return;
		}
		pager_offset = (vm_offset_t) file_pos;
	}

	/*
	 *	Deallocate the existing memory, then map the appropriate
	 *	memory object into the space left.
	 */

	result = vm_deallocate(user_map, user_addr, user_size);
	if (result == KERN_SUCCESS)
		result = vm_map(user_map, &user_addr, user_size, 0, FALSE,
				pager, pager_offset,
				(uap->share != MAP_SHARED),
				user_prot,
				(uap->share == MAP_SHARED) ?
					user_prot : VM_PROT_ALL,
				((realshare == MAP_SHARED) ?
					VM_INHERIT_SHARE : VM_INHERIT_COPY)
				);
	
	/*
	 *	Throw away references to the appropriate pager
	 */

	if (INODE_TYPE(ip,CHR)) {
#if	MACH_XP
		port_release(pager);
#else	MACH_XP
		vm_object_t	object = vm_object_lookup(pager);
		
		if (object != VM_OBJECT_NULL) {
			/* Once for the lookup, once for real */
			vm_object_deallocate(object);
			vm_object_deallocate(object);
		}
#endif	MACH_XP
	} else {
		inode_pager_release(pager);
	}

	if (result != KERN_SUCCESS) {
		u.u_error = EINVAL;
		return;
	}

	u.u_pofile[uap->fd] |= UF_MAPPED;
}

mremap()
{

}

munmap()
{
	register struct a {
		caddr_t	addr;
		int	len;
	} *uap = (struct a *)u.u_ap;
	vm_offset_t	user_addr;
	vm_size_t	user_size;
	kern_return_t	result;

	user_addr = (vm_offset_t) uap->addr;
	user_size = (vm_size_t) uap->len;
	if ((user_addr & page_mask) ||
	    (user_size & page_mask)) {
		u.u_error = EINVAL;
		return;
	}
	result = vm_deallocate(current_task()->map, user_addr, user_size);
	if (result != KERN_SUCCESS) {
		u.u_error = EINVAL;
		return;
	}
}

munmapfd(fd)
{
	u.u_pofile[fd] &= ~UF_MAPPED;
}

mprotect()
{
}

madvise()
{
}

mincore()
{
}

/* BEGIN DEFUNCT */
obreak()
{
	struct a {
		char	*nsiz;
	};
	vm_offset_t	old, new;
	kern_return_t	ret;

	new = round_page(((struct a *)u.u_ap)->nsiz);
	if ((int)(new - (vm_offset_t)u.u_data_start) > u.u_rlimit[RLIMIT_DATA].rlim_cur) {
		u.u_error = ENOMEM;
		return;
	}
	old = round_page(u.u_data_start + ctob(u.u_dsize));
	if (new > old) {
		ret = vm_allocate(current_task()->map, &old, new - old, FALSE);
		if (ret != KERN_SUCCESS)
			uprintf("%s: could not sbrk, return = %d\n", u.u_comm, ret);
		else
			u.u_dsize += btoc(new - old);
	}
}

int	both;

ovadvise()
{
#ifdef	lint
	both = 0;
#endif
}
/* END DEFUNCT */

/*
 * grow the stack to include the SP
 * true return if successful.
 */
grow(sp)
	unsigned sp;
{
	register int si;

	if (sp >= USRSTACK-ctob(u.u_ssize))
		return (0);
	si = round_page((USRSTACK - sp) - ctob(u.u_ssize) + ctob(SINCR));
	if ((unsigned)si > u.u_rlimit[RLIMIT_STACK].rlim_cur)
		return (0);
	return (1);
}
