h16937
s 00002/00002/00230
d D 8.2 95/05/14 00:50:34 mckusick 3 2
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00002/00230
d D 8.1 93/06/11 15:04:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00232/00000/00000
d D 7.1 93/03/10 00:00:15 utashiro 1 0
c date and time created 93/03/10 00:00:15 by utashiro
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 *	%sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Hdr: sun_misc.c,v 1.12 92/07/12 13:26:10 torek Exp $
 */

/*
 * NEWS-OS compatibility module.
 *
 * NEWS-OS system calls that are implemented differently in BSD are
 * handled here.
 */

#include <sys/param.h>
#include <sys/systm.h>
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

#include <miscfs/specfs/specdev.h>

#include <vm/vm.h>

#if 0
/* here is the sun layout (not used directly): */
struct sun_dirent {
	long	d_off;
	u_long	d_fileno;
	u_short	d_reclen;
	u_short	d_namlen;
	char	d_name[256];
};
#endif
/* and the BSD layout: */
struct bsd_dirent {
	u_long	d_fileno;
	u_short	d_reclen;
	u_short	d_namlen;
	char	d_name[256];
};

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
D 3
	VOP_LOCK(vp);
E 3
I 3
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p)
E 3
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
	if (error = VOP_READDIR(vp, &auio, fp->f_cred, &eofflag))
		goto out;
	inp = buf;
	outp = uap->buf;
	resid = uap->nbytes;
	if ((len = buflen - auio.uio_resid) == 0)
		goto eof;
	for (; len > 0; len -= reclen) {
		reclen = ((struct bsd_dirent *)inp)->d_reclen;
		if (reclen & 3)
			panic("sun_getdents");
		off += reclen;		/* each entry points to next */
		if (((struct bsd_dirent *)inp)->d_fileno == 0) {
			inp += reclen;	/* it is a hole; squish it out */
			continue;
		}
		if (reclen > len || resid < SUN_RECLEN(reclen)) {
			/* entry too big for buffer, so just stop */
			outp++;
			break;
		}
		/* copy out a Sun-shaped dirent */
		((struct bsd_dirent *)inp)->d_reclen = SUN_RECLEN(reclen);
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
D 3
	VOP_UNLOCK(vp);
E 3
I 3
	VOP_UNLOCK(vp, 0, p);
E 3
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

/*
 * setenvp system call
 */
struct news_setenvp_args {
	char	**envp;
};
news_setenvp(p, args, retval)
	struct proc *p;
	struct news_setenvp_args *args;
	int *retval;
{

	return (0);
}

/*
 * sysnews system call
 */
struct news_sysnews_args {
	int	ctrltype;
	int	arg1, arg2, arg3, arg4;
};
news_sysnews(p, args, retval)
	struct proc *p;
	struct news_sysnews_args *args;
	int *retval;
{

	return (0);
}
E 1
