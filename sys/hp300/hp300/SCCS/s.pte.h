h37214
s 00002/00002/00116
d D 8.1 93/06/10 21:41:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00004/00083
d D 7.4 92/06/05 15:36:46 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00038/00072/00049
d D 7.3 91/05/08 13:57:54 karels 3 2
c merge with stuff from pmap.h
e
s 00002/00014/00119
d D 7.2 90/12/05 19:30:21 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00133/00000/00000
d D 7.1 90/05/08 17:51:20 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 5
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 4
 * from: Utah $Hdr: pte.h 1.11 89/09/03$
E 4
I 4
 * from: Utah $Hdr: pte.h 1.13 92/01/20$
E 4
 *
 *	%W% (Berkeley) %G%
 */

/*
D 3
 * HP300 page table entry
 *
 * There are two major kinds of pte's: those which have ever existed (and are
 * thus either now in core or on the swap device), and those which have
 * never existed, but which will be filled on demand at first reference.
 * There is a structure describing each.  There is also an ancillary
 * structure used in page clustering.
E 3
I 3
 * HP300 hardware segment/page table entries
E 3
 */

D 3
#ifndef LOCORE
struct ste
{
unsigned int	sg_pfnum:20,		/* page table frame number */
		:8,			/* reserved at 0 */
		:1,			/* reserved at 1 */
		sg_prot:1,		/* write protect bit */
		sg_v:2;			/* valid bits */
E 3
I 3
struct ste {
	unsigned int	sg_pfnum:20;	/* page table frame number */
	unsigned int	:8;		/* reserved at 0 */
	unsigned int	:1;		/* reserved at 1 */
	unsigned int	sg_prot:1;	/* write protect bit */
	unsigned int	sg_v:2;		/* valid bits */
E 3
};

I 4
struct ste40 {
	unsigned int	sg_ptaddr:24;	/* page table page addr */
	unsigned int	:4;		/* reserved at 0 */
	unsigned int	sg_u;		/* hardware modified (dirty) bit */
	unsigned int	sg_prot:1;	/* write protect bit */
	unsigned int	sg_v:2;		/* valid bits */
};

E 4
D 3
struct pte
{
unsigned int	pg_pfnum:20,		/* page frame number or 0 */
		:3,
		pg_fod:1,		/* is fill on demand (=0) */
		:1,			/* reserved at zero */
		pg_ci:1,		/* cache inhibit bit */
		:1,			/* reserved at zero */
		pg_m:1,			/* hardware modified (dirty) bit */
		pg_u:1,			/* hardware used (reference) bit */
		pg_prot:1,		/* write protect bit */
		pg_v:2;			/* valid bit */
E 3
I 3
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
E 3
};

D 3
/* not used */
struct hpte
{
unsigned int	pg_pfnum:20,
		pg_high:12;		/* special for clustering */
};
E 3
I 3
typedef struct ste	st_entry_t;	/* segment table entry */
typedef struct pte	pt_entry_t;	/* Mach page table entry */
E 3

D 3
struct fpte
{
unsigned int	pg_blkno:22,		/* file system block number */
		pg_fileno:1,		/* file mapped from or TEXT or ZERO */
		pg_fod:1,		/* is fill on demand (=1) */
		:6,
		pg_v:2;
};
#endif
E 3
I 3
#define	PT_ENTRY_NULL	((pt_entry_t *) 0)
#define	ST_ENTRY_NULL	((st_entry_t *) 0)
E 3

D 3
#define	SG_V		0x00000002
E 3
I 3
#define	SG_V		0x00000002	/* segment is valid */
E 3
#define	SG_NV		0x00000000
D 3
#define	SG_PROT		0x00000004
E 3
I 3
#define	SG_PROT		0x00000004	/* access protection mask */
E 3
#define	SG_RO		0x00000004
#define	SG_RW		0x00000000
I 4
#define	SG_U		0x00000008	/* modified bit (68040) */
E 4
#define	SG_FRAME	0xfffff000
#define	SG_IMASK	0xffc00000
D 4
#define	SG_PMASK	0x003ff000
E 4
#define	SG_ISHIFT	22
I 4
#define	SG_PMASK	0x003ff000
E 4
#define	SG_PSHIFT	12

I 4
/* 68040 additions */
#define	SG4_MASK1	0xfe000000
#define	SG4_SHIFT1	25
#define	SG4_MASK2	0x01fc0000
#define	SG4_SHIFT2	18
#define	SG4_MASK3	0x0003f000
#define	SG4_SHIFT3	12
#define	SG4_ADDR1	0xfffffe00
#define	SG4_ADDR2	0xffffff00
#define	SG4_LEV1SIZE	128
#define	SG4_LEV2SIZE	128
#define	SG4_LEV3SIZE	64

E 4
#define	PG_V		0x00000001
#define	PG_NV		0x00000000
#define	PG_PROT		0x00000004
#define	PG_U		0x00000008
#define	PG_M		0x00000010
D 3
#define	PG_FOD		0x00000100
E 3
I 3
#define	PG_W		0x00000100
E 3
#define	PG_RO		0x00000004
#define	PG_RW		0x00000000
#define	PG_FRAME	0xfffff000
#define	PG_CI		0x00000040
D 3
#define	PG_PFNUM(x)	(((x) & PG_FRAME) >> PGSHIFT)
E 3
I 3
#define PG_SHIFT	12
#define	PG_PFNUM(x)	(((x) & PG_FRAME) >> PG_SHIFT)
E 3

D 3
/*
 * Pseudo protections.
 * Note that PG_URKW is not defined intuitively, but it is currently only
 * used in vgetu() to initialize the u-area PTEs in the process address
 * space.  Since the kernel never accesses the u-area thru these we are ok.
 */
#define	PG_KW		PG_RW
#define	PG_URKR		PG_RO
#define	PG_URKW		PG_RO
#define	PG_UW		PG_RW
E 3
I 3
D 4
#define HP_STSIZE	HP_PAGE_SIZE	/* segment table size */
#define HP_MAX_PTSIZE	HP_SEG_SIZE	/* max size of UPT */
E 4
I 4
/* 68040 additions */
#define	PG_CMASK	0x00000060	/* cache mode mask */
#define	PG_CWT		0x00000000	/* writethrough caching */
#define	PG_CCB		0x00000020	/* copyback caching */
#define	PG_CIS		0x00000040	/* cache inhibited serialized */
#define	PG_CIN		0x00000060	/* cache inhibited nonserialized */
#define	PG_SO		0x00000080	/* supervisor only */

#define HP_STSIZE	(MAXUL2SIZE*SG4_LEV2SIZE*sizeof(st_entry_t))
					/* user process segment table size */
#define HP_MAX_PTSIZE	0x400000	/* max size of UPT */
E 4
#define HP_MAX_KPTSIZE	0x100000	/* max memory to allocate to KPT */
#define HP_PTBASE	0x10000000	/* UPT map base address */
#define HP_PTMAXSIZE	0x70000000	/* UPT map maximum size */
E 3

D 3
#define	PG_FZERO	0
#define	PG_FTEXT	1
#define	PG_FMAX		(PG_FTEXT)

E 3
/*
D 3
 * Pte related macros
 */
#define	dirty(pte)	((pte)->pg_m)

/*
E 3
 * Kernel virtual address to page table entry and to physical address.
 */
D 3
#define	kvtopte(va) (&Sysmap[((unsigned)(va) &~ KERNBASE) >> PGSHIFT])
#define	ptetokv(pt) ((((struct pte *)(pt) - Sysmap) << PGSHIFT) | KERNBASE)
#define	kvtophys(x) ((kvtopte(x)->pg_pfnum << PGSHIFT) | ((int)(x) & PGOFSET))
E 3
I 3
#define	kvtopte(va) \
	(&Sysmap[((unsigned)(va) - VM_MIN_KERNEL_ADDRESS) >> PGSHIFT])
#define	ptetokv(pt) \
	((((pt_entry_t *)(pt) - Sysmap) << PGSHIFT) + VM_MIN_KERNEL_ADDRESS)
#define	kvtophys(va) \
	((kvtopte(va)->pg_pfnum << PGSHIFT) | ((int)(va) & PGOFSET))
E 3

D 3
#if defined(KERNEL) && !defined(LOCORE)
D 2
/* utilities defined in locore.s */
extern	struct pte Sysmap[];
extern	struct pte Usrptmap[];
extern	struct pte usrpt[];
extern	struct pte Swapmap[];
extern	struct pte Forkmap[];
extern	struct pte Xswapmap[];
extern	struct pte Xswap2map[];
extern	struct pte Pushmap[];
extern	struct pte Vfmap[];
extern	struct pte mmap[];
extern	struct pte msgbufmap[];
extern	struct pte kmempt[], ekmempt[];
extern	struct ste Sysseg[];
E 2
I 2
/* utilities defined in pmap.c */
extern	struct pte *Sysmap;
E 2
#endif /* defined(KERNEL) && !defined(LOCORE) */
E 3
E 1
