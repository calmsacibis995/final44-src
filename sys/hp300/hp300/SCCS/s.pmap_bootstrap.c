h08572
s 00002/00002/00485
d D 8.1 93/06/10 21:41:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00039/00079/00448
d D 7.4 92/12/27 09:53:17 hibler 4 3
c cleanup
e
s 00009/00007/00518
d D 7.3 92/10/11 09:42:45 bostic 3 2
c make kernel includes standard
e
s 00000/00135/00525
d D 7.2 92/06/15 14:51:32 hibler 2 1
c get rid of BOOTDEBUG code
e
s 00660/00000/00000
d D 7.1 92/06/05 15:38:14 hibler 1 0
c merge latest Utah hp300 code including 68040 support
e
u
U
t
T
I 1
/* 
D 5
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "param.h"
#include "pte.h"
#include "clockreg.h"
#include "../include/vmparam.h"
#include "../include/cpu.h"
E 3
I 3
#include <sys/param.h>
E 3
D 4

E 4
I 4
#include <sys/msgbuf.h>
E 4
D 3
#include "vm/vm.h"
E 3
I 3
#include <hp300/hp300/pte.h>
#include <hp300/hp300/clockreg.h>
E 3
D 4

E 4
I 3
#include <machine/vmparam.h>
#include <machine/cpu.h>

#include <vm/vm.h>

E 3
D 4
/*
 * Allocate various and sundry SYSMAPs used in the days of old VM
 * and not yet converted.  XXX.
 */
#define BSDVM_COMPAT	1

E 4
D 2
#ifdef BOOTDEBUG
/*
 * Mirrors the actual PT setup done in locore but none of the data
 * structures set up here are actually used.  In this way you can boot
 * the system and compare what it would have done (pmap_bootstrap) with
 * what it should do (locore) when debugging.  See locore.s as well.
 */
#define RELOC(v, t)	*((t*)((u_int)&(X##v) + firstpa))
int XSysptsize = 2;
int Xmmutype = MMU_68040;
int Xectype = 0;
int Xmachineid = HP_380;
int Xprotection_codes[8];
struct ste *XSysseg;
struct pte *XSysptmap, *XSysmap;
u_int XUmap, XCLKbase, XMMUbase;
char *Xintiobase, *Xintiolimit, *Xextiobase, *Xproc0paddr;
vm_offset_t Xavail_start, Xavail_end, Xvirtual_avail, Xvirtual_end;
vm_size_t Xmem_size;
int Xmaxmem, Xphysmem, Xpmap_aliasmask;
struct pmap Xkernel_pmap_store;
#else
E 2
#define RELOC(v, t)	*((t*)((u_int)&(v) + firstpa))
D 2
#endif
E 2

extern char *etext;
extern int Sysptsize;
extern char *extiobase, *proc0paddr;
extern struct ste *Sysseg;
extern struct pte *Sysptmap, *Sysmap;
extern vm_offset_t Umap, CLKbase, MMUbase;

extern int maxmem, physmem;
extern vm_offset_t avail_start, avail_end, virtual_avail, virtual_end;
extern vm_size_t mem_size;
D 4
extern int pmap_aliasmask, protection_codes[];
#if defined(DYNPGSIZE)
extern int hppagesperpage;
E 4
I 4
extern int protection_codes[];
#ifdef HAVEVAC
extern int pmap_aliasmask;
E 4
#endif

D 4
#if BSDVM_COMPAT
D 3
#include "msgbuf.h"
E 3
I 3
#include <sys/msgbuf.h>
E 3

E 4
/*
D 4
 * All those kernel PT submaps that BSD is so fond of
E 4
I 4
 * Special purpose kernel virtual addresses, used for mapping
 * physical pages for a variety of temporary or permanent purposes:
 *
 *	CADDR1, CADDR2:	pmap zero/copy operations
 *	vmmap:		/dev/mem, crash dumps, parity error checking
 *	ledbase:	SPU LEDs
 *	msgbufp:	kernel message buffer
E 4
 */
