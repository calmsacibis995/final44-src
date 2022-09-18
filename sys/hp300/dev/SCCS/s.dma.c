h01056
s 00002/00002/00445
d D 8.1 93/06/10 21:32:12 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00010/00436
d D 7.7 92/10/11 09:23:43 bostic 7 6
c make kernel includes standard
e
s 00021/00003/00425
d D 7.6 92/06/05 15:31:46 hibler 6 5
c merge latest Utah hp300 code including 68040 support
e
s 00006/00009/00422
d D 7.5 91/05/04 19:49:21 karels 5 4
c update to current include, device calling conventions
e
s 00002/00002/00429
d D 7.4 90/12/16 23:43:37 mckusick 4 3
c get proper versionof header files so that macros work
e
s 00009/00009/00422
d D 7.3 90/12/16 16:35:39 bostic 3 2
c kernel reorg
e
s 00150/00089/00281
d D 7.2 90/12/05 18:26:21 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00370/00000/00000
d D 7.1 90/05/08 22:06:52 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * DMA driver
 */

D 3
#include "param.h"
#include "systm.h"
#include "time.h"
#include "kernel.h"
#include "proc.h"
E 3
I 3
D 5
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/time.h"
#include "sys/kernel.h"
#include "sys/proc.h"
E 5
I 5
D 7
#include "param.h"
#include "systm.h"
#include "time.h"
#include "kernel.h"
#include "proc.h"
E 7
I 7
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
E 7

E 5
E 3
D 7
#include "dmareg.h"
#include "dmavar.h"
D 6
#include "device.h"
E 6
I 6
#include "hp/dev/device.h"
E 7
I 7
#include <hp300/dev/dmareg.h>
#include <hp300/dev/dmavar.h>
E 7
E 6

D 3
#include "machine/cpu.h"
#include "machine/isr.h"
E 3
I 3
D 7
#include "../include/cpu.h"
#include "../hp300/isr.h"
E 7
I 7
#include <hp/dev/device.h>

#include <machine/cpu.h>
#include <hp300/hp300/isr.h>
E 7
E 3

extern void isrlink();
D 5
extern void printf();
extern void panic();
E 5
extern void _insque();
extern void _remque();
extern void timeout();
D 5
extern int splbio();
extern void splx();
E 5
extern u_int kvtop();
extern void PCIA();

/*
 * The largest single request will be MAXPHYS bytes which will require
 * at most MAXPHYS/NBPG+1 chain elements to describe, i.e. if none of
 * the buffer pages are physically contiguous (MAXPHYS/NBPG) and the
 * buffer is not page aligned (+1).
 */
#define	DMAMAXIO	(MAXPHYS/NBPG+1)

D 2
#define	DMATIMO		15
E 2
I 2
struct	dma_chain {
	int	dc_count;
	char	*dc_addr;
};
E 2

struct	dma_softc {
D 2
	struct dmadevice *sc_hwaddr;
	struct dmaBdevice *sc_Bhwaddr;
	int	sc_type;
	int	sc_cur;
	int	sc_cmd;
	int	sc_timo;
	int	sc_count[DMAMAXIO+1];
	char	*sc_addr[DMAMAXIO+1];
E 2
I 2
	struct	dmadevice *sc_hwaddr;
	struct	dmaBdevice *sc_Bhwaddr;
	char	sc_type;
	char	sc_flags;
	u_short	sc_cmd;
	struct	dma_chain *sc_cur;
	struct	dma_chain *sc_last;
	struct	dma_chain sc_chain[DMAMAXIO];
E 2
} dma_softc[NDMA];

/* types */
#define	DMA_B	0
#define DMA_C	1

I 2
/* flags */
#define DMAF_PCFLUSH	0x01
#define DMAF_VCFLUSH	0x02
#define DMAF_NOINTR	0x04

E 2
struct	devqueue dmachan[NDMA + 1];
int	dmaintr();
D 2
void	dmatimo();
E 2

#ifdef DEBUG
int	dmadebug = 0;
#define DDB_WORD	0x01	/* same as DMAGO_WORD */
#define DDB_LWORD	0x02	/* same as DMAGO_LWORD */
#define	DDB_FOLLOW	0x04
#define DDB_IO		0x08

I 2
void	dmatimeout();
int	dmatimo[NDMA];

