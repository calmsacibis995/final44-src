h45726
s 00001/00004/00155
d D 8.4 95/04/12 13:47:49 mckusick 16 15
c fix includes for new locking
e
s 00001/00000/00158
d D 8.3 94/01/12 09:46:10 bostic 15 14
c lint
e
s 00044/00009/00114
d D 8.2 93/11/14 14:14:54 hibler 14 13
c faster /dev/zero, mmap interface (idea from netbsd)
e
s 00002/00002/00121
d D 8.1 93/06/10 21:41:13 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00119
d D 7.12 93/06/04 16:15:00 mckusick 12 11
c add an explicit assignment to avoid warnings
e
s 00010/00010/00111
d D 7.11 92/10/11 09:42:42 bostic 11 10
c make kernel includes standard
e
s 00004/00004/00117
d D 7.10 92/07/12 17:42:23 pendry 10 9
c MIN -> min
e
s 00002/00002/00119
d D 7.9 92/02/19 18:28:05 torek 9 8
c pmap_kernel() is really kernel_pmap variable
e
s 00005/00004/00116
d D 7.8 91/11/05 22:05:02 mckusick 8 7
c lint
e
s 00001/00001/00119
d D 7.7 91/09/12 16:20:05 marc 7 6
c need vm_prot.h before pmap.h
e
s 00000/00001/00120
d D 7.6 91/08/28 15:50:11 mckusick 6 5
c no longer need to include vm_statistics.h
e
s 00004/00004/00117
d D 7.5 91/05/07 09:59:21 hibler 5 4
c page-align arg to pmap_enter
e
s 00010/00012/00111
d D 7.4 91/04/20 17:20:57 karels 4 3
c fix includes; speed up writes to /dev/null
e
s 00012/00012/00111
d D 7.3 90/12/16 16:36:29 bostic 3 2
c kernel reorg
e
s 00011/00011/00112
d D 7.2 90/12/05 18:53:36 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00123/00000/00000
d D 7.1 90/05/08 18:09:11 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 13
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: mem.c 1.13 89/10/08$
E 5
I 5
 * from: Utah $Hdr: mem.c 1.14 90/10/12$
E 5
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Memory special file
 */

D 2
#include "pte.h"

E 2
D 3
#include "param.h"
#include "user.h"
#include "conf.h"
#include "buf.h"
#include "systm.h"
D 2
#include "vm.h"
E 2
#include "cmap.h"
#include "uio.h"
#include "malloc.h"
E 3
I 3
D 4
#include "sys/param.h"
#include "sys/user.h"
#include "sys/conf.h"
#include "sys/buf.h"
#include "sys/systm.h"
#include "sys/cmap.h"
#include "sys/uio.h"
#include "sys/malloc.h"
E 4
I 4
D 11
#include "param.h"
#include "conf.h"
#include "buf.h"
#include "systm.h"
#include "malloc.h"
E 11
I 11
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/malloc.h>
E 11
E 4
E 3

D 3
#include "cpu.h"
E 3
I 3
D 11
#include "../include/cpu.h"
E 11
I 11
#include <machine/cpu.h>
E 11
E 3

I 2
D 3
#include "../vm/vm_param.h"
#include "../vm/pmap.h"
#include "../vm/vm_prot.h"
E 3
I 3
D 11
#include "vm/vm_param.h"
I 4
#include "vm/lock.h"
D 6
#include "vm/vm_statistics.h"
E 6
E 4
D 7
#include "vm/pmap.h"
E 7
#include "vm/vm_prot.h"
I 7
#include "vm/pmap.h"
E 11
I 11
D 16
#include <vm/vm_param.h>
#include <vm/lock.h>
#include <vm/vm_prot.h>
#include <vm/pmap.h>
E 16
I 16
#include <vm/vm.h>
E 16
E 11
E 7
E 3

I 14
extern u_int lowram;
caddr_t zeropage;

