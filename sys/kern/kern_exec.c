/*-
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)kern_exec.c	8.10 (Berkeley) 5/14/95
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/filedesc.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/mount.h>
#include <sys/malloc.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/acct.h>
#include <sys/exec.h>
#include <sys/ktrace.h>
#include <sys/resourcevar.h>
#include <sys/syscallargs.h>

#include <machine/cpu.h>
#include <machine/reg.h>

#include <sys/mman.h>
#include <vm/vm.h>
#include <vm/vm_param.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_pager.h>

#include <sys/signalvar.h>

#ifdef HPUXCOMPAT
#include <sys/user.h>			/* for pcb */
#include <hp/hpux/hpux_exec.h>
#endif

#ifdef COPY_SIGCODE
extern char sigcode[], esigcode[];
#define	szsigcode	(esigcode - sigcode)
#else
#define	szsigcode	0
#endif

/*
 * exec system call
 */
execve(p, uap, retval)
	register struct proc *p;
	register struct execve_args /* {
		syscallarg(char *) path;
		syscallarg(char **) argp;  
		syscallarg(char **) envp;
	} */ *uap;      
	register_t *retval;
{
	register struct ucred *cred = p->p_ucred;
	register struct filedesc *fdp = p->p_fd;
	int na, ne, ucp, ap, cc, ssize;
	register char *cp;
	register int nc;
	unsigned len;
	int indir, uid, gid;
	char *sharg;
	struct vnode *vp;
	int resid, error, paged = 0;
	vm_offset_t execargs = 0;
	struct vattr vattr;
	char cfarg[MAXINTERP];
	union {
		char	ex_shell[MAXINTERP];	/* #! and interpreter name */
		struct	exec ex_exec;
#ifdef HPUXCOMPAT
		struct	hpux_exec ex_hexec;
#endif
	} exdata;
#ifdef HPUXCOMPAT
	struct hpux_exec hhead;
#endif
	struct nameidata nd;
	struct ps_strings ps;

	NDINIT(&nd, LOOKUP, FOLLOW | SAVENAME, UIO_USERSPACE,
		SCARG(uap, path), p);
	if (error = namei(&nd))
		return (error);
	vp = nd.ni_vp;
	VOP_LEASE(vp, p, cred, LEASE_READ);
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
	indir = 0;
	uid = cred->cr_uid;
	gid = cred->cr_gid;
	if (error = VOP_GETATTR(vp, &vattr, cred, p))
		goto bad;
	if (vp->v_mount->mnt_flag & MNT_NOEXEC) {
		error = EACCES;
		goto bad;
	}
	if ((vp->v_mount->mnt_flag & MNT_NOSUID) == 0) {
		if (vattr.va_mode & VSUID)
			uid = vattr.va_uid;
		if (vattr.va_mode & VSGID)
			gid = vattr.va_gid;
	}

  again:
	if (error = VOP_ACCESS(vp, VEXEC, cred, p))
		goto bad;
	if ((p->p_flag & P_TRACED) && (error = VOP_ACCESS(vp, VREAD, cred, p)))
		goto bad;
	if (vp->v_type != VREG ||
	    (vattr.va_mode & (VEXEC|(VEXEC>>3)|(VEXEC>>6))) == 0) {
		error = EACCES;
		goto bad;
	}

	/*
	 * Read in first few bytes of file for segment sizes, magic number:
	 *	OMAGIC = plain executable
	 *	NMAGIC = RO text
	 *	ZMAGIC = demand paged RO text
	 * Also an ASCII line beginning with #! is
	 * the file name of a ``shell'' and arguments may be prepended
	 * to the argument list if given here.
	 *
	 * SHELL NAMES ARE LIMITED IN LENGTH.
	 *
	 * ONLY ONE ARGUMENT MAY BE PASSED TO THE SHELL FROM
	 * THE ASCII LINE.
	 */
	exdata.ex_shell[0] = '\0';	/* for zero length files */
	error = vn_rdwr(UIO_READ, vp, (caddr_t)&exdata, sizeof (exdata),
	    (off_t)0, UIO_SYSSPACE, (IO_UNIT|IO_NODELOCKED), cred, &resid,
	    (struct proc *)0);
	if (error)
		goto bad;
#ifndef lint
	if (resid > sizeof(exdata) - sizeof(exdata.ex_exec) &&
	    exdata.ex_shell[0] != '#') {
		error = ENOEXEC;
		goto bad;
	}
#endif
#if defined(hp300) || defined(luna68k)
	switch ((int)exdata.ex_exec.a_mid) {

	/*
	 * An ancient hp200 or hp300 binary, shouldn't happen anymore.
	 * Mark as invalid.
	 */
	case MID_ZERO:
		exdata.ex_exec.a_magic = 0;
		break;

	/*
	 * HP200 series has a smaller page size so we cannot
	 * demand-load or even write protect text, so we just
	 * treat as OMAGIC.
	 */
	case MID_HP200:
		exdata.ex_exec.a_magic = OMAGIC;
		break;

	case MID_HP300:
		break;

#ifdef HPUXCOMPAT
	case MID_HPUX:
		/*
		 * Save a.out header.  This is eventually saved in the pcb,
		 * but we cannot do that yet in case the exec fails before
		 * the image is overlayed.
		 */
		bcopy((caddr_t)&exdata.ex_hexec,
		      (caddr_t)&hhead, sizeof hhead);
		/*
		 * Shuffle important fields to their BSD locations.
		 * Note that the order in which this is done is important.
		 */
		exdata.ex_exec.a_text = exdata.ex_hexec.ha_text;
		exdata.ex_exec.a_data = exdata.ex_hexec.ha_data;
		exdata.ex_exec.a_bss = exdata.ex_hexec.ha_bss;
		exdata.ex_exec.a_entry = exdata.ex_hexec.ha_entry;
		/*
		 * For ZMAGIC files, make sizes consistant with those
		 * generated by BSD ld.
		 */
		if (exdata.ex_exec.a_magic == ZMAGIC) {
			exdata.ex_exec.a_text = 
				ctob(btoc(exdata.ex_exec.a_text));
			nc = exdata.ex_exec.a_data + exdata.ex_exec.a_bss;
			exdata.ex_exec.a_data =
				ctob(btoc(exdata.ex_exec.a_data));
			nc -= (int)exdata.ex_exec.a_data;
			exdata.ex_exec.a_bss = (nc < 0) ? 0 : nc;
		}
		break;
#endif
	}
#endif
	switch ((int)exdata.ex_exec.a_magic) {

	case OMAGIC:
#ifdef COFF
		if (exdata.ex_exec.ex_fhdr.magic != COFF_MAGIC) {
			error = ENOEXEC;
			goto bad;
		}
#endif
#ifdef sparc
		if (exdata.ex_exec.a_mid != MID_SUN_SPARC) {
			error = ENOEXEC;
			goto bad;
		}
#endif
		exdata.ex_exec.a_data += exdata.ex_exec.a_text;
		exdata.ex_exec.a_text = 0;
		break;

	case ZMAGIC:
		paged = 1;
		/* FALLTHROUGH */

	case NMAGIC:
#ifdef COFF
		if (exdata.ex_exec.ex_fhdr.magic != COFF_MAGIC) {
			error = ENOEXEC;
			goto bad;
		}
#endif
#ifdef sparc
		if (exdata.ex_exec.a_mid != MID_SUN_SPARC) {
			error = ENOEXEC;
			goto bad;
		}
#endif
		if (exdata.ex_exec.a_text == 0) {
			error = ENOEXEC;
			goto bad;
		}
		break;

	default:
		if (exdata.ex_shell[0] != '#' ||
		    exdata.ex_shell[1] != '!' ||
		    indir) {
			error = ENOEXEC;
			goto bad;
		}
		for (cp = &exdata.ex_shell[2];; ++cp) {
			if (cp >= &exdata.ex_shell[MAXINTERP]) {
				error = ENOEXEC;
				goto bad;
			}
			if (*cp == '\n') {
				*cp = '\0';
				break;
			}
			if (*cp == '\t')
				*cp = ' ';
		}
		cp = &exdata.ex_shell[2];
		while (*cp == ' ')
			cp++;
		nd.ni_dirp = cp;
		while (*cp && *cp != ' ')
			cp++;
		cfarg[0] = '\0';
		if (*cp) {
			*cp++ = '\0';
			while (*cp == ' ')
				cp++;
			if (*cp)
				bcopy((caddr_t)cp, (caddr_t)cfarg, MAXINTERP);
		}
		indir = 1;
		vput(vp);
		nd.ni_segflg = UIO_SYSSPACE;
		if (error = namei(&nd))
			return (error);
		vp = nd.ni_vp;
		VOP_LEASE(vp, p, cred, LEASE_READ);
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
		if (error = VOP_GETATTR(vp, &vattr, cred, p))
			goto bad;
		uid = cred->cr_uid;	/* shell scripts can't be setuid */
		gid = cred->cr_gid;
		goto again;
	}

	/*
	 * Collect arguments on "file" in swap space.
	 */
	na = 0;
	ne = 0;
	nc = 0;
	cc = NCARGS;
	execargs = kmem_alloc_wait(exec_map, NCARGS);
#ifdef DIAGNOSTIC
	if (execargs == (vm_offset_t)0)
		panic("execve: kmem_alloc_wait");
#endif
	cp = (char *) execargs;
	/*
	 * Copy arguments into file in argdev area.
	 */
	if (SCARG(uap, argp)) for (;;) {
		ap = NULL;
		sharg = NULL;
		if (indir && na == 0) {
			sharg = nd.ni_cnd.cn_nameptr;
			ap = (int)sharg;
			SCARG(uap, argp)++;		/* ignore argv[0] */
		} else if (indir && (na == 1 && cfarg[0])) {
			sharg = cfarg;
			ap = (int)sharg;
		} else if (indir && (na == 1 || na == 2 && cfarg[0]))
			ap = (int)SCARG(uap, path);
		else if (SCARG(uap, argp)) {
			ap = fuword((caddr_t)SCARG(uap, argp));
			SCARG(uap, argp)++;
		}
		if (ap == NULL && SCARG(uap, envp)) {
			SCARG(uap, argp) = NULL;
			if ((ap = fuword((caddr_t)SCARG(uap, envp))) != NULL)
				SCARG(uap, envp)++, ne++;
		}
		if (ap == NULL)
			break;
		na++;
		if (ap == -1) {
			error = EFAULT;
			goto bad;
		}
		do {
			if (nc >= NCARGS-1) {
				error = E2BIG;
				break;
			}
			if (sharg) {
				error = copystr(sharg, cp, (unsigned)cc, &len);
				sharg += len;
			} else {
				error = copyinstr((caddr_t)ap, cp, (unsigned)cc,
				    &len);
				ap += len;
			}
			cp += len;
			nc += len;
			cc -= len;
		} while (error == ENAMETOOLONG);
		if (error)
			goto bad;
	}

	/*
	 * XXX the following is excessively bogus
	 *
	 * Compute initial process stack size and location of argc
	 * and character strings.  `nc' is currently just the number
	 * of characters of arg and env strings.
	 *
	 * nc = size of ps_strings structure +
	 *	size of signal code +
	 *	4 bytes of NULL pointer +
	 *	nc,
	 * rounded to nearest integer;
	 * ucp = USRSTACK - nc;		[user characters pointer]
	 * apsize = padding (if any) +
	 *	4 bytes of NULL pointer +
	 *	ne 4-byte pointers to env strings +
	 *	4 bytes of NULL pointer +
	 *	(na-ne) 4-byte pointers to arg strings +
	 *	4 bytes of argc;
	 * (this is the same as nc + (na+3)*4)
	 * ap = ucp - apsize;	[user address of argc]
	 * ssize = ssize + nc + machine-dependent space;
	 */
	nc = (sizeof(ps) + szsigcode + 4 + nc + NBPW-1) & ~(NBPW - 1);
#if defined(sparc) || defined(mips)
	ucp = USRSTACK;
	ssize = ALIGN(nc + (na + 3) * NBPW);
	ap = ucp - ssize;
	ucp -= nc;
#ifdef sparc
	ssize += sizeof(struct rwindow);
#endif
#else
	ssize = (na + 3) * NBPW;
	ucp = USRSTACK - nc;
	ap = ucp - ssize;
	ssize += nc;
#endif
	error = getxfile(p, vp, &exdata.ex_exec, paged, ssize, uid, gid);
	if (error)
		goto bad;

	/* take a reference to the new text vnode (for procfs) */
	if (p->p_textvp)
		vrele(p->p_textvp);
	VREF(vp);
	p->p_textvp = vp;

	vput(vp);
	vp = NULL;

#ifdef HPUXCOMPAT
	/*
	 * We are now committed to the exec so we can save the exec
	 * header in the pcb where we can dump it if necessary in core()
	 */
	if (p->p_md.md_flags & MDP_HPUX)
		bcopy((caddr_t)&hhead,
		      (caddr_t)p->p_addr->u_md.md_exec, sizeof hhead);
#endif

	/*
	 * Copy back arglist.
	 */
	cpu_setstack(p, ap);
	(void) suword((caddr_t)ap, na-ne);
	nc = 0;
	cp = (char *) execargs;
	cc = NCARGS;
	ps.ps_argvstr = (char *)ucp;	/* first argv string */
	ps.ps_nargvstr = na - ne;	/* argc */
	for (;;) {
		ap += NBPW;
		if (na == ne) {
			(void) suword((caddr_t)ap, 0);
			ap += NBPW;
			ps.ps_envstr = (char *)ucp;
			ps.ps_nenvstr = ne;
		}
		if (--na < 0)
			break;
		(void) suword((caddr_t)ap, ucp);
		do {
			error = copyoutstr(cp, (caddr_t)ucp, (unsigned)cc,
			    &len);
			ucp += len;
			cp += len;
			nc += len;
			cc -= len;
		} while (error == ENAMETOOLONG);
		if (error == EFAULT)
			panic("exec: EFAULT");
	}
	(void) suword((caddr_t)ap, 0);
	(void) copyout((caddr_t)&ps, (caddr_t)PS_STRINGS, sizeof(ps));

	execsigs(p);

	for (nc = fdp->fd_lastfile; nc >= 0; --nc) {
		if (fdp->fd_ofileflags[nc] & UF_EXCLOSE) {
			(void) closef(fdp->fd_ofiles[nc], p);
			fdp->fd_ofiles[nc] = NULL;
			fdp->fd_ofileflags[nc] = 0;
			if (nc < fdp->fd_freefile)
				fdp->fd_freefile = nc;
		}
		fdp->fd_ofileflags[nc] &= ~UF_MAPPED;
	}
	/*
	 * Adjust fd_lastfile to account for descriptors closed above.
	 * Don't decrement fd_lastfile past 0, as it's unsigned.
	 */
	while (fdp->fd_lastfile > 0 && fdp->fd_ofiles[fdp->fd_lastfile] == NULL)
		fdp->fd_lastfile--;
	setregs(p, exdata.ex_exec.a_entry, retval);
#ifdef COPY_SIGCODE
	/*
	 * Install sigcode at top of user stack.
	 */
	copyout((caddr_t)sigcode, (caddr_t)PS_STRINGS - szsigcode, szsigcode);
#endif
	/*
	 * Remember file name for accounting.
	 */
	p->p_acflag &= ~AFORK;
	if (nd.ni_cnd.cn_namelen > MAXCOMLEN)
		nd.ni_cnd.cn_namelen = MAXCOMLEN;
	bcopy((caddr_t)nd.ni_cnd.cn_nameptr, (caddr_t)p->p_comm,
	    (unsigned)nd.ni_cnd.cn_namelen);
	p->p_comm[nd.ni_cnd.cn_namelen] = '\0';
	cpu_exec(p);
bad:
	FREE(nd.ni_cnd.cn_pnbuf, M_NAMEI);
	if (execargs)
		kmem_free_wakeup(exec_map, execargs, NCARGS);
	if (vp)
		vput(vp);
	return (error);
}

