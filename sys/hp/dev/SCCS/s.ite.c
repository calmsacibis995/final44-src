h04306
s 00001/00001/00909
d D 8.3 95/01/09 17:38:55 cgd 19 18
c strategy returns void, ioctl cmd is u_long
e
s 00006/00002/00904
d D 8.2 94/01/12 10:05:43 bostic 18 17
c lint
e
s 00002/00002/00904
d D 8.1 93/06/10 21:24:13 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00009/00892
d D 7.16 93/02/18 20:41:03 hibler 16 15
c don't do cursor updates while ITE is off
e
s 00116/00063/00785
d D 7.15 92/12/27 09:12:45 hibler 15 14
c improvements: don't update cursor during bursts, don't raise
c spl above splhil in most cases
e
s 00013/00013/00835
d D 7.14 92/10/11 08:55:12 bostic 14 13
c make kernel includes standard
e
s 00003/00003/00845
d D 7.13 92/07/12 17:45:27 pendry 13 12
c MIN -> min
e
s 00001/00001/00847
d D 7.12 92/07/07 19:02:16 torek 12 11
c lint
e
s 00032/00059/00816
d D 7.11 92/06/05 15:23:25 hibler 11 10
c merge latest Utah hp300 code including 68040 support
e
s 00001/00005/00874
d D 7.10 92/02/15 21:18:15 torek 10 9
c convert to use new select interface, selrecord/selwakeup
e
s 00005/00002/00874
d D 7.9 92/02/05 23:25:08 mckusick 9 8
c ioctl takes five parameters
e
s 00003/00002/00873
d D 7.8 92/02/05 18:54:57 mckusick 8 7
c itestart is a void
e
s 00000/00001/00875
d D 7.7 91/11/05 22:07:08 mckusick 7 6
c lint
e
s 00004/00002/00872
d D 7.6 91/05/16 17:39:11 marc 6 5
c pass flags through in device close
e
s 00017/00014/00857
d D 7.5 91/05/04 19:49:16 karels 5 4
c update to current include, device calling conventions
e
s 00011/00011/00860
d D 7.4 90/12/16 16:36:21 bostic 4 3
c kernel reorg
e
s 00001/00001/00870
d D 7.3 90/11/04 19:33:27 mckusick 3 2
c update identifier from Utah
e
s 00002/00001/00869
d D 7.2 90/06/22 09:20:58 hibler 2 1
c minor correction to XCLUDE check
e
s 00870/00000/00000
d D 7.1 90/05/08 22:07:00 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 17
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 3
 * from: Utah $Hdr: ite.c 1.22 89/08/17$
E 3
I 3
D 11
 * from: Utah $Hdr: ite.c 1.1 90/07/09$
E 11
I 11
D 15
 * from: Utah $Hdr: ite.c 1.24 92/01/21$
E 15
I 15
 * from: Utah $Hdr: ite.c 1.28 92/12/20$
E 15
E 11
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Bit-mapped display terminal emulator machine independent code.
 * This is a very rudimentary.  Much more can be abstracted out of
 * the hardware dependent routines.
 */
#include "ite.h"
#if NITE > 0

#include "grf.h"

#undef NITE
#define NITE	NGRF

D 4
#include "param.h"
#include "conf.h"
#include "user.h"
#include "proc.h"
#include "ioctl.h"
#include "tty.h"
#include "systm.h"
#include "uio.h"
#include "malloc.h"
E 4
I 4
D 5
#include "sys/param.h"
#include "sys/conf.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/systm.h"
#include "sys/uio.h"
#include "sys/malloc.h"
E 5
I 5
D 14
#include "param.h"
#include "conf.h"
#include "proc.h"
#include "ioctl.h"
#include "tty.h"
#include "systm.h"
#include "malloc.h"
E 14
I 14
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/systm.h>
#include <sys/malloc.h>
E 14
E 5
E 4

I 11
D 14
#include "grfioctl.h"
#include "grfvar.h"
E 11
#include "itevar.h"
D 11
#include "iteioctl.h"
E 11
#include "kbdmap.h"
E 14
I 14
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
#include <hp/dev/itevar.h>
#include <hp/dev/kbdmap.h>
E 14

D 4
#include "machine/cpu.h"
E 4
I 4
D 5
#include "../include/cpu.h"
E 5
I 5
D 11
#include "machine/cpu.h"
E 5
E 4

E 11
#define set_attr(ip, attr)	((ip)->attribute |= (attr))
#define clr_attr(ip, attr)	((ip)->attribute &= ~(attr))

D 11
extern  int nodev();

