/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	tty_pty.c,v $
 * Revision 2.9  89/05/03  14:58:25  mikeg
 * 	Fixed the code in ptyioctl so that both Suntools and X will
 * 	run correctly on Sun's.  Had to change code for _N_TIOCSSIZE
 * 	and _N_TIOCGSIZE to use new struct (swsize) defined in
 * 	sys/ioctl.h.  TIOCGSIZE now handled in tty driver.
 * 	[89/04/12  11:54:41  mikeg]
 * 
 * Revision 2.8  89/03/09  19:32:19  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/26  11:27:45  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:33:49  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  88/12/13  13:13:32  mikeg
 * 	Enclosed changes for Suntools in "#ifdef sun"
 * 	conditional.
 * 
 * Revision 2.4  88/12/08  15:35:42  mikeg
 * 	Added code to ptyioctl to support the Sun ioctl's TIOCSSIZE 
 * 	(_N_TIOCSSIZE) and TIOCGSIZE (_N_TIOCGSIZE) in Mach to allow 
 * 	Suntools to run on Mach.
 * 	[88/06/14            mikeg]
 * 
 *
 * 09-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed to call new ttydetach() routine on close of control
 *	side.
 *	[ V5.1(XF23) ]
 *
 * 26-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Oops... select routines really do have to check whether
 *	the thread is waiting.  rsel or wsel could be non-zero from
 *	the last time...
 *
 * 15-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 17-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Adjusted to also accept new general TIOCSLOC call
 *	in anticipation of phasing out special PIOCSLOC call.
 *	[ V5.1(F7) ]
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for multiple threads.
 *
 * 26-Aug-86  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Copy TS_ONDELAY flag from control to slave pty in ptsopen.
 *	Under CMUCS
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 27-Sep-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: Expanded NPTY to (64+16).
 *
 * 14-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Carried over changes below. 
 *	[V1(1)]
 *
 * 21-Apr-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  added support for PIOCSLOC call to set terminal
 *	location from control PTY (V3.06i).
 *
 * 30-Mar-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  added npty definition for cdevsw[] (V3.06h).
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)tty_pty.c	7.1 (Berkeley) 6/5/86
 */

/*
 * Pseudo-teletype Driver
 * (Actually two drivers, requiring two entries in 'cdevsw')
 */
#include <pty.h>

#if	NPTY > 0
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/cmupty.h>

#if	NPTY == 1
#undef	NPTY
#define NPTY	(64+16)		/* crude XXX */
#endif	NPTY == 1

#define BUFSIZ 100		/* Chunk size iomoved to/from user */

/*
 * pts == /dev/tty[pqrs]?
 * ptc == /dev/pty[pqrs]?
 */
struct	tty pt_tty[NPTY];
struct	pt_ioctl {
	int	pt_flags;
	struct	proc *pt_selr, *pt_selw;
	u_char	pt_send;
	u_char	pt_ucntl;
} pt_ioctl[NPTY];
int	npty = NPTY;		/* for pstat -t */

#define PF_RCOLL	0x01
#define PF_WCOLL	0x02
#define PF_NBIO		0x04
#define PF_PKT		0x08		/* packet mode */
#define PF_STOPPED	0x10		/* user told stopped */
#define PF_REMOTE	0x20		/* remote and flow controlled input */
#define PF_NOSTOP	0x40
#define PF_UCNTL	0x80		/* user control mode */


/*ARGSUSED*/
ptsopen(dev, flag)
	dev_t dev;
{
	register struct tty *tp;
	int error;

#ifdef	lint
	npty = npty;
#endif	lint
	if (minor(dev) >= NPTY)
		return (ENXIO);
	tp = &pt_tty[minor(dev)];
	if ((tp->t_state & TS_ISOPEN) == 0) {
		ttychars(tp);		/* Set up default chars */
		tp->t_ispeed = tp->t_ospeed = EXTB;
		tp->t_flags = 0;	/* No features (nor raw mode) */
	} else if (tp->t_state&TS_XCLUDE && u.u_uid != 0)
		return (EBUSY);
	if (tp->t_oproc)			/* Ctrlr still around. */
		tp->t_state |= TS_CARR_ON;
	if (flag & O_NDELAY)	/* Let X work:  Don't wait if O_NDELAY is on. */
		tp->t_state |= TS_ONDELAY;
	else
		while ((tp->t_state & TS_CARR_ON) == 0) {
			tp->t_state |= TS_WOPEN;
			sleep((caddr_t)&tp->t_rawq, TTIPRI);
		}
	error = (*linesw[tp->t_line].l_open)(dev, tp);
	ptcwakeup(tp, FREAD|FWRITE);
	return (error);
}

