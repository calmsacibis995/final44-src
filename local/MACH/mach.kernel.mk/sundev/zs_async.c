/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	zs_async.c,v $
 * Revision 2.7  90/04/28  00:04:18  jjc
 * 	Picked up changes from SunOS 4.0.3 that add delays to
 * 	various routines.
 * 	[90/04/15            jjc]
 * 
 * Revision 2.6  89/07/11  17:33:00  jjc
 * 	Picked up SunOS 3.5 version.
 * 	[89/07/05  20:51:40  jjc]
 * 
 * Revision 2.5  89/03/09  21:50:29  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  20:00:17  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.3  88/08/24  02:17:17  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 *
 * 27-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Don't bother to print out "silo overflow" because it does
 *	not seem to matter for the mouse and you can tell that it
 *	has happened with the keyboard.
 *
 *  7-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in CS_TTYLOC stuff.
 *
 *  4-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Replaced all occurences of "romp" with "sunromp" to avoid
 *	name conflict with IBM PC RT "romp".
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)zs_async.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 *	Asynchronous protocol handler for Z8530 chips
 * 	Handles normal UNIX support for terminals & modems
 */
#include <zs.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/buf.h>
#include <sys/kernel.h>
#include <sys/reboot.h>

#include <machine/clock.h>
#include <machine/mmu.h>
#include <machine/cpu.h>
#include <sun/consdev.h>
#include <sundev/mbvar.h>
#include <sundev/zsreg.h>
#include <sundev/zscom.h>
#include <sundev/dmctl.h>

#if	MACH
#define	romp	sunromp
#endif	MACH

#define ZSWR1_INIT	(ZSWR1_SIE|ZSWR1_TIE|ZSWR1_RIE)
#define ZS_ON	(ZSWR5_DTR|ZSWR5_RTS)
#define ZS_OFF	0

#define NZSLINE 	(NZS*2)

#define OUTLINE 0x80	/* minor device flag for dialin/out on same line */
#define UNIT(x)	(minor(x)&~OUTLINE)
 
int	zsstart();
int	ttrstrt();
struct tty zs_tty[NZSLINE];
int	nzs = NZSLINE;

extern char zssoftCAR[NZSLINE];

#define ISPEED	B9600
#define IFLAGS	(EVENP|ODDP|ECHO|CRMOD)

#define PCLK	(19660800/4)	/* basic clock rate for UARTs */
#define ZSPEED(n)	ZSTimeConst(PCLK, n)
#define NSPEED	16	/* max # of speeds */
u_short	zs_speeds[NSPEED] = {
	0,
	ZSPEED(50),
	ZSPEED(75),
	ZSPEED(110),
#ifdef	lint
	ZSPEED(134),
#else
	ZSPEED(134.5),
#endif
	ZSPEED(150),
	ZSPEED(200),
	ZSPEED(300),
	ZSPEED(600),
	ZSPEED(1200),
	ZSPEED(1800),
	ZSPEED(2400),
	ZSPEED(4800),
	ZSPEED(9600),
	ZSPEED(19200),
	ZSPEED(38400),
};

/*
 * Communication between H/W level 6 interrupts
 * and software interrupts
 */
#define ZSIBUFSZ	256
struct zsaline {
	struct tty *za_tty;		/* associated tty */
	short	za_needsoft;		/* need for software interrupt */
	short	za_break;		/* break occurred */
	short	za_overrun;		/* overrun (either hw or sw) */
	short	za_ext;			/* modem status change */
	short	za_work;		/* work to do */
	u_char	za_rr0;			/* for break detection */
	u_char	za_ibuf[ZSIBUFSZ];	/* circular input buffer */
	short	za_iptr;		/* producing ptr for input */
	short	za_sptr;		/* consuming ptr for input */
	u_char	*za_optr;		/* output ptr */	
	short	za_ocnt;		/* output count */	
	short 	za_oflush;		/* # to flush when output done */
} zsaline[NZSLINE];

int zsticks = 3;		/* polling frequency */

/*
 * The async zs protocol
 */
int	zsa_attach(), zsa_txint(), zsa_xsint(), zsa_rxint(), zsa_srint(),
	zsa_softint();

struct zsops zsops_async = {
	zsa_attach,
	zsa_txint,
	zsa_xsint,
	zsa_rxint,
	zsa_srint,
	zsa_softint,
};

