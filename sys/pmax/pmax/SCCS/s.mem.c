h17218
s 00001/00004/00113
d D 8.3 95/06/02 17:25:19 ralph 9 8
c final changes for pmax 4.4-Lite II release
e
s 00004/00003/00113
d D 8.2 94/03/28 08:07:28 bostic 8 7
c fix address bounds check
c From: ralphc@pyramid.com (Ralph Campbell)
e
s 00002/00002/00114
d D 8.1 93/06/10 23:07:38 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/00106
d D 7.6 92/10/11 11:23:19 bostic 6 5
c make kernel includes standard
e
s 00001/00001/00115
d D 7.5 92/07/27 21:24:43 ralph 5 4
c use min() not MIN()
e
s 00004/00004/00112
d D 7.4 92/06/20 12:06:26 ralph 4 3
c use u_long instead of long long for reading dev/kmem.
e
s 00007/00008/00109
d D 7.3 92/03/15 19:15:48 ralph 3 2
c fix kmem address checking.
e
s 00012/00006/00105
d D 7.2 92/02/29 13:49:34 ralph 2 1
c fix test for correct address protection
e
s 00111/00000/00000
d D 7.1 92/01/07 17:29:21 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: mem.c 1.14 90/10/12$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Memory special file
 */

D 6
#include "param.h"
#include "conf.h"
#include "buf.h"
#include "systm.h"
#include "malloc.h"
E 6
I 6
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/malloc.h>
E 6

D 6
#include "../include/cpu.h"
E 6
I 6
#include <machine/cpu.h>
E 6

D 6
#include "vm/vm_param.h"
#include "vm/lock.h"
D 4
#include "vm/pmap.h"
E 4
#include "vm/vm_prot.h"
I 4
#include "vm/pmap.h"
E 6
I 6
D 9
#include <vm/vm_param.h>
#include <vm/lock.h>
#include <vm/vm_prot.h>
#include <vm/pmap.h>
E 9
I 9
#include <vm/vm.h>
E 9
E 6
E 4

/*ARGSUSED*/
mmrw(dev, uio, flags)
	dev_t dev;
	struct uio *uio;
	int flags;
{
D 3
	register int o;
	register u_int c, v;
E 3
I 3
D 4
	register off_t v;
E 4
I 4
	register u_long v;
E 4
	register u_int c;
E 3
	register struct iovec *iov;
	int error = 0;
	caddr_t zbuf = NULL;
D 2
	extern u_int lowram;
E 2
I 2
	extern vm_offset_t avail_end;
E 2

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
D 4
			v = uio->uio_offset;
E 4
I 4
			v = (u_long)uio->uio_offset;
E 4
			c = iov->iov_len;
D 8
			if (v + c >= physmem)
E 8
I 8
			if (v + c <= btoc(physmem))
				v += MACH_CACHED_MEMORY_ADDR;
			else
E 8
				return (EFAULT);
D 8
			error = uiomove((caddr_t)(MACH_CACHED_MEMORY_ADDR + v),
				(int)c, uio);
E 8
I 8
			error = uiomove((caddr_t)v, (int)c, uio);
E 8
			continue;

/* minor device 1 is kernel memory */
		case 1:
D 2
			c = iov->iov_len;
			if (!kernacc((caddr_t)uio->uio_offset, c,
			    uio->uio_rw == UIO_READ ? B_READ : B_WRITE))
E 2
I 2
D 3
			if (uio->uio_offset < MACH_CACHED_MEMORY_ADDR)
E 3
I 3
D 4
			v = uio->uio_offset;
E 4
I 4
			v = (u_long)uio->uio_offset;
E 4
			if (v < MACH_CACHED_MEMORY_ADDR)
E 3
E 2
				return (EFAULT);
D 2
			error = uiomove((caddr_t)uio->uio_offset, (int)c, uio);
			continue;
E 2
I 2
			c = iov->iov_len;
D 3
			if (uio->uio_offset + c <= avail_end ||
			    uio->uio_offset >= MACH_KSEG2_ADDR &&
			    kernacc((caddr_t)uio->uio_offset, c,
E 3
I 3
			if (v + c <= MACH_PHYS_TO_CACHED(avail_end) ||
			    v >= MACH_KSEG2_ADDR && kernacc((caddr_t)v, c,
E 3
			    uio->uio_rw == UIO_READ ? B_READ : B_WRITE)) {
D 3
				error = uiomove((caddr_t)uio->uio_offset,
					(int)c, uio);
E 3
I 3
				error = uiomove((caddr_t)v, (int)c, uio);
E 3
				continue;
			}
			return (EFAULT);
E 2

/* minor device 2 is EOF/RATHOLE */
		case 2:
			if (uio->uio_rw == UIO_WRITE)
				uio->uio_resid = 0;
			return (0);

/* minor device 12 (/dev/zero) is source of nulls on read, rathole on write */
		case 12:
			if (uio->uio_rw == UIO_WRITE) {
				c = iov->iov_len;
				break;
			}
			if (zbuf == NULL) {
				zbuf = (caddr_t)
				    malloc(CLBYTES, M_TEMP, M_WAITOK);
				bzero(zbuf, CLBYTES);
			}
D 5
			c = MIN(iov->iov_len, CLBYTES);
E 5
I 5
			c = min(iov->iov_len, CLBYTES);
E 5
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
	return (error);
}
E 1
