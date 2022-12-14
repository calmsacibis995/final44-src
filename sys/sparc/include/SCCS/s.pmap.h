h35034
s 00002/00002/00150
d D 8.1 93/06/11 15:12:19 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00150
d D 7.5 93/05/25 03:39:35 torek 5 4
c pedantically ANSI
e
s 00002/00002/00150
d D 7.4 93/04/20 18:54:34 torek 4 3
c spelling
e
s 00001/00001/00151
d D 7.3 92/10/11 12:42:15 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00147
d D 7.2 92/07/21 16:41:33 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00147/00000/00000
d D 7.1 92/07/13 00:43:04 torek 1 0
c date and time created 92/07/13 00:43:04 by torek
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: pmap.h,v 1.9 92/06/17 06:10:22 torek Exp $
E 4
I 4
D 5
 * from: $Header: pmap.h,v 1.10 92/11/26 02:04:40 torek Exp $
E 5
I 5
 * from: $Header: pmap.h,v 1.11 93/05/25 10:36:09 torek Exp $
E 5
E 4
 */

#ifndef	_SPARC_PMAP_H_
#define _SPARC_PMAP_H_

D 3
#include "machine/pte.h"
E 3
I 3
#include <machine/pte.h>
E 3

/*
 * Pmap structure.
 *
 * The pmap structure really comes in two variants, one---a single
 * instance---for kernel virtual memory and the other---up to nproc
 * instances---for user virtual memory.  Unfortunately, we have to mash
 * both into the same structure.  Fortunately, they are almost the same.
 *
 * The kernel begins at 0xf8000000 and runs to 0xffffffff (although
 * some of this is not actually used).  Kernel space, including DVMA
 * space (for now?), is mapped identically into all user contexts.
 * There is no point in duplicating this mapping in each user process
 * so they do not appear in the user structures.
 *
 * User space begins at 0x00000000 and runs through 0x1fffffff,
 * then has a `hole', then resumes at 0xe0000000 and runs until it
 * hits the kernel space at 0xf8000000.  This can be mapped
 * contiguously by ignorning the top two bits and pretending the
 * space goes from 0 to 37ffffff.  Typically the lower range is
 * used for text+data and the upper for stack, but the code here
 * makes no such distinction.
 *
 * Since each virtual segment covers 256 kbytes, the user space
 * requires 3584 segments, while the kernel (including DVMA) requires
 * only 512 segments.
 *
 * The segment map entry for virtual segment vseg is offset in
 * pmap->pm_rsegmap by 0 if pmap is not the kernel pmap, or by
 * NUSEG if it is.  We keep a pointer called pmap->pm_segmap
 * pre-offset by this value.  pmap->pm_segmap thus contains the
 * values to be loaded into the user portion of the hardware segment
 * map so as to reach the proper PMEGs within the MMU.  The kernel
 * mappings are `set early' and are always valid in every context
 * (every change is always propagated immediately).
 *
 * The PMEGs within the MMU are loaded `on demand'; when a PMEG is
 * taken away from context `c', the pmap for context c has its
 * corresponding pm_segmap[vseg] entry marked invalid (the MMU segment
 * map entry is also made invalid at the same time).  Thus
 * pm_segmap[vseg] is the `invalid pmeg' number (127 or 511) whenever
 * the corresponding PTEs are not actually in the MMU.  On the other
 * hand, pm_pte[vseg] is NULL only if no pages in that virtual segment
 * are in core; otherwise it points to a copy of the 32 or 64 PTEs that
 * must be loaded in the MMU in order to reach those pages.
 * pm_npte[vseg] counts the number of valid pages in each vseg.
 *
 * XXX performance: faster to count valid bits?
 *
 * The kernel pmap cannot malloc() PTEs since malloc() will sometimes
 * allocate a new virtual segment.  Since kernel mappings are never
 * `stolen' out of the the MMU, we just keep all its PTEs there, and
 * have no software copies.  Its mmu entries are nonetheless kept on lists
 * so that the code that fiddles with mmu lists has something to fiddle.
 */
#define	NKSEG	((int)((-(unsigned)KERNBASE) / NBPSG))	/* i.e., 512 */
#define	NUSEG	(4096 - NKSEG)				/* i.e., 3584 */

/* data appearing in both user and kernel pmaps */
struct pmap_common {
	union	ctxinfo *pmc_ctx;	/* current context, if any */
	int	pmc_ctxnum;		/* current context's number */
#if NCPUS > 1
	simple_lock_data_t pmc_lock;	/* spinlock */
#endif
	int	pmc_refcount;		/* just what it says */
	struct	mmuentry *pmc_mmuforw;	/* pmap pmeg chain */
	struct	mmuentry **pmc_mmuback;	/* (two way street) */
	pmeg_t	*pmc_segmap;		/* points to pm_rsegmap per above */
	u_char	*pmc_npte;		/* points to pm_rnpte */
	int	**pmc_pte;		/* points to pm_rpte */
};

/* data appearing only in user pmaps */
struct pmap {
	struct	pmap_common pmc;
	pmeg_t	pm_rsegmap[NUSEG];	/* segment map */
	u_char	pm_rnpte[NUSEG];	/* number of valid PTEs per seg */
	int	*pm_rpte[NUSEG];	/* points to PTEs for valid segments */
};

/* data appearing only in the kernel pmap */
struct kpmap {
	struct	pmap_common pmc;
	pmeg_t	pm_rsegmap[NKSEG];	/* segment map */
	u_char	pm_rnpte[NKSEG];	/* number of valid PTEs per kseg */
	int	*pm_rpte[NKSEG];	/* always NULL */
};

#define	pm_ctx		pmc.pmc_ctx
#define	pm_ctxnum	pmc.pmc_ctxnum
#define	pm_lock		pmc.pmc_lock
#define	pm_refcount	pmc.pmc_refcount
#define	pm_mmuforw	pmc.pmc_mmuforw
#define	pm_mmuback	pmc.pmc_mmuback
#define	pm_segmap	pmc.pmc_segmap
#define	pm_npte		pmc.pmc_npte
#define	pm_pte		pmc.pmc_pte

#ifdef KERNEL

typedef struct pmap *pmap_t;
#define PMAP_NULL	((pmap_t)0)

extern struct kpmap kernel_pmap_store;
#define	kernel_pmap ((struct pmap *)(&kernel_pmap_store))

#define PMAP_ACTIVATE(pmap, pcb, iscurproc)
#define PMAP_DEACTIVATE(pmap, pcb)

/*
 * Since PTEs also contain type bits, we have to have some way
 * to tell pmap_enter `this is an IO page' or `this is not to
 * be cached'.  Since physical addresses are always aligned, we
 * can do this with the low order bits.
 *
 * The ordering below is important: PMAP_PGTYPE << PG_TNC must give
 * exactly the PG_NC and PG_TYPE bits.
 */
#define	PMAP_OBIO	1		/* tells pmap_enter to use PG_OBIO */
#define	PMAP_VME16	2		/* etc */
#define	PMAP_VME32	3		/* etc */
#define	PMAP_NC		4		/* tells pmap_enter to set PG_NC */
#define	PMAP_TNC	7		/* mask to get PG_TYPE & PG_NC */

D 5
#endif	KERNEL
E 5
I 5
#endif /* KERNEL */
E 5

#endif /* _SPARC_PMAP_H_ */
E 1