D 4
struct pte	*CMAP1, *CMAP2, *mmap;
caddr_t		CADDR1, CADDR2, vmmap;
struct pte	*msgbufmap;
E 4
I 4
caddr_t		CADDR1, CADDR2, vmmap, ledbase;
E 4
struct msgbuf	*msgbufp;
D 2
#ifdef BOOTDEBUG
struct pte	*XCMAP1, *XCMAP2, *Xmmap;
caddr_t		XCADDR1, XCADDR2, Xvmmap;
struct pte	*Xmsgbufmap;
struct msgbuf	*Xmsgbufp;
E 2
D 4
#endif
E 4
D 2
#endif
E 2

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
	vm_offset_t kstpa, kptpa, iiopa, eiopa, kptmpa, lkptpa, p0upa;
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
	 *	iiopa		internal IO space
	 *			PT pages		IIOMAPSIZE pages
	 *
	 *	eiopa		external IO space
	 *			PT pages		EIOMAPSIZE pages
	 *
	 * [ Sysptsize is the number of pages of PT, IIOMAPSIZE and
	 *   EIOMAPSIZE are the number of PTEs, hence we need to round
	 *   the total to a page boundary with IO maps at the end. ]
	 *
	 *	kptmpa		kernel PT map		1 page
	 *
	 *	lkptpa		last kernel PT page	1 page
	 *
	 *	p0upa		proc 0 u-area		UPAGES pages
	 *
	 * The KVA corresponding to any of these PAs is:
	 *	(PA - firstpa + KERNBASE).
	 */
	if (RELOC(mmutype, int) == MMU_68040)
		kstsize = MAXKL2SIZE / (NPTEPG/SG4_LEV2SIZE);
	else
		kstsize = 1;
	kstpa = nextpa;
	nextpa += kstsize * NBPG;
	kptpa = nextpa;
	nptpages = RELOC(Sysptsize, int) +
		(IIOMAPSIZE + EIOMAPSIZE + NPTEPG - 1) / NPTEPG;
	nextpa += nptpages * NBPG;
	eiopa = nextpa - EIOMAPSIZE * sizeof(struct pte);
	iiopa = eiopa - IIOMAPSIZE * sizeof(struct pte);
	kptmpa = nextpa;
	nextpa += NBPG;
	lkptpa = nextpa;
	nextpa += NBPG;
	p0upa = nextpa;
	nextpa += UPAGES * NBPG;

	/*
	 * Initialize segment table and kernel page table map.
	 *
	 * On 68030s and earlier MMUs the two are identical except for
	 * the valid bits so both are initialized with essentially the
	 * same values.  On the 68040, which has a mandatory 3-level
	 * structure, the segment table holds the level 1 table and part
	 * (or all) of the level 2 table and hence is considerably
	 * different.  Here the first level consists of 128 descriptors
	 * (512 bytes) each mapping 32mb of address space.  Each of these
	 * points to blocks of 128 second level descriptors (512 bytes)
	 * each mapping 256kb.  Note that there may be additional "segment
	 * table" pages depending on how large MAXKL2SIZE is.
	 *
	 * Portions of the last segment of KVA space (0xFFF00000 -
	 * 0xFFFFFFFF) are mapped for a couple of purposes.  0xFFF00000
	 * for UPAGES is used for mapping the current process u-area
	 * (u + kernel stack).  The very last page (0xFFFFF000) is mapped
	 * to the last physical page of RAM to give us a region in which
	 * PA == VA.  We use the first part of this page for enabling
	 * and disabling mapping.  The last part of this page also contains
	 * info left by the boot ROM.
	 *
	 * XXX cramming two levels of mapping into the single "segment"
	 * table on the 68040 is intended as a temporary hack to get things
	 * working.  The 224mb of address space that this allows will most
	 * likely be insufficient in the future (at least for the kernel).
	 */
	if (RELOC(mmutype, int) == MMU_68040) {
		register int num;

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
		ste = &((u_int *)kstpa)[SG4_LEV1SIZE-1];
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
		pte = &((u_int *)kptmpa)[NPTEPG-1];
		*pte = lkptpa | PG_RW | PG_CI | PG_V;
	} else {
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
		 * Invalidate all but the last remaining entries in both.
		 */
		epte = &((u_int *)kptmpa)[NPTEPG-1];
		while (pte < epte) {
			*ste++ = SG_NV;
			*pte++ = PG_NV;
		}
		/*
		 * Initialize the last to point to point to the page
		 * table page allocated earlier.
		 */
		*ste = lkptpa | SG_RW | SG_V;
		*pte = lkptpa | PG_RW | PG_CI | PG_V;
	}
	/*
	 * Invalidate all but the final entry in the last kernel PT page
	 * (u-area PTEs will be validated later).  The final entry maps
	 * the last page of physical memory.
	 */
	pte = (u_int *)lkptpa;
	epte = &pte[NPTEPG-1];
	while (pte < epte)
		*pte++ = PG_NV;
	*pte = MAXADDR | PG_RW | PG_CI | PG_V;
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
	pte = &((u_int *)kptpa)[hp300_btop(KERNBASE)];
	epte = &pte[hp300_btop(hp300_trunc_page(&etext))];
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
	epte = &((u_int *)kptpa)[hp300_btop(nextpa - firstpa)];
	protopte = (protopte & ~PG_PROT) | PG_RW;
	/*
	 * Enable copy-back caching of data pages
	 */
	if (RELOC(mmutype, int) == MMU_68040)
		protopte |= PG_CCB;
	while (pte < epte) {
		*pte++ = protopte;
		protopte += NBPG;
	}
	/*
	 * Finally, validate the internal IO space PTEs (RW+CI).
	 * We do this here since the 320/350 MMU registers (also
	 * used, but to a lesser extent, on other models) are mapped
	 * in this range and it would be nice to be able to access
	 * them after the MMU is turned on.
	 */
	pte = (u_int *)iiopa;
	epte = (u_int *)eiopa;
	protopte = INTIOBASE | PG_RW | PG_CI | PG_V;
	while (pte < epte) {
		*pte++ = protopte;
		protopte += NBPG;
	}

	/*
	 * Calculate important exported kernel virtual addresses
	 */
	/*
	 * Sysseg: base of kernel segment table
	 */
	RELOC(Sysseg, struct ste *) =
		(struct ste *)(kstpa - firstpa);
	/*
	 * Sysptmap: base of kernel page table map
	 */
	RELOC(Sysptmap, struct pte *) =
		(struct pte *)(kptmpa - firstpa);
	/*
	 * Sysmap: kernel page table (as mapped through Sysptmap)
	 * Immediately follows `nptpages' of static kernel page table.
	 */
	RELOC(Sysmap, struct pte *) =
		(struct pte *)hp300_ptob(nptpages * NPTEPG);
	/*
	 * Umap: first of UPAGES PTEs (in Sysmap) for fixed-address u-area.
	 * HIGHPAGES PTEs from the end of Sysmap.
	 */
	RELOC(Umap, vm_offset_t) =
		(vm_offset_t)RELOC(Sysmap, struct pte *) +
			(HP_MAX_PTSIZE - HIGHPAGES * sizeof(struct pte));
	/*
	 * intiobase, intiolimit: base and end of internal (DIO) IO space.
	 * IIOMAPSIZE pages prior to external IO space at end of static
	 * kernel page table.
	 */
	RELOC(intiobase, char *) =
		(char *)hp300_ptob(nptpages*NPTEPG - (IIOMAPSIZE+EIOMAPSIZE));
	RELOC(intiolimit, char *) =
		(char *)hp300_ptob(nptpages*NPTEPG - EIOMAPSIZE);
	/*
	 * extiobase: base of external (DIO-II) IO space.
	 * EIOMAPSIZE pages at the end of the static kernel page table.
	 */
	RELOC(extiobase, char *) =
		(char *)hp300_ptob(nptpages*NPTEPG - EIOMAPSIZE);
	/*
	 * CLKbase, MMUbase: important registers in internal IO space
	 * accessed from assembly language.
	 */
	RELOC(CLKbase, vm_offset_t) =
		(vm_offset_t)RELOC(intiobase, char *) + CLKBASE;
	RELOC(MMUbase, vm_offset_t) =
		(vm_offset_t)RELOC(intiobase, char *) + MMUBASE;

	/*
	 * Setup u-area for process 0.
	 */
	/*
	 * Validate PTEs in Sysmap corresponding to the u-area (Umap)
	 * which are HIGHPAGES from the end of the last kernel PT page
	 * allocated earlier.
	 */
	pte = &((u_int *)lkptpa)[NPTEPG - HIGHPAGES];
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
	RELOC(proc0paddr, char *) = (char *)(p0upa - firstpa);

	/*
	 * VM data structures are now initialized, set up data for
	 * the pmap module.
	 */
	RELOC(avail_start, vm_offset_t) = nextpa;
	RELOC(avail_end, vm_offset_t) =
		hp300_ptob(RELOC(maxmem, int))
