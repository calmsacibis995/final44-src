h15095
s 00002/00002/00511
d D 8.4 95/02/19 08:00:43 cgd 21 20
c new names for functions.
e
s 00001/00001/00512
d D 8.3 94/01/12 10:10:48 bostic 20 19
c lint
e
s 00050/00014/00463
d D 8.2 93/09/09 14:47:59 hibler 19 18
c bring up to HP-UX 9.x level
e
s 00002/00002/00475
d D 8.1 93/07/08 11:32:54 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00472
d D 7.16 93/07/08 10:53:35 hibler 17 15
c cleanup
e
s 00002/00002/00475
d R 8.1 93/06/10 21:24:59 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00474
d D 7.15 93/05/12 20:30:24 mckusick 15 14
c requires COMPAT_43 to build
e
s 00007/00009/00467
d D 7.14 92/12/27 09:06:23 hibler 14 13
c latest Utah version
e
s 00012/00012/00464
d D 7.13 92/10/11 09:01:45 bostic 13 12
c make kernel includes standard
e
s 00012/00006/00464
d D 7.12 92/09/21 21:21:14 hibler 12 11
c fix a couple of minor bugs in my last revision
e
s 00158/00085/00312
d D 7.11 92/08/03 14:13:46 hibler 11 10
c termios support
e
s 00001/00001/00396
d D 7.10 92/02/15 18:08:27 mckusick 10 9
c have to include proc.h before socketvar.h
e
s 00002/00002/00395
d D 7.9 91/05/30 14:53:47 mckusick 9 8
c make file flags consistent
e
s 00027/00023/00370
d D 7.8 91/04/20 17:45:36 karels 8 7
c fix includes; new driver calling conventions w/ proc
e
s 00008/00004/00385
d D 7.7 91/01/11 00:00:50 mckusick 7 6
c add dynamically allocated file descriptors
e
s 00011/00011/00378
d D 7.6 90/12/16 16:36:43 bostic 6 5
c kernel reorg
e
s 00001/00001/00388
d D 7.5 90/10/24 15:10:50 mckusick 5 4
c update Utah source identifier
e
s 00240/00208/00149
d D 7.4 90/06/27 18:38:32 hibler 4 3
c convert directly between HP-UX termio and POSIX termios
e
s 00002/00009/00355
d D 7.3 90/06/24 19:08:57 mckusick 3 2
c purge use of RETURN
e
s 00046/00053/00318
d D 7.2 90/06/22 18:01:06 hibler 2 1
c eliminate use of u_error
e
s 00371/00000/00000
d D 7.1 90/05/08 22:18:43 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 18
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: hpux_tty.c 1.7 89/04/11$
E 5
I 5
D 14
 * from: Utah $Hdr: hpux_tty.c 1.1 90/07/09$
E 14
I 14
D 17
 * from: Utah $Hdr: hpux_tty.c 1.12 92/04/15$
E 17
I 17
D 19
 * from: Utah $Hdr: hpux_tty.c 1.13 93/06/30$
E 19
I 19
 * from: Utah $Hdr: hpux_tty.c 1.14 93/08/05$
E 19
E 17
E 14
E 5
 *
 *	%W% (Berkeley) %G%
 */

/*
 * stty/gtty/termio emulation stuff
 */
#ifdef HPUXCOMPAT
I 15
#ifndef COMPAT_43
#define COMPAT_43
#endif
E 15

D 6
#include "param.h"
#include "systm.h"
#include "user.h"
#include "ioctl.h"
#include "tty.h"
#include "proc.h"
#include "file.h"
#include "conf.h"
#include "buf.h"
#include "uio.h"
#include "kernel.h"
E 6
I 6
D 8
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
I 7
#include "sys/filedesc.h"
E 7
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/proc.h"
#include "sys/file.h"
#include "sys/conf.h"
#include "sys/buf.h"
#include "sys/uio.h"
#include "sys/kernel.h"
E 8
I 8
D 13
#include "param.h"
#include "systm.h"
#include "filedesc.h"
#include "ioctl.h"
D 10
#include "tty.h"
E 10
#include "proc.h"
I 10
#include "tty.h"
E 10
#include "file.h"
#include "conf.h"
#include "buf.h"
#include "kernel.h"
E 13
I 13
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/filedesc.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/file.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/kernel.h>
E 13
E 8
E 6

D 13
#include "hpux.h"
#include "hpux_termio.h"
E 13
I 13
#include <hp/hpux/hpux.h>
#include <hp/hpux/hpux_termio.h>
E 13

I 2
D 3
/*
 * XXX should just include syscontext.h but RETURN definition clashes
 * with defined constant in tty.h
 */
#undef RETURN
#define RETURN(value)	{ u.u_error = (value); return (u.u_error); }

E 3
E 2
D 4
char hpuxtobsdbaud[32] = {
	B0,	B50,	B75,	B110,	B134,	B150,	B200,	B300,
	B600,	B0,	B1200,	B1800,	B2400,	B0,	B4800,	B0,
	B9600,	EXTA,	EXTB,	B0,	B0,	B0,	B0,	B0,
	B0,	B0,	B0,	B0,	B0,	B0,	B0,	B0
};

char bsdtohpuxbaud[16] = {
	TIO_B0,		TIO_B50,	TIO_B75,	TIO_B110,
	TIO_B134,	TIO_B150,	TIO_B200,	TIO_B300,
	TIO_B600,	TIO_B1200,	TIO_B1800,	TIO_B2400,
	TIO_B4800,	TIO_B9600,	TIO_B19200,	TIO_B38400
};

E 4
/*
D 4
 * Map BSD style sgtty info to and from SYS5 style termio stuff.
 * Map BSD style sgtty info to and from V7 style sgtty stuff.
E 4
I 4
 * Map BSD/POSIX style termios info to and from SYS5 style termio stuff.
E 4
 */
D 8
hpuxtermio(fp, com, data)
E 8
I 8
D 19
hpuxtermio(fp, com, data, p)
E 8
	struct file *fp;
E 19
I 19
hpuxtermio(fd, com, data, p)
D 20
	int fd;
E 20
I 20
	int fd, com;
E 20
E 19
	caddr_t data;
I 8
	struct proc *p;
