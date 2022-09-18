h00226
s 00002/00000/00702
d D 8.14 95/05/21 19:48:30 mckusick 19 18
c inactive routine must unlock node
e
s 00005/00003/00697
d D 8.13 95/05/14 00:42:32 mckusick 18 17
c locking uses vop_nolock* functions
e
s 00019/00014/00681
d D 8.12 95/05/10 10:10:42 mckusick 17 16
c lookup error return cleanups (from mycroft)
e
s 00002/00000/00693
d D 8.11 95/04/03 23:15:38 mckusick 16 15
c add revoke operator
e
s 00003/00001/00690
d D 8.10 95/01/09 18:24:19 cgd 15 14
c microtime takes a timeval ptr.
e
s 00010/00000/00681
d D 8.9 94/06/04 19:36:18 mckusick 14 13
c add cookie and eofflag parameters to readdir
e
s 00000/00001/00681
d D 8.8 94/01/21 19:53:28 bostic 13 12
c copyright typo
e
s 00037/00000/00645
d D 8.7 94/01/14 08:28:54 pendry 12 11
c add pathconf entry point
e
s 00017/00111/00628
d D 8.6 94/01/05 12:12:54 pendry 11 10
c remove debug code.  KNF
e
s 00001/00001/00738
d D 8.5 94/01/05 05:45:19 pendry 10 9
c sosend's 2nd arg is mbuf, not sockaddr
e
s 00001/00003/00738
d D 8.4 94/01/04 21:39:46 bostic 9 8
c lint
e
s 00002/00001/00739
d D 8.3 94/01/04 07:52:26 pendry 8 7
c zero vp->v_data in reclaim
e
s 00001/00001/00739
d D 8.2 94/01/04 06:54:33 pendry 7 6
c allocate private VT_ tags
e
s 00002/00002/00738
d D 8.1 93/06/10 23:46:44 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00041/00037/00699
d D 7.3 92/08/15 15:02:37 pendry 5 4
c add local vars for args.
e
s 00006/00006/00730
d D 7.2 92/07/13 15:50:37 pendry 4 3
c fix typos
e
s 00077/00034/00659
d D 7.1 92/07/12 15:18:54 mckusick 3 2
c move to rev 7; new include location; syntax niggles
e
s 00007/00010/00686
d D 1.2 92/07/12 09:02:59 pendry 2 1
c new cred structure
e
s 00696/00000/00000
d D 1.1 92/06/03 14:26:06 pendry 1 0
c date and time created 92/06/03 14:26:06 by pendry
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
D 13
 * All rights reserved.
E 13
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: portal_vnops.c,v 1.4 1992/05/30 10:05:24 jsp Exp jsp $
 */

/*
 * Portal Filesystem
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/proc.h>
D 3
/*#include <sys/resourcevar.h>*/
E 3
#include <sys/filedesc.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/malloc.h>
#include <sys/namei.h>
D 3
/*#include <sys/buf.h>*/
E 3
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/un.h>
#include <sys/unpcb.h>
D 3
#include <portal/portal.h>
E 3
I 3
#include <miscfs/portal/portal.h>
E 3

static int portal_fileid = PORTAL_ROOTFILEID+1;

static void
portal_closefd(p, fd)
	struct proc *p;
	int fd;
{
	int error;
	struct {
		int fd;
	} ua;
	int rc;

	ua.fd = fd;
	error = close(p, &ua, &rc);
	/*
	 * We should never get an error, and there isn't anything
	 * we could do if we got one, so just print a message.
	 */
	if (error)
		printf("portal_closefd: error = %d\n", error);
}

/*
 * vp is the current namei directory
 * cnp is the name to locate in that directory...
 */
I 11
int
E 11
D 3
portal_lookup (ap)
	struct vop_lookup_args *ap;
E 3
I 3
portal_lookup(ap)
	struct vop_lookup_args /* {
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
	} */ *ap;
