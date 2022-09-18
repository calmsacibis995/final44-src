h60249
s 00002/00002/00208
d D 8.1 93/06/11 15:48:14 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00209
d D 7.6 93/06/02 10:54:11 hibler 11 10
c add pmap_wired_count macro for mlock/munlock
e
s 00002/00001/00207
d D 7.5 92/02/19 18:39:31 mckusick 10 9
c eliminate variable kernel_pmap and function pmap_kernel
e
s 00008/00005/00200
d D 7.4 91/05/12 20:09:40 william 9 8
c ifdef KERNEL'ed the externs
e
s 00000/00028/00205
d D 7.3 91/05/10 11:27:29 mckusick 8 7
c not derived from CMU
e
s 00034/00007/00199
d D 7.2 91/05/09 23:16:50 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00004/00205
d D 7.1 91/05/09 22:28:57 william 6 5
c remove unnecessary multiple types of NULL
e
s 00001/00007/00208
d D 1.5 91/05/09 18:08:27 william 5 4
c last minute changes, updating present version
e
s 00002/00000/00213
d D 1.4 91/04/17 11:45:34 william 4 3
c correct attribution
e
s 00003/00020/00210
d D 1.3 91/04/15 17:14:55 william 3 2
c touchup, it finally works
e
s 00062/00007/00168
d D 1.2 91/04/15 17:10:26 william 2 1
c recursive map changes start here
e
s 00175/00000/00000
d D 1.1 91/01/18 21:10:51 william 1 0
c date and time created 91/01/18 21:10:51 by william
e
u
U
t
T
I 1
/* 
D 7
 * Copyright (c) 1987 Carnegie-Mellon University
E 7
D 12
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
D 7
 * The Mach Operating System project at Carnegie-Mellon University.
E 7
I 7
D 8
 * The Mach Operating System project at Carnegie-Mellon University,
E 8
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and William Jolitz of UUNET Technologies Inc.
E 7
 *
D 7
 * The CMU software License Agreement specifies the terms and conditions
 * for use and redistribution.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
I 4
D 7
 * This version by William Jolitz for UUNET Technologies, Inc.
E 7
I 7
 *	%W% (Berkeley) %G%
D 8
 */

/*
 * Copyright (c) 1987 Carnegie-Mellon University.
 * All rights reserved.
E 7
 *
I 7
 * Authors: Avadis Tevanian, Jr., Michael Wayne Young
 * 
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND 
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
E 8
 */

/*
E 7
E 4
I 2
 * Derived from hp300 version by Mike Hibler, this version by William
 * Jolitz uses a recursive map [a pde points to the page directory] to
 * map the page tables using the pagetables themselves. This is done to
 * reduce the impact on kernel virtual memory for lots of sparse address
 * space, and to reduce the cost of memory to each process.
 *
E 2
 * from hp300:	@(#)pmap.h	7.2 (Berkeley) 12/16/90
D 7
 *
 *	%W% (Berkeley) %G%
E 7
 */

#ifndef	_PMAP_MACHINE_
#define	_PMAP_MACHINE_	1

D 5
#include "sys/lock.h"
#include "machine/vmparam.h"
#include "vm/vm_statistics.h"

E 5
/*
 * 386 page table entry and page table directory
 * W.Jolitz, 8/89
 */

struct pde
{
unsigned int	
		pd_v:1,			/* valid bit */
		pd_prot:2,		/* access control */
		pd_mbz1:2,		/* reserved, must be zero */
		pd_u:1,			/* hardware maintained 'used' bit */
		:1,			/* not used */
		pd_mbz2:2,		/* reserved, must be zero */
		:3,			/* reserved for software */
		pd_pfnum:20;		/* physical page frame number of pte's*/
};

#define	PD_MASK		0xffc00000	/* page directory address bits */
D 2
#define	PD_SHIFT	22		/* page directory address bits */
E 2
I 2
#define	PT_MASK		0x003ff000	/* page table address bits */
#define	PD_SHIFT	22		/* page directory address shift */
#define	PG_SHIFT	12		/* page table address shift */
E 2

struct pte
{
unsigned int	
		pg_v:1,			/* valid bit */
		pg_prot:2,		/* access control */
		pg_mbz1:2,		/* reserved, must be zero */
		pg_u:1,			/* hardware maintained 'used' bit */
		pg_m:1,			/* hardware maintained modified bit */
		pg_mbz2:2,		/* reserved, must be zero */
		pg_w:1,			/* software, wired down page */
		:1,			/* software (unused) */
		pg_nc:1,		/* 'uncacheable page' bit */
		pg_pfnum:20;		/* physical page frame number */
};

