h10040
s 00024/00001/00139
d D 8.2 94/01/11 16:05:43 mckusick 7 6
c print to virtual console so X screen isn't scrolled for console output (from ralph)
e
s 00002/00002/00138
d D 8.1 93/06/10 23:06:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00093/00033/00047
d D 7.5 92/11/15 16:30:27 ralph 5 4
c updates from Rick Macklem for maxine.
e
s 00011/00011/00069
d D 7.4 92/10/11 11:23:06 bostic 4 3
c make kernel includes standard
e
s 00005/00000/00075
d D 7.3 92/03/07 09:56:40 ralph 3 2
c added support for ds5000
e
s 00015/00003/00060
d D 7.2 92/02/29 11:47:02 ralph 2 1
c fixes to support kadb
e
s 00063/00000/00000
d D 7.1 92/01/07 17:29:19 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: cons.c 1.1 90/07/09$
 *
 *	%W% (Berkeley) %G%
 */

D 4
#include "param.h"
#include "proc.h"
#include "systm.h"
#include "buf.h"
#include "ioctl.h"
#include "tty.h"
#include "file.h"
#include "conf.h"
E 4
I 4
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/file.h>
#include <sys/conf.h>
E 4

D 4
#include "../include/machMon.h"
E 4
I 4
D 5
#include <machine/machMon.h>
E 5
I 5
#include <pmax/stand/dec_prom.h>
E 5
E 4

/*
D 5
 * Console output may be redirected to another tty
 * (e.g. a window); if so, constty will point to the current
 * virtual console.
E 5
I 5
 * Console I/O is redirected to the appropriate device, either a screen and
D 7
 * keyboard or a serial port.
E 7
I 7
 * keyboard, a serial port, or the "virtual" console.
E 7
E 5
 */
D 5
struct	tty *constty;		/* virtual console output device */
E 5
I 5
#include <pmax/pmax/cons.h>
E 5

I 7
extern struct tty *constty;	/* virtual console output device */

E 7
I 5
struct consdev cn_tab = {
	1,
	1,
	NODEV,
	(struct pmax_fb *)0,
	(int (*)())0,
	(int (*)())0,
	(void (*)())0,
	(struct tty *)0,
};

cnopen(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	if (cn_tab.cn_dev == NODEV)
		return (0);
	dev = cn_tab.cn_dev;
	return ((*cdevsw[major(dev)].d_open)(dev, flag, mode, p));
}
 
cnclose(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	if (cn_tab.cn_dev == NODEV)
		return (0);
	dev = cn_tab.cn_dev;
	return ((*cdevsw[major(dev)].d_close)(dev, flag, mode, p));
}
 
cnread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	if (cn_tab.cn_dev == NODEV)
		return (0);
	dev = cn_tab.cn_dev;
	return ((*cdevsw[major(dev)].d_read)(dev, uio, flag));
}
 
cnwrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
I 7
	if (constty)
		return ((*linesw[constty->t_line].l_write)(constty, uio, flag));
E 7
	if (cn_tab.cn_dev == NODEV)
		return (0);
	dev = cn_tab.cn_dev;
	return ((*cdevsw[major(dev)].d_write)(dev, uio, flag));
}
 
cnioctl(dev, cmd, data, flag, p)
	dev_t dev;
	caddr_t data;
	struct proc *p;
{
	int error;

I 7
	/*
	 * Superuser can always use this to wrest control of console
	 * output from the "virtual" console.
	 */
	if (cmd == TIOCCONS && constty) {
		error = suser(p->p_ucred, (u_short *) NULL);
		if (error)
			return (error);
		constty = NULL;
		return (0);
	}
#if 0
	if (constty) {
		error = (*linesw[constty->t_line].l_ioctl)
			(constty, cmd, data, flag, p);
		if (error >= 0)
			return (error);
	}
#endif
E 7
	if (cn_tab.cn_dev == NODEV)
		return (0);
	dev = cn_tab.cn_dev;
	return ((*cdevsw[major(dev)].d_ioctl)(dev, cmd, data, flag, p));
}

/*ARGSUSED*/
cnselect(dev, rw, p)
	dev_t dev;
	int rw;
	struct proc *p;
{
	if (cn_tab.cn_dev == NODEV)
		return (1);
	return (ttselect(cn_tab.cn_dev, rw, p));
}

E 5
/*
 * Get character from console.
 */
cngetc()
{
D 2
	int (*f)() = (int (*)())MACH_MON_GETCHAR;
E 2
I 2
D 5
	int (*f)();
#include "dc.h"
#if NDC > 0
D 4
#include "machine/dc7085cons.h"
#include "../dev/pdma.h"
E 4
I 4
#include <machine/dc7085cons.h>
#include <pmax/dev/pdma.h>
E 4
	extern struct pdma dcpdma[];
E 5
E 2

I 2
	/* check to be sure device has been initialized */
D 5
	if (dcpdma[0].p_addr)
		return (dcKBDGetc());
	f = (int (*)())MACH_MON_GETCHAR;
E 2
	return (*f)();
I 2
#else
	f = (int (*)())MACH_MON_GETCHAR;
	return (*f)();
#endif
E 5
I 5
	if (cn_tab.cn_dev == NODEV || cn_tab.cn_disabled)
		return ((*callv->getchar)());
	return ((*cn_tab.cn_getc)(cn_tab.cn_dev));
E 5
E 2
}

D 2
#include "pm.h"

E 2
/*
 * Print a character on console.
 */
cnputc(c)
	register int c;
{
I 2
D 5
#include "pm.h"
E 2
#if NPM > 0
	pmPutc(c);
#else
I 3
#include "cfb.h"
#if NCFB > 0
	cfbPutc(c);
#else
E 5
E 3
	int s;
D 5
	void (*f)() = (void (*)())MACH_MON_PUTCHAR;
E 5

D 5
	s = splhigh();
	(*f)(c);
	splx(s);
I 3
#endif
E 3
#endif
E 5
I 5
	if (cn_tab.cn_dev == NODEV || cn_tab.cn_disabled) {
		s = splhigh();
		(*callv->printf)("%c", c);
		splx(s);
	} else if (c) {
		if (c == '\n')
			(*cn_tab.cn_putc)(cn_tab.cn_dev, '\r');
		(*cn_tab.cn_putc)(cn_tab.cn_dev, c);
	}
E 5
}
E 1
