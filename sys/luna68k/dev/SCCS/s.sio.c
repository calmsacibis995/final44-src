h49925
s 00002/00002/00718
d D 8.1 93/06/10 22:17:05 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00059/00004/00661
d D 7.9 93/06/08 10:38:28 akito 9 8
c KGDB support
e
s 00020/00053/00645
d D 7.8 93/05/02 05:42:50 akito 8 7
c rewrite probe routine for BMC support
e
s 00037/00001/00661
d D 7.7 93/02/04 15:25:00 akito 7 6
c add line for error detect & multi byte read
e
s 00028/00004/00634
d D 7.6 92/12/25 13:08:39 akito 6 5
c add sio_port_info()
e
s 00008/00002/00630
d D 7.5 92/12/14 16:13:07 akito 5 4
c support TIOCCONS console redirection
e
s 00014/00014/00618
d D 7.4 92/12/10 13:50:46 akito 4 3
c make kernel includes standard, again.
e
s 00323/00388/00309
d D 7.3 92/11/17 16:19:30 akito 3 2
c for bmc driver
e
s 00013/00013/00684
d D 7.2 92/10/11 10:57:22 bostic 2 1
c make kernel includes standard
e
s 00697/00000/00000
d D 7.1 92/06/15 06:46:03 fujita 1 0
c date and time created 92/06/15 06:46:03 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 10
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * sio.c -- NEC uPD7201A UART Device Driver
D 3
 * by A.Fujita, NOV-25-1991
E 3
I 3
 *    remaked by A.Fujita, NOV-5-1992
E 3
 */

#include "sio.h"
#if NSIO > 0

D 3
#undef LOCAL_CONSOLE
E 3
I 3
#include "bmc.h"
E 3

D 3
/*
 *  OMRON LUNA internal serial interface
 *  uese NEC uPD7201A SIO
 */
E 3
I 3
D 4
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/ioctl.h"
#include "sys/proc.h"
#include "sys/tty.h"
#include "sys/conf.h"
#include "sys/file.h"
#include "sys/uio.h"
#include "sys/kernel.h"
#include "sys/syslog.h"
E 4
I 4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
E 4
E 3

D 2
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/ioctl.h"
#include "sys/proc.h"
#include "sys/tty.h"
#include "sys/conf.h"
#include "sys/file.h"
#include "sys/uio.h"
#include "sys/kernel.h"
#include "sys/syslog.h"
E 2
I 2
D 3
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
E 3
I 3
D 4
#include "device.h"
#include "sioreg.h"
#include "siovar.h"
E 4
I 4
#include <luna68k/dev/device.h>
#include <luna68k/dev/sioreg.h>
#include <luna68k/dev/siovar.h>
E 4
E 3
E 2

D 2
#include "device.h"
#include "sioreg.h"
E 2
I 2
D 3
#include <luna68k/dev/device.h>
#include <luna68k/dev/sioreg.h>
E 3
I 3
struct sio_portc *sio_port_assign();
I 6
struct sio_portc *sio_port_get();
E 6
E 3
E 2

D 3
#define SIO_IPL		6

E 3
int	sioprobe();
I 3
int	sioopen();
void	siostart();
int	sioparam();
int	siointr();

E 3
struct	driver siodriver = {
	sioprobe, "sio",
};

D 3
void	siostart();
int	sioparam(), siointr();
int	sio_active;
int	sioconsole = -1;
int	sioconsinit;
int	siodefaultrate = TTYDEF_SPEED;
int	siomajor;
struct	siodevice *sio_addr[2];
struct	tty sio_tty[NSIO];
E 3
I 3
D 8
#define NPORT	2					/* uPD7201A has 2 serial-port */
#define NLINE	1					/* number of active line */
E 3

E 8
D 3
#define	siounit(x)		minor(x)
E 3
I 3
struct	sio_portc sio_portc[NPORT] = {
D 8
	{ -1, -1, (struct siodevice *) 0x51000000, (int (*)()) 0 },
	{ -1, -1, (struct siodevice *) 0x51000004, (int (*)()) 0 }
E 8
I 8
	{ -1, -1, 0, (struct siodevice *) 0x51000000, (int (*)()) 0 },
	{ -1, -1, 1, (struct siodevice *) 0x51000004, (int (*)()) 0 }
E 8
};
E 3

I 3
D 8
struct	sio_softc sio_softc[NLINE];
E 8
I 8
struct	sio_softc sio_softc[NSIO];
E 8
E 3

D 3
#ifndef	LOCAL_CONSOLE
E 3
I 3
int	sio_init_done = 0;
D 8
int	siounitbase = 0;				/* This counter is used unit number assignment */
E 8
E 3

D 3
/*
 * local buffering
 */
E 3
I 3
int	siosoftCAR;
int	sio_active;
D 5
int	sioconsole;
E 5
I 5
int	sioconsole = -1;
E 5
int	siodefaultrate = TTYDEF_SPEED;
D 6
int	siomajor = 0;
E 6
I 6
int	siomajor = 12;
E 6
E 3

