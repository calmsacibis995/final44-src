h28288
s 00005/00002/00080
d D 7.3 91/07/25 22:57:18 mckusick 3 2
c free_count, active_count, inactive_count, wire_count, free_target,
c free_min, and inactive_target move into vm_statistics
e
s 00027/00004/00055
d D 7.2 91/04/21 18:36:24 mckusick 2 1
c update to new CMU copyright and distribution terms
e
s 00059/00000/00000
d D 7.1 90/12/05 18:08:46 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 2
 * Copyright (c) 1986, Avadis Tevanian, Jr., Michael Wayne Young, David Golub
 * Copyright (c) 1987 Carnegie-Mellon University
E 2
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
D 2
 * The CMU software License Agreement specifies the terms and conditions
 * for use and redistribution.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
I 2
 *
 *
 * Copyright (c) 1987, 1990 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Authors: Avadis Tevanian, Jr., Michael Wayne Young, David Golub
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
E 2
 */

/*
 *	Virtual memory statistics structure.
 */

#ifndef	_VM_STATISTICS_
#define	_VM_STATISTICS_

struct vm_statistics {
D 3
	long	pagesize;		/* page size in bytes */
E 3
I 3
	long	page_size;		/* page size in bytes */
	long	free_target;		/* # of pages desired free */
	long	free_min;		/* minimum # of pages desired free */
E 3
	long	free_count;		/* # of pages free */
D 3
	long	active_count;		/* # of pages active */
E 3
I 3
	long	inactive_target;	/* # of pages desired inactive */
E 3
	long	inactive_count;		/* # of pages inactive */
I 3
	long	active_count;		/* # of pages active */
E 3
	long	wire_count;		/* # of pages wired down */
	long	zero_fill_count;	/* # of zero fill pages */
	long	reactivations;		/* # of pages reactivated */
	long	pageins;		/* # of pageins */
	long	pageouts;		/* # of pageouts */
	long	faults;			/* # of faults */
	long	cow_faults;		/* # of copy-on-writes */
	long	lookups;		/* object cache lookups */
	long	hits;			/* object cache hits */
};

typedef struct vm_statistics	*vm_statistics_t;
typedef struct vm_statistics	vm_statistics_data_t;

#ifdef	KERNEL
vm_statistics_data_t	vm_stat;
#endif	KERNEL

/*
 *	Each machine dependent implementation is expected to
 *	keep certain statistics.  They may do this anyway they
 *	so choose, but are expected to return the statistics
 *	in the following structure.
 */

struct pmap_statistics {
	long		resident_count;	/* # of pages mapped (total)*/
	long		wired_count;	/* # of pages wired */
};

typedef struct pmap_statistics	*pmap_statistics_t;
#endif	_VM_STATISTICS_
E 1
