h50005
s 00006/00004/00897
d D 8.18 95/05/21 19:50:59 mckusick 20 19
c inactive routine must unlock node
e
s 00003/00002/00898
d D 8.17 95/05/14 00:44:01 mckusick 19 18
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00002/00898
d D 8.16 95/05/10 11:22:11 pendry 18 17
c VOP_REVOKE(vp, 0) should really be vgone(vp)
e
s 00053/00057/00847
d D 8.15 95/05/10 10:26:34 mckusick 17 16
c lookup error return cleanups (from mycroft)
e
s 00001/00000/00903
d D 8.14 95/04/03 23:17:44 mckusick 16 15
c add revoke operator
e
s 00002/00002/00901
d D 8.13 95/02/23 12:23:06 mckusick 15 12
c vgone => VOP_REVOKE
e
s 00002/00002/00901
d R 8.13 95/02/22 19:27:53 mckusick 14 12
c vgone => VOP_REVOKE
e
s 00002/00002/00901
d R 8.13 95/02/22 19:16:45 mckusick 13 12
c vgone => VOP_REVOKE
e
s 00003/00002/00900
d D 8.12 95/02/06 04:34:27 pendry 12 11
c fix cpy date & bmap args structure
e
s 00002/00000/00900
d D 8.11 95/02/06 04:31:54 pendry 11 10
c ensure bmap run list is initialised
e
s 00003/00004/00897
d D 8.10 95/01/09 18:24:39 cgd 10 9
c microtime takes a timeval ptr.
e
s 00004/00004/00897
d D 8.9 94/08/20 16:54:43 mckusick 9 8
c use new queue.h data structures
e
s 00160/00111/00741
d D 8.8 94/06/15 12:30:50 pendry 8 7
c merge in netbsd changes.
c security fixes, curproc becomes symlink, misc other trash.
e
s 00077/00013/00775
d D 8.7 94/06/04 19:47:22 mckusick 7 6
c add cookie and eofflag parameters to readdir
e
s 00026/00003/00762
d D 8.6 94/02/07 11:18:56 pendry 6 5
c minor security change for setuid processes
e
s 00009/00007/00756
d D 8.5 94/01/27 11:30:47 pendry 5 4
c add fpregs entry point
e
s 00002/00002/00761
d D 8.4 94/01/21 19:59:11 bostic 4 3
c copyright typo
e
s 00036/00002/00727
d D 8.3 94/01/14 08:29:26 pendry 3 2
c add pathconf entry point
e
s 00024/00024/00705
d D 8.2 94/01/06 00:06:39 pendry 2 1
c cleanup
e
s 00729/00000/00000
d D 8.1 94/01/05 12:34:12 pendry 1 0
c date and time created 94/01/05 12:34:12 by pendry
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
D 12
 * Copyright (c) 1993 Jan-Simon Pendry
D 4
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1993
E 12
I 12
 * Copyright (c) 1993, 1995 Jan-Simon Pendry
 * Copyright (c) 1993, 1995
E 12
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * From:
 *	$Id: procfs_vnops.c,v 3.2 1993/12/15 09:40:17 jsp Exp $
 */

/*
 * procfs vnode interface
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/namei.h>
#include <sys/malloc.h>
#include <sys/dirent.h>
#include <sys/resourcevar.h>
D 8
#include <miscfs/procfs/procfs.h>
E 8
#include <vm/vm.h>	/* for PAGE_SIZE */
I 8
#include <machine/reg.h>
#include <miscfs/procfs/procfs.h>
E 8

/*
 * Vnode Operations.
 *
 */

/*
 * This is a list of the valid names in the
 * process-specific sub-directories.  It is
 * used in procfs_lookup and procfs_readdir
 */
