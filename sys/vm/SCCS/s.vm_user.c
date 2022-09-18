h38061
s 00081/00026/00205
d D 8.2 94/01/12 16:07:34 hibler 7 6
c cleanup.
e
s 00002/00002/00229
d D 8.1 93/06/11 16:38:46 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00024/00203
d D 7.5 92/07/10 19:11:48 torek 5 4
c ANSIfy syscall args
e
s 00012/00005/00215
d D 7.4 92/05/04 17:24:07 bostic 4 3
c new include format; lint
e
s 00027/00004/00193
d D 7.3 91/04/21 18:36:25 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00007/00012/00190
d D 7.2 91/04/20 10:50:24 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00202/00000/00000
d D 7.1 90/12/05 18:08:49 mckusick 1 0
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
 *	User-exported virtual memory functions.
 */

D 4
#include "param.h"
#include "systm.h"
D 2
#include "user.h"
E 2
#include "proc.h"
E 4
I 4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
E 4

D 2
#include "../vm/vm_param.h"
#include "../vm/vm_object.h"
#include "../vm/vm_map.h"
#include "../vm/vm_page.h"
#include "../vm/vm_statistics.h"
E 2
I 2
D 4
#include "vm.h"
#include "vm_page.h"
E 4
I 4
#include <vm/vm.h>
E 4
E 2

D 2
#include "lock.h"			/* XXX */
E 2
simple_lock_data_t	vm_alloc_lock;	/* XXX */

#ifdef MACHVMCOMPAT
/*
 * BSD style syscall interfaces to MACH calls
 * All return MACH return values.
 */
I 5
struct svm_allocate_args {
	vm_map_t map;
	vm_offset_t *addr;
	vm_size_t size;
	boolean_t anywhere;
};
E 5
/* ARGSUSED */
I 4
int
E 4
svm_allocate(p, uap, retval)
	struct proc *p;
D 5
	struct args {
		vm_map_t map;
		vm_offset_t *addr;
		vm_size_t size;
		boolean_t anywhere;
	} *uap;
E 5
I 5
	struct svm_allocate_args *uap;
E 5
	int *retval;
{
	vm_offset_t addr;
	int rv;

	uap->map = p->p_map;		/* XXX */

	if (copyin((caddr_t)uap->addr, (caddr_t)&addr, sizeof (addr)))
		rv = KERN_INVALID_ARGUMENT;
	else
		rv = vm_allocate(uap->map, &addr, uap->size, uap->anywhere);
	if (rv == KERN_SUCCESS) {
		if (copyout((caddr_t)&addr, (caddr_t)uap->addr, sizeof(addr)))
			rv = KERN_INVALID_ARGUMENT;
	}
	return((int)rv);
}

I 5
struct svm_deallocate_args {
	vm_map_t map;
	vm_offset_t addr;
	vm_size_t size;
};
E 5
/* ARGSUSED */
I 4
int
E 4
svm_deallocate(p, uap, retval)
	struct proc *p;
D 5
	struct args {
		vm_map_t map;
		vm_offset_t addr;
		vm_size_t size;
	} *uap;
E 5
I 5
	struct svm_deallocate_args *uap;
E 5
	int *retval;
{
	int rv;

	uap->map = p->p_map;		/* XXX */
	rv = vm_deallocate(uap->map, uap->addr, uap->size);
	return((int)rv);
}

I 5
struct svm_inherit_args {
	vm_map_t map;
	vm_offset_t addr;
	vm_size_t size;
	vm_inherit_t inherit;
};
E 5
/* ARGSUSED */
I 4
int
E 4
svm_inherit(p, uap, retval)
	struct proc *p;
D 5
	struct args {
		vm_map_t map;
		vm_offset_t addr;
		vm_size_t size;
		vm_inherit_t inherit;
	} *uap;
E 5
I 5
	struct svm_inherit_args *uap;
E 5
	int *retval;
{
	int rv;

	uap->map = p->p_map;		/* XXX */
	rv = vm_inherit(uap->map, uap->addr, uap->size, uap->inherit);
	return((int)rv);
}

I 5
struct svm_protect_args {
	vm_map_t map;
	vm_offset_t addr;
	vm_size_t size;
	boolean_t setmax;
	vm_prot_t prot;
};
E 5
/* ARGSUSED */
I 4
int
E 4
svm_protect(p, uap, retval)
	struct proc *p;
D 5
	struct args {
		vm_map_t map;
		vm_offset_t addr;
		vm_size_t size;
		boolean_t setmax;
		vm_prot_t prot;
	} *uap;
E 5
I 5
	struct svm_protect_args *uap;
E 5
	int *retval;
{
	int rv;

	uap->map = p->p_map;		/* XXX */
	rv = vm_protect(uap->map, uap->addr, uap->size, uap->setmax, uap->prot);
	return((int)rv);
}
I 7

/*
 *	vm_inherit sets the inheritence of the specified range in the
 *	specified map.
 */
int
vm_inherit(map, start, size, new_inheritance)
	register vm_map_t	map;
	vm_offset_t		start;
	vm_size_t		size;
	vm_inherit_t		new_inheritance;
{
	if (map == NULL)
		return(KERN_INVALID_ARGUMENT);

	return(vm_map_inherit(map, trunc_page(start), round_page(start+size), new_inheritance));
}

