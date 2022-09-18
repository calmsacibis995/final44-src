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
 * $Log:	inode_pager.c,v $
 * Revision 2.39  90/07/03  16:34:03  mrt
 * 	Try to be a little smarter about when to use precious attribute
 * 	on supplied data.  Use inode_pager_setup_lock to avoid
 * 	race between 2 threads setting up the same inode.
 * 
 * 	Take advantage of precious functionality to allow space to be
 * 	freed when a page is paged in from a paging file.  Added
 * 	pager_dealloc_page to implement freeing of space.
 * 
 * 	Renamed pf_alloc, pf_dealloc, and pf_bmap to pager_alloc,
 * 	pager_dealloc, and pager_bmap to make it clear that these
 * 	operate on pagers rather than paging files.
 * 
 * 	Fix pagein buffer management code to reuse buffer space when
 * 	I/O fails instead of abandoning it.  Set base address for vm_map_find.
 * 
 * 	Removed MACH_XP conditionals: use builtin/old_pager.c if !MACH_VFS.
 * 	Use power of 2 backoff to get smaller buffers if vm_map_find
 * 	fails in ipset_buffer_allocate.
 * 
 * 	Clean up and turn on USE_SUPPLY code.
 * 
 * 	USE_SUPPLY modifications to use deallocate version of
 * 	memory_object_data_supply and take advantage of page stealing.
 * 
 * 	Use privileged host port for new vm_set_default_memory_manager.
 * 	[90/07/02            dlb]
 * 
 * Revision 2.38  90/03/27  18:28:26  dlb
 * 	Increment is->errors if pf_bmap(is, offset, B_WRITE) fails
 * 	(returns -1).  This fixes the reincarnation of the bug that
 * 	causes the system to return zero-filled memory when it runs out
 * 	of paging space.  Fix suggested by rpd.
 * 	[90/03/26            dlb]
 * 
 * Revision 2.37  89/12/22  16:26:20  rpd
 * 	If this isn't a MACH_VFS/MACH_XP kernel, use builtin/old_pager.c.
 * 	[89/12/22  16:14:15  rpd]
 * 
 * 	Added missing <mach/vm_param.h> include.
 * 	[89/12/01  13:50:25  rpd]
 * 
 * 	Purged inode_pager_active, inode_pager_shutdown.
 * 	[89/11/28  21:32:33  rpd]
 * 
 * 	Updated to new SERVER_LOOP interface.
 * 	Updated to new vm_map_pageable interface.
 * 	Fixed various unix_master/unix_release bugs.
 * 	Added support for multiple threads.
 * 	[89/11/24  23:04:36  rpd]
 * 
 * 	Revamped and simplified in the following ways:
 * 	1)  Purged non-MACH_XP, non-MACH_VFS code.
 * 	2)  Purged anonymous inode code; revised mach_swapon call.
 * 	3)  Purged internal queue of data requests.
 * 	4)  Simplified the no-senders detection.
 * 	5)  Dropped support for multiple client kernels.
 * 	[89/11/24  15:04:06  rpd]
 * 
 *
 * 	Condensed history:
 *	Picked up pager-file support (Peter King at NeXT).  (rfr)
 *	Replaced VOP_PAGE_INIT/VOP_RDWR with VOP_PAGE_WRITE.  (jsb)
 *	Use vm_set_default_memory_manager.  (mwyoung)
 *	Vnode/VFS support.  (jsb)
 *	Fake no-senders detections with a "dead" ref count.  (mwyoung)
 *	Allow multiple clients of a memory object.  (mwyoung)
 *	Use memory_object_data_error.  (mwyoung)
 *	Remember errors on a per-object basis. (mwyoung)
 *	Added inode_pager_release(). (mwyoung)
 *	Try to avoid deadlock when allocating data structures  (avie, mwyoung).
 *	Try to printf rather than panic when faced with errors (avie).
 *	"No buffer code" enhancements. (avie)
 *	External paging version. (mwyoung, bolosky)
 *	Allow pageout to ask whether a page has been written out.  (dbg)
 *	Keep only a pool of in-core inodes.  (avie)
 *	Use readahead when able. (avie)
 *	Require that inode operations occur
 *	 on the master processor (avie, rvb, dbg).
 *	Combine both "program text" and "normal file" handling
 *	 into one. (avie, mwyoung)
 *	Allocate paging inodes on mounted filesystems (mja);
 *	 allow preferences to be supplied (mwyoung).
 *
 * 12-Mar-86  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	inode_pager.c
 *
 *	"Swap" pager that pages to/from Unix inodes.  Also
 *	handles demand paging from files.
 *
 *	Assumes MACH_VFS and MACH_XP are both TRUE.
 */
#include <mach_nbc.h>
#include <mach_vfs.h>
#include <mach_assert.h>

#if	MACH_VFS

#include <mach/std_types.h>
#include <mach/memory_object.h>
#include <mach/message.h>
#include <mach/notify.h>
#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_object.h>
#include <kern/parallel.h>
#include <kern/zalloc.h>
#include <kern/task.h>
#include <kern/kern_port.h>
#include <kern/queue.h>
#include <kern/mfs.h>
#include <kern/xpr.h>
#include <kern/thread.h>
#include <kern/host.h>
#include <sys/buf.h>
#include <sys/errno.h>
#include <sys/inode.h>
#include <sys/uio.h>
#include <sys/user.h>
#include <builtin/inode_pager.h>

#include <vm/vm_page.h>		/* for data_request buffer hackery */

#ifndef	private
#define private
#endif	private

boolean_t	inode_pager_debug = FALSE;

/*
 *	Inode_pager data structure protocols:
 *
 *	The basic data structure is the inode_pager_t, which
 *	represents a particular (on-disk) inode, and thus a
 *	particular memory object.
 *
 *	Because of other demands for in-memory inodes, the
 *	inode_pager cannot consume too many inode structures.
 *	The inode_pager_iget() routine is used to get a real
 *	inode (including one inode reference) for a particular
 *	inode_pager_t; the inode_pager_iput() routine allows
 *	the inode to be recycled.  [The inode_pager_iget() may
 *	be called multiple times, though different threads.
 *	The count of inode_pager_iget() references is maintained
 *	internally, and does not get reflected in the actual
 *	inode reference count (other than the original call).]
 *
 *	Inode_pager objects can be created through either of
 *	two mechanisms:
 *		User mapping request:
 *			a user requests a memory object that
 *			corresponds to a particular inode;
 *		Kernel temporary object:
 *			the kernel provides a memory object that
 *			it uses for paging temporary data.
 *
 *	To satisfy a user request, the inode_pager must first find
 *	the memory_object associated with that inode if it has
 *	already been created.  [The inode must be resident, because
 *	the requestor must have a reference.]  Thus, the inode
 *	structure has been modified to contain the memory_object port.
 *
 *	This field in the inode is also used to prevent the
 *	destruction/truncation of inodes used strictly for paging.
 *
 *	Currently, the routines in the inode_pager are called
 *	from either of two sources:
 *		Inode_pager task:
 *			A separate singly-threaded task is created
 *			to service the memory management interface.
 *		Kernel-state user threads:
 *			Mapping and cache control requests are made
 *			from the kernel context of the client thread.
 *	The kernel-context threads, as well as outside use of the inode
 *	data structure, requires the inode_pager to synchronize as
 *	though it were multi-threaded.
 *
 *	The routines that act within the inode_pager task make all
 *	Mach kernel function requests through the RPC interface, and
 *	thus use the non-KERNEL data types for data objects (tasks,
 *	memory objects, ports).  Currently, the value of task_self()
 *	for the inode_pager task is cached in the inode_pager_self
 *	variable.
 *
 *	Despite being a separate task, the inode_pager runs within
 *	the kernel virtual address space, so that it may directly access
 *	inode data structures.  Memory allocation may also be done
 *	using the internal kernel functions.
 *
 *	The kernel-context threads also complicate port management.
 *	In addition to maintaining the port names known to the inode_pager
 *	task (including conversion between port names and inode_pager_t's),
 *	the data structures must contain the global names for the
 *	memory_object and memory_object_control ports.
 *
 *	Port rights and references are maintained as follows:
 *		Memory object port:
 *			The inode_pager task has all rights, and
 *			keeps one reference for the global name stored
 *			with the inode_pager_t structure.  [The port
 *			recorded in the inode is the global name, and is
 *			copied from the	inode_pager_t, sharing that
 *			reference.]
 *		Memory object control port:
 *			The inode_pager task has only send rights,
 *			and keeps one reference for the global name
 *			it stores.  [As with the memory_object port,
 *			the global name is copied into the inode itself,
 *			so that control functions can be instigated by
 *			kernel-context client threads.]
 *		Memory object name port:
 *			The inode_pager task has only send rights.
 *			The name port is not even recorded.
 *	Regardless how the object is created, the control and name
 *	ports are created by the kernel and passed through the memory
 *	management interface.
 *
 *	The inode_pager assumes that access to its memory objects
 *	will not be propagated to more that one host, and therefore
 *	provides no consistency guarantees beyond those made by the
 *	kernel.
 *
 *	In the event that more than one host attempts to use an inode
 *	memory object, the inode_pager will only record the last set
 *	of port names.  [This can happen with only one host if a new
 *	mapping is being established while termination of all previous
 *	mappings is taking place.]  Currently, the inode_pager assumes
 *	that its clients adhere to the initialization and termination
 *	protocols in the memory management interface; otherwise, port
 *	rights or out-of-line memory from erroneous messages may be
 *	allowed to accumulate.
 *
 *	As mentioned above, the inode_pager can also provide the backing
 *	storage for temporary memory objects.  Thus, it must adhere to
 *	the restrictions placed on default memory managers for those
 *	temporary objects (and currently, for other objects as well).
 *	
 *	[The phrase "currently" has been used above to denote aspects of
 *	the implementation that could be altered without changing the rest
 *	of the basic documentation.]
 */

