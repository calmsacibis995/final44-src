h58355
s 00021/00007/00212
d D 8.5 94/08/20 15:15:25 mckusick 12 11
c add LIST_INSERT_BEFORE and TAILQ_INSERT_BEFORE
e
s 00003/00003/00216
d D 8.4 94/01/04 16:16:42 bostic 11 10
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00030/00001/00189
d D 8.3 93/12/13 15:58:28 mckusick 10 9
c add some comments
e
s 00150/00088/00040
d D 8.2 93/11/23 07:12:45 bostic 9 8
c revised version for use by applications as well as the kernel
e
s 00002/00002/00126
d D 8.1 93/06/02 19:54:57 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00044/00041/00084
d D 7.6 92/10/07 23:28:17 mckusick 7 5
c new queue linkage names
e
s 00044/00041/00084
d R 7.6 92/10/07 22:27:39 mckusick 6 5
c new queue link names
e
s 00000/00050/00125
d D 7.5 92/10/07 00:12:32 mckusick 5 4
c move the last of the MACH queue code to vm.h
e
s 00116/00048/00059
d D 7.4 92/10/07 00:11:12 mckusick 4 3
c use a more efficient queue implementation
e
s 00027/00004/00080
d D 7.3 91/04/21 18:36:06 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00003/00003/00081
d D 7.2 91/02/05 17:04:23 bostic 2 1
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00084/00000/00000
d D 7.1 90/12/05 17:51:33 mckusick 1 0
c adopted from MACH 2.5 h/queue.h
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1985, Avadis Tevanian, Jr.
 * Copyright (c) 1987 Carnegie-Mellon University
E 3
D 8
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 8
I 8
D 9
 * Copyright (c) 1991, 1993
E 9
I 9
D 10
 * Copyright (c) 1993
E 10
I 10
 * Copyright (c) 1991, 1993
E 10
E 9
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 5
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
E 5
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
D 5
 *
 *
 * Copyright (c) 1987, 1990 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Author: Avadis Tevanian, Jr.
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
E 5
E 3
 */

D 4
/*
 *	Type definitions for generic queues.
 */

E 4
D 2
#ifndef	_QUEUE_
#define	_QUEUE_
E 2
I 2
D 11
#ifndef	_QUEUE_H_
#define	_QUEUE_H_
E 11
I 11
#ifndef	_SYS_QUEUE_H_
#define	_SYS_QUEUE_H_
E 11
I 10

/*
 * This file defines three types of data structures: lists, tail queues,
 * and circular queues.
 *
 * A list is headed by a single forward pointer (or an array of forward
 * pointers for a hash table header). The elements are doubly linked
 * so that an arbitrary element can be removed without a need to
D 12
 * traverse the list. New elements can be added to the list after
 * an existing element or at the head of the list. A list may only be
 * traversed in the forward direction.
E 12
I 12
 * traverse the list. New elements can be added to the list before
 * or after an existing element or at the head of the list. A list
 * may only be traversed in the forward direction.
E 12
 *
 * A tail queue is headed by a pair of pointers, one to the head of the
 * list and the other to the tail of the list. The elements are doubly
 * linked so that an arbitrary element can be removed without a need to
D 12
 * traverse the list. New elements can be added to the list after
 * an existing element, at the head of the list, or at the end of the
 * list. A tail queue may only be traversed in the forward direction.
E 12
I 12
 * traverse the list. New elements can be added to the list before or
 * after an existing element, at the head of the list, or at the end of
 * the list. A tail queue may only be traversed in the forward direction.
E 12
 *
 * A circle queue is headed by a pair of pointers, one to the head of the
 * list and the other to the tail of the list. The elements are doubly
 * linked so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before or after
 * an existing element, at the head of the list, or at the end of the list.
 * A circle queue may be traversed in either direction, but has a more
 * complex end of list detection.
 *
 * For details on the use of these macros, see the queue(3) manual page.
 */
E 10
E 2

I 4
/*
D 9
 * This file defines two types of data structures, lists and queues.
 *
 * A list is headed by a single forward pointer (or an array of forward
 * pointers for a hash table header). The elements are doubly linked
 * so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list after
 * an existing element or at the head of the list.
 *
 * A queue is headed by a pair of pointers, one to the head of the list
 * and the other to the tail of the list. The elements are doubly linked
 * so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list after
 * an existing element, at the head of the list, or at the end of
 * the list.
 *
 * Note that the implementation used here avoids the need to special
 * case inserting into an empty list, deleting the last element from
 * a list, or inserting at the beginning or end of a list. The drawback
 * to this method is that it is not possible to traverse a list or
 * queue backwards.
E 9
I 9
 * List definitions.
E 9
 */