E 14
E 2
/*ARGSUSED*/
mmrw(dev, uio, flags)
	dev_t dev;
	struct uio *uio;
	int flags;
{
	register int o;
	register u_int c, v;
	register struct iovec *iov;
	int error = 0;
D 14
	caddr_t zbuf = NULL;
E 14
I 12
	int kernloc;
E 12
D 14
	extern u_int lowram;
E 14

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
			v = uio->uio_offset;
#ifndef DEBUG
			/* allow reads only in RAM (except for DEBUG) */
			if (v >= 0xFFFFFFFC || v < lowram)
D 2
				goto fault;
E 2
I 2
				return (EFAULT);
E 2
#endif
D 2
			*(int *)mmap = (v & PG_FRAME) | PG_CI | PG_V |
				(uio->uio_rw == UIO_READ ? PG_RO : PG_RW);
			TBIS(vmmap);
E 2
I 2
D 5
			pmap_enter(pmap_kernel(), vmmap, v,
				uio->uio_rw == UIO_READ ? VM_PROT_READ : VM_PROT_WRITE,
				TRUE);
E 5
I 5
D 8
			pmap_enter(pmap_kernel(), vmmap, trunc_page(v),
				uio->uio_rw == UIO_READ ?
				   VM_PROT_READ : VM_PROT_WRITE, TRUE);
E 8
I 8
D 9
			pmap_enter(pmap_kernel(), (vm_offset_t)vmmap,
E 9
I 9
			pmap_enter(kernel_pmap, (vm_offset_t)vmmap,
E 9
			    trunc_page(v), uio->uio_rw == UIO_READ ?
			    VM_PROT_READ : VM_PROT_WRITE, TRUE);
E 8
E 5
E 2
			o = (int)uio->uio_offset & PGOFSET;
			c = (u_int)(NBPG - ((int)iov->iov_base & PGOFSET));
D 10
			c = MIN(c, (u_int)(NBPG - o));
			c = MIN(c, (u_int)iov->iov_len);
E 10
I 10
			c = min(c, (u_int)(NBPG - o));
			c = min(c, (u_int)iov->iov_len);
E 10
			error = uiomove((caddr_t)&vmmap[o], (int)c, uio);
I 2
D 8
			pmap_remove(pmap_kernel(), vmmap, &vmmap[NBPG]);
E 8
I 8
D 9
			pmap_remove(pmap_kernel(), (vm_offset_t)vmmap,
E 9
I 9
			pmap_remove(kernel_pmap, (vm_offset_t)vmmap,
E 9
			    (vm_offset_t)&vmmap[NBPG]);
E 8
E 2
			continue;

/* minor device 1 is kernel memory */
		case 1:
I 12
			kernloc = uio->uio_offset;
E 12
D 2
			c = iov->iov_len;
E 2
I 2
D 10
			c = MIN(iov->iov_len, MAXPHYS);
E 10
I 10
			c = min(iov->iov_len, MAXPHYS);
E 10
E 2
D 12
			if (!kernacc((caddr_t)uio->uio_offset, c,
E 12
I 12
			if (!kernacc((caddr_t)kernloc, c,
E 12
			    uio->uio_rw == UIO_READ ? B_READ : B_WRITE))
D 2
				goto fault;
E 2
I 2
				return (EFAULT);
E 2
D 12
			error = uiomove((caddr_t)uio->uio_offset, (int)c, uio);
E 12
I 12
			error = uiomove((caddr_t)kernloc, (int)c, uio);
E 12
			continue;

/* minor device 2 is EOF/RATHOLE */
		case 2:
D 4
			if (uio->uio_rw == UIO_READ)
				return (0);
			c = iov->iov_len;
			break;
E 4
I 4
			if (uio->uio_rw == UIO_WRITE)
				uio->uio_resid = 0;
			return (0);
E 4

/* minor device 12 (/dev/zero) is source of nulls on read, rathole on write */
		case 12:
			if (uio->uio_rw == UIO_WRITE) {
				c = iov->iov_len;
				break;
			}
D 14
			if (zbuf == NULL) {
				zbuf = (caddr_t)
				    malloc(CLBYTES, M_TEMP, M_WAITOK);
				bzero(zbuf, CLBYTES);
E 14
I 14
			/*
			 * On the first call, allocate and zero a page
			 * of memory for use with /dev/zero.
			 *
			 * XXX on the hp300 we already know where there
			 * is a global zeroed page, the null segment table.
			 */
			if (zeropage == NULL) {
#if CLBYTES == NBPG
				extern caddr_t Segtabzero;
				zeropage = Segtabzero;
#else
				zeropage = (caddr_t)
					malloc(CLBYTES, M_TEMP, M_WAITOK);
				bzero(zeropage, CLBYTES);
#endif
E 14
			}
D 10
			c = MIN(iov->iov_len, CLBYTES);
E 10
I 10
			c = min(iov->iov_len, CLBYTES);
E 10
D 14
			error = uiomove(zbuf, (int)c, uio);
E 14
I 14
			error = uiomove(zeropage, (int)c, uio);
E 14
			continue;

		default:
			return (ENXIO);
		}
		if (error)
			break;
		iov->iov_base += c;
		iov->iov_len -= c;
		uio->uio_offset += c;
		uio->uio_resid -= c;
	}
D 14
	if (zbuf)
		free(zbuf, M_TEMP);
E 14
	return (error);
I 14
}

mmmap(dev, off, prot)
	dev_t dev;
I 15
	int off, prot;
E 15
{
	/*
	 * /dev/mem is the only one that makes sense through this
	 * interface.  For /dev/kmem any physaddr we return here
	 * could be transient and hence incorrect or invalid at
	 * a later time.  /dev/null just doesn't make any sense
	 * and /dev/zero is a hack that is handled via the default
	 * pager in mmap().
	 */
	if (minor(dev) != 0)
		return (-1);
	/*
	 * Allow access only in RAM.
	 *
	 * XXX could be extended to allow access to IO space but must
	 * be very careful.
	 */
	if ((unsigned)off < lowram || (unsigned)off >= 0xFFFFFFFC)
		return (-1);
	return (hp300_btop(off));
E 14
D 2
fault:
	return (EFAULT);
E 2
}
E 1
