/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pmap.h,v $
 * Revision 2.11  89/03/09  22:20:36  rpd
 * 	More cleanup.
 * 
 * Revision 2.10  89/02/25  20:27:35  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.9  89/01/15  16:37:51  rpd
 * 	Updated the macros to the new style.
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:24:05  rpd]
 * 
 * Revision 2.8  88/08/25  18:23:48  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Remove forcible setting of AST_NONE when handling kernel_pmap in
 * 	activate macros.  Initializing the PCB is sufficient.
 * 	[88/08/11  18:50:57  mwyoung]
 * 
 * Revision 2.7  88/08/10  10:34:23  rvb
 * Be careful about what gets out when KERNEL is not defined.
 * It's pretty ridiculous that this file gets included by user
 * programs at all.
 * 
 * 13-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Include "pcb.h" for activate/deactivate macros.
 *
 *  9-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Fix PMAP_ACTIVATE macro for NCPUS <= 1.
 *
 * 13-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Actually include "cpus.h" and "vax/pcb.h"; we've been getting
 *	them indirectly by accident so far.
 *
 *  9-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Fix PMAP_ACTIVATE macro for NCPUS <= 1.
 *
 *  3-Apr-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Add PCB_PMAP_INITIALIZE to initialize pcb fields, even for
 *	kernel-only tasks.  Turn on AST_NONE when activating
 *	kernel_pmap.  [The latter may not be strictly necessary.]
 *
 * 17-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	MARK_CPU_IDLE and MARK_CPU_ACTIVE must manipulate a separate
 *	cpu_idle set.  The scheduler's cpu_idle indication is NOT
 *	synchronized with these calls.  MARK_CPU_ACTIVE also needs spls.
 *
 * 24-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added MARK_CPU_IDLE and MARK_CPU_ACTIVE to suppress TLB shootdown
 *	interrupts during the idle loop.
 *
 * 21-Jul-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added versions of PMAP_ACTIVATE and PMAP_DEACTIVATE for single
 *	CPU configurations.  Fixed PMAP_ACTIVATE so that it gets the
 *	lock on the new pmap only; simultaneous updates on the kernel pmap
 *	will be caught by an IP interrupt after save_context().
 *
 * 24-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added code to invalidate translation buffers on other CPUS.
 *
 * 19-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added definitions for VAX_PROT_SHIFT, VAX_PTE_WIRED and
 *	VAX_PTE_MOD for more efficient pmap module.
 *
 * 11-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Second try at sparse pmaps.  Separate pv_list and sparseness
 *
 *  5-Dec-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added page table entry definition, VAX protection codes, and a real
 *	pmap structure definition.
 *
 * 13-Oct-85  Michael Wayne Young (mwyoung) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	vax/pmap.h
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Machine-dependent structures for the physical map module.
 */

#ifndef	_PMAP_MACHINE_
#define _PMAP_MACHINE_	1

#ifndef	ASSEMBLER

#include <kern/lock.h>
#include <mach/vax/vm_param.h>
#include <mach/vm_statistics.h>

#ifdef	KERNEL
#include <vax/pcb.h>
#endif	KERNEL

/*
 *	VAX Page Table Entry
 */

struct pt_entry {
	unsigned int
			pfn:21,		/* page frame number */
/*			unused:5,	/* unused by VAX hardware */
			wired:1,	/* is this page wired? */
			unused:4,	/* bits we aren't using */
			modify:1,	/* hardware maintained modify */
			prot:4,		/* protection */
			valid:1;	/* valid */
};

typedef struct pt_entry	pt_entry_t;
#define PT_ENTRY_NULL	((pt_entry_t *) 0)

#endif	ASSEMBLER

/*
 *	Vax PTE protection codes.  (To be used in conjunction with the
 *	structure above).
 */

#define VAX_NO_ACCESS	0		/* no access */
#define VAX_UR		15		/* user readable */
#define VAX_UW		4		/* user writeable */
#define VAX_KR		3		/* kernel readable */
#define VAX_KW		2		/* kernel writeable */
#define VAX_URKW	14		/* kernel writeable, user readable */

