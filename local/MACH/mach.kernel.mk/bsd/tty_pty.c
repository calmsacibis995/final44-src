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
 * Revision 2.15  92/02/11  17:46:28  mja
 * 	     For luna, corrected errno treatment in ptyioctl().
 * 	[92/01/31            jfriedl]
 * 
 * Revision 2.14  91/10/31  22:24:27  mja
 * 	Merge in support for "detached" terminals from the old CMU
 * 	pseudo terminal driver including support for TIOCCSET,
 * 	TIOCCLOG, TIOCCHECK, and TIOCATTACH;  add new TIOCGSLAVE call
 * 	for pseudo terminal.
 * 	[91/10/30  17:58:26  mja]
 * 
 * Revision 2.13  91/04/03  13:03:56  mbj
 * 	Use luna88kdev vs dev.
 * 	[91/04/03            rvb]
 * 	Omron changes[sic]
 * 
 * Revision 2.12  90/08/30  10:59:24  bohman
 * 	Changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.11  90/07/03  16:33:13  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  17:48:05  mrt]
 * 
 * Revision 2.10  89/11/20  11:36:56  mja
 * 	Removed TS_ONDELAY bit from tp->t_state when closing the control
 * 	end.  This prevents dead processes from killing shells which
 * 	reuse the same pty.
 * 	[89/11/15            berman]
 * 
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

#ifdef  luna
#include <luna88kdev/cons.h>
extern struct conssw conssw;
#endif  luna

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
#if	CMU
#define PF_DETACHED	0x8000		/* slave terminal is detached */

/*
 *  Master/slave pair index tables.
 *
 *  The index is the minor device number and the resulting entry is the paired
 *  master or slave associated with the respective slave or master at that
 *  minor device number.
 *
 *  All driver routines called by the master map to their appropriate
 *  pt_ioctl[] structure directly using the supplied minor device number and
 *  map to the pt_tty[] structure of the paired slave indirectly via pttott()
 *  for that minor device.  Similarly, all driver routines called by the slave
 *  map to their appropriate pt_tty[] structure directly using the supplied
 *  minor device number and map to the pt_ioctl[] structure of the paired
 *  master indirectly via tttopt() for that minor device.
 *
 *  These tables are initialized by ptyinit() to pair master and slaves with
 *  the same minor device numbers initially to preserve compatibility with the
 *  old driver.  This pairing may be jumbled later as slaves detach and re-
 *  attach.
 */

struct pt_ioctl *pt_topty[NPTY];
struct tty      *pt_totty[NPTY];

#define	pttott(dev)	(pt_totty[minor(dev)])
#define	tttopt(dev)	(pt_topty[minor(dev)])



/*
 *  Macro used to invoke once-only initialization of data structures in the
 *  master and slave open routines. When the initialization routine is called,
 *  the pointer tested by this macro will be initialized, causing the test to
 *  always fail thereafter.
 */

#define ptyonce()		\
{				\
    if (pt_totty[0] == 0)	\
	ptyinit();		\
}



/*
 *  ptyinit - once-only initialization
 *
 *  Establish the default mappings between the minor devices of the master and
 *  the slave terminal devices and their paired slave terminal and master
 *  devices.
 */

ptyinit()
{
    register int i;

    for (i=0; i<NPTY; i++)
    {
	/*
	 *  The first execution of the following statement fulfills the once-
	 *  only criteria so that this routine will never be invoked again.
	 */
	pt_topty[i] = &pt_ioctl[i];
	pt_totty[i] = &pt_tty[i];
    }
}



#else
/*
 *  Rather than bracket all these references explicitly using the CMU
 *  conditional, they are replaced in-line in the code and expand to either the
 *  standard or CMU behavior accordingly.
 */
#define	pttott(dev)	(&pt_tty[minor(dev)])
#define	tttopt(dev)	(&pt_ioctl[minor(dev)])