E 3
{
D 2
	/*USES_VOP_LOCK;*/
E 2
D 17
	char *pname = ap->a_cnp->cn_nameptr;
E 17
I 17
	struct componentname *cnp = ap->a_cnp;
	struct vnode **vpp = ap->a_vpp;
	struct vnode *dvp = ap->a_dvp;
	char *pname = cnp->cn_nameptr;
E 17
	struct portalnode *pt;
	int error;
	struct vnode *fvp = 0;
	char *path;
	int size;

D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_lookup(%s)\n", pname);
#endif
E 11
D 17
	if (ap->a_cnp->cn_namelen == 1 && *pname == '.') {
		*ap->a_vpp = ap->a_dvp;
		VREF(ap->a_dvp);
		/*VOP_LOCK(ap->a_dvp);*/
E 17
I 17
	*vpp = NULLVP;

	if (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME)
		return (EROFS);

	if (cnp->cn_namelen == 1 && *pname == '.') {
		*vpp = dvp;
		VREF(dvp);
		/*VOP_LOCK(dvp);*/
E 17
		return (0);
	}

D 17

D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_lookup: allocate new vnode\n");
#endif
E 11
D 7
	error = getnewvnode(VT_UFS, ap->a_dvp->v_mount, portal_vnodeop_p, &fvp);
E 7
I 7
	error = getnewvnode(VT_PORTAL, ap->a_dvp->v_mount, portal_vnodeop_p, &fvp);
E 17
I 17
	error = getnewvnode(VT_PORTAL, dvp->v_mount, portal_vnodeop_p, &fvp);
E 17
E 7
	if (error)
		goto bad;
	fvp->v_type = VREG;
D 17
	MALLOC(fvp->v_data, void *, sizeof(struct portalnode),
		M_TEMP, M_WAITOK);
E 17
I 17
	MALLOC(fvp->v_data, void *, sizeof(struct portalnode), M_TEMP,
	    M_WAITOK);
E 17

	pt = VTOPORTAL(fvp);
	/*
	 * Save all of the remaining pathname and
	 * advance the namei next pointer to the end
	 * of the string.
	 */
D 2
#ifdef notyet
E 2
	for (size = 0, path = pname; *path; path++)
		size++;
D 2
	ndp->ni_next = path;
	ndp->ni_pathlen -= size - ndp->ni_namelen;
#endif
E 2
I 2
D 17
	ap->a_cnp->cn_consume = size - ap->a_cnp->cn_namelen;
E 17
I 17
	cnp->cn_consume = size - cnp->cn_namelen;
E 17

E 2
	pt->pt_arg = malloc(size+1, M_TEMP, M_WAITOK);
	pt->pt_size = size+1;
	bcopy(pname, pt->pt_arg, pt->pt_size);
	pt->pt_fileid = portal_fileid++;

D 17
	*ap->a_vpp = fvp;
E 17
I 17
	*vpp = fvp;
E 17
	/*VOP_LOCK(fvp);*/
D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_lookup: newvp = %x\n", fvp);
#endif
E 11
	return (0);

bad:;
D 17
	if (fvp) {
E 17
I 17
	if (fvp)
E 17
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_lookup: vrele(%x)\n", fvp);
#endif
E 11
		vrele(fvp);
D 17
	}
	*ap->a_vpp = NULL;
E 17
D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_lookup: error = %d\n", error);
#endif
E 11
	return (error);
}

static int
portal_connect(so, so2)
	struct socket *so;
	struct socket *so2;
{
	/* from unp_connect, bypassing the namei stuff... */
D 11

E 11
	struct socket *so3;
	struct unpcb *unp2;
	struct unpcb *unp3;

D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_connect\n");
#endif

E 11
	if (so2 == 0)
		return (ECONNREFUSED);

	if (so->so_type != so2->so_type)
		return (EPROTOTYPE);

	if ((so2->so_options & SO_ACCEPTCONN) == 0)
		return (ECONNREFUSED);

D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_connect: calling sonewconn\n");
#endif

E 11
	if ((so3 = sonewconn(so2, 0)) == 0)
		return (ECONNREFUSED);

	unp2 = sotounpcb(so2);
	unp3 = sotounpcb(so3);
	if (unp2->unp_addr)
		unp3->unp_addr = m_copy(unp2->unp_addr, 0, (int)M_COPYALL);

	so2 = so3;

D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_connect: calling unp_connect2\n");
#endif
E 11

	return (unp_connect2(so, so2));
}

I 11
int
E 11
D 3
portal_open (ap)
	struct vop_open_args *ap;
E 3
I 3
portal_open(ap)
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 3
{
	struct socket *so = 0;
	struct portalnode *pt;
I 5
	struct proc *p = ap->a_p;
	struct vnode *vp = ap->a_vp;
E 5
	int s;
	struct uio auio;
	struct iovec aiov[2];
	int res;
	struct mbuf *cm = 0;
	struct cmsghdr *cmsg;
	int newfds;
	int *ip;
	int fd;
	int error;
	int len;
	struct portalmount *fmp;
	struct file *fp;
	struct portal_cred pcred;

	/*
	 * Nothing to do when opening the root node.
	 */
D 5
	if (ap->a_vp->v_flag & VROOT)
E 5
I 5
	if (vp->v_flag & VROOT)
E 5
		return (0);

D 11
#ifdef PORTAL_DIAGNOSTIC
D 5
	printf("portal_open(%x)\n", ap->a_vp);
E 5
I 5
	printf("portal_open(%x)\n", vp);
E 5
#endif

E 11
	/*
	 * Can't be opened unless the caller is set up
	 * to deal with the side effects.  Check for this
	 * by testing whether the p_dupfd has been set.
	 */
D 5
	if (ap->a_p->p_dupfd >= 0)
E 5
I 5
	if (p->p_dupfd >= 0)
E 5
		return (ENODEV);

D 5
	pt = VTOPORTAL(ap->a_vp);
	fmp = VFSTOPORTAL(ap->a_vp->v_mount);
E 5
I 5
	pt = VTOPORTAL(vp);
	fmp = VFSTOPORTAL(vp->v_mount);
E 5

	/*
	 * Create a new socket.
	 */
	error = socreate(AF_UNIX, &so, SOCK_STREAM, 0);
	if (error)
		goto bad;

	/*
	 * Reserve some buffer space
	 */
D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_open: calling soreserve\n");
#endif
E 11
D 2
	res = max(512, pt->pt_size + 128);
E 2
I 2
	res = pt->pt_size + sizeof(pcred) + 512;	/* XXX */
E 2
	error = soreserve(so, res, res);
	if (error)
		goto bad;

	/*
	 * Kick off connection
	 */
D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_open: calling portal_connect\n");
#endif
E 11
	error = portal_connect(so, (struct socket *)fmp->pm_server->f_data);
	if (error)
		goto bad;

	/*
	 * Wait for connection to complete
	 */
D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_open: waiting for connect\n");
#endif
E 11
	/*
	 * XXX: Since the mount point is holding a reference on the
	 * underlying server socket, it is not easy to find out whether
	 * the server process is still running.  To handle this problem
	 * we loop waiting for the new socket to be connected (something
	 * which will only happen if the server is still running) or for
	 * the reference count on the server socket to drop to 1, which
	 * will happen if the server dies.  Sleep for 5 second intervals
	 * and keep polling the reference count.   XXX.
	 */
	s = splnet();
	while ((so->so_state & SS_ISCONNECTING) && so->so_error == 0) {
		if (fmp->pm_server->f_count == 1) {
			error = ECONNREFUSED;
			splx(s);
D 11
#ifdef PORTAL_DIAGNOSTIC
			printf("portal_open: server process has gone away\n");
#endif
E 11
			goto bad;
		}
		(void) tsleep((caddr_t) &so->so_timeo, PSOCK, "portalcon", 5 * hz);
	}
	splx(s);

	if (so->so_error) {
		error = so->so_error;
		goto bad;
	}
		
	/*
	 * Set miscellaneous flags
	 */
	so->so_rcv.sb_timeo = 0;
	so->so_snd.sb_timeo = 0;
	so->so_rcv.sb_flags |= SB_NOINTR;
	so->so_snd.sb_flags |= SB_NOINTR;

D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_open: constructing data uio\n");
#endif
E 11

I 2
	pcred.pcr_flag = ap->a_mode;
E 2
	pcred.pcr_uid = ap->a_cred->cr_uid;
D 2
	pcred.pcr_gid = ap->a_cred->cr_gid;
E 2
I 2
	pcred.pcr_ngroups = ap->a_cred->cr_ngroups;
	bcopy(ap->a_cred->cr_groups, pcred.pcr_groups, NGROUPS * sizeof(gid_t));
E 2
	aiov[0].iov_base = (caddr_t) &pcred;
	aiov[0].iov_len = sizeof(pcred);
	aiov[1].iov_base = pt->pt_arg;
	aiov[1].iov_len = pt->pt_size;
	auio.uio_iov = aiov;
	auio.uio_iovcnt = 2;
	auio.uio_rw = UIO_WRITE;
	auio.uio_segflg = UIO_SYSSPACE;
D 5
	auio.uio_procp = ap->a_p;
E 5
I 5
	auio.uio_procp = p;
E 5
	auio.uio_offset = 0;
	auio.uio_resid = aiov[0].iov_len + aiov[1].iov_len;

D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_open: sending data to server\n");
#endif
E 11
D 10
	error = sosend(so, (struct sockaddr *) 0, &auio,
E 10
I 10
	error = sosend(so, (struct mbuf *) 0, &auio,
E 10
			(struct mbuf *) 0, (struct mbuf *) 0, 0);
	if (error)
		goto bad;

	len = auio.uio_resid = sizeof(int);
	do {
		struct mbuf *m = 0;
		int flags = MSG_WAITALL;
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_open: receiving data from server\n");
		printf("portal_open: so = %x, cm = %x, resid = %d\n",
				so, cm, auio.uio_resid);
		printf("portal_open, uio=%x, mp0=%x, controlp=%x\n", &auio, &cm);
#endif
E 11
		error = soreceive(so, (struct mbuf **) 0, &auio,
					&m, &cm, &flags);
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_open: after receiving data\n");
		printf("portal_open: so = %x, cm = %x, resid = %d\n",
				so, cm, auio.uio_resid);
#endif
E 11
		if (error)
			goto bad;

		/*
		 * Grab an error code from the mbuf.
		 */
		if (m) {
			m = m_pullup(m, sizeof(int));	/* Needed? */
			if (m) {
				error = *(mtod(m, int *));
				m_freem(m);
			} else {
				error = EINVAL;
			}
D 11
#ifdef PORTAL_DIAGNOSTIC
			printf("portal_open: error returned is %d\n", error);
#endif
E 11
		} else {
			if (cm == 0) {
D 11
#ifdef PORTAL_DIAGNOSTIC
				printf("portal_open: no rights received\n");
#endif
E 11
				error = ECONNRESET;	 /* XXX */
#ifdef notdef
				break;
#endif
			}
		}
	} while (cm == 0 && auio.uio_resid == len && !error);

	if (cm == 0)
		goto bad;

	if (auio.uio_resid) {
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_open: still need another %d bytes\n", auio.uio_resid);
#endif
E 11
		error = 0;
#ifdef notdef
		error = EMSGSIZE;
		goto bad;
#endif
	}

	/*
	 * XXX: Break apart the control message, and retrieve the
	 * received file descriptor.  Note that more than one descriptor
	 * may have been received, or that the rights chain may have more
	 * than a single mbuf in it.  What to do?
	 */
D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_open: about to break apart control message\n");
#endif
E 11
	cmsg = mtod(cm, struct cmsghdr *);
	newfds = (cmsg->cmsg_len - sizeof(*cmsg)) / sizeof (int);
	if (newfds == 0) {
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_open: received no fds\n");
#endif
E 11
		error = ECONNREFUSED;
		goto bad;
	}
	/*
	 * At this point the rights message consists of a control message
	 * header, followed by a data region containing a vector of
	 * integer file descriptors.  The fds were allocated by the action
	 * of receiving the control message.
	 */
	ip = (int *) (cmsg + 1);
	fd = *ip++;
	if (newfds > 1) {
		/*
		 * Close extra fds.
		 */
		int i;
		printf("portal_open: %d extra fds\n", newfds - 1);
		for (i = 1; i < newfds; i++) {
D 5
			portal_closefd(ap->a_p, *ip);
E 5
I 5
			portal_closefd(p, *ip);
E 5
			ip++;
		}
	}

	/*
D 5
	 * Check that the ap->a_mode the file is being opened for is a subset 
	 * of the ap->a_mode of the existing descriptor.
E 5
I 5
	 * Check that the mode the file is being opened for is a subset 
	 * of the mode of the existing descriptor.
E 5
	 */
D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_open: checking file flags, fd = %d\n", fd);
#endif
E 11
D 5
 	fp = ap->a_p->p_fd->fd_ofiles[fd];
E 5
I 5
 	fp = p->p_fd->fd_ofiles[fd];
E 5
	if (((ap->a_mode & (FREAD|FWRITE)) | fp->f_flag) != fp->f_flag) {
D 5
		portal_closefd(ap->a_p, fd);
E 5
I 5
		portal_closefd(p, fd);
E 5
		error = EACCES;
		goto bad;
	}

D 11
#ifdef PORTAL_DIAGNOSTIC
	printf("portal_open: got fd = %d\n", fd);
#endif
E 11
	/*
	 * Save the dup fd in the proc structure then return the
	 * special error code (ENXIO) which causes magic things to
	 * happen in vn_open.  The whole concept is, well, hmmm.
	 */
D 5
	ap->a_p->p_dupfd = fd;
E 5
I 5
	p->p_dupfd = fd;
E 5
	error = ENXIO;

bad:;
	/*
	 * And discard the control message.
	 */
	if (cm) { 
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_open: free'ing control message\n");
#endif
E 11
		m_freem(cm);
	}

	if (so) {
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_open: calling soshutdown\n");
#endif
E 11
		soshutdown(so, 2);
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_open: calling soclose\n");
#endif
E 11
		soclose(so);
	}
D 11
#ifdef PORTAL_DIAGNOSTIC
	if (error != ENODEV)
		printf("portal_open: error = %d\n", error);
#endif
E 11
	return (error);
}

I 11
int
E 11
D 3
portal_getattr (ap)
	struct vop_getattr_args *ap;
E 3
I 3
portal_getattr(ap)
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 3
{
I 5
	struct vnode *vp = ap->a_vp;
	struct vattr *vap = ap->a_vap;
I 15
	struct timeval tv;
E 15
E 5
D 9
	unsigned fd;
	int error;
E 9

D 5
	bzero((caddr_t) ap->a_vap, sizeof(*ap->a_vap));
	vattr_null(ap->a_vap);
	ap->a_vap->va_uid = 0;
	ap->a_vap->va_gid = 0;
	ap->a_vap->va_fsid = ap->a_vp->v_mount->mnt_stat.f_fsid.val[0];
	ap->a_vap->va_size = DEV_BSIZE;
	ap->a_vap->va_blocksize = DEV_BSIZE;
	microtime(&ap->a_vap->va_atime);
	ap->a_vap->va_mtime = ap->a_vap->va_atime;
	ap->a_vap->va_ctime = ap->a_vap->va_ctime;
	ap->a_vap->va_gen = 0;
	ap->a_vap->va_flags = 0;
	ap->a_vap->va_rdev = 0;
	/* ap->a_vap->va_qbytes = 0; */
	ap->a_vap->va_bytes = 0;
	/* ap->a_vap->va_qsize = 0; */
	if (ap->a_vp->v_flag & VROOT) {
E 5
I 5
D 9
	bzero((caddr_t) vap, sizeof(*vap));
E 9
I 9
	bzero(vap, sizeof(*vap));
E 9
	vattr_null(vap);
	vap->va_uid = 0;
	vap->va_gid = 0;
	vap->va_fsid = vp->v_mount->mnt_stat.f_fsid.val[0];
	vap->va_size = DEV_BSIZE;
	vap->va_blocksize = DEV_BSIZE;
D 15
	microtime(&vap->va_atime);
E 15
I 15
	microtime(&tv);
	TIMEVAL_TO_TIMESPEC(&tv, &vap->va_atime);
E 15
	vap->va_mtime = vap->va_atime;
	vap->va_ctime = vap->va_ctime;
	vap->va_gen = 0;
	vap->va_flags = 0;
	vap->va_rdev = 0;
	/* vap->va_qbytes = 0; */
	vap->va_bytes = 0;
	/* vap->va_qsize = 0; */
	if (vp->v_flag & VROOT) {
E 5
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_getattr: stat rootdir\n");
#endif
E 11
D 5
		ap->a_vap->va_type = VDIR;
		ap->a_vap->va_mode = S_IRUSR|S_IWUSR|S_IXUSR|
E 5
I 5
		vap->va_type = VDIR;
		vap->va_mode = S_IRUSR|S_IWUSR|S_IXUSR|
E 5
				S_IRGRP|S_IWGRP|S_IXGRP|
				S_IROTH|S_IWOTH|S_IXOTH;
D 5
		ap->a_vap->va_nlink = 2;
		ap->a_vap->va_fileid = 2;
E 5
I 5
		vap->va_nlink = 2;
		vap->va_fileid = 2;
E 5
	} else {
D 11
#ifdef PORTAL_DIAGNOSTIC
		printf("portal_getattr: stat portal\n");
#endif
E 11
D 5
		ap->a_vap->va_type = VREG;
		ap->a_vap->va_mode = S_IRUSR|S_IWUSR|
E 5
I 5
		vap->va_type = VREG;
		vap->va_mode = S_IRUSR|S_IWUSR|
E 5
				S_IRGRP|S_IWGRP|
				S_IROTH|S_IWOTH;
D 5
		ap->a_vap->va_nlink = 1;
		ap->a_vap->va_fileid = VTOPORTAL(ap->a_vp)->pt_fileid;
E 5
I 5
		vap->va_nlink = 1;
		vap->va_fileid = VTOPORTAL(vp)->pt_fileid;
E 5
	}
	return (0);
}

I 11
int
E 11
D 3
portal_setattr (ap)
	struct vop_setattr_args *ap;
E 3
I 3
portal_setattr(ap)
	struct vop_setattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 3
{
I 11

E 11
	/*
	 * Can't mess with the root vnode
	 */
	if (ap->a_vp->v_flag & VROOT)
		return (EACCES);

	return (0);
}

/*
 * Fake readdir, just return empty directory.
 * It is hard to deal with '.' and '..' so don't bother.
 */
I 11
int
E 11
D 3
portal_readdir (ap)
	struct vop_readdir_args *ap;
E 3
I 3
portal_readdir(ap)
	struct vop_readdir_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
I 14
		int *a_eofflag;
		u_long *a_cookies;
		int a_ncookies;
E 14
	} */ *ap;
E 3
{
I 14

	/*
	 * We don't allow exporting portal mounts, and currently local
	 * requests do not need cookies.
	 */
	if (ap->a_ncookies)
		panic("portal_readdir: not hungry");
E 14
D 2
	*ap->a_eofflagp = 1;
E 2
I 2
D 11
	/* *ap->a_eofflagp = 1; */
E 11
I 11

E 11
E 2
	return (0);
}

I 11
int
E 11
D 3
portal_inactive (ap)
	struct vop_inactive_args *ap;
E 3
I 3
portal_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 19
		struct proc *a_p;
E 19
	} */ *ap;
E 3
{
D 11
#ifdef PORTAL_DIAGNOSTIC
	if (VTOPORTAL(ap->a_vp)->pt_arg)
		printf("portal_inactive(%x, %s)\n", ap->a_vp, VTOPORTAL(ap->a_vp)->pt_arg);
	else
		printf("portal_inactive(%x)\n", ap->a_vp);
#endif
	/*vgone(ap->a_vp);*/
E 11
I 11

I 19
	VOP_UNLOCK(ap->a_vp, 0, ap->a_p);
E 19
E 11
	return (0);
}

I 11
int
E 11
D 3
portal_reclaim (ap)
	struct vop_reclaim_args *ap;
E 3
I 3
portal_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 3
{
	struct portalnode *pt = VTOPORTAL(ap->a_vp);
D 11
#ifdef PORTAL_DIAGOISTIC
	printf("portal_reclaim(%x)\n", ap->a_vp);
#endif
E 11
I 11

E 11
	if (pt->pt_arg) {
		free((caddr_t) pt->pt_arg, M_TEMP);
		pt->pt_arg = 0;
	}
D 8
	FREE(pt, M_TEMP);
E 8
I 8
	FREE(ap->a_vp->v_data, M_TEMP);
	ap->a_vp->v_data = 0;
I 11

E 11
E 8
	return (0);
}

/*
I 12
 * Return POSIX pathconf information applicable to special devices.
 */
portal_pathconf(ap)
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
E 12
 * Print out the contents of a Portal vnode.
 */
/* ARGSUSED */
I 11
int
E 11
D 3
portal_print (ap)
	struct vop_print_args *ap;
E 3
I 3
portal_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 3
{
I 3

E 3
	printf("tag VT_PORTAL, portal vnode\n");
I 3
	return (0);
E 3
}

/*void*/
I 11
int
E 11
D 3
portal_vfree (ap)
	struct vop_vfree_args *ap;
E 3
I 3
portal_vfree(ap)
	struct vop_vfree_args /* {
		struct vnode *a_pvp;
		ino_t a_ino;
		int a_mode;
	} */ *ap;
E 3
{
D 3
	return;
E 3
I 3

	return (0);
E 3
}


/*
 * Portal vnode unsupported operation
 */
I 11
int
E 11
portal_enotsupp()
{
I 3

E 3
	return (EOPNOTSUPP);
}

/*
 * Portal "should never get here" operation
 */
I 11
int
E 11
portal_badop()
{
I 3

E 3
	panic("portal: bad op");
	/* NOTREACHED */
}

/*
 * Portal vnode null operation
 */
I 11
int
E 11
portal_nullop()
{
I 3

E 3
	return (0);
}

D 3
#define portal_create ((int (*) __P((struct  vop_create_args *)))portal_enotsupp)
E 3
I 3
#define portal_create ((int (*) __P((struct vop_create_args *)))portal_enotsupp)
E 3
#define portal_mknod ((int (*) __P((struct  vop_mknod_args *)))portal_enotsupp)
#define portal_close ((int (*) __P((struct  vop_close_args *)))nullop)
#define portal_access ((int (*) __P((struct  vop_access_args *)))nullop)
#define portal_read ((int (*) __P((struct  vop_read_args *)))portal_enotsupp)
#define portal_write ((int (*) __P((struct  vop_write_args *)))portal_enotsupp)
#define portal_ioctl ((int (*) __P((struct  vop_ioctl_args *)))portal_enotsupp)
D 3
#define portal_select ((int (*) __P((struct  vop_select_args *)))portal_enotsupp)
E 3
I 3
#define portal_select ((int (*) __P((struct vop_select_args *)))portal_enotsupp)
E 3
#define portal_mmap ((int (*) __P((struct  vop_mmap_args *)))portal_enotsupp)
I 16
#define	portal_revoke vop_revoke
E 16
#define portal_fsync ((int (*) __P((struct  vop_fsync_args *)))nullop)
#define portal_seek ((int (*) __P((struct  vop_seek_args *)))nullop)
D 3
#define portal_remove ((int (*) __P((struct  vop_remove_args *)))portal_enotsupp)
E 3
I 3
#define portal_remove ((int (*) __P((struct vop_remove_args *)))portal_enotsupp)
E 3
#define portal_link ((int (*) __P((struct  vop_link_args *)))portal_enotsupp)
D 3
#define portal_rename ((int (*) __P((struct  vop_rename_args *)))portal_enotsupp)
E 3
I 3
#define portal_rename ((int (*) __P((struct vop_rename_args *)))portal_enotsupp)
E 3
#define portal_mkdir ((int (*) __P((struct  vop_mkdir_args *)))portal_enotsupp)
#define portal_rmdir ((int (*) __P((struct  vop_rmdir_args *)))portal_enotsupp)
D 3
#define portal_symlink ((int (*) __P((struct  vop_symlink_args *)))portal_enotsupp)
#define portal_readlink ((int (*) __P((struct  vop_readlink_args *)))portal_enotsupp)
E 3
I 3
D 4
#define portal_symlink
E 4
I 4
#define portal_symlink \
E 4
	((int (*) __P((struct  vop_symlink_args *)))portal_enotsupp)
D 4
#define portal_readlink
E 4
I 4
#define portal_readlink \
E 4
	((int (*) __P((struct  vop_readlink_args *)))portal_enotsupp)
E 3
#define portal_abortop ((int (*) __P((struct  vop_abortop_args *)))nullop)
D 18
#define portal_lock ((int (*) __P((struct  vop_lock_args *)))nullop)
#define portal_unlock ((int (*) __P((struct  vop_unlock_args *)))nullop)
E 18
I 18
#define portal_lock ((int (*) __P((struct  vop_lock_args *)))vop_nolock)
#define portal_unlock ((int (*) __P((struct  vop_unlock_args *)))vop_nounlock)
E 18
#define portal_bmap ((int (*) __P((struct  vop_bmap_args *)))portal_badop)
D 3
#define portal_strategy ((int (*) __P((struct  vop_strategy_args *)))portal_badop)
E 3
I 3
D 4
#define portal_strategy
E 4
I 4
#define portal_strategy \
E 4
	((int (*) __P((struct  vop_strategy_args *)))portal_badop)
E 3
D 18
#define portal_islocked ((int (*) __P((struct  vop_islocked_args *)))nullop)
E 18
I 18
#define portal_islocked \
	((int (*) __P((struct vop_islocked_args *)))vop_noislocked)
#define fifo_islocked ((int(*) __P((struct vop_islocked_args *)))vop_noislocked)
E 18
D 3
#define portal_advlock ((int (*) __P((struct  vop_advlock_args *)))portal_enotsupp)
#define portal_blkatoff ((int (*) __P((struct  vop_blkatoff_args *)))portal_enotsupp)
E 3
I 3
D 4
#define portal_advlock
E 4
I 4
#define portal_advlock \
E 4
	((int (*) __P((struct  vop_advlock_args *)))portal_enotsupp)
D 4
#define portal_blkatoff
E 4
I 4
#define portal_blkatoff \
E 4
	((int (*) __P((struct  vop_blkatoff_args *)))portal_enotsupp)
E 3
D 2
#define portal_vget ((int (*) __P((struct  vop_vget_args *)))portal_enotsupp)
E 2
#define portal_valloc ((int(*) __P(( \
		struct vnode *pvp, \
		int mode, \
		struct ucred *cred, \
		struct vnode **vpp))) portal_enotsupp)
