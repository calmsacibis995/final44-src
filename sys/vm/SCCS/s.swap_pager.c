h48556
s 00002/00004/00981
d D 8.9 94/03/21 16:37:50 hibler 42 41
c lint
e
s 00001/00004/00984
d D 8.8 94/01/13 10:09:37 hibler 41 40
c get rid of lingering swap_pager_finish reference
e
s 00003/00001/00985
d D 8.7 94/01/13 09:21:28 bostic 40 39
c lint
e
s 00289/00186/00697
d D 8.6 94/01/12 15:51:05 hibler 39 38
c massive changes to use multi-page interface, cleanup.
e
s 00035/00034/00848
d D 8.5 93/12/30 16:01:13 mckusick 38 37
c convert to use new queue structures
e
s 00022/00031/00860
d D 8.4 93/11/14 14:00:15 hibler 37 36
c in io, check right off if page exists in object 
c makes shadow-chain traversal faster
e
s 00004/00002/00887
d D 8.3 93/11/10 10:58:26 torek 36 35
c finish up new device pager: all pagers get offsets
e
s 00001/00001/00888
d D 8.2 93/09/21 07:43:16 bostic 35 34
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00887
d D 8.1 93/06/11 16:37:11 bostic 34 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00889
d D 7.18 93/04/17 18:53:55 torek 33 32
c from pseudo-device to option
e
s 00006/00001/00887
d D 7.17 92/11/29 10:20:06 hibler 32 31
c only force wakeup of pageout daemon if we are short on memory
e
s 00000/00001/00888
d D 7.16 92/10/07 00:07:33 mckusick 31 30
c do not need to include <vm/queue.h> as it comes in from <vm/vm.h>
e
s 00007/00007/00882
d D 7.15 92/10/02 00:20:46 mckusick 30 29
c av_forw/av_back are gone; now use b_actf/b_actb for linking active buffers
e
s 00005/00005/00884
d D 7.14 92/10/01 17:54:21 mckusick 29 28
c convert vm_page bit fields to flags
e
s 00002/00002/00887
d D 7.13 92/09/21 21:44:12 hibler 28 27
c return VM_PAGER_ERROR not VM_PAGER_FAIL on IO errors
e
s 00002/00001/00887
d D 7.12 92/07/12 16:19:52 pendry 27 26
c new include location for specdev.h
e
s 00002/00002/00886
d D 7.11 92/07/08 22:38:38 torek 26 25
c return more likely values, not just random junk
e
s 00000/00001/00888
d D 7.10 92/07/03 00:49:33 mckusick 25 24
c delete USES
e
s 00001/00000/00888
d D 7.9 92/05/14 17:24:05 heideman 24 16
c vnode interface conversion
e
s 00001/00000/00888
d R 7.9 92/05/14 16:57:49 heideman 23 16
c vnode interface conversion
e
s 00001/00000/00888
d R 7.9 92/05/14 16:40:25 heideman 22 16
c vnode interface conversion
e
s 00001/00000/00888
d R 7.9 92/05/14 16:30:20 heideman 21 16
c vnode interface conversion
e
s 00001/00000/00888
d R 7.9 92/05/14 15:46:41 heideman 20 16
c vnode interface conversion
e
s 00001/00000/00888
d R 7.9 92/05/14 15:36:28 heideman 19 16
c vnode interface conversion
e
s 00001/00000/00888
d R 7.9 92/05/14 14:42:34 heideman 18 16
c vnode interface conversion
e
s 00001/00000/00888
d R 7.9 92/05/14 12:44:44 heideman 17 16
c vnode interface conversion
e
s 00001/00001/00887
d D 7.8 92/05/14 12:41:26 heideman 16 7
c vnode.h/specdev.h swapped to avoid prototype warnings
e
s 00001/00000/00888
d R 7.8 92/05/14 11:41:44 heideman 15 7
c vnode interface conversion
e
s 00001/00000/00888
d R 7.8 92/05/14 10:22:45 heideman 14 7
c vnode interface conversion
e
s 00001/00000/00888
d R 7.8 92/05/13 23:00:31 heideman 13 7
c vnode interface conversion
e
s 00001/00000/00888
d R 7.8 92/05/13 18:49:17 heideman 12 7
c vnode interface conversion
e
s 00001/00000/00888
d R 7.8 92/05/13 18:20:59 heideman 11 7
c vnode interface conversion
e
s 00001/00000/00888
d R 7.8 92/05/13 18:10:41 heideman 10 7
c vnode interface conversion
e
s 00001/00000/00888
d R 7.8 92/05/13 17:55:19 heideman 9 7
c vnode interface conversion
e
s 00001/00000/00888
d R 7.8 92/05/13 17:53:54 heideman 8 7
c vnode interface conversion
e
s 00051/00023/00837
d D 7.7 92/05/04 17:15:58 bostic 7 6
c add function prototypes; new include format; define pagerops here; lint
e
s 00004/00001/00856
d D 7.6 92/04/20 14:51:24 mckusick 6 5
c set dirty offset (from Macklem)
e
s 00001/00005/00856
d D 7.5 91/07/25 23:00:27 mckusick 5 4
c replace numerous includes with vm.h
e
s 00055/00069/00806
d D 7.4 91/05/07 09:32:46 hibler 4 3
c move a lot of synchronizing code over to DEBUG since we now
c keep the page frame busy while it is being processed by the pager
e
s 00019/00019/00856
d D 7.3 91/04/20 10:50:04 karels 3 2
c fix includes; new proc struct; rm *_NULL
e
s 00002/00001/00873
d D 7.2 91/03/04 21:57:42 mckusick 2 1
c update for diskless support
e
s 00874/00000/00000
d D 7.1 90/12/05 18:13:25 mckusick 1 0
c adopted from Mike Hibler at Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 University of Utah.
D 34
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 34
I 34
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 34
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
I 4
 * from: Utah $Hdr: swap_pager.c 1.4 91/04/30$
 *
E 4
 *	%W% (Berkeley) %G%
 */

/*
 * Quick hack to page to dedicated partition(s).
 * TODO:
 *	Add multiprocessor locks
 *	Deal with async writes in a better fashion
 */

D 33
#include "swappager.h"
#if NSWAPPAGER > 0

E 33
D 7
#include "param.h"
D 3
#include "user.h"
E 3
#include "proc.h"
#include "buf.h"
#include "map.h"
#include "systm.h"
#include "specdev.h"
#include "vnode.h"
#include "malloc.h"
#include "queue.h"
E 7
I 7
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/map.h>
D 16
#include <sys/specdev.h>
E 16
#include <sys/vnode.h>
I 16
D 27
#include <sys/specdev.h>
E 27
E 16
#include <sys/malloc.h>
I 27

#include <miscfs/specfs/specdev.h>
E 27
E 7

D 3
#include "../vm/vm_param.h"
#include "../vm/vm_pager.h"
#include "../vm/vm_page.h"
#include "../vm/vm_pageout.h"
#include "../vm/swap_pager.h"
E 3
I 3
D 5
#include "vm_param.h"
#include "queue.h"
#include "lock.h"
#include "vm_prot.h"
#include "vm_object.h"
E 5
I 5
D 7
#include "vm.h"
E 5
#include "vm_page.h"
#include "vm_pageout.h"
#include "swap_pager.h"
E 7
I 7
#include <vm/vm.h>
D 31
#include <vm/queue.h>
E 31
#include <vm/vm_page.h>
#include <vm/vm_pageout.h>
#include <vm/swap_pager.h>
E 7
E 3

#define NSWSIZES	16	/* size of swtab */
D 39
#define NPENDINGIO	64	/* max # of pending cleans */
E 39
#define MAXDADDRS	64	/* max # of disk addrs for fixed allocations */
I 39
#ifndef NPENDINGIO
#define NPENDINGIO	64	/* max # of pending cleans */
#endif
E 39

