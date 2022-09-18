h36149
s 00002/00002/00094
d D 8.1 93/06/11 16:37:05 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00032/00029/00064
d D 7.10 92/05/04 17:07:07 bostic 11 10
c update function prototypes
e
s 00001/00005/00092
d D 7.9 92/02/19 18:25:42 torek 10 9
c eliminate variable kernel_pmap and function pmap_kernel
e
s 00001/00001/00096
d D 7.8 91/09/12 15:09:38 marc 9 8
c whoopsey daisey, pamp_enter() has another arg ralphie
e
s 00009/00007/00088
d D 7.7 91/09/07 13:25:44 ralph 8 7
c forgot some proto defs.
e
s 00022/00020/00073
d D 7.6 91/09/06 19:04:31 ralph 7 6
c add ANSI prototypes for pmap functions.
e
s 00012/00000/00081
d D 7.5 91/08/28 15:42:03 mckusick 6 4
c pmap_statistics moves in from deprecated vm_statistics.h
e
s 00012/00000/00081
d R 7.5 91/08/27 18:26:46 mckusick 5 4
c move in pmap_statistics structure (from abandoned vm_statistics.h)
e
s 00004/00003/00077
d D 7.4 91/05/07 09:34:20 hibler 4 3
c pmap_kernel can be a macro, pmap_remove_all/pmap_copy_on_write gone
e
s 00027/00004/00053
d D 7.3 91/04/21 18:36:05 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00002/00006/00055
d D 7.2 91/04/20 10:50:03 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00061/00000/00000
d D 7.1 90/12/05 18:07:34 mckusick 1 0
c adopted from Mach 2.5
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
D 12
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
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
 *	Machine address mapping definitions -- machine-independent
 *	section.  [For machine-dependent section, see "machine/pmap.h".]
 */

#ifndef	_PMAP_VM_
#define	_PMAP_VM_

I 6
/*
 * Each machine dependent implementation is expected to
 * keep certain statistics.  They may do this anyway they
 * so choose, but are expected to return the statistics
 * in the following structure.
 */
struct pmap_statistics {
	long		resident_count;	/* # of pages mapped (total)*/
	long		wired_count;	/* # of pages wired */
};
typedef struct pmap_statistics	*pmap_statistics_t;

E 6
D 2
#ifdef KERNEL
#include "types.h"
#include "machine/pmap.h"
#else
#include <sys/types.h>
E 2
#include <machine/pmap.h>
D 2
#endif
E 2

#ifdef KERNEL
D 8
void		pmap_bootstrap();
E 8
I 8
D 11
void		pmap_bootstrap( /* machine dependent */ );
void *		pmap_bootstrap_alloc __P((int));
E 8
D 7
void		pmap_init();
I 2
void		pmap_pinit __P((struct pmap *pmap));
void		pmap_release __P((struct pmap *pmap));
E 2
vm_offset_t	pmap_map();
pmap_t		pmap_create();
D 4
pmap_t		pmap_kernel();
E 4
void		pmap_destroy();
void		pmap_reference();
void		pmap_remove();
D 4
void		pmap_remove_all();
void		pmap_copy_on_write();
E 4
I 4
void		pmap_page_protect();
E 4
void		pmap_protect();
void		pmap_enter();
vm_offset_t	pmap_extract();
void		pmap_update();
void		pmap_collect();
void		pmap_activate();
void		pmap_deactivate();
void		pmap_copy();
void		pmap_statistics();
void		pmap_clear_reference();
boolean_t	pmap_is_referenced();
E 7
I 7
void		pmap_init __P((vm_offset_t, vm_offset_t));
D 8
void		pmap_pinit __P((pmap_t));
void		pmap_release __P((pmap_t));
E 8
vm_offset_t	pmap_map __P((vm_offset_t, vm_offset_t, vm_offset_t, int));
pmap_t		pmap_create __P((vm_size_t));
I 8
void		pmap_pinit __P((pmap_t));
E 8
void		pmap_destroy __P((pmap_t));
I 8
void		pmap_release __P((pmap_t));
E 8
void		pmap_reference __P((pmap_t));
void		pmap_remove __P((pmap_t, vm_offset_t, vm_offset_t));
void		pmap_page_protect __P((vm_offset_t, vm_prot_t));
void		pmap_protect __P((pmap_t, vm_offset_t, vm_offset_t, vm_prot_t));
D 9
void		pmap_enter __P((pmap_t, vm_offset_t, vm_prot_t, boolean_t));
E 9
I 9
void		pmap_enter __P((pmap_t, vm_offset_t, vm_offset_t, vm_prot_t, boolean_t));
E 9
void		pmap_change_wiring __P((pmap_t, vm_offset_t, boolean_t));
vm_offset_t	pmap_extract __P((pmap_t, vm_offset_t));
I 8
void		pmap_copy __P((pmap_t, pmap_t, vm_offset_t, vm_size_t,
			vm_offset_t));
