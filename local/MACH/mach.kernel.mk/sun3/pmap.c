/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pmap.c,v $
 * Revision 2.17  91/04/10  16:34:52  mbj
 * 	Added vm_ofset_t s,e declarations to parameter list so addresses
 * 	wont be considered ints.
 * 	[91/02/09            berman]
 * 
 * Revision 2.16  90/08/16  18:34:37  mrt
 * 	Picked up pmap_protect changes from pure kernel.
 * 	[90/08/16            mrt]
 * 
 * Revision 2.14.1.1  90/07/24  17:39:31  jjc
 * 	Changed pmap_init() to include the frame buffer in the
 * 	physical memory that we manage.
 * 	[90/07/24            jjc]
 * 
 * Revision 2.15  90/07/24  18:33:02  mrt
 * 	Changed pmap_init() to include the frame buffer in the
 * 	physical memory that we manage.
 * 	[90/07/24            jjc]
 * 
 * Revision 2.14  89/10/10  10:59:30  mwyoung
 * 	Correct pmap_protect() to never increase access rights.
 * 	[89/07/31            mwyoung]
 * 
 * Revision 2.13  89/09/06  16:10:27  jsb
 * 	BCS problems...
 * 	[89/09/06  16:08:59  jsb]
 * 
 * Revision 2.12  89/09/06  16:01:06  jsb
 * 	Added pmap_phys_to_frame definition.
 * 	[89/09/06  15:59:16  jsb]
 * 
 * Revision 2.9  89/04/23  13:23:13  gm0w
 * 	Fixed pmap_enter() not to panic if it is asked to map in
 * 	physical page 0 and added check for valid pme when checking
 * 	to see if mapping has been made already.  Fix from jjc.
 * 	[89/04/23            gm0w]
 * 
 * Revision 2.8  89/03/09  21:37:13  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  19:46:31  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.6  88/12/19  02:50:05  mwyoung
 * 	Remove lint.
 * 	[88/12/18            mwyoung]
 * 	
 * 	Added pmap_valid_page.
 * 	[88/12/13  03:35:17  mwyoung]
 * 	
 * 	Excised uses of PHYS_TO_VM_PAGE.
 * 	[88/12/09            mwyoung]
 * 	
 * 	Add pmap_verify_free().
 * 	[88/12/07  16:36:19  mwyoung]
 * 
 * Revision 2.5  88/11/21  16:58:03  rvb
 * 	Pme_zero will always allocate a pmeg if necessary, but only
 * 	"reserve" it if requested.
 * 	Also some what earlier we changed pme_to_epa to use 78 vs 7f8 to
 * 	mask just the high nibble vs the whole byte -- which was wrong.
 * 	[88/11/11            rvb]
 * 
 * 28-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	I forgot to do a Cache_Flush_Context before the segments are
 *	invalidates in unload.
 *
 *  3-Feb-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Created by dbg.   Finished and debugged by rvb:
 *	    1.	Added pmeg wired bit vector since there was no
 *		room in the pme.
 *	    2.	Definition of epa (extended physical page address)
 *	    3.	pmeg cache in pmap -- loaded/unloaded during activate
 *	    4.	context wiring has gone away because of 3.
 *	TODO:
 *	    a.	one context get/set around each routine
 *	    b.	have pv_list scanners use a dedicated seg va to
 *		map cached pmegs thru
 */

/*
 *	Rewrite sun3/pmap.c following vax protocols.
 */

#include <cpus.h>
#include <cputypes.h>

#include <sys/param.h>

#include <mach/boolean.h>
#include <kern/thread.h>
#include <kern/zalloc.h>

#include <kern/lock.h>
#include <kern/queue.h>

#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <mach/vm_param.h>
#include <mach/vm_prot.h>

#include <sun3/cpu.h>


#if	SUN3_260
#define SUN_VAC 1
#define Cache_Flush_Context(c)	if (vac) cache_flush_context(c)
#define Cache_Flush_Seg(c, v)	if (vac) cache_flush_seg(c, v)
#define Cache_Flush_Page(c, v)	if (vac) cache_flush_page(c, v)
#define Cache_Flush_Range(c, s, e, t)	\
		if (vac) { \
		    if (s == trunc_pmeg(s) && \
			e == trunc_pmeg(e)) { \
			cache_flush_seg(c, s); \
		    } \
		    else for (t = s; t < e; t += NBPG) { \
			cache_flush_page(c, t); \
		    } \
		}
#define Vac_Physflush(p, s) vac_physflush(p, s)
#else	SUN3_260
#define Cache_Flush_Context(c)
#define Cache_Flush_Seg(c, v)
#define Cache_Flush_Page(c, v)
#define Cache_Flush_Range(c, s, e, t)
#define Vac_Physflush(p, s)
#endif	SUN3_260

#define queue_detach(e)		queue_init(e)
#define queue_detached(e)	queue_empty(e)

/*
 *	For each managed physical page, there is a list of all currently
 *	valid virtual mappings of that page.  An entry is a pv_entry_t;
 *	pv_head_table is the array of list headers.
 */

typedef	struct pv_entry	{
	struct pv_entry	*next;		/* next pv_entry */
	pmap_t		pmap;		/* pmap where mapping lies */
	vm_offset_t	va;		/* virtual address for mapping */
} *pv_entry_t;
#define PV_ENTRY_NULL	((pv_entry_t)0)

pv_entry_t	pv_head_table;		/* array of entries, one per physical page */
zone_t		pv_list_zone;		/* zone for more pv_entries */
/*
 *	Index into pv_head_table and the phys_attribute table starting
 *	at vm_first_phys.
 *	N.B. you should make sure that the argument is really a pa and not an
 *	epa, before you use pa_index. (see below)
 */
#define pa_index(pa)	(atop(pa - vm_first_phys))
#define pai_to_pvh(pai)	(&pv_head_table[pai])

/*
 *	Physical page attributes for managed pages.  Use same bit offset as high
 *	order byte in pme.
 */
#define PHYS_MODIFIED	0x01		/* page modified */
#define PHYS_REFERENCED	0x02		/* page referenced */
#define PHYS_NOCACHE	0x10		/* page cannot be cached */
#define PHYS_NOMATCH	0x20		/* mappings don't match for va-cache */

char	*phys_attributes;		/* attribute list for mapped pages */

/*
 *	First and last physical addresses that we maintain any information
 *	for.  Initialized to zero so that pmap operations done before
 *	pmap_init won't touch any non-existent structures.
 */
vm_offset_t	vm_first_phys = (vm_offset_t) 0;
vm_offset_t	vm_last_phys  = (vm_offset_t) 0;
/*
 *	SUN's physical address space is 34 bits; the two extra are type bits.
 * 	BUT since sun does not even need 32 bits of physical address for each
 *	type, we will incorporate the 2 type bits into the top nibble.  We call
 *	these extended physical addresses, epa's.
 */

/*
 *	'x' must have EPA_NC off
 */
#define managed_epa(x)	( (!(x & EPA_TYPE)) && \
			  (x < vm_last_phys) && (x >= vm_first_phys))

/*
 *	epa returned will never have EPA_NC on.
 */
#define pme_to_epa(pme)	( (((pme & 0x7ffff) << PGSHIFT) & (~EPA_XTYPE)) | \
			  ((pme & 0x78000) ? EPA_F : 0) | \
			  ((pme & PG_TYPE) << 2) )
#define epa_equal(epa0, epa1) ((epa0&~EPA_F) == (epa1&~EPA_F))

/*
 *	EPA_NC will be propagated to PG_NC
 */
#define epa_to_pme(pa)	( pa & EPA_F ? \
			  ( ((pa | EPA_NBL)   >> PGSHIFT) & 0x7ffff) | ( (pa & EPA_XTYPE) >> 2) : \
			  ( ((pa &~EPA_XTYPE) >> PGSHIFT) & 0x7ffff) | ( (pa & EPA_XTYPE) >> 2))

#define inc_pme(pme) (pme+=1)

/*
 *	pmegs are allocated one at a time
 */
struct	pmeg {
	queue_chain_t	link;		/* link in active or free queues */
	pmap_t		pmap;		/* pmap this page is allocated to */
	vm_offset_t	va;		/* first virtual address mapped by
					   this page */
	short		use_count;	/* number of mappings in use */
	short		cache_idx;	/* index in pmap's pmeg cache */
	unsigned long	wired;		/* specific pages that are wired */
};

typedef	struct pmeg	*pmeg_t;
#define PMEG_NULL	((pmeg_t)0)
#define is_pmeg_wired(pmegp, v) (pmegp->wired & (1 << (( (v - pmegp->va) >> PGSHIFT) & 0xf)))

struct pmeg	pmeg_array[NPMEG];	/* one pmeg_t for each possible
					   mapping page */

queue_head_t	pmeg_active_queue;	/* list of all active pme pages */
queue_head_t	pmeg_free_queue;	/* list of all free pme pages */

int		pmeg_free_count;
int		pmeg_active_count;
int		pmeg_wired_count;
int		pmeg_max_wired;
int		pmeg_max_active;

#define seg_to_pmeg(seg)	(&pmeg_array[seg])
#define pmeg_to_seg(pmeg)	(pmeg - pmeg_array)

#define pmeg_map_size	(NBSG)
#define trunc_pmeg(v)	((v) & ~(pmeg_map_size - 1))
#define round_pmeg(v)	(trunc_pmeg((v) + pmeg_map_size - 1))

#if	0
/*
 *	Contexts are also allocated among the pmaps.
 * temporarily in pmap.h so genassym.c can define ctx->num.
 * someday this field will be in pmap also and used from there.
 */
struct	context {
	queue_chain_t	link;		/* link in active or free queues */
	pmap_t		pmap;		/* pmap this context is allocated to */
	int		num;		/* context number for hardware */
};
#endif	0
typedef	struct context	*context_t;
#define CONTEXT_NULL	((context_t)0)

struct context	context_array[NCONTEXT];/* one for each context */


queue_head_t	context_active_queue;	/* list of all active contexts */
queue_head_t	context_free_queue;	/* list of all free contexts */

int		context_free_count;
int		context_active_count;

/*
 *	Locking and TLB invalidation
 *
 *	We only support a one-processor SUN at the moment, but all
 *	of the macros are defined so they can be used in the right places.
 */
#if	NCPUS > 1
	OOPS...
#else	NCPUS > 1

lock_data_t	pmap_system_lock;

