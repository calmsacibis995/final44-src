h45664
s 00004/00004/00523
d D 8.5 95/05/14 00:49:46 mckusick 12 11
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00002/00525
d D 8.4 95/04/03 08:49:37 mckusick 11 10
c MOUNT_* filesystem types are gone
e
s 00001/00001/00526
d D 8.3 94/06/06 18:31:17 mckusick 10 9
c VOP_READIR now has a cookie argument
e
s 00003/00002/00524
d D 8.2 93/09/23 16:46:46 bostic 9 8
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00524
d D 8.1 93/06/18 16:39:38 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00524
d D 7.6 93/06/18 16:39:11 mckusick 7 5
c make function call name match system call name
e
s 00002/00002/00524
d R 8.1 93/06/11 15:19:38 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00104/00506
d D 7.5 93/04/06 19:48:04 torek 5 4
c update from elf: setre[ug]id no longer needed; fix sun readdir
e
s 00019/00019/00591
d D 7.4 92/10/11 12:59:33 bostic 4 3
c make kernel includes standard
e
s 00005/00000/00605
d D 7.3 92/07/21 16:55:44 bostic 3 2
c update the contribution notice; LBL requires acknowledgement
e
s 00002/00001/00603
d D 7.2 92/07/13 17:21:14 torek 2 1
c specdev.h moves
e
s 00604/00000/00000
d D 7.1 92/07/13 00:40:46 torek 1 0
c date and time created 92/07/13 00:40:46 by torek
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 3
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 5
 *	California, Lawrence Berkeley Laboratories.
E 5
I 5
 *	California, Lawrence Berkeley Laboratory.
E 5
 *
E 3
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 5
 * from: $Header: sun_misc.c,v 1.12 92/07/12 13:26:10 torek Exp $
E 5
I 5
 * from: $Header: sun_misc.c,v 1.16 93/04/07 02:46:27 torek Exp $
E 5
 */

/*
 * SunOS compatibility module.
 *
 * SunOS system calls that are implemented differently in BSD are
 * handled here.
 */

D 4
#include "param.h"
#include "proc.h"
#include "file.h"
#include "filedesc.h"
#include "ioctl.h"
#include "malloc.h"
#include "mbuf.h"
#include "mman.h"
#include "mount.h"
#include "resource.h"
#include "resourcevar.h"
#include "signal.h"
#include "signalvar.h"
#include "socket.h"
#include "vnode.h"
D 2
#include "specdev.h"
E 2
#include "uio.h"
#include "wait.h"
E 4
I 4
#include <sys/param.h>
I 5
#include <sys/systm.h>
#include <sys/dirent.h>
E 5
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/filedesc.h>
#include <sys/ioctl.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/resource.h>
#include <sys/resourcevar.h>
#include <sys/signal.h>
#include <sys/signalvar.h>
#include <sys/socket.h>
#include <sys/vnode.h>
#include <sys/uio.h>
#include <sys/wait.h>
E 4
I 2

D 4
#include "miscfs/specfs/specdev.h"
E 4
I 4
#include <miscfs/specfs/specdev.h>
E 4
E 2

D 4
#include "vm/vm.h"
E 4
I 4
#include <vm/vm.h>
E 4

struct sun_wait4_args {
	int	pid;
	int	*status;
	int	options;
	struct	rusage *rusage;
};
sun_wait4(p, uap, retval)
	struct proc *p;
	struct sun_wait4_args *uap;
	int *retval;
{

	if (uap->pid == 0)
		uap->pid = WAIT_ANY;
	return (wait4(p, uap, retval));
}

struct sun_creat_args {
	char	*fname;
	int	fmode;
};
sun_creat(p, uap, retval)
	struct proc *p;
	struct sun_creat_args *uap;
	int *retval;
{
	struct args {
		char	*fname;
		int	mode;
		int	crtmode;
	} openuap;

	openuap.fname = uap->fname;
	openuap.crtmode = uap->fmode;
	openuap.mode = O_WRONLY | O_CREAT | O_TRUNC;
	return (open(p, &openuap, retval));
}

struct sun_execv_args {
	char	*fname;
	char	**argp;
	char	**envp;		/* pseudo */
};
sun_execv(p, uap, retval)
	struct proc *p;
	struct sun_execv_args *uap;
	int *retval;
{

	uap->envp = NULL;
	return (execve(p, uap, retval));
}

