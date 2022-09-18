/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mfs_prim.c,v $
 * Revision 2.14  90/07/03  16:38:03  mrt
 * 	Remove MACH_XP conditional and !MACH_XP code.
 * 	[90/06/28            dlb]
 * 
 * Revision 2.13  89/12/22  16:28:21  rpd
 * 	Updated vm_allocate_with_pager to vm_map.
 * 	Fixed vmp_push so it doesn't rely on non-preemptive scheduling.
 * 	[89/12/01  13:52:21  rpd]
 * 
 * Revision 2.12  89/10/03  19:25:30  rpd
 * 	Use copybzero instead of bzero in mfs_trunc.
 * 	[89/10/03  19:08:53  rpd]
 * 
 * 	Merged with my version at NeXT.  Summary:
 * 	Added vmp_lock/vmp_unlock macros.  Changed vnode_size to inode_size.
 * 	Replaced vnode_nlinks with VOP_NLINKS.  Fixed mfs_trunc.
 * 	Fixed lock arguments to memory_object_lock_request calls.
 * 	Added EINVAL argument check, tweaked error handling in mfs_io.
 * 	Modified vmp_push to request a lock_completed message
 * 	and wait until the inode_pager receives it.
 * 	[89/10/02  15:49:47  rpd]
 * 
 * Revision 2.11  89/06/25  00:00:19  jsb
 * 	This file didn't get merged in last time?
 * 	[89/06/24  23:26:10  jsb]
 * 
 * Revision 2.10.1.2  89/06/12  14:52:02  jsb
 * 	Removed previous change in allocation of mfs_map. Added two patchable
 * 	flags (close_deactivate and remap_deactivate) which determine whether
 * 	pages should be deactivated on close and on file remap. (On machines
 * 	where the inactive list is very small, deactivation is equivalent
 * 	to throwing the pages away.) Added a patchable flag which determines
 * 	whether pages should be thrown away when being cleaned in vmp_push.
 * 	(Previously, they always were.)
 * 	[89/06/12  14:36:46  jsb]
 * 
 * Revision 2.10  89/06/03  15:36:19  jsb
 * 	Allocate mfs_map in space accessible by sun ethernet interfaces
 * 	so that the nfs server doesn't have to copy file data.
 * 	[89/06/02  18:20:15  jsb]
 * 
 * Revision 2.9  89/05/11  15:40:04  gm0w
 * 	Minor fixes for NBC code from rfr.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.8  89/04/22  15:24:30  gm0w
 * 	Updated with new NBC code from rfr.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.7  89/03/09  20:14:20  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  18:06:46  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/01/18  20:19:51  jsb
 * 	Use #if MACH_VFS, not #ifdef...
 * 
 * Revision 2.4  89/01/18  00:49:38  jsb
 * 	The easy way to merge! (To be fixed for real later.)
 * 	[89/01/17  20:44:37  jsb]
 * 
 * Revision 2.3  89/01/15  21:24:23  rpd
 * 	Updated includes to the new style.
 * 	Use decl_simple_lock_data.
 * 
 * 09-Mar-88  John Seamons (jks) at NeXT
 *	MACH_VFS: allocate vm_info structures from a zone.
 *
 * 29-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Corrected calls to inode_pager_setup and kmem_alloc.
 *
 * 15-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 18-Jun-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Make most of this file dependent on MACH_NBC.
 *
 * 30-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	mfs_prim.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1987, Avadis Tevanian, Jr.
 *
 *	Support for mapped file system implementation.
 */

#include <mach_nbc.h>

#include <kern/lock.h>
#include <kern/mfs.h>

#include <sys/param.h>		/* all */
#include <sys/systm.h>		/* for */
#include <sys/mount.h>		/* inode.h */
#include <sys/dir.h>		/* Sure */
#include <sys/user.h>		/* is */
#include <sys/inode.h>		/* ugly */

#include <vm/vm_kern.h>
#include <mach/memory_object.h>
#include <mach/vm_param.h>

#include <kern/xpr.h>
#include <kern/sched_prim.h>

zone_t vm_info_zone;

/*
 *	Private variables and macros.
 */

queue_head_t		vm_info_queue;		/* lru list of structures */
decl_simple_lock_data(,	vm_info_lock_data)	/* lock for lru list */
int			vm_info_version = 0;	/* version number */