#define SPLVM(spl)	{ spl = splvm(); }
#define SPLX(spl)	{ splx(spl); }

#define PMAP_READ_LOCK(pmap, spl)	SPLVM(spl)
#define PMAP_WRITE_LOCK(spl)		SPLVM(spl)
#define PMAP_READ_UNLOCK(pmap, spl)	SPLX(spl)
#define PMAP_WRITE_UNLOCK(spl)		SPLX(spl)
#define PMAP_WRITE_TO_READ_LOCK(pmap)

#define LOCK_PVH(index)
#define UNLOCK_PVH(index)

#endif	NCPUS > 1

void	pmap_remove_range();	/* forward */
void	context_allocate();
void	context_free();

/*
 *	Kernel pmap
 */
struct pmap	kernel_pmap_store;	/* structure */
pmap_t		kernel_pmap;		/* pointer to it */

int	pmes_per_vm_page;		/* number of hardware pages per MACH VM page */
int	vac = 0;			/* SUN_VAC virtual address cache */

boolean_t	pmap_initialized = FALSE;/* Has pmap_init finished? */

	/* make sure we are not doing really bad things. use when hardware is going catatonic */
#define PARANOIA	0

	/* time consuming checks */
#define CHECK		0
#if	CHECK
#define Use_Check(x)	use_check(x)
#else	CHECK
#define Use_Check(x)
#endif	CHECK

	/* simple consistency checks */
#define SAFE		1
#if	SAFE
#else	SAFE
#endif	SAFE

	/* enable debugging printout on pmap_watch */
#define WATCH		1
#if	WATCH
int		pmap_watch = 0;
vm_offset_t	pmap_watch_va = (vm_offset_t) -1;
vm_offset_t	pmap_watch_epa = (vm_offset_t) -1;
#endif	WATCH

#define VM_FIRST_ADDRESS	0
#define VM_LAST_ADDRESS		KERNELBASE

/*
 *	Map memory at initialization.  The physical addresses being
 *	mapped are not managed and are never unmapped.
 *
 *	For now, VM is already on, we only need to map the
 *	specified memory.
 */
vm_offset_t pmap_map(virt, start, end, prot)
	register vm_offset_t	virt;
	register vm_offset_t	start;
	register vm_offset_t	end;
	register int		prot;
{
	register int		ps = PAGE_SIZE;

	while (start < end) {
		pmap_enter(kernel_pmap, virt, start, prot, FALSE);
		virt += ps;
		start += ps;
	}
	return(virt);
}

void	pmap_bootstrap()
{
	pmeg_t		pmegp;
	context_t	context;
	int		i;
	int		vxx = (NSEGMAP - 2) * NBSG;	/* scratch */
	vm_offset_t	v;

	pmes_per_vm_page = PAGE_SIZE / NBPG;

	lock_init(&pmap_system_lock, FALSE);

	kernel_pmap = &kernel_pmap_store;

	simple_lock_init(&kernel_pmap->lock);
	kernel_pmap->ref_count = 1;
		/* kernel gets the first context */
	kernel_pmap->context = &context_array[0];
	context_array[0].num = KCONTEXT;

	queue_init(&pmeg_free_queue);
	queue_init(&pmeg_active_queue);

		/* pmegp is now SEGINV which belongs to the kernel */
	pmeg_array[SEGINV].va = -1;		/* see pmeg_reserve */
	for (i = 0, pmegp = &pmeg_array[0]; i < NPMEG ; i++, pmegp++) {
	    if (pmegp->va) { /* belongs to kernel via pmeg_reserve */
		pmegp->pmap = PMAP_NULL;	/* permanent */
		pmegp->use_count = 2*NPAGSEG;	/* all mappings in use */
		pmeg_wired_count++;
		queue_detach( (queue_t) pmegp);
	    } else {
		setsgmap(vxx, i);
		for (v = vxx; v < vxx+NBSG; v += NBPG)
			setpgmap(v, 0);
		pmegp->va = 0;
		pmegp->cache_idx = 0;
		pmegp->use_count = 0;
		enqueue_tail(&pmeg_free_queue, (queue_entry_t) pmegp);
		pmeg_free_count++;
	    }
	}
	pmeg_max_wired = pmeg_wired_count;

	queue_init(&context_free_queue);
	queue_init(&context_active_queue);
	context = &context_array[0];
	for (i = 0; i < NCONTEXT; i++, context++) {
	    context->num = i;
	    if (i == KCONTEXT) {
		queue_detach( (queue_t) context);
		continue;
	    }
	    enqueue_tail(&context_free_queue, (queue_entry_t) context);
	}
	context_free_count = NCONTEXT - 1;
}

void	pmap_init(phys_start, phys_end)
	register vm_offset_t	phys_start, phys_end;
{
	int		npages;
	int		s;
	vm_offset_t	addr;
	extern
	vm_offset_t	vm_page_free_count;

	/*
	 *	Allocate and clear memory for the pv_head_table and the
	 *	phys_attribute list.
	 */
	npages = atop(mem_size);
	s = (vm_size_t)(sizeof(struct pv_entry) * npages
			+ npages);
	s = round_page(s);
	addr = (vm_offset_t) kmem_alloc(kernel_map, s);
	blkclr((caddr_t) addr, s);

	pv_head_table = (pv_entry_t)addr;
	phys_attributes = (char *) addr + (npages * sizeof(struct pv_entry));

	/*
	 *	The on board frame buffer memory may not be used, 
	 *	so include it with the physical memory that we manage.
	 */
	if (phys_start <= trunc_page(OBFBADDR))
		vm_first_phys = phys_start;
	else
		vm_first_phys = trunc_page(OBFBADDR);
		
	vm_last_phys = phys_end;

	/*
	 *	Create the zone of physical maps,
	 *	and of the physical-to-virtual entries.
	 */
	s = (vm_size_t) sizeof(struct pmap);
	pmap_zone = zinit(s, 400*s, 4096, FALSE, "pmap"); /* XXX */
	s = (vm_size_t) sizeof(struct pv_entry);
	pv_list_zone = zinit(s, 10000*s, 4096, FALSE, "pv_list"); /* XXX */

	printf("SPACE FREE:   ToTaL    = %x[%d]\n",
		atop(phys_end), atop(phys_end));
	printf("SPACE FREE: after load = %x[%d]\n",
		atop(phys_end - phys_start), atop(phys_end - phys_start));
	printf("SPACE FREE:  pmap_init = %x[%d]\n",
		vm_page_free_count, vm_page_free_count);

	pmap_initialized = TRUE;
}

boolean_t pmap_valid_page(phys_addr)
{
	/*
	 *	At the time this routine is used (in vm_page_startup,
	 *	before auto-configuration), "fbobmemavail" indicates
	 *	whether the frame buffer physical memory exists (and
	 *	is thus "available" for use by the device).  [Later,
	 *	it will indicate whether it is *still* available (and
	 *	thus does not belong to the device).]
	 *
	 *	If the screen memory isn't reserved, we can use any
	 *	page; else, we must avoid the screen memory range.
	 */

	return(
	       !fbobmemavail ||
		(
		 (phys_addr < trunc_page(OBFBADDR)) ||
		 (phys_addr >= round_page((OBFBADDR) + (FBSIZE)))
		)
	      );
		
}


/*
 *	Does a page table entry actually exist?
 */
#define pmeg_valid(pmap, va)	(getsegmap(pmap->context->num, va) != SEGINV)

pmeg_t	get_pmeg(pmap, va)
	pmap_t		pmap;
	vm_offset_t	va;
{
	int seg;
	seg = getsegmap(pmap->context->num, va);
	if (seg == SEGINV)
		return(PMEG_NULL);
	return (seg_to_pmeg(seg));
}

/*
 *	Reserve named pme group for kernel.
 */
void	pmeg_reserve(v)
	vm_offset_t v;
{
	int			seg = getsgmap(v);
	register pmeg_t		pmegp;

#if	SAFE
	if ((int) kernel_pmap)
		panic("pmeg_reserve: too late.");
	if (seg == SEGINV)
		panic ("can not reserve SEGINV");
#endif	SAFE
	pmegp = seg_to_pmeg(seg);

#if	SAFE
	if (pmegp->va != ((vm_offset_t) 0))
		panic("pmeg_reserve: already reserved");
#endif	SAFE
	pmegp->va = v;			/* implies reserved by kernel */
}

/*
 *	Allocate a pme page from the free list.
 */
pmeg_t	free_pmeg_alloc(pmap, va)
	pmap_t		pmap;
	vm_offset_t	va;
{
	pmeg_t		pmegp;
	int		i;

	if (queue_empty(&pmeg_free_queue)) {
	    return (PMEG_NULL);
	}

	pmegp = (pmeg_t) dequeue_head(&pmeg_free_queue);
	pmeg_free_count--;
#if	SAFE
	if (pmegp->pmap != PMAP_NULL || pmegp->va != (vm_offset_t)0){
	    printf("pmeg in use = %x[#%x], va = %x\n",
			pmegp, pmegp-pmeg_array, pmegp->va);
	    panic("free_pmegp_alloc");
	}
#endif	SAFE

	va = trunc_pmeg(va);

	pmegp->pmap = pmap;
	pmegp->va   = va;

	if (pmap == kernel_pmap) {
	    /*
	     *	Pme groups in kernel pmap are mapped into all
	     *	contexts, and are wired.
	     */
	    for (i = 0; i < NCONTEXT; i++)
		setsegmap(i, va, pmeg_to_seg(pmegp));
	    pmeg_wired_count++;
	    queue_detach( (queue_t) pmegp);
	}
	else {
	    register int idx = pmap->cache_idx++;

	    pmap->cache[idx] = (int) va | pmeg_to_seg(pmegp);
	    pmegp->cache_idx = idx;
	    setsegmap(pmap->context->num, va, pmeg_to_seg(pmegp));
	    enqueue_tail(&pmeg_active_queue, (queue_entry_t) pmegp);
	    pmeg_active_count++;
	    if (pmeg_active_count > pmeg_max_active)
		pmeg_max_active = pmeg_active_count;
	}

	return(pmegp);
}

/*
 *	Allocate a pme page, possibly recycling one from another pmap.
 */
