/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	pmap.h,v $
 * Revision 2.9  93/02/01  09:52:06  danner
 * 	Include gcc_asm.h
 * 
 * 
 * Revision 2.8  92/03/31  15:18:35  rpd
 * 	Removed pmap_remove_attributes.
 * 	[92/03/25            rpd]
 * 
 * Revision 2.7  91/05/14  17:46:03  mrt
 * 	Correcting copyright
 * 
 * Revision 2.6  91/05/08  13:21:52  dbg
 * 	Add volatile declarations.
 * 	[91/03/28            dbg]
 * 
 * 	Changes for discarding kernel stacks.  VAX hardware PCB is gone.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.5  90/09/09  14:34:12  rpd
 * 	Use decl_simple_lock_data.
 * 	[90/08/30            rpd]
 * 
 * Revision 2.4  90/06/02  15:08:48  rpd
 * 	Added PMAP_CONTEXT definition.
 * 	[90/03/26  23:05:17  rpd]
 * 
 * Revision 2.3  90/01/22  12:14:53  af
 * 	Added pmap_remove_attributes.
 * 
 * Revision 2.2.1.1  89/12/09  10:49:40  af
 * 	Added pmap_attribute() [does nothing].
 * 	[89/12/08            af]
 * 
 * Revision 2.2  89/09/08  11:27:56  dbg
 * 	Fix single-CPU definition of PMAP_DEACTIVATE_USER.
 * 	[89/08/22            dbg]
 * 
 *  7-Jul-88  David Golub (dbg) at Carnegie-Mellon University
 *	Split PMAP_ACTIVATE and PMAP_DEACTIVATE into separate user and
 *	kernel versions.
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
 * 29-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 * 24-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added MARK_CPU_IDLE and MARK_CPU_ACTIVE to suppress TLB shootdown
 *	interrupts during the idle loop.
 *
 *  7-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added pmap_phys_address() routine [macro].
 *
 * 21-Jul-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added versions of PMAP_ACTIVATE and PMAP_DEACTIVATE for single
 *	CPU configurations.  Fixed PMAP_ACTIVATE so that it gets the
 *	lock on the new pmap only; simultaneous updates on the kernel pmap
 *	will be caught by an IP interrupt after save_context().
 *
 * 15-Jul-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added pmap_resident_count(); fixed copyright.
 *
 * 24-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added code to invalidate translation buffers on other CPUS.
 *
 * 16-Jan-87  David Golub (dbg) at Carnegie-Mellon University
 *	Moved private declarations from this file to vax/pmap.c.
 *
 * 29-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Changed BUSYP, BUSYV to bit_lock, bit_unlock.  Removed last of
 *	'MACH_VM_SPARSE' code as it will be entirely rewritten.
 *
 * 19-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added definitions for VAX_PROT_SHIFT, VAX_PTE_WIRED and
 *	VAX_PTE_MOD for more efficient pmap module.
 *
 *  7-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed "unsigned long" to "unsigned int" in pt_entry to make
 *	lint happy.
 *
 * 25-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added VAX_URKW to protection codes (for U area in user space).
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
 */

/*
 *	File:	vax/pmap.h
 *
 *	Authors: Avadis Tevanian, Jr., Michael Wayne Young, 1985.
 *
 *	Machine-dependent structures for the physical map module.
 */

#ifndef	_PMAP_MACHINE_
#define	_PMAP_MACHINE_	1

#ifndef	ASSEMBLER

#include <vax/gcc_asm.h>
#include <kern/zalloc.h>
#include <kern/lock.h>
#include <mach/vax/vm_param.h>
#include <mach/vm_statistics.h>

/*
 *	VAX Page Table Entry
 */

struct pt_entry {
	unsigned int
			pfn:21,		/* page frame number */
			wired:1,	/* is this page wired?
					   (not used by hardware) */
			unused:4,	/* bits we aren't using
					   (not used by hardware) */
			modify:1,	/* hardware maintained modify */
			prot:4,		/* protection */
			valid:1;	/* valid */
};

typedef struct pt_entry	pt_entry_t;
#define	PT_ENTRY_NULL	((pt_entry_t *) 0)

#endif	ASSEMBLER

/*
 *	Vax PTE protection codes.  (To be used in conjunction with the
 *	structure above).
 */

#define	VAX_NO_ACCESS	0		/* no access */
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
#define	VAX_PTE_PFN	0x001fffff

#define	P0PAGES		0x200000	/* number of pages in P0 */
#define	P1PAGES		0x200000	/* number of pages in P1 */

#ifndef	ASSEMBLER
typedef	volatile long	cpu_set;	/* set of CPUs - must be <= 32 */

struct pmap {
	pt_entry_t	*p0br;		/* P0 base register */
	int		p0lr;		/* P0 length register */
	pt_entry_t	*p1br;		/* P1 base register */
	int		p1lr;		/* P1 length register */
	int		ref_count;	/* reference count */
	decl_simple_lock_data(,
			lock)		/* lock on map */
	struct pmap_statistics	stats;	/* map statistics */
	cpu_set		cpus_using;	/* bitmap of cpus using pmap */
};

