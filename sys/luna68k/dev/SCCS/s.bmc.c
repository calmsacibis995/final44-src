h16970
s 00002/00002/00640
d D 8.1 93/06/10 22:16:14 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00641
d D 7.8 93/06/08 10:37:53 akito 8 7
c return code of bmcprob is changed
e
s 00030/00033/00612
d D 7.7 93/05/02 05:41:29 akito 7 6
c probe routine support
e
s 00004/00000/00641
d D 7.6 93/02/04 15:23:15 akito 6 5
c reset Tx interrupt
e
s 00211/00006/00430
d D 7.5 92/12/25 13:10:51 akito 5 4
c move key-code table and decode routine from kbd.c
e
s 00000/00095/00436
d D 7.4 92/12/20 12:35:43 akito 4 3
c eliminate BMD define and related codes
e
s 00008/00003/00523
d D 7.3 92/12/14 16:12:51 akito 3 2
c support TIOCCONS console redirection
e
s 00013/00013/00513
d D 7.2 92/12/10 13:51:20 akito 2 1
c make kernel includes standard, again.
e
s 00526/00000/00000
d D 7.1 92/11/17 16:29:08 akito 1 0
c date and time created 92/11/17 16:29:08 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 9
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 7
#define	BMC_NOCONSOLE
D 4
#define	BMD
E 4

D 4
#ifdef	BMD
E 4
#define	BMC_CNPORT	1
D 4
#else
#define	BMC_CNPORT	0
#endif
E 4

E 7
#include "bmc.h"
#if NBMC > 0

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
I 7
#include <machine/stinger.h>
E 7
E 2
D 5

E 5
D 2
#include "device.h"
#include "sioreg.h"
#include "siovar.h"
E 2
I 2
#include <luna68k/dev/device.h>
#include <luna68k/dev/sioreg.h>
#include <luna68k/dev/siovar.h>
I 7
#include <luna68k/luna68k/cons.h>
E 7
E 2

D 4
#ifdef	BMD
E 4
D 5
#include "kbdreg.h"
D 4
#endif
E 4

E 5
extern	struct sio_portc *sio_port_assign();

int     bmcprobe();
int     bmcopen();
void    bmcstart();
int     bmcparam();
int     bmcintr();

struct	driver bmcdriver = {
	bmcprobe, "bmc",
};

struct	bmc_softc {
	struct sio_portc *sc_pc;
	int	sc_mask;
};

struct	bmc_softc bmc_softc[NBMC];

struct	tty bmc_tty[NBMC];

D 7
int	bmc_config_done = 0;
E 7
I 7
int	bmc_active;
E 7
D 3

int	bmcconsole;
E 3
I 3
int	bmcconsole = -1;
E 3
int	bmcdefaultrate = B9600;				/* speed of console line is fixed */
D 5
int	bmcmajor = 0;
E 5
I 5
int	bmcmajor = 13;
E 5

#define	bmcunit(x)		minor(x)

I 3
extern	struct tty *constty;
E 3

/*
I 5
 *  key-code decoding
 */

struct bmc_keymap {
	int	km_type;
	int	km_code[2];
};

#define KC_CHAR		0x000000FF
#define KC_TYPE		0x0000FF00
#define	KC_CODE		0x00000000
#define	KC_SHIFT	0x00000100
#define	KC_IGNORE	0x0000FF00

#define KS_SHIFT	0
#define KS_CTRL		1
#define KS_META		2