#ifdef DEBUG
int	swpagerdebug = 0x100;
#define	SDB_FOLLOW	0x001
#define SDB_INIT	0x002
#define SDB_ALLOC	0x004
#define SDB_IO		0x008
#define SDB_WRITE	0x010
#define SDB_FAIL	0x020
#define SDB_ALLOCBLK	0x040
#define SDB_FULL	0x080
#define SDB_ANOM	0x100
#define SDB_ANOMPANIC	0x200
I 39
#define SDB_CLUSTER	0x400
#define SDB_PARANOIA	0x800
E 39
#endif

I 38
TAILQ_HEAD(swpclean, swpagerclean);

E 38
struct swpagerclean {
D 38
	queue_head_t		spc_list;
	int			spc_flags;
	struct buf		*spc_bp;
	sw_pager_t		spc_swp;
	vm_offset_t		spc_kva;
	vm_page_t		spc_m;
E 38
I 38
	TAILQ_ENTRY(swpagerclean)	spc_list;
	int				spc_flags;
	struct buf			*spc_bp;
	sw_pager_t			spc_swp;
	vm_offset_t			spc_kva;
	vm_page_t			spc_m;
I 39
	int				spc_npages;
E 39
E 38
} swcleanlist[NPENDINGIO];
D 7
typedef	struct swpagerclean	*swp_clean_t;
E 7
I 7
typedef struct swpagerclean *swp_clean_t;
E 7

I 7
D 39

E 39
E 7
D 3
#define SWP_CLEAN_NULL		((swp_clean_t)0)

E 3
/* spc_flags values */
#define SPC_FREE	0x00
#define SPC_BUSY	0x01
#define SPC_DONE	0x02
#define SPC_ERROR	0x04
D 39
#define SPC_DIRTY	0x08
E 39

struct swtab {
	vm_size_t st_osize;	/* size of object (bytes) */
	int	  st_bsize;	/* vs. size of swap block (DEV_BSIZE units) */
#ifdef DEBUG
	u_long	  st_inuse;	/* number in this range in use */
	u_long	  st_usecnt;	/* total used of this size */
#endif
} swtab[NSWSIZES+1];

#ifdef DEBUG
D 39
int		swap_pager_pendingio;	/* max pending async "clean" ops */
E 39
int		swap_pager_poip;	/* pageouts in progress */
int		swap_pager_piip;	/* pageins in progress */
#endif

I 39
int		swap_pager_maxcluster;	/* maximum cluster size */
int		swap_pager_npendingio;	/* number of pager clean structs */

E 39
D 38
queue_head_t	swap_pager_inuse;	/* list of pending page cleans */
queue_head_t	swap_pager_free;	/* list of free pager clean structs */
queue_head_t	swap_pager_list;	/* list of "named" anon regions */
E 38
I 38
struct swpclean	swap_pager_inuse;	/* list of pending page cleans */
struct swpclean	swap_pager_free;	/* list of free pager clean structs */
struct pagerlst	swap_pager_list;	/* list of "named" anon regions */
E 38

D 7
void
E 7
I 7
D 40
static int		swap_pager_finish __P((swp_clean_t));
E 40
static void 		swap_pager_init __P((void));
D 36
static vm_pager_t	swap_pager_alloc __P((caddr_t, vm_size_t, vm_prot_t));
E 36
I 36
static vm_pager_t	swap_pager_alloc
			    __P((caddr_t, vm_size_t, vm_prot_t, vm_offset_t));
E 36
D 39
static boolean_t	swap_pager_clean __P((vm_page_t, int));
E 39
I 39
static void		swap_pager_clean __P((int));
#ifdef DEBUG
static void		swap_pager_clean_check __P((vm_page_t *, int, int));
#endif
static void		swap_pager_cluster
			    __P((vm_pager_t, vm_offset_t,
				 vm_offset_t *, vm_offset_t *));
E 39
static void		swap_pager_dealloc __P((vm_pager_t));
static int		swap_pager_getpage
D 39
			    __P((vm_pager_t, vm_page_t, boolean_t));
E 39
I 39
			    __P((vm_pager_t, vm_page_t *, int, boolean_t));
E 39
static boolean_t	swap_pager_haspage __P((vm_pager_t, vm_offset_t));
D 39
static int		swap_pager_io __P((sw_pager_t, vm_page_t, int));
E 39
I 39
static int		swap_pager_io __P((sw_pager_t, vm_page_t *, int, int));
E 39
static void		swap_pager_iodone __P((struct buf *));
static int		swap_pager_putpage
D 39
			    __P((vm_pager_t, vm_page_t, boolean_t));
E 39
I 39
			    __P((vm_pager_t, vm_page_t *, int, boolean_t));
E 39

struct pagerops swappagerops = {
	swap_pager_init,
	swap_pager_alloc,
	swap_pager_dealloc,
	swap_pager_getpage,
	swap_pager_putpage,
D 39
	swap_pager_haspage
E 39
I 39
	swap_pager_haspage,
	swap_pager_cluster
E 39
};

