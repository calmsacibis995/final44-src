/*-
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)pte.h	7.7 (Berkeley) 5/8/91
 */

/*
 * VAX page table entry
 *
 * There are two major kinds of pte's: those which have ever existed (and are
 * thus either now in core or on the swap device), and those which have
 * never existed, but which will be filled on demand at first reference.
 * There is a structure describing each.  There is also an ancillary
 * structure used in page clustering.
 */

#ifndef LOCORE
struct pte
{
unsigned int	pg_pfnum:21,		/* core page frame number or 0 */
		:2,
		pg_vreadm:1,		/* modified since vread (or with _m) */
		:1,
		pg_fod:1,		/* is fill on demand (=0) */
		pg_m:1,			/* hardware maintained modified bit */
		pg_prot:4,		/* access control */
		pg_v:1;			/* valid bit */
};
struct hpte
{
unsigned int	pg_pfnum:21,
		:2,
		pg_high:9;		/* special for clustering */
};
struct fpte
{
unsigned int	pg_blkno:24,		/* file system block number */
		pg_fileno:1,		/* file mapped from or TEXT or ZERO */
		pg_fod:1,		/* is fill on demand (=1) */
		:1,
		pg_prot:4,
		pg_v:1;
};
#endif

#define	PG_V		0x80000000
#define	PG_PROT		0x78000000
#define	PG_M		0x04000000
#define	PG_FOD		0x02000000
#define	PG_VREADM	0x00800000
#define	PG_PFNUM	0x001fffff

#define	PG_FZERO	0
#define	PG_FTEXT	1
#define	PG_FMAX		(PG_FTEXT)

#define	PG_NOACC	0
#define	PG_KW		0x10000000
#define	PG_KR		0x18000000
#define	PG_UW		0x20000000
#define	PG_URKW		0x70000000
#define	PG_URKR		0x78000000

/*
 * Pte related macros
 */
#define	dirty(pte)	((pte)->pg_m)

/*
 * Kernel virtual address to page table entry and to physical address.
 */
#define	kvtopte(va) (&Sysmap[((unsigned)(va) &~ KERNBASE) >> PGSHIFT])
#define	kvtophys(x) ((kvtopte(x)->pg_pfnum << PGSHIFT) | ((int)(x) & PGOFSET))

#if defined(KERNEL) && !defined(LOCORE)
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
extern	struct pte Nexmap[][16];
#if VAX8600
extern	struct pte Ioamap[][1];
#endif
#ifdef NFS
extern	struct pte Nfsiomap[];
#endif
#ifdef MFS
extern	struct pte Mfsiomap[];
#endif
#endif /* defined(KERNEL) && !defined(LOCORE) */
