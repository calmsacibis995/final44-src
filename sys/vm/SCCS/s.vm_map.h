h04105
s 00014/00000/00216
d D 8.9 95/05/17 11:41:22 pendry 15 14
c add vm_map_lock_drain_interlock to drain map locks
e
s 00004/00005/00212
d D 8.8 95/05/14 00:36:37 mckusick 14 13
c lock manager is back to taking a proc rather than a pid
e
s 00001/00001/00216
d D 8.7 95/04/27 14:47:33 mckusick 13 12
c give up and just include <sys/proc.h>
e
s 00008/00004/00209
d D 8.6 95/04/27 14:19:14 mckusick 12 11
c lockmanager takes an interlock and a pid rather than a proc ptr
e
s 00010/00001/00203
d D 8.5 95/04/12 17:22:38 mckusick 11 10
c add macros for vm_map_set_recursive and vm_map_clear_recursive
e
s 00006/00004/00198
d D 8.4 95/04/12 14:29:14 mckusick 10 9
c redefine vm_map_lock primitives in terms of lockmgr calls
e
s 00001/00001/00201
d D 8.3 94/03/15 11:13:51 bostic 9 8
c increase MAX_KMAPENT back to 500, vangogh's kernel is periodically
c crashing; From: mike@cs.utah.edu (Mike Hibler)
e
s 00003/00003/00199
d D 8.2 94/01/12 15:56:25 hibler 8 7
c reduce number of kernel map entries,
c add vm_map_clean, get rid of vm_map_is_allocated.
e
s 00002/00002/00200
d D 8.1 93/06/11 16:37:53 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00201
d D 7.6 93/05/24 23:15:25 torek 6 5
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00054/00032/00148
d D 7.5 92/05/04 17:07:48 bostic 5 4
c add function prototypes
e
s 00002/00000/00178
d D 7.4 92/02/19 18:44:04 torek 4 3
c prototype for new function
e
s 00028/00005/00150
d D 7.3 91/04/21 18:36:14 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00002/00023/00153
d D 7.2 91/04/20 10:50:10 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00176/00000/00000
d D 7.1 90/12/05 18:08:10 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 * Copyright (c) 1987 Carnegie-Mellon University
E 3
D 7
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
D 3
 * The CMU software License Agreement specifies the terms and conditions
 * for use and redistribution.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
D 2
 *	%W% (Berkeley) %G%
