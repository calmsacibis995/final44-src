h22053
s 00002/00002/00688
d D 8.1 93/06/11 15:53:33 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00016/00674
d D 7.9 92/10/11 10:20:02 bostic 9 8
c make kernel includes standard
e
s 00001/00001/00689
d D 7.8 92/05/20 16:50:59 bostic 8 7
c Don't clobber the state of the uart too much in probe, in case
c we are using the serial console; from Pace Willisson (pace@blitz.com)
e
s 00007/00003/00683
d D 7.7 92/02/28 18:45:13 sklower 7 6
c add proc argument to ioctl among others
e
s 00001/00005/00685
d D 7.6 92/02/25 14:06:21 torek 6 5
c convert to use new select interface, selrecord/selwakeup
e
s 00004/00002/00686
d D 7.5 91/05/16 17:42:34 marc 5 4
c pass flags through device close
e
s 00005/00005/00683
d D 7.4 91/05/12 18:33:14 william 4 3
c cleanup, put back in kgdb related code, fix nusance with probe
e
s 00216/00061/00472
d D 7.3 91/05/09 20:32:13 william 3 2
c don's changes to allow kgdb
e
s 00016/00009/00517
d D 7.2 91/05/09 20:31:03 william 2 1
c interim version before Don's console work 
e
s 00526/00000/00000
d D 7.1 91/04/03 12:32:20 william 1 0
c date and time created 91/04/03 12:32:20 by william
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1982, 1986, 1990, 1991 The Regents of the University of
 * California. All rights reserved.
E 3
I 3
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
E 3
 *
D 3
 * This code is derived from software contributed to Berkeley by
 * the University of Utah and William Jolitz.
 *
E 3
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "dca.h"
#if NDCA > 0
E 2
I 2
#include "com.h"
#if NCOM > 0
E 2
/*
D 3
 * COM driver, from hp300 dca.c 98626/98644/internal serial interface
E 3
I 3
 * COM driver, based on HP dca driver
 * uses National Semiconductor NS16450/NS16550AF UART
E 3
 */
D 3
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
D 2
#include "sys/user.h"
E 2
I 2
#include "sys/proc.h"
E 2
#include "sys/conf.h"
#include "sys/file.h"
#include "sys/uio.h"
#include "sys/kernel.h"
#include "sys/syslog.h"
E 3
I 3
D 9
#include "param.h"
#include "systm.h"
#include "ioctl.h"
#include "tty.h"
#include "proc.h"
#include "user.h"
#include "conf.h"
#include "file.h"
#include "uio.h"
#include "kernel.h"
#include "syslog.h"
E 9
I 9
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
E 9
E 3

D 9
#include "i386/isa/isa_device.h"
#include "i386/isa/comreg.h"
D 3
#include "i386/isa/ic/ns16450.h"
E 3
I 3
#include "i386/isa/ic/ns16550.h"
E 9
I 9
#include <i386/isa/isa_device.h>
#include <i386/isa/comreg.h>
#include <i386/isa/ic/ns16550.h>
E 9
E 3

D 7
int 	comprobe(), comattach(), comintr(), comstart(), comparam();
E 7
I 7
void	comstart();
int 	comprobe(), comattach(), comintr(), comparam();
E 7

struct	isa_driver comdriver = {
	comprobe, comattach, "com"
};

int	comsoftCAR;
int	com_active;
I 3
int	com_hasfifo;
E 3
D 2
int	ncom = NDCA;
E 2
I 2
int	ncom = NCOM;
I 3
#ifdef COMCONSOLE
int	comconsole = COMCONSOLE;
#else
E 3
E 2
int	comconsole = -1;
I 3
#endif
int	comconsinit;
E 3
int	comdefaultrate = TTYDEF_SPEED;
I 3
int	commajor;
E 3
D 2
short com_addr[NDCA];
struct	tty com_tty[NDCA];
E 2
I 2
short com_addr[NCOM];
struct	tty com_tty[NCOM];
E 2

struct speedtab comspeedtab[] = {
	0,	0,
	50,	COMBRD(50),
	75,	COMBRD(75),
	110,	COMBRD(110),
	134,	COMBRD(134),
	150,	COMBRD(150),
	200,	COMBRD(200),
	300,	COMBRD(300),
	600,	COMBRD(600),
	1200,	COMBRD(1200),
	1800,	COMBRD(1800),
	2400,	COMBRD(2400),
	4800,	COMBRD(4800),
	9600,	COMBRD(9600),
	19200,	COMBRD(19200),
	38400,	COMBRD(38400),
	57600,	COMBRD(57600),
	-1,	-1
};

