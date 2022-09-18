h07525
s 00002/00002/00838
d D 8.1 93/06/11 15:54:28 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00016/00823
d D 5.15 92/10/11 10:20:12 bostic 15 14
c make kernel includes standard
e
s 00002/00001/00837
d D 5.14 92/05/20 16:56:57 bostic 14 13
c Don't call linesw[].l_rint until the console is really opened
c (from 386bsd).  apparently, this fixes a panic caused by typing on the
c console while booting.  from Pace Willisson (pace@blitz.com)
e
s 00004/00002/00834
d D 5.13 92/02/28 18:45:11 sklower 13 12
c add proc argument to ioctl among others
e
s 00012/00016/00824
d D 5.12 92/02/25 14:06:06 torek 12 11
c convert to use new select interface, selrecord/selwakeup
c also fix indentation (style police)
e
s 00001/00003/00839
d D 5.11 91/05/21 10:43:14 bostic 11 10
c format polic
e
s 00004/00002/00838
d D 5.10 91/05/16 17:42:35 marc 10 9
c pass flags through device close
e
s 00001/00001/00839
d D 5.9 91/05/12 17:52:46 william 9 8
c remove obscure debugging flag
e
s 00114/00054/00726
d D 5.8 91/05/09 21:20:28 william 8 7
c name changed to allow support of virtual console code, other
c changes due to new devswtch parameter list
e
s 00131/00093/00649
d D 5.7 91/05/09 20:36:04 william 7 6
c interim version, changes for net2 tape
e
s 00002/00002/00740
d D 5.6 91/02/26 13:47:20 william 6 5
c nulldev() -> nullop()
e
s 00000/00000/00742
d D 5.5 91/01/08 19:31:50 william 5 4
c reno changes
e
s 00001/00001/00741
d D 5.4 90/11/18 11:31:56 bill 4 3
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00082/00058/00660
d D 5.3 90/11/08 19:26:07 bill 3 2
c autoconf, do vga first, fix cursor, update at clock, add atribs
e
s 00300/00125/00418
d D 5.2 90/06/23 18:36:54 donahn 2 1
c Added support for ibmpc term type and improved keyboard support.
e
s 00543/00000/00000
d D 5.1 90/04/24 12:59:17 william 1 0
c date and time created 90/04/24 12:59:17 by william
e
u
U
t
T
I 1
/*-
D 16
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * This code is derived from software contributed to Berkeley by
D 11
 * William Jolitz.
 *
I 8
 * Added support for ibmpc term type and improved keyboard support. -Don Ahn
E 11
I 11
 * William Jolitz and Don Ahn.
E 11
 *
E 8
I 2
D 7
 * Added support for ibmpc term type and improved keyboard support. -Don Ahn
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
E 2
D 7
 * %sccs.include.386.c%
 *
E 7
 *	%W% (Berkeley) %G%
 */

/*
D 8
 * code to work keyboard & display for console
E 8
I 8
 * code to work keyboard & display for PC-style console
E 8
 */
D 15
#include "param.h"
#include "conf.h"
D 7
#include "dir.h"
E 7
#include "ioctl.h"
D 7
#include "user.h"
E 7
#include "proc.h"
I 7
#include "user.h"
E 7
#include "tty.h"
#include "uio.h"
I 2
D 3
#include "machine/device.h"
E 3
I 3
D 4
#include "machine/isa/device.h"
E 4
I 4
D 7
#include "machine/isa/isa_device.h"
E 7
I 7
#include "i386/isa/isa_device.h"
E 7
E 4
E 3
E 2
#include "callout.h"
#include "systm.h"
#include "kernel.h"
#include "syslog.h"
D 7
#include "icu.h"
E 7
I 7
#include "i386/isa/icu.h"
I 8
#include "i386/i386/cons.h"
E 15
I 15
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/tty.h>
#include <sys/uio.h>
#include <sys/callout.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
E 15
E 8
E 7

I 15
#include <i386/isa/isa_device.h>
#include <i386/isa/icu.h>
#include <i386/i386/cons.h>

E 15
D 8
struct	tty cons;
E 8
I 8
struct	tty pccons;
E 8

D 8
struct	consoftc {
E 8
I 8
struct	pcconsoftc {
E 8
	char	cs_flags;
#define	CSF_ACTIVE	0x1	/* timeout active */
#define	CSF_POLLING	0x2	/* polling for input */
	char	cs_lastc;	/* last char sent */
	int	cs_timo;	/* timeouts since interrupt */
	u_long	cs_wedgecnt;	/* times restarted */
D 8
} consoftc;
E 8
I 8
} pcconsoftc;
E 8

I 2
D 8
int cnprobe(), cnattach();
E 8
I 8
int pcprobe(), pcattach();
E 8

D 3
struct	driver cndriver = {
E 3
I 3
D 8
struct	isa_driver cndriver = {
E 3
	cnprobe, cnattach, "cn",
E 8
I 8
struct	isa_driver pcdriver = {
	pcprobe, pcattach, "pc",
E 8
};

I 3
#define	COL		80
#define	ROW		25
#define	CHR		2
#define MONO_BASE	0x3B4
D 7
#define MONO_BUF	0xB0000
E 7
I 7
#define MONO_BUF	0xfe0B0000
E 7
#define CGA_BASE	0x3D4
D 7
#define CGA_BUF		0xB8000
E 7
I 7
#define CGA_BUF		0xfe0B8000
E 7
#define IOPHYSMEM	0xA0000

u_char	color = 0xe ;
static unsigned int addr_6845 = MONO_BASE;
u_short *Crtat = (u_short *)MONO_BUF;
I 7
static openf;
E 7

E 3
E 2
D 7
/*
 * We check the console periodically to make sure
 * that it hasn't wedged.  Unfortunately, if an XOFF
 * is typed on the console, that can't be distinguished
 * from more catastrophic failure.
 */
#define	CN_TIMERVAL	(hz)		/* frequency at which to check cons */
#define	CN_TIMO		(2*60)		/* intervals to allow for output char */

E 7
D 8
int	cnstart();
I 7
int	cnparam();
E 8
I 8
/*
 * We check the console periodically to make sure
 * that it hasn't wedged.  Unfortunately, if an XOFF
 * is typed on the console, that can't be distinguished
 * from more catastrophic failure.
 */
#define	CN_TIMERVAL	(hz)		/* frequency at which to check cons */
#define	CN_TIMO		(2*60)		/* intervals to allow for output char */

int	pcstart();
int	pcparam();
E 8
E 7
int	ttrstrt();
char	partab[];
I 8

/*
 * Wait for CP to accept last CP command sent
 * before setting up next command.
 */
#define	waitforlast(timo) { \
	if (pclast) { \
		(timo) = 10000; \
		do \
			uncache((char *)&pclast->cp_unit); \
		while ((pclast->cp_unit&CPTAKE) == 0 && --(timo)); \
	} \
}

E 8
D 7

/*
 * Wait for CP to accept last CP command sent
 * before setting up next command.
 */
#define	waitforlast(timo) { \
	if (cnlast) { \
		(timo) = 10000; \
		do \
			uncache((char *)&cnlast->cp_unit); \
		while ((cnlast->cp_unit&CPTAKE) == 0 && --(timo)); \
	} \
}

