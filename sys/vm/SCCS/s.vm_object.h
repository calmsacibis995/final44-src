h04689
s 00002/00002/00145
d D 8.4 95/01/09 17:45:37 cgd 13 12
c kill a typo in a comment, fix some style.
e
s 00002/00003/00145
d D 8.3 94/01/12 16:01:21 hibler 12 11
c reflect change in vm_object_page_clean interface.
e
s 00012/00007/00136
d D 8.2 93/12/13 23:50:22 mckusick 11 10
c convert resident memory list, object list, object cache list, and hash list
c to use <sys/queue.h>
e
s 00002/00002/00141
d D 8.1 93/06/11 16:38:10 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00141
d D 7.9 93/05/24 23:15:28 torek 9 8
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00000/00010/00143
d D 7.8 93/04/01 13:34:49 hibler 8 7
c eliminate LockHolder field to get vm_object size down to 64 bytes
e
s 00032/00031/00121
d D 7.7 92/05/04 17:08:12 bostic 7 6
c cleanup function prototypes
e
s 00001/00001/00151
d D 7.6 92/02/19 19:00:38 mckusick 6 5
c cleanup the buggies
e
s 00023/00018/00129
d D 7.5 92/02/19 18:43:38 torek 5 4
c prototypes
e
s 00009/00007/00138
d D 7.4 91/08/28 15:43:52 mckusick 4 3
c deprecate unused pager_ready; delete can_persist and internal
c and replace them with flags values
e
s 00027/00004/00118
d D 7.3 91/04/21 18:36:16 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00000/00012/00122
d D 7.2 91/04/20 10:50:15 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00134/00000/00000
d D 7.1 90/12/05 18:08:18 mckusick 1 0
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
D 10
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
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
 *	Virtual memory object module definitions.
 */

#ifndef	_VM_OBJECT_
#define	_VM_OBJECT_

I 11
#include <vm/vm_page.h>
E 11
D 2
#ifdef KERNEL
#include "types.h"
#include "lock.h"
#include "queue.h"
#include "../vm/vm_pager.h"
#else
#include <sys/types.h>
#include <sys/lock.h>
#include <sys/queue.h>
E 2
#include <vm/vm_pager.h>
D 2
#endif
E 2

/*
 *	Types defined:
 *
 *	vm_object_t		Virtual memory object.
 */

struct vm_object {
D 11
	queue_chain_t		memq;		/* Resident memory */
	queue_chain_t		object_list;	/* list of all objects */
E 11
I 11
	struct pglist		memq;		/* Resident memory */
	TAILQ_ENTRY(vm_object)	object_list;	/* list of all objects */
E 11
I 4
	u_short			flags;		/* see below */
	u_short			paging_in_progress; /* Paging (in or out) so
						    don't collapse or destroy */
E 4
	simple_lock_data_t	Lock;		/* Synchronization */
D 8
	int			LockHolder;
E 8
	int			ref_count;	/* How many refs?? */
	vm_size_t		size;		/* Object size */
	int			resident_page_count;
						/* number of resident pages */
	struct vm_object	*copy;		/* Object that holds copies of
						   my changed pages */
	vm_pager_t		pager;		/* Where to get data */
D 4
	boolean_t		pager_ready;	/* Have pager fields been filled? */
E 4
	vm_offset_t		paging_offset;	/* Offset into paging space */
	struct vm_object	*shadow;	/* My shadow */
	vm_offset_t		shadow_offset;	/* Offset in shadow */
D 4
	unsigned int
				paging_in_progress:16,
						/* Paging (in or out) - don't
						   collapse or destroy */
	/* boolean_t */		can_persist:1,	/* allow to persist */
	/* boolean_t */		internal:1;	/* internally created object */
E 4
D 11
	queue_chain_t		cached_list;	/* for persistence */
E 11
I 11
	TAILQ_ENTRY(vm_object)	cached_list;	/* for persistence */
E 11
};
I 4
/*
 * Flags
 */