E 2
I 2
D 3
 *	@(#)vm_map.h	7.1 (Berkeley) 12/5/90
E 3
I 3
 *	%W% (Berkeley) %G%
 *
 *
 * Copyright (c) 1987, 1990 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Authors: Avadis Tevanian, Jr., Michael Wayne Young
 * 
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND 
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
E 3
E 2
 */

/*
 *	Virtual memory map module definitions.
 */

#ifndef	_VM_MAP_
#define	_VM_MAP_

D 2
#ifdef KERNEL
#include "types.h"
#include "lock.h"
#include "../vm/pmap.h"
#include "../vm/vm_prot.h"
#include "../vm/vm_inherit.h"
#include "../vm/vm_object.h"
#else
#include <sys/types.h>
#include <sys/lock.h>
#include <vm/pmap.h>
#include <vm/vm_prot.h>
#include <vm/vm_inherit.h>
#include <vm/vm_object.h>
#endif

E 2
/*
 *	Types defined:
 *
 *	vm_map_t		the high-level address map data structure.
 *	vm_map_entry_t		an entry in an address map.
 *	vm_map_version_t	a timestamp of a map, for use with vm_map_lookup
 */

/*
 *	Objects which live in maps may be either VM objects, or
 *	another map (called a "sharing map") which denotes read-write
 *	sharing with other maps.
 */

union vm_map_object {
	struct vm_object	*vm_object;	/* object object */
	struct vm_map		*share_map;	/* share map */
	struct vm_map		*sub_map;	/* belongs to another map */
};

D 5
typedef union vm_map_object	vm_map_object_t;

E 5
/*
 *	Address map entries consist of start and end addresses,
 *	a VM object (or sharing map) and offset into that object,
 *	and user-exported inheritance and protection information.
 *	Also included is control information for virtual copy operations.
 */
struct vm_map_entry {
	struct vm_map_entry	*prev;		/* previous entry */
	struct vm_map_entry	*next;		/* next entry */
	vm_offset_t		start;		/* start address */
	vm_offset_t		end;		/* end address */
	union vm_map_object	object;		/* object I point to */
	vm_offset_t		offset;		/* offset into object */
	boolean_t		is_a_map;	/* Is "object" a map? */
	boolean_t		is_sub_map;	/* Is "object" a submap? */
		/* Only in sharing maps: */
	boolean_t		copy_on_write;	/* is data copy-on-write */
	boolean_t		needs_copy;	/* does object need to be copied */
		/* Only in task maps: */
	vm_prot_t		protection;	/* protection code */
	vm_prot_t		max_protection;	/* maximum protection */
	vm_inherit_t		inheritance;	/* inheritance */
	int			wired_count;	/* can be paged if = 0 */
};

D 5
typedef struct vm_map_entry	*vm_map_entry_t;

E 5
D 2
#define	VM_MAP_ENTRY_NULL	((vm_map_entry_t) 0)

E 2
/*
 *	Maps are doubly-linked lists of map entries, kept sorted
 *	by address.  A single hint is provided to start
 *	searches again from the last successful search,
 *	insertion, or removal.
 */
struct vm_map {
I 2
	struct pmap *		pmap;		/* Physical map */
E 2
	lock_data_t		lock;		/* Lock for map data */
	struct vm_map_entry	header;		/* List of entries */
	int			nentries;	/* Number of entries */
D 2
	pmap_t			pmap;		/* Physical map */
E 2
	vm_size_t		size;		/* virtual size */
	boolean_t		is_main_map;	/* Am I a main map? */
	int			ref_count;	/* Reference count */
	simple_lock_data_t	ref_lock;	/* Lock for ref_count field */
	vm_map_entry_t		hint;		/* hint for quick lookups */
	simple_lock_data_t	hint_lock;	/* lock for hint storage */
	vm_map_entry_t		first_free;	/* First free space hint */
	boolean_t		entries_pageable; /* map entries pageable?? */
	unsigned int		timestamp;	/* Version number */
#define	min_offset		header.start
#define max_offset		header.end
};

D 5
typedef	struct vm_map	*vm_map_t;

E 5
D 2
#define		VM_MAP_NULL	((vm_map_t) 0)

E 2
/*
 *	Map versions are used to validate a previous lookup attempt.
 *
 *	Since lookup operations may involve both a main map and
 *	a sharing map, it is necessary to have a timestamp from each.
 *	[If the main map timestamp has changed, the share_map and
 *	associated timestamp are no longer valid; the map version
 *	does not include a reference for the imbedded share_map.]
 */
typedef struct {
	int		main_timestamp;
	vm_map_t	share_map;
	int		share_timestamp;
} vm_map_version_t;

/*
 *	Macros:		vm_map_lock, etc.
 *	Function:
 *		Perform locking on the data portion of a map.
 */

I 10
D 13
extern struct proc *curproc;	/* XXX */
E 13
I 13
#include <sys/proc.h>	/* XXX for curproc and p_pid */
E 13
I 12
D 14
#define LOCKPID (curproc ? curproc->p_pid : LK_KERNPROC)
E 14
E 12

I 15
#define	vm_map_lock_drain_interlock(map) { \
	lockmgr(&(map)->lock, LK_DRAIN|LK_INTERLOCK, \
		&(map)->ref_lock, curproc); \
	(map)->timestamp++; \
}
#ifdef DIAGNOSTIC
E 15
E 10
D 5
#define		vm_map_lock(map)	{ lock_write(&(map)->lock); (map)->timestamp++; }
#define		vm_map_unlock(map)	lock_write_done(&(map)->lock)
#define		vm_map_lock_read(map)	lock_read(&(map)->lock)
#define		vm_map_unlock_read(map)	lock_read_done(&(map)->lock)
E 5
I 5
#define	vm_map_lock(map) { \
I 15
	if (lockmgr(&(map)->lock, LK_EXCLUSIVE, (void *)0, curproc) != 0) { \
		panic("vm_map_lock: failed to get lock"); \
	} \
	(map)->timestamp++; \
}
#else
#define	vm_map_lock(map) { \
E 15
D 10
	lock_write(&(map)->lock); \
