h41007
s 00007/00000/00495
d D 8.2 94/01/12 09:54:14 bostic 8 7
c lint
e
s 00002/00002/00493
d D 8.1 93/06/10 21:32:24 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00007/00486
d D 7.6 92/10/11 09:23:45 bostic 6 5
c make kernel includes standard
e
s 00009/00004/00484
d D 7.5 92/07/07 19:02:34 torek 5 4
c lint
e
s 00013/00004/00475
d D 7.4 92/06/05 15:30:45 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00003/00003/00476
d D 7.3 90/12/16 16:35:43 bostic 3 2
c kernel reorg
e
s 00054/00073/00425
d D 7.2 90/11/04 19:23:24 mckusick 2 1
c update from Mike Hibler
e
s 00498/00000/00000
d D 7.1 90/05/08 22:06:53 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * 98625A/B HPIB driver
 */
#include "hpib.h"
#if NHPIB > 0

D 3
#include "param.h"
#include "systm.h"
#include "buf.h"
E 3
I 3
D 6
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/buf.h"
E 3
D 4
#include "device.h"
E 4
I 4
#include "hp/dev/device.h"
E 4
#include "fhpibreg.h"
#include "hpibvar.h"
#include "dmavar.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>

#include <hp/dev/device.h>

#include <hp300/dev/fhpibreg.h>
#include <hp300/dev/hpibvar.h>
#include <hp300/dev/dmavar.h>
E 6

/*
 * Inline version of fhpibwait to be used in places where
 * we don't worry about getting hung.
 */
D 2
#define	FHPIBWAIT(hd, m)	while (((hd)->hpib_intr & (m)) == 0)
E 2
I 2
#define	FHPIBWAIT(hd, m)	while (((hd)->hpib_intr & (m)) == 0) DELAY(1)
E 2

#ifdef DEBUG
int	fhpibdebugunit = -1;
int	fhpibdebug = 0;
#define FDB_FAIL	0x01
#define FDB_DMA		0x02
#define FDB_WAIT	0x04
#define FDB_PPOLL	0x08

int	dopriodma = 0;	/* use high priority DMA */
int	doworddma = 1;	/* non-zero if we should attempt word dma */
D 2
int	dolworddma = 1;	/* use longword dma (scsi) */
E 2
int	doppollint = 1;	/* use ppoll interrupts instead of watchdog */
I 4
int	fhpibppolldelay = 50;
E 4

long	fhpibbadint[2] = { 0 };
long	fhpibtransfer[NHPIB] = { 0 };
long	fhpibnondma[NHPIB] = { 0 };
long	fhpibworddma[NHPIB] = { 0 };
I 4
long	fhpibppollfail[NHPIB] = { 0 };
E 4
D 2
long	fhpibremain[NHPIB] = { 0 };
long	fhpibloops[NHPIB] = { 0 };

E 2
#endif

int	fhpibcmd[NHPIB];
D 2
int	dmathresh = 3;	/* char count beyond which we will attempt dma */
E 2

D 2
extern	int hpibtimeout;

E 2
fhpibtype(hc)
	register struct hp_ctlr *hc;
{
	register struct hpib_softc *hs = &hpib_softc[hc->hp_unit];
	register struct fhpibdevice *hd = (struct fhpibdevice *)hc->hp_addr;

	if (hd->hpib_cid != HPIBC)
		return(0);
	hs->sc_type = HPIBC;
	hs->sc_ba = HPIBC_BA;
	hc->hp_ipl = HPIB_IPL(hd->hpib_ids);
	return(1);
}

fhpibreset(unit)
I 8
	int unit;