/*
 * Pager file structure.
 */
typedef struct pager_file {
	queue_chain_t	pf_chain;	/* link to other paging files */
	struct	inode	*pf_ip;		/* inode of paging file */
	u_int		pf_count;	/* Number of istruct using this file */
	u_char		*pf_bmap; 	/* Map of used blocks */
	long		pf_npgs;	/* Size of file in pages */
	long		pf_pfree;	/* Number of unused pages */
	long		pf_lowat;	/* Low water page */
	long		pf_hipage;	/* Highest page allocated */
	char		*pf_name;	/* Filename of this file */
	boolean_t	pf_prefer;
	lock_data_t	pf_lock;	/* Lock for alloc and dealloc */
} *pager_file_t;

#define	PAGER_FILE_NULL	(pager_file_t) 0
#define	MAXPAGERFILES 10

int minpagersize = 20971520;

#define	MINPAGERSIZE minpagersize

#if	NBBY == 8
#define BYTEMASK 0xff
#else	NBBY
Define a byte mask for this machine.
#endif	NBBY

/* Should be an integral of sizeof(vm_offset_t) */
#define PAGEMAP_THRESHOLD	512 

#define	PAGEMAP_ENTRIES		(PAGEMAP_THRESHOLD/sizeof(vm_offset_t))
#define	PAGEMAP_SIZE(npgs)	(npgs*sizeof(long))

#define	INDIRECT_PAGEMAP_ENTRIES(npgs) \
	(((npgs-1)/PAGEMAP_ENTRIES) + 1)

#define INDIRECT_PAGEMAP_SIZE(npgs) \
	(INDIRECT_PAGEMAP_ENTRIES(npgs) * sizeof(caddr_t))

#define INDIRECT_PAGEMAP(size)	(PAGEMAP_SIZE(size) > PAGEMAP_THRESHOLD)
#define RMAPSIZE(blocks) (howmany(blocks,NBBY))

/*
 * Pager file data structures
 */
queue_head_t		pager_files;
int			pager_file_count;

/*
 *	Basic inode pager structure
 */

typedef struct istruct {
	queue_chain_t	lru_links;	/* LRU queue links */
	int		client_count;	/* How many memory_object_init's
					 * have we received
					 */
	memory_object_t	pager;		/* Pager port */
	int		set;		/* set that this pager is in */
	port_t		pager_request;	/* Known request port */
	kern_port_t	pager_global;	/* XXX global name */
	int		errors;		/* Pageout error count */

	int		is_size;	/* size of this chunk in pages*/
	pager_file_t	is_pf;		/* Pager file this uses */
	vm_offset_t	**is_pmap;	/* Map of pages into paging file */

	unsigned int
			cached:1,	/* Can be cached? */
			paging:1,	/* inode used for paging */
			pages_returned:1; /* any clean pages returned ? */
	struct inode	*ip;		/* in memory inode */
	struct identity	*identity;	/* credentials */
} *inode_pager_t;

#define INODE_PAGER_NULL	((inode_pager_t) 0)

#if	!MACH_NBC
/*
 *	Nullify calls to mfs_uncache
 */
#define	mfs_uncache(ip)
#endif	!MACH_NBC

extern void	inode_pager_no_senders();

typedef struct inode_pager_set {
	port_t		ipset_set;	/* port set name */
	int		ipset_count;	/* number of objects in the set */
	thread_t	ipset_thread;	/* thread servicing the set */
	vm_offset_t	ipset_buf_base;	/* base of buffer region */
	vm_offset_t	ipset_buf_ptr;	/* next input buffer to use */
	vm_offset_t	ipset_buf_end;	/* end of buffer memory */
	vm_object_t	ipset_buf_object; /* vm_object for buffers */
} *inode_pager_set_t;

#define	IPSET_BUFFER_SIZE	32*PAGE_SIZE

task_t		inode_pager_task;
port_t		inode_pager_self;
inode_pager_set_t inode_pager_sets;
int		inode_pager_num_sets = 5;

decl_simple_lock_data(,inode_pager_init_lock)

/*
 *	Stuff for keeping a hash table of ports for inode_pager
 *	backed objects.
 */

#define		INODE_PORT_HASH_COUNT	127
typedef struct inode_port_entry {
		queue_chain_t	links;
		port_t		name;
		inode_pager_t	pager_rec;
} *inode_port_entry_t;
#define		INODE_PAGER_NULL	((inode_pager_t) 0)

private
queue_head_t	inode_port_hashtable[INODE_PORT_HASH_COUNT];
private
zone_t		inode_port_hash_zone;


#define		inode_port_hash(name_port) \
			(((int)(name_port) & 0xffffff) % INODE_PORT_HASH_COUNT)

private
void		inode_port_hash_insert(name_port, rec)
	port_t		name_port;
	inode_pager_t	rec;
{
	register
	inode_port_entry_t	new_entry =
		(inode_port_entry_t) zalloc(inode_port_hash_zone);

	new_entry->name = name_port;
	new_entry->pager_rec = rec;
	queue_enter(&inode_port_hashtable[inode_port_hash(name_port)],
			new_entry, inode_port_entry_t, links);
}

private
void		inode_port_hash_init()
{
	register vm_size_t	size;
	register int		i;

	size = (vm_size_t) sizeof(struct inode_port_entry);
	inode_port_hash_zone = zinit(size,
			(vm_size_t) 10000*size, /* XXX */
			PAGE_SIZE, FALSE, "inode_pager port hash");

	for (i = 0; i < INODE_PORT_HASH_COUNT; i++) 
		queue_init(&inode_port_hashtable[i]);
}

private
inode_pager_t	inode_pager_lookup(name_port)
	register port_t	 name_port;
{
	register
	queue_t bucket =
		(queue_t) &inode_port_hashtable[inode_port_hash(name_port)];
	register
	inode_port_entry_t entry =
		 (inode_port_entry_t) queue_first(bucket);

	while (!queue_end(bucket,&entry->links)) {
		if (entry->name == name_port)
			return(entry->pager_rec);
		entry = (inode_port_entry_t)queue_next(&entry->links);
	}
	return(INODE_PAGER_NULL);
}

private
inode_pager_t	inode_pager_lookup_external(name_port)
	port_t		name_port;
{
	kern_port_t	kport = (kern_port_t) name_port;
	port_t		name;

	assert(kport != KERN_PORT_NULL);

	port_lock(kport);
	assert(kport->port_receiver == inode_pager_task);
	name = kport->port_receiver_name;
	port_unlock(kport);

	return(inode_pager_lookup(name));
}


private
void		inode_port_hash_delete(name_port)
	register name_port;
{
	register queue_t bucket = 
		(queue_t) &inode_port_hashtable[inode_port_hash(name_port)];
	register inode_port_entry_t entry = 
		(inode_port_entry_t) queue_first(bucket);

	while (!queue_end(bucket,&entry->links)) {
		if (entry->name == name_port) {
			queue_remove(bucket, entry, inode_port_entry_t,links);
			zfree(inode_port_hash_zone, (vm_offset_t) entry);
			break;
		}
		entry = (inode_port_entry_t)queue_next(&entry->links);
	}
}

/*
 *	Forward declarations.
 */

boolean_t	inode_pager_server();
boolean_t	inode_pager_default_server();

/*
 *	Basic inode pager data structures
 */

zone_t			istruct_zone;

void		inode_uncache(ip)
	struct inode	*ip;
{
	mfs_uncache(ip);
	if (ip->i_vm_info->pager_request != PORT_NULL)
		memory_object_set_attributes(
			vm_object_lookup(ip->i_vm_info->pager_request),
			TRUE, FALSE, MEMORY_OBJECT_COPY_DELAY);
}

boolean_t	inode_uncache_try(ip)
	struct inode	*ip;
{
	vm_object_t	o;

	if (ip->i_vm_info->pager_request == PORT_NULL)
		return(FALSE);

	if ((o = vm_object_lookup(ip->i_vm_info->pager_request)) == VM_OBJECT_NULL) {
		/*
		 *	If there's no memory object for this port, it
		 *	must have been memory_object_terminate'd, and
		 *	thus is not in the cache.
		 */
		return(TRUE);
	}

	if (o->ref_count == 1) {
		memory_object_set_attributes(o, TRUE, FALSE, MEMORY_OBJECT_COPY_DELAY);
		return(TRUE);
	}
	vm_object_deallocate(o);
	return(FALSE);
}

/*
 * pf_allocate_page - allocate a page in the paging file
 */
