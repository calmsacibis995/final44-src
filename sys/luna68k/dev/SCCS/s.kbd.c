h05728
s 00000/00035/00303
d D 8.2 93/12/06 20:35:28 akito 8 7
c remove kbdselect (use ttselect)
e
s 00002/00002/00336
d D 8.1 93/06/10 22:16:39 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00001/00331
d D 7.6 93/02/04 15:26:07 akito 6 5
c add line for muti byte read
e
s 00015/00000/00317
d D 7.5 93/02/02 10:58:25 akito 5 4
c insert Rx buffer flushing code on close & disable mouse track
e
s 00000/00005/00317
d D 7.4 92/12/29 08:11:26 akito 4 3
c bug fix of hang up in interrupt process
e
s 00281/00173/00041
d D 7.3 92/12/25 13:11:54 akito 3 2
c This is keyboard & mouse device driver now.
e
s 00005/00005/00209
d D 7.2 92/12/10 13:52:30 akito 2 1
c change wrong key-code mapping [,./]
e
s 00214/00000/00000
d D 7.1 92/11/17 16:36:54 akito 1 0
c date and time created 92/11/17 16:36:54 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
D 3
 * kbd.c --
 *
E 3
I 3
 * kbd.c -- keyboard device driver
 *	remade by A.Fujita, DEC-21-1992
E 3
 */

I 3
#define NKBD	2
E 3

D 3
#include "bmc.h"
#if NBMC > 0

E 3
D 2
#include "param.h"
#include "kbdreg.h"
E 2
I 2
#include <sys/param.h>
D 3
#include <luna68k/dev/kbdreg.h>
E 3
I 3
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
E 2

I 3
#include <luna68k/dev/device.h>
#include <luna68k/dev/sioreg.h>
#include <luna68k/dev/siovar.h>
#include <luna68k/dev/kbio.h>
E 3