#define vm_info_lock()		simple_lock(&vm_info_lock_data)
#define vm_info_unlock()	simple_unlock(&vm_info_lock_data)

#define vmp_lock(vmp)		lock_write(&(vmp)->lock)
#define vmp_unlock(vmp)		lock_write_done(&(vmp)->lock)

#if	MACH_NBC
lock_data_t		mfs_alloc_lock_data;
boolean_t		mfs_alloc_wanted;
long			mfs_alloc_blocks = 0;

#define mfs_alloc_lock()	lock_write(&mfs_alloc_lock_data)
#define mfs_alloc_unlock()	lock_write_done(&mfs_alloc_lock_data)

vm_map_t	mfs_map;

/*
 *	mfs_map_size is the number of bytes of VM to use for file mapping.
 *	It should be set by machine dependent code (before the call to
 *	mfs_init) if the default is inappropriate.
 *
 *	mfs_max_window is the largest window size that will be given to
 *	a file mapping.  A default value is computed in mfs_init based on
 *	mfs_map_size.  This too may be set by machine dependent code
 *	if the default is not appropriate.
 *
 *	mfs_files_max is the maximum number of files that we will
 *	simultaneously leave mapped.  Note that memory for unmapped
 *	files will not necessarily leave the memory cache, but by
 *	unmapping these files the file system can throw away any
 *	file system related info (like inodes).  Again, this value
 *	can be sent by machine dependent code if the default is not
 *	appropriate.
 */

vm_size_t	mfs_map_size = 8*1024*1024;	/* size in bytes */
vm_size_t	mfs_max_window = 0;		/* largest window to use */

int		mfs_files_max = 100;		/* maximum # of files mapped */
int		mfs_files_mapped = 0;		/* current # mapped */

int close_flush = 1;			/* push pages on close? */
int close_deactivate = 0;		/* deactivate pages on close? */
int remap_deactivate = 0;		/* deactivate pages on remap? */
int push_free = 0;			/* free pages when pushing? */

#define CHUNK_SIZE	(64*1024)	/* XXX */
#endif	MACH_NBC

/*
 *	mfs_init:
 *
 *	Initialize the mfs module.
 */

mfs_init()
{
	int			i;
#if	MACH_NBC
	int			min, max;
#endif	MACH_NBC

	queue_init(&vm_info_queue);
	simple_lock_init(&vm_info_lock_data);
#if	MACH_NBC
	lock_init(&mfs_alloc_lock_data, TRUE);
	mfs_alloc_wanted = FALSE;
	mfs_map = kmem_suballoc(kernel_map, &min, &max, mfs_map_size, TRUE);
	if (mfs_max_window == 0)
		mfs_max_window = mfs_map_size / 20;
	if (mfs_max_window < CHUNK_SIZE)
		mfs_max_window = CHUNK_SIZE;
#endif	MACH_NBC

	i = (vm_size_t) sizeof (struct vm_info);
	vm_info_zone = zinit (i, 10000*i, 8192, FALSE, "vm_info zone");
}

/*
 *	vm_info_init:
 *
 *	Initialize a vm_info structure for an inode.
 */
vm_info_init(ip)
	struct inode *ip;
{
	register struct vm_info	*vmp;

	vmp = ip->i_vm_info;
	if (vmp == VM_INFO_NULL)
		vmp = (struct vm_info *) zalloc(vm_info_zone);
	vmp->map_count = 0;
	vmp->use_count = 0;
	vmp->va = 0;
	vmp->size = 0;
	vmp->offset = 0;
	vmp->identity = (struct identity *) NULL;
	vmp->error = 0;
	vmp->queued = FALSE;
	vmp->dirty = FALSE;
	vmp->close_flush = TRUE;	/* for safety, reconsider later */
	vmp->mapped = FALSE;
	vmp->inode_size = (vm_size_t)0;
	lock_init(&vmp->lock, TRUE);	/* sleep lock */
	vmp->object = VM_OBJECT_NULL;
	ip->i_vm_info = vmp;
}

#if	MACH_NBC
vm_info_enqueue(vmp)
	struct vm_info	*vmp;
{
	assert(!vmp->queued);
	assert(vmp->mapped);
	queue_enter(&vm_info_queue, vmp, struct vm_info *, lru_links);
	vmp->queued = TRUE;
	mfs_files_mapped++;
	vm_info_version++;
}

