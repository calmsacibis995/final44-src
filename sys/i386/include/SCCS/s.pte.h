h22347
s 00002/00002/00108
d D 8.1 93/06/11 15:48:26 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00013/00108
d D 5.5 91/05/09 18:08:22 william 6 5
c last minute changes, updating present version
e
s 00001/00001/00120
d D 5.4 91/01/18 14:32:15 william 5 4
c fixed just which copyright notice is included.
e
s 00008/00000/00113
d D 5.3 90/11/14 16:20:19 bill 4 3
c add exeception fault code manifest constants
e
s 00001/00004/00112
d D 5.2 90/11/14 16:05:33 bill 3 2
c formatting
e
s 00027/00009/00089
d D 5.1 90/04/24 18:52:35 william 2 1
c 1st Berkeley Release
e
s 00098/00000/00000
d D 1.1 90/03/12 15:48:16 bill 1 0
c date and time created 90/03/12 15:48:16 by bill
e
u
U
t
T
I 2
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 5
 * %sccs.include.noredist.c%
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
D 2
 * 386 page table entry and page table directory
E 2
I 2
D 3
 * 386 page table entry and page directory entry
E 3
I 3
 * 386 page table entry and page table directory
E 3
E 2
 * W.Jolitz, 8/89
 *
 * There are two major kinds of pte's: those which have ever existed (and are
 * thus either now in core or on the swap device), and those which have
 * never existed, but which will be filled on demand at first reference.
 * There is a structure describing each.  There is also an ancillary
 * structure used in page clustering.
 */

#ifndef LOCORE
D 2
struct ptd
E 2
I 2
struct pde
E 2
{
unsigned int	
D 2
		pg_v:1,			/* valid bit */
		pg_prot:2,		/* access control */
		pg_mbz1:2,		/* reserved, must be zero */
		pg_u:1,			/* hardware maintained 'used' bit */
E 2
I 2
		pd_v:1,			/* valid bit */
		pd_prot:2,		/* access control */
		pd_mbz1:2,		/* reserved, must be zero */
		pd_u:1,			/* hardware maintained 'used' bit */
E 2
		:1,			/* not used */
D 2
		pg_mbz2:2,		/* reserved, must be zero */
E 2
I 2
		pd_mbz2:2,		/* reserved, must be zero */
E 2
		:3,			/* reserved for software */
D 2
		pg_pfnum:20;		/* physical page frame number of pte's*/
E 2
I 2
		pd_pfnum:20;		/* physical page frame number of pte's*/
E 2
};
I 2
D 3

E 3
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
		pg_fod:1,		/* is fill on demand (=0) */
		:1,			/* must write back to swap (unused) */
		pg_nc:1,		/* 'uncacheable page' bit */
		pg_pfnum:20;		/* physical page frame number */
};
I 2
D 3

E 3
E 2
struct hpte
{
unsigned int	
		pg_high:12,		/* special for clustering */
		pg_pfnum:20;
};
I 2
D 3

E 3
E 2
struct fpte
{
unsigned int	
		pg_v:1,			/* valid bit */
		pg_prot:2,		/* access control */
		:5,
		pg_fileno:1,		/* file mapped from or TEXT or ZERO */
		pg_fod:1,		/* is fill on demand (=1) */
		pg_blkno:22;		/* file system block number */
};
#endif

I 2
#define	PD_MASK		0xffc00000	/* page directory address bits */
#define	PD_SHIFT	22		/* page directory address bits */

E 2
#define	PG_V		0x00000001
#define	PG_PROT		0x00000006 /* all protection bits . */
#define	PG_FOD		0x00000200
#define	PG_SWAPM	0x00000400
#define PG_N		0x00000800 /* Non-cacheable */
#define	PG_M		0x00000040
#define PG_U		0x00000020 /* not currently used */
D 2
#define	PG_PFNUM	0xfffff000
E 2
I 2
#define	PG_FRAME	0xfffff000
E 2

#define	PG_FZERO	0
#define	PG_FTEXT	1
#define	PG_FMAX		(PG_FTEXT)

#define	PG_NOACC	0
#define	PG_KR		0x00000000
#define	PG_KW		0x00000002
#define	PG_URKR		0x00000004
#define	PG_URKW		0x00000004
#define	PG_UW		0x00000006

/*
I 4
 * Page Protection Exception bits
 */

#define PGEX_P		0x01	/* Protection violation vs. not present */
#define PGEX_W		0x02	/* during a Write cycle */
#define PGEX_U		0x04	/* access from User mode (UPL) */

/*
E 4
 * Pte related macros
 */
#define	dirty(pte)	((pte)->pg_m)

#ifndef LOCORE
#ifdef KERNEL
D 6
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
E 6
I 6
/* utilities defined in pmap.c */
extern	struct pte *Sysmap;
E 6
#endif
#endif
E 1
