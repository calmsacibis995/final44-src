h50954
s 00001/00001/01297
d D 8.5 95/01/09 18:28:55 cgd 26 25
c ioctl cmd arg is u_long, strategy returns void.
e
s 00001/00000/01297
d D 8.4 94/01/12 09:48:59 bostic 25 24
c lint
e
s 00002/00000/01295
d D 8.3 94/01/12 09:48:40 bostic 24 23
c lint
e
s 00000/00001/01295
d D 8.2 93/09/04 13:25:07 bostic 23 22
c lint
e
s 00002/00002/01294
d D 8.1 93/06/10 21:32:03 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/01286
d D 7.21 93/02/18 20:42:58 hibler 21 20
c IOSTATS -> DCMSTATS
e
s 00018/00017/01278
d D 7.20 92/10/11 09:23:40 bostic 20 19
c make kernel includes standard
e
s 00001/00001/01294
d D 7.19 92/07/24 16:00:47 mccanne 19 18
c new kgdb framing---changed FRAME_START now identifies a packet
e
s 00003/00003/01292
d D 7.18 92/06/05 15:30:58 hibler 18 17
c merge latest Utah hp300 code including 68040 support
e
s 00002/00006/01293
d D 7.17 92/02/15 21:17:48 torek 17 16
c convert to use new select interface, selrecord/selwakeup
e
s 00005/00002/01294
d D 7.16 92/02/05 23:37:20 mckusick 16 15
c lint
e
s 00003/00002/01293
d D 7.15 92/02/05 18:52:17 mckusick 15 14
c dcmstart is a void
e
s 00079/00038/01216
d D 7.14 91/06/27 17:37:18 karels 14 13
c fix modem control in dcmclose; hack for "HP DCE" on new muxes
e
s 00004/00002/01250
d D 7.13 91/05/16 17:39:09 marc 13 12
c pass flags through in device close
e
s 00007/00005/01245
d D 7.12 91/05/07 09:47:16 hibler 12 11
c DIO-II support, KGDB_CHEAT ifdef from somebody
e
s 00100/00059/01150
d D 7.11 91/05/04 19:43:15 karels 11 10
c new kgdb stuff; use dev_t for kgdb_dev instead of cons index;
c sticky tty params; new proc and calling conventions
e
s 00014/00014/01195
d D 7.10 90/12/16 16:35:33 bostic 10 9
c kernel reorg
e
s 00067/00036/01142
d D 7.9 90/12/05 18:26:16 mckusick 9 8
c update from Mike Hibler for new VM and other machine support
e
s 00001/00001/01177
d D 7.8 90/06/30 16:34:46 karels 8 7
c uninitialized error value when carrier/CLOCAL was already on
e
s 00021/00008/01157
d D 7.7 90/06/27 09:00:44 hibler 7 6
c added rts/cts flow control
e
s 00007/00010/01158
d D 7.6 90/06/26 13:29:29 hibler 6 5
c replace ttclosed with ttysleep
e
s 00003/00006/01165
d D 7.5 90/06/22 08:59:10 hibler 5 4
c get rid of old recv char kludge, correct a debug printf
e
s 00001/00000/01170
d D 7.4 90/06/06 18:55:02 marc 4 3
c set WOPEN on first open
e
s 00003/00002/01167
d D 7.3 90/06/06 17:38:25 marc 3 2
c check for revoked terminal (ttclosed)
e
s 00586/00278/00583
d D 7.2 90/05/25 15:43:00 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00861/00000/00000
d D 7.1 90/05/08 22:06:51 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 22
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 9
 * from: $Hdr: dcm.c 1.17 89/10/01$
E 9
I 9
D 12
 * from: $Hdr: dcm.c 1.1 90/07/09$
E 12
I 12
D 18
 * from: $Hdr: dcm.c 1.26 91/01/21$
E 18
I 18
 * from Utah: $Hdr: dcm.c 1.29 92/01/21$
E 18
E 12
E 9
 *
 *	%W% (Berkeley) %G%
 */

/*
D 2
 *  Console support is not finished.
E 2
I 2
 * TODO:
 *	Timeouts
D 11
 *	Test console/kgdb support.
E 11
I 11
 *	Test console support.
E 11
E 2
 */

#include "dcm.h"
#if NDCM > 0
/*
 *  98642/MUX
 */
D 10
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
#include "time.h"
E 10
I 10
D 20
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/ioctl.h"
D 17
#include "sys/tty.h"
E 17
D 11
#include "sys/user.h"
E 11
I 11
#include "sys/proc.h"
I 17
#include "sys/tty.h"
E 17
E 11
#include "sys/conf.h"
#include "sys/file.h"
#include "sys/uio.h"
#include "sys/kernel.h"
#include "sys/syslog.h"
#include "sys/time.h"
E 20
I 20
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
#include <sys/time.h>
E 20
E 10

D 18
#include "device.h"
E 18
I 18
D 20
#include "hp/dev/device.h"
E 18
#include "dcmreg.h"
D 10
#include "machine/cpu.h"
#include "machine/isr.h"
E 10
I 10
D 11
#include "../include/cpu.h"
E 11
I 11
#include "machine/cpu.h"
E 11
#include "../hp300/isr.h"
E 20
I 20
#include <hp/dev/device.h>
E 20
E 10

I 20
#include <hp300/dev/dcmreg.h>
#include <machine/cpu.h>
#include <hp300/hp300/isr.h>

E 20
D 2
int	dcmprobe();
E 2
I 2
#ifndef DEFAULT_BAUD_RATE
#define DEFAULT_BAUD_RATE 9600
#endif

D 23
int	ttrstrt();
E 23
D 15
int	dcmprobe(), dcmstart(), dcmintr(), dcmparam();

E 15
I 15
int	dcmprobe(), dcmintr(), dcmparam();
void	dcmstart();
E 15
E 2
struct	driver dcmdriver = {
	dcmprobe, "dcm",
};

#define NDCMLINE (NDCM*4)

D 2
int	dcmstart(), dcmparam(), dcmintr();
int	dcmsoftCAR[NDCM];
int     dcmintschm[NDCM];
E 2
I 2
struct	tty dcm_tty[NDCMLINE];
I 9
struct	modemreg *dcm_modem[NDCMLINE];
E 9
I 7
char	mcndlast[NDCMLINE];	/* XXX last modem status for line */
E 7
int	ndcm = NDCMLINE;

E 2
int	dcm_active;
D 2
int	ndcm = NDCM;
int	dcmconsole = -1;
E 2
I 2
int	dcmsoftCAR[NDCM];
E 2
struct	dcmdevice *dcm_addr[NDCM];
D 2
struct	tty dcm_tty[NDCMLINE];
int	dcm_cnt = NDCMLINE;
E 2
struct	isr dcmisr[NDCM];
D 2
int     dcmintrval = 5; /* rate in secs that interschem is examined */
long    dcmbang[NDCM];
int	dcmchrrd[NDCM];	/* chars read during each sample time */
int     dcmintrocc[NDCM];	/* # of interrupts for each sample time */
E 2

D 2

E 2
struct speedtab dcmspeedtab[] = {
	0,	BR_0,
	50,	BR_50,
	75,	BR_75,
	110,	BR_110,
	134,	BR_134,
	150,	BR_150,
	300,	BR_300,
	600,	BR_600,
	1200,	BR_1200,
	1800,	BR_1800,
	2400,	BR_2400,
	4800,	BR_4800,
	9600,	BR_9600,
	19200,	BR_19200,
	38400,	BR_38400,
	-1,	-1
};

I 2
/* u-sec per character based on baudrate (assumes 1 start/8 data/1 stop bit) */
#define	DCM_USPERCH(s)	(10000000 / (s))

/*
 * Per board interrupt scheme.  16.7ms is the polling interrupt rate
D 14
 * (16.7ms is about 550 buad, 38.4k is 72 chars in 16.7ms).
E 14
I 14
 * (16.7ms is about 550 baud, 38.4k is 72 chars in 16.7ms).
E 14
 */
#define DIS_TIMER	0
#define DIS_PERCHAR	1
#define DIS_RESET	2

int	dcmistype = -1;		/* -1 == dynamic, 0 == timer, 1 == perchar */
int     dcminterval = 5;	/* interval (secs) between checks */
struct	dcmischeme {
	int	dis_perchar;	/* non-zero if interrupting per char */
	long	dis_time;	/* last time examined */
	int	dis_intr;	/* recv interrupts during last interval */
	int	dis_char;	/* characters read during last interval */
} dcmischeme[NDCM];

/*
 * Console support
 */
I 11
#ifdef DCMCONSOLE
int	dcmconsole = DCMCONSOLE;
#else
E 11
int	dcmconsole = -1;
I 11
#endif
int	dcmconsinit;
E 11
int	dcmdefaultrate = DEFAULT_BAUD_RATE;
int	dcmconbrdbusy = 0;
I 11
int	dcmmajor;
E 11
extern	struct tty *constty;

#ifdef KGDB
/*
 * Kernel GDB support
 */
I 11
D 20
#include "machine/remote-sl.h"
E 20
I 20
#include <machine/remote-sl.h>
E 20

E 11
D 14
extern int kgdb_dev;
E 14
I 14
extern dev_t kgdb_dev;
E 14
extern int kgdb_rate;
extern int kgdb_debug_init;
#endif

D 21
/* #define IOSTATS */
E 21
I 21
/* #define DCMSTATS */
E 21

E 2
#ifdef DEBUG
D 9
int	dcmdebug = 0x00;
E 9
I 9
int	dcmdebug = 0x0;
E 9
#define DDB_SIOERR	0x01
#define DDB_PARAM	0x02
#define DDB_INPUT	0x04
#define DDB_OUTPUT	0x08
#define DDB_INTR	0x10
D 2
#define DDB_IOCTL       0x20
#define DDB_INTSCHM     0x40
#define DDB_MOD         0x80
E 2
I 2
#define DDB_IOCTL	0x20
#define DDB_INTSCHM	0x40
#define DDB_MODEM	0x80
E 2
#define DDB_OPENCLOSE	0x100
D 2

