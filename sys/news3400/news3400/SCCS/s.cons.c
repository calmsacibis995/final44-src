h49130
s 00002/00002/00153
d D 8.1 93/06/11 15:02:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00147
d D 7.3 92/12/17 01:28:26 utashiro 3 2
c make kernel includes standard
e
s 00009/00000/00146
d D 7.2 92/06/26 18:23:30 utashiro 2 1
c support no-display configuration
e
s 00146/00000/00000
d D 7.1 92/06/04 16:06:53 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "param.h"
#include "proc.h"
#include "systm.h"
#include "buf.h"
#include "ioctl.h"
#include "tty.h"
#include "file.h"
#include "conf.h"
E 3
I 3
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/file.h>
#include <sys/conf.h>
E 3

I 2
#include "bm.h"

E 2
dev_t consdev = (dev_t)NULL;	/* initialized by consinit() */
struct tty *constty = 0;

vcopen(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	if ((dev = consdev) == NULL)
		return 0;
	return ((*cdevsw[major(dev)].d_open)(dev, flag, mode, p));
}

vcclose(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	if ((dev = consdev) == NULL)
		return 0;
	return ((*cdevsw[major(dev)].d_close)(dev, flag, mode, p));
}
 
vcread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	if ((dev = consdev) == NULL)
		return 0;
	return ((*cdevsw[major(dev)].d_read)(dev, uio, flag));
}
 
vcwrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
	int flag;
{
	if ((dev = consdev) == NULL)
		return 0;
	return ((*cdevsw[major(dev)].d_write)(dev, uio, flag));
}
 
vcstop(tp, flag)
	struct tty *tp;
	int flag;
{
	dev_t dev;

	if ((dev = consdev) == NULL)
		return 0;
	return ((*cdevsw[major(dev)].d_stop)(tp, flag));
}

vcioctl(dev, cmd, data, flag, p)
	dev_t dev;
	caddr_t data;
	struct proc *p;
{
	if ((dev = consdev) == NULL)
		return 0;
	return ((*cdevsw[major(dev)].d_ioctl)(dev, cmd, data, flag, p));
}

/*ARGSUSED*/
vcselect(dev, rw, p)
	dev_t dev;
	int rw;
	struct proc *p;
{
	if ((dev = consdev) == NULL)
		return 1;
	return (ttselect(dev, rw, p));
}

/*
 * Get character from console.
 */
cngetc()
{
	/* notyet */
	return(0);
}

#define	SCC_CONSOLE	0
/*
 * Print a character on console.
 */
cnputc(c)
	int c;
{
	int s;
	int (*putc)(), scccons_putc(), bmcons_putc();

	if (consdev == NULL)
		return 0;

I 2
#if NBM > 0
E 2
	if (consdev == makedev(1, 0))
		putc = scccons_putc;
	else
		putc = bmcons_putc;
I 2
#else
	putc = scccons_putc;
#endif
E 2

I 2
	/* KU: should be much more efficient */
E 2
	s = splhigh();
	putc(c);
	if (c == '\n')
		putc('\r');
	splx(s);
}

scccons_putc(c)
	int c;
{
	char cnbuf[1];

	cnbuf[0] = (char)c;
	scc_error_write(SCC_CONSOLE, cnbuf, 1);
}

I 2
#if NBM > 0
E 2
bmcons_putc(c)
	int c;
{
	char cnbuf[1];

	cnbuf[0] = (char)c;
	vt100_write(0, cnbuf, 1);
}
I 2
#endif
E 2
E 1