pmeg_t	pmeg_alloc(pmap, va)
	pmap_t		pmap;
	vm_offset_t	va;
{
	pmeg_t	pmegp;

	if (queue_empty(&pmeg_free_queue)) {
	    pmap_t		old_pmap;
	    vm_offset_t		old_va;

	    /*
	     *	No free pme pages.  recycle one.
	     */
	    pmegp = (pmeg_t) queue_first(&pmeg_active_queue);
	    if (pmegp == PMEG_NULL) {
		panic("not enough pme pages");
	    }
	    /*
	     *	Free the pme page.
	     */
#if	SAFE
	    if (pmegp->pmap == PMAP_NULL)
		panic("pmeg_alloc: freeing permanent pmeg");
#endif	SAFE
	    old_pmap = pmegp->pmap;
	    old_va = pmegp->va;
	    if (old_pmap->context == CONTEXT_NULL)
		context_allocate(old_pmap);
	    simple_lock(&old_pmap->lock);
	    Cache_Flush_Seg(old_pmap->context->num, old_va);
	    pmap_remove_range(old_pmap,
	    		      old_va,
			      old_va + pmeg_map_size,
			      TRUE);
	    simple_unlock(&old_pmap->lock);

	    /*
	     *	Should put the pme page at the head of the free queue.
	     */
	}
	return (free_pmeg_alloc(pmap, va));
}

/*
 *	Free a pme page.
 */
void	pmeg_free(pmegp)
	pmeg_t		pmegp;
{
	int		i;

#if	SAFE
	if (pmegp->pmap == PMAP_NULL)
		panic("pmeg_free: freeing permanent pmeg");

	if (pmegp->wired) {
		printf("wired = %x, pmeg = %x[#%x]\n",
			pmegp->wired, pmegp, pmegp-pmeg_array);
		panic("pmeg_free");
	}
#endif	SAFE
#if	PARANOIA
		/* pmeg's freed should be empty */
	{
		vm_offset_t	v;
		int		pme;
		for (i = 0, v = pmegp->va; i < NPAGSEG; i++, v += NBPG) {
			if (pme = getpagemap(pmegp->pmap->context->num, v)) {
				printf("pme = %x, pmeg = %x[#%x], va = %x\n",
					pme, pmegp, pmegp-pmeg_array, v);
				panic("pmeg_free");
			}
		}
	}
#endif	PARANOIA
	if (pmegp->pmap == kernel_pmap) {
	    /*
	     *	Must remove kernel pme group from all contexts.
	     */
	    for (i = 0; i < NCONTEXT; i++)
		setsegmap(i, pmegp->va, SEGINV);
	    pmeg_wired_count--;
	}
	else {
	    pmap_t	pmap = pmegp->pmap;
	    register int idx = --(pmap->cache_idx);
	    register int pi = pmegp->cache_idx;

	    if (idx != pi) {
#define cache_to_seg(x) (x&0xff)
#define cache_to_va(x) ((vm_offset_t) (x&~0xff))
		pmap->cache[pi] = pmap->cache[idx];
		seg_to_pmeg(cache_to_seg(pmap->cache[idx]))->cache_idx = pi;
	    }
	    pmap->cache[idx] = 0;
	    pmegp->cache_idx = 0;

	    setsegmap(pmegp->pmap->context->num, pmegp->va, SEGINV);

#if	PARANOIA
	    if (queue_detached( (queue_t) pmegp)) {
		printf("freeing wired pmeg %x[#%x]\n",
			pmegp, pmegp-pmeg_array);
		panic("pmeg_free");
	    }
		/* pmeg's should be on the active q,
		   if they are to be removed from it */
	    if (pmeg_remq_ck(&pmeg_active_queue, "pmeg_active_queue", pmegp))
#endif	PARANOIA
	    remqueue(&pmeg_active_queue, (queue_entry_t) pmegp);
	    pmeg_active_count--;
	}

	pmegp->pmap = PMAP_NULL;
	pmegp->va = (vm_offset_t) 0;
	pmegp->use_count = 0;

#if	CHECK
	pmeg_enq_ck(&pmeg_free_queue, "pmeg_free_queue", pmegp);
#endif	CHECK
	enqueue_head(&pmeg_free_queue, (queue_entry_t) pmegp);
	pmeg_free_count++;
}

/*
 *	Wire down a pme page, preventing it from being recycled.
 */
void	pmeg_wire(pmegp, va)
	pmeg_t	pmegp;
{
	register int	page = ( (va - pmegp->va) >> PGSHIFT) & 0xf;

#if	SAFE
	if (pmegp->pmap == PMAP_NULL)
		panic("pmeg_wire: wiring permanent pmeg");
#endif	SAFE

	if (pmegp->pmap != kernel_pmap && !pmegp->wired) {
		remqueue(&pmeg_active_queue, (queue_entry_t) pmegp);
		queue_detach( (queue_t) pmegp);
		pmeg_active_count--;
		pmeg_wired_count++;
		if (pmeg_wired_count > pmeg_max_wired)
		    pmeg_max_wired = pmeg_wired_count;
	}

	if (!(pmegp->wired & (1 << page))) {
		pmegp->wired |= 1 << page;
	}
}

/*
 *	Unwire a pme page, allowing it to be recycled.
 */
void	pmeg_unwire(pmegp, va)
	pmeg_t	pmegp;
{
	register int	page = ( (va - pmegp->va) >> PGSHIFT) & 0xf;

#if	SAFE
	if (pmegp->pmap == PMAP_NULL)
		panic("pmeg_unwire: unwiring permanent pmeg");
#endif	SAFE
	if (pmegp->wired & (1 << page)) {
		pmegp->wired &= ~(1 << page);

		if (pmegp->pmap != kernel_pmap && !pmegp->wired) {
#if	SAFE
			if (!queue_detached( (queue_t) pmegp)) {
				printf("pmeg not wired %x[#%x]\n",
					pmegp, pmegp-pmeg_array);
				panic("pmeg_unwire");
			}
#endif	SAFE

			enqueue_tail(&pmeg_active_queue, (queue_entry_t) pmegp);
			pmeg_wired_count--;
			pmeg_active_count++;
		}
	} else {
		panic("pmeg_unwire: not wired");
	}
}

/*
 *	Allocate a context for the specified pmap.  May grab one from
 *	another pmap.
 */
void	context_allocate(pmap)
	pmap_t		pmap;
{
	context_t context;

	if (queue_empty(&context_free_queue)) {
	    /*
	     *	No free contexts - recycle one.
	     */

	    context = (context_t) queue_first(&context_active_queue);
	    if (context == CONTEXT_NULL)
		panic("no active contexts");
	    context_free(context->pmap);
	}

	context = (context_t)dequeue_head(&context_free_queue);
	context_free_count--;

#if	SAFE
	if (context->pmap != PMAP_NULL) {
	    panic("context in use");
	}
#endif	SAFE

	context->pmap = pmap;
	pmap->context = context;
	context_load(pmap);

	enqueue_tail(&context_active_queue, (queue_entry_t)context);
	context_active_count++;
}

/*
 *	Free a context in use by a pmap.
 */
void	context_free(pmap)
	pmap_t		pmap;
{
	context_t	context = pmap->context;

	if (context == CONTEXT_NULL)
	    return;
	if (context->num == getcontext()) {
	    printf("kernel_vm_space = %d\n", current_thread()->task->kernel_vm_space);
	    panic("context_free: freeing self");
	}
	context_unload(pmap);
	pmap->context = CONTEXT_NULL;
	context->pmap = PMAP_NULL;

	remqueue(&context_active_queue, (queue_entry_t) context);
	context_active_count--;
	enqueue_head(&context_free_queue, (queue_entry_t) context);
	context_free_count++;
}

context_load(pmap)
	pmap_t		pmap;
{
	register int 	idx = pmap->cache_idx;
	register int	i;
	register int	*cp = pmap->cache;
	register int	cnum = pmap->context->num;

	for (i = 0; i < idx; i++, cp++) {
		setsegmap(cnum, *cp, *cp);
	}
}


context_unload(pmap)
	pmap_t		pmap;
{
	register int 	idx = pmap->cache_idx;
	register int	i;
	register int	*cp = pmap->cache;
	register int	cnum = pmap->context->num;

	Cache_Flush_Context(cnum);
	for (i = 0; i < idx; i++, cp++) {
		setsegmap(cnum, *cp, SEGINV);
	}
}

cache_destroy(pmap)
	pmap_t		pmap;
{
	register int 	idx = pmap->cache_idx;
	register int	i;
	register int	*cp = pmap->cache;
	register vm_offset_t	v;

	for (i = 0; i < idx; i++, cp++) {
		v  = cache_to_va(*cp);
		pmap_remove_range(pmap, v, v + NBSG, TRUE);
	}
}

/*
 *	Create and return a physical map.
 *
 *	If the size specified for the map
 *	is zero, the map is an actual physical
 *	map, and may be referenced by the
 *	hardware.
 *
 *	If the size specified is non-zero,
 *	the map will be used in software only, and
 *	is bounded by that size.
 */
pmap_t	pmap_create(size)
	vm_size_t	size;
{
	register pmap_t		pmap;

	if (size != 0) {
	    return(PMAP_NULL);
	}

	pmap = (pmap_t) zalloc(pmap_zone);
	if (pmap == PMAP_NULL) {
	    panic("pmap_create");
	}

	simple_lock_init(&pmap->lock);
	pmap->context = CONTEXT_NULL;
	pmap->cache_idx = 0;
	pmap->ref_count = 1;

	pmap->stats.resident_count = 0;
	pmap->stats.wired_count = 0;

	return (pmap);
}

/*
 *	Retire the given physical map from service.
 *	Should only be called if the map contains
 *	no valid mappings.
 */
void	pmap_destroy(pmap)
	pmap_t	pmap;
{
	if (pmap != PMAP_NULL) {
	    register int s;

	    SPLVM(s);
	    simple_lock(&pmap->lock);
	    if (--pmap->ref_count > 0) {
		simple_unlock(&pmap->lock);
		SPLX(s);
		return;
	    }
	    SPLX(s);

	    if (pmap->cache_idx) {
		printf("pmap_destroy: cache_idx pmap %x #%x\n", pmap, pmap->context->num);
		if (pmap->context == CONTEXT_NULL) {
		    printf("pmap_destroy: no context but cached\n");
		    context_allocate(pmap);
		}
		simple_lock(pmap->lock);
		Cache_Flush_Context(pmap->context->num);
		cache_destroy(pmap);
		simple_unlock(pmap->lock);
	    }
	    if (pmap->context != CONTEXT_NULL) {
		context_free(pmap);
	    }

#if	SAFE
	    if (pmap->cache_idx)
		panic("pmap_destroy: cache_idx");
#endif	SAFE

	    zfree(pmap_zone, (vm_offset_t)pmap);
	}
}

