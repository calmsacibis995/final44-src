h52902
s 00002/00002/00098
d D 8.1 93/06/10 22:29:08 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00100/00000/00000
d D 7.1 92/12/13 03:50:10 akito 1 0
c date and time created 92/12/13 03:50:10 by akito
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

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/file.h>
#include <sys/conf.h>
#include <luna68k/luna68k/cons.h>

#define NBMC	1
#define	NSIO	1
#define	NROM	1

/* XXX - all this could be autoconfig()ed */
#include "romvec.h"
#if NBMC > 0
int bmccnprobe(), bmccninit(), bmccngetc(), bmccnputc();
#endif
#if NSIO > 0
int siocnprobe(), siocninit(), siocngetc(), siocnputc();
#endif
#if NROM > 0
int romcnprobe(), romcninit(), romcngetc(), romcnputc();
#endif

struct	consdev constab[] = {
#if NBMC > 0
	{ bmccnprobe,	bmccninit,	bmccngetc,	bmccnputc },
#endif
#if NSIO > 0
	{ siocnprobe,	siocninit,	siocngetc,	siocnputc },
#endif
#if NROM > 0
	{ romcnprobe,	romcninit,	romcngetc,	romcnputc },
#endif
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

cngetc()
{
	if (cn_tab == NULL)
		return(0);
	return((*cn_tab->cn_getc)(cn_tab->cn_dev));
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
