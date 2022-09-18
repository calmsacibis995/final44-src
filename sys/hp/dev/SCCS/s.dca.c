h33683
s 00001/00001/00843
d D 8.3 95/01/09 17:38:50 cgd 21 20
c strategy returns void, ioctl cmd is u_long
e
s 00004/00000/00840
d D 8.2 94/01/12 09:59:07 bostic 20 19
c lint
e
s 00002/00002/00838
d D 8.1 93/06/10 21:23:12 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00047/00011/00793
d D 7.18 92/12/27 09:09:47 hibler 18 17
c fix OFLOW code, add hacks for less lossage on unbuffered port
e
s 00017/00017/00787
d D 7.17 92/10/11 08:55:04 bostic 17 16
c make kernel includes standard
e
s 00085/00022/00719
d D 7.16 92/06/05 15:23:12 hibler 16 15
c merge latest Utah hp300 code including 68040 support
e
s 00002/00006/00739
d D 7.15 92/02/15 21:18:02 torek 15 14
c convert to use new select interface, selrecord/selwakeup
e
s 00005/00002/00740
d D 7.14 92/02/05 23:35:54 mckusick 14 13
c lint
e
s 00003/00001/00739
d D 7.13 92/02/05 18:53:28 mckusick 13 12
c dcastart is a void
e
s 00016/00018/00724
d D 7.12 91/06/27 17:34:22 karels 12 11
c fix dcaclose modem control; KNF returns; small optimizations
e
s 00004/00002/00738
d D 7.11 91/05/16 17:39:07 marc 11 10
c pass flags through in device close
e
s 00082/00016/00658
d D 7.10 91/05/07 09:46:50 hibler 10 9
c fifo support from Donn, DIO-II support
e
s 00071/00049/00603
d D 7.9 91/05/04 19:43:13 karels 9 8
c new kgdb stuff; use dev_t for kgdb_dev instead of cons index;
c sticky tty params; new proc and calling conventions
e
s 00013/00013/00639
d D 7.8 90/12/16 16:35:31 bostic 8 7
c kernel reorg
e
s 00001/00001/00651
d D 7.7 90/06/30 16:34:39 karels 7 6
c uninitialized error value when carrier/CLOCAL was already on
e
s 00059/00056/00593
d D 7.6 90/06/27 09:01:33 hibler 6 5
c Van's speed enhancements and rts/cts flow control additions
e
s 00007/00009/00642
d D 7.5 90/06/26 13:29:26 hibler 5 4
c replace ttclosed with ttysleep
e
s 00001/00000/00650
d D 7.4 90/06/06 18:55:05 marc 4 3
c set WOPEN on first open
e
s 00003/00002/00647
d D 7.3 90/06/06 17:38:28 marc 3 2
c check for revoked terminal (ttclosed)
e
s 00015/00004/00634
d D 7.2 90/05/25 15:41:21 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00638/00000/00000
d D 7.1 90/05/08 22:06:50 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 19
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include "dca.h"
#if NDCA > 0
/*
D 16
 *  98626/98644/internal serial interface
I 10
 *  uses National Semiconductor INS8250/NS16550AF UART
E 16
I 16
 *  Driver for National Semiconductor INS8250/NS16550AF/WD16C552 UARTs.
 *  Includes:
 *	98626/98644/internal serial interface on hp300/hp400
 *	internal serial ports on hp700
 *
 *  N.B. On the hp700, there is a "secret bit" with undocumented behavior.
 *  The third bit of the Modem Control Register (MCR_IEN == 0x08) must be
 *  set to enable interrupts.
E 16
E 10
 */
D 8
#include "param.h"
#include "systm.h"
#include "ioctl.h"
#include "tty.h"
#include "user.h"
#include "conf.h"
#include "file.h"
#include "uio.h"
#include "kernel.h"
#include "syslog.h"
E 8
I 8
D 17
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/ioctl.h"
D 15
#include "sys/tty.h"
E 15
D 9
#include "sys/user.h"
E 9
I 9
#include "sys/proc.h"
I 15
#include "sys/tty.h"
E 15
E 9
#include "sys/conf.h"
#include "sys/file.h"
#include "sys/uio.h"
#include "sys/kernel.h"
#include "sys/syslog.h"
E 17
I 17
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
E 17
E 8

D 16
#include "device.h"
E 16
I 16
D 17
#include "hp/dev/device.h"
E 16
#include "dcareg.h"
E 17
I 17
#include <hp/dev/device.h>
#include <hp/dev/dcareg.h>
E 17
I 16

E 16
D 8
#include "machine/cpu.h"
#include "machine/isr.h"
E 8
I 8
D 9
#include "../include/cpu.h"
E 9
I 9
D 17
#include "machine/cpu.h"
E 17
I 17
#include <machine/cpu.h>
E 17
E 9
D 16
#include "../hp300/isr.h"
E 16
I 16
#ifdef hp300
D 17
#include "../../hp300/hp300/isr.h"
E 17
I 17
#include <hp300/hp300/isr.h>
E 17
#endif
#ifdef hp700
D 17
#include "machine/asp.h"
E 17
I 17
#include <machine/asp.h>
E 17
#endif
E 16
E 8