/*
 *	vm_protect sets the protection of the specified range in the
 *	specified map.
 */

int
vm_protect(map, start, size, set_maximum, new_protection)
	register vm_map_t	map;
	vm_offset_t		start;
	vm_size_t		size;
	boolean_t		set_maximum;
	vm_prot_t		new_protection;
{
	if (map == NULL)
		return(KERN_INVALID_ARGUMENT);

	return(vm_map_protect(map, trunc_page(start), round_page(start+size), new_protection, set_maximum));
}
E 7
#endif

/*
 *	vm_allocate allocates "zero fill" memory in the specfied
 *	map.
 */
I 4
int
E 4
vm_allocate(map, addr, size, anywhere)
	register vm_map_t	map;
	register vm_offset_t	*addr;
	register vm_size_t	size;
	boolean_t		anywhere;
{
	int	result;

D 2
	if (map == VM_MAP_NULL)
E 2
I 2
	if (map == NULL)
E 2
		return(KERN_INVALID_ARGUMENT);
	if (size == 0) {
		*addr = 0;
		return(KERN_SUCCESS);
	}

	if (anywhere)
		*addr = vm_map_min(map);
	else
		*addr = trunc_page(*addr);
	size = round_page(size);

D 2
	result = vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t) 0, addr,
E 2
I 2
D 7
	result = vm_map_find(map, NULL, (vm_offset_t) 0, addr,
E 2
			size, anywhere);
E 7
I 7
	result = vm_map_find(map, NULL, (vm_offset_t) 0, addr, size, anywhere);
E 7

	return(result);
}

/*
 *	vm_deallocate deallocates the specified range of addresses in the
 *	specified address map.
 */
I 4
int
E 4
vm_deallocate(map, start, size)
	register vm_map_t	map;
	vm_offset_t		start;
	vm_size_t		size;
{
D 2
	if (map == VM_MAP_NULL)
E 2
I 2
	if (map == NULL)
E 2
		return(KERN_INVALID_ARGUMENT);

	if (size == (vm_offset_t) 0)
		return(KERN_SUCCESS);

	return(vm_map_remove(map, trunc_page(start), round_page(start+size)));
}

/*
D 7
 *	vm_inherit sets the inheritence of the specified range in the
 *	specified map.
E 7
I 7
 * Similar to vm_allocate but assigns an explicit pager.
E 7
 */
I 4
int
E 4
D 7
vm_inherit(map, start, size, new_inheritance)
E 7
I 7
vm_allocate_with_pager(map, addr, size, anywhere, pager, poffset, internal)
E 7
	register vm_map_t	map;
D 7
	vm_offset_t		start;
	vm_size_t		size;
	vm_inherit_t		new_inheritance;
E 7
I 7
	register vm_offset_t	*addr;
	register vm_size_t	size;
	boolean_t		anywhere;
	vm_pager_t		pager;
	vm_offset_t		poffset;
	boolean_t		internal;
E 7
{
I 7
	register vm_object_t	object;
	register int		result;

E 7
D 2
	if (map == VM_MAP_NULL)
E 2
I 2
	if (map == NULL)
E 2
		return(KERN_INVALID_ARGUMENT);

D 7
	return(vm_map_inherit(map, trunc_page(start), round_page(start+size), new_inheritance));
}
E 7
I 7
	*addr = trunc_page(*addr);
	size = round_page(size);
E 7

D 7
/*
 *	vm_protect sets the protection of the specified range in the
 *	specified map.
 */
E 7
I 7
	/*
	 *	Lookup the pager/paging-space in the object cache.
	 *	If it's not there, then create a new object and cache
	 *	it.
	 */
	object = vm_object_lookup(pager);
	cnt.v_lookups++;
	if (object == NULL) {
		object = vm_object_allocate(size);
		/*
		 * From Mike Hibler: "unnamed anonymous objects should never
		 * be on the hash list ... For now you can just change
		 * vm_allocate_with_pager to not do vm_object_enter if this
		 * is an internal object ..."
		 */
		if (!internal)
			vm_object_enter(object, pager);
	} else
		cnt.v_hits++;
	if (internal)
		object->flags |= OBJ_INTERNAL;
	else {
		object->flags &= ~OBJ_INTERNAL;
		cnt.v_nzfod -= atop(size);
	}
E 7

I 4
D 7
int
E 4
vm_protect(map, start, size, set_maximum, new_protection)
	register vm_map_t	map;
	vm_offset_t		start;
	vm_size_t		size;
	boolean_t		set_maximum;
	vm_prot_t		new_protection;
{
D 2
	if (map == VM_MAP_NULL)
E 2
I 2
	if (map == NULL)
E 2
		return(KERN_INVALID_ARGUMENT);

	return(vm_map_protect(map, trunc_page(start), round_page(start+size), new_protection, set_maximum));
E 7
I 7
	result = vm_map_find(map, object, poffset, addr, size, anywhere);
	if (result != KERN_SUCCESS)
		vm_object_deallocate(object);
	else if (pager != NULL)
		vm_object_setpager(object, pager, (vm_offset_t) 0, TRUE);
	return(result);
E 7
}
E 1