extern	struct tty *constty;
#ifdef KGDB
I 3
D 9
#include "machine/remote-sl.h"
E 9
I 9
#include <machine/remote-sl.h>
E 9

E 3
extern int kgdb_dev;
extern int kgdb_rate;
extern int kgdb_debug_init;
#endif

#define	UNIT(x)		minor(x)

comprobe(dev)
struct isa_device *dev;
{
D 3
	if ((inb(dev->id_iobase+com_iir) & 0xf8) == 0)
E 3
I 3
D 4
	/*if ((inb(dev->id_iobase+com_iir) & 0x38) == 0)
E 4
I 4
	/* force access to id reg */
D 8
	outb(dev->id_iobase+com_cfcr, 0);
E 8
I 8
	outb(dev->id_iobase+com_cfcr, inb (dev->id_iobase+com_cfcr) & ~0x80);
E 8
	outb(dev->id_iobase+com_iir, 0);
	if ((inb(dev->id_iobase+com_iir) & 0x38) == 0)
E 4
E 3
		return(1);
D 3
	return(0);
E 3
I 3
D 4
printf("base %x val %x ", dev->id_iobase,
	inb(dev->id_iobase+com_iir));*/
E 4
	return(1);
E 3

}


int
comattach(isdp)
struct isa_device *isdp;
{
	struct	tty	*tp;
	u_char		unit;
	int		port = isdp->id_iobase;

I 3
	unit = isdp->id_unit;
E 3
	if (unit == comconsole)
		DELAY(100000);
D 3
	unit = isdp->id_unit;
E 3
	com_addr[unit] = port;
	com_active |= 1 << unit;
D 3
	/* comsoftCAR = isdp->id_flags; */
E 3
I 3
	comsoftCAR |= 1 << unit;	/* XXX */

