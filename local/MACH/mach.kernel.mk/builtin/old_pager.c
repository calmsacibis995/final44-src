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
 * $Log:	old_pager.c,v $
 * Revision 2.6  90/07/20  10:28:50  mrt
 * 	20-Jul-89 Mary Thompson (mrt)
 * 		Added a few missing declarations.
 * 
 * Revision 2.5  90/07/03  16:34:32  mrt
 * 	Fix pagein buffer management code to reuse buffer space when
 * 	I/O fails instead of abandoning it.  Set base address for vm_map_find.
 * 	[90/06/29            dlb]
 * 	Use power of 2 backoff to get smaller buffer if vm_map_find fails
 * 	in ipset_buffer_allocate.
 * 	[90/06/28            dlb]
 * 	Upgrade to use memory_object_data_supply (page stealing).
 * 	Delete all !MACH_XP code.
 * 	[90/06/28            dlb]
 * 	Use privileged host port for vm_set_default_memory_manager.
 * 	[90/06/12  14:43:55  dlb]
 * 
 * Revision 2.4  89/12/23  14:20:25  rpd
 * 	Added dummy mach_swapon.
 * 
 * Revision 2.3  89/12/22  16:35:33  rpd
 * 	MACH_XP:  Added dummy inode_pager_num_sets variable,
 * 	to keep bsd/init_main.c happy.  Updated SERVER_LOOP call.
 * 
 * Revision 2.2  89/12/22  16:26:58  rpd
 * 	Created from the X117 builtin/inode_pager.c, for use in
 * 	non-MACH_VFS and non-MACH_XP kernels.
 * 	[89/12/22  16:16:05  rpd]
 * 
 * Revision 2.36  89/10/11  13:46:58  dlb
 * 	Change to calling sequence of vm_map_pageable.
 * 	[89/01/26            dlb]
 * 
 * Revision 2.35  89/10/03  19:22:07  rpd
 * 	Renamed inode_pager_create to istruct_create,
 * 	renamed inode_pager_terminate to inode_pager_dead_pager,
 * 	and rationalized the real names of the memory_object_* functions.
 * 
 * 	Added a separate memory_object_data_unlock, which just panics.
 * 
 * 	When NBC, memory_object_lock_completed now wakes up a thread in vmp_push.
 * 
 * 	Corrected inode_pager_setup to use inode_pager_lookup_external
 * 	instead of inode_pager_lookup.
 * 	[89/10/02  15:31:11  rpd]
 * 
 * 	Changes from NeXT:  Reduced PAGEMAP_THRESHOLD to 64.
 * 	Added code to pf_bmap to grow the page map as needed.
 * 	[89/08/21  18:17:53  rpd]
 * 
 * 	Reworked is_page_initialize.  With any luck,
 * 	it handles pager-files correctly now.
 * 	[89/08/21  02:59:00  rpd]
 * 
 * Revision 2.34  89/08/09  10:11:16  jsb
 * 	Corrected init parameter for VOP_PAGE_WRITE in is_page_initialize.
 * 	[89/08/09  09:53:49  jsb]
 * 
 * Revision 2.33  89/07/30  18:29:06  gm0w
 * 	Removed extraneous "+ amount_sent" in is_page_write().
 * 	[89/07/29            gm0w]
 * 
 * Revision 2.32  89/07/14  15:26:05  rvb
 * 	Added in code to support paging files which contain multiple
 * 	memory objects.  This code originated with Peter King at NeXT
 * 	but has been significantly altered to work here.
 * 	[89/07/06            rfr]
 * 
 * Revision 2.31  89/06/24  23:59:43  jsb
 * 	This file didn't get merged in last time?
 * 	[89/06/24  23:22:51  jsb]
 * 
 * Revision 2.30.1.2  89/06/12  14:51:28  jsb
 * 	Replaced calls to VOP_PAGE_INIT and VOP_RDWR with VOP_PAGE_WRITE.
 * 	Corrected inode locking. Added missing '<< is->paging_shift'.
 * 	[89/06/12  11:27:23  jsb]
 * 
 * Revision 2.30  89/05/31  12:27:49  rvb
 * 	Stylistic change. [af]
 * 
 * Revision 2.29  89/05/11  15:39:39  gm0w
 * 	Minor fixes for NBC code from rfr.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.28  89/05/01  15:21:54  rpd
 * 	Don't initialize task->reply_port here.
 * 	[89/05/01  13:46:09  rpd]
 * 
 * Revision 2.27  89/04/22  15:23:12  gm0w
 * 	Changed back an UNLOCK_INODE that needs to stay an iunlock.
 * 	[89/04/22            gm0w]
 * 	Reimplemented VFS code to use new VOP_PAGE_READ and VOP_PAGE_INIT.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.26  89/04/18  16:42:29  mwyoung
 * 	Use vm_set_default_memory_manager().
 * 
 * 	Provide a runtime parameter for the number of pageins to allow
 * 	per pageout.
 * 	[89/04/07            mwyoung]
 * 
 * Revision 2.25  89/04/05  12:56:25  rvb
 * 	Forward declaration of inode_has_page(), inode_pager_server(),
 * 	and inode_pager_default_server() as boolean_t.
 * 	[89/03/21            rvb]
 * 
 * Revision 2.24  89/03/10  01:28:00  rpd
 * 	More cleanup.
 * 
 * Revision 2.23  89/03/07  03:48:44  rpd
 * 	Moved to builtin/.
 * 
 * Revision 2.22  89/02/26  11:14:47  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.21  89/02/07  22:54:44  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.20  89/01/23  15:33:02  rvb
 * 	Allow MACH_VFS w/o MACH_NFS.
 * 	[89/01/23  14:21:13  rvb]
 * 
 * Revision 2.19  89/01/20  15:50:10  jsb
 * 	Yet another (less slimey) attempt to get inode_pager to work with
 * 	MACH_VFS off.
 * 
 * Revision 2.18  89/01/20  13:08:43  jsb
 * 	If not MACH_VFS, use X69 version of inode_pager.c.
 * 
 * Revision 2.17  89/01/18  15:24:20  jsb
 * 	Fix mistakes made in merge.
 * 
 * Revision 2.16  89/01/18  01:28:21  jsb
 * 	Vnode support. (But not enough to support paging to the net.)
 * 	[89/01/17  11:04:35  jsb]
 * 
 * Revision 2.15  89/01/15  16:39:41  rpd
 * 	Updated includes for the new mach/ directory.
 * 	Use decl_simple_lock_data, simple_lock_addr.
 * 	[89/01/15  15:27:58  rpd]
 * 
 * Revision 2.14  89/01/12  11:16:20  rpd
 * 	Added <kern/std_types.h>.
 * 
 * Revision 2.13  89/01/10  23:33:43  rpd
 * 	Check return status of inode_pager_default allocation.
 * 	[89/01/10  13:36:37  rpd]
 * 	
 * 	Use object_copyin/object_copyout instead of port_copyin/port_copyout.
 * 	[89/01/09  14:50:15  rpd]
 * 
 * Revision 2.12  88/12/19  02:57:32  mwyoung
 * 	Remove more lint.
 * 	[88/12/18            mwyoung]
 * 	
 * 	Identify our task.
 * 	[88/12/12            mwyoung]
 * 	
 * 	Don't iput when encountering a previous paging error in
 * 	inode_pager_timeout, because the iget hasn't been done yet.
 * 	[88/12/06            mwyoung]
 * 	
 * 	MACH_XP: Allow paging to filesystems with large block sizes (by using
 * 	whole filesystem pages for a virtual page anyway).
 * 	
 * 	Change iswap_allocate() to account for wrong block sizes and
 * 	nearly-full filesystems.  Take preferences more seriously.
 * 	Print warnings when paging space is found in later (and less
 * 	desirable) passes.
 * 	[88/12/05            mwyoung]
 * 	
 * 	Use new XPR tags.
 * 	[88/11/22  01:15:22  mwyoung]
 * 	
 * 	Still check for client count in memory_object_terminate handler.
 * 	Restructure that routine to get the required operations out of
 * 	the way first.
 * 	[88/11/17  01:49:45  mwyoung]
 * 	
 * 	Prevent memory_object_terminate from destroying a memory_object
 * 	when another task has send rights.
 * 	
 * 	Forge a memory_object_terminate message when releasing a
 * 	memory_object (acquired through inode_pager_setup()) that
 * 	hasn't been used for mapping.  To do so, the reference must
 * 	be held, but this reference shouldn't prevent destruction.
 * 	Thus, these "dead" references are counted.  But this means
 * 	that memory_object_terminate can't throw away the inode_pager_t
 * 	if there are dead references; therefore, we mark it for
 * 	destruction by the last dead reference.
 * 	
 * 	All this owes to the lack of NO_MORE_SENDERS technology and the
 * 	fact that references are created behind the inode_pager's back
 * 	(in inode_pager_setup()).
 * 	[88/11/10            mwyoung]
 * 	
 * 	Added an empty handler for memory_object_copy().
 * 	[88/11/09            mwyoung]
 * 	
 * 	Fix the non-XP form of inode_uncache_try() also.
 * 	[88/11/06            mwyoung]
 * 	
 * 	Unify the versions of inode_read and inode_write somewhat by
 * 	defining the pager_return_t type internally for MACH_XP.
 * 	[88/11/04            mwyoung]
 * 	
 * 	Clean up inode_pager_t->pager and inode_pager_t->pager_global
 * 	during termination.
 * 	[88/11/04            mwyoung]
 * 	
 * 	Correct copy strategy setting in caching-related calls.  Allow
 * 	strategy to be boot/runtime settable for testing.
 * 	[88/11/03  19:14:07  mwyoung]
 * 
 * Revision 2.11  88/11/14  15:05:28  gm0w
 * 	10-14-88  Michael Young (mwyoung) at Carnegie Mellon
 * 	Recover lost line in inode_pager_terminate_object.
 * 	[88/11/14  14:57:39  mrt]
 * 
 * Revision 2.10  88/10/18  03:42:25  mwyoung
 * 	Eliminate uses of vm_object_uncache in non-MACH_XP clauses.
 * 	[88/10/15            mwyoung]
 * 	
 * 	Documented the data structures and protocols for future reference.
 * 	
 * 	Converted to use all new IPC and memory management primitives, so that
 * 	compatibility code can be destroyed.  Corrected port reference handling.
 * 	
 * 	Allow more than one client to use a memory object.  This can happen
 * 	either because of a race condition during shutdown, or because a client
 * 	has passed on access to the memory object to another host.  [In the
 * 	latter case, we make no consistency guarantees, but try not to crash :-).]
 * 	[88/10/02  17:08:22  mwyoung]
 * 	
 * 	Use the pager_request port for all uncaching operations...
 * 	vm_object_lookup only accepts the control port now.
 * 	
 * 	Add inode_uncache_try(), so that all caching knowledge is buried
 * 	in the inode_pager.  It's unclear why inode_pager_active() isn't
 * 	sufficient to find out, but I don't care to find out why right yet.
 * 	[88/09/18            mwyoung]
 * 	
 * 	Add some tracing code.
 * 	[88/09/18  19:01:22  mwyoung]
 * 	
 * 	Don't use iget() within iswap_allocate(), as it may take a lock
 * 	on a directory inode.  There's no reason that we need a real
 * 	inode anyway.
 * 	[88/08/31            mwyoung]
 * 
 * Revision 2.9  88/08/25  18:24:55  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Use memory_object_data_error when throwing away a pagein
 * 	request, so that the offending thread can get an exception.
 * 	[88/08/20  03:05:31  mwyoung]
 * 	
 * 	MACH_XP: Make a feeble effort to deal with running out of paging
 * 	space -- remember errors on a per-object basis, and throw away
 * 	future requests for error-ridden objects.  [A better solution
 * 	might put aside messages when an error occurs.]
 * 	[88/08/16  04:17:51  mwyoung]
 * 	
 * 	Initialize inode_pager_t->paging inside inode_pager_create.
 * 	[88/08/16  00:32:02  mwyoung]
 * 	
 * 	Add inode_pager_release() to get rid of whatever
 * 	inode_pager_setup() gives out.
 * 	Add size argument to memory_object_create.
 * 	Handle new memory_object_terminate call.
 * 	Remove port_copyout of memory_manager_default to kernel_task.
 * 	[88/08/11  18:52:17  mwyoung]
 * 
 * Revision 2.8  88/08/06  19:24:11  rpd
 * Eliminated use of kern/mach_ipc_defs.h.
 * 
 * Revision 2.7  88/07/23  01:21:49  rpd
 * Changed more occurrences of port_enable to xxx_port_enable.
 * 
 * Revision 2.6  88/07/20  21:09:51  rpd
 * Use old forms of port_allocate and port_enable.
 * 
 * 15-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Attempt to balance pagein requests with pageouts.
 *
 *  8-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Actually free port hash table records.
 *
 * 24-Feb-88  David Golub (dbg) at Carnegie-Mellon University
 *	Handle IO errors on paging (non-XP only).
 *
 * 18-Jan-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Delinted.
 *
 *  6-Jan-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Use pager_data_unavailable when inode_read fails in inode_pagein!.
 *
 *  6-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Move pager_cache() call and text bit handling inside
 *	inode_pager_setup().
 *
 * 24-Nov-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Make all external calls other than inode manipulations go
 *	through IPC.
 *
 *	Condensed history:
 *		Try to avoid deadlock when allocating data structures
 *		 (avie, mwyoung).
 *		Try to printf rather than panic when faced with errors (avie).
 *		"No buffer code" enhancements. (avie)
 *		External paging version. (mwyoung, bolosky)
 *		Allow pageout to ask whether a page has been
 *		 written out.  (dbg)
 *		Keep only a pool of in-core inodes.  (avie)
 *		Use readahead when able. (avie)
 *		Require that inode operations occur on the master
 *		 processor (avie, rvb, dbg).
 *		Combine both "program text" and "normal file" handling
 *		 into one. (avie, mwyoung)
 *		Allocate paging inodes on mounted filesystems (mja);
 *		 allow preferences to be supplied (mwyoung).
 *
 * 12-Mar-86  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	inode_pager.c
 *
 *	"Swap" pager that pages to/from Unix inodes.  Also
 *	handles demand paging from files.
 */