I 9
#define LIST_HEAD(name, type)						\
struct name {								\
	struct type *lh_first;	/* first element */			\
}
E 9

E 4
D 9
struct queue_entry {
D 4
	struct queue_entry	*next;		/* next element */
	struct queue_entry	*prev;		/* previous element */
E 4
I 4
D 7
	void	*next;		/* next element */
	void	**prev;		/* address of previous next element */
E 7
I 7
	void	*qe_next;	/* next element */
	void	**qe_prev;	/* address of previous next element */
E 7
E 4
};
E 9
I 9
#define LIST_ENTRY(type)						\
struct {								\
	struct type *le_next;	/* next element */			\
	struct type **le_prev;	/* address of previous next element */	\
}
E 9

D 4
typedef struct queue_entry	*queue_t;
typedef	struct queue_entry	queue_head_t;
typedef	struct queue_entry	queue_chain_t;
typedef	struct queue_entry	*queue_entry_t;
E 4
I 4
D 9
struct list_entry {
D 7
	void	*next;		/* next element */
E 7
I 7
	void	*le_next;	/* next element */
E 7
};
E 9
I 9
/*
 * List functions.
 */
#define	LIST_INIT(head) {						\
	(head)->lh_first = NULL;					\
}
E 9
E 4

I 9
#define LIST_INSERT_AFTER(listelm, elm, field) {			\
	if (((elm)->field.le_next = (listelm)->field.le_next) != NULL)	\
		(listelm)->field.le_next->field.le_prev =		\
		    &(elm)->field.le_next;				\
	(listelm)->field.le_next = (elm);				\
	(elm)->field.le_prev = &(listelm)->field.le_next;		\
}

I 12
#define	LIST_INSERT_BEFORE(listelm, elm, field) {			\
	(elm)->field.le_prev = (listelm)->field.le_prev;		\
	(elm)->field.le_next = (listelm);				\
	*(listelm)->field.le_prev = (elm);				\
	(listelm)->field.le_prev = &(elm)->field.le_next;		\
}

E 12
#define LIST_INSERT_HEAD(head, elm, field) {				\
	if (((elm)->field.le_next = (head)->lh_first) != NULL)		\
		(head)->lh_first->field.le_prev = &(elm)->field.le_next;\
	(head)->lh_first = (elm);					\
	(elm)->field.le_prev = &(head)->lh_first;			\
}

#define LIST_REMOVE(elm, field) {					\
	if ((elm)->field.le_next != NULL)				\
		(elm)->field.le_next->field.le_prev = 			\
		    (elm)->field.le_prev;				\
	*(elm)->field.le_prev = (elm)->field.le_next;			\
}

E 9
D 4
#define round_queue(size)	(((size)+7) & (~7))
E 4
I 4
/*
D 9
 * Value for pointers on removed entries.
E 9
I 9
 * Tail queue definitions.
E 9
 */
D 9
#define	NOLIST	(void *)0xdead
E 9
I 9
#define TAILQ_HEAD(name, type)						\
struct name {								\
	struct type *tqh_first;	/* first element */			\
	struct type **tqh_last;	/* addr of last next element */		\
}
E 9
E 4

I 9
#define TAILQ_ENTRY(type)						\
struct {								\
	struct type *tqe_next;	/* next element */			\
	struct type **tqe_prev;	/* address of previous next element */	\
}

E 9
D 4
#define enqueue(queue,elt)	enqueue_tail(queue, elt)
#define	dequeue(queue)		dequeue_head(queue)
E 4
I 4
/*
D 9
 * Queue functions.
E 9
I 9
 * Tail queue functions.
E 9
 */
D 7
#define	queue_init(head)	((head)->next = 0, (head)->prev = &(head)->next)
E 7
I 7
D 9
#define	queue_init(head) { \
	(head)->qe_next = 0; \
	(head)->qe_prev = &(head)->qe_next; \
E 9
I 9
#define	TAILQ_INIT(head) {						\
	(head)->tqh_first = NULL;					\
	(head)->tqh_last = &(head)->tqh_first;				\
E 9
}
E 7
E 4

D 4
#define	enqueue_head(queue,elt)	insque(elt,queue)
#define	enqueue_tail(queue,elt)	insque(elt,(queue)->prev)
#define	remqueue(queue,elt)	remque(elt)
E 4
I 4
D 9
#define queue_enter_tail(head, elm, type, field) { \
D 7
	(elm)->field.next = 0; \
	(elm)->field.prev = (head)->prev; \
	*(head)->prev = (elm); \
	(head)->prev = &(elm)->field.next; \
