h21507
s 00001/00001/00068
d D 8.3 95/04/28 17:29:18 bostic 9 8
c P80 is the 80Mbit ring
e
s 00041/00021/00028
d D 8.2 94/04/20 12:06:44 sklower 8 6
c make conform to RFC1573 (21 additional types)
e
s 00040/00020/00029
d R 8.2 94/04/20 11:44:44 bostic 7 6
c update from Keith Sklower, based on RFC1573 (21 additional types)
e
s 00002/00002/00047
d D 8.1 93/06/10 22:45:03 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00005/00037
d D 7.5 93/02/25 16:39:39 sklower 5 4
c make conform to MIB II
e
s 00004/00000/00038
d D 7.4 92/06/02 12:08:38 sklower 4 3
c latest types from mrose (need frame relay)
e
s 00001/00011/00037
d D 7.3 90/06/28 21:31:13 bostic 3 2
c new copyright notice
e
s 00028/00008/00020
d D 7.2 89/09/20 11:55:39 sklower 2 1
c Add more types for SNMP
e
s 00028/00000/00000
d D 7.1 89/09/04 17:32:38 karels 1 0
c new file by sklower
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1982, 1989 Regents of the University of California.
E 2
I 2
D 6
 * Copyright (c) 1989 Regents of the University of California.
E 2
 * All rights reserved.
E 6
I 6
D 8
 * Copyright (c) 1989, 1993
E 8
I 8
 * Copyright (c) 1989, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 3
 * Redistribution and use in source and binary forms are permitted
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 8

E 8
D 5
/* interface types for benefit of parsing media address headers */
E 5
I 5
/*
 * Interface types for benefit of parsing media address headers.
 * This list is derived from the SNMP list of ifTypes, currently
D 8
 * documented in RFC1123.
E 8
I 8
 * documented in RFC1573.
E 8
 */

E 5
D 2
#define	IFT_LOOP	0x1		/* loopback */
#define	IFT_XETHER	0x2		/* old 3MBaud experimental ethernet */
#define	IFT_ETHER	0x3		/* 802.3 */
#define	IFT_IMP		0x4		/* Arpanet imp interface */
#define	IFT_P8010	0x5		/* Pronet 10/Pronet 80 */
#define IFT_EON		0x6		/* ISO over IP */
#define IFT_HY		0x7		/* Hyperchannel */
E 2
I 2
D 8
#define IFT_OTHER	0x1		/* none of the following */
#define IFT_1822	0x2		/* old-style arpanet imp */
#define IFT_HDH1822	0x3		/* HDH arpanet imp */
#define IFT_X25DDN	0x4		/* x25 to imp */
D 5
#define IFT_X25		0x5		/* PDN X25 interface */
#define	IFT_ETHER	0x6		/* Ethernet I or II */
E 5
I 5
#define IFT_X25		0x5		/* PDN X25 interface (RFC877) */
E 8
I 8
#define	IFT_OTHER	0x1		/* none of the following */
#define	IFT_1822	0x2		/* old-style arpanet imp */
#define	IFT_HDH1822	0x3		/* HDH arpanet imp */
#define	IFT_X25DDN	0x4		/* x25 to imp */
#define	IFT_X25		0x5		/* PDN X25 interface (RFC877) */
E 8
#define	IFT_ETHER	0x6		/* Ethernet CSMACD */
E 5
#define	IFT_ISO88023	0x7		/* CMSA CD */
#define	IFT_ISO88024	0x8		/* Token Bus */
#define	IFT_ISO88025	0x9		/* Token Ring */
#define	IFT_ISO88026	0xa		/* MAN */
#define	IFT_STARLAN	0xb
#define	IFT_P10		0xc		/* Proteon 10MBit ring */
D 9
#define	IFT_P80		0xd		/* Proteon 10MBit ring */
E 9
I 9
#define	IFT_P80		0xd		/* Proteon 80MBit ring */
E 9
D 8
#define IFT_HY		0xe		/* Hyperchannel */
#define IFT_FDDI	0xf
#define IFT_LAPB	0x10
#define IFT_SDLC	0x11
#define IFT_T1		0x12
D 5
#define IFT_CEPT	0x13
E 5
I 5
#define IFT_CEPT	0x13		/* E1 - european T1 */
E 5
#define IFT_ISDNBASIC	0x14
#define IFT_ISDNPRIMARY	0x15
D 5
#define IFT_PTPSERIAL	0x16
E 5
I 5
#define IFT_PTPSERIAL	0x16		/* Proprietary PTP serial */
#define IFT_PPP		0x17		/* RFC 1331 */
E 8
I 8
#define	IFT_HY		0xe		/* Hyperchannel */
#define	IFT_FDDI	0xf
#define	IFT_LAPB	0x10
#define	IFT_SDLC	0x11
#define	IFT_T1		0x12
#define	IFT_CEPT	0x13		/* E1 - european T1 */
#define	IFT_ISDNBASIC	0x14
#define	IFT_ISDNPRIMARY	0x15
#define	IFT_PTPSERIAL	0x16		/* Proprietary PTP serial */
#define	IFT_PPP		0x17		/* RFC 1331 */
E 8
E 5
#define	IFT_LOOP	0x18		/* loopback */
D 8
#define IFT_EON		0x19		/* ISO over IP */
E 8
I 8
#define	IFT_EON		0x19		/* ISO over IP */
E 8
#define	IFT_XETHER	0x1a		/* obsolete 3MB experimental ethernet */
#define	IFT_NSIP	0x1b		/* XNS over IP */
#define	IFT_SLIP	0x1c		/* IP over generic TTY */
I 4
#define	IFT_ULTRA	0x1d		/* Ultra Technologies */
#define	IFT_DS3		0x1e		/* Generic T3 */
#define	IFT_SIP		0x1f		/* SMDS */
D 8
#define	IFT_FRELAY	0x20		/* Frame Relay */
I 5
#define IFT_RS232	0x21		/* Used elsewhere by SNMP as index */
E 8
I 8
#define	IFT_FRELAY	0x20		/* Frame Relay DTE only */
#define	IFT_RS232	0x21
#define	IFT_PARA	0x22		/* parallel-port */
#define	IFT_ARCNET	0x23
#define	IFT_ARCNETPLUS	0x24
#define	IFT_ATM		0x25		/* ATM cells */
#define	IFT_MIOX25	0x26
#define	IFT_SONET	0x27		/* SONET or SDH */
#define	IFT_X25PLE	0x28
#define	IFT_ISO88022LLC	0x29
#define	IFT_LOCALTALK	0x2a
#define	IFT_SMDSDXI	0x2b
#define	IFT_FRELAYDCE	0x2c		/* Frame Relay DCE */
#define	IFT_V35		0x2d
#define	IFT_HSSI	0x2e
#define	IFT_HIPPI	0x2f
#define	IFT_MODEM	0x30		/* Generic Modem */
#define	IFT_AAL5	0x31		/* AAL5 over ATM */
#define	IFT_SONETPATH	0x32
#define	IFT_SONETVT	0x33
#define	IFT_SMDSICIP	0x34		/* SMDS InterCarrier Interface */
#define	IFT_PROPVIRTUAL	0x35		/* Proprietary Virtual/internal */
#define	IFT_PROPMUX	0x36		/* Proprietary Multiplexing */
E 8
E 5
E 4
E 2
E 1
