h11190
s 00001/00001/00384
d D 8.2 95/01/09 18:22:34 cgd 24 23
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00002/00002/00383
d D 8.1 93/06/10 21:59:09 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00017/00368
d D 7.17 93/05/27 18:41:43 torek 22 21
c fully bracket those initializers, for gcc2 -W
e
s 00010/00010/00375
d D 7.16 92/10/11 10:38:37 bostic 21 20
c make kernel includes standard
e
s 00017/00005/00368
d D 7.15 92/08/24 17:08:05 marc 20 19
c some flags got moved around and code wasen't consistent
e
s 00000/00001/00373
d D 7.14 92/04/19 08:43:34 ralph 19 18
c dkstat.h is not used, removed.
e
s 00002/00000/00372
d D 7.13 92/03/09 09:55:58 torek 18 17
c gcc lint
e
s 00001/00001/00371
d D 7.12 92/02/15 17:32:33 mckusick 17 16
c must include proc before tty.h and socketvar.h
e
s 00002/00002/00370
d D 7.11 92/02/14 17:38:56 torek 16 15
c add COMPAT_SUNOS
e
s 00005/00004/00367
d D 7.10 91/05/09 21:21:34 bostic 15 14
c new copyright; att/bsd/shared
e
s 00000/00014/00371
d D 7.9 91/04/20 16:12:09 karels 14 13
c rm user.h, reg.h; move ttspeedtab back to tty.c for drivers
e
s 00000/00000/00385
d D 7.8 91/03/17 15:42:27 karels 13 12
c more-or-less working with new proc & user structs
e
s 00021/00008/00364
d D 7.7 91/02/15 14:10:11 marc 12 11
c readjust flags more carefully
e
s 00002/00002/00370
d D 7.6 90/06/14 13:18:24 marc 11 10
c VFLUSHO -> VDISCARD
e
s 00004/00000/00368
d D 7.5 90/05/15 16:20:29 mckusick 10 9
c "update for hp300 support from Utah"
e
s 00000/00001/00368
d D 7.4 90/02/17 10:15:09 mckusick 9 8
c get rid of dir.h
e
s 00002/00004/00367
d D 7.3 89/11/20 18:24:15 marc 8 7
c change name of old tiocsetd ioctls
e
s 00001/00000/00370
d D 7.2 89/09/04 15:33:53 karels 7 6
c dir.h for osi alpha release
e
s 00000/00000/00370
d D 7.1 89/09/03 18:10:42 karels 6 5
c rev 7
e
s 00003/00003/00367
d D 1.5 89/09/03 18:10:07 karels 5 4
c move IEXTEN; cbreak has IEXTEN
e
s 00000/00001/00370
d D 1.4 89/08/13 19:19:21 marc 4 3
c remove header reference to dir.h
e
s 00002/00002/00369
d D 1.3 89/04/25 14:50:57 mckusick 3 2
c ../machine => machine
e
s 00031/00041/00340
d D 1.2 88/10/18 15:16:56 marc 2 1
c new terminal driver
e
s 00381/00000/00000
d D 1.1 88/10/04 22:41:09 marc 1 0
c date and time created 88/10/04 22:41:09 by marc
e
u
U
t
T
I 1
D 15
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
/*-
D 23
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
 * %sccs.include.redist.c%
E 15
 *
D 2
 *	@(#)ttcompat.c	7.11 (Berkeley) 4/8/88
E 2
I 2
 *	%W% (Berkeley) %G%
E 2
 */

/* 
D 2
 * mapping routines for old line disciplines (yuck)
E 2
I 2
 * mapping routines for old line discipline (yuck)
E 2
 */
D 16
#ifdef COMPAT_43
E 16
I 16
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 16

D 3
#include "../machine/reg.h"

E 3
D 21
#include "param.h"
#include "systm.h"
I 7
D 9
#include "dir.h"
E 9
E 7
D 4
#include "dir.h"
E 4
D 14
#include "user.h"
E 14
#include "ioctl.h"
I 17
#include "proc.h"
E 17
#include "tty.h"
#include "termios.h"
D 17
#include "proc.h"
E 17
#include "file.h"
#include "conf.h"
D 19
#include "dkstat.h"
E 19
D 14
#include "uio.h"
E 14
#include "kernel.h"
#include "syslog.h"
E 21
I 21
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/termios.h>
#include <sys/file.h>
#include <sys/conf.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
E 21
I 3