struct sun_omsync_args {
	caddr_t	addr;
	int	len;
	int	flags;
};
sun_omsync(p, uap, retval)
	struct proc *p;
	struct sun_omsync_args *uap;
	int *retval;
{

	if (uap->flags)
		return (EINVAL);
	return (msync(p, uap, retval));
}

struct sun_unmount_args {
	char	*name;
	int	flags;	/* pseudo */
};
sun_unmount(p, uap, retval)
	struct proc *p;
	struct sun_unmount_args *uap;
	int *retval;
{

D 5
	uap->flags = MNT_NOFORCE;
E 5
I 5
	uap->flags = 0;
E 5
	return (unmount(p, uap, retval));
}

static int
gettype(tptr)
	int *tptr;
{
	int type, error;
	char in[20];

	if (error = copyinstr((caddr_t)*tptr, in, sizeof in, (u_int *)0))
		return (error);
	if (strcmp(in, "4.2") == 0 || strcmp(in, "ufs") == 0)
D 11
		type = MOUNT_UFS;
E 11
I 11
		type = 1;	/* old MOUNT_UFS */
E 11
	else if (strcmp(in, "nfs") == 0)
D 11
		type = MOUNT_NFS;
E 11
I 11
		type = 2;	/* old MOUNT_NFS */
E 11
	else
		return (EINVAL);
	*tptr = type;
	return (0);
}

#define	SUNM_RDONLY	0x01	/* mount fs read-only */
#define	SUNM_NOSUID	0x02	/* mount fs with setuid disallowed */
#define	SUNM_NEWTYPE	0x04	/* type is string (char *), not int */
#define	SUNM_GRPID	0x08	/* (bsd semantics; ignored) */
#define	SUNM_REMOUNT	0x10	/* update existing mount */
#define	SUNM_NOSUB	0x20	/* prevent submounts (rejected) */
#define	SUNM_MULTI	0x40	/* (ignored) */
#define	SUNM_SYS5	0x80	/* Sys 5-specific semantics (rejected) */

struct sun_mount_args {
	int	type;
	char	*dir;
	int	flags;
	caddr_t	data;
};
sun_mount(p, uap, retval)
	struct proc *p;
	struct sun_mount_args *uap;
	int *retval;
{
	int oflags = uap->flags, nflags, error;

	if (oflags & (SUNM_NOSUB | SUNM_SYS5))
		return (EINVAL);
	if (oflags & SUNM_NEWTYPE && (error = gettype(&uap->type)))
		return (error);
	nflags = 0;
	if (oflags & SUNM_RDONLY)
		nflags |= MNT_RDONLY;
	if (oflags & SUNM_NOSUID)
		nflags |= MNT_NOSUID;
	if (oflags & SUNM_REMOUNT)
		nflags |= MNT_UPDATE;
	uap->flags = nflags;
	return (mount(p, uap, retval));
}

struct sun_sigpending_args {
	int	*mask;
};
sun_sigpending(p, uap, retval)
	struct proc *p;
	struct sun_sigpending_args *uap;
	int *retval;
{
D 9
	int mask = p->p_sig & p->p_sigmask;
E 9
I 9
	int mask;
E 9

D 9
	return (copyout((caddr_t)&mask, (caddr_t)uap->mask, sizeof(int)));
E 9
I 9
	mask = p->p_siglist & p->p_sigmask;
	return (copyout(&mask, uap->mask, sizeof(int)));
E 9
}

D 5
#if 0
/* here is the sun layout (not used directly): */
E 5
I 5
/*
 * Here is the sun layout.  (Compare the BSD layout in <sys/dirent.h>.)
 * We can assume big-endian, so the BSD d_type field is just the high
 * byte of the SunOS d_namlen field, after adjusting for the extra "long".
 */
E 5
struct sun_dirent {
	long	d_off;
	u_long	d_fileno;
	u_short	d_reclen;
	u_short	d_namlen;
	char	d_name[256];
};
D 5
#endif
/* and the BSD layout: */
struct bsd_dirent {
	u_long	d_fileno;
	u_short	d_reclen;
	u_short	d_namlen;
	char	d_name[256];
};
E 5

/*
 * Read Sun-style directory entries.  We suck them into kernel space so
 * that they can be massaged before being copied out to user code.  Like
 * SunOS, we squish out `empty' entries.
 *
 * This is quite ugly, but what do you expect from compatibility code?
 */