E 7
u_char inb();

I 2
D 8
cnprobe(dev)
E 8
I 8
pcprobe(dev)
E 8
D 3
struct device *dev;
E 3
I 3
struct isa_device *dev;
E 3
{
	u_char c;
	int again = 0;

	/* Enable interrupts and keyboard controller */
	while (inb(0x64)&2); outb(0x64,0x60);
	while (inb(0x64)&2); outb(0x60,0x4D);

	/* Start keyboard stuff RESET */
	while (inb(0x64)&2);	/* wait input ready */
	outb(0x60,0xFF);	/* RESET */
	while((c=inb(0x60))!=0xFA) {
		if ((c == 0xFE) ||  (c == 0xFF)) {
			if(!again)printf("KEYBOARD disconnected: RECONNECT \n");
			while (inb(0x64)&2);	/* wait input ready */
			outb(0x60,0xFF);	/* RESET */
			again = 1;
		}
	}
D 3
	if (again) printf("KEYBOARD Reconnected\n");
E 3
	/* pick up keyboard reset return code */
D 3
	sgetc(1);
E 3
I 3
D 6
	while((c=inb(0x60))!=0xAA)nulldev();
E 6
I 6
D 7
	while((c=inb(0x60))!=0xAA)nullop();
E 7
I 7
	while((c=inb(0x60))!=0xAA);
E 7
E 6
E 3
	return 1;
}

D 8
cnattach(dev)
E 8
I 8
pcattach(dev)
E 8
D 3
struct device *dev;
E 3
I 3
struct isa_device *dev;
E 3
{
D 3
	INTREN(IRQ1);
E 3
I 3
	u_short *cp = Crtat + (CGA_BUF-MONO_BUF)/CHR;
	u_short was;

	/* Crtat initialized to point to MONO buffer   */
	/* if not present change to CGA_BUF offset     */
	/* ONLY ADD the difference since locore.s adds */
	/* in the remapped offset at the right time    */

	was = *Crtat;
	*Crtat = (u_short) 0xA55A;
	if (*Crtat != 0xA55A)
		printf("<mono>");
	else	printf("<color>");
	*Crtat = was;
I 7
	cursor();
E 7
E 3
}

E 2
D 7
/*ARGSUSED*/
cnopen(dev, flag)
E 7
I 7
/* ARGSUSED */
#ifdef __STDC__
D 8
cnopen(dev_t dev, int flag, int mode, struct proc *p)
E 8
I 8
pcopen(dev_t dev, int flag, int mode, struct proc *p)
E 8
#else
D 8
cnopen(dev, flag, mode, p)
E 8
I 8
pcopen(dev, flag, mode, p)
E 8
E 7
	dev_t dev;
I 7
	int flag, mode;
	struct proc *p;
#endif
E 7
{
	register struct tty *tp;
D 7
	int unit = minor(dev);
E 7

D 8
	tp = &cons;
D 7
	if (tp->t_state&TS_XCLUDE && u.u_uid != 0)
		return (EBUSY);
E 7
	tp->t_oproc = cnstart;
D 7
	if ((tp->t_state&TS_ISOPEN) == 0) {
E 7
I 7
	tp->t_param = cnparam;
E 8
I 8
	tp = &pccons;
	tp->t_oproc = pcstart;
	tp->t_param = pcparam;
E 8
	tp->t_dev = dev;
	openf++;
	if ((tp->t_state & TS_ISOPEN) == 0) {
		tp->t_state |= TS_WOPEN;
E 7
		ttychars(tp);
D 7
		tp->t_state = TS_ISOPEN|TS_CARR_ON;
		tp->t_flags = EVENP|ECHO|XTABS|CRMOD;
D 2
		INTREN(IRQ1);
E 2
		splnone();
	}
E 7
I 7
		tp->t_iflag = TTYDEF_IFLAG;
		tp->t_oflag = TTYDEF_OFLAG;
		tp->t_cflag = TTYDEF_CFLAG;
		tp->t_lflag = TTYDEF_LFLAG;
		tp->t_ispeed = tp->t_ospeed = TTYDEF_SPEED;
D 8
		cnparam(tp, &tp->t_termios);
E 8
I 8
		pcparam(tp, &tp->t_termios);
E 8
		ttsetwater(tp);
	} else if (tp->t_state&TS_XCLUDE && p->p_ucred->cr_uid != 0)
		return (EBUSY);
	tp->t_state |= TS_CARR_ON;
E 7
	return ((*linesw[tp->t_line].l_open)(dev, tp));
}

D 7

cnclose(dev)
E 7
I 7
D 8
cnclose(dev, flag)
E 8
I 8
D 10
pcclose(dev, flag)
E 10
I 10
pcclose(dev, flag, mode, p)
E 10
E 8
E 7
	dev_t dev;
I 10
	int flag, mode;
	struct proc *p;
E 10
{
D 8
	(*linesw[cons.t_line].l_close)(&cons);
	ttyclose(&cons);
E 8
I 8
D 10
	(*linesw[pccons.t_line].l_close)(&pccons);
E 10
I 10
	(*linesw[pccons.t_line].l_close)(&pccons, flag);
E 10
	ttyclose(&pccons);
E 8
I 7
	return(0);
E 7
D 3
	INTRDIS(IRQ1);
E 3
}

/*ARGSUSED*/
D 7
cnread(dev, uio)
E 7
I 7
D 8
cnread(dev, uio, flag)
E 8
I 8
pcread(dev, uio, flag)
E 8
E 7
	dev_t dev;
	struct uio *uio;
{
D 7
	return ((*linesw[cons.t_line].l_read)(&cons, uio));
E 7
I 7
D 8
	return ((*linesw[cons.t_line].l_read)(&cons, uio, flag));
E 8
I 8
	return ((*linesw[pccons.t_line].l_read)(&pccons, uio, flag));
E 8
E 7
}