int	dcaprobe();
struct	driver dcadriver = {
	dcaprobe, "dca",
};

D 13
int	dcastart(), dcaparam(), dcaintr();
E 13
I 13
void	dcastart();
int	dcaparam(), dcaintr();
E 13
int	dcasoftCAR;
int	dca_active;
I 10
int	dca_hasfifo;
E 10
int	ndca = NDCA;
I 9
#ifdef DCACONSOLE
int	dcaconsole = DCACONSOLE;
#else
E 9
int	dcaconsole = -1;
I 9
#endif
int	dcaconsinit;
E 9
int	dcadefaultrate = TTYDEF_SPEED;
I 9
int	dcamajor;
E 9
struct	dcadevice *dca_addr[NDCA];
struct	tty dca_tty[NDCA];
I 16
#ifdef hp300
E 16
struct	isr dcaisr[NDCA];
I 18
int	dcafastservice;
E 18
I 16
#endif
I 18
int	dcaoflows[NDCA];
E 18
E 16

struct speedtab dcaspeedtab[] = {
	0,	0,
	50,	DCABRD(50),
	75,	DCABRD(75),
	110,	DCABRD(110),
	134,	DCABRD(134),
	150,	DCABRD(150),
	200,	DCABRD(200),
	300,	DCABRD(300),
	600,	DCABRD(600),
	1200,	DCABRD(1200),
	1800,	DCABRD(1800),
	2400,	DCABRD(2400),
	4800,	DCABRD(4800),
	9600,	DCABRD(9600),
	19200,	DCABRD(19200),
	38400,	DCABRD(38400),
	-1,	-1
};

D 16
extern	struct tty *constty;
E 16
#ifdef KGDB
I 9
D 17
#include "machine/remote-sl.h"
E 17
I 17
#include <machine/remote-sl.h>
E 17

E 9
D 12
extern int kgdb_dev;
E 12
I 12
extern dev_t kgdb_dev;
E 12
extern int kgdb_rate;
extern int kgdb_debug_init;
#endif

#define	UNIT(x)		minor(x)

I 10
#ifdef DEBUG
long	fifoin[17];
long	fifoout[17];
long	dcaintrcount[16];
long	dcamintcount[16];
#endif

