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
 * $Log:	tty_cmupty.c,v $
 * Revision 2.14  91/06/17  20:46:48  berman
 * 	Added a flag to ptyread() to record whether TS_CARR was being
 * 	turned off intentionally by the driver before a read.  This flag
 * 	is then used to guard the resetting of TS_CARR and clearing of
 * 	error after the ttread().  Makes FIONBIO work on ptys.
 * 	[91/06/11            berman]
 * 
 * Revision 2.13  91/04/03  13:03:22  mbj
 * 	Omron changes[sic]
 * 
 * Revision 2.12  91/02/04  10:25:25  berman
 * 	Fixed ptycselect() to return that it is available for writing if the
 * 	slave is in cooked mode and its canonical queue is empty.  Also
 * 	fixed ptyfill() to use the data passed to it when the input queue of
 * 	the slave is full.  This allows l_rint routine (ttyinput) to handle
 * 	overflow and/or editting characters.
 * 	[91/02/04  08:05:27  dlc]
 * 
 * Revision 2.11  90/07/03  16:33:01  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  17:49:33  mrt]
 * 
 * Revision 2.10  89/11/20  11:37:00  mja
 * 	Added ttyflush() call at end of ptycopen() to remove any
 * 	left-over output from the queues.  Also added a wakeup at the
 * 	end of ptyclose to kick any open()s that are hung.
 * 	[89/11/15            berman]
 * 
 * Revision 2.9  89/07/11  13:13:03  jjc
 * 	Rewrote if statement in ptycioctl() to get around Sun 4
 * 	compiler/assembler problem.
 * 	[89/04/20            jjc]
 * 
 * Revision 2.8  89/03/09  19:31:54  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/26  11:27:18  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:33:36  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/23  22:08:08  af
 * 	GNU: work aroung compiler bug.
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  89/01/23  15:25:51  rvb
 * 	GNU: work aroung compiler bug.
 * 	[89/01/09            rvb]
 * 
 * Revision 2.3  88/12/19  12:48:47  mja
 * 	Increase NPTY from 32 to 64.
 * 	[88/10/14  16:23:37  mja]
 * 
 * 13-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Corrected bug in TIOCATTACH which treated TLC_DETACH as only a
 *	"short" type when it is actually a "long" type.
 *	[ V5.1(XF24) ]
 *
 * 09-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Replace internal uses of PTYLOGGEDIN bit with new common
 *	TS_LOGGEDIN terminal state bit.
 *	[ V5.1(XF23) ]
 *
 * 27-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: select routines really do have to check whether the
 *	thread is waiting.  Pointer to select()'ing thread could be
 *	non-zero from the last time a select was done.
 *
 * 18-Sep-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Corrected residual bug from 4.2 conversion in ttioctl() usage
 *	to adhere to the standard of first invoking the line discipline
 *	specific handler followed by the generic ttioctl() handler if
 *	that fails.
 *	[ V5.1(XF16) ]
 *
 * 15-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: De-linted.
 *
 * 14-Jul-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Flush 4.1 compatibility code.
 *	[ V5.1(XF13) ]
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for multiple threads.
 *
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed to use new TS_LOGGEDIN bit in ptycclose() to adjust
 *	PTYLOGGEDIN bit.
 *	[ V5.1(F1) ]
 *
 * 29-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed a missing CS_COMPAT conditional for t_chan field of tty
 *	structure.
 *
 * 10-Sep-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added support for select() and NBIO on control file;  added new control
 *	ioctl() calls to return logical device unit of application file and to
 *	disable all application ioctl() forwarding.
 *
 * 02-May-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Moved NPTY definition here from cmupty.h to avoid conflicts
 *	with configuration symbol in "other" pty driver.
 *
 * 21-Feb-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed bug which neglected to wake select()'ing process when
 *	the terminal output queue drains below the low water mark.
 *
 * 16-Nov-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed off by one error in check against NSIG.
 *
 * 15-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Changed to accept new uniform TIOCCSET,
 *	TIOCCLOG, TIOCCHECK and TIOCATTACH calls.
 *	[V1(1)]
 *
 * 19-Nov-84  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added support for detached pseudo terminals - a new table
 *	'pty_lctrl' maps the minor device number of the control file to
 *	the appropriate 'pty_ctrl' table entry (this provides the
 *	necessary level of indirection for detach/attach), the driver
 *	now (temporarily) interprets the Front End FEIOCCLOG,
 *	FEIOCCSET, FEIOCCHECK and FEIOCATTACH calls, ptycopen() and the
 *	PIOCCONN call now only allocate a control file if it is not in
 *	use and also not logged-in, ptycclose() no longer attempts to
 *	kill off all processes on its associated application
 *	terminal(s) but instead simply marks them as detached,
 *	ptyopen() avoids waiting for a control reply if the terminal is
 *	detached (e.g. so that /etc/getty can open the terminal to show
 *	it logged- out); added new PIOMGET ioctl call to return the
 *	current status bits and new ATTACHMSG to notify the control
 *	process when a terminal is attached; fixed PIOCXIOC call to
 *	correct save and restore CARR_ON bit (V3.07l).
 *
 * 10-May-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed synchronization bugs in ptyopen(), ptyclose() and
 *	ptyioctl() where application process was blocked at
 *	interruptable priority awaiting reply from control process with
 *	various "in progress" flags set.  If the application process was
 *	interrupted at this point, the "in progress" flag would remain set
 *	causing problems on the next attempt to synchronize with the
 *	control process.  Fixed to use tsleep() to catch signal
 *	and clear flag before processing it (V3.06j).
 *
 * 30-Mar-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added PIOCSLOC call to set the terminal location information;
 *	added clearing of terminal location in ptycclose();
 *	added npty definition for cdevsw[] (V3.06h).
 *
 * 10-Aug-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added PIOCMBIS and PIOCMBIC ioctl calls to set/clear bits in
 *	status (mode) word;  changed PIOCCCMSG, PIOCNOCCMSG,
 *	PIOCSIM and PIOCNOSIM to all use this new interface internally
 *	for adjusting the mode bits;  added new PTYHOLDSIG mode to disable
 *	resetting of signal after sending (for use with SIGHOLD), new
 *	PTYNEWSIG mode to cause interrupted control reads to return a
 *	byte count of 1 rather than restarting and new PTYNOBLOCK mode
 *	which allows control reads to return 0 without blocking if there
 *	is nothing to be read (V3.05e).
 *
 * 29-Jun-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added PIOCENBS and FIONREAD control ioctl calls; fixed minor bug in
 *	multiplex polling in ptycread(); removed obsolete optimization
 *	in ptyfill() which failed to call the line discipline input
 *	routine when in RAW mode (V3.05b).
 *
 * 13-Apr-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed BUFSIZ from 512 to 256 to reduce stack space
 *	consumption (V3.04f).
 *
 * 19-Oct-81  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed bug which neglected to notify multiplexor on wakeups of rawq
 *	for joined ptys (V3.02d).
 *
 * 21-Aug-81  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded for 4.1BSD by changing argument order to ttioctl()
 *	routine and renaming cmupty... (V3.00).
 *
 * 15-Oct-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed to support control of multiple pty terminals from one
 *	line; modified to hang only on open() if there is no open
 *	control line; added passing of arguments and error replies;
 *	added setting of EOF and sending signals from control end;
 *	implemented exact read lengths and input count quota messages
 *	(V1.09h).
 *
 * 05-Jun-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created (V1.08).
 *
 */
