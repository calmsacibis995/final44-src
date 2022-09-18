h18041
s 00002/00002/00074
d D 8.1 93/06/10 23:02:30 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00075
d D 7.8 93/06/02 10:57:34 hibler 9 8
c add pmap_wired_count macro for mlock/munlock
e
s 00035/00053/00040
d D 7.7 93/05/09 18:00:51 ralph 8 7
c new improved pmap changes
e
s 00001/00001/00092
d D 7.6 93/02/04 19:37:45 ralph 7 6
c added more kernel virtual address space
e
s 00002/00002/00091
d D 7.5 92/10/24 14:18:48 ralph 6 5
c increase kernel VM size
e
s 00008/00006/00085
d D 7.4 92/05/28 14:34:38 mckusick 5 3
c speedups from Rick Macklem
e
s 00001/00001/00090
d R 7.4 92/05/20 10:45:54 mckusick 4 3
c improve running time (from Macklem)
e
s 00001/00001/00090
d D 7.3 92/02/29 14:55:24 ralph 3 2
c increase kernel vm area
e
s 00002/00003/00089
d D 7.2 92/02/19 18:40:49 mckusick 2 1
c eliminate variable kernel_pmap and function pmap_kernel
e
s 00092/00000/00000
d D 7.1 92/01/07 20:35:50 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/* 
 * Copyright (c) 1987 Carnegie-Mellon University
D 10
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef	_PMAP_MACHINE_
#define	_PMAP_MACHINE_

/*
D 8
 * TLB hash table values.
 * SHIFT2 should shift virtual address bit 22 to the high bit of the index.
 *			address:	index:
 *	USRTEXT		0x00400000	10xxxxxxx
 *	USRDATA		0x10000000	00xxxxxxx
 *	USRSTACK	0x7FFFFFFF	11xxxxxxx
 * This gives 1/2 the table to data, 1/4 for text and 1/4 for stack.
 * Note: the current process has its hash table mapped at PMAP_HASH_UADDR.
 *	the kernel's hash table is mapped at PMAP_HASH_KADDR.
 *	The size of the hash table is known in locore.s.
E 8
I 8
 * The user address space is 2Gb (0x0 - 0x80000000).
 * User programs are laid out in memory as follows:
 *			address
 *	USRTEXT		0x00001000
 *	USRDATA		USRTEXT + text_size
 *	USRSTACK	0x7FFFFFFF
 *
 * The user address space is mapped using a two level structure where
 * virtual address bits 30..22 are used to index into a segment table which
 * points to a page worth of PTEs (4096 page can hold 1024 PTEs).
 * Bits 21..12 are then used to index a PTE which describes a page within 
 * a segment.
 *
E 8
 * The wired entries in the TLB will contain the following:
D 8
 *	UPAGES			(for curproc)
 *	PMAP_HASH_UPAGES	(for curproc)
 *	PMAP_HASH_KPAGES	(for kernel)
D 6
 * The kernel doesn't actual use a pmap_hash_t, the pm_hash field is NULL and
E 6
I 6
 * The kernel doesn't actually use a pmap_hash_t, the pm_hash field is NULL and
E 6
 * all the PTE entries are stored in a single array at PMAP_HASH_KADDR.
 * If we need more KPAGES that the TLB has wired entries, then we can switch
 * to a global pointer for the kernel TLB table.
 * If we try to use a hash table for the kernel, wired TLB entries become a
 * problem.
 * Note: PMAP_HASH_UPAGES should be a multiple of MACH pages (see pmap_enter()).
E 8
I 8
 *	0-1	(UPAGES)	for curproc user struct and kernel stack.
 *
 * Note: The kernel doesn't use the same data structures as user programs.
 * All the PTE entries are stored in a single array in Sysmap which is
 * dynamically allocated at boot time.
E 8
 */