D 14
#include "machine/reg.h"
E 3

E 14
D 2
/* begin XXX */
#undef t_erase
#undef t_kill
#undef t_intrc
#undef t_quitc
#undef t_startc
#undef t_stopc
#undef t_eofc
#undef t_brkc
#undef t_suspc
#undef t_dsuspc
#undef t_rprntc
#undef t_flushc
#undef t_werasc
#undef t_lnextc
/* end XXX */
E 2
I 2
int ttydebug = 0;
E 2

D 2
/* should fold these two tables into one */
E 2
I 2
D 12
/* XXX - fold these two tables into one */
E 12
E 2
static struct speedtab compatspeeds[] = {
D 22
	38400,	15,
	19200,	14,
	9600,	13,
	4800,	12,
	2400,	11,
	1800,	10,
	1200,	9,
	600,	8,
	300,	7,
	200,	6,
	150,	5,
	134,	4,
	110,	3,
	75,	2,
	50,	1,
	0,	0,
	-1,	-1,
E 22
I 22
	{ 38400, 15 },
	{ 19200, 14 },
	{ 9600,	13 },
	{ 4800,	12 },
	{ 2400,	11 },
	{ 1800,	10 },
	{ 1200,	9 },
	{ 600,	8 },
	{ 300,	7 },
	{ 200,	6 },
	{ 150,	5 },
	{ 134,	4 },
	{ 110,	3 },
	{ 75,	2 },
	{ 50,	1 },
	{ 0,	0 },
	{ -1,	-1 },
E 22
};
static int compatspcodes[16] = { 
	0, 50, 75, 110, 134, 150, 200, 300, 600, 1200,
	1800, 2400, 4800, 9600, 19200, 38400,
};
D 14

I 12
ttspeedtab(speed, table)
	register struct speedtab *table;
{

	for ( ; table->sp_speed != -1; table++)
		if (table->sp_speed == speed)
			return (table->sp_code);
	return (-1);
}
E 14

E 12
/*ARGSUSED*/
ttcompat(tp, com, data, flag)
	register struct tty *tp;
I 18
D 24
	int com;
E 24
I 24
	u_long com;
E 24
E 18
	caddr_t data;
I 18
	int flag;