#include <mach_nbc.h>
#include <mach_vfs.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/fs.h>
#include <sys/buf.h>
#include <sys/uio.h>
#include <sys/inode.h>
#include <sys/mount.h>

#include <mach/std_types.h>
#include <mach/mach_types.h>
#include <vm/vm_page.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <kern/parallel.h>
#include <kern/zalloc.h>

#include <vm/vm_object.h>
#include <kern/task.h>
#include <mach/vm_param.h>
#include <kern/kern_obj.h>
#include <kern/kern_port.h>
#include <kern/ipc_copyin.h>
#include <kern/ipc_copyout.h>
#include <kern/queue.h>
#include <mach/memory_object.h>

#include <mach/port.h>
#include <builtin/inode_pager.h>
#include <kern/mfs.h>
#include <kern/host.h>

#include <kern/xpr.h>

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
	queue_chain_t	pf_chain; /* link to other paging files */
	struct	inode	*pf_ip;	/* inode of paging file */
	u_int		pf_count; /* Number of vstruct using this file */
	u_char		*pf_bmap; /* Map of used blocks */
	long		pf_npgs; /* Size of file in pages */
	long		pf_pfree; /* Number of unused pages */
	char		*pf_name; /* Filename of this file */
	boolean_t	pf_prefer;
} *pager_file_t;

#define	PAGER_FILE_NULL	(pager_file_t) 0
#define	MAXPAGERFILES 10
#define	DEFAULT_PAGERFILE	"/etc/vm/swapfile"

int minpagersize = 20971520;

#define	MINPAGERSIZE minpagersize

#if	NBBY == 8
#define BYTEMASK 0xff
#else	NBBY
Define a byte mask for this machine.
#endif	NBBY

/* Should be an integral of sizeof(vm_offset_t) */
#define PAGEMAP_THRESHOLD	64

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

typedef enum {
		IS_OUT,
		IS_IN_MEMORY,
		IS_BUSY
	} inode_pager_state_t;

typedef struct istruct {
	queue_chain_t	lru_links;	/* LRU queue links */
	int		client_count;	/* How many memory_object_init's
					 * have we received
					 */
	int		dead_references;/* Number of references that don't
					 * prevent destruction
					 */
	boolean_t	free_me;	/* Should the last dead reference
					 * free the structure?
					 * A poor man's reference count.
					 */
	int		use_count;	/* How many times is the inode
					 * in use?
					 */
	inode_pager_state_t state;	/* istruct state */
	memory_object_t	pager;		/* Pager port */
	port_t		pager_request;	/* Known request port */
	port_t		pager_name;	/* Known name port */
	memory_object_t	pager_global;	/* XXX global name */
	port_t		pager_request_global; /* XXX (global) request port */
	int		errors;		/* Pageout error count */
	int		paging_shift;	/* How to adjust for fs block size */

	int		size;		/* size of this chunk in pages*/
	pager_file_t	pf_info;	/* Pager file this uses */
	vm_offset_t	**pmap;		/* Map of pages into paging file */

	unsigned int
	/* boolean_t */	queued:1,	/* on LRU queue? */
			cached:1,	/* Can be cached? */
			paging:1,	/* inode used for paging */
			swapfile:1;	/* inode is a remote swapfile */
	union {
		struct {
			dev_t		dev;	/* device */
			struct fs	*fs;	/* file system */
			ino_t		ino;	/* inode */
		} fs_ip;
		struct inode	*ip;	/* in memory inode */
	} inode;
	struct identity *identity;	/* identity */
} *inode_pager_t;

#define INODE_PAGER_NULL	((inode_pager_t) 0)

#if	!MACH_NBC
/*
 *	Nullify calls to mfs_uncache
 */
#define	mfs_uncache(ip)
#endif	!MACH_NBC

task_t		inode_pager_task;
port_t		inode_pager_self;
port_set_name_t	inode_pager_enabled_set;

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
	register	i;

	inode_port_hash_zone = zinit((vm_size_t) sizeof(struct inode_port_entry),
			(vm_size_t) 10 * ninode * sizeof(struct inode_port_entry),
			PAGE_SIZE, FALSE, "inode_pager port hash");

	for (i = 0; i < INODE_PORT_HASH_COUNT; i++) 
		queue_init(&inode_port_hashtable[i]);
}

private
inode_pager_t	inode_pager_lookup(name_port)
	register port_t name_port;
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
	port_reference((kern_port_t) name_port);
	object_copyout(inode_pager_task, (kern_obj_t) name_port,
		       MSG_TYPE_PORT, &name_port);
	return(inode_pager_lookup(name_port));
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
#if	!MACH_VFS
boolean_t	inode_has_page();
#endif	!MACH_VFS

boolean_t	inode_pager_server();
boolean_t	inode_pager_default_server();

/*
 *	Basic inode pager data structures
 */

int			istruct_qcount;		/* # in the queue */
int			istruct_qmax;		/* max to put in queue */
int			istruct_released;	/* # not in memory */
zone_t			istruct_zone;
queue_head_t		istruct_queue;
decl_simple_lock_data(,	istruct_lock)


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
 *	Routine:	istruct_put
 *	Function:
 *		Release one use of this inode_pager_t
 *	Implementation:
 *		Put this inode_pager structure at the end of
 *		an LRU reclaim list.  If over the limit on that list,
 *		take some elements off, releasing their in-memory inode
 *		references.
 */
private
void		istruct_put(is)
	register inode_pager_t	is;
{
	register struct inode *ip;

	simple_lock(&istruct_lock);
	is->use_count--;

	assert(is->use_count >= 0);

	ip = is->inode.ip;


	/*
	 *	Only queue files used for paging (?) but not pointing
	 *	to blocks in a swapfile.
	 */

	if (is->paging && !is->swapfile) {
		/*
		 *	If it's currently on the reclaim list (i.e.,
		 *	it's not a brand new structure), remove it from
		 *	its old place.
		 */
		if (is->queued) {
			queue_remove(&istruct_queue, is, inode_pager_t, 
							 lru_links);
			istruct_qcount--;
		}
		/*
		 *	Only queue structures which aren't in use by this
		 *	module.
		 */
		if (is->queued = (is->use_count == 0)) {
			queue_enter(&istruct_queue, is, inode_pager_t, 
							lru_links);
			istruct_qcount++;
		}
	}

	/*
	 *	If we're over our quota
	 */

	while (istruct_qcount > istruct_qmax) {
		/*
		 *	Select the first candidate
		 */

		if (queue_empty(&istruct_queue))
			break;
		is = (inode_pager_t) queue_first(&istruct_queue);
		queue_remove(&istruct_queue, is, inode_pager_t, lru_links);
		istruct_qcount--;
		istruct_released++;

		/*
		 *	Save the inode's (dev, fs, ino) information.
		 */

		is->queued = FALSE;
		ip = is->inode.ip;
		is->inode.fs_ip.dev = ip->i_dev;
		is->inode.fs_ip.fs = ip->i_fs;
		is->inode.fs_ip.ino = ip->i_number;

		/*
		 *	Release the inode.  Note that we must drop the
		 *	inode_pager queue lock, so we mark this structure
		 *	as busy momentarily.
		 */

		is->state = IS_BUSY;
		simple_unlock(&istruct_lock);
		RELEASE_INODE(ip);
		simple_lock(&istruct_lock);
		is->state = IS_OUT;
		thread_wakeup((int) is);
	}
	simple_unlock(&istruct_lock);
}

/*
 *	istruct_get:
 *
 *	Get an in memory inode corresponding to the specified paging space
 *	and guarantee that it will remain in memory (until furthur action
 *	is taken).
 *
 *	If there is already an in memory inode, we just return it.  If there
 *	is no in memory inode, we do an iget to grab one.
 *
 *	The inode is returned unlocked.
 */
