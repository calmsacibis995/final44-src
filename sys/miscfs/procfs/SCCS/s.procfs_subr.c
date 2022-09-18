h04395
s 00002/00001/00286
d D 8.6 95/05/14 00:44:01 mckusick 6 5
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00028/00029/00259
d D 8.5 94/06/15 12:30:49 pendry 5 4
c merge in netbsd changes.
c security fixes, curproc becomes symlink, misc other trash.
e
s 00007/00000/00281
d D 8.4 94/01/27 11:30:46 pendry 4 3
c add fpregs entry point
e
s 00002/00002/00279
d D 8.3 94/01/21 19:59:09 bostic 3 2
c copyright typo
e
s 00001/00002/00280
d D 8.2 94/01/05 23:57:59 pendry 2 1
c don't need vget to lock the vnode
e
s 00282/00000/00000
d D 8.1 94/01/05 12:34:11 pendry 1 0
c date and time created 94/01/05 12:34:11 by pendry
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1993 The Regents of the University of California.
E 3
 * Copyright (c) 1993 Jan-Simon Pendry
D 3
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * From:
 *	$Id: procfs_subr.c,v 3.2 1993/12/15 09:40:17 jsp Exp $
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/malloc.h>
#include <miscfs/procfs/procfs.h>

static struct pfsnode *pfshead;
static int pfsvplock;

/*
 * allocate a pfsnode/vnode pair.  the vnode is
 * referenced, but not locked.
 *
 * the pid, pfs_type, and mount point uniquely
 * identify a pfsnode.  the mount point is needed
 * because someone might mount this filesystem
 * twice.
 *
 * all pfsnodes are maintained on a singly-linked
 * list.  new nodes are only allocated when they cannot
 * be found on this list.  entries on the list are
 * removed when the vfs reclaim entry is called.
 *
 * a single lock is kept for the entire list.  this is
 * needed because the getnewvnode() function can block
 * waiting for a vnode to become free, in which case there
 * may be more than one process trying to get the same
 * vnode.  this lock is only taken if we are going to
 * call getnewvnode, since the kernel itself is single-threaded.
 *
 * if an entry is found on the list, then call vget() to
 * take a reference.  this is done because there may be
 * zero references to it and so it needs to removed from
 * the vnode free list.
 */
int
procfs_allocvp(mp, vpp, pid, pfs_type)
	struct mount *mp;
	struct vnode **vpp;
	long pid;
	pfstype pfs_type;
{
I 6
	struct proc *p = curproc;	/* XXX */
E 6
D 5
	int error;
E 5
	struct pfsnode *pfs;
I 5
	struct vnode *vp;
E 5
	struct pfsnode **pp;
I 5
	int error;
E 5

loop:
	for (pfs = pfshead; pfs != 0; pfs = pfs->pfs_next) {
I 5
		vp = PFSTOV(pfs);
E 5
		if (pfs->pfs_pid == pid &&
		    pfs->pfs_type == pfs_type &&
D 5
		    PFSTOV(pfs)->v_mount == mp) {
D 2
			if (vget(pfs->pfs_vnode, 1))
E 2
I 2
			if (vget(pfs->pfs_vnode, 0))
E 5
I 5
		    vp->v_mount == mp) {
D 6
			if (vget(vp, 0))
E 6
I 6
			if (vget(vp, 0, p))
E 6
E 5
E 2
				goto loop;
D 2
			VOP_UNLOCK(pfs->pfs_vnode);
E 2
D 5
			*vpp = pfs->pfs_vnode;
E 5
I 5
			*vpp = vp;
E 5
			return (0);
		}
	}

	/*
	 * otherwise lock the vp list while we call getnewvnode
	 * since that can block.
	 */ 
	if (pfsvplock & PROCFS_LOCKED) {
		pfsvplock |= PROCFS_WANT;
		sleep((caddr_t) &pfsvplock, PINOD);
		goto loop;
	}
	pfsvplock |= PROCFS_LOCKED;

D 5
	error = getnewvnode(VT_PROCFS, mp, procfs_vnodeop_p, vpp);
	if (error)
E 5
I 5
	if (error = getnewvnode(VT_PROCFS, mp, procfs_vnodeop_p, vpp))
E 5
		goto out;
I 5
	vp = *vpp;
E 5

D 5
	MALLOC((*vpp)->v_data, void *, sizeof(struct pfsnode),
		M_TEMP, M_WAITOK);
E 5
I 5
	MALLOC(pfs, void *, sizeof(struct pfsnode), M_TEMP, M_WAITOK);
	vp->v_data = pfs;
E 5

D 5
	pfs = VTOPFS(*vpp);
E 5
	pfs->pfs_next = 0;
	pfs->pfs_pid = (pid_t) pid;
	pfs->pfs_type = pfs_type;
D 5
	pfs->pfs_vnode = *vpp;
E 5
I 5
	pfs->pfs_vnode = vp;
E 5
	pfs->pfs_flags = 0;
	pfs->pfs_fileno = PROCFS_FILENO(pid, pfs_type);

	switch (pfs_type) {
	case Proot:	/* /proc = dr-xr-xr-x */
		pfs->pfs_mode = (VREAD|VEXEC) |
				(VREAD|VEXEC) >> 3 |
				(VREAD|VEXEC) >> 6;
I 5
		vp->v_type = VDIR;
		vp->v_flag = VROOT;
E 5
		break;

I 5
	case Pcurproc:	/* /proc/curproc = lr--r--r-- */
		pfs->pfs_mode = (VREAD) |
				(VREAD >> 3) |
				(VREAD >> 6);
		vp->v_type = VLNK;
		break;

E 5
	case Pproc:
		pfs->pfs_mode = (VREAD|VEXEC) |
				(VREAD|VEXEC) >> 3 |
				(VREAD|VEXEC) >> 6;
I 5
		vp->v_type = VDIR;
E 5
		break;

	case Pfile:
D 5
		pfs->pfs_mode = (VREAD|VWRITE);
		break;

E 5
	case Pmem:
D 5
		pfs->pfs_mode = (VREAD|VWRITE);
		break;

E 5
	case Pregs:
D 5
		pfs->pfs_mode = (VREAD|VWRITE);
		break;

E 5
I 4
	case Pfpregs:
		pfs->pfs_mode = (VREAD|VWRITE);
I 5
		vp->v_type = VREG;
E 5
		break;

E 4
	case Pctl:
I 5
	case Pnote:
	case Pnotepg:
E 5
		pfs->pfs_mode = (VWRITE);
I 5
		vp->v_type = VREG;
E 5
		break;

	case Pstatus:
		pfs->pfs_mode = (VREAD) |
				(VREAD >> 3) |
				(VREAD >> 6);
I 5
		vp->v_type = VREG;
E 5
		break;

D 5
	case Pnote:
		pfs->pfs_mode = (VWRITE);
		break;

	case Pnotepg:
		pfs->pfs_mode = (VWRITE);
		break;

E 5
	default:
		panic("procfs_allocvp");
	}

	/* add to procfs vnode list */
	for (pp = &pfshead; *pp; pp = &(*pp)->pfs_next)
		continue;
	*pp = pfs;

out:
	pfsvplock &= ~PROCFS_LOCKED;

	if (pfsvplock & PROCFS_WANT) {
		pfsvplock &= ~PROCFS_WANT;
		wakeup((caddr_t) &pfsvplock);
	}

	return (error);
}