/*ARGSUSED*/
D 7
cnwrite(dev, uio)
E 7
I 7
D 8
cnwrite(dev, uio, flag)
E 8
I 8
pcwrite(dev, uio, flag)
E 8
E 7
	dev_t dev;
	struct uio *uio;
{
D 7
	return ((*linesw[cons.t_line].l_write)(&cons, uio));
E 7
I 7
D 8
	return ((*linesw[cons.t_line].l_write)(&cons, uio, flag));
E 8
I 8
	return ((*linesw[pccons.t_line].l_write)(&pccons, uio, flag));
E 8
E 7
}

/*
 * Got a console receive interrupt -
 * the console processor wants to give us a character.
 * Catch the character, and see who it goes to.
 */
D 3
cnrint(dev)
E 3
I 3
D 8
cnrint(dev, irq, cpl)
E 8
I 8
pcrint(dev, irq, cpl)
E 8
E 3
	dev_t dev;
{
	int c;

	c = sgetc(1);
D 3
	if (c&0x100)return;
E 3
I 3
	if (c&0x100) return;
E 3
D 8
	if (consoftc.cs_flags&CSF_POLLING)
E 8
I 8
	if (pcconsoftc.cs_flags&CSF_POLLING)
E 8
		return;
#ifdef KDB
D 8
	if (kdbrintr(c, &cons))
E 8
I 8
	if (kdbrintr(c, &pccons))
E 8
		return;
#endif
D 8
	(*linesw[cons.t_line].l_rint)(c&0xff, &cons);
E 8
I 8
D 14
	(*linesw[pccons.t_line].l_rint)(c&0xff, &pccons);
E 14
I 14
	if (openf) /* 386bsd */
		(*linesw[pccons.t_line].l_rint)(c&0xff, &pccons);
E 14
E 8
}

D 7
cnioctl(dev, cmd, addr, flag)
E 7
I 7
D 8
cnioctl(dev, cmd, data, flag)
E 8
I 8
D 13
pcioctl(dev, cmd, data, flag)
E 13
I 13
pcioctl(dev, cmd, data, flag, p)
E 13
E 8
E 7
	dev_t dev;
I 13
	int cmd, flag;
E 13
D 7
	caddr_t addr;
E 7
I 7
	caddr_t data;
I 13
	struct proc *p;
E 13
E 7
{
D 8
	register struct tty *tp = &cons;
E 8
I 8
	register struct tty *tp = &pccons;
E 8
	register error;
 
D 7
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, addr);
E 7
I 7
D 13
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
E 13
I 13
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag, p);
E 13
E 7
	if (error >= 0)
D 7
		return error;
	if ((error = ttioctl(tp, cmd, addr, flag)) < 0)
		error = ENOTTY;
	else if (cmd == TIOCSETP || cmd == TIOCSETN)
		cnparams(tp);
	return (error);
E 7
I 7
		return (error);
	error = ttioctl(tp, cmd, data, flag);
	if (error >= 0)
		return (error);
	return (ENOTTY);
E 7
}

D 7
int	consintr = 1;
E 7
I 7
D 8
extern int	consintr ;
E 8
I 8
int	pcconsintr = 1;
E 8
E 7
/*
 * Got a console transmission interrupt -
 * the console processor wants another character.
 */
D 8
cnxint(dev)
E 8
I 8
pcxint(dev)
E 8
	dev_t dev;
{
	register struct tty *tp;
	register int unit;

D 8
	if (!consintr)
E 8
I 8
	if (!pcconsintr)
E 8
		return;
D 8
	cons.t_state &= ~TS_BUSY;
	consoftc.cs_timo = 0;
	if (cons.t_line)
		(*linesw[cons.t_line].l_start)(&cons);
E 8
I 8
	pccons.t_state &= ~TS_BUSY;
	pcconsoftc.cs_timo = 0;
	if (pccons.t_line)
		(*linesw[pccons.t_line].l_start)(&pccons);
E 8
	else
D 8
		cnstart(&cons);
E 8
I 8
		pcstart(&pccons);
E 8
}

D 8
cnstart(tp)
E 8
I 8
pcstart(tp)
E 8
	register struct tty *tp;
{
	register c, s;

	s = spltty();
	if (tp->t_state & (TS_TIMEOUT|TS_BUSY|TS_TTSTOP))
		goto out;
D 7
	if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
E 7
I 7
	do {
D 12
	if (tp->t_outq.c_cc <= tp->t_lowat) {
E 7
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
E 12
I 12
		if (tp->t_outq.c_cc <= tp->t_lowat) {
			if (tp->t_state&TS_ASLEEP) {
				tp->t_state &= ~TS_ASLEEP;
				wakeup((caddr_t)&tp->t_outq);
			}
			selwakeup(&tp->t_wsel);
E 12
		}
D 12
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
	}
D 7
	while (tp->t_outq.c_cc != 0) {
		c = getc(&tp->t_outq) & 0xff;
		if ((tp->t_flags & (RAW|LITOUT)) == 0) {
			if (c > 0177)
			{
				timeout(ttrstrt, (caddr_t)tp, (c&0177));
				tp->t_state |= TS_TIMEOUT;
				break;
			}
			c &= 0177;
		}
D 2
		sput(c,0xc);
E 2
I 2
		splx(s);
		sput(c,0x7);
		s = spltty();
E 2
	}
E 7
I 7
	if (tp->t_outq.c_cc == 0)
		goto out;
	c = getc(&tp->t_outq);
	splx(s);
	sput(c,0x7);
	s = spltty();
E 12
I 12
		if (tp->t_outq.c_cc == 0)
			goto out;
		c = getc(&tp->t_outq);
		splx(s);
		sput(c, 0x7);
		s = spltty();
E 12
	} while(1);
E 7
out:
	splx(s);
}

I 8
pccnprobe(cp)
	struct consdev *cp;
{
	int maj;
	extern int pcopen();

	/* locate the major number */
	for (maj = 0; maj < nchrdev; maj++)
		if (cdevsw[maj].d_open == pcopen)
			break;

	/* initialize required fields */
	cp->cn_dev = makedev(maj, 0);
	cp->cn_tp = &pccons;
	cp->cn_pri = CN_INTERNAL;
}

