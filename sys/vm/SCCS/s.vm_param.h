h16944
s 00013/00012/00121
d D 8.2 95/01/09 17:50:29 cgd 11 10
c KNF, and 64-bit safety.
e
s 00002/00002/00131
d D 8.1 93/06/11 16:38:33 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00020/00120
d D 7.9 93/05/24 23:15:35 torek 9 8
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00003/00003/00137
d D 7.8 93/04/18 00:23:20 mckusick 8 7
c specify types for sysctl names
e
s 00012/00000/00128
d D 7.7 93/02/04 01:27:58 mckusick 7 6
c add CTL_VM definitions
e
s 00000/00004/00128
d D 7.6 92/10/11 13:04:02 bostic 6 5
c make kernel includes standard
e
s 00018/00010/00114
d D 7.5 91/08/28 17:07:24 mckusick 5 4
c add num_pages macro; add PAGE_MASK macro
e
s 00002/00002/00122
d D 7.4 91/08/28 15:40:28 mckusick 4 3
c vm_stat is merged into vmmeter structure
e
s 00004/00005/00120
d D 7.3 91/07/25 22:58:40 mckusick 3 2
c add default software page size; page_size moves to vm_statistics
e
s 00027/00004/00098
d D 7.2 91/04/21 18:36:23 mckusick 2 1
c update to new CMU copyright and distribution terms
e
s 00102/00000/00000
d D 7.1 90/12/05 18:08:39 mckusick 1 0
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
D 10
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
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
 *	Machine independent virtual memory parameters.
 */

#ifndef	_VM_PARAM_
#define	_VM_PARAM_

D 6
#ifdef KERNEL
#include "machine/vmparam.h"
#else
E 6
#include <machine/vmparam.h>
D 6
#endif
E 6

/*
 * This belongs in types.h, but breaks too many existing programs.
 */
typedef int	boolean_t;
#define	TRUE	1
#define	FALSE	0

/*
 *	The machine independent pages are refered to as PAGES.  A page
 *	is some number of hardware pages, depending on the target machine.
 */
I 3
D 11
#define DEFAULT_PAGE_SIZE	4096
E 11
I 11
#define	DEFAULT_PAGE_SIZE	4096
E 11
E 3

/*
 *	All references to the size of a page should be done with PAGE_SIZE
 *	or PAGE_SHIFT.  The fact they are variables is hidden here so that
 *	we can easily make them constant if we so desire.
 */
I 3
D 4
#define	PAGE_SIZE	vm_stat.page_size	/* size of page */
E 4
I 4
#define	PAGE_SIZE	cnt.v_page_size		/* size of page */
I 5
D 11
#define PAGE_MASK	page_mask		/* size of page - 1 */
E 5
E 4
#define PAGE_SHIFT	page_shift		/* bits to shift for pages */
E 11
I 11
#define	PAGE_MASK	page_mask		/* size of page - 1 */
#define	PAGE_SHIFT	page_shift		/* bits to shift for pages */
E 11
I 5
#ifdef KERNEL
extern vm_size_t	page_mask;
extern int		page_shift;
#endif
E 5
E 3

I 7
/*
 * CTL_VM identifiers
 */
D 11
#define	VM_METER	 1		/* struct vmmeter */
#define	VM_LOADAVG	 2		/* struct loadavg */
#define	VM_MAXID	 3		/* number of valid vm ids */
E 11
I 11
#define	VM_METER	1		/* struct vmmeter */
#define	VM_LOADAVG	2		/* struct loadavg */
#define	VM_MAXID	3		/* number of valid vm ids */
E 11

D 11
#define CTL_VM_NAMES { \
E 11
I 11
#define	CTL_VM_NAMES { \
E 11
D 8
	"unspec", \
	"vmmeter", \
	"loadavg", \
E 8
I 8
	{ 0, 0 }, \
	{ "vmmeter", CTLTYPE_STRUCT }, \
	{ "loadavg", CTLTYPE_STRUCT }, \
E 8
}
E 7
I 5

E 5
D 3
#define	PAGE_SIZE	page_size	/* size of page in addressible units */
#define PAGE_SHIFT	page_shift	/* number of bits to shift for pages */

E 3
/* 
 *	Return values from the VM routines.
 */
#define	KERN_SUCCESS		0
#define	KERN_INVALID_ADDRESS	1
#define	KERN_PROTECTION_FAILURE	2
#define	KERN_NO_SPACE		3
#define	KERN_INVALID_ARGUMENT	4
#define	KERN_FAILURE		5
#define	KERN_RESOURCE_SHORTAGE	6
#define	KERN_NOT_RECEIVER	7
#define	KERN_NO_ACCESS		8

