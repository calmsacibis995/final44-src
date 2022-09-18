/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pi.c,v $
 * Revision 2.5  89/07/11  17:39:09  jjc
 * 	Changed to include machine dependent header files from machine/ not sun3/ because the Sun 4 uses this device driver too.
 * 	[89/07/06  16:54:20  jjc]
 * 
 * Revision 2.4  89/03/09  21:44:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:53:25  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.2  88/08/24  02:14:32  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 *
 *  7-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in CS_TTYLOC stuff.
 *
 */


#ifndef	lint
static	char sccsid[] = "@(#)pi.c 1.1 86/02/03 Copyr 1983 Sun Micro";
#endif

#include <pi.h>
/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

/*
 * Parallel Keyboard & Mouse drivers
 * Minor 0 is keyboard, 1 is mouse
 * Turns parallel data into a byte stream to be fed (usually)
 * into the keyboard or mouse line disciplines
 */
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/tty.h>
#include <sys/uio.h>

#include <machine/mmu.h>
#include <machine/scb.h>
#include <sun/consdev.h>
#include <sundev/mbvar.h>
#include <sundev/kbd.h>

/*
 * Driver information for auto-configuration stuff.
 */
int	piprobe();
struct	mb_driver pidriver = {
	piprobe, 0, 0, 0, 0, 0,
	0, "pi", 0, 0, 0, 0,
};

struct tty pitty[2];
#ifdef	MACH
int	nmti = 2;
#endif	MACH

struct pireg {
	u_char	pi_kbd;
	char	pi_mouse;	/* signed mouse delta or buttons */
};
struct pireg *piaddr, pilast;	/* used by low level clock intr */

/*
 * Probe for keyboard and mouse 
 * Diagnostics for unconnected keyboard or unpowered mouse
 */
piprobe(reg, unit)
	caddr_t reg;
	int unit;
{
	register struct pireg *pi;
	register int i;

	if (unit)
		return (0);
	if (peek((short *)reg) == -1)
		return (0);
	pi = (struct pireg *)reg;
	for (i=0; i<100000; i++)
		if (pi->pi_kbd != 0xFF)
			break;
	pitty[0].t_addr = reg;
	pitty[1].t_addr = reg;
	piaddr = pi;
	return (1);
}

/*
 * Open keyboard or mouse - enable call to piintr
 */
/*ARGSUSED*/
piopen(dev, flag)
	dev_t dev;
	int flag;
{
	int clkpiscan();
	register struct tty *tp;
	int pistart();
	register struct pireg *pi;

#ifdef	MACH
	static tlcinit = 0;

	/*
	 *  Initialize terminal locations on first call to driver.
	 */
	if (tlcinit == 0)
	{
		tlcinit++;
		for (unit=0; unit<npi; unit++)
		{
			tp = &pitty[unit];
			tp->t_ttyloc.tlc_hostid = TLC_MYHOST;
			tp->t_ttyloc.tlc_ttyid = unit;
		}
	}
#endif	MACH
 
	if (dev == kbddev && kbddevopen)
		return(0);
	if (minor(dev) > 1)
		return (ENXIO);
	tp = &pitty[minor(dev)];
	if (tp->t_addr == 0)
		return (ENXIO);
	pi = (struct pireg *)tp->t_addr;
	if (minor(dev) == 0 && pi->pi_kbd == 0xFF) 
		printf("keyboard not connected\n");
	if (minor(dev) == 1 && (pi->pi_mouse & 1) == 0)
		printf("no mouse power jumper on CPU parallel port\n");
	if (flag & FWRITE)
		return (EINVAL);
	if ((tp->t_state & TS_ISOPEN) == 0) {
		tp->t_flags = ANYP+RAW;
		tp->t_state |= TS_CARR_ON;
		tp->t_oproc = pistart;
	}
	scb.scb_autovec[5-1] = clkpiscan;
	start_piscan_clock();
	return ((*linesw[tp->t_line].l_open)(dev, tp));
}

/*
 * Close keyboard or mouse 
 * We never disable clkpiscan because its too hard to synchronize
 * all the opens and closes
 */
