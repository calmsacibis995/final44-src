h62628
s 00004/00003/00795
d D 7.16 91/05/16 18:18:03 marc 26 25
c pass flags from device close to l_close
e
s 00000/00001/00798
d D 7.15 91/05/09 13:08:40 sklower 25 24
c /sys/sys/bkmac.h is gone
e
s 00002/00001/00797
d D 7.14 91/02/12 12:52:34 karels 24 23
c dhuparam needed return values
e
s 00017/00017/00781
d D 7.13 90/12/16 16:58:29 bostic 23 22
c kernel reorg
e
s 00003/00003/00795
d D 7.12 90/06/28 15:30:51 marc 22 21
c ttysleep to catch revokes terminals
e
s 00003/00002/00795
d D 7.11 90/06/06 17:44:24 marc 21 20
c check for revoked terminal (ttclosed)
e
s 00012/00013/00785
d D 7.10 90/04/03 22:16:39 karels 20 19
c tsleep: unwind after signal interrupts; close routines must return value
e
s 00000/00001/00798
d D 7.9 90/02/17 11:03:23 mckusick 19 18
c get rid of dir.h
e
s 00002/00002/00797
d D 7.8 90/02/08 18:22:17 marc 18 17
c tsleep
e
s 00018/00049/00781
d D 7.7 89/09/06 14:30:22 marc 17 16
c posix tty
e
s 00147/00071/00683
d D 7.6 89/05/01 23:31:27 marc 16 15
c speed table, initializations, t_param, other terminal driver changes
e
s 00001/00001/00753
d D 7.5 89/04/25 14:12:01 mckusick 15 14
c ../macine => machine
e
s 00001/00001/00753
d D 7.4 89/01/24 17:24:00 bostic 14 13
c typo in attach routines; bug report 4.3BSD-tahoe/sys/34
e
s 00002/00002/00752
d D 7.3 88/08/27 07:20:44 tef 13 12
c Add support for microvax 3000.
e
s 00020/00011/00734
d D 7.2 86/12/19 11:46:27 karels 12 11
c correct uba reallocation on reset
e
s 00001/00001/00744
d D 7.1 86/06/05 01:06:47 mckusick 11 10
c 4.3BSD release version
e
s 00006/00000/00739
d D 4.10 86/04/22 11:06:03 kridle 10 9
c MicroVAX II Integration (KA630)
e
s 00001/00004/00738
d D 4.9 86/02/20 19:52:47 karels 9 8
c lint
e
s 00006/00005/00736
d D 4.8 86/02/17 22:58:28 karels 8 7
c correct uba allocation after reset
e
s 00001/00001/00740
d D 4.7 85/11/22 06:39:15 tef 7 6
c standard list of device addresses must be null terminated.
e
s 00007/00007/00734
d D 4.6 85/11/08 19:08:21 karels 6 5
c share unibus resources between multiplexor types
e
s 00007/00028/00734
d D 4.5 85/11/04 18:19:34 karels 5 4
c move carrier change code to line disciplines; make PORTSELECTOR
c code and configuration consistent; change default speed to 9600
e
s 00001/00001/00761
d D 4.4 85/09/17 18:34:01 eric 4 3
c facilities in syslog
e
s 00001/00001/00761
d D 4.3 85/08/13 05:09:43 lepreau 3 2
c add PASS8: pass all 8 bits of input
e
s 00007/00001/00755
d D 4.2 85/06/08 14:14:30 mckusick 2 1
c Add copyright
e
s 00756/00000/00000
d D 4.1 85/05/20 21:01:31 mckusick 1 0
c date and time created 85/05/20 21:01:31 by mckusick
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
D 8
 * Copyright (c) 1982 Regents of the University of California.
E 8
I 8
D 11
 * Copyright (c) 1985 Regents of the University of California.
E 11
I 11
 * Copyright (c) 1985, 1986 Regents of the University of California.
E 11
E 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 2

/*
 * based on	dh.c 6.3	84/03/15
 * and on	dmf.c	6.2	84/02/16
 *
 * Dave Johnson, Brown University Computer Science
 *	ddj%brown@csnet-relay
 */

#include "dhu.h"
#if NDHU > 0
/*
 * DHU-11 driver
 */
D 15
#include "../machine/pte.h"
E 15
I 15
D 23
#include "machine/pte.h"
E 23
I 23
#include "../include/pte.h"
E 23
E 15

D 18
#include "bk.h"
E 18
D 23
#include "param.h"
#include "conf.h"
D 19
#include "dir.h"
E 19
#include "user.h"
#include "proc.h"
#include "ioctl.h"
#include "tty.h"
I 16
#include "ttydefaults.h"
E 16
#include "map.h"
#include "buf.h"
#include "vm.h"
#include "kernel.h"
#include "syslog.h"
E 23
I 23
#include "sys/param.h"
#include "sys/conf.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/ttydefaults.h"
#include "sys/map.h"
#include "sys/buf.h"
#include "sys/vm.h"
#include "sys/kernel.h"
#include "sys/syslog.h"
E 23
I 18
D 20
#include "tsleep.h"
E 20
E 18

#include "uba.h"
#include "ubareg.h"
#include "ubavar.h"
#include "dhureg.h"