private
struct inode *istruct_get(is)
	inode_pager_t	is;
{
	register struct inode *ip;

	if (is == INODE_PAGER_NULL) {
		panic("istruct_get: null");
		return((struct inode *) 0);
	}

	/*
	 *	Remove possibility of garbage collection.
	 */
	simple_lock(&istruct_lock);
	is->use_count++;
	if (is->queued) {
		queue_remove(&istruct_queue, is, inode_pager_t, lru_links);
		istruct_qcount--;
		is->queued = FALSE;
	}
	while (is->state == IS_BUSY) {
		thread_sleep((int) is, simple_lock_addr(istruct_lock), FALSE);
		simple_lock(&istruct_lock);
	}

	if (is->state == IS_IN_MEMORY) {
		ip = is->inode.ip;
	} else {
		is->state = IS_BUSY;
		simple_unlock(&istruct_lock);
		ip = iget(is->inode.fs_ip.dev,
				  is->inode.fs_ip.fs,
				  is->inode.fs_ip.ino);
		if (ip == (struct inode *) 0)
				panic("istruct_get: unable");
		iunlock(ip);

		ip->i_vm_info->pager = is->pager_global;
		ip->i_vm_info->pager_request = is->pager_request_global;

		iunlock(ip);
		simple_lock(&istruct_lock);
		istruct_released--;
		is->inode.ip = ip;
		is->state = IS_IN_MEMORY;
		thread_wakeup((int) is);
	}
	simple_unlock(&istruct_lock);
	return(ip);
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

	if (pf->pf_pfree == 0)
		return(-1);

	for (bp = 0; bp < howmany(pf->pf_npgs, NBBY); bp++) {
		if (*(pf->pf_bmap + bp) != BYTEMASK) {
			for (i = 0; i < NBBY; i++) {
				if (isclr((pf->pf_bmap + bp), i))
					break;
			}
			break;
		}
	}
	if (bp*NBBY+i > pf->pf_npgs)
		panic("pf_allocate_page");
	
	setbit(pf->pf_bmap,(bp*NBBY+i));
	if (pf->pf_pfree-- == 0)
		printf("inode_pager: paging file is full.\n");

	if (inode_pager_debug)
	    printf("pf_allocate_page returning: %d (%d,%d)\n",bp*NBBY+i,bp,i);
	return(bp*NBBY+i);
}

void
pf_deallocate_page(pf, page)
     register struct pager_file *pf;
     daddr_t page;
{
	if (page > (daddr_t) pf->pf_npgs)
		panic("pf_deallocate_page");
	clrbit(pf->pf_bmap, page);
	if (pf->pf_pfree++ == 1) {
		printf("inode_pager: paging file is available again.\n");
	}
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
	struct inode * ip;
	/*
	 *	XXX This can still livelock -- if the
	 *	pageout daemon needs an inode_pager record
	 *	it won't get one until someone else
	 *	refills the zone.
	 */

	is = (struct istruct *) zalloc(istruct_zone);
	if (is == INODE_PAGER_NULL) return(is);
	is->pager_global = MEMORY_OBJECT_NULL;
	is->pager_request_global = PORT_NULL;
	is->pager = MEMORY_OBJECT_NULL;
	is->pager_request = PORT_NULL;

	is->size = atop(size);
	
	if (INDIRECT_PAGEMAP(is->size)) {
		is->pmap = (vm_offset_t **) kalloc(INDIRECT_PAGEMAP_SIZE(is->size));
	} else {
		is->pmap = (vm_offset_t **) kalloc(PAGEMAP_SIZE(is->size));
	}
	if (is->pmap == (vm_offset_t **) 0) {
		/*
		 * We can't sleep here, so if there are no free pages, then
		 * just return nothing.
		 */
		zfree(istruct_zone, (vm_offset_t) is);
		return(INODE_PAGER_NULL);
	}

	if (INDIRECT_PAGEMAP(is->size)) {
		for (i = 0; i < INDIRECT_PAGEMAP_ENTRIES(is->size);
		     is->pmap[i++] = NULL);
	} else {
	       	for (i = 0; i < is->size; is->pmap[i++] = (vm_offset_t *) -1);
	}

	is->client_count = 0;
	is->dead_references = 0;
	is->free_me = FALSE;
	is->use_count = 1;
	is->paging = TRUE;
	is->swapfile = TRUE;
	
	ip = is->inode.ip = pf->pf_ip;
	is->state = IS_IN_MEMORY;

	u.u_identity->id_ref++;
	is->identity = u.u_identity;
	is->queued = FALSE;
	is->errors = 0;
	is->paging_shift = 0;
	is->queued = FALSE;
	is->pf_info = pf;
	pf->pf_count++;

	istruct_put(is);

	return(is);
}

/*
 *	pf_bmap
 *
 *	Return f_offset into a pager file for a given f_offset into an
 *	object backed by the pager file.
 *
 *	Returns: -1 page not in pager file or no room left
 */