/*ARGSUSED*/
piclose(dev, flag)
	dev_t dev;
	int flag;
{
	register struct tty *tp = &pitty[minor(dev)];

	if (dev == kbddev)
		/*
		 * Don't close kbddev.  Otherwise can't get to monitor.
		 * Kbddev is "opened" in sun/autoconf.c but a reference count
		 * for the device is never incremented.  This explains why
		 * close is called at all while it is still being used.
		 */
		return;
	(*linesw[tp->t_line].l_close)(tp);
}

/*ARGSUSED*/
piread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp = &pitty[minor(dev)];

	return (*linesw[tp->t_line].l_read)(tp, uio);
}

/*ARGSUSED*/
piioctl(dev, cmd, data, flag)
	dev_t dev;
	int cmd;
	caddr_t data;
	int flag;
{
	int error;
	register struct tty *tp = &pitty[minor(dev)];

	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
	if (error >= 0)
		return (error);
	return (ttioctl(tp, cmd, data, flag));
}

/*
 * Called in case of random output
 * (e.g., bell to console)
 * Just flushes everything and resets current state
 */
pistart(tp)
	register struct tty *tp;
{

 	if (getc(&tp->t_outq) >= 0) {
 		while (getc(&tp->t_outq) >= 0)
 			;
 		/*
 		 * If there was something in the output queue and the kbd
 		 * is idle when set the last read byte to 0 (an impossible
 		 * kbd code).  This will cause the kbd driver to get another
 		 * idle.  It should be OK for the kbd driver to get
 		 * multiple idles.
 		 */ 
 		if (piaddr->pi_kbd == IDLEKEY) {
 			pilast.pi_kbd = 0;
 		}
 	}
}

/*
 * Mouse:
 * The high 4 bits have value 8 for a button sample,
 * otherwise the high 7 bits are a (signed) delta.
 * Since we can't tell the difference between a delta X
 * and a delta Y, we use the delta before the button sample as
 * the delta Y, and the delta after the button push as the delta X.
 * We re-arrange the order to button, deltaX, deltaY for the sake
 * of the common mouse code.
 */
piintr()
{
	register char m;
	register short limit = 10;
	short samp;
	register struct pireg *pi = piaddr;
	register struct tty *tp;
	static char button, lastbutton, deltay = 0;
	static enum { DELY, BUTTON, DELX } state = DELY;

	/* read and wait for two reads to concur in case sample is changing */
	samp = *(short *)pi;
	while (--limit > 0) {
		if (samp == *(short *)pi)
			goto found;
		samp = *(short *)pi;
	}
	return;		/* hopeless confusion */

found:
	pi = (struct pireg *)&samp;
	if (pi->pi_kbd != pilast.pi_kbd) {
		pilast.pi_kbd = pi->pi_kbd;
		tp = &pitty[0];
		if (tp->t_state & TS_ISOPEN) 
			(*linesw[tp->t_line].l_rint)(pi->pi_kbd, tp);
	}
	if (pi->pi_mouse == pilast.pi_mouse)	/* wait for sample to change */
		return;
	pilast.pi_mouse = pi->pi_mouse;
	m = pi->pi_mouse;
	tp = &pitty[1];
	if ((tp->t_state & TS_ISOPEN) == 0)	/* mouse not active */
		return;
	if ((m & 0xf0) == 0x80) {
		state = BUTTON;
		button = 0x80 | ((m>>1)&7);
	} else
		m >>= 1;
	switch (state) {

	case DELY:		/* delta Y until we see buttons */
		deltay = m;
		break;

	case BUTTON:		/* delta X immediately after we see buttons */
		state = DELX;
		break;

	case DELX:
		state = DELY;
		if (button == lastbutton && m == 0 && deltay == 0)
			break;		/* no new info */
		lastbutton = button;
		(*linesw[tp->t_line].l_rint)(button, tp);
		(*linesw[tp->t_line].l_rint)(m, tp);
		(*linesw[tp->t_line].l_rint)(deltay, tp);
		deltay = m;	/* in case next delta y equals this delta x */
		break;
	}
}