E 8
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct fhpibdevice *hd;

	hd = (struct fhpibdevice *)hs->sc_hc->hp_addr;
	hd->hpib_cid = 0xFF;
	DELAY(100);
	hd->hpib_cmd = CT_8BIT;
	hd->hpib_ar = AR_ARONC;
	fhpibifc(hd);
	hd->hpib_ie = IDS_IE;
	hd->hpib_data = C_DCL;
	DELAY(100000);
	/*
	 * See if we can do word dma.
	 * If so, we should be able to write and read back the appropos bit.
	 */
	hd->hpib_ie |= IDS_WDMA;
	if (hd->hpib_ie & IDS_WDMA) {
		hd->hpib_ie &= ~IDS_WDMA;
		hs->sc_flags |= HPIBF_DMA16;
#ifdef DEBUG
		if (fhpibdebug & FDB_DMA)
			printf("fhpibtype: unit %d has word dma\n", unit);

#endif
	}
}

fhpibifc(hd)
	register struct fhpibdevice *hd;
{
	hd->hpib_cmd |= CT_IFC;
	hd->hpib_cmd |= CT_INITFIFO;
	DELAY(100);
	hd->hpib_cmd &= ~CT_IFC;
	hd->hpib_cmd |= CT_REN;
	hd->hpib_stat = ST_ATN;
}

D 2
fhpibsend(unit, slave, sec, addr, cnt)
E 2
I 2
fhpibsend(unit, slave, sec, addr, origcnt)
I 8
	int unit, slave, sec, origcnt;
E 8
E 2
	register char *addr;
D 2
	register int cnt;
E 2
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct fhpibdevice *hd;
I 2
	register int cnt = origcnt;
E 2
	register int timo;
D 2
	int origcnt = cnt;
	int err = 0;
E 2

	hd = (struct fhpibdevice *)hs->sc_hc->hp_addr;
	hd->hpib_stat = 0;
	hd->hpib_imask = IM_IDLE | IM_ROOM;
	if (fhpibwait(hd, IM_IDLE) < 0)
D 2
		err++;
E 2
I 2
		goto senderr;
E 2
	hd->hpib_stat = ST_ATN;
	hd->hpib_data = C_UNL;
	hd->hpib_data = C_TAG + hs->sc_ba;
	hd->hpib_data = C_LAG + slave;
	if (sec != -1)
		hd->hpib_data = C_SCG + sec;
	if (fhpibwait(hd, IM_IDLE) < 0)