vm_offset_t
pf_bmap(is, f_offset, flag)
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
		printf("pf_bmap called with %x (%d)\n", f_offset, f_page);

	if (f_page > is->size) {
	    printf("pf_bmap:f_page > is->size (%d, %d)\n",f_page,is->size);
	    return ((vm_offset_t) -1);
	}

	/*
	 * If the object has grown, expand the page map.
	 */
	if (f_page >= is->size) {
		vm_offset_t	**new_pmap;
		int		new_size;

		new_size = f_page + 1;
		if (INDIRECT_PAGEMAP(new_size)) {

			/* Copy info from the old map */
			if (INDIRECT_PAGEMAP(is->size)) {
				if (INDIRECT_PAGEMAP_SIZE(new_size) ==
				    INDIRECT_PAGEMAP_SIZE(is->size)) {
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
				     i < INDIRECT_PAGEMAP_ENTRIES(is->size);
				     i++) {
					new_pmap[i] = is->pmap[i];
				}
				/* And free the old map */
				kfree((vm_offset_t)is->pmap,
				      INDIRECT_PAGEMAP_SIZE(is->size));
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
				for (i = 0; i < is->size; i++) {
					new_pmap[0][i] =
						(vm_offset_t) is->pmap[i];
				}
				/* Initialize the remainder of the block */
				for (i = is->size; i < PAGEMAP_ENTRIES;
				     new_pmap[0][i++] = (vm_offset_t)-1);
				/* And free the old map */
				kfree((vm_offset_t)is->pmap,
				      PAGEMAP_SIZE(is->size));
			}			
		} else {
			/* New map is direct */
			if ((new_pmap = (vm_offset_t **)
			     kalloc(PAGEMAP_SIZE(new_size))) == NULL) {
				return (-1);
			}
			/* Copy info from the old map */
			for (i = 0; i < is->size; i++) {
				new_pmap[i] = is->pmap[i];
			}
			/* Initialize the rest of the new map */
			for (i = is->size; i < new_size;
			     new_pmap[i++] = (vm_offset_t *) -1);
			kfree((vm_offset_t)is->pmap,
			      PAGEMAP_SIZE(is->size));
		}
		is->pmap = new_pmap;
leavemapalone:
		is->size = new_size;
	}

	if (INDIRECT_PAGEMAP(is->size)) {
		if (is->pmap[f_page/PAGEMAP_ENTRIES] == NULL) {
			if (flag == B_READ) {
				return ((vm_offset_t)-1);
			}
			if ((is->pmap[f_page/PAGEMAP_ENTRIES] =
			    (vm_offset_t *) kalloc(PAGEMAP_THRESHOLD)) == NULL) {
				return((vm_offset_t)-1);
			}
			for (i = 0; i < PAGEMAP_ENTRIES;
			     is->pmap[f_page/PAGEMAP_ENTRIES][i++] =
			     (vm_offset_t)-1);
		}
		if (is->pmap[f_page/PAGEMAP_ENTRIES][f_page%PAGEMAP_ENTRIES] ==
		    -1) {
			if (flag == B_READ) {
				return((vm_offset_t)-1);
			}
			if ((newpage = pf_allocate_page(is->pf_info)) ==
			    -1) {
				return((vm_offset_t)-1);
			}
			is->pmap[f_page/PAGEMAP_ENTRIES]
				[f_page%PAGEMAP_ENTRIES] = newpage;
		}
		newoffset = (f_offset&page_mask) +
			ptoa(is->pmap[f_page/PAGEMAP_ENTRIES]
				[f_page%PAGEMAP_ENTRIES]);
	} else {
		if (is->pmap[f_page] == (vm_offset_t *) -1) {
			if (flag == B_READ ||
			    (newpage = pf_allocate_page(is->pf_info)) ==
			    -1) {
				return((vm_offset_t)-1);
			}
			is->pmap[f_page] = (vm_offset_t *)newpage;
		}
		newoffset = (f_offset&page_mask) +
			ptoa((vm_offset_t)is->pmap[f_page]);
	}

	if (inode_pager_debug)
		printf("pf_bmap returning %x\n", newoffset);
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
inode_pager_t	istruct_create(ip, canwait, paging)
	register struct inode	*ip;
	boolean_t		canwait;
	boolean_t		paging;
{
	register inode_pager_t	is;

	/*
	 *	XXX This can still livelock -- if the
	 *	pageout daemon needs an inode_pager record
	 *	it won't get one until someone else
	 *	refills the zone.
	 */

#ifdef	lint
	canwait++;
#endif	lint
	is = (struct istruct *) zalloc(istruct_zone);

	if (is == INODE_PAGER_NULL)
		return(is);

	is->pager_global = MEMORY_OBJECT_NULL;
	is->pager_request_global = PORT_NULL;
	is->pager = MEMORY_OBJECT_NULL;
	is->pager_request = PORT_NULL;
	is->client_count = 0;
	is->dead_references = 0;
	is->free_me = FALSE;
	is->use_count = 1;
	is->paging = paging;
	is->swapfile = FALSE;
	ip->i_vm_info->pager = is->pager_global;
	ip->i_vm_info->pager_request = is->pager_request_global;
	is->state = IS_IN_MEMORY;

	is->inode.ip = ip;
	u.u_identity->id_ref++;
	is->identity = u.u_identity;
	is->queued = FALSE;
	is->errors = 0;

	is->paging_shift = 0;
	if (paging) {
		int		block_size;

		for (block_size = ip->i_fs->fs_bsize;
		     block_size > PAGE_SIZE;
		     block_size >>= 1)
			is->paging_shift++;
	}

	INCR_INODE(ip);

	istruct_put(is);

	XPR(XPR_INODE_PAGER, ("istruct_create: returning %x", (int) is));
	return(is);
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
memory_object_t	inode_pager_setup(ip, is_text, can_cache)
	struct inode	*ip;
	boolean_t	is_text;
	boolean_t	can_cache;
{
	register pager_file_t	pf;
	inode_pager_t		is;

	unix_master();

	if (ip == (struct inode *) 0) return(MEMORY_OBJECT_NULL);

	if (is_text) ip->i_flag |= ITEXT;

	if (ip->i_vm_info->pager == MEMORY_OBJECT_NULL) {
		/*
		 * Check to make sure this isn't in use as a pager file.
		 */
		for (pf = (pager_file_t) queue_first(&pager_files);
		     !queue_end(&pager_files, &pf->pf_chain);
		     pf = (pager_file_t) queue_next(&pf->pf_chain)) {
			if (pf->pf_ip == ip) {
			    uprintf("Can't page directly to a paging file.\n");
			    return(MEMORY_OBJECT_NULL);
			}
		}
		is = istruct_create(ip, TRUE, FALSE);

		if (is != INODE_PAGER_NULL) {
			if (port_allocate(inode_pager_task, &is->pager) != 
								KERN_SUCCESS)
			    panic("inode_pager_setup: can't allocate port");
			if (port_set_add(inode_pager_task,
					inode_pager_enabled_set,
					is->pager)
			    != KERN_SUCCESS)
				panic("inode_pager_setup: can't enable");

			inode_port_hash_insert(is->pager, is);

			/*
			 *	Get the global name for the port.
			 */

			(void) object_copyin(inode_pager_task, is->pager,
					     MSG_TYPE_PORT, FALSE,
					     (kern_obj_t *) &is->pager_global);

			/*
			 *	Save the global name in the inode.
			 *
			 *	[This step comes last so that we've got the association
			 *	entirely set up before the pager value can be grabbed
			 *	from the inode structure by someone else while we're
			 *	blocked in the port operations.]
			 */

			ip->i_vm_info->pager = is->pager_global;

			is->cached = can_cache;
		}
	} else {
		inode_pager_t is;

		is = inode_pager_lookup_external(ip->i_vm_info->pager);

		if (is != INODE_PAGER_NULL && is->identity != NULL) {
			free_identity(is->identity);
			u.u_identity->id_ref++;
			is->identity = u.u_identity;
		}
	}

	assert(ip->i_vm_info->pager != MEMORY_OBJECT_NULL);

	port_reference(ip->i_vm_info->pager);

	unix_release();
	return(ip->i_vm_info->pager);
}

/*
 *	Routine:	inode_pager_no_more_senders
 *	Purpose:
 *		Tell whether there are senders (other than the
 *		number of given dead references) to the
 *		given object.
 */
boolean_t	inode_pager_no_more_senders(object, dead_references)
	memory_object_t	object;		/* GLOBAL name of memory object */
	int		dead_references;
{
	kern_obj_t	port_thingy = (kern_obj_t) object;
	int		count;

	if (object == PORT_NULL)
		return(TRUE);

	simple_lock(&port_thingy->obj_data_lock);
	count = port_thingy->obj_references;
	simple_unlock(&port_thingy->obj_data_lock);

	/*
	 *	If the inode_pager has the only port rights,
	 *	then there should be the following references:
	 *		1 (send, receive, owner) for inode_pager_task
	 *		1 port set membership
	 *		1 for an inode_pager_t->pager_global field
	 */

	return((count - dead_references) <= 3);
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
	inode_pager_t	is = inode_pager_lookup_external(object);

	/*
	 *	If we have the only reference to the object,
	 *	and chose not to map it, we have to forge
	 *	the termination.  [Note that this is the
	 *	external form of memory_object_terminate,
	 *	and results in an IPC event that will be
	 *	processed in the inode_pager task context,
	 *	not ours.  We're in no hurry.]
	 *
	 *	We have to hold a reference in order to sen
	 *	the termination message.  Unfortunately, that
	 *	reference might prevent the inode_pager task
	 *	from actually performing the intended destruction.
	 *	Thus, we attach to the inode_pager_t a count of
	 *	references that	don't affect destruction.
	 *
	 *	XXX If NO_MORE_SENDERS support becomes available,
	 *	we don't have to check this manually.
	 *	XXX Alternatively, if we could atomically make
	 *	the memory_object_terminate call and lose our
	 *	reference, then this can be greatly simplified...
	 *	but we don't want to make that sort of assumption
	 *	(i.e., that after a message is queued, the caller
	 *	won't be put to sleep) about the IPC system.
	 */

	unix_master();

	if (is != INODE_PAGER_NULL) {
		int		dead;

		dead = ++is->dead_references;
		if (inode_pager_no_more_senders(object, dead))
			memory_object_terminate(object, PORT_NULL, PORT_NULL);
	}

	if (object != MEMORY_OBJECT_NULL)
		port_release(object);

	if (is != INODE_PAGER_NULL) {
		if (--is->dead_references == 0 && is->free_me) {
			if (is->swapfile) {
				pf_dealloc(is);
			} else {
				free_identity(is->identity);
				zfree(istruct_zone, (vm_offset_t) is);
			}
		}
	}

	unix_release();
}

/*
 *	Routine:	inode_pager_active
 *	Purpose:
 *		Indicates whether the given memory object is
 *		in use as a text file.  [If not, it can be flushed
 *		from the memory cache and written as a file.]
 *	NOTE:
 *		This call does not run in the context of the inode_pager.
 */
boolean_t	inode_pager_active(pager)
	memory_object_t	pager;
{
	if (pager != MEMORY_OBJECT_NULL) {
		inode_pager_t	is;

		if ((is = inode_pager_lookup_external(pager)) == INODE_PAGER_NULL) {
			printf("inode_pager_active: lookup of pager 0x%x failed\n", pager);
			return(FALSE);
		}
		return(is->paging);
	}
	return(FALSE);
}

typedef	int		pager_return_t;

#if	!MACH_VFS
pager_return_t	inode_read();	/* forward */
pager_return_t	inode_write();	/* forward */
#endif	!MACH_VFS

/*
 *	Make all calls involving the kernel interface go through IPC.
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


int		inode_pager_pagein_count = 0;
int		inode_pager_pageout_count = 0;
vm_offset_t	inode_pager_buf_base;
vm_offset_t	inode_pager_buf_ptr;
vm_offset_t	inode_pager_buf_end;
vm_object_t	inode_pager_buf_object;

#define	INODE_PAGER_BUFFER_SIZE		32*PAGE_SIZE

typedef struct data_request {
	queue_chain_t	others;
	memory_object_t	pager;
	port_t		reply_to;
	vm_offset_t	offset;
	vm_size_t	length;
	vm_prot_t	protection_required;
} *data_request_t;
	
queue_head_t	data_request_queue;
zone_t		data_request_zone;
msg_option_t	inode_pager_receive_option = MSG_OPTION_NONE;

void
is_page_initialize(is, ip, offset, addr)
	inode_pager_t	is;
	struct inode *	ip;
	vm_offset_t	offset;
	vm_offset_t	addr;
{
	if (!is->paging)
		panic("is_page_initialize");

	/*
	 *	This should work just like is_page_write,
	 *	except that it only writes the page if it
	 *	hasn't been written before.  If this is a swapfile,
	 *	then we can check our page-map and see if we
	 *	have already written this page.  Otherwise,
	 *	we have to rely on the init argument to VOP_PAGE_WRITE.
	 *	(Or inode_has_page, if not-MACH_VFS.)
	 */

	if (is->swapfile) {
		if (pf_bmap(is, offset, B_READ) == (vm_offset_t) -1) {
#if	MACH_VFS
			vm_offset_t	actual_offset;

			actual_offset = pf_bmap(is, offset, B_WRITE);
			if (actual_offset == (vm_offset_t) -1)
				return;

			if (VOP_PAGE_WRITE(ITOV(ip), addr, PAGE_SIZE,
					   actual_offset << is->paging_shift,
					   is->identity, FALSE))
				is->errors++;
#else	MACH_VFS
 	    		memory_object_data_write(is->pager, is->pager_request,
						 offset, addr, PAGE_SIZE);
#endif	MACH_VFS
		}
	} else {
#if	MACH_VFS
		if (VOP_PAGE_WRITE(ITOV(ip), addr, PAGE_SIZE,
				   offset << is->paging_shift,
				   is->identity, TRUE))
			is->errors++;
#else	MACH_VFS
		if (inode_has_page(is->pager, offset << is->paging_shift)) {
 	    		memory_object_data_write(is->pager, is->pager_request,
						 offset, addr, PAGE_SIZE);
		}
#endif	MACH_VFS
	}
}

kern_return_t
is_page_read(is, ip, offset, addr)
	inode_pager_t	is;
	struct inode *	ip;
	vm_offset_t	offset;
	vm_offset_t	addr;
{
	vm_offset_t	actual_offset;
	kern_return_t	ret;

	if (is->swapfile) {
		actual_offset = pf_bmap(is, offset, B_READ);
	} else {
		actual_offset = offset;
	}

	if (actual_offset == (vm_offset_t)-1) return (EINVAL);

#if	MACH_VFS
	ret = VOP_PAGE_READ(ITOV(ip), addr, PAGE_SIZE,
			(actual_offset << is->paging_shift), is->identity);
#else	MACH_VFS
	ret = inode_read(ip, addr, (actual_offset << is->paging_shift));
#endif	MACH_VFS

	inode_pager_pagein_count++;

	return (ret);
}


void
is_page_write(is, ip, offset, addr)
	inode_pager_t	is;
	struct inode *	ip;
	vm_offset_t	offset;
	vm_offset_t	addr;
{
	vm_offset_t	actual_offset;
	vm_offset_t	size = PAGE_SIZE;

	if (is->swapfile) {
		actual_offset = pf_bmap(is, offset, B_WRITE);
	} else {
		actual_offset = offset;
	}

	if (actual_offset == (vm_offset_t)-1) return;

#if	MACH_NBC
	if (!is->paging) {
		/*
		 *	Ensure that a paging operation doesn't
		 *	accidently extend a "mapped" file.
		 */
		if (actual_offset + size > ip->i_vm_info->inode_size)
			size = ip->i_vm_info->inode_size - actual_offset;
	}
#endif	MACH_NBC

#if	MACH_VFS
	if (VOP_PAGE_WRITE(ITOV(ip), addr, size,
			   actual_offset<<is->paging_shift,
			   is->identity, FALSE)) {
		is->errors++;
	}
#else	MACH_VFS
	ilock(ip);
	if (inode_write(ip, addr, size,
			actual_offset << is->paging_shift)) {
		printf("pageout: write error, error = %d\n", u.u_error);
		u.u_error = 0;
		is->errors++;
	}
	iunlock(ip);
#endif	MACH_VFS

	inode_pager_pageout_count++;
}

/*
 *	inode_pager_buffer_allocate:  Allocate buffer space.
 *
 *	Allocate buffer space.  This buffer is backed by a newly created
 *	vm_object so the page stealing code will do the right thing.
 */

