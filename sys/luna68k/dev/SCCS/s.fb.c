h29916
s 00002/00002/00128
d D 8.1 93/06/10 22:16:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00130
d D 7.4 93/06/02 09:56:36 akito 4 3
c remove unnecessary include
e
s 00032/00012/00100
d D 7.3 93/02/02 10:55:42 akito 3 2
c delete FBIO_ON & FBIO_OFF
e
s 00014/00018/00098
d D 7.2 92/12/20 12:37:59 akito 2 1
c add FBIO_ON & FBIO_OFF ioctl
e
s 00116/00000/00000
d D 7.1 92/12/19 09:54:14 akito 1 0
c date and time created 92/12/19 09:54:14 by akito
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992 OMRON Corporation.
D 5
 * Copyright (c) 1990,1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1993, 19901992
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 * from: hp/dev/grf.c		7.13 (Berkeley) 7/12/92
 *
 *	%W% (Berkeley) %G%
 */

/*
 * fb.c -- frame-buffer device driver
 *	by A.Fujita, Dec-16-1992
 */

#include <sys/param.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <luna68k/dev/fbio.h>

I 2
D 4
#include "bmc.h"

E 4
I 3
extern	int hz;

int	fb_erase_screen();

E 3
E 2
volatile struct fb_rfc *rfcPtr = (struct fb_rfc *) 0xB1000000;
static   struct fb_rfc  rfcVal;

int
fbopen(dev, flags, mode, p)
	dev_t dev;
	int flags, mode;
	struct proc *p;
{
I 3
	fb_erase_screen();

E 3
	return(0);
}

int
fbclose(dev, flags, mode, p)
	dev_t dev;
	int flags, mode;
	struct proc *p;
{
I 3
	fb_adjust(7, -27);

	timeout(fb_erase_screen, (caddr_t)0, hz);

E 3
	return(0);
}

int
fbioctl(dev, cmd, data, flags, p)
	dev_t dev;
	int cmd;
	caddr_t data;
	int flags;
	struct proc *p;
{
	struct fb_rfc *rfcp;
	int error;

	error = 0;
	switch (cmd) {

D 2
	case FBIOPUTRFCT:
E 2
I 2
D 3
	case FBIO_ON:
#if NBMC > 0
		bmd_off();
#endif
		break;
E 2

I 2
	case FBIO_OFF:
#if NBMC > 0
		bmd_on();
#endif
		break;

E 3
	case FBIOSETRFCT:
E 2
		*rfcPtr = rfcVal = *((struct fb_rfc *) data);
		break;

	case FBIOGETRFCT:
                *(struct fb_rfc *)data = rfcVal;
		break;

D 2
/*
	case GRFIOCON:
		error = grfon(dev);
		break;

	case GRFIOCOFF:
		error = grfoff(dev);
		break;

	case GRFIOCMAP:
		error = grfmmap(dev, (caddr_t *)data, p);
		break;

	case GRFIOCUNMAP:
		error = grfunmmap(dev, *(caddr_t *)data, p);
		break;
 */
E 2
	default:
		error = EINVAL;
		break;

	}
	return(error);
}

fb_adjust(hcnt, vcnt)
	int hcnt, vcnt;
{
	rfcVal.rfc_hcnt = hcnt;			/* shift left   16 dot */
	rfcVal.rfc_vcnt = vcnt;			/* shift down    1 dot */

	*rfcPtr = rfcVal;
I 3
}

#define PL_WIDTH	64				/* Plane Width  (long) */

#define	SB_HIGHT	1024				/* Screen Hight  (Bit) */
#define SL_WIDTH	40				/* Screen Width (Long) */

#define SKIP_NEXT_LINE(addr)			( addr += (PL_WIDTH - SL_WIDTH) )

fb_erase_screen()
{
	volatile register u_long *lp = (u_long *) 0xB1080008;

	register int i, j;

	for (i = 0; i < SB_HIGHT; i++) {
		for (j = 0; j < SL_WIDTH; j++)
			*lp++ = 0;
		SKIP_NEXT_LINE(lp);
	}

	return;
E 3
}

int
fbselect(dev, rw)
	dev_t dev;
	int rw;
{
	return(0);
}

int
fbmap(dev, off, prot)
	dev_t dev;
	int off, prot;
{
	return(((u_int) 0xB10C0000 + off) >> PGSHIFT);
}
E 1
