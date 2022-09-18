h23517
s 00002/00002/00214
d D 8.3 95/01/09 17:50:25 cgd 14 13
c KNF, and 64-bit safety.
e
s 00014/00012/00202
d D 8.2 93/12/13 23:52:41 mckusick 13 12
c convert free list, hash list, and object list to use <sys/queue.h>
e
s 00002/00002/00212
d D 8.1 93/06/11 16:38:17 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00212
d D 7.11 93/05/24 23:35:12 torek 11 10
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00003/00008/00211
d D 7.10 92/11/29 10:19:41 hibler 10 9
c remove unused page_lock and unlock_request fields
e
s 00004/00007/00215
d D 7.9 92/11/24 21:15:18 mckusick 9 8
c cleanups from Torek; new constants for future interface
e
s 00033/00046/00189
d D 7.8 92/10/01 17:55:31 mckusick 8 7
c convert vm_page bit fields to flags
e
s 00018/00023/00217
d D 7.7 92/05/04 17:08:42 bostic 7 6
c cleanup function prototypes
e
s 00025/00002/00215
d D 7.6 92/02/19 18:05:01 torek 6 5
c define VM_PAGE_INIT as vm_page_init was only used in one place
e
s 00015/00014/00202
d D 7.5 91/08/29 16:45:56 william 5 4
c added function prototypes, cleaning up.
e
s 00000/00019/00216
d D 7.4 91/07/25 22:56:49 mckusick 4 3
c free_count, active_count, inactive_count, wire_count, free_target, 
c free_min, and inactive_target move into vm_statistics
e
s 00027/00004/00208
d D 7.3 91/04/21 18:36:19 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00000/00007/00212
d D 7.2 91/04/20 10:50:18 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00219/00000/00000
d D 7.1 90/12/05 18:08:25 mckusick 1 0
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
D 12
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
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
 *	%W% (Berkeley) %G%
I 3
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
 */

/*
 *	Resident memory system definitions.
 */

#ifndef	_VM_PAGE_
#define	_VM_PAGE_

D 2
#include "../vm/vm_param.h"
#include "../vm/vm_object.h"
#include "../vm/vm_prot.h"
#include "lock.h"

E 2
/*
 *	Management of resident (logical) pages.
 *
 *	A small structure is kept for each resident
 *	page, indexed by page number.  Each structure
 *	is an element of several lists:
 *
 *		A hash table bucket used to quickly
 *		perform object/offset lookups
 *
 *		A list of all pages for a given object,
 *		so they can be quickly deactivated at
 *		time of deallocation.
 *
 *		An ordered list of pages due for pageout.
 *
 *	In addition, the structure contains the object
 *	and offset to which this page belongs (for pageout),
 *	and sundry status bits.
 *
 *	Fields in this structure are locked either by the lock on the
 *	object that the page belongs to (O) or by the lock on the page
 *	queues (P).
 */

I 13
TAILQ_HEAD(pglist, vm_page);