D 3
#define LOCAL_BUFSIZ	128
E 3
I 3
D 8
struct	tty sio_tty[NLINE];
E 8
I 8
struct	tty sio_tty[NSIO];
E 8
E 3

D 3
struct local_buf {
	u_char	*push;
	u_char	*pop;
	u_char	buf[LOCAL_BUFSIZ+4];
E 3
I 3
struct speedtab siospeedtab[] = {
	2400,	WR4_BAUD24,
	4800,	WR4_BAUD48,
	9600,	WR4_BAUD96,
E 3
};

D 3
struct local_buf rbuf, *rbp = &rbuf;
E 3
I 3
#define	siounit(x)		minor(x)
E 3

I 5
extern	struct tty *constty;
E 5

I 9
#ifdef KGDB
E 9
D 3
siolbufinit(bp)
	register struct local_buf *bp;
{
	bp->push = bp->pop = &(bp->buf[LOCAL_BUFSIZ]);
}

siolbufpush(bp, c)
	register struct local_buf *bp;
	register int c;
{

	*(--bp->push) = c;

	if (bp->push == &(bp->buf[0]))
		bp->push = &(bp->buf[LOCAL_BUFSIZ]);

	if (bp->push == bp->pop)
		bp->pop == (u_char *) 0;
}

int
siolbufpop(bp)
	register struct local_buf *bp;
{
	register int c;

	if (bp->pop == (u_char *) 0)
		bp->pop = bp->push;

	c = *(--bp->pop);

	if (bp->pop == &(bp->buf[0]))
		bp->pop = &(bp->buf[LOCAL_BUFSIZ]);

	return(c);
}

int
siolbufempty(bp)
	register struct local_buf *bp;
{
	if (bp->push == bp->pop)
		return(1);
	else
		return(0);
}
#endif

E 3
/*
I 9
 * Kernel GDB support
 */
#include <machine/remote-sl.h>

extern dev_t kgdb_dev;
extern int kgdb_rate;
extern int kgdb_debug_init;
#endif

/*
E 9
D 3
 * probing
E 3
I 3
 *  probe routines
E 3
 */

sioprobe(hd)
	register struct hp_device *hd;
{
D 3
	register struct siodevice *sio;
	register int unit;
E 3
I 3
D 8
	register int port;
E 8
I 8
	int unit = hd->hp_unit;
	register struct sio_softc *sc = &sio_softc[unit];
E 8
	register struct sio_portc *pc;
D 8
	register struct sio_softc *sc;
E 8
E 3

D 3
	sio = (struct siodevice *)hd->hp_addr;
	unit = hd->hp_unit;
E 3
I 3
D 8
	sioinit((struct siodevice *) hd->hp_addr, siodefaultrate);
E 8
I 8
	if (sc->sc_pc != 0) {
		pc = sc->sc_pc;
		printf("sio%d: port %d, address 0x%x, intr 0x%x (console)\n",
		       pc->pc_unit, pc->pc_port, pc->pc_addr, pc->pc_intr);
D 9
		return(0);
E 9
I 9
		return(1);
E 9
	}
E 8
E 3

D 3
	hd->hp_ipl = SIO_IPL;
E 3
I 3
D 8
	/* locate the major number */
	for (siomajor = 0; siomajor < nchrdev; siomajor++)
		if (cdevsw[siomajor].d_open == sioopen)
			break;
E 8
I 8
D 9
	sc->sc_pc = pc = sio_port_assign(SIO_PORT, siomajor, unit, siointr);
E 9
I 9
	sc->sc_pc = pc = sio_port_assign(unit, siomajor, unit, siointr);
E 9
E 8
E 3

D 3
	/*
	 *  We must set hardware address here.
	 *  but now already it's done.
E 3
I 3
D 8
	for (port = 0; port < NPORT; port++) {
		pc = &sio_portc[port];
E 8
I 8
	printf("sio%d: port %d, address 0x%x, intr 0x%x\n",
	       pc->pc_unit, pc->pc_port, pc->pc_addr, pc->pc_intr);
E 8
E 3

D 3
	sio_addr[unit] = sio;
E 3
I 3
D 8
		if (pc->pc_major != -1) {
			printf("%s%d: port %d, address 0x%x, intr 0x%x (console)\n",
			       (pc->pc_major == siomajor ? "sio" : "bmc" ),
			       pc->pc_unit, port, pc->pc_addr, pc->pc_intr);
			continue;
		}
E 3

D 3
	*/
E 3
I 3
		pc->pc_addr =
			(struct siodevice *)((u_long) hd->hp_addr + (sizeof(struct siodevice) * port));
#if NBMC > 0
		if (bmcinit(port))
			continue;
#endif
		if (++siounitbase < NLINE) {
			pc->pc_major = siomajor;
			pc->pc_intr  = siointr;
			pc->pc_unit  = siounitbase;
			printf("sio%d: port %d, address 0x%x\n", pc->pc_unit, port, pc->pc_addr);
E 3

D 3
	sio_active |= 1 << unit;
E 3
I 3
			sc = &sio_softc[pc->pc_unit];
			sc->sc_pc = pc;
E 3

D 3
	/*
	 *  We must pick up information from hd->hp_flags here.
	 *  It should be used instead of TTYDEF_CFLAG or like something.
	 *  
	 */
E 3
I 3
			sio_active |= 1 << pc->pc_unit;
			siosoftCAR |= 1 << pc->pc_unit;
		}
	}
E 8
I 8
	sio_active |= 1 << unit;
I 9

#ifdef KGDB
	if (major(kgdb_dev) == siomajor) {
#ifdef	notdef
		if (sioconsole == siounit(kgdb_dev)) {
			kgdb_dev = NODEV; /* can't debug over console port */
		} else {
#endif
		/*
		 * The following could potentially be replaced
		 * by the corresponding code in dcmcnprobe.
		 */
			if (kgdb_debug_init) {
				printf("sio%d: ", siounit(kgdb_dev));
				kgdb_connect(1);
			} else
				printf("sio%d: kgdb enabled\n", siounit(kgdb_dev));
#ifdef	notdef
		}
#endif
		/* end could be replaced */
	}
#endif

E 9
	siosoftCAR |= 1 << unit;
	return(1);
E 8
}
E 3

