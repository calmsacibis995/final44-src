/*-
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1994, Sean Eric Fagan
 *
 * %sccs.include.proprietary.c%
 *
 *	from: $Id: sys_process.c,v 1.14 1995/05/30 08:05:58 rgrimes Exp $
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/ptrace.h>
#include <sys/errno.h>
#include <sys/mount.h>
#include <sys/syscallargs.h>

#include <machine/reg.h>
#include <machine/psl.h>
#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_kern.h>

#include <sys/user.h>

static int
pread(procp, addr, retval)
	struct proc *procp;
	unsigned int addr;
	unsigned int *retval;
{
	int		rv;
	vm_map_t	map, tmap;
	vm_object_t	object;
	vm_offset_t	kva = 0;
	int		page_offset;	/* offset into page */
	vm_offset_t	pageno;		/* page number */
	vm_map_entry_t	out_entry;
	vm_prot_t	out_prot;
	boolean_t	wired, single_use;
	vm_offset_t	off;

	/* Map page into kernel space */

	map = &procp->p_vmspace->vm_map;

	page_offset = addr - trunc_page(addr);
	pageno = trunc_page(addr);

	tmap = map;
	rv = vm_map_lookup(&tmap, pageno, VM_PROT_READ, &out_entry,
		&object, &off, &out_prot, &wired, &single_use);

	if (rv != KERN_SUCCESS)
		return (EINVAL);

	vm_map_lookup_done(tmap, out_entry);

	/* Find space in kernel_map for the page we're interested in */
	rv = vm_map_find(kernel_map, object, off, &kva, PAGE_SIZE, 1);

	if (!rv) {
		vm_object_reference(object);

		rv = vm_map_pageable(kernel_map, kva, kva + PAGE_SIZE, 0);
		if (!rv) {
			*retval = 0;
			bcopy((caddr_t)kva + page_offset,
			       retval, sizeof *retval);
		}
		vm_map_remove(kernel_map, kva, kva + PAGE_SIZE);
	}
	return (rv);
}

static int
pwrite(procp, addr, datum)
	struct proc *procp;
	unsigned int addr;
	unsigned int datum;
{
	int		rv;
	vm_map_t	map, tmap;
	vm_object_t	object;
	vm_offset_t	kva = 0;
	int		page_offset;	/* offset into page */
	vm_offset_t	pageno;		/* page number */
	vm_map_entry_t	out_entry;
	vm_prot_t	out_prot;
	boolean_t	wired, single_use;
	vm_offset_t	off;
	boolean_t	fix_prot = 0;

	/* Map page into kernel space */

	map = &procp->p_vmspace->vm_map;

	page_offset = addr - trunc_page(addr);
	pageno = trunc_page(addr);

	/*
	 * Check the permissions for the area we're interested in.
	 */

	if (vm_map_check_protection(map, pageno, pageno + PAGE_SIZE,
	    VM_PROT_WRITE) == FALSE) {
		/*
		 * If the page was not writable, we make it so.
		 * XXX It is possible a page may *not* be read/executable,
		 * if a process changes that!
		 */
		fix_prot = 1;
		/* The page isn't writable, so let's try making it so... */
		if ((rv = vm_map_protect(map, pageno, pageno + PAGE_SIZE,
			VM_PROT_ALL, 0)) != KERN_SUCCESS)
		  return (EFAULT);	/* I guess... */
	}

	/*
	 * Now we need to get the page.  out_entry, out_prot, wired, and
	 * single_use aren't used.  One would think the vm code would be
	 * a *bit* nicer...  We use tmap because vm_map_lookup() can
	 * change the map argument.
	 */

	tmap = map;
	rv = vm_map_lookup(&tmap, pageno, VM_PROT_WRITE, &out_entry,
		&object, &off, &out_prot, &wired, &single_use);
	if (rv != KERN_SUCCESS) {
		return (EINVAL);
	}

	/*
	 * Okay, we've got the page.  Let's release tmap.
	 */

	vm_map_lookup_done(tmap, out_entry);

	/*
	 * Fault the page in...
	 */

	vm_map_pageable(map, trunc_page(vtopte(pageno)),
		trunc_page(vtopte(pageno)) + PAGE_SIZE, FALSE);
	rv = vm_fault(map, pageno, VM_PROT_WRITE|VM_PROT_READ, FALSE);
	vm_map_pageable(map, trunc_page(vtopte(pageno)),
		trunc_page(vtopte(pageno)) + PAGE_SIZE, TRUE);
	if (rv != KERN_SUCCESS)
		return (EFAULT);

	/* Find space in kernel_map for the page we're interested in */
	rv = vm_map_find(kernel_map, object, off, &kva, PAGE_SIZE, 1);

	if (!rv) {
		vm_object_reference(object);

		rv = vm_map_pageable(kernel_map, kva, kva + PAGE_SIZE, 0);
		if (!rv)
			bcopy(&datum, (caddr_t)kva + page_offset, sizeof datum);
		vm_map_remove(kernel_map, kva, kva + PAGE_SIZE);
	}

	if (fix_prot)
		vm_map_protect(map, pageno, pageno + PAGE_SIZE,
			VM_PROT_READ|VM_PROT_EXECUTE, 0);
	return (rv);
}

/*
 * Process debugging system call.
 */
