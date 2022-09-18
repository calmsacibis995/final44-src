h18203
s 00002/00004/00272
d D 8.5 94/06/15 12:30:46 pendry 5 4
c merge in netbsd changes.
c security fixes, curproc becomes symlink, misc other trash.
e
s 00002/00002/00274
d D 8.4 94/01/21 19:59:08 bostic 4 3
c copyright typo
e
s 00001/00000/00275
d D 8.3 94/01/21 18:40:10 bostic 3 2
c add SEF's coypright notice
e
s 00001/00001/00274
d D 8.2 94/01/17 14:44:17 pendry 2 1
c update contrib line
e
s 00275/00000/00000
d D 8.1 94/01/05 12:34:10 pendry 1 0
c date and time created 94/01/05 12:34:10 by pendry
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1993 The Regents of the University of California.
E 4
 * Copyright (c) 1993 Jan-Simon Pendry
I 3
 * Copyright (c) 1993 Sean Eric Fagan
E 3
D 4
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
D 2
 * Jan-Simon Pendry.
E 2
I 2
 * Jan-Simon Pendry and Sean Eric Fagan.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * From:
 *	$Id: procfs_mem.c,v 3.2 1993/12/15 09:40:17 jsp Exp $
 */

/*
 * This is a lightly hacked and merged version
 * of sef's pread/pwrite functions
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <miscfs/procfs/procfs.h>
#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>

static int
procfs_rwmem(p, uio)
	struct proc *p;
	struct uio *uio;
{
	int error;
	int writing;

	writing = uio->uio_rw == UIO_WRITE;

	/*
	 * Only map in one page at a time.  We don't have to, but it
	 * makes things easier.  This way is trivial - right?
	 */
	do {
		vm_map_t map, tmap;
		vm_object_t object;
		vm_offset_t kva;
		vm_offset_t uva;
		int page_offset;		/* offset into page */
		vm_offset_t pageno;		/* page number */
		vm_map_entry_t out_entry;
		vm_prot_t out_prot;
		vm_page_t m;
		boolean_t wired, single_use;
		vm_offset_t off;
		u_int len;
		int fix_prot;

		uva = (vm_offset_t) uio->uio_offset;
		if (uva > VM_MAXUSER_ADDRESS) {
			error = 0;
			break;
		}

		/*
		 * Get the page number of this segment.
		 */
		pageno = trunc_page(uva);
		page_offset = uva - pageno;

		/*
		 * How many bytes to copy
		 */
		len = min(PAGE_SIZE - page_offset, uio->uio_resid);

		/*
		 * The map we want...
		 */
		map = &p->p_vmspace->vm_map;
  
		/*
		 * Check the permissions for the area we're interested
		 * in.
		 */
		fix_prot = 0;
		if (writing)
			fix_prot = !vm_map_check_protection(map, pageno,
					pageno + PAGE_SIZE, VM_PROT_WRITE);

		if (fix_prot) {
			/*
			 * If the page is not writable, we make it so.
			 * XXX It is possible that a page may *not* be
			 * read/executable, if a process changes that!
			 * We will assume, for now, that a page is either
			 * VM_PROT_ALL, or VM_PROT_READ|VM_PROT_EXECUTE.
			 */
			error = vm_map_protect(map, pageno,
					pageno + PAGE_SIZE, VM_PROT_ALL, 0);
			if (error)
				break;
		}

		/*
		 * Now we need to get the page.  out_entry, out_prot, wired,
		 * and single_use aren't used.  One would think the vm code
		 * would be a *bit* nicer...  We use tmap because
		 * vm_map_lookup() can change the map argument.
		 */
		tmap = map;
		error = vm_map_lookup(&tmap, pageno,
				      writing ? VM_PROT_WRITE : VM_PROT_READ,
				      &out_entry, &object, &off, &out_prot,
				      &wired, &single_use);
		/*
		 * We're done with tmap now.
		 */
		if (!error)
			vm_map_lookup_done(tmap, out_entry);
  
		/*
		 * Fault the page in...
		 */
		if (!error && writing && object->shadow) {
			m = vm_page_lookup(object, off);
			if (m == 0 || (m->flags & PG_COPYONWRITE))
				error = vm_fault(map, pageno,
							VM_PROT_WRITE, FALSE);
		}

		/* Find space in kernel_map for the page we're interested in */
		if (!error)
			error = vm_map_find(kernel_map, object, off, &kva,
					PAGE_SIZE, 1);

		if (!error) {
			/*
			 * Neither vm_map_lookup() nor vm_map_find() appear
			 * to add a reference count to the object, so we do
			 * that here and now.
			 */
			vm_object_reference(object);

			/*
			 * Mark the page we just found as pageable.
			 */
			error = vm_map_pageable(kernel_map, kva,
				kva + PAGE_SIZE, 0);

			/*
			 * Now do the i/o move.
			 */
			if (!error)
				error = uiomove(kva + page_offset, len, uio);

			vm_map_remove(kernel_map, kva, kva + PAGE_SIZE);
		}
		if (fix_prot)
			vm_map_protect(map, pageno, pageno + PAGE_SIZE,
					VM_PROT_READ|VM_PROT_EXECUTE, 0);
	} while (error == 0 && uio->uio_resid > 0);

	return (error);
}

