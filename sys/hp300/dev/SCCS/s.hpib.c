h46094
s 00008/00000/00213
d D 8.2 94/01/12 09:50:39 bostic 10 9
c lint
e
s 00002/00002/00211
d D 8.1 93/06/10 21:33:07 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00008/00204
d D 7.8 92/10/11 09:23:56 bostic 8 7
c make kernel includes standard
e
s 00004/00003/00208
d D 7.7 92/09/21 21:24:48 hibler 7 6
c mod of Carl's fix: scale config time timeout value by cpuspeed
e
s 00001/00001/00210
d D 7.6 92/08/21 16:40:09 staelin 6 5
c increase the hpibidtimeout so hpib devices are correctly autoconfigured
e
s 00003/00002/00208
d D 7.5 92/07/07 19:21:58 torek 5 4
c lint
e
s 00001/00001/00209
d D 7.4 92/06/05 15:30:57 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00005/00005/00205
d D 7.3 90/12/16 16:36:13 bostic 3 2
c kernel reorg
e
s 00001/00002/00209
d D 7.2 90/11/04 19:32:29 mckusick 2 1
c update from Mike Hibler
e
s 00211/00000/00000
d D 7.1 90/05/08 22:06:59 mckusick 1 0
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
 * HPIB driver
 */
#include "hpib.h"
#if NHPIB > 0

D 3
#include "param.h"
#include "systm.h"
#include "buf.h"
E 3
I 3
D 8
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
#include "hpibvar.h"
#include "dmavar.h"
E 8
I 8
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
E 8

D 3
#include "machine/cpu.h"
#include "machine/isr.h"
E 3
I 3
D 8
#include "../include/cpu.h"
#include "../hp300/isr.h"
E 8
I 8
#include <hp/dev/device.h>
#include <hp300/dev/hpibvar.h>
#include <hp300/dev/dmavar.h>

#include <machine/cpu.h>
#include <hp300/hp300/isr.h>
E 8
E 3

D 2
int	internalhpib = IOV(0x478000);

E 2
int	hpibinit(), hpibstart(), hpibgo(), hpibintr(), hpibdone();
struct	driver hpibdriver = {
	hpibinit, "hpib", hpibstart, hpibgo, hpibintr, hpibdone,
};

struct	hpib_softc hpib_softc[NHPIB];
struct	isr hpib_isr[NHPIB];
int	nhpibppoll(), fhpibppoll();

int	hpibtimeout = 100000;	/* # of status tests before we give up */
D 6
int	hpibidtimeout = 20000;	/* # of status tests for hpibid() calls */
E 6
I 6
D 7
int	hpibidtimeout = 100000;	/* # of status tests for hpibid() calls */
E 7
I 7
int	hpibidtimeout = 10000;	/* # of status tests for hpibid() calls */
E 7
E 6
I 2
int	hpibdmathresh = 3;	/* byte count beyond which to attempt dma */
E 2

hpibinit(hc)
	register struct hp_ctlr *hc;
{
	register struct hpib_softc *hs = &hpib_softc[hc->hp_unit];
	
	if (!nhpibtype(hc) && !fhpibtype(hc))
		return(0);
	hs->sc_hc = hc;
	hs->sc_dq.dq_unit = hc->hp_unit;
	hs->sc_dq.dq_driver = &hpibdriver;
	hs->sc_sq.dq_forw = hs->sc_sq.dq_back = &hs->sc_sq;
	hpib_isr[hc->hp_unit].isr_intr = hpibintr;
	hpib_isr[hc->hp_unit].isr_ipl = hc->hp_ipl;
	hpib_isr[hc->hp_unit].isr_arg = hc->hp_unit;
	isrlink(&hpib_isr[hc->hp_unit]);
	hpibreset(hc->hp_unit);
	return(1);
}

hpibreset(unit)
	register int unit;
{
	if (hpib_softc[unit].sc_type == HPIBC)
		fhpibreset(unit);
	else
		nhpibreset(unit);
}

hpibreq(dq)
	register struct devqueue *dq;
{
	register struct devqueue *hq;

	hq = &hpib_softc[dq->dq_ctlr].sc_sq;
	insque(dq, hq->dq_back);
	if (dq->dq_back == hq)
		return(1);
	return(0);
}

