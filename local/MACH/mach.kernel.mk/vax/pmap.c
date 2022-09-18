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
 * $Log:	pmap.c,v $
 * Revision 2.12  89/03/09  22:20:20  rpd
 * 	More cleanup.
 * 
 * Revision 2.11  89/02/25  20:27:19  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.10  89/01/15  16:37:19  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:23:01  rpd]
 * 
 * Revision 2.9  88/12/19  02:55:00  mwyoung
 * 	Remove lint.
 * 	[88/12/17            mwyoung]
 * 	
 * 	Add pmap_valid_page().
 * 	[88/12/14            mwyoung]
 * 	
 * 	Fixed include file references.
 * 	[88/11/22  02:12:40  mwyoung]
 * 	
 * 	Only try to verify free pages after pmap_init is done.
 * 	[88/11/14            mwyoung]
 * 	
 * 	Add pmap_verify_free().
 * 	[88/11/09            mwyoung]
 * 
 * Revision 2.8  88/10/18  03:41:14  mwyoung
 * 	Move include file reference outside routines; lint gets confused.
 * 	[88/10/06            mwyoung]
 * 
 * Revision 2.7  88/08/25  18:23:05  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Use ZALLOC/ZFREE.
 * 	[88/08/16  00:42:24  mwyoung]
 * 
 * Revision 2.6  88/08/10  10:31:56  rvb
 *  10-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 *  	Define ka820_csr to map port controller.
 *  
 *   8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 *  	We need to define ka62a_csr1, kax_ssc and cca for the 6200.
 *  	They are set to appropriate physical addresses in vax_init
 *  	after the call to pmap_bootstrap.
 *  
 *   7-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Added bug fix from DBG: protect pv_list_zone with SPLVM
 * 	(missed one).
 * 
 * Revision 2.5.1.1  88/08/08  16:59:19  rvb
 * 10-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Define ka820_csr to map port controller.
 * 
 *  8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	We need to define ka62a_csr1, kax_ssc and cca for the 6200.
 * 	They are set to appropriate physical addresses in vax_init
 * 	after the call to pmap_bootstrap.
 * 
 * 10-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Remove parentheses in definitions of user_pt_{,un}lock; the
 *	simple_lock macro becomes empty for NCPUS == 1.
 *
 *  8-Jun-88  David Golub (dbg) at Carnegie-Mellon University
 *	Make kernel virtual address space larger if MACH_XP.
 *	Put in rest of bug fix from DLB.
 *
 *  7-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Added bug fix from DBG: protect pv_list_zone with SPLVM
 *	(missed one).
 *
 * 12-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added bug fix from DLB:  protect pv_list_zone with splvm.
 *
 * 10-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Define ka820_csr to map port controller.
 *
 *  8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	We need to define ka62a_csr1, kax_ssc and cca for the 6200.
 *	They are set to appropriate physical addresses in vax_init
 *	after the call to pmap_bootstrap.
 *
 * 21-Mar-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added code to manage virtual space for user page tables.
 *
 * 26-Feb-88  David Golub (dbg) at Carnegie-Mellon University
 *	Changed get_pte_page to a macro that does no checking, since its
 *	callers can check pte_page_valid first.  Made pmap_collect not
 *	discard wired-down mappings.
 *
 * 17-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Use cpus_idle, not the scheduler's cpu_idle, to determine when a
 *	cpu does not need to be interrupted.  The two are not
 *	synchronized.
 *
 * 29-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 * 24-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Update list doesn't need to be a circular buffer because it's
 *	always completely emptied while locked.  Made it a linear list.
 *	Changed signal_cpus to not interrupt a CPU if it's idle - the
 *	CPU will catch up with pending updates when it becomes active.
 *
 *	Bug fixes:
 *	1) Changed modify bit array to an array of bytes, to avoid
 *	having to access it with interlocked bit instructions (which I
 *	wasn't doing).
 *	2) Set p1br and p1lr in the kernel map, in case it's loaded into
 *	a PCB.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Corrected pmap_page_protect.
 *
 * 20-Jul-87  David Golub (dbg) at Carnegie-Mellon University
 *	Changes to TLB shootdown code:
 *	- beat on the locks less
 *	- adopt fixes from Charlie Hill
 *	- go back to normal read/write lock for the pmap system lock
 *	- new locking protocol from David Black
 *	- simple versions for single-CPU
 *
 *  3-Jun-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fix INVALIDATE_TLB macro so that it doesn't always do a TBIA (it
 *	was comparing virtual addresses against page counts).
 *
 * 19-May-87  David Golub (dbg) at Carnegie-Mellon University
 *	Remove active_pmap() - it duplicated current_pmap(). (Kept
 *	Avie's fixes).  Changed process_pmap_updates and
 *	pmap_update_interrupt to ignore active pmap if its cpu bit was
 *	OFF.  There is a gap in thread_block() between PMAP_DEACTIVATE() and
 *	save_context() where the pmap is no longer in use, but the
 *	interrupt level is not high enough to block pmap update
 *	interrupts.  The pmap still looks like it is in use, and if a
 *	pmap_update_interrupt arrives during this gap, the pmap will be
 *	reactivated (!), causing a system lockup.
 *
 *  7-May-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH_XP: Added pmap_page_protect.
 *
 * 11-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fix active_pmap macro: it was sometimes called with an argument
 *	which was always ignored.
 *
 *  8-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Performance optimizations... unfortunately, this module is still
 *	dominated by the cost of the pmap/pmap_system locking.
 *
 *  5-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Dynamically determine the number of reserved pte pages as enough
 *	to map each page twice.  We may want to change this in the
 *	future.
 *
 * 24-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added code to invalidate translation buffers on other CPUS.
 *
 *  2-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Make the pmap system lock be a spin lock.
 *
 * 16-Jan-87  David Golub (dbg) at Carnegie-Mellon University
 *	Implement sparse pmaps.  Move private declarations from pmap.h
 *	to this file.
 *
 * 20-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed pmap_expand to not zero newly allocated ptes itself
 *	since kmem_alloc already returns zero filled memory.
 *
 * 19-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	More performance hacks to pmap_remove/pmap_remove_pte_page.
 *
 * 19-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Made pmap_enter 3 times faster by not playing around with bit
 *	fields.
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 24-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Corrected several of Avie's latest performance hacks.
 *
 * 18-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Performance hacks to pmap_protect and pmap_remove_pte_page.
 *
 * 15-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added pmap_is_modified routine.
 *
 * 14-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Cut system page table size in half.
 *
 * 30-Sep-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added pmap_clear_reference, pmap_get_reference and made u-area
 *	special case code conditional on NOT MACH_TT.
 *
 * 25-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added special case in pmap_enter to make the U area (part of
 *	user address space) User Read, Kernel Write.  Users writing over
 *	the U area crash the kernel.
 *
 * 17-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	pmap_collect can't lock pmap and then call pmap_remove - same
 *	deadlock problem (see entry for 9 Jul 86).  And it can't call
 *	pmap_remove while unlocked, since a pmap_enter may happen before
 *	it locks the pmap again.  Thus it has to do the internals of
 *	pmap_remove (ecch).
 *
 * 16-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Block interrupts while pmap_lock is locked.  Allocating an mbuf
 *	from an interrupt may try to do a pmap_enter.
 *
 * 11-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	In pmap_collect, free the page tables after unlocking the pmap
 *	system lock.  Same problem as in last change note.
 *
 *  9-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Unlock the pmap system during pmap_expand, to avoid deadlock:
 *		We read_lock pmap_system
 *		Someone else tries to write_lock pmap system,
 *			waits
 *		We (during kmem_alloc or kmem_free) try to read-lock
 *			the pmap system again, wait for writer.
 *	Removed all MACH_VM_SPARSE code --- it's wrong and will be
 *	done over.
 *
 * 30-Jun-86  David Golub (dbg) at Carnegie-Mellon University
 *	Make sure we invalidate the TLB before fetching modify bits ---
 *	it's possible that modify bits for ptes in the TLB aren't set
 *	until the TLB is invalidated (which would cause us to lose them).
 *
 * 26-Jun-86  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Made pmap_collect actually garbage collect maps which
 *	are not really being used actively. A pmap_list of active pmaps
 *	is now kept and PMAP_ACTIVATE increments a use_count field of
 *	the pmap so we can effectively do an "LRU" like release of
 *	pmap data.
 *
 * 20-Jun-86  David Golub (dbg) at Carnegie-Mellon University
 *	Made pmap_enter preserve the modify bit if it's replacing a
 *	valid mapping.
 *
 * 17-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added a stub for pmap_clear_modify, which does nothing on the
 *	VAX version as the modify bit is a property of the virtual page.
 *	(Which we compute when necessary.)
 *
 * 14-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed an interesting bug in pmap_expand:  when growing the
 *	stack, we have to be careful not to unmap the kernel's stack, so
 *	deallocation of the "old" stack page tables are postponed until
 *	switching to the new page tables (after context switching).
 *
 * 13-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Save vax_vsbr (VAX virtual system base register) for locore to
 *	use in initializing slave processors.
 *
 * 18-Apr-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added pmap_change_wiring for quick page wiring/unwiring.
 *
 * 11-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Second try at sparse pmaps.  Separate PVList and sparse code.
 *
 *  5-Dec-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created based on original dummy file.
 *
 */
/*
 *	File:	pmap.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	VAX Physical Map management code.
 */
/*
 *	Manages physical address maps.
 *
 *	In addition to hardware address maps, this
 *	module is called upon to provide software-use-only
 *	maps which may or may not be stored in the same
 *	form as hardware maps.  These pseudo-maps are
 *	used to store intermediate results from copy
 *	operations to and from address spaces.
 *
 *	Since the information managed by this module is
 *	also stored by the logical address mapping module,
 *	this module may throw away valid virtual-to-physical
 *	mappings at almost any time.  However, invalidations
 *	of virtual-to-physical mappings must be done as
 *	requested.
 *
 *	In order to cope with hardware architectures which
 *	make virtual-to-physical map invalidates expensive,
 *	this module may delay invalidate or reduced protection
 *	operations until such time as they are actually
 *	necessary.  This module is given full information as
 *	to which processors are currently using which maps,
 *	and to when physical maps must be made correct.
 */

#include <mach_xp.h>

#include <mach/machine/vm_types.h>

#include <mach/boolean.h>
#include <kern/thread.h>
#include <kern/zalloc.h>

#include <kern/lock.h>

#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <vm/vm_page.h>
#include <vm/vm_user.h>

#include <vax/mtpr.h>
#include <mach/vax/vm_param.h>
#include <vax/pcb.h>

/*
 *	Private data structures.
 */

/*
 *	For each vm_page_t, there is a list of all currently
 *	valid virtual mappings of that page.  An entry is
 *	a pv_entry_t; the list is the pv_table.
 */

typedef struct pv_entry {
	struct pv_entry	*next;		/* next pv_entry */
	pmap_t		pmap;		/* pmap where mapping lies */
	vm_offset_t	va;		/* virtual address for mapping */
} *pv_entry_t;

#define PV_ENTRY_NULL	((pv_entry_t) 0)

pv_entry_t	pv_head_table;		/* array of entries, one per page */
zone_t		pv_list_zone;		/* zone of pv_entry structures */

/*
 *	Each entry in the pv_head_table is locked by a bit in the
 *	pv_lock_table.  The lock bits are accessed by the physical
 *	address of the page they lock.
 */

char	*pv_lock_table;		/* pointer to array of bits */
#define pv_lock_table_size(n)	(((n)+BYTE_SIZE-1)/BYTE_SIZE)

/*
 *	First and last physical addresses that we maintain any information
 *	for.  Initialized to zero so that pmap operations done before
 *	pmap_init won't touch any non-existent structures.
 */
vm_offset_t	vm_first_phys = (vm_offset_t) 0;
vm_offset_t	vm_last_phys  = (vm_offset_t) 0;

/*
 *	Index into pv_head table, its lock bits, and the modify bits
 *	starting at vm_first_phys.
 */

#define pa_index(pa)	(atop(pa - vm_first_phys))

#define pai_to_pvh(pai)		(&pv_head_table[pai])
#define lock_pvh_pai(pai)	(bit_lock(pai, pv_lock_table))
#define unlock_pvh_pai(pai)	(bit_unlock(pai, pv_lock_table))

/*
 *	Array of modify bits, one byte per physical page (to avoid expense
 *	of locking)
 */
char	*pmap_modify_list;

/*
 *	Physical memory is reserved for user page tables, and allocated
 *	one VAX page (512 bytes, 128 ptes) at a time when necessary.
 */
struct pte_page {
	queue_chain_t	link;		/* link in active or free queues */
	pmap_t		pmap;		/* pmap this page is allocated to */
	vm_offset_t	va;		/* first virtual address mapped
					   by this page */
	int		use_count;	/* number of mappings in use */
	int		wired_count;	/* number of mappings wired in */
};
typedef	struct pte_page	*ptep_t;	/* pointer to one */
#define PTE_PAGE_NULL	((ptep_t)0)

ptep_t	ptep_array;			/* pointer to array of ptep_t
					   for each pte page allocated */

queue_head_t	pte_page_queue_active;	/* list of all active pte pages */
queue_head_t	pte_page_queue_free;	/* list of all free pte pages */

decl_simple_lock_data(,
		pte_page_queue_lock)	/* both queues are locked either
					   by this lock, or by a write-
					   lock on the pmap system lock. */

vm_offset_t	first_pte_pa;		/* physical address of first pte
					   page */
int		first_pte_pfn;		/* VAX page number for above */
int		num_pte_pages = 0;	/* number of pte pages allocated */

#define pfn_to_pte_page(pfn)	(&ptep_array[(pfn) - first_pte_pfn])
#define pte_page_to_pfn(ptep)	(first_pte_pfn + ((ptep) - ptep_array))

/*
 *	One pte page holds 128 ptes, each one of which maps 512 bytes.
 */
#define pte_page_map_size	(vax_ptob(VAX_PGBYTES/sizeof(pt_entry_t)))

#define round_pte_page(v)	(((v)+VAX_PGBYTES-1)&~(VAX_PGBYTES-1))

/*
 *	Statistics
 */
int	pte_page_active_count = 0;
int	pte_page_free_count   = 0;
int	pte_page_wired_count  = 0;
int	pte_page_max_active   = 0;
int	pte_page_max_wired    = 0;

/*
 *	Locking and TLB invalidation
 */

/*
 *	Locking Protocols:
 *
 *	There are two structures in the pmap module that need locking:
 *	the pmaps themselves, and the per-page pv_lists (which are locked
 *	by locking the pv_lock_table entry that corresponds to the pv_head
 *	for the list in question.)  Most routines want to lock a pmap and
 *	then do operations in it that require pv_list locking -- however
 *	pmap_remove_all and pmap_copy_on_write operate on a physical page
 *	basis and want to do the locking in the reverse order, i.e. lock
 *	a pv_list and then go through all the pmaps referenced by that list.
 *	To protect against deadlock between these two cases, the pmap_lock
 *	is used.  There are three different locking protocols as a result:
 *
 *  1.  pmap operations only (pmap_extract, pmap_access, ...)  Lock only
 *		the pmap.
 *
 *  2.  pmap-based operations (pmap_enter, pmap_remove, ...)  Get a read
 *		lock on the pmap_lock (shared read), then lock the pmap
 *		and finally the pv_lists as needed [i.e. pmap lock before
 *		pv_list lock.]
 *
 *  3.  pv_list-based operations (pmap_remove_all, pmap_copy_on_write, ...)
 *		Get a write lock on the pmap_lock (exclusive write); this
 *		also guaranteees exclusive access to the pv_lists.  Lock the
 *		pmaps as needed.
 *
 *	At no time may any routine hold more than one pmap lock or more than
 *	one pv_list lock.  Because interrupt level routines can allocate
 *	mbufs and cause pmap_enter's, the pmap_lock and the lock on the
 *	kernel_pmap can only be held at splvm.
 */

#if	NCPUS > 1
/*
 *	We raise the interrupt level to splvm, to block interprocessor
 *	interrupts during pmap operations.  We must take the CPU out of
 *	the cpus_active set while interrupts are blocked.
 */
#define SPLVM(spl)	{ \
	spl = splvm(); \
	i_bit_clear(cpu_number(), &cpus_active); \
}