zsa_attach(zs)
	register struct zscom *zs;
{
	register struct zsaline *za = &zsaline[zs->zs_unit];
	register struct tty *tp = &zs_tty[zs->zs_unit];

	za->za_tty = tp;
	tp->t_addr = (caddr_t)zs;
	tp->t_dev = zs->zs_unit;
#ifdef	lint
	if (nzs == 0)
		nzs = 1;
#endif	lint
}

/*
 * Get the current speed of the console and turn it into something
 * UNIX knows about - used to preserve console speed when UNIX comes up
 */
zsgetspeed(dev)
	dev_t dev;
{
	register struct tty *tp;
	struct zscom *zs;
	int uspeed, zspeed;

	tp = &zs_tty[UNIT(dev)];
	if (tp->t_addr == 0)
		return (ENXIO);
	zs = (struct zscom *)tp->t_addr;
	zspeed = ZREAD(12);
	zspeed |= ZREAD(13) << 8;
	for (uspeed = 0; uspeed < NSPEED; uspeed++)
		if (zs_speeds[uspeed] == zspeed)
			return (uspeed);
	/* 9600 baud if we can't figure it out */
	return (ISPEED);
}

/*ARGSUSED*/
zsopen(dev, flag)
	dev_t dev;
{
	register struct tty *tp;
	struct zscom *zs;
	struct zsaline *za;
	register int unit;
	int s;
	static int first = 1;
	int zspoll();
#ifdef	MACH
	static tlcinit = 0;

	/*
	 *  Initialize terminal locations on first call to driver.
	 */
	if (tlcinit == 0)
	{
		tlcinit++;
		for (unit=0; unit<nzs; unit++)
		{
			tp = &zs_tty[unit];
			tp->t_ttyloc.tlc_hostid = TLC_MYHOST;
			tp->t_ttyloc.tlc_ttyid = unit;
		}
	}
#endif	MACH

	unit = UNIT(dev);
	tp = &zs_tty[unit];
	if (tp->t_addr == 0)
		return (ENXIO);
	tp->t_oproc = zsstart;
	zs = (struct zscom *)tp->t_addr;
	za = &zsaline[minor(tp->t_dev)];
	s = splzs();
	zs->zs_priv = (caddr_t)za;
	zsopinit(zs, &zsops_async);
	(void) splx(s);
	if (first) {
		first = 0;
		timeout(zspoll, (caddr_t)0, zsticks);
	}
	if (dev == kbddev && kbddevopen)
		return (0);
	s = spl5();
again:
	tp->t_state |= TS_WOPEN;
	if ((tp->t_state & TS_ISOPEN) == 0) {
		/* clear any stale input */
		za->za_iptr = 0;
		za->za_sptr = 0;
		za->za_overrun = 0;
		ttychars(tp);
		if (dev == rconsdev || dev == kbddev)
			tp->t_ospeed = tp->t_ispeed = zsgetspeed(dev);
		else
			tp->t_ospeed = tp->t_ispeed = ISPEED;
		tp->t_flags = IFLAGS;
#ifdef	MACH
		/* Don't use extra modes for S5 compatibility */
#else	MACH
		tp->t_xflags = 0;
#endif	MACH
		/* tp->t_state |= TS_HUPCLS; */
		zsparam(tp);
	} else if (tp->t_state&TS_XCLUDE && u.u_uid != 0) {
		(void) splx(s);
		return (EBUSY);
	} else if ((dev & OUTLINE) && !(tp->t_state&TS_OUT)) {
		(void) splx(s);
		return (ENXIO);
	}
	(void) zsmctl(tp, ZS_ON, DMSET);
	if (dev & OUTLINE)
		tp->t_state |= TS_OUT|TS_CARR_ON;
	if (zssoftCAR[unit] || (zsmctl(tp, 0, DMGET) & ZSRR0_CD))
		tp->t_state |= TS_CARR_ON;
	if ((flag & FNDELAY) == 0)
		if (((tp->t_state & TS_CARR_ON) == 0) ||
		    ((tp->t_state&TS_OUT) && (dev&OUTLINE) == 0)) {
			tp->t_state |= TS_WOPEN;
			(void) sleep((caddr_t)&tp->t_state, TTIPRI);
			goto again;
		}
	(void) splx(s);
	return ((*linesw[tp->t_line].l_open)(dev&~OUTLINE, tp));
}
 
