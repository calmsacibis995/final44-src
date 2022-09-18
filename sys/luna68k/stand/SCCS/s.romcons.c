h14197
s 00002/00002/00048
d D 8.1 93/06/10 22:29:53 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00050/00000/00000
d D 7.1 92/12/13 03:50:22 akito 1 0
c date and time created 92/12/13 03:50:22 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* romcons.c   OCT-21-1991 */

#include <sys/types.h>
#include <luna68k/luna68k/cons.h>
#include <luna68k/stand/romvec.h>

romcnprobe(cp)
	struct consdev *cp;
{
	cp->cn_tp  = 0;
	cp->cn_dev = 0;
	cp->cn_pri = CN_NORMAL;
}

romcninit(cp)
	struct consdev *cp;
{
}

romcngetc(dev)
	dev_t dev;
{
	int c;

	for (;;)
		if ((c = ROM_getchar()) != -1)
			break;

	return(c);
}

romcnputc(dev, c)
	dev_t dev;
	int c;
{
	ROM_putchar(c);
}
E 1