daddr_t
pf_allocate_page(pf)
     register struct pager_file *pf;
{
	int bp;			/* byte counter */
	int i;			/* bit counter */
	daddr_t page;		/* page number */

	lock_write(&pf->pf_lock);

	if (pf->pf_pfree == 0) {
		lock_done(&pf->pf_lock);
		return(-1);
	}

	for (bp = 0; bp < howmany(pf->pf_npgs, NBBY); bp++) {
		if (*(pf->pf_bmap + bp) != BYTEMASK) {
			for (i = 0; i < NBBY; i++) {
				if (isclr((pf->pf_bmap + bp), i))
					break;
			}
			break;
		}
	}
	page = bp*NBBY+i;
	if (page >= pf->pf_npgs) {
		panic("inode_pager_allocpage");
	}
	if (page > pf->pf_hipage) {
		pf->pf_hipage = page;
	}
	setbit(pf->pf_bmap,page);
	if (--pf->pf_pfree == 0)
		printf("inode_pager: %s is full.\n", pf->pf_name);

	lock_done(&pf->pf_lock);

	if (inode_pager_debug)
		printf("pf_allocate_page returning: %d\n", page);
	return(page);
}

void
pf_deallocate_page(pf, page)
     register struct pager_file *pf;
     daddr_t page;
{
	int		i;
	struct inode	*ip = pf->pf_ip;
	struct vattr	vattr;
	int		error;
	long		truncpage;

	lock_write(&pf->pf_lock);

	if (page >= (daddr_t) pf->pf_npgs)
		panic("inode_pager_deallocpage");
	clrbit(pf->pf_bmap, page);
	if (++pf->pf_pfree == 1)
		printf("inode_pager: %s is available again.\n", pf->pf_name);

	if (page == pf->pf_hipage) {
		/*
		 * Find a new high page
		 */
		for (i = page - 1; i >= 0; i--) {
			if (isset(pf->pf_bmap, i)) {
				pf->pf_hipage = i;
				break;
			}
		}
		truncpage = pf->pf_hipage + 1;

		/*
		 * If we are higher than the low water mark, truncate
		 * the file.
 		 */
		if (pf->pf_lowat &&
		    truncpage >= pf->pf_lowat &&
		    ip->i_vm_info->inode_size > ptoa(truncpage)) {
			struct identity	*tidentity;

			vattr_null(&vattr);
			vattr.va_size = ptoa(truncpage);
			assert((int) vattr.va_size >= 0);
			/*
			 * ufs uses u.u_identity for credentials checking.
			 */
			tidentity = u.u_identity;
			u.u_identity = ip->i_vm_info->identity;
			if (error = VOP_SETATTR(ITOV(ip), &vattr,
						ip->i_vm_info->identity)) {
				printf("inode_deallocpage: error truncating %s, error = %d\n",
				       pf->pf_name, error);
			}
			u.u_identity = tidentity;
		}
	}
	lock_done(&pf->pf_lock);
}


/*
 *	pf_pager_create
 *
 *	Create an istruct corresponding to the given pagerfile.
 *
 *	This may potentially cause other incore inodes to be
 *	released (but remembered by the istruct).
 */
private
inode_pager_t
pf_pager_create(pf, size)
	register pager_file_t	pf;
	vm_size_t		size;
{
	register inode_pager_t	is;
	register int i;

	/*
	 *	XXX This can still livelock -- if the
	 *	pageout daemon needs an inode_pager record
	 *	it won't get one until someone else
	 *	refills the zone.
	 */

	is = (struct istruct *) zalloc(istruct_zone);
	assert(is != INODE_PAGER_NULL);

	is->is_size = atop(round_page(size));

	is->pager_global = KERN_PORT_NULL;
	is->pager = MEMORY_OBJECT_NULL;
	is->pager_request = PORT_NULL;

	if (INDIRECT_PAGEMAP(is->is_size)) {
		is->is_pmap = (vm_offset_t **)
			kalloc(INDIRECT_PAGEMAP_SIZE(is->is_size));
	} else {
		is->is_pmap = (vm_offset_t **)
			kalloc(PAGEMAP_SIZE(is->is_size));
	}
	if (is->is_pmap == (vm_offset_t **) 0) {
		/*
		 * We can't sleep here, so if there are no free pages, then
		 * just return nothing.
		 */
		zfree(istruct_zone, (vm_offset_t) is);
		return(INODE_PAGER_NULL);
	}

	if (INDIRECT_PAGEMAP(is->is_size)) {
		bzero((caddr_t)is->is_pmap,
		      INDIRECT_PAGEMAP_SIZE(is->is_size));
	} else {
	       	for (i = 0; i < is->is_size;
		     is->is_pmap[i++] = (vm_offset_t *) -1);
	}

	is->client_count = 0;
	is->paging = TRUE;
	is->pages_returned = FALSE;

	is->ip = pf->pf_ip;

	u.u_identity->id_ref++;
	is->identity = u.u_identity;
	is->errors = 0;
	is->is_pf = pf;
	pf->pf_count++;

	return(is);
}

/*
 *	pager_bmap
 *
 *	Return f_offset into a pager file for a given f_offset into an
 *	object backed by the pager file.
 *
 *	Returns: -1 page not in pager file or no room left
 */
vm_offset_t
pager_bmap(is, f_offset, flag)
	struct istruct *is;
	vm_offset_t f_offset;
	int flag;
{
	vm_offset_t f_page;
	register int i;
	vm_offset_t newpage;
	vm_offset_t newoffset;

	f_page = atop(f_offset);

	if (inode_pager_debug)
		printf("pager_bmap called with %x (%d)\n", f_offset, f_page);

	/*
	 * If the object has grown, expand the page map.
	 */
	if (f_page >= is->is_size) {
		vm_offset_t	**new_pmap;
		int		new_size;

		new_size = f_page + 1;
		if (INDIRECT_PAGEMAP(new_size)) {

			/* Copy info from the old map */
			if (INDIRECT_PAGEMAP(is->is_size)) {
				if (INDIRECT_PAGEMAP_SIZE(new_size) ==
				    INDIRECT_PAGEMAP_SIZE(is->is_size)) {
					goto leavemapalone;
				}
				
				/* Get a new indirect map */
				if ((new_pmap = (vm_offset_t **)
				     kalloc(INDIRECT_PAGEMAP_SIZE(new_size)))
				    == NULL) {
					return (-1);
				}
				bzero((caddr_t)new_pmap,
				      INDIRECT_PAGEMAP_SIZE(new_size));

				/* Old map is indirect, copy the entries */
				for (i = 0;
				     i < INDIRECT_PAGEMAP_ENTRIES(is->is_size);
				     i++) {
					new_pmap[i] = is->is_pmap[i];
				}
				/* And free the old map */
				kfree((vm_offset_t)is->is_pmap,
				      INDIRECT_PAGEMAP_SIZE(is->is_size));
			} else {				
				/* Get a new indirect map */
				if ((new_pmap = (vm_offset_t **)
				     kalloc(INDIRECT_PAGEMAP_SIZE(new_size)))
				    == NULL) {
					return (-1);
				}
				bzero((caddr_t)new_pmap,
				      INDIRECT_PAGEMAP_SIZE(new_size));

				/*
				 * Old map is direct, move it to the
				 * first indirect block.
				 */
				if ((new_pmap[0] = (vm_offset_t *)
				     kalloc(PAGEMAP_THRESHOLD)) == NULL) {
					kfree((vm_offset_t)new_pmap,
					      INDIRECT_PAGEMAP_SIZE(new_size));
					return (-1);
				}
				for (i = 0; i < is->is_size; i++) {
					new_pmap[0][i] =
						(vm_offset_t) is->is_pmap[i];
				}
				/* Initialize the remainder of the block */
				for (i = is->is_size; i < PAGEMAP_ENTRIES;
				     new_pmap[0][i++] = (vm_offset_t)-1);
				/* And free the old map */
				kfree((vm_offset_t)is->is_pmap,
				      PAGEMAP_SIZE(is->is_size));
			}			
		} else {
			/* New map is direct */
			if ((new_pmap = (vm_offset_t **)
			     kalloc(PAGEMAP_SIZE(new_size))) == NULL) {
				return (-1);
			}
			/* Copy info from the old map */
			for (i = 0; i < is->is_size; i++) {
				new_pmap[i] = is->is_pmap[i];
			}
			/* Initialize the rest of the new map */
			for (i = is->is_size; i < new_size;
			     new_pmap[i++] = (vm_offset_t *) -1);
			kfree((vm_offset_t)is->is_pmap,
			      PAGEMAP_SIZE(is->is_size));
		}
		is->is_pmap = new_pmap;
leavemapalone:
		is->is_size = new_size;
	}

	if (INDIRECT_PAGEMAP(is->is_size)) {
		if (is->is_pmap[f_page/PAGEMAP_ENTRIES] == NULL) {
			if (flag == B_READ) {
				return ((vm_offset_t)-1);
			}
			if ((is->is_pmap[f_page/PAGEMAP_ENTRIES] =
			    (vm_offset_t *) kalloc(PAGEMAP_THRESHOLD)) == NULL) {
				return((vm_offset_t)-1);
			}
			for (i = 0; i < PAGEMAP_ENTRIES;
			     is->is_pmap[f_page/PAGEMAP_ENTRIES][i++] =
			     (vm_offset_t)-1);
		}
		if (is->is_pmap[f_page/PAGEMAP_ENTRIES]
		    [f_page%PAGEMAP_ENTRIES] == -1) {
			if (flag == B_READ) {
				return((vm_offset_t)-1);
			}
			if ((newpage = pf_allocate_page(is->is_pf)) ==
			    -1) {
				return((vm_offset_t)-1);
			}
			is->is_pmap[f_page/PAGEMAP_ENTRIES]
				[f_page%PAGEMAP_ENTRIES] = newpage;
		}
		newoffset = (f_offset&page_mask) +
			ptoa(is->is_pmap[f_page/PAGEMAP_ENTRIES]
				[f_page%PAGEMAP_ENTRIES]);
	} else {
		if (is->is_pmap[f_page] == (vm_offset_t *) -1) {
			if (flag == B_READ ||
			    (newpage = pf_allocate_page(is->is_pf)) ==
			    -1) {
				return((vm_offset_t)-1);
			}
			is->is_pmap[f_page] = (vm_offset_t *)newpage;
		}
		newoffset = (f_offset&page_mask) +
			ptoa((vm_offset_t)is->is_pmap[f_page]);
	}

	if (inode_pager_debug)
		printf("pager_bmap returning %x\n", newoffset);
	return(newoffset);
}