D 3
#ifdef LOCAL_CONSOLE
E 3
I 3
struct sio_portc *
sio_port_assign(port, major, unit, intr)
	int	port, major, unit;
	int	(*intr)();
{
D 6
	register struct sio_portc *pc = &sio_portc[port];
E 6
I 6
	register struct sio_portc *pc;
E 6
E 3

D 3
	/*
	 *  Enable Interrupt
	 *    I must rewirte basic handlers of console support,
	 *    Because it does not work, if interrupt occar.
	 *    Now using LOCAL_CONSOLE, so the problem isn't happend.
	 *
	 */
E 3
I 3
D 6
	if (pc->pc_major != -1)
		return((struct sio_portc *) 0);
E 6
I 6
	pc = &sio_portc[port];
E 6
E 3

I 6
D 8
/*
	if ((pc->pc_major != -1) && (major != 2))
		return((struct sio_portc *) 0);
 */
E 8
E 6
D 3
	sioreg(REG(unit, WR1), WR1_RXALLS | WR1_TXENBL);
E 3
I 3
	pc->pc_major = major;
	pc->pc_intr  = intr;
	pc->pc_unit  = unit;
E 3

D 3
#endif
	if (unit == sioconsole) {
		sioconsinit = 0;
	}

	return (1);
E 3
I 3
	return(pc);
I 6
}

struct sio_portc *
sio_port_get(port)
	int port;
{
	register struct sio_portc *pc;

	pc = &sio_portc[port];

	return(pc);
}

int 
sio_port_info()
{
	printf("sio_port_info[sio.c]:\t{%d}       major = %d, unit = %d, intr = 0x%x\n",
		0, sio_portc[0].pc_major, sio_portc[0].pc_unit, sio_portc[0].pc_intr);
	printf("sio_port_info[sio.c]:\t{%d}       major = %d, unit = %d, intr = 0x%x\n",
		1, sio_portc[1].pc_major, sio_portc[1].pc_unit, sio_portc[1].pc_intr);
E 6
E 3
}

D 3
int
E 3
I 3

/*
 *  entry routines
 */