E 10
dcaprobe(hd)
	register struct hp_device *hd;
{
	register struct dcadevice *dca;
	register int unit;

	dca = (struct dcadevice *)hd->hp_addr;
D 16
	if (dca->dca_irid != DCAID0 &&
	    dca->dca_irid != DCAREMID0 &&
	    dca->dca_irid != DCAID1 &&
	    dca->dca_irid != DCAREMID1)
E 16
I 16
#ifdef hp300
	if (dca->dca_id != DCAID0 &&
	    dca->dca_id != DCAREMID0 &&
	    dca->dca_id != DCAID1 &&
	    dca->dca_id != DCAREMID1)
E 16
		return (0);
I 16
#endif
E 16
	unit = hd->hp_unit;
	if (unit == dcaconsole)
		DELAY(100000);
D 16
	dca->dca_irid = 0xFF;
E 16
I 16
#ifdef hp300
	dca->dca_reset = 0xFF;
E 16
	DELAY(100);
I 16
#endif
E 16

I 10
	/* look for a NS 16550AF UART with FIFOs */
	dca->dca_fifo = FIFO_ENABLE|FIFO_RCV_RST|FIFO_XMT_RST|FIFO_TRIGGER_14;
	DELAY(100);
	if ((dca->dca_iir & IIR_FIFO_MASK) == IIR_FIFO_MASK)
		dca_hasfifo |= 1 << unit;

I 16
	dca_addr[unit] = dca;
#ifdef hp300
E 16
E 10
	hd->hp_ipl = DCAIPL(dca->dca_ic);
	dcaisr[unit].isr_ipl = hd->hp_ipl;
	dcaisr[unit].isr_arg = unit;
	dcaisr[unit].isr_intr = dcaintr;
D 16
	dca_addr[unit] = dca;
	dca_active |= 1 << unit;
	dcasoftCAR = hd->hp_flags;
E 16
	isrlink(&dcaisr[unit]);
I 16
#endif
	dca_active |= 1 << unit;
	if (hd->hp_flags)
		dcasoftCAR |= (1 << unit);
E 16
#ifdef KGDB
D 9
	if (kgdb_dev == makedev(1, unit)) {
E 9
I 9
	if (kgdb_dev == makedev(dcamajor, unit)) {
E 9
		if (dcaconsole == unit)
D 12
			kgdb_dev = -1;	/* can't debug over console port */
E 12
I 12
			kgdb_dev = NODEV; /* can't debug over console port */
E 12
		else {
D 9
			(void) dcainit(unit);
			dcaconsole = -2; /* XXX */
E 9
I 9
			(void) dcainit(unit, kgdb_rate);
I 12
			dcaconsinit = 1;	/* don't re-init in dcaputc */
E 12
E 9
			if (kgdb_debug_init) {
D 9
				printf("dca%d: kgdb waiting...", unit);
				/* trap into kgdb */
				asm("trap #15;");
				printf("connected.\n");
E 9
I 9
				/*
				 * Print prefix of device name,
				 * let kgdb_connect print the rest.
				 */
				printf("dca%d: ", unit);
				kgdb_connect(1);
E 9
			} else
				printf("dca%d: kgdb enabled\n", unit);
		}
	}
#endif
I 16
#ifdef hp300
E 16
	dca->dca_ic = IC_IE;
I 16
#endif
E 16
	/*
D 9
	 * Need to reset baud rate, etc. of next print so reset dcaconsole.
	 * Also make sure console is always "hardwired"
E 9
I 9
	 * Need to reset baud rate, etc. of next print so reset dcaconsinit.
	 * Also make sure console is always "hardwired."
E 9
	 */
	if (unit == dcaconsole) {
D 9
		dcaconsole = -1;
E 9
I 9
		dcaconsinit = 0;
E 9
		dcasoftCAR |= (1 << unit);
	}
	return (1);
}

D 9
dcaopen(dev, flag)
E 9
I 9
/* ARGSUSED */
#ifdef __STDC__
dcaopen(dev_t dev, int flag, int mode, struct proc *p)
#else
dcaopen(dev, flag, mode, p)
E 9
	dev_t dev;
I 9
	int flag, mode;
	struct proc *p;
#endif
E 9
{
	register struct tty *tp;
	register int unit;
I 2
D 7
	int error;
E 7
I 7
	int error = 0;
E 7
E 2
 
	unit = UNIT(dev);
	if (unit >= NDCA || (dca_active & (1 << unit)) == 0)
		return (ENXIO);
	tp = &dca_tty[unit];
	tp->t_oproc = dcastart;
	tp->t_param = dcaparam;
	tp->t_dev = dev;
	if ((tp->t_state & TS_ISOPEN) == 0) {
I 4
		tp->t_state |= TS_WOPEN;
E 4
		ttychars(tp);
D 9
		tp->t_iflag = TTYDEF_IFLAG;
		tp->t_oflag = TTYDEF_OFLAG;
		tp->t_cflag = TTYDEF_CFLAG;
		tp->t_lflag = TTYDEF_LFLAG;
		tp->t_ispeed = tp->t_ospeed = dcadefaultrate;
E 9
I 9
		if (tp->t_ispeed == 0) {
			tp->t_iflag = TTYDEF_IFLAG;
			tp->t_oflag = TTYDEF_OFLAG;
			tp->t_cflag = TTYDEF_CFLAG;
			tp->t_lflag = TTYDEF_LFLAG;
			tp->t_ispeed = tp->t_ospeed = dcadefaultrate;
		}
E 9
		dcaparam(tp, &tp->t_termios);
		ttsetwater(tp);
D 9
	} else if (tp->t_state&TS_XCLUDE && u.u_uid != 0)
E 9
I 9
	} else if (tp->t_state&TS_XCLUDE && p->p_ucred->cr_uid != 0)
E 9
		return (EBUSY);
	(void) dcamctl(dev, MCR_DTR | MCR_RTS, DMSET);
	if ((dcasoftCAR & (1 << unit)) || (dcamctl(dev, 0, DMGET) & MSR_DCD))
		tp->t_state |= TS_CARR_ON;
	(void) spltty();
D 5
	while (!(flag&O_NONBLOCK) && !(tp->t_cflag&CLOCAL) &&
E 5
I 5
	while ((flag&O_NONBLOCK) == 0 && (tp->t_cflag&CLOCAL) == 0 &&
E 5
	       (tp->t_state & TS_CARR_ON) == 0) {
		tp->t_state |= TS_WOPEN;
D 2
		sleep((caddr_t)&tp->t_rawq, TTIPRI);
E 2
I 2
D 3
		if (error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
				   ttopen, 0)) {
E 3
I 3
D 5
		if ((error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
				   ttopen, 0)) ||
		    (error = ttclosed(tp))) {
E 3
			tp->t_state &= ~TS_WOPEN;
			(void) spl0();
			return (error);
		}
E 5
I 5
		if (error = ttysleep(tp, (caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
		    ttopen, 0))
			break;
E 5
E 2
	}
	(void) spl0();
D 5
	return ((*linesw[tp->t_line].l_open)(dev, tp));
E 5
I 5
	if (error == 0)
		error = (*linesw[tp->t_line].l_open)(dev, tp);
I 18
#ifdef hp300
	/*
	 * XXX hack to speed up unbuffered builtin port.
	 * If dca_fastservice is set, a level 5 interrupt
	 * will be directed to dcaintr first.
	 */
	if (error == 0 && unit == 0 && (dca_hasfifo & 1) == 0)
		dcafastservice = 1;
#endif
E 18
	return (error);
E 5
}
 
/*ARGSUSED*/
D 11
dcaclose(dev, flag)
E 11
I 11
dcaclose(dev, flag, mode, p)
E 11
	dev_t dev;
I 11
	int flag, mode;
	struct proc *p;
E 11
{
	register struct tty *tp;
	register struct dcadevice *dca;
	register int unit;
 
	unit = UNIT(dev);
I 18
#ifdef hp300
	if (unit == 0)
		dcafastservice = 0;
#endif
E 18
	dca = dca_addr[unit];
	tp = &dca_tty[unit];
D 11
	(*linesw[tp->t_line].l_close)(tp);
E 11
I 11
	(*linesw[tp->t_line].l_close)(tp, flag);
E 11
	dca->dca_cfcr &= ~CFCR_SBREAK;
#ifdef KGDB
	/* do not disable interrupts if debugging */
D 9
	if (kgdb_dev != makedev(1, unit))
E 9
I 9
	if (dev != kgdb_dev)
E 9
#endif
	dca->dca_ier = 0;
D 9
	if (tp->t_cflag&HUPCL || tp->t_state&TS_WOPEN || 
	    (tp->t_state&TS_ISOPEN) == 0)
		(void) dcamctl(dev, 0, DMSET);
E 9
I 9
D 12
	(void) dcamctl(dev, 0, DMSET);
	if (tp->t_state & TS_HUPCLS)
		(*linesw[tp->t_line].l_modem)(tp, 0);
E 12
I 12
	if (tp->t_cflag&HUPCL || tp->t_state&TS_WOPEN ||
	    (tp->t_state&TS_ISOPEN) == 0)
		(void) dcamctl(dev, 0, DMSET);
E 12
E 9
	ttyclose(tp);
D 12
	return(0);
E 12
I 12
	return (0);
E 12
}
 
dcaread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
I 20
	int flag;
E 20
{
D 18
	register struct tty *tp = &dca_tty[UNIT(dev)];
E 18
I 18
	int unit = UNIT(dev);
	register struct tty *tp = &dca_tty[unit];
	int error, of;
E 18
 
D 18
	return ((*linesw[tp->t_line].l_read)(tp, uio, flag));
E 18
I 18
	of = dcaoflows[unit];
	error = (*linesw[tp->t_line].l_read)(tp, uio, flag);
	/*
	 * XXX hardly a reasonable thing to do, but reporting overflows
	 * at interrupt time just exacerbates the problem.
	 */
	if (dcaoflows[unit] != of)
		log(LOG_WARNING, "dca%d: silo overflow\n", unit);
	return (error);
E 18
}
 
dcawrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
I 20
	int flag;
E 20
{
	int unit = UNIT(dev);
	register struct tty *tp = &dca_tty[unit];
I 16
	extern struct tty *constty;
E 16
 
D 2
	if (unit == dcaconsole && constty &&
	    (constty->t_state&(TS_CARR_ON|TS_ISOPEN))==(TS_CARR_ON|TS_ISOPEN))
		tp = constty;
E 2
I 2
	/*
	 * (XXX) We disallow virtual consoles if the physical console is
	 * a serial port.  This is in case there is a display attached that
	 * is not the console.  In that situation we don't need/want the X
	 * server taking over the console.
	 */
	if (constty && unit == dcaconsole)
		constty = NULL;
E 2
	return ((*linesw[tp->t_line].l_write)(tp, uio, flag));
}
 
dcaintr(unit)
	register int unit;
{
	register struct dcadevice *dca;
D 6
	register int code;
E 6
I 6
	register u_char code;
	register struct tty *tp;
I 18
	int iflowdone = 0;
E 18
E 6

	dca = dca_addr[unit];
D 16
	if ((dca->dca_ic & IC_IR) == 0)
E 16
I 16
#ifdef hp300
	if ((dca->dca_ic & (IC_IR|IC_IE)) != (IC_IR|IC_IE))
E 16
D 12
		return(0);
E 12
I 12
		return (0);
I 16
#endif
I 18
	tp = &dca_tty[unit];
E 18
E 16
E 12
D 6
	while (((code = dca->dca_iir) & IIR_NOPEND) == 0) {
		code &= IIR_IMASK;
		if (code == IIR_RLS)
E 6
I 6
	while (1) {
		code = dca->dca_iir;
D 10
		switch (code) {
E 10
I 10
#ifdef DEBUG
		dcaintrcount[code & IIR_IMASK]++;
#endif
		switch (code & IIR_IMASK) {
E 10
		case IIR_NOPEND:
			return (1);
I 10
		case IIR_RXTOUT:
E 10
		case IIR_RXRDY:
			/* do time-critical read in-line */
D 18
			tp = &dca_tty[unit];
E 18
D 10
			code = dca->dca_data;
			if ((tp->t_state & TS_ISOPEN) == 0) {
E 10
I 10
/*
 * Process a received byte.  Inline for speed...
 */
E 10
#ifdef KGDB
D 9
				if (kgdb_dev == makedev(1, unit) &&
				    code == '!') {
					printf("kgdb trap from dca%d\n", unit);
					/* trap into kgdb */
					asm("trap #15;");
				}
E 9
I 9
D 10
				if (kgdb_dev == makedev(dcamajor, unit) &&
				    code == FRAME_END)
					kgdb_connect(0); /* trap into kgdb */
E 10
I 10
#define	RCVBYTE() \
			code = dca->dca_data; \
			if ((tp->t_state & TS_ISOPEN) == 0) { \
D 12
				if (kgdb_dev == makedev(dcamajor, unit) && \
				    code == FRAME_END) \
E 12
I 12
				if (code == FRAME_END && \
				    kgdb_dev == makedev(dcamajor, unit)) \
E 12
					kgdb_connect(0); /* trap into kgdb */ \
			} else \
				(*linesw[tp->t_line].l_rint)(code, tp)
#else
#define	RCVBYTE() \
			code = dca->dca_data; \
			if ((tp->t_state & TS_ISOPEN) != 0) \
				(*linesw[tp->t_line].l_rint)(code, tp)
E 10
E 9
#endif
D 10
			} else
				(*linesw[tp->t_line].l_rint)(code, tp);
E 10
I 10
			RCVBYTE();
			if (dca_hasfifo & (1 << unit)) {
#ifdef DEBUG
				register int fifocnt = 1;
#endif
				while ((code = dca->dca_lsr) & LSR_RCV_MASK) {
					if (code == LSR_RXRDY) {
						RCVBYTE();
					} else
						dcaeint(unit, code, dca);
#ifdef DEBUG
					fifocnt++;
#endif
				}
#ifdef DEBUG
				if (fifocnt > 16)
					fifoin[0]++;
				else
					fifoin[fifocnt]++;
#endif
			}
I 18
			if (!iflowdone && (tp->t_cflag&CRTS_IFLOW) &&
			    tp->t_rawq.c_cc > TTYHOG/2) {
				dca->dca_mcr &= ~MCR_RTS;
				iflowdone = 1;
			}
E 18
E 10
			break;
		case IIR_TXRDY:
D 18
			tp = &dca_tty[unit];
E 18
			tp->t_state &=~ (TS_BUSY|TS_FLUSH);
			if (tp->t_line)
				(*linesw[tp->t_line].l_start)(tp);
			else
				dcastart(tp);
			break;
		case IIR_RLS:
E 6
D 10
			dcaeint(unit, dca);
E 10
I 10
			dcaeint(unit, dca->dca_lsr, dca);
E 10
D 6
		else if (code == IIR_RXRDY)
			dcarint(unit, dca);
		else if (code == IIR_TXRDY)
			dcaxint(unit, dca);
		else
E 6
I 6
			break;
		default:
			if (code & IIR_NOPEND)
				return (1);
			log(LOG_WARNING, "dca%d: weird interrupt: 0x%x\n",
			    unit, code);
			/* fall through */
		case IIR_MLSC:
E 6
			dcamint(unit, dca);
I 6
			break;
		}
E 6
	}
D 6
	return(1);
E 6
}

D 10
dcaeint(unit, dca)
	register int unit;
E 10
I 10
dcaeint(unit, stat, dca)
	register int unit, stat;
E 10
	register struct dcadevice *dca;
{
	register struct tty *tp;
D 10
	register int stat, c;
E 10
I 10
	register int c;
E 10

	tp = &dca_tty[unit];
D 10
	stat = dca->dca_lsr;
E 10
D 6
	c = dca->dca_data & 0xff;
E 6
I 6
	c = dca->dca_data;
E 6
	if ((tp->t_state & TS_ISOPEN) == 0) {
#ifdef KGDB
		/* we don't care about parity errors */
		if (((stat & (LSR_BI|LSR_FE|LSR_PE)) == LSR_PE) &&
D 9
		    kgdb_dev == makedev(1, unit) && c == '!') {
			printf("kgdb trap from dca%d\n", unit);
			/* trap into kgdb */
			asm("trap #15;");
		}
E 9
I 9
		    kgdb_dev == makedev(dcamajor, unit) && c == FRAME_END)
			kgdb_connect(0); /* trap into kgdb */
E 9
#endif
		return;
	}
	if (stat & (LSR_BI | LSR_FE))
		c |= TTY_FE;
	else if (stat & LSR_PE)
		c |= TTY_PE;
	else if (stat & LSR_OE)
D 18
		log(LOG_WARNING, "dca%d: silo overflow\n", unit);
E 18
I 18
		dcaoflows[unit]++;
E 18
	(*linesw[tp->t_line].l_rint)(c, tp);
}

D 6
dcarint(unit, dca)
	int unit;
	register struct dcadevice *dca;
{
	register struct tty *tp;
	register int c;

	tp = &dca_tty[unit];
	c = dca->dca_data;
	if ((tp->t_state & TS_ISOPEN) == 0) {
#ifdef KGDB
		if (kgdb_dev == makedev(1, unit) && c == '!') {
			printf("kgdb trap from dca%d\n", unit);
			/* trap into kgdb */
			asm("trap #15;");
		}
#endif
		return;
	}
	(*linesw[tp->t_line].l_rint)(c, tp);
}

/*ARGSUSED*/
dcaxint(unit, dca)
	int unit;
	struct dcadevice *dca;
{
	register struct tty *tp;

	tp = &dca_tty[unit];
	tp->t_state &= ~TS_BUSY;
	if (tp->t_state & TS_FLUSH)
		tp->t_state &= ~TS_FLUSH;
	if (tp->t_line)
		(*linesw[tp->t_line].l_start)(tp);
	else
		dcastart(tp);
}

E 6
dcamint(unit, dca)
	register int unit;
	register struct dcadevice *dca;
{
	register struct tty *tp;
D 16
	register int stat;
E 16
I 16
	register u_char stat;
E 16

	tp = &dca_tty[unit];
	stat = dca->dca_msr;
I 10
#ifdef DEBUG
	dcamintcount[stat & 0xf]++;
#endif
E 10
D 6
	if ((stat & MSR_CCD) && (dcasoftCAR & (1 << unit)) == 0) {
E 6
I 6
D 18
	if ((stat & MSR_DDCD) && (dcasoftCAR & (1 << unit)) == 0) {
E 18
I 18
	if ((stat & MSR_DDCD) &&
	    (dcasoftCAR & (1 << unit)) == 0) {
E 18
E 6
		if (stat & MSR_DCD)
D 6
			(void) (*linesw[tp->t_line].l_modem)(tp, 1);
E 6
I 6
			(void)(*linesw[tp->t_line].l_modem)(tp, 1);
E 6
		else if ((*linesw[tp->t_line].l_modem)(tp, 0) == 0)
			dca->dca_mcr &= ~(MCR_DTR | MCR_RTS);
I 6
D 18
	} else if ((stat & MSR_DCTS) && (tp->t_state & TS_ISOPEN) &&
		   (tp->t_flags & CRTSCTS)) {
		/* the line is up and we want to do rts/cts flow control */
E 18
I 18
	}
	/*
	 * CTS change.
	 * If doing HW output flow control start/stop output as appropriate.
	 */
	if ((stat & MSR_DCTS) &&
	    (tp->t_state & TS_ISOPEN) && (tp->t_cflag & CCTS_OFLOW)) {
E 18
		if (stat & MSR_CTS) {
			tp->t_state &=~ TS_TTSTOP;
D 18
			ttstart(tp);
		} else
E 18
I 18
			dcastart(tp);
		} else {
E 18
			tp->t_state |= TS_TTSTOP;
I 18
		}
E 18
E 6
	}
}

D 14
dcaioctl(dev, cmd, data, flag)
E 14
I 14
dcaioctl(dev, cmd, data, flag, p)
E 14
	dev_t dev;
I 14
D 21
	int cmd;
E 21
I 21
	u_long cmd;
E 21
E 14
	caddr_t data;
I 14
	int flag;
	struct proc *p;
E 14
{
	register struct tty *tp;
	register int unit = UNIT(dev);
	register struct dcadevice *dca;
	register int error;
 
	tp = &dca_tty[unit];
D 14
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
E 14
I 14
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag, p);
E 14
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, data, flag);
	if (error >= 0)
		return (error);

	dca = dca_addr[unit];
	switch (cmd) {

	case TIOCSBRK:
		dca->dca_cfcr |= CFCR_SBREAK;
		break;

	case TIOCCBRK:
		dca->dca_cfcr &= ~CFCR_SBREAK;
		break;

	case TIOCSDTR:
		(void) dcamctl(dev, MCR_DTR | MCR_RTS, DMBIS);
		break;

	case TIOCCDTR:
		(void) dcamctl(dev, MCR_DTR | MCR_RTS, DMBIC);
		break;

	case TIOCMSET:
		(void) dcamctl(dev, *(int *)data, DMSET);
		break;

	case TIOCMBIS:
		(void) dcamctl(dev, *(int *)data, DMBIS);
		break;

	case TIOCMBIC:
		(void) dcamctl(dev, *(int *)data, DMBIC);
		break;

	case TIOCMGET:
		*(int *)data = dcamctl(dev, 0, DMGET);
		break;

	default:
		return (ENOTTY);
	}
	return (0);
}

dcaparam(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	register struct dcadevice *dca;
	register int cfcr, cflag = t->c_cflag;
	int unit = UNIT(tp->t_dev);
	int ospeed = ttspeedtab(t->c_ospeed, dcaspeedtab);
 
	/* check requested parameters */
        if (ospeed < 0 || (t->c_ispeed && t->c_ispeed != t->c_ospeed))
D 12
                return(EINVAL);
E 12
I 12
                return (EINVAL);
E 12
        /* and copy to tty */
        tp->t_ispeed = t->c_ispeed;
        tp->t_ospeed = t->c_ospeed;
        tp->t_cflag = cflag;

	dca = dca_addr[unit];
	dca->dca_ier = IER_ERXRDY | IER_ETXRDY | IER_ERLS | IER_EMSC;
I 16
#ifdef hp700
	dca->dca_mcr |= MCR_IEN;
#endif
E 16
	if (ospeed == 0) {
		(void) dcamctl(unit, 0, DMSET);	/* hang up line */
D 12
		return(0);
E 12
I 12
		return (0);
E 12
	}
	dca->dca_cfcr |= CFCR_DLAB;
	dca->dca_data = ospeed & 0xFF;
	dca->dca_ier = ospeed >> 8;
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
	dca->dca_cfcr = cfcr;
I 10
	if (dca_hasfifo & (1 << unit))
		dca->dca_fifo = FIFO_ENABLE | FIFO_TRIGGER_14;
E 10
D 12
	return(0);
E 12
I 12
	return (0);
E 12
}
 
I 13
void
E 13
dcastart(tp)
	register struct tty *tp;
{
	register struct dcadevice *dca;
	int s, unit, c;
 
	unit = UNIT(tp->t_dev);
	dca = dca_addr[unit];
	s = spltty();
D 6
	if (tp->t_state & (TS_TIMEOUT|TS_BUSY|TS_TTSTOP))
E 6
I 6
	if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP))
