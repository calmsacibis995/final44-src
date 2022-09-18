h07915
s 00002/00002/00068
d D 8.3 95/01/09 17:50:27 cgd 9 8
c KNF, and 64-bit safety.
e
s 00002/00000/00068
d D 8.2 94/01/12 16:03:52 hibler 8 7
c new prototypes.
e
s 00002/00002/00066
d D 8.1 93/06/11 16:38:25 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00064
d D 7.6 92/05/04 17:11:43 bostic 6 5
c add function pprototypes
e
s 00001/00001/00063
d D 7.5 91/08/28 15:47:28 mckusick 5 4
c vm_stat is merged into vmmeter structure
e
s 00001/00001/00063
d D 7.4 91/07/25 22:59:14 mckusick 4 3
c vm_page_free_count moves to vm_stat.free_count
e
s 00027/00004/00037
d D 7.3 91/04/21 18:36:21 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00000/00002/00041
d D 7.2 91/04/20 10:50:20 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00043/00000/00000
d D 7.1 90/12/05 18:08:32 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1986, Avadis Tevanian, Jr.
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
 *	%W% (Berkeley) %G%
I 3
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
E 3
 */

/*
 *	Header file for pageout daemon.
 */

D 2
#include "lock.h"

E 2
/*
 *	Exported data structures.
 */

extern int	vm_pages_needed;	/* should be some "event" structure */
simple_lock_data_t	vm_pages_needed_lock;


/*
 *	Exported routines.
 */

/*
 *	Signal pageout-daemon and wait for it.
 */

#define	VM_WAIT		{ \
			simple_lock(&vm_pages_needed_lock); \
D 9
			thread_wakeup((int)&vm_pages_needed); \
D 4
			thread_sleep((int)&vm_page_free_count, \
E 4
I 4
D 5
			thread_sleep((int)&vm_stat.free_count, \
E 5
I 5
			thread_sleep((int)&cnt.v_free_count, \
E 9
I 9
			thread_wakeup(&vm_pages_needed); \
			thread_sleep(&cnt.v_free_count, \
E 9
E 5
E 4
				&vm_pages_needed_lock, FALSE); \
			}
I 6
#ifdef KERNEL
void		 vm_pageout __P((void));
void		 vm_pageout_scan __P((void));
I 8
void		 vm_pageout_page __P((vm_page_t, vm_object_t));
void		 vm_pageout_cluster __P((vm_page_t, vm_object_t));
E 8
#endif
E 6
E 1