/*ARGSUSED*/
zsclose(dev, flag)
	dev_t dev;
{
	register struct tty *tp;
	register struct zscom *zs;
	register int unit;
 
	/*
	 * Need to supress zsintr throughout whole close sequence because
	 * one of last things that zsintr does is a l_rint which can be nasty
	 * if part way through a l_close or ttyclose of that tp.
	 */
	(void) spl5();
	unit = UNIT(dev);
	tp = &zs_tty[unit];
	(*linesw[tp->t_line].l_close)(tp);
	if (dev == kbddev) {
		/*
		 * Don't shut down this line.  Otherwise can't get to monitor.
		 * Kbddev is "opened" in sun/autoconf.c but a reference count
		 * for the device is never incremented.  This explains why
		 * close is called at all while it is still being used.
		 */
		(void) spl0();
		return;
	}
	tp->t_state &= ~TS_OUT;
	zs = (struct zscom *)tp->t_addr;
	if (zs->zs_wreg[5] & ZSWR5_BREAK) {
		(void) splzs();
		ZBIC(5, ZSWR5_BREAK);
		(void) spl5();
	}
	if ((tp->t_state&(TS_HUPCLS|TS_WOPEN)) || (tp->t_state&TS_ISOPEN)==0) {
		if (dev != rconsdev && dev != kbddev) {
			(void) zsmctl(tp, ZS_OFF, DMSET);
			(void) sleep((caddr_t)&lbolt, TTOPRI);
		}
	}
	ttyclose(tp);
	if ((tp->t_state & (TS_ISOPEN|TS_WOPEN)) == 0) {
		(void) splzs();
		ZBIC(1, ZSWR1_RIE);
		(void) spl5();
	}
	wakeup((caddr_t)&tp->t_state);
	(void) spl0();
}
 
zsread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp;
 
	tp = &zs_tty[UNIT(dev)];
	(*linesw[tp->t_line].l_read)(tp, uio);
}
 
zswrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp;
 
	tp = &zs_tty[UNIT(dev)];
	(*linesw[tp->t_line].l_write)(tp, uio);
}

/*ARGSUSED*/
zsselect(dev, rw)
	dev_t dev;
	int rw;
{
	register struct tty *tp;

	tp = &zs_tty[UNIT(dev)];
	switch (tp->t_line) {

	case OTTYDISC:
	case NTTYDISC:
	case TABLDISC:
	case NTABLDISC:
	case MOUSELDISC:
	case KBDLDISC:
		return (ttselect(dev & ~OUTLINE, rw));
		break;
	/*
	 * Select doesn't work on "non-standard" line disciplines.
	 * Return "ready": the least objectionable alternative.
	 */
	default:
		return(1);
	}
}

/*ARGSUSED*/
zsioctl(dev, cmd, data, flag)
	dev_t dev;
	caddr_t data;
{
	register struct tty *tp;
	register int unit = UNIT(dev);
	register struct zscom *zs;
	int error;
 
	tp = &zs_tty[unit];
	zs = (struct zscom *)tp->t_addr;
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
	if (error < 0)
		error = ttioctl(tp, cmd, data, flag);
	if (error >= 0) {
		switch (cmd) {
		case TIOCSETP:
		case TIOCSETN:
		case TIOCLSET:
		case TIOCLBIS:
		case TIOCLBIC:
#if	MACH
		/* Not used in Mach....  Used to set extra modes for S5 */
#else	MACH
		case TIOCSETX:
#endif	MACH
			zsparam(tp);
		}
		return (error);
	}
	switch(cmd) {

	case TIOCSBRK:
		(void) splzs();
		ZBIS(5, ZSWR5_BREAK);
		(void) spl0();
		break;
	case TIOCCBRK:
		(void) splzs();
		ZBIC(5, ZSWR5_BREAK);
		(void) spl0();
		break;
	case TIOCSDTR:
		(void) zsmctl(tp, ZS_ON, DMBIS);
		break;
	case TIOCCDTR:
		(void) zsmctl(tp, ZS_OFF, DMSET);
		break;
	case TIOCMSET:
		(void) zsmctl(tp, dmtozs(*(int *)data), DMSET);
		break;
	case TIOCMBIS:
		(void) zsmctl(tp, dmtozs(*(int *)data), DMBIS);
		break;
	case TIOCMBIC:
		(void) zsmctl(tp, dmtozs(*(int *)data), DMBIC);
		break;
	case TIOCMGET:
		*(int *)data = zstodm(zsmctl(tp, 0, DMGET));
		break;
	default:
		return (ENOTTY);
	}
	return (0);
}