D 2
		err++;
	hd->hpib_stat = ST_WRITE;
	if (cnt && !err) {
E 2
I 2
		goto senderr;
	if (cnt) {
		hd->hpib_stat = ST_WRITE;
E 2
		while (--cnt) {
			hd->hpib_data = *addr++;
			timo = hpibtimeout;
D 2
			while ((hd->hpib_intr & IM_ROOM) == 0)
				if (--timo == 0) {
					err++;
					goto out;
				}
E 2
I 2
			while ((hd->hpib_intr & IM_ROOM) == 0) {
				if (--timo <= 0)
					goto senderr;
				DELAY(1);
			}
E 2
		}
		hd->hpib_stat = ST_EOI;
		hd->hpib_data = *addr;
		FHPIBWAIT(hd, IM_ROOM);
		hd->hpib_stat = ST_ATN;
		/* XXX: HP-UX claims bug with CS80 transparent messages */
		if (sec == 0x12)
			DELAY(150);
		hd->hpib_data = C_UNL;
D 2
		if (fhpibwait(hd, IM_IDLE) < 0)
			err++;
E 2
I 2
		(void) fhpibwait(hd, IM_IDLE);
E 2
	}
D 2
out:
	if (err) {
		cnt++;
		fhpibifc(hd);
E 2
I 2
	hd->hpib_imask = 0;
	return (origcnt);
senderr:
	hd->hpib_imask = 0;
	fhpibifc(hd);
E 2
#ifdef DEBUG
D 2
		if (fhpibdebug & FDB_FAIL) {
			printf("hpib%d: fhpibsend failed: slave %d, sec %x, ",
			       unit, slave, sec);
			printf("sent %d of %d bytes\n", origcnt-cnt, origcnt);
		}
#endif
E 2
I 2
	if (fhpibdebug & FDB_FAIL) {
		printf("hpib%d: fhpibsend failed: slave %d, sec %x, ",
			unit, slave, sec);
		printf("sent %d of %d bytes\n", origcnt-cnt-1, origcnt);
E 2
	}
D 2
	hd->hpib_imask = 0;
	return(origcnt - cnt);
E 2
I 2
#endif
	return(origcnt - cnt - 1);
E 2
}

D 2
fhpibrecv(unit, slave, sec, addr, cnt)
E 2
I 2
fhpibrecv(unit, slave, sec, addr, origcnt)
I 8
	int unit, slave, sec, origcnt;
E 8
E 2
	register char *addr;
D 2
	register int cnt;
E 2
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct fhpibdevice *hd;
I 2
	register int cnt = origcnt;
E 2
	register int timo;
D 2
	int origcnt = cnt;
	int err = 0;
E 2

	hd = (struct fhpibdevice *)hs->sc_hc->hp_addr;
	hd->hpib_stat = 0;
	hd->hpib_imask = IM_IDLE | IM_ROOM | IM_BYTE;
	if (fhpibwait(hd, IM_IDLE) < 0)
D 2
		err++;
E 2
I 2
		goto recverror;
E 2
	hd->hpib_stat = ST_ATN;
	hd->hpib_data = C_UNL;
	hd->hpib_data = C_LAG + hs->sc_ba;
	hd->hpib_data = C_TAG + slave;
	if (sec != -1)
		hd->hpib_data = C_SCG + sec;
	if (fhpibwait(hd, IM_IDLE) < 0)
D 2
		err++;
E 2
I 2
		goto recverror;
E 2
	hd->hpib_stat = ST_READ0;
	hd->hpib_data = 0;
D 2
	if (cnt && !err) {
		do {
E 2
I 2
	if (cnt) {
		while (--cnt >= 0) {
E 2
			timo = hpibtimeout;
D 2
			while ((hd->hpib_intr & IM_BYTE) == 0)
				if (--timo == 0) {
					err++;
					goto out;
				}
E 2
I 2
			while ((hd->hpib_intr & IM_BYTE) == 0) {
				if (--timo == 0)
					goto recvbyteserror;
				DELAY(1);
			}
E 2
			*addr++ = hd->hpib_data;
D 2
		} while (--cnt);
out:
E 2
I 2
		}
E 2
		FHPIBWAIT(hd, IM_ROOM);
		hd->hpib_stat = ST_ATN;
		hd->hpib_data = (slave == 31) ? C_UNA : C_UNT;
D 2
		if (fhpibwait(hd, IM_IDLE) < 0)
			err++;
E 2
I 2
		(void) fhpibwait(hd, IM_IDLE);
E 2
	}
D 2
	if (err) {
		if (!cnt)
			cnt++;
		fhpibifc(hd);
E 2
I 2
	hd->hpib_imask = 0;
	return (origcnt);

recverror:
	fhpibifc(hd);
recvbyteserror:
	hd->hpib_imask = 0;
E 2
#ifdef DEBUG
D 2
		if (fhpibdebug & FDB_FAIL) {
			printf("hpib%d: fhpibrecv failed: slave %d, sec %x, ",
			       unit, slave, sec);
			printf("got %d of %d bytes\n", origcnt-cnt, origcnt);
		}
#endif
E 2
I 2
	if (fhpibdebug & FDB_FAIL) {
		printf("hpib%d: fhpibrecv failed: slave %d, sec %x, ",
		       unit, slave, sec);
		printf("got %d of %d bytes\n", origcnt-cnt-1, origcnt);
E 2
	}
D 2
	hd->hpib_imask = 0;
	return(origcnt - cnt);
E 2
I 2
#endif
	return(origcnt - cnt - 1);
E 2
}

fhpibgo(unit, slave, sec, addr, count, rw)
	register int unit;
I 8
	int slave, sec, count, rw;
E 8
	char *addr;
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct fhpibdevice *hd;
	register int i;
	int flags = 0;

#ifdef lint
	i = unit; if (i) return;
#endif
	hd = (struct fhpibdevice *)hs->sc_hc->hp_addr;
	hs->sc_flags |= HPIBF_IO;
	if (rw == B_READ)
		hs->sc_flags |= HPIBF_READ;
#ifdef DEBUG
	else if (hs->sc_flags & HPIBF_READ) {
		printf("fhpibgo: HPIBF_READ still set\n");
		hs->sc_flags &= ~HPIBF_READ;
	}
#endif
	hs->sc_count = count;
	hs->sc_addr = addr;
#ifdef DEBUG
	fhpibtransfer[unit]++;
#endif
	if ((hs->sc_flags & HPIBF_DMA16) &&
	    ((int)addr & 1) == 0 && count && (count & 1) == 0
#ifdef DEBUG
	    && doworddma
#endif
	    ) {
#ifdef DEBUG
		fhpibworddma[unit]++;
#endif
		flags |= DMAGO_WORD;
		hd->hpib_latch = 0;
	}
#ifdef DEBUG
	if (dopriodma)
		flags |= DMAGO_PRI;
#endif
	if (hs->sc_flags & HPIBF_READ) {
		fhpibcmd[unit] = CT_REN | CT_8BIT;
		hs->sc_curcnt = count;
		dmago(hs->sc_dq.dq_ctlr, addr, count, flags|DMAGO_READ);
		if (fhpibrecv(unit, slave, sec, 0, 0) < 0) {
#ifdef DEBUG
			printf("fhpibgo: recv failed, retrying...\n");
#endif
			(void) fhpibrecv(unit, slave, sec, 0, 0);
		}
		i = hd->hpib_cmd;
		hd->hpib_cmd = fhpibcmd[unit];
		hd->hpib_ie = IDS_DMA(hs->sc_dq.dq_ctlr) |
			((flags & DMAGO_WORD) ? IDS_WDMA : 0);
		return;
	}
	fhpibcmd[unit] = CT_REN | CT_8BIT | CT_FIFOSEL;
D 2
	if (count < dmathresh) {
E 2
I 2
	if (count < hpibdmathresh) {
E 2
#ifdef DEBUG
		fhpibnondma[unit]++;
D 2
		fhpibworddma[unit]--;
E 2
I 2
		if (flags & DMAGO_WORD)
			fhpibworddma[unit]--;
E 2
#endif
		hs->sc_curcnt = count;
		(void) fhpibsend(unit, slave, sec, addr, count);
		fhpibdone(unit);
		return;
	}
	count -= (flags & DMAGO_WORD) ? 2 : 1;
	hs->sc_curcnt = count;
	dmago(hs->sc_dq.dq_ctlr, addr, count, flags);
	if (fhpibsend(unit, slave, sec, 0, 0) < 0) {
#ifdef DEBUG
		printf("fhpibgo: send failed, retrying...\n");
#endif
		(void) fhpibsend(unit, slave, sec, 0, 0);
	}
	i = hd->hpib_cmd;
	hd->hpib_cmd = fhpibcmd[unit];
	hd->hpib_ie = IDS_DMA(hs->sc_dq.dq_ctlr) | IDS_WRITE |
		((flags & DMAGO_WORD) ? IDS_WDMA : 0);
}

fhpibdone(unit)
I 8
	int unit;
E 8
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct fhpibdevice *hd;
	register char *addr;
	register int cnt;

	hd = (struct fhpibdevice *)hs->sc_hc->hp_addr;
	cnt = hs->sc_curcnt;
	hs->sc_addr += cnt;
	hs->sc_count -= cnt;
#ifdef DEBUG
	if ((fhpibdebug & FDB_DMA) && fhpibdebugunit == unit)
		printf("fhpibdone: addr %x cnt %d\n",
		       hs->sc_addr, hs->sc_count);
#endif
	if (hs->sc_flags & HPIBF_READ)
		hd->hpib_imask = IM_IDLE | IM_BYTE;
	else {
		cnt = hs->sc_count;
		if (cnt) {
			addr = hs->sc_addr;
			hd->hpib_imask = IM_IDLE | IM_ROOM;
D 2
#ifdef DEBUG
			fhpibremain[unit]++;
			while ((hd->hpib_intr & IM_IDLE) == 0)
				fhpibloops[unit]++;
#else
E 2
			FHPIBWAIT(hd, IM_IDLE);
D 2
#endif
E 2
			hd->hpib_stat = ST_WRITE;
			while (--cnt) {
				hd->hpib_data = *addr++;
				FHPIBWAIT(hd, IM_ROOM);
			}
			hd->hpib_stat = ST_EOI;
			hd->hpib_data = *addr;
		}
		hd->hpib_imask = IM_IDLE;
	}
	hs->sc_flags |= HPIBF_DONE;
	hd->hpib_stat = ST_IENAB;
	hd->hpib_ie = IDS_IE;
}

fhpibintr(unit)
	register int unit;
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct fhpibdevice *hd;
	register struct devqueue *dq;
	register int stat0;

	hd = (struct fhpibdevice *)hs->sc_hc->hp_addr;
	stat0 = hd->hpib_ids;
	if ((stat0 & (IDS_IE|IDS_IR)) != (IDS_IE|IDS_IR)) {
#ifdef DEBUG
		if ((fhpibdebug & FDB_FAIL) && (stat0 & IDS_IR) &&
		    (hs->sc_flags & (HPIBF_IO|HPIBF_DONE)) != HPIBF_IO)
			printf("hpib%d: fhpibintr: bad status %x\n",
			       unit, stat0);
		fhpibbadint[0]++;
#endif
		return(0);
	}
	if ((hs->sc_flags & (HPIBF_IO|HPIBF_DONE)) == HPIBF_IO) {
#ifdef DEBUG
		fhpibbadint[1]++;
#endif
		return(0);
	}
#ifdef DEBUG
	if ((fhpibdebug & FDB_DMA) && fhpibdebugunit == unit)
		printf("fhpibintr: flags %x\n", hs->sc_flags);
#endif
	dq = hs->sc_sq.dq_forw;
	if (hs->sc_flags & HPIBF_IO) {
		stat0 = hd->hpib_cmd;
		hd->hpib_cmd = fhpibcmd[unit] & ~CT_8BIT;
		hd->hpib_stat = 0;
		hd->hpib_cmd = CT_REN | CT_8BIT;
		stat0 = hd->hpib_intr;
		hd->hpib_imask = 0;
		hs->sc_flags &= ~(HPIBF_DONE|HPIBF_IO|HPIBF_READ);
		dmafree(&hs->sc_dq);
		(dq->dq_driver->d_intr)(dq->dq_unit);
	} else if (hs->sc_flags & HPIBF_PPOLL) {
		stat0 = hd->hpib_intr;
#ifdef DEBUG
		if ((fhpibdebug & FDB_FAIL) &&
		    doppollint && (stat0 & IM_PPRESP) == 0)
			printf("hpib%d: fhpibintr: bad intr reg %x\n",
			       unit, stat0);
#endif
		hd->hpib_stat = 0;
		hd->hpib_imask = 0;
#ifdef DEBUG
		stat0 = fhpibppoll(unit);
		if ((fhpibdebug & FDB_PPOLL) && unit == fhpibdebugunit)
			printf("fhpibintr: got PPOLL status %x\n", stat0);
		if ((stat0 & (0x80 >> dq->dq_slave)) == 0) {
D 4
			printf("fhpibintr: PPOLL: unit %d slave %d stat %x\n",
			       unit, dq->dq_slave, stat0);
			return(1);
E 4
I 4
			/*
			 * XXX give it another shot (68040)
			 */
			fhpibppollfail[unit]++;
			DELAY(fhpibppolldelay);
			stat0 = fhpibppoll(unit);
			if ((stat0 & (0x80 >> dq->dq_slave)) == 0 &&
			    (fhpibdebug & FDB_PPOLL) && unit == fhpibdebugunit)
				printf("fhpibintr: PPOLL: unit %d slave %d stat %x\n",
				       unit, dq->dq_slave, stat0);
E 4
		}
#endif
		hs->sc_flags &= ~HPIBF_PPOLL;
		(dq->dq_driver->d_intr)(dq->dq_unit);
	}
	return(1);
}