D 4
#if BSDVM_COMPAT
E 4
			/* XXX allow for msgbuf */
D 4
			- hp300_round_page(sizeof(struct msgbuf))
#endif
				;
E 4
I 4
			- hp300_round_page(sizeof(struct msgbuf));
E 4
	RELOC(mem_size, vm_size_t) = hp300_ptob(RELOC(physmem, int));
	RELOC(virtual_avail, vm_offset_t) =
		VM_MIN_KERNEL_ADDRESS + (nextpa - firstpa);
	RELOC(virtual_end, vm_offset_t) = VM_MAX_KERNEL_ADDRESS;
D 4
#if defined(DYNPGSIZE)
	RELOC(hppagesperpage, int) = 1;		/* XXX */
#endif
E 4

I 4
#ifdef HAVEVAC
E 4
	/*
	 * Determine VA aliasing distance if any
	 */
	if (RELOC(ectype, int) == EC_VIRT)
D 4
		switch (RELOC(machineid, int)) {
		case HP_320:
E 4
I 4
		if (RELOC(machineid, int) == HP_320)
E 4
			RELOC(pmap_aliasmask, int) = 0x3fff;	/* 16k */
D 4
			break;
		case HP_350:
E 4
I 4
		else if (RELOC(machineid, int) == HP_350)
E 4
			RELOC(pmap_aliasmask, int) = 0x7fff;	/* 32k */
D 4
			break;
		}
