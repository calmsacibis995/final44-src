h43348
s 00002/00002/00422
d D 8.1 93/06/10 22:26:43 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00202/00283/00222
d D 7.3 93/05/12 04:12:50 akito 3 2
c LUNA-II (68040 based LUNA) support
e
s 00006/00006/00499
d D 7.2 92/10/11 11:07:54 bostic 2 1
c make kernel includes standard
e
s 00505/00000/00000
d D 7.1 92/06/15 06:38:45 fujita 1 0
c date and time created 92/06/15 06:38:45 by fujita
e
u
U
t
T
I 1
/* 
 * Copyright (c) 1992 OMRON Corporation.
D 4
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 3
 *	OMRON: $Id: pmap_bootstrap.c,v 1.2 92/06/14 18:11:27 moti Exp $
E 3
I 3
 * from: hp300/hp300/pmap_bootstrap.c	7.4 (Berkeley) 12/27/92
E 3
 *
D 3
 * from: hp300/hp300/pmap_bootstrap.c	7.1 (Berkeley) 6/5/92
 *
E 3
 *	%W% (Berkeley) %G%
 */

D 2
#include "param.h"
#include "pte.h"
#include "../include/vmparam.h"
#include "../include/cpu.h"
E 2
I 2
#include <sys/param.h>
I 3
#include <sys/msgbuf.h>
E 3
#include <luna68k/luna68k/pte.h>
#include <machine/vmparam.h>
#include <machine/cpu.h>
E 2

D 2
#include "vm/vm.h"
E 2
I 2
#include <vm/vm.h>
E 2

D 3
/*
 * Allocate various and sundry SYSMAPs used in the days of old VM
 * and not yet converted.  XXX.
 */
#define BSDVM_COMPAT	1

E 3
extern char *etext;
extern int Sysptsize;
D 3

E 3
extern char *proc0paddr;
extern struct ste *Sysseg;
extern struct pte *Sysptmap, *Sysmap;
extern vm_offset_t Umap;

extern int maxmem, physmem;
extern vm_offset_t avail_start, avail_end, virtual_avail, virtual_end;
extern vm_size_t mem_size;
extern int protection_codes[];
D 3
#if defined(DYNPGSIZE)
extern int lunapagesperpage;
#endif
E 3

D 3
#if BSDVM_COMPAT
D 2
#include "msgbuf.h"
E 2
I 2
#include <sys/msgbuf.h>
E 2

E 3
/*
D 3
 * All those kernel PT submaps that BSD is so fond of
E 3
I 3
 * Special purpose kernel virtual addresses, used for mapping
 * physical pages for a variety of temporary or permanent purposes:
 *
 *	CADDR1, CADDR2:	pmap zero/copy operations
 *	vmmap:		/dev/mem, crash dumps, parity error checking
 *	ledbase:	SPU LEDs
 *	msgbufp:	kernel message buffer
E 3
 */
D 3
struct pte	*CMAP1, *CMAP2, *mmap;
caddr_t		CADDR1, CADDR2, vmmap;
struct pte	*msgbufmap;
E 3
I 3
caddr_t		CADDR1, CADDR2, vmmap, ledbase;
E 3
struct msgbuf	*msgbufp;
D 3
#endif
E 3

D 3
/* 
 * LUNA H/W information.
 */
struct physmap io_physmap[] =
{
	{0x40000000,0x00100000,1},	/* debugger */
	{0x41000000,0x00020000,1},	/* PROM */
	{0x45000000,0x00000800,0},	/* calendar clock */
	{0x49000000,0x00000004,0},	/* pio-0 */
	{0x4D000000,0x00000004,0},	/* pio-1 */
	{0x51000000,0x00000008,0},	/* sio */
	{0x61000000,0x00000001,0},	/* TAS register */
	{0x63000000,0x00000001,0},	/* SYSINT flag */
	{0x6B000000,0x00000001,0},	/* internal FPP enable/disable */
	{0x6F000000,0x00000001,0},	/* external FPP enable/disable */
	{0x71000000,0x00020000,0},	/* 3 port RAM */
	{0,0,0}				/* terminate */
};
#define	IO_DBG_OFF	0		/* debugger offset in io_physmap[] */
#define	IOPTPAGE	((sizeof(io_physmap)/sizeof(struct physmap))-1)
int	ioptpage = IOPTPAGE;		/* for locore */

