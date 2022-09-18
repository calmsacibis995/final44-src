h64983
s 00002/00002/00162
d D 8.1 93/06/11 15:48:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00162
d D 7.1 91/05/09 23:16:51 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00163
d D 5.3 91/01/15 15:21:39 william 4 3
c trivia, reno changes, and kernel reorg
e
s 00022/00000/00142
d D 5.2 90/11/14 16:16:36 bill 3 2
c add exception code bits
e
s 00000/00000/00142
d D 5.1 90/04/24 18:52:37 william 2 1
c 1st Berkeley Release
e
s 00142/00000/00000
d D 1.1 90/03/12 15:48:21 bill 1 0
c date and time created 90/03/12 15:48:21 by bill
e
u
U
t
T
I 3
/*-
I 5
 * Copyright (c) 1989, 1990 William F. Jolitz
E 5
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
D 4
 * the University of Utah, and William Jolitz.
E 4
I 4
 * William Jolitz.
E 4
 *
D 5
 * %sccs.include.386.c%
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
/*
 * 386 Segmentation Data Structures and definitions
 *	William F. Jolitz (william@ernie.berkeley.edu) 6/20/1989
I 3
D 5
 * Copyright (c) 1989,1990 William F. Jolitz
E 5
E 3
 */

/*
 * Selectors
 */

#define	ISPL(s)	((s)&3)		/* what is the priority level of a selector */
#define	SEL_KPL	0		/* kernel priority level */	
#define	SEL_UPL	3		/* user priority level */	
#define	ISLDT(s)	((s)&SEL_LDT)	/* is it local or global */
#define	SEL_LDT	4		/* local descriptor table */	
#define	IDXSEL(s)	(((s)>>3) & 0x1fff)		/* index of selector */
#define	LSEL(s,r)	(((s)<<3) | SEL_LDT | r)	/* a local selector */
#define	GSEL(s,r)	(((s)<<3) | r)			/* a global selector */

/*
 * Memory and System segment descriptors
 */
struct	segment_descriptor	{
	unsigned sd_lolimit:16 ;	/* segment extent (lsb) */
	unsigned sd_lobase:24 ;		/* segment base address (lsb) */
	unsigned sd_type:5 ;		/* segment type */
	unsigned sd_dpl:2 ;		/* segment descriptor priority level */
	unsigned sd_p:1 ;		/* segment descriptor present */
	unsigned sd_hilimit:4 ;		/* segment extent (msb) */
	unsigned sd_xx:2 ;		/* unused */
	unsigned sd_def32:1 ;		/* default 32 vs 16 bit size */
	unsigned sd_gran:1 ;		/* limit granularity (byte/page units)*/
	unsigned sd_hibase:8 ;		/* segment base address  (msb) */
} ;

/*
 * Gate descriptors (e.g. indirect descriptors)
 */
struct	gate_descriptor	{
	unsigned gd_looffset:16 ;	/* gate offset (lsb) */
	unsigned gd_selector:16 ;	/* gate segment selector */
	unsigned gd_stkcpy:5 ;		/* number of stack wds to cpy */
	unsigned gd_xx:3 ;		/* unused */
	unsigned gd_type:5 ;		/* segment type */
	unsigned gd_dpl:2 ;		/* segment descriptor priority level */
	unsigned gd_p:1 ;		/* segment descriptor present */
	unsigned gd_hioffset:16 ;	/* gate offset (msb) */
} ;

/*
 * Generic descriptor
 */
union	descriptor	{
	struct	segment_descriptor sd;
	struct	gate_descriptor gd;
};
#define	d_type	gd.gd_type

	/* system segments and gate types */
