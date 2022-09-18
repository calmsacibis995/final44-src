h56360
s 00004/00003/00592
d D 7.7 91/05/16 18:18:07 marc 12 11
c pass flags from device close to l_close
e
s 00000/00001/00595
d D 7.6 91/05/09 13:08:55 sklower 11 10
c /sys/sys/bkmac.h is gone
e
s 00016/00016/00580
d D 7.5 90/12/16 16:58:39 bostic 10 9
c kernel reorg
e
s 00003/00003/00593
d D 7.4 90/06/28 15:31:00 marc 9 8
c ttysleep to catch revokes terminals
e
s 00003/00002/00593
d D 7.3 90/06/06 17:44:22 marc 8 7
c check for revoked terminal (ttclosed)
e
s 00000/00001/00595
d D 7.2 90/04/12 17:58:02 sklower 7 6
c no more bk.h
e
s 00000/00000/00596
d D 7.1 90/04/03 22:18:10 karels 6 5
c rev 7
e
s 00007/00004/00589
d D 1.5 90/04/03 22:17:10 karels 5 4
c tsleep: unwind after signal interrupts; close routines must return value
e
s 00000/00001/00593
d D 1.4 90/02/17 11:03:29 mckusick 4 3
c get rid of dir.h
e
s 00002/00001/00592
d D 1.3 90/02/08 18:22:24 marc 3 2
c tsleep
e
s 00057/00052/00536
d D 1.2 89/09/06 14:30:29 marc 2 1
c posix tty
e
s 00588/00000/00000
d D 1.1 89/08/15 19:13:58 marc 1 0
c date and time created 89/08/15 19:13:58 by marc
e
u
U
t
T
I 1
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Common code for DMF32 and DMZ32 drivers
 */
#include "dmf.h"
#include "dmz.h"
#if NDMF + NDMZ > 0

D 10
#include "machine/pte.h"
E 10
I 10
#include "../include/pte.h"
E 10

I 10
#include "sys/param.h"
E 10
D 7
#include "bk.h"
E 7
#include "uba.h"
D 10
#include "param.h"
#include "conf.h"
D 4
#include "dir.h"
E 4
#include "user.h"
#include "proc.h"
#include "ioctl.h"
#include "tty.h"
#include "map.h"
#include "buf.h"
#include "vm.h"
#include "bkmac.h"
#include "clist.h"
#include "file.h"
#include "uio.h"
#include "kernel.h"
#include "syslog.h"
E 10
I 10
#include "sys/conf.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/map.h"
#include "sys/buf.h"
#include "sys/vm.h"
D 11
#include "sys/bkmac.h"
E 11
#include "sys/clist.h"
#include "sys/file.h"
#include "sys/uio.h"
#include "sys/kernel.h"
#include "sys/syslog.h"
E 10
I 3
D 5
#include "tsleep.h"
E 5
E 3

#include "dmx.h"
#include "ubareg.h"
#include "ubavar.h"
#include "dmxreg.h"
#include "dmreg.h"

#ifndef	PORTSELECTOR
D 2
#define	ISPEED	B9600
#define	IFLAGS	(EVENP|ODDP|ECHO)
E 2
I 2
#define	ISPEED	TTYDEF_SPEED
#define	LFLAG	TTYDEF_LFLAG
E 2
#else
#define	ISPEED	B4800
D 2
#define	IFLAGS	(EVENP|ODDP)
E 2
I 2
#define	IFLAGS	(TTYDEF_LFLAG&~ECHO)
E 2
#endif

#ifndef DMX_TIMEOUT
#define DMX_TIMEOUT	10
#endif
int	dmx_timeout = DMX_TIMEOUT;		/* silo timeout, in ms */
int	dmx_mindma = 4;			/* don't dma below this point */

struct speedtab dmxspeedtab[] = {
	0,	0,
	75,	1,
	110,	2,
	134,	3,
	150,	4,
	300,	5,
	600,	6,
	1200,	7,
	1800,	010,
	2400,	012,
	4800,	014,
	9600,	016,
	19200,	017,
	EXTA,	017,
	-1,	-1
};
/*
 * The clist space is mapped by the drivers onto each UNIBUS.
 * The UBACVT macro converts a clist space address for unibus uban
 * into an I/O space address for the DMA routine.
 */