int topcat_scroll(),	topcat_init(),		topcat_deinit();
int topcat_clear(),	topcat_putc(),	 	topcat_cursor();
int gatorbox_scroll(),	gatorbox_init(),	gatorbox_deinit();
int gatorbox_clear(),	gatorbox_putc(), 	gatorbox_cursor();
int rbox_scroll(),	rbox_init(),		rbox_deinit();
int rbox_clear(),	rbox_putc(), 		rbox_cursor();
int dvbox_scroll(),	dvbox_init(),		dvbox_deinit();
int dvbox_clear(),	dvbox_putc(), 		dvbox_cursor();

struct itesw itesw[] =
{
	topcat_init,		topcat_deinit,		topcat_clear,
	topcat_putc,		topcat_cursor,		topcat_scroll,

	gatorbox_init,		gatorbox_deinit,	gatorbox_clear,
	gatorbox_putc,		gatorbox_cursor,	gatorbox_scroll,

	rbox_init,		rbox_deinit,		rbox_clear,
	rbox_putc,		rbox_cursor,		rbox_scroll,

	dvbox_init,		dvbox_deinit,		dvbox_clear,
	dvbox_putc,		dvbox_cursor,		dvbox_scroll,
};

E 11
/*
I 15
 * No need to raise SPL above the HIL (the only thing that can
 * affect our state.
 */
#include <hp/dev/hilreg.h>
#define splite()		splhil()

/*
E 15
 * # of chars are output in a single itestart() call.
 * If this is too big, user processes will be blocked out for
 * long periods of time while we are emptying the queue in itestart().
 * If it is too small, console output will be very ragged.
 */
int	iteburst = 64;

int	nite = NITE;
struct  tty *kbd_tty = NULL;
struct	tty ite_tty[NITE];
struct  ite_softc ite_softc[NITE];

D 8
int	itestart();
E 8
I 8
D 15
void	itestart();
E 8
D 12
extern	int ttrstrt();
E 12
I 12
extern	void ttrstrt __P((void *));
E 15
I 15
void	itestart(), iterestart();
E 15
E 12
extern	struct tty *constty;

/*
 * Primary attribute buffer to be used by the first bitmapped console
 * found. Secondary displays alloc the attribute buffer as needed.
 * Size is based on a 68x128 display, which is currently our largest.
 */
u_char  console_attributes[0x2200];

I 15
#define ite_erasecursor(ip, sp)	{ \
	if ((ip)->flags & ITE_CURSORON) \
		(*(sp)->ite_cursor)((ip), ERASE_CURSOR); \
}
#define ite_drawcursor(ip, sp) { \
	if ((ip)->flags & ITE_CURSORON) \
		(*(sp)->ite_cursor)((ip), DRAW_CURSOR); \
}
#define ite_movecursor(ip, sp) { \
	if ((ip)->flags & ITE_CURSORON) \
		(*(sp)->ite_cursor)((ip), MOVE_CURSOR); \
}

E 15
/*
 * Perform functions necessary to setup device as a terminal emulator.
 */
iteon(dev, flag)
	dev_t dev;
I 18
	int flag;
E 18
{
	int unit = UNIT(dev);
	struct tty *tp = &ite_tty[unit];
	struct ite_softc *ip = &ite_softc[unit];

	if (unit < 0 || unit >= NITE || (ip->flags&ITE_ALIVE) == 0)
		return(ENXIO);
	/* force ite active, overriding graphics mode */
	if (flag & 1) {
		ip->flags |= ITE_ACTIVE;
		ip->flags &= ~(ITE_INGRF|ITE_INITED);
	}
	/* leave graphics mode */
	if (flag & 2) {
		ip->flags &= ~ITE_INGRF;
		if ((ip->flags & ITE_ACTIVE) == 0)
			return(0);
	}
	ip->flags |= ITE_ACTIVE;
	if (ip->flags & ITE_INGRF)
		return(0);
	if (kbd_tty == NULL || kbd_tty == tp) {
		kbd_tty = tp;
D 11
		kbdenable();
E 11
I 11
		kbdenable(unit);
E 11
	}
	iteinit(dev);
	return(0);
}

iteinit(dev)
     dev_t dev;
{
	int unit = UNIT(dev);
	struct ite_softc *ip = &ite_softc[unit];

	if (ip->flags & ITE_INITED)
		return;
	
	ip->curx = 0;
	ip->cury = 0;
	ip->cursorx = 0;
	ip->cursory = 0;

D 11
	(*itesw[ip->type].ite_init)(ip);
	(*itesw[ip->type].ite_cursor)(ip, DRAW_CURSOR);
E 11
I 11
	(*ip->isw->ite_init)(ip);
D 15
	(*ip->isw->ite_cursor)(ip, DRAW_CURSOR);
E 15
I 15
	ip->flags |= ITE_CURSORON;
	ite_drawcursor(ip, ip->isw);
E 15
E 11

	ip->attribute = 0;
	if (ip->attrbuf == NULL)
		ip->attrbuf = (u_char *)
			malloc(ip->rows * ip->cols, M_DEVBUF, M_WAITOK);
	bzero(ip->attrbuf, (ip->rows * ip->cols));

	ip->imode = 0;
	ip->flags |= ITE_INITED;
}

