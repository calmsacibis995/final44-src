h31185
s 00001/00001/01455
d D 8.5 95/06/02 17:25:20 ralph 20 19
c final changes for pmax 4.4-Lite II release
e
s 00008/00002/01448
d D 8.4 94/01/26 21:14:13 mckusick 19 18
c allocate enough kernel virtual space since some tables increased in size
c (from Ralph)
e
s 00006/00005/01444
d D 8.3 94/01/11 16:05:10 mckusick 18 17
c fix page allocating to use new list macros (from Ralph)
e
s 00001/00001/01448
d D 8.2 93/09/23 16:38:06 bostic 17 16
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/01447
d D 8.1 93/06/10 23:07:42 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00388/00542/01061
d D 7.14 93/05/09 17:59:07 ralph 15 14
c new improved pmap changes
e
s 00001/00004/01602
d D 7.13 93/04/05 21:41:43 ralph 14 13
c fix mmap for devices.
e
s 00003/00003/01603
d D 7.12 92/10/24 14:15:43 ralph 13 12
c changes for vm_page->flags.
e
s 00009/00009/01597
d D 7.11 92/10/11 11:23:21 bostic 12 11
c make kernel includes standard
e
s 00001/00001/01605
d D 7.10 92/07/27 21:29:21 ralph 11 10
c fix warning for allproc
e
s 00131/00059/01475
d D 7.9 92/05/28 14:40:23 mckusick 10 9
c speed cache lookups (from Macklem)
e
s 00002/00002/01532
d D 7.8 92/05/16 16:55:03 ralph 9 8
c fix flushing cache for text pages. undo mem->clean 'fix'.
e
s 00001/00001/01533
d D 7.7 92/05/15 16:19:32 mckusick 8 7
c fix from Macklem
e
s 00001/00001/01533
d D 7.6 92/05/11 18:15:38 mckusick 7 5
c fix to avoid pageout of text pages back to their binaries (from macklem and ralph)
e
s 00002/00000/01534
d R 7.6 92/05/11 18:04:06 mckusick 6 5
c fix to avoid pageout of text pages back to their binaries (from macklem)
e
s 00000/00002/01534
d D 7.5 92/05/11 17:32:31 mckusick 5 4
c avoid stale caches (from macklem, approved by ralp)
e
s 00032/00029/01504
d D 7.4 92/03/14 13:48:50 ralph 4 3
c cleanup code & fix a KSEG0 addr being used for phys addr.
e
s 00087/00045/01446
d D 7.3 92/02/29 13:57:24 ralph 3 2
c fix cache problem by using correct phys addr in ptes
e
s 00001/00007/01490
d D 7.2 92/02/19 18:41:07 mckusick 2 1
c eliminate variable kernel_pmap and function pmap_kernel
e
s 01497/00000/00000
d D 7.1 92/01/07 17:29:22 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/* 
D 16
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
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

D 12
#include "param.h"
#include "proc.h"
#include "malloc.h"
#include "user.h"
E 12
I 12
#include <sys/param.h>
I 15
#include <sys/systm.h>
E 15
#include <sys/proc.h>
#include <sys/malloc.h>
#include <sys/user.h>
I 15
#include <sys/buf.h>
I 19
#ifdef SYSVSHM
#include <sys/shm.h>
#endif
E 19
E 15
E 12

D 12
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
E 12
I 12
D 15
#include <vm/vm.h>
E 15
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
I 15
#include <vm/vm_pageout.h>
E 15
E 12

D 12
#include "../include/machConst.h"
D 3
#include "pte.h"
E 3
I 3
#include "../include/pte.h"
E 12
I 12
#include <machine/machConst.h>
#include <machine/pte.h>
E 12
E 3

I 15
extern vm_page_t vm_page_alloc1 __P((void));
extern void vm_page_free1 __P((vm_page_t));

E 15
/*
 * For each vm_page_t, there is a list of all currently valid virtual
 * mappings of that page.  An entry is a pv_entry_t, the list is pv_table.
 * XXX really should do this as a part of the higher level code.
 */
typedef struct pv_entry {
	struct pv_entry	*pv_next;	/* next pv_entry */
	struct pmap	*pv_pmap;	/* pmap where mapping lies */
	vm_offset_t	pv_va;		/* virtual address for mapping */
D 4
	int		pv_flags;	/* flags */
E 4
} *pv_entry_t;

pv_entry_t	pv_table;	/* array of entries, one per page */
extern void	pmap_remove_pv();

#define pa_index(pa)		atop((pa) - first_phys_addr)
#define pa_to_pvh(pa)		(&pv_table[pa_index(pa)])

#ifdef DEBUG
struct {
	int kernel;	/* entering kernel mapping */
	int user;	/* entering user mapping */
	int ptpneeded;	/* needed to allocate a PT page */
	int pwchange;	/* no mapping change, just wiring or protection */
	int wchange;	/* no mapping change, just wiring */
	int mchange;	/* was mapped but mapping to different page */
	int managed;	/* a managed page */
	int firstpv;	/* first mapping for this PA */
	int secondpv;	/* second mapping for this PA */
	int ci;		/* cache inhibited */
	int unmanaged;	/* not a managed page */
	int flushes;	/* cache flushes */
	int cachehit;	/* new entry forced valid entry out */
} enter_stats;
struct {
	int calls;
	int removes;
	int flushes;
	int pidflushes;	/* HW pid stolen */
	int pvfirst;
	int pvsearch;
} remove_stats;

int pmapdebug;
#define PDB_FOLLOW	0x0001
#define PDB_INIT	0x0002
#define PDB_ENTER	0x0004
#define PDB_REMOVE	0x0008
#define PDB_CREATE	0x0010
#define PDB_PTPAGE	0x0020
D 15
#define PDB_CACHE	0x0040
E 15
I 15
#define PDB_PVENTRY	0x0040
E 15
#define PDB_BITS	0x0080
#define PDB_COLLECT	0x0100
#define PDB_PROTECT	0x0200
#define PDB_TLBPID	0x0400
#define PDB_PARANOIA	0x2000
#define PDB_WIRING	0x4000
#define PDB_PVDUMP	0x8000

#endif /* DEBUG */

D 15
u_int	whichpids[2] = {	/* bit mask of hardware PID's in use */
	3, 0
};

E 15
struct pmap	kernel_pmap_store;
D 2
pmap_t		kernel_pmap;
E 2
D 15
pmap_t		cur_pmap;	/* current pmap mapped in hardware */
E 15

vm_offset_t    	avail_start;	/* PA of first available physical page */
vm_offset_t	avail_end;	/* PA of last available physical page */
vm_size_t	mem_size;	/* memory size in bytes */
vm_offset_t	virtual_avail;  /* VA of first avail page (after kernel bss)*/
vm_offset_t	virtual_end;	/* VA of last avail page (end of kernel AS) */
int		pmaxpagesperpage;	/* PAGE_SIZE / NBPG */
#ifdef ATTR
char		*pmap_attributes;	/* reference and modify bits */
#endif
D 15
pmap_hash_t	zero_pmap_hash;		/* empty TLB hash table for init */
E 15
I 15
struct segtab	*free_segtab;		/* free list kept locally */
u_int		tlbpid_gen = 1;		/* TLB PID generation count */
int		tlbpid_cnt = 2;		/* next available TLB PID */
pt_entry_t	*Sysmap;		/* kernel pte table */
u_int		Sysmapsize;		/* number of pte's in Sysmap */
E 15

/*
 *	Bootstrap the system enough to run with virtual memory.
I 15
 *	firstaddr is the first unused kseg0 address (not page aligned).
E 15
 */
void
pmap_bootstrap(firstaddr)
	vm_offset_t firstaddr;
{
	register int i;
	vm_offset_t start = firstaddr;
I 3
D 4
	vm_offset_t pa;
E 4
E 3
	extern int maxmem, physmem;

I 15
#define	valloc(name, type, num) \
	    (name) = (type *)firstaddr; firstaddr = (vm_offset_t)((name)+(num))
E 15
	/*
D 15
	 * Allocate a TLB hash table for the kernel.
	 * This could be a KSEG0 address and thus save TLB entries but
	 * its faster and simpler in assembly language to have a
	 * fixed address that can be accessed with a 16 bit signed offset.
	 * Note: the kernel pm_hash field is null, user pm_hash fields are
	 * either the table or zero_pmap_hash.
E 15
I 15
	 * Allocate a PTE table for the kernel.
D 19
	 * The first '256' comes from PAGER_MAP_SIZE in vm_pager_init().
E 19
I 19
	 * The '1024' comes from PAGER_MAP_SIZE in vm_pager_init().
E 19
	 * This should be kept in sync.
	 * We also reserve space for kmem_alloc_pageable() for vm_fork().
E 15
	 */
D 15
	kernel_pmap_store.pm_hash = (pmap_hash_t)0;
	for (i = 0; i < PMAP_HASH_KPAGES; i++) {
		MachTLBWriteIndexed(i + UPAGES + PMAP_HASH_UPAGES,
			PMAP_HASH_KADDR + (i << PGSHIFT),
			firstaddr | PG_V | PG_M | PG_G);
		firstaddr += NBPG;
	}

E 15
I 15
	Sysmapsize = (VM_KMEM_SIZE + VM_MBUF_SIZE + VM_PHYS_SIZE +
D 19
		nbuf * MAXBSIZE + 16 * NCARGS) / NBPG + 256 + 256;
E 19
I 19
		nbuf * MAXBSIZE + 16 * NCARGS) / NBPG + 1024 + 256;
#ifdef SYSVSHM
	Sysmapsize += shminfo.shmall;
#endif
E 19
	valloc(Sysmap, pt_entry_t, Sysmapsize);
#ifdef ATTR
	valloc(pmap_attributes, char, physmem);
