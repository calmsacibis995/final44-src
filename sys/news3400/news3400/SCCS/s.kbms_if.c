h33001
s 00002/00002/00220
d D 8.1 93/06/11 15:02:41 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00020/00221
d D 7.3 93/03/09 23:53:57 utashiro 3 2
c cleanup header and machine dependency.
e
s 00006/00006/00235
d D 7.2 92/12/17 01:28:33 utashiro 2 1
c make kernel includes standard
e
s 00241/00000/00000
d D 7.1 92/06/04 16:06:54 mckusick 1 0
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
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* Keyboard Mouse Gate-array control routine */

D 2
#include "../include/fix_machine_type.h"
#include "../include/adrsmap.h"
E 2
I 2
D 3
#include <machine/fix_machine_type.h>
E 3
#include <machine/adrsmap.h>
E 2

#include "ms.h"
#include "bm.h"

D 2
#include "param.h"
#include "../sio/scc.h"
E 2
I 2
#include <sys/param.h>
#include <news3400/sio/scc.h>
E 2

D 3
#if defined(news1200) || defined(news3200)
E 3
I 3
#if defined(news3200)
E 3
D 2
#include "time.h"
#include "../iop/mouse.h"
E 2
I 2
#include <sys/time.h>
#include <news3400/iop/mouse.h>
E 2
#endif

typedef struct kbm_sw {
	u_char *stat_port;	/* Status port */
	u_char *data_port;	/* Data port */
	u_char *intr_port;	/* Interrupt port */
	u_char *reset_port;	/* Reset port */
	u_char *init1_port;	/* Initialize port 1 */
	u_char *init2_port;	/* Initialize port 2 */
	u_char *buzz_port;	/* Buzzer port */
	u_char *buzzf_port;	/* Buzzer frequency port */
	u_char intr_en;		/* Data for Interrupt Enable */
	u_char intr_in;		/* Interrupt Occur flag */
	u_char data_rdy;	/* Data Ready flag */
	u_char init1;		/* Speed */
	u_char init2;		/* Clock */
	u_char buzzf;		/* Buzzer frequency */
} Kbm_sw;

#define OFF 0x80
struct kbm_sw Kbm_port[] = {
	{
#ifdef news3400
		(u_char *) MOUSE_STAT,
#else
		(u_char *) KEYB_STAT,
#endif
		(u_char *) MOUSE_DATA,
		(u_char *) MOUSE_INTE,
		(u_char *) MOUSE_RESET,
		(u_char *) MOUSE_INIT1,
		(u_char *) MOUSE_INIT2,
		(u_char *) KEYB_BUZZ,
		(u_char *) KEYB_BUZZF,
		RX_MSINTE,
		RX_MSINT,
		RX_MSRDY,
#ifdef news3400
		0x80,	/* 1200 bps */
		0,
		0
#else
		1,
		0xe0,
		0x0a
#endif
	},
	{
		(u_char *) KEYB_STAT,
		(u_char *) KEYB_DATA,
		(u_char *) KEYB_INTE,
		(u_char *) KEYB_RESET,
		(u_char *) KEYB_INIT1,
		(u_char *) KEYB_INIT2,
		(u_char *) KEYB_BUZZ,
		(u_char *) KEYB_BUZZF,
		RX_KBINTE,
		RX_KBINT,
		RX_KBRDY,
#ifdef news3400
		0xf0,	/* 9600 bps */
		0,
		0
#else
		0,
		0xc0,
		0x0a
#endif
	}
};

kbm_open(chan)
	int chan;
{
	register Kbm_sw *kbm = &Kbm_port[chan];

#ifdef news3400
	/*
	 * Reset KB I/F.
	 * Disable KB interrupt.
	 * Clear KB overrun flag.
	 */
	*(volatile u_char *)kbm->reset_port = (u_char)0x01;
	*(volatile u_char *)kbm->init1_port = kbm->init1;
	if (chan == SCC_MOUSE)
		*(volatile u_char *)kbm->intr_port |= kbm->intr_en;
#else
	*kbm->reset_port = (u_char)0;
	*kbm->intr_port = (u_char)1;
#endif
D 3
#ifdef news1200
	*kbm->init1_port = kbm->init1;
	*kbm->init2_port = kbm->init2;
	*kbm->buzzf_port = kbm->buzzf;
#endif
E 3
	kbd_flush();
}

kbm_close(chan)
	int chan;
{
	register Kbm_sw *kbm = &Kbm_port[chan];

#ifdef news3400
	*(volatile u_char *)kbm->reset_port = (u_char)0x01;
#else
	*kbm->reset_port = (u_char)0;
	*kbm->intr_port = (u_char)0;
#endif
}

kbm_rint(chan)
	int chan;
{
#ifdef news3400
	volatile u_char *port = (volatile u_char *)Kbm_port[chan].data_port;
	volatile u_char *stat = (volatile u_char *)Kbm_port[chan].stat_port;
	volatile u_char *inte = (volatile u_char *)Kbm_port[chan].intr_port;
#else
	register u_char *port = Kbm_port[chan].data_port;
	register u_char *stat = Kbm_port[chan].stat_port;
	register u_char *inte = Kbm_port[chan].intr_port;
#endif
	int rdy = Kbm_port[chan].data_rdy;
	u_char code;

#ifdef news3400
	*inte &= ~Kbm_port[chan].intr_en;
#endif

	while (*stat & rdy) {
		code = *port;
		switch (chan) {
		    case SCC_MOUSE: {
#if NMS > 0
			extern int _ms_helper();

			if (xputc(code, SCC_MOUSE) < 0)
				printf("mouse queue overflow\n");
			/* KU:XXX softcall? */
			timeout(_ms_helper, (caddr_t)0, 0);
#endif
			break;
		    }
		    case SCC_KEYBOARD: {
#if NBM > 0
			extern int kb_softint();

			if (xputc(code, SCC_KEYBOARD) < 0)
				printf("keyboard queue overflow\n");
			/* KU:XXX softcall? */
			timeout(kb_softint, (caddr_t)0, 0);
#endif
			break;
		    }
		    default:
			printf("kb or ms stray intr\n");
			break;
		}
	}

#ifdef news3400
	*inte |= Kbm_port[chan].intr_en;
#else
	*inte = 1;
#endif
}


kbm_write(chan, buf, count)
	int chan;
	char *buf;
	register int count;
{
	register u_char *port = Kbm_port[chan].buzz_port;
	int c_save = count;
D 3

#ifdef news1200
	*port = count;
#endif

#ifdef news1700
	if (buf == NULL)
		while (--count >= 0)
			*port = 0xff;
	else
		while (--count >= 0)
			*port = *buf++;
#endif
E 3

#ifdef news3400
	*port = count / 3;
#endif

	return (c_save);
}

int
kbm_getc(chan)
	int chan;
{
#ifdef news3400
	volatile u_char *port = (volatile u_char *)Kbm_port[chan].data_port;
	volatile u_char *stat = (volatile u_char *)Kbm_port[chan].stat_port;
#else
	register u_char *port = Kbm_port[chan].data_port;
	register u_char *stat = Kbm_port[chan].stat_port;
#endif
	int rdy = Kbm_port[chan].data_rdy;

	if (*stat & rdy) 
		return (*port & 0xff);
	else
		return (-1);
}
E 1
