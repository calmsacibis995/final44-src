#ifndef lint
static	char sccsid[] = "@(#)mb_machdep.c 1.12 89/05/10 SMI";
#endif
/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mb_machdep.c,v $
 * Revision 2.3  92/02/04  21:15:25  mja
 * 	Added mbq_softcall() and upgraded queuing functions to SunOS
 * 	4.1.1.  Uncommented swab() so that we can compile without libc.a
 * 	[91/10/27            berman]
 * 
 * 	Cleaned up some of mb_mapalloc() and mb_relse() in preparation
 * 	for 4.1.1 merge with new queueing structures.
 * 	[91/10/26            berman]
 * 
 * Revision 2.2  90/12/17  17:16:44  berman
 * 	Imported from SunOS 4.0.3c for Sparcstation port.
 * 	[90/07/17            berman]
 * 
 */

/*
 * Copyright (c) 1988, 1989 by Sun Microsystems, Inc.
 */

/*
 * Machine dependent mainbus support routines. 
 * 
 * N.B. The mainbus code no longer requires the mainbus structures (mb_ctlr 
 * and so on) to ask for DVMA space or to queue up when DVMA is not available.
 * Drivers can now send in a generic map structure and a pointer to a function 
 * which is queued and invoked later when space frees up again. This mechanism
 * allows devices to manage their own queues and especially to queue multiple 
 * I/O's to the same device. The old mbsetup()/mbrelse() interface has been 
 * retained and can be used in the same way as before (these routines can
 * be found in <sundev/mb.c>).
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/vmmac.h>
#if	MACH
#else	MACH
#include <sys/vmmeter.h>
#endif	MACH
#include <sys/vmparam.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/mman.h>
#if	MACH
#else	MACH
#include <sys/debug.h>
#endif	MACH

#include <machine/mmu.h>
#include <machine/cpu.h>
#include <machine/psl.h>
#if	MACH
#include <machine/pmap.h>
#else	MACH
#include <machine/pte.h>
#endif	MACH
#include <machine/reg.h>

#include <sundev/mbvar.h> 

#if	MACH
#else	MACH
#include <vm/hat.h>
#include <vm/as.h>
#include <vm/page.h>
#include <vm/seg.h>
#include <machine/seg_kmem.h>
#endif	MACH

#if	MACH
#define DVMA_RUNOUT (-1)

typedef int (*func_t)();

extern u_int getpgmap();
#endif	MACH
/*
 * Drivers queue function pointers here when they have to wait
 * for resources. Subsequent calls from the same driver that are
 * forced to wait need not queue up again, as the function pointed
 * to will run the driver's internal queues until done or space runs
 * out again. The arg parameter can be used by drivers as a cookie
 * to be passed back by the callback function. They should pass in 
 * NULL if not using the parameter.
 * Note that if drivers keep calling the allocation routine after
 * resources ran out that the arg parameter associated with subsequent
 * calls is ignored.
 *
 * The system priority level at which the allocation routine is called at
 * also indicates an implicit ordering as to whom is called back first.
 * When a resource is freed, the current system priority level is used to
 * screen out and not call back directly waiters who called the allocation
 * routine at a lower system priority level- they instead are called via
 * softcall() (if resources are left after calling back directly those who
 * can be called back directly). Note that if the original call had stored
 * up at priority 0, the intent of this indirect mechanism cannot be
 * achieved (and a warning message will be printed upon the storing of
 * such a callback).
 *
 * Because elements may be removed out of order (due to pri differences),
 * a simple cycle through a limited array isn't enough if we still wan't
 * preserve any semblance of FIFO servicing. A simple linked list will fit
 * the bill. In fact, an array could still be used, but it turns out that
 * a linked list uses fewer instructions to manage in this fashion (while
 * losing locality of reference and possible cache gains). On the other
 * hand, this is more like we'll want this to be, and it probably doesn't
 * make that big a difference.
 */

#define MAXMBQLEN 10

static struct mbq_elem {
	struct mbq_elem	*mbq_next;
	func_t 		mbq_funcp;
	caddr_t 	mbq_arg;
	int		mbq_pri;
} mbq[MAXMBQLEN];

