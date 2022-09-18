/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	conskbd.c,v $
 * Revision 2.4  89/03/09  21:29:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:27:47  gm0w
 * 	Removed else legs of MACH and CMU conditionals and fixed 
 * 	includes as part of kernel cleanup.
 * 	[89/02/08            jjc]
 * 
 * 23-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Removed import of pte.h for MACH.
 *
 */

#ifndef	lint
static	char sccsid[] = "@(#)conskbd.c 1.1 86/02/03 Copyr 1983 Sun Micro";
#endif

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

/*
 * Console kbd driver for Sun.
 *
 * Indirects to kbddev found during autoconf.
 */

#include <sys/param.h>
#include <sys/conf.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/buf.h>
#include <sys/vmmac.h>
#include <sys/uio.h>
#include <sys/proc.h>

dev_t	kbddev = -1;
int	kbddevopen = 0;

/*ARGSUSED*/
conskbdopen(dev, flag)
	dev_t dev;
{
        int err;
        int ldisc = KBDLDISC;
        register struct cdevsw *dp;

	if (kbddev == -1)
		return (ENXIO);
	dp = &cdevsw[major(kbddev)];
        if (err = (*dp->d_open)(kbddev, flag))
                return (err);
	if (err = (*dp->d_ioctl) (kbddev, TIOCSETD, (caddr_t)&ldisc, flag))
                return (err);
	cdevsw[major(dev)].d_ttys = cdevsw[major(kbddev)].d_ttys+minor(kbddev);
	return (0);
}

/*ARGSUSED*/
conskbdclose(dev, flag)
	dev_t dev;
{

	if (kbddev != -1) {
		(*cdevsw[major(kbddev)].d_close)(kbddev, flag);
		cdevsw[major(dev)].d_ttys = 0;
	}
}

/*ARGSUSED*/
conskbdread(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	if (kbddev != -1)
		return ((*cdevsw[major(kbddev)].d_read)(kbddev, uio));
	return (ENXIO);
}

/*ARGSUSED*/
conskbdselect(dev, rw)
	dev_t dev;
	int rw;
{

	if (kbddev != -1)
		return ((*cdevsw[major(kbddev)].d_select)(kbddev, rw));
	return (ENXIO);
}

/*ARGSUSED*/
conskbdioctl(dev, cmd, data, flag)
	dev_t dev;
	caddr_t data;
{

	if (kbddev != -1)
		return ((*cdevsw[major(kbddev)].d_ioctl)
		    (kbddev, cmd, data, flag));
	return (ENOTTY);
}