D 17
static struct pfsnames {
D 8
	u_short	d_namlen;
E 8
I 8
	u_char	d_type;
	u_char	d_namlen;
E 8
	char	d_name[PROCFS_NAMELEN];
	pfstype	d_pfstype;
I 8
	int	(*d_valid) __P((struct proc *p));
E 8
} procent[] = {
E 17
I 17
struct proc_target {
	u_char	pt_type;
	u_char	pt_namlen;
	char	*pt_name;
	pfstype	pt_pfstype;
	int	(*pt_valid) __P((struct proc *p));
} proc_targets[] = {
E 17
#define N(s) sizeof(s)-1, s
D 17
	/* namlen, nam, type */
E 17
I 17
	/*	  name		type		validp */
E 17
D 5
	{  N("file"),   Pfile },
	{  N("mem"),    Pmem },
	{  N("regs"),   Pregs },
	{  N("ctl"),    Pctl },
	{  N("status"), Pstatus },
	{  N("note"),   Pnote },
	{  N("notepg"), Pnotepg },
E 5
I 5
D 8
	{  N("file"),	Pfile },
	{  N("mem"),	Pmem },
	{  N("regs"),	Pregs },
	{  N("fpregs"),	Pfpregs },
	{  N("ctl"),	Pctl },
	{  N("status"),	Pstatus },
	{  N("note"),	Pnote },
	{  N("notepg"),	Pnotepg },
E 8
I 8
	{ DT_DIR, N("."),	Pproc,		NULL },
	{ DT_DIR, N(".."),	Proot,		NULL },
	{ DT_REG, N("file"),	Pfile,		procfs_validfile },
	{ DT_REG, N("mem"),	Pmem,		NULL },
	{ DT_REG, N("regs"),	Pregs,		procfs_validregs },
	{ DT_REG, N("fpregs"),	Pfpregs,	procfs_validfpregs },
	{ DT_REG, N("ctl"),	Pctl,		NULL },
	{ DT_REG, N("status"),	Pstatus,	NULL },
	{ DT_REG, N("note"),	Pnote,		NULL },
	{ DT_REG, N("notepg"),	Pnotepg,	NULL },
E 8
E 5
#undef N
};
D 17
#define Nprocent (sizeof(procent)/sizeof(procent[0]))
E 17
I 17
static int nproc_targets = sizeof(proc_targets) / sizeof(proc_targets[0]);
E 17

static pid_t atopid __P((const char *, u_int));

/*
 * set things up for doing i/o on
 * the pfsnode (vp).  (vp) is locked
 * on entry, and should be left locked
 * on exit.
 *
 * for procfs we don't need to do anything
 * in particular for i/o.  all that is done
 * is to support exclusive open on process
 * memory images.
 */
procfs_open(ap)
D 7
	struct vop_open_args *ap;
E 7
I 7
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 7
{
	struct pfsnode *pfs = VTOPFS(ap->a_vp);

	switch (pfs->pfs_type) {
	case Pmem:
		if (PFIND(pfs->pfs_pid) == 0)
			return (ENOENT);	/* was ESRCH, jsp */

		if ((pfs->pfs_flags & FWRITE) && (ap->a_mode & O_EXCL) ||
D 8
				(pfs->pfs_flags & O_EXCL) && (ap->a_mode & FWRITE))
E 8
I 8
		    (pfs->pfs_flags & O_EXCL) && (ap->a_mode & FWRITE))
E 8
			return (EBUSY);

D 8

E 8
		if (ap->a_mode & FWRITE)
			pfs->pfs_flags = ap->a_mode & (FWRITE|O_EXCL);

		return (0);

	default:
		break;
	}

	return (0);
}

/*
 * close the pfsnode (vp) after doing i/o.
 * (vp) is not locked on entry or exit.
 *
 * nothing to do for procfs other than undo
 * any exclusive open flag (see _open above).
 */
procfs_close(ap)
D 7
	struct vop_close_args *ap;
E 7
I 7
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 7
{
	struct pfsnode *pfs = VTOPFS(ap->a_vp);

	switch (pfs->pfs_type) {
	case Pmem:
		if ((ap->a_fflag & FWRITE) && (pfs->pfs_flags & O_EXCL))
			pfs->pfs_flags &= ~(FWRITE|O_EXCL);
		break;
	}

	return (0);
}

/*
 * do an ioctl operation on pfsnode (vp).
 * (vp) is not locked on entry or exit.
 */
procfs_ioctl(ap)
D 7
	struct vop_ioctl_args *ap;
E 7
I 7
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
		int a_command;
		caddr_t a_data;
		int a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 7
{

	return (ENOTTY);
}

/*
 * do block mapping for pfsnode (vp).
 * since we don't use the buffer cache
 * for procfs this function should never
 * be called.  in any case, it's not clear
 * what part of the kernel ever makes use
 * of this function.  for sanity, this is the
 * usual no-op bmap, although returning
 * (EIO) would be a reasonable alternative.
 */
procfs_bmap(ap)
D 7
	struct vop_bmap_args *ap;
E 7
I 7
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
I 12
		int *a_runp;
E 12
	} */ *ap;
E 7
{

	if (ap->a_vpp != NULL)
		*ap->a_vpp = ap->a_vp;
	if (ap->a_bnp != NULL)
		*ap->a_bnp = ap->a_bn;
I 11
	if (ap->a_runp != NULL)
		*ap->a_runp = 0;
E 11
	return (0);
}

/*
D 20
 * _inactive is called when the pfsnode
E 20
I 20
 * procfs_inactive is called when the pfsnode
E 20
 * is vrele'd and the reference count goes
 * to zero.  (vp) will be on the vnode free
 * list, so to get it back vget() must be
 * used.
 *
 * for procfs, check if the process is still
 * alive and if it isn't then just throw away
D 15
 * the vnode by calling vgone().  this may
E 15
I 15
D 18
 * the vnode by calling VOP_REVOKE().  this may
E 18
I 18
 * the vnode by calling vgone().  this may
E 18
E 15
 * be overkill and a waste of time since the
 * chances are that the process will still be
 * there and PFIND is not free.
 *
D 20
 * (vp) is not locked on entry or exit.
E 20
I 20
 * (vp) is locked on entry, but must be unlocked on exit.
E 20
 */
procfs_inactive(ap)
D 7
	struct vop_inactive_args *ap;
