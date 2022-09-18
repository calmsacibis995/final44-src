h14596
s 00002/00002/00044
d D 8.1 93/06/11 16:37:42 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00019/00042
d D 7.5 92/05/04 17:11:21 bostic 5 4
c move function prototypes to vm_extern.h
e
s 00001/00001/00060
d D 7.4 92/02/19 19:00:39 mckusick 4 3
c cleanup the buggies
e
s 00010/00008/00051
d D 7.3 92/02/19 18:41:56 torek 3 2
c prototypes
e
s 00027/00004/00032
d D 7.2 91/04/21 18:36:11 mckusick 2 1
c update to new CMU copyright and distribution terms
e
s 00036/00000/00000
d D 7.1 90/12/05 18:08:01 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 2
 * Copyright (c) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 * Copyright (c) 1987 Carnegie-Mellon University
E 2
D 6
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
E 2
 */

D 5
/*
 *	Kernel memory management definitions.
 */
E 5
I 5
/* Kernel memory management definitions. */
E 5

D 3
void		kmem_init();
vm_offset_t	kmem_alloc();
vm_offset_t	kmem_alloc_pageable();
void		kmem_free();
vm_map_t	kmem_suballoc();
E 3
I 3
D 5
void		kmem_init __P((vm_offset_t, vm_offset_t));
vm_offset_t	kmem_alloc __P((vm_map_t, vm_size_t));
vm_offset_t	kmem_alloc_pageable __P((vm_map_t, vm_size_t));
void		kmem_free __P((vm_map_t, vm_offset_t, vm_size_t));
vm_map_t	kmem_suballoc __P((vm_map_t, vm_offset_t *, vm_offset_t *,
				   vm_size_t, boolean_t));
E 3

D 3
vm_offset_t	vm_move();
E 3
I 3
vm_offset_t	vm_move __P((vm_map_t, vm_offset_t, vm_map_t, vm_offset_t,
D 4
			     vm_size_t, boolean_t));
E 4
I 4
			     boolean_t));
E 4
E 3

D 3
vm_offset_t	kmem_alloc_wait();
void		kmem_free_wakeup();
E 3
I 3
vm_offset_t	kmem_alloc_wait __P((vm_map_t, vm_size_t));
void		kmem_free_wakeup __P((vm_map_t, vm_offset_t, vm_size_t));
E 3

E 5
I 5
vm_map_t	buffer_map;
vm_map_t	exec_map;
E 5
vm_map_t	kernel_map;
D 5
vm_map_t	mb_map;
E 5
vm_map_t	kmem_map;
D 5
vm_map_t	exec_map;
E 5
I 5
vm_map_t	mb_map;
E 5
vm_map_t	phys_map;
D 5
vm_map_t	buffer_map;
E 5
E 1
