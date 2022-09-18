h45823
s 00002/00002/00162
d D 8.1 93/06/11 15:35:03 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00011/00153
d D 7.7 92/10/11 10:11:02 bostic 15 14
c make kernel includes standard
e
s 00003/00003/00161
d D 7.6 92/07/13 09:11:07 pendry 14 13
c MIN -> min
e
s 00002/00002/00162
d D 7.5 92/02/19 18:30:04 torek 13 12
c eliminate function pmap_kernel
e
s 00001/00001/00163
d D 7.4 91/10/07 12:44:54 william 12 11
c need to move vm_prot ahead of pmap.h
e
s 00000/00001/00164
d D 7.3 91/09/03 09:10:51 william 11 10
c don't include vm_statistics.h anymore
e
s 00001/00001/00164
d D 7.2 91/05/09 19:26:23 william 10 9
c 
e
s 00002/00014/00163
d D 7.1 91/05/09 19:25:20 william 9 8
c scccs keywords, release no
e
s 00073/00013/00104
d D 5.7 91/05/09 19:19:26 william 8 7
c final version
e
s 00041/00032/00076
d D 5.6 91/01/19 12:45:49 william 7 6
c reno changes
e
s 00001/00001/00107
d D 5.5 90/11/25 16:08:04 bill 6 5
c last changes before merger with reno version. cross fingers.
e
s 00001/00001/00107
d D 5.4 90/11/18 11:30:08 bill 5 4
c fix autoconf, move code to isa.c, remove debugging, drop redundant tlbflushes, macros for tlb et al
e
s 00010/00011/00098
d D 5.3 90/11/14 13:30:49 bill 4 3
c conventions change
e
s 00012/00001/00097
d D 5.2 90/04/24 19:13:09 william 3 2
c 1st Berkeley Release
e
s 00002/00045/00096
d D 5.1 90/04/24 18:56:41 william 2 1
c 1st Berkeley Release
e
s 00141/00000/00000
d D 1.1 90/03/12 15:48:08 bill 1 0
c date and time created 90/03/12 15:48:08 by bill
e
u
U
t
T
I 1
D 3
/*	mem.c	1.4	86/12/15	*/
E 3
I 3
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
E 7
I 7
 * Copyright (c) 1988 University of Utah.
D 16
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
E 7
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * This code is derived from software contributed to Berkeley by
D 7
 * William Jolitz.
E 7
I 7
 * the Systems Programming Group of the University of Utah Computer
 * Science Department, and code derived from software contributed to
 * Berkeley by William Jolitz.
E 7
 *
D 7
 * %sccs.include.noredist.c%
E 7
I 7
D 8
 * %sccs.include.redist.c%
E 8
I 8
D 9
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
D 10
 * %sccs.include.noredist.c%
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
E 8
E 7
 *
I 7
 * from: Utah $Hdr: mem.c 1.13 89/10/08$
E 7
D 8
 *	%W% (Berkeley) %G%
E 8
I 8
D 9
 *	@(#)mem.c	5.6 (Berkeley) 1/19/91
E 9
I 9
 *	%W% (Berkeley) %G%
E 9
E 8
 */

E 3
D 4

E 4
/*
 * Memory special file
 */

D 4
#include "../machine/pte.h"
E 4
I 4
D 8
#include "machine/pte.h"
E 4

E 8
D 4
#include "../h/param.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/conf.h"
#include "../h/buf.h"
#include "../h/systm.h"
#include "../h/vm.h"
#include "../h/cmap.h"
#include "../h/uio.h"
E 4
I 4
D 15
#include "param.h"
D 7
#include "dir.h"
E 7
D 8
#include "user.h"
E 8
#include "conf.h"
#include "buf.h"
#include "systm.h"
D 8
#include "vm.h"
#include "cmap.h"
E 8
#include "uio.h"
I 7
#include "malloc.h"
E 15
I 15
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/uio.h>
#include <sys/malloc.h>
E 15
E 7
E 4

D 2
#include "../tahoe/mtpr.h"

E 2
D 7
mmread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
E 7
I 7
D 15
#include "machine/cpu.h"
E 15
I 15
#include <machine/cpu.h>
E 15
E 7

I 8
D 15
#include "vm/vm_param.h"
#include "vm/lock.h"
D 11
#include "vm/vm_statistics.h"
E 11
D 12
#include "vm/pmap.h"
E 12
#include "vm/vm_prot.h"
I 12
#include "vm/pmap.h"
E 15
I 15
#include <vm/vm_param.h>
#include <vm/lock.h>
#include <vm/vm_prot.h>
#include <vm/pmap.h>
E 15
E 12

extern        char *vmmap;            /* poor name! */
E 8
D 7
	return (mmrw(dev, uio, UIO_READ));
}