dmtozs(bits)
	register int bits;
{
	register int b = 0;

	if (bits & DML_CAR) b |= ZSRR0_CD;
	if (bits & DML_CTS) b |= ZSRR0_CTS;
	if (bits & DML_RTS) b |= ZSWR5_RTS;
	if (bits & DML_DTR) b |= ZSWR5_DTR;
	return (b);
}

zstodm(bits)
	register int bits;
{
	register int b = 0;

	if (bits & ZSRR0_CD) b |= DML_CAR;
	if (bits & ZSRR0_CTS) b |= DML_CTS;
	if (bits & ZSWR5_RTS) b |= DML_RTS;
	if (bits & ZSWR5_DTR) b |= DML_DTR;
	return (b);
}
 
zsparam(tp)
	register struct tty *tp;
{
	register struct zscom *zs = (struct zscom *)tp->t_addr;
	register int wr1, wr3, wr4, wr5, speed;
	int loops;
	int s;
	char c;
 
#ifdef lint
	c = 0;
	c = c;
#endif 
	if (tp->t_ispeed == 0) {
		(void) zsmctl(tp, ZS_OFF, DMSET);	/* hang up line */
		return;
	}
	wr1 = ZSWR1_INIT;
	wr3 = ZSWR3_RX_ENABLE;
	wr4 = ZSWR4_X16_CLK;
	wr5 = (zs->zs_wreg[5] & (ZSWR5_RTS|ZSWR5_DTR)) | ZSWR5_TX_ENABLE;
	if (tp->t_ispeed == B134) {	/* what a joke! */
		wr1 |= ZSWR1_PARITY_SPECIAL;
		wr3 |= ZSWR3_RX_6;
		wr4 |= ZSWR4_PARITY_ENABLE | ZSWR4_PARITY_EVEN;
		wr5 |= ZSWR5_TX_6;
	} else if (tp->t_flags&(RAW|LITOUT|PASS8)) {
		wr3 |= ZSWR3_RX_8;
		wr5 |= ZSWR5_TX_8;
	} else switch (tp->t_flags & (EVENP|ODDP)) {
	case 0:
		wr3 |= ZSWR3_RX_8;
		wr5 |= ZSWR5_TX_8;
		break;

	case EVENP:
		wr1 |= ZSWR1_PARITY_SPECIAL;
		wr3 |= ZSWR3_RX_7;
		wr4 |= ZSWR4_PARITY_ENABLE + ZSWR4_PARITY_EVEN;
		wr5 |= ZSWR5_TX_7;
		break;

	case ODDP:
		wr1 |= ZSWR1_PARITY_SPECIAL;
		wr3 |= ZSWR3_RX_7;
		wr4 |= ZSWR4_PARITY_ENABLE;
		wr5 |= ZSWR5_TX_7;
		break;

	case EVENP|ODDP:
		wr3 |= ZSWR3_RX_7;
		wr4 |= ZSWR4_PARITY_ENABLE + ZSWR4_PARITY_EVEN;
		wr5 |= ZSWR5_TX_7;
		break;
	}
#if	MACH
	if (tp->t_ispeed == B110)
#else	MACH
	if (tp->t_ispeed == B110 || tp->t_xflags & STOPB)
#endif	MACH
		wr4 |= ZSWR4_2_STOP;
	else if (tp->t_ispeed == B134)
		wr4 |= ZSWR4_1_5_STOP;
	else
		wr4 |= ZSWR4_1_STOP;
	speed = zs->zs_wreg[12] + (zs->zs_wreg[13] << 8);
	if (wr1 != zs->zs_wreg[1] || wr3 != zs->zs_wreg[3] ||
	    wr4 != zs->zs_wreg[4] || wr5 != zs->zs_wreg[5] ||
	    speed != zs_speeds[tp->t_ispeed&017]) {
		tp->t_state |= TS_FLUSH;
		zsstop(tp, 0);
		/* 
		 * Wait for that last damn character to get out the
		 * door.  At most 1000 loops of 100 usec each is worst
		 * case of 110 baud.  If something appears on the output
		 * queue then somebody higher up isn't synchronized
		 * and we give up.
		 */
		s = splzs();
		loops = 1000;
		while ((ZREAD(1) & ZSRR1_ALL_SENT) == 0 && --loops > 0) {
			(void) splx(s);
			DELAY(100);
			s = splzs();
		}
		ZWRITE(3, 0);	/* disable receiver while setting parameters */
		zs->zs_addr->zscc_control = ZSWR0_RESET_STATUS;
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		zs->zs_addr->zscc_control = ZSWR0_RESET_ERRORS;
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		c = zs->zs_addr->zscc_data; /* swallow junk */
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		c = zs->zs_addr->zscc_data; /* swallow junk */
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		c = zs->zs_addr->zscc_data; /* swallow junk */
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		ZWRITE(1, wr1);
		ZWRITE(4, wr4);
		ZWRITE(3, wr3);
		ZWRITE(5, wr5);
		speed = zs_speeds[tp->t_ispeed&017];
		ZWRITE(11, ZSWR11_TXCLK_BAUD + ZSWR11_RXCLK_BAUD);
		ZWRITE(14, ZSWR14_BAUD_FROM_PCLK);
		ZWRITE(12, speed);
		ZWRITE(13, speed >> 8);
		ZWRITE(14, ZSWR14_BAUD_ENA + ZSWR14_BAUD_FROM_PCLK);
		(void) splx(s);
		tp->t_state &= ~TS_FLUSH;
		zsstart(tp);
	}
}
 
