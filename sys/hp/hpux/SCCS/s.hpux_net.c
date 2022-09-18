h60017
s 00020/00019/00248
d D 8.3 95/02/19 08:00:03 cgd 12 11
c proper return types, new names for functions
e
s 00003/00003/00264
d D 8.2 93/09/09 14:46:59 hibler 11 10
c add missing arg to trace routine
e
s 00002/00002/00265
d D 8.1 93/06/10 21:24:40 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00085/00020/00182
d D 7.9 92/12/27 09:06:22 hibler 9 8
c latest Utah version
e
s 00014/00013/00188
d D 7.8 92/10/11 09:01:43 bostic 8 7
c make kernel includes standard
e
s 00002/00005/00199
d D 7.7 91/02/13 19:42:29 mckusick 7 6
c getsock now has three arguments and returns an error
e
s 00001/00001/00203
d D 7.6 90/12/16 22:16:13 mckusick 6 5
c fix include paths
e
s 00013/00013/00191
d D 7.5 90/12/16 16:36:28 bostic 5 4
c kernel reorg
e
s 00007/00007/00197
d D 7.4 90/08/21 23:59:09 karels 4 3
c use 4.3-compat versions of syscalls that pass back sockaddrs
e
s 00014/00012/00190
d D 7.3 90/06/28 19:35:05 karels 3 2
c RETURN => return, remove syscontext.h
e
s 00054/00056/00148
d D 7.2 90/06/22 18:00:58 hibler 2 1
c eliminate use of u_error
e
s 00204/00000/00000
d D 7.1 90/05/08 22:18:40 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 9
 * from: Utah $Hdr: hpux_net.c 1.33 89/08/23$
E 9
I 9
D 11
 * from: Utah $Hdr: hpux_net.c 1.6 92/12/26$
E 11
I 11
 * from: Utah $Hdr: hpux_net.c 1.8 93/08/02$
E 11
E 9
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Network related HP-UX compatibility routines
 */

#ifdef HPUXCOMPAT

D 5
#include "param.h"
#include "systm.h"
D 2
#include "user.h"
E 2
I 2
D 3
#include "syscontext.h"
E 3
E 2
#include "kernel.h"
I 3
#include "time.h"
#include "errno.h"
E 3
#include "proc.h"
#include "file.h"
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
I 3
#include "uio.h"
E 3
#include "ktrace.h"
#include "hpux.h"
E 5
I 5
D 8
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/kernel.h"
#include "sys/time.h"
#include "sys/errno.h"
#include "sys/proc.h"
#include "sys/file.h"
#include "sys/mbuf.h"
#include "sys/socket.h"
#include "sys/socketvar.h"
#include "sys/uio.h"
#include "sys/ktrace.h"
D 6
#include "sys/hpux.h"
E 6
I 6
#include "hpux.h"
E 8
I 8
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/uio.h>
#include <sys/ktrace.h>

#include <hp/hpux/hpux.h>
E 8
E 6
E 5

#define MINBSDIPCCODE	0x3EE
#define NUMBSDIPC	32

/*
 * HPUX netioctl() to BSD syscall map.
 * Indexed by callno - MINBSDIPCCODE
 */
D 4
extern int socket(), listen(), bind(), accept(), connect(), orecv();
extern int osend(), shutdown(), getsockname(), sendto();
extern int recvfrom(), getpeername();
E 4
I 4
D 12
extern int socket(), listen(), bind(), oaccept(), connect(), orecv();
extern int osend(), shutdown(), ogetsockname(), sendto();
extern int orecvfrom(), ogetpeername();
E 12
I 12
extern int socket(), listen(), bind(), compat_43_accept(), connect();
extern int compat_43_recv(), compat_43_send(), shutdown();
extern int compat_43_getsockname(), sendto(), compat_43_recvfrom();
extern int compat_43_getpeername();
E 12
E 4
int hpuxgetsockopt(), hpuxsetsockopt();
D 7
struct file *getsock();
E 7