/*
 *  Pseudo terminal driver
 */

#include <cmupty.h>

#if	NCMUPTY > 0
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/proc.h>
#include <sys/cmupty.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/acct.h>
#include <kern/thread.h>
 
/*
 *  This driver predates the pseudo-terminal driver which eventually found its
 *  way into the Berkeley system and preempted the 'pty' prefix.  In order to
 *  co-exist with it, we rename all global symbols here to avoid conflicts.
 */
#define npty	   ncmupty
#define pty_tty	   cmupty_tty
#define pty_ctrl   cmupty_ctrl
#define pty_lctrl  cmupty_lctrl
#define ptycclose  cmuptycclose
#define ptycioctl  cmuptycioctl
#define ptycopen   cmuptycopen
#define ptycread   cmuptycread
#define ptycselect cmuptycselect
#define ptycwrite  cmuptycwrite
#define ptyclose   cmuptyclose
#define ptyempty   cmuptyempty
#define ptyfill    cmuptyfill
#define ptyinit	   cmuptyinit
#define ptyioctl   cmuptyioctl
#define ptyopen	   cmuptyopen
#define ptyread	   cmuptyread
#define ptystart   cmuptystart
#define ptywait    cmuptywait
#define ptywrite   cmuptywrite

#undef	NPTY
#define NPTY	64

#define BUFSIZ	 256
#define MINCOUNT (sizeof(struct ptymsg) + sizeof (struct sgttyb))


int	ptystart();

struct tty pty_tty[NPTY];
struct ptyctrl pty_ctrl[NPTY];
struct ptyctrl *pty_lctrl[NPTY] = {0};
int npty = NPTY;



/*
 *  Macro used to invoke once-only initialization of data structures in the
 *  control and application open routines.  This insures that all non-zero
 *  fields of any related data structures are initialized appropriately before
 *  they will be used.  When the initialization routine is called, the pointer
 *  tested by this macro will be initialized, causing the test to always fail
 *  thereafter.
 */

#define ptyonce()		\
{				\
    if (pty_lctrl[0] == 0)	\
	ptyinit();		\
}



/*
 *  ptyinit - once-only initialization
 *
 *  - Establish the default mappings between the minor devices of the control
 *  file and the application terminals (this is initially an identity mapping
 *  but may change when terminals become detached from their original control
 *  file).
 *  - Initialize the 'mdev' and 'ldev' fields of the control structure and the
 *  'oproc' and 'iproc' fields of the terminal structure.
 *  - Show the terminal location for each terminal as "unknown".
 */

ptyinit()
{
    register int i;

    for (i=0; i<NPTY; i++)
    {
	register struct ptyctrl *cp;
	register struct tty *tp;

	cp = &pty_ctrl[i];
	/*
	 *  The first execution of the following statement fulfills the once-
	 *  only criteria so that this routine will never be invoked again.
	 */
	pty_lctrl[i] = cp;
	cp->pt_cpty = cp;
	cp->pt_ldev = i;
	cp->pt_mdev = i;
	tp = &pty_tty[i];
	tp->t_oproc = ptystart;
	tp->t_ttyloc.tlc_hostid = TLC_UNKHOST;
	tp->t_ttyloc.tlc_ttyid = TLC_UNKTTY;
    }
}