#define VAX_PROT_SHIFT	27
/*
 *	VAX pte bit definitions (to be used directly on the ptes
 *	without using the bit fields).
 */

#define VAX_PTE_VALID	0x80000000
#define VAX_PTE_UR	0x78000000
#define VAX_PTE_UW	0x20000000
#define VAX_PTE_KR	0x18000000
#define VAX_PTE_KW	0x10000000
#define VAX_PTE_URKW	0x70000000
#define VAX_PTE_MOD	0x04000000
#define VAX_PTE_WIRED	0x00200000
#define VAX_PTE_PFN	0x001fffff

#define P0PAGES		0x200000	/* number of pages in P0 */
#define P1PAGES		0x200000	/* number of pages in P1 */

#ifndef	ASSEMBLER
#include <kern/macro_help.h>

typedef	long		cpu_set;	/* set of CPUs - must be <= 32 */

struct pmap {
	pt_entry_t	*p0br;		/* P0 base register */
	long		p0lr;		/* P0 length register */
	pt_entry_t	*p1br;		/* P1 base register */
	long		p1lr;		/* P1 length register */
	int		ref_count;	/* reference count */
	decl_simple_lock_data(,
			lock)		/* lock on map */
	struct pmap_statistics	stats;	/* map statistics */
	cpu_set		cpus_using;	/* bitmap of cpus using pmap */
};

typedef struct pmap	*pmap_t;

#define PMAP_NULL	((pmap_t) 0)

#if	NCPUS > 1
/*
 *	List of cpus that are actively using mapped memory.  Any
 *	pmap update operation must wait for all cpus in this list.
 *	Update operations must still be queued to cpus not in this
 *	list.
 */
cpu_set		cpus_active;

/*
 *	List of cpus that are idle, but still operating, and will want
 *	to see any kernel pmap updates when they become active.
 */
cpu_set		cpus_idle;

/*
 *	Quick test for pmap update requests.
 */
boolean_t	cpu_update_needed[NCPUS];

/*
 *	External declarations for PMAP_ACTIVATE.
 */

void		process_pmap_updates();
void		pmap_update_interrupt();
extern	pmap_t	kernel_pmap;

#endif	NCPUS > 1

/*
 *	Machine dependent routines that are used only for VAX.
 */

pt_entry_t	*pmap_pte();

/*
 *	Macros for speed.
 */

#if	NCPUS > 1

/*
 *	For multiple CPUS, PMAP_ACTIVATE and PMAP_DEACTIVATE must manage
 *	fields to control TLB invalidation on other CPUS.
 */

#define PMAP_ACTIVATE(pmap, th, my_cpu)					\
MACRO_BEGIN								\
	register pmap_t		tpmap = (pmap);				\
	register struct pcb	*pcb = thread_pcb((th));		\
									\
									\
	/*								\
	 *	Let pmap updates proceed while we wait for this pmap.	\
	 */								\
	i_bit_clear((my_cpu), &cpus_active);				\
									\
	/*								\
	 *	Lock the pmap to put this cpu in its active set.	\
	 *	Wait for updates here.					\
	 */								\
	simple_lock(&tpmap->lock);					\
									\
	if (tpmap == kernel_pmap) {					\
	    /*								\
	     *	Process invalidate requests for the kernel pmap.	\
	     *	Don't load the map registers.				\
	     */								\
	    if (cpu_update_needed[(my_cpu)])				\
		process_pmap_updates(kernel_pmap);			\
	}								\
	else {								\
	    /*								\
	     *	No need to invalidate the TLB - the entire user pmap	\
	     *	will be invalidated by load_context().  Just reload	\
	     *	the map registers.					\
	     */								\
	    pcb->pcb_p0br = tpmap->p0br;				\
	    pcb->pcb_p0lr = tpmap->p0lr | AST_NONE;			\
	    pcb->pcb_p1br = tpmap->p1br;				\
	    pcb->pcb_p1lr = tpmap->p1lr;				\
	}								\
									\
	/*								\
	 *	Mark that this cpu is using the pmap.			\
	 */								\
	i_bit_set((my_cpu), &tpmap->cpus_using);			\
									\
	/*								\
	 *	Mark this cpu active - IPL will be lowered by		\
	 *	load_context().						\
	 */								\
	i_bit_set((my_cpu), &cpus_active);				\
									\
	simple_unlock(&tpmap->lock);					\
