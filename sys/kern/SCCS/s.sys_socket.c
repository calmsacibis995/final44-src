h48448
s 00006/00000/00171
d D 8.3 95/02/14 10:41:09 cgd 30 29
c specify return types.
e
s 00001/00001/00170
d D 8.2 95/01/09 18:22:22 cgd 29 28
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00002/00002/00169
d D 8.1 93/06/10 21:58:49 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00012/00159
d D 7.14 92/10/11 10:38:31 bostic 27 26
c make kernel includes standard
e
s 00008/00005/00163
d D 7.13 92/02/15 21:12:36 mckusick 26 25
c convert to use new select interface, selrecord/selwakeup
e
s 00001/00000/00167
d D 7.12 91/07/17 16:46:08 karels 25 23
c fstat of socket gets mode S_IFSOCK
e
s 00007/00007/00160
d R 7.12 91/06/21 10:42:53 mckusick 24 23
c soo_close now gets pointer to struct socket instead of file pointer
e
s 00003/00002/00164
d D 7.11 91/04/16 00:02:12 mckusick 23 22
c add proc pointer to soo_close
e
s 00002/00004/00164
d D 7.10 91/04/12 18:10:19 karels 22 21
c rm user.h, update includes
e
s 00009/00008/00159
d D 7.9 91/03/17 15:41:26 karels 21 20
c more-or-less working with new proc & user structs
e
s 00001/00011/00166
d D 7.8 90/06/28 21:22:47 bostic 20 19
c new copyright notice
e
s 00007/00002/00170
d D 7.7 90/06/25 11:00:17 karels 19 18
c copy SS_ASYNC to sockbuf
e
s 00005/00006/00167
d D 7.6 90/04/16 08:50:19 karels 18 17
c changed calling convention for sosend/soreceive; use IOCGROUP macro
c for cracking ioctl cmds
e
s 00019/00009/00154
d D 7.5 89/05/09 17:02:41 mckusick 17 16
c merge in vnodes
e
s 00005/00006/00158
d D 7.4 89/04/22 12:26:42 sklower 16 15
c checkpoint for version to be handed to NIST, simple tp4 connection
e
s 00010/00005/00154
d D 7.3 88/06/29 17:18:13 bostic 15 14
c install approved copyright notice
e
s 00009/00003/00150
d D 7.2 88/03/31 15:44:32 bostic 14 13
c add Berkeley specific header
e
s 00001/00001/00152
d D 7.1 86/06/05 00:08:28 mckusick 13 12
c 4.3BSD release version
e
s 00009/00000/00144
d D 6.6 85/09/16 20:52:33 karels 12 11
c allow select on exceptional conditions to notify of urgent data pending;
c connect on connected datagram socket does disconnect first; error status
c socket option
e
s 00007/00001/00137
d D 6.5 85/06/08 14:44:28 mckusick 11 10
c Add copyright
e
s 00001/00001/00137
d D 6.4 85/03/18 15:22:24 karels 10 9
c ifioctl args change
e
s 00012/00012/00126
d D 6.3 84/08/29 20:22:22 bloom 9 8
c Change to includes.  no more ../h
e
s 00000/00006/00138
d D 6.2 84/08/21 10:24:28 karels 8 7
c sostat now does the SENSE
e
s 00000/00000/00144
d D 6.1 83/07/29 06:37:47 sam 7 6
c 4.2 distribution
e
s 00004/00002/00140
d D 4.6 83/07/20 21:31:19 sam 6 5
c guard against null pointers 
e
s 00004/00019/00138
d D 4.5 83/06/13 23:04:19 sam 5 4
c lint and purge non operative locking on sockets
e
s 00018/00034/00139
d D 4.4 83/06/12 19:48:26 sam 4 3
c revamp network ioctls
e
s 00023/00005/00150
d D 4.3 83/06/12 14:30:17 sam 3 2
c cleanup locking a bit; fix problem with close not unlocking
e
s 00004/00000/00151
d D 4.2 83/06/11 00:53:46 sam 2 1
c FIONREAD
e
s 00151/00000/00000
d D 4.1 83/05/27 14:02:53 sam 1 0
c date and time created 83/05/27 14:02:53 by sam
e
u
U
t
T
I 1
D 11
/*	%M%	%I%	%E%	*/
E 11
I 11
/*
D 13
 * Copyright (c) 1982 Regents of the University of California.
E 13
I 13
D 16
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 16
I 16
D 17
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 17
I 17
D 18
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 18
I 18
D 28
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
E 18
E 17
E 16
E 13
D 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
 * All rights reserved.
E 28
I 28
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 28
E 14
 *
I 14
D 20
 * Redistribution and use in source and binary forms are permitted
D 15
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 15
I 15
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 20
I 20
 * %sccs.include.redist.c%
E 20
E 15
 *
E 14
 *	%W% (Berkeley) %G%
 */
E 11

