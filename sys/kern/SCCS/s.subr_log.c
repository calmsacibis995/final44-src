h41885
s 00006/00000/00206
d D 8.3 95/02/14 10:40:01 cgd 29 28
c specify return types.
e
s 00001/00001/00205
d D 8.2 95/01/09 18:22:10 cgd 28 27
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00002/00002/00204
d D 8.1 93/06/10 21:58:19 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00199
d D 7.18 92/10/11 10:38:20 bostic 26 25
c make kernel includes standard
e
s 00001/00000/00205
d D 7.17 92/07/12 17:31:29 pendry 25 24
c need to include systm.h
e
s 00001/00001/00204
d D 7.16 92/07/12 17:20:14 pendry 24 23
c MIN -> min, MAX -> max
e
s 00001/00001/00204
d D 7.15 92/07/07 19:12:09 torek 23 22
c FIONREAD can only return 32-bit size
e
s 00001/00000/00204
d D 7.14 92/05/20 17:37:39 bostic 22 21
c close should return 0
e
s 00004/00007/00200
d D 7.13 92/02/15 21:08:21 mckusick 21 20
c convert to use new select interface, selrecord/selwakeup
e
s 00008/00002/00199
d D 7.12 92/02/05 23:27:57 torek 20 19
c misc cleanups
e
s 00007/00006/00194
d D 7.11 91/03/17 15:41:46 karels 19 18
c more-or-less working with new proc & user structs
e
s 00020/00017/00180
d D 7.10 90/12/05 17:05:06 mckusick 18 17
c update for new VM
e
s 00001/00001/00196
d D 7.9 90/07/26 14:47:24 marc 17 16
c invert sign of negative pgrp
e
s 00001/00000/00196
d D 7.8 90/06/24 19:02:55 mckusick 16 15
c need to include vnode.h
e
s 00015/00019/00181
d D 7.7 90/06/24 16:43:16 karels 15 14
c correct args to logioctl (was missing dev!), don't hold reference
c to pgrp structure (use pgid), use read flag instead of local for non-blocking
e
s 00001/00001/00199
d D 7.6 90/05/17 15:47:04 marc 14 13
c pgsignal take extra argument
e
s 00005/00001/00195
d D 7.5 90/04/05 15:01:48 marc 13 12
c tsleep
e
s 00007/00005/00189
d D 7.4 89/11/20 18:20:44 marc 12 11
c pointer to process group held, (instead of process group id)
e
s 00001/00002/00193
d D 7.3 89/05/09 17:02:33 mckusick 11 10
c merge in vnodes
e
s 00008/00007/00187
d D 7.2 88/10/18 15:14:32 marc 10 9
c posix style job control - new process groups
e
s 00001/00001/00193
d D 7.1 86/06/05 00:06:30 mckusick 9 8
c 4.3BSD release version
e
s 00001/00001/00193
d D 6.8 86/02/23 23:10:06 karels 8 7
c lint
e
s 00008/00048/00186
d D 6.7 86/02/19 17:37:19 karels 7 6
c lint; remove debug
e
s 00004/00001/00230
d D 6.6 85/09/04 13:32:03 bloom 6 5
c lint cleanup
e
s 00007/00001/00224
d D 6.5 85/06/08 14:41:01 mckusick 5 4
c Add copyright
e
s 00007/00003/00218
d D 6.4 85/03/18 15:22:13 karels 4 3
c use separate global for open flag; print logged errors if log isn't 
c open yet; tprintf goes to log also
e
s 00008/00008/00213
d D 6.3 84/08/29 20:20:52 bloom 3 2
c Change to includes.  no more ../h
e
s 00033/00013/00188
d D 6.2 84/07/17 16:19:17 ralph 2 1
c first working version.
e
s 00201/00000/00000
d D 6.1 84/07/16 16:37:55 ralph 1 0
c date and time created 84/07/16 16:37:55 by ralph
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 9
 * Copyright (c) 1982 Regents of the University of California.
E 9
I 9
D 27
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 9
D 18
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
E 18
 *
I 18
 * %sccs.include.redist.c%
 *
E 18
 *	%W% (Berkeley) %G%
 */
E 5

/*
 * Error log buffer for kernel printf's.
 */

D 3
#include "../h/param.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/ioctl.h"
#include "../h/msgbuf.h"
#include "../h/file.h"
#include "../h/errno.h"
E 3
I 3
D 26
#include "param.h"
I 25
#include "systm.h"
E 25
D 11
#include "dir.h"
E 11
D 19
#include "user.h"
E 19
#include "proc.h"
I 16
#include "vnode.h"
E 16
#include "ioctl.h"
#include "msgbuf.h"
#include "file.h"
E 26
I 26
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/ioctl.h>
#include <sys/msgbuf.h>
#include <sys/file.h>
E 26
D 19
#include "errno.h"
E 19
E 3