#define SPLX(spl)	{ \
	i_bit_set(cpu_number(), &cpus_active); \
	splx(spl); \
}

/*
 *	Lock on pmap system
 */
lock_data_t	pmap_system_lock;

#define PMAP_READ_LOCK(pmap, spl) { \
	SPLVM(spl); \
	lock_read(&pmap_system_lock); \
	simple_lock(&(pmap)->lock); \
}

#define PMAP_WRITE_LOCK(spl) { \
	SPLVM(spl); \
	lock_write(&pmap_system_lock); \
}

#define PMAP_READ_UNLOCK(pmap, spl) { \
	simple_unlock(&(pmap)->lock); \
	lock_read_done(&pmap_system_lock); \
	SPLX(spl); \
}

#define PMAP_WRITE_UNLOCK(spl) { \
	lock_write_done(&pmap_system_lock); \
	SPLX(spl); \
}

#define PMAP_WRITE_TO_READ_LOCK(pmap) { \
	simple_lock(&(pmap)->lock); \
	lock_write_to_read(&pmap_system_lock); \
}

#define LOCK_PVH(index)		(lock_pvh_pai(index))

#define UNLOCK_PVH(index)	(unlock_pvh_pai(index))

#define PMAP_UPDATE_TLBS(pmap, s, e) \
{ \
	register cpu_set	cpu_mask = 1 << cpu_number(); \
	register cpu_set	users; \
 \
	/* Since the pmap is locked, other updates are locked */ \
	/* out, and any pmap_activate has finished. */ \
 \
	/* find other cpus using the pmap */ \
	users = (pmap)->cpus_using & ~cpu_mask; \
	if (users) { \
	    /* signal them, and wait for them to finish */ \
	    signal_cpus(users, (pmap), (s), (e)); \
	    while ((pmap)->cpus_using & cpus_active & ~cpu_mask) \
		continue; \
	} \
 \
	/* invalidate our own TLB if pmap is in use */ \
	if ((pmap)->cpus_using & cpu_mask) { \
	    INVALIDATE_TLB((s), (e)); \
	} \
}

#else	NCPUS > 1

#define SPLVM(spl)	{ spl = splvm(); }
#define SPLX(spl)	{ splx(spl); }

#define PMAP_READ_LOCK(pmap, spl)	SPLVM(spl)
#define PMAP_WRITE_LOCK(spl)		SPLVM(spl)
#define PMAP_READ_UNLOCK(pmap, spl)	SPLX(spl)
#define PMAP_WRITE_UNLOCK(spl)		SPLX(spl)
#define PMAP_WRITE_TO_READ_LOCK(pmap)

#define LOCK_PVH(index)
#define UNLOCK_PVH(index)

#define PMAP_UPDATE_TLBS(pmap, s, e) { \
	/* invalidate our own TLB if pmap is in use */ \
	if ((pmap)->cpus_using) { \
	    INVALIDATE_TLB((s), (e)); \
	} \
}

#endif	NCPUS > 1

#define MAX_TBIS_SIZE	32		/* > this -> TBIA */ /* XXX */

#define INVALIDATE_TLB(s, e) { \
	if ((e) - (s) < MAX_TBIS_SIZE*VAX_PGBYTES) { \
	    register vm_offset_t tbi_va; \
	    for (tbi_va = (s); tbi_va < (e); tbi_va += VAX_PGBYTES) \
		mtpr(TBIS, tbi_va); \
	} \
	else { \
	    mtpr(TBIA, 0); \
	} \
}


#if	NCPUS > 1
/*
 *	Structures to keep track of pending TLB invalidations
 */

#define UPDATE_LIST_SIZE	4

struct pmap_update_item {
	pmap_t		pmap;		/* pmap to invalidate */
	vm_offset_t	start;		/* start address to invalidate */
	vm_offset_t	end;		/* end address to invalidate */
} ;

typedef	struct pmap_update_item	*pmap_update_item_t;

/*
 *	List of pmap updates.  If the list overflows,
 *	the last entry is changed to invalidate all.
 */
struct pmap_update_list {
	decl_simple_lock_data(,	lock)
	int			count;
	struct pmap_update_item	item[UPDATE_LIST_SIZE];
} ;
typedef	struct pmap_update_list	*pmap_update_list_t;

struct pmap_update_list	cpu_update_list[NCPUS];

#endif	NCPUS > 1

/*
 *	Allocator for virtual space for VAX page tables.
 */

struct pt_region {
	struct pt_region	*next;
	struct pt_region	*prev;
	vm_offset_t		start;
	vm_offset_t		end;
	pmap_t			pmap;
};
typedef struct pt_region	*pt_region_t;
#define PT_REGION_NULL		((pt_region_t)0)

/*
 *	Use a pt_region for the head of the list to simplify
 *	boundary checking.
 */
struct pt_region	user_pt_list;
vm_offset_t		user_pt_min,
			user_pt_max;
vm_size_t		user_pt_total_size = 2*(P0PAGES*sizeof(pt_entry_t));
					/*
					 * Allow space to map just ONE full
					 * VAX address space.
					 */
vm_size_t		user_pt_free_size;
pt_region_t		user_pt_last_in_use;

decl_simple_lock_data(,	user_pt_lock_data)
#define user_pt_lock()		simple_lock(&user_pt_lock_data)
#define user_pt_unlock()	simple_unlock(&user_pt_lock_data)

void		user_pt_init();
void		user_pt_destroy();
void		user_pt_allocate();

#define DEBUG_USER_PT	0

/*
 *	Internal extension to pmap structure:
 */
struct a_pmap {
	struct pmap		pmap;
	struct pt_region	region_0;
	struct pt_region	region_1;
};
typedef struct a_pmap	*a_pmap_t;

/*
 *	Other useful macros.
 */
#define current_pmap()		(vm_map_pmap(current_thread()->task->map))
#define pmap_in_use(pmap, cpu)	(((pmap)->cpus_using & (1 << (cpu))) != 0)

#define vax_pfn(addr)		(vax_btop(addr) & 0x1fffff)
				/*
				 * page frame number, stripping off high 2
				 * bits (P0/P1/S0).
				 */
#define pmap_syspte(addr)	(&vax_vsbr[vax_pfn(addr)])
#define pmap_p0pte(pmap,addr)	(&(pmap)->p0br[vax_pfn(addr)])
#define pmap_p1pte(pmap,addr)	(&(pmap)->p1br[vax_pfn(addr)])

#define vax_p0(addr)	(((addr) & 0x40000000) == 0)
				/* stack bit not on -> p0 */

struct pmap	kernel_pmap_store;
pmap_t		kernel_pmap;
pt_entry_t	*vax_sbr;		/* physical address */
vm_size_t	vax_slr;
pt_entry_t	*vax_vsbr;		/* virtual address */
vm_offset_t	phys_map_vaddr1, phys_map_vaddr2;
pt_entry_t	*phys_map_pte1, *phys_map_pte2;

struct zone	*pmap_zone;		/* zone of pmap structures */

int		ptes_per_vm_page;	/* number of VAX ptes required to map
					   one VM page. */

boolean_t	pmap_initialized = FALSE;/* Has pmap_init completed? */


void pmap_remove_range();	/* forward */
#if	NCPUS > 1
void signal_cpus();		/* forward */
#endif	NCPUS > 1

/*
 *	Assume that there are three protection codes, all using low bits.
 */
int	user_protection_codes[8];
int	kernel_protection_codes[8];

vax_protection_init()
{
	register int	*kp, *up, prot;

	kp = kernel_protection_codes;
	up = user_protection_codes;
	for (prot = 0; prot < 8; prot++) {
		switch (prot) {
		case VM_PROT_NONE | VM_PROT_NONE | VM_PROT_NONE:
			*kp++ = 0;
			*up++ = 0;
			break;
		case VM_PROT_READ | VM_PROT_NONE | VM_PROT_NONE:
		case VM_PROT_READ | VM_PROT_NONE | VM_PROT_EXECUTE:
		case VM_PROT_NONE | VM_PROT_NONE | VM_PROT_EXECUTE:
			*kp++ = VAX_PTE_KR;
			*up++ = VAX_PTE_UR;
			break;
		case VM_PROT_NONE | VM_PROT_WRITE | VM_PROT_NONE:
		case VM_PROT_NONE | VM_PROT_WRITE | VM_PROT_EXECUTE:
		case VM_PROT_READ | VM_PROT_WRITE | VM_PROT_NONE:
		case VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE:
			*kp++ = VAX_PTE_KW;
			*up++ = VAX_PTE_UW;
			break;
		}
	}
}

/*
 *	Given a map and a machine independent protection code,
 *	convert to a vax protection code.
 */

#define vax_protection(map, prot) \
	(((map) == kernel_pmap) ? kernel_protection_codes[prot] : \
				 user_protection_codes[prot])
/*
 *	Given an offset and a map, compute the address of the
 *	pte.  If the address is invalid with respect to the map
 *	then PT_ENTRY_NULL is returned (and the map may need to grow).
 *
 *	This is only used internally.
 */
pt_entry_t *pmap_pte(map, addr)
	register pmap_t		map;
	register vm_offset_t	addr;
{
	register long	pfn;

	pfn = vax_pfn(addr);

	/*
	 *	Check for p0 or p1 region.
	 */

	if (vax_p0(addr)) {
		if (pfn >= map->p0lr)
			return(PT_ENTRY_NULL);
		return(map->p0br + pfn);
	}
	else {
		/* vax_pfn already stripped off the P1 bit. */

		if (pfn < map->p1lr)
			return(PT_ENTRY_NULL);
		return(map->p1br + pfn);
	}
}

/*
 *	Macro version for speed in this module (C version needed for external
 *	references.
 */
#define pmap_pte(map, addr) \
	(vax_p0(addr) ? \
		((vax_pfn(addr) >= map->p0lr) ? \
			PT_ENTRY_NULL : (map->p0br + vax_pfn(addr))) : \
		((vax_pfn(addr) < map->p1lr) ? \
			PT_ENTRY_NULL : (map->p1br + vax_pfn(addr))))


#define DEBUG_PTE_PAGE	0

#if	DEBUG_PTE_PAGE
void ptep_check(ptep)
	ptep_t	ptep;
{
	register pt_entry_t	*pte, *epte;
	int			ctu, ctw;

	/* check the use and wired counts */
	if (ptep == PTE_PAGE_NULL)
		return;
	pte = pmap_pte(ptep->pmap, ptep->va);
	epte = pte + VAX_PGBYTES/sizeof(pt_entry_t);
	ctu = 0;
	ctw = 0;
	while (pte < epte) {
		if (pte->pfn != 0) {
			ctu++;
			if (pte->wired)
				ctw++;
		}
		pte += ptes_per_vm_page;
	}

	if (ctu != ptep->use_count || ctw != ptep->wired_count) {
		printf("use %d wired %d - actual use %d wired %d\n",
		    	ptep->use_count, ptep->wired_count, ctu, ctw);
		panic("pte count");
	}
}
#endif	DEBUG_PTE_PAGE
/*
 *	Map memory at initialization.  The physical addresses being
 *	mapped are not managed and are never unmapped.
 *
 *	For now, VM is already on, we only need to map the
 *	specified memory.
 */