#define	ptyonce()	
#endif


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
	ptyonce();
	tp = &pt_tty[minor(dev)];
	if ((tp->t_state & TS_ISOPEN) == 0) {
		ttychars(tp);		/* Set up default chars */
		tp->t_ispeed = tp->t_ospeed = EXTB;
		tp->t_flags = 0;	/* No features (nor raw mode) */
#ifdef  luna
		j_init(tp);
#endif  luna
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

#ifdef  luna
	conssw_reset(dev, conssw.mode); /* console switch reset */
#endif  luna
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
	register struct pt_ioctl *pti = tttopt(dev);
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
	register struct pt_ioctl *pti = tttopt(tp->t_dev);

#if	CMU
	/*
	 *  A login process may exit while detached, thus marking its
	 *  associated terminal as no longer logged-in and consequently
	 *  available for reallocation.  This is the first place we will
	 *  typically find out (via ttylogout()).  It appears to be safe
	 *  to flush the terminal queues at this level so we take care of
	 *  freeing this master/slave pair for the next application here.
	 */
	if ((pti->pt_flags&PF_DETACHED) && (tp->t_state&TS_LOGGEDIN) == 0) {
		ttyflush(tp, (FREAD|FWRITE));
		tp->t_oproc = 0;
		pti->pt_flags &= ~(PF_DETACHED);
	}
#endif
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
	struct pt_ioctl *pti = tttopt(tp->t_dev);

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
	ptyonce();
	tp = pttott(dev);
#if	CMU
	/*
	 *  Require O_EXCL on open to access a master paired with a slave at a
	 *  different minor device number.
	 *
	 *  This allows existing applications using the old assumption that the
	 *  pair mapping is always an identity to continue to operate without
	 *  change since they are extremely unlikely to have been coded to
	 *  include any open flags other than O_RDWR.  Applications which know
	 *  better and use TIOCGSLAVE to perform this mapping specify O_EXCL to
	 *  enable the entire pool of free pairs.
	 */
	if ((flag&O_EXCL) == 0 && tp != &pt_tty[minor(dev)])
		return (EIO);
#endif
	if (tp->t_oproc)
		return (EIO);
	tp->t_oproc = ptsstart;
	(void)(*linesw[tp->t_line].l_modem)(tp, 1);
	tp->t_state |= TS_CARR_ON;
#if	CMU
	tp->t_state &= ~(TS_LOGGEDOUT);
#endif
	pti = &pt_ioctl[minor(dev)];
	pti->pt_flags = 0;
	pti->pt_send = 0;
	pti->pt_ucntl = 0;
#ifdef  luna
	tp->t_omron |= PTY_TTY;
#endif  luna
	return (0);
}

ptcclose(dev)
	dev_t dev;
{
	register struct tty *tp;

	tp = pttott(dev);
#if	CMU
	/*
	 *  If we are logged-in and the slave is marked to disable hang-ups
	 *  on a close, we just become detached instead.  Note that the output
	 *  function pointer is NOT reset even though the master is shutting
	 *  down.  This keeps new applications from opening our master and
	 *  becoming connected to the still active slave.
	 *
	 *  The slave ceases to be detached in one of two ways:
	 *  1)  A TIOCATTACH command from another slave will connect us to
	 *  that master thereby attaching us (and connect that slave to our
	 *  master thereby detaching it);
	 *  2)  The login process of the slave exits clearing TS_LOGGEDIN via
	 *  ttylogout() in the process and notifying us via ptsstart().
	 */
	if ((tp->t_state&TS_LOGGEDIN) && (tp->t_flags&NOHANG)) {
		struct pt_ioctl *pti = &pt_ioctl[minor(dev)];

		tp->t_ttyloc.tlc_ttyid = TLC_DETACH;
		pti->pt_flags |= PF_DETACHED;
		return;
	}
#endif
	/*
	 *  Perform the equivalent of a vhangup() on the slave terminal when
	 *  the control end is closed so that the next process to open it can
	 *  not accidentally attach to some other process left around from
	 *  the previous use.
	 */
	if (tp->t_dev)
		ttydetach(tp->t_dev, tp);
#if	CMU
	tp->t_ttyloc.tlc_hostid = TLC_UNKHOST;
	tp->t_ttyloc.tlc_ttyid = TLC_UNKTTY;
	tp->t_state &= ~(TS_ONDELAY);
#endif	/* CMU */

	(void)(*linesw[tp->t_line].l_modem)(tp, 0);
	tp->t_oproc = 0;		/* mark closed */
#ifdef  luna
	conssw_reset(dev, conssw.mode); /* console switch reset */
#endif  luna
}