/*
 * MB related stats
 */
static struct mbs {
	int m_runout;   	/* times DVMA has run out */
	int m_queued;    	/* driver already had request queued */
	int m_bigreq;   	/* largest request received (bytes) */
	int m_hiqlen;    	/* longest length of wait queue */
	int m_softcall;		/* number of callbacks via softcall */
} mbs;

static int mbqlen;         	/* current length of wait queue */
static struct mbq_elem *mbqfree, *mbwaitq;
static void mbq_store();	/* store element */
static void mbq_retrieve();	/* retrieve element */
static int mbq_softcall();	/* entry into callback via softcall */

extern struct map *dvmamap;

/*
 * run_mhq && mb_setup now in sundev/mb.c
 */

/*
 * Allocate and setup Mainbus map registers.  Flags says whether the
 * caller can't wait (e.g. if the caller is at interrupt level).  We 
 * also allow DMA to memory already mapped at the Mainbus (e.g., for 
 * Sun Ethernet board memory) if buscheck() says it's ok.
 *
 * We assume that the physical translations for the pages have already 
 * been locked down before we were called.
 */

/*
 * New interface for mainbus resources. The main reason for this is to
 * provide smart controllers with the ability to queue multiple I/Os to
 * a single device, which was impossible with the old stuff. This is also
 * a move towards cleaning up the complexity of the queueing structures
 * both for DVMA resources and for autoconf. 
 *
 * This routine accepts a function pointer which is queued if there is no
 * no space available and the caller cannot sleep.
 */
