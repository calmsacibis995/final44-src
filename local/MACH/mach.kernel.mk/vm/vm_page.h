/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_page.h,v $
 * Revision 2.14  90/07/03  16:57:48  mrt
 * 	Add precious bit.
 * 	[90/06/26            dlb]
 * 
 * Revision 2.13  89/12/22  15:57:14  rpd
 * 	Rename PAGE_WAKEUP to PAGE_WAKEUP_DONE to reflect the fact that
 * 	it clears the busy flag.  Add new PAGE_WAKEUP that only does the
 * 	wakeup, and leaves the busy flag alone.
 * 	[89/12/13            dlb]
 * 
 * Revision 2.12  89/10/10  13:48:19  mwyoung
 * 	Eliminate XP conditionals.
 * 	[89/10/10            mwyoung]
 * 
 * Revision 2.11  89/10/10  11:55:27  mwyoung
 * 	Add vm_page_module_init() declaration.
 * 	Change vm_page_zero_fill() to return void.
 * 	[89/08/07            mwyoung]
 * 	Added was_absent, overwriting fields.
 * 	[89/05/15            mwyoung]
 * 	Separate "private" from "fictitious" page attributes.
 * 	[89/04/22            mwyoung]
 * 
 * 	Move dirty bit under the object lock (from the page queues lock).
 * 	[89/04/22            mwyoung]
 * 
 * Revision 2.10  89/04/18  21:26:59  mwyoung
 * 	Recent history:
 * 		Add vm_page_fictitious_zone; remove clean, owner fields.
 * 	History condensation: no relevant history.
 * 	[89/04/18            mwyoung]
 * 
 * Revision 2.4  88/12/19  03:00:55  mwyoung
 */
/*
 *	File:	vm/vm_page.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Resident memory system definitions.
 */

#ifndef	_VM_VM_PAGE_H_
#define _VM_VM_PAGE_H_

#include <mach/boolean.h>
#include <mach/vm_prot.h>
#include <mach/vm_param.h>
#include <vm/vm_object.h>
#include <kern/queue.h>
#include <kern/lock.h>
#include <kern/thread.h>
#include <kern/zalloc.h>

#include <kern/macro_help.h>
#include <kern/sched_prim.h>	/* definitions of wait/wakeup */

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
 *	queues (P).  [Some fields require that both locks be held to
 *	change that field; holding either lock is sufficient to read.]
 */

struct vm_page {
	queue_chain_t	pageq;		/* queue info for FIFO
					 * queue or free list (P) */
	queue_chain_t	hashq;		/* hash table links (O)*/
	queue_chain_t	listq;		/* all pages in same object (O)*/

	vm_object_t	object;		/* which object am I in (O,P)*/
	vm_offset_t	offset;		/* offset into that object (O,P) */

	unsigned int	wire_count:16,	/* how many wired down maps use me?
					   (O&P) */
	/* boolean_t */	inactive:1,	/* page is in inactive list (P) */
			active:1,	/* page is in active list (P) */
			laundry:1,	/* page is being cleaned now (P)*/
			free:1,		/* page is on free list (P) */
			:0;		/* (force to 'long' boundary) */
#ifdef	ns32000
	int		pad;		/* extra space for ns32000 bit ops */
#endif	ns32000

	unsigned int
	/* boolean_t */	busy:1,		/* page is in transit (O) */
			wanted:1,	/* someone is waiting for page (O) */
			tabled:1,	/* page is in VP table (O) */
			fictitious:1,	/* Physical page doesn't exist (O) */
			private:1,	/* Page should not be returned to
					 *  the free list (O) */
			absent:1,	/* Data has been requested, but is
					 *  not yet available (O) */
			error:1,	/* Data manager was unable to provide
					 *  data due to error (O) */
			dirty:1,	/* Page must be cleaned (O) */
			was_absent:1,	/* Corresponding page was absent (O)
					 * [See memory_object_data_provided] */
			overwriting:1,	/* Request to unlock has been made
					 * without having data. (O)
					 * [See vm_object_overwrite] */
			precious:1,	/* Data must be returned to manager
					 *  even if not dirty  (O)
					 */
			:0;

	vm_offset_t	phys_addr;	/* Physical address of page, passed
					 *  to pmap_enter (read-only) */
	vm_prot_t	page_lock;	/* Uses prohibited by data manager (O) */
	vm_prot_t	unlock_request;	/* Outstanding unlock request (O) */
	vm_prot_t	max_mapping;	/* Uses made so far (O) */
};

typedef struct vm_page	*vm_page_t;

#define VM_PAGE_NULL		((vm_page_t) 0)

#if	VM_PAGE_DEBUG
#define VM_PAGE_RANGE_CHECK(mem)					\
		  (((unsigned int) (mem)) <				\
		   ((unsigned int) &vm_page_array[0])) ||		\
		  (((unsigned int) (mem)) >				\
		   ((unsigned int) &vm_page_array[last_page-first_page]))