/*
 * Copy data in and out of the target process.
 * We do this by mapping the process's page into
 * the kernel and then doing a uiomove direct
 * from the kernel address space.
 */
int
procfs_domem(curp, p, pfs, uio)
	struct proc *curp;
	struct proc *p;
	struct pfsnode *pfs;
	struct uio *uio;
{
D 5
	int error;
E 5

	if (uio->uio_resid == 0)
		return (0);

D 5
	error = procfs_rwmem(p, uio);

	return (error);
E 5
I 5
	return (procfs_rwmem(p, uio));
E 5
}

/*
 * Given process (p), find the vnode from which
 * it's text segment is being executed.
 *
 * It would be nice to grab this information from
 * the VM system, however, there is no sure-fire
 * way of doing that.  Instead, fork(), exec() and
 * wait() all maintain the p_textvp field in the
 * process proc structure which contains a held
 * reference to the exec'ed vnode.
 */
struct vnode *
procfs_findtextvp(p)
	struct proc *p;
{
I 5

E 5
	return (p->p_textvp);
}


#ifdef probably_never
/*
 * Given process (p), find the vnode from which
 * it's text segment is being mapped.
 *
 * (This is here, rather than in procfs_subr in order
 * to keep all the VM related code in one place.)
 */
struct vnode *
procfs_findtextvp(p)
	struct proc *p;
{
	int error;
	vm_object_t object;
	vm_offset_t pageno;		/* page number */

	/* find a vnode pager for the user address space */

	for (pageno = VM_MIN_ADDRESS;
			pageno < VM_MAXUSER_ADDRESS;
			pageno += PAGE_SIZE) {
		vm_map_t map;
		vm_map_entry_t out_entry;
		vm_prot_t out_prot;
		boolean_t wired, single_use;
		vm_offset_t off;

		map = &p->p_vmspace->vm_map;
		error = vm_map_lookup(&map, pageno,
			      VM_PROT_READ,
			      &out_entry, &object, &off, &out_prot,
			      &wired, &single_use);

		if (!error) {
			vm_pager_t pager;

			printf("procfs: found vm object\n");
			vm_map_lookup_done(map, out_entry);
			printf("procfs: vm object = %x\n", object);

			/*
			 * At this point, assuming no errors, object
			 * is the VM object mapping UVA (pageno).
			 * Ensure it has a vnode pager, then grab
			 * the vnode from that pager's handle.
			 */

			pager = object->pager;
			printf("procfs: pager = %x\n", pager);
			if (pager)
				printf("procfs: found pager, type = %d\n", pager->pg_type);
			if (pager && pager->pg_type == PG_VNODE) {
				struct vnode *vp;

				vp = (struct vnode *) pager->pg_handle;
				printf("procfs: vp = 0x%x\n", vp);
				return (vp);
			}
		}
	}

	printf("procfs: text object not found\n");
	return (0);
}
#endif /* probably_never */
E 1