E 2
long	dmahits[NDMA];
long	dmamisses[NDMA];
long	dmabyte[NDMA];
long	dmaword[NDMA];
long	dmalword[NDMA];
#endif

void
dmainit()
{
	register struct dmareg *dma = (struct dmareg *)DMA_BASE;
	register struct dma_softc *dc;
	register int i;
	char rev;

	/*
	 * Determine the DMA type.
	 * Don't know how to easily differentiate the A and B cards,
	 * so we just hope nobody has an A card (A cards will work if
	 * DMAINTLVL is set to 3).
	 */
	if (!badbaddr((char *)&dma->dma_id[2]))
		rev = dma->dma_id[2];
	else {
		rev = 'B';
#if !defined(HP320)
		panic("dmainit: DMA card requires hp320 support");
#endif
	}

	dc = &dma_softc[0];
	for (i = 0; i < NDMA; i++) {
		dc->sc_hwaddr = (i & 1) ? &dma->dma_chan1 : &dma->dma_chan0;
		dc->sc_Bhwaddr = (i & 1) ? &dma->dma_Bchan1 : &dma->dma_Bchan0;
		dc->sc_type = rev == 'B' ? DMA_B : DMA_C;
		dc++;
		dmachan[i].dq_forw = dmachan[i].dq_back = &dmachan[i];
	}
	dmachan[i].dq_forw = dmachan[i].dq_back = &dmachan[i];
D 2
	timeout(dmatimo, (caddr_t)0, DMATIMO * hz);
E 2
I 2
#ifdef DEBUG
	/* make sure timeout is really not needed */
	timeout(dmatimeout, 0, 30 * hz);
#endif
E 2

	printf("dma: 98620%c with 2 channels, %d bit DMA\n",
	       rev, rev == 'B' ? 16 : 32);
}

int
dmareq(dq)
	register struct devqueue *dq;
{
	register int i;
	register int chan;
	register int s = splbio();

	chan = dq->dq_ctlr;
	i = NDMA;
	while (--i >= 0) {
		if ((chan & (1 << i)) == 0)
			continue;
		if (dmachan[i].dq_forw != &dmachan[i])
			continue;
		insque(dq, &dmachan[i]);
		dq->dq_ctlr = i;
		splx(s);
		return(1);
	}
	insque(dq, dmachan[NDMA].dq_back);
	splx(s);
	return(0);
}

void
dmafree(dq)
	register struct devqueue *dq;
{
	int unit = dq->dq_ctlr;
	register struct dma_softc *dc = &dma_softc[unit];
	register struct devqueue *dn;
	register int chan, s;

	s = splbio();
D 2
	dc->sc_timo = 0;
E 2
I 2
#ifdef DEBUG
	dmatimo[unit] = 0;
#endif
E 2
	DMA_CLEAR(dc);
I 6
#if defined(HP360) || defined(HP370) || defined(HP380)
E 6
I 2
	/*
	 * XXX we may not always go thru the flush code in dmastop()
	 */
D 6
#if defined(HP360) || defined(HP370)
E 6
	if (dc->sc_flags & DMAF_PCFLUSH) {
		PCIA();
		dc->sc_flags &= ~DMAF_PCFLUSH;
	}
#endif
#if defined(HP320) || defined(HP350)
	if (dc->sc_flags & DMAF_VCFLUSH) {
		/*
		 * 320/350s have VACs that may also need flushing.
		 * In our case we only flush the supervisor side
		 * because we know that if we are DMAing to user
		 * space, the physical pages will also be mapped
		 * in kernel space (via vmapbuf) and hence cache-
		 * inhibited by the pmap module due to the multiple
		 * mapping.
		 */
		DCIS();
		dc->sc_flags &= ~DMAF_VCFLUSH;
	}
#endif
E 2
	remque(dq);
	chan = 1 << unit;
	for (dn = dmachan[NDMA].dq_forw;
	     dn != &dmachan[NDMA]; dn = dn->dq_forw) {
		if (dn->dq_ctlr & chan) {
			remque((caddr_t)dn);
			insque((caddr_t)dn, (caddr_t)dq->dq_back);
			splx(s);
			dn->dq_ctlr = dq->dq_ctlr;
			(dn->dq_driver->d_start)(dn->dq_unit);
			return;
		}
	}
	splx(s);
}