/* ARGSUSED */
pccninit(cp)
	struct consdev *cp;
{
	/*
	 * For now, don't screw with it.
	 */
	/* crtat = 0; */
}

E 8
I 7
static __color;

E 7
D 8
cnputc(c)
E 8
I 8
/* ARGSUSED */
pccnputc(dev, c)
	dev_t dev;
E 8
	char c;
D 7
{
E 7
I 7
D 8
{	int clr;
	clr = __color;
	if (clr == 0) clr = 0x30;
	else clr |= 0x60;
E 8
I 8
{
	int clr = __color;

	if (clr == 0)
		clr = 0x30;
	else
		clr |= 0x60;
E 8
E 7
D 2

E 2
	if (c == '\n')
D 2
		sput('\r',0xb);
	sput(c, 0xb);
E 2
I 2
D 7
		sput('\r',0x3);
	sput(c, 0x3);
E 7
I 7
D 8
		sput('\r',clr);
E 8
I 8
		sput('\r', clr);
E 8
	sput(c, clr);
E 7
E 2
}

/*
 * Print a character on console.
 */
D 8
cnputchar(c, tp)
E 8
I 8
pcputchar(c, tp)
E 8
	char c;
	register struct tty *tp;
{
D 2
	sput(c,0xa);
E 2
I 2
	sput(c,0x2);
E 2
	if (c=='\n') getchar();
}


D 8
cngetc()
E 8
I 8
/* ARGSUSED */
pccngetc(dev)
	dev_t dev;
E 8
{
	register int c, s;

D 8
	s = spltty();		/* block cnrint while we poll */
E 8
I 8
	s = spltty();		/* block pcrint while we poll */
E 8
D 2
	if (c == '\r')
		c = '\n';
E 2
I 2
	c = sgetc(0);
	if (c == '\r') c = '\n';
E 2
	splx(s);
	return (c);
}

D 8
cngetchar(tp)
E 8
I 8
pcgetchar(tp)
E 8
	register struct tty *tp;
{
	int c;

	c = sgetc(0);
	return (c&0xff);
}

/*
 * Set line parameters
 */
D 7
cnparams(tp)
E 7
I 7
D 8
cnparam(tp, t)
E 8
I 8
pcparam(tp, t)
E 8
E 7
	register struct tty *tp;
I 7
	register struct termios *t;
E 7
{
I 7
	register int cflag = t->c_cflag;
        /* and copy to tty */
        tp->t_ispeed = t->c_ispeed;
        tp->t_ospeed = t->c_ospeed;
        tp->t_cflag = cflag;

	return(0);
E 7
}

#ifdef KDB
/*
 * Turn input polling on/off (used by debugger).
 */
D 8
cnpoll(onoff)
E 8
I 8
pcpoll(onoff)
E 8
	int onoff;
{
}
#endif

D 2
#define	CRT_TXTADDR	Crtat
E 2
I 2
extern int hz;

I 7
static beeping;
E 7
sysbeepstop()
{
	/* disable counter 2 */
	outb(0x61,inb(0x61)&0xFC);
I 7
	beeping = 0;
E 7
}

sysbeep()
{
I 7

E 7
	/* enable counter 2 */
	outb(0x61,inb(0x61)|3);
	/* set command for counter 2, 2 byte write */
	outb(0x43,0xB6);
	/* send 0x637 for 750 HZ */
	outb(0x42,0x37);
	outb(0x42,0x06);
D 7
	timeout(sysbeepstop,0,hz/4);
E 7
I 7
	if(!beeping)timeout(sysbeepstop,0,hz/4);
	beeping = 1;
E 7
}

E 2
D 3
#define	COL		80
#define	ROW		25
#define	CHR		2
I 2
#define MONO_BASE	0x3B4
#define MONO_BUF	0xB0000
#define CGA_BASE	0x3D4
#define CGA_BUF		0xB8000
#define IOPHYSMEM	0xA0000
E 3
I 3
/* cursor() sets an offset (0-1999) into the 80x25 text area    */
E 3
E 2

D 2

u_short *Crtat = ((u_short *)0xb8000);
u_short	*crtat ;
E 2
D 3
u_char	color = 0xe ;
D 2
int row;
E 2
I 2
static unsigned int addr_6845;
u_short *Crtat = (u_short *)MONO_BUF;
E 3
I 3
static u_short *crtat = 0;
char bg_at = 0x0f;
char so_at = 0x70;
E 3
E 2

D 2
sput(c, ca) u_char c, ca; {
E 2
I 2
D 3
/* cursor() sets an offset (0-1999) into the 80x25 text area    */
/* Theoretically there should be a slight delay between outb's  */
/* and if your display has cursor problems that may be it.      */
/* This may have to be left as is since it is done after every  */
/* char and can seriously affect performance .                  */
E 3
I 3
cursor()
{ 	int pos = crtat - Crtat;
E 3
E 2

D 2
	if(inb(0x64)&2 == 0)sgetc(1);
E 2
I 2
D 3
cursor(pos)
int pos;
{
E 3
	outb(addr_6845,14);
	outb(addr_6845+1,pos >> 8);
	outb(addr_6845,15);
	outb(addr_6845+1,pos&0xff);
I 7
	timeout(cursor,0,hz/10);
E 7
}

I 7
u_char shfts, ctls, alts, caps, num, stp, scroll;

/*
 * Compensate for abysmally stupid frame buffer aribitration with macro
 */
#define	wrtchar(c) { do *crtat = (c); while ((c) != *crtat); crtat++; row++; }

E 7
/* sput has support for emulation of the 'ibmpc' termcap entry. */
/* This is a bare-bones implementation of a bare-bones entry    */
/* One modification: Change li#24 to li#25 to reflect 25 lines  */
D 3
/* sput tries to do 16-bit writes.  This may not work on all.   */
E 3

sput(c, ca)
u_char c, ca;
{

	static int esc,ebrac,eparm,cx,cy,row,so;
D 3
	static u_short *crtat = 0;
	int s;
E 3

D 3
	s = splnone();

/*
	if(inb(0x64)&1)sgetc(1);
*/
E 3
E 2
	if (crtat == 0) {
I 3
		u_short *cp = Crtat + (CGA_BUF-MONO_BUF)/CHR, was;
		unsigned cursorat;
E 3
D 2
		INTREN(IRQ1); /* XXX */
		crtat = CRT_TXTADDR; bzero (crtat,COL*ROW*CHR);
E 2
I 2

		/* Crtat initialized to point to MONO buffer   */
		/* if not present change to CGA_BUF offset     */
		/* ONLY ADD the difference since locore.s adds */
		/* in the remapped offset at the right time    */

D 3
		*Crtat = (u_short) 0xA55A;
		if (*Crtat != 0xA55A) {
			Crtat = Crtat + (CGA_BUF-MONO_BUF)/CHR;
E 3
I 3
		was = *cp;
		*cp = (u_short) 0xA55A;
		if (*cp != 0xA55A) {
			addr_6845 = MONO_BASE;
		} else {
			*cp = was;
E 3
			addr_6845 = CGA_BASE;
D 3
		} else addr_6845 = MONO_BASE;
		crtat = Crtat; bzero (crtat,COL*ROW*CHR);
E 3
I 3
			Crtat = Crtat + (CGA_BUF-MONO_BUF)/CHR;
		}
		/* Extract cursor location */
		outb(addr_6845,14);
		cursorat = inb(addr_6845+1)<<8 ;
		outb(addr_6845,15);
		cursorat |= inb(addr_6845+1);

		crtat = Crtat + cursorat;
		fillw((bg_at<<8)|' ', crtat, COL*ROW-cursorat);
E 3
E 2
	}
D 2
	/*if (crtat >= (CRT_TXTADDR+COL*(ROW-1))) {
		crtat = CRT_TXTADDR+COL*(ROW-1); row = 0;
	}*/
		if (crtat >= CRT_TXTADDR+COL*(ROW-1)) { /* scroll */
			bcopy(CRT_TXTADDR+COL, CRT_TXTADDR,COL*(ROW-1)*CHR);
			bzero (CRT_TXTADDR+COL*(ROW-1),COL*CHR) ;
			crtat -= COL ;
		}
E 2
	switch(c) {
I 2
	case 0x1B:
		esc = 1; ebrac = 0; eparm = 0;
		break;
E 2

	case '\t':
		do {
D 7
			*crtat++ = (ca<<8)| ' '; row++ ;
		} while (row %8);
E 7
I 7
			wrtchar((ca<<8)| ' ');
		} while (row % 8);
E 7
		break;

	case '\010':
		crtat--; row--;
I 2
		if (row < 0) row += COL;  /* non-destructive backspace */
E 2
		break;

	case '\r':
D 2
		/*bzero (crtat,(COL-row)*CHR) ;*/ crtat -= row ; row = 0;
E 2
I 2
		crtat -= row ; row = 0;
E 2
		break;

	case '\n':
D 2
		if (crtat >= CRT_TXTADDR+COL*(ROW-1)) { /* scroll */
			bcopy(CRT_TXTADDR+COL, CRT_TXTADDR,COL*(ROW-1)*CHR);
			bzero (CRT_TXTADDR+COL*(ROW-1),COL*CHR) ;
			crtat -= COL ;
		}
E 2
		crtat += COL ;
		break;

	default:
D 2
		*crtat++ = (ca<<8)| c; row++ ;
		if (row >= COL) {
		/*bzero (crtat,(COL-row)*CHR) ;*/ crtat -= row ; row = 0;
		if (crtat >= CRT_TXTADDR+COL*(ROW-1)) { /* scroll */
			bcopy(CRT_TXTADDR+COL, CRT_TXTADDR,COL*(ROW-1)*CHR);
			bzero (CRT_TXTADDR+COL*(ROW-1),COL*CHR) ;
			crtat -= COL ;
E 2
I 2
		if (esc) {
			if (ebrac) {
				switch(c) {
				case 'm': /* no support for standout */
					if (!cx) so = 0;
					else so = 1;
					esc = 0; ebrac = 0; eparm = 0;
					break;
				case 'A': /* back one row */
					crtat -= COL;
					esc = 0; ebrac = 0; eparm = 0;
					break;
				case 'B': /* down one row */
					crtat += COL;
					esc = 0; ebrac = 0; eparm = 0;
					break;
				case 'C': /* right cursor */
					crtat++; row++;
					esc = 0; ebrac = 0; eparm = 0;
					break;
				case 'J': /* Clear to end of display */
D 3
					bzero(crtat,(Crtat+COL*ROW-crtat)*CHR);
E 3
I 3
					fillw((bg_at<<8)+' ', crtat,
						Crtat+COL*ROW-crtat);
E 3
					esc = 0; ebrac = 0; eparm = 0;
					break;
				case 'K': /* Clear to EOL */
D 3
					bzero(crtat,(COL-row)*CHR);
E 3
I 3
D 7
					fillw((bg_at<<8)+' ', crtat, COL-row);
E 7
I 7
					fillw((bg_at<<8)+' ', crtat,
						COL-(crtat-Crtat)%COL);
E 7
E 3
					esc = 0; ebrac = 0; eparm = 0;
					break;
				case 'H': /* Cursor move */
					if ((!cx)||(!cy)) {
						crtat = Crtat;
						row = 0;
					} else {
						crtat = Crtat+(cx-1)*COL+cy-1;
						row = cy-1;
					}
					esc = 0; ebrac = 0; eparm = 0;
					break;
				case ';': /* Switch params in cursor def */
					eparm = 1;
D 3
					splx(s);
E 3
					return;
				default: /* Only numbers valid here */
					if ((c >= '0')&&(c <= '9')) {
						if (eparm) {
							cy *= 10;
							cy += c - '0';
						} else {
							cx *= 10;
							cx += c - '0';
						}
					} else {
						esc = 0; ebrac = 0; eparm = 0;
					}
D 3
					splx(s);
E 3
					return;
				}
				break;
			} else if (c == 'c') { /* Clear screen & home */
D 3
				bzero(Crtat,COL*ROW*CHR);
E 3
I 3
				fillw((bg_at<<8)+' ', Crtat,COL*ROW);
E 3
				crtat = Crtat; row = 0;
				esc = 0; ebrac = 0; eparm = 0;
D 3
			}else if (c == '[') { /* Start ESC [ sequence */
E 3
I 3
			} else if (c == '[') { /* Start ESC [ sequence */
E 3
				ebrac = 1; cx = 0; cy = 0; eparm = 0;
D 3
			}else{ /* Invalid, clear state */
E 3
I 3
			} else { /* Invalid, clear state */
E 3
				 esc = 0; ebrac = 0; eparm = 0;
			}
		} else {
D 7
			if (c == 7) {
E 7
I 7
			if (c == 7)
E 7
				sysbeep();
D 7
			}
E 7
			/* Print only printables */
D 3
			else if (c >= ' ') {
E 3
I 3
			else /*if (c >= ' ') */ {
D 6
				while(inb(0x3da)&1)nulldev();
E 6
I 6
D 7
				while(inb(0x3da)&1)nullop();
E 7
E 6
E 3
				if (so) {
D 3
					*crtat++ = 0x7000| c; row++ ;
E 3
I 3
D 7
					*crtat++ = (so_at<<8)| c; row++ ;
E 7
I 7
					wrtchar((so_at<<8)| c); 
E 7
E 3
				} else {
D 7
					*crtat++ = (ca<<8)| c; row++ ;
E 7
I 7
					wrtchar((ca<<8)| c); 
E 7
				}
				if (row >= COL) row = 0;
				break ;
			}
E 2
		}
D 2
		crtat += COL ;
		}
		break ;
E 2
	}
I 2
	if (crtat >= Crtat+COL*(ROW)) { /* scroll check */
I 7
		if (openf) do sgetc(1); while (scroll);
E 7
		bcopy(Crtat+COL,Crtat,COL*(ROW-1)*CHR);
D 3
		bzero (Crtat+COL*(ROW-1),COL*CHR) ;
E 3
I 3
D 7
		fillw ((bg_at<<8)+' ', Crtat+COL*(ROW-1),COL) ;
E 7
I 7
		fillw ((bg_at<<8) + ' ', Crtat+COL*(ROW-1),COL) ;
E 7
E 3
		crtat -= COL ;
	}
D 3
	cursor(crtat-Crtat);
	splx(s);
E 3
E 2
}
I 2

D 7

E 7
D 3

E 3
E 2
#define	L		0x0001	/* locking function */
#define	SHF		0x0002	/* keyboard shift */
#define	ALT		0x0004	/* alternate shift -- alternate chars */
#define	NUM		0x0008	/* numeric shift  cursors vs. numeric */
#define	CTL		0x0010	/* control shift  -- allows ctl function */
#define	CPS		0x0020	/* caps shift -- swaps case of letter */
#define	ASCII		0x0040	/* ascii code for this key */
#define	STP		0x0080	/* stop output */
#define	FUNC		0x0100	/* function key */
D 2
#define	SYSREQ		0x0200	/* sys req key */
E 2
I 2
#define	SCROLL		0x0200	/* scroll lock key */
E 2

D 2
unsigned	__debug ;
E 2
I 2
D 3
unsigned	__debug = 0 ;
E 3
I 3
D 7
unsigned	__debug = 0;
E 7
I 7
D 8
unsigned	__debug = 0xffe;
E 8
I 8
D 9
unsigned	__debug = 0xffe; /*0xffe */;
E 9
I 9
unsigned	__debug = 0; /*0xffe */;
E 9
E 8
E 7
E 3
E 2
u_short action[] = {
0,     ASCII, ASCII, ASCII, ASCII, ASCII, ASCII, ASCII,		/* scan  0- 7 */
ASCII, ASCII, ASCII, ASCII, ASCII, ASCII, ASCII, ASCII,		/* scan  8-15 */
ASCII, ASCII, ASCII, ASCII, ASCII, ASCII, ASCII, ASCII,		/* scan 16-23 */
ASCII, ASCII, ASCII, ASCII, ASCII,   CTL, ASCII, ASCII,		/* scan 24-31 */
ASCII, ASCII, ASCII, ASCII, ASCII, ASCII, ASCII, ASCII,		/* scan 32-39 */
ASCII, ASCII, SHF  , ASCII, ASCII, ASCII, ASCII, ASCII,		/* scan 40-47 */
ASCII, ASCII, ASCII, ASCII, ASCII, ASCII,  SHF,  ASCII,		/* scan 48-55 */
D 2
  ALT, ASCII, CPS|L, FUNC , FUNC , FUNC , FUNC , FUNC ,		/* scan 56-63 */
FUNC , FUNC , FUNC , FUNC , FUNC , NUM|L, STP|L, ASCII,		/* scan 64-71 */
E 2
I 2
  ALT, ASCII, CPS  , FUNC , FUNC , FUNC , FUNC , FUNC ,		/* scan 56-63 */
D 7
FUNC , FUNC , FUNC , FUNC , FUNC , NUM, STP, ASCII,		/* scan 64-71 */
E 7
I 7
FUNC , FUNC , FUNC , FUNC , FUNC , NUM, SCROLL, ASCII,		/* scan 64-71 */
E 7
E 2
ASCII, ASCII, ASCII, ASCII, ASCII, ASCII, ASCII, ASCII,		/* scan 72-79 */
ASCII, ASCII, ASCII, ASCII,     0,     0,     0,     0,		/* scan 80-87 */
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,	} ;

u_char unshift[] = {	/* no shift */
0,     033  , '1'  , '2'  , '3'  , '4'  , '5'  , '6'  ,		/* scan  0- 7 */
'7'  , '8'  , '9'  , '0'  , '-'  , '='  , 0177 ,'\t'  ,		/* scan  8-15 */

'q'  , 'w'  , 'e'  , 'r'  , 't'  , 'y'  , 'u'  , 'i'  ,		/* scan 16-23 */
'o'  , 'p'  , '['  , ']'  , '\r' , CTL  , 'a'  , 's'  ,		/* scan 24-31 */

'd'  , 'f'  , 'g'  , 'h'  , 'j'  , 'k'  , 'l'  , ';'  ,		/* scan 32-39 */
'\'' , '`'  , SHF  , '\\' , 'z'  , 'x'  , 'c'  , 'v'  ,		/* scan 40-47 */

'b'  , 'n'  , 'm'  , ','  , '.'  , '/'  , SHF  ,   '*',		/* scan 48-55 */
D 2
ALT  , ' '  , CPS|L,     1,     2,    3 ,     4,     5,		/* scan 56-63 */
E 2
I 2
ALT  , ' '  , CPS,     1,     2,    3 ,     4,     5,		/* scan 56-63 */
E 2

D 2
    6,     7,     8,     9,    10, NUM|L, STP|L,   '7',		/* scan 64-71 */
E 2
I 2
    6,     7,     8,     9,    10, NUM, STP,   '7',		/* scan 64-71 */
E 2
  '8',   '9',   '-',   '4',   '5',   '6',   '+',   '1',		/* scan 72-79 */

  '2',   '3',   '0',   '.',     0,     0,     0,     0,		/* scan 80-87 */
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,	} ;

u_char shift[] = {	/* shift shift */
0,     033  , '!'  , '@'  , '#'  , '$'  , '%'  , '^'  ,		/* scan  0- 7 */
'&'  , '*'  , '('  , ')'  , '_'  , '+'  , 0177 ,'\t'  ,		/* scan  8-15 */
'Q'  , 'W'  , 'E'  , 'R'  , 'T'  , 'Y'  , 'U'  , 'I'  ,		/* scan 16-23 */
'O'  , 'P'  , '{'  , '}'  , '\r' , CTL  , 'A'  , 'S'  ,		/* scan 24-31 */
'D'  , 'F'  , 'G'  , 'H'  , 'J'  , 'K'  , 'L'  , ':'  ,		/* scan 32-39 */
'"'  , '~'  , SHF  , '|'  , 'Z'  , 'X'  , 'C'  , 'V'  ,		/* scan 40-47 */
'B'  , 'N'  , 'M'  , '<'  , '>'  , '?'  , SHF  ,   '*',		/* scan 48-55 */
D 2
ALT  , ' '  , CPS|L,     0,     0, ' '  ,     0,     0,		/* scan 56-63 */
    0,     0,     0,     0,     0, NUM|L, STP|L,   '7',		/* scan 64-71 */
E 2
I 2
ALT  , ' '  , CPS,     0,     0, ' '  ,     0,     0,		/* scan 56-63 */
    0,     0,     0,     0,     0, NUM, STP,   '7',		/* scan 64-71 */
E 2
  '8',   '9',   '-',   '4',   '5',   '6',   '+',   '1',		/* scan 72-79 */
  '2',   '3',   '0',   '.',     0,     0,     0,     0,		/* scan 80-87 */
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,	} ;

u_char ctl[] = {	/* CTL shift */
0,     033  , '!'  , 000  , '#'  , '$'  , '%'  , 036  ,		/* scan  0- 7 */
'&'  , '*'  , '('  , ')'  , 037  , '+'  , 034  ,'\177',		/* scan  8-15 */
021  , 027  , 005  , 022  , 024  , 031  , 025  , 011  ,		/* scan 16-23 */
017  , 020  , 033  , 035  , '\r' , CTL  , 001  , 023  ,		/* scan 24-31 */
004  , 006  , 007  , 010  , 012  , 013  , 014  , ';'  ,		/* scan 32-39 */
'\'' , '`'  , SHF  , 034  , 032  , 030  , 003  , 026  ,		/* scan 40-47 */
002  , 016  , 015  , '<'  , '>'  , '?'  , SHF  ,   '*',		/* scan 48-55 */
D 2
ALT  , ' '  , CPS|L,     0,     0, ' '  ,     0,     0,		/* scan 56-63 */
CPS|L,     0,     0,     0,     0,     0,     0,     0,		/* scan 64-71 */
E 2
I 2
ALT  , ' '  , CPS,     0,     0, ' '  ,     0,     0,		/* scan 56-63 */
CPS,     0,     0,     0,     0,     0,     0,     0,		/* scan 64-71 */
E 2
    0,     0,     0,     0,     0,     0,     0,     0,		/* scan 72-79 */
    0,     0,     0,     0,     0,     0,     0,     0,		/* scan 80-87 */
D 2
    0,     0,   033, '7'  , '4'  , '1'  ,     0, NUM|L,		/* scan 88-95 */
'8'  , '5'  , '2'  ,     0, STP|L, '9'  , '6'  , '3'  ,		/*scan  96-103*/
E 2
I 2
    0,     0,   033, '7'  , '4'  , '1'  ,     0, NUM,		/* scan 88-95 */
'8'  , '5'  , '2'  ,     0, STP, '9'  , '6'  , '3'  ,		/*scan  96-103*/
E 2
'.'  ,     0, '*'  , '-'  , '+'  ,     0,     0,     0,		/*scan 104-111*/
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,	} ;

#ifdef notdef
struct key {
	u_short action;		/* how this key functions */
	char	ascii[8];	/* ascii result character indexed by shifts */
};
#endif

D 2
u_char shfts, ctls, alts, caps, num, stp;
E 2
I 2
D 7
u_char shfts, ctls, alts, caps, num, stp, scroll;
E 7
E 2

D 2
#define	KBSTATP	0x64	/* kbd status port */
#define		KBS_INP_BUF_FUL	0x02	/* kbd char ready */
#define	KBDATAP	0x60	/* kbd data port */
E 2
I 2
#define	KBSTAT		0x64	/* kbd status port */
#define	KBS_INP_BUF_FUL	0x02	/* kbd char ready */
#define	KBDATA		0x60	/* kbd data port */
E 2
#define	KBSTATUSPORT	0x61	/* kbd status */

D 2
u_char odt;
E 2
I 2
update_led()
{
	while (inb(0x64)&2);	/* wait input ready */
	outb(0x60,0xED);	/* LED Command */
	while (inb(0x64)&2);	/* wait input ready */
	outb(0x60,scroll | 2*num | 4*caps);
}
E 2

I 3
reset_cpu() {
	while(1) {
		while (inb(0x64)&2);	/* wait input ready */
		outb(0x64,0xFE);	/* Reset Command */
		DELAY(4000000);
		while (inb(0x64)&2);	/* wait input ready */
		outb(0x64,0xFF);	/* Keyboard Reset Command */
	}
	/* NOTREACHED */
}

E 3
D 2
int sgetc(on) {
	u_char dt, brk;
	u_short act;
	
E 2
I 2
/*
sgetc(noblock) : get a character from the keyboard. If noblock = 0 wait until
a key is gotten.  Otherwise return a 0x100 (256).
*/
int sgetc(noblock)
{
	u_char dt; unsigned key;
E 2
loop:
D 2
	do {
		while (inb(0x64)&2) ;
		dt = inb(0x60);
	} while (dt == odt);
	odt = dt;
if(dt == 0x54) _exit();
	brk = dt & 0x80 ; dt = dt & 0x7f ;
E 2
I 2
	/* First see if there is something in the keyboard port */
	if (inb(KBSTAT)&1) dt = inb(KBDATA);
	else { if (noblock) return (0x100); else goto loop; }
E 2

D 2
	act = action[dt];
	if (act&SHF) {
		if(brk)	shfts = 0; else shfts = 1;
	}
	if (act&ALT) {
		if(brk)	alts = 0; else alts = 1;
	}
	if (act&NUM) {
		if (act&L) {
			if(!brk) num ^= 1;
		} else if(brk)	num = 0; else num = 1;
	}
	if (act&CTL) {
		if(brk)	ctls = 0; else ctls = 1;
	}
	if (act&CPS) {
		if (act&L) {
			if(!brk) caps ^= 1;
		} else if(brk)	caps = 0; else caps = 1;
	}
	if (act&STP) {
		if (act&L) {
			if(!brk) stp ^= 1;
		} else if(brk)	stp = 0; else stp = 1;
	}
	if ((act&FUNC) &&  brk) {
		unsigned key = unshift[dt] ;
		if(__debug & (1<<key))
			__debug &= ~(1<<key) ;
		else
			__debug |= (1<<key) ;
	}
	if(stp) goto loop;
	if ((act&ASCII) && !brk) {
		u_char chr;
E 2
I 2
	/* Check for cntl-alt-del */
	if ((dt == 83)&&ctls&&alts) _exit();
E 2

D 2
		if (shfts){
			 chr = shift[dt] ; } else {
		if (ctls) {
			chr = ctl[dt] ; } else {
		chr = unshift[dt] ; } }
		if (caps && (chr >= 'a' && chr <= 'z')) {
			chr -= 'a' - 'A' ;
E 2
I 2
	/* Check for make/break */
	if (dt & 0x80) {
		/* break */
		dt = dt & 0x7f ;
		switch (action[dt]) {
		case SHF: shfts = 0; break;
		case ALT: alts = 0; break;
		case CTL: ctls = 0; break;
		case FUNC:
			/* Toggle debug flags */
			key = unshift[dt];
			if(__debug & (1<<key)) __debug &= ~(1<<key) ;
			else __debug |= (1<<key) ;
			break;
E 2
		}
D 2
		return(chr);
E 2
I 2
	} else {
		/* make */
		dt = dt & 0x7f ;
		switch (action[dt]) {
		/* LOCKING KEYS */
		case NUM: num ^= 1; update_led(); break;
		case CPS: caps ^= 1; update_led(); break;
		case SCROLL: scroll ^= 1; update_led(); break;
		case STP: stp ^= 1; if(stp) goto loop; break;

		/* NON-LOCKING KEYS */
		case SHF: shfts = 1; break;
		case ALT: alts = 1; break;
		case CTL: ctls = 1; break;
		case ASCII:
			if (shfts) dt = shift[dt];
			else if (ctls) dt = ctl[dt];
			else dt = unshift[dt];
			if (caps && (dt >= 'a' && dt <= 'z')) dt -= 'a' - 'A';
			return(dt);
		}
E 2
	}
D 2
	if(on) return (0x100); else goto loop;
E 2
I 2
	if (noblock) return (0x100); else goto loop;
E 2
}

pg(p,q,r,s,t,u,v,w,x,y,z) char *p; {
	printf(p,q,r,s,t,u,v,w,x,y,z);
	printf("\n");
	return(getchar());
}

/* special characters */
#define bs	8
#define lf	10	
#define cr	13	
#define cntlc	3	
#define del	0177	
#define cntld	4

getchar()
{
	register char thechar;
	register delay;
	int x;

D 8
	consoftc.cs_flags |= CSF_POLLING;
E 8
I 8
	pcconsoftc.cs_flags |= CSF_POLLING;
E 8
	x=splhigh();
D 2
sput('>',0xe);
E 2
I 2
	sput('>',0x6);
E 2
D 3
	while (1) {
E 3
I 3
	/*while (1) {*/
E 3
		thechar = (char) sgetc(0);
D 2
	consoftc.cs_flags &= ~CSF_POLLING;
	splx(x);
E 2
I 2
D 8
		consoftc.cs_flags &= ~CSF_POLLING;
E 8
I 8
		pcconsoftc.cs_flags &= ~CSF_POLLING;
E 8
		splx(x);
E 2
		switch (thechar) {
		    default: if (thechar >= ' ')
D 2
			     	sput(thechar,0xe);
E 2
I 2
			     	sput(thechar,0x6);
E 2
			     return(thechar);
		    case cr:
D 2
		    case lf: sput(cr,0xe);
			     sput(lf,0xe);
E 2
I 2
		    case lf: sput(cr,0x6);
			     sput(lf,0x6);
E 2
			     return(lf);
		    case bs:
		    case del:
D 2
			     sput(bs,0xe);
			     sput(' ',0xe);
			     sput(bs,0xe);
E 2
I 2
			     sput(bs,0x6);
			     sput(' ',0x6);
			     sput(bs,0x6);
E 2
			     return(thechar);
D 2
		    case cntlc:
E 2
I 2
		    /*case cntlc:
E 2
			     sput('^',0xe) ; sput('C',0xe) ; sput('\r',0xe) ; sput('\n',0xe) ;
D 2
			     _exit(-2) ;
E 2
I 2
			     _exit(-2) ; */
E 2
		    case cntld:
D 2
			     sput('^',0xe) ; sput('D',0xe) ; sput('\r',0xe) ; sput('\n',0xe) ;
E 2
I 2
			     sput('^',0x6) ; sput('D',0x6) ; sput('\r',0x6) ; sput('\n',0x6) ;
E 2
			     return(0);
		}
D 3
	}
E 3
I 3
	/*}*/
E 3
}
I 7

D 15
#include "machine/dbg.h"
#include "machine/stdarg.h"
E 15
I 15
#include <machine/dbg.h>
#include <machine/stdarg.h>
E 15
static nrow;

void
#ifdef __STDC__
dprintf(unsigned flgs, const char *fmt, ...)
#else
dprintf(flgs, fmt /*, va_alist */)
        char *fmt;
	unsigned flgs;
#endif
{	extern unsigned __debug;
	va_list ap;

	if((flgs&__debug) > DPAUSE) {
		__color = ffs(flgs&__debug)+1;
		va_start(ap,fmt);
		kprintf(fmt, 1, (struct tty *)0, ap);
		va_end(ap);
	if (flgs&DPAUSE || nrow%24 == 23) { 
		int x;
		x = splhigh();
		if (nrow%24 == 23) nrow = 0;
		sgetc(0);
		splx(x);
	}
	}
	__color = 0;
}

consinit() {}
E 7
E 1
