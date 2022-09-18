/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sun_init.c,v $
 * Revision 2.8  90/04/28  00:03:14  jjc
 * 	Always set address of first available physical page to be
 * 	above Sun 3/50 frame buffer.  We'll return the memory later
 * 	if this isn't a Sun 3/50.
 * 	[90/04/23            jjc]
 * 
 * Revision 2.7  89/03/09  21:38:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  19:47:34  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.5  88/12/19  02:50:25  mwyoung
 * 	Remove lint.
 * 	[88/12/18            mwyoung]
 * 
 * Revision 2.4  88/08/24  02:10:59  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 *
 *  9-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Eliminate use of freemem.  Fix copyright notice, include file format.
 *
 *  4-Feb-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Revised for new pmap module:
 *		pmap_bootstrap vs {ctx,pmeg}init
 *
 * 04-Oct-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added changes for Sun 3/{60,110}.
 *
 * 25-Jun-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code for Sun 3/260 to deal with cache and ecc memory.
 *	Don't cache prom monitor.
 *
 * 30-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: don't reserve pmeg for U_AREA.
 *
 * 29-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Made sure that memory allocated for IOPB isn't part of
 *	managed physical memory.
 *
 * 13-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified to use "esym" as the end of the kernel instead of
 *	"end" if the kernel debugger is enabled.
 *
 * 14-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Replaced all occurences of "romp" with "sunromp" to avoid
 *	name conflict with IBM PC RT "romp".
 *	Added code to set aside 1 page of virtual memory per cpu
 *	for scratch work.
 *
 * 31-Jul-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to set aside 2 pages of virtual memory for use
 *	by the phys routines.
 *
 * 14-Jun-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Created from startup routine.
 */
#include <cputypes.h>

#include <mach_kdb.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/vm.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/reboot.h>
#include <sys/conf.h>
#include <sys/inode.h>
#include <sys/file.h>
#include <sys/clist.h>
#include <sys/callout.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>
#include <sys/socket.h>
#include <sys/kernel.h>

#include <net/if.h>
#include <sys/quota.h>
#include <sun/consdev.h>
#include <sun/frame.h>
#include <sundev/mbvar.h>

#include <sun3/psl.h>
#include <sun3/reg.h>
#include <sun3/clock.h>
#include <sun3/scb.h>
#include <sun3/mmu.h>
#include <sun3/cpu.h>
#include <sun3/eeprom.h>
#include <sun3/interreg.h>
#include <sun3/memerr.h>
#include <sun3/eccreg.h>

#include <mach/vm_param.h>

#ifdef	SUN3_260
#include <sun3/enable.h>

extern struct eccreg	*ecc_alive[];
#endif	SUN3_260
extern int		kernprot;	/* write protect kernel text */
extern long		getpgmap();
extern u_char		getsgmap(), pmegallocres();

vm_offset_t    	avail_start;	/* PA of first available physical page */
vm_offset_t	avail_end;	/* PA of last available physical page */
vm_size_t	mem_size;	/* memory size in bytes */
vm_offset_t	virtual_avail;  /* VA of 1st available page (after kernel bss)*/
vm_offset_t	virtual_end;	/* VA of last available page (end of kernel address space */

vm_offset_t	phys_map_vaddr1, phys_map_vaddr2;
vm_offset_t	memdev_vaddr;