vm_offset_t pmap_map(virt, start, end, prot)
	register vm_offset_t	virt;
	register vm_offset_t	start;
	register vm_offset_t	end;
	register int		prot;
{
	register int		ps;

	ps = PAGE_SIZE;
	while (start < end) {
		pmap_enter(kernel_pmap, virt, start, prot, FALSE);
		virt += ps;
		start += ps;
	}
	return(virt);
/*
 * if this is only done on kernel map for bootstrapping, we can do it
 * like this:

	template = VAX_PTE_VALID | vax_protection(kernel_pmap, prot) |
				vax_btop(start);
	pte = pmap_syspte(virt);
	i = vax_btop(end - start);
	do {
		*(int *)pte++ = template++;
	} while (--i > 0);
	return (virt + round_page(end - start));
 */
}

/*
 *	min_virtual_size is the minimum amount of kernel address space
 *	that we want.  It is declared global so that it can easily be
 *	patched.
 */

#if	MACH_XP
long	min_virtual_size = 48*1024*1024;
#else	MACH_XP
long	min_virtual_size = 32*1024*1024;
#endif	MACH_XP

vm_size_t pmap_size(size)
	vm_size_t	size;
{
	register long	map_size;

	map_size = size/128;
	if (map_size*VAX_PGBYTES < min_virtual_size)
		map_size = min_virtual_size/VAX_PGBYTES;

	return(map_size);
}

#ifdef	VAX6200
#include <vaxnb/ka62a.h>
#include <vaxnb/cca.h>
#endif	VAX6200
#ifdef	VAX820
#include <vaxnb/ka820.h>
#endif	VAX820

/*
 *	Bootstrap the system enough to run with virtual memory.
 *	Map the kernel's code and data, and allocate the system page table.
 *	Called with mapping OFF.  Page_size must already be set.
 *
 *	Parameters:
 *	load_start:	PA where kernel was loaded
 *	avail_start	PA of first available physical page
 *	avail_end	PA of last available physical page
 *	virtual_avail	VA of first available page (after kernel bss)
 *	virtual_end	VA of last available page (end of kernel address space)
 *
 *	&start_text	start of kernel text
 *	&etext		end of kernel text
 */
void pmap_bootstrap(load_start, avail_start, avail_end,
			virtual_avail, virtual_end)

	vm_offset_t	load_start;
	vm_offset_t	*avail_start;	/* IN/OUT */
	vm_offset_t	*avail_end;	/* IN/OUT */
	vm_offset_t	*virtual_avail;	/* IN/OUT */
	vm_offset_t	*virtual_end;	/* OUT */
{
	register pt_entry_t	*sbr;
	long			slr;
	vm_offset_t		vaddr;
	vm_offset_t		s_text, e_text;
	extern int		start_text, etext;
	/*
	 *	Set ptes_per_vm_page for general use.
	 */
	ptes_per_vm_page = PAGE_SIZE / VAX_PGBYTES;

	/*
	 *	Initialize protection arrays.
	 */
	vax_protection_init();

	/*
	 *	The kernel's pmap is statically allocated so we don't
	 *	have to use pmap_create, which is unlikely to work
	 *	correctly at this part of the boot sequence.
	 */

	kernel_pmap = &kernel_pmap_store;

#if	NCPUS > 1
	lock_init(&pmap_system_lock, FALSE);	/* NOT a sleep lock */
#endif	NCPUS > 1

	simple_lock_init(&kernel_pmap->lock);

	/*
	 *	Allocate the kernel page table from the front
	 *	of available physical memory.
	 */

	sbr = kernel_pmap->p0br = (pt_entry_t *) (*avail_start);
	slr = kernel_pmap->p0lr = pmap_size(*avail_end - *avail_start);
	kernel_pmap->ref_count = 1;
	vax_sbr = sbr;
	vax_slr = slr;

	/*
	 *	Set up p1br and p1lr to valid values, in case kernel_pmap
	 *	is loaded into a vax PCB.
	 */
	kernel_pmap->p1br = (pt_entry_t *)VM_MIN_KERNEL_ADDRESS;
	kernel_pmap->p1lr = P1PAGES;

	/*
	 *	Clear the entire table, thus making the length register OK.
	 */

	blkclr(sbr, slr * sizeof(pt_entry_t));

	/*
	 *	Map low system memory, system text, system data/bss/symbols
	 */

	/*
	 *	&start_text and &etext can't have arithmetic done on them
	 *	directly because they must be physical addresses.
	 */

	s_text = (vm_offset_t) &start_text;
	e_text = (vm_offset_t) &etext;
	s_text = round_page(s_text);
	e_text = trunc_page(e_text);
	vaddr = pmap_map(VM_MIN_KERNEL_ADDRESS, load_start, s_text,
						VM_PROT_WRITE|VM_PROT_READ);
	vaddr = pmap_map(vaddr, s_text, e_text, VM_PROT_READ);
	vaddr = pmap_map(vaddr, e_text, *avail_start,
						VM_PROT_WRITE|VM_PROT_READ);

	/*
	 *	Map system page table
	 */

	*avail_start = round_page(sbr + slr);
	*virtual_avail = pmap_map(vaddr, (vm_offset_t) sbr, *avail_start,
					VM_PROT_WRITE|VM_PROT_READ);
	*virtual_end = VM_MIN_KERNEL_ADDRESS + (slr * VAX_PGBYTES);

	printf("Kernel virtual space from 0x80000000 to 0x%x.\n",
			*virtual_end);
	mtpr(SBR, sbr);
	mtpr(SLR, slr);

	/*
	 *	Once we turn on mapped mode, we need to reference the system
	 *	page table via its virtual address.  (Same for kernel_pmap).
	 */

	vax_vsbr = kernel_pmap->p0br = (pt_entry_t *) vaddr;
	kernel_pmap = (pmap_t) (((vm_offset_t) kernel_pmap - load_start) +
				VM_MIN_KERNEL_ADDRESS);

#ifdef	VAX6200
	if (cpu == VAX_6200) {
extern int cca_size;
	/*
	 * Allocate a few pages for processor private space.
	 */

		ka62a_csr1 = (int *)*virtual_avail;
		*virtual_avail += VAX_PGBYTES;
		cca = (struct cca *)*virtual_avail;
		*virtual_avail += ( (cca_size + (VAX_PGBYTES-1)) & ~(VAX_PGBYTES-1));
		ka62a_ssc = (struct ka62a_ssc *)*virtual_avail;
		*virtual_avail += PAGE_SIZE;
	}
#endif	VAX6200
#ifdef	VAX820
	if (cpu == VAX_820) {
	/*
	 * Allocate a few pages for processor private space.
	 */

		ka820_csr = (int *)*virtual_avail;
		*virtual_avail += VAX_PGBYTES;
	/* tmp kludge till we write pte_page .. */
		*virtual_avail += PAGE_SIZE - VAX_PGBYTES;
	}
#endif	VAX820

	/*
	 *	Allocate two (VAX) ptes in the system map to be used
	 *	for manipulating physical memory.  One pair is allocated
	 *	per CPU.
	 */

	phys_map_vaddr1 = *virtual_avail;
	*virtual_avail += VAX_PGBYTES*NCPUS;
	phys_map_vaddr2 = *virtual_avail;
	*virtual_avail += VAX_PGBYTES*NCPUS;

	phys_map_pte1 = pmap_syspte(phys_map_vaddr1);
	phys_map_pte2 = pmap_syspte(phys_map_vaddr2);

	*virtual_avail = round_page(*virtual_avail);

	/*
	 *	Map the kernel into P0 space for the leap to mapped mode.
	 *	NB: this doesn't work for non-zero loadpoint!
	 *	    we're depending on the pre-fetch hardware.
	 */

	mtpr(P0BR, vaddr);
	mtpr(P0LR, slr);

	/*
	 *	Allocate some amount of physical memory to use for
	 *	user page tables.  The amount allocated is enough to
	 *	map each physical page twice (there are 128 possible
	 *	mappings per (Vax) page of ptes.)
	 */

	if (num_pte_pages == 0) {
		num_pte_pages = vax_btop((*avail_end - *avail_start))/128;
		num_pte_pages *= 2;
		if (num_pte_pages < 20)
			num_pte_pages = 20;
	}

	first_pte_pa = *avail_start;
	*avail_start += round_page(vax_ptob(num_pte_pages));
	first_pte_pfn = vax_btop(first_pte_pa);

	/*
	 *	Don't forget to zero it.
	 */
	blkclr((caddr_t) first_pte_pa, *avail_start - first_pte_pa);
}

/*
 *	Initialize the pmap module.
 *	Called by vm_init, to initialize any structures that the pmap
 *	system needs to map virtual memory.
 */
void pmap_init(phys_start, phys_end)
	vm_offset_t	phys_start, phys_end;
{
	register long		npages;
	register vm_offset_t	addr;
	register vm_size_t	s;

	/*
	 *	Allocate memory for the pv_head_table and its lock bits,
	 *	the modify bit array, and the pte_page table.
	 */

	npages = atop(phys_end - phys_start);
	s = (vm_size_t) (sizeof(struct pv_entry) * npages
				+ pv_lock_table_size(npages)
				+ npages
				+ num_pte_pages * sizeof(struct pte_page));

	s = round_page(s);
	addr = (vm_offset_t) kmem_alloc(kernel_map, s);
	/*
	 *	memory was cleared by kmem-alloc
	 */

	/*
	 *	Allocate the structures first to preserve word-alignment.
	 */
	ptep_array = (ptep_t) addr;
	addr = (vm_offset_t)(ptep_array + num_pte_pages);

	pv_head_table = (pv_entry_t) addr;
	addr = (vm_offset_t) (pv_head_table + npages);

	pv_lock_table = (char *) addr;
	addr = (vm_offset_t) (pv_lock_table + pv_lock_table_size(npages));

	pmap_modify_list = (char *) addr;

	/*
	 *	Create the zone of physical maps,
	 *	and of the physical-to-virtual entries.
	 */
	s = (vm_size_t) sizeof(struct a_pmap);
	pmap_zone = zinit(s, 400*s, 4096, FALSE, "pmap"); /* XXX */
	s = (vm_size_t) sizeof(struct pv_entry);
	pv_list_zone = zinit(s, 10000*s, 4096, FALSE, "pv_list"); /* XXX */

	/*
	 *	Initialize the pte-page queues.
	 */
	simple_lock_init(&pte_page_queue_lock);
	queue_init(&pte_page_queue_free);
	queue_init(&pte_page_queue_active);

	{
	    register ptep_t	ptep;
	    register int	i;

	    for (i = 0, ptep = ptep_array; i < num_pte_pages; i++, ptep++) {
		enqueue_tail(&pte_page_queue_free, (queue_entry_t) ptep);
	    }

	}
	pte_page_free_count = num_pte_pages;

#if	NCPUS > 1
	/*
	 *	Set up the pmap request lists
	 */
	{
	    register pmap_update_list_t	up;
	    register int		i;

	    for (i = 0, up = cpu_update_list; i < NCPUS; i++, up++) {
		simple_lock_init(&up->lock);
		up->count = 0;
	    }
	}
#endif	NCPUS > 1

	/*
	 *	Initialize the user_pt allocation routines
	 */
	user_pt_init();

	/*
	 *	Only now, when all of the data structures are allocated,
	 *	can we set vm_first_phys and vm_last_phys.  If we set them
	 *	too soon, the kmem_alloc above will try to use these
	 *	data structures and blow up.
	 */

	vm_first_phys = phys_start;
	vm_last_phys = phys_end;

	pmap_initialized = TRUE;
}
/*
 *	The physical address space is dense... there are no holes.
 *	All addresses provided to vm_page_startup() are valid.
 */
boolean_t	pmap_valid_page(p)
	vm_offset_t	p;
{
#ifdef	lint
	p++;
#endif	lint
	return(TRUE);
}

/*
 *	Does a page table entry actually exist?
 */
#define pte_page_valid(pte)	(pmap_syspte((vm_offset_t)(pte))->valid)

/*
 *	Given a pte, returns the pte page pointer for it.
 *	Does not work on kernel map.
 */
#define get_pte_page(pte) \
	(pfn_to_pte_page(pmap_syspte((vm_offset_t)(pte))->pfn))

/*
 *	Allocate a free pte page.
 *	The affected pmap must be locked.
 *	Returns NULL if there are no free pte pages.
 */
ptep_t	pte_free_page_alloc(pmap, va)
	register pmap_t		pmap;
	vm_offset_t		va;
{
	register ptep_t		ptep;
	vm_offset_t		sysva;
	pt_entry_t		*syspte;

	simple_lock(&pte_page_queue_lock);
	if (queue_empty(&pte_page_queue_free)) {
		simple_unlock(&pte_page_queue_lock);
		return (PTE_PAGE_NULL);
	}

	ptep = (ptep_t) dequeue_head(&pte_page_queue_free);
	pte_page_free_count--;

	if (ptep->pmap != PMAP_NULL || ptep->va != (vm_offset_t) 0) {
		panic("ptep in use!");
	}

	/*
	 *	Enter the mapping for this page in the
	 *	system map.  The virtual address we enter is the
	 *	address that is mapped by the first pte in the
	 *	pte page.
	 */

	va &= ~(pte_page_map_size - 1);
	sysva = (vm_offset_t) pmap_pte(pmap, va);
	syspte = pmap_syspte(sysva);

	/*
	 *	Mapping is invalid - TLB invalidate is not needed
	 */
	*(int *)syspte = VAX_PTE_VALID | VAX_PTE_KW
			| pte_page_to_pfn(ptep);

	ptep->pmap = pmap;
	ptep->va = va;
	enqueue_tail(&pte_page_queue_active, (queue_entry_t) ptep);
	pte_page_active_count++;
	if (pte_page_active_count > pte_page_max_active)
		pte_page_max_active = pte_page_active_count;

	simple_unlock(&pte_page_queue_lock);

#if	DEBUG_PTE_PAGE
	ptep_check(ptep);	/* should be empty */
#endif	DEBUG_PTE_PAGE
	return(ptep);
}