struct bmc_keymap bmc_keymap[] = {
	KC_IGNORE,	0,		0,		/*   0 [0x00]	      */
	KC_IGNORE,	0,		0,		/*   1 [0x01]	      */
	KC_IGNORE,	0,		0,		/*   2 [0x02]	      */
	KC_IGNORE,	0,		0,		/*   3 [0x03]	      */
	KC_IGNORE,	0,		0,		/*   4 [0x04]	      */
	KC_IGNORE,	0,		0,		/*   5 [0x05]	      */
	KC_IGNORE,	0,		0,		/*   6 [0x06]	      */
	KC_IGNORE,	0,		0,		/*   7 [0x07]	      */
	KC_IGNORE,	0,		0,		/*   8 [0x08]	      */
	KC_CODE,	0x09,		0x09,		/*   9 [0x09]	TAB   */
	KC_SHIFT,	KS_CTRL,	KS_CTRL,	/*  10 [0x0A]	CTRL  */
	KC_IGNORE,	0,		0,		/*  11 [0x0B]	      */
	KC_SHIFT,	KS_SHIFT,	KS_SHIFT,	/*  12 [0x0C]	SHIFT */
	KC_SHIFT,	KS_SHIFT,	KS_SHIFT,	/*  13 [0x0D]	SHIFT */
	KC_IGNORE,	0,		0,		/*  14 [0x0E]	      */
	KC_SHIFT,	KS_META,	KS_META,	/*  15 [0x0F]	META  */
	KC_CODE,	0x1B,		0x1B,		/*  16 [0x10]	ESC   */
	KC_CODE,	0x08,		0x08,		/*  17 [0x11]	BS    */
	KC_CODE,	0x0D,		0x0D,		/*  18 [0x12]	CR    */
	KC_IGNORE,	0,		0,		/*  19 [0x13]	      */
	KC_CODE,	0x20,		0x20,		/*  20 [0x14]	SP    */
	KC_CODE,	0x7F,		0x7F,		/*  21 [0x15]	DEL   */
	KC_IGNORE,	0,		0,		/*  22 [0x16]	      */
	KC_IGNORE,	0,		0,		/*  23 [0x17]	      */
	KC_IGNORE,	0,		0,		/*  24 [0x18]	      */
	KC_IGNORE,	0,		0,		/*  25 [0x19]	      */
	KC_IGNORE,	0,		0,		/*  26 [0x1A]	      */
	KC_IGNORE,	0,		0,		/*  27 [0x1B]	      */
	KC_IGNORE,	0,		0,		/*  28 [0x1C]	      */
	KC_IGNORE,	0,		0,		/*  29 [0x1D]	      */
	KC_IGNORE,	0,		0,		/*  30 [0x1E]	      */
	KC_IGNORE,	0,		0,		/*  31 [0x1F]	      */
	KC_IGNORE,	0,		0,		/*  32 [0x20]	      */
	KC_IGNORE,	0,		0,		/*  33 [0x21]	      */
	KC_CODE,	0x31,		0x21,		/*  34 [0x22]	 1    */
	KC_CODE,	0x32,		0x22,		/*  35 [0x23]	 2    */
	KC_CODE,	0x33,		0x23,		/*  36 [0x24]	 3    */
	KC_CODE,	0x34,		0x24,		/*  37 [0x25]	 4    */
	KC_CODE,	0x35,		0x25,		/*  38 [0x26]	 5    */
	KC_CODE,	0x36,		0x26,		/*  39 [0x27]	 6    */
	KC_CODE,	0x37,		0x27,		/*  40 [0x28]	 7    */
	KC_CODE,	0x38,		0x28,		/*  41 [0x29]	 8    */
	KC_CODE,	0x39,		0x29,		/*  42 [0x2A]	 9    */
	KC_CODE,	0x30,		0x30,		/*  43 [0x2B]	 0    */
	KC_CODE,	0x2D,		0x3D,		/*  44 [0x2C]	 -    */
	KC_CODE,	0x5E,		0x7E,		/*  45 [0x2D]	 ^    */
	KC_CODE,	0x5C,		0x7C,		/*  46 [0x2E]	 \    */
	KC_IGNORE,	0,		0,		/*  47 [0x2F]	      */
	KC_IGNORE,	0,		0,		/*  48 [0x30]	      */
	KC_IGNORE,	0,		0,		/*  49 [0x31]	      */
	KC_CODE,	0x71,		0x51,		/*  50 [0x32]	 q    */
	KC_CODE,	0x77,		0x57,		/*  51 [0x33]	 w    */
	KC_CODE,	0x65,		0x45,		/*  52 [0x34]	 e    */
	KC_CODE,	0x72,		0x52,		/*  53 [0x35]	 r    */
	KC_CODE,	0x74,		0x54,		/*  54 [0x36]	 t    */
	KC_CODE,	0x79,		0x59,		/*  55 [0x37]	 y    */
	KC_CODE,	0x75,		0x55,		/*  56 [0x38]	 u    */
	KC_CODE,	0x69,		0x49,		/*  57 [0x39]	 i    */
	KC_CODE,	0x6F,		0x4F,		/*  58 [0x3A]	 o    */
	KC_CODE,	0x70,		0x50,		/*  59 [0x3B]	 p    */
	KC_CODE,	0x40,		0x60,		/*  60 [0x3C]	 @    */
	KC_CODE,	0x5B,		0x7B,		/*  61 [0x3D]	 [    */
	KC_IGNORE,	0,		0,		/*  62 [0x3E]	      */
	KC_IGNORE,	0,		0,		/*  63 [0x3F]	      */
	KC_IGNORE,	0,		0,		/*  64 [0x40]	      */
	KC_IGNORE,	0,		0,		/*  65 [0x41]	      */
	KC_CODE,	0x61,		0x41,		/*  66 [0x42]	 a    */
	KC_CODE,	0x73,		0x53,		/*  67 [0x43]	 s    */
	KC_CODE,	0x64,		0x44,		/*  68 [0x44]	 d    */
	KC_CODE,	0x66,		0x46,		/*  69 [0x45]	 f    */
	KC_CODE,	0x67,		0x47,		/*  70 [0x46]	 g    */
	KC_CODE,	0x68,		0x48,		/*  71 [0x47]	 h    */
	KC_CODE,	0x6A,		0x4A,		/*  72 [0x48]	 j    */
	KC_CODE,	0x6B,		0x4B,		/*  73 [0x49]	 k    */
	KC_CODE,	0x6C,		0x4C,		/*  74 [0x4A]	 l    */
	KC_CODE,	0x3B,		0x2B,		/*  75 [0x4B]	 ;    */
	KC_CODE,	0x3A,		0x2A,		/*  76 [0x4C]	 :    */
	KC_CODE,	0x5D,		0x7D,		/*  77 [0x4D]	 ]    */
	KC_IGNORE,	0,		0,		/*  78 [0x4E]	      */
	KC_IGNORE,	0,		0,		/*  79 [0x4F]	      */
	KC_IGNORE,	0,		0,		/*  80 [0x50]	      */
	KC_IGNORE,	0,		0,		/*  81 [0x51]	      */
	KC_CODE,	0x7A,		0x5A,		/*  82 [0x52]	 z    */
	KC_CODE,	0x78,		0x58,		/*  83 [0x53]	 x    */
	KC_CODE,	0x63,		0x43,		/*  84 [0x54]	 c    */
	KC_CODE,	0x76,		0x56,		/*  85 [0x55]	 v    */
	KC_CODE,	0x62,		0x42,		/*  86 [0x56]	 b    */
	KC_CODE,	0x6E,		0x4E,		/*  87 [0x57]	 n    */
	KC_CODE,	0x6D,		0x4D,		/*  88 [0x58]	 m    */
	KC_CODE,	0x2C,		0x3C,		/*  89 [0x59]	 ,    */
	KC_CODE,	0x2E,		0x3E,		/*  90 [0x5A]	 .    */
	KC_CODE,	0x2F,		0x3F,		/*  91 [0x5B]	 /    */
	KC_CODE,	0x5F,		0x5F,		/*  92 [0x5C]	 _    */
	KC_IGNORE,	0,		0,		/*  93 [0x5D]	      */
	KC_IGNORE,	0,		0,		/*  94 [0x5E]	      */
	KC_IGNORE,	0,		0,		/*  95 [0x5F]	      */
	KC_IGNORE,	0,		0,		/*  96 [0x60]	      */
	KC_IGNORE,	0,		0,		/*  97 [0x61]	      */
	KC_IGNORE,	0,		0,		/*  98 [0x62]	      */
	KC_IGNORE,	0,		0,		/*  99 [0x63]	      */
	KC_IGNORE,	0,		0,		/* 100 [0x64]	      */
	KC_IGNORE,	0,		0,		/* 101 [0x65]	      */
	KC_IGNORE,	0,		0,		/* 102 [0x66]	      */
	KC_IGNORE,	0,		0,		/* 103 [0x67]	      */
	KC_IGNORE,	0,		0,		/* 104 [0x68]	      */
	KC_IGNORE,	0,		0,		/* 105 [0x69]	      */
	KC_IGNORE,	0,		0,		/* 106 [0x6A]	      */
	KC_IGNORE,	0,		0,		/* 107 [0x6B]	      */
	KC_IGNORE,	0,		0,		/* 108 [0x6C]	      */
	KC_IGNORE,	0,		0,		/* 109 [0x6D]	      */
	KC_IGNORE,	0,		0,		/* 110 [0x6E]	      */
	KC_IGNORE,	0,		0,		/* 111 [0x6F]	      */
	KC_IGNORE,	0,		0,		/* 112 [0x70]	      */
	KC_IGNORE,	0,		0,		/* 113 [0x71]	      */
	KC_IGNORE,	0,		0,		/* 114 [0x72]	      */
	KC_IGNORE,	0,		0,		/* 115 [0x73]	      */
	KC_IGNORE,	0,		0,		/* 116 [0x74]	      */
	KC_IGNORE,	0,		0,		/* 117 [0x75]	      */
	KC_IGNORE,	0,		0,		/* 118 [0x76]	      */
	KC_IGNORE,	0,		0,		/* 119 [0x77]	      */
	KC_IGNORE,	0,		0,		/* 120 [0x78]	      */
	KC_IGNORE,	0,		0,		/* 121 [0x79]	      */
	KC_IGNORE,	0,		0,		/* 122 [0x7A]	      */
	KC_IGNORE,	0,		0,		/* 123 [0x7B]	      */
	KC_IGNORE,	0,		0,		/* 124 [0x7C]	      */
	KC_IGNORE,	0,		0,		/* 125 [0x7D]	      */
	KC_IGNORE,	0,		0,		/* 126 [0x7E]	      */
	KC_IGNORE,	0,		0,		/* 127 [0x7F]	      */
};