/*
 *	Add a reference to the specified pmap.
 */
void	pmap_reference(pmap)
	pmap_t	pmap;
{
	if (pmap != PMAP_NULL) {
	    int	s;

	    SPLVM(s);
	    simple_lock(&pmap->lock);
	    pmap->ref_count++;
	    simple_unlock(&pmap->lock);
	    SPLX(s);
	}
}

/*
 *	Remove a range of mapping entries.
 *	The range must lie entirely within one pmeg (this is NOT checked).
 *
 *	The pmap must be locked, and have a context.
 */
void	pmap_remove_range(pmap, sva, eva, free_if_empty)
	pmap_t		pmap;
	vm_offset_t	sva, eva;
	boolean_t	free_if_empty;
{
	vm_offset_t	cva, lva;
	int		lpme, pme;
	vm_offset_t	epa;
	pv_entry_t	pv_h, cur, prev;
	int		pai, i;
	int		num_removed;
	pmeg_t		pmegp;

	if (pmap->context == CONTEXT_NULL)
		context_allocate(pmap);

	pmegp = get_pmeg(pmap, sva);
#if	WATCH
	if (pmap_watch) {
	    printf("pmap_RANGE(pmap %x, va %x, eva %x, free_if_mt %x) #%x\n",
		    pmap, sva, eva, free_if_empty, pmegp-pmeg_array);
	}
#endif	WATCH
	num_removed = 0;
	Use_Check(pmegp);

	for (cva = sva; cva < eva; cva += PAGE_SIZE) {
	    pme = getpagemap(pmap->context->num, cva);
	    if ((pme & PG_V) == 0)
		continue;

#if	WATCH
	    if (pmap_watch_va != (vm_offset_t) -1 && cva == pmap_watch_va) {
		printf("va match\n");
		asm("trap #0xf");
	    }
#endif	WATCH
	    num_removed++;
	    if (is_pmeg_wired(pmegp, cva)) {
	    	pmeg_unwire(pmegp, cva);
		pmap->stats.wired_count--;
	    }
	    epa = pme_to_epa(pme);
#if	WATCH
	    if (pmap_watch_epa != (vm_offset_t) -1 && epa == pmap_watch_epa) {
		pr_pvlist(epa);
		printf("epa of cva match\n");
		asm("trap #0xf");
	    }
#endif	WATCH
	    if (!managed_epa(epa)) {
		/*
		 *	Not managed memory.  Don`t remove from pv_list
		 *	or collect modify bits; just clear the pmes.
		 */
		i = pmes_per_vm_page;
		lva = cva;
		do {
		    setpagemap(pmap->context->num, lva, 0);
		    lva += NBPG;
		} while (--i > 0);
		continue;
	    }
		/* so below epa is managed */
	    pai = pa_index(epa);
	    LOCK_PVH(pai);

	    /*
	     *	Get the modify bits.
	     */
	    i = pmes_per_vm_page;
	    lva = cva;
	    do {
		lpme = changepagemap(pmap->context->num, lva, 0, 0);
		phys_attributes[pai] |= pme_mr(lpme);
		lva += NBPG;
	    } while (--i > 0);

	    /*
	     *	Remove mapping from the pvlist.
	     */
	    pv_h = pai_to_pvh(pai);
	    if (pv_h->pmap == PMAP_NULL) {
		panic("pmap_remove_range: null pv_list!");
	    }
	    if (pv_h->va == cva && pv_h->pmap == pmap) {
		cur = pv_h->next;
		if (cur != PV_ENTRY_NULL) {
		    *pv_h = *cur;
		    zfree(pv_list_zone, (vm_offset_t) cur);
		}
		else {
		    pv_h->pmap = PMAP_NULL;
		    phys_attributes[pai] &= ~(PHYS_NOCACHE | PHYS_NOMATCH);
		}
	    }
	    else {
		prev = pv_h;
		while ((cur = prev->next) != PV_ENTRY_NULL) {
		    if (cur->va == cva && cur->pmap == pmap)
			break;
		    prev = cur;
		}
		if (cur == PV_ENTRY_NULL) {
		    panic("pmap_remove_range: mapping not in pv_list!");
		}
		prev->next = cur->next;
		zfree(pv_list_zone, (vm_offset_t) cur);
	    }
	    UNLOCK_PVH(pai);
	}

	/*
	 *	Update the counts.
	 */
	pmap->stats.resident_count -= num_removed;

	/*
	 *	See whether this pme page can be freed.
	 */
	pmegp->use_count   -= num_removed;
	Use_Check(pmegp);
	if (pmegp->use_count == 0 && free_if_empty) {
	    pmeg_free(pmegp);
	}
}

/*
 *	Remove the given range of addresses from the
 *	specified map.
 *
 *	It is assume that the start and end are properly rounded
 *	to the machine's page size.
 */

void	pmap_remove(pmap, s, e)
	pmap_t	pmap;
	vm_offset_t s,e;
{
	int		spl;
	register vm_offset_t	l, c;

	if (pmap == PMAP_NULL)
	    return;

	if (pmap->context == CONTEXT_NULL)
	    context_allocate(pmap);

	PMAP_READ_LOCK(pmap, spl);

	if (pmap == kernel_pmap) {
	    if (s < VM_MIN_KERNEL_ADDRESS)
		s = VM_MIN_KERNEL_ADDRESS;
	    if (e > VM_MAX_KERNEL_ADDRESS)
		e = VM_MAX_KERNEL_ADDRESS;
	}
	else {
	    if (e > VM_MAX_ADDRESS)
		e = VM_MAX_ADDRESS;
	}

	while (s < e) {
	    l = round_pmeg(s + 1);
	    if (l > e)
		l = e;
	    if (pmeg_valid(pmap, s)) {
		Cache_Flush_Range(pmap->context->num, s, l, c);
		pmap_remove_range(pmap, s, l, TRUE);
	    }
	    s = l;
	}

	PMAP_READ_UNLOCK(pmap, spl);
}

/*
 *	Removes the specified physical page from all physical maps
 *	in which it resides.  Saves reference and modify bits.
 */
void	pmap_remove_all(epa)
	vm_offset_t	epa;
{
	pv_entry_t	pv_h, cur;
	int		pme;
	vm_offset_t	va, lva;
	pmap_t		pmap;
	register int	i;
	int		spl, pai;
	pmeg_t		pmegp;
#if	WATCH
	static int	last_vm;

#ifdef	lint
	if (last_vm++) return;
#endif	lint

	last_vm = -1;

	if (pmap_watch) {
		printf("pmap_ALL(epa %x)\n", epa);
	}
#endif	WATCH

	epa &= ~EPA_NC;
	if (!managed_epa(epa)) {
	    /*
	     *	Not a managed page.
	     */
	    return;
	}
#if	WATCH
	if (pmap_watch_epa != (vm_offset_t) -1 && epa == pmap_watch_epa) {
		pr_pvlist(epa);
		printf("epa match\n");
		asm("trap #0xf");
	}
#endif	WATCH
	/*
	 *	Lock the pmap system first, since we will be changing
	 *	several pmaps.
	 */

	PMAP_WRITE_LOCK(spl);

	/*
	 *	Walk down PV list, removing all mappings.
	 */
	pai = pa_index(epa);
	pv_h = pai_to_pvh(pai);

	while ((pmap = pv_h->pmap) != PMAP_NULL) {
	    va = pv_h->va;
#if	WATCH
	    last_vm = va;
	    if (pmap_watch_va != (vm_offset_t) -1 && va == pmap_watch_va) {
		printf("va of epa match\n");
		asm("trap #0xf");
	    }
#endif	WATCH
	    if (pmap->context == CONTEXT_NULL)
		context_allocate(pmap);

	    simple_lock(&pmap->lock);
	    pme = getpagemap(pmap->context->num, va);
#if	SAFE
	    if ((pme & PG_V) == 0) {
		panic("pmap_remove_all: pme in list but not in map");
	    }
	    if (! epa_equal(pme_to_epa(pme), epa)) {
		panic("pmap_remove_all: pme does not point to page");
	    }
#endif	SAFE
	    pmap->stats.resident_count--;
	    pmegp = get_pmeg(pmap, va);
	    Use_Check(pmegp);
	    if (is_pmeg_wired(pmegp, va)) {
		printf("pmap_remove_all: removing a wired page\n");
		continue;
	    }
	    if ((cur = pv_h->next) != PV_ENTRY_NULL) {
		*pv_h = *cur;
		zfree(pv_list_zone, (vm_offset_t) cur);
	    }
	    else {
		pv_h->pmap = PMAP_NULL;
	    }
	    i = pmes_per_vm_page;
	    lva = va;
#if	PARANOIA
		/* record va/epa/obj/data paged out */
	    if (va > KERNELBASE)
	    	ppg_out(va, epa);
#endif	PARANOIA
	    do {
		Cache_Flush_Page(pmap->context->num, lva);
		pme = changepagemap(pmap->context->num, lva, 0, 0);
		phys_attributes[pai] |= pme_mr(pme);
		lva += NBPG;
	    } while (--i > 0);
#if	PARANOIA
		/* record va/epa/obj/data paged out */
	    if (va > KERNELBASE)
	    	ppg_attr(va, epa);
#endif	PARANOIA

	    if (--pmegp->use_count == 0) {
		pmeg_free(pmegp);
	    }
	    Use_Check(pmegp);
	    simple_unlock(&pmap->lock);
	}

	phys_attributes[pai] &= ~(PHYS_NOCACHE | PHYS_NOMATCH);
	PMAP_WRITE_UNLOCK(spl);
}