D 9
#ifdef	ASSEMBLER
#else	ASSEMBLER
E 9
I 9
#ifndef ASSEMBLER
E 9
/*
 *	Convert addresses to pages and vice versa.
 *	No rounding is used.
 */
D 9

#ifdef	KERNEL
E 9
I 9
#ifdef KERNEL
E 9
D 5
#define	atop(x)		(((unsigned)(x)) >> page_shift)
#define	ptoa(x)		((vm_offset_t)((x) << page_shift))
E 5
I 5
D 11
#define	atop(x)		(((unsigned)(x)) >> PAGE_SHIFT)
E 11
I 11
#define	atop(x)		(((unsigned long)(x)) >> PAGE_SHIFT)
E 11
#define	ptoa(x)		((vm_offset_t)((x) << PAGE_SHIFT))
E 5
D 9
#endif	KERNEL
E 9

/*
D 9
 *	Round off or truncate to the nearest page.  These will work
 *	for either addresses or counts.  (i.e. 1 byte rounds to 1 page
 *	bytes.
E 9
I 9
 * Round off or truncate to the nearest page.  These will work
 * for either addresses or counts (i.e., 1 byte rounds to 1 page).
E 9
 */
D 9

#ifdef	KERNEL
E 9
D 5
#define round_page(x)	((vm_offset_t)((((vm_offset_t)(x)) + page_mask) & ~page_mask))
#define trunc_page(x)	((vm_offset_t)(((vm_offset_t)(x)) & ~page_mask))
E 5
I 5
D 11
#define round_page(x) \
E 11
I 11
#define	round_page(x) \
E 11
	((vm_offset_t)((((vm_offset_t)(x)) + PAGE_MASK) & ~PAGE_MASK))
D 11
#define trunc_page(x) \
E 11
I 11
#define	trunc_page(x) \
E 11
	((vm_offset_t)(((vm_offset_t)(x)) & ~PAGE_MASK))
D 11
#define num_pages(x) \
E 11
I 11
#define	num_pages(x) \
E 11
	((vm_offset_t)((((vm_offset_t)(x)) + PAGE_MASK) >> PAGE_SHIFT))
E 5
D 9
#else	KERNEL
D 5
#define	round_page(x)	((((vm_offset_t)(x) + (vm_page_size - 1)) / vm_page_size) * vm_page_size)
#define	trunc_page(x)	((((vm_offset_t)(x)) / vm_page_size) * vm_page_size)
E 5
I 5
#define	round_page(x) \
       ((((vm_offset_t)(x) + (vm_page_size - 1)) / vm_page_size) * vm_page_size)
#define	trunc_page(x) \
	((((vm_offset_t)(x)) / vm_page_size) * vm_page_size)
E 5
#endif	KERNEL
E 9

D 9
#ifdef	KERNEL
E 9
D 3
extern vm_size_t	page_size;	/* machine independent page size */
extern vm_size_t	page_mask;	/* page_size - 1; mask for
E 3
I 3
D 4
extern vm_size_t	page_mask;	/* vm_stat.page_size - 1; mask for
E 4
I 4
D 5
extern vm_size_t	page_mask;	/* cnt.v_page_size - 1; mask for
E 4
E 3
						   offset within page */
extern int		page_shift;	/* shift to use for page size */

E 5
extern vm_size_t	mem_size;	/* size of physical memory (bytes) */
extern vm_offset_t	first_addr;	/* first physical page */
extern vm_offset_t	last_addr;	/* last physical page */
D 9
#endif	KERNEL
E 9

D 9
#endif	ASSEMBLER
E 9
I 9
#else
/* out-of-kernel versions of round_page and trunc_page */
#define	round_page(x) \
D 11
       ((((vm_offset_t)(x) + (vm_page_size - 1)) / vm_page_size) * vm_page_size)
E 11
I 11
	((((vm_offset_t)(x) + (vm_page_size - 1)) / vm_page_size) * \
	    vm_page_size)
E 11
#define	trunc_page(x) \
	((((vm_offset_t)(x)) / vm_page_size) * vm_page_size)
E 9

D 9
#endif	_VM_PARAM_
E 9
I 9
#endif /* KERNEL */
#endif /* ASSEMBLER */
#endif /* _VM_PARAM_ */
E 9
E 1