void
dmago(unit, addr, count, flags)
	int unit;
	register char *addr;
	register int count;
	register int flags;
{
	register struct dma_softc *dc = &dma_softc[unit];
I 2
	register struct dma_chain *dcp;
E 2
	register char *dmaend = NULL;
D 2
	register int tcount, i;
E 2
I 2
	register int tcount;
E 2

I 2
	if (count > MAXPHYS)
		panic("dmago: count > MAXPHYS");
#if defined(HP320)
	if (dc->sc_type == DMA_B && (flags & DMAGO_LWORD))
		panic("dmago: no can do 32-bit DMA");
#endif
E 2
#ifdef DEBUG
	if (dmadebug & DDB_FOLLOW)
		printf("dmago(%d, %x, %x, %x)\n",
		       unit, addr, count, flags);
	if (flags & DMAGO_LWORD)
		dmalword[unit]++;
	else if (flags & DMAGO_WORD)
		dmaword[unit]++;
	else
		dmabyte[unit]++;
#endif
D 2
#if defined(HP320)
	if (dc->sc_type == DMA_B && (flags & DMAGO_LWORD))
		panic("dmago: no can do 32-bit DMA");
#endif
E 2
	/*
	 * Build the DMA chain
	 */
D 2
	for (i = 0; i < DMAMAXIO && count; i++) {
		dc->sc_addr[i] = (char *)kvtop(addr);
		tcount = dc->sc_count[i] =
			MIN(count, NBPG - ((int)addr & PGOFSET));
		addr += dc->sc_count[i];
E 2
I 2
	for (dcp = dc->sc_chain; count > 0; dcp++) {
		dcp->dc_addr = (char *) kvtop(addr);
I 6
#if defined(HP380)
		/*
		 * Push back dirty cache lines
		 */
		if (mmutype == MMU_68040)
			DCFP(dcp->dc_addr);
#endif
E 6
		if (count < (tcount = NBPG - ((int)addr & PGOFSET)))
			tcount = count;
		dcp->dc_count = tcount;
		addr += tcount;
E 2
		count -= tcount;
D 2
		if (flags & (DMAGO_WORD|DMAGO_LWORD))
			tcount >>= (flags & DMAGO_WORD) ? 1 : 2;
		if (dc->sc_addr[i] == dmaend
E 2
I 2
		if (flags & DMAGO_LWORD)
			tcount >>= 2;
		else if (flags & DMAGO_WORD)
			tcount >>= 1;
		if (dcp->dc_addr == dmaend
E 2
#if defined(HP320)
		    /* only 16-bit count on 98620B */
		    && (dc->sc_type != DMA_B ||
D 2
			dc->sc_count[i-1] + tcount <= 65536)
E 2
I 2
			(dcp-1)->dc_count + tcount <= 65536)
E 2
#endif
		) {
#ifdef DEBUG
			dmahits[unit]++;
#endif
D 2
			dmaend += dc->sc_count[i];
			dc->sc_count[i-1] += tcount;
			i--;
E 2
I 2
			dmaend += dcp->dc_count;
			(--dcp)->dc_count += tcount;
E 2
		} else {
#ifdef DEBUG
			dmamisses[unit]++;
#endif
D 2
			dmaend = dc->sc_addr[i] + dc->sc_count[i];
			dc->sc_count[i] = tcount;
E 2
I 2
			dmaend = dcp->dc_addr + dcp->dc_count;
			dcp->dc_count = tcount;
E 2
		}
	}
D 2
	if (count)
		panic("dmago maxphys");
	dc->sc_count[i] = 0;
	dc->sc_cur = 0;
E 2
I 2
	dc->sc_cur = dc->sc_chain;
	dc->sc_last = --dcp;
	dc->sc_flags = 0;
E 2
	/*
	 * Set up the command word based on flags
	 */
	dc->sc_cmd = DMA_ENAB | DMA_IPL(DMAINTLVL) | DMA_START;
	if ((flags & DMAGO_READ) == 0)
		dc->sc_cmd |= DMA_WRT;
	if (flags & DMAGO_LWORD)
		dc->sc_cmd |= DMA_LWORD;
	else if (flags & DMAGO_WORD)
		dc->sc_cmd |= DMA_WORD;
	if (flags & DMAGO_PRI)
		dc->sc_cmd |= DMA_PRI;
I 6
#if defined(HP380)
	/*
	 * On the 68040 we need to flush (push) the data cache before a
	 * DMA (already done above) and flush again after DMA completes.
	 * In theory we should only need to flush prior to a write DMA
	 * and purge after a read DMA but if the entire page is not
	 * involved in the DMA we might purge some valid data.
	 */
	if (mmutype == MMU_68040 && (flags & DMAGO_READ))
		dc->sc_flags |= DMAF_PCFLUSH;
#endif
E 6
D 2

E 2
I 2
#if defined(HP360) || defined(HP370)
E 2
	/*
D 2
	 * We should be able to skip the dma completion interrupt
	 * if we only have one segment in the chain since many
	 * devices generate their own completion interrupt.
	 * However, on a 370 we have to take the interrupt on
	 * read transfers to invalidate the external cache.
E 2
I 2
	 * Remember if we need to flush external physical cache when
	 * DMA is done.  We only do this if we are reading (writing memory).
E 2
	 */
D 2
	if ((flags & DMAGO_NOINT) && i == 1
#if defined(HP370)
	    && ((flags & DMAGO_READ) == 0 || ectype != EC_PHYS)
E 2
I 2
	if (ectype == EC_PHYS && (flags & DMAGO_READ))
		dc->sc_flags |= DMAF_PCFLUSH;
E 2
#endif
D 2
	)
		dc->sc_cmd &= ~DMA_ENAB;
#ifdef DEBUG
#if defined(HP320)
	/* would this hurt? */
	if (dc->sc_type == DMA_B)
		dc->sc_cmd &= ~DMA_START;
E 2
I 2
#if defined(HP320) || defined(HP350)
	if (ectype == EC_VIRT && (flags & DMAGO_READ))
		dc->sc_flags |= DMAF_VCFLUSH;
E 2
#endif
I 2
	/*
	 * Remember if we can skip the dma completion interrupt on
	 * the last segment in the chain.
	 */
	if (flags & DMAGO_NOINT) {
		if (dc->sc_cur == dc->sc_last)
			dc->sc_cmd &= ~DMA_ENAB;
		else
			dc->sc_flags |= DMAF_NOINTR;
	}
#ifdef DEBUG
E 2
	if (dmadebug & DDB_IO)
		if ((dmadebug&DDB_WORD) && (dc->sc_cmd&DMA_WORD) ||
		    (dmadebug&DDB_LWORD) && (dc->sc_cmd&DMA_LWORD)) {
D 2
			printf("dmago: cmd %x\n", dc->sc_cmd);
			for (i = 0; dc->sc_count[i]; i++) 
				printf("  %d: %d@%x\n",
				       i, dc->sc_count[i], dc->sc_addr[i]);
E 2
I 2
			printf("dmago: cmd %x, flags %x\n",
			       dc->sc_cmd, dc->sc_flags);
			for (dcp = dc->sc_chain; dcp <= dc->sc_last; dcp++)
				printf("  %d: %d@%x\n", dcp-dc->sc_chain,
				       dcp->dc_count, dcp->dc_addr);
E 2
		}
I 2
	dmatimo[unit] = 1;
E 2
#endif
D 2

	/*
	 * Load and arm the channel
	 */
	dc->sc_timo = 1;
	DMA_ARM(dc, 0);
E 2
I 2
D 3
	DMA_ARM(dc);
E 3
I 3
D 4
	DMA_ARM(dc, "KIRK, MISSING AN ARG");
E 4
I 4
	DMA_ARM(dc);
E 4
E 3
E 2
}

void
dmastop(unit)
	register int unit;
{
	register struct dma_softc *dc = &dma_softc[unit];
	register struct devqueue *dq;

#ifdef DEBUG
	if (dmadebug & DDB_FOLLOW)
		printf("dmastop(%d)\n", unit);
I 2
	dmatimo[unit] = 0;
E 2
#endif
D 2
	dc->sc_timo = 0;
E 2
	DMA_CLEAR(dc);
D 2

E 2
I 2
D 6
#if defined(HP360) || defined(HP370)
E 6
I 6
#if defined(HP360) || defined(HP370) || defined(HP380)
E 6
	if (dc->sc_flags & DMAF_PCFLUSH) {
		PCIA();
		dc->sc_flags &= ~DMAF_PCFLUSH;
	}
#endif
#if defined(HP320) || defined(HP350)
	if (dc->sc_flags & DMAF_VCFLUSH) {
		/*
		 * 320/350s have VACs that may also need flushing.
		 * In our case we only flush the supervisor side
		 * because we know that if we are DMAing to user
		 * space, the physical pages will also be mapped
		 * in kernel space (via vmapbuf) and hence cache-
		 * inhibited by the pmap module due to the multiple
		 * mapping.
		 */
		DCIS();
		dc->sc_flags &= ~DMAF_VCFLUSH;
	}
#endif
E 2
	/*
	 * We may get this interrupt after a device service routine
	 * has freed the dma channel.  So, ignore the intr if there's
	 * nothing on the queue.
	 */
	dq = dmachan[unit].dq_forw;
D 2
	if (dq != &dmachan[unit]) {
#if defined(HP370)
		/*
		 * The 370 has an 64k external physical address cache.
		 * In theory, we should only need to flush it when
		 * DMAing to memory.
		 */
		if (ectype == EC_PHYS && (dc->sc_cmd & DMA_WRT) == 0)
			PCIA();
#endif
E 2
I 2
	if (dq != &dmachan[unit])
E 2
		(dq->dq_driver->d_done)(dq->dq_unit);
D 2
	}
E 2
}

int
dmaintr()
{
	register struct dma_softc *dc;
D 2
	register int i, j, stat;
E 2
I 2
	register int i, stat;
E 2
	int found = 0;

#ifdef DEBUG
	if (dmadebug & DDB_FOLLOW)
		printf("dmaintr\n");
#endif
	for (i = 0, dc = dma_softc; i < NDMA; i++, dc++) {
		stat = DMA_STAT(dc);
		if ((stat & DMA_INTR) == 0)
			continue;
		found++;
#ifdef DEBUG
		if (dmadebug & DDB_IO) {
			if ((dmadebug&DDB_WORD) && (dc->sc_cmd&DMA_WORD) ||
			    (dmadebug&DDB_LWORD) && (dc->sc_cmd&DMA_LWORD))
				printf("dmaintr: unit %d stat %x next %d\n",
D 2
				       i, stat, dc->sc_cur+1);
E 2
I 2
				       i, stat, (dc->sc_cur-dc->sc_chain)+1);
E 2
		}
		if (stat & DMA_ARMED)
			printf("dma%d: intr when armed\n", i);
#endif
D 2
		j = ++dc->sc_cur;
		if (j < DMAMAXIO && dc->sc_count[j]) {
			dc->sc_timo = 1;
E 2
I 2
		if (++dc->sc_cur <= dc->sc_last) {
#ifdef DEBUG
			dmatimo[i] = 1;
#endif
			/*
			 * Last chain segment, disable DMA interrupt.
			 */
			if (dc->sc_cur == dc->sc_last &&
			    (dc->sc_flags & DMAF_NOINTR))
				dc->sc_cmd &= ~DMA_ENAB;
E 2
			DMA_CLEAR(dc);
D 2
			DMA_ARM(dc, j);
E 2
I 2
D 3
			DMA_ARM(dc);
E 3
I 3
D 4
			DMA_ARM(dc, "KIRK, MISSING AN ARG");
E 4
I 4
			DMA_ARM(dc);
E 4
E 3
E 2
		} else
			dmastop(i);
	}
	return(found);
}

I 2
#ifdef DEBUG
E 2
void
D 2
dmatimo()
E 2
I 2
dmatimeout()
E 2
{
	register int i, s;
D 2
	register struct dma_softc *dc = &dma_softc[0];
E 2

D 2
	for (i = 0; i < NDMA; i++, dc++) {
E 2
I 2
	for (i = 0; i < NDMA; i++) {
E 2
		s = splbio();
D 2
		if (dc->sc_timo) {
			if (dc->sc_timo == 1)
				dc->sc_timo++;
			else
				dmastop(i);
E 2
I 2
		if (dmatimo[i]) {
			if (dmatimo[i] > 1)
				printf("dma%d: timeout #%d\n",
				       i, dmatimo[i]-1);
			dmatimo[i]++;
E 2
		}
		splx(s);
	}
D 2
	timeout(dmatimo, (caddr_t)0, DMATIMO * hz);
E 2
I 2
	timeout(dmatimeout, (caddr_t)0, 30 * hz);
E 2
}
I 2
#endif
E 2
E 1
