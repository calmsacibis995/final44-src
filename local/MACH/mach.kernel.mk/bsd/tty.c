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
 * $Log:	tty.c,v $
 * Revision 2.16  91/04/03  13:02:43  mbj
 * 	Omron changes[sic]
 * 
 * Revision 2.15  90/08/30  10:59:17  bohman
 * 	Ioctl changes for STDC.  Other changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.14  90/07/05  17:19:04  mrt
 * 	Restored return of -1 in ttioctl().  This indicates to the device 
 * 	driver that the tty driver is incapable of doing the ioctl at
 * 	this level.
 * 	[90/04/17            berman]
 * 
 * Revision 2.13  90/07/03  16:32:50  mrt
 * 	Define CMUVCONS if CMUCS is defined.
 * 	[90/06/25            mrt]
 * 
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  17:46:38  mrt]
 * 
 * Revision 2.12  89/08/23  16:20:07  berman
 * 	Changed ttwrite_xcons() to call original console write routine
 * 	(*xcons_write)()  when the minor device is non zero.  This
 * 	prevents redirection of second display's output on 
 * 		multiple display vaxen.
 * 	[89/07/06            berman]
 * 
 * Revision 2.11  89/05/30  10:36:01  rvb
 * 	Removed a typo that upset an uppity compiler.
 * 	[89/05/15            af]
 * 
 * Revision 2.10  89/03/09  19:31:37  rpd
 * 	More cleanup.
 * 
 * Revision 2.9  89/02/26  11:25:10  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.8  89/02/09  04:33:26  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.7  89/01/30  22:02:58  rpd
 * 	Added declaration of selwait.  (The one in sys/systm.h is extern now.)
 * 	[89/01/25  14:52:22  rpd]
 * 
 * Revision 2.6  89/01/18  00:42:13  jsb
 * 	Fix ttioctl so that it returns EINVAL (instead of -1) on error.
 * 	[89/01/16            jsb]
 * 
 * Revision 2.5  88/08/22  21:26:39  mja
 * 	Add TIOCVCONS and TIOCGCONS calls for two-way handling of
 * 	virtual console redirection and to provide some minimal
 * 	authorization; add new ttyvcons() routine which implements
 * 	these calls in common with their internal counterparts;  return
 * 	ENXIO for no control terminal and EACCES rather than EINVAL for
 * 	non-control terminal in TIOCLOGINDEV call; make TIOCSPGRP do an
 * 	implict TIOCVCONS_ASSIGN for now; flush obsolete TIOCSCONS call
 * 	(still implemented as _IO(t,104) for a transition period).
 * 	[88/08/08  15:37:06  mja]
 * 
 * Revision 2.4  88/07/15  15:36:11  mja
 * Correct to clear virtual console in tty_detach() rather than
 * ttyclose(); fix to virtual console redirect all devices with
 * same d_write routine as the device in the console slot (e.g.
 * micro-Vax QVSS); eliminate super-user override of virtual
 * console for now since previous check was inadequate; fix
 * ttwrite_xcons() to dispatch through line discipline.
 * 
 * 13-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Restored call to ttstart() in ttylogout() so that any pty
 *	controller is notified about the state change immediately.
 *	[ V5.1(XF24) ]
 *
 * 09-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created new ttydetach() routine; altered ttyopen() to restrict
 *	new controlling terminal changes somewhat.
 *	[ V5.1(XF23) ]
 *
 *  8-Mar-88  David Golub (dbg) at Carnegie-Mellon University
 *	Fixed ttyretype - it was assuming that t_rprntc was an
 *	unsigned character.
 *
 * 29-Jan-88  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Corrected setting of cons_tp in ttyclose().
 *
 * 10-Nov-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Implement TIOCCONS for all machines using new
 *	`xcons_tp' pointer and machine independent redirection at the
 *	ttwrite() level (superceding old semi-implemented `cons_tp'
 *	version which can no longer be directly invoked since TIOCCONS
 *	now controls only the new implementation).
 *	[ V5.1(XF21) ]
 *
 * 30-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Corrected unsigned character problem in ttbreakc() on the RT.
 *	[ V5.1(XF20) ]
 *
 * 27-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: select routines really do have to check whether the
 *	thread is waiting.  Pointer to select()'ing thread could be
 *	non-zero from the last time a select was done.
 *
 * 17-Jun-87  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added several 'spltty's around code which must atomically
 *	set and clear bits in memory, since some machines don't
 *	have instructions for this.  Intentionally neglected to
 *	include CS_BUGFIX conditionals, as they would have been
 *	excessively ugly.
 *
 *  1-Apr-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Well, dynix code thinks NTTYDISC is 1 and we think it is 2.  So
 *	amuse dynix for now.
 *
 *  5-Mar-87  David L. Black (dlb) at Carnegie-Mellon University
 *	Can't switch consoles on Multimax.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merge VICE changes -- include vice.h and change to #if VICE.
 *	Also, merged VICE & ibmrt versions of tty console switching code.
 *	This should be made slightly more general so as to work on all
 *	machines.  It shouldn't even be that much work.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for multiple threads.
 *
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Implement common TIOCCLOG call (still used
 *	independently by drivers for now); added TIOCLOGINDEV call to
 *	make a terminal the login terminal for the current process and
 *	a new ttylogout() routine called by exit() when the process
 *	goes away so that the appropriate terminal driver can be
 *	notified.
 *	[ V5.1(F1) ]
 *
 * 29-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  restored handling of (ITC) 4.2 TIOCSCONS as it is
 *	required by the Andrew console program.
 *
 * 27-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: Fixed to only set terminal location for terminal
 *	on first open if the host ID part has yet to be set.  This
 *	allows locations set by the controller of a pseudo terminal to
 *	override the default which doesn't really apply well to them.
 *	This whole scheme still needs some work...
 *	[ V5.1(F1) ]
 *
 * 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	Add #include cputypes.h for BALANCE definition.
 *	Add tpselect() for driver that passes in its own struct tty pointer
 *	(under #ifdef BALANCE).
 *	ttselect() should be defined in terms of tpselect().
 *
 * 24-Dec-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	ibmrt: added changes from ACIS for RT cons_tp variable support.
 *
 * 24-Nov-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  added terminal location initialization to
 *	ttyopen() in the hope of moving it out of the individual device
 *	drivers in the future, for now only the DMZ-32 driver is
 *	affected.
 *	[ V5.1(F1) ]
 *
 * 26-Aug-86  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Have ttsread and ttwrite look at TS_ONDELAY if TS_CARR_ON
 *	is off and if state is not TS_NBIO sleep for the carrier
 *	transition.  Under CMUCS flag.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 28-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Fix ttwrite() to avoid dead-lock when output
 *	routine (such as in the QVSS driver) completely drains the
 *	output queue (below the high water mark) before it returns.
 *	[V1(1)]
 *
 * 16-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.  Carried over changes below.
 *	[V1(1)]
 *
 * 10-Nov-84  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Changed not to echo any control characters
 *	rather than just the escape character (fix courtesy of Brad
 *	White) (V3.07l).
 *
 * 28-Mar-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Added TIOCGLOC call to return terminal location
 *	information (V3.06h).
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)tty.c	7.1 (Berkeley) 6/5/86
 */

#include <cputypes.h>
#include <vice.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/proc.h>
#include <sys/inode.h>
#include <sys/file.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/dk.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <machine/reg.h>

#ifdef CMUCS
#define CMUVCONS
#endif /* CMUCS */

short	tthiwat[NSPEEDS], ttlowat[NSPEEDS];

int selwait;

/*
 *  Console terminal ouptut redirect
 */
int	    XCONS_MAJDEV = 0;		/* physical console device number */
uid_t	    xcons_uid = TIOCGCONS_NOUID;/* console owner (for redirect check) */
struct tty *xcons_tp = 0;		/* redirected console pointer */
int       (*xcons_write)();		/* physical console write routine */
extern int ttwrite_xcons();

#ifdef  luna
ushort g_sjis[SJISGAS];         /* sift JIS gaiji address table */
#endif  luna

/*
 * Table giving parity for characters and indicating
 * character classes to tty driver.  In particular,
 * if the low 6 bits are 0, then the character needs
 * no special processing on output.
 */

char partab[] = {
	0001,0201,0201,0001,0201,0001,0001,0201,
	0202,0004,0003,0201,0005,0206,0201,0001,
	0201,0001,0001,0201,0001,0201,0201,0001,
	0001,0201,0201,0001,0201,0001,0001,0201,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0201,

	/*
	 * 7 bit ascii ends with the last character above,
	 * but we contine through all 256 codes for the sake
	 * of the tty output routines which use special vax
	 * instructions which need a 256 character trt table.
	 */

	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007
};

/*
 * Input mapping table-- if an entry is non-zero, when the
 * corresponding character is typed preceded by "\" the escape
 * sequence is replaced by the table value.  Mostly used for
 * upper-case only terminals.
 */
char	maptab[] ={
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,'|',000,000,000,000,000,'`',
	'{','}',000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,'~',000,
	000,'A','B','C','D','E','F','G',
	'H','I','J','K','L','M','N','O',
	'P','Q','R','S','T','U','V','W',
	'X','Y','Z',000,000,000,000,000,
};

short	tthiwat[16] =
   { 100,100,100,100,100,100,100,200,200,400,400,400,650,650,1300,2000 };
short	ttlowat[16] =
   {  30, 30, 30, 30, 30, 30, 30, 50, 50,120,120,120,125,125,125,125 };

struct	ttychars ttydefaults = {
	CERASE,	CKILL,	CINTR,	CQUIT,	CSTART,	CSTOP,	CEOF,
	CBRK,	CSUSP,	CDSUSP, CRPRNT, CFLUSH, CWERASE,CLNEXT
};

#ifdef luna
#define KANJI   1
#define GAIJI   2
#define JEND    8
#endif luna
ttychars(tp)
	struct tty *tp;
{

	tp->t_chars = ttydefaults;
}

/*
 * Wait for output to drain, then flush input waiting.
 */
ttywflush(tp)
	register struct tty *tp;
{

	ttywait(tp);
	ttyflush(tp, FREAD);
}

ttywait(tp)
	register struct tty *tp;
{
	register int s = spltty();

	while ((tp->t_outq.c_cc || tp->t_state&TS_BUSY) &&
#ifdef	ibmrt
	    tp->t_state&TS_CARR_ON && tp->t_oproc)	/* kludge for pty */
#else	ibmrt
	    tp->t_state&TS_CARR_ON)
#endif	ibmrt
	{
		(*tp->t_oproc)(tp);
		tp->t_state |= TS_ASLEEP;
		sleep((caddr_t)&tp->t_outq, TTOPRI);
	}
	splx(s);
}

/*
 * Flush all TTY queues
 */
ttyflush(tp, rw)
	register struct tty *tp;
{
	register s;

	s = spltty();
	if (rw & FREAD) {
		while (getc(&tp->t_canq) >= 0)
			;
		wakeup((caddr_t)&tp->t_rawq);
	}
	if (rw & FWRITE) {
		wakeup((caddr_t)&tp->t_outq);
		tp->t_state &= ~TS_TTSTOP;
		(*cdevsw[major(tp->t_dev)].d_stop)(tp, rw);
		while (getc(&tp->t_outq) >= 0)
			;
	}
	if (rw & FREAD) {
		while (getc(&tp->t_rawq) >= 0)
			;
		tp->t_rocount = 0;
		tp->t_rocol = 0;
		tp->t_state &= ~TS_LOCAL;
	}
	splx(s);
}

/*
 * Send stop character on input overflow.
 */
ttyblock(tp)
	register struct tty *tp;
{
	register x;

	x = tp->t_rawq.c_cc + tp->t_canq.c_cc;
	if (tp->t_rawq.c_cc > TTYHOG) {
		ttyflush(tp, FREAD|FWRITE);
		tp->t_state &= ~TS_TBLOCK;
	}
	/*
	 * Block further input iff:
	 * Current input > threshold AND input is available to user program
	 */
	if (x >= TTYHOG/2 && 
	    ((tp->t_flags & (RAW|CBREAK)) || (tp->t_canq.c_cc > 0))) {
		if (putc(tp->t_stopc, &tp->t_outq)==0) {
			tp->t_state |= TS_TBLOCK;
			ttstart(tp);
		}
	}
}

