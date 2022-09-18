h29975
s 00008/00008/00195
d D 7.5 90/12/16 17:03:12 bostic 5 4
c kernel reorg
e
s 00001/00011/00202
d D 7.4 90/06/28 22:33:21 bostic 4 3
c new copyright notice
e
s 00001/00001/00212
d D 7.3 90/04/12 19:41:21 sklower 3 2
c rename rx50operation to rx50rw for consistency with conf.c and others
e
s 00008/00024/00205
d D 7.2 89/05/09 20:57:52 mckusick 2 1
c merge in vnodes
e
s 00229/00000/00000
d D 7.1 88/07/09 14:09:29 karels 1 0
c vax 8200 support from torek
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

#if VAX8200

/*
 * Routines to handle the console RX50.
 */

D 5
#include "param.h"
#include "time.h"
#include "kernel.h"
#include "vmmac.h"
#include "buf.h"
#include "errno.h"
#include "uio.h"
E 5
I 5
#include "sys/param.h"
#include "sys/time.h"
#include "sys/kernel.h"
#include "sys/vmmac.h"
#include "sys/buf.h"
#include "sys/errno.h"
#include "sys/uio.h"
E 5

D 5
#include "cpu.h"
E 5
I 5
#include "../include/cpu.h"
E 5
#include "rx50reg.h"

struct	rx50device rx50device;

#define	rx50unit(dev)	minor(dev)

struct rx50state {
	short	rs_flags;	/* see below */
	short	rs_drive;	/* current drive number */
	u_int	rs_blkno;	/* current block number */
} rx50state;

/* flags */
#define	RS_0OPEN	0x01	/* drive 0 open -- must be first */
#define	RS_1OPEN	0x02	/* drive 1 open -- must be second */
#define	RS_BUSY		0x04	/* operation in progress */
#define	RS_WANT		0x08	/* wakeup when done */
#define	RS_DONE		0x20	/* I/O operation done */
#define	RS_ERROR	0x40	/* error bit set at interrupt */

/*
 * Open a console RX50.
 */
/*ARGSUSED*/
rx50open(dev, flags)
	dev_t dev;
	int flags;
{
	int unit;

	/* only on 8200 (yet) */
	if (cpu != VAX_8200 || (unit = rx50unit(dev)) >= 2)
		return (ENXIO);

	/* enforce exclusive access */
	if (rx50state.rs_flags & (1 << unit))
		return (EBUSY);
	rx50state.rs_flags |= 1 << unit;
	return (0);
}

/*
 * Close a console RX50.
 */
/*ARGSUSED*/
rx50close(dev, flags)
	dev_t dev;
	int flags;
{

	rx50state.rs_flags &= ~(1 << dev);	/* atomic */
}

/*
D 2
 * Perform a read (rw==UIO_READ) or write (rw==UIO_WRITE).
E 2
I 2
 * Perform a read (uio->uio_rw==UIO_READ) or write (uio->uio_rw==UIO_WRITE).
E 2
 */
D 2
rx50operation(dev, rw, uio)
E 2
I 2
D 3
rx50operation(dev, uio, flags)
E 3
I 3
rx50rw(dev, uio, flags)
E 3
E 2
	dev_t dev;
D 2
	enum uio_rw rw;
E 2
	register struct uio *uio;
I 2
	int flags;