E 7
I 7
	(elm)->field.qe_next = 0; \
	(elm)->field.qe_prev = (head)->qe_prev; \
	*(head)->qe_prev = (elm); \
	(head)->qe_prev = &(elm)->field.qe_next; \
E 9
I 9
#define TAILQ_INSERT_HEAD(head, elm, field) {				\
	if (((elm)->field.tqe_next = (head)->tqh_first) != NULL)	\
D 12
		(elm)->field.tqe_next->field.tqe_prev =			\
E 12
I 12
		(head)->tqh_first->field.tqe_prev =			\
E 12
		    &(elm)->field.tqe_next;				\
	else								\
		(head)->tqh_last = &(elm)->field.tqe_next;		\
	(head)->tqh_first = (elm);					\
	(elm)->field.tqe_prev = &(head)->tqh_first;			\
E 9
E 7
}
E 4

D 4
#define	queue_init(q)		((q)->next = (q)->prev = q)
#define	queue_first(q)		((q)->next)
#define	queue_next(qc)		((qc)->next)
#define	queue_end(q, qe)	((q) == (qe))
#define	queue_empty(q)		queue_end((q), queue_first(q))
E 4
I 4
D 9
#define queue_enter_head(head, elm, type, field) { \
	type queue_ptr; \
D 7
	if (queue_ptr = (head)->next) \
		queue_ptr->field.prev = &(elm)->field.next; \
E 7
I 7
	if (queue_ptr = (head)->qe_next) \
		queue_ptr->field.qe_prev = &(elm)->field.qe_next; \
E 7
	else \
D 7
		(head)->prev = &(elm)->field.next; \
	(head)->next = (elm); \
	(elm)->field.next = queue_ptr; \
	(elm)->field.prev = &(head)->next; \
E 7
I 7
		(head)->qe_prev = &(elm)->field.qe_next; \
	(head)->qe_next = (elm); \
	(elm)->field.qe_next = queue_ptr; \
	(elm)->field.qe_prev = &(head)->qe_next; \
E 9
I 9
#define TAILQ_INSERT_TAIL(head, elm, field) {				\
	(elm)->field.tqe_next = NULL;					\
	(elm)->field.tqe_prev = (head)->tqh_last;			\
	*(head)->tqh_last = (elm);					\
	(head)->tqh_last = &(elm)->field.tqe_next;			\
E 9
E 7
}
E 4

D 4
#define queue_enter(head, elt, type, field) {			\
	if (queue_empty((head))) {				\
		(head)->next = (queue_entry_t) elt;		\
		(head)->prev = (queue_entry_t) elt;		\
		(elt)->field.next = head;			\
		(elt)->field.prev = head;			\
	} else {						\
		register queue_entry_t prev = (head)->prev;	\
		(elt)->field.prev = prev;			\
		(elt)->field.next = head;			\
		(head)->prev = (queue_entry_t)(elt);		\
		((type)prev)->field.next = (queue_entry_t)(elt);\
	}							\
E 4
I 4
D 9
#define queue_insert_after(head, listelm, elm, type, field) { \
	type queue_ptr; \
D 7
	if (queue_ptr = (listelm)->next) \
		queue_ptr->field.prev = &(elm)->field.next; \
E 7
I 7
	if (queue_ptr = (listelm)->qe_next) \
		queue_ptr->field.qe_prev = &(elm)->field.qe_next; \
E 7
	else \
D 7
		(head)->prev = &(elm)->field.next; \
	(listelm)->next = (elm); \
	(elm)->field.next = queue_ptr; \
	(elm)->field.prev = &(listelm)->next; \
E 7
I 7
		(head)->qe_prev = &(elm)->field.qe_next; \
	(listelm)->qe_next = (elm); \
	(elm)->field.qe_next = queue_ptr; \
	(elm)->field.qe_prev = &(listelm)->qe_next; \
E 9
I 9
#define TAILQ_INSERT_AFTER(head, listelm, elm, field) {			\
	if (((elm)->field.tqe_next = (listelm)->field.tqe_next) != NULL)\
		(elm)->field.tqe_next->field.tqe_prev = 		\
		    &(elm)->field.tqe_next;				\
	else								\
		(head)->tqh_last = &(elm)->field.tqe_next;		\
	(listelm)->field.tqe_next = (elm);				\
	(elm)->field.tqe_prev = &(listelm)->field.tqe_next;		\