long unsigned int dcmrsize[33];	/* read sizes, 32 for over 31, 0 for 0 */
E 2
#endif

D 2
extern	struct tty *constty;
E 2
I 2
D 21
#ifdef IOSTATS
E 21
I 21
#ifdef DCMSTATS
E 21
#define	DCMRBSIZE	94
#define DCMXBSIZE	24
E 2

I 2
struct	dcmstats {
	long	xints;		    /* # of xmit ints */
	long	xchars;		    /* # of xmit chars */
	long	xempty;		    /* times outq is empty in dcmstart */
	long	xrestarts;	    /* times completed while xmitting */
	long	rints;		    /* # of recv ints */
	long	rchars;		    /* # of recv chars */
	long	xsilo[DCMXBSIZE+2]; /* times this many chars xmit on one int */
	long	rsilo[DCMRBSIZE+2]; /* times this many chars read on one int */
} dcmstats[NDCM];
#endif

E 2
#define UNIT(x)		minor(x)
D 2
#define	BOARD(x)	((x) >> 2)
E 2
I 2
#define	BOARD(x)	(((x) >> 2) & 0x3f)
E 2
#define PORT(x)		((x) & 3)
#define MKUNIT(b,p)	(((b) << 2) | (p))

I 14
/*
 * Conversion from "HP DCE" to almost-normal DCE: on the 638 8-port mux,
 * the distribution panel uses "HP DCE" conventions.  If requested via
 * the device flags, we swap the inputs to something closer to normal DCE,
 * allowing a straight-through cable to a DTE or a reversed cable
 * to a DCE (reversing 2-3, 4-5, 8-20 and leaving 6 unconnected;
 * this gets "DCD" on pin 20 and "CTS" on 4, but doesn't connect
 * DSR or make RTS work, though).  The following gives the full
 * details of a cable from this mux panel to a modem:
 *
 *		     HP		    modem
 *		name	pin	pin	name
 * HP inputs:
 *		"Rx"	 2	 3	Tx
 *		CTS	 4	 5	CTS	(only needed for CCTS_OFLOW)
 *		DCD	20	 8	DCD
 *		"DSR"	 9	 6	DSR	(unneeded)
 *		RI	22	22	RI	(unneeded)
 *
 * HP outputs:
 *		"Tx"	 3	 2	Rx
 *		"DTR"	 6	not connected
 *		"RTS"	 8	20	DTR
 *		"SR"	23	 4	RTS	(often not needed)
 */
#define	FLAG_STDDCE	0x10	/* map inputs if this bit is set in flags */
#define hp2dce_in(ibits)	(iconv[(ibits) & 0xf])
static char iconv[16] = {
	0,		MI_DM,		MI_CTS,		MI_CTS|MI_DM,
	MI_CD,		MI_CD|MI_DM,	MI_CD|MI_CTS,	MI_CD|MI_CTS|MI_DM,
	MI_RI,		MI_RI|MI_DM,	MI_RI|MI_CTS,	MI_RI|MI_CTS|MI_DM,
	MI_RI|MI_CD,	MI_RI|MI_CD|MI_DM, MI_RI|MI_CD|MI_CTS,
	MI_RI|MI_CD|MI_CTS|MI_DM
};