hpibfree(dq)
	register struct devqueue *dq;
{
	register struct devqueue *hq;

	hq = &hpib_softc[dq->dq_ctlr].sc_sq;
	remque(dq);
	if ((dq = hq->dq_forw) != hq)
		(dq->dq_driver->d_start)(dq->dq_unit);
}

hpibid(unit, slave)
I 10
	int unit, slave;
E 10
{
	short id;
	int ohpibtimeout;

	/*
D 7
	 * XXX: shorten timeout value (so autoconfig doesn't take forever)
E 7
I 7
	 * XXX shorten timeout value so autoconfig doesn't
	 * take forever on slow CPUs.
E 7
	 */
	ohpibtimeout = hpibtimeout;
D 7
	hpibtimeout = hpibidtimeout;
E 7
I 7
	hpibtimeout = hpibidtimeout * cpuspeed;
E 7
	if (hpibrecv(unit, 31, slave, &id, 2) != 2)
		id = 0;
	hpibtimeout = ohpibtimeout;
	return(id);
}

hpibsend(unit, slave, sec, addr, cnt)
	register int unit;
I 10
	int slave, sec, addr, cnt;
E 10
{
	if (hpib_softc[unit].sc_type == HPIBC)
		return(fhpibsend(unit, slave, sec, addr, cnt));
	else
		return(nhpibsend(unit, slave, sec, addr, cnt));
}

hpibrecv(unit, slave, sec, addr, cnt)
	register int unit;
I 10
	int slave, sec, addr, cnt;
E 10
{
	if (hpib_softc[unit].sc_type == HPIBC)
		return(fhpibrecv(unit, slave, sec, addr, cnt));
	else
		return(nhpibrecv(unit, slave, sec, addr, cnt));
}

hpibpptest(unit, slave)
	register int unit;
I 10
	int slave;
E 10
{
	int (*ppoll)();

	ppoll = (hpib_softc[unit].sc_type == HPIBC) ? fhpibppoll : nhpibppoll;
	return((*ppoll)(unit) & (0x80 >> slave));
}

hpibawait(unit)
I 5
	int unit;
E 5
{
	register struct hpib_softc *hs = &hpib_softc[unit];

	hs->sc_flags |= HPIBF_PPOLL;
	if (hs->sc_type == HPIBC)
D 5
		fhpibppwatch(unit);
E 5
I 5
		fhpibppwatch((void *)unit);
E 5
	else
D 5
		nhpibppwatch(unit);
E 5
I 5
		nhpibppwatch((void *)unit);
E 5
}

hpibswait(unit, slave)
	register int unit;
I 10
	int slave;
E 10
{
	register int timo = hpibtimeout;
	register int mask, (*ppoll)();

	ppoll = (hpib_softc[unit].sc_type == HPIBC) ? fhpibppoll : nhpibppoll;
	mask = 0x80 >> slave;
	while (((ppoll)(unit) & mask) == 0)
		if (--timo == 0) {
			printf("hpib%d: swait timeout\n", unit);
			return(-1);
		}
	return(0);
}

hpibustart(unit)
I 10
	int unit;
E 10
{
	register struct hpib_softc *hs = &hpib_softc[unit];

	if (hs->sc_type == HPIBA)
		hs->sc_dq.dq_ctlr = DMA0;
	else
		hs->sc_dq.dq_ctlr = DMA0 | DMA1;
	if (dmareq(&hs->sc_dq))
		return(1);
	return(0);
}

hpibstart(unit)
I 10
	int unit;
E 10
{
	register struct devqueue *dq;
	
	dq = hpib_softc[unit].sc_sq.dq_forw;
	(dq->dq_driver->d_go)(dq->dq_unit);
}

hpibgo(unit, slave, sec, addr, count, rw)
	register int unit;
I 10
	int slave, sec, addr, count, rw;
E 10
{
	if (hpib_softc[unit].sc_type == HPIBC)
		fhpibgo(unit, slave, sec, addr, count, rw);
	else
		nhpibgo(unit, slave, sec, addr, count, rw);
}

hpibdone(unit)
	register int unit;
{
	if (hpib_softc[unit].sc_type == HPIBC)
		fhpibdone(unit);
	else
		nhpibdone(unit);
}

hpibintr(unit)
	register int unit;
{
	int found;

	if (hpib_softc[unit].sc_type == HPIBC)
		found = fhpibintr(unit);
	else
		found = nhpibintr(unit);
	return(found);
}
#endif
E 1