fhpibppoll(unit)
I 8
	int unit;
E 8
{
	register struct fhpibdevice *hd;
	register int ppoll;

	hd = (struct fhpibdevice *)hpib_softc[unit].sc_hc->hp_addr;
	hd->hpib_stat = 0;
	hd->hpib_psense = 0;
	hd->hpib_pmask = 0xFF;
	hd->hpib_imask = IM_PPRESP | IM_PABORT;
	DELAY(25);
	hd->hpib_intr = IM_PABORT;
	ppoll = hd->hpib_data;
	if (hd->hpib_intr & IM_PABORT)
		ppoll = 0;
	hd->hpib_imask = 0;
	hd->hpib_pmask = 0;
	hd->hpib_stat = ST_IENAB;
	return(ppoll);
}

fhpibwait(hd, x)
	register struct fhpibdevice *hd;
I 8
	int x;
E 8
{
	register int timo = hpibtimeout;

	while ((hd->hpib_intr & x) == 0 && --timo)
D 2
		;
E 2
I 2
		DELAY(1);
E 2
	if (timo == 0) {
#ifdef DEBUG
		if (fhpibdebug & FDB_FAIL)
			printf("fhpibwait(%x, %x) timeout\n", hd, x);
#endif
		return(-1);
	}
	return(0);
}