/*
 * Restart typewriter output following a delay
 * timeout.
 * The name of the routine is passed to the timeout
 * subroutine and it is called during a clock interrupt.
 */
ttrstrt(tp)
	register struct tty *tp;
{
    register int ipl = spltty();

	if (tp == 0)
		panic("ttrstrt");
	tp->t_state &= ~TS_TIMEOUT;
	ttstart(tp);
        splx(ipl);
}

/*
 * Start output on the typewriter. It is used from the top half
 * after some characters have been put on the output queue,
 * from the interrupt routine to transmit the next
 * character, and after a timeout has finished.
 */
ttstart(tp)
	register struct tty *tp;
{
	register s;

	s = spltty();
	if ((tp->t_state & (TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) == 0 &&
	    tp->t_oproc)		/* kludge for pty */
		(*tp->t_oproc)(tp);
	splx(s);
}

/*
 * Flag a login process exit.
 */
ttylogout(dev)
	dev_t dev;
{
	register struct tty *tp;

	if (dev == NODEV)
		return;

	tp = &(cdevsw[major(dev)].d_ttys)[minor(dev)];
	ttydetach(dev, tp);
	tp->t_state &= ~TS_LOGGEDIN;
	tp->t_state |=  TS_LOGGEDOUT;
	/* let control know */
	ttstart(tp);
}

/*
 *  Close down a terminal.  This routine is called from ttylogout() above when
 *  the login process for a terminal exits, from vhangup() and whenever the
 *  control side of a pseudo-terminal is closed.  The terminal is disconnected
 *  from all open files, as the controlling terminal for any process and as a
 *  virtual console.  A hangup signal is sent to the terminal process group to
 *  eliminate any processes which weren't specifically intended to run in the
 *  background.
 */
ttydetach(dev, tp)
	dev_t       dev;
	struct tty *tp;
{
	register struct proc *p;

	forceclose(dev);
	for (p=allproc; p != NULL; p = p->p_nxt) {
		if (p->p_ttyp && p->p_ttyd == dev && p != u.u_procp) {
			extern struct tty sytty[];
			extern dev_t sydev;

			p->p_ttyp = &sytty[0];
			p->p_ttyd = sydev;
		}
	}
	(void) ttyvcons(tp, TIOCVCONS_DISABLE, 1);
	(void) ttyvcons(tp, TIOCVCONS_DEASSIGN, 1);

	if ((tp)->t_state&TS_ISOPEN)
		gsignal((tp)->t_pgrp, SIGHUP);
}

/*
 *  Manage virtual console state - tweaked to mimic Berkeley
 *  behavior, except when CMUVCONS is defined.
 */

ttyvcons(tp, which, always)
	register struct tty *tp;
{
	register int md;
	uid_t oldowner;
	uid_t newowner;

#if	defined(CMUVCONS)
	if (!always) {
		if (u.u_ttyp == NULL)
			return(ENXIO);
		if (u.u_ttyp != tp)
			return(EACCES);
	}
#else	/* CMUVCONS */
#ifdef	lint
	always = always;
#endif	/* lint */
#endif	/* CMUVCONS */

	switch (which) {
	    case TIOCVCONS_ENABLE:
		if (xcons_tp != 0) {
			if(xcons_tp == tp)
				return(0);
			else
				return(EBUSY);
		}
#if	defined(CMUVCONS)
		if (xcons_uid != u.u_uid)
			return(EPERM);
#else	/* CMUVCONS */
#if	!defined(UCONSOLE)
		if (!suser())
			return(u.u_error);
#endif	/* UCONSOLE */
#endif	/* CMUVCONS */
		xcons_tp = (tp);
		xcons_write = cdevsw[XCONS_MAJDEV].d_write;
		for (md=0; md<nchrdev; md++)
			if (cdevsw[md].d_write == xcons_write)
				cdevsw[md].d_write = ttwrite_xcons;
		break;

	    
	    case TIOCVCONS_DISABLE:
		if (xcons_tp == 0)
			return(ENOTCONN);
		if (xcons_tp != tp)
			return(EPERM);
		for (md=0; md<nchrdev; md++)
			if (cdevsw[md].d_write == ttwrite_xcons)
				cdevsw[md].d_write = xcons_write;
		xcons_tp  = 0;
		break;

#if	defined(CMUVCONS)
	    case TIOCVCONS_ASSIGN:
		oldowner = TIOCGCONS_NOUID;
		newowner = u.u_uid;
		goto doowner;
	
	    case TIOCVCONS_DEASSIGN:
		oldowner = u.u_uid;
		newowner = TIOCGCONS_NOUID;
		/* fall through */

	    doowner:
		if (cdevsw[major(tp->t_dev)].d_ioctl != cdevsw[XCONS_MAJDEV].d_ioctl)
			return(EINVAL);
		if (xcons_uid != oldowner && !always)
			return(EPERM);
		xcons_uid = newowner;
		break;
#else	/* CMUVCONS */
	    case TIOCVCONS_ASSIGN:
	    case TIOCVCONS_DEASSIGN:
#endif	/* CMUVCONS */
	    default:
		return(EINVAL);
	}
	return(0);
}

/*
 * Common code for tty ioctls.
 */
/*ARGSUSED*/
ttioctl(tp, com, data, flag)
	register struct tty *tp;
	caddr_t data;
{
	int dev = tp->t_dev;
	extern int nldisp;
	int s;
	register int newflags;

	/*
	 * If the ioctl involves modification,
	 * hang if in the background.
	 */
	switch (com) {

	case TIOCSETD:
	case TIOCSETP:
	case TIOCSETN:
	case TIOCFLUSH:
	case TIOCSETC:
	case TIOCSLTC:
	case TIOCSPGRP:
	case TIOCLBIS:
	case TIOCLBIC:
	case TIOCLSET:
	case TIOCSTI:
	case TIOCSWINSZ:
#ifdef  luna
	case TIOCTWOSB:
	case TIOCONESB:
#endif  luna
		while (tp->t_line == NTTYDISC &&
		   u.u_procp->p_pgrp != tp->t_pgrp && tp == u.u_ttyp &&
		   (u.u_procp->p_flag&SVFORK) == 0 &&
		   !(u.u_procp->p_sigignore & sigmask(SIGTTOU)) &&
		   !(u.u_procp->p_sigmask & sigmask(SIGTTOU))) {
			gsignal(u.u_procp->p_pgrp, SIGTTOU);
			sleep((caddr_t)&lbolt, TTOPRI);
		}
		break;
	}

	/*
	 * Process the ioctl.
	 */
	switch (com) {
#ifdef	CMU

	/* get terminal location */
	case TIOCGLOC:
	{
		bcopy((caddr_t)&(tp->t_ttyloc), data, sizeof(tp->t_ttyloc));
		break;
	}

#endif	/* CMU */

	/* define login capable terminal */
	case TIOCLOGINDEV:
	{
		if (! suser())
			return(u.u_error);
		if (u.u_ttyp == NULL) 
			return(ENXIO);
		if (u.u_ttyd != tp->t_dev) 
			return(EACCES);
		tp->t_state &= ~TS_LOGGEDOUT;
		u.u_procp->p_logdev = tp->t_dev;
		break;
	}

	/* change "logged-in" state */
	case TIOCCLOG:
	{
		if (! suser())
			return(u.u_error);
		if (*((int *)data))
		{
			tp->t_state |=  TS_LOGGEDIN;
		}
		else
		{
			tp->t_state &= ~TS_LOGGEDIN;
		}
		break;
	}

	/* get discipline number */
	case TIOCGETD:
#ifdef	balance
		if (tp->t_line == 2)
			*(int *)data = 1;
		else
#else	balance
		*(int *)data = tp->t_line;
#endif	balance
		break;

	/* set line discipline */
	case TIOCSETD: {
		register int t = *(int *)data;
		int error = 0;
#ifdef	balance
		if (t == 1)
			t = 2;
#endif	balance

		if ((unsigned) t >= nldisp)
			return (ENXIO);
		if (t != tp->t_line) {
			s = spltty();
			(*linesw[tp->t_line].l_close)(tp);
			error = (*linesw[t].l_open)(dev, tp);
			if (error) {
				(void) (*linesw[tp->t_line].l_open)(dev, tp);
				splx(s);
				return (error);
			}
			tp->t_line = t;
			splx(s);
		}
		break;
	}

	/* prevent more opens on channel */
	case TIOCEXCL:
		s = spltty();
		tp->t_state |= TS_XCLUDE;
		splx(s);
		break;

	case TIOCNXCL:
		s = spltty();
		tp->t_state &= ~TS_XCLUDE;
		splx(s);
		break;

	/* hang up line on last close */
	case TIOCHPCL:
		s = spltty();
		tp->t_state |= TS_HUPCLS;
		splx(s);
		break;

	case TIOCFLUSH: {
		register int flags = *(int *)data;

		if (flags == 0)
			flags = FREAD|FWRITE;
		else
			flags &= FREAD|FWRITE;
		ttyflush(tp, flags);
		break;
	}

	/* return number of characters immediately available */
	case FIONREAD:
		s = spltty();
		*(off_t *)data = ttnread(tp);
		splx(s);
		break;

	case TIOCOUTQ:
		*(int *)data = tp->t_outq.c_cc;
		break;

	case TIOCSTOP:
		s = spltty();
		if ((tp->t_state&TS_TTSTOP) == 0) {
			tp->t_state |= TS_TTSTOP;
			(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
		}
		splx(s);
		break;

	case TIOCSTART:
		s = spltty();
		if ((tp->t_state&TS_TTSTOP) || (tp->t_flags&FLUSHO)) {
			tp->t_state &= ~TS_TTSTOP;
			tp->t_flags &= ~FLUSHO;
			ttstart(tp);
		}
		splx(s);
		break;

	/*
	 * Simulate typing of a character at the terminal.
	 */
	case TIOCSTI:
		if (u.u_uid && (flag & FREAD) == 0)
			return (EPERM);
		if (u.u_uid && u.u_ttyp != tp)
			return (EACCES);
		s = spltty();
		(*linesw[tp->t_line].l_rint)(*(char *)data, tp);
		splx(s);
		break;

	case TIOCSETP:
	case TIOCSETN: {
		register struct sgttyb *sg = (struct sgttyb *)data;

		tp->t_erase = sg->sg_erase;
		tp->t_kill = sg->sg_kill;
		tp->t_ispeed = sg->sg_ispeed;
		tp->t_ospeed = sg->sg_ospeed;
		newflags = (tp->t_flags&0xffff0000) | (sg->sg_flags&0xffff);
		s = spltty();
		if (tp->t_flags&RAW || newflags&RAW || com == TIOCSETP) {
			ttywait(tp);
			ttyflush(tp, FREAD);
		} else if ((tp->t_flags&CBREAK) != (newflags&CBREAK)) {
			if (newflags&CBREAK) {
				struct clist tq;

				catq(&tp->t_rawq, &tp->t_canq);
				tq = tp->t_rawq;
				tp->t_rawq = tp->t_canq;
				tp->t_canq = tq;
			} else {
				tp->t_flags |= PENDIN;
				newflags |= PENDIN;
				ttwakeup(tp);
			}
		}
		tp->t_flags = newflags;
		if (tp->t_flags&RAW) {
			tp->t_state &= ~TS_TTSTOP;
			ttstart(tp);
		}
		splx(s);
		break;
	}

	/* send current parameters to user */
	case TIOCGETP: {
		register struct sgttyb *sg = (struct sgttyb *)data;

		sg->sg_ispeed = tp->t_ispeed;
		sg->sg_ospeed = tp->t_ospeed;
		sg->sg_erase = tp->t_erase;
		sg->sg_kill = tp->t_kill;
		sg->sg_flags = tp->t_flags;
		break;
	}

	case FIONBIO:
		s = spltty();
		if (*(int *)data)
			tp->t_state |= TS_NBIO;
		else
			tp->t_state &= ~TS_NBIO;
		splx(s);
		break;

	case FIOASYNC:
		s = spltty();
		if (*(int *)data)
			tp->t_state |= TS_ASYNC;
		else
			tp->t_state &= ~TS_ASYNC;
		splx(s);
		break;

	case TIOCGETC:
		bcopy((caddr_t)&tp->t_intrc, data, sizeof (struct tchars));
		break;

	case TIOCSETC:
		bcopy(data, (caddr_t)&tp->t_intrc, sizeof (struct tchars));
		break;

	/* set/get local special characters */
	case TIOCSLTC:
		bcopy(data, (caddr_t)&tp->t_suspc, sizeof (struct ltchars));
		break;

	case TIOCGLTC:
		bcopy((caddr_t)&tp->t_suspc, data, sizeof (struct ltchars));
		break;

	/*
	 * Modify local mode word.
	 */
	case TIOCLBIS:
		tp->t_flags |= *(int *)data << 16;
		break;

	case TIOCLBIC:
		tp->t_flags &= ~(*(int *)data << 16);
		break;

	case TIOCLSET:
		tp->t_flags &= 0xffff;
		tp->t_flags |= *(int *)data << 16;
		break;

	case TIOCLGET:
		*(int *)data = ((unsigned) tp->t_flags) >> 16;
		break;

	/*
	 * Allow SPGRP only if tty is open for reading.
	 * Quick check: if we can find a process in the new pgrp,
	 * this user must own that process.
	 * SHOULD VERIFY THAT PGRP IS IN USE AND IS THIS USER'S.
	 */
	case TIOCSPGRP: {
		struct proc *p;
		int pgrp = *(int *)data;

		if (u.u_uid && (flag & FREAD) == 0)
			return (EPERM);
		p = pfind(pgrp);
		if (p && p->p_pgrp == pgrp &&
		    p->p_uid != u.u_uid && u.u_uid && !inferior(p))
			return (EPERM);
		/* XXX - temp until LOGIN always makes this call */
		(void) ttyvcons(tp, TIOCVCONS_ASSIGN, 0);
		tp->t_pgrp = pgrp;
		break;
	}

	case TIOCGPGRP:
		*(int *)data = tp->t_pgrp;
		break;

	case TIOCVCONS:
		switch (*(int *)data) {
		    case TIOCVCONS_DISABLE:
		    case TIOCVCONS_ENABLE:
		    case TIOCVCONS_ASSIGN:
		    case TIOCVCONS_DEASSIGN:
			return (ttyvcons(tp, *(int *)data, 0));
		    default:
			return (EINVAL);
		}

#ifdef	__STDC__
	case _IO('t', 104):		/* XXX - 4.2 VICE compatibility */
#else
	case _IO(t, 104):		/* XXX - 4.2 VICE compatibility */
#endif
	case TIOCCONS:
		xcons_uid = u.u_uid;
		return (ttyvcons(tp, TIOCVCONS_ENABLE, 0));

	case TIOCGCONS:
		((struct tiocgcons *)data)->tgc_uid = xcons_uid;
		if (xcons_tp)
			((struct tiocgcons *)data)->tgc_dev = xcons_tp->t_dev;
		else
			((struct tiocgcons *)data)->tgc_dev = TIOCGCONS_NODEV;
		break;

	case TIOCSWINSZ:
		if (bcmp((caddr_t)&tp->t_winsize, data,
		    sizeof (struct winsize))) {
			tp->t_winsize = *(struct winsize *)data;
			gsignal(tp->t_pgrp, SIGWINCH);
		}
		break;

	case TIOCGWINSZ:
		*(struct winsize *)data = tp->t_winsize;
		break;
#ifdef  luna
        case TIOCTWOSB:
	        tp->t_omron |= TS_TWOSB;
	        break;

        case TIOCONESB:
	        tp->t_omron &= ~TS_TWOSB;
	        break;

        case JTERMGET :
	        bcopy(&tp->t_jt,
                      (struct jtermio *)data,
                      sizeof(struct jtermio));
        	break;

    case JTERMSET :
            s = spltty();
            bcopy((struct jtermio *)data,
                       &tp->t_jt,
                       sizeof(struct jtermio));
	    splx(s);
	    break;
#endif  luna

	default:
#ifdef	luna
		return(EINVAL);
#else	luna
		return(-1);
#endif	luna
	}
	return (0);
}

ttnread(tp)
	struct tty *tp;
{
	int nread = 0;

	if (tp->t_flags & PENDIN)
		ttypend(tp);
	nread = tp->t_canq.c_cc;
	if (tp->t_flags & (RAW|CBREAK))
		nread += tp->t_rawq.c_cc;
	return (nread);
}

ttselect(dev, rw)
	dev_t dev;
	int rw;
{
	register struct tty *tp = &cdevsw[major(dev)].d_ttys[minor(dev)];
	int nread;
	int s = spltty();

	switch (rw) {

	case FREAD:
		nread = ttnread(tp);
		if ((nread > 0) || ((tp->t_state & TS_CARR_ON) == 0))
			goto win;
		if (tp->t_rsel &&
			((thread_t)(tp->t_rsel))->wait_event
				== (int)&selwait)
			tp->t_state |= TS_RCOLL;
		else
			tp->t_rsel = (struct proc *) current_thread();
		break;

	case FWRITE:
		if (tp->t_outq.c_cc <= TTLOWAT(tp))
			goto win;
		if (tp->t_wsel &&
			((thread_t)(tp->t_wsel))->wait_event
				== (int)&selwait)
			tp->t_state |= TS_WCOLL;
		else
			tp->t_wsel = (struct proc *) current_thread();
		break;
	}
	splx(s);
	return (0);
win:
	splx(s);
	return (1);
}

#ifdef	balance
/*
 * Sequent drivers allocate their tty structures at boot time to allow
 * for binary configuration and more flexibility in minor number use.
 * Thus, need a version of ttselect() that takes a struct tty pointer,
 * rather than assuming it knows how to generate it.
 */

tpselect(tp, rw)
	register struct tty *tp;
	int rw;
{
	int nread;
	int s = spltty();

	switch (rw) {

	case FREAD:
		nread = ttnread(tp);
		if ((nread > 0) || ((tp->t_state & TS_CARR_ON) == 0))
			goto win;
		if (tp->t_rsel &&
			((thread_t)(tp->t_rsel))->wait_event
				== (int)&selwait)
			tp->t_state |= TS_RCOLL;
		else
			tp->t_rsel = (struct proc *) current_thread();
		break;

	case FWRITE:
		if (tp->t_outq.c_cc <= TTLOWAT(tp))
			goto win;
		if (tp->t_wsel &&
			((thread_t)(tp->t_wsel))->wait_event
				== (int)&selwait)
			tp->t_state |= TS_WCOLL;
		else
			tp->t_wsel = (struct proc *) current_thread();
		break;
	}
	splx(s);
	return (0);
win:
	splx(s);
	return (1);
}
#endif	balance
/*
 * Initial open of tty, or (re)entry to line discipline.
 * Establish a process group for distribution of
 * quits and interrupts from the tty.
 */
ttyopen(dev, tp)
	dev_t dev;
	register struct tty *tp;
{
	register struct proc *pp;
        int oldipl;

	pp = u.u_procp;
	tp->t_dev = dev;
#ifdef  luna
	tp->t_omron = 0;
#endif  luna
	if (pp->p_pgrp == 0) {
		register struct proc *p;

		/*
		 *  Try to make the controlling terminal identity somewhat more
		 *  reliable by restricting changes to the super-user or only
		 *  when no process belonging to another user is already using
		 *  this for a controlling terminal.  If this terminal is
		 *  already in use and we are not the super-user, we get a
		 *  disconnected terminal instead.
		 */
		for (p=allproc; p != NULL; p = p->p_nxt)
			if (p->p_ttyp && p->p_ttyd == dev &&
			                 p->p_uid != u.u_uid)
				break;
		if (p == NULL || u.u_uid == 0) {
			pp->p_ttyp = tp;
			pp->p_ttyd = dev;
		} else {
			extern struct tty sytty[];
			extern dev_t sydev;

			pp->p_ttyp = &sytty[0];
			pp->p_ttyd = sydev;
		}
		if (tp->t_pgrp == 0)
			tp->t_pgrp = pp->p_pid;
		pp->p_pgrp = tp->t_pgrp;
	}
	oldipl = spltty();
	tp->t_state &= ~TS_WOPEN;
	if ((tp->t_state & TS_ISOPEN) == 0) {
		tp->t_state |= TS_ISOPEN;
		splx(oldipl);
		bzero((caddr_t)&tp->t_winsize, sizeof(tp->t_winsize));
		if (tp->t_line != NTTYDISC)
			ttywflush(tp);
#ifdef	CMU
		/*
		 *  Initialize the terminal location on the first open for as
		 *  long as the host ID has not been set.  For directly
		 *  connected lines, this will be the only time that the
		 *  location changes.  For pseudo terminal lines, the location
		 *  will usually be set by the controlling process and this
		 *  code will not be invoked.
		 */
		if (tp->t_ttyloc.tlc_hostid == 0)
		{
			tp->t_ttyloc.tlc_hostid = TLC_MYHOST;
			tp->t_ttyloc.tlc_ttyid = minor(dev);
		}
#endif	/* CMU */
	} else splx(oldipl);
	return (0);
}

/*
 * "close" a line discipline
 */
ttylclose(tp)
	register struct tty *tp;
{

	ttywflush(tp);
	tp->t_line = 0;
}

/*
 * clean tp on last close
 */
ttyclose(tp)
	register struct tty *tp;
{

	/*
	 * Release the console if it was attached to this tty.
	 * ttyvcons will fail if it was either not attached or
	 * attached elsewhere.
	 * XXX is this necessary (emg)?
	 */
	(void)ttyvcons(tp, TIOCVCONS_DISABLE, 0);
	ttyflush(tp, FREAD|FWRITE);
	tp->t_pgrp = 0;
	tp->t_state = 0;
}

/*
 * Handle modem control transition on a tty.
 * Flag indicates new state of carrier.
 * Returns 0 if the line should be turned off, otherwise 1.
 */
ttymodem(tp, flag)
	register struct tty *tp;
{

	if ((tp->t_state&TS_WOPEN) == 0 && (tp->t_flags & MDMBUF)) {
		/*
		 * MDMBUF: do flow control according to carrier flag
		 */
		if (flag) {
			tp->t_state &= ~TS_TTSTOP;
			ttstart(tp);
		} else if ((tp->t_state&TS_TTSTOP) == 0) {
			tp->t_state |= TS_TTSTOP;
			(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
		}
	} else if (flag == 0) {
		/*
		 * Lost carrier.
		 */
		tp->t_state &= ~TS_CARR_ON;
		if (tp->t_state & TS_ISOPEN) {
			if ((tp->t_flags & NOHANG) == 0) {
				gsignal(tp->t_pgrp, SIGHUP);
				gsignal(tp->t_pgrp, SIGCONT);
				ttyflush(tp, FREAD|FWRITE);
				return (0);
			}
		}
	} else {
		/*
		 * Carrier now on.
		 */
		tp->t_state |= TS_CARR_ON;
		wakeup((caddr_t)&tp->t_rawq);
	}
	return (1);
}

/*
 * Default modem control routine (for other line disciplines).
 * Return argument flag, to turn off device on carrier drop.
 */
nullmodem(tp, flag)
	register struct tty *tp;
	int flag;
{
	
	if (flag)
		tp->t_state |= TS_CARR_ON;
	else
		tp->t_state &= ~TS_CARR_ON;
	return (flag);
}

/*
 * reinput pending characters after state switch
 * call at spltty().
 */
ttypend(tp)
	register struct tty *tp;
{
	struct clist tq;
	register c;

	tp->t_flags &= ~PENDIN;
	tp->t_state |= TS_TYPEN;
	tq = tp->t_rawq;
	tp->t_rawq.c_cc = 0;
	tp->t_rawq.c_cf = tp->t_rawq.c_cl = 0;
	while ((c = getc(&tq)) >= 0)
		ttyinput(c, tp);
	tp->t_state &= ~TS_TYPEN;
}

#ifdef luna
inputtimeout(tp)
register struct tty *tp;
{
        register struct jterm *jp;

        jp = &tp->t_jt;
        if(jp->kesctime)  {
                jp->kesctime = 2;
                ttyinput((int)jp->inputaddr[0],
			(struct tty *)jp->inputaddr[1]);
        }
}
#endif luna

/*
 * Place a character on raw TTY input queue,
 * putting in delimiters and waking up top
 * half as needed.  Also echo if required.
 * The arguments are the character and the
 * appropriate tty structure.
 */
ttyinput(c, tp)
	register c;
	register struct tty *tp;
{
	register int t_flags = tp->t_flags;
	int i;
#ifdef  luna
	int s;
        register struct jterm *jp;
	register short jt;
	register short jec;
	register kescc = 0;
	register convfg = 0;
	register pcount = 0;
        register ctmp;
	register char *colp;

	jp = &tp->t_jt; 
	jt = jp->j_flg;
	jec = jp->j_ecode;

	if(jp->kesctime == 1) /* timeoutflag is on (JIS mode). */
		jp->kesctime = 0;
#endif  luna

	/*
	 * If input is pending take it first.
	 */
	if (t_flags&PENDIN)
		ttypend(tp);
	tk_nin++;
	c &= 0377;

	/*
	 * In tandem mode, check high water mark.
	 */
	if (t_flags&TANDEM)
		ttyblock(tp);

#ifdef luna
/************************************ KANJIINPUT **************************/
	if(jt & (CONVTOINT)) {
        	kescc = jp->kesccount;
                if (tp->t_rawq.c_cc+tp->t_canq.c_cc >= (TTYHOG-1)) {
                        if ((tp->t_line == NTTYDISC)&& !(t_flags&RAW)) {
                                if((jp->firstbyte==1)||jp->kana){
                                                ;
                                } else {
                                        if (c==tp->t_rprntc||c==tp->t_werasc||
                                            c==tp->t_kill  ||c==tp->t_erase ||
                                            c==tp->t_intrc ||c==tp->t_quitc ||
                                            c==tp->t_startc||c==tp->t_stopc ||
                                            c==tp->t_lnextc||c==tp->t_flushc||
                                            c==tp->t_suspc) {
                                                goto iconvend;
                                        } else {
                                                if(!jp->kesccount) {
                                                        if(jp->inputconv == KANJI) {
                                                                for(i=0;i< jp->j_jendl ;i++) {
                                                                        putc(jp->j_jend[i],&tp->t_outq);                                        }
                                                        }
                                                        (void) ttyoutput(CTRL(g), tp);

                                                        goto endcase;
                                                }
                                        }
                                }
                        }
                }

                /**************** han-kaku kana syori ****************/
                if (jec == UJIS) {
                        if (H_K_1 == (c&0xff) && jp->firstbyte == 0) {
                                /*** ujis han-kaku kana (1st byte) ***/
                                putc(c, &tp->t_rawq);
                                if (tp->t_rocount++ == 0)
                                        tp->t_rocol = tp->t_col;
                                if (t_flags&ECHO) {
                                        putc(c, &tp->t_outq);
                                }
                                jp->kana++;
                                goto endcase;
                        }
                        if ((H_K_S<=(c&0xff) && (c&0xff)<=H_K_E) && jp->kana) {
                                /*** ujis han-kaku kana (2nd byte) ***/
                                putc(c, &tp->t_rawq);
                                tp->t_rocount++;
                                if (t_flags&CBREAK)
                                        ttwakeup(tp);
                                if (t_flags&ECHO) {
                                        putc(c, &tp->t_outq);
                                        colp = &tp->t_col;
                                        (*colp)++;
                                }
                                jp->kana=0;
                                goto endcase;
                        }
                } else if ((H_K_S<=(c&0xff) && (c&0xff)<=H_K_E) &&
                            jp->firstbyte == 0) {
                        /* sjis&jis han-kaku kana */
                        int c1, c2;
                        c1 = H_K_1;
                        c2 = c;
                        putc(c1, &tp->t_rawq);
                        if (tp->t_rocount++ == 0)
                                tp->t_rocol = tp->t_col;
                        putc(c2, &tp->t_rawq);
                        tp->t_rocount++;
                        if (t_flags&ECHO) {
                                putc(c, &tp->t_outq);
                                colp = &tp->t_col;
                                (*colp)++;
                        }
                        if (t_flags&CBREAK)
                                ttwakeup(tp);
                        goto endcase;
                }
                /************* han-kaku kana syori (END) *************/

                convfg = inputconvert(c, jp);
                switch (convfg) {
                case 0:
                        /* timeout on for JIS kanji input */
                        if(jec==JIS&&(jp->kesccount==kescc+1)){
                                if (jp->kesccount==1&&c==jp->j_jst[0]) {
                                        jp->kesctime = 1;
                                        jp->inputaddr[0] = (int)c;
                                        jp->inputaddr[1] = (int)tp;
                                        timeout(inputtimeout,tp,8);
                                        return;
                                }
                        }
                        if (t_flags&ECHO) {   
                                if(jec==JIS&&(jp->kesccount==kescc+1)){
                                        ;
                                } else if(jec==JIS&&kescc!=0&&
                                                    jp->kesccount==0) {
                                        for(i=0;i<jp->outputp;i++) {
                                                putc(jp->outputbuf[i], &tp->t_outq);

                                        }
                                        jp->outputp = 0;
                                        goto endcase;
                                } else {  
                                        putc(c, &tp->t_outq);
                                        colp = &tp->t_col;
                                        (*colp)++;
                                } 
                        } else {
                                jp->outputp = 0;
                        }
                        return;
                        break;
                case 1:
                        /* kanji input */
                        for (i=0;i<jp->outputp;i++) {
                                putc(jp->outputbuf[i], &tp->t_rawq);
                                if (tp->t_rocount++ == 0)
                                        tp->t_rocol = (tp->t_col-1);
                        }
                        if (t_flags&CBREAK)
                                ttwakeup(tp);
                        if (t_flags&ECHO) {
                                putc(c, &tp->t_outq);
                                colp = &tp->t_col;
                                (*colp)++;
                        }
                        jp->outputp = 0;
                        jp->firstbyte = 0;
                        goto endcase;
                        break;
                case 2:   
                        if(jec==JIS){
                                if (jp->kesccount==1&&c==jp->j_jst[0]) {
                                        jp->kesctime = 1;
                                        jp->inputaddr[0] = (int)c;
                                        jp->inputaddr[1] = (int)tp;
                                        timeout(inputtimeout,tp,8);
                                }
                        }
                        pcount = 0;
                        break;
                case 3:
                        /* timeout END */
                        jp->outputbuf[jp->outputp++] = c;
                        pcount = 0;
                        break;    
                case -1:
                        /* not kanji input */
                        jp->outputp = 0;
                        break;
               }
	}
iconvend :
        if(jt&CONVTOINT&&jec==JIS&&(convfg==2||convfg==3)) {

                if(jp->outputp && pcount < jp->outputp) {
                        c = jp->outputbuf[pcount++];
                        if (c == tp->t_stopc) {
                                if ((tp->t_state&TS_TTSTOP) == 0) {
                                        tp->t_state |= TS_TTSTOP;
                                        (*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);

                                }
                                goto iconvend;
                        }   
                } else if(pcount) {
                        pcount = 0;
                        jp->outputp = 0;
                        return;
               }
	}

        jp->firstbyte = 0;
/************************************ KANJIINPUT **************************/
#endif luna
	if (t_flags&RAW) {
		/*
		 * Raw mode, just put character
		 * in input q w/o interpretation.
		 */
		if (tp->t_rawq.c_cc > TTYHOG) 
			ttyflush(tp, FREAD|FWRITE);
		else {
			if (putc(c, &tp->t_rawq) >= 0)
				ttwakeup(tp);
			ttyecho(c, tp);
		}
		goto endcase;
	}

	/*
	 * Ignore any high bit added during
	 * previous ttyinput processing.
	 */
	if ((tp->t_state&TS_TYPEN) == 0 && (t_flags&PASS8) == 0)
		c &= 0177;
	/*
	 * Check for literal nexting very first
	 */
	if (tp->t_state&TS_LNCH) {
#ifdef  luna
	    ctmp = c | 0200;
#else  !luna
		c |= 0200;
#endif luna
		tp->t_state &= ~TS_LNCH;
	}
#ifdef  luna
        else {
                ctmp = c;
	}
#endif  luna

	/*
	 * Scan for special characters.  This code
	 * is really just a big case statement with
	 * non-constant cases.  The bottom of the
	 * case statement is labeled ``endcase'', so goto
	 * it after a case match, or similar.
	 */
	if (tp->t_line == NTTYDISC) {
#ifdef luna
		if (ctmp == tp->t_lnextc) {
#else  luna
		if (c == tp->t_lnextc) {
#endif luna
			if (t_flags&ECHO)
				ttyout("^\b", tp);
			tp->t_state |= TS_LNCH;
			goto endcase;
		}
#ifdef luna
		if (ctmp == tp->t_flushc) {
#else  luna
		if (c == tp->t_flushc) {
#endif luna
			if (t_flags&FLUSHO)
				tp->t_flags &= ~FLUSHO;
			else {
				ttyflush(tp, FWRITE);
#ifdef luna
				ttyecho(ctmp, tp);
#else  luna
				ttyecho(c, tp);
#endif luna
				if (tp->t_rawq.c_cc + tp->t_canq.c_cc)
					ttyretype(tp);
				tp->t_flags |= FLUSHO;
			}
			goto startoutput;
		}
#ifdef luna
		if (ctmp == tp->t_suspc) {
#else  luna
		if (c == tp->t_suspc) {
#endif luna
			if ((t_flags&NOFLSH) == 0)
				ttyflush(tp, FREAD);
#ifdef luna
			ttyecho(ctmp, tp);
#else  luna
			ttyecho(c, tp);
#endif luna
			gsignal(tp->t_pgrp, SIGTSTP);
			goto endcase;
		}
	}

	/*
	 * Handle start/stop characters.
	 */
#ifdef luna
	if (ctmp == tp->t_stopc) {
#else  luna
	if (c == tp->t_stopc) {
#endif luna
		if ((tp->t_state&TS_TTSTOP) == 0) {
			tp->t_state |= TS_TTSTOP;
			(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
			return;
		}
#ifdef luna
		if (ctmp != tp->t_startc)
#else  luna
		if (c != tp->t_startc)
#endif luna
			return;
		goto endcase;
	}
#ifdef luna
	if (ctmp == tp->t_startc)
#else  luna
	if (c == tp->t_startc)
#endif luna
		goto restartoutput;

	/*
	 * Look for interrupt/quit chars.
	 */
#ifdef luna
	if (ctmp == tp->t_intrc || ctmp == tp->t_quitc) {
#else  luna
	if (c == tp->t_intrc || c == tp->t_quitc) {
#endif luna
#ifdef  luna
/* 	        gsignal(tp->t_pgrp, c == tp->t_intrc ? SIGINT : SIGQUIT);  */
		if ((t_flags&NOFLSH) == 0)
                            ttyflush(tp, FREAD|FWRITE);
                /*********** kanji syori *****************/
                s = spltty();
                tp->t_jstate |= JINTR; /* interrupt flag  */
		if (tp->t_jstate & KINPROC) {
                            for (i = 0; i < MIN(EMAX, jp->j_jendl); i++) {
	                                putc(jp->j_jend[i], &tp->t_outq);
			    }
                            tp->t_jstate &= ~(KINPROC|GCPROC);
                            /* kanji first half byte flush*/
                            tp->t_jt.j_firstcode = 0;
		}
                splx(s);
	        gsignal(tp->t_pgrp, ctmp == tp->t_intrc ? SIGINT : SIGQUIT); 
		ttyecho(ctmp, tp);
#else  !luna
		if ((t_flags&NOFLSH) == 0)
			ttyflush(tp, FREAD|FWRITE);
		ttyecho(c, tp);
		gsignal(tp->t_pgrp, c == tp->t_intrc ? SIGINT : SIGQUIT);
#endif ! luna
		goto endcase;
	}

	if (tp->t_flags & LCASE && c <= 0177) {
		if (tp->t_state&TS_BKSL) {
			ttyrub(unputc(&tp->t_rawq), tp);
#ifdef luna
			if (maptab[ctmp])
				ctmp = maptab[ctmp];
#else  luna
			if (maptab[c])
				c = maptab[c];
#endif luna
#ifndef luna
			c |= 0200;
#endif  luna
			tp->t_state &= ~(TS_BKSL|TS_QUOT);
#ifdef luna
		} else if (ctmp >= 'A' && ctmp <= 'Z')
			ctmp += 'a' - 'A';
		else if (ctmp == '\\')
			tp->t_state |= TS_BKSL;
#else  luna
		} else if (c >= 'A' && c <= 'Z')
			c += 'a' - 'A';
		else if (c == '\\')
			tp->t_state |= TS_BKSL;
#endif luna
	}

#ifdef  luna
/*
	if ((ctmp == c) &&
	    (jp->j_flg & CONVTOEXT) &&
	    (jp->j_ecode != UJIS) &&
	    (H_K_S <= c) && (c <= H_K_E) &&
*/
/*	    (jp->j_firstcode == 0))  { /* KURI  89.1.29 */
/*
                putc(H_K_1, &tp->t_rawq);
		ttyecho(H_K_1, tp);
	    }
*/
#endif  luna
	/*
	 * Cbreak mode, don't process line editing
	 * characters; check high water mark for wakeup.
	 */
	if (t_flags&CBREAK) {
		if (tp->t_rawq.c_cc > TTYHOG) {
			if (tp->t_outq.c_cc < TTHIWAT(tp) &&
			    tp->t_line == NTTYDISC)
#ifdef	__STDC__
				(void) ttyoutput(CTRL('g'), tp);
#else
				(void) ttyoutput(CTRL(g), tp);
#endif
		} else if (putc(c, &tp->t_rawq) >= 0) {
			ttwakeup(tp);
			ttyecho(c, tp);
		}
		goto endcase;
	}

	/*
	 * From here on down cooked mode character
	 * processing takes place.
	 */
	if ((tp->t_state&TS_QUOT) &&
#ifdef luna
	    (ctmp == tp->t_erase || ctmp == tp->t_kill)) {
#else  luna
	    (c == tp->t_erase || c == tp->t_kill)) {
#endif luna
		ttyrub(unputc(&tp->t_rawq), tp);
#ifndef luna
		c |= 0200;
#endif  ! luna
	}
#ifdef luna
	if (ctmp == tp->t_erase) {
#else  luna
	if (c == tp->t_erase) {
#endif luna
		if (tp->t_rawq.c_cc)
			ttyrub(unputc(&tp->t_rawq), tp);
		goto endcase;
	}
#ifdef luna
	if (ctmp == tp->t_kill) {
#else  luna
	if (c == tp->t_kill) {
#endif luna
		if (t_flags&CRTKIL &&
		    tp->t_rawq.c_cc == tp->t_rocount) {
			while (tp->t_rawq.c_cc)
				ttyrub(unputc(&tp->t_rawq), tp);
		} else {
			ttyecho(c, tp);
			ttyecho('\n', tp);
			while (getc(&tp->t_rawq) > 0)
				;
			tp->t_rocount = 0;
		}
		tp->t_state &= ~TS_LOCAL;
		goto endcase;
	}

	/*
	 * New line discipline,
	 * check word erase/reprint line.
	 */
	if (tp->t_line == NTTYDISC) {
#ifdef luna
		if (ctmp == tp->t_werasc) {
#else  luna
		if (c == tp->t_werasc) {
#endif luna
			if (tp->t_rawq.c_cc == 0)
				goto endcase;
			do {
				c = unputc(&tp->t_rawq);
				if (c != ' ' && c != '\t')
					goto erasenb;
				ttyrub(c, tp);
			} while (tp->t_rawq.c_cc);
			goto endcase;
	erasenb:
			do {
				ttyrub(c, tp);
				if (tp->t_rawq.c_cc == 0)
					goto endcase;
				c = unputc(&tp->t_rawq);
			} while (c != ' ' && c != '\t');
			(void) putc(c, &tp->t_rawq);
			goto endcase;
		}
#ifdef luna
		if (ctmp == tp->t_rprntc) {
#else  luna
		if (c == tp->t_rprntc) {
#endif luna
			ttyretype(tp);
			goto endcase;
		}
	}

	/*
	 * Check for input buffer overflow
	 */
	if (tp->t_rawq.c_cc+tp->t_canq.c_cc >= TTYHOG) {
		if (tp->t_line == NTTYDISC)
#ifdef	__STDC__
			(void) ttyoutput(CTRL('g'), tp);
#else
			(void) ttyoutput(CTRL(g), tp);
#endif
		goto endcase;
	}

	/*
	 * Put data char in q for user and
	 * wakeup on seeing a line delimiter.
	 */
	if (putc(c, &tp->t_rawq) >= 0) {
#ifdef  luna
	        if (ttbreakc(ctmp, tp)) {
#else  !luna
		if (ttbreakc(c, tp)) {
#endif !luna
			tp->t_rocount = 0;
			catq(&tp->t_rawq, &tp->t_canq);
			ttwakeup(tp);
		} else if (tp->t_rocount++ == 0)
			tp->t_rocol = tp->t_col;
		tp->t_state &= ~TS_QUOT;
#ifdef  luna
                if (ctmp == '\\')
#else  !luna
		if (c == '\\')
#endif !luna
			tp->t_state |= TS_QUOT;
		if (tp->t_state&TS_ERASE) {
			tp->t_state &= ~TS_ERASE;
			(void) ttyoutput('/', tp);
		}
		i = tp->t_col;
		ttyecho(c, tp);
#ifdef  luna
		if (ctmp == tp->t_eofc && t_flags&ECHO) {
#else  !luna
		if (c == tp->t_eofc && t_flags&ECHO) {
#endif !luna
			i = MIN(2, tp->t_col - i);
			while (i > 0) {
				(void) ttyoutput('\b', tp);
				i--;
			}
		}
	}
endcase:
	/*
	 * If DEC-style start/stop is enabled don't restart
	 * output until seeing the start character.
	 */
	if (t_flags&DECCTQ && tp->t_state&TS_TTSTOP &&
	    tp->t_startc != tp->t_stopc)
#ifdef luna
	{
		if(pcount) {
			goto iconvend;
		} else {
#endif luna
		return;
#ifdef luna
		}
	}
	jp->firstbyte = 0;
	if(convfg!=2) 
		jp->kesccount = 0;
#endif luna
restartoutput:
	tp->t_state &= ~TS_TTSTOP;
	tp->t_flags &= ~FLUSHO;
startoutput:
	ttstart(tp);
#ifdef luna
	if(pcount) {
                goto iconvend;
        }
#endif luna
}

/*
 * Put character on TTY output queue, adding delays,
 * expanding tabs, and handling the CR/NL bit.
 * This is called both from the top half for output,
 * and from interrupt level for echoing.
 * The arguments are the character and the tty structure.
 * Returns < 0 if putc succeeds, otherwise returns char to resend
 * Must be recursive.
 */
#ifdef  luna
#define OUT_OF_UJIS(x)  ((x < _1_S || x > _1_E) && (x != H_K_1) && (x != H_K_S))
#define IS_UJIS(x)      ((x >= _1_S && x <= _1_E) || (x == H_K_S))
#endif  luna
ttyoutput(c, tp)
	register c;
	register struct tty *tp;
{
	register char *colp;
	register ctype;

#ifdef  luna
	register struct jterm *jp = &tp->t_jt;
	int s;
	int jep;

	c &= 0377;
#endif  luna
	if (tp->t_flags & (RAW|LITOUT)) {
		if (tp->t_flags&FLUSHO)
			return (-1);
		if (putc(c, &tp->t_outq))
			return (c);
		tk_nout++;
		return (-1);
	}

#ifdef  luna
	if (jp->j_flg & CONVTOEXT) {
                    if (!(c & 0x80) || OUT_OF_UJIS(c)) {
                        /*
                         * ASCII or han-kaku kana echo or
                         * 8-bits code out of UJIS internal code range
			 */
			s = spltty();
			jp->j_firstcode = 0;
			if (tp->t_jstate & KINPROC) {
			    /* send the kanji-out esc sequence */
			    for (jep = 0;
				 jep < MIN(EMAX, jp->j_jendl);
				 jep++) {
				putc(jp->j_jend[jep], &tp->t_outq);
			    }
			    tp->t_jstate &= ~(KINPROC|GCPROC);
			}
			splx(s);
		    } else {
			goto kproc;
		    }
		}
	if (c >= 0200) {
	    if ((jp->j_flg & CONVTOEXT) && (jp->j_ecode == UJIS)
		&& (IS_UJIS(c))) {
		colp = &tp->t_col;
		(*colp)++;
	    }
	    if (putc(c, &tp->t_outq))       /* HARA 8/16 */
		return(c);          /* HARA 8/16 */
	    return(-1);
	}
#endif  luna
	/*
	 * Ignore EOT in normal mode to avoid
	 * hanging up certain terminals.
	 */
#ifndef luna
	c &= 0177;
#endif  !luna
	if (c == CEOT && (tp->t_flags&CBREAK) == 0)
		return (-1);
	/*
	 * Turn tabs to spaces as required
	 */
	if (c == '\t' && (tp->t_flags&TBDELAY) == XTABS) {
		register int s;

		c = 8 - (tp->t_col&7);
		if ((tp->t_flags&FLUSHO) == 0) {
			s = spltty();		/* don't interrupt tabs */
			c -= b_to_q("        ", c, &tp->t_outq);
			tk_nout += c;
			splx(s);
		}
		tp->t_col += c;
		return (c ? -1 : '\t');
	}
	tk_nout++;
	/*
	 * for upper-case-only terminals,
	 * generate escapes.
	 */
	if (tp->t_flags&LCASE) {
		colp = "({)}!|^~'`";
		while (*colp++)
			if (c == *colp++) {
				if (ttyoutput('\\', tp) >= 0)
					return (c);
				c = colp[-2];
				break;
			}
		if ('A' <= c && c <= 'Z') {
			if (ttyoutput('\\', tp) >= 0)
				return (c);
		} else if ('a' <= c && c <= 'z')
			c += 'A' - 'a';
	}

	/*
	 * turn <nl> to <cr><lf> if desired.
	 */
	if (c == '\n' && tp->t_flags&CRMOD)
		if (ttyoutput('\r', tp) >= 0)
			return (c);
	if (c == '~' && tp->t_flags&TILDE)
		c = '`';
	if ((tp->t_flags&FLUSHO) == 0 && putc(c, &tp->t_outq))
		return (c);
	/*
	 * Calculate delays.
	 * The numbers here represent clock ticks
	 * and are not necessarily optimal for all terminals.
	 * The delays are indicated by characters above 0200.
	 * In raw mode there are no delays and the
	 * transmission path is 8 bits wide.
	 *
	 * SHOULD JUST ALLOW USER TO SPECIFY DELAYS
	 */
	colp = &tp->t_col;
	ctype = partab[c];
	c = 0;
	switch (ctype&077) {

	case ORDINARY:
		(*colp)++;

	case CONTROL:
		break;

	case BACKSPACE:
		if (*colp)
			(*colp)--;
		break;

	/*
	 * This macro is close enough to the correct thing;
	 * it should be replaced by real user settable delays
	 * in any event...
	 */
#define mstohz(ms)	(((ms) * hz) >> 10)
	case NEWLINE:
		ctype = (tp->t_flags >> 8) & 03;
		if (ctype == 1) { /* tty 37 */
			if (*colp > 0) {
				c = (((unsigned)*colp) >> 4) + 3;
				if ((unsigned)c > 6)
					c = 6;
			}
		} else if (ctype == 2) /* vt05 */
			c = mstohz(100);
		*colp = 0;
		break;

	case TAB:
		ctype = (tp->t_flags >> 10) & 03;
		if (ctype == 1) { /* tty 37 */
			c = 1 - (*colp | ~07);
			if (c < 5)
				c = 0;
		}
		*colp |= 07;
		(*colp)++;
		break;

	case VTAB:
		if (tp->t_flags&VTDELAY) /* tty 37 */
			c = 0177;
		break;

	case RETURN:
		ctype = (tp->t_flags >> 12) & 03;
		if (ctype == 1) /* tn 300 */
			c = mstohz(83);
		else if (ctype == 2) /* ti 700 */
			c = mstohz(166);
		else if (ctype == 3) { /* concept 100 */
			int i;

			if ((i = *colp) >= 0)
				for (; i < 9; i++)
					(void) putc(0177, &tp->t_outq);
		}
		*colp = 0;
	}
	if (c && (tp->t_flags&FLUSHO) == 0)
		(void) putc(c|0200, &tp->t_outq);
	return (-1);
#ifdef  luna
    kproc:                  /* kanji processing */
	{
	    register unsigned c1,c2;
	    short ecodef;
	    short onebyte;

	    if (jp->j_firstcode == 0 ) {
		jp->j_firstcode = c;
		return(-1);
	    }

	    ecodef = ASCII;
	    onebyte = 0;
	    
	    c1 = jp->j_firstcode;
	    jp->j_firstcode = 0;
	    c2 = (unsigned) c;
#ifdef notuse
	    if (G_1_S <= c1 && c1 <= G_1_E) {       /* gaiji processing */
		if (tp->t_omron & PTY_TTY) { /* 1.3.24 KOIZUMI */
		    return(-1);
		}
		c1 = G_1_E - (c1 - G_1_S);
		c2 = G_2_E - (c2 - G_2_S);
		 if (jp->j_ecode == JIS) {
		     c1 &= 0x7f;
		     c2 &= 0x7f;
		     c2 = c2 - JISG2S + jp->j_gcsa[1];
		     if (c2 > JISG2E ) {
			 c2 = c2 - (JISG2E + 1) + JISG2S;
			 c1 = c1 - JISG1S + jp->j_gcsa[0] + 1;
		     } else
			 c1 = c1 - JISG1S + jp->j_gcsa[0];
		     ecodef = GCPROC;
		 } else if (jp->j_ecode == SJIS) {
		     /* sift-JIS gaiji conversion */
		     unsigned int l1, l2, l;
		     unsigned char gcsa;
		     l1 = (c1 - G_1_S) * (G_2_E - G_2_S + 1) +
			 (c2 - G_2_S + 1);
		     if ((ushort) jp->j_gcsa[1] >= 0x80)
			 gcsa = (unsigned char) jp->j_gcsa[1] - 1;
		     else
			 gcsa = (unsigned char) jp->j_gcsa[1];
		     l2 = ((unsigned char) jp->j_gcsa[0] - SJISG1S)
			 * (SJISG2E - SJISG2S) + (gcsa - SJISG2S);
		     l = l1 + l2 - 1;
		     if (l >= SJISGAS)
			 return(-1);
		     c1 = (g_sjis[l] >> 8) & 0xff;
		     c2 = g_sjis[l] & 0xff;
		 } else if (jp->j_ecode == UJIS) {
		     /* u-JIS gaiji conversion */
		     c2 = c2 - G_2_S + (unsigned char)jp->j_gcsa[1];
		     if (c2 > G_2_E ) {
			 c2 = c2 - (G_2_E + 1) + G_2_S;
			 c1 = c1 - G_1_S +
			     (unsigned char)jp->j_gcsa[0] + 1;
		     } else {
			 c1 = c1 - G_1_S +
			     (unsigned char)jp->j_gcsa[0];
		     }
		 }
#endif notuse
	    if (c1 == H_K_1) {       /* han-kaku kana processing */
		if ((jp->j_ecode != UJIS) &&
		    (H_K_S <= c2 && c2 <= H_K_E)) {
		    c1 = c2;
		    onebyte = 1;
		}
	    } else {                        /* naiji processing */
		if (jp->j_ecode == JIS) {
		    c1 &= 0177;
		    c2 &= 0177;
		    ecodef = KINPROC;
		} else if (jp->j_ecode == SJIS) {
		    if (c1 & 0x01)
			    if (c2 <= 0xdf)
				c2 -= 0x61;
			    else
				c2 -= 0x60;
		    else
			c2 -= 0x02;
		    if (c1 <= 0xde)
			c1 = (c1 - 0xa1) / 2 + 0x81;
		    else
			c1 = (c1 - 0xdf) / 2 + 0xe0;
		}
	    }
	    s = spltty();
	    switch (ecodef) {
	    case ASCII :
		if (tp->t_jstate & KINPROC) {
		    for (jep = 0;
			 jep < MIN(EMAX, jp->j_jendl);
			 jep++) {
			putc(jp->j_jend[jep], &tp->t_outq);
		    }
		    tp->t_jstate &= ~(KINPROC|GCPROC);
		}
		break;
	    case KINPROC :
		if ((tp->t_jstate & GCPROC) ||
		    !(tp->t_jstate & KINPROC) ) {
		    for (jep = 0;
			 jep < MIN(EMAX, jp->j_jstl);
			 jep++) {
			putc(jp->j_jst[jep], &tp->t_outq);
		    }
		    tp->t_jstate &= ~GCPROC;
		    tp->t_jstate |= KINPROC;
		}
		break;
	    case GCPROC :
		if (!(tp->t_jstate & GCPROC)) {
		    if (!(tp->t_jstate & KINPROC)) {
			for (jep = 0;
			     jep < MIN(EMAX, jp->j_jstl);
			     jep++) {
			    putc(jp->j_jst[jep],
				 &tp->t_outq);
			}
			tp->t_jstate |= KINPROC;
		    }
		    for (jep = 0;
			 jep < MIN(EMAX, jp->j_gdspl);
			 jep++) {
			putc(jp->j_gdsp[jep], &tp->t_outq);
		    }
		    tp->t_jstate |= GCPROC;
		}
		break;
	    }
	    colp = &tp->t_col;
	    if ((tp->t_flags&FLUSHO) == 0) {
		    putc(c1, &tp->t_outq);
	    }
	    (*colp)++;
	    if (!onebyte) {
		if ((tp->t_flags&FLUSHO) == 0) {
                                putc(c2, &tp->t_outq);
                        } 
		if ((c1 == H_K_1)&&(jp->j_ecode == UJIS)) {
			;
		} else {
			(*colp)++;  
		}
	    }
	    splx(s);
	    return(-1);
	}                                             /* end of kproc */
#endif  luna
}
#undef mstohz

/*
 * Called from device's read routine after it has
 * calculated the tty-structure given as argument.
 */
ttread(tp, uio)
	register struct tty *tp;
	struct uio *uio;
{
	register struct clist *qp;
	register c, t_flags;
	int s, first, error = 0;

loop:
	/*
	 * Take any pending input first.
	 */
	s = spltty();
	if (tp->t_flags&PENDIN)
		ttypend(tp);
	splx(s);

	while ((tp->t_state&TS_CARR_ON)==0)
		if (tp->t_state&TS_ONDELAY) { /* open O_NDELAY */
			if (tp->t_state&TS_NBIO)
				return(EWOULDBLOCK);
			else 
				/* wake up on carrier transition */
				sleep((caddr_t)&tp->t_rawq, TTIPRI);
		}
		else 
			return(EIO);

	/*
	 * Hang process if it's in the background.
	 */
	if (tp == u.u_ttyp && u.u_procp->p_pgrp != tp->t_pgrp) {
		if ((u.u_procp->p_sigignore & sigmask(SIGTTIN)) ||
		   (u.u_procp->p_sigmask & sigmask(SIGTTIN)) ||
		    u.u_procp->p_flag&SVFORK)
			return (EIO);
		gsignal(u.u_procp->p_pgrp, SIGTTIN);
		sleep((caddr_t)&lbolt, TTIPRI);
		goto loop;
	}
	t_flags = tp->t_flags;

	/*
	 * In raw mode take characters directly from the
	 * raw queue w/o processing.  Interlock against
	 * device interrupts when interrogating rawq.
	 */
	if (t_flags&RAW) {
		s = spltty();
		if (tp->t_rawq.c_cc <= 0) {
			if ((tp->t_state&TS_CARR_ON) == 0 ||
			    (tp->t_state&TS_NBIO)) {
				splx(s);
				return (EWOULDBLOCK);
			}
			sleep((caddr_t)&tp->t_rawq, TTIPRI);
			splx(s);
			goto loop;
		}
		splx(s);
 		while (!error && tp->t_rawq.c_cc && uio->uio_resid)
 			error = ureadc(getc(&tp->t_rawq), uio);
		goto checktandem;
	}

	/*
	 * In cbreak mode use the rawq, otherwise
	 * take characters from the canonicalized q.
	 */
	qp = t_flags&CBREAK ? &tp->t_rawq : &tp->t_canq;

	/*
	 * No input, sleep on rawq awaiting hardware
	 * receipt and notification.
	 */
	s = spltty();
	if (qp->c_cc <= 0) {
		if ((tp->t_state&TS_CARR_ON) == 0 ||
		    (tp->t_state&TS_NBIO)) {
			splx(s);
			return (EWOULDBLOCK);
		}
		sleep((caddr_t)&tp->t_rawq, TTIPRI);
		splx(s);
		goto loop;
	}
	splx(s);

	/*
	 * Input present, perform input mapping
	 * and processing (we're not in raw mode).
	 */
	first = 1;
	while ((c = getc(qp)) >= 0) {
		if (t_flags&CRMOD && c == '\r')
			c = '\n';
		/*
		 * Check for delayed suspend character.
		 */
		if (tp->t_line == NTTYDISC && c == tp->t_dsuspc) {
			gsignal(tp->t_pgrp, SIGTSTP);
			if (first) {
				sleep((caddr_t)&lbolt, TTIPRI);
				goto loop;
			}
			break;
		}
		/*
		 * Interpret EOF only in cooked mode.
		 */
		if (c == tp->t_eofc && (t_flags&CBREAK) == 0)
			break;
		/*
		 * Give user character.
		 */
 		error = ureadc(t_flags&PASS8 ? c : c & 0177, uio);
		if (error)
			break;
 		if (uio->uio_resid == 0)
			break;
		/*
		 * In cooked mode check for a "break character"
		 * marking the end of a "line of input".
		 */
		if ((t_flags&CBREAK) == 0 && ttbreakc(c, tp))
			break;
		first = 0;
	}

checktandem:
	/*
	 * Look to unblock output now that (presumably)
	 * the input queue has gone down.
	 */
	if (tp->t_state&TS_TBLOCK && tp->t_rawq.c_cc < TTYHOG/5)
		if (putc(tp->t_startc, &tp->t_outq) == 0) {
			s = spltty();
			tp->t_state &= ~TS_TBLOCK;
			splx(s);
			ttstart(tp);
		}
	return (error);
}

/*
 * Check the output queue on tp for space for a kernel message
 * (from uprintf/tprintf).  Allow some space over the normal
 * hiwater mark so we don't lose messages due to normal flow
 * control, but don't let the tty run amok.
 */
ttycheckoutq(tp, wait)
	register struct tty *tp;
	int wait;
{
	int hiwat, s;

	hiwat = TTHIWAT(tp);
	s = spltty();
	if (tp->t_outq.c_cc > hiwat + 200)
	    while (tp->t_outq.c_cc > hiwat) {
		ttstart(tp);
		if (wait == 0) {
			splx(s);
			return (0);
		}
		tp->t_state |= TS_ASLEEP;
		sleep((caddr_t)&tp->t_outq, TTOPRI);
	}
	splx(s);
	return (1);
}

/*
 *  Called directly from cdevsw[] when the console output has been redirected.
 */
ttwrite_xcons(dev, uio)
	dev_t dev;
	register struct uio *uio;
{

	if (minor(dev) != 0)
		return((*xcons_write)(dev, uio));
	else
		return((*linesw[xcons_tp->t_line].l_write)(xcons_tp, uio));
}

/*
 * Called from the device's write routine after it has
 * calculated the tty-structure given as argument.
 */
ttwrite(tp, uio)
	register struct tty *tp;
	register struct uio *uio;
{
	register char *cp;
	register int cc, ce, c;
	int i, hiwat, cnt, error, s;
	char obuf[OBUFSIZ];
#ifdef  luna
	register struct jterm *jp = &tp->t_jt;
#endif  luna

	hiwat = TTHIWAT(tp);
	cnt = uio->uio_resid;
	error = 0;
#ifdef  luna
	tp->t_jstate &= ~JINTR; /* interrupt flag off */
#endif  luna
loop:
	while ((tp->t_state&TS_CARR_ON)==0)
		if (tp->t_state&TS_ONDELAY) { /* assume O_NDELAY */
			if (tp->t_state&TS_NBIO)
				return(EWOULDBLOCK);
			else 
				/* wake up on carrier transition */
				sleep((caddr_t)&tp->t_rawq, TTIPRI);
		}
		else 
			return(EIO);
	/*
	 * Hang the process if it's in the background.
	 */
	if (u.u_procp->p_pgrp != tp->t_pgrp && tp == u.u_ttyp &&
	    (tp->t_flags&TOSTOP) && (u.u_procp->p_flag&SVFORK)==0 &&
	    !(u.u_procp->p_sigignore & sigmask(SIGTTOU)) &&
	    !(u.u_procp->p_sigmask & sigmask(SIGTTOU))) {
		gsignal(u.u_procp->p_pgrp, SIGTTOU);
		sleep((caddr_t)&lbolt, TTIPRI);
		goto loop;
	}

	/*
	 * Process the user's data in at most OBUFSIZ
	 * chunks.  Perform lower case simulation and
	 * similar hacks.  Keep track of high water
	 * mark, sleep on overflow awaiting device aid
	 * in acquiring new space.
	 */
	while (uio->uio_resid > 0) {
		/*
		 * Grab a hunk of data from the user.
		 */
		cc = uio->uio_iov->iov_len;
		if (cc == 0) {
			uio->uio_iovcnt--;
			uio->uio_iov++;
			if (uio->uio_iovcnt <= 0)
				panic("ttwrite");
			continue;
		}
		if (cc > OBUFSIZ)
			cc = OBUFSIZ;
		cp = obuf;
		error = uiomove(cp, cc, UIO_WRITE, uio);
		if (error)
			break;
		if (tp->t_outq.c_cc > hiwat)
			goto ovhiwat;
		if (tp->t_flags&FLUSHO)
			continue;
		/*
		 * If we're mapping lower case or kludging tildes,
		 * then we've got to look at each character, so
		 * just feed the stuff to ttyoutput...
		 */
		if (tp->t_flags & (LCASE|TILDE)) {
			while (cc > 0) {
				c = *cp++;
				tp->t_rocount = 0;
				if ((c = ttyoutput(c, tp)) >= 0) {
					/* out of clists, wait a bit */
					ttstart(tp);
					sleep((caddr_t)&lbolt, TTOPRI);
					tp->t_rocount = 0;
					if (cc != 0) {
						uio->uio_iov->iov_base -= cc;
						uio->uio_iov->iov_len += cc;
						uio->uio_resid += cc;
						uio->uio_offset -= cc;
					}
					goto loop;
				}
				--cc;
				if (tp->t_outq.c_cc > hiwat)
					goto ovhiwat;
			}
			continue;
		}
		/*
		 * If nothing fancy need be done, grab those characters we
		 * can handle without any of ttyoutput's processing and
		 * just transfer them to the output q.  For those chars
		 * which require special processing (as indicated by the
		 * bits in partab), call ttyoutput.  After processing
		 * a hunk of data, look for FLUSHO so ^O's will take effect
		 * immediately.
		 */
		while (cc > 0) {
			if (tp->t_flags & (RAW|LITOUT))
				ce = cc;
			else {
				ce = cc - scanc((unsigned)cc, (caddr_t)cp,
				   (caddr_t)partab, 077);
				/*
				 * If ce is zero, then we're processing
				 * a special character through ttyoutput.
				 */
#ifdef  luna
				if ((ce == 0) || (jp->j_flg & CONVTOEXT)) {
#else  !luna
				if (ce == 0) {
#endif !luna
					tp->t_rocount = 0;
#ifdef  luna
					/* interrupt flag  */
					if(tp->t_jstate & JINTR) {
					    tp->t_jstate &= ~JINTR;
					    return(0);
					}
#endif  luna
					if (ttyoutput(*cp, tp) >= 0) {
					    /* no c-lists, wait a bit */
					    ttstart(tp);
					    sleep((caddr_t)&lbolt, TTOPRI);
					    if (cc != 0) {
					        uio->uio_iov->iov_base -= cc;
					        uio->uio_iov->iov_len += cc;
					        uio->uio_resid += cc;
						uio->uio_offset -= cc;
					    }
					    goto loop;
					}
					cp++, cc--;
					if (tp->t_flags&FLUSHO ||
					    tp->t_outq.c_cc > hiwat)
						goto ovhiwat;
					continue;
				}
			}
			/*
			 * A bunch of normal characters have been found,
			 * transfer them en masse to the output queue and
			 * continue processing at the top of the loop.
			 * If there are any further characters in this
			 * <= OBUFSIZ chunk, the first should be a character
			 * requiring special handling by ttyoutput.
			 */
			tp->t_rocount = 0;
			i = b_to_q(cp, ce, &tp->t_outq);
			ce -= i;
			tp->t_col += ce;
			cp += ce, cc -= ce, tk_nout += ce;
			if (i > 0) {
				/* out of c-lists, wait a bit */
				ttstart(tp);
				sleep((caddr_t)&lbolt, TTOPRI);
				uio->uio_iov->iov_base -= cc;
				uio->uio_iov->iov_len += cc;
				uio->uio_resid += cc;
				uio->uio_offset -= cc;
				goto loop;
			}
			if (tp->t_flags&FLUSHO || tp->t_outq.c_cc > hiwat)
				goto ovhiwat;
		}
	}
	ttstart(tp);
	return (error);

ovhiwat:
	s = spltty();
	if (cc != 0) {
		uio->uio_iov->iov_base -= cc;
		uio->uio_iov->iov_len += cc;
		uio->uio_resid += cc;
		uio->uio_offset -= cc;
	}
	/*
	 * This can only occur if FLUSHO
	 * is also set in t_flags.
	 */
	/*
	 *  The QVSS driver (for example) completely empties the output queue
	 *  without bothering with interrupts when the start routine is called.
	 *  Thus, we need to do this here rather than below so that a return
	 *  with the high-water mark no longer exceeded will not block the
	 *  process on an empty output queue.
	 */
	ttstart(tp);
	if (tp->t_outq.c_cc <= hiwat) {
		splx(s);
		goto loop;
	}
	if (tp->t_state&TS_NBIO) {
		splx(s);
		if (uio->uio_resid == cnt)
			return (EWOULDBLOCK);
		/*  Bug fix  -- BOGUS */
		splx(s);
		return (0);
	}
	tp->t_state |= TS_ASLEEP;
	sleep((caddr_t)&tp->t_outq, TTOPRI);
	splx(s);
	goto loop;
}

/*
 * Rubout one character from the rawq of tp
 * as cleanly as possible.
 */
ttyrub(c, tp)
	register c;
	register struct tty *tp;
{
	register char *cp;
	register int savecol;
	int s;
	char *nextc();
#ifdef  luna
	register struct jterm *jp = &tp->t_jt;
#endif  luna

	if ((tp->t_flags&ECHO) == 0)
		return;
	tp->t_flags &= ~FLUSHO;
	c &= 0377;
	if (tp->t_flags&CRTBS) {
		if (tp->t_rocount == 0) {
			/*
			 * Screwed by ttwrite; retype
			 */
			ttyretype(tp);
			return;
		}
#ifdef  luna
		/* 2byete code  erase KOI 89.1.30 */
		if((jp->j_flg & CONVTOEXT) &&
		   ((c&0xff) >= H_K_S) &&
		   ((c&0xff) <= _2_E)) {
		    /* 0xXXa0 - 0xXXfe */
		    c = unputc(&tp->t_rawq);
		    if((c&0xff) == H_K_1) {
			ttyrubo(tp, 1);
		    } else if((((c&0xff) >= _1_S) &&
			       ((c&0xff) <= _1_E))||
			      (((c&0xff) >= G_1_S) &&
			       ((c&0xff) <= G_1_E))) {
			ttyrubo(tp, 2);
		    } else {
			putc(c, &tp->t_rawq);
			tp->t_rocount++;
			ttyrubo(tp, 1);
		    }
		    goto rubend;
		}
#endif  luna
		if (c == ('\t'|0200) || c == ('\n'|0200))
			ttyrubo(tp, 2);
		else switch (partab[c&=0177]&0177) {

		case ORDINARY:
			if (tp->t_flags&LCASE && c >= 'A' && c <= 'Z')
				ttyrubo(tp, 2);
			else
				ttyrubo(tp, 1);
			break;

		case VTAB:
		case BACKSPACE:
		case CONTROL:
		case RETURN:
			if (tp->t_flags&CTLECH)
				ttyrubo(tp, 2);
			break;

		case TAB:
			if (tp->t_rocount < tp->t_rawq.c_cc) {
				ttyretype(tp);
				return;
			}
			s = spltty();
#ifdef luna
			savecol = (u_char)tp->t_col;
#else luna
			savecol = tp->t_col;
#endif luna
			tp->t_state |= TS_CNTTB;
			tp->t_flags |= FLUSHO;
			tp->t_col = tp->t_rocol;
			cp = tp->t_rawq.c_cf;
			for (; cp; cp = nextc(&tp->t_rawq, cp))
				ttyecho(*cp, tp);
			tp->t_flags &= ~FLUSHO;
			tp->t_state &= ~TS_CNTTB;
			splx(s);
			/*
			 * savecol will now be length of the tab
			 */
#ifdef luna
			savecol -= (u_char)tp->t_col;
#else luna
			savecol -= tp->t_col;
#endif luna
			tp->t_col += savecol;
			if (savecol > 8)
				savecol = 8;		/* overflow screw */
			while (--savecol >= 0)
				(void) ttyoutput('\b', tp);
			break;

		default:
			panic("ttyrub");
		}
	} else if (tp->t_flags&PRTERA) {
		if ((tp->t_state&TS_ERASE) == 0) {
			(void) ttyoutput('\\', tp);
			tp->t_state |= TS_ERASE;
		}
		ttyecho(c, tp);
	} else
		ttyecho(tp->t_erase, tp);
#ifdef  luna
    rubend:
#endif  luna
	tp->t_rocount--;
}

/*
 * Crt back over cnt chars perhaps
 * erasing them.
 */
ttyrubo(tp, cnt)
	register struct tty *tp;
	int cnt;
{
	register char *rubostring = tp->t_flags&CRTERA ? "\b \b" : "\b";

	while (--cnt >= 0)
		ttyout(rubostring, tp);
}

/*
 * Reprint the rawq line.
 * We assume c_cc has already been checked.
 */
ttyretype(tp)
	register struct tty *tp;
{
	register char *cp;
	char *nextc();
	int s;

	if (((unsigned)tp->t_rprntc & 0377) != 0377)
		ttyecho(tp->t_rprntc, tp);
	(void) ttyoutput('\n', tp);
	s = spltty();
	for (cp = tp->t_canq.c_cf; cp; cp = nextc(&tp->t_canq, cp))
		ttyecho(*cp, tp);
	for (cp = tp->t_rawq.c_cf; cp; cp = nextc(&tp->t_rawq, cp))
		ttyecho(*cp, tp);
	tp->t_state &= ~TS_ERASE;
	splx(s);
	tp->t_rocount = tp->t_rawq.c_cc;
	tp->t_rocol = 0;
}

/*
 * Echo a typed character to the terminal
 */
ttyecho(c, tp)
	register c;
	register struct tty *tp;
{

	if ((tp->t_state&TS_CNTTB) == 0)
		tp->t_flags &= ~FLUSHO;
	if ((tp->t_flags&ECHO) == 0)
		return;
	c &= 0377;
	if (tp->t_flags&RAW) {
		(void) ttyoutput(c, tp);
		return;
	}
	if (c == '\r' && tp->t_flags&CRMOD)
		c = '\n';
#ifdef luna
    if (!(c & 0200)) {
#endif luna
	if (tp->t_flags&CTLECH) {
		if ((c&0177) <= 037 && c!='\t' && c!='\n' || (c&0177)==0177) {
			(void) ttyoutput('^', tp);
			c &= 0177;
			if (c == 0177)
				c = '?';
			else if (tp->t_flags&LCASE)
				c += 'a' - 1;
			else
				c += 'A' - 1;
		}
	}
#ifdef luna
    } 
#endif luna
#ifdef  luna
	(void) ttyoutput(c, tp);
#else  !luna
	/*
	 * Do not echo non-printing control characters.  Mainly
	 * to stop causing special actions on most terminals.
	 */
	c &= 0177;
	if ((040 <= c && c <= 0176) || (07 <= c && c <= 012) || c == 015)
	    (void) ttyoutput(c, tp);
#endif !luna
}

/*
 * Is c a break char for tp?
 */
ttbreakc(c, tp)
	register c;
	register struct tty *tp;
{
#if	defined(ibmrt)
	/*
	 *  Quoted characters should not match any EOF or break characters.
	 *  This will normally be a problem only on the RT where these
	 *  character values are not sign-extended when compared from the tty
	 *  structure.  In particular, an undefined break character of 0377 in
	 *  the structre will cause a quoted DELETE (0200 + 0177) to improperly
	 *  act as a break character
	 */
	if ((c&0200) != 0)
		return(0);
#endif	defined(ibmrt)
	return (c == '\n' || c == tp->t_eofc || c == tp->t_brkc ||
		c == '\r' && (tp->t_flags&CRMOD));
}

/*
 * send string cp to tp
 */
ttyout(cp, tp)
	register char *cp;
	register struct tty *tp;
{
	register char c;

	while (c = *cp++)
		(void) ttyoutput(c, tp);
}

ttwakeup(tp)
	struct tty *tp;
{

	if (tp->t_rsel) {
		selwakeup(tp->t_rsel, tp->t_state&TS_RCOLL);
		tp->t_state &= ~TS_RCOLL;
		tp->t_rsel = 0;
	}
	if (tp->t_state & TS_ASYNC)
		gsignal(tp->t_pgrp, SIGIO); 
	wakeup((caddr_t)&tp->t_rawq);
}

#ifdef	luna
j_init(tp)
register struct tty *tp;
{
	register i;
	static gset = 0;

	if (!gset) {		/* sift JIS gaiji address table set */
		int i;
		unsigned char c1, c2;

		for (i = 0, c1 = SJISG1S, c2 = SJISG2S; i < SJISGAS; i++) {
			g_sjis[i] = (c1 << 8) + c2;
			c2++;
			if (c2 == 0x7f)
				c2++;
			if (c2 == SJISG2E + 1) {
				c2 = SJISG2S;
				c1++;
			}
	
			if (c1 > SJISG1E)
				break;
		}
	gset = 1;
	}

	tp->t_jt.j_level = 0;
	tp->t_jt.j_flg = 0;
	tp->t_jt.j_ecode = 0;
	tp->t_jt.j_jstl = 0;
	tp->t_jt.j_jendl = 0;
	tp->t_jt.j_gdspl = 0;
	tp->t_jt.j_gcsa[0] = 0;
	tp->t_jt.j_gcsa[1] = 0;
	tp->t_jt.j_firstcode = 0;
	tp->t_jt.outputp = 0;
	tp->t_jt.firstbyte = 0;
	tp->t_jt.kesccount = 0;
	tp->t_jt.inputconv = 0;
	tp->t_jt.eschit = 0;
	tp->t_jt.kesctime = 0;
	tp->t_jt.inputaddr[0] = 0;
	tp->t_jt.inputaddr[1] = 0;
	tp->t_jt.kana = 0;
	for ( i = 0; i < EMAX; i++) {
		tp->t_jt.j_jst[i] = 0;
		tp->t_jt.j_jend[i] = 0;
		tp->t_jt.j_gdsp[i] = 0;
	}

}

#define OUT_OF_JIS(x)   (x < JIS1S || JIS1E < x)
#define OUT_OF_SJIS1(x) (x < SJISH1S || (SJISH1E < x && x < SJISL1S) || SJISL1E < x)
#define OUT_OF_SJIS2(x) (x < SJIS2S || SJIS2E < x || x == 0x7f)
#undef OUT_OF_UJIS
#define OUT_OF_UJIS(x)  (x < _1_S || _1_E < x)
#define IS_SJIS_GAIJI(x)        (SJISG1S <= x && x <= SJISG1E)
#define IS_UJIS_GAIJI1(x)       (G_1_S <= x && x <= G_1_E)
#define KESC    (jp->kesccount)
#define min3(min,x,y,z) { min = (int) (((int) x <= (int) y) ? (int) x : (int) y);\
                          min = (int) (((int) min <= (int) z) ? (int) min : (int) z); }
inputconvert(c, jp)
register unsigned c;
struct jterm *jp;
{
	register int i;
	short miniesc;
	unsigned char c1, c2;
	int retval = 0;

	c &= 0xff;

	if (jp->j_ecode == SJIS)
		goto shiftjis;
	if (jp->j_ecode == UJIS)
		goto ujis;
	if(jp->kesctime == 2) { /* KOIZUMI 1.10 */
		jp->kesctime = 0;
		jp->outputp = 0;
		jp->eschit = 0;
		KESC = 0;
		return(3);
	}
re_enter :
	if (c == jp->j_jst[KESC]) {
		jp->kescinput[KESC] = c;
		if (!KESC)
			jp->eschit |= KANJI;
	} else
		jp->eschit &= ~KANJI;
#ifdef notuse
	if (c == jp->j_gdsp[KESC]) {
		jp->kescinput[KESC] = c;
		if (!KESC)
			jp->eschit |= GAIJI;
	} else
		jp->eschit &= ~GAIJI;
#endif notuse
	if (c == jp->j_jend[KESC]) {
		jp->kescinput[KESC] = c;
		if (!KESC)
			jp->eschit |= JEND;
	} else
		jp->eschit &= ~JEND;
	if (jp->eschit)
		KESC++;
	else if (KESC) {
		retval = 2;
		for (i = 0; i < KESC; i++)
			jp->outputbuf[jp->outputp++] = jp->kescinput[i];
		KESC = 0;
		goto re_enter;
	}
	if ((KESC == jp->j_jstl) && (jp->eschit & KANJI)) {
		for (i = 0; i < KESC; i++)
			jp->outputbuf[jp->outputp++] = jp->kescinput[i];
		jp->inputconv = KANJI;
		jp->eschit = 0;
		KESC = 0;
		return(0);
	}
#ifdef notuse
	else if (KESC == jp->j_gdspl && (jp->eschit & GAIJI))
		jp->inputconv = GAIJI;
#endif notuse
	else if (KESC == jp->j_jendl && (jp->eschit & JEND)) {
		for (i = 0; i < KESC; i++)
			jp->outputbuf[jp->outputp++] = jp->kescinput[i];
		jp->inputconv = 0;
		jp->firstbyte = 0;
		jp->eschit = 0;
		KESC = 0;
		return(0);
	}
	if (KESC) {
		if(retval == 2)
			return(2);
		else
			return(0);
	}

	if (jp->inputconv) {
		if (OUT_OF_JIS(c))
			return(-1);

		jp->localbuf[jp->firstbyte++] = c;
		if (jp->firstbyte == 1)
			return(0);

		if (jp->inputconv == KANJI) {
			jp->localbuf[0] |= 0x80;
			jp->localbuf[1] |= 0x80;
		} else {
		/* gaiji convert */
#ifdef notuse
			unsigned char g1, g2, gcsa1, gcsa2;
			int l;

			if (OUT_OF_JIS(jp->j_gcsa[0]) || OUT_OF_JIS(jp->j_gcsa[1])) {
				goto drain;
			}
			g1 = jp->localbuf[0];
			g2 = jp->localbuf[1];
			gcsa1 = jp->j_gcsa[0];
			gcsa2 = jp->j_gcsa[1];
			if (g1 < gcsa1 || (g1 == gcsa1 && g2 < gcsa2))
				l = (JIS1E - gcsa1) * (JIS1E - JIS1S + 1) + (JIS1E - gcsa2)
					 + (g1 - JIS1S) * (JIS1E - JIS1S + 1)
						+ (g2 - JIS1S +1);
			else
				if (g1 == gcsa1)
					l = g2 - gcsa2;
				else
					l = (g1 - gcsa1 - 1) * (JIS1E - JIS1S + 1)
						+ (JIS1E - gcsa2) + (g2 - JIS1S + 1);
			if (l >= (_1_E - _1_S + 1) * (G_1_E - G_1_S + 1)) {
				l %= (_1_E - _1_S + 1) * (G_1_E - G_1_S + 1);
				l++;
			}
			for (g1 = G_1_E; ; )
				if (l <= _1_E - _1_S) {
					g2 = G_1_E - l;
					break;
				} else {
					l -= _1_E - _1_S + 1;
					g1--;
				}
			jp->localbuf[0] = g1;
			jp->localbuf[1] = g2;
#endif notuse
		return(-1);
		}
		goto drain;
	} else {
		if(retval == 2)
			return(3);
		else
			return(-1);
	}
	
shiftjis :
	if (!jp->firstbyte) {
		jp->localbuf[jp->firstbyte++] = c;
		if (OUT_OF_SJIS1(c)) {
			return(-1);
		}
		return(0);
	}
	if (OUT_OF_SJIS2(c)) {
		jp->firstbyte = 0;
		return(-1);
	}
	jp->localbuf[jp->firstbyte++] = c;
	c1 = jp->localbuf[0];
	c2 = jp->localbuf[1];
	if (IS_SJIS_GAIJI(c1)) {
#ifdef notuse
		int l, ls, s;
		l = sjisgbsearch(c1, c2);
		ls = sjisgbsearch(jp->j_gcsa[0], jp->j_gcsa[1]);
		if (l != -1 && ls != -1) {
			
			s = l - ls;
			if (s < 0)
				s += SJISGAS;
			c1 = G_1_S + s / (G_2_E - G_2_S + 1);
			c2 = G_2_S + s % (G_2_E - G_2_S + 1);
			jp->localbuf[0] = G_1_E - (c1 - G_1_S);
			jp->localbuf[1] = G_2_E - (c2 - G_2_S);
		}
#endif notuse
		return(-1);
	} else {
		if (c1 <= SJISH1E) {
			if (c2 <= 0x9e) {
				jp->localbuf[0] = c1 * 2 - 0x61;
				if (c2 <= 0x7e)
					jp->localbuf[1] = c2 + 0x61;
				else
					jp->localbuf[1] = c2 + 0x60;
			} else {
				jp->localbuf[0] = c1 * 2 - 0x60;
				jp->localbuf[1] = c2 + 0x2;
			}
		} else {
			if (c2 <= 0x9e) {
				jp->localbuf[0] = c1 * 2 - 0xe1;
				if (c2 <= 0x7e)
					jp->localbuf[1] = c2 + 0x61;
				else
					jp->localbuf[1] = c2 + 0x60;
			} else {
				jp->localbuf[0] = c1 * 2 - 0xe0;
				jp->localbuf[1] = c2 + 0x2;
			}
		}
	}
	goto drain;

ujis :
	if (!jp->firstbyte) {
		jp->localbuf[jp->firstbyte++] = c;
		if (OUT_OF_UJIS(c)) {
			return(-1);
		}
		return(0);
	}

	if (OUT_OF_UJIS(c)) {
		jp->firstbyte = 0;
		return(-1);
	}
	jp->localbuf[jp->firstbyte++] = c;
	if (IS_UJIS_GAIJI1(jp->localbuf[0])) {
#ifdef notuse
		c1 = jp->localbuf[0];
		c2 = jp->localbuf[1];
		jp->localbuf[0] = G_1_E - (c1 - G_1_S);
		jp->localbuf[1] = G_2_E - (c2 - G_2_S);
#endif notuse
		return(-1);
	}
	goto drain;
drain :
	for (i = 0; jp->firstbyte != 0; jp->firstbyte--) {
		jp->outputbuf[jp->outputp++] = jp->localbuf[i++];
	}
	return(1);
}


/*
 * Search shift jis gaiji address table
 */

sjisgbsearch(c1, c2)
unsigned char c1, c2;
{
	union {
		unsigned short cc;
		unsigned char c[2];
	} code;
	int t_start, t_end, i, x;

	if (!IS_SJIS_GAIJI(c1) || OUT_OF_SJIS2(c2))
		return(-1);

	code.c[0] = c1;
	code.c[1] = c2;

	if (!g_sjis[0])
		return(-1);
	for (i = SJISGAS/2, t_start = 0, t_end = SJISGAS; ; ) {
		if (code.cc == g_sjis[i])
			return(i);
		if (code.cc <= g_sjis[i]) {
			t_end = i;
			x = 0;
		} else {
			t_start = i;
			x = 1;
		}
		i = (t_end + t_start + x) / 2;
	}
}
#endif	luna