E 13
struct vm_page {
D 13
	queue_chain_t	pageq;		/* queue info for FIFO
					 * queue or free list (P) */
	queue_chain_t	hashq;		/* hash table links (O)*/
	queue_chain_t	listq;		/* all pages in same object (O)*/
E 13
I 13
	TAILQ_ENTRY(vm_page)	pageq;		/* queue info for FIFO
						 * queue or free list (P) */
	TAILQ_ENTRY(vm_page)	hashq;		/* hash table links (O)*/
	TAILQ_ENTRY(vm_page)	listq;		/* pages in same object (O)*/
E 13

D 13
	vm_object_t	object;		/* which object am I in (O,P)*/
	vm_offset_t	offset;		/* offset into that object (O,P) */
E 13
I 13
	vm_object_t		object;		/* which object am I in (O,P)*/
	vm_offset_t		offset;		/* offset into object (O,P) */
E 13

D 8
	unsigned int	wire_count:16,	/* how many wired down maps use me?
					   (P) */
	/* boolean_t */	inactive:1,	/* page is in inactive list (P) */
			active:1,	/* page is in active list (P) */
			laundry:1,	/* page is being cleaned now (P)*/
#ifdef DEBUG
			pagerowned:1,	/* async paging op in progress */
			ptpage:1,	/* is a user page table page */
#endif
			:0;		/* (force to 'long' boundary) */
#ifdef	ns32000
	int		pad;		/* extra space for ns32000 bit ops */
#endif	ns32000
	boolean_t	clean;		/* page has not been modified */
	unsigned int
	/* boolean_t */	busy:1,		/* page is in transit (O) */
			wanted:1,	/* someone is waiting for page (O) */
			tabled:1,	/* page is in VP table (O) */
			copy_on_write:1,/* page must be copied before being
					   changed (O) */
			fictitious:1,	/* physical page doesn't exist (O) */
			absent:1,	/* virtual page doesn't exist (O) */
			fake:1,		/* page is a placeholder for page-in
					   (O) */
			:0;
E 8
I 8
D 13
	u_short		wire_count;	/* number wired down maps use me? (P) */
	u_short		flags;		/* see below */
E 13
I 13
	u_short			wire_count;	/* wired down maps refs (P) */
	u_short			flags;		/* see below */
E 13
E 8

D 13
	vm_offset_t	phys_addr;	/* physical address of page */
E 13
I 13
	vm_offset_t		phys_addr;	/* physical address of page */
E 13
D 10
	vm_prot_t	page_lock;	/* Uses prohibited by data manager */
	vm_prot_t	unlock_request;	/* Outstanding unlock request */
E 10
};

I 8
/*
 * These are the flags defined for vm_page.
I 9
 *
 * Note: PG_FILLED and PG_DIRTY are added for the filesystems.
E 9
 */
#define	PG_INACTIVE	0x0001		/* page is in inactive list (P) */
#define	PG_ACTIVE	0x0002		/* page is in active list (P) */
#define	PG_LAUNDRY	0x0004		/* page is being cleaned now (P)*/
#define	PG_CLEAN	0x0008		/* page has not been modified */
#define	PG_BUSY		0x0010		/* page is in transit (O) */
#define	PG_WANTED	0x0020		/* someone is waiting for page (O) */
#define	PG_TABLED	0x0040		/* page is in VP table (O) */
#define	PG_COPYONWRITE	0x0080		/* must copy page before changing (O) */
#define	PG_FICTITIOUS	0x0100		/* physical page doesn't exist (O) */
D 10
#define	PG_ABSENT	0x0200		/* virtual page doesn't exist (O) */
#define	PG_FAKE		0x0400		/* page is placeholder for pagein (O) */
I 9
#define	PG_FILLED	0x0800		/* client flag to set when filled */
#define	PG_DIRTY	0x1000		/* client flag to set when dirty */
E 10
I 10
#define	PG_FAKE		0x0200		/* page is placeholder for pagein (O) */
#define	PG_FILLED	0x0400		/* client flag to set when filled */
#define	PG_DIRTY	0x0800		/* client flag to set when dirty */
E 10
E 9
#define	PG_PAGEROWNED	0x4000		/* DEBUG: async paging op in progress */
#define	PG_PTPAGE	0x8000		/* DEBUG: is a user page table page */

E 8
D 7
typedef struct vm_page	*vm_page_t;
D 2

#define	VM_PAGE_NULL		((vm_page_t) 0)
E 2

E 7
#if	VM_PAGE_DEBUG
#define	VM_PAGE_CHECK(mem) { \
D 8
		if ( (((unsigned int) mem) < ((unsigned int) &vm_page_array[0])) || \
		     (((unsigned int) mem) > ((unsigned int) &vm_page_array[last_page-first_page])) || \
		     (mem->active && mem->inactive) \
		    ) panic("vm_page_check: not valid!"); \
		}
E 8
I 8
	if ((((unsigned int) mem) < ((unsigned int) &vm_page_array[0])) || \
	    (((unsigned int) mem) > \
		((unsigned int) &vm_page_array[last_page-first_page])) || \
	    ((mem->flags & (PG_ACTIVE | PG_INACTIVE)) == \
		(PG_ACTIVE | PG_INACTIVE))) \
		panic("vm_page_check: not valid!"); \
}
E 8
D 11
#else	VM_PAGE_DEBUG
E 11
I 11
#else /* VM_PAGE_DEBUG */
E 11
#define	VM_PAGE_CHECK(mem)
D 11
#endif	VM_PAGE_DEBUG
E 11
I 11
#endif /* VM_PAGE_DEBUG */
E 11