#define	PG_V		0x00000001
I 2
#define	PG_RO		0x00000000
#define	PG_RW		0x00000002
#define	PG_u		0x00000004
E 2
#define	PG_PROT		0x00000006 /* all protection bits . */
#define	PG_W		0x00000200
#define PG_N		0x00000800 /* Non-cacheable */
#define	PG_M		0x00000040
#define PG_U		0x00000020
#define	PG_FRAME	0xfffff000

#define	PG_NOACC	0
#define	PG_KR		0x00000000
#define	PG_KW		0x00000002
#define	PG_URKR		0x00000004
#define	PG_URKW		0x00000004
#define	PG_UW		0x00000006

I 2
/* Garbage for current bastardized pager that assumes a hp300 */
#define	PG_NV	0
#define	PG_CI	0
E 2
/*
 * Page Protection Exception bits
 */

#define PGEX_P		0x01	/* Protection violation vs. not present */
#define PGEX_W		0x02	/* during a Write cycle */
#define PGEX_U		0x04	/* access from User mode (UPL) */

typedef struct pde	pd_entry_t;	/* page directory entry */
typedef struct pte	pt_entry_t;	/* Mach page table entry */

D 6
#define	PD_ENTRY_NULL	((pd_entry_t *) 0)
#define	PT_ENTRY_NULL	((pt_entry_t *) 0)

E 6
/*
 * One page directory, shared between
 * kernel and user modes.
 */
#define I386_PAGE_SIZE	NBPG
#define I386_PDR_SIZE	NBPDR

#define I386_KPDES	8 /* KPT page directory size */
#define I386_UPDES	NBPDR/sizeof(struct pde)-8 /* UPT page directory size */

D 2
#define I386_MAX_PTSIZE	I386_UPDES*NBPG	/* max size of UPT */
#define I386_MAX_KPTSIZE I386_KPDES*NBPG /* max memory to allocate to KPT */
E 2
I 2
#define	UPTDI		0x3f6		/* ptd entry for u./kernel&user stack */
#define	PTDPTDI		0x3f7		/* ptd entry that points to ptd! */
#define	KPTDI_FIRST	0x3f8		/* start of kernel virtual pde's */
#define	KPTDI_LAST	0x3fA		/* last of kernel virtual pde's */
E 2

I 2
D 3
#define I386_MAX_PTSIZE	NPTEPG*NBPG	/* max size of PT */
#ifdef old
#define I386_MAX_KPTSIZE 0x100000 /* max memory to allocate to KPT */

#define	I386_PTBASE	0xfe200000
#define	I386_PTMAXSIZE	0x01000000

E 2
/*
 * Kernel virtual address to page table entry and to physical address.
 */
#define	kvtopte(va) \
	(&Sysmap[((unsigned)(va) - VM_MIN_KERNEL_ADDRESS) >> PGSHIFT])
#define	ptetokv(pt) \
	((((pt_entry_t *)(pt) - Sysmap) << PGSHIFT) + VM_MIN_KERNEL_ADDRESS)
#define	kvtophys(va) \
	((kvtopte(va)->pg_pfnum << PGSHIFT) | ((int)(va) & PGOFSET))
E 3
I 2
D 9
extern	pt_entry_t	*Sysmap;
D 3
#else
E 3
E 2

E 9
/*
I 2
 * Address of current and alternate address space page table maps
 * and directories.
 */
D 9
extern struct pte PTmap[], APTmap[], Upte;
extern struct pde PTD[], APTD[], PTDpde, APTDpde, Upde;
E 9
I 9
#ifdef KERNEL
extern struct pte	PTmap[], APTmap[], Upte;
extern struct pde	PTD[], APTD[], PTDpde, APTDpde, Upde;
extern	pt_entry_t	*Sysmap;
E 9

D 9
extern int IdlePTD;
E 9
I 9
extern int	IdlePTD;	/* physical address of "Idle" state directory */
#endif
E 9

/*
 * virtual address to page table entry and
 * to physical address. Likewise for alternate address space.
I 3
 * Note: these work recursively, thus vtopte of a pte will give
 * the corresponding pde that in turn maps it.
E 3
 */