static void
E 7
swap_pager_init()
{
	register swp_clean_t spc;
	register int i, bsize;
	extern int dmmin, dmmax;
	int maxbsize;

#ifdef DEBUG
	if (swpagerdebug & (SDB_FOLLOW|SDB_INIT))
		printf("swpg_init()\n");
#endif
	dfltpagerops = &swappagerops;
D 38
	queue_init(&swap_pager_list);
E 38
I 38
	TAILQ_INIT(&swap_pager_list);
E 38

	/*
I 39
	 * Allocate async IO structures.
	 *
	 * XXX it would be nice if we could do this dynamically based on
	 * the value of nswbuf (since we are ultimately limited by that)
	 * but neither nswbuf or malloc has been initialized yet.  So the
	 * structs are statically allocated above.
	 */
	swap_pager_npendingio = NPENDINGIO;

	/*
E 39
	 * Initialize clean lists
	 */
D 38
	queue_init(&swap_pager_inuse);
	queue_init(&swap_pager_free);
E 38
I 38
	TAILQ_INIT(&swap_pager_inuse);
	TAILQ_INIT(&swap_pager_free);
E 38
D 39
	for (i = 0, spc = swcleanlist; i < NPENDINGIO; i++, spc++) {
E 39
I 39
	for (i = 0, spc = swcleanlist; i < swap_pager_npendingio; i++, spc++) {
E 39
D 38
		queue_enter(&swap_pager_free, spc, swp_clean_t, spc_list);
E 38
I 38
		TAILQ_INSERT_TAIL(&swap_pager_free, spc, spc_list);
E 38
		spc->spc_flags = SPC_FREE;
	}

	/*
	 * Calculate the swap allocation constants.
	 */
        if (dmmin == 0) {
                dmmin = DMMIN;
		if (dmmin < CLBYTES/DEV_BSIZE)
			dmmin = CLBYTES/DEV_BSIZE;
	}
        if (dmmax == 0)
                dmmax = DMMAX;

	/*
	 * Fill in our table of object size vs. allocation size
	 */
	bsize = btodb(PAGE_SIZE);
	if (bsize < dmmin)
		bsize = dmmin;
	maxbsize = btodb(sizeof(sw_bm_t) * NBBY * PAGE_SIZE);
	if (maxbsize > dmmax)
		maxbsize = dmmax;
	for (i = 0; i < NSWSIZES; i++) {
		swtab[i].st_osize = (vm_size_t) (MAXDADDRS * dbtob(bsize));
		swtab[i].st_bsize = bsize;
I 39
		if (bsize <= btodb(MAXPHYS))
			swap_pager_maxcluster = dbtob(bsize);
E 39
#ifdef DEBUG
		if (swpagerdebug & SDB_INIT)
			printf("swpg_init: ix %d, size %x, bsize %x\n",
			       i, swtab[i].st_osize, swtab[i].st_bsize);
#endif
		if (bsize >= maxbsize)
			break;
		bsize *= 2;
	}
	swtab[i].st_osize = 0;
	swtab[i].st_bsize = bsize;
}

/*
 * Allocate a pager structure and associated resources.
 * Note that if we are called from the pageout daemon (handle == NULL)
 * we should not wait for memory as it could resulting in deadlock.
 */
D 7
vm_pager_t
E 7
I 7
static vm_pager_t
E 7
D 36
swap_pager_alloc(handle, size, prot)
E 36
I 36
swap_pager_alloc(handle, size, prot, foff)
E 36
	caddr_t handle;
	register vm_size_t size;
	vm_prot_t prot;
I 36
	vm_offset_t foff;
E 36
{
	register vm_pager_t pager;
	register sw_pager_t swp;
	struct swtab *swt;
	int waitok;

#ifdef DEBUG
	if (swpagerdebug & (SDB_FOLLOW|SDB_ALLOC))
		printf("swpg_alloc(%x, %x, %x)\n", handle, size, prot);
#endif
	/*
	 * If this is a "named" anonymous region, look it up and
	 * return the appropriate pager if it exists.
	 */
	if (handle) {
		pager = vm_pager_lookup(&swap_pager_list, handle);
D 3
		if (pager != VM_PAGER_NULL) {
E 3
I 3
		if (pager != NULL) {
E 3
			/*
			 * Use vm_object_lookup to gain a reference
			 * to the object and also to remove from the
			 * object cache.
			 */
D 3
			if (vm_object_lookup(pager) == VM_OBJECT_NULL)
E 3
I 3
			if (vm_object_lookup(pager) == NULL)
E 3
				panic("swap_pager_alloc: bad object");
			return(pager);
		}
	}
	/*
	 * Pager doesn't exist, allocate swap management resources
	 * and initialize.
	 */
	waitok = handle ? M_WAITOK : M_NOWAIT;
	pager = (vm_pager_t)malloc(sizeof *pager, M_VMPAGER, waitok);
D 3
	if (pager == VM_PAGER_NULL)
		return(VM_PAGER_NULL);
E 3
I 3
	if (pager == NULL)
		return(NULL);
E 3
	swp = (sw_pager_t)malloc(sizeof *swp, M_VMPGDATA, waitok);
	if (swp == NULL) {
#ifdef DEBUG
		if (swpagerdebug & SDB_FAIL)
			printf("swpg_alloc: swpager malloc failed\n");
#endif
		free((caddr_t)pager, M_VMPAGER);
D 3
		return(VM_PAGER_NULL);
E 3
I 3
		return(NULL);
E 3
	}
	size = round_page(size);
	for (swt = swtab; swt->st_osize; swt++)
		if (size <= swt->st_osize)
			break;
#ifdef DEBUG
	swt->st_inuse++;
	swt->st_usecnt++;
#endif
	swp->sw_osize = size;
	swp->sw_bsize = swt->st_bsize;
	swp->sw_nblocks = (btodb(size) + swp->sw_bsize - 1) / swp->sw_bsize;
	swp->sw_blocks = (sw_blk_t)
		malloc(swp->sw_nblocks*sizeof(*swp->sw_blocks),
		       M_VMPGDATA, M_NOWAIT);
	if (swp->sw_blocks == NULL) {
		free((caddr_t)swp, M_VMPGDATA);
		free((caddr_t)pager, M_VMPAGER);
#ifdef DEBUG
		if (swpagerdebug & SDB_FAIL)
			printf("swpg_alloc: sw_blocks malloc failed\n");
		swt->st_inuse--;
		swt->st_usecnt--;
#endif
		return(FALSE);
	}
	bzero((caddr_t)swp->sw_blocks,
	      swp->sw_nblocks * sizeof(*swp->sw_blocks));
	swp->sw_poip = 0;
	if (handle) {
		vm_object_t object;

		swp->sw_flags = SW_NAMED;
D 38
		queue_enter(&swap_pager_list, pager, vm_pager_t, pg_list);
E 38
I 38
		TAILQ_INSERT_TAIL(&swap_pager_list, pager, pg_list);
E 38
		/*
		 * Consistant with other pagers: return with object
		 * referenced.  Can't do this with handle == NULL
		 * since it might be the pageout daemon calling.
		 */
		object = vm_object_allocate(size);
		vm_object_enter(object, pager);
		vm_object_setpager(object, pager, 0, FALSE);
	} else {
		swp->sw_flags = 0;
D 38
		queue_init(&pager->pg_list);
E 38
I 38
		pager->pg_list.tqe_next = NULL;
		pager->pg_list.tqe_prev = NULL;
E 38
	}
	pager->pg_handle = handle;
	pager->pg_ops = &swappagerops;
	pager->pg_type = PG_SWAP;
I 39
	pager->pg_flags = PG_CLUSTERPUT;
E 39
D 37
	pager->pg_data = (caddr_t)swp;
E 37
I 37
	pager->pg_data = swp;
E 37

#ifdef DEBUG
	if (swpagerdebug & SDB_ALLOC)
		printf("swpg_alloc: pg_data %x, %x of %x at %x\n",
		       swp, swp->sw_nblocks, swp->sw_bsize, swp->sw_blocks);
#endif
	return(pager);
}

D 7
void
E 7
I 7
static void
E 7
swap_pager_dealloc(pager)
	vm_pager_t pager;
{
	register int i;
	register sw_blk_t bp;
	register sw_pager_t swp;
	struct swtab *swt;
	int s;

#ifdef DEBUG
	/* save panic time state */
	if ((swpagerdebug & SDB_ANOMPANIC) && panicstr)
		return;
	if (swpagerdebug & (SDB_FOLLOW|SDB_ALLOC))
		printf("swpg_dealloc(%x)\n", pager);
#endif
	/*
	 * Remove from list right away so lookups will fail if we
	 * block for pageout completion.
	 */
	swp = (sw_pager_t) pager->pg_data;
	if (swp->sw_flags & SW_NAMED) {
D 38
		queue_remove(&swap_pager_list, pager, vm_pager_t, pg_list);
E 38
I 38
		TAILQ_REMOVE(&swap_pager_list, pager, pg_list);
E 38
		swp->sw_flags &= ~SW_NAMED;
	}
#ifdef DEBUG
	for (swt = swtab; swt->st_osize; swt++)
		if (swp->sw_osize <= swt->st_osize)
			break;
	swt->st_inuse--;
#endif

	/*
	 * Wait for all pageouts to finish and remove
	 * all entries from cleaning list.
	 */
	s = splbio();
	while (swp->sw_poip) {
		swp->sw_flags |= SW_WANTED;
D 7
		assert_wait((int)swp);
E 7
I 7
D 39
		assert_wait((int)swp, 0);
E 7
		thread_block();
E 39
I 39
		(void) tsleep(swp, PVM, "swpgdealloc", 0);
E 39
	}
	splx(s);
D 3
	(void) swap_pager_clean(VM_PAGE_NULL, B_WRITE);
E 3
I 3
D 39
	(void) swap_pager_clean(NULL, B_WRITE);
E 39
I 39
	swap_pager_clean(B_WRITE);
E 39
E 3

	/*
	 * Free left over swap blocks
	 */
	for (i = 0, bp = swp->sw_blocks; i < swp->sw_nblocks; i++, bp++)
		if (bp->swb_block) {
#ifdef DEBUG
			if (swpagerdebug & (SDB_ALLOCBLK|SDB_FULL))
				printf("swpg_dealloc: blk %x\n",
				       bp->swb_block);
#endif
			rmfree(swapmap, swp->sw_bsize, bp->swb_block);
		}
	/*
	 * Free swap management resources
	 */
	free((caddr_t)swp->sw_blocks, M_VMPGDATA);
	free((caddr_t)swp, M_VMPGDATA);
	free((caddr_t)pager, M_VMPAGER);
}

I 7
static int
E 7
D 39
swap_pager_getpage(pager, m, sync)
E 39
I 39
swap_pager_getpage(pager, mlist, npages, sync)
E 39
	vm_pager_t pager;
D 39
	vm_page_t m;
E 39
I 39
	vm_page_t *mlist;
	int npages;
E 39
	boolean_t sync;
{
#ifdef DEBUG
	if (swpagerdebug & SDB_FOLLOW)
D 39
		printf("swpg_getpage(%x, %x, %d)\n", pager, m, sync);
E 39
I 39
		printf("swpg_getpage(%x, %x, %x, %x)\n",
		       pager, mlist, npages, sync);
E 39
#endif
D 39
	return(swap_pager_io((sw_pager_t)pager->pg_data, m, B_READ));
E 39
I 39
	return(swap_pager_io((sw_pager_t)pager->pg_data,
			     mlist, npages, B_READ));
E 39
}

I 7
static int
E 7
D 39
swap_pager_putpage(pager, m, sync)
E 39
I 39
swap_pager_putpage(pager, mlist, npages, sync)
E 39
	vm_pager_t pager;
D 39
	vm_page_t m;
E 39
I 39
	vm_page_t *mlist;
	int npages;
E 39
	boolean_t sync;
{
	int flags;

#ifdef DEBUG
	if (swpagerdebug & SDB_FOLLOW)
D 39
		printf("swpg_putpage(%x, %x, %d)\n", pager, m, sync);
E 39
I 39
		printf("swpg_putpage(%x, %x, %x, %x)\n",
		       pager, mlist, npages, sync);
E 39
#endif
D 3
	if (pager == VM_PAGER_NULL) {
		(void) swap_pager_clean(VM_PAGE_NULL, B_WRITE);
E 3
I 3
	if (pager == NULL) {
D 39
		(void) swap_pager_clean(NULL, B_WRITE);
E 39
I 39
		swap_pager_clean(B_WRITE);
E 39
E 3
D 26
		return;
E 26
I 26
		return (VM_PAGER_OK);		/* ??? */
E 26
	}
	flags = B_WRITE;
	if (!sync)
		flags |= B_ASYNC;
D 39
	return(swap_pager_io((sw_pager_t)pager->pg_data, m, flags));
E 39
I 39
	return(swap_pager_io((sw_pager_t)pager->pg_data,
			     mlist, npages, flags));
E 39
}

D 7
boolean_t
E 7
I 7
static boolean_t
E 7
swap_pager_haspage(pager, offset)
	vm_pager_t pager;
	vm_offset_t offset;
{
	register sw_pager_t swp;
	register sw_blk_t swb;
	int ix;

#ifdef DEBUG
	if (swpagerdebug & (SDB_FOLLOW|SDB_ALLOCBLK))
		printf("swpg_haspage(%x, %x) ", pager, offset);
#endif
	swp = (sw_pager_t) pager->pg_data;
	ix = offset / dbtob(swp->sw_bsize);
	if (swp->sw_blocks == NULL || ix >= swp->sw_nblocks) {
#ifdef DEBUG
		if (swpagerdebug & (SDB_FAIL|SDB_FOLLOW|SDB_ALLOCBLK))
			printf("swpg_haspage: %x bad offset %x, ix %x\n",
			       swp->sw_blocks, offset, ix);
#endif
		return(FALSE);
	}
	swb = &swp->sw_blocks[ix];
	if (swb->swb_block)
		ix = atop(offset % dbtob(swp->sw_bsize));
#ifdef DEBUG
	if (swpagerdebug & SDB_ALLOCBLK)
		printf("%x blk %x+%x ", swp->sw_blocks, swb->swb_block, ix);
	if (swpagerdebug & (SDB_FOLLOW|SDB_ALLOCBLK))
		printf("-> %c\n",
		       "FT"[swb->swb_block && (swb->swb_mask & (1 << ix))]);
#endif
	if (swb->swb_block && (swb->swb_mask & (1 << ix)))
		return(TRUE);
	return(FALSE);
}

I 39
static void
swap_pager_cluster(pager, offset, loffset, hoffset)
	vm_pager_t	pager;
	vm_offset_t	offset;
	vm_offset_t	*loffset;
	vm_offset_t	*hoffset;
{
	sw_pager_t swp;
	register int bsize;
	vm_offset_t loff, hoff;

#ifdef DEBUG
	if (swpagerdebug & (SDB_FOLLOW|SDB_CLUSTER))
		printf("swpg_cluster(%x, %x) ", pager, offset);
#endif
	swp = (sw_pager_t) pager->pg_data;
	bsize = dbtob(swp->sw_bsize);
	if (bsize > swap_pager_maxcluster)
		bsize = swap_pager_maxcluster;

	loff = offset - (offset % bsize);
	if (loff >= swp->sw_osize)
		panic("swap_pager_cluster: bad offset");

	hoff = loff + bsize;
	if (hoff > swp->sw_osize)
		hoff = swp->sw_osize;

	*loffset = loff;
	*hoffset = hoff;
#ifdef DEBUG
	if (swpagerdebug & (SDB_FOLLOW|SDB_CLUSTER))
		printf("returns [%x-%x]\n", loff, hoff);
#endif
}

E 39
/*
 * Scaled down version of swap().
 * Assumes that PAGE_SIZE < MAXPHYS; i.e. only one operation needed.
 * BOGUS:  lower level IO routines expect a KVA so we have to map our
 * provided physical page into the KVA to keep them happy.
 */
I 7
static int
E 7
D 39
swap_pager_io(swp, m, flags)
E 39
I 39
swap_pager_io(swp, mlist, npages, flags)
E 39
	register sw_pager_t swp;
D 39
	vm_page_t m;
E 39
I 39
	vm_page_t *mlist;
	int npages;
E 39
	int flags;
{
I 24
D 25
	USES_VOP_STRATEGY;
E 25
E 24
	register struct buf *bp;
	register sw_blk_t swb;
	register int s;
D 39
	int ix;
E 39
I 39
	int ix, mask;
E 39
	boolean_t rv;
	vm_offset_t kva, off;
	swp_clean_t spc;
I 39
	vm_page_t m;
E 39

#ifdef DEBUG
	/* save panic time state */
	if ((swpagerdebug & SDB_ANOMPANIC) && panicstr)
D 7
		return;
E 7
I 7
		return (VM_PAGER_FAIL);		/* XXX: correct return? */
E 7
	if (swpagerdebug & (SDB_FOLLOW|SDB_IO))
D 39
		printf("swpg_io(%x, %x, %x)\n", swp, m, flags);
I 37
	if ((flags & (B_READ|B_ASYNC)) == (B_READ|B_ASYNC))
		panic("swap_pager_io: cannot do ASYNC reads");
E 39
I 39
		printf("swpg_io(%x, %x, %x, %x)\n", swp, mlist, npages, flags);
	if (flags & B_READ) {
		if (flags & B_ASYNC)
			panic("swap_pager_io: cannot do ASYNC reads");
		if (npages != 1)
			panic("swap_pager_io: cannot do clustered reads");
	}
E 39
E 37
#endif

	/*
I 37
	 * First determine if the page exists in the pager if this is
	 * a sync read.  This quickly handles cases where we are
	 * following shadow chains looking for the top level object
	 * with the page.
	 */
I 39
	m = *mlist;
E 39
	off = m->offset + m->object->paging_offset;
	ix = off / dbtob(swp->sw_bsize);
D 39
	if (swp->sw_blocks == NULL || ix >= swp->sw_nblocks)
E 39
I 39
	if (swp->sw_blocks == NULL || ix >= swp->sw_nblocks) {
#ifdef DEBUG
		if ((flags & B_READ) == 0 && (swpagerdebug & SDB_ANOM)) {
			printf("swap_pager_io: no swap block on write\n");
			return(VM_PAGER_BAD);
		}
#endif
E 39
		return(VM_PAGER_FAIL);
I 39
	}
E 39
	swb = &swp->sw_blocks[ix];
	off = off % dbtob(swp->sw_bsize);
	if ((flags & B_READ) &&
	    (swb->swb_block == 0 || (swb->swb_mask & (1 << atop(off))) == 0))
		return(VM_PAGER_FAIL);

	/*
E 37
	 * For reads (pageins) and synchronous writes, we clean up
D 4
	 * all completed async pageouts and check to see if this
	 * page is currently being cleaned.  If it is, we just wait
	 * til the operation is done before continuing.
E 4
I 4
	 * all completed async pageouts.
E 4
	 */
	if ((flags & B_ASYNC) == 0) {
		s = splbio();
I 39
		swap_pager_clean(flags&B_READ);
E 39
I 4
#ifdef DEBUG
D 39
		/*
		 * Check to see if this page is currently being cleaned.
		 * If it is, we just wait til the operation is done before
		 * continuing.
		 */
E 4
		while (swap_pager_clean(m, flags&B_READ)) {
I 4
			if (swpagerdebug & SDB_ANOM)
				printf("swap_pager_io: page %x cleaning\n", m);

E 4
			swp->sw_flags |= SW_WANTED;
D 7
			assert_wait((int)swp);
E 7
I 7
			assert_wait((int)swp, 0);
E 7
			thread_block();
		}
I 4
#else
		(void) swap_pager_clean(m, flags&B_READ);
E 39
I 39
		if (swpagerdebug & SDB_PARANOIA)
			swap_pager_clean_check(mlist, npages, flags&B_READ);
E 39
#endif
E 4
		splx(s);
	}
	/*
	 * For async writes (pageouts), we cleanup completed pageouts so
	 * that all available resources are freed.  Also tells us if this
	 * page is already being cleaned.  If it is, or no resources
	 * are available, we try again later.
	 */
D 4
	else if (swap_pager_clean(m, B_WRITE) || queue_empty(&swap_pager_free))
E 4
I 4
D 39
	else if (swap_pager_clean(m, B_WRITE) ||
D 38
		 queue_empty(&swap_pager_free)) {
E 38
I 38
		 swap_pager_free.tqh_first == NULL) {
E 39
I 39
	else {
		swap_pager_clean(B_WRITE);
E 39
E 38
#ifdef DEBUG
D 39
		if ((swpagerdebug & SDB_ANOM) &&
D 38
		    !queue_empty(&swap_pager_free))
E 38
I 38
		    swap_pager_free.tqh_first != NULL)
E 38
			printf("swap_pager_io: page %x already cleaning\n", m);
E 39
I 39
		if (swpagerdebug & SDB_PARANOIA)
			swap_pager_clean_check(mlist, npages, B_WRITE);
E 39
#endif
E 4
D 39
		return(VM_PAGER_FAIL);
E 39
I 39
		if (swap_pager_free.tqh_first == NULL) {
#ifdef DEBUG
			if (swpagerdebug & SDB_FAIL)
				printf("%s: no available io headers\n",
				       "swap_pager_io");
#endif
			return(VM_PAGER_AGAIN);
		}
E 39
I 4
	}
E 4

	/*
D 37
	 * Determine swap block and allocate as necessary.
E 37
I 37
	 * Allocate a swap block if necessary.
E 37
	 */
D 37
	off = m->offset + m->object->paging_offset;
	ix = off / dbtob(swp->sw_bsize);
	if (swp->sw_blocks == NULL || ix >= swp->sw_nblocks) {
#ifdef DEBUG
		if (swpagerdebug & SDB_FAIL)
			printf("swpg_io: bad offset %x+%x(%d) in %x\n",
			       m->offset, m->object->paging_offset,
			       ix, swp->sw_blocks);
#endif
		return(VM_PAGER_FAIL);
	}
	swb = &swp->sw_blocks[ix];
	off = off % dbtob(swp->sw_bsize);
	if (flags & B_READ) {
		if (swb->swb_block == 0 ||
		    (swb->swb_mask & (1 << atop(off))) == 0) {
#ifdef DEBUG
			if (swpagerdebug & (SDB_ALLOCBLK|SDB_FAIL))
				printf("swpg_io: %x bad read: blk %x+%x, mask %x, off %x+%x\n",
				       swp->sw_blocks,
				       swb->swb_block, atop(off),
				       swb->swb_mask,
				       m->offset, m->object->paging_offset);
#endif
			/* XXX: should we zero page here?? */
			return(VM_PAGER_FAIL);
		}
	} else if (swb->swb_block == 0) {
E 37
I 37
	if (swb->swb_block == 0) {
E 37
		swb->swb_block = rmalloc(swapmap, swp->sw_bsize);
		if (swb->swb_block == 0) {
#ifdef DEBUG
			if (swpagerdebug & SDB_FAIL)
				printf("swpg_io: rmalloc of %x failed\n",
				       swp->sw_bsize);
#endif
I 39
			/*
			 * XXX this is technically a resource shortage that
			 * should return AGAIN, but the situation isn't likely
			 * to be remedied just by delaying a little while and
			 * trying again (the pageout daemon's current response
			 * to AGAIN) so we just return FAIL.
			 */
E 39
			return(VM_PAGER_FAIL);
		}
#ifdef DEBUG
		if (swpagerdebug & (SDB_FULL|SDB_ALLOCBLK))
			printf("swpg_io: %x alloc blk %x at ix %x\n",
			       swp->sw_blocks, swb->swb_block, ix);
#endif
	}

	/*
	 * Allocate a kernel virtual address and initialize so that PTE
	 * is available for lower level IO drivers.
	 */
D 39
	kva = vm_pager_map_page(m);
E 39
I 39
	kva = vm_pager_map_pages(mlist, npages, !(flags & B_ASYNC));
	if (kva == NULL) {
#ifdef DEBUG
		if (swpagerdebug & SDB_FAIL)
			printf("%s: no KVA space to map pages\n",
			       "swap_pager_io");
#endif
		return(VM_PAGER_AGAIN);
	}
E 39

	/*
D 39
	 * Get a swap buffer header and perform the IO
E 39
I 39
	 * Get a swap buffer header and initialize it.
E 39
	 */
	s = splbio();
D 30
	while (bswlist.av_forw == NULL) {
E 30
I 30
	while (bswlist.b_actf == NULL) {
E 30
#ifdef DEBUG
		if (swpagerdebug & SDB_ANOM)
D 4
			printf("swpg_io: wait on swbuf for %x (%d)\n",
E 4
I 4
			printf("swap_pager_io: wait on swbuf for %x (%d)\n",
E 4
			       m, flags);
#endif
		bswlist.b_flags |= B_WANTED;
D 37
		sleep((caddr_t)&bswlist, PSWP+1);
E 37
I 37
D 39
		tsleep((caddr_t)&bswlist, PSWP+1, "swpgio", 0);
E 39
I 39
		tsleep((caddr_t)&bswlist, PSWP+1, "swpgiobuf", 0);
E 39
E 37
	}
D 30
	bp = bswlist.av_forw;
	bswlist.av_forw = bp->av_forw;
E 30
I 30
	bp = bswlist.b_actf;
	bswlist.b_actf = bp->b_actf;
E 30
	splx(s);
	bp->b_flags = B_BUSY | (flags & B_READ);
D 3
	bp->b_proc = &proc[0];	/* XXX (but without B_PHYS set this is ok) */
E 3
I 3
	bp->b_proc = &proc0;	/* XXX (but without B_PHYS set this is ok) */
E 3
D 35
	bp->b_un.b_addr = (caddr_t)kva;
E 35
I 35
	bp->b_data = (caddr_t)kva;
E 35
	bp->b_blkno = swb->swb_block + btodb(off);
	VHOLD(swapdev_vp);
	bp->b_vp = swapdev_vp;
D 2
	bp->b_dev = swapdev_vp->v_rdev;
E 2
I 2
	if (swapdev_vp->v_type == VBLK)
		bp->b_dev = swapdev_vp->v_rdev;
E 2
D 39
	bp->b_bcount = PAGE_SIZE;
E 39
I 39
	bp->b_bcount = npages * PAGE_SIZE;

	/*
	 * For writes we set up additional buffer fields, record a pageout
	 * in progress and mark that these swap blocks are now allocated.
	 */
E 39
D 6
	if ((bp->b_flags & B_READ) == 0)
E 6
I 6
	if ((bp->b_flags & B_READ) == 0) {
		bp->b_dirtyoff = 0;
D 39
		bp->b_dirtyend = PAGE_SIZE;
E 39
I 39
		bp->b_dirtyend = npages * PAGE_SIZE;
E 39
E 6
		swapdev_vp->v_numoutput++;
I 39
		s = splbio();
		swp->sw_poip++;
		splx(s);
		mask = (~(~0 << npages)) << atop(off);
#ifdef DEBUG
		swap_pager_poip++;
		if (swpagerdebug & SDB_WRITE)
			printf("swpg_io: write: bp=%x swp=%x poip=%d\n",
			       bp, swp, swp->sw_poip);
		if ((swpagerdebug & SDB_ALLOCBLK) &&
		    (swb->swb_mask & mask) != mask)
			printf("swpg_io: %x write %d pages at %x+%x\n",
			       swp->sw_blocks, npages, swb->swb_block,
			       atop(off));
		if (swpagerdebug & SDB_CLUSTER)
			printf("swpg_io: off=%x, npg=%x, mask=%x, bmask=%x\n",
			       off, npages, mask, swb->swb_mask);
#endif
		swb->swb_mask |= mask;
E 39
I 6
	}
E 6
D 39

E 39
	/*
D 39
	 * If this is an async write we set up additional buffer fields
E 39
I 39
	 * If this is an async write we set up still more buffer fields
E 39
	 * and place a "cleaning" entry on the inuse queue.
	 */
	if ((flags & (B_READ|B_ASYNC)) == B_ASYNC) {
#ifdef DEBUG
D 38
		if (queue_empty(&swap_pager_free))
E 38
I 38
		if (swap_pager_free.tqh_first == NULL)
E 38
			panic("swpg_io: lost spc");
#endif
D 38
		queue_remove_first(&swap_pager_free,
				   spc, swp_clean_t, spc_list);
E 38
I 38
		spc = swap_pager_free.tqh_first;
		TAILQ_REMOVE(&swap_pager_free, spc, spc_list);
E 38
#ifdef DEBUG
		if (spc->spc_flags != SPC_FREE)
			panic("swpg_io: bad free spc");
#endif
		spc->spc_flags = SPC_BUSY;
		spc->spc_bp = bp;
		spc->spc_swp = swp;
		spc->spc_kva = kva;
I 39
		/*
D 41
		 * Record the first page.  This allows swap_pager_finish
E 41
I 41
		 * Record the first page.  This allows swap_pager_clean
E 41
		 * to efficiently handle the common case of a single page.
		 * For clusters, it allows us to locate the object easily
		 * and we then reconstruct the rest of the mlist from spc_kva.
I 40
D 41
		 *
		 * XXX
		 * swap_pager_finish no longer exists.
E 41
E 40
		 */
E 39
		spc->spc_m = m;
I 39
		spc->spc_npages = npages;
E 39
D 4
#ifdef DEBUG
		m->pagerowned = 1;
#endif
E 4
		bp->b_flags |= B_CALL;
		bp->b_iodone = swap_pager_iodone;
		s = splbio();
D 39
		swp->sw_poip++;
E 39
D 38
		queue_enter(&swap_pager_inuse, spc, swp_clean_t, spc_list);
E 38
I 38
		TAILQ_INSERT_TAIL(&swap_pager_inuse, spc, spc_list);
E 38
D 39

#ifdef DEBUG
		swap_pager_poip++;
		if (swpagerdebug & SDB_WRITE)
			printf("swpg_io: write: bp=%x swp=%x spc=%x poip=%d\n",
			       bp, swp, spc, swp->sw_poip);
		if ((swpagerdebug & SDB_ALLOCBLK) &&
		    (swb->swb_mask & (1 << atop(off))) == 0)
			printf("swpg_io: %x write blk %x+%x\n",
			       swp->sw_blocks, swb->swb_block, atop(off));
#endif
		swb->swb_mask |= (1 << atop(off));
E 39
D 4
		/*
		 * XXX: Block write faults til we are done.
		 */
		m->page_lock = VM_PROT_WRITE;
		m->unlock_request = VM_PROT_ALL;
		pmap_copy_on_write(VM_PAGE_TO_PHYS(m));
E 4
		splx(s);
	}
I 39

	/*
	 * Finally, start the IO operation.
	 * If it is async we are all done, otherwise we must wait for
	 * completion and cleanup afterwards.
	 */
E 39
#ifdef DEBUG
	if (swpagerdebug & SDB_IO)
		printf("swpg_io: IO start: bp %x, db %x, va %x, pa %x\n",
		       bp, swb->swb_block+btodb(off), kva, VM_PAGE_TO_PHYS(m));
#endif
	VOP_STRATEGY(bp);
	if ((flags & (B_READ|B_ASYNC)) == B_ASYNC) {
#ifdef DEBUG
		if (swpagerdebug & SDB_IO)
			printf("swpg_io:  IO started: bp %x\n", bp);
#endif
		return(VM_PAGER_PEND);
	}
	s = splbio();
#ifdef DEBUG
	if (flags & B_READ)
		swap_pager_piip++;
	else
		swap_pager_poip++;
#endif
D 39
	while ((bp->b_flags & B_DONE) == 0) {
D 7
		assert_wait((int)bp);
E 7
I 7
		assert_wait((int)bp, 0);
E 7
		thread_block();
	}
E 39
I 39
	while ((bp->b_flags & B_DONE) == 0)
		(void) tsleep(bp, PVM, "swpgio", 0);
	if ((flags & B_READ) == 0)
		--swp->sw_poip;
E 39
#ifdef DEBUG
	if (flags & B_READ)
		--swap_pager_piip;
	else
		--swap_pager_poip;
#endif
D 28
	rv = (bp->b_flags & B_ERROR) ? VM_PAGER_FAIL : VM_PAGER_OK;
E 28
I 28
	rv = (bp->b_flags & B_ERROR) ? VM_PAGER_ERROR : VM_PAGER_OK;
E 28
	bp->b_flags &= ~(B_BUSY|B_WANTED|B_PHYS|B_PAGET|B_UAREA|B_DIRTY);
D 30
	bp->av_forw = bswlist.av_forw;
	bswlist.av_forw = bp;
E 30
I 30
	bp->b_actf = bswlist.b_actf;
	bswlist.b_actf = bp;
E 30
	if (bp->b_vp)
		brelvp(bp);
	if (bswlist.b_flags & B_WANTED) {
		bswlist.b_flags &= ~B_WANTED;
D 39
		thread_wakeup((int)&bswlist);
E 39
I 39
		wakeup(&bswlist);
E 39
	}
	if ((flags & B_READ) == 0 && rv == VM_PAGER_OK) {
D 4
		m->clean = 1;
E 4
I 4
D 29
		m->clean = TRUE;
E 29
I 29
		m->flags |= PG_CLEAN;
E 29
E 4
		pmap_clear_modify(VM_PAGE_TO_PHYS(m));
	}
	splx(s);
#ifdef DEBUG
	if (swpagerdebug & SDB_IO)
		printf("swpg_io:  IO done: bp %x, rv %d\n", bp, rv);
D 28
	if ((swpagerdebug & SDB_FAIL) && rv == VM_PAGER_FAIL)
E 28
I 28
	if ((swpagerdebug & SDB_FAIL) && rv == VM_PAGER_ERROR)
E 28
		printf("swpg_io: IO error\n");
#endif
D 39
	vm_pager_unmap_page(kva);
E 39
I 39
	vm_pager_unmap_pages(kva, npages);
E 39
	return(rv);
}

D 7
boolean_t
E 7
I 7
D 39
static boolean_t
E 7
swap_pager_clean(m, rw)
	vm_page_t m;
E 39
I 39
static void
swap_pager_clean(rw)
E 39
	int rw;
{
D 39
	register swp_clean_t spc, tspc;
	register int s;
E 39
I 39
	register swp_clean_t spc;
	register int s, i;
	vm_object_t object;
	vm_page_t m;
E 39

#ifdef DEBUG
	/* save panic time state */
	if ((swpagerdebug & SDB_ANOMPANIC) && panicstr)
D 26
		return;
E 26
I 26
D 39
		return (FALSE);			/* ??? */
E 39
I 39
		return;
E 39
E 26
	if (swpagerdebug & SDB_FOLLOW)
D 39
		printf("swpg_clean(%x, %d)\n", m, rw);
E 39
I 39
		printf("swpg_clean(%x)\n", rw);
E 39
#endif
D 3
	tspc = SWP_CLEAN_NULL;
E 3
I 3
D 39
	tspc = NULL;
E 39
I 39

E 39
E 3
	for (;;) {
		/*
		 * Look up and removal from inuse list must be done
		 * at splbio() to avoid conflicts with swap_pager_iodone.
		 */
		s = splbio();
D 38
		spc = (swp_clean_t) queue_first(&swap_pager_inuse);
		while (!queue_end(&swap_pager_inuse, (queue_entry_t)spc)) {
E 38
I 38
		for (spc = swap_pager_inuse.tqh_first;
		     spc != NULL;
		     spc = spc->spc_list.tqe_next) {
I 39
			/*
			 * If the operation is done, remove it from the
			 * list and process it.
			 *
			 * XXX if we can't get the object lock we also
			 * leave it on the list and try again later.
			 * Is there something better we could do?
			 */
E 39
E 38
			if ((spc->spc_flags & SPC_DONE) &&
D 39
			    swap_pager_finish(spc)) {
E 39
I 39
			    vm_object_lock_try(spc->spc_m->object)) {
E 39
D 38
				queue_remove(&swap_pager_inuse, spc,
					     swp_clean_t, spc_list);
E 38
I 38
				TAILQ_REMOVE(&swap_pager_inuse, spc, spc_list);
E 38
				break;
			}
D 39
			if (m && m == spc->spc_m) {
#ifdef DEBUG
				if (swpagerdebug & SDB_ANOM)
D 4
					printf("swpg_clean: %x on list, flags %x\n",
E 4
I 4
					printf("swap_pager_clean: page %x on list, flags %x\n",
E 4
					       m, spc->spc_flags);
#endif
				tspc = spc;
			}
E 39
D 38
			spc = (swp_clean_t) queue_next(&spc->spc_list);
E 38
		}
I 42
		splx(s);
E 42

		/*
		 * No operations done, thats all we can do for now.
		 */
D 38
		if (queue_end(&swap_pager_inuse, (queue_entry_t)spc))
E 38
I 38
D 39
		if (spc == NULL)
E 39
I 39
D 42
		if (spc == NULL) {
			splx(s);
E 42
I 42
		if (spc == NULL)
E 42
E 39
E 38
			break;
I 39
D 42
		}
E 39
		splx(s);
E 42

		/*
D 39
		 * The desired page was found to be busy earlier in
		 * the scan but has since completed.
E 39
I 39
		 * Found a completed operation so finish it off.
		 * Note: no longer at splbio since entry is off the list.
E 39
		 */
D 39
		if (tspc && tspc == spc) {
#ifdef DEBUG
			if (swpagerdebug & SDB_ANOM)
D 4
				printf("swpg_clean: %x done while looking\n",
E 4
I 4
				printf("swap_pager_clean: page %x done while looking\n",
E 4
				       m);
#endif
D 3
			tspc = SWP_CLEAN_NULL;
E 3
I 3
			tspc = NULL;
E 39
I 39
		m = spc->spc_m;
		object = m->object;

		/*
		 * Process each page in the cluster.
		 * The first page is explicitly kept in the cleaning
		 * entry, others must be reconstructed from the KVA.
		 */
		for (i = 0; i < spc->spc_npages; i++) {
			if (i)
				m = vm_pager_atop(spc->spc_kva + ptoa(i));
			/*
			 * If no error mark as clean and inform the pmap
			 * system.  If there was an error, mark as dirty
			 * so we will try again.
			 *
			 * XXX could get stuck doing this, should give up
			 * after awhile.
			 */
			if (spc->spc_flags & SPC_ERROR) {
				printf("%s: clean of page %x failed\n",
				       "swap_pager_clean",
				       VM_PAGE_TO_PHYS(m));
				m->flags |= PG_LAUNDRY;
			} else {
				m->flags |= PG_CLEAN;
				pmap_clear_modify(VM_PAGE_TO_PHYS(m));
			}
			m->flags &= ~PG_BUSY;
			PAGE_WAKEUP(m);
E 39
E 3
		}
I 39

		/*
		 * Done with the object, decrement the paging count
		 * and unlock it.
		 */
		if (--object->paging_in_progress == 0)
			wakeup(object);
		vm_object_unlock(object);

		/*
		 * Free up KVM used and put the entry back on the list.
		 */
		vm_pager_unmap_pages(spc->spc_kva, spc->spc_npages);
E 39
		spc->spc_flags = SPC_FREE;
D 39
		vm_pager_unmap_page(spc->spc_kva);
E 39
D 38
		queue_enter(&swap_pager_free, spc, swp_clean_t, spc_list);
E 38
I 38
		TAILQ_INSERT_TAIL(&swap_pager_free, spc, spc_list);
E 38
#ifdef DEBUG
		if (swpagerdebug & SDB_WRITE)
			printf("swpg_clean: free spc %x\n", spc);
#endif
	}
I 4
D 39
#ifdef DEBUG
E 4
	/*
	 * If we found that the desired page is already being cleaned
	 * mark it so that swap_pager_iodone() will not set the clean
	 * flag before the pageout daemon has another chance to clean it.
	 */
	if (tspc && rw == B_WRITE) {
D 4
#ifdef DEBUG
E 4
		if (swpagerdebug & SDB_ANOM)
D 4
			printf("swpg_clean: %x on clean list\n", tspc);
#endif
E 4
I 4
			printf("swap_pager_clean: page %x on clean list\n",
			       tspc);
E 4
		tspc->spc_flags |= SPC_DIRTY;
	}
I 4
#endif
E 4
	splx(s);

#ifdef DEBUG
	if (swpagerdebug & SDB_WRITE)
		printf("swpg_clean: return %d\n", tspc ? TRUE : FALSE);
	if ((swpagerdebug & SDB_ANOM) && tspc)
		printf("swpg_clean: %s of cleaning page %x\n",
		       rw == B_READ ? "get" : "put", m);
#endif
	return(tspc ? TRUE : FALSE);
E 39
}

I 7
D 39
static int
E 7
swap_pager_finish(spc)
	register swp_clean_t spc;
E 39
I 39
#ifdef DEBUG
static void
swap_pager_clean_check(mlist, npages, rw)
	vm_page_t *mlist;
	int npages;
	int rw;
E 39
{
D 39
	vm_object_t object = spc->spc_m->object;
E 39
I 39
	register swp_clean_t spc;
	boolean_t bad;
	int i, j, s;
	vm_page_t m;
E 39

D 39
	/*
	 * Mark the paging operation as done.
	 * (XXX) If we cannot get the lock, leave it til later.
	 * (XXX) Also we are assuming that an async write is a
	 *       pageout operation that has incremented the counter.
	 */
	if (!vm_object_lock_try(object))
		return(0);
E 39
I 39
	if (panicstr)
		return;
E 39

D 4
#ifdef DEBUG
	spc->spc_m->pagerowned = 0;
#endif

E 4
D 39
	if (--object->paging_in_progress == 0)
		thread_wakeup((int) object);

I 4
#ifdef DEBUG
E 4
	/*
	 * XXX: this isn't even close to the right thing to do,
	 * introduces a variety of race conditions.
	 *
	 * If dirty, vm_pageout() has attempted to clean the page
	 * again.  In this case we do not do anything as we will
D 4
	 * see the page again shortly.  Otherwise, if no error mark
	 * as clean and inform the pmap system.  If error, mark as
	 * dirty so we will try again (XXX: could get stuck doing
	 * this, should give up after awhile).
E 4
I 4
	 * see the page again shortly.
E 4
	 */
D 4
	if ((spc->spc_flags & SPC_DIRTY) == 0) {
		if (spc->spc_flags & SPC_ERROR) {
			printf("swap_pager: clean of %x failed\n",
			       VM_PAGE_TO_PHYS(spc->spc_m));
			spc->spc_m->laundry = TRUE;
		} else {
			spc->spc_m->clean = TRUE;
			pmap_clear_modify(VM_PAGE_TO_PHYS(spc->spc_m));
		}
E 4
I 4
	if (spc->spc_flags & SPC_DIRTY) {
		if (swpagerdebug & SDB_ANOM)
			printf("swap_pager_finish: page %x dirty again\n",
			       spc->spc_m);
D 29
		spc->spc_m->busy = FALSE;
E 29
I 29
		spc->spc_m->flags &= ~PG_BUSY;
E 29
		PAGE_WAKEUP(spc->spc_m);
		vm_object_unlock(object);
		return(1);
E 39
I 39
	bad = FALSE;
	s = splbio();
	for (spc = swap_pager_inuse.tqh_first;
	     spc != NULL;
	     spc = spc->spc_list.tqe_next) {
		for (j = 0; j < spc->spc_npages; j++) {
			m = vm_pager_atop(spc->spc_kva + ptoa(j));
			for (i = 0; i < npages; i++)
				if (m == mlist[i]) {
					if (swpagerdebug & SDB_ANOM)
						printf(
		"swpg_clean_check: %s: page %x on list, flags %x\n",
		rw == B_WRITE ? "write" : "read", mlist[i], spc->spc_flags);
					bad = TRUE;
				}
		}
E 39
E 4
	}
I 39
	splx(s);
	if (bad)
		panic("swpg_clean_check");
}
E 39
I 4
#endif
E 4
D 39
	/*
D 4
	 * XXX: allow blocked write faults to continue
E 4
I 4
	 * If no error mark as clean and inform the pmap system.
	 * If error, mark as dirty so we will try again.
	 * (XXX could get stuck doing this, should give up after awhile)
E 4
	 */
D 4
	spc->spc_m->page_lock = spc->spc_m->unlock_request = VM_PROT_NONE;
E 4
I 4
	if (spc->spc_flags & SPC_ERROR) {
		printf("swap_pager_finish: clean of page %x failed\n",
		       VM_PAGE_TO_PHYS(spc->spc_m));
D 29
		spc->spc_m->laundry = TRUE;
E 29
I 29
		spc->spc_m->flags |= PG_LAUNDRY;
E 29
	} else {
D 29
		spc->spc_m->clean = TRUE;
E 29
I 29
		spc->spc_m->flags |= PG_CLEAN;
E 29
		pmap_clear_modify(VM_PAGE_TO_PHYS(spc->spc_m));
	}
D 29
	spc->spc_m->busy = FALSE;
E 29
I 29
	spc->spc_m->flags &= ~PG_BUSY;
E 29
E 4
	PAGE_WAKEUP(spc->spc_m);
E 39

D 39
	vm_object_unlock(object);
	return(1);
}

E 39
I 7
static void
E 7
swap_pager_iodone(bp)
	register struct buf *bp;
{
	register swp_clean_t spc;
	daddr_t blk;
	int s;

#ifdef DEBUG
	/* save panic time state */
	if ((swpagerdebug & SDB_ANOMPANIC) && panicstr)
		return;
	if (swpagerdebug & SDB_FOLLOW)
		printf("swpg_iodone(%x)\n", bp);
#endif
	s = splbio();
D 38
	spc = (swp_clean_t) queue_first(&swap_pager_inuse);
	while (!queue_end(&swap_pager_inuse, (queue_entry_t)spc)) {
E 38
I 38
	for (spc = swap_pager_inuse.tqh_first;
	     spc != NULL;
	     spc = spc->spc_list.tqe_next)
E 38
		if (spc->spc_bp == bp)
			break;
D 38
		spc = (swp_clean_t) queue_next(&spc->spc_list);
	}
E 38
#ifdef DEBUG
D 38
	if (queue_end(&swap_pager_inuse, (queue_entry_t)spc))
E 38
I 38
	if (spc == NULL)
E 38
D 4
		panic("swpg_iodone: bp not found");
E 4
I 4
		panic("swap_pager_iodone: bp not found");
E 4
#endif

	spc->spc_flags &= ~SPC_BUSY;
	spc->spc_flags |= SPC_DONE;
	if (bp->b_flags & B_ERROR)
		spc->spc_flags |= SPC_ERROR;
	spc->spc_bp = NULL;
	blk = bp->b_blkno;

#ifdef DEBUG
	--swap_pager_poip;
	if (swpagerdebug & SDB_WRITE)
		printf("swpg_iodone: bp=%x swp=%x flags=%x spc=%x poip=%x\n",
		       bp, spc->spc_swp, spc->spc_swp->sw_flags,
		       spc, spc->spc_swp->sw_poip);
#endif

	spc->spc_swp->sw_poip--;
	if (spc->spc_swp->sw_flags & SW_WANTED) {
		spc->spc_swp->sw_flags &= ~SW_WANTED;
D 39
		thread_wakeup((int)spc->spc_swp);
E 39
I 39
		wakeup(spc->spc_swp);
E 39
	}
		
	bp->b_flags &= ~(B_BUSY|B_WANTED|B_PHYS|B_PAGET|B_UAREA|B_DIRTY);
D 30
	bp->av_forw = bswlist.av_forw;
	bswlist.av_forw = bp;
E 30
I 30
	bp->b_actf = bswlist.b_actf;
	bswlist.b_actf = bp;
E 30
	if (bp->b_vp)
		brelvp(bp);
	if (bswlist.b_flags & B_WANTED) {
		bswlist.b_flags &= ~B_WANTED;
D 39
		thread_wakeup((int)&bswlist);
E 39
I 39
		wakeup(&bswlist);
E 39
	}
D 4
#if 0
	/*
	 * XXX: this isn't even close to the right thing to do,
	 * introduces a variety of race conditions.
	 *
	 * If dirty, vm_pageout() has attempted to clean the page
	 * again.  In this case we do not do anything as we will
	 * see the page again shortly.  Otherwise, if no error mark
	 * as clean and inform the pmap system.  If error, mark as
	 * dirty so we will try again (XXX: could get stuck doing
	 * this, should give up after awhile).
	 */
	if ((spc->spc_flags & SPC_DIRTY) == 0) {
		if (spc->spc_flags & SPC_ERROR) {
			printf("swap_pager: clean of %x (block %x) failed\n",
			       VM_PAGE_TO_PHYS(spc->spc_m), blk);
			spc->spc_m->laundry = TRUE;
		} else {
			spc->spc_m->clean = TRUE;
			pmap_clear_modify(VM_PAGE_TO_PHYS(spc->spc_m));
		}
	}
	/*
	 * XXX: allow blocked write faults to continue
	 */
	spc->spc_m->page_lock = spc->spc_m->unlock_request = VM_PROT_NONE;
	PAGE_WAKEUP(spc->spc_m);
#endif

E 4
D 32
	thread_wakeup((int) &vm_pages_needed);
E 32
I 32
D 39
	/*
	 * Only kick the pageout daemon if we are really hurting
	 * for pages, otherwise this page will be picked up later.
	 */
	if (cnt.v_free_count < cnt.v_free_min)
		thread_wakeup((int) &vm_pages_needed);
E 39
I 39
	wakeup(&vm_pages_needed);
E 39
E 32
	splx(s);
}
D 33
#endif
E 33
E 1