	/* look for a NS 16550AF UART with FIFOs */
	outb(port+com_fifo, FIFO_ENABLE|FIFO_RCV_RST|FIFO_XMT_RST|FIFO_TRIGGER_14);
	DELAY(100);
	if ((inb(port+com_iir) & IIR_FIFO_MASK) == IIR_FIFO_MASK)
		com_hasfifo |= 1 << unit;

E 3
	outb(port+com_ier, 0);
	outb(port+com_mcr, 0 | MCR_IENABLE);
#ifdef KGDB
D 3
	if (kgdb_dev == makedev(1, unit)) {
E 3
I 3
D 4
	if (1/*kgdb_dev == makedev(commajor, unit)*/) {
E 4
I 4
	if (kgdb_dev == makedev(commajor, unit)) {
E 4
E 3
		if (comconsole == unit)
			kgdb_dev = -1;	/* can't debug over console port */
		else {
D 3
			(void) cominit(unit);
			comconsole = -2; /* XXX */
E 3
I 3
			(void) cominit(unit, kgdb_rate);
E 3
			if (kgdb_debug_init) {
D 3
				printf("com%d: kgdb waiting...", unit);
				/* trap into kgdb */
				asm("trap #15;");
				printf("connected.\n");
E 3
I 3
				/*
				 * Print prefix of device name,
				 * let kgdb_connect print the rest.
				 */
				printf("com%d: ", unit);
				kgdb_connect(1);
E 3
			} else
				printf("com%d: kgdb enabled\n", unit);
		}
	}
#endif
	/*
D 3
	 * Need to reset baud rate, etc. of next print so reset comconsole.
E 3
I 3
	 * Need to reset baud rate, etc. of next print so reset comconsinit.
E 3
	 * Also make sure console is always "hardwired"
	 */
	if (unit == comconsole) {
D 3
		comconsole = -1;
E 3
I 3
		comconsinit = 0;
E 3
		comsoftCAR |= (1 << unit);
	}
D 3
comsoftCAR |= (1 << unit);
E 3
	return (1);
}

D 2
comopen(dev, flag)
E 2
I 2
/* ARGSUSED */
#ifdef __STDC__
comopen(dev_t dev, int flag, int mode, struct proc *p)
#else
comopen(dev, flag, mode, p)
E 2
	dev_t dev;
I 2
	int flag, mode;
	struct proc *p;
#endif
E 2
{
	register struct tty *tp;
	register int unit;
	int error = 0;
 
	unit = UNIT(dev);
D 2
	if (unit >= NDCA || (com_active & (1 << unit)) == 0)
E 2
I 2
	if (unit >= NCOM || (com_active & (1 << unit)) == 0)
E 2
		return (ENXIO);
	tp = &com_tty[unit];
	tp->t_oproc = comstart;
	tp->t_param = comparam;
	tp->t_dev = dev;
	if ((tp->t_state & TS_ISOPEN) == 0) {
		tp->t_state |= TS_WOPEN;
		ttychars(tp);
D 3
		tp->t_iflag = TTYDEF_IFLAG;
		tp->t_oflag = TTYDEF_OFLAG;
		tp->t_cflag = TTYDEF_CFLAG;
		tp->t_lflag = TTYDEF_LFLAG;
		tp->t_ispeed = tp->t_ospeed = comdefaultrate;
E 3
I 3
		if (tp->t_ispeed == 0) {
			tp->t_iflag = TTYDEF_IFLAG;
			tp->t_oflag = TTYDEF_OFLAG;
			tp->t_cflag = TTYDEF_CFLAG;
			tp->t_lflag = TTYDEF_LFLAG;
			tp->t_ispeed = tp->t_ospeed = comdefaultrate;
		}
E 3
		comparam(tp, &tp->t_termios);
		ttsetwater(tp);
D 2
	} else if (tp->t_state&TS_XCLUDE && u.u_uid != 0)
E 2
I 2
	} else if (tp->t_state&TS_XCLUDE && p->p_ucred->cr_uid != 0)
E 2
		return (EBUSY);
	(void) spltty();
	(void) commctl(dev, MCR_DTR | MCR_RTS, DMSET);
	if ((comsoftCAR & (1 << unit)) || (commctl(dev, 0, DMGET) & MSR_DCD))
		tp->t_state |= TS_CARR_ON;
	while ((flag&O_NONBLOCK) == 0 && (tp->t_cflag&CLOCAL) == 0 &&
	       (tp->t_state & TS_CARR_ON) == 0) {
		tp->t_state |= TS_WOPEN;
		if (error = ttysleep(tp, (caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
		    ttopen, 0))
			break;
	}
	(void) spl0();
	if (error == 0)
		error = (*linesw[tp->t_line].l_open)(dev, tp);
	return (error);
}
 
/*ARGSUSED*/
D 5
comclose(dev, flag)
E 5
I 5
comclose(dev, flag, mode, p)
E 5
	dev_t dev;
I 5
	int flag, mode;
	struct proc *p;
E 5
{
	register struct tty *tp;
	register com;
	register int unit;
 
	unit = UNIT(dev);
	com = com_addr[unit];
	tp = &com_tty[unit];
D 5
	(*linesw[tp->t_line].l_close)(tp);
E 5
I 5
	(*linesw[tp->t_line].l_close)(tp, flag);
E 5
	outb(com+com_cfcr, inb(com+com_cfcr) & ~CFCR_SBREAK);
#ifdef KGDB
	/* do not disable interrupts if debugging */
D 3
	if (kgdb_dev != makedev(1, unit))
E 3
I 3
	if (kgdb_dev != makedev(commajor, unit))
E 3
#endif
	outb(com+com_ier, 0);
	if (tp->t_cflag&HUPCL || tp->t_state&TS_WOPEN || 
	    (tp->t_state&TS_ISOPEN) == 0)
		(void) commctl(dev, 0, DMSET);
	ttyclose(tp);
	return(0);
}
 
comread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp = &com_tty[UNIT(dev)];
 
	return ((*linesw[tp->t_line].l_read)(tp, uio, flag));
}
 
comwrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	int unit = UNIT(dev);
	register struct tty *tp = &com_tty[unit];
 
D 3
#ifdef notyet
E 3
	/*
	 * (XXX) We disallow virtual consoles if the physical console is
	 * a serial port.  This is in case there is a display attached that
	 * is not the console.  In that situation we don't need/want the X
	 * server taking over the console.
	 */
	if (constty && unit == comconsole)
		constty = NULL;
D 3
#endif
E 3
	return ((*linesw[tp->t_line].l_write)(tp, uio, flag));
}
 