vm_info_dequeue(vmp)
	struct vm_info	*vmp;
{
	assert(vmp->queued);
	queue_remove(&vm_info_queue, vmp, struct vm_info *, lru_links);
	vmp->queued = FALSE;
	mfs_files_mapped--;
	vm_info_version++;
}

/*
 *	map_inode:
 *
 *	Indicate that the specified inode should be mapped into VM.
 *	A reference count is maintained for each mapped file.
 */
map_inode(ip)
	register struct inode	*ip;
{
	register struct vm_info	*vmp;
	memory_object_t	pager;
	extern lock_data_t	vm_alloc_lock;

	vmp = ip->i_vm_info;
	if (vmp->map_count++ > 0)
		return;		/* file already mapped */

	if (vmp->mapped)
		return;		/* file was still cached */

	vmp_get(vmp);

	pager = vmp->pager = (memory_object_t) inode_pager_setup(ip, FALSE, TRUE);
				/* not a TEXT file, can cache */
	/*
	 *	Lookup what object is actually holding this file's
	 *	pages so we can flush them when necessary.  This
	 *	would be done differently in an out-of-kernel implementation.
	 *
	 *	Note that the lookup keeps a reference to the object which
	 *	we must release elsewhere.
	 */
	vmp->object =vm_object_enter(pager, (vm_size_t) inode_size(ip),FALSE);
	inode_pager_release(vmp->pager);
	vmp->error = 0;

	vmp->inode_size = inode_size(ip);	/* must be before setting
						   mapped below to prevent
						   mfs_fsync from recursive
						   locking */
	vmp->va = 0;
	vmp->size = 0;
	vmp->offset = 0;
	vmp->mapped = TRUE;

	/*
	 *	If the file is less than the maximum window size then
	 *	just map the whole file now.
	 */

	if (vmp->inode_size > 0 && vmp->inode_size < mfs_max_window)
		remap_inode(ip, 0, vmp->inode_size);

	vmp_put(vmp);	/* put will queue on LRU list */
}

/*
 *	unmap_inode:
 *
 *	Called when an inode is closed.
 */
unmap_inode(ip)
	register struct inode	*ip;
{
	register struct vm_info		*vmp;
	register struct vm_object	*object;
	int				links;

	vmp = ip->i_vm_info;
	if (!vmp->mapped)
		return;	/* not a mapped file */
	if (--vmp->map_count > 0)
		return;

	/*
	 *	If there are no links left to the file then release
	 *	the resources held.  If there are links left, then keep
	 *	the file mapped under the assumption that someone else
	 *	will soon map the same file.  However, the pages in
	 *	the object are deactivated to put them near the list
	 *	of pages to be reused by the VM system (this would
	 *	be done differently out of the kernel, of course, then
	 *	again, the primitives for this don't exist out of the
	 *	kernel yet.
	 */

	vmp->map_count++;
	VOP_NLINKS(ITOV(ip), &links, u.u_cred);	/* may uncache, see below */
	vmp->map_count--;
	if (links == 0) {
		mfs_memfree(vmp, FALSE);
	}
	else {
		/*
		 *	pushing the pages may cause an uncache
		 *	operation (thanks NFS), so gain an extra
		 *	reference to guarantee that the object
		 *	does not go away.  (Note that such an
		 *	uncache actually takes place since we have
		 *	already released the map_count above).
		 */
		object = vmp->object;
		if (close_flush || vmp->close_flush) {
			vmp->map_count++;	/* prevent uncache race */
			vmp_get(vmp);
			vmp_push(vmp);
		}
		if (close_deactivate) {
			vm_object_lock(object);
			vm_object_deactivate_pages(object);
			vm_object_unlock(object);
		}
		if (close_flush || vmp->close_flush) {
			vmp_put(vmp);
			vmp->map_count--;
		}
	}
}

/*
 *	remap_inode:
 *
 *	Remap the specified inode (due to extension of the file perhaps).
 *	Upon return, it should be possible to access data in the file
 *	starting at the "start" address for "size" bytes.
 */