/*
 *	istruct_create
 *
 *	Create an istruct corresponding to the given ip.
 *
 *	This may potentially cause other incore inodes to be
 *	released (but remembered by the istruct).
 */
private
inode_pager_t	istruct_create(ip)
	register struct inode	*ip;
{
	register inode_pager_t	is;
	struct identity		*identity;

	/*
	 *	XXX This can still livelock -- if the
	 *	pageout daemon needs an inode_pager record
	 *	it won't get one until someone else
	 *	refills the zone.
	 */

	is = (struct istruct *) zalloc(istruct_zone);
	assert(is != INODE_PAGER_NULL);

	is->pager_global = KERN_PORT_NULL;
	is->pager = MEMORY_OBJECT_NULL;
	is->pager_request = PORT_NULL;
	is->client_count = 0;
	is->paging = FALSE;
	is->pages_returned = FALSE;
	ip->i_vm_info->pager = (memory_object_t) is->pager_global;
	ip->i_vm_info->pager_request = (memory_object_control_t) PORT_NULL;

	is->ip = ip;

	identity = u.u_identity;
	identity->id_ref++;
	is->identity = identity;

	is->errors = 0;

	INCR_INODE(ip);

	return(is);
}

/*
 *	Routine:	inode_pager_add
 *	Purpose:
 *		Put an inode_pager_t into a set.
 *		Called from inode_pager_setup (random context)
 *		and inode_pager_create (inode_pager context).
 */

void inode_pager_add(is)
	register inode_pager_t	is;
{
	extern struct timeval time;
	port_t name = is->pager;
	inode_pager_set_t set;
	int i;

	i = ((time.tv_sec + time.tv_usec + name) %
	     (unsigned int) inode_pager_num_sets);
	assert((0 <= i) && (i < inode_pager_num_sets));
	set = &inode_pager_sets[i];

	if (port_set_add(inode_pager_task,
			 set->ipset_set, name) != KERN_SUCCESS)
		panic("inode_pager_add: can't put object into set");

	set->ipset_count++;
	is->set = i;
}

/*
 *	Routine:	inode_pager_no_senders
 *	Purpose:
 *		Cleans up and deallocates an inode_pager_t.
 *		Called from inode_pager_release (random context)
 *		and inode_pager_terminate (inode_pager context).
 */

void inode_pager_no_senders(is)
	register inode_pager_t	is;
{
	if (is->client_count != 0)
		panic("inode_pager_no_senders: client count");

	assert(is->pager_request == PORT_NULL);

	assert(is->pager_global != KERN_PORT_NULL);
	port_release(is->pager_global);

	if (!is->paging) {
		struct inode	*ip = is->ip;

		/*
		 *	Release the inode reference and clear
		 *	the pager field in vm_info.  Do this
		 *	before destroying the port, so the
		 *	field doesn't have to hold a reference.
		 */

#if	!MACH_NBC
		ip->i_flag &= ~ITEXT;
#endif	!MACH_NBC
		ip->i_vm_info->pager = MEMORY_OBJECT_NULL;
		FINISH_WITH_INODE(ip);
	}

	/*
	 *	Remove the memory object port association, and then
	 *	the destroy the port itself.
	 */

	inode_port_hash_delete(is->pager);
	if (port_deallocate(inode_pager_task, is->pager) != KERN_SUCCESS)
		panic("inode_pager_no_senders: destroy pager");

	inode_pager_sets[is->set].ipset_count--;

	if (is->paging) {
		pager_dealloc(is);
	} else {
		free_identity(is->identity);
		zfree(istruct_zone, (vm_offset_t) is);
	}
}

/*
 *	Routine:	inode_pager_setup
 *	Purpose:
 *		Returns a memory object (that may be used in
 *		a call to vm_map) representing the given inode.
 *	Side effects:
 *		When the memory object returned by this call
 *		is no longer needed (e.g., it has been mapped
 *		into the desired address space), it should be
 *		deallocated using inode_pager_release.
 *	NOTE:
 *		This call does not run in the context of the 
 *		inode_pager task, and therefore must translate
 *		the ports it gets itself.
 */

lock_data_t	inode_pager_setup_lock;

memory_object_t	inode_pager_setup(ip, is_text, can_cache)
	struct inode	*ip;
	boolean_t	is_text;
	boolean_t	can_cache;
{
	register pager_file_t	pf;
	inode_pager_t		is;
	kern_port_t		port;

	if (ip == (struct inode *) 0)
		return(MEMORY_OBJECT_NULL);

	/*
	 *	inode_pager_setup_lock makes sure that only one
	 *	inode_pager_setup can be in progress at any time.
	 *	This prevents duplicate istruct alloacation if
	 *	one instance blocks and a second call is made on the
	 *	same inode.
	 */

	unix_master();

	lock_write(&inode_pager_setup_lock);

#if	!MACH_NBC
	/*
	 *	When file-writing goes through the mapped file system,
	 *	we don't need to turn on the text bit to prevent the file
	 *	from being written.  This is because we have the file
	 *	mapped copy-on-write, so everything will work out OK.
	 */
	if (is_text)
		ip->i_flag |= ITEXT;
#endif	!MACH_NBC

	if (ip->i_vm_info->pager == MEMORY_OBJECT_NULL) {
		/*
		 * Check to make sure this isn't in use as a pager file.
		 */
		for (pf = (pager_file_t) queue_first(&pager_files);
		     !queue_end(&pager_files, &pf->pf_chain);
		     pf = (pager_file_t) queue_next(&pf->pf_chain)) {
			if (pf->pf_ip == ip) {
			    uprintf("Can't page directly to a paging file.\n");
			    unix_release();
			    lock_done(&inode_pager_setup_lock);
			    return(MEMORY_OBJECT_NULL);
			}
		}

		is = istruct_create(ip);

		if (port_allocate(inode_pager_task, &is->pager)
							!= KERN_SUCCESS)
		    panic("inode_pager_setup: can't allocate port");

		/*
		 *	Get the global name for the port.
		 */

		is->pager_global =
			port_lookup(inode_pager_task, is->pager);

		inode_pager_add(is);
		inode_port_hash_insert(is->pager, is);

		/*
		 *	Save the global name in the inode.
		 *
		 *	[This step comes last so that we've
		 *	got the association entirely set up
		 *	before the pager value can be grabbed
		 *	from the inode structure by someone
		 *	else while we're blocked in the port
		 *	operations.]
		 */

		ip->i_vm_info->pager =
			(memory_object_t) is->pager_global;

		is->cached = can_cache;
	} else {
		struct identity *identity;

		is = inode_pager_lookup_external(ip->i_vm_info->pager);
		assert(is != INODE_PAGER_NULL);

		identity = u.u_identity;
		identity->id_ref++;
		if (is->identity != NULL)
			free_identity(is->identity);
		is->identity = identity;
	}

	port = (kern_port_t) ip->i_vm_info->pager;
	assert(port != KERN_PORT_NULL);
	port_reference(port);

	lock_done(&inode_pager_setup_lock);
	unix_release();
	return((memory_object_t) port);
}

/*
 *	Routine:	inode_pager_release
 *	Purpose:
 *		Relinquish any references or rights that were
 *		associated with the result of a call to
 *		inode_pager_setup.
 *	NOTE:
 *		This call, like inode_pager_setup, does not run
 *		in the context of the inode_pager.
 */
void		inode_pager_release(object)
	memory_object_t	object;
{
	register kern_port_t port = (kern_port_t) object;

	if (port != KERN_PORT_NULL) {
		int refs;

		unix_master();

		port_lock(port);
		refs = --port->port_references;
		assert(port->port_in_use);
		port_unlock(port);

		/*
		 *  The port has no senders left if there are only
		 *  three remaining references, for
		 *	1) translation entry in inode_pager_task
		 *	2) membership in a port set
		 *	3) for inode_pager_t->pager_global field
		 *
		 *  This should happen rarely here; much more often
		 *  a memory object has no senders after it is terminated.
		 */

		if (refs <= 3) {
			inode_pager_t is;

			assert(refs == 3);
#if	MACH_ASSERT
			printf("inode_pager_release: no senders\n");
#endif	MACH_ASSERT

			is = inode_pager_lookup_external((port_t) port);
			assert(is != INODE_PAGER_NULL);
			assert(!is->paging);

			inode_pager_no_senders(is);
		}

		unix_release();
	}
}

/*
 * 	Routine:	inode_pager_file_init
 *	Function:
 *		Create a pager_file structure for a new pager file.
 *	Arguments:
 *		The file in question is specified by inode pointer.
 *		lowat and hiwat are the low water and high water marks
 *		that the size of pager file will float between.  If
 *		the low water mark is zero, then the file will not
 *		shrink after paging space is freed.  If the high water
 *		mark is zero, the file will grow without bounds.
 */
