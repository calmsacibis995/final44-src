h10552
s 00001/00001/00140
d D 8.2 93/12/10 18:10:37 mckusick 7 6
c lint
e
s 00002/00002/00139
d D 8.1 93/06/11 15:17:06 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00138
d D 7.5 93/04/20 23:35:36 torek 5 4
c spelling; KNF
e
s 00007/00007/00134
d D 7.4 92/10/11 12:57:21 bostic 4 3
c make kernel includes standard
e
s 00005/00000/00136
d D 7.3 92/07/21 16:54:36 bostic 3 2
c update the contribution notice; LBL requires acknowledgement
e
s 00003/00003/00133
d D 7.2 92/07/13 15:51:13 torek 2 1
c MIN => min
e
s 00136/00000/00000
d D 7.1 92/07/13 00:44:39 torek 1 0
c date and time created 92/07/13 00:44:39 by torek
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 3
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 5
 *	California, Lawrence Berkeley Laboratories.
E 5
I 5
 *	California, Lawrence Berkeley Laboratory.
E 5
 *
E 3
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 5
 * from: $Header: mem.c,v 1.8 92/06/17 05:22:16 torek Exp $
E 5
I 5
 * from: $Header: mem.c,v 1.9 92/11/26 03:05:03 torek Exp $
E 5
 */

/*
 * Memory special file
 */

D 4
#include "param.h"
#include "proc.h"
#include "conf.h"
#include "buf.h"
#include "systm.h"
#include "malloc.h"
E 4
I 4
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/malloc.h>
E 4

D 4
#include "vm/vm.h"
E 4
I 4
#include <vm/vm.h>
E 4

/*ARGSUSED*/
mmrw(dev, uio, flags)
	dev_t dev;
	struct uio *uio;
	int flags;
{
	register struct iovec *iov;
	register caddr_t va;
	register int o;
	register u_int c;
	int error = 0;
	caddr_t zbuf = NULL;
	extern caddr_t vmempage;
	static struct {
		int	locked;
		int	wanted;
	} physlock;

	if (minor(dev) == 0) {
		/* lock against other uses of shared vmempage */
		while (physlock.locked) {
			physlock.wanted = 1;
D 5
			(void) tsleep((caddr_t)&physlock, PZERO, "mmrw", 0);
E 5
I 5
			(void)tsleep((caddr_t)&physlock, PZERO, "mmrw", 0);
E 5
		}
		physlock.locked = 1;
	}
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
			o = uio->uio_offset;
			va = vmempage;
			if (pmap_enter_hw(kernel_pmap, (vm_offset_t)va, 
			    (vm_offset_t)trunc_page(o), 
			    uio->uio_rw == UIO_READ ?
			    VM_PROT_READ : VM_PROT_WRITE, 1)) {
				error = EFAULT;
				goto unlock;
			}
			o = (int)uio->uio_offset & PGOFSET;
D 2
			c = MIN(uio->uio_resid, (u_int)(NBPG - o));
E 2
I 2
			c = min(uio->uio_resid, (u_int)(NBPG - o));
E 2
			error = uiomove(&va[o], (int)c, uio);
			pmap_remove(kernel_pmap,
			    (vm_offset_t)va, (vm_offset_t)va + PAGE_SIZE);
			continue;

/* minor device 1 is kernel memory */
		case 1:
D 7
			va = (caddr_t)uio->uio_offset;
E 7
I 7
			va = (caddr_t)(int)uio->uio_offset;
E 7
D 2
			c = MIN(iov->iov_len, MAXPHYS);
E 2
I 2
			c = min(iov->iov_len, MAXPHYS);
E 2
			if (!kernacc(va, c,
			    uio->uio_rw == UIO_READ ? B_READ : B_WRITE))
				return (EFAULT);
			error = uiomove(va, (int)c, uio);
			continue;

/* minor device 2 is EOF/RATHOLE */
		case 2:
			if (uio->uio_rw == UIO_WRITE)
				uio->uio_resid = 0;
			return (0);

/* XXX should add sbus, `prom', etc */

/* minor device 12 (/dev/zero) is source of nulls on read, rathole on write */
		case 12:
			if (uio->uio_rw == UIO_WRITE) {
				uio->uio_resid = 0;
				return (0);
			}
			if (zbuf == NULL) {	/* XXX grot */
				zbuf = (caddr_t)malloc(CLBYTES,
				    M_TEMP, M_WAITOK);
				bzero(zbuf, CLBYTES);
			}
D 2
			c = MIN(iov->iov_len, CLBYTES);
E 2
I 2
			c = min(iov->iov_len, CLBYTES);
E 2
			error = uiomove(zbuf, (int)c, uio);
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
	if (zbuf)
		free(zbuf, M_TEMP);
	if (minor(dev) == 0) {
unlock:
		physlock.locked = 0;
		if (physlock.wanted)
			wakeup((caddr_t)&physlock);
	}
	return (error);
}
E 1
