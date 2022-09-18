h39068
s 00002/00002/00166
d D 8.1 93/06/11 15:34:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/00158
d D 7.3 92/10/11 10:10:54 bostic 3 2
c make kernel includes standard
e
s 00035/00053/00133
d D 7.2 91/05/09 18:18:47 donn 2 1
c last minute changes for passing proc ptr
e
s 00186/00000/00000
d D 7.1 91/04/13 10:54:17 donn 1 0
c date and time created 91/04/13 10:54:17 by donn
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 2
 * Copyright (c) 1990 The Regents of the University of California.
E 2
I 2
D 4
 * Copyright (c) 1991 The Regents of the University of California.
E 2
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
D 2
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
D 2
 * from: Utah $Hdr: cons.c 1.1 90/07/09$
 *
 *	@(#)cons.c	7.5 (Berkeley) 12/16/90
E 2
I 2
 *	%W% (Berkeley) %G%
E 2
 */

I 2

E 2
D 3
#include "sys/param.h"
I 2
#include "sys/proc.h"
E 2
#include "sys/user.h"
#include "sys/systm.h"
#include "sys/buf.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/file.h"
#include "sys/conf.h"
E 3
I 3
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/file.h>
#include <sys/conf.h>
E 3

D 3
#include "cons.h"
E 3
I 3
#include <i386/i386/cons.h>
E 3

/* XXX - all this could be autoconfig()ed */
D 2
#include "ite.h"
#if NITE > 0
int itecnprobe(), itecninit(), itecngetc(), itecnputc();
E 2
I 2
int pccnprobe(), pccninit(), pccngetc(), pccnputc();
#include "com.h"
#if NCOM > 0
int comcnprobe(), comcninit(), comcngetc(), comcnputc();
E 2
#endif
D 2
#include "dca.h"
#if NDCA > 0
int dcacnprobe(), dcacninit(), dcacngetc(), dcacnputc();
#endif
#include "dcm.h"
#if NDCM > 0
int dcmcnprobe(), dcmcninit(), dcmcngetc(), dcmcnputc();
#endif
E 2

struct	consdev constab[] = {
D 2
#if NITE > 0
	{ itecnprobe,	itecninit,	itecngetc,	itecnputc },
E 2
I 2
	{ pccnprobe,	pccninit,	pccngetc,	pccnputc },
#if NCOM > 0
	{ comcnprobe,	comcninit,	comcngetc,	comcnputc },
E 2
#endif
D 2
#if NDCA > 0
	{ dcacnprobe,	dcacninit,	dcacngetc,	dcacnputc },
#endif
#if NDCM > 0
	{ dcmcnprobe,	dcmcninit,	dcmcngetc,	dcmcnputc },
#endif
E 2
	{ 0 },
};
/* end XXX */

struct	tty *constty = 0;	/* virtual console output device */
struct	consdev *cn_tab;	/* physical console device info */
struct	tty *cn_tty;		/* XXX: console tty struct for tprintf */

cninit()
{
	register struct consdev *cp;

	/*
	 * Collect information about all possible consoles
	 * and find the one with highest priority
	 */
	for (cp = constab; cp->cn_probe; cp++) {
		(*cp->cn_probe)(cp);
		if (cp->cn_pri > CN_DEAD &&
		    (cn_tab == NULL || cp->cn_pri > cn_tab->cn_pri))
			cn_tab = cp;
	}
	/*
	 * No console, we can handle it
	 */
	if ((cp = cn_tab) == NULL)
		return;
	/*
	 * Turn on console
	 */
	cn_tty = cp->cn_tp;
	(*cp->cn_init)(cp);
}

D 2
cnopen(dev, flag)
E 2
I 2
cnopen(dev, flag, mode, p)
E 2
	dev_t dev;
I 2
	int flag, mode;
	struct proc *p;
E 2
{
	if (cn_tab == NULL)
D 2
		return(0);
E 2
I 2
		return (0);
E 2
	dev = cn_tab->cn_dev;
D 2
	return ((*cdevsw[major(dev)].d_open)(dev, flag));
E 2
I 2
	return ((*cdevsw[major(dev)].d_open)(dev, flag, mode, p));
E 2
}
 
D 2
cnclose(dev, flag)
E 2
I 2
cnclose(dev, flag, mode, p)
E 2
	dev_t dev;
I 2
	int flag, mode;
	struct proc *p;
E 2
{
	if (cn_tab == NULL)
D 2
		return(0);
E 2
I 2
		return (0);
E 2
	dev = cn_tab->cn_dev;
D 2
	return ((*cdevsw[major(dev)].d_close)(dev, flag));
E 2
I 2
	return ((*cdevsw[major(dev)].d_close)(dev, flag, mode, p));
E 2
}
 
cnread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	if (cn_tab == NULL)
D 2
		return(0);
E 2
I 2
		return (0);
E 2
	dev = cn_tab->cn_dev;
	return ((*cdevsw[major(dev)].d_read)(dev, uio, flag));
}
 
cnwrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	if (cn_tab == NULL)
D 2
		return(0);
E 2
I 2
		return (0);
E 2
	dev = cn_tab->cn_dev;
	return ((*cdevsw[major(dev)].d_write)(dev, uio, flag));
}
 
D 2
cnioctl(dev, cmd, data, flag)
E 2
I 2
cnioctl(dev, cmd, data, flag, p)
E 2
	dev_t dev;
	caddr_t data;
I 2
	struct proc *p;
E 2
{
	int error;

	if (cn_tab == NULL)
D 2
		return(0);
E 2
I 2
		return (0);
E 2
	/*
	 * Superuser can always use this to wrest control of console
	 * output from the "virtual" console.
	 */
	if (cmd == TIOCCONS && constty) {
D 2
		error = suser(u.u_cred, &u.u_acflag);
E 2
I 2
		error = suser(p->p_ucred, (u_short *) NULL);
E 2
		if (error)
			return (error);
		constty = NULL;
		return (0);
	}
	dev = cn_tab->cn_dev;
D 2
	return ((*cdevsw[major(dev)].d_ioctl)(dev, cmd, data, flag));
E 2
I 2
	return ((*cdevsw[major(dev)].d_ioctl)(dev, cmd, data, flag, p));
E 2
}

/*ARGSUSED*/
D 2
cnselect(dev, rw)
E 2
I 2
cnselect(dev, rw, p)
E 2
	dev_t dev;
	int rw;
I 2
	struct proc *p;
E 2
{
	if (cn_tab == NULL)
D 2
		return(1);
	return(ttselect(cn_tab->cn_dev, rw));
E 2
I 2
		return (1);
	return (ttselect(cn_tab->cn_dev, rw, p));
E 2
}

cngetc()
{
	if (cn_tab == NULL)
D 2
		return(0);
	return((*cn_tab->cn_getc)(cn_tab->cn_dev));
E 2
I 2
		return (0);
	return ((*cn_tab->cn_getc)(cn_tab->cn_dev));
E 2
}

cnputc(c)
	register int c;
{
	if (cn_tab == NULL)
		return;
	if (c) {
		(*cn_tab->cn_putc)(cn_tab->cn_dev, c);
		if (c == '\n')
			(*cn_tab->cn_putc)(cn_tab->cn_dev, '\r');
	}
}
E 1