E 3
/*
 * Bootstrap the VM system.
 *
 * Called with MMU off so we must relocate all global references by `firstpa'
 * (don't call any functions here!)  `nextpa' is the first available physical
 * memory address.  Returns an updated first PA reflecting the memory we
 * have allocated.  MMU is still off when we return.
 *
 * XXX assumes sizeof(u_int) == sizeof(struct pte)
 * XXX a PIC compiler would make this much easier.
 */
void
pmap_bootstrap(nextpa, firstpa)
	vm_offset_t nextpa;
	register vm_offset_t firstpa;
{
D 3
	vm_offset_t kstpa, kptpa, iopa, kptmpa, ukptpa, p0upa;
E 3
I 3
	vm_offset_t kstpa, kptpa, kptmpa, lkptpa, p0upa;
E 3
	u_int nptpages, kstsize;
	register u_int protoste, protopte, *ste, *pte, *epte;

	/*
	 * Calculate important physical addresses:
	 *
	 *	kstpa		kernel segment table	1 page (!040)
	 *						N pages (040)
	 *
	 *	kptpa		statically allocated
	 *			kernel PT pages		Sysptsize+ pages
	 *
I 3
	 * [ Sysptsize is the number of pages of PT, hence we need to
	 *   round the total to a page boundary at the end. ]
	 *
E 3
	 *	kptmpa		kernel PT map		1 page
	 *
D 3
	 *	ukptpa		Uarea kernel PT page	1 page
E 3
I 3
	 *	lkptpa		last kernel PT page	1 page
E 3
	 *
D 3
	 *	iopa		IO and debbuger space
	 *			PT pages		IOPTPAGE pages
	 *
	 *
E 3
	 *	p0upa		proc 0 u-area		UPAGES pages
	 *
	 * The KVA corresponding to any of these PAs is:
	 *	(PA - firstpa + KERNBASE).
	 */
D 3
	kstsize = 1;
E 3
I 3
	if (mmutype == MMU_68040)
		kstsize = MAXKL2SIZE / (NPTEPG/SG4_LEV2SIZE);
	else
		kstsize = 1;
E 3
	kstpa = nextpa;
	nextpa += kstsize * NBPG;
	kptpa = nextpa;
	nptpages = Sysptsize;
	nextpa += nptpages * NBPG;
	kptmpa = nextpa;
	nextpa += NBPG;
D 3
	ukptpa = nextpa;
E 3
I 3
	lkptpa = nextpa;
E 3
	nextpa += NBPG;
D 3
	iopa = nextpa;
	nextpa += IOPTPAGE * NBPG;
E 3
	p0upa = nextpa;
	nextpa += UPAGES * NBPG;

	/*
	 * Initialize segment table and kernel page table map.
	 *
	 * On 68030s and earlier MMUs the two are identical except for
	 * the valid bits so both are initialized with essentially the
D 3
	 * same values.
	 * 0x3FF00000 for UPAGES is used for mapping the current process u-area
	 * (u + kernel stack). 
E 3
I 3
	 * same values.  On the 68040, which has a mandatory 3-level
	 * structure, the segment table holds the level 1 table and part
	 * (or all) of the level 2 table and hence is considerably
	 * different.  Here the first level consists of 128 descriptors
	 * (512 bytes) each mapping 32mb of address space.  Each of these
	 * points to blocks of 128 second level descriptors (512 bytes)
	 * each mapping 256kb.  Note that there may be additional "segment
	 * table" pages depending on how large MAXKL2SIZE is.
	 *
	 * Portions of the last segment of KVA space (0x3FF00000 -
	 * 0x3FFFFFFF) are mapped for a couple of purposes.  0x3FF00000
	 * for UPAGES is used for mapping the current process u-area
	 * (u + kernel stack).  The very last page (0x3FFFF000) is mapped
	 * to the last physical page of RAM to give us a region in which
	 * PA == VA.  We use the first part of this page for enabling
	 * and disabling mapping.  The last part of this page also contains
	 * info left by the boot ROM.
	 *
	 * XXX cramming two levels of mapping into the single "segment"
	 * table on the 68040 is intended as a temporary hack to get things
	 * working.  The 224mb of address space that this allows will most
	 * likely be insufficient in the future (at least for the kernel).
E 3
	 */
I 3
#if defined(LUNA2)
	if (mmutype == MMU_68040) {
		register int num;
E 3

D 3
	/*
	 * Map the page table pages in both the HW segment table
	 * and the software Sysptmap.  Note that Sysptmap is also
	 * considered a PT page hence the +1.
	 */
	ste = (u_int *)kstpa;
	pte = (u_int *)kptmpa;
	epte = &pte[nptpages+1];
	protoste = kptpa | SG_RW | SG_V;
	protopte = kptpa | PG_RW | PG_CI | PG_V;
	while (pte < epte) {
	    *ste++ = protoste;
	    *pte++ = protopte;
	    protoste += NBPG;
	    protopte += NBPG;
E 3
I 3
		/*
		 * First invalidate the entire "segment table" pages
		 * (levels 1 and 2 have the same "invalid" value).
		 */
		pte = (u_int *)kstpa;
		epte = &pte[kstsize * NPTEPG];
		while (pte < epte)
			*pte++ = SG_NV;
		/*
		 * Initialize level 2 descriptors (which immediately
		 * follow the level 1 table).  We need:
		 *	NPTEPG / SG4_LEV3SIZE
		 * level 2 descriptors to map each of the nptpages+1
		 * pages of PTEs.  Note that we set the "used" bit
		 * now to save the HW the expense of doing it.
		 */
		num = (nptpages + 1) * (NPTEPG / SG4_LEV3SIZE);
		pte = &((u_int *)kstpa)[SG4_LEV1SIZE];
		epte = &pte[num];
		protoste = kptpa | SG_U | SG_RW | SG_V;
		while (pte < epte) {
			*pte++ = protoste;
			protoste += (SG4_LEV3SIZE * sizeof(struct ste));
		}
		/*
		 * Initialize level 1 descriptors.  We need:
		 *	roundup(num, SG4_LEV2SIZE) / SG4_LEV2SIZE
		 * level 1 descriptors to map the `num' level 2's.
		 */
		pte = (u_int *)kstpa;
		epte = &pte[roundup(num, SG4_LEV2SIZE) / SG4_LEV2SIZE];
		protoste = (u_int)&pte[SG4_LEV1SIZE] | SG_U | SG_RW | SG_V;
		while (pte < epte) {
			*pte++ = protoste;
			protoste += (SG4_LEV2SIZE * sizeof(struct ste));
		}
		/*
		 * Initialize the final level 1 descriptor to map the last
		 * block of level 2 descriptors.
		 */
		ste = &((u_int *)kstpa)[KERNELSTACK >> SG4_SHIFT1];
		pte = &((u_int *)kstpa)[kstsize*NPTEPG - SG4_LEV2SIZE];
		*ste = (u_int)pte | SG_U | SG_RW | SG_V;
		/*
		 * Now initialize the final portion of that block of
		 * descriptors to map the "last PT page".
		 */
		pte = &((u_int *)kstpa)[kstsize*NPTEPG - NPTEPG/SG4_LEV3SIZE];
		epte = &pte[NPTEPG/SG4_LEV3SIZE];
		protoste = lkptpa | SG_U | SG_RW | SG_V;
		while (pte < epte) {
			*pte++ = protoste;
			protoste += (SG4_LEV3SIZE * sizeof(struct ste));
		}
		/*
		 * Initialize Sysptmap
		 */
		pte = (u_int *)kptmpa;
		epte = &pte[nptpages+1];
		protopte = kptpa | PG_RW | PG_CI | PG_V;
		while (pte < epte) {
			*pte++ = protopte;
			protopte += NBPG;
		}
		pte = &((u_int *)kptmpa)[KERNELSTACK>>SG_ISHIFT];
		*pte = lkptpa | PG_RW | PG_CI | PG_V;
	} else
#endif
	{
		/*
		 * Map the page table pages in both the HW segment table
		 * and the software Sysptmap.  Note that Sysptmap is also
		 * considered a PT page hence the +1.
		 */
		ste = (u_int *)kstpa;
		pte = (u_int *)kptmpa;
		epte = &pte[nptpages+1];
		protoste = kptpa | SG_RW | SG_V;
		protopte = kptpa | PG_RW | PG_CI | PG_V;
		while (pte < epte) {
			*ste++ = protoste;
			*pte++ = protopte;
			protoste += NBPG;
			protopte += NBPG;
		}
		/*
		 * Invalidate all entries.
		 */
		epte = &((u_int *)kptmpa)[NPTEPG];
		while (pte < epte) {
			*ste++ = SG_NV;
			*pte++ = PG_NV;
		}
		/* LUNA: Uarea pt map */
		ste = (u_int *)kstpa;
		pte = (u_int *)kptmpa;
		ste[KERNELSTACK>>SG_ISHIFT] = lkptpa | SG_RW | SG_V;
		pte[KERNELSTACK>>SG_ISHIFT] = lkptpa | PG_RW | PG_CI | PG_V;
E 3
	}
	/*
D 3
	 * Invalidate all but the last remaining entries in both.
	 */
	epte = &((u_int *)kptmpa)[NPTEPG];
	while (pte < epte) {
	    *ste++ = SG_NV;
	    *pte++ = PG_NV;
	}
	/* LUNA: Uarea pt map */
	ste = (u_int *)kstpa;
	pte = (u_int *)kptmpa;
	ste[KERNELSTACK>>SG_ISHIFT] = ukptpa | SG_RW | SG_V;
	pte[KERNELSTACK>>SG_ISHIFT] = ukptpa | PG_RW | PG_CI | PG_V;

	/*
E 3
	 * Invalidate all but the final entry in the last kernel PT page
	 * (u-area PTEs will be validated later).  The final entry maps
	 * the last page of physical memory.
	 */
D 3
	pte = (u_int *)ukptpa;
E 3
I 3
	pte = (u_int *)lkptpa;
E 3
	epte = &pte[NPTEPG];
	while (pte < epte)
		*pte++ = PG_NV;
	/*
	 * Initialize kernel page table.
	 * Start by invalidating the `nptpages' that we have allocated.
	 */
	pte = (u_int *)kptpa;
	epte = &pte[nptpages * NPTEPG];
	while (pte < epte)
		*pte++ = PG_NV;
	/*
	 * Validate PTEs for kernel text (RO)
	 */
	pte = &((u_int *)kptpa)[luna_btop(KERNBASE)];
	epte = &pte[luna_btop(luna_trunc_page(&etext))];
#ifdef KGDB
	protopte = firstpa | PG_RW | PG_V;	/* XXX RW for now */
#else
	protopte = firstpa | PG_RO | PG_V;
#endif
	while (pte < epte) {
		*pte++ = protopte;
		protopte += NBPG;
	}
	/*
	 * Validate PTEs for kernel data/bss, dynamic data allocated
	 * by us so far (nextpa - firstpa bytes), and pages for proc0
	 * u-area and page table allocated below (RW).
	 */
	epte = &((u_int *)kptpa)[luna_btop(nextpa - firstpa)];
	protopte = (protopte & ~PG_PROT) | PG_RW;
I 3
#if defined(LUNA2)
	/*
	 * Enable copy-back caching of data pages
	 */
	if (mmutype == MMU_68040)
		protopte |= PG_CCB;
#endif
E 3
	while (pte < epte) {
		*pte++ = protopte;
		protopte += NBPG;
	}
D 3

	/* initialize; all IO pte invalidate */
	pte = (u_int *)iopa;
	epte = &pte[IOPTPAGE * NPTEPG];
	while (pte < epte)
		*pte++ = PG_NV;
E 3
	/*
D 3
	 * Here, we validate STEs and kernel page table PTEs
	 * for io space.
	 */
	{
	    int index;

	    protoste = iopa | SG_RW | SG_V;
	    protopte = iopa | PG_RW | PG_CI | PG_V;
	    for (index = 0; io_physmap[index].pm_phys; index++)
	      {
		  ste = &((u_int *)kstpa)[io_physmap[index].pm_phys/NBSEG];
		  pte = &((u_int *)kptmpa)[io_physmap[index].pm_phys/NBSEG];
		  *ste = protoste;
		  *pte = protopte;
		  protoste += NBPG;
		  protopte += NBPG;
	      }
	    /*
	     * Finally, validate the IO space PTEs.
	     */
	    /* create io(and debbuger) PTEs */
	    for (index = 0; io_physmap[index].pm_phys; index++)
	      {
		  pte = (u_int *)iopa + index*NPTEPG;
		  epte = &pte[(luna_round_page(io_physmap[index].pm_size))>>PG_SHIFT];
		  /* 
		   * First entry(index == IO_DBG_OFF) is very special, 
		   * we map debugger at fixed address(0x40000000).
		   * Debugger is always loaded (maxmem+1) page.
		   */
		  protopte = (index == IO_DBG_OFF ? 
			      ((maxmem+1)<<PG_SHIFT) : io_physmap[index].pm_phys) |
		    PG_RW |(io_physmap[index].pm_cache == 0 ? PG_CI : 0) | PG_V;
		  
		  /* physical page setup loop */
		  while (pte < epte) {
		      *pte++ = protopte;
		      protopte += NBPG;
		  }
	      }
	}
	/*
E 3
	 * Calculate important exported kernel virtual addresses
	 */
	/*
	 * Sysseg: base of kernel segment table
	 */
	Sysseg = (struct ste *)(kstpa - firstpa);
	/*
	 * Sysptmap: base of kernel page table map
	 */
	Sysptmap = (struct pte *)(kptmpa - firstpa);
	/*
	 * Sysmap: kernel page table (as mapped through Sysptmap)
	 * Immediately follows `nptpages' of static kernel page table.
	 */
	Sysmap = (struct pte *)luna_ptob(nptpages * NPTEPG);
	/*
	 * Umap: first of UPAGES PTEs (in Sysmap) for fixed-address u-area.
	 * HIGHPAGES PTEs from the end of Sysmap.
	 * LUNA: User stack address = 0x3ff00000.
	 */
	Umap = (vm_offset_t)Sysmap + (LUNA_MAX_PTSIZE/4 - HIGHPAGES * sizeof(struct pte));
I 3

E 3
	/*
	 * Setup u-area for process 0.
	 */
	/*
	 * Validate PTEs in Sysmap corresponding to the u-area (Umap)
	 * which are HIGHPAGES from the end of the last kernel PT page
	 * allocated earlier.
	 */
D 3
	pte = &((u_int *)ukptpa)[NPTEPG - HIGHPAGES];
E 3
I 3
	pte = &((u_int *)lkptpa)[NPTEPG - HIGHPAGES];
E 3
	epte = &pte[UPAGES];
	protopte = p0upa | PG_RW | PG_V;
	while (pte < epte) {
		*pte++ = protopte;
		protopte += NBPG;
	}
	/*
	 * Zero the u-area.
	 * NOTE: `pte' and `epte' aren't PTEs here.
	 */
	pte = (u_int *)p0upa;
	epte = (u_int *)(p0upa + UPAGES*NBPG);
	while (pte < epte)
		*pte++ = 0;
	/*
	 * Remember the u-area address so it can be loaded in the
	 * proc struct p_addr field later.
	 */
	proc0paddr = (char *)(p0upa - firstpa);

	/*
	 * VM data structures are now initialized, set up data for
	 * the pmap module.
	 */
	avail_start = nextpa;
D 3
	avail_end = luna_ptob(maxmem);
#if BSDVM_COMPAT
E 3
I 3
	avail_end = luna_ptob(maxmem)
E 3
			/* XXX allow for msgbuf */
D 3
			- luna_round_page(sizeof(struct msgbuf))
#endif
				;
E 3
I 3
			- luna_round_page(sizeof(struct msgbuf));
E 3
	mem_size = luna_ptob(physmem);
D 3
	virtual_avail =	VM_MIN_KERNEL_ADDRESS + (nextpa - firstpa);
E 3
I 3
	virtual_avail = VM_MIN_KERNEL_ADDRESS + (nextpa - firstpa);
E 3
	virtual_end = VM_MAX_KERNEL_ADDRESS;
D 3
#if defined(DYNPGSIZE)
	lunapagesperpage = 1;		/* XXX */
#endif
E 3
I 3

E 3
	/*
	 * Initialize protection array.
I 3
	 * XXX don't use a switch statement, it might produce an
	 * absolute "jmp" table.
E 3
	 */
	{
D 3
		register int *kp, prot;
E 3
I 3
		register int *kp;
E 3

		kp = protection_codes;
D 3
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
E 3
I 3
		kp[VM_PROT_NONE|VM_PROT_NONE|VM_PROT_NONE] = 0;
		kp[VM_PROT_READ|VM_PROT_NONE|VM_PROT_NONE] = PG_RO;
		kp[VM_PROT_READ|VM_PROT_NONE|VM_PROT_EXECUTE] = PG_RO;
		kp[VM_PROT_NONE|VM_PROT_NONE|VM_PROT_EXECUTE] = PG_RO;
		kp[VM_PROT_NONE|VM_PROT_WRITE|VM_PROT_NONE] = PG_RW;
		kp[VM_PROT_NONE|VM_PROT_WRITE|VM_PROT_EXECUTE] = PG_RW;
		kp[VM_PROT_READ|VM_PROT_WRITE|VM_PROT_NONE] = PG_RW;
		kp[VM_PROT_READ|VM_PROT_WRITE|VM_PROT_EXECUTE] = PG_RW;
E 3
	}

	/*
	 * Kernel page/segment table allocated in locore,
	 * just initialize pointers.
	 */
	{
		struct pmap *kpm = &kernel_pmap_store;

		kpm->pm_stab = Sysseg;
		kpm->pm_ptab = Sysmap;
		simple_lock_init(&kpm->pm_lock);
		kpm->pm_count = 1;
		kpm->pm_stpa = (struct ste *)kstpa;
I 3
#if defined(LUNA2)
		/*
		 * For the 040 we also initialize the free level 2
		 * descriptor mask noting that we have used:
		 *	0:		level 1 table
		 *	1 to `num':	map page tables
		 *	MAXKL2SIZE-1:	maps last-page page table
		 */
		if (mmutype == MMU_68040) {
			register int num;
			
			kpm->pm_stfree = ~l2tobm(0);
			num = roundup((nptpages + 1) * (NPTEPG / SG4_LEV3SIZE),
				      SG4_LEV2SIZE) / SG4_LEV2SIZE;
			while (num)
				kpm->pm_stfree &= ~l2tobm(num--);
			kpm->pm_stfree &= ~l2tobm(MAXKL2SIZE-1);
			for (num = MAXKL2SIZE;
			     num < sizeof(kpm->pm_stfree)*NBBY;
			     num++)
				kpm->pm_stfree &= ~l2tobm(num);
		}
#endif
E 3
	}

D 3
#if BSDVM_COMPAT
#define	SYSMAP(c, p, v, n) \
	v = (c)va; va += ((n)*LUNA_PAGE_SIZE); \
	p = (struct pte *)pte; pte += (n);

E 3
	/*
D 3
	 * Allocate all the submaps we need
E 3
I 3
	 * Allocate some fixed, special purpose kernel virtual addresses
E 3
	 */
	{
		vm_offset_t va = virtual_avail;

D 3
		pte = &Sysmap[luna_btop(va)];
	
		SYSMAP(caddr_t		,CMAP1		,CADDR1	   ,1	)
		SYSMAP(caddr_t		,CMAP2		,CADDR2	   ,1	)
		SYSMAP(caddr_t		,mmap		,vmmap	   ,1	)
		SYSMAP(struct msgbuf *	,msgbufmap	,msgbufp   ,1	)

E 3
I 3
		CADDR1 = (caddr_t)va;
		va += LUNA_PAGE_SIZE;
		CADDR2 = (caddr_t)va;
		va += LUNA_PAGE_SIZE;
		vmmap = (caddr_t)va;
		va += LUNA_PAGE_SIZE;
		ledbase = (caddr_t)va;
		va += LUNA_PAGE_SIZE;
		msgbufp = (struct msgbuf *)va;
		va += LUNA_PAGE_SIZE;
E 3
		virtual_avail = va;
	}
D 3
#undef	SYSMAP
#endif
E 3
}
D 3

pmap_showstuff()
{
	int i;
	printf("CADDR1=%x pte at CMAP1=%x\n", CADDR1, CMAP1);
	printf("CADDR2=%x pte at CMAP2=%x\n", CADDR2, CMAP2);
	printf("vmmap=%x pte at mmap=%x\n", vmmap, mmap);
	printf("msgbufp=%x pte at msgbufmap=%x\n", msgbufp, msgbufmap);
	printf("virtual_avail=%x, virtual_end=%x\n", virtual_avail, virtual_end);
	for (i = 0; i < 8; i++)
		printf("%x ", protection_codes[i]);
	printf("\n");
}

#ifdef BOOTDEBUG
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
Opmap_bootstrap(firstaddr, loadaddr)
	vm_offset_t firstaddr;
	vm_offset_t loadaddr;
{
#if BSDVM_COMPAT
	vm_offset_t va;
	struct pte *pte;
#endif

	avail_start = firstaddr;
	avail_end = maxmem << PGSHIFT;

#if BSDVM_COMPAT
	/* XXX: allow for msgbuf */
	avail_end -= luna_round_page(sizeof(struct msgbuf));
#endif

	mem_size = physmem << PGSHIFT;
	virtual_avail = VM_MIN_KERNEL_ADDRESS + (firstaddr - loadaddr);
	virtual_end = VM_MAX_KERNEL_ADDRESS;
#if defined(DYNPGSIZE)
	lunapagesperpage = PAGE_SIZE / LUNA_PAGE_SIZE;
#endif
	/*
	 * Initialize protection array.
	 */
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
	v = (c)va; va += ((n)*LUNA_PAGE_SIZE); p = pte; pte += (n);

	va = virtual_avail;
	pte = &Sysmap[luna_btop(va)];

	SYSMAP(caddr_t		,CMAP1		,CADDR1	   ,1		)
	SYSMAP(caddr_t		,CMAP2		,CADDR2	   ,1		)
	SYSMAP(caddr_t		,mmap		,vmmap	   ,1		)
	SYSMAP(struct msgbuf *	,msgbufmap	,msgbufp   ,1		)
	virtual_avail = va;
#undef SYSMAP
#endif
}
#endif
E 3
E 1