int
mb_mapalloc(map, bp, flags, waitfp, arg)
	register struct map *map;
	register struct buf *bp;
	int flags;
	func_t waitfp;
	caddr_t arg;
{
	register int reg, s, o, npf;
	struct mbcookie mbcookie;
#ifdef sun3x
	struct pte pte;
#endif sun3x
#ifdef sun2
	struct ctx *ctx;
#endif sun2
#if	MACH
	char *addr;
	caddr_t bufaddr;
	long pme;
	struct pme *pte;
#endif	MACH

	/*
	 * At this point there is only one of two maps for mainbus 
	 * resources, so make sure this is the right one.
	 */
#if	MACH
#ifdef	OPENPROMS
	if (map != dvmamap) panic("mb_mapalloc not in dvma space");
#else	OPENPROMS
	if (map != mb_hd.mh_map) panic("mb_mapalloc not in mb_hd space");
#endif	OPENPROMS
#else	MACH
#ifdef	OPENPROMS
	ASSERT(map == dvmamap);
#else	OPENPROMS
	ASSERT(map == mb_hd.mh_map);
#endif	OPENPROMS
#endif	MACH

	/* 
	 * Size the xfer, rounding up a page if necessary.
	 */
	o = (int)bp->b_un.b_addr & PAGEOFFSET;
	npf = mmu_btopr(bp->b_bcount + o);

#if	MACH
        pme = getpgmap(bp->b_un.b_addr);
        pte = (struct pme *)&pme;
#endif	MACH

	reg = buscheck(bp->b_un.b_addr, npf);

	if (reg < 0)
		panic("mbsetup buscheck fail");

	/*
	 * If not OBMEM, for non-sun4c machines, return the
	 * cookie that buscheck makes up for VME addresses.
	 *
	 * For sun4c, we skip this and force a mapping across
	 * DVMA[] (I/O on sun4c always goes through MMU context
	 * 0- even SBus to SBus transactions).
	 */
	if (reg > 0) {
		/*
		 * In contiguous mainbus memory,
		 * i.e., not on on-board memory
		 * (mainbus is historical).
		 */
		mbcookie.mbi_mapreg = reg;
		mbcookie.mbi_offset = o;
		return (*(int *)&mbcookie);
	}

	/*
	 * Else the request is for all type 0 memory which still needs
	 * to be mapped into DVMA space.  Allocate virtual space for the
	 * mapping including one extra for redzone at end of mapping.
	 */

	s = splr(pritospl(SPLMB));
#if	MACH
	npf++;
	while ((reg = (int)rmalloc( map, (long)npf )) == 0) {
#else	MACH
	while ((reg = bp_alloc(map, bp, npf + 1)) == 0) {
#endif	MACH
		/*
		 * No DVMA available. We either queue the function ptr 
		 * or sleep, depending on the caller's state of mind. 
		 */
		if (flags & MB_CANTWAIT) {
			if (waitfp) {
				mbq_store(waitfp, arg, spltoipl(s));
				mbs.m_bigreq = MAX(ctob(npf), mbs.m_bigreq);
			}
			(void) splx(s);
			return (0);
		}
		mapwant(map)++;
		(void) sleep((caddr_t)map, PSWP);
	}
	(void) splx(s);

#ifdef sun2
	ctx = mmu_getctx();
	if (ctx != kctx)
		mmu_setctx(kctx);
#endif sun2

	/*
	 * Map the bp into kernel virtual address in DVMA space.
	 * We over allocate one slot and mark this mapping
	 * invalid.  This protects against run away transfers
	 * and is also used as termination condition in mb_mapfree.
	 * We set the redzone to invalid every time because we're
	 * paranoid, but we use mmu_setpte instead of hat_pteload
	 * because we want it to be fast.
	 */
#if	MACH
        addr = &DVMA[ctob(reg)];
        bufaddr = bp->b_un.b_addr;
        while (--npf > 0) {
                register int pfnum;

                pme = getpgmap(bufaddr);
                pte = (struct pme *)&pme;

                switch (*(int *)pte & PGT_MASK) {
                default:
                        /* may not go from dvma back out to the bus */
                        panic("mb_mapalloc: bad PGT");
                case PGT_OBMEM:
			/* Fall through after flushing */
#ifdef	VAC
                        if (vac) vac_pageflush(bufaddr);
#endif	VAC
                case PGT_OBIO:
                        if ((pfnum = pte->pfn) == 0)
                                panic("mb_mapalloc: zero pfnum");
                        setpgmap(addr, (long)(PG_V | PG_KW | pfnum));
                        addr += NBPG;
                        bufaddr += NBPG;
                }
        }
	/* Mark the redzone page as invalid */
        setpgmap(addr, (long)0);
#else	MACH
	bp_map(bp, &DVMA[mmu_ptob(reg)]);

#ifdef sun3x
	*(u_int *)&pte = MMU_INVALIDPTE;
	hat_pteload(&kseg, &DVMA[mmu_ptob(reg + npf)],
	    (struct page *)NULL, &pte, PTELD_LOCK | PTELD_NOSYNC);
#else sun3x
	mmu_setpte(&DVMA[mmu_ptob(reg + npf)], mmu_pteinvalid);
#endif sun3x
#endif	MACH

#ifdef sun2
	if (ctx != kctx)
		mmu_setctx(ctx);
#endif sun2

	mbcookie.mbi_mapreg = reg;
	mbcookie.mbi_offset = o;
	return (*(int *)&mbcookie);
}

/*
 * mb_relse now back in sundev/mb.c
 */

/*
 * Release resources on Mainbus, and then unblock resource waiters.
 */
void
mb_mapfree(map, amr)
	register struct map *map;
	int *amr;
{
	register char *addr;
	register int reg;
	register int npf;
#if	MACH
#else	MACH
#ifdef sun3x
	struct pte *ppte;
#else sun3x
	struct pte pte;
#endif sun3x
#endif	MACH
	int mr, s, stat;
#ifdef sun2
	struct ctx *ctx;
#endif sun2
#ifdef SUN3X_470
	int flush = 0;
#endif SUN3X_470

	/*
	 * At this point there is only one of two maps for mainbus 
	 * resources, so make sure this is the right one.
	 */
#if	MACH
#ifdef	OPENPROMS
	if (map != dvmamap) panic("mb_mapalloc not in dvma space");
#else	OPENPROMS
	if (map != mb_hd.mh_map) panic("mb_mapalloc not in mb_hd space");
#endif	OPENPROMS
#else	MACH
#ifdef	OPENPROMS
	ASSERT(map == dvmamap);
#else	OPENPROMS
	ASSERT(map == mb_hd.mh_map);
#endif	OPENPROMS
#endif	MACH

	/*
	 * Carefully see if we should release the space.
	 */
	s = splr(pritospl(SPLMB));
	mr = *amr;
	if (mr == 0) {
		printf("mb_mapfree: MR == 0!!!\n");
		(void) splx(s);
		return;
	}
	*amr = 0;
	(void) splx(s);		/* we're supposed to be safe for awhile */

#ifdef sun3x
	if ((reg = MBI_MR(mr)) < dvmasize) {		/* DVMA memory */
		/*
		 * First we have to read the hardware maps to figure
		 * out how big the transfer really was.  This relies
		 * on having an invalid pte to terminate the mapping.
		 * We start looking at the 2nd page to avoid always
		 * looking at the first page.
		 */
		addr = &DVMA[mmu_ptob(reg + 1)];
		/*
		 * NOTE -- this assumes that the ptes for DVMA space
		 * are contiguous and ascending. This must remain true!
		 */
		ppte = hat_ptefind(&kas, addr);
		if (ppte == NULL)
			panic("mbrelse no ptes");
		/*
		 * See if the first page of the mapping was I/O cacheable.
		 */
#ifdef SUN3X_470
                if (cpu == CPU_SUN3X_470) {
			if ((ppte - 1)->pte_iocache)
				flush = 1;
		}
#endif SUN3X_470
		for (npf = 2; ; npf++, ppte++)
			if (!pte_valid(ppte))
				break;
#ifdef SUN3X_470
                if (cpu == CPU_SUN3X_470) {
		/*
		 * If the mapping was I/O cacheable, loop through the cache,
		 * flushing all the lines for this mapping.
		 */
			if (flush) {
				for (flush = 0; flush < npf; flush++)
					ioc_flush(reg + flush);
			}
                }
#endif SUN3X_470
		/*
		 * Now use hat_unload to unload the translations
		 * without getting the referenced and modified bits.
		 */
		hat_unload(&kseg, &DVMA[mmu_ptob(reg)],
		    (u_int)(npf << MMU_PAGESHIFT));
		/*
		 * Put back the registers in the resource map.
		 * The map code must not be reentered, so we
		 * do this at high spl.
		 */
		s = splx(pritospl(SPLMB));
		rmfree(map, (long)npf, (u_long)reg);
		(void) splx(s);
	}

#else sun3x
/*
 * EXTREME HACK HERE IF MBI_MR never works!
 */
#if	MACH
reg = MBI_MR(mr);
{
#else 	MACH
	if ((reg = MBI_MR(mr)) < dvmasize) {		/* DVMA memory */
#endif	MACH
#ifdef sun2
		ctx = mmu_getctx();
		if (ctx != kctx)
			mmu_setctx(kctx);
#endif sun2

#if	MACH
                register int npf = 1;           /* plus one for last entry */

                for (addr = &DVMA[ctob(reg)]; getpgmap(addr) != (u_int)0;
                    addr += NBPG, npf++) {

#ifdef	VAC
			if (vac) vac_pageflush(addr);
#endif	VAC
                        setpgmap(addr, (long)0);
                }
#else	MACH
#ifdef VAC
		if (vac) {
#ifdef sun4c
			/*
			 * First we have to read the hardware maps to figure
			 * out how big the transfer really was.  This relies
			 * on having an invalid pte to terminate the mapping.
			 * We start looking at the first page since we are
			 * syncing the cache as we go. We only sync the
			 * cache for dirty pages, since output doesn't
			 * make the cache stale. This assumes that the
			 * I/O is going through the MMU and thus setting
			 * the dirty bit when appropriate.
			 *
			 * NOTE: this method of syncing the cache only
			 * works for write-through caches, where the flush
			 * is always an invalidate. A write-back cache
			 * would not work this way.
			 */
			addr = &DVMA[mmu_ptob(reg)];
			for (npf = 0; ; npf++) {
				mmu_getpte((addr_t)addr, &pte);
				if (!pte_valid(&pte))
					break;
				if (pte.pg_m)
					hat_vacsync(MAKE_PFNUM(&pte));
				addr += MMU_PAGESIZE;
			}
#else sun4c
			/*
			 * First we have to read the hardware maps to figure
			 * out how big the transfer really was.  This relies
			 * on having an invalid pte to terminate the mapping.
			 * We start looking at the 2nd page to avoid always
			 * looking at the first page.
			 */
			addr = &DVMA[mmu_ptob(reg + 1)];
			for (npf = 1; ; npf++) {
				mmu_getpte((addr_t)addr, &pte);
				if (!pte_valid(&pte))
					break;
				addr += MMU_PAGESIZE;
			}
#endif sun4c

			/* For these pages we need to flush io cache
			 * lines before we give up the mapping.
			 * Needed for sun4_460, On other sun4s this 
	 		 * will be a nop
			*/
#ifdef IOC
			ioc_flushaddr(&(DVMA[mmu_ptob(reg)]), npf);
#endif


			/*
			 * Now use hat_unload to unload the translations
			 * without getting the referenced and modified bits.
			 */
			hat_unload(&kseg, &DVMA[mmu_ptob(reg)],
			    (u_int)mmu_ptob(npf));
		} else 
#endif VAC
		{
			/*
			 * No vac, can just use mmu operations to unload
			 * the DVMA mappings.
			 */
			addr = &DVMA[mmu_ptob(reg)];
			for (npf = 0; ; npf++) {
				mmu_getpte((addr_t)addr, &pte);
#ifdef IOC
				ioc_flush(reg+npf, pte.pg_ioc);
#endif

				if (!pte_valid(&pte))
					break;
				mmu_setpte((addr_t)addr, mmu_pteinvalid);
				addr += MMU_PAGESIZE;
			}
		}
#ifdef sun2
		if (ctx != kctx)
			mmu_setctx(ctx);
#endif sun2
#endif	MACH

		/*
		 * Put back the registers in the resource map.
		 * The map code must not be reentered, so we
		 * do this at high spl.
		 */
		s = splr(pritospl(SPLMB));
#if	MACH
		rmfree(map, (long)npf, (u_long)reg);
#else	MACH
		rmfree(map, (long)(npf + 1), (u_long)reg);
#endif	MACH
		(void) splx(s);
	}
#endif sun3x

	/*
	 * Try to map waiting devices, using the queued function ptr.
	 * If a request can't be mapped, we just return, as mb_mapalloc
	 * has already requeued the request.
	 */
	s = splr(pritospl(SPLMB));
	if (mbwaitq)
		mbq_retrieve(spltoipl(s));
#if	MACH
        /*
         * Wakeup sleepers for map registers.
         */
	if( mapwant(map) ) {
		mapwant(map)--;
		wakeup( (caddr_t)map );
	}
#endif	MACH
	(void) splx(s);
}

/*
 * Store a queue element, returning if the funcp is already queued.
 * Always called at SPLMB. 
 */
static void
mbq_store(funcp, arg, pri)
	func_t funcp;
	caddr_t arg;
	int pri;
{
	register struct mbq_elem *lq = NULL;
	register struct mbq_elem *q =  mbwaitq;

	/*
	 * Search the queue to see whether funcp is still queued
	 */

	while (q != NULL) {
		if (q->mbq_funcp == funcp) {
			mbs.m_queued++;
			return;
		}
		lq = q;
		q = q->mbq_next;
	}

	if ((q = mbqfree) == NULL) {
		int i;

		/*
		 * If mbwaitq is NULL when mbqfree is NULL, then
		 * this is the first time thru, else we just got
		 * too many callers. Die.
		 */

		if (mbwaitq) {
			panic("mbq_store: too many callers");
			/*NOTREACHED*/
		}

		/*
		 * ...else initialize the free queue
		 */

		for (i = 0; i < MAXMBQLEN-1; i++)
			mbq[i].mbq_next = &mbq[i+1];
		q = mbqfree = mbq;
	}

	mbqfree = q->mbq_next;

	q->mbq_funcp = funcp;
	q->mbq_arg = arg;
	if ((q->mbq_pri = pri) == 0) {
		printf("Warning: MB callback stored at priority 0!\n");
	}

	if (lq == NULL) {
		q->mbq_next = mbwaitq;
		mbwaitq = q;
	} else {
		q->mbq_next = (struct mbq_elem *) NULL;
		lq->mbq_next = q;
	}

	mbs.m_runout++;
	mbqlen++;
	mbs.m_hiqlen = MAX(mbqlen, mbs.m_hiqlen);
}

/*
 * Retrieve queue elements from the wait queue.
 * Always called at SPLMB. Honor protocol of
 * first calling directly only waiters who are
 * waiting at pri or greater, using softcall
 * to call everybody else (if resources are
 * still left).
 */
static void
mbq_retrieve(pri)
	int pri;
{
	register struct mbq_elem *q, *pq;
	int stat;

	if ((q = mbwaitq) == (struct mbq_elem *) NULL)
		return;

	pq = (struct mbq_elem *) NULL;
	stat = 0;

	do {
		if (q->mbq_pri >= pri) {
			register func_t func;
			register caddr_t arg;

			/*
			 * save a copy of the function/argument pair
			 */

			func = q->mbq_funcp;
			arg = q->mbq_arg;

			/*
			 * Snip the queue element out of the chain
			 * and put it back on the free list before
			 * doing the callback.
			 */

			if (pq) {
				pq->mbq_next = q->mbq_next;
				q->mbq_next = mbqfree;
				mbqfree = q;
				q = pq->mbq_next;
			} else {
				mbwaitq = q->mbq_next;
				q->mbq_next = mbqfree;
				mbqfree = q;
				q = mbwaitq;
			}

			mbqlen -= 1;

			/*
			 * and call the function specified
			 */

			stat = (*(func)) (arg);

			/*
			 * If we ran out again, all bets are off
			 */
			if (stat == DVMA_RUNOUT)
				break;
		} else {
			pq = q;
			q = q->mbq_next;
		}

	} while (q != (struct mbq_elem *) NULL);

	if (stat != DVMA_RUNOUT && mbwaitq != (struct mbq_elem *) NULL) {
		softcall(mbq_softcall, (caddr_t) 0);
	}
}

/*ARGSUSED*/
static int
mbq_softcall(arg)
caddr_t arg;
{
	register s = splr(pritospl(SPLMB));
	mbs.m_softcall++;
	mbq_retrieve(0);
	(void) splx(s);
}

#if	MACH
/*
 * Put swab here, as mb_machdep.c is compiled common to
 * both sun4c and sun{2,3,4} builds.
 */
/*
 * Swap bytes in 16-bit [half-]words
 * for going between the 11 and the interdata
 */
void
swab(pf, pt, n)
	register caddr_t pf, pt;
	register int n;
{
	register char temp;

	n = (n+1)>>1;

	while (--n >= 0) {
		temp = *pf++;
		*pt++ = *pf++;
		*pt++ = temp;
	}
}
#endif	MACH

#ifdef	notdef
/*
 * When someone wants this function, they can allow it to be defined-
 * lint complains too much otherwise.
 */

/*
 * Non buffer setup interface... set up a buffer and call mb_mapalloc.
 * If DVMA runs out. waitfp is queued and invoked later when space becomes
 * available.
 */
int
mb_nbmapalloc(map, addr, bcnt, flags, waitfp, arg)
	struct map *map;
	caddr_t addr;
	int bcnt, flags;
	func_t waitfp;
	caddr_t arg;
{
	struct buf mbbuf;

	bzero((caddr_t)&mbbuf, sizeof (mbbuf));
	mbbuf.b_un.b_addr = addr;
	mbbuf.b_flags = B_BUSY;
	mbbuf.b_bcount = bcnt;
	return (mb_mapalloc(map, &mbbuf, flags, waitfp, arg));
}

#endif	notdef