void inode_pager_buffer_allocate()
{
	register vm_object_t	object;
	register size_t		size;

	/*
	 *	Note: we don't hold a reference for the buffer object.
	 *	That would confuse the page stealing code.  Instead
	 *	we rely on the map entry to hold the reference as long
	 *	as any of the object is mapped.
	 */

	size = INODE_PAGER_BUFFER_SIZE;
	object = vm_object_allocate(size);
	inode_pager_buf_object = object;

	/*
	 *	Under normal circumstances, we should be able to get
	 *	a complete buffer of INODE_PAGER_BUFFER_SIZE.  But under
	 *	heavy paging traffic, we may have to settle for less
	 *	due to map fragmentation.  This code assumes that
	 *	INODE_PAGER_BUFFER_SIZE is a power of 2 multiple of PAGE_SIZE.
	 */

	inode_pager_buf_base = vm_map_min(inode_pager_task->map);
	while (vm_map_find(inode_pager_task->map, object, 0,
			&inode_pager_buf_base, size, TRUE)
		!= KERN_SUCCESS) {

		    size = size/2;
		    if (size < PAGE_SIZE)
			    panic("inode_pager_buffer_allocate: no space");

		    inode_pager_buf_base = vm_map_min(inode_pager_task->map);
	}

	inode_pager_buf_ptr = inode_pager_buf_base;
	inode_pager_buf_end = inode_pager_buf_base + size;
}

kern_return_t	
memory_object_data_request(pager, reply_to, offset,length, protection_required)
	memory_object_t	pager;
	port_t		reply_to;
	vm_offset_t	offset;
	vm_size_t	length;
	vm_prot_t	protection_required;
{
	register
	data_request_t	entry = (data_request_t)zalloc(data_request_zone);
		
	if (inode_pager_debug)
		printf("%s: pager=%d, offset=0x%x, length=0x%x\n",
			"memory_object_data_request(inode_pager)",
			pager, offset, length);

	if (length != PAGE_SIZE) panic("inode_pagein: bad length");

	/*
	 *	Queue this request until we're not busy.
	 */

	entry->pager = pager;
	entry->reply_to = reply_to;
	entry->offset = offset;
	entry->length = length;
	entry->protection_required = protection_required;
	queue_enter(&data_request_queue, entry, data_request_t, others);

	XPR(XPR_INODE_PAGER_DATA, 
	 ("memory_object_data_request(inode_pager): pager 0x%x, offset 0x%x",
         entry->pager, entry->offset));

	/*
	 *	Time out when there's nothing else to do.
	 */

	inode_pager_receive_option = RCV_TIMEOUT;

	/*
	 *	XXX May be necessary to check for queue buildup.
	 */

	return(KERN_SUCCESS);
}

void
inode_pager_timeout()
{
	inode_pager_t	is;
	register
	struct inode	*ip;
	int		ret;
	register
	data_request_t	entry;
	vm_offset_t	entry_offset;
	kern_return_t	result = KERN_SUCCESS;
	register
	vm_offset_t	buffer;
	vm_page_t	m;

	/*
	 *	If there are no pending pagein requests
	 */

	if (queue_empty(&data_request_queue)) {
		/*
		 *	Then wait synchronously for the next
		 *	request.
		 */

		inode_pager_receive_option = MSG_OPTION_NONE;
		return;
	}

	/*
	 *	Process exactly one pagein request, but continue
	 *	to accept timeouts on message receive operations.
	 */

	queue_remove_first(&data_request_queue, entry, data_request_t, others);

	XPR(XPR_INODE_PAGER_DATA, 
		("inode_pager_timeout: pager 0x%x, offset 0x%x",
		entry->pager, entry->offset));

	if (inode_pager_debug)
		printf("inode_pager_timeout: pager=%d, offset=%d\n",
			entry->pager, entry->offset);

	if ((is = inode_pager_lookup(entry->pager)) == INODE_PAGER_NULL) {
		/*
		 *	This object was terminated while this
		 *	request was queued.  Just ignore it.
		 *	[A pagein request may also have been aborted
		 *	while it was queued.  It doesn't hurt to
		 *	provide data anyway, even for a totally unrelated
		 *	object.]
		 */

		result = KERN_SUCCESS;
		goto cleanup;
	}

	if (is->errors) {
		printf("inode_pager_timeout: dropping request because of");
		printf(" previous paging errors\n");
		result = memory_object_data_error(entry->reply_to,
				entry->offset, PAGE_SIZE,
				KERN_FAILURE);

		goto cleanup;
	}
		
	unix_master();

	/*
	 *	Get next buffer.
	 */
	if (inode_pager_buf_ptr == inode_pager_buf_end)
		inode_pager_buffer_allocate();

	buffer = inode_pager_buf_ptr;
	inode_pager_buf_ptr += PAGE_SIZE;

	/*
	 *	Allocate a physical page for this buffer and map it in
	 *	for the I/O.  This works, but a more general solution
	 *	might be a good idea.
	 */
	 
	while ((m = vm_page_alloc(inode_pager_buf_object,
			buffer - inode_pager_buf_base)) == VM_PAGE_NULL) {
				VM_WAIT;
	}
	pmap_enter(kernel_pmap, buffer, VM_PAGE_TO_PHYS(m),
		VM_PROT_READ|VM_PROT_WRITE, TRUE);

	/*
	 *	Read the page into the buffer and then unmap it.
	 *	memory_object_data_supply can steal the page
	 *	without mapping it in.
	 */

	ip = istruct_get(is);
	LOCK_INODE(ip);
	ret = is_page_read(is, ip, entry->offset, buffer);

	pmap_remove(kernel_pmap, buffer, buffer + PAGE_SIZE);
	if (ret) {
		VM_PAGE_FREE(m);
		inode_pager_buf_ptr = buffer;
	}
	else {
		/*
		 *	Clear busy, wakeup should never happen.
		 */
		PAGE_WAKEUP_DONE(m);
	}

	switch(ret) {
		case 0:
			result = memory_object_data_supply(
					entry->reply_to, entry->offset,
					buffer, PAGE_SIZE, TRUE,
					VM_PROT_NONE,
					FALSE, PORT_NULL);
			break;
		case EINVAL:
			result = memory_object_data_unavailable(
					entry->reply_to, entry->offset,
					PAGE_SIZE);
			break;
		case EIO:
			result = memory_object_data_error(
					entry->reply_to, entry->offset,
					PAGE_SIZE, KERN_FAILURE);
			break;
		default:
			panic("inode_pagein: bogus return from VOP_PAGE_READ");
	}
	UNLOCK_INODE(ip);
	istruct_put(is);

	unix_release();

 cleanup:;

	zfree(data_request_zone, (vm_offset_t) entry);

	if (result != KERN_SUCCESS && result != KERN_NOT_RECEIVER)
		printf("inode_pager_timeout: bad result (%d)\n", result);
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
	struct inode	*ip;
	vm_offset_t	amount_sent;
	vm_offset_t	f_offset;

#ifdef	lint
	pager_request++;
#endif	lint

	XPR(XPR_INODE_PAGER_DATA, 
	("memory_object_data_initialize(inode_pager): pager 0x%x, offset 0x%x",
	pager, offset));

	if (inode_pager_debug)
		printf("%s: pager=%d, offset=0x%x, length=0x%x\n",
			"memory_object_data_initialize(inode_pager)",
			pager, offset, data_cnt);

	if ((data_cnt % PAGE_SIZE) != 0) {
	    printf("memory_object_data_initialize: not a multiple of a page");
	    data_cnt = round_page(data_cnt);
	}

	unix_master();
	is = inode_pager_lookup(pager);
	ip = istruct_get(is);

	for (amount_sent = 0;
	     amount_sent < data_cnt;
	     amount_sent += PAGE_SIZE) {
		is_page_initialize(is,ip,offset+amount_sent,addr+amount_sent);
	}

	istruct_put(is);
	unix_release();

#if	MACH_VFS
	if (vm_deallocate(inode_pager_self, addr, data_cnt) != KERN_SUCCESS)
		panic("memory_object_data_initialize: deallocate failed");
#endif	MACH_VFS

	return(KERN_SUCCESS);
}

int	inode_pager_in_out_ratio = 4;

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
	register struct inode	*ip;
	inode_pager_t	is;
	vm_offset_t	f_offset;

#ifdef	lint
	pager_request++;
#endif	lint

	XPR(XPR_INODE_PAGER_DATA, 
	 ("memory_object_data_write(inode_pager): pager 0x%x, offset 0x%x",
	 pager, offset));

	if (inode_pager_debug)
		printf("%s: pager=%d, offset=0x%x, length=0x%x\n",
			"pager_data_write(inode_pager)",
			pager, offset, data_cnt);

	if ((data_cnt % PAGE_SIZE) != 0) {
		printf("memory_object_data_write: not a multiple of a page");
		data_cnt = round_page(data_cnt);
	}

	unix_master();
	is = inode_pager_lookup(pager);
	ip = istruct_get(is);

	for (amount_sent = 0;
	     amount_sent < data_cnt;
	     amount_sent += PAGE_SIZE) {
		is_page_write(is,ip,offset + amount_sent, addr + amount_sent);
	}

	istruct_put(is);
	unix_release();

	if (vm_deallocate(inode_pager_self, addr, data_cnt) != KERN_SUCCESS)
		panic("inode_data_write: deallocate failed");

	/*
	 *	After each successful pageout, allow some number of
	 *	pending pageins to complete.
	 */

	{ 
		int i;
		for (i = 0; i < inode_pager_in_out_ratio; i++)
			inode_pager_timeout();
	}

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
	struct inode *	ip;

#ifdef	lint
	offset++; length++;
#endif	lint

	unix_master();

	is = inode_pager_lookup(pager);
	if (is == INODE_PAGER_NULL)
		panic("(inode_pager)lock_completed: lookup failed");

	ip = istruct_get(is);

	/*
	 *	A thread in vmp_push (kern/mfs_prim.c) wants to know
	 *	when the pageouts he triggered are finished.
	 *	Because the lock_completed was queued after the
	 *	data_write messages, they must be all done now.
	 */

	thread_wakeup((int) ip->i_vm_info);

	istruct_put(is);
	unix_release();
	return KERN_SUCCESS;

#else	MACH_NBC

#ifdef	lint
	pager++; pager_request++;
	offset++; length++;
#endif	lint

	panic("(vnode_pager)lock_completed: called");
	return KERN_FAILURE;
#endif	MACH_NBC
}

kern_return_t	
memory_object_copy(old_memory_object, old_memory_control, offset, length,
							new_memory_object)
	memory_object_t		old_memory_object;
	memory_object_control_t	old_memory_control;
	vm_offset_t		offset;
	vm_size_t		length;
	memory_object_t		new_memory_object;
{
#ifdef	lint
	old_memory_object++; 
	old_memory_control++; offset++; length++; new_memory_object++;
#endif	lint
	panic("(inode_pager)memory_object_copy: called");
	return KERN_FAILURE;
}

#if	!MACH_VFS
int		inode_read_aheads = 0;
int		inode_read_individuals = 0;