/*ARGSUSED*/
ptyopen(d, flag)
{
	register struct tty *tp;
	register dev;
	register struct ptyctrl *cp;
	int error = 0;
 
	dev = minor(d);
	if (dev >= NPTY)
		return(ENXIO);
	ptyonce();
	cp = &pty_ctrl[dev];
	tp = &pty_tty[dev];
	tp->t_state |= TS_WOPEN;
	while (cp->pt_state&(OPENINPROG|CLOSEINPROG))
		sleep((caddr_t)&cp->pt_openbuf, TTIPRI);
	if ((tp->t_state & TS_ISOPEN) == 0) {
		ttychars(tp);
		tp->t_ispeed = tp->t_ospeed = EXTB;
		tp->t_flags = ODDP|EVENP|XTABS|ECHO;
#ifdef  luna
		j_init(tp);
#endif  luna
	} else if (tp->t_state&TS_XCLUDE && u.u_uid != 0) {
		error = EBUSY;
		goto out;
	}
	tp->t_dev = d;
	if ((cp->pt_state&PTYDETACHED) == 0)
	{
	    cp->pt_state |= (OPENINPROG|OPENFLG);
	    ptystart(tp);
	    cp->pt_openbuf = (u.u_ap[1]);
	    ptywait(&(cp->pt_state), OPENINPROG, &(cp->pt_openbuf));
	    if (error=cp->pt_openbuf)
		goto out;
	}
	(*linesw[tp->t_line].l_open)(d, tp);
	tp->t_state |= TS_CARR_ON;
out:
	tp->t_state &= ~TS_WOPEN;
	return(error);
}
 
ptyclose(d)
{
	register struct tty *tp;
	register struct ptyctrl *cp;
	register dev;
 
	dev = minor(d);
	cp = &pty_ctrl[dev];
	tp = &pty_tty[dev];
	ttywflush(tp);
	while (cp->pt_state&(CLOSEINPROG))
		sleep((caddr_t)&cp->pt_closebuf, TTIPRI);
	if (cp->pt_state&PTYINUSE)
	{
	    cp->pt_state |= (CLOSEINPROG|CLOSEFLG);
	    ptystart(tp);
	    ptywait(&(cp->pt_state), CLOSEINPROG, &(cp->pt_closebuf));
	}
	(*linesw[tp->t_line].l_close)(tp);
	ttyclose(tp);
	wakeup((caddr_t)&cp->pt_openbuf);
}
 
ptyread(d, uio)
	struct uio *uio;
{
	register int md;
	register int cnt;
	register struct tty *tp;
	register struct ptyctrl *cp;
	int carrier_state = 0;
	int error = 0;
 
	md = minor(d);
	cnt = uio->uio_resid;
	tp = &pty_tty[md];
	cp = &pty_ctrl[md];

	do
	{
	    if ((cp->pt_state&PTYEOF) && tp->t_rawq.c_cc == 0)
	    {
		cp->pt_state &= ~PTYEOF;
		carrier_state = tp->t_state & TS_CARR_ON;
		tp->t_state &= ~TS_CARR_ON;
	    }
	    if (error=(*linesw[tp->t_line].l_read)(tp, uio))
	    {
		if (uio->uio_resid == cnt &&
		    (cp->pt_state&PTYINUSE) &&
		    carrier_state)
		{
		    tp->t_state |= TS_CARR_ON;
		    carrier_state = 0;
		    error = 0;
		}
		break;
	    }
	    if (cp->pt_state&PTYCCMSG)
	    {
		cp->pt_state |= CCFLG;
		ptystart(tp);
	    }
	} while ((cp->pt_state&PTYSIM) && uio->uio_resid && error == 0);
	return(error);
}
 
ptywrite(d, uio)
	struct uio *uio;
{
	register struct tty *tp;
	register struct ptyctrl *cp;
	register int carr_on;
	int error;