struct sun_getdents_args {
	int	fd;
	char	*buf;
	int	nbytes;
};
sun_getdents(p, uap, retval)
	struct proc *p;
	register struct sun_getdents_args *uap;
	int *retval;
{
	register struct vnode *vp;
	register caddr_t inp, buf;	/* BSD-format */
	register int len, reclen;	/* BSD-format */
	register caddr_t outp;		/* Sun-format */
	register int resid;		/* Sun-format */
	struct file *fp;
	struct uio auio;
	struct iovec aiov;
	off_t off;			/* true file offset */
	long soff;			/* Sun file offset */
	int buflen, error, eofflag;
I 5
#define	BSD_DIRENT(cp) ((struct dirent *)(cp))
E 5
#define	SUN_RECLEN(reclen) (reclen + sizeof(long))

	if ((error = getvnode(p->p_fd, uap->fd, &fp)) != 0)
		return (error);
	if ((fp->f_flag & FREAD) == 0)
		return (EBADF);
	vp = (struct vnode *)fp->f_data;
	if (vp->v_type != VDIR)	/* XXX  vnode readdir op should do this */
		return (EINVAL);
	buflen = min(MAXBSIZE, uap->nbytes);
	buf = malloc(buflen, M_TEMP, M_WAITOK);
D 12
	VOP_LOCK(vp);
E 12
I 12
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p)
E 12
	off = fp->f_offset;
again:
	aiov.iov_base = buf;
	aiov.iov_len = buflen;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_procp = p;
	auio.uio_resid = buflen;
	auio.uio_offset = off;
	/*
	 * First we read into the malloc'ed buffer, then
	 * we massage it into user space, one record at a time.
	 */
D 10
	if (error = VOP_READDIR(vp, &auio, fp->f_cred, &eofflag))
E 10
I 10
	if (error = VOP_READDIR(vp, &auio, fp->f_cred, &eofflag, (u_long *)0,0))
E 10
		goto out;
	inp = buf;
	outp = uap->buf;
	resid = uap->nbytes;
	if ((len = buflen - auio.uio_resid) == 0)
		goto eof;
	for (; len > 0; len -= reclen) {
D 5
		reclen = ((struct bsd_dirent *)inp)->d_reclen;
E 5
I 5
		reclen = ((struct dirent *)inp)->d_reclen;
E 5
		if (reclen & 3)
			panic("sun_getdents");
		off += reclen;		/* each entry points to next */
D 5
		if (((struct bsd_dirent *)inp)->d_fileno == 0) {
E 5
I 5
		if (BSD_DIRENT(inp)->d_fileno == 0) {
E 5
			inp += reclen;	/* it is a hole; squish it out */
			continue;
		}
		if (reclen > len || resid < SUN_RECLEN(reclen)) {
			/* entry too big for buffer, so just stop */
			outp++;
			break;
		}
D 5
		/* copy out a Sun-shaped dirent */
		((struct bsd_dirent *)inp)->d_reclen = SUN_RECLEN(reclen);
E 5
I 5
		/*
		 * Massage in place to make a Sun-shaped dirent (otherwise
		 * we have to worry about touching user memory outside of
		 * the copyout() call).
		 */
		BSD_DIRENT(inp)->d_reclen = SUN_RECLEN(reclen);
		BSD_DIRENT(inp)->d_type = 0;
E 5
		soff = off;
		if ((error = copyout((caddr_t)&soff, outp, sizeof soff)) != 0 ||
		    (error = copyout(inp, outp + sizeof soff, reclen)) != 0)
			goto out;
		/* advance past this real entry */
		inp += reclen;
		/* advance output past Sun-shaped entry */
		outp += SUN_RECLEN(reclen);
		resid -= SUN_RECLEN(reclen);
	}
	/* if we squished out the whole block, try again */
	if (outp == uap->buf)
		goto again;
	fp->f_offset = off;		/* update the vnode offset */
eof:
	*retval = uap->nbytes - resid;
out:
D 12
	VOP_UNLOCK(vp);
E 12
I 12
	VOP_UNLOCK(vp, 0, p);
E 12
	free(buf, M_TEMP);
	return (error);
}

#define	MAXDOMAINNAME	64
char	sun_domainname[MAXDOMAINNAME];
int	sun_domainnamelen = 1;

struct sun_getdomainname_args {
	char	*name;
	int	namelen;
};
sun_getdomainname(p, uap, retval)
	struct proc *p;
	struct sun_getdomainname_args *uap;
	int *retval;
{
	register int l = min(uap->namelen, sun_domainnamelen + 1);

	return (copyout(sun_domainname, uap->name, l));
}