struct hpuxtobsdipc {
	int (*rout)();
	int nargs;
} hpuxtobsdipc[NUMBSDIPC] = {
D 12
	socket,		3, /* 3ee */	listen,		2, /* 3ef */
D 4
	bind,		3, /* 3f0 */	accept,		3, /* 3f1 */
E 4
I 4
	bind,		3, /* 3f0 */	oaccept,	3, /* 3f1 */
E 4
	connect,	3, /* 3f2 */	orecv,		4, /* 3f3 */
	osend,		4, /* 3f4 */	shutdown,	2, /* 3f5 */
D 4
	getsockname,	3, /* 3f6 */	hpuxsetsockopt,	5, /* 3f7 */
	sendto,		6, /* 3f8 */	recvfrom,	6, /* 3f9 */
	getpeername,	3, /* 3fa */	NULL,		0, /* 3fb */
E 4
I 4
	ogetsockname,	3, /* 3f6 */	hpuxsetsockopt,	5, /* 3f7 */
	sendto,		6, /* 3f8 */	orecvfrom,	6, /* 3f9 */
	ogetpeername,	3, /* 3fa */	NULL,		0, /* 3fb */
E 4
	NULL,		0, /* 3fc */	NULL,		0, /* 3fd */
	NULL,		0, /* 3fe */	NULL,		0, /* 3ff */
	NULL,		0, /* 400 */	NULL,		0, /* 401 */
	NULL,		0, /* 402 */	NULL,		0, /* 403 */
	NULL,		0, /* 404 */	NULL,		0, /* 405 */
	NULL,		0, /* 406 */	NULL,		0, /* 407 */
	NULL,		0, /* 408 */	NULL,		0, /* 409 */
	NULL,		0, /* 40a */	hpuxgetsockopt,	5, /* 40b */
	NULL,		0, /* 40c */	NULL,		0, /* 40d */
E 12
I 12
	socket,		3, /* 3ee */		listen,		2, /* 3ef */
	bind,		3, /* 3f0 */	compat_43_accept,	3, /* 3f1 */
	connect,	3, /* 3f2 */	compat_43_recv,		4, /* 3f3 */
	compat_43_send,		4, /* 3f4 */	shutdown,	2, /* 3f5 */
	compat_43_getsockname,	3, /* 3f6 */	hpuxsetsockopt,	5, /* 3f7 */
	sendto,		6, /* 3f8 */	compat_43_recvfrom,	6, /* 3f9 */
	compat_43_getpeername,	3, /* 3fa */	NULL,		0, /* 3fb */
	NULL,		0, /* 3fc */		NULL,		0, /* 3fd */
	NULL,		0, /* 3fe */		NULL,		0, /* 3ff */
	NULL,		0, /* 400 */		NULL,		0, /* 401 */
	NULL,		0, /* 402 */		NULL,		0, /* 403 */
	NULL,		0, /* 404 */		NULL,		0, /* 405 */
	NULL,		0, /* 406 */		NULL,		0, /* 407 */
	NULL,		0, /* 408 */		NULL,		0, /* 409 */
	NULL,		0, /* 40a */		hpuxgetsockopt,	5, /* 40b */
	NULL,		0, /* 40c */		NULL,		0, /* 40d */
E 12
};

/*
 * Single system call entry to BSD style IPC.
 * Gleened from disassembled libbsdipc.a syscall entries.
 */