remap_inode(ip, start, size)
	register struct inode	*ip;
	vm_offset_t		start;
	register vm_size_t	size;
{
	register struct vm_info	*vmp;
	vm_offset_t		addr, offset;
	kern_return_t		ret;

	vmp = ip->i_vm_info;
	/*
	 *	Remove old mapping (making its space available).
	 */
	if (vmp->size > 0)
		mfs_map_remove(vmp, vmp->va, vmp->va + vmp->size, TRUE, remap_deactivate);

	offset = trunc_page(start);
	size = round_page(start + size) - offset;
	if (size < CHUNK_SIZE)
		size = CHUNK_SIZE;
	do {
		addr = vm_map_min(mfs_map);
		mfs_alloc_lock();
		ret = vm_map(mfs_map, &addr, size, 0, TRUE,
			     vmp->pager, offset, FALSE,
			     VM_PROT_ALL, VM_PROT_ALL, VM_INHERIT_COPY);
		/*
		 *	If there was no space, see if we can free up mappings
		 *	on the LRU list.  If not, just wait for someone else
		 *	to free their memory.
		 */
		if (ret == KERN_NO_SPACE) {
			register struct vm_info	*vmp1;

			vm_info_lock();
			vmp1 = VM_INFO_NULL;
			if (!queue_empty(&vm_info_queue)) {
				vmp1 = (struct vm_info *)
						queue_first(&vm_info_queue);
				vm_info_dequeue(vmp1);
			}
			vm_info_unlock();
			/*
			 *	If we found someone, free up its memory.
			 */
			if (vmp1 != VM_INFO_NULL) {
				mfs_alloc_unlock();
				mfs_memfree(vmp1, TRUE);
				mfs_alloc_lock();
			}
			else {
				mfs_alloc_wanted = TRUE;
				assert_wait(&mfs_map, FALSE);
				mfs_alloc_blocks++;	/* statistic only */
				mfs_alloc_unlock();
				thread_block();
				mfs_alloc_lock();
			}
		}
		else if (ret != KERN_SUCCESS) {
			printf("Unexpected error on file map, ret = %d.\n",
					ret);
			panic("remap_inode");
		}
		mfs_alloc_unlock();
	} while (ret != KERN_SUCCESS);
	/*
	 *	Fill in variables corresponding to new mapping.
	 */
	vmp->va = addr;
	vmp->size = size;
	vmp->offset = offset;
	return(TRUE);
}

/*
 *	mfs_trunc:
 *
 *	The specified inode is truncated to the specified size.
 */
mfs_trunc(ip, length)
	register struct inode	*ip;
	register int		length;
{
	register struct vm_info	*vmp;
	register vm_size_t	size, rsize;

	vmp = ip->i_vm_info;

	vmp_lock(vmp);

	if (length > vmp->inode_size) {
		vmp_unlock(vmp);
		return;
	}

	if (!vmp->mapped) {	/* file not mapped, just update size */
		vmp->inode_size = length;
		vmp_unlock(vmp);
		return;
	}

	/*
	 *	Unmap everything past the new end page.
	 *	Also flush any pages that may be left in the object using
	 *	ino_flush (is this necessary?).
	 *	rsize is the size relative to the mapped offset.
	 */
	size = round_page(length);
	if (size >= vmp->offset) {
		rsize = size - vmp->offset;
	}
	else {
		rsize = 0;
	}
	if (rsize < vmp->size) {
		mfs_map_remove(vmp, vmp->va + rsize, vmp->va + vmp->size,
			       FALSE, TRUE);
		vmp->size = rsize;		/* mapped size */
	}
	if (vmp->inode_size > size)
		ino_flush(ip, size, vmp->inode_size - size);
	vmp->inode_size = length;	/* file size */
	/*
	 *	If the new length isn't page aligned, zero the extra
	 *	bytes in the last page.
	 */
	if (length != size) {
		vm_size_t	n;

		n = size - length;
		/*
		 * Make sure the bytes to be zeroed are mapped.
		 */
		if ((length < vmp->offset) ||
		   ((length + n) > (vmp->offset + vmp->size)))
			remap_inode(ip, length, n);

		/*
		 *	If there is an error faulting in the page,
		 *	just ignore it.  The page isn't resident,
		 *	so it doesn't have to be zero.
		 */

		(void) copybzero(vmp->va + length - vmp->offset, n);

		/*
		 *	Do NOT set dirty flag... the cached memory copy
		 *	is zeroed, but this change doesn't need to be
		 *	flushed to disk (the inode already has the right
		 *	size.  Besides, if we set this bit, we would need
		 *	to clean it immediately to prevent a later sync
		 *	operation from incorrectly cleaning a cached-only
		 *	copy of this vmp (which causes problems with NFS
		 *	due to the fact that we have changed the mod time
		 *	by truncating and will need to do an mfs_uncache).
		 *	NFS is a pain.  Note that this means that there
		 *	will be a dirty page left in the vmp.  If this
		 *	turns out to be a problem we'll have to set the dirty
		 *	flag and immediately do a flush.
		 *
		 *	UPDATE: 4/4/13.  We need to really flush this.
		 *	Use the map_count hack to prevent a race with
		 *	uncaching.
		 */
		vmp->map_count++;	/* prevent uncache race */
		vmp->dirty = TRUE;
		vmp_push(vmp);
		vmp->map_count--;
	}
	vmp_unlock(vmp);
}

