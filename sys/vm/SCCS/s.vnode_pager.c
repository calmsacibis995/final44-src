h61717
s 00016/00013/00540
d D 8.10 95/05/14 00:37:21 mckusick 42 41
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00001/00002/00552
d D 8.9 94/11/21 15:37:33 mckusick 41 40
c check that thing being uncached is a regular file
e
s 00001/00000/00553
d D 8.8 94/02/13 14:19:41 bostic 40 39
c comment typo -- confidence that this has run plummets
e
s 00018/00011/00535
d D 8.7 94/02/13 10:51:21 hibler 39 38
c attempt to avoid races with file size changes
e
s 00003/00001/00543
d D 8.6 94/01/13 09:23:09 bostic 38 37
c lint
e
s 00102/00033/00442
d D 8.5 94/01/12 16:08:25 hibler 37 36
c use new multi-page interface,
c consistantly LOCK/UNLOCK vnodes.
e
s 00006/00008/00469
d D 8.4 93/12/30 16:01:33 mckusick 36 35
c convert to use new queue structures
e
s 00001/00001/00476
d D 8.3 93/11/14 13:54:44 hibler 35 34
c eliminate unneeded cast
e
s 00004/00002/00473
d D 8.2 93/11/10 10:58:31 torek 34 33
c finish up new device pager: all pagers get offsets
e
s 00002/00002/00473
d D 8.1 93/06/11 16:38:50 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00003/00475
d D 7.16 93/04/17 18:53:57 torek 32 31
c from pseudo-device to option
e
s 00001/00001/00477
d D 7.15 92/10/07 17:18:54 margo 31 30
c Add argument to VOP_BMAP.
e
s 00001/00001/00477
d D 7.14 92/10/01 17:53:34 mckusick 30 29
c convert vm_page bit fields to flags
e
s 00001/00001/00477
d D 7.13 92/09/21 21:44:33 hibler 29 28
c return VM_PAGER_ERROR not VM_PAGER_FAIL on IO errors
e
s 00001/00001/00477
d D 7.12 92/07/08 22:42:56 torek 28 27
c got to return *some* value, FALSE is probably right...
e
s 00000/00008/00478
d D 7.11 92/07/03 00:49:38 mckusick 27 26
c delete USES
e
s 00008/00000/00478
d D 7.10 92/05/14 17:24:35 heideman 26 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/14 16:58:25 heideman 25 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/14 16:40:56 heideman 24 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/14 16:30:53 heideman 23 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/14 15:47:35 heideman 22 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/14 15:36:59 heideman 21 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/14 14:43:09 heideman 20 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/14 12:45:27 heideman 19 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/14 11:42:30 heideman 18 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/14 10:23:27 heideman 17 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/13 23:01:12 heideman 16 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/13 18:49:49 heideman 15 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/13 18:21:31 heideman 14 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/13 18:11:09 heideman 13 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/13 17:55:46 heideman 12 10
c vnode interface conversion
e
s 00008/00000/00478
d R 7.10 92/05/13 17:54:22 heideman 11 10
c vnode interface conversion
e
s 00003/00003/00475
d D 7.9 92/05/13 15:04:36 mckusick 10 9
c exported routines cannot be static
e
s 00041/00016/00437
d D 7.8 92/05/04 17:16:35 bostic 9 8
c add function prototypes; new include format; define pagerops here; lint
e
s 00001/00001/00452
d D 7.7 91/12/14 21:13:19 mckusick 8 7
c statfs.f_bsize => statfs.f_iosize; statfs.f_fsize => statfs.f_bsize (for SunOS)
e
s 00001/00005/00452
d D 7.6 91/07/25 23:00:09 mckusick 7 6
c replace numerous includes with vm.h
e
s 00010/00010/00447
d D 7.5 91/04/20 13:00:50 karels 6 4
c fix includes; new proc struct; rm *_NULL
e
s 00001/00001/00456
d R 7.5 91/04/20 10:50:25 karels 5 4
c fix includes; new proc struct; rm *_NULL
e
s 00001/00001/00456
d D 7.4 91/04/19 17:15:58 mckusick 4 3
c lint
e
s 00008/00004/00449
d D 7.3 91/04/16 00:22:58 mckusick 3 2
c add proc pointers to appropriate VOP and uio setup operations
e
s 00015/00012/00438
d D 7.2 91/04/12 18:14:33 karels 2 1
c rm user.h, new proc structure, mv VTEXT'ing of vnode to exec;
c still need to fix credential use
e
s 00450/00000/00000
d D 7.1 90/12/05 18:13:45 mckusick 1 0
c adopted from Mike Hibler at Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 University of Utah.
D 33
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 33
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 40
/*
E 40
D 39
/*
E 39
 * Page to/from files (vnodes).
 *
 * TODO:
 *	pageouts
I 2
 *	fix credential use (uses current process credentials now)
E 2
 */
