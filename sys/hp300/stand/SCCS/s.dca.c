h55048
s 00002/00002/00101
d D 8.1 93/06/10 21:46:39 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00099
d D 7.5 92/10/11 10:01:36 bostic 5 4
c make kernel includes standard
e
s 00008/00004/00095
d D 7.4 92/06/18 21:33:20 hibler 4 3
c merge with latest Utah version
e
s 00008/00007/00091
d D 7.3 91/05/07 10:05:45 hibler 3 2
c DIO-II support
e
s 00004/00004/00094
d D 7.2 90/12/16 16:39:13 bostic 2 1
c kernel reorg
e
s 00098/00000/00000
d D 7.1 90/05/08 22:46:02 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifdef DCACONSOLE
D 2
#include "../sys/param.h"
#include "../hpdev/dcareg.h"
#include "machine/cpu.h"
#include "machine/cons.h"
E 2
I 2
D 5
#include "sys/param.h"
D 4
#include "../dev/dcareg.h"
E 4
I 4
#include "hp/dev/dcareg.h"
E 4
#include "../include/cpu.h"
D 4
#include "../hp300/cons.h"
E 4
I 4
#include "hp/dev/cons.h"
E 5
I 5
#include <sys/param.h>
#include <hp/dev/dcareg.h>
#include <machine/cpu.h>
#include <hp/dev/cons.h>
E 5
E 4
E 2

D 3
#define CONSDEV	(0)
#define CONSOLE ((struct dcadevice *)(EXTIOBASE + (9 * IOCARDSIZE)))
E 3
I 3
struct dcadevice *dcacnaddr = 0;
E 3

dcaprobe(cp)
	struct consdev *cp;
{
D 3
	register struct dcadevice *dca = CONSOLE;
E 3
I 3
	register struct dcadevice *dca;
E 3

D 3
	if (badaddr((char *)CONSOLE)) {
E 3
I 3
	dcacnaddr = (struct dcadevice *) sctoaddr(CONSCODE);
	if (badaddr((char *)dcacnaddr)) {
E 3
		cp->cn_pri = CN_DEAD;
		return;
	}
I 4
#ifdef FORCEDCACONSOLE
	cp->cn_pri = CN_REMOTE;
#else
E 4
I 3
	dca = dcacnaddr;
E 3
D 4
	switch (dca->dca_irid) {
E 4
I 4
	switch (dca->dca_id) {
E 4
	case DCAID0:
	case DCAID1:
		cp->cn_pri = CN_NORMAL;
		break;
	case DCAREMID0:
	case DCAREMID1:
		cp->cn_pri = CN_REMOTE;
		break;
	default:
		cp->cn_pri = CN_DEAD;
		break;
	}
I 4
#endif
E 4
}

dcainit(cp)
	struct consdev *cp;
{
D 3
	register struct dcadevice *dca = CONSOLE;
E 3
I 3
	register struct dcadevice *dca = dcacnaddr;
E 3

D 4
	dca->dca_irid = 0xFF;
E 4
I 4
	dca->dca_reset = 0xFF;
E 4
	DELAY(100);
	dca->dca_ic = 0;
	dca->dca_cfcr = CFCR_DLAB;
	dca->dca_data = DCABRD(9600) & 0xFF;
	dca->dca_ier = DCABRD(9600) >> 8;
	dca->dca_cfcr = CFCR_8BITS;
}

#ifndef SMALL
dcagetchar()
{
D 3
	register struct dcadevice *dca = CONSOLE;
E 3
I 3
	register struct dcadevice *dca = dcacnaddr;
E 3
	short stat;
	int c;

	if (((stat = dca->dca_lsr) & LSR_RXRDY) == 0)
		return(0);
	c = dca->dca_data;
	return(c);
}
#else
dcagetchar()
{
	return(0);
}
#endif

dcaputchar(c)
	register int c;
{
D 3
	register struct dcadevice *dca = CONSOLE;
E 3
I 3
	register struct dcadevice *dca = dcacnaddr;
E 3
	register int timo;
	short stat;

	/* wait a reasonable time for the transmitter to come ready */
	timo = 50000;
	while (((stat = dca->dca_lsr) & LSR_TXRDY) == 0 && --timo)
		;
	dca->dca_data = c;
	/* wait for this transmission to complete */
	timo = 1000000;
	while (((stat = dca->dca_lsr) & LSR_TXRDY) == 0 && --timo)
		;
}
#endif
E 1
