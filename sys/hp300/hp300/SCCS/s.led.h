h17648
s 00002/00002/00025
d D 8.1 93/06/10 21:41:03 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 7.1 92/12/27 10:50:40 hibler 1 0
c date and time created 92/12/27 10:50:40 by hibler
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 University of Utah.
D 2
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: led.h 1.2 92/08/27$
 *
 *	%W% (Berkeley) %G%
 */

#define	LED_ADDR	0x1FFFF		/* a ROM address--strange but true */

#define	LED_LANXMT	0x80		/* for LAN transmit activity */
#define	LED_LANRCV	0x40		/* for LAN receive activity */
#define	LED_DISK	0x20		/* for disk activity */
#define	LED_PULSE	0x10		/* heartbeat */

#ifdef KERNEL
extern	char *ledaddr;
extern	int inledcontrol;
#endif
E 1