E 6
		goto out;
	if (tp->t_outq.c_cc <= tp->t_lowat) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
D 15
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
E 15
I 15
		selwakeup(&tp->t_wsel);
E 15
	}
	if (tp->t_outq.c_cc == 0)
		goto out;
D 6
	c = getc(&tp->t_outq);
	tp->t_state |= TS_BUSY;
	dca->dca_data = c;
E 6
I 6
	if (dca->dca_lsr & LSR_TXRDY) {
		c = getc(&tp->t_outq);
		tp->t_state |= TS_BUSY;
		dca->dca_data = c;
I 10
		if (dca_hasfifo & (1 << unit)) {
			for (c = 1; c < 16 && tp->t_outq.c_cc; ++c)
				dca->dca_data = getc(&tp->t_outq);
#ifdef DEBUG
			if (c > 16)
				fifoout[0]++;
			else
				fifoout[c]++;
#endif
		}
E 10
	}
E 6
out:
	splx(s);
}
 
/*
 * Stop output on a line.
 */
/*ARGSUSED*/
dcastop(tp, flag)
	register struct tty *tp;
I 20
	int flag;
E 20
{
	register int s;

	s = spltty();
	if (tp->t_state & TS_BUSY) {
		if ((tp->t_state&TS_TTSTOP)==0)
			tp->t_state |= TS_FLUSH;
	}
	splx(s);
}
 
