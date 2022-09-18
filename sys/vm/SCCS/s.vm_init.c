h46094
s 00002/00002/00075
d D 8.1 93/06/11 16:37:36 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00073
d D 7.7 92/05/04 17:22:12 bostic 7 6
c new include format
e
s 00001/00001/00076
d D 7.6 92/01/14 15:44:29 marc 6 5
c need to pass kernel size when init'ing on the MIPS
e
s 00002/00001/00075
d D 7.5 91/08/29 16:47:21 william 5 4
c changed interface to vm_page_startup function, due to new
c allocation procedure.
e
s 00001/00001/00075
d D 7.4 91/07/25 22:52:17 mckusick 4 3
c set the software page size
e
s 00027/00004/00049
d D 7.3 91/04/21 18:36:09 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00006/00008/00047
d D 7.2 91/04/20 10:50:08 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00055/00000/00000
d D 7.1 90/12/05 18:07:52 mckusick 1 0
c adopted from Mach 2.5
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 * Copyright (c) 1987 Carnegie-Mellon University
E 3
D 8
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
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
E 3
 */

/*
 *	Initialize the Virtual Memory subsystem.
 */

D 2
#include "types.h"
#include "../vm/vm_param.h"
#include "lock.h"
#include "../vm/vm_object.h"
#include "../vm/vm_map.h"
#include "../vm/vm_page.h"
#include "../vm/vm_kern.h"
E 2
I 2
D 7
#include "param.h"
E 7
I 7
#include <sys/param.h>
E 7
E 2

I 2
D 7
#include "vm.h"
#include "vm_page.h"
#include "vm_kern.h"
E 7
I 7
#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_kern.h>
E 7

E 2
/*
 *	vm_init initializes the virtual memory system.
 *	This is done only by the first cpu up.
 *
 *	The start and end address of physical memory is passed in.
 */

void vm_mem_init()
{
	extern vm_offset_t	avail_start, avail_end;
	extern vm_offset_t	virtual_avail, virtual_end;

	/*
	 *	Initializes resident memory structures.
	 *	From here on, all physical memory is accounted for,
	 *	and we use only virtual addresses.
	 */
D 4

E 4
I 4
	vm_set_page_size();
E 4
D 5
	virtual_avail = vm_page_startup(avail_start, avail_end, virtual_avail);
E 5
I 5
	vm_page_startup(&avail_start, &avail_end);

E 5
	/*
	 * Initialize other VM packages
	 */
D 6
	vm_object_init();
E 6
I 6
	vm_object_init(virtual_end - VM_MIN_KERNEL_ADDRESS);
E 6
D 2
	vm_map_init();
E 2
I 2
	vm_map_startup();
E 2
	kmem_init(virtual_avail, virtual_end);
	pmap_init(avail_start, avail_end);
	vm_pager_init();
}
E 1