#define VM_PAGE_CHECK(mem)						\
		MACRO_BEGIN						\
		if ( ((mem) == VM_PAGE_NULL) ||				\
		     (!(mem)->fictitious && VM_PAGE_RANGE_CHECK(mem)) || \
		     ((mem)->active && (mem)->inactive)			\
		    ) {							\
			Debugger("vm_page_check: not valid!");		\
		}							\
		MACRO_END

#else	VM_PAGE_DEBUG
#define VM_PAGE_CHECK(mem)
#endif	VM_PAGE_DEBUG

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
queue_head_t	vm_page_queue_free;	/* memory free queue */
extern
queue_head_t	vm_page_queue_active;	/* active memory queue */
extern
queue_head_t	vm_page_queue_inactive;	/* inactive memory queue */

#ifdef	VM_PAGE_DEBUG
extern
vm_page_t	vm_page_array;		/* First resident page in table */
extern
long		first_page;		/* first physical page number */
					/* ... represented in vm_page_array */
extern
long		last_page;		/* last physical page number */
					/* ... represented in vm_page_array */
					/* [INCLUSIVE] */
#endif	VM_PAGE_DEBUG

extern
vm_offset_t	first_phys_addr;	/* physical address for first_page */
extern
vm_offset_t	last_phys_addr;		/* physical address for last_page */

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

#define VM_PAGE_TO_PHYS(entry)	((entry)->phys_addr)

decl_simple_lock_data(extern,vm_page_queue_lock)/* lock on active and inactive
						   page queues */
decl_simple_lock_data(extern,vm_page_queue_free_lock)
						/* lock on free page queue */

extern
boolean_t		vm_page_free_wanted;	/* a thread is waiting for memory */

extern
zone_t			vm_page_fictitious_zone;/* Fictitious pages */

extern void		vm_page_module_init();
extern vm_offset_t	vm_page_startup();
extern void		vm_page_create();
extern vm_page_t	vm_page_lookup();
extern vm_page_t	vm_page_alloc();
extern void		vm_page_init();
extern void		vm_page_free();
extern void		vm_page_free_synchronized();
extern void		vm_page_activate();
extern void		vm_page_deactivate();
extern void		vm_page_rename();
extern void		vm_page_insert();
extern void		vm_page_remove();

extern void		vm_page_zero_fill();
extern void		vm_page_copy();

extern void		vm_page_wire();
extern void		vm_page_unwire();

extern void		vm_set_page_size();

/*
 *	Functions implemented as macros
 */

#define PAGE_ASSERT_WAIT(m, interruptible)			\
		MACRO_BEGIN					\
		(m)->wanted = TRUE;				\
		assert_wait((int) (m), (interruptible));	\
		MACRO_END

#define PAGE_WAKEUP_DONE(m)					\
		MACRO_BEGIN					\
		(m)->busy = FALSE;				\
		if ((m)->wanted) {				\
			(m)->wanted = FALSE;			\
			thread_wakeup((int) (m));		\
		}						\
		MACRO_END

#define PAGE_WAKEUP(m)						\
		MACRO_BEGIN					\
		if ((m)->wanted) {				\
			(m)->wanted = FALSE;			\
			thread_wakeup((int) (m));		\
		}						\
		MACRO_END

#define VM_PAGE_FREE(p) 			\
		MACRO_BEGIN			\
		vm_page_lock_queues();		\
		vm_page_free(p);		\
		vm_page_unlock_queues();	\
		MACRO_END

/*
 *	Macro to be used in place of pmap_enter()
 */

#define PMAP_ENTER(pmap, virtual_address, page, protection, wired) \
		MACRO_BEGIN					\
		pmap_enter(					\
			(pmap),					\
			(virtual_address),			\
			(page)->phys_addr,			\
			(protection) & ~(page)->page_lock,	\
			(wired)					\
		 );						\
		(page)->max_mapping |= (protection);		\
		MACRO_END


#if	FAST_FORM
#define VM_WAIT							\
		MACRO_BEGIN					\
		simple_lock(&vm_page_queue_free_lock);		\
		vm_page_free_wanted = TRUE;			\
		thread_wakeup((int)&vm_page_free_wanted);	\
		thread_sleep((int)&vm_page_free_count,		\
			&vm_page_queue_free_lock, FALSE);	\
		MACRO_END
#else	FAST_FORM

extern void		vm_wait();
#define VM_WAIT		vm_wait()

#endif	FAST_FORM

#define vm_page_lock_queues()	simple_lock(&vm_page_queue_lock)
#define vm_page_unlock_queues()	simple_unlock(&vm_page_queue_lock)

#define VM_PAGE_QUEUES_REMOVE(mem)				\
	MACRO_BEGIN						\
	if (mem->active) {					\
		queue_remove(&vm_page_queue_active,		\
			mem, vm_page_t, pageq);			\
		mem->active = FALSE;				\
		vm_page_active_count--;				\
	}							\
								\
	if (mem->inactive) {					\
		queue_remove(&vm_page_queue_inactive,		\
			mem, vm_page_t, pageq);			\
		mem->inactive = FALSE;				\
		vm_page_inactive_count--;			\
	}							\
	MACRO_END

#endif	_VM_VM_PAGE_H_