comintr(unit)
	register int unit;
{
	register com;
	register u_char code;
	register struct tty *tp;

	com = com_addr[unit];
	while (1) {
		code = inb(com+com_iir);
D 3
		switch (code) {
E 3
I 3
		switch (code & IIR_IMASK) {
E 3
		case IIR_NOPEND:
			return (1);
I 3
		case IIR_RXTOUT:
E 3
		case IIR_RXRDY:
D 3
			/* do time-critical read in-line */
E 3
			tp = &com_tty[unit];
D 3
			code = inb(com+com_data);
			if ((tp->t_state & TS_ISOPEN) == 0) {
E 3
I 3
/*
 * Process received bytes.  Inline for speed...
 */
E 3
#ifdef KGDB
D 3
				if (kgdb_dev == makedev(1, unit) &&
				    code == '!') {
					printf("kgdb trap from com%d\n", unit);
					/* trap into kgdb */
					asm("trap #15;");
				}
E 3
I 3
#define	RCVBYTE() \
			code = inb(com+com_data); \
			if ((tp->t_state & TS_ISOPEN) == 0) { \
				if (kgdb_dev == makedev(commajor, unit) && \
				    code == FRAME_END) \
					kgdb_connect(0); /* trap into kgdb */ \
			} else \
				(*linesw[tp->t_line].l_rint)(code, tp)
#else
#define	RCVBYTE() \
			code = inb(com+com_data); \
			if (tp->t_state & TS_ISOPEN) \
				(*linesw[tp->t_line].l_rint)(code, tp)
E 3
#endif
D 3
			} else
				(*linesw[tp->t_line].l_rint)(code, tp);
E 3
I 3

			RCVBYTE();

			if (com_hasfifo & (1 << unit))
				while ((code = inb(com+com_lsr)) & LSR_RCV_MASK) {
					if (code == LSR_RXRDY) {
						RCVBYTE();
					} else
						comeint(unit, code, com);
				}
E 3
			break;
		case IIR_TXRDY:
			tp = &com_tty[unit];
			tp->t_state &=~ (TS_BUSY|TS_FLUSH);
			if (tp->t_line)
				(*linesw[tp->t_line].l_start)(tp);
			else
				comstart(tp);
			break;
		case IIR_RLS:
D 3
			comeint(unit, com);
E 3
I 3
			comeint(unit, inb(com+com_lsr), com);
E 3
			break;
		default:
			if (code & IIR_NOPEND)
				return (1);
			log(LOG_WARNING, "com%d: weird interrupt: 0x%x\n",
			    unit, code);
			/* fall through */
		case IIR_MLSC:
			commint(unit, com);
			break;
		}
	}
}

D 3
comeint(unit, com)
	register int unit;
E 3
I 3
comeint(unit, stat, com)
	register int unit, stat;
E 3
	register com;
{
	register struct tty *tp;
D 3
	register int stat, c;
E 3
I 3
	register int c;
E 3

	tp = &com_tty[unit];
D 3
	stat = inb(com+com_lsr);
E 3
	c = inb(com+com_data);
	if ((tp->t_state & TS_ISOPEN) == 0) {
#ifdef KGDB
		/* we don't care about parity errors */
		if (((stat & (LSR_BI|LSR_FE|LSR_PE)) == LSR_PE) &&
D 3
		    kgdb_dev == makedev(1, unit) && c == '!') {
			printf("kgdb trap from com%d\n", unit);
			/* trap into kgdb */
			asm("trap #15;");
		}
E 3
I 3
		    kgdb_dev == makedev(commajor, unit) && c == FRAME_END)
			kgdb_connect(0); /* trap into kgdb */
E 3
#endif
		return;
	}
	if (stat & (LSR_BI | LSR_FE))
		c |= TTY_FE;
	else if (stat & LSR_PE)
		c |= TTY_PE;
	else if (stat & LSR_OE)
		log(LOG_WARNING, "com%d: silo overflow\n", unit);
	(*linesw[tp->t_line].l_rint)(c, tp);
}

commint(unit, com)
	register int unit;
	register com;
{
	register struct tty *tp;
	register int stat;

	tp = &com_tty[unit];
	stat = inb(com+com_msr);
	if ((stat & MSR_DDCD) && (comsoftCAR & (1 << unit)) == 0) {
		if (stat & MSR_DCD)
			(void)(*linesw[tp->t_line].l_modem)(tp, 1);
		else if ((*linesw[tp->t_line].l_modem)(tp, 0) == 0)
			outb(com+com_mcr,
				inb(com+com_mcr) & ~(MCR_DTR | MCR_RTS) | MCR_IENABLE);
	} else if ((stat & MSR_DCTS) && (tp->t_state & TS_ISOPEN) &&
		   (tp->t_flags & CRTSCTS)) {
		/* the line is up and we want to do rts/cts flow control */
		if (stat & MSR_CTS) {
			tp->t_state &=~ TS_TTSTOP;
			ttstart(tp);
		} else
			tp->t_state |= TS_TTSTOP;
	}
}

