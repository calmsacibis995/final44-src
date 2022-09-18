h47233
s 00002/00002/00111
d D 8.1 93/06/10 21:44:59 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00112
d D 7.13 93/06/02 10:52:27 hibler 13 12
c add pmap_wired_count macro for use in mlock/munlock
e
s 00002/00002/00110
d D 7.12 93/05/24 23:25:38 torek 12 11
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00010/00003/00102
d D 7.11 92/12/27 09:27:43 hibler 11 10
c performance improvements
e
s 00001/00001/00104
d D 7.10 92/06/22 14:14:56 mkm 10 9
c need more kernel address space for big machines
e
s 00026/00003/00079
d D 7.9 92/06/05 15:29:18 hibler 9 8
c merge latest Utah hp300 code including 68040 support
e
s 00002/00002/00080
d D 7.8 92/02/19 18:40:30 mckusick 8 7
c eliminate variable kernel_pmap and function pmap_kernel
e
s 00002/00001/00080
d D 7.7 91/11/05 22:04:49 mckusick 7 6
c lint
e
s 00002/00000/00079
d D 7.6 91/05/10 13:02:42 bostic 6 5
c put redist script in
e
s 00002/00004/00077
d D 7.5 91/05/10 10:21:52 mckusick 5 4
c correct copyright, Utah not CMU
e
s 00002/00001/00079
d D 7.4 91/05/07 10:04:36 hibler 4 3
c pmap_kernel macro
e
s 00012/00091/00068
d D 7.3 91/04/20 16:53:51 karels 3 2
c move pte/ste defs to hp300/pte.h; rm *_NULL, foo_t typedefs;
c fix includes; add iscurproc arg to PMAP_ACTIVATE; mv vmmap from systm.h
e
s 00001/00007/00158
d D 7.2 90/12/16 16:37:27 bostic 2 1
c kernel reorg
e
s 00165/00000/00000
d D 7.1 90/12/05 19:26:10 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
 * Copyright (c) 1987 Carnegie-Mellon University
D 14
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
D 5
 * The Mach Operating System project at Carnegie-Mellon University.
 *
 * The CMU software License Agreement specifies the terms and conditions
 * for use and redistribution.
E 5
I 5
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
E 5
 *
I 6
 * %sccs.include.redist.c%
 *
E 6
 *	%W% (Berkeley) %G%
 */

#ifndef	_PMAP_MACHINE_
D 3
#define	_PMAP_MACHINE_	1
E 3
I 3
#define	_PMAP_MACHINE_
E 3

D 2
#ifdef	KERNEL
#include "../sys/lock.h"
#include "machine/vmparam.h"
#include "../vm/vm_statistics.h"
#else
E 2
D 3
#include <sys/lock.h>
D 2
#include <machine/vmparam.h>
E 2
I 2
#include <hp300/include/vmparam.h>
E 2
#include <vm/vm_statistics.h>
D 2
#endif	/* KERNEL */
E 2

/*
 * HP300 hardware segment/page table entries
 */

struct ste {
	unsigned int	sg_pfnum:20;	/* page table frame number */
	unsigned int	:8;		/* reserved at 0 */
	unsigned int	:1;		/* reserved at 1 */
	unsigned int	sg_prot:1;	/* write protect bit */
	unsigned int	sg_v:2;		/* valid bits */
};

struct pte {
	unsigned int	pg_pfnum:20;	/* page frame number or 0 */
	unsigned int	:3;
	unsigned int	pg_w:1;		/* is wired */
	unsigned int	:1;		/* reserved at zero */
	unsigned int	pg_ci:1;	/* cache inhibit bit */
	unsigned int	:1;		/* reserved at zero */
	unsigned int	pg_m:1;		/* hardware modified (dirty) bit */
	unsigned int	pg_u:1;		/* hardware used (reference) bit */
	unsigned int	pg_prot:1;	/* write protect bit */
	unsigned int	pg_v:2;		/* valid bit */
};

typedef struct ste	st_entry_t;	/* segment table entry */
typedef struct pte	pt_entry_t;	/* Mach page table entry */

#define	PT_ENTRY_NULL	((pt_entry_t *) 0)
#define	ST_ENTRY_NULL	((st_entry_t *) 0)

