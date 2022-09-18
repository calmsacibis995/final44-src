/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_machdep.c,v $
 * Revision 2.5  89/03/09  21:39:25  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:48:37  gm0w
 * 	Added include of cputypes.h as it is needed and no longer
 * 	getting included from elsewhere.
 * 	[89/02/18            mrt]
 * 
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * 14-Mar-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added vac_{enable,disable}_kpage().
 *
 *  1-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Changes for new pmap module:
 *		Flush most of the file.
 *
 * 28-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Let's be clever about how many segs to flush on ctxalloc.  We
 *	used to do over 5,700,000 ctx_setsegmap calls during a kernel
 *	build.
 *
 * 18-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Mapout was not removing the kernel address from all the ctx's.
 *	It was just removing it from ctx 0, 8 times.
 *
 * 27-Aug-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified pmegunload() to use macros to manipulate a pv
 *	list.
 *
 * 01-Jul-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Fixed up for Sun 3/260 virtual address cache:
 *		1) Added include of "../machine/enable.h"
 *		2) Set context in pmegrelease(), mapout(), and
 *		   changeprot() before flushing
 *		3) Added vac_flushall()
 *		4) Removed call to flush segment from pmegfree()
 *		   because it is flushed before pmegfree() is
 *		   called
 *		5) Flush before calling pmegunload() or 
 *		   ctx_unload().
 *
 * 10-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Perform cache flushes for 260 virtual cache.
 *
 * 30-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: eliminated use of u_pme.
 *
 * 15-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to changeprot() to allow changing the 
 *	protection of the u-area.
 *
 * 24-Nov-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Zeroed resident and wired count in pmap whose context is
 *	being freed in ctxfree().
 *
 * 14-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Changed various routines that collect modify bits to
 *	ignore them for physical pages not managed by the
 *	VM system.
 *
 * 26-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Rewritten for Mach.
 *
 */

#ifndef	lint
static	char sccsid[] = "@(#)vm_machdep.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Machine dependent virtual memory support.
 * Context and segment and page map support for the Sun-3.
 */

#include <cputypes.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/vm.h>

#include <sun3/mmu.h>
#include <sun3/cpu.h>
#include <sun3/reg.h>
#include <sun3/buserr.h>
#include <sun3/scb.h>
#ifdef	VAC
#include <sun3/enable.h>
#endif	VAC
#include <sundev/mbvar.h>
#include <sun3/pmap.h>
#include <vm/vm_page.h>
#include <vm/vm_object.h>
#include <vm/vm_kern.h>


/*
 * Move pages from one kernel virtual address to another.
 * Both addresses are assumed to reside in the Sysmap,
 * and size must be a multiple of CLSIZE.
 */
pagemove(from, to, size)
	register caddr_t from, to;
	int size;
{
	register long from_pme;

	if (size % CLBYTES)
		panic("pagemove");
	while (size > 0) {
#ifdef	SUN3_260
		cache_flush_page(KCONTEXT, to);
#endif	SUN3_260
		from_pme = getpgmap(from);
		setpgmap(to, from_pme);
#ifdef	SUN3_260
		cache_flush_page(KCONTEXT, from);
#endif	SUN3_260
		setpgmap(from, (long)0);
		from += NBPG;
		to += NBPG;
		size -= NBPG;
	}
}

/*
 * Check kernel accessibility to a given address.
 * Unlike the vax, vaddr is checked against the range of Sysmap only!
 */
kernacc(vaddr, count, access)
	caddr_t vaddr;
	u_int count;
	int access;
{
	register long	pme;

	count = btoc((int)vaddr + count) - btop(vaddr);
	if ((long)vaddr > VM_MAX_KERNEL_ADDRESS 
	    || (long)vaddr < VM_MIN_KERNEL_ADDRESS)
		return (0);
	access = access == B_READ ? 0 : PG_W;
	while (count--) {
		pme = getpgmap(vaddr);
		if (!(pme & PG_V) || ((pme & PG_W) < access))
			return (0);
	}
	return (1);
}

#ifdef	SUN3_260
extern u_char enablereg;
/*
 * Disable the caching of this kernel page by turing on bit PG_NC in mmu.
 * We turn on PG_NC only if the memory type is onboard memory and PG_NC
 * is off.
 */
vac_disable_kpage(vaddr)
	caddr_t vaddr;
{
	register int pte = getpgmap(vaddr);

	if ((enablereg & ENA_CACHE) && (pte & PGT_MASK) == PGT_OBMEM &&
	    !(pte & PG_NC)) {
		/* onboard mem and PG_NC is not turned on yet */
		vac_pageflush(vaddr);	/* do a write-back */
		pte |= PG_NC;		/* turn on PG_NC, disable caching */
		setpgmap(vaddr, (long)pte);
	}
}

/*
 * Enable the caching of this kernel page by turning off bit PG_NC in mmu.
 * We turn off PG_NC only if the memory type is onboard memory and PG_NC
 * is on.
 */
vac_enable_kpage(vaddr)
	caddr_t vaddr;
{
	register int pte = getpgmap(vaddr);

	if ((enablereg & ENA_CACHE) && (pte & PGT_MASK) == PGT_OBMEM &&
	    (pte & PG_NC)) {
		/* onboard mem and PG_NC is on; nothing is in VAC, no flush */
		pte &= ~PG_NC;		/* turn off PG_NC, enable caching */
		setpgmap(vaddr, (long)pte);
	}
}

/* 
 * Flush the entire VAC. Flush all user contexts and flush all valid
 * kernel segments. It is only used by dumpsys() before we dump
 * the entire physical memory.
 */
vac_flushall()
{
	register i;

	if (vac) {
		/* Flush all user contexts. */
		for (i = 0; i < NCONTEXT; i++)
			/* There is no user page in context KCONTEXT. */
			if (i != KCONTEXT) {
				cache_flush_context(i);
			}
		/* Flush entire kernel address space. */
		for (i = KERNELBASE; i < MONEND; i+= NBSG)
			if (getsegmap(KCONTEXT, (u_int)i) != SEGINV)
				cache_flush_seg(KCONTEXT, (u_int)i);
	}
}
#endif	SUN3_260