ptsclose(dev)
	dev_t dev;
{
	register struct tty *tp;

	tp = &pt_tty[minor(dev)];
	(*linesw[tp->t_line].l_close)(tp);
	ttyclose(tp);
	ptcwakeup(tp, FREAD|FWRITE);
}

ptsread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp = &pt_tty[minor(dev)];
	register struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
	int error = 0;

again:
	if (pti->pt_flags & PF_REMOTE) {
		while (tp == u.u_ttyp && u.u_procp->p_pgrp != tp->t_pgrp) {
			if ((u.u_procp->p_sigignore & sigmask(SIGTTIN)) ||
			    (u.u_procp->p_sigmask & sigmask(SIGTTIN)) ||
			    u.u_procp->p_flag&SVFORK)
				return (EIO);
			gsignal(u.u_procp->p_pgrp, SIGTTIN);
			sleep((caddr_t)&lbolt, TTIPRI);
		}
		if (tp->t_canq.c_cc == 0) {
			if (tp->t_state & TS_NBIO)
				return (EWOULDBLOCK);
			sleep((caddr_t)&tp->t_canq, TTIPRI);
			goto again;
		}
		while (tp->t_canq.c_cc > 1 && uio->uio_resid > 0)
			if (ureadc(getc(&tp->t_canq), uio) < 0) {
				error = EFAULT;
				break;
			}
		if (tp->t_canq.c_cc == 1)
			(void) getc(&tp->t_canq);
		if (tp->t_canq.c_cc)
			return (error);
	} else
		if (tp->t_oproc)
			error = (*linesw[tp->t_line].l_read)(tp, uio);
	ptcwakeup(tp, FWRITE);
	return (error);
}

/*
 * Write to pseudo-tty.
 * Wakeups of controlling tty will happen
 * indirectly, when tty driver calls ptsstart.
 */
ptswrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp;

	tp = &pt_tty[minor(dev)];
	if (tp->t_oproc == 0)
		return (EIO);
	return ((*linesw[tp->t_line].l_write)(tp, uio));
}

/*
 * Start output on pseudo-tty.
 * Wake up process selecting or sleeping for input from controlling tty.
 */
ptsstart(tp)
	struct tty *tp;
{
	register struct pt_ioctl *pti = &pt_ioctl[minor(tp->t_dev)];

	if (tp->t_state & TS_TTSTOP)
		return;
	if (pti->pt_flags & PF_STOPPED) {
		pti->pt_flags &= ~PF_STOPPED;
		pti->pt_send = TIOCPKT_START;
	}
	ptcwakeup(tp, FREAD);
}

ptcwakeup(tp, flag)
	struct tty *tp;
{
	struct pt_ioctl *pti = &pt_ioctl[minor(tp->t_dev)];

	if (flag & FREAD) {
		if (pti->pt_selr) {
			selwakeup(pti->pt_selr, pti->pt_flags & PF_RCOLL);
			pti->pt_selr = 0;
			pti->pt_flags &= ~PF_RCOLL;
		}
		wakeup((caddr_t)&tp->t_outq.c_cf);
	}
	if (flag & FWRITE) {
		if (pti->pt_selw) {
			selwakeup(pti->pt_selw, pti->pt_flags & PF_WCOLL);
			pti->pt_selw = 0;
			pti->pt_flags &= ~PF_WCOLL;
		}
		wakeup((caddr_t)&tp->t_rawq.c_cf);
	}
}

/*ARGSUSED*/
ptcopen(dev, flag)
	dev_t dev;
	int flag;
{
	register struct tty *tp;
	struct pt_ioctl *pti;

	if (minor(dev) >= NPTY)
		return (ENXIO);
	tp = &pt_tty[minor(dev)];
	if (tp->t_oproc)
		return (EIO);
	tp->t_oproc = ptsstart;
	(void)(*linesw[tp->t_line].l_modem)(tp, 1);
	tp->t_state |= TS_CARR_ON;
	pti = &pt_ioctl[minor(dev)];
	pti->pt_flags = 0;
	pti->pt_send = 0;
	pti->pt_ucntl = 0;
	return (0);
}

