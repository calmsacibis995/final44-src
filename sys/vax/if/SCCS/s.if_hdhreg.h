h63081
s 00001/00011/00107
d D 7.3 90/06/28 22:51:45 bostic 6 5
c new copyright notice
e
s 00021/00004/00097
d D 7.2 88/08/04 15:22:19 bostic 5 4
c add Berkeley specific copyright
e
s 00000/00000/00101
d D 7.1 86/06/05 01:36:24 mckusick 4 3
c 4.3BSD release version
e
s 00012/00012/00089
d D 6.3 86/02/20 16:54:30 karels 3 2
c lint
e
s 00001/00000/00100
d D 6.2 85/11/11 11:09:46 karels 2 1
c now compiles under 4.3
e
s 00100/00000/00000
d D 6.1 85/08/26 17:39:50 karels 1 0
c from ACC
e
u
U
t
T
I 2
D 5
/*	%W% (Berkeley) %G% */
E 2
I 1


/* $Header$ */
E 5
I 5
/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Advanced Computer Communications.
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */
E 5

/*
 * ACC IF-11/HDH interface
 */

struct hdhregs {			/* device registers */
	u_short	csr;			/* control and status register */
	u_char	iochn;			/* logical channel */
	u_char	ioadx;			/* address extension (A16,A17) */
	u_short	ioadl;			/* buffer address (A0-A15) */
	u_short	iocnt;			/* byte count */
	u_char	iofcn;			/* UMC funciton code */
	u_char	iosbf;			/* UMC subfunction code */
	u_char	ioini;			/* comm regs valid flag */
	u_char	staack;			/* interrupt acknowledge flag */
	u_char	ionmi;			/* NMI routine active flag */
	u_char	ioxfrg;			/* UMR transfer grant flag */
	u_char	stachn;			/* interrupt channel number */
	u_char	statyp;			/* interrupt type code */
	u_char	stacc;			/* completion function code */
	u_char	stacs;			/* completion subfunction code */
	u_short	stacnt;			/* completion byte count */
};

/* defines for CSR */

#define HDH_UER		0100000		/* UMC error condition */
#define HDH_NXM		0040000		/* non-existent memory error */
#define HDH_PER		0020000		/* UNIBUS parity error */
#define HDH_ZRUN	0010000		/* Z80 running */
#define HDH_ZGO		0004000		/* Z80 not in wait state */
#define HDH_MBLK	0000200		/* memory swap state (0=main, 1=srv) */
#define	HDH_SRV		0000100		/* select UMC service memory */
#define HDH_MAIN	0000040		/* select UMC main memory */
#define HDH_DMA		0000020		/* DMA enable */
#define HDH_WRT		0000010		/* DMA write enable */
#define HDH_IEN		0000004		/* interrupt enable */
#define HDH_RST		0000002		/* reset */
#define	HDH_NMI		0000001		/* cause NMI */

#define HDH_BITS \
"\10\20UER\17NXM\16PER\15ZRUN\14ZGO\10MBLK\7SRV\6MAIN\5DMA\4WRT\3IEN\2RST\1NMI"

/* start i/o function code definitions */

#define HDHWRT		0	/* write to if-11 */
#define HDHRDB		1	/* read from if-11 */
#define HDHSTR		2	/* stream flag */
#define HDHEOS		6	/* end of stream flag */
#define HDHABT		8	/* abort flag */
#define HDHUMR		16	/* UMR protocol flag */

/* interrupt type definitions */

#define HDHSACK		0	/* start i/o ack */
#define HDHDONE		1	/* i/o completion */
#define HDHXREQ		2	/* UMR protocol transfer request */

/* i/o completion codes */

#define HDHIOCOK	0001	/* successful completion */
#define HDHIOCOKP 	0002	/* successful completion, more data pending */
#define HDHIOCABT 	0361	/* i/o aborted */
#define HDHIOCERR 	0321	/* program error */
#define HDHIOCOVR 	0363	/* overrun error */
#define HDHIOCUBE 	0374	/* non-existant memory or unibus error */

/* UMR protocol transfer grant code definitions */

#define HDHXEVN		1	/* start with even address */
#define HDHXODD		2	/* start with odd address */
#define HDHNUMR		4	/* non-UMR transfer */
#define HDHXABT		8	/* abort transfer */

/* HDH supervisor request code definitions */
#define HDHINIT		0x42	/* SYSINIT opcode */

#define HDHSUP		0xf0	/* supervisor HDH status/line control prefix */
#define HDHIMP		0x400	/* IMP line up modifier */
#define HDHREFL		0x800	/* reflect mode modifier */
#define HDHINLB		0x1000	/* internal loopback modifier */
#define HDHEXLP		0x2000	/* external loopback modifier */
D 3
#define HDHRQST		HDHSUP+0x0000	/* line status request */
#define HDHRQUP		HDHSUP+0x0100	/* line up request */
#define HDHRQDN		HDHSUP+0x0200	/* line down request */
E 3
I 3
#define HDHRQST		(HDHSUP+0x0000)	/* line status request */
#define HDHRQUP		(HDHSUP+0x0100)	/* line up request */
#define HDHRQDN		(HDHSUP+0x0200)	/* line down request */
E 3

/* HDH supervisor reply code definitions */

D 3
#define HDHIACK		HDHSUP+0x4200	/* line init ack */
#define HDHLNUP		HDHSUP+0x0100	/* line up reply */
#define HDHLNDN		HDHSUP+0x0200	/* line down reply */
#define HDHLNACK	HDHSUP+0x0300	/* ack line up request (but line is down now) */
#define HDHTIMO		HDHSUP+0x0400	/* line timeout */
#define HDHLOOP		HDHSUP+0x0500	/* loopback message */
#define HDHDTERR	HDHSUP+0x0600	/* host data error detected */
#define HDHSQRCV	HDHSUP+0x0700	/* HDLC sequence error detected by IMP */
#define HDHSQERR	HDHSUP+0x0800	/* HDLC sequence error detected by if-11 */
E 3
I 3
#define HDHIACK		(HDHSUP+0x4200)	/* line init ack */
#define HDHLNUP		(HDHSUP+0x0100)	/* line up reply */
#define HDHLNDN		(HDHSUP+0x0200)	/* line down reply */
#define HDHLNACK	(HDHSUP+0x0300)	/* ack line up request (but line is down now) */
#define HDHTIMO		(HDHSUP+0x0400)	/* line timeout */
#define HDHLOOP		(HDHSUP+0x0500)	/* loopback message */
#define HDHDTERR	(HDHSUP+0x0600)	/* host data error detected */
#define HDHSQRCV	(HDHSUP+0x0700)	/* HDLC sequence error detected by IMP */
#define HDHSQERR	(HDHSUP+0x0800)	/* HDLC sequence error detected by if-11 */
E 3
E 1