/*
 *	mfs_get:
 *
 *	Get locked access to the specified file.  The start and size describe
 *	the address range that will be accessed in the near future and
 *	serves as a hint of where to map the file if it is not already
 *	mapped.  Upon return, it is guaranteed that there is enough VM
 *	available for remapping operations within that range (each window
 *	no larger than the chunk size).
 */
mfs_get(ip, start, size)
	register struct inode	*ip;
	vm_offset_t		start;
	register vm_size_t	size;
{
	register struct vm_info	*vmp;

	vmp = ip->i_vm_info;

	vmp_get(vmp);

	/*
	 *	If the requested size is larger than the size we have
	 *	mapped, be sure we can get enough VM now.  This size
	 *	is bounded by the maximum window size.
	 */

	if (size > mfs_max_window)
		size = mfs_max_window;

	if (size > vmp->size) {
		remap_inode(ip, start, size);
	}

}

/*
 *	mfs_put:
 *
 *	Indicate that locked access is no longer desired of a file.
 */
mfs_put(ip)
	register struct inode	*ip;
{
	vmp_put(ip->i_vm_info);
}

/*
 *	vmp_get:
 *
 *	Get exclusive access to the specified vm_info structure.
 */
vmp_get(vmp)
	struct vm_info	*vmp;
{
	/*
	 *	Remove from LRU list (if its there).
	 */
	vm_info_lock();
	if (vmp->queued) {
		vm_info_dequeue(vmp);
	}
	vmp->use_count++;	/* to protect requeueing in vmp_put */
	vm_info_unlock();

	/*
	 *	Lock out others using this file.
	 */
	vmp_lock(vmp);
}

/*
 *	vmp_put:
 *
 *	Release exclusive access gained in vmp_get.
 */
vmp_put(vmp)
	register struct vm_info	*vmp;
{
	/*
	 *	Place back on LRU list if noone else using it.
	 */
	vm_info_lock();
	if (--vmp->use_count == 0) {
		vm_info_enqueue(vmp);
	}
	vm_info_unlock();
	/*
	 *	Let others at file.
	 */
	vmp_unlock(vmp);
	if (mfs_files_mapped > mfs_files_max)
		mfs_cache_trim();
}

/*
 *	mfs_uncache:
 *
 *	Make sure there are no cached mappings for the specified inode.
 */
mfs_uncache(ip)
	register struct inode	*ip;
{
	register struct vm_info	*vmp;

	vmp = ip->i_vm_info;
	/*
	 *	If the file is mapped but there is noone actively using
	 *	it then remove its mappings.
	 */
	if (vmp->mapped && vmp->map_count == 0) {
		mfs_memfree(vmp, FALSE);
	}
}

mfs_memfree(vmp, flush)
	register struct vm_info	*vmp;
	boolean_t		flush;
{
	struct identity	*identity;
	vm_object_t	object;

	vm_info_lock();
	if (vmp->queued) {
		vm_info_dequeue(vmp);
	}
	vm_info_unlock();
	vmp_lock(vmp);
	if (vmp->map_count == 0) {	/* cached only */
		vmp->mapped = FALSE;	/* prevent recursive flushes */
	}
	mfs_map_remove(vmp, vmp->va, vmp->va + vmp->size, flush, TRUE);
	vmp->size = 0;
	vmp->va = 0;
	object = VM_OBJECT_NULL;
	if (vmp->map_count == 0) {	/* cached only */
		/*
		 * lookup (in map_inode) gained a reference, so need to
		 * lose it.
		 */
		object = vmp->object;
		vmp->object = VM_OBJECT_NULL;
		identity = vmp->identity;
		if (identity) {
			free_identity(identity);
			vmp->identity = NULL;
		}
	}
	vmp_unlock(vmp);
	if (object != VM_OBJECT_NULL)
		vm_object_deallocate(object);
}