E 10
I 10
D 12
	lockmgr(&(map)->lock, LK_EXCLUSIVE, curproc); \
E 12
I 12
D 14
	lockmgr(&(map)->lock, LK_EXCLUSIVE, (void *)0, LOCKPID); \
E 14
I 14
	lockmgr(&(map)->lock, LK_EXCLUSIVE, (void *)0, curproc); \
E 14
E 12
E 10
	(map)->timestamp++; \
}
I 15
#endif /* DIAGNOSTIC */
E 15
D 10
#define	vm_map_unlock(map)	lock_write_done(&(map)->lock)
#define	vm_map_lock_read(map)	lock_read(&(map)->lock)
#define	vm_map_unlock_read(map)	lock_read_done(&(map)->lock)
E 10
I 10
D 12
#define	vm_map_unlock(map)	lockmgr(&(map)->lock, LK_RELEASE, curproc)
#define	vm_map_lock_read(map)	lockmgr(&(map)->lock, LK_SHARED, curproc)
#define	vm_map_unlock_read(map)	lockmgr(&(map)->lock, LK_RELEASE, curproc)
E 12
I 12
#define	vm_map_unlock(map) \
D 14
		lockmgr(&(map)->lock, LK_RELEASE, (void *)0, LOCKPID)
E 14
I 14
		lockmgr(&(map)->lock, LK_RELEASE, (void *)0, curproc)
E 14
#define	vm_map_lock_read(map) \
D 14
		lockmgr(&(map)->lock, LK_SHARED, (void *)0, LOCKPID)
E 14
I 14
		lockmgr(&(map)->lock, LK_SHARED, (void *)0, curproc)
E 14
#define	vm_map_unlock_read(map) \
D 14
		lockmgr(&(map)->lock, LK_RELEASE, (void *)0, LOCKPID)
E 14
I 14
		lockmgr(&(map)->lock, LK_RELEASE, (void *)0, curproc)
E 14
E 12
E 10
E 5
D 11

E 11
I 11
#define vm_map_set_recursive(map) { \
	simple_lock(&(map)->lk_interlock); \
	(map)->lk_flags |= LK_CANRECURSE; \
	simple_unlock(&(map)->lk_interlock); \
}
#define vm_map_clear_recursive(map) { \
	simple_lock(&(map)->lk_interlock); \
	(map)->lk_flags &= ~LK_CANRECURSE; \
	simple_unlock(&(map)->lk_interlock); \
}
E 11
/*
D 5
 *	Exported procedures that operate on vm_map_t.
 */

void		vm_map_init();
vm_map_t	vm_map_create();
void		vm_map_deallocate();
void		vm_map_reference();
I 4
int		vm_map_findspace __P((vm_map_t, vm_offset_t, vm_size_t,
				      vm_offset_t *));
E 4
int		vm_map_find();
int		vm_map_remove();
int		vm_map_lookup();
void		vm_map_lookup_done();
int		vm_map_protect();
int		vm_map_inherit();
int		vm_map_copy();
D 2
vm_map_t	vm_map_fork();
E 2
void		vm_map_print();
void		vm_map_copy_entry();
boolean_t	vm_map_verify();
void		vm_map_verify_done();

/*
E 5
 *	Functions implemented as macros
 */