E 4
I 4
#endif
E 4

	/*
	 * Initialize protection array.
I 4
	 * XXX don't use a switch statement, it might produce an
	 * absolute "jmp" table.
E 4
	 */
	{
D 4
		register int *kp, prot;
E 4
I 4
		register int *kp;
E 4

		kp = &RELOC(protection_codes, int);
D 4
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
E 4
I 4
		kp[VM_PROT_NONE|VM_PROT_NONE|VM_PROT_NONE] = 0;
		kp[VM_PROT_READ|VM_PROT_NONE|VM_PROT_NONE] = PG_RO;
		kp[VM_PROT_READ|VM_PROT_NONE|VM_PROT_EXECUTE] = PG_RO;
		kp[VM_PROT_NONE|VM_PROT_NONE|VM_PROT_EXECUTE] = PG_RO;
		kp[VM_PROT_NONE|VM_PROT_WRITE|VM_PROT_NONE] = PG_RW;
		kp[VM_PROT_NONE|VM_PROT_WRITE|VM_PROT_EXECUTE] = PG_RW;
		kp[VM_PROT_READ|VM_PROT_WRITE|VM_PROT_NONE] = PG_RW;
		kp[VM_PROT_READ|VM_PROT_WRITE|VM_PROT_EXECUTE] = PG_RW;
E 4
	}

	/*
	 * Kernel page/segment table allocated in locore,
	 * just initialize pointers.
	 */
	{
		struct pmap *kpm = &RELOC(kernel_pmap_store, struct pmap);

		kpm->pm_stab = RELOC(Sysseg, struct ste *);
		kpm->pm_ptab = RELOC(Sysmap, struct pte *);
		simple_lock_init(&kpm->pm_lock);
		kpm->pm_count = 1;
		kpm->pm_stpa = (struct ste *)kstpa;
		/*
		 * For the 040 we also initialize the free level 2
		 * descriptor mask noting that we have used:
		 *	0:		level 1 table
		 *	1 to `num':	map page tables
		 *	MAXKL2SIZE-1:	maps last-page page table
		 */
		if (RELOC(mmutype, int) == MMU_68040) {
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
	}

D 4
#if BSDVM_COMPAT
#define	SYSMAP(c, p, v, n) \
	RELOC(v, c) = (c)va; va += ((n)*HP_PAGE_SIZE); \
	RELOC(p, struct pte *) = (struct pte *)pte; pte += (n);

E 4
	/*
D 4
	 * Allocate all the submaps we need
E 4
I 4
	 * Allocate some fixed, special purpose kernel virtual addresses
E 4
	 */
	{
		vm_offset_t va = RELOC(virtual_avail, vm_offset_t);

D 4
		pte = &((u_int *)RELOC(Sysmap, struct pte *))[hp300_btop(va)];
	
		SYSMAP(caddr_t		,CMAP1		,CADDR1	   ,1	)
		SYSMAP(caddr_t		,CMAP2		,CADDR2	   ,1	)
		SYSMAP(caddr_t		,mmap		,vmmap	   ,1	)
		SYSMAP(struct msgbuf *	,msgbufmap	,msgbufp   ,1	)

E 4
I 4
		RELOC(CADDR1, caddr_t) = (caddr_t)va;
		va += HP_PAGE_SIZE;
		RELOC(CADDR2, caddr_t) = (caddr_t)va;
		va += HP_PAGE_SIZE;
		RELOC(vmmap, caddr_t) = (caddr_t)va;
		va += HP_PAGE_SIZE;
		RELOC(ledbase, caddr_t) = (caddr_t)va;
		va += HP_PAGE_SIZE;
		RELOC(msgbufp, struct msgbuf *) = (struct msgbuf *)va;
		va += HP_PAGE_SIZE;
E 4
		RELOC(virtual_avail, vm_offset_t) = va;
	}
D 4
#undef	SYSMAP
#endif
}

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
E 4
}
D 2

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
	avail_end -= hp300_round_page(sizeof(struct msgbuf));
#endif

	mem_size = physmem << PGSHIFT;
	virtual_avail = VM_MIN_KERNEL_ADDRESS + (firstaddr - loadaddr);
	virtual_end = VM_MAX_KERNEL_ADDRESS;
#if defined(DYNPGSIZE)
	hppagesperpage = PAGE_SIZE / HP_PAGE_SIZE;
#endif

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
	v = (c)va; va += ((n)*HP_PAGE_SIZE); p = pte; pte += (n);

	va = virtual_avail;
	pte = &Sysmap[hp300_btop(va)];

	SYSMAP(caddr_t		,CMAP1		,CADDR1	   ,1		)
	SYSMAP(caddr_t		,CMAP2		,CADDR2	   ,1		)
	SYSMAP(caddr_t		,mmap		,vmmap	   ,1		)
	SYSMAP(struct msgbuf *	,msgbufmap	,msgbufp   ,1		)
	virtual_avail = va;
#undef SYSMAP
#endif
}
#endif
E 2
E 1