dcamctl(dev, bits, how)
	dev_t dev;
	int bits, how;
{
	register struct dcadevice *dca;
	register int unit;
	int s;

	unit = UNIT(dev);
	dca = dca_addr[unit];
I 16
#ifdef hp700
	/*
	 * Always make sure MCR_IEN is set (unless setting to 0)
	 */
#ifdef KGDB
	if (how == DMSET && kgdb_dev == makedev(dcamajor, unit))
		bits |= MCR_IEN;
	else
#endif
	if (how == DMBIS || (how == DMSET && bits))
		bits |= MCR_IEN;
	else if (how == DMBIC)
		bits &= ~MCR_IEN;
#endif
E 16
	s = spltty();
	switch (how) {

	case DMSET:
		dca->dca_mcr = bits;
		break;

	case DMBIS:
		dca->dca_mcr |= bits;
		break;

	case DMBIC:
		dca->dca_mcr &= ~bits;
		break;

	case DMGET:
		bits = dca->dca_msr;
		break;
	}
	(void) splx(s);
D 12
	return(bits);
E 12
I 12
	return (bits);
E 12
}

/*
 * Following are all routines needed for DCA to act as console
 */
D 8
#include "machine/cons.h"
E 8
I 8
D 16
#include "../hp300/cons.h"
E 16
I 16
D 17
#include "hp/dev/cons.h"
E 17
I 17
#include <hp/dev/cons.h>
E 17
E 16
E 8