int	shift_flag = 0;
int	ctrl_flag  = 0;
int	meta_flag  = 0;

bmc_decode(code)
	register u_char code;
{
	register unsigned int c, updown;

	if (code & 0x80)
		updown = 1;
	else
		updown = 0;

	code &= 0x7F;

	c = bmc_keymap[code].km_type;

	switch(c) {

	case KC_CODE:
		if (updown)
			c = KC_IGNORE;
		break;

	case KC_SHIFT:
		switch(bmc_keymap[code].km_code[0]) {
		case KS_SHIFT:
			shift_flag = 1 - updown;
			break;

		case KS_CTRL:
			ctrl_flag  = 1 - updown;
			break;

		case KS_META:
			meta_flag  = 1 - updown;
			break;
		}
		break;

	default:
		break;
	}

	c |= bmc_keymap[code].km_code[shift_flag];

	if (bmc_keymap[code].km_type == KC_CODE) {
		if (meta_flag)
			c |= 0x0080;
		if (ctrl_flag)
			c &= 0xFF1F;
	}

	return(c);
}


/*
E 5
 *  probe routine
 */

bmcprobe(hd)
	register struct hp_device *hd;
{
D 7
}
E 7
I 7
	int unit = hd->hp_unit;
	register struct bmc_softc *sc = &bmc_softc[unit];
	register struct sio_portc *pc;