struct sun_setdomainname_args {
	char	*name;
	int	namelen;
};
sun_setdomainname(p, uap, retval)
	struct proc *p;
	struct sun_setdomainname_args *uap;
	int *retval;
{
	register int l = uap->namelen, error;

	if (l >= MAXDOMAINNAME)
		return (EINVAL);	/* ??? ENAMETOOLONG? */
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
	if (error = copyin(uap->name, sun_domainname, l))
		return (error);
	sun_domainname[l] = 0;
	return (0);
}

#define	SUN_MMAP_MASK	0xf		/* mask for SHARED/PRIVATE */
#define	SUN_MMAP_CANDO	0x80000000	/* if not, old mmap & cannot handle */

#define	DEVZERO	makedev(3, 12)		/* major,minor of /dev/zero */

#define	SUN_MMAP_SAME	(MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_INHERIT)

struct sun_mmap_args {
	caddr_t	addr;
	size_t	len;
	int	prot;
	int	flags;
	int	fd;
	long	off;		/* not off_t! */
D 7
	quad_t	qoff;		/* created here and fed to smmap() */
E 7
I 7
	quad_t	qoff;		/* created here and fed to mmap() */
E 7
};
sun_mmap(p, uap, retval)
	register struct proc *p;
	register struct sun_mmap_args *uap;
	int *retval;
{
	register int flags;
	register struct filedesc *fdp;
	register struct file *fp;
	register struct vnode *vp;

	/*
	 * Verify the arguments.
	 */
	flags = uap->flags;
	if ((flags & SUN_MMAP_CANDO) == 0)
		return (EINVAL);
	if ((flags & SUN_MMAP_MASK) != MAP_SHARED &&
	    (flags & SUN_MMAP_MASK) != MAP_PRIVATE)
		return (EINVAL);
	flags &= ~SUN_MMAP_CANDO;

	/*
	 * Special case: if fd refers to /dev/zero, map as MAP_ANON.  (XXX)
	 */
	fdp = p->p_fd;
	if ((unsigned)uap->fd < fdp->fd_nfiles &&			/*XXX*/
	    (fp = fdp->fd_ofiles[uap->fd]) != NULL &&			/*XXX*/
	    fp->f_type == DTYPE_VNODE &&				/*XXX*/
	    (vp = (struct vnode *)fp->f_data)->v_type == VCHR &&	/*XXX*/
	    vp->v_rdev == DEVZERO) {					/*XXX*/
		flags |= MAP_ANON;
		uap->fd = -1;
	}

	/* All done, fix up fields and go. */
	uap->flags = flags;
	uap->qoff = (quad_t)uap->off;
D 7
	return (smmap(p, uap, retval));
E 7
I 7
	return (mmap(p, uap, retval));
E 7
}

#define	MC_SYNC		1
#define	MC_LOCK		2
#define	MC_UNLOCK	3
#define	MC_ADVISE	4
#define	MC_LOCKAS	5
#define	MC_UNLOCKAS	6

struct sun_mctl_args {
	caddr_t	addr;
	size_t	len;
	int	func;
	void	*arg;
};
sun_mctl(p, uap, retval)
	register struct proc *p;
	register struct sun_mctl_args *uap;
	int *retval;
{

	switch (uap->func) {

	case MC_ADVISE:		/* ignore for now */
		return (0);

	case MC_SYNC:		/* translate to msync */
		return (msync(p, uap, retval));

	default:
		return (EINVAL);
	}
D 5
}

struct sun_setreuid_args {
	int	ruid;		/* not uid_t */
	int	euid;
};
sun_setreuid(p, uap, retval)
	struct proc *p;
	struct sun_setreuid_args *uap;
	int *retval;
{
	register struct pcred *pc = p->p_cred;
	register uid_t ruid, euid;
	int error;

	if (uap->ruid == -1)
		ruid = pc->p_ruid;
	else
		ruid = uap->ruid;
	/*
	 * Allow setting real uid to previous effective, for swapping real and
	 * effective.  This should be:
	 *
	 * if (ruid != pc->p_ruid &&
	 *     (error = suser(pc->pc_ucred, &p->p_acflag)))
	 */
	if (ruid != pc->p_ruid && ruid != pc->pc_ucred->cr_uid /* XXX */ &&
	    (error = suser(pc->pc_ucred, &p->p_acflag)))
		return (error);
	if (uap->euid == -1)
		euid = pc->pc_ucred->cr_uid;
	else
		euid = uap->euid;
	if (euid != pc->pc_ucred->cr_uid && euid != pc->p_ruid &&
	    euid != pc->p_svuid && (error = suser(pc->pc_ucred, &p->p_acflag)))
		return (error);
	/*
	 * Everything's okay, do it.  Copy credentials so other references do
	 * not see our changes.
	 */
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_uid = euid;
	pc->p_ruid = ruid;
	p->p_flag |= SUGID;
	return (0);
}