E 7
I 7
	struct vop_inactive_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 7
{
D 20
	struct pfsnode *pfs = VTOPFS(ap->a_vp);
E 20
I 20
	struct vnode *vp = ap->a_vp;
	struct pfsnode *pfs = VTOPFS(vp);
E 20

I 20
	VOP_UNLOCK(vp, 0, ap->a_p);
E 20
	if (PFIND(pfs->pfs_pid) == 0)
D 15
		vgone(ap->a_vp);
E 15
I 15
D 17
		VOP_REVOKE(ap->a_vp, 0);
E 17
I 17
D 18
		VOP_REVOKE(ap->a_vp);
E 18
I 18
D 20
		vgone(ap->a_vp);
E 20
I 20
		vgone(vp);
E 20
E 18
E 17
E 15

	return (0);
}

/*
 * _reclaim is called when getnewvnode()
 * wants to make use of an entry on the vnode
 * free list.  at this time the filesystem needs
 * to free any private data and remove the node
 * from any private lists.
 */
procfs_reclaim(ap)
D 7
	struct vop_reclaim_args *ap;
E 7
I 7
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 7
{
D 8
	int error;
E 8

D 8
	error = procfs_freevp(ap->a_vp);
	return (error);
E 8
I 8
	return (procfs_freevp(ap->a_vp));
E 8
}

/*
I 3
 * Return POSIX pathconf information applicable to special devices.
 */
procfs_pathconf(ap)
	struct vop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		int *a_retval;
	} */ *ap;
{

	switch (ap->a_name) {
	case _PC_LINK_MAX:
		*ap->a_retval = LINK_MAX;
		return (0);
	case _PC_MAX_CANON:
		*ap->a_retval = MAX_CANON;
		return (0);
	case _PC_MAX_INPUT:
		*ap->a_retval = MAX_INPUT;
		return (0);
	case _PC_PIPE_BUF:
		*ap->a_retval = PIPE_BUF;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		return (0);
	case _PC_VDISABLE:
		*ap->a_retval = _POSIX_VDISABLE;
		return (0);
	default:
		return (EINVAL);
	}
	/* NOTREACHED */
}

/*
E 3
 * _print is used for debugging.
 * just print a readable description
 * of (vp).
 */
procfs_print(ap)
D 7
	struct vop_print_args *ap;
E 7
I 7
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 7
{
	struct pfsnode *pfs = VTOPFS(ap->a_vp);

D 8
	printf("tag VT_PROCFS, pid %d, mode %x, flags %x\n",
		pfs->pfs_pid,
		pfs->pfs_mode, pfs->pfs_flags);
E 8
I 8
	printf("tag VT_PROCFS, type %s, pid %d, mode %x, flags %x\n",
	    pfs->pfs_type, pfs->pfs_pid, pfs->pfs_mode, pfs->pfs_flags);
E 8
}

/*
 * _abortop is called when operations such as
 * rename and create fail.  this entry is responsible
 * for undoing any side-effects caused by the lookup.
 * this will always include freeing the pathname buffer.
 */
procfs_abortop(ap)
D 7
	struct vop_abortop_args *ap;
E 7
I 7
	struct vop_abortop_args /* {
		struct vnode *a_dvp;
		struct componentname *a_cnp;
	} */ *ap;
E 7
{

	if ((ap->a_cnp->cn_flags & (HASBUF | SAVESTART)) == HASBUF)
		FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
	return (0);
}

/*
 * generic entry point for unsupported operations
 */
procfs_badop()
{

	return (EIO);
}

/*
 * Invent attributes for pfsnode (vp) and store
 * them in (vap).
 * Directories lengths are returned as zero since
 * any real length would require the genuine size
 * to be computed, and nothing cares anyway.
 *
 * this is relatively minimal for procfs.
 */
procfs_getattr(ap)
D 7
	struct vop_getattr_args *ap;