I 12
}

#define	TAILQ_INSERT_BEFORE(listelm, elm, field) {			\
	(elm)->field.tqe_prev = (listelm)->field.tqe_prev;		\
	(elm)->field.tqe_next = (listelm);				\
	*(listelm)->field.tqe_prev = (elm);				\
	(listelm)->field.tqe_prev = &(elm)->field.tqe_next;		\
E 12
E 9
E 7
E 4
}

D 4
#define	queue_field(head, thing, type, field)			\
		(((head) == (thing)) ? (head) : &((type)(thing))->field)
E 4
I 4
D 9
#define queue_remove(head, elm, type, field) { \
	type queue_ptr; \
D 7
	if (queue_ptr = (elm)->field.next) \
		queue_ptr->field.prev = (elm)->field.prev; \
E 7
I 7
	if (queue_ptr = (elm)->field.qe_next) \
		queue_ptr->field.qe_prev = (elm)->field.qe_prev; \
E 7
	else \
D 7
		(head)->prev = (elm)->field.prev; \
	*(elm)->field.prev = queue_ptr; \
	(elm)->field.next = NOLIST; \
	(elm)->field.prev = NOLIST; \
E 7
I 7
		(head)->qe_prev = (elm)->field.qe_prev; \
	*(elm)->field.qe_prev = queue_ptr; \
	(elm)->field.qe_next = NOLIST; \
	(elm)->field.qe_prev = NOLIST; \
E 9
I 9
#define TAILQ_REMOVE(head, elm, field) {				\
	if (((elm)->field.tqe_next) != NULL)				\
		(elm)->field.tqe_next->field.tqe_prev = 		\
		    (elm)->field.tqe_prev;				\
	else								\
		(head)->tqh_last = (elm)->field.tqe_prev;		\
	*(elm)->field.tqe_prev = (elm)->field.tqe_next;			\
E 9
E 7
}
E 4

D 4
#define	queue_remove(head, elt, type, field) {			\
	register queue_entry_t next = (elt)->field.next;	\
	register queue_entry_t prev = (elt)->field.prev;	\
	queue_field((head), next, type, field)->prev = prev;	\
	queue_field((head), prev, type, field)->next = next;	\
E 4
I 4
/*
D 9
 * List functions.
E 9
I 9
 * Circular queue definitions.
E 9
 */
D 9
#define list_enter_head(head, elm, type, field) { \
	type queue_ptr; \
D 7
	if (queue_ptr = (head)->next) \
		queue_ptr->field.prev = &(elm)->field.next; \
	(head)->next = (elm); \
	(elm)->field.next = queue_ptr; \
	(elm)->field.prev = &(head)->next; \
E 7
I 7
	if (queue_ptr = (head)->le_next) \
		queue_ptr->field.qe_prev = &(elm)->field.qe_next; \
	(head)->le_next = (elm); \
	(elm)->field.qe_next = queue_ptr; \
	(elm)->field.qe_prev = &(head)->le_next; \
E 9
I 9
#define CIRCLEQ_HEAD(name, type)					\
struct name {								\
	struct type *cqh_first;		/* first element */		\
	struct type *cqh_last;		/* last element */		\
E 9
E 7
E 4
}

D 4
#define	queue_assign(to, from, type, field) {			\
	((type)((from)->prev))->field.next = (to);		\
	((type)((from)->next))->field.prev = (to);		\
	*to = *from;						\
E 4
I 4
D 9
#define list_insert_after(listelm, elm, type, field) { \
	type queue_ptr; \
D 7
	if (queue_ptr = (listelm)->next) \
		queue_ptr->field.prev = &(elm)->field.next; \
	(listelm)->next = (elm); \
	(elm)->field.next = queue_ptr; \
	(elm)->field.prev = &(listelm)->next; \
E 7
I 7
	if (queue_ptr = (listelm)->qe_next) \
		queue_ptr->field.qe_prev = &(elm)->field.qe_next; \
	(listelm)->qe_next = (elm); \
	(elm)->field.qe_next = queue_ptr; \
	(elm)->field.qe_prev = &(listelm)->qe_next; \
E 9
I 9
#define CIRCLEQ_ENTRY(type)						\
struct {								\
	struct type *cqe_next;		/* next element */		\
	struct type *cqe_prev;		/* previous element */		\
E 9
E 7
E 4
}