int
inode_pager_file_init(pfp, ip, lowat, hiwat)
	pager_file_t	*pfp;
	struct inode	*ip;
	long lowat;
	long hiwat;
{
	struct vattr	vattr;
	register pager_file_t	pf;
	int	error;
	long	i;
	struct statfs	fstat;
	struct identity	*identity;
	vm_size_t	size;

	*pfp = PAGER_FILE_NULL;

	/*
	 * Make sure no other object paging to this file?
	 */
	mfs_uncache(ip);
	if (ip->i_vm_info->mapped) {
		return(EBUSY);
	}

	/*
	 * Clean up the file blocks on a pager file by
	 * truncating to length "lowat".
	 */
	identity = u.u_identity;
	error = VOP_GETATTR(ITOV(ip), &vattr, identity);
	size = vattr.va_size;
	if (size > lowat) {
		vattr_null(&vattr);
		vattr.va_size = size = lowat;
		error = VOP_SETATTR(ITOV(ip), &vattr, identity);
		if (error) {
			return(error);
		}
	}

	/*
	 * Initialize the inode_size field
	 */
	ip->i_vm_info->inode_size = size;

	pf = (pager_file_t) kalloc(sizeof(struct pager_file));
	INCR_INODE(ip);
	pf->pf_ip = ip;
	identity->id_ref++;
	ip->i_vm_info->identity = identity;
	pf->pf_count = 0;
	pf->pf_lowat = atop(round_page(lowat));
	/*
	 * If no maximum space is specified, then we should make a map that
	 * can cover the entire disk, otherwise the block map need only
	 * cover the maximum space allowed.
	 */
	if (!hiwat) {
		error = VFS_STATFS(ITOV(ip)->v_vfsp, &fstat);
		if (error) {
			kfree((vm_offset_t) pf, sizeof(struct pager_file));
			return(error);
		}
		hiwat = fstat.f_blocks * fstat.f_bsize;
	}
	pf->pf_pfree = pf->pf_npgs = atop(hiwat);
	pf->pf_bmap = (u_char *) kalloc(RMAPSIZE(pf->pf_npgs));
	for (i = 0; i < pf->pf_npgs; i++) {
		clrbit(pf->pf_bmap, i);
	}
	pf->pf_hipage = -1;
	pf->pf_prefer = FALSE;
	lock_init(&pf->pf_lock, TRUE);

	/*
	 * Put the new pager file in the list.
	 */
	queue_enter(&pager_files, pf, pager_file_t, pf_chain);
	pager_file_count++;
	*pfp = pf;
	return (0);
}

/*
 *	Routine:	mach_swapon
 *	Function:
 *		Syscall interface to mach_swapon.
 */
kern_return_t
mach_swapon(filename, flags, lowat, hiwat)
	char 	*filename;
	int	flags;
	long	lowat;
	long	hiwat;
{
	struct inode		*ip;
	struct pathname		pn;
	pager_file_t		pf;
	kern_return_t		error;
	char 			*name;
	int			namelen;

	if (!suser())
		return(KERN_NO_ACCESS);

	unix_master();

	/*
	 * Get a inode for the paging area.
	 */
	error = pn_get(filename, UIO_USERSPACE, &pn);
	if (error) {
		unix_release();
		return(KERN_INVALID_ARGUMENT);
	}

	namelen = pn.pn_pathlen + 1;
	name = (char *)kalloc(namelen);
	strncpy(name, pn.pn_path, namelen - 1);
	name[namelen - 1] = '\0';

	ip = (struct inode *)0;
	error = lookuppn(&pn, FOLLOW_LINK, (struct inode **)0, &ip);
	pn_free(&pn);
	if (error) {
		error = KERN_INVALID_ARGUMENT;
		goto bailout;
	}

	if ((ip->i_mode&IFMT) != IFREG) {
		error = KERN_INVALID_ARGUMENT;
		goto bailout;
	}

	/*
	 * Look to see if we are already paging to this file.
	 */
	for (pf = (pager_file_t) queue_first(&pager_files);
	     !queue_end(&pager_files, &pf->pf_chain);
	     pf = (pager_file_t) queue_next(&pf->pf_chain)) {
		if (pf->pf_ip == ip)
			break;
	}
	if (!queue_end(&pager_files, &pf->pf_chain)) {
		error = KERN_INVALID_ARGUMENT;
		goto bailout;
	}

	error = inode_pager_file_init(&pf, ip, lowat, hiwat);
	if (error) {
		error = KERN_INVALID_ARGUMENT;
		goto bailout;
	}
	pf->pf_prefer = ((flags & MS_PREFER) != 0);
	pf->pf_name = name;
	name = NULL;

	error = KERN_SUCCESS;
bailout:
	if (ip) {
		FINISH_WITH_INODE(ip);
	}
	if (name) {
		kfree(name, namelen);
	}
	unix_release();
	return(error);
}

/*
 *	Routine:	inode_swap_preference
 *	Function:
 *		An old system call.
 */
kern_return_t inode_swap_preference(device, prefer, never)
	dev_t		device;
	boolean_t	prefer;
	boolean_t	never;
{
#ifdef	lint
	device++; prefer++; never++;
#endif	lint

	return KERN_FAILURE;
}			

/*
 *	Routine:	inode_pager_start_slave
 *	Purpose:
 *		Start a slave thread to handle a port set.
 *		Communicates the slave's number to him
 *		in the reply_port field of the thread structure.
 *
 *		Note that the mach_user_internal.h interface
 *		contains thread_create and thread_resume
 *		definitions that we don't want.
 */

thread_t inode_pager_start_slave(num)
	int num;
{
	extern void inode_pager_slave();
	thread_t slave;

	if (thread_create(inode_pager_task, &slave) != KERN_SUCCESS)
		panic("inode_pager: can't create slave thread");

	thread_start(slave, inode_pager_slave, THREAD_SYSTEMMODE);
	slave->max_priority = BASEPRI_SYSTEM;
	slave->priority = BASEPRI_SYSTEM;
	slave->sched_pri = BASEPRI_SYSTEM;
	slave->ipc_kernel = TRUE;

	slave->vm_privilege = TRUE;
	thread_swappable(slave, FALSE);

	slave->reply_port = (port_t) num;

	if (thread_resume(slave) != KERN_SUCCESS)
		panic("inode_pager: can't start slave thread");

	return(slave);
}

/*
 *	Make all calls involving the kernel interface go through IPC.
 *	All code after this point runs in the context of the pager.
 */

#include <mach/mach_user_internal.h>

/*
 *	Rename all of the functions in the pager interface,
 *	to avoid confusing them with the kernel interface
 */

#define memory_object_init		inode_pager_init
#define memory_object_terminate		inode_pager_terminate
#define memory_object_data_request	inode_pager_data_request
#define memory_object_data_unlock	inode_pager_data_unlock
#define memory_object_data_write	inode_pager_data_write
#define memory_object_copy		inode_pager_copy
#define memory_object_lock_completed	inode_pager_lock_completed
#define memory_object_create		inode_pager_create
#define memory_object_data_initialize	inode_pager_data_initialize
#define memory_object_supply_completed	inode_pager_supply_completed
#define memory_object_data_return	inode_pager_data_return


int		inode_pager_pagein_count = 0;
int		inode_pager_pageout_count = 0;

port_t		inode_pager_default = PORT_NULL;

/*
 *	Routine:	pf_find
 *	Function:
 *		Allocate a place for paging out a kernel-created
 *		memory object.
 *
 *	Implementation: 
 *		Looks through the paging files for the one with the
 *		most free space.  First, only "preferred" paging files
 *		are considered, then local paging files, and then
 *		remote paging files.  In each case, the pager file
 *		the most free blocks will be chosen.
 *
 *	In/out conditions:
 *		If the paging area is on a local disk, the inode is
 *		returned locked.
 */
pager_file_t
pf_find()
{
	int		pass;
	int 		mostspace;
	pager_file_t	pf, mostpf;

	mostpf = PAGER_FILE_NULL;
	mostspace = 0;

	if (pager_file_count > 1) {
		for (pass = 0; pass < 4; pass++) {
			for (pf = (pager_file_t)queue_first(&pager_files);
			     !queue_end(&pager_files, &pf->pf_chain);
			     pf = (pager_file_t)queue_next(&pf->pf_chain)) {

				/*
				 *	In passes 0 and 1, only consider
				 *	preferred paging files.
				 */

				if ((pass < 2) && !pf->pf_prefer)
					continue;

				/*
				 *	In passes 0 and 2, only consider
				 *	local (ufs) paging files.
				 */

				if (!(pass & 1) &&
				    (pf->pf_ip->i_type != ITYPE_UFS))
					continue;

				if (pf->pf_pfree > mostspace) {
					mostspace = pf->pf_pfree;
					mostpf = pf;
				}
			}
			/*
			 * If we found space, then break out of loop.
			 */
			if (mostpf != PAGER_FILE_NULL)
				break;
		}
	} else if (pager_file_count == 1) {
		mostpf = (pager_file_t) queue_first(&pager_files);
	}

	return(mostpf);
}

inode_pager_t pager_alloc(size)
	vm_size_t	size;
{
	pager_file_t	pf;

#ifdef	lint
	size++;
#endif	lint

	if (inode_pager_debug)
		printf("pager_alloc called with size = %d pages\n",atop(size));

	/*
	 *	Get a pager_file, then turn it into a paging space.
	 */

	if ((pf = pf_find()) == PAGER_FILE_NULL)
		return(INODE_PAGER_NULL);

	return(pf_pager_create(pf, size));
}

