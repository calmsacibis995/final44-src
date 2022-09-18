h31635
s 00027/00004/00025
d D 7.2 91/04/21 18:36:26 mckusick 2 1
c update to new CMU copyright and distribution terms
e
s 00029/00000/00000
d D 7.1 90/12/05 18:08:52 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 2
 * Copyright (c) 1986, Avadis Tevanian, Jr., Michael Wayne Young
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

/*
 *	Kernel memory management definitions.
 */

#ifndef	_VM_USER_
#define	_VM_USER_

int	vm_allocate();
int	vm_deallocate();
int	vm_inherit();
int	vm_protect();
int	vm_statistics();

#endif	_VM_USER_
E 1
