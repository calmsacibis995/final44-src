/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mem.c,v $
 * Revision 1.3  89/02/26  12:32:40  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 *  8-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed vm_object_null procedure call to VM_OBJECT_NULL.
 *
 */

#include <mach_load.h>
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mem.c	7.1 (Berkeley) 6/5/86
 */

/*
 * Memory special file
 */

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/vm.h>
#include <sys/uio.h>

#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <mach/vm_param.h>

extern int loadpt;

mmread(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (mmrw(dev, uio, UIO_READ));
}

mmwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (mmrw(dev, uio, UIO_WRITE));
}

mmrw(dev, uio, rw)
	dev_t dev;
	struct uio *uio;
	enum uio_rw rw;
{
	register int o;
	register u_int c, v;
	register struct iovec *iov;
	int error = 0;
	vm_offset_t	where;
	int		spl;


	while (uio->uio_resid > 0 && error == 0) {
		iov = uio->uio_iov;
		if (iov->iov_len == 0) {
			uio->uio_iov++;
			uio->uio_iovcnt--;
			if (uio->uio_iovcnt < 0)
				panic("mmrw");
			continue;
		}
		switch (minor(dev)) {

/* minor device 0 is physical memory */
		case 0:
#if	MACH_LOAD
			v = trunc_page(uio->uio_offset + loadpt);
#else	MACH_LOAD
			v = trunc_page(uio->uio_offset);
#endif	MACH_LOAD
			if (uio->uio_offset >= mem_size)
				goto fault;

			spl = splvm();
			where = vm_map_min(kernel_map);
			if (vm_map_find(kernel_map, VM_OBJECT_NULL,
				(vm_offset_t) 0, &where, PAGE_SIZE, TRUE) != KERN_SUCCESS) {
				splx(spl);
				goto fault;
			}
			pmap_enter(vm_map_pmap(kernel_map), where, v,
					VM_PROT_READ|VM_PROT_WRITE, FALSE);
			pmap_update();
#if	MACH_LOAD
			o = (uio->uio_offset + loadpt) - v;
#else	MACH_LOAD
			o = uio->uio_offset - v;
#endif	MACH_LOAD
			c = min(PAGE_SIZE - o, (u_int)iov->iov_len);
			error = uiomove((caddr_t) (where + o), c, rw, uio);
			vm_map_remove(kernel_map, where, where + PAGE_SIZE);
			splx(spl);
			continue;

/* minor device 1 is kernel memory */
		case 1:
			c = iov->iov_len;
			if (!kernacc((caddr_t)uio->uio_offset, c, rw == UIO_READ ? B_READ : B_WRITE))
				goto fault;
			error = uiomove((caddr_t)uio->uio_offset, (int)c, rw, uio);
			continue;

/* minor device 2 is EOF/RATHOLE */
		case 2:
			if (rw == UIO_READ)
				return (0);
			c = iov->iov_len;
			break;
		}
/* minor device 3 is unibus memory (addressed by shorts) */
		if (error)
			break;
		iov->iov_base += c;
		iov->iov_len -= c;
		uio->uio_offset += c;
		uio->uio_resid -= c;
	}
	return (error);
fault:
	return (EFAULT);
}
