h43422
s 00002/00012/00109
d D 8.5 94/07/07 21:55:45 hibler 9 8
c don't use GCC-isms in MI code (from cgd)
e
s 00045/00014/00076
d D 8.4 94/01/12 16:06:23 hibler 8 7
c multi-page interface for get/put.
e
s 00008/00006/00082
d D 8.3 93/12/13 23:54:52 mckusick 7 6
c convert pager list to use <sys/queue.h>
e
s 00005/00004/00083
d D 8.2 93/11/10 10:58:30 torek 6 5
c finish up new device pager: all pagers get offsets
e
s 00002/00002/00085
d D 8.1 93/06/11 16:38:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00081
d D 7.4 92/09/21 21:43:32 hibler 4 3
c added VM_PAGER_ERROR to reflect pager IO errors
e
s 00023/00018/00062
d D 7.3 92/05/04 17:12:03 bostic 3 2
c add function prototypes
e
s 00000/00012/00080
d D 7.2 91/04/20 10:50:22 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00092/00000/00000
d D 7.1 90/12/05 18:13:37 mckusick 1 0
c adopted from Mike Hibler at Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 University of Utah.
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Pager routine interface definition.
 * For BSD we use a cleaner version of the internal pager interface.
 */

#ifndef	_VM_PAGER_
#define	_VM_PAGER_

I 7
TAILQ_HEAD(pagerlst, pager_struct);

E 7
D 2
#ifdef KERNEL
#include "types.h"
#include "queue.h"
#else
#include <sys/types.h>
#include <sys/queue.h>
#endif

E 2
struct	pager_struct {
D 7
	queue_head_t	pg_list;	/* links for list management */
	caddr_t		pg_handle;	/* external handle (vp, dev, fp) */
	int		pg_type;	/* type of pager */
	struct pagerops	*pg_ops;	/* pager operations */
D 6
	caddr_t		pg_data;	/* private pager data */
E 6
I 6
	void		*pg_data;	/* private pager data */
E 7
I 7
	TAILQ_ENTRY(pager_struct) pg_list;	/* links for list management */
	caddr_t			  pg_handle;	/* ext. handle (vp, dev, fp) */
	int			  pg_type;	/* type of pager */
I 8
	int			  pg_flags;	/* flags */
E 8
	struct pagerops		  *pg_ops;	/* pager operations */
	void			  *pg_data;	/* private pager data */
E 7
E 6
};
D 3
typedef	struct pager_struct *vm_pager_t;
E 3

D 2
#define	vm_pager_null	((vm_pager_t) 0)	/* XXX MACH compat */
#define	VM_PAGER_NULL	((vm_pager_t) 0)

E 2
/* pager types */
#define PG_DFLT		-1
#define	PG_SWAP		0
#define	PG_VNODE	1
#define PG_DEVICE	2

I 8
/* flags */
#define PG_CLUSTERGET	1
#define PG_CLUSTERPUT	2

E 8
struct	pagerops {
D 3
	void		(*pgo_init)();		/* initialize pager */
	vm_pager_t	(*pgo_alloc)();		/* allocate pager */
	void		(*pgo_dealloc)();	/* disassociate */
	int		(*pgo_getpage)();	/* get (read) page */
	int		(*pgo_putpage)();	/* put (write) page */
	boolean_t  	(*pgo_haspage)();	/* does pager have page? */
E 3
I 3
	void		(*pgo_init)		/* Initialize pager. */
			    __P((void));
	vm_pager_t	(*pgo_alloc)		/* Allocate pager. */
D 6
			    __P((caddr_t, vm_size_t, vm_prot_t));
E 6
I 6
			    __P((caddr_t, vm_size_t, vm_prot_t, vm_offset_t));
E 6
	void		(*pgo_dealloc)		/* Disassociate. */
			    __P((vm_pager_t));
D 8
	int		(*pgo_getpage)		/* Get (read) page. */
			    __P((vm_pager_t, vm_page_t, boolean_t));
	int		(*pgo_putpage)		/* Put (write) page. */
			    __P((vm_pager_t, vm_page_t, boolean_t));
E 8
I 8
	int		(*pgo_getpages)		/* Get (read) page. */
			    __P((vm_pager_t, vm_page_t *, int, boolean_t));
	int		(*pgo_putpages)		/* Put (write) page. */
			    __P((vm_pager_t, vm_page_t *, int, boolean_t));
E 8
	boolean_t  	(*pgo_haspage)		/* Does pager have page? */
			    __P((vm_pager_t, vm_offset_t));
I 8
	void		(*pgo_cluster)		/* Return range of cluster. */
			    __P((vm_pager_t, vm_offset_t,
				 vm_offset_t *, vm_offset_t *));
E 8
E 3
};
D 2
#define PAGER_OPS_NULL	((struct pagerops *)0)
E 2