ptcclose(dev)
	dev_t dev;
{
	register struct tty *tp;

	tp = &pt_tty[minor(dev)];
	/*
	 *  Perform the equivalent of a vhangup() on the slave terminal when
	 *  the control end is closed so that the next process to open it can
	 *  not accidentally attach to some other process left around from
	 *  the previous use.
	 */
	if (tp->t_dev)
		ttydetach(tp->t_dev, tp);
#ifdef	CMUCS
	tp->t_ttyloc.tlc_hostid = TLC_UNKHOST;
	tp->t_ttyloc.tlc_ttyid = TLC_UNKTTY;
#endif	CMUCS
	(void)(*linesw[tp->t_line].l_modem)(tp, 0);
	tp->t_oproc = 0;		/* mark closed */
}

ptcread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp = &pt_tty[minor(dev)];
	struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
	char buf[BUFSIZ];
	int error = 0, cc;

	/*
	 * We want to block until the slave
	 * is open, and there's something to read;
	 * but if we lost the slave or we're NBIO,
	 * then return the appropriate error instead.
	 */
	for (;;) {
		if (tp->t_state&TS_ISOPEN) {
			if (pti->pt_flags&PF_PKT && pti->pt_send) {
				error = ureadc((int)pti->pt_send, uio);
				if (error)
					return (error);
				pti->pt_send = 0;
				return (0);
			}
			if (pti->pt_flags&PF_UCNTL && pti->pt_ucntl) {
				error = ureadc((int)pti->pt_ucntl, uio);
				if (error)
					return (error);
				pti->pt_ucntl = 0;
				return (0);
			}
			if (tp->t_outq.c_cc && (tp->t_state&TS_TTSTOP) == 0)
				break;
		}
		if ((tp->t_state&TS_CARR_ON) == 0)
			return (EIO);
		if (pti->pt_flags&PF_NBIO)
			return (EWOULDBLOCK);
		sleep((caddr_t)&tp->t_outq.c_cf, TTIPRI);
	}
	if (pti->pt_flags & (PF_PKT|PF_UCNTL))
		error = ureadc(0, uio);
	while (uio->uio_resid > 0 && error == 0) {
		cc = q_to_b(&tp->t_outq, buf, MIN(uio->uio_resid, BUFSIZ));
		if (cc <= 0)
			break;
		error = uiomove(buf, cc, UIO_READ, uio);
	}
	if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
	}
	return (error);
}

ptsstop(tp, flush)
	register struct tty *tp;
	int flush;
{
	struct pt_ioctl *pti = &pt_ioctl[minor(tp->t_dev)];
	int flag;

	/* note: FLUSHREAD and FLUSHWRITE already ok */
	if (flush == 0) {
		flush = TIOCPKT_STOP;
		pti->pt_flags |= PF_STOPPED;
	} else
		pti->pt_flags &= ~PF_STOPPED;
	pti->pt_send |= flush;
	/* change of perspective */
	flag = 0;
	if (flush & FREAD)
		flag |= FWRITE;
	if (flush & FWRITE)
		flag |= FREAD;
	ptcwakeup(tp, flag);
}

ptcselect(dev, rw)
	dev_t dev;
	int rw;
{
	register struct tty *tp = &pt_tty[minor(dev)];
	struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
	int s;

	if ((tp->t_state&TS_CARR_ON) == 0)
		return (1);
	switch (rw) {

	case FREAD:
		/*
		 * Need to block timeouts (ttrstart).
		 */
		s = spltty();
		if ((tp->t_state&TS_ISOPEN) &&
		     tp->t_outq.c_cc && (tp->t_state&TS_TTSTOP) == 0) {
			splx(s);
			return (1);
		}
		splx(s);
		/* FALLTHROUGH */

	case 0:					/* exceptional */
		if ((tp->t_state&TS_ISOPEN) &&
		    (pti->pt_flags&PF_PKT && pti->pt_send ||
		     pti->pt_flags&PF_UCNTL && pti->pt_ucntl))
			return (1);
		if (pti->pt_selr &&
			((thread_t)(pti->pt_selr))->wait_event
				== (int)&selwait)
			pti->pt_flags |= PF_RCOLL;
		else
			pti->pt_selr = (struct proc *) current_thread();
		break;


	case FWRITE:
		if (tp->t_state&TS_ISOPEN) {
			if (pti->pt_flags & PF_REMOTE) {
			    if (tp->t_canq.c_cc == 0)
				return (1);
			} else {
			    if (tp->t_rawq.c_cc + tp->t_canq.c_cc < TTYHOG-2)
				    return (1);
			    if (tp->t_canq.c_cc == 0 &&
			        (tp->t_flags & (RAW|CBREAK)) == 0)
				    return (1);
			}
		}
		if (pti->pt_selw &&
			((thread_t)(pti->pt_selw))->wait_event
				== (int)&selwait)
			pti->pt_flags |= PF_WCOLL;
		else
			pti->pt_selw = (struct proc *) current_thread();
		break;

	}
	return (0);
}