E 7

D 7
bmcinit(port)
	register int port;
{
	register struct bmc_softc *sc = &bmc_softc[0];

	/*
	 * if BMC is already configured, should be skipped.
         */
	if (bmc_config_done)
E 7
I 7
	if (sc->sc_pc != 0) {
		pc = sc->sc_pc;
		printf("bmc%d: port %d, address 0x%x, intr 0x%x (console)\n",
		       pc->pc_unit, pc->pc_port, pc->pc_addr, pc->pc_intr);
E 7
D 8
		return(0);
E 8
I 8
		return(1);
E 8
I 7
	}
E 7

	/*
	 * Check out bitmap Interface board
	 */

D 7
	/* port checking (for keyboard) */
	if (port != 1)
E 7
I 7
	if (KernInter.plane == 0) {
E 7
		return(0);
I 7
	}
E 7

	/* locate the major number */
	for (bmcmajor = 0; bmcmajor < nchrdev; bmcmajor++)
		if (cdevsw[bmcmajor].d_open == bmcopen)
			break;

D 7
	sc->sc_pc = sio_port_assign(port, bmcmajor, 0, bmcintr);
E 7
I 7
	sc->sc_pc = pc = sio_port_assign(BMC_PORT, bmcmajor, unit, bmcintr);
E 7

D 7
	printf("bmc%d: port %d, address 0x%x\n", sc->sc_pc->pc_unit, port, sc->sc_pc->pc_addr);
E 7
I 7
	printf("bmc%d: port %d, address 0x%x, intr 0x%x\n",
	       pc->pc_unit, pc->pc_port, pc->pc_addr, pc->pc_intr);
E 7

D 4
#ifdef	BMD
E 4
	bmdinit();
D 4
#endif
E 4

D 7
	bmc_config_done = 1;
E 7
I 7
	bmc_active |= 1 << unit;
E 7
	return(1);
}