E 7
I 7
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 7
{
	struct pfsnode *pfs = VTOPFS(ap->a_vp);
I 2
	struct vattr *vap = ap->a_vap;
E 2
	struct proc *procp;
I 10
	struct timeval tv;
E 10
	int error;

	/* first check the process still exists */
D 6
	procp = PFIND(pfs->pfs_pid);
	if (procp == 0)
		return (ENOENT);
E 6
I 6
	switch (pfs->pfs_type) {
	case Proot:
I 8
	case Pcurproc:
E 8
		procp = 0;
		break;
E 6

I 6
	default:
		procp = PFIND(pfs->pfs_pid);
		if (procp == 0)
			return (ENOENT);
	}

E 6
	error = 0;

	/* start by zeroing out the attributes */
D 2
	VATTR_NULL(ap->a_vap);
E 2
I 2
	VATTR_NULL(vap);
E 2

	/* next do all the common fields */
D 2
	(ap->a_vap)->va_type = ap->a_vp->v_type;
	(ap->a_vap)->va_mode = pfs->pfs_mode;
	(ap->a_vap)->va_fileid = pfs->pfs_fileno;
	(ap->a_vap)->va_flags = 0;
	(ap->a_vap)->va_blocksize = PAGE_SIZE;
	(ap->a_vap)->va_bytes = ap->a_vap->va_size = 0;
E 2
I 2
	vap->va_type = ap->a_vp->v_type;
	vap->va_mode = pfs->pfs_mode;
	vap->va_fileid = pfs->pfs_fileno;
	vap->va_flags = 0;
	vap->va_blocksize = PAGE_SIZE;
	vap->va_bytes = vap->va_size = 0;
I 6

	/*
I 8
	 * Make all times be current TOD.
	 * It would be possible to get the process start
	 * time from the p_stat structure, but there's
	 * no "file creation" time stamp anyway, and the
	 * p_stat structure is not addressible if u. gets
	 * swapped out for that process.
D 10
	 *
	 * XXX
	 * Note that microtime() returns a timeval, not a timespec.
E 10
	 */
D 10
	microtime(&vap->va_ctime);
E 10
I 10
	microtime(&tv);
	TIMEVAL_TO_TIMESPEC(&tv, &vap->va_ctime);
E 10
	vap->va_atime = vap->va_mtime = vap->va_ctime;

	/*
E 8
	 * If the process has exercised some setuid or setgid
	 * privilege, then rip away read/write permission so
	 * that only root can gain access.
	 */
	switch (pfs->pfs_type) {
I 8
	case Pmem:
E 8
	case Pregs:
	case Pfpregs:
D 8
	case Pmem:
E 8
		if (procp->p_flag & P_SUGID)
			vap->va_mode &= ~((VREAD|VWRITE)|
					  ((VREAD|VWRITE)>>3)|
					  ((VREAD|VWRITE)>>6));
I 8
	case Pctl:
	case Pstatus:
	case Pnote:
	case Pnotepg:
		vap->va_nlink = 1;
		vap->va_uid = procp->p_ucred->cr_uid;
		vap->va_gid = procp->p_ucred->cr_gid;
E 8
		break;
	}
E 6
E 2

	/*
D 8
	 * Make all times be current TOD.
	 * It would be possible to get the process start
	 * time from the p_stat structure, but there's
	 * no "file creation" time stamp anyway, and the
	 * p_stat structure is not addressible if u. gets
	 * swapped out for that process.
	 */
D 2
	microtime(&(ap->a_vap)->va_ctime);
	(ap->a_vap)->va_atime = ap->a_vap->va_mtime = ap->a_vap->va_ctime;
E 2
I 2
	microtime(&vap->va_ctime);
	vap->va_atime = vap->va_mtime = vap->va_ctime;
E 2

	/*
E 8
	 * now do the object specific fields
	 *
	 * The size could be set from struct reg, but it's hardly
	 * worth the trouble, and it puts some (potentially) machine
	 * dependent data into this machine-independent code.  If it
	 * becomes important then this function should break out into
	 * a per-file stat function in the corresponding .c file.
	 */

	switch (pfs->pfs_type) {
	case Proot:
D 2
		ap->a_vap->va_nlink = 2;
		ap->a_vap->va_uid = 0;
		ap->a_vap->va_gid = 0;
E 2
I 2
D 8
		vap->va_nlink = 2;
E 8
I 8
		/*
		 * Set nlink to 1 to tell fts(3) we don't actually know.
		 */
		vap->va_nlink = 1;
E 8
		vap->va_uid = 0;
		vap->va_gid = 0;
I 8
		vap->va_size = vap->va_bytes = DEV_BSIZE;
E 8
E 2
		break;

I 8
	case Pcurproc: {
		char buf[16];		/* should be enough */
		vap->va_nlink = 1;
		vap->va_uid = 0;
		vap->va_gid = 0;
		vap->va_size = vap->va_bytes =
		    sprintf(buf, "%ld", (long)curproc->p_pid);
		break;
	}

E 8
	case Pproc:
D 2
		ap->a_vap->va_nlink = 2;
		ap->a_vap->va_uid = procp->p_ucred->cr_uid;
		ap->a_vap->va_gid = procp->p_ucred->cr_gid;
E 2
I 2
		vap->va_nlink = 2;
		vap->va_uid = procp->p_ucred->cr_uid;
		vap->va_gid = procp->p_ucred->cr_gid;
I 8
		vap->va_size = vap->va_bytes = DEV_BSIZE;
E 8
E 2
		break;

	case Pfile:
		error = EOPNOTSUPP;
		break;

	case Pmem:
D 2
		ap->a_vap->va_nlink = 1;
		ap->a_vap->va_bytes = ap->a_vap->va_size =
E 2
I 2
D 8
		vap->va_nlink = 1;
E 8
		vap->va_bytes = vap->va_size =
E 2
			ctob(procp->p_vmspace->vm_tsize +
				    procp->p_vmspace->vm_dsize +
				    procp->p_vmspace->vm_ssize);
D 2
		ap->a_vap->va_uid = procp->p_ucred->cr_uid;
		ap->a_vap->va_gid = procp->p_ucred->cr_gid;
E 2
I 2
D 8
		vap->va_uid = procp->p_ucred->cr_uid;
		vap->va_gid = procp->p_ucred->cr_gid;
E 8
E 2
		break;

	case Pregs:
I 8
		vap->va_bytes = vap->va_size = sizeof(struct reg);
		break;

E 8
I 5
	case Pfpregs:
I 8
		vap->va_bytes = vap->va_size = sizeof(struct fpreg);
		break;

E 8
E 5
	case Pctl:
	case Pstatus:
	case Pnote:
	case Pnotepg:
D 2
		ap->a_vap->va_nlink = 1;
		ap->a_vap->va_uid = procp->p_ucred->cr_uid;
		ap->a_vap->va_gid = procp->p_ucred->cr_gid;
E 2
I 2
D 8
		vap->va_nlink = 1;
		vap->va_uid = procp->p_ucred->cr_uid;
		vap->va_gid = procp->p_ucred->cr_gid;
E 8
E 2
		break;

	default:
		panic("procfs_getattr");
	}

	return (error);
}