D 9
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/file.h"
#include "../h/mbuf.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/ioctl.h"
#include "../h/uio.h"
#include "../h/stat.h"
E 9
I 9
D 27
#include "param.h"
#include "systm.h"
I 26
#include "proc.h"
E 26
D 17
#include "dir.h"
E 17
D 22
#include "user.h"
E 22
#include "file.h"
#include "mbuf.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "ioctl.h"
D 22
#include "uio.h"
E 22
#include "stat.h"
E 27
I 27
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
E 27
E 9

D 22
#include "../net/if.h"
#include "../net/route.h"
E 22
I 22
D 27
#include "net/if.h"
#include "net/route.h"
E 27
I 27
#include <net/if.h>
#include <net/route.h>
E 27
E 22

D 3
int	soo_rw(), soo_ioctl(), soo_select(), soo_stat(), soo_close();
E 3
I 3
D 17
int	soo_rw(), soo_ioctl(), soo_select(), soo_close();
E 17
I 17
D 23
int	soo_read(), soo_write(), soo_ioctl(), soo_select(), soo_close();
E 23
E 17
E 3
struct	fileops socketops =
D 3
    { soo_rw, soo_ioctl, soo_select, soo_stat, soo_close };
E 3
I 3
D 17
    { soo_rw, soo_ioctl, soo_select, soo_close };
E 17
I 17
    { soo_read, soo_write, soo_ioctl, soo_select, soo_close };
E 17
E 3

D 17
soo_rw(fp, rw, uio)
E 17
I 17
/* ARGSUSED */
I 30
int
E 30
soo_read(fp, uio, cred)
E 17
	struct file *fp;
D 17
	enum uio_rw rw;
E 17
	struct uio *uio;
I 17
	struct ucred *cred;
E 17
{
D 17
	int soreceive(), sosend();
E 17

D 16
	return (
	    (*(rw==UIO_READ?soreceive:sosend))
	      ((struct socket *)fp->f_data, 0, uio, 0, 0));
E 16
I 16
D 17
	return ((*(rw == UIO_READ ? soreceive : sosend))
	      ((struct socket *)fp->f_data, 0, uio, 0, 0, 0));
E 17
I 17
	return (soreceive((struct socket *)fp->f_data, (struct mbuf **)0,
D 18
		uio, (int *)0, (struct mbuf **)0, (struct mbuf **)0));
E 18
I 18
		uio, (struct mbuf **)0, (struct mbuf **)0, (int *)0));
E 18
}

/* ARGSUSED */
I 30
int
E 30
soo_write(fp, uio, cred)
	struct file *fp;
	struct uio *uio;
	struct ucred *cred;
{

	return (sosend((struct socket *)fp->f_data, (struct mbuf *)0,
D 18
		uio, 0, (struct mbuf *)0, (struct mbuf *)0));
E 18
I 18
		uio, (struct mbuf *)0, (struct mbuf *)0, 0));
E 18
E 17
E 16
}

I 30
int
E 30
D 21
soo_ioctl(fp, cmd, data)
E 21
I 21
soo_ioctl(fp, cmd, data, p)
E 21
	struct file *fp;
D 29
	int cmd;
E 29
I 29
	u_long cmd;
E 29
	register caddr_t data;
I 21
	struct proc *p;
E 21
{
	register struct socket *so = (struct socket *)fp->f_data;

	switch (cmd) {

	case FIONBIO:
		if (*(int *)data)
			so->so_state |= SS_NBIO;
		else
			so->so_state &= ~SS_NBIO;
D 4
		break;
E 4
I 4
		return (0);
E 4

	case FIOASYNC:
D 19
		if (*(int *)data)
E 19
I 19
		if (*(int *)data) {
E 19
			so->so_state |= SS_ASYNC;
D 19
		else
E 19
I 19
			so->so_rcv.sb_flags |= SB_ASYNC;
			so->so_snd.sb_flags |= SB_ASYNC;
		} else {
E 19
			so->so_state &= ~SS_ASYNC;
I 19
			so->so_rcv.sb_flags &= ~SB_ASYNC;
			so->so_snd.sb_flags &= ~SB_ASYNC;
		}
E 19
D 4
		break;
E 4
I 4
		return (0);
E 4

I 2
	case FIONREAD:
		*(int *)data = so->so_rcv.sb_cc;
D 4
		break;
E 4
I 4
		return (0);
E 4

E 2
	case SIOCSPGRP:
D 16
		so->so_pgrp = *(int *)data;
E 16
I 16
		so->so_pgid = *(int *)data;
E 16
D 4
		break;
E 4
I 4
		return (0);
E 4

	case SIOCGPGRP:
D 16
		*(int *)data = so->so_pgrp;
E 16
I 16
		*(int *)data = so->so_pgid;
E 16
D 4
		break;
E 4
I 4
		return (0);
E 4

	case SIOCATMARK:
		*(int *)data = (so->so_state&SS_RCVATMARK) != 0;
D 4
		break;

	/* routing table update calls */
	case SIOCADDRT:
	case SIOCDELRT:
		if (!suser())
			return (u.u_error);
		return (rtrequest(cmd, (struct rtentry *)data));

	/* interface parameter requests */
	case SIOCSIFADDR:
	case SIOCSIFFLAGS:
	case SIOCSIFDSTADDR:
		if (!suser())
			return (u.u_error);
		return (ifrequest(cmd, data));

	case SIOCGIFADDR:
	case SIOCGIFFLAGS:
	case SIOCGIFDSTADDR:
		return (ifrequest(cmd, data));

	case SIOCGIFCONF:
		return (ifconf(cmd, data));

	/* type/protocol specific ioctls */
	default:
		return (ENOTTY);		/* XXX */
E 4
I 4
		return (0);
E 4
	}
D 4
	return (0);
E 4
I 4
	/*
	 * Interface/routing/protocol specific ioctls:
	 * interface and routing ioctls should have a
	 * different entry since a socket's unnecessary
	 */
D 18
#define	cmdbyte(x)	(((x) >> 8) & 0xff)
	if (cmdbyte(cmd) == 'i')
E 18
I 18
	if (IOCGROUP(cmd) == 'i')
E 18
D 10
		return (ifioctl(cmd, data));
E 10
I 10
D 21
		return (ifioctl(so, cmd, data));
E 21
I 21
		return (ifioctl(so, cmd, data, p));
E 21
E 10
D 18
	if (cmdbyte(cmd) == 'r')
E 18
I 18
	if (IOCGROUP(cmd) == 'r')
E 18
D 21
		return (rtioctl(cmd, data));
E 21
I 21
		return (rtioctl(cmd, data, p));
E 21
	return ((*so->so_proto->pr_usrreq)(so, PRU_CONTROL, 
	    (struct mbuf *)cmd, (struct mbuf *)data, (struct mbuf *)0));
E 4
}