mmwrite(dev, uio)
E 7
I 7
/*ARGSUSED*/
mmrw(dev, uio, flags)
E 7
	dev_t dev;
	struct uio *uio;
I 7
	int flags;
E 7
{
D 7

	return (mmrw(dev, uio, UIO_WRITE));
}

mmrw(dev, uio, rw)
	dev_t dev;
	struct uio *uio;
	enum uio_rw rw;
{
E 7
	register int o;
	register u_int c, v;
	register struct iovec *iov;
	int error = 0;
I 7
	caddr_t zbuf = NULL;
E 7
D 2
	extern caddr_t vmembeg, vmemend;
E 2

D 7

E 7
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
D 7
			v = btop(uio->uio_offset);
			if (v >= physmem)
				goto fault;
D 2
			*(int *)mmap = v | PG_V |
E 2
I 2
			*(int *)mmap = ctob(v) | PG_V |
E 2
				(rw == UIO_READ ? PG_KR : PG_KW);
D 2
			mtpr(TBIS, vmmap);
E 2
I 2
D 5
			load_cr3(_cr3());
E 5
I 5
D 6
			tlbflush();
E 6
I 6
			load_cr3(u.u_pcb.pcb_ptd);
E 7
I 7
			v = uio->uio_offset;
D 8
			*(int *)mmap = (v & PG_FRAME) | PG_V |
				(uio->uio_rw == UIO_READ ? PG_KR : PG_KW);
			load_cr3(u.u_pcb.pcb_cr3);
E 8
I 8
D 13
			pmap_enter(pmap_kernel(), vmmap, v,
E 13
I 13
			pmap_enter(kernel_pmap, vmmap, v,
E 13
				uio->uio_rw == UIO_READ ? VM_PROT_READ : VM_PROT_WRITE,
				TRUE);
E 8
E 7
E 6
E 5
E 2
			o = (int)uio->uio_offset & PGOFSET;
			c = (u_int)(NBPG - ((int)iov->iov_base & PGOFSET));
D 14
			c = MIN(c, (u_int)(NBPG - o));
			c = MIN(c, (u_int)iov->iov_len);
E 14
I 14
			c = min(c, (u_int)(NBPG - o));
			c = min(c, (u_int)iov->iov_len);
E 14
D 7
			error = uiomove((caddr_t)&vmmap[o], (int)c, rw, uio);
E 7
I 7
			error = uiomove((caddr_t)&vmmap[o], (int)c, uio);
I 8
D 13
			pmap_remove(pmap_kernel(), vmmap, &vmmap[NBPG]);
E 13
I 13
			pmap_remove(kernel_pmap, vmmap, &vmmap[NBPG]);
E 13
E 8
E 7
			continue;

/* minor device 1 is kernel memory */
		case 1:
D 2
			if ((caddr_t)uio->uio_offset < (caddr_t)&vmembeg &&
			    (caddr_t)uio->uio_offset + uio->uio_resid >= (caddr_t)&vmembeg)
				goto fault;
			if ((caddr_t)uio->uio_offset >= (caddr_t)&vmembeg &&
			    (caddr_t)uio->uio_offset < (caddr_t)&vmemend)
				goto fault;
E 2
			c = iov->iov_len;
D 7
			if (!kernacc((caddr_t)uio->uio_offset, c, rw == UIO_READ ? B_READ : B_WRITE))
E 7
I 7
			if (!kernacc((caddr_t)uio->uio_offset, c,
			    uio->uio_rw == UIO_READ ? B_READ : B_WRITE))
E 7
D 8
				goto fault;
E 8
I 8
				return(EFAULT);
E 8
D 7
			error = uiomove((caddr_t)uio->uio_offset, (int)c, rw, uio);
E 7
I 7
			error = uiomove((caddr_t)uio->uio_offset, (int)c, uio);
E 7
			continue;

/* minor device 2 is EOF/RATHOLE */
		case 2:
D 7
			if (rw == UIO_READ)
E 7
I 7
			if (uio->uio_rw == UIO_READ)
E 7
				return (0);
			c = iov->iov_len;
			break;

I 7
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
D 14
			c = MIN(iov->iov_len, CLBYTES);
E 14
I 14
			c = min(iov->iov_len, CLBYTES);
E 14
			error = uiomove(zbuf, (int)c, uio);
			continue;

I 8
#ifdef notyet
/* 386 I/O address space (/dev/ioport[bwl]) is a read/write access to seperate
   i/o device address bus, different than memory bus. Semantics here are
   very different than ordinary read/write, as if iov_len is a multiple
   an implied string move from a single port will be done. Note that lseek
   must be used to set the port number reliably. */
		case 14:
			if (iov->iov_len == 1) {
				u_char tmp;
				tmp = inb(uio->uio_offset);
				error = uiomove (&tmp, iov->iov_len, uio);
			} else {
				if (!useracc((caddr_t)iov->iov_base,
					iov->iov_len, uio->uio_rw))
					return (EFAULT);
				insb(uio->uio_offset, iov->iov_base,
					iov->iov_len);
			}
			break;
		case 15:
			if (iov->iov_len == sizeof (short)) {
				u_short tmp;
				tmp = inw(uio->uio_offset);
				error = uiomove (&tmp, iov->iov_len, uio);
			} else {
				if (!useracc((caddr_t)iov->iov_base,
					iov->iov_len, uio->uio_rw))
					return (EFAULT);
				insw(uio->uio_offset, iov->iov_base,
					iov->iov_len/ sizeof (short));
			}
			break;
		case 16:
			if (iov->iov_len == sizeof (long)) {
				u_long tmp;
				tmp = inl(uio->uio_offset);
				error = uiomove (&tmp, iov->iov_len, uio);
			} else {
				if (!useracc((caddr_t)iov->iov_base,
					iov->iov_len, uio->uio_rw))
					return (EFAULT);
				insl(uio->uio_offset, iov->iov_base,
					iov->iov_len/ sizeof (long));
			}
			break;
#endif

E 8
		default:
			return (ENXIO);
E 7
D 2
/* minor device 3 is versabus memory (addressed by shorts) */
		case 3:
			c = iov->iov_len;
			if (!kernacc((caddr_t)uio->uio_offset, c, rw == UIO_READ ? B_READ : B_WRITE))
				goto fault;
			if (!useracc(iov->iov_base, c, rw == UIO_READ ? B_WRITE : B_READ))
				goto fault;
			error = VERSAcpy((caddr_t)uio->uio_offset, iov->iov_base,
			    (int)c, rw);
			break;
E 2
		}
		if (error)
			break;
		iov->iov_base += c;
		iov->iov_len -= c;
		uio->uio_offset += c;
		uio->uio_resid -= c;
	}
I 7
	if (zbuf)
		free(zbuf, M_TEMP);
E 7
	return (error);
D 8
fault:
	return (EFAULT);
E 8
D 2
}

/*
 * VERSABUS Address Space <--> User Space transfer
 */
VERSAcpy(versaadd, usradd, n, rw)
	caddr_t versaadd, usradd;
	register int n;
	enum uio_rw rw;
{
	register short *from, *to;
 
	if(((int)versaadd&1) || ((int)usradd&1))
		return (EFAULT);
	if (rw == UIO_READ) {
		from = (short *)versaadd;
		to = (short *)usradd;
	} else {
		from = (short *)usradd;
		to = (short *)versaadd;
	}
	for (n >>= 1; n > 0; n--)
		*to++ = *from++;
	return (0);
E 2
}
E 1