#define	SG_V		0x00000002	/* segment is valid */
#define	SG_NV		0x00000000
#define	SG_PROT		0x00000004	/* access protection mask */
#define	SG_RO		0x00000004
#define	SG_RW		0x00000000
#define	SG_FRAME	0xfffff000
#define	SG_IMASK	0xffc00000
#define	SG_PMASK	0x003ff000
#define	SG_ISHIFT	22
#define	SG_PSHIFT	12

#define	PG_V		0x00000001
#define	PG_NV		0x00000000
#define	PG_PROT		0x00000004
#define	PG_U		0x00000008
#define	PG_M		0x00000010
#define	PG_W		0x00000100
#define	PG_RO		0x00000004
#define	PG_RW		0x00000000
#define	PG_FRAME	0xfffff000
#define	PG_CI		0x00000040
#define PG_SHIFT	12
#define	PG_PFNUM(x)	(((x) & PG_FRAME) >> PG_SHIFT)

E 3
#define HP_PAGE_SIZE	NBPG
I 9
#if defined(HP380)
#define HP_SEG_SIZE	(mmutype == MMU_68040 ? 0x40000 : NBSEG)
#else
E 9
#define HP_SEG_SIZE	NBSEG
I 9
#endif
E 9

I 9
#define hp300_trunc_seg(x)	(((unsigned)(x)) & ~(HP_SEG_SIZE-1))
#define hp300_round_seg(x)	hp300_trunc_seg((unsigned)(x) + HP_SEG_SIZE-1)

E 9
D 3
#define HP_STSIZE	HP_PAGE_SIZE	/* segment table size */
#define HP_MAX_PTSIZE	HP_SEG_SIZE	/* max size of UPT */
#define HP_MAX_KPTSIZE	0x100000	/* max memory to allocate to KPT */
#define HP_PTBASE	0x10000000	/* UPT map base address */
#define HP_PTMAXSIZE	0x70000000	/* UPT map maximum size */

E 3
/*
D 3
 * Kernel virtual address to page table entry and to physical address.
 */
#define	kvtopte(va) \
	(&Sysmap[((unsigned)(va) - VM_MIN_KERNEL_ADDRESS) >> PGSHIFT])
#define	ptetokv(pt) \
	((((pt_entry_t *)(pt) - Sysmap) << PGSHIFT) + VM_MIN_KERNEL_ADDRESS)
#define	kvtophys(va) \
	((kvtopte(va)->pg_pfnum << PGSHIFT) | ((int)(va) & PGOFSET))

/*
E 3
 * Pmap stuff
 */
D 3
#define PMAP_NULL	((pmap_t) 0)

E 3
struct pmap {
D 3
	pt_entry_t		*pm_ptab;	/* KVA of page table */
	st_entry_t		*pm_stab;	/* KVA of segment table */
	boolean_t		pm_stchanged;	/* ST changed */
E 3
I 3
	struct pte		*pm_ptab;	/* KVA of page table */
	struct ste		*pm_stab;	/* KVA of segment table */
	int			pm_stchanged;	/* ST changed */
I 9
	int			pm_stfree;	/* 040: free lev2 blocks */
	struct ste		*pm_stpa;	/* 040: ST phys addr */
E 9
E 3
	short			pm_sref;	/* segment table ref count */
	short			pm_count;	/* pmap reference count */
	simple_lock_data_t	pm_lock;	/* lock on pmap */
	struct pmap_statistics	pm_stats;	/* pmap statistics */
	long			pm_ptpages;	/* more stats: PT pages */
};

typedef struct pmap	*pmap_t;

D 8
extern pmap_t		kernel_pmap;
E 8
I 8
extern struct pmap	kernel_pmap_store;
D 11
#define kernel_pmap (&kernel_pmap_store)
E 11
E 8

I 11
#define kernel_pmap	(&kernel_pmap_store)
#define	active_pmap(pm) \
	((pm) == kernel_pmap || (pm) == curproc->p_vmspace->vm_map.pmap)

E 11
/*
I 9
 * On the 040 we keep track of which level 2 blocks are already in use
 * with the pm_stfree mask.  Bits are arranged from LSB (block 0) to MSB
 * (block 31).  For convenience, the level 1 table is considered to be
 * block 0.
 *
 * MAX[KU]L2SIZE control how many pages of level 2 descriptors are allowed.
 * for the kernel and users.  8 implies only the initial "segment table"
 * page is used.  WARNING: don't change MAXUL2SIZE unless you can allocate
 * physically contiguous pages for the ST in pmap.c!
 */