#define LOG_RDPRI	(PZERO + 1)

D 4
#define LOG_OPEN	0x01
E 4
D 15
#define LOG_NBIO	0x02
E 15
#define LOG_ASYNC	0x04
#define LOG_RDWAIT	0x08

struct logsoftc {
	int	sc_state;		/* see above for possibilities */
D 21
	struct	proc *sc_selp;		/* process waiting on select call */
E 21
I 21
	struct	selinfo sc_selp;	/* process waiting on select call */
E 21
D 10
	int	sc_pgrp;		/* process group for async I/O */
E 10
I 10
D 12
	pid_t	sc_pgid;		/* process group id for async I/O */
E 12
I 12
D 15
	struct	pgrp *sc_pgrp;		/* process group for async I/O */
E 15
I 15
	int	sc_pgid;		/* process/group for async I/O */
E 15
E 12
E 10
} logsoftc;

I 4
int	log_open;			/* also used in log() */

E 4
I 2
D 7
#ifdef LOGDEBUG
/*VARARGS1*/
xprintf(fmt, x1)
	char *fmt;
	unsigned x1;
{

	prf(fmt, &x1, 1, (struct tty *)0);
}
#endif

E 7
I 6
/*ARGSUSED*/
I 29
int
E 29
E 6
E 2
D 19
logopen(dev)
E 19
I 19
logopen(dev, flags, mode, p)
E 19
	dev_t dev;
I 19
	int flags, mode;
	struct proc *p;
