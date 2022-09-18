h33924
s 00002/00002/00032
d D 8.1 93/06/11 14:57:01 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 7.1 92/06/04 15:59:11 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
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
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: if_enreg.h,v 4.300 91/06/09 06:25:57 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 * if_enreg.h for news800, news900
 */

#ifndef __IF_ENREG__
#define __IF_ENREG__ 1

/* command definitions */
#define	ENC_ADDR	0x00		/* Get Ethernet address */
#define	ENC_DIAG	0x01		/* Run On-board Diagnostics */
#define	ENC_START	0x02		/* Go Online */
#define	ENC_RESET	0x03		/* Reset */
#define	ENC_STAT	0x04		/* Report and Reset Statistics */
#define	ENC_XMIT	0x05		/* Load Transmit Data and Send */
#define	ENC_RECV	0x06		/* Receive Data */
#define	ENC_PROM	0x07		/* Set prom mode */
#define	ENC_SADDR	0x08		/* Set Ethernet address */
#define	ENC_NEWIF	0x09		/* Switch driver interface */

#endif /* !__IF_ENREG__ */
E 1