E 2
{
	register struct rx50device *rxaddr;
	register struct rx50state *rs;
	register char *cp;
	register int error, i, t;
	char secbuf[512];
	static char driveselect[2] = { RXCMD_DRIVE0, RXCMD_DRIVE1 };

	/* enforce whole-sector I/O */
	if ((uio->uio_offset & 511) || (uio->uio_resid & 511))
		return (EINVAL);

	rs = &rx50state;

	/* lock out others */
	i = spl4();
	while (rs->rs_flags & RS_BUSY) {
		rs->rs_flags |= RS_WANT;
		sleep((caddr_t) &rx50state, PZERO - 1);
	}
	rs->rs_flags |= RS_BUSY;
	rs->rs_drive = rx50unit(dev);
	splx(i);

	rxaddr = &rx50device;
	error = 0;

	while (uio->uio_resid) {
		rs->rs_blkno = uio->uio_offset >> 9;
		if (rs->rs_blkno >= RX50MAXSEC) {
			if (rs->rs_blkno > RX50MAXSEC)
				error = EINVAL;
D 2
			else if (rw == UIO_WRITE)
E 2
I 2
			else if (uio->uio_rw == UIO_WRITE)
E 2
				error = ENOSPC;
			/* else ``eof'' */
			break;
		}
		rs->rs_flags &= ~(RS_ERROR | RS_DONE);
D 2
		if (rw == UIO_WRITE) {
E 2
I 2
		if (uio->uio_rw == UIO_WRITE) {
E 2
			/* copy the data to the RX50 silo */
D 2
			error = uiomove(secbuf, 512, UIO_WRITE, uio);
E 2
I 2
			error = uiomove(secbuf, 512, uio);
E 2
			if (error)
				break;
			i = rxaddr->rxrda;
			for (cp = secbuf, i = 512; --i >= 0;)
				rxaddr->rxfdb = *cp++;
			i = RXCMD_WRITE;
		} else
			i = RXCMD_READ;
		rxaddr->rxcmd = i | driveselect[rs->rs_drive];
		i = rs->rs_blkno - ((t = rs->rs_blkno / RX50SEC) * RX50SEC);
		rxaddr->rxtrk = t == 79 ? 0 : t + 1;
#ifdef notdef
		rxaddr->rxsec = "\1\3\5\7\11\1\3\5\7"[(2*t + i) % 5] + (i > 4);
#else
		rxaddr->rxsec = RX50SKEW(i, t);
#endif
		i = rxaddr->rxgo;	/* start it up */
		i = spl4();
		while ((rs->rs_flags & RS_DONE) == 0)
			sleep((caddr_t) &rs->rs_blkno, PRIBIO);
		splx(i);
		if (rs->rs_flags & RS_ERROR) {
			error = EIO;
			break;
		}
D 2
		if (rw == UIO_READ) {
E 2
I 2
		if (uio->uio_rw == UIO_READ) {
E 2
			/* copy the data out of the silo */
			i = rxaddr->rxrda;
			for (cp = secbuf, i = 512; --i >= 0;)
				*cp++ = rxaddr->rxedb;
D 2
			error = uiomove(secbuf, 512, UIO_READ, uio);
E 2
I 2
			error = uiomove(secbuf, 512, uio);
E 2
			if (error)
				break;
		}
	}

	/* let others in */
	rs->rs_flags &= ~RS_BUSY;
	if (rs->rs_flags & RS_WANT)
		wakeup((caddr_t) rs);

	return (error);
D 2
}

rx50read(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (rx50operation(dev, UIO_READ, uio));
}

rx50write(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (rx50operation(dev, UIO_WRITE, uio));
E 2
}

rx50intr()
{
	register struct rx50device *rxaddr = &rx50device;
	register struct rx50state *rs = &rx50state;
	int i;

#ifdef lint
	i = 0; i = i;
#endif

	/* ignore spurious interrupts */
	if ((rxaddr->rxcmd & RXCMD_DONE) == 0)
		return;
	if ((rs->rs_flags & RS_BUSY) == 0) {
		printf("stray rx50 interrupt ignored\n");
		return;
	}
	if (rxaddr->rxcmd & RXCMD_ERROR) {
		printf(
	"csa%d: hard error sn%d: cmd=%x trk=%x sec=%x csc=%x ict=%x ext=%x\n",
			rs->rs_drive + 1, rs->rs_blkno,
			rxaddr->rxcmd, rxaddr->rxtrk, rxaddr->rxsec,
			rxaddr->rxcsc, rxaddr->rxict, rxaddr->rxext);
		rxaddr->rxcmd = RXCMD_RESET;
		i = rxaddr->rxgo;
		rs->rs_flags |= RS_ERROR;
	}
	rs->rs_flags |= RS_DONE;
	wakeup((caddr_t) &rs->rs_blkno);
}
#endif
E 1