D 3
#define portal_truncate ((int (*) __P((struct  vop_truncate_args *)))portal_enotsupp)
#define portal_update ((int (*) __P((struct  vop_update_args *)))portal_enotsupp)
#define portal_bwrite ((int (*) __P((struct  vop_bwrite_args *)))portal_enotsupp)
E 3
I 3
D 4
#define portal_truncate
E 4
I 4
#define portal_truncate \
E 4
	((int (*) __P((struct  vop_truncate_args *)))portal_enotsupp)
#define portal_update ((int (*) __P((struct vop_update_args *)))portal_enotsupp)
#define portal_bwrite ((int (*) __P((struct vop_bwrite_args *)))portal_enotsupp)
E 3

int (**portal_vnodeop_p)();
struct vnodeopv_entry_desc portal_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, portal_lookup },		/* lookup */
	{ &vop_create_desc, portal_create },		/* create */
	{ &vop_mknod_desc, portal_mknod },		/* mknod */
	{ &vop_open_desc, portal_open },		/* open */
	{ &vop_close_desc, portal_close },		/* close */
	{ &vop_access_desc, portal_access },		/* access */
	{ &vop_getattr_desc, portal_getattr },		/* getattr */
	{ &vop_setattr_desc, portal_setattr },		/* setattr */
	{ &vop_read_desc, portal_read },		/* read */
	{ &vop_write_desc, portal_write },		/* write */
	{ &vop_ioctl_desc, portal_ioctl },		/* ioctl */
	{ &vop_select_desc, portal_select },		/* select */
	{ &vop_mmap_desc, portal_mmap },		/* mmap */
