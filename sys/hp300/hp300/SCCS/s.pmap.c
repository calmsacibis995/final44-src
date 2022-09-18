h21639
s 00016/00000/02496
d D 8.7 95/05/17 00:09:00 mckusick 26 25
c avoid simple_lock deadlocks with machine independent VM code (from hibler)
e
s 00001/00001/02495
d D 8.6 94/05/27 09:12:14 hibler 25 24
c improper parameter to pmap_changebit (should be PA not VA)
c (from holmgren@tenon.com)
e
s 00014/00007/02482
d D 8.5 94/03/21 16:32:20 hibler 24 23
c allocate segment tables out of a private submap that doesn't
c require pre-allocated kernel map entries
e
s 00032/00012/02457
d D 8.4 94/01/12 14:38:26 hibler 23 22
c dubious change to not remove wired mappings in pmap_protect_page.
c (can lead to mappings that cannot be removed as opposed to removing wired
c mappings that shouldn't be removed)
e
s 00004/00003/02465
d D 8.3 94/01/04 22:25:44 bostic 22 21
c lint, KNF
e
s 00001/00001/02467
d D 8.2 93/11/14 14:20:28 hibler 21 20
c use faster copypage primative in pmap_copy_page
e
s 00002/00002/02466
d D 8.1 93/06/10 21:41:20 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00009/02457
d D 7.16 93/05/20 08:07:27 hibler 19 18
c make sure PT page is marked clean at allocation to avoid pageout
e
s 00615/00498/01851
d D 7.15 92/12/27 09:52:47 hibler 18 17
c massive changes mostly performance related
e
s 00010/00010/02339
d D 7.14 92/10/11 09:42:43 bostic 17 16
c make kernel includes standard
e
s 00001/00001/02348
d D 7.13 92/10/01 17:50:40 mckusick 16 15
c convert vm_page bit fields to flags
e
s 00006/00003/02343
d D 7.12 92/08/03 13:57:15 hibler 15 14
c fixup a comment
e
s 00001/00001/02345
d D 7.11 92/07/12 22:37:57 mckusick 14 13
c lint
e
s 00001/00000/02345
d D 7.10 92/07/12 17:49:24 pendry 13 12
c needs to include "systm.h"
e
s 00424/00225/01921
d D 7.9 92/06/05 15:36:42 hibler 12 11
c merge latest Utah hp300 code including 68040 support
e
s 00000/00008/02146
d D 7.8 92/02/19 18:40:10 mckusick 11 10
c eliminate variable kernel_pmap and function pmap_kernel
e
s 00003/00000/02151
d D 7.7 91/09/12 16:37:37 marc 10 9
c need void declarations to be consistant with prototypes
e
s 00030/00001/02121
d D 7.6 91/08/29 16:30:40 william 9 8
c added pmap_bootstrap_alloc(), the "before malloc" allocator.
e
s 00003/00004/02119
d D 7.5 91/05/10 10:17:34 mckusick 8 4
c correct copyright, Utah not CMU
e
s 00003/00003/02147
d R 7.7 91/05/09 23:14:59 bostic 7 6
c get the copyright right
e
s 00032/00004/02118
d R 7.6 91/05/09 22:24:42 bostic 6 5
c get the copyright notice right
e
s 00003/00004/02119
d R 7.5 91/05/08 13:59:25 bostic 5 4
c new copyright; att/bsd/shared
e
s 00050/00055/02073
d D 7.4 91/05/07 09:55:38 hibler 4 3
c DIO-II support
c pmap_remove_all and pmap_copy_on_write become pmap_page_protect
c pmap_kernel a macro
c kludge for "proper" pager support
e
s 00003/00002/02125
d D 7.3 91/05/04 19:27:20 karels 3 2
c u => kstack
e
s 00089/00055/02038
d D 7.2 91/04/20 16:57:45 karels 2 1
c fix includes; rm *_NULL; nproc => maxproc; break pmap_pinit out of pmap_init
c (init without alloc); pmap_release broken out of pmap_destry; new proc struct
e
s 02093/00000/00000
d D 7.1 90/12/05 19:26:04 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 8
 * Copyright (c) 1987 Carnegie-Mellon University
E 8
D 20
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * This code is derived from software contributed to Berkeley by
D 8
 * The Mach Operating System project at Carnegie-Mellon University.
E 8
I 8
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
E 8
 *
D 8
 * The CMU software License Agreement specifies the terms and conditions
 * for use and redistribution.
E 8
I 8
 * %sccs.include.redist.c%
E 8
 *
 *	%W% (Berkeley) %G%
 */

/*
D 18
 *	HP9000/300 series physical map management code.
D 15
 *	For 68020/68030 machines with HP, 68551, or 68030 MMUs
 *		(models 320,350,318,319,330,340,360,370,345,375)
E 15
I 15
 *	Supports:
 *		68020 with HP MMU	models 320, 350
 *		68020 with 68551 MMU	models 318, 319, 330 (all untested)
 *		68030 with on-chip MMU	models 340, 360, 370, 345, 375, 400
 *		68040 with on-chip MMU	models 380, 425, 433
E 18
I 18
 * HP9000/300 series physical map management code.
 *
 * Supports:
 *	68020 with HP MMU	models 320, 350
 *	68020 with 68551 MMU	models 318, 319, 330 (all untested)
 *	68030 with on-chip MMU	models 340, 360, 370, 345, 375, 400
 *	68040 with on-chip MMU	models 380, 425, 433
 *
 * Notes:
E 18
E 15
 *	Don't even pay lip service to multiprocessor support.
I 4
 *
D 12
 *	XXX will only work for PAGE_SIZE == NBPG (hppagesperpage == 1)
 *	right now because of the assumed one-to-one relationship of PT
 *	pages to STEs.
E 12
I 12
D 18
 *	XXX will only work for PAGE_SIZE == NBPG (i.e. 4096 bytes).
D 15
 *	Hence, there is no point in defining DYNPGSIZE.
E 15
I 15
 *	Hence, there is no point in defining DYNPGSIZE as it stands now.
E 18
I 18
 *	We assume TLB entries don't have process tags (except for the
 *	supervisor/user distinction) so we only invalidate TLB entries
 *	when changing mappings for the current (or kernel) pmap.  This is
 *	technically not true for the 68551 but we flush the TLB on every
 *	context switch, so it effectively winds up that way.
 *
 *	Bitwise and/or operations are significantly faster than bitfield
 *	references so we use them when accessing STE/PTEs in the pmap_pte_*
 *	macros.  Note also that the two are not always equivalent; e.g.:
 *		(*(int *)pte & PG_PROT) [4] != pte->pg_prot [1]
 *	and a couple of routines that deal with protection and wiring take
 *	some shortcuts that assume the and/or definitions.
 *
 *	This implementation will only work for PAGE_SIZE == NBPG
 *	(i.e. 4096 bytes).
E 18
E 15
E 12
E 4
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

D 17
#include "param.h"
I 13
#include "systm.h"
E 13
D 2
#include "../vm/vm_param.h"
#include "user.h"
E 2
#include "proc.h"
D 2
#include "lock.h"
E 2
#include "malloc.h"
I 2
#include "user.h"
E 17
I 17
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/malloc.h>
#include <sys/user.h>
E 17
E 2

D 2
#include "../vm/pmap.h"
#include "../vm/vm_map.h"
#include "../vm/vm_kern.h"
#include "../vm/vm_prot.h"
#include "../vm/vm_page.h"
E 2
I 2
D 17
#include "pte.h"
E 17
I 17
#include <hp300/hp300/pte.h>
E 17
E 2

D 2
#include "machine/cpu.h"
E 2
I 2
D 17
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
E 17
I 17
#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
E 17
D 9
#include "vm/vm_statistics.h"
E 9
E 2

I 2
D 17
#include "../include/cpu.h"
E 17
I 17
#include <machine/cpu.h>
E 17

E 2
D 12
/*
 * Allocate various and sundry SYSMAPs used in the days of old VM
 * and not yet converted.  XXX.
 */
#define BSDVM_COMPAT	1

E 12
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
struct {
	int collectscans;
	int collectpages;
	int kpttotal;
	int kptinuse;
	int kptmaxuse;
} kpt_stats;
struct {
	int kernel;	/* entering kernel mapping */
	int user;	/* entering user mapping */
	int ptpneeded;	/* needed to allocate a PT page */
I 18
	int nochange;	/* no change at all */
E 18
	int pwchange;	/* no mapping change, just wiring or protection */
	int wchange;	/* no mapping change, just wiring */
I 18
	int pchange;	/* no mapping change, just protection */
E 18
	int mchange;	/* was mapped but mapping to different page */
	int managed;	/* a managed page */
	int firstpv;	/* first mapping for this PA */
	int secondpv;	/* second mapping for this PA */
	int ci;		/* cache inhibited */
	int unmanaged;	/* not a managed page */
	int flushes;	/* cache flushes */
} enter_stats;
struct {
	int calls;
	int removes;
	int pvfirst;
	int pvsearch;
	int ptinvalid;
	int uflushes;
	int sflushes;
} remove_stats;
I 12
struct {
	int calls;
D 18
	int pages;
E 18
I 18
	int changed;
E 18
	int alreadyro;
	int alreadyrw;
} protect_stats;
I 18
struct chgstats {
	int setcalls;
	int sethits;
	int setmiss;
	int clrcalls;
	int clrhits;
	int clrmiss;
} changebit_stats[16];
#endif
E 18
E 12

I 18
#ifdef DEBUG
E 18
int debugmap = 0;
int pmapdebug = 0x2000;
#define PDB_FOLLOW	0x0001
#define PDB_INIT	0x0002
#define PDB_ENTER	0x0004
#define PDB_REMOVE	0x0008
#define PDB_CREATE	0x0010
#define PDB_PTPAGE	0x0020
#define PDB_CACHE	0x0040
#define PDB_BITS	0x0080
#define PDB_COLLECT	0x0100
#define PDB_PROTECT	0x0200
#define PDB_SEGTAB	0x0400
I 18
#define PDB_MULTIMAP	0x0800
E 18
#define PDB_PARANOIA	0x2000
#define PDB_WIRING	0x4000
#define PDB_PVDUMP	0x8000

I 18
#ifdef HAVEVAC
E 18
int pmapvacflush = 0;
#define	PVF_ENTER	0x01
#define	PVF_REMOVE	0x02
#define	PVF_PROTECT	0x04
#define	PVF_TOTAL	0x80
I 18
#endif
E 18
I 4

I 12
#if defined(HP380)
int dowriteback = 1;	/* 68040: enable writeback caching */
int dokwriteback = 1;	/* 68040: enable writeback caching of kernel AS */
#endif

E 12
extern vm_offset_t pager_sva, pager_eva;
E 4
#endif

/*
 * Get STEs and PTEs for user/kernel address space
 */
I 12
#if defined(HP380)
D 18
#define	pmap_ste(m, v)	\
	(&((m)->pm_stab[(vm_offset_t)(v) \
			>> (mmutype == MMU_68040 ? SG4_SHIFT1 : SG_ISHIFT)]))
E 18
#define	pmap_ste1(m, v)	\
	(&((m)->pm_stab[(vm_offset_t)(v) >> SG4_SHIFT1]))
/* XXX assumes physically contiguous ST pages (if more than one) */
#define pmap_ste2(m, v) \
	(&((m)->pm_stab[(st_entry_t *)(*(u_int *)pmap_ste1(m, v) & SG4_ADDR1) \
			- (m)->pm_stpa + (((v) & SG4_MASK2) >> SG4_SHIFT2)]))
D 18
#else
E 12
#define	pmap_ste(m, v)	(&((m)->pm_stab[(vm_offset_t)(v) >> SG_ISHIFT]))
I 12
#endif
E 12
#define pmap_pte(m, v)	(&((m)->pm_ptab[(vm_offset_t)(v) >> PG_SHIFT]))

D 12
#define pmap_pte_pa(pte)	(*(int *)(pte) & PG_FRAME)
E 12
I 12
#if defined(HP380)
E 18
I 18
#define	pmap_ste(m, v)	\
	(&((m)->pm_stab[(vm_offset_t)(v) \
			>> (mmutype == MMU_68040 ? SG4_SHIFT1 : SG_ISHIFT)]))
E 18
#define pmap_ste_v(m, v) \
	(mmutype == MMU_68040 \
D 18
	 ? (pmap_ste1(m, v)->sg_v && pmap_ste2(m, v)->sg_v) \
	 : (pmap_ste(m, v)->sg_v))
E 18
I 18
	 ? ((*(int *)pmap_ste1(m, v) & SG_V) && \
	    (*(int *)pmap_ste2(m, v) & SG_V)) \
	 : (*(int *)pmap_ste(m, v) & SG_V))
E 18
#else
D 18
#define pmap_ste_v(m, v)	(pmap_ste(m, v)->sg_v)
E 18
I 18
#define	pmap_ste(m, v)	 (&((m)->pm_stab[(vm_offset_t)(v) >> SG_ISHIFT]))
#define pmap_ste_v(m, v) (*(int *)pmap_ste(m, v) & SG_V)
E 18
#endif
E 12

I 18
#define pmap_pte(m, v)	(&((m)->pm_ptab[(vm_offset_t)(v) >> PG_SHIFT]))
E 18
D 12
#define pmap_ste_v(pte)		((pte)->sg_v)
E 12
I 12
#define pmap_pte_pa(pte)	(*(int *)(pte) & PG_FRAME)
E 12
D 18
#define pmap_pte_w(pte)		((pte)->pg_w)
#define pmap_pte_ci(pte)	((pte)->pg_ci)
#define pmap_pte_m(pte)		((pte)->pg_m)
#define pmap_pte_u(pte)		((pte)->pg_u)
I 12
#define pmap_pte_prot(pte)	((pte)->pg_prot)
E 12
#define pmap_pte_v(pte)		((pte)->pg_v)
#define pmap_pte_set_w(pte, v)		((pte)->pg_w = (v))
#define pmap_pte_set_prot(pte, v)	((pte)->pg_prot = (v))
E 18
I 18
#define pmap_pte_w(pte)		(*(int *)(pte) & PG_W)
#define pmap_pte_ci(pte)	(*(int *)(pte) & PG_CI)
#define pmap_pte_m(pte)		(*(int *)(pte) & PG_M)
#define pmap_pte_u(pte)		(*(int *)(pte) & PG_U)
#define pmap_pte_prot(pte)	(*(int *)(pte) & PG_PROT)
#define pmap_pte_v(pte)		(*(int *)(pte) & PG_V)
E 18

I 18
#define pmap_pte_set_w(pte, v) \
	if (v) *(int *)(pte) |= PG_W; else *(int *)(pte) &= ~PG_W
#define pmap_pte_set_prot(pte, v) \
	if (v) *(int *)(pte) |= PG_PROT; else *(int *)(pte) &= ~PG_PROT
#define pmap_pte_w_chg(pte, nw)		((nw) ^ pmap_pte_w(pte))
#define pmap_pte_prot_chg(pte, np)	((np) ^ pmap_pte_prot(pte))

E 18
/*
 * Given a map and a machine independent protection code,
D 18
 * convert to a vax protection code.
E 18
I 18
 * convert to an hp300 protection code.
E 18
 */
#define pte_prot(m, p)	(protection_codes[p])
int	protection_codes[8];

/*
 * Kernel page table page management.
 */
