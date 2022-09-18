h50054
s 00006/00004/00202
d D 7.5 91/05/09 20:11:00 bostic 8 7
c new copyright; att/bsd/shared
e
s 00007/00007/00199
d D 7.4 90/12/16 17:02:01 bostic 7 6
c kernel reorg
e
s 00000/00002/00206
d D 7.3 90/02/17 10:48:33 mckusick 6 5
c get rid of unneeded header files
e
s 00009/00025/00199
d D 7.2 89/05/09 20:56:34 mckusick 5 4
c merge in vnodes
e
s 00001/00001/00223
d D 7.1 86/06/05 00:42:43 mckusick 4 3
c 4.3BSD release version
e
s 00003/00000/00221
d D 1.3 86/02/23 23:06:07 karels 3 2
c lint
e
s 00004/00002/00217
d D 1.2 85/08/07 17:18:46 bloom 2 1
c fix hang if attempting to read after last sector
e
s 00219/00000/00000
d D 1.1 85/08/05 14:48:53 bloom 1 0
c date and time created 85/08/05 14:48:53 by bloom
e
u
U
t
T
I 1
D 8
/*
D 4
 * Copyright (c) 1982 Regents of the University of California.
E 4
I 4
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
/*-
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 8
 *
I 8
 * %sccs.include.redist.c%
 *
E 8
 *	%W% (Berkeley) %G%
 */
I 8

E 8
/*
 * TO DO (tef  7/18/85):
 *	1) change printf's to log() instead???
 */

#if VAX8600
D 7
#include "param.h"
#include "systm.h"
#include "conf.h"
D 6
#include "dir.h"
E 6
#include "user.h"
#include "buf.h"
E 7
I 7
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/conf.h"
#include "sys/user.h"
#include "sys/buf.h"
E 7
D 6
#include "uio.h"
E 6

#include "cons.h"
D 7
#include "cpu.h"
E 7
I 7
#include "../include/cpu.h"
E 7
#include "crl.h"
D 7
#include "mtpr.h"
E 7
I 7
#include "../include/mtpr.h"
E 7

struct {
	short	crl_state;		/* open and busy flags */
	short	crl_active;		/* driver state flag */
	struct	buf *crl_buf;		/* buffer we're using */
	ushort *crl_xaddr;		/* transfer address */
	short	crl_errcnt;
} crltab;

struct {
	int	crl_cs;		/* saved controller status */
	int	crl_ds;		/* saved drive status */
} crlstat;

/*ARGSUSED*/
crlopen(dev, flag)
	dev_t dev;
	int flag;
{
	struct buf *geteblk();

	if (cpu != VAX_8600)
		return (ENXIO);
	if (crltab.crl_state != CRL_IDLE)
		return (EALREADY);
	crltab.crl_state = CRL_OPEN;
	crltab.crl_buf = geteblk(512);
	return (0);
}

/*ARGSUSED*/
crlclose(dev, flag)
	dev_t dev;
	int flag;
{

	brelse(crltab.crl_buf);
	crltab.crl_state = CRL_IDLE;
}

D 5
crloperation(rw, uio)
	enum uio_rw rw;
E 5
I 5
/*ARGSUSED*/
crlrw(dev, uio, flag)
	dev_t dev;
E 5
	struct uio *uio;
I 5
	int flag;
