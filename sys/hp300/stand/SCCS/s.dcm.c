h63270
s 00002/00002/00127
d D 8.1 93/06/10 21:46:42 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00125
d D 7.5 92/10/11 10:01:37 bostic 5 4
c make kernel includes standard
e
s 00002/00002/00127
d D 7.4 92/06/18 21:33:21 hibler 4 3
c merge with latest Utah version
e
s 00012/00013/00117
d D 7.3 91/05/07 10:05:48 hibler 3 2
c DIO-II support
e
s 00004/00004/00126
d D 7.2 90/12/16 16:39:15 bostic 2 1
c kernel reorg
e
s 00130/00000/00000
d D 7.1 90/05/25 16:20:52 mckusick 1 0
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

#ifdef DCMCONSOLE
D 2
#include "param.h"
#include "machine/cons.h"
#include "../hpdev/device.h"
#include "../hpdev/dcmreg.h"
E 2
I 2
D 5
#include "sys/param.h"
D 4
#include "../hp300/cons.h"
#include "../dev/device.h"
E 4
I 4
#include "hp/dev/cons.h"
#include "hp/dev/device.h"
E 4
#include "../dev/dcmreg.h"
E 5
I 5
#include <sys/param.h>
#include <hp/dev/cons.h>
#include <hp/dev/device.h>
#include <hp300/dev/dcmreg.h>
E 5
E 2

D 3
#define CONSPORT	(1)
struct dcmdevice *CONSOLE = NULL;
E 3
I 3
struct dcmdevice *dcmcnaddr = NULL;
E 3

dcmprobe(cp)
	struct consdev *cp;
{
	extern struct hp_hw sc_table[];
	register struct hp_hw *hw;
	register struct dcmdevice *dcm;

D 3
	for (hw = sc_table; hw < &sc_table[MAX_CTLR]; hw++)
	        if (hw->hw_type == COMMDCM && !badaddr((caddr_t)hw->hw_addr))
E 3
I 3
	for (hw = sc_table; hw < &sc_table[MAXCTLRS]; hw++)
	        if (HW_ISDEV(hw, D_COMMDCM) && !badaddr((caddr_t)hw->hw_kva))
E 3
			break;
D 3
	if (hw->hw_type != COMMDCM) {
E 3
I 3
	if (!HW_ISDEV(hw, D_COMMDCM)) {
E 3
		cp->cn_pri = CN_DEAD;
		return;
	}
D 3
	CONSOLE = (struct dcmdevice *)hw->hw_addr;
E 3
I 3
	dcmcnaddr = (struct dcmdevice *) hw->hw_kva;
E 3

D 3
	dcm = CONSOLE;
E 3
I 3
	dcm = dcmcnaddr;
E 3
	switch (dcm->dcm_rsid) {
	case DCMID:
		cp->cn_pri = CN_NORMAL;
		break;
	case DCMID|DCMCON:
		cp->cn_pri = CN_REMOTE;
		break;
	default:
		cp->cn_pri = CN_DEAD;
		break;
	}
}

dcminit(cp)
	struct consdev *cp;
{
D 3
	register struct dcmdevice *dcm = CONSOLE;
	register int port = CONSPORT;
E 3
I 3
	register struct dcmdevice *dcm = dcmcnaddr;
	register int port = CONUNIT;
E 3

	dcm->dcm_ic = IC_ID;
	while (dcm->dcm_thead[port].ptr != dcm->dcm_ttail[port].ptr)
		;
	dcm->dcm_data[port].dcm_baud = BR_9600;
	dcm->dcm_data[port].dcm_conf = LC_8BITS | LC_1STOP;
	SEM_LOCK(dcm);
	dcm->dcm_cmdtab[port].dcm_data |= CT_CON;
	dcm->dcm_cr |= (1 << port);
	SEM_UNLOCK(dcm);
	DELAY(15000);
}

#ifndef SMALL
dcmgetchar()
{
D 3
	register struct dcmdevice *dcm = CONSOLE;
E 3
I 3
	register struct dcmdevice *dcm = dcmcnaddr;
E 3
	register struct dcmrfifo *fifo;
	register struct dcmpreg *pp;
	register unsigned head;
	int c, stat, port;

D 3
	port = CONSPORT;
E 3
I 3
	port = CONUNIT;
E 3
	pp = dcm_preg(dcm, port);
	head = pp->r_head & RX_MASK;
	if (head == (pp->r_tail & RX_MASK))
		return(0);
	fifo = &dcm->dcm_rfifos[3-port][head>>1];
	c = fifo->data_char;
	stat = fifo->data_stat;
	pp->r_head = (head + 2) & RX_MASK;
	SEM_LOCK(dcm);
	stat = dcm->dcm_iir;
	SEM_UNLOCK(dcm);
	return(c);
}
#else
dcmgetchar()
{
	return(0);
}
#endif

dcmputchar(c)
	register int c;
{
D 3
	register struct dcmdevice *dcm = CONSOLE;
E 3
I 3
	register struct dcmdevice *dcm = dcmcnaddr;
E 3
	register struct dcmpreg *pp;
	register int timo;
	unsigned tail;
	int port, stat;

D 3
	port = CONSPORT;
E 3
I 3
	port = CONUNIT;
E 3
	pp = dcm_preg(dcm, port);
	tail = pp->t_tail & TX_MASK;
	timo = 50000;
	while (tail != (pp->t_head & TX_MASK) && --timo)
		;
	dcm->dcm_tfifos[3-port][tail].data_char = c;
	pp->t_tail = tail = (tail + 1) & TX_MASK;
	SEM_LOCK(dcm);
	dcm->dcm_cmdtab[port].dcm_data |= CT_TX;
	dcm->dcm_cr |= (1 << port);
	SEM_UNLOCK(dcm);
	timo = 1000000;
	while (tail != (pp->t_head & TX_MASK) && --timo)
		;
	SEM_LOCK(dcm);
	stat = dcm->dcm_iir;
	SEM_UNLOCK(dcm);
}
#endif
E 1
