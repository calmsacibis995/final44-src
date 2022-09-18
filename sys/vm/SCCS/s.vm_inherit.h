h32316
s 00002/00002/00055
d D 8.1 93/06/11 16:37:33 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00056
d D 7.4 93/05/24 23:15:30 torek 4 3
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00000/00008/00057
d D 7.3 92/05/04 17:10:49 bostic 3 2
c move definition of vm_inherit_t to vm.h
e
s 00027/00004/00038
d D 7.2 91/04/21 18:36:08 mckusick 2 1
c update to new CMU copyright and distribution terms
e
s 00042/00000/00000
d D 7.1 90/12/05 18:07:48 mckusick 1 0
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
D 5
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
 *	Virtual memory map inheritance definitions.
 */

#ifndef	_VM_INHERIT_
#define	_VM_INHERIT_

/*
D 3
 *	Types defined:
 *
 *	vm_inherit_t	inheritance codes.
 */

typedef int		vm_inherit_t;	/* might want to change this */

/*
E 3
 *	Enumeration of valid values for vm_inherit_t.
 */

#define	VM_INHERIT_SHARE	((vm_inherit_t) 0)	/* share with child */
#define	VM_INHERIT_COPY		((vm_inherit_t) 1)	/* copy into child */
#define VM_INHERIT_NONE		((vm_inherit_t) 2)	/* absent from child */
#define	VM_INHERIT_DONATE_COPY	((vm_inherit_t) 3)	/* copy and delete */

#define VM_INHERIT_DEFAULT	VM_INHERIT_COPY

D 4
#endif	_VM_INHERIT_
E 4
I 4
#endif /* _VM_INHERIT_ */
E 4
E 1