/*
 *	mfs_cache_trim:
 *
 *	trim the number of files in the cache to be less than the max
 *	we want.
 */

mfs_cache_trim()
{
	register struct vm_info	*vmp;

	while (TRUE) {
		vm_info_lock();
		if (mfs_files_mapped <= mfs_files_max) {
			vm_info_unlock();
			return;
		}
		/*
		 * grab file at head of lru list.
		 */
		vmp = (struct vm_info *) queue_first(&vm_info_queue);
		vm_info_dequeue(vmp);
		vm_info_unlock();
		/*
		 *	Free up its memory.
		 */
		mfs_memfree(vmp, TRUE);
	}
}

/*
 *	mfs_cache_clear:
 *
 *	Clear the mapped file cache.  Note that the map_count is implicitly
 *	locked by the Unix file system code that calls this routine.
 */
mfs_cache_clear()
{
	register struct vm_info	*vmp;
	int			last_version;

	vm_info_lock();
	last_version = vm_info_version;
	vmp = (struct vm_info *) queue_first(&vm_info_queue);
	while (!queue_end(&vm_info_queue, (queue_entry_t) vmp)) {
		if (vmp->map_count == 0) {
			vm_info_unlock();
			mfs_memfree(vmp, TRUE);
			vm_info_lock();
			/*
			 * mfs_memfree increments version number, causing
			 * restart below.
			 */
		}
		/*
		 *	If the version didn't change, just keep scanning
		 *	down the queue.  If the version did change, we
		 *	need to restart from the beginning.
		 */
		if (last_version == vm_info_version) {
			vmp = (struct vm_info *) queue_next(&vmp->lru_links);
		}
		else {
			vmp = (struct vm_info *) queue_first(&vm_info_queue);
			last_version = vm_info_version;
		}
	}
	vm_info_unlock();
}

/*
 *	mfs_map_remove:
 *
 *	Remove specified address range from the mfs map and wake up anyone
 *	waiting for map space.  Be sure pages are flushed back to inode.
 */

mfs_map_remove(vmp, start, end, flush, deactivate)
	struct vm_info	*vmp;
	vm_offset_t	start;
	vm_size_t	end;
	boolean_t	flush;
	boolean_t	deactivate;
{
	vm_object_t	object;

	/*
	 *	Note:	If we do need to flush, the vmp is already
	 *	locked at this point.
	 */
	if (flush) {
/*		vmp->map_count++;	/* prevent recursive flushes */
		vmp_push(vmp);
/*		vmp->map_count--;*/
	}

	/*
	 *	Free the address space.
	 */
	mfs_alloc_lock();
	vm_map_remove(mfs_map, start, end);
	if (mfs_alloc_wanted) {
		mfs_alloc_wanted = FALSE;
		thread_wakeup(&mfs_map);
	}
	mfs_alloc_unlock();
	/*
	 *	Deactivate the pages.
	 */
	if (deactivate) {
		object = vmp->object;
		if (object != VM_OBJECT_NULL) {
			vm_object_lock(object);
			vm_object_deactivate_pages(object);
			vm_object_unlock(object);
		}
	}
}

inode_size(ip)
	struct inode	*ip;
{
	struct vattr		vattr;

	VOP_GETATTR(ITOV(ip), &vattr, u.u_cred);
	return(vattr.va_size);
}

#include <sys/uio.h>

int	nbc_debug = 0x0;

boolean_t mfs_io(ip, uio, rw, ioflag, identity)
	register struct inode	*ip;
	register struct uio	*uio;
	enum uio_rw		rw;
	int			ioflag;
	struct identity		*identity;
{
	register vm_offset_t	va;
	register struct vm_info	*vmp;
	register int		n, diff, bsize;
	int			vsize;
	int			type;
	int			error;