/*
 *	Allocate a pte page.  May grab one from another pmap if
 *	there are no free pages.
 *	Must be called with the pmap system locked for write.
 */
ptep_t	pte_page_alloc(pmap, va)
	pmap_t		pmap;
	vm_offset_t	va;
{
	ptep_t	ptep;

	if (queue_empty(&pte_page_queue_free)) {

		pmap_t		old_pmap;
		vm_offset_t	old_va;
		pt_entry_t	*spte, *epte;

		/*
		 *	no free pte pages.  Recycle one.
		 */
		ptep = (ptep_t) queue_first(&pte_page_queue_active);
		if (ptep == PTE_PAGE_NULL) {
			panic("not enough pte pages!");
		}

		/*
		 *	free the pte page
		 */

		old_pmap = ptep->pmap;
		old_va = ptep->va;
		spte = pmap_pte(old_pmap, old_va);
		epte = spte + VAX_PGBYTES/sizeof(pt_entry_t);
		simple_lock(&old_pmap->lock);
		PMAP_UPDATE_TLBS(old_pmap, old_va, old_va + pte_page_map_size);
		pmap_remove_range(old_pmap, old_va, spte, epte, TRUE);
		/*
		 *	calls pte_page_free, which clears the pte page
		 *	and puts it at the head of the free queue.
		 */
		simple_unlock(&old_pmap->lock);
	}
	return (pte_free_page_alloc(pmap, va));
}
	
/*
 *	Free a pte page.
 *	The mappings in the pte page must have already been freed.
 *	The pmap system needs only to be locked for read.
 */
void	pte_page_free(ptep)
	register ptep_t	ptep;
{
	vm_offset_t	sysva;
	pt_entry_t	*syspte;

#if	DEBUG_PTE_PAGE
	ptep_check(ptep);	/* should be empty */
#endif	DEBUG_PTE_PAGE
	/*
	 *	Remove the mapping from the system page table.
	 */
	sysva = (vm_offset_t) pmap_pte(ptep->pmap, ptep->va);
	syspte = pmap_syspte(sysva);
	simple_lock(&kernel_pmap->lock);
	PMAP_UPDATE_TLBS(kernel_pmap, sysva, sysva + VAX_PGBYTES);
	*(int *)syspte = 0;
	simple_unlock(&kernel_pmap->lock);

	/*
	 *	Clear the pte group fields.
	 */
	ptep->pmap = PMAP_NULL;
	ptep->va = (vm_offset_t) 0;
	ptep->use_count = 0;
	ptep->wired_count = 0;

	/*
	 *	Put it on the free list.
	 */
	simple_lock(&pte_page_queue_lock);
	remqueue(&pte_page_queue_active, (queue_entry_t) ptep);
	pte_page_active_count--;
	enqueue_head(&pte_page_queue_free, (queue_entry_t) ptep);
	pte_page_free_count++;
	simple_unlock(&pte_page_queue_lock);
}

/*
 *	Wire down a pte page so it cannot be reused.
 */
void	pte_page_wire(ptep)
	ptep_t	ptep;
{
	simple_lock(&pte_page_queue_lock);
	remqueue(&pte_page_queue_active, (queue_entry_t) ptep);
	pte_page_active_count--;
	pte_page_wired_count++;
	if (pte_page_wired_count > pte_page_max_wired)
		pte_page_max_wired = pte_page_wired_count;
	simple_unlock(&pte_page_queue_lock);
}

/*
 *	Unwire a pte page.
 */
void	pte_page_unwire(ptep)
	ptep_t	ptep;
{
	simple_lock(&pte_page_queue_lock);
	enqueue_tail(&pte_page_queue_active, (queue_entry_t) ptep);
	pte_page_wired_count--;
	pte_page_active_count++;
	simple_unlock(&pte_page_queue_lock);
}

/*
 *	Create and return a physical map.
 *
 *	If the size specified for the map
 *	is zero, the map is an actual physical
 *	map, and may be referenced by the
 *	hardware.
 *
 *	If the size specified is non-zero,
 *	the map will be used in software only, and
 *	is bounded by that size.
 */
pmap_t pmap_create(size)
	vm_size_t	size;
{
	register pmap_t		p;
	register pt_region_t	region;

	/*
	 *	A software use-only map doesn't even need a map.
	 */

	if (size != 0) {
		return(PMAP_NULL);
	}

	ZALLOC(pmap_zone, p, pmap_t);
	if (p == PMAP_NULL) {
		panic("pmap_create: cannot allocate a pmap");
	}

	/*
	 *	The VAX insists that p0br and p1br always point to
	 *	valid kernel-space addresses (or, in the case of p1br,
	 *	that the end of the "hole" in the p1 region must be
	 *	a valid kernel address).
	 */

	p->p0br = (pt_entry_t *)VM_MIN_KERNEL_ADDRESS;
	p->p0lr = 0;
	p->p1br = (pt_entry_t *)VM_MIN_KERNEL_ADDRESS;
	p->p1lr = P1PAGES;
	p->ref_count = 1;

	simple_lock_init(&p->lock);
	p->cpus_using = 0;

	/*
	 *	Initialize statistics.
	 */

	p->stats.resident_count = 0;
	p->stats.wired_count = 0;

	/*
	 *	Initialize the map regions to empty.
	 */
	region = &((a_pmap_t)p)->region_0;
	region->pmap = p;
	region->start = 0;
	region->end = 0;
	region->next = region;	/* chain region to itself */
	region->prev = region;	/* to mark it not-in-use */

	region = &((a_pmap_t)p)->region_1;
	region->pmap = p;
	region->start = 0;
	region->end = 0;
	region->next = region;	/* chain region to itself */
	region->prev = region;	/* to mark it not-in-use */

	return(p);
}

/*
 *	Retire the given physical map from service.
 *	Should only be called if the map contains
 *	no valid mappings.
 */

void pmap_destroy(p)
	register pmap_t	p;
{
	register int		c, s;

	if (p == PMAP_NULL)
		return;

	SPLVM(s);
	simple_lock(&p->lock);
	c = --p->ref_count;
	simple_unlock(&p->lock);
	SPLX(s);

	if (c != 0)
		return;	/* pmap still in use */

	user_pt_destroy(&((a_pmap_t)p)->region_0);
	user_pt_destroy(&((a_pmap_t)p)->region_1);

	ZFREE(pmap_zone, (vm_offset_t) p);
}

/*
 *	Add a reference to the specified pmap.
 */

void pmap_reference(p)
	register pmap_t	p;
{
	int	s;
	if (p != PMAP_NULL) {
		SPLVM(s);
		simple_lock(&p->lock);
		p->ref_count++;
		simple_unlock(&p->lock);
		SPLX(s);
	}
}

/*
 *	Remove a range of Vax page-table entries.
 *	The entries given are the first (inclusive)
 *	and last (exclusive) entries for the VM pages.
 *	The virtual address is the va for the first pte.
 *
 *	The pmap must be locked.
 *	If the pmap is not the kernel pmap, the range must lie
 *	entirely within one pte-page.  This is NOT checked.
 *	Assumes that the pte-page exists.
 */

/* static */
void pmap_remove_range(pmap, va, spte, epte, free_if_empty)
	pmap_t			pmap;
	vm_offset_t		va;
	pt_entry_t		*spte;
	pt_entry_t		*epte;
	boolean_t		free_if_empty;
{
	register pt_entry_t	*cpte;
	int			pfn;
	int			num_removed, num_unwired;
	register int		pai;
	register vm_offset_t	pa;

#if	DEBUG_PTE_PAGE
	if (pmap != kernel_pmap)
		ptep_check(get_pte_page(spte));
#endif	DEBUG_PTE_PAGE
	num_removed = 0;
	num_unwired = 0;

	for (cpte = spte; cpte < epte;
	     cpte += ptes_per_vm_page, va += PAGE_SIZE) {

	    pfn = cpte->pfn;
	    if (pfn == 0)
		continue;

	    num_removed++;
	    if (cpte->wired)
		num_unwired++;

	    pa = vax_ptob(pfn);
	    if (pa < vm_first_phys || pa >= vm_last_phys) {
		/*
		 *	Outside range of managed physical memory.
		 */
		continue;
	    }

	    pai = pa_index(pa);
	    LOCK_PVH(pai);

	    /*
	     *	Get the modify bits.
	     */
	    {
		register int		i;
		register pt_entry_t	*lpte;

		i = ptes_per_vm_page;
		lpte = cpte;
		do {
		    if (lpte->modify) {
			pmap_modify_list[pai] = 1;
			break;
		    }
		    lpte++;
		} while (--i > 0);
	    }

	    /*
	     *	Remove the mapping from the pvlist for
	     *	this physical page.
	     */
	    {
		register pv_entry_t	pv_h, prev, cur;

		pv_h = pai_to_pvh(pai);
		if (pv_h->pmap == PMAP_NULL) {
		    panic("pmap_remove: null pv_list!");
		}
		if (pv_h->va == va && pv_h->pmap == pmap) {
		    /*
		     * Header is the pv_entry.  Copy the next one
		     * to header and free the next one (we cannot
		     * free the header)
		     */
		    cur = pv_h->next;
		    if (cur != PV_ENTRY_NULL) {
			*pv_h = *cur;
			ZFREE(pv_list_zone, (vm_offset_t) cur);
		    }
		    else {
			pv_h->pmap = PMAP_NULL;
		    }
		}
		else {
		    cur = pv_h;
		    do {
			prev = cur;
			if ((cur = prev->next) == PV_ENTRY_NULL) {
			    panic("pmap-remove: mapping not in pv_list!");
			}
		    } while (cur->va != va || cur->pmap != pmap);
		    prev->next = cur->next;
		    ZFREE(pv_list_zone, (vm_offset_t) cur);
		}
	    }
	    UNLOCK_PVH(pai);
	}

	/*
	 *	Zero the PTEs to remove the mappings.
	 */

	bzero((caddr_t) spte, (epte-spte)*sizeof(pt_entry_t));

	/*
	 *	Update the counts
	 */
	pmap->stats.resident_count -= num_removed;
	pmap->stats.wired_count -= num_unwired;

	if (pmap != kernel_pmap) {
		register ptep_t	ptep;

		/*
		 *	See whether this pte page can be freed.
		 */
		ptep = get_pte_page(spte);
		ptep->use_count -= num_removed;
		ptep->wired_count -= num_unwired;
#if	DEBUG_PTE_PAGE
		ptep_check(ptep);
#endif	DEBUG_PTE_PAGE
		if (ptep->use_count == 0 && free_if_empty)
			pte_page_free(ptep);
		else if (num_unwired > 0 && ptep->wired_count == 0)
			/* was > 0 before */
			pte_page_unwire(ptep);
	}
}

/*
 *	Remove the given range of addresses
 *	from the specified map.
 *
 *	It is assumed that the start and end are properly
 *	rounded to the VAX page size.
 */

void pmap_remove(map, s, e)
	pmap_t		map;
	vm_offset_t	s, e;
{
	register pt_entry_t	*spte, *epte, *lpte, *syspte;
	int			spl;

	if (map == PMAP_NULL)
		return;

	PMAP_READ_LOCK(map, spl);

	/*
	 *	Invalidate the translation buffer first
	 */
	PMAP_UPDATE_TLBS(map, s, e);

	if (map == kernel_pmap) {
		/*
		 *	Kernel pmap is resident - can do entire
		 *	range at once.
		 */
		spte = pmap_syspte(s);
		epte = spte + vax_btop(e - s);
		pmap_remove_range(map, s, spte, epte, TRUE);
	}
	else {
		/*
		 *	User pmap.  Break into p0 and p1,
		 *	then check each pte page.
		 */
	    {
		register vm_offset_t p0end, p0start;

		p0end = vax_ptob(map->p0lr);
		if (s < p0end) {
			/*
			 *	Range includes P0.
			 */

			if (e < p0end)
				p0end = e;
			spte = pmap_p0pte(map, s);
			epte = spte + vax_btop(p0end - s);
			lpte = (pt_entry_t *)vax_round_page(spte+1);
			syspte = pmap_syspte(spte);
			p0start = s;
			while (spte < epte) {
				if (lpte > epte)
					lpte = epte;
				if (syspte->valid)
					pmap_remove_range(map, p0start,
						spte, lpte, TRUE);
				p0start += vax_ptob(lpte-spte);
				spte = lpte;
				lpte += VAX_PGBYTES/sizeof(pt_entry_t);
				syspte++;
			}
		}
	    }
	    {
		register vm_offset_t p1start;

		p1start = vax_ptob(P0PAGES + map->p1lr);
		if (e > p1start) {
			/*
			 *	Range includes P1.
			 */
			if (s > p1start)
				p1start = s;
			spte = pmap_p1pte(map, p1start);
			epte = spte + vax_btop(e - p1start);
			lpte = (pt_entry_t *)vax_round_page(spte+1);
			syspte = pmap_syspte(spte);
			while (spte < epte) {
				if (lpte > epte)
					lpte = epte;
				if (syspte->valid)
					pmap_remove_range(map, p1start,
						spte, lpte, TRUE);
				p1start += vax_ptob(lpte-spte);
				spte = lpte;
				lpte += VAX_PGBYTES/sizeof(pt_entry_t);
				syspte++;
			}
		}
	    }
	}

	PMAP_READ_UNLOCK(map, spl);
}

