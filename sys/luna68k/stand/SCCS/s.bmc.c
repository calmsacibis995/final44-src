h61223
s 00002/00002/00085
d D 8.1 93/06/10 22:28:56 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00000/00080
d D 7.2 93/01/20 09:13:05 akito 2 1
c added BM board checking
e
s 00080/00000/00000
d D 7.1 92/12/13 03:50:08 akito 1 0
c date and time created 92/12/13 03:50:08 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * bmc.c -- bitmap console driver
 *   by A.Fujita, JUL-06-1992
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <luna68k/stand/rcvbuf.h>
#include <luna68k/stand/preset.h>

extern	int dipsw1;
I 2
extern	int nplane;

E 2
extern	struct rcvbuf	rcvbuf[];

bmcintr()
{
}

/*
 * Following are all routines needed for SIO to act as console
 */
#include <luna68k/luna68k/cons.h>

bmccnprobe(cp)
	struct consdev *cp;
{
	if ((dipsw1 & PS_BMC_CONS) == 0) {
I 2
		cp->cn_pri = CN_DEAD;
		return;
	}

	if (nplane == 0) {
E 2
		cp->cn_pri = CN_DEAD;
		return;
	}

	/* initialize required fields */
	cp->cn_dev = 1;
	cp->cn_tp  = 0;
	cp->cn_pri = CN_NORMAL;
}

bmccninit(cp)
	struct consdev *cp;
{
	sioinit();
	bmdinit();
}

bmccngetc(dev)
	dev_t dev;
{
	register int c;
	register int unit = 1;

	while (RBUF_EMPTY(unit)) {
		DELAY(10);
	}

	POP_RBUF(unit, c);

	return(c);
/*
	return(siocngetc(dev));
 */
}

bmccnputc(dev, c)
	dev_t dev;
	int c;
{
	bmdputc(c);
}
E 1