struct kpt_page {
	struct kpt_page *kpt_next;	/* link on either used or free list */
	vm_offset_t	kpt_va;		/* always valid kernel VA */
	vm_offset_t	kpt_pa;		/* PA of this page (for speed) */
};
struct kpt_page *kpt_free_list, *kpt_used_list;
struct kpt_page *kpt_pages;

/*
 * Kernel segment/page table and page table map.
 * The page table map gives us a level of indirection we need to dynamically
 * expand the page table.  It is essentially a copy of the segment table
 * with PTEs instead of STEs.  All are initialized in locore at boot time.
 * Sysmap will initially contain VM_KERNEL_PT_PAGES pages of PTEs.
 * Segtabzero is an empty segment table which all processes share til they
 * reference something.
 */
st_entry_t	*Sysseg;
pt_entry_t	*Sysmap, *Sysptmap;
D 12
st_entry_t	*Segtabzero;
#if BSDVM_COMPAT
vm_size_t	Sysptsize = VM_KERNEL_PT_PAGES + 4 / NPTEPG;
#else
E 12
I 12
st_entry_t	*Segtabzero, *Segtabzeropa;
E 12
vm_size_t	Sysptsize = VM_KERNEL_PT_PAGES;
D 12
#endif
E 12

struct pmap	kernel_pmap_store;
D 11
pmap_t		kernel_pmap;
E 11
D 24
vm_map_t	pt_map;
E 24
I 24
vm_map_t	st_map, pt_map;
E 24

vm_offset_t    	avail_start;	/* PA of first available physical page */
vm_offset_t	avail_end;	/* PA of last available physical page */
vm_size_t	mem_size;	/* memory size in bytes */
vm_offset_t	virtual_avail;  /* VA of first avail page (after kernel bss)*/
vm_offset_t	virtual_end;	/* VA of last avail page (end of kernel AS) */
vm_offset_t	vm_first_phys;	/* PA of first managed page */
vm_offset_t	vm_last_phys;	/* PA just past last managed page */
I 12
D 18
#if defined(DYNPGSIZE)
E 12
int		hppagesperpage;	/* PAGE_SIZE / HP_PAGE_SIZE */
I 12
#endif
E 18
E 12
boolean_t	pmap_initialized = FALSE;	/* Has pmap_init completed? */
D 18
int		pmap_aliasmask;	/* seperation at which VA aliasing ok */
E 18
char		*pmap_attributes;	/* reference and modify bits */
I 18
#ifdef HAVEVAC
int		pmap_aliasmask;	/* seperation at which VA aliasing ok */
#endif
E 18
I 12
#if defined(HP380)
D 18
int		protostfree;
E 18
I 18
int		protostfree;	/* prototype (default) free ST map */
E 18
#endif
E 12

D 18
boolean_t	pmap_testbit();
void		pmap_enter_ptpage();
E 18
I 18
/*
 * Internal routines
 */
void pmap_remove_mapping __P((pmap_t, vm_offset_t, pt_entry_t *, int));
boolean_t pmap_testbit	__P((vm_offset_t, int));
void pmap_changebit	__P((vm_offset_t, int, boolean_t));
void pmap_enter_ptpage	__P((pmap_t, vm_offset_t));
#ifdef DEBUG
void pmap_pvdump	__P((vm_offset_t));
void pmap_check_wiring	__P((char *, vm_offset_t));
#endif
E 18

I 18
/* pmap_remove_mapping flags */
#define	PRM_TFLUSH	1
#define	PRM_CFLUSH	2

E 18
D 12
#if BSDVM_COMPAT
#include "msgbuf.h"

E 12
/*
D 12
 * All those kernel PT submaps that BSD is so fond of
 */
struct pte	*CMAP1, *CMAP2, *mmap;
caddr_t		CADDR1, CADDR2, vmmap;
struct pte	*msgbufmap;
struct msgbuf	*msgbufp;
#endif

/*
 *	Bootstrap the system enough to run with virtual memory.
 *	Map the kernel's code and data, and allocate the system page table.
 *
 *	On the HP this is called after mapping has already been enabled
 *	and just syncs the pmap module with what has already been done.
 *	[We can't call it easily with mapping off since the kernel is not
 *	mapped with PA == VA, hence we would have to relocate every address
 *	from the linked base (virtual) address 0 to the actual (physical)
 *	address of 0xFFxxxxxx.]
 */
void
pmap_bootstrap(firstaddr, loadaddr)
	vm_offset_t firstaddr;
	vm_offset_t loadaddr;
{
#if BSDVM_COMPAT
	vm_offset_t va;
	struct pte *pte;
#endif
	extern vm_offset_t maxmem, physmem;

	avail_start = firstaddr;
	avail_end = maxmem << PGSHIFT;

	/* XXX: allow for msgbuf */
	avail_end -= hp300_round_page(sizeof(struct msgbuf));

	mem_size = physmem << PGSHIFT;
	virtual_avail = VM_MIN_KERNEL_ADDRESS + (firstaddr - loadaddr);
	virtual_end = VM_MAX_KERNEL_ADDRESS;
	hppagesperpage = PAGE_SIZE / HP_PAGE_SIZE;

	/*
	 * Determine VA aliasing distance if any
	 */
	if (ectype == EC_VIRT)
		switch (machineid) {
		case HP_320:
			pmap_aliasmask = 0x3fff;	/* 16k */
			break;
		case HP_350:
			pmap_aliasmask = 0x7fff;	/* 32k */
			break;
		}

	/*
	 * Initialize protection array.
	 */
	hp300_protection_init();
D 11

	/*
	 * The kernel's pmap is statically allocated so we don't
	 * have to use pmap_create, which is unlikely to work
	 * correctly at this part of the boot sequence.
	 */
	kernel_pmap = &kernel_pmap_store;
E 11

	/*
	 * Kernel page/segment table allocated in locore,
	 * just initialize pointers.
	 */
	kernel_pmap->pm_stab = Sysseg;
	kernel_pmap->pm_ptab = Sysmap;

	simple_lock_init(&kernel_pmap->pm_lock);
	kernel_pmap->pm_count = 1;

#if BSDVM_COMPAT
	/*
	 * Allocate all the submaps we need
	 */
#define	SYSMAP(c, p, v, n)	\
	v = (c)va; va += ((n)*HP_PAGE_SIZE); p = pte; pte += (n);

	va = virtual_avail;
	pte = pmap_pte(kernel_pmap, va);

	SYSMAP(caddr_t		,CMAP1		,CADDR1	   ,1		)
	SYSMAP(caddr_t		,CMAP2		,CADDR2	   ,1		)
	SYSMAP(caddr_t		,mmap		,vmmap	   ,1		)
	SYSMAP(struct msgbuf *	,msgbufmap	,msgbufp   ,1		)
	virtual_avail = va;
#endif
I 9
}

/*
E 12
 * Bootstrap memory allocator. This function allows for early dynamic
 * memory allocation until the virtual memory system has been bootstrapped.
 * After that point, either kmem_alloc or malloc should be used. This
 * function works by stealing pages from the (to be) managed page pool,
 * stealing virtual address space, then mapping the pages and zeroing them.
 *
 * It should be used from pmap_bootstrap till vm_page_startup, afterwards
 * it cannot be used, and will generate a panic if tried. Note that this
 * memory will never be freed, and in essence it is wired down.
 */
