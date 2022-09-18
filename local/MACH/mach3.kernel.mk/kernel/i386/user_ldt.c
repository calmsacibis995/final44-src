/* 
 * Mach Operating System
 * Copyright (c) 1994,1993,1992,1991 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	user_ldt.c,v $
 * Revision 2.5  94/12/15  15:26:22  dbg
 * 	More bug fixes...
 * 	[94/09/07            dbg]
 * 
 * 	Fix the fix below...
 * 	[94/07/21            dbg]
 * 
 * Revision 2.4  93/11/17  16:40:43  dbg
 * 	Fixed bug in i386_set_ldt: descriptors were being copied into
 * 	the old LDT (which was sometimes NULL), thus being thrown away
 * 	(!).
 * 	[93/09/10            dbg]
 * 	Removed lint.
 * 	[93/06/17            dbg]
 * 
 * Revision 2.3  92/02/23  19:45:12  elf
 * 	Eliminate keep_wired argument from vm_map_copyin().
 * 	[92/02/23            danner]
 * 
 * Revision 2.2  92/01/03  20:10:02  dbg
 * 	Created.
 * 	[91/08/20            dbg]
 * 
 */

/*
 * User LDT management.
 * Each thread in a task may have its own LDT.
 */

#include <kern/kalloc.h>
#include <kern/memory.h>
#include <kern/thread.h>

#include <vm/vm_kern.h>

#include <i386/seg.h>
#include <i386/thread.h>
#include <i386/user_ldt.h>

char	acc_type[8][3] = {
    /*	code	stack	data */
    {	0,	0,	1	},	/* data */
    {	0,	1,	1	},	/* data, writable */
    {	0,	0,	1	},	/* data, expand-down */
    {	0,	1,	1	},	/* data, writable, expand-down */
    {	1,	0,	0	},	/* code */
    {	1,	0,	1	},	/* code, readable */
    {	1,	0,	0	},	/* code, conforming */
    {	1,	0,	1	},	/* code, readable, conforming */
};

extern struct fake_descriptor ldt[];	/* for system call gate */

boolean_t selector_check(
	thread_t	thread,
	int		sel,
	int		type)	/* code, stack, data */
{
	struct user_ldt	*ldt;
	int	access;

	ldt = thread->pcb->ims.ldt;
	if (ldt == 0) {
	    switch (type) {
		case S_CODE:
		    return sel == USER_CS;
		case S_STACK:
		    return sel == USER_DS;
		case S_DATA:
		    return sel == 0 ||
			   sel == USER_CS ||
			   sel == USER_DS;
	    }
	}

	if (type != S_DATA && sel == 0)
	    return FALSE;
	if ((sel & (SEL_LDT|SEL_PL)) != (SEL_LDT|SEL_PL_U)
	  || sel > ldt->desc.limit_low)
		return FALSE;

	access = ldt->ldt[sel_idx(sel)].access;
	
	if ((access & (ACC_P|ACC_PL|ACC_TYPE_USER))
		!= (ACC_P|ACC_PL_U|ACC_TYPE_USER))
	    return FALSE;
		/* present, pl == pl.user, not system */

	return acc_type[(access & 0xe)>>1][type];
}

/*
 * Add the descriptors to the LDT, starting with
 * the descriptor for 'first_selector'.
 */