	tp = &pty_tty[minor(d)];
	cp = &pty_ctrl[minor(d)];
	if (cp->pt_state&PTYINUSE)
	{
		carr_on = (tp->t_state^TS_CARR_ON)&TS_CARR_ON;
		tp->t_state |= TS_CARR_ON;
	}
	else
		carr_on = 0;
	error = (*linesw[tp->t_line].l_write)(tp, uio);
	tp->t_state ^= carr_on;
	return(error);
}
 
 
/*ARGSUSED*/
ptyioctl(dev, cmd, data, flag)
	caddr_t data;
	dev_t dev;
{
	register md;
	register struct tty *tp;
	register struct ptyctrl *cp;
 	ptioctlbuf_t ioctlbuf;
	int buflen;
 
	md = minor(dev);

	tp = &pty_tty[md];
	cp = &pty_ctrl[md];
	/*
	 *  Handle pseudo terminal specific ioctl calls for attaching/detaching
	 *  terminals.  By historical accident, these calls are all defined by
	 *  the Front End driver.  This should be cleaned up someday.
	 */
	switch (cmd)
	{
	    /*
	     *  Send HANGUP to process group on detach condition.
	     */
	    case TIOCCSET:
	    {
		if (*((int *)data)&CDETHUP)
		    cp->pt_state |= PTYDETHUP;
		else
		    cp->pt_state &= ~PTYDETHUP;
		break;
	    }

	    /*
	     *  Change logged-in state.
	     */
	    case TIOCCLOG:
	    {
		if (!suser())
		    return(EPERM);
	        cp->pt_state &= ~PTYDETHUP;	/* implicit reset */
		if (*((int *)data))
		{
		    tp->t_state |=  TS_LOGGEDIN;
		}
		else
		{
		    /*
		     *  We may have allowed an open to complete without a
		     *  listening control file so encourage such processes to
		     *  go away if they are now not logged-in by turning off
		     *  the software carrier indication so that all reads will
		     *  return an EOF.
		     */
		    if (cp->pt_state&PTYDETACHED)
		    {
			tp->t_state &= ~TS_CARR_ON;
			ttyflush(tp, (FREAD|FWRITE));
		    }
		    cp->pt_state &= ~(PTYDETACHED);
		    tp->t_state &= ~TS_LOGGEDIN;
		}
		break;
	    }

	    /*
	     *  Check for detached pseudo/terminal or attach to detached
	     *  pseudo-terminal.
	     */
	    case TIOCCHECK:
	    case TIOCATTACH:
	    {
		register struct ptyctrl *dcp;
		register struct tty *dtp;
		register int i;

		i = minor(*((int *)data));
		if (major(*((int *)data)) != major(dev) || i < 0 || i >= NPTY)
		    return(EINVAL);
		dcp = &pty_ctrl[i];
		dtp = &pty_tty[i];
		if ((dcp->pt_state&(PTYDETACHED|PTYINUSE)) == PTYDETACHED)
		{
		    if (cmd == TIOCATTACH)
		    {
			int ldev;
			struct ptyctrl *tcp;

			if (!suser())
			    return(EPERM);
			/*
			 *  Pick up the new terminal location from the current
			 *  application terminal and assign it to the
			 *  application terminal being attached.  The terminal
			 *  location for the current application terminal
			 *  becomes "detached".
		         */
			dtp->t_ttyloc.tlc_hostid = tp->t_ttyloc.tlc_hostid;
			dtp->t_ttyloc.tlc_ttyid = tp->t_ttyloc.tlc_ttyid;
			tp->t_ttyloc.tlc_ttyid = TLC_DETACH;
			/*
			 *  Swap the minor devices associated with each
			 *  affected control file.  The application minor
			 *  device of the detached terminal is connected to the
			 *  minor device of the current control file and the
			 *  application minor device of its present terminal is
			 *  connected to the minor device of the previously
			 *  detached control file.
		         */
			ldev = cp->pt_ldev;
			tcp = pty_lctrl[ldev];
			pty_lctrl[ldev] = pty_lctrl[dcp->pt_ldev];
			cp->pt_ldev = dcp->pt_ldev;
			pty_lctrl[dcp->pt_ldev] = tcp;
			dcp->pt_ldev = ldev;
			/*
			 *  Show the current application terminal now detached
			 *  and prod it in case some other process on the
			 *  terminal is in a control response wait (since there
			 *  is now no longer a control file associated with
			 *  it).
			 */
			cp->pt_state |= PTYDETACHED;
			cp->pt_state &= ~(PTYINUSE|OPENINPROG|CLOSEINPROG|IOCTLINPROG);
			wakeup((caddr_t)&cp->pt_openbuf);
			wakeup((caddr_t)&cp->pt_closebuf);
			wakeup((caddr_t)&cp->pt_ioctlbuf);
			wakeup((caddr_t)&cp->pt_state);
			/*
			 *  Copy the control mode bits and signal status from
			 *  the old terminal, show it now attached and arrange
			 *  to send a notification message.
			 */
			dcp->pt_state &= ~(PTYDETACHED|PTYRWMODES);
			dcp->pt_state |= (PTYINUSE|ATTACHFLG|
					  (cp->pt_state&PTYRWMODES));
			dcp->pt_sigp = u.u_procp;
			dcp->pt_pid  = u.u_procp->p_pid;
			dcp->pt_sign = cp->pt_sign;
			ptystart(dtp);
		    }
		    u.u_r.r_val1 = 1;
		}
		return(0);
		/* can't afford to fall through! */
	    }
	}
	if (cp->pt_state&PTYNOIOCTL)
	    buflen = -1;
	else
	{
	    while (cp->pt_state&(IOCTLINPROG))
		    sleep((caddr_t)&cp->pt_ioctlbuf, TTIPRI);
	    if (cp->pt_state&PTYINUSE)
	    {
		cp->pt_state |= (IOCTLINPROG);
		cp->pt_cmdbuf = cmd;
		bcopy(data, (caddr_t)&cp->pt_ioctlbuf,sizeof(cp->pt_ioctlbuf));
		cp->pt_state |= (IOCTLFLG);
		ptystart(tp);
		ptywait(&(cp->pt_state), IOCTLINPROG,
			 (caddr_t)&(cp->pt_ioctlbuf));
		/*
		 *  Must copy these here before we might block since we have
		 *  already issued the wakeup for any other blocked processes
		 *  which may be waiting within ioctl().  The ttioctl() may be
		 *  interrupted and never return and we need to copy the buffer
		 *  since the copyout() may block on a page fault.
		 */
		buflen = cp->pt_buflen;
		bcopy((caddr_t)&(cp->pt_ioctlbuf), (caddr_t)&ioctlbuf,
			 sizeof ioctlbuf);
	    }
	    else
		buflen = -1;
	}
	if (buflen < 0)
	{
	    int error;

	    error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
	    if (error < 0)
		error = ttioctl(tp, cmd, data, flag);
	    if (error < 0)
	        error = ENOTTY;
	    return(error);
	}
	if (buflen > sizeof ioctlbuf)
	    return(buflen-sizeof ioctlbuf);
	bcopy((caddr_t)&ioctlbuf, data, (unsigned)buflen);
	return(0);
}
 
