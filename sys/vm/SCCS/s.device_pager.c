h23840
s 00020/00009/00322
d D 8.5 94/01/12 15:45:32 hibler 13 12
c reflect new multi-page interface.
e
s 00016/00015/00315
d D 8.4 93/12/30 16:01:35 mckusick 12 11
c convert to use new queue structures
e
s 00001/00001/00329
d D 8.3 93/11/21 10:27:57 hibler 11 10
c vm_page_insert should be done with paging queues locked (torek)
e
s 00151/00068/00179
d D 8.2 93/10/24 12:59:08 hibler 10 9
c new improved version: dynamic allocation of fake pages
e
s 00002/00002/00245
d D 8.1 93/06/11 16:36:40 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00247
d D 7.8 93/04/17 18:53:58 torek 8 7
c from pseudo-device to option
e
s 00001/00001/00250
d D 7.7 92/10/01 17:54:27 mckusick 7 6
c convert vm_page bit fields to flags
e
s 00033/00012/00218
d D 7.6 92/05/04 17:13:10 bostic 6 5
c add function prototypes; new include format; define pagerops here
e
s 00001/00001/00229
d D 7.5 92/02/19 19:10:59 mckusick 5 4
c lint
e
s 00001/00001/00229
d D 7.4 92/02/19 18:08:03 torek 4 3
c replace vm_page_init with VM_PAGE_INIT macro
e
s 00005/00008/00225
d D 7.3 91/08/16 17:45:58 mckusick 3 2
c move up debugging output to place where it is valid
e
s 00014/00018/00219
d D 7.2 91/04/20 10:50:02 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00237/00000/00000
d D 7.1 90/12/05 18:13:19 mckusick 1 0
c adopted from Mike Hibler at Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 University of Utah.
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Page to/from special files.
 */

D 8
#include "devpager.h"
#if NDEVPAGER > 0

E 8
D 6
#include "param.h"
D 2
#include "queue.h"
E 2
#include "conf.h"
#include "mman.h"
#include "malloc.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/mman.h>
#include <sys/malloc.h>
E 6
D 2
#include "uio.h"
E 2

D 2
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_pager.h"
#include "../vm/vm_page.h"
#include "../vm/vm_kern.h"
#include "../vm/device_pager.h"
E 2
I 2
D 6
#include "vm.h"
#include "vm_page.h"
#include "vm_kern.h"
#include "device_pager.h"
E 6
I 6
#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
#include <vm/device_pager.h>
E 6
E 2

D 10
queue_head_t	dev_pager_list;	/* list of managed devices */
E 10
I 10
D 12
queue_head_t	dev_pager_list;		/* list of managed devices */
queue_head_t	dev_pager_fakelist;	/* list of available vm_page_t's */
E 12
I 12
struct pagerlst	dev_pager_list;		/* list of managed devices */
struct pglist	dev_pager_fakelist;	/* list of available vm_page_t's */
E 12
E 10

#ifdef DEBUG
int	dpagerdebug = 0;
#define	DDB_FOLLOW	0x01
#define DDB_INIT	0x02
#define DDB_ALLOC	0x04
#define DDB_FAIL	0x08
#endif

D 6
void
E 6
I 6
D 10
static vm_pager_t	 dev_pager_alloc __P((caddr_t, vm_size_t, vm_prot_t));
E 10
I 10
static vm_pager_t	 dev_pager_alloc
			    __P((caddr_t, vm_size_t, vm_prot_t, vm_offset_t));
E 10
static void		 dev_pager_dealloc __P((vm_pager_t));
static int		 dev_pager_getpage
D 13
			    __P((vm_pager_t, vm_page_t, boolean_t));
E 13
I 13
			    __P((vm_pager_t, vm_page_t *, int, boolean_t));
E 13
static boolean_t	 dev_pager_haspage __P((vm_pager_t, vm_offset_t));
static void		 dev_pager_init __P((void));
static int		 dev_pager_putpage
D 13
			    __P((vm_pager_t, vm_page_t, boolean_t));
E 13
I 13
			    __P((vm_pager_t, vm_page_t *, int, boolean_t));
E 13
I 10
static vm_page_t	 dev_pager_getfake __P((vm_offset_t));
static void		 dev_pager_putfake __P((vm_page_t));
E 10