D 23
#include "bkmac.h"
#include "clist.h"
#include "file.h"
#include "uio.h"
E 23
I 23
D 25
#include "sys/bkmac.h"
E 25
#include "sys/clist.h"
#include "sys/file.h"
#include "sys/uio.h"
E 23

/*
 * Definition of the driver for the auto-configuration program.
 */
int	dhuprobe(), dhuattach(), dhurint(), dhuxint();
struct	uba_device *dhuinfo[NDHU];
D 7
u_short dhustd[] = { 160440, 160500 };	/* some common addresses */
E 7
I 7
u_short dhustd[] = { 160440, 160500, 0 };	/* some common addresses */
E 7
struct	uba_driver dhudriver =
	{ dhuprobe, 0, dhuattach, 0, dhustd, "dhu", dhuinfo };

#define	NDHULINE 	(NDHU*16)

#define	UNIT(x)	(minor(x))

#ifndef PORTSELECTOR
D 5
#define ISPEED	B300
E 5
I 5
D 16
#define ISPEED	B9600
E 5
#define IFLAGS	(EVENP|ODDP|ECHO)
E 16
I 16
#define SPEED	TTYDEF_SPEED
#define LFLAG	TTYDEF_LFLAG
E 16
#else
D 16
#define ISPEED	B4800
#define IFLAGS	(EVENP|ODDP)
E 16
I 16
#define SPEED	B4800
#define LFLAG	(TTYDEF_LFLAG & ~ECHO)
E 16
#endif

/*
 * default receive silo timeout value -- valid values are 2..255
 * number of ms. to delay between first char received and receive interrupt
 *
 * A value of 20 gives same response as ABLE dh/dm with silo alarm = 0
 */
#define	DHU_DEF_TIMO	20

/*
 * Other values for silo timeout register defined here but not used:
 * receive interrupt only on modem control or silo alarm (3/4 full)
 */
#define DHU_POLL_TIMO	0
/*
 * receive interrupt immediately on receive character
 */
#define DHU_NO_TIMO	1

/*
 * Local variables for the driver
 */
/*
 * Baud rates: no 50, 200, or 38400 baud; all other rates are from "Group B".
 *	EXTA => 19200 baud
 *	EXTB => 2000 baud
 */
D 16
char	dhu_speeds[] =
	{ 0, 0, 1, 2, 3, 4, 0, 5, 6, 7, 8, 10, 11, 13, 14, 9 };
E 16
I 16
struct speedtab dhuspeedtab[] = {
	19200,	14,
	9600,	13,
	4800,	11,
	2400,	10,
	2000,	9,
	1800,	8,
	1200,	7,
	600,	6,
	300,	5,
	150,	4,
	134,	3,
	110,	2,
	75,	1,
	0,	0,
I 17
	EXTA,	14,
	EXTB,	9,
E 17
	-1,	-1,
};
E 16

short	dhusoftCAR[NDHU];

struct	tty dhu_tty[NDHULINE];
int	ndhu = NDHULINE;
int	dhuact;				/* mask of active dhu's */
int	dhustart(), ttrstrt();

/*
D 12
 * The clist space is mapped by the driver onto each UNIBUS.
E 12
I 12
 * The clist space is mapped by one terminal driver onto each UNIBUS.
 * The identity of the board which allocated resources is recorded,
 * so the process may be repeated after UNIBUS resets.
E 12
 * The UBACVT macro converts a clist space address for unibus uban
 * into an i/o space address for the DMA routine.
 */
D 12
int	dhu_ubinfo[NUBA];	/* info about allocated unibus map */
D 6
static int cbase[NUBA];		/* base address in unibus map */
E 6
I 6
int	cbase[NUBA];		/* base address in unibus map */
E 12
I 12
int	dhu_uballoc[NUBA];	/* which dhu (if any) allocated unibus map */
int	cbase[NUBA];		/* base address of clists in unibus map */
E 12
E 6
#define UBACVT(x, uban) 	(cbase[uban] + ((x)-(char *)cfree))

/*
 * Routine for configuration to force a dhu to interrupt.
 */
/*ARGSUSED*/
dhuprobe(reg)
	caddr_t reg;
{
	register int br, cvec;		/* these are ``value-result'' */
	register struct dhudevice *dhuaddr = (struct dhudevice *)reg;
	int i;

#ifdef lint
	br = 0; cvec = br; br = cvec;
	if (ndhu == 0) ndhu = 1;
	dhurint(0); dhuxint(0);
#endif
	/*
	 * The basic idea here is:
	 *	do a self-test by setting the Master-Reset bit
	 *	if this fails, then return
	 *	if successful, there will be 8 diagnostic codes in RX FIFO
	 *	therefore ask for a  Received-Data-Available interrupt
	 *	wait for it...
	 *	reset the interrupt-enable bit and flush out the diag. codes
	 */
	dhuaddr->dhucsr = DHU_CS_MCLR;
	for (i = 0; i < 1000; i++) {
		DELAY(10000);
		if ((dhuaddr->dhucsr&DHU_CS_MCLR) == 0)
			break;
	}
	if (dhuaddr->dhucsr&DHU_CS_MCLR)
		return(0);
	if (dhuaddr->dhucsr&DHU_CS_DFAIL)
		return(0);
	dhuaddr->dhucsr = DHU_CS_RIE;
	DELAY(1000);
	dhuaddr->dhucsr = 0;
	while (dhuaddr->dhurbuf < 0)
		/* void */;
	return (sizeof(struct dhudevice));
}