#define		vm_map_min(map)		((map)->min_offset)
#define		vm_map_max(map)		((map)->max_offset)
#define		vm_map_pmap(map)	((map)->pmap)

/* XXX: number of kernel maps and entries to statically allocate */
#define MAX_KMAP	10
D 8
#define	MAX_KMAPENT	500
E 8
I 8
D 9
#define	MAX_KMAPENT	250
E 9
I 9
#define	MAX_KMAPENT	500
E 9
E 8

I 5
#ifdef KERNEL
boolean_t	 vm_map_check_protection __P((vm_map_t,
		    vm_offset_t, vm_offset_t, vm_prot_t));
int		 vm_map_copy __P((vm_map_t, vm_map_t, vm_offset_t,
		    vm_size_t, vm_offset_t, boolean_t, boolean_t));
void		 vm_map_copy_entry __P((vm_map_t,
		    vm_map_t, vm_map_entry_t, vm_map_entry_t));
struct pmap;
vm_map_t	 vm_map_create __P((struct pmap *,
		    vm_offset_t, vm_offset_t, boolean_t));
void		 vm_map_deallocate __P((vm_map_t));
int		 vm_map_delete __P((vm_map_t, vm_offset_t, vm_offset_t));
vm_map_entry_t	 vm_map_entry_create __P((vm_map_t));
void		 vm_map_entry_delete __P((vm_map_t, vm_map_entry_t));
void		 vm_map_entry_dispose __P((vm_map_t, vm_map_entry_t));
void		 vm_map_entry_unwire __P((vm_map_t, vm_map_entry_t));
int		 vm_map_find __P((vm_map_t, vm_object_t,
		    vm_offset_t, vm_offset_t *, vm_size_t, boolean_t));
int		 vm_map_findspace __P((vm_map_t,
		    vm_offset_t, vm_size_t, vm_offset_t *));
int		 vm_map_inherit __P((vm_map_t,
		    vm_offset_t, vm_offset_t, vm_inherit_t));
void		 vm_map_init __P((struct vm_map *,
		    vm_offset_t, vm_offset_t, boolean_t));
int		 vm_map_insert __P((vm_map_t,
		    vm_object_t, vm_offset_t, vm_offset_t, vm_offset_t));
D 8
boolean_t	 vm_map_is_allocated __P((vm_map_t,
		    vm_offset_t, vm_offset_t, boolean_t));
E 8
int		 vm_map_lookup __P((vm_map_t *, vm_offset_t, vm_prot_t,
		    vm_map_entry_t *, vm_object_t *, vm_offset_t *, vm_prot_t *,
		    boolean_t *, boolean_t *));
void		 vm_map_lookup_done __P((vm_map_t, vm_map_entry_t));
boolean_t	 vm_map_lookup_entry __P((vm_map_t,
		    vm_offset_t, vm_map_entry_t *));
int		 vm_map_pageable __P((vm_map_t,
		    vm_offset_t, vm_offset_t, boolean_t));
I 8
int		 vm_map_clean __P((vm_map_t,
		    vm_offset_t, vm_offset_t, boolean_t, boolean_t));
E 8
void		 vm_map_print __P((vm_map_t, boolean_t));
int		 vm_map_protect __P((vm_map_t,
		    vm_offset_t, vm_offset_t, vm_prot_t, boolean_t));
void		 vm_map_reference __P((vm_map_t));
int		 vm_map_remove __P((vm_map_t, vm_offset_t, vm_offset_t));
void		 vm_map_simplify __P((vm_map_t, vm_offset_t));
void		 vm_map_simplify_entry __P((vm_map_t, vm_map_entry_t));
void		 vm_map_startup __P((void));
int		 vm_map_submap __P((vm_map_t,
		    vm_offset_t, vm_offset_t, vm_map_t));
#endif
E 5
D 6
#endif	_VM_MAP_
E 6
I 6
#endif /* _VM_MAP_ */
E 6
E 1
