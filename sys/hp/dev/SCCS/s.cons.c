h18678
s 00002/00001/00154
d D 8.3 95/01/09 17:38:56 cgd 11 10
c strategy returns void, ioctl cmd is u_long
e
s 00003/00000/00152
d D 8.2 94/01/12 09:57:40 bostic 10 9
c lint
e
s 00002/00002/00150
d D 8.1 93/06/10 21:23:05 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00009/00143
d D 7.8 92/10/11 08:55:03 bostic 8 7
c make kernel includes standard
e
s 00002/00030/00150
d D 7.7 92/06/05 15:23:30 hibler 7 6
c merge latest Utah hp300 code including 68040 support
e
s 00024/00018/00156
d D 7.6 91/05/04 19:31:36 karels 6 5
c u. is gone; new device calling conventions
e
s 00008/00008/00166
d D 7.5 90/12/16 16:36:03 bostic 5 4
c kernel reorg
e
s 00001/00001/00173
d D 7.4 90/11/02 16:25:57 mckusick 4 3
c update identifier from Utah
e
s 00004/00004/00170
d D 7.3 90/06/06 16:36:45 mckusick 3 2
c need flags arguments
e
s 00007/00002/00167
d D 7.2 90/05/25 15:49:08 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00169/00000/00000
d D 7.1 90/05/08 18:09:07 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 4
 * from: Utah $Hdr: cons.c 1.4 88/12/03$
E 4
I 4
D 7
 * from: Utah $Hdr: cons.c 1.1 90/07/09$
E 7
I 7
 * from: Utah $Hdr: cons.c 1.7 92/01/21$
E 7
E 4
 *
 *	%W% (Berkeley) %G%
 */

D 5
#include "param.h"
#include "user.h"
#include "systm.h"
#include "buf.h"
#include "ioctl.h"
#include "tty.h"
#include "file.h"
#include "conf.h"
E 5
I 5
D 8
#include "sys/param.h"
D 6
#include "sys/user.h"
E 6
I 6
#include "sys/proc.h"
E 6
#include "sys/systm.h"
#include "sys/buf.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/file.h"
#include "sys/conf.h"
E 8
I 8
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/file.h>
#include <sys/conf.h>
E 8
E 5

D 8
#include "cons.h"
E 8
I 8
#include <hp/dev/cons.h>
E 8

D 7
/* XXX - all this could be autoconfig()ed */
#include "ite.h"
#if NITE > 0
int itecnprobe(), itecninit(), itecngetc(), itecnputc();
#endif
#include "dca.h"
#if NDCA > 0
int dcacnprobe(), dcacninit(), dcacngetc(), dcacnputc();
#endif
I 2
#include "dcm.h"
#if NDCM > 0
int dcmcnprobe(), dcmcninit(), dcmcngetc(), dcmcnputc();
#endif
E 2

struct	consdev constab[] = {
#if NITE > 0
	{ itecnprobe,	itecninit,	itecngetc,	itecnputc },
#endif
#if NDCA > 0
	{ dcacnprobe,	dcacninit,	dcacngetc,	dcacnputc },
#endif
I 2
#if NDCM > 0
	{ dcmcnprobe,	dcmcninit,	dcmcngetc,	dcmcnputc },
#endif
E 2
	{ 0 },
};
/* end XXX */
D 2

extern	struct consdev constab[];
E 2

struct	tty *constty = 0;	/* virtual console output device */
E 7
I 7
struct	tty *constty;		/* virtual console output device */
E 7
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

D 6
cnopen(dev, flag)
E 6
I 6
cnopen(dev, flag, mode, p)
E 6
	dev_t dev;
I 6
	int flag, mode;
	struct proc *p;
E 6
{
	if (cn_tab == NULL)
D 6
		return(0);
E 6
I 6
		return (0);
E 6
	dev = cn_tab->cn_dev;
D 6
	return ((*cdevsw[major(dev)].d_open)(dev, flag));
E 6
I 6
	return ((*cdevsw[major(dev)].d_open)(dev, flag, mode, p));
E 6
}
 
D 6
cnclose(dev, flag)
E 6
I 6
cnclose(dev, flag, mode, p)
E 6
	dev_t dev;
I 6
	int flag, mode;
	struct proc *p;
E 6
{
	if (cn_tab == NULL)
D 6
		return(0);
E 6
I 6
		return (0);
E 6
	dev = cn_tab->cn_dev;
D 6
	return ((*cdevsw[major(dev)].d_close)(dev, flag));
E 6
I 6
	return ((*cdevsw[major(dev)].d_close)(dev, flag, mode, p));
E 6
}
 
D 3
cnread(dev, uio)
E 3
I 3
cnread(dev, uio, flag)
E 3
	dev_t dev;
	struct uio *uio;
I 10
	int flag;
E 10
{
	if (cn_tab == NULL)
D 6
		return(0);
E 6
I 6
		return (0);
E 6
	dev = cn_tab->cn_dev;
D 3
	return ((*cdevsw[major(dev)].d_read)(dev, uio));
E 3
I 3
	return ((*cdevsw[major(dev)].d_read)(dev, uio, flag));
E 3
}
 
D 3
cnwrite(dev, uio)
E 3
I 3
cnwrite(dev, uio, flag)
E 3
	dev_t dev;
	struct uio *uio;
I 10
	int flag;
E 10
{
	if (cn_tab == NULL)
D 6
		return(0);
E 6
I 6
		return (0);
E 6
	dev = cn_tab->cn_dev;
D 3
	return ((*cdevsw[major(dev)].d_write)(dev, uio));
E 3
I 3
	return ((*cdevsw[major(dev)].d_write)(dev, uio, flag));
E 3
}
 
D 6
cnioctl(dev, cmd, data, flag)
E 6
I 6
cnioctl(dev, cmd, data, flag, p)
E 6
	dev_t dev;
I 10
D 11
	int cmd, flag;
E 11
I 11
	u_long cmd;
E 11
E 10
	caddr_t data;
I 11
	int flag;
E 11
I 6
	struct proc *p;
E 6
{
	int error;

	if (cn_tab == NULL)
D 6
		return(0);
E 6
I 6
		return (0);
E 6
	/*
	 * Superuser can always use this to wrest control of console
	 * output from the "virtual" console.
	 */
	if (cmd == TIOCCONS && constty) {
D 6
		error = suser(u.u_cred, &u.u_acflag);
E 6
I 6
		error = suser(p->p_ucred, (u_short *) NULL);
E 6
		if (error)
			return (error);
		constty = NULL;
		return (0);
	}
	dev = cn_tab->cn_dev;
D 6
	return ((*cdevsw[major(dev)].d_ioctl)(dev, cmd, data, flag));
E 6
I 6
	return ((*cdevsw[major(dev)].d_ioctl)(dev, cmd, data, flag, p));
E 6
}

/*ARGSUSED*/
D 6
cnselect(dev, rw)
E 6
I 6
cnselect(dev, rw, p)
E 6
	dev_t dev;
	int rw;
I 6
	struct proc *p;
E 6
{
	if (cn_tab == NULL)
D 6
		return(1);
	return(ttselect(cn_tab->cn_dev, rw));
E 6
I 6
		return (1);
	return (ttselect(cn_tab->cn_dev, rw, p));
E 6
}

cngetc()
{
	if (cn_tab == NULL)
D 6
		return(0);
	return((*cn_tab->cn_getc)(cn_tab->cn_dev));
E 6
I 6
		return (0);
	return ((*cn_tab->cn_getc)(cn_tab->cn_dev));
E 6
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