E 3
/* ARGSUSED */
#ifdef __STDC__
sioopen(dev_t dev, int flag, int mode, struct proc *p)
#else
sioopen(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
#endif
{
	register struct tty *tp;
	register int unit;
	int error = 0;

	unit = siounit(dev);
D 3
	if (unit >= NSIO || (sio_active & (1 << unit)) == 0)
E 3
I 3
D 8
	if (unit >= NLINE || (sio_active & (1 << unit)) == 0)
E 8
I 8
	if (unit >= NSIO || (sio_active & (1 << unit)) == 0)
E 8
E 3
		return (ENXIO);
D 3

E 3
	tp = &sio_tty[unit];
	tp->t_oproc = siostart;
	tp->t_param = sioparam;
	tp->t_dev = dev;
D 3

E 3
	if ((tp->t_state & TS_ISOPEN) == 0) {
		tp->t_state |= TS_WOPEN;
		ttychars(tp);
		if (tp->t_ispeed == 0) {
			tp->t_iflag = TTYDEF_IFLAG;
			tp->t_oflag = TTYDEF_OFLAG;
I 3
/*			tp->t_cflag = TTYDEF_CFLAG;		*/
E 3
			tp->t_cflag = (CREAD | CS8 | HUPCL);
			tp->t_lflag = TTYDEF_LFLAG;
			tp->t_ispeed = tp->t_ospeed = siodefaultrate;
		}
		sioparam(tp, &tp->t_termios);
		ttsetwater(tp);
	} else if (tp->t_state&TS_XCLUDE && p->p_ucred->cr_uid != 0)
		return (EBUSY);
D 3

	/*
	 *  We must set DTR & RTS here.
	 *  Need a routine like XXXmctl().
	 *
	 */

	/*
	 *  The next statment should be executed, when Carrier Detected
	 *  or using special serial line which ignore carrier.
	 *
	 *  Should be checked out RR0, I think. Omit this time.
	 */

	 tp->t_state |= TS_CARR_ON;

E 3
I 3
	(void) siomctl(dev, WR5_DTR | WR5_RTS, DMSET);
	if ((siosoftCAR & (1 << unit)) || (siomctl(dev, 0, DMGET) & RR0_DCD))
		tp->t_state |= TS_CARR_ON;
E 3
	(void) spltty();
D 3

E 3
	while ((flag&O_NONBLOCK) == 0 && (tp->t_cflag&CLOCAL) == 0 &&
	       (tp->t_state & TS_CARR_ON) == 0) {
		tp->t_state |= TS_WOPEN;
		if (error = ttysleep(tp, (caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
		    ttopen, 0))
			break;
	}
D 3

E 3
	(void) spl0();
D 3

E 3
	if (error == 0)
		error = (*linesw[tp->t_line].l_open)(dev, tp);
D 3

E 3
	return (error);
}
D 3
 
E 3
I 3

E 3
/*ARGSUSED*/
sioclose(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	register struct tty *tp;
D 3
	register struct siodevice *sio;
E 3
	register int unit;

	unit = siounit(dev);
D 3
	sio = sio_addr[unit];
E 3
	tp = &sio_tty[unit];
D 3

E 3
	(*linesw[tp->t_line].l_close)(tp, flag);
D 3

	/*
	 *  We must send BREAK to current line here.
	 *  Not supported yet.
	 */

	/*
	 *  We must reset DTR & RTS here.
	 *  Need a routine like XXXmctl().
	 *
	 */

E 3
I 3
	(void) siomctl(dev, WR5_BREAK, DMBIS);
	if (tp->t_cflag&HUPCL || tp->t_state&TS_WOPEN ||
	    (tp->t_state&TS_ISOPEN) == 0)
		(void) siomctl(dev, 0, DMSET);
E 3
	ttyclose(tp);
	return (0);
}
 
sioread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
D 3
	int flag;
E 3
{
	register struct tty *tp = &sio_tty[siounit(dev)];
 
	return ((*linesw[tp->t_line].l_read)(tp, uio, flag));
}
 
siowrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
D 3
	int flag;
E 3
{
D 5
	register struct tty *tp = &sio_tty[siounit(dev)];
E 5
I 5
	register int unit = siounit(dev);
	register struct tty *tp = &sio_tty[unit];

	if ((unit == sioconsole) && constty &&
	    (constty->t_state&(TS_CARR_ON|TS_ISOPEN))==(TS_CARR_ON|TS_ISOPEN))
		tp = constty;
E 5

	return ((*linesw[tp->t_line].l_write)(tp, uio, flag));
}

D 3
siointr()
{
	register int unit = 0;
	register struct siodevice *sio = sio_addr[unit];
	register u_char code;
E 3
I 3
/*
 * Stop output on a line.
 */
/*ARGSUSED*/
siostop(tp, flag)
E 3
	register struct tty *tp;
D 3
	int s, rr;
E 3
I 3
{
	register int s;
E 3

D 3
	rr = siogetreg(unit);
	tp = &sio_tty[unit];
	if (rr & RR_RXRDY) {
		code = sio->sio_data;
		if ((tp->t_state & TS_ISOPEN) != 0)
			(*linesw[tp->t_line].l_rint)(code, tp);
#ifndef LOCAL_CONSOLE
		else
			siolbufpush(rbp, code);
#endif
E 3
I 3
	s = spltty();
	if (tp->t_state & TS_BUSY) {
		if ((tp->t_state&TS_TTSTOP)==0)
			tp->t_state |= TS_FLUSH;
E 3
	}
D 3

	if (rr & RR_TXRDY) {
		sio->sio_cmd = WR0_RSTPEND;
		tp->t_state &= ~(TS_BUSY|TS_FLUSH);
		if (tp->t_line)
			(*linesw[tp->t_line].l_start)(tp);
		else
			siostart(tp);
	}
E 3
I 3
	splx(s);
E 3
}

sioioctl(dev, cmd, data, flag, p)
	dev_t dev;
	int cmd;
	caddr_t data;
	int flag;
	struct proc *p;
{
	register struct tty *tp;
	register int unit = siounit(dev);
D 3
	register struct siodevice *sio;
E 3
	register int error;
D 3
 
E 3
I 3

E 3
	tp = &sio_tty[unit];
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag, p);
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, data, flag);
	if (error >= 0)
		return (error);

D 3
	/*
	 *  We must support flow control of serial lines.
	 *  Not yet.
	 */

	sio = sio_addr[unit];
E 3
	switch (cmd) {

	case TIOCSBRK:
I 3
		(void) siomctl(dev, WR5_BREAK, DMBIS);
		break;

E 3
	case TIOCCBRK:
I 3
		(void) siomctl(dev, WR5_BREAK, DMBIC);
		break;

E 3
	case TIOCSDTR:
I 3
		(void) siomctl(dev, WR5_DTR | WR5_RTS, DMBIS);
		break;

E 3
	case TIOCCDTR:
I 3
		(void) siomctl(dev, WR5_DTR | WR5_RTS, DMBIC);
		break;

E 3
	case TIOCMSET:
I 3
		(void) siomctl(dev, *(int *)data, DMSET);
		break;

E 3
	case TIOCMBIS:
I 3
		(void) siomctl(dev, *(int *)data, DMBIS);
		break;

E 3
	case TIOCMBIC:
I 3
		(void) siomctl(dev, *(int *)data, DMBIC);
		break;

E 3
	case TIOCMGET:
I 3
		*(int *)data = siomctl(dev, 0, DMGET);
		break;

E 3
	default:
		return (ENOTTY);
	}
D 3

E 3
	return (0);
}

D 3
sioparam(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	return (0);
}
E 3

I 3
/*
 *
 */

E 3
void
siostart(tp)
	register struct tty *tp;
{
	register struct siodevice *sio;
D 3
	int s, unit, c, rr;
E 3
I 3
	register int rr;
	int s, unit, c;
E 3
 
	unit = siounit(tp->t_dev);
D 3
	sio = sio_addr[unit];

E 3
I 3
	sio = sio_softc[unit].sc_pc->pc_addr;
E 3
	s = spltty();
D 3

E 3
	if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP))
		goto out;
D 3

E 3
	if (tp->t_outq.c_cc <= tp->t_lowat) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		selwakeup(&tp->t_wsel);
	}