#define	SDT_SYSNULL	 0	/* system null */
#define	SDT_SYS286TSS	 1	/* system 286 TSS available */
#define	SDT_SYSLDT	 2	/* system local descriptor table */
#define	SDT_SYS286BSY	 3	/* system 286 TSS busy */
#define	SDT_SYS286CGT	 4	/* system 286 call gate */
#define	SDT_SYSTASKGT	 5	/* system task gate */
#define	SDT_SYS286IGT	 6	/* system 286 interrupt gate */
#define	SDT_SYS286TGT	 7	/* system 286 trap gate */
#define	SDT_SYSNULL2	 8	/* system null again */
#define	SDT_SYS386TSS	 9	/* system 386 TSS available */
#define	SDT_SYSNULL3	10	/* system null again */
#define	SDT_SYS386BSY	11	/* system 386 TSS busy */
#define	SDT_SYS386CGT	12	/* system 386 call gate */
#define	SDT_SYSNULL4	13	/* system null again */
#define	SDT_SYS386IGT	14	/* system 386 interrupt gate */
#define	SDT_SYS386TGT	15	/* system 386 trap gate */

	/* memory segment types */
#define	SDT_MEMRO	16	/* memory read only */
#define	SDT_MEMROA	17	/* memory read only accessed */
#define	SDT_MEMRW	18	/* memory read write */
#define	SDT_MEMRWA	19	/* memory read write accessed */
#define	SDT_MEMROD	20	/* memory read only expand dwn limit */
#define	SDT_MEMRODA	21	/* memory read only expand dwn limit accessed */
#define	SDT_MEMRWD	22	/* memory read write expand dwn limit */
#define	SDT_MEMRWDA	23	/* memory read write expand dwn limit acessed */
#define	SDT_MEME	24	/* memory execute only */
#define	SDT_MEMEA	25	/* memory execute only accessed */
#define	SDT_MEMER	26	/* memory execute read */
#define	SDT_MEMERA	27	/* memory execute read accessed */
#define	SDT_MEMEC	28	/* memory execute only conforming */
#define	SDT_MEMEAC	29	/* memory execute only accessed conforming */
#define	SDT_MEMERC	30	/* memory execute read conforming */
#define	SDT_MEMERAC	31	/* memory execute read accessed conforming */

/* is memory segment descriptor pointer ? */
#define ISMEMSDP(s)	((s->d_type) >= SDT_MEMRO && (s->d_type) <= SDT_MEMERAC)

/* is 286 gate descriptor pointer ? */
#define IS286GDP(s)	(((s->d_type) >= SDT_SYS286CGT \
				 && (s->d_type) < SDT_SYS286TGT))

/* is 386 gate descriptor pointer ? */
#define IS386GDP(s)	(((s->d_type) >= SDT_SYS386CGT \
				&& (s->d_type) < SDT_SYS386TGT))

/* is gate descriptor pointer ? */
#define ISGDP(s)	(IS286GDP(s) || IS386GDP(s))

/* is segment descriptor pointer ? */
#define ISSDP(s)	(ISMEMSDP(s) || !ISGDP(s))

/* is system segment descriptor pointer ? */
#define ISSYSSDP(s)	(!ISMEMSDP(s) && !ISGDP(s))

/*
 * Software definitions are in this convenient format,
 * which are translated into inconvenient segment descriptors
 * when needed to be used by the 386 hardware
 */

struct	soft_segment_descriptor	{
	unsigned ssd_base ;		/* segment base address  */
	unsigned ssd_limit ;		/* segment extent */
	unsigned ssd_type:5 ;		/* segment type */
	unsigned ssd_dpl:2 ;		/* segment descriptor priority level */
	unsigned ssd_p:1 ;		/* segment descriptor present */
	unsigned ssd_xx:4 ;		/* unused */
	unsigned ssd_xx1:2 ;		/* unused */
	unsigned ssd_def32:1 ;		/* default 32 vs 16 bit size */
	unsigned ssd_gran:1 ;		/* limit granularity (byte/page units)*/
};

extern ssdtosd() ;	/* to decode a ssd */
extern sdtossd() ;	/* to encode a sd */

/*
 * region descriptors, used to load gdt/idt tables before segments yet exist
 */
struct region_descriptor {
	unsigned rd_limit:16 ;		/* segment extent */
	char *rd_base;			/* base address  */
};

I 3
/*
 * Segment Protection Exception code bits
 */

#define	SEGEX_EXT	0x01	/* recursive or externally induced */
#define	SEGEX_IDT	0x02	/* interrupt descriptor table */
#define	SEGEX_TI	0x04	/* local descriptor table */
				/* other bits are affected descriptor index */
#define SEGEX_IDX(s)	((s)>>3)&0x1fff)
E 3
E 1