MACRO_END

#define PMAP_DEACTIVATE(pmap, thread, my_cpu)				\
MACRO_BEGIN								\
	/*								\
	 *	Mark pmap no longer in use by this cpu even if		\
	 *	pmap is locked against updates.				\
	 */								\
	i_bit_clear((my_cpu), &(pmap)->cpus_using);			\
MACRO_END

#define MARK_CPU_IDLE(my_cpu)						\
MACRO_BEGIN								\
	/*								\
	 *	Mark this cpu idle, and remove it from the active set,	\
	 *	since it is not actively using any pmap.  Signal_cpus	\
	 *	will notice that it is idle, and avoid signaling it,	\
	 *	but will queue the update request for when the cpu	\
	 *	becomes active.						\
	 */								\
	int	s = splvm();						\
	i_bit_set((my_cpu), &cpus_idle);				\
	i_bit_clear((my_cpu), &cpus_active);				\
	splx(s);							\
MACRO_END

#define MARK_CPU_ACTIVE(my_cpu)						\
MACRO_BEGIN								\
									\
	int	s = splvm();						\
	/*								\
	 *	If a kernel_pmap update was requested while this cpu	\
	 *	was idle, process it as if we got the interrupt.	\
	 *	Before doing so, remove this cpu from the idle set.	\
	 *	Since we do not grab any pmap locks while we flush	\
	 *	our TLB, another cpu may start an update operation	\
	 *	before we finish.  Removing this cpu from the idle	\
	 *	set assures that we will receive another update		\
	 *	interrupt if this happens.				\
	 */								\
	i_bit_clear((my_cpu), &cpus_idle);				\
									\
	if (cpu_update_needed[(my_cpu)])				\
	    pmap_update_interrupt();					\
									\
	/*								\
	 *	Mark that this cpu is now active.			\
	 */								\
	i_bit_set((my_cpu), &cpus_active);				\
	splx(s);							\
MACRO_END

#else	NCPUS > 1

/*
 *	With only one CPU, we just have to indicate whether the pmap is
 *	in use.
 */

#define PMAP_ACTIVATE(pmap, th, my_cpu)					\
MACRO_BEGIN								\
	register pmap_t		tpmap = (pmap);				\
	register struct pcb	*pcb = thread_pcb((th));		\
									\
	if (tpmap != kernel_pmap) {					\
	    pcb->pcb_p0br = tpmap->p0br;				\
	    pcb->pcb_p0lr = tpmap->p0lr | AST_NONE;			\
	    pcb->pcb_p1br = tpmap->p1br;				\
	    pcb->pcb_p1lr = tpmap->p1lr;				\
	}								\
	tpmap->cpus_using = TRUE;					\
MACRO_END

#define PMAP_DEACTIVATE(pmap, thread, cpu)				\
MACRO_BEGIN								\
	(pmap)->cpus_using = FALSE;					\
MACRO_END

#endif	NCPUS > 1

#define PMAP_PCB_INITIALIZE(pcb)					\
MACRO_BEGIN								\
	pcb->pcb_p0br = (struct pt_entry *) VM_MIN_KERNEL_ADDRESS;	\
	pcb->pcb_p0lr = 0 | AST_NONE;					\
	pcb->pcb_p1br = (struct pt_entry *) VM_MIN_KERNEL_ADDRESS;	\
	pcb->pcb_p1lr = P1PAGES;					\
MACRO_END

#define pmap_resident_count(pmap)	((pmap)->stats.resident_count)
#define pmap_phys_address(frame)	((vm_offset_t) (vax_ptob(frame)))

#endif	ASSEMBLER

#endif	_PMAP_MACHINE_
