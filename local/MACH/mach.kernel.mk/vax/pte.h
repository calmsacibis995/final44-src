/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	pte.h,v $
 * Revision 2.6  89/03/09  22:20:51  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:27:48  gm0w
 * 	Changes for cleanup.
 * 
 * 19-Apr-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: Remove unneeded page maps.
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)pte.h	7.1 (Berkeley) 6/5/86
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

#ifndef	LOCORE
struct pte
{
unsigned int	pg_pfnum:21,		/* core page frame number or 0 */
		:2,
		pg_vreadm:1,		/* modified since vread (or with _m) */
		pg_swapm:1,		/* have to write back to swap */
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

#define PG_V		0x80000000
#define PG_PROT		0x78000000
#define PG_M		0x04000000
#define PG_FOD		0x02000000
#define PG_VREADM	0x00800000
#define PG_PFNUM	0x001fffff

#define PG_FZERO	0
#define PG_FTEXT	1
#define PG_FMAX		(PG_FTEXT)

#define PG_NOACC	0
#define PG_KW		0x10000000
#define PG_KR		0x18000000
#define PG_UW		0x20000000
#define PG_URKW		0x70000000
#define PG_URKR		0x78000000

/*
 * Pte related macros
 */
#define dirty(pte)	((pte)->pg_fod == 0 && (pte)->pg_pfnum && \
			    ((pte)->pg_m || (pte)->pg_swapm))

#ifndef	LOCORE
#ifdef	KERNEL

/* utilities defined in locore.s */
extern	struct pte *Sysmap;
			/* one of many names for the kernel page table */
#endif
#endif