D 7

E 7
/*
 *  entry routines
 */

/* ARGSUSED */
#ifdef __STDC__
bmcopen(dev_t dev, int flag, int mode, struct proc *p)
#else
bmcopen(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
#endif
{
	register struct tty *tp;
	register int unit;
	int error = 0;

	unit = bmcunit(dev);
I 7

E 7
	if (unit >= NBMC)
		return (ENXIO);
I 7
	if ((bmc_active & (1 << unit)) == 0)
		return (ENXIO);

E 7
	tp = &bmc_tty[unit];
	tp->t_oproc = bmcstart;
	tp->t_param = bmcparam;
	tp->t_dev = dev;
	if ((tp->t_state & TS_ISOPEN) == 0) {
		tp->t_state |= TS_WOPEN;
		ttychars(tp);
		if (tp->t_ispeed == 0) {
			tp->t_iflag = TTYDEF_IFLAG;
			tp->t_oflag = TTYDEF_OFLAG;
			tp->t_cflag = TTYDEF_CFLAG;
/*			tp->t_cflag = (CREAD | CS8 | HUPCL);	*/
			tp->t_lflag = TTYDEF_LFLAG;
			tp->t_ispeed = tp->t_ospeed = bmcdefaultrate;
		}
		bmcparam(tp, &tp->t_termios);
		ttsetwater(tp);
	} else if (tp->t_state&TS_XCLUDE && p->p_ucred->cr_uid != 0)
		return (EBUSY);
	tp->t_state |= TS_CARR_ON;
	(void) spltty();
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
bmcclose(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	register struct tty *tp;
	register int unit;

	unit = bmcunit(dev);
	tp = &bmc_tty[unit];
	(*linesw[tp->t_line].l_close)(tp, flag);
	ttyclose(tp);
	return (0);
}
 
bmcread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp = &bmc_tty[bmcunit(dev)];
 
	return ((*linesw[tp->t_line].l_read)(tp, uio, flag));
}
 
bmcwrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
D 3
	register struct tty *tp = &bmc_tty[bmcunit(dev)];
E 3
I 3
	register int unit = bmcunit(dev);
	register struct tty *tp = &bmc_tty[unit];

	if ((unit == bmcconsole) && constty &&
	    (constty->t_state&(TS_CARR_ON|TS_ISOPEN))==(TS_CARR_ON|TS_ISOPEN))
		tp = constty;
E 3

	return ((*linesw[tp->t_line].l_write)(tp, uio, flag));
}

/*
 * Stop output on a line.
 */
/*ARGSUSED*/
bmcstop(tp, flag)
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

bmcioctl(dev, cmd, data, flag, p)
	dev_t dev;
	int cmd;
	caddr_t data;
	int flag;
	struct proc *p;
{
	register struct tty *tp;
	register int unit = bmcunit(dev);
	register int error;