D 3

E 3
	if (tp->t_outq.c_cc == 0)
		goto out;
D 3

	rr = siogetreg(unit);
E 3
I 3
	rr = siogetreg(sio);
E 3
	if (rr & RR_TXRDY) {
		c = getc(&tp->t_outq);
		tp->t_state |= TS_BUSY;
		sio->sio_data = c;
	}
D 3

E 3
out:
	splx(s);
}
D 3
 
E 3
I 3

sioparam(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	int unit = siounit(tp->t_dev);
	register struct siodevice *sio;
	register cflag = t->c_cflag;
	register u_char wr;
	int ospeed = ttspeedtab(t->c_ospeed, siospeedtab);

	sio = sio_softc[unit].sc_pc->pc_addr;

	switch (cflag & CSIZE) {
	case CS5:
	case CS6:
	case CS7:
	case CS8:
		break;
	}

	wr = ospeed;

	if (cflag & PARENB) {
		wr |= WR4_PARENAB;
		if ((cflag&PARODD) == 0)
			wr |= WR4_EPARITY;
	}

	if (cflag & CSTOPB)
		wr |= WR4_STOP2;			/* 2 stop bit */
	else
		wr |= WR4_STOP1;			/* 1 stop bit */

	(void) sioreg(sio, WR4, wr);

	return (0);
}

siomctl()
{
	return (0);
}


E 3
/*
D 3
 * Stop output on a line.
E 3
I 3
 *  Interrupt handling
E 3
 */
D 3
/*ARGSUSED*/
siostop(tp, flag)
	register struct tty *tp;
	int flag;
E 3
I 3