D 7
comioctl(dev, cmd, data, flag)
E 7
I 7
comioctl(dev, cmd, data, flag, p)
E 7
	dev_t dev;
I 7
	int cmd, flag;
E 7
	caddr_t data;
I 7
	struct proc *p;
E 7
{
	register struct tty *tp;
	register int unit = UNIT(dev);
	register com;
	register int error;
 
	tp = &com_tty[unit];
D 7
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
E 7
I 7
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag, p);
E 7
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, data, flag);
	if (error >= 0)
		return (error);

	com = com_addr[unit];
	switch (cmd) {

	case TIOCSBRK:
		outb(com+com_cfcr, inb(com+com_cfcr) | CFCR_SBREAK);
		break;

	case TIOCCBRK:
		outb(com+com_cfcr, inb(com+com_cfcr) & ~CFCR_SBREAK);
		break;

	case TIOCSDTR:
		(void) commctl(dev, MCR_DTR | MCR_RTS, DMBIS);
		break;

	case TIOCCDTR:
		(void) commctl(dev, MCR_DTR | MCR_RTS, DMBIC);
		break;

	case TIOCMSET:
		(void) commctl(dev, *(int *)data, DMSET);
		break;

	case TIOCMBIS:
		(void) commctl(dev, *(int *)data, DMBIS);
		break;

	case TIOCMBIC:
		(void) commctl(dev, *(int *)data, DMBIC);
		break;

	case TIOCMGET:
		*(int *)data = commctl(dev, 0, DMGET);
		break;

	default:
		return (ENOTTY);
	}
	return (0);
}

comparam(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	register com;
	register int cfcr, cflag = t->c_cflag;
	int unit = UNIT(tp->t_dev);
	int ospeed = ttspeedtab(t->c_ospeed, comspeedtab);
 
	/* check requested parameters */
        if (ospeed < 0 || (t->c_ispeed && t->c_ispeed != t->c_ospeed))
                return(EINVAL);
        /* and copy to tty */
        tp->t_ispeed = t->c_ispeed;
        tp->t_ospeed = t->c_ospeed;
        tp->t_cflag = cflag;

	com = com_addr[unit];
	outb(com+com_ier, IER_ERXRDY | IER_ETXRDY | IER_ERLS /*| IER_EMSC*/);
	if (ospeed == 0) {
		(void) commctl(unit, 0, DMSET);	/* hang up line */
		return(0);
	}
	outb(com+com_cfcr, inb(com+com_cfcr) | CFCR_DLAB);
	outb(com+com_data, ospeed & 0xFF);
	outb(com+com_ier, ospeed >> 8);
	switch (cflag&CSIZE) {
	case CS5:
		cfcr = CFCR_5BITS; break;
	case CS6:
		cfcr = CFCR_6BITS; break;
	case CS7:
		cfcr = CFCR_7BITS; break;
	case CS8:
		cfcr = CFCR_8BITS; break;
	}
	if (cflag&PARENB) {
		cfcr |= CFCR_PENAB;
		if ((cflag&PARODD) == 0)
			cfcr |= CFCR_PEVEN;
	}
	if (cflag&CSTOPB)
		cfcr |= CFCR_STOPB;
	outb(com+com_cfcr, cfcr);
I 3

	if (com_hasfifo & (1 << unit))
		outb(com+com_fifo, FIFO_ENABLE | FIFO_TRIGGER_14);

E 3
	return(0);
}
 
I 7
void
E 7
comstart(tp)
	register struct tty *tp;
{
	register com;
	int s, unit, c;
 
	unit = UNIT(tp->t_dev);
	com = com_addr[unit];
	s = spltty();
	if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP))
		goto out;
	if (tp->t_outq.c_cc <= tp->t_lowat) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
D 6
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
E 6
I 6
		selwakeup(&tp->t_wsel);
E 6
	}
	if (tp->t_outq.c_cc == 0)
		goto out;
	if (inb(com+com_lsr) & LSR_TXRDY) {
		c = getc(&tp->t_outq);
		tp->t_state |= TS_BUSY;
		outb(com+com_data, c);
I 3
		if (com_hasfifo & (1 << unit))
			for (c = 1; c < 16 && tp->t_outq.c_cc; ++c)
				outb(com+com_data, getc(&tp->t_outq));
E 3
	}
