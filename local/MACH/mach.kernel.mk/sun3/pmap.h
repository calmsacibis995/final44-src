/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pmap.h,v $
 * Revision 2.9  90/03/09  00:34:30  af
 * 	Added null pmap_attribute() macro.
 * 
 * 
 * Revision 2.8  89/10/11  22:27:55  dlb
 * 	Put maco, zalloc and lock stuff under #ifdef KERNEL conditionals
 * 	so that this will compile outside the kernel where it is used by
 * 	adb.
 * 	[89/10/11            mrt]
 * 
 * Revision 2.7  89/10/11  14:50:16  dlb
 * 	Add PMAP_CONTEXT macro - does nothing.
 * 	[89/10/07            dlb]
 * 
 * Revision 2.6  89/03/09  21:37:27  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  19:46:45  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.4  89/01/15  16:33:19  rpd
 * 	Updated includes to the new style.
 * 	Updated macros to the new style.
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:13:52  rpd]
 * 
 *  3-Feb-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Revised for dbg's new pmap.c
 *
 * 19-Jun-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Created for Sun 3.
 *
 */

#ifndef	SUN3_PMAP_H_
#define SUN3_PMAP_H_	1

#ifndef	ASSEMBLER

#ifdef	KERNEL
#include <kern/zalloc.h>
#include <kern/lock.h>
#endif	KERNEL
#include <sun3/mmu.h>
#include <mach/sun3/vm_param.h>
#include <mach/vm_statistics.h>

/*
 * Sun 3 hardware page table entry
 */

struct pme {
	unsigned int	valid:1;	/* valid bit */
	unsigned int	prot:2;		/* access protection */
	unsigned int	nocache:1;	/* no cache bit */
	unsigned int	type:2;		/* page type */
	unsigned int	ref:1;		/* referenced */
	unsigned int	modify:1;	/* modified */
	unsigned int	:4;
	unsigned int	wired:1;	/* wired down */
	unsigned int	pfn:19;		/* page frame number */
};

typedef struct pme	pme_t;		/* Mach page table entry */

#endif	ASSEMBLER

#define PG_V		0x80000000	/* page is valid */
#define PG_PROT		0x60000000	/* access protection mask */
#define PG_W		0x40000000	/* write enable bit */
#define PG_S		0x20000000	/* system page */
#define PG_NC		0x10000000	/* no cache bit */
#define PG_TYPE		0x0C000000	/* page type mask */
#define PG_R		0x02000000	/* page referenced bit */
#define PG_M		0x01000000	/* page modified bit */
#define PG_MR		0x03000000	/* mask above two bits */
#define PG_PFNUM	0x0C07FFFF	/* page # mask */

#define PG_KW		(PG_S|PG_W)
#define PG_KR		PG_S
#define PG_UW		PG_W		/* kernel can still access */
#define PG_UWKW		PG_UW
#define PG_UR		0		/* kernel can still access */
#define PG_URKR		PG_UR
#define PG_UPAGE	PG_KW		/* sun3 u pages not user accessable */

#define PGT_MASK	(3<<26)

#define PGT_OBMEM	(0<<26)		/* onboard memory */
#define PGT_OBIO	(1<<26)		/* onboard I/O */
#define PGT_VME_D16	(2<<26)		/* VMEbus 16-bit data */
#define PGT_VME_D32	(3<<26)		/* VMEbus 32-bit data */

#define EPA_OBMEM	0x00000000	/* onboard memory */
#define EPA_OBIO	0x10000000	/* onboard I/O */
#define EPA_VME_D16	0x20000000	/* VMEbus 16-bit data */
#define EPA_VME_D32	0x30000000	/* VMEbus 32-bit data */
#define EPA_NC		0x40000000	/* no cache bit */
#define EPA_XTYPE	0x70000000	/* cache and mem type */
#define EPA_TYPE	0x30000000	/* mem type */
#define EPA_F		0x80000000	/* Nibble is really 0xf */
#define EPA_NBL		0xf0000000	/* top nibble mask */

#define PAGE_OBMEM	0		/* pme->type is main memory */

#define pme_mr(x)	( ( x & PG_MR) >> 24)

#ifndef	ASSEMBLER
#ifdef	KERNEL
#include <kern/macro_help.h>

/*
 * Pmap stuff
 */
struct pmap {
	struct context		*context;	/* ptr. to current context */
	int			ref_count;	/* reference count */
	simple_lock_data_t	lock;		/* lock on map */
	struct pmap_statistics	stats;		/* map statistics */
						/* NOTE: we depend on
						   stats->wired_count being
						   accurate to lock/unlock
						   contexts! */
	int		cache_idx;		/* next available slot */
	int		cache[NPMEG];		/* remember pmeg's given to
						   this pmap */
};

typedef struct pmap	*pmap_t;
#define PMAP_NULL	((pmap_t) 0)

extern pmap_t	kernel_pmap;

zone_t		pmap_zone;		/* zone for more pv_entries */

extern vm_offset_t	phys_map_vaddr1,
			phys_map_vaddr2;

extern queue_head_t	context_active_queue;
extern int		context_active_count;

/*
 *	Macros for speed
 */
#define PMAP_ACTIVATE(pmap, th, cpu)					\
MACRO_BEGIN								\
	if ((pmap) != kernel_pmap) {					\
		if ((pmap)->context == 0)				\
			context_allocate(pmap);				\
		remqueue(&context_active_queue,				\
			 (queue_entry_t) (pmap)->context);		\
		context_active_count--;					\
	}								\
MACRO_END

#define PMAP_DEACTIVATE(pmap, th, cpu)					\
MACRO_BEGIN								\
	if ((pmap) != kernel_pmap) {					\
		enqueue_tail(&context_active_queue,			\
			     (queue_entry_t) (pmap)->context);		\
		context_active_count++;					\
	}								\
MACRO_END


#define PMAP_CONTEXT(pmap,th)

struct	context {
	queue_chain_t	link;		/* link in active or free queues */
	pmap_t		pmap;		/* pmap this context is allocated to */
	int		num;		/* context number for hardware */
};

#define pmap_resident_count(pmap)	((pmap)->stats.resident_count)
#define pmap_attribute(pmap,addr,siz,attr,val)	0

/*
 *	Initialize (head of) pv list
 */

#endif	KERNEL
#endif	ASSEMBLER
#endif	SUN3_PMAP_H_
