h26270
s 00001/00001/00118
d D 8.2 95/05/14 00:50:08 mckusick 20 19
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00002/00117
d D 8.1 93/06/10 22:53:43 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00014/00105
d D 7.10 92/10/11 11:49:44 bostic 18 17
c make kernel includes standard
e
s 00000/00001/00119
d D 7.9 92/09/21 14:17:09 mckusick 17 16
c get rid of USES keywords
e
s 00001/00000/00119
d D 7.8 92/05/14 17:40:28 heideman 16 7
c vnode interface conversion
e
s 00001/00000/00119
d R 7.8 92/05/14 15:59:25 heideman 15 7
c vnode interface conversion
e
s 00001/00000/00119
d R 7.8 92/05/14 14:58:49 heideman 14 7
c vnode interface conversion
e
s 00001/00000/00119
d R 7.8 92/05/14 13:06:40 heideman 13 7
c vnode interface conversion
e
s 00001/00000/00119
d R 7.8 92/05/14 12:03:06 heideman 12 7
c vnode interface conversion
e
s 00001/00000/00119
d R 7.8 92/05/14 11:26:37 heideman 11 7
c vnode interface conversion
e
s 00001/00000/00119
d R 7.8 92/05/13 23:22:20 heideman 10 7
c vnode interface conversion
e
s 00001/00000/00119
d R 7.8 92/05/13 19:05:14 heideman 9 7
c vnode interface conversion
e
s 00001/00000/00119
d R 7.8 92/05/13 18:37:30 heideman 8 7
c vnode interface conversion
e
s 00002/00003/00117
d D 7.7 92/02/05 18:09:00 sklower 7 6
c new namei calling convention
e
s 00017/00025/00103
d D 7.6 91/06/26 17:06:35 sklower 6 5
c play catchup with newvm changes
e
s 00002/00001/00126
d D 7.5 91/04/12 18:08:02 mckusick 5 4
c add additional argument to vn_rdwr()
e
s 00001/00001/00126
d D 7.4 91/03/12 15:09:51 sklower 4 3
c old cpp forgave missing double quotes at end of #include line, gcc doesn't
e
s 00027/00100/00100
d D 7.3 90/08/30 18:48:30 sklower 3 2
c this version compiles; completely untested
e
s 00013/00001/00187
d D 7.2 90/05/11 15:22:06 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00188/00000/00000
d D 7.1 90/05/11 11:19:38 sklower 1 0
c date and time created 90/05/11 11:19:38 by sklower
e
u
U
t
T
I 1
D 2
/* Copyright (c) University of British Columbia, 1984 */
E 2
I 2
/*
 * Copyright (c) University of British Columbia, 1984
D 19
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 3
#include "../h/param.h"
#ifdef NFS
E 3
I 3
D 4
#include "param.h
E 4
I 4
D 18
#include "param.h"
E 4
E 3
#include "systm.h"
D 3
#include "dir.h"
E 3
I 3
D 6
#include "time.h"
E 6
I 6
#include "namei.h"
E 6
#include "proc.h"
E 3
D 6
#include "user.h"
E 6
#include "vnode.h"
D 3
#include "vfs.h"
E 3
#include "kernel.h"
I 3
#include "file.h"
D 6
#include "acct.h"
E 3
#include "uio.h"
E 6
D 3
#else
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/inode.h"
#include "../h/kernel.h"
#ifdef BSD4_3
#include "../h/namei.h"
#else
#include "../h/nami.h"
#endif
#include "../h/uio.h"
#endif
E 3
I 3
#include "socket.h"
#include "socketvar.h"
E 18
I 18
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
E 18
E 3

D 3
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
#include "../netccitt/x25.h"
#include "../netccitt/x25acct.h"
E 3
I 3
D 18
#include "../net/if.h"
E 18
I 18
#include <net/if.h>
E 18
E 3

I 3
D 18
#include "x25.h"
#include "pk.h"
#include "pk_var.h"
#include "x25acct.h"
E 18
I 18
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
#include <netccitt/x25acct.h>
E 18
E 3

D 3
#ifdef NFS
struct	vnode *pkacctp;
#else
struct	inode *pkacctp;
#endif
E 3

I 3
struct	vnode *pkacctp;
E 3
/* 
 *  Turn on packet accounting
 */

pk_accton (path)
	char *path;
{
I 16
D 17
	USES_VOP_UNLOCK;
E 17
E 16
D 3
#ifdef NFS
	register int error;
	struct vnode *vp;
#else
#ifdef BSD4_3
	struct nameidata *ndp = &u.u_nd;
#endif
	register struct inode *ip;
#endif
E 3
I 3
	register struct vnode *vp = NULL;
D 6
	register struct nameidata *ndp = &u.u_nd;
E 6
I 6
	struct nameidata nd;
E 6
	struct vnode *oacctp = pkacctp;
I 6
	struct proc *p = curproc;
E 6
	int error;
E 3

D 3
#ifdef NFS
	if (error = lookupname(path, UIO_USERSPACE, FOLLOW_LINK,
		(struct vnode **)0, &vp))
E 3
I 3
D 6
	ndp -> ni_segflg = UIO_USERSPACE;
	ndp -> ni_dirp = path;
	if (error = vn_open (ndp, FREAD|FWRITE, 0))
E 6
I 6
	if (path == 0)
		goto close;
D 7
	nd.ni_segflg = UIO_USERSPACE;
	nd.ni_dirp = path;
	if (error = vn_open (&nd, p, FWRITE, 0644))
E 7
I 7
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, path, p);
	if (error = vn_open (&nd, FWRITE, 0644))
