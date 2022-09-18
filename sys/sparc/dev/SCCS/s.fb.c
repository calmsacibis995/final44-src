h18755
s 00002/00002/00095
d D 8.1 93/06/11 15:08:17 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00095
d D 7.4 93/04/20 05:49:24 torek 4 3
c spelling
e
s 00006/00006/00091
d D 7.3 92/10/11 12:38:55 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00092
d D 7.2 92/07/21 16:37:57 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00092/00000/00000
d D 7.1 92/07/13 00:41:29 torek 1 0
c date and time created 92/07/13 00:41:29 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: fb.c,v 1.6 92/06/17 05:35:46 torek Exp $
E 4
I 4
 * from: $Header: fb.c,v 1.7 92/11/26 01:12:48 torek Exp $
E 4
 */

/*
 * /dev/fb (indirect frame buffer driver).  This is gross; we should
 * just build cdevsw[] dynamically.
 */

D 3
#include "sys/param.h"
#include "sys/conf.h"
#include "sys/device.h"
#include "sys/proc.h"
#include "sys/fbio.h"
E 3
I 3
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/device.h>
#include <sys/proc.h>
#include <sys/fbio.h>
E 3

D 3
#include "machine/fbvar.h"
E 3
I 3
#include <machine/fbvar.h>
E 3

static struct fbdevice *devfb;

void
fb_unblank()
{

	if (devfb)
		(*devfb->fb_driver->fbd_unblank)(devfb->fb_device);
}

void
fb_attach(fb)
	struct fbdevice *fb;
{

if (devfb) panic("multiple /dev/fb declarers");
	devfb = fb;
}

int
fbopen(dev, flags, mode, p)
	dev_t dev;
	int flags, mode;
	struct proc *p;
{

	if (devfb == NULL)
		return (ENXIO);
	return (cdevsw[devfb->fb_major].d_open(dev, flags, mode, p));
}

int
fbclose(dev, flags, mode, p)
	dev_t dev;
	int flags, mode;
	struct proc *p;
{

	return (cdevsw[devfb->fb_major].d_close(dev, flags, mode, p));
}

int
fbioctl(dev, cmd, data, flags, p)
	dev_t dev;
	int cmd;
	caddr_t data;
	int flags;
	struct proc *p;
{

	return (cdevsw[devfb->fb_major].d_ioctl(dev, cmd, data, flags, p));
}

int
fbmap(dev, off, prot)
	dev_t dev;
	int off, prot;
{
	int (*map)() = cdevsw[devfb->fb_major].d_mmap;

	if (map == NULL)
		return (-1);
	return (map(dev, off, prot));
}
E 1