I 9
struct hpuxnetioctl_args {
	int	call;
	int	*args;
};
E 9
D 2
hpuxnetioctl()
{
	struct a {
E 2
I 2
hpuxnetioctl(p, uap, retval)
	struct proc *p;
D 9
	struct args {
E 2
		int	call;
		int	*args;
D 2
	} *uap = (struct a *)u.u_ap;
E 2
I 2
	} *uap;
E 9
I 9
	struct hpuxnetioctl_args *uap;
E 9
	int *retval;
{
E 2
	int *args, i;
	register int code;
I 2
	int error;
E 2

	args = uap->args;
	code = uap->call - MINBSDIPCCODE;
D 2
	if (code < 0 || code >= NUMBSDIPC || hpuxtobsdipc[code].rout == NULL) {
		u.u_error = EINVAL;
		return;
	}
E 2
I 2
	if (code < 0 || code >= NUMBSDIPC || hpuxtobsdipc[code].rout == NULL)
D 3
		RETURN (EINVAL);
E 3
I 3
		return (EINVAL);
E 3
E 2
	if ((i = hpuxtobsdipc[code].nargs * sizeof (int)) &&
D 2
	    (u.u_error = copyin((caddr_t)args, (caddr_t)u.u_arg, (u_int)i))) {
E 2
I 2
	    (error = copyin((caddr_t)args, (caddr_t)uap, (u_int)i))) {
E 2
#ifdef KTRACE
D 2
                if (KTRPOINT(u.u_procp, KTR_SYSCALL))
                        ktrsyscall(u.u_procp->p_tracep, code + MINBSDIPCCODE,
E 2
I 2
                if (KTRPOINT(p, KTR_SYSCALL))
                        ktrsyscall(p->p_tracep, code + MINBSDIPCCODE,
E 2
D 11
				   hpuxtobsdipc[code].nargs);
E 11
I 11
				   hpuxtobsdipc[code].nargs, (int *)uap);
E 11
#endif
D 2
		return;
E 2
I 2
D 3
		RETURN (error);
E 3
I 3
		return (error);
E 3
E 2
	}
#ifdef KTRACE
D 2
        if (KTRPOINT(u.u_procp, KTR_SYSCALL))
                ktrsyscall(u.u_procp->p_tracep, code + MINBSDIPCCODE,
E 2
I 2
        if (KTRPOINT(p, KTR_SYSCALL))
                ktrsyscall(p->p_tracep, code + MINBSDIPCCODE,
E 2
D 11
			   hpuxtobsdipc[code].nargs);
E 11
I 11
			   hpuxtobsdipc[code].nargs, (int *)uap);
E 11
#endif
D 2
	(*hpuxtobsdipc[code].rout)();
E 2
I 2
D 3
	RETURN ((*hpuxtobsdipc[code].rout)(p, uap, retval));
E 3
I 3
	return ((*hpuxtobsdipc[code].rout)(p, uap, retval));
E 3
E 2
}

I 9
socksetsize(size, m)
	int size;
	struct mbuf *m;
{
	register int tmp;

	if (size < sizeof(int)) {
		switch(size) {
	    	case 1:
			tmp = (int) *mtod(m, char *);
			break;
	    	case 2:
			tmp = (int) *mtod(m, short *);
			break;
	    	case 3:
			tmp = (((int) *mtod(m, int *)) >> 8) & 0xffffff;
			break;
		}
		*mtod(m, int *) = tmp;
		m->m_len = sizeof(int);
	} else {
		m->m_len = size;
	}
}

struct hpuxsetsockopt_args {
	int	s;
	int	level;
	int	name;
	caddr_t	val;
	int	valsize;
};
/* ARGSUSED */
E 9
D 2
hpuxsetsockopt()
{
	struct a {
E 2
I 2
hpuxsetsockopt(p, uap, retval)
	struct proc *p;
D 9
	struct args {
E 2
		int	s;
		int	level;
		int	name;
		caddr_t	val;
		int	valsize;
D 2
	} *uap = (struct a *)u.u_ap;
E 2
I 2
	} *uap;
E 9
I 9
	struct hpuxsetsockopt_args *uap;
E 9
	int *retval;
{
E 2
	struct file *fp;
	struct mbuf *m = NULL;
D 2
	int tmp;
E 2
I 2
	int tmp, error;
E 2

D 2
	fp = getsock(uap->s);
E 2
I 2
D 7
	fp = getsock(uap->s, &error);
E 2
	if (fp == 0)
E 7
I 7
	if (error = getsock(p->p_fd, uap->s, &fp))
E 7
D 2
		return;
	if (uap->valsize > MLEN) {
		u.u_error = EINVAL;
		return;
	}
E 2
I 2
D 3
		RETURN (error);
E 3
I 3
		return (error);
E 3
	if (uap->valsize > MLEN)
D 3
		RETURN (EINVAL);
E 3
I 3
		return (EINVAL);
E 3
E 2
	if (uap->val) {
		m = m_get(M_WAIT, MT_SOOPTS);
D 2
		if (m == NULL) {
			u.u_error = ENOBUFS;
			return;
		}
		u.u_error =
		    copyin(uap->val, mtod(m, caddr_t), (u_int)uap->valsize);
		if (u.u_error) {
E 2
I 2
		if (m == NULL)
D 3
			RETURN (ENOBUFS);
E 3
I 3
			return (ENOBUFS);
E 3
		if (error = copyin(uap->val, mtod(m, caddr_t),
		    (u_int)uap->valsize)) {
E 2
			(void) m_free(m);
D 2
			return;
E 2
I 2
D 3
			RETURN (error);
E 3
I 3
			return (error);
E 3
E 2
		}
		if (uap->name == SO_LINGER) {
			tmp = *mtod(m, int *);
			mtod(m, struct linger *)->l_onoff = 1;
			mtod(m, struct linger *)->l_linger = tmp;
			m->m_len = sizeof(struct linger);
		} else
D 9
			m->m_len = uap->valsize;
E 9
I 9
			socksetsize(uap->valsize, m);
E 9
	} else if (uap->name == ~SO_LINGER) {
		m = m_get(M_WAIT, MT_SOOPTS);
		if (m) {
			uap->name = SO_LINGER;
			mtod(m, struct linger *)->l_onoff = 0;
			m->m_len = sizeof(struct linger);
		}
	}
D 2
	u.u_error =
	    sosetopt((struct socket *)fp->f_data, uap->level, uap->name, m);
E 2
I 2
D 3
	RETURN (sosetopt((struct socket *)fp->f_data, uap->level,
E 3
I 3
	return (sosetopt((struct socket *)fp->f_data, uap->level,
E 3
	    uap->name, m));
E 2
}

I 9
struct hpuxsetsockopt2_args {
	int	s;
	int	level;
	int	name;
	caddr_t	val;
	int	valsize;
};
/* ARGSUSED */
hpuxsetsockopt2(p, uap, retval)
	struct proc *p;
	register struct hpuxsetsockopt2_args *uap;
	int *retval;
{
	struct file *fp;
	struct mbuf *m = NULL;
	int error;

	if (error = getsock(p->p_fd, uap->s, &fp))
		return (error);
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
		socksetsize(uap->valsize, m);
	}
	return (sosetopt((struct socket *)fp->f_data, uap->level,
	    uap->name, m));
}

struct hpuxgetsockopt_args {
	int	s;
	int	level;
	int	name;
	caddr_t	val;
	int	*avalsize;
};
E 9
D 2
hpuxgetsockopt()
{
	struct a {
E 2
I 2
hpuxgetsockopt(p, uap, retval)
	struct proc *p;
D 9
	struct args {
E 2
		int	s;
		int	level;
		int	name;
		caddr_t	val;
		int	*avalsize;
D 2
	} *uap = (struct a *)u.u_ap;
E 2
I 2
	} *uap;
E 9
I 9
	struct hpuxgetsockopt_args *uap;
E 9
	int *retval;
{
E 2
	struct file *fp;
	struct mbuf *m = NULL;
D 2
	int valsize;
E 2
I 2
	int valsize, error;
E 2

D 2
	fp = getsock(uap->s);
E 2
I 2
D 7
	fp = getsock(uap->s, &error);
E 2
	if (fp == 0)
E 7
I 7
	if (error = getsock(p->p_fd, uap->s, &fp))
E 7
D 2
		return;
E 2
I 2
D 3
		RETURN (error);
E 3
I 3
		return (error);
E 3
E 2
	if (uap->val) {
D 2
		u.u_error = copyin((caddr_t)uap->avalsize, (caddr_t)&valsize,
			sizeof (valsize));
		if (u.u_error)
			return;
E 2
I 2
		if (error = copyin((caddr_t)uap->avalsize, (caddr_t)&valsize,
		    sizeof (valsize)))
D 3
			RETURN (error);
E 3
I 3
			return (error);
E 3
E 2
	} else
		valsize = 0;
D 2
	u.u_error =
	    sogetopt((struct socket *)fp->f_data, uap->level, uap->name, &m);
	if (u.u_error)
E 2
I 2
	if (error = sogetopt((struct socket *)fp->f_data, uap->level,
	    uap->name, &m))
E 2
		goto bad;
	if (uap->val && valsize && m != NULL) {
		if (uap->name == SO_LINGER) {
			if (mtod(m, struct linger *)->l_onoff)
				*mtod(m, int *) = mtod(m, struct linger *)->l_linger;
			else
				*mtod(m, int *) = 0;
			m->m_len = sizeof(int);
		}
		if (valsize > m->m_len)
			valsize = m->m_len;
D 2
		u.u_error = copyout(mtod(m, caddr_t), uap->val, (u_int)valsize);
		if (u.u_error)
			goto bad;
		u.u_error = copyout((caddr_t)&valsize, (caddr_t)uap->avalsize,
		    sizeof (valsize));
E 2
I 2
		error = copyout(mtod(m, caddr_t), uap->val, (u_int)valsize);
		if (error == 0)
			error = copyout((caddr_t)&valsize,
			    (caddr_t)uap->avalsize, sizeof (valsize));
E 2
	}
bad:
	if (m != NULL)
		(void) m_free(m);
I 2
D 3
	RETURN (error);
E 3
I 3
	return (error);
E 3
E 2
}
#endif
E 1