pager_dealloc(is)
	inode_pager_t	is;
{
	pager_file_t		pf;
	int			i,j;

	pf = is->is_pf;
	if (pf == NULL)
		panic("pager_dealloc: is->is_pf == NULL");

	if (INDIRECT_PAGEMAP(is->is_size)) {
		for (i = 0; i < INDIRECT_PAGEMAP_ENTRIES(is->is_size); i++) {
			if (is->is_pmap[i] != NULL) {
				for(j = 0; j < PAGEMAP_ENTRIES; j++) {
					if (is->is_pmap[i][j] != -1) {
						pf_deallocate_page(pf, 
							    is->is_pmap[i][j]);
					}
				}
				kfree(is->is_pmap[i], PAGEMAP_THRESHOLD);
			}
		}
		kfree(is->is_pmap, INDIRECT_PAGEMAP_SIZE(is->is_size));
	} else {
		for (i = 0; i < is->is_size; i++) {
			if (is->is_pmap[i] != (vm_offset_t *)-1) {
				pf_deallocate_page(pf,
					(daddr_t) is->is_pmap[i]);
			}
		}
		kfree(is->is_pmap, PAGEMAP_SIZE(is->is_size));
	}
	pf->pf_count--;

	free_identity(is->identity);
	zfree(istruct_zone, (vm_offset_t) is);
}

pager_dealloc_page(is, offset)
	register inode_pager_t	is;
	vm_offset_t		offset;
{
	pager_file_t		pf;
	register vm_offset_t	page;
	register vm_offset_t	*pmap_entry;

	page = atop(offset);
	if (page >= is->is_size)
		panic("pager_dealloc_page: beyond end of file");

	pf = is->is_pf;

	if (INDIRECT_PAGEMAP(is->is_size)) {
		if (is->is_pmap[page/PAGEMAP_ENTRIES] == NULL)
			return;

		pmap_entry = &(is->is_pmap[page/PAGEMAP_ENTRIES]
				[page%PAGEMAP_ENTRIES]);
	}
	else {
		pmap_entry = (vm_offset_t *) &(is->is_pmap[page]);
	}

	page = *pmap_entry;
	*pmap_entry = (vm_offset_t) -1;

	if (page != (vm_offset_t) -1)
		pf_deallocate_page(pf, page);
}

void
is_page_initialize(is, offset, addr)
	inode_pager_t	is;
	vm_offset_t	offset;
	vm_offset_t	addr;
{
	vm_offset_t	actual_offset;

	if (!is->paging)
		panic("is_page_initialize");

	actual_offset = pager_bmap(is, offset, B_READ);
	if (actual_offset != (vm_offset_t) -1)
		return;

	actual_offset = pager_bmap(is, offset, B_WRITE);
	if (actual_offset == (vm_offset_t) -1) {
		is->errors++;
		return;
	}

	if (VOP_PAGE_WRITE(ITOV(is->ip), addr, PAGE_SIZE,
			   actual_offset, is->identity, FALSE))
		is->errors++;
}

kern_return_t
is_page_read(is, offset, addr)
	inode_pager_t	is;
	vm_offset_t	offset;
	vm_offset_t	addr;
{
	vm_offset_t	actual_offset;
	kern_return_t	ret;

	if (is->paging) {
		actual_offset = pager_bmap(is, offset, B_READ);
	} else {
		actual_offset = offset;
	}

	if (actual_offset == (vm_offset_t)-1)
		return (EINVAL);

	ret = VOP_PAGE_READ(ITOV(is->ip), addr, PAGE_SIZE,
			    actual_offset, is->identity);

	inode_pager_pagein_count++;

	return (ret);
}


void
is_page_write(is, offset, addr)
	inode_pager_t	is;
	vm_offset_t	offset;
	vm_offset_t	addr;
{
	vm_offset_t	actual_offset;
	vm_offset_t	size = PAGE_SIZE;

	if (is->paging) {
		actual_offset = pager_bmap(is, offset, B_WRITE);
	} else {
		actual_offset = offset;
	}

	if (actual_offset == (vm_offset_t)-1) {
		is->errors++;
		return;
	}

#if	MACH_NBC
	if (!is->paging) {
		vm_offset_t file_size = is->ip->i_vm_info->inode_size;

		/*
		 *	Ensure that a paging operation doesn't
		 *	accidently extend a "mapped" file.
		 */
		if (actual_offset + size > file_size) {
			if (actual_offset > file_size)
				panic("is_page_write");

			size = file_size - actual_offset;
		}
	}
#endif	MACH_NBC

	if (VOP_PAGE_WRITE(ITOV(is->ip), addr, size,
			   actual_offset, is->identity, FALSE))
		is->errors++;

	inode_pager_pageout_count++;
}

/*
 *	ipset_buffer_allocate:  Allocate buffer for an inode pager set.
 *
 *	Allocate a buffer for an inode pager set.  This buffer
 *	is backed by a newly created vm_object so the page stealing
 *	code will do the right thing.
 */

void ipset_buffer_allocate(ipset)
inode_pager_set_t	ipset;
{
	register vm_object_t	object;
	register vm_size_t	size;

	/*
	 *	Note: we don't hold a reference for the buffer object.
	 *	That would confuse the page stealing code.  Instead
	 *	we rely on the map entry to hold the reference as long
	 *	as any of the object is mapped.
	 */

	size = IPSET_BUFFER_SIZE;
	object = vm_object_allocate(size);
	ipset->ipset_buf_object = object;

	/*
	 *	Under normal circumstances, we should be able to get
	 *	a complete buffer of IPSET_BUFFER_SIZE.  But under
	 *	heavy paging traffic, we may have to settle for less
	 *	due to map fragmentation.  This code assumes
	 *	IPSET_BUFFER_SIZE is a power of 2 multiple of PAGE_SIZE.
	 */

	ipset->ipset_buf_base = vm_map_min(inode_pager_task->map);
	while (vm_map_find(inode_pager_task->map, object, 0,
			&ipset->ipset_buf_base, size, TRUE)
		!= KERN_SUCCESS) {

		    size = size/2;
		    if (size < PAGE_SIZE)
			panic("(inode_pager)ipset_buffer_allocate: no space");

		    ipset->ipset_buf_base = vm_map_min(inode_pager_task->map);
	}

	ipset->ipset_buf_ptr = ipset->ipset_buf_base;
	ipset->ipset_buf_end = ipset->ipset_buf_base + size;
}

kern_return_t	
memory_object_data_request(pager, pager_request,
			   offset, length, protection_required)
	memory_object_t	pager;
	port_t		pager_request;
	vm_offset_t	offset;
	vm_size_t	length;
	vm_prot_t	protection_required;
{
	register inode_pager_t	is;
	int			ret;
	register vm_offset_t	buffer;
	register
	inode_pager_set_t	ipset;
	vm_page_t		m;
	boolean_t		precious;

	if (inode_pager_debug)
		printf("%s: pager=%d, offset=0x%x, length=0x%x\n",
			"(inode_pager)data_request",
			pager, offset, length);

	if (length != PAGE_SIZE)
		panic("(inode_pager)data_request: bad length");

	unix_master();

	is = inode_pager_lookup(pager);
	if (is == INODE_PAGER_NULL)
		panic("(inode_pager)data_request: lookup failed");

	assert(is->client_count == 1);
	assert(is->pager_request == pager_request);

	if (is->errors) {
		printf("(inode_pager)data_request:\n");
		printf(" dropping request (previous errors)\n");

		(void) memory_object_data_error(pager_request, offset,
						PAGE_SIZE, KERN_FAILURE);
		return KERN_SUCCESS;
	}

	/*
	 *	Get next buffer for this pager set.
	 */
	ipset = &inode_pager_sets[is->set];
	if (ipset->ipset_buf_ptr == ipset->ipset_buf_end)
		ipset_buffer_allocate(ipset);
		
	buffer = ipset->ipset_buf_ptr;
	ipset->ipset_buf_ptr += PAGE_SIZE;

	/*
	 *	Allocate a physical page for this buffer, and
	 *	map it in for the I/O.  This works, but a more
	 *	general solution might be a good idea.
	 */
	while ((m = vm_page_alloc(ipset->ipset_buf_object,
			buffer - ipset->ipset_buf_base)) == VM_PAGE_NULL) {
				VM_WAIT;
	}
	pmap_enter(kernel_pmap, buffer, VM_PAGE_TO_PHYS(m),
		VM_PROT_READ|VM_PROT_WRITE, TRUE);

	/*
	 *	Read the page into the buffer and then unmap it.
	 *	memory_object_data_supply can steal the page
	 *	without mapping it in.
	 */

	ret = is_page_read(is, offset, buffer);

	pmap_remove(kernel_pmap, buffer, buffer + PAGE_SIZE);
	if (ret) {
		VM_PAGE_FREE(m);
		ipset->ipset_buf_ptr = buffer;
	}
	else {
		/*
		 *	Clear busy, wakeup should never happen.
		 *	Remove page from disk and supply it precious
		 *	if the page is from a paging object AND
		 *		It's going to be written, or
		 *		No clean pages have been returned to this
		 *			object, or
		 *		The paging file is short on space.
		 *
		 * 	This is primitive, but captures objects that are
		 *	initialized and then only read; they will be paged
		 *	out dirty once, then paged out clean, and left on disk.
		 *
		 * XXX	Should add check for paging file tight on space.
		 *
		 */
		PAGE_WAKEUP_DONE(m);
		precious = (is->paging &&
			    ((protection_required & VM_PROT_WRITE) ||
			     (!is->pages_returned)));

		if (precious)
			pager_dealloc_page(is, offset);
	}

	unix_release();

	switch (ret) {
		case 0:
			(void) memory_object_data_supply(
					pager_request, offset, buffer,
					PAGE_SIZE, TRUE,
					VM_PROT_NONE,
					precious, PORT_NULL);
			break;
		case EINVAL:
			(void) memory_object_data_unavailable(
					pager_request, offset, PAGE_SIZE);
			break;
		case EIO:
			(void) memory_object_data_error(
					pager_request, offset,
					PAGE_SIZE, KERN_FAILURE);
			break;
		default:
			panic("(inode_pager)data_request: is_page_read");
	}

	return KERN_SUCCESS;
}