typedef struct pmap	*pmap_t;

#define	PMAP_NULL	((pmap_t) 0)

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
volatile
boolean_t	cpu_update_needed[NCPUS];

/*
 *	External declarations for PMAP_ACTIVATE.
 */

extern void	process_pmap_updates();
extern void	pmap_update_interrupt();
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

#define	PMAP_ACTIVATE_KERNEL(my_cpu) {					\
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
	simple_lock(&kernel_pmap->lock);				\
									\
	/*								\
	 *	Process invalidate requests for the kernel pmap.	\
	 */								\
	if (cpu_update_needed[(my_cpu)])				\
	    process_pmap_updates(kernel_pmap);				\
									\
	/*								\
	 *	Mark that this cpu is using the pmap.			\
	 */								\
	i_bit_set((my_cpu), &kernel_pmap->cpus_using);			\
									\
	/*								\
	 *	Mark this cpu active - IPL will be lowered by		\
	 *	load_context().						\
	 */								\
	i_bit_set((my_cpu), &cpus_active);				\
									\
	simple_unlock(&kernel_pmap->lock);				\
}

#define PMAP_DEACTIVATE_KERNEL(my_cpu)	{				\
	/*								\
	 *	Mark pmap no longer in use by this cpu even if		\
	 *	pmap is locked against updates.				\
	 */								\
	i_bit_clear((my_cpu), &kernel_pmap->cpus_using);		\
}

#define PMAP_ACTIVATE_USER(pmap, th, my_cpu)	{			\
	register pmap_t		tpmap = (pmap);				\
									\
	/*								\
	 *	Do nothing if this is the kernel pmap.			\
	 */								\
	if (tpmap != kernel_pmap) {					\
	    register pcb_t	pcb = thread_pcb((th));			\
									\
	    /*								\
	     *	Let pmap updates proceed while we wait for this pmap.	\
	     */								\
	    i_bit_clear((my_cpu), &cpus_active);			\
									\
	    /*								\
	     *	Lock the pmap to put this cpu in its active set.	\
	     *	Wait for updates here.					\
	     */								\
	    simple_lock(&tpmap->lock);					\
									\
	    /*								\
	     *	Reload the map registers and invalidate the TLB.	\
	     */								\
	    mtpr(P0BR, (int) tpmap->p0br);				\
	    mtpr(P0LR,       tpmap->p0lr);				\
	    mtpr(P1BR, (int) tpmap->p1br);				\
	    mtpr(P1LR,       tpmap->p1lr);				\
									\
	    mtpr(TBIA, 0);						\
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
	    simple_unlock(&tpmap->lock);				\
	}								\
}

#define PMAP_DEACTIVATE_USER(pmap, thread, my_cpu)	{		\
	register pmap_t		tpmap = (pmap);				\
	/*								\
	 *	Do nothing if this is the kernel pmap.			\
	 */								\
	if (tpmap != kernel_pmap) {					\
									\
	    /*								\
	     *	Mark pmap no longer in use by this cpu even if		\
	     *	pmap is locked against updates.				\
	     */								\
	    i_bit_clear((my_cpu), &tpmap->cpus_using);			\
	}								\
}

#define	MARK_CPU_IDLE(my_cpu)	{					\
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
}

#define	MARK_CPU_ACTIVE(my_cpu)	{					\
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
}

#else	NCPUS > 1

/*
 *	With only one CPU, we just have to indicate whether the pmap is
 *	in use.
 */

#define	PMAP_ACTIVATE_KERNEL(my_cpu)	{				\
	kernel_pmap->cpus_using = TRUE;					\
}

#define PMAP_DEACTIVATE_KERNEL(my_cpu)	{				\
	kernel_pmap->cpus_using = FALSE;				\
}

#define PMAP_ACTIVATE_USER(pmap, th, my_cpu)	{			\
	register pmap_t		tpmap = (pmap);				\
									\
	if (tpmap != kernel_pmap) {					\
	    register pcb_t	pcb = thread_pcb((th));			\
									\
	    mtpr(P0BR, (int) tpmap->p0br);				\
	    mtpr(P0LR,       tpmap->p0lr);				\
	    mtpr(P1BR, (int) tpmap->p1br);				\
	    mtpr(P1LR,       tpmap->p1lr);				\
									\
	    mtpr(TBIA, 0);						\
									\
	    tpmap->cpus_using = TRUE;					\
	}								\
}

#define PMAP_DEACTIVATE_USER(pmap, thread, cpu)	{			\
	if ((pmap) != kernel_pmap)					\
	    (pmap)->cpus_using = FALSE;					\
}

#endif	NCPUS > 1

#define	pmap_resident_count(pmap)	((pmap)->stats.resident_count)
#define	pmap_phys_address(frame)	((vm_offset_t) (vax_ptob(frame)))
#define pmap_attribute(pmap,addr,size,attr,val)	KERN_INVALID_ARGUMENT

#endif	ASSEMBLER

#endif	_PMAP_MACHINE_