	bsize = ITOV(ip)->v_vfsp->vfs_bsize;
	type = (ITOV(ip)->v_mode&VFMT);
	vmp = ip->i_vm_info;
	XPR(XPR_VM_OBJECT, ("mfs_io(%c): ip 0x%x, offset %d, size %d\n",
		rw == UIO_READ ? 'R' : 'W',
		ip, uio->uio_offset, uio->uio_resid));
	if (nbc_debug & 4) {
		printf("mfs_io(%c): ip 0x%x, offset %d, size %d\n",
			rw == UIO_READ ? 'R' : 'W',
			ip, uio->uio_offset, uio->uio_resid);
	}

	if (uio->uio_resid == 0) {
		return (0);
	}

	if ((int) uio->uio_offset < 0 ||
	    (int) (uio->uio_offset + uio->uio_resid) < 0) {
		return (EINVAL);
	}

	mfs_get(ip, uio->uio_offset, uio->uio_resid);

	/*
	 *	Set identity.
	 */
	if (rw == UIO_WRITE || (rw == UIO_READ && vmp->identity == NULL)) {
		identity->id_ref++;
		if (vmp->identity)
			free_identity(vmp->identity);
		vmp->identity = identity;
	}

	vsize = vmp->inode_size;	/* was inode_size(ip) */

	if ((rw == UIO_WRITE) && (ioflag & IO_APPEND)) {
		uio->uio_offset = vsize;
	}


	do {
		n = MIN((unsigned)bsize, uio->uio_resid);
		if (rw == UIO_READ) {
			diff = vsize - uio->uio_offset;
			if (diff <= 0) {
				mfs_put(ip);
				return (0);
				}
			if (diff < n)
				n = diff;
		}

		if ((rw == UIO_WRITE) &&
			   (uio->uio_offset + n > vmp->inode_size) &&
			   (type == VDIR || type == VREG || type == VLNK))
			vmp->inode_size = uio->uio_offset + n;
		/*
		 *	Check to be sure we have a valid window
		 *	for the mapped file.
		 */
		if ((uio->uio_offset < vmp->offset) ||
		   ((uio->uio_offset + n) > (vmp->offset + vmp->size)))
			remap_inode(ip, uio->uio_offset, n);

		va = vmp->va + uio->uio_offset - vmp->offset;
		XPR(XPR_VM_OBJECT, ("uiomove: va = 0x%x, n = %d.\n", va, n));
		if (nbc_debug & 4) {
			printf("uiomove: va = 0x%x, n = %d.\n", va, n);
		}
		error = uiomove(va, n, rw, uio);
		/*
		 *	Set dirty bit each time through loop just in
		 *	case remap above caused it to be cleared.
		 */
		if (rw == UIO_WRITE)
			vmp->dirty = TRUE;
		/*
		 *	Check for errors left by the pager.  Report the
		 *	error only once.
		 */
		if (vmp->error) {
			error = vmp->error;
			vmp->error = 0;
			/*
			 * The error might have been a permission
			 * error based on the credential.  We release it
			 * so that the next person who tries a read doesn't
			 * get stuck with it.
			 */
			if (vmp->identity)
				free_identity(vmp->identity);
			vmp->identity = NULL;
		}
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
	if ((error == 0) && (rw == UIO_WRITE) && (ioflag & IO_SYNC)) {
		/* Flush pages to disk */
		vmp_push(vmp);
		if (vmp->error) {
			error = vmp->error;
			vmp->error = 0;
		}
	}
	mfs_put(ip);
	return(error);
}

/*
 *	mfs_sync:
 *
 *	Sync the mfs cache (called by sync()).
 */
mfs_sync()
{
	register struct vm_info	*vmp, *next;
	int			last_version;

	vm_info_lock();
	last_version = vm_info_version;
	vmp = (struct vm_info *) queue_first(&vm_info_queue);
	while (!queue_end(&vm_info_queue, (queue_entry_t) vmp)) {
		next = (struct vm_info *) queue_next(&vmp->lru_links);
		if (vmp->dirty) {
			vm_info_unlock();
			vmp_get(vmp);
			vmp_push(vmp);
			vmp_put(vmp);
			vm_info_lock();
			/*
			 *	Since we unlocked, the get and put
			 *	operations would increment version by
			 *	two, so add two to our version.
			 *	If anything else happened in the meantime,
			 *	version numbers will not match and we
			 *	will restart.
			 */
			last_version += 2;
		}
		/*
		 *	If the version didn't change, just keep scanning
		 *	down the queue.  If the version did change, we
		 *	need to restart from the beginning.
		 */
		if (last_version == vm_info_version) {
			vmp = next;
		}
		else {
			vmp = (struct vm_info *) queue_first(&vm_info_queue);
			last_version = vm_info_version;
		}
	}
	vm_info_unlock();
}

/*
 *	Sync pages in specified inode.
 */
mfs_fsync(ip)
	struct inode	*ip;
{
	struct vm_info	*vmp;