ptcwrite(dev, uio)
	dev_t dev;
	register struct uio *uio;
{
	register struct tty *tp = &pt_tty[minor(dev)];
	register struct iovec *iov;
	register char *cp;
	register int cc = 0;
	char locbuf[BUFSIZ];
	int cnt = 0;
	struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
	int error = 0;

again:
	if ((tp->t_state&TS_ISOPEN) == 0)
		goto block;
	if (pti->pt_flags & PF_REMOTE) {
		if (tp->t_canq.c_cc)
			goto block;
		while (uio->uio_iovcnt > 0 && tp->t_canq.c_cc < TTYHOG - 1) {
			iov = uio->uio_iov;
			if (iov->iov_len == 0) {
				uio->uio_iovcnt--;	
				uio->uio_iov++;
				continue;
			}
			if (cc == 0) {
				cc = MIN(iov->iov_len, BUFSIZ);
				cc = MIN(cc, TTYHOG - 1 - tp->t_canq.c_cc);
				cp = locbuf;
				error = uiomove(cp, cc, UIO_WRITE, uio);
				if (error)
					return (error);
				/* check again for safety */
				if ((tp->t_state&TS_ISOPEN) == 0)
					return (EIO);
			}
			if (cc)
				(void) b_to_q(cp, cc, &tp->t_canq);
			cc = 0;
		}
		(void) putc(0, &tp->t_canq);
		ttwakeup(tp);
		wakeup((caddr_t)&tp->t_canq);
		return (0);
	}
	while (uio->uio_iovcnt > 0) {
		iov = uio->uio_iov;
		if (cc == 0) {
			if (iov->iov_len == 0) {
				uio->uio_iovcnt--;	
				uio->uio_iov++;
				continue;
			}
			cc = MIN(iov->iov_len, BUFSIZ);
			cp = locbuf;
			error = uiomove(cp, cc, UIO_WRITE, uio);
			if (error)
				return (error);
			/* check again for safety */
			if ((tp->t_state&TS_ISOPEN) == 0)
				return (EIO);
		}
		while (cc > 0) {
			if ((tp->t_rawq.c_cc + tp->t_canq.c_cc) >= TTYHOG - 2 &&
			   (tp->t_canq.c_cc > 0 ||
			      tp->t_flags & (RAW|CBREAK))) {
				wakeup((caddr_t)&tp->t_rawq);
				goto block;
			}
			(*linesw[tp->t_line].l_rint)(*cp++, tp);
			cnt++;
			cc--;
		}
		cc = 0;
	}
	return (0);
block:
	/*
	 * Come here to wait for slave to open, for space
	 * in outq, or space in rawq.
	 */
	if ((tp->t_state&TS_CARR_ON) == 0)
		return (EIO);
	if (pti->pt_flags & PF_NBIO) {
		iov->iov_base -= cc;
		iov->iov_len += cc;
		uio->uio_resid += cc;
		uio->uio_offset -= cc;
		if (cnt == 0)
			return (EWOULDBLOCK);
		return (0);
	}
	sleep((caddr_t)&tp->t_rawq.c_cf, TTOPRI);
	goto again;
}