/*
 * memory_object_data_initialize: check whether we already have each page, and
 * write it if we do not.  The implementation is far from optimized, and
 * also assumes that the inode_pager is single-threaded.
 */
kern_return_t
memory_object_data_initialize(pager, pager_request, offset, addr, data_cnt)
	memory_object_t	pager;
	port_t		pager_request;
	register
	vm_offset_t	offset;
	register
	pointer_t	addr;
	vm_size_t	data_cnt;
{
	inode_pager_t	is;
	vm_offset_t	amount_sent;

#ifdef	lint
	pager_request++;
#endif	lint

	XPR(XPR_INODE_PAGER_DATA,
	    ("(inode_pager)data_initialize: pager 0x%x, offset 0x%x",
	     pager, offset));

	if (inode_pager_debug)
		printf("%s: pager=%d, offset=0x%x, length=0x%x\n",
		       "(inode_pager)data_initialize",
		       pager, offset, data_cnt);

	if ((data_cnt % PAGE_SIZE) != 0)
		panic("(inode_pager)data_initialize: data_cnt");

	unix_master();

	is = inode_pager_lookup(pager);
	if (is == INODE_PAGER_NULL)
		panic("(inode_pager)data_initialize: lookup failed");

	assert(is->client_count == 1);
	assert(is->pager_request == pager_request);

	for (amount_sent = 0;
	     amount_sent < data_cnt;
	     amount_sent += PAGE_SIZE) {
		is_page_initialize(is,offset+amount_sent,addr+amount_sent);
	}

	unix_release();

	if (vm_deallocate(inode_pager_self, addr, data_cnt) != KERN_SUCCESS)
		panic("(inode_pager)data_initialize: deallocate failed");

	return(KERN_SUCCESS);
}

/*
 * memory_object_data_write: split up the stuff coming in 
 * from a memory_object_data_write call
 * into individual pages and pass them off to inode_write.
 */
kern_return_t	
memory_object_data_write(pager, pager_request, offset, addr, data_cnt)
	memory_object_t	pager;
	port_t		pager_request;
	register
	vm_offset_t	offset;
	register
	pointer_t	addr;
	vm_size_t	data_cnt;
{
	register
	vm_size_t	amount_sent;
	inode_pager_t	is;

#ifdef	lint
	pager_request++;
#endif	lint

	XPR(XPR_INODE_PAGER_DATA, 
	    ("(inode_pager)data_write: pager 0x%x, offset 0x%x",
	     pager, offset));

	if (inode_pager_debug)
		printf("%s: pager=%d, offset=0x%x, length=0x%x\n",
		       "(inode_pager)data_write",
		       pager, offset, data_cnt);

	if ((data_cnt % PAGE_SIZE) != 0)
		panic("(inode_pager)data_write: data_cnt");

	unix_master();

	is = inode_pager_lookup(pager);
	if (is == INODE_PAGER_NULL)
		panic("(inode_pager)data_write: lookup failed");

	assert(is->client_count == 1);
	assert(is->pager_request == pager_request);

	for (amount_sent = 0;
	     amount_sent < data_cnt;
	     amount_sent += PAGE_SIZE) {
		is_page_write(is, offset + amount_sent, addr + amount_sent);
	}

	unix_release();

	if (vm_deallocate(inode_pager_self, addr, data_cnt) != KERN_SUCCESS)
		panic("(inode_pager)data_write: deallocate failed");

	return(KERN_SUCCESS);
}

/*
 * memory_object_data_return: A page paged in from a paging file
 * has been paged back out.  Put it back.  Set pages_returned
 * flag in istruct to warn data_request that this happened.
 */
kern_return_t	
memory_object_data_return(pager, pager_request, offset, addr, data_cnt)
	memory_object_t	pager;
	port_t		pager_request;
	register
	vm_offset_t	offset;
	register
	pointer_t	addr;
	vm_size_t	data_cnt;
{
	register
	vm_size_t	amount_sent;
	inode_pager_t	is;

#ifdef	lint
	pager_request++;
#endif	lint

	XPR(XPR_INODE_PAGER_DATA, 
	    ("(inode_pager)data_return: pager 0x%x, offset 0x%x",
	     pager, offset));

	if (inode_pager_debug)
		printf("%s: pager=%d, offset=0x%x, length=0x%x\n",
		       "(inode_pager)data_return",
		       pager, offset, data_cnt);

	if ((data_cnt % PAGE_SIZE) != 0)
		panic("(inode_pager)data_return: data_cnt");

	unix_master();

	is = inode_pager_lookup(pager);
	if (is == INODE_PAGER_NULL)
		panic("(inode_pager)data_return: lookup failed");

	assert(is->client_count == 1);
	assert(is->pager_request == pager_request);

	is->pages_returned = TRUE;

	for (amount_sent = 0;
	     amount_sent < data_cnt;
	     amount_sent += PAGE_SIZE) {
		is_page_write(is, offset + amount_sent, addr + amount_sent);
	}

	unix_release();

	if (vm_deallocate(inode_pager_self, addr, data_cnt) != KERN_SUCCESS)
		panic("(inode_pager)data_return: deallocate failed");

	return(KERN_SUCCESS);
}

kern_return_t	
memory_object_data_unlock(pager, pager_request,
			  offset, length, protection_required)
	memory_object_t	pager;
	port_t		pager_request;
	vm_offset_t	offset;
	vm_size_t	length;
	vm_prot_t	protection_required;
{
#ifdef	lint
	pager++; pager_request++;
	offset++; length++;
	protection_required++;
#endif	lint

	panic("(inode_pager)data_unlock: called");
	return KERN_FAILURE;
}

kern_return_t
memory_object_lock_completed(pager, pager_request, offset, length)
	memory_object_t	pager;
	port_t		pager_request;
	vm_offset_t	offset;
	vm_size_t	length;
{
#if	MACH_NBC
	inode_pager_t	is;

#ifdef	lint
	offset++; length++;
#endif	lint

	unix_master();

	is = inode_pager_lookup(pager);
	if (is == INODE_PAGER_NULL)
		panic("(inode_pager)lock_completed: lookup failed");

	assert(is->client_count == 1);
	assert(is->pager_request == pager_request);

	/*
	 *	A thread in vmp_push (kern/mfs_prim.c) wants to know
	 *	when the pageouts he triggered are finished.
	 *	Because the lock_completed was queued after the
	 *	data_write messages, they must be all done now.
	 */

	thread_wakeup((int) is->ip->i_vm_info);
	unix_release();
	return KERN_SUCCESS;

#else	MACH_NBC

#ifdef	lint
	pager++; pager_request++;
	offset++; length++;
#endif	lint

	panic("(inode_pager)lock_completed: called");
	return KERN_FAILURE;
#endif	MACH_NBC
}

kern_return_t
memory_object_copy(old_memory_object, old_memory_control,
		   offset, length, new_memory_object)
	memory_object_t		old_memory_object;
	memory_object_control_t	old_memory_control;
	vm_offset_t		offset;
	vm_size_t		length;
	memory_object_t		new_memory_object;
{
#ifdef	lint
	old_memory_object++; old_memory_control++;
	offset++; length++; new_memory_object++;
#endif	lint

	panic("(inode_pager)copy: called");
	return KERN_FAILURE;
}

kern_return_t
memory_object_supply_completed(pager, pager_request, offset,
			length, result, error_offset)
memory_object_t	pager;
port_t		pager_request;
vm_offset_t	offset;
vm_size_t	length;
kern_return_t	result;
vm_offset_t	error_offset;
{
#ifdef	lint
	pager++; pager_request++; offset++;
	length++; result++; error_offset++;
#endif	lint

	panic("(inode_pager)supply_completed: called");
	return(KERN_FAILURE);
}

/*
 *	Routine:	memory_object_create
 *	Purpose:
 *		Handle requests for memory objects from the
 *		kernel.
 *	Notes:
 *		Because we only give out the default memory
 *		manager port to the kernel, we don't have to
 *		be so paranoid about the contents.
 */
