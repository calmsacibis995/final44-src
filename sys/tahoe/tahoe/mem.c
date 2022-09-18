/*
 * Copyright (c) 1988, 1990 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mem.c	7.5 (Berkeley) 12/16/90
 */

/*
 * Memory special file
 */

#include "sys/param.h"
#include "sys/user.h"
#include "sys/conf.h"
#include "sys/buf.h"
#include "sys/systm.h"
#include "sys/vm.h"
#include "sys/cmap.h"
#include "sys/uio.h"

#include "../include/pte.h"
#include "../include/mtpr.h"

/* ARGSUSED */
mmrw(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
	int flag;
{
	register int o;
	register u_int c, v;
	register struct iovec *iov;
	int error = 0;
	extern caddr_t vmembeg, vmemend;


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
			v = btop(uio->uio_offset);
			if (v >= physmem)
				goto fault;
			*(int *)mmap = v | PG_V |
				(uio->uio_rw == UIO_READ ? PG_KR : PG_KW);
			mtpr(TBIS, vmmap);
			o = (int)uio->uio_offset & PGOFSET;
			c = (u_int)(NBPG - ((int)iov->iov_base & PGOFSET));
			c = MIN(c, (u_int)(NBPG - o));
			c = MIN(c, (u_int)iov->iov_len);
			error = uiomove((caddr_t)&vmmap[o], (int)c, uio);
			continue;

/* minor device 1 is kernel memory */
		case 1:
			if ((caddr_t)uio->uio_offset < (caddr_t)&vmembeg &&
			    (caddr_t)uio->uio_offset + uio->uio_resid >= (caddr_t)&vmembeg)
				goto fault;
			if ((caddr_t)uio->uio_offset >= (caddr_t)&vmembeg &&
			    (caddr_t)uio->uio_offset < (caddr_t)&vmemend)
				goto fault;
			c = iov->iov_len;
			if (!kernacc((caddr_t)uio->uio_offset, c,
			    uio->uio_rw == UIO_READ ? B_READ : B_WRITE))
				goto fault;
			error = uiomove((caddr_t)uio->uio_offset, (int)c, uio);
			continue;

/* minor device 2 is EOF/RATHOLE */
		case 2:
			if (uio->uio_rw == UIO_WRITE)
				uio->uio_resid = 0;
			return (0);

/* minor device 3 is versabus memory (addressed by shorts) */
		case 3:
			c = iov->iov_len;
			if (!kernacc((caddr_t)uio->uio_offset, c,
			    uio->uio_rw == UIO_READ ? B_READ : B_WRITE))
				goto fault;
			if (!useracc(iov->iov_base, c,
			    uio->uio_rw == UIO_READ ? B_WRITE : B_READ))
				goto fault;
			error = VERSAcpy((caddr_t)uio->uio_offset, iov->iov_base,
			    (int)c, uio->uio_rw);
			break;
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
}