void *
D 22
pmap_bootstrap_alloc(size) {
	vm_offset_t val;
	int i;
E 22
I 22
pmap_bootstrap_alloc(size)
	int size;
{
E 22
	extern boolean_t vm_page_startup_initialized;
I 22
	vm_offset_t val;
E 22
	
	if (vm_page_startup_initialized)
		panic("pmap_bootstrap_alloc: called after startup initialized");
	size = round_page(size);
	val = virtual_avail;

	virtual_avail = pmap_map(virtual_avail, avail_start,
		avail_start + size, VM_PROT_READ|VM_PROT_WRITE);
	avail_start += size;

	blkclr ((caddr_t) val, size);
	return ((void *) val);
E 9
}

/*
 *	Initialize the pmap module.
 *	Called by vm_init, to initialize any structures that the pmap
 *	system needs to map virtual memory.
 */
void
pmap_init(phys_start, phys_end)
	vm_offset_t	phys_start, phys_end;
{
	vm_offset_t	addr, addr2;
	vm_size_t	npg, s;
	int		rv;
D 4
	extern vm_offset_t	DIObase;
E 4
I 3
	extern char kstack[];
E 3

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_init(%x, %x)\n", phys_start, phys_end);
#endif
	/*
	 * Now that kernel map has been allocated, we can mark as
	 * unavailable regions which we have mapped in locore.
	 */
D 4
	addr = DIObase;
E 4
I 4
	addr = (vm_offset_t) intiobase;
E 4
D 2
	(void) vm_map_find(kernel_map, VM_OBJECT_NULL, (vm_offset_t) 0,
E 2
I 2
	(void) vm_map_find(kernel_map, NULL, (vm_offset_t) 0,
E 2
D 4
			   &addr, hp300_ptob(IOMAPSIZE), FALSE);
	if (addr != DIObase)
E 4
I 4
			   &addr, hp300_ptob(IIOMAPSIZE+EIOMAPSIZE), FALSE);
	if (addr != (vm_offset_t)intiobase)
E 4
		goto bogons;
	addr = (vm_offset_t) Sysmap;
	vm_object_reference(kernel_object);
	(void) vm_map_find(kernel_map, kernel_object, addr,
			   &addr, HP_MAX_PTSIZE, FALSE);
	/*
	 * If this fails it is probably because the static portion of
	 * the kernel page table isn't big enough and we overran the
	 * page table map.   Need to adjust pmap_size() in hp300_init.c.
	 */
	if (addr != (vm_offset_t)Sysmap)
		goto bogons;

D 3
	addr = (vm_offset_t) &u;
E 3
I 3
	addr = (vm_offset_t) kstack;
E 3
	vm_object_reference(kernel_object);
	(void) vm_map_find(kernel_map, kernel_object, addr,
			   &addr, hp300_ptob(UPAGES), FALSE);
D 3
	if (addr != (vm_offset_t)&u)
E 3
I 3
	if (addr != (vm_offset_t)kstack)
E 3
bogons:
		panic("pmap_init: bogons in the VM system!\n");

#ifdef DEBUG
	if (pmapdebug & PDB_INIT) {
		printf("pmap_init: Sysseg %x, Sysmap %x, Sysptmap %x\n",
		       Sysseg, Sysmap, Sysptmap);
		printf("  pstart %x, pend %x, vstart %x, vend %x\n",
		       avail_start, avail_end, virtual_avail, virtual_end);
	}
#endif

	/*
	 * Allocate memory for random pmap data structures.  Includes the
	 * initial segment table, pv_head_table and pmap_attributes.
	 */
	npg = atop(phys_end - phys_start);
	s = (vm_size_t) (HP_STSIZE + sizeof(struct pv_entry) * npg + npg);
	s = round_page(s);
	addr = (vm_offset_t) kmem_alloc(kernel_map, s);
	Segtabzero = (st_entry_t *) addr;
I 12
	Segtabzeropa = (st_entry_t *) pmap_extract(kernel_pmap, addr);
E 12
	addr += HP_STSIZE;
	pv_table = (pv_entry_t) addr;
	addr += sizeof(struct pv_entry) * npg;
	pmap_attributes = (char *) addr;
#ifdef DEBUG
	if (pmapdebug & PDB_INIT)
D 12
		printf("pmap_init: %x bytes (%x pgs): seg %x tbl %x attr %x\n",
		       s, npg, Segtabzero, pv_table, pmap_attributes);
E 12
I 12
		printf("pmap_init: %x bytes: npg %x s0 %x(%x) tbl %x atr %x\n",
		       s, npg, Segtabzero, Segtabzeropa,
		       pv_table, pmap_attributes);
E 12
#endif

	/*
	 * Allocate physical memory for kernel PT pages and their management.
	 * We need 1 PT page per possible task plus some slop.
	 */
D 2
	npg = min(atop(HP_MAX_KPTSIZE), nproc+16);
E 2
I 2
	npg = min(atop(HP_MAX_KPTSIZE), maxproc+16);
E 2
	s = ptoa(npg) + round_page(npg * sizeof(struct kpt_page));

	/*
	 * Verify that space will be allocated in region for which
	 * we already have kernel PT pages.
	 */
	addr = 0;
D 2
	rv = vm_map_find(kernel_map, VM_OBJECT_NULL, 0, &addr, s, TRUE);
E 2
I 2
	rv = vm_map_find(kernel_map, NULL, 0, &addr, s, TRUE);
E 2
	if (rv != KERN_SUCCESS || addr + s >= (vm_offset_t)Sysmap)
		panic("pmap_init: kernel PT too small");
	vm_map_remove(kernel_map, addr, addr + s);

	/*
	 * Now allocate the space and link the pages together to
	 * form the KPT free list.
	 */
	addr = (vm_offset_t) kmem_alloc(kernel_map, s);
	s = ptoa(npg);
	addr2 = addr + s;
	kpt_pages = &((struct kpt_page *)addr2)[npg];
	kpt_free_list = (struct kpt_page *) 0;
	do {
		addr2 -= HP_PAGE_SIZE;
		(--kpt_pages)->kpt_next = kpt_free_list;
		kpt_free_list = kpt_pages;
		kpt_pages->kpt_va = addr2;
		kpt_pages->kpt_pa = pmap_extract(kernel_pmap, addr2);
	} while (addr != addr2);
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
	kpt_stats.kpttotal = atop(s);
I 18
#endif
#ifdef DEBUG
E 18
	if (pmapdebug & PDB_INIT)
		printf("pmap_init: KPT: %d pages from %x to %x\n",
		       atop(s), addr, addr + s);
#endif

	/*
I 24
	 * Allocate the segment table map
	 */
	s = maxproc * HP_STSIZE;
	st_map = kmem_suballoc(kernel_map, &addr, &addr2, s, TRUE);

	/*
E 24
	 * Slightly modified version of kmem_suballoc() to get page table
	 * map where we want it.
	 */
	addr = HP_PTBASE;
D 2
	s = min(HP_PTMAXSIZE, nproc*HP_MAX_PTSIZE);
E 2
I 2
	s = min(HP_PTMAXSIZE, maxproc*HP_MAX_PTSIZE);
E 2
	addr2 = addr + s;
D 2
	rv = vm_map_find(kernel_map, VM_OBJECT_NULL, 0, &addr, s, TRUE);
E 2
I 2
	rv = vm_map_find(kernel_map, NULL, 0, &addr, s, TRUE);
E 2
	if (rv != KERN_SUCCESS)
		panic("pmap_init: cannot allocate space for PT map");
	pmap_reference(vm_map_pmap(kernel_map));
	pt_map = vm_map_create(vm_map_pmap(kernel_map), addr, addr2, TRUE);
D 2
	if (pt_map == VM_MAP_NULL)
E 2
I 2
	if (pt_map == NULL)
E 2
		panic("pmap_init: cannot create pt_map");
	rv = vm_map_submap(kernel_map, addr, addr2, pt_map);
	if (rv != KERN_SUCCESS)
		panic("pmap_init: cannot map range to pt_map");
#ifdef DEBUG
	if (pmapdebug & PDB_INIT)
		printf("pmap_init: pt_map [%x - %x)\n", addr, addr2);
#endif

I 12
#if defined(HP380)
	if (mmutype == MMU_68040) {
		protostfree = ~l2tobm(0);
		for (rv = MAXUL2SIZE; rv < sizeof(protostfree)*NBBY; rv++)
			protostfree &= ~l2tobm(rv);
	}
#endif

E 12
	/*
	 * Now it is safe to enable pv_table recording.
	 */
	vm_first_phys = phys_start;
	vm_last_phys = phys_end;
	pmap_initialized = TRUE;
}

/*
 *	Used to map a range of physical addresses into kernel
 *	virtual address space.
 *
 *	For now, VM is already on, we only need to map the
 *	specified memory.
 */
vm_offset_t
pmap_map(virt, start, end, prot)
	vm_offset_t	virt;
	vm_offset_t	start;
	vm_offset_t	end;
	int		prot;
{
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_map(%x, %x, %x, %x)\n", virt, start, end, prot);
#endif
	while (start < end) {
		pmap_enter(kernel_pmap, virt, start, prot, FALSE);
		virt += PAGE_SIZE;
		start += PAGE_SIZE;
	}
	return(virt);
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
pmap_t
pmap_create(size)
	vm_size_t	size;
{
	register pmap_t pmap;

#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_CREATE))
		printf("pmap_create(%x)\n", size);
#endif
	/*
	 * Software use map does not need a pmap
	 */
	if (size)
D 2
		return(PMAP_NULL);
E 2
I 2
		return(NULL);
E 2

	/* XXX: is it ok to wait here? */
	pmap = (pmap_t) malloc(sizeof *pmap, M_VMPMAP, M_WAITOK);
D 2
	if (pmap == PMAP_NULL)
E 2
I 2
#ifdef notifwewait
	if (pmap == NULL)
E 2
		panic("pmap_create: cannot allocate a pmap");
I 2
#endif
	bzero(pmap, sizeof(*pmap));
	pmap_pinit(pmap);
	return (pmap);
}
E 2

I 2
/*
 * Initialize a preallocated and zeroed pmap structure,
 * such as one in a vmspace structure.
 */
void
pmap_pinit(pmap)
	register struct pmap *pmap;
{

#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_CREATE))
		printf("pmap_pinit(%x)\n", pmap);
#endif
E 2
	/*
	 * No need to allocate page table space yet but we do need a
	 * valid segment table.  Initially, we point everyone at the
	 * "null" segment table.  On the first pmap_enter, a real
	 * segment table will be allocated.
	 */
D 2
	pmap->pm_ptab = PT_ENTRY_NULL;
E 2
	pmap->pm_stab = Segtabzero;
I 12
	pmap->pm_stpa = Segtabzeropa;
#if defined(HP380)
	if (mmutype == MMU_68040)
		pmap->pm_stfree = protostfree;
#endif
E 12
	pmap->pm_stchanged = TRUE;
D 2
	pmap->pm_sref = 0;
E 2
	pmap->pm_count = 1;
	simple_lock_init(&pmap->pm_lock);
D 2
	pmap->pm_stats.resident_count = 0;
	pmap->pm_stats.wired_count = 0;
	pmap->pm_ptpages = 0;
	return(pmap);
E 2
}

/*
 *	Retire the given physical map from service.
 *	Should only be called if the map contains
 *	no valid mappings.
 */
void
pmap_destroy(pmap)
	register pmap_t pmap;
{
	int count;

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_destroy(%x)\n", pmap);
#endif
D 2
	if (pmap == PMAP_NULL)
E 2
I 2
	if (pmap == NULL)
E 2
		return;

	simple_lock(&pmap->pm_lock);
	count = --pmap->pm_count;
	simple_unlock(&pmap->pm_lock);
D 2
	if (count)
		return;
E 2
I 2
	if (count == 0) {
		pmap_release(pmap);
		free((caddr_t)pmap, M_VMPMAP);
	}
}
E 2

I 2
/*
 * Release any resources held by the given physical map.
 * Called when a pmap initialized by pmap_pinit is being released.
 * Should only be called if the map contains no valid mappings.
 */
void
pmap_release(pmap)
	register struct pmap *pmap;
{

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_release(%x)\n", pmap);
#endif
#ifdef notdef /* DIAGNOSTIC */
	/* count would be 0 from pmap_destroy... */
	simple_lock(&pmap->pm_lock);
	if (pmap->pm_count != 1)
		panic("pmap_release count");
#endif
E 2
	if (pmap->pm_ptab)
		kmem_free_wakeup(pt_map, (vm_offset_t)pmap->pm_ptab,
				 HP_MAX_PTSIZE);
	if (pmap->pm_stab != Segtabzero)
D 24
		kmem_free(kernel_map, (vm_offset_t)pmap->pm_stab, HP_STSIZE);
E 24
I 24
		kmem_free_wakeup(st_map, (vm_offset_t)pmap->pm_stab,
				 HP_STSIZE);
E 24
D 2
	free((caddr_t)pmap, M_VMPMAP);
E 2
}

/*
 *	Add a reference to the specified pmap.
 */
void
pmap_reference(pmap)
	pmap_t	pmap;
{
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_reference(%x)\n", pmap);
#endif
D 2
	if (pmap != PMAP_NULL) {
E 2
I 2
	if (pmap != NULL) {
E 2
		simple_lock(&pmap->pm_lock);
		pmap->pm_count++;
		simple_unlock(&pmap->pm_lock);
	}
}

/*
 *	Remove the given range of addresses from the specified map.
 *
 *	It is assumed that the start and end are properly
 *	rounded to the page size.
 */
void
pmap_remove(pmap, sva, eva)
	register pmap_t pmap;
D 18
	vm_offset_t sva, eva;
E 18
I 18
	register vm_offset_t sva, eva;
E 18
{
D 18
	register vm_offset_t pa, va;
E 18
I 18
	register vm_offset_t nssva;
E 18
	register pt_entry_t *pte;
D 18
	register pv_entry_t pv, npv;
D 12
	register int ix;
E 12
	pmap_t ptpmap;
	int *ste, s, bits;
	boolean_t firstpage = TRUE;
	boolean_t flushcache = FALSE;
#ifdef DEBUG
	pt_entry_t opte;
E 18
I 18
	boolean_t firstpage, needcflush;
	int flags;
E 18

I 18
#ifdef DEBUG
E 18
	if (pmapdebug & (PDB_FOLLOW|PDB_REMOVE|PDB_PROTECT))
		printf("pmap_remove(%x, %x, %x)\n", pmap, sva, eva);
#endif

D 2
	if (pmap == PMAP_NULL)
E 2
I 2
	if (pmap == NULL)
E 2
		return;

D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
	remove_stats.calls++;
#endif
D 18
	for (va = sva; va < eva; va += PAGE_SIZE) {
E 18
I 18
	firstpage = TRUE;
	needcflush = FALSE;
	flags = active_pmap(pmap) ? PRM_TFLUSH : 0;
	while (sva < eva) {
		nssva = hp300_trunc_seg(sva) + HP_SEG_SIZE;
		if (nssva == 0 || nssva > eva)
			nssva = eva;
E 18
		/*
D 18
		 * Weed out invalid mappings.
		 * Note: we assume that the segment table is always allocated.
E 18
I 18
		 * If VA belongs to an unallocated segment,
		 * skip to the next segment boundary.
E 18
		 */
D 12
		if (!pmap_ste_v(pmap_ste(pmap, va))) {
E 12
I 12
D 18
		if (!pmap_ste_v(pmap, va)) {
E 12
			/* XXX: avoid address wrap around */
D 12
			if (va >= hp300_trunc_seg((vm_offset_t)-1))
E 12
I 12
			if (va >= hp300_trunc_seg(VM_MAX_ADDRESS))
E 12
				break;
			va = hp300_round_seg(va + PAGE_SIZE) - PAGE_SIZE;
E 18
I 18
		if (!pmap_ste_v(pmap, sva)) {
			sva = nssva;
E 18
			continue;
		}
D 18
		pte = pmap_pte(pmap, va);
		pa = pmap_pte_pa(pte);
		if (pa == 0)
			continue;
E 18
		/*
D 18
		 * Invalidating a non-CI page, must flush external VAC
		 * unless it is a supervisor mapping and we have already
		 * flushed the supervisor side.
E 18
I 18
		 * Invalidate every valid mapping within this segment.
E 18
		 */
D 18
		if (pmap_aliasmask && !pmap_pte_ci(pte) &&
		    !(pmap == kernel_pmap && firstpage))
			flushcache = TRUE;
#ifdef DEBUG
		opte = *pte;
		remove_stats.removes++;
E 18
I 18
		pte = pmap_pte(pmap, sva);
		while (sva < nssva) {
			if (pmap_pte_v(pte)) {
#ifdef HAVEVAC
				if (pmap_aliasmask) {
					/*
					 * Purge kernel side of VAC to ensure
					 * we get the correct state of any
					 * hardware maintained bits.
					 */
					if (firstpage) {
						DCIS();
#ifdef PMAPSTATS
						remove_stats.sflushes++;
E 18
#endif
D 18
		/*
		 * Update statistics
		 */
		if (pmap_pte_w(pte))
			pmap->pm_stats.wired_count--;
		pmap->pm_stats.resident_count--;

		/*
		 * Invalidate the PTEs.
		 * XXX: should cluster them up and invalidate as many
		 * as possible at once.
		 */
#ifdef DEBUG
		if (pmapdebug & PDB_REMOVE)
D 12
			printf("remove: invalidating %x ptes at %x\n",
			       hppagesperpage, pte);
E 12
I 12
			printf("remove: invalidating pte at %x\n", pte);
E 12
#endif
		/*
		 * Flush VAC to ensure we get the correct state of any
		 * hardware maintained bits.
		 */
		if (firstpage && pmap_aliasmask) {
			firstpage = FALSE;
			if (pmap == kernel_pmap)
				flushcache = FALSE;
			DCIS();
#ifdef DEBUG
			remove_stats.sflushes++;
#endif
		}
D 12
		bits = ix = 0;
		do {
			bits |= *(int *)pte & (PG_U|PG_M);
			*(int *)pte++ = PG_NV;
			TBIS(va + ix * HP_PAGE_SIZE);
		} while (++ix != hppagesperpage);
E 12
I 12
#if defined(DYNPGSIZE)
		{
			register int ix = 0;
E 12

I 12
			bits = 0;
			do {
				bits |= *(int *)pte & (PG_U|PG_M);
				*(int *)pte++ = PG_NV;
				TBIS(va + ix * HP_PAGE_SIZE);
			} while (++ix != hppagesperpage);
		}
#else
		bits = *(int *)pte & (PG_U|PG_M);
		*(int *)pte = PG_NV;
		TBIS(va);
#endif
E 12
		/*
		 * For user mappings decrement the wiring count on
		 * the PT page.  We do this after the PTE has been
		 * invalidated because vm_map_pageable winds up in
		 * pmap_pageable which clears the modify bit for the
		 * PT page.
		 */
		if (pmap != kernel_pmap) {
			pte = pmap_pte(pmap, va);
			vm_map_pageable(pt_map, trunc_page(pte),
					round_page(pte+1), TRUE);
#ifdef DEBUG
			if (pmapdebug & PDB_WIRING)
				pmap_check_wiring("remove", trunc_page(pte));
#endif
		}
		/*
		 * Remove from the PV table (raise IPL since we
		 * may be called at interrupt time).
		 */
		if (pa < vm_first_phys || pa >= vm_last_phys)
			continue;
		pv = pa_to_pvh(pa);
		ste = (int *)0;
		s = splimp();
		/*
		 * If it is the first entry on the list, it is actually
		 * in the header and we must copy the following entry up
		 * to the header.  Otherwise we must search the list for
		 * the entry.  In either case we free the now unused entry.
		 */
		if (pmap == pv->pv_pmap && va == pv->pv_va) {
			ste = (int *)pv->pv_ptste;
			ptpmap = pv->pv_ptpmap;
			npv = pv->pv_next;
			if (npv) {
				*pv = *npv;
				free((caddr_t)npv, M_VMPVENT);
			} else
D 2
				pv->pv_pmap = PMAP_NULL;
E 2
I 2
				pv->pv_pmap = NULL;
E 2
#ifdef DEBUG
			remove_stats.pvfirst++;
#endif
		} else {
			for (npv = pv->pv_next; npv; npv = npv->pv_next) {
#ifdef DEBUG
				remove_stats.pvsearch++;
#endif
				if (pmap == npv->pv_pmap && va == npv->pv_va)
					break;
				pv = npv;
			}
#ifdef DEBUG
D 2
			if (npv == PV_ENTRY_NULL)
E 2
I 2
			if (npv == NULL)
E 2
				panic("pmap_remove: PA not in pv_tab");
#endif
			ste = (int *)npv->pv_ptste;
			ptpmap = npv->pv_ptpmap;
			pv->pv_next = npv->pv_next;
			free((caddr_t)npv, M_VMPVENT);
			pv = pa_to_pvh(pa);
		}
		/*
		 * If only one mapping left we no longer need to cache inhibit
		 */
		if (pv->pv_pmap &&
D 2
		    pv->pv_next == PV_ENTRY_NULL && (pv->pv_flags & PV_CI)) {
E 2
I 2
		    pv->pv_next == NULL && (pv->pv_flags & PV_CI)) {
E 2
#ifdef DEBUG
			if (pmapdebug & PDB_CACHE)
				printf("remove: clearing CI for pa %x\n", pa);
#endif
			pv->pv_flags &= ~PV_CI;
			pmap_changebit(pa, PG_CI, FALSE);
#ifdef DEBUG
			if ((pmapdebug & (PDB_CACHE|PDB_PVDUMP)) ==
			    (PDB_CACHE|PDB_PVDUMP))
				pmap_pvdump(pa);
#endif
		}

		/*
		 * If this was a PT page we must also remove the
		 * mapping from the associated segment table.
		 */
		if (ste) {
#ifdef DEBUG
			remove_stats.ptinvalid++;
			if (pmapdebug & (PDB_REMOVE|PDB_PTPAGE)) {
				printf("remove: ste was %x@%x pte was %x@%x\n",
				       *ste, ste,
				       *(int *)&opte, pmap_pte(pmap, va));
			}
#endif
I 12
#if defined(HP380)
			if (mmutype == MMU_68040) {
				int *este = &ste[NPTEPG/SG4_LEV3SIZE];

				while (ste < este)
					*ste++ = SG_NV;
			} else
#endif
E 12
			*ste = SG_NV;
			/*
			 * If it was a user PT page, we decrement the
			 * reference count on the segment table as well,
			 * freeing it if it is now empty.
			 */
			if (ptpmap != kernel_pmap) {
#ifdef DEBUG
				if (pmapdebug & (PDB_REMOVE|PDB_SEGTAB))
					printf("remove: stab %x, refcnt %d\n",
					       ptpmap->pm_stab,
					       ptpmap->pm_sref - 1);
				if ((pmapdebug & PDB_PARANOIA) &&
D 2
				    ptpmap->pm_stab != trunc_page(ste))
E 2
I 2
				    ptpmap->pm_stab != (st_entry_t *)trunc_page(ste))
E 2
					panic("remove: bogus ste");
#endif
				if (--(ptpmap->pm_sref) == 0) {
#ifdef DEBUG
					if (pmapdebug&(PDB_REMOVE|PDB_SEGTAB))
					printf("remove: free stab %x\n",
					       ptpmap->pm_stab);
#endif
					kmem_free(kernel_map,
						  (vm_offset_t)ptpmap->pm_stab,
						  HP_STSIZE);
					ptpmap->pm_stab = Segtabzero;
I 12
					ptpmap->pm_stpa = Segtabzeropa;
#if defined(HP380)
					if (mmutype == MMU_68040)
						ptpmap->pm_stfree = protostfree;
#endif
E 12
					ptpmap->pm_stchanged = TRUE;
E 18
I 18
					}
E 18
					/*
D 18
					 * XXX may have changed segment table
					 * pointer for current process so
					 * update now to reload hardware.
E 18
I 18
					 * Remember if we may need to
					 * flush the VAC due to a non-CI
					 * mapping.
E 18
					 */
D 2
					if (ptpmap == u.u_procp->p_map->pmap)
E 2
I 2
D 18
					if (ptpmap == curproc->p_vmspace->vm_map.pmap)
E 2
						PMAP_ACTIVATE(ptpmap,
D 2
							(struct pcb *)u.u_procp->p_addr);
E 2
I 2
							(struct pcb *)curproc->p_addr, 1);
E 18
I 18
					if (!needcflush && !pmap_pte_ci(pte))
						needcflush = TRUE;

E 18
E 2
				}
I 18
#endif
				pmap_remove_mapping(pmap, sva, pte, flags);
				firstpage = FALSE;
E 18
			}
D 18
			if (ptpmap == kernel_pmap)
				TBIAS();
			else
				TBIAU();
			pv->pv_flags &= ~PV_PTPAGE;
			ptpmap->pm_ptpages--;
E 18
I 18
			pte++;
			sva += PAGE_SIZE;
E 18
		}
D 18
		/*
		 * Update saved attributes for managed page
		 */
		pmap_attributes[pa_index(pa)] |= bits;
		splx(s);
E 18
	}
I 18
	/*
	 * Didn't do anything, no need for cache flushes
	 */
	if (firstpage)
		return;
#ifdef HAVEVAC
	/*
	 * In a couple of cases, we don't need to worry about flushing
	 * the VAC:
	 * 	1. if this is a kernel mapping,
	 *	   we have already done it
	 *	2. if it is a user mapping not for the current process,
	 *	   it won't be there
	 */
	if (pmap_aliasmask &&
	    (pmap == kernel_pmap || pmap != curproc->p_vmspace->vm_map.pmap))
		needcflush = FALSE;
E 18
#ifdef DEBUG
D 18
	if (pmapvacflush & PVF_REMOVE) {
E 18
I 18
	if (pmap_aliasmask && (pmapvacflush & PVF_REMOVE)) {
E 18
		if (pmapvacflush & PVF_TOTAL)
			DCIA();
		else if (pmap == kernel_pmap)
			DCIS();
		else
			DCIU();
D 18
	}
E 18
I 18
	} else
E 18
#endif
D 18
	if (flushcache) {
E 18
I 18
	if (needcflush) {
E 18
		if (pmap == kernel_pmap) {
			DCIS();
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
			remove_stats.sflushes++;
#endif
		} else {
			DCIU();
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
			remove_stats.uflushes++;
#endif
		}
	}
I 18
#endif
E 18
}

/*
D 4
 *	Routine:	pmap_remove_all
 *	Function:
 *		Removes this physical page from
 *		all physical maps in which it resides.
 *		Reflects back modify bits to the pager.
E 4
I 4
 *	pmap_page_protect:
 *
 *	Lower the permission for all mappings to a given page.
E 4
 */
void
D 4
pmap_remove_all(pa)
	vm_offset_t pa;
E 4
I 4
pmap_page_protect(pa, prot)
	vm_offset_t	pa;
	vm_prot_t	prot;
E 4
{
	register pv_entry_t pv;
	int s;

#ifdef DEBUG
D 4
	if (pmapdebug & (PDB_FOLLOW|PDB_REMOVE|PDB_PROTECT))
		printf("pmap_remove_all(%x)\n", pa);
E 4
I 4
	if ((pmapdebug & (PDB_FOLLOW|PDB_PROTECT)) ||
	    prot == VM_PROT_NONE && (pmapdebug & PDB_REMOVE))
		printf("pmap_page_protect(%x, %x)\n", pa, prot);
E 4
#endif
D 4
	/*
	 * Not one of ours
	 */
E 4
	if (pa < vm_first_phys || pa >= vm_last_phys)
		return;

D 4
	pv = pa_to_pvh(pa);
	s = splimp();
	/*
	 * Do it the easy way for now
	 */
D 2
	while (pv->pv_pmap != PMAP_NULL) {
E 2
I 2
	while (pv->pv_pmap != NULL) {
E 4
I 4
	switch (prot) {
I 18
	case VM_PROT_READ|VM_PROT_WRITE:
E 18
	case VM_PROT_ALL:
D 23
		break;
E 23
I 23
		return;
E 23
	/* copy_on_write */
	case VM_PROT_READ:
	case VM_PROT_READ|VM_PROT_EXECUTE:
		pmap_changebit(pa, PG_RO, TRUE);
D 23
		break;
E 23
I 23
		return;
E 23
	/* remove_all */
	default:
D 23
		pv = pa_to_pvh(pa);
		s = splimp();
		while (pv->pv_pmap != NULL) {
E 23
I 23
		break;
	}
	pv = pa_to_pvh(pa);
	s = splimp();
	while (pv->pv_pmap != NULL) {
		register pt_entry_t *pte;

		pte = pmap_pte(pv->pv_pmap, pv->pv_va);
E 23
E 4
E 2
#ifdef DEBUG
D 4
		if (!pmap_ste_v(pmap_ste(pv->pv_pmap, pv->pv_va)) ||
		    pmap_pte_pa(pmap_pte(pv->pv_pmap, pv->pv_va)) != pa)
			panic("pmap_remove_all: bad mapping");
E 4
I 4
D 12
			if (!pmap_ste_v(pmap_ste(pv->pv_pmap,pv->pv_va)) ||
E 12
I 12
D 23
			if (!pmap_ste_v(pv->pv_pmap, pv->pv_va) ||
E 12
			    pmap_pte_pa(pmap_pte(pv->pv_pmap,pv->pv_va)) != pa)
				panic("pmap_page_protect: bad mapping");
E 23
I 23
		if (!pmap_ste_v(pv->pv_pmap, pv->pv_va) ||
		    pmap_pte_pa(pte) != pa)
			panic("pmap_page_protect: bad mapping");
E 23
E 4
#endif
I 23
		if (!pmap_pte_w(pte))
E 23
D 4
		pmap_remove(pv->pv_pmap, pv->pv_va, pv->pv_va + PAGE_SIZE);
E 4
I 4
D 18
			pmap_remove(pv->pv_pmap, pv->pv_va,
				    pv->pv_va + PAGE_SIZE);
E 18
I 18
			pmap_remove_mapping(pv->pv_pmap, pv->pv_va,
D 23
					    PT_ENTRY_NULL,
					    PRM_TFLUSH|PRM_CFLUSH);
E 23
I 23
					    pte, PRM_TFLUSH|PRM_CFLUSH);
		else {
			pv = pv->pv_next;
#ifdef DEBUG
			if (pmapdebug & PDB_PARANOIA)
				printf("%s wired mapping for %x not removed\n",
				       "pmap_page_protect:", pa);
#endif
E 23
E 18
		}
D 23
		splx(s);
		break;
E 23
E 4
	}
I 23
	splx(s);
E 23
D 4
	splx(s);
E 4
}

/*
D 4
 *	Routine:	pmap_copy_on_write
 *	Function:
 *		Remove write privileges from all
 *		physical maps for this physical page.
 */
void
pmap_copy_on_write(pa)
	vm_offset_t pa;
{
#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_PROTECT))
		printf("pmap_copy_on_write(%x)\n", pa);
#endif
	pmap_changebit(pa, PG_RO, TRUE);
}

/*
E 4
 *	Set the physical protection on the
 *	specified range of this map as requested.
 */
void
pmap_protect(pmap, sva, eva, prot)
	register pmap_t	pmap;
D 18
	vm_offset_t	sva, eva;
	vm_prot_t	prot;
E 18
I 18
	register vm_offset_t sva, eva;
	vm_prot_t prot;
E 18
{
I 18
	register vm_offset_t nssva;
E 18
	register pt_entry_t *pte;
D 18
	register vm_offset_t va;
D 12
	register int ix;
E 12
	int hpprot;
	boolean_t firstpage = TRUE;
E 18
I 18
	boolean_t firstpage, needtflush;
	int isro;
E 18

#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_PROTECT))
		printf("pmap_protect(%x, %x, %x, %x)\n", pmap, sva, eva, prot);
I 12
D 18
	protect_stats.calls++;
E 18
E 12
#endif
I 18

E 18
D 2
	if (pmap == PMAP_NULL)
E 2
I 2
	if (pmap == NULL)
E 2
		return;

I 18
#ifdef PMAPSTATS
	protect_stats.calls++;
#endif
E 18
	if ((prot & VM_PROT_READ) == VM_PROT_NONE) {
		pmap_remove(pmap, sva, eva);
		return;
	}
	if (prot & VM_PROT_WRITE)
		return;

D 18
	pte = pmap_pte(pmap, sva);
	hpprot = pte_prot(pmap, prot) == PG_RO ? 1 : 0;
	for (va = sva; va < eva; va += PAGE_SIZE) {
E 18
I 18
	isro = pte_prot(pmap, prot);
	needtflush = active_pmap(pmap);
	firstpage = TRUE;
	while (sva < eva) {
		nssva = hp300_trunc_seg(sva) + HP_SEG_SIZE;
		if (nssva == 0 || nssva > eva)
			nssva = eva;
E 18
		/*
D 18
		 * Page table page is not allocated.
		 * Skip it, we don't want to force allocation
		 * of unnecessary PTE pages just to set the protection.
E 18
I 18
		 * If VA belongs to an unallocated segment,
		 * skip to the next segment boundary.
E 18
		 */
D 12
		if (!pmap_ste_v(pmap_ste(pmap, va))) {
E 12
I 12
D 18
		if (!pmap_ste_v(pmap, va)) {
E 12
			/* XXX: avoid address wrap around */
			if (va >= hp300_trunc_seg((vm_offset_t)-1))
				break;
			va = hp300_round_seg(va + PAGE_SIZE) - PAGE_SIZE;
D 12
			pte = pmap_pte(pmap, va);
			pte += hppagesperpage;
E 12
I 12
#if defined(DYNPGSIZE)
			pte = pmap_pte(pmap, va) + hppagesperpage;
#else
			pte = pmap_pte(pmap, va) + 1;
#endif
E 18
I 18
		if (!pmap_ste_v(pmap, sva)) {
			sva = nssva;
E 18
E 12
			continue;
		}
		/*
D 18
		 * Page not valid.  Again, skip it.
		 * Should we do this?  Or set protection anyway?
E 18
I 18
		 * Change protection on mapping if it is valid and doesn't
		 * already have the correct protection.
E 18
		 */
D 18
		if (!pmap_pte_v(pte)) {
I 12
#if defined(DYNPGSIZE)
E 12
			pte += hppagesperpage;
I 12
#else
			pte++;
#endif
E 12
			continue;
		}
		/*
D 12
		 * Flush VAC to ensure we get correct state of HW bits
		 * so we don't clobber them.
E 12
I 12
		 * Purge kernel side of VAC to ensure we get correct state
		 * of HW bits so we don't clobber them.
E 12
		 */
		if (firstpage && pmap_aliasmask) {
			firstpage = FALSE;
			DCIS();
		}
D 12
		ix = 0;
		do {
			/* clear VAC here if PG_RO? */
			pmap_pte_set_prot(pte++, hpprot);
			TBIS(va + ix * HP_PAGE_SIZE);
		} while (++ix != hppagesperpage);
E 12
I 12
#if defined(DYNPGSIZE)
		{
			register int ix = 0;

			do {
E 18
I 18
		pte = pmap_pte(pmap, sva);
		while (sva < nssva) {
			if (pmap_pte_v(pte) && pmap_pte_prot_chg(pte, isro)) {
#ifdef HAVEVAC
E 18
				/*
D 18
				 * Clear caches as necessary if making RO.
				 * XXX clear VAC?  Doesn't seem to be needed.
E 18
I 18
				 * Purge kernel side of VAC to ensure we
				 * get the correct state of any hardware
				 * maintained bits.
				 *
				 * XXX do we need to clear the VAC in
				 * general to reflect the new protection?
E 18
				 */
I 18
				if (firstpage && pmap_aliasmask)
					DCIS();
#endif
E 18
#if defined(HP380)
D 18
				if (hpprot && !pmap_pte_prot(pte)) {
E 18
I 18
				/*
				 * Clear caches if making RO (see section
				 * "7.3 Cache Coherency" in the manual).
				 */
				if (isro && mmutype == MMU_68040) {
E 18
					vm_offset_t pa = pmap_pte_pa(pte);

D 18
					if (mmutype == MMU_68040) {
						DCFP(pa);
						ICPP(pa);
					}
E 18
I 18
					DCFP(pa);
					ICPP(pa);
E 18
				}
#endif
D 18
#ifdef DEBUG
				protect_stats.pages++;
				if (hpprot && pmap_pte_prot(pte))
E 18
I 18
				pmap_pte_set_prot(pte, isro);
				if (needtflush)
					TBIS(sva);
#ifdef PMAPSTATS
				protect_stats.changed++;
#endif
				firstpage = FALSE;
			}
#ifdef PMAPSTATS
			else if (pmap_pte_v(pte)) {
				if (isro)
E 18
					protect_stats.alreadyro++;
D 18
				if (!hpprot && !pmap_pte_prot(pte))
E 18
I 18
				else
E 18
					protect_stats.alreadyrw++;
D 18
#endif
				pmap_pte_set_prot(pte++, hpprot);
				TBIS(va + ix * HP_PAGE_SIZE);
			} while (++ix != hppagesperpage);
		}
#else
		/*
		 * Clear caches as necessary if making RO.
		 * XXX clear VAC?  Doesn't seem to be needed.
		 */
#if defined(HP380)
		if (hpprot && !pmap_pte_prot(pte)) {
			vm_offset_t pa = pmap_pte_pa(pte);

			if (mmutype == MMU_68040) {
				DCFP(pa);
				ICPP(pa);
E 18
			}
D 18
		}
E 18
#endif
D 18
#ifdef DEBUG
		protect_stats.pages++;
		if (hpprot && pmap_pte_prot(pte))
			protect_stats.alreadyro++;
		if (!hpprot && !pmap_pte_prot(pte))
			protect_stats.alreadyrw++;
#endif
		pmap_pte_set_prot(pte++, hpprot);
		TBIS(va);
#endif
E 18
I 18
			pte++;
			sva += PAGE_SIZE;
		}
E 18
E 12
	}
D 18
#ifdef DEBUG
	if (hpprot && (pmapvacflush & PVF_PROTECT)) {
E 18
I 18
#if defined(HAVEVAC) && defined(DEBUG)
	if (pmap_aliasmask && (pmapvacflush & PVF_PROTECT)) {
E 18
		if (pmapvacflush & PVF_TOTAL)
			DCIA();
		else if (pmap == kernel_pmap)
			DCIS();
		else
			DCIU();
	}
#endif
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
void
pmap_enter(pmap, va, pa, prot, wired)
	register pmap_t pmap;
	vm_offset_t va;
	register vm_offset_t pa;
	vm_prot_t prot;
	boolean_t wired;
{
	register pt_entry_t *pte;
D 12
	register int npte, ix;
E 12
I 12
	register int npte;
E 12
	vm_offset_t opa;
	boolean_t cacheable = TRUE;
	boolean_t checkpv = TRUE;

#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_ENTER))
		printf("pmap_enter(%x, %x, %x, %x, %x)\n",
		       pmap, va, pa, prot, wired);
#endif
D 2
	if (pmap == PMAP_NULL)
E 2
I 2
	if (pmap == NULL)
E 2
		return;

D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
	if (pmap == kernel_pmap)
		enter_stats.kernel++;
	else
		enter_stats.user++;
#endif
	/*
	 * For user mapping, allocate kernel VM resources if necessary.
	 */
D 2
	if (pmap->pm_ptab == PT_ENTRY_NULL)
E 2
I 2
	if (pmap->pm_ptab == NULL)
E 2
		pmap->pm_ptab = (pt_entry_t *)
			kmem_alloc_wait(pt_map, HP_MAX_PTSIZE);

	/*
	 * Segment table entry not valid, we need a new PT page
	 */
D 12
	if (!pmap_ste_v(pmap_ste(pmap, va)))
E 12
I 12
	if (!pmap_ste_v(pmap, va))
E 12
		pmap_enter_ptpage(pmap, va);

I 18
	pa = hp300_trunc_page(pa);
E 18
	pte = pmap_pte(pmap, va);
	opa = pmap_pte_pa(pte);
#ifdef DEBUG
	if (pmapdebug & PDB_ENTER)
		printf("enter: pte %x, *pte %x\n", pte, *(int *)pte);
#endif

	/*
	 * Mapping has not changed, must be protection or wiring change.
	 */
	if (opa == pa) {
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
		enter_stats.pwchange++;
#endif
		/*
		 * Wiring change, just update stats.
		 * We don't worry about wiring PT pages as they remain
		 * resident as long as there are valid mappings in them.
		 * Hence, if a user page is wired, the PT page will be also.
		 */
D 18
		if (wired && !pmap_pte_w(pte) || !wired && pmap_pte_w(pte)) {
E 18
I 18
		if (pmap_pte_w_chg(pte, wired ? PG_W : 0)) {
E 18
#ifdef DEBUG
			if (pmapdebug & PDB_ENTER)
				printf("enter: wiring change -> %x\n", wired);
#endif
			if (wired)
				pmap->pm_stats.wired_count++;
			else
				pmap->pm_stats.wired_count--;
D 18
#ifdef DEBUG
			enter_stats.wchange++;
E 18
I 18
#ifdef PMAPSTATS
			if (pmap_pte_prot(pte) == pte_prot(pmap, prot))
				enter_stats.wchange++;
E 18
#endif
		}
I 18
#ifdef PMAPSTATS
		else if (pmap_pte_prot(pte) != pte_prot(pmap, prot))
			enter_stats.pchange++;
		else
			enter_stats.nochange++;
#endif
E 18
		/*
		 * Retain cache inhibition status
		 */
		checkpv = FALSE;
		if (pmap_pte_ci(pte))
			cacheable = FALSE;
		goto validate;
	}

	/*
	 * Mapping has changed, invalidate old range and fall through to
	 * handle validating new mapping.
	 */
	if (opa) {
#ifdef DEBUG
		if (pmapdebug & PDB_ENTER)
			printf("enter: removing old mapping %x\n", va);
#endif
D 18
		pmap_remove(pmap, va, va + PAGE_SIZE);
#ifdef DEBUG
E 18
I 18
		pmap_remove_mapping(pmap, va, pte, PRM_TFLUSH|PRM_CFLUSH);
#ifdef PMAPSTATS
E 18
		enter_stats.mchange++;
#endif
	}

	/*
	 * If this is a new user mapping, increment the wiring count
	 * on this PT page.  PT pages are wired down as long as there
	 * is a valid mapping in the page.
	 */
	if (pmap != kernel_pmap)
D 19
		vm_map_pageable(pt_map, trunc_page(pte),
				round_page(pte+1), FALSE);
E 19
I 19
		(void) vm_map_pageable(pt_map, trunc_page(pte),
				       round_page(pte+1), FALSE);
E 19

	/*
	 * Enter on the PV list if part of our managed memory
	 * Note that we raise IPL while manipulating pv_table
	 * since pmap_enter can be called at interrupt time.
	 */
	if (pa >= vm_first_phys && pa < vm_last_phys) {
		register pv_entry_t pv, npv;
		int s;

D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
		enter_stats.managed++;
#endif
		pv = pa_to_pvh(pa);
		s = splimp();
#ifdef DEBUG
		if (pmapdebug & PDB_ENTER)
			printf("enter: pv at %x: %x/%x/%x\n",
			       pv, pv->pv_va, pv->pv_pmap, pv->pv_next);
#endif
		/*
		 * No entries yet, use header as the first entry
		 */
D 2
		if (pv->pv_pmap == PMAP_NULL) {
E 2
I 2
		if (pv->pv_pmap == NULL) {
E 2
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
			enter_stats.firstpv++;
#endif
			pv->pv_va = va;
			pv->pv_pmap = pmap;
D 2
			pv->pv_next = PV_ENTRY_NULL;
			pv->pv_ptste = ST_ENTRY_NULL;
			pv->pv_ptpmap = PMAP_NULL;
E 2
I 2
			pv->pv_next = NULL;
			pv->pv_ptste = NULL;
			pv->pv_ptpmap = NULL;
E 2
			pv->pv_flags = 0;
		}
		/*
		 * There is at least one other VA mapping this page.
		 * Place this entry after the header.
		 */
		else {
#ifdef DEBUG
			for (npv = pv; npv; npv = npv->pv_next)
				if (pmap == npv->pv_pmap && va == npv->pv_va)
					panic("pmap_enter: already in pv_tab");
#endif
			npv = (pv_entry_t)
				malloc(sizeof *npv, M_VMPVENT, M_NOWAIT);
			npv->pv_va = va;
			npv->pv_pmap = pmap;
			npv->pv_next = pv->pv_next;
D 2
			npv->pv_ptste = ST_ENTRY_NULL;
			npv->pv_ptpmap = PMAP_NULL;
E 2
I 2
			npv->pv_ptste = NULL;
			npv->pv_ptpmap = NULL;
I 18
			npv->pv_flags = 0;
E 18
E 2
			pv->pv_next = npv;
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
			if (!npv->pv_next)
				enter_stats.secondpv++;
#endif
I 18
#ifdef HAVEVAC
E 18
			/*
			 * Since there is another logical mapping for the
			 * same page we may need to cache-inhibit the
			 * descriptors on those CPUs with external VACs.
			 * We don't need to CI if:
			 *
			 * - No two mappings belong to the same user pmaps.
			 *   Since the cache is flushed on context switches
			 *   there is no problem between user processes.
			 *
			 * - Mappings within a single pmap are a certain
			 *   magic distance apart.  VAs at these appropriate
			 *   boundaries map to the same cache entries or
			 *   otherwise don't conflict.
			 *
			 * To keep it simple, we only check for these special
			 * cases if there are only two mappings, otherwise we
			 * punt and always CI.
			 *
			 * Note that there are no aliasing problems with the
			 * on-chip data-cache when the WA bit is set.
			 */
			if (pmap_aliasmask) {
				if (pv->pv_flags & PV_CI) {
#ifdef DEBUG
					if (pmapdebug & PDB_CACHE)
					printf("enter: pa %x already CI'ed\n",
					       pa);
#endif
					checkpv = cacheable = FALSE;
				} else if (npv->pv_next ||
					   ((pmap == pv->pv_pmap ||
					     pmap == kernel_pmap ||
					     pv->pv_pmap == kernel_pmap) &&
					    ((pv->pv_va & pmap_aliasmask) !=
					     (va & pmap_aliasmask)))) {
#ifdef DEBUG
					if (pmapdebug & PDB_CACHE)
					printf("enter: pa %x CI'ing all\n",
					       pa);
#endif
					cacheable = FALSE;
					pv->pv_flags |= PV_CI;
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
					enter_stats.ci++;
#endif
				}
			}
I 18
#endif
E 18
		}
		splx(s);
	}
	/*
	 * Assumption: if it is not part of our managed memory
	 * then it must be device memory which may be volitile.
	 */
	else if (pmap_initialized) {
		checkpv = cacheable = FALSE;
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
		enter_stats.unmanaged++;
#endif
	}

	/*
	 * Increment counters
	 */
	pmap->pm_stats.resident_count++;
	if (wired)
		pmap->pm_stats.wired_count++;

validate:
I 18
#ifdef HAVEVAC
E 18
	/*
D 12
	 * Flush VAC to ensure we get correct state of HW bits
	 * so we don't clobber them.
E 12
I 12
	 * Purge kernel side of VAC to ensure we get correct state
	 * of HW bits so we don't clobber them.
E 12
	 */
	if (pmap_aliasmask)
		DCIS();
I 18
#endif
E 18
	/*
D 18
	 * Now validate mapping with desired protection/wiring.
	 * Assume uniform modified and referenced status for all
	 * HP pages in a MACH page.
E 18
I 18
	 * Build the new PTE.
E 18
	 */
D 18
	npte = (pa & PG_FRAME) | pte_prot(pmap, prot) | PG_V;
	npte |= (*(int *)pte & (PG_M|PG_U));
E 18
I 18
	npte = pa | pte_prot(pmap, prot) | (*(int *)pte & (PG_M|PG_U)) | PG_V;
E 18
	if (wired)
		npte |= PG_W;
	if (!checkpv && !cacheable)
		npte |= PG_CI;
I 12
#if defined(HP380)
	if (mmutype == MMU_68040 && (npte & (PG_PROT|PG_CI)) == PG_RW)
E 12
#ifdef DEBUG
I 12
		if (dowriteback && (dokwriteback || pmap != kernel_pmap))
#endif
		npte |= PG_CCB;
#endif
#ifdef DEBUG
E 12
	if (pmapdebug & PDB_ENTER)
		printf("enter: new pte value %x\n", npte);
#endif
D 12
	ix = 0;
	do {
		*(int *)pte++ = npte;
		TBIS(va);
		npte += HP_PAGE_SIZE;
		va += HP_PAGE_SIZE;
	} while (++ix != hppagesperpage);
E 12
I 12
D 18
#if defined(DYNPGSIZE)
	{
		register int ix = 0;

		do {
E 18
I 18
	/*
	 * Remember if this was a wiring-only change.
	 * If so, we need not flush the TLB and caches.
	 */
	wired = ((*(int *)pte ^ npte) == PG_W);
E 18
#if defined(HP380)
D 18
			if (mmutype == MMU_68040) {
				DCFP(pa);
				ICPP(pa);
			}
#endif
			*(int *)pte++ = npte;
			TBIS(va);
			npte += HP_PAGE_SIZE;
			va += HP_PAGE_SIZE;
		} while (++ix != hppagesperpage);
	}
#else
#if defined(HP380)
	if (mmutype == MMU_68040) {
E 18
I 18
	if (mmutype == MMU_68040 && !wired) {
E 18
		DCFP(pa);
		ICPP(pa);
	}
#endif
	*(int *)pte = npte;
D 18
	TBIS(va);
#endif
E 18
I 18
	if (!wired && active_pmap(pmap))
		TBIS(va);
#ifdef HAVEVAC
E 18
E 12
	/*
	 * The following is executed if we are entering a second
	 * (or greater) mapping for a physical page and the mappings
	 * may create an aliasing problem.  In this case we must
	 * cache inhibit the descriptors involved and flush any
	 * external VAC.
	 */
	if (checkpv && !cacheable) {
		pmap_changebit(pa, PG_CI, TRUE);
		DCIA();
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
		enter_stats.flushes++;
#endif
#ifdef DEBUG
		if ((pmapdebug & (PDB_CACHE|PDB_PVDUMP)) ==
		    (PDB_CACHE|PDB_PVDUMP))
			pmap_pvdump(pa);
#endif
	}
#ifdef DEBUG
	else if (pmapvacflush & PVF_ENTER) {
		if (pmapvacflush & PVF_TOTAL)
			DCIA();
		else if (pmap == kernel_pmap)
			DCIS();
		else
			DCIU();
	}
D 18
	if ((pmapdebug & PDB_WIRING) && pmap != kernel_pmap) {
I 12
#if defined(DYNPGSIZE)
E 12
		va -= PAGE_SIZE;
E 18
I 12
#endif
I 18
#endif
#ifdef DEBUG
	if ((pmapdebug & PDB_WIRING) && pmap != kernel_pmap)
E 18
E 12
		pmap_check_wiring("enter", trunc_page(pmap_pte(pmap, va)));
D 18
	}
E 18
#endif
}

/*
 *	Routine:	pmap_change_wiring
 *	Function:	Change the wiring attribute for a map/virtual-address
 *			pair.
 *	In/out conditions:
 *			The mapping must already exist in the pmap.
 */
void
pmap_change_wiring(pmap, va, wired)
	register pmap_t	pmap;
	vm_offset_t	va;
	boolean_t	wired;
{
	register pt_entry_t *pte;
D 12
	register int ix;
E 12

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_change_wiring(%x, %x, %x)\n", pmap, va, wired);
#endif
D 2
	if (pmap == PMAP_NULL)
E 2
I 2
	if (pmap == NULL)
E 2
		return;

	pte = pmap_pte(pmap, va);
#ifdef DEBUG
	/*
	 * Page table page is not allocated.
	 * Should this ever happen?  Ignore it for now,
	 * we don't want to force allocation of unnecessary PTE pages.
	 */
D 12
	if (!pmap_ste_v(pmap_ste(pmap, va))) {
E 12
I 12
	if (!pmap_ste_v(pmap, va)) {
E 12
		if (pmapdebug & PDB_PARANOIA)
			printf("pmap_change_wiring: invalid STE for %x\n", va);
		return;
	}
	/*
	 * Page not valid.  Should this ever happen?
	 * Just continue and change wiring anyway.
	 */
	if (!pmap_pte_v(pte)) {
		if (pmapdebug & PDB_PARANOIA)
			printf("pmap_change_wiring: invalid PTE for %x\n", va);
	}
#endif
D 18
	if (wired && !pmap_pte_w(pte) || !wired && pmap_pte_w(pte)) {
E 18
I 18
	/*
	 * If wiring actually changed (always?) set the wire bit and
	 * update the wire count.  Note that wiring is not a hardware
	 * characteristic so there is no need to invalidate the TLB.
	 */
	if (pmap_pte_w_chg(pte, wired ? PG_W : 0)) {
		pmap_pte_set_w(pte, wired);
E 18
		if (wired)
			pmap->pm_stats.wired_count++;
		else
			pmap->pm_stats.wired_count--;
	}
D 18
	/*
	 * Wiring is not a hardware characteristic so there is no need
	 * to invalidate TLB.
	 */
D 12
	ix = 0;
	do {
		pmap_pte_set_w(pte++, wired);
	} while (++ix != hppagesperpage);
E 12
I 12
#if defined(DYNPGSIZE)
	{
		register int ix = 0;

		do {
			pmap_pte_set_w(pte++, wired);
		} while (++ix != hppagesperpage);
	}
#else
	pmap_pte_set_w(pte, wired);
#endif
E 18
E 12
}

/*
 *	Routine:	pmap_extract
 *	Function:
 *		Extract the physical page address associated
 *		with the given map/virtual_address pair.
 */

vm_offset_t
pmap_extract(pmap, va)
	register pmap_t	pmap;
	vm_offset_t va;
{
	register vm_offset_t pa;

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_extract(%x, %x) -> ", pmap, va);
#endif
	pa = 0;
D 12
	if (pmap && pmap_ste_v(pmap_ste(pmap, va)))
E 12
I 12
	if (pmap && pmap_ste_v(pmap, va))
E 12
		pa = *(int *)pmap_pte(pmap, va);
	if (pa)
		pa = (pa & PG_FRAME) | (va & ~PG_FRAME);
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("%x\n", pa);
#endif
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
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_copy(%x, %x, %x, %x, %x)\n",
		       dst_pmap, src_pmap, dst_addr, len, src_addr);
#endif
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
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_update()\n");
#endif
	TBIA();
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
void
pmap_collect(pmap)
	pmap_t		pmap;
{
	register vm_offset_t pa;
	register pv_entry_t pv;
	register int *pte;
	vm_offset_t kpa;
	int s;

#ifdef DEBUG
	int *ste;
	int opmapdebug;
#endif
	if (pmap != kernel_pmap)
		return;

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_collect(%x)\n", pmap);
I 18
#endif
#ifdef PMAPSTATS
E 18
	kpt_stats.collectscans++;
#endif
	s = splimp();
	for (pa = vm_first_phys; pa < vm_last_phys; pa += PAGE_SIZE) {
		register struct kpt_page *kpt, **pkpt;

		/*
		 * Locate physical pages which are being used as kernel
		 * page table pages.
		 */
		pv = pa_to_pvh(pa);
		if (pv->pv_pmap != kernel_pmap || !(pv->pv_flags & PV_PTPAGE))
			continue;
		do {
			if (pv->pv_ptste && pv->pv_ptpmap == kernel_pmap)
				break;
		} while (pv = pv->pv_next);
D 2
		if (pv == PV_ENTRY_NULL)
E 2
I 2
		if (pv == NULL)
E 2
			continue;
#ifdef DEBUG
		if (pv->pv_va < (vm_offset_t)Sysmap ||
		    pv->pv_va >= (vm_offset_t)Sysmap + HP_MAX_PTSIZE)
			printf("collect: kernel PT VA out of range\n");
		else
			goto ok;
		pmap_pvdump(pa);
		continue;
ok:
#endif
		pte = (int *)(pv->pv_va + HP_PAGE_SIZE);
		while (--pte >= (int *)pv->pv_va && *pte == PG_NV)
			;
		if (pte >= (int *)pv->pv_va)
			continue;

#ifdef DEBUG
		if (pmapdebug & (PDB_PTPAGE|PDB_COLLECT)) {
			printf("collect: freeing KPT page at %x (ste %x@%x)\n",
			       pv->pv_va, *(int *)pv->pv_ptste, pv->pv_ptste);
			opmapdebug = pmapdebug;
			pmapdebug |= PDB_PTPAGE;
		}

		ste = (int *)pv->pv_ptste;
#endif
		/*
		 * If all entries were invalid we can remove the page.
D 18
		 * We call pmap_remove to take care of invalidating ST
		 * and Sysptmap entries.
E 18
I 18
		 * We call pmap_remove_entry to take care of invalidating
		 * ST and Sysptmap entries.
E 18
		 */
		kpa = pmap_extract(pmap, pv->pv_va);
D 18
		pmap_remove(pmap, pv->pv_va, pv->pv_va + HP_PAGE_SIZE);
E 18
I 18
		pmap_remove_mapping(pmap, pv->pv_va, PT_ENTRY_NULL,
				    PRM_TFLUSH|PRM_CFLUSH);
E 18
		/*
		 * Use the physical address to locate the original
		 * (kmem_alloc assigned) address for the page and put
		 * that page back on the free list.
		 */
		for (pkpt = &kpt_used_list, kpt = *pkpt;
		     kpt != (struct kpt_page *)0;
		     pkpt = &kpt->kpt_next, kpt = *pkpt)
			if (kpt->kpt_pa == kpa)
				break;
#ifdef DEBUG
		if (kpt == (struct kpt_page *)0)
			panic("pmap_collect: lost a KPT page");
		if (pmapdebug & (PDB_PTPAGE|PDB_COLLECT))
			printf("collect: %x (%x) to free list\n",
			       kpt->kpt_va, kpa);
#endif
		*pkpt = kpt->kpt_next;
		kpt->kpt_next = kpt_free_list;
		kpt_free_list = kpt;
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
		kpt_stats.kptinuse--;
		kpt_stats.collectpages++;
I 18
#endif
#ifdef DEBUG
E 18
		if (pmapdebug & (PDB_PTPAGE|PDB_COLLECT))
			pmapdebug = opmapdebug;

		if (*ste)
			printf("collect: kernel STE at %x still valid (%x)\n",
			       ste, *ste);
		ste = (int *)&Sysptmap[(st_entry_t *)ste-pmap_ste(kernel_pmap, 0)];
		if (*ste)
			printf("collect: kernel PTmap at %x still valid (%x)\n",
			       ste, *ste);
#endif
	}
	splx(s);
}

void
pmap_activate(pmap, pcbp)
	register pmap_t pmap;
	struct pcb *pcbp;
{
#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_SEGTAB))
		printf("pmap_activate(%x, %x)\n", pmap, pcbp);
#endif
D 2
	PMAP_ACTIVATE(pmap, pcbp);
E 2
I 2
	PMAP_ACTIVATE(pmap, pcbp, pmap == curproc->p_vmspace->vm_map.pmap);
E 2
}

/*
D 4
 *	Routine:	pmap_kernel
 *	Function:
 *		Returns the physical map handle for the kernel.
 */
pmap_t
pmap_kernel()
{
    	return (kernel_pmap);
}

/*
E 4
 *	pmap_zero_page zeros the specified (machine independent)
 *	page by mapping the page into virtual memory and using
 *	bzero to clear its contents, one machine dependent page
 *	at a time.
I 12
 *
 *	XXX this is a bad implementation for virtual cache machines
 *	(320/350) because pmap_enter doesn't cache-inhibit the temporary
 *	kernel mapping and we wind up with data cached for that KVA.
 *	It is probably a win for physical cache machines (370/380)
 *	as the cache loading is not wasted.
E 12
 */
I 10
void
E 10
pmap_zero_page(phys)
D 12
	register vm_offset_t	phys;
E 12
I 12
	vm_offset_t phys;
E 12
{
D 12
	register int ix;
E 12
I 12
	register vm_offset_t kva;
	extern caddr_t CADDR1;
E 12

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_zero_page(%x)\n", phys);
#endif
D 12
	phys >>= PG_SHIFT;
	ix = 0;
	do {
		clearseg(phys++);
	} while (++ix != hppagesperpage);
E 12
I 12
	kva = (vm_offset_t) CADDR1;
D 18
#if defined(DYNPGSIZE)
	{
		register int ix = 0;

		do {
			pmap_enter(kernel_pmap, kva, phys,
				   VM_PROT_READ|VM_PROT_WRITE, TRUE);
			bzero((caddr_t)kva, HP_PAGE_SIZE);
			pmap_remove(kernel_pmap, kva, kva+HP_PAGE_SIZE);
			phys += HP_PAGE_SIZE;
		} while (++ix != hppagesperpage);
	}
#else
E 18
	pmap_enter(kernel_pmap, kva, phys, VM_PROT_READ|VM_PROT_WRITE, TRUE);
	bzero((caddr_t)kva, HP_PAGE_SIZE);
D 18
	pmap_remove(kernel_pmap, kva, kva+PAGE_SIZE);
#endif
E 18
I 18
	pmap_remove_mapping(kernel_pmap, kva, PT_ENTRY_NULL,
			    PRM_TFLUSH|PRM_CFLUSH);
E 18
E 12
}

/*
 *	pmap_copy_page copies the specified (machine independent)
 *	page by mapping the page into virtual memory and using
 *	bcopy to copy the page, one machine dependent page at a
 *	time.
I 12
 *
 *
 *	XXX this is a bad implementation for virtual cache machines
 *	(320/350) because pmap_enter doesn't cache-inhibit the temporary
 *	kernel mapping and we wind up with data cached for that KVA.
 *	It is probably a win for physical cache machines (370/380)
 *	as the cache loading is not wasted.
E 12
 */
I 10
void
E 10
pmap_copy_page(src, dst)
D 12
	register vm_offset_t	src, dst;
E 12
I 12
	vm_offset_t src, dst;
E 12
{
D 12
	register int ix;
E 12
I 12
	register vm_offset_t skva, dkva;
	extern caddr_t CADDR1, CADDR2;
E 12

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_copy_page(%x, %x)\n", src, dst);
#endif
D 12
	src >>= PG_SHIFT;
	dst >>= PG_SHIFT;
	ix = 0;
	do {
		physcopyseg(src++, dst++);
	} while (++ix != hppagesperpage);
E 12
I 12
	skva = (vm_offset_t) CADDR1;
	dkva = (vm_offset_t) CADDR2;
D 18
#if defined(DYNPGSIZE)
	{
		register int ix = 0;

		do {
			pmap_enter(kernel_pmap, skva, src, VM_PROT_READ, TRUE);
			pmap_enter(kernel_pmap, dkva, dst,
				   VM_PROT_READ|VM_PROT_WRITE, TRUE);
			bcopy((caddr_t)skva, (caddr_t)dkva, PAGE_SIZE);
			/* CADDR1 and CADDR2 are virtually contiguous */
			pmap_remove(kernel_pmap, skva, skva+2*HP_PAGE_SIZE);
			src += HP_PAGE_SIZE;
			dst += HP_PAGE_SIZE;
		} while (++ix != hppagesperpage);
	}
#else
E 18
	pmap_enter(kernel_pmap, skva, src, VM_PROT_READ, TRUE);
	pmap_enter(kernel_pmap, dkva, dst, VM_PROT_READ|VM_PROT_WRITE, TRUE);
D 21
	bcopy((caddr_t)skva, (caddr_t)dkva, PAGE_SIZE);
E 21
I 21
	copypage((caddr_t)skva, (caddr_t)dkva);
E 21
	/* CADDR1 and CADDR2 are virtually contiguous */
	pmap_remove(kernel_pmap, skva, skva+2*PAGE_SIZE);
D 18
#endif
E 18
E 12
}

D 12

E 12
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
I 10
void
E 10
pmap_pageable(pmap, sva, eva, pageable)
	pmap_t		pmap;
	vm_offset_t	sva, eva;
	boolean_t	pageable;
{
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_pageable(%x, %x, %x, %x)\n",
		       pmap, sva, eva, pageable);
#endif
	/*
	 * If we are making a PT page pageable then all valid
	 * mappings must be gone from that page.  Hence it should
	 * be all zeros and there is no need to clean it.
	 * Assumptions:
	 *	- we are called with only one page at a time
	 *	- PT pages have only one pv_table entry
	 */
	if (pmap == kernel_pmap && pageable && sva + PAGE_SIZE == eva) {
		register pv_entry_t pv;
		register vm_offset_t pa;

#ifdef DEBUG
		if ((pmapdebug & (PDB_FOLLOW|PDB_PTPAGE)) == PDB_PTPAGE)
			printf("pmap_pageable(%x, %x, %x, %x)\n",
			       pmap, sva, eva, pageable);
#endif
D 12
		if (!pmap_ste_v(pmap_ste(pmap, sva)))
E 12
I 12
		if (!pmap_ste_v(pmap, sva))
E 12
			return;
		pa = pmap_pte_pa(pmap_pte(pmap, sva));
		if (pa < vm_first_phys || pa >= vm_last_phys)
			return;
		pv = pa_to_pvh(pa);
D 2
		if (pv->pv_ptste == ST_ENTRY_NULL)
E 2
I 2
		if (pv->pv_ptste == NULL)
E 2
			return;
#ifdef DEBUG
		if (pv->pv_va != sva || pv->pv_next) {
			printf("pmap_pageable: bad PT page va %x next %x\n",
			       pv->pv_va, pv->pv_next);
			return;
		}
#endif
		/*
		 * Mark it unmodified to avoid pageout
		 */
D 2
		pmap_clear_modify(pa);
E 2
I 2
		pmap_changebit(pa, PG_M, FALSE);
E 2
#ifdef DEBUG
I 23
		if ((PHYS_TO_VM_PAGE(pa)->flags & PG_CLEAN) == 0) {
			printf("pa %x: flags=%x: not clean\n",
			       pa, PHYS_TO_VM_PAGE(pa)->flags);
			PHYS_TO_VM_PAGE(pa)->flags |= PG_CLEAN;
		}
E 23
		if (pmapdebug & PDB_PTPAGE)
			printf("pmap_pageable: PT page %x(%x) unmodified\n",
			       sva, *(int *)pmap_pte(pmap, sva));
		if (pmapdebug & PDB_WIRING)
			pmap_check_wiring("pageable", sva);
#endif
	}
}

/*
 *	Clear the modify bits on the specified physical page.
 */

void
pmap_clear_modify(pa)
	vm_offset_t	pa;
{
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_clear_modify(%x)\n", pa);
#endif
	pmap_changebit(pa, PG_M, FALSE);
}

/*
 *	pmap_clear_reference:
 *
 *	Clear the reference bit on the specified physical page.
 */

void pmap_clear_reference(pa)
	vm_offset_t	pa;
{
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_clear_reference(%x)\n", pa);
#endif
	pmap_changebit(pa, PG_U, FALSE);
}

/*
 *	pmap_is_referenced:
 *
 *	Return whether or not the specified physical page is referenced
 *	by any physical maps.
 */

boolean_t
pmap_is_referenced(pa)
	vm_offset_t	pa;
{
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW) {
		boolean_t rv = pmap_testbit(pa, PG_U);
		printf("pmap_is_referenced(%x) -> %c\n", pa, "FT"[rv]);
		return(rv);
	}
#endif
	return(pmap_testbit(pa, PG_U));
}

/*
 *	pmap_is_modified:
 *
 *	Return whether or not the specified physical page is modified
 *	by any physical maps.
 */

boolean_t
pmap_is_modified(pa)
	vm_offset_t	pa;
{
#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW) {
		boolean_t rv = pmap_testbit(pa, PG_M);
		printf("pmap_is_modified(%x) -> %c\n", pa, "FT"[rv]);
		return(rv);
	}
#endif
	return(pmap_testbit(pa, PG_M));
}

vm_offset_t
pmap_phys_address(ppn)
	int ppn;
{
	return(hp300_ptob(ppn));
}

I 18
#ifdef HPUXCOMPAT
E 18
/*
I 18
 * 'PUX hack for dealing with the so called multi-mapped address space.
 * The first 256mb is mapped in at every 256mb region from 0x10000000
 * up to 0xF0000000.  This allows for 15 bits of tag information.
 *
 * We implement this at the segment table level, the machine independent
 * VM knows nothing about it.
 */
pmap_mapmulti(pmap, va)
	pmap_t pmap;
	vm_offset_t va;
{
	int *ste, *bste;

#ifdef DEBUG
	if (pmapdebug & PDB_MULTIMAP) {
		ste = (int *)pmap_ste(pmap, HPMMBASEADDR(va));
		printf("pmap_mapmulti(%x, %x): bste %x(%x)",
		       pmap, va, ste, *ste);
		ste = (int *)pmap_ste(pmap, va);
		printf(" ste %x(%x)\n", ste, *ste);
	}
#endif
	bste = (int *) pmap_ste(pmap, HPMMBASEADDR(va));
	ste = (int *) pmap_ste(pmap, va);
	if (*ste == SG_NV && (*bste & SG_V)) {
		*ste = *bste;
		TBIAU();
		return (KERN_SUCCESS);
	}
	return (KERN_INVALID_ADDRESS);
}
#endif

/*
E 18
 * Miscellaneous support routines follow
 */

I 18
/*
 * Invalidate a single page denoted by pmap/va.
 * If (pte != NULL), it is the already computed PTE for the page.
 * If (flags & PRM_TFLUSH), we must invalidate any TLB information.
 * If (flags & PRM_CFLUSH), we must flush/invalidate any cache information.
 */
E 18
/* static */
I 18
void
pmap_remove_mapping(pmap, va, pte, flags)
	register pmap_t pmap;
	register vm_offset_t va;
	register pt_entry_t *pte;
	int flags;
{
	register vm_offset_t pa;
	register pv_entry_t pv, npv;
	pmap_t ptpmap;
	int *ste, s, bits;
#ifdef DEBUG
	pt_entry_t opte;

	if (pmapdebug & (PDB_FOLLOW|PDB_REMOVE|PDB_PROTECT))
		printf("pmap_remove_mapping(%x, %x, %x, %x)\n",
		       pmap, va, pte, flags);
#endif

	/*
	 * PTE not provided, compute it from pmap and va.
	 */
	if (pte == PT_ENTRY_NULL) {
		pte = pmap_pte(pmap, va);
		if (*(int *)pte == PG_NV)
			return;
	}
#ifdef HAVEVAC
	if (pmap_aliasmask && (flags & PRM_CFLUSH)) {
		/*
		 * Purge kernel side of VAC to ensure we get the correct
		 * state of any hardware maintained bits.
		 */
		DCIS();
#ifdef PMAPSTATS
		remove_stats.sflushes++;
#endif
		/*
		 * If this is a non-CI user mapping for the current process,
		 * flush the VAC.  Note that the kernel side was flushed
		 * above so we don't worry about non-CI kernel mappings.
		 */
		if (pmap == curproc->p_vmspace->vm_map.pmap &&
		    !pmap_pte_ci(pte)) {
			DCIU();
#ifdef PMAPSTATS
			remove_stats.uflushes++;
#endif
		}
	}
#endif
	pa = pmap_pte_pa(pte);
#ifdef DEBUG
	opte = *pte;
#endif
#ifdef PMAPSTATS
	remove_stats.removes++;
#endif
	/*
	 * Update statistics
	 */
	if (pmap_pte_w(pte))
		pmap->pm_stats.wired_count--;
	pmap->pm_stats.resident_count--;

	/*
	 * Invalidate the PTE after saving the reference modify info.
	 */
#ifdef DEBUG
	if (pmapdebug & PDB_REMOVE)
		printf("remove: invalidating pte at %x\n", pte);
#endif
	bits = *(int *)pte & (PG_U|PG_M);
	*(int *)pte = PG_NV;
	if ((flags & PRM_TFLUSH) && active_pmap(pmap))
		TBIS(va);
	/*
	 * For user mappings decrement the wiring count on
	 * the PT page.  We do this after the PTE has been
	 * invalidated because vm_map_pageable winds up in
	 * pmap_pageable which clears the modify bit for the
	 * PT page.
	 */
	if (pmap != kernel_pmap) {
I 26
#if defined(DEBUG) && NCPUS == 1
		/*
		 * XXX this recursive use of the VM won't work on a MP
		 * (or when otherwise debugging simple locks).  We might
		 * be called with the page queue lock held (e.g. from
		 * the pageout daemon) and vm_map_pageable might call
		 * vm_fault_unwire which would try to lock the page queues
		 * again.  For debugging we hack and drop the lock.
		 */
		int hadit = !simple_lock_try(&vm_page_queue_lock);
		simple_unlock(&vm_page_queue_lock);
#endif
E 26
D 19
		vm_map_pageable(pt_map, trunc_page(pte),
				round_page(pte+1), TRUE);
E 19
I 19
		(void) vm_map_pageable(pt_map, trunc_page(pte),
				       round_page(pte+1), TRUE);
E 19
#ifdef DEBUG
		if (pmapdebug & PDB_WIRING)
			pmap_check_wiring("remove", trunc_page(pte));
I 26
#if NCPUS == 1
		if (hadit)
			simple_lock(&vm_page_queue_lock);
#endif
E 26
#endif
	}
	/*
	 * If this isn't a managed page, we are all done.
	 */
	if (pa < vm_first_phys || pa >= vm_last_phys)
		return;
	/*
	 * Otherwise remove it from the PV table
	 * (raise IPL since we may be called at interrupt time).
	 */
	pv = pa_to_pvh(pa);
	ste = (int *)0;
	s = splimp();
	/*
	 * If it is the first entry on the list, it is actually
	 * in the header and we must copy the following entry up
	 * to the header.  Otherwise we must search the list for
	 * the entry.  In either case we free the now unused entry.
	 */
	if (pmap == pv->pv_pmap && va == pv->pv_va) {
		ste = (int *)pv->pv_ptste;
		ptpmap = pv->pv_ptpmap;
		npv = pv->pv_next;
		if (npv) {
			npv->pv_flags = pv->pv_flags;
			*pv = *npv;
			free((caddr_t)npv, M_VMPVENT);
		} else
			pv->pv_pmap = NULL;
#ifdef PMAPSTATS
		remove_stats.pvfirst++;
#endif
	} else {
		for (npv = pv->pv_next; npv; npv = npv->pv_next) {
#ifdef PMAPSTATS
			remove_stats.pvsearch++;
#endif
			if (pmap == npv->pv_pmap && va == npv->pv_va)
				break;
			pv = npv;
		}
#ifdef DEBUG
		if (npv == NULL)
			panic("pmap_remove: PA not in pv_tab");
#endif
		ste = (int *)npv->pv_ptste;
		ptpmap = npv->pv_ptpmap;
		pv->pv_next = npv->pv_next;
		free((caddr_t)npv, M_VMPVENT);
		pv = pa_to_pvh(pa);
	}
#ifdef HAVEVAC
	/*
	 * If only one mapping left we no longer need to cache inhibit
	 */
	if (pmap_aliasmask &&
	    pv->pv_pmap && pv->pv_next == NULL && (pv->pv_flags & PV_CI)) {
#ifdef DEBUG
		if (pmapdebug & PDB_CACHE)
			printf("remove: clearing CI for pa %x\n", pa);
#endif
		pv->pv_flags &= ~PV_CI;
		pmap_changebit(pa, PG_CI, FALSE);
#ifdef DEBUG
		if ((pmapdebug & (PDB_CACHE|PDB_PVDUMP)) ==
		    (PDB_CACHE|PDB_PVDUMP))
			pmap_pvdump(pa);
#endif
	}
#endif
	/*
	 * If this was a PT page we must also remove the
	 * mapping from the associated segment table.
	 */
	if (ste) {
#ifdef PMAPSTATS
		remove_stats.ptinvalid++;
#endif
#ifdef DEBUG
		if (pmapdebug & (PDB_REMOVE|PDB_PTPAGE))
			printf("remove: ste was %x@%x pte was %x@%x\n",
			       *ste, ste, *(int *)&opte, pmap_pte(pmap, va));
#endif
#if defined(HP380)
		if (mmutype == MMU_68040) {
			int *este = &ste[NPTEPG/SG4_LEV3SIZE];

			while (ste < este)
				*ste++ = SG_NV;
#ifdef DEBUG
			ste -= NPTEPG/SG4_LEV3SIZE;
#endif
		} else
#endif
		*ste = SG_NV;
		/*
		 * If it was a user PT page, we decrement the
		 * reference count on the segment table as well,
		 * freeing it if it is now empty.
		 */
		if (ptpmap != kernel_pmap) {
#ifdef DEBUG
			if (pmapdebug & (PDB_REMOVE|PDB_SEGTAB))
				printf("remove: stab %x, refcnt %d\n",
				       ptpmap->pm_stab, ptpmap->pm_sref - 1);
			if ((pmapdebug & PDB_PARANOIA) &&
			    ptpmap->pm_stab != (st_entry_t *)trunc_page(ste))
				panic("remove: bogus ste");
#endif
			if (--(ptpmap->pm_sref) == 0) {
#ifdef DEBUG
				if (pmapdebug&(PDB_REMOVE|PDB_SEGTAB))
					printf("remove: free stab %x\n",
					       ptpmap->pm_stab);
#endif
D 24
				kmem_free(kernel_map,
					  (vm_offset_t)ptpmap->pm_stab,
					  HP_STSIZE);
E 24
I 24
				kmem_free_wakeup(st_map,
						 (vm_offset_t)ptpmap->pm_stab,
						 HP_STSIZE);
E 24
				ptpmap->pm_stab = Segtabzero;
				ptpmap->pm_stpa = Segtabzeropa;
#if defined(HP380)
				if (mmutype == MMU_68040)
					ptpmap->pm_stfree = protostfree;
#endif
				ptpmap->pm_stchanged = TRUE;
				/*
				 * XXX may have changed segment table
				 * pointer for current process so
				 * update now to reload hardware.
				 */
				if (ptpmap == curproc->p_vmspace->vm_map.pmap)
					PMAP_ACTIVATE(ptpmap,
					    (struct pcb *)curproc->p_addr, 1);
			}
I 23
#ifdef DEBUG
			else if (ptpmap->pm_sref < 0)
				panic("remove: sref < 0");
#endif
E 23
		}
#if 0
		/*
		 * XXX this should be unnecessary as we have been
		 * flushing individual mappings as we go.
		 */
		if (ptpmap == kernel_pmap)
			TBIAS();
		else
			TBIAU();
#endif
		pv->pv_flags &= ~PV_PTPAGE;
		ptpmap->pm_ptpages--;
	}
	/*
	 * Update saved attributes for managed page
	 */
	pmap_attributes[pa_index(pa)] |= bits;
	splx(s);
}

/* static */
E 18
D 12
hp300_protection_init()
{
	register int *kp, prot;

	kp = protection_codes;
	for (prot = 0; prot < 8; prot++) {
		switch (prot) {
		case VM_PROT_NONE | VM_PROT_NONE | VM_PROT_NONE:
			*kp++ = 0;
			break;
		case VM_PROT_READ | VM_PROT_NONE | VM_PROT_NONE:
		case VM_PROT_READ | VM_PROT_NONE | VM_PROT_EXECUTE:
		case VM_PROT_NONE | VM_PROT_NONE | VM_PROT_EXECUTE:
			*kp++ = PG_RO;
			break;
		case VM_PROT_NONE | VM_PROT_WRITE | VM_PROT_NONE:
		case VM_PROT_NONE | VM_PROT_WRITE | VM_PROT_EXECUTE:
		case VM_PROT_READ | VM_PROT_WRITE | VM_PROT_NONE:
		case VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE:
			*kp++ = PG_RW;
			break;
		}
	}
}

/* static */
E 12
boolean_t
pmap_testbit(pa, bit)
	register vm_offset_t pa;
	int bit;
{
	register pv_entry_t pv;
D 12
	register int *pte, ix;
E 12
I 12
	register int *pte;
E 12
	int s;

	if (pa < vm_first_phys || pa >= vm_last_phys)
		return(FALSE);

	pv = pa_to_pvh(pa);
	s = splimp();
	/*
	 * Check saved info first
	 */
	if (pmap_attributes[pa_index(pa)] & bit) {
		splx(s);
		return(TRUE);
	}
I 18
#ifdef HAVEVAC
E 18
	/*
	 * Flush VAC to get correct state of any hardware maintained bits.
	 */
	if (pmap_aliasmask && (bit & (PG_U|PG_M)))
		DCIS();
I 18
#endif
E 18
	/*
	 * Not found, check current mappings returning
	 * immediately if found.
	 */
D 2
	if (pv->pv_pmap != PMAP_NULL) {
E 2
I 2
	if (pv->pv_pmap != NULL) {
E 2
		for (; pv; pv = pv->pv_next) {
			pte = (int *) pmap_pte(pv->pv_pmap, pv->pv_va);
D 12
			ix = 0;
			do {
				if (*pte++ & bit) {
					splx(s);
					return(TRUE);
				}
			} while (++ix != hppagesperpage);
E 12
I 12
D 18
#if defined(DYNPGSIZE)
			{
				register int ix = 0;

				do {
					if (*pte++ & bit) {
						splx(s);
						return(TRUE);
					}
				} while (++ix != hppagesperpage);
			}
#else
E 18
			if (*pte & bit) {
				splx(s);
				return(TRUE);
			}
D 18
#endif
E 18
E 12
		}
	}
	splx(s);
	return(FALSE);
}

/* static */
I 18
void
E 18
pmap_changebit(pa, bit, setem)
	register vm_offset_t pa;
	int bit;
	boolean_t setem;
{
	register pv_entry_t pv;
D 12
	register int *pte, npte, ix;
E 12
I 12
	register int *pte, npte;
E 12
	vm_offset_t va;
	int s;
	boolean_t firstpage = TRUE;
I 18
#ifdef PMAPSTATS
	struct chgstats *chgp;
#endif
E 18

#ifdef DEBUG
	if (pmapdebug & PDB_BITS)
		printf("pmap_changebit(%x, %x, %s)\n",
		       pa, bit, setem ? "set" : "clear");
#endif
	if (pa < vm_first_phys || pa >= vm_last_phys)
		return;

I 18
#ifdef PMAPSTATS
	chgp = &changebit_stats[(bit>>2)-1];
	if (setem)
		chgp->setcalls++;
	else
		chgp->clrcalls++;
#endif
E 18
	pv = pa_to_pvh(pa);
	s = splimp();
	/*
	 * Clear saved attributes (modify, reference)
	 */
	if (!setem)
		pmap_attributes[pa_index(pa)] &= ~bit;
I 12
D 18
#if defined(HP380)
E 18
E 12
	/*
I 12
D 18
	 * If we are changing caching status or protection
	 * make sure the caches are flushed.
	 */
	if (mmutype == MMU_68040 &&
	    (bit == PG_RO && setem || (bit & PG_CMASK))) {
		DCFP(pa);
		ICPP(pa);
	}
#endif
	/*
E 18
E 12
	 * Loop over all current mappings setting/clearing as appropos
	 * If setting RO do we need to clear the VAC?
	 */
D 2
	if (pv->pv_pmap != PMAP_NULL) {
E 2
I 2
	if (pv->pv_pmap != NULL) {
E 2
#ifdef DEBUG
		int toflush = 0;
#endif
		for (; pv; pv = pv->pv_next) {
#ifdef DEBUG
			toflush |= (pv->pv_pmap == kernel_pmap) ? 2 : 1;
#endif
			va = pv->pv_va;
I 4

			/*
			 * XXX don't write protect pager mappings
			 */
			if (bit == PG_RO) {
				extern vm_offset_t pager_sva, pager_eva;

				if (va >= pager_sva && va < pager_eva)
					continue;
			}

E 4
			pte = (int *) pmap_pte(pv->pv_pmap, va);
I 18
#ifdef HAVEVAC
E 18
			/*
			 * Flush VAC to ensure we get correct state of HW bits
			 * so we don't clobber them.
			 */
			if (firstpage && pmap_aliasmask) {
				firstpage = FALSE;
				DCIS();
			}
D 12
			ix = 0;
			do {
				if (setem)
					npte = *pte | bit;
				else
					npte = *pte & ~bit;
				if (*pte != npte) {
					*pte = npte;
					TBIS(va);
				}
				va += HP_PAGE_SIZE;
				pte++;
			} while (++ix != hppagesperpage);
E 12
I 12
D 18
#if defined(DYNPGSIZE)
			{
				register int ix = 0;

				do {
					if (setem)
						npte = *pte | bit;
					else
						npte = *pte & ~bit;
					if (*pte != npte) {
						*pte = npte;
						TBIS(va);
					}
					va += HP_PAGE_SIZE;
					pte++;
				} while (++ix != hppagesperpage);
			}
#else
E 18
I 18
#endif
E 18
			if (setem)
				npte = *pte | bit;
			else
				npte = *pte & ~bit;
			if (*pte != npte) {
I 18
#if defined(HP380)
				/*
				 * If we are changing caching status or
				 * protection make sure the caches are
				 * flushed (but only once).
				 */
				if (firstpage && mmutype == MMU_68040 &&
				    (bit == PG_RO && setem ||
				     (bit & PG_CMASK))) {
					firstpage = FALSE;
					DCFP(pa);
					ICPP(pa);
				}
#endif
E 18
				*pte = npte;
D 18
				TBIS(va);
E 18
I 18
				if (active_pmap(pv->pv_pmap))
					TBIS(va);
#ifdef PMAPSTATS
				if (setem)
					chgp->sethits++;
				else
					chgp->clrhits++;
#endif
E 18
			}
I 18
#ifdef PMAPSTATS
			else {
				if (setem)
					chgp->setmiss++;
				else
					chgp->clrmiss++;
			}
E 18
#endif
E 12
		}
D 18
#ifdef DEBUG
E 18
I 18
#if defined(HAVEVAC) && defined(DEBUG)
E 18
		if (setem && bit == PG_RO && (pmapvacflush & PVF_PROTECT)) {
			if ((pmapvacflush & PVF_TOTAL) || toflush == 3)
				DCIA();
			else if (toflush == 2)
				DCIS();
			else
				DCIU();
		}
#endif
	}
	splx(s);
}

/* static */
void
pmap_enter_ptpage(pmap, va)
	register pmap_t pmap;
	register vm_offset_t va;
{
	register vm_offset_t ptpa;
	register pv_entry_t pv;
	st_entry_t *ste;
	int s;

#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_ENTER|PDB_PTPAGE))
		printf("pmap_enter_ptpage: pmap %x, va %x\n", pmap, va);
I 18
#endif
#ifdef PMAPSTATS
E 18
	enter_stats.ptpneeded++;
#endif
	/*
	 * Allocate a segment table if necessary.  Note that it is allocated
D 24
	 * from kernel_map and not pt_map.  This keeps user page tables
E 24
I 24
	 * from a private map and not pt_map.  This keeps user page tables
E 24
	 * aligned on segment boundaries in the kernel address space.
	 * The segment table is wired down.  It will be freed whenever the
	 * reference count drops to zero.
	 */
	if (pmap->pm_stab == Segtabzero) {
		pmap->pm_stab = (st_entry_t *)
D 24
			kmem_alloc(kernel_map, HP_STSIZE);
E 24
I 24
			kmem_alloc(st_map, HP_STSIZE);
E 24
I 12
		pmap->pm_stpa = (st_entry_t *)
			pmap_extract(kernel_pmap, (vm_offset_t)pmap->pm_stab);
#if defined(HP380)
		if (mmutype == MMU_68040) {
#ifdef DEBUG
			if (dowriteback && dokwriteback)
#endif
D 25
			pmap_changebit((vm_offset_t)pmap->pm_stab, PG_CCB, 0);
E 25
I 25
			pmap_changebit((vm_offset_t)pmap->pm_stpa, PG_CCB, 0);
E 25
			pmap->pm_stfree = protostfree;
		}
#endif
E 12
		pmap->pm_stchanged = TRUE;
		/*
		 * XXX may have changed segment table pointer for current
		 * process so update now to reload hardware.
		 */
D 2
		if (pmap == u.u_procp->p_map->pmap)
			PMAP_ACTIVATE(pmap, (struct pcb *)u.u_procp->p_addr);
E 2
I 2
		if (pmap == curproc->p_vmspace->vm_map.pmap)
			PMAP_ACTIVATE(pmap, (struct pcb *)curproc->p_addr, 1);
E 2
#ifdef DEBUG
		if (pmapdebug & (PDB_ENTER|PDB_PTPAGE|PDB_SEGTAB))
D 12
			printf("enter: pmap %x stab %x\n",
			       pmap, pmap->pm_stab);
E 12
I 12
			printf("enter: pmap %x stab %x(%x)\n",
			       pmap, pmap->pm_stab, pmap->pm_stpa);
E 12
#endif
	}

	ste = pmap_ste(pmap, va);
I 12
#if defined(HP380)
	/*
	 * Allocate level 2 descriptor block if necessary
	 */
	if (mmutype == MMU_68040) {
		if (!ste->sg_v) {
			int ix;
			caddr_t addr;
			
			ix = bmtol2(pmap->pm_stfree);
			if (ix == -1)
				panic("enter: out of address space"); /* XXX */
			pmap->pm_stfree &= ~l2tobm(ix);
			addr = (caddr_t)&pmap->pm_stab[ix*SG4_LEV2SIZE];
			bzero(addr, SG4_LEV2SIZE*sizeof(st_entry_t));
			addr = (caddr_t)&pmap->pm_stpa[ix*SG4_LEV2SIZE];
			*(int *)ste = (u_int)addr | SG_RW | SG_U | SG_V;
#ifdef DEBUG
			if (pmapdebug & (PDB_ENTER|PDB_PTPAGE|PDB_SEGTAB))
				printf("enter: alloc ste2 %d(%x)\n", ix, addr);
#endif
		}
		ste = pmap_ste2(pmap, va);
		/*
		 * Since a level 2 descriptor maps a block of SG4_LEV3SIZE
		 * level 3 descriptors, we need a chunk of NPTEPG/SG4_LEV3SIZE
		 * (16) such descriptors (NBPG/SG4_LEV3SIZE bytes) to map a
		 * PT page--the unit of allocation.  We set `ste' to point
		 * to the first entry of that chunk which is validated in its
		 * entirety below.
		 */
		ste = (st_entry_t *)((int)ste & ~(NBPG/SG4_LEV3SIZE-1));
#ifdef DEBUG
		if (pmapdebug & (PDB_ENTER|PDB_PTPAGE|PDB_SEGTAB))
			printf("enter: ste2 %x (%x)\n",
			       pmap_ste2(pmap, va), ste);
#endif
	}
#endif
E 12
	va = trunc_page((vm_offset_t)pmap_pte(pmap, va));

	/*
	 * In the kernel we allocate a page from the kernel PT page
	 * free list and map it into the kernel page table map (via
	 * pmap_enter).
	 */
	if (pmap == kernel_pmap) {
		register struct kpt_page *kpt;

		s = splimp();
		if ((kpt = kpt_free_list) == (struct kpt_page *)0) {
			/*
			 * No PT pages available.
			 * Try once to free up unused ones.
			 */
#ifdef DEBUG
			if (pmapdebug & PDB_COLLECT)
				printf("enter: no KPT pages, collecting...\n");
#endif
			pmap_collect(kernel_pmap);
			if ((kpt = kpt_free_list) == (struct kpt_page *)0)
				panic("pmap_enter_ptpage: can't get KPT page");
		}
D 18
#ifdef DEBUG
E 18
I 18
#ifdef PMAPSTATS
E 18
		if (++kpt_stats.kptinuse > kpt_stats.kptmaxuse)
			kpt_stats.kptmaxuse = kpt_stats.kptinuse;
#endif
		kpt_free_list = kpt->kpt_next;
		kpt->kpt_next = kpt_used_list;
		kpt_used_list = kpt;
		ptpa = kpt->kpt_pa;
D 14
		bzero(kpt->kpt_va, HP_PAGE_SIZE);
E 14
I 14
		bzero((caddr_t)kpt->kpt_va, HP_PAGE_SIZE);
E 14
		pmap_enter(pmap, va, ptpa, VM_PROT_DEFAULT, TRUE);
#ifdef DEBUG
D 12
		if (pmapdebug & (PDB_ENTER|PDB_PTPAGE))
E 12
I 12
		if (pmapdebug & (PDB_ENTER|PDB_PTPAGE)) {
			int ix = pmap_ste(pmap, va) - pmap_ste(pmap, 0);

E 12
			printf("enter: add &Sysptmap[%d]: %x (KPT page %x)\n",
D 12
			       ste - pmap_ste(pmap, 0),
			       *(int *)&Sysptmap[ste - pmap_ste(pmap, 0)],
			       kpt->kpt_va);
E 12
I 12
			       ix, *(int *)&Sysptmap[ix], kpt->kpt_va);
		}
E 12
#endif
		splx(s);
	}
	/*
	 * For user processes we just simulate a fault on that location
	 * letting the VM system allocate a zero-filled page.
	 */
	else {
#ifdef DEBUG
		if (pmapdebug & (PDB_ENTER|PDB_PTPAGE))
			printf("enter: about to fault UPT pg at %x\n", va);
I 19
#endif
E 19
D 12
#endif
E 12
I 12
		s = vm_fault(pt_map, va, VM_PROT_READ|VM_PROT_WRITE, FALSE);
		if (s != KERN_SUCCESS) {
			printf("vm_fault(pt_map, %x, RW, 0) -> %d\n", va, s);
			panic("pmap_enter: vm_fault failed");
		}
D 19
#else
E 12
		if (vm_fault(pt_map, va, VM_PROT_READ|VM_PROT_WRITE, FALSE)
		    != KERN_SUCCESS)
			panic("pmap_enter: vm_fault failed");
I 12
#endif
E 19
E 12
		ptpa = pmap_extract(kernel_pmap, va);
I 19
		/*
		 * Mark the page clean now to avoid its pageout (and
		 * hence creation of a pager) between now and when it
		 * is wired; i.e. while it is on a paging queue.
		 */
		PHYS_TO_VM_PAGE(ptpa)->flags |= PG_CLEAN;
E 19
#ifdef DEBUG
D 16
		PHYS_TO_VM_PAGE(ptpa)->ptpage = TRUE;
E 16
I 16
		PHYS_TO_VM_PAGE(ptpa)->flags |= PG_PTPAGE;
E 16
#endif
	}
D 12

E 12
I 12
#if defined(HP380)
E 12
	/*
I 12
	 * Turn off copyback caching of page table pages,
	 * could get ugly otherwise.
	 */
#ifdef DEBUG
	if (dowriteback && dokwriteback)
#endif
	if (mmutype == MMU_68040) {
		int *pte = (int *)pmap_pte(kernel_pmap, va);
#ifdef DEBUG
		if ((pmapdebug & PDB_PARANOIA) && (*pte & PG_CCB) == 0)
			printf("%s PT no CCB: kva=%x ptpa=%x pte@%x=%x\n",
			       pmap == kernel_pmap ? "Kernel" : "User",
			       va, ptpa, pte, *pte);
#endif
		pmap_changebit(ptpa, PG_CCB, 0);
	}
#endif
	/*
E 12
	 * Locate the PV entry in the kernel for this PT page and
	 * record the STE address.  This is so that we can invalidate
	 * the STE when we remove the mapping for the page.
	 */
	pv = pa_to_pvh(ptpa);
	s = splimp();
	if (pv) {
		pv->pv_flags |= PV_PTPAGE;
		do {
			if (pv->pv_pmap == kernel_pmap && pv->pv_va == va)
				break;
		} while (pv = pv->pv_next);
	}
#ifdef DEBUG
D 2
	if (pv == PV_ENTRY_NULL)
E 2
I 2
	if (pv == NULL)
E 2
		panic("pmap_enter_ptpage: PT page not entered");
#endif
	pv->pv_ptste = ste;
	pv->pv_ptpmap = pmap;
#ifdef DEBUG
	if (pmapdebug & (PDB_ENTER|PDB_PTPAGE))
		printf("enter: new PT page at PA %x, ste at %x\n", ptpa, ste);
#endif

	/*
	 * Map the new PT page into the segment table.
	 * Also increment the reference count on the segment table if this
	 * was a user page table page.  Note that we don't use vm_map_pageable
	 * to keep the count like we do for PT pages, this is mostly because
	 * it would be difficult to identify ST pages in pmap_pageable to
	 * release them.  We also avoid the overhead of vm_map_pageable.
	 */
I 12
#if defined(HP380)
	if (mmutype == MMU_68040) {
		st_entry_t *este;

		for (este = &ste[NPTEPG/SG4_LEV3SIZE]; ste < este; ste++) {
			*(int *)ste = ptpa | SG_U | SG_RW | SG_V;
			ptpa += SG4_LEV3SIZE * sizeof(st_entry_t);
		}
	} else
#endif
E 12
	*(int *)ste = (ptpa & SG_FRAME) | SG_RW | SG_V;
	if (pmap != kernel_pmap) {
		pmap->pm_sref++;
#ifdef DEBUG
		if (pmapdebug & (PDB_ENTER|PDB_PTPAGE|PDB_SEGTAB))
			printf("enter: stab %x refcnt %d\n",
			       pmap->pm_stab, pmap->pm_sref);
#endif
	}
I 18
#if 0
E 18
	/*
	 * Flush stale TLB info.
	 */
	if (pmap == kernel_pmap)
		TBIAS();
	else
		TBIAU();
I 18
#endif
E 18
	pmap->pm_ptpages++;
	splx(s);
}

#ifdef DEBUG
I 18
/* static */
void
E 18
pmap_pvdump(pa)
	vm_offset_t pa;
{
	register pv_entry_t pv;

	printf("pa %x", pa);
	for (pv = pa_to_pvh(pa); pv; pv = pv->pv_next)
		printf(" -> pmap %x, va %x, ptste %x, ptpmap %x, flags %x",
		       pv->pv_pmap, pv->pv_va, pv->pv_ptste, pv->pv_ptpmap,
		       pv->pv_flags);
	printf("\n");
}

I 18
/* static */
void
E 18
pmap_check_wiring(str, va)
	char *str;
	vm_offset_t va;
{
	vm_map_entry_t entry;
	register int count, *pte;

	va = trunc_page(va);
D 12
	if (!pmap_ste_v(pmap_ste(kernel_pmap, va)) ||
E 12
I 12
	if (!pmap_ste_v(kernel_pmap, va) ||
E 12
	    !pmap_pte_v(pmap_pte(kernel_pmap, va)))
		return;

	if (!vm_map_lookup_entry(pt_map, va, &entry)) {
		printf("wired_check: entry for %x not found\n", va);
		return;
	}
	count = 0;
	for (pte = (int *)va; pte < (int *)(va+PAGE_SIZE); pte++)
		if (*pte)
			count++;
	if (entry->wired_count != count)
		printf("*%s*: %x: w%d/a%d\n",
		       str, va, entry->wired_count, count);
}
#endif
E 1