kern_return_t
i386_set_ldt(
	thread_t	thread,
	int		first_selector,
	struct real_descriptor *desc_list,
	natural_t	count,
	boolean_t	desc_list_inline)
{
	user_ldt_t	new_ldt, old_ldt, cur_ldt;
	struct real_descriptor *dp;
	int		i;
	pcb_t		pcb;
	vm_size_t	ldt_size_needed;
	int		first_desc = sel_idx(first_selector);
	vm_map_copy_t	old_copy_object;

	if (thread == THREAD_NULL)
	    return KERN_INVALID_ARGUMENT;
	if (first_desc < 0 || first_desc > 8191)
	    return KERN_INVALID_ARGUMENT;
	if (first_desc + count >= 8192)
	    return KERN_INVALID_ARGUMENT;

	/*
	 * If desc_list is not inline, it is in copyin form.
	 * We must copy it out to the kernel map, and wire
	 * it down (we touch it while the PCB is locked).
	 *
	 * We make a copy of the copyin object, and clear
	 * out the old one, so that returning KERN_INVALID_ARGUMENT
	 * will not try to deallocate the data twice.
	 */
	if (!desc_list_inline) {
	    kern_return_t	kr;
	    vm_offset_t		dst_addr;

	    old_copy_object = (vm_map_copy_t) desc_list;

	    kr = vm_map_copyout(ipc_kernel_map, &dst_addr,
				vm_map_copy_copy(old_copy_object));
	    if (kr != KERN_SUCCESS)
		return kr;

	    (void) vm_map_pageable(ipc_kernel_map,
			dst_addr,
			dst_addr + count * sizeof(struct real_descriptor),
			VM_PROT_READ|VM_PROT_WRITE);
	    desc_list = (struct real_descriptor *)dst_addr;
	}

	/*
	 *	Check that all descriptors are valid:
	 *	. not present
	 *	. user privilege level, code segment
	 *	. user privilege level, data segment
	 *	. call gate to a user segment
	 *	. call gate to a kernel segment -
	 *	  forced to call kernel trap entry
	 */
	for (i = 0, dp = desc_list;
	     i < count;
	     i++, dp++)
	{
	    if ((dp->access & ACC_P) == 0) {
		/*
		 *	Segment is not present.  Allow any values
		 *	in descriptor.
		 */
	    }
	    else {
		/*
		 *	Segment is present.  Protection level must
		 *	be 3 (user), and segment must be a non-system
		 *	segment or the special call gate to the kernel.
		 */
		switch (dp->access & ~ACC_A) {
		    case ACC_P:
			/* valid empty descriptor */
			break;
		    case ACC_P | ACC_CALL_GATE:
			/* Mach kernel call */
			*dp = *(struct real_descriptor *)
				&ldt[sel_idx(USER_SCALL)];
			break;
		    case ACC_P | ACC_PL_U | ACC_DATA:
		    case ACC_P | ACC_PL_U | ACC_DATA_W:
		    case ACC_P | ACC_PL_U | ACC_DATA_E:
		    case ACC_P | ACC_PL_U | ACC_DATA_EW:
		    case ACC_P | ACC_PL_U | ACC_CODE:
		    case ACC_P | ACC_PL_U | ACC_CODE_R:
		    case ACC_P | ACC_PL_U | ACC_CODE_C:
		    case ACC_P | ACC_PL_U | ACC_CODE_CR:
		    case ACC_P | ACC_PL_U | ACC_CALL_GATE_16:
		    case ACC_P | ACC_PL_U | ACC_CALL_GATE:
			break;
		    default:
			return KERN_INVALID_ARGUMENT;
		}
	    }
	}

	/*
	 *	Compute the size of the LDT needed.
	 *	(first_desc is counted from 0)
	 */
	ldt_size_needed = sizeof(struct real_descriptor)
			* (first_desc + count);

	pcb = thread->pcb;
	old_ldt = 0;	/* the one to throw away */
	new_ldt = 0;	/* the one to allocate */
    Retry:
	simple_lock(&pcb->lock);
	cur_ldt = pcb->ims.ldt;
	if (cur_ldt == 0 ||
	    cur_ldt->desc.limit_low + 1 < ldt_size_needed)
	{
	    /*
	     * No current LDT, or not big enough
	     */
	    if (new_ldt == 0) {
		simple_unlock(&pcb->lock);

		/*
		 *	Allocate the LDT.  Add one descriptor preceding
		 *	the LDT to describe the LDT itself.
		 */
		new_ldt = (user_ldt_t)
				kalloc(ldt_size_needed
				       + sizeof(struct real_descriptor));
		/*
		 *	Clear the LDT.
		 */
		bzero(&new_ldt->ldt[0], ldt_size_needed);

		/*
		 *	Build a descriptor that describes the
		 *	LDT itself.
		 */
	    {
		vm_offset_t	ldt_base;

		ldt_base = (vm_offset_t) &new_ldt->ldt[0];

		new_ldt->desc.limit_low   = ldt_size_needed - 1;
		new_ldt->desc.limit_high  = 0;
		new_ldt->desc.base_low    = ldt_base & 0xffff;
		new_ldt->desc.base_med    = (ldt_base >> 16) & 0xff;
		new_ldt->desc.base_high   = ldt_base >> 24;
		new_ldt->desc.access      = ACC_P | ACC_LDT;
		new_ldt->desc.granularity = 0;
	    }

		goto Retry;
	    }

	    /*
	     * Have new LDT.  Copy descriptors from current to new.
	     */
	    if (cur_ldt)
		bcopy(&cur_ldt->ldt[0],
		      &new_ldt->ldt[0],
		      cur_ldt->desc.limit_low + 1);

	    old_ldt = cur_ldt;	/* discard old LDT */
	    cur_ldt = new_ldt;	/* use new LDT from now on */
	    new_ldt = 0;	/* keep new LDT */

	    pcb->ims.ldt = cur_ldt;	/* set LDT for thread */
	}

	/*
	 * Install new descriptors.
	 */
	bcopy(desc_list,
	      &cur_ldt->ldt[first_desc],
	      count * sizeof(struct real_descriptor));

	simple_unlock(&pcb->lock);

	/*
	 *	Discard old LDT if it was replaced
	 */
	if (old_ldt)
	    kfree((vm_offset_t)old_ldt,
		  old_ldt->desc.limit_low + 1
		+ sizeof(struct real_descriptor));

	/*
	 *	Discard new LDT if it was not used
	 */
	if (new_ldt)
	    kfree((vm_offset_t)new_ldt,
		  new_ldt->desc.limit_low + 1
		+ sizeof(struct real_descriptor));

	/*
	 * Free the descriptor list, if it was
	 * out-of-line.  Also discard the original
	 * copy object for it.
	 */
	if (!desc_list_inline) {
	    (void) kmem_free(ipc_kernel_map,
			(vm_offset_t) desc_list,
			count * sizeof(struct real_descriptor));
	    vm_map_copy_discard(old_copy_object);
	}

	return KERN_SUCCESS;
}