pager_return_t	
inode_read(ip, buffer, f_offset)
	register struct inode	*ip;
	vm_offset_t		buffer;
	vm_offset_t		f_offset;
{
	vm_offset_t	p_offset;	/* byte offset within physical page */
	INODE_DEV_TYPE dev = INODE_DEV(ip);
	register struct fs	*fs;
	daddr_t		lbn, bn;
	int		size;
	long		bsize;
	int		csize, on, n, save_error, err;
	u_long		diff;
	struct buf	*bp;

#define ZERO_PAGE	bzero((caddr_t) buffer, PAGE_SIZE);

	/*
	 *	Get the inode and the offset within it to read from.
	 */

	p_offset = 0;

	fs = ip->i_fs;
	bsize = fs->fs_bsize;
	csize = PAGE_SIZE;

	/*
	 * Be sure that data not in the file is zero filled.
	 * The easiest way to do this is to zero the entire
	 * page now.
	 */

	if (ip->i_size < (f_offset + csize)) {
		ZERO_PAGE;
	}

	/*
	 *	Read from the inode until we've filled the page.
	 */
	do {
		/*
		 *	Find block and offset within it for our data.
		 */
		lbn = lblkno(fs, f_offset);	/* logical block number */
		on  = blkoff(fs, f_offset);	/* byte offset within block */

		/*
		 *	Find the size we can read - don't go beyond the
		 *	end of a block.
		 */
		n = MIN((unsigned)(bsize - on), csize);
		diff = ip->i_size - f_offset;
		if (ip->i_size <= f_offset) {
			if (p_offset == 0) {
				/*
				 * entire block beyond end of file -
				 * doesn't exist
				 */
				return(EINVAL);
			}
			/*
			 * block partially there - zero the rest of it
			 */
			break;
		}
		if (diff < n)
			n = diff;

		/*
		 *	Read the index to find the disk block to read
		 *	from.  If there is no block, report that we don't
		 *	have this data.
		 *
		 *	!!! Assumes that:
		 *		1) Any offset will be on a fragment boundary
		 *		2) The inode has whole page
		 */
		save_error = u.u_error;
		u.u_error = 0;
		/* changes u.u_error! */
		bn = fsbtodb(fs,
			BMAP(ip, lbn, B_READ, (int)(on+n) ));
		err = u.u_error;
		u.u_error = save_error;

		if (err) {
			printf("IO error on pagein: error = %d.\n",err);
			return(EIO);
		}

		if ((long)bn < 0)
			return(EINVAL);

		size = blksize(fs, ip, lbn);

		/*
		 *	Read the block through the buffer pool,
		 *	then copy it to the physical memory already
		 *	allocated for this page.
		 */

		if ((ip->i_lastr + 1) == lbn) {
			inode_read_aheads++;
			bp = breada(dev, bn, size, rablock, rasize);
		} else {
			inode_read_individuals++;
			bp = bread(dev, bn, size);
		}
		ip->i_lastr = lbn;

		n = MIN(n, size - bp->b_resid);
		if (bp->b_flags & B_ERROR) {
			brelse(bp);
			printf("IO error on pagein (bread)\n");
			return(EIO);
		}
		bcopy(bp->b_un.b_addr+on, (caddr_t) buffer + p_offset,
			(unsigned int) n);

		/*
		 *	Account for how much we've read this time
		 *	around.
		 */
		csize -= n;
		p_offset += n;
		f_offset += n;

		if (n + on == bsize || f_offset == ip->i_size)
			bp->b_flags |= B_AGE;
		brelse(bp);

	} while (csize > 0 && n != 0);

	return(0);
}

pager_return_t	
inode_write(ip, addr, csize, f_offset)
	register struct inode	*ip;
	vm_offset_t	addr;
	vm_size_t	csize;
	vm_offset_t	f_offset;	/* byte offset within file block */
{
	vm_offset_t	p_offset;	/* byte offset within physical page */
	INODE_DEV_TYPE dev = INODE_DEV(ip);
	register struct fs	*fs;
	daddr_t		lbn, bn;
	int		size;
	long		bsize;
	int		on, n, save_error, err;
	struct buf	*bp;

	unix_master();

	p_offset = 0;

	fs = ip->i_fs;
	bsize = fs->fs_bsize;

	do {
		lbn = lblkno(fs, f_offset);	/* logical block number */
		on  = blkoff(fs, f_offset);	/* byte offset within block */

		n   = MIN((unsigned)(bsize - on), csize);

		save_error = u.u_error;
		u.u_error = 0;
		/* changes u.u_error! */

		/*
		 *	The B_XXX argument to the bmap() call is used
		 *	by the NBC system to direct inode flushing.
		 */

		bn = fsbtodb(fs, BMAP(ip, lbn, B_WRITE | B_XXX, (int)(on+n) ));
		err = u.u_error;
		u.u_error = save_error;

		if (err || (long) bn < 0) {
			printf("IO error on pageout: error = %d.\n",err);
			unix_release();
			return(EIO);
		}

		if (f_offset + n > ip->i_size) {
			ip->i_size = f_offset + n;
		}

		size = blksize(fs, ip, lbn);

		if (n == bsize)
			bp = getblk(dev, bn, size);
		else
			bp = bread(dev, bn, size);

		n = MIN(n, size - bp->b_resid);
		if (bp->b_flags & B_ERROR) {
			brelse(bp);
			printf("IO error on pageout (bread)\n");
			unix_release();
			return(EIO);
		}
		bcopy((caddr_t) (addr + p_offset), bp->b_un.b_addr+on, 
			(unsigned int) n);

		csize -= n;
		p_offset += n;
		f_offset += n;

		if (n + on == bsize) {
			bp->b_flags |= B_AGE;
			bawrite(bp);
		}
		else
			bdwrite(bp);
		CHGUPD_INODE(ip);

	} while (csize != 0 && n != 0);

	unix_release();
	return(0);
}

/*
 *	inode_has_page:
 *
 *	Parameters:
 *		pager
 *		id		paging object
 *		offset		Offset in paging object to test
 *
 *	Assumptions:
 *		This is only used on shadowing (copy) objects.
 *		If part of the page has been found, we assume that the
 *		entire page is in the inode.
 */
boolean_t 
inode_has_page(pager, offset)
	memory_object_t	pager;
	vm_offset_t	offset;
{
	register struct inode	*ip;
	vm_offset_t	f_offset;	/* byte offset within file block */
	register struct fs	*fs;
	daddr_t		lbn, bn;
	long		bsize;
	int		csize, on, n, save_error, err;
	u_long		diff;
	inode_pager_t	is;

	/*
	 * For now, we do all inode hacking on the master cpu.
	 */

	unix_master();

	if ((is = inode_pager_lookup(pager)) == INODE_PAGER_NULL)
		return(FALSE);

	ip = istruct_get(is);
	f_offset = offset;

	ilock(ip);

	fs = ip->i_fs;
	bsize = fs->fs_bsize;
	csize = PAGE_SIZE;

	/*
	 *	Find block and offset within it for our data.
	 */
	lbn = lblkno(fs, f_offset);	/* logical block number */
	on  = blkoff(fs, f_offset);	/* byte offset within block */

	/*
	 *	Find the size we can read - don't go beyond the
	 *	end of a block.
	 */
	n = MIN((unsigned)(bsize - on), csize);
	diff = ip->i_size - f_offset;
	if (ip->i_size <= f_offset) {
		/*
		 * entire block beyond end of file -
		 * doesn't exist
		 */
		istruct_put(is);
		iunlock(ip);
		unix_release();
		return(FALSE);
	}

	if (diff < n)
		n = diff;

	/*
	 *	Read the index to find the disk block to read
	 *	from.  If there is no block, report that we don't
	 *	have this data.
	 *
	 *	!!! Assumes that:
	 *		1) Any offset will be on a fragment boundary
	 *		2) The inode won't have just part of a page
	 */
	save_error = u.u_error;
	u.u_error = 0;
	/* changes u.u_error! */
	bn = fsbtodb(fs,
		BMAP(ip, lbn, B_READ, (int)(on+n) ));
	err = u.u_error;
	u.u_error = save_error;

	if (err) {
		printf("IO error on has_page: error = %d.\n",err);
		istruct_put(is);
		iunlock(ip);
		unix_release();
		return(TRUE);
	}

	if ((long)bn < 0) {
		istruct_put(is);
		iunlock(ip);
		unix_release();
		return(FALSE);	/* page not in inode */
	}

	/*
	 *	We know that we have at least part of the page.
	 *	Assume it is all there.
	 */

	istruct_put(is);
	iunlock(ip);
	unix_release();
	return(TRUE);
}
#endif	!MACH_VFS

/*
 * 	Routine:	pf_file_init
 *	Function:
 *		Create a pager_file structure for a new pager file.
 *
 *	Arguments:
 *		This file in question is specified by inode pointer.  The
 *		maximum amount of space allocatable is specified as the size.
 *		if size is 0, then there is no limit.
 *	In/Out conditions:
 *		The pointer to the new pager_file is returned.
 */
pager_file_t
pf_file_init(ip, size)
	struct inode *ip;
	long size;
{
#if	MACH_VFS
	struct vattr	vattr;
#endif	MACH_VFS
	register pager_file_t	pf;
	int	error;
	long	i;
#if	MACH_VFS
	struct statfs	fstat;
#endif	MACH_VFS

	/*
	 * Is some other object paging to this file?
	 */
	if (ip->i_vm_info->pager) {
		uprintf("Pager file being paged to as normal file.\n");
		return(PAGER_FILE_NULL);
	}

#if	MACH_VFS
	/*
	 * Clean up the file blocks on an pager file by
	 * truncating to length "size".
	 */
	vattr_null(&vattr);
	vattr.va_size = MAX(size, MINPAGERSIZE);
	error = VOP_SETATTR(ITOV(ip), &vattr, u.u_identity);
	if (error) {
		printf("pf_file_init: truncate failed, error = %d\n",
		       error);
		return(PAGER_FILE_NULL);
	}
#else	MACH_VFS
	itrunc(ip,(u_long)MAX(size, MINPAGERSIZE));
#endif	MACH_VFS

	/*
	 * Initialize the inode_size field
	 */
	ip->i_vm_info->inode_size = size;

	pf = (pager_file_t) kalloc(sizeof(struct pager_file));
	INCR_INODE(ip);	
	pf->pf_ip = ip;
	pf->pf_count = 0;

	/*
	 * If no maximum space is specified, then we should make a map that
	 * can cover the entire disk, otherwise the block map need only
	 * cover the maximum space allowed.
	 */
	if (!size) {
#if	MACH_VFS
		error = VFS_STATFS(ITOV(ip)->v_vfsp, &fstat);
		if (error) {
			kfree((vm_offset_t) pf, sizeof(struct pager_file));
			return(PAGER_FILE_NULL);
		}
		size = fstat.f_blocks * fstat.f_bsize;
#else	MACH_VFS
		size = ip->i_fs->fs_size * ip->i_fs->fs_bsize;
#endif	MACH_VFS
	}

	if (inode_pager_debug)
		printf("Paging file %x size = %d\n", ip, size);

	pf->pf_pfree = pf->pf_npgs = atop(size);
	pf->pf_bmap = (u_char *) kalloc(RMAPSIZE(pf->pf_npgs));
	for (i = 0; i < pf->pf_npgs; i++) {
		clrbit(pf->pf_bmap, i);
	}
	pf->pf_prefer = FALSE;
	/*
	 * Put the new pager file in the list.
	 */
	queue_enter(&pager_files, pf, pager_file_t, pf_chain);
	pager_file_count++;
	return(pf);
}

boolean_t paging_file_initialized = FALSE;
boolean_t use_paging_file = FALSE;