I 16
	{ &vop_revoke_desc, portal_revoke },		/* revoke */
E 16
	{ &vop_fsync_desc, portal_fsync },		/* fsync */
	{ &vop_seek_desc, portal_seek },		/* seek */
	{ &vop_remove_desc, portal_remove },		/* remove */
	{ &vop_link_desc, portal_link },		/* link */
	{ &vop_rename_desc, portal_rename },		/* rename */
	{ &vop_mkdir_desc, portal_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, portal_rmdir },		/* rmdir */
	{ &vop_symlink_desc, portal_symlink },		/* symlink */
	{ &vop_readdir_desc, portal_readdir },		/* readdir */
	{ &vop_readlink_desc, portal_readlink },	/* readlink */
	{ &vop_abortop_desc, portal_abortop },		/* abortop */
	{ &vop_inactive_desc, portal_inactive },	/* inactive */
	{ &vop_reclaim_desc, portal_reclaim },		/* reclaim */
	{ &vop_lock_desc, portal_lock },		/* lock */
	{ &vop_unlock_desc, portal_unlock },		/* unlock */
	{ &vop_bmap_desc, portal_bmap },		/* bmap */
	{ &vop_strategy_desc, portal_strategy },	/* strategy */
	{ &vop_print_desc, portal_print },		/* print */
	{ &vop_islocked_desc, portal_islocked },	/* islocked */
I 12
	{ &vop_pathconf_desc, portal_pathconf },	/* pathconf */
E 12
	{ &vop_advlock_desc, portal_advlock },		/* advlock */
	{ &vop_blkatoff_desc, portal_blkatoff },	/* blkatoff */
D 2
	{ &vop_vget_desc, portal_vget },		/* vget */
E 2
	{ &vop_valloc_desc, portal_valloc },		/* valloc */
	{ &vop_vfree_desc, portal_vfree },		/* vfree */
	{ &vop_truncate_desc, portal_truncate },	/* truncate */
	{ &vop_update_desc, portal_update },		/* update */
	{ &vop_bwrite_desc, portal_bwrite },		/* bwrite */
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
struct vnodeopv_desc portal_vnodeop_opv_desc =
	{ &portal_vnodeop_p, portal_vnodeop_entries };
E 1