D 10
#define	MAXKL2SIZE	16
E 10
I 10
#define	MAXKL2SIZE	32
E 10
#define MAXUL2SIZE	8
#define l2tobm(n)	(1 << (n))
#define	bmtol2(n)	(ffs(n) - 1)

/*
E 9
 * Macros for speed
 */
D 3
#define PMAP_ACTIVATE(pmapp, pcbp) \
	if ((pmapp) != PMAP_NULL && (pmapp)->pm_stchanged) { \
E 3
I 3
#define PMAP_ACTIVATE(pmapp, pcbp, iscurproc) \
	if ((pmapp) != NULL && (pmapp)->pm_stchanged) { \
E 3
D 9
		(pcbp)->pcb_ustp = \
D 7
		    hp300_btop(pmap_extract(kernel_pmap, (pmapp)->pm_stab)); \
E 7
I 7
		    hp300_btop(pmap_extract(kernel_pmap, \
			((vm_offset_t)(pmapp)->pm_stab))); \
E 9
I 9
		(pcbp)->pcb_ustp = hp300_btop((vm_offset_t)(pmapp)->pm_stpa); \
E 9
E 7
D 3
		if ((pmapp) == u.u_procp->p_map->pmap) \
E 3
I 3
		if (iscurproc) \
E 3
			loadustp((pcbp)->pcb_ustp); \
		(pmapp)->pm_stchanged = FALSE; \
	}
#define PMAP_DEACTIVATE(pmapp, pcbp)

/*
 * For each vm_page_t, there is a list of all currently valid virtual
 * mappings of that page.  An entry is a pv_entry_t, the list is pv_table.
 */
typedef struct pv_entry {
	struct pv_entry	*pv_next;	/* next pv_entry */
D 3
	pmap_t		pv_pmap;	/* pmap where mapping lies */
E 3
I 3
	struct pmap	*pv_pmap;	/* pmap where mapping lies */
E 3
	vm_offset_t	pv_va;		/* virtual address for mapping */
D 3
	st_entry_t	*pv_ptste;	/* non-zero if VA maps a PT page */
	pmap_t		pv_ptpmap;	/* if pv_ptste, pmap for PT page */
E 3
I 3
	struct ste	*pv_ptste;	/* non-zero if VA maps a PT page */
	struct pmap	*pv_ptpmap;	/* if pv_ptste, pmap for PT page */
E 3
	int		pv_flags;	/* flags */
} *pv_entry_t;

D 3
#define	PV_ENTRY_NULL	((pv_entry_t) 0)

E 3
D 11
#define	PV_CI		0x01	/* all entries must be cache inhibited */
#define PV_PTPAGE	0x02	/* entry maps a page table page */
E 11
I 11
#define	PV_CI		0x01	/* header: all entries are cache inhibited */
#define PV_PTPAGE	0x02	/* header: entry maps a page table page */
E 11

#ifdef	KERNEL
I 11
#if defined(HP320) || defined(HP350)
#define	HAVEVAC				/* include cheezy VAC support */
#endif

E 11
D 3

E 3
pv_entry_t	pv_table;		/* array of entries, one per page */

#define pa_index(pa)		atop(pa - vm_first_phys)
#define pa_to_pvh(pa)		(&pv_table[pa_index(pa)])

I 4
D 8
#define	pmap_kernel()			(kernel_pmap)
E 8
E 4
#define	pmap_resident_count(pmap)	((pmap)->pm_stats.resident_count)
I 13
#define	pmap_wired_count(pmap)		((pmap)->pm_stats.wired_count)
E 13

D 3
extern	pt_entry_t	*Sysmap;
E 3
I 3
extern	struct pte *Sysmap;
extern	char *vmmap;			/* map for mem, dumps, etc. */
E 3
D 12
#endif	KERNEL
E 12
I 12
#endif /* KERNEL */
E 12

D 12
#endif	_PMAP_MACHINE_
E 12
I 12
#endif /* _PMAP_MACHINE_ */
E 12
E 1