	vmp = ip->i_vm_info;
	if ((vmp != VM_INFO_NULL) && (vmp->mapped)) {
		vmp_get(vmp);
		vmp_push(vmp);
		vmp_put(vmp);
	}
	return(vmp->error);
}

#include <vm/vm_page.h>
#include <vm/vm_object.h>

/*
 *	Search for and flush pages in the specified range.  For now, it is
 *	unnecessary to flush to disk since I do that synchronously.
 */
ino_flush(ip, start, size)
	struct inode		*ip;
	register vm_offset_t	start;
	vm_size_t		size;
{
	register vm_offset_t	end;
	register vm_object_t	object;
	register vm_page_t	m;

	object = ip->i_vm_info->object;
	if (object == VM_OBJECT_NULL)
		return;

	vm_object_reference(object);
	memory_object_lock_request(object, start, size, FALSE, TRUE, VM_PROT_NONE, PORT_NULL);
}

/*
 *	Search for and push (to disk) pages in the specified range.
 *	We need some better interactions with the VM system to simplify
 *	the code.
 */
vmp_push(vmp/*, start, size*/)
	struct vm_info		*vmp;
/*	register vm_offset_t	start;
	vm_size_t		size;*/
{
	register vm_offset_t	start;
	vm_size_t		size;
	register vm_offset_t	end;
	register vm_object_t	object;
	register vm_page_t	m;
	memory_object_t		pager;
	memory_object_control_t	request;

	if (!vmp->dirty)
		return;
	vmp->dirty = FALSE;

	start = vmp->offset;
	size = vmp->size;

	object = vmp->object;
	if (object == VM_OBJECT_NULL)
		return;

	vm_object_lock(object);
	object->ref_count++;	/* for lock_request */
	vm_object_paging_begin(object);	/* so we can use paging ports  */
	pager = object->pager;
	request = object->pager_request;
	vm_object_unlock(object);

	if (pager == MEMORY_OBJECT_NULL)
		panic("vmp_push: null pager");

	(void) memory_object_lock_request(object, start, size,
					  TRUE, push_free, VM_PROT_NONE,
					  PORT_NULL);
	assert_wait((int) vmp, FALSE);
	(void) memory_object_lock_completed(pager, request, start, size);

	/*
	 *	memory_object_lock_request freed the object ref;
	 *	we still have to take care of the paging ref.
	 */

	vm_object_lock(object);
	vm_object_paging_end(object);
	vm_object_unlock(object);

	/*
	 *	The lock_request will generate a stream of
	 *	data_write messages.  We do an assert_wait
	 *	to say we are waiting on vmp and then send
	 *	a lock_completed message to the inode_pager.
	 *	When it sees this, it will wake us up.
	 *
	 *	If the memory_object_lock_completed code
	 *	uses SEND_SWITCH, then we will actually be
	 *	blocked on the event inside the IPC code.
	 *	Then the thread_block call below does nothing.
	 *
	 *	If the memory_object_lock_completed code
	 *	doesn't use SEND_SWITCH, we will block on
	 *	the event in the thread_block call below,
	 *	and then the inode_pager will run to wake us up.
	 *
	 *	If we did the assert_wait before the lock_request,
	 *	then if it used SEND_SWITCH when sending a data_write
	 *	message we would block on the event too soon, before
	 *	sending the lock_completed that will wake us up.
	 *
	 *	So this scheme works no matter how the scheduling happens.
	 *	The message sending code may/may not use SEND_SWITCH;
	 *	it would even work if the current thread were preempted
	 *	arbitrarily.
	 *
	 *	Because vmp is locked throughout, nobody else
	 *	can get in here to sleep on vmp or generate
	 *	another lock_completed wakeup.
	 */

	thread_block();

}
#endif	MACH_NBC