E 14
dcmprobe(hd)
	register struct hp_device *hd;
{
	register struct dcmdevice *dcm;
	register int i;
	register int timo = 0;
D 2
	int s, brd;
E 2
I 2
D 14
	int s, brd, isconsole;
E 14
I 14
	int s, brd, isconsole, mbits;
E 14
E 2

	dcm = (struct dcmdevice *)hd->hp_addr;
	if ((dcm->dcm_rsid & 0x1f) != DCMID)
		return (0);
	brd = hd->hp_unit;
I 2
	isconsole = (brd == BOARD(dcmconsole));
	/*
	 * XXX selected console device (CONSUNIT) as determined by
	 * dcmcnprobe does not agree with logical numbering imposed
	 * by the config file (i.e. lowest address DCM is not unit
	 * CONSUNIT).  Don't recognize this card.
	 */
	if (isconsole && dcm != dcm_addr[BOARD(dcmconsole)])
D 14
		return(0);
E 14
I 14
		return (0);
E 14

	/*
	 * Empirically derived self-test magic
	 */
E 2
	s = spltty();
	dcm->dcm_rsid = DCMRS;
	DELAY(50000);	/* 5000 is not long enough */
	dcm->dcm_rsid = 0; 
	dcm->dcm_ic = IC_IE;
	dcm->dcm_cr = CR_SELFT;
D 2
	while ((dcm->dcm_ic & IC_IR) == 0) {
		if (++timo == 20000) {
			printf("dcm%d: timeout on selftest interrupt\n", brd);
			printf("dcm%d:rsid %x, ic %x, cr %x, iir %x\n",
			       brd, dcm->dcm_rsid, dcm->dcm_ic,
			       dcm->dcm_cr, dcm->dcm_iir);
E 2
I 2
	while ((dcm->dcm_ic & IC_IR) == 0)
		if (++timo == 20000)
E 2
D 14
			return(0);
E 14
I 14
			return (0);
E 14
D 2
		}
	}
E 2
	DELAY(50000)	/* XXX why is this needed ???? */
D 2
	while ((dcm->dcm_iir & IIR_SELFT) == 0) {
		if (++timo == 400000) {
			printf("dcm%d: timeout on selftest\n", brd);
			printf("dcm%d:rsid %x, ic %x, cr %x, iir %x\n",
			       brd, dcm->dcm_rsid, dcm->dcm_ic,
			       dcm->dcm_cr, dcm->dcm_iir);
E 2
I 2
	while ((dcm->dcm_iir & IIR_SELFT) == 0)
		if (++timo == 400000)
E 2
D 14
			return(0);
E 14
I 14
			return (0);
E 14
D 2
		}
	}
E 2
	DELAY(50000)	/* XXX why is this needed ???? */
	if (dcm->dcm_stcon != ST_OK) {
D 2
		printf("dcm%d: self test failed: %x\n", brd, dcm->dcm_stcon);
E 2
I 2
		if (!isconsole)
			printf("dcm%d: self test failed: %x\n",
			       brd, dcm->dcm_stcon);
E 2
D 14
		return(0);
E 14
I 14
		return (0);
E 14
	}
	dcm->dcm_ic = IC_ID;
	splx(s);

	hd->hp_ipl = DCMIPL(dcm->dcm_ic);
D 2
	dcmisr[brd].isr_ipl = hd->hp_ipl;
	dcmisr[brd].isr_arg = brd;
	dcmisr[brd].isr_intr = dcmintr;
E 2
	dcm_addr[brd] = dcm;
	dcm_active |= 1 << brd;
	dcmsoftCAR[brd] = hd->hp_flags;
D 2
	dcmintschm[brd] = 1;	/* start with interrupt/char */
	for (i = 0; i < 256; i++)
		dcm->dcm_bmap[i].data_data = 0x0f;
	dcmintrocc[brd] = 0;
	dcmchrrd[brd] = 0;
E 2
I 2
	dcmisr[brd].isr_ipl = hd->hp_ipl;
	dcmisr[brd].isr_arg = brd;
	dcmisr[brd].isr_intr = dcmintr;
E 2
	isrlink(&dcmisr[brd]);
D 2
	dcm->dcm_mdmmsk = MI_CD;	/* Enable carrier detect interrupts */
	dcm->dcm_ic = IC_IE;	/* turn interrupts on */
E 2
I 2
#ifdef KGDB
D 11
	if (major(kgdb_dev) == 2 && BOARD(kgdb_dev) == brd) {
E 11
I 11
	if (major(kgdb_dev) == dcmmajor && BOARD(kgdb_dev) == brd) {
E 11
		if (dcmconsole == UNIT(kgdb_dev))
D 14
			kgdb_dev = -1;	/* can't debug over console port */
E 14
I 14
			kgdb_dev = NODEV; /* can't debug over console port */
E 14
I 12
#ifndef KGDB_CHEAT
E 12
I 11
		/*
		 * The following could potentially be replaced
		 * by the corresponding code in dcmcnprobe.
		 */
E 11
		else {
			(void) dcminit(kgdb_dev, kgdb_rate);
			if (kgdb_debug_init) {
D 11
				printf("dcm%d: kgdb waiting...",
				       UNIT(kgdb_dev));
				/* trap into kgdb */
				asm("trap #15;");
				printf("connected.\n");
E 11
I 11
				printf("dcm%d: ", UNIT(kgdb_dev));
				kgdb_connect(1);
E 11
			} else
D 11
				printf("dcm%d: kgdb enabled\n",
				       UNIT(kgdb_dev));
E 11
I 11
				printf("dcm%d: kgdb enabled\n", UNIT(kgdb_dev));
E 11
		}
I 11
		/* end could be replaced */
I 12
#endif
E 12
E 11
	}
#endif
	if (dcmistype == DIS_TIMER)
		dcmsetischeme(brd, DIS_RESET|DIS_TIMER);
	else
		dcmsetischeme(brd, DIS_RESET|DIS_PERCHAR);
D 7
	dcm->dcm_mdmmsk = MI_CD;	/* enable modem carrier detect intr */
E 7
I 7
D 9
	dcm->dcm_mdmmsk = MI_CD|MI_CTS;	/* DCD (modem) and CTS (flow ctrl) */
E 9
I 9

	/* load pointers to modem control */
	dcm_modem[MKUNIT(brd, 0)] = &dcm->dcm_modem0;
	dcm_modem[MKUNIT(brd, 1)] = &dcm->dcm_modem1;
	dcm_modem[MKUNIT(brd, 2)] = &dcm->dcm_modem2;
	dcm_modem[MKUNIT(brd, 3)] = &dcm->dcm_modem3;
	/* set DCD (modem) and CTS (flow control) on all ports */
I 14
	if (dcmsoftCAR[brd] & FLAG_STDDCE)
		mbits = hp2dce_in(MI_CD|MI_CTS);
	else
		mbits = MI_CD|MI_CTS;
E 14
	for (i = 0; i < 4; i++)
D 14
		dcm_modem[MKUNIT(brd, i)]->mdmmsk = MI_CD|MI_CTS;
E 14
I 14
		dcm_modem[MKUNIT(brd, i)]->mdmmsk = mbits;
E 14

E 9
E 7
	dcm->dcm_ic = IC_IE;		/* turn all interrupts on */
E 2
	/*
	 * Need to reset baud rate, etc. of next print so reset dcmconsole.
	 * Also make sure console is always "hardwired"
	 */
D 2
	if (brd == BOARD(dcmconsole)) {
		dcmsoftCAR[brd] |= (1 << PORT(dcmconsole));
E 2
I 2
	if (isconsole) {
E 2
D 11
		dcmconsole = -1;
E 11
I 11
		dcmconsinit = 0;
E 11
I 2
		dcmsoftCAR[brd] |= (1 << PORT(dcmconsole));
E 2
	}
	return (1);
}

D 11
dcmopen(dev, flag)
E 11
I 11
/* ARGSUSED */
#ifdef __STDC__
dcmopen(dev_t dev, int flag, int mode, struct proc *p)
#else
dcmopen(dev, flag, mode, p)
E 11
	dev_t dev;
I 11
	int flag, mode;
	struct proc *p;
#endif
E 11
{
	register struct tty *tp;
	register int unit, brd;
I 2
D 8
	int error;
E 8
I 8
D 14
	int error = 0;
E 14
I 14
	int error = 0, mbits;
E 14
E 8
E 2

	unit = UNIT(dev);
	brd = BOARD(unit);
D 2
	dcmbang[brd] = time.tv_sec;	/* for interrupt scheme */
	if (unit >= dcm_cnt || (dcm_active & (1 << brd)) == 0)
E 2
I 2
	if (unit >= NDCMLINE || (dcm_active & (1 << brd)) == 0)
E 2
		return (ENXIO);
I 2
D 11
#ifdef KGDB
	if (unit == UNIT(kgdb_dev))
		return (EBUSY);
#endif
E 11
E 2
	tp = &dcm_tty[unit];
	tp->t_oproc = dcmstart;
D 2
	tp->t_param = dcaparam;
E 2
I 2
	tp->t_param = dcmparam;
E 2
	tp->t_dev = dev;
	if ((tp->t_state & TS_ISOPEN) == 0) {
I 4
		tp->t_state |= TS_WOPEN;
E 4
		ttychars(tp);
D 11
		tp->t_iflag = TTYDEF_IFLAG;
		tp->t_oflag = TTYDEF_OFLAG;
		tp->t_cflag = TTYDEF_CFLAG;
		tp->t_lflag = TTYDEF_LFLAG;
		tp->t_ispeed = tp->t_ospeed = TTYDEF_SPEED;
E 11
I 11
		if (tp->t_ispeed == 0) {
			tp->t_iflag = TTYDEF_IFLAG;
			tp->t_oflag = TTYDEF_OFLAG;
			tp->t_cflag = TTYDEF_CFLAG;
			tp->t_lflag = TTYDEF_LFLAG;
			tp->t_ispeed = tp->t_ospeed = TTYDEF_SPEED;
		}
E 11
D 2
		dcmparam(tp, &tp->t_termios);
E 2
I 2
		(void) dcmparam(tp, &tp->t_termios);
E 2
		ttsetwater(tp);
D 11
	} else if (tp->t_state&TS_XCLUDE && u.u_uid != 0)
E 11
I 11
	} else if (tp->t_state&TS_XCLUDE && p->p_ucred->cr_uid != 0)
E 11
		return (EBUSY);
D 9
	if (PORT(unit) == 0)	/* enable port 0 */
		(void) dcmmctl(dev, MO_ON, DMSET);
E 9
I 9
D 14
	(void) dcmmctl(dev, MO_ON, DMSET);	/* enable port */
E 14
I 14
	mbits = MO_ON;
	if (dcmsoftCAR[brd] & FLAG_STDDCE)
		mbits |= MO_SR;		/* pin 23, could be used as RTS */
	(void) dcmmctl(dev, mbits, DMSET);	/* enable port */
E 14
E 9
D 11
	if (dcmsoftCAR[brd] & (1 << PORT(unit)))
E 11
I 11
	if ((dcmsoftCAR[brd] & (1 << PORT(unit))) ||
	    (dcmmctl(dev, MO_OFF, DMGET) & MI_CD))
E 11
		tp->t_state |= TS_CARR_ON;
D 9
	else if (PORT(unit))		/* Only port 0 has modem control */
		tp->t_state |= TS_CARR_ON;
E 9
D 11
	else if (dcmmctl(dev, MO_OFF, DMGET) & MI_CD)
		tp->t_state |= TS_CARR_ON;
E 11
I 9
#ifdef DEBUG
	if (dcmdebug & DDB_MODEM)
		printf("dcm%d: dcmopen port %d softcarr %c\n",
		       brd, unit, (tp->t_state & TS_CARR_ON) ? '1' : '0');
#endif
E 9
	(void) spltty();
D 6
	while (!(flag&O_NONBLOCK) && !(tp->t_cflag&CLOCAL) &&
E 6
I 6
	while ((flag&O_NONBLOCK) == 0 && (tp->t_cflag&CLOCAL) == 0 &&
E 6
D 14
	       (tp->t_state & TS_CARR_ON) == 0) {
E 14
I 14
	    (tp->t_state & TS_CARR_ON) == 0) {
E 14
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
D 6
		if ((error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
				   ttopen, 0)) ||
		    (error = ttclosed(tp))) {
E 3
			tp->t_state &= ~TS_WOPEN;
			(void) spl0();
			return (error);
		}
E 6
I 6
		if (error = ttysleep(tp, (caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
		    ttopen, 0))
			break;
E 6
E 2
	}
	(void) spl0();
I 9

E 9
D 6

E 6
#ifdef DEBUG
	if (dcmdebug & DDB_OPENCLOSE)
		printf("dcmopen: u %x st %x fl %x\n",
			unit, tp->t_state, tp->t_flags);
#endif
D 6
	return ((*linesw[tp->t_line].l_open)(dev, tp));
E 6
I 6
	if (error == 0)
		error = (*linesw[tp->t_line].l_open)(dev, tp);
	return (error);
E 6
}
 
/*ARGSUSED*/
D 13
dcmclose(dev, flag)
E 13
I 13
dcmclose(dev, flag, mode, p)
E 13
	dev_t dev;
I 13
	int flag, mode;
	struct proc *p;
E 13
{
	register struct tty *tp;
	int unit;
 
	unit = UNIT(dev);
	tp = &dcm_tty[unit];
D 13
	(*linesw[tp->t_line].l_close)(tp);
E 13
I 13
	(*linesw[tp->t_line].l_close)(tp, flag);
E 13
D 11
	if (tp->t_cflag&HUPCL || tp->t_state&TS_WOPEN || 
	    (tp->t_state&TS_ISOPEN) == 0)
		(void) dcmmctl(dev, MO_OFF, DMSET);
E 11
I 11
D 14
#ifdef KGDB
	if (dev != kgdb_dev)
#endif
	(void) dcmmctl(dev, MO_OFF, DMSET);
	if (tp->t_state & TS_HUPCLS)
		(*linesw[tp->t_line].l_modem)(tp, 0);
E 14
I 14
	if (tp->t_cflag&HUPCL || tp->t_state&TS_WOPEN ||
	    (tp->t_state&TS_ISOPEN) == 0)
		(void) dcmmctl(dev, MO_OFF, DMSET);
E 14
E 11
#ifdef DEBUG
	if (dcmdebug & DDB_OPENCLOSE)
		printf("dcmclose: u %x st %x fl %x\n",
			unit, tp->t_state, tp->t_flags);
#endif
	ttyclose(tp);
D 14
	return(0);
E 14
I 14
	return (0);
E 14
}
 
dcmread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
I 24
	int flag;
E 24
{
	register struct tty *tp;
 
	tp = &dcm_tty[UNIT(dev)];
	return ((*linesw[tp->t_line].l_read)(tp, uio, flag));
}
 
dcmwrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
I 24
	int flag;
E 24
{
	int unit = UNIT(dev);
	register struct tty *tp;
 
	tp = &dcm_tty[unit];
D 2
	if (unit == dcmconsole && constty &&
	    (constty->t_state&(TS_CARR_ON|TS_ISOPEN))==(TS_CARR_ON|TS_ISOPEN))
		tp = constty;
E 2
I 2
	/*
	 * XXX we disallow virtual consoles if the physical console is
	 * a serial port.  This is in case there is a display attached that
	 * is not the console.  In that situation we don't need/want the X
	 * server taking over the console.
	 */
	if (constty && unit == dcmconsole)
		constty = NULL;
E 2
	return ((*linesw[tp->t_line].l_write)(tp, uio, flag));
}
 
dcmintr(brd)
	register int brd;
{
D 2
	register struct dcmdevice *dcm;
E 2
I 2
	register struct dcmdevice *dcm = dcm_addr[brd];
	register struct dcmischeme *dis;
E 2
D 9
	int i, code, pcnd[4], mcnd, delta;
E 9
I 9
	register int unit = MKUNIT(brd, 0);
	register int code, i;
	int pcnd[4], mcode, mcnd[4];
E 9

D 2
	dcm = dcm_addr[brd];
E 2
I 2
	/*
	 * Do all guarded register accesses right off to minimize
	 * block out of hardware.
	 */
E 2
	SEM_LOCK(dcm);
	if ((dcm->dcm_ic & IC_IR) == 0) {
		SEM_UNLOCK(dcm);
D 14
		return(0);
E 14
I 14
		return (0);
E 14
	}
	for (i = 0; i < 4; i++) {
		pcnd[i] = dcm->dcm_icrtab[i].dcm_data;
		dcm->dcm_icrtab[i].dcm_data = 0;
I 9
D 14
		mcnd[i] = dcm_modem[unit+i]->mdmin;
E 14
I 14
		code = dcm_modem[unit+i]->mdmin;
		if (dcmsoftCAR[brd] & FLAG_STDDCE)
			code = hp2dce_in(code);
		mcnd[i] = code;
E 14
E 9
	}
D 9
	mcnd = dcm->dcm_mdmin;
E 9
	code = dcm->dcm_iir & IIR_MASK;
D 2
	dcm->dcm_iir = 0;
E 2
I 2
	dcm->dcm_iir = 0;	/* XXX doc claims read clears interrupt?! */
I 9
	mcode = dcm->dcm_modemintr;
	dcm->dcm_modemintr = 0;
E 9
E 2
	SEM_UNLOCK(dcm);

#ifdef DEBUG
D 9
	if (dcmdebug & DDB_INTR)
D 2
		printf("dcmintr: iir %x p0 %x p1 %x p2 %x p3 %x m %x\n", 
			code, pcnd[0], pcnd[1], pcnd[2], 
			pcnd[3], mcnd);
E 2
I 2
		printf("dcmintr(%d): iir %x p0 %x p1 %x p2 %x p3 %x m %x\n", 
		       brd, code, pcnd[0], pcnd[1], pcnd[2], pcnd[3], mcnd);
E 9
I 9
	if (dcmdebug & DDB_INTR) {
		printf("dcmintr(%d): iir %x pc %x/%x/%x/%x ",
		       brd, code, pcnd[0], pcnd[1], pcnd[2], pcnd[3]); 
		printf("miir %x mc %x/%x/%x/%x\n",
		       mcode, mcnd[0], mcnd[1], mcnd[2], mcnd[3]);
	}
E 9
E 2
#endif
I 2
	if (code & IIR_TIMEO)
		dcmrint(brd, dcm);
E 2
	if (code & IIR_PORT0)
D 9
		dcmpint(MKUNIT(brd, 0), pcnd[0], dcm);
E 9
I 9
		dcmpint(unit+0, pcnd[0], dcm);
E 9
	if (code & IIR_PORT1)
D 9
		dcmpint(MKUNIT(brd, 1), pcnd[1],  dcm);
E 9
I 9
		dcmpint(unit+1, pcnd[1], dcm);
E 9
	if (code & IIR_PORT2)
D 9
		dcmpint(MKUNIT(brd, 2), pcnd[2], dcm);
E 9
I 9
		dcmpint(unit+2, pcnd[2], dcm);
E 9
	if (code & IIR_PORT3)
D 9
		dcmpint(MKUNIT(brd, 3), pcnd[3], dcm);
	if (code & IIR_MODM)
D 7
		dcmmint(MKUNIT(brd, 0), mcnd, dcm);	/* always port 0 */
E 7
I 7
		dcmmint(MKUNIT(brd, 0), mcnd, dcm);	/* XXX always port 0 */
E 9
I 9
		dcmpint(unit+3, pcnd[3], dcm);
	if (code & IIR_MODM) {
		if (mcode == 0 || mcode & 0x1)	/* mcode==0 -> 98642 board */
			dcmmint(unit+0, mcnd[0], dcm);
		if (mcode & 0x2)
			dcmmint(unit+1, mcnd[1], dcm);
		if (mcode & 0x4)
			dcmmint(unit+2, mcnd[2], dcm);
		if (mcode & 0x8)
			dcmmint(unit+3, mcnd[3], dcm);
	}
E 9
E 7
D 2
	if (code & IIR_TIMEO)
		dcmrint(brd, dcm);
E 2

I 2
	dis = &dcmischeme[brd];
E 2
	/*
D 2
	 * See if need to change interrupt rate.
	 * 16.7ms is the polling interrupt rate.
	 * Reference: 16.7ms is about 550 buad; 38.4k is 72 chars in 16.7ms
E 2
I 2
	 * Chalk up a receiver interrupt if the timer running or one of
	 * the ports reports a special character interrupt.
E 2
	 */
D 2
	if ((delta = time.tv_sec - dcmbang[brd]) >= dcmintrval) {  
		dcmbang[brd] = time.tv_sec;
E 2
I 2
	if ((code & IIR_TIMEO) ||
	    ((pcnd[0]|pcnd[1]|pcnd[2]|pcnd[3]) & IT_SPEC))
		dis->dis_intr++;
	/*
	 * See if it is time to check/change the interrupt rate.
	 */
	if (dcmistype < 0 &&
D 9
	    (delta = time.tv_sec - dis->dis_time) >= dcminterval) {
E 9
I 9
	    (i = time.tv_sec - dis->dis_time) >= dcminterval) {
E 9
E 2
		/*
D 2
		 * 66 threshold of 600 buad, use 70
E 2
I 2
		 * If currently per-character and averaged over 70 interrupts
		 * per-second (66 is threshold of 600 baud) in last interval,
		 * switch to timer mode.
		 *
		 * XXX decay counts ala load average to avoid spikes?
E 2
		 */
D 2
		if (dcmintschm[brd] && dcmintrocc[brd] > 70 * delta)
			dcm_setintrschm(dcm, 0, brd);
		else if (!dcmintschm[brd] && dcmintrocc[brd] > dcmchrrd[brd]) {
			dcm_setintrschm(dcm, 1, brd);
			/*
			 * Must check the receive queue after switch
			 * from polling mode to interrupt/char
			 */
E 2
I 2
D 9
		if (dis->dis_perchar && dis->dis_intr > 70 * delta)
E 9
I 9
		if (dis->dis_perchar && dis->dis_intr > 70 * i)
E 9
			dcmsetischeme(brd, DIS_TIMER);
		/*
		 * If currently using timer and had more interrupts than
		 * received characters in the last interval, switch back
		 * to per-character.  Note that after changing to per-char
		 * we must process any characters already in the queue
		 * since they may have arrived before the bitmap was setup.
		 *
		 * XXX decay counts?
		 */
		else if (!dis->dis_perchar && dis->dis_intr > dis->dis_char) {
			dcmsetischeme(brd, DIS_PERCHAR);
E 2
			dcmrint(brd, dcm);
		}
D 2
		dcmintrocc[brd] = 0;
		dcmchrrd[brd] = 0;
	} else
		dcmintrocc[brd]++;

E 2
I 2
		dis->dis_intr = dis->dis_char = 0;
		dis->dis_time = time.tv_sec;
	}
E 2
D 14
	return(1);
E 14
I 14
	return (1);
E 14
}

/*
 *  Port interrupt.  Can be two things:
 *	First, it might be a special character (exception interrupt);
 *	Second, it may be a buffer empty (transmit interrupt);
 */
dcmpint(unit, code, dcm)
	int unit, code;
D 2
	register struct dcmdevice *dcm;
E 2
I 2
	struct dcmdevice *dcm;
E 2
{
D 2
	register struct tty *tp;
	register int port = PORT(unit);
E 2
I 2
	struct tty *tp = &dcm_tty[unit];
E 2

D 2
	if (code & IT_SPEC) {
		tp = &dcm_tty[unit];
		if ((tp->t_state & TS_ISOPEN) != 0)
			dcmreadbuf(unit, dcm, tp, port);
		else
			dcm->dcm_rhead[port].ptr = dcm->dcm_rtail[port].ptr & RX_MASK;
	}
E 2
I 2
	if (code & IT_SPEC)
		dcmreadbuf(unit, dcm, tp);
E 2
	if (code & IT_TX)
D 2
		dcmxint(unit, dcm);
E 2
I 2
		dcmxint(unit, dcm, tp);
E 2
}

dcmrint(brd, dcm)
	int brd;
	register struct dcmdevice *dcm;
{
D 2
	register struct tty *tp;
E 2
	register int i, unit;
I 2
	register struct tty *tp;
E 2

	unit = MKUNIT(brd, 0);
	tp = &dcm_tty[unit];
D 2
	for (i = 0; i < 4; i++, tp++, unit++) {
		/* TS_WOPEN catch race when switching to polling mode */
		if ((tp->t_state & (TS_ISOPEN|TS_WOPEN)) != 0)
			dcmreadbuf(unit, dcm, tp, i);
		else
			dcm->dcm_rhead[i].ptr = dcm->dcm_rtail[i].ptr & RX_MASK;
	}
E 2
I 2
	for (i = 0; i < 4; i++, tp++, unit++)
		dcmreadbuf(unit, dcm, tp);
E 2
}

D 2
dcmreadbuf(unit, dcm, tp, port)
E 2
I 2
dcmreadbuf(unit, dcm, tp)
E 2
	int unit;
	register struct dcmdevice *dcm;
	register struct tty *tp;
D 2
	register int port;
E 2
{
I 2
	int port = PORT(unit);
	register struct dcmpreg *pp = dcm_preg(dcm, port);
	register struct dcmrfifo *fifo;
E 2
	register int c, stat;
	register unsigned head;
D 2
	unsigned tail;
#ifdef DEBUG
	int silocnt;
	silocnt = 0;
#endif /* DEBUG */
E 2
I 2
	int nch = 0;
D 21
#ifdef IOSTATS
E 21
I 21
#ifdef DCMSTATS
E 21
	struct dcmstats *dsp = &dcmstats[BOARD(unit)];
E 2

D 2
readrestart:
	head = dcm->dcm_rhead[port].ptr & RX_MASK;
	tail = dcm->dcm_rtail[port].ptr & RX_MASK;

	while (head != tail) {
		c = dcm->dcm_rfifos[3 - port][head / 2].data_char;
		stat = dcm->dcm_rfifos[3 - port][head / 2].data_stat;
		dcmchrrd[BOARD(unit)]++;
#ifdef DEBUG
		silocnt++;
E 2
I 2
	dsp->rints++;
#endif
D 5
	/*
	 * TS_WOPEN catches a race when switching to polling mode from dcmrint
	 */
	if ((tp->t_state & (TS_ISOPEN|TS_WOPEN)) == 0) {
E 5
I 5
	if ((tp->t_state & TS_ISOPEN) == 0) {
E 5
#ifdef KGDB
D 11
		if (unit == UNIT(kgdb_dev) &&
E 11
I 11
		if ((makedev(dcmmajor, unit) == kgdb_dev) &&
E 11
		    (head = pp->r_head & RX_MASK) != (pp->r_tail & RX_MASK) &&
D 11
		    dcm->dcm_rfifos[3-port][head>>1].data_char == '!') {
E 11
I 11
D 19
		    dcm->dcm_rfifos[3-port][head>>1].data_char == FRAME_END) {
E 19
I 19
		    dcm->dcm_rfifos[3-port][head>>1].data_char == FRAME_START) {
E 19
E 11
			pp->r_head = (head + 2) & RX_MASK;
D 11
			printf("kgdb trap from dcm%d\n", unit);
			/* trap into kgdb */
			asm("trap #15;");
E 11
I 11
			kgdb_connect(0);	/* trap into kgdb */
E 11
			return;
		}
E 2
D 11
#endif
E 11
I 11
#endif /* KGDB */
E 11
I 2
		pp->r_head = pp->r_tail & RX_MASK;
		return;
	}

	head = pp->r_head & RX_MASK;
	fifo = &dcm->dcm_rfifos[3-port][head>>1];
	/*
	 * XXX upper bound on how many chars we will take in one swallow?
	 */
	while (head != (pp->r_tail & RX_MASK)) {
		/*
		 * Get character/status and update head pointer as fast
		 * as possible to make room for more characters.
		 */
		c = fifo->data_char;
		stat = fifo->data_stat;
E 2
		head = (head + 2) & RX_MASK;
D 2
		dcm->dcm_rhead[port].ptr = head;
E 2
I 2
		pp->r_head = head;
		fifo = head ? fifo+1 : &dcm->dcm_rfifos[3-port][0];
		nch++;
E 2

#ifdef DEBUG
		if (dcmdebug & DDB_INPUT)
D 2
			printf("dcmreadbuf: u%d p%d c%x s%x f%x h%x t%x char %c\n",
			       BOARD(unit), PORT(unit), c&0xFF, stat&0xFF,
			       tp->t_flags, head, tail, c);
E 2
I 2
			printf("dcmreadbuf(%d): c%x('%c') s%x f%x h%x t%x\n",
			       unit, c&0xFF, c, stat&0xFF,
			       tp->t_flags, head, pp->r_tail);
E 2
#endif
D 2
		if (stat & RD_MASK) {	/* Check for errors */
E 2
I 2
		/*
		 * Check for and handle errors
		 */
		if (stat & RD_MASK) {
E 2
#ifdef DEBUG
D 2
			if (dcmdebug & DDB_INPUT || dcmdebug & DDB_SIOERR)
				printf("dcm%d port%d: data error: stat 0x%x data 0x%x chr %c\n",
				       BOARD(unit), PORT(unit), stat, c, c);
E 2
I 2
			if (dcmdebug & (DDB_INPUT|DDB_SIOERR))
				printf("dcmreadbuf(%d): err: c%x('%c') s%x\n",
				       unit, stat, c&0xFF, c);
E 2
#endif
			if (stat & (RD_BD | RD_FE))
				c |= TTY_FE;
			else if (stat & RD_PE)
				c |= TTY_PE;
			else if (stat & RD_OVF)
				log(LOG_WARNING,
D 2
				    "dcm%d port%d: silo overflow\n",
				    BOARD(unit), PORT(unit));
E 2
I 2
				    "dcm%d: silo overflow\n", unit);
E 2
			else if (stat & RD_OE)
				log(LOG_WARNING,
D 2
				    "dcm%d port%d: uart overflow\n",
				    BOARD(unit), PORT(unit));
E 2
I 2
				    "dcm%d: uart overflow\n", unit);
E 2
		}
		(*linesw[tp->t_line].l_rint)(c, tp);
	}
D 2
	/* for higher speed need to processes everything that might
	 * have arrived since we started; see if tail changed */
	if (tail != dcm->dcm_rtail[port].ptr & RX_MASK)
		goto readrestart;

#ifdef DEBUG
	if (silocnt < 33)
		dcmrsize[silocnt]++;
E 2
I 2
	dcmischeme[BOARD(unit)].dis_char += nch;
D 21
#ifdef IOSTATS
E 21
I 21
#ifdef DCMSTATS
E 21
	dsp->rchars += nch;
	if (nch <= DCMRBSIZE)
		dsp->rsilo[nch]++;
E 2
	else
D 2
		dcmrsize[32]++;
E 2
I 2
		dsp->rsilo[DCMRBSIZE+1]++;
E 2
#endif
}

D 2
dcmxint(unit, dcm)
E 2
I 2
dcmxint(unit, dcm, tp)
E 2
	int unit;
	struct dcmdevice *dcm;
D 2
{
E 2
	register struct tty *tp;
D 2

	tp = &dcm_tty[unit];
E 2
I 2
{
E 2
	tp->t_state &= ~TS_BUSY;
	if (tp->t_state & TS_FLUSH)
		tp->t_state &= ~TS_FLUSH;
D 11
	if (tp->t_line)
		(*linesw[tp->t_line].l_start)(tp);
	else
		dcmstart(tp);
E 11
I 11
	(*linesw[tp->t_line].l_start)(tp);
E 11
}

dcmmint(unit, mcnd, dcm)
	register int unit;
	register struct dcmdevice *dcm;
        int mcnd;
{
	register struct tty *tp;
I 7
	int delta;
E 7

#ifdef DEBUG
D 2
	if (dcmdebug & DDB_MOD)
E 2
I 2
	if (dcmdebug & DDB_MODEM)
E 2
D 7
		printf("dcmmint: unit %x mcnd %x\n", unit, mcnd);
E 7
I 7
D 9
		printf("dcmmint: unit %x mcnd %x mcndlast\n",
E 9
I 9
		printf("dcmmint: port %d mcnd %x mcndlast %x\n",
E 9
		       unit, mcnd, mcndlast[unit]);
E 7
D 2
#endif DEBUG
E 2
I 2
#endif
E 2
	tp = &dcm_tty[unit];
D 7
	if ((dcmsoftCAR[BOARD(unit)] & (1 << PORT(unit))) == 0) {
E 7
I 7
	delta = mcnd ^ mcndlast[unit];
	mcndlast[unit] = mcnd;
I 11
	if ((delta & MI_CTS) && (tp->t_state & TS_ISOPEN) &&
D 14
	    (tp->t_flags & CRTSCTS)) {
E 14
I 14
	    (tp->t_flags & CCTS_OFLOW)) {
E 14
		if (mcnd & MI_CTS) {
			tp->t_state &= ~TS_TTSTOP;
			ttstart(tp);
		} else
			tp->t_state |= TS_TTSTOP;	/* inline dcmstop */
	}
E 11
D 14
	if ((delta & MI_CD) &&
	    (dcmsoftCAR[BOARD(unit)] & (1 << PORT(unit))) == 0) {
E 14
I 14
	if (delta & MI_CD) {
E 14
E 7
		if (mcnd & MI_CD)
D 7
			(void) (*linesw[tp->t_line].l_modem)(tp, 1);
E 7
I 7
			(void)(*linesw[tp->t_line].l_modem)(tp, 1);
E 7
D 14
		else if ((*linesw[tp->t_line].l_modem)(tp, 0) == 0) {
D 7
			dcm->dcm_mdmout &= ~(MO_DTR | MO_RTS);
E 7
I 7
D 9
			dcm->dcm_mdmout &= ~(MO_DTR|MO_RTS);
E 9
I 9
			dcm_modem[unit]->mdmout &= ~(MO_DTR|MO_RTS);
E 14
I 14
		else if ((dcmsoftCAR[BOARD(unit)] & (1 << PORT(unit))) == 0 &&
		    (*linesw[tp->t_line].l_modem)(tp, 0) == 0) {
			dcm_modem[unit]->mdmout = MO_OFF;
E 14
E 9
E 7
			SEM_LOCK(dcm);
I 9
			dcm->dcm_modemchng |= 1<<(unit & 3);
E 9
			dcm->dcm_cr |= CR_MODM;
			SEM_UNLOCK(dcm);
I 2
			DELAY(10); /* time to change lines */
E 2
		}
I 7
D 11
	} else if ((delta & MI_CTS) &&
		   (tp->t_state & TS_ISOPEN) && (tp->t_flags & CRTSCTS)) {
		if (mcnd & MI_CTS) {
			tp->t_state &= ~TS_TTSTOP;
			ttstart(tp);
		} else
			tp->t_state |= TS_TTSTOP;	/* inline dcmstop */
E 11
E 7
	}
}

D 16
dcmioctl(dev, cmd, data, flag)
E 16
I 16
dcmioctl(dev, cmd, data, flag, p)
E 16
	dev_t dev;
I 16
D 26
	int cmd;
E 26
I 26
	u_long cmd;
E 26
E 16
	caddr_t data;
I 16
	int flag;
	struct proc *p;
E 16
{
	register struct tty *tp;
	register int unit = UNIT(dev);
	register struct dcmdevice *dcm;
	register int port;
D 2
	int error;
E 2
I 2
	int error, s;
E 2
 
#ifdef DEBUG
	if (dcmdebug & DDB_IOCTL)
		printf("dcmioctl: unit %d cmd %x data %x flag %x\n",
		       unit, cmd, *data, flag);
#endif
	tp = &dcm_tty[unit];
D 16
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
E 16
I 16
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag, p);
E 16
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, data, flag);
	if (error >= 0)
		return (error);

	port = PORT(unit);
	dcm = dcm_addr[BOARD(unit)];
	switch (cmd) {
	case TIOCSBRK:
D 2
		dcm->dcm_cmdtab[port].dcm_data = CT_BRK;
E 2
I 2
		/*
		 * Wait for transmitter buffer to empty
		 */
		s = spltty();
		while (dcm->dcm_thead[port].ptr != dcm->dcm_ttail[port].ptr)
			DELAY(DCM_USPERCH(tp->t_ospeed));
E 2
		SEM_LOCK(dcm);
D 2
		dcm->dcm_cr = (1 << port);	/* start break */
E 2
I 2
		dcm->dcm_cmdtab[port].dcm_data |= CT_BRK;
		dcm->dcm_cr |= (1 << port);	/* start break */
E 2
		SEM_UNLOCK(dcm);
I 2
		splx(s);
E 2
		break;

	case TIOCCBRK:
D 2
		dcm->dcm_cmdtab[port].dcm_data = CT_BRK;
E 2
		SEM_LOCK(dcm);
D 2
		dcm->dcm_cr = (1 << port);	/* end break */
E 2
I 2
		dcm->dcm_cmdtab[port].dcm_data |= CT_BRK;
		dcm->dcm_cr |= (1 << port);	/* end break */
E 2
		SEM_UNLOCK(dcm);
		break;

	case TIOCSDTR:
		(void) dcmmctl(dev, MO_ON, DMBIS);
		break;

	case TIOCCDTR:
		(void) dcmmctl(dev, MO_ON, DMBIC);
		break;

	case TIOCMSET:
		(void) dcmmctl(dev, *(int *)data, DMSET);
		break;

	case TIOCMBIS:
		(void) dcmmctl(dev, *(int *)data, DMBIS);
		break;

	case TIOCMBIC:
		(void) dcmmctl(dev, *(int *)data, DMBIC);
		break;

	case TIOCMGET:
		*(int *)data = dcmmctl(dev, 0, DMGET);
		break;

	default:
		return (ENOTTY);
	}
	return (0);
}

dcmparam(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	register struct dcmdevice *dcm;
D 2
	register int mode, cflag = t->c_cflag;
	register int port;
	int unit = UNIT(tp->t_dev);
E 2
I 2
	register int port, mode, cflag = t->c_cflag;
E 2
	int ospeed = ttspeedtab(t->c_ospeed, dcmspeedtab);
D 2
 
E 2
I 2

E 2
	/* check requested parameters */
        if (ospeed < 0 || (t->c_ispeed && t->c_ispeed != t->c_ospeed))
D 14
                return(EINVAL);
E 14
I 14
                return (EINVAL);
E 14
        /* and copy to tty */
        tp->t_ispeed = t->c_ispeed;
        tp->t_ospeed = t->c_ospeed;
        tp->t_cflag = cflag;
D 2

	dcm = dcm_addr[BOARD(unit)];
E 2
	if (ospeed == 0) {
D 2
		(void) dcmmctl(unit, MO_OFF, DMSET);	/* hang up line */
		return;
E 2
I 2
		(void) dcmmctl(UNIT(tp->t_dev), MO_OFF, DMSET);
D 14
		return(0);
E 14
I 14
		return (0);
E 14
E 2
	}
D 2
	port = PORT(unit);
	dcm->dcm_data[port].dcm_baud = ospeed;
E 2
I 2

	mode = 0;
E 2
	switch (cflag&CSIZE) {
	case CS5:
		mode = LC_5BITS; break;
	case CS6:
		mode = LC_6BITS; break;
	case CS7:
		mode = LC_7BITS; break;
	case CS8:
		mode = LC_8BITS; break;
	}
	if (cflag&PARENB) {
		if (cflag&PARODD)
			mode |= LC_PODD;
		else
			mode |= LC_PEVEN;
	}
	if (cflag&CSTOPB)
		mode |= LC_2STOP;
	else
		mode |= LC_1STOP;
#ifdef DEBUG
	if (dcmdebug & DDB_PARAM)
D 2
		printf("dcmparam: unit %d cflag %x mode %x speed %x\n",
		       unit, cflag, mode, ospeed);
E 2
I 2
		printf("dcmparam(%d): cflag %x mode %x speed %d uperch %d\n",
		       UNIT(tp->t_dev), cflag, mode, tp->t_ospeed,
		       DCM_USPERCH(tp->t_ospeed));
E 2
#endif
D 2
	/* wait for transmitter buffer to empty */
	while (dcm->dcm_thead[port].ptr != dcm->dcm_ttail[port].ptr)
		;
E 2

I 2
	port = PORT(tp->t_dev);
	dcm = dcm_addr[BOARD(tp->t_dev)];
	/*
	 * Wait for transmitter buffer to empty.
	 */
	while (dcm->dcm_thead[port].ptr != dcm->dcm_ttail[port].ptr)
		DELAY(DCM_USPERCH(tp->t_ospeed));
	/*
	 * Make changes known to hardware.
	 */
	dcm->dcm_data[port].dcm_baud = ospeed;
E 2
	dcm->dcm_data[port].dcm_conf = mode;
D 2
	dcm->dcm_cmdtab[port].dcm_data = CT_CON;
E 2
	SEM_LOCK(dcm);
D 2
	dcm->dcm_cr = (1 << port);
E 2
I 2
	dcm->dcm_cmdtab[port].dcm_data |= CT_CON;
	dcm->dcm_cr |= (1 << port);
E 2
	SEM_UNLOCK(dcm);
I 2
	/*
D 11
	 * Delay for config change to take place. Weighted by buad.
E 11
I 11
	 * Delay for config change to take place. Weighted by baud.
E 11
	 * XXX why do we do this?
	 */
	DELAY(16 * DCM_USPERCH(tp->t_ospeed));
D 14
	return(0);
E 14
I 14
	return (0);
E 14
E 2
}
 
I 15
void
E 15
dcmstart(tp)
	register struct tty *tp;
{
	register struct dcmdevice *dcm;
D 2
	int s, unit, c;
	register int tail, next, head, port;
	int restart = 0, nch = 0;
 
	unit = UNIT(tp->t_dev);
	port = PORT(unit);
	dcm = dcm_addr[BOARD(unit)];
E 2
I 2
	register struct dcmpreg *pp;
	register struct dcmtfifo *fifo;
	register char *bp;
	register unsigned tail, next;
	register int port, nch;
	unsigned head;
	char buf[16];
	int s;
D 21
#ifdef IOSTATS
E 21
I 21
#ifdef DCMSTATS
E 21
	struct dcmstats *dsp = &dcmstats[BOARD(tp->t_dev)];
	int tch = 0;
#endif

E 2
	s = spltty();
I 2
D 21
#ifdef IOSTATS
E 21
I 21
#ifdef DCMSTATS
E 21
	dsp->xints++;
#endif
E 2
#ifdef DEBUG
	if (dcmdebug & DDB_OUTPUT)
D 2
		printf("dcmstart: unit %d state %x flags %x outcc %d\n",
		       unit, tp->t_state, tp->t_flags, tp->t_outq.c_cc);
E 2
I 2
		printf("dcmstart(%d): state %x flags %x outcc %d\n",
		       UNIT(tp->t_dev), tp->t_state, tp->t_flags,
		       tp->t_outq.c_cc);
E 2
#endif
	if (tp->t_state & (TS_TIMEOUT|TS_BUSY|TS_TTSTOP))
		goto out;
	if (tp->t_outq.c_cc <= tp->t_lowat) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
D 17
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
E 17
I 17
		selwakeup(&tp->t_wsel);
E 17
	}
D 2
	tail = dcm->dcm_ttail[port].ptr & TX_MASK;
	next = (dcm->dcm_ttail[port].ptr + 1) & TX_MASK;
	head = dcm->dcm_thead[port].ptr & TX_MASK;
E 2
I 2
	if (tp->t_outq.c_cc == 0) {
D 21
#ifdef IOSTATS
E 21
I 21
#ifdef DCMSTATS
E 21
		dsp->xempty++;
#endif
		goto out;
	}

	dcm = dcm_addr[BOARD(tp->t_dev)];
	port = PORT(tp->t_dev);
	pp = dcm_preg(dcm, port);
	tail = pp->t_tail & TX_MASK;
	next = (tail + 1) & TX_MASK;
	head = pp->t_head & TX_MASK;
	if (head == next)
		goto out;
	fifo = &dcm->dcm_tfifos[3-port][tail];
again:
	nch = q_to_b(&tp->t_outq, buf, (head - next) & TX_MASK);
D 21
#ifdef IOSTATS
E 21
I 21
#ifdef DCMSTATS
E 21
	tch += nch;
#endif
E 2
#ifdef DEBUG
D 2
      if (dcmdebug & DDB_OUTPUT)
              printf("\thead %x tail %x next %x\n",
                     head, tail, next);
E 2
I 2
	if (dcmdebug & DDB_OUTPUT)
		printf("\thead %x tail %x nch %d\n", head, tail, nch);
E 2
#endif
D 2
	if (tail == head && tp->t_outq.c_cc)
		restart++;
	while (tp->t_outq.c_cc && next != head) {
		nch++;
		c = getc(&tp->t_outq);
		dcm->dcm_tfifos[3 - port][tail].data_char = c;
		dcm->dcm_ttail[port].ptr = next;
E 2
I 2
	/*
	 * Loop transmitting all the characters we can.
	 */
	for (bp = buf; --nch >= 0; bp++) {
		fifo->data_char = *bp;
		pp->t_tail = next;
		/*
		 * If this is the first character,
		 * get the hardware moving right now.
		 */
		if (bp == buf) {
			tp->t_state |= TS_BUSY;
			SEM_LOCK(dcm);
			dcm->dcm_cmdtab[port].dcm_data |= CT_TX;
			dcm->dcm_cr |= (1 << port);
			SEM_UNLOCK(dcm);
		}
E 2
		tail = next;
D 2
		next = (tail + 1) & TX_MASK;
E 2
I 2
		fifo = tail ? fifo+1 : &dcm->dcm_tfifos[3-port][0];
		next = (next + 1) & TX_MASK;
E 2
	}
D 2
	if (restart && nch) {
E 2
I 2
	/*
	 * Head changed while we were loading the buffer,
	 * go back and load some more if we can.
	 */
	if (tp->t_outq.c_cc && head != (pp->t_head & TX_MASK)) {
D 21
#ifdef IOSTATS
E 21
I 21
#ifdef DCMSTATS
E 21
		dsp->xrestarts++;
#endif
		head = pp->t_head & TX_MASK;
		goto again;
	}
I 11

E 11
	/*
	 * Kick it one last time in case it finished while we were
D 7
	 * loading the last time.
E 7
I 7
	 * loading the last bunch.
E 7
	 */
	if (bp > &buf[1]) {
E 2
		tp->t_state |= TS_BUSY;
		SEM_LOCK(dcm);
I 2
		dcm->dcm_cmdtab[port].dcm_data |= CT_TX;
		dcm->dcm_cr |= (1 << port);
		SEM_UNLOCK(dcm);
	}
E 2
#ifdef DEBUG
	if (dcmdebug & DDB_INTR)
D 2
		printf("TX on port %d head %x tail %x cc %d\n",
			port, tail, head, tp->t_outq.c_cc);
E 2
I 2
D 5
		printf("dcmstart(%d): head %x tail %x outqcc %d ch %d\n",
		       UNIT(tp->t_dev), head, tail, tp->t_outq.c_cc, tch);
E 5
I 5
		printf("dcmstart(%d): head %x tail %x outqcc %d\n",
		       UNIT(tp->t_dev), head, tail, tp->t_outq.c_cc);
E 5
E 2
#endif
D 2
		dcm->dcm_cmdtab[port].dcm_data = CT_TX;
		dcm->dcm_cr = (1 << port);
		SEM_UNLOCK(dcm);
	}
E 2
out:
I 2
D 21
#ifdef IOSTATS
E 21
I 21
#ifdef DCMSTATS
E 21
	dsp->xchars += tch;
	if (tch <= DCMXBSIZE)
		dsp->xsilo[tch]++;
	else
		dsp->xsilo[DCMXBSIZE+1]++;
#endif
E 2
	splx(s);
}
 
/*
 * Stop output on a line.
 */
dcmstop(tp, flag)
	register struct tty *tp;
I 25
	int flag;
E 25
{
	int s;

	s = spltty();
	if (tp->t_state & TS_BUSY) {
I 2
		/* XXX is there some way to safely stop transmission? */
E 2
D 7
		if ((tp->t_state&TS_TTSTOP)==0)
E 7
I 7
		if ((tp->t_state&TS_TTSTOP) == 0)
E 7
			tp->t_state |= TS_FLUSH;
	}
	splx(s);
}
 
D 9
/* Modem control */

E 9
I 9
/*
 * Modem control
 */
E 9
dcmmctl(dev, bits, how)
	dev_t dev;
	int bits, how;
{
	register struct dcmdevice *dcm;
D 9
	int s, hit = 0;
E 9
I 9
D 14
	int s, unit, hit = 0;
E 14
I 14
	int s, unit, brd, hit = 0;
E 14
E 9

D 2
	/* Only port 0 has modem control lines. For right now the following */
	/* is ok, but needs to changed for the 8 port board. */
E 2
I 2
D 9
	/*
	 * Only port 0 has modem control lines.
	 * XXX ok for now but needs to changed for the 8 port board.
	 */
E 2
	if (PORT(UNIT(dev)) != 0)
		return(bits);
E 9
I 9
	unit = UNIT(dev);
#ifdef DEBUG
	if (dcmdebug & DDB_MODEM)
		printf("dcmmctl(%d) unit %d  bits 0x%x how %x\n",
		       BOARD(unit), unit, bits, how);
#endif
E 9

D 9
	dcm = dcm_addr[BOARD(UNIT(dev))];
E 9
I 9
D 14
	dcm = dcm_addr[BOARD(unit)];
E 14
I 14
	brd = BOARD(unit);
	dcm = dcm_addr[brd];
E 14
E 9
	s = spltty();
	switch (how) {

	case DMSET:
D 9
		dcm->dcm_mdmout = bits;
E 9
I 9
		dcm_modem[unit]->mdmout = bits;
E 9
		hit++;
		break;

	case DMBIS:
D 9
		dcm->dcm_mdmout |= bits;
E 9
I 9
		dcm_modem[unit]->mdmout |= bits;
E 9
		hit++;
		break;

	case DMBIC:
D 9
		dcm->dcm_mdmout &= ~bits;
E 9
I 9
		dcm_modem[unit]->mdmout &= ~bits;
E 9
		hit++;
		break;

	case DMGET:
D 9
		bits = dcm->dcm_mdmin;
E 9
I 9
		bits = dcm_modem[unit]->mdmin;
I 14
		if (dcmsoftCAR[brd] & FLAG_STDDCE)
			bits = hp2dce_in(bits);
E 14
E 9
		break;
	}
	if (hit) {
		SEM_LOCK(dcm);
I 9
		dcm->dcm_modemchng |= 1<<(unit & 3);
E 9
		dcm->dcm_cr |= CR_MODM;
		SEM_UNLOCK(dcm);
I 2
		DELAY(10); /* delay until done */
E 2
		(void) splx(s);
	}
D 14
	return(bits);
E 14
I 14
	return (bits);
E 14
}

D 2
dcm_setintrschm(dcm, request, brd)
     register struct dcmdevice *dcm;
     int request, brd;
E 2
I 2
/*
 * Set board to either interrupt per-character or at a fixed interval.
 */
dcmsetischeme(brd, flags)
	int brd, flags;
E 2
{
I 2
	register struct dcmdevice *dcm = dcm_addr[brd];
	register struct dcmischeme *dis = &dcmischeme[brd];
E 2
	register int i;
I 2
	u_char mask;
	int perchar = flags & DIS_PERCHAR;
E 2

#ifdef DEBUG
D 2
	if (dcmdebug & DDB_INTSCHM) {
		printf("dcm%d set intr schm request %d int state %x silo hist \n\t",
		       brd, request, dcmintschm[brd]);
		for (i = 0; i < 33; i++)  {
			printf("  %u", dcmrsize[i]);
			dcmrsize[i] = 0;
		}
		printf("\n");
E 2
I 2
	if (dcmdebug & DDB_INTSCHM)
		printf("dcmsetischeme(%d, %d): cur %d, ints %d, chars %d\n",
		       brd, perchar, dis->dis_perchar,
		       dis->dis_intr, dis->dis_char);
	if ((flags & DIS_RESET) == 0 && perchar == dis->dis_perchar) {
		printf("dcmsetischeme(%d):  redundent request %d\n",
		       brd, perchar);
		return;
E 2
	}
D 2
#endif /* DEBUG */
E 2
I 2
#endif
	/*
	 * If perchar is non-zero, we enable interrupts on all characters
	 * otherwise we disable perchar interrupts and use periodic
	 * polling interrupts.
	 */
	dis->dis_perchar = perchar;
	mask = perchar ? 0xf : 0x0;
	for (i = 0; i < 256; i++)
		dcm->dcm_bmap[i].data_data = mask;
	/*
	 * Don't slow down tandem mode, interrupt on flow control
	 * chars for any port on the board.
	 */
	if (!perchar) {
		register struct tty *tp = &dcm_tty[MKUNIT(brd, 0)];
		int c;
E 2

D 2
	/* if request true then we interrupt per char, else use card */
	/* polling interrupt hardware */
#ifdef DEBUG
	if (request == dcmintschm[brd]) { 
		printf("dcm%d setintrschm redundent request %x current %x\n",
		       brd, request, dcmintschm[brd]);
		return;
E 2
I 2
		for (i = 0; i < 4; i++, tp++) {
			if ((c = tp->t_cc[VSTART]) != _POSIX_VDISABLE)
				dcm->dcm_bmap[c].data_data |= (1 << i);
			if ((c = tp->t_cc[VSTOP]) != _POSIX_VDISABLE)
				dcm->dcm_bmap[c].data_data |= (1 << i);
		}
E 2
	}
D 2
#endif /* DEBUG */
	if (request) {
		for (i = 0; i < 256; i++)
			dcm->dcm_bmap[i].data_data = 0x0f;
		dcmintschm[brd] = 1;
	}
	else {
		for (i = 0; i < 256; i++) 
			dcm->dcm_bmap[i].data_data = 0x00;
		/*
		 * Don't slow down tandem mode, interrupt on these chars.
		 * XXX bad assumption, everyone uses ^Q, ^S for flow
		 */
		dcm->dcm_bmap[0x11].data_data = 0x0f;
		dcm->dcm_bmap[0x13].data_data = 0x0f;
		dcmintschm[brd] = 0;
	}
	while (dcm->dcm_cr & CR_TIMER) ;
E 2
I 2
	/*
	 * Board starts with timer disabled so if first call is to
	 * set perchar mode then we don't want to toggle the timer.
	 */
	if (flags == (DIS_RESET|DIS_PERCHAR))
		return;
	/*
	 * Toggle card 16.7ms interrupts (we first make sure that card
	 * has cleared the bit so it will see the toggle).
	 */
	while (dcm->dcm_cr & CR_TIMER)
		;
E 2
	SEM_LOCK(dcm);
D 2
	dcm->dcm_cr |= CR_TIMER;	/* toggle card 16.7ms interrupts */
E 2
I 2
	dcm->dcm_cr |= CR_TIMER;
E 2
	SEM_UNLOCK(dcm);
}

D 2
#ifdef notdef
E 2
/*
 * Following are all routines needed for DCM to act as console
 */
I 2
D 10
#include "machine/cons.h"
E 10
I 10
D 18
#include "../hp300/cons.h"
E 18
I 18
D 20
#include "hp/dev/cons.h"
E 20
I 20
#include <hp/dev/cons.h>
E 20
E 18
E 10
E 2

D 2
struct tty *
dcmcninit(majordev)
	dev_t majordev;
E 2
I 2
dcmcnprobe(cp)
	struct consdev *cp;
E 2
{
D 2
	register struct dcmdevice *dcm;
	int unit, s;
	short stat;
E 2
I 2
	register struct hp_hw *hw;
D 11
	int unit, i;
	extern int dcmopen();
E 11
I 11
	int unit;
E 11
E 2

I 11
	/* locate the major number */
	for (dcmmajor = 0; dcmmajor < nchrdev; dcmmajor++)
		if (cdevsw[dcmmajor].d_open == dcmopen)
			break;

E 11
D 2
	unit = CONUNIT;				/* XXX */
	dcm_addr[BOARD(CONUNIT)] = CONADDR;	/* XXX */
E 2
I 2
	/*
	 * Implicitly assigns the lowest select code DCM card found to be
	 * logical unit 0 (actually CONUNIT).  If your config file does
	 * anything different, you're screwed.
	 */
	for (hw = sc_table; hw->hw_type; hw++)
D 12
	        if (hw->hw_type == COMMDCM && !badaddr((short *)hw->hw_addr))
E 12
I 12
		if (HW_ISDEV(hw, D_COMMDCM) && !badaddr((short *)hw->hw_kva))
E 12
			break;
D 12
	if (hw->hw_type != COMMDCM) {
E 12
I 12
	if (!HW_ISDEV(hw, D_COMMDCM)) {
E 12
		cp->cn_pri = CN_DEAD;
		return;
	}
	unit = CONUNIT;
D 12
	dcm_addr[BOARD(CONUNIT)] = (struct dcmdevice *)hw->hw_addr;
E 12
I 12
	dcm_addr[BOARD(CONUNIT)] = (struct dcmdevice *)hw->hw_kva;
E 12
E 2

D 2
	dcm = dcm_addr[unit];
E 2
I 2
D 11
	/* locate the major number */
	for (i = 0; i < nchrdev; i++)
		if (cdevsw[i].d_open == dcmopen)
			break;

E 11
	/* initialize required fields */
D 11
	cp->cn_dev = makedev(i, unit);
E 11
I 11
	cp->cn_dev = makedev(dcmmajor, unit);
E 11
	cp->cn_tp = &dcm_tty[unit];
	switch (dcm_addr[BOARD(unit)]->dcm_rsid) {
	case DCMID:
		cp->cn_pri = CN_NORMAL;
		break;
	case DCMID|DCMCON:
		cp->cn_pri = CN_REMOTE;
		break;
	default:
		cp->cn_pri = CN_DEAD;
D 11
		break;
E 11
I 11
		return;
E 11
	}
I 11
	/*
	 * If dcmconsole is initialized, raise our priority.
	 */
	if (dcmconsole == UNIT(unit))
		cp->cn_pri = CN_REMOTE;
D 14
#ifdef KGDB
	if (major(kgdb_dev) == 2)			/* XXX */
		kgdb_dev = makedev(dcmmajor, minor(kgdb_dev));
E 14
D 12
#ifdef notdef
E 12
I 12
#ifdef KGDB_CHEAT
E 12
	/*
	 * This doesn't currently work, at least not with ite consoles;
	 * the console hasn't been initialized yet.
	 */
	if (major(kgdb_dev) == dcmmajor && BOARD(kgdb_dev) == BOARD(unit)) {
		(void) dcminit(kgdb_dev, kgdb_rate);
		if (kgdb_debug_init) {
			/*
			 * We assume that console is ready for us...
			 * this assumes that a dca or ite console
			 * has been selected already and will init
			 * on the first putc.
			 */
			printf("dcm%d: ", UNIT(kgdb_dev));
			kgdb_connect(1);
		}
	}
#endif
D 14
#endif
E 14
E 11
}

dcmcninit(cp)
	struct consdev *cp;
{
	dcminit(cp->cn_dev, dcmdefaultrate);
I 11
	dcmconsinit = 1;
E 11
	dcmconsole = UNIT(cp->cn_dev);
}

dcminit(dev, rate)
	dev_t dev;
	int rate;
{
	register struct dcmdevice *dcm = dcm_addr[BOARD(dev)];
	int s, mode, port;

	port = PORT(dev);
	mode = LC_8BITS | LC_1STOP;
E 2
	s = splhigh();
D 2
	/* do something */
E 2
I 2
	/*
	 * Wait for transmitter buffer to empty.
	 */
	while (dcm->dcm_thead[port].ptr != dcm->dcm_ttail[port].ptr)
		DELAY(DCM_USPERCH(rate));
	/*
	 * Make changes known to hardware.
	 */
	dcm->dcm_data[port].dcm_baud = ttspeedtab(rate, dcmspeedtab);
	dcm->dcm_data[port].dcm_conf = mode;
	SEM_LOCK(dcm);
	dcm->dcm_cmdtab[port].dcm_data |= CT_CON;
	dcm->dcm_cr |= (1 << port);
	SEM_UNLOCK(dcm);
	/*
D 11
	 * Delay for config change to take place. Weighted by buad.
E 11
I 11
	 * Delay for config change to take place. Weighted by baud.
E 11
	 * XXX why do we do this?
	 */
	DELAY(16 * DCM_USPERCH(rate));
E 2
	splx(s);
D 2
	dcmconsole = unit;
	if (majordev)
		dcm_tty[unit].t_dev = makedev(majordev, unit);
	return(&dcm_tty[unit]);
E 2
}

dcmcngetc(dev)
I 2
	dev_t dev;
E 2
{
D 2
	return(0);
E 2
I 2
	register struct dcmdevice *dcm = dcm_addr[BOARD(dev)];
	register struct dcmrfifo *fifo;
	register struct dcmpreg *pp;
	register unsigned head;
	int s, c, stat, port;

	port = PORT(dev);
	pp = dcm_preg(dcm, port);
	s = splhigh();
	head = pp->r_head & RX_MASK;
	fifo = &dcm->dcm_rfifos[3-port][head>>1];
	while (head == (pp->r_tail & RX_MASK))
		;
	/*
	 * If board interrupts are enabled, just let our received char
	 * interrupt through in case some other port on the board was
	 * busy.  Otherwise we must clear the interrupt.
	 */
	SEM_LOCK(dcm);
	if ((dcm->dcm_ic & IC_IE) == 0)
		stat = dcm->dcm_iir;
	SEM_UNLOCK(dcm);
	c = fifo->data_char;
	stat = fifo->data_stat;
	pp->r_head = (head + 2) & RX_MASK;
	splx(s);
D 14
	return(c);
E 14
I 14
	return (c);
E 14
E 2
}

/*
 * Console kernel output character routine.
 */
dcmcnputc(dev, c)
	dev_t dev;
D 2
	register int c;
E 2
I 2
	int c;
E 2
{
	register struct dcmdevice *dcm = dcm_addr[BOARD(dev)];
D 2
	int port = PORT(dev);
	short stat;
	int head, tail, next;
	int s = splhigh();
E 2
I 2
	register struct dcmpreg *pp;
	unsigned tail;
	int s, port, stat;
E 2

D 2
	if (dcmconsole == -1)
		(void) dcmcninit(0);

	do {
		tail = dcm->dcm_ttail[port].ptr & TX_MASK;
		head = dcm->dcm_thead[port].ptr & TX_MASK;
	} while (tail != head);
	next = (dcm->dcm_ttail[port].ptr + 1) & TX_MASK;

	dcm->dcm_tfifos[3 - port][tail].data_char = c;
	dcm->dcm_ttail[port].ptr = next;

	dcm->dcm_cmdtab[port].dcm_data = CT_TX;
E 2
I 2
	port = PORT(dev);
	pp = dcm_preg(dcm, port);
	s = splhigh();
#ifdef KGDB
	if (dev != kgdb_dev)
#endif
D 11
	if (dcmconsole == -1) {
E 11
I 11
	if (dcmconsinit == 0) {
E 11
		(void) dcminit(dev, dcmdefaultrate);
D 11
		dcmconsole = UNIT(dev);
E 11
I 11
		dcmconsinit = 1;
E 11
	}
	tail = pp->t_tail & TX_MASK;
	while (tail != (pp->t_head & TX_MASK))
		;
	dcm->dcm_tfifos[3-port][tail].data_char = c;
	pp->t_tail = tail = (tail + 1) & TX_MASK;
E 2
	SEM_LOCK(dcm);
D 2
	dcm->dcm_cr = (1 << port);
E 2
I 2
	dcm->dcm_cmdtab[port].dcm_data |= CT_TX;
	dcm->dcm_cr |= (1 << port);
E 2
	SEM_UNLOCK(dcm);
D 2

E 2
I 2
	while (tail != (pp->t_head & TX_MASK))
		;
	/*
	 * If board interrupts are enabled, just let our completion
	 * interrupt through in case some other port on the board
	 * was busy.  Otherwise we must clear the interrupt.
	 */
	if ((dcm->dcm_ic & IC_IE) == 0) {
		SEM_LOCK(dcm);
		stat = dcm->dcm_iir;
		SEM_UNLOCK(dcm);
	}
E 2
	splx(s);
}
D 2
#endif
E 2
#endif
E 1