struct pagerops devicepagerops = {
	dev_pager_init,
	dev_pager_alloc,
	dev_pager_dealloc,
	dev_pager_getpage,
	dev_pager_putpage,
D 13
	dev_pager_haspage
E 13
I 13
	dev_pager_haspage,
	vm_pager_clusternull
E 13
};

static void
E 6
dev_pager_init()
{
#ifdef DEBUG
	if (dpagerdebug & DDB_FOLLOW)
		printf("dev_pager_init()\n");
#endif
D 12
	queue_init(&dev_pager_list);
I 10
	queue_init(&dev_pager_fakelist);
E 12
I 12
	TAILQ_INIT(&dev_pager_list);
	TAILQ_INIT(&dev_pager_fakelist);
E 12
E 10
}

D 6
vm_pager_t
E 6
I 6
static vm_pager_t
E 6
D 10
dev_pager_alloc(handle, size, prot)
E 10
I 10
dev_pager_alloc(handle, size, prot, foff)
E 10
	caddr_t handle;
	vm_size_t size;
	vm_prot_t prot;
I 10
	vm_offset_t foff;
E 10
{
	dev_t dev;
	vm_pager_t pager;
D 10
	int (*mapfunc)(), nprot;
	register vm_object_t object;
	register vm_page_t page;
	register dev_pager_t devp;
	register int npages, off;
D 2
	extern int nulldev(), nodev();
E 2
I 2
	extern int nullop(), enodev();
E 10
I 10
	int (*mapfunc)();
	vm_object_t object;
	dev_pager_t devp;
	int npages, off;
E 10
E 2

D 10

E 10
#ifdef DEBUG
	if (dpagerdebug & DDB_FOLLOW)
D 10
		printf("dev_pager_alloc(%x, %x, %x)\n", handle, size, prot);
E 10
I 10
		printf("dev_pager_alloc(%x, %x, %x, %x)\n",
		       handle, size, prot, foff);
E 10
#endif
I 10
#ifdef DIAGNOSTIC
E 10
	/*
	 * Pageout to device, should never happen.
	 */
	if (handle == NULL)
		panic("dev_pager_alloc called");
I 10
#endif
E 10

	/*
D 10
	 * Look it up, creating as necessary
E 10
I 10
	 * Make sure this device can be mapped.
E 10
	 */
I 10
	dev = (dev_t)handle;
	mapfunc = cdevsw[major(dev)].d_mmap;
	if (mapfunc == NULL || mapfunc == enodev || mapfunc == nullop)
		return(NULL);

	/*
	 * Offset should be page aligned.
	 */
	if (foff & PAGE_MASK)
		return(NULL);

	/*
	 * Check that the specified range of the device allows the
	 * desired protection.
	 *
	 * XXX assumes VM_PROT_* == PROT_*
	 */
	npages = atop(round_page(size));
	for (off = foff; npages--; off += PAGE_SIZE)
		if ((*mapfunc)(dev, off, (int)prot) == -1)
			return(NULL);

	/*
	 * Look up pager, creating as necessary.
	 */
top:
E 10
	pager = vm_pager_lookup(&dev_pager_list, handle);
D 2
	if (pager == VM_PAGER_NULL) {
E 2
I 2
	if (pager == NULL) {
E 2
		/*
D 10
		 * Validation.  Make sure this device can be mapped
		 * and that range to map is acceptible to device.
		 */
		dev = (dev_t)handle;
		mapfunc = cdevsw[major(dev)].d_mmap;
D 2
		if (!mapfunc || mapfunc == nodev || mapfunc == nulldev)
			return(VM_PAGER_NULL);
E 2
I 2
		if (!mapfunc || mapfunc == enodev || mapfunc == nullop)
			return(NULL);
E 2
		nprot = 0;
		if (prot & VM_PROT_READ)
			nprot |= PROT_READ;
		if (prot & VM_PROT_WRITE)
			nprot |= PROT_WRITE;
		if (prot & VM_PROT_EXECUTE)
			nprot |= PROT_EXEC;
		npages = atop(round_page(size));
		for (off = 0; npages--; off += PAGE_SIZE)
			if ((*mapfunc)(dev, off, nprot) == -1)
D 2
				return(VM_PAGER_NULL);
E 2
I 2
				return(NULL);
E 2
		/*
E 10
		 * Allocate and initialize pager structs
		 */
		pager = (vm_pager_t)malloc(sizeof *pager, M_VMPAGER, M_WAITOK);
D 2
		if (pager == VM_PAGER_NULL)
			return(VM_PAGER_NULL);
E 2
I 2
		if (pager == NULL)
			return(NULL);
E 2
		devp = (dev_pager_t)malloc(sizeof *devp, M_VMPGDATA, M_WAITOK);
D 2
		if (devp == DEV_PAGER_NULL) {
E 2
I 2
		if (devp == NULL) {
E 2
			free((caddr_t)pager, M_VMPAGER);
D 2
			return(VM_PAGER_NULL);
E 2
I 2
			return(NULL);
E 2
		}
D 10
		devp->devp_dev = dev;
		devp->devp_npages = atop(round_page(size));
E 10
		pager->pg_handle = handle;
		pager->pg_ops = &devicepagerops;
		pager->pg_type = PG_DEVICE;
I 13
		pager->pg_flags = 0;
E 13
D 10
		pager->pg_data = (caddr_t)devp;
E 10
I 10
		pager->pg_data = devp;
D 12
		queue_init(&devp->devp_pglist);
E 12
I 12
		TAILQ_INIT(&devp->devp_pglist);
E 12
E 10
		/*
D 10
		 * Allocate object and vm_page structures to describe memory
E 10
I 10
		 * Allocate object and associate it with the pager.
E 10
		 */
D 10
		npages = devp->devp_npages;
		object = devp->devp_object = vm_object_allocate(ptoa(npages));
E 10
I 10
		object = devp->devp_object = vm_object_allocate(0);
E 10
		vm_object_enter(object, pager);
		vm_object_setpager(object, pager, (vm_offset_t)0, FALSE);
D 10
		devp->devp_pages = (vm_page_t)
			kmem_alloc(kernel_map, npages*sizeof(struct vm_page));
		off = 0;
		for (page = devp->devp_pages;
		     page < &devp->devp_pages[npages]; page++) {
			vm_object_lock(object);
D 4
			vm_page_init(page, object, off);
E 4
I 4
			VM_PAGE_INIT(page, object, off);
E 4
			page->phys_addr =
				pmap_phys_address((*mapfunc)(dev, off, nprot));
			page->wire_count = 1;
D 7
			page->fictitious = TRUE;
E 7
I 7
			page->flags |= PG_FICTITIOUS;
E 7
			PAGE_WAKEUP(page);
			vm_object_unlock(object);
			off += PAGE_SIZE;
		}
E 10
		/*
		 * Finally, put it on the managed list so other can find it.
I 10
		 * First we re-lookup in case someone else beat us to this
		 * point (due to blocking in the various mallocs).  If so,
		 * we free everything and start over.
E 10
		 */
D 10
		queue_enter(&dev_pager_list, devp, dev_pager_t, devp_list);
E 10
I 10
		if (vm_pager_lookup(&dev_pager_list, handle)) {
			free((caddr_t)devp, M_VMPGDATA);
			free((caddr_t)pager, M_VMPAGER);
			goto top;
		}
D 12
		queue_enter(&dev_pager_list, pager, vm_pager_t, pg_list);
E 12
I 12
		TAILQ_INSERT_TAIL(&dev_pager_list, pager, pg_list);
E 12
E 10
#ifdef DEBUG
D 3
		if (dpagerdebug & DDB_ALLOC)
E 3
I 3
		if (dpagerdebug & DDB_ALLOC) {
E 3
D 10
			printf("dev_pager_alloc: pages %d@%x\n",
			       devp->devp_npages, devp->devp_pages);
E 10
I 3
			printf("dev_pager_alloc: pager %x devp %x object %x\n",
			       pager, devp, object);
			vm_object_print(object, FALSE);
		}
E 3
#endif
	} else {
		/*
		 * vm_object_lookup() gains a reference and also
		 * removes the object from the cache.
		 */
I 10
		object = vm_object_lookup(pager);
#ifdef DIAGNOSTIC
E 10
		devp = (dev_pager_t)pager->pg_data;
D 10
		if (vm_object_lookup(pager) != devp->devp_object)
E 10
I 10
		if (object != devp->devp_object)
E 10
			panic("dev_pager_setup: bad object");
I 10
#endif
E 10
	}
D 3
#ifdef DEBUG
	if (dpagerdebug & DDB_ALLOC) {
		printf("dev_pager_alloc: pager %x devp %x object %x\n",
		       pager, devp, object);
		vm_object_print(object, FALSE);
	}
#endif
E 3
	return(pager);
D 10

E 10
}

D 6
void
E 6
I 6
static void
E 6
dev_pager_dealloc(pager)
	vm_pager_t pager;
{
D 10
	dev_pager_t devp = (dev_pager_t)pager->pg_data;
	register vm_object_t object;
E 10
I 10
	dev_pager_t devp;
	vm_object_t object;
	vm_page_t m;
E 10

#ifdef DEBUG
	if (dpagerdebug & DDB_FOLLOW)
		printf("dev_pager_dealloc(%x)\n", pager);
#endif
D 10
	queue_remove(&dev_pager_list, devp, dev_pager_t, devp_list);
E 10
I 10
D 12
	queue_remove(&dev_pager_list, pager, vm_pager_t, pg_list);
E 12
I 12
	TAILQ_REMOVE(&dev_pager_list, pager, pg_list);
E 12
	/*
	 * Get the object.
	 * Note: cannot use vm_object_lookup since object has already
	 * been removed from the hash chain.
	 */
	devp = (dev_pager_t)pager->pg_data;
E 10
	object = devp->devp_object;
#ifdef DEBUG
	if (dpagerdebug & DDB_ALLOC)
D 10
		printf("dev_pager_dealloc: devp %x object %x pages %d@%x\n",
		       devp, object, devp->devp_npages, devp->devp_pages);
E 10
I 10
		printf("dev_pager_dealloc: devp %x object %x\n", devp, object);
E 10
#endif
D 10
	while (!queue_empty(&object->memq))
		vm_page_remove((vm_page_t)queue_first(&object->memq));
D 5
	kmem_free(kernel_map, devp->devp_pages,
E 5
I 5
	kmem_free(kernel_map, (vm_offset_t)devp->devp_pages,
E 5
		  devp->devp_npages * sizeof(struct vm_page));
E 10
I 10
	/*
	 * Free up our fake pages.
	 */
D 12
	while (!queue_empty(&devp->devp_pglist)) {
		queue_remove_first(&devp->devp_pglist, m, vm_page_t, pageq);
E 12
I 12
	while ((m = devp->devp_pglist.tqh_first) != NULL) {
		TAILQ_REMOVE(&devp->devp_pglist, m, pageq);
E 12
		dev_pager_putfake(m);
	}
E 10
	free((caddr_t)devp, M_VMPGDATA);
D 10
	pager->pg_data = 0;
E 10
I 10
	free((caddr_t)pager, M_VMPAGER);
E 10
}

I 6
static int
E 6
D 13
dev_pager_getpage(pager, m, sync)
E 13
I 13
dev_pager_getpage(pager, mlist, npages, sync)
E 13
	vm_pager_t pager;
D 13
	vm_page_t m;
E 13
I 13
	vm_page_t *mlist;
	int npages;
E 13
	boolean_t sync;
{
I 10
	register vm_object_t object;
	vm_offset_t offset, paddr;
	vm_page_t page;
	dev_t dev;
	int (*mapfunc)(), prot;
I 13
	vm_page_t m;
E 13

E 10
#ifdef DEBUG
	if (dpagerdebug & DDB_FOLLOW)
D 13
		printf("dev_pager_getpage(%x, %x)\n", pager, m);
E 13
I 13
		printf("dev_pager_getpage(%x, %x, %x, %x)\n",
		       pager, mlist, npages, sync);
E 13
#endif
D 10
	return(VM_PAGER_BAD);
E 10
I 10

I 13
	if (npages != 1)
		panic("dev_pager_getpage: cannot handle multiple pages");
	m = *mlist;

E 13
	object = m->object;
	dev = (dev_t)pager->pg_handle;
	offset = m->offset + object->paging_offset;
	prot = PROT_READ;	/* XXX should pass in? */
	mapfunc = cdevsw[major(dev)].d_mmap;
#ifdef DIAGNOSTIC
	if (mapfunc == NULL || mapfunc == enodev || mapfunc == nullop)
		panic("dev_pager_getpage: no map function");
#endif
	paddr = pmap_phys_address((*mapfunc)(dev, (int)offset, prot));
#ifdef DIAGNOSTIC
	if (paddr == -1)
		panic("dev_pager_getpage: map function returns error");
#endif
	/*
	 * Replace the passed in page with our own fake page and free
	 * up the original.
	 */
	page = dev_pager_getfake(paddr);
D 12
	queue_enter(&((dev_pager_t)pager->pg_data)->devp_pglist,
		    page, vm_page_t, pageq);
E 12
I 12
	TAILQ_INSERT_TAIL(&((dev_pager_t)pager->pg_data)->devp_pglist, page,
	    pageq);
E 12
	vm_object_lock(object);
	vm_page_lock_queues();
	vm_page_free(m);
D 11
	vm_page_unlock_queues();
E 11
	vm_page_insert(page, object, offset);
I 11
	vm_page_unlock_queues();
E 11
	PAGE_WAKEUP(m);
	if (offset + PAGE_SIZE > object->size)
		object->size = offset + PAGE_SIZE;	/* XXX anal */
	vm_object_unlock(object);

	return(VM_PAGER_OK);
E 10
}

I 6
static int
E 6
D 13
dev_pager_putpage(pager, m, sync)
E 13
I 13
dev_pager_putpage(pager, mlist, npages, sync)
E 13
	vm_pager_t pager;
D 13
	vm_page_t m;
E 13
I 13
	vm_page_t *mlist;
	int npages;
E 13
	boolean_t sync;
{
#ifdef DEBUG
	if (dpagerdebug & DDB_FOLLOW)
D 13
		printf("dev_pager_putpage(%x, %x)\n", pager, m);
E 13
I 13
		printf("dev_pager_putpage(%x, %x, %x, %x)\n",
		       pager, mlist, npages, sync);
E 13
#endif
D 2
	if (pager == VM_PAGER_NULL)
E 2
I 2
	if (pager == NULL)
E 2
		return;
	panic("dev_pager_putpage called");
}

D 6
boolean_t
E 6
I 6
static boolean_t
E 6
dev_pager_haspage(pager, offset)
	vm_pager_t pager;
	vm_offset_t offset;
{
#ifdef DEBUG
	if (dpagerdebug & DDB_FOLLOW)
		printf("dev_pager_haspage(%x, %x)\n", pager, offset);
#endif
	return(TRUE);
I 10
}

static vm_page_t
dev_pager_getfake(paddr)
	vm_offset_t paddr;
{
	vm_page_t m;
	int i;

D 12
	if (queue_empty(&dev_pager_fakelist)) {
E 12
I 12
	if (dev_pager_fakelist.tqh_first == NULL) {
E 12
		m = (vm_page_t)malloc(PAGE_SIZE, M_VMPGDATA, M_WAITOK);
		for (i = PAGE_SIZE / sizeof(*m); i > 0; i--) {
D 12
			queue_enter(&dev_pager_fakelist, m, vm_page_t, pageq);
E 12
I 12
			TAILQ_INSERT_TAIL(&dev_pager_fakelist, m, pageq);
E 12
			m++;
		}
	}
D 12
	queue_remove_first(&dev_pager_fakelist, m, vm_page_t, pageq);
E 12
I 12
	m = dev_pager_fakelist.tqh_first;
	TAILQ_REMOVE(&dev_pager_fakelist, m, pageq);
E 12
	m->flags = PG_BUSY | PG_CLEAN | PG_FAKE | PG_FICTITIOUS;
	m->phys_addr = paddr;
	m->wire_count = 1;
	return(m);
}

static void
dev_pager_putfake(m)
	vm_page_t m;
{
#ifdef DIAGNOSTIC
	if (!(m->flags & PG_FICTITIOUS))
		panic("dev_pager_putfake: bad page");
#endif
D 12
	queue_enter(&dev_pager_fakelist, m, vm_page_t, pageq);
E 12
I 12
	TAILQ_INSERT_TAIL(&dev_pager_fakelist, m, pageq);
E 12
E 10
}
D 8
#endif
E 8
E 1
