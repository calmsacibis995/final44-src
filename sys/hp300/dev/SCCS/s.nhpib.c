h08558
s 00005/00000/00331
d D 8.2 94/01/12 09:54:15 bostic 10 9
c lint
e
s 00002/00002/00329
d D 8.1 93/06/10 21:33:42 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00326
d D 7.8 92/12/27 20:53:08 hibler 8 7
c cannot use timeout at boot time
e
s 00007/00007/00319
d D 7.7 92/10/11 09:24:04 bostic 7 6
c make kernel includes standard
e
s 00008/00004/00318
d D 7.6 92/07/07 19:02:35 torek 6 5
c lint
e
s 00001/00001/00321
d D 7.5 92/06/05 15:30:47 hibler 5 4
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00321
d D 7.4 91/05/07 09:49:04 hibler 4 3
c internalhpib is now caddr_t
e
s 00004/00003/00318
d D 7.3 90/12/16 16:36:44 bostic 3 2
c kernel reorg
e
s 00081/00084/00240
d D 7.2 90/11/04 19:37:40 mckusick 2 1
c update from Mike Hibler
e
s 00324/00000/00000
d D 7.1 90/05/08 22:07:05 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Internal/98624 HPIB driver
 */
#include "hpib.h"
#if NHPIB > 0

D 3
#include "param.h"
#include "systm.h"
#include "buf.h"
E 3
I 3
D 7
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/buf.h"
E 7
I 7
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
E 7

E 3
D 5
#include "device.h"
E 5
I 5
D 7
#include "hp/dev/device.h"
E 5
#include "nhpibreg.h"
#include "hpibvar.h"
#include "dmavar.h"
E 7
I 7
#include <hp/dev/device.h>
#include <hp300/dev/nhpibreg.h>
#include <hp300/dev/hpibvar.h>
#include <hp300/dev/dmavar.h>
E 7

nhpibtype(hc)
	register struct hp_ctlr *hc;
{
	register struct hpib_softc *hs = &hpib_softc[hc->hp_unit];
	register struct nhpibdevice *hd = (struct nhpibdevice *)hc->hp_addr;

D 4
	if ((int)hc->hp_addr == internalhpib) {
E 4
I 4
	if (hc->hp_addr == internalhpib) {
E 4
		hs->sc_type = HPIBA;
		hs->sc_ba = HPIBA_BA;
		hc->hp_ipl = HPIBA_IPL;
	}
	else if (hd->hpib_cid == HPIBB) {
		hs->sc_type = HPIBB;
		hs->sc_ba = hd->hpib_csa & CSA_BA;
		hc->hp_ipl = HPIB_IPL(hd->hpib_ids);
	}
	else
		return(0);
	return(1);
}

nhpibreset(unit)
I 10
	int unit;
E 10
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct nhpibdevice *hd;

	hd = (struct nhpibdevice *)hs->sc_hc->hp_addr;
	hd->hpib_acr = AUX_SSWRST;
	hd->hpib_ar = hs->sc_ba;
	hd->hpib_lim = LIS_ERR;
	hd->hpib_mim = 0;
	hd->hpib_acr = AUX_CDAI;
	hd->hpib_acr = AUX_CSHDW;
	hd->hpib_acr = AUX_SSTD1;
	hd->hpib_acr = AUX_SVSTD1;
	hd->hpib_acr = AUX_CPP;
	hd->hpib_acr = AUX_CHDFA;
	hd->hpib_acr = AUX_CHDFE;
	hd->hpib_acr = AUX_RHDF;
	hd->hpib_acr = AUX_CSWRST;
	nhpibifc(hd);
	hd->hpib_ie = IDS_IE;
	hd->hpib_data = C_DCL;
	DELAY(100000);
}

nhpibifc(hd)
	register struct nhpibdevice *hd;
{
	hd->hpib_acr = AUX_TCA;
	hd->hpib_acr = AUX_CSRE;
	hd->hpib_acr = AUX_SSIC;
	DELAY(100);
	hd->hpib_acr = AUX_CSIC;
	hd->hpib_acr = AUX_SSRE;
}

D 2
nhpibsend(unit, slave, sec, addr, cnt)
E 2
I 2
nhpibsend(unit, slave, sec, addr, origcnt)
I 10
	int unit, slave, sec, origcnt;
E 10
E 2
	register char *addr;
D 2
	register int cnt;