ptystart(tp)
register struct tty *tp;
{

	register struct ptyctrl *ccp;

	ccp = pty_ctrl[minor(tp->t_dev)].pt_cpty;
	if (ccp->pt_state&OUTPUTWAIT)
	{
		ccp->pt_state &= ~OUTPUTWAIT;
		wakeup((caddr_t)&ccp->pt_cpty);
	}
	else if (ptywread(ccp, tp))
	{
		if (ccp->pt_sign)
		{
			if (ccp->pt_sigp->p_pid == ccp->pt_pid)
				psignal(ccp->pt_sigp, (int)ccp->pt_sign);
			if ((ccp->pt_state&PTYHOLDSIG) == 0)
				ccp->pt_sign = 0;
		}
		if (ccp->pt_rselp)
		{
			selwakeup(ccp->pt_rselp, ccp->pt_state&PTYRSELCOLL);
			ccp->pt_rselp = 0;
			ccp->pt_state &= ~PTYRSELCOLL;
		}
	}

}



/*
 *  Synchronize application and control processes.
 *
 *  Called by application process with flag bit set in state word.
 *  Sleep until flag bit has been cleared by control process (indicating
 *  that the request has been processed) and wake any other blocked
 *  application processes which may be waiting for this flag.
 *  If a signal arrives in the mean time, abort by clearing the
 *  flag, waking other blocked application processes since the
 *  flag is now free and processing the signal.
 */

ptywait(statep, flag, addr)
register int *statep;
int flag;
char *addr;
{
    int rval;

    while ((*statep)&flag)
    {
	rval = tsleep((caddr_t)statep, TTIPRI, 0);
	if (rval == TS_SIG)
	{
	    *statep &= ~flag;
	    wakeup(addr);
	    longjmp(&u.u_qsave);
	}
    }
    wakeup(addr);
}



/* ARGSUSED */
ptycopen(d, flag)
{

	register l;
	register dev;
	register struct tty *tp;
	register struct ptyctrl *ccp;
 
	dev = minor(d);
	if (dev >= NPTY)
		return(ENXIO);
	ptyonce();
	ccp = pty_lctrl[dev];
	tp = &pty_tty[ccp->pt_mdev];
	if ((ccp->pt_state&PTYINUSE) || (tp->t_state&TS_LOGGEDIN))
		return(EBUSY);
	ccp->pt_state |= PTYINUSE;
	ccp->pt_state &= ~(PTYRWMODES);
	ccp->pt_ostate = -1;
	ccp->pt_cpty = ccp;
	ccp->pt_ctrl[0] = ccp;
	ccp->pt_next = 0;
	ccp->pt_high = 0;
	for (l=1; l<NPTYL; l++)
		ccp->pt_ctrl[l] = NULL;
	tp->t_ttyloc.tlc_hostid = TLC_UNKHOST;
	tp->t_ttyloc.tlc_ttyid = TLC_UNKTTY;
	ttyflush(tp, FREAD|FWRITE);
#ifdef  luna
	tp->t_omron |= PTY_TTY;
#endif  luna
	return(0);
}



ptycclose(d)
{

	register int l;
	register struct tty *tp;
	register struct ptyctrl *cp;
	register struct ptyctrl *ccp;
 
	ccp = pty_lctrl[minor(d)];
	for (l=0; l<NPTYL; l++)
	{
		if ((cp=ccp->pt_ctrl[l]) == NULL)
			continue;
		tp = &pty_tty[cp->pt_mdev];
		if ((cp->pt_state&PTYDETHUP) || (tp->t_state&TS_LOGGEDIN) == 0)
		{
		    gsignal(tp->t_pgrp, SIGHUP);
		    ttyflush(tp, (FREAD|FWRITE));
		    tp->t_state &= ~TS_CARR_ON;
		}
		else
		{
		    tp->t_ttyloc.tlc_ttyid = TLC_DETACH;
		}
		cp->pt_state |= (PTYDETACHED);
		cp->pt_state &= ~(PTYINUSE|OPENINPROG|CLOSEINPROG|IOCTLINPROG);
		/*
		 *  Prod the application terminal in case it was waiting for a
		 *  control response.
		 */
		wakeup((caddr_t)&cp->pt_openbuf);
		wakeup((caddr_t)&cp->pt_closebuf);
		wakeup((caddr_t)&cp->pt_ioctlbuf);
		wakeup((caddr_t)&cp->pt_state);
	}
}