pr_pvlist(epa)
	vm_offset_t	epa;
{
	pv_entry_t	pv_h;
	int		pme;
	vm_offset_t	va;
	pmap_t		pmap;
	int		spl, pai;
	pmeg_t		pmegp;

	printf("pr_pvlist(epa %x)\n", epa);

	epa &= ~EPA_NC;
	if (!managed_epa(epa)) {
	    /*
	     *	Not a managed page.
	     */
	    return;
	}

	/*
	 *	Lock the pmap system first, since we will be changing
	 *	several pmaps.
	 */

	PMAP_WRITE_LOCK(spl);

	/*
	 *	Walk down PV list, removing all mappings.
	 */
	pai = pa_index(epa);
	pv_h = pai_to_pvh(pai);

	while ((pmap = pv_h->pmap) != PMAP_NULL) {
	    va = pv_h->va;
	    printf("	pr_pvlist: va = %x epa = %x pmap = %x\n", va, epa, pmap);

	    if (pmap->context == CONTEXT_NULL)
		context_allocate(pmap);

	    simple_lock(&pmap->lock);
	    pme = getpagemap(pmap->context->num, va);
	    if ((pme & PG_V) == 0) {
		printf("pr_pvlist: pme in list but not in map\n");
	    }
	    if (! epa_equal(pme_to_epa(pme), epa)) {
		printf("pr_pvlist: pme does not point to page\n");
	    }
	    pmegp = get_pmeg(pmap, va);
	    if (is_pmeg_wired(pmegp, va)) {
		panic("pr_pvlist: removing a wired page");
	    }
	    pv_h = pv_h->next;
	    simple_unlock(&pmap->lock);
	    if (!pv_h)
	    	break;
	}
	PMAP_WRITE_UNLOCK(spl);
}

boolean_t pmap_verify_free(phys)
	vm_offset_t	phys;
{
	pv_entry_t	pv_h;
	int		pai;
	int		spl;
	boolean_t	result;

	if (!pmap_initialized)
		return(TRUE);

	phys &= ~EPA_NC;
	if (!managed_epa(phys))
	    return(FALSE);

	PMAP_WRITE_LOCK(spl);

	pai = pa_index(phys);
	pv_h = pai_to_pvh(pai);

	result = (pv_h->pmap == PMAP_NULL);
	PMAP_WRITE_UNLOCK(spl);

	return(result);
}


/*
 *	Removes write privileges from all physical maps for the
 *	specified physical page.
 */
void	pmap_copy_on_write(epa)
	vm_offset_t	epa;
{
	pv_entry_t	pv_e;
	pmap_t		pmap;
	vm_offset_t	va;
	int		pme, i, spl;

	epa &= ~EPA_NC;
	if (!managed_epa(epa)) {
	    return;
	}

	/*
	 *	Lock the entire pmap system, since we may be changing
	 *	several maps.
	 */
	PMAP_WRITE_LOCK(spl);

	pv_e = pai_to_pvh(pa_index(epa));
	if (pv_e->pmap == PMAP_NULL) {
	    PMAP_WRITE_UNLOCK(spl);
	    return;
	}

	while (pv_e != PV_ENTRY_NULL) {
	    pmap = pv_e->pmap;
	    va = pv_e->va;
	    if (pmap->context == CONTEXT_NULL)
		context_allocate(pmap);

	    simple_lock(&pmap->lock);

	    i = pmes_per_vm_page;
	    do {
		/*
		 *	Turn off write permission for each mapping.
		 *	We only have to flush the cache if the mapping
		 *	is writeable.
		 */
		pme = getpagemap(pmap->context->num, va);
		if (pme & PG_W) {
		    Cache_Flush_Page(pmap->context->num, va);
		    setpagemap(pmap->context->num, va, pme & ~PG_W);
		}
		va += NBPG;
	    } while (--i > 0);

	    simple_unlock(&pmap->lock);
	    pv_e = pv_e->next;
	}
}

/*
 *	Limit the access rights to the specified range of this pmap as requested.
 */
void	pmap_protect(pmap, s, e, prot)
	pmap_t	pmap;
	vm_offset_t	s, e;
	vm_prot_t	prot;
{
	register int		new_prot;
	register vm_offset_t	l, c;
	register int		pme;
	int			spl;
	int			cnum;

	if (pmap == PMAP_NULL)
	    return;

	if ((prot & VM_PROT_READ) == 0) {
	    pmap_remove(pmap, s, e);
	    return;
	}

	if (prot & VM_PROT_WRITE)
		return;

	if (pmap->context == CONTEXT_NULL)
	    context_allocate(pmap);

	cnum = pmap->context->num;

	new_prot = sun_protection(pmap, prot);

	SPLVM(spl);
	simple_lock(&pmap->lock);

	if (pmap == kernel_pmap) {
	    if (s < VM_MIN_KERNEL_ADDRESS)
		s = VM_MIN_KERNEL_ADDRESS;
	    if (e > VM_MAX_KERNEL_ADDRESS)
		e = VM_MAX_KERNEL_ADDRESS;
	}
	else {
	    if (e > VM_MAX_ADDRESS)
		e = VM_MAX_ADDRESS;
	}


	while (s < e) {
	    l = round_pmeg(s + 1);
	    if (l > e)
		l = e;
	    if (pmeg_valid(pmap, s)) {
		Cache_Flush_Range(cnum, s, l, c);
		for (c = s; c < l; c += NBPG) {
		    pme = changepagemap(cnum, c, ~PG_PROT, new_prot);
		    if ( ! (pme & PG_V))
		    	setpagemap(cnum, c, 0);
		}
	    }
	s = l;
	}

	simple_unlock(&pmap->lock);
	SPLX(spl);
}

/*
 *	Insert the given physical page (p) at
 *	the specified virtual address (v) in the
 *	target physical map with the protection requested.
 *
 *	If specified, the page will be wired down, meaning
 *	that the related pme can not be reclaimed.
 *
 *	NB:  This is the only routine which MAY NOT lazy-evaluate
 *	or lose information.  That is, this routine must actually
 *	insert this page into the given map NOW.
 */
void	pmap_enter(pmap, va, epa, prot, wired)
	pmap_t		pmap;
	vm_offset_t	va;
	vm_offset_t	epa;
	vm_prot_t	prot;
	boolean_t	wired;
{
	int		new_prot;
	pv_entry_t	pv_e, pv_h;
	pmeg_t		pmegp;
	int		pme, newpme;
	vm_offset_t	old_epa;
	int		i;
	vm_offset_t	lva;
	int		spl;
	int		pai;

	if (pmap == PMAP_NULL) {
	    return;
	}

	/*
	 *	Set up the template for the new page table entry.
	 *		EPA_NC gets propagated to PG_NC.
	 */
	new_prot = sun_protection(pmap, prot);
	newpme = PG_V | new_prot | epa_to_pme(epa);
	epa &= ~EPA_NC;

	/*
	 *	Must allocate a new pvlist entry while we're unlocked;
	 *	zalloc may cause pageout (which will lock the pmap system).
	 *	If we determine we need a pvlist entry, we will unlock
	 *	and allocate one.  Then we will retry, throwing away
	 *	the allocated entry later (if we no longer need it).
	 */
	pv_e = PV_ENTRY_NULL;

Retry:
	PMAP_READ_LOCK(pmap, spl);

	/*
	 *	Get a context.
	 */
	while (pmap->context == CONTEXT_NULL) {
	    PMAP_READ_UNLOCK(pmap, spl);
	    context_allocate(pmap);
	    PMAP_READ_LOCK(pmap, spl);
	}

	/*
	 *	Get a pme page for this mapping.
	 */
	if (!pmeg_valid(pmap, va)) {
	    /*
	    *	First try to get a free page-table page.
	    */
	    pmegp = free_pmeg_alloc(pmap, va);
	    if (pmegp == PMEG_NULL) {
		/*
		 *	No free pme pages.  Must get the write lock on
		 *	the pmap system to grab one away from another
		 *	pmap.
		 */
		PMAP_READ_UNLOCK(pmap, spl);
		PMAP_WRITE_LOCK(spl);
		/*
		 *	Should check for our context going away here...
		 */
		if (pmap->context == CONTEXT_NULL) {
		    /* lost it */
		    PMAP_WRITE_UNLOCK(spl);
		    goto Retry;
		}
		pmegp = pmeg_alloc(pmap, va);
		PMAP_WRITE_TO_READ_LOCK(pmap);
	    }
	} else
	    pmegp = get_pmeg(pmap, va);
#if	WATCH
	if (pmap_watch) {
	    printf("pmap_enter(pmap %x, va %x, epa %x, prot %x, wired %x) #%x\n",
		    pmap, va, epa, prot, wired, pmegp-pmeg_array);
	}
	if (pmap_watch_va != (vm_offset_t) -1 && va == pmap_watch_va) {
		printf("va match\n");
		asm("trap #0xf");
	}
	if (pmap_watch_epa != (vm_offset_t) -1 && epa == pmap_watch_epa) {
		pr_pvlist(epa);
		printf("epa match\n");
		asm("trap #0xf");
	}
#endif	WATCH

	Use_Check(pmegp);
	pme = getpagemap(pmap->context->num, va);
	old_epa = pme_to_epa(pme);
	if ((pme & PG_V) && epa_equal(old_epa, epa)) {
	    /*
	     *	Special case if the physical page is already mapped
	     *	at this address.  May be changing its wired attribute
	     *	or protection.
	     */
	    if (wired && ! is_pmeg_wired(pmegp, va)) {
		pmap->stats.wired_count++;
		pmeg_wire(pmegp, va);
	    }
	    else if (!wired && is_pmeg_wired(pmegp, va)) {
		pmap->stats.wired_count--;
		pmeg_unwire(pmegp, va);
	    }

	    i = pmes_per_vm_page;
	    lva = va;
	    do {
		Cache_Flush_Page(pmap->context->num, lva);
		changepagemap(pmap->context->num, lva, PG_M|PG_R, newpme);
		lva += NBPG;
		inc_pme(newpme);
	    } while (--i > 0);
	}
	else {
	    /*
	     *	Remove old mapping from the PV list if necessary.
	     */
	    if (! epa_equal(old_epa, 0)) {
#if	SUN_VAC
		if (vac) {
		    i = pmes_per_vm_page;
		    lva = va;
		    do {
			Cache_Flush_Page(pmap->context->num, lva);
			lva += NBPG;
		    } while (--i > 0);
		}
#endif	SUN_VAC
		pmap_remove_range(pmap, va, va + PAGE_SIZE, FALSE);
	    }
	    if (managed_epa(epa)) {

		pai = pa_index(epa);
		LOCK_PVH(pai);
		pv_h = pai_to_pvh(pai);

		if (pv_h->pmap == PMAP_NULL) {
		    /*
		     *	No mappings yet - put at head.
		     */
		    pv_h->va = va;
		    pv_h->pmap = pmap;
		    pv_h->next = PV_ENTRY_NULL;
		    if (newpme & PG_NC)
			phys_attributes[pai] |= PHYS_NOCACHE;
		}
		else {
		    if (pv_e == PV_ENTRY_NULL) {
			/*
			 *	Must unlock the map to allocate from a zone.
			 */
			UNLOCK_PVH(pai);
			PMAP_READ_UNLOCK(pmap, spl);
			pv_e = (pv_entry_t) zalloc(pv_list_zone);
			goto Retry;
		    }
		    /*
		     *	Insert new entry after header, then check whether
		     *	we can still cache the mappings.
		     */
		    pv_e->va = va;
		    pv_e->pmap = pmap;
		    pv_e->next = pv_h->next;
		    pv_h->next = pv_e;

		    if (phys_attributes[pai] & (PHYS_NOMATCH | PHYS_NOCACHE)) {
			newpme |= PG_NC;
		    }
		    else if (newpme & PG_NC) {
			phys_attributes[pai] |= PHYS_NOCACHE;
			pv_uncache(pv_h);
		    }
		    else if ((va & 0x1FFFF) != (pv_h->va & 0x1FFFF)){
			newpme |= PG_NC;
			phys_attributes[pai] |= PHYS_NOMATCH;
			pv_uncache(pv_h);
		    }
			
		    /*
		     *	We used the pvlist entry - don't deallocate it.
		     */
		    pv_e = PV_ENTRY_NULL;
		}
		UNLOCK_PVH(pai);
	    }

	    /*
	     *	And count the mapping.
	     */
	    pmap->stats.resident_count++;
	    pmegp->use_count++;
	    if (wired) {
		pmap->stats.wired_count++;
		pmeg_wire(pmegp, va);
	    }
	    
	    i = pmes_per_vm_page;
	    lva = va;
	    do {
		setpagemap(pmap->context->num, lva, newpme);
		lva += NBPG;
		inc_pme(newpme);
	    } while (--i > 0);
	}
#if	PARANOIA
		/* check va/epa/obj/data paged back in */
	if (va > KERNELBASE)
		ppg_in(va, epa);
#endif	PARANOIA

	Use_Check(pmegp);
	PMAP_READ_UNLOCK(pmap, spl);

	if (pv_e != PV_ENTRY_NULL) {
	    zfree(pv_list_zone, (vm_offset_t) pv_e);
	}
}