D 8
#define PMAP_HASH_UPAGES	1
D 3
#define PMAP_HASH_KPAGES	2
E 3
I 3
D 6
#define PMAP_HASH_KPAGES	3
E 6
I 6
D 7
#define PMAP_HASH_KPAGES	4
E 7
I 7
#define PMAP_HASH_KPAGES	5
E 7
E 6
E 3
#define PMAP_HASH_UADDR		(UADDR - PMAP_HASH_UPAGES * NBPG)
#define PMAP_HASH_KADDR		(UADDR - (PMAP_HASH_UPAGES + PMAP_HASH_KPAGES) * NBPG)
D 5
#define PMAP_HASH_NUM_ENTRIES	512
#define PMAP_HASH_SIZE_SHIFT	3
E 5
I 5
#define PMAP_HASH_NUM_ENTRIES	256
#define PMAP_HASH_SIZE_SHIFT	4
E 5
#define PMAP_HASH_SHIFT1	12
D 5
#define PMAP_HASH_SHIFT2	14
E 5
I 5
#define PMAP_HASH_SHIFT2	21
E 5
#define PMAP_HASH_MASK1		0x07f
D 5
#define PMAP_HASH_MASK2		0x180
E 5
I 5
#define PMAP_HASH_MASK2		0x080
E 5
#define PMAP_HASH_SIZE		(PMAP_HASH_NUM_ENTRIES*sizeof(struct pmap_hash))
E 8

D 8
/* compute pointer to pmap hash table */
#define PMAP_HASH(va) \
	((((va) >> PMAP_HASH_SHIFT1) & PMAP_HASH_MASK1) | \
	 (((va) >> PMAP_HASH_SHIFT2) & PMAP_HASH_MASK2))
E 8
I 8
#define pmax_trunc_seg(x)	((vm_offset_t)(x) & ~SEGOFSET)
#define pmax_round_seg(x)	(((vm_offset_t)(x) + SEGOFSET) & ~SEGOFSET)
#define pmap_segmap(m, v)	((m)->pm_segtab->seg_tab[((v) >> SEGSHIFT)])
E 8

D 8
/*
 * A TLB hash entry.
 */
typedef struct pmap_hash {
D 5
	u_int	low;		/* The TLB low register value. */
	u_int	high;		/* The TLB high register value. */
E 5
I 5
	struct {
		u_int	low;		/* The TLB low register value. */
		u_int	high;		/* The TLB high register value. */
	} pmh_pte[2];
E 5
} *pmap_hash_t;
E 8
I 8
#define PMAP_SEGTABSIZE		512
E 8

I 8
union pt_entry;

struct segtab {
	union pt_entry	*seg_tab[PMAP_SEGTABSIZE];
};

E 8
/*
 * Machine dependent pmap structure.
 */
typedef struct pmap {
	int			pm_count;	/* pmap reference count */
	simple_lock_data_t	pm_lock;	/* lock on pmap */
	struct pmap_statistics	pm_stats;	/* pmap statistics */
D 8
	int			pm_flags;	/* see below */
E 8
	int			pm_tlbpid;	/* address space tag */
D 8
	pmap_hash_t		pm_hash;	/* TLB cache */
	unsigned		pm_hash_ptes[PMAP_HASH_UPAGES];
E 8
I 8
	u_int			pm_tlbgen;	/* TLB PID generation number */
	struct segtab		*pm_segtab;	/* pointers to pages of PTEs */
E 8
} *pmap_t;

D 8
#define PM_MODIFIED	1		/* flush tlbpid before resume() */

E 8
/*
 * Defines for pmap_attributes[phys_mach_page];
 */
#define PMAP_ATTR_MOD	0x01	/* page has been modified */
#define PMAP_ATTR_REF	0x02	/* page has been referenced */

#ifdef	KERNEL
D 2
#define	pmap_kernel()	(kernel_pmap)

extern	pmap_t kernel_pmap;
E 2
I 2
D 8
extern struct pmap kernel_pmap_store;
#define kernel_pmap (&kernel_pmap_store)
E 8
E 2
extern	char *pmap_attributes;		/* reference and modify bits */
D 8
#endif	KERNEL
#endif	_PMAP_MACHINE_
E 8
I 8
extern	struct pmap kernel_pmap_store;
#define kernel_pmap (&kernel_pmap_store)
I 9
#define	pmap_wired_count(pmap) 	((pmap)->pm_stats.wired_count)
E 9
#endif	/* KERNEL */

#endif	/* _PMAP_MACHINE_ */
E 8
E 1