E 7
E 6
E 3
		return (error);
D 3
	if (vp->v_type != VREG) {
		VN_RELE(vp);
E 3
I 3
D 6
	vp = ndp -> ni_vp;
E 6
I 6
	vp = nd.ni_vp;
D 20
	VOP_UNLOCK(vp);
E 20
I 20
	VOP_UNLOCK(vp, 0, p);
E 20
E 6
	if (vp -> v_type != VREG) {
		vrele (vp);
E 3
		return (EACCES);
	}
D 3
	if (vp->v_vfsp->vfs_flag & VFS_RDONLY) {
		VN_RELE(vp);
		return (EROFS);
	}
E 3
	pkacctp = vp;
D 3
#else
#ifdef BSD4_3
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = path;
	ip = namei(ndp);
#else
	u.u_dirp = path;
	ip = namei (schar, LOOKUP, 1);
#endif
	if (ip == NULL)
		return (u.u_error);

	if ((ip -> i_mode & IFMT) != IFREG) {
		iput (ip);
		return (EACCES);
	}
	if (pkacctp)
		if (pkacctp->i_number != ip->i_number ||
		    pkacctp->i_dev != ip->i_dev)
			irele(pkacctp);
	pkacctp = ip;
	iunlock (ip);
#endif
E 3
I 3
D 6
	if (oacctp)
		vrele (oacctp);
E 3
	return (0);
}

/* 
 *  Turn off packet accounting
 */

pk_acctoff ()
{
	if (pkacctp) {
D 3
#ifdef NFS
		VN_RELE(pkacctp);
#else
		irele (pkacctp);
#endif
E 3
I 3
		vrele (pkacctp);
E 3
		pkacctp = 0;
E 6
I 6
	if (oacctp) {
	close:
		error = vn_close (oacctp, FWRITE, p -> p_ucred, p);
E 6
	}
I 6
	return (error);
E 6
}

/* 
 *  Write a record on the accounting file.
 */

pk_acct (lcp)
register struct pklcd *lcp;
{
D 3
#ifdef NFS
E 3
	register struct vnode *vp;
D 3
#else
	register struct inode *ip;
	off_t siz;
#endif
E 3
	register struct sockaddr_x25 *sa;
	register char *src, *dst;
	register int len;
D 3
#ifndef WATERLOO
E 3
	register long etime;
D 3
#endif
E 3
	static struct x25acct acbuf;

D 3
#ifdef NFS
E 3
	if ((vp = pkacctp) == 0)
D 3
#else
	if ((ip = pkacctp) == 0)
#endif
E 3
		return;
D 3

E 3
	bzero ((caddr_t)&acbuf, sizeof (acbuf));
	if (lcp -> lcd_ceaddr != 0)
		sa = lcp -> lcd_ceaddr;
	else if (lcp -> lcd_craddr != 0) {
		sa = lcp -> lcd_craddr;
		acbuf.x25acct_callin = 1;
	} else
		return;

	if (sa -> x25_opts.op_flags & X25_REVERSE_CHARGE)
		acbuf.x25acct_revcharge = 1;
	acbuf.x25acct_stime = lcp -> lcd_stime;
D 3
#ifdef WATERLOO
E 3
	acbuf.x25acct_etime = time.tv_sec - acbuf.x25acct_stime;
D 3
#else
	etime = time.tv_sec - acbuf.x25acct_stime;
	acbuf.x25acct_etime = etime > 0xffff ? 0xffff : etime;
#endif
E 3
D 6
	acbuf.x25acct_uid = u.u_uid;
E 6
I 6
	acbuf.x25acct_uid = curproc -> p_cred -> p_ruid;
E 6
	acbuf.x25acct_psize = sa -> x25_opts.op_psize;
	acbuf.x25acct_net = sa -> x25_net;
	/*
	 * Convert address to bcd
	 */
	src = sa -> x25_addr;
	dst = acbuf.x25acct_addr;
	for (len = 0; *src; len++)
		if (len & 01)
			*dst++ |= *src++ & 0xf;
		else
			*dst = *src++ << 4;
	acbuf.x25acct_addrlen = len;

	bcopy (sa -> x25_udata, acbuf.x25acct_udata,
		sizeof (acbuf.x25acct_udata));
	acbuf.x25acct_txcnt = lcp -> lcd_txcnt;
	acbuf.x25acct_rxcnt = lcp -> lcd_rxcnt;

D 3
#ifdef NFS
E 3
	(void) vn_rdwr(UIO_WRITE, vp, (caddr_t)&acbuf, sizeof (acbuf),
D 3
		(off_t)0, UIO_SYSSPACE, IO_UNIT|IO_APPEND, (int *)0);
#else
	ilock (ip);
	siz = ip -> i_size;
	if (rdwri (UIO_WRITE, ip, (caddr_t)&acbuf, sizeof (acbuf),
	    siz, 1, (int *) 0))
		itrunc (ip, (u_long) siz);
	iunlock (ip);
#endif
E 3
I 3
D 5
		(off_t)0, UIO_SYSSPACE, IO_UNIT|IO_APPEND, u.u_cred, (int *)0);
E 5
I 5
D 6
		(off_t)0, UIO_SYSSPACE, IO_UNIT|IO_APPEND, u.u_cred, (int *)0,
E 6
I 6
		(off_t)0, UIO_SYSSPACE, IO_UNIT|IO_APPEND,
		curproc -> p_ucred, (int *)0,
E 6
		(struct proc *)0);
E 5
E 3
}
E 1