D 32
#include "vnodepager.h"
#if NVNODEPAGER > 0
E 32

D 9
#include "param.h"
D 2
#include "user.h"
E 2
I 2
#include "proc.h"
E 2
#include "malloc.h"
#include "vnode.h"
#include "uio.h"
#include "mount.h"
E 9
I 9
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/malloc.h>
#include <sys/vnode.h>
#include <sys/uio.h>
#include <sys/mount.h>
E 9
I 2

D 7
#include "vm_param.h"
#include "lock.h"
E 2
#include "queue.h"
I 2
#include "vm_prot.h"
#include "vm_object.h"
E 7
I 7
D 9
#include "vm.h"
E 7
#include "vm_page.h"
#include "vnode_pager.h"
E 9
I 9
#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vnode_pager.h>
E 9
E 2

D 2
#include "../vm/vm_param.h"
#include "../vm/vm_pager.h"
#include "../vm/vm_page.h"
#include "../vm/vnode_pager.h"

E 2
D 36
queue_head_t	vnode_pager_list;	/* list of managed vnodes */
E 36
I 36
struct pagerlst	vnode_pager_list;	/* list of managed vnodes */
E 36

#ifdef DEBUG
int	vpagerdebug = 0x00;
#define	VDB_FOLLOW	0x01
#define VDB_INIT	0x02
#define VDB_IO		0x04
#define VDB_FAIL	0x08
#define VDB_ALLOC	0x10
#define VDB_SIZE	0x20
#endif

D 9
void
E 9
I 9
D 34
static vm_pager_t	 vnode_pager_alloc __P((caddr_t, vm_size_t, vm_prot_t));
E 34
I 34
static vm_pager_t	 vnode_pager_alloc
			    __P((caddr_t, vm_size_t, vm_prot_t, vm_offset_t));
I 37
static void		 vnode_pager_cluster
			    __P((vm_pager_t, vm_offset_t,
				 vm_offset_t *, vm_offset_t *));
E 37
E 34
static void		 vnode_pager_dealloc __P((vm_pager_t));
static int		 vnode_pager_getpage
D 37
			    __P((vm_pager_t, vm_page_t, boolean_t));
E 37
I 37
			    __P((vm_pager_t, vm_page_t *, int, boolean_t));
E 37
static boolean_t	 vnode_pager_haspage __P((vm_pager_t, vm_offset_t));
static void		 vnode_pager_init __P((void));
static int		 vnode_pager_io
D 37
			    __P((vn_pager_t, vm_page_t, enum uio_rw));
E 37
I 37
			    __P((vn_pager_t, vm_page_t *, int,
				 boolean_t, enum uio_rw));
E 37
static boolean_t	 vnode_pager_putpage
D 37
			    __P((vm_pager_t, vm_page_t, boolean_t));
E 37
I 37
			    __P((vm_pager_t, vm_page_t *, int, boolean_t));
E 37

struct pagerops vnodepagerops = {
	vnode_pager_init,
	vnode_pager_alloc,
	vnode_pager_dealloc,
	vnode_pager_getpage,
	vnode_pager_putpage,
D 37
	vnode_pager_haspage
E 37
I 37
	vnode_pager_haspage,
	vnode_pager_cluster
E 37
};

