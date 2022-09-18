h15472
s 00001/00011/00156
d D 7.4 90/06/28 22:50:45 bostic 4 3
c new copyright notice
e
s 00013/00006/00154
d D 7.3 88/06/29 17:55:34 bostic 3 2
c install approved copyright notice
e
s 00014/00007/00146
d D 7.2 88/06/13 15:10:25 mckusick 2 1
c update copyright for distribution
e
s 00153/00000/00000
d D 7.1 87/07/20 10:22:45 karels 1 0
c from Mt. Xinu; status unknown
e
u
U
t
T
I 1
/*
D 2
 * %W% (Berkeley) %G%
E 2
I 2
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 *
 *	%W% (Berkeley) %G%
D 3
 *
E 3
I 3
 */

/*
E 3
E 2
 * DMV-11 Driver
 *
 * Qbus Sync DDCMP interface - DMV operated in full duplex, point to point mode
 *
D 2
 * Derived from 4.3 release if_dmc.h rev. 6.4 dated 6/8/85
 * 
 * Bob Kridle
 * mt Xinu
E 2
I 2
 * Written by Bob Kridle of Mt Xinu
 * starting from if_dmc.h version 6.4 dated 6/8/85 
E 2
 */

struct dmvdevice {
	union {
		u_char    xbsel[2];
		u_short	xwsel;
	} xw0;
	union {
		u_char    xbsel[2];
		u_short	xwsel;
	} xw1;
	union {
		u_char    xbsel[2];
		u_short	xwsel;
	} xw2;
	union {
		u_char    xbsel[2];
		u_short	xwsel;
	} xw3;
	union {
		u_char    xbsel[2];
		u_short	xwsel;
	} xw4;
};

#define  bsel0	xw0.xbsel[0]
#define  bsel1	xw0.xbsel[1]
#define  bsel2	xw1.xbsel[0]
#define  bsel3	xw1.xbsel[1]
#define  bsel4	xw2.xbsel[0]
#define  bsel5	xw2.xbsel[1]
#define  bsel6	xw3.xbsel[0]
#define  bsel7	xw3.xbsel[1]
#define  bsel10	xw4.xbsel[0]
#define  bsel11	xw4.xbsel[1]

#define	 wsel0	xw0.xwsel
#define	 wsel2	xw1.xwsel
#define	 wsel4	xw2.xwsel
#define	 wsel6	xw3.xwsel
#define	 wsel10	xw4.xwsel

/*
 * dmv software packet encapsulation.  This allows the dmv
 * link to be multiplexed among several protocols.
 * The first eight bytes of the dmc header are garbage,
 * since on a vax the uba has been known to mung these
 * bytes.  The next two bytes encapsulate packet type.
 */
struct dmv_header {
D 2
/*	Lets try without this first for dmv - rk
	char	dmv_buf[8];	/* space for uba on vax */
E 2
	short	dmv_type;	/* encapsulate packet type */
};

/* packet types */
#define	DMV_IPTYPE	1
#define	DMV_TRAILER	2
#define	DMV_NTRAILER	16

/*
 * DMVMTU includes space for data (1024) + 
 * protocol header (256) + trailer descriptor (4).
 * The software link encapsulation header (dmv_header)
 * is handled separately.
 */
#define DMVMTU  1284

#define	RDYSCAN	16	/* loop delay for RDYI after RQI */

	/* defines for bsel0 */

#define	DMV_IEI		0x01		/* interrupt enable, input */
#define	DMV_IEO		0x10		/* interrupt enable, output */
#define	DMV_RQI		0x80		/* request input */
#define DMV0BITS	"\10\8RQI\5IEO\1IEI"

	/* defines for bsel1 */

#define	DMV_MCLR	0x40		/* master clear */
#define	DMV_RUN		0x80		/* run */
#define DMV1BITS	"\10\8RUN\7MCLR"

	/* defines for bsel2 */

#define	DMV_CMD		0x07		/* command/response type field */


	/* input commands */

#define	DMV_BACCR	0x00		/* buffer address, char. count - rec */
#define	DMV_BACCX	0x04		/* buffer address, char. count - xmit */
#define	DMV_MDEFI	0x02		/* mode definition input */
#define	DMV_CNTRLI	0x01		/* control input */

	/* response identifiers */

#define	DMV_CNTRLO	0x01		/* control output */
#define	DMV_MDEFO	0x02		/* information output */
#define	DMV_BDRUS	0x00		/* buffer definition - rec. used */
#define	DMV_BDRUNUS	0x03		/* buffer disposition - rec. unused */
#define	DMV_BDXSA	0x04		/* buffer dispostiion - sent & ack */
#define	DMV_BDXSN	0x06		/* buffer dispostiion - sent & not ack*/
#define	DMV_BDXNS	0x07		/* buffer dispostiion - not sent */

#define DMV_22BIT	0x08		/* buffer address in 22 bit format */
#define DMV_RDI		0x10		/* ready for input */
#define DMV_RDO		0x80		/* ready for output */
#define DMV2BITS	"\10\8RDO\5RDI"

	/* defines for CNTRLI mode */

#define	DMV_RDTSS	0x20		/* read tributary status slot */
#define	DMV_RDCTSS	0x40		/* read/clear tributary status slot */
#define	DMV_WRTSS	0x80		/* write tributary status slot */
#define	DMV_TRIBN	0x1f		/* tributary number */
#define	DMV_RQKEY	0x1f		/* control command request key */
#define DMV_ECBP	0x100		/* establish common buffer pool */

	/* relevant command request keys */

#define DMV_NOP		0x00		/* no-op */
#define DMV_ESTTRIB	0x01		/* establish tributary */
#define DMV_REQSUS	0x03		/* request start up state */
#define DMV_REQHS	0x05		/* request halt state */
#define DMV_WMC		0x10		/* write modem control */
#define DMV_RMC		0x11		/* read modem control */

	/* some interesting CNTRLO codes 
	 *
	 * use the manual if yours isn't here!!
	 */

#define	DMV_RTE		0002		/* receive threshold error */
#define	DMV_TTE		0004		/* xmit threshold error */
#define	DMV_STE		0006		/* select threshold error */
#define DMV_ORUN	0024		/* other end enters run state */
#define DMV_NXM		0302		/* non-existant memory */
#define DMV_MODD	0304		/* modem disconnected */
#define DMV_QOVF	0306		/* response queue overflow */
#define DMV_CXRL	0310		/* modem cxr lost */

#define DMV_EEC		0377		/* CNTRLO error code mask */
E 1