#define OBJ_CANPERSIST	0x0001	/* allow to persist */
#define OBJ_INTERNAL	0x0002	/* internally created object */
#define OBJ_ACTIVE	0x0004	/* used to mark active objects */
E 4

I 11
TAILQ_HEAD(vm_object_hash_head, vm_object_hash_entry);

E 11
D 7
typedef struct vm_object	*vm_object_t;

E 7
struct vm_object_hash_entry {
D 11
	queue_chain_t		hash_links;	/* hash chain links */
	vm_object_t		object;		/* object we represent */
E 11
I 11
	TAILQ_ENTRY(vm_object_hash_entry)  hash_links;	/* hash chain links */
D 13
	vm_object_t			   object;	/* object represened */
E 13
I 13
	vm_object_t			   object;	/* object represented */
E 13
E 11
};

typedef struct vm_object_hash_entry	*vm_object_hash_entry_t;

#ifdef	KERNEL
D 11
queue_head_t	vm_object_cached_list;	/* list of objects persisting */
E 11
I 11
TAILQ_HEAD(object_q, vm_object);

struct object_q	vm_object_cached_list;	/* list of objects persisting */
E 11
int		vm_object_cached;	/* size of cached list */
simple_lock_data_t	vm_cache_lock;	/* lock for object cache */

D 11
queue_head_t	vm_object_list;		/* list of allocated objects */
E 11
I 11
struct object_q	vm_object_list;		/* list of allocated objects */
E 11
long		vm_object_count;	/* count of all objects */
simple_lock_data_t	vm_object_list_lock;
					/* lock for object list and count */

vm_object_t	kernel_object;		/* the single kernel object */
vm_object_t	kmem_object;

#define	vm_object_cache_lock()		simple_lock(&vm_cache_lock)
#define	vm_object_cache_unlock()	simple_unlock(&vm_cache_lock)
D 9
#endif	KERNEL
E 9
I 9
#endif /* KERNEL */
E 9
D 2

#define	VM_OBJECT_NULL		((vm_object_t) 0)
E 2

D 7
/*
 *	Declare procedures that operate on VM objects.
 */

D 5
void		vm_object_init ();
void		vm_object_terminate();
vm_object_t	vm_object_allocate();
void		vm_object_reference();
void		vm_object_deallocate();
void		vm_object_pmap_copy();
void		vm_object_pmap_remove();
void		vm_object_page_remove();
void		vm_object_shadow();
void		vm_object_copy();
void		vm_object_collapse();
vm_object_t	vm_object_lookup();
void		vm_object_enter();
void		vm_object_setpager();
#define		vm_object_cache(pager)		pager_cache(vm_object_lookup(pager),TRUE)
#define		vm_object_uncache(pager)	pager_cache(vm_object_lookup(pager),FALSE)
E 5
I 5
D 6
void	vm_object_init __P((void));
E 6
I 6
void	vm_object_init __P((vm_size_t));
E 6
void	vm_object_terminate __P((vm_object_t));
vm_object_t	vm_object_allocate __P((vm_size_t));
void	vm_object_reference __P((vm_object_t));
void	vm_object_deallocate __P((vm_object_t));
void	vm_object_pmap_copy __P((vm_object_t, vm_offset_t, vm_offset_t));
void	vm_object_pmap_remove __P((vm_object_t, vm_offset_t, vm_offset_t));
void	vm_object_page_remove __P((vm_object_t, vm_offset_t, vm_offset_t));
void	vm_object_shadow __P((vm_object_t *, vm_offset_t *, vm_size_t));
void	vm_object_copy __P((vm_object_t, vm_offset_t, vm_size_t,
			    vm_object_t *, vm_offset_t *, boolean_t *));
void	vm_object_collapse __P((vm_object_t));
vm_object_t	vm_object_lookup __P((vm_pager_t));
void	vm_object_enter __P((vm_object_t, vm_pager_t));
void	vm_object_setpager __P((vm_object_t, vm_pager_t,
				vm_offset_t, boolean_t));
#define	vm_object_cache(pager)	 pager_cache(vm_object_lookup(pager),TRUE)
#define	vm_object_uncache(pager) pager_cache(vm_object_lookup(pager),FALSE)
E 5