static void
E 9
vnode_pager_init()
{
#ifdef DEBUG
	if (vpagerdebug & VDB_FOLLOW)
		printf("vnode_pager_init()\n");
#endif
D 36
	queue_init(&vnode_pager_list);
E 36
I 36
	TAILQ_INIT(&vnode_pager_list);
E 36
}

/*
 * Allocate (or lookup) pager for a vnode.
 * Handle is a vnode pointer.
 */
D 9
vm_pager_t
E 9
I 9
static vm_pager_t
E 9
D 34
vnode_pager_alloc(handle, size, prot)
E 34
I 34
vnode_pager_alloc(handle, size, prot, foff)
E 34
	caddr_t handle;
	vm_size_t size;
	vm_prot_t prot;
I 34
	vm_offset_t foff;
E 34
{
I 26
D 27
	USES_VOP_GETATTR;
E 27
E 26
	register vm_pager_t pager;
	register vn_pager_t vnp;
	vm_object_t object;
	struct vattr vattr;
	struct vnode *vp;
I 3
	struct proc *p = curproc;	/* XXX */
E 3

#ifdef DEBUG
	if (vpagerdebug & (VDB_FOLLOW|VDB_ALLOC))
		printf("vnode_pager_alloc(%x, %x, %x)\n", handle, size, prot);
#endif
	/*
	 * Pageout to vnode, no can do yet.
	 */
	if (handle == NULL)
D 6
		return(VM_PAGER_NULL);
E 6
I 6
		return(NULL);
E 6

	/*
	 * Vnodes keep a pointer to any associated pager so no need to
	 * lookup with vm_pager_lookup.
	 */
	vp = (struct vnode *)handle;
	pager = (vm_pager_t)vp->v_vmdata;
D 6
	if (pager == VM_PAGER_NULL) {
E 6
I 6
	if (pager == NULL) {
E 6
		/*
		 * Allocate pager structures
		 */
		pager = (vm_pager_t)malloc(sizeof *pager, M_VMPAGER, M_WAITOK);
D 6
		if (pager == VM_PAGER_NULL)
			return(VM_PAGER_NULL);
E 6
I 6
		if (pager == NULL)
			return(NULL);
E 6
		vnp = (vn_pager_t)malloc(sizeof *vnp, M_VMPGDATA, M_WAITOK);
D 6
		if (vnp == VN_PAGER_NULL) {
E 6
I 6
		if (vnp == NULL) {
E 6
			free((caddr_t)pager, M_VMPAGER);
D 6
			return(VM_PAGER_NULL);
E 6
I 6
			return(NULL);
E 6
		}
		/*
		 * And an object of the appropriate size
		 */
D 2
		if (VOP_GETATTR(vp, &vattr, u.u_cred) == 0) {
E 2
I 2
D 3
		if (VOP_GETATTR(vp, &vattr, curproc->p_ucred) == 0) {
E 3
I 3
		if (VOP_GETATTR(vp, &vattr, p->p_ucred, p) == 0) {
E 3
E 2
			object = vm_object_allocate(round_page(vattr.va_size));
			vm_object_enter(object, pager);
			vm_object_setpager(object, pager, 0, TRUE);
		} else {
			free((caddr_t)vnp, M_VMPGDATA);
			free((caddr_t)pager, M_VMPAGER);
D 6
			return(VM_PAGER_NULL);
E 6
I 6
			return(NULL);
E 6
		}
		/*
		 * Hold a reference to the vnode and initialize pager data.
		 */
		VREF(vp);
		vnp->vnp_flags = 0;
		vnp->vnp_vp = vp;
		vnp->vnp_size = vattr.va_size;
D 36
		queue_enter(&vnode_pager_list, pager, vm_pager_t, pg_list);
E 36
I 36
		TAILQ_INSERT_TAIL(&vnode_pager_list, pager, pg_list);
E 36
		pager->pg_handle = handle;
		pager->pg_type = PG_VNODE;
I 37
		pager->pg_flags = 0;
E 37
		pager->pg_ops = &vnodepagerops;
D 35
		pager->pg_data = (caddr_t)vnp;
E 35
I 35
		pager->pg_data = vnp;
E 35
		vp->v_vmdata = (caddr_t)pager;
	} else {
		/*
		 * vm_object_lookup() will remove the object from the
		 * cache if found and also gain a reference to the object.
		 */
		object = vm_object_lookup(pager);
I 2
#ifdef DEBUG
E 2
		vnp = (vn_pager_t)pager->pg_data;
I 2
#endif
E 2
	}
D 2
	if (prot & VM_PROT_EXECUTE)
		vp->v_flag |= VTEXT;		/* XXX */
E 2
#ifdef DEBUG
	if (vpagerdebug & VDB_ALLOC)
		printf("vnode_pager_setup: vp %x sz %x pager %x object %x\n",
		       vp, vnp->vnp_size, pager, object);
#endif
	return(pager);
}

D 9
void
E 9
I 9
static void
E 9
vnode_pager_dealloc(pager)
	vm_pager_t pager;
{
I 26
D 27
	USES_VOP_FSYNC;
E 27
E 26
	register vn_pager_t vnp = (vn_pager_t)pager->pg_data;
	register struct vnode *vp;
I 38
#ifdef NOTDEF
E 38
I 3
	struct proc *p = curproc;		/* XXX */
I 38
#endif
E 38
E 3

#ifdef DEBUG
	if (vpagerdebug & VDB_FOLLOW)
		printf("vnode_pager_dealloc(%x)\n", pager);
#endif
	if (vp = vnp->vnp_vp) {
		vp->v_vmdata = NULL;
		vp->v_flag &= ~VTEXT;
D 38
#if 0
E 38
I 38
#if NOTDEF
E 38
		/* can hang if done at reboot on NFS FS */
D 2
		(void) VOP_FSYNC(vp, u.u_cred);
E 2
I 2
D 3
		(void) VOP_FSYNC(vp, curproc->p_ucred);
E 3
I 3
		(void) VOP_FSYNC(vp, p->p_ucred, p);
E 3
E 2
#endif
		vrele(vp);
	}
D 36
	queue_remove(&vnode_pager_list, pager, vm_pager_t, pg_list);
E 36
I 36
	TAILQ_REMOVE(&vnode_pager_list, pager, pg_list);
E 36
	free((caddr_t)vnp, M_VMPGDATA);
	free((caddr_t)pager, M_VMPAGER);
}

I 9
static int
E 9
D 37
vnode_pager_getpage(pager, m, sync)
E 37
I 37
vnode_pager_getpage(pager, mlist, npages, sync)
E 37
	vm_pager_t pager;
D 37
	vm_page_t m;
E 37
I 37
	vm_page_t *mlist;
	int npages;
E 37
	boolean_t sync;
{

#ifdef DEBUG
	if (vpagerdebug & VDB_FOLLOW)
D 37
		printf("vnode_pager_getpage(%x, %x)\n", pager, m);
E 37
I 37
		printf("vnode_pager_getpage(%x, %x, %x, %x)\n",
		       pager, mlist, npages, sync);
E 37
#endif
D 37
	return(vnode_pager_io((vn_pager_t)pager->pg_data, m, UIO_READ));
E 37
I 37
	return(vnode_pager_io((vn_pager_t)pager->pg_data,
			      mlist, npages, sync, UIO_READ));
E 37
}

D 9
boolean_t
E 9
I 9
static boolean_t
E 9
D 37
vnode_pager_putpage(pager, m, sync)
E 37
I 37
vnode_pager_putpage(pager, mlist, npages, sync)
E 37
	vm_pager_t pager;
D 37
	vm_page_t m;
E 37
I 37
	vm_page_t *mlist;
	int npages;
E 37
	boolean_t sync;
{
	int err;

#ifdef DEBUG
	if (vpagerdebug & VDB_FOLLOW)
D 37
		printf("vnode_pager_putpage(%x, %x)\n", pager, m);
E 37
I 37
		printf("vnode_pager_putpage(%x, %x, %x, %x)\n",
		       pager, mlist, npages, sync);
E 37
#endif
D 6
	if (pager == VM_PAGER_NULL)
E 6
I 6
	if (pager == NULL)
E 6
D 28
		return;
E 28
I 28
		return (FALSE);			/* ??? */
E 28
D 37
	err = vnode_pager_io((vn_pager_t)pager->pg_data, m, UIO_WRITE);
E 37
I 37
	err = vnode_pager_io((vn_pager_t)pager->pg_data,
			     mlist, npages, sync, UIO_WRITE);
	/*
	 * If the operation was successful, mark the pages clean.
	 */
E 37
	if (err == VM_PAGER_OK) {
D 30
		m->clean = TRUE;			/* XXX - wrong place */
E 30
I 30
D 37
		m->flags |= PG_CLEAN;			/* XXX - wrong place */
E 30
		pmap_clear_modify(VM_PAGE_TO_PHYS(m));	/* XXX - wrong place */
E 37
I 37
		while (npages--) {
			(*mlist)->flags |= PG_CLEAN;
			pmap_clear_modify(VM_PAGE_TO_PHYS(*mlist));
			mlist++;
		}
E 37
	}
	return(err);
}

D 9
boolean_t
E 9
I 9
static boolean_t
E 9
vnode_pager_haspage(pager, offset)
	vm_pager_t pager;
	vm_offset_t offset;
{
I 26
D 27
	USES_VOP_BMAP;
E 27
E 26
D 42
	register vn_pager_t vnp = (vn_pager_t)pager->pg_data;
E 42
I 42
	struct proc *p = curproc;	/* XXX */
	vn_pager_t vnp = (vn_pager_t)pager->pg_data;
E 42
	daddr_t bn;
	int err;

#ifdef DEBUG
	if (vpagerdebug & VDB_FOLLOW)
		printf("vnode_pager_haspage(%x, %x)\n", pager, offset);
#endif

	/*
	 * Offset beyond end of file, do not have the page
I 39
	 * Lock the vnode first to make sure we have the most recent
	 * version of the size.
E 39
	 */
I 39
D 42
	VOP_LOCK(vnp->vnp_vp);
E 42
I 42
	vn_lock(vnp->vnp_vp, LK_EXCLUSIVE | LK_RETRY, p);
E 42
E 39
	if (offset >= vnp->vnp_size) {
I 39
D 42
		VOP_UNLOCK(vnp->vnp_vp);
E 42
I 42
		VOP_UNLOCK(vnp->vnp_vp, 0, p);
E 42
E 39
#ifdef DEBUG
		if (vpagerdebug & (VDB_FAIL|VDB_SIZE))
			printf("vnode_pager_haspage: pg %x, off %x, size %x\n",
			       pager, offset, vnp->vnp_size);
#endif
		return(FALSE);
	}

	/*
	 * Read the index to find the disk block to read
	 * from.  If there is no block, report that we don't
	 * have this data.
	 *
	 * Assumes that the vnode has whole page or nothing.
	 */
I 37
D 39
	VOP_LOCK(vnp->vnp_vp);
E 39
E 37
	err = VOP_BMAP(vnp->vnp_vp,
D 8
		       offset / vnp->vnp_vp->v_mount->mnt_stat.f_bsize,
E 8
I 8
		       offset / vnp->vnp_vp->v_mount->mnt_stat.f_iosize,
E 8
D 4
		       (struct vnode *)0, &bn);
E 4
I 4
D 31
		       (struct vnode **)0, &bn);
E 31
I 31
		       (struct vnode **)0, &bn, NULL);
I 37
D 42
	VOP_UNLOCK(vnp->vnp_vp);
E 42
I 42
	VOP_UNLOCK(vnp->vnp_vp, 0, p);
E 42
E 37
E 31
E 4
	if (err) {
#ifdef DEBUG
		if (vpagerdebug & VDB_FAIL)
			printf("vnode_pager_haspage: BMAP err %d, pg %x, off %x\n",
			       err, pager, offset);
#endif
		return(TRUE);
	}
	return((long)bn < 0 ? FALSE : TRUE);
}

I 37
static void
vnode_pager_cluster(pager, offset, loffset, hoffset)
	vm_pager_t	pager;
	vm_offset_t	offset;
	vm_offset_t	*loffset;
	vm_offset_t	*hoffset;
{
	vn_pager_t vnp = (vn_pager_t)pager->pg_data;
	vm_offset_t loff, hoff;

#ifdef DEBUG
	if (vpagerdebug & VDB_FOLLOW)
		printf("vnode_pager_cluster(%x, %x) ", pager, offset);
#endif
	loff = offset;
	if (loff >= vnp->vnp_size)
		panic("vnode_pager_cluster: bad offset");
	/*
	 * XXX could use VOP_BMAP to get maxcontig value
	 */
	hoff = loff + MAXBSIZE;
	if (hoff > round_page(vnp->vnp_size))
		hoff = round_page(vnp->vnp_size);

	*loffset = loff;
	*hoffset = hoff;
#ifdef DEBUG
	if (vpagerdebug & VDB_FOLLOW)
		printf("returns [%x-%x]\n", loff, hoff);
#endif
}

E 37
/*
 * (XXX)
 * Lets the VM system know about a change in size for a file.
 * If this vnode is mapped into some address space (i.e. we have a pager
 * for it) we adjust our own internal size and flush any cached pages in
 * the associated object that are affected by the size change.
 *
 * Note: this routine may be invoked as a result of a pager put
 * operation (possibly at object termination time), so we must be careful.
 */
I 9
D 10
static void
E 10
I 10
void
E 10
E 9
vnode_pager_setsize(vp, nsize)
	struct vnode *vp;
	u_long nsize;
{
	register vn_pager_t vnp;
	register vm_object_t object;
	vm_pager_t pager;

	/*
	 * Not a mapped vnode
	 */
	if (vp == NULL || vp->v_type != VREG || vp->v_vmdata == NULL)
		return;
	/*
	 * Hasn't changed size
	 */
	pager = (vm_pager_t)vp->v_vmdata;
	vnp = (vn_pager_t)pager->pg_data;
	if (nsize == vnp->vnp_size)
		return;
	/*
	 * No object.
	 * This can happen during object termination since
	 * vm_object_page_clean is called after the object
	 * has been removed from the hash table, and clean
	 * may cause vnode write operations which can wind
	 * up back here.
	 */
	object = vm_object_lookup(pager);
D 6
	if (object == VM_OBJECT_NULL)
E 6
I 6
	if (object == NULL)
E 6
		return;

#ifdef DEBUG
	if (vpagerdebug & (VDB_FOLLOW|VDB_SIZE))
		printf("vnode_pager_setsize: vp %x obj %x osz %d nsz %d\n",
		       vp, object, vnp->vnp_size, nsize);
#endif
	/*
	 * File has shrunk.
	 * Toss any cached pages beyond the new EOF.
	 */
	if (nsize < vnp->vnp_size) {
		vm_object_lock(object);
		vm_object_page_remove(object,
				      (vm_offset_t)nsize, vnp->vnp_size);
		vm_object_unlock(object);
	}
	vnp->vnp_size = (vm_offset_t)nsize;
	vm_object_deallocate(object);
}

I 9
D 10
static void
E 10
I 10
void
E 10
E 9
vnode_pager_umount(mp)
	register struct mount *mp;
{
D 42
	register vm_pager_t pager, npager;
E 42
I 42
	struct proc *p = curproc;	/* XXX */
	vm_pager_t pager, npager;
E 42
	struct vnode *vp;

D 36
	pager = (vm_pager_t) queue_first(&vnode_pager_list);
	while (!queue_end(&vnode_pager_list, (queue_entry_t)pager)) {
E 36
I 36
	for (pager = vnode_pager_list.tqh_first; pager != NULL; pager = npager){
E 36
		/*
		 * Save the next pointer now since uncaching may
		 * terminate the object and render pager invalid
		 */
I 36
		npager = pager->pg_list.tqe_next;
E 36
		vp = ((vn_pager_t)pager->pg_data)->vnp_vp;
D 36
		npager = (vm_pager_t) queue_next(&pager->pg_list);
E 36
D 37
		if (mp == (struct mount *)0 || vp->v_mount == mp)
E 37
I 37
		if (mp == (struct mount *)0 || vp->v_mount == mp) {
D 42
			VOP_LOCK(vp);
E 42
I 42
			vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 42
E 37
			(void) vnode_pager_uncache(vp);
I 37
D 42
			VOP_UNLOCK(vp);
E 42
I 42
			VOP_UNLOCK(vp, 0, p);
E 42
		}
E 37
D 36
		pager = npager;
E 36
	}
}

/*
 * Remove vnode associated object from the object cache.
 *
D 37
 * Note: this routine may be invoked as a result of a pager put
 * operation (possibly at object termination time), so we must be careful.
E 37
I 37
 * XXX unlock the vnode if it is currently locked.
 * We must do this since uncaching the object may result in its
 * destruction which may initiate paging activity which may necessitate
 * re-locking the vnode.
E 37
 */
D 9
boolean_t
E 9
I 9
D 10
static boolean_t
E 10
I 10
boolean_t
E 10
E 9
vnode_pager_uncache(vp)
	register struct vnode *vp;
{
I 26
D 27
	USES_VOP_ISLOCKED;
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 27
E 26
D 42
	register vm_object_t object;
E 42
I 42
	struct proc *p = curproc;	/* XXX */
	vm_object_t object;
E 42
D 37
	boolean_t uncached, locked;
E 37
I 37
	boolean_t uncached;
E 37
	vm_pager_t pager;

	/*
	 * Not a mapped vnode
	 */
D 41
	pager = (vm_pager_t)vp->v_vmdata;
D 6
	if (pager == vm_pager_null)
E 6
I 6
	if (pager == NULL)
E 41
I 41
	if (vp->v_type != VREG || (pager = (vm_pager_t)vp->v_vmdata) == NULL)
E 41
E 6
		return (TRUE);
I 37
#ifdef DEBUG
	if (!VOP_ISLOCKED(vp)) {
		extern int (**nfsv2_vnodeop_p)();

		if (vp->v_op != nfsv2_vnodeop_p)
			panic("vnode_pager_uncache: vnode not locked!");
	}
#endif
E 37
	/*
D 37
	 * Unlock the vnode if it is currently locked.
	 * We do this since uncaching the object may result
	 * in its destruction which may initiate paging
	 * activity which may necessitate locking the vnode.
	 */
	locked = VOP_ISLOCKED(vp);
	if (locked)
		VOP_UNLOCK(vp);
	/*
E 37
	 * Must use vm_object_lookup() as it actually removes
	 * the object from the cache list.
	 */
	object = vm_object_lookup(pager);
	if (object) {
		uncached = (object->ref_count <= 1);
I 37
D 42
		VOP_UNLOCK(vp);
E 42
I 42
		VOP_UNLOCK(vp, 0, p);
E 42
E 37
		pager_cache(object, FALSE);
I 37
D 42
		VOP_LOCK(vp);
E 42
I 42
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 42
E 37
	} else
		uncached = TRUE;
D 37
	if (locked)
		VOP_LOCK(vp);
E 37
	return(uncached);
}

I 9
static int
E 9
D 37
vnode_pager_io(vnp, m, rw)
E 37
I 37
vnode_pager_io(vnp, mlist, npages, sync, rw)
E 37
	register vn_pager_t vnp;
D 37
	vm_page_t m;
E 37
I 37
	vm_page_t *mlist;
	int npages;
	boolean_t sync;
E 37
	enum uio_rw rw;
{
I 26
D 27
	USES_VOP_READ;
	USES_VOP_WRITE;
E 27
E 26
	struct uio auio;
	struct iovec aiov;
	vm_offset_t kva, foff;
	int error, size;
I 3
	struct proc *p = curproc;		/* XXX */
E 3

I 37
	/* XXX */
	vm_page_t m;
	if (npages != 1)
		panic("vnode_pager_io: cannot handle multiple pages");
	m = *mlist;
	/* XXX */

E 37
#ifdef DEBUG
	if (vpagerdebug & VDB_FOLLOW)
		printf("vnode_pager_io(%x, %x, %c): vnode %x\n",
		       vnp, m, rw == UIO_READ ? 'R' : 'W', vnp->vnp_vp);
#endif
	foff = m->offset + m->object->paging_offset;
	/*
D 39
	 * Return failure if beyond current EOF
E 39
I 39
	 * Allocate a kernel virtual address and initialize so that
	 * we can use VOP_READ/WRITE routines.
E 39
	 */
I 39
	kva = vm_pager_map_pages(mlist, npages, sync);
	if (kva == NULL)
		return(VM_PAGER_AGAIN);
	/*
	 * After all of the potentially blocking operations have been
	 * performed, we can do the size checks:
	 *	read beyond EOF (returns error)
	 *	short read
	 */
D 42
	VOP_LOCK(vnp->vnp_vp);
E 42
I 42
	vn_lock(vnp->vnp_vp, LK_EXCLUSIVE | LK_RETRY, p);
E 42
E 39
	if (foff >= vnp->vnp_size) {
I 39
D 42
		VOP_UNLOCK(vnp->vnp_vp);
E 42
I 42
		VOP_UNLOCK(vnp->vnp_vp, 0, p);
E 42
		vm_pager_unmap_pages(kva, npages);
E 39
#ifdef DEBUG
		if (vpagerdebug & VDB_SIZE)
			printf("vnode_pager_io: vp %x, off %d size %d\n",
			       vnp->vnp_vp, foff, vnp->vnp_size);
#endif
		return(VM_PAGER_BAD);
	}
	if (foff + PAGE_SIZE > vnp->vnp_size)
		size = vnp->vnp_size - foff;
	else
		size = PAGE_SIZE;
D 39
	/*
	 * Allocate a kernel virtual address and initialize so that
	 * we can use VOP_READ/WRITE routines.
	 */
D 37
	kva = vm_pager_map_page(m);
E 37
I 37
	kva = vm_pager_map_pages(mlist, npages, sync);
	if (kva == NULL)
		return(VM_PAGER_AGAIN);
E 39
E 37
	aiov.iov_base = (caddr_t)kva;
	aiov.iov_len = size;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = foff;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_rw = rw;
	auio.uio_resid = size;
I 3
	auio.uio_procp = (struct proc *)0;
E 3
#ifdef DEBUG
	if (vpagerdebug & VDB_IO)
		printf("vnode_pager_io: vp %x kva %x foff %x size %x",
		       vnp->vnp_vp, kva, foff, size);
#endif
I 37
D 39
	VOP_LOCK(vnp->vnp_vp);
E 39
E 37
	if (rw == UIO_READ)
D 2
		error = VOP_READ(vnp->vnp_vp, &auio, 0, u.u_cred);
E 2
I 2
D 3
		error = VOP_READ(vnp->vnp_vp, &auio, 0, curproc->p_ucred);
E 3
I 3
		error = VOP_READ(vnp->vnp_vp, &auio, 0, p->p_ucred);
E 3
E 2
	else
D 2
		error = VOP_WRITE(vnp->vnp_vp, &auio, 0, u.u_cred);
E 2
I 2
D 3
		error = VOP_WRITE(vnp->vnp_vp, &auio, 0, curproc->p_ucred);
E 3
I 3
		error = VOP_WRITE(vnp->vnp_vp, &auio, 0, p->p_ucred);
I 37
D 42
	VOP_UNLOCK(vnp->vnp_vp);
E 42
I 42
	VOP_UNLOCK(vnp->vnp_vp, 0, p);
E 42
E 37
E 3
E 2
#ifdef DEBUG
	if (vpagerdebug & VDB_IO) {
		if (error || auio.uio_resid)
			printf(" returns error %x, resid %x",
			       error, auio.uio_resid);
		printf("\n");
	}
#endif
	if (!error) {
		register int count = size - auio.uio_resid;

		if (count == 0)
			error = EINVAL;
		else if (count != PAGE_SIZE && rw == UIO_READ)
D 9
			bzero(kva + count, PAGE_SIZE - count);
E 9
I 9
			bzero((void *)(kva + count), PAGE_SIZE - count);
E 9
	}
D 37
	vm_pager_unmap_page(kva);
E 37
I 37
	vm_pager_unmap_pages(kva, npages);
E 37
D 29
	return (error ? VM_PAGER_FAIL : VM_PAGER_OK);
E 29
I 29
	return (error ? VM_PAGER_ERROR : VM_PAGER_OK);
E 29
}
D 32
#endif
E 32
E 1