#endif
E 15
	/*
D 15
	 * Allocate an empty TLB hash table for initial pmap's.
	 */
D 3
	zero_pmap_hash = (pmap_hash_t)firstaddr;
E 3
I 3
	zero_pmap_hash = (pmap_hash_t)MACH_PHYS_TO_CACHED(firstaddr);
D 4
	pa = firstaddr;
E 3
	firstaddr += PMAP_HASH_UPAGES * NBPG;
E 4
 
	/* init proc[0]'s pmap hash table */
	for (i = 0; i < PMAP_HASH_UPAGES; i++) {
D 3
		kernel_pmap_store.pm_hash_ptes[i] =
			((u_int)zero_pmap_hash + (i << PGSHIFT)) | PG_V | PG_RO;
E 3
I 3
D 4
		kernel_pmap_store.pm_hash_ptes[i] = pa | PG_V | PG_RO;
E 4
I 4
		kernel_pmap_store.pm_hash_ptes[i] = firstaddr | PG_V | PG_RO;
E 4
E 3
		MachTLBWriteIndexed(i + UPAGES,
			(PMAP_HASH_UADDR + (i << PGSHIFT)) |
				(1 << VMMACH_TLB_PID_SHIFT),
			kernel_pmap_store.pm_hash_ptes[i]);
I 3
D 4
		pa += NBPG;
E 4
I 4
		firstaddr += NBPG;
E 4
E 3
	}

	/*
E 15
	 * Allocate memory for pv_table.
	 * This will allocate more entries than we really need.
D 15
	 * We should do this in pmap_init when we know the actual
	 * phys_start and phys_end but its better to use phys addresses
E 15
I 15
	 * We could do this in pmap_init when we know the actual
	 * phys_start and phys_end but its better to use kseg0 addresses
E 15
	 * rather than kernel virtual addresses mapped through the TLB.
	 */
D 15
	i = (maxmem - pmax_btop(firstaddr)) * sizeof(struct pv_entry);
	i = pmax_round_page(i);
D 3
	pv_table = (pv_entry_t)firstaddr;
E 3
I 3
	pv_table = (pv_entry_t)MACH_PHYS_TO_CACHED(firstaddr);
E 3
	firstaddr += i;
E 15
I 15
	i = maxmem - pmax_btop(MACH_CACHED_TO_PHYS(firstaddr));
	valloc(pv_table, struct pv_entry, i);
E 15

	/*
	 * Clear allocated memory.
	 */
D 3
	bzero((caddr_t)start, firstaddr - start);
E 3
I 3
D 15
	bzero((caddr_t)MACH_PHYS_TO_CACHED(start), firstaddr - start);
E 15
I 15
	firstaddr = pmax_round_page(firstaddr);
	bzero((caddr_t)start, firstaddr - start);
E 15
E 3

D 15
	avail_start = firstaddr;
E 15
I 15
	avail_start = MACH_CACHED_TO_PHYS(firstaddr);
E 15
	avail_end = pmax_ptob(maxmem);
	mem_size = avail_end - avail_start;

	virtual_avail = VM_MIN_KERNEL_ADDRESS;
D 15
	virtual_end = VM_MIN_KERNEL_ADDRESS + PMAP_HASH_KPAGES * NPTEPG * NBPG;
E 15
I 15
	virtual_end = VM_MIN_KERNEL_ADDRESS + Sysmapsize * NBPG;
E 15
	/* XXX need to decide how to set cnt.v_page_size */
	pmaxpagesperpage = 1;

D 2
	/*
	 * The kernel's pmap is statically allocated so we don't
	 * have to use pmap_create, which is unlikely to work
	 * correctly at this part of the boot sequence.
	 */
	kernel_pmap = cur_pmap = &kernel_pmap_store;
E 2
I 2
D 15
	cur_pmap = &kernel_pmap_store;
E 15
E 2
D 4
	simple_lock_init(&kernel_pmap->pm_lock);
	kernel_pmap->pm_count = 1;
E 4
I 4
	simple_lock_init(&kernel_pmap_store.pm_lock);
	kernel_pmap_store.pm_count = 1;
E 4
}

/*
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
pmap_bootstrap_alloc(size)
	int size;
{
	vm_offset_t val;
	extern boolean_t vm_page_startup_initialized;

	if (vm_page_startup_initialized)
		panic("pmap_bootstrap_alloc: called after startup initialized");

D 3
	val = avail_start;
E 3
I 3
	val = MACH_PHYS_TO_CACHED(avail_start);
E 3
	size = round_page(size);
	avail_start += size;

D 3
	blkclr((caddr_t) val, size);
	return ((void *) val);
E 3
I 3
	blkclr((caddr_t)val, size);
	return ((void *)val);
E 3
}

/*
 *	Initialize the pmap module.
 *	Called by vm_init, to initialize any structures that the pmap
 *	system needs to map virtual memory.
 */
void
pmap_init(phys_start, phys_end)
	vm_offset_t phys_start, phys_end;
{

#ifdef DEBUG
D 15
	if (pmapdebug & PDB_FOLLOW)
E 15
I 15
	if (pmapdebug & (PDB_FOLLOW|PDB_INIT))
E 15
		printf("pmap_init(%x, %x)\n", phys_start, phys_end);
#endif
}

/*
D 15
 *	Used to map a range of physical addresses into kernel
 *	virtual address space.
 *
 *	This routine should only be called by vm_page_startup()
 *	with KSEG0 addresses.
 */
vm_offset_t
pmap_map(virt, start, end, prot)
	vm_offset_t virt;
	vm_offset_t start;
	vm_offset_t end;
	int prot;
{

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_map(%x, %x, %x, %x)\n", virt, start, end, prot);
#endif

D 3
	return(round_page(end));
E 3
I 3
	return (round_page(end));
E 3
}

/*
E 15
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
	vm_size_t size;
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
D 3
		return(NULL);
E 3
I 3
		return (NULL);
E 3

D 15
	printf("pmap_create(%x) XXX\n", size); /* XXX */
E 15
	/* XXX: is it ok to wait here? */
	pmap = (pmap_t) malloc(sizeof *pmap, M_VMPMAP, M_WAITOK);
#ifdef notifwewait
	if (pmap == NULL)
		panic("pmap_create: cannot allocate a pmap");
#endif
	bzero(pmap, sizeof(*pmap));
	pmap_pinit(pmap);
	return (pmap);
}

/*
 * Initialize a preallocated and zeroed pmap structure,
 * such as one in a vmspace structure.
 */
void
pmap_pinit(pmap)
	register struct pmap *pmap;
{
	register int i;
I 15
	int s;
E 15
	extern struct vmspace vmspace0;
I 15
	extern struct user *proc0paddr;
E 15

#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_CREATE))
		printf("pmap_pinit(%x)\n", pmap);
#endif
	simple_lock_init(&pmap->pm_lock);
	pmap->pm_count = 1;
D 15
	pmap->pm_flags = 0;
	pmap->pm_hash = zero_pmap_hash;
	for (i = 0; i < PMAP_HASH_UPAGES; i++)
		pmap->pm_hash_ptes[i] =
D 4
			((u_int)zero_pmap_hash + (i << PGSHIFT)) | PG_V | PG_RO;
E 4
I 4
			(MACH_CACHED_TO_PHYS(zero_pmap_hash) + (i << PGSHIFT)) |
				PG_V | PG_RO;
E 4
	if (pmap == &vmspace0.vm_pmap)
		pmap->pm_tlbpid = 1;	/* preallocated in mach_init() */
	else
		pmap->pm_tlbpid = -1;	/* none allocated yet */
E 15
I 15
	if (free_segtab) {
		s = splimp();
		pmap->pm_segtab = free_segtab;
		free_segtab = *(struct segtab **)free_segtab;
		pmap->pm_segtab->seg_tab[0] = NULL;
		splx(s);
	} else {
		register struct segtab *stp;
		vm_page_t mem;

		mem = vm_page_alloc1();
		pmap_zero_page(VM_PAGE_TO_PHYS(mem));
		pmap->pm_segtab = stp = (struct segtab *)
			MACH_PHYS_TO_CACHED(VM_PAGE_TO_PHYS(mem));
		i = pmaxpagesperpage * (NBPG / sizeof(struct segtab));
		s = splimp();
		while (--i != 0) {
			stp++;
			*(struct segtab **)stp = free_segtab;
			free_segtab = stp;
		}
		splx(s);
	}
#ifdef DIAGNOSTIC
	for (i = 0; i < PMAP_SEGTABSIZE; i++)
		if (pmap->pm_segtab->seg_tab[i] != 0)
			panic("pmap_pinit: pm_segtab != 0");
#endif
	if (pmap == &vmspace0.vm_pmap) {
		/*
		 * The initial process has already been allocated a TLBPID
		 * in mach_init().
		 */
		pmap->pm_tlbpid = 1;
		pmap->pm_tlbgen = tlbpid_gen;
		proc0paddr->u_pcb.pcb_segtab = (void *)pmap->pm_segtab;
	} else {
		pmap->pm_tlbpid = 0;
		pmap->pm_tlbgen = 0;
	}
E 15
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
D 15
	if (pmapdebug & PDB_FOLLOW)
E 15
I 15
	if (pmapdebug & (PDB_FOLLOW|PDB_CREATE))
E 15
		printf("pmap_destroy(%x)\n", pmap);
#endif
	if (pmap == NULL)
		return;

D 15
	printf("pmap_destroy(%x) XXX\n", pmap); /* XXX */
E 15
	simple_lock(&pmap->pm_lock);
	count = --pmap->pm_count;
	simple_unlock(&pmap->pm_lock);
	if (count == 0) {
		pmap_release(pmap);
		free((caddr_t)pmap, M_VMPMAP);
	}
}