/*
 *	Routine:	pmap_remove_all
 *	Function:
 *		Removes this physical page from
 *		all physical maps in which it resides.
 *		Reflects back modify bits to the pager.
 */
void pmap_remove_all(phys)
	vm_offset_t	phys;
{
	register pv_entry_t	pv_h;
	register pt_entry_t	*pte;
	int			pai;
	register vm_offset_t	va;
	register pmap_t		pmap;
	int			spl;

	if (phys < vm_first_phys || phys >= vm_last_phys) {
	    /*
	     *	Not a managed page.
	     */
	    return;
	}

	/*
	 *	Lock the pmap system first, since we will be changing
	 *	several pmaps.
	 */

	PMAP_WRITE_LOCK(spl);

	/*
	 *	Walk down PV list, removing all mappings.
	 *	We have to do the same work as in pmap_remove_pte_page
	 *	since that routine locks the pv_head.  We don't have
	 *	to lock the pv_head, since we have the entire pmap system.
	 */
	pai = pa_index(phys);
	pv_h = pai_to_pvh(pai);

	while ( (pmap = pv_h->pmap) != PMAP_NULL) {
	    va = pv_h->va;

	    /*
	     *	Lock the pmap to block pmap_extract and similar routines.
	     */
	    simple_lock(&pmap->lock);

	    pte = pmap_pte(pmap, va);

	    if (!pte_page_valid(pte))
		panic("pmap_remove_all: pte invalid");

	    if (vax_ptob(pte->pfn) != phys) {
		panic("pmap_remove_all: pte doesn't point to page!");
	    }

	    pmap->stats.resident_count--;
	    if (pte->wired) {
		panic("pmap_remove_all removing a wired page");
	    }

	    /*
	     *	Tell CPU using pmap to invalidate its TLB
	     */
	    PMAP_UPDATE_TLBS(pmap, va, va + PAGE_SIZE);

	    /*
	     *	Remove the pv_entry from the pv_list.
	     */
	    {
		register pv_entry_t	cur;

		if ((cur = pv_h->next) != PV_ENTRY_NULL) {
		    *pv_h = *cur;
		    ZFREE(pv_list_zone, (vm_offset_t) cur);
		}
		else
		    pv_h->pmap = PMAP_NULL;
	    }

	    /*
	     *	Remove the mapping, collecting any modify bits.
	     */
	    {
		register pt_entry_t	*lpte;
		register int		i;

		i = ptes_per_vm_page;
		lpte = pte;
		do {
		    if (lpte->modify) {
			pmap_modify_list[pai] = 1;
		    }
		    *(int *)lpte++ = 0;
		} while (--i > 0);
	    }

	    /*
	     *	Free the pte page if it is no longer needed.
	     */
	    if (pmap != kernel_pmap) {
		register ptep_t	ptep;

		ptep = get_pte_page(pte);
		if (--ptep->use_count == 0)
		    	pte_page_free(ptep);
#if	DEBUG_PTE_PAGE
		else
		    	ptep_check(ptep);
#endif	DEBUG_PTE_PAGE
	    }
	    simple_unlock(&pmap->lock);
	}

	PMAP_WRITE_UNLOCK(spl);
}

boolean_t pmap_verify_free(phys)
	vm_offset_t	phys;
{
	pv_entry_t	pv_h;
	int		pai;
	int		spl;
	boolean_t	result;

	if (!pmap_initialized)
		return(TRUE);

	if (phys < vm_first_phys || phys >= vm_last_phys)
		return(FALSE);

	PMAP_WRITE_LOCK(spl);

	pai = pa_index(phys);
	pv_h = pai_to_pvh(pai);

	result = (pv_h->pmap == PMAP_NULL);
	PMAP_WRITE_UNLOCK(spl);

	return(result);
}

/*
 *	Routine:	pmap_copy_on_write
 *	Function:
 *		Remove write privileges from all
 *		physical maps for this physical page.
 */
void pmap_copy_on_write(phys)
	vm_offset_t	phys;
{
	register pv_entry_t	pv_e;
	register pt_entry_t	*pte;
	register int		i;
	int			spl;

	/*
	 *	Lock the entire pmap system, since we may be changing
	 *	several maps.
	 */
	PMAP_WRITE_LOCK(spl);

	pv_e = pai_to_pvh(pa_index(phys));
	if (pv_e->pmap == PMAP_NULL) {
		PMAP_WRITE_UNLOCK(spl);
		return;		/* no mappings */
	}

	/*
	 *	Run down the list of mappings to this physical page,
	 *	disabling write privileges on each one.
	 */

	while (pv_e != PV_ENTRY_NULL) {
		pmap_t		pmap;
		vm_offset_t	va;

		pmap = pv_e->pmap;
		va = pv_e->va;

		simple_lock(&pmap->lock);

		pte = pmap_pte(pmap, va);

		if (!pte_page_valid(pte))
			panic("pmap_copy_on_write: invalid pte");

		/*
		 *	Ask cpus using pmap to invalidate their TLBs
		 */
		PMAP_UPDATE_TLBS(pmap, va, va + PAGE_SIZE);

		if (pte->prot == VAX_KW) {
			/*
			 *	Kernel write becomes kernel read
			 */
			i = ptes_per_vm_page;
			do {
				pte->prot = VAX_KR;
				pte++;
			} while (--i > 0);
		}
		else if (pte->prot == VAX_UW) {
			/*
			 *	User write becomes user read
			 */
			i = ptes_per_vm_page;
			do {
				pte->prot = VAX_UR;
				pte++;
			} while (--i > 0);
		}
		simple_unlock(&pmap->lock);

		pv_e = pv_e->next;
	}

	PMAP_WRITE_UNLOCK(spl);
}

/*
 *	Set the physical protection on the
 *	specified range of this map as requested.
 */
void pmap_protect(map, s, e, prot)
	pmap_t		map;
	vm_offset_t	s, e;
	vm_prot_t	prot;
{
	register pt_entry_t	*spte, *epte, *lpte;
	register int 		vp;
	vm_offset_t	p0end, p1start;
	int		spl;

	if (map == PMAP_NULL)
		return;

	vp = vax_protection(map, prot) >> VAX_PROT_SHIFT;

	SPLVM(spl);
	simple_lock(&map->lock);

	/*
	 *	Invalidate the translation buffer first
	 */
	PMAP_UPDATE_TLBS(map, s, e);

	if (map == kernel_pmap) {
		/*
		 *	Kernel pmap is resident - can do entire
		 *	range at once.
		 */
		spte = pmap_syspte(s);
		epte = spte + vax_btop(e - s);
		while (spte < epte) {
			spte->prot = vp;
			spte++;
		}
	}
	else {
		/*
		 *	User pmap.  Break into p0 and p1,
		 *	then check each pte page.
		 */
		p0end = vax_ptob(map->p0lr);
		if (s < p0end) {
			/*
			 *	Range includes P0.
			 */
			if (e < p0end)
				p0end = e;
			spte = pmap_p0pte(map, s);
			epte = spte + vax_btop(p0end - s);
			while (spte < epte) {
				lpte = (pt_entry_t *)vax_round_page(spte+1);
				if (lpte > epte)
					lpte = epte;
				if (pte_page_valid(spte)) {
					for (; spte < lpte; spte++)
						spte->prot = vp;
				}
				else {
					spte = lpte;
				}
			}
		}
		p1start = vax_ptob(P0PAGES + map->p1lr);
		if (e > p1start) {
			/*
			 *	Range includes P1.
			 */
			if (s > p1start)
				p1start = s;
			spte = pmap_p1pte(map, p1start);
			epte = spte + vax_btop(e - p1start);
			while (spte < epte) {
				lpte = (pt_entry_t *)vax_round_page(spte+1);
				if (lpte > epte)
					lpte = epte;
				if (pte_page_valid(spte)) {
					for (; spte < lpte; spte++)
						spte->prot = vp;
				}
				else {
					spte = lpte;
				}
			}
		}
	}

	simple_unlock(&map->lock);
	SPLX(spl);
}

/*
 *	Insert the given physical page (p) at
 *	the specified virtual address (v) in the
 *	target physical map with the protection requested.
 *
 *	If specified, the page will be wired down, meaning
 *	that the related pte can not be reclaimed.
 *
 *	NB:  This is the only routine which MAY NOT lazy-evaluate
 *	or lose information.  That is, this routine must actually
 *	insert this page into the given map NOW.
 */
void pmap_enter(pmap, v, pa, prot, wired)
	register pmap_t		pmap;
	vm_offset_t		v;
	register vm_offset_t	pa;
	vm_prot_t		prot;
	boolean_t		wired;
{
	register pt_entry_t	*pte;
	pv_entry_t		pv_e;
	int			spl, vp;
	ptep_t			ptep;
	vm_offset_t		old_pa;

	if (pmap == PMAP_NULL)
		return;

	vp = vax_protection(pmap, prot);

	/*
	 *	Must allocate a new pvlist entry while we're unlocked;
	 *	zalloc may cause pageout (which will lock the pmap system).
	 *	If we determine we need a pvlist entry, we will unlock
	 *	and allocate one.  Then we will retry, throwing away
	 *	the allocated entry later (if we no longer need it).
	 */
	pv_e = PV_ENTRY_NULL;
Retry:

	PMAP_READ_LOCK(pmap, spl);

	/*
	 *	Expand pmap to include this pte.  Assume that
	 *	pmap is always expanded to include enough VAX
	 *	pages to map one VM page.
	 */

	while ((pte = pmap_pte(pmap, v)) == PT_ENTRY_NULL) {
		/*
		 *	Must unlock to expand the pmap.
		 */
		PMAP_READ_UNLOCK(pmap, spl);

		user_pt_allocate(pmap, v);

		PMAP_READ_LOCK(pmap, spl);
	}

	/*
	 *	Allocate a physical page for this pte if there isn't
	 *	one already
	 */
	if (pmap == kernel_pmap)
		ptep = PTE_PAGE_NULL;
	else if (pte_page_valid(pte))
		ptep = get_pte_page(pte);
	else {
	    /*
	     *	Try to get a free page-table page.
	     */
	    ptep = pte_free_page_alloc(pmap, v);
	    if (ptep == PTE_PAGE_NULL) {
		/*
		 *	No free pte pages.  Must get the write lock
		 *	on the pmap system to grab one from another pmap.
		 */
		PMAP_READ_UNLOCK(pmap, spl);

		/*
		 *	It's possible that the pte may have gone away...
		 */
		PMAP_WRITE_LOCK(spl);
		pte = pmap_pte(pmap, v);
		if (pte == PT_ENTRY_NULL) {
		    /*
		     *	If it has, back out and try again
		     */
		    PMAP_WRITE_UNLOCK(spl);
		    goto Retry;
		}
		ptep = pte_page_alloc(pmap, v);
		PMAP_WRITE_TO_READ_LOCK(pmap);
	    }
	}

#if	DEBUG_PTE_PAGE
	ptep_check(ptep);
#endif	DEBUG_PTE_PAGE
	/*
	 *	Special case if the physical page is already mapped
	 *	at this address.
	 */
	old_pa = vax_ptob(pte->pfn);
	if (old_pa == pa) {
	    /*
	     *	May be changing its wired attribute or protection
	     */
		
	    if (wired && !pte->wired) {
		pmap->stats.wired_count++;
		if (ptep && ptep->wired_count++ == 0)
		    pte_page_wire(ptep);
	    }
	    else if (!wired && pte->wired) {
		pmap->stats.wired_count--;
		if (ptep && --ptep->wired_count > 0)
		    pte_page_unwire(ptep);
	    }

	    {
		register int template, i;

		template = VAX_PTE_VALID | vp | vax_btop(pa);
		if (wired)
		    template |= VAX_PTE_WIRED;
		PMAP_UPDATE_TLBS(pmap, v, v + PAGE_SIZE);
		i = ptes_per_vm_page;
		do {
		    if (pte->modify)
			template |= VAX_PTE_MOD;
		    *(int *)pte++ = template++;
		} while (--i > 0);
	    }
#if	DEBUG_PTE_PAGE
	    ptep_check(ptep);
#endif	DEBUG_PTE_PAGE
	}
	else {

	    /*
	     *	Remove old mapping from the PV list if necessary.
	     */
	    if (old_pa != (vm_offset_t) 0) {
		/*
		 *	Invalidate the translation buffer,
		 *	then remove the mapping.
		 */
		PMAP_UPDATE_TLBS(pmap, v, v + PAGE_SIZE);

		/*
		 *	Don't free the pte page if removing last
		 *	mapping - we will immediately replace it.
		 */
		pmap_remove_range(pmap, v, pte,
				pte + ptes_per_vm_page, FALSE);
#if	DEBUG_PTE_PAGE
		ptep_check(ptep);
#endif	DEBUG_PTE_PAGE
	    }

	    if (pa >= vm_first_phys && pa < vm_last_phys) {

		/*
		 *	Enter the mapping in the PV list for this
		 *	physical page.
		 */
		register int		pai;
		register pv_entry_t	pv_h;

		pai = pa_index(pa);
		LOCK_PVH(pai);
		pv_h = pai_to_pvh(pai);

		if (pv_h->pmap == PMAP_NULL) {
		    /*
		     *	No mappings yet
		     */
		    pv_h->va = v;
		    pv_h->pmap = pmap;
		    pv_h->next = PV_ENTRY_NULL;
		}
		else {
#if	DEBUG
		    {
			/* check that this mapping is not already there */
			pv_entry_t	e = pv_h;
			while (e != PV_ENTRY_NULL) {
			    if (e->pmap == pmap && e->va == v)
				panic("pmap_enter: already in pv_list");
			    e = e->next;
			}
		    }
#endif	DEBUG
		    
		    /*
		     *	Add new pv_entry after header.
		     */
		    if (pv_e == PV_ENTRY_NULL) {
			UNLOCK_PVH(pai);
			PMAP_READ_UNLOCK(pmap, spl);
			/*
			 * This isn't correct either: if zalloc blocks in
			 * kmem_alloc, we return with our CPU in the active
			 * set but ipl raised.  We then can deadlock
			 * grabbing the zone lock.
			 */
			SPLVM(spl);
			ZALLOC(pv_list_zone, pv_e, pv_entry_t);
			SPLX(spl);
			goto Retry;
		    }
		    pv_e->va = v;
		    pv_e->pmap = pmap;
		    pv_e->next = pv_h->next;
		    pv_h->next = pv_e;
		    /*
		     *	Remember that we used the pvlist entry.
		     */
		    pv_e = PV_ENTRY_NULL;
		}
		UNLOCK_PVH(pai);
	    }

	    /*
	     *	And count the mapping.
	     */

	    pmap->stats.resident_count++;
	    if (ptep)
		ptep->use_count++;
	    if (wired) {
		pmap->stats.wired_count++;
		if (ptep && ptep->wired_count++ == 0)
		    pte_page_wire(ptep);
	    }

	    {
		/*
		 *	Build a template to speed up entering -
		 *	only the pfn changes.
		 */
		register int template, i;

		template = VAX_PTE_VALID | vp | vax_btop(pa);
		if (wired)
		    template |= VAX_PTE_WIRED;
		i = ptes_per_vm_page;
		do {
		    *(int *)pte++ = template++;
		} while (--i > 0);
	    }
	}
#if	DEBUG_PTE_PAGE
	ptep_check(ptep);
#endif	DEBUG_PTE_PAGE

	PMAP_READ_UNLOCK(pmap, spl);

	if (pv_e != PV_ENTRY_NULL) {
		SPLVM(spl);
		ZFREE(pv_list_zone, (vm_offset_t) pv_e);
		SPLX(spl);
	}
}

