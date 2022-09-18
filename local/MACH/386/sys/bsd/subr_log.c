/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	subr_log.c,v $
 * Revision 2.8  89/03/09  19:30:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  14:45:34  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:32:47  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/23  22:06:09  af
 * 	On Mips, the msgbuf is dynamically allocated.  A quick hack to
 * 	make the existing code look ok.
 * 	[89/01/11            af]
 * 
 * Revision 2.4  89/01/18  00:41:08  jsb
 * 	Fix logioctl so that it returns EINVAL (instead of -1) on error.
 * 	[89/01/16            jsb]
 * 
 * Revision 2.3  88/07/15  15:34:17  mja
 * Add include for "kern/thread.h" on advice from DLB.
 * 
 * 15-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Use a thread (cast to a struct proc * :-() when doing selwakeup.
 *	Problem discovered by David Black.
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)subr_log.c	7.1 (Berkeley) 6/5/86
 */

/*
 * Error log buffer for kernel printf's.
 */

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/msgbuf.h>
#include <sys/file.h>
#include <sys/errno.h>
#include <kern/thread.h>

#ifdef	mips
struct	msgbuf *pmsgbuf;
#define msgbuf	(*pmsgbuf)	/* dynamically allocated on Mips. Sigh */
#else	mips
struct	msgbuf msgbuf;
#endif	mips

#define LOG_RDPRI	(PZERO + 1)

#define LOG_NBIO	0x02
#define LOG_ASYNC	0x04
#define LOG_RDWAIT	0x08

struct logsoftc {
	int	sc_state;		/* see above for possibilities */
	struct	proc *sc_selp;		/* process waiting on select call */
	int	sc_pgrp;		/* process group for async I/O */
} logsoftc;

int	log_open;			/* also used in log() */

/*ARGSUSED*/
logopen(dev)
	dev_t dev;
{

	if (log_open)
		return (EBUSY);
	log_open = 1;
	logsoftc.sc_selp = 0;
	logsoftc.sc_pgrp = u.u_procp->p_pgrp;
	/*
	 * Potential race here with putchar() but since putchar should be
	 * called by autoconf, msg_magic should be initialized by the time
	 * we get here.
	 */
	if (msgbuf.msg_magic != MSG_MAGIC) {
		register int i;

		msgbuf.msg_magic = MSG_MAGIC;
		msgbuf.msg_bufx = msgbuf.msg_bufr = 0;
		for (i=0; i < MSG_BSIZE; i++)
			msgbuf.msg_bufc[i] = 0;
	}
	return (0);
}

/*ARGSUSED*/
logclose(dev, flag)
	dev_t dev;
{
	log_open = 0;
	logsoftc.sc_state = 0;
	logsoftc.sc_selp = 0;
	logsoftc.sc_pgrp = 0;
}

/*ARGSUSED*/
logread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register long l;
	register int s;
	int error = 0;

	s = splhigh();
	while (msgbuf.msg_bufr == msgbuf.msg_bufx) {
		if (logsoftc.sc_state & LOG_NBIO) {
			splx(s);
			return (EWOULDBLOCK);
		}
		logsoftc.sc_state |= LOG_RDWAIT;
		sleep((caddr_t)&msgbuf, LOG_RDPRI);
	}
	splx(s);
	logsoftc.sc_state &= ~LOG_RDWAIT;

	while (uio->uio_resid > 0) {
		l = msgbuf.msg_bufx - msgbuf.msg_bufr;
		if (l < 0)
			l = MSG_BSIZE - msgbuf.msg_bufr;
		l = MIN(l, uio->uio_resid);
		if (l == 0)
			break;
		error = uiomove((caddr_t)&msgbuf.msg_bufc[msgbuf.msg_bufr],
			(int)l, UIO_READ, uio);
		if (error)
			break;
		msgbuf.msg_bufr += l;
		if (msgbuf.msg_bufr < 0 || msgbuf.msg_bufr >= MSG_BSIZE)
			msgbuf.msg_bufr = 0;
	}
	return (error);
}

/*ARGSUSED*/
logselect(dev, rw)
	dev_t dev;
	int rw;
{
	int s = splhigh();

	switch (rw) {

	case FREAD:
		if (msgbuf.msg_bufr != msgbuf.msg_bufx) {
			splx(s);
			return (1);
		}
		logsoftc.sc_selp = (struct proc *) current_thread();
		break;
	}
	splx(s);
	return (0);
}

logwakeup()
{

	if (!log_open)
		return;
	if (logsoftc.sc_selp) {
		selwakeup(logsoftc.sc_selp, 0);
		logsoftc.sc_selp = 0;
	}
	if (logsoftc.sc_state & LOG_ASYNC)
		gsignal(logsoftc.sc_pgrp, SIGIO); 
	if (logsoftc.sc_state & LOG_RDWAIT) {
		wakeup((caddr_t)&msgbuf);
		logsoftc.sc_state &= ~LOG_RDWAIT;
	}
}

/*ARGSUSED*/
logioctl(com, data, flag)
	caddr_t data;
{
	long l;
	int s;

	switch (com) {

	/* return number of characters immediately available */
	case FIONREAD:
		s = splhigh();
		l = msgbuf.msg_bufx - msgbuf.msg_bufr;
		splx(s);
		if (l < 0)
			l += MSG_BSIZE;
		*(off_t *)data = l;
		break;

	case FIONBIO:
		if (*(int *)data)
			logsoftc.sc_state |= LOG_NBIO;
		else
			logsoftc.sc_state &= ~LOG_NBIO;
		break;

	case FIOASYNC:
		if (*(int *)data)
			logsoftc.sc_state |= LOG_ASYNC;
		else
			logsoftc.sc_state &= ~LOG_ASYNC;
		break;

	case TIOCSPGRP:
		logsoftc.sc_pgrp = *(int *)data;
		break;

	case TIOCGPGRP:
		*(int *)data = logsoftc.sc_pgrp;
		break;

	default:
		return EINVAL;
	}
	return (0);
}