void
_siointr()
E 3
{
D 3
	register int s;
E 3
I 3
	register int port;
	register struct sio_portc *pc;
E 3

D 3
	s = spltty();
	if (tp->t_state & TS_BUSY) {
		if ((tp->t_state&TS_TTSTOP)==0)
			tp->t_state |= TS_FLUSH;
E 3
I 3
	for (port = 0; port < NPORT; port++) {
		pc = &sio_portc[port];

		if (pc->pc_major != -1)
			(pc->pc_intr)(pc->pc_unit);
E 3
	}
D 3
	splx(s);
E 3
}

I 3
siointr(unit)
	register int unit;
{
	register struct siodevice *sio = sio_softc[unit].sc_pc->pc_addr;
	register u_char code;
	register struct tty *tp;
	int s, rr;

	tp = &sio_tty[unit];
D 7
	rr = siogetreg(sio);
E 7

I 7
start:
	rr = siogetreg(sio);
E 7
	if (rr & RR_RXRDY) {
I 7
		if (rr & (RR_FRAMING | RR_OVERRUN | RR_PARITY)) {
			sioeint(unit, rr, sio);
			goto start;
		}

E 7
		code = sio->sio_data;
		if ((tp->t_state & TS_ISOPEN) != 0)
			(*linesw[tp->t_line].l_rint)(code, tp);
I 7
D 9

E 9
I 9
#ifdef KGDB
		else {
			if (code == FRAME_END &&
			    kgdb_dev == makedev(siomajor, unit))
				kgdb_connect(0); /* trap into kgdb */
		}
#endif
E 9
		while ((rr = siogetreg(sio)) & RR_RXRDY) {
			code = sio->sio_data;
			if ((tp->t_state & TS_ISOPEN) != 0)
				(*linesw[tp->t_line].l_rint)(code, tp);
I 9
#ifdef KGDB
			else {
				if (code == FRAME_END &&
				    kgdb_dev == makedev(siomajor, unit))
					kgdb_connect(0); /* trap into kgdb */
			}
#endif
E 9
		}
E 7
	}

	if (rr & RR_TXRDY) {
		sio->sio_cmd = WR0_RSTPEND;
		tp->t_state &= ~(TS_BUSY|TS_FLUSH);
		if (tp->t_line)
			(*linesw[tp->t_line].l_start)(tp);
		else
			siostart(tp);
	}
I 7
}

sioeint(unit, stat, sio)
	register int unit, stat;
	register struct siodevice *sio;
{
	register struct tty *tp;
	register int code;

	tp = &sio_tty[unit];

	code = sio->sio_data;

	sio->sio_cmd = WR0_ERRRST;

D 9
	if ((tp->t_state & TS_ISOPEN) == 0)
E 9
I 9
	if ((tp->t_state & TS_ISOPEN) == 0) {
#ifdef KGDB
		/* we don't care about parity errors */
		if (((stat & (RR_FRAMING|RR_PARITY)) == RR_PARITY) &&
		    kgdb_dev == makedev(siomajor, unit) && code == FRAME_END)
			kgdb_connect(0); /* trap into kgdb */
#endif
E 9
		return;
I 9
	}
E 9

	if (stat & RR_FRAMING)
		code |= TTY_FE;
	else if (stat & RR_PARITY)
		code |= TTY_PE;

	(*linesw[tp->t_line].l_rint)(code, tp);
E 7
}

E 3
/*
 * Following are all routines needed for SIO to act as console
 */
D 2
#include "../luna68k/cons.h"
E 2
I 2
D 3
#include <luna68k/luna68k/cons.h>
E 3
I 3
D 4
#include "../luna68k/cons.h"
E 4
I 4
#include <luna68k/luna68k/cons.h>
E 4
E 3
E 2

siocnprobe(cp)
D 3
	struct consdev *cp;
E 3
I 3
	register struct consdev *cp;
E 3
{
D 3
	int unit;
E 3
I 3
	register int unit = 0;
E 3

D 3
	/* Line Selection: 0: Channel-A (ttya),  1: Channel-B (keyboard) */
	unit = 0;
    
E 3
	/* locate the major number */
	for (siomajor = 0; siomajor < nchrdev; siomajor++)
		if (cdevsw[siomajor].d_open == sioopen)
			break;

D 3
	sio_addr[0] = (struct siodevice *) 0x51000000;
	sio_addr[1] = (struct siodevice *) 0x51000004;
E 3
I 3
D 8
	siounitbase = -1;
E 3

E 8
D 3
	/* make sure hardware exists */
	if (badaddr((short *)sio_addr[0])) {
		cp->cn_pri = CN_DEAD;
		return;
	}

	/* locate the major number */

E 3
	/* initialize required fields */
	cp->cn_dev = makedev(siomajor, unit);
D 3
	cp->cn_tp  = 0;
E 3
I 3
	cp->cn_tp  = &sio_tty[unit];
E 3
	cp->cn_pri = CN_NORMAL;
}

siocninit(cp)
	struct consdev *cp;
{
	int unit = siounit(cp->cn_dev);
I 3
	register struct sio_softc *sc = &sio_softc[unit];
E 3

D 3
	sioinit(unit);
E 3
I 3
	sioinit((struct siodevice *) SIO_HARDADDR, siodefaultrate);

	/* port assign */
D 8
	sc->sc_pc = sio_port_assign(0, siomajor, unit, siointr);
E 8
I 8
	sc->sc_pc = sio_port_assign(SIO_PORT, siomajor, unit, siointr);
E 8

E 3
	sioconsole = unit;
I 3
D 8
	siounitbase = 0;
	
E 8
	sio_active |= 1 << unit;
	siosoftCAR |= 1 << unit;
E 3
}

D 3
/*
 * Routines for Console Support
 */


#ifdef LOCAL_CONSOLE

int local_console;

E 3
siocngetc(dev)
	dev_t dev;
{
D 3
	int c, rr0, rr1;
	int unit;
	int s;
E 3
I 3
	struct sio_softc *sc = &sio_softc[siounit(dev)];
	struct sio_portc *pc = sc->sc_pc;
E 3

D 3
	unit = local_console;

	s = splhigh();
loop:
	while (((rr0 = sioreg(REG(unit, RR0), 0)) & RR0_RXAVAIL) == 0);
	rr1 = sioreg(REG(unit, RR1), 0);
	c = sio_addr[unit]->sio_data;

	if ((rr0 & RR0_BREAK) == RR0_BREAK)		/* Break Detected */
		goto loop;

	if ((rr1 & RR1_OVERRUN) == RR1_OVERRUN) {	/* Data Over Run */
		sioreg(REG(unit, WR0), WR0_ERRRST);
		goto loop;
	}

	if ((rr1 & RR1_PARITY) == RR1_PARITY) {		/* Parity Error */
		sioreg(REG(unit, WR0), WR0_ERRRST);
		goto loop;
	}

	if ((rr1 & RR1_FRAMING) == RR1_FRAMING) {	/* Framing Error */
		sioreg(REG(unit, WR0), WR0_ERRRST);
		goto loop;
	}

	sioreg(REG(unit, WR0), WR0_RSTPEND);
	splx(s);
	return(c);
E 3
I 3
	return(sio_imgetc(pc->pc_addr));
E 3
}

siocnputc(dev, c)
	dev_t dev;
	int c;
{
D 3
	int unit;
	int s;
E 3
I 3
	struct sio_softc *sc = &sio_softc[siounit(dev)];
	struct sio_portc *pc = sc->sc_pc;
E 3

D 3
	unit = local_console;
E 3
I 3
	sio_imputc(pc->pc_addr, c);
}
E 3

D 3
	if (sioconsole == -1) {
		(void) sioinit(unit);
		sioconsole = unit;
	}
E 3

D 3
	s = splhigh();
E 3
I 3
/*
 *  sio raw-level routines
 */
E 3

D 3
	/* wait for any pending transmission to finish */
	while ((sioreg(REG(unit, RR0), 0) & RR0_TXEMPTY) == 0);
E 3
I 3
sioinit(sio0, rate)
	register struct siodevice *sio0;
	register int rate;
{
	register struct siodevice *sio1;
	int s;
E 3

D 3
	sio_addr[unit]->sio_data = (c & 0xFF);
E 3
I 3
	rate = ttspeedtab(rate, siospeedtab);
E 3

D 3
	/* wait for any pending transmission to finish */
	while ((sioreg(REG(unit, RR0), 0) & RR0_TXEMPTY) == 0);
E 3
I 3
	if (sio_init_done)
		return;
E 3

D 3
	splx(s);
}
E 3
I 3
	sio1 = (struct siodevice *) ((u_long) sio0 + sizeof(struct siodevice));
E 3

D 3
sioinit(unit)
	int unit;
{
	int s;

E 3
	s = splhigh();

D 3
	sioreg(REG(unit, WR0), WR0_CHANRST);		/* Channel-A Reset */
	sioreg(WR2A, WR2_VEC86  | WR2_INTR_1);		/* Set CPU BUS Interface Mode */
	sioreg(WR2B, 0);				/* Set Interrupt Vector */
	sioreg(REG(unit, WR0), WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(REG(unit, WR4), WR4_BAUD96 | WR4_STOP1 | WR4_NPARITY);	/* Tx/Rx */
	sioreg(REG(unit, WR3), WR3_RX8BIT | WR3_RXENBL);		/* Rx */
	sioreg(REG(unit, WR5), WR5_TX8BIT | WR5_TXENBL);		/* Tx */
	sioreg(REG(unit, WR0), WR0_RSTINT);		/* Reset E/S Interrupt */
E 3
I 3
	sioreg(sio0, WR0,  WR0_CHANRST);		/* Channel-A Reset */
E 3

D 3
	unit = local_console = 1 - unit;
E 3
I 3
	sioreg(sio0, WR2, (WR2_VEC86  | WR2_INTR_1));	/* Set CPU BUS Interface Mode */
	sioreg(sio1, WR2,  0);				/* Set Interrupt Vector */
E 3

D 3
	sioreg(REG(unit, WR0), WR0_CHANRST);		/* Channel-B Reset */
E 3
I 3
	sioreg(sio0, WR0,  WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(sio0, WR4, (rate | WR4_STOP1 | WR4_NPARITY));	/* Tx/Rx */
	sioreg(sio0, WR3, (WR3_RX8BIT | WR3_RXENBL));		/* Rx */
	sioreg(sio0, WR5, (WR5_TX8BIT | WR5_TXENBL));		/* Tx */
	sioreg(sio0, WR0,  WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(sio0, WR1, (WR1_RXALLS | WR1_TXENBL));
E 3

D 3
	sioreg(REG(unit, WR0), WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(REG(unit, WR4), WR4_BAUD96 | WR4_STOP1 | WR4_NPARITY);	/* Tx/Rx */
	sioreg(REG(unit, WR3), WR3_RX8BIT | WR3_RXENBL);		/* Rx */
	sioreg(REG(unit, WR5), WR5_TX8BIT | WR5_TXENBL);		/* Tx */
	sioreg(REG(unit, WR0), WR0_RSTINT);		/* Reset E/S Interrupt */
E 3
I 3
	sioreg(sio1, WR0,  WR0_CHANRST);		/* Channel-B Reset */
E 3

I 3
	sioreg(sio1, WR0,  WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(sio1, WR4, (rate | WR4_STOP1 | WR4_NPARITY));	/* Tx/Rx */
	sioreg(sio1, WR3, (WR3_RX8BIT | WR3_RXENBL));		/* Rx */
	sioreg(sio1, WR5, (WR5_TX8BIT | WR5_TXENBL));		/* Tx */
	sioreg(sio1, WR0,  WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(sio1, WR1, (WR1_RXALLS | WR1_TXENBL));

E 3
	splx(s);
I 3

	sio_init_done = 1;
E 3
}
D 3
#else
	
/*
 * console put & get
 */
E 3

D 3
siocngetc(dev)
	dev_t dev;
E 3
I 3
sio_imgetc(sio)
	register struct siodevice *sio;
E 3
{
D 3
	while (siolbufempty(rbp))
		DELAY(10);
E 3
I 3
	register int rr0, rr1;
	int c, s;
E 3

D 3
	return(siolbufpop(rbp));
E 3
I 3
	s = splhigh();
	while (((rr0 = sioreg(sio, RR0, 0)) & RR0_RXAVAIL) == 0)
		;
	c = sio->sio_data;
	sioreg(sio, WR0, WR0_RSTPEND);
	splx(s);
	return (c);
E 3
}

D 3
siocnputc(dev, c)
	dev_t dev;
E 3
I 3
sio_imputc(sio, c)
	register struct siodevice *sio;
E 3
	int c;
{
D 3
	register int unit = siounit(dev);
	register struct siodevice *sio = sio_addr[unit];
E 3
	register u_char code;
D 3
	int s, rr;
E 3
I 3
	register int rr;
	int s;
E 3

	s = splhigh();
D 3
	sioreg(REG(unit, WR1), WR1_RXALLS);
E 3

I 3
	sioreg(sio, WR1, WR1_RXALLS);

E 3
	do {
		DELAY(1);
D 3
		rr = siogetreg(unit);
E 3
I 3
		rr = siogetreg(sio);
E 3
	} while (!(rr & RR_TXRDY));
D 3
		
	code = (c & 0xff);
E 3
I 3

	code = (c & 0xFF);
E 3
	sio->sio_data = code;

	do {
		DELAY(1);
D 3
		rr = siogetreg(unit);
E 3
I 3
		rr = siogetreg(sio);
E 3
	} while (!(rr & RR_TXRDY));

D 3
	sioreg(REG(unit, WR1), WR1_RXALLS | WR1_TXENBL);
	splx(s);
}
E 3
I 3
	sioreg(sio, WR1, (WR1_RXALLS | WR1_TXENBL));
E 3

D 3
sioinit(unit)
	int unit;
{
	int s;

	siolbufinit(rbp);

	s = splhigh();

	unit = 0;

	sioreg(REG(unit, WR0), WR0_CHANRST);		/* Channel-A Reset */
	sioreg(WR2A, WR2_VEC86  | WR2_INTR_1);		/* Set CPU BUS Interface Mode */
	sioreg(WR2B, 0);				/* Set Interrupt Vector */
	sioreg(REG(unit, WR0), WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(REG(unit, WR4), WR4_BAUD96 | WR4_STOP1 | WR4_NPARITY);	/* Tx/Rx */
	sioreg(REG(unit, WR3), WR3_RX8BIT | WR3_RXENBL);		/* Rx */
	sioreg(REG(unit, WR5), WR5_TX8BIT | WR5_TXENBL);		/* Tx */
	sioreg(REG(unit, WR0), WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(REG(unit, WR1), WR1_RXALLS | WR1_TXENBL);

	unit = 1;

	sioreg(REG(unit, WR0), WR0_CHANRST);		/* Channel-A Reset */

	sioreg(REG(unit, WR0), WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(REG(unit, WR4), WR4_BAUD96 | WR4_STOP1 | WR4_NPARITY);	/* Tx/Rx */
	sioreg(REG(unit, WR3), WR3_RX8BIT | WR3_RXENBL);		/* Rx */
	sioreg(REG(unit, WR5), WR5_TX8BIT | WR5_TXENBL);		/* Tx */
	sioreg(REG(unit, WR0), WR0_RSTINT);		/* Reset E/S Interrupt */
	sioreg(REG(unit, WR1), WR1_RXALLS | WR1_TXENBL);

E 3
	splx(s);
}
D 3
#endif
E 3

I 3
/*
 *  uPD7201A register operation
 */

E 3
int
D 3
siogetreg(unit)
	register int unit;
E 3
I 3
siogetreg(sio)
	register struct siodevice *sio;
E 3
{
D 3
	register struct siodevice *sio = sio_addr[unit];
E 3
	register int rr = 0;

	rr = sio->sio_stat;
	rr <<= 8;
	sio->sio_cmd = 1;	/* Select RR1 */
	rr |= sio->sio_stat;

	return(rr);
}

int
D 3
sioreg(reg, val)
E 3
I 3
sioreg(sio, reg, val)
	register struct siodevice *sio;
E 3
	register int reg, val;
{
D 3
	register int chan;

	chan = CHANNEL(reg);

E 3
	if (isStatusReg(reg)) {
D 3
		if (REGNO(reg) != 0)
		    sio_addr[chan]->sio_cmd = REGNO(reg);
		return(sio_addr[chan]->sio_stat);
E 3
I 3
		if (reg != 0)
		    sio->sio_cmd = reg;
		val = sio->sio_stat;
E 3
	} else {
D 3
		if (REGNO(reg) != 0)
		    sio_addr[chan]->sio_cmd = REGNO(reg);
		sio_addr[chan]->sio_cmd = val;
		return(val);
E 3
I 3
		if (reg != 0)
		    sio->sio_cmd = reg;
		sio->sio_cmd = val;
E 3
	}
I 3

	return(val);
E 3
}
#endif
E 1