int	cbase[NUBA];			/* base address in unibus map */
#define	UBACVT(x, uban)		(cbase[uban] + ((x)-(char *)cfree))

int	ttrstrt();

/*
 * DMF/DMZ open common code
 */
D 2
dmxopen(tp, sc)
E 2
I 2
dmxopen(tp, sc, flag)
E 2
	register struct tty *tp;
	register struct dmx_softc *sc;
{
D 5
	int s, unit;
E 5
I 5
	int s, unit, error = 0;
E 5
	int dmxparam();

	s = spltty();
	if ((sc->dmx_flags & DMX_ACTIVE) == 0) {
		sc->dmx_octet->csr |= DMF_IE;
		sc->dmx_flags |= DMX_ACTIVE;
		sc->dmx_octet->rsp = dmx_timeout;
	}
	splx(s);
	if (tp->t_state & TS_XCLUDE && u.u_uid != 0)
		return (EBUSY);
	/*
	 * If this is first open, initialize tty state to default.
	 */
	if ((tp->t_state&TS_ISOPEN) == 0) {
I 9
		tp->t_state |= TS_WOPEN;
E 9
		ttychars(tp);
#ifndef PORTSELECTOR
		if (tp->t_ispeed == 0) {
I 2
#endif
			tp->t_iflag = TTYDEF_IFLAG;
                        tp->t_oflag = TTYDEF_OFLAG;
                        tp->t_cflag = TTYDEF_CFLAG;
                        tp->t_lflag = LFLAG;
                        tp->t_ispeed = tp->t_ospeed = ISPEED;
#ifdef PORTSELECTOR
			tp->t_cflag |= HUPCL;
E 2
#else
D 2
			tp->t_state |= TS_HUPCLS;
#endif PORTSELECTOR
			tp->t_ispeed = ISPEED;
			tp->t_ospeed = ISPEED;
			tp->t_flags = IFLAGS;
#ifndef PORTSELECTOR
E 2
		}
D 2
#endif PORTSELECTOR
E 2
I 2
#endif
E 2
	}
D 2
	dmxparam(tp);
E 2
I 2
	dmxparam(tp, &tp->t_termios);
E 2

	unit = minor(tp->t_dev) & 07;
	/*
	 * Wait for carrier, then process line discipline specific open.
	 */
	s = spltty();
	for (;;) {
		if ((dmxmctl(tp, DMF_ON, DMSET) & DMF_CAR) ||
		    (sc->dmx_softCAR & (1 << unit)))
			tp->t_state |= TS_CARR_ON;
D 2
		if (tp->t_state & TS_CARR_ON)
E 2
I 2
		if (tp->t_state&TS_CARR_ON || flag&O_NONBLOCK ||
		    tp->t_cflag&CLOCAL)
E 2
			break;
		tp->t_state |= TS_WOPEN;
D 3
		sleep((caddr_t)&tp->t_rawq, TTIPRI);
E 3
I 3
D 5
		tsleep((caddr_t)&tp->t_rawq, TTIPRI, SLP_DMX_OPN, 0);
E 5
I 5
D 8
		if (error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
		    ttopen, 0))
E 8
I 8
D 9
		if ((error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
				    ttopen, 0)) ||
		    (error = ttclosed(tp)))
E 9
I 9
		if (error = ttysleep(tp, (caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
		    ttopen, 0))
E 9
E 8
			break;
E 5
E 3
	}
	splx(s);
I 5
	if (error)
		return (error);
E 5
	return ((*linesw[tp->t_line].l_open)(tp->t_dev, tp));
}

D 12
dmxclose(tp)
	register struct tty *tp;
E 12
I 12
dmxclose(tp, flag)
	struct tty *tp;
	int flag;