kern_return_t
i386_get_ldt(
	thread_t	thread,
	int		first_selector,
	int		selector_count,		/* number wanted */
	struct real_descriptor **desc_list,	/* in/out */
	natural_t	*count)			/* in/out */
{
	struct user_ldt *user_ldt;
	pcb_t		pcb = thread->pcb;
	int		first_desc = sel_idx(first_selector);
	unsigned int	ldt_count;
	vm_size_t	ldt_size;
	vm_size_t	size, size_needed;
	vm_offset_t	addr;

	if (thread == THREAD_NULL)
	    return KERN_INVALID_ARGUMENT;
	if (first_desc < 0 || first_desc > 8191)
	    return KERN_INVALID_ARGUMENT;
	if (first_desc + selector_count >= 8192)
	    return KERN_INVALID_ARGUMENT;

	addr = 0;
	size = 0;

	for (;;) {
	    simple_lock(&pcb->lock);
	    user_ldt = pcb->ims.ldt;
	    if (user_ldt == 0) {
		simple_unlock(&pcb->lock);
		if (addr)
		    kmem_free(ipc_kernel_map, addr, size);
		*count = 0;
		return KERN_SUCCESS;
	    }

	    /*
	     * Find how many descriptors we should return.
	     */
	    ldt_count = (user_ldt->desc.limit_low + 1) /
			sizeof (struct real_descriptor);
	    ldt_count -= first_desc;
	    if (ldt_count > selector_count)
		ldt_count = selector_count;

	    ldt_size = ldt_count * sizeof(struct real_descriptor);

	    /*
	     * Do we have the memory we need?
	     */
	    if (ldt_count <= *count)
		break;		/* fits in-line */

	    size_needed = round_page(ldt_size);
	    if (size_needed <= size)
		break;

	    /*
	     * Unlock the pcb and allocate more memory
	     */
	    simple_unlock(&pcb->lock);

	    if (size != 0)
		kmem_free(ipc_kernel_map, addr, size);

	    size = size_needed;

	    if (kmem_alloc(ipc_kernel_map, &addr, size)
			!= KERN_SUCCESS)
		return KERN_RESOURCE_SHORTAGE;
	}

	/*
	 * copy out the descriptors
	 */
	bcopy(&user_ldt[first_desc],
	      *desc_list,
	      ldt_size);
	*count = ldt_count;
	simple_unlock(&pcb->lock);

	if (addr) {
	    vm_size_t		size_used, size_left;
	    vm_map_copy_t	memory;

	    /*
	     * Free any unused memory beyond the end of the last page used
	     */
	    size_used = round_page(ldt_size);
	    if (size_used != size)
		kmem_free(ipc_kernel_map,
			addr + size_used, size - size_used);

	    /*
	     * Zero the remainder of the page being returned.
	     */
	    size_left = size_used - ldt_size;
	    if (size_left > 0)
		bzero((void *)addr + ldt_size, size_left);

	    /*
	     * Make memory into copyin form - this unwires it.
	     */
	    (void) vm_map_copyin(ipc_kernel_map, addr, size_used, TRUE, &memory);
	    *desc_list = (struct real_descriptor *)memory;
	}

	return KERN_SUCCESS;
}

void
user_ldt_free(
	user_ldt_t	user_ldt)
{
	kfree((vm_offset_t)user_ldt,
		user_ldt->desc.limit_low + 1
		+ sizeof(struct real_descriptor));
}

void
user_ldt_init(void)
{
	/* nothing here yet... */
}