/*ARGSUSED*/
ptyioctl(dev, cmd, data, flag)
	caddr_t data;
	dev_t dev;
{
	register struct tty *tp = &pt_tty[minor(dev)];
	register struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
	int stop, error;
	extern ttyinput();

	/*
	 * IF CONTROLLER STTY THEN MUST FLUSH TO PREVENT A HANG.
	 * ttywflush(tp) will hang if there are characters in the outq.
	 */
	if (cdevsw[major(dev)].d_open == ptcopen)
		switch (cmd) {

		case TIOCPKT:
			if (*(int *)data) {
				if (pti->pt_flags & PF_UCNTL)
					return (EINVAL);
				pti->pt_flags |= PF_PKT;
			} else
				pti->pt_flags &= ~PF_PKT;
			return (0);

		case TIOCUCNTL:
			if (*(int *)data) {
				if (pti->pt_flags & PF_PKT)
					return (EINVAL);
				pti->pt_flags |= PF_UCNTL;
			} else
				pti->pt_flags &= ~PF_UCNTL;
			return (0);

		case TIOCREMOTE:
			if (*(int *)data)
				pti->pt_flags |= PF_REMOTE;
			else
				pti->pt_flags &= ~PF_REMOTE;
			ttyflush(tp, FREAD|FWRITE);
			return (0);

		case FIONBIO:
			if (*(int *)data)
				pti->pt_flags |= PF_NBIO;
			else
				pti->pt_flags &= ~PF_NBIO;
			return (0);

		case TIOCSETP:
		case TIOCSETN:
		case TIOCSETD:
			while (getc(&tp->t_outq) >= 0)
				;
			break;
#ifdef	CMUCS
		case TIOCSLOC:
		case PIOCSLOC:		/* XXX */
		    {
			tp->t_ttyloc.tlc_hostid = ((struct ttyloc *)data)->tlc_hostid;
			tp->t_ttyloc.tlc_ttyid = ((struct ttyloc *)data)->tlc_ttyid;
			return(0);
		    }
#endif	CMUCS
		}

#ifdef	sun	/* Yes, this is a property of SunOS */

/*
 * The following code was added in order to allow Suntools to run under Mach. 
 * Note that TIOCSSIZE has the same ioctl number as _O_TIOCSSIZE and 
 * TIOCSWINSZ.  Thus a call specifying any of these ioctl's will be 
 * handled here.
 */
	switch (cmd) {

	case TIOCSSIZE:	/* This isn't very pretty, but what driver is? */
		/*
		 * Check to make sure this is not a TIOCSWINSZ which has
		 * the same ioctl number.  We distinguish between the two
		 * by examining the "ts_lines" field in the ttysize structure.
		 * If the upper 16 bits of this field are non-zero, we assume
		 * it is a TIOCSWINSZ. TIOCSWINSZ is handled by the regular 
		 * tty driver.
		 */
		if ((((struct swsize *)data)->ts_lines&0xffff0000) != 0)
			break;

	case _N_TIOCSSIZE:
		tp->t_winsize.ws_row = ((struct swsize *)data)->ts_lines;
		tp->t_winsize.ws_col = ((struct swsize *)data)->ts_cols;
		return (0);

	/*
	 * There is no way to distinguish between a real TIOCGSIZE as 
	 * in SunOS and the 4.3 TIOCGWINSZ since the kluge used above 
	 * can't be used (we don't know what the user is doing).  We'll
	 * assume that it's a TIOCGWINSZ and punt to the tty driver.
	 */
	case _N_TIOCGSIZE:
		((struct swsize *)data)->ts_lines = tp->t_winsize.ws_row;
		((struct swsize *)data)->ts_cols = tp->t_winsize.ws_col;
		return (0);
        }

#endif	sun

	error = ttioctl(tp, cmd, data, flag);
	/*
	 * Since we use the tty queues internally,
	 * pty's can't be switched to disciplines which overwrite
	 * the queues.  We can't tell anything about the discipline
	 * from here...
	 */
	if (linesw[tp->t_line].l_rint != ttyinput) {
		(*linesw[tp->t_line].l_close)(tp);
		tp->t_line = 0;
		(void)(*linesw[tp->t_line].l_open)(dev, tp);
		error = ENOTTY;
	}
	if (error < 0) {
		if (pti->pt_flags & PF_UCNTL &&
		    (cmd & ~0xff) == UIOCCMD(0)) {
			if (cmd & 0xff) {
				pti->pt_ucntl = (u_char)cmd;
				ptcwakeup(tp, FREAD);
			}
			return (0);
		}
		error = ENOTTY;
	}
	stop = (tp->t_flags & RAW) == 0 &&
	    tp->t_stopc == CTRL(s) && tp->t_startc == CTRL(q);
	if (pti->pt_flags & PF_NOSTOP) {
		if (stop) {
			pti->pt_send &= ~TIOCPKT_NOSTOP;
			pti->pt_send |= TIOCPKT_DOSTOP;
			pti->pt_flags &= ~PF_NOSTOP;
			ptcwakeup(tp, FREAD);
		}
	} else {
		if (!stop) {
			pti->pt_send &= ~TIOCPKT_DOSTOP;
			pti->pt_send |= TIOCPKT_NOSTOP;
			pti->pt_flags |= PF_NOSTOP;
			ptcwakeup(tp, FREAD);
		}
	}
	return (error);
}
#endif	NPTY > 0