E 12
{

D 12
	(*linesw[tp->t_line].l_close)(tp);
E 12
I 12
	(*linesw[tp->t_line].l_close)(tp, flag);
E 12
	(void) dmxmctl(tp, DMF_BRK, DMBIC);
D 2
	if (tp->t_state & TS_HUPCLS || (tp->t_state & TS_ISOPEN) == 0)
E 2
I 2
	if (tp->t_cflag & HUPCL || (tp->t_state & TS_ISOPEN) == 0)
E 2
		(void) dmxmctl(tp, DMF_OFF, DMSET);
D 5
	ttyclose(tp);
E 5
I 5
	return (ttyclose(tp));
E 5
}

dmxrint(sc)
	register struct dmx_softc *sc;
{
D 2
	register c;
E 2
I 2
	register c, cc;
E 2
	register struct tty *tp;
	register struct dmx_octet *addr;
	int unit;
	int overrun = 0;

	addr = (struct dmx_octet *)sc->dmx_octet;
	/*
	 * Loop fetching characters from the silo for this
	 * octet until there are no more in the silo.
	 */
	while ((c = addr->rbuf) < 0) {
D 2

E 2
I 2
		cc = c&0xff;
E 2
		unit = (c >> 8) & 07;
		tp = sc->dmx_tty + unit;
		if (c & DMF_DSC) {
			addr->csr = DMF_IE | DMFIR_RMSTSC | unit;
			if (addr->rmstsc & DMF_CAR)
				(void)(*linesw[tp->t_line].l_modem)(tp, 1);
			else if ((sc->dmx_softCAR & (1 << unit)) == 0 &&
			    (*linesw[tp->t_line].l_modem)(tp, 0) == 0) {
				addr->csr = DMF_IE | DMFIR_LCR | unit;
				addr->lctms = DMF_ENA;
			}
			continue;
		}
		if ((tp->t_state&TS_ISOPEN) == 0) {
			wakeup((caddr_t)&tp->t_rawq);
#ifdef PORTSELECTOR
			if ((tp->t_state & TS_WOPEN) == 0)
#endif
				continue;
		}
		if (c & (DMF_PE|DMF_DO|DMF_FE)) {
			if (c & DMF_PE)
D 2
				if ((tp->t_flags & (EVENP|ODDP)) == EVENP
			 	|| (tp->t_flags & (EVENP|ODDP)) == ODDP)
					continue;
E 2
I 2
				cc |= TTY_PE;
E 2
			if ((c & DMF_DO) && overrun == 0) {
				log(LOG_WARNING,
				    "dm%c%d: silo overflow, line %d\n",
				    sc->dmx_type, sc->dmx_unit,
				    sc->dmx_unit0 + unit);
				overrun = 1;
			}
			if (c & DMF_FE)
D 2
				/*
				 * At framing error (break) generate
				 * a null (in raw mode, for getty), or an
				 * interrupt (in cooked/cbreak mode).
				 */
				if (tp->t_flags & RAW)
					c = 0;
				else
					c = tp->t_intrc;
E 2
I 2
				cc |= TTY_FE;
E 2
		}
D 2
		(*linesw[tp->t_line].l_rint)(c, tp);
E 2
I 2
		(*linesw[tp->t_line].l_rint)(cc, tp);
E 2
	}
}

dmxioctl(tp, cmd, data, flag)
	register struct tty *tp;
	caddr_t data;
{
	int error;

	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, data, flag);
D 2
	if (error >= 0) {
		if (cmd == TIOCSETP || cmd == TIOCSETN || cmd == TIOCLBIS ||
		    cmd == TIOCLBIC || cmd == TIOCLSET)
			dmxparam(tp);
E 2
I 2
	if (error >= 0)
E 2
		return (error);
D 2
	}
E 2
I 2