/* ARGSUSED */
ptycioctl(dev, cmd, data, flag)
caddr_t data;
dev_t dev;
{
    int sign;
    int mode;
    unsigned l;
    register md;
    register struct tty *tp;
    register struct ptyctrl *cp;
    register struct ptyctrl *ccp;
    struct ptymsg msg;
    int error;
#ifdef	sun4
    int	loggedin;
#endif	sun4

    md = minor(dev);
    ccp = pty_lctrl[md];
    l = cmd&PTYLMASK;
    if (cmd == FIONREAD)
	l = 0;
    else
	cmd &= ~PTYLMASK;
    if (l>ccp->pt_high || (cp=ccp->pt_ctrl[l]) == NULL)
	return(EINVAL);
    tp = &pty_tty[cp->pt_mdev];

    switch(cmd)
    {
	case PIOCCONN:
	    if (l != 0)
		return(EINVAL);
	    for (l=0; l<NPTY; l++)
	    {
		cp = &pty_ctrl[l];
#ifdef	sun4
		/*
		 *	Sun 4 assembler segmentation faults on
		 *	if statement in #else leg below, so I
		 *	rewrote it into something the assembler
		 *	likes better.
		 */
		loggedin = pty_tty[cp->pt_mdev].t_state&TS_LOGGEDIN;
		if ((cp->pt_state&PTYINUSE) || loggedin)
#else	sun4
		if ((cp->pt_state&PTYINUSE)
		    ||
		    (pty_tty[cp->pt_mdev].t_state&TS_LOGGEDIN))
#endif	sun4
		    continue;
		if (ccp->pt_high >= (NPTYL-1))
		    break;
		msg.pt_line = ccp->pt_high+1;
		msg.pt_arg  = l;
		msg.pt_msg  = cmd;
		bcopy((caddr_t)&msg, data, sizeof msg);
		cp->pt_state |= PTYINUSE;
		cp->pt_ostate = -1;
		cp->pt_cpty = ccp;
		ccp->pt_ctrl[++(ccp->pt_high)] = cp;
		return(0);
	    }
	    return(EMFILE);

	case PIOCXIOC:
	{
	    u_int size;
	    char stkbuf[128];	    /* big enuf for essentially everything */
	    caddr_t xdata = stkbuf;
	    caddr_t memp = NULL;
	    caddr_t kalloc();
	    int com;

	    /*
	     *  This call is defined with IOC_VOID so that we can have a handle
	     *  on the actual address supplied by the user program.  The first
	     *  longword at that location is the command to be executed.  The
	     *  remaining words (if any) are the standard parameters for that
	     *  command which must be fetched and set up just as the ioctl()
	     *  system call would before passing them to ttioctl().
	     */
	    data = *((caddr_t *)data);
	    if (error = copyin(data, (caddr_t)&com, sizeof(com)))
		return(error);
	    data += sizeof(com);
	    /*
	     *  Mimic ioctl() code which sets up data area.
	     */
	    size = IOCPARM_LEN(com);
	    if (size > IOCPARM_MAX) 
		return(EFAULT);
	    if (size > sizeof(stkbuf)) {
		memp = kalloc(IOCPARM_MAX);
		if (memp == NULL)
		    panic("cmuptcioctl kalloc");
		xdata = memp;
	    }
	    if (com&IOC_IN)
	    {
		if (size)
		{
		    if (error = copyin(data, xdata, size)) {
			if (memp != NULL)
			    kfree(memp, IOCPARM_MAX);
			return(error);
		    }
		}
		else
		    *(caddr_t *)xdata = data;
	    }
	    else if ((com&IOC_OUT) && size)
	    {
		/*
		 *  ioctl() code does this to always return something
		 *  deterministic.
		 */
		bzero(xdata, size);
	    }
	    else if (com&IOC_VOID)
	    {
		*(caddr_t *)xdata = data;
	    }
	    sign = (tp->t_state^TS_CARR_ON)&TS_CARR_ON;
	    tp->t_state |= TS_CARR_ON;
	    error = (*linesw[tp->t_line].l_ioctl) (tp, com, xdata,
			(FREAD|FWRITE));
	    if (error < 0)
	        error = ttioctl (tp, com, xdata, (FREAD|FWRITE));
	    if (error < 0)
	        error = ENOTTY;
	    tp->t_state ^= sign;
	    /*
	     *  Mimic ioctl() code which returns data area.
	     */
	    if (error == 0 && (com&IOC_OUT) && size)
		error = copyout(xdata, data, size);
	    if (memp != NULL)
		kfree(memp, IOCPARM_MAX);
	    return(error);
	}

	case PIOCSEOF:
	    if (tp->t_rawq.c_cc == 0)
	    {
		tp->t_state &= ~TS_CARR_ON;
		wakeup((caddr_t)&tp->t_rawq);
	    }
	    else
		cp->pt_state |= PTYEOF;
	    break;
	case PIOCDGET:
	{
	    *((int *)data) = (cp->pt_mdev);
	    break;
	}
	case PIOCMGET:
	{
	    /*  Simulate the old PTYLOGGEDIN bit to applications for now  */
	    *((int *)data) = (cp->pt_state&(PTYRWMODES|PTYROMODES))
			     |
			     ((tp->t_state&TS_LOGGEDIN)?PTYLOGGEDIN:0);
	    break;
	}
	case PIOCSIM:		/* obsolete - use PIOCMBIS */
	    mode = PTYSIM;
	    goto ptymbis;
	case PIOCNOSIM:		/* obsolete - use PIOCMBIC */
	    mode = PTYSIM;
	    goto ptymbic;
	case PIOCCCMSG:		/* obsolete - use PIOCMBIS */
	    mode = PTYCCMSG;
	    goto ptymbis;
	case PIOCNOCCMSG:	/* obsolete - use PIOCMBIC */
	    mode = PTYCCMSG;
	    goto ptymbic;
	case PIOCMBIS:
	{
	    mode = *((int *)data);

	    if (mode&~(PTYRWMODES|PTYROMODES))
		return(EINVAL);
	ptymbis:
	    cp->pt_state |= (mode&PTYRWMODES);
	    break;
	}
	case PIOCMBIC:
	{
	    mode = *((int *)data);
	    if (mode&~(PTYRWMODES|PTYROMODES))
		return(EINVAL);
	ptymbic:
	    cp->pt_state &= ~(mode&PTYRWMODES);
	    break;
	}
	case PIOCSSIG:
	    gsignal(tp->t_pgrp, *((int *)data));
	    break;
	case PIOCENBS:
	{
	    int ipl;

	    if (*((u_int *)data) <= NSIG)
	    {
		ipl = spl5();		/* This probably isn't needed */
		cp->pt_sigp = u.u_procp;
		cp->pt_pid  = u.u_procp->p_pid;
		cp->pt_sign = *((u_int *)data);
		splx(ipl);
	    }
	    else
		return(EINVAL);
	    break;
	}
	case PIOCSLOC:
	{
	    tp->t_ttyloc.tlc_hostid = ((struct ttyloc *)data)->tlc_hostid;
	    tp->t_ttyloc.tlc_ttyid = ((struct ttyloc *)data)->tlc_ttyid;
	    break;
	}
	case FIONREAD:
	{
	    int next = ccp->pt_next;
	    int nread = 0;
	    int i;

	    for (i=ccp->pt_high; i-- >= 0; )
	    {
		if (next > ccp->pt_high)
		    next = 0;
		if ((cp=ccp->pt_ctrl[next++]) == NULL)
		    continue;
		tp = &pty_tty[cp->pt_mdev];
		if (nread = ptywread(cp, tp))
		    break;
	    }
	    *((int *)data) = nread;
	    break;
	}
	case FIONBIO:
	{
	    if (*(int *)data)
		cp->pt_state |= PTYNOBLOCK;
	    else
		cp->pt_state &= ~PTYNOBLOCK;
	    break;
	}
	default:
	    return(EINVAL);
    }
    return(0);
}