/*
 *	Routine:	pmap_change_wiring
 *	Function:	Change the wiring attribute for a map/virtual-address
 *			pair.
 *	In/out conditions:
 *			The mapping must already exist in the pmap.
 */
void pmap_change_wiring(map, v, wired)
	register pmap_t	map;
	vm_offset_t	v;
	boolean_t	wired;
{
	register pt_entry_t	*pte;
	register int		i;
	int			spl;
	ptep_t			ptep;

	/*
	 *	We must grab the pmap system lock because we may
	 *	change a pte_page queue.
	 */
	PMAP_READ_LOCK(map, spl);

	if ((pte = pmap_pte(map, v)) == PT_ENTRY_NULL)
		panic("pmap_change_wiring: pte missing");

	if (map == kernel_pmap)
		ptep = PTE_PAGE_NULL;
	else if (!pte_page_valid(pte))
		panic("pmap_change_wiring: pte invalid");
	else
		ptep = get_pte_page(pte);

	if (wired && !pte->wired) {
		/*
		 *	wiring down mapping
		 */
		map->stats.wired_count++;
		if (ptep && ptep->wired_count++ == 0)
			pte_page_wire(ptep);
	}
	else if (!wired && pte->wired) {
		/*
		 *	unwiring mapping
		 */
		map->stats.wired_count--;
		if (ptep && --ptep->wired_count == 0)
			pte_page_unwire(ptep);
	}

	i = ptes_per_vm_page;
	do {
		(pte++)->wired = wired;
	} while (--i > 0);

	PMAP_READ_UNLOCK(map, spl);
}

/*
 *	Routine:	pmap_extract
 *	Function:
 *		Extract the physical page address associated
 *		with the given map/virtual_address pair.
 */

vm_offset_t pmap_extract(pmap, va)
	register pmap_t	pmap;
	vm_offset_t	va;
{
	register pt_entry_t	*pte;
	register vm_offset_t	pa;
	int			spl;

	SPLVM(spl);
	simple_lock(&pmap->lock);
	if ((pte = pmap_pte(pmap, va)) == PT_ENTRY_NULL)
		pa = (vm_offset_t) 0;
	else if (pmap != kernel_pmap && !pte_page_valid(pte))
		pa = (vm_offset_t) 0;
	else
		pa = vax_ptob(pte->pfn);
	if (pa)
		pa |= va & (VAX_PGBYTES-1);	/* offset within page */
	simple_unlock(&pmap->lock);
	SPLX(spl);
	return(pa);
}

/*
 *	Copy the range specified by src_addr/len
 *	from the source map to the range dst_addr/len
 *	in the destination map.
 *
 *	This routine is only advisory and need not do anything.
 */
void pmap_copy(dst_pmap, src_pmap, dst_addr, len, src_addr)
	pmap_t		dst_pmap;
	pmap_t		src_pmap;
	vm_offset_t	dst_addr;
	vm_size_t	len;
	vm_offset_t	src_addr;
{
#ifdef	lint
	dst_pmap++; src_pmap++; dst_addr++; len++; src_addr++;
#endif	lint
}

/*
 *	Require that all active physical maps contain no
 *	incorrect entries NOW.  [This update includes
 *	forcing updates of any address map caching.]
 *
 *	Generally used to insure that a thread about
 *	to run will see a semantically correct world.
 */
void pmap_update()
{
	mtpr(TBIA, 0);	/* XXX */
}

/*
 *	Routine:	pmap_collect
 *	Function:
 *		Garbage collects the physical map system for
 *		pages which are no longer used.
 *		Success need not be guaranteed -- that is, there
 *		may well be pages which are not referenced, but
 *		others may be collected.
 *	Usage:
 *		Called by the pageout daemon when pages are scarce.
 */
#if	1
void pmap_collect(p)
	pmap_t		p;
{
#ifdef	lint
	p++;
#endif	lint
	/* does nothing */
}
#else	1
void pmap_collect(p)
	pmap_t 		p;
{
	vm_offset_t	p0addr, p1addr;
	vm_size_t	p0size, p1size;
	vm_offset_t	va;
	pt_entry_t	*spte, *epte, *lpte;
	int		spl;

	if (p == PMAP_NULL)
		return;

	if (p == kernel_pmap)
		panic("pmap_collect on kernel_pmap");

	/*
	 *	We can't call kmem-free with the pmap system
	 *	locked.  Save addresses of any areas to free,
	 *	and free them after unlocking.
	 */
	p0addr = 0;
	p1addr = 0;

	/*
	 *	Garbage collect map, but only if there are no
	 *	wired-down mappings.
	 */
	PMAP_READ_LOCK(p, spl);

	if (p->stats.wired_count != 0) {
		PMAP_READ_UNLOCK(p, spl);
		return;
	}

	PMAP_UPDATE_TLBS(p, VM_MIN_ADDRESS, VM_MAX_ADDRESS);

	if (p->p0lr) {
		/*
		 *	Remove all of P0 region.
		 */
		va = (vm_offset_t) 0;
		spte = p->p0br;
		epte = spte + p->p0lr;

		while (spte < epte) {
			lpte = (pt_entry_t *)vax_round_page(spte+1);
			if (lpte > epte)
				lpte = epte;
			if (pte_page_valid(spte))
				pmap_remove_range(p, va,
					spte, lpte, TRUE);
			va += vax_ptob(lpte - spte);
			spte = lpte;
		}

		p0size = p->p0lr*sizeof(pt_entry_t);
		p0addr = (vm_offset_t) p->p0br;
	}

	if (p->p1lr < P1PAGES) {
		/*
		 *	Remove all of P1 region.
		 */
		va = vax_ptob(P0PAGES + p->p1lr);
		spte = p->p1br + p->p1lr;
		epte = p->p1br + P1PAGES;

		while (spte < epte) {
			lpte = (pt_entry_t *)vax_round_page(spte+1);
			if (lpte > epte)
				lpte = epte;
			if (pte_page_valid(spte))
				pmap_remove_range(p, va,
					spte, lpte, TRUE);
			va += vax_ptob(lpte - spte);
			spte = lpte;

		}

		p1size = (P1PAGES - p->p1lr)*sizeof(pt_entry_t);
		p1addr = (vm_offset_t) (p->p1br + p->p1lr);
	}

	p->p0br = (pt_entry_t *)VM_MIN_KERNEL_ADDRESS;
	p->p0lr = 0;

	p->p1br = (pt_entry_t *)VM_MIN_KERNEL_ADDRESS;
	p->p1lr = P1PAGES;

	PMAP_READ_UNLOCK(p, spl);

	if (p0addr)
		(void) vm_deallocate(user_pt_map, p0addr, p0size);
	if (p1addr)
		(void) vm_deallocate(user_pt_map, p1addr, p1size);

}
#endif	1

/*
 *	Routine:	pmap_activate
 *	Function:
 *		Binds the given physical map to the given
 *		processor, and returns a hardware map description.
 */
void pmap_activate(my_pmap, th, my_cpu)
	register pmap_t	my_pmap;
	thread_t	th;
	int		my_cpu;
{
	PMAP_ACTIVATE(my_pmap, th, my_cpu);
}


/*
 *	Routine:	pmap_deactivate
 *	Function:
 *		Indicates that the given physical map is no longer
 *		in use on the specified processor.  (This is a macro
 *		in pmap.h)
 */
void pmap_deactivate(pmap, th, which_cpu)
	pmap_t		pmap;
	thread_t	th;
	int		which_cpu;
{
#ifdef	lint
	pmap++; th++; which_cpu++;
#endif	lint
	PMAP_DEACTIVATE(pmap, th, which_cpu);
}

/*
 *	Routine:	pmap_kernel
 *	Function:
 *		Returns the physical map handle for the kernel.
 */
pmap_t pmap_kernel()
{
    	return (kernel_pmap);
}

/*
 *	pmap_zero_page zeros the specified (machine independent)
 *	page.  This routine is written entirely in assembly language,
 *	see vax/phys.s.
 */
#if	0
pmap_zero_page(phys)
	register vm_offset_t	phys;
{
	register int	i;

	i = PAGE_SIZE / VAX_PGBYTES;
	phys = vax_pfn(phys);

	while (i--)
		zero_phys(phys++);
}
#endif	0

/*
 *	pmap_copy_page copies the specified (machine independent)
 *	pages.  This routine is written entirely in assembly language,
 *	see vax/phys.s.
 */
#if	0
pmap_copy_page(src, dst)
	vm_offset_t	src, dst;
{
	int	i;

	i = PAGE_SIZE / VAX_PGBYTES;

	while (i--) {
		copy_phys(vax_pfn(src), vax_pfn(dst));
		src += VAX_PGBYTES;
		dst += VAX_PGBYTES;
	}
}
#endif	0

/*
 *	Routine:	pmap_pageable
 *	Function:
 *		Make the specified pages (by pmap, offset)
 *		pageable (or not) as requested.
 *
 *		A page which is not pageable may not take
 *		a fault; therefore, its page table entry
 *		must remain valid for the duration.
 *
 *		This routine is merely advisory; pmap_enter
 *		will specify that these pages are to be wired
 *		down (or not) as appropriate.
 */
pmap_pageable(pmap, start, end, pageable)
	pmap_t		pmap;
	vm_offset_t	start;
	vm_offset_t	end;
	boolean_t	pageable;
{
#ifdef	lint
	pmap++; start++; end++; pageable++;
#endif	lint
}

/*
 *	pmap_redzone
 *
 *	Give the kernel read-only access to the specified address.
 *	This is used to detect stack overflows.  It is assumed that the
 *	address specified is the last possible kernel stack address.
 *	Therefore, we round up to the nearest machine dependent page.
 */

void pmap_redzone(pmap, addr)
	pmap_t		pmap;
	vm_offset_t	addr;
{
	pt_entry_t	*pte;
	int		spl;

	addr = vax_round_page(addr);
	SPLVM(spl);
	simple_lock(&pmap->lock);
	if ((pte = pmap_pte(pmap, addr)) != PT_ENTRY_NULL)
		pte->prot = VAX_KR;
	mtpr(TBIS, addr);
	simple_unlock(&pmap->lock);
	SPLX(spl);
}

/*
 *	Clear the modify bits on the specified physical page.
 *
 *	XXX this does not yet work if the physical page is in
 *	    any maps
 */

void pmap_clear_modify(phys)
	register vm_offset_t	phys;
{
	if (phys >= vm_first_phys && phys < vm_last_phys)
	    pmap_modify_list[pa_index(phys)] = 0;
}

/*
 *	pmap_is_modified:
 *
 *	Return whether or not the specified physical page is modified
 *	by any physical maps.
 *
 *	XXX this does not yet return complete information if the page
 *	    is in any pmaps - pmap_clear_reference should have just
 *	    been called
 *	    
 */

boolean_t pmap_is_modified(phys)
	register vm_offset_t	phys;
{
	if (phys >= vm_first_phys && phys < vm_last_phys)
	    return ((boolean_t)pmap_modify_list[pa_index(phys)]);
	else
	    return (FALSE);
}