E 2
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct nhpibdevice *hd;
D 2
	register int origcnt = cnt;
E 2
I 2
	register int cnt = origcnt;
E 2

	hd = (struct nhpibdevice *)hs->sc_hc->hp_addr;
	hd->hpib_acr = AUX_TCA;
	hd->hpib_data = C_UNL;
D 2
	nhpibowait(hd);
E 2
I 2
	if (nhpibwait(hd, MIS_BO))
		goto senderror;
E 2
	hd->hpib_data = C_TAG + hs->sc_ba;
	hd->hpib_acr = AUX_STON;
D 2
	nhpibowait(hd);
E 2
I 2
	if (nhpibwait(hd, MIS_BO))
		goto senderror;
E 2
	hd->hpib_data = C_LAG + slave;
D 2
	nhpibowait(hd);
E 2
I 2
	if (nhpibwait(hd, MIS_BO))
		goto senderror;
E 2
	if (sec != -1) {
		hd->hpib_data = C_SCG + sec;
D 2
		nhpibowait(hd);
E 2
I 2
		if (nhpibwait(hd, MIS_BO))
			goto senderror;
E 2
	}
	hd->hpib_acr = AUX_GTS;
	if (cnt) {
D 2
		while (--cnt) {
E 2
I 2
		while (--cnt > 0) {
E 2
			hd->hpib_data = *addr++;
D 2
			if (nhpibowait(hd) < 0) {
				nhpibifc(hd);
				cnt++;
				goto out;
			}
E 2
I 2
			if (nhpibwait(hd, MIS_BO))
				goto senderror;
E 2
		}
		hd->hpib_acr = AUX_EOI;
		hd->hpib_data = *addr;
D 2
		if (nhpibowait(hd) < 0) {
			nhpibifc(hd);
			cnt++;
		}
		else
			hd->hpib_acr = AUX_TCA;
E 2
I 2
		if (nhpibwait(hd, MIS_BO))
			goto senderror;
		hd->hpib_acr = AUX_TCA;
#if 0
		/*
		 * May be causing 345 disks to hang due to interference
		 * with PPOLL mechanism.
		 */
		hd->hpib_data = C_UNL;
		(void) nhpibwait(hd, MIS_BO);
#endif
E 2
	}
D 2
out:
	return(origcnt - cnt);
E 2
I 2
	return(origcnt);
senderror:
	nhpibifc(hd);
	return(origcnt - cnt - 1);
E 2
}

D 2
nhpibrecv(unit, slave, sec, addr, cnt)
E 2
I 2
nhpibrecv(unit, slave, sec, addr, origcnt)
I 10
	int unit, slave, sec, origcnt;
E 10
E 2
	register char *addr;
D 2
	register int cnt;
E 2
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct nhpibdevice *hd;
D 2
	register int origcnt = cnt;
E 2
I 2
	register int cnt = origcnt;
E 2

	hd = (struct nhpibdevice *)hs->sc_hc->hp_addr;
	hd->hpib_acr = AUX_TCA;
	hd->hpib_data = C_UNL;
D 2
	nhpibowait(hd);
E 2
I 2
	if (nhpibwait(hd, MIS_BO))
		goto recverror;
E 2
	hd->hpib_data = C_LAG + hs->sc_ba;
	hd->hpib_acr = AUX_SLON;
D 2
	nhpibowait(hd);
E 2
I 2
	if (nhpibwait(hd, MIS_BO))
		goto recverror;
E 2
	hd->hpib_data = C_TAG + slave;
D 2
	nhpibowait(hd);
E 2
I 2
	if (nhpibwait(hd, MIS_BO))
		goto recverror;
E 2
	if (sec != -1) {
		hd->hpib_data = C_SCG + sec;
D 2
		nhpibowait(hd);
E 2
I 2
		if (nhpibwait(hd, MIS_BO))
			goto recverror;
E 2
	}
	hd->hpib_acr = AUX_RHDF;
	hd->hpib_acr = AUX_GTS;
	if (cnt) {
		while (--cnt >= 0) {
D 2
			if (nhpibiwait(hd) < 0) {
				nhpibifc(hd);
				break;
			}
E 2
I 2
			if (nhpibwait(hd, MIS_BI))
				goto recvbyteserror;
E 2
			*addr++ = hd->hpib_data;
		}
D 2
		cnt++;
E 2
		hd->hpib_acr = AUX_TCA;
I 2
		hd->hpib_data = (slave == 31) ? C_UNA : C_UNT;
		(void) nhpibwait(hd, MIS_BO);
E 2
	}