D 7
#ifdef	KERNEL
E 7
I 7
#ifdef KERNEL
E 7
/*
 *	Each pageable resident page falls into one of three lists:
 *
 *	free	
 *		Available for allocation now.
 *	inactive
 *		Not referenced in any map, but still has an
 *		object/offset-page mapping, and may be dirty.
 *		This is the list of pages that should be
 *		paged out next.
 *	active
 *		A list of pages which have been placed in
 *		at least one physical map.  This list is
 *		ordered, in LRU-like fashion.
 */

extern
D 13
queue_head_t	vm_page_queue_free;	/* memory free queue */
E 13
I 13
struct pglist	vm_page_queue_free;	/* memory free queue */
E 13
extern
D 13
queue_head_t	vm_page_queue_active;	/* active memory queue */
E 13
I 13
struct pglist	vm_page_queue_active;	/* active memory queue */
E 13
extern
D 13
queue_head_t	vm_page_queue_inactive;	/* inactive memory queue */
E 13
I 13
struct pglist	vm_page_queue_inactive;	/* inactive memory queue */
E 13

extern
vm_page_t	vm_page_array;		/* First resident page in table */
extern
long		first_page;		/* first physical page number */
					/* ... represented in vm_page_array */
extern
long		last_page;		/* last physical page number */
					/* ... represented in vm_page_array */
					/* [INCLUSIVE] */
extern
vm_offset_t	first_phys_addr;	/* physical address for first_page */
extern
vm_offset_t	last_phys_addr;		/* physical address for last_page */

D 4
extern
int	vm_page_free_count;	/* How many pages are free? */
extern
int	vm_page_active_count;	/* How many pages are active? */
extern
int	vm_page_inactive_count;	/* How many pages are inactive? */
extern
int	vm_page_wire_count;	/* How many pages are wired? */
extern
int	vm_page_free_target;	/* How many do we want free? */
extern
int	vm_page_free_min;	/* When to wakeup pageout */
extern
int	vm_page_inactive_target;/* How many do we want inactive? */
extern
int	vm_page_free_reserved;	/* How many pages reserved to do pageout */
extern
int	vm_page_laundry_count;	/* How many pages being laundered? */

E 4
#define VM_PAGE_TO_PHYS(entry)	((entry)->phys_addr)

#define IS_VM_PHYSADDR(pa) \
		((pa) >= first_phys_addr && (pa) <= last_phys_addr)

#define PHYS_TO_VM_PAGE(pa) \
		(&vm_page_array[atop(pa) - first_page ])

extern
simple_lock_data_t	vm_page_queue_lock;	/* lock on active and inactive
						   page queues */
D 7
extern
E 7
I 7
extern						/* lock on free page queue */
E 7
simple_lock_data_t	vm_page_queue_free_lock;
D 7
						/* lock on free page queue */
D 5
vm_offset_t	vm_page_startup();
vm_page_t	vm_page_lookup();
vm_page_t	vm_page_alloc();
void		vm_page_init();
void		vm_page_free();
void		vm_page_activate();
void		vm_page_deactivate();
void		vm_page_rename();
void		vm_page_replace();
E 5
I 5
void		vm_page_startup __P((vm_offset_t *start, vm_offset_t *end));
vm_page_t	vm_page_lookup __P((vm_object_t object, vm_offset_t offset));
vm_page_t	vm_page_alloc __P((vm_object_t object, vm_offset_t offset));
D 6
void		vm_page_init __P((vm_page_t mem, vm_object_t object,
			vm_offset_t offset));
E 6
void		vm_page_free __P((vm_page_t mem));
void		vm_page_activate __P((vm_page_t mem));
void		vm_page_deactivate __P((vm_page_t mem));
void		vm_page_rename __P((vm_page_t mem, vm_object_t new_object,
			vm_offset_t new_offset));
E 7
E 5

D 5
boolean_t	vm_page_zero_fill();
void		vm_page_copy();
E 5
I 5
D 7
boolean_t	vm_page_zero_fill __P((vm_page_t mem));
void		vm_page_copy __P((vm_page_t src_mem, vm_page_t dst_mem));
E 5