/*
 *	pmap_clear_reference:
 *
 *	Clear the reference bit on the specified physical page.
 *	For the VAX, we actually have to remove all references
 *	to this page to simulate the lacking reference bit.
 */

void pmap_clear_reference(phys)
	vm_offset_t	phys;
{
	pmap_remove_all(phys);
}

/*
 *	pmap_is_referenced:
 *
 *	Return whether or not the specified physical page is referenced
 *	by any physical maps.
 *
 *	Since the VAX has no such mechanism, we always return FALSE
 *	and simulate the reference bit in pmap_clear_reference.
 */

boolean_t pmap_is_referenced(phys)
	vm_offset_t	phys;
{
#ifdef	lint
	phys++;
#endif	lint
	return(FALSE);
}

#if	NCPUS > 1
/*
*	    TLB Coherence Code (TLB "shootdown" code)
* 
* Threads that belong to the same task share the same address space and
* hence share a pmap.  However, they  may run on distinct cpus and thus
* have distinct TLBs that cache page table entries. In order to guarantee
* the TLBs are consistent, whenever a pmap is changed, all threads that
* are active in that pmap must have their TLB updated. To keep track of
* this information, the set of cpus that are currently using a pmap is
* maintained within each pmap structure (cpus_using). Pmap_activate() and
* pmap_deactivate add and remove, respectively, a cpu from this set.
* Since the TLBs are not addressable over the bus, each processor must
* flush its own TLB; a processor that needs to invalidate another TLB
* needs to interrupt the processor that owns that TLB to signal the
* update.
* 
* Whenever a pmap is updated, the lock on that pmap is locked, and all
* cpus using the pmap are signaled to invalidate. All threads that need
* to activate a pmap must wait for the lock to clear to await any updates
* in progress before using the pmap. They must ACQUIRE the lock to add
* their cpu to the cpus_using set. An implicit assumption made
* throughout the TLB code is that all kernel code that runs at or higher
* than splvm blocks out update interrupts, and that such code does not
* touch pageable pages.
* 
* A shootdown interrupt serves another function besides signaling a
* processor to invalidate. The interrupt routine (pmap_update_interrupt)
* waits for the both the pmap lock (and the kernel pmap lock) to clear,
* preventing user code from making implicit pmap updates while the
* sending processor is performing its update. (This could happen via a
* user data write reference that turns on the modify bit in the page
* table). It must wait for any kernel updates that may have started
* concurrently with a user pmap update because the IPC code
* changes mappings.
* Spinning on the VALUES of the locks is sufficient (rather than
* having to acquire the locks) because any updates that occur subsequent
* to finding the lock unlocked will be signaled via another interrupt.
* (This assumes the interrupt is cleared before the low level interrupt code 
* calls pmap_update_interrupt()). 
* 
* The signaling processor must wait for any implicit updates in progress
* to terminate before continuing with its update. Thus it must wait for an
* acknowledgement of the interrupt from each processor for which such
* references could be made. For maintaining this information, a set
* cpus_active is used. A cpu is in this set if and only if it can 
* use a pmap. When pmap_update_interrupt() is entered, a cpu is removed from
* this set; when all such cpus are removed, it is safe to update.
* 
* Before attempting to acquire the update lock on a pmap, a cpu (A) must
* be at least at the priority of the interprocessor interrupt
* (splip<=splvm). Otherwise, A could grab a lock and be interrupted by a
* kernel update; it would spin forever in pmap_update_interrupt() trying
* to acquire the user pmap lock it had already acquired. Furthermore A
* must remove itself from cpus_active.  Otherwise, another cpu holding
* the lock (B) could be in the process of sending an update signal to A,
* and thus be waiting for A to remove itself from cpus_active. If A is
* spinning on the lock at priority this will never happen and a deadlock
* will result.
*/

/*
 *	Signal another CPU that it must flush its TLB
 */
void    signal_cpus(use_list, pmap, start, end)
	register cpu_set	use_list;
	pmap_t			pmap;
	vm_offset_t		start, end;
{
	register int		which_cpu, j;
	register pmap_update_list_t	update_list_p;
	register pmap_update_item_t	update_item_p;

	while ((which_cpu = ffs(use_list)) != 0) {
	    which_cpu -= 1;	/* convert to 0 origin */

	    update_list_p = &cpu_update_list[which_cpu];
	    simple_lock(&update_list_p->lock);

	    j = update_list_p->count;
	    if (j >= UPDATE_LIST_SIZE) {
		/*
		 *	list overflowed.  Change last item to
		 *	indicate overflow.
		 */
		update_list_p->item[UPDATE_LIST_SIZE-1].pmap  = kernel_pmap;
		update_list_p->item[UPDATE_LIST_SIZE-1].start = VM_MIN_ADDRESS;
		update_list_p->item[UPDATE_LIST_SIZE-1].end   = VM_MAX_KERNEL_ADDRESS;
	    }
	    else {
		update_item_p = &update_list_p->item[j];
		update_item_p->pmap  = pmap;
		update_item_p->start = start;
		update_item_p->end   = end;

		update_list_p->count = j+1;
	    }
	    cpu_update_needed[which_cpu] = TRUE;
	    simple_unlock(&update_list_p->lock);

	    if ((cpus_idle & (1 << which_cpu)) == 0)
		interrupt_processor(which_cpu);
	    use_list &= ~(1 << which_cpu);
	}
}

void process_pmap_updates(my_pmap)
	register pmap_t		my_pmap;
{
	register int		my_cpu = cpu_number();
	register pmap_update_list_t	update_list_p;
	register int		j;
	register pmap_t		pmap;

	update_list_p = &cpu_update_list[my_cpu];
	simple_lock(&update_list_p->lock);

	for (j = 0; j < update_list_p->count; j++) {
	    pmap = update_list_p->item[j].pmap;
	    if (pmap == my_pmap ||
		pmap == kernel_pmap) {

		INVALIDATE_TLB(update_list_p->item[j].start,
				update_list_p->item[j].end);
	    }
	}
	update_list_p->count = 0;
	cpu_update_needed[my_cpu] = FALSE;
	simple_unlock(&update_list_p->lock);
}

/*
 *	Interrupt routine for TBIA requested from other processor.
 */
void pmap_update_interrupt()
{
	register int		my_cpu;
	register pmap_t		my_pmap;
	int			s;

	my_cpu = cpu_number();

	/*
	 *	Exit now if we're idle.  We'll pick up the update request
	 *	when we go active, and we must not put ourselves back in
	 *	the active set because we'll never process the interrupt
	 *	while we're idle (thus hanging the system).
	 */
	if (cpus_idle & (1 << my_cpu))
	    return;

	if (current_thread() == THREAD_NULL)
	    my_pmap = kernel_pmap;
	else {
	    my_pmap = current_pmap();
	    if (!pmap_in_use(my_pmap, my_cpu))
		my_pmap = kernel_pmap;
	}

	/*
	 *	Raise spl to splvm (above splip) to block out pmap_extract
	 *	from IO code (which would put this cpu back in the active
	 *	set).
	 */
	s = splvm();

	do {

	    /*
	     *	Indicate that we're not using either user or kernel
	     *	pmap.
	     */
	    i_bit_clear(my_cpu, &cpus_active);

	    /*
	     *	Wait for any pmap updates in progress, on either user
	     *	or kernel pmap.
	     */
	    while (my_pmap->lock.lock_data || kernel_pmap->lock.lock_data)
		continue;

	    process_pmap_updates(my_pmap);

	    i_bit_set(my_cpu, &cpus_active);

	    if (my_pmap != kernel_pmap) {
		mtpr(P0BR, my_pmap->p0br);
		mtpr(P0LR, my_pmap->p0lr);
		mtpr(P1BR, my_pmap->p1br);
		mtpr(P1LR, my_pmap->p1lr);
	    }
	} while (cpu_update_needed[my_cpu]);
	
	splx(s);
}
#else	NCPUS > 1
/*
 *	Dummy routine to satisfy external reference.
 */
void pmap_update_interrupt()
{
	/* should never be called. */
}
#endif	NCPUS > 1

/*
 *	pmap_page_protect:
 *
 *	Lower the permission for all mappings to a given page.
 */
void	pmap_page_protect(phys, prot)
	vm_offset_t	phys;
	vm_prot_t	prot;
{
	switch (prot) {
		case VM_PROT_READ:
		case VM_PROT_READ|VM_PROT_EXECUTE:
			pmap_copy_on_write(phys);
			break;
		case VM_PROT_ALL:
			break;
		default:
			pmap_remove_all(phys);
			break;
	}
}

/*
 *	User page table space management.
 */
void user_pt_init()
{
	user_pt_min = kmem_alloc_pageable(kernel_map, user_pt_total_size);
	user_pt_max = user_pt_min + user_pt_total_size;

	user_pt_list.prev = user_pt_list.next = &user_pt_list;
	user_pt_list.end  = user_pt_min;
	user_pt_list.start = user_pt_max;
	user_pt_last_in_use = &user_pt_list;
	user_pt_free_size = user_pt_total_size;
}

/*
 *	Move data by remapping in kernel map.  Assumes that kernel TLB
 *	has already been flushed for old range, and that new range is
 *	unmapped.
 */
void user_pt_move_ptes(old_start, new_start, size)
	register vm_offset_t	old_start;
	vm_offset_t		new_start;
	register vm_size_t	size;
{
	register pt_entry_t	*opte, *npte;
	register int		count;

	if (old_start == new_start)
	    return;

	opte = pmap_syspte(old_start);
	npte = pmap_syspte(new_start);
	count = vax_btop(size);

	simple_lock(&kernel_pmap->lock);
	PMAP_UPDATE_TLBS(kernel_pmap, old_start, old_start + size);

	if (new_start < old_start) {
	    /*
	     *	Moving toward lower addresses.
	     *	Move left-to-right.
	     */

	    while (count > 0) {
		*(int *)npte++ = *(int *)opte;
		*(int *)opte++ = 0;
		count--;
	    }
	}
	else {
	    /*
	     *	Moving toward higher addresses.
	     *	Move right-to-left.
	     */
	    opte += count;
	    npte += count;

	    while (count > 0) {
		*(int *)--npte = *(int *)--opte;
		*(int *)opte = 0;
		count--;
	    }
	}
	simple_unlock(&kernel_pmap->lock);
}

/*
 *	Move a user_pt region to a new location.  The pmaps are moved,
 *	the new sizes entered in the region, and the user_pt free space
 *	updated.  Caller will relink the region in the user_pt_list
 *	if necessary.
 */
void user_pt_move(region, new_start, new_size)
	register pt_region_t	region;
	vm_offset_t		new_start;
	vm_size_t		new_size;
{
	register pmap_t	pmap;
	int		spl;
	vm_offset_t	old_start;
	vm_size_t	old_size;

	old_start = region->start;
	old_size = region->end - old_start;

	region->start = new_start;
	region->end = new_start + new_size;

	user_pt_free_size -= new_size - old_size;

	pmap = region->pmap;

	PMAP_READ_LOCK(pmap, spl);

	if (region == &((a_pmap_t)pmap)->region_0) {
	    /*
	     *	moving region 0
	     */
	    if (old_size != 0) {
		/*
		 *	Invalidate old region in kernel map before we
		 *	move it.  Invalidate region in user map only
		 *	to prevent base and length registers being
		 *	used while the page table is moving, and to
		 *	force the new registers to be loaded (the mapping
		 *	information itself is not changed).
		 */
		PMAP_UPDATE_TLBS(pmap, VM_MIN_ADDRESS, vax_ptob(pmap->p0lr));

		user_pt_move_ptes(old_start, new_start, old_size);
	    }

	    pmap->p0br = (pt_entry_t *)new_start;
	    pmap->p0lr = new_size / sizeof(pt_entry_t);

	    if (current_thread() != THREAD_NULL &&
		current_pmap() == pmap) {
		mtpr(P0BR, pmap->p0br);
		mtpr(P0LR, pmap->p0lr);
	    }
	}
	else {
	    /*
	     *	moving region 1
	     */
	    if (old_size != 0) {
		PMAP_UPDATE_TLBS(pmap, vax_ptob(P0PAGES + pmap->p1lr),
				VM_MAX_ADDRESS);

		user_pt_move_ptes(old_start, region->end - old_size, old_size);
	    }

	    pmap->p1br = (pt_entry_t *)(new_start + new_size
					- P1PAGES * sizeof(pt_entry_t));
	    pmap->p1lr = P1PAGES - (new_size / sizeof(pt_entry_t));

	    if (current_thread() != THREAD_NULL &&
		current_pmap() == pmap) {
		mtpr(P1BR, pmap->p1br);
		mtpr(P1LR, pmap->p1lr);
	    }
	}

	PMAP_READ_UNLOCK(pmap, spl);
}

void user_pt_delete(region)
	register pt_region_t	region;
{
#if	DEBUG_USER_PT
	if (region->next == region)
	    panic("user_pt_delete");
#endif	DEBUG_USER_PT

	if (user_pt_last_in_use->end >= region->start)
	    user_pt_last_in_use = region->prev;
	remque((queue_entry_t)region);
	user_pt_free_size += region->end - region->start;

	/*
	 *	Chain the region to itself so that remque does
	 *	not have to check whether it is on the user_pt_list.
	 */
	region->next = region;
	region->prev = region;
	region->start = 0;
	region->end = 0;
}

/*
 *	Finds a free area of size 'length' in the user_pt map.
 *	Allocates it for 'region' if found.  Skips over 'region'
 *	so that its existing area can be reallocated.
 *
 *	Assumes that region is already in the user_pt_list.
 */