/*
 * Release any resources held by the given physical map.
 * Called when a pmap initialized by pmap_pinit is being released.
 * Should only be called if the map contains no valid mappings.
 */
void
pmap_release(pmap)
	register pmap_t pmap;
{
D 15
	register int id;
#ifdef DIAGNOSTIC
	register int i;
#endif
E 15

#ifdef DEBUG
D 15
	if (pmapdebug & PDB_FOLLOW)
E 15
I 15
	if (pmapdebug & (PDB_FOLLOW|PDB_CREATE))
E 15
		printf("pmap_release(%x)\n", pmap);
#endif

D 15
	if (pmap->pm_hash && pmap->pm_hash != zero_pmap_hash) {
		kmem_free(kernel_map, (vm_offset_t)pmap->pm_hash,
			PMAP_HASH_SIZE);
		pmap->pm_hash = zero_pmap_hash;
	}
	if ((id = pmap->pm_tlbpid) < 0)
		return;
E 15
I 15
	if (pmap->pm_segtab) {
		register pt_entry_t *pte;
		register int i;
		int s;
E 15
#ifdef DIAGNOSTIC
D 15
	if (!(whichpids[id >> 5] & (1 << (id & 0x1F))))
		panic("pmap_release: id free");
E 15
I 15
		register int j;
E 15
#endif
D 15
	MachTLBFlushPID(id);
	whichpids[id >> 5] &= ~(1 << (id & 0x1F));
	pmap->pm_flags &= ~PM_MODIFIED;
	pmap->pm_tlbpid = -1;
	if (pmap == cur_pmap)
		cur_pmap = (pmap_t)0;
E 15
I 15

		for (i = 0; i < PMAP_SEGTABSIZE; i++) {
			/* get pointer to segment map */
			pte = pmap->pm_segtab->seg_tab[i];
			if (!pte)
				continue;
			vm_page_free1(
				PHYS_TO_VM_PAGE(MACH_CACHED_TO_PHYS(pte)));
E 15
#ifdef DIAGNOSTIC
D 15
	/* invalidate user PTE cache */
	for (i = 0; i < PMAP_HASH_UPAGES; i++)
		MachTLBWriteIndexed(i + UPAGES, MACH_RESERVED_ADDR, 0);
E 15
I 15
			for (j = 0; j < NPTEPG; j++) {
				if (pte->pt_entry)
					panic("pmap_release: segmap not empty");
			}
E 15
#endif
I 15
			pmap->pm_segtab->seg_tab[i] = NULL;
		}
		s = splimp();
		*(struct segtab **)pmap->pm_segtab = free_segtab;
		free_segtab = pmap->pm_segtab;
		splx(s);
		pmap->pm_segtab = NULL;
	}
E 15
}

/*
 *	Add a reference to the specified pmap.
 */