D 3
struct kbd_keymap kbd_keymap[] = {
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
D 2
	KC_CODE,	0x6B,		0x3C,		/*  89 [0x59]	 ,    */
	KC_CODE,	0x6C,		0x3E,		/*  90 [0x5A]	 .    */
	KC_CODE,	0x3B,		0x3F,		/*  91 [0x5B]	 /    */
E 2
I 2
	KC_CODE,	0x2C,		0x3C,		/*  89 [0x59]	 ,    */
	KC_CODE,	0x2E,		0x3E,		/*  90 [0x5A]	 .    */
	KC_CODE,	0x2F,		0x3F,		/*  91 [0x5B]	 /    */
E 2
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
E 3
I 3
extern	struct sio_portc *sio_port_assign();
extern	struct sio_portc *sio_port_get();
E 3

D 3
int	shift_flag = 0;
int	ctrl_flag  = 0;
int	meta_flag  = 0;
E 3
I 3
struct	sio_softc kbd_softc[NKBD];
struct	sio_portc kbd_sport;
struct	sio_portc *kbd_pc;
E 3

D 3
kbd_decode(code)
	register u_char code;
E 3
I 3
int     kbdopen();
void    kbdstart();
int     kbdparam();
int     kbdintr();

struct	tty kbd_tty[NKBD];

int	kbddefaultrate = B9600;				/* speed of console line is fixed */
int	kbdmajor = 14;
int	kbd_state = 0;

#define	kbdunit(x)		minor(x)

/*
 *  entry routines
 */

/* ARGSUSED */
#ifdef __STDC__
kbdopen(dev_t dev, int flag, int mode, struct proc *p)
#else
kbdopen(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
#endif
E 3
{
D 3
	register unsigned int c, updown;
E 3
I 3
	register struct tty *tp;
	register int unit, s;
	register struct sio_portc *pc;
	int error = 0;
E 3

D 3
	if (code & 0x80)
		updown = 1;
	else
		updown = 0;
E 3
I 3
	unit = kbdunit(dev);
E 3

D 3
	code &= 0x7F;
E 3
I 3
	if (unit != 0)
		return (ENXIO);
E 3

D 3
	c = kbd_keymap[code].km_type;
E 3
I 3
	if (kbd_state == 0) {
		s = splhigh();
		pc = sio_port_get(1);
		kbd_sport = *pc;
		kbd_pc = sio_port_assign(1, kbdmajor, unit, kbdintr);
		splx(s);
	}
	kbd_softc[unit].sc_pc = kbd_pc;
	kbd_state |= 1 << unit;
E 3

D 3
	switch(c) {
E 3
I 3
	tp = &kbd_tty[unit];
	tp->t_oproc = kbdstart;
	tp->t_param = kbdparam;
	tp->t_dev = dev;
	if ((tp->t_state & TS_ISOPEN) == 0) {
		tp->t_state |= TS_WOPEN;
		ttychars(tp);
		if (tp->t_ispeed == 0) {
/*
			tp->t_iflag = TTYDEF_IFLAG;
			tp->t_oflag = TTYDEF_OFLAG;
			tp->t_cflag = TTYDEF_CFLAG;
			tp->t_lflag = TTYDEF_LFLAG;
 */
			tp->t_iflag = 0;
			tp->t_oflag = 0;
			tp->t_cflag = (CREAD | CS8 | HUPCL);
			tp->t_lflag = 0;
E 3

D 3
	case KC_CODE:
		if (updown)
			c = KC_IGNORE;
		break;
E 3
I 3
			tp->t_ispeed = tp->t_ospeed = kbddefaultrate;
		}
		ttsetwater(tp);
	} else if (tp->t_state&TS_XCLUDE && p->p_ucred->cr_uid != 0)
		return (EBUSY);
E 3

D 3
	case KC_SHIFT:
		switch(kbd_keymap[code].km_code[0]) {
		case KS_SHIFT:
			shift_flag = 1 - updown;
			break;
E 3
I 3
	tp->t_state |= TS_CARR_ON;
E 3

D 3
		case KS_CTRL:
			ctrl_flag  = 1 - updown;
			break;
E 3
I 3
	if (error == 0)
		error = (*linesw[tp->t_line].l_open)(dev, tp);
E 3

D 3
		case KS_META:
			meta_flag  = 1 - updown;
			break;
E 3
I 3
	return (error);
}

/*ARGSUSED*/
kbdclose(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
I 5
	register struct siodevice *sio = kbd_pc->pc_addr;
E 5
	register struct	sio_portc *pc;
	register struct tty *tp;
	register int unit, s;
I 5
	int  code, rr;
E 5

	unit = kbdunit(dev);

	tp = &kbd_tty[unit];
	(*linesw[tp->t_line].l_close)(tp, flag);
	ttyclose(tp);

	kbd_state &= ~(1 << unit);

	if (kbd_state == 0) {
		s = splhigh();
I 5

		while((rr = siogetreg(sio)) & RR_RXRDY) {
			code = sio->sio_data;
			DELAY(100);
		}

E 5
		pc = &kbd_sport;
		(void) sio_port_assign(1, pc->pc_major, pc->pc_unit, pc->pc_intr);
		splx(s);
	}

	return (0);
}
 
kbdread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp = &kbd_tty[kbdunit(dev)];
 
	return ((*linesw[tp->t_line].l_read)(tp, uio, flag));
}

int
kbdparam(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	int unit = kbdunit(tp->t_dev);
	register struct sio_softc *sc = &kbd_softc[unit];
	register int cflag = t->c_cflag;
 
        /* and copy to tty */
        tp->t_ispeed = t->c_ispeed;
        tp->t_ospeed = t->c_ospeed;
        tp->t_cflag = cflag;

	/*
	 * change line speed
	 */

	/*
	 * parity
	 */

	/*
	 * stop bit
	 */

	return (0);
}

kbdioctl(dev, cmd, data, flag, p)
	dev_t dev;
	int cmd;
	caddr_t data;
	int flag;
	struct proc *p;
{
	register struct siodevice *sio = kbd_pc->pc_addr;
	register struct tty *tp;
	register int unit = kbdunit(dev);
	register int error;
I 5
	int code, rr, s;
E 5

	tp = &kbd_tty[unit];
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag, p);
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, data, flag);
	if (error >= 0)
		return (error);

	switch (cmd) {

	case KIOCMOUSE:
		if (*((int *) data)) {
			sio->sio_data = 0x60;	/* enable  mouse tracking */
		} else {
I 5
			s = splhigh();
E 5
			sio->sio_data = 0x20;	/* disable mouse tracking */
I 5
			while((rr = siogetreg(sio)) & RR_RXRDY) {
				code = sio->sio_data;
				DELAY(100);
			}
			splx(s);
E 5
E 3
		}
		break;

	default:
D 3
		break;
E 3
I 3
		return (ENOTTY);
E 3
	}
I 3
	return (0);
}
E 3

D 3
	c |= kbd_keymap[code].km_code[shift_flag];
E 3
I 3
/*
 *
 */
void
kbdstart(tp)
	register struct tty *tp;
{
	register int unit;
	register struct siodevice *sio = kbd_pc->pc_addr;
	register int rr;
	int s, c;
 
	s = spltty();
E 3

D 3
	if (kbd_keymap[code].km_type == KC_CODE) {
		if (meta_flag)
			c |= 0x0080;
		if (ctrl_flag)
			c &= 0xFF1F;
E 3
I 3
	if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP))
		goto out;