dcacnprobe(cp)
	struct consdev *cp;
{
D 10
	int unit, i;
E 10
I 10
	int unit;
E 10
D 9
	extern int dcaopen();
E 9

I 9
	/* locate the major number */
	for (dcamajor = 0; dcamajor < nchrdev; dcamajor++)
		if (cdevsw[dcamajor].d_open == dcaopen)
			break;

E 9
	/* XXX: ick */
	unit = CONUNIT;
I 16
#ifdef hp300
E 16
D 10
	dca_addr[CONUNIT] = CONADDR;
E 10
I 10
	dca_addr[CONUNIT] = (struct dcadevice *) sctova(CONSCODE);
E 10

	/* make sure hardware exists */
	if (badaddr((short *)dca_addr[unit])) {
		cp->cn_pri = CN_DEAD;
		return;
	}
I 16
#endif
#ifdef hp700
	dca_addr[CONUNIT] = CONPORT;
#endif
E 16

D 9
	/* locate the major number */
	for (i = 0; i < nchrdev; i++)
		if (cdevsw[i].d_open == dcaopen)
			break;

E 9
	/* initialize required fields */
D 9
	cp->cn_dev = makedev(i, unit);
E 9
I 9
	cp->cn_dev = makedev(dcamajor, unit);
E 9
	cp->cn_tp = &dca_tty[unit];
D 16
	switch (dca_addr[unit]->dca_irid) {
E 16
I 16
#ifdef hp300
	switch (dca_addr[unit]->dca_id) {
E 16
	case DCAID0:
	case DCAID1:
		cp->cn_pri = CN_NORMAL;
		break;
	case DCAREMID0:
	case DCAREMID1:
		cp->cn_pri = CN_REMOTE;
		break;
	default:
		cp->cn_pri = CN_DEAD;
		break;
	}
I 16
#endif
#ifdef hp700
	cp->cn_pri = CN_NORMAL;
#endif
E 16
I 9
	/*
D 10
	 * If dcmconsole is initialized, raise our priority.
E 10
I 10
	 * If dcaconsole is initialized, raise our priority.
E 10
	 */
	if (dcaconsole == unit)
		cp->cn_pri = CN_REMOTE;
I 10
#ifdef KGDB
E 10
	if (major(kgdb_dev) == 1)			/* XXX */
		kgdb_dev = makedev(dcamajor, minor(kgdb_dev));
I 10
#endif
E 10
E 9
}

dcacninit(cp)
	struct consdev *cp;
{
	int unit = UNIT(cp->cn_dev);

D 9
	dcainit(unit);
E 9
I 9
	dcainit(unit, dcadefaultrate);
E 9
	dcaconsole = unit;
I 9
	dcaconsinit = 1;
E 9
}

D 9
dcainit(unit)
	int unit;
E 9
I 9
dcainit(unit, rate)
	int unit, rate;
E 9
{
	register struct dcadevice *dca;
D 9
	int s, rate;
E 9
I 9
	int s;
E 9
	short stat;

#ifdef lint
	stat = unit; if (stat) return;
#endif
	dca = dca_addr[unit];
	s = splhigh();
D 16
	dca->dca_irid = 0xFF;
E 16
I 16
#ifdef hp300
	dca->dca_reset = 0xFF;
E 16
	DELAY(100);
	dca->dca_ic = IC_IE;
I 16
#endif
E 16
	dca->dca_cfcr = CFCR_DLAB;
D 9
	rate = ttspeedtab(dcadefaultrate, dcaspeedtab);
E 9
I 9
	rate = ttspeedtab(rate, dcaspeedtab);
E 9
	dca->dca_data = rate & 0xFF;
	dca->dca_ier = rate >> 8;
	dca->dca_cfcr = CFCR_8BITS;
	dca->dca_ier = IER_ERXRDY | IER_ETXRDY;
I 16
#ifdef hp700
	dca->dca_mcr |= MCR_IEN;
#endif
E 16
I 10
	dca->dca_fifo = FIFO_ENABLE|FIFO_RCV_RST|FIFO_XMT_RST|FIFO_TRIGGER_14;
I 16
	DELAY(100);
E 16
E 10
	stat = dca->dca_iir;
	splx(s);
}

dcacngetc(dev)
I 20
	dev_t dev;
E 20
{
	register struct dcadevice *dca = dca_addr[UNIT(dev)];
D 16
	short stat;
E 16
I 16
	register u_char stat;
E 16
	int c, s;

#ifdef lint
D 12
	stat = dev; if (stat) return(0);
E 12
I 12
	stat = dev; if (stat) return (0);
E 12
#endif
	s = splhigh();
	while (((stat = dca->dca_lsr) & LSR_RXRDY) == 0)
		;
	c = dca->dca_data;
	stat = dca->dca_iir;
	splx(s);
D 12
	return(c);
E 12
I 12
	return (c);
E 12
}

/*
 * Console kernel output character routine.
 */
dcacnputc(dev, c)
	dev_t dev;
	register int c;
{
	register struct dcadevice *dca = dca_addr[UNIT(dev)];
	register int timo;
D 16
	short stat;
E 16
I 16
	register u_char stat;
E 16
	int s = splhigh();

#ifdef lint
	stat = dev; if (stat) return;
D 12
#endif
D 9
	if (dcaconsole == -1) {
		(void) dcainit(UNIT(dev));
		dcaconsole = UNIT(dev);
E 9
I 9
#ifdef KGDB
	if (dev != kgdb_dev)
E 12
#endif
	if (dcaconsinit == 0) {
		(void) dcainit(UNIT(dev), dcadefaultrate);
		dcaconsinit = 1;
E 9
	}
	/* wait for any pending transmission to finish */
	timo = 50000;
	while (((stat = dca->dca_lsr) & LSR_TXRDY) == 0 && --timo)
		;
	dca->dca_data = c;
	/* wait for this transmission to complete */
	timo = 1500000;
	while (((stat = dca->dca_lsr) & LSR_TXRDY) == 0 && --timo)
		;
D 16
	/* clear any interrupts generated by this transmission */
	stat = dca->dca_iir;
E 16
I 16
	/*
	 * If the "normal" interface was busy transfering a character
	 * we must let our interrupt through to keep things moving.
	 * Otherwise, we clear the interrupt that we have caused.
	 */
	if ((dca_tty[UNIT(dev)].t_state & TS_BUSY) == 0)
		stat = dca->dca_iir;
E 16
	splx(s);
}
#endif
E 1
