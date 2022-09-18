h05491
s 00006/00002/00132
d D 8.4 94/06/15 12:34:21 pendry 4 3
c merge in some of the netbsd changes.
e
s 00022/00000/00112
d D 8.3 94/01/27 11:36:49 pendry 3 2
c add stubs for fpreg support
e
s 00002/00002/00110
d D 8.2 94/01/21 19:44:18 bostic 2 1
c copyright typo
e
s 00112/00000/00000
d D 8.1 94/01/05 12:54:31 pendry 1 0
c date and time created 94/01/05 12:54:31 by pendry
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1993 The Regents of the University of California.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 * Copyright (c) 1993 Jan-Simon Pendry
D 2
 * All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * From:
 *	$Id: procfs_i386.c,v 3.2 1993/12/15 09:40:17 jsp Exp $
 */

/*
 * Functions to be implemented here are:
 *
 * procfs_read_regs(proc, regs)
 *	Get the current user-visible register set from the process
 *	and copy it into the regs structure (<machine/reg.h>).
 *	The process is stopped at the time read_regs is called.
 *
 * procfs_write_regs(proc, regs)
 *	Update the current register set from the passed in regs
 *	structure.  Take care to avoid clobbering special CPU
 *	registers or privileged bits in the PSL.
 *	The process is stopped at the time write_regs is called.
 *
I 3
 * procfs_read_fpregs, procfs_write_fpregs
 *	deal with the floating point register set, otherwise as above.
 *
E 3
 * procfs_sstep(proc)
 *	Arrange for the process to trap after executing a single instruction.
 *
 * procfs_fix_sstep(proc)
 *	Cleanup process state after executing a single-step instruction.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/vnode.h>
#include <machine/psl.h>
#include <machine/reg.h>
/*#include <machine/frame.h>*/
#include <miscfs/procfs/procfs.h>

int
procfs_read_regs(p, regs)
	struct proc *p;
	struct reg *regs;
{
	struct frame *f;

	if ((p->p_flag & P_INMEM) == 0)
		return (EIO);

	f = (struct frame *) p->p_md.md_regs;
	bcopy((void *) f->f_regs, (void *) regs->r_regs, sizeof(regs->r_regs));
	regs->r_pc = f->f_pc;
	regs->r_sr = f->f_sr;

	return (0);
}

/*
 * Update the process's current register
 * set.  Depending on the architecture this
 * may have fix-up work to do, especially
 * if the IAR or PCW are modified.
 */
int
procfs_write_regs(p, regs)
	struct proc *p;
	struct reg *regs;
{
	struct frame *f;

	if ((p->p_flag & P_INMEM) == 0)
		return (EIO);

	f = (struct frame *) p->p_md.md_regs;
	bcopy((void *) regs->r_regs, (void *) f->f_regs, sizeof(f->f_regs));
	f->f_pc = regs->r_pc;
	f->f_sr = regs->r_sr;

	return (0);
}
I 3

int
procfs_read_fpregs(p, fpregs)
	struct proc *p;
	struct fpreg *fpregs;
{

	return (EOPNOTSUPP);
}

int
procfs_write_fpregs(p, fpregs)
	struct proc *p;
	struct fpreg *fpregs;
{

	return (EOPNOTSUPP);
}

E 3

int
D 4
procfs_sstep(p)
E 4
I 4
procfs_sstep(p, sstep)
E 4
	struct proc *p;
I 4
	int sstep;
E 4
{
	int error;
	struct reg r;

	error = procfs_read_regs(p, &r);
	if (error == 0) {
D 4
		r.r_sr |= PSL_T;
E 4
I 4
		if (sstep)
			r.r_sr |= PSL_T;
		else
			r.r_sr |= PSL_T;
E 4
		error = procfs_write_regs(p, &r);
	}

	return (error);
}

void
procfs_fix_sstep(p)
	struct proc *p;
{
}
E 1