E 8
{
I 19
	struct file *fp;
E 19
D 4
	struct sgttyb sg;
	struct bsdtchars {	/* avoid problem with ttychars.h */
		char bsdt_intrc;
		char bsdt_quitc;
		char bsdt_startc;
		char bsdt_stopc;
		char bsdt_eofc;
		char bsdt_brkc;
	} tc;
	struct bsdltchars {	/* avoid problem with ttychars.h */
		char bsdt_suspc;
		char bsdt_dsuspc;
		char bsdt_rprntc;
		char bsdt_flushc;
		char bsdt_werasc;
		char bsdt_lnextc;
	} ltc;
D 2
	int lmode, (*ioctlrout)();
E 2
I 2
	int lmode, error, (*ioctlrout)();
E 2
	register u_short flag;
E 4
I 4
	struct termios tios;
I 11
	struct hpuxtermios htios;
E 11
	int line, error, (*ioctlrout)();
E 4
D 11
	register struct hpuxtermio *tiop;
E 11
I 11
	int newi = 0;
E 11

I 19
	fp = p->p_fd->fd_ofiles[fd];
E 19
	ioctlrout = fp->f_ops->fo_ioctl;
D 11
	tiop = (struct hpuxtermio *)data;
E 11
	switch (com) {
I 11
	case HPUXTCGETATTR:
		newi = 1;
		/* fall into ... */
E 11
	case HPUXTCGETA:
D 4
		/* get everything we might need */
E 4
I 4
		/*
		 * Get BSD terminal state
		 */
E 4
D 11
		bzero(data, sizeof(struct hpuxtermio));
E 11
D 2
		if (u.u_error = ioctlrout(fp, TIOCGETP, (caddr_t)&sg))
E 2
I 2
D 4
		if (error = ioctlrout(fp, TIOCGETP, (caddr_t)&sg))
E 4
I 4
D 8
		if (error = (*ioctlrout)(fp, TIOCGETA, (caddr_t)&tios))
E 8
I 8
		if (error = (*ioctlrout)(fp, TIOCGETA, (caddr_t)&tios, p))
E 8
E 4
E 2
			break;
I 11
		bzero((char *)&htios, sizeof htios);
E 11
D 4
		(void) ioctlrout(fp, TIOCGETC, (caddr_t)&tc);
		(void) ioctlrout(fp, TIOCLGET, (caddr_t)&lmode);

		/* set baud rate */
		tiop->c_cflag = (u_short)bsdtohpuxbaud[sg.sg_ispeed&0xF];

		/* set editing chars except for EOF/EOL (set below) */
		tiop->c_cc[HPUXVINTR] = tc.bsdt_intrc;
		tiop->c_cc[HPUXVQUIT] = tc.bsdt_quitc;
		tiop->c_cc[HPUXVERASE] = sg.sg_erase;
		tiop->c_cc[HPUXVKILL] = sg.sg_kill;

		/* set flags */
		flag = sg.sg_flags;
		if ((flag & TBDELAY) == XTABS)
E 4
I 4
		/*
		 * Set iflag.
		 * Same through ICRNL, no BSD equivs for IUCLC, IENQAK
		 */
D 11
		tiop->c_iflag = tios.c_iflag & 0x1ff;
E 11
I 11
		htios.c_iflag = tios.c_iflag & 0x1ff;
E 11
		if (tios.c_iflag & IXON)
D 11
			tiop->c_iflag |= TIO_IXON;
E 11
I 11
			htios.c_iflag |= TIO_IXON;
E 11
		if (tios.c_iflag & IXOFF)
D 11
			tiop->c_iflag |= TIO_IXOFF;
E 11
I 11
			htios.c_iflag |= TIO_IXOFF;
E 11
		if (tios.c_iflag & IXANY)
D 11
			tiop->c_iflag |= TIO_IXANY;
E 11
I 11
			htios.c_iflag |= TIO_IXANY;
E 11
		/*
		 * Set oflag.
		 * No BSD equivs for OLCUC/OCRNL/ONOCR/ONLRET/OFILL/OFDEL
		 * or any of the delays.
		 */
		if (tios.c_oflag & OPOST)
D 11
			tiop->c_oflag |= TIO_OPOST;
E 11
I 11
			htios.c_oflag |= TIO_OPOST;
E 11
		if (tios.c_oflag & ONLCR)
D 11
			tiop->c_oflag |= TIO_ONLCR;
E 11
I 11
			htios.c_oflag |= TIO_ONLCR;
E 11
		if (tios.c_oflag & OXTABS)
E 4
D 11
			tiop->c_oflag |= TIO_TAB3;
E 11
I 11
			htios.c_oflag |= TIO_TAB3;
E 11
D 4
		else if (flag & TBDELAY)
			tiop->c_oflag |= TIO_TAB1;
		if (flag & LCASE) {
			tiop->c_iflag |= TIO_IUCLC;
			tiop->c_oflag |= TIO_OLCUC;
			tiop->c_lflag |= TIO_XCASE;
E 4
I 4
		/*
		 * Set cflag.
		 * Baud from ospeed, rest from cflag.
		 */
D 11
		tiop->c_cflag = bsdtohpuxbaud(tios.c_ospeed);
E 11
I 11
		htios.c_cflag = bsdtohpuxbaud(tios.c_ospeed);
E 11
		switch (tios.c_cflag & CSIZE) {
		case CS5:
D 11
			tiop->c_cflag |= TIO_CS5; break;
E 11
I 11
			htios.c_cflag |= TIO_CS5; break;
E 11
		case CS6:
D 11
			tiop->c_cflag |= TIO_CS6; break;
E 11
I 11
			htios.c_cflag |= TIO_CS6; break;
E 11
		case CS7:
D 11
			tiop->c_cflag |= TIO_CS7; break;
E 11
I 11
			htios.c_cflag |= TIO_CS7; break;
E 11
		case CS8:
D 11
			tiop->c_cflag |= TIO_CS8; break;
E 11
I 11
			htios.c_cflag |= TIO_CS8; break;
E 11
E 4
		}
D 4
		if (flag & ECHO)
E 4
I 4
		if (tios.c_cflag & CSTOPB)
D 11
			tiop->c_cflag |= TIO_CSTOPB;
E 11
I 11
			htios.c_cflag |= TIO_CSTOPB;
E 11
		if (tios.c_cflag & CREAD)
D 11
			tiop->c_cflag |= TIO_CREAD;
E 11
I 11
			htios.c_cflag |= TIO_CREAD;
E 11
		if (tios.c_cflag & PARENB)
D 11
			tiop->c_cflag |= TIO_PARENB;
E 11
I 11
			htios.c_cflag |= TIO_PARENB;
E 11
		if (tios.c_cflag & PARODD)
D 11
			tiop->c_cflag |= TIO_PARODD;
E 11
I 11
			htios.c_cflag |= TIO_PARODD;
E 11
		if (tios.c_cflag & HUPCL)
D 11
			tiop->c_cflag |= TIO_HUPCL;
E 11
I 11
			htios.c_cflag |= TIO_HUPCL;
E 11
		if (tios.c_cflag & CLOCAL)
D 11
			tiop->c_cflag |= TIO_CLOCAL;
E 11
I 11
			htios.c_cflag |= TIO_CLOCAL;
E 11
		/*
		 * Set lflag.
		 * No BSD equiv for XCASE.
		 */
		if (tios.c_lflag & ECHOE)
D 11
			tiop->c_lflag |= TIO_ECHOE;
E 11
I 11
			htios.c_lflag |= TIO_ECHOE;
E 11
		if (tios.c_lflag & ECHOK)
D 11
			tiop->c_lflag |= TIO_ECHOK;
E 11
I 11
			htios.c_lflag |= TIO_ECHOK;
E 11
		if (tios.c_lflag & ECHO)
E 4
D 11
			tiop->c_lflag |= TIO_ECHO;
E 11
I 11
			htios.c_lflag |= TIO_ECHO;
E 11
D 4
		if (flag & CRMOD) {
			tiop->c_iflag |= TIO_ICRNL;
			tiop->c_oflag |= TIO_ONLCR;
			if (flag & CR1)
				tiop->c_oflag |= TIO_CR1;
			if (flag & CR2)
				tiop->c_oflag |= TIO_CR2|TIO_ONOCR;
E 4
I 4
		if (tios.c_lflag & ECHONL)
D 11
			tiop->c_lflag |= TIO_ECHONL;
E 11
I 11
			htios.c_lflag |= TIO_ECHONL;
E 11
		if (tios.c_lflag & ISIG)
D 11
			tiop->c_lflag |= TIO_ISIG;
E 11
I 11
			htios.c_lflag |= TIO_ISIG;
E 11
		if (tios.c_lflag & ICANON)
D 11
			tiop->c_lflag |= TIO_ICANON;
E 11
I 11
			htios.c_lflag |= TIO_ICANON;
E 11
		if (tios.c_lflag & NOFLSH)
D 11
			tiop->c_lflag |= TIO_NOFLSH;
E 11
I 11
			htios.c_lflag |= TIO_NOFLSH;
E 11
		/*
		 * Line discipline
		 */
D 11
		line = 0;
D 8
		(void) (*ioctlrout)(fp, TIOCGETD, (caddr_t)&line);
E 8
I 8
		(void) (*ioctlrout)(fp, TIOCGETD, (caddr_t)&line, p);
E 8
		tiop->c_line = line;
E 11
I 11
		if (!newi) {
			line = 0;
			(void) (*ioctlrout)(fp, TIOCGETD, (caddr_t)&line, p);
			htios.c_reserved = line;
		}
E 11
		/*
D 11
		 * Set editing chars
E 11
I 11
		 * Set editing chars.
		 * No BSD equiv for VSWTCH.
E 11
		 */
D 11
		tiop->c_cc[HPUXVINTR] = tios.c_cc[VINTR];
		tiop->c_cc[HPUXVQUIT] = tios.c_cc[VQUIT];
		tiop->c_cc[HPUXVERASE] = tios.c_cc[VERASE];
		tiop->c_cc[HPUXVKILL] = tios.c_cc[VKILL];
		if (tiop->c_lflag & TIO_ICANON) {
			tiop->c_cc[HPUXVEOF] = tios.c_cc[VEOF];
			tiop->c_cc[HPUXVEOL] = tios.c_cc[VEOL];
E 4
		} else {
D 4
			tiop->c_oflag |= TIO_ONLRET;
			if (flag & NL1)
				tiop->c_oflag |= TIO_CR1;
			if (flag & NL2)
				tiop->c_oflag |= TIO_CR2;
E 4
I 4
			tiop->c_cc[HPUXVMIN] = tios.c_cc[VMIN];
			tiop->c_cc[HPUXVTIME] = tios.c_cc[VTIME];
E 4
		}
E 11
I 11
		htios.c_cc[HPUXVINTR] = tios.c_cc[VINTR];
		htios.c_cc[HPUXVQUIT] = tios.c_cc[VQUIT];
		htios.c_cc[HPUXVERASE] = tios.c_cc[VERASE];
		htios.c_cc[HPUXVKILL] = tios.c_cc[VKILL];
		htios.c_cc[HPUXVEOF] = tios.c_cc[VEOF];
		htios.c_cc[HPUXVEOL] = tios.c_cc[VEOL];
		htios.c_cc[HPUXVEOL2] = tios.c_cc[VEOL2];
		htios.c_cc[HPUXVSWTCH] = 0;
I 19
#if 1
		/*
		 * XXX since VMIN and VTIME are not implemented,
		 * we need to return something reasonable.
		 * Otherwise a GETA/SETA combo would always put
		 * the tty in non-blocking mode (since VMIN == VTIME == 0).
		 */
		if (fp->f_flag & FNONBLOCK) {
			htios.c_cc[HPUXVMINS] = 0;
			htios.c_cc[HPUXVTIMES] = 0;
		} else {
			htios.c_cc[HPUXVMINS] = 6;
			htios.c_cc[HPUXVTIMES] = 1;
		}
#else
E 19
		htios.c_cc[HPUXVMINS] = tios.c_cc[VMIN];
		htios.c_cc[HPUXVTIMES] = tios.c_cc[VTIME];
I 19
#endif
E 19
		htios.c_cc[HPUXVSUSP] = tios.c_cc[VSUSP];
		htios.c_cc[HPUXVSTART] = tios.c_cc[VSTART];
		htios.c_cc[HPUXVSTOP] = tios.c_cc[VSTOP];
		if (newi)
			bcopy((char *)&htios, data, sizeof htios);
		else
			termiostotermio(&htios, (struct hpuxtermio *)data);
E 11
D 4
		if (flag & RAW) {
			tiop->c_cflag |= TIO_CS8;
			tiop->c_iflag &= ~(TIO_ICRNL|TIO_IUCLC);
			tiop->c_cc[HPUXVMIN] = 6;
			tiop->c_cc[HPUXVTIME] = 1;
		} else {
			tiop->c_iflag |= TIO_BRKINT;
			if (tc.bsdt_startc == CSTART && tc.bsdt_stopc == CSTOP)
				tiop->c_iflag |= TIO_IXON;
			if (flag & TANDEM)
				tiop->c_iflag |= TIO_IXOFF;
			else if ((lmode & LDECCTQ) == 0)
				tiop->c_iflag |= TIO_IXANY;
			if ((lmode & LLITOUT) == 0) {
				tiop->c_iflag |= TIO_IGNPAR;
				tiop->c_oflag |= TIO_OPOST;
			}
			if (lmode & LPASS8)
				tiop->c_cflag |= TIO_CS8;
			else
				tiop->c_iflag |= TIO_ISTRIP;
			tiop->c_cflag |= TIO_CS7|TIO_PARENB;
			tiop->c_lflag |= TIO_ISIG;
			if (flag & CBREAK) {
				tiop->c_cc[HPUXVMIN] = 6;
				tiop->c_cc[HPUXVTIME] = 1;
			} else {
				tiop->c_lflag |= TIO_ICANON|TIO_ECHOK;
				if (lmode & LCRTERA)
					tiop->c_lflag |= TIO_ECHOE;
				tiop->c_cc[HPUXVEOF] = tc.bsdt_eofc;
				tiop->c_cc[HPUXVEOL] = tc.bsdt_brkc;
			}
		}
		tiop->c_cflag |= TIO_PARENB;
		if (flag & ODDP) {
			if (flag & EVENP)
				tiop->c_cflag &= ~TIO_PARENB;
			tiop->c_cflag |= TIO_PARODD;
		}
		if (tiop->c_cflag & TIO_PARENB)
			tiop->c_iflag |= TIO_INPCK;
		if (flag & VTDELAY)
			tiop->c_oflag |= TIO_FFDLY;
		if (flag & BSDELAY)
			tiop->c_oflag |= TIO_BSDLY;
E 4
		break;

I 11
	case HPUXTCSETATTR:
	case HPUXTCSETATTRD:
	case HPUXTCSETATTRF:
		newi = 1;
		/* fall into ... */
E 11
	case HPUXTCSETA:
	case HPUXTCSETAW:
	case HPUXTCSETAF:
I 11
D 12
		if (newi)
			bcopy(data, (char *)&htios, sizeof htios);
		else
			termiototermios((struct termio *)data, &htios);
E 12
E 11
D 4
		/* get old lmode and determine if we are a tty */
D 2
		if (u.u_error = ioctlrout(fp, TIOCLGET, (caddr_t)&lmode))
E 2
I 2
		if (error = ioctlrout(fp, TIOCLGET, (caddr_t)&lmode))
E 4
I 4
		/*
		 * Get old characteristics and determine if we are a tty.
		 */
D 8
		if (error = (*ioctlrout)(fp, TIOCGETA, (caddr_t)&tios))
E 8
I 8
		if (error = (*ioctlrout)(fp, TIOCGETA, (caddr_t)&tios, p))
E 8
E 4
E 2
			break;
I 12
		if (newi)
			bcopy(data, (char *)&htios, sizeof htios);
		else
			termiototermios((struct termio *)data, &htios, &tios);
E 12
D 4
		(void) ioctlrout(fp, TIOCGLTC, (caddr_t)&ltc);

		/* set baud rate */
		sg.sg_ispeed = hpuxtobsdbaud[tiop->c_cflag&TIO_CBAUD];
		sg.sg_ospeed = sg.sg_ispeed;

		/* set special chars to defaults for cooked mode */
		sg.sg_erase = tiop->c_cc[HPUXVERASE];
		sg.sg_kill = tiop->c_cc[HPUXVKILL];
		tc.bsdt_intrc = tiop->c_cc[HPUXVINTR];
		tc.bsdt_quitc = tiop->c_cc[HPUXVQUIT];
		tc.bsdt_startc = CSTART;
		tc.bsdt_stopc = CSTOP;
		tc.bsdt_eofc = tiop->c_cc[HPUXVEOF];
		tc.bsdt_brkc = tiop->c_cc[HPUXVEOL];
		ltc.bsdt_suspc = CSUSP;
		ltc.bsdt_dsuspc = CDSUSP;
D 2
		ltc.bsdt_flushc = CFLUSH;
E 2
I 2
		ltc.bsdt_flushc = CDISCARD;
E 2
		ltc.bsdt_lnextc = CLNEXT;

		/* set flags */
		flag = 0;
		if (tiop->c_oflag & TIO_BSDLY)
			flag |= BSDELAY;
		if (tiop->c_oflag & TIO_FFDLY)
			flag |= VTDELAY;
		if (tiop->c_oflag & TIO_TAB1) {
			if (tiop->c_oflag & TIO_TAB2)
				flag |= XTABS;
			else
				flag |= TAB1;
		} else if (tiop->c_oflag & TIO_TAB2)
			flag |= TAB2;
		if (tiop->c_oflag & TIO_CR1) {
			flag |= CR1;
			if (tiop->c_oflag & TIO_ONLRET)
				flag |= NL1;
		}
		if (tiop->c_oflag & TIO_CR2) {
			flag |= CR2;
			if (tiop->c_oflag & TIO_ONLRET)
				flag |= NL2;
		}
		if ((tiop->c_oflag & (TIO_NLDLY|TIO_ONLRET)) == TIO_NLDLY)
			flag |= NL2;
		if ((tiop->c_cflag & TIO_PARENB) == 0)
			flag |= ODDP|EVENP;
		else if (tiop->c_cflag & TIO_PARODD)
			flag |= ODDP;
		else
			flag |= EVENP;
		if ((tiop->c_iflag & TIO_ICRNL) || (tiop->c_oflag & TIO_ONLCR))
			flag |= CRMOD;
		if (tiop->c_lflag & TIO_ECHO)
			flag |= ECHO;
		if (tiop->c_iflag & TIO_IUCLC)
			flag |= LCASE;
E 4
I 4
		/*
		 * Set iflag.
		 * Same through ICRNL, no HP-UX equiv for IMAXBEL
		 */
		tios.c_iflag &= ~(IXON|IXOFF|IXANY|0x1ff);
D 11
		tios.c_iflag |= tiop->c_iflag & 0x1ff;
		if (tiop->c_iflag & TIO_IXON)
E 11
I 11
		tios.c_iflag |= htios.c_iflag & 0x1ff;
		if (htios.c_iflag & TIO_IXON)
E 11
			tios.c_iflag |= IXON;
E 4
D 11
		if (tiop->c_iflag & TIO_IXOFF)
E 11
I 11
		if (htios.c_iflag & TIO_IXOFF)
E 11
D 4
			flag |= TANDEM;
		if ((tiop->c_lflag & TIO_ICANON) == 0) {
			if (tiop->c_lflag & TIO_ISIG)
				flag |= CBREAK;
			else
				flag |= RAW;
E 4
I 4
			tios.c_iflag |= IXOFF;
D 11
		if (tiop->c_iflag & TIO_IXANY)
E 11
I 11
		if (htios.c_iflag & TIO_IXANY)
E 11
			tios.c_iflag |= IXANY;
		/*
		 * Set oflag.
		 * No HP-UX equiv for ONOEOT
		 */
		tios.c_oflag &= ~(OPOST|ONLCR|OXTABS);
D 11
		if (tiop->c_oflag & TIO_OPOST)
E 11
I 11
		if (htios.c_oflag & TIO_OPOST)
E 11
			tios.c_oflag |= OPOST;
D 11
		if (tiop->c_oflag & TIO_ONLCR)
E 11
I 11
		if (htios.c_oflag & TIO_ONLCR)
E 11
			tios.c_oflag |= ONLCR;
D 11
		if (tiop->c_oflag & TIO_TAB3)
E 11
I 11
		if (htios.c_oflag & TIO_TAB3)
E 11
			tios.c_oflag |= OXTABS;
		/*
		 * Set cflag.
		 * No HP-UX equiv for CCTS_OFLOW/CCTS_IFLOW/MDMBUF
		 */
		tios.c_cflag &=
			~(CSIZE|CSTOPB|CREAD|PARENB|PARODD|HUPCL|CLOCAL);
D 11
		switch (tiop->c_cflag & TIO_CSIZE) {
E 11
I 11
		switch (htios.c_cflag & TIO_CSIZE) {
E 11
		case TIO_CS5:
			tios.c_cflag |= CS5; break;
		case TIO_CS6:
			tios.c_cflag |= CS6; break;
		case TIO_CS7:
			tios.c_cflag |= CS7; break;
		case TIO_CS8:
			tios.c_cflag |= CS8; break;
E 4
		}
D 4
		if (flag & CBREAK) {
			ltc.bsdt_suspc = ltc.bsdt_dsuspc = -1;
			ltc.bsdt_flushc = ltc.bsdt_lnextc = -1;
			if ((tiop->c_iflag & TIO_IXON) == 0)
				tc.bsdt_startc = tc.bsdt_stopc = -1;
		}
		sg.sg_flags = flag;
		lmode &= ~(LCRTERA|LLITOUT|LDECCTQ|LPASS8);
E 4
I 4
D 11
		if (tiop->c_cflag & TIO_CSTOPB)
E 11
I 11
		if (htios.c_cflag & TIO_CSTOPB)
E 11
			tios.c_cflag |= CSTOPB;
D 11
		if (tiop->c_cflag & TIO_CREAD)
E 11
I 11
		if (htios.c_cflag & TIO_CREAD)
E 11
			tios.c_cflag |= CREAD;
D 11
		if (tiop->c_cflag & TIO_PARENB)
E 11
I 11
		if (htios.c_cflag & TIO_PARENB)
E 11
			tios.c_cflag |= PARENB;
D 11
		if (tiop->c_cflag & TIO_PARODD)
E 11
I 11
		if (htios.c_cflag & TIO_PARODD)
E 11
			tios.c_cflag |= PARODD;
D 11
		if (tiop->c_cflag & TIO_HUPCL)
E 11
I 11
		if (htios.c_cflag & TIO_HUPCL)
E 11
			tios.c_cflag |= HUPCL;
D 11
		if (tiop->c_cflag & TIO_CLOCAL)
E 11
I 11
		if (htios.c_cflag & TIO_CLOCAL)
E 11
			tios.c_cflag |= CLOCAL;
		/*
		 * Set lflag.
		 * No HP-UX equiv for ECHOKE/ECHOPRT/ECHOCTL
		 * IEXTEN treated as part of ICANON
		 */
		tios.c_lflag &= ~(ECHOE|ECHOK|ECHO|ISIG|ICANON|IEXTEN|NOFLSH);
E 4
D 11
		if (tiop->c_lflag & TIO_ECHOE)
E 11
I 11
		if (htios.c_lflag & TIO_ECHOE)
E 11
D 4
			lmode |= LCRTERA;
		if ((tiop->c_oflag & TIO_OPOST) == 0)
			lmode |= LLITOUT;
		if ((tiop->c_iflag & TIO_IXANY) == 0)
			lmode |= LDECCTQ;
		if ((tiop->c_cflag & TIO_CS8) &&
		    (tiop->c_iflag & TIO_ISTRIP) == 0)
			lmode |= LPASS8;

		/* set the new stuff */
E 4
I 4
			tios.c_lflag |= ECHOE;
D 11
		if (tiop->c_lflag & TIO_ECHOK)
E 11
I 11
		if (htios.c_lflag & TIO_ECHOK)
E 11
			tios.c_lflag |= ECHOK;
D 11
		if (tiop->c_lflag & TIO_ECHO)
E 11
I 11
		if (htios.c_lflag & TIO_ECHO)
E 11
			tios.c_lflag |= ECHO;
D 11
		if (tiop->c_lflag & TIO_ECHONL)
E 11
I 11
		if (htios.c_lflag & TIO_ECHONL)
E 11
			tios.c_lflag |= ECHONL;
D 11
		if (tiop->c_lflag & TIO_ISIG)
E 11
I 11
		if (htios.c_lflag & TIO_ISIG)
E 11
			tios.c_lflag |= ISIG;
D 11
		if (tiop->c_lflag & TIO_ICANON)
E 11
I 11
		if (htios.c_lflag & TIO_ICANON)
E 11
			tios.c_lflag |= (ICANON|IEXTEN);
D 11
		if (tiop->c_lflag & TIO_NOFLSH)
E 11
I 11
		if (htios.c_lflag & TIO_NOFLSH)
E 11
			tios.c_lflag |= NOFLSH;
		/*
		 * Set editing chars.
D 11
		 * No HP-UX equivs of VEOL2/VWERASE/VREPRINT/VSUSP/VDSUSP
		 * VSTOP/VLNEXT/VDISCARD/VMIN/VTIME/VSTATUS/VERASE2
E 11
I 11
		 * No HP-UX equivs of VWERASE/VREPRINT/VDSUSP/VLNEXT
		 * /VDISCARD/VSTATUS/VERASE2
E 11
		 */
D 11
		tios.c_cc[VINTR] = tiop->c_cc[HPUXVINTR];
		tios.c_cc[VQUIT] = tiop->c_cc[HPUXVQUIT];
		tios.c_cc[VERASE] = tiop->c_cc[HPUXVERASE];
		tios.c_cc[VKILL] = tiop->c_cc[HPUXVKILL];
		if (tios.c_lflag & ICANON) {
			tios.c_cc[VEOF] = tiop->c_cc[HPUXVEOF];
			tios.c_cc[VEOL] = tiop->c_cc[HPUXVEOL];
		} else {
			tios.c_cc[VMIN] = tiop->c_cc[HPUXVMIN];
			tios.c_cc[VTIME] = tiop->c_cc[HPUXVTIME];
		}
E 11
I 11
		tios.c_cc[VINTR] = htios.c_cc[HPUXVINTR];
		tios.c_cc[VQUIT] = htios.c_cc[HPUXVQUIT];
		tios.c_cc[VERASE] = htios.c_cc[HPUXVERASE];
		tios.c_cc[VKILL] = htios.c_cc[HPUXVKILL];
		tios.c_cc[VEOF] = htios.c_cc[HPUXVEOF];
		tios.c_cc[VEOL] = htios.c_cc[HPUXVEOL];
		tios.c_cc[VEOL2] = htios.c_cc[HPUXVEOL2];
		tios.c_cc[VMIN] = htios.c_cc[HPUXVMINS];
		tios.c_cc[VTIME] = htios.c_cc[HPUXVTIMES];
		tios.c_cc[VSUSP] = htios.c_cc[HPUXVSUSP];
		tios.c_cc[VSTART] = htios.c_cc[HPUXVSTART];
		tios.c_cc[VSTOP] = htios.c_cc[HPUXVSTOP];

E 11
		/*
		 * Set the new stuff
		 */
E 4
D 11
		if (com == HPUXTCSETA)
E 11
I 11
		if (com == HPUXTCSETA || com == HPUXTCSETATTR)
E 11
D 4
			com = TIOCSETN;
E 4
I 4
			com = TIOCSETA;
D 11
		else if (com == HPUXTCSETAW)
E 11
I 11
		else if (com == HPUXTCSETAW || com == HPUXTCSETATTRD)
E 11
			com = TIOCSETAW;
E 4
		else
D 4
			com = TIOCSETP;
		(void) ioctlrout(fp, com, (caddr_t)&sg);
		(void) ioctlrout(fp, TIOCSETC, (caddr_t)&tc);
		(void) ioctlrout(fp, TIOCSLTC, (caddr_t)&ltc);
		(void) ioctlrout(fp, TIOCLSET, (caddr_t)&lmode);
		if (tiop->c_cflag & TIO_HUPCL)
			(void) ioctlrout(fp, TIOCHPCL, (caddr_t)0);
E 4
I 4
			com = TIOCSETAF;
D 8
		error = (*ioctlrout)(fp, com, (caddr_t)&tios);
E 8
I 8
		error = (*ioctlrout)(fp, com, (caddr_t)&tios, p);
E 8
		if (error == 0) {
			/*
			 * Set line discipline
			 */
D 11
			line = tiop->c_line;
D 8
			(void) (*ioctlrout)(fp, TIOCSETD, (caddr_t)&line);
E 8
I 8
			(void) (*ioctlrout)(fp, TIOCSETD, (caddr_t)&line, p);
E 11
I 11
			if (!newi) {
				line = htios.c_reserved;
				(void) (*ioctlrout)(fp, TIOCSETD,
						    (caddr_t)&line, p);
			}
E 11
E 8
			/*
D 19
			 * Set non-blocking IO if VMIN == VTIME == 0.
			 * Should handle the other cases as well.  It also
			 * isn't correct to just turn it off as it could be
			 * on as the result of a fcntl operation.
E 19
I 19
			 * Set non-blocking IO if VMIN == VTIME == 0, clear
			 * if not.  Should handle the other cases as well.
			 * Note it isn't correct to just turn NBIO off like
			 * we do as it could be on as the result of a fcntl
			 * operation.
			 *
E 19
			 * XXX - wouldn't need to do this at all if VMIN/VTIME
			 * were implemented.
			 */
D 11
			line = (tiop->c_cc[HPUXVMIN] == 0 &&
				tiop->c_cc[HPUXVTIME] == 0);
E 11
I 11
D 19
			line = (htios.c_cc[HPUXVMIN] == 0 &&
				htios.c_cc[HPUXVTIME] == 0);
E 11
D 8
			(void) fset(fp, FNDELAY, line);
E 8
I 8
			if (line)
D 9
				fp->f_flag |= FNDELAY;
E 9
I 9
				fp->f_flag |= FNONBLOCK;
E 9
			else
D 9
				fp->f_flag &= ~FNDELAY;
E 9
I 9
				fp->f_flag &= ~FNONBLOCK;
E 9
			(void) (*ioctlrout)(fp, FIONBIO, (caddr_t)&line, p);
E 19
I 19
			{
				struct hpuxfcntl_args {
					int fdes, cmd, arg;
				} args;
				int flags, nbio;

				nbio = (htios.c_cc[HPUXVMINS] == 0 &&
					htios.c_cc[HPUXVTIMES] == 0);
				if (nbio && (fp->f_flag & FNONBLOCK) == 0 ||
				    !nbio && (fp->f_flag & FNONBLOCK)) {
					args.fdes = fd;
					args.cmd = F_GETFL;
					args.arg = 0;
					(void) hpuxfcntl(p, &args, &flags);
					if (nbio)
						flags |= HPUXNDELAY;
					else
						flags &= ~HPUXNDELAY;
					args.cmd = F_SETFL;
					args.arg = flags;
					(void) hpuxfcntl(p, &args, &flags);
				}
			}
E 19
E 8
		}
E 4
		break;

D 2
	case HPUXTIOCGETP:
		u.u_error = ioctlrout(fp, TIOCGETP, (caddr_t)&sg);
		if (u.u_error)
			break;
		flag = sg.sg_flags;
		sg.sg_flags &= ~(V7_HUPCL|V7_XTABS|V7_NOAL);
		if (flag & XTABS)
			sg.sg_flags |= V7_XTABS;
		bcopy((caddr_t)&sg, data, sizeof sg);
		break;

	case HPUXTIOCSETP:
		bcopy(data, (caddr_t)&sg, sizeof sg);
		flag = sg.sg_flags;
		sg.sg_flags &= ~(V7_HUPCL|V7_XTABS|V7_NOAL);
		if (flag & V7_XTABS)
			sg.sg_flags |= XTABS;
		u.u_error = ioctlrout(fp, TIOCSETP, (caddr_t)&sg);
		if (flag & V7_HUPCL)
			(void) ioctlrout(fp, TIOCHPCL, (caddr_t)0);
		break;

E 2
	default:
I 2
		error = EINVAL;
E 2
		break;
	}
D 2
	return(u.u_error);
E 2
I 2
	return(error);
I 4
}

I 11
D 12
termiototermios(tio, tios)
E 12
I 12
termiototermios(tio, tios, bsdtios)
E 12
	struct hpuxtermio *tio;
	struct hpuxtermios *tios;
I 12
	struct termios *bsdtios;
E 12
{
	int i;

	bzero((char *)tios, sizeof *tios);
	tios->c_iflag = tio->c_iflag;
	tios->c_oflag = tio->c_oflag;
	tios->c_cflag = tio->c_cflag;
	tios->c_lflag = tio->c_lflag;
	tios->c_reserved = tio->c_line;
	for (i = 0; i <= HPUXVSWTCH; i++)
		tios->c_cc[i] = tio->c_cc[i];
	if (tios->c_lflag & TIO_ICANON) {
		tios->c_cc[HPUXVEOF] = tio->c_cc[HPUXVEOF];
		tios->c_cc[HPUXVEOL] = tio->c_cc[HPUXVEOL];
D 17
		tios->c_cc[HPUXVMINS] = tios->c_cc[HPUXVTIMES] = 0;
E 17
I 17
		tios->c_cc[HPUXVMINS] = 0;
		tios->c_cc[HPUXVTIMES] = 0;
E 17
	} else {
D 17
		tios->c_cc[HPUXVEOF] = tios->c_cc[HPUXVEOL] = 0;
E 17
I 17
		tios->c_cc[HPUXVEOF] = 0;
		tios->c_cc[HPUXVEOL] = 0;
E 17
		tios->c_cc[HPUXVMINS] = tio->c_cc[HPUXVMIN];
		tios->c_cc[HPUXVTIMES] = tio->c_cc[HPUXVTIME];
	}
I 12
D 17
	tios->c_cc[HPUXVMINS] = bsdtios->c_cc[VMIN];
	tios->c_cc[HPUXVTIMES] = bsdtios->c_cc[VTIME];
E 17
	tios->c_cc[HPUXVSUSP] = bsdtios->c_cc[VSUSP];
	tios->c_cc[HPUXVSTART] = bsdtios->c_cc[VSTART];
	tios->c_cc[HPUXVSTOP] = bsdtios->c_cc[VSTOP];
E 12
}

termiostotermio(tios, tio)
	struct hpuxtermios *tios;
	struct hpuxtermio *tio;
{
	int i;

	tio->c_iflag = tios->c_iflag;
	tio->c_oflag = tios->c_oflag;
	tio->c_cflag = tios->c_cflag;
	tio->c_lflag = tios->c_lflag;
	tio->c_line = tios->c_reserved;
	for (i = 0; i <= HPUXVSWTCH; i++)
		tio->c_cc[i] = tios->c_cc[i];
D 12
	if (tios->c_lflag & ICANON) {
E 12
I 12
	if (tios->c_lflag & TIO_ICANON) {
E 12
		tio->c_cc[HPUXVEOF] = tios->c_cc[HPUXVEOF];
		tio->c_cc[HPUXVEOL] = tios->c_cc[HPUXVEOL];
	} else {
		tio->c_cc[HPUXVMIN] = tios->c_cc[HPUXVMINS];
		tio->c_cc[HPUXVTIME] = tios->c_cc[HPUXVTIMES];
	}
}

E 11
bsdtohpuxbaud(bsdspeed)
	long bsdspeed;
{
	switch (bsdspeed) {
	case B0:     return(TIO_B0);
	case B50:    return(TIO_B50);
	case B75:    return(TIO_B75);
	case B110:   return(TIO_B110);
	case B134:   return(TIO_B134);
	case B150:   return(TIO_B150);
	case B200:   return(TIO_B200);
	case B300:   return(TIO_B300);
	case B600:   return(TIO_B600);
	case B1200:  return(TIO_B1200);
	case B1800:  return(TIO_B1800);
	case B2400:  return(TIO_B2400);
	case B4800:  return(TIO_B4800);
	case B9600:  return(TIO_B9600);
	case B19200: return(TIO_B19200);
	case B38400: return(TIO_B38400);
	default:     return(TIO_B0);
	}
}

hpuxtobsdbaud(hpuxspeed)
	int hpuxspeed;
{
	static char hpuxtobsdbaudtab[32] = {
		B0,	B50,	B75,	B110,	B134,	B150,	B200,	B300,
		B600,	B0,	B1200,	B1800,	B2400,	B0,	B4800,	B0,
		B9600,	B19200,	B38400,	B0,	B0,	B0,	B0,	B0,
		B0,	B0,	B0,	B0,	B0,	B0,	EXTA,	EXTB
	};

	return(hpuxtobsdbaudtab[hpuxspeed & TIO_CBAUD]);
E 4
E 2
}

D 11
/* #ifdef COMPAT */
E 11
I 11
#ifdef COMPAT_OHPUX
I 14
struct ohpuxsgtty_args {
	int	fdes;
	caddr_t	cmarg;
};
E 14
E 11
D 2
ohpuxgtty()
{
	struct a {
E 2
I 2
D 21
ohpuxgtty(p, uap, retval)
E 21
I 21
compat_43_hpuxgtty(p, uap, retval)
E 21
	struct proc *p;
D 14
	struct args {
E 2
		int	fdes;
		caddr_t	cmarg;
D 2
	} *uap = (struct a *)u.u_ap;
E 2
I 2
	} *uap;
E 14
I 14
	struct ohpuxsgtty_args *uap;
E 14
	int *retval;
{
E 2

D 2
	getsettty(uap->fdes, HPUXTIOCGETP, uap->cmarg);
E 2
I 2
D 3
	RETURN (getsettty(uap->fdes, HPUXTIOCGETP, uap->cmarg));
E 3
I 3
D 7
	return (getsettty(uap->fdes, HPUXTIOCGETP, uap->cmarg));
E 7
I 7
	return (getsettty(p, uap->fdes, HPUXTIOCGETP, uap->cmarg));
E 7
E 3
E 2
}

D 2
ohpuxstty()
{
	struct a {
E 2
I 2
D 21
ohpuxstty(p, uap, retval)
E 21
I 21
compat_43_hpuxstty(p, uap, retval)
E 21
	struct proc *p;
D 14
	struct args {
E 2
		int	fdes;
		caddr_t	cmarg;
D 2
	} *uap = (struct a *)u.u_ap;
E 2
I 2
	} *uap;
E 14
I 14
	struct ohpuxsgtty_args *uap;
E 14
	int *retval;
{
E 2

D 2
	getsettty(uap->fdes, HPUXTIOCSETP, uap->cmarg);
E 2
I 2
D 3
	RETURN (getsettty(uap->fdes, HPUXTIOCSETP, uap->cmarg));
E 3
I 3
D 7
	return (getsettty(uap->fdes, HPUXTIOCSETP, uap->cmarg));
E 7
I 7
	return (getsettty(p, uap->fdes, HPUXTIOCSETP, uap->cmarg));
E 7
E 3
E 2
}

/*
 * Simplified version of ioctl() for use by
 * gtty/stty and TIOCGETP/TIOCSETP.
 */
D 7
getsettty(fdes, com, cmarg)
E 7
I 7
getsettty(p, fdes, com, cmarg)
	struct proc *p;
E 7
	int fdes, com;
	caddr_t cmarg;
{
I 7
	register struct filedesc *fdp = p->p_fd;
E 7
	register struct file *fp;
	struct hpuxsgttyb hsb;
	struct sgttyb sb;
I 2
	int error;
E 2

D 2
	if ((unsigned)fdes >= NOFILE || (fp = u.u_ofile[fdes]) == NULL) {
		u.u_error = EBADF;
		return;
	}
	if ((fp->f_flag & (FREAD|FWRITE)) == 0) {
		u.u_error = EBADF;
		return;
	}
E 2
I 2
D 7
	if ((unsigned)fdes >= NOFILE || (fp = u.u_ofile[fdes]) == NULL)
E 7
I 7
D 8
	if (((unsigned)fdes) >= fdp->fd_maxfiles ||
	    (fp = OFILE(fdp, fdes)) == NULL)
E 8
I 8
	if (((unsigned)fdes) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[fdes]) == NULL)
E 8
E 7
		return (EBADF);
	if ((fp->f_flag & (FREAD|FWRITE)) == 0)
		return (EBADF);
E 2
	if (com == HPUXTIOCSETP) {
D 2
		u.u_error = copyin(cmarg, (caddr_t)&hsb, sizeof hsb);
		if (u.u_error)
			return;
E 2
I 2
		if (error = copyin(cmarg, (caddr_t)&hsb, sizeof hsb))
			return (error);
E 2
		sb.sg_ispeed = hsb.sg_ispeed;
		sb.sg_ospeed = hsb.sg_ospeed;
		sb.sg_erase = hsb.sg_erase;
		sb.sg_kill = hsb.sg_kill;
D 2
		sb.sg_flags = (short) hsb.sg_flags;
E 2
I 2
		sb.sg_flags = hsb.sg_flags & ~(V7_HUPCL|V7_XTABS|V7_NOAL);
		if (hsb.sg_flags & V7_XTABS)
			sb.sg_flags |= XTABS;
		if (hsb.sg_flags & V7_HUPCL)
D 8
			(void)(*fp->f_ops->fo_ioctl)(fp, TIOCHPCL, (caddr_t)0);
E 8
I 8
			(void)(*fp->f_ops->fo_ioctl)
				(fp, TIOCHPCL, (caddr_t)0, p);
E 8
E 2
		com = TIOCSETP;
	} else {
		bzero((caddr_t)&hsb, sizeof hsb);
		com = TIOCGETP;
	}
D 2
	u.u_error = (*fp->f_ops->fo_ioctl)(fp, com, (caddr_t)&sb);
	if (u.u_error == 0 && com == TIOCGETP) {
E 2
I 2
D 8
	error = (*fp->f_ops->fo_ioctl)(fp, com, (caddr_t)&sb);
E 8
I 8
	error = (*fp->f_ops->fo_ioctl)(fp, com, (caddr_t)&sb, p);
E 8
	if (error == 0 && com == TIOCGETP) {
E 2
		hsb.sg_ispeed = sb.sg_ispeed;
		hsb.sg_ospeed = sb.sg_ospeed;
		hsb.sg_erase = sb.sg_erase;
		hsb.sg_kill = sb.sg_kill;
D 2
		hsb.sg_flags = (int) sb.sg_flags;
		u.u_error = copyout((caddr_t)&hsb, cmarg, sizeof hsb);
E 2
I 2
		hsb.sg_flags = sb.sg_flags & ~(V7_HUPCL|V7_XTABS|V7_NOAL);
		if (sb.sg_flags & XTABS)
			hsb.sg_flags |= V7_XTABS;
		error = copyout((caddr_t)&hsb, cmarg, sizeof hsb);
E 2
	}
I 2
	return (error);
E 2
}
D 11
/* #endif */
E 11
I 11
#endif
E 11
#endif
E 1