	tp = &bmc_tty[unit];
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag, p);
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, data, flag);
	if (error >= 0)
		return (error);

	switch (cmd) {
	default:
		return (ENOTTY);
	}
	return (0);
}

/*
 *
 */
D 4
#ifdef BMD
E 4
void
bmcstart(tp)
	register struct tty *tp;
{
	int unit = bmcunit(tp->t_dev);
	register struct bmc_softc *sc = &bmc_softc[unit];
	register int cc, s;
	int hiwat = 0;

	s = spltty();
	if (tp->t_state & (TS_TIMEOUT|TS_BUSY|TS_TTSTOP)) {
		splx(s);
		return;
	}
	tp->t_state |= TS_BUSY;
	cc = tp->t_outq.c_cc;
	if (cc <= tp->t_lowat) {
		if (tp->t_state & TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		selwakeup(&tp->t_wsel);
	}
	/*
	 * Limit the amount of output we do in one burst
	 * to prevent hogging the CPU.
	 */
D 4
/*
	if (cc > iteburst) {
		hiwat++;
		cc = iteburst;
	}
 */
E 4
	while (--cc >= 0) {
		register int c;

		c = getc(&tp->t_outq);
		/*
		 * iteputchar() may take a long time and we don't want to
		 * block all interrupts for long periods of time.  Since
		 * there is no need to stay at high priority while outputing
		 * the character (since we don't have to worry about
		 * interrupts), we don't.  We just need to make sure that
		 * we don't reenter iteputchar, which is guarenteed by the
		 * earlier setting of TS_BUSY.
		 */
		splx(s);
		bmdputc(c & sc->sc_mask);
		spltty();
	}
D 4
/*
	if (hiwat) {
		tp->t_state |= TS_TIMEOUT;
		timeout(ttrstrt, tp, 1);
	}
 */
E 4
	tp->t_state &= ~TS_BUSY;
	splx(s);
}
D 4
#else
void
bmcstart(tp)
	register struct tty *tp;
{
	register struct siodevice *sio;
	register int rr;
	int s, unit, c;
 
	unit = bmcunit(tp->t_dev);
	sio = bmc_softc[unit].sc_pc->pc_addr;
	s = spltty();
	if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP))
		goto out;
	if (tp->t_outq.c_cc <= tp->t_lowat) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		selwakeup(&tp->t_wsel);
	}
	if (tp->t_outq.c_cc == 0)
		goto out;
	rr = siogetreg(sio);
	if (rr & RR_TXRDY) {
		c = getc(&tp->t_outq);
		tp->t_state |= TS_BUSY;
		sio->sio_data = c;
	}
out:
	splx(s);
}
#endif
E 4

bmcparam(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	int unit = bmcunit(tp->t_dev);
	register struct bmc_softc *sc = &bmc_softc[unit];
	register int cflag = t->c_cflag;
 
        /* and copy to tty */
        tp->t_ispeed = t->c_ispeed;
        tp->t_ospeed = t->c_ospeed;
        tp->t_cflag = cflag;

	/*
	 * change line speed
	 */

	switch (cflag&CSIZE) {
	case CS5:
		sc->sc_mask = 0x1F ; break;
	case CS6:
		sc->sc_mask = 0x3F ; break;
	case CS7:
		sc->sc_mask = 0x7F ; break;
	case CS8:
		sc->sc_mask = 0xFF ; break;
	}

	/*
	 * parity
	 */

	/*
	 * stop bit
	 */

	return (0);
}


/*
 *  interrupt handling 
 */

