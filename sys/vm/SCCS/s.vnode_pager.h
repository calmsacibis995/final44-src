h62349
s 00002/00002/00031
d D 8.1 93/06/11 16:38:55 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00019/00033
d D 7.2 92/05/04 17:17:37 bostic 2 1
c definition of pagerops moves to vnode_pager.c where it belongs
e
s 00052/00000/00000
d D 7.1 90/12/05 18:13:49 mckusick 1 0
c adopted from Mike Hibler at Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 University of Utah.
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef	_VNODE_PAGER_
#define	_VNODE_PAGER_	1

/*
 * VNODE pager private data.
 */
struct vnpager {
	int		vnp_flags;	/* flags */
	struct vnode	*vnp_vp;	/* vnode */
	vm_size_t	vnp_size;	/* vnode current size */
};
typedef struct vnpager	*vn_pager_t;

#define VN_PAGER_NULL	((vn_pager_t)0)

#define	VNP_PAGING	0x01		/* vnode used for pageout */
#define VNP_CACHED	0x02		/* vnode is cached */

D 2
#ifdef KERNEL

void		vnode_pager_init();
vm_pager_t	vnode_pager_alloc();
void		vnode_pager_dealloc();
int		vnode_pager_getpage(), vnode_pager_putpage();
boolean_t	vnode_pager_haspage();

struct pagerops vnodepagerops = {
	vnode_pager_init,
	vnode_pager_alloc,
	vnode_pager_dealloc,
	vnode_pager_getpage,
	vnode_pager_putpage,
	vnode_pager_haspage
};

#endif

E 2
#endif	/* _VNODE_PAGER_ */
E 1