/*
D 5
 * XXX: this will have to change if we every allow more than one
E 5
I 5
 * XXX: this will have to change if we ever allow more than one
E 5
 * pending operation per HP-IB.
 */
D 5
fhpibppwatch(unit)
E 5
I 5
void
fhpibppwatch(arg)
	void *arg;
E 5
{
D 5
	register struct hpib_softc *hs = &hpib_softc[unit];
E 5
I 5
	register int unit;
	register struct hpib_softc *hs;
E 5
	register struct fhpibdevice *hd;
	register int slave;

I 5
	unit = (int)arg;
	hs = &hpib_softc[unit];
E 5
	if ((hs->sc_flags & HPIBF_PPOLL) == 0)
		return;
	hd = (struct fhpibdevice *)hs->sc_hc->hp_addr;
	slave = (0x80 >> hs->sc_sq.dq_forw->dq_slave);
#ifdef DEBUG
	if (!doppollint) {
		if (fhpibppoll(unit) & slave) {
			hd->hpib_stat = ST_IENAB;
			hd->hpib_imask = IM_IDLE | IM_ROOM;
		} else
D 5
			timeout(fhpibppwatch, unit, 1);
E 5
I 5
			timeout(fhpibppwatch, (void *)unit, 1);
E 5
		return;
	}
	if ((fhpibdebug & FDB_PPOLL) && unit == fhpibdebugunit)
		printf("fhpibppwatch: sense request on %d\n", unit);
#endif
	hd->hpib_psense = ~slave;
	hd->hpib_pmask = slave;
	hd->hpib_stat = ST_IENAB;
	hd->hpib_imask = IM_PPRESP | IM_PABORT;
	hd->hpib_ie = IDS_IE;
}
#endif
E 1
