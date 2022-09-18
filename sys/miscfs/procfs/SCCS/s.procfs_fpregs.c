h52570
s 00008/00000/00061
d D 8.2 94/06/15 12:30:54 pendry 2 1
c merge in netbsd changes.
c security fixes, curproc becomes symlink, misc other trash.
e
s 00061/00000/00000
d D 8.1 94/01/27 11:30:30 pendry 1 0
c date and time created 94/01/27 11:30:30 by pendry
e
u
U
t
T
I 1
/*
 * Copyright (c) 1993 Jan-Simon Pendry
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * From:
 *	$Id: procfs_regs.c,v 3.2 1993/12/15 09:40:17 jsp Exp $
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <machine/reg.h>
#include <miscfs/procfs/procfs.h>

int
procfs_dofpregs(curp, p, pfs, uio)
	struct proc *curp;
	struct proc *p;
	struct pfsnode *pfs;
	struct uio *uio;
{
	int error;
	struct fpreg r;
	char *kv;
	int kl;

	kl = sizeof(r);
	kv = (char *) &r;

	kv += uio->uio_offset;
	kl -= uio->uio_offset;
	if (kl > uio->uio_resid)
		kl = uio->uio_resid;

	if (kl < 0)
		error = EINVAL;
	else
		error = procfs_read_fpregs(p, &r);
	if (error == 0)
		error = uiomove(kv, kl, uio);
	if (error == 0 && uio->uio_rw == UIO_WRITE) {
		if (p->p_stat != SSTOP)
			error = EBUSY;
		else
			error = procfs_write_fpregs(p, &r);
	}

	uio->uio_offset = 0;
	return (error);
}
I 2

int
procfs_validfpregs(p)
	struct proc *p;
{

	return ((p->p_flag & P_SYSTEM) == 0);
}
E 2
E 1
