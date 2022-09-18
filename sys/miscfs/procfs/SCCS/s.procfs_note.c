h31215
s 00002/00002/00045
d D 8.2 94/01/21 20:00:11 bostic 2 1
c copyright typo
e
s 00047/00000/00000
d D 8.1 94/01/05 12:34:10 pendry 1 0
c date and time created 94/01/05 12:34:10 by pendry
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
 * Copyright (c) 1993 Jan-Simon Pendry
D 2
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	$Id: procfs_note.c,v 3.2 1993/12/15 09:40:17 jsp Exp $
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/signal.h>
#include <miscfs/procfs/procfs.h>

int
procfs_donote(curp, p, pfs, uio)
	struct proc *curp;
	struct proc *p;
	struct pfsnode *pfs;
	struct uio *uio;
{
	int xlen;
	int error;
	char note[PROCFS_NOTELEN+1];

	if (uio->uio_rw != UIO_WRITE)
		return (EINVAL);

	xlen = PROCFS_NOTELEN;
	error = vfs_getuserstr(uio, note, &xlen);
	if (error)
		return (error);

	/* send to process's notify function */
	return (EOPNOTSUPP);
}
E 1