ptcread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp = pttott(dev);
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
#if	CMU
		/*
		 *  The paired slave identity may have changed since				 *  we last blocked (i.e. a re-attach).
		 */
		tp = pttott(dev);
#endif
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
#if	CMU
		/*
		 *  Notify the application master that the slave has logged
		 *  out.  This condition is set via ttylogout() when the login
		 *  process associated with this terminal exists and persists
		 *  until the master is closed and re-opened.
		 */
		if (tp->t_state&TS_LOGGEDOUT)
			return (ECONNABORTED);
#endif
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
	struct pt_ioctl *pti = tttopt(tp->t_dev);
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
	register struct tty *tp = pttott(dev);
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
#if	CMU
		/*
		 *  This must also be selectable since it will cause an error
		 *  return in ptcread() when present.
		 */
		if (tp->t_state&TS_LOGGEDOUT)
			return(1);
#endif
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
	register struct tty *tp = pttott(dev);
	register struct iovec *iov;
	register char *cp;
	register int cc = 0;
	char locbuf[BUFSIZ];
	int cnt = 0;
	struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
	int error = 0;

again:
#if	CMU
	/*
	 *  The paired slave identity may have changed since
         *  we last blocked (i.e. a re-attach).
	 */
	tp = pttott(dev);
#endif
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
	register struct tty *tp;
	register struct pt_ioctl *pti;
	int stop, error;
	extern ttyinput();
#ifdef  luna
	struct jtermio jb;
	int s, mode;

	error = 0;
#endif  luna

	/*
	 * IF CONTROLLER STTY THEN MUST FLUSH TO PREVENT A HANG.
	 * ttywflush(tp) will hang if there are characters in the outq.
	 */
	if (cdevsw[major(dev)].d_open == ptcopen) {
		tp = pttott(dev);
		pti = &pt_ioctl[minor(dev)];
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
#if	CMU
		/*
		 *  Provide the minor device number of the slave paired with
		 *  this master.
		 */
		case TIOCGSLAVE:
			*((int *)data) = pttott(dev)-pt_tty;
			return(0);

		case TIOCSLOC:
		case PIOCSLOC:		/* XXX */
		    {
			tp->t_ttyloc.tlc_hostid = ((struct ttyloc *)data)->tlc_hostid;
			tp->t_ttyloc.tlc_ttyid = ((struct ttyloc *)data)->tlc_ttyid;
			return(0);
		    }
#endif	/* CMU */
		}
	} else {
		tp = &pt_tty[minor(dev)];
		pti = tttopt(dev);
	}