zsstart(tp)
	register struct tty *tp;
{
	register struct zscom *zs = (struct zscom *)tp->t_addr;
	register struct zsaline *za = (struct zsaline *)zs->zs_priv;
	register int s, cc;
 
	s = spl5();
	if (tp->t_state & (TS_TIMEOUT|TS_BUSY|TS_TTSTOP|TS_FLUSH))
		goto out;
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
	if (tp->t_outq.c_cc == 0)
		goto out;
	if (za->za_ocnt > 0) {
		tp->t_state |= TS_BUSY;
		goto out;
	}
	if (tp->t_flags & (RAW|LITOUT))
		cc = ndqb(&tp->t_outq, 0);
	else {
		cc = ndqb(&tp->t_outq, 0200);
		if (cc == 0) {
			cc = getc(&tp->t_outq);
			timeout(ttrstrt, (caddr_t)tp, (cc&0x7f) + 6);
			tp->t_state |= TS_TIMEOUT;
			goto out;
		}
	}
	(void) splzs();
	za->za_optr = (u_char *)tp->t_outq.c_cf;
	za->za_oflush = za->za_ocnt = cc;
	if (zs->zs_addr->zscc_control & ZSRR0_TX_READY) {
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		zs->zs_addr->zscc_data = *za->za_optr++;
#if	SUNOS_403
		/* XXX we assume there is enough time here for recovery */
#endif	SUNOS_403
		za->za_ocnt--;
	}
	tp->t_state |= TS_BUSY;
out:
	(void) splx(s);
}

/*
 * Stop output on a line.
 */
/*ARGSUSED*/
zsstop(tp, flag)
	register struct tty *tp;
{
	register struct zscom *zs = (struct zscom *)tp->t_addr;
	register struct zsaline *za = (struct zsaline *)zs->zs_priv;
	int s = splzs();

	if (tp->t_state & TS_BUSY) {
		if ((tp->t_state&TS_TTSTOP)==0)
			za->za_oflush = 0;
		else
			za->za_oflush -= za->za_ocnt;
		za->za_ocnt = 0;
	}
	(void) splx(s);
}
 
zsmctl(tp, bits, how)
	struct tty *tp;
	int bits, how;
{
	register struct zscom *zs = (struct zscom *)tp->t_addr;
	register int mbits, s;

	s = splzs();
	mbits = zs->zs_wreg[5] & (ZSWR5_RTS|ZSWR5_DTR);
	zs->zs_addr->zscc_control = ZSWR0_RESET_STATUS;
#if	SUNOS_403
	ZSDELAY(2);
#else	SUNOS_403
	DELAY(2);
#endif	SUNOS_403
	mbits |= zs->zs_addr->zscc_control & (ZSRR0_CD|ZSRR0_CTS);
#if	SUNOS_403
	ZSDELAY(2);
#endif	SUNOS_403
	switch (how) {
	case DMSET:
		mbits = bits;
		break;

	case DMBIS:
		mbits |= bits;
		break;

	case DMBIC:
		mbits &= ~bits;
		break;

	case DMGET:
		(void) splx(s);
		return (mbits);
	}
	zs->zs_wreg[5] &= ~(ZSWR5_RTS|ZSWR5_DTR);
	ZBIS(5, mbits & (ZSWR5_RTS|ZSWR5_DTR));
	(void) splx(s);
	return (mbits);
}