procfs_setattr(ap)
D 7
	struct vop_setattr_args *ap;
E 7
I 7
	struct vop_setattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 7
{
	/*
	 * just fake out attribute setting
	 * it's not good to generate an error
	 * return, otherwise things like creat()
	 * will fail when they try to set the
	 * file length to 0.  worse, this means
	 * that echo $note > /proc/$pid/note will fail.
	 */

	return (0);
}

/*
 * implement access checking.
 *
 * something very similar to this code is duplicated
 * throughout the 4bsd kernel and should be moved
 * into kern/vfs_subr.c sometime.
 *
 * actually, the check for super-user is slightly
 * broken since it will allow read access to write-only
 * objects.  this doesn't cause any particular trouble
 * but does mean that the i/o entry points need to check
 * that the operation really does make sense.
 */
procfs_access(ap)
D 7
	struct vop_access_args *ap;
E 7
I 7
	struct vop_access_args /* {
		struct vnode *a_vp;
		int a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 7
{
	struct vattr *vap;
	struct vattr vattr;
	int error;

	/*
	 * If you're the super-user,
	 * you always get access.
	 */
D 8
	if (ap->a_cred->cr_uid == (uid_t) 0)
E 8
I 8
	if (ap->a_cred->cr_uid == 0)
E 8
		return (0);
I 8

E 8
	vap = &vattr;
	if (error = VOP_GETATTR(ap->a_vp, vap, ap->a_cred, ap->a_p))
		return (error);

	/*
	 * Access check is based on only one of owner, group, public.
	 * If not owner, then check group. If not a member of the
	 * group, then check public access.
	 */
	if (ap->a_cred->cr_uid != vap->va_uid) {
		gid_t *gp;
		int i;

D 8
		(ap->a_mode) >>= 3;
E 8
I 8
		ap->a_mode >>= 3;
E 8
		gp = ap->a_cred->cr_groups;
		for (i = 0; i < ap->a_cred->cr_ngroups; i++, gp++)
			if (vap->va_gid == *gp)
				goto found;
		ap->a_mode >>= 3;
found:
		;
	}

	if ((vap->va_mode & ap->a_mode) == ap->a_mode)
		return (0);

	return (EACCES);
}

/*
 * lookup.  this is incredibly complicated in the
 * general case, however for most pseudo-filesystems
 * very little needs to be done.
 *
 * unless you want to get a migraine, just make sure your
 * filesystem doesn't do any locking of its own.  otherwise
 * read and inwardly digest ufs_lookup().
 */
procfs_lookup(ap)
D 7
	struct vop_lookup_args *ap;
E 7
I 7
	struct vop_lookup_args /* {
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
	} */ *ap;