/*
 *	Routine:	pf_default_init
 *	Function:
 *		Locate and initialize the default paging file.
 */
void
pf_default_init()
{
	struct inode	*ip;
	pager_file_t	pf;
	int		error;

#if	MACH_VFS
	struct pathname pn;
	struct vnode * vp;
	vp = (struct vnode *)0;
	if (error = pn_get(DEFAULT_PAGERFILE, UIO_SYSSPACE, &pn)) {
		printf("vnode_pager:Can't initialize %s\n",DEFAULT_PAGERFILE);
		goto bailout;
	}
	error = lookuppn(&pn, FOLLOW_LINK, (struct vnode **)0, &vp);
	pn_free(&pn);
	if (error) {
		printf("vnode_pager:Can't initialize %s\n",DEFAULT_PAGERFILE);
		goto bailout;
	}
	ip = VTOI(vp);
	if ((pf = pf_file_init(ip, 0)) == PAGER_FILE_NULL) {
		printf("vnode_pager:Can't initialize %s\n",DEFAULT_PAGERFILE);
	}
bailout:
	if (vp) {
		VN_RELE(vp);
	}
#else	MACH_VFS
	struct nameidata *ndp = &u.u_nd;
	u.u_error = 0;
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_SYSSPACE;
	ndp->ni_dirp = (DEFAULT_PAGERFILE);
	(ip) = namei(ndp);
	if (!u.u_error) {
		if ((pf = pf_file_init(ip, 0)) == PAGER_FILE_NULL) {
			printf("inode_pager: Can't initialize %s\n",
						       DEFAULT_PAGERFILE);
		}
	}
#endif	MACH_VFS
}

#if 0
/*
 *	Routine:	mach_swapon
 *	Function:
 *		Syscall interface to mach_swapon.
 */
mach_swapon(filename, flags, size)
     char 	*filename;
     int	flags;
     long	size;
{
	struct vnode		*vp;
	struct pathname		pn;
	register int		error;

	unix_master();

	/*
	 * Get a vnode for the paging area.
	 */
	vp = (struct vnode *)0;
	error = pn_get(filename, UIO_USERSPACE, &pn);
	if (error)
		goto bailout;

	error = lookuppn(&pn, FOLLOW_LINK, (struct vnode **)0, &vp);
	if (error) {
		pn_free(&pn);
		goto bailout;
	}
	pn_free(&pn);

	error = pf_find_preference(vp, flags, size);

bailout:
	if (vp) {
		VN_RELE(vp);
	}
	unix_release();
	return(error);
}

/*
 *	Routine:	pf_find_preference
 *	Function:
 *		Allow user to express a preference over files used for
 *		paging.
 *	Arguments:
 *		The file in question is specified by vnode pointer.
 */