D 4
#define	queue_remove_first(h, e, t, f) {			\
	e = (t) queue_first((h));				\
	queue_remove((h), (e), t, f);				\
E 4
I 4
D 9
#define list_remove(elm, type, field) { \
	type queue_ptr; \
D 7
	if (queue_ptr = (elm)->field.next) \
		queue_ptr->field.prev = (elm)->field.prev; \
	*(elm)->field.prev = queue_ptr; \
	(elm)->field.next = NOLIST; \
	(elm)->field.prev = NOLIST; \
E 7
I 7
	if (queue_ptr = (elm)->field.qe_next) \
		queue_ptr->field.qe_prev = (elm)->field.qe_prev; \
	*(elm)->field.qe_prev = queue_ptr; \
	(elm)->field.qe_next = NOLIST; \
	(elm)->field.qe_prev = NOLIST; \
E 9
I 9
/*
 * Circular queue functions.
 */
#define	CIRCLEQ_INIT(head) {						\
	(head)->cqh_first = (void *)(head);				\
	(head)->cqh_last = (void *)(head);				\
E 9
E 7
D 5
}

/*
 * Compatibility with old MACH VM code.
 */
typedef struct queue_entry	*queue_t;
typedef	struct queue_entry	queue_head_t;
typedef	struct queue_entry	queue_chain_t;
typedef	struct queue_entry	*queue_entry_t;

#define	queue_first(head)	((head)->next)
#define	queue_next(elm)		((elm)->next)
#define	queue_empty(head)	((head)->next == 0)
#define	queue_end(elm, head)	((elm) == 0)

#define queue_enter(head, elt, type, field) \
	queue_enter_tail(head, elt, type, field)

#define queue_remove_first(head, elt, type, field) { \
	elt = queue_first(head); \
	queue_remove(head, elt, type, field) \
E 5
E 4
}

I 9
#define CIRCLEQ_INSERT_AFTER(head, listelm, elm, field) {		\
	(elm)->field.cqe_next = (listelm)->field.cqe_next;		\
	(elm)->field.cqe_prev = (listelm);				\
	if ((listelm)->field.cqe_next == (void *)(head))		\
		(head)->cqh_last = (elm);				\
	else								\
		(listelm)->field.cqe_next->field.cqe_prev = (elm);	\
	(listelm)->field.cqe_next = (elm);				\
}

#define CIRCLEQ_INSERT_BEFORE(head, listelm, elm, field) {		\
	(elm)->field.cqe_next = (listelm);				\
	(elm)->field.cqe_prev = (listelm)->field.cqe_prev;		\
	if ((listelm)->field.cqe_prev == (void *)(head))		\
		(head)->cqh_first = (elm);				\
	else								\
		(listelm)->field.cqe_prev->field.cqe_next = (elm);	\
	(listelm)->field.cqe_prev = (elm);				\
}

#define CIRCLEQ_INSERT_HEAD(head, elm, field) {				\
	(elm)->field.cqe_next = (head)->cqh_first;			\
	(elm)->field.cqe_prev = (void *)(head);				\
	if ((head)->cqh_last == (void *)(head))				\
		(head)->cqh_last = (elm);				\
	else								\
		(head)->cqh_first->field.cqe_prev = (elm);		\
	(head)->cqh_first = (elm);					\
}

#define CIRCLEQ_INSERT_TAIL(head, elm, field) {				\
	(elm)->field.cqe_next = (void *)(head);				\
	(elm)->field.cqe_prev = (head)->cqh_last;			\
	if ((head)->cqh_first == (void *)(head))			\
		(head)->cqh_first = (elm);				\
	else								\
		(head)->cqh_last->field.cqe_next = (elm);		\
	(head)->cqh_last = (elm);					\
}

#define	CIRCLEQ_REMOVE(head, elm, field) {				\
	if ((elm)->field.cqe_next == (void *)(head))			\
		(head)->cqh_last = (elm)->field.cqe_prev;		\
	else								\
		(elm)->field.cqe_next->field.cqe_prev =			\
		    (elm)->field.cqe_prev;				\
	if ((elm)->field.cqe_prev == (void *)(head))			\
		(head)->cqh_first = (elm)->field.cqe_next;		\
	else								\
		(elm)->field.cqe_prev->field.cqe_next =			\
		    (elm)->field.cqe_next;				\
}
E 9
D 2
#endif	/* _QUEUE_ */
E 2
I 2
D 11
#endif	/* !_QUEUE_H_ */
E 11
I 11
#endif	/* !_SYS_QUEUE_H_ */
E 11
E 2
E 1