E 19
{
I 18
	register struct msgbuf *mbp = msgbufp;
E 18

D 7
#ifdef LOGDEBUG
D 2
	printf("logopen: dev=0x%x\n", dev);
E 2
I 2
	xprintf("logopen: dev=0x%x\n", dev);
E 2
#endif
E 7
D 4
	if (logsoftc.sc_state & LOG_OPEN)
E 4
I 4
	if (log_open)
E 4
D 2
		return(EBUSY);
E 2
I 2
		return (EBUSY);
E 2
D 4
	logsoftc.sc_state |= LOG_OPEN;
E 4
I 4
	log_open = 1;
E 4
D 15
	logsoftc.sc_selp = 0;
D 10
	logsoftc.sc_pgrp = u.u_procp->p_pgrp;
E 10
I 10
D 12
	logsoftc.sc_pgid = u.u_procp->p_pgrp->pg_id;
E 12
I 12
	logsoftc.sc_pgrp = u.u_procp->p_pgrp;
E 15
I 15
D 19
	logsoftc.sc_pgid = u.u_procp->p_pid;	/* signal process only */
E 19
I 19
	logsoftc.sc_pgid = p->p_pid;		/* signal process only */
E 19
E 15
E 12
E 10
	/*
	 * Potential race here with putchar() but since putchar should be
	 * called by autoconf, msg_magic should be initialized by the time
	 * we get here.
	 */
D 18
	if (msgbuf.msg_magic != MSG_MAGIC) {
E 18
I 18
	if (mbp->msg_magic != MSG_MAGIC) {
E 18
		register int i;

D 18
		msgbuf.msg_magic = MSG_MAGIC;
		msgbuf.msg_bufx = msgbuf.msg_bufr = 0;
E 18
I 18
		mbp->msg_magic = MSG_MAGIC;
		mbp->msg_bufx = mbp->msg_bufr = 0;
E 18
		for (i=0; i < MSG_BSIZE; i++)
D 18
			msgbuf.msg_bufc[i] = 0;
E 18
I 18
			mbp->msg_bufc[i] = 0;
E 18
	}
D 2
	return(0);
E 2
I 2
D 7
#ifdef LOGDEBUG
	xprintf("logopen: bufx=%d, bufr=%d\n", msgbuf.msg_bufx, msgbuf.msg_bufr);
#endif
E 7
	return (0);
E 2
}

I 6
/*ARGSUSED*/
I 29
int
E 29
E 6
D 20
logclose(dev, flag)
E 20
I 20
logclose(dev, flag, mode, p)
E 20
	dev_t dev;
I 20
	int flag, mode;
	struct proc *p;
E 20
{
I 21

E 21
I 4
	log_open = 0;
E 4
	logsoftc.sc_state = 0;
I 22
	return (0);
E 22
D 21
	logsoftc.sc_selp = 0;
E 21
D 10
	logsoftc.sc_pgrp = 0;
E 10
I 10
D 12
	logsoftc.sc_pgid = 0;
E 12
I 12
D 15
	logsoftc.sc_pgrp = NULL;
E 15
E 12
E 10
D 7
#ifdef LOGDEBUG
D 2
	printf("logclose: dev=0x%x\n", dev);
E 2
I 2
	xprintf("logclose: dev=0x%x\n", dev);
E 2
#endif
E 7
}

I 6
/*ARGSUSED*/
I 29
int
E 29
E 6
D 15
logread(dev, uio)
E 15
I 15
logread(dev, uio, flag)
E 15
	dev_t dev;
	struct uio *uio;
I 15
	int flag;
E 15
{
I 18
	register struct msgbuf *mbp = msgbufp;
E 18
	register long l;
D 7
	register u_int c;
E 7
D 6
	register struct iovec *iov;
E 6
	register int s;
	int error = 0;

D 7
#ifdef LOGDEBUG
D 2
	printf("logread: dev=0x%x\n", dev);
E 2
I 2
	xprintf("logread: dev=0x%x\n", dev);
E 2
#endif

E 7
	s = splhigh();
D 18
	while (msgbuf.msg_bufr == msgbuf.msg_bufx) {
E 18
I 18
	while (mbp->msg_bufr == mbp->msg_bufx) {
E 18
D 15
		if (logsoftc.sc_state & LOG_NBIO) {
E 15
I 15
		if (flag & IO_NDELAY) {
E 15
			splx(s);
D 2
			return(EWOULDBLOCK);
E 2
I 2
			return (EWOULDBLOCK);
E 2
		}
		logsoftc.sc_state |= LOG_RDWAIT;
D 13
		sleep((caddr_t)&msgbuf, LOG_RDPRI);
E 13
I 13
D 18
		if (error = tsleep((caddr_t)&msgbuf, LOG_RDPRI | PCATCH,
E 18
I 18
		if (error = tsleep((caddr_t)mbp, LOG_RDPRI | PCATCH,
E 18
		    "klog", 0)) {
			splx(s);
			return (error);
		}
E 13
	}
	splx(s);
	logsoftc.sc_state &= ~LOG_RDWAIT;

	while (uio->uio_resid > 0) {
D 18
		l = msgbuf.msg_bufx - msgbuf.msg_bufr;
E 18
I 18
		l = mbp->msg_bufx - mbp->msg_bufr;
E 18
		if (l < 0)
D 18
			l = MSG_BSIZE - msgbuf.msg_bufr;
E 18
I 18
			l = MSG_BSIZE - mbp->msg_bufr;
E 18
D 7
		c = min((u_int) l, (u_int)uio->uio_resid);
I 2
#ifdef LOGDEBUG
		xprintf("logread: bufx=%d, bufr=%d, l=%d, c=%d\n",
			msgbuf.msg_bufx, msgbuf.msg_bufr, l, c);
#endif
		if (c <= 0)
E 7
I 7
D 8
		l = min(l, uio->uio_resid);
E 8
I 8
D 24
		l = MIN(l, uio->uio_resid);
E 24
I 24
		l = min(l, uio->uio_resid);
E 24
E 8
		if (l == 0)
E 7
			break;
E 2
D 18
		error = uiomove((caddr_t)&msgbuf.msg_bufc[msgbuf.msg_bufr],
E 18
I 18
		error = uiomove((caddr_t)&mbp->msg_bufc[mbp->msg_bufr],
E 18
D 7
			(int)c, UIO_READ, uio);
E 7
I 7
D 11
			(int)l, UIO_READ, uio);
E 11
I 11
			(int)l, uio);
E 11
E 7
		if (error)
			break;
D 7
		msgbuf.msg_bufr += c;
E 7
I 7
D 18
		msgbuf.msg_bufr += l;
E 7
		if (msgbuf.msg_bufr < 0 || msgbuf.msg_bufr >= MSG_BSIZE)
			msgbuf.msg_bufr = 0;
E 18
I 18
		mbp->msg_bufr += l;
		if (mbp->msg_bufr < 0 || mbp->msg_bufr >= MSG_BSIZE)
			mbp->msg_bufr = 0;
E 18
	}
D 2
	return(error);
E 2
I 2
	return (error);
E 2
}

I 6
/*ARGSUSED*/
I 29
int
E 29
E 6
D 19
logselect(dev, rw)
E 19
I 19
logselect(dev, rw, p)
E 19
	dev_t dev;
	int rw;
I 19
	struct proc *p;
E 19
{
	int s = splhigh();

	switch (rw) {

	case FREAD:
D 7
		if (msgbuf.msg_bufr != msgbuf.msg_bufx)
			goto win;
#ifdef LOGDEBUG
		if (logsoftc.sc_selp)
D 2
			printf("logselect: collision\n");
E 2
I 2
			xprintf("logselect: collision\n");
E 2
#endif
E 7
I 7
D 18
		if (msgbuf.msg_bufr != msgbuf.msg_bufx) {
E 18
I 18
		if (msgbufp->msg_bufr != msgbufp->msg_bufx) {
E 18
			splx(s);
			return (1);
		}
E 7
D 19
		logsoftc.sc_selp = u.u_procp;
E 19
I 19
D 21
		logsoftc.sc_selp = p;
E 21
I 21
		selrecord(p, &logsoftc.sc_selp);
E 21
E 19
		break;
D 7

	case FWRITE:
#ifdef LOGDEBUG
D 2
		printf("logselect: FWRITE\n");
E 2
I 2
		xprintf("logselect: FWRITE\n");
E 2
#endif
		break;
E 7
	}
	splx(s);
D 2
	return(0);
E 2
I 2
	return (0);
E 2
D 7
win:
	splx(s);
D 2
	return(1);
E 2
I 2
	return (1);
E 7
E 2
}

I 29
void
E 29
logwakeup()
{
I 15
	struct proc *p;
E 15

I 4
	if (!log_open)
		return;
E 4
D 21
	if (logsoftc.sc_selp) {
		selwakeup(logsoftc.sc_selp, 0);
		logsoftc.sc_selp = 0;
	}
E 21
I 21
	selwakeup(&logsoftc.sc_selp);
E 21
D 15
	if (logsoftc.sc_state & LOG_ASYNC)
D 10
		gsignal(logsoftc.sc_pgrp, SIGIO); 
E 10
I 10
D 12
		gsignal(logsoftc.sc_pgid, SIGIO); 
E 12
I 12
D 14
		pgsignal(logsoftc.sc_pgrp, SIGIO); 
E 14
I 14
		pgsignal(logsoftc.sc_pgrp, SIGIO, 0); 
E 15
I 15
	if (logsoftc.sc_state & LOG_ASYNC) {
		if (logsoftc.sc_pgid < 0)
D 17
			gsignal(logsoftc.sc_pgid, SIGIO); 
E 17
I 17
			gsignal(-logsoftc.sc_pgid, SIGIO); 
E 17
		else if (p = pfind(logsoftc.sc_pgid))
			psignal(p, SIGIO);
	}
E 15
E 14
E 12
E 10
	if (logsoftc.sc_state & LOG_RDWAIT) {
D 18
		wakeup((caddr_t)&msgbuf);
E 18
I 18
		wakeup((caddr_t)msgbufp);
E 18
		logsoftc.sc_state &= ~LOG_RDWAIT;
	}
}

/*ARGSUSED*/
I 29
int
E 29
D 15
logioctl(com, data, flag)
E 15
I 15
D 20
logioctl(dev, com, data, flag)
E 20
I 20
logioctl(dev, com, data, flag, p)
	dev_t dev;
D 28
	int com;
E 28
I 28
	u_long com;
E 28
E 20
E 15
	caddr_t data;
I 20
	int flag;
	struct proc *p;
E 20
{
	long l;
	int s;

	switch (com) {

	/* return number of characters immediately available */
	case FIONREAD:
		s = splhigh();
D 18
		l = msgbuf.msg_bufx - msgbuf.msg_bufr;
E 18
I 18
		l = msgbufp->msg_bufx - msgbufp->msg_bufr;
E 18
		splx(s);
		if (l < 0)
			l += MSG_BSIZE;
D 23
		*(off_t *)data = l;
E 23
I 23
		*(int *)data = l;
E 23
		break;

	case FIONBIO:
D 15
		if (*(int *)data)
			logsoftc.sc_state |= LOG_NBIO;
		else
			logsoftc.sc_state &= ~LOG_NBIO;
E 15
		break;

	case FIOASYNC:
		if (*(int *)data)
			logsoftc.sc_state |= LOG_ASYNC;
		else
			logsoftc.sc_state &= ~LOG_ASYNC;
		break;

I 12
D 15
#ifdef notdef	/* XXX remove -- a single open device doesn't need this */
E 12
D 10
	case TIOCSPGRP:
		logsoftc.sc_pgrp = *(int *)data;
E 10
I 10
	case TIOCSPGRP: {
E 15
I 15
	case TIOCSPGRP:
E 15
		logsoftc.sc_pgid = *(int *)data;
E 10
		break;
I 10
D 15
	}
I 12
#endif
E 15
E 12
E 10

	case TIOCGPGRP:
D 10
		*(int *)data = logsoftc.sc_pgrp;
E 10
I 10
D 12
		*(int *)data = logsoftc.sc_pgid;
E 12
I 12
D 15
		*(int *)data = logsoftc.sc_pgrp->pg_id;
E 15
I 15
		*(int *)data = logsoftc.sc_pgid;
E 15
E 12
E 10
		break;

	default:
D 2
		return(-1);
E 2
I 2
		return (-1);
E 2
	}
D 2
	return(0);
E 2
I 2
	return (0);
E 2
}
E 1