I 30
int
E 30
D 21
soo_select(fp, which)
E 21
I 21
soo_select(fp, which, p)
E 21
	struct file *fp;
	int which;
I 21
	struct proc *p;
E 21
{
	register struct socket *so = (struct socket *)fp->f_data;
	register int s = splnet();

	switch (which) {

	case FREAD:
		if (soreadable(so)) {
			splx(s);
			return (1);
		}
D 21
		sbselqueue(&so->so_rcv);
E 21
I 21
D 26
		sbselqueue(&so->so_rcv, p);
E 26
I 26
		selrecord(p, &so->so_rcv.sb_sel);
		so->so_rcv.sb_flags |= SB_SEL;
E 26
E 21
		break;

	case FWRITE:
		if (sowriteable(so)) {
			splx(s);
			return (1);
		}
D 21
		sbselqueue(&so->so_snd);
E 21
I 21
D 26
		sbselqueue(&so->so_snd, p);
E 26
I 26
		selrecord(p, &so->so_snd.sb_sel);
		so->so_snd.sb_flags |= SB_SEL;
E 26
E 21
		break;
I 12

	case 0:
D 26
		if (so->so_oobmark ||
		    (so->so_state & SS_RCVATMARK)) {
E 26
I 26
		if (so->so_oobmark || (so->so_state & SS_RCVATMARK)) {
E 26
			splx(s);
			return (1);
		}
D 21
		sbselqueue(&so->so_rcv);
E 21
I 21
D 26
		sbselqueue(&so->so_rcv, p);
E 26
I 26
		selrecord(p, &so->so_rcv.sb_sel);
		so->so_rcv.sb_flags |= SB_SEL;
E 26
E 21
		break;
E 12
	}
	splx(s);
	return (0);
}

I 30
int
E 30
I 5
D 21
/*ARGSUSED*/
E 21
E 5
D 3
soo_stat(fp, ub)
	struct file *fp;
E 3
I 3
soo_stat(so, ub)
	register struct socket *so;
E 3
	register struct stat *ub;
{
D 3
	register struct socket *so = (struct socket *)fp->f_data;
E 3

I 5
D 8
#ifdef lint
	so = so;
#endif
E 8
E 5
	bzero((caddr_t)ub, sizeof (*ub));
I 25
	ub->st_mode = S_IFSOCK;
E 25
D 8
#ifdef notdef
E 8
	return ((*so->so_proto->pr_usrreq)(so, PRU_SENSE,
	    (struct mbuf *)ub, (struct mbuf *)0, 
	    (struct mbuf *)0));
D 8
#endif
	return (0);
E 8
}

D 23
soo_close(fp)
E 23
I 23
/* ARGSUSED */
I 30
int
E 30
soo_close(fp, p)
E 23
	struct file *fp;
I 23
	struct proc *p;
E 23
{
D 6
	int error = soclose((struct socket *)fp->f_data);

E 6
I 6
	int error = 0;
D 14
	
E 14
I 14

E 14
	if (fp->f_data)
		error = soclose((struct socket *)fp->f_data);
E 6
	fp->f_data = 0;
	return (error);
I 3
D 5
}

/*ARGSUSED*/
soo_lock(so, pf, how)
	struct socket *so;
	u_char *pf;
	int how;
{

	return (EOPNOTSUPP);
}

/*ARGSUSED*/
soo_unlock(so, flags)
	struct socket *so;
	int flags;
{

	panic("soo_unlock");
E 5
E 3
}
E 1