/*
 *	Routine:	pmap_change_wiring
 *	Function:	Change the wiring attribute for a map/virtual-address
 *			pair.
 *	In/out conditions:
 *			The mapping must already exist in the pmap.
 */
void	pmap_change_wiring(pmap, va, wired)
	register pmap_t	pmap;
	vm_offset_t	va;
	boolean_t	wired;
{
	long			pme;
	pmeg_t			pmegp;
	vm_offset_t		lva;
	int			i;
	int			spl;

	if (pmap == PMAP_NULL)
	    return;

	if (pmap->context == CONTEXT_NULL)
	    context_allocate(pmap);

	/*
	 *	Must grab the pmap system lock because we may change
	 *	a pmeg queue.
	 */
	PMAP_READ_LOCK(map, spl);

#if	SAFE
	if (!pmeg_valid(pmap, va))
	    panic("pmap_change_wiring: pme invalid");
#endif	SAFE
	pmegp = get_pmeg(pmap, va);

	pme = getpagemap(pmap->context->num, va);
	if (wired && ! is_pmeg_wired(pmegp, va)) {
	    /*
	     *	Wiring down mapping
	     */
	    pmap->stats.wired_count++;
	    pmeg_wire(pmegp, va);
	}
	else if (!wired && is_pmeg_wired(pmegp, va)) {
	    /*
	     *	Unwiring mapping.
	     */
	    pmap->stats.wired_count--;
	    pmeg_unwire(pmegp, va);
	}

	i = pmes_per_vm_page;
	lva = va;
	do {
	    pme = getpagemap(pmap->context->num, lva);
	    if ((pme & PG_V) == 0)
		panic("pmap_change_wiring");
	    /* the wire bit is not kept in the pme */
	    lva += NBPG;
	} while (--i > 0);

	PMAP_READ_UNLOCK(pmap, spl);
}

/*
 *	Routine:	pmap_extract
 *	Function:
 *		Extract the physical page address associated
 *		with the given map/virtual_address pair.
 */

vm_offset_t pmap_extract(pmap, va)
	register pmap_t	pmap;
	vm_offset_t	va;
{
	long			pme;
	vm_offset_t		epa;
	int			spl;

	if (pmap == PMAP_NULL){
		printf("pmap_extract: null pmap\n");
		return(0);
	}
	if (pmap->context == CONTEXT_NULL)
	    context_allocate(pmap);

	SPLVM(spl);
	simple_lock(&pmap->lock);

	pme = getpagemap(pmap->context->num, va);

	if ((pme & PG_V) == 0)
	    epa = (vm_offset_t) 0;
	else {
	    epa = (vm_offset_t) pme_to_epa(pme);
	    epa |= va & (NBPG-1);	/* offset within page */
	}
	simple_unlock(&pmap->lock);
	SPLX(spl);

	return (epa);
}

/*
 *	Routine:	pmap_access
 *	Function:
 *		Returns whether there is a valid mapping for the
 *		given virtual address stored in the given physical map.
 */

boolean_t pmap_access(pmap, va)
	pmap_t		pmap;
	vm_offset_t	va;
{
	long			pme;
	boolean_t		ok;
	int			spl;

	if (pmap == PMAP_NULL){
		printf("pmap_access: null pmap\n");
		return(FALSE);
	}
	if (pmap->context == CONTEXT_NULL)
	    context_allocate(pmap);

	SPLVM(spl);
	simple_lock(&pmap->lock);

	pme = getpagemap(pmap->context->num, va);

	if ((pme & PG_V) == 0)
		ok = FALSE;
	else
		ok = TRUE;

	simple_unlock(&pmap->lock);
	SPLX(spl);
	return (ok);
}

/*
 *	Copy the range specified by src_addr/len
 *	from the source map to the range dst_addr/len
 *	in the destination map.
 *
 *	This routine is only advisory and need not do anything.
 */
void pmap_copy(dst_pmap, src_pmap, dst_addr, len, src_addr)
	pmap_t		dst_pmap;
	pmap_t		src_pmap;
	vm_offset_t	dst_addr;
	vm_size_t	len;
	vm_offset_t	src_addr;
{
#ifdef	lint
	dst_pmap++; src_pmap++; dst_addr++; len++; src_addr++;
#endif	lint
}

/*
 *	Require that all active physical maps contain no
 *	incorrect entries NOW.  [This update includes
 *	forcing updates of any address map caching.]
 *
 *	Generally used to insure that a thread about
 *	to run will see a semantically correct world.
 */
void pmap_update()
{
	/* Flush TLB */
	/* Sun 3 doesn't have a TLB */
}

/*
 *	Routine:	pmap_collect
 *	Function:
 *		Garbage collects the physical map system for
 *		pages which are no longer used.
 *		Success need not be guaranteed -- that is, there
 *		may well be pages which are not referenced, but
 *		others may be collected.
 *	Usage:
 *		Called by the pageout daemon when pages are scarce.
 */
void pmap_collect()
{
}

/*
 *	Routine:	pmap_activate
 *	Function:
 *		Binds the given physical map to the given
 *		processor, and returns a hardware map description.
 */
void pmap_activate(pmap, th, cpu)
	register pmap_t	pmap;
	thread_t	th;
	int		cpu;
{
	PMAP_ACTIVATE(pmap, th, cpu);
}

/*
 *	Routine:	pmap_deactivate
 *	Function:
 *		Indicates that the given physical map is no longer
 *		in use on the specified processor.  (This is a macro
 *		in pmap.h)
 */
void pmap_deactivate(pmap, th, what_cpu)
	pmap_t		pmap;
	thread_t	th;
	int		what_cpu;
{
#ifdef	lint
	th++; what_cpu++;
#endif	lint
#if	NCPUS > 1
	; YOU LOSE ;
#endif	NCPUS > 1
	PMAP_DEACTIVATE(pmap, th, what_cpu);
}

/*
 *	Routine:	pmap_kernel
 *	Function:
 *		Returns the physical map handle for the kernel.
 */
pmap_t pmap_kernel()
{
    	return (kernel_pmap);
}


/*
 *	Given a map and a machine independent protection code,
 *	convert to a sun protection code.
 */
int sun_protection(pmap, prot)
	pmap_t		pmap;
	vm_prot_t	prot;
{
	register int	p;

	p = (pmap == kernel_pmap) ? PG_S : 0;
	if (prot & VM_PROT_WRITE)
	    p |= PG_W;
	return(p);
}

/*
 *	Clear the modify bits on the specified physical page.
 *
 *	XXX this does not yet work if the physical page is in
 *	    any maps
 */

void pmap_clear_modify(epa)
	register vm_offset_t	epa;
{
	epa &= ~EPA_NC;
	if (managed_epa(epa))
	    update_phys_attributes(epa, 0, PHYS_MODIFIED);
}

/*
 *	pmap_is_modified:
 *
 *	Return whether or not the specified physical page is modified
 *	by any physical maps.
 *
 *	XXX this does not yet return complete information if the page
 *	    is in any pmaps - pmap_remove_all should have just
 *	    been called
 *	    
 */

boolean_t pmap_is_modified(epa)
	register vm_offset_t	epa;
{
	epa &= ~EPA_NC;
	if (managed_epa(epa))
	    return update_phys_attributes(epa, PHYS_MODIFIED, 0);
	else
	    return (FALSE);
}

/*
 *	pmap_clear_reference:
 *
 *	Clear the reference bit on the specified physical page.
 *
 *	XXX this does not yet work if the physical page is in
 *	    any maps
 */

void pmap_clear_reference(epa)
	vm_offset_t	epa;
{
	epa &= ~EPA_NC;
	if (managed_epa(epa))
	    update_phys_attributes(epa, 0, PHYS_REFERENCED);
}

/*
 *	pmap_is_referenced:
 *
 *	Return whether or not the specified physical page is referenced
 *	by any physical maps.
 *
 *	XXX this does not yet return complete information if the page
 *	    is in any pmaps - pmap_remove_all should have just
 *	    been called
 */

boolean_t pmap_is_referenced(epa)
	vm_offset_t	epa;
{
	epa &= ~EPA_NC;
	if (managed_epa(epa)) {
	    return update_phys_attributes(epa, PHYS_REFERENCED, 0);
	} else
	    return (FALSE);
}