ptycread(d, uio)
	struct uio *uio;
{
	register l;
	register size;
	register char *addr;
	register struct tty *tp;
	register struct ptyctrl *cp;
	register struct ptyctrl *ccp;
	struct ptymsg msg;

	ccp = pty_lctrl[minor(d)];
	while (uio->uio_resid >= MINCOUNT)
	{
	    int error;

	    msg.pt_arg = size = 0;
	    for (l=ccp->pt_high; l-- >= 0; )
	    {
		if (ccp->pt_next > ccp->pt_high)
			ccp->pt_next = 0;
		msg.pt_line = ccp->pt_next;
		if ((cp=ccp->pt_ctrl[(ccp->pt_next)++]) == NULL)
			continue;
		tp = &pty_tty[cp->pt_mdev];
		if (uio->uio_resid > MINCOUNT)
		{
#ifdef	__GNU__
		 unsigned char tmp = msg.pt_line;
			error = ptyempty(tp, (int)tmp, uio);
#else	__GNU__
			error = ptyempty(tp, (int)msg.pt_line, uio);
#endif	__GNU__
			if (error >= 0)
			    return(error);
		}
		if (cp->pt_state&ATTACHFLG)
		{
			cp->pt_state &= ~ATTACHFLG;
			msg.pt_msg = ATTACHMSG;
			msg.pt_arg = (u_char)cp->pt_mdev;
		}
		else if (cp->pt_state&OPENFLG)
		{
			cp->pt_state &= ~OPENFLG;
			msg.pt_msg = OPENMSG;
			msg.pt_arg = cp->pt_openbuf;
			msg.pt_aux = cp->pt_mdev;
		}
		else if (cp->pt_state&IOCTLFLG)
		{
			cp->pt_state &= ~IOCTLFLG;
			msg.pt_msg = IOCTLMSG;
			addr = (caddr_t)&cp->pt_cmdbuf;
			size = sizeof (cp->pt_ioctlbuf)+ sizeof (cp->pt_cmdbuf);
		}
		else if (cp->pt_state&CLOSEFLG)
		{
			cp->pt_state &= ~CLOSEFLG;
			msg.pt_msg = CLOSEMSG;
			msg.pt_arg = cp->pt_closebuf;
		}
		else if (cp->pt_state&CCFLG)
		{
			cp->pt_state &= ~CCFLG;
			cp->pt_orcc = tp->t_rawq.c_cc;
			msg.pt_msg = CCMSG;
			addr = (caddr_t)&cp->pt_orcc;
			size = sizeof (cp->pt_orcc);
		}
		else if (tp->t_state != cp->pt_ostate)
		{
			cp->pt_ostate = tp->t_state;
			msg.pt_msg = STATEMSG;
			addr = (caddr_t)&cp->pt_ostate;
			size = sizeof (cp->pt_ostate);
		}
		else
		{
			continue;
		}
		error = uiomove((caddr_t)&msg, sizeof msg, UIO_READ, uio);
		if (error == 0)
		    error = uiomove(addr, size, UIO_READ, uio);
		return(error);
	    }
	    if (ccp->pt_state&PTYNOBLOCK)
		return(0);
	    if (ccp->pt_state&PTYNEWSIG)
		uio->uio_resid--;
	    ccp->pt_state |= OUTPUTWAIT;
	    while (ccp->pt_state&OUTPUTWAIT)
		sleep((caddr_t)&ccp->pt_cpty, TTOPRI);
	    if (ccp->pt_state&PTYNEWSIG)
		uio->uio_resid++;
	}
	return(0);
}


ptyempty(atp, l, uio)
	struct tty *atp;
	struct uio *uio;
{
	register cc;
	register struct tty *tp;
	struct {struct ptymsg msg; char wbuf[BUFSIZ];} wmsg;