	if (tp->t_outq.c_cc <= tp->t_lowat) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		selwakeup(&tp->t_wsel);
E 3
	}

D 3
	return(c);
E 3
I 3
	if (tp->t_outq.c_cc != 0)
		c = getc(&tp->t_outq);

out:
	splx(s);
E 3
}
D 3
#endif
E 3
I 3

/*
 *  interrupt handling 
 */

kbdintr(unit)
	register int unit;
{
	register struct siodevice *sio = kbd_pc->pc_addr;
	register struct tty *tp;
	register u_char code;
	int s, rr;

I 6
	tp = &kbd_tty[0];		/* Keyboard */
E 6
	rr = siogetreg(sio);

	if (rr & RR_RXRDY) {
		code = sio->sio_data;
D 6
		tp = &kbd_tty[0];		/* Keyboard */
E 6
		if ((tp->t_state & TS_ISOPEN) != 0)
			(*linesw[tp->t_line].l_rint)(code, tp);
I 6

		while ((rr = siogetreg(sio)) & RR_RXRDY) {
			code = sio->sio_data;
			if ((tp->t_state & TS_ISOPEN) != 0)
				(*linesw[tp->t_line].l_rint)(code, tp);
		}
E 6
	}

	if (rr & RR_TXRDY) {
		sio->sio_cmd = WR0_RSTPEND;
D 4
		tp->t_state &= ~(TS_BUSY|TS_FLUSH);
		if (tp->t_line)
			(*linesw[tp->t_line].l_start)(tp);
		else
			kbdstart(tp);
E 4
	}
}
D 8

kbdselect(dev, rw, p)
	dev_t dev;
	int rw;
	struct proc *p;
{
	register int unit = kbdunit(dev);
	register struct tty *tp;
	int nread;
	int s = spltty();

	tp = &kbd_tty[unit];

	switch (rw) {

	case FREAD:
		nread = ttnread(tp);
		if (nread > 0 || ((tp->t_cflag&CLOCAL) == 0 && (tp->t_state&TS_CARR_ON) == 0))
			goto win;

		selrecord(p, &tp->t_rsel);
		break;

	case FWRITE:
		if (tp->t_outq.c_cc <= tp->t_lowat)
			goto win;
		selrecord(p, &tp->t_wsel);
		break;
	}
	splx(s);
	return (0);
win:
	splx(s);
	return (1);
}
E 8
E 3
E 1