/*
 * get/put return values
D 4
 * OK	operation was successful
 * BAD	specified data was out of the accepted range
 * FAIL	specified data was in range, but doesn't exist
 * PEND	operations was initiated but not completed
E 4
I 4
 * OK	 operation was successful
 * BAD	 specified data was out of the accepted range
 * FAIL	 specified data was in range, but doesn't exist
 * PEND	 operations was initiated but not completed
 * ERROR error while accessing data that is in range and exists
I 8
 * AGAIN temporary resource shortage prevented operation from happening
E 8
E 4
 */
#define	VM_PAGER_OK	0
#define	VM_PAGER_BAD	1
#define	VM_PAGER_FAIL	2
#define	VM_PAGER_PEND	3
I 4
#define	VM_PAGER_ERROR	4
I 8
#define VM_PAGER_AGAIN	5
E 8
E 4

D 6
#define	VM_PAGER_ALLOC(h, s, p)		(*(pg)->pg_ops->pgo_alloc)(h, s, p)
E 6
I 6
D 8
#define	VM_PAGER_ALLOC(h, s, p, o)	(*(pg)->pg_ops->pgo_alloc)(h, s, p, o)
E 6
#define	VM_PAGER_DEALLOC(pg)		(*(pg)->pg_ops->pgo_dealloc)(pg)
#define	VM_PAGER_GET(pg, m, s)		(*(pg)->pg_ops->pgo_getpage)(pg, m, s)
#define	VM_PAGER_PUT(pg, m, s)		(*(pg)->pg_ops->pgo_putpage)(pg, m, s)
#define	VM_PAGER_HASPAGE(pg, o)		(*(pg)->pg_ops->pgo_haspage)(pg, o)

E 8
#ifdef KERNEL
D 3
vm_pager_t	vm_pager_allocate();
void		vm_pager_deallocate();
int		vm_pager_get();
int		vm_pager_put();
boolean_t	vm_pager_has_page();

vm_offset_t	vm_pager_map_page();
void		vm_pager_unmap_page();
vm_pager_t	vm_pager_lookup();
void		vm_pager_sync();

E 3
extern struct pagerops *dfltpagerops;
I 3

D 6
vm_pager_t	 vm_pager_allocate __P((int, caddr_t, vm_size_t, vm_prot_t));
E 6
I 6
vm_pager_t	 vm_pager_allocate
		    __P((int, caddr_t, vm_size_t, vm_prot_t, vm_offset_t));
I 8
vm_page_t	 vm_pager_atop __P((vm_offset_t));
void		 vm_pager_cluster
		    __P((vm_pager_t, vm_offset_t,
			 vm_offset_t *, vm_offset_t *));
void		 vm_pager_clusternull
		    __P((vm_pager_t, vm_offset_t,
			 vm_offset_t *, vm_offset_t *));
E 8
E 6
void		 vm_pager_deallocate __P((vm_pager_t));
D 8
int		 vm_pager_get __P((vm_pager_t, vm_page_t, boolean_t));
E 8
I 8
int		 vm_pager_get_pages
		    __P((vm_pager_t, vm_page_t *, int, boolean_t));
E 8
boolean_t	 vm_pager_has_page __P((vm_pager_t, vm_offset_t));
void		 vm_pager_init __P((void));
D 7
vm_pager_t	 vm_pager_lookup __P((queue_head_t *, caddr_t));
E 7
I 7
vm_pager_t	 vm_pager_lookup __P((struct pagerlst *, caddr_t));
E 7
D 8
vm_offset_t	 vm_pager_map_page __P((vm_page_t));
int		 vm_pager_put __P((vm_pager_t, vm_page_t, boolean_t));
E 8
I 8
vm_offset_t	 vm_pager_map_pages __P((vm_page_t *, int, boolean_t));
int		 vm_pager_put_pages
		    __P((vm_pager_t, vm_page_t *, int, boolean_t));
E 8
void		 vm_pager_sync __P((void));
D 8
void		 vm_pager_unmap_page __P((vm_offset_t));
E 8
I 8
void		 vm_pager_unmap_pages __P((vm_offset_t, int));

#define vm_pager_cancluster(p, b)	((p)->pg_flags & (b))

/*
 * XXX compat with old interface
 */
D 9
#define vm_pager_get(p, m, s) \
({ \
	vm_page_t ml[1]; \
	ml[0] = (m); \
	vm_pager_get_pages(p, ml, 1, s); \
})
#define vm_pager_put(p, m, s) \
({ \
	vm_page_t ml[1]; \
	ml[0] = (m); \
	vm_pager_put_pages(p, ml, 1, s); \
})
E 9
I 9
int		 vm_pager_get __P((vm_pager_t, vm_page_t, boolean_t));
int		 vm_pager_put __P((vm_pager_t, vm_page_t, boolean_t));
E 9
E 8
E 3
#endif

#endif	/* _VM_PAGER_ */
E 1