	tp = atp;
	if (tp->t_state & (TS_TIMEOUT|TS_BUSY|TS_TTSTOP))
		return(-1);
	if (tp->t_outq.c_cc <= TTLOWAT(tp))
	{
 		if (tp->t_state&TS_ASLEEP)
		{
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		if (tp->t_wsel)
		{
			selwakeup(tp->t_wsel, tp->t_state&TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
	}
	if (tp->t_outq.c_cc == 0)
		return(-1);
	wmsg.msg.pt_msg = WRITEMSG;
	wmsg.msg.pt_arg = 0;
	wmsg.msg.pt_line = l;
	cc = q_to_b(&tp->t_outq, wmsg.wbuf, (int)min(BUFSIZ, (u_int)(uio->uio_resid-sizeof wmsg.msg)));
	return(uiomove((caddr_t)&wmsg, sizeof wmsg.msg + cc, UIO_READ, uio));
}


ptycselect(dev, rw)
	dev_t dev;
	int rw;
{
	register struct tty *tp;
	register struct ptyctrl *cp;

	cp = pty_lctrl[minor(dev)];
	tp = &pty_tty[cp->pt_ctrl[0]->pt_mdev];

	switch (rw)
	{
	    case FREAD:
	    {
		int s;

		s = spltty();
		if (ptywdread(tp))
		{
			splx(s);
			return(1);
		}
		splx(s);
		/* fall through */
	    }

	    case 0:
	    {
		if (ptywxread(cp, tp))
			return(1);
		if (cp->pt_rselp &&
			((thread_t)(cp->pt_rselp))->wait_event
				== (int)&selwait)
			cp->pt_state |= PTYRSELCOLL;
		else
			cp->pt_rselp = (struct proc *) current_thread();
		break;
	    }
	
	    case  FWRITE:
	    {
		if ((((tp->t_flags&(RAW|CBREAK))==0?tp->t_canq.c_cc:0)+tp->t_rawq.c_cc) < (TTYHOG-2))
			return(1);
		if (tp->t_canq.c_cc == 0 && (tp->t_flags & (RAW|CBREAK)) == 0)
			return (1);
		if (cp->pt_wselp &&
			((thread_t)(cp->pt_wselp))->wait_event
				== (int)&selwait)
			cp->pt_state |= PTYWSELCOLL;
		else
			cp->pt_wselp = (struct proc *) current_thread();
		break;
	    }
	}
	return(0);
}



ptycwrite(d, uio)
	struct uio *uio;
{

	register struct tty *tp;
	register struct ptyctrl *cp;
	register struct ptyctrl *ccp;
	struct ptyreply msg;

	ccp = pty_lctrl[minor(d)];
	while (uio->uio_resid >= sizeof msg)
	{
		int error;

		error = uiomove((caddr_t)&msg, sizeof msg, UIO_WRITE, uio);
		if (error)
			return(error);
		if (msg.pt_line > ccp->pt_high || (cp=ccp->pt_ctrl[msg.pt_line]) == 0)
			return(EINVAL);
		tp = &pty_tty[cp->pt_mdev];
		switch (msg.pt_reply)
		{
		    case OPENREPLY:
			if (cp->pt_state&OPENINPROG)
			{
			    cp->pt_openbuf = msg.pt_error;
			    cp->pt_state &= ~OPENINPROG;
			    wakeup((caddr_t)&cp->pt_state);
			}
			continue;

		    case CLOSEREPLY:
			if (cp->pt_state&CLOSEINPROG)
			{
			    cp->pt_state &= ~CLOSEINPROG;
			    wakeup((caddr_t)&cp->pt_state);
			}
			continue;

		    case IOCTLREPLY:
		    case IOCTLDATA:
			if (cp->pt_state&IOCTLINPROG)
			{
			    if (msg.pt_reply == IOCTLDATA)
			    {
				if (msg.pt_len > sizeof cp->pt_ioctlbuf)
					return(EINVAL);
				cp->pt_buflen = msg.pt_len;
				error = uiomove((caddr_t)&cp->pt_ioctlbuf, (int)min((u_int)cp->pt_buflen, sizeof cp->pt_ioctlbuf), UIO_WRITE, uio);
				if (error)
					return(error);
			    }
			    else if (msg.pt_error)
				cp->pt_buflen = msg.pt_error + sizeof cp->pt_ioctlbuf;

			    else
				cp->pt_buflen = -1;
			    cp->pt_state &= ~IOCTLINPROG;
			    wakeup((caddr_t)&cp->pt_state);
			}
			continue;

		    case READDATA:
			return(ptyfill(tp, cp, uio));

		    default:
			return(EINVAL);
		}
	}
	return(0);
}


ptyfill(atp, cp, uio)
	struct tty *atp;
	struct ptyctrl *cp;
	struct uio *uio;
{
	register cc;
	register char *rp, *re;
	register struct tty *tp;
	char rbuf[TTYHOG];

	tp = atp;
	while (uio->uio_resid)
	{
		int error;

		cc = min((u_int)uio->uio_resid,
		         (u_int)TTYHOG
				-
				(
			          ((tp->t_flags&(RAW|CBREAK))==0?tp->t_canq.c_cc:0)
				  +
				  tp->t_rawq.c_cc
				));
		if (cc == 0)
		    cc = uio->uio_resid;
		if (cp->pt_state&PTYSIM)
		    cc &= ~(sizeof(struct ptymsg)-1);
		if (cc <= 0)
			return(0);
		re = rbuf + cc;
		error = uiomove(rp=rbuf, cc, UIO_WRITE, uio);
		if (error)
		     return(error);
		while (rp < re)
			(*linesw[tp->t_line].l_rint)(*rp++, tp);
	}
	return(0);
}
#endif	NCMUPTY > 0