int
procfs_freevp(vp)
	struct vnode *vp;
{
	struct pfsnode **pfspp;
	struct pfsnode *pfs = VTOPFS(vp);

	for (pfspp = &pfshead; *pfspp != 0; pfspp = &(*pfspp)->pfs_next) {
		if (*pfspp == pfs) {
			*pfspp = pfs->pfs_next;
			break;
		}
	}

	FREE(vp->v_data, M_TEMP);
	vp->v_data = 0;
	return (0);
}

int
procfs_rw(ap)
	struct vop_read_args *ap;
{
	struct vnode *vp = ap->a_vp;
	struct uio *uio = ap->a_uio;
	struct proc *curp = uio->uio_procp;
	struct pfsnode *pfs = VTOPFS(vp);
	struct proc *p;

	p = PFIND(pfs->pfs_pid);
	if (p == 0)
		return (EINVAL);

	switch (pfs->pfs_type) {
	case Pnote:
	case Pnotepg:
		return (procfs_donote(curp, p, pfs, uio));

	case Pregs:
		return (procfs_doregs(curp, p, pfs, uio));
I 4

	case Pfpregs:
		return (procfs_dofpregs(curp, p, pfs, uio));
E 4

	case Pctl:
		return (procfs_doctl(curp, p, pfs, uio));

	case Pstatus:
		return (procfs_dostatus(curp, p, pfs, uio));

	case Pmem:
		return (procfs_domem(curp, p, pfs, uio));

	default:
		return (EOPNOTSUPP);
	}
}

/*
 * Get a string from userland into (buf).  Strip a trailing
 * nl character (to allow easy access from the shell).
 * The buffer should be *buflenp + 1 chars long.  vfs_getuserstr
 * will automatically add a nul char at the end.
 *
 * Returns 0 on success or the following errors
 *
 * EINVAL:    file offset is non-zero.
 * EMSGSIZE:  message is longer than kernel buffer
 * EFAULT:    user i/o buffer is not addressable
 */
int
vfs_getuserstr(uio, buf, buflenp)
	struct uio *uio;
	char *buf;
	int *buflenp;
{
	int xlen;
	int error;

	if (uio->uio_offset != 0)
		return (EINVAL);

	xlen = *buflenp;

	/* must be able to read the whole string in one go */
	if (xlen < uio->uio_resid)
		return (EMSGSIZE);
	xlen = uio->uio_resid;

D 5
	error = uiomove(buf, xlen, uio);
	if (error)
E 5
I 5
	if (error = uiomove(buf, xlen, uio))
E 5
		return (error);

	/* allow multiple writes without seeks */
	uio->uio_offset = 0;

	/* cleanup string and remove trailing newline */
	buf[xlen] = '\0';
	xlen = strlen(buf);
	if (xlen > 0 && buf[xlen-1] == '\n')
		buf[--xlen] = '\0';
	*buflenp = xlen;

	return (0);
}

vfs_namemap_t *
vfs_findname(nm, buf, buflen)
	vfs_namemap_t *nm;
	char *buf;
	int buflen;
{
I 5

E 5
	for (; nm->nm_name; nm++)
		if (bcmp(buf, (char *) nm->nm_name, buflen+1) == 0)
			return (nm);

	return (0);
}
E 1