/*
 * Routine called to attach a dhu.
 */
dhuattach(ui)
	struct uba_device *ui;
{

	dhusoftCAR[ui->ui_unit] = ui->ui_flags;
I 8
	cbase[ui->ui_ubanum] = -1;
I 12
D 14
	dhu_uballoc[ui->ui_unit] = -1;
E 14
I 14
	dhu_uballoc[ui->ui_ubanum] = -1;
E 14
E 12
E 8
}

/*
 * Open a DHU11 line, mapping the clist onto the uba if this
 * is the first dhu on this uba.  Turn on this dhu if this is
 * the first use of it.
 */
/*ARGSUSED*/
dhuopen(dev, flag)
	dev_t dev;
{
	register struct tty *tp;
	register int unit, dhu;
	register struct dhudevice *addr;
	register struct uba_device *ui;
D 20
	int s;
E 20
I 20
	int s, error = 0;
E 20
I 16
	extern dhuparam();
E 16

	unit = UNIT(dev);
	dhu = unit >> 4;
	if (unit >= NDHULINE || (ui = dhuinfo[dhu])== 0 || ui->ui_alive == 0)
		return (ENXIO);
	tp = &dhu_tty[unit];
	if (tp->t_state & TS_XCLUDE && u.u_uid != 0)
		return (EBUSY);
	addr = (struct dhudevice *)ui->ui_addr;
	tp->t_addr = (caddr_t)addr;
	tp->t_oproc = dhustart;
I 16
	tp->t_param = dhuparam;
E 16
	/*
	 * While setting up state for this uba and this dhu,
	 * block uba resets which can clear the state.
	 */
	s = spl5();
D 6
	if (dhu_ubinfo[ui->ui_ubanum] == 0) {
E 6
I 6
D 8
	if (cbase[ui->ui_ubanum] == 0) {
E 8
I 8
	if (cbase[ui->ui_ubanum] == -1) {
E 8
E 6
D 12
		dhu_ubinfo[ui->ui_ubanum] =
		    uballoc(ui->ui_ubanum, (caddr_t)cfree,
			nclist*sizeof(struct cblock), 0);
D 8
		cbase[ui->ui_ubanum] = dhu_ubinfo[ui->ui_ubanum]&0x3ffff;
E 8
I 8
		cbase[ui->ui_ubanum] = UBAI_ADDR(dhu_ubinfo[ui->ui_ubanum]);
E 12
I 12
		dhu_uballoc[ui->ui_ubanum] = dhu;
		cbase[ui->ui_ubanum] = UBAI_ADDR(uballoc(ui->ui_ubanum,
		    (caddr_t)cfree, nclist*sizeof(struct cblock), 0));
E 12
E 8
	}
	if ((dhuact&(1<<dhu)) == 0) {
		addr->dhucsr = DHU_SELECT(0) | DHU_IE;
		addr->dhutimo = DHU_DEF_TIMO;
		dhuact |= (1<<dhu);
		/* anything else to configure whole board */
	}
	(void) splx(s);
	/*
	 * If this is first open, initialize tty state to default.
	 */
	if ((tp->t_state&TS_ISOPEN) == 0) {
I 22
		tp->t_state |= TS_WOPEN;
E 22
		ttychars(tp);
#ifndef PORTSELECTOR
D 16
		if (tp->t_ispeed == 0) {
#else
			tp->t_state |= TS_HUPCLS;
#endif PORTSELECTOR
			tp->t_ispeed = ISPEED;
			tp->t_ospeed = ISPEED;
			tp->t_flags = IFLAGS;
#ifndef PORTSELECTOR
E 16
I 16
		if (tp->t_ospeed == 0) {
#endif 
			tp->t_ispeed = SPEED;
			tp->t_ospeed = SPEED;
			ttsetwater(tp);
			tp->t_iflag = TTYDEF_IFLAG;
			tp->t_oflag = TTYDEF_OFLAG;
			tp->t_lflag = LFLAG;
			tp->t_cflag = TTYDEF_CFLAG;
#ifdef PORTSELECTOR
			tp->t_cflag |= HUPCL;
#else 
E 16
		}
D 16
#endif PORTSELECTOR
E 16
I 16
#endif 
E 16
		tp->t_dev = dev;
D 16
		dhuparam(unit);
E 16
I 16
		dhuparam(tp, &tp->t_termios);
E 16
	}
	/*
	 * Wait for carrier, then process line discipline specific open.
	 */
D 16
	s = spl5();
E 16
I 16
	s = spltty();
E 16
	if ((dhumctl(dev, DHU_ON, DMSET) & DHU_CAR) ||
	    (dhusoftCAR[dhu] & (1<<(unit&0xf))))
		tp->t_state |= TS_CARR_ON;
D 17
	while ((tp->t_state & TS_CARR_ON) == 0) {
E 17
I 17
D 20
	while (!(flag&O_NONBLOCK) && !(tp->t_cflag&CLOCAL) &&
	       (tp->t_state & TS_CARR_ON) == 0) {
E 20
I 20
	while ((flag&O_NONBLOCK) == 0 && (tp->t_cflag&CLOCAL) == 0 &&
	    (tp->t_state & TS_CARR_ON) == 0) {
E 20
E 17
		tp->t_state |= TS_WOPEN;
D 18
		sleep((caddr_t)&tp->t_rawq, TTIPRI);
E 18
I 18
D 20
		tsleep((caddr_t)&tp->t_rawq, TTIPRI, SLP_DHU_OPN, 0);
E 20
I 20
D 21
		if (error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
		    ttopen, 0))
E 21
I 21
D 22
		if ((error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
				    ttopen, 0)) ||
		    (error = ttclosed(tp)))
E 22
I 22
		if (error = ttysleep(tp, (caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
		    ttopen, 0))
E 22
E 21
			break;
E 20
E 18
	}
	(void) splx(s);
I 20
	if (error)
		return (error);
E 20
	return ((*linesw[tp->t_line].l_open)(dev, tp));
}

/*
 * Close a DHU11 line, turning off the modem control.
 */
/*ARGSUSED*/
D 26
dhuclose(dev, flag)
E 26
I 26
dhuclose(dev, flag, mode, p)
E 26
	dev_t dev;
D 26
	int flag;
E 26
I 26
	int flag, mode;
	struct proc *p;
E 26
{
	register struct tty *tp;
	register unit;

	unit = UNIT(dev);
	tp = &dhu_tty[unit];
D 26
	(*linesw[tp->t_line].l_close)(tp);
E 26
I 26
	(*linesw[tp->t_line].l_close)(tp, flag);
E 26
	(void) dhumctl(unit, DHU_BRK, DMBIC);
D 16
	if ((tp->t_state&(TS_HUPCLS|TS_WOPEN)) || (tp->t_state&TS_ISOPEN)==0)
E 16
I 16
	if ((tp->t_state&TS_WOPEN) || (tp->t_cflag&HUPCL) || 
D 20
	    (tp->t_state&TS_ISOPEN)==0)
E 20
I 20
	    (tp->t_state&TS_ISOPEN) == 0) {
E 20
E 16
#ifdef PORTSELECTOR
D 20
	{
		extern int wakeup();

E 20
		(void) dhumctl(unit, DHU_OFF, DMSET);
		/* Hold DTR low for 0.5 seconds */
D 20
		timeout(wakeup, (caddr_t) &tp->t_dev, hz/2);
		sleep((caddr_t) &tp->t_dev, PZERO);
	}
E 20
I 20
		(void) tsleep((caddr_t) &tp->t_dev, PZERO, ttclos, hz/2);
E 20
#else
		(void) dhumctl(unit, DHU_OFF, DMSET);
#endif PORTSELECTOR
D 20
	ttyclose(tp);
E 20
I 20
	}
	return (ttyclose(tp));
E 20
}

D 17
dhuread(dev, uio)
E 17
I 17
dhuread(dev, uio, flag)
E 17
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp = &dhu_tty[UNIT(dev)];

D 17
	return ((*linesw[tp->t_line].l_read)(tp, uio));
E 17
I 17
	return ((*linesw[tp->t_line].l_read)(tp, uio, flag));
E 17
}

D 17
dhuwrite(dev, uio)
E 17
I 17
dhuwrite(dev, uio, flag)
E 17
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp = &dhu_tty[UNIT(dev)];

D 17
	return ((*linesw[tp->t_line].l_write)(tp, uio));
E 17
I 17
	return ((*linesw[tp->t_line].l_write)(tp, uio, flag));
E 17
}

/*
 * DHU11 receiver interrupt.
 */
dhurint(dhu)
	int dhu;
{
	register struct tty *tp;
D 16
	register c;
E 16
I 16
	register creg, c;
E 16
	register struct dhudevice *addr;
	register struct tty *tp0;
	register struct uba_device *ui;
	register line;
	int overrun = 0;

I 10
D 13
#ifdef VAX630
E 13
I 13
#ifdef QBA
E 13
D 16
	(void) spl5();
E 16
I 16
	(void) spltty();
E 16
#endif
E 10
	ui = dhuinfo[dhu];
	if (ui == 0 || ui->ui_alive == 0)
		return;
	addr = (struct dhudevice *)ui->ui_addr;
	tp0 = &dhu_tty[dhu<<4];
	/*
	 * Loop fetching characters from the silo for this
	 * dhu until there are no more in the silo.
	 */
D 16
	while ((c = addr->dhurbuf) < 0) {	/* (c & DHU_RB_VALID) == on */
		line = DHU_RX_LINE(c);
E 16
I 16
	while ((creg = addr->dhurbuf) < 0) {	/* (c & DHU_RB_VALID) == on */
		line = DHU_RX_LINE(creg);
E 16
		tp = tp0 + line;
D 16
		if ((c & DHU_RB_STAT) == DHU_RB_STAT) {
E 16
I 16
		c = creg & 0xff;
		if ((creg & DHU_RB_STAT) == DHU_RB_STAT) {
E 16
			/*
			 * modem changed or diag info
			 */
D 16
			if (c & DHU_RB_DIAG) {
E 16
I 16
			if (creg & DHU_RB_DIAG) {
E 16
				/* decode diagnostic messages */
				continue;
			}
D 5
			if ((tp->t_state & TS_WOPEN) == 0 &&
			    (tp->t_flags & MDMBUF)) {
				if (c & DHU_ST_DCD) {
					tp->t_state &= ~TS_TTSTOP;
					ttstart(tp);
				} else if ((tp->t_state & TS_TTSTOP) == 0) {
					tp->t_state |= TS_TTSTOP;
					dhustop(tp, 0);
				}
			} else if ((c & DHU_ST_DCD) == 0 &&
				   (dhusoftCAR[dhu] & (1<<line)) == 0) {
				if ((tp->t_state & TS_WOPEN) == 0 &&
				    (tp->t_flags & NOHANG) == 0) {
					gsignal(tp->t_pgrp, SIGHUP);
					gsignal(tp->t_pgrp, SIGCONT);
					(void) dhumctl((dhu<<4)|line,
								DHU_OFF, DMSET);
					ttyflush(tp, FREAD|FWRITE);
				}
				tp->t_state &= ~TS_CARR_ON;
			} else {
				if ((tp->t_state & TS_CARR_ON) == 0) {
					tp->t_state |= TS_CARR_ON;
					wakeup((caddr_t)&tp->t_rawq);
				}
			}
E 5
I 5
D 16
			if (c & DHU_ST_DCD)
E 16
I 16
			if (creg & DHU_ST_DCD)
E 16
				(void)(*linesw[tp->t_line].l_modem)(tp, 1);
			else if ((dhusoftCAR[dhu] & (1<<line)) == 0 &&
			    (*linesw[tp->t_line].l_modem)(tp, 0) == 0)
				(void) dhumctl((dhu<<4)|line, DHU_OFF, DMSET);
E 5
			continue;
		}
		if ((tp->t_state&TS_ISOPEN) == 0) {
			wakeup((caddr_t)&tp->t_rawq);
#ifdef PORTSELECTOR
			if ((tp->t_state&TS_WOPEN) == 0)
#endif
D 5
			continue;
E 5
I 5
				continue;
E 5
		}
D 16
		if (c & DHU_RB_PE)
			if ((tp->t_flags&(EVENP|ODDP)) == EVENP ||
			    (tp->t_flags&(EVENP|ODDP)) == ODDP)
				continue;
		if ((c & DHU_RB_DO) && overrun == 0) {
D 4
			log(KERN_RECOV, "dhu%d: silo overflow\n", dhu);
E 4
I 4
			log(LOG_WARNING, "dhu%d: silo overflow\n", dhu);
E 4
			overrun = 1;
E 16
I 16
D 17
#ifdef COMPAT_43
		if (tp->t_line != POSXDISC) {
			if (creg & DHU_RB_PE)
				if ((tp->t_flags&(EVENP|ODDP)) == EVENP ||
				    (tp->t_flags&(EVENP|ODDP)) == ODDP)
					continue;
			if ((creg & DHU_RB_DO) && overrun == 0) {
				log(LOG_WARNING, "dhu%d: silo overflow\n", dhu);
				overrun = 1;
			}
			if (creg & DHU_RB_FE)
				/*
				 * At framing error (break) generate
				 * a null (in raw mode, for getty), or a
				 * interrupt (in cooked/cbreak mode).
				 */
				if (tp->t_flags&RAW)
					c = 0;
				else
					c = tp->t_intrc;
		} else {
#endif /*COMPAT_43*/
			if (creg & DHU_RB_PE)
				c |= TTY_PE;
			if (creg & DHU_RB_DO && overrun == 0) {
				log(LOG_WARNING, "dhu%d: silo overflow\n", dhu);
				overrun = 1;
			}
			if (creg & DHU_RB_FE)
				c |= TTY_FE;
#ifdef COMPAT_43
E 17
I 17
		if (creg & DHU_RB_PE)
			c |= TTY_PE;
		if (creg & DHU_RB_DO && overrun == 0) {
			log(LOG_WARNING, "dhu%d: silo overflow\n", dhu);
			overrun = 1;
E 17
E 16
		}
D 16
		if (c & DHU_RB_FE)
			/*
			 * At framing error (break) generate
			 * a null (in raw mode, for getty), or a
			 * interrupt (in cooked/cbreak mode).
			 */
			if (tp->t_flags&RAW)
				c = 0;
			else
				c = tp->t_intrc;
E 16
I 16
D 17
#endif
E 17
I 17
		if (creg & DHU_RB_FE)
			c |= TTY_FE;
E 17

E 16
D 17
#if NBK > 0
		if (tp->t_line == NETLDISC) {
			c &= 0x7f;
			BKINPUT(c, tp);
		} else
#endif
			(*linesw[tp->t_line].l_rint)(c, tp);
E 17
I 17
		(*linesw[tp->t_line].l_rint)(c, tp);
E 17
	}
}

/*
 * Ioctl for DHU11.
 */
/*ARGSUSED*/
dhuioctl(dev, cmd, data, flag)
	caddr_t data;
{
	register struct tty *tp;
	register int unit = UNIT(dev);
D 9
	register dhu = unit>>4;
	register bit = (1<<(unit&0xf));
E 9
	int error;

	tp = &dhu_tty[unit];
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, data, flag);
D 16
	if (error >= 0) {
		if (cmd == TIOCSETP || cmd == TIOCSETN || cmd == TIOCLSET ||
		    cmd == TIOCLBIC || cmd == TIOCLBIS)
			dhuparam(unit);
E 16
I 16
	if (error >= 0)
E 16
		return (error);
D 16
	}
E 16

	switch (cmd) {
	case TIOCSBRK:
		(void) dhumctl(unit, DHU_BRK, DMBIS);
		break;

	case TIOCCBRK:
		(void) dhumctl(unit, DHU_BRK, DMBIC);
		break;

	case TIOCSDTR:
		(void) dhumctl(unit, DHU_DTR|DHU_RTS, DMBIS);
		break;

	case TIOCCDTR:
		(void) dhumctl(unit, DHU_DTR|DHU_RTS, DMBIC);
		break;

	case TIOCMSET:
		(void) dhumctl(dev, dmtodhu(*(int *)data), DMSET);
		break;

	case TIOCMBIS:
		(void) dhumctl(dev, dmtodhu(*(int *)data), DMBIS);
		break;

	case TIOCMBIC:
		(void) dhumctl(dev, dmtodhu(*(int *)data), DMBIC);
		break;

	case TIOCMGET:
		*(int *)data = dhutodm(dhumctl(dev, 0, DMGET));
		break;
	default:
		return (ENOTTY);
	}
	return (0);
}

dmtodhu(bits)
	register int bits;
{
	register int b = 0;

	if (bits & DML_RTS) b |= DHU_RTS;
	if (bits & DML_DTR) b |= DHU_DTR;
	if (bits & DML_LE) b |= DHU_LE;
	return(b);
}

dhutodm(bits)
	register int bits;
{
	register int b = 0;

	if (bits & DHU_DSR) b |= DML_DSR;
	if (bits & DHU_RNG) b |= DML_RNG;
	if (bits & DHU_CAR) b |= DML_CAR;
	if (bits & DHU_CTS) b |= DML_CTS;
	if (bits & DHU_RTS) b |= DML_RTS;
	if (bits & DHU_DTR) b |= DML_DTR;
	if (bits & DHU_LE) b |= DML_LE;
	return(b);
}


/*
 * Set parameters from open or stty into the DHU hardware
D 16
 * registers.
E 16
I 16
 * registers.  Impossible values for speed or character
 * size are ignored and not copied back into tp.
E 16
 */
D 16
dhuparam(unit)
	register int unit;
{
E 16
I 16
dhuparam(tp, want)
E 16
	register struct tty *tp;
D 16
	register struct dhudevice *addr;
E 16
I 16
	register struct termios *want;
{
	register int unit = UNIT(tp->t_dev);
	register struct dhudevice *addr = (struct dhudevice *)tp->t_addr;
E 16
	register int lpar;
I 16
	register long cflag;
	register int incode, outcode;
E 16
	int s;
D 16

	tp = &dhu_tty[unit];
	addr = (struct dhudevice *)tp->t_addr;
E 16
I 16
	
E 16
	/*
	 * Block interrupts so parameters will be set
	 * before the line interrupts.
	 */
D 16
	s = spl5();
	if ((tp->t_ispeed) == 0) {
		tp->t_state |= TS_HUPCLS;
E 16
I 16
	s = spltty();

	if (want->c_ospeed == 0) {
		tp->t_ospeed = 0;
		tp->t_cflag |= HUPCL;
E 16
		(void)dhumctl(unit, DHU_OFF, DMSET);
		splx(s);
D 24
		return;
E 24
I 24
		return (0);
E 24
	}
D 16
	lpar = (dhu_speeds[tp->t_ospeed]<<12) | (dhu_speeds[tp->t_ispeed]<<8);
	if ((tp->t_ispeed) == B134)
		lpar |= DHU_LP_BITS6|DHU_LP_PENABLE;
D 3
	else if (tp->t_flags & (RAW|LITOUT))
E 3
I 3
	else if (tp->t_flags & (RAW|LITOUT|PASS8))
E 3
		lpar |= DHU_LP_BITS8;
E 16
I 16

	if ((outcode = ttspeedtab(want->c_ospeed, dhuspeedtab)) >= 0)
		tp->t_ospeed = want->c_ospeed;
E 16
	else
D 16
		lpar |= DHU_LP_BITS7|DHU_LP_PENABLE;
	if (tp->t_flags&EVENP)
		lpar |= DHU_LP_EPAR;
	if ((tp->t_ospeed) == B110)
E 16
I 16
		outcode = ttspeedtab(tp->t_ospeed, dhuspeedtab);

	if (want->c_ispeed == 0) {
		tp->t_ispeed = 0;
		incode = outcode;
	} else if ((incode = ttspeedtab(want->c_ispeed, dhuspeedtab)) >= 0)
		tp->t_ispeed = want->c_ispeed;
	else
		incode = ttspeedtab(tp->t_ispeed, dhuspeedtab);

	lpar = ((char)outcode<<12) | ((char)incode<<8);

	switch (want->c_cflag&CSIZE) {
	case CS6: case CS7: case CS8:
		tp->t_cflag =  want->c_cflag;
		break;
	default:
		tp->t_cflag = (tp->t_cflag&CSIZE) | (want->c_cflag & ~CSIZE);
	}
	cflag = tp->t_cflag;

	switch(cflag&CSIZE) {
	case CS6:
		lpar |= DHU_LP_BITS6;
		break;
	case CS7:
		lpar |= DHU_LP_BITS7;
		break;
	case CS8:
		lpar |= DHU_LP_BITS8;
		break;
	}
	if (cflag&PARENB) {
		lpar |= DHU_LP_PENABLE;
		if ((cflag&PARODD) == 0)
			lpar |= DHU_LP_EPAR;
	}
	if (cflag&CSTOPB)
E 16
		lpar |= DHU_LP_TWOSB;
D 16
	addr->dhucsr = DHU_SELECT(unit) | DHU_IE;
E 16
I 16
D 17
	if (cflag&CREAD)
		addr->dhucsr = DHU_SELECT(unit) | DHU_IE;
	else
		addr->dhucsr = DHU_SELECT(unit) | DHU_CS_TIE;
E 17

I 17
	addr->dhucsr = DHU_SELECT(unit) | DHU_IE;
E 17
E 16
	addr->dhulpr = lpar;
	splx(s);
I 24
	return (0);
E 24
}

/*
 * DHU11 transmitter interrupt.
 * Restart each line which used to be active but has
 * terminated transmission since the last interrupt.
 */
dhuxint(dhu)
	int dhu;
{
	register struct tty *tp;
	register struct dhudevice *addr;
	register struct tty *tp0;
	register struct uba_device *ui;
	register int line, t;
	u_short cntr;

I 10
D 13
#ifdef VAX630
E 13
I 13
#ifdef QBA
E 13
	(void) spl5();
#endif
E 10
	ui = dhuinfo[dhu];
	tp0 = &dhu_tty[dhu<<4];
	addr = (struct dhudevice *)ui->ui_addr;
	while ((t = addr->dhucsrh) & DHU_CSH_TI) {
		line = DHU_TX_LINE(t);
		tp = tp0 + line;
		tp->t_state &= ~TS_BUSY;
		if (t & DHU_CSH_NXM) {
			printf("dhu(%d,%d): NXM fault\n", dhu, line);
			/* SHOULD RESTART OR SOMETHING... */
		}
		if (tp->t_state&TS_FLUSH)
			tp->t_state &= ~TS_FLUSH;
		else {
			addr->dhucsrl = DHU_SELECT(line) | DHU_IE;
			/*
			 * Do arithmetic in a short to make up
			 * for lost 16&17 bits.
			 */
			cntr = addr->dhubar1 -
			    UBACVT(tp->t_outq.c_cf, ui->ui_ubanum);
			ndflush(&tp->t_outq, (int)cntr);
		}
		if (tp->t_line)
			(*linesw[tp->t_line].l_start)(tp);
		else
			dhustart(tp);
	}
}

/*
 * Start (restart) transmission on the given DHU11 line.
 */
dhustart(tp)
	register struct tty *tp;
{
	register struct dhudevice *addr;
	register int car, dhu, unit, nch;
	int s;

	unit = minor(tp->t_dev);
	dhu = unit >> 4;
	unit &= 0xf;
	addr = (struct dhudevice *)tp->t_addr;

	/*
	 * Must hold interrupts in following code to prevent
	 * state of the tp from changing.
	 */
	s = spl5();
	/*
	 * If it's currently active, or delaying, no need to do anything.
	 */
	if (tp->t_state&(TS_TIMEOUT|TS_BUSY|TS_TTSTOP))
		goto out;
	/*
	 * If there are sleepers, and output has drained below low
	 * water mark, wake up the sleepers..
	 */
D 16
	if (tp->t_outq.c_cc<=TTLOWAT(tp)) {
E 16
I 16
	if (tp->t_outq.c_cc <= tp->t_lowat) {
E 16
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
	/*
	 * Now restart transmission unless the output queue is
	 * empty.
	 */
	if (tp->t_outq.c_cc == 0)
		goto out;
D 16
	if (tp->t_flags & (RAW|LITOUT))
E 16
I 16
D 17
	if (!(tp->t_oflag & OPOST))
E 17
I 17
	if (1 || !(tp->t_oflag & OPOST))	/*XXX*/
E 17
E 16
		nch = ndqb(&tp->t_outq, 0);
	else {
		nch = ndqb(&tp->t_outq, 0200);
		/*
		 * If first thing on queue is a delay process it.
		 */
		if (nch == 0) {
			nch = getc(&tp->t_outq);
			timeout(ttrstrt, (caddr_t)tp, (nch&0x7f)+6);
			tp->t_state |= TS_TIMEOUT;
			goto out;
		}
	}
	/*
	 * If characters to transmit, restart transmission.
	 */
	if (nch) {
		car = UBACVT(tp->t_outq.c_cf, dhuinfo[dhu]->ui_ubanum);
		addr->dhucsrl = DHU_SELECT(unit) | DHU_IE;
		addr->dhulcr &= ~DHU_LC_TXABORT;
		addr->dhubcr = nch;
		addr->dhubar1 = car;
		addr->dhubar2 = ((car >> DHU_XBA_SHIFT) & DHU_BA2_XBA) |
					DHU_BA2_DMAGO;
		tp->t_state |= TS_BUSY;
	}
out:
	splx(s);
}

/*
 * Stop output on a line, e.g. for ^S/^Q or output flush.
 */
/*ARGSUSED*/
dhustop(tp, flag)
	register struct tty *tp;
{
	register struct dhudevice *addr;
	register int unit, s;

	addr = (struct dhudevice *)tp->t_addr;
	/*
	 * Block input/output interrupts while messing with state.
	 */
	s = spl5();
	if (tp->t_state & TS_BUSY) {
		/*
		 * Device is transmitting; stop output
		 * by selecting the line and setting the
		 * abort xmit bit.  We will get an xmit interrupt,
		 * where we will figure out where to continue the
		 * next time the transmitter is enabled.  If
		 * TS_FLUSH is set, the outq will be flushed.
		 * In either case, dhustart will clear the TXABORT bit.
		 */
		unit = minor(tp->t_dev);
		addr->dhucsrl = DHU_SELECT(unit) | DHU_IE;
		addr->dhulcr |= DHU_LC_TXABORT;
		if ((tp->t_state&TS_TTSTOP)==0)
			tp->t_state |= TS_FLUSH;
	}
	(void) splx(s);
}

/*
 * DHU11 modem control
 */
dhumctl(dev, bits, how)
	dev_t dev;
	int bits, how;
{
	register struct dhudevice *dhuaddr;
D 9
	register int unit, mbits, lcr;
E 9
I 9
	register int unit, mbits;
E 9
	int s;

	unit = UNIT(dev);
	dhuaddr = (struct dhudevice *)(dhu_tty[unit].t_addr);
	unit &= 0xf;
	s = spl5();
	dhuaddr->dhucsr = DHU_SELECT(unit) | DHU_IE;
	/*
	 * combine byte from stat register (read only, bits 16..23)
	 * with lcr register (read write, bits 0..15).
	 */
	mbits = dhuaddr->dhulcr | (dhuaddr->dhustat << 16);
	switch (how) {
	case DMSET:
		mbits = (mbits & 0xff0000) | bits;
		break;

	case DMBIS:
		mbits |= bits;
		break;

	case DMBIC:
		mbits &= ~bits;
		break;

	case DMGET:
		(void) splx(s);
		return(mbits);
	}
	dhuaddr->dhulcr = (mbits & 0xffff) | DHU_LC_RXEN;
	dhuaddr->dhulcr2 = DHU_LC2_TXEN;
	(void) splx(s);
	return(mbits);
}

/*
 * Reset state of driver if UBA reset was necessary.
 * Reset the line and modem control registers.
 * restart transmitters.
 */
dhureset(uban)
	int uban;
{
	register int dhu, unit;
	register struct tty *tp;
	register struct uba_device *ui;
	register struct dhudevice *addr;
	int i;
D 9
	register int s;
E 9

D 6
	if (dhu_ubinfo[uban] == 0)
		return;
	dhu_ubinfo[uban] = uballoc(uban, (caddr_t)cfree,
				    nclist*sizeof (struct cblock), 0);
	cbase[uban] = dhu_ubinfo[uban]&0x3ffff;
E 6
	for (dhu = 0; dhu < NDHU; dhu++) {
		ui = dhuinfo[dhu];
		if (ui == 0 || ui->ui_alive == 0 || ui->ui_ubanum != uban)
			continue;
		printf(" dhu%d", dhu);
I 6
D 8
		if (cbase[uban] == 0) {
E 8
I 8
D 12
		if (dhu_ubinfo[uban]) {
E 8
			dhu_ubinfo[uban] = uballoc(uban, (caddr_t)cfree,
					    nclist*sizeof (struct cblock), 0);
D 8
			cbase[uban] = dhu_ubinfo[uban]&0x3ffff;
E 8
I 8
			cbase[uban] = UBAI_ADDR(dhu_ubinfo[uban]);
E 12
I 12
		if (dhu_uballoc[uban] == dhu) {
			int info;

			info = uballoc(uban, (caddr_t)cfree,
			    nclist * sizeof(struct cblock), UBA_CANTWAIT);
			if (info)
				cbase[uban] = UBAI_ADDR(info);
			else {
				printf(" [can't get uba map]");
				cbase[uban] = -1;
			}
E 12
E 8
		}
E 6
		addr = (struct dhudevice *)ui->ui_addr;
		addr->dhucsr = DHU_SELECT(0) | DHU_IE;
		addr->dhutimo = DHU_DEF_TIMO;
		unit = dhu * 16;
		for (i = 0; i < 16; i++) {
			tp = &dhu_tty[unit];
			if (tp->t_state & (TS_ISOPEN|TS_WOPEN)) {
D 16
				dhuparam(unit);
E 16
I 16
				dhuparam(tp, &tp->t_termios);
E 16
				(void)dhumctl(unit, DHU_ON, DMSET);
				tp->t_state &= ~TS_BUSY;
				dhustart(tp);
			}
			unit++;
		}
	}
}
#endif
E 1