struct sun_setregid_args {
	int	rgid;		/* not gid_t */
	int	egid;
};
sun_setregid(p, uap, retval)
	struct proc *p;
	struct sun_setregid_args *uap;
	int *retval;
{
	register struct pcred *pc = p->p_cred;
	register gid_t rgid, egid;
	int error;

	if (uap->rgid == -1)
		rgid = pc->p_rgid;
	else
		rgid = uap->rgid;
	/*
	 * Allow setting real gid to previous effective, for swapping real and
	 * effective.  This didn't really work correctly in 4.[23], but is
	 * preserved so old stuff doesn't fail.  This should be:
	 *
	 * if (rgid != pc->p_rgid &&
	 *     (error = suser(pc->pc_ucred, &p->p_acflag)))
	 */
	if (rgid != pc->p_rgid && rgid != pc->pc_ucred->cr_groups[0] /* XXX */ &&
	    (error = suser(pc->pc_ucred, &p->p_acflag)))
		return (error);
	if (uap->egid == -1)
		egid = pc->pc_ucred->cr_groups[0];
	else
		egid = uap->egid;
	if (egid != pc->pc_ucred->cr_groups[0] && egid != pc->p_rgid &&
	    egid != pc->p_svgid && (error = suser(pc->pc_ucred, &p->p_acflag)))
		return (error);
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_groups[0] = egid;
	pc->p_rgid = rgid;
	p->p_flag |= SUGID;
	return (0);
E 5
}

struct sun_setsockopt_args {
	int	s;
	int	level;
	int	name;
	caddr_t	val;
	int	valsize;
};
sun_setsockopt(p, uap, retval)
	struct proc *p;
	register struct sun_setsockopt_args *uap;
	int *retval;
{
	struct file *fp;
	struct mbuf *m = NULL;
	int error;

	if (error = getsock(p->p_fd, uap->s, &fp))
		return (error);
#define	SO_DONTLINGER (~SO_LINGER)
	if (uap->name == SO_DONTLINGER) {
		m = m_get(M_WAIT, MT_SOOPTS);
		if (m == NULL)
			return (ENOBUFS);
		mtod(m, struct linger *)->l_onoff = 0;
		m->m_len = sizeof(struct linger);
		return (sosetopt((struct socket *)fp->f_data, uap->level,
		    SO_LINGER, m));
	}
	if (uap->valsize > MLEN)
		return (EINVAL);
	if (uap->val) {
		m = m_get(M_WAIT, MT_SOOPTS);
		if (m == NULL)
			return (ENOBUFS);
		if (error = copyin(uap->val, mtod(m, caddr_t),
		    (u_int)uap->valsize)) {
			(void) m_free(m);
			return (error);
		}
		m->m_len = uap->valsize;
	}
	return (sosetopt((struct socket *)fp->f_data, uap->level,
	    uap->name, m));
}

struct sun_fchroot_args {
	int	fdes;
};
sun_fchroot(p, uap, retval)
	register struct proc *p;
	register struct sun_fchroot_args *uap;
	int *retval;
{
	register struct filedesc *fdp = p->p_fd;
	register struct vnode *vp;
	struct file *fp;
	int error;

	if ((error = suser(p->p_ucred, &p->p_acflag)) != 0)
		return (error);
	if ((error = getvnode(fdp, uap->fdes, &fp)) != 0)
		return (error);
	vp = (struct vnode *)fp->f_data;
D 12
	VOP_LOCK(vp);
E 12
I 12
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p)
E 12
	if (vp->v_type != VDIR)
		error = ENOTDIR;
	else
		error = VOP_ACCESS(vp, VEXEC, p->p_ucred, p);
D 12
	VOP_UNLOCK(vp);
E 12
I 12
	VOP_UNLOCK(vp, 0, p);
E 12
	if (error)
		return (error);
	VREF(vp);
	if (fdp->fd_rdir != NULL)
		vrele(fdp->fd_rdir);
	fdp->fd_rdir = vp;
	return (0);
}
E 1