E 5
{
	register struct buf *bp;
	register int i;
	register int s;
	int error;

	if (uio->uio_resid == 0) 
		return (0);
	s = spl4();
	while (crltab.crl_state & CRL_BUSY)
		sleep((caddr_t)&crltab, PRIBIO);
	crltab.crl_state |= CRL_BUSY;
	splx(s);

	bp = crltab.crl_buf;
	error = 0;
	while ((i = imin(CRLBYSEC, uio->uio_resid)) > 0) {
		bp->b_blkno = uio->uio_offset>>9;
D 2
		if (bp->b_blkno >= MAXSEC || (uio->uio_offset & 0x1FF) != 0)
			return (EIO);
E 2
I 2
		if (bp->b_blkno >= MAXSEC || (uio->uio_offset & 0x1FF) != 0) {
			error = EIO;
			break;
		}
E 2
D 5
		if (rw == UIO_WRITE) {
			error = uiomove(bp->b_un.b_addr, i, UIO_WRITE, uio);
E 5
I 5
		if (uio->uio_rw == UIO_WRITE) {
			error = uiomove(bp->b_un.b_addr, i, uio);
E 5
			if (error)
				break;
		}
D 5
		bp->b_flags = rw == UIO_WRITE ? B_WRITE : B_READ;
E 5
I 5
		bp->b_flags = uio->uio_rw == UIO_WRITE ? B_WRITE : B_READ;
E 5
		s = spl4(); 
		crlstart();
		while ((bp->b_flags & B_DONE) == 0)
			sleep((caddr_t)bp, PRIBIO);	
		splx(s);
		if (bp->b_flags & B_ERROR) {
			error = EIO;
			break;
		}
D 5
		if (rw == UIO_READ) {
			error = uiomove(bp->b_un.b_addr, i, UIO_READ, uio);
E 5
I 5
		if (uio->uio_rw == UIO_READ) {
			error = uiomove(bp->b_un.b_addr, i, uio);
E 5
			if (error)
				break;
		}
	}
	crltab.crl_state &= ~CRL_BUSY;
	wakeup((caddr_t)&crltab);
	return (error);
D 5
}

/*ARGSUSED*/
crlread(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (crloperation(UIO_READ, uio));
}

/*ARGSUSED*/
crlwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (crloperation(UIO_WRITE, uio));
E 5
}

crlstart()
{
	register struct buf *bp;

	bp = crltab.crl_buf;
	crltab.crl_errcnt = 0;
	crltab.crl_xaddr = (ushort *) bp->b_un.b_addr;
	bp->b_resid = 0;

	if ((mfpr(STXCS) & STXCS_RDY) == 0)
		/* not ready to receive order */
		return;
	if ((bp->b_flags&(B_READ|B_WRITE)) == B_READ) {
		crltab.crl_active = CRL_F_READ;
		mtpr(STXCS, bp->b_blkno<<8 | STXCS_IE | CRL_F_READ);
	} else {
		crltab.crl_active = CRL_F_WRITE;
		mtpr(STXCS, bp->b_blkno<<8 | STXCS_IE | CRL_F_WRITE);
	}
I 3
#ifdef lint
	crlintr();
#endif
E 3
}

crlintr()
{
	register struct buf *bp;
	int i;

	bp = crltab.crl_buf;
	i = mfpr(STXCS);
	switch ((i>>24) & 0xFF) {

	case CRL_S_XCMPLT:
		switch (crltab.crl_active) {

		case CRL_F_RETSTS:
			crlstat.crl_ds = mfpr(STXDB);
			printf("crlcs=0x%b, crlds=0x%b\n", crlstat.crl_cs,
				CRLCS_BITS, crlstat.crl_ds, CRLDS_BITS); 
			break;

		case CRL_F_READ:
		case CRL_F_WRITE:
			bp->b_flags |= B_DONE;
		}
		crltab.crl_active = 0;
		wakeup((caddr_t)bp);
		break;

	case CRL_S_XCONT:
		switch (crltab.crl_active) {

		case CRL_F_WRITE:
			mtpr(STXDB, *crltab.crl_xaddr++);
			mtpr(STXCS, bp->b_blkno<<8 | STXCS_IE | CRL_F_WRITE);
			break;

		case CRL_F_READ:
			*crltab.crl_xaddr++ = mfpr(STXDB);
			mtpr(STXCS, bp->b_blkno<<8 | STXCS_IE | CRL_F_READ);
		}
		break;

	case CRL_S_ABORT:
		crltab.crl_active = CRL_F_RETSTS;
		mtpr(STXCS, STXCS_IE | CRL_F_RETSTS);
		bp->b_flags |= B_DONE|B_ERROR;
		break;

	case CRL_S_RETSTS:
		crlstat.crl_cs = mfpr(STXDB);
		mtpr(STXCS, STXCS_IE | CRL_S_RETSTS);
		break;

	case CRL_S_HNDSHK:
		printf("crl: hndshk error\n");	/* dump out some status too? */
		crltab.crl_active = 0;
		bp->b_flags |= B_DONE|B_ERROR;
		wakeup((caddr_t)bp);
		break;

	case CRL_S_HWERR:
		printf("crl: hard error sn%d\n", bp->b_blkno);
		crltab.crl_active = CRL_F_ABORT;
		mtpr(STXCS, STXCS_IE | CRL_F_ABORT);
		break;
	}
}
#endif
E 1