/*
 * Read in and set up memory for executed file.
 */
getxfile(p, vp, ep, paged, ssize, uid, gid)
	register struct proc *p;
	register struct vnode *vp;
	register struct exec *ep;
	int paged, ssize, uid, gid;
{
	register struct ucred *cred = p->p_ucred;
	register struct vmspace *vm = p->p_vmspace;
	vm_offset_t addr;
	vm_size_t xts, size;
	segsz_t ds;
	off_t toff;
	int error = 0;

#ifdef HPUXCOMPAT
	if (ep->a_mid == MID_HPUX)
		toff = paged ? CLBYTES : sizeof(struct hpux_exec);
	else
#endif
#ifdef COFF
	toff = N_TXTOFF(*ep);
#else
#ifdef sparc
	if (ep->a_mid == MID_SUN_SPARC)
		toff = paged ? 0 : sizeof(struct exec);
	else
#endif
	if (paged)
#ifdef mips
		toff = 0;
#else
		toff = CLBYTES;
#endif
	else
		toff = sizeof (struct exec);
#endif
	if (ep->a_text != 0 && (vp->v_flag & VTEXT) == 0 &&
	    vp->v_writecount != 0)
		return (ETXTBSY);

	/*
	 * Compute text and data sizes and make sure not too large.
	 * Text size is rounded to an ``ld page''; data+bss is left
	 * in machine pages.  Check data and bss separately as they
	 * may overflow when summed together.  (XXX not done yet)
	 */
	xts = roundup(ep->a_text, __LDPGSZ);
	ds = clrnd(btoc(ep->a_data + ep->a_bss));

	/*
	 * If we're sharing the address space, allocate a new space
	 * and release our reference to the old one.  Otherwise,
	 * empty out the existing vmspace.
	 */
#ifdef sparc
	kill_user_windows(p);		/* before addrs go away */
#endif
	if (vm->vm_refcnt > 1) {
		p->p_vmspace = vmspace_alloc(VM_MIN_ADDRESS,
		    VM_MAXUSER_ADDRESS, 1);
		vmspace_free(vm);
		vm = p->p_vmspace;
	} else {
#ifdef SYSVSHM
		if (vm->vm_shm)
			shmexit(p);
#endif
		(void) vm_map_remove(&vm->vm_map, VM_MIN_ADDRESS,
		    VM_MAXUSER_ADDRESS);
	}
	/*
	 * If parent is waiting for us to exec or exit,
	 * P_PPWAIT will be set; clear it and wakeup parent.
	 */
	if (p->p_flag & P_PPWAIT) {
		p->p_flag &= ~P_PPWAIT;
		wakeup((caddr_t) p->p_pptr);
	}
#if defined(HP380) || defined(LUNA2)
	/* default to copyback caching on 68040 */
	if (mmutype == MMU_68040)
		p->p_md.md_flags |= (MDP_CCBDATA|MDP_CCBSTACK);
#endif
#ifdef HPUXCOMPAT
	p->p_md.md_flags &= ~(MDP_HPUX|MDP_HPUXMMAP);
	/* note that we are an HP-UX binary */
	if (ep->a_mid == MID_HPUX)
		p->p_md.md_flags |= MDP_HPUX;
	/* deal with miscellaneous attributes */
	if (ep->a_trsize & HPUXM_VALID) {
		if (ep->a_trsize & HPUXM_DATAWT)
			p->p_md.md_flags &= ~MDP_CCBDATA;
		if (ep->a_trsize & HPUXM_STKWT)
			p->p_md.md_flags &= ~MDP_CCBSTACK;
	}
#endif
#ifdef ULTRIXCOMPAT
	/*
	 * Always start out as an ULTRIX process.
	 * A system call in crt0.o will change us to BSD system calls later.
	 */
	p->p_md.md_flags |= MDP_ULTRIX;
#endif
	p->p_flag |= P_EXEC;
#ifndef COFF
	addr = VM_MIN_ADDRESS;
	if (vm_allocate(&vm->vm_map, &addr, xts + ctob(ds), FALSE)) {
		uprintf("Cannot allocate text+data space\n");
		error = ENOMEM;			/* XXX */
		goto badmap;
	}
	vm->vm_taddr = (caddr_t)VM_MIN_ADDRESS;
	vm->vm_daddr = (caddr_t)(VM_MIN_ADDRESS + xts);
#else /* COFF */
	addr = (vm_offset_t)ep->ex_aout.codeStart;
	vm->vm_taddr = (caddr_t)addr;
	if (vm_allocate(&vm->vm_map, &addr, xts, FALSE)) {
		uprintf("Cannot allocate text space\n");
		error = ENOMEM;			/* XXX */
		goto badmap;
	}
	addr = (vm_offset_t)ep->ex_aout.heapStart;
	vm->vm_daddr = (caddr_t)addr;
	if (vm_allocate(&vm->vm_map, &addr, round_page(ctob(ds)), FALSE)) {
		uprintf("Cannot allocate data space\n");
		error = ENOMEM;			/* XXX */
		goto badmap;
	}
#endif /* COFF */
	size = round_page(MAXSSIZ);		/* XXX */
#ifdef	i386
	addr = trunc_page(USRSTACK - size) - NBPG;	/* XXX */
#else
	addr = trunc_page(USRSTACK - size);
#endif
	if (vm_allocate(&vm->vm_map, &addr, size, FALSE)) {
		uprintf("Cannot allocate stack space\n");
		error = ENOMEM;			/* XXX */
		goto badmap;
	}
	size -= round_page(p->p_rlimit[RLIMIT_STACK].rlim_cur);
	if (vm_map_protect(&vm->vm_map, addr, addr+size, VM_PROT_NONE, FALSE)) {
		uprintf("Cannot protect stack space\n");
		error = ENOMEM;
		goto badmap;
	}
	vm->vm_maxsaddr = (caddr_t)addr;

	if (paged == 0) {
		/*
		 * Read in data segment.
		 */
		(void) vn_rdwr(UIO_READ, vp, vm->vm_daddr, (int) ep->a_data,
			(off_t)(toff + ep->a_text), UIO_USERSPACE,
			(IO_UNIT|IO_NODELOCKED), cred, (int *)0, p);
		/*
		 * Read in text segment if necessary (0410),
		 * and read-protect it.
		 */
		if (ep->a_text > 0) {
			error = vn_rdwr(UIO_READ, vp, vm->vm_taddr,
			    (int)ep->a_text, toff, UIO_USERSPACE,
			    (IO_UNIT|IO_NODELOCKED), cred, (int *)0, p);
			(void) vm_map_protect(&vm->vm_map,
			    (vm_offset_t)vm->vm_taddr,
			    (vm_offset_t)vm->vm_taddr + trunc_page(ep->a_text),
			    VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
		}
	} else {
		/*
		 * Allocate a region backed by the exec'ed vnode.
		 */
#ifndef COFF
		addr = VM_MIN_ADDRESS;
		size = round_page(xts + ep->a_data);
		error = vm_mmap(&vm->vm_map, &addr, size,
			VM_PROT_ALL, VM_PROT_ALL,
			MAP_COPY|MAP_FIXED,
			(caddr_t)vp, (vm_offset_t)toff);
		(void) vm_map_protect(&vm->vm_map, addr, addr + xts,
			VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
#else /* COFF */
		addr = (vm_offset_t)vm->vm_taddr;
		size = xts;
		error = vm_mmap(&vm->vm_map, &addr, size,
			VM_PROT_READ|VM_PROT_EXECUTE, VM_PROT_ALL,
			MAP_COPY|MAP_FIXED,
			(caddr_t)vp, (vm_offset_t)toff);
		toff += size;
		addr = (vm_offset_t)vm->vm_daddr;
		size = round_page(ep->a_data);
		error = vm_mmap(&vm->vm_map, &addr, size,
			VM_PROT_ALL, VM_PROT_ALL,
			MAP_COPY|MAP_FIXED,
			(caddr_t)vp, (vm_offset_t)toff);
#endif /* COFF */
		vp->v_flag |= VTEXT;
	}
	if (error) {
badmap:
		killproc(p, "VM allocation in exec");
		p->p_flag |= P_NOSWAP;
		return(error);
	}

	/*
	 * set SUID/SGID protections, if no tracing
	 */
	p->p_flag &= ~P_SUGID;
	if ((p->p_flag & P_TRACED) == 0) {
		if (uid != cred->cr_uid || gid != cred->cr_gid) {
			p->p_ucred = cred = crcopy(cred);
#ifdef KTRACE
			/*
			 * If process is being ktraced, turn off - unless
			 * root set it.
			 */
			if (p->p_tracep && !(p->p_traceflag & KTRFAC_ROOT)) {
				vrele(p->p_tracep);
				p->p_tracep = NULL;
				p->p_traceflag = 0;
			}
#endif
			cred->cr_uid = uid;
			cred->cr_gid = gid;
			p->p_flag |= P_SUGID;
		}
	} else
		psignal(p, SIGTRAP);
	p->p_cred->p_svuid = cred->cr_uid;
	p->p_cred->p_svgid = cred->cr_gid;
	vm->vm_tsize = btoc(xts);
	vm->vm_dsize = ds;
	vm->vm_ssize = btoc(ssize);
	if (p->p_flag & P_PROFIL)
		stopprofclock(p);
#if defined(tahoe)
	/* move this when tahoe cpu_exec is created */
	p->p_addr->u_pcb.pcb_savacc.faddr = (float *)NULL;
#endif
	return (0);
}