#if	CMU
	switch (cmd) {
	/*
	 *  HANGUP process rather than detach on close.
	 */
	case TIOCCSET: /* deprecated - use LNOHANG directly */
	{
	    if (*((int *)data)&CDETHUP)
		tp->t_flags &= ~NOHANG;
	    else
		tp->t_flags |= NOHANG;
	    break;
	}

	/*
	 *  Change logged-in state.
	 */
	case TIOCCLOG:
	{
	    if (!suser())
		return(EPERM);
	    tp->t_flags |= NOHANG; /* implicit reset still needed? -mja */
	    if (*((int *)data))
		tp->t_state |=  TS_LOGGEDIN;
	    else
		tp->t_state &= ~TS_LOGGEDIN;
	    break;
	}

	/*
	 *  Check for or attach to detached slave.
	 */
	case TIOCCHECK:
	case TIOCATTACH:
	{
	    register struct pt_ioctl *dpti;
	    register struct tty *dtp;
	    register int i;

	    /*
	     *  We must be detachable ourself and the target device number must
	     *  be for our device and in range.
	     */
	    i = minor(*((int *)data));
	    if ((tp->t_flags&NOHANG) == 0
	      || major(*((int *)data)) != major(dev) || i < 0 || i >= NPTY)
		return(EINVAL);
	    dpti = tttopt(i);
	    dtp = &pt_tty[i];
	    if (dpti->pt_flags&PF_DETACHED)
	    {
		if (cmd == TIOCATTACH)
		{
		    struct tty xtp;

		    if (!suser())
			return(EPERM);
		    /*
		     *  Pick up the new terminal location from the current
		     *  slave terminal and assign it to the slave terminal
		     *  being attached.  The terminal location for the current
		     *  slave terminal becomes "detached".
		     */
		    dtp->t_ttyloc.tlc_hostid = tp->t_ttyloc.tlc_hostid;
		    dtp->t_ttyloc.tlc_ttyid = tp->t_ttyloc.tlc_ttyid;
		    tp->t_ttyloc.tlc_ttyid = TLC_DETACH;
		    /*
		     *  Swap the slave to master and master to slave mapping
		     *  table entries for the current and detached master and
		     *  slave files.  The current master file is connected to
		     *  the previously detached slave terminal (thereby
		     *  attaching it) and the master file of the detached slave
		     *  is connected to the current slave terminal (thereby
		     *  detaching it).
		     */
		    pt_topty[i] = pti;
		    pt_topty[minor(tp->t_dev)] = dpti; 
		    pt_totty[pti-pt_ioctl] = dtp;
		    pt_totty[dpti-pt_ioctl] = tp;
		    /*
		     *  Swap the slave terminal control state that happens to
		     *  be recorded in the control record.
		     */
		    ;
		    /*
		     *  Swap the pseudo terminal state that happens to be
		     *  recorded in the slave terminal.
		     */
		    xtp.t_oproc = tp->t_oproc;
		    tp->t_oproc = dtp->t_oproc;
		    dtp->t_oproc = xtp.t_oproc;
		    /*
		     *  Nudge the master process which may have been sleeping
		     *  on the old slave terminal queues.
		     */
		    ptcwakeup(tp, FREAD|FWRITE);
		    /*
		     *  Restart output on the newly attached slave terminal.
		     */
		    ptsstart(dtp);
		}
		u.u_r.r_val1 = 1;
	    }
	    return(0);
	    /* can't afford to fall through! */
	}
	}
#endif	/* CMU */
#ifdef  luna
	/* made by OMRON (for Nihongo, console switching ) */
	switch (cmd) {
	case TIOCCONS:
	    if (conssw_set(dev, TIOCNORMAL))
		return(EACCES);
	    error = 0;
	    break;
	case TIOCSETCONS:
	    if (conssw_set(dev, TIOCFORCE))
		return(EACCES);
	    error = 0;
	    break;
	case TIOCRESETCONS:
	    if (conssw_reset(dev, TIOCRESET))
		return(EINVAL);
	    if (tp->t_state & TS_ASLEEP) {
		tp->t_state &= ~TS_ASLEEP;
		wakeup((caddr_t)&tp->t_outq);
	    }
	    error = 0;
	    break;
	case JTERMGET : /* for nihongo */
	    bcopy(&tp->t_jt, data, sizeof(jb));
	    break;
	case JTERMSET : /* for nihongo */
	    s = SPLX();
	    bcopy(data, &tp->t_jt, sizeof(jb));
	    splx(s);
	    break;
	default:
	    error = ttioctl(tp, cmd, data, flag);
/*
	    if(error < 0)
		error = ENOTTY; /* jfriedl@omron -- 90-MAR-10
 90.7.15 KOIZUMI */
	    break;
	}
#endif luna

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

#ifndef luna
	error = ttioctl(tp, cmd, data, flag);
#endif luna
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
#if defined(luna)
	if (error == EINVAL)
#else
	if (error < 0)
#endif
	{
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
#ifdef	__STDC__
	    tp->t_stopc == CTRL('s') && tp->t_startc == CTRL('q');
#else
	    tp->t_stopc == CTRL(s) && tp->t_startc == CTRL(q);
#endif
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