E 18
{
D 12
	switch(com) {
E 12
I 12

	switch (com) {
E 12
	case TIOCGETP: {
		register struct sgttyb *sg = (struct sgttyb *)data;
		register u_char *cc = tp->t_cc;
		register speed;

		speed = ttspeedtab(tp->t_ospeed, compatspeeds);
		sg->sg_ospeed = (speed == -1) ? 15 : speed;
		if (tp->t_ispeed == 0)
			sg->sg_ispeed = sg->sg_ospeed;
		else {
			speed = ttspeedtab(tp->t_ispeed, compatspeeds);
			sg->sg_ispeed = (speed == -1) ? 15 : speed;
		}
D 2

E 2
		sg->sg_erase = cc[VERASE];
		sg->sg_kill = cc[VKILL];
D 2
		sg->sg_flags = ttcompatgetflags(tp) & 0xffff;
E 2
I 2
		sg->sg_flags = ttcompatgetflags(tp);
E 2
		break;
	}

	case TIOCSETP:
	case TIOCSETN: {
		register struct sgttyb *sg = (struct sgttyb *)data;
		struct termios term;
		int speed;

		term = tp->t_termios;
D 2

E 2
		if ((speed = sg->sg_ispeed) > 15 || speed < 0)
			term.c_ispeed = speed;
		else
			term.c_ispeed = compatspcodes[speed];
		if ((speed = sg->sg_ospeed) > 15 || speed < 0)
			term.c_ospeed = speed;
		else
			term.c_ospeed = compatspcodes[speed];
D 2
		
E 2
		term.c_cc[VERASE] = sg->sg_erase;
		term.c_cc[VKILL] = sg->sg_kill;
D 8
		if (sg->sg_erase == -1)
D 2
			term.c_cc[VERASE2] = POSIX_V_DISABLE;

E 2
I 2
			term.c_cc[VERASE2] = _POSIX_VDISABLE;
E 8
E 2
D 12
		tp->t_flags = (tp->t_flags&0xffff0000) | sg->sg_flags;
E 12
I 12
		tp->t_flags = tp->t_flags&0xffff0000 | sg->sg_flags&0xffff;
E 12
D 2

E 2
		ttcompatsetflags(tp, &term);
		return (ttioctl(tp, com == TIOCSETP ? TIOCSETAF : TIOCSETA, 
			&term, flag));
	}

	case TIOCGETC: {
		struct tchars *tc = (struct tchars *)data;
		register u_char *cc = tp->t_cc;

		tc->t_intrc = cc[VINTR];
		tc->t_quitc = cc[VQUIT];
		tc->t_startc = cc[VSTART];
		tc->t_stopc = cc[VSTOP];
		tc->t_eofc = cc[VEOF];
		tc->t_brkc = cc[VEOL];
		break;
	}
	case TIOCSETC: {
		struct tchars *tc = (struct tchars *)data;
		register u_char *cc = tp->t_cc;

		cc[VINTR] = tc->t_intrc;
		cc[VQUIT] = tc->t_quitc;
		cc[VSTART] = tc->t_startc;
		cc[VSTOP] = tc->t_stopc;
		cc[VEOF] = tc->t_eofc;
		cc[VEOL] = tc->t_brkc;
		if (tc->t_brkc == -1)
D 2
			cc[VEOL2] = POSIX_V_DISABLE;
E 2
I 2
			cc[VEOL2] = _POSIX_VDISABLE;
E 2
		break;
	}
	case TIOCSLTC: {
		struct ltchars *ltc = (struct ltchars *)data;
		register u_char *cc = tp->t_cc;

		cc[VSUSP] = ltc->t_suspc;
		cc[VDSUSP] = ltc->t_dsuspc;
		cc[VREPRINT] = ltc->t_rprntc;
D 11
		cc[VFLUSHO] = ltc->t_flushc;
E 11
I 11
		cc[VDISCARD] = ltc->t_flushc;
E 11
		cc[VWERASE] = ltc->t_werasc;
		cc[VLNEXT] = ltc->t_lnextc;
		break;
	}
	case TIOCGLTC: {
		struct ltchars *ltc = (struct ltchars *)data;
		register u_char *cc = tp->t_cc;

		ltc->t_suspc = cc[VSUSP];
		ltc->t_dsuspc = cc[VDSUSP];
		ltc->t_rprntc = cc[VREPRINT];
D 11
		ltc->t_flushc = cc[VFLUSHO];
E 11
I 11
		ltc->t_flushc = cc[VDISCARD];
E 11
		ltc->t_werasc = cc[VWERASE];
		ltc->t_lnextc = cc[VLNEXT];
		break;
	}
	case TIOCLBIS:
	case TIOCLBIC:
	case TIOCLSET: {
		struct termios term;

		term = tp->t_termios;
		if (com == TIOCLSET)
D 2
			tp->t_flags = (tp->t_flags&0xffff) | *(short *)data<<16;
E 2
I 2
			tp->t_flags = (tp->t_flags&0xffff) | *(int *)data<<16;
E 2
		else {
			tp->t_flags = 
			 (ttcompatgetflags(tp)&0xffff0000)|(tp->t_flags&0xffff);
			if (com == TIOCLBIS)
D 2
				tp->t_flags |= *(short *)data<<16;
E 2
I 2
				tp->t_flags |= *(int *)data<<16;
E 2
			else
D 2
				tp->t_flags &= ~(*(short *)data<<16);
E 2
I 2
				tp->t_flags &= ~(*(int *)data<<16);
E 2
		}
		ttcompatsetlflags(tp, &term);
		return (ttioctl(tp, TIOCSETA, &term, flag));
	}
	case TIOCLGET:
D 2
		*(short *)data = ttcompatgetflags(tp)>>16;
E 2
I 2
		*(int *)data = ttcompatgetflags(tp)>>16;
		if (ttydebug)
			printf("CLGET: returning %x\n", *(int *)data);
E 2
		break;
I 2

D 8
	case TIOCGETDCOMPAT:
E 8
I 8
	case OTIOCGETD:
E 8
		*(int *)data = tp->t_line ? tp->t_line : 2;
		break;

D 8
	case TIOCSETDCOMPAT: {
E 8
I 8
	case OTIOCSETD: {
E 8
		int ldisczero = 0;

D 12
		return(ttioctl(tp, TIOCSETD, 
E 12
I 12
		return (ttioctl(tp, TIOCSETD, 
E 12
			*(int *)data == 2 ? (caddr_t)&ldisczero : data, flag));
I 12
	    }
E 12
I 10

	case OTIOCCONS:
		*(int *)data = 1;
D 12
		return(ttioctl(tp, TIOCCONS, data, flag));
E 10
	}
E 12
I 12
		return (ttioctl(tp, TIOCCONS, data, flag));
E 12

E 2
	default:
		return (-1);
	}
D 12
	return(0);
E 12
I 12
	return (0);
E 12
}

D 2


E 2
ttcompatgetflags(tp)
	register struct tty *tp;
{
	register long iflag = tp->t_iflag;
	register long lflag = tp->t_lflag;
	register long oflag = tp->t_oflag;
	register long cflag = tp->t_cflag;
	register flags = 0;

	if (iflag&IXOFF)
		flags |= TANDEM;
	if (iflag&ICRNL || oflag&ONLCR)
		flags |= CRMOD;
	if (cflag&PARENB) {
		if (iflag&INPCK) {
			if (cflag&PARODD)
				flags |= ODDP;
			else
				flags |= EVENP;
		} else
			flags |= EVENP | ODDP;
	} else {
		if ((tp->t_flags&LITOUT) && !(oflag&OPOST))
			flags |= LITOUT;
		if (tp->t_flags&PASS8)
			flags |= PASS8;
	}
	
	if ((lflag&ICANON) == 0) {	
		/* fudge */
		if (iflag&IXON || lflag&ISIG || lflag&IEXTEN || cflag&PARENB)
			flags |= CBREAK;
		else
			flags |= RAW;
	}
I 20
	if (cflag&MDMBUF)
		flags |= MDMBUF;
	if ((cflag&HUPCL) == 0)
		flags |= NOHANG;
E 20
	if (oflag&OXTABS)
		flags |= XTABS;
D 2

E 2
	if (lflag&ECHOE)
D 2
		flags |= CRTERA;
E 2
I 2
		flags |= CRTERA|CRTBS;
E 2
	if (lflag&ECHOKE)
D 2
		flags |= CRTKIL;
E 2
I 2
		flags |= CRTKIL|CRTBS;
E 2
	if (lflag&ECHOPRT)
		flags |= PRTERA;
	if (lflag&ECHOCTL)
		flags |= CTLECH;
	if ((iflag&IXANY) == 0)
		flags |= DECCTQ;
D 20
	flags |= lflag&(ECHO|MDMBUF|TOSTOP|FLUSHO|NOHANG|PENDIN|NOFLSH);
E 20
I 20
	flags |= lflag&(ECHO|TOSTOP|FLUSHO|PENDIN|NOFLSH);
E 20
D 2

E 2
I 2
if (ttydebug)
	printf("getflags: %x\n", flags);
E 2
	return (flags);
}

ttcompatsetflags(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	register flags = tp->t_flags;
	register long iflag = t->c_iflag;
	register long oflag = t->c_oflag;
	register long lflag = t->c_lflag;
	register long cflag = t->c_cflag;

	if (flags & RAW) {
		iflag &= IXOFF;
		oflag &= ~OPOST;
D 5
		lflag &= ~(ECHOCTL|ISIG|ICANON);
E 5
I 5
		lflag &= ~(ECHOCTL|ISIG|ICANON|IEXTEN);
E 5
	} else {
D 5
		iflag |= BRKINT|IXON|IEXTEN|IMAXBEL;
E 5
I 5
		iflag |= BRKINT|IXON|IMAXBEL;
E 5
		oflag |= OPOST;
D 5
		lflag |= ISIG;
E 5
I 5
D 12
		lflag |= ISIG|IEXTEN;
E 12
I 12
		lflag |= ISIG|IEXTEN|ECHOCTL;	/* XXX was echoctl on ? */
E 12
E 5
		if (flags & XTABS)
			oflag |= OXTABS;
		else
			oflag &= ~OXTABS;
		if (flags & CBREAK)
			lflag &= ~ICANON;
		else
			lflag |= ICANON;
		if (flags&CRMOD) {
			iflag |= ICRNL;
			oflag |= ONLCR;
		} else {
			iflag &= ~ICRNL;
			oflag &= ~ONLCR;
		}
	}
	if (flags&ECHO)
		lflag |= ECHO;
	else
		lflag &= ~ECHO;
		
	if (flags&(RAW|LITOUT|PASS8)) {
		cflag &= ~(CSIZE|PARENB);
		cflag |= CS8;
		if ((flags&(RAW|PASS8)) == 0)
			iflag |= ISTRIP;
I 12
		else
			iflag &= ~ISTRIP;
E 12
	} else {
		cflag &= ~CSIZE;
		cflag |= CS7|PARENB;
I 12
		iflag |= ISTRIP;
E 12
	}
	if ((flags&(EVENP|ODDP)) == EVENP) {
		iflag |= INPCK;
		cflag &= ~PARODD;
	} else if ((flags&(EVENP|ODDP)) == ODDP) {
		iflag |= INPCK;
		cflag |= PARODD;
	} else 
		iflag &= ~INPCK;
	if (flags&LITOUT)
		oflag &= ~OPOST;	/* move earlier ? */
	if (flags&TANDEM)
		iflag |= IXOFF;
	else
		iflag &= ~IXOFF;
	t->c_iflag = iflag;
	t->c_oflag = oflag;
	t->c_lflag = lflag;
	t->c_cflag = cflag;
}

D 2
/* XXX - rethink this whole routine */
E 2
ttcompatsetlflags(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	register flags = tp->t_flags;
	register long iflag = t->c_iflag;
	register long oflag = t->c_oflag;
	register long lflag = t->c_lflag;
	register long cflag = t->c_cflag;
I 2

E 2
	if (flags&CRTERA)
		lflag |= ECHOE;
	else
D 2
		lflag &= ECHOE;
E 2
I 2
		lflag &= ~ECHOE;
E 2
	if (flags&CRTKIL)
		lflag |= ECHOKE;
	else
		lflag &= ~ECHOKE;
	if (flags&PRTERA)
		lflag |= ECHOPRT;
	else
		lflag &= ~ECHOPRT;
	if (flags&CTLECH)
		lflag |= ECHOCTL;
	else
		lflag &= ~ECHOCTL;
	if ((flags&DECCTQ) == 0)
D 20
		lflag |= IXANY;
E 20
I 20
		iflag |= IXANY;
E 20
	else
D 20
		lflag &= ~IXANY;
D 2

E 2
	lflag &= ~(MDMBUF|TOSTOP|FLUSHO|NOHANG|PENDIN|NOFLSH);
	lflag |= flags&(MDMBUF|TOSTOP|FLUSHO|NOHANG|PENDIN|NOFLSH);
E 20
I 20
		iflag &= ~IXANY;
	if (flags & MDMBUF)
		cflag |= MDMBUF;
	else
		cflag &= ~MDMBUF;
	if (flags&NOHANG)
		cflag &= ~HUPCL;
	else
		cflag |= HUPCL;
	lflag &= ~(TOSTOP|FLUSHO|PENDIN|NOFLSH);
	lflag |= flags&(TOSTOP|FLUSHO|PENDIN|NOFLSH);
E 20
D 2

E 2
	if (flags&(LITOUT|PASS8)) {
		iflag &= ~ISTRIP;
		cflag &= ~(CSIZE|PARENB);
		cflag |= CS8;
		if (flags&LITOUT)
			oflag &= ~OPOST;
		if ((flags&(PASS8|RAW)) == 0)
			iflag |= ISTRIP;
	} else if ((flags&RAW) == 0) {
		cflag &= ~CSIZE;
		cflag |= CS7|PARENB;
		oflag |= OPOST;
	}
	t->c_iflag = iflag;
	t->c_oflag = oflag;
	t->c_lflag = lflag;
	t->c_cflag = cflag;
}
D 16
#endif	/* COMPAT_43 */
E 16
I 16
#endif	/* COMPAT_43 || COMPAT_SUNOS */
E 16
E 1