E 7
{
	struct componentname *cnp = ap->a_cnp;
	struct vnode **vpp = ap->a_vpp;
	struct vnode *dvp = ap->a_dvp;
	char *pname = cnp->cn_nameptr;
I 19
	struct proc *curp = cnp->cn_proc;
E 19
	int error = 0;
I 17
	struct proc_target *pt;
	struct vnode *fvp;
E 17
D 3
	int flag;
E 3
	pid_t pid;
D 17
	struct vnode *nvp;
E 17
	struct pfsnode *pfs;
D 17
	struct proc *procp;
D 3
	int mode;
E 3
	pfstype pfs_type;
E 17
I 17
	struct proc *p;
E 17
	int i;

I 17
	*vpp = NULL;

	if (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME)
		return (EROFS);

E 17
	if (cnp->cn_namelen == 1 && *pname == '.') {
		*vpp = dvp;
		VREF(dvp);
D 19
		/*VOP_LOCK(dvp);*/
E 19
I 19
		/* vn_lock(dvp, LK_EXCLUSIVE | LK_RETRY, curp); */
E 19
		return (0);
	}

D 17
	*vpp = NULL;

E 17
	pfs = VTOPFS(dvp);
	switch (pfs->pfs_type) {
	case Proot:
		if (cnp->cn_flags & ISDOTDOT)
			return (EIO);

		if (CNEQ(cnp, "curproc", 7))
D 8
			pid = cnp->cn_proc->p_pid;
		else
			pid = atopid(pname, cnp->cn_namelen);
E 8
I 8
			return (procfs_allocvp(dvp->v_mount, vpp, 0, Pcurproc));

		pid = atopid(pname, cnp->cn_namelen);
E 8
		if (pid == NO_PID)
D 17
			return (ENOENT);
E 17
I 17
			break;
E 17

D 17
		procp = PFIND(pid);
		if (procp == 0)
			return (ENOENT);
E 17
I 17
		p = PFIND(pid);
		if (p == 0)
			break;
E 17

D 8
		error = procfs_allocvp(dvp->v_mount, &nvp, pid, Pproc);
		if (error)
			return (error);
E 8
I 8
		return (procfs_allocvp(dvp->v_mount, vpp, pid, Pproc));
E 8

D 8
		nvp->v_type = VDIR;
		pfs = VTOPFS(nvp);

		*vpp = nvp;
		return (0);

E 8
	case Pproc:
D 17
		if (cnp->cn_flags & ISDOTDOT) {
			error = procfs_root(dvp->v_mount, vpp);
			return (error);
		}
E 17
I 17
		if (cnp->cn_flags & ISDOTDOT)
			return (procfs_root(dvp->v_mount, vpp));
E 17

D 17
		procp = PFIND(pfs->pfs_pid);
		if (procp == 0)
			return (ENOENT);
E 17
I 17
		p = PFIND(pfs->pfs_pid);
		if (p == 0)
			break;
E 17

D 17
		for (i = 0; i < Nprocent; i++) {
			struct pfsnames *dp = &procent[i];

			if (cnp->cn_namelen == dp->d_namlen &&
D 8
			    bcmp(pname, dp->d_name, dp->d_namlen) == 0) {
E 8
I 8
			    bcmp(pname, dp->d_name, dp->d_namlen) == 0 &&
			    (dp->d_valid == NULL || (*dp->d_valid)(procp))) {
E 8
			    	pfs_type = dp->d_pfstype;
E 17
I 17
		for (pt = proc_targets, i = 0; i < nproc_targets; pt++, i++) {
			if (cnp->cn_namelen == pt->pt_namlen &&
			    bcmp(pt->pt_name, pname, cnp->cn_namelen) == 0 &&
			    (pt->pt_valid == NULL || (*pt->pt_valid)(p)))
E 17
				goto found;
D 17
			}
E 17
		}
D 17
		return (ENOENT);
E 17
I 17
		break;
E 17

	found:
D 17
		if (pfs_type == Pfile) {
			nvp = procfs_findtextvp(procp);
D 8
			if (nvp) {
				VREF(nvp);
				VOP_LOCK(nvp);
			} else {
				error = ENXIO;
			}
		} else {
			error = procfs_allocvp(dvp->v_mount, &nvp,
					pfs->pfs_pid, pfs_type);
			if (error)
				return (error);

			nvp->v_type = VREG;
			pfs = VTOPFS(nvp);
E 8
I 8
			if (nvp == NULLVP)
				return (ENXIO);
			VREF(nvp);
			VOP_LOCK(nvp);
			*vpp = nvp;
E 17
I 17
		if (pt->pt_pfstype == Pfile) {
			fvp = procfs_findtextvp(p);
			/* We already checked that it exists. */
			VREF(fvp);
D 19
			VOP_LOCK(fvp);
E 19
I 19
			vn_lock(fvp, LK_EXCLUSIVE | LK_RETRY, curp);
E 19
			*vpp = fvp;
E 17
			return (0);
E 8
		}
D 8
		*vpp = nvp;
		return (error);
E 8

I 8
		return (procfs_allocvp(dvp->v_mount, vpp, pfs->pfs_pid,
D 17
		    pfs_type));
E 17
I 17
		    pt->pt_pfstype));
E 17

E 8
	default:
		return (ENOTDIR);
	}
I 17

	return (cnp->cn_nameiop == LOOKUP ? ENOENT : EROFS);
E 17
}

I 8
int
procfs_validfile(p)
	struct proc *p;
{

	return (procfs_findtextvp(p) != NULLVP);
}

E 8
/*
 * readdir returns directory entries from pfsnode (vp).
 *
 * the strategy here with procfs is to generate a single
 * directory entry at a time (struct pfsdent) and then
 * copy that out to userland using uiomove.  a more efficent
 * though more complex implementation, would try to minimize
 * the number of calls to uiomove().  for procfs, this is
 * hardly worth the added code complexity.
 *
 * this should just be done through read()
 */
procfs_readdir(ap)
D 7
	struct vop_readdir_args *ap;
E 7
I 7
	struct vop_readdir_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
		int *a_eofflag;
		u_long *a_cookies;
		int a_ncookies;
	} */ *ap;