E 2
	switch (cmd) {

	case TIOCSBRK:
		(void) dmxmctl(tp, DMF_BRK, DMBIS);
		break;

	case TIOCCBRK:
		(void) dmxmctl(tp, DMF_BRK, DMBIC);
		break;

	case TIOCSDTR:
		(void) dmxmctl(tp, DMF_DTR|DMF_RTS, DMBIS);
		break;

	case TIOCCDTR:
		(void) dmxmctl(tp, DMF_DTR|DMF_RTS, DMBIC);
		break;

	case TIOCMSET:
		(void) dmxmctl(tp, dmtodmx(*(int *)data), DMSET);
		break;

	case TIOCMBIS:
		(void) dmxmctl(tp, dmtodmx(*(int *)data), DMBIS);
		break;

	case TIOCMBIC:
		(void) dmxmctl(tp, dmtodmx(*(int *)data), DMBIC);
		break;

	case TIOCMGET:
		*(int *)data = dmxmctl(tp, 0, DMGET);
		break;

	default:
		return (ENOTTY);
	}
	return (0);
}

/*
 * modem control
 * "bits" are dmf/dmz lcr format;
 * return of DMGET is DM11 format.
 */
dmxmctl(tp, bits, how)
	struct tty *tp;
	int bits, how;
{
	register struct dmx_octet *addr;
	register int unit, mbits, lcr;
	int s;

	unit = minor(tp->t_dev) & 07;
	addr = (struct dmx_octet *)(tp->t_addr);

	s = spltty();
	addr->csr = DMF_IE | DMFIR_RMSTSC | unit;
	mbits = addr->rmstsc & 0xff00;
	addr->csr = DMF_IE | DMFIR_LCR | unit;
	lcr = addr->lctms;

	switch (how) {
	case DMSET:
		lcr = bits;
		break;

	case DMBIS:
		lcr |= bits;
		break;

	case DMBIC:
		lcr &= ~bits;
		break;

	case DMGET:
		splx(s);
		return (dmxtodm(mbits, lcr));
	}
	addr->lctms = lcr;
	(void) splx(s);
	return (mbits);
}

/*
 * Routine to convert modem status from dm to dmf/dmz lctmr format.
 */
dmtodmx(bits)
	register int bits;
{
	register int lcr = DMF_ENA;

	if (bits & DML_DTR)
		lcr |= DMF_DTR;
	if (bits & DML_RTS)
		lcr |= DMF_RTS;
	if (bits & DML_ST)
		lcr |= DMF_SRTS;
	if (bits & DML_USR)
		lcr |= DMF_USRW;
	return (lcr);
}

/*
 * Routine to convert modem status from dmf/dmz receive modem status
 * and line control register to dm format.
 * If dmf/dmz user modem read bit set, set DML_USR.
 */
dmxtodm(mstat, lcr)
	register int mstat, lcr;
{

	mstat = ((mstat & (DMF_DSR|DMF_RNG|DMF_CAR|DMF_CTS|DMF_SR)) >> 7) | 
		((mstat & DMF_USRR) >> 1) | DML_LE;
	if (lcr & DMF_DTR)
		mstat |= DML_DTR;
	if (lcr & DMF_SRTS)
		mstat |= DML_ST;
	if (lcr & DMF_RTS)
		mstat |= DML_RTS;
	return (mstat);
}
 

/*
 * Set parameters from open or ioctl into the hardware registers.
 */
D 2
dmxparam(tp)
E 2
I 2
dmxparam(tp, t)
E 2
	register struct tty *tp;
I 2
	register struct termios *t;