update_phys_attributes(pa, check, clr)
	vm_offset_t	pa;
{
	pv_entry_t	pv_h;
	int		pme;
	vm_offset_t	va;
	pmap_t		pmap;
	register int	i;
	int		pai;
	int		change = -1;		/* i.e. don't change pme */

	change &= ~ ( ((clr&PHYS_MODIFIED) ? PG_M : 0) | ((clr&PHYS_REFERENCED) ? PG_R : 0) );

	/*
	 *	Walk down PV list, let pmap_remove_all do all the hairy
	 *	consistency checks
	 */
	pai = pa_index(pa);
	pv_h = pai_to_pvh(pai);

	if (!clr)
		if ((phys_attributes[pai] & check) == check)
			return 1;
	while ((pmap = pv_h->pmap) != PMAP_NULL) {
	    va = pv_h->va;
	    if (pmap->context == CONTEXT_NULL)
		context_allocate(pmap);

	    simple_lock(&pmap->lock);

	    i = pmes_per_vm_page;
	    do {
		Cache_Flush_Page(pmap->context->num, va);
		pme = changepagemap(pmap->context->num, va, change, 0);
		phys_attributes[pai] |= pme_mr(pme);
		if (!clr)
			if ((phys_attributes[pai] & check) == check) {
				simple_unlock(&pmap->lock);
				return 1;
			}

		va += NBPG;
	    } while (--i > 0);

	    simple_unlock(&pmap->lock);

	    if ((pv_h = pv_h->next) == PV_ENTRY_NULL) {
	    	break;
	    }

	}
	phys_attributes[pai] &= ~ clr;
	return ((phys_attributes[pai] & check) == check);
}

/*
 *	Routine:	pmap_pageable
 *	Function:
 *		Make the specified pages (by pmap, offset)
 *		pageable (or not) as requested.
 *
 *		A page which is not pageable may not take
 *		a fault; therefore, its page table entry
 *		must remain valid for the duration.
 *
 *		This routine is merely advisory; pmap_enter
 *		will specify that these pages are to be wired
 *		down (or not) as appropriate.
 *
 */
void pmap_pageable(pmap, start, end, pageable)
	pmap_t		pmap;
	vm_offset_t	start;
	vm_offset_t	end;
	boolean_t	pageable;
{
#ifdef	lint
	pmap++; start++; end++; pageable++;
#endif	lint
}

/*
 *	Make each virtual page in the pv list not cacheable from the given
 *	pv_entry to the end of the list
 */
pv_uncache(pv_e)
	pv_entry_t	pv_e;
{
	register pv_entry_t	cur;
	register pmap_t		pmap;
	register vm_offset_t	va;
	int			i;

	for (cur = pv_e; cur != PV_ENTRY_NULL && cur->pmap != PMAP_NULL;
			cur = cur->next){
	    pmap = cur->pmap;
	    va = cur->va;
	    if (pmap->context == CONTEXT_NULL)
		context_allocate(pmap);
	    i = pmes_per_vm_page;
	    do {
		Cache_Flush_Page(pmap->context->num, va);
		changepagemap(pmap->context->num, va, -1, PG_NC);
	    } while (--i > 0);
	}
}

/*
 *	Routines to manipulate memory via physical addresses.
 */

/*
 *	pmap_zero_page zeros the specified (machine independent)
 *	page by mapping the page into virtual memory and using
 *	bzero to clear its contents, one machine dependent page
 *	at a time.
 */
pmap_zero_page(epa)
	register vm_offset_t	epa;
{
	register vm_offset_t	va;
	register int		i, pme;

	Vac_Physflush(epa, PAGE_SIZE);
	va = (vm_offset_t)(phys_map_vaddr1 + (cpu_number() * NBPG));
	i = pmes_per_vm_page;
	/*
	 *	No need to fill up the cache with a page full
	 *	of zeros.
	 */
	pme = epa_to_pme(epa) | PG_V | PG_KW | PG_NC;
	do {
	    setpgmap(va, pme);
	    bzero(va, NBPG);
	    inc_pme(pme);
	    va += NBPG;
	} while (--i > 0);
}

/*
 *	pmap_copy_page copies the specified (machine independent)
 *	page by mapping the page into virtual memory and using
 *	bcopy to copy the page, one machine dependent page at a
 *	time.
 */
pmap_copy_page(src, dst)
	vm_offset_t	src, dst;
{
	register int		dstpme, srcpme, i;
	register vm_offset_t	dstva, srcva;

	Vac_Physflush(src, PAGE_SIZE);
	srcpme = epa_to_pme(src) | PG_V | PG_KR | PG_NC;
	srcva = (vm_offset_t)(phys_map_vaddr1 + (cpu_number() * NBPG));
	Vac_Physflush(dst, PAGE_SIZE);
	dstpme = epa_to_pme(dst) | PG_V | PG_KW | PG_NC;
	dstva = (vm_offset_t)(phys_map_vaddr2 + (cpu_number() * NBPG));

	i = pmes_per_vm_page;
	do {
	    setpgmap(srcva, srcpme);
	    setpgmap(dstva, dstpme);
	    bcopy(srcva, dstva, NBPG);
	    inc_pme(srcpme);
	    inc_pme(dstpme);
	    srcva += NBPG;
	    dstva += NBPG;
	} while (--i > 0);
}


/*
 *	copy_to_phys
 *
 *	Copy virtual memory to physical memory by mapping the physical
 *	memory into virtual memory and then doing a virtual to virtual
 *	copy with bcopy.
 *	NB: assumes that both source and destination are aligned
 *	on page boundaries.
 */
copy_to_phys(srcva, dstpa, bytecount)
	register vm_offset_t	srcva;
	register vm_offset_t	dstpa;
	register int		bytecount;
{
	register vm_offset_t	dstva;
	register int		copy_size, offset;

	Vac_Physflush(dstpa, bytecount);
	dstva = (vm_offset_t)(phys_map_vaddr1 + (cpu_number() * NBPG));
	copy_size = NBPG;
	offset = dstpa - sun_trunc_page(dstpa);
	dstpa -= offset;

	while (bytecount > 0){
	    copy_size = NBPG - offset;
	    if (copy_size > bytecount)
		copy_size = bytecount;
	    setpgmap(dstva, epa_to_pme(dstpa) | PG_V | PG_KW);
	    dstva += offset;
	    bcopy(srcva, dstva, copy_size);
	    Cache_Flush_Page(KCONTEXT, dstva);
	    srcva += copy_size;
	    dstpa += NBPG;
	    bytecount -= copy_size;
	    offset = 0;
	}
}

/*
 *	copy_from_phys
 *
 *	Copy physical memory to virtual memory by mapping the physical
 *	memory into virtual memory and then doing a virtual to virtual
 *	copy with bcopy.
 *	NB: assumes that both source and destination are aligned
 *	on page boundaries.
 */
copy_from_phys(srcpa, dstva, bytecount)
	register vm_offset_t	srcpa;
	register vm_offset_t	dstva;
	register int		bytecount;
{
	register vm_offset_t	srcva;
	register int		copy_size, offset;

	Vac_Physflush(srcpa, bytecount);
	srcva = (vm_offset_t)(phys_map_vaddr1 + (cpu_number() * NBPG));
	copy_size = NBPG;
	offset = srcpa - sun_trunc_page(srcpa);
	srcpa -= offset;
	while (bytecount > 0){
		copy_size = NBPG - offset;
		setpgmap(srcva, epa_to_pme(srcpa) | PG_V | PG_KR);
		srcva += offset;
		if (copy_size > bytecount)
			copy_size = bytecount;
		bcopy(srcva, dstva, copy_size);
		Cache_Flush_Page(KCONTEXT, (caddr_t)srcva);
		dstva += copy_size;
		srcpa += NBPG;
		bytecount -= copy_size;
		offset = 0;
	}
}

/*
 *	pmap_page_protect:
 *
 *	Lower the permission for all mappings to a given page.
 */
void	pmap_page_protect(epa, prot)
	vm_offset_t	epa;
	vm_prot_t	prot;
{
	switch (prot) {
		case VM_PROT_READ:
		case VM_PROT_READ|VM_PROT_EXECUTE:
			pmap_copy_on_write(epa);
			break;
		case VM_PROT_ALL:
			break;
		default:
			pmap_remove_all(epa);
			break;
	}
}

vm_offset_t	pmap_phys_address(x)
	int		x;
{
	
	return (pme_to_epa(x) | EPA_NC);
}

int	pmap_phys_to_frame(phys)
	vm_offset_t	phys;
{
	return epa_to_pme(phys);
}

/*
 *	getmemc
 *	Get 1 byte from physical memory.
 */
unsigned char getmemc(epa)
	vm_offset_t	epa;
{
	unsigned char	byte;
	caddr_t		va;

	Vac_Physflush(epa, PAGE_SIZE);	/* Ouch! */
	va = (caddr_t)(phys_map_vaddr1 + (cpu_number() * NBPG));
	setpgmap(va, epa_to_pme(epa) | PG_V | PG_KR | PG_NC);
	byte = *(unsigned char *)(va + (epa & (NBPG - 1)));
	return(byte);
}

/*
 *	putmemc
 *	Put 1 byte into physical memory.
 */
void putmemc(epa, byte)
	vm_offset_t	epa;
	unsigned char	byte;
{
	caddr_t		va;

	Vac_Physflush(epa, PAGE_SIZE);	/* Ouch! */
	va = (caddr_t)(phys_map_vaddr1 + (cpu_number() * NBPG));
	setpgmap(va, epa_to_pme(epa) | PG_V | PG_KW | PG_NC);
	va += epa & (NBPG - 1);
	*(unsigned char *)va = byte;
}

#if	SUN_VAC
/*
 *	Flush specified number of bytes (rounded up to a page) from virtual
 *	address cache starting at given physical address
 */