E 8
void		pmap_update __P((void));
void		pmap_collect __P((pmap_t));
D 8
void		pmap_copy __P((pmap_t, pmap_t, vm_offset_t, vm_size_t, vm_offset_t));
E 8
void		pmap_zero_page __P((vm_offset_t));
void		pmap_copy_page __P((vm_offset_t, vm_offset_t));
I 8
void		pmap_pageable __P((pmap_t, vm_offset_t, vm_offset_t,
			boolean_t));
E 8
void		pmap_clear_reference __P((vm_offset_t pa));
void		pmap_clear_modify __P((vm_offset_t pa));
boolean_t	pmap_is_referenced __P((vm_offset_t pa));
boolean_t	pmap_is_modified __P((vm_offset_t pa));
I 8
vm_offset_t	pmap_phys_address __P((int));
E 8
E 7
I 4
D 10
#ifndef pmap_kernel
pmap_t		pmap_kernel();
#endif
E 10
E 4
D 8

void		pmap_redzone();
boolean_t	pmap_access();
E 8

E 11
I 11
__BEGIN_DECLS
void		*pmap_bootstrap_alloc __P((int));
void		 pmap_bootstrap( /* machine dependent */ );
void		 pmap_change_wiring __P((pmap_t, vm_offset_t, boolean_t));
void		 pmap_clear_modify __P((vm_offset_t pa));
void		 pmap_clear_reference __P((vm_offset_t pa));
void		 pmap_collect __P((pmap_t));
void		 pmap_copy __P((pmap_t,
		    pmap_t, vm_offset_t, vm_size_t, vm_offset_t));
void		 pmap_copy_page __P((vm_offset_t, vm_offset_t));
pmap_t		 pmap_create __P((vm_size_t));
void		 pmap_destroy __P((pmap_t));
void		 pmap_enter __P((pmap_t,
		    vm_offset_t, vm_offset_t, vm_prot_t, boolean_t));
vm_offset_t	 pmap_extract __P((pmap_t, vm_offset_t));
void		 pmap_init __P((vm_offset_t, vm_offset_t));
boolean_t	 pmap_is_modified __P((vm_offset_t pa));
boolean_t	 pmap_is_referenced __P((vm_offset_t pa));
vm_offset_t	 pmap_map __P((vm_offset_t, vm_offset_t, vm_offset_t, int));
void		 pmap_page_protect __P((vm_offset_t, vm_prot_t));
void		 pmap_pageable __P((pmap_t,
		    vm_offset_t, vm_offset_t, boolean_t));
vm_offset_t	 pmap_phys_address __P((int));
void		 pmap_pinit __P((pmap_t));
void		 pmap_protect __P((pmap_t,
		    vm_offset_t, vm_offset_t, vm_prot_t));
void		 pmap_reference __P((pmap_t));
void		 pmap_release __P((pmap_t));
void		 pmap_remove __P((pmap_t, vm_offset_t, vm_offset_t));
void		 pmap_update __P((void));
void		 pmap_zero_page __P((vm_offset_t));
__END_DECLS
E 11
D 10
extern pmap_t	kernel_pmap;
E 10
#endif

D 10
#endif	_PMAP_VM_
E 10
I 10
#endif /* _PMAP_VM_ */
E 10
E 1