zsa_txint(zs)
	register struct zscom *zs;
{
	register struct zsaline *za = (struct zsaline *)zs->zs_priv;
	register struct zscc_device *zsaddr = zs->zs_addr;

	if (za->za_ocnt > 0 && (zsaddr->zscc_control & ZSRR0_TX_READY)) {
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		zsaddr->zscc_data = *za->za_optr++;
		za->za_ocnt--;
	} else {
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		za->za_work++;
		zsaddr->zscc_control = ZSWR0_RESET_TXINT;
		ZSSETSOFT(zs);
	}
}

zsa_xsint(zs)
	register struct zscom *zs;
{
	register struct zsaline *za = (struct zsaline *)zs->zs_priv;
	register struct tty *tp = za->za_tty;
	register struct zscc_device *zsaddr = zs->zs_addr;
	register u_char s0, x0, c;

	s0 = zsaddr->zscc_control;
#if	SUNOS_403
	ZSDELAY(2);
#endif	SUNOS_403
	x0 = s0 ^ za->za_rr0;
	za->za_rr0 = s0;
	zsaddr->zscc_control = ZSWR0_RESET_STATUS;
	if ((x0 & ZSRR0_BREAK) && (s0 & ZSRR0_BREAK) == 0) {
		za->za_break++;
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		c = zsaddr->zscc_data; /* swallow null */
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
#ifdef	lint
		c = c;
#endif
		zsaddr->zscc_control = ZSWR0_RESET_ERRORS;
#if	SUNOS_403
		ZSDELAY(2);
#endif	SUNOS_403
		if (tp->t_dev == kbddev) {
#if	MACH
			montrap(*romp->v_abortent);
#else	MACH
			if (boothowto & RB_DEBUG) {
				CALL_DEBUG();
			} else {
				montrap(*romp->v_abortent);
			}
#endif	MACH
		}
	}
	za->za_work++;
	za->za_ext++;
	ZSSETSOFT(zs);
}

zsa_rxint(zs)
	register struct zscom *zs;
{
	register struct zsaline *za = (struct zsaline *)zs->zs_priv;
	register struct tty *tp = za->za_tty;
	register struct zscc_device *zsaddr = zs->zs_addr;
	register u_char c;

	c = zsaddr->zscc_data;
	if (c == 0 && (za->za_rr0 & ZSRR0_BREAK)) {
		if (ZREAD(0) & ZSRR0_BREAK)
			return;
		zsa_xsint(zs);
	}
	za->za_ibuf[za->za_iptr++] = c;
	if (za->za_iptr >= ZSIBUFSZ)
		za->za_iptr = 0;
	if (za->za_iptr == za->za_sptr)
		za->za_overrun++;
	za->za_work++;
	if (tp->t_line == MOUSELDISC || (c & 0177) == tp->t_stopc ||
	    ++za->za_needsoft > 20) {
		za->za_needsoft = 0;
		ZSSETSOFT(zs);
	}
}

zsa_srint(zs)
	register struct zscom *zs;
{
	register struct zsaline *za = (struct zsaline *)zs->zs_priv;
	register struct zscc_device *zsaddr = zs->zs_addr;
	register short s1;
	register u_char c;

	s1 = ZREAD(1);
#if	SUNOS_403
	ZSDELAY(2);
#endif	SUNOS_403
	c = zsaddr->zscc_data;	/* swallow bad char */
#if	SUNOS_403
	ZSDELAY(2);
#endif	SUNOS_403
#ifdef	lint
	c = c;
#endif
	zsaddr->zscc_control = ZSWR0_RESET_ERRORS;
#if	SUNOS_403
	ZSDELAY(2);
#endif	SUNOS_403
	if (s1 & ZSRR1_DO) {
		za->za_overrun++;
		za->za_work++;
		ZSSETSOFT(zs);
	}
}

/*
 * Handle a software interrupt 
 */
zsa_softint(zs)
	register struct zscom *zs;
{
	register struct zsaline *za = (struct zsaline *)zs->zs_priv;

	if (zsa_process(za))	/* true if too much work at once */
		zspoll(1);
	return (0);
}