vac_physflush(epa, bytecount)
	register vm_offset_t	epa;
	register int		bytecount;
{
	register pv_entry_t	pv_h;
	long			pme;
	register vm_offset_t	va;
	register pmap_t		pmap;
	int 			pai;
	int			i;

	epa &= ~EPA_NC;
	if (!vac || !managed_epa(epa))
		return;

	epa = trunc_page(epa);
	while (bytecount > 0){
	    /*
	     *	Run down the PV list, flushing all of the virtual pages
	     *	that map to this physical page
	     */
	    pai = pa_index(epa);
	    LOCK_PVH(pai);
	    for (pv_h = pai_to_pvh(pai); pv_h != PV_ENTRY_NULL
		     && pv_h->pmap != PMAP_NULL; pv_h = pv_h->next) {
		pmap = pv_h->pmap;
		va = pv_h->va;
		if (pmap->context == CONTEXT_NULL)
		    context_allocate(pmap);
		i = pmes_per_vm_page;
		do {
		    pme = getpagemap(pmap->context->num, va);
		    if ((pme & PG_V) == 0)
			panic("vac_physflush: pme in list but not in map");
		    Cache_Flush_Page(pmap->context->num, va);
		} while (--i > 0);
	    }
	    UNLOCK_PVH(pai);
	    bytecount -= PAGE_SIZE;
	    epa += PAGE_SIZE;
	}
}
#endif	SUN_VAC

pmap_map_page(vaddr, pfn, size)
	vm_offset_t		vaddr;
	vm_offset_t		pfn;
	u_int			size;
{
	vm_offset_t		epa = pme_to_epa(pfn) | EPA_NC;
	
	pmap_map(vaddr, epa, epa + size, VM_PROT_READ|VM_PROT_WRITE);
}

/*
 *	Set the protection on the specified range of this pmap as requested.
 *	Like pmap_protect, but kernel only, use sun protections and deal with
 *	PG_NC nocache
 */
void	pme_protect(s, e, prot)
	vm_offset_t	s, e;
	int		prot;
{
	register vm_offset_t	l, c;
	u_int		pme;

	while (s < e) {
	    l = round_pmeg(s + 1);
	    if (l > e)
		l = e;
	    if (pmeg_valid(kernel_pmap, s)) {
		Cache_Flush_Range(KCONTEXT, s, l, c);
		for (c = s; c < l; c += NBPG) {
		    pme = changepgmap(c, ~(PG_PROT|PG_NC), prot);
		    if ( ! (pme & PG_V))
		    	setpgmap(c, 0);
		}
	    }
	s = l;
	}
}

/*
 *	Set the pme on the specified range of this map to zero.
 *	And create pmeg if requested and SEGINV
 */
void	pme_zero(s, e, reserved)
	vm_offset_t	s, e;
{
	register vm_offset_t	l, c;
	register pmeg_t		pmegp;


	while (s < e) {
	    l = round_pmeg(s + 1);
	    if (l > e)
		l = e;
	    if (pmegp=get_pmeg(kernel_pmap, s)) {
		Cache_Flush_Range(KCONTEXT, s, l, c);
	    } else if ((pmegp=pmeg_alloc(kernel_pmap, s)) == PMEG_NULL) {
			panic("pme_zero: no pmegs");
	    } else if (reserved) {
		    pmegp->pmap = PMAP_NULL;	/* can't recycle pmeg */
		    pmegp->use_count = 4*NPAGSEG;
	    }

	    for (c = s; c < l; c += NBPG)
		setpgmap(c, 0);
	    s = l;
	}
}


/*
 *	To save rewriting/modifying old sun code, define:
 */

getkpgmap(va)
	vm_offset_t va;
{
	if (va <  VM_MIN_KERNEL_ADDRESS ||
	    va >= VM_MAX_KERNEL_ADDRESS)
		panic("getkpgmap");
	return (getpgmap(va));
}

vac_pageflush(va)
	vm_offset_t va;
{
	Cache_Flush_Page(CURRENTCONTEXT, va);
}

#if	CHECK
use_check(pmegp)
	pmeg_t		pmegp;
{
	vm_offset_t	v;
	int		pme;
	int		count = 0;
	int		i;

	if (pmegp->pmap == PMAP_NULL)
		return;
	if (pmegp->pmap->context == CONTEXT_NULL)
		context_allocate(pmegp->pmap);
	for (i = 0, v = pmegp->va; i < NPAGSEG; i++, v += NBPG) {
		pme = getpagemap(pmegp->pmap->context->num, v);
		if (pme & PG_V)
			count++;
	}

	if (pmegp->use_count != count) {
		printf("v = %x, pmeg %x[#%x] use_count = %x, pme_count = %x\n",
			pmegp->va, pmegp, pmegp - pmeg_array, pmegp->use_count, count);
		break_here();
	}
}

break_here()
{
}

print_context_queue(q, name)
	queue_entry_t		q;
	char *			name;
{
	queue_entry_t		e;
	int			cnt = NCONTEXT;

	if (queue_empty(q))
		printf("QUEUE: %s EMTPY\n", name);
	else {
		printf("QUEUE: %s ", name);
		e = queue_first(q);
		while ( (! queue_end(q, e)) && cnt--) {
			printf("%x ", ((context_t)e)->num);
		       e = queue_next(e);
		}
		printf("\n");
	}
}

context_enq_ck(q, name, context)
	queue_entry_t		q;
	char *			name;
	context_t		context;
{
	queue_entry_t		e;
	int			cnt = NCONTEXT;

	if (queue_empty(q))
		printf("QUEUE SCAN: %s EMTPY\n", name);
	else {
		e = queue_first(q);
		while ( (! queue_end(q, e)) && cnt--) {
			if ( ((context_t)q) == context ) {
				printf("%s: entry %x[%x] exists.\n",
					name, context, context-context_array);
				print_context_queue(q, name);
				asm("trap #0xf");
			}
		       e = queue_next(e);
		}
		if (cnt <= 0) {
			printf("QUEUE SCAN: %s Knotted\n", name);
			print_context_queue(q, name);
			asm("trap #0xf");
		}
	}
}

print_pmeg_queue(q, name)
	queue_entry_t		q;
	char *			name;
{
	queue_entry_t		e;
	int			cnt = NPMEG;

	if (queue_empty(q))
		printf("QUEUE SCAN: %s EMTPY\n", name);
	else {
		printf("QUEUE SCAN: %s ", name);
		e = queue_first(q);
		while ( (! queue_end(q, e)) && cnt--) {
			printf("%x ", pmeg_to_seg(((pmeg_t)e)));
		       e = queue_next(e);
		}
		printf("\n");
	}
}

pmeg_enq_ck(q, name, pmegp)
	queue_entry_t		q;
	char *			name;
	pmeg_t			pmegp;
{
	queue_entry_t		e;
	int			cnt = NPMEG;

	if (queue_empty(q))
		printf("QUEUE SCAN: %s EMTPY\n", name);
	else {
		e = queue_first(q);
		while ( (! queue_end(q, e)) && cnt--) {
			if ( ((pmeg_t)e) == pmegp ) {
				printf("%s: entry %x[%x] exists.\n",
					name, pmegp, pmegp-pmeg_array);
				print_pmeg_queue(q, name);
				asm("trap #0xf");
			}
		       e = queue_next(e);
		}
		if (cnt <= 0) {
			printf("QUEUE SCAN: %s Knotted\n", name);
			print_pmeg_queue(q, name);
			asm("trap #0xf");
		}
	}
}

pmeg_remq_ck(q, name, pmegp)
	queue_entry_t		q;
	char *			name;
	pmeg_t			pmegp;
{
	queue_entry_t		e;
	int			cnt = NPMEG;

	if (queue_empty(q))
		printf("QUEUE SCAN: %s EMTPY\n", name);
	else {
		e = queue_first(q);
		while ( (! queue_end(q, e)) && cnt--) {
			if ( ((pmeg_t)e) == pmegp ) {
				return 1;
			}
		       e = queue_next(e);
		}
		if (cnt <= 0) {
			printf("QUEUE SCAN: %s Knotted\n", name);
			print_pmeg_queue(q, name);
			asm("trap #0xf");
		}
		printf("%s: entry %x[%x] missing.\n",
			name, pmegp, pmegp-pmeg_array);
		print_pmeg_queue(q, name);
		print_pmeg_queue(&pmeg_free_queue, "pmeg_free_queue");
		asm("trap #0xf");
	}
	return 0;
}
#endif	CHECK

#if	PARANOIA
#include <vm/vm_page.h>
#include <vm/vm_object.h>
static ppg_cksum(), ppg_all0();
static int ppg_save_index = 0;

int ppg_index = 0;
int ppg_on = 0;

struct ppg_stat
       {
	vm_offset_t	va;
	vm_offset_t	pa;
	int		cksum;
	int		attr;
	int		pme;
       } 		ppg_stat[101];

ppg_out(va, pa)
{
	register int			i;
	register struct ppg_stat	*ppgp;

	if (!current_thread() || !vm_page_array || !ppg_on)
		return;

	for (i = 0; i < ppg_index; i++) {
		if (ppg_stat[i].va == va)
			ppg_save_index = i;
			break;
	}
	ppgp = &ppg_stat[i];
	ppgp->va = va;
	ppgp->pa = pa;
	ppgp->cksum = ppg_cksum((int *)va);
	ppgp->pme = getpagemap(-1, va);

}

ppg_attr(va, epa)
{
	register int	i = ppg_save_index;

	if (!current_thread() || !vm_page_array || !ppg_on)
		return;

	if (va != ppg_stat[i].va) {
		printf("ppg_stat = %x\n", &ppg_stat[i]);
		panic("ppg_attr");
	}

	ppg_stat[i].attr = phys_attributes[pa_index(epa)];

	if (ppg_index < 100)
		ppg_index++;
}

ppg_in(va, pa)
{
	register int			i;
	register int			sum;
	register struct ppg_stat	*ppgp;

	if (!current_thread() || !vm_page_array || !ppg_on || !ppg_index)
		return;

	sum = ppg_cksum((int*)va);

	for (i = 0; i < ppg_index; i++)
		if (ppg_stat[i].va == va && ppg_stat[i].cksum != sum) {
			ppgp = &ppg_stat[i];
			printf("ppg_in %x: va %x, opa %x, pa %x, owd %x wd %x\n",
				&ppg_stat[i], va, ppgp->pa, pa, ppgp->cksum, sum);
			printf("ppg_in: zero = %x\n", ppg_all0((int*)va));
			printf("attributes = %x, pme = %x\n",
				ppgp->attr, ppgp->pme);
			asm("trap #0xf");
			return;
		}
}

static ppg_cksum(vp)
	register int	*vp;
{
	register int	i;
	register int	sum;

	for (i = 0, sum = 0; i < 2048; i++)
		sum += *vp++;
	return sum;
}

static ppg_all0(vp)
	register int	*vp;
{
	register int	i;

	for (i = 0; i < 2048; i++)
		if (*vp++)
			return 0;
	return 1;
}
#endif	PARANOIA