D 2
	return(origcnt - cnt);
E 2
I 2
	return(origcnt);
recverror:
	nhpibifc(hd);
recvbyteserror:
	return(origcnt - cnt - 1);
E 2
}

nhpibgo(unit, slave, sec, addr, count, rw)
	register int unit, slave;
I 10
	int sec, count, rw;
E 10
	char *addr;
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct nhpibdevice *hd;

	hd = (struct nhpibdevice *)hs->sc_hc->hp_addr;
	hs->sc_flags |= HPIBF_IO;
	if (rw == B_READ)
		hs->sc_flags |= HPIBF_READ;
#ifdef DEBUG
	else if (hs->sc_flags & HPIBF_READ) {
		printf("nhpibgo: HPIBF_READ still set\n");
		hs->sc_flags &= ~HPIBF_READ;
	}
#endif
	hs->sc_count = count;
	hs->sc_addr = addr;
	if (hs->sc_flags & HPIBF_READ) {
		hs->sc_curcnt = count;
		dmago(hs->sc_dq.dq_ctlr, addr, count, DMAGO_BYTE|DMAGO_READ);
		nhpibrecv(unit, slave, sec, 0, 0);
		hd->hpib_mim = MIS_END;
D 2
	}
	else {
		if (count == 1) {
			hs->sc_curcnt = 1;
			dmago(hs->sc_dq.dq_ctlr, addr, 1, DMAGO_BYTE);
			nhpibsend(unit, slave, sec, 0, 0);
			hd->hpib_acr = AUX_EOI;
E 2
I 2
	} else {
		hd->hpib_mim = 0;
		if (count < hpibdmathresh) {
			hs->sc_curcnt = count;
			nhpibsend(unit, slave, sec, addr, count);
			nhpibdone(unit);
			return;
E 2
		}
D 2
		else {
			hs->sc_curcnt = count - 1;
			dmago(hs->sc_dq.dq_ctlr, addr, count - 1, DMAGO_BYTE);
			nhpibsend(unit, slave, sec, 0, 0);
		}
E 2
I 2
		hs->sc_curcnt = --count;
		dmago(hs->sc_dq.dq_ctlr, addr, count, DMAGO_BYTE);
		nhpibsend(unit, slave, sec, 0, 0);
E 2
	}
	hd->hpib_ie = IDS_IE | IDS_DMA(hs->sc_dq.dq_ctlr);
}

nhpibdone(unit)
	register int unit;
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct nhpibdevice *hd;
	register int cnt;

	hd = (struct nhpibdevice *)hs->sc_hc->hp_addr;
	cnt = hs->sc_curcnt;
	hs->sc_addr += cnt;
	hs->sc_count -= cnt;
D 2
	if (hs->sc_flags & HPIBF_READ) {
		hs->sc_flags |= HPIBF_DONE;
		hd->hpib_ie = IDS_IE;
	} else {
E 2
I 2
	hs->sc_flags |= HPIBF_DONE;
	hd->hpib_ie = IDS_IE;
	if ((hs->sc_flags & HPIBF_READ) == 0) {
E 2
		if (hs->sc_count == 1) {
D 2
			hs->sc_curcnt = 1;
E 2
I 2
			(void) nhpibwait(hd, MIS_BO);
E 2
			hd->hpib_acr = AUX_EOI;
D 2
			dmago(hs->sc_dq.dq_ctlr, hs->sc_addr, 1, DMAGO_BYTE);
			return;
E 2
I 2
			hd->hpib_data = *hs->sc_addr;
			hd->hpib_mim = MIS_BO;
E 2
		}
D 2
		hs->sc_flags |= HPIBF_DONE;
		hd->hpib_ie = IDS_IE;
		hd->hpib_mim = MIS_BO;
E 2
I 2
#ifdef DEBUG
		else if (hs->sc_count)
			panic("nhpibdone");
#endif
E 2
	}
}

