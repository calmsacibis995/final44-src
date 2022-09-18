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
 * $Log:	mem.c,v $
 * Revision 2.3  89/02/25  20:25:38  gm0w
 * 	Changes for cleanup.
 * 
 *  8-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed vm_object_null procedure call to VM_OBJECT_NULL.
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 25-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to new virtual memory code.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 *  8-Mar-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Funny new version views /dev/mem the same as /dev/mom -- sometimes
 *
 *  7-Mar-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added minor 6, with origin half way through shared memory 1040..0000
 *
 * 15-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Add minor's 4 and 5. 4 references the mpm device registers (actually
 *	any device's registers). you use numbers like 8k*nexus# +offset.  Be
 *	really careful inspecifying registers for your particular nexus it
 *	is trivial to get a machine check it you address something strange
 *	or out of bounds for you nexus.  I suppose someone should add a
 *	table to specify valid address to reach the registers on each
 *	particular nexus type.
 *	# 5 references physical memory starting at 256Meg -- which is where
 *	shared memory lives.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mem.c	7.1 (Berkeley) 6/5/86
 */

#include <mach_mpm.h>
#include <mach_load.h>

/*
 * Memory special file
 */

#include <vax/pte.h>

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/vm.h>
#include <sys/uio.h>

#if	NMACH_MPM > 0
#include <vax/ma780var.h>
#endif	NMACH_MPM > 0
#include <vax/mtpr.h>

#include <uba.h>
#if	NUBA > 0
#include <vaxuba/ubavar.h>
#endif	NUBA > 0

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
			for (c = 0; c < NUBA; c++) {
				if ((caddr_t)uio->uio_offset < (caddr_t)unibus_start[c] &&
				    (caddr_t)uio->uio_offset + uio->uio_resid >= (caddr_t)unibus_start[c])
					goto fault;
				if ((caddr_t)uio->uio_offset >= (caddr_t)unibus_start[c] &&
				    (caddr_t)uio->uio_offset < (caddr_t)unibus_end[c])
					goto fault;
			}
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

/* minor device 3 is unibus memory (addressed by shorts) */
		case 3:
			c = iov->iov_len;
			if (!kernacc((caddr_t)uio->uio_offset, c, rw == UIO_READ ? B_READ : B_WRITE))
				goto fault;
			if (!useracc(iov->iov_base, c, rw == UIO_READ ? B_WRITE : B_READ))
				goto fault;
			error = UNIcpy((caddr_t)uio->uio_offset, iov->iov_base,
			    (int)c, rw);
			break;
#if	NMACH_MPM > 0
/* minor device 4 is kernel nexus memory */
		case 4:
			v = btop(uio->uio_offset) | btop(0x20000000) ;

		/* XXX - This needs to be fixed. */
#ifndef	lint
			if (1) goto fault;
#endif	lint
/* minor device 5 is physical multiport memory */
		case 5:
			v = uio->uio_offset + 0x10000000 ;
			if (v < MPMEM_ORIGIN || v >= MPMEM_END)
				goto fault ;

			v = btop(v) ;
		/* XXX - This needs to be fixed. */
#ifndef	lint
			if (1) goto fault;
#endif	lint
/* minor device 6 is high half physical multiport memory */
		case 6:
			v = uio->uio_offset + 0x10400000 ;
			if (v < MPMEM_ORIGIN || v >= MPMEM_END)
				goto fault ;

			v = btop(v) ;
		/* XXX - This needs to be fixed. */
#ifndef	lint
			if (1) goto fault;
#endif	lint
#endif	NMACH_MPM > 0
		}
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

/*
 * UNIBUS Address Space <--> User Space transfer
 */
UNIcpy(uniadd, usradd, n, rw)
	caddr_t uniadd, usradd;
	register int n;
	enum uio_rw rw;
{
	register short *from, *to;
 
	if (rw == UIO_READ) {
		from = (short *)uniadd;
		to = (short *)usradd;
	} else {
		from = (short *)usradd;
		to = (short *)uniadd;
	}
	for (n >>= 1; n > 0; n--)
		*to++ = *from++;
	return (0);
}