void
pmap_reference(pmap)
	pmap_t pmap;
{

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_reference(%x)\n", pmap);
#endif
	if (pmap != NULL) {
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
	vm_offset_t sva, eva;
{
D 15
	register vm_offset_t va;
	register pv_entry_t pv, npv;
I 10
	register int i;
E 10
	pmap_hash_t hp;
E 15
I 15
	register vm_offset_t nssva;
	register pt_entry_t *pte;
E 15
	unsigned entry;

#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_REMOVE|PDB_PROTECT))
		printf("pmap_remove(%x, %x, %x)\n", pmap, sva, eva);
	remove_stats.calls++;
#endif
	if (pmap == NULL)
		return;

D 15
	/* anything in the cache? */
	if (pmap->pm_tlbpid < 0 || pmap->pm_hash == zero_pmap_hash)
		return;

	if (!pmap->pm_hash) {
E 15
I 15
	if (!pmap->pm_segtab) {
E 15
		register pt_entry_t *pte;

		/* remove entries from kernel pmap */
I 3
#ifdef DIAGNOSTIC
D 15
		if (sva < VM_MIN_KERNEL_ADDRESS ||
		    eva > VM_MIN_KERNEL_ADDRESS + PMAP_HASH_KPAGES*NPTEPG*NBPG)
			panic("pmap_remove");
E 15
I 15
		if (sva < VM_MIN_KERNEL_ADDRESS || eva > virtual_end)
			panic("pmap_remove: kva not in range");
E 15
#endif
E 3
		pte = kvtopte(sva);
D 15
		for (va = sva; va < eva; va += NBPG, pte++) {
E 15
I 15
		for (; sva < eva; sva += NBPG, pte++) {
E 15
			entry = pte->pt_entry;
			if (!(entry & PG_V))
				continue;
			if (entry & PG_WIRED)
				pmap->pm_stats.wired_count--;
			pmap->pm_stats.resident_count--;
D 15
			pmap_remove_pv(pmap, va, entry & PG_FRAME);
E 15
I 15
			pmap_remove_pv(pmap, sva, entry & PG_FRAME);
E 15
#ifdef ATTR
D 15
			pmap_attributes[atop(entry - KERNBASE)] = 0;
E 15
I 15
			pmap_attributes[atop(entry & PG_FRAME)] = 0;
E 15
#endif
			pte->pt_entry = PG_NV;
			/*
			 * Flush the TLB for the given address.
			 */
D 15
			MachTLBFlushAddr(va);
E 15
I 15
			MachTLBFlushAddr(sva);
E 15
#ifdef DEBUG
			remove_stats.flushes++;
#endif
		}
		return;
	}

D 15
	va = sva | (pmap->pm_tlbpid << VMMACH_TLB_PID_SHIFT);
	eva |= (pmap->pm_tlbpid << VMMACH_TLB_PID_SHIFT);
	/*
	 * If we are not in the current address space, just flush the
	 * software cache and not the hardware.
	 */
	if (pmap != cur_pmap) {
		for (; va < eva; va += NBPG) {
			hp = &pmap->pm_hash[PMAP_HASH(va)];
D 10
			if (hp->high != va)
E 10
I 10
			if (hp->pmh_pte[0].high == va)
				i = 0;
			else if (hp->pmh_pte[1].high == va)
				i = 1;
			else
E 15
I 15
#ifdef DIAGNOSTIC
	if (eva > VM_MAXUSER_ADDRESS)
		panic("pmap_remove: uva not in range");
#endif
	while (sva < eva) {
		nssva = pmax_trunc_seg(sva) + NBSEG;
		if (nssva == 0 || nssva > eva)
			nssva = eva;
		/*
		 * If VA belongs to an unallocated segment,
		 * skip to the next segment boundary.
		 */
		if (!(pte = pmap_segmap(pmap, sva))) {
			sva = nssva;
			continue;
		}
		/*
		 * Invalidate every valid mapping within this segment.
		 */
		pte += (sva >> PGSHIFT) & (NPTEPG - 1);
		for (; sva < nssva; sva += NBPG, pte++) {
			entry = pte->pt_entry;
			if (!(entry & PG_V))
E 15
E 10
				continue;
D 15

D 10
			hp->high = 0;
			entry = hp->low;
E 10
I 10
			hp->pmh_pte[i].high = 0;
			entry = hp->pmh_pte[i].low;
E 15
E 10
			if (entry & PG_WIRED)
				pmap->pm_stats.wired_count--;
			pmap->pm_stats.resident_count--;
D 15
			pmap_remove_pv(pmap, va & PG_FRAME, entry & PG_FRAME);
E 15
I 15
			pmap_remove_pv(pmap, sva, entry & PG_FRAME);
E 15
#ifdef ATTR
D 15
			pmap_attributes[atop(entry - KERNBASE)] = 0;
E 15
I 15
			pmap_attributes[atop(entry & PG_FRAME)] = 0;
E 15
#endif
D 15
			pmap->pm_flags |= PM_MODIFIED;
E 15
I 15
			pte->pt_entry = PG_NV;
			/*
			 * Flush the TLB for the given address.
			 */
			if (pmap->pm_tlbgen == tlbpid_gen) {
				MachTLBFlushAddr(sva | (pmap->pm_tlbpid <<
					VMMACH_TLB_PID_SHIFT));
E 15
#ifdef DEBUG
D 15
			remove_stats.removes++;
E 15
I 15
				remove_stats.flushes++;
E 15
#endif
I 15
			}
E 15
		}
D 15
		return;
E 15
	}
D 15

	for (; va < eva; va += NBPG) {
		hp = &pmap->pm_hash[PMAP_HASH(va)];
D 10
		if (hp->high != va)
E 10
I 10
		if (hp->pmh_pte[0].high == va)
			i = 0;
		else if (hp->pmh_pte[1].high == va)
			i = 1;
		else
E 10
			continue;

D 10
		hp->high = 0;
		entry = hp->low;
E 10
I 10
		hp->pmh_pte[i].high = 0;
		entry = hp->pmh_pte[i].low;
E 10
		if (entry & PG_WIRED)
			pmap->pm_stats.wired_count--;
		pmap->pm_stats.resident_count--;
		pmap_remove_pv(pmap, va & PG_FRAME, entry & PG_FRAME);
#ifdef ATTR
		pmap_attributes[atop(entry - KERNBASE)] = 0;
#endif
		/*
D 10
		 * Flush the TLB for the given address.
		 */
E 10
I 10
		* Flush the TLB for the given address.
		*/
E 10
		MachTLBFlushAddr(va);
#ifdef DEBUG
		remove_stats.flushes++;
#endif
	}
E 15
}

/*
 *	pmap_page_protect:
 *
 *	Lower the permission for all mappings to a given page.
 */
void
pmap_page_protect(pa, prot)
	vm_offset_t pa;
	vm_prot_t prot;
{
	register pv_entry_t pv;
	register vm_offset_t va;
	int s;

#ifdef DEBUG
	if ((pmapdebug & (PDB_FOLLOW|PDB_PROTECT)) ||
	    prot == VM_PROT_NONE && (pmapdebug & PDB_REMOVE))
		printf("pmap_page_protect(%x, %x)\n", pa, prot);
#endif
	if (!IS_VM_PHYSADDR(pa))
		return;

	switch (prot) {
I 15
	case VM_PROT_READ|VM_PROT_WRITE:
E 15
	case VM_PROT_ALL:
		break;

	/* copy_on_write */
	case VM_PROT_READ:
	case VM_PROT_READ|VM_PROT_EXECUTE:
		pv = pa_to_pvh(pa);
		s = splimp();
		/*
		 * Loop over all current mappings setting/clearing as appropos.
		 */
		if (pv->pv_pmap != NULL) {
			for (; pv; pv = pv->pv_next) {
				extern vm_offset_t pager_sva, pager_eva;
I 15

E 15
				va = pv->pv_va;

				/*
				 * XXX don't write protect pager mappings
				 */
				if (va >= pager_sva && va < pager_eva)
					continue;
				pmap_protect(pv->pv_pmap, va, va + PAGE_SIZE,
					prot);
			}
		}
		splx(s);
		break;

	/* remove_all */
	default:
		pv = pa_to_pvh(pa);
		s = splimp();
		while (pv->pv_pmap != NULL) {
			pmap_remove(pv->pv_pmap, pv->pv_va,
				    pv->pv_va + PAGE_SIZE);
		}
		splx(s);
	}
}

/*
 *	Set the physical protection on the
 *	specified range of this map as requested.
 */
void
pmap_protect(pmap, sva, eva, prot)
	register pmap_t pmap;
	vm_offset_t sva, eva;
	vm_prot_t prot;
{
D 15
	register vm_offset_t va;
I 10
	register int i;
E 10
	pmap_hash_t hp;
E 15
I 15
	register vm_offset_t nssva;
	register pt_entry_t *pte;
	register unsigned entry;
E 15
	u_int p;

#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_PROTECT))
		printf("pmap_protect(%x, %x, %x, %x)\n", pmap, sva, eva, prot);
#endif
	if (pmap == NULL)
		return;

D 15
	/* anything in the software cache? */
	if (pmap->pm_tlbpid < 0 || pmap->pm_hash == zero_pmap_hash)
		return;

	if (!(prot & VM_PROT_READ)) {
E 15
I 15
	if ((prot & VM_PROT_READ) == VM_PROT_NONE) {
E 15
		pmap_remove(pmap, sva, eva);
		return;
	}

D 15
	if (!pmap->pm_hash) {
		register pt_entry_t *pte;
E 15
I 15
	p = (prot & VM_PROT_WRITE) ? PG_RW : PG_RO;
E 15

I 15
	if (!pmap->pm_segtab) {
E 15
		/*
		 * Change entries in kernel pmap.
		 * This will trap if the page is writeable (in order to set
		 * the dirty bit) even if the dirty bit is already set. The
		 * optimization isn't worth the effort since this code isn't
		 * executed much. The common case is to make a user page
		 * read-only.
		 */
I 3
#ifdef DIAGNOSTIC
D 15
		if (sva < VM_MIN_KERNEL_ADDRESS ||
		    eva > VM_MIN_KERNEL_ADDRESS + PMAP_HASH_KPAGES*NPTEPG*NBPG)
			panic("pmap_protect");
E 15
I 15
		if (sva < VM_MIN_KERNEL_ADDRESS || eva > virtual_end)
			panic("pmap_protect: kva not in range");
E 15
#endif
E 3
D 15
		p = (prot & VM_PROT_WRITE) ? PG_RW : PG_RO;
E 15
		pte = kvtopte(sva);
D 15
		for (va = sva; va < eva; va += NBPG, pte++) {
			if (!(pte->pt_entry & PG_V))
E 15
I 15
		for (; sva < eva; sva += NBPG, pte++) {
			entry = pte->pt_entry;
			if (!(entry & PG_V))
E 15
				continue;
D 15
			pte->pt_entry = (pte->pt_entry & ~(PG_M | PG_RO)) | p;
E 15
I 15
			entry = (entry & ~(PG_M | PG_RO)) | p;
			pte->pt_entry = entry;
E 15
			/*
			 * Update the TLB if the given address is in the cache.
			 */
D 15
			MachTLBUpdate(va, pte->pt_entry);
E 15
I 15
			MachTLBUpdate(sva, entry);
E 15
		}
		return;
	}

D 15
	p = (prot & VM_PROT_WRITE) ? PG_RW : PG_RO;
	va = sva | (pmap->pm_tlbpid << VMMACH_TLB_PID_SHIFT);
	eva |= (pmap->pm_tlbpid << VMMACH_TLB_PID_SHIFT);
	/*
	 * If we are not in the current address space, just flush the
	 * software cache and not the hardware.
	 */
	if (pmap != cur_pmap) {
		for (; va < eva; va += NBPG) {
			hp = &pmap->pm_hash[PMAP_HASH(va)];
D 10
			if (hp->high != va)
E 10
I 10
			if (hp->pmh_pte[0].high == va)
				i = 0;
			else if (hp->pmh_pte[1].high == va)
				i = 1;
			else
E 15
I 15
#ifdef DIAGNOSTIC
	if (eva > VM_MAXUSER_ADDRESS)
		panic("pmap_protect: uva not in range");
#endif
	while (sva < eva) {
		nssva = pmax_trunc_seg(sva) + NBSEG;
		if (nssva == 0 || nssva > eva)
			nssva = eva;
		/*
		 * If VA belongs to an unallocated segment,
		 * skip to the next segment boundary.
		 */
		if (!(pte = pmap_segmap(pmap, sva))) {
			sva = nssva;
			continue;
		}
		/*
		 * Change protection on every valid mapping within this segment.
		 */
		pte += (sva >> PGSHIFT) & (NPTEPG - 1);
		for (; sva < nssva; sva += NBPG, pte++) {
			entry = pte->pt_entry;
			if (!(entry & PG_V))
E 15
E 10
				continue;
D 15

D 10
			hp->low = (hp->low & ~(PG_M | PG_RO)) | p;
E 10
I 10
			hp->pmh_pte[i].low = (hp->pmh_pte[i].low & ~(PG_M | PG_RO)) | p;
E 10
			pmap->pm_flags |= PM_MODIFIED;
E 15
I 15
			entry = (entry & ~(PG_M | PG_RO)) | p;
			pte->pt_entry = entry;
			/*
			 * Update the TLB if the given address is in the cache.
			 */
			if (pmap->pm_tlbgen == tlbpid_gen)
				MachTLBUpdate(sva | (pmap->pm_tlbpid <<
					VMMACH_TLB_PID_SHIFT), entry);
E 15
		}
D 15
		return;
E 15
	}
D 15

	for (; va < eva; va += NBPG) {
		hp = &pmap->pm_hash[PMAP_HASH(va)];
D 10
		if (hp->high != va)
E 10
I 10
		if (hp->pmh_pte[0].high == va)
			i = 0;
		else if (hp->pmh_pte[1].high == va)
			i = 1;
		else
E 10
			continue;

D 10
		hp->low = (hp->low & ~(PG_M | PG_RO)) | p;
E 10
I 10
		hp->pmh_pte[i].low = (hp->pmh_pte[i].low & ~(PG_M | PG_RO)) | p;
E 10
		/*
D 10
		 * Update the TLB if the given address is in the cache.
		 */
		MachTLBUpdate(hp->high, hp->low);
E 10
I 10
		* Update the TLB if the given address is in the cache.
		*/
		MachTLBUpdate(hp->pmh_pte[i].high, hp->pmh_pte[i].low);
E 10
	}
E 15
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
D 15
	register pmap_hash_t hp;
E 15
I 15
	register pt_entry_t *pte;
E 15
	register u_int npte;
D 10
	register int i;
E 10
I 10
	register int i, j;
D 15
	int newpos;
E 15
I 15
	vm_page_t mem;
E 15
E 10

#ifdef DEBUG
	if (pmapdebug & (PDB_FOLLOW|PDB_ENTER))
		printf("pmap_enter(%x, %x, %x, %x, %x)\n",
		       pmap, va, pa, prot, wired);
#endif
#ifdef DIAGNOSTIC
	if (!pmap)
		panic("pmap_enter: pmap");
D 15
	if (pmap->pm_tlbpid < 0)
		panic("pmap_enter: tlbpid");
D 4
	if (pmap == kernel_pmap) {
E 4
I 4
	if (!pmap->pm_hash) {
E 15
I 15
	if (!pmap->pm_segtab) {
E 15
E 4
		enter_stats.kernel++;
D 4
		if ((va & 0xE0000000) != 0xC0000000)
E 4
I 4
D 15
		if (va < VM_MIN_KERNEL_ADDRESS ||
		    va >= VM_MIN_KERNEL_ADDRESS + PMAP_HASH_KPAGES*NPTEPG*NBPG)
E 15
I 15
		if (va < VM_MIN_KERNEL_ADDRESS || va >= virtual_end)
E 15
E 4
			panic("pmap_enter: kva");
	} else {
		enter_stats.user++;
D 15
		if (va & 0x80000000)
E 15
I 15
		if (va >= VM_MAXUSER_ADDRESS)
E 15
			panic("pmap_enter: uva");
	}
I 3
	if (pa & 0x80000000)
		panic("pmap_enter: pa");
E 3
	if (!(prot & VM_PROT_READ))
		panic("pmap_enter: prot");
#endif

D 15
	/*
	 * See if we need to create a new TLB cache.
	 */
	if (pmap->pm_hash == zero_pmap_hash) {
		register vm_offset_t kva;
		register pt_entry_t *pte;

		kva = kmem_alloc(kernel_map, PMAP_HASH_SIZE);
		pmap->pm_hash = (pmap_hash_t)kva;

		/*
		 * Convert the kernel virtual address to a physical one
		 * and cache it in the pmap. Note: if the phyical address
		 * can change (due to memory compaction in kmem_alloc?),
		 * we will have to update things.
		 */
		pte = kvtopte(kva);
		for (i = 0; i < PMAP_HASH_UPAGES; i++) {
			pmap->pm_hash_ptes[i] = pte->pt_entry & ~PG_G;
			pte++;
		}

		/*
		 * Map in new TLB cache if it is current.
		 */
		if (pmap == cur_pmap) {
D 4
#ifdef DIAGNOSTIC
			if (pmap->pm_tlbpid < 0)
				panic("pmap_enter: tlbpid");
#endif
E 4
			for (i = 0; i < PMAP_HASH_UPAGES; i++) {
				MachTLBWriteIndexed(i + UPAGES,
					(PMAP_HASH_UADDR + (i << PGSHIFT)) |
						(pmap->pm_tlbpid  <<
						VMMACH_TLB_PID_SHIFT),
					pmap->pm_hash_ptes[i]);
			}
		}
#ifdef DIAGNOSTIC
		for (i = 0; i < PAGE_SIZE; i += sizeof(int), kva += sizeof(int))
			if (*(int *)kva != 0)
				panic("pmap_enter: *kva != 0");
#endif
	}

E 15
	if (IS_VM_PHYSADDR(pa)) {
		register pv_entry_t pv, npv;
		int s;

		if (!(prot & VM_PROT_WRITE))
			npte = PG_RO;
		else {
			register vm_page_t mem;

			mem = PHYS_TO_VM_PAGE(pa);
			if ((int)va < 0) {
				/*
				 * Don't bother to trap on kernel writes,
				 * just record page as dirty.
				 */
				npte = PG_M;
D 7
				mem->clean = FALSE;
E 7
I 7
D 9
				mem->clean = TRUE;
E 9
I 9
D 13
				mem->clean = FALSE;
E 13
I 13
				mem->flags &= ~PG_CLEAN;
E 13
E 9
E 7
			} else
#ifdef ATTR
D 15
				if ((pmap_attributes[atop(pa - KERNBASE)] &
E 15
I 15
				if ((pmap_attributes[atop(pa)] &
E 15
D 13
				    PMAP_ATTR_MOD) || !mem->clean)
E 13
I 13
				    PMAP_ATTR_MOD) || !(mem->flags & PG_CLEAN))
E 13
#else
D 13
				if (!mem->clean)
E 13
I 13
				if (!(mem->flags & PG_CLEAN))
E 13
#endif
					npte = PG_M;
			else
				npte = 0;
		}

#ifdef DEBUG
		enter_stats.managed++;
#endif
		/*
		 * Enter the pmap and virtual address into the
		 * physical to virtual map table.
		 */
		pv = pa_to_pvh(pa);
		s = splimp();
#ifdef DEBUG
		if (pmapdebug & PDB_ENTER)
			printf("pmap_enter: pv %x: was %x/%x/%x\n",
			       pv, pv->pv_va, pv->pv_pmap, pv->pv_next);
#endif
		if (pv->pv_pmap == NULL) {
			/*
			 * No entries yet, use header as the first entry
			 */
#ifdef DEBUG
I 15
			if (pmapdebug & PDB_PVENTRY)
				printf("pmap_enter: first pv: pmap %x va %x\n",
					pmap, va);
E 15
			enter_stats.firstpv++;
#endif
			pv->pv_va = va;
			pv->pv_pmap = pmap;
			pv->pv_next = NULL;
D 4
			pv->pv_flags = 0;
E 4
		} else {
			/*
			 * There is at least one other VA mapping this page.
			 * Place this entry after the header.
			 *
			 * Note: the entry may already be in the table if
			 * we are only changing the protection bits.
			 */
			for (npv = pv; npv; npv = npv->pv_next)
				if (pmap == npv->pv_pmap && va == npv->pv_va) {
#ifdef DIAGNOSTIC
D 15
				    if (!pmap->pm_hash) {
E 15
					unsigned entry;

D 15
					entry = kvtopte(va)->pt_entry;
E 15
I 15
					if (!pmap->pm_segtab)
						entry = kvtopte(va)->pt_entry;
					else {
						pte = pmap_segmap(pmap, va);
						if (pte) {
							pte += (va >> PGSHIFT) &
							    (NPTEPG - 1);
							entry = pte->pt_entry;
						} else
							entry = 0;
					}
E 15
					if (!(entry & PG_V) ||
					    (entry & PG_FRAME) != pa)
D 15
			printf("found kva %x pa %x in pv_table but != %x\n",
				va, pa, entry);
				    } else {
					hp = &pmap->pm_hash[PMAP_HASH(va)];
D 10
					if (hp->high != (va |
					    (pmap->pm_tlbpid <<
					    VMMACH_TLB_PID_SHIFT)) ||
					    (hp->low & PG_FRAME) != pa)
			printf("found va %x pa %x in pv_table but != %x %x\n",
				va, pa, hp->high, hp->low);
E 10
I 10
					if ((hp->pmh_pte[0].high == (va |
					(pmap->pm_tlbpid <<
					VMMACH_TLB_PID_SHIFT)) &&
					(hp->pmh_pte[0].low & PG_FRAME) == pa) ||
					(hp->pmh_pte[1].high == (va |
					(pmap->pm_tlbpid <<
					VMMACH_TLB_PID_SHIFT)) &&
					(hp->pmh_pte[1].low & PG_FRAME) == pa))
						goto fnd;
			printf("found va %x pa %x in pv_table but !=\n",
				va, pa);
E 10
				    }
E 15
I 15
						printf(
			"pmap_enter: found va %x pa %x in pv_table but != %x\n",
							va, pa, entry);
E 15
#endif
					goto fnd;
				}
I 15
#ifdef DEBUG
			if (pmapdebug & PDB_PVENTRY)
				printf("pmap_enter: new pv: pmap %x va %x\n",
					pmap, va);
#endif
E 15
			/* can this cause us to recurse forever? */
			npv = (pv_entry_t)
				malloc(sizeof *npv, M_VMPVENT, M_NOWAIT);
			npv->pv_va = va;
			npv->pv_pmap = pmap;
			npv->pv_next = pv->pv_next;
			pv->pv_next = npv;
#ifdef DEBUG
			if (!npv->pv_next)
				enter_stats.secondpv++;
#endif
		fnd:
			;
		}
		splx(s);
	} else {
		/*
		 * Assumption: if it is not part of our managed memory
		 * then it must be device memory which may be volitile.
		 */
#ifdef DEBUG
		enter_stats.unmanaged++;
#endif
D 14
		printf("pmap_enter: UNMANAGED ADDRESS va %x pa %x\n",
			va, pa); /* XXX */
		npte = (prot & VM_PROT_WRITE) ? PG_M : PG_RO;
E 14
I 14
		npte = (prot & VM_PROT_WRITE) ? (PG_M | PG_N) : (PG_RO | PG_N);
E 14
	}

I 3
	/*
	 * The only time we need to flush the cache is if we
	 * execute from a physical address and then change the data.
	 * This is the best place to do this.
	 * pmap_protect() and pmap_remove() are mostly used to switch
	 * between R/W and R/O pages.
	 * NOTE: we only support cache flush for read only text.
	 */
D 5
#if 0
E 5
	if (prot == (VM_PROT_READ | VM_PROT_EXECUTE))
D 9
		MachFlushICache(MACH_PHYS_TO_UNCACHED(pa), PAGE_SIZE);
E 9
I 9
		MachFlushICache(MACH_PHYS_TO_CACHED(pa), PAGE_SIZE);
E 9
D 5
#endif
E 5

E 3
D 15
	if (!pmap->pm_hash) {
		register pt_entry_t *pte;

E 15
I 15
	if (!pmap->pm_segtab) {
E 15
		/* enter entries into kernel pmap */
		pte = kvtopte(va);
		npte |= pa | PG_V | PG_G;
		if (wired) {
			pmap->pm_stats.wired_count += pmaxpagesperpage;
			npte |= PG_WIRED;
		}
		i = pmaxpagesperpage;
		do {
			if (!(pte->pt_entry & PG_V)) {
				pmap->pm_stats.resident_count++;
D 15
				MachTLBWriteRandom(va, npte);
E 15
			} else {
I 4
#ifdef DIAGNOSTIC
				if (pte->pt_entry & PG_WIRED)
					panic("pmap_enter: kernel wired");
#endif
E 4
D 15
				/*
				 * Update the same virtual address entry.
				 */
				MachTLBUpdate(va, npte);
I 4
				printf("TLB update kva %x pte %x -> %x\n",
					va, pte->pt_entry, npte); /* XXX */
E 15
E 4
			}
I 15
			/*
			 * Update the same virtual address entry.
			 */
			MachTLBUpdate(va, npte);
E 15
			pte->pt_entry = npte;
			va += NBPG;
			npte += NBPG;
			pte++;
		} while (--i != 0);
		return;
	}

I 15
	if (!(pte = pmap_segmap(pmap, va))) {
		mem = vm_page_alloc1();
		pmap_zero_page(VM_PAGE_TO_PHYS(mem));
		pmap_segmap(pmap, va) = pte = (pt_entry_t *)
			MACH_PHYS_TO_CACHED(VM_PAGE_TO_PHYS(mem));
	}
	pte += (va >> PGSHIFT) & (NPTEPG - 1);

E 15
	/*
	 * Now validate mapping with desired protection/wiring.
	 * Assume uniform modified and referenced status for all
	 * PMAX pages in a MACH page.
	 */
	npte |= pa | PG_V;
	if (wired) {
		pmap->pm_stats.wired_count += pmaxpagesperpage;
		npte |= PG_WIRED;
	}
#ifdef DEBUG
D 15
	if (pmapdebug & PDB_ENTER)
		printf("pmap_enter: new pte value %x\n", npte);
E 15
I 15
	if (pmapdebug & PDB_ENTER) {
		printf("pmap_enter: new pte %x", npte);
		if (pmap->pm_tlbgen == tlbpid_gen)
			printf(" tlbpid %d", pmap->pm_tlbpid);
		printf("\n");
	}
E 15
#endif
D 15
	va |= (pmap->pm_tlbpid << VMMACH_TLB_PID_SHIFT);
E 15
	i = pmaxpagesperpage;
	do {
D 15
		hp = &pmap->pm_hash[PMAP_HASH(va)];
D 10
		if (!hp->high) {
E 10
I 10
		if (hp->pmh_pte[0].high == va &&
		    (hp->pmh_pte[0].low & PG_FRAME) == (npte & PG_FRAME))
			j = 0;
		else if (hp->pmh_pte[1].high == va &&
		    (hp->pmh_pte[1].low & PG_FRAME) == (npte & PG_FRAME))
			j = 1;
		else
			j = -1;
		if (j >= 0) {
#ifdef DEBUG
			enter_stats.cachehit++;
#endif
			if (!(hp->pmh_pte[j].low & PG_WIRED)) {
				/*
				 * Update the same entry.
				 */
				hp->pmh_pte[j].low = npte;
				MachTLBUpdate(va, npte);
			} else {
				/*
				 * Don't replace wired entries, just update
				 * the hardware TLB.
				 * Bug: routines to flush the TLB won't know
				 * that the entry is in the hardware.
				 */
				printf("pmap_enter: wired va %x %x\n", va,
					hp->pmh_pte[j].low); /* XXX */
				panic("pmap_enter: wired"); /* XXX */
				MachTLBWriteRandom(va, npte);
			}
			goto next;
		}
		if (!hp->pmh_pte[0].high)
			j = 0;
		else if (!hp->pmh_pte[1].high)
			j = 1;
		else
			j = -1;
		if (j >= 0) {
E 10
			pmap->pm_stats.resident_count++;
D 10
			hp->high = va;
			hp->low = npte;
E 10
I 10
			hp->pmh_pte[j].high = va;
			hp->pmh_pte[j].low = npte;
E 10
			MachTLBWriteRandom(va, npte);
		} else {
#ifdef DEBUG
			enter_stats.cachehit++;
#endif
D 4
			if (hp->high == va) {
				/*
				 * Update the same entry.
				 */
				hp->low = npte;
				MachTLBUpdate(va, npte);
			} else if (!(hp->low & PG_WIRED)) {
				MachTLBFlushAddr(hp->high);
				pmap_remove_pv(pmap, hp->high & PG_FRAME,
					hp->low & PG_FRAME);
				hp->high = va;
				hp->low = npte;
				MachTLBWriteRandom(va, npte);
E 4
I 4
D 10
			if (!(hp->low & PG_WIRED)) {
				if (hp->high == va &&
				    (hp->low & PG_FRAME) == (npte & PG_FRAME)) {
					/*
					 * Update the same entry.
					 */
					hp->low = npte;
					MachTLBUpdate(va, npte);
				} else {
					MachTLBFlushAddr(hp->high);
					pmap_remove_pv(pmap,
						hp->high & PG_FRAME,
						hp->low & PG_FRAME);
					hp->high = va;
					hp->low = npte;
					MachTLBWriteRandom(va, npte);
				}
E 10
I 10
			if (!(hp->pmh_pte[1].low & PG_WIRED)) {
				MachTLBFlushAddr(hp->pmh_pte[1].high);
				pmap_remove_pv(pmap,
					hp->pmh_pte[1].high & PG_FRAME,
					hp->pmh_pte[1].low & PG_FRAME);
				hp->pmh_pte[1] = hp->pmh_pte[0];
				hp->pmh_pte[0].high = va;
				hp->pmh_pte[0].low = npte;
				MachTLBWriteRandom(va, npte);
E 10
E 4
			} else {
				/*
				 * Don't replace wired entries, just update
				 * the hardware TLB.
				 * Bug: routines to flush the TLB won't know
				 * that the entry is in the hardware.
				 */
				printf("pmap_enter: wired va %x %x\n", va,
D 10
					hp->low); /* XXX */
E 10
I 10
					hp->pmh_pte[1].low); /* XXX */
E 10
				panic("pmap_enter: wired"); /* XXX */
				MachTLBWriteRandom(va, npte);
			}
		}
I 10
next:
E 15
I 15
		pte->pt_entry = npte;
		if (pmap->pm_tlbgen == tlbpid_gen)
			MachTLBUpdate(va | (pmap->pm_tlbpid <<
				VMMACH_TLB_PID_SHIFT), npte);
E 15
E 10
		va += NBPG;
		npte += NBPG;
I 15
		pte++;
E 15
	} while (--i != 0);
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
	vm_offset_t va;
	boolean_t wired;
{
D 15
	register pmap_hash_t hp;
E 15
I 15
	register pt_entry_t *pte;
E 15
	u_int p;
D 10
	int i;
E 10
I 10
D 15
	register int i, j;
E 15
I 15
	register int i;
E 15
E 10

#ifdef DEBUG
D 15
	if (pmapdebug & PDB_FOLLOW)
E 15
I 15
	if (pmapdebug & (PDB_FOLLOW|PDB_WIRING))
E 15
		printf("pmap_change_wiring(%x, %x, %x)\n", pmap, va, wired);
#endif
	if (pmap == NULL)
		return;

	p = wired ? PG_WIRED : 0;

	/*
	 * Don't need to flush the TLB since PG_WIRED is only in software.
	 */
D 15
	if (!pmap->pm_hash) {
		register pt_entry_t *pte;

E 15
I 15
	if (!pmap->pm_segtab) {
E 15
		/* change entries in kernel pmap */
I 3
#ifdef DIAGNOSTIC
D 15
		if (va < VM_MIN_KERNEL_ADDRESS ||
		    va >= VM_MIN_KERNEL_ADDRESS + PMAP_HASH_KPAGES*NPTEPG*NBPG)
E 15
I 15
		if (va < VM_MIN_KERNEL_ADDRESS || va >= virtual_end)
E 15
			panic("pmap_change_wiring");
#endif
E 3
		pte = kvtopte(va);
D 15
		i = pmaxpagesperpage;
		if (!(pte->pt_entry & PG_WIRED) && p)
			pmap->pm_stats.wired_count += i;
		else if ((pte->pt_entry & PG_WIRED) && !p)
			pmap->pm_stats.wired_count -= i;
		do {
			if (!(pte->pt_entry & PG_V))
				continue;
			pte->pt_entry = (pte->pt_entry & ~PG_WIRED) | p;
			pte++;
		} while (--i != 0);
	} else if (pmap->pm_tlbpid >= 0 && pmap->pm_hash != zero_pmap_hash) {
		i = pmaxpagesperpage;
I 10
		va = (va & PG_FRAME) | (pmap->pm_tlbpid << VMMACH_TLB_PID_SHIFT);
E 10
		do {
			hp = &pmap->pm_hash[PMAP_HASH(va)];
D 10
			if (!hp->high)
E 10
I 10
			if (hp->pmh_pte[0].high == va)
				j = 0;
			else if (hp->pmh_pte[1].high == va)
				j = 1;
			else {
				va += NBPG;
E 10
				continue;
D 10
			if (!(hp->low & PG_WIRED) && p)
E 10
I 10
			}
			if (!(hp->pmh_pte[j].low & PG_WIRED) && p)
E 10
				pmap->pm_stats.wired_count++;
D 10
			else if ((hp->low & PG_WIRED) && !p)
E 10
I 10
			else if ((hp->pmh_pte[j].low & PG_WIRED) && !p)
E 10
				pmap->pm_stats.wired_count--;
D 10
			hp->low = (hp->low & ~PG_WIRED) | p;
E 10
I 10
			hp->pmh_pte[j].low = (hp->pmh_pte[j].low & ~PG_WIRED) | p;
E 10
			va += NBPG;
		} while (--i != 0);
E 15
I 15
	} else {
		if (!(pte = pmap_segmap(pmap, va)))
			return;
		pte += (va >> PGSHIFT) & (NPTEPG - 1);
E 15
	}
I 15

	i = pmaxpagesperpage;
	if (!(pte->pt_entry & PG_WIRED) && p)
		pmap->pm_stats.wired_count += i;
	else if ((pte->pt_entry & PG_WIRED) && !p)
		pmap->pm_stats.wired_count -= i;
	do {
		if (pte->pt_entry & PG_V)
			pte->pt_entry = (pte->pt_entry & ~PG_WIRED) | p;
		pte++;
	} while (--i != 0);
E 15
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
D 15
	register pmap_hash_t hp;
I 10
	register int i;
E 15
E 10

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_extract(%x, %x) -> ", pmap, va);
#endif

D 3
	if (!pmap->pm_hash)
E 3
I 3
D 15
	if (!pmap->pm_hash) {
E 15
I 15
	if (!pmap->pm_segtab) {
E 15
#ifdef DIAGNOSTIC
D 15
		if (va < VM_MIN_KERNEL_ADDRESS ||
		    va >= VM_MIN_KERNEL_ADDRESS + PMAP_HASH_KPAGES*NPTEPG*NBPG)
E 15
I 15
		if (va < VM_MIN_KERNEL_ADDRESS || va >= virtual_end)
E 15
			panic("pmap_extract");
#endif
E 3
		pa = kvtopte(va)->pt_entry & PG_FRAME;
D 3
	else if (pmap->pm_tlbpid >= 0) {
E 3
I 3
D 15
	} else if (pmap->pm_tlbpid >= 0) {
E 3
		hp = &pmap->pm_hash[PMAP_HASH(va)];
D 10
		if (hp->high)
			pa = hp->low & PG_FRAME;
E 10
I 10
		va = (va & PG_FRAME) | (pmap->pm_tlbpid << VMMACH_TLB_PID_SHIFT);
		if (hp->pmh_pte[0].high == va)
			pa = hp->pmh_pte[0].low & PG_FRAME;
		else if (hp->pmh_pte[1].high == va)
			pa = hp->pmh_pte[1].low & PG_FRAME;
E 10
		else
E 15
I 15
	} else {
		register pt_entry_t *pte;

		if (!(pte = pmap_segmap(pmap, va)))
E 15
			pa = 0;
D 15
	} else
		pa = 0;
E 15
I 15
		else {
			pte += (va >> PGSHIFT) & (NPTEPG - 1);
			pa = pte->pt_entry & PG_FRAME;
		}
	}
	if (pa)
		pa |= va & PGOFSET;
E 15

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
D 15
		printf("%x\n", pa);
E 15
I 15
		printf("pmap_extract: pa %x\n", pa);
E 15
#endif
D 3
	return(pa);
E 3
I 3
	return (pa);
E 3
}

/*
 *	Copy the range specified by src_addr/len
 *	from the source map to the range dst_addr/len
 *	in the destination map.
 *
 *	This routine is only advisory and need not do anything.
 */
D 3
void pmap_copy(dst_pmap, src_pmap, dst_addr, len, src_addr)
E 3
I 3
void
pmap_copy(dst_pmap, src_pmap, dst_addr, len, src_addr)
E 3
	pmap_t dst_pmap;
	pmap_t src_pmap;
	vm_offset_t dst_addr;
	vm_size_t len;
	vm_offset_t src_addr;
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
D 3
void pmap_update()
E 3
I 3
void
pmap_update()
E 3
{

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_update()\n");
#endif
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
	pmap_t pmap;
{

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_collect(%x)\n", pmap);
#endif
}

/*
 *	pmap_zero_page zeros the specified (machine independent)
 *	page.
 */
void
pmap_zero_page(phys)
D 3
	register vm_offset_t phys;
E 3
I 3
	vm_offset_t phys;
E 3
{
D 3
	register vm_offset_t end;
E 3
I 3
	register int *p, *end;
E 3

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_zero_page(%x)\n", phys);
#endif
D 3
	end = phys + PAGE_SIZE;
E 3
I 3
	p = (int *)MACH_PHYS_TO_CACHED(phys);
	end = p + PAGE_SIZE / sizeof(int);
E 3
	do {
D 3
		((unsigned *)phys)[0] = 0;
		((unsigned *)phys)[1] = 0;
		((unsigned *)phys)[2] = 0;
		((unsigned *)phys)[3] = 0;
		phys += 4 * sizeof(unsigned);
	} while (phys != end);
E 3
I 3
		p[0] = 0;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0;
		p += 4;
	} while (p != end);
E 3
}

/*
 *	pmap_copy_page copies the specified (machine independent)
 *	page.
 */
void
pmap_copy_page(src, dst)
D 3
	register vm_offset_t src, dst;
E 3
I 3
	vm_offset_t src, dst;
E 3
{
D 3
	register vm_offset_t end;
	register unsigned tmp0, tmp1, tmp2, tmp3;
E 3
I 3
	register int *s, *d, *end;
	register int tmp0, tmp1, tmp2, tmp3;
E 3

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_copy_page(%x, %x)\n", src, dst);
#endif
D 3
	end = src + PAGE_SIZE;
E 3
I 3
	s = (int *)MACH_PHYS_TO_CACHED(src);
	d = (int *)MACH_PHYS_TO_CACHED(dst);
	end = s + PAGE_SIZE / sizeof(int);
E 3
	do {
D 3
		tmp0 = ((unsigned *)src)[0];
		tmp1 = ((unsigned *)src)[1];
		tmp2 = ((unsigned *)src)[2];
		tmp3 = ((unsigned *)src)[3];
		((unsigned *)dst)[0] = tmp0;
		((unsigned *)dst)[1] = tmp1;
		((unsigned *)dst)[2] = tmp2;
		((unsigned *)dst)[3] = tmp3;
		src += 4 * sizeof(unsigned);
		dst += 4 * sizeof(unsigned);
	} while (src != end);
E 3
I 3
		tmp0 = s[0];
		tmp1 = s[1];
		tmp2 = s[2];
		tmp3 = s[3];
		d[0] = tmp0;
		d[1] = tmp1;
		d[2] = tmp2;
		d[3] = tmp3;
		s += 4;
		d += 4;
	} while (s != end);
E 3
}

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
void
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
}

/*
 *	Clear the modify bits on the specified physical page.
 */
void
pmap_clear_modify(pa)
	vm_offset_t pa;
{
D 15
	pmap_hash_t hp;
E 15

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_clear_modify(%x)\n", pa);
#endif
#ifdef ATTR
D 15
	pmap_attributes[atop(pa - KERNBASE)] &= ~PMAP_ATTR_MOD;
E 15
I 15
	pmap_attributes[atop(pa)] &= ~PMAP_ATTR_MOD;
E 15
#endif
}

/*
 *	pmap_clear_reference:
 *
 *	Clear the reference bit on the specified physical page.
 */
void
pmap_clear_reference(pa)
	vm_offset_t pa;
{

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_clear_reference(%x)\n", pa);
#endif
#ifdef ATTR
D 15
	pmap_attributes[atop(pa - KERNBASE)] &= ~PMAP_ATTR_REF;
E 15
I 15
	pmap_attributes[atop(pa)] &= ~PMAP_ATTR_REF;
E 15
#endif
}

/*
 *	pmap_is_referenced:
 *
 *	Return whether or not the specified physical page is referenced
 *	by any physical maps.
 */
boolean_t
pmap_is_referenced(pa)
	vm_offset_t pa;
{
#ifdef ATTR
D 3
	return(pmap_attributes[atop(pa - KERNBASE)] & PMAP_ATTR_REF);
E 3
I 3
D 15
	return (pmap_attributes[atop(pa - KERNBASE)] & PMAP_ATTR_REF);
E 15
I 15
	return (pmap_attributes[atop(pa)] & PMAP_ATTR_REF);
E 15
E 3
#else
D 3
	return(FALSE);
E 3
I 3
	return (FALSE);
E 3
#endif
}

/*
 *	pmap_is_modified:
 *
 *	Return whether or not the specified physical page is modified
 *	by any physical maps.
 */
boolean_t
pmap_is_modified(pa)
	vm_offset_t pa;
{
#ifdef ATTR
D 3
	return(pmap_attributes[atop(pa - KERNBASE)] & PMAP_ATTR_MOD);
E 3
I 3
D 15
	return (pmap_attributes[atop(pa - KERNBASE)] & PMAP_ATTR_MOD);
E 15
I 15
	return (pmap_attributes[atop(pa)] & PMAP_ATTR_MOD);
E 15
E 3
#else
D 3
	return(FALSE);
E 3
I 3
	return (FALSE);
E 3
#endif
}

vm_offset_t
pmap_phys_address(ppn)
	int ppn;
{

#ifdef DEBUG
	if (pmapdebug & PDB_FOLLOW)
		printf("pmap_phys_address(%x)\n", ppn);
#endif
D 14
	panic("pmap_phys_address"); /* XXX */
E 14
D 3
	return(pmax_ptob(ppn));
E 3
I 3
	return (pmax_ptob(ppn));
E 3
}

/*
 * Miscellaneous support routines
 */

/*
 * Allocate a hardware PID and return it.
D 15
 * Also, change the hardwired TLB entry to point to the current TLB cache.
 * This is called by swtch().
E 15
I 15
 * It takes almost as much or more time to search the TLB for a
 * specific PID and flush those entries as it does to flush the entire TLB.
 * Therefore, when we allocate a new PID, we just take the next number. When
 * we run out of numbers, we flush the TLB, increment the generation count
 * and start over. PID zero is reserved for kernel use.
D 17
 * This is called only by swtch().
E 17
I 17
 * This is called only by switch().
E 17
E 15
 */
int
pmap_alloc_tlbpid(p)
	register struct proc *p;
{
	register pmap_t pmap;
D 15
	register u_int i;
E 15
	register int id;

	pmap = &p->p_vmspace->vm_pmap;
D 15
	if ((id = pmap->pm_tlbpid) >= 0) {
		if (pmap->pm_flags & PM_MODIFIED) {
			pmap->pm_flags &= ~PM_MODIFIED;
			MachTLBFlushPID(id);
E 15
I 15
	if (pmap->pm_tlbgen != tlbpid_gen) {
		id = tlbpid_cnt;
		if (id == VMMACH_NUM_PIDS) {
			MachTLBFlush();
			/* reserve tlbpid_gen == 0 to alway mean invalid */
			if (++tlbpid_gen == 0)
				tlbpid_gen = 1;
			id = 1;
E 15
		}
D 15
		goto done;
	}
E 15
I 15
		tlbpid_cnt = id + 1;
		pmap->pm_tlbpid = id;
		pmap->pm_tlbgen = tlbpid_gen;
	} else
		id = pmap->pm_tlbpid;
E 15

D 15
	if ((i = whichpids[0]) != 0xFFFFFFFF)
		id = 0;
	else if ((i = whichpids[1]) != 0xFFFFFFFF)
		id = 32;
	else {
		register struct proc *q;
		register pmap_t q_pmap;

		/*
		 * Have to find a tlbpid to recycle.
		 * There is probably a better way to do this.
		 */
D 11
		for (q = allproc; q != NULL; q = q->p_nxt) {
E 11
I 11
		for (q = (struct proc *)allproc; q != NULL; q = q->p_nxt) {
E 11
			q_pmap = &q->p_vmspace->vm_pmap;
			if ((id = q_pmap->pm_tlbpid) < 0)
				continue;
			if (q->p_stat != SRUN)
				goto fnd;
		}
		if (id < 0)
			panic("TLBPidAlloc");
	fnd:
		printf("pmap_alloc_tlbpid: recycle pid %d (%s) tlbpid %d\n",
			q->p_pid, q->p_comm, id); /* XXX */
		/*
		 * Even though the virtual to physical mapping hasn't changed,
		 * we need to clear the PID tag in the high entry of the cache.
		 */
		if (q_pmap->pm_hash != zero_pmap_hash) {
			register pmap_hash_t hp;
I 10
			register int j;
E 10

			hp = q_pmap->pm_hash;
			for (i = 0; i < PMAP_HASH_NUM_ENTRIES; i++, hp++) {
D 10
				if (!hp->high)
E 10
I 10
			    for (j = 0; j < 2; j++) {
				if (!hp->pmh_pte[j].high)
E 10
					continue;

D 10
				if (hp->low & PG_WIRED) {
					printf("Clearing wired user entry! h %x l %x\n", hp->high, hp->low);
E 10
I 10
				if (hp->pmh_pte[j].low & PG_WIRED) {
					printf("Clearing wired user entry! h %x l %x\n", hp->pmh_pte[j].high, hp->pmh_pte[j].low);
E 10
					panic("pmap_alloc_tlbpid: wired");
				}
D 8
				pmap_remove_pv(pmap, hp->high & PG_FRAME,
E 8
I 8
D 10
				pmap_remove_pv(q_pmap, hp->high & PG_FRAME,
E 8
					hp->low & PG_FRAME);
				hp->high = 0;
E 10
I 10
				pmap_remove_pv(q_pmap,
					hp->pmh_pte[j].high & PG_FRAME,
					hp->pmh_pte[j].low & PG_FRAME);
				hp->pmh_pte[j].high = 0;
E 10
				q_pmap->pm_stats.resident_count--;
I 10
			    }
E 10
			}
		}
		q_pmap->pm_tlbpid = -1;
		MachTLBFlushPID(id);
E 15
#ifdef DEBUG
D 15
		remove_stats.pidflushes++;
#endif
		pmap->pm_tlbpid = id;
		goto done;
E 15
I 15
	if (pmapdebug & (PDB_FOLLOW|PDB_TLBPID)) {
		if (curproc)
			printf("pmap_alloc_tlbpid: curproc %d '%s' ",
				curproc->p_pid, curproc->p_comm);
		else
			printf("pmap_alloc_tlbpid: curproc <none> ");
		printf("segtab %x tlbpid %d pid %d '%s'\n",
			pmap->pm_segtab, id, p->p_pid, p->p_comm);
E 15
	}
D 15
	while (i & 1) {
		i >>= 1;
		id++;
	}
	whichpids[id >> 5] |= 1 << (id & 0x1F);
	pmap->pm_tlbpid = id;
done:
	/*
	 * Map in new TLB cache.
	 */
	if (pmap == cur_pmap)
		return (id);
	cur_pmap = pmap;
	for (i = 0; i < PMAP_HASH_UPAGES; i++) {
		MachTLBWriteIndexed(i + UPAGES,
			(PMAP_HASH_UADDR + (i << PGSHIFT)) |
				(id << VMMACH_TLB_PID_SHIFT),
			pmap->pm_hash_ptes[i]);
	}
E 15
I 15
#endif
E 15
	return (id);
}

/*
 * Remove a physical to virtual address translation.
 */
void
pmap_remove_pv(pmap, va, pa)
	pmap_t pmap;
	vm_offset_t va, pa;
{
	register pv_entry_t pv, npv;
	int s;

#ifdef DEBUG
D 15
	if (pmapdebug & PDB_FOLLOW)
E 15
I 15
	if (pmapdebug & (PDB_FOLLOW|PDB_PVENTRY))
E 15
		printf("pmap_remove_pv(%x, %x, %x)\n", pmap, va, pa);
#endif
	/*
	 * Remove page from the PV table (raise IPL since we
	 * may be called at interrupt time).
	 */
	if (!IS_VM_PHYSADDR(pa))
		return;
	pv = pa_to_pvh(pa);
	s = splimp();
	/*
	 * If it is the first entry on the list, it is actually
	 * in the header and we must copy the following entry up
	 * to the header.  Otherwise we must search the list for
	 * the entry.  In either case we free the now unused entry.
	 */
	if (pmap == pv->pv_pmap && va == pv->pv_va) {
		npv = pv->pv_next;
		if (npv) {
			*pv = *npv;
			free((caddr_t)npv, M_VMPVENT);
		} else
			pv->pv_pmap = NULL;
#ifdef DEBUG
		remove_stats.pvfirst++;
#endif
	} else {
		for (npv = pv->pv_next; npv; pv = npv, npv = npv->pv_next) {
#ifdef DEBUG
			remove_stats.pvsearch++;
#endif
			if (pmap == npv->pv_pmap && va == npv->pv_va)
				goto fnd;
		}
#ifdef DIAGNOSTIC
		printf("pmap_remove_pv(%x, %x, %x) not found\n", pmap, va, pa);
		panic("pmap_remove_pv");
#endif
	fnd:
		pv->pv_next = npv->pv_next;
		free((caddr_t)npv, M_VMPVENT);
	}
	splx(s);
}

D 15
#ifdef DEBUG
pmap_print(pmap)
	pmap_t pmap;
E 15
I 15
/*
 *	vm_page_alloc1:
 *
 *	Allocate and return a memory cell with no associated object.
 */
vm_page_t
vm_page_alloc1()
E 15
{
D 15
	register pmap_hash_t hp;
D 10
	register int i;
E 10
I 10
	register int i, j;
E 15
I 15
	register vm_page_t	mem;
	int		spl;
E 15
E 10

D 15
	printf("\tpmap_print(%x)\n", pmap);
E 15
I 15
	spl = splimp();				/* XXX */
	simple_lock(&vm_page_queue_free_lock);
D 18
	if (queue_empty(&vm_page_queue_free)) {
E 18
I 18
	if (vm_page_queue_free.tqh_first == NULL) {
E 18
		simple_unlock(&vm_page_queue_free_lock);
		splx(spl);
		return (NULL);
	}
E 15

D 15
	if (pmap->pm_hash == zero_pmap_hash) {
		printf("pm_hash == zero\n");
		return;
E 15
I 15
D 18
	queue_remove_first(&vm_page_queue_free, mem, vm_page_t, pageq);
E 18
I 18
	mem = vm_page_queue_free.tqh_first;
	TAILQ_REMOVE(&vm_page_queue_free, mem, pageq);
E 18

	cnt.v_free_count--;
	simple_unlock(&vm_page_queue_free_lock);
	splx(spl);

	mem->flags = PG_BUSY | PG_CLEAN | PG_FAKE;
	mem->wire_count = 0;

	/*
	 *	Decide if we should poke the pageout daemon.
	 *	We do this if the free count is less than the low
	 *	water mark, or if the free count is less than the high
	 *	water mark (but above the low water mark) and the inactive
	 *	count is less than its target.
	 *
	 *	We don't have the counts locked ... if they change a little,
	 *	it doesn't really matter.
	 */

	if (cnt.v_free_count < cnt.v_free_min ||
	    (cnt.v_free_count < cnt.v_free_target &&
	     cnt.v_inactive_count < cnt.v_inactive_target))
D 20
		thread_wakeup((int)&vm_pages_needed);
E 20
I 20
		thread_wakeup(&vm_pages_needed);
E 20
	return (mem);
}

/*
 *	vm_page_free1:
 *
 *	Returns the given page to the free list,
 *	disassociating it with any VM object.
 *
 *	Object and page must be locked prior to entry.
 */
void
vm_page_free1(mem)
	register vm_page_t	mem;
{

	if (mem->flags & PG_ACTIVE) {
D 18
		queue_remove(&vm_page_queue_active, mem, vm_page_t, pageq);
E 18
I 18
		TAILQ_REMOVE(&vm_page_queue_active, mem, pageq);
E 18
		mem->flags &= ~PG_ACTIVE;
		cnt.v_active_count--;
E 15
	}
D 15
	if (pmap->pm_hash == (pmap_hash_t)0) {
		printf("pm_hash == kernel\n");
		return;
E 15
I 15

	if (mem->flags & PG_INACTIVE) {
D 18
		queue_remove(&vm_page_queue_inactive, mem, vm_page_t, pageq);
E 18
I 18
		TAILQ_REMOVE(&vm_page_queue_inactive, mem, pageq);
E 18
		mem->flags &= ~PG_INACTIVE;
		cnt.v_inactive_count--;
E 15
	}
D 15
	hp = pmap->pm_hash;
	for (i = 0; i < PMAP_HASH_NUM_ENTRIES; i++, hp++) {
D 10
		if (!hp->high)
E 10
I 10
	    for (j = 0; j < 2; j++) {
		if (!hp->pmh_pte[j].high)
E 10
			continue;
D 10
		printf("%d: hi %x low %x\n", i, hp->high, hp->low);
E 10
I 10
		printf("%d: hi %x low %x\n", i, hp->pmh_pte[j].high, hp->pmh_pte[j].low);
	    }
E 15
I 15

	if (!(mem->flags & PG_FICTITIOUS)) {
		int	spl;

		spl = splimp();
		simple_lock(&vm_page_queue_free_lock);
D 18
		queue_enter(&vm_page_queue_free, mem, vm_page_t, pageq);
E 18
I 18
		TAILQ_INSERT_TAIL(&vm_page_queue_free, mem, pageq);
E 18

		cnt.v_free_count++;
		simple_unlock(&vm_page_queue_free_lock);
		splx(spl);
E 15
E 10
	}
}
D 15
#endif
E 15
E 1