E 7
{
	struct uio *uio = ap->a_uio;
	struct pfsdent d;
	struct pfsdent *dp = &d;
	struct pfsnode *pfs;
	int error;
	int count;
	int i;
I 7

	/*
	 * We don't allow exporting procfs mounts, and currently local
	 * requests do not need cookies.
	 */
	if (ap->a_ncookies)
		panic("procfs_readdir: not hungry");
E 7

	pfs = VTOPFS(ap->a_vp);

	if (uio->uio_resid < UIO_MX)
		return (EINVAL);
	if (uio->uio_offset & (UIO_MX-1))
		return (EINVAL);
	if (uio->uio_offset < 0)
		return (EINVAL);

	error = 0;
	count = 0;
	i = uio->uio_offset / UIO_MX;

	switch (pfs->pfs_type) {
	/*
	 * this is for the process-specific sub-directories.
	 * all that is needed to is copy out all the entries
	 * from the procent[] table (top of this file).
	 */
	case Pproc: {
D 8
		while (uio->uio_resid >= UIO_MX) {
			struct pfsnames *dt;
E 8
I 8
D 17
		pid_t pid = pfs->pfs_pid;
		struct pfsnames *dt;
E 17
I 17
		struct proc *p;
		struct proc_target *pt;
E 17
E 8

D 8
			if (i >= Nprocent)
E 8
I 8
D 17
		for (dt = &procent[i]; i < Nprocent && uio->uio_resid >= UIO_MX;
		     dt++, i++) {
			struct proc *p = PFIND(pid);
E 17
I 17
		p = PFIND(pfs->pfs_pid);
		if (p == NULL)
			break;
E 17

D 17
			if (p == NULL)
E 8
				break;

D 8
			dt = &procent[i];
E 8
I 8
			if (dt->d_valid && (*dt->d_valid)(p) == 0)
E 17
I 17
		for (pt = &proc_targets[i];
		     uio->uio_resid >= UIO_MX && i < nproc_targets; pt++, i++) {
			if (pt->pt_valid && (*pt->pt_valid)(p) == 0)
E 17
				continue;
E 8
			
			dp->d_reclen = UIO_MX;
D 8
			dp->d_fileno = PROCFS_FILENO(pfs->pfs_pid, dt->d_pfstype);
			dp->d_type = DT_REG;
E 8
I 8
D 17
			dp->d_fileno = PROCFS_FILENO(pid, dt->d_pfstype);
E 8
			dp->d_namlen = dt->d_namlen;
D 8
			bcopy(dt->d_name, dp->d_name, sizeof(dt->d_name)-1);
			error = uiomove((caddr_t) dp, UIO_MX, uio);
			if (error)
E 8
I 8
			bcopy(dt->d_name, dp->d_name, dt->d_namlen + 1);
			dp->d_type = dt->d_type;
E 17
I 17
			dp->d_fileno = PROCFS_FILENO(pfs->pfs_pid, pt->pt_pfstype);
			dp->d_namlen = pt->pt_namlen;
			bcopy(pt->pt_name, dp->d_name, pt->pt_namlen + 1);
			dp->d_type = pt->pt_type;
E 17

			if (error = uiomove((caddr_t)dp, UIO_MX, uio))
E 8
				break;
D 8
			count += UIO_MX;
			i++;
E 8
		}

	    	break;
D 17

E 17
	    }

	/*
	 * this is for the root of the procfs filesystem
	 * what is needed is a special entry for "curproc"
	 * followed by an entry for each process on allproc
#ifdef PROCFS_ZOMBIE
	 * and zombproc.
#endif
	 */

	case Proot: {
D 8
		int pcnt;
E 8
#ifdef PROCFS_ZOMBIE
		int doingzomb = 0;
#endif
D 8
		volatile struct proc *p;
E 8
I 8
		int pcnt = 0;
D 9
		volatile struct proc *p = allproc;
E 9
I 9
		volatile struct proc *p = allproc.lh_first;
E 9
E 8

D 8
		p = allproc;

#define PROCFS_XFILES	1	/* number of other entries, like "curproc" */
		pcnt = PROCFS_XFILES;

		while (p && uio->uio_resid >= UIO_MX) {
E 8
I 8
	again:
		for (; p && uio->uio_resid >= UIO_MX; i++, pcnt++) {
E 8
			bzero((char *) dp, UIO_MX);
D 8
			dp->d_type = DT_DIR;
E 8
			dp->d_reclen = UIO_MX;

			switch (i) {
D 8
			case 0:
				/* ship out entry for "curproc" */
				dp->d_fileno = PROCFS_FILENO(PID_MAX+1, Pproc);
D 2
				dp->d_namlen = 7;
				bcopy("curproc", dp->d_name, dp->d_namlen+1);
E 2
I 2
				dp->d_namlen = sprintf(dp->d_name, "curproc");
E 8
I 8
			case 0:		/* `.' */
			case 1:		/* `..' */
				dp->d_fileno = PROCFS_FILENO(0, Proot);
				dp->d_namlen = i + 1;
				bcopy("..", dp->d_name, dp->d_namlen);
				dp->d_name[i + 1] = '\0';
				dp->d_type = DT_DIR;
E 8
E 2
				break;

I 8
			case 2:
				dp->d_fileno = PROCFS_FILENO(0, Pcurproc);
				dp->d_namlen = 7;
				bcopy("curproc", dp->d_name, 8);
				dp->d_type = DT_LNK;
				break;

E 8
			default:
D 8
				if (pcnt >= i) {
					dp->d_fileno = PROCFS_FILENO(p->p_pid, Pproc);
					dp->d_namlen = sprintf(dp->d_name, "%ld", (long) p->p_pid);
E 8
I 8
				while (pcnt < i) {
					pcnt++;
D 9
					p = p->p_next;
E 9
I 9
					p = p->p_list.le_next;
E 9
					if (!p)
						goto done;
E 8
				}
D 8

E 8
I 8
				dp->d_fileno = PROCFS_FILENO(p->p_pid, Pproc);
				dp->d_namlen = sprintf(dp->d_name, "%ld",
				    (long)p->p_pid);
				dp->d_type = DT_REG;
E 8
D 9
				p = p->p_next;
E 9
I 9
				p = p->p_list.le_next;
E 9
D 8

#ifdef PROCFS_ZOMBIE
				if (p == 0 && doingzomb == 0) {
					doingzomb = 1;
					p = zombproc;
				}
#endif

				if (pcnt++ < i)
					continue;

E 8
				break;
			}
D 8
			error = uiomove((caddr_t) dp, UIO_MX, uio);
			if (error)
E 8
I 8

			if (error = uiomove((caddr_t)dp, UIO_MX, uio))
E 8
				break;
D 8
			count += UIO_MX;
			i++;
E 8
		}
I 8
	done:
E 8

I 8
#ifdef PROCFS_ZOMBIE
		if (p == 0 && doingzomb == 0) {
			doingzomb = 1;
D 9
			p = zombproc;
E 9
I 9
			p = zombproc.lh_first;
E 9
			goto again;
		}
#endif

E 8
		break;

	    }

	default:
		error = ENOTDIR;
		break;
	}

	uio->uio_offset = i * UIO_MX;

	return (error);
I 8
}

/*
 * readlink reads the link of `curproc'
 */
procfs_readlink(ap)
	struct vop_readlink_args *ap;
{
	struct uio *uio = ap->a_uio;
	char buf[16];		/* should be enough */
	int len;

	if (VTOPFS(ap->a_vp)->pfs_fileno != PROCFS_FILENO(0, Pcurproc))
		return (EINVAL);

	len = sprintf(buf, "%ld", (long)curproc->p_pid);

	return (uiomove((caddr_t)buf, len, ap->a_uio));
E 8
}

/*
 * convert decimal ascii to pid_t
 */
static pid_t
atopid(b, len)
	const char *b;
	u_int len;
{
	pid_t p = 0;

	while (len--) {
		char c = *b++;
		if (c < '0' || c > '9')
			return (NO_PID);
		p = 10 * p + (c - '0');
		if (p > PID_MAX)
			return (NO_PID);
	}

	return (p);
}

/*
 * procfs vnode operations.
 */
int (**procfs_vnodeop_p)();
struct vnodeopv_entry_desc procfs_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, procfs_lookup },		/* lookup */
	{ &vop_create_desc, procfs_create },		/* create */
	{ &vop_mknod_desc, procfs_mknod },		/* mknod */
	{ &vop_open_desc, procfs_open },		/* open */
	{ &vop_close_desc, procfs_close },		/* close */
	{ &vop_access_desc, procfs_access },		/* access */
	{ &vop_getattr_desc, procfs_getattr },		/* getattr */
	{ &vop_setattr_desc, procfs_setattr },		/* setattr */
	{ &vop_read_desc, procfs_read },		/* read */
	{ &vop_write_desc, procfs_write },		/* write */
	{ &vop_ioctl_desc, procfs_ioctl },		/* ioctl */
	{ &vop_select_desc, procfs_select },		/* select */
	{ &vop_mmap_desc, procfs_mmap },		/* mmap */
I 16
	{ &vop_revoke_desc, procfs_revoke },		/* revoke */
E 16
	{ &vop_fsync_desc, procfs_fsync },		/* fsync */
	{ &vop_seek_desc, procfs_seek },		/* seek */
	{ &vop_remove_desc, procfs_remove },		/* remove */
	{ &vop_link_desc, procfs_link },		/* link */
	{ &vop_rename_desc, procfs_rename },		/* rename */
	{ &vop_mkdir_desc, procfs_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, procfs_rmdir },		/* rmdir */
	{ &vop_symlink_desc, procfs_symlink },		/* symlink */
	{ &vop_readdir_desc, procfs_readdir },		/* readdir */
	{ &vop_readlink_desc, procfs_readlink },	/* readlink */
	{ &vop_abortop_desc, procfs_abortop },		/* abortop */
	{ &vop_inactive_desc, procfs_inactive },	/* inactive */
	{ &vop_reclaim_desc, procfs_reclaim },		/* reclaim */
	{ &vop_lock_desc, procfs_lock },		/* lock */
	{ &vop_unlock_desc, procfs_unlock },		/* unlock */
	{ &vop_bmap_desc, procfs_bmap },		/* bmap */
	{ &vop_strategy_desc, procfs_strategy },	/* strategy */
	{ &vop_print_desc, procfs_print },		/* print */
	{ &vop_islocked_desc, procfs_islocked },	/* islocked */
	{ &vop_pathconf_desc, procfs_pathconf },	/* pathconf */
	{ &vop_advlock_desc, procfs_advlock },		/* advlock */
	{ &vop_blkatoff_desc, procfs_blkatoff },	/* blkatoff */
	{ &vop_valloc_desc, procfs_valloc },		/* valloc */
	{ &vop_vfree_desc, procfs_vfree },		/* vfree */
	{ &vop_truncate_desc, procfs_truncate },	/* truncate */
	{ &vop_update_desc, procfs_update },		/* update */
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
struct vnodeopv_desc procfs_vnodeop_opv_desc =
	{ &procfs_vnodeop_p, procfs_vnodeop_entries };
E 1