ptrace(curp, uap, retval)
	struct proc *curp;
	struct ptrace_args /* {
		syscallarg(int) req;
		syscallarg(pid_t) pid;
		syscallarg(caddr_t) addr;
		syscallarg(int) data;
	} */ *uap;
	register_t *retval;
{
	struct proc *p;
	int s, error = 0;

	if (SCARG(uap, req) == PT_TRACE_ME) {
		curp->p_flag |= P_TRACED;
		return (0);
	}
	if ((p = pfind(SCARG(uap, pid))) == 0)
		return (ESRCH);
	if (SCARG(uap, req) != PT_ATTACH &&
	    ((p->p_flag & P_TRACED) == 0 ||
	     (p->p_pptr && curp != p->p_pptr) ||
	     (!p->p_pptr && curp != p->p_pptr)))
		return (ESRCH);
	if (SCARG(uap, req) != PT_ATTACH) {
		if ((p->p_flag & P_TRACED) == 0)
			return (EPERM);
		if (p->p_stat != SSTOP || (p->p_flag & P_WAITED) == 0)
			return (EBUSY);
	}
	/*
	 * XXX The PT_ATTACH code is completely broken.  It will
	 * be obsoleted by a /proc filesystem, so is it worth it
	 * to fix it?  (Answer, probably.  So that'll be next,
	 * I guess.)
	 */

	switch (SCARG(uap, req)) {

	case PT_ATTACH:
		/*
		 * Must be root if the process has used set user or group
		 * privileges or does not belong to the real user.  Must
		 * not be already traced.  Can't attach to ourselves.
		 */
		if ((p->p_flag & P_SUGID ||
		    p->p_cred->p_ruid != curp->p_cred->p_ruid) &&
		    (error = suser(p->p_ucred, &p->p_acflag)) != 0)
			return (error);
		if (p->p_flag & P_TRACED)
			return (EALREADY);	/* ??? */
		if (p->p_pid == curp->p_pid)
			return (EINVAL);
		/*
		 * It would be nice if the tracing relationship was separate
		 * from the parent relationship but that would require
		 * another set of links in the proc struct or for "wait"
		 * to scan the entire proc table.  To make life easier,
		 * we just re-parent the process we're trying to trace.
		 * The old parent is remembered so we can put things back
		 * on a "detach".
		 */
		p->p_flag |= P_TRACED;
		p->p_oppid = p->p_pptr->p_pid;
		proc_reparent(p, curp);
		psignal(p, SIGSTOP);
		return (0);

	case PT_DETACH:
		if ((unsigned)SCARG(uap, data) >= NSIG)
			return (EINVAL);
		p->p_flag &= ~P_TRACED;
		if (p->p_oppid != p->p_pptr->p_pid) {
                        struct proc *pp = pfind(p->p_oppid);

                        if (pp)
                                proc_reparent(p, pp);
		}
		p->p_oppid = 0;
		psignal(p->p_pptr, SIGCHLD);
		wakeup((caddr_t)p->p_pptr);
		s = splhigh();
		if (p->p_stat == SSTOP) {
			p->p_xstat = SCARG(uap, data);
			setrunnable(p);
		} else if (SCARG(uap, data)) {
			psignal(p, SCARG(uap, data));
		}
		splx(s);
		return (0);

	case PT_READ_I:
	case PT_READ_D:
		return (pread(p, (unsigned int)SCARG(uap, addr), retval));

	case PT_WRITE_I:
	case PT_WRITE_D:
		return (pwrite(p, (unsigned int)SCARG(uap, addr),
		    (unsigned int)SCARG(uap, data)));

	case PT_STEP:
		if ((error = ptrace_single_step(p)))
			return (error);
		/* fall through */
	case PT_CONTINUE:
		/*
		 * Continue at addr SCARG(uap, addr) with signal
		 * SCARG(uap, data); if SCARG(uap, addr) is 1,
		 * then we just let the chips fall where they may.
		 *
		 * The only check I'll make right now is for SCARG(uap, data)
		 * to be larger than NSIG; if so, we return EINVAL.
		 */
		if (SCARG(uap, data) >= NSIG)
			return (EINVAL);

		if (SCARG(uap, addr) != (caddr_t)1) {
			fill_eproc(p, &p->p_addr->u_kproc.kp_eproc);
			if ((error = ptrace_set_pc(p, (u_int)SCARG(uap, addr))))
				return (error);
		}

		p->p_xstat = SCARG(uap, data);

/*		if (p->p_stat == SSTOP) */
		setrunnable(p);
		return (0);

	case PT_READ_U:
		if ((u_int)SCARG(uap, addr) > (UPAGES * NBPG - sizeof(int)))
			return (EFAULT);
		p->p_addr->u_kproc.kp_proc = *p;
		fill_eproc(p, &p->p_addr->u_kproc.kp_eproc);
		*retval = *(int*)((u_int)p->p_addr + (u_int)SCARG(uap, addr));
		return (0);

	case PT_WRITE_U:
		p->p_addr->u_kproc.kp_proc = *p;
		fill_eproc(p, &p->p_addr->u_kproc.kp_eproc);
		return (ptrace_write_u(p, (vm_offset_t)SCARG(uap, addr),
		    SCARG(uap, data)));

	case PT_KILL:
		p->p_xstat = SIGKILL;
		setrunnable(p);
		return (0);

#ifdef PT_GETREGS
	case PT_GETREGS:
		/*
		 * copyout the registers into addr.  There's no
		 * size constraint!!! *GRRR*
		 */
		return (ptrace_getregs(p, SCARG(uap, addr)));

	case PT_SETREGS:
		/*
		 * copyin the registers from addr.  Again, no
		 * size constraint!!! *GRRRR*
		 */
		return (ptrace_setregs(p, SCARG(uap, addr)));

#endif /* PT_GETREGS */
	default:
		break;
	}

	return (0);
}

int
trace_req(p)
	struct proc *p;
{

	return (1);
}