#define	vtopte(va)	(PTmap + i386_btop(va))
#define	kvtopte(va)	vtopte(va)
#define	ptetov(pt)	(i386_ptob(pt - PTmap)) 
#define	vtophys(va)  (i386_ptob(vtopte(va)->pg_pfnum) | ((int)(va) & PGOFSET))
I 3
#define ispt(va)	((va) >= UPT_MIN_ADDRESS && (va) <= KPT_MAX_ADDRESS)
E 3

#define	avtopte(va)	(APTmap + i386_btop(va))
#define	ptetoav(pt)	(i386_ptob(pt - APTmap)) 
#define	avtophys(va)  (i386_ptob(avtopte(va)->pg_pfnum) | ((int)(va) & PGOFSET))

/*
 * macros to generate page directory/table indicies
 */

#define	pdei(va)	(((va)&PD_MASK)>>PD_SHIFT)
#define	ptei(va)	(((va)&PT_MASK)>>PT_SHIFT)
D 3
#endif
E 3

/*
E 2
 * Pmap stuff
 */
D 5
#define PMAP_NULL	((pmap_t) 0)
E 5

struct pmap {
D 2
	pt_entry_t		*pm_ptab;	/* KVA of page table */
E 2
	pd_entry_t		*pm_pdir;	/* KVA of page directory */
I 2
D 5
	/* caddr_t			*pm_ptobj;	/* page table object */
E 5
E 2
	boolean_t		pm_pdchanged;	/* pdir changed */
	short			pm_dref;	/* page directory ref count */
	short			pm_count;	/* pmap reference count */
	simple_lock_data_t	pm_lock;	/* lock on pmap */
	struct pmap_statistics	pm_stats;	/* pmap statistics */
	long			pm_ptpages;	/* more stats: PT pages */
};

typedef struct pmap	*pmap_t;

I 9
#ifdef KERNEL
E 9
D 10
extern pmap_t		kernel_pmap;
E 10
I 10
extern struct pmap	kernel_pmap_store;
#define kernel_pmap (&kernel_pmap_store)
E 10
I 9
#endif
E 9

/*
 * Macros for speed
 */
#define PMAP_ACTIVATE(pmapp, pcbp) \
D 2
	if ((pmapp) != PMAP_NULL && (pmapp)->pm_pdchanged) { \
E 2
I 2
D 6
	if ((pmapp) != PMAP_NULL /*&& (pmapp)->pm_pdchanged */) {  \
E 6
I 6
	if ((pmapp) != NULL /*&& (pmapp)->pm_pdchanged */) {  \
E 6
E 2
		(pcbp)->pcb_cr3 = \
D 2
		    i386_btop(pmap_extract(kernel_pmap, (pmapp)->pm_pdir)); \
E 2
I 2
		    pmap_extract(kernel_pmap, (pmapp)->pm_pdir); \
E 2
D 5
		if ((pmapp) == u.u_procp->p_map->pmap) \
E 5
I 5
		if ((pmapp) == &curproc->p_vmspace->vm_pmap) \
E 5
			load_cr3((pcbp)->pcb_cr3); \
		(pmapp)->pm_pdchanged = FALSE; \
	}
I 2

E 2
#define PMAP_DEACTIVATE(pmapp, pcbp)

/*
 * For each vm_page_t, there is a list of all currently valid virtual
 * mappings of that page.  An entry is a pv_entry_t, the list is pv_table.
 */
typedef struct pv_entry {
	struct pv_entry	*pv_next;	/* next pv_entry */
	pmap_t		pv_pmap;	/* pmap where mapping lies */
	vm_offset_t	pv_va;		/* virtual address for mapping */
D 3
	pd_entry_t	*pv_ptpde;	/* non-zero if VA maps a PT page */
	pmap_t		pv_ptpmap;	/* if pv_ptpde, pmap for PT page */
E 3
	int		pv_flags;	/* flags */
} *pv_entry_t;

#define	PV_ENTRY_NULL	((pv_entry_t) 0)

#define	PV_CI		0x01	/* all entries must be cache inhibited */
#define PV_PTPAGE	0x02	/* entry maps a page table page */

#ifdef	KERNEL

pv_entry_t	pv_table;		/* array of entries, one per page */

#define pa_index(pa)		atop(pa - vm_first_phys)
#define pa_to_pvh(pa)		(&pv_table[pa_index(pa)])

#define	pmap_resident_count(pmap)	((pmap)->pm_stats.resident_count)
I 11
#define	pmap_wired_count(pmap)		((pmap)->pm_stats.wired_count)
E 11

D 2
extern	pt_entry_t	*Sysmap;
E 2
#endif	KERNEL

#endif	_PMAP_MACHINE_
E 1
