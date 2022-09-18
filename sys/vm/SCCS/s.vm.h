h55765
s 00002/00002/00071
d D 8.5 95/05/11 14:45:35 mckusick 10 9
c <sys/lock.h> MUST FOLLOW <vm/vm_param.h>
e
s 00002/00006/00071
d D 8.4 95/04/27 14:11:40 mckusick 9 8
c atomic_lock => simplelock
e
s 00013/00001/00064
d D 8.3 95/04/12 17:05:01 mckusick 8 7
c add compatibility to kernel-wide lock manager
e
s 00000/00022/00065
d D 8.2 93/12/13 23:53:34 mckusick 7 6
c pitch <sys/queue.h> compatibility code
e
s 00002/00002/00085
d D 8.1 93/06/11 16:37:18 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00083
d D 7.5 92/10/07 22:27:02 mckusick 5 4
c new queue link names; fix queue_end
e
s 00022/00001/00065
d D 7.4 92/10/07 00:13:59 mckusick 4 3
c queue.h moves to /sys/sys; old MACH queue compatibility code moves here
e
s 00024/00006/00042
d D 7.3 92/05/04 17:09:56 bostic 3 2
c move in definitions of vm exported types
e
s 00001/00001/00047
d D 7.2 91/08/28 15:45:25 mckusick 2 1
c vm_statistics.h is merged into vmmeter.h
e
s 00048/00000/00000
d D 7.1 91/05/05 16:25:49 karels 1 0
c new file
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef VM_H
#define VM_H
I 3

typedef int vm_inherit_t;		/* XXX: inheritance codes */

union vm_map_object;
typedef union vm_map_object vm_map_object_t;

struct vm_map_entry;
typedef struct vm_map_entry *vm_map_entry_t;

struct vm_map;
typedef struct vm_map *vm_map_t;

struct vm_object;
typedef struct vm_object *vm_object_t;

struct vm_page;
typedef struct vm_page  *vm_page_t;

struct pager_struct;
typedef struct pager_struct *vm_pager_t;

I 8
/*
D 10
 *	MACH VM locking primitives mappings to kernel locking primitives.
E 10
I 10
 *	MACH VM locking type mappings to kernel types
E 10
 */
D 9
typedef struct atomic_lk	simple_lock_data_t;
typedef struct atomic_lk	*simple_lock_t;
E 9
I 9
typedef struct simplelock	simple_lock_data_t;
typedef struct simplelock	*simple_lock_t;
E 9
typedef struct lock		lock_data_t;
typedef struct lock		*lock_t;
D 9
#define	simple_lock(l)		atomic_lock(l)
#define	simple_lock_init(l)	atomic_lock_init(l)
#define	simple_lock_try(l)	atomic_lock_try(l)
#define	simple_unlock(l)	atomic_unlock(l)
E 9

E 8
#include <sys/vmmeter.h>
I 4
#include <sys/queue.h>
I 8
D 10
#include <sys/lock.h>
E 10
E 8
E 4
D 7

I 4
/*
 * Compatibility with old MACH queue.h
 */
typedef struct queue_entry	*queue_t;
typedef	struct queue_entry	queue_head_t;
typedef	struct queue_entry	queue_chain_t;
typedef	struct queue_entry	*queue_entry_t;

D 5
#define	queue_first(head)	((head)->next)
#define	queue_next(elm)		((elm)->next)
#define	queue_empty(head)	((head)->next == 0)
#define	queue_end(elm, head)	((elm) == 0)
E 5
I 5
#define	queue_first(head)	((head)->qe_next)
#define	queue_next(elm)		((elm)->qe_next)
#define	queue_empty(head)	((head)->qe_next == 0)
#define	queue_end(head, elm)	((elm) == 0)
E 5

#define queue_enter(head, elt, type, field) \
	queue_enter_tail(head, elt, type, field)

#define queue_remove_first(head, elt, type, field) { \
	elt = queue_first(head); \
	queue_remove(head, elt, type, field) \
}

E 7
E 4
E 3
#include <vm/vm_param.h>
I 10
#include <sys/lock.h>
E 10
D 8
#include <vm/lock.h>
E 8
D 4
#include <vm/queue.h>
E 4
#include <vm/vm_prot.h>
#include <vm/vm_inherit.h>
#include <vm/vm_map.h>
#include <vm/vm_object.h>
D 2
#include <vm/vm_statistics.h>
E 2
#include <vm/pmap.h>
I 2
D 3
#include <sys/vmmeter.h>
E 3
I 3
#include <vm/vm_extern.h>
E 3
E 2

/*
 * Shareable process virtual address space.
 * May eventually be merged with vm_map.
 * Several fields are temporary (text, data stuff).
 */
struct vmspace {
	struct	vm_map vm_map;	/* VM address map */
	struct	pmap vm_pmap;	/* private physical map */
	int	vm_refcnt;	/* number of references */
	caddr_t	vm_shm;		/* SYS5 shared memory private data XXX */
/* we copy from vm_startcopy to the end of the structure on fork */
#define vm_startcopy vm_rssize
	segsz_t vm_rssize; 	/* current resident set size in pages */
	segsz_t vm_swrss;	/* resident set size before last swap */
	segsz_t vm_tsize;	/* text size (pages) XXX */
	segsz_t vm_dsize;	/* data size (pages) XXX */
	segsz_t vm_ssize;	/* stack size (pages) */
	caddr_t	vm_taddr;	/* user virtual address of text XXX */
	caddr_t	vm_daddr;	/* user virtual address of data XXX */
	caddr_t vm_maxsaddr;	/* user VA at max stack growth */
};
D 3

struct	vmspace *vmspace_alloc __P((vm_offset_t min, vm_offset_t max,
			int pageable));
struct	vmspace *vmspace_fork __P((struct vmspace *));
void	vmspace_free __P((struct vmspace *));
E 3
#endif /* VM_H */
E 1
