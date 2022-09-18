h39462
s 00002/00002/00077
d D 8.1 93/06/10 23:02:45 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00005/00071
d D 7.3 93/05/09 18:01:58 ralph 3 2
c new improved pmap changes
e
s 00001/00003/00075
d D 7.2 92/02/29 14:46:47 ralph 2 1
c removed kvtophys; not used.
e
s 00078/00000/00000
d D 7.1 92/01/07 17:32:21 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: pte.h 1.11 89/09/03$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * R2000 hardware page table entry
 */

#ifndef LOCORE
struct pte {
#if BYTE_ORDER == BIG_ENDIAN
unsigned int	pg_pfnum:20,		/* HW: core page frame number or 0 */
		pg_n:1,			/* HW: non-cacheable bit */
		pg_m:1,			/* HW: modified (dirty) bit */
		pg_v:1,			/* HW: valid bit */
		pg_g:1,			/* HW: ignore pid bit */
		:4,
		pg_swapm:1,		/* SW: page must be forced to swap */
		pg_fod:1,		/* SW: is fill on demand (=0) */
		pg_prot:2;		/* SW: access control */
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
unsigned int	pg_prot:2,		/* SW: access control */
		pg_fod:1,		/* SW: is fill on demand (=0) */
		pg_swapm:1,		/* SW: page must be forced to swap */
		:4,
		pg_g:1,			/* HW: ignore pid bit */
		pg_v:1,			/* HW: valid bit */
		pg_m:1,			/* HW: modified (dirty) bit */
		pg_n:1,			/* HW: non-cacheable bit */
		pg_pfnum:20;		/* HW: core page frame number or 0 */
#endif
};

D 3
typedef union {
E 3
I 3
typedef union pt_entry {
E 3
	unsigned int	pt_entry;	/* for copying, etc. */
	struct pte	pt_pte;		/* for getting to bits by name */
} pt_entry_t;	/* Mach page table entry */
#endif /* LOCORE */

#define	PT_ENTRY_NULL	((pt_entry_t *) 0)

#define	PG_PROT		0x00000003
#define PG_RW		0x00000000
#define PG_RO		0x00000001
#define PG_WIRED	0x00000002
#define	PG_G		0x00000100
#define	PG_V		0x00000200
#define	PG_NV		0x00000000
#define	PG_M		0x00000400
#define	PG_N		0x00000800
#define	PG_FRAME	0xfffff000
#define PG_SHIFT	12
#define	PG_PFNUM(x)	(((x) & PG_FRAME) >> PG_SHIFT)

I 3
#if defined(KERNEL) && !defined(LOCORE)
E 3
/*
D 2
 * Kernel virtual address to page table entry and to physical address.
E 2
I 2
 * Kernel virtual address to page table entry and visa versa.
E 2
 */
#define	kvtopte(va) \
D 3
	((pt_entry_t *)PMAP_HASH_KADDR + \
	(((vm_offset_t)(va) - VM_MIN_KERNEL_ADDRESS) >> PGSHIFT))
E 3
I 3
	(Sysmap + (((vm_offset_t)(va) - VM_MIN_KERNEL_ADDRESS) >> PGSHIFT))
E 3
#define	ptetokv(pte) \
D 3
	((((pt_entry_t *)(pte) - PMAP_HASH_KADDR) << PGSHIFT) + \
	VM_MIN_KERNEL_ADDRESS)
E 3
I 3
	((((pt_entry_t *)(pte) - Sysmap) << PGSHIFT) + VM_MIN_KERNEL_ADDRESS)

extern	pt_entry_t *Sysmap;		/* kernel pte table */
extern	u_int Sysmapsize;		/* number of pte's in Sysmap */
#endif
E 3
D 2
#define	kvtophys(va) \
	((kvtopte(va)->pt_entry & PG_FRAME) | ((unsigned)(va) & PGOFSET))
E 2
E 1