kern_return_t pf_find_preference(vp, flags, size)
	struct vnode		*vp;
	int		flags;
	long		size;
{
	register int		i;
	pager_file_t		pf;
	int			error;

	if (!suser())
		return(KERN_NO_ACCESS);

	unix_master();

	if (vp->v_type != VREG) {
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
	if (queue_end(&pager_files, &pf->pf_chain)) {
		pf = vnode_pager_file_init(vp, size);
		if (pf == PAGER_FILE_NULL) {
			error = KERN_FAILURE;
			goto bailout;
		}
	}
	pf->pf_prefer = ((flags & VS_PREFER) != 0);

	error = KERN_SUCCESS;
bailout:
	unix_release();
	return(error);
}			
#endif	0
	
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

				if ((pass < 2) && !pf->pf_prefer)
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

inode_pager_t pf_alloc(size)
	vm_size_t	size;
{
	pager_file_t	pf;
	inode_pager_t 	is = INODE_PAGER_NULL;

#ifdef	lint
	size++;
#endif	lint

	unix_master();
	if (inode_pager_debug)
		printf("pf_alloc called with size = %d pages\n",atop(size));

	/*
	 *	Get a pager_file, then turn it into a paging space.
	 */

	if ((pf = pf_find()) == PAGER_FILE_NULL) {
		goto out;
	}
	if ((is = pf_pager_create(pf, size)) == INODE_PAGER_NULL) {
		goto out;
	}
out:
	unix_release();
	return(is);
}

boolean_t pf_dealloc(is)
	inode_pager_t	is;
{
	register struct inode	*ip;
	pager_file_t		pf;
	int			i,j;

	unix_master();

	ip = istruct_get(is);

	if (!(pf = is->pf_info)) {
		panic("pf_dealloc: is->pf_info == NULL");
	}
	if (INDIRECT_PAGEMAP(is->size)) {
		for (i = 0; i < INDIRECT_PAGEMAP_ENTRIES(is->size); i++) {
			if (is->pmap[i] != NULL) {
				for(j = 0; j < PAGEMAP_ENTRIES; j++) {
					if (is->pmap[i][j] != -1) {
						pf_deallocate_page(pf, 
							    is->pmap[i][j]);
					}
				}
				kfree(is->pmap[i], PAGEMAP_THRESHOLD);
			}
		}
		kfree(is->pmap, INDIRECT_PAGEMAP_SIZE(is->size));
	} else {
		for (i = 0; i < is->size; i++) {
			if (is->pmap[i] != (vm_offset_t *)-1) {
				pf_deallocate_page(pf, is->pmap[i]);
			}
		}
		kfree(is->pmap, PAGEMAP_SIZE(is->size));
	}
	pf->pf_count--;

	free_identity(is->identity);
	zfree(istruct_zone, (vm_offset_t) is);
	unix_release();
}

/*
 *	Swapping preferences table, paired with the mount table.
 */

struct {
	boolean_t	swap_preferred;
	boolean_t	swap_never;
} iswap_table[NMOUNT];

/*
 *	Routine:	inode_swap_preference
 *	Function:
 *		Allow user to express a preference over filesystems
 *		used for paging.
 *	Arguments:
 *		The device in question is specified by (block device)
 *		major/minor number.
 *	In/out conditions:
 *		The specified filesystem must already be mounted.
 *
 *	Mach_NFS FIXME: must change to allow filenames instead??
 *	IT LOOKS LIKE this call is used to START swapping to a pagefile?
 */
kern_return_t inode_swap_preference(device, prefer, never)
	dev_t		device;
	boolean_t	prefer;
	boolean_t	never;
{
	register int		i;

	if (!suser())
		return(KERN_NO_ACCESS);

	if (device == NODEV)
		return(KERN_INVALID_ARGUMENT);

	unix_master();
	for (i = 0; i < NMOUNT; i++)
		if (mount[i].m_dev == device)
			if (mount[i].m_bufp != NULL) {
				iswap_table[i].swap_preferred = prefer;
				iswap_table[i].swap_never = never;
			} else {
				unix_release();
				return(KERN_INVALID_ARGUMENT);
			}
	unix_release();
	return(KERN_SUCCESS);
}			

kern_return_t
mach_swapon(filename, flags, lowat, hiwat)
	char 	*filename;
	int	flags;
	long	lowat;
	long	hiwat;
{
	return(KERN_FAILURE);
}

/*
 *	Routine:	iswap_allocate
 *	Function:
 *		Allocate an inode for paging out a kernel-created
 *		memory object.
 *
 *	Implementation:
 *		Looks through the mounted filesystems for the
 *		one with the most free space.  First, only "preferred"
 *		filesystems are considered, then those that are
 *		not prohibited.
 *
 *		In order to use the inode's disk block map to
 *		determine whether a page has ever been written,
 *		filesystems for which the block size is a
 *		perfect divisor of the page size are preferred.
 *
 *	In/out conditions:
 *		The inode is returned locked.
 */
struct inode	*iswap_allocate(bsize)
	vm_size_t	bsize;
{
	struct inode	*ip;
	int		pass;
	int 		mostf;
	int 		mostidx, midx;
	struct mount	*mp;
	struct fs	*fs;
	static
	char		*warnings[] = {
				(char *) 0,	/* Nothing */
				(char *) 0,	/* None preferred */
				"swapping to filesystem with smaller blocksize",
				"swapping to filesystem with larger blocksize",
				"SWAPPING BEYOND FREE RESERVE (REBOOT RECOMMENDED)",
				"UNABLE TO FIND SWAP SPACE (REBOOT RECOMMENDED)"
			};


	/*
	 *	Look thru all mounted file systems for the one with
	 *	the most free space that meets the right criteria.
	 *	During each pass, the criteria are relaxed somewhat.
	 */

	unix_master();

	mostidx = -1;
	mostf   = 0;

	for (pass = 1; (pass <= 5) && (mostidx == -1); pass++) {
		for (midx = 0; midx < NMOUNT; midx++) {
			int ffrags;
	
			mp = &mount[midx];	
			if (mp->m_bufp == NULL || NO_MOUNT_DEVICE(mp))
				continue;

			/*
			 *	Never write on read-only filesystems
			 */

			fs = MOUNT_TO_FS(mp);

			if (FS_READONLY(fs))
				continue;

			/*
			 *	Abide by advisory information...
			 *	never swap on things so marked.
			 */

			if (iswap_table[midx].swap_never)
				continue;

			/*
			 *	Take preferences pretty seriously --
			 *	ignore other heuristics.
			 */

			if (!iswap_table[midx].swap_preferred) {
				if (pass == 1)
					continue;

				/* 
				 *	We prefer to page only to filesystems
				 *	where the block size exactly matches
				 *	the page size.
				 *
				 *	Filesystems that have smaller block
				 *	sizes are better -- they just do more
				 *	I/O's per page.
				 *
				 *	If all else fails, we can use a larger
				 *	block size at the expense of disk space.
				 */

				if ((pass <= 2) && (FS_BSIZE(fs) < bsize))
					continue;

				if ((pass <= 3) && (FS_BSIZE(fs) > bsize))
					continue;
			}

			/*
			 *	See how much free space is available...
			 *	allow for the filesystem's free reserve,
			 *	unless we have no other options.
			 */
			FS_PAGING_FREE_SPACE(fs, ffrags, pass);
			if (ffrags > mostf) {
				mostf = ffrags;
				mostidx = midx;
			}
		}
	}

	ip = (struct inode *) 0;

	if (mostidx == -1)
		goto done;

	if (warnings[pass-2] != (char *) 0) {
		printf("inode_pager (iswap_allocate): %s\n", warnings[pass-2]);
		/* Only issue a given warning once */
		warnings[pass-2] = (char *) 0;
	}

	GET_ROOT_PAGING_INODE(mostidx, ip);
	if (ip == (struct inode *) 0)
		goto done;
	MODIFY_INODE(ip);
	ip->i_nlink = 0;	/* fsck will remove */
	ip->i_uid = 0;		/* which user? */
	ip->i_gid = 0;
	ip->i_mode = IFREG;

 done: ;
	unix_release();
	return(ip);
}

port_t		inode_pager_default = PORT_NULL;

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
	port_rcv_t	new_pager;
	vm_size_t	new_size;
	port_t		new_pager_request;
	port_t		new_pager_name;
	vm_size_t	new_page_size;
{
	inode_pager_t	is;
	struct inode	*ip;

#ifdef	lint
	/* XXX Eventually, use new_size to optimize for small objects */
	new_size++;
#endif	lint

	if (inode_pager_debug)
		printf("%s: new_pager=%d, new_request=%d, new_name=%d\n",
			"memory_object_data_create",
			new_pager, new_pager_request, new_pager_name);

	if (old_pager != inode_pager_default) {
		printf("memory_object_create: non-kernel caller!\n");

		/*
		 * XXX Should throw away spurious port rights -- 
		 * use port_status to avoid giving away important ports
		 */
		return(KERN_FAILURE);
	}

	if (new_page_size != PAGE_SIZE) {
		printf("memory_object_create: wrong page size\n");
		return(KERN_INVALID_ARGUMENT);
	}

	if (use_paging_file) {
		if (!paging_file_initialized) {
			pf_default_init();
			paging_file_initialized = TRUE;
		}
		is = pf_alloc(new_size);
		if (is == INODE_PAGER_NULL) {
	    	  	printf("memory_object_create: unable to allocate");
	    	  	printf("inode_pager structure[REBOOT SUGGESTED]\n");
	    	  	return(KERN_RESOURCE_SHORTAGE);
		}
	} else {
		if ((ip = iswap_allocate(PAGE_SIZE)) == (struct inode *) 0) {
		    printf("memory_object_create: unable to find an inode");
		    printf(" [REBOOT SUGGESTED]\n");
		    return(KERN_RESOURCE_SHORTAGE);
		}

		if ((is=istruct_create(ip,TRUE,TRUE))==INODE_PAGER_NULL) {
		    printf("memory_object_create: unable to allocate");
		    printf(" inode_pager structure [REBOOT SUGGESTED]\n");
		    return(KERN_RESOURCE_SHORTAGE);
		}
	}

	is->client_count++;

	/*
	 *	Determine the global name, and wedge it
	 *	into the inode structure
	 */

	(void) object_copyin(inode_pager_task, new_pager,
			     MSG_TYPE_PORT, FALSE,
			     (kern_obj_t *) &is->pager_global);

	if (!use_paging_file) ip->i_vm_info->pager = is->pager_global;

	/*
	 *	Set up associations between these ports
	 *	and this inode_pager structure
	 */

	is->pager = new_pager;
	is->pager_request = new_pager_request;
	is->pager_request_global = PORT_NULL;
	is->pager_name = new_pager_name;
	inode_port_hash_insert(new_pager, is);
	if (!use_paging_file) iput(ip);

	if (port_set_add(inode_pager_self, inode_pager_enabled_set, new_pager)
	    != KERN_SUCCESS)
		panic("memory_object_create: couldn't enable");

	return(KERN_SUCCESS);
}

memory_object_copy_strategy_t inode_copy_strategy = MEMORY_OBJECT_COPY_DELAY;

kern_return_t	memory_object_init(pager, pager_request, pager_name, pager_page_size)
	port_t		pager;
	port_t		pager_request;
	port_t		pager_name;
	vm_size_t	pager_page_size;
{
	inode_pager_t	is;
	struct inode	*ip;

	if (inode_pager_debug)
		printf("%s: pager=%d, request=%d, name=%d\n",
			"memory_object_data_init",
			pager, pager_request, pager_name);

	if (pager_page_size != PAGE_SIZE) {
		printf("memory_object_init: wrong page size");
		return(KERN_FAILURE);
	}

	if ((is = inode_pager_lookup(pager)) == INODE_PAGER_NULL) {
		printf("memory_object_init: bogus pager");
		return(KERN_FAILURE);
	}

	/*
	 *	We have to accept the possibility that another
	 *	memory_object_init call has already been performed
	 *	(either because the object got remapped before the
	 *	termination completed, or because of a malicious
	 *	client).
	 *
	 *	If we're faced with multiple clients, we only save
	 *	the state for the latest one.  [This means that
	 *	attempts to uncache the object may fail.]
	 *	XXX We could try to handle this by only allowing
	 *	the latest kernel to cache the data, or no kernel
	 *	to cache it should there be more than one.
	 */

	if (is->client_count++ > 0)
		printf("memory_object_init: multiple clients!\n");

	is->pager_request = pager_request;
	is->pager_name = pager_name;

	if (is->pager_request_global != PORT_NULL)
		port_release(is->pager_request_global);

	(void) object_copyin(inode_pager_task, pager_request,
			     MSG_TYPE_PORT, FALSE,
			     (kern_obj_t *) &is->pager_request_global);

	ip = istruct_get(is);
	ip->i_vm_info->pager_request = is->pager_request_global;
	istruct_put(is);

	(void) memory_object_set_attributes(pager_request, TRUE,
					is->cached, inode_copy_strategy);

	return(KERN_SUCCESS);
}

kern_return_t	memory_object_terminate(pager, pager_request, pager_name)
	port_t		pager;
	port_all_t	pager_request;
	port_all_t	pager_name;
{
	inode_pager_t	is = inode_pager_lookup(pager);
	struct inode	*ip;

	/*
	 *	Throw away the port rights, regardless whether this
	 *	request made any sense at all.  In order for the
	 *	message to be accepted, they must have been port_all_t's.
	 *	Therefore, they can't be any of the ports we already owned.
	 */

	if (pager_name != PORT_NULL)
		port_deallocate(inode_pager_self, pager_name);
	if (pager_request != PORT_NULL)
		port_deallocate(inode_pager_self, pager_request);

	/*
	 *	Only clean up if the object has not grown other
	 *	references while we've been running.
	 *
	 *	We move to the master processor to prevent other references
	 *	from appearing (and so that the dead reference count is
	 *	safe).
	 */

	if (is == INODE_PAGER_NULL)
		return(KERN_SUCCESS);

	is->client_count--;

	unix_master();

	if (!inode_pager_no_more_senders(is->pager_global, is->dead_references)) {
		unix_release();
		return(KERN_SUCCESS);
	}

	if (is->client_count != 0)
		printf("memory_object_terminate: client count\n");
	if (is->use_count != 0)
		printf("memory_object_terminate: use count");

	if (!is->swapfile) {
		/*
		 *	Release the inode reference.
		 */
		ip = istruct_get(is);
		ip->i_flag &= ~ITEXT;
		ip->i_vm_info->pager = MEMORY_OBJECT_NULL;
		RELEASE_INODE(ip);
	}

	/*
	 *	Release the port references held in the inode_pager
	 *	data structure.
	 */

	if (is->pager_global != PORT_NULL) {
		port_release(is->pager_global);
		is->pager_global = PORT_NULL;
	}
	if (is->pager_request_global != PORT_NULL) {
		port_release(is->pager_request_global);
		is->pager_request_global = PORT_NULL;
	}

	/*
	 *	Remove the memory object port association, and then
	 *	the destroy the port itself.
	 */

	inode_port_hash_delete(is->pager);
	port_deallocate(inode_pager_self, is->pager);

	/*
	 *	Remove the structure from the LRU queue.
	 */

	simple_lock(&istruct_lock);
	if (is->queued) {
		queue_remove(&istruct_queue, is, inode_pager_t, lru_links);
		istruct_qcount--;
	}
	simple_unlock(&istruct_lock);

	/*
	 *	Free the structure
	 *
	 *	If there are dying references, they'll need to
	 *	access the inode_pager structure (to decrement
	 *	that field), so we leave it to the last reference.
	 */

	if (is->dead_references == 0) {
		if (is->swapfile) {
			pf_dealloc(is);
		} else {
			free_identity(is->identity);
			zfree(istruct_zone, (vm_offset_t) is);
		}
	} else
	 	is->free_me = TRUE;

	unix_release();
	return(KERN_SUCCESS);
}

void		inode_pager_dead_pager(pager)
	port_t		pager;
{
	printf("inode_pager_dead_pager: unexpected, port=0x%x\n", pager);
}

/*
 *	Include the server loop
 */

#define SERVER_LOOP		inode_pager_server_loop
#define SERVER_NAME		"inode_pager"
#define TERMINATE_FUNCTION	inode_pager_dead_pager
#define SERVER_DISPATCH(in,out)	\
		(inode_pager_server(in, out) || \
		 inode_pager_default_server(in, out))
#define RECEIVE_OPTION		inode_pager_receive_option
#define TIMEOUT_FUNCTION	inode_pager_timeout()

#include <kern/server_loop.c>

#define memory_object_server		inode_pager_server
#include <mach/memory_object_server.c>
#define memory_object_default_server	inode_pager_default_server
#include <mach/memory_object_default_server.c>

int inode_pager_num_sets = 1;

void		inode_pager()
{
	memory_object_t	t;
	extern void task_name();

	task_name("inode pager");

	/*
	 *	Initialize the name port hashing stuff.
	 */

	inode_port_hash_init();

	inode_pager_task = current_task();

	inode_pager_self = task_self();

	/*
	 *	We are the default pager.
	 *	Initialize the "default pager" port.
	 */

	if (port_allocate(inode_pager_self, &inode_pager_default) != KERN_SUCCESS)
		panic("inode_pager: can't allocate default port");
	if (port_set_backlog(inode_pager_self, inode_pager_default, 2) != KERN_SUCCESS)
		panic("inode_pager: can't set backlog on default pager");

	if (port_set_allocate(inode_pager_self, &inode_pager_enabled_set)
	    != KERN_SUCCESS)
		panic("inode_pager: cannot create enabled port set");

	if (port_set_add(inode_pager_self,
			inode_pager_enabled_set,
			inode_pager_default)
	    != KERN_SUCCESS)
		panic("inode_pager: cannot enable default port");

	t = inode_pager_default;
	(void) vm_set_default_memory_manager(host_priv_self(), &t);

	/*
	 *	Allocate the buffer for pagein.
	 */

	inode_pager_buffer_allocate();

	/*
	 *	Initialize the pending pagein requests data structures.
	 */

	data_request_zone = zinit((vm_size_t) sizeof(struct data_request),
				(vm_size_t) 4096 *
					(vm_size_t) sizeof(struct data_request),
				(vm_size_t) sizeof(struct data_request),
				FALSE, "inode pager pending data requests");
	queue_init(&data_request_queue);

	SERVER_LOOP(inode_pager_enabled_set, TRUE);
}


void 	inode_pager_bootstrap()
{
	register vm_size_t	size;
	register int		i;

	/*
	 *	Initialize zone of paging structures.
	 */

	size = (vm_size_t) sizeof(struct istruct);
	istruct_zone = zinit(size,
			(vm_size_t) size*ninode*10,
			PAGE_SIZE,
			FALSE, "inode pager structures");
	queue_init(&istruct_queue);
	simple_lock_init(&istruct_lock);
	istruct_qcount = 0;
	istruct_qmax = ninode/4;
	istruct_released = 0;

	for (i = 0; i < NMOUNT; i++) {
		iswap_table[i].swap_preferred = FALSE;
		iswap_table[i].swap_never = FALSE;
	}
	iswap_table[0].swap_never = TRUE;

	queue_init(&pager_files);
	pager_file_count = 0;
}