/*
 * "Shut down" device as terminal emulator.
 * Note that we do not deinit the console device unless forced.
 * Deinit'ing the console every time leads to a very active
 * screen when processing /etc/rc.
 */
iteoff(dev, flag)
	dev_t dev;
I 18
	int flag;
E 18
{
	register struct ite_softc *ip = &ite_softc[UNIT(dev)];

D 16
	if (flag & 2)
E 16
I 16
	if (flag & 2) {
E 16
		ip->flags |= ITE_INGRF;
I 16
		ip->flags &= ~ITE_CURSORON;
	}
E 16
	if ((ip->flags & ITE_ACTIVE) == 0)
		return;
	if ((flag & 1) ||
D 15
	    (ip->flags & (ITE_INGRF|ITE_ISCONS|ITE_INITED)) == ITE_INITED)
E 15
I 15
D 16
	    (ip->flags & (ITE_INGRF|ITE_ISCONS|ITE_INITED)) == ITE_INITED) {
E 16
I 16
	    (ip->flags & (ITE_INGRF|ITE_ISCONS|ITE_INITED)) == ITE_INITED)
E 16
E 15
D 11
		(*itesw[ip->type].ite_deinit)(ip);
E 11
I 11
		(*ip->isw->ite_deinit)(ip);
I 15
D 16
		ip->flags &= ~ITE_CURSORON;
	}
E 16
E 15
E 11
	if ((flag & 2) == 0)
		ip->flags &= ~ITE_ACTIVE;
}

D 5
/*ARGSUSED*/
iteopen(dev, flag)
E 5
I 5
/* ARGSUSED */
#ifdef __STDC__
iteopen(dev_t dev, int mode, int devtype, struct proc *p)
#else
iteopen(dev, mode, devtype, p)
E 5
	dev_t dev;
I 5
	int mode, devtype;
	struct proc *p;
#endif
E 5
{
	int unit = UNIT(dev);
	register struct tty *tp = &ite_tty[unit];
	register struct ite_softc *ip = &ite_softc[unit];
	register int error;
	int first = 0;

D 2
	if (tp->t_state&TS_XCLUDE && u.u_uid != 0)
E 2
I 2
	if ((tp->t_state&(TS_ISOPEN|TS_XCLUDE)) == (TS_ISOPEN|TS_XCLUDE)
D 5
	    && u.u_uid != 0)
E 5
I 5
	    && p->p_ucred->cr_uid != 0)
E 5
E 2
		return (EBUSY);
	if ((ip->flags & ITE_ACTIVE) == 0) {
		error = iteon(dev, 0);
		if (error)
			return (error);
		first = 1;
	}
	tp->t_oproc = itestart;
	tp->t_param = NULL;
	tp->t_dev = dev;
	if ((tp->t_state&TS_ISOPEN) == 0) {
		ttychars(tp);
		tp->t_iflag = TTYDEF_IFLAG;
		tp->t_oflag = TTYDEF_OFLAG;
		tp->t_cflag = CS8|CREAD;
		tp->t_lflag = TTYDEF_LFLAG;
		tp->t_ispeed = tp->t_ospeed = TTYDEF_SPEED;
		tp->t_state = TS_ISOPEN|TS_CARR_ON;
		ttsetwater(tp);
	}
	error = (*linesw[tp->t_line].l_open)(dev, tp);
	if (error == 0) {
		tp->t_winsize.ws_row = ip->rows;
		tp->t_winsize.ws_col = ip->cols;
	} else if (first)
		iteoff(dev, 0);
	return (error);
}

/*ARGSUSED*/
D 6
iteclose(dev, flag)
E 6
I 6
iteclose(dev, flag, mode, p)
E 6
	dev_t dev;
I 6
	int flag, mode;
	struct proc *p;
E 6
{
	register struct tty *tp = &ite_tty[UNIT(dev)];

D 6
	(*linesw[tp->t_line].l_close)(tp);
E 6
I 6
	(*linesw[tp->t_line].l_close)(tp, flag);
E 6
	ttyclose(tp);
	iteoff(dev, 0);
	return(0);
}

iteread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
I 18
	int flag;
E 18
{
	register struct tty *tp = &ite_tty[UNIT(dev)];

	return ((*linesw[tp->t_line].l_read)(tp, uio, flag));
}

itewrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
I 18
	int flag;
E 18
{
	int unit = UNIT(dev);
	register struct tty *tp = &ite_tty[unit];

	if ((ite_softc[unit].flags & ITE_ISCONS) && constty &&
	    (constty->t_state&(TS_CARR_ON|TS_ISOPEN))==(TS_CARR_ON|TS_ISOPEN))
		tp = constty;
	return ((*linesw[tp->t_line].l_write)(tp, uio, flag));
}