E 2
{
	register struct dmx_octet *addr;
	register int lpar, lcr;
I 2
	register int cflag = t->c_cflag;
E 2
	int s, unit;
I 2
	int ispeed = ttspeedtab(t->c_ispeed, dmxspeedtab);
        int ospeed = ttspeedtab(t->c_ospeed, dmxspeedtab);
E 2

I 2
        /* check requested parameters */
        if (ospeed < 0 || ispeed < 0 || (cflag&CSIZE) == CS5)
                return(EINVAL);
        if (ispeed == 0)
                ispeed = ospeed;
        /* and copy to tty */
        tp->t_ispeed = t->c_ispeed;
        tp->t_ospeed = t->c_ospeed;
        tp->t_cflag = cflag;

E 2
	addr = (struct dmx_octet *)tp->t_addr;
	unit = minor(tp->t_dev) & 07;
	/*
	 * Block interrupts so parameters will be set
	 * before the line interrupts.
	 */
	s = spltty();
	addr->csr = unit | DMFIR_LCR | DMF_IE;
D 2
	if (tp->t_ispeed == 0) {
		tp->t_state |= TS_HUPCLS;
E 2
I 2
	if (ospeed == 0) {
		tp->t_cflag |= HUPCL;
E 2
		(void) dmxmctl(tp, DMF_OFF, DMSET);
		splx(s);
		return;
	}
D 2
	lpar = (dmx_speeds[tp->t_ospeed]<<12) | (dmx_speeds[tp->t_ispeed]<<8);
E 2
I 2
	lpar = (ospeed<<12) | (ispeed<<8);
E 2
	lcr = DMF_ENA;
D 2
	if ((tp->t_ispeed) == B134)
		lpar |= BITS6|PENABLE;
	else if (tp->t_flags & (RAW|LITOUT|PASS8))
		lpar |= BITS8;
	else {
		lpar |= BITS7|PENABLE;
		/* CHECK FOR XON/XOFF AND SET lcr |= DMF_AUTOX; */
	}
	if (tp->t_flags&EVENP)
		lpar |= EPAR;
	if ((tp->t_ospeed) == B110)
		lpar |= TWOSB;
E 2
I 2
	switch (cflag&CSIZE) {
        case CS6:       lpar |= BITS6; break;
        case CS7:       lpar |= BITS7; break;
        case CS8:       lpar |= BITS8; break;
        }
        if (cflag&PARENB)
                lpar |= PENABLE;
        if (!(cflag&PARODD))
                lpar |= EPAR;
        if (cflag&CSTOPB)
                lpar |= TWOSB;

E 2
	lpar |= (unit&07);
	addr->lpr = lpar;
	addr->lctms = (addr->lctms &~ 0xff) | lcr;
	splx(s);
I 2
	return 0;
E 2
}

/*
 * Process a transmit interrupt on an octet.
 */
dmxxint(sc)
	register struct dmx_softc *sc;
{
	register struct tty *tp;
	register struct dmx_octet *addr;
	register int t;

	addr = (struct dmx_octet *)sc->dmx_octet;
	while ((t = addr->csr) & DMF_TI) {
		if (t & DMF_NXM)
			/* SHOULD RESTART OR SOMETHING... */
			printf("dm%c%d: NXM line %d\n", sc->dmx_type,
			    sc->dmx_unit, sc->dmx_unit0 + (t >> 8 & 7));
		t = t >> 8 & 7;
		tp = sc->dmx_tty + t;
		tp->t_state &= ~TS_BUSY;
		if (tp->t_state & TS_FLUSH)
			tp->t_state &= ~TS_FLUSH;
#define new
#ifndef new
		else if (sc->dmx_dmacount[t]) {
			short cntr;

			/*
			 * Do arithmetic in a short to make up
			 * for lost 16&17 bits.
			 */
			addr->csr = DMFIR_TBA | DMF_IE | t;
			cntr = addr->tba -
			    UBACVT(tp->t_outq.c_cf, sc->dmx_ubanum);
			ndflush(&tp->t_outq, (int)cntr);
		}
#else
		else if (sc->dmx_dmacount[t])
			ndflush(&tp->t_outq, sc->dmx_dmacount[t]);
		sc->dmx_dmacount[t] = 0;
#endif
		(*linesw[tp->t_line].l_start)(tp);
	}
}

dmxstart(tp, sc)
	register struct tty *tp;
	struct dmx_softc *sc;
{
	register struct dmx_octet *addr;
	register int unit, nch;
	int s;

	unit = minor(tp->t_dev) & 07;
	addr = (struct dmx_octet *)tp->t_addr;

	/*
	 * Must hold interrupts in following code to prevent
	 * state of the tp from changing.
	 */
	s = spltty();
	/*
	 * If it's currently active, or delaying, no need to do anything.
	 */
	if (tp->t_state&(TS_TIMEOUT|TS_BUSY|TS_TTSTOP))
		goto out;
	/*
	 * If there are still characters to dma or in the silo,
	 * just reenable the transmitter.
	 */
	addr->csr = DMF_IE | DMFIR_TBUF | unit;
#ifdef new
	if (addr->tsc || sc->dmx_dmacount[unit]) {
#else
	if (addr->tsc) {
#endif
		addr->csr = DMF_IE | DMFIR_LCR | unit;
		addr->lctms = addr->lctms | DMF_TE;
		tp->t_state |= TS_BUSY;
		goto out;
	}
	/*
	 * If there are sleepers, and output has drained below low
	 * water mark, wake up the sleepers.
	 */
D 2
	if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
E 2
I 2
	if (tp->t_outq.c_cc <= tp->t_lowat) {
E 2
		if (tp->t_state & TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
	}
	/*
	 * Now restart transmission unless the output queue is
	 * empty.
	 */
	if (tp->t_outq.c_cc == 0)
		goto out;
D 2
	if (tp->t_flags & (RAW|LITOUT))
E 2
I 2
	if (1 || !(tp->t_oflag&OPOST))	/*XXX*/
E 2
		nch = ndqb(&tp->t_outq, 0);
	else {
		if ((nch = ndqb(&tp->t_outq, 0200)) == 0) {
			/*
		 	* If first thing on queue is a delay process it.
		 	*/
			nch = getc(&tp->t_outq);
			timeout(ttrstrt, (caddr_t)tp, (nch&0x7f)+6);
			tp->t_state |= TS_TIMEOUT;
			goto out;
		}
	}
	/*
	 * If characters to transmit, restart transmission.
	 */
	if (nch >= dmx_mindma) {
		register car;

		sc->dmx_dmacount[unit] = nch;
		addr->csr = DMF_IE | DMFIR_LCR | unit;
		addr->lctms = addr->lctms | DMF_TE;
		car = UBACVT(tp->t_outq.c_cf, sc->dmx_ubanum);
		addr->csr = DMF_IE | DMFIR_TBA | unit;
		addr->tba = car;
		addr->tcc = ((car >> 2) & 0xc000) | nch;
		tp->t_state |= TS_BUSY;
	} else if (nch) {
		register char *cp = tp->t_outq.c_cf;
		register int i;

#ifndef new
		sc->dmx_dmacount[unit] = 0;
#endif
		nch = MIN(nch, DMF_SILOCNT);
		addr->csr = DMF_IE | DMFIR_LCR | unit;
		addr->lctms = addr->lctms | DMF_TE;
		addr->csr = DMF_IE | DMFIR_TBUF | unit;
		for (i = 0; i < nch; i++)
			addr->tbuf = *cp++;
		ndflush(&tp->t_outq, nch);
		tp->t_state |= TS_BUSY;
	}
out:
	splx(s);
}

dmxstop(tp, sc, flag)
	register struct tty *tp;
	struct dmx_softc *sc;
{
	register struct dmx_octet *addr;
	register unit = minor(tp->t_dev) & 7;
	int s;

	addr = (struct dmx_octet *)tp->t_addr;
	/*
	 * Block input/output interrupts while messing with state.
	 */
	s = spltty();
	if (flag) {
		addr->csr = DMF_IE | DMFIR_TBUF | unit;
		if (addr->tsc) {
			/*
			 * Flush regardless of whether we're transmitting
			 * (TS_BUSY), if the silo contains untransmitted
			 * characters.
			 */
			addr->csr = DMFIR_LCR | unit | DMF_IE;
			addr->lctms = addr->lctms | DMF_TE | DMF_FLUSH;
			/* this will interrupt so let dmxxint handle the rest */
			tp->t_state |= TS_FLUSH|TS_BUSY;
		}
/*#ifdef new*/
		sc->dmx_dmacount[unit] = 0;
/*#endif*/
	} else {
		/*
		 * Stop transmission by disabling
		 * the transmitter.  We'll pick up where we
		 * left off by reenabling in dmxstart.
		 */
		addr->csr = DMFIR_LCR | unit | DMF_IE;
		addr->lctms = addr->lctms &~ DMF_TE;
		/* no interrupt here */
		tp->t_state &= ~TS_BUSY;
	}
	splx(s);
}
#endif NDMF + NDMZ
E 1