boolean_t user_pt_find(region, size)
	register pt_region_t	region;
	register vm_size_t	size;
{
	register pt_region_t	entry, next;

	entry = user_pt_last_in_use;
	if (entry == region)
	    entry = entry->prev;

	while (TRUE) {
	    next = entry->next;
	    if (next == region)
		next = next->next;
	    if (next->start - entry->end >= size)
		break;
	    entry = next;
	    if (entry == &user_pt_list)
		return (FALSE);	/* no space */
	}

	/*
	 *	Remove region from its current spot...
	 */
	remque((queue_entry_t)region);

	/*
	 *	Move any contained mappings to the new spot...
	 */
	user_pt_move(region,
		     entry->end,
		     size);

	/*
	 *	and insert it after entry.
	 */
	insque((queue_entry_t)region, (queue_entry_t)entry);

	if (user_pt_last_in_use == entry)
	    user_pt_last_in_use = region;

	return(TRUE);
}

/*
 *	Recycle enough pt_regions to allocate space for a new region.
 *	Marked_region is the region to be reallocated; skip over it
 *	when recycling entries.
 */
void user_pt_collect(marked_region, new_size)
	pt_region_t	marked_region;
	vm_size_t	new_size;
{
	register pt_region_t	entry;
	pt_region_t		first_entry, next_entry;
	int		spl;

	PMAP_WRITE_LOCK(spl);

	/*
	 *	Find a block of regions with no wired-down mappings
	 *	that will give the needed space when freed.
	 */
	first_entry = PT_REGION_NULL;
	for (entry = user_pt_list.next;
	     entry != &user_pt_list;
	     entry = entry->next) {

	    if (entry->pmap->stats.wired_count) {
		/*
		 *	Cannot recycle this region.
		 */
		first_entry = PT_REGION_NULL;
	    }
	    else {
		if (first_entry == PT_REGION_NULL) {
		    first_entry = entry;
		}
		if (entry->next->start - first_entry->prev->end >= new_size)
		    break;
	    }
	}
	if (first_entry == PT_REGION_NULL) {
	    panic("user_pt_collect");
	}

	next_entry = entry->next;

	/*
	 *	Now free up all of the regions that we found.
	 */
	entry = first_entry;
	while (entry != next_entry) {
	    pmap_t	pmap;
	    register vm_offset_t	va;
	    register pt_entry_t	*spte, *epte, *lpte;
	    pt_region_t	next;

	    if (entry == marked_region) {
		entry = entry->next;
		continue;
	    }

	    pmap = entry->pmap;
	    simple_lock(&pmap->lock);

	    if (entry == &((a_pmap_t)pmap)->region_0) {

		PMAP_UPDATE_TLBS(pmap, VM_MIN_ADDRESS,
				vax_ptob(pmap->p0lr));

		va = (vm_offset_t) 0;
		spte = pmap->p0br;
		epte = spte + pmap->p0lr;

		while (spte < epte) {
		    lpte = (pt_entry_t *)vax_round_page(spte+1);
		    if (lpte > epte)
			lpte = epte;
		    if (pte_page_valid(spte))
			pmap_remove_range(pmap, va, spte, lpte, TRUE);
		    va += vax_ptob(lpte - spte);
		    spte = lpte;
		}
		pmap->p0br = (pt_entry_t *)VM_MIN_KERNEL_ADDRESS;
		pmap->p0lr = 0;
	    }
	    else {
		va = vax_ptob(P0PAGES + pmap->p1lr);
		PMAP_UPDATE_TLBS(pmap, va, VM_MAX_ADDRESS);

		spte = pmap->p1br + pmap->p1lr;
		epte = pmap->p1br + P1PAGES;

		while (spte < epte) {
		    lpte = (pt_entry_t *)vax_round_page(spte+1);
		    if (lpte > epte)
			lpte = epte;
		    if (pte_page_valid(spte))
			pmap_remove_range(pmap, va, spte, lpte, TRUE);
		    va += vax_ptob(lpte - spte);
		    spte = lpte;
		}
		pmap->p1br = (pt_entry_t *)VM_MIN_KERNEL_ADDRESS;
		pmap->p1lr = P1PAGES;

	    }

	    /*
	     *	Reload the base registers if the current thread is
	     *	using the pmap.
	     */
	    if (current_thread() != THREAD_NULL && pmap == current_pmap()) {
		mtpr(P0BR, pmap->p0br);
		mtpr(P0LR, pmap->p0lr);
		mtpr(P1BR, pmap->p1br);
		mtpr(P1LR, pmap->p1lr);
	    }
	    simple_unlock(&pmap->lock);

	    /*
	     *	The kernel mappings for the region have already been freed,
	     *	since all pte pages have been freed.
	     */

	    next = entry->next;
	    user_pt_delete(entry);
	    entry = next;
	}
	PMAP_WRITE_UNLOCK(spl);
}


void user_pt_destroy(region)
	register pt_region_t	region;
{
	user_pt_lock();

	if (region->end - region->start != 0) {
	    /*
	     *	The kernel mappings for the region have already been freed,
	     *	since all pte pages have been freed.  Just delete the region.
	     */
	    user_pt_delete(region);
	}
#if	DEBUG_USER_PT
	user_pt_check("destroy", PT_REGION_NULL);
#endif	DEBUG_USER_PT
	user_pt_unlock();
}


/*
 *	Routine:	user_pt_allocate
 *
 *	Expands a pmap to be able to map the specified virtual address.
 *
 *	Allocates new virtual memory for the P0 or P1 portion of the
 *	pmap, then re-maps the physical pages that were in the old
 *	pmap to be in the new pmap.
 *
 *	Must be called with the pmap system and the pmap unlocked,
 *	since these must be unlocked to use vm_allocate or vm_deallocate.
 *	Thus it must be called in a loop that checks whether the map
 *	has been expanded enough.
 *	(We won't loop forever, since page tables aren't shrunk.)
 */
void user_pt_allocate(pmap, v)
	pmap_t		pmap;
	vm_offset_t	v;
{
	register vm_size_t	new_size, old_size;
	register pt_region_t	region;

	if (pmap == kernel_pmap)
		panic("kernel pmap too small");

	user_pt_lock();

	if (vax_p0(v)) {
	    /*
	     *	Find a new P0 region large enough to map v
	     */
	    register vm_size_t ptsize;

	    ptsize = vax_btop(v + PAGE_SIZE);
	    new_size = round_pte_page(ptsize * sizeof(pt_entry_t));

	    region = &((a_pmap_t)pmap)->region_0;
	}
	else {
	    /*
	     *	Same for P1
	     */
	    register vm_size_t ptsize;

	    ptsize = vax_btop(VM_MAX_ADDRESS - v);
	    new_size = round_pte_page(ptsize * sizeof(pt_entry_t));

	    region = &((a_pmap_t)pmap)->region_1;
	}

	old_size = region->end - region->start;
	if (old_size != 0) {
	    /*
	     *	Region exists.  First see whether it can be extended.
	     */
	    if (vax_p0(v)) {
		if (region->next->start - region->start >= new_size) {
		    /*
		     *	Extend toward higher addresses.  No need
		     *	to lock pmap, since no existing data changes.
		     */
		    user_pt_free_size -= new_size - old_size;
		    region->end = region->start + new_size;
		    pmap->p0lr = new_size / sizeof(pt_entry_t);
		    if (current_thread() != THREAD_NULL &&
			current_pmap() == pmap)
			mtpr(P0LR, pmap->p0lr);
#if	DEBUG_USER_PT
		    user_pt_check("extend P0", PT_REGION_NULL);
#endif	DEBUG_USER_PT
		    user_pt_unlock();
		    return;
		}
	    }
	    else {
		if (region->end - region->prev->end >= new_size) {
		    /*
		     *	Extend toward lower addresses.  No need
		     *	to lock pmap, since no existing data changes.
		     */
		    user_pt_free_size -= new_size - old_size;
		    region->start = region->end - new_size;
		    pmap->p1lr = P1PAGES - (new_size / sizeof(pt_entry_t));
		    if (current_thread() != THREAD_NULL &&
			current_pmap() == pmap)
			mtpr(P1LR, pmap->p1lr);
#if	DEBUG_USER_PT
		    user_pt_check("extend P1", PT_REGION_NULL);
#endif	DEBUG_USER_PT
		    user_pt_unlock();
		    return;
		}
	    }
	}

	else {
	    /*
	     *	If region is not allocated, link it into the top
	     *	of the region list, with no space allocated,
	     *	to simplify the rest of the code.
	     */
	    enqueue_tail((queue_t)&user_pt_list, (queue_entry_t)region);
	    region->start = region->end = user_pt_max;
	}

	if (user_pt_free_size >= new_size) {
	    /*
	     *	Can allocate region without collecting other regions.
	     */

	    /*
	     *	See if there is enough room to move region
	     */
	    if (region->next->start - region->prev->end >= new_size) {
		user_pt_move(region,
			     region->prev->end,
			     new_size);

#if	DEBUG_USER_PT
		user_pt_check("extend into free space", PT_REGION_NULL);
#endif	DEBUG_USER_PT
		user_pt_unlock();
		return;
	    }

	    /*
	     *	Look for a free area in the user page table.
	     */
	    if (user_pt_find(region, new_size)) {
		/*
		 *	Found one; region has been moved here.
		 */
#if	DEBUG_USER_PT
		user_pt_check("find new region", PT_REGION_NULL);
#endif	DEBUG_USER_PT
		user_pt_unlock();
		return;
	    }

	    /*
	     *	Compress regions between start and current region
	     *	toward bottom of space.
	     */
	    {
		register pt_region_t	entry;

		for (entry = user_pt_list.next;
		     entry != region;
		     entry = entry->next) {
		    user_pt_move(entry,
				 entry->prev->end,
				 entry->end - entry->start);
		}
#if	DEBUG_USER_PT
		user_pt_check("compress to bottom", region);
#endif	DEBUG_USER_PT
	    }

	    /*
	     *	See if there is enough room to move region
	     */
	    if (region->next->start - region->prev->end >= new_size) {
		user_pt_move(region,
			     region->prev->end,
			     new_size);
#if	DEBUG_USER_PT
		user_pt_check("move after compress to bottom", PT_REGION_NULL);
#endif	DEBUG_USER_PT
		user_pt_unlock();
		return;
	    }

	    /*
	     *	Compress regions between current region and end
	     *	toward top of space.
	     */
	    {
		register pt_region_t	entry;
		register vm_size_t	cur_size;

		for (entry = user_pt_list.prev;
		     entry != region;
		     entry = entry->prev) {
		    cur_size = entry->end - entry->start;
		    user_pt_move(entry,
				 entry->next->start - cur_size,
				 cur_size);
		}
#if	DEBUG_USER_PT
		user_pt_check("compress to top", region);
#endif	DEBUG_USER_PT
	    }

	    /*
	     *	See if there is enough room to move region
	     */
	    if (region->next->start - region->prev->end >= new_size) {
		user_pt_move(region,
			     region->prev->end,
			     new_size);
#if	DEBUG_USER_PT
		user_pt_check("move after compress to top", PT_REGION_NULL);
#endif	DEBUG_USER_PT
		user_pt_unlock();
		return;
	    }
	}

	/*
	 *	Not enough room even when compressing entries.
	 *	Remove some, marking the current entry so that
	 *	it is not collected but its space can count toward
	 *	free space.
	 */
	user_pt_collect(region, new_size);
#if	DEBUG_USER_PT
	user_pt_check("after collect", region);
#endif	DEBUG_USER_PT

	/*
	 *	Look for a free area in the user page table.
	 */
	if (user_pt_find(region, new_size)) {
	    /*
	     *	Found one; region has been moved here.
	     */
#if	DEBUG_USER_PT
	    user_pt_check("find after collect", PT_REGION_NULL);
#endif	DEBUG_USER_PT
	    user_pt_unlock();
	    return;
	}

	/*
	 *	All out!
	 */
	panic("user_pt_allocate");
}

#if	DEBUG_USER_PT
user_pt_check(msg, exempt_region)
	char	*msg;
	register pt_region_t	exempt_region;
{
	register pt_region_t	entry;
	register vm_size_t	used = 0;
	register pt_entry_t	*spte, *epte;
	register boolean_t	found_last_in_use = FALSE;

	if (user_pt_last_in_use == &user_pt_list)
	    found_last_in_use = TRUE;

	for (entry = user_pt_list.next;
	     entry != &user_pt_list;
	     entry = entry->next) {
	    if (entry->prev->next != entry ||
		entry->end < entry->start ||
		entry->prev->end > entry->start ||
		entry->end > entry->next->start) {
		printf("%s\n", msg);
		panic("user_pt_check: entries out of order");
		}
	    if (entry != exempt_region && entry->end == entry->start) {
		printf("%s\n", msg);
		panic("user_pt_check: zero-length region:");
	    }
	    used += entry->end - entry->start;
	    spte = pmap_syspte(entry->prev->end);
	    epte = pmap_syspte(entry->start);
	    for (;spte < epte; spte++) {
		if (*(int *)spte != 0) {
		    printf("%s\n", msg);
		    panic("user_pt_check: unallocated region in use");
		}
	    }
	    if (user_pt_last_in_use == entry)
		found_last_in_use = TRUE;
	}
	if (!found_last_in_use) {
	    panic("user_pt_check: last_in_use not in list");
	}
	if (user_pt_free_size + used != user_pt_total_size) {
	    printf("%s\n", msg);
	    panic("user_pt_check: free size mismatch");
	}
}
#endif	DEBUG_USER_PT