D 5
void		vm_page_wire();
void		vm_page_unwire();
E 5
I 5
void		vm_page_wire __P((vm_page_t mem));
void		vm_page_unwire __P((vm_page_t mem));
E 5

D 5
void		vm_set_page_size();
E 5
I 5
void		vm_set_page_size __P((void));
E 5

E 7
/*
 *	Functions implemented as macros
 */

#define PAGE_ASSERT_WAIT(m, interruptible)	{ \
D 8
				(m)->wanted = TRUE; \
E 8
I 8
				(m)->flags |= PG_WANTED; \
E 8
D 14
				assert_wait((int) (m), (interruptible)); \
E 14
I 14
				assert_wait((m), (interruptible)); \
E 14
			}

#define PAGE_WAKEUP(m)	{ \
D 8
				(m)->busy = FALSE; \
				if ((m)->wanted) { \
					(m)->wanted = FALSE; \
E 8
I 8
				(m)->flags &= ~PG_BUSY; \
				if ((m)->flags & PG_WANTED) { \
					(m)->flags &= ~PG_WANTED; \
E 8
D 14
					thread_wakeup((int) (m)); \
E 14
I 14
					thread_wakeup((m)); \
E 14
				} \
			}

#define	vm_page_lock_queues()	simple_lock(&vm_page_queue_lock)
#define	vm_page_unlock_queues()	simple_unlock(&vm_page_queue_lock)

D 8
#define vm_page_set_modified(m)	{ (m)->clean = FALSE; }
E 8
I 8
#define vm_page_set_modified(m)	{ (m)->flags &= ~PG_CLEAN; }
E 8
I 6

D 9
#ifdef DEBUG
D 8
#define	VM_PAGE_DEBUG_INIT(m) ((m)->pagerowned = 0, (m)->ptpage = 0)
E 8
I 8
#define	VM_PAGE_DEBUG_INIT(m)
E 8
#else
#define	VM_PAGE_DEBUG_INIT(m)
#endif

E 9
#define	VM_PAGE_INIT(mem, object, offset) { \
D 8
	(mem)->busy = TRUE; \
	(mem)->tabled = FALSE; \
E 8
I 8
	(mem)->flags = PG_BUSY | PG_CLEAN | PG_FAKE; \
E 8
	vm_page_insert((mem), (object), (offset)); \
D 8
	(mem)->absent = FALSE; \
	(mem)->fictitious = FALSE; \
E 8
D 10
	(mem)->page_lock = VM_PROT_NONE; \
	(mem)->unlock_request = VM_PROT_NONE; \
E 10
D 8
	(mem)->laundry = FALSE; \
	(mem)->active = FALSE; \
	(mem)->inactive = FALSE; \
E 8
	(mem)->wire_count = 0; \
D 8
	(mem)->clean = TRUE; \
	(mem)->copy_on_write = FALSE; \
	(mem)->fake = TRUE; \
E 8
D 9
	VM_PAGE_DEBUG_INIT(mem); \
E 9
}

E 6
D 7
#endif	KERNEL
#endif	_VM_PAGE_
E 7
I 7
void		 vm_page_activate __P((vm_page_t));
vm_page_t	 vm_page_alloc __P((vm_object_t, vm_offset_t));
void		 vm_page_copy __P((vm_page_t, vm_page_t));
void		 vm_page_deactivate __P((vm_page_t));
void		 vm_page_free __P((vm_page_t));
void		 vm_page_insert __P((vm_page_t, vm_object_t, vm_offset_t));
vm_page_t	 vm_page_lookup __P((vm_object_t, vm_offset_t));
void		 vm_page_remove __P((vm_page_t));
void		 vm_page_rename __P((vm_page_t, vm_object_t, vm_offset_t));
void		 vm_page_startup __P((vm_offset_t *, vm_offset_t *));
void		 vm_page_unwire __P((vm_page_t));
void		 vm_page_wire __P((vm_page_t));
boolean_t	 vm_page_zero_fill __P((vm_page_t));

#endif /* KERNEL */
#endif /* !_VM_PAGE_ */
E 7
E 1