sun_init()
{
	u_int 			firstaddr;/* next free physical page number */
	register unsigned	i;
	int			mon_mem;
	long		 	pme;
	register vm_offset_t	v, lv;
	void 			v_handler();

	extern char		start[], etext[], end[];

#if	MACH_KDB
	extern char		*esym;
#define END	esym
#else	MACH_KDB
#define END	end
#endif	MACH_KDB


	/*
	 * Reset machine indep. page size to be Sun page size
	 */
	page_size = NBPG;
	vm_set_page_size();

	initscb();			/* set trap vectors */
	*INTERREG |= IR_ENA_INT;	/* make sure interrupts can occur */

	virtual_avail = round_page(END);
	firstaddr = round_page((int)END - KERNELBASE);

	/*
	 * Dodge Sun 3/50 frame buffer.
	 *
	 * Always make address of first available physical page point after
	 * the frame buffer.  We will make the physical memory for the frame
	 * buffer available later if we discover it is not needed.
	 */
	if (firstaddr < OBFBADDR)
		firstaddr = round_page((int)OBFBADDR + FBSIZE);
	else
		firstaddr += round_page(FBSIZE);

	/* 
	 * Bump end of kernel up by 2 pages per cpu to make room for virtual
	 * pages needed by phys routines like pmap_copy_page, copy_to_phys,
	 * etc..  Remember the virtual addresses of these pages which lie at
	 * the end of the kernel bss or the symbol table if kernel debugging
	 * is enabled.
	 */
	phys_map_vaddr1 = virtual_avail;
	phys_map_vaddr2 = phys_map_vaddr1 + PAGE_SIZE * NCPUS;
	memdev_vaddr = phys_map_vaddr2 + PAGE_SIZE * NCPUS;

	/*
	 * Bump end up by 1 page per cpu for virtual memory to map physical
	 * memory to do scratch work on.
	 */
	virtual_avail = memdev_vaddr + PAGE_SIZE * NCPUS;

	/*
	 * Reserve necessary pmegs and set segment mapping.
	 * It is assumed here that the pmegs for low
	 * memory have already been duplicated for the
	 * segments up in the kernel virtual address space.
	 */

	/*
	 * invalidate to start of high mapping
	 */

	for (v = 0; v < (vm_offset_t)KERNELBASE; v += NBSG)
		setsgmap(v, (u_char)SEGINV);

	/* reserve kernel pmegs */
#define round_pmeg(x) (((int)(END+SGOFSET))&~SGOFSET)
	for (; v < (vm_offset_t)round_pmeg(END); v += NBSG)
		pmeg_reserve(v);

	for (; v < (vm_offset_t)MONSTART; v += NBSG) 	/* invalidate to mon start */
		setsgmap(v, (u_char)SEGINV);

	for (; v < (vm_offset_t)MONEND; v += NBSG) {		/* reserve monitor pmegs */
		if (getsgmap(v) != (u_char)SEGINV) {
			for (lv = v; lv < v + NBSG; lv += NBPG) {
				long pg = getpgmap(lv);
				
				if ((pg & PG_V) && (pg & PG_PROT) >= PG_KR)
					break;
			}
			if (lv < v + NBSG) {
				/*
				 * The pmeg had a valid page with
				 * some access allowed, reserve
				 * the pmeg for the monitor.
				 */
				pmeg_reserve(v);
			} else {
				/*
				 * "steal" wasted pmeg back from the monitor
				 */
				setsgmap(v, (u_char)SEGINV);
			}
		}
	}

	for (; v < (vm_offset_t)((NSEGMAP - 1)*NBSG); v += NBSG)		/* invalid until last seg */
		setsgmap(v, (u_char)SEGINV);

	pmeg_reserve(v);					/* last segment is used for
								 * devices and dvma map
								 */
	/*
	 * Now go through all the other contexts and set up the segment
	 * maps so that all segments are mapped the same.
	 * We have to use a PROM routine to do this since we don't want
	 * to switch to a new (unmapped) context to call setsegmap()!
	 */

	for (i = 0; i < NCONTEXT; i++) {
		if (i == KCONTEXT)
			continue;

		for (v = 0; v < (vm_offset_t)(NBSG * NSEGMAP); v += NBSG)
			(*sunromp->v_setcxsegmap)(i, v, getsgmap(v));
	}

	/*
	 * Now all the monitor set up pmeg's have been reserved.
	 * Normal allocation can proceed.
	 * pmap_reserve is now illegal
	 */
	pmap_bootstrap();

	/*
	 * Initialize kernel page table entries.
	 * We'd pmap_map but we really don't know the epa's
	 */

	/* invalid until start except scb page which is kernel writable */

	for (v = (vm_offset_t)KERNELBASE; v < (vm_offset_t)start; v += NBPG) {
		if (v == (vm_offset_t)&scb)
			pme = PG_V | PG_KW | getpgmap(v) & PG_PFNUM;
		else
			pme = 0;
		setpgmap(v, pme);
	}

	/* set up kernel text pages */
	pmap_protect(kernel_pmap, start, trunc_page(etext),
			     kernprot ? VM_PROT_READ : VM_PROT_WRITE|VM_PROT_READ);

	/* set up kernel data/bss pages to be writeable */
	pmap_protect(kernel_pmap, trunc_page(etext), round_page(END), VM_PROT_READ|VM_PROT_WRITE);

	pme_zero(round_page(END),
		((u_int)virtual_avail + SGOFSET) & ~SGOFSET,
		TRUE);

	/*
	 * Remove user access to monitor-set-up maps.
	 */
	pme_protect(MONSTART, MONEND, PG_KW|PG_NC);

	/*
	 * Invalidate any other pages in last segment
	 * besides the u area, EEPROM_ADDR, CLKADDR,
	 * MEMREG, INTERREG and MONSHORTPAGE.  This sets
	 * up the kernel redzone below the u area.  We
	 * get interrupt redzone for free when the kernel
	 * is write protected as the interrupt stack is
	 * the first thing in the data area.  Since u
	 * and MONSHORTPAGE are defined as 32 bit virtual
	 * addresses (to get short references to work),
	 * we must mask to get only the 28 bits we really
	 * want to look at.
	 */
	lv = (vm_offset_t)(NBSG * (NSEGMAP - 1));
	for (v = lv; v < lv + NBSG; v += NBPG) {
		if (v == ((vm_offset_t)MONSHORTPAGE & 0x0FFFFFFF))
			setpgmap(v,		/* remove any user access */
			    (long)(((getpgmap(v) & ~PG_PROT) | PG_KW | PG_NC)));
		else if (
		    v != ((vm_offset_t)MONSHORTPAGE & 0x0FFFFFFF) &&
		    v != (vm_offset_t)EEPROM_ADDR &&
		    v != (vm_offset_t)CLKADDR &&
		    v != (vm_offset_t)MEMREG &&
		    v != (vm_offset_t)INTERREG)
			setpgmap(v, (long)0);
	}

	setcputype();			/* sets cpu and dvmasize variables */
#ifdef	SUN3_260
	if (cpu == CPU_SUN3_260)	/* initialize virtual address cache */
		vac_init();
#endif

	/*
	 * Make sure the memory error register is
	 * set up to generate interrupts on error.
	 */
#if	defined(SUN3_160) || defined(SUN3_50) || defined(SUN3_110) || defined(SUN3_60)
	if (cpu == CPU_SUN3_160 || cpu == CPU_SUN3_50)
		MEMREG->mr_per = PER_INTENA | PER_CHECK;
#endif	defined(SUN3_160) || defined(SUN3_50) || defined(SUN3_110) || defined(SUN3_60)

#ifdef	SUN3_260
	if (cpu == CPU_SUN3_260) {
		register struct eccreg **ecc_nxt = ecc_alive;
		register struct eccreg *ecc;

		/*
		 * Go probe for all memory cards and perform initialization.
		 * The address of the cards found is stashed in ecc_alive[].
		 * We assume that the cards are already enabled and the
		 * base addresses have been set correctly by the monitor.
		 */
		for (ecc = ECCREG; ecc < &ECCREG[MAX_ECC]; ecc++) {
			if (peekc((char *)ecc) == -1)
				continue;
			MEMREG->mr_dvma = 1; /* clear intr from mem register */
			ecc->syndrome |= SY_CE_MASK; /* clear syndrom fields */
			ecc->eccena |= ENA_SCRUB_MASK;
			ecc->eccena |= ENA_BUSENA_MASK;
			*ecc_nxt++ = ecc;
		}
		*ecc_nxt = (struct eccreg *)0;		/* terminate list */
	}
#endif	SUN3_260

	/*
	 * v_memorysize is the amount of physical memory while
	 * v_memoryavail is the amount of usable memory in versions
	 * equal or greater to 1.  Mon_mem is the difference which
	 * is the number of pages hidden by the monitor.
	 */

	if (sunromp->v_romvec_version >= 1)
		mon_mem = btop(*sunromp->v_memorysize - *sunromp->v_memoryavail);
	else
		mon_mem = 0;
	/*
	 * If physmem is patched to be non-zero, use it instead of
	 * the monitor value unless physmem is larger than the total
	 * amount of memory on hand.
	 */
	if (physmem == 0 || physmem > btop(*sunromp->v_memorysize))
		physmem = btop(*sunromp->v_memorysize);
	/*
	 * Adjust physmem down for the pages stolen by the monitor.
	 */
	physmem -= mon_mem;

	/*
	 * v_vector_cmd is the handler for new monitor vector
	 * command in versions equal or greater to 2.
	 * We install v_handler() there for Unix.
	 */
	if (sunromp->v_romvec_version >= 2)
		*sunromp->v_vector_cmd = v_handler;

#include <bwtwo.h>
#if	NBWTWO > 0
	if (physmem > btop(OBFBADDR + FBSIZE))
	        fbobmemavail = 1;
	else
	        fbobmemavail = 0;
#else
	fbobmemavail = 0;
#endif


	/* XXX - need to handle message buffer */


	/*
	 * Allocate pmegs for DVMA space with zero pme's
	 */
	pme_zero(DVMA, DVMA + NBPG*dvmasize, TRUE);

	/*
	 * Allocate IOPB memory space just below the message
	 * buffer and map it to the first pages of DVMA space.
	 */
	physmem -= IOPBMEM;
	pmap_map_page(DVMA, physmem, IOPBMEM*NBPG);

	/*
	 *	The following constants are set to keep a bunch
	 *	of Unix code happy, all uses of these should eventually
	 *	be fixed.
	 */
	maxmem = physmem;

	/*
	 *	Tell the VM system what virtual and physical memory
	 *	it can use.
	 */
	mem_size = (vm_size_t)ptob(physmem);	/* Mach version of physmem */

	avail_start = (vm_offset_t)round_page(firstaddr);
	avail_end = (vm_offset_t)trunc_page(mem_size);
	virtual_avail = (vm_offset_t)round_page(virtual_avail);
	virtual_end = (vm_offset_t)round_page(VM_MAX_KERNEL_ADDRESS);
}