kern_return_t	memory_object_create(old_pager, new_pager, new_size, new_pager_request, new_pager_name, new_page_size)
	port_t		old_pager;
	port_t		new_pager;
	vm_size_t	new_size;
	port_t		new_pager_request;
	port_t		new_pager_name;
	vm_size_t	new_page_size;
{
	inode_pager_t	is;

	if (inode_pager_debug)
		printf("%s: new_pager=%d, new_request=%d, new_name=%d\n",
			"(inode_pager)create",
			new_pager, new_pager_request, new_pager_name);

	if (old_pager != inode_pager_default)
		panic("(inode_pager)create: old_pager not default");

	if (new_pager == PORT_NULL)
		panic("(inode_pager)create: null new_pager");

	if (new_pager_request == PORT_NULL)
		panic("(inode_pager)create: null new_pager_request");

	if (new_pager_name != PORT_NULL)
		panic("(inode_pager)create: non-null new_pager_name");

	if (new_page_size != PAGE_SIZE)
		panic("(inode_pager)create: wrong page size");

	unix_master();

	is = pager_alloc(new_size);
	if (is == INODE_PAGER_NULL) {
		printf("(inode_pager)create: unable to allocate");
		printf(" inode_pager structure [REBOOT SUGGESTED]\n");
		return(KERN_RESOURCE_SHORTAGE);
	}

	assert(is->client_count == 0);
	is->client_count = 1;

	assert(is->paging);

	assert(is->pager == PORT_NULL);
	is->pager = new_pager;

	assert(is->pager_global == KERN_PORT_NULL);
	is->pager_global = port_lookup(inode_pager_task, new_pager);

	assert(is->pager_request == PORT_NULL);
	is->pager_request = new_pager_request;

	inode_pager_add(is);
	inode_port_hash_insert(new_pager, is);

	unix_release();

	return(KERN_SUCCESS);
}

memory_object_copy_strategy_t inode_copy_strategy = MEMORY_OBJECT_COPY_DELAY;

kern_return_t
memory_object_init(pager, pager_request, pager_name, pager_page_size)
	port_t		pager;
	port_t		pager_request;
	port_t		pager_name;
	vm_size_t	pager_page_size;
{
	inode_pager_t	is;
	kern_port_t	pager_request_port;

	if (inode_pager_debug)
		printf("(inode_pager)init: pager=%d, request=%d, name=%d\n",
		       pager, pager_request, pager_name);

	if (pager_page_size != PAGE_SIZE)
		panic("(inode_pager)init: wrong page size");

	if (pager_request == PORT_NULL)
		panic("(inode_pager)init: null request port");

	if (pager_name == PORT_NULL)
		panic("(inode_pager)init: null name port");

	unix_master();

	is = inode_pager_lookup(pager);
	if (is == INODE_PAGER_NULL)
		panic("(inode_pager)init: lookup failed");

	if (is->paging)
		panic("(inode_pager)init: paging");

	if (is->client_count++ > 0)
		panic("(inode_pager)init: multiple clients!");

	assert(is->pager_request == PORT_NULL);
	is->pager_request = pager_request;

	/*
	 *	Use port_lookup to convert pager_request to
	 *	pager_request_port, but release the ref immediately.
	 *	(The pager/pager_request fields in vm_info don't
	 *	need refs, because they are cleared when the ports
	 *	are destroyed, in inode_pager_no_senders and
	 *	inode_pager_terminate.)
	 */

	pager_request_port = port_lookup(inode_pager_task, pager_request);
	port_release(pager_request_port);
	is->ip->i_vm_info->pager_request =
		(memory_object_control_t) pager_request_port;

	/*
	 *	Reply to the kernel:  the memory object is ready.
	 */

	if (memory_object_set_attributes(pager_request, TRUE,
					 is->cached, inode_copy_strategy)
						!= KERN_SUCCESS)
		panic("(inode_pager)init: set_attributes");

	unix_release();
	return(KERN_SUCCESS);
}

kern_return_t	memory_object_terminate(pager, pager_request, pager_name)
	port_t		pager;
	port_t		pager_request;
	port_t		pager_name;
{
	inode_pager_t	is;
	kern_port_t	port;
	int		refs;

	if (pager_request == PORT_NULL)
		panic("(inode_pager)terminate: null request port");

	if ((pager_name != PORT_NULL) &&
	    (port_deallocate(inode_pager_self, pager_name) != KERN_SUCCESS))
		panic("(inode_pager)terminate: deallocate name");

	/*
	 *	The kernel can call memory_object_init on this memory_object
	 *	and reuse it before the last send right disappears.
	 *	So, when we are done the object has to be ready for
	 *	either memory_object_init or inode_pager_no_senders.
	 */

	unix_master();

	is = inode_pager_lookup(pager);
	if (is == INODE_PAGER_NULL)
		panic("(inode_pager)terminate: lookup failed");

	assert(is->client_count == 1);
	assert(is->pager_request == pager_request);

	is->client_count = 0;
	is->pager_request = PORT_NULL;

	/*
	 *	Clear pager_request in vm_info before
	 *	deallocating the port, so the field doesn't
	 *	need to hold a ref.
	 */

	if (is->paging) {
		assert(is->ip->i_vm_info->pager_request == PORT_NULL);
	} else
		is->ip->i_vm_info->pager_request = PORT_NULL;

	if (port_deallocate(inode_pager_self, pager_request) != KERN_SUCCESS)
		panic("(inode_pager)terminate: deallocate request");

	port = is->pager_global;
	assert(port != KERN_PORT_NULL);

	port_lock(port);
	refs = port->port_references;
	assert(port->port_in_use);
	port_unlock(port);

	/* see inode_pager_release for no-senders detection discussion */

	if (refs <= 3) {
		assert(refs == 3);

		inode_pager_no_senders(is);
	} else {
		/* this should be a rare situation */

		assert(!is->paging);
#if	MACH_ASSERT
		printf("(inode_pager)terminate: %d senders left\n", refs-3);
#endif	MACH_ASSERT
	}

	unix_release();
	return KERN_SUCCESS;
}

void
inode_pager_port_death(port)
	port_t port;
{
	panic("inode_pager_port_death");
}

/*
 *	Include the server loop
 */

#define SERVER_LOOP		inode_pager_server_loop
#define SERVER_NAME		"inode_pager"
#define SERVER_DISPATCH(in,out)	\
		(inode_pager_server(in, out) || \
		 inode_pager_default_server(in, out))
#define	TERMINATE_FUNCTION	inode_pager_port_death

#include <kern/server_loop.c>

#define memory_object_server		inode_pager_server
#include <mach/memory_object_server.c>
#define memory_object_default_server	inode_pager_default_server
#include <mach/memory_object_default_server.c>

void		inode_pager_slave()
{
	thread_t self = current_thread();
	int my_num;

	/*
	 *	Hack:  The slave thread's number is communicated to it
	 *	in the reply_port field of its thread structure.
	 *	No problem, as long as we remember to clear this field
	 *	before Mig operations try to use it.
	 */

	my_num = (int) self->reply_port;
	self->reply_port = PORT_NULL;

	SERVER_LOOP(inode_pager_sets[my_num].ipset_set, FALSE);
}

void		inode_pager()
{
	extern void task_name();
	memory_object_t	t;
	int i;

	task_name(SERVER_NAME);

	/*
	 *	Initialize the name port hashing stuff.
	 */

	inode_port_hash_init();

	lock_init(&inode_pager_setup_lock, TRUE);

	inode_pager_task = current_task();
	inode_pager_self = task_self();

	/*
	 *	We are the default pager.
	 *	Initialize the "default pager" port.
	 */

	if (port_allocate(inode_pager_self, &inode_pager_default)
							!= KERN_SUCCESS)
		panic("inode_pager: can't allocate default port");
	if (port_set_backlog(inode_pager_self, inode_pager_default, 2)
							!= KERN_SUCCESS)
		panic("inode_pager: can't set backlog on default pager");

	t = inode_pager_default;
	(void) vm_set_default_memory_manager(host_priv_self(), &t);

	if (inode_pager_num_sets < 1)
		panic("inode_pager: number of sets less than one");

	inode_pager_sets = (inode_pager_set_t)
		kalloc((inode_pager_num_sets * sizeof *inode_pager_sets));
	if (inode_pager_sets == 0)
		panic("inode_pager: can't allocate sets");

	for (i = 0; i < inode_pager_num_sets; i++) {
		inode_pager_set_t ipset = &inode_pager_sets[i];
		port_t name;

		if (port_set_allocate(inode_pager_self, &name) != KERN_SUCCESS)
			panic("inode_pager: cannot create port set");

		ipset->ipset_set = name;
		ipset->ipset_count = 0;
		ipset->ipset_thread = THREAD_NULL;
		ipset_buffer_allocate(ipset);
	}

	/*
	 *	Instead of using inode_pager_add,
	 *	put the default port into set 0 and
	 *	don't increment ipset_count.
	 */

	if (port_set_add(inode_pager_self,
			 inode_pager_sets[0].ipset_set, inode_pager_default)
							!= KERN_SUCCESS)
		panic("inode_pager: cannot enable default port");
	inode_pager_sets[0].ipset_thread = current_thread();

	for (i = 1; i < inode_pager_num_sets; i++) {
		inode_pager_set_t ipset = &inode_pager_sets[i];

		ipset->ipset_thread = inode_pager_start_slave(i);
	}

	SERVER_LOOP(inode_pager_sets[0].ipset_set, TRUE);
}

void 	inode_pager_bootstrap()
{
	register vm_size_t	size;

	/*
	 *	Initialize zone of paging structures.
	 */

	size = (vm_size_t) sizeof(struct istruct);
	istruct_zone = zinit(size,
			(vm_size_t) 10000*size,	/* XXX */
			PAGE_SIZE,
			FALSE, "inode pager structures");

	queue_init(&pager_files);
	pager_file_count = 0;
}

#else	MACH_VFS
#include <builtin/old_pager.c>
#endif	MACH_VFS
