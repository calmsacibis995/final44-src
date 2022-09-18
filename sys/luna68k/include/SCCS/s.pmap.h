h64090
s 00003/00003/00120
d D 8.2 93/12/06 20:39:45 akito 7 6
c sync up to hp300/include/pmap.h 7.13 (Berkeley) 6/2/93
e
s 00002/00002/00121
d D 8.1 93/06/10 22:22:24 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00122
d D 7.5 93/06/02 10:54:57 hibler 5 4
c add pmap_wired_count macro for mlock/munlock
e
s 00004/00000/00118
d D 7.4 93/05/12 04:10:35 akito 4 3
c LUNA-II (68040 based LUNA) support
e
s 00008/00004/00110
d D 7.3 93/01/02 13:38:40 akito 3 2
c sync up to hp300/include/pmap.h 7.11
e
s 00001/00003/00113
d D 7.2 92/06/30 17:21:33 fujita 2 1
c sync up to hp300/include/pmap.h 7.9
e
s 00116/00000/00000
d D 7.1 92/06/15 06:28:24 fujita 1 0
c date and time created 92/06/15 06:28:24 by fujita
e
u
U
t
T
I 1
/* 
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1992 OMRON Corporation.
D 6
 * Copyright (c) 1991, 1992 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 3
 *	OMRON: $Id: pmap.h,v 1.2 92/06/14 06:29:43 moti Exp $
E 3
I 3
D 7
 * from: hp300/include/pmap.h	7.11 (Berkeley) 12/27/92
E 7
I 7
 * from: hp300/include/pmap.h	7.13 (Berkeley) 6/2/93
E 7
E 3
 *
 *	%W% (Berkeley) %G%
 */

#ifndef	_PMAP_MACHINE_
#define	_PMAP_MACHINE_

#define LUNA_PAGE_SIZE	NBPG
I 4
#if defined(LUNA2)
#define LUNA_SEG_SIZE	(mmutype == MMU_68040 ? 0x40000 : NBSEG)
#else
E 4
#define LUNA_SEG_SIZE	NBSEG
I 4
#endif
E 4

#define luna_trunc_seg(x)	(((unsigned)(x)) & ~(LUNA_SEG_SIZE-1))
#define luna_round_seg(x)	luna_trunc_seg((unsigned)(x) + LUNA_SEG_SIZE-1)

/*
 * Pmap stuff
 */
struct pmap {
	struct pte		*pm_ptab;	/* KVA of page table */
	struct ste		*pm_stab;	/* KVA of segment table */
	int			pm_stchanged;	/* ST changed */
	int			pm_stfree;	/* 040: free lev2 blocks */
	struct ste		*pm_stpa;	/* 040: ST phys addr */
	short			pm_sref;	/* segment table ref count */
	short			pm_count;	/* pmap reference count */
	simple_lock_data_t	pm_lock;	/* lock on pmap */
	struct pmap_statistics	pm_stats;	/* pmap statistics */
	long			pm_ptpages;	/* more stats: PT pages */
};

typedef struct pmap	*pmap_t;

extern struct pmap	kernel_pmap_store;
D 3
#define kernel_pmap (&kernel_pmap_store)
E 3

I 3
#define kernel_pmap	(&kernel_pmap_store)
#define	active_pmap(pm) \
	((pm) == kernel_pmap || (pm) == curproc->p_vmspace->vm_map.pmap)

E 3
/*
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
#define	MAXKL2SIZE	16
#define MAXUL2SIZE	8
#define l2tobm(n)	(1 << (n))
#define	bmtol2(n)	(ffs(n) - 1)

/*
 * Macros for speed
 */
#define PMAP_ACTIVATE(pmapp, pcbp, iscurproc) \
	if ((pmapp) != NULL && (pmapp)->pm_stchanged) { \
D 2
		(pcbp)->pcb_ustp = \
		    luna_btop(pmap_extract(kernel_pmap, \
			((vm_offset_t)(pmapp)->pm_stab))); \
E 2
I 2
		(pcbp)->pcb_ustp = luna_btop((vm_offset_t)(pmapp)->pm_stpa); \
E 2
		if (iscurproc) \
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
	struct pmap	*pv_pmap;	/* pmap where mapping lies */
	vm_offset_t	pv_va;		/* virtual address for mapping */
	struct ste	*pv_ptste;	/* non-zero if VA maps a PT page */
	struct pmap	*pv_ptpmap;	/* if pv_ptste, pmap for PT page */
	int		pv_flags;	/* flags */
} *pv_entry_t;

D 3
#define	PV_CI		0x01	/* all entries must be cache inhibited */
#define PV_PTPAGE	0x02	/* entry maps a page table page */
E 3
I 3
#define	PV_CI		0x01	/* header: all entries are cache inhibited */
#define PV_PTPAGE	0x02	/* header: entry maps a page table page */
E 3

#ifdef	KERNEL
I 3

E 3
pv_entry_t	pv_table;		/* array of entries, one per page */

#define pa_index(pa)		atop(pa - vm_first_phys)
#define pa_to_pvh(pa)		(&pv_table[pa_index(pa)])

#define	pmap_resident_count(pmap)	((pmap)->pm_stats.resident_count)
I 5
#define	pmap_wired_count(pmap)		((pmap)->pm_stats.wired_count)
E 5

extern	struct pte *Sysmap;
extern	char *vmmap;			/* map for mem, dumps, etc. */

/*
 * definitions LUNA IO space mapping
 */
struct physmap {
	int pm_phys;
	int pm_size;
	int pm_cache;
} ;

D 7
#endif
E 7
I 7
#endif /* KERNEL */
E 7

D 7
#endif	_PMAP_MACHINE_
E 7
I 7
#endif /* _PMAP_MACHINE_ */
E 7
E 1
