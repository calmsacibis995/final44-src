h32185
s 00001/00001/00026
d D 8.3 93/12/13 23:55:31 mckusick 5 4
c convert page list to use <sys/queue.h>
e
s 00001/00007/00026
d D 8.2 93/10/24 12:58:58 hibler 4 3
c new improved version: dynamic allocation of fake pages
e
s 00002/00002/00031
d D 8.1 93/06/11 16:36:47 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00019/00033
d D 7.2 92/05/04 17:13:37 bostic 2 1
c definition of pagerops moves to device_pager.c where it belongs
e
s 00052/00000/00000
d D 7.1 90/12/05 18:13:22 mckusick 1 0
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

#ifndef	_DEVICE_PAGER_
#define	_DEVICE_PAGER_	1

/*
 * Device pager private data.
 */
struct devpager {
D 4
	queue_head_t	devp_list;	/* list of managed devices */
	dev_t		devp_dev;	/* devno of device */
	vm_page_t	devp_pages;	/* page structs for device */
	int		devp_npages;	/* size of device in pages */
	int		devp_count;	/* reference count */
E 4
I 4
D 5
	queue_head_t	devp_pglist;	/* list of pages allocated */
E 5
I 5
	struct pglist	devp_pglist;	/* list of pages allocated */
E 5
E 4
	vm_object_t	devp_object;	/* object representing this device */
};
typedef struct devpager	*dev_pager_t;
D 4

#define DEV_PAGER_NULL	((dev_pager_t)0)
E 4

D 2
#ifdef KERNEL

void		dev_pager_init();
vm_pager_t	dev_pager_alloc();
void		dev_pager_dealloc();
boolean_t	dev_pager_getpage(), dev_pager_putpage();
boolean_t	dev_pager_haspage();

struct pagerops devicepagerops = {
	dev_pager_init,
	dev_pager_alloc,
	dev_pager_dealloc,
	dev_pager_getpage,
	dev_pager_putpage,
	dev_pager_haspage
};

#endif

E 2
#endif	/* _DEVICE_PAGER_ */
E 1