D 5
void		vm_object_cache_clear();
void		vm_object_print();
E 5
I 5
void	vm_object_cache_clear __P((void));
void	vm_object_print __P((vm_object_t, boolean_t));

void	thread_sleep __P((int, simple_lock_t, boolean_t));
void	thread_wakeup __P((int));
E 5

E 7
D 8
#if	VM_OBJECT_DEBUG
#define	vm_object_lock_init(object)	{ simple_lock_init(&(object)->Lock); (object)->LockHolder = 0; }
#define	vm_object_lock(object)		{ simple_lock(&(object)->Lock); (object)->LockHolder = (int) current_thread(); }
#define	vm_object_unlock(object)	{ (object)->LockHolder = 0; simple_unlock(&(object)->Lock); }
#define	vm_object_lock_try(object)	(simple_lock_try(&(object)->Lock) ? ( ((object)->LockHolder = (int) current_thread()) , TRUE) : FALSE)
#define	vm_object_sleep(event, object, interruptible) \
					{ (object)->LockHolder = 0; thread_sleep((event), &(object)->Lock, (interruptible)); }
#else	VM_OBJECT_DEBUG
E 8
#define	vm_object_lock_init(object)	simple_lock_init(&(object)->Lock)
#define	vm_object_lock(object)		simple_lock(&(object)->Lock)
#define	vm_object_unlock(object)	simple_unlock(&(object)->Lock)
#define	vm_object_lock_try(object)	simple_lock_try(&(object)->Lock)
#define	vm_object_sleep(event, object, interruptible) \
D 13
					thread_sleep((event), &(object)->Lock, (interruptible))
E 13
I 13
			thread_sleep((event), &(object)->Lock, (interruptible))
E 13
D 8
#endif	VM_OBJECT_DEBUG
E 8

I 7
#ifdef KERNEL
vm_object_t	 vm_object_allocate __P((vm_size_t));
void		 vm_object_cache_clear __P((void));
void		 vm_object_cache_trim __P((void));
boolean_t	 vm_object_coalesce __P((vm_object_t, vm_object_t,
		    vm_offset_t, vm_offset_t, vm_offset_t, vm_size_t));
void		 vm_object_collapse __P((vm_object_t));
void		 vm_object_copy __P((vm_object_t, vm_offset_t, vm_size_t,
		    vm_object_t *, vm_offset_t *, boolean_t *));
void		 vm_object_deactivate_pages __P((vm_object_t));
void		 vm_object_deallocate __P((vm_object_t));
void		 vm_object_enter __P((vm_object_t, vm_pager_t));
void		 vm_object_init __P((vm_size_t));
vm_object_t	 vm_object_lookup __P((vm_pager_t));
D 12
void		 vm_object_page_clean __P((vm_object_t,
		    vm_offset_t, vm_offset_t, boolean_t));
E 12
I 12
boolean_t	 vm_object_page_clean __P((vm_object_t,
		    vm_offset_t, vm_offset_t, boolean_t, boolean_t));
E 12
void		 vm_object_page_remove __P((vm_object_t,
		    vm_offset_t, vm_offset_t));
void		 vm_object_pmap_copy __P((vm_object_t,
		    vm_offset_t, vm_offset_t));
void		 vm_object_pmap_remove __P((vm_object_t,
		    vm_offset_t, vm_offset_t));
void		 vm_object_print __P((vm_object_t, boolean_t));
void		 vm_object_reference __P((vm_object_t));
void		 vm_object_remove __P((vm_pager_t));
void		 vm_object_setpager __P((vm_object_t,
		    vm_pager_t, vm_offset_t, boolean_t));
void		 vm_object_shadow __P((vm_object_t *,
		    vm_offset_t *, vm_size_t));
D 12
void		 vm_object_shutdown __P((void));
E 12
void		 vm_object_terminate __P((vm_object_t));
#endif
E 7
D 9
#endif	_VM_OBJECT_
E 9
I 9
#endif /* _VM_OBJECT_ */
E 9
E 1