D 9
iteioctl(dev, cmd, addr, flag)
E 9
I 9
iteioctl(dev, cmd, addr, flag, p)
E 9
	dev_t dev;
I 9
D 19
	int cmd;
E 19
I 19
	u_long cmd;
E 19
E 9
	caddr_t addr;
I 9
	int flag;
	struct proc *p;
E 9
{
	register struct tty *tp = &ite_tty[UNIT(dev)];
	int error;

D 9
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, addr, flag);
E 9
I 9
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, addr, flag, p);
E 9
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, addr, flag);
	if (error >= 0)
		return (error);
	return (ENOTTY);
}

I 8
void
I 15
iterestart(tp)
	register struct tty *tp;
{
	register int s = splite();

	tp->t_state &= ~TS_TIMEOUT;
	itestart(tp);
	splx(s);
}

void
E 15
E 8
itestart(tp)
	register struct tty *tp;
{
	register int cc, s;
D 16
	int hiwat = 0;
E 16
I 16
	int hiwat = 0, hadcursor = 0;
E 16
I 15
	struct ite_softc *ip;
E 15

D 15
	s = spltty();
E 15
I 15
	/*
	 * (Potentially) lower priority.  We only need to protect ourselves
	 * from keyboard interrupts since that is all that can affect the
	 * state of our tty (kernel printf doesn't go through this routine).
	 */
	s = splite();
E 15
	if (tp->t_state & (TS_TIMEOUT|TS_BUSY|TS_TTSTOP)) {
		splx(s);
		return;
	}
	tp->t_state |= TS_BUSY;
	cc = tp->t_outq.c_cc;
	if (cc <= tp->t_lowat) {
		if (tp->t_state & TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
D 8
			wakeup(&tp->t_outq);
E 8
I 8
			wakeup((caddr_t)&tp->t_outq);
E 8
		}
D 10
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
E 10
I 10
		selwakeup(&tp->t_wsel);
E 10
	}
	/*
D 15
	 * Limit the amount of output we do in one burst
	 * to prevent hogging the CPU.
E 15
I 15
	 * Handle common (?) case
E 15
	 */
D 15
	if (cc > iteburst) {
		hiwat++;
		cc = iteburst;
	}
	while (--cc >= 0) {
		register int c;

		c = getc(&tp->t_outq);
E 15
I 15
	if (cc == 1) {
		iteputchar(getc(&tp->t_outq), tp->t_dev);
	} else if (cc) {
E 15
		/*
D 15
		 * iteputchar() may take a long time and we don't want to
		 * block all interrupts for long periods of time.  Since
		 * there is no need to stay at high priority while outputing
		 * the character (since we don't have to worry about
		 * interrupts), we don't.  We just need to make sure that
		 * we don't reenter iteputchar, which is guarenteed by the
		 * earlier setting of TS_BUSY.
E 15
I 15
		 * Limit the amount of output we do in one burst
		 * to prevent hogging the CPU.
E 15
		 */
D 15
		splx(s);
		iteputchar(c, tp->t_dev);
		spltty();
E 15
I 15
		if (cc > iteburst) {
			hiwat++;
			cc = iteburst;
		}
		/*
		 * Turn off cursor while we output multiple characters.
		 * Saves a lot of expensive window move operations.
		 */
		ip = &ite_softc[UNIT(tp->t_dev)];
D 16
		ite_erasecursor(ip, ip->isw);
		ip->flags &= ~ITE_CURSORON;
E 16
I 16
		if (ip->flags & ITE_CURSORON) {
			ite_erasecursor(ip, ip->isw);
			ip->flags &= ~ITE_CURSORON;
			hadcursor = 1;
		}
E 16
		while (--cc >= 0)
			iteputchar(getc(&tp->t_outq), tp->t_dev);
D 16
		ip->flags |= ITE_CURSORON;
		ite_drawcursor(ip, ip->isw);
E 16
I 16
		if (hadcursor) {
			ip->flags |= ITE_CURSORON;
			ite_drawcursor(ip, ip->isw);
		}
E 16
		if (hiwat) {
			tp->t_state |= TS_TIMEOUT;
			timeout(iterestart, tp, 1);
		}
E 15
	}
D 15
	if (hiwat) {
		tp->t_state |= TS_TIMEOUT;
		timeout(ttrstrt, tp, 1);
	}
E 15
	tp->t_state &= ~TS_BUSY;
	splx(s);
}

itefilter(stat, c)
D 18
     register char stat, c;
E 18
I 18
	register char stat, c;
E 18
{
	static int capsmode = 0;
	static int metamode = 0;
  	register char code, *str;

	if (kbd_tty == NULL)
		return;

	switch (c & 0xFF) {
	case KBD_CAPSLOCK:
		capsmode = !capsmode;
		return;

	case KBD_EXT_LEFT_DOWN:
	case KBD_EXT_RIGHT_DOWN:
		metamode = 1;
		return;
		
	case KBD_EXT_LEFT_UP:
	case KBD_EXT_RIGHT_UP:
		metamode = 0;
		return;
	}

	c &= KBD_CHARMASK;
	switch ((stat>>KBD_SSHIFT) & KBD_SMASK) {

	case KBD_KEY:
	        if (!capsmode) {
			code = kbd_keymap[c];
			break;
		}
D 18
		/* fall into... */
E 18
I 18
		/* FALLTHROUGH */
E 18

	case KBD_SHIFT:
		code = kbd_shiftmap[c];
		break;

	case KBD_CTRL:
		code = kbd_ctrlmap[c];
		break;
		
	case KBD_CTRLSHIFT:	
		code = kbd_ctrlshiftmap[c];
		break;
        }

	if (code == NULL && (str = kbd_stringmap[c]) != NULL) {
		while (*str)
			(*linesw[kbd_tty->t_line].l_rint)(*str++, kbd_tty);
	} else {
		if (metamode)
			code |= 0x80;
		(*linesw[kbd_tty->t_line].l_rint)(code, kbd_tty);
	}
}

iteputchar(c, dev)
	register int c;
	dev_t dev;  
{
	int unit = UNIT(dev);
	register struct ite_softc *ip = &ite_softc[unit];
D 11
	register struct itesw *sp = &itesw[ip->type];
E 11
I 11
	register struct itesw *sp = ip->isw;
E 11
	register int n;

	if ((ip->flags & (ITE_ACTIVE|ITE_INGRF)) != ITE_ACTIVE)
	  	return;

	if (ip->escape) {
doesc:
		switch (ip->escape) {

		case '&':			/* Next can be a,d, or s */
			if (ip->fpd++) {
				ip->escape = c;
				ip->fpd = 0;
			}
			return;

		case 'a':				/* cursor change */
			switch (c) {

			case 'Y':			/* Only y coord. */
D 13
				ip->cury = MIN(ip->pos, ip->rows-1);
E 13
I 13
				ip->cury = min(ip->pos, ip->rows-1);
E 13
				ip->pos = 0;
				ip->escape = 0;
D 15
				(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
				ite_movecursor(ip, sp);
E 15
				clr_attr(ip, ATTR_INV);
				break;

			case 'y':			/* y coord first */
D 13
				ip->cury = MIN(ip->pos, ip->rows-1);
E 13
I 13
				ip->cury = min(ip->pos, ip->rows-1);
E 13
				ip->pos = 0;
				ip->fpd = 0;
				break;

			case 'C':			/* x coord */
D 13
				ip->curx = MIN(ip->pos, ip->cols-1);
E 13
I 13
				ip->curx = min(ip->pos, ip->cols-1);
E 13
				ip->pos = 0;
				ip->escape = 0;
D 15
				(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
				ite_movecursor(ip, sp);
E 15
				clr_attr(ip, ATTR_INV);
				break;

			default:	     /* Possibly a 3 digit number. */
				if (c >= '0' && c <= '9' && ip->fpd < 3) {
					ip->pos = ip->pos * 10 + (c - '0');
					ip->fpd++;
				} else {
					ip->pos = 0;
					ip->escape = 0;
				}
				break;
			}
			return;

		case 'd':				/* attribute change */
			switch (c) {

			case 'B':
				set_attr(ip, ATTR_INV);
				break;
		        case 'D':
				/* XXX: we don't do anything for underline */
				set_attr(ip, ATTR_UL);
				break;
		        case '@':
				clr_attr(ip, ATTR_ALL);
				break;
			}
			ip->escape = 0;
			return;

		case 's':				/* keypad control */
			switch (ip->fpd) {

			case 0:
				ip->hold = c;
				ip->fpd++;
				return;

			case 1:
				if (c == 'A') {
					switch (ip->hold) {
	
					case '0':
						clr_attr(ip, ATTR_KPAD);
						break;
					case '1':
						set_attr(ip, ATTR_KPAD);
						break;
					}
				}
				ip->hold = 0;
			}
			ip->escape = 0;
			return;

		case 'i':			/* back tab */
			if (ip->curx > TABSIZE) {
				n = ip->curx - (ip->curx & (TABSIZE - 1));
				ip->curx -= n;
			} else
				ip->curx = 0;
D 15
			(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
			ite_movecursor(ip, sp);
E 15
			ip->escape = 0;
			return;

		case '3':			/* clear all tabs */
			goto ignore;

		case 'K':			/* clear_eol */
			ite_clrtoeol(ip, sp, ip->cury, ip->curx);
			ip->escape = 0;
			return;

		case 'J':			/* clear_eos */
			ite_clrtoeos(ip, sp);
			ip->escape = 0;
			return;

		case 'B':			/* cursor down 1 line */
			if (++ip->cury == ip->rows) {
				--ip->cury;
I 15
				ite_erasecursor(ip, sp);
E 15
				(*sp->ite_scroll)(ip, 1, 0, 1, SCROLL_UP);
				ite_clrtoeol(ip, sp, ip->cury, 0);
			}
			else
D 15
				(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
				ite_movecursor(ip, sp);
E 15
			clr_attr(ip, ATTR_INV);
			ip->escape = 0;
			return;

		case 'C':			/* cursor forward 1 char */
			ip->escape = 0;
			itecheckwrap(ip, sp);
			return;

		case 'A':			/* cursor up 1 line */
			if (ip->cury > 0) {
				ip->cury--;
D 15
				(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
				ite_movecursor(ip, sp);
E 15
			}
			ip->escape = 0;
			clr_attr(ip, ATTR_INV);
			return;

		case 'P':			/* delete character */
			ite_dchar(ip, sp);
			ip->escape = 0;
			return;

		case 'M':			/* delete line */
			ite_dline(ip, sp);
			ip->escape = 0;
			return;

		case 'Q':			/* enter insert mode */
			ip->imode = 1;
			ip->escape = 0;
			return;

		case 'R':			/* exit insert mode */
			ip->imode = 0;
			ip->escape = 0;
			return;

		case 'L':			/* insert blank line */
			ite_iline(ip, sp);
			ip->escape = 0;
			return;

		case 'h':			/* home key */
			ip->cury = ip->curx = 0;
D 15
			(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
			ite_movecursor(ip, sp);
E 15
			ip->escape = 0;
			return;

		case 'D':			/* left arrow key */
			if (ip->curx > 0) {
				ip->curx--;
D 15
				(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
				ite_movecursor(ip, sp);
E 15
			}
			ip->escape = 0;
			return;

		case '1':			/* set tab in all rows */
			goto ignore;

		case ESC:
			if ((ip->escape = c) == ESC)
				break;
			ip->fpd = 0;
			goto doesc;

		default:
ignore:
			ip->escape = 0;
			return;

		}
	}

	switch (c &= 0x7F) {

	case '\n':

		if (++ip->cury == ip->rows) {
			--ip->cury;
I 15
			ite_erasecursor(ip, sp);
E 15
			(*sp->ite_scroll)(ip, 1, 0, 1, SCROLL_UP);
			ite_clrtoeol(ip, sp, ip->cury, 0);
D 15
		}
		else
			(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
		} else
			ite_movecursor(ip, sp);
E 15
		clr_attr(ip, ATTR_INV);
		break;

	case '\r':
		if (ip->curx) {
			ip->curx = 0;
D 15
			(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
			ite_movecursor(ip, sp);
E 15
		}
		break;
	
	case '\b':
		if (--ip->curx < 0)
			ip->curx = 0;
		else
D 15
			(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
			ite_movecursor(ip, sp);
E 15
		break;

	case '\t':
		if (ip->curx < TABEND(unit)) {
			n = TABSIZE - (ip->curx & (TABSIZE - 1));
			ip->curx += n;
D 15
			(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
			ite_movecursor(ip, sp);
E 15
		} else
			itecheckwrap(ip, sp);
		break;

	case CTRL('G'):
		if (&ite_tty[unit] == kbd_tty)
D 11
			kbdbell();
E 11
I 11
			kbdbell(unit);
E 11
		break;

	case ESC:
		ip->escape = ESC;
		break;

	default:
		if (c < ' ' || c == DEL)
			break;
		if (ip->imode)
			ite_ichar(ip, sp);
		if ((ip->attribute & ATTR_INV) || attrtest(ip, ATTR_INV)) {
			attrset(ip, ATTR_INV);
			(*sp->ite_putc)(ip, c, ip->cury, ip->curx, ATTR_INV);
D 15
		}			
		else
E 15
I 15
		} else
E 15
			(*sp->ite_putc)(ip, c, ip->cury, ip->curx, ATTR_NOR);
D 15
		(*sp->ite_cursor)(ip, DRAW_CURSOR);
E 15
I 15
		ite_drawcursor(ip, sp);
E 15
		itecheckwrap(ip, sp);
		break;
	}
}

itecheckwrap(ip, sp)
     register struct ite_softc *ip;
     register struct itesw *sp;
{
	if (++ip->curx == ip->cols) {
		ip->curx = 0;
		clr_attr(ip, ATTR_INV);
		if (++ip->cury == ip->rows) {
			--ip->cury;
I 15
			ite_erasecursor(ip, sp);
E 15
			(*sp->ite_scroll)(ip, 1, 0, 1, SCROLL_UP);
			ite_clrtoeol(ip, sp, ip->cury, 0);
			return;
		}
	}
D 15
	(*sp->ite_cursor)(ip, MOVE_CURSOR);
E 15
I 15
	ite_movecursor(ip, sp);
E 15
}

ite_dchar(ip, sp)
     register struct ite_softc *ip;
     register struct itesw *sp;
{
D 15
	(*sp->ite_scroll)(ip, ip->cury, ip->curx + 1, 1, SCROLL_LEFT);
	attrmov(ip, ip->cury, ip->curx + 1, ip->cury, ip->curx,
		1, ip->cols - ip->curx - 1);
E 15
I 15
	if (ip->curx < ip->cols - 1) {
		ite_erasecursor(ip, sp);
		(*sp->ite_scroll)(ip, ip->cury, ip->curx + 1, 1, SCROLL_LEFT);
		attrmov(ip, ip->cury, ip->curx + 1, ip->cury, ip->curx,
			1, ip->cols - ip->curx - 1);
	}
E 15
	attrclr(ip, ip->cury, ip->cols - 1, 1, 1);
	(*sp->ite_putc)(ip, ' ', ip->cury, ip->cols - 1, ATTR_NOR);
D 15
	(*sp->ite_cursor)(ip, DRAW_CURSOR);
E 15
I 15
	ite_drawcursor(ip, sp);
E 15
}

ite_ichar(ip, sp)
     register struct ite_softc *ip;
     register struct itesw *sp;
{
D 15
	(*sp->ite_scroll)(ip, ip->cury, ip->curx, 1, SCROLL_RIGHT);
	attrmov(ip, ip->cury, ip->curx, ip->cury, ip->curx + 1,
		1, ip->cols - ip->curx - 1);
E 15
I 15
	if (ip->curx < ip->cols - 1) {
		ite_erasecursor(ip, sp);
		(*sp->ite_scroll)(ip, ip->cury, ip->curx, 1, SCROLL_RIGHT);
		attrmov(ip, ip->cury, ip->curx, ip->cury, ip->curx + 1,
			1, ip->cols - ip->curx - 1);
	}
E 15
	attrclr(ip, ip->cury, ip->curx, 1, 1);
	(*sp->ite_putc)(ip, ' ', ip->cury, ip->curx, ATTR_NOR);
D 15
	(*sp->ite_cursor)(ip, DRAW_CURSOR);
E 15
I 15
	ite_drawcursor(ip, sp);
E 15
}

ite_dline(ip, sp)
     register struct ite_softc *ip;
     register struct itesw *sp;
{
D 15
	(*sp->ite_scroll)(ip, ip->cury + 1, 0, 1, SCROLL_UP);
	attrmov(ip, ip->cury + 1, 0, ip->cury, 0,
		ip->rows - ip->cury - 1, ip->cols);
E 15
I 15
	if (ip->cury < ip->rows - 1) {
		ite_erasecursor(ip, sp);
		(*sp->ite_scroll)(ip, ip->cury + 1, 0, 1, SCROLL_UP);
		attrmov(ip, ip->cury + 1, 0, ip->cury, 0,
			ip->rows - ip->cury - 1, ip->cols);
	}
E 15
	ite_clrtoeol(ip, sp, ip->rows - 1, 0);
}

ite_iline(ip, sp)
     register struct ite_softc *ip;
     register struct itesw *sp;
{
D 15
	(*sp->ite_scroll)(ip, ip->cury, 0, 1, SCROLL_DOWN);
	attrmov(ip, ip->cury, 0, ip->cury + 1, 0,
		ip->rows - ip->cury - 1, ip->cols);
E 15
I 15
	if (ip->cury < ip->rows - 1) {
		ite_erasecursor(ip, sp);
		(*sp->ite_scroll)(ip, ip->cury, 0, 1, SCROLL_DOWN);
		attrmov(ip, ip->cury, 0, ip->cury + 1, 0,
			ip->rows - ip->cury - 1, ip->cols);
	}
E 15
	ite_clrtoeol(ip, sp, ip->cury, 0);
}

ite_clrtoeol(ip, sp, y, x)
     register struct ite_softc *ip;
     register struct itesw *sp;
     register int y, x;
{
	(*sp->ite_clear)(ip, y, x, 1, ip->cols - x);
	attrclr(ip, y, x, 1, ip->cols - x);
D 15
	(*sp->ite_cursor)(ip, DRAW_CURSOR);
E 15
I 15
	ite_drawcursor(ip, sp);
E 15
}

ite_clrtoeos(ip, sp)
     register struct ite_softc *ip;
     register struct itesw *sp;
{
	(*sp->ite_clear)(ip, ip->cury, 0, ip->rows - ip->cury, ip->cols);
	attrclr(ip, ip->cury, 0, ip->rows - ip->cury, ip->cols);
D 15
	(*sp->ite_cursor)(ip, DRAW_CURSOR);
E 15
I 15
	ite_drawcursor(ip, sp);
E 15
}

/*
 * Console functions
 */
D 4
#include "machine/cons.h"
E 4
I 4
D 11
#include "../hp300/cons.h"
E 4
#include "grfioctl.h"
#include "grfvar.h"
E 11
I 11
D 14
#include "cons.h"
E 14
I 14
#include <hp/dev/cons.h>
E 14
#ifdef hp300
D 14
#include "grfreg.h"
E 14
I 14
#include <hp/dev/grfreg.h>
E 14
#endif
E 11

#ifdef DEBUG
/*
 * Minimum ITE number at which to start looking for a console.
 * Setting to 0 will do normal search, 1 will skip first ITE device,
 * NITE will skip ITEs and use serial port.
 */
int	whichconsole = 0;
#endif

itecnprobe(cp)
	struct consdev *cp;
{
	register struct ite_softc *ip;
D 11
	int i, maj, unit, pri;
E 11
I 11
	int i, sw, maj, unit, pri;
E 11
D 5
	extern int iteopen();
E 5

	/* locate the major number */
	for (maj = 0; maj < nchrdev; maj++)
		if (cdevsw[maj].d_open == iteopen)
			break;

	/* urk! */
	grfconfig();

	/* check all the individual displays and find the best */
	unit = -1;
	pri = CN_DEAD;
	for (i = 0; i < NITE; i++) {
		struct grf_softc *gp = &grf_softc[i];

		ip = &ite_softc[i];
		if ((gp->g_flags & GF_ALIVE) == 0)
			continue;
		ip->flags = (ITE_ALIVE|ITE_CONSOLE);

D 11
		/* XXX - we need to do something about mapping these */
		switch (gp->g_type) {
E 11
I 11
		/* locate the proper switch table. */
		for (sw = 0; sw < nitesw; sw++)
			if (itesw[sw].ite_hwid == gp->g_sw->gd_hwid)
				break;
E 11

D 11
		case GT_TOPCAT:
		case GT_LRCATSEYE:
		case GT_HRCCATSEYE:
		case GT_HRMCATSEYE:
			ip->type = ITE_TOPCAT;
			break;
		case GT_GATORBOX:
			ip->type = ITE_GATORBOX;
			break;
		case GT_RENAISSANCE:
			ip->type = ITE_RENAISSANCE;
			break;
		case GT_DAVINCI:
			ip->type = ITE_DAVINCI;
			break;
		}
E 11
I 11
		if (sw == nitesw)
			continue;
E 11
#ifdef DEBUG
		if (i < whichconsole)
			continue;
#endif
I 11
		ip->isw = &itesw[sw];
		ip->grf = gp;
#ifdef hp300
E 11
		if ((int)gp->g_display.gd_regaddr == GRFIADDR) {
			pri = CN_INTERNAL;
			unit = i;
		} else if (unit < 0) {
			pri = CN_NORMAL;
			unit = i;
		}
I 11
#endif
#ifdef hp800
		/* XXX use the first one for now */
		if (unit < 0) {
			pri = CN_INTERNAL;
			unit = i;
		}
#endif
E 11
	}

	/* initialize required fields */
	cp->cn_dev = makedev(maj, unit);
	cp->cn_tp = &ite_tty[unit];
	cp->cn_pri = pri;
}

itecninit(cp)
	struct consdev *cp;
{
	int unit = UNIT(cp->cn_dev);
	struct ite_softc *ip = &ite_softc[unit];

	ip->attrbuf = console_attributes;
	iteinit(cp->cn_dev);
	ip->flags |= (ITE_ACTIVE|ITE_ISCONS);
	kbd_tty = &ite_tty[unit];
}

/*ARGSUSED*/
itecngetc(dev)
	dev_t dev;
{
	register int c;
	int stat;

D 11
	c = kbdgetc(&stat);
E 11
I 11
	c = kbdgetc(0, &stat);	/* XXX always read from keyboard 0 for now */
E 11
	switch ((stat >> KBD_SSHIFT) & KBD_SMASK) {
	case KBD_SHIFT:
		c = kbd_shiftmap[c & KBD_CHARMASK];
		break;
	case KBD_CTRL:
		c = kbd_ctrlmap[c & KBD_CHARMASK];
		break;
	case KBD_KEY:
		c = kbd_keymap[c & KBD_CHARMASK];
		break;
	default:
		c = 0;
		break;
	}
	return(c);
}

itecnputc(dev, c)
	dev_t dev;
	int c;
{
	static int paniced = 0;
	struct ite_softc *ip = &ite_softc[UNIT(dev)];
D 7
	extern char *panicstr;
E 7

	if (panicstr && !paniced &&
	    (ip->flags & (ITE_ACTIVE|ITE_INGRF)) != ITE_ACTIVE) {
		(void) iteon(dev, 3);
		paniced = 1;
	}
	iteputchar(c, dev);
}
#endif
E 1