D 4
#ifdef BMD
E 4
bmcintr(unit)
	register int unit;
{
	register struct siodevice *sio = bmc_softc[unit].sc_pc->pc_addr;
	register struct tty *tp;
	register u_char code;
	register int c;
	int s, rr;

	tp = &bmc_tty[unit];
	rr = siogetreg(sio);

	if (rr & RR_RXRDY) {
		code = sio->sio_data;
D 5
		c = kbd_decode(code);
E 5
I 5
		c = bmc_decode(code);
E 5
		if (c & KC_TYPE)			/* skip special codes */
			return;
		code = (c & KC_CHAR);
		if ((tp->t_state & TS_ISOPEN) != 0)
			(*linesw[tp->t_line].l_rint)(code, tp);
	}
I 6

	if (rr & RR_TXRDY) {
		sio->sio_cmd = WR0_RSTPEND;
	}
E 6
}
D 4
#else
bmcintr(unit)
	register int unit;
{
	register struct siodevice *sio = bmc_softc[unit].sc_pc->pc_addr;
	register u_char code;
	register struct tty *tp;
	int s, rr;
E 4

D 4
	tp = &bmc_tty[unit];
	rr = siogetreg(sio);

	if (rr & RR_RXRDY) {
		code = sio->sio_data;
		if ((tp->t_state & TS_ISOPEN) != 0)
			(*linesw[tp->t_line].l_rint)(code, tp);
	}

	if (rr & RR_TXRDY) {
		sio->sio_cmd = WR0_RSTPEND;
		tp->t_state &= ~(TS_BUSY|TS_FLUSH);
		if (tp->t_line)
			(*linesw[tp->t_line].l_start)(tp);
		else
			bmcstart(tp);
	}

}
#endif

E 4
/*
 * Following are all routines needed for SIO to act as console
 */
D 7
#include "../luna68k/cons.h"
E 7

bmccnprobe(cp)
	register struct consdev *cp;
{
D 7
#ifdef BMC_NOCONSOLE
	cp->cn_pri = CN_DEAD;
	return;
#else
	/* check DIP-SW setup */
	/* check bitmap interface board */
E 7

I 7
	if ((KernInter.dipsw & KIFF_DIPSW_NOBM) || (KernInter.plane == 0)) {
		cp->cn_pri = CN_DEAD;
		return;
	}

E 7
	/* locate the major number */
	for (bmcmajor = 0; bmcmajor < nchrdev; bmcmajor++)
		if (cdevsw[bmcmajor].d_open == bmcopen)
			break;
D 7

E 7
I 7
	
E 7
	/* initialize required fields */
	cp->cn_dev = makedev(bmcmajor, 0);
	cp->cn_tp  = &bmc_tty[0];
	cp->cn_pri = CN_INTERNAL;
D 7

	bmc_config_done = 1;
#endif
E 7
}

bmccninit(cp)
	struct consdev *cp;
{
	int unit = bmcunit(cp->cn_dev);
	register struct bmc_softc *sc = &bmc_softc[0];

	sioinit((struct siodevice *) SIO_HARDADDR, bmcdefaultrate);
I 7

E 7
D 4
#ifdef	BMD
E 4
	bmdinit();
D 4
#endif
E 4

	/* port assign */
D 7
	sc->sc_pc = sio_port_assign(BMC_CNPORT, bmcmajor, 0, bmcintr);
E 7
I 7
	sc->sc_pc = sio_port_assign(BMC_PORT, bmcmajor, 0, bmcintr);
E 7

	bmcconsole = unit;
I 7
	bmc_active |= 1 << unit;
E 7
}

bmccngetc(dev)
	dev_t dev;
{
	struct bmc_softc *sc = &bmc_softc[bmcunit(dev)];
	struct sio_portc *pc = sc->sc_pc;
D 4
#ifdef	BMD
E 4
	register int c;
	register u_char code;

	do {
		code = sio_imgetc(pc->pc_addr);
D 5
	} while ((c = kbd_decode(code)) & KC_TYPE);
E 5
I 5
	} while ((c = bmc_decode(code)) & KC_TYPE);
E 5

	return(c);
D 4
#else
	return(sio_imgetc(pc->pc_addr));
#endif
E 4
}

bmccnputc(dev, c)
	dev_t dev;
	int c;
{
	struct bmc_softc *sc = &bmc_softc[bmcunit(dev)];
	struct sio_portc *pc = sc->sc_pc;

D 4
#ifdef BMD
E 4
	bmdputc(c);
D 4
#else
	sio_imputc(pc->pc_addr, c);
#endif
E 4
}
#endif
E 1