nhpibintr(unit)
	register int unit;
{
	register struct hpib_softc *hs = &hpib_softc[unit];
	register struct nhpibdevice *hd;
D 2
	register struct devqueue *dq = hs->sc_sq.dq_forw;
E 2
I 2
	register struct devqueue *dq;
E 2
	register int stat0;
	int stat1;

#ifdef lint
	if (stat1 = unit) return(1);
#endif
	hd = (struct nhpibdevice *)hs->sc_hc->hp_addr;
	if ((hd->hpib_ids & IDS_IR) == 0)
		return(0);
	stat0 = hd->hpib_mis;
	stat1 = hd->hpib_lis;
I 2
	dq = hs->sc_sq.dq_forw;
E 2
	if (hs->sc_flags & HPIBF_IO) {
		hd->hpib_mim = 0;
		if ((hs->sc_flags & HPIBF_DONE) == 0)
			dmastop(hs->sc_dq.dq_ctlr);
		hd->hpib_acr = AUX_TCA;
		hs->sc_flags &= ~(HPIBF_DONE|HPIBF_IO|HPIBF_READ);
		dmafree(&hs->sc_dq);
		(dq->dq_driver->d_intr)(dq->dq_unit);
D 2
		return(1);
	}
	if (hs->sc_flags & HPIBF_PPOLL) {
E 2
I 2
	} else if (hs->sc_flags & HPIBF_PPOLL) {
E 2
		hd->hpib_mim = 0;
		stat0 = nhpibppoll(unit);
		if (stat0 & (0x80 >> dq->dq_slave)) {
			hs->sc_flags &= ~HPIBF_PPOLL;
			(dq->dq_driver->d_intr)(dq->dq_unit);
		}
D 2
		return(1);
E 2
I 2
#ifdef DEBUG
		else
			printf("hpib%d: PPOLL intr bad status %x\n",
			       unit, stat0);
#endif
E 2
	}
	return(1);
}

nhpibppoll(unit)
D 2
	register int unit;
E 2
I 2
	int unit;
E 2
{
D 2
	register struct hpib_softc *hs = &hpib_softc[unit];
E 2
	register struct nhpibdevice *hd;
	register int ppoll;

D 2
	hd = (struct nhpibdevice *)hs->sc_hc->hp_addr;
E 2
I 2
	hd = (struct nhpibdevice *)hpib_softc[unit].sc_hc->hp_addr;
E 2
	hd->hpib_acr = AUX_SPP;
	DELAY(25);
	ppoll = hd->hpib_cpt;
	hd->hpib_acr = AUX_CPP;
	return(ppoll);
}

D 2
nhpibowait(hd)
E 2
I 2
nhpibwait(hd, x)
E 2
	register struct nhpibdevice *hd;
I 10
	int x;
E 10
{
D 2
	extern int hpibtimeout;
E 2
	register int timo = hpibtimeout;

D 2
	while ((hd->hpib_mis & MIS_BO) == 0 && --timo)
		;
E 2
I 2
	while ((hd->hpib_mis & x) == 0 && --timo)
		DELAY(1);
E 2
	if (timo == 0)
		return(-1);
	return(0);
}

D 2
nhpibiwait(hd)
	register struct nhpibdevice *hd;
{
	extern int hpibtimeout;
	register int timo = hpibtimeout;

	while ((hd->hpib_mis & MIS_BI) == 0 && --timo)
		;
	if (timo == 0)
		return(-1);
	return(0);
}

E 2
D 6
nhpibppwatch(unit)
	register int unit;
E 6
I 6
void
nhpibppwatch(arg)
	void *arg;
E 6
{
D 6
	register struct hpib_softc *hs = &hpib_softc[unit];
E 6
I 6
	register struct hpib_softc *hs;
	register int unit;
I 8
	extern int cold;
E 8
E 6
D 2
	register struct devqueue *dq = hs->sc_sq.dq_forw;
	register int slave = 0x80 >> dq->dq_slave;
E 2

I 6
	unit = (int)arg;
	hs = &hpib_softc[unit];
E 6
	if ((hs->sc_flags & HPIBF_PPOLL) == 0)
		return;
I 8
again:
E 8
D 2
	if (nhpibppoll(unit) & slave)
E 2
I 2
	if (nhpibppoll(unit) & (0x80 >> hs->sc_sq.dq_forw->dq_slave))
E 2
       		((struct nhpibdevice *)hs->sc_hc->hp_addr)->hpib_mim = MIS_BO;
I 8
	else if (cold)
		/* timeouts not working yet */
		goto again;
E 8
	else
D 6
		timeout(nhpibppwatch, unit, 1);
E 6
I 6
		timeout(nhpibppwatch, (void *)unit, 1);
E 6
}
#endif
E 1