/*
 * Poll for events in the zscom structures
 * This routine is called at level 1, we jack up to 3 to lock
 * out zsa_softint.
 */
zspoll(direct)
{
	register struct zsaline *za;
	register short more;
	register int s;

	do {
		more = 0;
		for (za = &zsaline[0]; za < &zsaline[NZSLINE]; za++)
		if (za->za_work) {
			za->za_work = 0;
			s = spl3();
			if (zsa_process(za)) {
				za->za_work++;
				more++;
			}
			(void) splx(s);
		}
	} while (more);
	if (!direct)
		timeout(zspoll, (caddr_t)0, zsticks);
}

/* 
 * Process software interrupts (or poll)
 * Crucial points:
 * 1.  Inner loop gives equal priority to input and output so that
 *     in TANDEM mode the stop character has a chance of being sent
 *     before enough input arrives to exceed TTYHOG.  This has happened
 *     in very busy systems.
 * 2.  The inner loop is executed at most 20 times before the next line
 *     is serviced -- this "schedules" more fairly among lines.
 * 3.  BUG - breaks are handled "out-of-band" - their relative position
 *     among input events is lost, as well as multiple breaks together.
 *     This is probably not a problem in practice.
 */
zsa_process(za)
	register struct zsaline *za;
{
	register struct tty *tp = za->za_tty;
	register struct zscc_device *zsaddr =
			((struct zscom *)tp->t_addr)->zs_addr;
	register short i;
	register u_char c;

	if (za->za_ext) {
		za->za_ext = 0;
		/* carrier up? */
		if ((zsaddr->zscc_control & ZSRR0_CD) ||
		    zssoftCAR[UNIT(tp->t_dev)] || (tp->t_state & TS_OUT)) {
			if ((tp->t_state&TS_CARR_ON) == 0) {
				wakeup((caddr_t)&tp->t_state);
				tp->t_state |= TS_CARR_ON;
			}
		} else {	/* no carrier */
			if ((tp->t_state&TS_CARR_ON) &&
			    (tp->t_flags&NOHANG)==0) {
				gsignal(tp->t_pgrp, SIGHUP);
				gsignal(tp->t_pgrp, SIGCONT);
				(void) zsmctl(tp, ZSWR5_DTR, DMBIC);
				switch (tp->t_line) {
				case OTTYDISC:
				case NTTYDISC:
				case TABLDISC:
				case NTABLDISC:
				case MOUSELDISC:
				case KBDLDISC:
					ttyflush(tp, FREAD|FWRITE);
					break;
				default:
					ttyflush(tp, FWRITE);
				}
			}
			tp->t_state &= ~TS_CARR_ON;
		}
	}
	if (za->za_overrun) {
		za->za_overrun = 0;
		za->za_iptr = 0;
		za->za_sptr = 0;
		if (tp->t_state & TS_ISOPEN)
#if	MACH
			/* don't bother printing error message */;
#else	MACH
			printf("zs%d: silo overflow\n", minor(tp->t_dev));
#endif	MACH
	}
	if (za->za_break &&
	    (zsaddr->zscc_control & ZSRR0_BREAK) == 0) {
		za->za_break = 0;
		if (tp->t_dev == kbddev) {
#include <kb.h>
#if	NKB > 0
			if (tp->t_dev != rconsdev)	/* serial kbd */
				kbdreset(tp);
#endif	NKB > 0
		} else if (tp->t_state & TS_ISOPEN) {
			c = (tp->t_flags & RAW) ? 0 : tp->t_intrc;
			(*linesw[tp->t_line].l_rint)(c, tp);
		}
	}
	/* need to handle I & O in same loop to make TANDEM mode work */
	i = 0;
	do {
		if (za->za_sptr != za->za_iptr) {
			c = za->za_ibuf[za->za_sptr++];
			if (za->za_sptr >= ZSIBUFSZ)
				za->za_sptr = 0;
			if (tp->t_state & TS_ISOPEN)
				(*linesw[tp->t_line].l_rint)(c, tp);
		}
		if (za->za_ocnt <= 0 && (tp->t_state & TS_BUSY)) {
			ndflush(&tp->t_outq, za->za_oflush);
			tp->t_state &= ~TS_BUSY;
			if (tp->t_line)
				(*linesw[tp->t_line].l_start)(tp);
			else
				zsstart(tp);
		}
	} while (za->za_sptr != za->za_iptr && ++i < 20);
	return (i >= 20);
}