out:
	splx(s);
}
 
/*
 * Stop output on a line.
 */
/*ARGSUSED*/
comstop(tp, flag)
	register struct tty *tp;
{
	register int s;

	s = spltty();
	if (tp->t_state & TS_BUSY) {
		if ((tp->t_state&TS_TTSTOP)==0)
			tp->t_state |= TS_FLUSH;
	}
	splx(s);
}
 
commctl(dev, bits, how)
	dev_t dev;
	int bits, how;
{
	register com;
	register int unit;
	int s;

	unit = UNIT(dev);
	com = com_addr[unit];
	s = spltty();
	switch (how) {

	case DMSET:
		outb(com+com_mcr, bits | MCR_IENABLE);
		break;

	case DMBIS:
		outb(com+com_mcr, inb(com+com_mcr) | bits | MCR_IENABLE);
		break;

	case DMBIC:
		outb(com+com_mcr, inb(com+com_mcr) & ~bits | MCR_IENABLE);
		break;

	case DMGET:
		bits = inb(com+com_msr);
		break;
	}
	(void) splx(s);
	return(bits);
I 3
}

/*
 * Following are all routines needed for COM to act as console
 */
D 9
#include "i386/i386/cons.h"
E 9
I 9
#include <i386/i386/cons.h>
E 9

comcnprobe(cp)
	struct consdev *cp;
{
	int unit;
D 4
	extern int comopen();
E 4

	/* locate the major number */
	for (commajor = 0; commajor < nchrdev; commajor++)
		if (cdevsw[commajor].d_open == comopen)
			break;

	/* XXX: ick */
	unit = CONUNIT;
	com_addr[CONUNIT] = CONADDR;

	/* make sure hardware exists?  XXX */

	/* initialize required fields */
	cp->cn_dev = makedev(commajor, unit);
	cp->cn_tp = &com_tty[unit];
#ifdef	COMCONSOLE
	cp->cn_pri = CN_REMOTE;		/* Force a serial port console */
#else
	cp->cn_pri = CN_NORMAL;
#endif
}

comcninit(cp)
	struct consdev *cp;
{
	int unit = UNIT(cp->cn_dev);

	cominit(unit, comdefaultrate);
	comconsole = unit;
	comconsinit = 1;
}

cominit(unit, rate)
	int unit, rate;
{
	register int com;
	int s;
	short stat;

#ifdef lint
	stat = unit; if (stat) return;
#endif
	com = com_addr[unit];
	s = splhigh();
	outb(com+com_cfcr, CFCR_DLAB);
	rate = ttspeedtab(comdefaultrate, comspeedtab);
	outb(com+com_data, rate & 0xFF);
	outb(com+com_ier, rate >> 8);
	outb(com+com_cfcr, CFCR_8BITS);
	outb(com+com_ier, IER_ERXRDY | IER_ETXRDY);
	outb(com+com_fifo, FIFO_ENABLE|FIFO_RCV_RST|FIFO_XMT_RST|FIFO_TRIGGER_14);
	stat = inb(com+com_iir);
	splx(s);
}

comcngetc(dev)
{
	register com = com_addr[UNIT(dev)];
	short stat;
	int c, s;

#ifdef lint
	stat = dev; if (stat) return(0);
#endif
	s = splhigh();
	while (((stat = inb(com+com_lsr)) & LSR_RXRDY) == 0)
		;
	c = inb(com+com_data);
	stat = inb(com+com_iir);
	splx(s);
	return(c);
}

/*
 * Console kernel output character routine.
 */
comcnputc(dev, c)
	dev_t dev;
	register int c;
{
	register com = com_addr[UNIT(dev)];
	register int timo;
	short stat;
	int s = splhigh();

#ifdef lint
	stat = dev; if (stat) return;
#endif
#ifdef KGDB
	if (dev != kgdb_dev)
#endif
	if (comconsinit == 0) {
		(void) cominit(UNIT(dev), comdefaultrate);
		comconsinit = 1;
	}
	/* wait for any pending transmission to finish */
	timo = 50000;
	while (((stat = inb(com+com_lsr)) & LSR_TXRDY) == 0 && --timo)
		;
	outb(com+com_data, c);
	/* wait for this transmission to complete */
	timo = 1500000;
	while (((stat = inb(com+com_lsr)) & LSR_TXRDY) == 0 && --timo)
		;
	/* clear any interrupts generated by this transmission */
	stat = inb(com+com_iir);
	splx(s);
E 3
}
#endif
E 1
